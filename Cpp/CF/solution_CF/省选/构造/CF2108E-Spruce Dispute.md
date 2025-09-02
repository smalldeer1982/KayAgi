# Spruce Dispute

## 题目描述

四月的天气已经相当炎热，Polycarp 决定这是拆除他几年前搭建的云杉树的绝佳时机。当他绕着树走了几个小时，积蓄力量时，他注意到一个有趣的现象：这棵云杉实际上是一棵树$^{\text{∗}}$——而且不是普通的树，它由奇数个顶点 $n$ 组成。更特别的是，$n-1$ 个顶点上挂着圣诞装饰品，这些装饰品恰好涂有 $\frac{n-1}{2}$ 种不同的颜色，每种颜色恰好有两个装饰品。剩下的顶点按照传统，挂着树顶的星星。

经过几天的心理准备，Polycarp 终于开始拆除云杉。他先取下了树顶的星星，并开始拆卸一些树枝，这时他突然想到一个自然的问题：如何移除树的一条边，并重新排列装饰品，使得同色装饰品之间的简单路径长度之和尽可能大？

在这个问题中，移除树的一条边的定义如下：选择一对相邻顶点 $a$ 和 $b$（$a < b$），然后从树中移除顶点 $b$，并将 $b$ 的所有相邻顶点（除了 $a$）直接重新连接到 $a$ 上。

Polycarp 在得到这个问题的答案之前无法继续拆除云杉。然而，检查所有可能的选项会花费他数年时间。鉴于你在竞赛编程方面的经验，他向你求助。但你能解决这个争议吗？

$^{\text{∗}}$ 树是指一个无环的连通图。

## 说明/提示

考虑第一个测试用例。

移除连接顶点 $1$ 和 $2$ 的边。之后，顶点 $2$ 将从树中移除，顶点 $3$ 和 $4$ 将被连接到顶点 $1$。

将顶点 $3$ 和 $4$ 涂为第一种颜色，顶点 $1$ 和 $5$ 涂为第二种颜色。同色装饰品之间的简单路径长度之和为 $2 + 2 = 4$。可以证明，这是可能的最大值。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2108E/60feb47fab29e7103e114ad3b20f5966a35c1290.png)

在第二个和第三个例子中，路径长度之和的最大值分别为 $3$ 和 $9$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
5
1 2
2 3
2 4
4 5
5
1 2
1 3
1 4
1 5
7
1 5
5 4
4 3
3 2
2 6
6 7```

### 输出

```
1 2
2 0 1 1 2
1 5
1 1 2 2 0
4 3
1 3 3 0 2 2 1```

# 题解

## 作者：Unnamed114514 (赞：2)

**Lemma1**：所有路径之间一定有交。

**Proof**：考虑两条路径 $(u_1,v_1),(u_2,v_2)$，如果它们之间没有交点，那么选择它们上距离最近的两个点 $a_1,a_2$，那么存在 $u_1\to a_1\to a_2\to v_2,u_2\to a_2\to a_1\to v_1$ 的路径，显然后者更优。

**Lemma2**：这个交点一定是重心。

**Proof**：否则它一定有一棵子树大小过半，因此这棵子树一定不能和外面的匹配完。

那么我们以重心为根搜索，贡献就是所有点的深度之和，那么删除每条边对答案的贡献容易算出来了。

**Lemma3**：如果删除的是重心，那么这条边的另一个端点就是新的重心；否则重心保持不变。

**Proof**：因为 $n$ 为奇数，所以删掉一个点后 $\lfloor\dfrac{n}{2}\rfloor$ 保持不变，因此没有删掉重心的话，只会减少子树大小，所以它仍然是重心；否则因为另一个点的总 $siz\le\lfloor\dfrac{n}{2}\rfloor$，所以它的儿子的 $siz\le \lfloor\dfrac{n}{2}\rfloor$，原重心的其它儿子 $siz$ 不变，所以这个端点就是新的重心。

**Lemma4**：删除一个点后，若有两个重心，那么选择哪个重心对答案不影响。

**Proof**：容易发现，如果以这两个重心之间的边断开这棵树，那么两边的 $siz$ 都是 $\dfrac{n}{2}$，因此改变重心的位置答案不变。

最后就是对答案的求解了：以最终的重心为根，先求出每个儿子的 $siz$，然后从子树中选择剩余节点数最大的两个子树，让它们两个匹配。

容易发现，这样最终一定只会剩下一个点，这个点和重心匹配即可。

```cpp
#include<bits/stdc++.h>
#define endl '\n' 
#define inf 0x3f3f3f3f
using namespace std;
const int N=2e5+5;
int T,n,tot,hv,siz[N],a[N],c[N],dep[N],sum[N];
vector<int> G[N],G2[N],vec[N];
void dfs(int u,int fa){
	int mx=0;
	siz[u]=1;
	for(auto v:G[u]){
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		mx=max(mx,siz[v]);
	}
	if(max(n-siz[u],mx)<=n/2) hv=u;
}
void dfs2(int u,int P,int fa){
	siz[u]=1;
	for(auto v:G2[u]){
		if(v==fa) continue;
		dfs2(v,P,u);
		siz[u]+=siz[v];
	}
	vec[P].emplace_back(u);
}
void dfs3(int u,int fa){
	siz[u]=1;
	for(auto v:G[u]){
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		dfs3(v,u);
		siz[u]+=siz[v];
	}
}
bool cmp(int x,int y){ return siz[x]>siz[y]; }
priority_queue<pair<int,int> > q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1,u,v;i<n;++i){
			cin>>u>>v;
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		hv=0;
		dfs(1,0);
		dep[hv]=0;
		dfs3(hv,0);
		int U=0,V=0,cs=inf,cnt=0;
		for(int u=1;u<=n;++u) for(auto v:G[u]){
			if(u>v) continue;
			if(dep[u]<dep[v]){
				if(siz[v]-1+dep[v]<cs) cs=siz[v]-1+dep[v],U=u,V=v;
			} else{
				if(siz[u]+dep[v]<cs) cs=siz[u]+dep[v],U=u,V=v;
			}
		}
		cout<<U<<' '<<V<<endl,c[V]=0;
		if(hv==V) hv=U;
		for(int u=1;u<=n;++u) for(auto v:G[u]){
			if((u==U&&v==V)||(u==V&&v==U)) continue;
			G2[u==V?U:u].emplace_back(v==V?U:v);
		}
		tot=0;
		while(q.size()) q.pop();
		for(auto k:G2[hv]){
			dfs2(k,k,hv);
			q.emplace(make_pair((int)vec[k].size()-1,k));
		}
		while(q.size()>1){
			pair<int,int> x=q.top();
			q.pop();
			pair<int,int> y=q.top();
			q.pop();
			++cnt,c[vec[x.second][x.first]]=c[vec[y.second][y.first]]=cnt;
			if(x.first) q.emplace(make_pair(x.first-1,x.second));
			if(y.first) q.emplace(make_pair(y.first-1,y.second));
		}
		++cnt,c[vec[q.top().second][0]]=c[hv]=cnt;
		for(int i=1;i<=n;++i) cout<<c[i]<<' ';
		cout<<endl;
		for(int i=1;i<=n;++i){
			G[i].clear(),G[i].shrink_to_fit();
			G2[i].clear(),G2[i].shrink_to_fit();
			vec[i].clear(),vec[i].shrink_to_fit();
		}
	}
	return 0;
}
```

---

## 作者：_jimmywang_ (赞：2)

我们先考虑如果确定了断边方案，如何构造一组路径长度和最大的方案。也就是在确定一个偶数个点的树以后构造方案。

首先考虑路径长度和的上界是什么。每条边分别考虑，那么路径长度和在某一条边 $(u,v)$ 上的贡献就是经过这条边的路径数。记 $s_u,s_v$ 为切断这条边后和 $u,v$ 相连的连通块大小。那么对于这条边，贡献的上界就是 $\min(s_u,s_v)$，取到这个上界的充要条件是 $s$ 较小的那一边所有的点颜色互不相同，这样的话每个颜色的路径都必然经过这条边。

那么我们能不能使得所有边都达到这个上界呢？答案是可以的。具体的考虑如下的构造方式：

我们先找出这棵树的任意一个重心 $g$，把它作为根。那么此时每条边 $(fa_u,u)$ 的贡献都应该是 $sz_u$，其中 $fa_u$ 表示 $u$ 的父亲，$sz_u$ 表示 $u$ 的子树大小。这是由重心的性质保证的。此时答案为 $\sum_{u\neq g} sz_u$。

接下来，我们随便找出一个 dfs 序，并依次标上颜色 $1,2,\dots,\frac{n}{2},1,2,\dots,\frac{n}{2}$。因为重心的每个子树大小均不超过 $\frac{n}{2}$，所以这样可以保证每个子树里颜色均不相同。

至此我们完成了构造。那么应该如何确定题目中的缩边呢？

我们还是先找出原树的重心 $g$ 为根（注意由于是奇数个点，这个重心是唯一的），然后枚举缩某一条边 $(fa_u,u)$ 对答案的减少量。由于是重心，可以证明缩一条边以后仍然是重心，所以仍然可以使用上面的 $\sum_{u\neq g} sz_u$ 的方式计算答案。

记 $dep_u$ 为 $u$ 的深度，令 $dep_g=0$。那么画画图手模一下可以得出：缩 $(fa_u,u)$ 会使答案减少 $sz_u+(dep_u-1)$。于是我们求出这个值最小的 $u$ 并缩边并构造即可。

---

