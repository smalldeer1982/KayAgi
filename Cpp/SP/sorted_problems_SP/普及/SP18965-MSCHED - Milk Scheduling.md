---
title: "MSCHED - Milk Scheduling"
layout: "post"
diff: 普及/提高-
pid: SP18965
tag: []
---

# MSCHED - Milk Scheduling

## 题目描述

 [English](/problems/MSCHED/en/) [Vietnamese](/problems/MSCHED/vn/)Farmer John has N cows that need to be milked (1 <= N <= 10,000), each of which takes only one unit of time to milk.

Being impatient animals, some cows will refuse to be milked if Farmer John waits too long to milk them. More specifically, cow i produces g\_i gallons of milk (1 <= g\_i <= 1000), but only if she is milked before a deadline at time d\_i (1 <= d\_i <= 10,000). Time starts at t=0, so at most x total cows can be milked prior to a deadline at time t=x.

Please help Farmer John determine the maximum amount of milk that he can obtain if he milks the cows optimally.

**Input** :

\- Line 1: The value of N.

\- Lines 2..1+N: Line i+1 contains the integers g\_i and d\_i.

**Output** : A single numbers denotes the maximum number of gallons of milk Farmer John can obtain.

**Sample** :

 **Input:**

 4

 10 3

 7 5

 8 1

 2 1

 **Output :**

 25

Input details : There are 4 cows. The first produces 10 gallons of milk if milked by time 3, and so on.

Output details : Farmer John milks cow 3 first, giving up on cow 4 since she cannot be milked by her deadline due to the conflict with cow 3. Farmer John then milks cows 1 and 2.

