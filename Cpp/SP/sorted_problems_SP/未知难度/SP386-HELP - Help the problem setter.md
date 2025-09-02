---
title: "HELP - Help the problem setter"
layout: "post"
diff: 难度0
pid: SP386
tag: []
---

# HELP - Help the problem setter

## 题目描述

 Preparing a problem for a programming contest takes a lot of time. Not only do you have to write the problem description and write a solution, but you also have to create difficult input files. In this problem, you get the chance to help the problem setter to create some input for a certain problem.  
 For this purpose, let us select the problem which was not solved during last year's local contest. The problem was about finding the optimal binary search tree, given the probabilities that certain nodes are accessed. Your job will be: given the desired optimal binary search tree, find some access probabilities for which this binary search tree is the unique optimal binary search tree. Don't worry if you have not read last year's problem, all required definitions are provided in the following.  
 Let us define a **binary search tree** inductively as follows:

- The empty tree which has no node at all is a binary search tree
- Each non-empty binary search tree has a root, which is a node labelled with an integer, and two binary search trees as left and right subtree of the root
- A left subtree contains no node with a label ≥ than the label of the root
- A right subtree contains no node with a label ≤ than the label of the root

Given such a binary search tree, the following **search procedure** can be used to locate a node in the tree:  
 Start with the root node. Compare the label of the current node with the desired label. If it is the same, you have found the right node. Otherwise, if the desired label is smaller, search in the left subtree, otherwise search in the right subtree.  
 The **access cost** to locate a node is the number of nodes you have to visit until you find the right node. An **optimal binary search tree** is a binary search tree with the minimum expected access cost.

