---
title: "Game of the Year"
layout: "post"
diff: 提高+/省选-
pid: CF1783E
tag: ['数学', '贪心', '树状数组', '数论', '前缀和', 'ST 表']
---

# Game of the Year

## 题目描述

Monocarp 和 Polycarp 正在玩电脑游戏。游戏特点：$ n $ 个编号从 $ 1 $ 到 $ n $ 的BOSS。

他俩将用以下方式与BOSS战斗

- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- Monocarp 进行 $ k $ 次尝试撒掉boss;
- Polycarp 进行 $ k $ 次尝试撒掉boss;
- ...

Monocarp 在第 $ a_i $ 次尝试中撒掉了第 $ i $ 只BOSS。Polycarp 在第 $ b_i $ 次尝试中撒掉了第 $ i $ 只BOSS。其中一个人撒掉第 $ i $ 只BOSS后，他们就会尝试撒第 $ (i+1) $ 只BOSS。并且他们的尝试计数器都会清空。撒掉第 $ n $ 只BOSS后，游戏结束。

找到从$ 1 $ 到 $ n $所有的 $ k $ 值， 使得 Monocarp 可以杀死所有的BOSS。

## 输入格式

第一行输入一个整数 $ t $ ( $ 1 \le t \le 10^4 $ ) — 样例数。

每个样例第一行输入一个整数 $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — BOSS的数量。

每个样例第二行输入 $ n $ 个整数： $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ) — Monocarp 撒死每只BOSS的尝试次数。

每个样例第三行输入 $ n $ 个整数： $ b_1, b_2, \dots, b_n $ ( $ 1 \le b_i \le n $ ) — Polycarp 撒死每只BOSS的尝试次数。

所有测试样例的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ .

## 输出格式

对于每个样例输出两行。第一行应该包含一个正整数 $ \mathit{cnt} $ — 从 $ 1 $ 到 $ n $ 使得 Monocarp 可以撒死所有BOSS的 $ k $ 的总数。第二行应该包含 $ \mathit{cnt} $ 个正整数 — 所有 $ k $ 的值。

## 说明/提示

考虑最后一组测试样例

使 $ k = 1 $。首先，Monocarp经过1次尝试撒死第一只BOSS。成功，因为 $ a_1 = 1 $。 然后，Monocarp进行一次尝试撒死第二只BOSS。不成功，因为 $ a_2 > 1 $。于是，Polycarp尝试了一下。也不成功，因为 $ b_2 > 1 $。然后Monocarp进行了另一次尝试。仍然不成功，因为 $ a_2 > 2 $。直到Polycarp 在第三次尝试撒掉了BOSS。Monocarp没能撒掉BOSS。因此，$ k = 1 $ 不是答案。

使 $ k = 2 $ . Monocarp仍然在他的第一次尝试中撒死了BOSS。然后，他进行了两次不成功的尝试未能撒死BOSS。然后，Polycarp进行了两次不成功的尝试。然后，Monocarp进行了两次尝试，并且在第四次尝试中撒掉了BOSS。撒掉第三只BOSS的方法也类似。首先，Monocarp进行两次不成功的尝试。然后，Polycarp进行两次不成功的尝试。然后，Monocarp还有两次尝试机会，但在这两次机会中第一次就撒死了BOSS，因为 $ a_3 = 3 $。 第四只BOSS也被Monocarp撒死。因此，$ k = 2 $ 是答案。

## 样例 #1

### 输入

```
3
3
1 1 1
2 3 1
1
1
1
4
1 4 3 2
3 3 4 1
```

### 输出

```
3
1 2 3 
1
1 
2
2 4
```

