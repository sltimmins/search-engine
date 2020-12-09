//
// Created by Kevin Leong on 11/15/20.
//
/**
 * All made by Kevin Leong
 */

#ifndef SEARCH_ENGINE_DSTREE_H
#define SEARCH_ENGINE_DSTREE_H

#include <vector>

template<typename T>

class DSTree {
private:

    /**
     * Tree Node for AVL Tree
     */
    template<typename Type>
    struct TreeNode {
        T payload;

        TreeNode* left;
        TreeNode* right;

        int height;
        bool active;

        /**
        * Constructors
        */

        TreeNode(){
            this->payload = NULL;
            this->left = this->right = nullptr;
            this->height = NULL;
            this->active = true;
        }
        TreeNode(T value){
            this->payload = value;
            this->left = nullptr;
            this->right = nullptr;
            this->height = 0;
            this->active = true;
        }
        TreeNode(T value, TreeNode* left, TreeNode* right){
            this->payload = value;
            this->left = left;
            this->right = right;
            this->active = true;
        }

        /**
        * Copy Constructor
        */
        TreeNode(const TreeNode &copy){
            this->payload = copy.payload;
            this->left = copy.left;
            this->right = copy.right;
            this->height = copy.height;
            this->active = copy.active;
        }

        /**
        *   Destructor
        */
        ~TreeNode() = default;

        /**
        *   Equals Operator
        */
        TreeNode &operator= (const TreeNode *&copy)
        {
            this->payload = copy->payload;
            this->left = copy->left;
            this->right = copy->right;
            this->height = copy->height;
            this->active = copy->active;
        }

        /**
        * Returns Payload and Height
        */
        T getPayload()
        {
            return this->payload;
        }
        int getHeight()
        {
            return this->height;
        }
    };

    /*===================================================================================================*/

    /**
     *  Private Data members for AVL Tree
     */
    TreeNode<T> *root;
    int numNode;

    /**
      * PRIVATE: Recursive insert function
      */
    void insert(T value, TreeNode<T> *&newVal)
    {
        if(newVal == nullptr)
        {
            newVal = new TreeNode<T>(value, nullptr, nullptr);
        } else if(!newVal->active)
        {
            if(newVal->left != nullptr && newVal->right != nullptr){
                newVal->payload = value;
                newVal->active = true;
            } else {
                if(newVal->left != nullptr && newVal->left->payload < value){
                    newVal->payload = value;
                    newVal->active = true;
                } else if(newVal->right != nullptr && newVal->right->payload > value){
                    newVal->payload = value;
                    newVal->active = true;
                }
            }

        }else if(value < newVal->payload)
        {
            //FOR THE ACTIVE
            insert(value, newVal->left);

            if(height(newVal->left) - height(newVal->right) == 2)
            {
                //CASE 1
                if(value < newVal->left->payload)
                {
                    rotateWithLeftChild(newVal);
                } else //CASE 2
                {
                    doubleWithLeftChild(newVal);
                }
            }
        } else if(value > newVal->payload)
        {
            insert(value, newVal->right);

            if(height(newVal->right) - height(newVal->left) == 2)
            {
                //CASE 3
                if(value > newVal->right->payload)
                {
                    rotateWithRightChild(newVal);
                } else //CASE 4
                {
                    doubleWithRightChild(newVal);
                }
            }
        } else;
        newVal->height = max(height(newVal->left),height(newVal->right)) + 1;
    }


    /**
    *   PRIVATE: Recursive remove function
    */
    void remove(T value, TreeNode<T> *node)
    {
        if(node == NULL)
        {
            return;
        } else if(value < node->payload)
        {
            remove(value, node->left);
        } else if(value > node->payload)
        {
            remove (value, node->right);
        } else if(value == node->payload) {
            node->active = false;
            this->numNode--;
        } else;
    }

    /**
    *  Returns the height of the node
    */
    int height(TreeNode<T> *t) const{
        return t == NULL ? -1 : t->height;
    }
    /**
    *   Returns the max between two heights
    */
    int max (int left, int right) const{
        return left > right ? left : right;
    }

    /**
    *   PRIVATE: Recursive delete for destructor
    */
    void del(TreeNode<T> *&deleteNode)
    {
        if(deleteNode->left != nullptr)
        {
            del(deleteNode->left);
        }
        if(deleteNode->right != nullptr)
        {
            del(deleteNode->right);
        }

        delete deleteNode;
        deleteNode = nullptr;
        this->numNode--;
    }

    /**
     * PRIVATE For copy constructor and equals operator
     */
    static TreeNode<T> * copyNode(TreeNode<T> *node){
        if(node != nullptr){
            TreeNode<T>* left = copyNode(node->left);
            TreeNode<T>* right = copyNode(node->right);

            return new TreeNode<T>(node->payload, left, right);
        } else {
            return NULL;
        }
    }

    /**
    *   The next 4 are the rotates for the insert function
    */
    void rotateWithLeftChild(TreeNode<T> *&k2)
    {
        TreeNode<T> *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }
    void doubleWithLeftChild(TreeNode<T> *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void rotateWithRightChild(TreeNode<T> *&k1)
    {
        TreeNode<T> *k2 = k1->right;
        k1->right= k2->left;
        k2->left= k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }
    void doubleWithRightChild(TreeNode<T> *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);

    }

    /**
    *   Goes through the tree and returns a node if found
    *   If not found, it creates a new node and returns it
    *   Also couts an error
    */
    TreeNode<T>* find(T value, TreeNode<T> *node) const{
        TreeNode<T> *returnNode = nullptr;
        if(value < node->payload && node->active)
        {
            if(node->left != nullptr)
            {
                returnNode = find(value, node->left);
            }

        } else if(value > node->payload && node->active)
        {
            if(node->right != nullptr)
            {
                returnNode = find(value, node->right);
            }

        } else if(value == node->payload && node->active)
        {
            returnNode = node;
        } else;

        return returnNode;
    }

    /**
     * Pushes each node into a vector
     */
    void pushVect(TreeNode<T> *node, std::vector<T> &treeVect){
        if(node->left != nullptr){
            pushVect(node->left, treeVect);
        }
        if(node->right != nullptr){
            pushVect(node->right, treeVect);
        }

        treeVect.push_back(node->payload);
    }

    void preOrderTraversal(std::ostream &os, TreeNode<T> *node, int &count)
    {
        if(node != nullptr)
        {
            count++;
            if(count != numNode)
            {
                os << node->payload << "," << std::endl;
            }
            else
            {
                os << node->payload << std::endl;
            }
            preOrderTraversal(os, node->left, count);
            preOrderTraversal(os, node->right, count);
        }
    }

public:

    DSTree<T>();
    DSTree<T>(const DSTree<T>& copy);
    ~DSTree<T>();

    DSTree<T> &operator= (const DSTree<T> &copy);

    void insert(T value);
    void remove(T value);
    bool find(T value);
    void clear();
    void preOrderTraversal(std::ostream& os);

    int getNumNodes();

    void toVector(std::vector<T> &treeVector);

    /**
    *  This is the PUBLIC get that calls the private one
    */
    T& get(T value){
        TreeNode<T> *toReturn = find(value, this->root);

        return toReturn->payload;
    }
};

/**
*   Constructor
*/
template<typename T>
DSTree<T>::DSTree()
{
    this->root = nullptr;
    this->numNode = 0;
}
/**
 *
 * Copy constructor
 */
template<typename T>
DSTree<T>::DSTree(const DSTree<T> &copy) {
    if(copy.numNode !=0){
        this->root = copyNode(copy.root);

        this->numNode = copy.numNode;
    } else {
        this->root = nullptr;
        this->numNode = 0;
    }
}
/**
*   Destructor
*   Uses the private del function
*/
template<typename T>
DSTree<T>::~DSTree<T>()
{
    if(this->numNode > 0)
    {
        del(this->root);
    } else;
}

/**
 * Equals Operator
 */
template<typename T>
DSTree<T> &DSTree<T>::operator=(const DSTree<T> &copy) {
    if(copy.numNode !=0){
        this->root = copyNode(copy.root);
        this->numNode = copy.numNode;
    } else {
        this->root = nullptr;
        this->numNode = 0;
    }
    return this;
}
/**
*  PUBLIC insert calls the private one
*/
template<typename T>
void DSTree<T>::insert(T value)
{
    if(this->numNode == 0) {
        this->root = new TreeNode<T>(value);
    }
    else
    {
        insert(value, this->root);
    }
    this->numNode++;
}
/**
*   PUBLIC remove that calls the private remove
*/
template<typename T>
void DSTree<T>::remove(T value) {
    if(this->numNode != 0){
        remove(value, this->root);
    } else;
}
/**
 * Find function that returns a bool
 */
template<typename T>
bool DSTree<T>::find(T value) {
    if(this->root == nullptr){
        return false;
    } else {
        TreeNode<T>* comp = find(value, this->root);
        if(comp == NULL){
            return false;
        } else {
            return true;
        }
    }
}
/**
*   Returns the total number of nodes inside of the AVL Tree
*/
template<typename T>
int DSTree<T>::getNumNodes() {
    return this->numNode;
}

/**
 *
 * Clears the tree
 */
template<typename T>
void DSTree<T>::clear() {
    if(this->numNode > 0)
    {
        del(this->root);
    } else;
}

/**
 * Transforms the AVL tree into vector format (not ordered)
 * @tparam T
 * @param treeVector
 */
template<typename T>
void DSTree<T>::toVector(std::vector<T> &treeVector){
    if(this->numNode > 0){
        pushVect(this->root, treeVector);
    } else;
}

template<typename T>
void DSTree<T>::preOrderTraversal(std::ostream &os)
{
    int count = 0;
    preOrderTraversal(os, root, count);
}

#endif //SEARCH_ENGINE_DSTREE_H

