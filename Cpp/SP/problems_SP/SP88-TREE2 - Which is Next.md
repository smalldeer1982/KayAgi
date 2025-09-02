---
title: "TREE2 - Which is Next"
layout: "post"
diff: 难度0
pid: SP88
tag: []
---

# TREE2 - Which is Next

## 题目描述

每个学计算机科学的学生都知道二叉树。这里给出了一种定义二叉树的方法。二叉树可以通过递归的方式定义：一个二叉树 $t$ 可以是一个外部节点（即叶子节点），表示为 ![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png)，或者是一个有序对 $t = (t_1, t_2)$，表示一个有两个子树的内部节点 ![*](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/8b86f1a6f7d325580c5fe63e5997439bff5dde01.png)，其中 $t_1$ 是左子树，$t_2$ 是右子树。根据该定义，任何二叉树的节点数都是奇数。设 $B(n)$ 为所有节点数为 $n$ 的二叉树的集合，其中 $n$ 是奇数。

例如，$B(1)$ 只包含一棵树 ![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png)；$B(3)$ 包含 $B(3) = \{(![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png), ![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png))\}$；而 $B(5)$ 则有 $B(5) = \{(![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png), (![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png), ![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png))), ((![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png), ![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png)), ![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png))\}$。下面的图展示了 $B(5)$ 中的树。

![The trees B(5)](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/4dcd745415a0dae27058cbb400e718cb592d3be6.png)

记树 $t$ 的节点数为 $|t|$。给定一棵树 $t$，我们定义其唯一的整数标识符 $N(t)$ 如下：

- 对于叶子节点：$N(\text{![o](https://cdn.luogu.com.cn/upload/vjudge_pic/SP88/fd5cb50fba7f235c3ee3ab7b7d717c47554381b0.png)}) = 0$
- 对于内部节点：$N(t_1, t_2) = 2^{|t_1| + |t_2|} + 2^{|t_2|} \cdot N(t_1) + N(t_2)$

## 输入格式

输入的第一行包含一个整数 $t$，表示测试用例的数量。接下来有 $t$ 个测试用例。

每个测试用例的唯一一行包含一个整数 $n$（$0 \le n \le 2^{30}$），代表某棵二叉树 $t$ 的标识符。

## 输出格式

对于每个测试用例，输出一行，包含一个整数 $s$，表示在 $B(|t|)$ 集合中，$t$ 的下一个二叉树的标识符。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
1
20
```

### 输出

```
24
```

