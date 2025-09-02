# Restore the Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_d

$ N $ 頂点の根付き木 (注記を参照) があり、その頂点には $ 1 $ から $ N $ までの番号が振られています。 根以外の各頂点には、その親から一本の有向辺が伸びています。 なお、根は頂点 $ 1 $ とは限りません。

高橋くんは、このグラフに $ M $ 本の新たな有向辺を書き加えました。 書き足された各辺 $ u\ \rightarrow\ v $ は、ある頂点 $ u $ からその子孫であるような頂点 $ v $ に向かって伸びています。

高橋くんが辺を書き加えたあとの $ N $ 頂点 $ N-1+M $ 辺の有向グラフが与えられます。 より具体的には、$ N-1+M $ 組の整数のペア $ (A_1,\ B_1),\ ...,\ (A_{N-1+M},\ B_{N-1+M}) $ が与えられ、これらは $ i $ 番目の辺が頂点 $ A_i $ から頂点 $ B_i $ に向かって伸びていることを表します。

元の根付き木を復元してください。

## 说明/提示

### 注記

「木」や関連するグラフ理論の用語に関しては、[Wikipediaの記事](https://ja.wikipedia.org/wiki/%E6%9C%A8_(%E6%95%B0%E5%AD%A6))などをご覧ください。

### 制約

- $ 3\ \leq\ N $
- $ 1\ \leq\ M $
- $ N\ +\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- $ A_i\ \neq\ B_i $
- $ i\ \neq\ j $ ならば $ (A_i,\ B_i)\ \neq\ (A_j,\ B_j) $
- 入力されるグラフは、$ N $ 頂点の根付き木に問題文中の条件を満たす $ M $ 本の辺を書き足すことで得られる。

### Sample Explanation 1

入力されたグラフは次のようなものです。 !\[\](https://img.atcoder.jp/nikkei2019-qual/ee05880ceecf703f656dd50bf22c573f.png) これは、$ 1\ \rightarrow\ 2\ \rightarrow\ 3 $ という根付き木に辺 $ 1\ \rightarrow\ 3 $ を書き足したものであると考えられます。

## 样例 #1

### 输入

```
3 1
1 2
1 3
2 3```

### 输出

```
0
1
2```

## 样例 #2

### 输入

```
6 3
2 1
2 3
4 1
4 2
6 1
2 6
4 6
6 5```

### 输出

```
6
4
2
0
6
2```

# 题解

## 作者：igAC (赞：1)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_nikkei2019_qual_d)

[ATlink](https://atcoder.jp/contests/nikkei2019-qual/tasks/nikkei2019_qual_d)

简要题意：

$n$ 个节点组成了一棵有根树，后面又增加了 $m$ 条有向边。

于是就成了 $n+m-1$ 条边的有向图，输入给定这个图。

这 $m$ 条边都是从原树的一个节点连上了自己的后代。

请求出原树的结构（对于节点 $1 \sim n$ 输出每个节点的父亲，如果是根节点则输出 $0$）。

Translated by WSXZCLXS

~~麻烦管理把上面这段翻译也提交了吧，谢谢。~~

# $\text{Solution}$

简单图论题。

由于 $m$ 条边都是由深度小的向深度大的连边。

所以根节点一定是唯一没有入度的点。

接下来我们就可以进行拓扑排序。

因为先遍历的节点是深度较小的节点，所以拓扑排序删掉的最后一条入边的起点就是这个节点的父亲。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m,in[N],out[N],fa[N];
int head[N],tot;
struct Edge{
	int to,nxt;
}e[N<<1];
void add_edge(int x,int y){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	head[x]=tot;
}
void topo(){
	queue<int>q;
	for(int i=1;i<=n;++i){
		if(!in[i]){
			q.push(i);
			fa[i]=0;
		}
	}
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(!(--in[y])){
				q.push(y);
				fa[y]=x;
			}
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n+m-1;++i){
		int x=read(),y=read();
		add_edge(x,y);
		++out[x],++in[y];
	}
	topo();
	for(int i=1;i<=n;++i) printf("%d\n",fa[i]);
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## Restore the Tree

对于 $u_i \to v$ 的边，其实限制的就是 $d(v) = \max \{d(u_i)\} + 1$，然后通过跑拓扑就可以算出每个点的深度。

然后一个树上 $u$ 是 $v$ 的父节点的条件是 $d(v) = d(u) + 1$ 且 $v,u$ 之间连边。

于是发现 $d(v)$ 是由最大的 $d(u)+ 1$ 得到的，即拓扑中最后一个访问的 $u$，也即删掉后使 $v$ 没有入度的那个点。拓扑时记录 $p_v = u$ 即可。

```cpp
n = read(), m = read();
for (int i = 1, x, y; i < n + m; ++i)
  x = read(), y = read(), e[x].push_back(y), ++deg[y];
for (int i = 1; i <= n; ++i)
  if (!deg[i]) q.push(i);
while (q.size()) {
  int x = q.front(); q.pop();
  for (const int &y : e[x])
    if (!--deg[y]) p[y] = x, q.push(y);
}
for (int i = 1; i <= n; ++i) printf("%d\n", p[i]);
```

---

## 作者：_Flame_ (赞：0)

## $\text{solution}$

求原树的结构，即要求出原树上每一个点的父亲，很像一个拓扑排序的题。

考虑先找到根节点，由于每条边都是有向边，且都连上自己的后代，所以当一个点入度为零时，它一定是原树的根。

然后我们发现如果一个点 $u$ 向一个点 $v$ 连边时，$u$ 一定是 $v$ 的祖先，必定在 $v$ 之前输出，这个时候就可以进行拓扑排序了。

从根往下遍历，对于每一个点，最后一条遍历到的入边的起点为这个点的父亲，每遍历到一条边更新答案，最后输出即可。

[code](https://www.luogu.com.cn/paste/ebm48rde)

---

