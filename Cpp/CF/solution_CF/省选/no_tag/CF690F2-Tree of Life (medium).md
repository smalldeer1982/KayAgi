# Tree of Life (medium)

## 题目描述

Heidi got tired of deciphering the prophecy hidden in the Tree of Life and decided to go back to her headquarters, rest a little and try there. Of course, she cannot uproot the Tree and take it with her, so she made a drawing of the Tree on a piece of paper. On second thought, she made more identical drawings so as to have $ n $ in total (where $ n $ is the number of vertices of the Tree of Life) – who knows what might happen?

Indeed, on her way back Heidi was ambushed by a group of zombies. While she managed to fend them off, they have damaged her drawings in a peculiar way: from the $ i $ -th copy, the vertex numbered $ i $ was removed, along with all adjacent edges. In each picture, the zombies have also erased all the vertex numbers and relabeled the remaining $ n-1 $ vertices arbitrarily using numbers $ 1 $ to $ n $ (fortunately, each vertex still has a distinct number). What's more, the drawings have been arbitrarily shuffled/reordered.

Now Heidi wants to recover the Tree of Life from her descriptions of all the drawings (as lists of edges).

## 样例 #1

### 输入

```
1
5 5
2
4 1
2 1
1
3 1
3
4 1
4 3
2 1
3
3 1
3 2
4 1
3
2 1
3 2
4 2
```

### 输出

```
YES
2 5
4 2
3 2
5 1
```

# 题解

## 作者：Alex_Wei (赞：0)

### [CF690F2 Tree of Life (medium)](https://www.luogu.com.cn/problem/CF690F2)

找出任意一个 $m_i = n - 2$ 的 $T'_i$，它一定是原树被删掉了一个叶子。往任意结点加叶子，然后检查是否合法。

问题转化为给定树 $T$，删去每个点得到 $T_i$，是否存在排列 $p_i$ 使得 $T_i$ 和 $T'_{p_i}$ 同构。

我们通过以下方式计算无根树森林的哈希值：对每棵无根树，计算其哈希值。将哈希值从小到大排序后返回一个长度为连通块数量的列表。

无根树的哈希值：以两个重心为根分别计算有根树哈希值，并将结果取 $\min$。

设 $T_i$ 得到列表 $H_i$，$T_i'$ 得到列表 $H'_i$，将 $H$ 和 $H'$ 排序后比较对应位置是否相等即可。

时间复杂度 $\mathcal{O}(n ^ 3\log n)$，但是卡不满。[代码](https://codeforces.com/contest/690/submission/210826653)。

---

