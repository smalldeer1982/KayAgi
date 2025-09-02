# [ARC035C] アットコーダー王国の交通事情

## 题目描述

高桥君是 Atcoder 王国的国王。Atcoder 王国包括$N$个城市（编号$1$~$N$）和$m$条双向的道路。每条道路都有长度。对于 Atcoder 王国中的任意城市 [A,B]，都可以保证从$A$到$B$有多条道路。

高桥君认为，Atcoder人的幸福在很大程度上取决于交通的便利性。为了找出人们的幸福程度，他想找到所有可能城市之间最短路径长度的总和$S$。

如果城市i和j之间的最短路径的长度为 D(i,j)，则

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT1215/c6cb071ff4a2960ab2be46d08083e517ddb9f45e.png)

高桥先生正计划建造K条新道路作为公共项目。这样的建设可能会导致多于两条或两条直接连接城市的道路，在这种情况下，现有道路将不会被拆除，而是会被增加。

您的任务是按照给定的顺序建造一条新路，并编写一个程序来计算上述每种施工的S。

## 样例 #1

### 输入

```
4 3
1 2 1
2 3 1
3 4 10
2
3 4 1
1 4 1```

### 输出

```
10
8```

## 样例 #2

### 输入

```
8 16
8 7 38
2 8 142
5 2 722
8 6 779
4 6 820
1 3 316
1 7 417
8 3 41
1 4 801
3 2 126
4 2 71
8 4 738
4 3 336
7 5 717
5 6 316
2 1 501
10
6 1 950
6 1 493
1 6 308
3 4 298
2 5 518
1 5 402
4 7 625
7 6 124
3 8 166
2 4 708```

### 输出

```
13649
12878
11954
11954
11280
11058
11058
8099
8099
8099```

# 题解

## 作者：_Kenma_ (赞：0)

# AT_arc035 解题报告

## 前言

怎么没人写 SPFA 的题解。

SPFA 它又活了。

~~其实写 SPFA 是因为我每次写 Floyd 都会写假。~~

## 思路分析

发现我们需要一个 $O(n^2k)$ 的优秀做法。

从每个点出发，暴力跑一次 SPFA，得到初始的最短路。

对于加边操作，连边后将连边的两点 $x,y$ 放入队列中，对于每个源点 $z$，暴力松弛 $z$ 的单源最短路。

这样做看起来是 $O(n^3k)$，但是实际上是 $O(n^2k)$ 的。

考虑证明。

对于每一个源点 $z$，我们抽象出以它为根的最短路树。

发现，每次加边 $(x,y,w)$ 时，它的最短路树至多变化 $x,y$ 路径上的一条边。

所以每个点的最短路在每一次松弛都至多变化一次。

因此，每个点对于每一次松弛都至多入队一次。

所以单次松弛的复杂度是线性的。

还是看图比较直观：

![](https://cdn.luogu.com.cn/upload/image_hosting/u2pi5enr.png)

然后就可以直接做了。

## 代码实现

只有一个 SPFA。

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,x,y,w,ans;
int head[200005],nxt[400005],targetx[400005],targetw[400005],tot;
void add(int x,int y,int w){
	tot++;
	nxt[tot]=head[x];
	head[x]=tot;
	targetx[tot]=y;
	targetw[tot]=w;
}
queue<int> q;
bool vis[200005];
int dis[405][405];
void spfa(int s){
	while(q.size()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=nxt[i]){
			int y=targetx[i],w=targetw[i];
			if(dis[s][y]>dis[s][x]+w){
				dis[s][y]=dis[s][x]+w;
				if(vis[y]) continue;
				q.push(y);
				vis[y]=1; 
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>w;
		add(x,y,w);
		add(y,x,w);
	}
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=n;i++){
		dis[i][i]=0;
	}
	for(int i=1;i<=n;i++){
		q.push(i);
		vis[i]=1;
		spfa(i);
	}
	cin>>k; 
	for(int i=1;i<=k;i++){
		cin>>x>>y>>w;
		add(x,y,w);
		add(y,x,w);
		for(int j=1;j<=n;j++){
			q.push(x);
			q.push(y);
			vis[x]=vis[y]=1;
			if(!vis[j]){
				q.push(j);
				vis[j]=1;
			}
			spfa(j);
		}
		ans=0;
		for(int j=1;j<=n;j++){
			for(int t=j+1;t<=n;t++){
				ans+=dis[j][t];
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：AkeRi (赞：0)

## Description

维护一张图，在线加边询问 $\sum_{i=1}^n\sum_{j=i+1}^{n}D(i,j)$，其中 $D(i,j)$ 表示点 $i$ 到点 $j$ 的最短路。

## Solution
来考虑怎么暴力草过去，如果对于每次加边都重新跑一遍 Floyd 显然过不去。

发现我们加完边之后只需要考虑加的边的影响即可，所以可以做到 $\text{O}(n^2)$ 维护最短路。所以只需要先跑一次 Floyd，然后对于每次加入的从 $u$ 连向 $v$ 的权值为 $w$ 边，只需要进行如下松弛即可：

$$D(i,j)=\min\{D(i,j),D(i,u)+D(v,j)+w,D(i,v)+D(u,j)+w\}$$

然后进行一个 $\text{O}(n^2)$ 的统计就做完了。时间复杂度 $\text{O}(n^3+k\times n^2)=\text{O}(n^2k)$ 显然对于 $n\le300,k\le400$ 没有什么压力。
```cpp
/*

by L1rs1ngzN1sLyr

*/
#include<bits/stdc++.h>
#define int long long
const int AI=1e3+9;
const int KI=1e6+2;
const int CI=1e7+3;
int read(){int x=0,w=1;char ch=0;while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}return x*w;}
int dis[AI][AI];
int n=read(),m=read();
signed main()
{
    memset(dis,0x3f,sizeof dis);
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read(),w=read();
        dis[u][v]=w;dis[v][u]=w;
        dis[u][u]=0,dis[v][v]=0;
    }
    for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dis[i][j]=std::min(dis[i][j],dis[i][k]+dis[k][j]);
    int k=read();
    while(k--)
    {
        int ans=0;
        int u=read(),v=read(),w=read();
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
        {
            dis[i][j]=std::min(dis[i][j],std::min(dis[i][u]+dis[v][j]+w,dis[i][v]+dis[u][j]+w));
        }
        for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) ans+=dis[i][j];
        std::cout<<ans<<'\n';
    }
}
```

---

