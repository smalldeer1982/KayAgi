# Permutation and Queries

## 题目描述

给定由 $1 \sim n$ 构成的排列 $p$，有两种操作:

- `1 x y`：交换 $p_{x}$ 和 $p_{y}$。

- `2 i k`：给出 $i$ 的初始值，令 $i \gets p_{i}$ 执行 $k$ 次，最后输出 $i$。

至少有一个第二类操作。

## 样例 #1

### 输入

```
5 4
5 3 4 2 1
2 3 1
2 1 2
1 1 3
2 1 2```

### 输出

```
4
1
2```

## 样例 #2

### 输入

```
5 9
2 3 5 1 4
2 3 5
2 5 5
2 5 1
2 5 3
2 5 4
1 5 4
2 5 3
2 2 5
2 5 1```

### 输出

```
3
5
4
2
3
3
3
1```

# 题解

## 作者：I_am_Accepted (赞：13)

### Preface

~~H 是 Hydro，代表水题（不是）~~

分块好题（其实应该是根号分治？）

### Analysis

设 $B=\sqrt{n}$。

将原问题转化成有向图，发现是多个环。我们对于一个点 $x$，不仅存下一个是 $ne_x$，还维护上一个是 $pr_x$、以及下 $B$ 个是 $ju_x$（jump）。

对于操作 `1 x y`，我们 $O(1)$ 修改 $pr,ne$，发现 $ju$ 改变的只有 $x,y$ 的前驱 $B$ 个（包括本身）。通过 $pr$ 追溯到 $x$ 的上 $B-1$ 个，通过两个指针 $O(B)$ 求出（具体看代码），$y$ 同理。

对于询问 `2 i k`，先将 $i$ 向前用 $ju$ 数组 jump，再一步一步走，$O(\dfrac{n}{B})=O(B)$。

总时间 $O(n\sqrt{n})$ 预处理和 $O(q\sqrt{n})$ 维护、回答。

### Code

```cpp
#define N 100010
int pr[N],ne[N],ju[N];
int n,b;
inline int move(int x,int y){
	while(y--) x=ne[x];
	return x;
}
void calc(int x){
	int y=ne[x];
	For(i,1,b-1) x=pr[x];
	For(i,1,b){
		ju[x]=y;
		x=ne[x];
		y=ne[y];
	}
}
signed main(){
	int q;
	cin>>n>>q;
	b=sqrt(n);
	cerr<<"b"<<b<<endl;
	For(i,1,n) cin>>ne[i];
	For(i,1,n) pr[ne[i]]=i;
	For(i,1,n) ju[i]=move(i,b);
	int opt,x,y;
	while(q--){
		cin>>opt>>x>>y;
		if(opt==1){
			swap(pr[ne[x]],pr[ne[y]]);
			swap(ne[x],ne[y]);
			calc(x);
			calc(y);
		}else if(opt==2){
			while(y>=b){
				y-=b;
				x=ju[x];
			}
			cout<<move(x,y)<<endl;
		}else assert(0);
	}
    return 0;
}
```

---

## 作者：WOL_GO (赞：2)

一道根号分治好题。首先观察到题面 $1\le n,q \le 10^5$，可以想到根号的算法，于是我们考虑根号分治。我们维护三个数组 $next_{i}$ 表示当前的数 $i$ 下一步可以跳到第 $next_{i}$ 号点上，$last_{i}$ 表示当前的数 $last_{i}$ 下一步可以跳到第 $i$ 号点上，$ne_{i}$ 表示当前的数 $i$ 下 $\sqrt{n}$ 步可以跳到第 $ne_{i}$ 号点上。对于修改操作，我们只需要先交换两个数的 $next$ 和 $last$，然后用 $\sqrt{n}$ 的时间求出一个点 $j$ 使 $ne_{j}=i$，然后一直更新 $ne_{j}$ 直到 $j=i$。对于查询操作，我们则需要分两类讨论。

1. 对于 $k\le \sqrt{n}$ 的情况，暴力模拟即可。

2. 对于 $k\ge \sqrt{n}$ 的情况，先跳 $\sqrt{n}$ 块，然后再一块一块跳即可。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5,block=316;
int n,m,a[maxn],las[maxn],ne[maxn];
int getne(int x){
    int to=x;
    for(int i=1;i<=block;i++)to=las[to];
    return to;
}
int main(){
    #ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    #endif
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i],las[a[i]]=i;
    for(int i=1;i<=n;i++){
        int to=i;
        for(int j=1;j<=block;j++)to=a[to];
        ne[i]=to;
    }
    while(m--){
        int opt,x,y;
        cin>>opt>>x>>y;
        if(opt==1){
            // cout<<ne[xx]<<" "<<xx<<" "<<ne[yy]<<" "<<yy<<"\n";
            // swap(a[las[x]],a[las[y]]);
//            swap(las[x],las[y]);
             swap(las[a[x]],las[a[y]]);
            // return 0;
			swap(a[x],a[y]);
			int xx=getne(x),yy=getne(y);
            // return 0;
//            swap(x,y);
            int to=x;
            // cout<<x<<" "<<xx<<"\n";
            for(int i=1;i<=block;i++){
                xx=a[xx];
                to=a[to];
                ne[xx]=to;
                // cout<<xx<<" "<<to<<" "<<ne[xx]<<"\n";
            }
            to=y;
            for(int i=1;i<=block;i++){
                yy=a[yy];
                to=a[to];
                ne[yy]=to;
            }
        }
        else{
            while(y>block)x=ne[x],y-=block;
            for(int i=1;i<=y;i++)x=a[x];
            cout<<x<<"\n";
        }
//        for(int i=1;i<=n;i++)cout<<a[i]<<" ";
//        cout<<"\n";
//         for(int i=1;i<=n;i++)cout<<ne[i]<<" ";
//         cout<<"\n\n";
    }
    return 0;
}
```


---

## 作者：Day_Tao (赞：1)

### 题目大意
给定一个排列，有两种操作：

- 交换 $p_x$，$p_y$ 的位置。
- 输出 $k$ 次 $i\gets p_i$ 以后的的 $i$。
---
### Sol
可以看到 $n,p \le 1 \times10^5$，这时就可以想到根号分治了。

首先我们设 $lst_i$ 为遍历到 $i$ 的上一个数，$nxt_i$ 为 $i$ 往后进行操作二 $\sqrt n$ 次。

在预处理时，可以记录下 $lst_{p_i}$ 的值，即当前的 $i$。然后对于每个 $p_i$ 求出它进行操作二 $\sqrt n$ 次之后所得到的值，总复杂度 $O(n + n \sqrt n)$。

接下来进行操作的输入。当 $opt$ 为 $1$ 时，对于 $lst$ 与 $p$ 数组，交换位置不会对其他的位置造成影响，所以直接交换。但是对于 $nxt$ 数组，由于这记录了 $\sqrt n$ 次的结果，所以必有 $\sqrt n$ 个数会造成影响，所以需要再次更新。具体操作详见代码部分。时间复杂度为单次 $O(\sqrt n)$。当 $opt$ 为 $2$ 时，对于输入的 $i$ 一直进行每次走 $\sqrt n$ 步的操作，同时 $k$ 也相应减少 $\sqrt n$ ，直到 $k \le \sqrt n$。剩下 $k \ge 0$ 的部分就直接进行暴力走，单次复杂度也为 $O(\sqrt n)$。询问的总复杂度为 $O(q\sqrt n)$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)
#define pqg priority_queue<int, vector<int>, greater<int>>
#define pql priority_queue<int, vector<int>, less<int>>
#define ls root << 1
#define rs root << 1 | 1
#define scnaf scanf
#define rt register int
#define int long long
const int MAX = 2e5 + 5;
const int INF = 0x7fffffff;
const int mod = 998244353;
int n, q, p[MAX], op, x, y, lst[MAX], nxt[MAX], m;
signed main()
{
    scanf("%lld%lld", &n, &q);
    for (int i = 1; i <= n; i++)                       // 记录lst数组
        scanf("%lld", &p[i]), lst[p[i]] = i;
    m = sqrt(n);
    for (int i = 1; i <= n; i++)                       // 记录nxt数组
    {
        int nxtt = i;
        for (int j = 1; j <= m; j++)
            nxtt = p[nxtt];
        nxt[i] = nxtt;
    }
    while (q--)
    {
        scanf("%lld%lld%lld", &op, &x, &y);
        if (op == 1)
        {
            swap(p[x], p[y]);
            swap(lst[p[x]], lst[p[y]]);                //交换p数组和lst数组
            int xx = x;
            for (int i = 1; i <= m; i++)
                xx = lst[xx];
            int yy = y;
            for (int i = 1; i <= m; i++)
                yy = lst[yy];                         //这里是找到最前面的被这次修改所影响的数，即 x , y 前sqrt(n)个
            int t = x;                                //最前面的那个 xx , yy 走sqrt(n)步的结果就是 x 和 y
            for (int i = 1; i <= m; i++)
                xx = p[xx], t = p[t], nxt[xx] = t;
            t = y;
            for (int i = 1; i <= m; i++)
                yy = p[yy], t = p[t], nxt[yy] = t;    //一个个修改后面会被影响到的数，t 与 xx 或 yy 都同时向后挪一位，差值仍然为sqrt(n)
        }
        else                                          //查询
        {
            while (y > m)
                y -= m, x = nxt[x];
            for (int i = 1; i <= y; i++)
                x = p[x];
            printf("%lld\n", x);
        }
    }
    return 0;
}
```
---
### END

---

## 作者：laboba (赞：1)

可能没什么用的思考过程（面向我这种不能理解如何想到分块的分块小白QwQ）：

首先感觉看到询问的形态会比较自然的想到对每个 $i$ 预处理/维护一些特定的 $k$，然后用已有的数据去凑询问中的 $k$，那么问题就在维护哪些值使得询问能快速求出答案且修改操作不会影响太多值。

一开始想到的是预处理 $2$ 的若干次幂，然后发现修改代价比 $O(n)$ 还大qwq。一个问题在于，这样处理需要维护许多非常大，$k$ 与 $n$ 基本同阶的数据，虽然加快了凑 $k$ 的过程，而一个修改操作会影响很多这样的数据，复杂度就炸了。所以这让我们去尝试平衡询问和修改的复杂度，$\sqrt n$ 分块满足的就是这样一件事。

正解：

考虑分块，维护数组 $a_i$，表示 $i=p_i$ 共 $\sqrt n$ 次后的 $i$。对于询问，只需要 $i$ 先在 $a$ 上直接跳 $\left[\dfrac{k}{\sqrt n}\right]$ 次，剩下的在 $p$ 上跳。对于修改，$a$ 中会被影响的数字最多只有 $2\times \sqrt n$ 个，用一个辅助数组 $q$ 满足 $q_{p_i}=i$ 来寻找这些会被影响的数，$p$ 和 $q$ 则直接修改即可。

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=100100;
int p[N],q[N],a[N];
int n,m;
void update(int x){//update表示更新x会影响的sqrt(n)个值 
	int tmp=x;
	for(int i=1;i<m;i++)tmp=q[tmp]; 
	for(int j=p[x],f=1;f<=m;f++,tmp=p[tmp],j=p[j]){
		a[tmp]=j;
	}
}
void change(int x,int y){
	swap(p[x],p[y]);
	q[p[y]]=y;
	q[p[x]]=x;
	update(x);
	update(y);
}
int query(int i,int k){
	int ans=i;
	for(int j=1;j<=k/m;j++)ans=a[ans];
	for(int j=1;j<=k%m;j++)ans=p[ans];
	return ans;
}
int main(){
	int qwq;
	scanf("%d%d",&n,&qwq);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]),q[p[i]]=i;
	m=sqrt(n);
	for(int i=1;i<=n;i++){
		a[i]=i;
		for(int j=1;j<=m;j++)a[i]=p[a[i]];
	}
	while(qwq--){
		int type,x,y;
		scanf("%d%d%d",&type,&x,&y);
		if(type==1)change(x,y);
		else printf("%d\n",query(x,y));
	} 
} 
```


---

## 作者：Retired_lvmao (赞：1)

### 题意

给定一个长度为 $n$ 的排列 $p$，要求支持一下两种操作：

- 1.交换排列中的两个数
- 2.查询如果从 $x$ 开始，进行 $y$ 次 $x=p_x$ 操作后的结果。

### 题解

考虑分治，记 $B=\sqrt{n}$，对于每个数，预处理出 $f(x)$ 表示从 $x$ 往后走 $B$ 步的结果。每次交换的时候，对于 $x,y$ 两数暴力修改 $f(x)$ 和 $f(y)$，对 $x$ 和 $y$ 的前后 $\sqrt{n}$ 的 $f$ 可以暴力递推修改。查询时，先每次跳 $B$ 步，不足 $B$ 步的暴力跳。综合复杂度为 $n\sqrt{n}$ 。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int base;
int n,nxt[100010],lst[100010],q;
int tmp[100010];
void remake(int x)
{
	int nw=x;
	for(int i=1;i<=base;i++)
		nw=nxt[nw];
	tmp[x]=nw;
	nw=x;
	for(int i=1;i<=base;i++)
	{
		nw=lst[nw];
		tmp[nw]=lst[tmp[nxt[nw]]];
	}
	nw=x;
	for(int i=1;i<=base;i++)
	{
		nw=nxt[nw];
		tmp[nw]=nxt[tmp[lst[nw]]];
	}
}
int main()
{
	scanf("%d%d",&n,&q);base=sqrt(n);
	for(int i=1;i<=n;i++)
		scanf("%d",&nxt[i]),lst[nxt[i]]=i;
	for(int i=1;i<=n;i++)
		remake(i);
	for(int i=1;i<=q;i++)
	{
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)
		{
			swap(nxt[x],nxt[y]);
			swap(lst[nxt[x]],lst[nxt[y]]);
			remake(x);remake(y);
		}
		else if(opt==2)
		{
			int nw=x;
			while(y>=base)
				nw=tmp[nw],y-=base;
			while(y)
				nw=nxt[nw],y--;
			printf("%d\n",nw);
		}
	}
}
```

---

## 作者：zhanghengrui (赞：0)

类似于分块的想法。

考虑把每个环拆成若干个大小不超过 $B$ 的块，维护每个块内的点和环上的下一个块、每个点所属块和在块内的编号；

先看交换操作：

- 如果 $x$ 和 $y$ 在同一个块内（不妨设块内 $x$ 在 $y$ 前），就是把 $(x, y]$ 这段拆出来单独成块，直接在 vector 里 copy、erase 即可，复杂度 $O(B)$；
- 如果 $x$ 和 $y$ 不在同一个块内，就是把 $x$ 所在块和 $y$ 所在块后的所有点以及两个块的 next 交换，同样是几次 copy、erase 的事，复杂度 $O(B)$。

（点的信息可以在操作过程中一起维护）

交换完之后，我们可以看刚刚操作的块，如果太大（大于 $B$）或者太小（和下一个块的大小之和不超过 $B$）就拆开 / 合并，这样可以保证每个块的大小都不超过 $B$ 且长为 $l$ 的环的块的个数为 $O(\frac{l}{B})$。~~（其实没有这个调整操作也[能过](https://codeforces.com/contest/1619/submission/144027676)，可能是数据太水了）~~

然后是询问，直接一个个块跳就行，复杂度 $O(\frac{n}{B})$。

取 $B = \sqrt{n}$，总时间复杂度 $O((n + q) \sqrt{n})$。

---

代码：

```cpp
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

constexpr unsigned short MAX_BLOCK_SIZE = 316;

struct Block {
  std::vector<unsigned long> nodes;
  unsigned long next;
};

struct Node {
  unsigned long block;
  unsigned short id;
};

int main() {
  unsigned long n, q;
  std::vector<bool> vis;
  std::vector<unsigned long> p;
  std::vector<Block> blocks;
  std::vector<Node> nodes;
  const auto adjustBlock = [&](unsigned long block) {
    if (blocks[block].next == block)
      return;
    if (blocks[block].nodes.size() + blocks[blocks[block].next].nodes.size() <=
        MAX_BLOCK_SIZE) {
      for (const auto &u : blocks[blocks[block].next].nodes) {
        nodes[u] = Node{
            block, static_cast<unsigned short>(blocks[block].nodes.size())};
        blocks[block].nodes.push_back(u);
      }
      blocks[block].next = blocks[blocks[block].next].next;
      return;
    }
    if (blocks[block].nodes.size() > MAX_BLOCK_SIZE) {
      const unsigned long newBlock = blocks.size();
      blocks.push_back(Block{{}, blocks[block].next});
      blocks[block].next = newBlock;
      std::copy(blocks[block].nodes.cbegin() + MAX_BLOCK_SIZE,
                blocks[block].nodes.cend(),
                std::back_inserter(blocks[newBlock].nodes));
      blocks[block].nodes.erase(blocks[block].nodes.cbegin() + MAX_BLOCK_SIZE,
                                blocks[block].nodes.cend());
      for (unsigned short i = 0; i < blocks[newBlock].nodes.size(); ++i)
        nodes[blocks[newBlock].nodes[i]] = Node{newBlock, i};
    }
  };
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin >> n >> q;
  p.resize(n);
  for (auto &item : p) {
    std::cin >> item;
    --item;
  }
  vis.assign(n, false);
  nodes.resize(n);
  for (unsigned long i = 0; i < n; ++i) {
    if (!vis[i]) {
      unsigned long u = i, firstBlock, block = blocks.size();
      blocks.push_back(Block{{}, block});
      firstBlock = block;
      do {
        if (blocks[block].nodes.size() == MAX_BLOCK_SIZE) {
          const unsigned long newBlock = blocks.size();
          blocks.push_back(Block{{}, newBlock});
          blocks[block].next = newBlock;
          block = newBlock;
        }
        nodes[u].block = block;
        nodes[u].id = blocks[block].nodes.size();
        blocks[block].nodes.push_back(u);
        vis[u] = true;
        u = p[u];
      } while (u != i);
      blocks[block].next = firstBlock;
    }
  }
  while (q--) {
    unsigned short t;
    std::cin >> t;
    switch (t) {
    case 1: {
      unsigned long x, y;
      std::cin >> x >> y;
      --x;
      --y;
      if (nodes[x].block == nodes[y].block) {
        const unsigned long block = blocks.size();
        if (nodes[x].id > nodes[y].id)
          std::swap(x, y);
        blocks.push_back(Block{{}, block});
        std::copy(blocks[nodes[x].block].nodes.cbegin() + nodes[x].id + 1,
                  blocks[nodes[x].block].nodes.cbegin() + nodes[y].id + 1,
                  std::back_inserter(blocks[block].nodes));
        blocks[nodes[x].block].nodes.erase(
            blocks[nodes[x].block].nodes.cbegin() + nodes[x].id + 1,
            blocks[nodes[x].block].nodes.cbegin() + nodes[y].id + 1);
        for (unsigned short i = 0; i < blocks[block].nodes.size(); ++i)
          nodes[blocks[block].nodes[i]] = Node{block, i};
        for (unsigned short i = nodes[x].id + 1;
             i < blocks[nodes[x].block].nodes.size(); ++i)
          nodes[blocks[nodes[x].block].nodes[i]].id = i;
        adjustBlock(nodes[x].block);
      } else {
        std::vector<unsigned long> v1, v2;
        std::copy(blocks[nodes[x].block].nodes.cbegin() + nodes[x].id + 1,
                  blocks[nodes[x].block].nodes.cend(), std::back_inserter(v1));
        std::copy(blocks[nodes[y].block].nodes.cbegin() + nodes[y].id + 1,
                  blocks[nodes[y].block].nodes.cend(), std::back_inserter(v2));
        blocks[nodes[x].block].nodes.erase(
            blocks[nodes[x].block].nodes.cbegin() + nodes[x].id + 1,
            blocks[nodes[x].block].nodes.cend());
        blocks[nodes[y].block].nodes.erase(
            blocks[nodes[y].block].nodes.cbegin() + nodes[y].id + 1,
            blocks[nodes[y].block].nodes.cend());
        for (const auto &u : v1) {
          nodes[u] = Node{
              nodes[y].block,
              static_cast<unsigned short>(blocks[nodes[y].block].nodes.size())};
          blocks[nodes[y].block].nodes.push_back(u);
        }
        for (const auto &u : v2) {
          nodes[u] = Node{
              nodes[x].block,
              static_cast<unsigned short>(blocks[nodes[x].block].nodes.size())};
          blocks[nodes[x].block].nodes.push_back(u);
        }
        std::swap(blocks[nodes[x].block].next, blocks[nodes[y].block].next);
        adjustBlock(nodes[x].block);
        adjustBlock(nodes[y].block);
      }
      break;
    }
    case 2: {
      unsigned long u, k;
      std::cin >> u >> k;
      --u;
      while (blocks[nodes[u].block].nodes.size() - nodes[u].id <= k) {
        k -= blocks[nodes[u].block].nodes.size() - nodes[u].id;
        u = blocks[blocks[nodes[u].block].next].nodes.front();
      }
      std::cout << blocks[nodes[u].block].nodes[nodes[u].id + k] + 1 << '\n';
      break;
    }
    }
  }
  return 0;
}
```

---

## 作者：Shunpower (赞：0)

不会根号分治。启动操作分块。

-----------------

显然题意是操作置换环，查询置换环上移动 $k$ 步之后的位置。

离线，考虑把所有操作按照 $B$ 个一块分块，我们每一轮集中处理一块的操作，最后重新维护好置换环。

考虑如果询问的点所在的置换环没有在这一块里面被操作过，那么它的形态一定是不变的。正如之前所说的，我们可以直接每块都 $\mathcal O(\frac{nq}{B})$ 地维护好，查询 $\mathcal O(1)$。

考虑如果操作过怎么办。我们不妨把所有操作过的位置断开，这样只有 $\mathcal O(B)$ 个位置是断开的，产生了 $\mathcal O(B)$ 个置换链，每个置换链都是这一块之前维护好的置换环的一部分。

每次查询的时候，我们可以强行跳置换链：类似树链剖分，我们跳向链尾，再暴力跳修改过的位置，以此类推。这样最多跳 $\mathcal O(B)$ 次就能摸清楚它所在的置换环的环长，取模之后我们也可以简单地 $\mathcal O(B)$ 找到它后面第 $k$ 个位置是谁：还是先暴力跳一堆置换链，不够跳的时候因为每个置换链就是一个置换环的部分，所以直接在之前维护好的置换环信息上查询就行了。

可以用记忆化搜索剖置换链，很好写。置换环的部分会恶心一点，但都是板子级别的处理。

总时间复杂度 $\mathcal O(qB+\frac{nq}{B})$，取 $B=\sqrt n$ 有最优复杂度 $\mathcal O(q\sqrt n)$。

```cpp
int n,q;
int p[N];
int len;
struct queries{
	int op,x,y;
} k[N];
bool vis[N];
bool met[N];
int nex[N],dis[N];
void dp(int x){
	if(met[x]){
		if(!nex[x]) dis[x]=-1e9;
		return;
	}
	if(vis[x]) return nex[x]=x,dis[x]=0,void();
	met[x]=1;
	dp(p[x]);
	nex[x]=nex[p[x]],dis[x]=dis[p[x]]+1;
}
int tot;
vector <int> loops[N];
int id[N],pos[N];
int find_next(int x,int step){
	return loops[id[x]][pos[x]+step];
}
void work(int L,int R){
	fr1(i,1,n) vis[i]=0;
	fr1(i,L,R){
		if(k[i].op==1) vis[k[i].x]=vis[k[i].y]=1;
	}
	fr1(i,1,n) nex[i]=dis[i]=met[i]=0;
	fr1(i,1,n) dp(i);
	fr1(i,1,n) met[i]=0;
	tot=0;
	fr1(i,1,n){
		if(met[i]) continue;
		int x=i;
		vector <int> perm;
		do{
			met[x]=1;
			perm.pb(x);
			x=p[x];
		}while(x!=perm[0]);
		int sz=perm.size()-1;
		fr1(j,0,sz) pos[perm[j]]=j,id[perm[j]]=tot+1;
		fr1(j,0,sz) perm.pb(perm[j]);
		tot++;
		loops[tot]=perm;
	}
	fr1(i,L,R){
		if(k[i].op==1) swap(p[k[i].x],p[k[i].y]);
		else{
			if(dis[k[i].x]<0){
				cout<<find_next(k[i].x,k[i].y%(loops[id[k[i].x]].size()/2))<<'\n';
				continue;
			}
			int nowp=nex[k[i].x];
			int len=0;
			int cnt=0;
			do{
				cnt++;
				nowp=p[nowp];
				len+=dis[nowp]+1;
				nowp=nex[nowp];
			}while(nowp!=nex[k[i].x]);
			k[i].y%=len;
			while(k[i].y>dis[k[i].x]){
				k[i].y-=dis[k[i].x]+1;
				k[i].x=p[nex[k[i].x]];
			}
			cout<<find_next(k[i].x,k[i].y)<<'\n';
		}
	}
	fr1(i,1,tot) loops[i].clear();
}
// #define Shun cute
int main(){
#ifdef Shun
	freopen("extreme.in","r",stdin);
	freopen("extreme.out","w",stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>n>>q;
	fr1(i,1,n) cin>>p[i];
	len=sqrt(n);
	int lst=1;
	fr1(i,1,q){
		cin>>k[i].op>>k[i].x>>k[i].y;
		if(i%len==0||i==q) work(lst,i),lst=i+1;
	}
	ET;
}
//ALL FOR Zhang Junhao.
```

---

