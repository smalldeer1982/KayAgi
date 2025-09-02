# [BalticOI 2020] 病毒 (Day2)

## 题目背景

本题数据为删减版（去掉了最后的 $6$ 组数据），完整版请去 [CF1387C](https://www.luogu.com.cn/problem/CF1387C) 提交。

## 题目描述

给定一种病毒，为了方便，我们用 $0$ 到 $G-1$ 的整数描述他的基因序列。

现在这个病毒可以进行变异，有一些变异规则，每个变异规则可以让基因序列上的某个数变成某个片段，如果用变异规则让基因序列变成了全部为 $0$ 和 $1$ 的序列，那么这个病毒就变异完成了。

病毒可以通过抗体进行检测，比如 $01011$ 就可以检测到 $0101110$，但不能检测到 $110110$。

对于从 $2$ 到 $G-1$ 中的基因，科学家想知道，是否能通过任意一组给定的抗体检测到这个基因变异形成的其他所有基因，不能的话，那么求不能检测到的基因中的最短长度。

## 说明/提示

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（11 pts）：$M=0$。
- Subtask 2（14 pts）：$N = G-2$。
- Subtask 3（25 pts）：$M=1$。
- Subtask 4（32 pts）：$\sum l \le 10$。
- Subtask 5（18 pts）：无特殊限制。

对于 $100\%$ 的数据，$G > 2$，$N \ge G-2$，$M \ge 0$。$2 \le a <G$，$k \ge 1$，$0 \le b_i<G$，$\sum k \le 100$，$l \ge 1$，$0 \le c_i \le 1$，$\sum l\le 50$。

**本题强制 $O2$ 优化。**

## 样例 #1

### 输入

```
6 6 2
2 2 0 1
3 3 2 0 0
3 2 1 3
4 4 0 3 1 2
5 2 2 1
5 1 5
2 1 1
5 0 0 1 0 0```

### 输出

```
NO 2
NO 4
NO 9
YES```

# 题解

## 作者：QuantAsk (赞：5)

题目链接: [https://www.luogu.com.cn/problem/P6698](https://www.luogu.com.cn/problem/P6698)

[更好的阅读体验（也许）](https://www.cnblogs.com/QuantAsk/p/16404011.html)

## 题目大意
有一个包含 $0\sim G-1$ 的字符集，其中有 $n$ 种变换，能够将一个字符 $a_i(a_i>1)$ 变为一串字符 $b_i$ ，当一个字符串中只剩下 $0$ 和 $1$ 时变换就结束了。

然后给出 $m$ 个匹配串 $c_i$ 。现在对于每个字符 $i\in[2,G-1]$ ，是否字符 $i$ 无论变化结束时都含有至少一个匹配串，如果不是，求一个最短的不包含任何匹配串的最终串长度。

保证每个在 $[2,G-1]$ 的字符都能进行变化，匹配串中只包含 $0/1$ 。

$\sum t_i\leq 50,\sum |b_i|\leq 100,n\leq 100,2<G\leq n+2$

## 解题思路
有匹配的问题，我们先拿所有的 $c_i$ 出来建一棵 AC 自动机 ，然后考虑怎么计算每个字符能从哪个状态跳到哪个状态。

注意我们在 AC 自动机 上走状态时不能走到包含匹配串的状态，这样我们可以将无论如何都包含匹配串视为最短不包含匹配串的长度无穷大。

那么我们考虑 dp 这个最短的长度，设 $f_{i,s,t}$ 表示字符 $i$ 经过变换后，能从状态 $s$ 走到状态 $t$ 的最短长度。

转移时我们考虑枚举一个变换 $i$ ，再枚举一个起点 $s$ ，然后设 $g_{j,x}$ 表示现在走到 $b_{i,j}$ ，在状态 $x$ 时的最短长度，那么转移时就有

$$g_{j+1,y}=min\{g_{j,x}+f_{b_{i,j},x,y}\}$$

但是会注意到 $f_{i,s,t}$ 之间的转移并不是一个单向的关系，会发现这是一个和最短路很类似的转移，我们考虑魔改一下 SPFA 。

我们先把 $0,1$ 加入队列，然后每次取出队头 $x$ ，我们把所有包含字符 $x$ 的 $b_i$ 都拿出来跑一次 $g$ ，如果这次跑出来的 $g$ 能够更新 $f_{a_i,s,t}$ ，那么我们就把 $a_i$ 入队（如果之前 $a_i$ 不在队列中）。

我们视 SPFA 的复杂度为 $O(n^2)$ ，记 AC 自动机状态数为 $k$ ，每做一次转移应该是 $O(|b_i|k^3)$ ，那么这题中 SPFA 的复杂度应该就是 $O(G\sum |b_i|k^3)$ ，实际上跑起来常数会很小，可以通过本题。

## code
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#define ll long long
using namespace std;
const ll N=105,inf=1e18;
ll G,n,m,a[N],f[N][N][N],g[N][52];
ll cnt,ch[N][2],fail[N];bool ed[N],v[N];
queue<int> q;vector<int> b[N],T[N];
void ins(ll n){
	ll x=0;
	for(ll i=1,c;i<=n;i++){
		scanf("%lld",&c);
		if(!ch[x][c])ch[x][c]=++cnt;
		x=ch[x][c];
	}
	ed[x]=1;return;
}
void getfail(){
	for(ll i=0;i<2;i++)
		if(ch[0][i])q.push(ch[0][i]);
	while(!q.empty()){
		ll x=q.front();q.pop();
		ed[x]|=ed[fail[x]];
		for(ll i=0;i<2;i++){
			if(ch[x][i]){
				fail[ch[x][i]]=ch[fail[x]][i];
				q.push(ch[x][i]);
			}
			else ch[x][i]=ch[fail[x]][i];
		}
	}
	return;
}
bool solve(int i){
	bool flag=0;
	for(ll s=0;s<=cnt;s++){
		if(ed[s])continue;
		memset(g,0x3f,sizeof(g));g[0][s]=0;
		for(ll j=0;j<b[i].size();j++){
			for(ll x=0;x<=cnt;x++){
				if(g[j][x]>=inf)continue;
				for(ll y=0;y<=cnt;y++)
					g[j+1][y]=min(g[j+1][y],g[j][x]+f[b[i][j]][x][y]);
			}
		}
		for(ll x=0;x<=cnt;x++){
			flag|=(g[b[i].size()][x]<f[a[i]][s][x]);
			f[a[i]][s][x]=min(f[a[i]][s][x],g[b[i].size()][x]);
		}
	}
	return flag;
} 
void SPFA(){
	q.push(0);q.push(1);v[0]=v[1]=1;
	while(!q.empty()){
		int x=q.front();q.pop();v[x]=0;
		for(int i=0;i<T[x].size();i++){
			int y=T[x][i];
			if(solve(y)&&!v[a[y]])
				q.push(a[y]),v[a[y]]=1;
		}
	}
	return;
}
signed main()
{
	scanf("%lld%lld%lld",&G,&n,&m);
	for(ll i=1,k;i<=n;i++){
		scanf("%lld%lld",&a[i],&k);
		for(ll j=1,x;j<=k;j++){
			scanf("%lld",&x),b[i].push_back(x);
			T[x].push_back(i);
		}
	}
	for(ll i=1,k;i<=m;i++){
		scanf("%lld",&k);
		ins(k);
	}
	getfail();ll k=0;
	memset(f,0x3f,sizeof(f));
	for(ll i=0;i<=cnt;i++){
		if(ed[i])continue;
		if(!ed[ch[i][0]])f[0][i][ch[i][0]]=1;
		if(!ed[ch[i][1]])f[1][i][ch[i][1]]=1;
	}
	SPFA();
	for(ll i=2;i<G;i++){
		ll ans=inf;
		for(ll x=0;x<=cnt;x++)
			ans=min(ans,f[i][0][x]);
		if(ans>=inf)puts("YES");
		else printf("NO %lld\n",ans);
	}
	return 0;
}
```

-----

### 题外话
最开始我是直接暴力把所有的变换的转移跑了 $G$ 次发现过了。

但是我证不出来为啥这样是对的（虽然感觉应该和 SPFA 的做法差不多），所以就又写了个 SPFA 的版本。

希望有大佬指点 /kk 。

---

## 作者：_ANIG_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/P6698)

把所有抗体建 AC 自动机。

问题转化为求最短的串，使得在 AC 自动机上跑的过程中不会到达任何一个关键点。

可以用类似 Bellman–Ford 的方式求最短路。

设 $f_{t,n,a,b}$ 表示从 AC 自动机的节点 $a$ 出发，经过基因 $n$ 形成的字符串，最终到达节点 $b$，转移轮数为 $t$，字符串长度的最小值。

转移的时候开个辅助数组 $dp_{i,k}$ 表示当前展开到第 $i$ 个数，终点为 $k$ 的最短路。

总复杂度 $O(n^5)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=55,M=105,T=60,inf=1e18;
int n,m,qs,son[N][2],mk[N],nxt[N],idx,f[M][N][N],tmp[N],dp[N];
deque<int>q;
vector<vector<int> >p[M];
void AC(){
	for(int i=0;i<2;i++)if(son[0][i])q.push_back(son[0][i]);
	while(q.size()){
		int x=q.front();
		q.pop_front();
		for(int i=0;i<2;i++){
			int c=son[x][i];
			if(c){
				nxt[c]=son[nxt[x]][i];
				mk[c]|=mk[nxt[c]];
				q.push_back(c);
			}else son[x][i]=son[nxt[x]][i];
		}
	}
}
signed main(){
	cin>>n>>m>>qs;
	for(int i=1;i<=m;i++){
		int a,k,x;
		cin>>a>>k;
		vector<int>emp;
		p[a].push_back(emp);
		while(k--){
			cin>>x;
			p[a].back().push_back(x);
		}
	}
	while(qs--){
		int k,x=0,y;
		cin>>k;
		for(int i=1;i<=k;i++){
			cin>>y;
			if(!son[x][y])son[x][y]=++idx;
			x=son[x][y];
		}
		mk[x]=1;
	}
	AC();
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=idx;i++){
		if(!mk[son[i][0]])f[0][i][son[i][0]]=1;
		if(!mk[son[i][1]])f[1][i][son[i][1]]=1;
	}
	for(int i=1;i<=T;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<=idx;k++){
			    for(int l=0;l<=idx;l++){
			    	f[j][k][l]=f[j][k][l];
			    }
			    for(auto c:p[j]){
			  		memset(dp,0x3f,sizeof(dp));
			  		dp[k]=0;
				    for(auto d:c){
					    memset(tmp,0x3f,sizeof(tmp));
				    	for(int l=0;l<=idx;l++){
				    		if(!mk[l])
				    		for(int r=0;r<=idx;r++){
				    			tmp[l]=min(tmp[l],dp[r]+f[d][r][l]);
				    		}
				    	}
				    	memcpy(dp,tmp,sizeof(dp));
				    }
				    for(int l=0;l<=idx;l++)f[j][k][l]=min(f[j][k][l],dp[l]);
				}
			}
		}
	}
	for(int i=2;i<n;i++){
		int res=inf;
		for(int j=0;j<=idx;j++){
			if(!mk[j])res=min(res,f[i][0][j]);
		}
		if(res<inf)cout<<"NO "<<res<<"\n";
		else cout<<"YES\n";
	}
}
```

---

