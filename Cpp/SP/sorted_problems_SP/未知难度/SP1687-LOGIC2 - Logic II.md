---
title: "LOGIC2 - Logic II"
layout: "post"
diff: 难度0
pid: SP1687
tag: []
---

# LOGIC2 - Logic II

## 题目描述

Some day in 2003 in Byteland began calm and quietly as any other day. Some people went to work, some to school, some to store to buy food. Drivers were traditionally stucked in traffic jams, drinking coffee and reading morning newspaper. Suddenly the regularity of this day was disturbed by huge explosion."They blew up the embassy of Bajtocja!!!" somebody cried. Everybody began to run away in panic.

Police works pretty good in Byteland and first radiocars appeared near the embassy only few seconds after the explosion. All the people near the embassy were detained. Only one of the people is the organizer of the explosion, the others could by just occasional witnesses. It is known, among these M(1<=M<=11) people, N(1<=N<=M) people always lie because they want to make the work of police more difficult, the others always tell the truth.

All these people say P(1<=P<=30) sentences in total.All the useful sentences are in one of the 4 forms below, all the other sentences are useless and you can ignore them.

- I am guilty.
- I am not guilty.
- _Somebody_ is guilty.
- _Somebody_ is not guilty.
- Today is _Someday_.

## 输入格式

Multiple test cases. For each test case:

The first line contains three integers M, N and P. M lines follow, each contains a name of one of the people.All names contain only capital Latin letters and no whitespaces.P lines come next, each contains no more than 250 characters, the speaker and his/her speech. See the example.

You can assume that there's no whitespace at the start and the end of a line, and there are no two consecutive spaces in the input.

Input terminate by EOF.

## 输出格式

The name of the organizer if you can determine, or _Cannot Determine_ if you find more than one, or _Impossible_ if you find no one.

## 样例 #1

### 输入

```
3 1 5
MIKE
CHARLES
KATE
MIKE: I am guilty.
MIKE: Today is Sunday.
CHARLES: MIKE is guilty.
KATE: I am guilty.
KATE: How are you??
```

### 输出

```
MIKE
```

