---
title: "Tree Separator"
layout: "post"
diff: 普及+/提高
pid: AT_jag2017autumn_e
tag: []
---

# Tree Separator

## 题目描述

给定一棵无根树 $T$ 与一个整数 $K$，你需要找到两个不同的节点 $u,v$，使得将在 $u,v$ 简单路径上的点及其所连接的边全部删去后剩余的连通块中大小至少为 $K$ 的连通块数量最多。

## 输入格式

第一行两个正整数 $N,K(2 \le N \le 10^5, 1 \le K \le N)$。

接下来 $N-1$ 行，每行两个正整数 $u_i,v_i(1\le u_i,v_i \le n, u_i \ne v_i)$，表示树上的一条边 $(u_i,v_i)$。

## 输出格式

输出剩余的连通块中大小至少为 $K$ 的连通块数量的最大值。

