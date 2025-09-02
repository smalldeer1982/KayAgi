# Multihedgehog

## 题目描述

有人送给 Ivan 一个奇怪的生日礼物。这是一只“刺猬”——一个连通无向图，其中有一个顶点的度数至少为 $3$（我们称之为中心），其余所有顶点的度数均为 $1$。Ivan 觉得刺猬太无聊了，于是决定自己制作 $k$-多重刺猬。

我们定义 $k$-多重刺猬如下：

- $1$-多重刺猬就是刺猬：它有一个度数至少为 $3$ 的顶点，以及若干度数为 $1$ 的顶点。
- 对于所有 $k \ge 2$，$k$-多重刺猬是在 $(k-1)$-多重刺猬的基础上，对每个度数为 $1$ 的顶点 $v$ 进行如下操作：设 $u$ 为其唯一的邻居；删除顶点 $v$，新建一个以顶点 $w$ 为中心的刺猬，并用一条边连接 $u$ 和 $w$。新建的每个刺猬可以彼此不同，也可以与最初的刺猬不同。

因此，$k$-多重刺猬一定是一棵树。Ivan 制作了 $k$-多重刺猬，但他不确定自己是否没有出错。因此他请你帮忙判断，他制作的树是否真的是 $k$-多重刺猬。

## 说明/提示

第一个样例中的 $2$-多重刺猬如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1067B/fa74b226e7f972e84df3729441b7e1df84488eb4.png)

其中心为顶点 $13$。最后一步新建的刺猬分别为：\ [4（中心），1，2，3\]，\ [6（中心），7，8，9\]，\ [5（中心），10，11，12，13\]。

第二个样例中的树不是刺猬，因为中心的度数应至少为 $3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
14 2
1 4
2 4
3 4
4 13
10 5
11 5
12 5
14 5
5 13
6 7
8 6
13 6
9 6
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3 1
1 3
2 3
```

### 输出

```
No
```

# 题解

## 作者：ZMQ_Ink6556 (赞：8)

## CF1067B Multihedgehog 题解
### 解题思路
首先，看这道题的题目：Multihedgehog。这里可以翻译为“刺猬图”。为什么称之为刺猬图呢？因为这道题的图却是有很多“刺”。

来看题目里给出的这张图：

![01](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1067B/fa74b226e7f972e84df3729441b7e1df84488eb4.png)

在这张图里，我们可以认为第 $13$ 个点为“刺猬”，也就是这颗树的根节点。而以 $4$，$5$ 和 $6$ 号节点为根节点的子树就是第 $13$ 号节点的“刺”。

![02](https://cdn.luogu.com.cn/upload/image_hosting/7igj17dr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

通过这张图，我们可以总结出一个验证题目给出的数据是否为 $k$ 次刺猬图的一种方法，主要思路是一轮一轮给刺猬“拔刺”。在拔掉最外层的所有叶子节点后，那么接下来的一层中，所有没有子节点的刺猬成为新的刺。

这个方法细节有点多，具体可以分为以下几个步骤实现：

- 判断现在所有的非叶子节点是否都有 $3$ 个及以上的子节点，原因是题目里给出 $1$ 重刺猬图的中心度数要 $\le3$。如果检查出有 $0<\text{子节点数}<3$ 的节点，则这张图就不是刺猬图。
- 删除所有叶子节点，并且断开所有与之相连的边。
- 将变成叶子节点的刺猬标记出来，方便下一轮操作。
- 检查剩余的点数是否为 $1$。如果剩余点数为 $1$ 且 $\text{轮数} < k$，那么说明这个图是刺猬图，但不是 $k$ 重刺猬图，也要特判掉。

这道题虽然思维不是很难，但是细节比较多，需要多留意。

### 参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct p
{
	int v , nxt;
}edge[200005];
int h[200005] , etmp , u[200005] , v[200005] , n , k , degree[200005] , tmp;
bool flag[200005];
bool chk()
{
	int q = 1;
	for(int i = 1 ; i <= n ; i++)
	{
		q *= 3;
		if(q > n)
		{
			if(k > i)
			{
				return 1;
			}
			return 0;
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> k;
	if(chk())
	{
		cout << "No";
		return 0;
	}
	for(int i = 1 ; i < n ; i++)
	{
		cin >> u[i] >> v[i];
		etmp += 2;
		edge[etmp - 1].v = v[i];
		edge[etmp - 1].nxt = h[u[i]];
		h[u[i]] = etmp - 1;
		edge[etmp].v = u[i];
		edge[etmp].nxt = h[v[i]];
		h[v[i]] = etmp;
	}
	while(k)
	{
		for(int i = 1 ; i <= n ; i++)
		{
			if(flag[i])
			{
				continue;
			}
			degree[i] = 0;
			for(int j = h[i] ; j ; j = edge[j].nxt)
			{
				if(!flag[edge[j].v])
				{
					degree[i]++;
				}
			}
		}
		int c = 0;
		for(int i = 1 ; i <= n ; i++)
		{
			if(degree[i] > 1)
			{
				c++;
			}
		}
		if(c == 0)
		{
			cout << "No";
			return 0;
		}
		for(int i = 1 ; i <= n ; i++)
		{
			if(flag[i])
			{
				continue;
			}
			tmp = 0;
			for(int j = h[i] ; j ; j = edge[j].nxt)
			{
				if(!flag[edge[j].v] && degree[edge[j].v] == 1)
				{
					tmp++;
				}
			}
			if(tmp < 3 && tmp != 0)
			{
				cout << "No";
				return 0;
			}
		}
		for(int i = 1 ; i <= n ; i++)
		{
			if(flag[i])
			{
				continue;
			}
			for(int j = h[i] ; j ; j = edge[j].nxt)
			{
				if(!flag[edge[j].v] && degree[edge[j].v] == 1)
				{
					flag[edge[j].v] = 1;
				}
			}
		}
		k--;
	}
	int k = 0;
	for(int i = 1 ; i <= n ; i++)
	{
		if(!flag[i])
		{
			k++;
		}
	}
	if(k == 1)
	{
		cout << "Yes";
		return 0;
	}
	cout << "No"; 
	return 0;
}
```
#### 代码千万条，思维第一条。
#### 抄题不可取，棕名两行泪。

---

## 作者：Ezis (赞：3)

### 题意：

定义 k-multihedgehog 为：

对于 1-multihedgehog，其中一个点度数 $\ge3$ ，其它点度数均为 $1$.

k-multihedgehog 是在 (k-1)-multihedgehog 的基础上，把所有度为 $1$ 的点替换成一个 1-multihedgehog 并与原图相连。

现给定一张 $n$ 个点的图以及一个数 $k$ ，问这张图是不是一个 k-multihedgehog。

### 思路：

先想想已知这棵树的 root 的时候。

这可以直接 dfs 扫一遍，判断每个点所对应的子树是否符合要求即可。

边界为深度等于 $k$ 时，此时直接判断与它相连的有几条边。

若不是边界，当连边数 $<3$ 时(不算与父亲相连的)，说明不成立，输出 No。

考虑如何求 root。

这里有两种方法:

第一，用一种类似拓扑排序的算法求

但这种方法还要删边，过于麻烦，先不过多考虑

第二，定义一个点的高度为它儿子高度的最大值 $+1$ ，叶子节点高度为 $1$。

然后，我们可以发现 $root$ 的高度一定是 $k+1$

并且其余点的高度都不与 $root$ 相同，否则不合法。

所以我们可以先任选一个点跑一边 dfs 求每个点的高度，

判断一下 $root$ ，再跑一遍刚刚的做法即可。

时间复杂度 $O(n)$

注意,当 $k \ge n$ 时，可直接输出 No，此时必然无解。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,dep[100005],mat[100005],head[100005],edgenum,root;
struct node{
	int to,nxt;
}edge[200005];
void add(int u,int v){
	edgenum++;
	edge[edgenum].to=v;
	edge[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs1(int u,int fa){
	int mx=0;
	for(int e=head[u];e;e=edge[e].nxt){
		int v=edge[e].to;
		if(v==fa) continue;
		dfs1(v,u);
		mx=max(mx,dep[v]);
	}
	dep[u]=mx+1;
}
bool dfs2(int u,int fa,int dep){
	int cnt=0;
	for(int e=head[u];e;e=edge[e].nxt){
		int v=edge[e].to;
		if(v==fa) continue;
		cnt++;
	}
	if(dep==k) return (cnt==0);
	if(cnt<3) return false;
	bool flag=true;
	for(int e=head[u];e;e=edge[e].nxt){
		int v=edge[e].to;
		if(v==fa) continue;
		flag=flag&dfs2(v,u,dep+1);
	}
	return flag;
}
int main(){
	scanf("%d%d",&n,&k);
	if(k>=n){
		printf("No");
		return 0;
	}
	for(int i=1,u,v;i<n;i++){
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dfs1(1,0);
	bool flag1=0;
	for(int i=1;i<=n;i++)
		if(dep[i]==k+1){
			if(flag1){
				printf("No");
				return 0;
			}
			flag1=true;
			root=i;
		}
	flag1=dfs2(root,0,0);
	if(flag1) printf("Yes");
	else printf("No");
	return 0;
}
```


---

## 作者：hongshixiaobai (赞：3)

看到没人交 bfs 的题解，来交一篇
## 题意
给你一棵树，让你判断是不是刺猬图
## 
## 思路
先 bfs 找到根节点，然后从根节点往外搜每个点合不合法（我根节点好像搜歪了，但只要保证正确的图搜的对就行，不正确的我还没找到搜错后输出 yes 的情况，欢迎纠错）
## 
知道思路后实现就很简单了，上代码
## 
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,i,u,v,d[100005],x,zz,maxf;
vector<int>mp[100005];
queue<int>q;
struct p
{
	int x,f;
};
queue<p>q1;
bool vis1[200005],vis2[100005];
int main()
{
	cin>>n>>k;
	if(k>=11||n == 1)
	{
		cout<<"No";
		return 0;
	}
	for(i = 1;i<n;i++)
	{
		cin>>u>>v;
		d[u]++;
		d[v]++;
		mp[u].push_back(v);
		mp[v].push_back(u);
	}
	for(i = 1;i<=n;i++)
	{
		if(d[i] == 1)
		{
			q.push(i);
			vis1[i] = 1;
		}
	}
	while(q.size()-1)
	{
		x = q.front();
		q.pop();
		for(i = 0;i<mp[x].size();i++)
		{
			if(vis1[mp[x][i]] == 0)
			{
				q.push(mp[x][i]);
				vis1[mp[x][i]] = 1;
			}
		}
	}
	zz = q.front();
	q.pop();
	p tmp,x1;
	tmp.x = zz;
	tmp.f = 0;
	q1.push(tmp);
	vis2[tmp.x] = 1;
	while(q1.size())
	{
		x1 = q1.front();
		q1.pop();
		int t=0;
		for(i = 0;i<mp[x1.x].size();i++)
		{
			if(vis2[mp[x1.x][i]] == 0)
			{
				t++;
				tmp.x = mp[x1.x][i];
				tmp.f = x1.f+1;
				q1.push(tmp);
				vis2[mp[x1.x][i]] = 1;
			}
		}
		if(t<3&&t>0)
		{
			cout<<"No";
			return 0;
		}
		if(tmp.f != k&&d[tmp.x] == 1)
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

## 作者：OIerWu_829 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1067B)

多重刺猬图是在 $1$ 重刺猬图的基础上递归地进行定义，将刺猬地每一根“刺”变成一个刺猬图，便可以在原图上增加一重。如何判断一张图是不是多重刺猬图呢？我们可以从定义出发反向操作，把刺猬图最外层的刺去掉后，刺猬图便会降低一重。重复以上操作，最后刺猬图只会剩下一个最核心的点。实际上，刺就是图中度为 $1$ 的结点，在删去之前，我们需要判断与它相连的点度数是否不小于 $3$，如果在过程中发现有结点不满足这个要求，那么就可以直接判断出这个图不是刺猬图。

在计算结点总数时，数量会随着重数的增加以指数级别增加，在中心结点上至少加 $3$ 个结点变为 $1$ 重图，至少加 $3^2=9$ 个结点变为 $2$ 重图，后面的以此类推，所以重数最多不会超过 $12$（$3^{12}=531441$，最外层的结点数量已经超过 $n$）。给出代码：

```cpp
#include <iostream>
using namespace std;

const int N = 2e5 + 5;

int n, k, head[N], d[N], del[N], cnt;

struct Edge
{
	int v, nxt;
} edge[N];

void add(int u, int v)
{
	cnt++;
	edge[cnt].v = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}

bool Solve()
{
	if (k > 12) return false;
	while (k)
	{
		for (int i = 1; i <= n; i++)
		{
			if (del[i]) continue;
			d[i] = 0;
			for (int j = head[i]; j; j = edge[j].nxt)
			{
				if (!del[edge[j].v]) d[i]++;
			}
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			if (d[i] > 1) cnt++;
		}
		if (!cnt) return false;
		for (int i = 1; i <= n; i++)
		{
			if (del[i]) continue;
			int leaf = 0;
			for (int j = head[i]; j; j = edge[j].nxt)
			{
				int v = edge[j].v;
				if (!del[v] && d[v] == 1) leaf++;
			}
			if (leaf < 3 && leaf != 0) return false;
		}
		for (int i = 1; i <= n; i++)
		{
			if (del[i]) continue;
			for (int j = head[i]; j; j = edge[j].nxt)
			{
				int v = edge[j].v;
				if (!del[v] && d[v] == 1) del[v] = 1;
			}
		}
		k--;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!del[i]) cnt++;
	}
	return (cnt == 1);
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    cout << (Solve() ? "Yes\n" : "No\n");
    return 0;
}
```

---

## 作者：GWBailang (赞：2)

Multihedgehog，刺猬图。

~~因为我比较懒~~因为我这道题是我刚学图论时做的题，连邻接矩阵都不懂，所以我莫名奇妙的高出了一种非常规操作，调了进一周结果还通过了。这篇题解我就讲一个用不到邻接矩阵的方法。

题目定义一颗“刺猬图”为：对于每一个点，出度要么为 $0$ 要么大于等于 $3$。但是我存图的方法有点特殊，我分别存了每一条边的左端点（$u$）和右端点（$v$），以及每一个点都连接着几条边。是的，这成了无向图，然后我调了半天，找到了可以判断是否为刺猬树的方法：模拟“拔刺”，我们一共需要“拔”$k$ 次，每一次先记录每个点都连接着几个度为 $1$ 的点，我们设这个值为 $d_i$，如果这个图是个刺猬图，必须满足所有的 $d_i$ 都要么是 $0$ 要么大于等于 $3$。有一个 $d_i$ 不满足就一定不是刺猬图。如果不满足就直接输出 ```No``` 即可，不用再往下执行，如果满足，就“拔刺”，将所有度为 $1$ 的点连接着的边都删除。

最后拔完 $k$ 次，再判断还剩几条边，如果没有边了，就说明这是个刺猬图，输出 ```Yes```，否则输出 ```No```。

不懂可以看代码注释：
```
#include<bits/stdc++.h>
using namespace std;
struct Node{
	int u,v;//这条边连接u和v
	bool sf;//后续“拔刺”用到的，记录这根“刺”是否被“拔”了
}bian[100005];//每一条边
int dian[100005];//每一个点的度
int ci[100005];//每一个点连接着几个度为1的点
int n,k;
bool cicicici(){
	memset(ci,0,sizeof(ci));
	//找由外向内第二层的那些点，都连着几个度为1的点
	for(int i=1;i<n;i++){//分别找每条边的u和v
		if(bian[i].sf){
			//如果这个点的度为1，也就是刺猬图最外层的刺
			if(dian[bian[i].u]==1)ci[bian[i].v]++;
			if(dian[bian[i].v]==1)ci[bian[i].u]++;
		}
	}
	for(int i=1;i<=n;i++){
		if(ci[i]!=0&&ci[i]<3)return false;
		//如果有第二层的点只连了1或2个最外层的点，那么这个图就一定不是刺猬图
	}
	return true;
}
bool du(){
	memset(dian,0,sizeof(dian));
	for(int i=1;i<n;i++){//计算每个点的度
		if(bian[i].sf){
			dian[bian[i].u]++;
			dian[bian[i].v]++;
		}
	}
	return cicicici();
}
void baci(){//拔刺
	for(int i=1;i<n;i++){
		if(bian[i].sf){
			if(dian[bian[i].u]==1||dian[bian[i].v]==1){
				//如果连着度为1的点就把这条边删除
				bian[i].sf=false;
			}
		}
	}
	return;
}
int diandian(){
	int cnt=0;
	for(int i=1;i<n;i++){
		if(bian[i].sf)cnt++;//还有几条边
	}
	return cnt;
}
void no(){cout<<"No\n";exit(0);}//压行用的
void yes(){cout<<"Yes\n";exit(0);}
int main(){
	cin>>n>>k;
	if(k>12||n==1)no();//3^13>10^4
	for(int i=1;i<n;i++){
		cin>>bian[i].u>>bian[i].v;
		bian[i].sf=true;
	}
	if(!du())no();//先判断一遍
	for(int i=1;i<=k;i++){//需要拔k次刺
		baci();
		if(!du())no();
		else if(i==k&&diandian()==0)yes();
		if(diandian()==0)no();
	}
	no();
	return 0;
}
```


---

## 作者：_edge_ (赞：2)

这道被我一眼秒掉的题目，真的是 $1800$ 的？

看一下题，题目中的意思大概就是把那个度数 $\ge 3$ 的视为根，然后把它的子节点都给替换掉。

然后我们去观察一下样例，可以明确的是度数 $= 1$ 的肯定是一个 1-multihedgehog 的子节点，然后我们将这些点删掉之后，发觉删除了之后，这张图就是 k-1-multihedgehog，然后可以猜测一下，大概就是从外面往里搞。

实际这题目有点类似与拓扑排序，可以类比，然而这题目树是无向边，当然也不是没有办法，依旧可以类似与拓扑排序，不过要记录一个 vis1 数组，为当前是否被访问过，如果有的话，那就之后无需访问。

当然，这也有点像 BFS ~~事实上，我也不太清楚。~~

大体的想法就是先把度数 $\ge 1$ 的都搞到一个队列里面，然后取出节点，如果这个节点，它的儿子是 $\ge 3$ 个的，那么就是可以的，否则可以直接特判掉无解，因为它这个要保证每一个节点都是根或者度数 $=1$ 的节点，当然对于它的儿子来说，如果他们的图级别不一样，显然也是无解。

上述图的级别指的是 k-multihedgehog 中的 k。

然后我们去寻找这个最大的级别是啥，比较一下它和题目中给定的 $k$ 即可。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
const int INF=1e5+5;
struct _node_edge{
    int to_,next_;
}edge[INF<<1];
int head[INF],tot,in[INF],dis_[INF],vis[INF],vis1[INF];
queue <int> q;
void add_edge(int x,int y) {
    edge[++tot]=(_node_edge){y,head[x]};
    head[x]=tot;in[y]++;return ;
}
int n,k;
signed main()
{
    memset(dis_,255,sizeof dis_);
    scanf("%d %d",&n,&k);
    for (int i=1;i<n;i++) {
        int x=0,y=0;scanf("%d %d",&x,&y);
        add_edge(x,y);add_edge(y,x);
    }
    for (int i=1;i<=n;i++) {
        if (in[i]==1) {
            dis_[i]=0;
            vis[i]=1e9;
            vis1[i]=1;
            q.push(i);
        }
    }
    while (q.size()) {
        int x=q.front();q.pop();
        vis1[x]=1;
        // cout<<x<<"\n";
        if (vis[x]<3) {cout<<"No\n";return 0;}
        for (int i=head[x];i;i=edge[i].next_) {
            int v=edge[i].to_;if (vis1[v]) continue;
            if (dis_[v]==-1) dis_[v]=dis_[x]+1,vis[v]=1;
            else if (dis_[v]!=dis_[x]+1) {cout<<"No\n";return 0;}
            else vis[v]++;
            if (--in[v]==1) q.push(v);
        }
    }
    int Max=0;
    for (int i=1;i<=n;i++)
        Max=max(Max,dis_[i]);
    // cout<<dis_[6]<<" over\n";
    if (Max==k) cout<<"Yes\n";
    else cout<<"No\n";
    return 0;
}
```


---

## 作者：run_away (赞：1)

## 题意

定义 $1$ 阶“刺猬图” 为一个点度数 $\ge3$，其他点度数为 $1$ 的树。

把一个 $1$ 阶“刺猬图” 中所有度数为 $1$ 的点替换成以它为根的 $1$ 阶“刺猬图”，这样的树称作 $2$ 阶“刺猬图”。

以此类推。

给定一棵 $n$ 个点的树和整数 $k$，如果该树是 $k$ 阶“刺猬图”，输出 `Yes`，否则输出 `No`。

## 分析

思路挺简单。

首先找到树的中心，就是作为“刺猬图” 时的根节点，然后跑一遍 DFS，求解出每个点的高度和儿子数，判断即可。

但有个问题是怎么求中心。

### WA#1

如果 $k\ge n$，肯定输出 `No`。

先求树的直径，因为它是一棵树，所以满足 $dis_i$ 为直径一半的 $i$ 肯定是中心。

然后就 WA 了，看样例 1 可以发现，直径是 $4$，但跑出来 $dis$ 是 $2$ 的不止一个。

### WA#2

经过观察可以发现 $dis$ 为直径一半的可能是叶子节点，所以加入特判，可过样例，但是还是 WA。

再手造一组数据发现这种节点不一定是叶子节点。

### WA#3

两次 DFS 求高度和度数，原理和前面类似，所以也 WA。

### AC

如果从叶子节点标记高度为 $1$，那么根节点肯定是 $k+1$，所以可以搜一遍，然后记录 $dep$，如果有多个点都是 $k+1$，那么就肯定不满足“刺猬图” 的性质。

后面就很好写了，总时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll mod=1e9+7,maxn=1e5+5,maxt=505;
ll n,k,dis[maxn],rt,dep[maxn];
vector<ll>son[maxn];
inline void dfs1(ll u,ll pre){
    ll mx=0;
    dep[u]=dep[pre]+1;
    for(auto v:son[u]){
        if(v==pre)continue;
        dfs1(v,u);
        mx=max(mx,dis[v]);
    }
    dis[u]=mx+1;
}
inline bool dfs2(ll u,ll pre){
    ll cnt=0;
    for(auto v:son[u]){
        if(v==pre)continue;
        ++cnt;
    }
    if(dep[u]==k+1)return !cnt;
    if(cnt<3)return 0;
    for(auto v:son[u]){
        if(v==pre)continue;
        if(!dfs2(v,u))return 0;
    }
    return 1;
}
signed main(){
    n=read(),k=read();
    if(k>=n)puts("No"),exit(0);
    for(ll i=1;i<n;++i){
        ll u=read(),v=read();
        son[u].push_back(v);
        son[v].push_back(u);
    }
    dfs1(1,0);
    for(ll i=1;i<=n;++i){
        if(dis[i]==k+1){
            if(rt)puts("No"),exit(0);
            else rt=i;
        }
    }
    dfs1(rt,0);
    puts(dfs2(rt,0)?"Yes":"No");
    return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

这题是蓝？？？？？

首先统计每一个点的入度，如果有一个点的度数为 $2$ 或者不存在一个点的度数 $>2$，那么显然无解。

求树的直径，设这个值为 $k'$。若 $2\mid k'$ 那么无解，否则令 $k=\lfloor\frac{k'}{2}\rfloor$ 即为题目中的 $k$。若不等则无解。

然后跑多源多汇最短路，起点为每一个度数为 $1$ 的节点。设这些结点的距离都为 $0$，那么令每一条边权都为 $1$，跑最短路，这样算出来的就是每一个点到叶子节点的简单路径所经过的最少边数。

找到唯一一个距离为 $k$ 的节点。这个节点必须是距离最远的节点。那么这个节点就是这个树最中心的节点，即这个树为一开始未进行扩展时的 `1-Multihedgehog` 的重心节点。

从重心节点开始跑最短路即可。时间复杂度 $O(n)$。

---

## 作者：Loser_Syx (赞：1)

Orz 手速哥 [_•́へ•́╬_](https://www.luogu.com.cn/user/90693)。

由于一开始直接找第一个 `1-multihedgehog` 不方便，不好得知每个点为最深节点可以构成的最大值（下称深度）。  
考虑反推，从深度最小的节点先开始，由于最后一个被扩充的点度数一定为 $1$，所以这个节点的层数是确定的。

然后就是阅读理解，题面写的很糊。  
题面中所指度数 $\geq 3$，理论上应该修改为出度 $\geq 3$。

因为无向图中已经确定了一些点和边的顺序且此图为一棵树，故可以得出所有边的指向。  
然后考虑模拟拓扑排序，依次从深度最小的去做，每次都是更新比他深度大的节点，具体地，更新自己没有更新过的出边上的点。  
这样发现相邻两个节点深度差只可能为 $1$，故可以借用此来判合法。  
此外对于每个节点还需记录它被更新了几次，$\geq 3$ 直接扩展。

注意到除度数为 $1$ 的节点外，其他的点的出度都应 $\geq 3$（尽管拓扑排序时是按照从入到出更新的），且一开始的 `1-multihedgehog` 的出度 $\geq 3$ 的点只能有一个，所以上升到 `k-multihedgehog` 时也只能有一个。  
对上述情况继续判定即可。

剩下情况即为合法。

```cpp
vector<int> g[101010];
bool vis[101010];
int d[101010], in[101010], deg[101010];
#define pii pair<int, int>
#define fi first
#define se second
signed main() {
	int n, k;
	read(n, k);
	for (int i = 1; i < n; ++i) {
		int u, v;
		read(u, v);
		g[u].emplace_back(v);
		g[v].emplace_back(u);
		++deg[u];
		++deg[v];
	}
	priority_queue<pii, vector<pii>, greater<pii> > topsort;
	for (int i = 1; i <= n; ++i) {
		if (deg[i] == 1) {
			topsort.push({1, i});
			vis[i] = 1;
			in[i] = 3;
			d[i] = 1;
			//cout << i << '\n';
		}
	}
	while (!topsort.empty()) {
		pii u = topsort.top();
		topsort.pop();
		for (const auto &i : g[u.se]) {
			if (d[i] && d[i] == u.fi - 1) continue;
			if (d[i] == 0 || d[i] == u.fi + 1) {
				in[i] ++;
				d[i] = u.fi + 1;
				if (in[i] >= 3 && !vis[i]) {
					vis[i] = 1;
					topsort.push({d[i], i});
				}
			} else return puts("No"), 0;
		}
	}
	int cnt = 0;
	//cout << d[14] << ' ' << in[14] << '\n'; 
	for (int i = 1; i <= n; ++i) {
		if (in[i] < 3) return puts("No"), 0;
		cnt += d[i] == k+1;
	}
	puts(cnt == 1 ? "Yes" : "No");
	return 0;
}
```

---

## 作者：water_tomato (赞：1)

## 题意

定义一棵树 k-multihedgehog：

对于 1-multihedgehog，其中一个点度数 $\ge3$ ，其它点度数均为 $1$.

k-multihedgehog 是在 k-1-multihedgehog 的基础上，把所有度为 $1$ 的点替换成一个 1-multihedgehog 并与原图相连。

## 解析

我们可以用**模拟**的做法来解决这个问题。我们先假设给出的树是 k-multihedgehog 然后由外自内一层一层删除并记录删了几层，最后再将我们得到的层数与 $k$ 进行比较，判断是否相同即可。当然，如果在模拟过程中发现了不合题意的情况，就直接输出 `No` 并退出。

那模拟具体怎么实现呢？

我们可以先把最外层的点抽出来，然后找到他们的父亲节点，再将这个父亲节点处理了，处理完这个父亲节点的同时把这个父亲节点推进队列里去，成为下一轮的“最外层的点”，如此往复。同时，由于相邻两层要分开处理，我们需要两个队列滚一下。

这么讲可能不是很清楚，代码会注释的比较详细。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,K;
struct edge{
	int to,next;
}e[N<<1];
int head[N],cnt,num;
int vis[N];
int in[N];
inline void add(int x,int y){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
}
inline void solve(){
	queue<int> q[2];
	for(int i=1;i<=n;i++)
		if(in[i]==1) q[0].push(i),vis[i]=0;//推进最外层的点 
	for(int	t=0;;t^=1){//相邻两层不能混淆，因此需要用 t 标记一下 
		while(!q[t].empty()){
			int x=q[t].front();q[t].pop();
			if(in[x]==0) continue;//如果这个点已经被处理过了，即度数减为 0 了，直接 continue 即可 
			int u;
            for(int i=head[x];i;i=e[i].next){//寻找父亲节点 
                if(in[e[i].to]==0) continue;
                u=e[i].to;break;
            }
            if(in[u]<3){printf("No\n");exit(0);}//如果父亲节点度数 <3，显然是不合题意的 
			int tot=0;//tot 记录儿子个数 
			for(int i=head[u];i;i=e[i].next){
				int v=e[i].to;
				if(in[v]==1&&vis[v]==t) in[v]--,in[u]--,tot++;//对于找到的儿子，父亲和儿子都处理一下 
			}
			if(tot<3){printf("No\n");exit(0);}//如果非最外层节点的儿子数 <3，显然是不合题意的 
			q[t^1].push(u);vis[u]=t^1;
//			printf("out%d %d %d %d\n",x,u,t,num);
		}
		if(q[t^1].empty()) break;//如果下一轮是 empty ，那么说明我们已经找到最终的初始父亲了，可以退出 
		num++;
	}
}
int main(){
	scanf("%d%d",&n,&K);
	memset(vis,-1,sizeof(vis));
	for(int i=1,x,y;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
		in[x]++;in[y]++;//初始记录度数 
	}
	if(K>=n){printf("No\n");return 0;}//显然，层数大于点数直接输出 No (题面 k的范围特别大) 
	solve();
	if(num==K) printf("Yes\n");//若模拟得到的层数和给出的相同，输出 Yes 
	else printf("No\n");
	return 0;
}
```

如果对代码理解仍然有困难，可以注意代码里有一行被注释掉的 `printf` ，对于样例 $1$ ，输出结果是这样的：

```
out1 4 0 0
out7 6 0 0
out10 5 0 0
out4 13 1 1
```

我们可以看到，该程序先找到了最外层的 $1$ 号点，然后处理了父亲 $4$ 号点，这样三次处理了第一层，然后找到了第二轮成为最外层的 $4$ 号点，处理了他的父亲 $13$ 号点，最后 $13$ 号点处理之后得到的下一层是 empty 的，循环就结束了，除初始根以外找到了 $2$ 层，与 $k$ 相同，故结果为 `Yes`。

## 琐记

拿到这题的时候，我真的觉得……挺简单，结果一直 WA ，发现这道题坑点很多，处理也算是比较麻烦。此外，不直接从外向内处理，而是每次找父亲节点处理最外层的思路也算是比较有趣的了。

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1067b-multihedgehog-de-ti-jie/)
## 题目大意
定义 $k$ 阶刺猬树：

- 对于 $1$ 阶刺猬树，其中一个点的度 $\ge3$，其它点的度均为 $1$。
- 对于 $k$ 阶刺猬树，是在 $k−1$ 阶刺猬树的基础上，把所有度为 $1$ 的点替换成 $1$ 阶刺猬树，并与原图相连。

给定 $n$ 个点的树，判断是否是 $k$ 阶刺猬树。

## 思路
对于任意 $k$ 阶刺猬树，有性质：

- 假定 $a$ 为原始 $1$ 阶刺猬树的度 $\ge 3$ 的节点，则 $a$ 到所有叶子节点的距离均为 $k$。

而且只要满足此性质及为 $k$ 阶刺猬树。

证明：

假设 $a$ 为 $1$ 阶刺猬树的度 $\ge 3$ 的节点，那么所有的节点到 $a$ 的距离均为 $1$。

$2$ 阶刺猬树则将所有度为 $1$ 的节点增加一层，及将 $a$ 到叶子节点的距离增加 $1$。

对于 $k$ 阶刺猬树，$a$ 到叶子的节点均为 $k-1$ 阶刺猬树到叶子的节点的距离加 $1$，所以 $k$ 阶刺猬树中 $a$ 到叶子节点的距离为 $k$。

相对的，将所有的叶子节点都向父节点移动，那么如果所有的移动经过 $k$ 次移动，到最后在一个节点汇合那么这棵树就是 $k$ 阶刺猬树。
## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+6;
int n,k,du[N];
bool vis[N];
vector<int> v[N];
queue<int> q[2];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>k;
	if(k>n){
		cout<<"No\n";
		exit(0);
	}
	for(int i=1,x,y;i<n;i++){
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
		du[x]++,du[y]++;
	}
	for(int i=1;i<=n;i++){
		if(du[i]==1){
			q[1].push(i);
			vis[i]=1;
			// cout<<i<<' ';
		}
	}
	// cout<<'\n';
	// exit(0);
	for(int i=1;i<k;i++){
		while(!q[i%2].empty()){
			int x=q[i%2].front();
			q[i%2].pop();
			for(int j:v[x]){
				if(vis[j]){
					continue;
				}
				if(du[j]<=3){
					cout<<"No\n";
					exit(0);
				}
				// cout<<j<<' ';
				vis[j]=1;
				q[(i+1)%2].push(j);
			}
		}
		// cout<<'\n';
	}
	int cnt=0,p;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			cnt++;
			p=i;
			if(du[i]<3){
				cout<<"No\n";
				exit(0);
			}
		}
	}
	if(cnt==1&&q[k%2].size()==v[p].size()){
		cout<<"Yes\n";
	}
	else{
		cout<<"No\n";
	}

	return 0;
}
```

---

## 作者：KυρωVixen (赞：0)

# CF1067B 题解

## 题意

一个 $1$ 阶刺猬是一个至少有 $4$ 个点的菊花图。

一个 $k$ 阶刺猬可以这样得到：将一个 $k-1$ 阶刺猬所有度数等于 $1$ 的点替换为一个 $1$ 阶刺猬。

所有刺猬都是树。

给你一棵树，问你它是不是 $k$ 阶刺猬。

## 题解
考虑暴力。

每次将度数为 $1$ 的点全部删掉，并统计所有与删掉的点所连的点，每个点因为删掉所减小的度数是否大于等于 $3$。

这样删 $k$ 次，应该最后只剩余 $1$ 个点。如果有删到一半点数已经为 $1$ 的情况或者删 $k$ 次仍未删到只有 $1$ 个点，则特判。

采用 `set` 存图，`map` 判断度数，精细实现即可做到 $O(n\log n)$。

关于 $k$：可以发现合法的 $k$ 一定在 $\log n$ 量级，所以在如前文特判后 $k$ 并不会影响时间复杂度。

## 代码
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define fi first
#define sc second
#define endl '\n'
using namespace std;
const int N=1e5+5;
int n,k,now,cnt,d[N],del[N];
set<int>G[N];
map<int,int>mp[2];
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>k; cnt=n;
    rep(i,2,n){
        int u,v; cin>>u>>v; d[u]++; d[v]++;
        G[u].insert(v); G[v].insert(u);
    }
    rep(i,1,n) if(d[i]==1) mp[now][i]=0; 
    rep(i,1,k){
        if(mp[now].size()<=1){
            cout<<"No"<<endl; return 0;
        } 
        for(auto p:mp[now]){
            int u=p.fi; del[u]=1; cnt--;
            for(int v:G[u]){
                mp[now^1][v]++;
                G[v].erase(u);
            }
        }
        for(auto p:mp[now^1]){
            if(p.sc<3){
                cout<<"No"<<endl; return 0;
            }
        }
        mp[now].clear();
        now^=1;
    }
    if(cnt!=1) cout<<"No"<<endl;
    else cout<<"Yes"<<endl;
}
```

---

