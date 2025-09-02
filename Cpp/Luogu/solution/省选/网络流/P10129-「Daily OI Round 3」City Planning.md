# 「Daily OI Round 3」City Planning

## 题目背景

只要不失去你的崇高，整个世界都会为你敞开。

## 题目描述

Provence-Alpes-Côte d'Azur 的管理者们遇上大麻烦了！他们邀请你来解决城市规划的问题。

这群管理者一共有 $t$ 人，并且这个地区一共有 $n$ 个城镇，第 $i$ 个城镇内部又有 $k_i$ 个村庄，通过 $p_i$ 条道路连接，第 $j$ 条道路双向连接第 $i$ 个城镇中的第 $u_{i,j}$ 和 $v_{i,j}$ 两个村庄，管理道路的人是第 $w_{i,j}$ 个，客流量是 $z_{i,j}$。

为了管理组内部的团结，保证每个人在同一个城镇最多管理 $1$ 条道路。

现在这些城镇中的村庄和村庄之间的道路都遭到了损坏，管理者们急于恢复这些城镇内的交通。这些城镇互相之间有 $m$ 条高铁，每条高铁连接了 $u,v$ 两个城镇，并且当初为了设计的优美，这 $n$ 个城镇和 $m$ 条高铁构成了一个**二分图**。

对于每个城镇 $i$，你都需要帮助管理组选择一个参数 $c_i(1 \le c_i \le k_i)$，修复一些村庄，编号在 $1 \sim c_i$ 之间的村庄都会被修复，如果道路的两端的村庄都修复了，那么这条道路就会自动修复。因此第 $i$ 个城镇中会产生 $b_{i,c_i}$ 的花费。

对于管理者 $i$ 来说，如果存在两条他在不同城镇管理的道路都没有被修复，并且这两条道路所属的城镇有高铁**直接连接**，你需要支付这两条道路的人流量的乘积来弥补损失，这样管理者 $i$ 才会高兴。（对于**任意**两条满足上述条件的道路你都需要弥补损失，而不是对于每个管理者只需要弥补一对道路的损失）

为了让管理组的成员都高兴并且给出的方案符合题目的要求（即 $1 \le c_i \le k_i$），你需要提前计算好自己至少需要支付多少钱以应对这一群管理者们的刁难。



## 说明/提示

#### 【样例解释 #1】

我们可以选择 $c_1=1,c_2=2$，那么花费就是 $b_{1,c_1}+b_{2,c_2}=3+6=9$，而没有一个管理员你需要讨好。

#### 【样例解释 #2】

我们可以选择 $c_1=1,c_2=1,c_3=2$，那么花费就是 $b_{1,c_1}+b_{2,c_2}+b_{3,c_3}=1+1=2$，但是管理员 $2$ 在城镇 $1$ 中管理的道路 $2 \to 3$ 不可能被修复，在城镇 $2$ 中管理的道路 $1 \to 2$ 不可能被修复，你就需要花费 $2 \times 1 = 2$ 的代价讨好管理员 $2$，总的代价就是 $4$。

你并不需要讨好管理员 $1$，哪怕他在城镇 $1$ 和 $3$ 中分别有一条道路不可能被修复，因为城镇 $1$ 和 $3$ 没有高铁相连，所以你不需要为此支付额外的资金。

#### 【数据范围】

对于全部数据保证：$1 \le n \le 50$，$1 \le k_i \le 100$，$0 \le p_i \le t$，$0 \le m \le 500$，$1 \le t \le 50$，$1 \le x,y \le n$，$x \ne y$，$0 \le b_{i,j} \le 10^9$，$1 \le u_{i,j},v_{i,j} \le k_i$，$1 \le w_{i,j} \le t$，$1 \le z_{i,j} \le 10^4$。

$n$ 个城镇和 $m$ 条高铁构成的图是一个二分图，每个管理员在同一个村庄管理的道路数量不超过 $1$。

**可能有连接同一对城镇的不同的高铁，不会出现自己连向自己的高铁。但城镇中的村庄可能会有自己连向自己的道路，也可能出现连接同一对村庄的不同的道路。**

## 样例 #1

### 输入

```
2 2 3
2 1
2 1
1 3
3
1 1 2 3
1 1 1 1
1 1 3 3
2 0
7 6```

### 输出

```
9```

## 样例 #2

### 输入

```
3 1 3
1 2
3 2
1 2 3
1 2 1 3
2 3 2 2
2 2
1 100
1 1 1 3
1 2 2 1
5 1
5 0 5 5 5
4 5 1 3```

### 输出

```
4```

## 样例 #3

### 输入

```
5 6 5
4 3
3 5
1 2
2 1
3 4
3 5
2 0
37 44
4 2
33 2 43 49
3 1 3 6
3 4 4 6
6 4
4 23 0 9 35 22
3 4 2 7
3 4 5 3
2 1 3 2
4 4 4 10
3 2
14 41 35
2 2 4 1
3 3 2 5
3 5
27 39 9
3 3 2 1
3 2 3 3
2 1 1 5
2 1 5 3
1 2 4 8```

### 输出

```
71```

# 题解

## 作者：masonpop (赞：2)

官方题解太神了，我就补几张图吧。

先不考虑那个补偿费，那么就是一个贪心。转换成网络流模型可以这样：对于左部点 $i$，连出一条长为 $k_i$ 的链，边权分别为 $c_{i,1},c_{i,2},\cdots,c_{i,k_i}$。对于右部点同理，只不过边权反过来，为什么反过来之后会解释。对于每个链尾点，向汇点连边权 $\infty$ 边。这种情况下，最小割就是答案。

![](https://cdn.luogu.com.cn/upload/image_hosting/t4k31p7p.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

考虑什么情况下需要补偿费。对于两条对应边 $(x_i,y_i)$ 和 $(x_j,y_j)$，设链上断掉的边是第 $w_i,w_j$ 条。如果 $\max(x_i,y_i)>w_i$ 且 $\max(x_j,y_j)>w_j$，那么就需要支付费用。发现这个过程非常像切糕里面的额外限制。我们直接把这 $y_j$ 和 $x_i$ 连 $z_i\times z_j$ 的边。如果不懂可以看图：

![](https://cdn.luogu.com.cn/upload/image_hosting/llj92q08.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)


这样的话，为了使这条路径不连通，只有三种途径：$w_j$ 很大，$w_i$ 很大，或者断掉绿边并付出 $z_i\times z_j$ 的代价。正好符合题意。

建出图后跑最小割即可。[代码](https://www.luogu.com.cn/paste/l7uyixm0)。

---

## 作者：Acoipp (赞：1)

下面是出题人题解：

首先考虑如果管理员 $p$ 在第 $i$ 个城镇管理了 $x_i \to y_i$ 的道路，在第 $j$ 个城镇管理了 $x_j \to y_j$ 的道路，并且城镇 $i$ 和城镇 $j$ 有高铁相连。

如果我们选择的 $c_i < \max(x_i,y_i)$ 并且 $c_j < \max(x_j,y_j)$，那么就要支付 $z_i \times z_j$ 的花费。

并且我们发现，根据题目给出的限制 $i$ 和 $j$ 这两个城镇一定分别位于二分图的左右部。

于是我们可以以此建立网络流模型，求最小割。

首先，对于所有二分图左部的城镇，从 $s$ 引出来一条链，链上的第 $i-1$ 个节点到第 $i$ 个节点的流量为这条链所代表的城镇的 $c_i$，这条链的最后一个节点向汇点 $t$ 连接流量为 $\text{inf}$ 的边。

可以发现链的第 $0$ 个节点就是源点。

对于所有二分图右部的城镇，链上的第 $i+1$ 个节点到第 $i$ 个节点的流量为这条链所代表的城镇的 $c_i$，源点 $s$ 向这条链的第 $n$ 个节点连接流量为 $c_n$ 的边。（$n$ 是村庄的数量）

可以发现这种链的第 $0$ 个节点就是汇点，这条链的第 $1$ 个节点向汇点连接流量为 $\text{inf}$ 的边。

那么如果先不考虑“讨好”的花费，这样求出来的最小割恰好就是每个城镇选择一个 $c_i$ 的最小花费。

接下来我们考虑“讨好”的花费，如果第 $i$ 条链断开了第 $k \to k+1$ 的边，第 $j$ 条链断开了第 $l+1 \to l$ 的边，代表 $c_i=k+1,c_j=l$，根据上面说的，如果 $c_i < \max(x_i,y_i)$ 并且 $c_j < \max(x_j,y_j)$，那么花费 $z_i \times z_j$。

于是我们可以从右部节点所代表的链的第 $\max(x_j,y_j)$ 个点向左部节点所代表的链的第 $\max(x_i,y_i)-1$ 个点连接流量为 $z_i \times z_j$ 的边。

这样的话如果 $c_i \ge \max(x_i,y_i)$ 或者 $c_j \ge \max(x_j,y_j)$，就不需要花费 $z_i \times z_j$ 了，否则这两个点一定仍然连通源点和汇点就一定需要切断这条权值为 $z_i \times z_j$ 的边，由最小割的定义，这样的做法是正确的。

根据这道题 [P3227 切糕](https://www.luogu.com.cn/problem/P3227) 的证明方法我们可以证明不会存在一条链被割断了两次及以上（有多个 $c_i$）。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 105
#define M 2000005 
using namespace std;
struct node{ll city,village,people;};
vector<ll> op[N];
vector<node> lead[N]; 
ll n,m,s,t,people,i,j,x,y,u,v,w,z,ans,temp,vis[N],id[N][N],k[N],p[N],calc[N][N],maps[N][N];
ll la[M],ne[M],to[M],val[M],dis[M],cur[M],tot=1,sum[M],inf;
inline void merge(ll x,ll y,ll z){
	tot++,ne[tot] = la[x],la[x] = tot,to[tot] = y,val[tot] = z;
	tot++,ne[tot] = la[y],la[y] = tot,to[tot] = x,val[tot] = 0;
}
ll dfs(ll x,ll step){
	if(x==t) return step;
	ll used = 0;
	for(ll i=cur[x];i;i=ne[i]){
		cur[x] = i;
		if(dis[to[i]]+1==dis[x]&&val[i]>0){
			ll temp = dfs(to[i],min(val[i],step-used));
			val[i] -= temp,val[i^1] += temp,used += temp;
			if(used==step) return used;
		}
	}
	if(--sum[dis[x]]==0) dis[s] = inf;
	sum[++dis[x]]++;
	return used;
}
void dfs(ll x){
	for(ll i=0;i<op[x].size();i++){
		if(vis[op[x][i]]){
			assert(vis[op[x][i]]==-vis[x]);
			continue;
		}
		vis[op[x][i]] = -vis[x];
		dfs(op[x][i]);
	}
}
char stin[15],stout[15];
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>people;
	assert(1<=n&&n<=50),assert(0<=m&&m<=500),assert(1<=people&&people<=50);
	s=0,t=1;
	while(m--){
		cin>>x>>y;
		assert(1<=x&&x<=n&&1<=y&&y<=n);
		op[x].push_back(y),op[y].push_back(x);
		maps[x][y] = maps[y][x] = 1;
	}
	for(i=1;i<=n;i++) if(!vis[i]) vis[i]=1,dfs(i);
	for(i=1;i<=n;i++){
		cin>>k[i]>>p[i];
		assert(1<=k[i]&&k[i]<=100),assert(0<=p[i]&&p[i]<=people);
		for(j=1;j<=k[i];j++) id[i][j]=t++,cin>>calc[i][j],assert(0<=calc[i][j]&&calc[i][j]<=1000000000);
		if(vis[i]==1) for(j=1;j<=k[i];j++) merge(id[i][j-1],id[i][j],calc[i][j]);
		else for(j=1;j<=k[i];j++) merge(id[i][j+1],id[i][j],calc[i][j]);
		for(j=1;j<=p[i];j++){
			cin>>u>>v>>w>>z;
			assert(1<=u&&u<=k[i]),assert(1<=v&&v<=k[i]),assert(1<=w&&w<=people),assert(1<=z&&z<=10000);
			lead[w].push_back((node){i,max(u,v),z});
		} 
	}
	for(i=1;i<=n;i++){
		if(vis[i]==1) merge(id[i][k[i]],t,1e18);
		else merge(id[i][1],t,1e18);
	}
	for(i=1;i<=people;i++){
		for(ll l1=0;l1<lead[i].size();l1++){
			for(ll l2=l1+1;l2<lead[i].size();l2++){
				assert(lead[i][l1].city!=lead[i][l2].city);
				if(!maps[lead[i][l1].city][lead[i][l2].city]) continue;
				node a = lead[i][l1],b = lead[i][l2];
				if(vis[a.city]==-1) swap(a,b);
				if(a.village==1||b.village==1) continue;
				merge(id[b.city][b.village],id[a.city][a.village-1],a.people*b.people);
			}
		}
	}
	sum[0] = inf = t-s+1;
	while(dis[s]<inf){
		for(i=s;i<=t;i++) cur[i]=la[i];
		ans+=dfs(s,1e18);
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

