---
title: "Gotta Catch Em' All!"
layout: "post"
diff: 普及-
pid: CF757A
tag: ['字符串', '概率论']
---

# Gotta Catch Em' All!

## 题目描述

Bash wants to become a Pokemon master one day. Although he liked a lot of Pokemon, he has always been fascinated by Bulbasaur the most. Soon, things started getting serious and his fascination turned into an obsession. Since he is too young to go out and catch Bulbasaur, he came up with his own way of catching a Bulbasaur.

Each day, he takes the front page of the newspaper. He cuts out the letters one at a time, from anywhere on the front page of the newspaper to form the word "Bulbasaur" (without quotes) and sticks it on his wall. Bash is very particular about case — the first letter of "Bulbasaur" must be upper case and the rest must be lower case. By doing this he thinks he has caught one Bulbasaur. He then repeats this step on the left over part of the newspaper. He keeps doing this until it is not possible to form the word "Bulbasaur" from the newspaper.

Given the text on the front page of the newspaper, can you tell how many Bulbasaurs he will catch today?

Note: uppercase and lowercase letters are considered different.

## 输入格式

Input contains a single line containing a string $ s $ ( $ 1<=|s|<=10^{5} $ ) — the text on the front page of the newspaper without spaces and punctuation marks. $ |s| $ is the length of the string $ s $ .

The string $ s $ contains lowercase and uppercase English letters, i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF757A/5a3118f39129b2a74b924e2ddab1fc42162a4073.png).

## 输出格式

Output a single integer, the answer to the problem.

## 说明/提示

In the first case, you could pick: Bulbbasaur.

In the second case, there is no way to pick even a single Bulbasaur.

In the third case, you can rearrange the string to BulbasaurBulbasauraddrgndgddgargndbb to get two words "Bulbasaur".

## 样例 #1

### 输入

```
Bulbbasaur

```

### 输出

```
1

```

## 样例 #2

### 输入

```
F

```

### 输出

```
0

```

## 样例 #3

### 输入

```
aBddulbasaurrgndgbualdBdsagaurrgndbb

```

### 输出

```
2

```

