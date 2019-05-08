/**
 * Copyright (c) 2019 Anatolii Kurotych
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "binarytree.h"

BinaryTree::BinaryTree()
{

}

Node * BinaryTree::delete_tree_r(struct Node ** tree) // Рекурсивное удаление всех элементов дерева ( проходим по всем элементам и удаляем их )
{
    if (*tree != NULL)
    {
        struct Node *tmp = *tree;
        tmp->left = delete_tree_r(&((*tree)->left)); // Движемся до конца в левый элемент
        tmp->right = delete_tree_r(&((*tree)->right)); // при возврате с конца левого элемента заходим в правые поддеревья и двигаемся в них до конца влево
        free(tmp); *tree = NULL; return (tmp); // Удаляем элемент
    }
    return nullptr;
}




Node * BinaryTree::search_insert_r(struct Node ** root, const int d)
{
    struct Node * pnew = NULL;
    if (!(*root))
    {
        pnew = (struct Node *)malloc(sizeof(struct Node));
        pnew->d = d;
        pnew->left = pnew->right = NULL;
        *root = pnew;
    }
    else
    {
        if ((*root)->d == d) {
            QMessageBox::information(0, "Внимание!", "Данный элемент уже находится в дереве.");
            return ((*root));
        }
        if (d < (*root)->d) search_insert_r(&((*root)->left), d);
        if (d >(*root)->d) search_insert_r(&((*root)->right), d);
    }
    return (pnew);
}

void BinaryTree::print_tree(const struct Node * root, std::string st) // Рекурсивный обход дерева с выводом результата в контейнер
{

    std::string str = st;
    if (root)
    {
        results[str] = root->d; // Записываем значение в контейнер
        str.append("L");
        print_tree(root->left, str);
        str.erase(str.end() - 1);
        str.append("R");
        print_tree(root->right, str);
    }
    else if(str.length()) str.erase(str.end() - 1);
}


bool BinaryTree::delete_node(struct Node ** root, const int d)
{
    int found = 0;
    struct Node * pv = *root, *prev = NULL;
    l_r way = no_move;

    while (pv && !found) // ищем элемент который хотим удалить
    {
        if (d == pv->d) { found = 1; }
        else if (d < pv->d) // Если значение которое мы ищем меньше нужного двигаемся в лево
        {
            prev = pv;
            pv = pv->left;
            way = mLeft;
        }
        else // Иначе двигаемся вправо
        {
            prev = pv;
            pv = pv->right;
            way = mRight;
        }
    }

    if (found) // если элемент для удаления найден:
    {
        if (pv->left == NULL && pv->right == NULL) //Удаление элемента без "детей"
        {
            free(pv); pv = NULL;
            if (way == mLeft)     prev->left = NULL;
            else if (way == mRight)    prev->right = NULL;
            else    *root = NULL;
        }
        else if (pv->right == NULL) //Удаление элемента у котора есть ребенок с лева
        {
            if (way == mLeft)    prev->left = pv->left;
            else if (way == mRight)   prev->right = pv->left;
            else    *root = pv->left;
            free(pv);
        }
        else if (pv->left == NULL) //Удаление элемента у котора есть ребенок с права
        {
            if (way == mLeft)  prev->left = pv->right;
            else if (way == mRight) prev->right = pv->right;
            else    *root = pv->right;
            free(pv);
        }
        else  // удаление узла с двумя ребенками
        {
            struct Node * ptmp = NULL;
            prev = ptmp = pv->right; // идем к правому ребенку
            while (ptmp->left) // Дальше двигаемся в упор в лево
            {
                prev = ptmp;
                ptmp = ptmp->left;
            }
            pv->d = ptmp->d; // ставим значение найденого элемента, на место удаленного

            prev->left = ptmp->right; //Если у элемента который стает на место удаленного есть правый предок, ставим его на место найденого

            if ((ptmp == prev))
            {
                if (!prev->right) // "отвязываем" указатель на правый элемент если за ним ничего дальше нет
                {
                    pv->right = NULL;
                }
                else
                {
                    pv->right = prev->right; // а вот если за ним что-то есть, перепривязываем на следующий элемент
                }
            }

            free(ptmp);

        }
        return (true);
    }
    return (false);
}
