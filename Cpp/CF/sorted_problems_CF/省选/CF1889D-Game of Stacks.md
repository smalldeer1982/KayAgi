---
title: "Game of Stacks"
layout: "post"
diff: 省选/NOI-
pid: CF1889D
tag: []
---

# Game of Stacks

## 题目描述

You have $ n $ stacks $ r_1,r_2,\ldots,r_n $ . Each stack contains some positive integers ranging from $ 1 $ to $ n $ .

Define the following functions:

```
function init(pos):
    stacks := an array that contains n stacks r[1], r[2], ..., r[n]
    return get(stacks, pos)

function get(stacks, pos):
    if stacks[pos] is empty:
        return pos
    else:
        new_pos := the top element of stacks[pos]
        pop the top element of stacks[pos]
        return get(stacks, new_pos)
```

You want to know the values returned by $ \texttt{init(1)}, \texttt{init(2)}, \ldots, \texttt{init(n)} $ .

Note that, during these calls, the stacks $ r_1,r_2,\ldots,r_n $ don't change, so the calls $ \texttt{init(1)}, \texttt{init(2)}, \ldots, \texttt{init(n)} $ are independent.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 1\le n\le 10^5 $ ) — the length of the array $ r $ .

Each of the following $ n $ lines contains several integers. The first integer $ k_i $ ( $ 0\le k_i\le 10^5 $ ) represents the number of elements in the $ i $ -th stack, and the following $ k_i $ positive integers $ c_{i,1},c_{i,2},\ldots,c_{i,k_i} $ ( $ 1\le c_{i,j}\le n $ ) represent the elements in the $ i $ -th stack. $ c_{i,1} $ is the bottom element.

In each test, $ \sum k_i\le 10^6 $ .

## 输出格式

You need to output $ n $ values, the $ i $ -th of which is the value returned by $ \texttt{init(i)} $ .

## 说明/提示

In the first example:

- When you call $ \texttt{init(1)} $ , set $ \texttt{stacks := [[1,2,2],[3,1,2],[1,2,1]]} $ , and then call $ \texttt{get(stacks, 1)} $ . 
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3,1,2],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3,1],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3],[1,2,1]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1],[3],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 3} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1,2,1]] $ , and then call $ \texttt{get(stacks, 3)} $ .
  - $ \texttt{stacks[3]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[3]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[],[],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is empty, return $ 1 $ .
- When you call $ \texttt{init(2)} $ , set $ \texttt{stacks := [[1,2,2],[3,1,2],[1,2,1]]} $ , and then call $ \texttt{get(stacks, 2)} $ . 
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2,2],[3,1],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2,2],[3],[1,2,1]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3],[1,2,1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 3} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[],[1,2,1]] $ , and then call $ \texttt{get(stacks, 3)} $ .
  - $ \texttt{stacks[3]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[3]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1,2]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is empty, return $ 2 $ .
- When you call $ \texttt{init(3)} $ , set $ \texttt{stacks := [[1,2,2],[3,1,2],[1,2,1]]} $ , and then call $ \texttt{get(stacks, 3)} $ . 
  - $ \texttt{stacks[3]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[3]} $ , which makes $ \texttt{stacks} $ become $ [[1,2,2],[3,1,2],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3,1,2],[1,2]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3,1],[1,2]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 1} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1,2],[3],[1,2]] $ , and then call $ \texttt{get(stacks, 1)} $ .
  - $ \texttt{stacks[1]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[1]} $ , which makes $ \texttt{stacks} $ become $ [[1],[3],[1,2]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is not empty, set $ \texttt{new_pos := 3} $ , and pop the top element of $ \texttt{stacks[2]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1,2]] $ , and then call $ \texttt{get(stacks, 3)} $ .
  - $ \texttt{stacks[3]} $ is not empty, set $ \texttt{new_pos := 2} $ , and pop the top element of $ \texttt{stacks[3]} $ , which makes $ \texttt{stacks} $ become $ [[1],[],[1]] $ , and then call $ \texttt{get(stacks, 2)} $ .
  - $ \texttt{stacks[2]} $ is empty, return $ 2 $ .

## 样例 #1

### 输入

```
3
3 1 2 2
3 3 1 2
3 1 2 1
```

### 输出

```
1 2 2
```

## 样例 #2

### 输入

```
5
5 1 2 4 3 4
6 1 2 5 3 3 4
6 1 1 4 4 4 2
9 3 1 4 2 3 5 5 1 2
4 4 4 1 3
```

### 输出

```
1 1 1 1 1
```

