---
title: "Empire Strikes Back"
layout: "post"
diff: 提高+/省选-
pid: CF300E
tag: []
---

# Empire Strikes Back

## 题目描述

In a far away galaxy there is war again. The treacherous Republic made $ k $ precision strikes of power $ a_{i} $ on the Empire possessions. To cope with the republican threat, the Supreme Council decided to deal a decisive blow to the enemy forces.

To successfully complete the conflict, the confrontation balance after the blow should be a positive integer. The balance of confrontation is a number that looks like ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300E/ae456f9650d5b3ca46e54c303d07fec088f6ad5e.png), where $ p=n! $ ( $ n $ is the power of the Imperial strike), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF300E/99b314c14cf87aaec7902ee9933ec2e853964496.png). After many years of war the Empire's resources are low. So to reduce the costs, $ n $ should be a minimum positive integer that is approved by the commanders.

Help the Empire, find the minimum positive integer $ n $ , where the described fraction is a positive integer.

## 输入格式

The first line contains integer $ k $ $ (1<=k<=10^{6}) $ . The second line contains $ k $ integers $ a_{1},a_{2},...,a_{k} $ $ (1<=a_{i}<=10^{7}) $ .

## 输出格式

Print the minimum positive integer $ n $ , needed for the Empire to win.

Please, do not use the %lld to read or write 64-but integers in С++. It is preferred to use the cin, cout streams or the %I64d specificator.

## 样例 #1

### 输入

```
2
1000 1000

```

### 输出

```
2000
```

## 样例 #2

### 输入

```
1
2

```

### 输出

```
2
```

