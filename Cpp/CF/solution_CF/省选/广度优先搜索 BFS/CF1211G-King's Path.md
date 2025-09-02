# King's Path

## 题目描述

树之国有n个城市和n-1条双向道路。每条路连接着两个不同的城市。你可以从任何一个城市开车到另一个城市，只需要沿着道路行驶。城市的编号从1到n。当然，你在这个描述中认出了一棵无向树。

每个城市都有一面国旗，在第 i 个城市，国旗的颜色是$c_i$。不同城市的国旗颜色可能是一样的。

如果国王旅行沿途 [$u_1$,$u_2$,$u_3$,...,$u_k$] 那么这就意味着,他开始在城市 $u_1$ ,然后移动到城市$u_2$  ($u_2$与$u_1$之间有公路连接) ,然后从$u_2$到$u_3$ ($u_3$与$u_2$之间有公路连接),直到他到达城市$u_k$。在这条路线上，国王可能会多次访问同一个城市。换句话说，路线[$u_1$,$u_2$,$u_3$,...,$u_k$]不一定由不同的城市组成。在图论方面，国王沿着一些路径 [$u_1$,$u_2$,$u_3$,...,$u_k$] 从$u_1$移动到$u_k$，这并不一定简单(对于城市 $u_j$ 和$u_{j+1}$(所有 j 取于1到k-1)都是通过道路连接的)。

当国王从一个城市到另一个城市时，城市领导人交换旗帜作为他们友谊的标志。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1211G/d695a88743c705b53ebb6d0c8763366c0983b769.png)
例：
移动国王沿路线[1,4,2,6]。顶点的颜色与该顶点的标志颜色相匹配。出于美观的原因，国王希望城市$d_i$(1$\le$i$\le$n)的旗帜颜色都是相同的。确定国王是否可以选择一些路线并沿着它行驶，以便每个城市的旗帜颜色都与期望的颜色相同。**注意，国王可以选择(并驾驶)一条路线。如果是，为国王找一条最短的路线。**

如果旗子的初始颜色已经符合国王的要求(即对于所有i,$c_i$=$d_i$)，则认为国王的路线长度为k=0。

## 样例 #1

### 输入

```
1
7
2 3 2 7 1 1 3
7 1 2 3 1 2 3
1 7
4 1
2 6
2 3
2 4
5 4
```

### 输出

```
Yes
4
1 4 2 6 
```

## 样例 #2

### 输入

```
1
5
1 2 2 2 2
2 2 2 2 1
1 2
2 3
3 4
4 5
```

### 输出

```
Yes
5
1 2 3 4 5 
```

## 样例 #3

### 输入

```
3
4
10 20 10 20
20 10 20 10
1 2
1 3
1 4
2
1000000 1000000
1000000 1000000
1 2
10
4 2 2 4 2 4 1 2 3 4
4 2 4 4 3 2 1 2 4 2
5 8
6 9
10 5
1 10
7 10
3 4
5 9
3 10
2 4
```

### 输出

```
No
Yes
0
Yes
5
3 10 5 9 6 
```

# 题解

## 作者：Lynkcat (赞：2)

考虑最终操作的一定是一条链，因为非简单路径的操作等价于某一条简单路径。

假设最终操作的一定是根到某一个点的路径，然后是把那个点转到根这里来。这样就可以哈希了，记录根到当前点路径的 $b$ 数组哈希值以及不算上根的 $a$ 数组哈希值。然后看看把 $a$ 左移一位再加上根的 $a$ 是否和 $b$ 相等，并且还要满足不被经过的子树每个节点的 $a_i$ 都等于 $b_i$。

然后现在问题就是找到这个根，直接把 $a$ 不等于 $b$ 的点扣出来虚树找叶子就行了。实现是不需要建虚树，上面只是描述的形象一点而已（

时间复杂度 $O(n)$。这题只允许 Kotlin 语言的提交，但是可以通过扔到 gym 的 mashup 里用 C++ 提交。

```c++
// Lynkcat.
// Problem: A. King's Path
// Contest: Codeforces - 10.10
// URL: https://codeforces.com/gym/403227/problem/A
// Memory Limit: 256 MB
// Time Limit: 5000 ms

#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e9
#define mod 998244353
#define mod1 1000000007
#define int ll
#define N 200005
using namespace std;
int dep[N],ffa[N],v[N];
int Ans;
int tot=0;
int a[N],b[N];
int siz[N];
int col[N];
poly G[N];
int Rt,Rt1;
int n;
pa work(pa x,int y)
{
	x.fi=(x.fi*233%mod+y)%mod;
	x.se=(x.se*233%mod1+y)%mod1;
	return x;
}
void dfs1(int k,int fa)
{
	ffa[k]=fa;
	v[k]=(a[k]==b[k]);
	dep[k]=dep[fa]+1;
	for (auto u:G[k])
	{
		if (u==fa) continue;
		dfs1(u,k);
		v[k]&=v[u];
	}
}
void dfs(int k,int fa,pa x,pa y)
{
	x=work(x,b[k]);
	if (fa)
		y=work(y,a[k]);
	int sum=0;
	for (auto u:G[k])
	{
		if (u==fa) continue;
		sum+=v[u];
	}
	if (fa)
	{
		pa z=y;
		z=work(z,a[Rt]);
		if (z==x&&sum==(int)G[k].size()-(k!=Rt))
		{
			if (dep[k]<dep[Ans]) Ans=k;
		}
	}
	for (auto u:G[k])
	{
		if (u==fa) continue;
		if (sum-v[u]==(int)G[k].size()-(k!=Rt)-1)
		{
			dfs(u,k,x,y);
		}
	}
}
void dfs2(int k,int fa)
{
	siz[k]=col[k];
	int tt=0;
	for (auto u:G[k])
	{
		if (u==fa) continue;
		dfs2(u,k);
		siz[k]+=siz[u];
		tt+=(siz[u]>0);
	}
	tt+=(tot-siz[k])>0;
	if (tt==1&&a[k]!=b[k])
	{
		if (Rt) Rt1=k;
		else Rt=k;
    }
}
void BellaKira()
{
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i];col[i]=0;
	}
	bool ans=1;
	for (int i=1;i<=n;i++)
	{
		cin>>b[i];
		ans&=(a[i]==b[i]);
	}
	for (int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	if (ans)
	{
		for (int i=1;i<=n;i++) poly().swap(G[i]);
		cout<<"Yes\n";
		cout<<"0\n";
		return;
	}
	Rt=0,Rt1=0;tot=0;
	for (int i=1;i<=n;i++)
		if (a[i]!=b[i])
		{
			col[i]=1;
			tot++;
		}
	dfs2(1,0);
	Ans=0;
	dep[0]=0;
	dfs1(Rt,0);
	dep[0]=inf;
	dfs(Rt,0,mp(0,0),mp(0,0));
	if (Ans)
	{
		cout<<"Yes\n";
		cout<<dep[Ans]<<'\n';
		poly g;
		while (Ans)
		{
			g.push_back(Ans);
			Ans=ffa[Ans];
		}
		reverse(g.begin(),g.end());
		for (auto u:g) cout<<u<<" ";
		cout<<'\n';
		for (int i=1;i<=n;i++) poly().swap(G[i]);
		return;
	}
	if (!Rt1) 
	{
		cout<<"No\n";
		for (int i=1;i<=n;i++) poly().swap(G[i]);
		return;
	}
	
	swap(Rt,Rt1);
	dep[0]=0;
	dfs1(Rt,0);
	dep[0]=inf;
	dfs(Rt,0,mp(0,0),mp(0,0));
	if (Ans)
	{
		cout<<"Yes\n";
		cout<<dep[Ans]<<'\n';
		poly g;
		while (Ans)
		{
			g.push_back(Ans);
			Ans=ffa[Ans];
		}
		reverse(g.begin(),g.end());
		for (auto u:g) cout<<u<<" ";
		cout<<'\n';
		for (int i=1;i<=n;i++) poly().swap(G[i]);
		return;
	}
	cout<<"No\n";
	for (int i=1;i<=n;i++) poly().swap(G[i]);
}
signed main()
{
	IOS;
	cin.tie(0);
	int T=1;
	cin>>T;
	while (T--)
	{
		BellaKira();
	}
}
```

---

