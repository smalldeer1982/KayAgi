# [USACO16DEC] Moocast G

## 题目描述

Farmer John 的 $N$ 头奶牛（$1 \leq N \leq 1000$）希望组织一个紧急的“哞播”系统，用于在它们之间广播重要消息。

为了避免在长距离上互相哞叫，奶牛们决定为自己配备对讲机，每头奶牛一个。这些对讲机每个都有一个有限的传输半径，但奶牛们可以通过多次跳跃的路径中继消息，因此并非每头奶牛都需要能够直接与其他每头奶牛通信。

奶牛们需要决定在对讲机上花费多少钱。如果它们花费 $X$，每头奶牛将获得一个能够传输到 $\sqrt{X}$ 距离的对讲机。也就是说，两头奶牛之间的平方距离必须不超过 $X$，它们才能通信。

请帮助奶牛们确定 $X$ 的最小整数值，使得从任何一头奶牛发出的广播最终能够到达其他所有奶牛。

## 样例 #1

### 输入

```
4
1 3
5 4
7 2
6 1```

### 输出

```
17
```

# 题解

## 作者：奔波儿霸 (赞：8)

#### 题目大意

给定$N$个点的横纵坐标。两个点之间能够连边的条件是两个点的距离小于$\sqrt{\text{花费}}$，算出能够使得所有的点都连通的最小花费。

#### 解题思路

根本用不着二分答案嘛。直接$N^2$建边，跑一遍$Kruskal$。记录在最小生成树中的最长的一条边。显然只要使得这条边能够建立，那么这棵最小生成树中的所有的边都可以建立。答案就是最长的边的距离的平方，注意要用$double$存边权。

#### 附上代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 1e3+3;
int n, x[maxn], y[maxn], cnt, tot, f[maxn];
double Ans;
struct Edge {
	int u, v;
	double w;
}ed[maxn * maxn];
inline bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}
inline int find(int x) {
	if(x == f[x]) return x;
	else return f[x] = find(f[x]);
}
inline void Kruskal() {
	for(int i=1; i<=n; i++) f[i] = i;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if(i != j) {
				++cnt;
				ed[cnt].u = i, ed[cnt].v = j, ed[cnt].w = sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
			}
		}
	}
	sort(ed+1, ed+1+cnt, cmp);
	for(int i=1; i<=cnt; i++) {
		int xx = find(ed[i].u), yy = find(ed[i].v);
		if(xx != yy) {
			f[xx] = find(yy);
			tot ++;
			Ans = ed[i].w;
		}
		if(tot == n-1) {
			break;
		}
	}
}

int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d%d", &x[i], &y[i]);
	}
	Kruskal();
	printf("%.0lf", Ans * Ans);
}
```

---

## 作者：__Watcher (赞：2)

这一题的二分答案方法说的不清不楚，这里补一篇二分答案的题解。

---

二分答案，就是二分这一题中的 $X$。对于每一个枚举出来的值 $k$，用并查集维护联通关系。枚举任意两个点，若它们间距离的平方小于 $k$，则合并两个点所在的并查集。若搜索后所有点在同一个并查集内，在当前值 $k$ 可用。二分区域可以设为距离最远的点的平方，懒的话设成 $10^9$ 就可以了。总复杂度 $O(n^2 \log 10^9)$（并查集的复杂度就当常数吧），可以通过此题。

---

更好的解法当然是最小生成树，这次参见其它题解吧。

---
提供代码，仅供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int read() {
	int x=0, f=1; char ch=' ';
	while(!isdigit(ch)) {ch=getchar(); if(ch=='-') f=-1;}
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48), ch=getchar();
	return x*f;
}
int n, x[1005], y[1005], f[1005];
int find(int x) {
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
bool check(int k) {
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=n;i++) {
		for(int j=i+1;j<=n;j++) {
			if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])>k) continue;
			int x=find(i), y=find(j);
			if(x!=y) f[x]=y;
		}
	}
	for(int i=2;i<=n;i++) {
		if(find(i)!=find(i-1)) return false;
	}
	return true;
}
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) x[i]=read(), y[i]=read();
	int l=0, r=1e9, mid;
	while(l<r) {
		mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l;
}

```


---

## 作者：elijahqi (赞：2)

这大概是比较裸的最小生成树，写之前建议仔细读题 题目意思是求可以使得所有奶牛都联通的最大值最小

那么kruskal求得最后一条边即可

```cpp
#include<cstdio>
#include<algorithm>
#define N 1100
using namespace std;
inline int qrt(int x){
    return x*x;
}
int num,n,x[N],y[N],fa[N];
inline int calc(int i,int j){
    int ans=qrt(x[i]-x[j])+qrt(y[i]-y[j]);
    return ans;
}
inline int read(){
    int x=0;char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') {
        x=x*10+ch-'0';ch=getchar();
    }
    return x;
}
struct node{
    int x,y,w;
}data[N*N];
inline void insert1(int x,int y,int w){
    data[++num].x=x;data[num].y=y;data[num].w=w;
}
inline int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
inline bool cmp(node a,node b){
    return a.w<b.w;
}
int main(){
    freopen("2840.in","r",stdin);
    freopen("2840.out","w",stdout);
    n=read();num=0;
    for (int i=1;i<=n;++i) x[i]=read(),y[i]=read();
    for (int i=1;i<=n;++i) fa[i]=i;
    for (int i=1;i<=n;++i){
        for (int j=i+1;j<=n;++j){
            insert1(i,j,calc(i,j));
        }
    }
    int tot=0;
    sort(data+1,data+1+num,cmp);
    //for (int i=1;i<=num;++i )printf("%d %d %d\n",data[i].x,data[i].y,data[i].w);
    int i;
    for (i=1;i<=num;++i){
        int p=find(data[i].x),q=find(data[i].y);
        if (p!=q) fa[p]=q,++tot;
    //    printf("%d %d %d\n",data[i].x,data[i].y,data[i].w);
        if (tot==n-1) break;
    }
    printf("%d",data[i].w);
    return 0;
}
```

---

## 作者：blackjack (赞：2)

明显的二分答案，之前的题解有点繁了
```cpp
#include<iostream>
#include<cmath>
#include<vector>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

int x;
int G[1001][1001];
int A[1001][3];
typedef double dd;
bool R[1001][1001];
int n;
int T[1001];
bool C[1001];
int ans=0;

inline  void cal(int i,int j){
	dd xa=(dd)A[i][1],xb=(dd)A[j][1];
	dd ya=(dd)A[i][2],yb=(dd)A[j][2];
	dd ans=0;
	ans=(xa-xb)*(xa-xb)+(ya-yb)*(ya-yb);
	G[i][j]=(int)(ceil(ans));
	G[j][i]=G[i][j];
}
void dfs(int x,int k,int be){
	for (int i=1;i<=n;i++){
		if (G[i][k]<=x and C[i]==0){
			C[i]=1;
			T[be]++;
			dfs(x,i,be);
		}
	}
}


int main(){
//	freopen("moocast.in","r",stdin);
//	freopen("moocast.out","w",stdout);
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>A[i][1]>>A[i][2];
	for (int i=1;i<n;i++){
		for (int j=i+1;j<=n;j++){
			cal(i,j);
		}
	}
	int f=1,p=111111111;
	while(f<p-1){
		memset(T,0,sizeof(T));
		memset(C,0,sizeof(C));
		x=(f+p)/2;
		C[1]=1;
		dfs(x,1,1);
		if (T[1]==n-1)
			p=x;
		else
			f=x;
	}
	x=ceil((f+p)/2);
	cout<<x+1<<endl;
	return 0;
}

```


---

## 作者：Chavapa (赞：1)

$USACO$ ~~金组大水题~~ 最小生成树入门练手题

既然是最小生成树，
## 何必要二分答案？
我们完全可以不用$Kruskal$，
## 何必要$O(n^2)$建边？
显然，答案是最小生成树中最长边的平方，直接勾股定理就行——
## 何必要处理小数精度问题？

对于边权需要自行计算的完全图（如本题只给出坐标的情况），在时间复杂度允许的情况下，我们一般采用$Prim$算法。

$Prim$的思想类似于最短路中的$dijkstra$。

初始时，将任意结点（通常选$1$号结点）加入最小生成树，然后我们维护一个$min[i]$数组用于记录结点$i$到已经确定的最小生成树的最短距离。

每次循环中，我们根据贪心思想，找到一个离最小生成树最近的且未被加入到树中的结点，添加到树中，并用当前的结点去松弛与其相连的结点。重复该操作直到所有元素被加入到最小生成树中。

时间复杂度$O(n^2)$，在稠密图中有不俗的表现。

### $Prim$正确性证明：

对于任意一个顶点$v$，连接到该顶点的所有边中的一条最短边$(v, vj)$必然属于最小生成树（即任意一个属于最小生成树的连通子图，从外部连接到该连通子图的所有边中的一条最短边必然属于最小生成树）

传送门：[P3366 【模版】最小生成树](https://www.luogu.org/problem/P3366)

然后我们就可以用$Prim$愉快地$AC$这道金组~~难题~~辣

## Code
```c
program cast;
const INF=99999999999999;
var ans,m,u:int64;
    min,x,y:array[0..1010] of int64;
    vis:array[0..1010] of boolean;
    i,j,n:longint;
begin
  readln(n);
  for i:=1 to n do readln(x[i],y[i]);
  for i:=1 to n do min[i]:=INF;
  min[1]:=0;
  for i:=1 to n do
  begin
    m:=INF;
    for j:=1 to n do
      if (not vis[j])and(min[j]<m) then
      begin
        m:=min[j]; u:=j;
      end;
    vis[u]:=true;
    for j:=1 to n do
      if (not vis[j])and(sqr(x[j]-x[u])+sqr(y[j]-y[u])<min[j]) then
        min[j]:=sqr(x[j]-x[u])+sqr(y[j]-y[u]);
  end;
  for i:=1 to n do
    if min[i]>ans then ans:=min[i];
  writeln(ans);
end.

```

---

## 作者：szbszb (赞：1)

这是一道标准的最小生成树的题

为什么呢？大家应该都学过勾股定理吧？在平面直角坐标系中，两点A(x1,y1),B(x2,y2)的距离|AB|等于sqrt((x1-x2)^2+(y1-y2)^2），而我们可以发现，我们最后要求的是最大的|AB|^2,也就是(x1-x2)^2+(y1-y2)^2（当然在C++里得写成(x1-x2) * (x1-x2)+(y1-y2) * (y1-y2))，所以，我们只要求出边权为两点距离平方的最小生成树中最长边的长就可以了。

首先，我们可以通过一次双重循环求出每条边的边权，然后再跑一边最小生成树算法。

被熟知的求最小生成树的算法有prime、kruskal两种，而这次我们的图是完全图（即图的每两点之间都有连边），而prime更适合跑稠密图，因此我们选用prime算法。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,i,j,x[1001],y[1001],p[1001][1001],d[1001],u,max1;
bool b[1001];
priority_queue<pair<long long,long long> >q;//堆优化
int main()
{
	scanf("%lld",&n);
	for (i=1;i<=n;i++)
		scanf("%lld%lld",&x[i],&y[i]);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
		p[i][j]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);//求出两两点之间的距离
	for (i=1;i<=n;i++) d[i]=1e11;
	d[1]=0;
	max1=0;
	q.push(make_pair(0,1));
	while (q.size())
	{
		u=q.top().second;
		q.pop();
		if (b[u]) continue;
		max1=max(max1,d[u]);//求出最大边权
		b[u]=true;
		for (i=1;i<=n;i++)
			if (d[i]>p[u][i])
			{
				d[i]=p[u][i];
				q.push(make_pair(-d[i],i));//prime
			}
	}
	printf("%lld",max1);
	return 0;
}
```
其实这题数据较小，感觉kruskal也能跑过，但既然已经A了也就懒得打了。

---

## 作者：haunter (赞：1)

~~很显然~~这是一道最小生成树水题，只要求最小生成树中最长边的平方就行了，但是在某些数据上实数平方转整数时因为默认去小数部分所以会炸精度，要加上一个小常数压压惊。。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;bool v[1500];
double x[1500],y[1500],w[1500][1500],d[1500],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		for(int j=1;j<i;j++)w[i][j]=w[j][i]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
	}
	for(int i=1;i<=n;i++)d[i]=w[1][i];
	memset(v,false,sizeof(v));
	v[1]=true;ans=0;
	for(int i=1;i<=n-1;i++){
		t=1;
		while(v[t])t++;
		for(int j=t;j<=n;j++)if(!v[j]&&d[j]<d[t])t=j;
		if(d[t]>ans)ans=d[t];//存最长边
		d[t]=0;
		v[t]=true;
		for(int j=1;j<=n;j++)if(w[t][j]<d[j])d[j]=w[t][j];
		
	}
	t=ans*ans+0.000001;//防止炸精度
	cout<<t;
}
```

---

## 作者：sleepyNick (赞：1)

**P党的福利**

最浅显的方法：这道题的关键就是建图O(n^2)+Kruskal

~~二分答案~~太复杂啦

我的建图方法：对于读入的点，两两之间用距离公式算出长度，然后对于建立的图，跑一遍Kruskal。**在跑的过程中，记下最长的边长即为答案。**

举个栗子!
![](https://cdn.luogu.com.cn/upload/pic/23276.png)
对于输入数据：

4

1 2

1 3

2 2

2 0

我们建立一个这样的图，共6条边

可以推得边数：$\frac{n(n-1)}{2}$

然后就可以愉快地Kruskal了

贴代码：
```pascal
var i,ans,tot,n,j:longint;
x,y,father:array[0..10000] of longint;
a,b,v:array[0..600000] of longint;

procedure swap(var x,y:longint);
var temp:longint;
begin
temp:=x;x:=y;y:=temp;
end;

procedure sort(l,r:longint);   //排序，kruskal基本操作
var i,j,t,mid:longint;
begin
i:=l;j:=r;
mid:=v[(l+r) div 2];
repeat
    while v[i]<mid do
        inc(i);
    while v[j]>mid do
        dec(j);
    if i<=j
        then begin
                 swap(a[i],a[j]);
                 swap(b[i],b[j]);
                 swap(v[i],v[j]);
                 inc(i);dec(j);
             end;
until i>j;
if l<j
    then sort(l,j);
if i<r
    then sort(i,r);
end;

function getfather(x:longint):longint;   //并查集
begin
if father[x]=x
    then exit(father[x]);
father[x]:=getfather(father[x]);
exit(father[x]);
end;

procedure merge(x,y:longint);
var xx,yy:longint;
begin
xx:=getfather(x);
yy:=getfather(y);
father[xx]:=yy;
end;

function query(x,y:longint):boolean;
begin
exit(getfather(x)=getfather(y));
end;

begin
readln(n);
for i:=1 to n do
    readln(x[i],y[i]);
for i:=1 to n-1 do    //O(n^2)的建图
    for j:=i+1 to n do
        begin
            inc(tot);
            a[tot]:=i;b[tot]:=j;
            v[tot]:=sqr(x[i]-x[j])+sqr(y[i]-y[j]); //距离公式建边
        end;
sort(1,tot);
for i:=1 to n do
    father[i]:=i;
for i:=1 to tot do
    if query(a[i],b[i])=false
        then begin
                 if v[i]>ans   
                     then ans:=v[i];   //保存最长的边
                 merge(a[i],b[i]);
             end;
writeln(ans);
end.
```

---

## 作者：fangxk2003 (赞：1)

第一次写题解，有不对的地方希望指出。QwQ

题意：告诉你N个点的坐标，让你求能使这N个点连通的N-1条线段中最长的一条线段的最小值的平方，也就是他们要花费的钱数。

首先， 用勾股定理，只要求sqr(x1-x2)+sqr(y1-y2)就行了。

这道题可以用最小生成树，也可以用二分，下面就只介绍最小生成树，时间复杂度为O（N^2）。

首先，初始化：在最小生成树中加入第一个点，并标记。然后算出其他每个点到第一个点的距离。每次循环找一个离最小生成树最近的点，并标记，在最小生成树中加入这个点，并更新那些还没有加入最小生成树的点离最小生成树的最短距离。循环N-1次，把每个点都加入，最后只要找那条最长的边就可以了。

【参考程序】

```cpp
var n,i,j,min,max,ll,minl:longint;
    x,y,l:array[1..1000]of longint;
    b:array[1..1000]of boolean;
begin
 readln(n);
 for i:=1 to n do
  readln(x[i],y[i]);
 for i:=2 to n do//初始化
  l[i]:=sqr(x[1]-x[i])+sqr(y[1]-y[i]);
 b[1]:=true;
 for i:=1 to n-1 do//找边
 begin
  min:=maxlongint;
  for j:=1 to n do
   if (not(b[j]))and(l[j]<min) then//找最近的未标记的点
   begin
    min:=l[j];
    minl:=j;
   end;
  if min>max then max:=min;//更新最长边
  b[minl]:=true;//标记
  for j:=1 to n do//更新没有加入最小生成树的点到最小生成树的距离
   if not(b[j]) then
   begin
    ll:=sqr(x[minl]-x[j])+sqr(y[minl]-y[j]);
    if ll<l[j] then l[j]:=ll;
   end;
 end;
 writeln(max);
 close(input);close(output);
end.
```

---

## 作者：OceanLiu (赞：0)

这道题和我做过的一道题很像（P2504 [HAOI2006]聪明的猴子）反正我第一时间想到的就是先无脑Kruscal一遍……

打完最小生成树后，我陷入了沉思。突然，我灵机一动，想到了一个绝妙的方法：只要以最小生成树的最大的那一条边为准，不就vans了吗？！

有两点比较坑的是，dis要用double类型；数组一定要开大一点！（我因为这个RE了）

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][3],k,fa[2000005];
int find(int x)
{
	if (x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
bool quary(int x,int y)
{
	return find(x)==find(y);
}
void merge(int x,int y)
{
	fa[find(x)]=find(y);
}
struct node
{
	int fr,to;
	double dis;
}q[2000005];
bool cmp(node x,node y)
{
	return x.dis<y.dis;
}
int main()
{
	int n;
	cin>>n;
	for (int i=1;i<=2000004;i++) fa[i]=i;
	for (int i=1;i<=n;i++)
		cin>>a[i][1]>>a[i][2];
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			if (i!=j)
			{
				k++;
				q[k].fr=i;q[k].to=j;q[k].dis=sqrt((a[i][1]-a[j][1])*(a[i][1]-a[j][1])+(a[i][2]-a[j][2])*(a[i][2]-a[j][2]));
			}
	sort(q+1,q+k+1,cmp);
	int cnt=0; double ans=0;
	for (int i=1;i<=k;i++)
	{
		if (quary(q[i].fr,q[i].to)) continue;
		merge(q[i].fr,q[i].to);
		ans=q[i].dis;
		if (++cnt==n-1) break;
	}
	printf("%.0lf", ans*ans);
	return 0;
}
```
顺便提一句，很大一部分生成树，并查集的题都是相通的。学会多总结，多思考，尝试少看题解，一些比较难的问题也就迎刃而解了。

本菜鸟还是太弱了，想不到什么好的方法，欢迎各路大神爆踩我~~

---

## 作者：hht2005 (赞：0)

**简化题面**

给你n个点，可以在任意两点间连边，代价为两点间的距离。在保证图联通的情况下，最小化最大边权。输出最小的最大边权的平方。

**思路**

有题解说可以用二分答案，可我不会怎么办？其实并不用二分答案，最小生成树就行，输出最小生成树的最大边权。

**证明**（自己瞎写的，不一定完善  ~~应该是一定不~~）

首先，树保证了连通，对于任何一幅图，去掉一些边后变成树，它依然满足条件，而且答案一定不会更大。

第二，最小生成树是不停地找最小的边，那么它最大的边权一定会被最小化。如果最大边权可以更小，那它就不是最小生成树。反之，如果它是最小生成树，那么最大的边权就不会更小。所以，最小生成树的最大边权就是答案。

**实现**

最小生成树一般有两种找法，Kruskal算法和Prim算法。由于任意两点间都可以连边，所以选择Prim算法更好。

在算两点之间距离时有一个小技巧，不要存他们的距离，而是存他们的距离的平方，这样不会影响答案，却可以避免玄学的精度判断，写起来也简单一些。

**code：**

```cpp
#include<cstdio>
#include<cstring>
//map存两点间的距离，x、y为读入的坐标，dis为每个点到原生成树集合距离的平方，f为每个点是否在原生成树集合内
int map[1010][1010],x[1010],y[1010],dis[1010],f[1010];
int main()
{
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)//读入、构图
    {
        scanf("%d%d",x+i,y+i);
        for(int j=1;j<i;j++)
            map[i][j]=map[j][i]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
    }
    //初始化每个点到原生成树集合的距离
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    for(int i=1;i<=n;i++)
    {
        int minn=0x3f3f3f3f,minj;
        for(int j=1;j<=n;j++)\\寻找最小距离
            if(!f[j]&&dis[j]<minn)
            {
                minn=dis[j];
                minj=j;
            }
        //更新答案并标记距离最小点
        ans=ans>minn?ans:minn;
        f[minj]=1;
        for(int j=1;j<=n;j++)//更新距离
            if(!f[j]&&dis[j]>map[minj][j])
                dis[j]=map[minj][j];
    }
    printf("%d\n",ans);//ans即为最大边权的平方
}
```

---

## 作者：不争不闹 (赞：0)

一句话题目：
给你一个只有点（n个）的图，找到最小的无向边边长使得图每两个点之间都连通

那就是典型的二分答案嘛
判断方法是从任意一个点（我用的第一个点）进行搜索，看是否能遍历整张图 

~~好水~~
>
```cpp

#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
inline int read()
{
	int n=0,w=1;register char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c<='9'&&c>='0')n=n*10+c-'0',c=getchar(); 
	return n*w;
}
struct Node{
	int x,y;
}cow[1001];
int n,emp,tmp;
bool vis[1001];
std::queue<int> q;
inline int work(int a,int b,int k)
{
	emp=cow[a].x-cow[b].x;
	tmp=cow[a].y-cow[b].y;
	return k>=emp*emp+tmp*tmp;
}
inline bool judge(int k)
{
	memset(vis,false,sizeof vis);
	while(!q.empty())q.pop();
	q.push(1);vis[1]=true;
	while(!q.empty())
	{
		int now=q.front();q.pop();
		for(int i=1;i<=n;++i)
			if(!vis[i]&&work(now,i,k))
				q.push(i),vis[i]=true;
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])
			return false;
	return true;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i)
		cow[i].x=read(),cow[i].y=read();
	int ans,l=0,r=1<<31-1,mid;//r开小了答案会是0
	while(l<=r)
	{
		mid=l+r>>1;
		if(judge(mid))
			ans=mid,r=mid-1;
		else	l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```

---

