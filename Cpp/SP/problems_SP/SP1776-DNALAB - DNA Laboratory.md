---
title: "DNALAB - DNA Laboratory"
layout: "post"
diff: 难度0
pid: SP1776
tag: []
---

# DNALAB - DNA Laboratory

## 题目描述

Having started to build his own DNA lab just recently, the evil doctor Frankenstein is not quite up to date yet. He wants to extract his DNA, enhance it somewhat and clone himself. He has already figured out how to extract DNA from some of his blood cells, but unfortunately reading off the DNA sequence means breaking the DNA into a number of short pieces and analyzing those first. Frankenstein has not quite understood how to put the pieces together to recover the original  
 sequence.

 His pragmatic approach to the problem is to sneak into university and to kidnap a number of smart looking students. Not surprisingly, you are one of them, so you would better come up with a solution pretty fast.

 You are given a list of strings over the alphabet A (for adenine), C (cytosine), G (guanine), and T (thymine), and your task is to find the shortest string (which is typically not listed) that contains all given strings as substrings. If there are several such strings of shortest length, find the smallest in alphabetical/lexicographical order.

**Input**  
 The fist line contains the number of scenarios. For each scenario, the first line contains the number n of strings with 1<=n<=15. Then these strings with 1 <= length <= 100 follow, one on each line, and they consist of the letters ‘A’, ‘C’, ‘G’, and ‘T’ only.

**Output**  
 The output for every scenario begins with a line containing “Scenario #i:”, where i is the number of the scenario starting at 1. Then print a single line containing the shortest (and smallest) string as described above. Terminate the output for the scenario with a blank line.

**Sample Input**  
 1  
 2  
 TGCACA  
 CAT

**Sample Output**

Scenario #1:  
 TGCACAT

