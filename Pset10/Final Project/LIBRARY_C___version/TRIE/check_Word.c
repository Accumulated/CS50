// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Restart from beginning
    int k = 0;
    ptr = root;

    // Buffer for word is a solution for UPPER_CASE PROBLEM 
    while (word[k] != '\0')
    {
        k++;
    }
    char *new_word = malloc(k);


    // To solve the UPPER_CASE problem with out modifing the original word
    for (int n = 0; n < k; n++)
    {
        if (word[n] >= 'A' && word[n] <= 'Z')
        {
            if (word[n] + 32 == tolower(word[n]))
            {
                new_word[n] = (char) tolower((word[n]));
            }
            else
            {
                free(new_word);
                ptr = root;
                return false;
            }

        }
        else
        {
            new_word[n] = word[n];
        }
    }

    // start traversing trie
    for (int j = 0; j < k; j++)
    {
        int tmp = 0;

        // checking for '\'' char
        new_word[j] == '\'' ? (tmp = (new_word[j] - 13)) : (tmp = (new_word[j] - 97));

        // checking for index value
        if (ptr -> children[tmp] == NULL)
        {
            free(new_word);
            ptr = root;
            return false;
        }
        else
        {
            ptr = ptr -> children[tmp];
        }
    }

    // Checking for is_word field in Dictionary
    if (ptr -> is_word == true)
    {
        free(new_word);
        ptr = root;
        return true;
    }

    free(new_word);
    ptr = root;
    return false;
}