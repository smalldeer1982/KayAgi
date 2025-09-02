# [GCJ Farewell Round #2] Railroad Maintenance

## 题目描述

你负责一个铁路网络的维护工作。该网络由 $\mathbf{N}$ 个车站和 $\mathbf{L}$ 条铁路线组成。每条铁路线双向服务于一个固定的车站列表（列车在列表的第一个和最后一个车站调头）。在一个车站可以从一条线路换乘到另一条线路，这意味着从车站 $a$ 到车站 $b$ 的行程是可行的，如果存在一个铁路线列表，其中第一条线路服务于车站 $a$，最后一条线路服务于车站 $b$，并且对于列表中任意两条相邻的铁路线，至少存在一个车站同时被这两条线路服务。

最简单的维护方式是每次关闭整条铁路线。然而，有些铁路线可能是**关键线路**。一条铁路线是关键线路，如果移除它后会导致至少一对车站之间的行程变得不可能。

给定现有的铁路线列表，计算其中有多少条是关键线路。

## 说明/提示

**样例解释**

在样例 #1 中，第一条铁路线是关键线路，因为它是唯一服务于车站 $2$ 的线路。由于关闭其他任何线路都不会导致至少一对车站之间的行程变得不可能，因此它们不是关键线路。

![](https://cdn.luogu.com.cn/upload/image_hosting/hstw804z.png)

在样例 #2 中，没有关键线路。

![](https://cdn.luogu.com.cn/upload/image_hosting/iodjuwf1.png)

样例 #3 与样例 #2 类似，但缺少最后一条铁路线。这使得剩余的所有铁路线都成为关键线路。

在样例 #4 中，最后一条铁路线是关键线路，因为没有它就无法从车站 $1$ 到达车站 $4$。与样例 #1 类似，由于这条铁路线已经连接了所有车站，其他线路都不是关键线路。

![](https://cdn.luogu.com.cn/upload/image_hosting/xcha3btp.png)

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- 对所有 $i$，$2 \leq \mathbf{K}_i \leq \mathbf{N}$。
- 对所有 $i, j$，$1 \leq \mathbf{S}_{i,j} \leq \mathbf{N}$。
- 对所有 $i, j, j'$ 且 $j \neq j'$，$\mathbf{S}_{i,j} \neq \mathbf{S}_{i,j'}$（每条铁路线中每个车站最多出现一次）。

根据上述定义，当没有铁路线被关闭时，所有车站对之间的行程都是可行的。

**测试集 1（9 分，可见判定）**
- $2 \leq \mathbf{N} \leq 100$。
- $1 \leq \mathbf{L} \leq 100$。
- $\mathbf{K}_1 + \mathbf{K}_2 + \cdots + \mathbf{K}_\mathbf{L} \leq 200$。

**测试集 2（20 分，可见判定）**
- $2 \leq \mathbf{N} \leq 10^5$。
- $1 \leq \mathbf{L} \leq 10^5$。
- $\mathbf{K}_1 + \mathbf{K}_2 + \cdots + \mathbf{K}_\mathbf{L} \leq 2 \times 10^5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 3
3
1 2 3
2
1 4
3
4 1 3
4 4
2
1 2
2
3 4
2
3 2
2
4 1
4 3
2
1 2
2
3 4
2
3 2
4 3
2
1 2
2
3 4
4
4 1 2 3```

### 输出

```
Case #1: 1
Case #2: 0
Case #3: 3
Case #4: 1```

# 题解

## 作者：yinpeichu2021 (赞：0)

## 思路

这是一道有意思的图论建模。

我们发现这个“关键线路”的定义和割点、割边的定义有相似之处，但是这题会删除一整条路径，好像没办法直接求。

我们希望将一整条路径看成一个整体，于是我们新建出 $L$ 个虚点表示这些路径，然后将其与路径上的点连边。这样做点之间的连通性并不会发生改变，但是我们将一整条路径整合成了一个点，这样就可以直接 tarjan 求割点，统计作为虚点的割点就可以了。

## Code

```cpp
#include<bits/stdc++.h>
#define eps 1e-6
#define MOD 998244353
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define MAXN 200005
int n,L;
vector<int>v[MAXN];
int dfn[MAXN],low[MAXN],num;
bool cut[MAXN];
void tarjan(int x){
	dfn[x]=low[x]=++num;
	int flag=0;
	for(int y:v[x])
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]){
				flag++;
				if(x!=1||flag>1)cut[x]=1;
			}
		}else low[x]=min(low[x],dfn[y]);
}
void solve(){
	cin>>n>>L;
	num=0;
	for(int i=1;i<=n+L;i++)v[i].clear(),dfn[i]=low[i]=cut[i]=0;
	for(int i=1;i<=L;i++){
		int k,x;cin>>k;
		while(k--){
			cin>>x;
			v[n+i].push_back(x);// 建边
			v[x].push_back(n+i);// n+i 表示第 i 条路径
		}
	}
	tarjan(1);// 题目保证联通，只需要跑一遍
	int ans=0;
	for(int i=n+1;i<=n+L;i++)ans+=cut[i];
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T,_=0;cin>>T;
	while(T--)cout<<"Case #"<<++_<<": ",solve();
	
	return 0;
}
```

---

