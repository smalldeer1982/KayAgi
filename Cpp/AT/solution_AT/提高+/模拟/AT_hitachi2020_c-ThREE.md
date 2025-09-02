# ThREE

## 题目描述

[problemUrl]: https://atcoder.jp/contests/hitachi2020/tasks/hitachi2020_c

$ N $ 頂点の木があります。頂点には $ 1 $ から $ N $ までの番号がついており、 $ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を結んでいます。

$ 3 $ が大好きな高橋くんは、以下の条件を満たす $ 1 $ から $ N $ までの整数の順列 $ p_1,\ p_2,\ \ldots\ ,\ p_N $ を探しています。

- すべての頂点の組 $ (i,\ j) $ について、頂点 $ i $ と頂点 $ j $ の距離が $ 3 $ であるならば、$ p_i $ と $ p_j $ の和または積が $ 3 $ の倍数である。

ただし、頂点 $ i $ と頂点 $ j $ の距離とは、頂点 $ i $ から頂点 $ j $ へ最短経路で移動するときに使用する辺の個数のことを指します。

高橋くんのために条件を満たす順列を $ 1 $ つ見つけてください。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ a_i,\ b_i\ \leq\ N $
- 与えられるグラフは木である

### Sample Explanation 1

距離が $ 3 $ である頂点の組は $ (2,\ 4) $ と $ (2,\ 5) $ の $ 2 $ つです。 - $ p_2\ +\ p_4\ =\ 6 $ - $ p_2\times\ p_5\ =\ 6 $ であるため、この順列は条件を満たします。

## 样例 #1

### 输入

```
5
1 2
1 3
3 4
3 5```

### 输出

```
1 2 5 4 3```

# 题解

## 作者：StudyingFather (赞：25)

从反面考虑。什么时候会出现两个距离为 $3$ 的点的点权和以及点权积都不是 $3$ 的倍数的情况呢？

容易发现，当 $p_i \equiv p_j \equiv 1 \pmod 3$ 或 $p_i \equiv p_j \equiv 2 \pmod 3$ 时，如果 $i$ 和 $j$ 的距离为 $3$，构造出的树就不满足要求。

因此我们的目标是让满足上述条件的点之间的距离不为三。

从根节点开始进行黑白染色。设黑节点的数量为 $x$，白节点的数量为 $y$。

1. $x,y \gt \left \lfloor \dfrac{n}{3} \right \rfloor$

此时首先将所有满足 $i \equiv 1 \pmod 3$ 的 $i$ 分配给黑节点（显然此时所有满足条件的 $i$ 都会分配到黑节点），将所有满足 $i \equiv 2 \pmod 3$ 的 $i$ 分配到白节点，剩下的数（显然都满足 $3 \mid i$）随意分配。

因为所有满足 $i \equiv 1 \pmod 3$ 的节点颜色相同，这些节点间的距离必为偶数，从而不会出现不合要求的情况。

$i \equiv 2 \pmod 3$ 的节点同理。

2. $x \leq \left \lfloor \dfrac{n}{3} \right \rfloor$

将满足 $3 \mid i$ 的 $i$ 分配给黑节点（显然不会有节点分不到数字），剩下的全给白节点。

这时候所有满足 $i \equiv 1 \pmod 3$ 或 $i \equiv 2 \pmod 3$ 的节点全为白节点，也不会出现不合要求的情况。

3. $y \leq \left \lfloor \dfrac{n}{3} \right \rfloor$

和 2 情况同理，不再赘述。

综上，我们对于每一种树，都可以构造一种满足条件的方案。

```cpp
#include <iostream>
#include <vector>
using namespace std;
int col[200005],p[200005],cnt0,cnt1;
vector<int> e[200005];
void dfs(int u,int fa)
{
 col[u]=!col[fa];
 if(col[u])cnt1++;
 else cnt0++;
 for(auto v:e[u])
  if(v!=fa)dfs(v,u);
}
int main()
{
 int n;
 cin>>n;
 for(int i=1;i<n;i++)
 {
  int u,v;
  cin>>u>>v;
  e[u].push_back(v);
  e[v].push_back(u);
 }
 dfs(1,1);
 int p1=1,p2=2,p3=3;
 if(cnt0>n/3&&cnt1>n/3)
 {
  for(int i=1;i<=n;i++)
   if(col[i]==0)
   {
    if(p1<=n)p[i]=p1,p1+=3;
    else p[i]=p3,p3+=3;
   }
   else
   {
    if(p2<=n)p[i]=p2,p2+=3;
    else p[i]=p3,p3+=3;
   }
 }
 else if(cnt1<=n/3)
 {
  for(int i=1;i<=n;i++)
   if(col[i]==0)
   {
    if(p1<=n)p[i]=p1,p1+=3;
    else if(p2<=n)p[i]=p2,p2+=3;
    else p[i]=p3,p3+=3;
   }
   else
    p[i]=p3,p3+=3;
 }
 else if(cnt0<=n/3)
 {
  for(int i=1;i<=n;i++)
   if(col[i]==1)
   {
    if(p1<=n)p[i]=p1,p1+=3;
    else if(p2<=n)p[i]=p2,p2+=3;
    else p[i]=p3,p3+=3;
   }
   else
    p[i]=p3,p3+=3;
 }
 for(int i=1;i<=n;i++)
  cout<<p[i]<<' ';
 cout<<endl;
 return 0;
}
```

---

## 作者：KokiNiwa (赞：4)

# C-ThREE

[Social Infrastructure Information Systems Division, Hitachi Programming Contest 2020](https://atcoder.jp/contests/hitachi2020)

这场比赛里的一道构造题。

## 题目叙述

给你一颗$n$个结点的树，你要把$1\sim n$填进去，使得树上任意距离为$3$的点都满足填进去的数的和或者乘积至少一个是$3$的倍数。

## 题解

我的构造好弱呀......

+ 和或者积至少一个是$3$的倍数，等价于不为$1,1$也不为$2,2$（这题之所以能做也就因为这个条件可以转化为两个数模$1$不同这种形式吧...

+ 考虑黑白染色。那么同色的两点距离显然不是$3$。考虑把模$3$余$1$的数放一种颜色的点，模$3$余$2$的放另一种颜色。
+ 可能黑色点或白色点数量不够
  + 如果$\min(white, black)\le \frac{n}{3}$。那么考虑把所有模$3$余$0$的点都放在较少的那种颜色上。其余的点随便放。
  + 否则，模$3$余$1$的放黑色点上，模$3$余$2$的放白色点上。

## 知识点

+ 距离为$3$的颜色不同，可以考虑黑白染色。

## 代码

```cpp
#include <cstdio>
#include <vector>
using namespace std;
const int maxNode = 2e5 + 5;
vector<int> tree[maxNode];
int nbNode, ans[maxNode];
vector<int> col[2], kind[3];
void Dfs(int now, int from, int faCol) {
	col[faCol ^ 1].push_back(now);
	for (int to : tree[now]) {
		if (to == from) continue ;
		Dfs(to, now, faCol ^ 1);
	}
}
int main() {
	scanf("%d", &nbNode);
	for (int edge = 1; edge < nbNode; ++edge) {
		int u, v;
		scanf("%d%d", &u, &v);
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	for (int num = 1; num <= nbNode; ++num)
		kind[num % 3].push_back(num);
	Dfs(1, -1, 1);
	if (col[0].size() > col[1].size())
		swap(col[0], col[1]);
	if (col[0].size() <= kind[0].size()) {
		int now = 0, pt = 0;
		for (int node : col[0])
			ans[node] = kind[0][pt++];
		if (pt >= kind[0].size()) {
			++now;
			pt = 0;
		}
		for (int node = 1; node <= nbNode; ++node)
			if (!ans[node]) {
				ans[node] = kind[now][pt++];
				if (pt >= kind[now].size()) {
					pt = 0;
					++now;
				}
			}
	} else {
		int pt = 0;
		for (int num : kind[1])
			ans[col[0][pt]] = num, ++pt;
		pt = 0;
		for (int num : kind[2])
			ans[col[1][pt]] = num, ++pt;
		pt = 0;
		for (int node = 1; node <= nbNode; ++node)
			if (!ans[node])
				ans[node] = kind[0][pt++];
	}
	for (int node = 1; node <= nbNode; ++node)
		printf("%d ", ans[node]);
	printf("\n");
	return 0;
}
```



---

## 作者：Sol1 (赞：3)

显然答案只和每一个点的点权模 $3$ 的值有关，问题变为用 $x$ 个 $0$，$x$ 或 $x+1$ 个 $1$，$x$ 或 $x+1$ 个 $2$ 覆盖给定的树，且满足题目中条件。

不难发现 $0$ 有很强的特殊性，因为选择 $0$ 的点不需要考虑其他点的权值就可以满足条件。不妨先去掉 $0$，考虑 **仅用 $1$ 和 $2$ 且不考虑数量限制如何覆盖。**

考虑建一个图 $G$。对于一对点 $(i,j)$，如果其距离在树中是 $3$，则在 $G$ 中连一条 $i\leftrightarrow j$ 的边。

那么现在可以发现 **原树中的一个用 $1$ 和 $2$ 的覆盖方案对应到 $G$ 中是一个二分图染色方案。**

当然 $G$ 的边数是爆炸的，不能直接求染色。但是我们发现如果直接按树中深度的奇偶性染色，就必然是 $G$ 的一个二分图染色。

那么现在可以构造仅用 $1$ 和 $2$ 且不考虑数量限制的覆盖方案了，考虑加入 $0$ 和数量限制。

不难发现一个点选 $0$ 相当于直接从 $G$ 中删去该点。

那么如果两侧的点数量都大于等于对应的数量限制，就直接删到对应的数量限制就行了。

如果有一侧小于对应的数量限制，那么显然这一侧可以全部删掉，剩下的直接随便填也可以满足限制。

于是这题就做完了，复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[(1<<21)+5], *p1 = buf, *p2 = buf;

inline int qread() {
	char c = getchar();
	int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

struct Edge {
	int to, nxt;
	Edge() {
		nxt = -1;
	}
};
Edge e[400005];
int n, hd[200005], pnt, ans[200005];
bool flag[200005];
vector <int> a, b;

inline void AddEdge(int u, int v) {
	e[++pnt].to = v;
	e[pnt].nxt = hd[u];
	hd[u] = pnt;
}

inline void Read() {
	n = qread();
	for (int i = 1;i < n;i++) {
		int u = qread(), v = qread();
		AddEdge(u, v);
		AddEdge(v, u);
	}
}

inline void Dfs(int u, int fa, int dep) {
	if (dep & 1) a.push_back(u);
	else b.push_back(u);
	for (int i = hd[u];~i;i = e[i].nxt) {
		if (e[i].to != fa) Dfs(e[i].to, u, dep + 1);
	}
}

inline void Solve() {
	if (a.size() < b.size()) swap(a, b);
	int sz1 = a.size(), sz2 = b.size(), cnt0 = n / 3, cnt1 = n / 3 + (n % 3 >= 1), cnt2 = n / 3 + (n % 3 >= 2);
	if (sz2 <= cnt0) {
		for (int i = 0;i < sz2;i++) {
			ans[b[i]] = 3 * (i + 1);
			flag[3 * (i + 1)] = 1;
		}
		for (int i = 0;i < sz1;i++) {
			if (i) ans[a[i]] = ans[a[i - 1]];
			else ans[a[i]] = 1;
			while (flag[ans[a[i]]]) ans[a[i]]++;
			flag[ans[a[i]]] = 1;
		}
	} else {
		int cur = 0;
		for (int i = 0;i < cnt1;i++) ans[a[i]] = 3 * i + 1;
		for (int i = 0;i < cnt2;i++) ans[b[i]] = 3 * i + 2;
		for (int i = cnt1;i < sz1;i++) ans[a[i]] = 3 * (++cur);
		for (int i = cnt2;i < sz2;i++) ans[b[i]] = 3 * (++cur);
	}
	for (int i = 1;i <= n;i++) printf("%d ", ans[i]);
}

int main() {
	memset(hd, -1, sizeof(hd));
	Read();
	Dfs(1, -1, 1);
	Solve();
	return 0;
}
```

---

## 作者：ylxmf2005 (赞：2)

### Description
有一棵 $n$ 个点的无根树，边权为一。求一个 $1 \sim n$ 的排列 $p_1 \sim p_n$，使得对于任意两个下标 $(i,j)$ 如果点 $i$ 与点 $j$ 在树上的距离为 $3$ 那么 $p_i + p_j | 3 \lor p_ip_j | 3$。有多个随意输出一个，如果没有输出 $-1$。

### Solution
~~根据样例~~，不可能没有方案。

令 $1$ 为根节点，将 $1 \sim n$ 的每个数 $\bmod \ 3$。因为一个数加 $\pm 3$ 它的奇偶性一定改变，不妨用黑白染色的方法，将每个点按与根节点距离的奇偶性分类。

对于一个数对 $p_i,p_j$ 假设 $p_i \leq p_j$。如果 $i$ 和 $j$ 的距离为 $3$ 那么有 $p_i = 1,p_j = 2 \lor p_i = 0, p_j = \{ 0,1,2 \}$。

所以构造方案非常简单，先在能将 $1,2$ 分完的前提下，尽量把它们分在不同奇偶性的点集中，再把 $0$ 分给余下的点。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int N = 2e5 + 5, INF = 0x3f3f3f3f;
inline int read() {
	int x = 0, f = 0; char ch = 0;
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
int ans[N];
vector <int> G[N], col[2], mod[3];
void dfs(int x, int c, int fa) {
	col[c].push_back(x);
	for (auto y : G[x]) if (y != fa) dfs(y, c ^ 1, x);
}
void sol(int i, int j) {
	while (!col[i].empty() && !mod[j].empty()) {
		ans[col[i].back()] = mod[j].back();
		col[i].pop_back(), mod[j].pop_back();
	}
}
int main() {
	int n = read();
	for (int i = 1; i < n; i++) {
		int x = read(), y = read();
		G[x].pb(y), G[y].pb(x);
	}
	for (int i = 1; i <= n; i++) mod[i % 3].pb(i);
	dfs(1, 0, 0);
	sol(col[0].size() < col[1].size(), 1), sol(col[0].size() < col[1].size(), 2);
	sol(0, 0), sol(1, 0);
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}     
```

---

## 作者：Aiopr_2378 (赞：2)

# Solution AT5759 ThREE

很显然，我们构造的排列中，一定有 $a\equiv0\pmod{m}$ 、 $a\equiv1\pmod{m}$ 和 $a\equiv2\pmod{m}$ 这三种情况。

我们用 $1,2,3$ 分别表示除 $3$ 余 $1,2,3$ 的情况。

那么，如果这是一个链，就很简单：按照 $1,2,1,2,1,2...a,2$ 的顺序排列，然后，0就可以随便插入(任何数 $\times0$ 还是 $0$ )。

那如何扩大到一颗树？

参考链的情况，深度为偶数的填 $1$ ，为奇数的填 $0$ 。 $0$ 依旧还是随便填。

所以我们需要进行dfs算出每个节点的深度。

同时，若个数较少的那一组个数 $\leq n/3$ ，我们可以优先填 $0$ 。对于个数多的那一组，我们可以优先填 $1$ .

参考代码：

```cpp
#include<iostream>
#include<vector>
using namespace std;
int n,num[200005],ans[200005];
vector<int> v[3],a[200005],c[2];
void dfs(int x,int fa){
	num[x]=num[fa]^1;
	c[num[x]].push_back(x);
	for(int i=0;i<a[x].size();i++){
		int v=a[x][i];
		if(v!=fa) dfs(v,x);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) v[i%3].push_back(i);
	for(int i=1;i<n;i++){
		int v,w;
		cin>>v>>w;
		a[v].push_back(w);
		a[w].push_back(v);
	}
	dfs(1,0);
	if(c[0].size()>c[1].size()) swap(c[0],c[1]);
	if(c[0].size()<=n/3){
		for(int i=0;i<c[0].size();i++){
			int w=c[0][i];
			ans[w]=v[0].back();
			v[0].pop_back();
		}
		for(int i=0;i<c[1].size();i++){
			int w=c[1][i];
			for(int j=0;j<3;j++){
				if(v[j].size()){
					ans[w]=v[j].back();
					v[j].pop_back();
					break;
				}
			}
		}
	}
	else{
		for(int i=0;i<c[0].size();i++){
			int w=c[0][i];
			if(v[1].size()){
				ans[w]=v[1].back();
				v[1].pop_back();
			}
			else{
				for(int j=0;j<3;j++){
					if(v[j].size()){
						ans[w]=v[j].back();
						v[j].pop_back();
						break;
					}
				}
			}
		}
		for(int i=0;i<c[1].size();i++){
			int w=c[1][i];
			for(int j=0;j<3;j++){
				if(v[j].size()){
					ans[w]=v[j].back();
					v[j].pop_back();
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
```

谢谢观看

---

## 作者：Durancer (赞：1)

### 题目描述

> 给定一颗 $n$ 个节点的树，要求把 $1-n$ 给分配到每一个节点上作为权值，要求任意距离为 $3$ 的点对的权值之和或者乘积为 $3$ 的倍数。

> $n\leq2\times 10^5$

### 思路

寻找一颗树中距离为 $3$ 的点对不难找到，但是枚举肯定会 $\text{TLE}$，我们手膜一下样例发现，其实就是一些有根树(根暂定为 $1$ )中的深度奇偶性不同的点进行配对。

我们把分配的数可以分为三类：取模后分别为 $0,1,2$ 的数。

如果不考虑 $0$ 的贡献，那么深度为奇数的点分配的和深度为偶数的点分配的点的值奇偶性要不同才可以，因为只能根据求和来满足条件。

首先，如果深度为奇数的点，偶数的点其中一个或者是两个的数量小于取模后为 $0$ 的值的个数，那么就可以把数量较小的哪一组点，全部弄成 $3$ 的倍数即可，然后其余一组随便放都会符合条件。

另外一种情况，如果两组都大于取模后 $0$ 的个数，那么就考虑先把偶数部分的赋值为 $3i+2$ ，该奇数的赋值为 $3i+1$ ，然后剩下的超出部分全部赋值为 $3i$ 即可。

### 代码实现

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2e5+9;
const int M=2e5+9;
struct node{
	int last;
	int to;
}e[N<<1];
int head[N],cnt;
int n,Q;
int ans[N];
vector<int> a;//奇数深度 
vector<int> b;//偶数深度 
bool vis[N];
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
void add(int from,int to)
{
	e[++cnt].last=head[from];
	e[cnt].to=to;
	head[from]=cnt;
}
void dfs(int u,int fa,int dep)
{
	if(dep%2) a.push_back(u);
	else b.push_back(u);
	for(int i=head[u];i;i=e[i].last)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u,dep+1);
	}
}
void work()
{
	if(a.size()<b.size())
		swap(a,b);//选用b作为数量较小的那个
	int Asiz=a.size();
	int Bsiz=b.size();
	int cnt0=n/3 , cnt1=n/3+(n%3>=1) , cnt2=n/3+(n%3>=2);
	//printf("0 = %d , 1 = %d , 2 = %d \n",cnt0,cnt1,cnt2);
	//printf("奇数= ");
	//for(int i=0;i<Asiz;i++)
	//	printf("%d ",a[i]);
	//printf("偶数= ");
	//for(int i=0;i<Bsiz;i++)
	//	printf("%d ",b[i]); 
	int tot=1;
	if(Bsiz<=cnt0)//可以全部用0包围 
	{
		for(int i=0;i<b.size();i++)
		{
			ans[b[i]]=(i+1)*3;
			vis[(i+1)*3]=true;
		}
		for(int i=0;i<a.size();i++)
		{
			ans[a[i]]=tot;
			vis[tot]=true;
			while(vis[tot])
				tot++; 
		}
	}  
	else
	{
		for(int i=0;i<cnt1;i++)
			ans[a[i]]=i*3+1;
		for(int i=0;i<cnt2;i++)
			ans[b[i]]=i*3+2;
		for(int i=cnt1;i<Asiz;i++)
			ans[a[i]]=(tot++)*3;
		for(int i=cnt2;i<Bsiz;i++)
			ans[b[i]]=(tot++)*3;
	}
}
int main()
{
	n=read();
	for(int i=1;i<n;i++)
	{ 
		int u=read();
		int v=read();
		add(u,v);
		add(v,u);
	}
	dfs(1,0,1);
	work();
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}

```

---

