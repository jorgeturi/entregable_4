
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************************************************/
/*                       NOMENCLATURAS                        */
/**************************************************************/
/**
 * BT - Binary Tree: Árbol binario.
 * BTN - binary tree node: nodo de árbol binario.
 * SBT - Search Binary Tree: ABB - Árbol binario de búsqueda.
 * AVL - AVL Tree: Árbol AVL.
 * root: nodo raíz del árbol.
 * parent node: nodo padre.
 * child node: nodo hijo.
 * internal node,
 * inner node,
 * inode,
 * branch node: nodo interno, que tiene hijos.
 * external node,
 * leaf node,
 * outer node,
 * terminal node: nodo hoja de un árbol.
 */
/**************************************************************/

#include "arbolb.h"
/**************************************************************/
/*                     ÁRBOLES BINARIOS                       */
/**************************************************************/

/**
 * Crea un nodo de un BTN en base a un valor t_elem_btree
 */
btn* btn_new(t_elem_btree value)
{
    btn* nuevo = malloc (sizeof(btn));
    nuevo->value = value;
    nuevo->left = NULL;
    nuevo->right = NULL;

    return nuevo;
}

/**
 * Elimina un nodo, si tiene hijos elimina sus hijos también.
 *
*/

void btn_free(btn** node)
{

    if(btn_isLeaf(*node))
    {
        free(*node);
        return;
    }

    if((*node)->left != NULL)       ///si a donde apunta nodo tiene algo a la izq
    {
        btn_free(&(*node)->left);   ///llamo a liberar, si es una hoja, libera
        (*node)->left = NULL;       ///a donde apuntaba lo libere, asi que asigno NULL
        btn_free(&(*node));         ///veo si ahora donde apunta node, se formo una hoja para volver a otra capa
    }
    if((*node)->right != NULL)      /// "" a la der
    {
        btn_free(&(*node)->right);
        (*node)->right = NULL;      ///asigno NULL
        btn_free(&(*node));
    }

    return;
}



/**
 * Devuelve -1 si el primero es menor, 1 si es mayor, 0 si es igual. Todo con respecto al segundo
 * Función auxiliar utilizada en find.
 */
int _cmp(t_elem_btree a, t_elem_btree b)
{
    return (a > b) ? 1 : (a < b) ? -1 : 0;
}

/**
 * Busca un nodo con un determinado elemento y devuelve su referencia
 * Se busca el nodo en pre-order (debe recorrer todo el árbol no hay un criterio de ordenamiento)
 * Debe devolver la referencia a la ubicación del puntero al nodo. Si no existe, devuelve NULL
 */
btn** btn_find(btn** node, t_elem_btree value, int cmp(t_elem_btree, t_elem_btree))
{
    btn** referencia = NULL;
    if(*node == NULL){
        return NULL;
    }


    if(*node != NULL)
    {
        int is_the_value = cmp(value, (*node)->value);  ///comparo con el nodo
        if(is_the_value)
        {
            referencia = node;
            return referencia;
        }

        referencia = btn_find(&(*node)->left, value, cmp);///llamo por izq
        if(referencia != NULL)                            ///de volver algo no nulo es que lo encontre
        {
            return referencia;
        }
        referencia = btn_find(&(*node)->right, value, cmp);///idem derecha
        if(referencia != NULL)
        {
            return referencia;
        }
    }

    return referencia;
}

/**
 * Devuelve 1 si el nodo es una hoja.
 * Devuelve 0 si no es una hoja.
 */
int btn_isLeaf(btn *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        return 1;
    }
    return 0;
}

/**
 * Cuenta la cantidad de nodos de un árbol binario.
 */
int btn_count(btn *node)
{
    int result = 0;
    if (node != NULL)
    {
        result = 1 + btn_count(node->left) + btn_count(node->right);
    }
    return result;
}

/**
 * Agrega un nodo en un árbol binario con el siguiente criterio:
 * - Si el subárbol es nulo se agrega ahí,
 * - Si no es NULL lo agrega en el hijo con menor cantidad de nodos,
 * - Si sus hijos tienen la misma cantidad de nodos lo agrega a la izquierda.
 */
int btn_insert(btn** node, btn *newNode)
{
    if((*node) == NULL)
    {
        (*node) = newNode;
    }

    btn* nodo_original = *node;

    int hijoiz = btn_count((*node)->left);
    int hijode = btn_count((*node)->right);

    if( hijode < hijoiz)
    {

        while( (*node)->right != NULL)
        {
            (*node) = (*node)->right;
        }
        (*node)->right = newNode;

    }
    else
    {
        while( (*node)->left != NULL)
        {
            (*node) = (*node)->left;
        }
        (*node)->left = newNode;
    }

    *node = nodo_original;

    return 1;
}

/**
 * Agrega un valor a un BT con el criterio:
 * - Si el subárbol es nulo se agrega ahí,
 * - Si no es NULL lo agrega en el hijo con menor cantidad de nodos,
 * - Si sus hijos tienen la misma cantidad de nodos lo agrega a la izquierda.
 */
int btn_insert_value(btn **node, int value)
{
    int pude = 0;

    if((*node) == NULL)
    {
        return pude;
    }

    btn* nodo_original = *node;

    int hijoiz = btn_count((*node)->left);
    int hijode = btn_count((*node)->right);

    if( hijode < hijoiz)
    {

        while( (*node)->right != NULL)
        {
            (*node) = (*node)->right;
        }
        (*node)->right->value = value;

    }
    else
    {
        while( (*node)->left != NULL)
        {
            (*node) = (*node)->left;
        }
        (*node)->left->value = value;
    }

    pude = 1;
    *node = nodo_original;
    return pude;
}


/**
 * Determinar el nivel de un nodo.
 * - Recibe como entrada la raíz, un valor y una función de comparación de valores.
 */

int son_iguales(t_elem_btree elem1, t_elem_btree elem2)
{
    return(elem1 == elem2)? 1 : 0;
}

/*
void _btn_level(btn **node, t_elem_btree value, int cmp(t_elem_btree, t_elem_btree), int* level_actual, int* corte)
{
    while (*corte == 0){

    if (node == NULL){
        *level_actual = *level_actual-1;
        return -1;
    }
    printf("LEVEL ACTUAL %d\n", *level_actual);
    printf("viendo %d\n", (*node)->value);

    if (cmp(value, (*node)->value) == 1){
        *corte = 1;
        printf("ENTRE");
        return *level_actual;
    }


        *node = (*node)->left;
        _btn_level( node,value,cmp,level_actual, corte);

        if (*corte == 1){

        }
         *level_actual = *level_actual + 1;
        *node = (*node)->right;
          _btn_level(node,value,cmp,level_actual, corte);
         if (*corte == 1){
        }

    }
    ///btn_postorder(*node, , nivel)

   ///IDEA
}
*/
void buscar_y_contar(btn* node, int*variables)
{

    if(node == NULL)
    {
        printf("es nulo\n");
    }



    if (variables[3] != 1)
    {
        if(node != NULL)
        {
            variables[1] = variables[1] + 1;
        }
        if(node == NULL)
        {
            variables[1] = variables[1] - 1;
        }
        printf("veo que hay %d y comparo con %d\n", node->value, variables[0]);
        if(node->value == variables[0])
        {
            variables[2] = variables[1];
            variables[3] = 1;
        }
    }
}



void _btn_level(btn *node, int*variables)
{

    if (node == NULL)
    {
        return;
    }
    if (btn_isLeaf(node)){
        variables[1] = variables[1] - 1;
    }

    if (variables[2] != 1)
    {

            printf("veo que hay %d y comparo con %d, nivel %d, okey %d\n", node->value, variables[0], variables[1], variables[2]);

            if(node->value == variables[0])
            {
                variables[2] = 1;
                variables[3] = variables[1];
                return;
            }

            variables[1] = variables[1] + 1;

            _btn_level(node->right, variables);
            variables[1] = 0 ;
            if(node->left != NULL){
               variables[1] = variables[1] + 1;
            }
            _btn_level(node->left, variables);



    }



}

int btn_level(btn* root, t_elem_btree value, int cmp(t_elem_btree, t_elem_btree))
{
    int nivel = -1;
    btn** valor = btn_find(&root, value, son_iguales);
    printf("valor esta %x y apunta a %x", valor, *valor);
    if (*valor != NULL){
        nivel = 0;
    }

    return nivel;
}


/**
 * Devuelve el valor máximo entre 2 enteros.
 * Función auxiliar utilizada en height.
 */
int _max(int a, int b)
{
    return (a > b) ? a : b;
}



/**
 * Devuelve la altura de un BTN
 */
int btn_height(btn *node)    ///CAMBIE LA DEFINICION, POR SI T_ELEM DEJA DE SER UN INT
{

    if (node == NULL)
    {
        return -1;
    }
    int izq = btn_height(node->left); ///me busca el max por izq
    int der = btn_height(node->right);

    return (izq >= der) ? izq + 1 : der +1;

}


/**
 * Recorrido de un BT en inorden
 *
 */
void btn_inorder(btn *node, void btn_do(btn*, void*), void* ctx)
{
    if (!node) return;

    btn_inorder(node->left, btn_do, ctx);
    btn_do(node, ctx);
    btn_inorder(node->right, btn_do, ctx);

}

void btn_print_int(btn* node, void* algo)
{
    printf("%d \n", node->value);
}

/**
 * Recorrido de un BT en postorder
 */
void btn_postorder(btn *node, void btn_do(btn*, void*), void* ctx)
{
    if (!node) return;


    btn_postorder(node->left, btn_do, ctx);
    btn_postorder(node->right, btn_do, ctx);
    btn_do(node, ctx);

}

/**
 * Recorrido de un BT en preorder
 */
void btn_preorder(btn *node, void btn_do(btn*, void*), void* ctx)
{
    if (!node) return;

    btn_do(node, ctx);
    btn_preorder(node->left, btn_do, ctx);
    btn_preorder(node->right, btn_do, ctx);

}


/**************************************************************/
/*                         ADICIONALES                        */
/**************************************************************/

/**
 * DE USO INTERNO para dibujar un árbol.
 */
int _btn_print(btn *tree, int is_left, int offset, int depth, char s[20][255], void toStr (btn*, char*))
{
    char b[200];
    int width = 5;

    if (!tree) return 0;
    toStr(tree, b);
    //sprintf(b, "%s", str);


    int left = _btn_print(tree->left, 1, offset, depth + 1, s, toStr);
    int right = _btn_print(tree->right, 0, offset + left + width, depth + 1, s, toStr);

    // for (int i = 0; i < width; i++) s[2 * depth][offset + left + i] = b[i];
    for (int i = 0; i < strlen(b); i++) s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left)
    {
        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

    }
    else if (depth && !is_left)
    {
        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }

    return left + width + right;
}

/**
 * Dibuja un árbol binario con caracteres
 * (Los valores de los nodos deben estar entre 0 y 999).
 */
void btn_print(btn *tree, void toStr (btn*, char*))
{
    char s[40][255];
    for (int i = 0; i < 20; i++) sprintf(s[i], "%80s", " ");

    _btn_print(tree, 0, 0, 0, s, toStr);

    for (int i = 0; i < 20; i++)
    {
        int j = 0;
        while (s[i][j] != '\0' && s[i][j] == ' ')
        {
            j++;
        }
        if (s[i][j] != '\0')
        {
            printf("%s\n", s[i]);
        }
    }
}

void intToStr(btn* node, char* str)
{
    sprintf(str, "%d %d", node->value->minute, node->value->temperature); // Usamos sprintf para convertir el entero a una cadena
}
