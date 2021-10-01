#include "parser.h"



void next_token(void) {
    printf("CURRENT: %s\n", parser.current_token->contents);
    parser.current_token = parser.peek_token;
    parser.peek_token++;
}


bool check_token(token_type_t type) {
    return parser.current_token->type == type;
}


bool check_peek(token_type_t type) {
    return parser.peek_token->type == type;
}


bool match(token_type_t type) {
    if (!check_token(type)) {
        printf("ERROR: got %s. expected %s \n", hash_token_type(parser.current_token->type), \
        hash_token_type(type));
        return false;
    }
    next_token();
}



// node_t *root = NULL; 


// void tree_insert(token_t *token ) {
    
//     node_t *temp = malloc(sizeof(node_t));
//     node_t *current;
//     node_t *parent;

//     temp->token = token;
//     temp->left = NULL;
//     temp->right = NULL;

//     if (root == NULL) {
//         root = temp;
//     }
//     else {
//         current = root;
//         parent = NULL;

//         while(true) {
//             parent = current;

//             if (token->type <= parent->token->type) {
//                 current = current->left;
//                 if (current == NULL) {
//                     parent->left = temp;
//                     // printf("add left [%s\t%s]\n", hash_token_type(parent->left->token->type), temp->token->contents);
//                     return;
//                 }
//             }
//             else {
//                 current = current->right;
//                 if (current == NULL) {
//                     parent->right = temp;
//                     // printf("add right [%s\t%s]\n", hash_token_type(parent->right->token->type), temp->token->contents);
//                     return;
//                 }
//             }
//         }
//     }
// }


// void pre_order_traversal(node_t *node) {
//     if (node == NULL)
//         return;
//     printf("[%-20s %-20d %s]\n", hash_token_type(node->token->type), node->token->type, node->token->contents);
//     pre_order_traversal(node->left);
//     pre_order_traversal(node->right);
// }


// void in_order_traversal(node_t *node) {
//     if (node == NULL)
//         return;
//     in_order_traversal(node->left);
//     printf("[%-20s %-20d %s]\n", hash_token_type(node->token->type), node->token->type, node->token->contents);
//     in_order_traversal(node->right);
// }


// void post_order_traversal(node_t *node) {
//     if (node == NULL)
//         return;
//     post_order_traversal(node->left);
//     post_order_traversal(node->right);
//     printf("[%-20s %-20d %s]\n", hash_token_type(node->token->type), node->token->type, node->token->contents);

// }


// int _print_t(node_t *tree, int is_left, int offset, int depth, char s[20][255])
// {
//     char b[20];
//     int width = 3;

//     if (!tree) return 0;

//     //sprintf(b, "%03s", hash_token_type(tree->token->type));

//     int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
//     int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

// #ifdef COMPACT
//     for (int i = 0; i < width; i++)
//         s[depth][offset + left + i] = b[i];

//     if (depth && is_left) {

//         for (int i = 0; i < width + right; i++)
//             s[depth - 1][offset + left + width/2 + i] = '-';

//         s[depth - 1][offset + left + width/2] = '.';

//     } else if (depth && !is_left) {

//         for (int i = 0; i < left + width; i++)
//             s[depth - 1][offset - width/2 + i] = '-';

//         s[depth - 1][offset + left + width/2] = '.';
//     }
// #else
//     for (int i = 0; i < width; i++)
//         s[2 * depth][offset + left + i] = b[i];

//     if (depth && is_left) {

//         for (int i = 0; i < width + right; i++)
//             s[2 * depth - 1][offset + left + width/2 + i] = '-';

//         s[2 * depth - 1][offset + left + width/2] = '+';
//         s[2 * depth - 1][offset + left + width + right + width/2] = '+';

//     } else if (depth && !is_left) {

//         for (int i = 0; i < left + width; i++)
//             s[2 * depth - 1][offset - width/2 + i] = '-';

//         s[2 * depth - 1][offset + left + width/2] = '+';
//         s[2 * depth - 1][offset - width/2 - 1] = '+';
//     }
// #endif

//     return left + width + right;
// }

// void print_t(node_t *tree) {
//     char s[20][255];
//     for (int i = 0; i < 20; i++)
//         sprintf(s[i], "%80s", " ");

//     _print_t(tree, 0, 0, 0, s);

//     for (int i = 0; i < 20; i++)
//         printf("%s\n", s[i]);
// }