# 「SWTR-5」Chain

## 题目描述

给定 $n$ 个点，$m$ 条边的有向无环图。不保证图连通。

$q$ 次询问，每次给出 $k$ 和 $k$ 个互不相同的数 $c_i$，求出如果去掉这 $k$ 个点，整个有向无环图将剩余多少条链。答案对 $10^9+7$ 取模。**每次询问独立。**

- “链”的定义是：我们设一条长度为 $p$ 的链的路径为 $w_0\to w_1\to\cdots\to w_{p-1}\to w_p$，则应满足 $w_0$ 入度为 $0$，$w_p$ 出度为 $0$。你可以将其理解为一条食物链。

- 两条链是“不同的”，当且仅当它们的长度不同，或者经过的点集不同。

- **需要特别注意的是，删去某些点后新产生的链不计入答案。** 例如 $1\to 2\to 3\to 4$ 一图中，有 $1$ 条链 $1\to 2\to 3\to 4$。如果去掉 $2$ 号点，则剩余 $0$ 条链。

## 说明/提示

「样例 $1$ 说明」

DAG 如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2gbdoemh.png)

询问 $1$：如果去掉 $2,4,6$，则剩余 $1$ 条链：$3\to 5$。

询问 $2$：如果去掉 $4,6$，则剩余 $3$ 条链：$3\to 5$，$3\to 2\to 5$，$3\to 7\to 2\to 5$。

询问 $7$：如果去掉 $6$，则剩余 $5$ 条链：$3\to 5$，$3\to 2\to 5$，$3\to 7\to 2\to 5$，$3\to 1\to 4\to 5$，$3\to 7\to 4\to 5$。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 point）：给定的图是一条链。
- Subtask 2（14 points）：$n,q\leq 10$。
- Subtask 3（20 points）：$q\leq 10^3$。
- Subtask 4（17 points）：$k=1$。
- Subtask 5（18 points）：$k=2$。
- Subtask 6（30 points）：无特殊限制。

对于 $100\%$ 的数据：$2\leq n\leq 2\times 10^3$，$1\leq m\leq \min(\frac{n\times(n-1)}{2},2\times 10^4)$，$1\leq q\leq 5\times 10^5$。  
所有询问满足：$1\leq \sum k\leq 2\times 10^6$，$0\leq k\leq \min(n,15)$，$1\leq c_i\leq n$。保证 $c_i$ 互不相同。

**本题轻微卡常，请注意 IO 优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) D。  
idea & solution：[Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
7 14
3 2
4 5
2 5
2 6
3 1
3 5
3 7
3 6
6 4
1 4
6 5
1 6
7 2
7 4
7
3 2 4 6
2 4 6
2 2 5
2 1 4
0
1 4
1 6```

### 输出

```
1
3
0
6
13
7
5```

## 样例 #2

### 输入

```
233 1
1 2
6
0
1 10
2 10 40
1 1
1 2
2 1 2```

### 输出

```
232
231
230
231
231
231```

# 题解

## 作者：yxzy4615 (赞：11)

### 题目描述
给定$n$个点，$m$条边的有向无环图。不保证图联通。
$q$次询问，每次给出$k$和$k$个互不相同的数$c_i$
 ，求出如果去掉这$k$个点，整个有向无环图将剩余多少条链。答案对$10^9+7$取模。每次询问独立。

- “链”的定义是：我们设一条长度为$p$的链的路径为$w_0\to w_1\to\cdots\to w_{p-1}\to w_p$ ，则应满足$w_0$入度为$0$，$w_p$出度为$0$。你可以将其理解为一条食物链。

- 两条链是“不同的”，当且仅当它们的长度不同，或者经过的点集不同。

- 需要特别注意的是，删去某些点后新产生的链不计入答案。 例如$1\to 2\to 3\to 4$一图中，有$1$条链$1\to 2\to 3\to 4$。如果去掉$2$号点，则剩余$0$条链。

### 数据范围

- Subtask 1（1 point）：给定的图是一条链。
- Subtask 2（14 points）：$n,q\leq 10$。
- Subtask 3（20 points）：$q\leq 10^3$。
- Subtask 4（17 points）：$k=1$。
- Subtask 5（18 points）：$k=2$。
- Subtask 6（30 points）：无特殊限制。

对于$100\%$的数据：$2\leq n\leq 2\times 10^3$，$1\leq m\leq \min(\frac{n\times(n-1)}{2},2\times 10^4)$，$1\leq q\leq 5\times 10^5$

所有询问满足：$1\leq \sum k\leq 2\times 10^6$，$0\leq k\leq \min(n,15)$，$1\leq c_i\leq n$。保证 $c_i$互不相同。

### 题目分析
#### $Subtask1$
很明显，如果 $k=0$ 就只有一条链，否则就没有。

#### $Subtask2-3$
标记删掉的点，暴力去跑图。

设$f_i$表示以$i$结尾的链数，转移显然：

 $$∀(u,v),f_v\leftarrow f_u+f_v$$

时间复杂度$O(qm)$。

#### $Subtask4$
$k=1$的情况下，考虑删去的点会对答案产生多少贡献。

拿样例作分析：

![](https://cdn.luogu.com.cn/upload/image_hosting/2gbdoemh.png)


入度为$0$的点是$3$，出度为$0$的点是$5$。手玩找出$f_i$。

$
\begin{matrix}
  i & 1 & 2 & 3 & 4 & 5 & 6 & 7\\
f_i & 1  & 2 & 1  & 6 & 13 & 4 & 1
\end{matrix}
$

再找出每个点到出度为$0$的点的方案数$n\!f_i$。

$
\begin{matrix}
  i   & 1 & 2 & 3  & 4 & 5 & 6 & 7\\
n\!f_i & 3 & 3 & 13 & 1 & 1 & 2 & 4
\end{matrix}
$

手玩答案后汇总得：

$
\begin{matrix}
  i   & 1  & 2 & 3  & 4 & 5  & 6 & 7\\
f_i   & 1  & 2 & 1  & 6 & 13 & 4 & 1\\
n\!f_i & 3  & 3 & 13 & 1 & 1  & 2 & 4\\
ans_i  & 10 & 7 & 0  & 7 & 0  & 5 & 9
\end{matrix}
$

设$s$为出度为$0$的$f_i$的和，发现$ans_i=s-f_i\times n\!f_i$。

$O(m)$预处理，$O(1)$查询，总复杂度$O(q+m)$。

#### $Subtask5$

对于$k=2$，直接用 $ans=s-f_i\times n\!f_i-f_j\times n\!f_j$计算可能会出问题，因为同时经过$i,j$的链会被重复计算，考虑两点容斥。

设$d_{i,j}$表示在原图上$i \to j$的方案数，还是通过样例：

$
\begin{matrix}
  d_{i,j} & 1 & 2 & 3 & 4 & 5  & 6 & 7 & i\\
 1      & 1 & 0 & 0 & 2 & 3  & 1 & 0 & \\
 2      & 0 & 1 & 0 & 1 & 3  & 1 & 0 & \\
 3      & 1 & 2 & 1 & 6 & 13 & 4 & 1 & \\
 4      & 0 & 0 & 0 & 1 & 1  & 0 & 0 & \\
 5      & 0 & 0 & 0 & 0 & 1  & 0 & 0 & \\
 6      & 0 & 0 & 0 & 1 & 2  & 1 & 0 & \\
 7      & 0 & 1 & 0 & 2 & 4  & 1 & 1 & \\
  j     &
\end{matrix}
$

可以发现一个性质:若 $i\ne j$，则 $d_{i,j}\times d_{j,i}=0$。~~显然成立。~~

- 如果 $d_{i,j}=d_{j,i}=0$，代表 $i,j$到出度为$0$的点的路径不相交，直接用 $ans=s-f_i\times n\!f_i-f_j\times n\!f_j$ 计算即可。
- 如果 $d_{i,j}\ne 0$，代表 $i,j$到出度为$0$的点的路径中 $i$包含  $j$，重复路径就是 $f_i\times d_{i,j}\times n\!f_j$，用 $ans=s-f_i\times n\!f_i - (f_j - f_i \times d_{i,j})\times n\!f_j$ 计算即可。
- 如果 $d_{j,i}\ne 0$。用 $ans=s-f_i\times (n\!f_i - f_j \times d_{j,i})- f_j\times n\!f_j$ 计算即可，同上。

所以，总计算式为：
$$ ans=s-(f_i-f_j\times d_{j,i})\times n\!f_i - (f_j - f_i \times d_{i,j})\times n\!f_j$$

$O(nm)$预处理，$O(1)$查询，总复杂度$O(nm+q)$。

#### $Subtask6$
到此，思路已经全部出来了，将$k=2$的情况扩展。对所有删去的点的每个点对 $(i,j)$，如果$i$能到达$j$，就往$i\to j$连一条的边，然后再拓扑排序一遍：对于每个点$i$的出边 $p$ 将 $f_p\leftarrow f_p-f_i\times d_{i,p}$ 。最后统计答案，即
$$ans=s-\sum\limits_{i=1}^kf_{c_i}\times n\!f_{c_i}$$
这个可以通过预处理拓扑序避免每次询问再跑一遍拓扑，即根据**拓扑序排序**后进行容斥。

$O(nm)$预处理，$O(k^2)$查询，总复杂度$O(nm+k\sum k)$。

## [参考代码](https://www.luogu.com.cn/paste/2xoqfn83)

---

## 作者：a___ (赞：8)

如果不考虑删点求链数，我们显然有一个很简单的 $\mathbf O(n)$ DAG 拓扑序上 dp。设 $f_i$ 表示从入度为 $0$ 的点到 $i$ 的方案数，有 $\forall (u,v),f_v\leftarrow f_u$。最终答案即为所有出度为 $0$ 的点的 $f$ 之和。  

现在考虑删一个点 $x$ 的情况，容易想到再设一个 $g_i$ 表示从出度为 $0$ 的点到 $i$ 的方案数，最后总答案减去 $f_xg_x$。  

考虑删多个点，由于本题 $n,k$ 很小，考虑容斥。显然直接减 $k$ 次 $f_xg_x$ 会算重，于是我们再求一个两点之间的路径数 $h_{x,y}$。将所有拓扑序比 $x$ 大的所有 $y$ 的 $f_y$ 减 $f_xh_{x,y}$，然后再乘 $g_x$，再从总答案中减掉。

复杂度 $\mathbf O(nm+k\sum k)$。  

```cpp
#include<cstdio>
#include<algorithm>
const int N=2010,M=20010,p=1e9+7;
int n,m,qt,las[N],nxt[M],to[M],cnt,du[N],c[N],d[N],f[N],g[N],h[N][N],q[N],id[N],sum,ans;
inline void add(int u,int v){++cnt;to[cnt]=v;nxt[cnt]=las[u];las[u]=cnt;++du[v];}
bool cmp(const int &x,const int &y){return id[x]<id[y];}
int main()
{
	int i,j,k,x,y,hd,tl=0;scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)scanf("%d%d",&x,&y),add(x,y);
	for(i=1;i<=n;i++)if(!du[i])f[q[++tl]=i]=1;
	for(hd=1;hd<=tl;++hd)for(i=las[q[hd]];i;i=nxt[i]){f[to[i]]=(f[to[i]]+f[q[hd]])%p;if(!--du[to[i]])q[++tl]=to[i];}
	for(hd=tl;hd>=1;--hd)if(las[q[hd]])for(i=las[q[hd]];i;i=nxt[i])g[q[hd]]=(g[q[hd]]+g[to[i]])%p;else g[q[hd]]=1,sum=(sum+f[q[hd]])%p;
	for(i=1;i<=n;i++)
	{
		h[q[i]][q[i]]=1;id[q[i]]=i;
		for(j=i;j<=n;j++)for(k=las[q[j]];k;k=nxt[k])h[q[i]][to[k]]=(h[q[i]][to[k]]+h[q[i]][q[j]])%p;
	}
	scanf("%d",&qt);
	while(qt--)
	{
		scanf("%d",&m);ans=sum;
		for(i=1;i<=m;i++)scanf("%d",&c[i]);
		std::sort(c+1,c+1+m,cmp);
		for(i=1;i<=m;i++)d[i]=f[c[i]];
		for(i=1;i<=m;i++)for(j=i+1;j<=m;j++)d[j]=(d[j]-1ll*d[i]*h[c[i]][c[j]]%p+p)%p;
		for(i=1;i<=m;i++)ans=(ans-1ll*d[i]*g[c[i]]%p+p)%p;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：wwlw (赞：3)

### Description

给定一个 DAG，每次询问如果删除 $k\leq 15$ 个点，还剩下多少条入度为零的点到出度为零的点的路径。新增的路径不参与统计。

### Solution

唯一可做题，其他的都没什么思路/kel。

$k$ 很小，容易想到一个枚举子集的做法，那么只需要预处理出每两个点之间的距离。可以按拓扑序删点，然后再一遍拓扑求出所有点到当前点的距离。配合容斥可以过前 75%，复杂度 $O(nm+q2^k)$。

发现只需要知道最后一个点是哪个点，把这 $k$ 个点按拓扑序排序，然后考虑 dp。$dp_{i,j}$ 表示选了 $j$ 个点，最后一个点是第 $i$ 个的从入度为零的点到 $i$ 的路径条数。那么统计答案就只需要乘上 $(-1)^j$ 的容斥系数，再乘上点到终点的方案数。这样单次询问就是 $O(k^3)$。

再次观察，发现并不需要知道选了多少个，只需要在转移的时候容斥，那么就可以删掉一维。单次 $O(k^2)$。

```cpp
#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

const int N=2e3+7;
const int Mod=1e9+7;

queue<int> Q;
vector<int> G[N];
int dfn[N],in[N],dis[N][N],In[N],a[N],dp[16];

inline bool Cmp(int x,int y){return dfn[x]<dfn[y];}

int main(){
    freopen("foodchain.in","r",stdin);
    freopen("foodchain.out","w",stdout);
    int n=read(),m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        G[u].push_back(v),In[v]++;
    }
    for(int u=1;u<=n;u++){
        if(!G[u].size()) G[u].push_back(n+1),In[n+1]++;
        if(!In[u]) G[0].push_back(u),In[u]++;
        in[u]=In[u];
    }
    Q.push(0); int timer=0;
    while(!Q.empty()){
        int u=Q.front(); Q.pop(); dfn[u]=++timer;
        for(int v:G[u]) if(!(--in[v])) Q.push(v);
    }
    for(int i=0;i<=n+1;i++) a[i]=i;
    sort(a,a+1+n+1,Cmp);
    for(int i=0;i<=n+1;i++){
        const int U=a[i];
        for(int v=0;v<=n+1;v++) in[v]=In[v];
        dis[U][U]=1;
        for(int j=i;j<=n+1;j++)
            if(!in[a[j]]) Q.push(a[j]);
        while(!Q.empty()){
            int u=Q.front(); Q.pop();
            for(int v:G[u]){
                dis[U][v]=(dis[U][v]+dis[U][u])%Mod;
                if(!(--in[v])) Q.push(v);
            }
        }
        for(int v:G[U]) --In[v];
    }
    int q=read();
    while(q--){
        int k=read();
        for(int i=1;i<=k;i++) a[i]=read();
        sort(a+1,a+1+k,Cmp);
        for(int i=1;i<=k;i++)
            dp[i]=Mod-dis[0][a[i]]; 
        for(int i=1;i<=k;i++)
        for(int j=1;j<i;j++)
            dp[i]=(dp[i]-1ll*dp[j]*dis[a[j]][a[i]]%Mod+Mod)%Mod;
        int ans=dis[0][n+1];
        for(int i=1;i<=k;i++)
            ans=(ans+1ll*dp[i]*dis[a[i]][n+1]%Mod)%Mod;
        printf("%d\n",ans);
    }
}
```

---

## 作者：EnofTaiPeople (赞：3)

对于一个有向无环图，首先想到的就是进行拓扑排序。排序的同时，可以将两点之间的路径数预处理出来，并在这之前，把所有入度为零的点放入集合 ```S```，出度为零的点放到集合 ```T```，最开始的答案记为 ```sum```。为了查询方便，同时记录 ```onto[x]``` 为所有入度为零的点到 x 的路径总数，```znto[x]``` 为 x 到所有出度为零的点的路径总数，代码如下：
```cpp
for(i=1;i<=m;++i){x=read();lk[x].push_back(y=read());++deg[y];}
for(x=1;x<=n;++x){if(deg[x]==0)S.push_back(x);if(lk[x].empty())T.push_back(x);}
queue<int>bfs;Ssize=S.size();Tsize=T.size();
for(i=0;i<Ssize;++i)bfs.push(S[i]);
while(!bfs.empty()){
	x=bfs.front();bfs.pop();siz=lk[x].size();
	RT[Topo[x]=++Top]=x;Got[x][x]=1;
	for(i=0;i<siz;++i){
		if(--deg[lk[x][i]]==0)bfs.push(lk[x][i]);
		for(ai=1;ai<=n;++ai)(Got[ai][lk[x][i]]+=Got[ai][x])%=M;
	}
}
for(ai=0;ai<Ssize;++ai)
	for(i=0;i<Tsize;++i)
		sum=(sum+Got[S[ai]][T[i]])%M;
for(ai=0;ai<Ssize;++ai)
	for(i=1;i<=n;++i)
		(onto[i]+=Got[S[ai]][i])%=M;
for(ai=0;ai<Tsize;++ai)
	for(i=1;i<=n;++i)
		(znto[i]+=Got[i][T[ai]])%=M;
```
容易发现上面的做法是 $O(n^2)$，因此不会超时。
接下来是一个递推的过程，记 ```ans[x]``` 为从所有入度为零的点到 x 的**有效**路径总数，这里的**有效**指的是没有经过任何一个被删除的点的路径总数。
于是，$ans[x]=onto[x]-Got[x][y]\times\sum\limits_{y \in Delt\bigwedge y\neq x}^nans[y]$ 因为任意无效路径已经从 ```ans``` 数组中去除所以不会统计两遍。注意 x 到 y 有路径的必要条件是 x 的拓扑序比 y 更靠前，于是可以将询问先按拓扑序进行排序然后每次循环只需考虑拓扑序比当前点更靠前的点。完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e3+3,M=1e9+7;
char buf[1<<23],*p1,*p2,c;
int an,f,Ssize,Tsize;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1==p2))?EOF:*p1++
inline int read(){
	an=0;f=1;while(!isdigit(c=gc))if(c=='-')f=-f;
	do an=an*10+c-'0';while(isdigit(c=gc));return an*f;
}
ll Got[N][N],onto[N],znto[N],sum,nsum,ans[N];
int Topo[N],Top,n,m,ask[40],k,deg[N],now,fdeg[N],q,RT[N];
inline bool cmp(const int &a,const int &b){
	return Topo[a]<Topo[b];
}
vector<int>lk[N],S,T;
int main(){
	n=read();m=read();int i,x,y,siz,ai;
	for(i=1;i<=m;++i){x=read();lk[x].push_back(y=read());++deg[y];}
	for(x=1;x<=n;++x){if(deg[x]==0)S.push_back(x);if(lk[x].empty())T.push_back(x);}
	queue<int>bfs;Ssize=S.size();Tsize=T.size();
	for(i=0;i<Ssize;++i)bfs.push(S[i]);
	while(!bfs.empty()){
		x=bfs.front();bfs.pop();siz=lk[x].size();
		RT[Topo[x]=++Top]=x;Got[x][x]=1;
		for(i=0;i<siz;++i){
			if(--deg[lk[x][i]]==0)bfs.push(lk[x][i]);
			for(ai=1;ai<=n;++ai)(Got[ai][lk[x][i]]+=Got[ai][x])%=M;
		}
	}
	for(ai=0;ai<Ssize;++ai)
		for(i=0;i<Tsize;++i)
			sum=(sum+Got[S[ai]][T[i]])%M;
	for(ai=0;ai<Ssize;++ai)
		for(i=1;i<=n;++i)
			(onto[i]+=Got[S[ai]][i])%=M;
	for(ai=0;ai<Tsize;++ai)
		for(i=1;i<=n;++i)
			(znto[i]+=Got[i][T[ai]])%=M;
	q=read();
	while(q--){
		for(ai=1,k=read();ai<=k;++ai)ask[ai]=read(),ans[ai]=0;
		sort(ask+1,ask+k+1,cmp);nsum=sum;
		for(ai=1;ai<=k;++ai){
			ans[ai]=onto[ask[ai]];
			for(i=1;i<ai;++i)
				(ans[ai]-=ans[i]*Got[ask[i]][ask[ai]])%=M;
			(nsum-=ans[ai]*znto[ask[ai]])%=M;
		}
		nsum=(nsum+M)%M;
		printf("%lld\n",nsum);
	}
	return 0;
}
```

---

## 作者：yzh_Error404 (赞：1)

前置知识点： 拓扑排序+容斥

本题分三个步骤：建图，拓扑，容斥减边

因为有多个入度为零的点和出度为零的点，所以我们可以建一个超级源点连接所有入度为零的点，一个超级汇点连接所有出度为零的点。

建图讲完了，接下来是拓扑。

拓扑就是普通的拓扑，但需要记录拓扑序 $dfn$ ，同时记录每个点到每个点的路径数量 $dp$ 。

最后是容斥减边，先把要删的点按拓扑序排序，之后找出每一个点对 $(c_i,c_j)~,~i,j\in[1,k+1]$ ，让  $dis_i$ 减去 $dis_j\times dp_{del_j,del_i}$ 即可（ $dis_i$ 表示超级源点到点 $i$ 的路径条数 ）。

最终答案就是 $dis_{k+1}$ 即超级源点到超级汇点的路径条数。

代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=8e3+5;
const int MAXM=4e4+5;
const int MOD=1e9+7;
struct node
{
	int to,nxt;
}e[MAXM];
int head[MAXN],cnt,sum;
int ru[MAXN],chu[MAXN];
int dfn[MAXN],dp[MAXN][MAXN];
int del[MAXN],dis[MAXN];
int n,m;
inline void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
	chu[x]++;
	ru[y]++;//统计入度和出度
}
inline void topo()//普通的拓扑排序
{
	queue<int>q;
	q.push(n-1);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		dfn[x]=++sum;//记录拓扑序
		for(register int i=head[x];i;i=e[i].nxt)
		{
			int y=e[i].to;
			ru[y]--;
			for(register int j=1;j<=n;j++)
				dp[j][y]=(dp[j][y]+dp[j][x])%MOD;//累加路径条数
			if(!ru[y])q.push(y);
		}
	}
}
inline bool cmp(int x,int y)//被删除的点需按拓扑序排序
{
	return dfn[x]<dfn[y];
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(register int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%lld%lld",&x,&y);
		add(x,y);
	}
	for(register int i=1;i<=n;i++)//建立超级源点n+1
		if(!ru[i])add(n+1,i);
	for(register int i=1;i<=n;i++)//建立超级汇点n+2
		if(!chu[i])add(i,n+2);
	n+=2;
	for(register int i=1;i<=n;i++)
		dp[i][i]=1;
	topo();
	int q;
	scanf("%lld",&q);
	while(q--)
	{
		int k;
		scanf("%lld",&k);
		for(register int i=1;i<=k;i++)
			scanf("%lld",&del[i]);
		del[0]=n-1;
		del[k+1]=n;
		dis[0]=-1;
		sort(del+1,del+k+1,cmp);
		for(register int i=1;i<=k+1;i++)
		{
			dis[i]=0;
			for(register int j=0;j<i;j++)
				dis[i]=(dis[i]-dis[j]*dp[del[j]][del[i]]%MOD)%MOD;//容斥减边
		}
		printf("%lld\n",(dis[k+1]+MOD)%MOD);//答案就是dis[k+1]
	}
	return 0;
}
```

---

## 作者：JiaY19 (赞：1)

比较恶心的一道蓝题。

#### 思路

拓扑排序 + dp。

看到有向无环图，首先考虑拓扑排序。

记录下每个点的拓扑序，以及每两个节点之间有多少条路径,以及 $f_{i}$ 和 $r_{i}$。

 $f_{i}$ 为入度为 $0$ 到点 $i$ 的路径数，$r_{i}$ 为反图上的 $f_{i}$。

运用DP，设需要删除的点为 $c_{i}$ 。

对于每个点 $c_{i}$ 的出边 $c_{j}$ ，将 $f_{c_j}$ 减去 $f_{c_j} \times d_{c_i , c_j}$ 。

其中 $d_{c_i , c_j}$ 代表 $c_{i}$ 到 $c_{j}$ 有多少条路径。

最后在统计答案，即$sum - \sum{f_{c_i} \times r_{c_i}}$。

发现每次DP时都做拓扑排序比较麻烦。

所以可以预处理。

也就相当于根据拓扑排序进行容斥。

#### Code

代码也不算长。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p = 1e9 + 7;
int n, m, q, cnt, leng;
int head[3001], ru[3001], chu[3001], dfn[3001], dp[3001][3001], f[3001], c[3001];

struct edge
{
    int to, nxt;
} e[20010], e1[20010];

int read()
{
    int X = 0, qwe = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-') qwe = -1;
        ch = getchar();
    }
    while (isdigit(ch))
        X = X * 10 + (int)(ch - '0'),
        ch = getchar();
    return X * qwe;
}

void add(int x, int y)
{
    e[++cnt] = (edge)
    {
        y, head[x]
    };
    head[x] = cnt;
}

void topo()
{
    int top;
    queue<int>q;
    q.push(n - 1);
    while (!q.empty())
    {
        top = q.front(), dfn[top] = ++leng, q.pop();
        for (int i = head[top]; i > 0; i = e[i].nxt)
        {
            ru[e[i].to]--;
            for (int j = 1; j <= n; ++j) dp[j][e[i].to] = (dp[j][top] + dp[j][e[i].to]) % p;
            if (!ru[e[i].to]) q.push(e[i].to);
        }
    }
    return;
}

bool cmp(int x, int y)
{
    return dfn[x] < dfn[y];
}

signed main()
{
//    freopen("foodchain.in", "r", stdin);
//    freopen("foodchain.out", "w", stdout);
    int x, y;
    n = read(), m = read();
    for (int i = 1; i <= m; i++) x = read(), y = read(), add(x, y), ru[y]++, chu[x]++;
    for (int i = 1; i <= n; i++)
        if (!ru[i])
            add(n + 1, i), ru[i]++, chu[n + 1]++;
    for (int i = 1; i <= n; i++)
        if (!chu[i])
            add(i, n + 2), chu[i]++, ru[n + 2]++;
    n += 2;
    for (int i = 1; i <= n; i++) dp[i][i] = 1;
    topo(), q = read();
    while (q--)
    {
        int k = read();
        for (int i = 1; i <= k; i++) c[i] = read();
        c[0] = n - 1, c[k + 1] = n, f[0] = -1;
        sort(c  + 1, c + k + 1, cmp);
        for (int i = 1; i <= k + 1; i++)
        {
            f[i] = 0;
            for (int j = 0; j <= i - 1; j++) f[i] = (f[i] - f[j] * dp[c[j]][c[i]] % p) % p;
        }
		printf("%lld\n" , (f[k + 1] + p) % p);
    }
    return 0;
}
```

---

## 作者：xie_lzh (赞：0)

# P6651题解
## 题意 
自己看题面。
## 思路
题目给出这是个 $DAG$ 所以猜测要用拓扑排序。

再看询问 ：询问 $q$ 次，每次询问独立。

看到数据范围 $q≤500000$ 显然需要在询问前预处理，否则时间会炸。

所以容易想到应先预处理出一个点也不删时链的数量。

在看到每次询问给出多个点，求删除后链的数量，发现不太好想，所以先考虑只删一个点。

在这种情况下，可以预处理每个点到 食物链顶端 的路径条数 和 到 食物链底部 的路径条数，每次询问将删除的点到 链顶和链底 的路径条数相乘，再输出预处理出的 链的条数 减去这个值，可以做到 $O(1)$ 的询问，但要注意取模是要在取完一次模后再加 $mod$ 再模 $mod$ ，不然会有负数的情况。

--------------------------------------------
在考虑完一个点后，再想每次删两个点的做法。

当这两个点不在同一条链上是，直接按一个点的求法就行。

当两个点位于同一条连上时，可以考虑将拓扑序大的点到 食物链底部 的路径条数减去拓扑序小的点到 食物链底端的路径条数乘上两点之间的路径条数，感性理解即为 拓扑序大的点在不经过 拓扑序小的那个点的情况下到食物链底部的路径条数，这样一来，就能有效地去重。

三个点及以上的情况与两个点的情况相似，这里不再赘述。

具体看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
const ll N=2e3+5,M=2e4+5,mod=1000000007;
ll n,m,q,k,c[N],st[N],ed[N],rd[N],cd[N],ans,nans;
ll head[N],to[M],nxt[M],cnt,topo,top[N],kk[N],S[N],T[N],ss,tt;
ll dis[N][N];
queue<int> d;
ll read()//快读
{
	int r=0,f=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')  f=-1;
		c=getchar();
	} 
	while(isdigit(c))  
	{
		r=(r<<1)+(r<<3)+c-48;
		c=getchar();
	}
	return r*f;
}
void add(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
bool cmp(int x,int y) //按拓扑序排序
{
	return top[x]<top[y];
}
signed main()
{
	n=read(); m=read();
	for(int i=1,u,v;i<=m;i++) //连边
	{
		u=read();v=read();
		add(u,v);
		rd[v]++; cd[u]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(rd[i]==0)
		{
			d.push(i);
			S[++ss]=i; //链底数量
		}
		if(cd[i]==0)
			T[++tt]=i; //链顶数量
	}
		
	while(!d.empty()) //求任意两点之间路径条数，同时记录拓扑序
	{
		int u=d.front();
		d.pop();
		dis[u][u]=1;
		top[u]=++topo;
		for(int i=head[u];i;i=nxt[i])
		{
			int v=to[i];
			for(int j=1;j<=n;j++)
				dis[j][v]=(dis[j][v]+dis[j][u])%mod;
			rd[v]--;
			if(rd[v]==0) d.push(v);
		}
	}
	for(int i=1;i<=ss;i++)
		for(int j=1;j<=tt;j++)
			(ans+=dis[S[i]][T[j]])%=mod; //初始链的条数
	for(int i=1;i<=ss;i++)
		for(int j=1;j<=n;j++)
			(st[j]+=dis[S[i]][j])%=mod; //每个点到链底的条数
	for(int i=1;i<=tt;i++)
		for(int j=1;j<=n;j++)
			(ed[j]+=dis[j][T[i]])%=mod; //每个点到链顶的条数
	q=read();
	while(q--)
	{
		k=read();
		nans=ans;
		for(int i=1;i<=k;i++)
			c[i]=read();
		sort(c+1,c+1+k,cmp);//拓扑排序
		for(int i=1;i<=k;i++)
		{
			kk[i]=st[c[i]];
			for(int j=1;j<i;j++)
				(kk[i]-=dis[c[j]][c[i]]*kk[j])%=mod; //减去重复部分
			nans=((nans-kk[i]*ed[c[i]])%mod+mod)%mod; //注意去模
		}
		printf("%lld\n",nans);
	}
}
```


---

