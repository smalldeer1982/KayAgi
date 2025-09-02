# [POI 2017 R3] 披萨配送员 Pizza delivery

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5061)。

## 题目描述

**题目译自 [XXIV Olimpiada Informatyczna — III etap](https://sio2.mimuw.edu.pl/c/oi24-3/dashboard/) [Dostawca pizzy](https://szkopul.edu.pl/problemset/problem/q_HBwDECevrQ2iQh1wT6ssx2/statement/)**

拜托城是一座风景如画的城市，拥有 $n$ 个路口，通过 $n-1$ 条双向道路相连。每路口旁有一户人家，其中之一是 Bajtazar 的披萨店。拜托城的居民酷爱披萨，每日清晨，Bajtazar 烘焙 $n-1$ 张披萨，挨家挨户送达（除自家外）。

为避免披萨冷却，Bajtazar 为配送车配备了尖端加热器，但其耗能极高，他希望尽量缩短使用时间。他的策略是：装载若干披萨，开启加热器，送至部分住户，送完最后一张后关闭加热器，返回披萨店。他最多愿意进行 $k$ 次配送，想知道送完所有披萨所需的最短加热器运行时间。

加热器在停留期间（Bajtazar 送披萨上门时）的运行时间可忽略。

## 说明/提示

**样例 1 解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/5ybl7frg.png)

Bajtazar 进行三次配送：$1 \rightarrow 2 \rightarrow 4 \rightarrow 2 \rightarrow 5 \rightsquigarrow 1$（加热器运行 $15$ 分钟），$1 \rightarrow 2 \rightarrow 3 \rightsquigarrow 1$（$16$ 分钟），$1 \rightarrow 6 \rightarrow 1 \rightarrow 7 \rightsquigarrow 1$（$3$ 分钟）。

**附加样例**

1. $n=15, k=3$，小型完全二叉树，通往叶子的道路通行时间 $6$ 分钟，其余道路 $1$ 分钟。
2. $n=2000, k=100$，披萨店直达所有路口，大型随机通行时间。
3. $n=50000, k=1000$，披萨店直达两个路口，其中之一可达其余所有路口，所有通行时间为 $1$。

所有测试数据满足 $n \geq 2, k \geq 1, 1 \leq c_i \leq 1000000$。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n, k \leq 10$           | $12$ |
| $2$    | $n, k \leq 2000$         | $24$ |
| $3$    | $n, k \leq 100000$ 且 $n \cdot k \leq 4000000$ | $28$ |
| $4$    | $n, k \leq 100000$       | $36$ |

## 样例 #1

### 输入

```
7 3
1 2 5
2 3 11
2 4 2
5 2 6
1 6 1
7 1 1```

### 输出

```
34```

# 题解

## 作者：qzmoot (赞：6)

# 题解：P12753 [POI 2017 R3] 披萨配送员 Pizza delivery
## 题目大意
不难发现这是让我们来进行一颗树的遍历，然后可以有 $k$ 次机会可以进行瞬移操作。问最少遍历所有点的最小代价需要多少。
## 分析
不难发现我们如果没有瞬移操作，那么显然总代价为路径长度总数的两倍。

手玩后发现，我们在叶子结点瞬移最优（显然）。在叶子结点瞬移会省去该结点 $u$ 到他的祖先结点 $v$（该结点 $v$ 有不止一个儿子）的距离，同时多走一次祖先结点到根结点的路径。

那么，我们对每个结点作为被找到的祖先结点进行操作即可。将该结点最长链的长度省掉一定是最优的。

那么对于每一个节点，我们将他产生的贡献存下后进行排序或用数据结构维护，取出前 $k$ 大的后在全局答案中减掉就是最小代价。

---

## 作者：2147483647str (赞：3)

注意到一个关键性质，快递员只会在叶子处停留并返回，并且他在遍历完一棵子树后才会遍历下一棵子树。

先不考虑 $k$ 的限制，
由此可设计一个树形 dp 状态。

设 $dp_{x,0/1}$ 表示送完一个子树，回/不回根节点的最短用时，则答案即为 $dp_{1,1}$。

转移就是考虑把两条路径拼起来，具体详见代码。

现在考虑 $k$ 的限制，发现套一个 wqs 二分便可轻松解决。

时间复杂度 $O(n \log V)$

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
typedef pair<ll,int> pii;
pii operator+(pii a,pii b){
	return pii{a.first+b.first,a.second+b.second};
}
int n,k;
int h[N],e[N<<1],ne[N<<1],w[N<<1],tot,deg[N];
void add(int a,int b,int c){
	e[++tot]=b,ne[tot]=h[a],h[a]=tot,w[tot]=c;
}
pii dp[N][2];
int wqs_val;
ll dist[N];
void dfs(int x,int fa){
	for(int i=h[x];i;i=ne[i])if(e[i]!=fa){
		dist[e[i]]=dist[x]+w[i];
		dfs(e[i],x);
	}
}
void solve(int x,int fa){
	dp[x][0]={dist[x]+wqs_val,1};
	if(x!=1&&deg[x]==1){
		dp[x][1]={dist[x]+wqs_val,1};
		return;
	}
	dp[x][1]={0x3f3f3f3f3f3f3f3f,0};
	for(int i=h[x];i;i=ne[i])if(e[i]!=fa){
		solve(e[i],x);
		pii f0=dp[x][0],f1=dp[x][1];
		dp[x][0]=min(min(f0+dp[e[i]][1],f1+dp[e[i]][0]+pii{w[i],0}),f0+dp[e[i]][0]+pii{w[i]-dist[x]-wqs_val,-1});
		dp[x][1]=min(min(f1+dp[e[i]][1],f0+dp[e[i]][1]+pii{-dist[x]-wqs_val,-1}),f1+dp[e[i]][0]+pii{w[i]-dist[x]-wqs_val,-1});
	}
}
bool check(ll mid){
	wqs_val=mid;
	solve(1,0);
	return dp[1][1].second<=k;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1,a,b,c;i<n;i++)scanf("%d%d%d",&a,&b,&c),add(a,b,c),add(b,a,c),deg[a]++,deg[b]++;
	dfs(1,0);
	solve(1,0);
	if(dp[1][1].second<=k){
		printf("%lld\n",dp[1][1].first);
		return 0;
	}ll l=0,r=1e9,ans=-1;
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}check(ans);
	printf("%lld\n",dp[1][1].first-ans*k);
	return 0;
}
```

---

