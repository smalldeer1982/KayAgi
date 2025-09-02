# [ABC291F] Teleporter and Closed off

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc291/tasks/abc291_f

$ N $ 個の都市があり、都市 $ 1 $, 都市 $ 2 $, $ \ldots $, 都市 $ N $ と番号づけられています。  
いくつかの異なる都市の間は一方通行のテレポーターによって移動できます。 都市 $ i $ $ (1\leq\ i\leq\ N) $ からテレポーターによって直接移動できる都市は `0` と `1` からなる長さ $ M $ の文字列 $ S_i $ によって表されます。具体的には、$ 1\leq\ j\leq\ N $ に対して、

- $ 1\leq\ j-i\leq\ M $ かつ $ S_i $ の $ (j-i) $ 文字目が `1` ならば、都市 $ i $ から都市 $ j $ に直接移動できる。
- そうでない時、都市 $ i $ から都市 $ j $ へは直接移動できない。

$ k=2,3,\ldots,\ N-1 $ に対して次の問題を解いてください。

> テレポータを繰り返し使用することによって、**都市 $ k $ を通らずに**都市 $ 1 $ から 都市 $ N $ へ移動できるか判定し、 できるならばそのために必要なテレポーターの使用回数の最小値を、 できないならば $ -1 $ を出力せよ。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 10^5 $
- $ 1\leq\ M\leq\ 10 $
- $ M\ <\ N $
- $ S_i $ は `0` と `1` のみからなる長さ $ M $ の文字列
- $ i+j\ >\ N $ ならば $ S_i $ の $ j $ 文字目は `0`
- $ N,M $ は整数

### Sample Explanation 1

テレポータによって各都市からはそれぞれ以下の都市へ直接移動する事ができます。 - 都市 $ 1 $ からは都市 $ 2,3 $ へ移動できる。 - 都市 $ 2 $ からは都市 $ 4 $ へ移動できる。 - 都市 $ 3 $ からは都市 $ 4,5 $ へ移動できる。 - 都市 $ 4 $ からは都市 $ 5 $ へ移動できる。 - 都市 $ 5 $ から移動できる都市は存在しない。 よって、都市 $ 1 $ から都市 $ 5 $ へ移動する方法は、 - 経路 $ 1 $ : 都市 $ 1 $ $ \to $ 都市 $ 2 $ $ \to $ 都市 $ 4 $ $ \to $ 都市 $ 5 $ - 経路 $ 2 $ : 都市 $ 1 $ $ \to $ 都市 $ 3 $ $ \to $ 都市 $ 4 $ $ \to $ 都市 $ 5 $ - 経路 $ 3 $ : 都市 $ 1 $ $ \to $ 都市 $ 3 $ $ \to $ 都市 $ 5 $ の $ 3 $ つがあり、 - 都市 $ 2 $ を通らない経路は経路 $ 2 $, 経路 $ 3 $ の $ 2 $つであり、そのうちテレポーターの使用回数が最小となるのは経路 $ 3 $ で、この時 $ 2 $ 回使用する。 - 都市 $ 3 $ を通らない経路は経路 $ 1 $ のみであり、この時テレポーターは $ 3 $ 回使用する。 - 都市 $ 4 $ を通らない経路は経路 $ 3 $ のみであり、この時テレポーターは $ 2 $ 回使用する。 となります。よって、$ 2,3,2 $ をこの順に空白区切りで出力します。

### Sample Explanation 2

都市 $ 1 $ から都市 $ 6 $ へ移動する方法は、都市 $ 1 $ $ \to $ 都市 $ 2 $ $ \to $ 都市 $ 5 $ $ \to $ 都市 $ 6 $ のみであるため、 $ k=2,5 $ の場合には都市 $ k $ を通らずに都市 $ 1 $ から都市 $ 6 $ へ移動する方法は存在せず、 $ k=3,4 $ の場合には上の方法が条件をみたし、テレポーターを $ 3 $ 回使用します。 よって、$ -1,3,3,-1 $ をこの順に空白区切りで出力します。 テレポーターは一方通行であるため、 都市 $ 3 $ から都市 $ 4 $ へはテレポーターによって移動できますが、 都市 $ 4 $ から都市 $ 3 $ へは移動できず、 都市 $ 1 $ $ \to $ 都市 $ 4 $ $ \to $ 都市 $ 3 $ $ \to $ 都市 $ 6 $ のような移動はできない事に注意してください。

## 样例 #1

### 输入

```
5 2
11
01
11
10
00```

### 输出

```
2 3 2```

## 样例 #2

### 输入

```
6 3
101
001
101
000
100
000```

### 输出

```
-1 3 3 -1```

# 题解

## 作者：iiiiiyang (赞：5)

[逆天的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17158710.html)

[题目链接](https://www.luogu.com.cn/problem/AT_abc291_f)

给定一个 $n$ 个点的图，每个点只向编号最多大于它 $m$ 的点连单向边，求不经过 $2 \sim n$ 中的一个点，$1 \to n$ 的最短路。注意到 $m$ 很小，这里给出两种做法，都是基于 $m$ 的特性来做的。

第一种是直接搜索。首先我们求出 $1$ 到每个点的最短路和 $n$ 到每个点的最短路。如果说不经过点 $i$，对于点 $j$ 有 $j+k>i (1 \le k \le m,j+k \le n)$ 且有边 $j \to j+k$ 那就说明存在这条合法路径，直接枚举 $j$ 和 $k$ 即可，统计的答案即为 $dis_{1 \to j} + dis_{j+k \to n} +1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

namespace LgxTpre
{
	static const int MAX=100010;
	static const int INF=4557430888798830399;
	static const int mod=998244353;
	
	int n,m,ans;
	string s[MAX];
	
	struct edge
	{
		int nex,to;
	}e[MAX<<5];
	int head[MAX],cnt;
	inline void add(int x,int y)
	{
		e[++cnt].nex=head[x],head[x]=cnt,e[cnt].to=y;
		return;
	}
	
	queue<int> q;
	int dis[MAX][2];
	inline void bfs(int dir)
	{
		if(!dir) q.push(1),dis[1][0]=0;
		else q.push(n),dis[n][1]=0;
		while(!q.empty())
		{
			int now=q.front(); q.pop();
			for(int i=head[now];i;i=e[i].nex)
			{
				int to=e[i].to;
				if(dis[to][dir]>dis[now][dir]+1)
					dis[to][dir]=dis[now][dir]+1,q.push(to);
			}
		}
		return;
	}
	inline void init()
	{
		memset(head,0,sizeof head);
		cnt=0;
	}
	
	inline void lmy_forever()
	{
		cin>>n>>m;
		memset(dis,0x3f,sizeof dis);
		for(int i=1;i<=n;++i) cin>>s[i];
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(s[i][j-1]=='1') 
					add(i,i+j);
		bfs(0);
		init();
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(s[i][j-1]=='1') 
					add(i+j,i);
		bfs(1);
		for(int i=2;i<n;++i)
		{
			ans=INF;
			for(int j=max(1ll,i-m+1);j<i;++j)
				for(int k=1;k<=m;++k)
					if(j+k>i&&s[j][k-1]=='1')
						ans=min(ans,dis[j][0]+dis[j+k][1]+1);
			if(ans==INF) cout<<-1<<" ";
			else cout<<ans<<" ";
		}
		return;
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	LgxTpre::lmy_forever();
	return (0-0);
}
```

第二种是矩阵。记 $d_i$ 为 $1 \to i$ 的最小花费，设计状态矩阵：
$$
\begin{bmatrix}
d_i \; d_{i-1} \; d_{i-2} \cdots d_{i-m}
\end{bmatrix}
$$

将原先的矩阵乘法（乘和加）重新定义为加和取 $\min$，显然是满足结合律的，即：
$$
a_{i,j} = \min_{1 \le k \le m} b_{i,k} + c_{k,j}
$$

我们记 $k$ 为第几个转移矩阵，首先初始化：
$$
Base_{k,i,j} = 
\begin{cases}
0 \; (j=i+1) \\
\infty \; \text{otherwise}
\end{cases}
$$

如果存在 $x \to x+i$ 的边，我们令 $Base_{x+i,i,1}=1$，即为可以以 $1$ 花费从 $i$ 直接到 $i+x$。

考虑矩阵的意义，因为是取 $\min$ 运算，所以极大值必定取不到，含义就是不存在这种边；$0$ 即为 $d_{i-1} \sim d_{i-m}$ 的状态的继承。然后我们发现不经过第几个点实际上就是不进行第几个转移矩阵的操作，所以我们对转移矩阵求前缀积和后缀积，就可以线性得到答案了。

由于我的矩阵自带大常数的问题，相比于搜索处于极大的劣势。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

namespace LgxTpre
{
	static const int MAX=100010;
	static const int INF=4557430888798830399;
	static const int mod=998244353;
	
	int n,m,ans;
	string s[MAX];
	
	struct Matrix
	{
		static const int qck=15;
		int a[qck][qck];
		Matrix operator * (const Matrix& T) const 
		{
			Matrix res; memset(res.a,0x3f,sizeof res.a);
			for(int i=1;i<=m;++i)
				for(int j=1;j<=m;++j)
					for(int k=1;k<=m;++k)
						res.a[i][j]=min(res.a[i][j],a[i][k]+T.a[k][j]);
			return res;
		}
	}pre[MAX],suf[MAX],bas[MAX];
	
	inline void lmy_forever()
	{
		cin>>n>>m;
		for(int i=1;i<=n;++i)
			cin>>s[i];
		for(int i=0;i<=n;++i)
			for(int j=1;j<=m;++j)
				for(int k=1;k<=m;++k)
					bas[i].a[j][k]=(k==j+1)?0:INF;	
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(s[i][j-1]=='1')
					bas[i+j].a[j][1]=1;
		pre[2]=bas[2];
		for(int i=3;i<=n;++i) pre[i]=pre[i-1]*bas[i];
		suf[n]=bas[n];
		for(int i=n-1;i>=1;--i) suf[i]=bas[i]*suf[i+1];
		for(int i=2;i<n;++i)
		{
			if(i==2) ans=(bas[0]*suf[i+1]).a[1][1];
			else ans=(pre[i-1]*bas[0]*suf[i+1]).a[1][1];
			if(ans==INF) cout<<-1<<" ";
			else cout<<ans<<" ";
		}
		return;
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	LgxTpre::lmy_forever();
	return (0-0);
}
```

---

## 作者：lfxxx (赞：2)

考虑一个问题，每个点只会向编号大于它的点连边。

那么也就是说，从 $i$ 到 $j$ 的路径上**只会**经过编号大于等于 $i$ 且小于等于 $j$ 的点。

那么这个时候处理不经过 $i$ 的最短路就很好说了。

所以说可以找一个点 $k$ 它连着 $w$ 使得 $k < i$  且 $w > i$，答案就是 $dis_{1,k} + dis_{w,n} + 1$。

因为边上点编号差最多为 $m$ 所以可以从 $i-m$ 开始枚举。

最短路就用 BFS 解决就可以了（因为每条边边权都是 $1$）。

最后复杂度是 $O(n \times m)$ 的，代码实现很简单，就不放了。

---

## 作者：CrTsIr400 (赞：1)

题意：$N$ 个点，每个点出至多 $M$ 条边（连向后面），求对于删去每个 $i$ 点，从 $1$ 出发到 $N$ 最少走的边数。$N\le 10^5,M\le 10$。

题解：先考虑 DP，设 $f[i]$ 为 $1$ 到 $i$ 最少走的边数，$g[i]$ 为 $i$ 到 $N$ 最少走的边数。

枚举删掉的 $i$ 点，这个时候考虑采用“不删除”思想。即枚举没有 $i$ 的贡献。

从右到左枚举在 $i$ 左边的左端点，进而枚举出 $i$ 右边的右端点，时间复杂度 $O(nm^2)$ 可以通过。

算法思维：DP+看数据范围暴力+不删除思想。

```cpp
const I N=1e5+10;
I n,m;vector<I>v[N],e[N];
I fs[N],ls[N];
I main(){
	scanf("%d%d",&n,&m);
	for(I i=1;i<=n;++i)
		for(I j=1,x;j<=m;++j){
			scanf("%1d",&x);
			if(x&&i+j<=n)v[i].push_back(i+j),e[i+j].push_back(i);
		}
	memset(fs,0x3f,N<<2);
	memset(ls,0x3f,N<<2);
	fs[1]=ls[n]=0;
	for(I i=1;i<=n;++i)
		for(auto j:v[i])
			fs[j]=min(fs[j],fs[i]+1);
	for(I i=n;i;--i)
		for(auto j:e[i])
			ls[j]=min(ls[j],ls[i]+1);
	for(I i=2;i<n;++i){
		I ans=0x3f3f3f3f;
		for(I lp=i-1;lp&&lp>i-m;--lp)
			for(auto rp:v[lp])
				if(rp>i)
				ans=min(ans,fs[lp]+ls[rp]+1);
		printf("%d ",ans==0x3f3f3f3f?-1:ans);}
	return 0;
}
```

## 

---

## 作者：ダ月 (赞：0)

### 题意概要：

给定 $n$ 个点，每个点对应一个长度为 $m$ 的字符串，其中第 $i$ 为如果是 $1$ 的话，若当前点为 $x$，说明能走到 $x+i$ 的位置；如果是 $0$，则走不到。现在有些城市被禁止途径，求从 $1$ 走到 $n$ 的位置最少需要途径几个城市。其中 $1$ 点不算。输出 $2,3,\dots,n-1$ 点不能通过的最少途径数。

### 题目分析：

如果考虑暴力最短路径，因为带修改有 $n$ 个点，复杂度较大，无法通过。考虑 dp，设 $f_i$ 表示如果任何城市没有禁止的话，从 $1$ 走到 $i$ 最小途经数。设 $g_i$ 表示如果任何城市没有禁止的话，从 $i$ 走到 $n$ 的最少途径数。

显然，可以得到状态转移方程：

$f_i=\min\{f_j+1\},c_{i,i-j}=1,\max\{1,i-m\}\le j<i$。

$g_i$ 同理。

考虑修改，对于每个点 $i$，若 $i$ 禁止通过，那么答案就是：

$\min\{f_j+g_k+1\},\max\{1,i-m\}\le j<i<k\le\min\{i+m,n\}$。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m;
char c[N][15];
int f[2][N];/*f[0]就是题解中的f，f[1]是题解中的g*/
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",c[i]+1);
	memset(f,0x3f,sizeof(f));
	f[0][1]=f[1][n]=0;
	for(int i=1;i<=n;i++)
		for(int j=max(i-m,1);j<i;j++)
			if(c[j][i-j]=='1')
				f[0][i]=min(f[0][j]+1,f[0][i]);
	for(int i=n;i>=1;i--)
		for(int j=min(i+m,n);j>i;j--)
			if(c[i][j-i]=='1')
				f[1][i]=min(f[1][j]+1,f[1][i]);
	for(int i=2;i<n;i++){
		int ans=1e9;
		for(int j=max(i-m,1);j<i;j++)
			for(int k=i+1;k<=min(i+m,n);k++)
				if(k-j<=m&&c[j][k-j]=='1')
					ans=min(f[0][j]+f[1][k]+1,ans);
		printf("%d\n",ans==1e9?-1:ans);
	}return 0;
}
```

时间复杂度：$O(nm^2)$。

---

