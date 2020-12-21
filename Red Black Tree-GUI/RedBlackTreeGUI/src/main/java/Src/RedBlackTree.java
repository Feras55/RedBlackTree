/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Src;

import static java.lang.constant.ConstantDescs.NULL;

/**
 *
 * @author Feras
 */
public class RedBlackTree {
    Node root;
    
     void clear(Node node){
        if (node == NULL)
            return;
        clear(node.left);
        clear(node.right);
        /* delete node;
        node = NULL;
        Delete is automatic in java*/
    }
     
     Node find(Node node, int k){
        if (node == NULL){
            return (Node) NULL;
        }
        if (k == node.key){
            return node;
        }
        if (k < node.key){
            return find(node.left, k);
        }
        return find(node.right, k);
    }
     
    Node rotateRight(Node node){
        Node A = node.left;
        Node B = node;
        Node y = node.left.right;
        Node p = node.parent;
        B.left = y;
        if (y != NULL) y.parent = B;
        A.right = B;
        B.parent = A;

        A.parent = p;
        if (p != NULL && p.right == B){
            p.right = A;
        }
        else if (p != NULL){
            p.left = A;
        }
        return A;
    }     
        Node rotateLeft(Node node){
        Node B = node.right;
        Node A = node;
        Node y = node.right.left;
        Node p = node.parent;
        B.left = A;
        A.parent = B;
        A.right = y;
        if (y != NULL){
            y.parent = A;
        }

        B.parent = p;
        if (p != NULL && p.right == A){
            p.right = B;
        }
        else if (p != NULL){
            p.left = B;
        }

        return B;
    }
    
   int checkInvariant(Node node){
        if (node == NULL) return 0;

        int blackNodeLeft = checkInvariant(node.left);
        int blackNodesRight = checkInvariant(node.right);
        if (blackNodeLeft != blackNodesRight) {
            System.out.println("Invariant broken!!!");
        }     
        return (node.black ? 1 : 0) + blackNodeLeft;
    }

    
    
}
