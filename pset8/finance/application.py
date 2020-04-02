import os
import time
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    indicate = db.execute("SELECT * FROM indication WHERE id = :idd", idd=session["user_id"])

    rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    return render_template("index.html", indication=indicate, balance=round(rows[0]["cash"]))


##########################################################################################################################################################################
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check for empty fields
        if not request.form.get("symbol") or request.form.get("symbol") == 0:
            return apology("NO STOCKS", 400)
        if not (request.form.get("shares")).isnumeric() or not round(float(request.form.get("shares"))) or round(float(request.form.get("shares"))) <= 0:
            return apology("INVALID INPUT", 400)

        stock = request.form.get("symbol")
        shares = request.form.get("shares")

        # Search for stock details
        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("Doesn't exsist", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = :idd",
                          idd=session["user_id"])

        idd = session["user_id"]
        total_price = int(shares)*(quote["price"])
        if rows[0]["cash"] < total_price:
            return apology("Mafesh flos ya 7lawa", 400)

        # UPDATE Portfolio table(log table)
        db.execute("INSERT INTO portfolio (stock, price, time, id, shares, status) VALUES (:stock, :total_price, :time, :idd, :sharess, :status)",
                   stock=request.form.get("symbol"),
                   total_price=int(shares)*(quote["price"]),
                   time=time.asctime(time.localtime(time.time())),
                   idd=session["user_id"],
                   sharess=int(request.form.get("shares")), status="buy")

        # Operations for indication table
        indicate = db.execute("SELECT * FROM indication WHERE id = :idd", idd=session["user_id"])

        # Incase of new stock bought from current user_id
        if len(indicate) != 1 or not request.form.get("symbol") in indicate[0]["stock"]:

            # INSERT into INDICATION table for new stocks bought
            db.execute("INSERT INTO indication (stock, shares, totally_paid, id, totally_sold, stock_price) VALUES (:stock, :shares, :totally_paid, :id, :totally_sold, :stockprice)",
                       stock=request.form.get("symbol"),
                       shares=int(request.form.get("shares")),
                       totally_paid=int(shares)*(quote["price"]),
                       id=session["user_id"], totally_sold=0,
                       stockprice=quote["price"])

        else:
            # Accumulate the stock shares and money paid for it
            db.execute("UPDATE indication set shares = :shares, totally_paid = :totally_paid WHERE id = :id",
                       shares=indicate[0]["shares"]+int(request.form.get("shares")),
                       totally_paid=indicate[0]["totally_paid"]+int(shares)*(quote["price"]),
                       id=session["user_id"])

        db.execute("UPDATE users SET cash = :value WHERE id = :idd ",
                   value=round(rows[0]["cash"]) - total_price, idd=session["user_id"])
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


##########################################################################################################################################################################

@app.route("/check", methods=["GET"])
def check(stock, shares):
    """Return true if username available, else false, in JSON format"""

    return jsonify("TODO")

#####################################################################################################
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute("SELECT * FROM portfolio WHERE id = :id", id=session["user_id"])
    return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

##################################################################################################################################
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("INVALID", 400)

        quote = lookup(request.form.get("symbol"))

        # Invalid input
        if not quote:
            return apology("Doesn't exsist", 400)

        return render_template("dquote.html", row=quote)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

#################################################################################################################################
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Missing username!", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Missing password", 400)

        # Ensure Password is equal to the confirmed one
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("Invalid Password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Ensure username exists
        if len(rows) == 1:
            return apology("repeated username", 400)

        hashed = generate_password_hash(request.form.get("password"))

        db.execute("INSERT INTO users(username, hash) VALUES (:username, :hashedd)",
                   username=request.form.get("username"), hashedd=hashed)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    rows1 = db.execute("SELECT * FROM indication WHERE id = :id", id=session["user_id"])
    rows2 = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    if request.method == "POST":

        indicate = db.execute("SELECT * FROM indication WHERE stock = :stock and id = :id",
                              stock=request.form.get("symbol"), id=session["user_id"])
        # Detect errors for empty list
        if len(indicate) != 1:
            return apology("YOU DIDN'T BUY ANY STOCKS", 400)

        # Detect errors for invalid stocks
        if request.form.get("symbol") != indicate[0]["stock"] or not request.form.get("symbol") or request.form.get("symbol") == 0:
            return apology("YOU DON'T OWN THAT STOCK", 400)

        if not (request.form.get("shares")).isnumeric() or not round(float(request.form.get("shares"))) or round(float(request.form.get("shares"))) <= 0:
            return apology("INVALID INPUT", 400)

        # Detect errors for invalid shares
        if int(request.form.get("shares")) > int(indicate[0]["shares"]):
            return apology("you don't have enough shares", 400)

        quote = lookup(request.form.get("symbol"))

        # UPDATE Portfolio table
        db.execute("INSERT INTO portfolio (stock, price, time, id, shares, status) VALUES (:stock, :total_price, :time, :idd, :sharess, :status)",
                   stock=request.form.get("symbol"),
                   total_price=int(request.form.get("shares"))*(quote["price"]),
                   time=time.asctime(time.localtime(time.time())),
                   idd=session["user_id"],
                   sharess=int(request.form.get("shares")),
                   status="sell")

        db.execute("UPDATE indication set shares = :sharess, totally_sold = :totally_sold , totally_paid = :totally_paid WHERE id = :id and stock = :stock",
                   sharess=indicate[0]["shares"]-int(request.form.get("shares")),
                   totally_sold=int(request.form.get("shares"))*(quote["price"]),
                   totally_paid=indicate[0]["totally_paid"] - int(request.form.get("shares"))*(quote["price"]),
                   id=session["user_id"],
                   stock=request.form.get("symbol"))

        if indicate[0]["shares"]-int(request.form.get("shares")) == 0:
            db.execute("DELETE FROM indication WHERE  stock = :stock", stock=request.form.get("symbol"))

        db.execute("UPDATE users SET cash = :value WHERE id = :idd ",
                   value=rows2[0]["cash"] + int(request.form.get("shares"))*(quote["price"]),
                   idd=session["user_id"])

        return redirect("/")
    else:
        return render_template("sell.html", rows=rows1)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
