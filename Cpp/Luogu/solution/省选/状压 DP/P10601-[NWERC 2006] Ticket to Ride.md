# [NWERC 2006] Ticket to Ride

## 题目描述

给一张地图，地图上有一些城市，城市之间可能有线路连通，我们用一个无向图来表示以简化概念，每条边有个权值，表示选择这条边需要花费的费用。给定 $4$ 对顶点（可能重复），求一个权值最小的边集，使得任意一对顶点可以由选出的边集中的边相连。

## 说明/提示

数据保证，$1\leq n\leq 30$，$0\leq m\leq 1000$，$1\leq w\leq 10000$。

## 样例 #1

### 输入

```
10 15
stockholm
amsterdam
london
berlin
copenhagen
oslo
helsinki
dublin
reykjavik
brussels
oslo stockholm 415
stockholm helsinki 396
oslo london 1153
oslo copenhagen 485
stockholm copenhagen 522
copenhagen berlin 354
copenhagen amsterdam 622
helsinki berlin 1107
london amsterdam 356
berlin amsterdam 575
london dublin 463
reykjavik dublin 1498
reykjavik oslo 1748
london brussels 318
brussels amsterdam 173
stockholm amsterdam
oslo london
reykjavik dublin
brussels helsinki```

### 输出

```
3907```

## 样例 #2

### 输入

```
2 1
first
second
first second 10
first first
first first
second first
first first```

### 输出

```
10```

# 题解

## 作者：cff_0102 (赞：2)

如果本题要求那八个城市全部互相连通，那么就是最小斯坦纳树的模板了，但是题目中只需要四对城市两两之间连通即可。

可以先跑一遍[最小斯坦纳树](/problem/P6192)，此时就能得到所有含有顶点 $i$ 的包含 $S$ 中的关键点的树的权值之和的最小值，即 $dp_{i,S}$，其中也有只包含一部分关键点的树。

接着就可以再进行一次状压 dp，设 $ans_{S}$ 表示包含 $S$ 中的关键**点对**的图（可以不连通）的最小权值和，其中 $0\le S\le 15$。那么转移的时候，就枚举 $S$ 的子集 $s$，并更新 $ans_S$ 的值，如果 $ans_s+ans_{S\oplus s}<ans_S$，则将 $ans_S$ 赋值为 $ans_s+ans_{S\oplus s}$。$ans_S$ 的初始化也不难，需要找到对应的 $dp_{i,S'}$。其中 $i$ 需要找到 $S$ 的一个点并对应找到它在 $n$ 个点中的编号，而 $S'$ 则复杂一些，需要找到 $S$ 中所有点对，再把一个点对拆成两个点，具体方式可以参考代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
const int N=105,K=10;
int dp[N][1<<K];
bool vis[N];
vector<PII>e[N];
map<string,int>mp;
int n;
void dij(int S){
	memset(vis,0,sizeof(vis));
	priority_queue<PII,vector<PII>,greater<PII>>q;
	for(int i=1;i<=n;i++)if(dp[i][S]!=0x3f3f3f3f)q.push({dp[i][S],i});
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(PII t:e[x]){
			int y=t.first,w=t.second;
			if(dp[y][S]>dp[x][S]+w){
				dp[y][S]=dp[x][S]+w;
				q.push({dp[y][S],y});
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int m;cin>>n>>m;int k=8;
	for(int i=1;i<=n;i++){
		string s;cin>>s;
		mp[s]=i;
	}
	for(int i=1;i<=m;i++){
		string u,v;int w;cin>>u>>v>>w;
		e[mp[u]].push_back({mp[v],w});
		e[mp[v]].push_back({mp[u],w});
	}
	string s1,s2,s3,s4,s5,s6,s7,s8;cin>>s1>>s2>>s3>>s4>>s5>>s6>>s7>>s8;
	int p[9]={0,mp[s1],mp[s2],mp[s3],mp[s4],mp[s5],mp[s6],mp[s7],mp[s8]};
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=k;i++)dp[p[i]][1<<i-1]=0;
	for(int S=0;S<(1<<k);S++){
		for(int s=S;s;s=((s-1)&S)){
			for(int i=1;i<=n;i++)dp[i][S]=min(dp[i][S],dp[i][s]+dp[i][S^s]);
		}
		dij(S);
	}
	int ans[16]={0};
	//ans[S] 表示只让 S 中的这几对点互相连通的最小花费
	//转移时枚举子集 s，ans[S]=min(ans[S],ans[s]+ans[S^s])
	for(int S=1;S<16;S++){
		int i=__lg(S&(-S))+1;
		int x=0;for(int j=0;j<4;j++)if(S&(1<<j))x|=((1<<j*2)|(1<<j*2+1));
		ans[S]=dp[p[i*2]][x];
		for(int s=S;s;s=((s-1)&S)){
			ans[S]=min(ans[S],ans[s]+ans[S^s]);
		}
	}
	cout<<ans[15];
	return 0;
}
```

---

