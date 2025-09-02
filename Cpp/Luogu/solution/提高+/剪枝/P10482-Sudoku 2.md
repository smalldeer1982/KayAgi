# Sudoku 2

## 题目描述

在数独游戏中，给定一个大的 9 × 9 网格，分成了较小的 3 × 3 子网格。例如，

![](https://cdn.luogu.com.cn/upload/image_hosting/acjiq3ud.png)

在给定网格中的一些数字后，你的目标是确定剩余的数字，使得数字 1 到 9 恰好出现在以下位置：(1) 九个 3 × 3 子网格中的每一个，(2) 九行中的每一个，以及 (3) 九列中的每一个。

## 样例 #1

### 输入

```
.2738..1..1...6735.......293.5692.8...........6.1745.364.......9518...7..8..6534.
......52..8.4......3...9...5.1...6..2..7........3.....6...1..........7.4.......3.
end```

### 输出

```
527389416819426735436751829375692184194538267268174593643217958951843672782965341
416837529982465371735129468571298643293746185864351297647913852359682714128574936```

# 题解

## 作者：wwxxbb (赞：12)

省流：此题解是 DLX 学习笔记，会详细地介绍 DLX。

篇幅较长，见谅。

## 1. 前言

X 算法是由 Donald E. Knuth 提出的，用 Dancing Links 优化，所以叫 DLX。

它用于解决精确覆盖问题和重复覆盖问题。重复覆盖问题还要配合 A* 剪枝。下面讲解精确覆盖问题。

精确覆盖问题的基本模型如下：

> 给定一个 $n$ 行 $m$ 列的矩阵，矩阵中每个元素要么是 $1$，要么是 $0$。
>
> 你需要在矩阵中挑选出若干行，使得对于矩阵的每一列 $j$，在你挑选的这些行中，有且仅有一行的第 $j$ 个元素为 $1$。

这里用 [OI wiki](https://oi-wiki.org/search/dlx/) 的例子。

假设矩阵为：
$$
\begin{pmatrix}
  0 & 0 & 1 & 0 & 1 & 1 & 0 \\
  1 & 0 & 0 & 1 & 0 & 0 & 1 \\
  0 & 1 & 1 & 0 & 0 & 1 & 0 \\
  1 & 0 & 0 & 1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 & 0 & 0 & 1 \\
  0 & 0 & 0 & 1 & 1 & 0 & 1
\end{pmatrix}
$$

普通的搜索复杂度是 $\mathcal{O}(2 ^ n \cdot nm)$ 或 $\mathcal{O}(2 ^ n \cdot m)$ 的，$n, m$ 的范围都不会太大。但是用 DLX 解决 $n, m$ 范围可以达到 $500$ 甚至更大。

## 2. X 算法

### 2.1 算法流程

X 算法的流程如下：

1. 选择第一行，将它删除，并将所有 $1$ 所在的列打上标记；

$$
\begin{pmatrix}
  \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
  1 & 0 & \color{Red}0 & 1 & \color{Red}0 & \color{Red}0 & 1 \\
  0 & 1 & \color{Red}1 & 0 & \color{Red}0 & \color{Red}1 & 0 \\
  1 & 0 & \color{Red}0 & 1 & \color{Red}0 & \color{Red}0 & 0 \\
  0 & 1 & \color{Red}0 & 0 & \color{Red}0 & \color{Red}0 & 1 \\
  0 & 0 & \color{Red}0 & 1 & \color{Red}1 & \color{Red}0 & 1
  \end{pmatrix}
$$

2. 选择所有被标记的列，将它们删除，并将这些列中含 $1$ 的行打上标记（重复覆盖问题无需打标记）；

$$
\begin{pmatrix}
  \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
  1 & 0 & \color{Red}0 & 1 & \color{Red}0 & \color{Red}0 & 1 \\
  \color{Green}0 & \color{Green}1 & \color{Red}1 & \color{Green}0 & \color{Red}0 & \color{Red}1 & \color{Green}0 \\
  1 & 0 & \color{Red}0 & 1 & \color{Red}0 & \color{Red}0 & 0 \\
  0 & 1 & \color{Red}0 & 0 & \color{Red}0 & \color{Red}0 & 1 \\
  \color{Green}0 & \color{Green}0 & \color{Red}0 & \color{Green}1 & \color{Red}1 & \color{Red}0 & \color{Green}1
\end{pmatrix}
$$

3. 选择所有被标记的行，将它们删除；

   $$
   \begin{pmatrix}
     \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
     1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 1 \\
     \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
     1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 0 \\
     0 & 1 & \color{Blue}0 & 0 & \color{Blue}0 & \color{Blue}0 & 1 \\
     \color{Blue}0 & \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1
   \end{pmatrix}
   $$

    于是得到一个新的小 01 矩阵：

$$
\begin{pmatrix}
  1 & 0 & 1 & 1 \\
  1 & 0 & 1 & 0 \\
  0 & 1 & 0 & 1
\end{pmatrix}
$$

4. 选择第一行（原来的第二行），将它删除，并将所有 $1$ 所在的列打上标记；

$$
\begin{pmatrix}
  \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
  \color{Red}1 & 0 & \color{Red}1 & \color{Red}0 \\
  \color{Red}0 & 1 & \color{Red}0 & \color{Red}1
\end{pmatrix}
$$

5. 选择所有被标记的列，将它们删除，并将这些列中含 $1$ 的行打上标记；

   $$
   \begin{pmatrix}
     \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
     \color{Red}1 & \color{Green}0 & \color{Red}1 & \color{Red}0 \\
     \color{Red}0 & \color{Green}1 & \color{Red}0 & \color{Red}1
   \end{pmatrix}
   $$

6. 选择所有被标记的行，将它们删除；

   $$
   \begin{pmatrix}
     \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
     \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
     \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1
   \end{pmatrix}
   $$

   这样就得到了一个空矩阵。但是上次删除的行 `1 0 1 1` 不是全 $1$ 的，说明选择有误；

7. 回溯到步骤 4，考虑选择第二行（原来的第四行），将它删除，并将所有 $1$ 所在的列打上标记；

   $$
   \begin{pmatrix}
     \color{Red}1 & 0 & \color{Red}1 & 1 \\
     \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
     \color{Red}0 & 1 & \color{Red}0 & 1
   \end{pmatrix}
   $$

8. 选择所有被标记的列，将它们删除，并将这些列中含 $1$ 的行打上标记；

   $$
   \begin{pmatrix}
     \color{Red}1 & \color{Green}0 & \color{Red}1 & \color{Green}1 \\
     \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
     \color{Red}0 & 1 & \color{Red}0 & 1
   \end{pmatrix}
   $$

9. 选择所有被标记的行，将它们删除；

   $$
   \begin{pmatrix}
     \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
     \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
     \color{Blue}0 & 1 & \color{Blue}0 & 1
     \end{pmatrix}
   $$

   于是我们得到了这样的一个矩阵：

   $$
   \begin{pmatrix}
     1 & 1
   \end{pmatrix}
   $$

10. 此时第一行（原来的第五行）有 $2$ 个 $1$，将它们全部删除，得到一个空矩阵，由于上一次删除的时候，删除的是全 $1$ 的行，因此成功。

答案即为被删除的三行：$1, 4, 5$。

### 2.2 步骤讲解

看起来挺直观的，但为什么是这样的？

首先不考虑无解的情况，我们选了第一行，所以这一行为 $1$ 的列里不能有 $1$，所以把有 $1$ 的列删掉。

列中有 $1$ 的行如果也选的话，就会有多个 $1$ 在同一列，所以要删掉。

这就是一次操作。

我们发现，一次操作已经决定了一些列，这里的决定是指这一列已经有 $1$ 且确定了，于是我们可以对得到的小矩阵进行递归操作继续决定剩下的列。

### 2.3 无解情况

第 $6$ 步里说上次删的一行不全为 $1$ 所以无解，这又是为什么呢？

这是由于此次操作中这个小矩阵的第二列没有 $1$，不符合题目要求。

所以我们判断无解的情况就是看上一次删除的行是否全为 $1$。

注意，这个删除指的是我们主动选这一行删，而不是在删完这一行后被动地将有 $1$ 的行删掉。

## 3. Dancing Links

发现 X 算法需要大量的删除和恢复行和列的操作。

我们可以用双向十字链表来优化。

而在双向十字链表上不断跳跃的过程被形象地比喻成「跳跃」，因此被用来优化 X 算法的双向十字链表也被称为「Dancing Links」。

### 3.1 双向十字链表

双向十字链表中存在四个指针域，分别指向上、下、左、右的元素，且每个元素 $i$ 在整个双向十字链表系中都对应着一个格子，因此还要表示 $i$ 所在的列和所在的行，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/m7csaa92.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/n2jihqpd.png)

上图就是一个 DLX。DLX 中的元素有 $4$ 中，下面一一介绍。

1. 总表头 (head)

   有且只有一个，作用是方便 DLX 运作。可以通过 DLX 的右节点是否为空判断是否有解。

2. 元素节点 (idx)

   如上图的 $0 \sim 15$，它们表示矩阵中的 $1$。是的，DLX 只需要存 $1$ 就够了。

   一是因为只存 $1$ 方便我们判断；二是因为能用 DLX 解决的问题 $1$ 的数量都比较少，换句话说，这是一个稀疏矩阵，占用内存较少。

3. 行节点 (row) 和列节点 (col)

   它们的作用也是方便 DLX 运作。

我们再将 X 算法的过程用 Dancing Links 模拟一遍：

1. 判断 `head.right == head` 。如果等于，说明求出解，输出答案并返回 `true`；否则，继续。
2. 取列元素 `p = head.right` 。
3. 遍历列元素所在列链，选择一行。
4. 删除与该行链元素冲突的行列，得到一个新的 DLX 。
5. 如果新的 DLX 中仍有列元素且列链为空，则返回 `false` ；否则跳转步骤 1。
6. 如果选择该行后未求得解，则回溯到当前状态，选择下一行，跳转步骤 5。如果所有行都遍历过仍未求得解，说明之前有行选择错误或无解，返回 `false` 。
7. 如果最终函数返回值为 `false` ，则无解。

下面讲一下 DLX 的几个操作。

### 3.2 变量含义

```cpp
#define jump(i, p, x) for (int i = p[x]; i != x; i = p[i])
// 用这个宏定义只是为了方便
// 由于我们的链表是循环链表，所以遍历的时候可以一直朝一个方向跳
const int N = 100010; // 我们数组开的大小是 1 的个数 + 列的个数，这里只是一个参考
int n, m, idx;
// n、m 存储 DLX 的大小，下文会讲解如何计算 DLX 大小
// idx 存储的是点的编号
int u[N], d[N], l[N], r[N], first[N];
// u、d、l、r 是每一个点的上、下、左、右点的编号
// first 是每一行第一个元素，方便下面的插入操作
int row[N], col[N], s[N];
// row 和 col 记录的是第 idx 号元素对应在原矩阵的行和列
// s 是每一列的 1 的个数，可以优化 DLX，下面会讲
int ans[N], tot;
// 这是栈，用了存储答案
```

### 3.3 创建 (build)

```cpp
void build(int x, int y) { // 创建一个 x 行 y 列的 DLX
  	n = x, m = y, tot = 0;
	for (int i = 0; i <= m; i ++)
    	u[i] = d[i] = i, l[i] = i - 1, r[i] = i + 1;
    	// 初始的时候 DLX 只有一行，上下节点都是自己，左节点是 i - 1，右节点是 i + 1
  	l[0] = m, r[m] = 0, idx = m + 1; // 0 号点的左边是 m，m 号点的右边是 0，总共有 m + 1 个点
    // 这样可以保证水平、竖直方向上都是循环链表
  	memset(s, 0, sizeof s), memset(first, 0, sizeof first);
}
```

建完之后的 DLX 长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/m3u0lanu.png)

### 3.4 插入 (add)

```cpp
void add(int i, int j) { // 在第 i 行 第 j 列插入一个 1
    row[++ idx] = i, col[idx] = j, s[j] ++;
    // idx ++ 表示元素数量加 1，当前元素编号为 idx
    // 记录行和列，这一列的 1 的数量加 1
    u[idx] = j, d[idx] = d[j], u[d[j]] = idx, d[j] = idx;
    if (!first[i]) first[i] = l[idx] = r[idx] = idx;
    else l[idx] = first[i], r[idx] = r[first[i]], l[r[first[i]]] = idx, r[first[i]] = idx;
}
```

由于链表的插入有些抽象，下面借助图示讲解。

![](https://cdn.luogu.com.cn/upload/image_hosting/m7csaa92.png)

我们先考虑竖直方向。

我们要把 $idx$ 插入到 $c$ 的正下方：

- $idx$ 下方的结点为原来 $c$ 的下结点；
- $idx$ 下方的结点（即原来 $c$ 的下结点）的上结点为 $idx$;
- $idx$ 的上结点为 $c$；
- $c$ 的下结点为 $idx$。

写成代码就是：

```cpp
u[idx] = j, d[idx] = d[j], u[d[j]] = idx, d[j] = idx; // 这里不建议写连等，可能会挂
```

变量名有些不一样，见谅。

水平方向要分情况讨论：

- 第 $r$ 行没有元素，即 `first[r] = 0`，此时这一行的第一个元素就是 $idx$，即 `first[r] = idx`。由于是循环链表，所以 $idx$ 的左边右边都是 $idx$，写成代码就是：

```cpp
if (!first[i]) first[i] = l[idx] = r[idx] = idx;
```

- 第 $r$ 行有元素，我们把 $idx$ 插到 `first[r]` 的正右方：
  - $idx$ 右侧的结点为原来 `first[r]` 的右结点；
  - 原来 `first[r]` 右侧的结点的左结点为 $idx$；
  - $idx$ 的左结点为 `first[r]`；
  - `first[r]` 的右结点为 $idx$。

```cpp
else l[idx] = first[i], r[idx] = r[first[i]], l[r[first[i]]] = idx, r[first[i]] = idx;
// 这里的 else 和上面的 if 是匹配的
```

合起来就是上面的代码。

### 3.5 递归 (dance)

函数 `dance` 的类型是 `bool`，因为要判无解。

下面代码先抛出两个操作：

- 删除 (delete)
- 撤销 (undo)

用于删除一列和恢复一列。

```cpp
bool dance() {
    if (!r[0]) return 1;
    // 如果 0 号结点没有右结点，那么矩阵为空，则有解
    // 这就是总表头 0 号点的作用
    int p = r[0];
    jump(i, r, 0) if (s[i] < s[p])
        p = i;
    // 这就是上面说到的优化，每次删去 1 个数最少的一列，类似高斯消元，这样能保证程序具有一定的启发性，使搜索树分支最少
    del(p); // 把这一列删掉
    jump(i, d, p) { // 遍历删除的那一列
        ans[++ tot] = row[i]; // 记录当前删去的行
        jump(j, r, i) del(col[j]); // 删去当前列有 1 的行
        // 我们删除行的时候是遍历这一行的所有列，再把这一列删掉
        // 这就是 DLX 里面只存 1 的好处，不需要任何判断，直接删就完了
        if (dance()) return 1; // 递归下一层，如果有解，就返回 true
        jump(j, l, i) undo(col[j]); // 恢复这一行
        // 重点！！！我们在恢复的时候，怎么删的，就要怎么反过来恢复，操作的顺序也要反过来，在两个函数里面也是一样的
        // 如果不反过来，在一些题目会死循环，下面有原因
        tot --; // 回溯
    }
    // 如果程序运行到这里，就说明当前删的这行会导致无解，所以返回 false 并恢复这一列
    undo(p);
    return 0;
}
```

#### 3.5.1 关于恢复操作的方向的问题

结论：恢复的顺序要与删除的顺序相反，操作的顺序也要相反。

这由删除函数和恢复函数的性质决定，注意删除列 $c$ 时，$c$ 列中的 u 和 d 都没有更改，这样做的目的是方便恢复。所以在接下来的操作中，$c$ 列中的 u 和 d 也不能变。

考虑依次删除的列 $c_1$，$c_2$，且它们包含同一行，那么删 $c_2$ 时，$c_1$ 的 u，d 就变了！所以在恢复时应先恢复 $c_2$ 再恢复 $c_1$，否则链表指针会错乱，引起死循环。

### 3.6 删除 (delete)

`delete(p)` 表示在 DLX 中删除第 $p$ 列以及与其相关的行和列。

```cpp
void del(int p) {
    r[l[p]] = r[p], l[r[p]] = l[p];
    /* 这里同样是对链表进行操作，可以这样理解：
     p 左侧的结点的右结点应为 p 的右结点
     p 右侧的结点的左结点应为 p 的左结点
    */
    jump(i, d, p) // 顺着这一列往下走，把走过的每一行都删掉
        jump(j, r, i) { // 遍历当前行的每一列
        u[d[j]] = u[j], d[u[j]] = d[j];
        /*
        j 上方的结点的下结点应为 j 的下结点。
		j 下方的结点的上结点应为 j 的上结点。
        */
        s[col[j]] --;
        // 每一列的元素个数要减 1
    }
}
```

配上图片理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/8eriixmz.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/4vcjeg1q.png)

### 3.7 撤销 (undo)

`undo(p)` 表示在 DLX 中还原第 $p$ 列以及与其相关的行和列。

注意操作顺序要与删除时相反，原因上面讲过。

```cpp
void undo(int p) {
    jump(i, u, p) // 注意这里
        jump(j, l, i) { // 注意这里
        d[u[j]] = u[d[j]] = j;
        s[col[j]] ++;
    }
    r[l[p]] = l[r[p]] = p; // 还有这里
}
```

[模板题](https://www.luogu.com.cn/problem/P4929)代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DLX {
    #define jump(i, p, x) for (int i = p[x]; i != x; i = p[i])
    static const int N = 5000 + 500 + 10;
    // 上面讲过，数组大小是 1 的个数 + 列的个数
    // 在模版题里，1 的个数是 5000，列有 500，加了 10 是为了防止越界
    // 其实不用那么精打细算，多开一点更保险

    int n, m, idx;
    int u[N], d[N], l[N], r[N], first[N];
    int s[N], row[N], col[N];
    int ans[N], tot;
    
    void build() {
        tot = 0;
        for (int i = 0; i <= m; i ++)
            u[i] = d[i] = i, l[i] = i - 1, r[i] = i + 1;
        l[0] = m, r[m] = 0, idx = m + 1;
        memset(s, 0, sizeof s), memset(first, 0, sizeof first);
    }

    void add(int i, int j) {
        row[++ idx] = i, col[idx] = j, s[j] ++;
        u[idx] = j, d[idx] = d[j], u[d[j]] = idx, d[j] = idx;
        if (!first[i]) first[i] = l[idx] = r[idx] = idx;
        else l[idx] = first[i], r[idx] = r[first[i]], l[r[first[i]]] = idx, r[first[i]] = idx;
    }

    void del(int p) {
        l[r[p]] = l[p], r[l[p]] = r[p];
        jump(i, d, p)
            jump(j, r, i) {
                s[col[j]] --;
                u[d[j]] = u[j], d[u[j]] = d[j];
            }
    }

    void undo(int p) {
        jump(i, u, p)
            jump(j, l, i) {
                d[u[j]] = u[d[j]] = j;
                s[col[j]] ++;
            }
        r[l[p]] = l[r[p]] = p;
    }
    
    bool dance() {
        if (!r[0]) return 1;
        int p = r[0];
        jump(i, r, 0) if (s[i] < s[p])
            p = i;
        del(p);
        jump(i, d, p) {
            ans[++ tot] = row[i];
            jump(j, r, i) del(col[j]);
            if (dance()) return 1;
            jump(j, l, i) undo(col[j]);
            tot --;
        }
        undo(p);
        return 0;
    }
} X;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> X.n >> X.m;
    X.build();
    for (int i = 1; i <= X.n; i ++)
        for (int j = 1, x; j <= X.m; j ++) {
            cin >> x;
            if (x) X.add(i, j);
        }
    if (X.dance()) for (int i = 1; i <= X.tot; i ++)
        cout << X.ans[i] << ' ';
    else cout << "No Solution!";
    return 0;
}
```

封装了 DLX 模版，需要自取。

## 4. 建模

DLX 的难点，不全在于链表的建立，而在于建模。

**请确保已经完全掌握 DLX 模板后再继续阅读下文。**

我们每拿到一个题，应该考虑行和列所表示的意义：

- 行表示 **决策**，因为每行对应着一个集合，也就对应着选或不选；
- 列表示 **状态**，因为每一列对应着某个条件。

对于某一行而言，由于不同的列的值不相同，我们 **由不同的状态，定义了一个决策**。

## 5. 例题

[P1784 数独](https://www.luogu.com.cn/problem/P1784)。

#### 思路

行代表问题的所有情况，列代表问题的约束条件。每个格子能够填的数字为 $[1, 9]$，并且总共有 $9 \times 9$ 个格子，所以总的情况数为 $729$ 种。也就是 DLX 有 $729$ 行。列则分为四种：

1. $[1, 81]$ 列分别对应了 $9$ 行，每行共 $9$ 个数字的放置情况；
2. $[82, 162]$ 列分别对应了 $9$ 列，每列共 $9$ 个数字的放置情况；
3. $[163, 243]$ 列分别对应了 $9$ 个宫，每个宫共 $9$ 个数字的放置情况；
4. $[244, 324)$ 列 分别对应了 $81$ 个格子是否被放置了数字。

所以总的列数为 $4 \times 81 = 324$ 列。

即我们建立的 DLX 大小为 $729 \times 324$，$1$ 的个数为 $729 \times 4 = 2916$ 个。

注意：搜索题比较玄学，有些时候 TLE 了可以改变不同范围内决策的顺序，比如说，我们可以让 $[1, 81]$ 列决定宫，$[163, 243]$ 列决定行。

#### 参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int res[10][10]; // 存储输入和答案

struct DLX {
    #define jump(i, p, x) for (int i = p[x]; i ^ x; i = p[i])
    static const int N = 9 * 9 * 9 * 4 + 9 * 9 * 4 + 10;
    // 这里数组开 2916 + 324。我多开了个 10

    int n, m, idx;
    int u[N], d[N], l[N], r[N], first[N];
    int s[N], row[N], col[N];
    int ans[N], tot;
    
    void build(int x, int y) {
        n = x, m = y;
        for (int i = 0; i <= m; i ++)
            u[i] = d[i] = i, l[i] = i - 1, r[i] = i + 1;
        l[0] = m, r[m] = 0, idx = m + 1;
    }

    void add(int i, int j) {
        row[++ idx] = i, col[idx] = j, s[j] ++;
        u[idx] = j, d[idx] = d[j], d[j] = u[d[j]] = idx;
        if (!first[i]) first[i] = l[idx] = r[idx] = idx;
        else l[idx] = first[i], r[idx] = r[first[i]], l[r[first[i]]] = idx, r[first[i]] = idx;
    }

    void del(int p) {
        l[r[p]] = l[p], r[l[p]] = r[p];
        jump(i, d, p)
            jump(j, r, i) {
                s[col[j]] --;
                u[d[j]] = u[j], d[u[j]] = d[j];
            }
    }

    void undo(int p) {
        jump(i, u, p)
            jump(j, l, i) {
                d[u[j]] = u[d[j]] = j;
                s[col[j]] ++;
            }
        r[l[p]] = l[r[p]] = p;
    }
    
    bool dance() {
        if (!r[0]) {
            for (int i = 1; i <= tot; i ++) {
                int x = (ans[i] - 1) / 81 + 1;
                int y = (ans[i] - 1) / 9 % 9 + 1;
                int v = (ans[i] - 1) % 9 + 1;
                res[x][y] = v; // 这里是根据行号利用公式决定行、列和数字
            }
            return 1;
        }
        int p = r[0];
        jump(i, r, 0) if (s[i] < s[p])
            p = i;
        del(p);
        jump(i, d, p) {
            ans[++ tot] = row[i];
            jump(j, r, i) del(col[j]);
            if (dance()) return 1;
            jump(j, l, i) undo(col[j]);
            tot --;
        }
        undo(p);
        return 0;
    }
} X;

void insert(int r, int c, int x) { // 在第 r 行第 c 列放置 x 数字
    int id = (r - 1) * 81 + (c - 1) * 9 + x; // 计算行号
    int n1 = (r - 1) * 9 + x; // 行
    int n2 = (c - 1) * 9 + x + 81; // 列
    int n3 = ((r - 1) / 3 * 3 + (c - 1) / 3) * 9 + x + 162; // 宫
    int n4 = (r - 1) * 9 + c + 243; // 格子
    // 公式可以自己去推
    X.add(id, n1);
    X.add(id, n2);
    X.add(id, n3);
    X.add(id, n4);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    X.build(729, 324);
    for (int i = 1; i <= 9; i ++) {
        for (int j = 1; j <= 9; j ++) {
            cin >> res[i][j];
            if (res[i][j]) insert(i, j, res[i][j]); // 如果不为 0，则只有 1 种决策
            else for (int k = 1; k <= 9; k ++) insert(i, j, k); // 否则有 9 种决策
        }
    }
    X.dance();
    for (int i = 1; i <= 9; i ++, cout << '\n')
        for (int j = 1; j <= 9; j ++)
            cout << res[i][j] << ' ';
    return 0;
}
```

多倍经验：

- [P1074 靶形数独](https://www.luogu.com.cn/problem/P1074)

- [P10481 Sudoku](https://www.luogu.com.cn/problem/P10481)
- [P10482 Sudoku 2](https://www.luogu.com.cn/problem/P10482)

- [SP1110 Sudoku](https://www.luogu.com.cn/problem/SP1110)

- [UVA1309 Sudoku](https://www.luogu.com.cn/problem/UVA1309)

其中 P1074 要加权值；P10482 多测记得清空清干净；SP1110 和 UVA1309 数独边长为 $16$，将与 $9$ 有关的改成 $16$ 即可。

要代码的可以私信我。

## 参考资料

- [OI wiki](https://oi-wiki.org/search/dlx/)
- ~~个人理解~~

---

## 作者：Ivan422 (赞：3)

如果你按照这篇题解打完了代码，那么恭喜你，你可以通过修改少数字符通过一道黑题。

用位运算，记录每一个数在行和列的占用情况。

接着搜索。


1. 首先选择了可能答案最少的点搜索。但是为了给其他减值留出发挥空间，只优先考虑唯一解，剩下的在 $bestcnt$ 中记录。
2. 找到行唯一点填写。
3. 找到列唯一点填写。
4. 找到宫唯一点填写。
5. 把刚刚在 $bestcnt$ 中的点存下来枚举了。

注意位运算的处理和读入，以及枚举答案，位置不要错了。

~~因为这个东西实在没什么写的，具体看可读性超高的代码和注释，祝你水黑平安。~~

---

这个东西代码好长。

```cpp
// ExFish UVA1309 Solution Version 1
#include<bits/stdc++.h>
using namespace std;
const int N=10,M=1<<9,AZ=9,GZ=3;
char STA='1',SPA='.';
string s;
int LOG[M],mx_dfs,popc[M];
char a[N][N];
int can_put_in[N][N]; // Can Put In A Number: BIN

inline void put_a_number_in(int x,int y,int z){ // Put Number
	for(int i=1;i<=AZ;i++){
		can_put_in[x][i]&=~(1<<z); // Row Can't Put In
		can_put_in[i][y]&=~(1<<z); // Col Can't Put In
	}
	// Case Can't Put In
	int case_x=(x-1)/GZ*GZ+1,case_y=(y-1)/GZ*GZ+1;
	for(int i=case_x;i<case_x+GZ;i++)for(int j=case_y;j<case_y+GZ;j++){
		can_put_in[i][j]&=~(1<<z);
	}
}
bool dfs(int last_block_cnt){ // Dfs
	if(last_block_cnt==0){ // Find A Solution
		for(int i=1;i<=AZ;i++)printf("%s",a[i]+1);
		printf("\n");
		return 1;
	}
	int now_can_put_in[N][N];
	memcpy(now_can_put_in,can_put_in,sizeof(now_can_put_in));
	int the_best_cnt=AZ+1,the_best_x,the_best_y;
	// 1. Find Only & Now Search The Best
	for(int i=1;i<=AZ;i++){
		for(int j=1;j<=AZ;j++){
			if(a[i][j]!=SPA)continue; // There is a number
			if(can_put_in[i][j]==0)return 0; // No Answer
			if(popc[can_put_in[i][j]]==1){ // Only One
				a[i][j]=LOG[can_put_in[i][j]]+STA;
				put_a_number_in(i,j,LOG[can_put_in[i][j]]); // Put In
				if(dfs(last_block_cnt-1))return 1; // Dfs
				a[i][j]=SPA; // Wrong, This Solution Need To Destroyed
				memcpy(can_put_in,now_can_put_in,sizeof(now_can_put_in));
				return 0; // Destroyed
			}
			if(popc[can_put_in[i][j]]<the_best_cnt){ // Search The Best
				the_best_cnt=popc[can_put_in[i][j]];
				the_best_x=i;
				the_best_y=j;
			}
		}
	}
	// 2. Find The Best Col
	for(int i=1;i<=AZ;i++){
		int this_col=0,need_to_solve=0;
		for(int j=1;j<=AZ;j++){
			if(a[i][j]==SPA)need_to_solve++; // Find Need To Solve Place
			else this_col|=(1<<(a[i][j]-STA)); // Mark It
		}
		if(need_to_solve==0)continue; // Full
		for(int x=0;x<AZ;x++){ // Number
			if((this_col>>x)&1)continue; // Full
			int want_to_put=0,put_position=0;
			for(int j=1;j<=AZ;j++){
				if(a[i][j]!=SPA)continue; // There is a number
				if(((can_put_in[i][j]>>x)&1)==0)continue; // Can't Put It
				want_to_put++;
				put_position=j;
				if(want_to_put>1)break; // Can't Solve It
			}
			if(want_to_put==0)return 0; // All Kill
			if(want_to_put!=1)continue; // Can't Solve It
			a[i][put_position]=x+STA;
			put_a_number_in(i,put_position,x); // Put In
			if(dfs(last_block_cnt-1))return 1; // Dfs
			a[i][put_position]=SPA; // Wrong, This Solution Need To Destroyed
			memcpy(can_put_in,now_can_put_in,sizeof(now_can_put_in));
			return 0; // Destroyed
		}
	}
	// 3. Find The Best Row
	for(int i=1;i<=AZ;i++){
		int this_row=0,need_to_solve=0;
		for(int j=1;j<=AZ;j++){
			if(a[j][i]==SPA)need_to_solve++; // Find Need To Solve Place
			else this_row|=(1<<(a[j][i]-STA)); // Mark It
		}
		if(need_to_solve==0)continue; // Full
		for(int x=0;x<AZ;x++){ // Number
			if((this_row>>x)&1)continue; // Full
			int want_to_put=0,put_position=0;
			for(int j=1;j<=AZ;j++){
				if(a[j][i]!=SPA)continue; // There is a number
				if(((can_put_in[j][i]>>x)&1)==0)continue; // Can't Put It
				want_to_put++;
				put_position=j;
				if(want_to_put>1)break; // Can't Solve It
			}
			if(want_to_put==0)return 0; // All Kill
			if(want_to_put!=1)continue; // Can't Solve It
			a[put_position][i]=x+STA;
			put_a_number_in(put_position,i,x); // Put In
			if(dfs(last_block_cnt-1))return 1; // Dfs
			a[put_position][i]=SPA; // Wrong, This Solution Need To Destroyed
			memcpy(can_put_in,now_can_put_in,sizeof(now_can_put_in));
			return 0; // Destroyed
		}
	}
	// GZ. Find The Best Case
	for(int x=1;x<=AZ-GZ+1;x+=GZ)for(int y=1;y<=AZ-GZ+1;y+=GZ){
		int this_case=0,need_to_solve=0;
		for(int i=x;i<x+GZ;i++)for(int j=y;j<y+GZ;j++){
			if(a[i][j]==SPA)need_to_solve++; // Find Need To Solve Place
			else this_case|=(1<<(a[i][j]-STA)); // Mark It			
		}
		if(need_to_solve==0)continue; // Full
		for(int k=0;k<AZ;k++){
			if((this_case>>k)&1)continue; // Full
			int want_to_put=0,put_position_x=0,put_position_y=0;			
			for(int i=x;i<x+GZ;i++)for(int j=y;j<y+GZ;j++){
				if(a[i][j]!=SPA)continue; // There is a number
				if(((can_put_in[i][j]>>k)&1)==0)continue; // Can't Put It
				want_to_put++;
				put_position_x=i,put_position_y=j;
			}			
			if(want_to_put==0)return 0; // All Kill
			if(want_to_put!=1)continue; // Can't Solve It
			a[put_position_x][put_position_y]=k+STA;
			put_a_number_in(put_position_x,put_position_y,k); // Put In
			if(dfs(last_block_cnt-1))return 1; // Dfs
			a[put_position_x][put_position_y]=SPA; // Wrong, This Solution Need To Destroyed
			memcpy(can_put_in,now_can_put_in,sizeof(now_can_put_in));
			return 0; // Destroyed
		}		
	}
	// Last Search
	for(int i=can_put_in[the_best_x][the_best_y];i;i-=i&-i){
		int number=LOG[i&-i];
		a[the_best_x][the_best_y]=number+STA;
		put_a_number_in(the_best_x,the_best_y,number); // Put In
		if(dfs(last_block_cnt-1))return 1; // Dfs
		a[the_best_x][the_best_y]=SPA; // Wrong, This Solution Need To Destroyed
		memcpy(can_put_in,now_can_put_in,sizeof(now_can_put_in));
	}
	return 0; // Destroyed
}
int _;
string sss;
int main(){
	for(int i=0;i<AZ;i++)LOG[1<<i]=i;
	for(int i=0;i<(1<<AZ);i++)for(int j=i;j;j-=j&-j)popc[i]++;
	while(cin>>sss){ // Input The Sudoku
		if(sss=="end")break;
		++_;
		for(int i=1;i<=AZ;i++)for(int j=1;j<=AZ;j++)a[i][j]=sss[(i-1)*AZ+j-1];
		for(int i=1;i<=AZ;i++)for(int j=1;j<=AZ;j++)can_put_in[i][j]=(1<<AZ)-1;
		mx_dfs=0;
		for(int i=1;i<=AZ;i++)for(int j=1;j<=AZ;j++){
			if(a[i][j]==SPA)mx_dfs++;
			else put_a_number_in(i,j,a[i][j]-STA);
		}
		if(!dfs(mx_dfs))assert(0);
	}
	return 0;
}
```

---

## 作者：chenhanzheapple (赞：3)

# 前言

本文由 [chenhanzheapple](https://www.luogu.com.cn/user/895479) 和 [kexun_kevin](https://www.luogu.com.cn/user/674527) 编写完成，其中第一部分由 [kexun_kevin](https://www.luogu.com.cn/user/674527) 编写完成。第二部分由 [chenhanzheapple](https://www.luogu.com.cn/user/895479) 编写完成。因此代码风格不同。

# 搜索

## 朴素 dfs

想要解决数独问题，我们不难想到可以在每个位置逐个
枚举所有数字，可以使用 **dfs 算法**。该算法并非本文主题，故仅附一份暴力代码供参考。

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int a[15][15];
bool r[15][15], c[15][15], g[15][15];

void print()
{
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
			cout << a[i][j] << ' ';
		cout << '\n';
	}
}

bool chk()
{
	memset(r, false, sizeof r);
	memset(c, false, sizeof c);
	memset(g, false, sizeof g);
	for (int i = 1; i <= 9; ++i)
		for (int j = 1; j <= 9; ++j)
		{
			int x = a[i][j];
			if (r[i][x] || c[j][x] || g[(i-1)/3*3+(j-1)/3+1][x]) return false;
			r[i][x] = c[j][x] = g[(i-1)/3*3+(j-1)/3+1][x] = true;
		}
	return true;
}

void dfs(int x, int y)
{
	if (a[x][y])
	{
		if (x == 9 && y == 9)
		{
			if (chk())
			{
				print();
				exit(0);
			}
		}
		else if (y == 9) dfs(x+1, 1);
		else dfs(x, y+1);
		return;
	}
	for (int i = 1; i <= 9; ++i)
	{
		a[x][y] = i;
		if (x == 9 && y == 9)
		{
			if (chk())
			{
				print();
				exit(0);
			}
		}
		else if (y == 9) dfs(x+1, 1);
		else dfs(x, y+1);
		a[x][y] = 0;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for (int i = 1; i <= 9; ++i)
		for (int j = 1; j <= 9; ++j)
			cin >> a[i][j];
	dfs(1, 1);
	return 0;
}
```

可以发现该方法时间复杂度极高，所以必然不可行，因此需要剪枝。

## 剪枝

### 定义

**剪枝是一种常见的搜索优化方式。**

dfs 的搜索过程可呈现为一棵树，我们称之为 dfs 树，过程中每个选择都会对应其中的一个子树。  

然而对一些选择后对最后结果一定没有任何价值的选项，我们自然而然地可以排除他们。具体的，我们应去除其对应子树，避免浪费时间。

### 可行性剪枝

可行性剪枝是最直观、基础的剪枝方式，具体来说就是去除掉不符合规则的选项。 

在数独这个问题中，其具体表现如下：

$$
\begin{pmatrix}
8 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0\\
0 & 0 & 3 & 6 & 0 & 0 & 0 & 0 & 0\\  
0 & 7 & 0 & 0 & 9 & 0 & 2 & 0 & 0\\  
0 & 5 & 0 & 0 & 0 & 7 & 0 & 0 & 0\\  
0 & 0 & 0 & 0 & 4 & 5 & 7 & 0 & 0\\  
0 & 0 & 0 & 1 & 0 & 0 & 0 & 3 & 0\\  
0 & 0 & 1 & 0 & 0 & 0 & 0 & 6 & 8\\  
0 & 0 & 8 & 5 & 0 & 0 & 0 & 1 & 0\\  
0 & 9 & 0 & 0 & 0 & 0 & 4 & 0 & 0
\end{pmatrix}
$$

其中 $0$ 表示未填数。

在该数独中，如果我们在 $(1,2)$ 的位置填入数字 $8$ ，显然违反规则，所以该选项不用考虑。然而在上文所给代码中，该选项被试验了一遍，大大降低了效率，如果我们使用剪枝便可加快速度。

具体地，可以添加如下代码优化：

```cpp
for (int i = 1; i <= 9; ++i)
{
   if (r[x][i] || c[y][i] || g[id[x][y]][i]) continue;
}
```
其中 $r,c,g,id$ 分别为行、列、宫已选择数字和该位置对应宫号。

### 最优性剪枝

最优性剪枝也是一种较好理解的方式，具体为如果题目要求解最大、最小值等类型时，一旦目前所得数值大于已经求出的最优解，且后续数值离最优越来越远时，就可以停止搜索。  

不过在数独问题中，我们无须利用此方法，故不做深入讲解。

### 重复性剪枝

这类剪枝的想法在于，如果你搜索到某一部分，发现这与之前已经计算过的某个方案完全等效，那我们就可以停止枚举，直接调用之前的结果。  

不过这类剪枝在数独问题中也没有太大应用。

### 搜索顺序剪枝

这种方式就相对较抽象，利用了贪心思想。具体来说，我们如果有两个价值相等的部分，但其所需的尝试数量不同，我们应先解决次数较少的一个，因为其性价比更高。

不过这种方法在数独问题中其实更好理解，就是选择先枚举可填充数字最少的格子。计算机自然也可以实现类似功能。

## 实现

讲解了理论部分，下面就是实现部分。作者的代码主要运用了 **可行性剪枝** 和 **搜索顺序剪枝**。

不过由于想要找到目前可填数字最少的格子，暴力枚举是 $O(9^3)$ 的，大大减慢了我们的速度。我们需用到 **位运算** 进行优化，优化过程不过多赘述。

```cpp
#include <iostream>
#define lowbit(x) (x & -x)
using namespace std;

const int N = (1 << 9);
int n, a[10][10], cnt[N], f[N], r[10], c[10], g[10], cntn;
char ch;
int id[10][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
				  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
				  {0, 1, 1, 1, 2, 2, 2, 3, 3, 3},
				  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
				  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
				  {0, 4, 4, 4, 5, 5, 5, 6, 6, 6},
				  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
				  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9},
				  {0, 7, 7, 7, 8, 8, 8, 9, 9, 9}};

int get(int x)
{
	int cnt = 0;
	while (x)
	{
		++cnt;
		x -= lowbit(x);
	}
	return cnt;
}

void qc(int x, int y, int num)
{
	r[x] ^= (1 << num);
	c[y] ^= (1 << num);
	g[id[x][y]] ^= (1 << num);
}

bool dfs(int cntn)
{
	if (!cntn) return true;
	int mn = 10, x, y, num;
	for (int i = 1; i <= 9; ++i)
		for (int j = 1; j <= 9; ++j)
			if (!a[i][j])
			{
				num = r[i] & c[j] & g[id[i][j]];
				if (cnt[num] < mn)
				{
					x = i, y = j;
					mn = cnt[num];
				}
			}
	num = r[x] & c[y] & g[id[x][y]];
	while (num)
	{
		int nw = f[lowbit(num)];
		a[x][y] = nw + 1;
		qc(x, y, nw);
		if (dfs(cntn - 1)) return true;
		a[x][y] = 0;
		qc(x, y, nw);
		num -= lowbit(num);
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for (int i = 0; i < N; ++i) cnt[i] = get(i);
	for (int i = 0; i <= 8; ++i) f[1<<i] = i;
	while (true)
	{
		cntn = 0;
		for (int i = 1; i <= 9; ++i) r[i] = c[i] = g[i] = N - 1;
		for (int i = 1; i <= 9; ++i)
			for (int j = 1; j <= 9; ++j)
			{
				cin >> ch;
				if (ch == 'e') return 0;
				if (ch == '.')
				{
					a[i][j] = 0;
					++cntn;
				}
				else
				{
					a[i][j] = ch - '0';
					qc(i, j, a[i][j]-1);
				}
			}
		if (dfs(cntn))
			for (int i = 1; i <= 9; ++i)
				for (int j = 1; j <= 9; ++j)
					cout << a[i][j];
		cout << '\n';
    }
	return 0;
}
```

# 使用 DLX 算法解决数独问题

## 引入——精确覆盖问题

### 定义

给定一个 $n$ 行 $m$ 列的 `01` 矩阵，现在你需要挑选若干行，使得对于矩阵的每一列 $j$，在你挑选的这些行中，有且仅有一个 $1$。找到任意解。这个问题被称为精确覆盖问题。

### 例子

$$
\begin{pmatrix}
0 & 0 & 1 & 0 & 1 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 0 & 1 \\
0 & 1 & 1 & 0 & 0 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 & 0 & 1 \\
0 & 0 & 0 & 1 & 1 & 0 & 1
\end{pmatrix}
$$

### 暴力

#### 1

枚举每行是否被选择，时间复杂度 $O(n \times m \times 2^n)$。

#### 2

将每行看做一个二进制数，因此问题转换为：选择若干个二进制数，使它们的两两之间的按位与为 $0$，按位或为 $2^n-1$，$n$ 为选择二进制数的个数。枚举是否选择每个数，在搜索时判断即可做到 $O(2^n)$。

### 正解

暴力不可行，因此需要使用一种新的算法——Dancing Links 优化 X 算法，简称 DLX 算法。

## X 算法

### 定义-相关元素

  将 $x$ 行的所有元素打上标记，再将第 $x$ 行中含 $1$ 的列打上标记。所有打上标记的元素为 $x$ 行的相关元素。

  将 $y$ 列的所有元素打上标记，再将第 $y$ 列中含 $1$ 的行打上标记。所有打上标记的元素为 $y$ 列的相关元素。

### 定义-强相关元素

将 $x$ 行的所有元素打上标记，将第 $x$ 行中含 $1$ 的列打上标记，再将上一步所有打上标记的列中含 $1$ 的行打上标记。所有打上标记的元素为 $x$ 行的强相关元素。

将 $y$ 列的所有元素打上标记，将第 $y$ 列中含 $1$ 的行打上标记，再将上一步所有打上标记的行中含 $1$ 的列打上标记。所有打上标记的元素为 $y$ 列的强相关元素。

### 算法步骤

1. 选择矩阵中未选择过的一行，设选中的这个行是 **原来的** 第 $x$ 行，将 $x$ 加入到答案集合 $S$ 中（这里我们统一按从第一行选择到最后一行选择）。如果所有行都已经尝试过，则判定为无解，算法结束。

2. 删除所有 $x$ 行的强相关元素。

3. 若新矩阵为不为空，则转到第一步。若新矩阵为空且 $x$ 行中的元素全部为 $1$，则找到答案，答案为需要选择集合 $S$ 中的所有行。若新矩阵为空且之前选择的行中元素不是全部为 $1$，则转到第一步并将所有 $x$ 的相关元素恢复。 

### 例子

我们引用在精确覆盖问题中的例子来进行说明。

在这个例子中，我们先将这一行的所有强相关元素打上标记，再进行了删除操作。

初始矩阵为：

$$
\begin{pmatrix}
0 & 0 & 1 & 0 & 1 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 0 & 1 \\
0 & 1 & 1 & 0 & 0 & 1 & 0 \\
1 & 0 & 0 & 1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 & 0 & 1 \\
0 & 0 & 0 & 1 & 1 & 0 & 1
\end{pmatrix}
$$

1.  选择第一行。红色为被选中行。

  $$
  \begin{pmatrix}
    \color{Red}0 & \color{Red}0 & \color{Red}1 & \color{Red}0 & \color{Red}1 & \color{Red}1 & \color{Red}0 \\
    1 & 0 & 0 & 1 & 0 & 0 & 1 \\
    0 & 1 & 1 & 0 & 0 & 1 & 0 \\
    1 & 0 & 0 & 1 & 0 & 0 & 0 \\
    0 & 1 & 0 & 0 & 0 & 0 & 1 \\
    0 & 0 & 0 & 1 & 1 & 0 & 1
    \end{pmatrix}
  $$

2.  将第一行的所有相关元素打上标记，其中蓝色表示标记。

  $$
  \begin{pmatrix}
    \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 \\
    1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 1 \\
    \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
    1 & 0 & \color{Blue}0 & 1 & \color{Blue}0 & \color{Blue}0 & 0 \\
    0 & 1 & \color{Blue}0 & 0 & \color{Blue}0 & \color{Blue}0 & 1 \\
    \color{Blue}0 & \color{Blue}0 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1
  \end{pmatrix}
  $$

3.  删除所有被标记元素，得到一个新的小 01 矩阵：

  $$
  \begin{pmatrix}
    1 & 0 & 1 & 1 \\
    1 & 0 & 1 & 0 \\
    0 & 1 & 0 & 1
  \end{pmatrix}
  $$

4.  选择第一行（注意，**这个第一行是新矩阵的第一行，下面所有对于行的称呼均为当前矩阵的行数**）。

  $$
  \begin{pmatrix}
    \color{Red}1 & \color{Red}0 & \color{Red}1 & \color{Red}1 \\
    1 & 0 & 1 & 0 \\
    0 & 1 & 0 & 1
  \end{pmatrix}
  $$

5.  将第一行的所有相关元素打上标记。

  $$
  \begin{pmatrix}
    \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
    \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
    \color{Blue}0 & \color{Blue}1 & \color{Blue}0 & \color{Blue}1
  \end{pmatrix}
  $$

6. 删除所有被标记元素，得到一个空矩阵。但是上次删除的行 `1 0 1 1` 不是全 $1$ 的，说明选择有误，需要回到 **这个例子的** 第 4 步重新选择。

7.  回溯到步骤 4，选择第二行。

  $$
  \begin{pmatrix}
    1 & 0 & 1 & 1 \\
    \color{Red}1 & \color{Red}0 & \color{Red}1 & \color{Red}0 \\
    0 & 1 & 0 & 1
  \end{pmatrix}
  $$

8.  将第二行的所有相关元素打上标记。

  $$
  \begin{pmatrix}
    \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}1 \\
    \color{Blue}1 & \color{Blue}0 & \color{Blue}1 & \color{Blue}0 \\
    \color{Blue}0 & 1 & \color{Blue}0 & 1
    \end{pmatrix}
  $$

9.  删除所有被标记元素，得到一个新的小 01 矩阵：
    
  $$
  \begin{pmatrix}
    1 & 1
  \end{pmatrix}
  $$

10.  选择第一行。

  $$
  \begin{pmatrix}
    \color{Red}1 & \color{Red}1
  \end{pmatrix}
  $$

11.  将第二行的所有相关元素打上标记。

  $$
  \begin{pmatrix}
    \color{Blue}1 & \color{Blue}1
  \end{pmatrix}
  $$

12.  删除所有被标记元素，得到一个空矩阵，且上一次删除的时候，删除的是全 $1$ 的行，算法结束，答案即为被选择的三行，即 $S$ 中的编号：$1, 4, 5$。

## Dancing-Links 优化 X 算法（DLX 算法）

### 来源及基本思想

不难看出，X 算法需要大量的删除行、删除列和恢复行、恢复列的操作。

因此我们可以使用双十字链表维护。

而在双向十字链表上不断跳跃的过程被形象地比喻成跳跃，因此被用来优化 X 算法的双向十字链表也被称为 Dancing Links。

下文将介绍双十字链表的实现方式及 DLX 算法的实现方式。

### 时间复杂度

$O(x^n)$，其中 $n$ 为矩阵中 $1$ 的个数，$x$ 为一个非常接近于 $1$ 的常数。

## 双十字链表（Dancing Links）

### 定义

双十字链表不同于普通链表，它有 $4$ 个指针，分别指向上、下、左、右四个元素。如下图所示是双十字链表里的单个节点。

以下所有关于指针数组的描述与下图相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/p76qrimu.png)

一整个双十字链表：

![](https://cdn.luogu.com.cn/upload/image_hosting/cg30g5mw.png)

其中 $first$ 数组指向的是每行的开头，而在每列的开头有一个哨兵节点（图中白色节点），红色的 $0$ 号节点是双十字链表的初始节点。

### 操作

#### remove 操作

`remove(x)` 这个操作可以将第 $x$ 列的所有强相关元素移除。

注意：我们下文使用这个双十字链表时仅会插入为 $1$ 的位置，因此可以暴力删点。下同，不再赘述。

将第 $x$ 列移除仅需将其哨兵节点左右的节点连接即可。

接着枚举该列的所有结点，再枚举这些列所在的行，将这些行的所有节点的上下节点连接即可。

示例程序：

```cpp
void remove(int x){
	//第x行的哨兵节点即为x节点。
	R[L[x]] = R[x];
	L[R[x]] = L[x];
	for(int y=U[x];y!=x;y=U[y]){
		for(int z=R[y];z!=y;z=R[z]){//因为每行都是双向循环链表，因此可以从任意这一行的一点开始遍历。
			U[D[z]] = U[z];
			D[U[z]] = D[z];
			sz[col[z]]--;//sz数组记录每列的元素个数，row_i表示i号元素属于哪一行，col_i表示i号元素属于哪一列，下同，并不再赘述。
		}
	}
}
```

#### recover 操作

`recover(x)` 这个操作可以将第 $x$ 列的所有强相关元素恢复。

这个操作即为 remove 操作的反向操作。

接着枚举该列的所有结点，再枚举这些列所在的行，将这些行的所有节点的上下节点连接到当前节点即可。

将第 $x$ 列移除仅需将其哨兵节点左右的节点连接到当前节点即可。

示例程序：

```cpp
void recover(int x){
	for(int y=U[x];y!=x;y=U[y]){
		for(int z=R[y];z!=y;z=R[z]){
			U[D[z]] = z;
			D[U[z]] = z;
			sz[col[z]]++;
		}
	}
	R[L[x]] = x;
	L[R[x]] = x;
}
```

#### build 操作

`build(r,c)` 操作可以建一个新的长为 $r$，宽为 $c$ 的双十字链表。

我们仅需建出哨兵元素即可。

因为每一行都是双向循环链表，所以哨兵元素也不例外。

![](https://cdn.luogu.com.cn/upload/image_hosting/gup99gc0.png)

示例程序：

```cpp
void build(int r,int c){
	n = r,m = c;//我们将双十字链表封装到结构体内，因此需要开设变量来保存边长。
	for(int i=0;i<=c;i++){//建立哨兵节点 
		L[i] = i-1,R[i] = i+1;
		U[i] = i,D[i] = i;//因为双十字链表的每一列也是双向循环链表，因此初始哨兵节点的上、下指针均指向自己。 
	}
  L[0] = c;
  R[c] = 0;
	id = c+1;//id表示如果要添加元素的话，下一个元素的编号，下文阐述插入操作时将会使用。
}
```

#### insert 操作

`insert(r,c)` 操作能在第 $r$ 行，第 $c$ 列的位置插入一个节点（这个节点编号为 $id$，上文示例程序的注释中有提到，这里不再赘述，下同）。

先设置这个节点的行（$row$ 数组）编号为 $r$，列（$col$ 数组）编号为 $c$。

然后将节点 $id$ 插入到第 $c$ 行哨兵节点下方，即 $c$ 节点下方。**我们可以这样做是因为我们在删除与恢复操作时会遍历一整行或一整列，而每行或每列中元素顺序并不重要，下同，并不再赘述。**

之后我们分两种情况讨论。

- 若第 $r$ 行在插入之前没有节点，则直接将 $first_r$ 指向节点 $id$。$id$ 的左、右指针均为本身，即 $id$。
- 若第 $r$ 行在插入之前有节点，则将节点 $id$ 插入到 $first_r$ 之后。

示例程序：

```cpp
void insert(int r,int c){
    id++;//注意要改变下一次插入元素的编号
    row[id] = r,col[id] = c;
    sz[c]++;//这里需要增加行元素个数
    U[id] = c;
    D[id] = D[c];
    U[D[c]] = id;
    D[c] = id;
    if(!first[r]){
        first[r] = L[id] = R[id] = id;
    }
    else{
        L[id] = first[r];
        R[id] = R[first[r]];
        L[R[first[r]]] = id;
        R[first[r]] = id;
    }
}
```

#### dance 操作

`dance(x)` 操作能递归实现 X 算法，这个操作也是 DLX 算法的主体。

步骤如下：

1. 若 $0$ 号节点没有右节点，即矩阵（双十字链表）中没有任何元素时，算法结束，答案为 $S$ 中的所有元素。
2. 枚举所有列，找到 $sz$ 最小的列，即 $1$ 个数最少的列（**这里与上文介绍 X 算法流程的部分有不同，这是为了使程序有启发性，使递归次数更少，也就是速度更快**），使用 remove 操作删除它。
3. 枚举该列所有有 $1$ 的行，枚举其是否被选择。
4. 递归下去，如果找到答案，返回；如果无解，返回并报告无解；否则恢复该列。

示例程序：

```cpp
bool dance(int x){
    if(!R[0]){
        ans = x;
        return 1;
    }
    int y = R[0];
    for(int i=R[0];i;i=R[i]){
        if(sz[i]<sz[y]){
            y = i;
        }
    }
    remove(y);
    for(int i=D[y];i!=y;i=D[i]){
        s[x] = row[i];
        for(int j=R[i];j!=i;j=R[j]){
            remove(col[j]);
        }
        if(dance(x+1)){
            return 1;
        }
        for(int j=L[i];j!=i;j=L[j]){
            recover(col[j]);
        }
    }
    recover(y);
}
```

### 最终程序/DLX 模板

```cpp
struct DLX{
    int n,m,id,ans;
    int L[1005],R[1005],U[1005],D[1005],first[1005],sz[1005],row[1005],col[1005],s[1005];
    void build(int r,int c){
        n = r,m = c;
        for(int i=0;i<=m;i++){
            L[i] = i-1,R[i] = i+1;
            U[i] = i,D[i] = i;
        }
        L[0] = c;
        R[c] = 0;
        id = c+1;
    }
    void remove(int x){
        R[L[x]] = R[x];
        L[R[x]] = L[x];
        for(int y=U[x];y!=x;y=U[y]){
            for(int z=R[y];z!=y;z=R[z]){
                U[D[z]] = U[z];
                D[U[z]] = D[z];
                sz[col[z]]--;
            }
        }
    }
    void recover(int x){
        for(int y=U[x];y!=x;y=U[y]){
            for(int z=R[y];z!=y;z=R[z]){
                U[D[z]] = z;
                D[U[z]] = z;
                sz[col[z]]++;
            }
        }
        R[L[x]] = x;
        L[R[x]] = x;
    }
    void insert(int r,int c){
        row[id] = r,col[id] = c;
        sz[c]++;
        U[id] = c;
        D[id] = D[c];
        U[D[c]] = id;
        D[c] = id;
        if(!first[r]){
            first[r] = L[id] = R[id] = id;
        }
        else{
            L[id] = first[r];
            R[id] = R[first[r]];
            L[R[first[r]]] = id;
            R[first[r]] = id;
        }
        id++;
    }
    bool dance(int x){
        if(!R[0]){
            ans = x;
            return 1;
        }
        int y = R[0];
        for(int i=R[0];i;i=R[i]){
            if(sz[i]<sz[y]){
                y = i;
            }
        }
        remove(y);
        for(int i=D[y];i!=y;i=D[i]){
            s[x] = row[i];
            for(int j=R[i];j!=i;j=R[j]){
                remove(col[j]);
            }
            if(dance(x+1)){
                return 1;
            }
            for(int j=L[i];j!=i;j=L[j]){
                recover(col[j]);
            }
        }
        recover(y);
    }
}DancingLinks;
```

## 建模

### 基本思想

对于每道题，我们考虑行和列代表的意义。

行代表 **决策**，也就是选\不选。

列代表 **状态**，也就是约束条件。

对于某一行而言，由于不同的列的值不相同，我们 **由不同的状态，定义了一个决策**。

## 解决数独问题

### 决策-行

依照上文，因为有 $9$ 行 $9$ 列，每个格子可以填的数组有 $[1,9]$（离散状态下），因此DLX有 $9^3$ 行，即 $729$ 行。

### 约束条件-列

在数独中，**每填一个数可以使用三元组 $(x,y,z)$ 表示，即在第 $x$ 行，第 $y$ 列填入了数 $z$。**

因此决策状态 $(x,y,z)$ 所造成的影响为：

- 第 $x$ 行使用了数 $z$，这一行不能继续使用该数。
- 第 $y$ 列使用了数 $z$，这一列不能继续使用该数。
- 设第 $x$ 行第 $y$ 列所在的宫为第 $w$ 宫，则第 $w$ 宫使用了数 $z$，这一宫不能继续使用该数。
- 第 $x$ 行第 $y$ 列填入的数 $z$，这个位置不能再次填数。

因此决策有 $4$ 种影响，数独里有 $81$ 个格子，因此有 $81 \times 4$ 列，即 $324$ 列。有 $729 \times 4$ 即 $2916$ 个 $1$。

由于这一部分较难理解，同时较难说明，因此标程中不予注释。

## 标程

### 9×9 大小

例题：P10482


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[15][15];
struct DLX{
    int n,m,id,ans;
    int L[10005],R[10005],U[10005],D[10005],first[10005],sz[10005],row[10005],col[10005],s[10005];
    void build(int r,int c){
        memset(L,0,sizeof(L));
        memset(R,0,sizeof(R));
        memset(U,0,sizeof(U));
        memset(R,0,sizeof(R));
        memset(first,0,sizeof(first));
        memset(sz,0,sizeof(sz));
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        memset(s,0,sizeof(s));
        n = r,m = c;
        for(int i=0;i<=m;i++){
            L[i] = i-1,R[i] = i+1;
            U[i] = i,D[i] = i;
        }
        L[0] = c;
        R[c] = 0;
        id = c+1;
    }
    void remove(int x){
        R[L[x]] = R[x];
        L[R[x]] = L[x];
        for(int i=D[x];i!=x;i=D[i]){
            for(int j=R[i];j!=i;j=R[j]){
                sz[col[j]]--;
                U[D[j]] = U[j];
                D[U[j]] = D[j];
            }
        }
    }
    void recover(int x){
        for(int i=U[x];i!=x;i=U[i]){
            for(int j=L[i];j!=i;j=L[j]){
                D[U[j]] = U[D[j]] = j;
                sz[col[j]]++;
            }
        }
        R[L[x]] = L[R[x]] = x;
    }
    void insert(int r,int c){
        id++;
        row[id] = r,col[id] = c;
        sz[c]++;
        U[id] = c;
        D[id] = D[c];
        D[c] = U[D[c]] = id;
        if(!first[r]){
            first[r] = L[id] = R[id] = id;
        }
        else{
            L[id] = first[r];
            R[id] = R[first[r]];
            R[first[r]] = L[R[first[r]]] = id;
        }
    }
    bool dance(int x){
        if(!R[0]){
            for(int i=1;i<x;i++){
                a[(s[i]-1)/81+1][(s[i]-1)/9%9+1] = (s[i]-1)%9+1;
            }
            return 1;
        }
        int y = R[0];
        for(int i=R[0];i;i=R[i]){
            if(sz[i]<sz[y]){
                y = i;
            }
        }
        remove(y);
        for(int i=D[y];i!=y;i=D[i]){
            s[x] = row[i];
            for(int j=R[i];j!=i;j=R[j]){
                remove(col[j]);
            }
            if(dance(x+1)){
                return 1;
            }
            for(int j=L[i];j!=i;j=L[j]){
                recover(col[j]);
            }
        }
        recover(y);
        return 0;
    }
}DancingLinks;
void work(int x,int y,int z){
    int idx = (x-1)*81+(y-1)*9+z;
    DancingLinks.insert(idx,(x-1)*9+z);
    DancingLinks.insert(idx,(y-1)*9+z+81);
    DancingLinks.insert(idx,((x-1)/3*3+(y-1)/3)*9+z+162);
    DancingLinks.insert(idx,(x-1)*9+y+243);
}
int main(){
    while(1){
        DancingLinks.build(729,324);
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                char c;
                cin >> c;
                if(c=='e'){
                    return 0;
                }
                if(c>='0' && c<='9'){
                    a[i][j] = c-'0';
                    work(i,j,a[i][j]);
                }
                else{
                    for(int k=1;k<=9;k++){
                        work(i,j,k);
                    }
                }
            }
        }
        DancingLinks.dance(1);
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                cout << a[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}
```

### 16×16 大小

例题：UVA1309

基本思路与上文一致，仅需将计算行、列、宫时的公式换成 $16 \times 16$ 大小的公式，再将数组空间开大即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][105];
struct DLX{
    int n,m,id,ans;
    int L[200005],R[200005],U[200005],D[200005],first[200005],sz[200005],row[200005],col[200005],s[200005];
    void build(int r,int c){
        memset(L,0,sizeof(L));
        memset(R,0,sizeof(R));
        memset(U,0,sizeof(U));
        memset(R,0,sizeof(R));
        memset(first,0,sizeof(first));
        memset(sz,0,sizeof(sz));
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        memset(s,0,sizeof(s));
        n = r,m = c;
        for(int i=0;i<=m;i++){
            L[i] = i-1,R[i] = i+1;
            U[i] = i,D[i] = i;
        }
        L[0] = c;
        R[c] = 0;
        id = c+1;
    }
    void remove(int x){
        R[L[x]] = R[x];
        L[R[x]] = L[x];
        for(int i=D[x];i!=x;i=D[i]){
            for(int j=R[i];j!=i;j=R[j]){
                sz[col[j]]--;
                U[D[j]] = U[j];
                D[U[j]] = D[j];
            }
        }
    }
    void recover(int x){
        for(int i=U[x];i!=x;i=U[i]){
            for(int j=L[i];j!=i;j=L[j]){
                D[U[j]] = U[D[j]] = j;
                sz[col[j]]++;
            }
        }
        R[L[x]] = L[R[x]] = x;
    }
    void insert(int r,int c){
        id++;
        row[id] = r,col[id] = c;
        sz[c]++;
        U[id] = c;
        D[id] = D[c];
        D[c] = U[D[c]] = id;
        if(!first[r]){
            first[r] = L[id] = R[id] = id;
        }
        else{
            L[id] = first[r];
            R[id] = R[first[r]];
            R[first[r]] = L[R[first[r]]] = id;
        }
    }
    bool dance(int x){
        if(!R[0]){
            for(int i=1;i<x;i++){
                a[(s[i]-1)/256+1][(s[i]-1)/16%16+1] = (s[i]-1)%16+1;
            }
            return 1;
        }
        int y = R[0];
        for(int i=R[0];i;i=R[i]){
            if(sz[i]<sz[y]){
                y = i;
            }
        }
        remove(y);
        for(int i=D[y];i!=y;i=D[i]){
            s[x] = row[i];
            for(int j=R[i];j!=i;j=R[j]){
                remove(col[j]);
            }
            if(dance(x+1)){
                return 1;
            }
            for(int j=L[i];j!=i;j=L[j]){
                recover(col[j]);
            }
        }
        recover(y);
        return 0;
    }
}DancingLinks;
void work(int x,int y,int z){
    int idx = (x-1)*256+(y-1)*16+z;
    DancingLinks.insert(idx,(x-1)*16+z);
    DancingLinks.insert(idx,(y-1)*16+z+256);
    DancingLinks.insert(idx,((x-1)/4*4+(y-1)/4)*16+z+512);
    DancingLinks.insert(idx,(x-1)*16+y+768);
}
int main(){
    string s;
    int cnt = 0;
    while(cin >> s){
        cnt++;
        if(cnt>1){
            cout << endl;
        }
        DancingLinks.build(4096,1024);
        for(int i=1;i<=16;i++){
            if(i!=1){
                cin >> s;
            }
            for(int j=1;j<=16;j++){
                char c = s[j-1];
                if(c!='-'){
                    a[i][j] = c-'A'+1;
                    work(i,j,a[i][j]);
                }
                else{
                    for(int k=1;k<=16;k++){
                        work(i,j,k);
                    }
                }
            }
        }
        DancingLinks.dance(1);
        for(int i=1;i<=16;i++){
            for(int j=1;j<=16;j++){
                cout << (char)(a[i][j]+'A'-1);
            }
            cout << endl;
        }
    }
    return 0;
}
```

---

## 作者：神仙酱 (赞：3)

借此机会整理一下剪枝相关的技巧，希望读者能从中举一反三（~~不是因为这题题解少所以好通过~~）。此外，我在文末附了一些剪枝相关的好题，可以据本文技巧进行运用和练习。

## 基本剪枝技巧
考虑一个简单的选数求和问题：从一些给定的、有重复的数 $a_1, a_2, \ldots , a_n$ 中，允许选最少的几个数，使之和为一个定值 $s$。

### 1. 搜索顺序优化
在大部分搜索问题中，搜索树并不是完全树，这意味着有的分支浅，有的分支深，而且无论是深的分支还是浅的分支都有可能搜到结果上相同的状态，这启示我们应该先从较浅的分支探索。例如在选数求和问题中，一条可行的经验是，先排序，然后从较大的数开始试。在本题中的优化也是基于此。

### 2. 重复性剪枝
搜索过程中，如果可以判定几条分支是完全等效的，那么只需要对其中一条分支搜索即可。例如在选数问题中，对于相同的数，一旦判定其中一个不符合要求，那么之后遇到这个数就也可以跳过了。

### 3. 最优性剪枝
常见于要求最大/最小/最优的搜索问题中，如果当前花费的代价已经大于目前搜到的最优解，那么无论如何都不可能再得到更优的结果，因此应当停止对当前分支的搜索，立刻回溯。例如在选数求和问题中，目前凑出 $k$ 需要最少的数是 $3$ 个，而当前搜索已经用了 $3$ 个数还未能达到 $k$，那么就可以回溯了。

### 4. 可行性剪枝
如果发现分支无法到达递归边界，则应当回溯。遇到一个搜索问题，先考虑能否在搜索前通过预处理剪枝，再考虑搜索时如何检查能否到达递归边界。例如在选数求和问题中，如果存在一些数大于 $k$，那么应当将这些数排除。在搜索时，如果发现当前和已经大于 $k$ 或当前和加上之后数的和仍然小于 $k$，则应当回溯。

## 本题
依次审视上述四条剪枝技巧：

1. **搜索顺序优化**：在同一状态下，是否存在某些搜索分支比另一些浅？也就是说，我们有很多空要填，那么是否存在一个空，先填它可以让我们更少步数地知道这个填法是否可行？具体而言，假设有两个空，在分别检查完行、列和九宫格之后，它们分别还可以填两个数和五个数，那么先从只能填两个数的空开始搜索是较优的。

2. **重复性剪枝**：是否存在某些重复的状态？否，并不存在等效冗余。

3. **最优性剪枝**：我们只需要探索是否可行或求出一个解，因此不需要最优性剪枝。

4. **可行性剪枝**：怎么判定当前状态还能不能继续搜下去？如果发现这个空所有数都试完了，或者这个空已经没有可填的数了，那么这一定是个不可行的填法，因此需要回溯。

更多实现细节见代码注释。
## AC代码
```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 9;
using cell_t = bitset<N>;
/*
 使用 bitset 表示已经用掉的数。例如如果已经用了 1，那么bitset[0] = true。
 hor: 同一行已经用掉的数。
 ver: 同一列已经用掉的数。
 square：九宫格内已经用掉的数。
*/
cell_t hor[N], ver[N], square[N];
char str[N][N];
int root;

// cnt：还需要填写多少数
bool dfs(int cnt) {
    if (cnt == 0)
        return true;
    int min_avail = N + 1, x, y;
    cell_t avail{};
    // 找到还能填的数最少的位置
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            if (str[i][j] == '.') {
                int k = i / root * root + j / root;
                avail = ~(hor[i] | ver[j] | square[k]);
                if (avail.count() < min_avail) {
                    min_avail = avail.count();
                    x = i, y = j;
                }
            }
    }
    int k = x / root * root + y / root;
    // 如果 avail[i] 为 true，则意味着 i + 1 还可用。
    avail = ~(hor[x] | ver[y] | square[k]);
    for (int i = 0; i < N; ++i) {
        if (avail[i]) {
            str[x][y] = '1' + i;
            hor[x][i] = ver[y][i] = square[k][i] = true;
            if (dfs(cnt - 1))
                return true;
            str[x][y] = '.';
            hor[x][i] = ver[y][i] = square[k][i] = false;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    root = sqrt(N);
    string data;
    while (cin >> data, data != "end") {
        memcpy(str, data.c_str(), sizeof str);
        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            hor[i].reset(), ver[i].reset(), square[i].reset();
            // 维护该行已经用掉的数。
            for (int j = 0; j < N; ++j)
                if (str[i][j] != '.')
                    hor[i][str[i][j] - '1'] = true;
            cnt += N - hor[i].count();
        }
        // 维护该列已经用掉的数。
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (str[j][i] != '.')
                    ver[i][str[j][i] - '1'] = true;
	// 维护每一个九宫格已经用掉的数。
        for (int i = 0, idx = 0; i < N; i += root)
            for (int j = 0; j < N; j += root, ++idx)
                for (int k = 0; k < root; ++k)
                    for (int l = 0; l < root; ++l)
                        if (str[i + k][j + l] != '.')
                            square[idx][str[i + k][j + l] - '1'] = true;
        dfs(cnt);
        for (int i = 0; i < N; ++i)
            copy_n(str[i], N, ostream_iterator<char>(cout));
        cout << "\n";
    }
    return 0;
}
```

## 推荐例题
[P1120](https://www.luogu.com.cn/problem/P1120)，[P2329](https://www.luogu.com.cn/problem/P2329)，[P1074](https://www.luogu.com.cn/problem/P1074)。

---

## 作者：xiaomo8125 (赞：3)

# P10482 Sudoku2
蓝书上来的，看到没有人写 DFS 位运算常数优化，于是来写一下，帮助其他和我一样不会的蒟蒻
## 常数优化
  对于每行、每列、每个九宫格，分别用一个 9 位二进制数（全局整数变量）保存哪些数字还可以填

  对于每个位置，把它所在行、列、九宫格的 3 个二进制数做位与运算（&），就可以得到该位置能填哪些数，用 lowbit 运算就可以把能填的数字取出
  
  当一个位置填上某数后，把该位置所在的行、列、九宫格记录的二进制数的对应位改为 0 ，即可更新当前状态；回溯时改回 1 即可还原现场。
  
  ——《算阶》

  更多细节下见代码

  
```cpp
#include<iostream>
#define N (1 << 9)//如果写define位运算一定要记得写括号！！！
#define lowbit(x) (x & -x)
using namespace std;
int T,n,a[10][10];
int cnt[N],f[N],x[9],y[9],z[9];
char c;
int gon(int i,int j){//在第几个九宫格
	return i / 3 * 3 + j / 3;
}
int get_cnt(int i){//二进制下有多少个1，即为可填的数字个数
	int ans=0;
	while(i) ans++ , i-=lowbit(i);
	return ans;
}
void work(int i,int j,int v){
	x[i] ^= (1<<v);//异或的成对变换的运用
	y[j] ^= (1<<v);
	z[gon(i,j)] ^= (1<<v);
}
bool dfs(int tot){
	if(!tot)return true;//找到则返回
	int t=10,nx,ny;
	for(int i=0;i<=8;i++){
		for(int j=0;j<=8;j++){
			if(!a[i][j]){
				int w = x[i] & y[j] & z[gon(i,j)];
				if(cnt[w]<t) nx=i,ny=j,t=cnt[w];//找到能填数目最小的
			}
		}
	}	
	int w=x[nx]&y[ny]&z[gon(nx,ny)];
	while(w){
		int now=f[lowbit(w)];
		a[nx][ny]=now+1;
		work(nx,ny,now);
		if(dfs(tot-1)) return true;
		a[nx][ny]=0;
		work(nx,ny,now);//回溯
		w-=lowbit(w);
	}
	return false;
}
int main(){
	for(int i=0;i<N;i++){
		cnt[i]=get_cnt(i);
	}
	for(int i=0;i<=8;i++){
		f[1<<i]=i;
	}
	while(1){
		int tot=0;
		for(int i=0;i<=8;i++){
			x[i]=y[i]=z[i]=N-1;
		}
		for(int i=0;i<=8;i++){
			for(int j=0;j<=8;j++){
				cin>>c;
				if(c=='e'){
					return 0;
				}
				else if(c=='.')
					a[i][j]=0;
				else{
					a[i][j]=c-'0';
				}
				if(a[i][j]) work(i,j,a[i][j]-1);
				else{
					tot++;
				}
			}
	}
		if(dfs(tot)){
			for(int i=0;i<=8;i++){
				for(int j=0;j<=8;j++){
					printf("%d",a[i][j]);
				}
			}
		}
		cout<<endl;
    }
	return 0;
}
```

---

## 作者：Muzhou10 (赞：2)

位运算操作有些抽象，这里使用 bitset。

该题目来源于李煜东的《算法竞赛进阶指南》，下面给出书中的解决方案。

1. 对于每行、每列、每个九宫格，分别用一个九位二进制数保存**哪些数字还可以填**。

2. 对于每个位置，把它所在的行、列、九宫格的三个二进制数做按位与运算，就可以得到该位置能填哪些数，用 lowbit 运算就可以把能填的数字取出。

3. 当一个位置填上某个数后，把该位置所在的行、列、九宫格记录的二进制数对应位改为零，即可更新当前状态；回溯时改为一即可还原现场。

4. 为减小搜索树的规模，每次从未填的位置里**选择能填合法数字最少的位置**作为下一个分支。

现在让我们来详细分析一下这个过程，就下图第一行第一列为例。

![](https://cdn.luogu.com.cn/upload/image_hosting/acjiq3ud.png)

| 数字  | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0（补） |
| --- | - | - | - | - | - | - | - | - | - | ---- |
| 行   | 1 | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0    |
| 列   | 0 | 1 | 1 | 0 | 1 | 1 | 0 | 1 | 1 | 0    |
| 九宫格 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 0 | 1 | 0    |
| 可取的 | 0 | 0 | 0 | 0 | 1 | 1 | 0 | 0 | 0 | 0    |

对于二进制数 $(0000110000)_2$，取 lowbit 得 $(10000)_2$，取的数就是 $\log_2{16}=4$。

然后再对 $(0000110000)_2-(10000)_2$ 取 lowbit，取对数后取出 $5$。

一步一步搜索即可。

```cpp
#include<iostream>
#include<bitset>
using namespace std;
struct pos{
    int x,y;
};
bitset<10> hang[9];
bitset<10> lie[9];
bitset<10> ge[3][3];
int a[9][9],lg2[1025];
int cnt; //需要填的数的总数
int lowbit(int x){
    return x&(-x);
}
pos getnext(){    //选择”能填合法数字“最少的位置作为下一个分支
    pos res={0,0};
    int minn=10;
    for (int i=0;i<9;++i){
        for (int j=0;j<9;++j){
            if (!a[i][j]){
                bitset<10> tmp=(hang[i]&lie[j]&ge[i/3][j/3]);
                if ((int)tmp.count()<minn){
                    res=(pos){i,j};
                    minn=tmp.count();
                }
            }
        }
    }
    return res;
}
bool dfs(int x){
    if (x==cnt+1){    //填完了，边界
        for (int i=0;i<9;++i){
            for (int j=0;j<9;++j){
                cout << a[i][j];
            }
        }
        cout << "\n";
        return 1;
    }
    pos nx=getnext();
    int xx=nx.x,yy=nx.y;
    int tmp=(hang[xx]&lie[yy]&ge[xx/3][yy/3]).to_ulong(); //综合下来能填的
    while(tmp>0){
        int llb=lowbit(tmp);
        int lb=lg2[llb]; //取出对应的数字
        hang[xx][lb]=lie[yy][lb]=ge[xx/3][yy/3][lb]=0;
        a[xx][yy]=lb;
        // printf("%d %d %d\n",xx,yy,a[xx][yy]);
        if (dfs(x+1)) return 1; //减小时间复杂度，若成功填出，直接步步退出
        hang[xx][lb]=lie[yy][lb]=ge[xx/3][yy/3][lb]=1;
        a[xx][yy]=0; //回溯
        tmp-=llb;
    }
    return 0;
}
void init(){
    for (int i=0;i<9;++i){
        hang[i].set();
        lie[i].set();
        ge[i/3][i%3].set();
        hang[i].reset(0);
        lie[i].reset(0);
        ge[i/3][i%3].reset(0);
    }
    for (int i=0;i<9;++i){
        for (int j=0;j<9;++j){
            a[i][j]=0;
        }
    }
    cnt=0;
}
int main(){
    for (int i=2;i<=1024;++i){ //预处理
        lg2[i]=lg2[i/2]+1;
    }
    while(1){
        init();
        char c=getchar();
        if (c=='e') break;
        for (int i=0;i<9;++i){
            for (int j=0;j<9;++j){
                if (c=='.') ++cnt;    //统计
                if (c!='.'){
                    a[i][j]=c-48;
                    hang[i][c-48]=0;
                    lie[j][c-48]=0;
                    ge[i/3][j/3][c-48]=0;
                }
                c=getchar();
            }
        }
        dfs(1);
    }

    return 0;
}
```

---

## 作者：cjh_trailblazer (赞：2)

### [原题面](https://www.luogu.com.cn/problem/P10482)
## 题目分析：
这道题是常见搜索题，~~事实上是蒟蒻不会舞蹈链~~，DFS 即可。  
## 剪枝思路：
利用人类做数独的思路，找最简单的填。  
将每一行、列、宫中的数字是否可填用二进制数表示，再用  $\operatorname{lowbit}$ 操作取数即可。  
当然，记得回溯时将数还原，还想优化时间就用位运算处理。  
最后注意一下输入输出格式即可。
## 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[81];
int cnt[1<<9], f[1<<9];
int x[9], y[9], z[9], X[81], Y[81];
int gx, gy, gz;

inline void get(int i) {
	gx = X[i];
	gy = Y[i];
	gz = gx / 3 * 3 + gy / 3;
}

void work(int i, int k) {
	get(i);
	x[gx] ^= (1 << k);
	y[gy] ^= (1 << k);
	z[gz] ^= (1 << k);
}

bool dfs(int ans) {
	if (!ans) return 1;
	int k = 10, t;
	for (int i = 0; i < 81; i++)
		if (s[i] == '.') {
			get(i);
			int w = x[gx] & y[gy] & z[gz];
			if (cnt[w] < k) {
				k = cnt[w];
				t = i;
			}
		}
	get(t);
	int w = x[gx] & y[gy] & z[gz];
	while (w) {
		int now = f[w&-w];
		s[t] = now + '1';
		work(t, now);
		if (dfs(ans - 1)) return 1;
		work(t, now);
		s[t] = '.';
		w -= w & -w;
	}
	return 0;
}

void Sudoku() {
	for (int i = 0; i < 9; i++) x[i] = y[i] = z[i] = (1 << 9) - 1;
	int ans = 0;
	for (int i = 0; i < 81; i++)
		if (s[i] != '.') work(i, s[i] - '1');
		else ++ans;
	if (dfs(ans)) for (int i = 0; i < 81; i++) cout << s[i];
	cout << endl;
}

int get_cnt(int i) {
	int ans = 0;
	while (i) {
		++ans;
		i -= (i & -i);
	}
	return ans;
}

int main() {
	for (int i = 0; i < (1 << 9); i++) cnt[i] = get_cnt(i);
	for (int i = 0; i < 9; i++) f[1<<i] = i;
	for (int i = 0; i < 81; i++) {
		X[i] = i / 9;
		Y[i] = i % 9;
	}
	while (cin >> s && s[0] != 'e') Sudoku();
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：2)

准备给读者上压力。

注意，此题的剪枝标准是 [SP1110](https://www.luogu.com.cn/problem/SP1110) 的标准。

之前做 SP1110 时，是看题解理清的思路。

但是不能交题解了，于是，准备在此题上交一下。

首先，为了使搜索树的无解点少。

我们可以尽量先去搜合法情况少的点（搜索顺序）。

为了常数，我们用位运算记录一些局面（卡常）。

这是最难的两个剪枝。

重复性剪枝不用考虑，可行性较为简单（搜索一些局部是否可填）。

还有其他大大小小的剪枝，具体看代码。

[代码在里面（大量）](https://www.luogu.com.cn/paste/jwpq5rgh)。

---

## 作者：qcf2010 (赞：1)

这道题可以说是
[P10481 Sudoku](https://www.luogu.com.cn/problem/P10481)
的加强版。相比于那道题，本题的数据更强。本蒟蒻本想着改一改上一题用过的纯暴力代码就可以通过，~~不出意外地超时了~~。

那本题如何通过呢？

# 使用位运算优化

可以参考一下蓝书《算法竞赛进阶指南》的提示：

>- 对于每行、每列、每个九宫格，分别用一个 $9$ 位二进制数（全局整数变量）保存哪些数字还可以填。
>- 对于每一个位置，把它所在行、列、九宫格的 $3$ 个二进制数做位与（&）运算，就可以得到该位置能填哪些数，用 $\operatorname{lowbit}$ 运算就可以把能填的数字取出。
>- 当一个位置填上某个数后，把该位置所在的行、列、九宫格记录的二进制数的对应位改为 $0$，即可更新当前状态；回溯时改回 $1$，即可还原现场。

::::info[不知道 $\operatorname{lowbit}$ 运算的可以看这里]
~~其实也摘自蓝书~~
>$\operatorname{lowbit}(n)$ 定义为非负整数 $n$ 在二进制表示下“最低位的 $1$ 及其后边所有的 $0$”构成的数值。例如，$n=10$ 的二进制表示为 $(1010)_2$，则 $\operatorname{lowbit}(n)=2=(10)_2$。

有兴趣的读者可以自己找资料阅读，这里直接给出结论：

$$\operatorname{lowbit}(n)=n\operatorname{and}-n$$

我们可以通过 $\operatorname{lowbit}$ 运算找出整数二进制表示下所有是 $1$ 的位。代码如下：

```cpp
int H[37];

//初始化：预处理。
void Initialize(){
	for(int i=0;i<36;++i) H[(1ll<<i)%37]=i;
}

//查询：对于数 x，返回的数组中包含其二进制下所有为 1 的位。
vector<int> Query(int x){
	vector<int> ans;
	while(x){
		ans.push_back(H[(x&-x)%37]);
		x-=x&-x;
	}
	return ans;
}

```
::::

于是我很开心的写完了，代码在[这里](https://www.luogu.com.cn/paste/utaf5iti)。

~~不出意外又超时了。~~

怎么办呢？直到我读到了这位[大佬](https://www.luogu.com.cn/user/895479)的[文章](https://www.luogu.com.cn/article/gafo8z11)，我才突然明白……

# 剪枝是个好东西

想学剪枝的看[这里](https://oi-wiki.org/search/opt/)或者是上文提到的大佬的文章。本题运用到的主要是**搜索顺序剪枝**。

跳出来想，如果你现在在玩一个数独，你会从哪里开始填呢？

想必是某个空可以填的数少，你才会先解决这个空吧。

其实本题题也是如此。对于每一次搜索，我们都选择可以选择的数最少的空，这样就可以大大减少不必要的搜索。

# 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;

int a[15][15];
string s;

int h[15],l[15],g[15];

int H[37],cnt[1<<9+1];

int Get_cnt(int i){
	int ans=0;
	while(i){
		++ans;
		i-=i&-i;
	}
	return ans;
}

int Get(int x,int y){
	return x/3*3+y/3;
}

void Work(int x,int y,int v){
	h[x]^=(1<<v);
	l[y]^=(1<<v);
	g[Get(x,y)]^=(1<<v);
}

void Print(){
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			cout<<a[i][j];
		}
	}
	cout<<"\n";
}

bool Dfs(int now){
	if(!now){
		Print();
		return 1;
	}
	int t=10,x,y;
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			if(!a[i][j]){
				int able=h[i]&l[j]&g[Get(i,j)];
				if(cnt[able]<t){
					x=i;
					y=j;
					t=cnt[able];
				}
			}
		}
	}
	int able=h[x]&l[y]&g[Get(x,y)];
	while(able){
		int num=H[(able&-able)%37];
		Work(x,y,num);
		a[x][y]=num+1;
		if(Dfs(now-1)) return 1;
		Work(x,y,num);
		a[x][y]=0;
		able-=able&-able;
	}
	return 0;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	for(int i=0;i<(1<<9);++i) cnt[i]=Get_cnt(i);
	for(int i=0;i<36;++i) H[(1ll<<i)%37]=i;
	
	while(1){
		cin>>s;
		if(s=="end") return 0;
		for(int i=0;i<9;++i) h[i]=l[i]=g[i]=(1<<9)-1;
		int tot=0;
		for(int i=0;i<9;++i){
			for(int j=0;j<9;++j){
				char c=s[i*9+j];
				if(c=='.') a[i][j]=0;
				else a[i][j]=c-'0';
				if(a[i][j]) Work(i,j,a[i][j]-1);
				else ++tot;
			}
		}
		Dfs(tot);
	}
	
	return 0;
}
```

---

## 作者：ineverleft (赞：1)

首先考虑如何将数独问题转化成 DLX 。

一般的转化思路是把原问题的选法对应成行，限制对应成列，可以得出下面的转化方法。

行：每个格子选哪个数，有 $9^2$ 个格子，每个格子有 $9$ 种选法，一共 $9^2 \times 9$ 行。

列：考虑所有限制：

1. 每个格子恰好填一个数，对应第 $1 \sim 9^2$ 列。

2. 每行 $0\sim 8$ （这里用 $1 \sim 9$ 也可以，我习惯用 $0 \sim 8$）分别恰好出现一次，对应第 $9^2+1 \sim 9^2+9^2$ 列。

3. 每列 $0 \sim 8$ 分别恰好出现一次，对应第 $9^2\times 2+1 \sim 9^2 \times 2 +9^2$ 列。

4. 每个方块 $0 \sim 8$ 分别恰好出现一次，对应第 $9^2 \times 3+1 \sim 9^2 \times 3+9^2$ 列。

   一共 $9^2 \times 4$ 列。

接下来只需要进行 DLX 精确覆盖就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=20000;

int m=9*9*4;

int u[N],d[N],l[N],r[N],s[N],col[N],row[N],idx;
int ans[N],top;
struct Op{
    int x,y;
    char z;
}op[N];

char g[10][10];

void init(){
    for(int i=0;i<=m;i++){
        l[i]=i-1,r[i]=i+1;
        s[i]=0;
        d[i]=u[i]=i;
    }
    l[0]=m,r[m]=0;
    idx=m+1;
}

void add(int &hh,int &tt,int x,int y){
    row[idx]=x,col[idx]=y,s[y]++;
    u[idx]=y,d[idx]=d[y],l[idx]=hh,r[idx]=tt;
    u[d[y]]=idx,d[y]=idx,r[hh]=idx,l[tt]=idx;
    tt=idx++;
}

void remove(int p){
    r[l[p]]=r[p],l[r[p]]=l[p];
    for(int i=d[p];i!=p;i=d[i]){
        for(int j=r[i];j!=i;j=r[j]){
            s[col[j]]--;
            u[d[j]]=u[j],d[u[j]]=d[j];
        }
    }
}

void resume(int p){
    for(int i=u[p];i!=p;i=u[i]){
        for(int j=l[i];j!=i;j=l[j]){
            u[d[j]]=j,d[u[j]]=j;
            s[col[j]]++;
        }
    }
    r[l[p]]=p,l[r[p]]=p;
}

bool dfs(){
    if(!r[0])return true;
    int p=r[0];
    for(int i=r[0];i;i=r[i]){
        if(s[i]<s[p])p=i;
    }
    remove(p);
    for(int i=d[p];i!=p;i=d[i]){
        ans[++top]=row[i];
        for(int j=r[i];j!=i;j=r[j])remove(col[j]);
        if(dfs())return true;
        for(int j=l[i];j!=i;j=l[j])resume(col[j]);
        top--;
    }
    resume(p);
    return false;
}

int main(){
    string str;
    while(cin >> str){
        if(str=="end")break;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                g[i][j]=str[i*9+j];
            }
        }
        init();
        for(int i=0,n=1;i<9;i++){
            for(int j=0;j<9;j++){
                int a=0,b=8;
                if(g[i][j]!='.')a=b=g[i][j]-'1';
                for(int k=a;k<=b;k++,n++){
                    int hh=idx,tt=idx;
                    op[n]={i,j,char(k+'1')};
                    add(hh,tt,n,i*9+j+1);//这里的+1是因为ij从0开始
                    add(hh,tt,n,81+i*9+k+1);
                    add(hh,tt,n,162+j*9+k+1);
                    add(hh,tt,n,243+(i/3*3+j/3)*9+k+1);
                }
            }
        }
        dfs();
        for(int i=1;i<=top;i++){
            auto t=op[ans[i]];
            g[t.x][t.y]=t.z;
        }
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                cout << g[i][j];
            }
        }
        cout << endl;
    }
    return 0;
}
```

---

## 作者：_zuoqingyuan (赞：1)

# 题意简述

> 给你若干组数独，求出每一组数独的解。

# 思路分析

对于数独问题，解决方法只有 DLX 和搜索。这里我们用搜索加剪枝就可以通过。

### 暴力搜索

我们思考最朴素的搜索。

枚举一个没有填数的位置，然后任意填上一个数。搜索下一个没有填数的位置，循环往复。直到所有的位置都填上了，再判断数独是否成立。

这样做的时间复杂度很大程度上取决于没有填数的位置的个数。

```cpp
void dfs(int rem){
    if(!rem&&pd()){//pd()指当前填写的方案是否合法
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
        exit(0);
    }
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(a[i][j])continue;
            for(int k=1;k<=9;k++){
                a[i][j]=k;
                dfs(rem-1);
                a[i][j]=0;
            }
        }
    }
    return 0;
}
```

这样是无法通过本题的。需要进一步优化，我们要进行**剪枝**，所谓剪枝，就是及时排除不可能状态从而**减小搜索树规模**。

### 剪枝一

如果我们找到了一个没填数的位置 $(i,j)$，把所有的 $k\in [1,9]$ 都尝试了一遍。我们可以确定，这种情况属于不可能的情况，就不必再枚举其他的位置了。

很好理解，如果此时的 $(i,j)$ 无法填下任意一个数字，未来就算在其他位置填下了数子，也依然无法改变 $(i,j)$ 没有候选项的结果，依然无解。

```cpp
for(int i=1;i<=9;i++){
    for(int j=1;j<=9;j++){
        if(a[i][j])continue;
        for(int k=1;k<=9;k++){
            a[i][j]=k;
            dfs(rem-1);
            a[i][j]=0;
        }
        return 0;
    }
}
```
看似一个简单的代码，实际上大大减小了常数。

### 剪枝二

思考正常人在解数独时采取的策略。抛开复杂的不谈，人类在解决数独问题时的基本策略就是：**每次挑选候选项个数最少的位置去尝试**。

例如，你发现两个位置没有填数字，一个位置上可以填的数字有 $9$ 个，另一个位置上可以填的数字有 $2$ 个，你会选择先填哪一个？

显然，选择后者既可以快速确定答案，也可以快速排除已经做出的错误选择。这启发我们，计算当前数独内，**可填数字个数最少**的一个位置去枚举。

如何计算可填数字个数？限制一个位置所填的数字可能是同行，同列，同九宫格。我们记录同行，同列，同九宫格未填的数字，然后取其公共部分，比较公共部分数量最少的哪一个位置去填写。

我们运用**状态压缩**的方法，具体的说，我们用一个长度为 $9$ 的二进制串，第 $i$ 个位置上如果是 $1$，就说明这个数字还未填写。我们记录每行，每列，每九宫格的二进制串。利用 C++ 自带的与运算与在一起，再提前**预处理**出各个二进制状态中 $1$ 的个数。时间复杂度均为 $O(1)$。

具体还是看代码吧。

# Code

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=(1<<9);
int row[11],col[11],mk[4][4],mp[N],ones[N];//每行，每列，每九宫格压缩后的状态
char s[100];
int lowbit(int x){return x&(-x);}
int get(int x,int y){
    return row[x]&col[y]&mk[x/3][y/3];
}//计算出每个位置可填的数的个数
void init1(){
    int cnt=0;
    for(int i=0;i<N;i++){
        cnt=0;
        for(int j=i;j;j-=lowbit(j))cnt++;
        ones[i]=cnt;//预处理不同状态
    }
    for(int i=0;i<9;i++)mp[1<<i]=i;
}//预处理
void init2(){
    for(int i=0;i<9;i++)row[i]=col[i]=N-1;
    for(int i=0;i<3;i++)for(int j=0;j<3;j++)mk[i][j]=N-1;//多测要清空
}
bool dfs(int t){
    if(t==0)return 1;
    int mintp=10,x=0,y=0;
    for(int i=0,k=0;i<9;i++){
        for(int j=0;j<9;j++,k++){
            if(s[k]=='.'){
                int tp=ones[get(i,j)];
                if(tp<mintp)mintp=tp,x=i,y=j;//寻找可填数字最少的位置
            }
        }
    }
    for(int op=get(x,y);op;op-=lowbit(op)){
        int k=mp[lowbit(op)];//一次枚举可填的数字
        row[x]-=(1<<k),col[y]-=(1<<k),mk[x/3][y/3]-=(1<<k),s[x*9+y]=k+'1';//更新
        if(dfs(t-1))return 1;//搜索
        row[x]+=(1<<k),col[y]+=(1<<k),mk[x/3][y/3]+=(1<<k),s[x*9+y]='.';//还原现场
    }
    return 0;
}
int main(){
    init1();
    while(scanf("%s",s)&&s[0]!='e'){
        init2();
        int num=0,k=0;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++,k++){
                if(s[k]=='.')num++;
                else{
                    int t=s[k]-'1';
                    row[i]-=(1<<t);
                    col[j]-=(1<<t);
                    mk[i/3][j/3]-=(1<<t);
                }
            }
        }
        dfs(num);
        printf("%s\n",s);
    }
}
```

如有错误，请指出。

---

## 作者：Vct14 (赞：0)

这篇题解的做法为优化 dfs。

首先给出 P10481 稍作修改得到的代码。思路是使用一个大小为 $9$ 的 bitset 将每一行、每一列、每一个宫内各个数字可不可以填存下来，每次枚举第一个未填的数，将对应行列宫的 bitset 与起来，得到该位可填的数，继续搜索即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

char c[12][12];
bitset<10> h[10],l[10],g[10];
bool ok;

void dfs(int s){
    if(s==81){
        for(int i=0; i<9; i++) for(int j=0; j<9; j++) cout<<c[i][j];
        ok=1;return ;
    }
    for(int i=0; i<9; i++) for(int j=0; j<9; j++) if(c[i][j]=='.'){
        bitset<10> ad=h[i]&l[j]&g[i/3*3+j/3];
        for(int k=0; k<9; k++) if(ad.test(k)){
            c[i][j]=(char)(k+'0'+1);
            bitset<10> hh=h[i],ll=l[j],gg=g[i/3*3+j/3];
            h[i].reset(k),l[j].reset(k),g[i/3*3+j/3].reset(k);
            dfs(s+1);if(ok) return ;
            c[i][j]='.';
            h[i]=hh,l[j]=ll,g[i/3*3+j/3]=gg;
        }
        return ;
    }
}

void solve(){
    for(int i=0; i<9; i++) h[i].set(),l[i].set(),g[i].set();
    string s;cin>>s;int sss=-1;if(s=="end") exit(0);
    for(int i=0; i<9; i++) for(int j=0; j<9; j++) c[i][j]=s[++sss];
    int cnt=0;ok=0;
    for(int i=0; i<9; i++) for(int j=0; j<9; j++)
        if(c[i][j]!='.') h[i].reset(c[i][j]-'0'-1),l[j].reset(c[i][j]-'0'-1),g[i/3*3+j/3].reset(c[i][j]-'0'-1),cnt++;
    dfs(cnt);
    cout<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    while(1) solve();
	return 0;
}
```

但是本题数据较强，需要进行优化。注意到人类在完成数独时会优先处理方案数更少的位置，因为这样可以用较少的尝试确定较多位置的值，即可以大幅减少尝试次数。

因此对于每一个局面，我们找到可填的数最少的位置，并尝试该位可填的数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

char c[12][12];
bitset<10> h[10],l[10],g[10];
bool ok;

void dfs(int s){
    if(s==81){
        for(int i=0; i<9; i++) for(int j=0; j<9; j++) cout<<c[i][j];
        ok=1;return ;
    }
    int I,J,mn=10;
    for(int i=0; i<9; i++) for(int j=0; j<9; j++) if(c[i][j]=='.'){
        bitset<10> ad=h[i]&l[j]&g[i/3*3+j/3];
        int k=ad.count();
        if(k<mn) mn=k,I=i,J=j;
    }
    bitset<10> ad=h[I]&l[J]&g[I/3*3+J/3];
    for(int k=0; k<9; k++) if(ad.test(k)){
        c[I][J]=(char)(k+'0'+1);
        bitset<10> hh=h[I],ll=l[J],gg=g[I/3*3+J/3];
        h[I].reset(k),l[J].reset(k),g[I/3*3+J/3].reset(k);
        dfs(s+1);if(ok) return ;
        c[I][J]='.';
        h[I]=hh,l[J]=ll,g[I/3*3+J/3]=gg;
    }
}

void solve(){
    for(int i=0; i<9; i++) h[i].set(),l[i].set(),g[i].set();
    string s;cin>>s;int sss=-1;if(s=="end") exit(0);
    for(int i=0; i<9; i++) for(int j=0; j<9; j++) c[i][j]=s[++sss];
    int cnt=0;ok=0;
    for(int i=0; i<9; i++) for(int j=0; j<9; j++)
        if(c[i][j]!='.') h[i].reset(c[i][j]-'0'-1),l[j].reset(c[i][j]-'0'-1),g[i/3*3+j/3].reset(c[i][j]-'0'-1),cnt++;
    dfs(cnt);
    cout<<"\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    while(1) solve();
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

这题就是上题的难度加强版。

显然对于数独问题比较靠谱的算法是 DLX 也就是舞蹈链，但是搜索其实也是能直接过去的，具体就是剪枝。

首先我们在满足条件的情况下枚举合理的数，这也是最基础的方法。~~当然我也就止步于此~~。

然后考虑解可不可行的问题，如果一个数填不了就直接退出，这是剪枝其一。

然后就是一个种比较玄学的剪枝了，回忆一下人类做数独题是怎么做的。我们一开始看到哪儿不确定的数少就优先确定哪里，因为这样方便点嘛。看似无用的做法实际上非常有用，因为先确定少的一部分更容易快速确定答案，这样减少了一部分一开始的枚举量嘛。

加上这几个剪枝就能够过掉了应该。

---

