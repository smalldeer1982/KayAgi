# Robotruck

## 题目描述

有n个垃圾，第i个垃圾的坐标为(xi,yi)，重量为wi。有一个机器人，要按照编号从小到大的顺序捡起所有垃圾并扔进垃圾桶（垃圾桶在原点(0,0)）。机器人可以捡起几个垃圾以后一起扔掉，但任何时候其手中的垃圾总重量不能超过最大载重C。两点间的行走距离为曼哈顿距离（即横坐标之差的绝对值加上纵坐标之差的绝对值）。求出机器人行走的最短总路程（一开始，机器人在(0,0)处）。

# 题解

## 作者：五年长久 (赞：2)

# Robotruck 题目解析
[题面 PDF](https://onlinejudge.org/external/11/p1169.pdf)  
## 写在前面
有一说一，UVa 的输出真让人难绷。  
教练在讲解这道题的时候，曾经嘲讽说这道题不配紫题，也不知道管理员能不能接纳这个意见吧难度降成蓝色。  
然而这道题还是不很顺手，写个题解自己捋一捋思路吧。  
参考了刘汝佳的紫书，并且尽量从我能理解的方向去阐明思路。  
## 状态转移方程
这道题明显 DP。那么对于一道 DP 题，首先思考定义。  
试定义：$dp_i$ 为**前 $i$ 个元素中一口气运 $i-j$ 个的最小代价**，换而言之，过程被分解成了两部分：  
第一步：先以最优方式运送 $j$ 个垃圾；  
第二步：一口气运送第 $j+1$ 到 $i$ 这么多垃圾。  
若令$distance_{i → j}$表示 $i$ 到 $j$ 一共要走的路程（曼哈顿距离），那么则有：  
$$dp_i=\min{dp_j+distance_{0 → j+1}+distance_{0 → i}+distance_{j+1 → i}}$$
$dp_j$ 好理解，剩下的部分就是先走到 $j+1$，再从 $j+1$ 捡垃圾一直到 $i$，最后从 $i$ 回到原点。  
所以 $j$ 的取值范围也不难得到：  
$$j∈[0,i),\sum_{x=j+1}^{i}{weight_x}\le c$$
其中 $weight_x$ 代表了每个垃圾的质量。  
代码实现也很方便，但是 $O(n^2)$ 的时间复杂度，显然不是我们希望的。
## 能不能更快一点？
如果使用前缀和解决这道问题，试定义：$dis\_m$ 表示用前缀和存储的两个点之间的曼哈顿距离，$dis\_back$ 表示每个点和原点之间的距离。  
则上述状态转移方程变为：
$$dp_i=\min{dp_j+dis\_back_{j+1}+dis\_back_{i}+dis\_m_{i}-dis\_m_{j+1}}$$
显然，$dis\_back_{i}$ 和 $dis\_m_{i}$ 两个对于同一个 $i$ 而言是定量，不变，可以从 $\min$  中提取出来。  
则状态转移方程变为：
$$dp_i=\min({dp_j+dis\_m_{j+1}+dis\_back_{j+1}}) +dis\_m_{i}+dis\_back_{i}$$
若定义 $f_j=d_j+dis\_m_{j+1}+dis\_back_{j+1}$，那么状态转移方程进一步简化为：
$$dp_i=\min{\green{f_j}}+dis\_m_{i}+dis\_back_{i}\ \ (j∈[0,i),且\green{\sum_{x=j+1}^{i}{weight_x}\le c})$$
如果想优化，那么不难发现我标出绿色的两端是我们极力争取的。  
1. 先思考 $\min{f_j}$，只要它合法，且没有比他更小的来替代它，那么此时对于 $dp_i$，选择谁呼之欲出。而且，在得到一个新 $dp_i$ 后，如果**此后**有一个比他小的数出现，那么，可以果断舍弃较大的。也许我们可以通过一个能把最小值直接送到我们面前的数据结构来解决这个问题。
   
2. 接着思考 $\sum_{x=j+1}^{i}{weight_x}\le c$，如果一个 $i$ 足够大，那么对于开始的若干个物品，我们认为他已经不合法了，而且未来也不会合法，对于这些数据，我们果断舍弃。  

综上所述，我们可以使用**单调队列**优化这道题。
## 解决
首先，我们需要定义一个函数来计算上述的 $f_i$:
```c++
int com(int x){
	return dp[x]-dis_m[x+1]+dis_back[x+1];
}
```
接着，就可以开始单调队列了。维护一个单增队列，同时动态队头出队：
```c++
front=rear=1;
for(int i=1;i<=n;i++){
  while(front<=rear&&tot_weight[i]-tot_weight[q[front]]>c){
    front++;
  }
  dp[i]=com(q[front])+dis_m[i]+dis_back[i];
  while(front<=rear&&com(i)<=com(q[rear])){
    rear--;
  }
  q[++rear]=i;
}
```
同时，输出的时候要注意，输出完一行空一行再输出，最后一个数据不输出多余的空行。UVa 老传统了。  
还有一个小细节。在代码中可以看到我使用宏定义自己写了一个 ``abs``，而非使用 ``cmath`` 或``algorithm``，这是一个比较基本的原则：能不用上述的两个库（尤其是 ``cmath``）尽量不用，尤其是在单独用 ``abs`` 的时候，一行宏定义解决的问题就不要搞进来一堆函数。上述的两个库函数太多，容易起冲突。
## 代码
那么，代码解决也不难了，和其他题解大同小异，互相形成对照。
```c++
//exam name:[UVA1169]Robotruck
/*
dp[i] 表示前i个物品一口气运前j个的代价
dp[i]=min{dp[j]-dis_m(j+1)+dis_back(j+1)}+dis_m(i)+dis_back(i)
前j个物品运输代价+(j+1)到i的曼哈顿距离+去(j+1)的曼哈顿距离+回原点的曼哈顿距离 
*/
#include <iostream>
#include <cstring>
#include <cstdio>
#define abs(x) (((x)>0)?(x):(-(x)))
#define int long long 
using namespace std;
const int MAXN=100005;
int com(int);
int dp[MAXN],dis_m[MAXN],dis_back[MAXN],tot_weight[MAXN];
int x[MAXN],y[MAXN],w[MAXN];
int q[MAXN];
int front,rear;
int t,c,n;
signed main(){
	cin>>t;
	for(int kase=1;kase<=t;kase++){
		memset(dis_m,0,sizeof(dis_m));
		memset(dis_back,0,sizeof(dis_back));
		memset(tot_weight,0,sizeof(tot_weight));
		x[0]=y[0]=0;
		cin>>c>>n;
		for(int i=1;i<=n;i++){
			cin>>x[i]>>y[i]>>w[i];
			dis_back[i]=abs(x[i])+abs(y[i]);
			dis_m[i]=dis_m[i-1]+abs(x[i]-x[i-1])+abs(y[i]-y[i-1]);
			tot_weight[i]=tot_weight[i-1]+w[i];
		}
		front=rear=1;
		for(int i=1;i<=n;i++){
			while(front<=rear&&tot_weight[i]-tot_weight[q[front]]>c){
				front++;
			}
			dp[i]=com(q[front])+dis_m[i]+dis_back[i];
			while(front<=rear&&com(i)<=com(q[rear])){
				rear--;
			}
			q[++rear]=i;
		}
		cout<<dp[n]<<endl;
		if(kase<t){
			puts("");
		}
	}
	return 0;
}
int com(int x){
	return dp[x]-dis_m[x+1]+dis_back[x+1];
}
```
## 写在后面
本人蒟蒻，某些地方没有讲清楚的什么的可以联系我，我会及时极力修改，感谢大家支持！

---

## 作者：zsc2003 (赞：2)

看到另一个大佬写的线段树优化$dp$

我就在这里写一篇单调队列优化的吧

首先思路是差不多的,令$dp_i$表示当前处理到第$i$个垃圾并且把它放回到了垃圾桶$(0,0)$

$s_i$表示前$i$个垃圾的质量的前缀和

$dis_i$表示前$i$个垃圾的曼哈顿距离的前缀和

$d_i$表示从$(0,0)$到$i$个垃圾的曼哈顿距离

这样就不难写出$dp$方程

$ dp_i=min(dp_i , dp_j+dis_i-dis_{j+1}+d_i+d_{j+1}) \ \ \ \ \ \ \ \   (0 \leq j \leq i-1)$

将与$i$无关的部分提出来$:dp_j-dis_{j+1}+d_{j+1}$

将这一部分使用单调队列优化掉,最后加上剩余的与$i$有关的部分$$即可

下面附上代码$($另一篇题解提供的$hack$数据本代码也可以通过$)$


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
inline int read()//读入优化 
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=100010;
int T,n,c;
int dp[N];
int s[N],dis[N];
struct node
{
	int x,y,w;
}a[N];
inline int dist(int i,int j){return abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y);}//求出两点间的曼哈顿距离 
int q[N],head,tail;
int d[N];
int main()
{
	T=read();
	while(T--)
	{
		c=read(),n=read();
		memset(dp,0x3f,sizeof(dp));//最初把答案赋成+∞
		dp[0]=0;//因为有多组数据,记得把所有数组清空 
		s[0]=0,dis[0]=0;
		a[0].x=0,a[0].y=0,a[0].w=0;
		for(int i=1;i<=n;i++)
		{
			a[i].x=read(),a[i].y=read(),a[i].w=read();
			s[i]=s[i-1]+a[i].w;
			dis[i]=dis[i-1]+dist(i,i-1);
			d[i]=a[i].x+a[i].y;
		}
		head=1,tail=1;
		q[1]=0;//要先将0入队列中 
		for(int i=1;i<=n;i++)
		{
			while(head<=tail&&(s[i]-s[q[head]]>c))
				head++;
			if(head<=tail)
				dp[i]=dis[i]+d[i]+dp[q[head]]-dis[q[head]+1]+d[q[head]+1];
			while(head<=tail&&(dp[i]-dis[i+1]+d[i+1]<dp[q[tail]]-dis[q[tail]+1]+d[q[tail]+1]))
				tail--;
			q[++tail]=i;		
			//注意在处理掉不合法状态时一定要判断队列是否为空 
		}
		printf("%d\n",dp[n]);
		if(T)putchar('\n');
	}
	return 0;
}
```

---

## 作者：endless_loop (赞：1)

一道很有意思的dp。

首先，这显然是一个线性 dp，状态显然是现在的垃圾编号和从哪个垃圾编号转移得到，在这里我们约定都是由。

于是我们就可以得到一个状态转移方程：

$$dp[i]=\min\limits_{1\le j \le n}\left\{dp[j]+dis(i,j)\right\},\sum^{i}_{k=j}c_k\le C$$

其中 $dis(i,j)$ 表示从编号 $i$ 的垃圾收集到 编号为 $j$ 的垃圾加上从原点到两个垃圾所需的路程。

显然，转移有 $n$ 个，而求出 $i$ 到 $j$ 的路径需要 $O(n)$ 的时间，于是时间复杂度就是 $O(n^3)$。

显然刚才的时间复杂度过不去，而容易想到我们可以用前缀和搞一下，把复杂度变成 $O(n^2)$。

接着我们发现有很多状态是不合法的，因为我们需要满足 $\sum^{i}_{k=j}c_k\le C$ 的条件。

接着我们来看看现在我们的状态转移方程：

$$dp[i]=\min\limits_{1\le j\le n}\left\{d[j]+pre[i]-pre[j+1]+x[i]+y[i]+x[j+1]+y[j+1]\right\}$$

然后我们设
$$A[i]=pre[i]+x[i]+y[i]$$
$$B[i]=d[i]-pre[i+1]+x[i+1]+y[i+1]$$

接着，我们的状态转移方程就可以写成这样
$$dp[i]=\min\limits_{1\le j\le n}\left\{A[i]+B[j]\right\}$$

还有，我们观察到 $c_i$ 都大于 $0$，显然 $i-j$ 越大,$\sum^{i}_{j=k}c_k$ 也会越大。

这时如果有一个 $j$ 值的 $B[j]$ 不仅小，而且离 $i$ 远，那我们一定没有考虑这个决策的必要，这让人自然想到单调队列。

于是我们就可以优化成 $O(n)$ 了，最后注意一下输出格式，每组数据中有空行。

Code：
```cpp
#include<iostream>
using namespace std;
const int maxn=1e5+5;
inline int abs(int x) {
	return x>0?x:-x;
}
int x[maxn],y[maxn],w[maxn],d[maxn],prew[maxn],prep[maxn];
int q[maxn],l,r;
inline int f(int i){return d[i]-prep[i+1]+x[i+1]+y[i+1];}//简化B[i]
int main() {
	int t;
	cin>>t;
	while(t--) {
		int c,n;
		cin>>c>>n;
		for(int i=1; i<=n; ++i) {
			cin>>x[i]>>y[i]>>w[i];
			prep[i]=prep[i-1]+abs(x[i]-x[i-1])+abs(y[i]-y[i-1]);
			prew[i]=prew[i-1]+w[i];
		}
		l=0,r=1;
		for(int i=1; i<=n; ++i) {
			while(l<r&&prew[i]-prew[q[l]]>c)l++;
			int j=q[l];
			d[i]=d[j]+prep[i]-prep[j+1]+x[i]+y[i]+x[j+1]+y[j+1];
			while(l<r&&f(q[r-1])>=f(i))r--;
			q[r++]=i;
		}
		cout<<d[n]<<endl;
		if(t>0)cout<<endl;//注意输出格式
	}
	return 0;
}
```

---

## 作者：Apricot (赞：1)

## Dp+优化

首先我们考虑暴力怎么写？dp[i]表示选到i号辣鸡并将其放回的最优解，那么令dis[i]表示从1走到i的曼哈顿距离之和，from[i]表示从（0，0）走到i的曼哈顿距离，那么

$$dp[i]=min(dp[i],dp[j]+dis[i]-dis[j+1]+from[j+1]+from[i]);$$

$$0<=j<=i-1$$

我们移项：
$$dp[i]=min(dp[i],dp[j]-dis[j+1]+from[j+1]+dis[i]+from[i]);$$

$$0<=j<=i-1$$

显然，$$dp[j]-dis[j+1]+from[j+1]$$ 可以用~~线段树~~单调队列维护。

然后这道题就愉快的结束了~~（我用了线段树）~~

### 注意要换行！！！！
送大家一组样例，~~这组样例卡掉了一个CSDN的标程~~

**in：**
```
5
77
9
9 26 38
38 1 44
26 28 72
38 37 29
2 7 27
14 20 9
21 13 45
25 32 33
10 4 41
17
1
3 1 12
43
3
37 10 36
30 32 31
18 5 13
36
5
14 23 33
2 18 5
33 8 13
6 31 13
13 21 25
76
5
27 2 61
32 41 41
16 37 17
34 40 9
37 26 49

```
**out**
```
602

8

264

290

358

```

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<cstring>
#include<cmath>
#define half (l+r)>>1
using namespace std;
const int maxn=100006;
inline int abs_(int x,int y)
{
    return x>y?x-y:y-x;
}
int x[maxn],y[maxn],w[maxn],from[maxn],cost[maxn],dp[maxn],n,sum[maxn];
struct hzw
{
    int lc,rc,mx;
}t[maxn*5];
int tot;
inline void build(int s,int l,int r)
{
    if(l==r)
    {
        t[s].mx=0x3f3f3f3f;
        return;
    }
    int mid=half;
    t[s].lc=++tot;
    build(tot,l,mid);
    t[s].rc=++tot;
    build(tot,mid+1,r);
}
inline void update(int s,int l,int r,int p,int x)
{
    if (l==p&&r==p)
    {
        t[s].mx=x;
        return;
    }
    int mid=half;
    if (p<=mid) update(t[s].lc,l,mid,p,x);
    else update(t[s].rc,mid+1,r,p,x);
    t[s].mx=min(t[t[s].lc].mx,t[t[s].rc].mx);
}
inline int query(int s,int l,int r,int cl,int cr)
{
    if (l==cl&&r==cr)
    {
        return t[s].mx;
    }
    int mid=half;
    if (cr<=mid) return query(t[s].lc,l,mid,cl,cr);
    else if (cl>mid) return query(t[s].rc,mid+1,r,cl,cr);
    else
    return min(query(t[s].lc,l,mid,cl,mid),
    	       query(t[s].rc,mid+1,r,mid+1,cr));
}
inline int search(int ll,int rr,int k)
{
    int l=ll,r=rr,ans=rr;
    while (l<=r)
    {
        int mid=half;
        if (cost[rr]-cost[mid-1]<=k)
        {
            r=mid-1;
            ans=min(ans,mid);
        }
        else l=mid+1;
    }
    return ans;
}
int main()
{
//	freopen("data.in","r",stdin);
//	freopen("baoli.out","w",stdout);
    int gg,maxx;
    cin>>gg;
    while (gg--)
    {
        memset(dp,0x3f,sizeof(dp));
        tot=1;
        cin>>maxx;
        scanf("%d",&n);
        build(1,0,n);
        for (int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&x[i],&y[i],&w[i]);
            from[i]=x[i]+y[i];
            if (i>1) 
            sum[i]=sum[i-1]+abs_(x[i],x[i-1])+abs_(y[i],y[i-1]);
            cost[i]=cost[i-1]+w[i];
        }
    	dp[0]=0;
    	dp[1]=2*from[1];
		update(1,0,n,0,from[1]);
		update(1,0,n,1,from[2]-sum[2]+dp[1]);
		for (int i=2;i<=n;++i)
		{
			int wh=search(0,i,maxx);
			wh=max(0,wh-1);
			dp[i]=query(1,0,n,wh,i-1)+sum[i]+from[i];
			update(1,0,n,i,from[i+1]-sum[i+1]+dp[i]);
		}
		cout<<dp[n]<<endl;
		if (gg!=0)cout<<endl;
    }
    return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很明显这是一道动规题，还是数据范围很弱的那种。

所以，本题最好用比较朴素 ~~（暴力）~~ 的方法，~~而不是一大堆优化加上来，一不小心代码写崩直接爆零。~~

接下来进入正题。

##### 各种变量

像这种带各种坐标的题目，肯定得定义一大堆数组。

定义 $dp_i$ 为如果只考虑 $1$ 到 $i$ 号包裹的情况下机器人最短要**走多远**。

定义 $sw_i$ 为第 $1$ 到 $i$ 号包裹的**重量之和**，就是用来大大减少时间复杂度的前缀和，

定义 $da_i$ 为第 $i$ 号包裹到第 $i-1$ 号包裹的**最短路径长度**，也就是**曼哈顿距离**。

定义 $sda_i$ 为 $da_i$ 的**前缀和**，也就是 $sda_i=\sum_{j=1}^ida_j$。

定义 $ds_i$ 为第 $i$ 号包裹**到起点的距离**。

##### 实现过程

初始化时 $dp_0$ 肯定设为 $0$。

接下来，从 $1$ 个包裹的情况开始，依次考虑，最后解决 $n$ 个包裹的情况。

机器人可以先送完 $1$ 到 $j$ 号包裹，再送 $j+1$ 到 $i$ 号包裹。那么就有了如下的动规方程：

$$dp_i=\operatorname{min}(dp_j+ds_{j+1}+sda_i-sda_{j+1}+ds_i)(0\le j<i\le n)$$

更清楚些：

$$dp[i]=\operatorname{min}(dp[j]+ds[j+1]+sda[i]-sda[j+1]+ds[i])(0\le j<i\le n)$$

$dp_n$ 即为答案。

### 2 代码与记录

多测不需要清空，难得啊。

```cpp
#include<cstdio>
using namespace std;
#define max_n 100000//最大垃圾数
#define INF 21474837
int t;//测试数据数量
int c;//最大运货重量
int n;//垃圾数量
int dp[max_n+2];//动规数组
int sw[max_n+2];//包裹重量前缀和
int da[max_n+2];//da[i]是第i-1到i号包裹最短距离
int sda[max_n+2];//da的前缀和
int ds[max_n+2];//ds[i]是第i号包裹到起点的距离
inline int absi(int a){return a>0?a:-a;}
inline int mi(int a,int b){return a<b?a:b;}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("UVA01169_1.in","r",stdin);
	freopen("UVA01169_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	dp[0]=sw[0]=sda[0];
	for(int ca=1;ca<=t;++ca){
		scanf("%d%d",&c,&n);
		for(int i=1,x,y,w,nx=0,ny=0;i<=n;++i){
			scanf("%d%d%d",&x,&y,&w);
			sw[i]=sw[i-1]+w;
			da[i]=absi(x-nx)+absi(y-ny);
			sda[i]=sda[i-1]+da[i];
			ds[i]=x+y;
			nx=x;
			ny=y;
			dp[i]=INF;
			for(int j=i-1;j>=0&&sw[i]-sw[j]<=c;--j){
				dp[i]=mi(dp[i],dp[j]+ds[j+1]+sda[i]-sda[j+1]+ds[i]);
			}
		}
		printf("%d\n",dp[n]);
		if(ca<t)printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/53910645)

By **dengziyue**

---

