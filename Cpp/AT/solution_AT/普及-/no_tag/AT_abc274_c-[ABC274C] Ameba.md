# [ABC274C] Ameba

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc274/tasks/abc274_c

あなたはアメーバの観察記録をつけました。

最初 $ 1 $ 匹のアメーバがおり、番号は $ 1 $ です。

観察記録は時系列順に $ N $ 個あり、$ i $ 番目の観察記録は「番号 $ A_i $ のアメーバが分裂して消滅し、新たに $ 2 $ 匹のアメーバが生まれ、それらにそれぞれ $ 2i,2i+1 $ と番号をつけた」というものです。  
 このとき、アメーバ $ A_i $ を アメーバ $ 2i,2i+1 $ の親と呼びます。

各 $ k=1,\ldots,2N+1 $ について、アメーバ $ k $ から何代親を遡るとアメーバ $ 1 $ になるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- 観察記録は矛盾していない。すなわち
  - $ 1\leq\ A_i\ \leq\ 2i-1 $
  - $ A_i $ は相異なる整数

### Sample Explanation 1

アメーバ $ 1 $ からアメーバ $ 2,3 $ が生まれ、アメーバ $ 2 $ からアメーバ $ 4,5 $ が生まれました。 - アメーバ $ 1 $ は $ 0 $ 代遡るとアメーバ $ 1 $ になります。 - アメーバ $ 2 $ は $ 1 $ 代遡るとアメーバ $ 1 $ になります。 - アメーバ $ 3 $ は $ 1 $ 代遡るとアメーバ $ 1 $ になります。 - アメーバ $ 4 $ は $ 1 $ 代遡るとアメーバ $ 2 $ になり、$ 2 $ 代遡るとアメーバ $ 1 $ になります。 - アメーバ $ 5 $ は $ 1 $ 代遡るとアメーバ $ 2 $ になり、$ 2 $ 代遡るとアメーバ $ 1 $ になります。

## 样例 #1

### 输入

```
2
1 2```

### 输出

```
0
1
1
2
2```

## 样例 #2

### 输入

```
4
1 3 5 2```

### 输出

```
0
1
1
2
2
3
3
2
2```

# 题解

## 作者：JustForYourself (赞：3)

并不是一道难题。我们用 $rnk(i)$ 来维护第 $i$ 个节点到根节点的距离。

初始为 $rnk(1)=0$，显然。

对于 $i=1,2,...,N$，我们有 $rnk(2 \times i) = rnk(2 \times i + 1) = rnk(a_i) + 1$。接着模拟即可。

注意数组要开到 $2 \times N$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int rnk[400010];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	rnk[1] = 0;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		rnk[i * 2] = rnk[x] + 1;
		rnk[i * 2 + 1] = rnk[x] + 1;
	}
	for (int i = 1; i <= n * 2 + 1; i++) {
		cout << rnk[i] << endl;
	}
	return 0;
}
```

---

## 作者：RainSpark (赞：2)

# 题目大意

你做了变形虫的观察记录。

刚开始只有一个变形虫，编号为 $1$。

有 $N$ 条按时间顺序排列的观察记录，第 $i$ 条观察记录为编号为 $A_i$ 的变形虫分裂并消失，产生了 $2$ 个新的变形虫，分别编号为 $2i,2i+1$。

在这种情况下，变形虫 $A_i$ 被称为变形虫 $2i,2i+1$ 的父母。

对于第 $k=1,\ldots,2N+1$ 个变形虫，求 $1$ 号变形虫是 $k$ 号变形虫的第几代父母？

# 思路

前置：父亲结点表示法、DFS。

把每个变形虫看作二叉树上的一个结点，那么，从每个结点开始向上找最终都可以回到 $1$ 号结点。

所以，可以使用父亲节点表示法，$\texttt{fa[k]}$ 表示变形虫 $k$ 的第一代父母为 $\texttt{fa[k]}$。这样，对于每个结点进行一次 DFS，同时统计经过父母数即可。

# 优化

不排除数据中会出现极端情况（其实数据很水，裸的 DFS 就过了）：大部分结点都在一条链上，导致一条链重复查询而 TLE。可以使用记忆化搜索，再开一个数组 `f[k]`，赋初值为 $-1$，如果经过的某个结点已经在之前的查询中查到了，即 `f[k]！=-1`，那么就直接返回 `f[k]` 中的结果，或者记录，节省时间。

# 代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
const int N=800005;
using namespace std;
int n,a[N];
int fa[N],f[N];
int findfa(int x){
	if(x==1) return 0; //如果找到爹了
	if(f[x]!=-1) return f[x]; //记忆化搜索
	f[x]=1+findfa(fa[x]);
	return f[x];
} 
int main(){
	scanf("%d",&n);
	memset(f,-1,sizeof(f));
	fa[1]=1,f[1]=0; //注意初始化
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		fa[i*2]=a[i],fa[i*2+1]=a[i]; //记录父亲
	}
	for(int i=1;i<=2*n+1;i++)
		printf("%d\n",findfa(i));
    return 0;
}
```

------------

[赛时 AC 记录](https://atcoder.jp/contests/abc274/submissions/35880811)



---

## 作者：ttq012 (赞：0)

$\texttt{diff: }\color{gray}{315}$

题意：给定一颗二叉树，问 $1$ 号节点是 $i$ 号节点的多少代祖先，$i$ 是 $1\sim 2n + 1$ 中的所有整数。

题解：

因为这道题的难度只有 $315$，所以一定是使用很简单的方法，所以用非常简单的树剖的树上差分写。

由于 $1$ 号节点是根节点，所以问 $1$ 是 $i$ 的多少代祖先就是问 $1\sim i$ 的距离。

那么就可以在 $O(n\log n)$ 的时间使用 $O(\log n)$ 的树上差分求两点距离求出答案了。

Tips：

树剖需要建双向边。

比如说建边部分：

```cpp
// 随便举了一个栗子
void add(int a)
{
  z[a].push_back(i << 1);
  z[i << 1].push_back(a);
    // a<<1|1 同理
}
```



代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
const int N = 9e5 + 10;
int a[N];
vector <int> z[N];
int dfs_order[N], rk[N], cnt, top[N], len[N], fa[N], sz[N], dep[N], son[N];
void dfs1(int now, int fa = -1)
{
  if (now == 9)
  {
    cerr << "now 'now' = 9.\n";
    cerr << fa << ' ' << ::fa[now] << '\n';
  }
  dep[now] = dep[::fa[now]] + 1;
  sz[now] = 1;
  for (auto &u : z[now])
  {
    if (u == fa)
      continue ;
    ::fa[u] = now;
    dfs1(u, now);
    sz[now] += sz[u];
    if (sz[u] > sz[son[now]])
      son[now] = u;
  }
}

void dfs2(int now, int h, int fa = -1)
{
  cnt ++;
  dfs_order[cnt] = now;
  rk[now] = cnt;
  top[now] = h;
  len[h] ++;
  int p = -1;
  for (auto &u : z[now])
  {
    if (u == fa)
      continue ;
    if (p == -1)
      p = u;
    else if (sz[u] > sz[p])
      p = u;
  }
  if (p == -1)
    return ;
  dfs2(p, h, now);
  for (auto &u : z[now])
    if (p != u && u != fa)
      dfs2(u, u, now);
}

int lca(int x, int y)
{
  while (top[x] != top[y])
  {
    if (dep[top[x]] < dep[top[y]])
      swap (x, y);
    x = fa[top[x]];
  }
  if (dep[x] < dep[y])
    return x;
  return y;
}

int qdis(int u, int v)
{
  return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

signed main()
{
  cin >> n;
  for (int i = 1; i <= n; i ++)
  {
    int x;
    cin >> x;
    z[x].push_back(i << 1);
    z[x].push_back(i << 1 | 1);
    z[i << 1].push_back(x);
    z[i << 1 | 1].push_back(x);
  }
  dfs1(1);
  dfs2(1, 1);
  for (int i = 1; i <= 9; i ++)
    cerr << dep[i] << ' ';
  cerr << '\n';
  for (int i = 1; i <= (n << 1 | 1); i ++)
    cout << qdis(1, i) << '\n';
  return 0;
}

```



---

