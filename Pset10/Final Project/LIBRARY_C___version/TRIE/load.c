// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // Restart for every word from the top of the root
        ptr = root;

        // loop to assign the new word in trie
        for (int j = 0; word[j] != '\0'; j++)
        {
            // tmp to store the chars index
            int tmp = 0;

            // checking for '\'' char
            word[j] == '\'' ? (tmp = word[j] - 13) : (tmp = word[j] - 97);

            // first time in the array's index (tmp)
            if (ptr -> children[tmp] == NULL)
            {
                ptr -> children[tmp] = malloc(sizeof(node));

                if (!(ptr -> children[tmp]))
                {
                    printf("error allocating NEWNODE \n");
                    return false;
                }


                // Initializing all indeces to NULL and is_word to false by default
                ptr -> children[tmp] -> is_word = false;
                for (int k = 0; k < N; k++)
                {
                    ptr -> children[tmp] -> children[k] = NULL;
                }

                ptr = ptr -> children [tmp];
            }

            // if an address already existed in this index (i.e. tmp)
            else
            {
                // exsist node now assigned to ptr
                ptr = ptr -> children[tmp];
            }
        }
        ptr -> is_word = true;
        SIZE++;
    }

    // Close dictionary
    fclose(file);
	printf("LOAD IS A SUCCESS \n");
    LOAD_FLAG = true;
    // Indicate success
    return true;
}