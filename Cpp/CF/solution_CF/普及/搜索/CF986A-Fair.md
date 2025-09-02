# Fair

## 题目描述

一些公司将在Byteland举办商品交易会（or博览会？）。在Byteland有 $n$ 个城市，城市间有 $m$ 条双向道路。当然，城镇之间两两连通。
Byteland生产的货物有 $k$ 种类型，每个城镇只生产一种。
为了举办商品交易会，你必须至少带来 $s$ 种不同类型的商品。将货物从 $u$ 镇带到城镇 $v$ 将花费 $d(u,v)$ 的费用，其中 $d(u,v)$ 是从 $u$ 到 $v$ 的最短路径的长度。
路径的长度是这个路径中的道路的数量。              
组织者将支付所有的运输费用，但他们可以选择从哪些城镇带来货物。现在他们想计算每个城镇举办商品交易会的最小费用。

## 样例 #1

### 输入

```
5 5 4 3
1 2 4 3 2
1 2
2 3
3 4
4 1
4 5
```

### 输出

```
2 2 2 2 3 
```

## 样例 #2

### 输入

```
7 6 3 2
1 2 3 3 2 2 1
1 2
2 3
3 4
2 5
5 6
6 7
```

### 输出

```
1 1 1 2 2 1 1 
```

# 题解

## 作者：Namelessone (赞：11)

根据k的大小考虑枚举颜色，将每个颜色当成一个超级源点，设当前颜色为x，所有颜色为x的节点与这个颜色形成的超级源点距离都为0，将这些距离为0的节点放入队列，进行BFS，更新dis[i][c]数组(i代表节点编号，c代表颜色) 经过O(n)复杂度的BFS后可以得到所有点与当前颜色形成的超级源点的距离。
所有颜色都进行BFS操作后可以得到所有点与所有颜色之间的最短距离。
最后将每个节点的颜色距离进行排序，取前s个就是当前节点的答案
代码:

```
#include<bits/stdc++.h>
using namespace std;
int const maxn=1e5+10;
vector<int> v[maxn],e[maxn];
int dis[maxn][110],a[maxn];
queue<int> q;
int main(){
    int n,m,k,s;
    scanf("%d%d%d%d",&n,&m,&k,&s);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]),v[a[i]].push_back(i);
    for (int i=1;i<=m;i++) {
        int x,y;
        scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    memset(dis,-1,sizeof(dis));
    for (int c=1;c<=k;c++) {
        for (auto i:v[c]) {
            q.push(i);
            dis[i][c]=0;
        }
        while (!q.empty()) {
            int x=q.front();
            q.pop();
            for (auto i:e[x]) {
                if (dis[i][c]==-1) {
                    dis[i][c]=dis[x][c]+1;
                    q.push(i);
                }
            }
        }
    }
    int ans=0;
    for (int i=1;i<=n;i++){
        ans=0;
        sort(dis[i]+1,dis[i]+1+k);
        for (int j=1;j<=s;j++) {
            ans+=dis[i][j];
        }
        printf("%d ",ans);
    }

}


---

## 作者：_JC_ (赞：3)

先来介绍什么事nth_element（dalao可自动跳过）：
nth_elment是一个在algorithm中的函数。作用是将一个数组的前k位中的最小的s个由小到大调到前s位。
用法：nth_element（（数组名）+起始位，（数组名）+要排的数的个数，（数组名）+终止位）；

这一题中我们可以算每个点到每种货物的最短距离，再选择里面前s小的作为要拿的货物。其实这就等于算出每种货物到每个点的最短距离。
于是我们只要将每个点的信息push到一个Q里面，在运行一遍BFS，算出点与各种货物之间的最短路。
最后我们枚举某个点，再用nth_element去算一个点到每种货物中前s小的，它们之和便是该点的答案。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int INF=2e9;
struct d
{
    int hw,bs,now;//货物，此时步数，此时在的点
}node;
vector <int> V[100005];//存无向边
queue <d> Q;
int dis[100005][105],n,m,k,s,bs[100005],ans[105],da;//dis存某个点与某种货物间的最短路，bs存某点的货物种类
bool visit[100005][105];//存某个点与某种货物是否已经找到最短路
void BFS()
{
    int bs1,hw1,now1;
    while(!Q.empty())//当Q里没有东西，说明所有最短路都已算出
    {
        bs1=Q.front().bs;
        hw1=Q.front().hw;
        now1=Q.front().now;
        Q.pop();
        for(int i=0;i<V[now1].size();i++)
        {
            if(!visit[V[now1][i]][hw1])//点V[now1][i]（点）与hw1（货物）的最短路还没算出来，且先算出的最短路一点比后算的小
            {
                visit[V[now1][i]][hw1]=true;
                dis[V[now1][i]][hw1]=bs1+1;//此时的步数为到上一个点的步数+1
                node.hw=hw1;
                node.bs=bs1+1;
                node.now=V[now1][i];
                Q.push(node);
            }
        }
    }
    return ;
}
int main()
{
    scanf("%d %d %d %d",&n,&m,&k,&s);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=k;j++)
    dis[i][j]=INF;//初始化点与点间的距离
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&bs[i]);
        visit[i][bs[i]]=true;
        dis[i][bs[i]]=0;//某个点本身就有某种货物，其与该货物的距离为0
    }
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        V[a].push_back(b);
        V[b].push_back(a);
    }
    for(int i=1;i<=n;i++)//将每个点push进队列
    {
        node.hw=bs[i];
        node.now=i;
        node.bs=0;
        Q.push(node);
    }
    BFS();
    for(int i=1;i<=n;i++)
    {
        da=0;
        for(int j=1;j<=k;j++)
        ans[j]=dis[i][j];//用一个ans去暂存否则nth_element会出错
        nth_element(ans+1,ans+s+1,ans+k+1);//算前s小的最短路
        for(int j=1;j<=s;j++)
        da+=ans[j];
        printf("%d ",da);
    }
    return 0;
}```

---

## 作者：Aurora_Borealis_ (赞：1)

鉴于 $k$ 的数据范围非常小，容易想到对每种颜色处理最短路。

令 $dis_{i,j}$ 表示所有第 $i$ 种颜色的点，到 $j$ 号点的最短路。由于每种颜色点会有多个，考虑对于每种颜色设超级源点 $k_i$，对该颜色每个点连 $0$ 边，最后对于每个超级源点跑最短路即可。

至于统计答案我想到了 $2$ 种方法：排序，优先队列。排序和优先队列复杂度都是 $O(n\log n)$。

另外，因为边权为 $1$，最短路跑BFS就好辣。

---

## 作者：qjxqjx (赞：1)

## 题目思路：
用动态数组即可完成此题。每次输入放在数组后面，以此类推，维护颜色的距离，枚举点，注意是从小到大，取前 $s$ 个相加即可。

正确思路如下：  
1.按照颜色跑 BFS ;  
2.维护 $dis_{i,j}$ 表示颜色 $j$ 到点 $i$ 的最近距离；  
3.枚举所有的点 $i$，将 $dis_{i,j}$ 从小到大排序，取前 $s$ 个颜色相加，即为答案；

代码需要用到动态数组，由于是多重数据，每次都要清空，队列定义在函数里面，这样不用再去清空了，要注意 dis 数组为二维数组，数据开 $10^5+5$。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,k,s;
vector<int>nbr[maxn];//动态数组
int a[maxn];
int dis[maxn][105];
bool vis[maxn];
void bfs(int type){
	queue<int>q;
	memset(vis,0,sizeof(vis));//初始化
	for(int i=1;i<=n;i++){
		if(a[i]==type){
			dis[i][type]=0;
			vis[i]=true;
			q.push(i);
		}
	}
	while(!q.empty()){
		int cur=q.front();
		q.pop();
		for(int i=0;i<nbr[cur].size();i++){
			int next=nbr[cur][i];
			if(vis[next]==0){
				vis[next]=true;
				dis[next][type]=dis[cur][type]+1;
				q.push(next);
			}
		}
	}
	return ;
}
int main(){
	cin>>n>>m>>k>>s;
	memset(dis,0x3f,sizeof(dis));//初始化
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		nbr[x].push_back(y);
		nbr[y].push_back(x);
	}
	for(int i=1;i<=k;i++){
		bfs(i);
	}
	for(int i=1;i<=n;i++){
		sort(dis[i]+1,dis[i]+1+k);//从小到大排序
		int ans=0;
		for(int j=1;j<=s;j++){//循环 x 遍把答案累加再输出
			ans+=dis[i][j];
		}
		cout<<ans<<" ";
	}
	return 0;
}
```


---

## 作者：_HMZ_ (赞：0)

~~最近社贡一直在掉，来水一篇题解。~~

## 解题思路：

很容易想到一个 $n \times m$ 的算法，对于每一个点都跑一边广搜。

明显，这样会 TLE 到起飞。但是，通过仔细阅读题目，我们发现 $k$ 只有 $100$。

这说明了有很多的扩展是根本不必要的，因为每一个城市都必须要有 $s$ 种**不同的**商品。

于是，很明显想到一个思路，把所有颜色相同的放到一个队列里，对于每一个颜色跑一遍广搜。

但是，怎么统计答案呢？因为这道题的边权默认是 $1$，所以先搜索到的点就已经是最短路了。

于是我们开一个数组 $getans_{i,j}$ 表示第 $i$ 个节点 $j$ 种货物的最短路。

在扩展的时候将 $getans$ 处理一下就好了。

## AC代码：
 
```cpp
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
namespace io//这里是快读

using namespace io;
int n,m,k,S,head[100005],tot,color[100005],getans[100005][101],siz[1000005];
bool vis[100005],check[100005][101];
queue<pair<int,int> > q[105];//这里表示第i种颜色的队列，第一个值记录当前的点，第二个值记录距离。
struct node
{
	int y,nex;
}s[1000005];
inline void add(int i,int j)
{
	s[++tot].y=j,s[tot].nex=head[i];
	head[i]=tot;
}
inline void bfs(int c)//广搜，c表示当前搜索的颜色
{
	while(!q[c].empty())
	{
		int now=q[c].front().first,dis=q[c].front().second;
		q[c].pop();
		if(check[now][c])	continue;//check的含义是这个颜色有没有被搜索过，如果已经被扩展就没有意义了（因为是广搜，所以先搜索到的边权一定小）。
		getans[now][++siz[now]]=dis,check[now][c]=true;
		for(register int i=head[now];i;i=s[i].nex)
		{
			int y=s[i].y;
			if(!vis[y])
			{
				vis[y]=true;
				q[c].push(make_pair(y,dis+1));
			}
		}
	}
}
signed main()
{
	n=read(),m=read(),k=read(),S=read();
	for(register int i=1;i<=n;++i)
	{
		color[i]=read();
		q[color[i]].push(make_pair(i,0));//初始化队列。
	}
	for(register int i=1;i<=m;++i)
	{
		int u,v;
		u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	for(register int i=1;i<=k;++i)
	{
		bfs(i);
		for(register int j=1;j<=n;j++)
			vis[j]=false;
	}
	for(register int i=1;i<=n;++i)//统计答案，既然要求最小，那就从小到大排序，优先选距离小的货物。
	{
		int sum=0;
		sort(getans[i]+1,getans[i]+1+siz[i]);
		for(int j=1;j<=S;j++)
			sum+=getans[i][j];
		write(sum),putchar(' ');
	}
	flush();
	return 0;
}
```


---

