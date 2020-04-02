// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (LOAD_FLAG == true)
    {
        return SIZE;
    }
    return 0;
}