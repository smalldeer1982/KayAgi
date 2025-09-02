---
title: "M00PAIR - 0 0 Pairs"
layout: "post"
diff: 难度0
pid: SP3973
tag: []
---

# M00PAIR - 0 0 Pairs

## 题目描述

 [English](/problems/M00PAIR/en/) [Vietnamese](/problems/M00PAIR/vn/)A sequence consisting of one digit, the number 1 is initially written into a computer. At each successive time step, the computer simultaneously tranforms each digit 0 into the sequence 1 0 and each digit 1 into the sequence 0 1.

So, after the first time step, the sequence 0 1 is obtained; after the second, the sequence 1 0 0 1, after the third, the sequence 0 1 1 0 1 0 0 1 and so on.

How many pairs of consequitive zeroes will appear in the sequence after n steps?

### Input

Clarification for this Problem: The Range of inputs is from 1 to 999 in some order and in particular not in ascending order

### Output

For each input n print the number of consequitive zeroes pairs that will appear in the sequence after n steps.

### Sample

 ```
Sample Input 
1
2 
3 
4
5 
Sample output 
0
1 
1
3
5
 
```
**Notice : Long output - 1.45MB**  - there are a lot of input/output so it is easy to TLE if you dont optimize in/out if you use Java ...

