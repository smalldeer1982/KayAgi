# [JOIG 2025] 最悪の記者 5 / Worst Reporter 5

## 题目背景

水獭乌苏太郎是一名报社记者，正在报道附近举行的一场大型马拉松比赛。

## 题目描述

共有 $N$ 名运动员参加比赛，编号从 $1$ 到 $N$ 。乌苏太郎在报道比赛时，在笔记中记录了如下信息：

- 比赛开始时，$N$ 名运动员位于不同的位置上；
- 比赛过程中，排名变化恰好发生了 $M$ 次：在第 $i(1\le i\le M)$ 次排名变化中，运动员 $A_i$ 和 $B_i$ 交换位置，保证排名变化前两位运动员之间没有其他运动员；
- 没有两个排名变化同时发生。

乌苏太郎想在报纸上刊登一张排名表，表示比赛结束后运动员的排名：排名表是一个长度为 $N$ 的序列 $P$，其中 $P_j$ 代表排名为 $j$ 的运动员的编号。

然而乌苏太郎并没有记录排名表，也没有记录每次排名变化时哪一方的排名上升（即不知道是 $A_i$ 超过了 $B_i$ 还是反之）。于是他想让你判断是否存在一个排名表，使得不与他记录的信息矛盾；如果存在，他想让你求出字典序最小的排名表。

称一个长度为 $N$ 的排名表序列 $a$ 在字典序上小于另一个长度为 $N$ 的排名表序列 $b$，当且仅当存在一个 $k(1\le k\le N)$ 满足如下条件：

- $a_l=b_l(1\le l\le k-1)$；
- $a_k<b_k$。

## 说明/提示

#### 【样例解释 #1】

假设比赛开始时，运动员排名为 $1,2,3,5,4$。

比赛过程如下：

- 在第 $1$ 次排名变化中，运动员 $1,2$ 交换位置，排名变为 $2,1,3,5,4$；
- 在第 $2$ 次排名变化中，运动员 $4,5$ 交换位置，排名变为 $2,1,3,4,5$；
- 在第 $3$ 次排名变化中，运动员 $3,4$ 交换位置，排名变为 $2,1,4,3,5$；
- 在第 $4$ 次排名变化中，运动员 $3,5$ 交换位置，排名变为 $2,1,4,5,3$；
- 在第 $5$ 次排名变化中，运动员 $1,4$ 交换位置，排名变为 $2,4,1,5,3$；

最终的排名表 $P=\{2,4,1,5,3\}$。可以证明这是字典序最小的。

该样例满足子任务 $1,3,5$ 的限制。

#### 【样例解释 #2】

不存在与给定信息不矛盾的排名表。

该样例满足子任务 $1,3,5$ 的限制。

#### 【样例解释 #3】

该样例满足所有子任务的限制。

#### 【样例解释 #4】

该样例满足子任务 $1,3,4,5$ 的限制。

#### 【数据范围】

- $2\le N\le 5\times 10^5$；
- $1\le M\le 5\times 10^5$；
- $1\le A_i<B_i\le N(1\le i\le M)$。

#### 【子任务】

1. （$13$ 分）$N,M\le 8$；
2. （$16$ 分）$A_1,A_2,\ldots,A_M,B_1,B_2,\ldots,B_M$ 两两不同；
3. （$29$ 分）$N,M\le 1000$；
4. （$23$ 分）在第 $i(2\le i\le M)$ 次排名变化中，$A_i$ 和 $B_i$ 中至少有一个值在 $A_1,A_2,\ldots,A_{i-1},B_1,B_2,\ldots,B_{i-1}$ 中没有出现；
5. （$19$ 分）无附加限制。

## 样例 #1

### 输入

```
5 5
1 2
4 5
3 4
3 5
1 4```

### 输出

```
Yes
2
4
1
5
3```

## 样例 #2

### 输入

```
3 4
1 3
2 3
1 3
2 3```

### 输出

```
No```

## 样例 #3

### 输入

```
8 3
1 8
3 5
4 7```

### 输出

```
Yes
1
8
2
3
5
4
7
6```

## 样例 #4

### 输入

```
6 5
1 2
1 3
1 4
1 5
1 6```

### 输出

```
Yes
1
6
5
4
3
2```

# 题解

## 作者：GUO120822 (赞：2)

图论建模。

令 $id_i$ 表示 $i$ 号运动员在最后一轮的 $id_i$ 号运动员的位置。

倒着建边，初始 $id_i=i$。

每次对于 $id_{x_i}$ 和 $id_{y_i}$ 建边，表示 $id_{x_i}$ 和 $id_{y_i}$ 运动员在最后一轮相邻。

所以建边之后的 $x$ 连接 $y$ 表示 $x$ 与 $y$ 在最后一轮相邻。

然后若有度数大于二的，直接无解。

如果有环，直接无解。

其他情况，找到每个联通块度为一的最小点。

然后直接一一遍历即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
struct FSI{
	template<typename T>
	FSI& operator >> (T &res){
		res=0;T f=1;char ch=getchar();
		while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
		while (isdigit(ch)){res=res*10+ch-'0';ch=getchar();}
		res*=f;
		return *this;
	}
}scan;
const int N=6e5+10,M=1e6+10;
int n,m,i,x[M],y[M]; 
int last[N],c;
int id[N];
int ans[N],k,d[N];
bool vis[N],v[M];
struct Node{
	int to,next;
}a[M<<1];
struct node{
	int u,v;
}e[M];
void add(int u,int v)
{
	a[++c]={v,last[u]};
	last[u]=c;
}
void dfs(int x)
{
	int i,to;
	vis[x]=true;
	ans[++k]=x;
	for (i=last[x];i;i=a[i].next)
	{
		to=a[i].to;
		if (!vis[to]) dfs(to);
	}
}
bool cmp(node x,node y){return x.u<y.u||(x.u==y.u&&x.v<y.v);}
int main()
{
	scan>>n>>m;
	for (i=1;i<=m;i++) scan>>x[i]>>y[i];
	for (i=1;i<=n;i++) id[i]=i;
	for (i=m;i>=1;i--)
	{
		e[i]={id[x[i]],id[y[i]]};
		if (id[x[i]]>id[y[i]]) swap(e[i].u,e[i].v);
		swap(id[x[i]],id[y[i]]);
	}
	sort(e+1,e+m+1,cmp);
	for (i=1;i<=m;i++)
	{
		if (e[i].u==e[i-1].u&&e[i].v==e[i-1].v) v[i]=true;
	}
	for (i=1;i<=m;i++)
	{
		if (!v[i])
		{
			add(e[i].u,e[i].v);
			add(e[i].v,e[i].u);
			d[e[i].u]++;
			d[e[i].v]++;
		}
	}
	for (i=1;i<=n;i++) if (d[i]>2){puts("No");return 0;}
	for (i=1;i<=n;i++)
	{
		if (!vis[i])
		{
			if (!d[i]) ans[++k]=i,vis[i]=true;
			else if (d[i]==1) dfs(i);
		}
	}
	if (k!=n){puts("No");return 0;}
	puts("Yes");
	for (i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：E_M_T (赞：2)

## 题意

一个排列 $S$，经过 $m$ 次交换**相邻**数得到 $T$，求 $T$ 最小字典序。


这题真的有蓝吗，做下来感觉没有大的瓶颈。

考虑 sub2，交换两个数 $x,y$ 即要求 $x,y$ 在原排列 $S$ 中相邻。下文“相邻”都指在原排列 $S$ 中相邻。

拓展到一般情况，若交换 $x,y$ 和 $y,z$，要求的是 $x,y$ 相邻以及 $x,z$ 相邻，因为 $y,z$ 交换前 $x,y$ 交换了。

于是设辅助数组 $id_x$，初始时 $id_x=x$。


交换 $x$ 和 $y$ 即要求 $id_x$ 和 $id_y$ 相邻。

用一条端点为 $id_x$ 和 $id_y$ 的边记录这个信息，并交换 $id_x$ 与 $id_y$。注意判重边。

因为每个数只能和两个数相邻，所以一个点最多两个度。最后合法的图一定是一些链和单独的点。

这些链和点维护的是 $S$ 的信息，所以如果直接把他们贪心的拼起来得到是 $S$ 字典序最小。

于是将 $m$ 次交换完成之后再贪心的将这些链点组合即可。

```cpp
#include<bits/stdc++.h>
#define sd std::
//#define int long long
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define ff(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define me(x,y) memset(x,y,sizeof x)
#define pii sd pair<int,int>
#define X first
#define Y second
#define Fr(a) for(auto it:a)
int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
void put(int x){print(x);putchar('\n');}
void printk(int x){print(x);putchar(' ');}
const int N=1e6+10;
int n,m,id[N],cnt,d[N],vis[N],fa[N];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]); 
}
void merge(int x,int y)
{
	x=find(x),y=find(y);
	fa[x]=y;
}
struct node
{
	int nex;
	int to;
}a[N<<1];
int tot,head[N];
void add(int u,int v)
{
	a[++tot].nex=head[u];
	head[u]=tot;
	a[tot].to=v;
}
sd map<pii,int> mp;//判重边
sd vector<int> g[N];
void dfs(int u)
{
	g[cnt].emplace_back(u);
	for(int i=head[u];i;i=a[i].nex)
	{
		int v=a[i].to;
		if(vis[v]) continue;
		vis[v]=1;
		dfs(v);
	}
}
pii p[N];
int cmp(pii x,pii y)
{
	return x.X<y.X;
}
int ans[N],res,po1[N],po2[N];
void solve()
{
	n=read(),m=read();
	F(i,1,n) id[i]=fa[i]=i;
	F(i,1,m)
	{
		int x=read(),y=read();
		po1[i]=x,po2[i]=y;
		if(mp[{id[x],id[y]}])
		{
			sd swap(id[x],id[y]);
			continue;
		}
		if(find(id[x])==find(id[y])) return puts("No"),void();
		merge(id[x],id[y]);
		mp[{id[x],id[y]}]=mp[{id[y],id[x]}]=1;
		add(id[x],id[y]);
		add(id[y],id[x]);
		d[id[x]]++;
		d[id[y]]++;
		sd swap(id[x],id[y]);
	}
	F(i,1,n) if(d[i]>2) return puts("No"),void();
	F(i,1,n)
	{
		if(!vis[i]&&d[i]<=1)//从端点遍历记录一个链
		{
			++cnt;
			vis[i]=1;
			dfs(i);
		}
	}
	
	F(i,1,cnt)
	{
		int k1=g[i].size();
		F(j,0,k1-1) p[g[i][j]].X=i,p[g[i][j]].Y=j;
	}
	F(i,1,m)
	{
		sd swap(p[po1[i]].Y,p[po2[i]].Y);
	}
	F(i,1,n) g[p[i].X][p[i].Y]=i;
	F(i,1,cnt)
	{
		int k1=g[i].size();
		if(g[i][0]>g[i][k1-1]) reverse(g[i].begin(),g[i].end());
		p[i].X=g[i][0];
		p[i].Y=i;
	}
	sd sort(p+1,p+1+cnt,cmp);
	puts("Yes");
	F(i,1,cnt)
	{
		Fr(g[p[i].Y]) put(it);
	}
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：wxccd2z (赞：2)

赛时忘删调试信息，导致爆 $0$。

### 题目大意

有一个初始排列 $S$，和一个最终排列 $T$，其长度均为 $N$。现在有 $M$ 个操作数对 $(A_{i}, B_{i})$，表示在第 $i$ 个时间节点，排列中 $A_{i}$ 和 $B_{i}$ 相邻，将其交换。

请你构造出一个合法 $S$，使得最终排列 $T$ 的字典序最小。如果无解输出 No。

### 解决方案

我们正序去观察 $M$ 个数对，发现初始排列中 $(A_1, B_1)$ 是必定相邻的，由此，我们就想到 $(A_N, B_N)$ 在最终排列中也是相邻的。由此我们得出猜测，这道题目很可能是倒序去推理，并且最终得出的性质和若干约束数对有关。

继续观察，我们发现我们要使更前面的操作在最终排列中合法，我们只需要将其后面的操作全部进行之后，得出的排列中两个数字相邻即可。例如样例一中：

```

1 2 3 4 5

4 2 3 1 5 (1, 4)

4 2 5 1 3 (1, 4) (3, 5)

3 2 5 1 4 (1, 4) (3, 5) (1, 5)

3 2 4 1 5 (1, 4) (3, 5) (1, 5)

3 2 4 1 5 (1, 4) (3, 5) (1, 5) (2, 4)
```
现在局面又陷入僵局，我们并不知道得到这些信息过后怎么构造最终的答案排列。因为是二元组，首先想到建图看看性质。

然后得到这些二元组构成的图竟然是一条链。继续思考，如果默认单个节点也是链的话，发现答案排列就是由这些不连通的链拼接构成的。并且环和树是不容许出现的，即无解。

即最后我们将度数为 $0$ 或 $1$ 的节点从小到大排序，依次取出，如果链的另一头已经用过，则跳过，否则顺序遍历这条链并加入答案当中。

如果答案序列大小小于 $N$，则出现了环。

如果出现了度数大于 $2$ 的节点，则出现了树。

时间复杂度 $O(n)$。

### 代码实现


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define ll long long

using namespace std;

const int N = 5e5 + 10;

int a[N], b[N], d[N], n, m, vis[N], p[N]; vector<int> G[N], h; 

set<pair<int, int>> S;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);  cout.tie(0);
	cin >> n >> m;
	L(i, 1, n) p[i] = i;
	L(i, 1, m) cin >> a[i] >>b[i];
	R(i, m, 1) {
		int x = a[i], y = b[i];
		if(S.count(make_pair(p[x], p[y])) || S.count(make_pair(p[y], p[x]))) {
			swap(p[x], p[y]);
			continue;
		}
		G[p[x]].push_back(p[y]);
		G[p[y]].push_back(p[x]);
		d[p[x]]++; d[p[y]]++;
		S.insert(make_pair(p[x], p[y])); 
		swap(p[x], p[y]);
	}
	vector<int> ans;
	L(i, 1, n) if(d[i] < 2) h.push_back(i);
	L(i, 1, n) if(d[i] > 2) return cout << "No", 0;
	for(auto x : h) {
		if(vis[x]) continue;
		int u = x; vis[u] = 1;
		while(1) {
			ans.push_back(u);
			bool f = 1;
			for(auto v : G[u])
			  if(!vis[v]) {
			  	f = 0;
			  	vis[v] = 1;
			  	u = v;
			  	break;
			  }
			if(f) break;
		}
	}
	if(ans.size() < n) return cout << "No\n", 0;
	cout << "Yes\n";
	for(int i = 0; i < n - 1; i++)
	  cout << ans[i] << '\n';
	cout << ans[n-1];
	return 0; 
}



```

---

## 作者：BlachSnake (赞：1)

并非图论建模。

实为暴力模拟。

对于 $v \in [1,n]$ 新建一个仅包含 $v$ 的双向链表。

定义双向链表的「表头」为其中连接**至少**一个空节点的节点。

对于一对 $a_i,b_i$ 交换时：

- 若 $a_i,b_i$ 在同一个链表 $T$ 内：
  * 若 $a_i,b_i$ 在 $T$ 中不相邻 ：输出`No`，结束程序。
  * 若 $a_i,b_i$ 相邻：交换 $a_i,b_i$。
- 若 $a_i,b_i$ 不在同一链表内：考虑合并 $a_i,b_i$ 所在链表。
  * 若 $a_i$ **或** $b_i$ 不为其所在链表「表头」：输出`No`，结束程序。
  * 若 $a_i,b_i$ **均**为其所在链表「表头」：连接 $a_i,b_i$，**然后交换** $a_i,b_i$。

如未结束程序，输出`Yes`并输出方案。

如何判断 $a_i,b_i$ 是否相邻？直接在链表上查找即可。

如何判断 $a_i,b_i$ 是否在同一链表上？使用并查集维护。

有关代码中`exchange`操作的形象化理解可见下图。

![图炸了qwq](https://cdn.luogu.com.cn/upload/image_hosting/k019yozq.png)

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 500120;

int c[N][2];
bool v[N];
//#define empty(a) (c[a][0] == 0 && c[a][1] == 0)
#define spare(a) (c[a][0] == 0 || c[a][1] == 0) // 判断 a 是否为「表头」，是为true
#define full(a) (c[a][0] != 0 && c[a][1] != 0) // 判断 a 是否为「表头」，否为true
#define found(a, b) (c[a][0] == b || c[a][1] == b) // 判断 a 是否与 b 相邻
#define check(a, b) (c[a][1] == b) // 求 b 在 a 的哪一个指针上 
#define canfill(a) check(a, 0) // 求 a 连接空节点的指针 
// *** 并非指针（bushi 
inline void exchange(int a, int b) // 链表交换操作 
{
	int w1 = check(a, b), w2 = check(b, a), x;
	if (c[a][!w1] != 0)
	{
		x = c[a][!w1];
		c[x][check(x, a)] = b;
	}
	if (c[b][!w2] != 0)
	{
		x = c[b][!w2];
		c[x][check(x, b)] = a;
	}
	c[b][w2] = c[a][!w1];
	c[a][w1] = c[b][!w2];
	c[b][!w2] = a;
	c[a][!w1] = b;

}
void Dfs(int x, int z) // 遍历链表 
{
	cout << x << '\n';
	v[x] = true;
	for (int i = 0; i < 2; ++i)
		if (c[x][i] != 0 && c[x][i] != z)
			Dfs(c[x][i], x);
}
// *** 上面的 if 本可以写成 (!v[c[x][i]])，但先前作者写出了环 XD 
// *** 所以用了这个判断以迅速判断是否出现环（及其他的奇形怪状 

int f[N], sz[N];
inline void Init(int n) // 并查集初始化 
{
	iota(f + 1, f + n + 1, 1);
	fill(sz + 1, sz + n + 1, 1);
}
int Find(int x) // 路径压缩 
{
	return x == f[x] ? x : (f[x] = Find(f[x]));
}
inline bool Merge(int x, int y) // （启发式）合并 
{
	x = Find(x), y = Find(y);
	if (x == y)
		return false; // 已在同一链表上 
	if (sz[x] < sz[y])
		swap(x, y);
	f[y] = x;
	sz[x] += sz[y];
	return true; // 可以合并 
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	Init(n);
	for (int i = 1; i <= m; ++i)
	{
		int a, b;
		cin >> a >> b;
		if (!Merge(a, b)) // 如果 a_i, b_i 在同一链表上 
		{
			if (!found(a, b)) // 如果 a_i, b_i 不相邻 
			{
				cout << "No\n";
				return 0;
			}
			else // 如果 a_i, b_i 相邻 
			{
				exchange(a, b);
			}
		}
		else // 如果 a_i, b_i 不在同一链表上 
		{
			if (full(a) || full(b)) // 如果 a_i 或 b_i 不是「表头」 
			{
				cout << "No";
				return 0;
			}
			else // 如果 a_i, b_i 均为「表头」 
			{
				int w1 = canfill(a), w2 = canfill(b);
				c[a][w1] = b;
				c[b][w2] = a;
				exchange(a, b);
			}
		}
	}
	// 输出方案 
	cout << "Yes\n";
	for (int i = 1; i <= n; ++i)
		if (spare(i) && !v[i]) // 找尽可能小的「表头」 遍历
			Dfs(i, 0);
	return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

有点难度的图论建模。

注意到只有相邻的两个人才能交换位置，所以**此题唯一的限制就是交换的两个人位置需要相邻**。

考虑如何刻画这个限制，因为我们是**要求最终的序列**，同时交换操作又是**可逆的**，所以我们可以**倒序操作**。具体地，当我们从后往前遍历到某个交换操作的时候，说明这两个人当前所在的**位置是相邻**的。因此我们只需要找到该操作后面的操作中，这两个位置**分别被换成了什么人**，这两个人在最后的序列上就是相邻的。

维护分别被换成了什么人，直接记录一个映射，交换的时候把映射交换即可。

求出相邻限制后，显然就是可以图论建模的了：**把相邻限制看做无向边**，则**每个连通块都必须是一条链**，否则一定无解。同时注意重边是合法的。在最小化字典序的时候以链两端的最小编号为关键字排序即可。

实现上，可以使用并查集求连通块，并维护每个连通块的点数、去除重边后的边数、每个点的度数就可以快速判断是否是一条链了。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
using pi=pair<int,int>;
const int N=500005;
const int inf=0x3f3f3f3f;
int n,m,s[N],a[N],b[N],f[N],sz[N],ds[N],szd[N],idx=0,id[N],ltk[N];
vector<int>g[N];
map<pi,bool>vis;
void init()
{
	for(int i=1;i<=n;i++)
	{
		f[i]=i;
		sz[i]=0;
		szd[i]=1;
	}
}
int findf(int x)
{
	if(f[x]!=x)f[x]=findf(f[x]);
	return f[x];
}
void combine(int x,int y)
{
	int fx=findf(x),fy=findf(y);
	if(fx!=fy)
	{
		f[fx]=fy;
		sz[fy]+=sz[fx];
		szd[fy]+=szd[fx];
	}
}
bitset<N>viss;
void solve(int s)
{
	int p=s;
	while(1)
	{
		cout<<p<<'\n';
		viss[p]=1;
		int orip=p;
		for(auto v:g[p])
		{
			if(viss[v]==0)
			{
				p=v;
				break;
			}
		}
		if(orip==p)break;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	init();
	for(int i=1;i<=m;i++)
	{
		cin>>a[i]>>b[i];
	}
	for(int i=1;i<=n;i++)
	{
		s[i]=i;
	}
	for(int i=m;i>=1;i--)
	{
		int u=s[a[i]],v=s[b[i]];
		if(u==v)
		{
			cout<<"No";
			return 0;
		}
		if(vis[{min(u,v),max(u,v)}]==0)
		{
			vis[{min(u,v),max(u,v)}]=1;
			combine(u,v);
			sz[findf(u)]++;
			ds[u]++;ds[v]++;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		swap(s[a[i]],s[b[i]]);
	}
	for(int i=1;i<=n;i++)
	{
		if(ds[i]>=3)
		{
			cout<<"No";
			return 0;
		}
		if(szd[findf(i)]!=sz[findf(i)]+1)
		{
			cout<<"No";
			return 0;			
		}
		if(findf(i)==i)
		{
			id[i]=++idx;
		}
	}
	for(int i=1;i<=idx;i++)
	{
		ltk[i]=inf;
	}
	for(int i=1;i<=n;i++)
	{
		if(ds[i]<=1)
		{
			ltk[id[findf(i)]]=min(ltk[id[findf(i)]],i);
		}
	}	
	sort(ltk+1,ltk+idx+1);
	cout<<"Yes\n";
	for(int i=1;i<=idx;i++)
	{
		solve(ltk[i]);
	}
	return 0;
}
```

---

## 作者：114514lhc (赞：1)

没参加比赛，现在切一下。  
挺简单的，就是维护 $i$ 左右两边的数（无序），然后听他的，让我交换谁就交换谁（修改 $i$ 两侧的数）。  
定义 $a$，$b$ 数组为 $i$ 两侧的数（不分左右）
初始为 $0$。   
据题意，每次读入两个数 $x$，$y$。   
- 若 $x$，$y$ 之前无交集，则令 $a_x$ 或 $b_x$ 为 $0$ 的一个等于 $y$，令 $a_y$ 或 $b_y$ 为 $0$ 的一个等于 $x$。若找不到为 $0$ 的，输出 No。
- 若有交集，则无需进行上一步。
- 然后交换 $x$，$y$（语言过于抽象）：  
  举个例子：   
  要将 $u$，$x$，$y$，$v$ 改为 $u$，$y$，$x$，$v$，   
  则将   
   $a_u=0$，$b_u=x$    
   $a_x=0$，$b_x=y$   
   $a_y=x$，$b_y=v$   
   $a_v=y$，$b_v=0$   
  改为   
   $a_u=0$，$b_u=y$    
   $a_y=u$，$b_y=x$   
   $a_x=y$，$b_x=v$   
   $a_v=x$，$b_v=0$
   
那么现在已经理清每个点之间的关系，输出即可枚举每一个点，若其一边为 $0$，则作为起点输出一条链（可能有多个起点），如果出现环，输出 No。  
代码如下：  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[514514],b[514514],hmx[514514];
queue<int>p;
void swp(int x,int y)
{
    if(b[x]==y)swap(b[x],a[x]);
    if(b[y]==x)swap(b[y],a[y]);
    if(b[b[x]]==x)swap(b[b[x]],a[b[x]]);
    if(b[b[y]]==y)swap(b[b[y]],a[b[y]]);
    //交换后好处理
    a[b[x]]=y;a[b[y]]=x;
    swap(b[x],b[y]);
}
void cot(int u)
{
    int v=0;
    for(int i=1;i<=n;i++)
    {
        p.push(u);hmx[u]=1;
        if(a[u]!=0&&a[u]!=v)v=u,u=a[u];
        else v=u,u=b[u];
        if(u==0)break;
    }
}
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    int fl=0;//Yes or No
    for(int i=1;i<=m;i++)
    {
        int x,y;cin>>x>>y;
        if(a[x]!=y&&b[x]!=y)
        {
            if(a[x]==0)
            {
                a[x]=y;
                if(a[y]==0)a[y]=x;
                else if(b[y]==0)b[y]=x;
                else fl=1;//找不到0
            }
            else if(b[x]==0)
            {
                b[x]=y;
                if(a[y]==0)a[y]=x;
                else if(b[y]==0)b[y]=x;
                else fl=1;//找不到0
            }
            else fl=1;//找不到0
        }
        swp(x,y);
    }
    if(fl){cout<<"No";return 0;}
    int u=0,v=0;
    for(int i=1;i<=n;i++)
        if((a[i]==0||b[i]==0)&&!hmx[i])
            cot(i);//枚举起点
    if(p.size()!=n){cout<<"No"<<endl;return 0;}
    //有环会找不到起点，所以点选数不全
    cout<<"Yes"<<endl;
    while(p.size())
    {
        int u=p.front();p.pop();
        cout<<u<<endl;
    }
    return 0;
}

```
审核大大求过呀！

---

## 作者：grard4 (赞：1)

毒瘤 D 题。。。一言难尽。

本题解做法来自大神 [$\text{MicroSun}$](https://www.luogu.com.cn/user/514700)（此人考场上仅需28分钟就直接切了）

题目要求我们找出一个 $1$ ~ $n$ 的排列，满足能够依次执行 $m$ 次交换操作（其中第 $i$ 个操作必须保证当前状态下 $A_i$ 和 $B_i$ 相邻），并要求答案的字典序最小。

由于每步操作都确保了在当前状态下被交换的两个数必定相邻的关系。所以对于答案中的每个 $P_i$，考虑其相邻一边或两边的数都一定是些什么，尝试将最后必定相邻的两个数进行连边。

记 $f_i$ 为当前状态下值为 $i$ 的元素所处的位置出现在最终状态下值为 $f_i$ 的元素所处的位置，初始化为 $f_i=i$。

考虑从答案入手，**倒序**处理每个操作，对于操作 $(A_i,B_i)$，将 $f_{A_i}$ 和 $f_{B_i}$ 连上一条边，并将 $f_{A_i}$ 和 $f_{B_i}$ 进行交换，这样 $A_i$ 下一步会出现在最终状态下值为 $f_{B_i}$ 的元素所处的位置，$B_i$ 下一步会出现在最终状态下值为 $f_{A_i}$ 的元素所处的位置。不影响最终状态下每个元素的相邻性，可以手动尝试着模拟下。

此时如果有解，**当且仅当**这个图只包含一些孤点和若干条链，否则将无法构成排列。

对每条链取较小的那个链头，输出的时候只需根据链头从小到大输出每条链就可以保证答案的字典序最小了。记得要防止重边。

$\text{code：}$

```cpp
#include<bits/stdc++.h>
#define MAXN 500005
#define pb push_back
using namespace std;
int n,m,tot,a[MAXN],b[MAXN],p[MAXN];
bool pr[MAXN],vis[MAXN];
// 用 map 记录下连接过的边
map<pair<int,int>,bool >mp;
vector<int> G[MAXN];
// dfs 判断是否为链并记录这条链共有多少个节点
void dfs(int u,int fa){
    vis[u]=true,tot++;
    for (auto v:G[u]){
        if (v==fa) continue;
        // 如果遇到了环,那么一定无法构成链,此时直接输出无解即可
        if (vis[v]) {puts("No");exit(0);}
        dfs(v,u);
    }
}
void print(int u,int fa){
    cout<<u<<endl;
    for (auto v:G[u]){
        if (v==fa) continue;
        print(v,u);
    }
}
int main(){
    cin>>n>>m;;
    for (int i=1;i<=n;i++) p[i]=i;
    for (int i=1;i<=m;i++) cin>>a[i]>>b[i];
    for (int i=m;i;i--)
    {
        swap(p[a[i]],p[b[i]]);
        if (mp.count({p[a[i]],p[b[i]]})) continue;   //建边时要避免重边
        G[p[a[i]]].pb(p[b[i]]),G[p[b[i]]].pb(p[a[i]]);
        mp[{p[a[i]],p[b[i]]}]=mp[{p[b[i]],p[a[i]]}]=true;
    }
    for (int i=1;i<=n;i++)
    {
        // 如果一个点的度数超过了2,那么一定无法构成链,此时直接输出无解即可 
        if (G[i].size()>2) {puts("No");return 0;}
        if (G[i].empty()) tot++,pr[i]=true;
        else if (!vis[i]&&G[i].size()==1) dfs(i,0),pr[i]=true;  // 度数为 1 的点一定就是一条链的链头
    }
    if (tot<n) {puts("No");return 0;} //统计的点数小于n就直接输出无解
    else {puts("Yes");for (int i=1;i<=n;i++) if (pr[i]) print(i,0);}
    return 0;
}
```

---

## 作者：chengzicong (赞：1)

整体思路还是比较清晰，顺着建图即可，每个人视作一个点。是每次加入边的时候交换两点连接的边，每次 check 一下顶点的度，如果大于 2 直接退出输出 No，完成建图后进行 dfs (选取度数小于等于一的节点)遍历并且保存路径为向量，检查头尾如果头大就颠倒路径。最后依照所有路径头部的大小排列拼接。最后如果有的点没有被访问过那么也输出 "No" ,否则输出 "Yes" 并输出拼接好的路径。


    #include <bits/stdc++.h>

    using namespace std;
  
    vector<vector<int>>Map;
    vector<vector<int>>Res;
    vector<bool>Visit;
    int N,M;
    int a,b;
    
    void change(){
        vector<int>tmp1,tmp2;
        for(auto i:Map[a]){
            if(i!=b)tmp1.push_back(i);
            for(int j=0;j<Map[i].size();j++){
                if(Map[i][j]==a&&i!=b)Map[i][j]=b;
            }
        }
        for(auto i:Map[b]){
            if(i!=a)tmp2.push_back(i);
            for(int j=0;j<Map[i].size();j++){
                if(Map[i][j]==b&&i!=a)Map[i][j]=a;
            }
        }
    
        tmp1.push_back(a);
        tmp2.push_back(b);
        Map[a]=tmp2;
        Map[b]=tmp1;
        if(Map[a].size()>2||Map[b].size()>2){
            printf("No\n");
            exit(0);
        }
    }
    void dfs(vector<int>&V,int now,int parent){
        Visit[now]=true;
        V.push_back(now);
        for(auto i:Map[now]){
            if(!Visit[i]){
                dfs(V,i,now);
            }
            else if(i!=parent){
                printf("No\n");
                exit(0);
            }
        }
    }
    
    bool cmp(vector<int>&A,vector<int>&B){
        return A[0]<B[0];
    }
    
    int main()
    {
        scanf("%d%d",&N,&M);
        Map.resize(N+1);
        Visit.resize(N+1);
        for(int i=0;i<M;i++){
            scanf("%d%d",&a,&b);
            change();
        }
    
        for(int i=1;i<=N;i++){
            if(Map[i].size()<=1&&!Visit[i]){
                vector<int>T;
                dfs(T,i,0);
                if(!T.empty()){
                    if(T[0]>T.back()){
                        for(int j=0;j<T.size()/2;j++){
                            swap(T[j],T[T.size()-1-j]);
                        }
                    }
                    Res.push_back(T);
                }
            }
        }
        for(int i=1;i<=N;i++){
            if(!Visit[i]){
                printf("No\n");
                exit(0);
            }
        }
        sort(Res.begin(),Res.end());
        printf("Yes\n");
        for(auto i:Res){
            for(auto j:i){
                printf("%d\n",j);
            }
        }
        return 0;
    }

---

## 作者：poembelief (赞：0)

# 题意
[题目传送门](https://www.luogu.com.cn/problem/P11726)
# 分析
题目中要求交换位置的两名运动员之间没有其他运动员，由此可以联想到维护需要交换的运动员之间的关系。

手玩一下可以发现，交换操作会限制一些运动员的先后顺序，这很像链，因此考虑用链来维护，每个交换操作就是对于链的合并和检查，按顺序模拟操作之后会得到若干条链，接下来只需要贪心地把链连起来就行了。

两点在同一链上就检查是否合法，否则检查是否合法后进行合并。操作完成后再进行交换操作。

关于合并和检查链的方法可看下方代码。

**我太菜了，维护链的交换操作太难写了！！！**

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
/*
*/
const int N=5e5+5;
int n,m,a[N],b[N],x,y,to[N],fa[N],f[N];
bool ins[N];
int get(int x){
	return x==f[x]?x:f[x]=get(f[x]);
}
void print(int x,int f){
	if(ins[x]) return;
	printf("%d\n",x);
	ins[x]=1;
	if(to[x]!=f) print(to[x],x);
	else print(fa[x],x);
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen("tx.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=m;i++){
		x=a[i],y=b[i];
		if(x>y) swap(x,y);
		if(get(x)==get(y)){
			if(to[x]!=y&&fa[x]!=y){
				printf("No\n");
				return 0;
			}
		}
		else{
			if((to[x]&&fa[x])||(to[y]&&fa[y])){
				printf("No\n");
				return 0;
			}
			else{
				if(!to[x]) to[x]=y;
				else fa[x]=y;
				if(!to[y]) to[y]=x;
				else fa[y]=x;
				f[get(x)]=get(y);
			}
		}
		if(fa[x]!=y){
			if(to[fa[x]]==x) to[fa[x]]=y;
			if(fa[fa[x]]==x) fa[fa[x]]=y;
		}
		if(to[x]!=y){
			if(fa[to[x]]==x) fa[to[x]]=y;
			if(to[to[x]]==x) to[to[x]]=y;
		}
		if(to[y]!=x){
			if(fa[to[y]]==y) fa[to[y]]=x;
			if(to[to[y]]==y) to[to[y]]=x;
		}
		if(fa[y]!=x){
			if(fa[fa[y]]==y) fa[fa[y]]=x;
			if(to[fa[y]]==y) to[fa[y]]=x;
		}
		if(fa[y]!=x){
			if(to[x]!=y) swap(fa[y],to[x]);
			else swap(fa[y],fa[x]);
		}
		else{
			if(to[x]!=y) swap(to[y],to[x]);
			else swap(to[y],fa[x]);
		}
	}
	printf("Yes\n");
	ins[0]=1;
	for(int i=1;i<=n;i++){
		if(ins[i]) continue;
		if(!fa[i]||!to[i]){
			print(i,0);
		}
	}
	return 0;
}

```

---

