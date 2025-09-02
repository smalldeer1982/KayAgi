---
title: "SKYLINE2 - Draw Skyline Graph"
layout: "post"
diff: 难度0
pid: SP19320
tag: []
---

# SKYLINE2 - Draw Skyline Graph

## 题目描述

Once My Friend Deepan Gupta went a shop to buy a Laptop with features he needed. Seller showed him alot of laptops having various distinct features like cost, speed, memory, color, design, brand etc. But He was worrying only about memory and speed as he only needed these two. Because of so many laptops he got confused. He was not able to select a laptop. So he decided to select a skyline set in terms of {memory, speed} which will make it easier for him to decide. Objects are said to be in skyline set such that no one object in set dominates other object of set and all the objects which are not in the set are dominated by atleast one object in the set. No Object in the set is dominated by any other object (both set and not in set). One Object dominate other object if all the features of first objects are greater than or equal to second objects's corresponding features, but there exists alteast a feature that is strictly gerater than second object's corresponding feature. No one object dominate other object it means object does not satisfy the dominance condition, So Skyline Set can have two different objects with both same features.

For example:  
Laptop1 : memory : 100GB, Processor Speed : 700GHz  
Laptop2 : memory : 200GB, Processor Speed : 500GHz  
Laptop3 : memory : 50GB, Processor Speed : 100GHz  
Laptop4: memory : 200GB, Processor Speed : 500GHz  
{Laptop1, Laptop2, Laptop4} are in skyline set while Laptop3 is not.

  
If Still not understood 'SKYLINE', refer this link :: [LINK](http://www.ccs.neu.edu/home/jarodwen/materials/skyline_pre.pdf)  
  
Given N number of laptops with {M\[i\],S\[i\]}. Your task is to select a skyline set and print {M\[i\],S\[i\]} in newline of all the objects in set with decreasing order of M\[i\] value. If two Objects have same M\[i\] value, then you can print them in any order. For exact output format, refer to given examples.

**Constraints:** 1<=T<=50, 1<=N<=10^5, 1<=M\[i\], S\[i\]<=10^9.

**Input:**

First line contains t, number of testcases. For each testcase, first line contains N, number of laptops. After that each of next N lines contains {M\[i\],S\[i\]} data for ith laptop, M\[i\] is memory && S\[i\] is Speed of Processor of ith Laptop.

**Output:**  
For Each testcase first line contains K, number of Skyline objebts in set, then each of next K lines contains {M\[i\],S\[i\]} data for ith laptop in decreasing order of M\[i\].

  **Example**  
**Input:**  
2  
3  
100 700  
200 500  
50 100  
  
4  
200 500  
100 1000  
50 900  
1000 50  
  
**Output:**  
2  
200 500  
100 700  
3  
1000 50  
200 500  
100 1000

**HINT : Just Follow the statement Very CareFully || Observe the examples.**

