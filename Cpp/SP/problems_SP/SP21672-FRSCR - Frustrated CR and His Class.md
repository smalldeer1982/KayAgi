---
title: "FRSCR - Frustrated CR and His Class"
layout: "post"
diff: 难度0
pid: SP21672
tag: []
---

# FRSCR - Frustrated CR and His Class

## 题目描述

As we all know that our CR gets Frustrated by all the work he is given by CSE Department . This time he is thinking of dividing the work to the whole class.  
HOD of the department has given a project on DBMS to CR which must be completed in **P** units of time. Project consist of two types of task   
1-> You have to find some tables from database .  
2-> You have to execute certain queries on them.

Now our CR decides to divide the class in two groups of strength **n** and **m**(say A & B) . Group A is given the task of finding tables from database & group B is given the task of executing certain queries on tables provided by group A. **Group B will start their queries on tables only after they have received all the tables from group A. There is no time lag between end of task of group A and beginning of task of group B.** .

Every student has his/her own capability of doing the task.

Suppose a student of group A can finds first table in X minute then he will find the second table in 2X more minutes and third table in 3X more minutes and so on.(Eg: if a student finds first table in 3 minutes then he will find second table in 6 more minute and third table in 9 more minutes.This means that he can find a total of 3 tables in 18 minutes. Therefore from 18th minute uptil 29th minute he can find only 3 tables ) . The same goes for second group.

**A project is said to be complete if and only if at least one query is executed on every table found by group A.  
All members of a group start working simultaneously.  
You can assume every member of group A always finds a new unique table.**

Now if the project is complete, the HOD gives a score to the CR which is equal to the numbers of tables sucessfully found by first group and successfully queried by the second group. If the project is incomplete, CR gets 0 score.

**INPUT**  
First line contains an integer **t** denoting the number of test cases.  
Each test case consists of 4 lines.  
First line contains and integer **p** denoting time given by HOD.  
Next line contains integers **n** & **m** denoting the strength of first and second group respectively.  
Next line contains n integers representing the capability of students in group A.  
Next line contains m integers representing the capability of students in group B.

**OUTPUT**   
For each test case print the maximum score obtained by our CR or 0 is project remains incomplete.

**CONSTRAINTS:**   
0 < T <= 1000  
0 < p <= 10^7  
0 < n,m <=100

0<capability<=10

**EXAMPLE**

**INPUT**   
1  
20  
2 2  
2 3  
1 2

**OUTPUT**  
5

**EXPLANATION**  
For given test case group A can find 5 table in first 12 minute and group B can perform 5 query in remaining 8 minute . Here we cannot get more than 5 points in any other case.

