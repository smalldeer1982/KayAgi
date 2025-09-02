# Berland Army

## 题目描述

There are $ n $ military men in the Berland army. Some of them have given orders to other military men by now. Given $ m $ pairs ( $ x_{i} $ , $ y_{i} $ ), meaning that the military man $ x_{i} $ gave the $ i $ -th order to another military man $ y_{i} $ .

It is time for reform! The Berland Ministry of Defence plans to introduce ranks in the Berland army. Each military man should be assigned a rank — integer number between $ 1 $ and $ k $ , inclusive. Some of them have been already assigned a rank, but the rest of them should get a rank soon.

Help the ministry to assign ranks to the rest of the army so that:

- for each of $ m $ orders it is true that the rank of a person giving the order (military man $ x_{i} $ ) is strictly greater than the rank of a person receiving the order (military man $ y_{i} $ );
- for each rank from $ 1 $ to $ k $ there is at least one military man with this rank.

## 样例 #1

### 输入

```
5 3 3
0 3 0 0 2
2 4
3 4
3 5
```

### 输出

```
1 3 3 2 2 
```

## 样例 #2

### 输入

```
7 6 5
0 4 5 4 1 0 0
6 1
3 6
3 1
7 5
7 1
7 4
```

### 输出

```
2 4 5 4 1 3 5 
```

## 样例 #3

### 输入

```
2 2 2
2 1
1 2
2 1
```

### 输出

```
-1
```

# 题解

## 作者：suxxsfe (赞：6)

http://codeforces.com/problemset/problem/883/B  

给有向图，某些点点权已知，确定其他未知点权，使得：  

1. 所有点权在 $[1,k]$ 之间；
2. 对于边 $x\rightarrow y$，$x$ 的点权大于 $y$ 的；
3. 对于所有的 $i\in [1,k]$，都有至少一个点点权为 $i$。

----------------------------  

考虑先正反两边找到每一个点的最大、最小点权，记为 $[l_u,r_u]$。然后对于每个 $i$ 确定哪些点的点权为 $i$，使得在不违反条件 2 的情况下尽量去满足条件 3。  
此时点权 $[1,i-1]$ 必然已经被分配完，记 $S$ 为所有 $l_u\le i$ 的 $u$ 的集合。  
那么对于所有的 $r_u=i$ 的 $u$，都要分配点权为 $i$。因为如果分配成 $j<i$ 的话，由于存在已经被分配成 $j$ 的点，可能会产生冲突违反条件 2。而显然把他们分配为 $i$ 也更符合条件 3。  
若不存在 $r_u=i$ 的点，则需要取一个 $r_u>i$ 的点分配为 $i$。此时对于条件 3，显然取 $r_u$ 最小的最优。  
如果此时仍然没有 $r_u>i$ 的点，则为无解。  

```cpp  
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<utility>
#include<set>
#define reg register
#define EN puts("")
#define INT_INF ((int)0x3f3f3f3f)
#define LL_INF ((long long)0x3f3f3f3f3f3f3f3f)
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=getchar();}
	return y?x:-x;
}
#define N 200006
#define M 200006
struct Graph{
	int fir[N],nex[M],to[M],tot;
	inline void add(int u,int v){
		to[++tot]=v;
		nex[tot]=fir[u];fir[u]=tot;
	}
};
Graph G,T;
int n,m,k;
int val[N];
int in[N],out[N];
int min[N],max[N],id[N];
int left,right,que[N];
inline int topo1(){
	left=0;right=-1;
	for(reg int i=1;i<=n;i++)if(!out[i]) min[i]=val[i]?val[i]:1,que[++right]=i;
	reg int u,i,v;while(left<=right){
		u=que[left++];
		for(i=T.fir[u];i;i=T.nex[i]){
			v=T.to[i];
			min[v]=std::max(min[v],min[u]+1);
			if(!--out[v]){
				if(val[v]&&val[v]<min[v]) return 1;
				min[v]=std::max(min[v],val[v]);
				que[++right]=v;
			}
		}
	}
	for(reg int i=1;i<=n;i++)if(out[i]) return 1;
	return 0;
}
inline int topo2(){
	left=0;right=-1;
	for(reg int i=1;i<=n;i++){
		if(!in[i]) max[i]=val[i]?val[i]:k,que[++right]=i;
		else max[i]=k;
	}
	reg int u,i,v;while(left<=right){
		u=que[left++];
		for(i=G.fir[u];i;i=G.nex[i]){
			v=G.to[i];
			max[v]=std::min(max[v],max[u]-1);
			if(!--in[v]){
				if(val[v]&&val[v]>max[v]) return 1;
				if(val[v]) max[v]=std::min(max[v],val[v]);
				que[++right]=v;
			}
		}
	}
	for(reg int i=1;i<=n;i++)if(in[i]) return 1;
	return 0;
}
int ans[N];
std::set<std::pair<int,int> >set;
int main(){
	n=read();m=read();k=read();
	for(reg int i=1;i<=n;i++) val[i]=read();
	for(reg int u,v,i=1;i<=m;i++){
		u=read();v=read();
		in[v]++;out[u]++;
		G.add(u,v);T.add(v,u);
	}
	if(topo1()||topo2()) return puts("-1"),0;
	for(reg int i=1;i<=n;i++)if(min[i]>max[i]) return puts("-1"),0;
//		for(reg int i=1;i<=n;i++) printf("%d : [%d %d]\n",i,min[i],max[i]);
	for(reg int i=1;i<=n;i++) id[i]=i;
	std::sort(id+1,id+1+n,[](reg int a,reg int b){return min[a]==min[b]?max[a]<max[b]:min[a]<min[b];});
	for(reg int now=1,i=1;i<=k;i++){
		while(now<=n&&min[id[now]]<=i) set.insert(std::make_pair(max[id[now]],id[now])),now++;
		int have=0;
		while(!set.empty()){
			int id=(*set.begin()).second;
			if(have&&max[id]>i) break;
			ans[id]=i;have=1;
			set.erase(set.begin());
		}
		if(!have) return puts("-1"),0;
	}
	for(reg int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Twig_K (赞：5)

首先，如果图中存在环那么一定无解，想到用拓扑排序判断是否所有点都进过队列。

我们还可以通过两遍拓扑排序，求出每个点权值的上界和下界。先在原图上跑拓扑排序：

- 入度为 $0$ 的点，它的权值的上界就是 $K$。
- 否则，它的权值应该严格小于它的所有前驱的权值。可以很容易地在删边时计算。
- 在拓扑排序结束后，如果答案不在 $[1,K]$ 范围内，或是原本确定权值的点值被修改了，那么无解。以及上面提到的拓扑排序遍经不完，存在环的无解情况。

然后在反图上也跑一遍拓扑排序，这一次求的是每个点的下界。我的做法是把值域倒过来，扔进同样的函数算，再倒回来得出下界。

现在我们求出了每个点权值的上界和下界（权值已经确定的点，上界和下界相等）$[l_i,r_i]$，现在要寻找一种为每个点分配权值的方案，使得 $1$ 到 $K$ 每种权值都存在。

把所有上下界的区间按照下界排序，从 $1$ 到 $K$ 枚举权值 $i$ ，用堆维护所有下界不超过 $i$ 且还没有被赋值的区间集合。对于每个 $i$：

- 如果堆为空，意味着并没有能用的下界不超过 $i$ 的区间，无解。
- 如果堆内有上界小于等于 $i$ 的区间，把对应的这些点都赋值为 $i$ 并把它们弹出。事实上，堆中不会存在上界小于 $i$ 的区间，因为已经在枚举 $i-1$ 的时候弹出堆了。
- 如果堆内没有上界小于等于 $i$ 的区间，取一个上界最小的赋值为 $i$ 并弹出。

## 代码

完整代码见[提交记录](https://codeforces.com/problemset/submission/883/297199980)。

```cpp
bool topo(vector<int> *ve,int *t,int *res)
{
    For(i,1,n) res[i]=t[i]?t[i]:K+1;//如果已经有权值，初始值就是点权
    For(u,1,n) for(int v:ve[u]) ++d[v];
    int num=0;
    queue<int> q;
    For(i,1,n) if(!d[i]) res[i]=min(res[i],K),q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();++num;
        for(auto v:ve[u]){
            res[v]=min(res[v],res[u]-1);
            if(!--d[v]) q.push(v);
        }
    }//以下是拓扑排序无解的情况。
    if(num<n) return false;
    //对于 res[i]!=t[i] : 拓扑过程中正常取min，结束后如果权值经过若干次取min发生变化，说明非法。
    For(i,1,n) if(res[i]<1||res[i]>K||t[i]&&res[i]!=t[i]) return false; return true;
}
signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int u,v;
    cin>>n>>m>>K;
    For(i,1,n) cin>>v1[i],v2[i]=v1[i]?K+1-v1[i]:0;//v2：倒序后的点权，与反图对应。
    For(i,1,m) cin>>u>>v,g1[u].push_back(v),g2[v].push_back(u);

    if(!topo(g1,v1,d1)||!topo(g2,v2,d2)) NO;
    For(i,1,n) a[i]=(node){d1[i],K+1-d2[i],i};//K+1-d2[i]: 把点权倒回来
    sort(a+1,a+1+n,[&](node xx,node yy){ return xx.dn<yy.dn; });

    for(int i=1,p=1;i<=K;i++)
    {
        while(p<=n&&a[p].dn<=i) q.push(mk(a[p].up,a[p].id)),p++;//排序后双指针
        bool flag=false;
        while(!q.empty()&&q.top().fi<=i) flag=true,ans[q.top().se]=i,q.pop();
        if(flag) continue;
        if(q.empty()) NO;
        else ans[q.top().se]=i,q.pop();
    }
    For(i,1,n) cout<<ans[i]<<' ';
}
```

---

## 作者：xiaoxiaoxia (赞：1)

## 题目大意
有 $n$ 个士兵，现在要给他们赋军衔 $1-k$，给 $m$ 条边，每条边 $u$ 到 $v$ 表示 $u$ 可以命令 $v$,即 $u$ 的军衔比 $v$ 大。输出赋衔方案。
关键的要求：
1. 输入给定了一些士兵的军衔。只有部分士兵的军衔可供你修改。
2. $1-k$ 这 $k$ 个军衔每个都要有人。即对于任意一个军衔等级 $i$，$n$ 个人中必须要有人获得这个军衔。
## 思路概述
这题的要求非常复杂，我大概想出了一个贪心的思路：
先正反跑两次拓扑排序，得到在考虑不考虑每个军衔情况下的，每个人的最高和最低可能军衔。然后以最高可能军衔为第一关键字和最低可能军衔为第二关键字排序。由于父亲的最高可能军衔一定比儿子大，所以父亲一定在前面。然后贪心式地赋军衔就可以了，注意一下如果第 $i$ 个人的 $low$ 等于目前贪心的 $top$ 那么也要赋值为 $top$ 就可以了。
我们说得更加学术一点来说：就是对于一个图来说所有点按 $L$ 排序后，将 $1 \dots k$ 从小到大分配给各点，假设遍历到 $i$，$\left[1,i-1\right]$ 都已经分配完毕，用一个集合 $S$ 维护所有未分配的且 $L\leq i$ 的点。对于 $S$ 中所有 $R\leq i$ 的点，显然全分配为 $i$ 会更优，这是因为如果分配为 $j<i$ 的话，可能会与之前的点违背条件 $2$。而对于$S$中所有 $R>i$ 的点，我们尽量先不分配一定不会影响条件 $2$，这是由于之前拓扑排序保证的。需要注意如果不存在 $R \leq i$ 的点的话，那么必须从 $R>i$ 中选择一个，显然选择一个 $R$ 小的会使条件 $1$ 更优。
## 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=210000;
int n,m,k;
vector<int> head[MAXN];
vector<pair<int, int> > rnk[MAXN];
int solid[MAXN];
int low[MAXN],ans[MAXN];
int high[MAXN];
int in[MAXN];
int flag=1;
struct Edge
{
	int x,y;
	Edge() {}
}edge[MAXN];
void Input()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&solid[i]);
	}
	int u,v;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d",&edge[i].x,&edge[i].y);
	}
}
void init()
{
	for(int i=1;i<=n;++i)
	{
		head[i].clear();
		in[i]=0;
	}
}
void toposort(int now[],int type)
{
	queue<int > q;
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		if(!in[i])
		{
			q.push(i);
			++cnt;
		}
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<head[u].size();++i)
		{
			int v=head[u][i];
			if(type<0)
			{
				now[v]=min(now[v],now[u]-1);
			}
			else
			{
				now[v]=max(now[v],now[u]+1);
			}
			if(--in[v]<=0)
			{
				++cnt;
				q.push(v);
			}
		}
	}
	if(cnt!=n)
	{
		flag=0;
	}
}
void work()
{
	int u,v;
	flag=1;
	init();
	for(int i=1;i<=n;++i)
	{
		if(solid[i]) high[i]=solid[i];
		else high[i]=k;
	}
	for(int i=1;i<=m;++i)
	{
		u=edge[i].x,v=edge[i].y;
		head[u].push_back(v);
		in[v]++;
	}
	toposort(high,-1);
	if(flag==0)
	{
		printf("-1\n");
		return;
	}
	init();
	for(int i=1;i<=n;++i)
	{
		if(solid[i]) low[i]=solid[i];
		else low[i]=1;
	}
	for(int i=1;i<=m;++i)
	{
		u=edge[i].y;v=edge[i].x;
		head[u].push_back(v);
		in[v]++;
	}
	toposort(low,1);
	if(flag==0)
	{
		printf("-1\n");
		return;
	}
	
	for(int i=1;i<=n;++i)
	{
		if(low[i]>high[i])
		{
			printf("-1\n");return;
		}
	}
	int top=k;
	for(int i=1;i<=k;++i) rnk[i].clear();
	for(int i=1;i<=n;++i)
	{
		rnk[high[i]].push_back(make_pair(-low[i],i));
	}
	set< pair<int,int> > S;
	set< pair<int,int> >::iterator it;
	for(int i=0;i<rnk[k].size();++i)
	{
		S.insert(rnk[k][i]);
	}
	pair<int ,int > tmp;
	while(top)
	{
		if(S.empty())
		{
			printf("-1\n");
			return;
		}
		it=S.begin();
		tmp=*it;
		ans[tmp.second]=top;
		S.erase(it);
		while(1)
		{
			it=S.begin();
			tmp=*it;
			if(-tmp.first<top) break;
			ans[tmp.second]=top;
			S.erase(it);
		}
		--top;
		for(int i=0;i<rnk[top].size();++i)
		{
			S.insert(rnk[top][i]);
		}
	}
	while(!S.empty())
	{
		tmp=*it;
		ans[tmp.second]=1;
		S.erase(it);
	}
	for(int i=1;i<=n;++i)
		printf("%d ",ans[i]);
	printf("\n");
}
int main()
{
	Input();
	work();
	return 0;
}
```

---

