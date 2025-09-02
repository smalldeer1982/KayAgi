---
title: "Presents"
layout: "post"
diff: 入门
pid: CF136A
tag: ['模拟']
---

# Presents

## 题目描述

Little Petya very much likes gifts. Recently he has received a new laptop as a New Year gift from his mother. He immediately decided to give it to somebody else as what can be more pleasant than giving somebody gifts. And on this occasion he organized a New Year party at his place and invited $ n $ his friends there.

If there's one thing Petya likes more that receiving gifts, that's watching others giving gifts to somebody else. Thus, he safely hid the laptop until the next New Year and made up his mind to watch his friends exchanging gifts while he does not participate in the process. He numbered all his friends with integers from $ 1 $ to $ n $ . Petya remembered that a friend number $ i $ gave a gift to a friend number $ p_{i} $ . He also remembered that each of his friends received exactly one gift.

Now Petya wants to know for each friend $ i $ the number of a friend who has given him a gift.

## 输入格式

The first line contains one integer $ n $ ( $ 1<=n<=100 $ ) — the quantity of friends Petya invited to the party. The second line contains $ n $ space-separated integers: the $ i $ -th number is $ p_{i} $ — the number of a friend who gave a gift to friend number $ i $ . It is guaranteed that each friend received exactly one gift. It is possible that some friends do not share Petya's ideas of giving gifts to somebody else. Those friends gave the gifts to themselves.

## 输出格式

Print $ n $ space-separated integers: the $ i $ -th number should equal the number of the friend who gave a gift to friend number $ i $ .

## 样例 #1

### 输入

```
4
2 3 4 1

```

### 输出

```
4 1 2 3

```

## 样例 #2

### 输入

```
3
1 3 2

```

### 输出

```
1 3 2

```

## 样例 #3

### 输入

```
2
1 2

```

### 输出

```
1 2

```

