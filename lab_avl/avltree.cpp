/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */




template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
	if (subtree== NULL)
		return V();
    if (subtree->key == key)
    	return subtree->value;
    else if (subtree->key > key)
    	return find(subtree->left, key);
    else 
    	return find(subtree->right,key);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Outputs the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    Node* temp1 = t->right->left;
    t->right = temp1;
    temp->left = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = temp;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Outputs the rotation name (don't remove this)
    // your code here
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = temp;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);

}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
	if (heightOrNeg1(subtree->left)-heightOrNeg1(subtree->right) > 1){
		if (heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right) >= 0){
			rotateRight(subtree);
		}
		else 
			rotateLeftRight(subtree);
	}
	else if (heightOrNeg1(subtree->left)-heightOrNeg1(subtree->right) < -1){
		if (heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left) >= 0){
			rotateLeft(subtree);
		}
		else 
			rotateRightLeft(subtree);
	}

	subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
    //cout<<"~~~~~~"<<endl;
    //update_height(root);
    //rebalance(root);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if(subtree == NULL)
        subtree = new Node(key, value);
    else if(key < subtree->key){
        insert(subtree->left, key, value);
    }else {
        insert(subtree->right, key, value);
    }

    rebalance(subtree);

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
    //update_height(root);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    // if (subtree == NULL)
    //     return;

    // if (key < subtree->key) {
    //     // your code here
    //     remove(subtree->left, key);

    // }
    // else if (key > subtree->key) {
    //     // your code here
    //     remove(subtree->right, key);

    // } else {
    //     if (subtree->left == NULL && subtree->right == NULL) {
    //         // no-child remove
    //         // your code here

    //         delete subtree;
    //         subtree = NULL;
    //     } else if (subtree->left != NULL && subtree->right != NULL) {

    //         // your code here
    //         Node* temp = subtree->left;
    //         while(temp->right!=NULL){
    //             temp = temp->right;
    //         }
    //         swap(subtree, temp);
    //         remove(subtree->left, key);
    //     } else {

    //         // your code here
    //         if(subtree->right == NULL){
    //             Node* temp = subtree->left;
    //             delete subtree;
    //             subtree = temp;

    //         }else{
    //             Node* temp = subtree->right;
    //             delete subtree;
    //             subtree = temp;

    //         }
    //     }
    //     // your code here


    // }
    // if(subtree!=NULL){

    //         rebalance(subtree);
    //     }
    if (subtree == NULL)
    	return ;
    if (key < subtree->key){
    	remove(subtree->left,key);
    }
    else if (key > subtree->key){
    	remove(subtree->right,key);
    }
    else {
    	if (subtree->left == NULL && subtree->right == NULL){
    		delete subtree;
    		subtree = NULL;
    	}
    	else if (subtree->left != NULL and subtree->right != NULL){
    		Node* temp = subtree->left;
    		while (temp != NULL){
    			temp = temp->right;
    		}
    		swap(subtree,temp);
    		remove(subtree->left,key);
    	}
    	else {
    		if (subtree->left == NULL){
    			Node* temp = subtree->right;
    			delete subtree;
    			subtree = temp;
    		}
    		else{
    			Node* temp = subtree->left;
    			delete subtree;
    			subtree = temp;   			
    		}
    	}
    }
    if (subtree!= NULL)
    	rebalance(subtree);
}
