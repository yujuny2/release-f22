/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node*& node = find(root, key);
    if (node == NULL) {
        return V();
    }
    return node->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == NULL || subtree->key == key) {
        return subtree;
    }

    if (subtree->key > key) {
        return find(subtree->left, key);
    }
    
    return find(subtree->right, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    Node*& tbi = find(root, key);
    if (tbi == NULL) {
        tbi = new Node(key, value);
    }
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    // Node* tmp = first;
    // second->right = first->right;
    // first->right = NULL;
    // first = second;
    // second = tmp;
    // std::cout << first->left << std::endl;
    // std::cout << second->right->key << std::endl;
    // second->right = NULL;
    // std::cout << "segfault" << std::endl;

    // first->left = left_tmp;
    // second->left = NULL;

    K first_key = first->key;
    V first_value = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = first_key;
    second->value = first_value;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root, key);
    // your code here
    // Node*& ptr = find(root, key);
    // if (!ptr) return;
    // if (!ptr->left && !ptr->right) {
    //     delete ptr;
    //     ptr = NULL;
    // } else if (!(ptr->left)) {
    //     Node* ptr_right = ptr->right;
    //     delete ptr;
    //     ptr = ptr_right;
    // } else if (!(ptr->right)) {
    //     Node* ptr_left = ptr->left;
    //     delete ptr;
    //     ptr = ptr_left;
    // } else {
    //     Node* iop = ptr->left;
    //     Node* prev = ptr;
    //     if (!(iop->right)) {
    //         Node* ptr_right = ptr->right;
    //         delete ptr;
    //         ptr = iop;
    //         ptr->right = ptr_right;
    //         return;
    //     }
    //     while (iop->right) {
    //         prev = iop;
    //         iop = iop->right;
    //     }
    //     // Node*& iop_ref = iop;
    //     swap(ptr, iop);
    //     delete iop;
    //     iop = NULL;
    //     prev->right = NULL;
    // }
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree->left;
            while (iop->right) {
                iop = iop->right;
            }
            swap(subtree, iop);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if (!subtree->left) {
                swap(subtree, subtree->right);
                remove(subtree->right, key);
            } else if (!subtree->right) {
                swap(subtree, subtree->left);
                remove(subtree->left, key);
            }
        }
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> bst;
    for (auto node : inList) {
        bst.insert(node.first, node.second);
    }
    return bst;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> tree_height(inList.size(), 0);
    std::sort(inList.begin(), inList.end());
    do {
        BST<K,V> bst = listBuild(inList);
        tree_height[bst.height()]++;
    } while (std::next_permutation(inList.begin(), inList.end()));
    return tree_height;
}