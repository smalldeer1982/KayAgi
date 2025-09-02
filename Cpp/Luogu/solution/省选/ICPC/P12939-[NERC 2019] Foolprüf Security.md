# [NERC 2019] Foolprüf Security

## 题目描述

Alice 和 Bob 获得了一份秘密地下设施的地图。该设施由 $n$ 个**安全单元**和 $m$ 个**化学实验室**组成，通过双向隧道连接。该设施的地图构成一棵**树**：共有 $n + m - 1$ 条隧道，且不存在环路。安全单元对应的顶点编号为 $1$ 至 $n$，化学实验室的编号为 $n+1$ 至 $n+m$。每条隧道连接一个安全单元和一个化学实验室；不存在连接两个安全单元或两个化学实验室的隧道。

为了防止 Alice 或 Bob 被捕，他们决定将地图分成两部分。为此，他们计算了这棵树的 **Prüfer 编码**。Alice 随后将原始编码中 $1$ 至 $n$ 的部分数字按顺序保存到她的数据存储中，Bob 则保存了 $n+1$ 至 $n+m$ 的部分数字，同样按原始编码的顺序存储。

一棵 $k$ 个顶点的树的 Prüfer 编码是一个长度为 $k - 2$ 的序列，其中每个数字的取值范围是 $1$ 至 $k$，构造方式如下：找到标号最小的叶子节点（度数为 1 的顶点），将其从树中移除，并记录其唯一邻居的标号。重复此过程 $k - 3$ 次，直到只剩一条边。记录的 $k - 2$ 个顶点标号序列即为 Prüfer 编码。

Alice 和 Bob 安全返回后，准备将他们的数据合并以恢复原始地图。但他们在备份时可能出错，导致不存在符合条件的地图。他们需要你的帮助来恢复任意一种可能的地图，使得 Alice 和 Bob 保存的部分都是该地图 Prüfer 编码的子序列。


## 说明/提示

第一个示例中树的 Prüfer 编码为 $(\underline{7}, \mathbf{1}, 6, \mathbf{3}, \mathbf{3}, \underline{8}, \mathbf{4})$。

![](https://cdn.luogu.com.cn/upload/image_hosting/6z6yk20m.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4 5 4 2
1 3 3 4
7 8```

### 输出

```
Yes
1 5
1 6
2 7
6 3
3 7
9 4
3 8
4 8```

## 样例 #2

### 输入

```
4 3 3 1
3 2 2
6```

### 输出

```
No```

# 题解

## 作者：FFTotoro (赞：3)

题目中的编号类似于一个黑白染色的形式（树是一个二分图），下文将两种结点称为“黑点”（共有 $n$ 个）和“白点”（共有 $m$ 个）。考虑 Prüfer 序列的构造过程：最终只留下了一个黑点和一个白点，每次删去一个黑点就会在 Prüfer 序列里面加入一个白点，反之亦然，所以最终 Prüfer 序列里一定有 $n-1$ 个白点（删了这么多黑点）和 $m-1$ 个黑点（删了这么多白点）。

于是可以得出无解的一个充分条件：$k_a\ge m$ 或 $k_b\ge n$。下面提出一种构造，证明这个条件是必要的：

对于 $k_a<m-1$ 或 $k_b<n-1$ 的情况，在序列后随便填数直到 $k_a=m-1$ 且 $k_b=n-1$（对于 $a$ 序列可以填 $1\sim n$ 的数，$b$ 序列可以填 $n+1\sim n+m$ 的数），于是只需要证明 $k_a=m-1$ 且 $k_b=n-1$ 时有解。

回头考虑 Prüfer 序列的构造方式，最终留下的一条边必然是 $(a_{m-1},b_{n-1})$。按照如下方式定义一个长度为 $n+m$ 的“度数序列” $d$：$d_{a_{m-1}}=d_{b_{n-1}}=+\infin$，其他的 $d_i$ 为 $i$ 在 Prüfer 序列中的出现次数。

按照如下流程构造：在 $d_i=0$ 中的 $i$ 中选择最小的 $i$，令与 $i$ 相连的唯一一个结点为 $u$，在边集中加入 $(i,u)$，将 $d_i$ 设为 $-1$（相当于之后不再考虑 $i$），$d_u\gets d_u-1$；循环往复直到边达到 $n+m-2$ 条，最后加入 $(a_{m-1},b_{n-1})$。

优先队列维护这个过程可以做到 $O(n\log n)$。借助[模板题题解的技巧](https://oi-wiki.org/graph/prufer/#%E7%BA%BF%E6%80%A7%E6%97%B6%E9%97%B4%E9%87%8D%E5%BB%BA%E6%A0%91)（维护一个指针从左往右扫）可以优化到 $O(n)$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,m,ka,kb; cin>>n>>m>>ka>>kb;
  if(ka>=m||kb>=n)cout<<"No\n",exit(0);
  vector<int> a(ka),b(kb),d(n+m);
  for(auto &i:a)cin>>i,d[--i]++;
  for(auto &i:b)cin>>i,d[--i]++;
  while(a.size()<m-1)a.emplace_back(0),d[0]++;
  while(b.size()<n-1)b.emplace_back(n),d[n]++;
  // 补全 a 和 b 两个序列
  d[a.back()]++,d[b.back()]++; // 相当于设为了正无穷
  vector<pair<int,int> > e;
  int c=-1,p=0,pa=0,pb=0;
  while(e.size()<n+m-2){
    while(d[p])p++;
    if(c<0||c>=p)c=p++;
    int t=c<n?b[pb++]:a[pa++];
    e.emplace_back(c,t),c=--d[t]?-1:t;
  } // 使用模板题题解的技巧优化到 O(n)
  e.emplace_back(a.back(),b.back());
  cout<<"Yes\n";
  for(auto [u,v]:e)cout<<u+1<<' '<<v+1<<'\n';
  return 0;
}
```

---

