# Sakurako's Hobby

## 题目描述

对于一个给定的排列 $ p $，Sakurako 称整数 $ j $ 从整数 $ i $ 可达，意思是可以通过若干次操作将 $ i $ 改为 $ p_i $，最终使 $ i $ 等于 $ j $。

举个例子，如果 $ p=[3,5,6,1,2,4] $，那么 $ 4 $ 是从 $ 1 $ 可达的，因为变化过程可以是：$ i=1 \rightarrow i=p_1=3 \rightarrow i=p_3=6 \rightarrow i=p_6=4 $。这样 $ i $ 就变成了 $ 4 $，因此 $ 4 $ 是从 $ 1 $ 可达的。

在这个排列中，每个数字都有两种颜色：黑色或白色。

Sakurako 定义了一个函数 $ F(i) $，表示从 $ i $ 可达的黑色整数的总数。

她对每一个 $ 1\le i\le n $ 的 $ F(i) $ 都很感兴趣，但计算所有值太过复杂，因此她希望你能帮助她解决这个问题。

一个长度为 $ n $ 的排列是一个由 $ 1 $ 到 $ n $ 这 $ n $ 个不同整数构成的数组。例如，$ [2,3,1,5,4] $ 是一个排列，而 $ [1,2,2] $ 却不是（因为数字 $ 2 $ 出现了两次），同样地，$ [1,3,4] $ 也不是（$ n=3 $，但数组中包含 $ 4 $）。

## 样例 #1

### 输入

```
5
1
1
0
5
1 2 4 5 3
10101
5
5 4 1 3 2
10011
6
3 5 6 1 2 4
010000
6
1 2 3 4 5 6
100110```

### 输出

```
1 
0 1 1 1 1 
2 2 2 2 2 
4 1 4 4 1 4 
0 1 1 0 0 1```

# 题解

## 作者：chenxi2009 (赞：4)

# 思路

如果我们在每对可以相互转换的数字之间连一条有向边，我们会发现它们形成了若干个环，每个环都是一个强连通分量 —— 每一个分量之间的所有数字都可以互相转换。

所以我们用并查集去维护和合并环，在这个过程中额外维护一个并查集中黑色数字的数量即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,p[200001],f[200001],cnt[200001];
char s[200001];
int find(int x){
	return x == f[x] ? x : f[x] = find(f[x]);
}
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++){
			scanf("%d",&p[i]);
		}
		for(int i = 1;i <= n;i ++){
			s[i] = 0;
			while(s[i] != '0' && s[i] != '1'){
				s[i] = getchar();
			}
		}
		for(int i = 1;i <= n;i ++){
			f[i] = i; 
			cnt[i] = '1' - s[i];
		}
		for(int i = 1;i <= n;i ++){
			int u = find(i),v = find(p[i]);
			if(u == v){
				continue;
			}
			f[u] = v;
			cnt[v] += cnt[u];
		}
		for(int i = 1;i <= n;i ++){
			printf("%d ",cnt[find(i)]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：cly312 (赞：1)

可以发现可以转化的数字之间出现了环，我们遍历每一个值，记录这个值可以到达的数字，结果为过程中出现了黑色的数字。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<int>p(n);
		vector<int>F(n,0);
		vector<bool>visited(n,false);
		string s;
		for(int i=0;i<n;i++){
			cin>>p[i];
			p[i]--;
		}
		cin>>s;
		for(int i=0;i<n;i++){
			if(!visited[i]){
				vector<int>cycle;
				int cnt=0;
				int cur=i;
				while(!visited[cur]){
					visited[cur]=true;
					cycle.push_back(cur);
					if(s[cur]=='0'){
						cnt++;
					}
					cur=p[cur];
				}
				for(int index:cycle){
					F[index]=cnt;
				}
			}
		}
		for(int i=0;i<n;i++){
			cout<<F[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：Super_Cube (赞：1)

# Solution

对于每个 $i$ 向 $p_i$ 连有向边，跑强连通分量缩点，最终会得到一个森林，那么 $F(i)$ 即为缩点后 $i$ 所在强连通分量及其子树内所有黑点个数。具体实现为缩点后建反图跑拓扑排序向上累加黑点个数。

# Code

```cpp
#include<bits/stdc++.h>
std::vector<int>v[200005];
int dfn[200005],low[200005],tdx;
int scc_id[200005],scc;
std::stack<int>S;
int dp[200005];
char s[200005];
void tarjan(int p){
	dfn[p]=low[p]=++tdx;
	S.push(p);
	for(const int&i:v[p])
		if(!dfn[i])
			tarjan(i),low[p]=std::min(low[p],low[i]);
		else if(!scc_id[i])
			low[p]=std::min(low[p],dfn[i]);
	if(dfn[p]==low[p]){
		dp[++scc]=0;
		while(true){
			scc_id[S.top()]=scc;
			dp[scc]+=s[S.top()]=='0';
			if(S.top()==p)break;
			S.pop();
		}
		S.pop();
	}
}
std::unordered_set<int>g[200005];
int in[200005];
inline void topo(){
	std::queue<int>q;
	for(int i=1;i<=scc;++i)
		if(!in[i])q.push(i);
	while(!q.empty()){
		int t1=q.front();q.pop();
		for(const int&i:g[t1])
			if(dp[i]+=dp[t1],!(--in[i]))q.push(i);
	}
}
int T,n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			v[i].clear(),dfn[i]=scc_id[i]=0;
		for(int i=1,x;i<=n;++i)
			scanf("%d",&x),v[i].push_back(x);
		scanf("%s",s+1);
		tdx=scc=0;
		for(int i=1;i<=n;++i)
			if(!dfn[i])tarjan(i);
		for(int i=1;i<=scc;++i)
			g[i].clear();
		for(int i=1;i<=n;++i)
			for(const int&j:v[i])
				if(scc_id[i]!=scc_id[j])
					g[scc_id[j]].insert(scc_id[i]),++in[scc_id[i]];
		topo();
		for(int i=1;i<=n;++i)
			printf("%d%c",dp[scc_id[i]]," \n"[i==n]);
	}
	return 0;
}
```

---

## 作者：naroto2022 (赞：1)

# CF2008D 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF2008D)

### 题意

给定一个 `01` 串，和一个 $1\sim n$ 的排列 $p_i$，称两个数 $i,j$ 是互相到达的，当且仅当 $i$ 可以通过若干次 $i=p_i$ 而变成 $j$，询问对于每个 $i$，可以到达多少个在字符串中的位置为 `0` 的点。

### 思路

看到题目很容易就想到图论，把 $i$ 与 $p_i$ 连一条有向边，把题目转换成图上的问题。

首先，因为 $p_i$ 是一个 $1\sim n$ 的排列，所以一个数至多指向一个点，一个数也至多被一个点指向。

于是就可以想到，这个图一定是若干个环组成的，而且环与环之间没有边相连。

到了这里，思路就很清晰了，直接跑一遍 tarjan，每个点的答案就是在其所在的强联通分量的点的个数。

代码很板，非常好打。

### 代码

注：题目要求能到达的 `0` 的个数，但作者为了方便，所以给取反了，改成求能到达的 `1` 的个数。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
using namespace std;
const int MN=2e5+5;
ll n,a[MN],c[MN],head[MN],tot,low[MN],num[MN],dfn,f[MN],sta[MN],top,scc[MN],cnt,val[MN];
char s[MN];
bool vis[MN];
struct edge{
	ll nxt,to;
	void clear(){nxt=to=0;}
}e[MN<<2];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
void add(ll u, ll v){e[++tot].nxt=head[u];head[u]=tot;e[tot].to=v;}
void init(ll n){
	for(int i=0; i<=tot; i++) e[i].clear();
	for(int i=0; i<=n; i++) head[i]=low[i]=num[i]=sta[i]=scc[i]=val[i]=0;
	top=dfn=cnt=tot=0;
}
void tarjan(ll u){
	low[u]=num[u]=++dfn;sta[++top]=u;
	for(int i=head[u]; i; i=e[i].nxt){
		ll v=e[i].to;
		if(!num[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		} 
		else if(!scc[v]) low[u]=min(low[u],num[v]);
	}
	if(low[u]==num[u]){
		cnt++;
		while(1){
			ll v=sta[top--];
			scc[v]=cnt;val[cnt]+=c[v];
			if(u==v) break;
		}
	}
}
void solve(){
	init(n);
	n=read();
	for(ll i=1; i<=n; i++){
		a[i]=read();
		add(i,a[i]);
	}
	cin>>s;
	for(int i=0; i<n; i++) c[a[i+1]]=s[i]-'0';
	for(int i=1; i<=n; i++) c[i]=c[i]^1;
	for(int i=1; i<=n; i++) if(!num[i]) tarjan(i);
	for(int i=1; i<=n; i++) f[i]=val[scc[i]];
	for(int i=1; i<=n; i++) write(f[i]),putchar(' ');putchar('\n');
}
int main(){
	ll T=read();while(T--) solve();
	return 0;
}
```

---

## 作者：Lfz312g (赞：0)

# CF2008D Sakurako's Hobby
## 题意简析
给出一个 $1$ 到 $n$ 的排列 $p$，$p_i$ 表示第 $i$ 个点向 $p_i$ 连一条边，给出每一个点的颜色，求出每一个点能经过的黑色点的数量。
## 题目分析
首先考虑暴力 dfs 遍历，时间复杂度为 $O(n^2)$，显然超时，我们考虑在 dfs 的基础上进行优化。  
考虑这样一组数据 $[3,5,6,1,2,4]$。  
![](https://cdn.luogu.com.cn/upload/image_hosting/mwpka89z.png)  
其颜色为 $[0,1,0,0,0,0]$，可以发现同一个环内的点，所经过的黑色点个数一致。故答案为 $[4,1,4,4,1,4]$。  
我们每一次在 dfs 遍历中，记录下每一个点所能达到的点，和该点能经过的黑色点数，之后遇到同一环内的点，直接输出即可。  
最劣时间复杂度仍为 $O(n^2)$，实测跑得飞快，可以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005];
int ansn[200005];
char v[200005];
int vis[200005];
int ans=0;
void dfs(int x,int s)
{
	if (vis[x]) return;
	vis[x]=s;
	ans+=('1'-v[x]);
	dfs(a[x],s);
}
void solve()
{
	memset(vis,0,sizeof(vis));
	int n;
	cin>>n;
	for (int i=1;i<=n;i+=1) cin>>a[i];
	for (int i=1;i<=n;i++) cin>>v[i];
	for (int i=1;i<=n;i++)
	{
		ans=0;
		if (vis[i])
		{
			cout<<ansn[vis[i]]<<" ";
			continue;
		}
		dfs(i,i);
		ansn[i]=ans;
		cout<<ans<<" ";
	}
	putchar('\n');
}
int main()
{
	int t;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

---

