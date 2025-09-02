---
title: "Representative Sampling"
layout: "post"
diff: 提高+/省选-
pid: CF178F3
tag: ['动态规划 DP', '字典树 Trie']
---

# Representative Sampling

## 题目描述

The Smart Beaver from ABBYY has a long history of cooperating with the "Institute of Cytology and Genetics". Recently, the Institute staff challenged the Beaver with a new problem. The problem is as follows.

There is a collection of $ n $ proteins (not necessarily distinct). Each protein is a string consisting of lowercase Latin letters. The problem that the scientists offered to the Beaver is to select a subcollection of size $ k $ from the initial collection of proteins so that the representativity of the selected subset of proteins is maximum possible.

The Smart Beaver from ABBYY did some research and came to the conclusion that the representativity of a collection of proteins can be evaluated by a single number, which is simply calculated. Let's suppose we have a collection $ {a_{1},...,a_{k}} $ consisting of $ k $ strings describing proteins. The representativity of this collection is the following value:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF178F3/c7b3873e6751582bb5e2ad2c1deb58138ab9c543.png)where $ f(x,y) $ is the length of the longest common prefix of strings $ x $ and $ y $ ; for example, $ f( $ "abc", "abd" $ )=2 $ , and $ f( $ "ab", "bcd" $ )=0 $ .

Thus, the representativity of collection of proteins $ { $ "abc", "abd", "abe" $ } $ equals $ 6 $ , and the representativity of collection $ { $ "aaa", "ba", "ba" $ } $ equals $ 2 $ .

Having discovered that, the Smart Beaver from ABBYY asked the Cup contestants to write a program that selects, from the given collection of proteins, a subcollection of size $ k $ which has the largest possible value of representativity. Help him to solve this problem!

## 输入格式

The first input line contains two integers $ n $ and $ k $ ( $ 1<=k<=n $ ), separated by a single space. The following $ n $ lines contain the descriptions of proteins, one per line. Each protein is a non-empty string of no more than $ 500 $ characters consisting of only lowercase Latin letters (a $ ... $ z). Some of the strings may be equal.

The input limitations for getting 20 points are:

- $ 1<=n<=20 $

The input limitations for getting 50 points are:

- $ 1<=n<=100 $

The input limitations for getting 100 points are:

- $ 1<=n<=2000 $

## 输出格式

Print a single number denoting the largest possible value of representativity that a subcollection of size $ k $ of the given collection of proteins can have.

## 样例 #1

### 输入

```
3 2
aba
bzd
abq

```

### 输出

```
2

```

## 样例 #2

### 输入

```
4 3
eee
rrr
ttt
qqq

```

### 输出

```
0

```

## 样例 #3

### 输入

```
4 3
aaa
abba
abbc
abbd

```

### 输出

```
9

```



---

---
title: "Yasya and the Mysterious Tree"
layout: "post"
diff: 提高+/省选-
pid: CF1980G
tag: ['字典树 Trie']
---

# Yasya and the Mysterious Tree

## 题目描述

Yasya was walking in the forest and accidentally found a tree with $ n $ vertices. A tree is a connected undirected graph with no cycles.

Next to the tree, the girl found an ancient manuscript with $ m $ queries written on it. The queries can be of two types.

The first type of query is described by the integer $ y $ . The weight of each edge in the tree is replaced by the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) of the weight of that edge and the integer $ y $ .

The second type is described by the vertex $ v $ and the integer $ x $ . Yasya chooses a vertex $ u $ ( $ 1 \le u \le n $ , $ u \neq v $ ) and mentally draws a bidirectional edge of weight $ x $ from $ v $ to $ u $ in the tree.

Then Yasya finds a simple cycle in the resulting graph and calculates the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) of all the edges in it. She wants to choose a vertex $ u $ such that the calculated value is maximum. This calculated value will be the answer to the query. It can be shown that such a cycle exists and is unique under the given constraints (independent of the choice of $ u $ ). If an edge between $ v $ and $ u $ already existed, a simple cycle is the path $ v \to u \to v $ .

Note that the second type of query is performed mentally, meaning the tree does not change in any way after it.

Help Yasya answer all the queries.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

The descriptions of the test cases follow.

The first line of each test case contains two integers $ n $ , $ m $ ( $ 2 \le n \le 2 \cdot 10^5 $ , $ 1 \le m \le 2 \cdot 10^5 $ ) — the number of vertices in the tree and the number of queries.

The next $ n - 1 $ lines of each test case contain three integers $ v $ , $ u $ , $ w $ ( $ 1 \le v, u \le n $ , $ 1 \le w \le 10^9 $ ) — the ends of some edge in the tree and its weight.

It is guaranteed that the given set of edges forms a tree.

The next $ m $ lines of each test case describe the queries:

- ^ $ y $ ( $ 1 \le y \le 10^9 $ ) — parameter of the first type query;
- ? $ v $ $ x $ ( $ 1 \le v \le n $ , $ 1 \le x \le 10^9 $ ) — parameters of the second type query.

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 2 \cdot 10^5 $ . The same is guaranteed for $ m $ .

## 输出格式

For each test case, output the answers to the queries of the second type.

## 样例 #1

### 输入

```
2
3 7
1 2 1
3 1 8
^ 5
? 2 9
^ 1
? 1 10
^ 6
? 3 1
? 2 9
5 6
1 2 777
3 2 2812
4 1 16
5 3 1000000000
^ 4
? 3 123
? 5 1000000000
^ 1000000000
? 1 908070
? 2 1
```

### 输出

```
13 15 11 10 
1000000127 2812 999756331 999999756
```

## 样例 #2

### 输入

```
3
8 4
8 6 3
6 3 4
2 5 4
7 6 2
7 1 10
4 1 4
5 1 2
^ 4
^ 7
? 7 8
? 4 10
5 6
3 1 4
2 3 9
4 3 6
5 2 10
? 5 7
^ 1
^ 8
? 4 10
? 1 9
? 3 6
4 2
2 1 4
4 3 5
2 3 4
^ 13
? 1 10
```

### 输出

```
14 13 
13 8 11 11 
10
```



---

---
title: "Auto Complete"
layout: "post"
diff: 提高+/省选-
pid: CF2041I
tag: ['字典树 Trie']
---

# Auto Complete

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041I/256207cb416106d4b37786d3e769d2d51218a3e5.png)You are designing a snazzy new text editor, and you want to add a nifty auto-complete feature to help users save time. Here is how it will work: if a user types "App", your editor will magically suggest the word "Application"! Even better, users can personalize the words that auto-complete in your editor.

Your editor will support 4 kinds of operations (Let's say the current text in your editor is $ t $ ):

1. Add an auto complete pattern $ p_i $ .
2. Delete an auto complete pattern $ p_i $ .
3. Append a string $ s $ to the end of $ t $ .
4. Delete $ c $ characters from the end of $ t $ . Note that if $ c $ is larger then the length of $ t $ , delete all the characters from $ t $ .

After each action, your editor should suggest an auto-complete candidate $ i $ that matches the following criteria:

1. The string $ p_i $ has a prefix equal to $ t $ .
2. If there are multiple $ p_i $ , pick the longest one.
3. If there are still multiple $ p_i $ , pick the one with the smallest lexicographic order.
4. If there are still multiple $ p_i $ , pick the one with the smallest ID.

 To simplify the question, for each action, print the suggested auto complete pattern ID. If there's no match, print -1.For example, let us say we have three candidates: "alice", "bob", and "charlie", with ID 1, 2, and 3. At first, there is nothing on the screen, so "charlie" (3) should be suggested because it is the longest. Then, let us say the user types "b". You should suggest "bob" (2) because it is the only one that starts with "b". Finally, let us say the user type "body". You should print -1 because there is no matched pattern.

## 输入格式

The first line contains an integer $ n $ , followed by $ n $ lines, with each line containing an action.

There are four types of actions:

1. $ i $ $ p_i $
2. $ i $
3. $ s $
4. $ c $

 The add actions are followed by an integer $ i $ and a pattern $ p_i $ , which means the user wants to add a pattern with ID $ i $ . The delete actions are followed by an integer $ i $ , which means the user wants to delete $ p_i $ from the pattern set. The append actions are followed by a string $ s $ , which means the user appends $ s $ to the end of $ t $ . The backspace actions are followed by an integer $ c $ , which means the user deletes $ c $ characters from the end of $ t $ . All the parameters are splitted by a single space character.- $ 1 \leq n \leq 10^6 $
- The total number of characters in all $ p_i $ and $ s $ does not exceed $ 2\times 10^6 $ .
- $ 1 \leq c \leq 2\times 10^6 $
- The strings $ p_i $ and $ s $ may contain any printable characters, excluding all space characters (ASCII number in the range from $ 33 $ to $ 126 $ ).
- The ID $ i $ for each add operation is unique.
- The ID $ i $ for each delete is guaranteed to be valid.
- Each ID $ i $ satisfies $ 0\le i \le n $ .

## 输出格式

The program should output $ n $ lines. For each action, output an integer $ i $ , which means that after the action, $ p_i $ is the suggested auto complete candidate. If there is no $ p_i $ that matches the requirement, output -1.

## 样例 #1

### 输入

```
6
add 1 pattern1_alice
add 2 pattern2_bob
add 3 pattern3_charlie
append pattern
append 2_bobabc
backspace 3
```

### 输出

```
1
1
3
3
-1
2
```

## 样例 #2

### 输入

```
6
append pattern
add 1 pattern1_alice____
add 2 pattern2_bob______
add 3 pattern3_charlie__
delete 1
delete 2
```

### 输出

```
-1
1
1
1
2
3
```



---

---
title: "Watto and Mechanism"
layout: "post"
diff: 提高+/省选-
pid: CF514C
tag: ['字符串', '字典树 Trie']
---

# Watto and Mechanism

## 题目描述

Watto, the owner of a spare parts store, has recently got an order for the mechanism that can process strings in a certain way. Initially the memory of the mechanism is filled with $ n $ strings. Then the mechanism should be able to process queries of the following type: "Given string $ s $ , determine if the memory of the mechanism contains string $ t $ that consists of the same number of characters as $ s $ and differs from $ s $ in exactly one position".

Watto has already compiled the mechanism, all that's left is to write a program for it and check it on the data consisting of $ n $ initial lines and $ m $ queries. He decided to entrust this job to you.

## 输入格式

The first line contains two non-negative numbers $ n $ and $ m $ ( $ 0<=n<=3·10^{5} $ , $ 0<=m<=3·10^{5} $ ) — the number of the initial strings and the number of queries, respectively.

Next follow $ n $ non-empty strings that are uploaded to the memory of the mechanism.

Next follow $ m $ non-empty strings that are the queries to the mechanism.

The total length of lines in the input doesn't exceed $ 6·10^{5} $ . Each line consists only of letters 'a', 'b', 'c'.

## 输出格式

For each query print on a single line "YES" (without the quotes), if the memory of the mechanism contains the required string, otherwise print "NO" (without the quotes).

## 样例 #1

### 输入

```
2 3
aaaaa
acacaca
aabaa
ccacacc
caaac

```

### 输出

```
YES
NO
NO

```



---

---
title: "Vasiliy's Multiset"
layout: "post"
diff: 提高+/省选-
pid: CF706D
tag: ['素数判断,质数,筛法', '进制', '字典树 Trie']
---

# Vasiliy's Multiset

## 题目描述

Author has gone out of the stories about Vasiliy, so here is just a formal task description.

You are given $ q $ queries and a multiset $ A $ , initially containing only integer $ 0 $ . There are three types of queries:

1. "+ x" — add integer $ x $ to multiset $ A $ .
2. "- x" — erase one occurrence of integer $ x $ from multiset $ A $ . It's guaranteed that at least one $ x $ is present in the multiset $ A $ before this query.
3. "? x" — you are given integer $ x $ and need to compute the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/728a3690d3a76b81fb1ccb07b4c04b8d10b1870d.png), i.e. the maximum value of bitwise exclusive OR (also know as XOR) of integer $ x $ and some integer $ y $ from the multiset $ A $ .

Multiset is a set, where equal elements are allowed.

## 输入格式

The first line of the input contains a single integer $ q $ ( $ 1<=q<=200000 $ ) — the number of queries Vasiliy has to perform.

Each of the following $ q $ lines of the input contains one of three characters '+', '-' or '?' and an integer $ x_{i} $ ( $ 1<=x_{i}<=10^{9} $ ). It's guaranteed that there is at least one query of the third type.

Note, that the integer $ 0 $ will always be present in the set $ A $ .

## 输出格式

For each query of the type '?' print one integer — the maximum value of bitwise exclusive OR (XOR) of integer $ x_{i} $ and some integer from the multiset $ A $ .

## 说明/提示

After first five operations multiset $ A $ contains integers $ 0 $ , $ 8 $ , $ 9 $ , $ 11 $ , $ 6 $ and $ 1 $ .

The answer for the sixth query is integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/4b442d72cf0f109da9eae35430cf9dc9dfa35fdf.png) — maximum among integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/c712973b7cb6a6b393c3b423fc78dda636ebb034.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e9b3f94b7acd1861f4b82fb60d691b2bd163374e.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/1bf5d0b4ff98720973629f7915ae529e790539ba.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/9023c8bab139f08429005ae47d2d497f5795be9b.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF706D/e21b15be88af70287d01c0b8f13ae0d351197a9c.png).

## 样例 #1

### 输入

```
10
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
? 8
? 11

```

### 输出

```
11
10
14
13

```



---

