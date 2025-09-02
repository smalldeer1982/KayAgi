# [OOI 2025] Strong Connectivity Strikes Back

## 题目背景

[试题来源](https://inf-open.ru/2024-25/final-materials/)。

## 题目描述

有向图的顶点 $u$ 和 $v$ 被称为强连通的，如果存在一条从 $u$ 到 $v$ 的路径，并且存在一条从 $v$ 到 $u$ 的路径。注意，如果 $u$ 和 $v$ 强连通，且 $v$ 和 $w$ 强连通，那么 $u$ 和 $w$ 也强连通。因此，图中的顶点被划分为若干个强连通分量。属于同一个强连通分量的顶点彼此强连通（包括其本身），并且与任何不属于该分量的顶点都不强连通。

在一次图论课上，Alice 在黑板上画了一个包含 $n$ 个顶点的有向图，并且高亮了图中的强连通分量。课间，Bob 决定恶作剧，他想删除图中一些边的方向，并且希望 Alice 能够根据剩下的边和课间的强连通分量划分，唯一地恢复这些被删除方向的边。

帮助 Bob 确定最大可以删除的边数，以及可以删除这些边的方案数。

更正式地说，找到一个边的子集 $A$，使得如果我们删除集合 $A$ 中边的方向，则根据剩下的边的方向以及强连通分量的划分信息，可以唯一地恢复集合 $A$ 中边的方向，从而保持图的强连通分量不变。并且，求出这个子集 $A$ 的最大大小，以及这个子集的方案数。

由于这样的方案数可能非常大，输出该数对 $10^9 + 7$ 取模的结果。

如果正确计算了最大子集的大小，但方案数计算错误，则将获得部分分数。

## 说明/提示

**样例解释**

在这个样例中，图的强连通分量如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/5fould0s.png)

可以删除虚线边的方向。实际上，边 $(1, 5)$ 不能反向，因为如果反向，顶点 $1$、$2$、$3$、$5$ 将属于同一个强连通分量。同样，边 $(3, 4)$ 和 $(4, 2)$ 也不能反向，因为这样 $2$、$3$、$4$ 将不属于同一个强连通分量。

现在，考虑一个错误的子集选择方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/yxvk46vo.png)

这里，虚线加粗边的方向不能删除。例如，如果我们将边 $(1, 2)$ 和 $(1, 5)$ 的方向反向，得到的图依然会有相同的强连通分量划分。

可以证明，有 $4$ 条边的方向不能删除，因此正确答案是 $3$。

**评分**

本题的测试点共包含七个分组。分组的分数规则如下：

如果正确计算了最大边子集的大小和该子集的方案数，并且在该分组的所有测试点中都正确，用户将获得该分组的满分。

如果正确计算了最大子集的大小，但方案数计算错误，则将为该分组获得部分分数。此时，依赖该分组的分组也将进行测试，并且可能获得满分。

| 组别 | 部分分数 | 满分分数 | 限制条件：$n$ | 限制条件：$m$ | 依赖组别 | 说明                           |
| :--- | :------- | :------- | :----------- | :----------- | :------- | :---------------------------- |
| 0    | 0        | 0        | --            | --            | --       | 样例测试点。                  |
| 1    | 7        | 11       | $n \le 14$    | $m \le 14$    | 0        |                               |
| 2    | 5        | 9        | $n \le 20$    | $m \le 20$    | 0, 1     |                               |
| 3    | 8        | 12       | --            | --            | --       | 满足 $u_i < v_i$，对于所有 $1 \le i \le n - 1$，存在一条边 $(i, i + 1)$。 |
| 4    | 8        | 13       | --            | --            | 3        | 满足 $u_i < v_i$。            |
| 5    | 12       | 20       | --            | --            | --       | 对于所有 $1 \leqslant i \leqslant n - 1$，存在一条边 $(i, i + 1)$，且存在一条边 $(n, 1)$。 |
| 6    | 13       | 21       | --            | --            | 5        | 图是一个强连通分量。         |
| 7    | 8        | 14       | --            | --            | 0 -- 6   |                               |

## 样例 #1

### 输入

```
5 6 0
1 2
1 5
2 3
3 4
3 5
4 2```

### 输出

```
3
3```

# 题解

## 作者：Larryyu (赞：3)

## _Description_

有一张 $n$ 个点，$m$ 条边的有向图。

```Bob``` 不知道原图具体形态，但知道哪些点在同一强连通分量中。

```Alice``` 要将一些边改为无向边，使得 ```Bob``` 可以确定每条无向边在原图中的方向。

求最多能改多少条边，以及方案数对 $10^9+7$ 取模的结果。

保证任意两点之间最多只有一条边，无论方向如何。

$2\le n\le2000,1\le m\le2000$。

## _Solution_

下文中，$u\rightsquigarrow v$ 表示 $u$ 到 $v$ 的一条路径。

先考虑缩完点后在DAG上的边。

对于边 $u\to v$，如果删去该边后依然存在 $u\rightsquigarrow v$，那么可以改为无向边，因为反向后会有新的SCC生成。

注意缩点后的图可能有重边，如果不满足上面的条件，则重边中要保留一条。

此部分可以 $O(n+m)$，本文代码为 $O(nm)$。

再考虑SCC内部的边，接下来的原图为单个SCC。

如果删去 $u\to v$ 后不改变原图连通性，则不能变无向边，因为无法确定方向。

否则 $u\to v$ 反向后一定改变原图连通性。

因为 $u\to v$ 属于一个SCC，所以一定有 $v\rightsquigarrow u$，只有这上面的边影响 $u\to v$ 能否变无向边。

于是考虑删掉 $u\to v$ 后所点形成的DAG，其中 $u$ 的出度和 $v$ 的入度一定为 $0$，再将 $u\to v$ 放回去，设这张图为 $G_{u,v}$。

每条边都对应一张这样的图，而每张这样的图都与其中SCC集合形成双射，所以一条边可以用一个SCC集合表示。

> 引理：
>
> 若两条边的SCC集合不同，那两条边之间是否删除方向互不影响。
>
> 证明：
>
> 设两条边分别为 $u\to v$ 和 $x\to y$。
>
> 因为其SCC集合不同，所以两条边不可能同时在对方缩完点后的DAG上。
>
> 若两条边都不在对方DAG上则显然互不影响。
>
> 否则设 $x\to y$ 在 $u\to v$ 的DAG上，也就是 $u\to v$ 在 $x\to y$ 的DAG上被缩在了一个SCC里面，设其为 $A$，如果 $u\to v$ 最后删向也要先保证 $A$ 的连通性，只要 $A$ 连通，内部边是否删向对 $x\to y$ 能否删向没有影响。
>
> 同理，在 $x\to y$ 的DAG上，$x\to y$ 是否删向都要先保证 $A \rightsquigarrow x\to y \rightsquigarrow A$ 这条路径只能唯一定向，而 $u\to v$ 在 $A$ 中不影响这条路径，所以这条路径在 $u\to v$ 的DAG上是固定方向的，与 $x\to y$ 是否删向无关。

于是我们可以将SCC集合相同的边分到一组一起考虑，不同组之间互不影响。

对于一组边 $E$，设这种边的数量为 $c1$，对应的SCC集合中SCC的数量为 $c2$，有 $c2\ge c1$。

因为这组边对应的 $G$ 上，存在一个环使得 $E$ 是其边集的子集，且对于非环边 $u\to v$，环上路径 $u\rightsquigarrow v$ 的边集与 $E$ 无交。

若 $c2=c1$ 即环的边集就是 $E$，那至少要保留一条边有方向，方案数为 $|E|-1$。

否则 $c2>c1$ 则 $E$ 全都可以删向，方案数为 $|E|$。

对于不同组的边，由于互不影响，方案数由乘法原理可知相乘即可。

时间复杂度 $O(nm)$。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
mt19937 rnd(time(0));
const int N=2020,M=2020,mo=1e9+7;
int n,m,g,cnt,tot;
ll ans1,ans2=1;
ull hsh;
int u[N],v[N],col[N],dfn[N],low[N];
int fl[N][N],hs1[N],hs2[N];
bool vis[N],ext[N][N];
stack<int> s;
vector<int> e[N];
map<pair<int,ull>,int> mp;
void dfs(int x,int &t,int op){
	dfn[x]=low[x]=++cnt;
	vis[x]=1,s.push(x);
	for(int y:e[x]){
		if(ext[x][y]) continue;
		if(!dfn[y]){
			dfs(y,t,op);
			low[x]=min(low[x],low[y]);
		}else if(vis[y])
			low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		t++;
		ull tmp=0;
		int num=1;
		while(s.top()!=x){
			if(op) col[s.top()]=t;
			vis[s.top()]=0;
			tmp^=hs1[s.top()],num++;
			s.pop();
		}
		if(op) col[x]=t;
		vis[x]=0;
		hsh+=(tmp^hs1[x])*hs2[num];
		s.pop();
	}
}
void alter(int x){
	vis[x]=1;
	for(int y:e[x])
		if(!vis[y]) alter(y);
}
bool check(int x,int y){
	for(int i=1;i<=tot;i++) vis[i]=0;
	for(int z:e[x]){
		if(y==z||vis[z]) continue;
		alter(z);
	}
	return vis[y];
}
void solve(int x){
	hsh=0;
	mp.clear();
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1;i<=m;i++)
		if(col[u[i]]==col[v[i]]&&col[u[i]]==x) e[u[i]].push_back(v[i]);
	for(int i=1;i<=m;i++){
		if(col[u[i]]!=col[v[i]]||col[u[i]]!=x) continue;
		int tmp=0;
		ext[u[i]][v[i]]=1,hsh=0;
		e[v[i]].push_back(u[i]);
		cnt=hsh=0;
		for(int i=1;i<=n;i++) dfn[i]=low[i]=0;
		for(int i=1;i<=n;i++)
			if(col[i]==x&&!dfn[i]) dfs(i,tmp,0);
		mp[{tmp,hsh}]++;  //求出这条边对应的SCC集合
		e[v[i]].pop_back();
		ext[u[i]][v[i]]=0;
	}
	for(auto [h,b]:mp){
		int a=h.first;
		if(a==1) continue;  //SCC集合大小为1说明这条边是否存在不影响连通性
		if(b==a) ans1+=b-1,ans2=ans2*b%mo;
		else ans1+=b;  //对于每一组边分开算贡献
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n>>m>>g;
	for(int i=1;i<=n;i++) hs1[i]=rnd(),hs2[i]=rnd();
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i];
		e[u[i]].push_back(v[i]);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) dfs(i,tot,1);
	}
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1;i<=m;i++){
		int x=col[u[i]],y=col[v[i]];
		if(x==y) continue;
		if(!fl[x][y]) e[x].push_back(y);
		fl[x][y]++;
	}
	for(int i=1;i<=tot;i++){
		for(int j=1;j<=tot;j++){
			if(!fl[i][j]) continue;
			if(check(i,j)) ans1+=fl[i][j];
			else ans1+=fl[i][j]-1,ans2=ans2*fl[i][j]%mo;
		}  //计算原图缩点后DAG上的边产生的贡献
	}
	for(int i=1;i<=tot;i++) solve(i);  //单个SCC考虑
	cout<<ans1<<'\n'<<ans2<<'\n';
	return 0;
}
```

---

