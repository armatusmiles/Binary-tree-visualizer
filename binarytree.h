#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <QObject>
#include <QMessageBox>

struct Node
{
    int d;
    struct Node *left;
    struct Node *right;
};

typedef enum { no_move, mLeft, mRight } l_r;

class BinaryTree : public QObject
{
    Q_OBJECT

public:
    std::map<std::string,int> results;
    BinaryTree();
    struct Node *search_insert_r(struct Node **, const int);
    bool   delete_node(struct Node **, const int);
    struct Node *delete_tree_r(struct Node **);
    void        print_tree(const struct Node *, std::string st);
};

#endif // BINARYTREE_H
