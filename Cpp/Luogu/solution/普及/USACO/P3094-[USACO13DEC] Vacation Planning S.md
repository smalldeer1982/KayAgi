# [USACO13DEC] Vacation Planning S

## 题目描述

有N(1 <= N <= 200)个农场，用1..N编号。航空公司计划在农场间建立航线。对于任意一条航线，选择农场1..K中的农场作为枢纽(1 <= K <= 100, K <= N)。


当前共有M (1 <= M <= 10,000)条单向航线连接这些农场，从农场u\_i 到农场 v\_i, 将花费 d\_i美元。(1 <= d\_i <= 1,000,000).


航空公司最近收到Q (1 <= Q <= 10,000)个单向航行请求。第i个航行请求是从农场a\_i到农场 b\_i，航行必须经过至少一个枢纽农场（可以是起点或者终点农场），因此可能会多次经过某些农场。


请计算可行航行请求的数量，及完成所有可行请求的总费用。


## 说明/提示

There are three farms (numbered 1..3); farm 1 is a hub.  There is a $10 flight from farm 3 to farm 1, and so on.  We wish to look for trips from farm 3 to farm 2, from 2->3, and from 1->2.


The trip from 3->2 has only one possible route, of cost 10+7.  The trip from 2->3 has no valid route, since there is no flight leaving farm 2.  The trip from 1->2 has only one valid route again, of cost 7.


## 样例 #1

### 输入

```
3 3 1 3 
3 1 10 
1 3 10 
1 2 7 
3 2 
2 3 
1 2 
```

### 输出

```
2 
24 
```

# 题解

## 作者：Harry27182 (赞：8)

~~又是一道大水题......~~

------------
本题需要多源最短路。看到$n<=200$的范围，果断选择$Floyd$。
```cpp
for(int l=1;l<=n;l++)
	 for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	    	if(f[i][j]>f[i][l]+f[l][j])f[i][j]=f[i][l]+f[l][j];
            
```
记得先枚举中转点啊

然后先把$sum$设成正无穷，然后逐一枚举$1-k$,更新$sum$.
如果$sum$为正无穷，那么可行方案$--$,否则$ans+=sum$.
就可以完美$ac$了！

完整代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long//不要忘了开long long 
using namespace std;
int n,m,k,q,u,v,w,ans,sum,a,b;
int f[205][205];
signed main()
{
	cin>>n>>m>>k>>q;
	memset(f,63,sizeof(f));
	for(int i=1;i<=n;i++)f[i][i]=0;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		f[u][v]=min(f[u][v],w);
	}//初始化部分 
	for(int l=1;l<=n;l++)
	  for(int i=1;i<=n;i++)
	    for(int j=1;j<=n;j++)
	    	if(f[i][j]>f[i][l]+f[l][j])f[i][j]=f[i][l]+f[l][j];//弗洛伊德 
	int num=q;
	for(int i=1;i<=q;i++)
	{
		cin>>a>>b;
		sum=0x3f3f3f3f;
		for(int j=1;j<=k;j++)
		{
			sum=min(sum,f[a][j]+f[j][b]);
		}//枚举每一个中转 
		if(sum==0x3f3f3f3f)num--;//如果不通，方案-- 
		else ans+=sum;//否则加上最短路程 
	}
	cout<<num<<endl<<ans;
	return 0;
} 
```


---

## 作者：greenheadstrange (赞：7)

首先分析题目，题目中需要用到任意两点间最短路。

可以n次spfa，n次dijstra，或者floyed均可

再一看数据，n<=200 _nice！_

直接用floyed：

```cpp
for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
```
做完最短路后，只需在读入数据后枚举每一个点作为中转即可

```cpp
scanf("%d%d",&x,&y);
z=INF;
for(int i=1;i<=p;i++)
	z=min(z,f[x][i]+f[i][y]);
if(z!=INF)ans1++,ans2+=z;
```
最后，50分惨痛的教训，记得开long long哦！

废话少说，上代码：

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
int n,m,p,q,x,y,z,f[205][205];
long long ans1,ans2;
void floyed(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
}
int main(){
	scanf("%d%d%d%d",&n,&m,&p,&q);
	memset(f,0x3f,sizeof(f));//初始为极值 
	for(int i=1;i<=n;i++)f[i][i]=0;//点到自己的距离为0 
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		f[x][y]=min(f[x][y],z);//更新两点间的距离 
	}
	floyed();
	while(q--){
		scanf("%d%d",&x,&y);
		z=INF;
		for(int i=1;i<=p;i++)
			z=min(z,f[x][i]+f[i][y]);
		if(z!=INF)ans1++,ans2+=z;//统计答案 
	}
	printf("%lld\n%lld",ans1,ans2);
	return 0;
}

```


---

## 作者：XL4453 (赞：1)

Floyd 的板子题，稍微说一下这个算法本身和注意点吧。

------------
前置知识： Floyd

Floyd 是一种处理多元最短路的算法。

Floyd 的核心就是松弛操作，对于一对 $(x,y)$ ，求其最短路其实可以用一个新的点 $i$ 来优化，具体为 $(x,i)$ 与 $(i,y)$ 的和。Floyd 就是枚举所有的中转点，从而实现对于每一个点对都求出其最短路。

要理解 Floyd 要转化生活中（数学中）最常见的思维：两点之间线段最短。其实究其本质是因为 Floyd 中原本图并不一定就是线段之间的链接，可能有一条“直接链接”却是绕了好大的弯的路，反倒不如再经过一个点中转。

理解算法之后就是实现了。

具体做法为先枚举所有的中转点，然后枚举被优化的点，进行松弛即可。

代码实现为：

```cpp
void floyd(){
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	if(i!=k)//这一行和下面的判断可以不加，但加上会快一些，正确性上没什么问题。
	for(int j=1;j<=n;j++)
	if(i!=j&&j!=k)
	f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
}
```

然后就是一个远古的问题：为什么中转点要放在最外层？

自己的理解是这样的：对于中转点，其实是对于前 k 个点进行中转的最小距离，如果将其放到里面（在这种理解下，放到外面显然是对的），就不一定能保证这是在前 $k$ 个点中转后最优的，因为用来中转的点也不一定是最优的，就导致了最优子结构得不到保证，最终出错。（个人理解，希望大佬能给出更棒的解释$QAQ$）


------------
解题思路：

首先用 Floyd 求出任意两点之间的最小距离，然后对于每一个询问枚举中转点，求出距离即可。
___________________
注意点：

1. 初始化要把点到点本身的距离赋值为0。

2. Floyd 不可以处理负权环问题。（也就是一个总权值为负的环，然后就可以一直跑这个环，导致无解。）

_____________
代码：

```cpp
#include<cstdio>
using namespace std;
const int INF=0x3f3f3f3f;
int min(int x,int y){
	if(x<y)return x;
	return y;
}
int n,m,k,q,x,y,z,f[205][205],ans,tt;
long long num;
void floyd(){
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	if(i!=k)
	for(int j=1;j<=n;j++)
	if(i!=j&&j!=k)
	f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
}
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(i!=j)
	f[i][j]=INF;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		f[x][y]=min(f[x][y],z);
	}
	floyd();
	while(q--){
		scanf("%d%d",&x,&y);
		ans=INF;
		for(int i=1;i<=k;i++){
			ans=min(ans,f[x][i]+f[i][y]);
		}
		if(ans!=INF)num+=ans,tt++;
	}
	printf("%d\n%lld",tt,num);
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：1)

到[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)食用效果更佳

首先，这题需要用到任意两点间的最短路

因为$n \le 200$,所以可以用$O(n^3)$的Floyd预处理

$d_{i,j} = \min(d_{i, j}, d_{i, k} + d_{k, j})$

从外到内依次枚举$k, i, j$即可

此时$d_{x, y}$即为从$x$到$y$的最短路

在回答询问时，因为必须经过一个中转点，所以我们枚举每个中转点$j \in [1, k]$

令当前询问的最短路长度$val$为$\min(d_{x, j}, d_{j, y})$（设当前问的两个点为$x$,$y$, 且令$val$的初值为$\infty$）

最后若$val$不为无穷大，则更新答案

感觉我这篇题解已经讲得十分细致，还有不懂请参考代码

注意开long long！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, q, d[210][210], cnt;
long long ans;
int main() {
	memset(d, 0x3f, sizeof d);
	cin >> n >> m >> k >> q;
	for (register int i = 1; i <= n; ++i) d[i][i] = 0;
	for (register int i = 1; i <= m; ++i) {
		int u, v, a;
		scanf("%d%d%d", &u, &v, &a);
		d[u][v] = min(d[u][v], a);
	}
	for (register int k = 1; k <= n; ++k)
		for (register int i = 1; i <= n; ++i)
			for (register int j = 1; j <= n; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	for (register int i = 1; i <= q; ++i) {
		int x, y, val = 1e9;
		scanf("%d%d", &x, &y);
		for (register int j = 1; j <= k; ++j)	
			val = min(val, d[x][j] + d[j][y]);
		if (val != 1e9) ans += val, ++cnt;
	}
	cout << cnt << '\n' << ans;
}
```



---

## 作者：LYqwq (赞：0)

 [题目传送门](https://www.luogu.com.cn/problem/P3094) 

# 题目大意

有 $n$ 个农场，用 $1 \dots n$ 编号。有 $m$ 道单项航线连接这些农场，每条航线从农场 $u_i$ 连接到农场 $v_i$，花费为 $w_i$。

有 $q$ 个请求，请求从农场 $a_i$ 到 $b_i$，至少经过一个枢纽农场的最少花费。$1 \dots k$ 为枢纽农场。

输出可行请求的数量及完成的总费用。

# 思路

由于多组请求，很容易想到 Floyd。$1 \le n \le 200$，所以 Floyd 是可行的。

也可以用~~壮烈牺牲的~~ SPFA，跑 $n$ 次，每次以当前农场为起始点，最后求出全源最短路。

dijkstra 也是同理。

重点是寻找经过枢纽的路径（至少这题就这个要点脑子）。

每个枢纽都遍历一遍，找出从 $a \rightarrow i$ 加上 $i \rightarrow b$ 的最短路径，取经过所有枢纽的最小值就行了。

具体见代码。

~~代码巨长，小心阅读。~~

# 代码

## Floyd 版

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N=2e2+5,M=1e4+5,inf=0x3f3f3f3f;
int n,m,k,t,s=1,u,v,w,a,b,ans,cnt; // t是题目中的q，防止与队列重名
long long sum; // 会爆int
int dist[N][N]; // dist记录每两个点之间的距离

// 整个快读不过分吧？
inline int read(){
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
	if(flag) return X;
	return ~(X-1);
}

void floyd(){
	for(int k=1; k<=n; k++){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
			}
		}
	}
}

int main(){
	memset(dist,inf,sizeof(dist)); // 赋初值
	n=read(),m=read(),k=read(),t=read();
	for(int i=1; i<=n; i++){
		dist[i][i]=0;
	}
	while(m--){
		u=read(),v=read(),w=read();
		dist[u][v]=min(dist[u][v],w); // 两点间如果之前有连边，那就取小的那个
	}
	floyd(); // 直接求全源最短路
	while(t--){
		ans=inf;
		a=read(),b=read();
		for(int i=1; i<=k; i++){
			// 1~k中的农场都可以是枢纽，故取经过这个点的最小值
			ans=min(ans,dist[a][i]+dist[i][b]);
		}
		if(ans==inf) continue; // 若 a 不能到 b，那就走人
		cnt++; // 完成
		sum+=ans; // 费用
	}
	cout << cnt << endl << sum << endl;
	return 0;
}
```

## SPFA 版

```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N=2e2+5,M=1e4+5,inf=0x3f3f3f3f;
struct edge{
	int to,nxt,val; // 链式前向星存图
}e[M];
int n,m,k,t,s=1,u,v,w,a,b,ans,cnt; // t是题目中的q，防止与队列重名
long long sum; // 会爆int
int head[N],top;
int dist[N][N],vis[N]; // dist记录每两个点之间的距离，vis记录跑最短路时是否访问过
queue<int> q; // spfa用的队列

// 整个快读不过分吧？
inline int read(){
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
	if(flag) return X;
	return ~(X-1);
}

void add(int u,int v,int w){ // 加边
	top++;
	e[top].to=v;
	e[top].val=w;
	e[top].nxt=head[u];
	head[u]=top;
}

void spfa(int s){ // spfa板子，s表示当前的开始顶点，start
	for(int i=1; i<=n; i++){
		dist[s][i]=inf;
		vis[s]=0; // 由于多次使用vis，所以也要清零
	}
	dist[s][s]=0;
	vis[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u]; i; i=e[i].nxt){
			int v=e[i].to;
			if(dist[s][v]>dist[s][u]+e[i].val){
				dist[s][v]=dist[s][u]+e[i].val;
				if(!vis[v]){
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
}

int main(){
	n=read(),m=read(),k=read(),t=read();
	while(m--){
		u=read(),v=read(),w=read();
		add(u,v,w);
	}
	for(int i=1; i<=n; i++){ // 求出每两点之间的最短路径
		spfa(i);
	}
	while(t--){
		ans=inf;
		a=read(),b=read();
		for(int i=1; i<=k; i++){
			// 1~k中的农场都可以是枢纽，故取经过这个点的最小值
			ans=min(ans,dist[a][i]+dist[i][b]);
		}
		if(ans==inf) continue; // 若 a 不能到 b，那就走人
		cnt++; // 完成
		sum+=ans; // 费用
	}
	cout << cnt << endl << sum << endl;
	return 0;
}
```

## dijkstra 版

```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N=2e2+5,M=1e4+5,inf=0x3f3f3f3f;
struct edge{
	int to,nxt,val; // 链式前向星存图
}e[M];
int n,m,k,t,s=1,u,v,w,a,b,ans,cnt; // t是题目中的q，防止与队列重名
long long sum; // 会爆int
int head[N],top;
int dist[N][N],vis[N]; // dist记录每两个点之间的距离，vis记录跑最短路时是否访问过
priority_queue<pair<int,int>> q; // dijkstra用的堆

// 整个快读不过分吧？
inline int read(){
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0' && ch<='9') X=(X<<1)+(X<<3)+ch-'0',ch=getchar();
	if(flag) return X;
	return ~(X-1);
}

void add(int u,int v,int w){ // 加边
	top++;
	e[top].to=v;
	e[top].val=w;
	e[top].nxt=head[u];
	head[u]=top;
}

void dijkstra(int s){ // 同spfa
	for(int i=1; i<=n; i++){
		dist[s][i]=inf;
		vis[i]=0;
	}
	dist[s][s]=0;
	q.push(make_pair(0,s));
	while(!q.empty()){
		u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u]; i; i=e[i].nxt){
			v=e[i].to;
			if(dist[s][v]>dist[s][u]+e[i].val){
				dist[s][v]=dist[s][u]+e[i].val;
				q.push(make_pair(-dist[s][v],v));
			}
		}
	}
}

int main(){
	n=read(),m=read(),k=read(),t=read();
	while(m--){
		u=read(),v=read(),w=read();
		add(u,v,w);
	}
	for(int i=1; i<=n; i++){ // 求出每两点之间的最短路径
		dijkstra(i);
	}
	while(t--){
		ans=inf;
		a=read(),b=read();
		for(int i=1; i<=k; i++){
			// 1~k中的农场都可以是枢纽，故取经过这个点的最小值
			ans=min(ans,dist[a][i]+dist[i][b]);
		}
		if(ans==inf) continue; // 若 a 不能到 b，那就走人
		cnt++; // 完成
		sum+=ans; // 费用
	}
	cout << cnt << endl << sum << endl;
	return 0;
}
```

---

## 作者：Viktley (赞：0)

**大意：**

有 $n$ 个点， $m$ 条边，问必须经过 $1\rightarrow k$ 的关键点后，

求A~B的最短路

---

**思路：**

考虑 $1\rightarrow k$ 中的任意一个一点作为中转点，

那最后答案不就转换成了 $\begin{array}{l}min\left(dis_{st,i}+dis_{i,ed}\right)\\\vert\leq i\leq k\end{array}$

这和 $Floyed$ 的模板不是一样的吗？

```cpp
void Floyed()
{
	for(int k = 1; k <= n; k++)
	 for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= n; j++)
		f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}
```

故我们先用一遍 $Floyed$ **多源最短路**

求出任意两点的距离，接着在问题询问的时候，

枚举 $1\rightarrow k$ 每一个点作为中转点，取最小值不就行了？

---

**Code：**

```cpp
#include <cstdio>
#include <iostream>
#include <cstring> 
#define MAXN 0x3f3f3f3f
#define ll long long
using namespace std;
int n, m, k, q, x, y, z, f[205][205], temp;
ll ans1, ans2;
void Floyed()
{
	for(int k = 1; k <= n; k++)
	 for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= n; j++)
		f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}
int main(){
	scanf("%d%d%d%d", &n, &m, &k, &q);
	memset(f, 0x3f, sizeof(f));
	for(int i = 1; i <= n; i++) f[i][i] = 0;
	for(int i = 1; i <= m; i++) scanf("%d%d%d",&x, &y, &z), f[x][y] = z;
	Floyed();
	for(int i = 1; i <= q; i++)
	{
		scanf("%d%d", &x, &y);
		temp = MAXN;
		for(int i = 1; i <= k; i++)
			temp = min(temp, f[x][i] + f[i][y]);
		if(temp != MAXN) ans1++, ans2 += temp;
	}
	printf("%lld\n%lld", ans1, ans2);
	return 0;
}

```


---

## 作者：Jsxts_ (赞：0)

# 题解P3094



## 题意

给定一个有向图，然后给q个询问，问a是否能到达b，并求出所有询问的花费总和以及询问成功的次数。

## 题解

一道求最短路问题。

看一下数据范围，$N \le 200$,可以用 $O(n^3)$ 的 Floyd 过了。

$Floyd$ 做法：

先用邻接矩阵存图，开 $200*200$ 的二维数组就够了。跑完最短路之后，对于每一次询问，因为必须经过$1 \sim k$ 的一个点，所以答案就是
$$ \sum _{i=1} ^ k w[a][i] + w[i][b]$$

的最小值，（意思就是先从a到i，再从i到b，这样就保证经过 $i$ 点了）

附上[Floyd详解](https://blog.csdn.net/zjbzlc/article/details/100541988?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522160092555019724835812473%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=160092555019724835812473&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_click~default-5-100541988.first_rank_ecpm_v3_pc_rank_v2&utm_term=Floyd&spm=1018.2118.3001.4187)

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[210][210];//邻接矩阵存图（200*200就够了） 
int main() {
	int n,m,p,q;
	scanf("%d%d%d%d",&n,&m,&p,&q);
	memset(a,0x3f,sizeof a);//初始化为负无穷 
	for (int i = 1;i <= n;i ++ ) {
		a[i][i] = 0;//i到i距离为零 
	}
	for (int i = 1;i <= m;i ++ ) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		a[u][v] = w;//存图，单向边
	}
	for (int k = 1;k <= n;k ++ ) {
		for (int i = 1;i <= n;i ++ ) {
			for (int j = 1;j <= n;j ++ ) {
				a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
				//Floyd板子跑一遍就可以了 
			}
		}
	}
	long long ans = 0;//最小花费总和 
	int cnt = 0;//记录能到达的次数 
	while (q -- ) {//查询 
		int x,y;
		long long minn = 2e9;
		scanf("%d%d",&x,&y);
		for (int i = 1;i <= p;i ++ ) {
			if (a[x][i] + a[i][y] > 0) {
				//从x到i，再从i到y 
				minn = min(minn,a[x][i] + a[i][y]);
				//取最小值 
			}
		}
		if (minn != 2e9) {//有答案 
			ans += minn;//累计 
			cnt ++;
		}
	}
	printf("%d\n%lld",cnt,ans);//输出 
	return 0;
}
```


难度：黄左右

时间：140ms

###### [双倍经验](https://www.luogu.com.cn/problem/SP18966)

---

## 作者：EDqwq (赞：0)


### 思路


由于**数据范围为200**，并且**多次询问**,所以Floyd是对这道题最合适的算法。


我们一开始跑一遍Floyd，对每一个询问，给答案变量设一个很大的初始值，循环判断要经过的中转站，取最小值，如果答案还是为**初始值**，说明**无解**，否则计数器加一，总价格加当前最小答案。

***

思路有了，下面是几个注意事项：

1. Floyd数组要附初始值

1. **不开long long见祖宗**（0pts）


***

都讲完了，下面是代码，请配合注释食用:

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int read(){//快读
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n,m,k,q;
int maps[300][300];//我这里开300，实际上201就够了
int anss;
int ansss;

signed main(){
	cin>>n>>m>>k>>q;
	for(int i = 1;i <= n;i ++){//初始值
		for(int j = 1;j <= n;j ++){
			if(i == j)maps[i][j] = 0;
			else maps[i][j] = 2147483647;
		}
	}
	for(int i = 1;i <= m;i ++){
		int x,y,w;
		x = read(),y = read(),w = read();
		maps[x][y] = w;//有向图（单向航班）
	}
	for(int k = 1;k <= n;k ++){//Floyd模板
		for(int i = 1;i <= n;i ++){
			for(int j = 1;j <= n;j ++){
				maps[i][j] = min(maps[i][j],maps[i][k] + maps[k][j]);
			}
		}
	}
	for(int i = 1;i <= q;i ++){
		int x,y;
		int ans = 2147483647;
		x = read(),y = read();
		for(int i = 1;i <= k;i ++){//选择中转站
			if(maps[x][i] + maps[i][y] != 0){//如果不为0，更新答案
				ans = min(ans,maps[x][i] + maps[i][y]);
			}
		}
		if(ans != 2147483647){//有解更新答案
			ansss += ans;
			anss ++;
		}
	}
	cout<<anss<<endl<<ansss;
	return 0;
}
```



---

## 作者：WanderingTrader (赞：0)

这题一看就知道，最短路问题。不过是把边权换成了价格。  
### 题目分析
我们发现：$n\le200$，那太好了！！连$O(n^3)$的Floyd都能过了，更别提$O(n^2\log n)$的Dij和SPFA了。  
鉴于个人喜好，这里采用Dij和Floyd两种方法。  
### Floyd解法
Floyd模板想必大家都很熟悉了，也就是：
```cpp
#define N 205
#define ll long long
#define INF 1e12 
ll d[N][N];
void Floyd(int n)
{
	for(int k = 1;k <= n;++k)
		for(int i = 1;i <= n;++i)
			for(int j = 1;j <= n;++j)
				d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
}
```
唯一要注意的就是k要放在最外层循环，否则会WA。  

这题与模板有个不同，就是它规定了必须要经过一个枢纽。怎么办呢？很简单。Floyd里不是有这么一句吗：
```cpp
d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
```
它的作用就是强制在i到j的路上必须经过k。  
那我们也仿写一个。  
从a到b，必须经过s($1\le s\le k$)，则有：
```cpp
for(int i = 1;i <= k;++i)
	num = min(num,d[a][i] + d[i][b]);
```
所以询问部分就是：
```cpp
while(q--)
{
	int a,b;
	scanf("%d%d",&a,&b);
	ll num = INF;
	for(int i = 1;i <= k;++i)
		num = min(num,d[a][i] + d[i][b]);
	if(num == INF) continue;
	++cnt;
	ans += num;
}
```
巧妙的将Floyd算法中的公式运用到了其它类似问题上。  
全部代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define N 205
#define ll long long
#define INF 1e12 
ll d[N][N];
void Floyd(int n)
{
	for(int k = 1;k <= n;++k)
		for(int i = 1;i <= n;++i)
			for(int j = 1;j <= n;++j)
				d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
}
int main()
{
	int n,m,k,q;
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i = 1;i <= n;++i)
		for(int j = 1;j <= n;++j)
			if(i!=j) d[i][j] = INF;
	for(int i = 1;i <= m;++i)
	{
		int u,v;
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		d[u][v] = min(d[u][v],w);
	}
	Floyd(n);
	int cnt = 0;
	ll ans = 0;
	while(q--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		ll num = INF;
		for(int i = 1;i <= k;++i)
			num = min(num,d[a][i] + d[i][b]);
		if(num == INF) continue;
		++cnt;
		ans += num;
	}
	printf("%d\n%lld\n",cnt,ans);
	return 0;
}
```
输入输出部分别忘了判断重边（好习惯）。  
### Dijkstra解法
$O(n^3)$的Dij也能过，但保险起见还是写了一个堆优化。  
```cpp
void dijkstra(int s)
{
	fill(d[s]+1,d[s] + n+1,INF);
	fill(vis[s]+1,vis[s]+n+1,false);
	d[s][s] = 0;
	priority_queue <node> Q;
	Q.push((node){s,0});
	while(!Q.empty())
	{
		node t = Q.top();
		Q.pop();
		if(vis[s][t.x]) continue;
		vis[s][t.x] = true;
		int size = e[t.x].size();
		for(int i = 0;i < size;++i)
		{
			if(d[s][e[t.x][i]] > d[s][t.x] + w[t.x][i])
			{
				d[s][e[t.x][i]] = d[s][t.x] + w[t.x][i];
				Q.push((node){e[t.x][i],d[s][e[t.x][i]]});
			}
		}
	}
}
```
借助堆优化，将原本“查找目前与目标结点距离最近的结点”的复杂度降至$O(\log n)$，还是很高效的。  

输入部分可以封装一下：
```cpp
void read()
{
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i = 1;i <= m;++i)
	{
		int x,y;
		ll z;
		scanf("%d%d%lld",&x,&y,&z);
		e[x].push_back(y);
		w[x].push_back(z);
	}
}
```
剩下的和Floyd基本一样，不再赘述。  
全部代码：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define ll long long
#define N 205
#define INF 1e12
struct node
{
	int x;
	ll d;
	bool operator < (const node& a) const
	{
		return d > a.d;
	}
};
int n,m,k,q;
vector <int> e[N];
vector <ll> w[N];
ll d[N][N];
bool vis[N][N];
void read()
{
	scanf("%d%d%d%d",&n,&m,&k,&q);
	for(int i = 1;i <= m;++i)
	{
		int x,y;
		ll z;
		scanf("%d%d%lld",&x,&y,&z);
		e[x].push_back(y);
		w[x].push_back(z);
	}
}
void dijkstra(int s)
{
	fill(d[s]+1,d[s] + n+1,INF);
	fill(vis[s]+1,vis[s]+n+1,false);
	d[s][s] = 0;
	priority_queue <node> Q;
	Q.push((node){s,0});
	while(!Q.empty())
	{
		node t = Q.top();
		Q.pop();
		if(vis[s][t.x]) continue;
		vis[s][t.x] = true;
		int size = e[t.x].size();
		for(int i = 0;i < size;++i)
		{
			if(d[s][e[t.x][i]] > d[s][t.x] + w[t.x][i])
			{
				d[s][e[t.x][i]] = d[s][t.x] + w[t.x][i];
				Q.push((node){e[t.x][i],d[s][e[t.x][i]]});
			}
		}
	}
}
int main()
{
	read();
	for(int i = 1;i <= n;++i)
		dijkstra(i);
	int cnt = 0;
	ll ans = 0;
	while(q--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		ll num = INF;
		for(int i = 1;i <= k;++i)
			num = min(num,d[a][i] + d[i][b]);
		if(num == INF) continue;
		++cnt;
		ans += num;
	}
	printf("%d\n%lld\n",cnt,ans);
	return 0;
}
/*
3 3 1 3 
3 1 10 
1 3 10 
1 2 7 
*/
```
对比评测结果可以发现，Dij和Floyd是各有千秋的。Dij的效率很高，但使用邻接表的必然后果就是常数和空间开销大，而且码量也比Floyd大。而Floyd的效率虽然不高，但它代码简洁，省空间，在数据允许的情况下不妨试一试。  
[Dij结果](https://www.luogu.com.cn/record/35088329)  
[Floyd结果](https://www.luogu.com.cn/record/35088480)  
$$
\mathrm{The\ End.}
$$

---

## 作者：muse_umbra (赞：0)

由题意看  
必须经过中转站(枢纽农场)  
那就用中转站跑最短路  
先在原图跑求的是中转站到其他点的最短路  
然后再反向建边跑最短路  
求的是其他点到中转站的最短路  
为什么要这样  
因为这是有向图  
然后在每次询问中，枚举每一个中转站，求最小的最短路  
虽然代码很长  
但很好写  
这道题我是今天考试考了  
只是略改了一下代码
有些地方奇怪的话不要在意~~这使你充满了决心~~
```cpp
#include<bits/stdc++.h>
#define ll long long
#define M 20005
#define re register
using namespace std;
inline int read()
{
	int w=0,q=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')q=-1;c=getchar();}
	while(c>='0'&&c<='9'){w=(w<<1)+(w<<3)+c-'0';c=getchar();}
	return w*q;
}
int cnt,h1[M],sum,h2[M],vis[M];
struct node{int nxt,to;ll val;}a1[M],a2[M];
void add1(int x,int y,ll val){a1[++cnt].nxt=h1[x];a1[cnt].to=y;a1[cnt].val=val;h1[x]=cnt;}
void add2(int x,int y,ll val){a2[++sum].nxt=h2[x];a2[sum].to=y;a2[sum].val=val;h2[x]=sum;}
ll dis[201][M][2];
ll dn[50005];
void spfa1(int x,int y)//跑原图
{
	memset(vis,0,sizeof(vis));
	deque<int> q;
	q.push_back(x);
	vis[x]=1;
	dis[y][x][0]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop_front();
		vis[u]=0;
		for(re int i=h1[u];i;i=a1[i].nxt)
		{
			int v=a1[i].to;
			if(dis[y][v][0]>dis[y][u][0]+a1[i].val)
			{
				dis[y][v][0]=dis[y][u][0]+a1[i].val;
				if(!vis[v])
				{
					if(q.size()&&dis[y][v][0]>dis[y][q.front()][0])q.push_back(v);
					else q.push_front(v);
					vis[v]=1;
				}
			}
		}
	}
}
void spfa2(int x,int y)//跑反向后的图
{
	memset(vis,0,sizeof(vis));
	deque<int> q;
	q.push_back(x);
	vis[x]=1;
	dis[y][x][1]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop_front();
		vis[u]=0;
		for(re int i=h2[u];i;i=a2[i].nxt)
		{
			int v=a2[i].to;
			if(dis[y][v][1]>dis[y][u][1]+a2[i].val)
			{
				dis[y][v][1]=dis[y][u][1]+a2[i].val;
				if(!vis[v])
				{
					if(q.size()&&dis[y][v][1]>dis[y][q.front()][1])q.push_back(v);
					else q.push_front(v);
					vis[v]=1;
				}
			}
		}
	}
}
int n,k,q,m;
int main()
{
//	freopen("vacation.in","r",stdin);freopen("vacation.out","w",stdout);
	memset(dis,0x3f,sizeof(dis));
	int zs=0;
	ll jsq=0;
	n=read(),m=read(),k=read(),q=read();
	for(re int i=1;i<=m;i++){int x=read(),y=read(),z=read();add1(x,y,z);add2(y,x,z);}
	for(re int i=1;i<=k;i++){spfa1(i,i),spfa2(i,i);}
	for(re int i=1;i<=q;i++)
	{
		ll ans=0x3f3f3f3f,x=read(),y=read();
		for(re int j=1;j<=k;j++){ans=min(dis[j][x][1]+dis[j][y][0],ans);}
		if(ans<0x3f3f3f3f){zs++;jsq+=ans;}
	}
	printf("%d\n",zs);
	printf("%lld",jsq);
	return 0;
}
```
考试时n最大有20000，但这个只有200太小了  
所以下面的都能过  
建议加强数据

---

## 作者：绚濑绘里 (赞：0)

因为n<=200，所以可以floyd预处理出每两点之间的最短路。询问从u到v时，枚举编号1~k的点（枢纽）作为中转，求dis(u,i)+dis(i,v)的最小值。


```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
const int mxn=300;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int mp[mxn][mxn];
int n,m,k,Q;

int main(){
    memset(mp,0x3f,sizeof mp);
    n=read();m=read();k=read();Q=read();
    int i,j;
    int u,v,d;
    for(i=1;i<=m;i++){
        u=read();v=read();d=read();
        mp[u][v]=min(mp[u][v],d);
    }
    for(int e=1;e<=n;e++)
     for(i=1;i<=n;i++)
      for(j=1;j<=n;j++){
          if(i==j)mp[i][j]=0;
          else mp[i][j]=min(mp[i][j],mp[i][e]+mp[e][j]);
      }
    long long ans=0;int cnt=0;
    while(Q--){
        u=read();v=read();
        d=0x3f3f3f3f;
        for(i=1;i<=k;i++){
            d=min(d,mp[u][i]+mp[i][v]);
        }
        if(d<0x3f3f3f3f){
            cnt++;
            ans+=d;
        }
    }
    printf("%d\n%lld\n",cnt,ans);
    return 0;
}
```

---

## 作者：Expecto (赞：0)

啊我今天运势不好啊。。。。一些细节没注意到

直接Floyd，注意sum要long long ，询问的时候经过那些枢纽求最小值

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[202][202];
int main(){
    memset(f,127/3,sizeof(f));
    int n,m,K,q;
    scanf("%d%d%d%d",&n,&m,&K,&q);
    for(int i=1;i<=n;i++) f[i][i]=0;
    while (m--){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        f[x][y]=z;
    }
    for (int k=1;k<=n;k++)
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
    int ans=0,inf=f[0][0];
    long long sum=0;
    while (q--){
        int x,y,cost=inf;
        scanf("%d%d",&x,&y);
        for (int i=1;i<=K;i++)
            cost=min(cost,f[x][i]+f[i][y]);
        if (cost==inf) continue;
        ans++;
        sum+=cost;
    }
    cout<<ans<<'\n'<<sum;
    return 0;
}

```

---

