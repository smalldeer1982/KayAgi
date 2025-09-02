---
title: "Scarborough Fair"
layout: "post"
diff: 入门
pid: CF897A
tag: ['模拟', '字符串']
---

# Scarborough Fair

## 题目描述

Are you going to Scarborough Fair?Parsley, sage, rosemary and thyme.

Remember me to one who lives there.

He once was the true love of mine.





Willem is taking the girl to the highest building in island No.28, however, neither of them knows how to get there.

Willem asks his friend, Grick for directions, Grick helped them, and gave them a task.

Although the girl wants to help, Willem insists on doing it by himself.

Grick gave Willem a string of length $ n $ .

Willem needs to do $ m $ operations, each operation has four parameters $ l,r,c_{1},c_{2} $ , which means that all symbols $ c_{1} $ in range $ [l,r] $ (from $ l $ -th to $ r $ -th, including $ l $ and $ r $ ) are changed into $ c_{2} $ . String is 1-indexed.

Grick wants to know the final string after all the $ m $ operations.

## 输入格式

The first line contains two integers $ n $ and $ m $ $ (1<=n,m<=100) $ .

The second line contains a string $ s $ of length $ n $ , consisting of lowercase English letters.

Each of the next $ m $ lines contains four parameters $ l,r,c_{1},c_{2} $ ( $ 1<=l<=r<=n $ , $ c_{1},c_{2} $ are lowercase English letters), separated by space.

## 输出格式

Output string $ s $ after performing $ m $ operations described above.

## 说明/提示

For the second example:

After the first operation, the string is wxxak.

After the second operation, the string is waaak.

After the third operation, the string is gaaak.

## 样例 #1

### 输入

```
3 1
ioi
1 1 i n

```

### 输出

```
noi
```

## 样例 #2

### 输入

```
5 3
wxhak
3 3 h x
1 5 x a
1 3 w g

```

### 输出

```
gaaak
```

