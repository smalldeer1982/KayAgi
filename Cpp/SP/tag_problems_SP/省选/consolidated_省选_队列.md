---
title: "INGRED - Ingredients"
layout: "post"
diff: 省选/NOI-
pid: SP18187
tag: ['最短路', '进制', '队列']
---

# INGRED - Ingredients

## 题目描述

 You are given **n** cities with **m** bi-directional roads connecting them and the length of each road. There are two friends living in different cities who wish to collect some ingredients available at different stores to make cake. There are s such stores. They need not come back home after purchasing the ingredients. Petrol is expensive and they would hence like to travel minimum total distance (sum of distance distance traveled by both kids). Help them find out what this distance is.



---

---
title: "WORDRING - Word Rings"
layout: "post"
diff: 省选/NOI-
pid: SP2885
tag: ['字符串', '队列']
---

# WORDRING - Word Rings

## 题目描述

如果字符串A的**结尾两个**字符与字符串B的**开头两个**字符相匹配，我们称A与B能 **“ 相连 ”** ( 注意：A与B能相连，不代表B与A能相连 ) 

 当若干个串首尾 “ 相连 ” 成一个环时，我们称之为一个环串（一个串首尾相连也算） 

 我们希望从给定的全小写字符串中找出一个环串，使这个环串的平均长度最长     
 
```
 intercommunicational
 alkylbenzenesulfonate
 tetraiodophenolphthalein
```

如上例：第一个串能与第二个串相连，第二个串能与第三个串相连，第三个串又能与第一个串相连。按此顺序连接，便形成了一个环串。

长度为 20+21+24=65 ( **首尾重复部分需计算两次** ) ，总共使用了3个串，所以平均长度是 65/3≈21.6666

## 输入格式

多组数据  
 每组数据第一行一个整数n，表示字符串数量   
 接下来n行每行一个长度**小于等于1000**的字符串  
 读入以n=0结束

## 输出格式

若不存在环串，输出"No solution."。否则输出最长的环串平均长度。

Translated by @远藤沙椰

## 样例 #1

### 输入

```
3
intercommunicational
alkylbenzenesulfonate
tetraiodophenolphthalein
0
```

### 输出

```
21.66
```



---

---
title: "C2CRNI - Crni"
layout: "post"
diff: 省选/NOI-
pid: SP7884
tag: ['单调队列', '容斥原理']
---

# C2CRNI - Crni

## 题目描述

尽管Mirko找到了所有最有趣的游乐设施，但他的热情仍然没有消失，于是他无聊地打开了方格笔记本，开始给方块涂色，于是一个新的甚至更难的问题浮现了出来。

现在有个$N\times N$的矩阵，每个格子被填充了黑色或者白色。如果这个矩形的一个子矩形内的所有格子均为黑色并且由至少两个格子组成，则这个子矩形称为**黑矩形**。

![](https://cdn.luogu.com.cn/upload/image_hosting/hidn0vrp.png)

左图框选了两个不是黑矩形的子矩形。1号子矩形不是黑矩形，因为它包含了白色的格子；2号子矩形不是黑矩形，因为它仅包含一个格子。右图框选了三个有效的黑矩形。

现在Mirko想知道找出两个不相交的黑矩形的方案的总数目。由于结果可能非常大，因此你的答案需要对$10007$取模。

## 输入格式

第一行为一个整数$N$

接下来$N$行每行$N$个字母表示矩阵每个格子的颜色。`C`为黑色，`B`为白色。

## 输出格式

不相交黑矩形对的数量对$10007$取模后的值。

### 样例

#### 样例#1
输入：
```
2
CC
CC
```

输出：
```
2
```

#### 样例#2
输入：
```
3
CCB
CCB
CBB
```
输出：
```
5
```

#### 样例#3

输入：
```
5
BCCBB
BBCBB
BCCBB
BBBBB
CCBBB
```

输出：
```
8
```

## 样例 #1

### 输入

```
\n2 \nCC \nCC\n\n
```

### 输出

```
\n2\n\nInput:\n3 \nCCB \nCCB \nCBB\n\nOutput:\n5\n\nInput:\n5\nBCCBB\nBBCBB\nBCCBB\nBBBBB\nCCBBB\n\nOutput:\n8
```



---

