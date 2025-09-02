---
title: "Bear and Different Names"
layout: "post"
diff: 普及/提高-
pid: CF771B
tag: []
---

# Bear and Different Names

## 题目描述

In the army, it isn't easy to form a group of soldiers that will be effective on the battlefield. The communication is crucial and thus no two soldiers should share a name (what would happen if they got an order that Bob is a scouter, if there are two Bobs?).

A group of soldiers is effective if and only if their names are different. For example, a group (John, Bob, Limak) would be effective, while groups (Gary, Bob, Gary) and (Alice, Alice) wouldn't.

You are a spy in the enemy's camp. You noticed $ n $ soldiers standing in a row, numbered $ 1 $ through $ n $ . The general wants to choose a group of $ k $ consecutive soldiers. For every $ k $ consecutive soldiers, the general wrote down whether they would be an effective group or not.

You managed to steal the general's notes, with $ n-k+1 $ strings $ s_{1},s_{2},...,s_{n-k+1} $ , each either "YES" or "NO".

- The string $ s_{1} $ describes a group of soldiers $ 1 $ through $ k $ ("YES" if the group is effective, and "NO" otherwise).
- The string $ s_{2} $ describes a group of soldiers $ 2 $ through $ k+1 $ .
- And so on, till the string $ s_{n-k+1} $ that describes a group of soldiers $ n-k+1 $ through $ n $ .

Your task is to find possible names of $ n $ soldiers. Names should match the stolen notes. Each name should be a string that consists of between $ 1 $ and $ 10 $ English letters, inclusive. The first letter should be uppercase, and all other letters should be lowercase. Names don't have to be existing names — it's allowed to print "Xyzzzdj" or "T" for example.

Find and print any solution. It can be proved that there always exists at least one solution.

## 输入格式

The first line of the input contains two integers $ n $ and $ k $ ( $ 2<=k<=n<=50 $ ) — the number of soldiers and the size of a group respectively.

The second line contains $ n-k+1 $ strings $ s_{1},s_{2},...,s_{n-k+1} $ . The string $ s_{i} $ is "YES" if the group of soldiers $ i $ through $ i+k-1 $ is effective, and "NO" otherwise.

## 输出格式

Find any solution satisfying all given conditions. In one line print $ n $ space-separated strings, denoting possible names of soldiers in the order. The first letter of each name should be uppercase, while the other letters should be lowercase. Each name should contain English letters only and has length from $ 1 $ to $ 10 $ .

If there are multiple valid solutions, print any of them.

## 说明/提示

In the first sample, there are $ 8 $ soldiers. For every $ 3 $ consecutive ones we know whether they would be an effective group. Let's analyze the provided sample output:

- First three soldiers (i.e. Adam, Bob, Bob) wouldn't be an effective group because there are two Bobs. Indeed, the string $ s_{1} $ is "NO".
- Soldiers $ 2 $ through $ 4 $ (Bob, Bob, Cpqepqwer) wouldn't be effective either, and the string $ s_{2} $ is "NO".
- Soldiers $ 3 $ through $ 5 $ (Bob, Cpqepqwer, Limak) would be effective, and the string $ s_{3} $ is "YES".
- ...,
- Soldiers $ 6 $ through $ 8 $ (Adam, Bob, Adam) wouldn't be effective, and the string $ s_{6} $ is "NO".

## 样例 #1

### 输入

```
8 3
NO NO YES YES YES NO

```

### 输出

```
Adam Bob Bob Cpqepqwer Limak Adam Bob Adam
```

## 样例 #2

### 输入

```
9 8
YES NO

```

### 输出

```
R Q Ccccccccc Ccocc Ccc So Strong Samples Ccc
```

## 样例 #3

### 输入

```
3 2
NO NO

```

### 输出

```
Na Na Na
```

