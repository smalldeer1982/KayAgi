---
title: "DWARFLOG - Manipulate Dwarfs"
layout: "post"
diff: 普及+/提高
pid: SP24772
tag: []
---

# DWARFLOG - Manipulate Dwarfs

## 题目描述

In a small village beyond seven hills and seven seas, Snow White lives together with N dwarves who spend all their time eating and playing League of Legends. Snow White wants to put an end to this, so she has organized gym classes for them.

At the beginning of each class, the dwarves must stand in line, ordered by their height. For the purposes of this task, assume that the dwarves have heights 1, 2, ..., N (each exactly once) and initially all are standing in sorted order with height from 1 to N. Now Snow White play on them by issuing commands of the form:

• 1 X Y -- dwarves with height X and Y in the line must switch places. She also checks their ordering by issuing queries of the form:  
• 2 A B -- do dwarves with heights A, A+1, ..., B (not necessarily in that order) occupy a contiguous subsequence of the current line? Help the doofus dwarves follow Snow White's instructions and respond to her queries.

**INPUT**  
The first line of input contains the two positive integers N and M, the number of dwarves and the number of Snow White's requests, respectively (2

  
**OUTPUT**  
The output must contain one line for each request of type 2, containing the reply to the query, either “YES” or “NO”.

**Example**:

**Input** :

4 5  
2 2 3  
2 2 4  
1 1 3  
2 3 4  
1 4 3

**Output** :

YES

YES

NO

