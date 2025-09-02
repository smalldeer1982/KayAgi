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

