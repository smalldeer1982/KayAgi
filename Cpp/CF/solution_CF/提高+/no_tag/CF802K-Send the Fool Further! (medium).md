# Send the Fool Further! (medium)

## 题目描述

## 题面
给定一棵节点数为 $n$  （编号为 $0-(n-1)$  ）的树，每一条边有一个权值。现在要求从点0出发，在不经过一个点超过 $k$  次的情况下经过的边的权值和最大。（每一条边在第一次经过之后权值即变为0；从点0出发时也视作经过了1次点0；最后不需要回到点0）

## 说明/提示

$ 3≤n≤10^5 $   
$ 1≤k≤10^5 $   
$ 0≤u,v≤n-1, 1≤c≤10^4 $   

感谢@星烁晶熠辉 提供的翻译

## 样例 #1

### 输入

```
9 3
0 1 1
0 2 1
1 3 2
1 4 2
1 5 2
2 6 3
2 7 3
2 8 3
```

### 输出

```
15
```

## 样例 #2

### 输入

```
9 5
0 1 1
0 2 1
1 3 2
1 4 2
1 5 2
2 6 3
2 7 3
2 8 3
```

### 输出

```
17
```

## 样例 #3

### 输入

```
11 6
1 0 7932
2 1 1952
3 2 2227
4 0 9112
5 4 6067
6 0 6786
7 6 3883
8 4 7137
9 1 2796
10 5 6200
```

### 输出

```
54092
```

# 题解

## 作者：crh1272336175 (赞：4)

dp

f[i][0]代表i点出发最终回到i点能访问的最多点数（最多访问k-1个分支）

f[i][1]代表i点出发最终不回到i点能访问的最多点数（最多访问k个分支）

最终答案=f[1][1]

先dfs一遍，求出儿子数量，若儿子数小于等于k-1，那么全部可以访问，只需对f[i][0]排序即可。

如果儿子数大于k-1，那么优先取k-1个最大的，剩下的1个通过枚举来确定

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
int n,k,tot;
int Next[M<<1],head[M],des[M<<1],len[M<<1];
int f[M][2],sum[M],s[M];
void add(int a,int b,int c)
{
	Next[++tot]=head[a]; des[tot]=b; len[tot]=c;
	head[a]=tot;
} 
int cmp(int a,int b)
{
	return f[a][0]>f[b][0];
} 
void dfs(int x,int pre)
{
	for(int i=head[x]; i; i=Next[i])
	{
		int y=des[i],z=len[i];
		if(y==pre) continue;
		dfs(y,x);
		f[y][0]+=z; f[y][1]+=z;
	}
	int cnt=0;
	for(int i=head[x]; i; i=Next[i])
	{
		int y=des[i];
		if(y==pre) continue;
		s[++cnt]=y;
	}
	sort(s+1,s+1+cnt,cmp);
	for(int i=1; i<=cnt; i++) sum[i]=sum[i-1]+f[s[i]][0];
	f[x][0]=sum[min(k-1,cnt)];
	for(int i=1; i<=cnt; i++)
	{
		if(i<=k) f[x][1]=max(f[x][1],sum[min(cnt,k)]-f[s[i]][0]+f[s[i]][1]);
		else f[x][1]=max(f[x][1],sum[k-1]+f[s[i]][1]); 
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1; i<n; i++)
	{
		int a,b,c; scanf("%d%d%d",&a,&b,&c);
		a++; b++;
		add(a,b,c); add(b,a,c);
	}
	dfs(1,0);
	printf("%d",f[1][1]);
	return 0;
}
```


---

## 作者：jiuguaiwf (赞：3)

没人发那我就写一篇......

#### 题目给了一棵树，要求经过的边权和最大（多次经过只能算一次），且每个点至多经过K次。

#### 几秒思考后：求树上最大权值联通块，且每点出度最多为K-1?

然而码完后连样例都过不了QwQ

#### 题目提示我们最终不必回到起点，那么我们可以用最后一次机会走向树梢而不是返回权值早已取完的祖先节点！这样权值和更大啦～

捋顺思路，考虑dp状态：有K-1个子节点必须返回，1个子节点可以延伸到远方。

dp[u][0]表示回到u点获得的最大权值和，dp[u][1]表示不会u点，向下延伸的最大和。

#### 转移显然：设v为u的儿子，dp[u][0]就是权值最大的K-1个dp[v][0]之和；dp[u][1]取K-1个dp[v][0]与1个dp[v][1]的和的max。

权值排序后从高往低选搞定它。

递推dp[u][1]时有个小技巧：取前K个dp[v][0]，之后再枚举K个中哪一个取dp[v][1]，sum+dp[v][1]-dp[v][0]更新答案就行了。

自认为代码挺清楚的呢～

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int dp[100005][2],n,cnt,h[100005],k,val[100005];
struct wf{int to,nxt,w;}edge[100005<<1];
struct wff{int val,x;};
vector<wff> son[100005];
void add(int u,int v,int w)
{
	edge[++cnt].to=v;
	edge[cnt].w=w;
	edge[cnt].nxt=h[u];
	h[u]=cnt;
}
bool cmp(wff a,wff b){return a.val>b.val;}
void dfs(int u,int fa)
{
	for (int i=h[u];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if (v==fa) continue;
		dfs(v,u);
		val[v]=dp[v][0]+edge[i].w;
		son[u].push_back((wff){val[v],v});
	}
	sort(son[u].begin(),son[u].end(),cmp);
	for (int i=0;i<son[u].size();++i)
	{
		dp[u][0]+=son[u][i].val;//推dp[u][0]，只取K-1个
		if (i>=k-2) break;
	}
	int sum=0;
	for (int i=0;i<son[u].size();++i)
	{
		sum+=son[u][i].val;
		if (i>=k-1) break;//先算K个的sum
	}
	for (int i=0;i<son[u].size();++i)
	{
		dp[u][1]=max(dp[u][1],sum+dp[son[u][i].x][1]-dp[son[u][i].x][0]);//小技巧
		if (i>=k-1) break;
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	int u,v,w;
	for (int i=1;i<n;++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		++u,++v;
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,1);
	printf("%d",dp[1][1]);
	return 0;
}
```
有问题您私我。


NOI前发题解能涨RP？   NOI2019 RP++,Bless all;


---

## 作者：lei_yu (赞：2)

值得一做的树形DP
------------

首先要转化题目条件，不难想到：

**如果经过某个点$k$次且要回到这个点，则最多可以向下经过这个点的$k-1$颗子树。**


**如果经过某个点$k$次且不用回到这个点，则最多可以向下经过这个点的$k$颗子树。**

这是这个题的突破口，通过下图可以直观地理解：（不要忘记了到达这个点也算是经过这个点）

![](https://cdn.luogu.com.cn/upload/image_hosting/yv4ysz8z.png)


------------

通过以上分析，我们便可以设出方程并转移了。

首先设$f[u][0/1]$表示以点u为根的子树不回/回到当前点获得的最大代价（经过边的权值和）

对于$f[u][1]$即回到当前点的代价，我们只需要取获得代价最大的$min(son[u],k-1)$个子树的$f[v][1]$并加上$dis(u,v)$即可。

（$son[u]$表示点$u$的儿子即子树个数）

至于怎么求代价最大的前$k-1$个子树，直接开一个数组$t$然后$sort$就行。

显然这样不会超时。但是我们**t数组由于时间原因是不能每一次都清零的，因此需要注意一下不要在叶子节点使用这个数组**

------------

对于$f[u][0]$即不用回到当前点的代价，除了上一段话里面的两个部分，还需要加上某一个子树的$f[u][0]$，但是由于**一个子树只能取0或1不能两个都取**，我们无法确定应该取哪一个子树不回来，因此必须枚举一下。

为了每一次直接使用前$k$个和前$k-1$个$f[v][1]$的和，可以使用前缀和。

这个转移是本题的中心，具体实现可以参考代码。码疯不行请见谅。

------------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int r()
{
	int k=1,s=0;char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')k=-1;
		c=getchar();
	}
	while(isdigit(c))
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*k;
}
struct node
{
	int to,next,dis;
}a[250001];
struct nood
{
	int w,bh;
}s[200001];
int n,k,cnt,head[200001],f[200001][2],size[200001],sum[200001];
void add_edge(int from,int to,int dis)
{
	a[++cnt].to=to;
	a[cnt].next=head[from];
	a[cnt].dis=dis;
	head[from]=cnt;
}
bool cmp(nood x,nood y)
{
	return x.w>y.w;
}
void dfs(int u,int fa)
{
	for(int i=head[u];i;i=a[i].next)
	{
		int v=a[i].to;
		if(v!=fa)dfs(v,u);
	}
	
	int t=0;
	for(int i=head[u];i;i=a[i].next)//不能放到一起，不然s数组就乱了 
	{
		int v=a[i].to;
		if(v!=fa)
		{
			f[v][1]+=a[i].dis;//边界：到达就会访问这条边
			f[v][0]+=a[i].dis;
			s[++t].w=f[v][0];
			s[t]. bh=v;
		}
	}
	
	sort(s+1,s+t+1,cmp); 
	
	for(int i=1;i<=t;i++)sum[i]=sum[i-1]+s[i].w;//前缀和 
	f[u][0]=sum[min(k-1,t)];//注意越界 
	
	if(t==0)return;
	
	for(int i=1;i<=k;i++)
	{
		f[u][1]=max(f[u][1],sum[min(k,t)]-s[i].w+f[s[i].bh][1]);//1到k之间的选择 
		if(i>=t)break;
	}

	//第K个选择在上面或者下面都一样 
	
	for(int i=k+1;i<=t;i++)
	f[u][1]=max(f[u][1],sum[k-1]+f[s[i].bh][1]);//k之后的选择 
	
}
int main()
{
	int x,y,z;
	n=r();k=r();
	for(int i=1;i<n;i++)
	{
		x=r();y=r();z=r();
		x++;y++;
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	dfs(1,0);
	cout<<f[1][1];
	return 0;
}
```


---

## 作者：xfrvq (赞：1)

$\tt^\ast2100$，简单切掉。$\Large\texttt{CSP2022 rp++}$。

模拟一遍样例 1，发现总路程分为两部分

1. 遍历 $\tt1$ 这棵子树，最后回到 $\tt1$。
2. 遍历 $\tt2$ 这棵子树，最后停在 $\tt2$。

通过观察题意我们知道子树间并没有干扰，考虑树形 $\tt DP$。

$\tt DP$ 算出子树答案？

通过观察上述的那个过程，我们发现 $\tt DP$ 状态应该有两种

+ $f_i$：从 $i$ 开始向 $i$ 的子树走，最后**必须**回到 $i$，答案最大多少。
+ $g_i$：从 $i$ 开始向 $i$ 的子树走，最后**不必**回到 $i$，答案最大多少。

最后的答案即是 $g_0$

下面我们记 $v$ 是 $u$ 的儿子，$w$ 是 $(u,v)$ 边权。

+ $f_u$ 转移：将所有 $f_v+w$ 排序，最大的 $k-1$ 个之和。
+ $g_u$ 转移：枚举每一个 $v$ 作为结束时走的子树，答案就是最大的 $k-1$ 个 $f_{v_0}+w$ 加上 $g_v+w$（当然 $\forall v_0,v_0\ne v$）。

其实就是简单的对 $f_v+w$ 排序。

```cpp
const int N = 1e5 + 5;
const int inf = 1e9;

int n,k;
vector<pair<int,int>> G[N];
ll f[N],g[N];

void dfs(int u = 1,int ft = 0){
	vector<int> son;
	for(auto[v,w] : G[u]) if(v != ft) 
		dfs(v,u),f[v] += w,g[v] += w,son.pb(v);
	if(G[u].size() <= k){
		for(int v : son) f[u] += f[v];
		for(int v : son) g[u] = max(g[u],f[u] - f[v] + g[v]);
	} else {
		vector tmp({inf});
		for(int v : son) tmp.pb(f[v]);
		ranges::sort(tmp,greater<>());
		rep(i,1,k - 1) f[u] += tmp[i];
		for(int v : son){
			ll ans = f[u] + g[v];
			if(f[v] >= tmp[k - 1]) ans += tmp[k] - f[v];
			g[u] = max(g[u],ans);
		}
	}
}

int main(){
	read(n,k);
	for(int i = 1;i < n;++i){
		int u,v,w;
		read(u,v,w); ++u,++v;
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
	}
	dfs();
	print(g[1]);
	return 0;
}
```

---

