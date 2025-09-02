# [ABC035D] トレジャーハント

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc035/tasks/abc035_d

高橋君が住む国には $ N $ 箇所の町と町同士をつなぐ一方通行の道が $ M $ 本あり、それぞれの町には $ 1 $ から $ N $ の番号が割りふられています。 $ i $ 番目の道は $ a_i $ 番の町から $ b_i $ 番の町へ移動することが可能であり、移動に $ c_i $ 分だけかかります。

所持金が $ 0 $ 円の高橋君は $ T $ 分間のトレジャーハントに出かけることにしました。高橋君は開始 $ 0 $ 分の時点で $ 1 $ 番の町にいます。また、開始から $ T $ 分の時点にも $ 1 $ 番の町にいなくてはなりません。高橋君が $ i $ 番の町に $ 1 $ 分間滞在すると、 $ A_i $ 円が高橋君の所持金に加算されます。

$ T $ 分間のトレジャーハントによって高橋君の所持金は最大いくらになるか求めてください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1≦N≦200 $ を満たすデータセットに正解した場合 $ 50 $ 点が与えられる。
- 追加制約のないデータセットに正解した場合は、追加で $ 50 $ 点が与えられ、合計 $ 100 $ 点が得られる。

### Sample Explanation 1

\- 開始から $ 0 $ 分の時点から $ 2 $ 分かけて町 $ 1 $ から町 $ 2 $ に移動します。 - 開始から $ 2 $ 分の時点から $ 2 $ 分間、町 $ 2 $ に滞在します。所持金は $ 6 $ 円になります。 - 開始から $ 4 $ 分の時点から $ 1 $ 分かけて町 $ 2 $ から町 $ 1 $ に移動します。 - 開始から $ 5 $ 分の時点で町 $ 1 $ にいます。トレジャーハントが終了します。 - このケースは部分点の制約を満たします。

### Sample Explanation 2

\- 開始 $ 0 $ 分の時点から $ 3 $ 分間、町 $ 1 $ に滞在するのが最適であり、所持金を $ 3 $ 円にすることができます。 - このケースは部分点の制約を満たします。

### Sample Explanation 3

\- このケースは部分点の制約を満たします。

## 样例 #1

### 输入

```
2 2 5
1 3
1 2 2
2 1 1```

### 输出

```
6```

## 样例 #2

### 输入

```
2 2 3
1 3
1 2 2
2 1 1```

### 输出

```
3```

## 样例 #3

### 输入

```
8 15 120
1 2 6 16 1 3 11 9
1 8 1
7 3 14
8 2 13
3 5 4
5 7 5
6 4 1
6 8 17
7 8 5
1 4 2
4 7 1
6 1 3
3 1 10
2 6 5
2 4 12
5 1 30```

### 输出

```
1488```

# 题解

## 作者：Erica_N_Contina (赞：0)

# [ABC035D] トレジャーハント



## 思路

一开始我们想到 dp，但发现 $T$ 值过大，无法把 $T$ 作为一个维度。

我们考虑以下事实：对于一条可以从 $1$ 号点出发回到 $1$ 号点的路径，我们如果只在路径数权值最大的点停留，那么能获得的钱数最大。

**最初的想法**

所以我们只需要考虑经过点 $1$ 的环有哪些，计算出每个环的总路径长度 $l_i$，统计每个环上权值最大的点的权值 $v_i$，选择 $v_i\times (T-l_i)$ 最大的那个环即可。



我们考虑以 $1$ 号点为起点，将 $1$ 号点克隆为 $n+1$ 号点作为终点（即假设 $1$ 号点与点 $p_i$ 有一条 $p_i→1$ 的边，那么我们就创建一条 $p_i→n+1$ 的边）。

对于每一次，我们从 $1→n+1$ 跑一次最短路，记录路径上权值最大的点的权值 $v$ 和路径长度 $l$，从而计算出 $v\times (T-l)$ 并且尝试更新答案。然后我们删掉这条路径。

——欸，删掉这条路径貌似不太好写，因为这条路径上的某些边同样也是其他路径上的边！所以这个方法貌似不可取。

**最终的想法**

我们换一个角度思考。既然不好考虑经过点 $1$ 的环有哪些，那么我们就从点出发——我们枚举点 $i$，如果我们发现从 $1→i$ 有路径，从 $i→1$ 也有路径，那么不就相当于有一个经过了点i的环吗？

既然我们要枚举每一个点 $i$，那么我们就假定这个点是路径上权值最大的点。那么现在我们点的权值已经确定了，我们只要考虑路径长度即可——我们要让路径长度尽可能的小！

所以我们需要找到从 $1→i$ 的最短路和 $i→1$ 的最短路。

**解题**

我们跑两边最短路，第一次求出 $1$ 到其他点的最短路，第二次求出其他点到 $1$ 的最短路（这里我们需要构建反向边，然后以 $1$ 号点为起点跑最短路）。最后我们枚举点，更新答案。

注意图中有环。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100005;
const int INF=1e9;

int a[N];
int n,m,T;
int vis[N],h[N];
int dis[N],disr[N],u,w,v,ans;
struct node {
	int nxt,dis;
};

vector<node> e[N],r[N];

priority_queue<pair<int,int>> pq;

void add(int a,int b,int dis) {
	e[a].push_back((node){b,dis});
}

void add2(int a,int b,int dis) {//建立反向边 
	r[a].push_back((node){b,dis});
}


void djstr(int rt) {
	pq.push(make_pair(0,rt));
	int u=rt;	//先从起点开始查
	for(int i=1; i<=n; i++)dis[i]=INF;	//初始化边权

	dis[rt]=0;
	vis[rt]=1;
	
	while(pq.size()) {	//搜完全图
		
		u=pq.top().second;
		vis[u]=1;
		pq.pop();
		for(int i=0;i<e[u].size();i++){
			int v=e[u][i].nxt,w=e[u][i].dis;
			if(!vis[v]&&dis[u]+w<dis[v]){
				dis[v]=dis[u]+w;	//更新
				pq.push(make_pair(-dis[v],v));
			}
		}
	}
}



void djstr2(int rt) {
	memset(vis,0,sizeof vis);
	
	pq.push(make_pair(0,rt));
	int u=rt;	//先从起点开始查
	for(int i=1; i<=n; i++)disr[i]=INF;	//初始化边权

	disr[rt]=0;
	vis[rt]=1;
	
	while(pq.size()) {	//搜完全图
		
		u=pq.top().second;
		vis[u]=1;
		pq.pop();
		for(int i=0;i<r[u].size();i++){
			int v=r[u][i].nxt,w=r[u][i].dis;
			if(!vis[v]&&disr[u]+w<disr[v]){
				disr[v]=disr[u]+w;	//更新
				pq.push(make_pair(-disr[v],v));
			}
		}
	}
}

signed main(){
    
    scanf("%lld%lld%lld",&n,&m,&T);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
        add2(v,u,w);
    }
    
    djstr(1);
    djstr2(1);
    
    ans=0;
    
    for(int i=1;i<=n;i++){
    	if(dis[i]==INF||disr[i]==INF)continue;
    	ans=max(ans,a[i]*(T-dis[i]-disr[i]));
	}
	cout<<ans<<endl;
	
	return 0;
}

```


注意有一种情况是一直在点 $1$ 不动！（样例 $2$）



---

