#ifndef ARBOLB_H_INCLUDED
#define ARBOLB_H_INCLUDED

#include "reading.h"
#define t_elem_btree reading*

typedef struct _btn {
    t_elem_btree value;
    struct _btn *left;
    struct _btn *right;
} btn;

btn* btn_new(t_elem_btree value);
void btn_free(btn** node);
void _btn_free(btn** node);
int _cmp(t_elem_btree a, t_elem_btree b);
btn** btn_find(btn** node, t_elem_btree value, int cmp(t_elem_btree, t_elem_btree));
int btn_isLeaf(btn *node);
int btn_count(btn *node);
int btn_insert(btn** node, btn *newNode);///
int btn_insert_value(btn **node, int value);///
int btn_level(btn* root, t_elem_btree value, int cmp(t_elem_btree, t_elem_btree));
int _max(int a, int b);///
int btn_height(btn *node);
void btn_inorder(btn *node, void btn_do(btn*, void*), void* ctx);
void btn_postorder(btn *node, void btn_do(btn*, void*), void* ctx);
void btn_preorder(btn *node, void btn_do(btn*, void*), void* ctx);
int _btn_print(btn *tree, int is_left, int offset, int depth, char s[20][255], void toStr (btn*, char*));///
void btn_print(btn *tree, void toStr (btn*, char*));///
int son_iguales(t_elem_btree elem1, t_elem_btree elem2);
void intToStr(btn* node, char* str);


#endif // ARBOLB_H_INCLUDED
