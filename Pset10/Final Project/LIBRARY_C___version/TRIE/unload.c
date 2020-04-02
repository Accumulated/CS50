// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *last_before_stack = NULL;
    int i = 0;

    // looping over the root its self
    for (i = 0; i < N ; i++)
    {
        if (ptr -> children[i] == NULL);
        else
        {
            last_before_stack = ptr;
            ptr = ptr -> children[i];

            unload();
            ptr = last_before_stack;
        }
    }
    if (i == 27)
    {
        free(ptr);
        return true;
    }
    return false;
}
