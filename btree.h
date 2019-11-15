#ifndef BTREE_H
#define BTREE_H

#include "node.h"
#include <cmath>
#include <algorithm>

template <typename T>
class BTree {
    private:
        Node<T>* root;
        unsigned int degree;
        unsigned int minimChilds;
        unsigned int maxKeys;
        unsigned int control;
        bool isOdd(){
            return degree%2==1;
        }
    public:
        BTree(unsigned int degree) : degree(degree), root(nullptr) {
            minimChilds = ceil(double(degree)/2);
            maxKeys = degree-1; control = 0;
        }

        bool search(T data) {

            return false;
        }
        void checkProperties(Node<T>* nodeBefore,Node<T>* nodeToLook){
            if (nodeToLook->numberKeys > degree-1){
                if (nodeBefore == nodeToLook){
                    nodeBefore = nullptr;
                    nodeBefore = new Node<T>(degree);
                    root = nodeBefore;
                } else{
                    for (int i = 0; i < nodeBefore->numberChilds ; ++i) {
                        if(nodeToLook == nodeBefore->childs[i]){
                            nodeBefore->deleteChild(i);
                            break;
                        }
                    }
                }
                vector<Node<T>*> nodesToUp;
                if (isOdd()){
                    for (int i = 0; i < nodeToLook->numberKeys; ++i) {
                        if (i%2 == 1){
                            nodeBefore->insertData(nodeToLook->keys[i]);
                        }else{
                            Node<T>* oneElementNode = new Node<T>(degree);
                            oneElementNode->insertData(nodeToLook->keys[i]);
                            oneElementNode->insertChild(nodeToLook->childs[i]);
                            if(i+1<nodeToLook->numberChilds){
                                oneElementNode->insertChild(nodeToLook->childs[i+1]);
                            }
                            nodesToUp.push_back(oneElementNode);
                        }
                    }
                } else{
                    Node<T>* twoElementNode = new Node<T>(degree);
                    twoElementNode->insertData(nodeToLook->keys[0]);
                    twoElementNode->insertData(nodeToLook->keys[1]);
                    twoElementNode->insertChild(nodeToLook->childs[0]);
                    twoElementNode->insertChild(nodeToLook->childs[1]);
                    twoElementNode->insertChild(nodeToLook->childs[2]);
                    nodesToUp.push_back(twoElementNode);
                    for (int i = 2; i < nodeToLook->numberKeys; ++i) {
                        if (i%2 == 0){
                            nodeBefore->insertData(nodeToLook->keys[i]);
                        }else{
                            Node<T>* oneElementNode = new Node<T>(degree);
                            oneElementNode->insertData(nodeToLook->keys[i]);
                            oneElementNode->insertChild(nodeToLook->childs[i]);
                            if(i+1<nodeToLook->numberChilds){
                                oneElementNode->insertChild(nodeToLook->childs[i+1]);
                            }
                            nodesToUp.push_back(oneElementNode);
                        }
                    }
                }
                for (auto nodes = nodesToUp.begin(); nodes != nodesToUp.end() ; ++nodes) {
                    nodeBefore->insertChild(*nodes);
                }
            }
        }

        void insertDataAfterRoot(Node<T>* nodeToLook,Node<T>* nodeBefore,T data){
            Node<T>* nodeBeforeThis = nodeToLook;
            if (nodeToLook->numberChilds>0){
                    if (data < nodeToLook->keys[0]){
                    nodeToLook = nodeToLook->childs[0];
                }else{
                    int atChild;
                    for (atChild = 1; atChild < nodeToLook->numberChilds-1 ; ++atChild) {
                        if (nodeToLook->keys[atChild-1] < data and data < nodeToLook->keys[atChild]){
                            break;
                        } else{
                            continue;
                        }
                    }
                    nodeToLook = nodeToLook->childs[atChild];
                    }
               insertDataAfterRoot(nodeToLook,nodeBeforeThis,data);
            } else{
                nodeToLook->insertData(data);
            }
            if (control != 1){
                checkProperties(nodeBefore,nodeToLook);
            }
            control++;
        }


        void insertDataAfterRoot(Node<T>* nodeToLook,T data){
            Node<T>* nodeBefore = nodeToLook;
            if (nodeToLook->numberChilds>0){
                if (data < nodeToLook->keys[0]){
                    nodeToLook = nodeToLook->childs[0];
                }else{
                    int atChild;
                    for (atChild = 1; atChild < nodeToLook->numberChilds-1 ; ++atChild) {
                        if (nodeToLook->keys[atChild-1] < data and data < nodeToLook->keys[atChild]){
                            break;
                        }
                    }
                    nodeToLook = nodeToLook->childs[atChild];
                }
                insertDataAfterRoot(nodeToLook,nodeBefore,data);
            } else{
                nodeToLook->insertData(data);
            }
                checkProperties(nodeBefore,root);
            control++;
        }

        bool insert(T data) {
            if(root == nullptr){
                root = new Node<T>(degree);
                root->insertData(data);
            } else{
                control = 0;
                insertDataAfterRoot(root,data);
            }
        }

        bool remove(int k) {

            return true;
        }

        void print() {
            // TODO
        }

        ~BTree(){

        }
};

#endif