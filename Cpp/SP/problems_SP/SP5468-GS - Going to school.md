---
title: "GS - Going to school"
layout: "post"
diff: 难度0
pid: SP5468
tag: []
---

# GS - Going to school

## 题目描述

Your family has just moved to small town with simple transportation system: there are N conjunctions and N - 1 roads connecting the conjunctions. These roads guarantee that it’s possible to travel between any two conjunctions. Each road connects two conjunctions and has a preferred value.

  
You are new here and not familiar with the roads. So when you stay at a conjunction which is not your destination, you will choose one of incident roads to walk (even it makes you get farther from your destination). The probability of choosing one road equals to its preferred value divide to total preferred value of all incident roads. For example, if there are three incident roads at current conjunction with preferred value 1, 2 and 3, the probability of choosing each road is 1/6, 2/6 and 3/6, respectively.

  
Given the starting conjunction where your house is and the final conjunction where is your school, what is the expected number of roads you have to walk to reach the destination?

  
Input  
The input begins with T – number of test cases. For each test case, there will be:  
• The first line consists of N, st, en - number of conjunctions, starting and final  
conjunction.  
• In next N - 1 lines, each line consists of three positive integers u, v and c indicate that  
there is a road between conjunction u and v with preferred value c.

  
Output  
For each test case, print the expected number of roads you have to walk, round to exactly 5  
precision digits.

  
Limits  
T <= 20  
1 <= N <= 15  
All numbers in input <= 100

  
Sample input  
1  
3 2 3  
1 2 1  
2 3 1

  
Sample output  
3.00000

  
Explanation  
There are 50% chance of going 2-3 directly; 25% chance of going 2-1-2-3, 12.5% of going 2-1-  
2-1-2-3 and so on. The result equals 1 × 50% + 3 × 25% + 5 × 12.5% + … = 3

