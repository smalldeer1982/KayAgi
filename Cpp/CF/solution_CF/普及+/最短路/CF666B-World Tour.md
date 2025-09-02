# World Tour

## 题目描述

A famous sculptor Cicasso goes to a world tour!

Well, it is not actually a world-wide. But not everyone should have the opportunity to see works of sculptor, shouldn't he? Otherwise there will be no any exclusivity. So Cicasso will entirely hold the world tour in his native country — Berland.

Cicasso is very devoted to his work and he wants to be distracted as little as possible. Therefore he will visit only four cities. These cities will be different, so no one could think that he has "favourites". Of course, to save money, he will chose the shortest paths between these cities. But as you have probably guessed, Cicasso is a weird person. Although he doesn't like to organize exhibitions, he likes to travel around the country and enjoy its scenery. So he wants the total distance which he will travel to be as large as possible. However, the sculptor is bad in planning, so he asks you for help.

There are $ n $ cities and $ m $ one-way roads in Berland. You have to choose four different cities, which Cicasso will visit and also determine the order in which he will visit them. So that the total distance he will travel, if he visits cities in your order, starting from the first city in your list, and ending in the last, choosing each time the shortest route between a pair of cities — will be the largest.

Note that intermediate routes may pass through the cities, which are assigned to the tour, as well as pass twice through the same city. For example, the tour can look like that: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF666B/a1ec5df39eab48a433cbfa38b3e24c1e861f8538.png). Four cities in the order of visiting marked as overlines: $ [1,5,2,4] $ .

Note that Berland is a high-tech country. So using nanotechnologies all roads were altered so that they have the same length. For the same reason moving using regular cars is not very popular in the country, and it can happen that there are such pairs of cities, one of which generally can not be reached by car from the other one. However, Cicasso is very conservative and cannot travel without the car. Choose cities so that the sculptor can make the tour using only the automobile. It is guaranteed that it is always possible to do.

## 说明/提示

Let $ d(x,y) $ be the shortest distance between cities $ x $ and $ y $ . Then in the example $ d(2,1)=3,d(1,8)=7,d(8,7)=3 $ . The total distance equals $ 13 $ .

## 样例 #1

### 输入

```
8 9
1 2
2 3
3 4
4 1
4 5
5 6
6 7
7 8
8 5
```

### 输出

```
2 1 8 7
```

# 题解

## 作者：Juanzhang (赞：7)

**思路：**

- $bfs$+~~暴力~~枚举

> 找到$a,b,c,d$四点，使得$a$到$b$的最短路$+b$到$c$的最短路$+c$到$d$的最短路最长

首先，可以想到枚举四点，计算最短路，$O(n^5)$

然后，发现可以预处理出多源最短路，因为边权相同，可以对每一点$bfs$~~（反正bfs比spfa快）~~，$O(n^4)$

接着，发现只要预处理出连向$b$点的尽量远的一点，$c$连向的尽量远的一点就可以以$O(n^2)$完成

*但我们仅仅预处理出连向$b$点的**最**远的一点，$c$连向的**最**远的一点就够了吗？*

假如$c$点连向的最远的一点为$k$，连向$b$点的最远的一点为$l$，

若$k=l$。。。

所以最远是不够的

*但我们仅仅预处理出连向$b$点的**最**远，**次**远的一点，$c$连向的**最**远，**次**远的一点就够了吗？*

假如$c$点连向的最远的一点为$k_1$，次远的一点为$k_2$；连向$b$点的最远的一点为$l_1$，次元的一点为$l_2$

若$k_1=l_1\& k_2=b$

所以次远是不够的

第三远呢？

假设最远相同，次远已被选被，还有第三远

因此第三远已足够

时间复杂度$O(n^2)$

**核心代码：**

``` cpp
#include <bits/stdc++.h>
using namespace std;

···

	for (int j = 1; j <= n; j++) {
		for (int k = 1; k <= n; k++) {
			if (j == k) {
				continue;
			}
			for (pii p1 : pre[j]) {
				int i = p1.sec;
				if (i == j || i == k) {
					continue;
				}
				for (pii p2 : nxt[k]) {
					int l = p2.sec;
					if (i == l || j == l || k == l) {
						continue;
					}
					if (sum < dis[i][j] + dis[j][k] + dis[k][l]) {
						sum = dis[i][j] + dis[j][k] + dis[k][l];
						ans[1] = i, ans[2] = j, ans[3] = k, ans[4] = l;
					}
				}
			}
		}
	}
```

与@王景毅 大佬的~~暴力~~枚举相似。。

---

## 作者：sane1981 (赞：6)

# CF666B题目解读
[原题传送门 Luogu](https://www.luogu.com.cn/problem/CF666B) [原题传送门 Codeforces](https://codeforces.com/problemset/problem/666/B)

这个编号真好，666。

好了，本题被某位神犇解释的清楚明白了，那我们直接讲思路。

这道题目其实和 2022 年的 S 组的第一题有异曲同工之妙，思路也差不都。都是用 BFS 预处理全源最短路 (~~因为 SPFA 已经死了~~)。$O(n^4)$ 枚举所有的点显然会 TLE。所以可以枚举 $b,c$ 两点，然后只枚举前三大的 $a,d$ 点。至于为什么，经过不少大神的指导，我终于明白了。

假设我们已经枚举好了 $b,c$ 两点，那么我们现在求 $dis(a,b)$ 和 $dis(c,d)$ 的最大值。如果出现类似 $a=c$ 或 $a=d$ 或 $b=c$ 这几种情况，那么们我们的代码就 GG 了。

如果我们枚举到第二大呢？很遗憾，可能会出现这种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/ue1j090b.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

枚举到第三大就没有问题了，我的理解是对于 $a$ 最多只会和 $d,c$ 冲突。那么第三大的 $dis(a,b)$ 就一定会满足要求，那么第四大，第五大的也就没必要去枚举了。

还有要注意这里是有向边，因此 $dis(u,v)$ 不一定等于 $dis(v,u)$ 所以操作时要开两个数组。
# AC Code
```cpp
#include<bits/stdc++.h>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int,int> PII;
const int N=3005;
int n,m,a,b,ans,f1,f2,f3,f4;
int head[N],tot;
struct edge{
	int next,to;
}g[5005];
vector <PII> A[N],B[N];
int dis[N][N];
bool inq[N];
bool cmp(PII X,PII Y){
	return X.first>Y.first;
}
void add(int u,int v){
	g[++tot]=(edge){head[u],v};
	head[u]=tot;
}
void SPFA(int s){
	queue <int> Q;
	for(int i=1;i<=n;i++) dis[s][i]=1<<30,inq[i]=false;
	Q.push(s);
	dis[s][s]=0,inq[s]=true;
	while(!Q.empty()){
		int u=Q.front();Q.pop();
		inq[u]=false;
		for(int i=head[u];i;i=g[i].next){
			int v=g[i].to;
			if(dis[s][v]>dis[s][u]+1){
				dis[s][v]=dis[s][u]+1;
				if(!inq[v]) Q.push(v),inq[v]=true;
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	for(int i=1;i<=n;i++){
		SPFA(i);
		for(int j=1;j<=n;j++)
			if(dis[i][j]==1<<30) dis[i][j]=-1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			if(dis[i][j]!=-1) A[i].push_back(make_pair(dis[i][j],j));
			if(dis[j][i]!=-1) B[i].push_back(make_pair(dis[j][i],j));
		}
		sort(A[i].begin(),A[i].end(),cmp);
		sort(B[i].begin(),B[i].end(),cmp);
	}
	for(int x2=1;x2<=n;x2++){
		for(int x3=1;x3<=n;x3++){//枚举b,c 
			if(x2==x3||dis[x2][x3]==-1) continue;
			for(int k1=0;k1<3&&k1<B[x2].size();k1++){
				int x1=B[x2][k1].second;
				if(x1==x3||x1==x2) continue;
				int w1=B[x2][k1].first;
				for(int k2=0;k2<3&&k2<A[x3].size();k2++){
					int x4=A[x3][k2].second;
					if(x4==x1||x4==x2||x4==x3) continue;
					int w4=A[x3][k2].first;
					if(ans<dis[x2][x3]+w1+w4){
						ans=dis[x2][x3]+w1+w4;
//						printf("distance: %d->%d->%d->%d = %d+%d+%d = %d \n",x1,x2,x3,x4,w1,dis[x2][x3],w4,ans);
						f1=x1;f2=x2;f3=x3;f4=x4;
					}
				}
			} 
		}
	}
//	cout<<ans<<endl;
	printf("%d %d %d %d\n",f1,f2,f3,f4);
	return 0; 
}
```
此外发一下 [P8817 [CSP-S 2022] 假期计划](https://www.luogu.com.cn/problem/P8817) 。

---

## 作者：猪龙骨丶丶 (赞：6)

n<=3000 m<=5000稀疏图选贼spfa而不是dijkstra
先n2logn预处理每两个点之间的最短路的最长距离，因为只有4个点，时长5s，我们可以暴力枚举中间2个点，~~枚举4个会t~~，求得答案且每个点不需要枚举所有与他连通的点，先排序，最多只有3个点是重的。



```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4000,M=6000;
struct qwq{
	int to,next;
}e[M];
int head[N],cnt=0,n,m,d[N][N];	int vst[N]={};
vector< pair<int,int> >a[N],b[N];
void add(int from,int to)
{
	e[++cnt].next =head[from],head[from]=cnt,e[cnt].to=to;
}
void spfa(int s)
{
memset(vst,0,sizeof(vst));
	queue<int>q;
	d[s][s]=0;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop(),vst[u]=0;
		for(int i=head[u];i;i=e[i].next ){
			int v=e[i].to;
			if(d[s][v]>d[s][u]+1||d[s][v]==-1){
				d[s][v]=d[s][u]+1;
				if(!vst[v]){
					vst[v]=1;
					q.push(v);
				}
			}
		}
	}
}
void init()
{
	memset(d,-1,sizeof(d));
	for(int t=1;t<=n;t++){
		spfa(t);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b),add(a,b);
		
		
	}
	init();
	int ans=0,aa,bb,cc,dd;
	for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
			if(i==j)
			continue;
			if(d[i][j]!=-1)
			a[i].push_back(make_pair(d[i][j],j));
			if(d[j][i]!=-1)
			b[i].push_back(make_pair(d[j][i],j));
		}
		sort(a[i].begin(),a[i].end());
		sort(b[i].begin(),b[i].end());
	}
	for(int n2=1;n2<=n;n2++){
		int sn2=b[n2].size(),n1,n4;
		for(int n3=1;n3<=n;n3++){
			if(n2==n3||d[n2][n3]==-1)
			continue;
			int sn3=a[n3].size();
			for(int sn1=sn2-1;sn1>=0&&sn1>=sn2-3;sn1--){
				n1=b[n2][sn1].second;
				if(n1==n2||n1==n3)continue;
				for(int sn4=sn3-1;sn4>=0&&sn4>=sn3-3;sn4--){
					int n4=a[n3][sn4].second;
					if(n4==n2||n4==n3||n4==n1)
					continue;
					if(ans<d[n1][n2]+d[n2][n3]+d[n3][n4])
					{
						ans=d[n1][n2]+d[n2][n3]+d[n3][n4];
						aa=n1,bb=n2,cc=n3,dd=n4;
					}
				}
			}
			
		}
	}
	cout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<" ";
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

乍一看很难，但仔细一想，跑n次spfa，然后每个点记录3个备选，最后暴力枚举中间的两个即可。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=1<<20;
const int N=3005;
vector< pair<int,int> >a[N],b[N];
vector<int>c[N];
int dis[N][N];
bool vis[N];
int ans[5];
int n,m,x,y;
void spfa(int i)
{
   memset(vis,0,sizeof(vis));
   queue<int>q;
   q.push(i);
   vis[i]=1;
   while(!q.empty())
   {
       int x=q.front();
	   q.pop();
       vis[x]=0;
       for(int j=0;j<c[x].size();j++)
       {
           int nxt=c[x][j];
           if(dis[i][nxt]>dis[i][x]+1)
           {
               dis[i][nxt]=dis[i][x]+1;
               if(!vis[nxt])
               {
                   vis[nxt]=1;
                   q.push(nxt);
               }
           }
       }
   }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
        {
            if(i==j)
			  	dis[i][j]=0;
            else
			  	dis[i][j]=INF;
        }
	}
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        c[x].push_back(y);
    }
    for(int i=1;i<=n;i++)
        spfa(i);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j)
				continue;
            if(dis[i][j]!=INF)
				a[i].push_back(make_pair(dis[i][j],j));
            if(dis[j][i]!=INF)
				b[i].push_back(make_pair(dis[j][i],j));
        }
        sort(a[i].begin(),a[i].end());
        sort(b[i].begin(),b[i].end());
    }
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        int nb=b[i].size();
        for(int j=1;j<=n;j++)
        {
            if(i==j||dis[i][j]==INF)
				continue;
            int ma=a[j].size();
            for(int k=nb-1;k>=0&&k>=nb-3;k--)
            {
                int kk=b[i][k].second;
                if(kk==i||kk==j)
					continue;
                for(int p=ma-1;p>=0&&p>=ma-3;p--)
                {
                    int pp=a[j][p].second;
                    if(pp==i||pp==j||pp==kk)
						continue;
                    if(sum<dis[kk][i]+dis[i][j]+dis[j][pp])
                    {
                        sum=dis[kk][i]+dis[i][j]+dis[j][pp];
                        ans[1]=kk;
						ans[2]=i;
						ans[3]=j;
						ans[4]=pp;
                    }
                }
            }
        }
    }
    for(int i=1;i<=4;i++)
		printf("%d ",ans[i]);
	printf("\n");
    return 0;
}

```

---

## 作者：james1BadCreeper (赞：1)

对每个点进行 bfs 求出任意两点之间的最短路，然后枚举 $b,c$。要使得最短路最大，我们只需要找一个最大的 $a\rightarrow b$ 和 $c\rightarrow d$，直接预处理即可。但是这样可能会有重复，因此考虑记录前三大的然后判重。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m; 
int dis[3005][3005], to[3005][3], fr[3005][3]; 
vector<int> G[3005]; 

int main(void) {
    scanf("%d%d", &n, &m); 
    while (m--) {
        int u, v; scanf("%d%d", &u, &v); 
        G[u].emplace_back(v); 
    } memset(dis, -1, sizeof dis); 
    for (int s = 1; s <= n; ++s) {
        queue<int> q; dis[s][s] = 0; q.push(s); 
        while (!q.empty()) {
            int u = q.front(); q.pop(); 
            for (int v : G[u]) if (dis[s][v] == -1) dis[s][v] = dis[s][u] + 1, q.push(v); 
        }
    }
    for (int i = 1; i <= n; ++i) {
        int tmp[5], tot = 0; memset(tmp, 0, sizeof tmp); 
        for (int j = 1; j <= n; ++j) if (j != i && dis[j][i] != -1) {
            tmp[tot++] = j;
            sort(tmp, tmp + tot, [&](const int x, const int y) { return dis[x][i] > dis[y][i]; }); 
            if (tot == 4) tot = 3; 
        }
        for (int j = 0; j < 3; ++j) to[i][j] = tmp[j]; 
        tot = 0; memset(tmp, 0, sizeof tmp); 
        for (int j = 1; j <= n; ++j) if (j != i && dis[i][j] != -1) {
            tmp[tot++] = j;
            sort(tmp, tmp + tot, [&](const int x, const int y) { return dis[i][x] > dis[i][y]; }); 
            if (tot == 4) tot = 3; 
        }
        for (int j = 0; j < 3; ++j) fr[i][j] = tmp[j]; 
    }
    int aa, bb, cc, dd, ans = 0; 
    for (int b = 1; b <= n; ++b) for (int c = 1; c <= n; ++c) if (b != c && dis[b][c] != -1) {
        int a = 0, d = 0; 
        for (int i = 0; i < 3; ++i) if (dis[to[b][i]][b] != -1 && to[b][i] != c) { a = to[b][i]; break; }
        for (int i = 0; i < 3; ++i) if (dis[c][fr[c][i]] != -1 && fr[c][i] != a && fr[c][i] != b) { d = fr[c][i]; break; }
        
        int res = dis[a][b] + dis[b][c] + dis[c][d]; 
        if (a && d && res > ans) ans = res, aa = a, bb = b, cc = c, dd = d; 

        a = 0, d = 0; 
        for (int i = 0; i < 3; ++i) if (dis[c][fr[c][i]] != -1 && fr[c][i] != b) { d = fr[c][i]; break; }
        for (int i = 0; i < 3; ++i) if (dis[to[b][i]][b] != -1 && to[b][i] != c && to[b][i] != d) { a = to[b][i]; break; }
        res = dis[a][b] + dis[b][c] + dis[c][d]; 
        if (a && d && res > ans) ans = res, aa = a, bb = b, cc = c, dd = d; 
        
    }
    return printf("%d %d %d %d\n", aa, bb, cc, dd), 0; 
}
```

---

## 作者：sprads (赞：1)

### 前言

考试时没有做出来，差了亿点点。强迫自己写篇题解。

### 题意概述

给定 $n$ 个点，$m$ 条边的有向图。

记 $x$ 到 $y$ 的最短路为 $d(x,y)$。

选出四个**不同的**点 $a,b,c,d$，使得 $d(a,b)+d(b,c)+d(c,d)$ 最大。

### 思路

首先任意两点的最短路很好求，因为 $n \le 3000,m\le 5000$，直接在一开始将每个点作为起点 BFS 即可。时间复杂度 $O(nm)$。

此时就有一个很简单的思路，暴力枚举四个点，$O(1)$ 计算 $d(a,b)+d(b,c)+d(c,d)$，就可以做到 $O(n^4)$。

但是这显然不够，数据范围要求我们最多枚举两个点。观察到 $b,c$ 两个点在式子中出现两次，不妨枚举它们两个，再来确定 $a,d$。

于是很自然地想到对于每个点 $x$ 预处理出 $d(y,x)$ 最大的 $y$ 和 $d(x,z)$ 最大的 $z$。

枚举 $b,c$ 时就可以 $O(1)$ 找到 $d(y,b)$ 最大的 $y$ 作为 $a$，$d(c,z)$ 最大的 $z$ 作为 $d$，使得此时 $d(a,b)+d(b,c)+d(c,d)$ 最大。

但是，我们枚举 $b,c$ 时，通过 $b,c$ 找到的 $a,d$ 可能相同或等于 $b$ 和 $c$，因此，直接找最大是行不通的。（~~考试时想到这就寄了~~）

但是（没错还有但是），点 $a,d$ 只要不与另外三点重复即可，因此只需要预处理出 $d$ 值前三大的点，就可以通过调配使得 $a,b,c,d$ 互不相同。（具体的细节可以看代码）

时间复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
#define res(a,b,c,d) h[a][b] + h[b][c] + h[c][d]
using namespace std;
const int N = 3005,M = 5005,INF = 0xcfcfcfcf;//INF是一个极小值
int tot,head[N],ver[M],Next[M];
int n,m,h[N][N],s[N][3],t[N][3],A,B,C,D,ans;
// s[x][0]存储y表示d(y,x)最大，s[x][1]存储y表示d(y,x)次大,s[x][2]存储表示d(y,x)第三大
// t[x][0]则是反过来，例如t[x][0]存储z表示d(x,z)最大
void add(int x,int y){
	tot++;
	ver[tot] = y;
	Next[tot] = head[x];
	head[x] = tot;
}
void BFS(int s,int (&d)[N]){
	queue<int> q;
	d[s] = 0;
	q.push(s);
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(int i = head[x];i;i = Next[i]){
			int y = ver[i];
			if(d[y] == INF){
				d[y] = d[x] + 1;
				q.push(y);
			}
		}
	}
}
void prework(){//预处理前三大
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			if(i == j)continue;
			for(int k = 0;k < 3;k++){//写了个形似插入排序的东西
				if(h[i][t[i][k]] <= h[i][j]){
					for(int l = 2;l > k;l--)
						t[i][l] = t[i][l - 1];
					t[i][k] = j;
					break;
				}
			}
			for(int k = 0;k < 3;k++){
				if(h[s[j][k]][j] <= h[i][j]){
					for(int l = 2;l > k;l--)
						s[j][l] = s[j][l - 1];
					s[j][k] = i;
					break;
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	memset(h,0xcf,sizeof(h));
	for(int i = 1;i <= n;i++)
		BFS(i,h[i]);//以i作为起点，BFS求最短路
	prework();
	for(int b = 1;b <= n;b++){
		for(int c = 1;c <= n;c++){
			if(b == c || h[b][c] == INF)continue;
			int x = 0,y = 0;
			if(s[b][x] == c)x++;//如果与c相同，跳过
			if(t[c][y] == b)y++;//如果与b相同，跳过
			if(s[b][x] == t[c][y]){//找到的ad相同，分两种情况
				int i = x + 1,j = y + 1;
				if(s[b][i] == c)i++;//换一个a,当然还要保证a不为c
				if(t[c][j] == b)j++;//换一个c，同上不为b
				int a = s[b][x],d = t[c][j];
				if(res(a,b,c,d) > ans){//换d不换a
					A = a,B = b,C = c,D = d;
					ans = res(a,b,c,d);
				}
				a = s[b][i],d = t[c][y];
				if(res(a,b,c,d) > ans){//换a不换d
					A = a,B = b,C = c,D = d;
					ans = res(a,b,c,d);
				}
           //两个同时换显然不优，不做讨论
			}
			else{
				int a = s[b][x],d = t[c][y];//ad不相同，直接与答案比较
				if(res(a,b,c,d) > ans){
					A = a,B = b,C = c,D = d;
					ans = res(a,b,c,d);
				}
			}
		}
	}
	printf("%d %d %d %d\n",A,B,C,D);
	return 0;
}
```


---

## 作者：kfhkx (赞：1)

看到没有Pascal，就来一波吧~


## 题意：

给你一张n个点m条边的有向图，让你给出四个点的序列s1->s2->s3->s4，使得这四个点依次间的最短路之和最大。(4 ≤ n ≤ 3000, 3 ≤ m ≤ 5000) 

时空限制 5000ms / 512MB （非常充裕~）

## 思路：

1. 正向和反向各建一个图，然后各跑n次最短路($ 2n^3 $)

这里我用的是链式前向星+堆优化的dijkstra

2. 暴力枚举找3个最长的最短路的点作为备选，多选一个的原因是怕选了重点($ 2n^2 $)

3. 最后再从3个中暴力选出2个点，就搞定了($ 9n^2 $)

总计  $ 13n^2 $

------------


这样的思路看起来很暴力，但是打得很爽，感觉能特别深刻的感受到暴力枚举和最短路的魅力~

下面附上5.2k的工整代码 

无指针，阅读体验极佳

## CF666B(真6).pas

```pascal
var
        n,m,i,j,k,l,tot,v,head,st1,st2,st3,ans,bns1,ans1,ans2,ans3,s1,s2,s3,s4:longint;
        he,ne,t,w,cj,num,heap,dis:array[0..400010] of longint;
        x,y:array[0..300010] of longint;
        bis,bh1,yh1,bh2,yh2,bj:array[0..3010,0..3010] of longint;
procedure swap(var x,y:longint);//自定义交换函数
var
        t:longint;
begin
        t:=x;
        x:=y;
        y:=t;
end;
procedure link(x,y,z:longint);//链式前向星
begin
        inc(tot);
        ne[tot]:=he[x];
        he[x]:=tot;
        t[tot]:=y;
        w[tot]:=z;
end;
//以下为堆优化
//**
procedure insert(a,x:longint);
var
        i:longint;
begin
        if cj[x]<>0 then begin
                heap[cj[x]]:=a;
                i:=cj[x];
        end else begin
                inc(heap[0]);
                heap[heap[0]]:=a;
                num[heap[0]]:=x;
                i:=heap[0];
                cj[x]:=heap[0];
        end;
        while (i>>1>0) and (heap[i]<heap[i>>1]) do begin
                swap(cj[num[i]],cj[num[i>>1]]);
                swap(heap[i],heap[i>>1]);
                swap(num[i],num[i>>1]);
                i:=i>>1;
        end;
end;
procedure del;
var
        mid,i:longint;
begin
        cj[num[1]]:=0;
        heap[1]:=heap[heap[0]];
        num[1]:=num[heap[0]];
        dec(heap[0]);
        i:=1;
        if (heap[i<<1]<heap[i<<1+1]) or (i=heap[0]) then mid:=i<<1 else mid:=i<<1+1;
        while (mid<=heap[0]) and (heap[mid]<heap[i]) do begin
                swap(cj[num[i]],cj[num[mid]]);
                swap(heap[i],heap[mid]);
                swap(num[i],num[mid]);
                i:=mid;
                if (heap[i<<1]<heap[i<<1+1]) or (i<<1=heap[0]) then mid:=i<<1 else mid:=i<<1+1;
        end;
end;
//**
procedure dij(x:longint);//标准dijkstra
var
        i:longint;
begin
        for i:=1 to n do begin
                dis[i]:=maxlongint;
                heap[i]:=0;
                num[i]:=0;
                cj[i]:=0;
        end;
        dis[x]:=0;
        head:=x;
        heap[0]:=1;
        heap[1]:=0;
        num[1]:=x;
        while heap[0]<>0 do begin
                v:=he[head];
                while v<>0 do begin
                        if dis[t[v]]>dis[head]+w[v] then begin
                                dis[t[v]]:=dis[head]+w[v];
                                insert(dis[t[v]],t[v]);
                        end;
                        v:=ne[v];
                end;
                del;
                head:=num[1];
        end;
//暴力枚举3个点
//**
        ans1:=0;
        ans2:=0;
        ans3:=0;
        st1:=0;
        st2:=0;
        st3:=0;
        for j:=1 to n do begin
                if (dis[j]=maxlongint) or (dis[j]=0) then continue;
                if dis[j]>ans3 then begin
                        if dis[j]>ans2 then begin
                                if dis[j]>ans1 then begin
                                        ans3:=ans2;
                                        st3:=st2;
                                        ans2:=ans1;
                                        st2:=st1;
                                        ans1:=dis[j];
                                        st1:=j;
                                 end else begin
                                        ans3:=ans2;
                                        st3:=st2;
                                        ans2:=dis[j];
                                        st2:=j;
                                 end
                        end else begin
                                ans3:=dis[j];
                                st3:=j;
                        end;
                end;
        end;
//**
end;
procedure fz1(x,y:longint);//将找到的点保存在数组里面
begin
        bh1[x,y+1]:=ans1;
        bh1[x,y+2]:=ans2;
        bh1[x,y+3]:=ans3;
        yh1[x,y+1]:=st1;
        yh1[x,y+2]:=st2;
        yh1[x,y+3]:=st3;
end;
procedure fz2(x,y:longint);
begin
        bh2[x,y+1]:=ans1;
        bh2[x,y+2]:=ans2;
        bh2[x,y+3]:=ans3;
        yh2[x,y+1]:=st1;
        yh2[x,y+2]:=st2;
        yh2[x,y+3]:=st3;
end;
begin
        readln(n,m);
        for i:=1 to m do begin
                read(x[i],y[i]);
                if x[i]=y[i] then continue;
                link(x[i],y[i],1);//正向存图
        end;
        for i:=1 to n do begin
                dij(i);
                fz1(i,0);
                for j:=1 to n do bis[i,j]:=dis[j];
        end;
        tot:=0;
        fillchar(he,sizeof(he),0);
        for i:=1 to m do begin
                if x[i]=y[i] then continue;
                link(y[i],x[i],1);//反向存图
        end;
        for i:=1 to n do begin
                dij(i);
                fz2(i,0);
        end;
//3中选2
        s1:=1;
        s2:=2;
        s3:=3;
        s4:=4;
        ans:=-maxlongint;
        for i:=1 to n do for j:=1 to n do if (bis[i,j]<>maxlongint) and (bis[i,j]<>0) then
         for k:=1 to 3 do for l:=1 to 3 do begin
                ans1:=yh1[j,k];
                bns1:=yh2[i,l];
                if (bns1<>i) and (bns1<>j) and (bns1<>ans1) and (i<>j) and (i<>ans1) and (j<>ans1) and (ans1<>0) and (bns1<>0) then
                 if bh1[j,k]+bh2[i,l]+bis[i,j]>ans then begin
                        s1:=bns1;
                        s2:=i;
                        s3:=j;
                        s4:=ans1;
                        ans:=bh1[j,k]+bh2[i,l]+bis[i,j];
                end;
        end;
        write(s1,' ',s2,' ',s3,' ',s4);//完美输出
end.
```

---

## 作者：luan341502 (赞：0)

假期计划弱化版。

对于数据范围 $n \le 3000$，显然我们可以跑 $n$ 次 dijkstra 求出每两点间最短路。

对于四个点的选取，我们枚举中间的两个点 $b$、$c$，然后对于 $b$ 点取到这个点的最短路前四小的点作为 $a$，并同理选取 $d$。用四个点更新答案即可。

注意判断四个点中有相同的点、没有路径连接这几种特殊情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct edge{
	int to,next;
}e[100005];
int head[3005],cnt=0;
int dis[3005][3005];
bool vis[3005];
struct Dis{
	int dis,id;
}dis1[3005][3005],dis2[3005][3005];
int ans=0,ansa,ansb,ansc,ansd;
bool cmp(Dis x,Dis y){
	return x.dis>y.dis;
}
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void dijkstra(int s){
	priority_queue<pair<int,int> > q;
	for(int i=1;i<=n;i++) dis[s][i]=1e9,vis[i]=false;
	dis[s][s]=0;q.push(make_pair(0,s));
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;vis[x]=true;
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			if(dis[s][y]>dis[s][x]+1){
				dis[s][y]=dis[s][x]+1;
				q.push(make_pair(-dis[s][y],y));
			}
		}
	}
}
void solve(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;cin>>u>>v;
		add(u,v);
	}
	for(int i=1;i<=n;i++) dijkstra(i);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) if(dis[i][j]>=1e9) dis[i][j]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) dis1[i][j].dis=dis[i][j],dis1[i][j].id=j;
		sort(dis1[i]+1,dis1[i]+n+1,cmp);
		for(int j=1;j<=n;j++) dis2[i][j].dis=dis[j][i],dis2[i][j].id=j;
		sort(dis2[i]+1,dis2[i]+n+1,cmp);
	}
	for(int b=1;b<=n;b++){
		for(int c=1;c<=n;c++){
			if(b==c) continue;
			for(int x=1;x<=4;x++)
				for(int y=1;y<=4;y++){
					int a=dis2[b][x].id,d=dis1[c][y].id;
					if(!dis[a][b]||!dis[b][c]||!dis[c][d]) continue;
					if(a==b||a==c||a==d||b==c||b==d||c==d) continue;
					int now=dis[a][b]+dis[b][c]+dis[c][d];
					if(ans<now) ans=now,ansa=a,ansb=b,ansc=c,ansd=d;
				}
		}
	}
	cout<<ansa<<" "<<ansb<<" "<<ansc<<" "<<ansd<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	/*int tt;cin>>tt;while(tt--)*/solve();
	return 0;
}
```


---

## 作者：Xiphi (赞：0)

摘自我的 blog。

首先来做 P8817，时隔一年终于补完了！

思路很妙。从暴力 $n^4$ 开始考虑。首先发现可以只枚举中间 $B,C$ 两点，接着用枚举 $A$，然后 bitset 取 AND，复杂度 $n^4/w$。然后考虑预处理，设 $pos1_{i,j}$ 表示 点 $B$ 为 $i$ 时，满足条件的点权最大的点是多少。 $C$ 点同理，接着就在枚举 $B,C$ 时，只枚举 $3^2$ 次，算出 $B,C$ 为 $i,j$ 时，点权最大和为多少。注意一些细节，如不是连通图的情况（不是连通图就要 `memset` $dis$ 数组）。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k;
int v[5005];
vector<int> Adj[5005];
int dis[2505][2505],vis[2505];
set<pair<int,int>,greater<pair<int,int>>> pos1[2505];
void bfs(int s){
	queue<int> q;
	q.push(s);
	vis[s]=1;
	dis[s][s]=0;
	while(!q.empty()){
		int top=q.front();
		q.pop();
		for(int i=0;i<Adj[top].size();++i){
			if(!vis[Adj[top][i]]){
				dis[s][Adj[top][i]]=dis[s][top]+1;
				vis[Adj[top][i]]=1;
				q.push(Adj[top][i]);
			}
		}
	}
}
signed main(){
//	freopen("holiday3.in","r",stdin);
//	freopen("holiday3.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>m>>k;
	memset(dis,0x3f,sizeof dis);
	for(int i=2;i<=n;++i) cin>>v[i];
	for(int i=1,x,y;i<=m;++i){
		cin>>x>>y;
		Adj[x].push_back(y);
		Adj[y].push_back(x);
	}
	for(int i=1;i<=n;++i){
		bfs(i);
		memset(vis,0,sizeof vis);
	}
//	for(int i=1;i<=n;++i){
//		for(int j=1;j<=n;++j){
//			cout<<dis[i][j]<<' ';
//		}
//		cout<<'\n';
//	}
	for(int i=2;i<=n;++i){
		for(int j=2;j<=n;++j){
			if(i==j) continue;
			if(dis[1][j]<=k+1&&dis[j][i]<=k+1){
				pos1[i].insert({v[j],j});
				if(pos1[i].size()>3) pos1[i].erase(--pos1[i].end());
			}
		}
	}
	int Ans=0;
	for(int i=2;i<=n;++i){
		for(int j=2;j<=n;++j){
			if(i==j ) continue;
			if(dis[i][j]>k+1) continue;
			for(set<pair<int,int>,greater<pair<int,int>>>::iterator it=pos1[i].begin();it!=pos1[i].end();++it){
				for(set<pair<int,int>,greater<pair<int,int>>>::iterator it1=pos1[j].begin();it1!=pos1[j].end();++it1){
					pair<int,int> t1=*it,t2=*it1;
					if(t1.second!=t2.second&&t1.second!=j&&t2.second!=i&&t1.second!=i&&t2.second!=j){
						Ans=max(Ans,t2.first+t1.first+v[i]+v[j]);
					}
				}
			}
		}
	}
	cout<<Ans;
	return 0;
}
```

CF666B 跟这题差不多， bfs 预处理全源最短路，然后枚举 $B,C$ 两点。平凡的，接着就是一样的预处理，只需要预处理距离前三大即可。预处理部分简单来说就是枚举 $B$ 然后枚举中转点 $A$。

---

## 作者：WaterSun (赞：0)

CSP-2022 S2 T1 弱化版。

# 思路

首先因为边权均为 $1$，所以我们可以在 $\Theta(n^2)$ 的复杂度用 BFS 求解出任意两点 $i,j$ 的最短距离 $d_{i,j}$（如果 $i$ 不能到达 $j$，则令  $d_{i,j} = -1$）。

有一个贪心的结论，就是使每一条 $A \to B,B \to C,C \to D$ 的路径长度都更大，我们就想让每一条边都是以每一个点为起点的最长路。

但是，显然这样做事有可能会冲突的，因为有可能有以两个不同的点为起点的最长路的终点可能相同。

所以考虑多处理出次长路和次次长路，这样就一定不会冲突。因为当 $A \to B$ 和 $B \to C$ 冲突时，$B \to C$ 可以用次长路；又当 $B \to C$ 和 $C \to D$ 冲突时，$C \to D$ 可以用次次长路。所以处理出前 $3$ 大的足矣。

然后求方案，考虑用一个 `vector<pii> dm[i][0/1]` 分别存储以 $i$ 为起点的路径，以及以其他点为起点到达 $i$ 的路径。（**注意：当起点为 $i$，终点为 $j$ 时，如果满足 $d_{i,j} \neq -1$ 时，才能将 $i \to j$ 的路径存入**）

然后枚举 $B,C$，再用这个 `vector` 枚举出 $A,D$ 即可。

因为上文提到，用前 $3$ 大路径一定能凑出最终答案，所以在枚举 $A,D$ 时枚举前 $3$ 大即可。保证了时间复杂度为 $\Theta(n^2)$。

# code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 3010,M = 5010;
int n,m,Max,A,B,C,D;
int idx,h[N],e[M],ne[M];
int dist[N][N];
vector<pii> dm[N][2];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void add(int a,int b){
	ne[idx] = h[a];
	e[idx] = b;
	h[a] = idx++;
}

inline void bfs(int s){
	queue<int> q;
	dist[s][s] = 0;
	q.push(s);
	while (!q.empty()){
		int t = q.front();
		q.pop();
		for (re int i = h[t];~i;i = ne[i]){
			int j = e[i];
			if (!~dist[s][j]){
				dist[s][j] = dist[s][t] + 1;
				q.push(j);
			}
		}
	}
}

int main(){
	memset(h,-1,sizeof(h));
	memset(dist,-1,sizeof(dist));
	n = read();
	m = read();
	for (re int i = 1;i <= m;i++){
		int a,b;
		a = read();
		b = read();
		add(a,b);
	}
	for (re int i = 1;i <= n;i++) bfs(i);
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= n;j++){
			if (i == j) continue;
			if (~dist[i][j]) dm[i][0].push_back({dist[i][j],j});
			if (~dist[j][i]) dm[i][1].push_back({dist[j][i],j});
		}
		sort(dm[i][0].begin(),dm[i][0].end(),[](const pii &a,const pii &b){
			return a.fst > b.fst;
		});
		sort(dm[i][1].begin(),dm[i][1].end(),[](const pii &a,const pii &b){
			return a.fst > b.fst;
		});
	}
	for (re int b = 1;b <= n;b++){
		for (re int c = 1;c <= n;c++){
			if (c == b || !~dist[b][c]) continue;//不能有重复元素，且 b 一定能到达 c 
			int lb = dm[b][1].size();
			for (re int p = 0;p < 3 && p < lb;p++){
				int a = dm[b][1][p].snd;
				if (a == b || a == c) continue;//同理 
				int lc = dm[c][0].size();
				for (re int q = 0;q < 3 && q < lc;q++){
					int d = dm[c][0][q].snd;
					if (d == a || d == b || d == c) continue;//同理 
					if (Max < dist[a][b] + dist[b][c] + dist[c][d]){
						Max = dist[a][b] + dist[b][c] + dist[c][d];
						A = a;
						B = b;
						C = c;
						D = d;
					}
				}
			}
		}
	}
	printf("%d %d %d %d",A,B,C,D);
	return 0;
}
```

---

## 作者：SilverLi (赞：0)

[World Tour の 传送门](https://codeforces.com/problemset/problem/666/B)

> [更杂乱的阅读体验](https://www.cnblogs.com/Silver-Wolf/p/17742012.html)

> $4 \le n \le 3000$

说明可以用 $n^2$ 的做法，题目要求 $4$ 个点的最短路最长，共 $3$ 条路经，则枚举 $2$ 个点。

如果枚举 $a, c$，则要找 $b, d$，但 $b$ 和 $c$ 也要判断路径，比较麻烦，所以直接枚举 $b, c$。

然后枚举 $b, c$ 对应的最短路最长的点，因为枚举点共会 $6$ 种重合情况，而 $b, c$ 已经判掉了，所以只有 $5$ 种情况，就直接枚举最短路最长的前 $5$ 个 $a$，$d$ 同理。

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#define d first
#define id second
using namespace std;
constexpr int N = 3e3 + 5;
int n, m, vis[N];
vector<int> g[N];
int pre[N][N], dx[N][N];
pair<int, int> dis[N][N];
inline void dij(int s) {
	memset(dis[s], -1, sizeof(dis[s]));
	dis[s][s].d = 0;
	memset(dx[s], -1, sizeof(dx[s]));
	dx[s][s] = 0;
	for (int i = 1; i <= n; ++i)
		dis[s][i].id = i;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push({0, s});
	while (!q.empty()) {
		int u = q.top().id;
		q.pop();
		vis[u] = 1;
		for (int l = 0; l < g[u].size(); ++l) {
			int i = g[u][l];
			if (dis[s][i].d > dis[s][u].d + 1 || dis[s][i].d == -1) {
				dis[s][i].d = dis[s][u].d + 1;
				dx[s][i] = dx[s][u] + 1;
				if (!vis[i])	q.push({dis[s][i].d, i});
			}
		}
	}
	sort(dis[s] + 1, dis[s] + n + 1, greater<pair<int, int>>());
}
int id;
inline bool cmp(int a, int b) {
	return dx[a][id] > dx[b][id];
}
inline void special() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			if (dx[j][i] != -1)	pre[i][j] = j;
		id = i;
		sort(pre[i] + 1, pre[i] + n + 1, cmp);
	}
}
signed main() {
	cin >> n >> m;
	while (m--) {
		int u, v;
		cin >> u >> v;
		g[u].emplace_back(v);
	}
	for (int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof(vis));
		dij(i);
// 		cerr << "DIJ " << i << '\n';
// 		for (int j = 1; j <= n; ++j)
// 			cerr << "  " << dis[i][j].id << ' ' << dis[i][j].d << '\n';
	}
	special();
	int ans = 0, anss[5];
	for (int j = 1; j <= n; ++j)
		for (int k = 1; k <= n; ++k) {
			if (j == k || dx[j][k] == -1)	continue;
			for (int ix = 1; ix <= min(3, n); ++ix) {
				int i = pre[j][ix];
				if (i == j || k == i || i == 0)	continue;
				for (int lx = 1; lx <=  min(3, n); ++lx) {
					int l = dis[k][lx].id;
					if (i == l || k == l || j == l || l == 0)	continue;
					if (ans < dx[i][j] + dx[j][k] + dx[k][l]) {
						ans = dx[i][j] + dx[j][k] + dx[k][l];
//						printf("YEAH %d %d %d %d\n  %d %d %d\n", i, j, k, l, dx[i][j], dx[j][k], dx[k][l]);
						anss[1] = i, anss[2] = j, anss[3] = k, anss[4] = l;
					}
				}
			}
		}
	for (int i = 1; i <= 4; ++i)
		cout << anss[i] << ' ';
	return 0;
}
```

---

