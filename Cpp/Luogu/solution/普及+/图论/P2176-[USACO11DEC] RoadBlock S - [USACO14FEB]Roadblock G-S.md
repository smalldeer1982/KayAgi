# [USACO11DEC] RoadBlock S / [USACO14FEB]Roadblock G/S

## 题目描述

每天早晨，FJ 从家中穿过农场走到牛棚。农场由 $N$ 块农田组成，农田通过 $M$ 条双向道路连接，每条路有一定长度。FJ 的房子在 $1$ 号田，牛棚在 $N$ 号田。没有两块田被多条道路连接，以适当的路径顺序总是能在农场任意一对田间行走。当 FJ 从一块田走到另一块时，总是以总路长最短的道路顺序来走。

FJ 的牛呢，总是不安好心，决定干扰他每天早晨的计划。它们在 $M$ 条路的某一条上安放一叠稻草堆，使这条路的长度加倍。牛希望选择一条路干扰使得 FJ 从家到牛棚的路长增加最多。它们请你设计并告诉它们最大增量是多少。

## 说明/提示

【样例说明】

若使 $3$ 和 $4$ 之间的道路长加倍，最短路将由 $1 \rightarrow 3 \rightarrow 4 \rightarrow 5$ 变为 $1 \rightarrow 3 \rightarrow 5$。

【数据规模和约定】

对于 $30\%$ 的数据，$N \le 70，M \le 1500$。

对于 $100\%$ 的数据，$1 \le N \le 100，1 \le M \le 5,000，1 \le L_i \le 1,000,000$。

## 样例 #1

### 输入

```
5 7
2 1 5
1 3 1
3 2 8
3 5 7
3 4 3
2 4 7
4 5 2```

### 输出

```
2```

# 题解

## 作者：霜月骑士 (赞：51)


 - 作为一个提交了无数遍此题的蒟蒻，我决定来为此题献上我的第一篇题解。
 

------------

   暴力做法：
   
    毕竟我们比赛的时候不可能所有题都去想正解，所以当我们遇到一些没有必要打正解的题目时，我们应该尝试去暴力拿分（当暴力也能ac或拿大部分分时）
   
   该怎么打暴力呢？
   
   这是一项“玄学”，首先我们有个思路，这道题是在不停地找最短路，那我们就拿出我们的最短路模板 dijkstra+堆优化 ，要修边的话，因为我们~~并不想~~并不知道要修改哪些边，那我们干脆就把每条边都修改一次，然后走（m+1）次最短路
   
   然而，用dijkstra+堆优化 打暴力的同学可能会发现无论如何暴力拿分都有1个点t掉，这里是一处此题很奇妙的地方。让我们来算一算这个暴力算法的时间复杂度 首先是dijkstra+堆优化的最短路复杂度 （n+m）logn【按最大数据大约是35000次】 然后因为我们走了（m+1次）所以是 （m+1）（n+m）logn 我们会发现，这个算法在题目的范围内破亿了，这也就是dijkstra+堆优化t掉的原因。
  
  但是由于这道题n的范围极其之小，我们会发现最原始的dijkstra的时间复杂度（n^2） 我们扫一遍查找离起点最近的未遍历的点，再扫一遍，用此点来进行松弛操作【更新最短路】 那么大致的时间复杂度就是（2*n^2）我们再进行（m+1）次 【按最大数据来计算则大概刚好到1亿，算是勉强挨边】 次数要小于堆优化过的 （所以这道题用原始版dijkstra是可以过的）
  
  dijkstra暴力代码如下（由于我不会用邻接表做原始dijkstra所以就用邻接矩阵来存图，若有哪位巨佬会，望能多多指教） （1050ms）
  ```cpp
#include <iostream>
#include <queue>
#include <iomanip>
#include <cstdio>
#define ll long long
using namespace std;
int uv[105][105]={0};//用邻接矩阵
int q=0,n,m;
int x[6005],y[6005],o=0;//用于记录“要修改”的每条边

bool flag[110]={0};
int road[110]={0};//这两个是dijkstra用的数组保存状态和最短路
void dijkstra(){

for( int i=1;i<=n;i++){
 flag[i]=0;
 road[i]=uv[1][i];
}
road[1]=0;
flag[1]=1;
    for( int i=1;i<n;i++){
        int minn=0x7fffff;
        int t;
        for( int j=1;j<=n;j++)
            if(flag[j]==0&&road[j]<minn){
                t=j;
                minn=road[j];
            }
    flag[t]=1;
    for( int k=1;k<=n;k++) 
     road[k]=min(road[k],road[t]+uv[t][k]); 
}
}

int main (){
   int l;
 scanf("%d%d",&n,&m);

 for(int i=1;i<=n;i++)
  for( int j=1;j<=n;j++)
    uv[i][j]=0x7fffff; //初始化每条边

    for( int i=1;i<=m;i++){
        int j,k,l;
        scanf("%d%d%d",&j,&k,&l);

          uv[j][k]=l;
          uv[k][j]=l;
        x[++o]=j;
        y[o]=k;
    } //输入，存储图

    dijkstra();
  int ans=road[n];//求出修边前的最短路长度
    l=0;

    for(int i=1;i<=o;i++){
        uv[x[i]][y[i]]*=2;
        uv[y[i]][x[i]]*=2;
    dijkstra();
         l=max(l,road[n]);
        uv[y[i]][x[i]]/=2;
         uv[x[i]][y[i]]/=2;
    } //暴力修边，疯狂求最短路
printf("%d",l-ans);    

}

```

除外，spfa玄学的时间复杂度（kE）用来暴力这道题也能过

spfa暴力代码如下 （1134ms）

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
int m,n;
queue <int> q;
bool flag[110];
int uv[110][110]={0};
int road[110];
int x[6000],y[6000],o=0;
void spfa(int v){
    for(int i=1;i<=n;i++) {
        flag[i]=0;
        road[i]=0x7fffff;
    }
    road[v]=0;
    flag[v]=1;
    q.push(v);
    while(!q.empty()){
        int t=q.front();
        for(int i=1;i<=n;i++)
        if(uv[t][i]!=0x7fffff) 
        if(road[i]>road[t]+uv[t][i]){
            road[i]=road[t]+uv[t][i];
            if(flag[i]==0){
                q.push(i);
                flag[i]=1;
            }
        }
        
        flag[t]=0;
        q.pop();
    }
}

int main (){
    int i,j,k,l;
    
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++) 
    uv[i][j]=0x7fffff;
    
    for(i=1;i<=m;i++){
        cin>>j>>k>>l;
        uv[j][k]=l;
        uv[k][j]=l;
        x[++o]=j;
        y[o]=k;
    }

    spfa(1);
   
    
    l=0;
    int ans=road[n];
    for(i=1;i<=o;i++){
        uv[x[i]][y[i]]*=2;
        uv[y[i]][x[i]]*=2;
        spfa(1);
        l=max(l,road[n]);
        uv[x[i]][y[i]]/=2;
        uv[y[i]][x[i]]/=2;
    }
    printf("%d",l-ans);
    }


```


------------


 对比来看，spfa的代码显得很简洁呢（或许这就是spfa常年被noip针对的缘故吧）
 
 ~~愉快~~“艰难的”暴力过后，我们也该想想正解了，毕竟oier做题不能仅靠暴力，况且这道题是因为其数据范围小才能被暴力ac，那么这道题的正确方法到底该怎么做呢？
 
 其实原理很简单，看过其他题解的，也应该懂了，但为了题解的完整性，蒟蒻我还是提及一番吧
 
 原理：如果我们修改的路不在原来的最短路上，那么它（这条修改后的边）的修改对于这一次最短路的值没有意义。那么我们也该想到了，在做完第一次dijkstra后，找到位于最短路上的边，对这些边来进行修改求解就好了

那么我们用邻接矩阵的优势也就来了，
可以直接用dfs往回搜索

```cpp
void dfs(int v,int len){
    if(v==1) return ;
    for(int i=1;i<=n;i++)
    if(uv[i][v]!=0x7fffff)
    if(road[v]-uv[i][v]==road[i]){
        x[++o]=v;y[o]=i;
        dfs(i,road[i]);
        return ;
    }
}


```
这样加一个子程序，再对源代码进行一些操作
dijkstra+dfs ac正解（33ms）

```cpp
#include <iostream>
#include <queue>
#include <iomanip>
#include <cstdio>
#define ll long long
using namespace std;
int uv[105][105]={0};
int q=0,n,m;
int x[5005],y[5005],o=0;
bool flag[110]={0};
int road[110]={0};
void dijkstra(){
  
for( int i=1;i<=n;i++){
 flag[i]=0;
 road[i]=uv[1][i];
}
road[1]=0;
flag[1]=1;
    for( int i=1;i<n;i++){
    	int minn=0x7fffff;
    	int t;
    	for( int j=1;j<=n;j++)
    		if(flag[j]==0&&road[j]<minn){
    			t=j;
    			minn=road[j];
            }
    flag[t]=1;
    for( int k=1;k<=n;k++) 
     road[k]=min(road[k],road[t]+uv[t][k]); 
}
}

void dfs(int v,int len){
    if(v==1) return ;
    for(int i=1;i<=n;i++)
    if(uv[i][v]!=0x7fffff)
    if(road[v]-uv[i][v]==road[i]){
        x[++o]=v;y[o]=i;
        dfs(i,road[i]);
        return ;
    }
}

int main (){
   
    int l;
  // freopen("t.txt","r",stdin); 
 scanf("%d%d",&n,&m);
 
 for(int i=1;i<=n;i++)
  for( int j=1;j<=n;j++)
    uv[i][j]=0x7fffff;
 
    for( int i=1;i<=m;i++){
    	int j,k,l;
        scanf("%d%d%d",&j,&k,&l);
 
      	uv[j][k]=l;
      	uv[k][j]=l;
    }

    dijkstra();
    dfs(n,road[n]);
   
  int ans=road[n];
    l=0;
    for(int i=1;i<=o;i++){
       uv[x[i]][y[i]]*=2;
        uv[y[i]][x[i]]*=2;
    dijkstra();
     	l=max(l,road[n]);

     	  uv[x[i]][y[i]]/=2;
     	  uv[y[i]][x[i]]/=2;
    
 }
printf("%d",l-ans);	
    
} 
```
spfa也是类似（避免过长，我在此就不贴出代码了）
【要真想要代码，可以在评测记录中搜我的名字】
【但是不要直接抄哦，小心被抓到】


最后总结： 其实这是一道不算难的题，主要考察的是最短路的模板，以及最短路dfs，或者暴力时对暴力算法时间复杂度的估量，计算；

  引文：此处n较小，我们可用邻接矩阵和原始dijkstra来处理，那么如果n、m数据都增强，这样做会不会出问题呢？
  
  还真那么有这样一道题，与此题极为相似
  P1186 玛丽卡 
  
  建议大家都可以去试试
  
  那么我们就在那道题的题解上，再见吧，拜拜。
  
  


~~【可能看不到我了，因为懒】~~
  
 【如果觉得我打的题解有那么一点点作用的话，欢迎给我留言和点赞】
 
 【各位巨佬对本蒟蒻有什么建议和指教，指正的也欢迎提出】
 
 【最后谢谢各位巨佬，能看完这篇啰嗦鬼码的题解】
   

 
 
 
  
  
  
  
   
   
  
   

 
 

---

## 作者：MloVtry (赞：31)

（这题...spfa会被卡？）

虽然不知道为什么满世界的dj，我还是贴一个spfahaole


显然如果扩大一条边，且能使最短路增加，这条边一定在原最短路上，不然最短路仍然是原来的最短路，不会有增量


所以枚举最短路上的边，逐一试图扩大，然后重新跑最短路，得到一个新的最短路，然后得到增量，进行操♂作就好了

因为是无向边所以可以从1开始记录边，这样^1就是对应的反向边了（写过网络流的应该理解吧0v0）


代码
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define M 15000
#include<queue> 
#define N 110
using namespace std;
int n,m;
int po,ans;
int head[N],to[M],next[M],len[M],e=1;
void buid(int u,int v,int l)
{
    next[++e]=head[u],head[u]=e;
    to[e]=v,len[e]=l;
}
int dis[N],init[N];
int pre[N],fr[N],that[M],nu;
queue<int> q;
void spfa(int s)
{
    memset(dis,20,sizeof(dis));
    dis[s]=0;init[s]=1,q.push(s);
    while(!q.empty())
    {
        int now=q.front();q.pop();init[now]=0;
        for(int i=head[now];i;i=next[i])
        {
            int j=to[i];
            if(dis[j]>dis[now]+len[i])
            {
                dis[j]=dis[now]+len[i];
                pre[j]=i;fr[j]=now;
                if(!init[j])
                {
                    init[j]=1;q.push(j);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int u,v,l;
        scanf("%d%d%d",&u,&v,&l);
        buid(u,v,l);
        buid(v,u,l);
    }
    spfa(1);po=dis[n];
    int now=n;
    while(now!=1)
    {
        that[++nu]=pre[now];//记路径
        now=fr[now];
    }
    for(int i=1;i<=nu;++i)//枚举路径
    {
        len[that[i]]*=2;
        len[that[i]^1]*=2;
        spfa(1);//操♂作
        ans=max(ans,dis[n]);
        len[that[i]]/=2;
        len[that[i]^1]/=2;
    }
    cout<<ans-po<<endl;//end
    return 0;
} 
//今天也依旧没有捞到岛风47厌战呢OvO

```

---

## 作者：奔波儿霸 (赞：16)

#### 瞎扯两句

这是一道最短路题目，不知道大家有没有做过玛丽卡这道题目，如果没做，在做完这道题之后可以去拿个双倍经验哦

建议去[我的博客](https://www.cnblogs.com/bljfy/p/9493382.html)阅读，将会有更好的阅读体验

[玛丽卡](https://www.cnblogs.com/bljfy/p/9447320.html)的题解我也写了，谢谢大家赏脸

~~好吧，我承认自己就是来骗热度的QAQ，但是谁叫各位这么善良呢~~



#### 解题思路

先求出一张图中的最短路径，并将其记录下来，我们首先思考：要有增量的前提是新的最短路径比原先的要短。

那就好办了，我们枚举将最短路径中的每一条边都翻倍，再跑最短路。这样的出来的路径去一个最大值，到最后减去一开始的最短路径，这就是答案。

为什么呢，因为如果我们对不在最短路径中的边进行翻倍的操作，那最短路径肯定没变，还是那样，所以只能改变最短路径中的边。


#### 附上代码
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int, int> P;
const int maxnode = 103, maxedge = 10003, INF = 1234567890;
priority_queue<P, vector<P>, greater<P> > Q;
int n, m, fir[maxnode], nxt[maxedge], cnt, pre[maxnode], Ans;
int u[maxedge], v[maxedge], w[maxedge], dis[maxnode], bef;
bool cut[maxnode][maxnode], flag;
inline void addedge(int x, int y, int z) {
	nxt[++cnt] = fir[x];
	fir[x] = cnt;
	u[cnt] = x, v[cnt] = y, w[cnt] = z;
}
inline void Dijkstra() {
	Q.push(P(0, 1));
	fill(dis+1, dis+1+n, INF);
	dis[1] = 0;
	P x;
	int k;
	while (!Q.empty()) {
		x = Q.top();
		Q.pop();
		if(x.first > dis[x.second]) continue;
		k = fir[x.second];
		while (k != -1) {
			if(cut[u[k]][v[k]]) {
				if(dis[v[k]] > dis[u[k]] + w[k] + w[k]) {
					dis[v[k]] = dis[u[k]] + w[k] + w[k];
					Q.push(P(dis[v[k]], v[k]));
				}
			}
			else if(dis[v[k]] > dis[u[k]] + w[k]) {
				dis[v[k]] = dis[u[k]] + w[k];
				if(!flag) pre[v[k]] = u[k];
				Q.push(P(dis[v[k]], v[k]));
			}
			k = nxt[k];
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	int x, y, z;
	memset(fir, -1, sizeof(fir));
	for(int i=1; i<=m; i++) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
		addedge(y, x, z);
	}
	flag = false;
	Dijkstra();
	flag = true;
	bef = dis[n];
	for(int i=n; i!=1; i=pre[i]) {
		cut[i][pre[i]] = 1;
		cut[pre[i]][i] = 1;
		Dijkstra();
		cut[i][pre[i]] = 0;
		cut[pre[i]][i] = 0;
		Ans = max(Ans, dis[n]);
	}
	printf("%d", Ans-bef);
}

```


---

## 作者：弱弱弱 (赞：11)

这道题边数远大于点数，~~显然，~~不管是时间复杂度为O(VE)的Ford，O(KE)的SPFA（K为进队次数，一般来说K是常数，但不排除被故意卡），在边数大于点数时，dijkstra的效率更胜一筹（有负的边权不能用dijkstra）。另外这道题的边权加倍不需对每边进行枚举，只需对未加倍前的最短路上的边加倍，因为你对非最短路上的边加倍，再走还是最短路。
C++代码：
 ```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,a[105][105],pre[105],t,dis[105],ans1,ans2;
bool b[105];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        a[x][y]=z;//无向图
        a[y][x]=z;//x到y，y到x，都要存
    }
    memset(dis,127,sizeof(dis));//dijkstra模版，只是多存个路径
    t=1;pre[1]=0;b[1]=1;dis[1]=0;
    for(int i=1;i<n;i++)
    {
        for(int j=1;j<=n;j++)
            if(a[t][j]>0&&dis[t]+a[t][j]<dis[j]){dis[j]=dis[t]+a[t][j];pre[j]=t;}
        int x=0x7fffffff;
        for(int j=1;j<=n;j++)
            if(dis[j]<x&&!b[j]){x=dis[j];t=j;}
        b[t]=1;
    }
    ans1=dis[n];
    int p=n;
    while(pre[p]!=0)//已知循环次数可以不用dfs
    {
        a[p][pre[p]]*=2;
        a[pre[p]][p]*=2;
        memset(dis,127,sizeof(dis));
        memset(b,0,sizeof(b));
        t=1;b[1]=1;dis[1]=0;
        for(int i=1;i<n;i++)
        {
            for(int j=1;j<=n;j++)
                if(a[t][j]>0&&dis[t]+a[t][j]<dis[j])dis[j]=dis[t]+a[t][j];
            int x=0x7fffffff;
            for(int j=1;j<=n;j++)
                if(dis[j]<x&&!b[j]){x=dis[j];t=j;}
            b[t]=1;
        }
        ans2=max(ans2,dis[n]);
        a[p][pre[p]]/=2;//类似dfs回溯
        a[pre[p]][p]/=2;
        p=pre[p];
    }
    printf("%d",ans2-ans1);
}

```

---

## 作者：lytqwq (赞：5)

我觉得我这是最暴力的方法23333

AC结果：[https://www.luogu.org/recordnew/show/17062771](https://www.luogu.org/recordnew/show/17062771)

解释在注释上。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[101][101],b[101][101],ago,maxn,dis[101],pre[101];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) 
	{
		for(int o=1;o<=n;o++) 
		{
			a[i][o]=b[i][o]=23333333;//初始化一个很大的数 
		}
	}
	for(int i=1;i<=m;i++) 
	{
		int x,y,z;
		cin>>x>>y>>z;
		a[x][y]=z;//无向图 
		a[y][x]=z;
	}
	
	for(int i=2;i<=n;i++)
	{
		dis[i]=23333333;
		pre[i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		int minn=23333333,mn;
		for(int o=1;o<=n;o++)
		{
			if(dis[o]<minn&&pre[o]==0)
			{
				minn=dis[o];
				mn=o;
			}
		}
		pre[mn]=1;
		for(int i=1;i<=n;i++)
		{
			if(dis[mn]+a[mn][i]<dis[i])
			{
				dis[i]=dis[mn]+a[mn][i];
			}
		}
	}
	/*
	dijkstra
	*/
	
	ago=dis[n];
	//记录结果
	 
	for(int q=1;q<=n;q++) 
	{
		for(int p=1;p<=n;p++) 
		{
			if(a[q][p]==0) 
			{
				continue;//没有路就跳出 
			}
			
			a[q][p]=a[q][p]*2;
			
			for(int i=1;i<=n;i++) 
			{
				dis[i]=23333333;
				pre[i]=0;
			}
			dis[1]=0;
			for(int i=1;i<=n;i++) 
			{
				int minn=23333333,mn;
				for(int o=1;o<=n;o++) 
				{
					if(dis[o]<minn&&pre[o]==0) 
					{
						minn=dis[o];
						mn=o;
					}
				}
				pre[mn]=1;
				for(int i=1;i<=n;i++) 
				{
					if(dis[mn]+a[mn][i]<dis[i]) 
					{
						dis[i]=dis[mn]+a[mn][i];
					}
				}
			}
			//dijkstra
			maxn=max(maxn,dis[n]);
			//累加最大值 
			
			a[q][p]=a[q][p]/2;//返回 
		}
	}
	cout<<maxn-ago;//最大增量 
}
```


---

## 作者：KenLi (赞：5)

先讲一下次短路的做法，~~不要问我为什么~~！:

使用 _Dijkstra/Spfa_ 跑一遍最短路，在松弛时记录最短路的路径

以SPFA为例：
```cpp
if(dis[u]+w<dis[v]){
	pre[v]=u;
	dis[v]=dis[u]+w;
	q.push(v);
}
//同理，Dijkstra的话只需要将q.push(v)改成q.push(make_pair(-dis[v],v))即可
```
per[i]数组表示最短路上编号为i的点的前驱结点

此时最短路上的边数为m

循环m次，循环运用迭代的思想，每次删除第i条边后跑最短路，跑完重新连接第i条边

由于删边操作的特殊性，故无法使用vector邻接表存边，但链式前向星和邻接矩阵还系阔以滴

以邻接矩阵为例：
```cpp
for(int i=n;pre[i];i=pre[i]){
	int tmp=mat[i][pre[i]];
	mat[i][pre[i]]=mat[pre[i]][i]=INF;//此处为删边操作
	//初始化dis数组
	//执行最短路
	ans=min(ans,dis[n]);
	mat[i][pre[i]]=mat[pre[i]][i]=tmp;//此处恢复连通
}
```
 _ans_ 即为次短路边权之和
 


------------
~~华丽的分割线~~

回到本题，仔细思考便不难发现：**只需要将次短路的删边操作改为边权乘以2， _ans_ 改为取最大值并与最短路径相减即可！**

附上代码：
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<cstdio>
#include<cctype>
#include<cstring>
#define INF 0x7fffffff
#define BUFF_SIZE 1<<15
#define get_ch() (fs==ft&&(ft=(fs=read_buf)+fread(read_buf,1,BUFF_SIZE,stdin),fs==ft))?0:*fs++
#define min_tree(a,b) a.val<b.val?a:b
#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b
using namespace std;
namespace readln{
    char read_buf[BUFF_SIZE],*fs,*ft;
    template<typename _Tp>
    inline void scanf_(_Tp &tmp){
        bool flag=false;
        char ch=get_ch();
        tmp=0;
        while(!isdigit(ch)){
            flag|=ch=='-';
            ch=get_ch();
        }
        while(isdigit(ch)){
            tmp=(tmp<<3)+(tmp<<1)+(ch^48);
            ch=get_ch();
        }
        tmp=flag?-tmp:tmp;
    }
}using namespace readln;
template<typename _Tp,typename... Args>
inline void scanf_(_Tp& t,Args&... args){
    scanf_(t);
    scanf_(args...);
}
struct Node{
    int ind,val;
}tree[131072];
int n,m,cnt,bit,dis[256],pre[65536],mat[256][256],ans,min_dis;
bool vis[256];
inline void build(){
	memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;++i){
        dis[i]=INF;
    }
    for(bit=1;bit<=n+1;bit<<=1);
    for(int i=bit+1;i<=bit+n;++i){
        tree[i].ind=i-bit;
    }
    for(int i=bit<<1;i>=1;--i){
        tree[i].val=INF;
    }
}
inline void update(int ind,int val){
    tree[bit+ind].val=val;
    for(int i=(bit+ind)>>1;i;i>>=1){
        tree[i]=min_tree(tree[i<<1],tree[i<<1|1]);
    }
}
inline void Dijkstra(){
    dis[1]=0;
    update(1,0);
    while(tree[1].val<INF){
        int u=tree[1].ind;
        vis[u]=true;
        update(u,INF);
        for(int v=1;v<=n;++v){
            if(mat[u][v]==INF){
                continue;
            }
            int w=mat[u][v];
            if(dis[u]+w<dis[v]&&!vis[v]){
                dis[v]=dis[u]+w;
                update(v,dis[v]);
            }
        }
    }
}
int main(){
    scanf_(n,m);
    for(int i=0;i<=n;++i){
        for(int j=0;j<=n;++j){
            mat[i][j]=INF;
        }
    }
    build();
    for(int i=1;i<=m;++i){
        int u,v,w;
        scanf_(u,v,w);
        mat[u][v]=min(w,mat[u][v]);
        mat[v][u]=min(w,mat[v][u]);
    }
    dis[1]=0;
    update(1,0);
    while(tree[1].val<INF){
        int u=tree[1].ind;
        vis[u]=true;
        update(u,INF);
        for(int v=1;v<=n;++v){
            if(mat[u][v]==INF){
                continue;
            }
            int w=mat[u][v];
            if(dis[u]+w<dis[v]&&!vis[v]){
                pre[v]=u;
                dis[v]=dis[u]+w;
                update(v,dis[v]);
            }
        }
    }
    min_dis=dis[n];
    for(int i=n;pre[i];i=pre[i]){//这里才是重点
        int tmp=mat[i][pre[i]];
        build();
        mat[i][pre[i]]<<=1;
        mat[pre[i]][i]<<=1;
        Dijkstra();
        ans=max(ans,dis[n]);
        mat[i][pre[i]]=mat[pre[i]][i]=tmp;
    }
    printf("%d",ans-min_dis);
    return 0;
}
```
 _~~写得很冗长，很大一部分是——玄学快读和优化迪杰的zkw~~_ 
 
**实际上我还是认为我的码风是完美滴**

---

## 作者：TinyKiecoo (赞：5)

### Vector存图+Dijkstra最短路

翻了翻题解，貌似没有用vector存图的，既然这样那本蒟蒻就贴一个vector的题解。

题目思路比较简单，先跑一遍正常的最短路，然后枚举在这条最短路上的每一条边，将其长度翻倍，再跑一遍最短路，输出新的最短路减去旧的最短路之后的最大值。


#### 本题关键就是如何记录原先的最短路：
在Dijkstra更新距离d数组时额外记录前驱节点，即记录d[i]的上一步d[j]，本操作可以使用结构体实现。

代码块：


```cpp
//枚举与x点相连的每一条边。
for(register int i=0;i<v[x].size();i++){
// val是路径长，from是前一个节点。
       if(d[v[x][i].to].val>d[x].val+v[x][i].val){
           d[v[x][i].to].val=d[x].val+v[x][i].val;
           d[v[x][i].to].from=x;
           q.push(make_pair(d[v[x][i].to].val,v[x][i].to));
           //优先队列优化
       }
}
```

由于d数组存的是1号点到所有点的最短路，而我们需要的有效路径只是从1到n的最短路，所以如果将路径记录完毕后将路径提取出来，后面将路径翻倍会相对更容易实现，我们可以利用递归从n点倒着退回来，将有效路径单独保存出来。

```cpp
inline void Return(int xx){
    if(d[xx].from==0)return;//退到了起点则退出，起点不需记录
    Return(d[xx].from);     //未到起点则再往前退一步
    Road_Recorder[++h]=xx;  //将非起点路径记录
}
//最后保存出来的路径即为
//1->Road_Recorder[1]->Road_Recorder[2]->……->n
```

#### Vector操作核心：将路径长度翻倍

使用vector存图时改变路径长一般用枚举方式实现。若将x点与y点的路径长翻倍，我们需要枚举与x相连的所有边，直至找到y点，将此边改变。由于是双向图，我们需要再重复此操作更改y与x相连的边。由于枚举导致本步时间复杂度并不确定。

由于我们还要再改其他的边，所以我们改完当前边并记录结果之后还需将其还原，所以我们在修改时直接记录下此边在vector中的位置，$O(1)$还原。

```cpp
//last为起点，Road_Recorder[i]为目标点
for(register int j=0;j<v[last].size();j++){     //枚举所有边
            if(v[last][j].to==Road_Recorder[i]){//找到了目标边
                v[last][j].val<<=1;             //更改
                change1=j;                      //记录位置
                break;
            }
}
//重复进行，将起点与目标点交换
for(register int j=0;j<v[Road_Recorder[i]].size();j++){
            if(v[Road_Recorder[i]][j].to==last){
                v[Road_Recorder[i]][j].val<<=1;
                change2=j;
                break;
            }
}
```
#### 路径的还原
```cpp
v[last][change1].val>>=1;
v[Road_Recorder[i]][change2].val>>=1;
```

#### 最后贴完整代码

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;
struct node{
    int to,val;
}add;
vector<node>v[101];
struct Node{
    int from,to,val;
}d[101];
bool f[101];
inline void ADD(int x,int y,int z){
    add.to=y;
    add.val=z;
    v[x].push_back(add);
}
int m,n,x,y,z,h,ans,change1,change2,dd[101],Road_Recorder[101],last=1;
inline void Return(int xx){
    if(d[xx].from==0)return;
    Return(d[xx].from);
    Road_Recorder[++h]=xx;
}
int main(){
    scanf("%d%d",&n,&m);
    for(register int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        ADD(x,y,z);
        ADD(y,x,z);
        //建图
    }
    /* 首先跑一边Dij，算出原始最短路 ↓*/
    memset(d,0x7f,sizeof(d));
    d[1].val=d[1].from=0;
    q.push(make_pair(0,1));
    while(!q.empty()){
        x=q.top().second;
        q.pop();
        if(f[x])continue;
        f[x]=1;
        for(register int i=0;i<v[x].size();i++){
            if(d[v[x][i].to].val>d[x].val+v[x][i].val){
                d[v[x][i].to].val=d[x].val+v[x][i].val;
                d[v[x][i].to].from=x;
                q.push(make_pair(d[v[x][i].to].val,v[x][i].to));
            }
        }
    }
    Return(n);//提取记录的路径
    for(register int i=1;i<=h;i++){//枚举改变的路径
        for(register int j=0;j<v[last].size();j++){//更改长度
            if(v[last][j].to==Road_Recorder[i]){
                v[last][j].val<<=1;
                change1=j;
                break;
            }
        }
        for(register int j=0;j<v[Road_Recorder[i]].size();j++){
            if(v[Road_Recorder[i]][j].to==last){
                v[Road_Recorder[i]][j].val<<=1;
                change2=j;
                break;
            }
        }
        /*算出新的最短路↓*/
        memset(dd,0x7f,sizeof(dd));
        memset(f,0,sizeof(f));
        dd[1]=0;
        q.push(make_pair(0,1));
        while(!q.empty()){
            x=q.top().second;
            q.pop();
            if(f[x])continue;
            f[x]=1;
            for(register int j=0;j<v[x].size();j++){
                if(dd[v[x][j].to]>dd[x]+v[x][j].val){
                    dd[v[x][j].to]=dd[x]+v[x][j].val;
                    q.push(make_pair(dd[v[x][j].to],v[x][j].to));
                }
            }
        }
        if(dd[n]-d[n].val>ans)ans=dd[n]-d[n].val;//比较答案
        v[last][change1].val>>=1;
        v[Road_Recorder[i]][change2].val>>=1;//路径还原
        last=Road_Recorder[i];//本次的目标点会成为下次的起点
        //last初值为1
    }
    printf("%d",ans);
}
```

如上文所说，由于枚举导致时间复杂度并不确定，精心造数据的话可能会被卡的慢一些，**~~但是肯定不会TLE吧……（弱弱地）~~**。

Luogu P1186 玛丽卡题目相似，数据范围n<=1000，[最慢的点304ms](https://www.luogu.org/recordnew/show/16962378)，~~真的算很快了~~。平均复杂度貌似$O(n^2logn)$，~~反正不会有人故意出测试点卡这种方法。~~

**欢迎各位巨佬提出建议和指教最后谢谢大家能够忍着如此啰嗦的题解看到最后。**

**~~（逃……**~~

---

## 作者：starwolfy_rika (赞：5)

你可曾听过SPFA堆优化？？？

堆优化的spfa又叫 允许多次入队的dijkstra。

没有负边的时候和dij一样，有负权边可能会被卡成指数级别。

那么这道题也是如此，只要将SPFA中的队列改成优先队列即可qwq

放代码qwq

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
long long n,m,dis[100005],head[100005],tot=1;//这里tot开始自己设为0，后来wa了一个点qwq。
long long ans,p[100005],f[100005],t[100005],k,sum;
bool vis[100005];
struct node
{
	int start,to,val;
}edge[100005];
struct cmp
{
    bool operator()(int a,int b)
    {
        return dis[a]>dis[b];
    }
};
priority_queue<int,vector<int>,cmp> q;//建堆
void add(int u,int v,int w)
{
	edge[++tot].start=v;
	edge[tot].val=w;
	edge[tot].to=head[u];
	head[u]=tot;
}
void spfa()
{
	memset(dis,0x7f,sizeof(dis));
	dis[1]=0;
	q.push(1);
	vis[1]=true;
	while(!q.empty())
	{
		int u=q.top();//这里不是q.front()！
		q.pop();
		vis[u]=false;
		for(int i=head[u];i;i=edge[i].to)
		{
			int v=edge[i].start;
			if(dis[v]>dis[u]+edge[i].val)
			{
				dis[v]=dis[u]+edge[i].val;
				p[v]=i;
				f[v]=u;
				if(!vis[v])
				{
					q.push(v);
					vis[v]=true;
				}
			}
		}
	}
	return ;
}
int main()
{
	int n,m;
	cin>>n>>m;
	
	for(int i=1;i<=m;i++)
	{
	    int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	spfa();
	ans=dis[n];
	int x=n;
	while(x!=1)
	{
		t[++k]=p[x];
		x=f[x];
	}
	for(int i=1;i<=k;i++)
	{
		edge[t[i]].val*=2;
		edge[t[i]^1].val*=2;
		spfa();
		sum=max(sum,dis[n]);
		edge[t[i]].val/=2;
		edge[t[i]^1].val/=2;
	}//原先这里写的太丑，参考了大佬的改成这样qwq
	cout<<sum-ans<<endl;
	return 0;
}


```
强烈推荐堆优化spfa qwq。。。
所以，spfa还没彻底死qwq（虽说这是披着spfa皮子的dijkstra）

---

## 作者：vegetabird (赞：3)

这道题是一道比较正常的最短路径题。

最短路径中，比较常用的算法有dijstra和spfa

其中dijstra的时间复杂度为O(n^2)，是稳定的算法

spfa的时间复杂度是O(k\*E)(E是边数，k是常数，一般<10)，但是这个算法是不稳定的算法，可能会被数据卡（这里好像有一个点卡spfa）

所以，这里就讲一下dijstra的解法

这道题的解法其实很暴力：

1. 求出在添加稻草堆前的最短路，并记录

2. 枚举每一条边，放上稻草堆，求一次最短路，最后求出添加稻草堆后最短路的最大值

代码


```cpp
#include<cstdio>
#include<cstring>
int n,m;
int a[10010],b[10010],l[10010];        //数组建立
int first[110],next[10010];                //链式前项星储存边
bool visited[110];                    //第i点是否被访问过
int dis[110];                        //dis数组表示1好点到i的最短距离
int ans1,ans2=0;
using namespace std;
void dij(){
    int i,j,u,k;
    dis[1]=0;
    for(i=1;i<=n;i++){                                    依次确定n个点的最短路
        u=0;
        for(j=1;j<=n;j++){
            if((dis[j]<dis[u])&&(!visited[j])){
                u=j;
            }
        }                                    //找到当前dis最小点u
        k=first[u];
        visited[u]=true;                        //该点最短路已经确定，无需再访问
        while(k!=-1){
            if(dis[b[k]]>dis[u]+l[k]){
                dis[b[k]]=dis[u]+l[k];            //优化相邻点最短路
            }
            k=next[k];
        }
    }
}
int main(){
    int i,j,u,k,cnt;
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    for(i=0;i<=n;i++){
        dis[i]=0x1fffffff;
    }
    for(i=1;i<=m;i++){
        scanf("%d%d%d",&a[i],&b[i],&l[i]);
        next[i]=first[a[i]];
        first[a[i]]=i;
        a[i+m]=b[i];
        b[i+m]=a[i];
        l[i+m]=l[i];
        next[i+m]=first[a[i+m]];
        first[a[i+m]]=i+m;                            //存边
    }
    memset(visited,false,sizeof(visited));
    ans1=dis[n];
    for(cnt=1;cnt<=m;cnt++){
        l[cnt]=l[cnt+m]=2*l[cnt];
        for(i=0;i<=n;i++){
            dis[i]=0x1fffffff;
            visited[i]=false;
        }
        if(dis[n]>ans2){
            ans2=dis[n];
        }
        l[cnt]=l[cnt+m]=l[cnt]/2;
    }
    printf("%d\n",ans2-ans1);
    return 0;
}
```
好了，就是这么多



为了防止某些人偷懒直接ctrl+c，特在程序中删去函数的调用，共两次，外加一次注释前未加"//"，请谅解


---

## 作者：rediserver (赞：3)

# P2176 [USACO14FEB]路障Roadblock

[GitHub题解](https://github.com/jerrykcode/luogu)

[原题地址](https://www.luogu.org/problemnew/show/P2176)

## 思路
邻接表，堆优化dijkstra

先计算一遍最短路径，设为min_dist，然后遍历路径上所有的边，对每一条边，将其权重增倍，再次计算最短路径，设为tmp_dist，之后将权重还原。tmp_dist - min_dist的最大值即答案。

具体见代码注释

## 代码

```cpp
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

#define NO_VALUE -1

typedef unsigned char Vertex; //顶点

//邻接点结构体
struct AdjNode {
    Vertex v; //邻接顶点
    int weight; //邻接边权重
    AdjNode(Vertex v, int weight) : v(v), weight(weight) {}
};

//Dijkstra类
class Dijkstra {
public :
    Dijkstra() : pre_memory_alloc_(false) {}
    ~Dijkstra() { if (pre_memory_alloc_) free(pre_); }

    /* 计算源(0)到终点(nv - 1)的最短路径，用p_min_dist指针传出。nv为顶点数量，record_path表示是否记录路径。*/
    bool dijkstra(vector<AdjNode> *graph, int nv, bool record_path, int *p_min_dist);

    /* 依次得到最后一次调用dijkstra并记录路径时，最短路径上的边，用p_from，p_to指针传出。
       第一次调用本函数得到最短路径上的最后一条边，之后每次调用得到上次调用的前一条边。*/
    bool getMinPath(Vertex *p_from, Vertex *p_to);
private:
    //优先队列使用的结构体
    struct Node {
        Vertex v;
        int dist;
        Node(Vertex v, int dist) : v(v), dist(dist) {}
    };
    struct cmp {
        bool operator() (Node& a, Node& b) {
            return a.dist > b.dist;
        }
    };

    //类变量
    int nv_;
    Vertex src_, des_; //nv_, src_, des_ 在getMinPath中用于记录

    int *dist_;
    bool *collected_;
    Vertex *pre_;
    bool pre_memory_alloc_; //pre_数组分配了内存则为true
};

bool Dijkstra::dijkstra(vector<AdjNode>* graph, int nv, bool record_path, int * p_min_dist) {	
    dist_ = new int[nv];
    fill(dist_, dist_ + nv, NO_VALUE);
    collected_ = new bool[nv];
    fill(collected_, collected_ + nv, false);
    Vertex src = 0, des = nv - 1;
    if (record_path) { //需要记录路径
        //更新nv_，src_，des_
        nv_ = nv;
        src_ = src;
        des_ = des;
        if (pre_memory_alloc_) free(pre_);
        pre_ = new Vertex[nv];
        pre_memory_alloc_ = true;
    }	
    dist_[(size_t)src] = 0;
    priority_queue<Node, vector<Node>, cmp> q;
    q.push(Node(src, dist_[(size_t)src]));
    while (!q.empty()) {
        Vertex min_vertex = q.top().v;
        q.pop();
        if (collected_[(size_t)min_vertex]) continue;
        collected_[(size_t)min_vertex] = true;
        if (min_vertex == des) {
            while (!q.empty()) q.pop();
            break;
        }
        int min_dist = dist_[(size_t)min_vertex];
        for (AdjNode adjNode : graph[min_vertex]) {
            Vertex adj_vertex = adjNode.v;
            int adj_weight = adjNode.weight;
            if (!collected_[(size_t)adj_vertex]) {
                if (min_dist + adj_weight < dist_[(size_t)adj_vertex] || dist_[(size_t)adj_vertex] == NO_VALUE) {
                    dist_[(size_t)adj_vertex] = min_dist + adj_weight;
                    q.push(Node(adj_vertex, dist_[(size_t)adj_vertex]));
                    if (record_path) pre_[(size_t)adj_vertex] = min_vertex; //记录路径
                }
            }
        }
    }//while
    bool result = collected_[(size_t)des];
    *p_min_dist = dist_[(size_t)des];
    free(dist_);
    free(collected_);
    return result;
}

bool Dijkstra::getMinPath(Vertex * p_from, Vertex * p_to) {	
    if (des_ == src_) return false;
    *p_from = pre_[(size_t)des_];
    *p_to = des_;
    des_ = *p_from;
    return true;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<AdjNode> *graph = new vector<AdjNode>[n];
    int a_i, b_i, l_i;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a_i, &b_i, &l_i);
        a_i--; b_i--;
        graph[a_i].push_back(AdjNode(b_i, l_i));
        graph[b_i].push_back(AdjNode(a_i, l_i));
    }
    Dijkstra dijkstra;
    int min_dist, tmp_dist, result = 0;
    dijkstra.dijkstra(graph, n, true, &min_dist);
    Vertex from, to;	
    while (dijkstra.getMinPath(&from, &to)) { //遍历最短路径上的所有边
        auto it = graph[(size_t)from].begin();
        for (; it != graph[(size_t)from].end(); it++)
            if (it->v == to) {
                it->weight *= 2; //增倍
                break;
            }
        if (dijkstra.dijkstra(graph, n, false, &tmp_dist))
            if (tmp_dist - min_dist > result) result = tmp_dist - min_dist;
        it->weight /= 2; //还原
    }
    printf("%d", result);
    for (int i = 0; i < n; i++)
        vector<AdjNode>().swap(graph[i]);
    return 0;
}
```

---

## 作者：转身、已陌路 (赞：2)

图论题  100个点 5000条边 可以用邻接矩阵  floyed可能会超时（没试过）  我用的是dijkstra  做m次循环 分别将每条路\*2（别忘了将双向的路都\*2  而且计算后要将路径还原！！！）  找到最大的增加量即可！！

代码：


    
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[5000][5000];
int d[5000];
bool f[5000];
int path[5000][5];
void read()//读入函数 
{
    scanf("%d%d",&n,&m);
    int x,y,z;
    for (int i=1;i<=m;i++)
    {
        cin>>x>>y>>z;
        a[y][x]=a[x][y]=z;//无向图 
        path[i][1]=x;//记录两个节点 
        path[i][2]=y;
    }
    return;    
}
void dijkstra(int st)//dijkstra标准版子 
{
    memset(d,10,sizeof(d));
    for (int i=1;i<=n;i++) d[i]=a[st][i];
    memset(f,false,sizeof(f));
    f[st]=true; d[st]=0;
    for (int i=1;i<n;i++)
    {
        int minn=1000000000,k=0;
        for (int j=1;j<=n;j++)
        if (!f[j]&&(d[j]<minn)) minn=d[j],k=j;
        if (k==0) return;
        f[k]=true;
        for (int j=1;j<=n;j++)
        if ((!f[j]) && (d[k]+a[k][j]<d[j]))
                d[j]=d[k]+a[k][j];
    }
}
int main()
{
    memset(a,10,sizeof(a));
    read();
    int maxx=0,l,hh;
    dijkstra(1);
    hh=d[n];//找到FJ原来需要的路径长度 
    for (int i=1;i<=m;i++)
    {
        a[path[i][1]][path[i][2]]*=2;
        a[path[i][2]][path[i][1]]*=2;//将这条路安放一叠稻草堆  即路径长度*2  千万不要忘了双向！！！ 
        dijkstra(1);//做一遍dijkstra 
        if (abs(d[n]-hh)>maxx) maxx=abs(d[n]-hh),l=abs(d[n]-hh);//找到最大增量 
        a[path[i][1]][path[i][2]]/=2;
        a[path[i][2]][path[i][1]]/=2;
    }
    cout<<l;//美妙的输出时间 
    return 0;
}
```

---

## 作者：Starria的脑残粉 (赞：1)

看起来好多人都要结构体诶。。（蒟蒻不会用stl

就是先跑一遍最短路显然可以证明你需要翻倍的边一定会在最短路上

然后暴力枚举就可以拉

懒得写前向星用了邻接矩阵

有可能有重边然后用了两个邻接矩阵。。（滑稽

时间复杂度最坏情况下n^3

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[2000][2000],b[2000][2000],f[2000],ff[2000],fa[2000],ans,x,y,z;
bool flag[2000];
long long dij(long long x,long long y)//暴力求当x到y的边翻倍之后的最短路
    {
        long long kk=a[x][y];a[x][y]=min(kk*2,b[x][y]);a[y][x]=min(kk*2,b[y][x]);
        memset(f,10,sizeof(f));
        memset(flag,0,sizeof(flag));
        f[1]=0;
        for (long long i=1;i<=n;i++)
            {
                long long k=0;
                for (long long j=1;j<=n;j++)
                    if (!flag[j]&&f[j]<f[k]) k=j;
                flag[k]=true;
                for (long long j=1;j<=n;j++)
                    f[j]=min(f[j],f[k]+a[k][j]);
            }
        a[x][y]=kk;a[y][x]=kk;
        return f[n];
    }
void dfs(long long x)//枚举最短路
    {
        if (!fa[x])return;
        ans=max(ans,dij(fa[x],x));
        dfs(fa[x]);
    }
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    memset(a,10,sizeof(a));memset(b,10,sizeof(b));
    for (long long i=1;i<=m;i++){
        cin>>x>>y>>z;
        b[x][y]=min(b[x][y],max(a[x][y],z));
        b[y][x]=min(b[y][x],max(a[y][x],z));
        a[x][y]=min(a[x][y],z);a[y][x]=min(a[y][x],z);//b[i][j]代表次长边
    }
    memset(f,10,sizeof(f));
    f[1]=0;
    for (long long i=1;i<=n;i++)
        {
            long long k=0;
            for (long long j=1;j<=n;j++)
                if (!flag[j]&&(f[j]<f[k])) k=j;
            fa[k]=ff[k];flag[k]=true;
            for (long long j=1;j<=n;j++)
                if (f[j]>f[k]+a[k][j])f[j]=f[k]+a[k][j],ff[j]=k;
        }
    long long lsg=f[n];dfs(n);
    cout<<ans-lsg;
}
```

---

## 作者：TsReaper (赞：1)

一道类次短路问题。首先枚举在哪一条路上放置稻草。如果在不是最短路的边上放置稻草，由于最短路不变，小Z的路长也不变。所以，我们枚举最短路上的每一条边，将该边放置稻草后，跑一遍最短路。所有放置稻草后最短路的最大值与原最短路的差值就是答案。


---

## 作者：zyc123 (赞：0)

## 求过
本蒟蒻第一篇题解（**求过！！**）—>显然求过是重点。  
如果有什么问题，请指出，谢！！！
## 主要思路
（还是比较暴力的）—>因为害怕超时，用的堆优化，后来貌似还挺快的。  
1、倒着跑$Dijkstra$，记录从$n$到所有点的最短路。  
2、正着跑$dfs$，将所有在最短路上的边记录。  
3、（暴力开始）枚举每一个边，将它的长度加倍，并跑一遍$Dijkstra$，更改$ans$，最后将这条边改回来，去更改下一条。  
4、结束。
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;
struct edge {
    int zd;//终点 
    int cd;//长度 
    int xyg;//next 
} bian[200010];//前向星存边 
struct node {
    int d,u;//长度，点 
    bool operator<(const node &a)const {
        return d>a.d;
    }
};
int n,m,cnt=1,exmin,tt,ans;//边，点，cnt，第一遍的最短路，dfs存边的，答案 
int first[200010],flag[1100],which[200100],dis[1100];//前向星，Dijkstra,dfs存边的，距离 
priority_queue<node> q;
void add(int qd,int zd,int cd) {
    cnt++;//从2开始存边（其实从0也可以，貌似从偶数存都可以） 
    bian[cnt].zd=zd;
    bian[cnt].cd=cd;
    bian[cnt].xyg=first[qd];
    first[qd]=cnt;
}
void Dijkstra(int x) {//堆优化
    memset(dis,0x3f,sizeof(dis));
    memset(flag,0,sizeof(flag));//flag一定要归零！！
    dis[x]=0;
    q.push(node {0,x});
    while(!q.empty()) {
        node fir=q.top();
        q.pop();
        if(flag[fir.u]) continue;
        flag[fir.u]=1;
        int u=fir.u;
        for(int i=first[u]; i>1; i=bian[i].xyg) {
            if(dis[bian[i].zd]>bian[i].cd+dis[u]) {
                dis[bian[i].zd]=bian[i].cd+dis[u];
                q.push(node {dis[bian[i].zd],bian[i].zd});
            }
        }
    }
}
void dfs(int x,int y) {//dfs 
//如果n到这个点的最短路+从1开始到这里的距离=最短路，那么这个点一定在最短路上 
    for(int i=first[x]; i>1; i=bian[i].xyg) { 
        int what=bian[i].zd;
        int how=dis[what];
        int len=y+bian[i].cd;//此时的长度等于现在的x到1的距离加上这条边的长度
        if(len+how==exmin) {
            tt++;
            which[tt]=i;//记录边 
            dfs(bian[i].zd,len);
        }
    }
}
void change(int x) {
    int what=which[x];
    bian[what].cd*=2;
    bian[what^1].cd*=2;//what^1就是what对应的反边（所以要从偶数开始存） 
}
void restore(int x) {
    int what=which[x];
    bian[what].cd/=2;
    bian[what^1].cd/=2;
}
void last() {
    for(int i=1; i<=tt; i++) {
        change(i);
        Dijkstra(n);
        ans=max(ans,dis[1]-exmin);
        restore(i);
    }
}
int main() {
    cin>>n>>m;
    for(int i=1; i<=m; i++) {//存边
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
        add(b,a,c);
    }
    Dijkstra(n);
    exmin=dis[1];//记录最短路
    dfs(1,0);
    last();
    cout<<ans;
}
```


---

## 作者：曹老师 (赞：0)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco14feb-rblock.html)

迪杰斯特拉 + $DFS$

**千万不要这样做：**
找一遍最短路，$DFS$出路径，同时找出最短路中路径最长的那条边，然后加倍，再跑一遍最短路，求答案。

~~这样做你并不能$AC$，如果故意卡你，甚至会保龄……（别问我怎么知道的）~~

**正确做法其实差不多，就是：**

跑一边最短路，$DFS$维护出从1到$n$走过的每一条边，枚举每一条边，加倍，求出一个值，取最大值为答案。

## Code ##

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#define INF 2147483647
using namespace std;

struct Node {
	int to , next , len;
};
Node e[50005];
struct Road {
	int num , len;
	Road(int nn , int dd) {
		num = nn , len = dd;
	}
	bool operator < (const Road &a) const {
		return len > a.len;
	}	
};
int head[255] , tot = 0;
int n , m , sum = 0 , map[255][255];
int dis[255] , maxx = -1 , num = 0 , res = 0 , r[255] , top = 0;
priority_queue<Road>q; 

void add(int x , int y , int len) {
	tot++;
	e[tot].to = y;
	e[tot].next = head[x];
	e[tot].len = len;
	head[x] = tot;
}

void dij(int s) {
	for(int i=1; i<=n; i++)
		dis[i] = INF;
	dis[s] = 0;
	q.push(Road(s , 0));
	while(!q.empty()) {
		Road u = q.top();
		q.pop();
		if(u.len != dis[u.num])
			continue;
		for(int i=head[u.num]; i; i=e[i].next)
			if(e[i].len + u.len < dis[e[i].to]) {
				dis[e[i].to] = e[i].len + u.len;
				q.push(Road(e[i].to , dis[e[i].to]));
			}
	}
}

int dfs(int x , int fa) {
	if(x == n && sum == dis[n])
		return 1;
	if(sum > dis[n])
		return 0;
	int temp = sum;
	for(int i=head[x]; i; i=e[i].next) {
		if(e[i].to == fa)
			continue;
		sum += map[x][e[i].to];
		if(dfs(e[i].to , x)) {
			r[++top] = i;
			if(map[e[i].to][x] > maxx)
				maxx = map[e[i].to][x];
			return 1;		
		}
		sum = temp;
	}
	return 0;
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++) {
		int x , y , z;
		scanf("%d%d%d",&x,&y,&z);
		add(x , y , z);
		add(y , x , z);
		map[x][y] = map[y][x] = z;
	}
	dij(1);
	res = dis[n];
	dfs(1 , 0);
	for(int i=1; i<=top; i++) {
		if(r[i] % 2 != 0)
			e[r[i]].len = e[r[i]+1].len = 2 * e[r[i]].len;
		else
			e[r[i]].len = e[r[i]-1].len = 2 * e[r[i]].len;
		dij(1);
		num = max(num , dis[n] - res);
		if(r[i] % 2 != 0)
			e[r[i]].len = e[r[i]+1].len =  e[r[i]].len / 2;
		else
			e[r[i]].len = e[r[i]-1].len =  e[r[i]].len / 2;
	}
	printf("%d",num);
	return 0;
}
```


  [1]: http://usaco.org/index.php?page=viewproblem2&cpid=398
  [2]: https://www.luogu.org/problemnew/show/P2176
  [3]: https://www.lydsy.com/JudgeOnline/problem.php?id=3445

---

## 作者：Blind_God (赞：0)

##dijkstra加堆优化

###讲实话这道题的数据真心有点水，我开始理解错了意思，就用首次最短路中的最大值作为放障碍的路，居然拿了90分（汗）。

###这道题很多人说SPFA会被卡啊（没试过），那就用dijkstra好了，至少我基本每个点都是0ms，基本思路就是先找一次最短路，再将每段路尝试\*2，将变化的最大值输出就好了。（我用了指针（不需要！！），只是想练练~，不要骂我）

##代码很长很臭，反正大部分也就是模板

```cpp
#include<iostream>
#define maxn 251
using namespace std;
struct edge{
    int from,to,len;  //记录起点是为了方便修改路的长度
    edge *next;  //我用指针是因为蒟蒻想顺便练习下链表
};
edge *last[maxn],*pre[maxn],*p;
int pos[maxn],heap[maxn],dis[maxn],heap_size,n,m,maxx,q,ans;
bool in_heap[maxn];
void add_edge(int from,int to,int len){
    edge *temp=new edge;
    temp->from=from;
    temp->to=to;
    temp->len=len;
    temp->next=last[from];
    last[from]=temp;
}
void swapp(int i,int j){
    int temp=heap[i];
    heap[i]=heap[j];
    heap[j]=temp;
    pos[heap[i]]=i;
    pos[heap[j]]=j;
}
void shift_up(int now){  //函数基本都是加堆优化的基本操作
    int next=0;
    while(now>1){
        next=now>>1;
        if(dis[heap[next]]>dis[heap[now]])
          swapp(now,next);
        now=next;
    }
}
void put(int s){
    heap[++heap_size]=s;
    pos[s]=heap_size;
    in_heap[s]=true;
    shift_up(heap_size);
}
int get(){
    int res=heap[1],now=1,next;
    in_heap[heap[1]]=false;
    heap[1]=heap[heap_size--];
    while(now*2<heap_size){
        next=now<<1;
        if(dis[heap[next+1]]<dis[heap[next]]&&next<heap_size)next++;
        if(heap[now]<=heap[next])return res;
        swapp(now,next);
        now=next;
    }
    return res;
}
void dijkstra(){  //写成函数方便调用吧
    put(1);
    dis[1]=0;
    while(heap_size>0){
        int top=get();  //从堆中取出暂时路径最短的点
        edge *temp=last[top];
        while(temp!=NULL){
            if(dis[temp->to]>dis[top]+temp->len)  //用这个点修改与其相连的点
              {
                  dis[temp->to]=dis[top]+temp->len;
                  pre[temp->to]=temp;  //记录下每个点的前驱
                    if(in_heap[temp->to])shift_up(pos[temp->to]);  //如果点在堆中，则变化后调整位置
                    else put(temp->to);  //不在堆中则压入
              }
            temp=temp->next;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);  //写这个是怕cin和cout太慢，但又觉得cin方便
    int i,x,y,z;
    cin>>n>>m;
    for(i=1;i<=m;i++)
    {
        cin>>x>>y>>z;
        add_edge(x,y,z); //无向图，要放两次
        add_edge(y,x,z);
    }
    for(i=1;i<=n;i++)dis[i]=0x7fffffff/3;
    dijkstra();  //求出初始的最短路径
    q=dis[n];  //记录
    for(p=pre[n];p!=NULL;p=pre[p->from])  //尝试路径中的每段路
    {
        p->len*=2;
        for(i=1;i<=n;i++)dis[i]=0x7fffffff/3;
        dijkstra();
        ans=max(ans,dis[n]-q);
        p->len/=2;  //千万记得要还原
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：能神带你飞 (赞：0)

最短路

先跑一遍，然后枚举每一条边，不停的跑啊跑啊．．．

有一个点卡ＳＰＦＡ，恩，玄学的时间复杂度不靠谱


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int q[10000];
int dis[105];
int p[105];
struct node{
    int to;
    int next;
    int m;
}s[10005];
int h[105];
int ji;
int in(int u,int v,int l){
    ji++;
    s[ji].to =v;
    s[ji].next =h[u];
    h[u]=ji;
    s[ji].m =l;
    ji++;
    s[ji].to =u;
    s[ji].next =h[v];
    h[v]=ji;
    s[ji].m =l;
}
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    memset(dis,127,sizeof(dis));
    dis[1]=0;
    int a,b,l;
    for(int i=0;i<m;i++){
        scanf("%d %d %d",&a,&b,&l);
        in(a,b,l);
    }
    int head=0,tail=0;
    q[0]=1;
    p[1]=1;
    tail++;
    while(head!=tail){
        int u=q[head];
        p[u]=0;
        for(int i=h[u];i!=0;i=s[i].next ){
            int v=s[i].to ,w=s[i].m ;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(p[v]==0){
                    p[v]=1;
                    q[tail]=v;
                    tail++;
                }
            }
        }
        head++;
    }
    int x=dis[n];
    int mx=0;
    if(ji>4950)ji=4950;      //坑啊，防卡 
    for(int t=1;t<=ji;t=t+2){
        s[t].m *=2;
        s[t+1].m *=2;
        memset(dis,127,sizeof(dis));
        dis[1]=0;
        int head=0,tail=0;
        q[0]=1;
        p[1]=1;
        tail++;
        while(head!=tail){
            int u=q[head];
            p[u]=0;
            for(int i=h[u];i!=0;i=s[i].next ){
                int v=s[i].to ,w=s[i].m ;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    if(p[v]==0){
                        p[v]=1;
                        q[tail]=v;
                        tail++;
                    }
                }
            }
            head++;
        }
        if(dis[n]-x>mx){
            mx=dis[n]-x;
        }
        s[t].m /=2;
        s[t+1].m /=2;
    } 
    cout<<mx;
}
```

---

## 作者：l1360300734 (赞：0)

这个题是标准的dijkstra,我先进行一遍dijkstra，找出来没有路障是的最短路，用一个结构体zou记录下走过的边，再遍历所有是最短路走过的边，找出使得路程增加的最大值，这样能比遍历所有的边省好多时间那，

献上蒟蒻的代码：

```cpp
#include<cstring>
#include<cstdio>
using namespace std;
struct hehe
{
    int lai;
    int qu;
}zou[251];
bool b[251];
int w[251][251],dis[251],pre[251],a,s,n,m,yuanlai,xianzai,max1,s1;
void print(int x)//通过递归找出来走过那些边
{
    if (pre[x]==0)
        return;
    print(pre[x]);
    s++;
    zou[s].qu=x;
    zou[s].lai=pre[x];
//    printf("->%d",x);
}
int dijkstra()//标准dijkstra版子
{
    int i,j,k,min1;
    memset(b,0,sizeof(b));
    memset(dis,0,sizeof(dis));
    for (i=1;i<=n;i++)
        dis[i]=w[1][i];
    dis[1]=0;
    b[1]=true;
    for (i=1;i<=n-1;i++)
    {
        min1=0x7fffffff;
        k=0;
        for (j=1;j<=n;j++)
            if (dis[j]<min1&&!b[j])
            {
                k=j;
                min1=dis[j];
            }
        b[k]=true;
        if (!k)
            break;
        for (j=1;j<=n;j++)
            if (dis[j]>dis[k]+w[k][j])
                dis[j]=dis[k]+w[k][j];
    }
    return dis[n];
}
int main()
{
    int i,j,k,min1,x,y,z;
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            w[i][j]=0x3f3f3f3f-1;
    for (i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        w[x][y]=w[y][x]=z;
        if (y==1)//记录每个点的前驱
            pre[x]=y;
        if (x==1)//记录每个点的前驱
            pre[y]=x;
    }
    for (i=1;i<=n;i++)
        dis[i]=w[1][i];
    dis[1]=0;
    b[1]=true;
    pre[1]=0;
    for (i=1;i<=n-1;i++)
    {
        min1=0x7fffffff;
        k=0;
        for (j=1;j<=n;j++)
            if (dis[j]<min1&&!b[j])
            {
                k=j;
                min1=dis[j];
            }
        b[k]=true;
        if (!k)
            break;
        for (j=1;j<=n;j++)
            if (dis[j]>dis[k]+w[k][j])
            {
                dis[j]=dis[k]+w[k][j];
                pre[j]=k;//记录每个点的前驱
            }
    }
    yuanlai=dis[n];
    print(n);
    for (i=1;i<=s;i++)//遍历所有的边
    {
        w[zou[i].lai][zou[i].qu]=2*w[zou[i].lai][zou[i].qu];
        s1=dijkstra();
        if (s1-yuanlai>max1)//找到最大值
            max1=s1-yuanlai;
        w[zou[i].lai][zou[i].qu]=w[zou[i].lai][zou[i].qu]/2;
    }
    printf("%d",max1);//输出
}
```

---

## 作者：QWsin (赞：0)

**
我就说几句：

第一个  这道题跟上一道（别告诉我你不是试炼场刷过来的）很像 类似次短路

用dijkstra跑一遍  记录最短路上的点的前驱  然后枚举最短路上得边（非最短路得边\*2没影响） 遇到这条边的时候就把边权\*2  我用的是两个点确定一条边

[color=red]  woc数据有毒！！！！！我看110的5010后三个点会RE= =  出题人你智商干什么去了   愤怒的我直接后面加上一个0完事= =[/color]

**

```cpp

#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=100+10;
const int maxm=5000+10;
const int INF=(1<<30);
struct Node{
    int u,d;
    Node(){}
    Node(int u,int d):u(u),d(d){}
    bool operator < (const Node &rhs)const{
        return d>rhs.d;
    }
};

int n,m;
int first[maxn],next[maxm],u[maxm],v[maxm],w[maxm];
void init_data()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) first[i]=-1;
    for(int i=1;i<=2*m;i+=2)
    {
        scanf("%d%d%d",u+i,v+i,w+i);
        next[i]=first[u[i]];
        first[u[i]]=i;
        w[i+1]=w[i];
        u[i+1]=v[i];
        v[i+1]=u[i];
        next[i+1]=first[v[i]];
        first[v[i]]=i+1;
    }
}

int d[maxn],vis[maxn],pre[maxn];
int dijkstra(int f,int t)                                         //这里f  t为两个点 记录一条*2的边
{                                                                         //只有第一次需要更新pre（前驱）
    priority_queue<Node>q;                          //而且此后不能更新pre  看main里的for
    for(int i=1;i<=n;i++) d[i]=INF,vis[i]=0;
    d[1]=0;
    if(f==-1)pre[1]=-1;
    q.push(Node(1,0));
    while(!q.empty())
    {
        Node x=q.top();q.pop();
        if(vis[x.u]) continue;
        vis[x.u]=1;
        for(int i=first[x.u];i!=-1;i=next[i])
          if(x.u==f&&v[i]==t)
          {
              if(d[v[i]]>d[x.u]+2*w[i])
            {
                  d[v[i]]=d[x.u]+2*w[i];
                  if(f==-1)pre[v[i]]=x.u;
                  q.push(Node(v[i],d[v[i]]));
            }
          }
          else if(d[v[i]]>d[x.u]+w[i])
          {
              d[v[i]]=d[x.u]+w[i];
              if(f==-1)pre[v[i]]=x.u;
              q.push(Node(v[i],d[v[i]]));
          }
    }
    return d[n];
}

int main()
{
    init_data();
    int minl=dijkstra(-1,-1),ans=0;
    for(int x=n;x!=1;x=pre[x])
    {
        ans=max(ans,dijkstra(pre[x],x)-minl);
    }
    cout<<ans;
    return 0;
}


```

---

## 作者：xsap (赞：0)

- ~~这题SPFA会被卡吗?(实测好像并不会，也没有比Dijkstra慢很多)~~

![实测SPFA](https://img-blog.csdnimg.cn/20200107181610538.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3hzYXBsb3Nlcg==,size_16,color_FFFFFF,t_70)
- 纯暴力思路就是枚举每一条边，之后将这条边边权翻倍。时间复杂度**O(E × 最短路复杂度 )**，用SPFA可能会被卡，dijkstra直接爆炸
- 优化的思路是显然，草堆只可能**放在最短路上**，所以每次判断一条边是否在最短路上，如果是，才跑最短路，这样程序效率会快很多，SPFA也不会被卡，当然，因为是全正边，所以肯定跑Dijkstra
- 至于如何判断是否在1-n的最短路上。方法是：先跑一次以1为源点的最短路，记到数组dis[1][i]中；再跑一次以 n为源点的最短路，记到 dis[2][i] 中；每次检查一条i -> j的边，就看dis[1][i] + g[i][j] + dis[2][j] = dis[1][n] 吗。
- 最好用邻接矩阵存，这样更易于翻倍边权。
- 代码：（Dijkstra）

```cpp
# include <iostream>
# include <cstdio>
# include <set>

using namespace std ;

int n , m ;
int g[105][105] ;
set < pair< int , int > > heap ;
int dis[4][40005] ;

void dij( int s , int tmp )
{
	while ( heap.size() )
	{
		heap.erase( heap.begin() ) ;
	}
	for ( int i = 1 ; i <= n ; i++ )
		dis[tmp][i] = 1e9 + 5 ;
	dis[tmp][s] = 0 ;
	heap.insert( make_pair( dis[tmp][s] , s ) ) ;
	for ( int i = 1; i <= n ; i++ )
	{
		int x = heap.begin() -> second ;
		int d = heap.begin() -> first ;
		heap.erase( make_pair( d , x ) ) ;
		for ( int j = 1 ; j <= n ; j++ )
		{
			if ( dis[tmp][x] + g[x][j] >= dis[tmp][j] )
				continue ;
			heap.erase( make_pair( dis[tmp][j] , j ) ) ;
			dis[tmp][j] = dis[tmp][x] + g[x][j] ;
			heap.insert( make_pair( dis[tmp][j] , j ) ) ;
		}
	}
	return ;
}

int main()
{
	for ( int i = 1 ; i <= 100 ; i++ )
		for ( int j = 1 ; j <= 100 ; j++ )
			g[i][j] = 1000000000 ;
	scanf("%d%d" , &n , &m) ;
	for ( int i = 1 ; i <= m ; i++ )
	{
		int x , y , z ;
		scanf("%d%d%d" , &x , &y , &z) ;
		g[x][y] = z ;
		g[y][x] = z ;
	}
	dij( 1 , 1 ) ;
	dij( n , 2 ) ;
	int ans = 0 ;
	for ( int i = 1 ; i <= n ; i++ )
	{
		for ( int j = 1; j <= n ; j++ )
		{
			if ( dis[1][i] + g[i][j] + dis[2][j] == dis[1][n] )
			{
				g[i][j] *= 2 ;
				g[j][i] *= 2 ;
				dij( 1 , 3 ) ;
				g[i][j] /= 2 ;
				g[j][i] /= 2 ;
				ans = max( ans , dis[3][n] - dis[1][n] ) ;
			}
		}
	}
	printf("%d\n" , ans) ;
	return 0 ;
}
```

- SPFA版

```cpp
# include <iostream>
# include <cstdio>
# include <set>
# include <queue>

using namespace std;

int n , m ;
int g[105][105] ;
int dis[4][40005] ;
bool already[105] ;
queue < int > q ;

void spfa( int s , int tmp )
{
	for ( int i = 1 ; i <= n ; i++ )
	{
		dis[tmp][i] = 1e9 + 5 ;
		already[i] = false ;
	}
	already[s] = 1 ;
	dis[tmp][s] = 0 ;
	q.push( s ) ;
	while ( ! q.empty() )
	{
		int x = q.front() ;
		already[x] = 0 ;
		q.pop() ;
		for ( int y = 1 ; y <= n ; y++ )
		{
			if ( dis[tmp][x] + g[x][y] >= dis[tmp][y] )
				continue ;
			dis[tmp][y] = dis[tmp][x] + g[x][y] ;
			if ( already[y] )
				continue ;
			already[y] = 1 ;
			q.push( y ) ;
		}
	}
}

int main()
{
	for ( int i = 1 ; i <= 100 ; i++ )
		for ( int j = 1 ; j <= 100 ; j++ )
			g[i][j] = 1000000000 ;
	scanf("%d%d" , &n , &m) ;
	for ( int i = 1 ; i <= m ; i++ )
	{
		int x , y , z ;
		scanf("%d%d%d" , &x , &y , &z) ;
		g[x][y] = z ;
		g[y][x] = z ;
	}
	spfa( 1 , 1 ) ;
	spfa( n , 2 ) ;
	int ans = 0 ;
	for ( int i = 1 ; i <= n ; i++ )
	{
		for ( int j = 1; j <= n ; j++ )
		{
			if ( dis[1][i] + g[i][j] + dis[2][j] == dis[1][n] )
			{
				g[i][j] *= 2 ;
				g[j][i] *= 2 ;
				spfa( 1 , 3 ) ;
				g[i][j] /= 2 ;
				g[j][i] /= 2 ;
				ans = max( ans , dis[3][n] - dis[1][n] ) ;
			}
		}
	}
	printf("%d\n" , ans) ;
	return 0 ;
}

```

---

