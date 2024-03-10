/* (c) Larry Herman, 2023.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

/* DO NOT MODIFY THIS FILE OR YOUR CODE WILL NOT COMPILE ON THE SUBMIT
 * SERVER. */

/* This function takes as parameters two arrays of pointers to
 * dynamically-allocated strings (pointers to characters), which must end in
 * NULL, and compares them, returning 1 if they have the same number of
 * elements and the same corresponding elements, and 0 otherwise.  This
 * function facilitates writing tests that call the function get_vertex_list()
 * and want to compare its results against expected results.  The function
 * also returns 1 if both parameters are NULL.  See examples of how it is
 * called in any public tests that use it.
 */
int compare_vertex_lists(char **names, char **expected_names);
