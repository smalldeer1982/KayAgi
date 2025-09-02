# Robot Rapping Results Report

## 题目描述

#### 题目简述
$n$ 个机器人，每个机器人有一个不同的级别，级别介于 $1\sim n$，高级别的可以打败低级别的，现在给出 $n$ 个机器人的 $m$ 场比赛胜负情况，问最少需要前几场比赛就可以确定每个机器人的级别。

## 说明/提示

$2\leq n\leq 10^5$，$1\leq m\leq \min(\frac{n\times (n-1)}{2},10^5)$。

## 样例 #1

### 输入

```
4 5
2 1
1 3
2 3
4 2
4 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 2
1 2
3 2
```

### 输出

```
-1
```

# 题解

## 作者：EnochWenzhou (赞：8)

这题有两种写法，一种是先二分答案是在第几条边，将小于此边的边都加入，跑一遍拓扑序列，假如在某一时间队列中的元素多于一个即表示这个图的拓扑序不只一种即为错误，反之可以排出名次。比较容易想到。O(nlogn)

这里再介绍另一种做法。加入几条边也等同于先把所有边加入后删除几条，那么只需在跑一遍拓扑序的时候记录能够求出这个点的拓扑序的最少边数为多少。记录dfn为拓扑序，id为最少边数。假如某一点x要更新y点时：假如dfn[x]+1>dfn[y]那么dfn[y]=dfn[x]+1,id[y]=x与y的边,假如dfn[x]+1==dfn[y]那么id[y]=max(id[y],x与y的边),即可。时间复杂度能够达到O(n)

O(n)做法：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define rint register int
#define M 100010
using namespace std;
int n,m,a1,b1,cnt,in[M],nt[M],to[M],ft[M],id[M],dfn[M],ID[M],mk[M],ans,F;
queue<int>q;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a1,&b1);
		cnt++,id[cnt]=i,to[cnt]=b1,nt[cnt]=ft[a1],ft[a1]=cnt;in[b1]++;
	}
	for(int i=1;i<=n;i++)
		if(!in[i]){
			if(F){cout<<-1;return 0;}
			q.push(i),F=1;
		}
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=ft[x];i;i=nt[i]){
			int y=to[i];
			if(dfn[y]==dfn[x]+1)ID[y]=min(ID[y],id[i]);
			if(dfn[y]<dfn[x]+1)dfn[y]=dfn[x]+1,ID[y]=id[i];
			if(!(--in[y]))q.push(y);
		}
	}
	for(int i=1;i<=n;i++){if(mk[dfn[i]]){cout<<-1;return 0;}mk[dfn[i]]=1;}
	for(int i=1;i<=n;i++)ans=max(ans,ID[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Allanljx (赞：3)

## 思路

先二分前几场比赛可以确定级别。把机器人 $u$ 打败机器人 $v$ 变为一条从 $u$ 连向 $v$ 的边。然后对前 $mid$ 条边进行拓扑排序。当入度为 $0$ 的点不止一个时不行，因为这几个机器人的等级（顺序）不唯一。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
queue<int> q;
int n,m,ans;
vector<int> t[100005];
int in[100005];
int vis[100005];
int u[100005],v[100005];
void init()//初始化 
{
	memset(in,0,sizeof(in));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) t[i].clear();
	while(q.size()) q.pop();
}
bool topo()//拓扑排序 
{
	for(int i=1;i<=n;i++) if(!in[i]) q.push(i),vis[i]=1;
	while(q.size())
	{
		if(q.size()>1) return 0;//入度为0的点不止一个 
		int f=q.front();
		q.pop();
		for(int i=0;i<t[f].size();i++)
		{
			in[t[f][i]]--;
			if(!in[t[f][i]]&&!vis[t[f][i]]) q.push(t[f][i]),vis[t[f][i]]=1;
		}
	}
	return 1;
}
bool check(int x)
{
	for(int i=1;i<=x;i++)//建图，统计入度 
	{
		t[u[i]].push_back(v[i]);
		in[v[i]]++;
	}
	return topo();
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i];
	int l=1,r=m;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
		init();
	}
	if(!ans) puts("-1");//没找到（无法确定） 
	else cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Hhy882577 (赞：2)

## 思路

首先，题目中明确了比赛中无水平一样的机器人，可以明确排名，由于在一场**明确排名**的比赛中，一定有**强**和**弱**之分，这样可以理解为两者存在一条有向边。把这个结论放在图论中抽象一点，即：**最弱**者不仅谁都打不过（入度为零），还会被所有碰见它的人击败。**最强**者反之（出度为零）。很容易想到拓扑排序。

因此本题判断是否输出 $\textnormal{-}1$ 的方法就出来了：如果跑完拓扑排序还存在有入度不为零的机器人，则不能确定排名。

然后就是如何跑拓扑的问题。看到题目中还给了求最小值，考虑二分。又因为我们确定的边数越多，排名肯定也越明确，二分边数 $m$ 来拓扑排序即可（注意每次一定要初始化！！！该清零的就清零！！！）。

复杂度 $O(n\log n)$

---

## Code

### vector 存图版：


```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
int n,m,ind[N],ans,a[N],b[N];
vector<int> edge[N];
bool check(int mid){
	memset(ind,0,sizeof(ind));		//初始化 
	for(int i=1;i<=n;i++)
		edge[i].clear();
	for(int i=1;i<=mid;i++){
		ind[b[i]]++;
		edge[a[i]].push_back(b[i]);
	}
	queue<int> q;
	for(int i=1;i<=n;i++){		//有入度为零的就入队，下文同理 
		if(ind[i]==0)
			q.push(i);
	}
	while(!q.empty()){
		if(q.size()>1)		//如果有两个及以上"入度为零"的情况，说明不能确定排名 
			return 0;
		int hx=q.front();
		q.pop();
		for(auto it : edge[hx]){
			ind[it]--;
			if(ind[it]==0)
				q.push(it);
		}
	}
	return 1;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)		//数组存下来每次二分都要重建 
		cin>>a[i]>>b[i];
	int l=1,r=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){			//拓扑排序 
			r=mid-1;
			ans=mid;
		}
		else
			l=mid+1;
	//	cout<<ans<<" "<<l<<" "<<r<<"\n";
	}
	if(ans==0)		//找不到就返回-1 
		cout<<-1;
	else
		cout<<ans;
	return 0;
} 
```

### 链式前向星存图版（其实本质没有区别）：


```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
struct Edge{
	int next,to;
}edge[N<<4];
int n,m,ind[N],ans,a[N],b[N],head[N],cnt;
inline void add(int from,int to){		//加边 
	edge[cnt].next=head[from];
	edge[cnt].to=to;
	head[from]=cnt++;
}
bool check(int mid){
	memset(head,-1,sizeof(head));		//初始化 
	memset(ind,0,sizeof(ind));
	cnt=0;
	for(int i=1;i<=n;i++)
		edge[i].next=edge[i].to=0;
	for(int i=1;i<=mid;i++){
		ind[b[i]]++;
		add(a[i],b[i]);
	}
	queue<int> q;
	for(int i=1;i<=n;i++){
		if(ind[i]==0)
			q.push(i);
	}
	while(!q.empty()){
		if(q.size()>1)		//如果有两个及以上"入度为零"的情况，说明不能确定排名 
			return 0;
		int hx=q.front();
		q.pop();
		for(int i=head[hx];~i;i=edge[i].next){
			ind[edge[i].to]--;
			if(ind[edge[i].to]==0)
				q.push(edge[i].to);
		}
	}
	return 1;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)		//数组存下来每次二分都要重建
		cin>>a[i]>>b[i];
	int l=1,r=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){		//拓扑排序 
			r=mid-1;
			ans=mid;
		}
		else
			l=mid+1;
	//	cout<<ans<<" "<<l<<" "<<r<<"\n";
	}
	if(ans==0)		//找不到就返回-1 
		cout<<-1;
	else
		cout<<ans;
	return 0;
} 
```

完结撒花 QWQ

---

## 作者：Diode123 (赞：2)

## 前言

本文做法参考 @[EnochWenzhou](https://www.luogu.com.cn/user/40262) 大佬的 $ O(n) $ 做法，但是由于那是篇远古题解，并没有使用 Latex ，而且同时使用了 `id[]` 和 `ID[]` ，导致看上去很难懂，所以这里写一篇更为详细的，有问题欢迎大佬指出。

## 题目分析

显然，要确定每个机器人的级别，我们要使用**拓扑排序**，不过由于要确定每个机器人的级别，就不能有多个拓扑序，而判断此点只需要查询队列中是否同时存在了 多于 $1$ 个点就行了。

那么怎么确定“最少需要前几场比赛”才能确定呢？我们可以在拓扑排序时**记录确定这个点拓扑序的编号最小边**，使用类似 松弛 或 DP 的操作实现。

定义 $ ged_i $ 表示 确定编号为 $i$ 的点拓扑序的编号最小边，$tp_i$ 表示编号为 $i$ 的点的拓扑序，在遍历一个点的每一条边时，该边本身编号为 $i$ ，起始点编号为  $nx$，目标点编号为 $to$ ，那么当 $tp_{to} = tp_{nx} + 1$ 时，即从 $i$ 这条边更新 $tp_{to}$ 时 $tp_{to}$ 的值不变时：

$$ged_{to} = \min(ged_{to}, i)$$

即判断 $i$ 是否比 $ged_{to}$ 小，如果更小才将 $ged_{to}$ 更新为 $i$ ；

而当 $tp_{to} < tp_{nx} + 1$ 时，即从 $i$ 这条边更新 $tp_{to}$ 能使 $tp_{to}$ 更大（此边应该被更新使其满足拓扑序）时：

$$ tp_{to} = tp_{nx}+1,\  ged_{to} = i $$

即更新点 $to$ 的拓扑序 $tp_{to}$ 的同时更新 $ged_i$ 。

这样边记录边拓扑序后，答案就为 $  \max_{i=1}^{n}\{ ged_{i} \} $ ，时间复杂度为 $O(n+m)$ ，对于此题非常优。

注：[**这**](https://www.luogu.com.cn/article/ih7scq62) 是 @[EnochWenzhou](https://www.luogu.com.cn/user/40262) 大佬的题解，其中 代码的 `ID[]` 与正文的 $id[]$ 即本文中的 $ged_{i}$ ，代码的 `id[]` 即本文边的编号，因为这位大佬使用邻接表存图，但是本文题解使用链式前向星存图，故能直接得到编号，而且这位大佬的判断多拓扑序方式也有点不一样。部分细节于代码注释给出。

## Code

```cpp
#include<bits/stdc++.h>
#define N 100005 
using namespace std;
struct Edge{
	int next, to;
}edge[N<<2]; //链式前向星
int head[N], cnt, n, m, ind[N], k, tp[N], ged[N]; //同正文
bool flag=1; //用于指示是否有多个拓扑序
void AddEdge(int from, int to){ 
	edge[++cnt].next = head[from];
	edge[cnt].to = to;
	head[from] = cnt; //如果你的样例1输出3，可以检查你的边的编号是否从1开始
}
void toposort(){ //BFS 跑拓扑序
	queue<int> q;
	for(int i=1; i<=n; i++){
		if(ind[i]==0){ q.push(i);}
	} 
	while(!q.empty()){
		if(q.size()>1){ flag=0; return ; }  
		int nx= q.front(); q.pop(); tp[nx]=++k;
		for(int i=head[nx]; ~i; i=edge[i].next){
			int to = edge[i].to;
			if(tp[to]==tp[nx]+1) ged[to]=min(ged[to],i);
			if(tp[to]<tp[nx]+1) tp[to]=tp[nx]+1,ged[to]=i; //同正文
			ind[to]--;
			if(!ind[to]){ q.push(to); }
		}
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	memset(head, -1, sizeof head);
	cin >> n >> m;
	for(int i=1,u,v; i<=m; i++){
		cin >> u >> v;
		AddEdge(u,v);
		ind[v]++;
	}
	toposort();
	int ans=0;
	if(flag){
		for	(int i=1; i<=n; i++) ans = max(ans,ged[i]);
		cout<<ans;
	} 
	else cout<< -1;
	return 0;
}
```

---

## 作者：Sine_Func (赞：2)

# [CF645D](https://www.luogu.com.cn/problem/CF645D)
## 思路
二分 $+$ 拓扑排序

容易发现答案具有单调性，因为知道了更多的比赛结果只会让排序更加容易。对于每一次二分，对前 $mid$ 条边进行拓扑排序。当队列中有多个元素时，就意味着顺序不唯一。

## code


```cpp
#include<bits/stdc++.h>
#define AC return 0;
using namespace std;
int n, m, u[100010], v[100010], in[100010], sum;
bool check(int x) {
	vector<int>g[100010];
	queue<int>q;
	sum = 0;
	memset(in, 0, sizeof(in));
	for (int i = 1; i <= x; i++) {//建图，统计入度
		g[u[i]].push_back(v[i]);
		in[v[i]]++;
	}
	for (int i = 1; i <= n; i++)
		if (!in[i]) {
			q.push(i);
			++sum;
		}
	cout << "\n";
	while (!q.empty()) {//拓扑排序
		if (q.size() > 1)return 0;
		int l = q.front();
		q.pop();
		for (int i = 0; i < g[l].size(); i++) {
			in[g[l][i]]--;
			if (!in[g[l][i]]) {
				q.push(g[l][i]);
				++sum;
			}
		}
	}
	if (sum != n)return 0;
	return 1;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> u[i] >> v[i];
	if (!check(m)) {//统计能否排出顺序
		cout << -1;
		return 0;
	}
	int l = 1, r = m;
	while (l < r) {//二分
		int mid = ((l + r) >> 1);
		if (check(mid))r = mid;
		else l = mid + 1;
	}
	cout << l;
	AC;
}
```

---

## 作者：concert_B (赞：2)

# CF645D 题解
#### ~~啥玩意儿？并查集？~~——from 蒟蒻 BTJ
## 二分答案+[拓扑排序](https://www.luogu.com.cn/problem/B3644)
 
 设机器人 $u$ 打败机器人 $v$。
 
 则建立一条自 $u$ 向 $v$ 的有向边。
 
 二分边数 $m$，剩下的交给 topo 板板。
 
 复杂度 $O(n\log n)$，刚好 ~~haha~~。
## 拓扑排序

基本的步骤：

计算每个点的入度。

- 入度为 $0$ 就加入队列。

- 当队列不为空则循环：

	- 取出队首元素并输出。

	- 遍历队首元素的连边，对应节点的入度 $−1$。

	- 当对应的节点入度为 $0$ 就加入队列。

——from [LV06](https://www.luogu.com.cn/user/558597) 巨佬的[博客](https://www.luogu.com.cn/blog/558597/b3644-post) OZR。
## 样例解释
四条边：

![](https://cdn.luogu.com.cn/upload/image_hosting/ic6xxx12.png)

五条边：

![](https://cdn.luogu.com.cn/upload/image_hosting/ys5zqw88.png)

可见四条边即可。
## CODE:

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#define int long long
const int N=1e5+5;
int n,m;
std::pair<int,int> p[N];
std::queue<int> q;
std::vector<int> e[N];
bool vis[N];
int in[N];
bool check(int x){
	memset(in,0,sizeof(in));
	memset(vis,false,sizeof(vis));
	while(!q.empty())	q.pop();
	for(int i=0;i<N;i++)	e[i].clear();
	for(int i=1;i<=x;i++){
		e[p[i].first].push_back(p[i].second);
		in[p[i].second]++;
	}
	for(int i=1;i<=n;i++){
		if(in[i])	continue;
		vis[i]=true;
		q.push(i);
	}
	while(!q.empty()){
		if(q.size()>1)	return false;
		int u=q.front();
		q.pop();
		for(std::vector<int>::iterator it=e[u].begin();it!=e[u].end();it++){
			in[*it]--;
			if(!in[*it]&&!vis[*it]){
				vis[*it]=1;
				q.push(*it);
			}
		}
	}
	return true;
}
signed main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0),std::cout.tie(0);
	std::cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		std::cin>>u>>v;
		p[i]=std::make_pair(u,v);
	}
	int l=1,r=m;
	bool f=false;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))	r=mid-1,f=1;
		else	l=mid+1;
	}
	if(f)	std::cout<<r+1;
	else	std::cout<<-1;
	return 0;
}
```
## 后记
 本来真打算打并查集的，后来发现太长~~太难打~~，就不打惹。

有没有巨佬打个并查集让我涨涨见识。
## 完结撒花~

---

## 作者：凤凰工作室 (赞：0)

### Problem

有 $N$ 个机器人，给出 $M$ 组关系，表示两个机器人的能力关系，问至少需要前几组关系可以确定所有机器人的排名。

### Solution

由于是求最少的前几组关系，而关系越少越难确定排名，关系越多越容易确定，不难发现本题满足单调性，考虑二分。

那么给出关系要求总排名的题，就应该使用拓扑排序实现。

### Topological Sorting

对于一个有向图，每次从一个入度为 $0$ 的节点开始，删除它和它的所有出边，并将它存储到拓扑序列里。

如果图存在环，或者关系不足，那么拓扑排序将无法遍历所有节点（但是本题不考虑环，因为机器人的能力不可能成为一个环）。

剩下的拓扑序列就是机器人的总排名。

### Code

```Cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;

int x[100005],y[100005],d[100005];
queue<int>q;

namespace Graph //链式前向星存图
{
    int h[100005],to[100005],nxt[100005],idx;
    void init_graph(void)
    {
        while(!q.empty())
            q.pop();
        memset(d,0,sizeof(d));
        memset(h,-1,sizeof(h));
        idx=0;
    }

    void add_edge(int u,int v)
    {
        to[idx]=v;
        nxt[idx]=h[u];
        h[u]=idx++;
    }
}

using namespace Graph;

bool check(int k)
{
    init_graph();
    for(int i=1;i<=k;i++)
    {
        add_edge(x[i],y[i]);
        d[y[i]]++;//存每个点的入度
    }
    for(int i=1;i<=n;i++)
        if(d[i]==0)q.push(i);
    if(q.size()>1||q.size()==0)return false;
    while(!q.empty())//用 BFS 遍历
    {
        int t=q.front();
        q.pop();
        for(int i=h[t];i!=-1;i=nxt[i])
        {
            int j=to[i];
            d[j]--;//删边
            if(!d[j])//入度为 0
                q.push(j);
        }
        if(q.size()>1)return false;
    }
    return true;
}

signed main(void)
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>x[i]>>y[i];
    int l=1,r=m,mid;
    while(l<r)//二分
    {
        mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    if(check(l))
        cout<<l;
    else
        cout<<-1;
    return 0;
}
```

---

## 作者：yh888 (赞：0)

## [CF645D](https://www.luogu.com.cn/problem/CF645D) 题解

### 题目大意
给出 $m$ 场关于 $n$ 个机器人的比赛胜负情况，求最少通过前几场能推出所有机器人的强弱级别（即对于任意两个机器人都能知道谁强谁弱）。

### 思路
容易想到 **拓扑排序**。$\\$
如果入度为 $0$ 时的数量大于一，则表示两个点的强弱情况不能确定。$\\$
遍历比赛场数，每次跑一边拓扑，判断是否符合题意，时间复杂度约为 $O(n\times m)$。$\\$
观察数据范围发现会喜提 TLE。

优化复杂度，考虑用**二分**。$\\$用二分答案找到符合题意的最小比赛场数，时间复杂度 $O(n\log n)$。

### Code
```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,u[N],v[N],d[N],ans=-1;
vector<int> G[N];
bool check(int x){
	queue<int> q;
	for(int i=1;i<=n;i++){		//记得清空 
		d[i]=0;
		G[i].clear();
	}
	for(int i=1;i<=x;i++){
		G[u[i]].push_back(v[i]);		//存图 
		d[v[i]]++;
	}
	int c=0;		//记录有多少个点加入到队列当中 
	for(int i=1;i<=n;i++)
		if(!d[i]){
			q.push(i);
			c++;
		}
	while(q.size()){
		if(q.size()>1)		//当前情况大于一，不符合题意 
			return 0;
		int now=q.front();
		q.pop();
		for(auto it:G[now]){
			if(!--d[it]){
				c++;
				q.push(it);
			}
		}
	}
	if(c!=n)		//跑完拓扑却没有n个点 
		return 0;
	return 1;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>u[i]>>v[i];
	int l=1,r=m;
	while(l<=r){		//二分答案 
		int mid=(l+r)>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}else
			l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

~~本蒟蒻的第一篇题解~~，祝大家 AC 愉快！

---

## 作者：qiuzijin2026 (赞：0)

# Robot Rapping Results Report

## [题面](https://www.luogu.com.cn/problem/CF645D)

## 思路

二分+拓扑排序。

我们可以发现答案具有单调性，因为如果知道了更多场比赛的结果只会让级别排名更容易，所以本题可以二分答案。

我们发现级别排名不唯一的情况就是同时存在多个入度为 $1$ 的点，此时答案不成立。

写一遍拓扑排序的模板就行了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int to;
	int next;
}b[100005];
int h[100005],l;
void jb(int x,int y){
	b[++l].to=y;
	b[l].next=h[x];
	h[x]=l;
}
int n,m;
int u[100005],v[100005];
int rd[100005];
queue<int> q;
bool tp(int x){
	l=0;
	memset(h,0,sizeof(h));
	memset(b,0,sizeof(b));
	memset(rd,0,sizeof(rd));
	for(int i=1;i<=x;i++){
		jb(u[i],v[i]);
		rd[v[i]]++;
	}
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++) if(rd[i]==0) q.push(i);
	if(q.size()>1) return false;
	int tmp;
	while(!q.empty()){
		if(q.size()>1) return false;
		tmp=q.front();
		q.pop();
		for(int i=h[tmp];i;i=b[i].next){
			rd[b[i].to]--;
			if(rd[b[i].to]==0) q.push(b[i].to);
		}
		if(q.size()>1) return false;
	}
	return true;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&u[i],&v[i]);
	int l=1,r=m,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(tp(mid)) r=mid;
		else l=mid+1;
	}
	if(tp(l)) printf("%d",l);
	else printf("-1");
	return 0;
}

```

---

## 作者：Dream__Sky (赞：0)

首先我们知道只要边数越多，机器人间的关系就越能够确定，具有单调性，我们先考虑二分。

接下来我们考虑如何判断二分枚举的前 $i$ 条边，我们可以转化为一个有向图，一条“强弱”关系就相当于一条有向边，跑拓扑排序即可。

如果跑完一遍拓扑排序后，仍有一个机器人的入度不为  $0$，说明它还不能确定。

复杂度 $O(n \log n)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10; 
int n,m,U[N],V[N],in[N],vis[N];
vector<int> e[N];
bool check(int x)
{
	queue<int> q;
	memset(in,0,sizeof in);
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++) e[i].clear();
	for(int i=1;i<=x;i++) in[V[i]]++,e[U[i]].push_back(V[i]);
	for(int i=1;i<=n;i++) if(!in[i]) vis[i]=1,q.push(i);
	while(!q.empty())
	{
		if(q.size()>1) return 0;
		int u=q.front();
		q.pop();
		for(auto v:e[u])
		{
			in[v]--;
			if(!in[v]&&!vis[v]) vis[v]=1,q.push(v);
		}
	}
	return 1;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>U[i]>>V[i];
	
	int l=1,r=m,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	if(!ans) cout<<-1;
	else cout<<ans;
	return 0;
}

```


---

## 作者：COsm0s (赞：0)

二分和拓扑排序。

一条“强-弱”关系可以转化为一条有向边。那么把整张图存下来后，只要入度为 $0$ 的数量不唯一时，强弱关系不唯一，也就无解。反之，在拓扑过程中如果入度为 $0$ 的边始终只有一条，那么关系唯一确定，强弱关系可以判别。

二分边数即可。

复杂度 $\Theta(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define REP(i, a, b) for(int i = (a); i <= (b); i ++)
#define DOW(i, a, b) for(int i = (a); i >= (b); i --)
using namespace std;
namespace Cosmos {
	const int N = 2e5 + 5;
	int n, m, tot, h[N], in[N], u[N], v[N];
	bool vis[N];
	struct Edge {
		int to, nxt;
	} e[N];
	void add(int u, int v) {
		e[++ tot].to = v;
		e[tot].nxt = h[u];
		h[u] = tot;
	}
	bool Topo() {
		queue<int> q;
		REP(i, 1, n) if(!in[i]) q.push(i), vis[i] = true;
		while(!q.empty()) {
			if(q.size() > 1) return false;
			int x = q.front();
			q.pop();
			for(int i = h[x]; i; i = e[i].nxt) {
				int y = e[i].to;
				in[y] --;
				if(!in[y] && !vis[y]) q.push(y), vis[y] = true;
			}
		}
		return true;
	}
	bool check(int mid) {
		tot = 0;
		memset(in, 0, sizeof in);
		memset(vis, 0, sizeof vis);
		memset(h, 0, sizeof h);
		memset(e, 0, sizeof e);
		REP(i, 1, mid) add(u[i], v[i]), in[v[i]] ++;
		return Topo();
	}
	int main() {
		cin >> n >> m;
		REP(i, 1, m) cin >> u[i] >> v[i];
		int l = 1, r = m, ans = 0;
		while (l <= r) {
			int mid = l + r >> 1;
			if (check(mid)) r = mid - 1, ans = mid;
			else l = mid + 1;
		}
		if(!ans) cout << -1 << '\n';
		else cout << l << '\n';
		return 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) Cosmos::main();
	return 0;
}
```


---

## 作者：wizardMarshall (赞：0)

[题面](https://www.luogu.com.cn/problem/CF645D)

## 题意

能否通过两两强弱关系确定每个人的唯一强弱等级，以及最少通过几对强弱关系就可以看出。

## 思路


看到这道题容易想到拓扑，一对强弱关系转换成一条有向边，通过拓扑可以确定数据是否合法。

也就是说，如果存在环或者两个连通块。这种情况明显是不合法的。

我们再来看以下例子：

![不确定关系](https://cdn.luogu.com.cn/upload/image_hosting/k88wk9k3.png)

可以看出，$(1,2)$，$(1,3)$，$(2,4)$，$(3,4)$ 这些点对已经有了强弱关系。这种情况下是存在强弱关系的，但**并不唯一**。$(2,3)$ 就没有直接或间接的关系能够推导出他们之间的强弱关系。

因此，拓扑排序过程中的任意时刻，都不能出现**两个及以上的入度为零的点**。否则，我们是不知道这两个点谁小谁大的。

----

说完了拓扑判断合法性，我们还有一个问题，就是最少几对强弱关系就一定能够推导出等级。由于整体方案合法，多一条边显然不会变坏，满足单调性，考虑二分。


## 代码

```c++

#include <bits/stdc++.h>
using namespace std;

pair <int, int> xy[100005];

vector <int> edge[100005];

int in[100005];

int n, m;
bool check(int x) {
	
	queue <int> q;
	for (int i = 1; i <= n; i++) {//每次check之前一定要初始化
		edge[i].clear();
		in[i] = 0;
	}
	for (int i = 1; i <= x; i++) {
		edge[xy[i].first].push_back(xy[i].second);
		in[xy[i].second]++;
	}
	for (int i = 1; i <= n; i++) {
		if (!in[i]) {
			q.push(i);
		}
	}
	int cnt = 0;
	while (!q.empty()) {
		if (q.size() > 1)return 0;//任意时刻入度为0的点都不能大于1个
		int f = q.front();q.pop();
		cnt++;
		for (auto i :edge[f]) {
			in[i]--;
			if (!in[i]) {//正常拓扑加点
				q.push(i);
			}
		}
	}
	if (cnt != n)return 0;//如果有一些点还有入度，就是有环
	return 1;
}
signed main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &xy[i].first, &xy[i].second);
	}
	if (!check(m)) {//最开始判断合法性，如果所有边加上还是不能得出确定结果或者本身就不合法，坑定-1
		cout << -1;
		return 0;
	}
	int l = 1, r = m, temp = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (check(mid)) {//二分找最小满足条件的点
			r = mid - 1;
			temp = mid;
		}else l = mid + 1;
	}cout << temp;
	return 0;
}



```

---

