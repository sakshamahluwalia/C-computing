#include <stdio.h>
#include <stdlib.h>
// Add your other system includes here.

#include "ptree.h"

// Defining the constants described in ptree.h
const unsigned int MAX_PATH_LENGTH = 1024;

// If TEST is defined (see the Makefile), will look in the tests 
// directory for PIDs, instead of /proc.
#ifdef TEST
    const char *PROC_ROOT = "tests";
#else
    const char *PROC_ROOT = "/proc";
#endif

char* get_name_of_process(char* path); 
struct TreeNode* make_tree(pid_t pid);
int get_siblings(const char* path, pid_t pid, struct TreeNode **root);
void print_ptree_helper(struct TreeNode *root, int max_depth, int curr_depth);

/*
 * Creates a PTree rooted at the process pid.
 * The function returns 0 if the tree was created successfully 
 * and 1 if the tree could not be created or if at least
 * one PID was encountered that could not be found or was not an 
 * executing process.
 */
int generate_ptree(struct TreeNode **root, pid_t pid) {
    // Here's a way to generate a string representing the name of
    // a file to open. Note that it uses the PROC_ROOT variable.
    char procfile[MAX_PATH_LENGTH + 1];
    if (sprintf(procfile, "%s/%d/exe", PROC_ROOT, pid) < 0) {
        fprintf(stderr, "sprintf failed to produce a filename\n");
        return 1;
    } 
    else {
        sprintf(procfile, "%s/%d", PROC_ROOT, pid);
        if (!get_siblings(PROC_ROOT, pid, root))
        {
            return 0;
        } else {
            return 2;
        }
    }
    // The line here should be a function call to retrive the name of a procss.
    // You will want to remove this line eventually since this 
    // function should not print anything. 
}

/*
 * Prints the TreeNodes encountered on a preorder traversal of an PTree
 * to a specified maximum depth. If the maximum depth is 0, then the 
 * entire tree is printed.
 */
void print_ptree(struct TreeNode *root, int max_depth) {
    print_ptree_helper(root, max_depth, 0);
}


// Helper Functions start here
char* get_name_of_process(char* path) {
    // The next two lines are putting together the path of the cmdline file.
    char name[MAX_PATH_LENGTH + 1];
    sprintf(name, "%s/cmdline", path);

    char* filename = malloc(sizeof(MAX_PATH_LENGTH + 1));

    FILE *to_open = fopen(name, "r");
    if (to_open == NULL) 
    {
        fprintf(stderr, "Cannot open file\n");
        exit(1);
    }
    fscanf(to_open, "%s", filename);
    if (fclose(to_open))
    {
        printf("Error closing the file");
        exit(1);
    }
    return filename;
}

int get_siblings(const char* path, pid_t pid, struct TreeNode **root) {
    char name[MAX_PATH_LENGTH + 1];
    int* id = malloc(sizeof(int *));
    if (sprintf(name, "%s/%d/task/%d/children", path, pid, pid) < 0)
    {
        fprintf(stderr, "sprintf failed to produce a filename\n");
        exit(1);
    }

    FILE *to_open = fopen(name, "r");
    if (to_open == NULL) 
    {
        fprintf(stderr, "Cannot open file\n");
        exit(1);
    }
    *root = make_tree(pid);
    while (fscanf(to_open, "%d", id) != EOF)
    {
        if (!((*root)->child))
        {   
            ((*root)->child) = make_tree(*id);
            get_siblings(path, *id, &(*root)->child);
        } else {
            if (((*root)->child->sibling))
            {
                struct TreeNode* obj = (*root)->child;
                while ((obj->sibling)) {
                    obj = obj->sibling;
                }
                (obj->sibling) = make_tree(*id);
                get_siblings(path, *id, &(obj->sibling));
            }
            else {
                ((*root)->child->sibling) = make_tree(*id);
                get_siblings(path, *id, &((*root)->child->sibling));
            }
        }
    }
    if (fclose(to_open))
    {
        printf("Error closing the file");
        exit(1);
    }
    return 0;
}

struct TreeNode* make_tree(pid_t pid) {
    char procfile[MAX_PATH_LENGTH + 1];
    struct TreeNode* node = malloc(sizeof(struct TreeNode));
    if (sprintf(procfile, "%s/%d", PROC_ROOT, pid) < 0) 
    {
        fprintf(stderr, "sprintf failed to produce a filename\n");
        exit(1);
    }
    char* name = get_name_of_process(procfile);
    node->pid = pid;
    node->name = name;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

void print_ptree_helper(struct TreeNode *root, int max_depth, int curr_depth) {
    if (curr_depth <= max_depth || max_depth == 0)
    {
        printf("%*s", curr_depth * 2, "");
        printf("%d: %s\n", root->pid, root->name);  
        if (root->child)
        {   
            print_ptree_helper(root->child, max_depth, ++curr_depth);
            if (root->sibling)
            {   
                print_ptree_helper(root->sibling, max_depth, --curr_depth);
            }
        } 
        else {
            if (root->sibling)
            {   
                print_ptree_helper(root->sibling, max_depth, curr_depth);
            }
        }
    }
}