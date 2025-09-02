# INTERVAL - Intervals

## 题目描述

有 $n$ 个区间，在区间 $[a_i,b_i]$ 中至少取任意互不相同的 $c_i$ 个整数。求在满足 $n$ 个区间的情况下，至少要取多少个正整数。

## 样例 #1

### 输入

```
1
5
3 7 3
8 10 3
6 8 1
1 3 1
10 11 1```

### 输出

```
6```

# 题解

## 作者：追梦_Chen (赞：39)

这题是差分约束系统一个很经典的例题，需要好好写一波~~
# 差分约束系统
### 定义
如果一个系统是由n个变量和m个约束条件组成，并且每个约束条件能够形成形如$$x_i-x_j<=c_k$$
### 我们就称该系统是差分约束系统
若你在AC此题前，对差分约束系统概念及应用**不熟悉**，可以看看这位神犇的blog

[膜拜巨佬](https://blog.csdn.net/my_sunshine26/article/details/72849441#commentBox)

讲一讲我的理解（请路过的神犇斧正）：我觉得差分约束系统是利用题面中给出的约束条件，和题干中隐藏的约束条件建图，之后求解最短（长）路的过程，在建图的过程中要先关注具体问题，若求的是**两个变量差的最大值**，那么将所有不等式转变成"**<=**"的形式并且在**建图后求最短路**，反之在转换成"**>=**"的形式，并且求**最长路**
# **咳咳咳，我们回到本题**
本题就是从0-50000选出最少的数，使每个区间至少有c个数被选，这是求最小值，**所以我们待会要将所有的不等式转换成">="的形式**
我们用数组d[i]表示0-i之间至少要选多少个数，所以对于每一个约束条件，可以看成$$d[b_i]-d[a_i-1]>=c_i$$

![](https://cdn.luogu.com.cn/upload/pic/30521.png)
上述公式变形$$d[b_i]>=c_i+d[a_i-1]$$

#### **因此我们在a[i-1]和b[i]之间建一条长度为c[i]的边**

上述建边过程只是题干中给出的条件，我们还要找出题目中的隐藏条件（隐藏条件视题目而为，有则加）。

#### 因为d[i]表示的是0-i之间要选的最小个数，所以d[i]一定要大于d[i-1]；

#### 又因为每个数只能选一次，所以d[i]-d[i-1]要么为0，要么为1；
由上述两个条件，我们对应出两个不等式
$$d_i-d_{i-1}>=0$$
$$d_{i-1}-d_{i}>=-1$$

**所以我们在i-1和i之间连长度为0的有向边，在i和i-1之间连长度为-1的有向边**

因为i的范围是0-50000所以i-1会变成负数，我们都知道，若数组的下标为负，程序会运行错误，**所以我们不妨给所有的变量加1，这样就不会出现负下标了**，所以上述加边过程可简述为
```cpp
1---->在a[i]和b[i]+1之间连一条长度为c[i]的有向边

2---->在i和i+1之间连一条长度为0的有向边

3---->在i+1和i之间连一条长度为-1的有向边
```
***接着，设d[0]为1,以0为起点求单元最长路***
# 注意

```cpp
求单元最长路要用SPFA算法，因为Dijkstra算法的贪心思路不适用于最长路，但是SPFA算法会把点x的所有出边都遍历一遍。既能求最短，也能求最长。
能屈能伸~~~~~~~~~~
```
**代码自然是标配**

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <queue>
//头文件请忽略
using namespace std;
const int maxn=500010;
int ver[maxn],head[maxn],edge[maxn],Next[maxn],tot,d[maxn];//d[i]表示从1到i至少需要多少个整数 
int n;
queue<int>q;
bool v[maxn+5]; 
void add(int x,int y,int z){
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}//加边函数
void SPFA(){
	memset(d,-1,sizeof(d));
	memset(v,0,sizeof(v));
	d[0]=0;v[0]=1;//以0号节点为起点
	q.push(0);
	while(q.size()){
		int x=q.front();
		q.pop();
		v[x]=0;
		for(int i=head[x];i;i=Next[i]){
			int y,z;
			y=ver[i];
			z=edge[i];
			if(d[y]<d[x]+z){
				d[y]=d[x]+z;
				if(!v[y])	q.push(y),v[y]=1;
			}
		}
	}
}
int main(){
	int t;
	scanf("%d",&t);
	scanf("\n");
	for(int k=1;k<=t;k++){
		tot=0;
		int mn=-1000; 
		memset(ver,0,sizeof(ver));
		memset(head,0,sizeof(head));
		memset(Next,0,sizeof(Next));
		memset(edge,0,sizeof(edge));//多组数据记得清空
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int a=0,b=0,c=0;
			scanf("%d%d%d",&a,&b,&c);
			add(a,b+1,c);
			mn=max(mn,b);//建图
		}
		for(int i=1;i<=mn+1;i++){
			add(i-1,i,0);
			add(i,i-1,-1);
		}//建图
		SPFA();//spfa求最长路
		if(k<t){
			printf("%d\n",d[mn+1]); 
		}else{
			printf("%d",d[mn+1]); 
		}
		
	}

	return 0;
}

```
能否求一波赞~~~~~

---

## 作者：emptysetvvvv (赞：15)

## 差分约束系统
### 背景
小萌新$\varnothing$要为心爱的小哥哥更新题解，但她还是希望得到一点点赞。

- **差分约束系统**：所谓差分约束系统，是由一系列形如$x_i-x_j\leqslant a_i$的不等关系互相约束组成的系统。注意，对于$x_i-x_j\geqslant a_i$的形式，应化为$x_j-x_i\leqslant -a_i$。这样的不等式组，要么无解，要么有无限解，因为通过这些不等式组只能得出相对大小关系。解差分约束系统，是$SPFA$的重要应用。

- 等等？？为什么会和图论扯上关系？？首先来看，在图中，若$j$到$i$有一条边权为$a$的有向边，则一定有$dis_i\leqslant dis_j + a$（$dis_i$表示起点到点$i$的距离），即$dis_i - dis_j\leqslant a$，这与系统中每一个不等式的结构完全一致，因此$x_i-x_j\leqslant a_i$等价于$j$到$i$有一条边权为$a_i$的边。在这幅图上以$i$为起点求最短路，求得$dis_j$即系统中$X_j$相对于$X_i$的最小值（$X_j$至少比$X_i$大多少）。同理，最长路即最大值。采用$SPFA$的原因相信大家已经很清楚了，边权可以为负。在求解时，我们往往规定$X_0$最为起点，这个$X_0$与所有点均有边权为$0$的边。

- 这里说的比较简略，有疑惑的话可以戳[这篇博客](https://blog.csdn.net/dragon60066/article/details/80245797)，他对$\varnothing$帮助很大。

### 思路

- 首先转化题意，区间$\displaystyle [L_i,R_i]$至少要选$\ C_i\ $个数，求**总共**即**前$R_{max}$个数**里面至少要选多少个。那么**前$R_i$个里面选的个数** 至少要比 **前$L_i-1$个里面选的个数**多$C_i$，换言之，若$X[i]$表示**前$i$个数选了多少个**，则$X[R_i]-X[L_i-1]\geqslant C_i$。问题化为固定$X[L_{min}-1]=0$，求$X[R_{max}]$的最小值。

- 问题分析到这一步，已经是很清晰的差分约束系统了。解不等式组求$X[R_{max}]-X[L_{min}-1]$的最小值。考虑到$\ 0\leqslant X[i]-X[i-1]\leqslant 1$，我们有$\begin{cases}X[l_i-1]-X[R_i]\leqslant -C_i\\X[i-1]-X[i]\leqslant 0\\X[i]-X[i-1]\leqslant 1\end{cases}$，根据上文"$X_i-X_j\leqslant C$等价于$j$到$i$有一条边权为$C$的边"建边跑**最短路**即可。

- 注意：既然$L_i$可以为$0$，就要考虑到$L_i-1$可能为负，所以我们在建图时需要统一给编号$+1$。另一点是，建边权为$-C_i$的边总是让人不爽，所以也可以反向建边，这样边权就为$C_i$了，最后求**最长路**，$dis[R_{max}+1]$（编号统一$\ +1$）。

### 代码

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int maxn = 50005;
bool in[maxn];
int Tot, n, cnt, source, target, dis[maxn], head[maxn];
struct Edge {
	int next, to, dist;
} e[maxn * 3];
void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].next = head[u];
    e[cnt].dist = w;
    head[u] = cnt;
}
queue<int> q;
void SPFA(int s) {
    memset(dis, -0x3f, sizeof dis);
    dis[s] = 0;
    q.push(s); in[s] = true; 
    while(!q.empty()) {
        int cur = q.front();
        q.pop(); in[cur] = false;
        for(int i = head[cur]; i; i = e[i].next)
            if(dis[e[i].to] < dis[cur] + e[i].dist) {
                dis[e[i].to] = dis[cur] + e[i].dist;
                if(!in[e[i].to]) q.push(e[i].to), in[e[i].to] = true;
            }
    }
}
int main() {
    scanf("%d", &Tot);
    while(Tot--) {
        memset(in, 0, sizeof in), memset(head, 0, sizeof head);
        cnt = 0, source = 0x3f3f3f3f, target = 0;
        scanf("%d", &n);
        for(int i = 0, l, r, w; i < n; i++) {
            scanf("%d %d %d", &l, &r, &w);
            add(l, r + 1, w);
            source = min(source, l), target = max(target, r + 1);
        }
        for(int i = source; i < target; i++)
            add(i, i + 1, 0), add(i + 1, i, -1);
        SPFA(source);
        printf("%d\n", dis[target]); if(Tot) putchar('\n');
    }
    return 0;
}
```

---

## 作者：年华天地 (赞：7)

我看其他题解都写的是差分约束，那我就来一发贪心的吧。
## 思路

首先，我们可以将给定的区间按照右端点排序，然后我们考虑怎么选数，首先我们都清楚，如果两个区间有重复，那么我们一定是在重复的区域选数是最优的，那么这个也一样，因为我们把区间按照右端点排好序了，所以我们一定是在区间的右边选数一定更优。

## 实现

知道了思路，我们怎么实现它呢？按照思路，我们需要从右边开始选数，那么我们需要一种数据结构来维护两个操作，一是询问当前区间选了多少个数，二是从右边开始选数，那么我们当然想到了万能的线段树呀。区间查询很常规，从右边开始选数就是给区间+1，只不过要优先在有区间加，也就是先便利右区间，我是用w（全局变量）记录要选多少个数，注意区间必须是小于等于w才加。
```
void add(int id,int l,int r)
{
	if (t[id].lazy)pushdown(id);
	if (t[id].l>r||t[id].r<l||w<=0||t[id].sum==t[id].len)return ;
	else if (t[id].l>=l&&t[id].r<=r&&w>=t[id].len-t[id].sum)
	{
		w-=t[id].len-t[id].sum;
		t[id].sum=t[id].len;
		t[id].lazy=1;
		return ;
	}
	else add(id*2+1,l,r),add(id*2,l,r);
	t[id].sum=t[id*2].sum+t[id*2+1].sum;
}
```

## 完整代码
```
#include<cstdio>
#include<algorithm>
#define mid (l+r)/2
using namespace std;
const int maxn=1e5;
int n,w;
struct node{
	int l,r,w;
}s[maxn];
struct tree{
	int l,r,sum,lazy,len;
}t[maxn*4];
bool cmp(node a,node b)
{
	return a.r<b.r;
}
void build(int id,int l,int r)
{
	t[id].l=l;
	t[id].r=r;
	t[id].sum=0;
	t[id].lazy=0;
	t[id].len=r-l+1;
	if (l==r)return ;
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
}
void pushdown(int id)
{
	t[id*2].lazy=t[id*2+1].lazy=1;
	t[id*2].sum=t[id*2].r-t[id*2].l+1;
	t[id*2+1].sum=t[id*2+1].r-t[id*2+1].l+1;
	t[id].lazy=0;
}
int query(int id,int l,int r)
{
	if(t[id].l>r||t[id].r<l)return 0;
	if (t[id].lazy)pushdown(id);
	if (t[id].l>=l&&t[id].r<=r)return t[id].sum;
	return query(id*2,l,r)+query(id*2+1,l,r);
}
void add(int id,int l,int r)
{
	if (t[id].lazy)pushdown(id);
	if (t[id].l>r||t[id].r<l||w<=0||t[id].sum==t[id].len)return ;
	else if (t[id].l>=l&&t[id].r<=r&&w>=t[id].len-t[id].sum)
	{
		w-=t[id].len-t[id].sum;
		t[id].sum=t[id].len;
		t[id].lazy=1;
		return ;
	}
	else add(id*2+1,l,r),add(id*2,l,r);
	t[id].sum=t[id*2].sum+t[id*2+1].sum;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int maxx=0;
		for (int i=1;i<=n;i++)scanf("%d%d%d",&s[i].l,&s[i].r,&s[i].w),maxx=maxx>s[i].r?maxx:s[i].r;
		build(1,1,maxx);
		sort(s+1,s+n+1,cmp);
		for (int i=1;i<=n;i++)w=s[i].w-query(1,s[i].l,s[i].r),add(1,s[i].l,s[i].r);
		printf("%d\n",t[1].sum);
	}
	return 0;
}
```




---

## 作者：_Diu_ (赞：3)

题目传送门：[SP116 INTERVAL - Intervals](https://www.luogu.com.cn/problem/SP116)

双倍经验：[UVA1723 Intervals](https://www.luogu.com.cn/problem/UVA1723)

三倍经验：[P1250 种树](https://www.luogu.com.cn/problem/P1250)

## 差分约束系统

## 建图

这一题的关键是建图

我们可以把对应前缀和的值映射到一张图上的每一个点

$d_i$表示在$[1,i]$中选了多少个数

那么对于每一对$(a,b,c)$，则有不等式$d_b-d_{a-1}>=c$

不等号两边同乘$-1$：$d_{a-1}-d_b<=-c$

利用这个不等式建图

还有隐含条件每一个数只有两个状态

即选或不选

则有不等式$0<=d_i-d_{i-1}<=1$

分解出两个不等式

$\begin{cases}d_{i-1}-d_i\le0\\d_i-d_{i-1}\le1\end{cases}$

建完图后以节点最大的$b$为起点跑$spfa$

$-d_0$就是答案了

## $code$

上代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
using namespace std;
const int N=50010;
int n,m,u,v,w,d[N],cnt[N],mx,ans;
bool vis[N];
queue<int> q;
struct cxk{
    int v,w;
};
vector<cxk> g[N];
int read(){//超级慢读 
    int x;
    scanf("%lld",&x);
    return x;
}
bool spfa(int s){
    memset(vis,0,sizeof(vis));
    memset(d,127,sizeof(d));
    memset(cnt,0,sizeof(cnt));
    d[s]=0;
    q.push(s);
    vis[s]=1;
    cnt[s]++;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i].v;
            int w=g[u][i].w;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=1,cnt[v]++;
                    if(cnt[v]==n)return 0;
                }
            }
              
        }
    }
    return 1;
}
void work(int t){
    m=read();
    for(int i=1;i<N;i++)g[i].clear();
    int mx=0;
    while(m--){
        u=read(),v=read(),w=read();
        mx=max(mx,v);
        g[v].push_back((cxk){u-1,-w});
    }
    for(int i=1;i<=mx;i++)g[i].push_back((cxk){i-1,0}),g[i-1].push_back((cxk){i,1});
    spfa(mx);
    printf("%lld\n",-d[0]);
    if(t)puts("");
}
signed main(){
	while(1+1!=2)printf("昔时稀世西世西市惜时西施吸食稀世西世西市惜时西施稀释稀屎\n");//防伪标志 
	int t;
	scanf("%lld",&t);
	while(t--)work(t);
	while(1+1!=2)printf("昔时稀世西世西市惜时西施吸食稀世西世西市惜时西施稀释稀屎\n");
}
```

### ~~个人有一些奇怪的癖好不要介意哈~~

---

## 作者：仙鸣 (赞：2)

# 这是一道差分约束的经典例题!!!

#### 令d[i]表示0到i这个区间内至少要选出d[i]个数，那么对于每个[ai,bi],有d[b] - d[ai-1] >= ci，同时隐含的一个条件是0 <= d[i] - d[i-1] <= 1,但是因此d[-1]不能表示，令d[i+1]示0到i这个区间内至少要选出d[i+1]个数，然后d[0] = 0,直接求取最长路就行了。边的存储使用链式向前星，这样效率最高。

[大佬讲差分约束](https://blog.csdn.net/consciousman/article/details/53812818 )

###### 代码附上
```cpp
#include<iostream>
#include<cstdio> 
#include<algorithm>
#include<cstring>
#include<cmath>
#define INF -0x3f3f3f3f
using namespace std;
struct node {
	int to,next,q;
} a[10000005];
int last[10000005],tz=0,dis[10000005],f[10000005],lt[10000005];
void add(int x,int y,int z) {
	a[++tz].to=y;
	a[tz].next=last[x];
	a[tz].q=z;
	last[x]=tz;
}
int main() {
	int n,mx=0,mn=999999;
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		memset(a,0,sizeof(a));
		memset(last,0,sizeof(last));
		memset(last,0,sizeof(last));
		memset(lt,0,sizeof(lt));
		memset(f,0,sizeof(f));
		int y;
		scanf("%d",&y);
		for(int j=1; j<=y; j++) {
			int w,x,z;
			scanf("%d%d%d",&w,&x,&z);
			add(w,x+1,z);
			mx=max(x,mx);
			mn=min(w,mn);
		}
		for(int i=mn; i<=mx; i++)dis[i]=INF;
		mx+=1;
		for(int i=mn; i<mx; i++) {
			add(i,i+1,0);
			add(i+1,i,-1);
		}
		int head=1,tail=1;
		lt[head]=mn;
		f[mn]=1;
		dis[mn]=0;
		while(head<=tail) {
			int j=lt[head];
			for(int i=last[j]; i; i=a[i].next) {
				int k=a[i].to;
				if(dis[k]<dis[j]+a[i].q) {
					dis[k]=dis[j]+a[i].q;
					if(f[k]==0) {
						f[k]=1;
						lt[++tail]=k;
					}
				}
			}
			f[j]=0;
			lt[head]=0;
			head++;
		}
		printf("%d\n",dis[mx]);
	}
	return 0;
}
```


---

## 作者：Vanilla_chan (赞：1)

节选自[拓扑/差分约束学习笔记](https://www.luogu.com.cn/blog/Vanilla-chan/ta-pu-ci-fen-yue-shu-xue-xi-bi-ji)。如果您想学习差分约束的话不妨看看~

## Problem

从$0\sim50000$选出最少的数，使每个区间至少有$c$个数被选。

## Solution

这是求**最小值**，所以将所有的不等式转换成$\ge$的形式。

类似于[P1250 种树](https://www.luogu.com.cn/problem/P1250)的思想，考虑如何将题目中的

设$sum[x]$是前缀和：

对于每一个约束条件，可以看成$sum[b_i]-sum[a_i-1]\ge c_i$.

由于**每一个数只能选择一次**，$0\le sum_x-sum_{x-1}\le1$.

注意这里下标是从$0$开始的，所以就全部$+1$就好。

最后，多测不清空，抱玲两行泪。

## Code

```c++
/**************************************************************
 * Problem: SP116
 * Author: Vanilla_chan
 * Date: 20210330
 * E-Mail: Vanilla_chan@outlook.com
**************************************************************/
//预编译部分已略
#define N 500010
int n,m,s;
int head[N],ver[N<<1],cnt[N],nxt[N<<1],w[N<<1],dis[N],book[N];
int tot;
void insert(int x,int y,int z)
{
	nxt[++tot]=head[x];
	head[x]=tot;
	w[tot]=z;
	ver[tot]=y;
}
struct node
{
	int x,dis;
	node(int xx,int vv)
	{
		x=xx,dis=vv;
	}
};
queue<node>q;
LL ans;
int t;
signed main()
{
// 	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	t=read();
	while(t--)
	{
		tot=0;
		memset(head,0,sizeof(head));
		memset(nxt,0,sizeof(nxt));
		memset(dis,0,sizeof(dis));
		memset(cnt,0,sizeof(cnt));
		memset(w,0,sizeof(w));
		memset(book,0,sizeof(book));
		memset(ver,0,sizeof(ver));
		n=0;
		m=read();
		for(int i=1,a,b,c;i<=m;i++)
		{
			a=read();
			b=read();
			c=read();
			n=max(n,max(a,b));
			insert(a,b+1,c);
		}
		s=n+2;
		for(int i=1;i<=n+1;i++)
		{
			dis[i]=-1;
			insert(s,i,0);
			insert(i-1,i,0);
			insert(i,i-1,-1);
		}
		
		int x;
		q.push(node(s,0));
		while(!q.empty())
		{
			x=q.front().x;
			q.pop();
			book[x]=0;
			for(int i=head[x],v;i;i=nxt[i])
			{
				v=ver[i];
				if(dis[v]<dis[x]+w[i])
				{
					dis[v]=dis[x]+w[i];
					if(!book[v])
					{
						if(cnt[v]>n)
						{
							cout<<"-1";
							return 0;
						}
						
						q.push(node(v,dis[v])),book[v]=1,cnt[v]++;
					}
				}
			}
		}
		cout<<dis[n+1]<<endl;
	}
	return 0;
}
```



---

## 作者：xixiup (赞：1)

## 思路分享

思考，对于取数满足区间大于小于问题的题，我们可以考虑**差分约束**。

考虑将一个整数看作一个点，题中的一个区间 $a_i,b_i,c_i$ 就可以看作一条边 $a_i \xrightarrow{c_i} \left(b_i+1\right)$。

然后对于区间相交的情况，我们怎么考虑呢？

我们可以思考，对于两个相交的区间，在这里面选 $1$ 个整数可以作出 $2$ 的贡献，所以我们就可以对于任意一个整数 $i\in \left( 1,n \right]$ 建两条边 $\left( i-1 \right) \xrightarrow{0} i$ 和 $\left( i-1 \right) \xleftarrow{-1} i$ 就可以了。

然后，我们就可以在这个图上跑最长路，由于 $c_i \leqslant b_i-a_i+1$，所以图中没有正环。

最后的答案就是 $dis_{maxm+1}$ 了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+100,maxm=5e5+100;
int n,m,bg[maxn],ne[maxm],to[maxm],le[maxm],cnt;
int ans[maxn],in[maxn];
priority_queue<pair<int,int> >q;
void add(int x,int y,int z){
	cnt++;
	ne[cnt]=bg[x];
	to[cnt]=y;
	le[cnt]=z;
	bg[x]=cnt;
}
void dijkstra(){//最长路
	for(int i=2;i<=50001;i++){
		ans[i]=-1000000000;
	}
	memset(in,0,sizeof(in));
	q.push(make_pair(0,1));
	while(!q.empty()){
		int x=q.top().second;
		q.pop();
		in[x]=0;
		for(int i=bg[x];i;i=ne[i]){
			int y=to[i];
			if(ans[x]+le[i]>ans[y]){
				ans[y]=ans[x]+le[i];
				if(in[y]!=1){
					in[y]=1;
					q.push(make_pair(ans[y],y));
				}
			}
		}
	}
	while(!q.empty()){
		q.pop();
	}
	printf("%d\n",ans[50001]);
}
int main(){
	freopen("SP116.in","r",stdin);
	freopen("SP116.out","w",stdout);
	int t;
	cin>>t;
	for(int T=1;T<=t;T++){
		scanf("%d",&n);
		memset(bg,0,sizeof(bg));
		memset(ne,0,sizeof(ne));
		memset(to,0,sizeof(to));
		cnt=0;
		for(int i=2;i<=50001;i++){//相邻的点加边
			add(i,i-1,-1);
			add(i-1,i,0);
		}
		for(int i=1;i<=n;i++){//每一个区间加边
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			add(x,y+1,z);
		}
		dijkstra();
	}
	return 0;
}

```


---

## 作者：极寒神冰 (赞：1)

### 差分约束

我们一般将$d_u+w>=d_v$称作三角形不等式，就是在点u上连一条权值为w的边到点v。

题意就是告诉你一些不等式 $S[a_i]-S[b_i]>=c_i$,且满足$S[i]-S[i-1]>=0$且$s[i]-s[i+1]>=-1$。然后求这些不等式组的最小解。

首先可以移项得$S[a_i]-c_i>=S[b_i]$即将$a_i$到$b_i$连一条边权为$-c_i$的边。

为了满足$S[i]-S[i-1]>=0$且$s[i]-s[i+1]<=1$,我们可以从$i$到$i+1$建一条边权为$0$,从$i+1$到$i$连一条边权为$-1$的边。

之后用spfa跑最长路即可

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int N=600010;
const int inf=0x3f3f3f3f;
struct edge
{
	int nxt,to,val;
}e[N];
int dis[N],head[N],n,minn=inf,maxx=-inf,cnt,vis[N];
inline void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v,int d)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].val=d;
	head[u]=cnt;
}
inline void spfa()
{
	queue<int>q;
	q.push(minn);
	dis[minn]=0;
	while(q.size()>0)
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].to;
			if(dis[v]<dis[u]+e[i].val)
			{
				dis[v]=dis[u]+e[i].val;
				if(!vis[v])
				{
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}
int _;
int main()
{
	{
		init();
		n=read();
		for(int i=1;i<=n;i++)
		{
			int x=read(),y=read(),z=read();
			add_edge(x,y+1,z);
			minn=min(minn,x);
			maxx=max(maxx,y+1);
		}
		for(int i=minn;i<=maxx;i++)
		{
			dis[i]=-inf;
			add_edge(i,i+1,0);
			add_edge(i+1,i,-1);
		}
		spfa();
		cout<<dis[maxx]<<endl;
	}
	
}
```




---

## 作者：Y_B_Y (赞：1)

这一题和P1250类似,但是数据范围大了很多,所以朴素的贪心不能过,我们得另寻他路

这一题的题意为,在数轴上给$n$个区间,每个区间内要区一定的整数,所以我们可以设$S_i$为$i$之前(包括i自身)取了多少个整数,假设它给我们一个区间$[l,r]$,在这个区间中**至少**要取$w$个数,所以可以得到$S_r-S_{l-1}≥w$

现在我们不难发现,可以用差分约束来解决这个问题(如果没学过差分约束,看[P5960 【模板】差分约束算法](https://www.luogu.com.cn/problem/P5960))

所以我们可以从$l-1$号点向$r$号点连一条长度为$w$的边,再跑一遍最长路(因为$S_{l-1}+w≤S_r$,类似最长路的求法),就发现$\operatorname{WA}$惨了,为什么?

因为这一个条件还不太够,因为我们发现这样建出来的图并不联通,所以我们要想一种方法是不同区间关联在一起,我们再看题目的数据范围发现$0≤l,r≤50000$,所以我们可以一口气把所有的数关联再一起

我们不难发现$S_i-S_{i-1}≤1,S_{i-1}-S_i≤0$

变形得$S_{i-1}-S_i≥-1,S_i-S_{i-1}≥0$,并在代码中将这些点连在一起

我们设所有区间中$l$的最小值为$minn$,$r$的最大值为$maxn$,由题目知$S_{minn-1}=0$(因为在这前面放了无意义,血亏),而我们要求的是$S_{maxn}$

所以从$minn-1$开始跑最长路($\operatorname{SPFA}$的重生),再输出$S_{maxn}$,就可以了

还有一件事,为了防止出现负下标,我们可以将上面的所以**下标**和**点的序号**全部加一

细节看代码,注意每跑完一次要**完全的初始化一遍**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+999,M=N;
int n,m,ft[N],v[N],t,dis[N],cnt,tim[N],a[N],l[N],r[N],w[N],tot,maxn=-0x3f3f3f3f,minn=0x3f3f3f3f;
bool inq[N];
queue<int> Q;
struct hh
{
    int nx,to,w;
}rd[M];
int spfa(int st) //SPFA最长路
{
	
    for(int i=minn;i<=maxn;i++) dis[i]=-0x3f3f3f3f;
    dis[st]=0;
    inq[st]=1;
    Q.push(st);
    while(!Q.empty()) 
    {
       int now=Q.front();Q.pop();
       inq[now]=0;
       for(int i=ft[now];i;i=rd[i].nx) 
       {
           int to=rd[i].to,w=rd[i].w;
           if(dis[to]<dis[now]+w) 
           {
               dis[to]=dis[now]+w;
               if(!inq[to]) 
               {
				  tim[to]++;
                  Q.push(to);
                  inq[to]=1;
               }
           } 
       }
    }
    return 0;//终点可改
}
void add(int x,int y,int w)
{
	rd[++cnt].nx=ft[x];
	ft[x]=cnt;
	rd[cnt].to=y;
	rd[cnt].w=w;
}
inline long long read()
{
    char c=getchar();long long sum=0,f=1;
    while(!(c>='0'&&c<='9')) {if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') {sum=((sum<<1)+(sum<<3))+(c-'0');c=getchar();}
    return sum*f;
}
signed main()
{
	int T=read();
	while(T--)
	{
	n=read();
	for(int i=1;i<=n;i++) 
	{
		int x=read(),y=read();
		add(x,y+1,read());//连边
		minn=min(minn,min(x,y+1));//求minn和maxn
		maxn=max(maxn,max(x,y+1));
	}
	for(int i=minn;i<maxn;i++)  add(i+1,i,-1),add(i,i+1,0);//连边
	spfa(minn);
	printf("%d\n",dis[maxn]);
	if(T>0) putchar('\n');//注意输出,最后一行不要回车
	for(int i=minn;i<=maxn;i++) ft[i]=0,tim[i]=0;//初始化
	for(int i=1;i<=cnt;i++) rd[i].nx=rd[i].to=rd[i].w=0;//初始化
	cnt=0;//初始化
    }	
	return 0; 
}
```


---

## 作者：Hexarhy (赞：1)

### Preface

差分约束经典例题，在李煜东的《算法竞赛进阶指南》里有。关键在于构造不等式。

### Solution

题面给的约束条件是对于区间 $[a_i,b_i]$，于是很套路地设 $s_i$ 为区间 $[1,i]$ 中取的个数。那么约束条件就转化为：

$$s_{b_i}-s_{a_i-1}\ge c_i$$

值得注意的是，本题还有一些**隐含**的约束条件。

- $\forall i\in[1,50000],s_i-s_{i-1}\ge 0$，任意区间取的个数不能为负数。

- $s_i-s_{i-1}\le 1$，任意区间取的个数不能超过区间长度。

接下来就跑差分约束。题目求最小值，于是就转化为求最长路。

$$\begin{cases}s_{b_i}\ge s_{a_i-1}+c_i\\s_i\ge s_{i-1}\\s_{i-1}\ge s_i-1\end{cases}$$

答案就是 $dis[50000]$。

### Notice

- 注意 $n$ 只是约束条件个数。未知量个数应该为 $50000$。

- 多测要清空。

### Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <climits>
using namespace std;

const int MAXN=5e4+5;
#define N 50000
int n;
struct node
{
	int to,val;
};
vector<node> edge[MAXN];
int dis[MAXN];
bool visit[MAXN];

void clear(void)
{
	memset(visit,false,sizeof(visit));
	for(int i=0;i<=N+1;i++)	dis[i]=INT_MIN;
	for(int i=0;i<=N+1;i++)	edge[i].clear();
}

void spfa(const int st)
{
	queue<int> q;
	visit[st]=true;dis[st]=0;
	q.push(st);
	while(!q.empty())
	{
		const int u=q.front();
		q.pop();
		visit[u]=false;
		for(auto it:edge[u])
		{
			const int v=it.to,w=it.val;
			if(dis[v]<dis[u]+w)//最长路
			{
				dis[v]=dis[u]+w;
				if(!visit[v])
				{
					q.push(v);
					visit[v]=true;
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int T;cin>>T;
	while(T--)
	{
		clear();
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			int u,v,w;cin>>u>>v>>w;
			edge[u-1].push_back(node{v,w});
		}
		for(int i=1;i<=N;i++)
		{
			edge[i-1].push_back(node{i,0});
			edge[i].push_back(node{i-1,-1});
		}
		spfa(0);
		cout<<dis[N]<<endl;
	}
	return 0;
}
```

---

## 作者：Zxsoul (赞：0)

## 差分约束 板子

### 题面

>从给定范围内选出尽量少的整数，使每个区间$[a_i,b_i]$内都有至少 $c_i$ 个数被选出

### 思路

既然这是一道差分约束题，那么就需要找出**不等关系**

题目中的 $x_i$ 作为未知量，将其表示出来就好了，

我们将每个 $x_i$ 用 $s[i]$ 表示 0~i 中最少选的数

那么为了满足条件，我们有 $s[b_i]-s[a_i - 1] >= c_i$

系统已找出，因为是最少，所以跑 **最长路**，值得高兴地是他**没卡**

### 实现方式

上述式子只是大体，不好表示，因此我们发现一些隐含的条件，即
$$
s[i] - s[i - 1] >= 0
$$

$$
s[i] - s[k - 1] <= 1
$$
有了这样的式子，建图就可以充分了，题解完毕

### Code
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
struct node{
  int v, nxt, w;
} e[B];
int vis[B], dis[B];
int head[B], cnt, n, m, minx = inf, manx = -inf;
void add(int u, int v, int w){
  e[++cnt].nxt = head[u];
  e[cnt].v = v;
  e[cnt].w = w;
  head[u] = cnt;
}
void spfa(int s){
  memset(vis, 0, sizeof(vis));
  memset(dis, -inf, sizeof(dis));
  queue<int> q;
  dis[s] = 0, vis[s] = 1, q.push(s);
  while(!q.empty()){
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt){
      int v = e[i].v, w = e[i].w;
      if(dis[v] < dis[u] + w)
      {
        dis[v] =dis[u] + w;
        if(!vis[v]){
          vis[v] = 1;
          q.push(v);
        }
      }
    }
  }
}
int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
  m = read();
  while(m--){
    memset(head, 0, sizeof(head));
    minx = inf;
    manx = -inf;
    cnt = 0;
  n = read();
  for(int i = 1; i <= n; i++){
    int a, b, c;
    cin >> a >> b >> c;
    add(a - 1, b, c);
    minx = min(minx, a - 1);
    manx = max(manx, b);
  }
  for(int i = minx; i <= manx; i++){
    add(i, i + 1, 0);
    add(i + 1, i, -1);
  }
  spfa(minx);
  cout << dis[manx] << endl;
}
  fclose(stdin);
  fclose(stdout);
  return 0;
}


```

---

## 作者：Azuree (赞：0)

[查看原题请戳这里](https://www.luogu.org/problem/SP116)

## 差分约束

差分约束系统：由N个变量$X_1, X_2, X_3 …. X_N$和$M$个未知条件组成的N元一次不等式组，其中，每个条件都形如  
$X_i \le X_j + C_k$  
我们的问题是：给出一组满足所有条件的解，否则判断出无解  

注意到，$X_i\le X_j + c_k$ 与单源最短路中的三角不等式很相似，建立N个节点对应N个变量。对于每组条件，从 j 向i连一条边。同时虚构0号节点并向每一个节点连一条边，如果存在负环则无解。否则有解。  

## 问题转化
那么，我们怎么根据这个题目建立起一个差分约束系统呢？  
我们可以用$siz[i]$表示区间$[0,i]$中被选的元素的个数，那么区间$[a_i,b_i]$中被选中的元素的个数我们就可以用$siz[b_i]-siz[a_i-1]$来表示。于是我们就可以从$a_i-1$向$b_i$连一条权值为$w$的有向边。  
另外，为了保证图的连通性，我们需要再从每一个数$a$向$a+1$连一条权为$0$的边，从每一个数$a$向$a-1$连一条权为$-1$的边。

那么，为什么这么连呢？  

因为$siz[a+1] -siz[a] \le 1$且$siz[a]-siz[a+1]\ge-1$。

最终的图是这个样子的（以该数据为例）![](https://wflight.github.io/2019/08/05/%E9%A2%98%E8%A7%A3-SP116-%E3%80%90INTERVAL-Intervals%E3%80%91/1564974953405.png)  
![1564974989829](https://wflight.github.io/2019/08/05/%E9%A2%98%E8%A7%A3-SP116-%E3%80%90INTERVAL-Intervals%E3%80%91/1564974989829.png)

code：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
#define ll long long
#define INF 0x7fffffff
#define re register

using namespace std;

int read()
{
	register int x = 0,f = 1;register char ch;
	ch = getchar();
	while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
	while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}

int x,y,z,n,cnt,ans,minn,maxx;
int d[200005],vis[200005],dis[200005];

struct edge{
	int to,next,v;
}e[200005];

void add(int x,int y,int z)
{
	e[++cnt].to = y;
	e[cnt].v = z;
	e[cnt].next = d[x];
	d[x] = cnt;
}

void clannad()
{
	for(int i = 0; i <= cnt; i++) e[i].to = 0,e[i].next = 0,e[i].v = 0;
	for(int i = 0; i <= cnt; i++) d[i] = 0;
	cnt = 0;
}

queue<int> que;

int spfa(int s)
{
	while(!que.empty()) que.pop();
	for(int i = minn; i <= maxx; i++) dis[i] = -INF;
	dis[s] = 0;
	memset(vis,0,sizeof(vis));
	que.push(s);
	dis[s] = 0;
	vis[s] = 1;
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		vis[u] = 0;
		for(int i = d[u]; i; i = e[i].next)
		{
			int v = e[i].to;
			int w = e[i].v;
			if(dis[v] < dis[u] + w)
			{
				dis[v] = dis[u] + w;
				if(!vis[v]) que.push(v),vis[v] = 1;
			}
		}
	}
	return dis[maxx];
}

int main()
{
	int t;
	t = read();
	for(t; t > 0; t--)
	{
		n = read();
		maxx = -INF;
		minn = INF;
		for(int i = 1; i <= n; i++)
		{
			x = read();
			y = read();
			z = read();
			add(x - 1,y,z);
			maxx = max(y,maxx);
			minn = min(x - 1,minn);
		}
		for(int i = minn; i <= maxx; i++)
		{
			add(i,i + 1,0);
			add(i + 1,	i,-1);
		}
		int ans = spfa(minn);
		printf("%d\n",ans);
		clannad();
	}
    return 0;
}
```


---

## 作者：doyo (赞：0)

本题属于较裸的差分约束题

先介绍一下差分约束系统

1、一般包含N个变量x1~xn以及M个约束条件

2、每个约束条件都是由两个变量作差构成的（当然，有些题不是差可以化成作差）形如xi-xj<=ck

那么我们需要求出一组解使得所有约束条件得到满足，就是求解差分约束

因为差分约束中的每一个约束条件都可变形为xi<=xj+ck，所以我们可以把变量xi看做有向图中的结点，然后ck看做边权，跑一遍最短路即可

当然，对于这道题，我们设s[k]表示0~k之间最少选出s[k]个整数，所以有s[bi]-s[ai-1]>=ci

整理后变为c[i]+s[ai-1]<=s[bi]

只不过变为了最长路而已，而且题目给定了ci<=bi-ai+1,说明一定有解，连正环都不用判断。

:“关于SPFA，它已经死了”

不，它还活在差分约束里。

这里大家一定要注意，求最长路不能只是简单地把dijkstra里的三角不等式改一下

我们都知道dijkstra最短路不能处理负边权，所以，最长路它也不能处理正边权。 于是，上代码
```
#include<cstdio>
#include<queue>
#include<string>
#include<algorithm>
#include<cstring>
#define il inline
using namespace std;
const int maxn=5e5+5;
const int inf=0x7fffffff;
struct Edge
{
	int next;
	int to;
	int dis;
}edge[maxn];
bool vis[maxn];
int head[maxn],dis[maxn];
int n,m,t,maxx,minn,tot;
queue<int> q; 
il void addedge(int from,int to,int dis)
//链式前向星存边 
{
	edge[++tot].next=head[from];
	edge[tot].to=to;
	edge[tot].dis=dis;
	head[from]=tot;
}
il int read()
{
	int num=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=num*10+ch-'0';
		ch=getchar();
	}
	return num*f;
}
void spfa()
//spfa求最长路，不过这里不需要判断正环
//因为题目保证c[i]<=b[i]-a[i]+1,所以肯定有解 
{
	for(int i=0;i<=maxx;i++) dis[i]=-inf;
	dis[minn]=0;vis[minn]=true;q.push(minn);
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=false;
		for(int i=head[u];i;i=edge[i].next)
		{
			int v=edge[i].to;
			if(dis[u]+edge[i].dis>dis[v])
			{
				dis[v]=dis[u]+edge[i].dis;
				if(!vis[v])
				{
					vis[v]=true;
					q.push(v);
				}
			}
		}
	}
}
int main()
{
	int x,y,z;
	t=read();
	while(t--)
	{
		maxx=-inf;minn=inf;tot=0;//每做一次都要初始化！！！ 
		memset(vis,false,sizeof vis);//认真！本蒟蒻因为忘了将tot赋为零无限RE 
		memset(head,0,sizeof head);
		memset(edge,0,sizeof edge);
		n=read();
		for(int i=1;i<=n;i++)
		{
			x=read();y=read();z=read();
			addedge(x-1,y,z);
			minn=min(minn,x-1);
			maxx=max(maxx,y);
		}
		for(int i=minn;i<=maxx;i++)
		{
			addedge(i,i+1,0);//加上一些判定条件，保证解有意义
			addedge(i+1,i,-1);
		}
		spfa();
		printf("%d\n",dis[maxx]);
	}
	return 0;
}
```



---

