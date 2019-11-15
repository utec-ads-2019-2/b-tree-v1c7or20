#ifndef NODE_H
#define NODE_H

#include <vector>
#include <algorithm>

using namespace std;

template <class A>
class Compare;


template <typename A>
class BTree;

template <class B>
class CompareKeys;

template <typename T>
class Node {
    unsigned int size;
    unsigned int numberKeys;
    unsigned int numberChilds;
    vector<T> keys;
    vector<Node<T>*> childs;
    bool isLeaf;
    Compare<T> compare;
    CompareKeys<T> compareInt;

    public: 
        Node(unsigned int size, bool isLeaf = true) : size(size), isLeaf(isLeaf) {
            numberChilds = numberKeys = 0;
            keys.resize(size - 1);
            childs.resize(size);
        }

        void insertData(T data){
            if (numberKeys < size-1)
                keys[numberKeys] = (data);
            else
                keys.push_back(data);
            numberKeys++;
            sort(keys.begin(),keys.end(), compareInt);
        }

        void insertChild(Node<T>* toInsert){
            if (numberChilds>=size){
                childs.resize(size+1);
                childs[numberChilds]=(toInsert);
                numberChilds++;
            }else if (toInsert != nullptr){
                childs[numberChilds] = toInsert;
                numberChilds++;
            }
            sort(childs.begin(),childs.end(),compare);
        }

        void deleteChild(int i){
            this->childs[i] = nullptr;
            numberChilds--;
            sort(childs.begin(),childs.end(),compare);
        }
        /**
         * An alternative is to create two different nodes (Internal and Leaf) that inherite from Node 
         * an implement this function
         */
        //virtual bool isLeaf() = 0;

    friend class BTree<T>;
    friend class Compare<T>;
};

template <class A>
class Compare{
public:
    bool operator()(Node<A> *first, Node<A> *second){
        if (first != nullptr and second!= nullptr)
            return first->keys[0]<second->keys[0];
        else return first != nullptr;
    }
};

template <class B>
class CompareKeys{
public:
    bool operator()(B first, B second){
        if (first != 0 and second != 0)
            return first < second;
        else return first != 0;
    }
};

#endif