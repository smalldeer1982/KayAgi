# Animal Observation (hard version)

## 题目描述

The only difference between easy and hard versions is the constraint on $ k $ .

Gildong loves observing animals, so he bought two cameras to take videos of wild animals in a forest. The color of one camera is red, and the other one's color is blue.

Gildong is going to take videos for $ n $ days, starting from day $ 1 $ to day $ n $ . The forest can be divided into $ m $ areas, numbered from $ 1 $ to $ m $ . He'll use the cameras in the following way:

- On every odd day ( $ 1 $ -st, $ 3 $ -rd, $ 5 $ -th, ...), bring the red camera to the forest and record a video for $ 2 $ days.
- On every even day ( $ 2 $ -nd, $ 4 $ -th, $ 6 $ -th, ...), bring the blue camera to the forest and record a video for $ 2 $ days.
- If he starts recording on the $ n $ -th day with one of the cameras, the camera records for only one day.

Each camera can observe $ k $ consecutive areas of the forest. For example, if $ m=5 $ and $ k=3 $ , he can put a camera to observe one of these three ranges of areas for two days: $ [1,3] $ , $ [2,4] $ , and $ [3,5] $ .

Gildong got information about how many animals will be seen in each area on each day. Since he would like to observe as many animals as possible, he wants you to find the best way to place the two cameras for $ n $ days. Note that if the two cameras are observing the same area on the same day, the animals observed in that area are counted only once.

## 说明/提示

The optimal way to observe animals in the four examples are as follows:

Example 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F2/d3d7ccf6369074c42d9cb3c6953ef69b03850081.png)Example 2:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F2/cb62ca568d7dec1d0d903ae38c9fff43fc945cf2.png)Example 3:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F2/3e18878b2213816dafe01bd460999dff35151fc8.png)Example 4:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1304F2/dc814ca536d6cd407d5a49988e0923d5d85a8629.png)

## 样例 #1

### 输入

```
4 5 2
0 2 1 1 0
0 0 3 1 2
1 0 4 3 1
3 3 0 0 4```

### 输出

```
25```

## 样例 #2

### 输入

```
3 3 1
1 2 3
4 5 6
7 8 9```

### 输出

```
31```

## 样例 #3

### 输入

```
3 3 2
1 2 3
4 5 6
7 8 9```

### 输出

```
44```

## 样例 #4

### 输入

```
3 3 3
1 2 3
4 5 6
7 8 9```

### 输出

```
45```

# 题解

## 作者：Alex_Wei (赞：26)

> [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1304F2) & [CF题面传送门](https://www.luogu.com.cn/problem/CF1304F2)

> 题意简述：给定一个 $n\times m$ 的大矩形，在每一行选一个点，以所有选中的点为左上角作一个水平方向长为 $k$，竖直方向长为 $2$ 的小矩形（超出矩阵的范围忽略）。求所有小矩形的并覆盖的数之和的最大值。

~~现在的 Div.2 是越来越水了。~~

- 下文中，我们定义 $d_{i,j}$ 为大矩阵第 $i$ 行，第 $j$ 列的点的值。

---

因为矩阵的值没有负数，所以我们可以明确的一点是，肯定不会选在某一行第 $m-k+1$ 个点的右边。

假设我们第 $i$ 行选的是第 $j(j>m-k+1)$ 个点，那么它对答案的贡献就是 $\sum_{x=j}^n d_{i,x}$，而选在第 $m-k+1$ 个点的贡献是 $\sum_{x=m-k+1}^n d_{i,x}$。因为 $j>m-k+1$，所以前者的贡献不大于后者的贡献，选后者一定更优。

- 下文中，我们设 $g$ 为 $m-k+1$。

---

容易想到一个 DP 方案：设 $f_{i,j}$ 为第 $i$ 行选在第 $j$ 个点时前 $i$ 行覆盖的数的最大值。

如果**相同的格子被覆盖两次算两个贡献**，那么转移方程就很容易出来了：

$$f_{i,j}=\max_{x=1}^g\left(f_{i-1,x}+\sum_{y=x}^{x+k-1}d_{i,y}\right)+\sum_{x=j}^{j+k-1}d_{i,x}$$

目标值为 $\max_{x=1}^g f_{n,x}$。

求和的前缀和预处理一下，求 $\max$ 的也预处理一下，就可以做到 $\mathcal O(1)$ 转移，总时间复杂度 $\mathcal O(nm)$。

- 接下来，我们假设 $pre_{i,j}=f_{i,j}+\sum_{x=j}^{j+k-1}d_{i,x}$。

---

**但是我们要去掉重复计算的部分。** 假设我们当前转移到了第 $i$ 行第 $j$ 列，那么 $d_{i,j},d_{i,j+1},\dots,d_{i,j+k-1}$ 就会对前面 $\max$ 的柿子产生重复贡献。

- 一个点 $d_{i,y}$ 在哪里已经被计算过了？$pre_{i-1,y},pre_{i-1,y-1},\dots,pre_{i-1,y-k+1}$。

  可以看出，计算上面这些的时候已经包含了 $d_{i,y}$，将上面这些 $pre$ 减去 $d_{i,y}$ 就能去掉 $d_{i,y}$ 产生的重复贡献。

这个时候我们需要的就是一个支持区间加减和区间求最大值的数据结构。线段树！

计算 $f_{i,j}$ 的时候，去掉 $d_{i,j},d_{i,j+1},\dots,d_{i,j+k-1}$ 的重复贡献即可。但这样时间复杂度是 $\mathcal O(nmk\log m)$ 的，无法承受。

实际上，从 $f_{i,j-1}$ 移到 $f_{i,j}$ 的过程中，只有两个点的状态改变了：$d_{i,j-1}$ 不再产生重复贡献，$d_{i,j+k-1}$ 开始产生重复贡献。这两个点修改一下即可。时间复杂度 $\mathcal O(nm\log m)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fi first
#define se second
#define pii pair<int,int>

const int N=2e4+5;
int n,m,k,g,d[55][N],dp[55][N],s[55][N]; 
int val[N<<2],laz[N<<2];
void build(int day,int l,int r,int x){
	if(l==r){
		val[x]=dp[day][l]+s[day+1][l+k-1]-s[day+1][l-1];
		return;
	}
	int m=l+r>>1;
	build(day,l,m,x<<1);
	build(day,m+1,r,x<<1|1);
	val[x]=max(val[x<<1],val[x<<1|1]);
}
void push(int x){
	if(laz[x]){
		val[x<<1]+=laz[x];
		val[x<<1|1]+=laz[x];
		laz[x<<1]+=laz[x];
		laz[x<<1|1]+=laz[x];
		laz[x]=0;
	}
}
void modify(int l,int r,int ql,int qr,int x,int v){
	if(ql<=l&&r<=qr){
		val[x]+=v;
		laz[x]+=v;
		return;
	}
	int m=l+r>>1;
	push(x);
	if(ql<=m)modify(l,m,ql,qr,x<<1,v);
	if(m<qr)modify(m+1,r,ql,qr,x<<1|1,v);
	val[x]=max(val[x<<1],val[x<<1|1]);
}
void add(int day,int pos){//计算重复贡献
	if(pos)modify(1,g,max(1,pos-k+1),min(g,pos),1,-d[day][pos]);
}
void del(int day,int pos){//不再产生重复贡献
	if(pos)modify(1,g,max(1,pos-k+1),min(g,pos),1,d[day][pos]);
}
int main(){
	cin>>n>>m>>k,g=m-k+1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&d[i][j]),s[i][j]=s[i][j-1]+d[i][j];//s是一行的前缀和
	for(int i=1;i<=n;i++){
		if(i>1)for(int j=1;j<k;j++)add(i,j);//计算重复贡献
		for(int j=1;j+k-1<=m;j++){
			int l=j,r=j+k-1;
			if(i==1)dp[1][j]=s[1][r]-s[1][l-1];
			else del(i,l-1),add(i,r),dp[i][j]=s[i][r]-s[i][l-1]+val[1];
		}
		memset(val,0,sizeof(val));
		memset(laz,0,sizeof(laz));//数组不清空，爆零两行泪！
		if(i<n)build(i,1,g,1);
	}
	int ans=0;
	for(int i=1;i<=g;i++)ans=max(ans,dp[n][i]);
	cout<<ans<<endl;
    return 0;
}
```

码字不易，点个赞呗 awa。

---

## 作者：wucstdio (赞：8)

不得不说打这一场是真的爽……

这道题我写的是 $O(nm\log m)$ 的线段树解法，但是好像还有单调队列的 $O(nm)$ 解法。

### 题目大意

给你一个 $n\times m$ 的矩形，每一个格子里面有一个数字，你可以在每一行里选择一个 $2\times k$ 的矩形（这个矩形跨越两行），要求最后所有你选择的矩形的并的权值和最大。

### 数据范围

$1\le n\le 50,1\le m\le 20000$

### 解题过程

首先我们注意到可以 DP。

设 $f_{i,j}$ 表示处理完了前 $i-1$ 行，其中第 $i-1$ 行选择的区间是 $[j,j+k-1]$，当前覆盖的格子的最大权值。

令 $S_{i,j}=\sum_{k=1}^ja_{i,k}$，枚举当前行选择的区间，我们可以得到转移方程：

$$g_{i,j}=\max_{l}\begin{cases}f_{i-1,l}-(S_{i,l+k-1}-S_{i,j-1})&\text{if $l\in [j-k,j]$}\\f_{i-1,l}-(S_{i,j+k-1}-S_{i,l-1})&\text{if $l\in [j,j+k]$}\\f_{i-1,l}&\text{otherwise}\end{cases}$$

$$f_{i,j}=g_{i,j}+S_{i,j+k-1}-S_{i,j-1}+S_{i+1,j+k-1}-S_{i+1,j-1}$$

也就是减去重复的再加上新覆盖的。直接转移是 $O(nm^2)$ 的。

我们设 $x_{i,j}=f_{i,j}-S_{i,j+k-1}$,$y_{i,j}=f_{i,j}+S_{i,j-1}$，则上式变为：

$$g_{i,j}=\max_{l}\begin{cases}x_{i-1,l}+S_{i,j-1}&\text{if $l\in [j-k,j]$}\\y_{i-1,l}-S_{i,j+k-1}&\text{if $l\in [j,j+k]$}\\f_{i-1,l}&\text{otherwise}\end{cases}$$

我们需要维护出 $x,y,f$ 三个数组，实现单点修改和区间取 $\max$，可以用线段树轻松实现。

时间复杂度为 $O(nm\log m)$。

### 代码

注意代码里面的 $k$ 和 $l$ 与题目中的 $k$ 和 $l$ 意义是相反的。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define lc x<<1//相比之前我现在的码风发生了一些微小的改变
#define rc x<<1|1
#define mid ((l+r)>>1)
using namespace std;
struct Tree//线段树
{
	ll maxv[80005];
	void pushup(int x)
	{
		maxv[x]=max(maxv[lc],maxv[rc]);
	}
	void update(int x,int l,int r,int p,ll v)
	{
		if(l==r)
		{
			maxv[x]=v;
			return;
		}
		if(p<=mid)update(lc,l,mid,p,v);
		else update(rc,mid+1,r,p,v);
		pushup(x);
	}
	ll ask(int x,int l,int r,int from,int to)
	{
		if(from>to)return -1e12;
		if(l>=from&&r<=to)return maxv[x];
		ll ans=-1e12;
		if(from<=mid)ans=max(ans,ask(lc,l,mid,from,to));
		if(to>mid)ans=max(ans,ask(rc,mid+1,r,from,to));
		return ans;
	}
};
Tree t1,t2,t3;//t1,t2,t3分别维护f,x,y
int n,m,l;
ll a[55][20005],s[55][20005],f[20005];
int main()
{
	scanf("%d%d%d",&n,&m,&l);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    scanf("%lld",&a[i][j]);
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    s[i][j]=s[i][j-1]+a[i][j];
	for(int i=1;i<=80000;i++)
	  t1.maxv[i]=t2.maxv[i]=t3.maxv[i]=-1e12;//注意初值
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j+l-1<=m;j++)
		{
			f[j]=max(t1.ask(1,1,m,1,j-l),t1.ask(1,1,m,j+l,m));//case 1
			f[j]=max(f[j],t2.ask(1,1,m,j-l+1,j)+s[i][j-1]);//case 2
			f[j]=max(f[j],t3.ask(1,1,m,j+1,j+l)-s[i][j+l-1]);//case 3
			f[j]=max(f[j],0ll);
		}
		for(int j=1;j+l-1<=m;j++)
		{
			f[j]=f[j]+s[i][j+l-1]-s[i][j-1]+s[i+1][j+l-1]-s[i+1][j-1];
			t1.update(1,1,m,j,f[j]);
			t2.update(1,1,m,j,f[j]-s[i+1][j+l-1]);
			t3.update(1,1,m,j,f[j]+s[i+1][j-1]);//单点修改
		}
	}
	printf("%lld\n",t1.ask(1,1,n,1,n));
	return 0;
}
```

---

## 作者：beacon_cwk (赞：6)

~~被抢先了？？？~~

补一个单调队列的做法。如果你不会的话，先去了解一下。

首先，设 $w_{i,j}$ 表示第$i$行第$j$个格子的值；设 $dp_{i,j}$ 表示考虑到第 $i$ 行，上一行选的左端点是 $j$
 ，**且不考虑第 $i+1$ 行被覆盖的格子**时的最大值。

$dp_{i,j} = max(dp_{i-1,a}+gsum(i,a,a+k-1)+gsum(i,j,j+k-1)-dec)$

其中， $gsum(i,l,r)$ 表示第 $i$ 行里第 $l$ 至第 $r$ 个元素的和， $dec$ 是重叠部分。

直接转移是 $O(m^2n)$ 的。然而，可以发现，k很小时，很多转移都是无用的。


对于所有的 $a < max(1,j-k+1) $ 和 $a > min(j+k-1,m-k+1)$ ，都没有重叠部分，所以维护前缀与后缀最大值，把这两部分优化成 $O(1)$ ，再枚举所有 
$max(1,j-k+1) \leq a \leq min(j+k-1,m-k+1)$
转移。复杂度 $O(nmk)$ 可以过 F1 。

F2 怎么搞呢？

先把 $ gsum(i,a,a+k-1)+gsum(i,j,j+k-1)-dec $ 这个东西转化一下。为了方便，把它叫做 $add$ 。

看这个图。

![](https://cdn.luogu.com.cn/upload/image_hosting/7sp43865.png)

棕色和绿色的线段是增加权值的范围。棕色的$a \leq k$，绿色的$a \geq k$。

这里把它拆成两部分：$a \leq j$ ， 和 $a \geq j$，先允许它们重叠。

观察一下：

$$ add=\left\{
\begin{array}{rcl}
gsum (i,a,j+k-1)       &      & {a     \leq      j}\\
gsum (i,j,a+k-1)     &      & {a \geq j}\\
\end{array} \right. $$

转移时，把第一种和第二种拆开来。

在优化前，先来看看当$j$增加$1$时，这些值的变化。（下文的$j$是原来未增加的）

对于 $a \leq j$，它的 $add$ 增加了 $w_{i,j+k}$，同时可选的状态里， $a = j - k + 1$ 被移除了，$a = j + 1$ 被加进来；对于$a \geq j$，它的 $add$ 减少了 $w_{i,j}$，同时可选的状态里， $a = j$ 被移除了，$a = j + k$ 被加进来。由于所有这些$add$都是同时增加，同时减少，**相对大小关系不会变**。这些在图上画一画可能会帮助理解。

于是就可以单调队列优化。开两个队列，对应着两种转移。入队时对于队尾 $x$ 和进入的元素 $y$（$x$ 和 $y$ 是下标），比较 $dp_{i-1,x}+add_x$ 与 $dp_{i-1,y}+add_y$ 。

时间复杂度 $O(nm)$ ~~但是只比log的快了一点点？~~

代码：

```cpp
//注意有些实现可能略微不同
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mit map<int,int>::iterator
#define sit set<int>::iterator
#define itrm(g,x) for(mit g=x.begin();g!=x.end();g++)
#define itrs(g,x) for(sit g=x.begin();g!=x.end();g++)
#define ltype int
#define rep(i,j,k) for(ltype(i)=(j);(i)<=(k);(i)++)
#define rap(i,j,k) for(ltype(i)=(j);(i)<(k);(i)++)
#define per(i,j,k) for(ltype(i)=(j);(i)>=(k);(i)--)
#define pii pair<int,int>
#define fi first
#define se second
#define mpr make_pair
#define pb push_back
#define fastio ios::sync_with_stdio(false)
const int inf=0x3f3f3f3f,mod=1000000007;
const double pi=3.1415926535897932,eps=1e-6;
int m,n,a[55][20005],pre[20005],suf[20005],dp[55][20005],k,sum[55][20005],val[55][20005];
int gsum(int x,int l,int r){return sum[x][r]-sum[x][l-1];}
int q1[20010],q2[20010],l1,l2,r1,r2;
void push1(int x,int y,int z){
    while(dp[z-1][x] + gsum(z,x,y) >dp[z-1][q1[r1]] + gsum(z,q1[r1],y) && r1 >= l1) r1--;
    q1[++r1] = x;
}
void pop1(int x){
    while(q1[l1] <= x && r1 >= l1) l1++;
}
void push2(int x,int y,int z){
    while(dp[z-1][x] + gsum(z,y,x + k - 1) >dp[z-1][q2[r2]] + gsum(z,y,q2[r2] + k - 1) && r2 >= l2) r2--;
    q2[++r2] = x;
}
void pop2(int x){
    while(q2[l2] <= x && r2 >= l2) l2++;
}//注意这两个pop，是把所有下标小于等于x的弹出
void upd(int x){
    rep(i,1,m - k + 1) pre[i]=suf[i]=0;
    rep(i,1,m - k + 1) pre[i]=max(pre[i-1],dp[x][i] + val[x+1][i]);
    per(i,m - k + 1,1) suf[i]=max(suf[i+1],dp[x][i] + val[x+1][i]);
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    rep(i,1,n) rep(j,1,m) {scanf("%d",&a[i][j]);sum[i][j] = sum[i][j-1] + a[i][j];}
    rep(i,1,n) rep(j,1,m - k + 1) val[i][j] = gsum(i, j, j + k - 1);//val[i][j]第i行以第j个元素开始，长度为k的连续段的w值总和
    //dp[i][j] 考虑到第i行，且暂时不考虑第(i+1)行的最大值
    rep(j,1,m - k + 1) dp[1][j] = val[1][j];
    upd(1);
    rep(i,2,n){
        l1 = l2 = 2;r1 = r2 = 1;//清空
        int lst = 0,lst2 = 0;//用来增加状态
        rep(j,1,m - k + 1){
            int rr = j + k - 1;
            int l = max(1,j - k + 1), r = min(m - k + 1,j + k - 1), v=val[i][j];
            pop1(l - 1);
            pop2(j - 1);//这两个用来弹出已经不能转移的状态，注意我的出队写的有点奇怪
            rep(a,lst+1,r) push2(a, j, i);
            lst = r;
            rep(a,lst2+1,j) push1(a, rr, i);
            lst2 = j;// 新状态入队，上面的a覆盖了外面的那个数组
            dp[i][j] = max(pre[l - 1],suf[r + 1]) + v;// 第0种，无重叠部分的
            int fr1 = q1[l1], fr2 = q2[l2];
            dp[i][j] = max(dp[i][j], max(dp[i-1][fr1] + gsum(i,fr1,rr), dp[i-1][fr2] + gsum(i,j,fr2 + k - 1)));//第1种与第2种写在一起了
        }
        if(i < n) upd(i);//更新前后缀最大值
    }
    int ans=0;
    rep(i,1,m - k + 1) ans=max(ans, dp[n][i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：dblark (赞：5)

[easy version 的题解](https://www.luogu.com.cn/blog/dblark/solution-cf1304f1)

Hard version $ k $ 的范围变大了，说明在 $ j - k + 1 \leq l \leq j + k - 1 $ 情况下的转移还可以继续优化。

当 $ j - k + 1 \leq l \leq j $ 时，$ \text{max} \{ f_{i - 1, l} + sum_{i, j + k - 1} - sum_{i, l + k - 1} \} $ 仅与 $ f_{i - 1, l} - sum_{i, l + k - 1} $ 有关。再观察可得 $ l $ 的范围是滑动的。因此我们可以用单调队列来维护这个值。当 $ j + 1 \leq l \leq j + k - 1 $ 时同理。

时间复杂度 $ O(n m) $。

```cpp
#include <cstdio>
#include <deque>
#include <algorithm>
#include <utility>
#define N 55
#define M 20005

int n, m, k;
int a[N][M], sum[N][M], f[N][M], pre[M], suf[M];
std::deque<std::pair<int, int> > q1, q2;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            scanf("%d", &a[i][j]);
            sum[i][j] = sum[i][j - 1] + a[i][j];
        }
    for (int i = 1; i <= m - k + 1; ++i) f[1][i] = sum[1][i + k - 1] - sum[1][i - 1] + sum[2][i + k - 1] - sum[2][i - 1];
    for (int i = m - k + 1; i; --i) suf[i] = std::max(suf[i + 1], f[1][i]);
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m - k + 1; ++j) pre[j] = std::max(pre[j - 1], f[i - 1][j]);
        for (int j = m - k + 1; j; --j) suf[j] = std::max(suf[j + 1], f[i - 1][j]);
        q1.clear(), q2.clear();
        for (int j = 1; j <= std::min(k - 1, m - k + 1); ++j) {
            while (!q2.empty() && f[i - 1][j] + sum[i][j - 1] >= q2.back().second) q2.pop_back();
            q2.push_back(std::make_pair(j, f[i - 1][j] + sum[i][j - 1]));
        }
        for (int j = 1; j <= m - k + 1; ++j) {
            f[i][j] = std::max(j > k ? pre[j - k] : 0, j + k <= m - k + 1 ? suf[j + k] : 0) + sum[i][j + k - 1] - sum[i][j - 1];
            while (!q1.empty() && f[i - 1][j] - sum[i][j + k - 1] >= q1.back().second) q1.pop_back();
            q1.push_back(std::make_pair(j, f[i - 1][j] - sum[i][j + k - 1]));
            while (!q1.empty() && q1.front().first <= j - k) q1.pop_front();
            f[i][j] = std::max(f[i][j], q1.front().second + sum[i][j + k - 1]);
            if (j + k - 1 <= m - k + 1) {
                while (!q2.empty() && f[i - 1][j + k - 1] + sum[i][j + k - 2] >= q2.back().second) q2.pop_back();
                q2.push_back(std::make_pair(j + k - 1, f[i - 1][j + k - 1] + sum[i][j + k - 2]));
            }
            while (!q2.empty() && q2.front().first <= j) q2.pop_front();
            if (!q2.empty()) f[i][j] = std::max(f[i][j], q2.front().second - sum[i][j - 1]);
            f[i][j] += sum[i + 1][j + k - 1] - sum[i + 1][j - 1];
        }
    }
    int ans = 0;
    for (int i = 1; i <= m - k + 1; ++i) ans = std::max(ans, f[n][i]);
    printf("%d\n", ans);
}
```

---

## 作者：Fido_Puppy (赞：3)

$$\texttt{Foreword}$$

第一次在模拟赛中打出 T4。

$$\texttt{Description}$$

[CF1304F2 Animal Observation (hard version)](https://www.luogu.com.cn/problem/CF1304F2)

给定一个 $n \times m$ 的网格和一个整数 $k$，网格上每个位置有一个数字 $a_{i,j} (1 \le i \le n, 1 \le j \le m)$。

对于所有 $i \in [1, n]$，你可以指定一个区间 $[l, r](1 \le l \le r \le m, r - l + 1 \le k)$，然后将所有 $a_{x,y}(i \le x \le \min(n, i + 1), l \le y \le r)$ 覆盖一次。

你需要求出，对于所有指定区间的方案，被覆盖的所有数的和的最大值是多少。在本题中，一个数字如果被覆盖多次，这个数字也只会被计算一次。

$$\texttt{Solution}$$

首先考虑到 $a_{i,j} \ge 0(i \in [1,n],j \in [1,m])$，所以我们在一行中选多肯定是比选少优的。

所以我们可以考虑动态规划，定义状态 $f_{i,j}$ 表示第 $i$ 行选择了区间 $[j, j + k - 1]$ 所被覆盖的数的和的最大值。

我们直接暴力转移，时间复杂度为 $\mathcal{O(nm^2)}$，无法承受。

所以我们首先把状态转移方程写出来，观察是否能够优化。

假设上一次我们选择的区间为 $[last, last + k - 1]$，

这一次选择的区间为 $[j, j + k - 1]$。

$$sum_{i,j} = \sum_{k = 1}^{j}a_{i,k}$$

设 $cnt = sum_{i + 1,j+k-1} - sum_{i + 1,j - 1}$，表示下一行中选的数的和。

+ $\text{Situation One}$

上一次选择的区间与这一次选择的有交集，且上一次选择的区间在前面。

条件：

$last + k - 1 \ge j$ 并且 $last \le j$。

$j - k + 1 \le last \le j$

$$f_{i,j} = f_{i-1, last} + sum_{i,j+k-1}-sum_{i,j-1}-(sum_{i,last+k-1}-sum_{i,j-1})+cnt$$

$$f_{i,j} = f_{i-1, last} + sum_{i,j+k-1} - sum_{i,last+k-1}+cnt$$

$$f_{i,j} = (f_{i-1, last} - sum_{i,last+k-1}) + sum_{i,j+k-1}+cnt$$

所以我们只需要在区间 $[\max(1,j-k+1),j]$ 中查询 $f_{i-1,last}-sum_{i,last+k-1}$ 的最大值即可，可以用线段树维护。

+ $\text{Situation Two}$

上一次选择的区间与这一次选择的有交集，且上一次选择的区间在后面。

条件：

$last \le j+k-1$ 并且 $last \ge j$。

$j \le last \le j+k-1$

$$f_{i,j} = f_{i-1, last} + sum_{i,j+k-1}-sum_{i,j-1}-(sum_{i,j+k-1}-sum_{i,last-1})+cnt$$

$$f_{i,j} = f_{i-1, last} - sum_{i,j-1} + sum_{i,last-1}+cnt$$

$$f_{i,j} = (f_{i-1, last} + sum_{i,last-1}) - sum_{i,j-1}+cnt$$

所以我们只需要在区间 $[j,\min(m,j+k-1)]$ 中查询 $f_{i-1,last}+sum_{i,last-1}$ 的最大值即可，可以用线段树维护。

+ $\text{Situation Three}$

上一次选择的区间与这一次选择的没有交集。

条件：

$last + k - 1 < j$ 或者 $last > j + k - 1$

所以 $last \le j - k$ 或者 $last \ge j + k$。

$$f_{i,j} = f_{i - 1, last} + sum_{i,j+k-1}-sum_{i,j-1}+cnt$$

所以我们只需要在区间 $[1,j-k]$ 和 $[j+k,m]$ 中查询 $f_{i-1,last}$ 的最大值即可，可以用线段树维护。

$$\texttt{Summary}$$

开三棵线段树进行维护，时间复杂度 $\mathcal{O(nm\log m)}$。

注意一些细节。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

using namespace std;

const int inf = 2e9;

inline int read() {
	int res = 0; char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) res = (res << 1) + (res << 3) + (c ^ '0'), c = getchar();
	return res;
}

int f[51][20001], a[51][20001], sum[51][20001];
int n, m, k;

struct SegmentTree {
	struct Node {
		int l, r, Max;
	}t[ 20001 << 2 ];
	void build(int p, int l, int r, int x, int opt) {
		t[p].l = l; t[p].r = r;
		if (l == r) {
			if (opt == 1) {
				t[p].Max = f[x][l] - sum[ x + 1 ][ min(l + k - 1, m) ];
			}
			else if (opt == 2) {
				t[p].Max = f[x][l] + sum[ x + 1 ][ l - 1 ];
			}
			else if (opt == 3) {
				t[p].Max = f[x][l];
			}
			return ;
		}
		int mid = l + r >> 1;
		build(p << 1, l, mid, x, opt); build(p << 1 | 1, mid + 1, r, x, opt);
		t[p].Max = max(t[ p << 1 ].Max, t[ p << 1 | 1 ].Max);
	}
	int query(int p, int x, int y) {
		if (x > y) return -inf;
		if (t[p].l >= x && t[p].r <= y) return t[p].Max;
		int ans = -inf, mid = t[p].l + t[p].r >> 1;
		if (x <= mid) ans = max(ans, query(p << 1, x, y));
		if (mid < y) ans = max(ans, query(p << 1 | 1, x, y));
		return ans;
	}
}T1, T2, T3;

signed main() {
	n = read(); m = read(); k = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			a[i][j] = read();
			sum[i][j] = sum[i][ j - 1 ] + a[i][j];
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) f[i][j] = -inf;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i == 1) {
				f[i][j] = sum[1][ min(m, j + k - 1) ] - sum[1][ j - 1 ] + sum[2][ min(m, j + k - 1) ] - sum[2][ j - 1 ];
			}
			else {
				f[i][j] = max(f[i][j], T1.query(1, max(1, j - k + 1), j) + sum[i][ min(m, j + k - 1) ]);
				f[i][j] = max(f[i][j], T2.query(1, j, min(j + k - 1, m)) - sum[i][ j - 1 ]);
				f[i][j] = max(f[i][j], max(T3.query(1, 1, j - k), T3.query(1, j + k, m)) + sum[i][ min(m, j + k - 1) ] - sum[i][ j - 1 ]);
				if (i != n) f[i][j] += sum[ i + 1 ][ min(m, j + k - 1) ] - sum[ i + 1 ][ j - 1 ];
			}
		}
		if (i != n) {	
			T1.build(1, 1, m, i, 1);
			T2.build(1, 1, m, i, 2);
			T3.build(1, 1, m, i, 3);
		}
	}
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		ans = max(ans, f[n][i]);
	}
	printf("%lld\n", ans);
	return 0;
}
```
$$\texttt{Thanks for watching!}$$

---

## 作者：XenonKnight (赞：3)

[easy 题目链接](https://codeforces.ml/contest/1304/problem/F1) & [hard 题目链接](https://codeforces.ml/contest/1304/problem/F2)

> 给出一张 $n \times m$ 的矩阵，每个格子上面有一个数，你要在每行选出一个点 $(i,t)$，并覆盖左上角为 $(i,t)$，右下角为 $(\min(i+1,n),\min(t+k-1,m))$ 的矩形。求被覆盖的格子上数的和的最大值。

> easy 数据范围：$1 \leq n \leq 50$，$1 \leq m \leq 2 \times 10^4$，$1 \leq k \leq 20$。

> hard 数据范围：$1 \leq n \leq 50$，$1 \leq m \leq 2 \times 10^4$，$1 \leq k \leq m$。

楼下单调队列题解写得真好，可惜对单调队列部分的讲解不够详细，这里提供详细讲解。

首先可以想到 $dp$。发现第 $i$ 行对答案的贡献只与第 $i$ 行与第 $i-1$ 行的贡献有关，因此设 $dp_{i,j}$ 为扫到第 $i$ 行，第 $i$ 行选择的数是 $j$，前 $i$ 行被覆盖的数的最大和。

很显然可以枚举上一行填的数 $l$。那么可以得到状态方程：
- $dp_{i,j}=dp_{i-1,l}+\sum\limits_{t=l}^{\min(l+k-1,m)}a_{i,t}+\sum\limits_{t=l}^{\min(j+k-1,m)}a_{i,t}\ \ \ (l \leq j-k\ \ \operatorname{or}\ \ l \geq j+k)$
- $dp_{i,j}=dp_{i-1,l}+\sum\limits_{t=l}^{\min(j+k-1,m)}a_{i,t}\ \ \ (j-k \le l \le j)$
- $dp_{i,j}=dp_{i-1,l}+\sum\limits_{t=j}^{\min(l+k-1,m)}a_{i,t}\ \ \ (j \leq l \le j+k)$

里面的 $\sum$ 可以预处理单行的前缀和 $s_{i,j}$，$\mathcal O(1)$ 求出。

这个算法是 $\mathcal O(nm^2)$ 的，朴素转移会 TLE。

不过发现第一种情况可以记录前缀后缀 $dp_{i-1,j}+\sum\limits_{t=l}^{\min(l+k-1,m)}a_{i,t}+\sum\limits_{t=l}^{\min(j+k-1,m)}a_{i,t}$ 中的最大值，第一种情况就可以 $\mathcal O(1)$ 转移了。F1 就被我们搞掉了。

对于 F2，很显然要 $dp$ 优化，看到这种决策变量在一个区间中的，可以想到线段树/单调队列优化。这里讲单调队列优化。

以第二种情况为例，将原来的式子转化为：$dp_{i-1,l}+s_{i,\min(j+k-1,m)}-s_{i,l-1}$。

拆成两部分，一部分与 $l$ 有关，一部分与 $j$ 有关，即 $(s_{i,\min(j+k-1,m)})+(dp_{i-1,j}-s_{i,l-1})$。

用单调队列维护 $(dp_{i-1,j}-s_{i,l-1})$ 的最大值，可以做到均摊 $\mathcal O(1)$ 的时间复杂度。

第三种情况也类似，原式可化为 $dp_{i-1,l}+s_{i,min(l+k-1,m)}-s_{i,j-1}$

还是拆成两部分，$-s_{i,j-1}+(dp_{i-1,l}+s_{i,min(l+k-1,m))}$

单调队列维护 $(dp_{i-1,l}+s_{i,min(l+k-1,m)})$ 的最大值。注意此处要倒序枚举。

最后求 $\max dp_{n,i}$ 就可以了。

F1：
```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read(),k=read(),a[55][20005],sum[55][20005],dp[55][20005],mxp[55][20005],mxs[55][20005];
signed main(){
	fz(i,1,n)	fz(j,1,m)	a[i][j]=read(),sum[i][j]=sum[i][j-1]+a[i][j];
	fz(i,1,m)	dp[1][i]=sum[1][min(i+k-1,m)]-sum[1][i-1];
	fz(i,1,m)	mxp[1][i]=max(mxp[1][i-1],dp[1][i]+sum[2][min(i+k-1,m)]-sum[2][i-1]);
	fd(i,m,1)	mxs[1][i]=max(mxs[1][i+1],dp[1][i]+sum[2][min(i+k-1,m)]-sum[2][i-1]);
	fz(i,2,n){
		fz(j,1,m){
			if(j+k<=m)	dp[i][j]=max(dp[i][j],mxs[i-1][j+k]+sum[i][j+k-1]-sum[i][j-1]);
			if(j-k>=1)	dp[i][j]=max(dp[i][j],mxp[i-1][j-k]+sum[i][j+k-1]-sum[i][j-1]);
			fz(l,max(j-k+1,1ll),min(j+k-1,m)){
				dp[i][j]=max(dp[i][j],dp[i-1][l]+sum[i][min(max(j+k-1,l+k-1),m)]-sum[i][min(j,l)-1]);
			}
//			cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
		}
		fz(j,1,m)	mxp[i][j]=max(mxp[i][j-1],dp[i][j]+sum[i+1][min(j+k-1,m)]-sum[i+1][j-1]);
		fd(j,m,1)	mxs[i][j]=max(mxs[i][j+1],dp[i][j]+sum[i+1][min(j+k-1,m)]-sum[i+1][j-1]);
	}
	int ans=0;
	fz(i,1,m) ans=max(ans,dp[n][i]);
	cout<<ans<<endl;
	return 0;
}
```

F2：
```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read(),k=read(),a[55][20005],sum[55][20005],dp[55][20005],mxp[55][20005],mxs[55][20005];
int rit(int x){
	return ((x+k-1)>m)?(m):(x+k-1);
}
signed main(){
	fz(i,1,n)	fz(j,1,m)	a[i][j]=read(),sum[i][j]=sum[i][j-1]+a[i][j];
	fz(i,1,m)	dp[1][i]=sum[1][min(i+k-1,m)]-sum[1][i-1];
	fz(i,1,m)	mxp[1][i]=max(mxp[1][i-1],dp[1][i]+sum[2][min(i+k-1,m)]-sum[2][i-1]);
	fd(i,m,1)	mxs[1][i]=max(mxs[1][i+1],dp[1][i]+sum[2][min(i+k-1,m)]-sum[2][i-1]);
	fz(i,2,n){
		deque<pii> q1,q2;
		fz(j,1,m){
			if(j+k<=m)	dp[i][j]=max(dp[i][j],mxs[i-1][j+k]+sum[i][rit(j)]-sum[i][j-1]);
			if(j-k>=1)	dp[i][j]=max(dp[i][j],mxp[i-1][j-k]+sum[i][rit(j)]-sum[i][j-1]);
//			fz(l,max(j-k+1,1ll),min(j+k-1,m)){
//				dp[i][j]=max(dp[i][j],dp[i-1][l]+sum[i][min(max(j+k-1,l+k-1),m)]-sum[i][min(j,l)-1]);
//			}
//			cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
		}
		fz(j,1,m){
			while(!q1.empty()&&q1.front().se<=j-k)	q1.pop_front();
			if(!q1.empty())	dp[i][j]=max(dp[i][j],q1.front().fi+sum[i][rit(j)]);
			while(!q1.empty()&&dp[i-1][j]-sum[i][j-1]>q1.back().fi)	q1.pop_back();
			q1.push_back({dp[i-1][j]-sum[i][j-1],j});
		}
		fd(j,m,1){
			while(!q2.empty()&&q2.front().se>=j+k)	q2.pop_front();
			while(!q2.empty()&&dp[i-1][j]+sum[i][rit(j)]>q2.back().fi)	q2.pop_back();
			q2.push_back({dp[i-1][j]+sum[i][rit(j)],j});
			dp[i][j]=max(dp[i][j],q2.front().fi-sum[i][j-1]);
		}
//		fz(j,1,m){
//			cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
//		}
		fz(j,1,m)	mxp[i][j]=max(mxp[i][j-1],dp[i][j]+sum[i+1][min(j+k-1,m)]-sum[i+1][j-1]);
		fd(j,m,1)	mxs[i][j]=max(mxs[i][j+1],dp[i][j]+sum[i+1][min(j+k-1,m)]-sum[i+1][j-1]);
	}
	int ans=0;
	fz(i,1,m) ans=max(ans,dp[n][i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：wrzSama (赞：1)

## 题目大意

Gildong 计划拍摄森林中的野生动物们。森林被划分为 $m$ 个地区，依次编号为 $1$ 到 $m$，他的拍摄计划持续 $n$ 天。
每一天，他会选择森林中连续的 $k$ 个地区，并且录一段长为 $2$ 天的录像。（如果是最后一天，那就录一段长度为 $1$ 天的录像）这样所有在这两天之内在这 $k$ 个地区中出现过的动物都会被拍摄到。他知道未来 $n$ 天内每一天每一个地区会出现多少野生动物。他想拍摄下尽可能多的野生动物。注意如果一个动物被拍摄了两次，那么只会被计算一次。你的任务是求出拍摄到的动物数量的最大值。

## 思路

设 $dp_{i,j}$ 表示前 $i$ 天第 $i$ 天拍摄 $[j-k+1,j]$ 的地区能拍摄到的最大动物数量，则$dp_{i,j}=max(dp_{i-1,k})+s_{i,j}-s_{i,j-k}+s_{i+1,j}-s_{i+1,j-k}$，$s_{i,j}$ 表示第 $i$ 天前 $j$ 个地区的动物总数量。因为第 $i$ 天拍摄可能会和第 $i-1$ 天拍摄有重复拍摄的部分，所以在转移得到 $dp_{i,j}$ 前要先将第 $i-1$ 天的 $dp$ 值减去其与第 $i-1$ 天和第 $i$ 天拍摄重复的地区。具体的，在第 $i$ 天中从小到大枚举 $j$，每次令第 $i-1$ 天中得 $[j,j+k-1]$ 的 $dp$ 值减去 $a_{i,j}$，再令 $[j-k,j-1]$ 的 $dp$ 值加上 $a_{i,j-k}$，$a_{i,j}$ 为第 $i$ 天第 $j$ 个地区的动物数量。用线段树来维护第 $i-1$ 天中 $dp$ 值的最大值，$dp_{i,j}$ 就可以从这个值转移。最后输出第 $n$ 天的 $dp$ 值的最大值作为答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,m,k,s[55][20005],dp[20005],tr[80005],lz[80005],ans;
void update(int o,int l,int r,int x,int y,int k)
{
	if(x<=l&&r<=y)
	{
		tr[o]+=k;
		lz[o]+=k;
		return;
	}
	int mid=(l+r)>>1;
	if(lz[o])
	{
		tr[o<<1]+=lz[o];
		lz[o<<1]+=lz[o];
		tr[o<<1|1]+=lz[o];
		lz[o<<1|1]+=lz[o];
		lz[o]=0;
	}
	if(x<=mid) update(o<<1,l,mid,x,y,k);
	if(y>mid) update(o<<1|1,mid+1,r,x,y,k);
	tr[o]=max(tr[o<<1],tr[o<<1|1]);
}
void build(int o,int l,int r)
{
	lz[o]=0;
	if(l==r)
	{
		tr[o]=dp[l];
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	tr[o]=max(tr[o<<1],tr[o<<1|1]);
}
int main()
{
	n=read();
	m=read();
	k=read();
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) s[i][j]=s[i][j-1]+read();
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			if(i==1)
			{
				dp[j]=s[i][j]-s[i][max(0,j-k)];
				if(i<n) dp[j]+=s[i+1][j]-s[i+1][max(0,j-k)];
				else ans=max(ans,dp[j]);
				continue;
			}
			update(1,1,m,j,min(m,j+k-1),s[i][j-1]-s[i][j]);
			if(j>k) update(1,1,m,j-k,j-1,s[i][j-k]-s[i][j-k-1]);
			dp[j]=tr[1]+s[i][j]-s[i][max(0,j-k)];
			if(i<n) dp[j]+=s[i+1][j]-s[i+1][max(0,j-k)];
			else ans=max(ans,dp[j]);
		}
		build(1,1,m);
	}
	write(ans);
	return 0;
}
```


---

## 作者：intel_core (赞：1)

先胡一个比较 `naive` 的做法：

先记 $s_i[l,r]$ 表示第 $i$ 行 $[l,r]$ 位置的数的和。

* $f_{i,j}$ 表示考虑到第 $i$ 行，且第 $i$ 行选的矩形的左边界是 $j$ 的最大值。

* 转移的时候从 $f_{i-1,p}$，直接 $f_{i,j}=f_{i-1,p}+s_i[p,p+k-1] \bigcup [j,j+k-1]$，讨论 $[p,p+k-1]$ 与 $[j,j+k-1]$ 是否相交即可。

复杂度 $O(nm^2)$，差点意思。

由于 $k \le 20$，所以一个区间至多与 $40$ 个区间相交，不相交的情况浪费了大量转移时间。

只需要处理 $f_{i-1}$ 的前缀/后缀最大值，然后单次 $O(k)$ 枚举相交的区间即可。

复杂度 $O(nmk)$，可以通过 `F1`。

---------

上面的做法还需要进一步优化；两个区间不相交的情况已经优化到了 $O(1)$ 一次转移，很难再优化了。

考虑如何快速计算 $\max \limits_{[p,j+k-1]\bigcap [j,j+k-1]\not\equiv \varnothing} \{ f_{i-1,p}+s_i[p,p+k-1] \bigcup [j,j+k-1] \}$。

我们不妨设 $p \le j$，另一种情况可以类似。

所以要求的变成了 $\max \limits_{p\ge j-k} \{ f_{i-1,p}+s_i[p,j+k-1]  \}$。

稍作变形，可以变成 $\max \limits_{p\ge j-k} \{ f_{i-1,p}+s_i[1,j+k-1]-s_i[1,p-1]  \}$。

可以用单调队列求区间 $f_{i-1,p}-s_i[1,p-1]$ 的最大值，然后剩下的都是只和 $j$ 有关的信息。

复杂度 $O(nm)$ ，当然，用一些数据结构多一个 $\log$ 也行。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=55;
const int MR=2e4+10;
#define int long long
int n,m,k,a[NR][MR],f[NR][MR];
int pre[MR],suf[MR],sum[NR][MR];

signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]),sum[i][j]=sum[i][j-1]+a[i][j];
	for(int i=1;i<=n;i++){
		memset(pre,0,sizeof(pre));
		memset(suf,0,sizeof(suf));
		if(i>1)
			for(int j=1;j<=m-k+1;j++)f[i-1][j]+=sum[i][j+k-1]-sum[i][j-1];
		for(int j=1;j<=m-k+1;j++)pre[j]=max(pre[j-1],f[i-1][j]);
		for(int j=m-k+1;j>=1;j--)suf[j]=max(suf[j+1],f[i-1][j]);
		for(int j=1;j<=m-k+1;j++)
			f[i][j]=max(pre[max(0ll,j-k)],suf[min(m-k+2,j+k)])+sum[i][j+k-1]-sum[i][j-1];
		deque<int>q;
		for(int j=1;j<=m-k+1;j++){
			while(!q.empty()&&q.front()<=j-k)q.pop_front();
			while(!q.empty()&&f[i-1][q.back()]-sum[i][q.back()+k-1]<=f[i-1][j]-sum[i][j+k-1])q.pop_back();
			q.push_back(j);
			if(!q.empty())f[i][j]=max(f[i][j],f[i-1][q.front()]-sum[i][q.front()+k-1]+sum[i][j+k-1]);
		}
		q.clear();
		for(int j=m-k+1;j>=1;j--){
			while(!q.empty()&&q.front()>=j+k)q.pop_front();
			while(!q.empty()&&f[i-1][q.back()]+sum[i][q.back()-1]<=f[i-1][j]+sum[i][j-1])q.pop_back();
			q.push_back(j);
			if(!q.empty())f[i][j]=max(f[i][j],f[i-1][q.front()]+sum[i][q.front()-1]-sum[i][j-1]);
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++)ans=max(ans,f[n][i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Leap_Frog (赞：1)

### Problem.
还算比较经典的 dp 题吧。  
楼上楼下的题解看不懂，还是自己来写一篇吧。
### Discription.
给定一个矩阵，现在你可以对每一行取出一个这一行和下一行组成的 $2\times k$ 的子矩阵，并取走其中的所有数（如果最后一行的话就只能取一行。  
现在你需要让你取出的所有数最大化。  
### Solution.
首先，有一个很显然的 $O(n\times m^2)$ 的 dp。  
设 $dp_{i,j}$ 表示第 $i$ 和 $i+1$ 行选 $[j,j+k-1]$ 这个子矩阵时的最大答案。  
那么 $dp_{i,j}$ 可以从所有的 $dp_{i-1,k}$ 转移过来，主要就是去重。  
但是如果暴力枚举时肯定能算出去重函数的，所以我们得到了一份 TLE on 13的代码，如下
```cpp
//愿你有一天能和你重要的人重逢。
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
int n,m,K,a[55][20005],s[55][20005],dp[55][20005];
inline int cf(int i,int l,int r) {if(l>r) swap(l,r);return max(s[i][l+K-1]-s[i][r-1],0);}
int main()
{
	read(n),read(m),read(K);int mx=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) read(a[i][j]),s[i][j]=s[i][j-1]+a[i][j];
	for(int j=1;j<=m-K+1;j++) dp[1][j]=s[1][j+K-1]-s[1][j-1]+s[2][j+K-1]-s[2][j-1];
	for(int i=2;i<=n;i++) for(int j=1;j<=m-K+1;j++) for(int k=1;k<=m-K+1;k++)
		dp[i][j]=max(dp[i][j],dp[i-1][k]+s[i+1][j+K-1]-s[i+1][j-1]+s[i][j+K-1]-s[i][j-1]-cf(i,k,j));
	for(int j=1;j<=m-K+1;j++) mx=max(mx,dp[n][j]);
	return printf("%d\n",mx),0;
}
```
然后我们就能获得……0分的好成绩，毕竟 F1 都不让这种方法过。  

然后我们考虑优化，F1 那题有一个限制 $k\le\min(20,m)$。  
思考思考这个限制有什么用：我们会发现，因为上面的重复（`cf`）中有一个 `max`，我们考虑去掉它。  
首先，矩阵中所有的数都是正数，那么也就是说只有在 `l+K-1>=r` 时才会取到 `s[i][l+K-1]-s[i][r-1]`。  
那么这就好办了，只有在 $j-K+1\le k\le j+K-1$ 时那个 `cf` 函数才会有用。  
然后又因为 $k$ 很小，那么我们直接暴力转移这样的状态，剩下的因为 `cf` 函数等于 $0$，所以我们直接记录前缀最大值后缀最大值就好了，这样复杂度是 $O(n\times m\times k)$ 的，足以通过 F1，代码
```cpp
//愿你有一天能和你重要的人重逢。
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
int n,m,K,a[55][20005],s[55][20005],dp[55][20005],mx1[55][25005],mx2[55][25005];
inline int cf(int i,int l,int r) {if(l>r) swap(l,r);return l+K-1>=r?s[i][l+K-1]-s[i][r-1]:0;}
int main()
{
	read(n),read(m),read(K);int mx=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) read(a[i][j]),s[i][j]=s[i][j-1]+a[i][j];
	for(int j=1;j<=m-K+1;j++) dp[1][j]=s[1][j+K-1]-s[1][j-1]+s[2][j+K-1]-s[2][j-1];
	for(int j=1;j<=m-K+1;j++) mx1[1][j]=max(mx1[1][j-1],dp[1][j]);
	for(int j=m-K+1;j>=1;j--) mx2[1][j]=max(mx2[1][j+1],dp[1][j]);
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=m-K+1;j++)
		{
			int now=s[i+1][j+K-1]-s[i+1][j-1]+s[i][j+K-1]-s[i][j-1];
			dp[i][j]=max(dp[i][j],now+max(j>K?mx1[i-1][j-K]:0,mx2[i-1][j+K]));
			for(int k=max(j-K+1,1);k<=min(j+K-1,m-K+1);k++) dp[i][j]=max(dp[i][j],dp[i-1][k]+now-cf(i,k,j));
		}
		for(int j=1;j<=m-K+1;j++) mx1[i][j]=max(mx1[i][j-1],dp[i][j]);
		for(int j=m-K+1;j>=1;j--) mx2[i][j]=max(mx2[i][j+1],dp[i][j]);
	}
	for(int j=1;j<=m-K+1;j++) mx=max(mx,dp[n][j]);
	return printf("%d\n",mx),0;
}
```
然后，我们继续思考，如果 k 很大这样复杂度还是无法通过 F2，我们仔细观察一下，发现上面的暴力转移过程中还可以继续分类讨论，如下
```cpp
for(int k=max(j-K+1,1);k<=j;k++) dp[i][j]=max(dp[i][j],dp[i-1][k]+now-s[i][k+K-1]+s[i][j-1]);
for(int k=j;k<=min(j+K-1,m-K+1);k++) dp[i][j]=max(dp[i][j],dp[i-1][k]+now-s[i][j+K-1]+s[i][k-1]);
```
那么这样就很显然了吧。  
在上面那一行中，`now+s[i][j-1]`是不变的，而 `dp[i-1][k]+s[i][k+K-1]`与 $j$ 无关。  
下面那一行中，`now-s[i]`是不变的，而`dp[i-1][k]+s[i][k-1]`是与 $j$ 无关的。  
那么我们只需要用 线段树 或 st表 等数据结构来维护区间最大值就好了，复杂度是 $O(n\times m\log m)$ 的，笔者用的线段树。  

```cpp
//愿你有一天能和你重要的人重逢。
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
int n,m,K,a[55][20005],s[55][20005],dp[55][20005],mx1[55][25005],mx2[55][25005],t[25005];
inline int cf(int i,int l,int r) {if(l>r) swap(l,r);return s[i][l+K-1]-s[i][r-1];}
struct segmenttree
{
	int t[100005];
	inline void build(int x,int l,int r,int *c)
	{
		if(!(l^r)) return(void)(t[x]=c[l]);
		build(x<<1,l,(l+r)>>1,c),build(x<<1|1,((l+r)>>1)+1,r,c),t[x]=max(t[x<<1],t[x<<1|1]);
	}
	inline int query(int x,int l,int r,int dl,int dr)
	{
		if(dl>r||l>dr) return -1e9;else if(dl<=l&&r<=dr) return t[x];
		return max(query(x<<1,l,(l+r)>>1,dl,dr),query(x<<1|1,((l+r)>>1)+1,r,dl,dr));
	}
}T1,T2;
int main()
{
	read(n),read(m),read(K);int mx=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) read(a[i][j]),s[i][j]=s[i][j-1]+a[i][j];
	for(int j=1;j<=m-K+1;j++) dp[1][j]=s[1][j+K-1]-s[1][j-1]+s[2][j+K-1]-s[2][j-1];
	for(int j=1;j<=m-K+1;j++) mx1[1][j]=max(mx1[1][j-1],dp[1][j]);
	for(int j=m-K+1;j>=1;j--) mx2[1][j]=max(mx2[1][j+1],dp[1][j]);
	for(int i=2;i<=n;i++)
	{
		for(int k=1;k<=m-K+1;k++) t[k]=dp[i-1][k]-s[i][k+K-1];
		T1.build(1,1,m-K+1,t);
		for(int k=1;k<=m-K+1;k++) t[k]=dp[i-1][k]+s[i][k-1];
		T2.build(1,1,m-K+1,t);
		for(int j=1;j<=m-K+1;j++)
		{
			int now=s[i+1][j+K-1]-s[i+1][j-1]+s[i][j+K-1]-s[i][j-1];
			dp[i][j]=max(dp[i][j],now+max(j>K?mx1[i-1][j-K]:0,mx2[i-1][j+K]));
			dp[i][j]=max(dp[i][j],T1.query(1,1,m-K+1,max(j-K+1,1),j)+now+s[i][j-1]);
			dp[i][j]=max(dp[i][j],T2.query(1,1,m-K+1,j,min(j+K-1,m-K+1))+now-s[i][j+K-1]);
//			for(int k=max(j-K+1,1);k<=j;k++) dp[i][j]=max(dp[i][j],dp[i-1][k]+now-s[i][k+K-1]+s[i][j-1]);
//			for(int k=j;k<=min(j+K-1,m-K+1);k++) dp[i][j]=max(dp[i][j],dp[i-1][k]+now-s[i][j+K-1]+s[i][k-1]);
		}
		for(int j=1;j<=m-K+1;j++) mx1[i][j]=max(mx1[i][j-1],dp[i][j]);
		for(int j=m-K+1;j>=1;j--) mx2[i][j]=max(mx2[i][j+1],dp[i][j]);
	}
	for(int j=1;j<=m-K+1;j++) mx=max(mx,dp[n][j]);
	return printf("%d\n",mx),0;
}
```
### Coding.
完结撒花，如果你从头到尾看下来了，你还不知道代码在哪里吗？

---

## 作者：bluewindde (赞：0)

本文是作者 VP 赛场想到的抽象解法，一定不是最优解。

DP 很显然。

设 $dp_{i, j}$ 表示第 $i$ 天的相机放在 $j$ 区域，可以拍摄到的野生动物的数量的最大值。

设 $w(t, x, y)$ 表示第 $i$ 天的相机放在 $x$ 区域，前一天的相机放在 $y$ 区域的答案，有转移

$$dp_{i, j} = \max\limits_{x = 1}^m \{ dp_{i - 1, x} + w(i, j, x) \}$$

所求即为

$$\max\limits_{i = 1}^m dp_{n, i}$$

对 $a$ 数组求前缀和，$w$ 容易在 $O(1)$ 的时间内求出，时间复杂度 $O(nm^2)$，不能通过。

发现如果 $x$ 很小或者 $x$ 很大，它们的情况本质相同（即 $w$ 函数的值相同），可以打包处理。具体而言，如果区间 $[x, x + k - 1]$ 与 $[j, j + k - 1]$ 无交，$w$ 的函数值相同，ST 表处理这样的 $dp_{i - 1, x}$ 的最大值，暴力枚举有交的 $O(k)$ 个区间，时间复杂度 $O(nm \log m + nk)$，可以通过 easy version。

考虑快速处理有交的部分：开两棵线段树，分别维护 $x < j$ 和 $x > j$ 时合法的 $dp_{i - 1, x} + w(i, j, x)$ 的最大值（$x = j$ 时单独处理）。移动 $j$ 时：删去非法区间；加入新的合法区间；对于其他区间的贡献变化是一致的，通过区间加维护。对一个 $j$ 的答案即为两棵线段树的最大值加上 $\sum\limits_{t = j}^{\min\{j + k - 1, m\}} a_{i + 1, t}$（即漏算的答案）。时间复杂度 $O(nm \log m)$，可以通过。

场上没调出来，场后发现线段树可以用单调队列替换，码量和速度都吊打线段树，很无语。

```cpp
#include <iostream>
#include <math.h>

#define int long long

using namespace std;

int n, m, k;
int a[55][20005];
int f[55][20005];

int dp[55][20005];

static inline int calc(int x, int y1, int y2) { return f[x][y2] - f[x][y1 - 1]; }

int st[20005][18];
static inline void init() {
    for (int j = 1; j <= 16; ++j)
        for (int i = 1; i + (1 << j) - 1 <= m; ++i)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
static inline int query(int l, int r) {
    int len = (int)log2(r - l + 1);
    return max(st[l][len], st[r - (1 << len) + 1][len]);
}

class SGT {
  public:
    struct node {
        int val;
        inline node operator+(const node &nd) const { return {max(val, nd.val)}; }
    } d[80005];
    int tag[80005];
    inline void pushdown(int p) {
        d[p << 1].val += tag[p];
        d[p << 1 | 1].val += tag[p];
        tag[p << 1] += tag[p];
        tag[p << 1 | 1] += tag[p];
        tag[p] = 0;
    }
    inline void build(int s, int t, int p) {
        tag[p] = 0;
        d[p].val = 0;
        if (s == t)
            return;
        int mid = (s + t) >> 1;
        build(s, mid, p << 1);
        build(mid + 1, t, p << 1 | 1);
        d[p] = d[p << 1] + d[p << 1 | 1];
    }
    inline void update(int l, int r, int s, int t, int c, int p) {
        if (l <= s && r >= t) {
            d[p].val += c;
            tag[p] += c;
            return;
        }
        int mid = (s + t) >> 1;
        pushdown(p);
        if (l <= mid)
            update(l, r, s, mid, c, p << 1);
        if (r > mid)
            update(l, r, mid + 1, t, c, p << 1 | 1);
        d[p] = d[p << 1] + d[p << 1 | 1];
    }
    inline void cover(int x, int s, int t, int c, int p) {
        if (s == t) {
            d[p].val = c;
            return;
        }
        int mid = (s + t) >> 1;
        pushdown(p);
        if (x <= mid)
            cover(x, s, mid, c, p << 1);
        else
            cover(x, mid + 1, t, c, p << 1 | 1);
        d[p] = d[p << 1] + d[p << 1 | 1];
    }
} pre, suf;

static inline void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            f[i][j] = f[i][j - 1] + a[i][j];
        }
    }
    for (int j = 1; j <= m; ++j)
        dp[1][j] = calc(1, j, min(j + k - 1, m)) + calc(2, j, min(j + k - 1, m));
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            st[j][0] = dp[i - 1][j];
        init();
        pre.build(1, m, 1);
        suf.build(1, m, 1);
        for (int j = 2; j <= k && j <= m; ++j)
            suf.cover(j, 1, m, dp[i - 1][j] + calc(i, 1, j - 1), 1);
        for (int j = 1; j <= m; ++j) {
            int l = j;
            int r = min(j + k - 1, m);
            int ret = 0;
            if (j - k > 0)
                ret = max(ret, query(1, j - k) + calc(i, l, r));
            if (j + k <= m)
                ret = max(ret, query(j + k, m) + calc(i, l, r));
            ret = max(ret, pre.d[1].val);
            ret = max(ret, suf.d[1].val);
            ret = max(ret, dp[i - 1][l]);
            dp[i][j] = calc(i + 1, l, r) + ret;
            // add
            pre.cover(l, 1, m, dp[i - 1][l], 1);
            if (r + 1 <= m)
                suf.cover(r + 1, 1, m, dp[i - 1][r + 1] + calc(i, j, r), 1);
            // delete
            if (l - k + 1 >= 1)
                pre.cover(l - k + 1, 1, m, 0, 1);
            if (l < m)
                suf.cover(l + 1, 1, m, 0, 1);
            // move
            if (r < m)
                pre.update(max(l - k + 2, 1ll), l, 1, m, a[i][r + 1], 1);
            if (l + 2 <= m)
                suf.update(l + 2, min(r + 1, m), 1, m, -a[i][j], 1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= m; ++i)
        ans = max(ans, dp[n][i]);
    cout << ans << endl;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("CF1304F.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
可能是比较难做的题？但是如果想到了也不会很难做。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
可以先去看一下我对于 [F1](https://www.luogu.com.cn/article/mblrc4iy) 的做法。

考虑思路连续，尝试把上一题的思路推到这一题。

注意到 dp 是无法删去的，我们要做的还是从转移优化入手。

同上一题，定义 $f_{i,j}$ 表示必须选择左上角位于 $(i,j)$ 的矩形的最大答案。

如果把题目的转移方程简而言之，就是从**去重过**的上一行最大值转移过来。

上一题我们使用了前后缀不重复 $\max$ 维护，重复部分暴力枚举的方式来维护。

考虑这里产生的多次操作所劣势的地方。

当我们的矩形从 $(i,j)\rightarrow(i,j+1)$ 时，$j+1\sim j+k-1$ 这一段仍然是被覆盖的，产生影响的仅仅只有加上了 $j$ 这一位和去掉了 $j+k$ 这一位。

当一位 $(i,j)$ 被移除时，我们考虑他产生的贡献。

若我们只把这一行拿出来：
$$1,\dots,j+1-k,j+2-k,\dots,j,\dots,j+k-2,j+k-1,\dots,m$$
产生影响的最左/右的两个区间即为 $j+1-k\sim j/j\sim j+k-1$。

对于 $f$ 的值的贡献也就在于 $j+1-k\sim j$ 这一段。

考虑直接上个线段树来维护这个东西。

那么就是从全局最大值转移过来即可。

这个时候的代码就比较清晰了。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
using namespace std;
const int N=55,M=2e4+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,k,l,a[N][M],s[N][M],t[M<<2],lz[M<<2],f[N][M];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void pushson(int p,int w){t[p]+=w;lz[p]+=w;}
inline void pushdown(int p){pushson(ls,lz[p]);pushson(rs,lz[p]);lz[p]=0;}
inline void modify(int p,int l,int r,int s,int e,int w)
{
	if(l>=s&&r<=e) return pushson(p,w),void();
	pushdown(p);
	if(mid>=s) modify(ls,l,mid,s,e,w);
	if(mid<e) modify(rs,mid+1,r,s,e,w);
	t[p]=max(t[ls],t[rs]);
}
inline int ww(int i,int j){return s[i][j+k-1]-s[i][j-1];}
inline void mdf(int i,int x,int op){modify(1,1,l,x+1-k,min(x,l),op*a[i][x]);}
signed main()
{
    n=read(),m=read(),k=read();l=m-k+1;for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) s[i][j]=s[i][j-1]+(a[i][j]=read());
    for(int j=1;j<=m;j++) f[1][j]=ww(1,j)+ww(2,j);
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=l;j++) modify(1,1,l,j,j,f[i-1][j]);
		for(int j=k,s=0;j>=1;j--) s+=a[i][j],(j<=l)&&(modify(1,1,l,j,j,-s),0);
		for(int j=1;j<=l;j++)
		{
			f[i][j]=t[1]+ww(i+1,j)+ww(i,j);
			mdf(i,j,1);mdf(i,j+k,-1);
		}
		memset(t,0,sizeof t);memset(lz,0,sizeof lz);
	}
    int ans=0;for(int i=1;i<=l;i++) ans=max(ans,f[n][i]);print(ans);
    genshin:;flush();return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

## 思路

设$a_{i,j}$ 表示第 $i$ 天 $j$ 地区的动物数量， $s(i,l,r) = \sum_{p=l}^r a_{i,p}$

设 $f_{i,j}$ 表示前 $i$ 天满足第 $i-1$ 天拍摄的范围是 $[j, j + k)$ 的条件下，拍摄到的动物数量的最大值。

于是我们可以得到递推式

$$f_{i,j} = \max_{p} \{ f_{i-1,p}-V\}+ s(i,j,j+k-1) + s(i-1,j,j+k-1)$$

其中 $V$ 表示第 $i-1$ 天 $[j,j+k-1]$ 与 $[p,p+k-1]$ 的重叠部分的动物数量

我们预处理出 $f_{i-1}$ 的前缀 $\max$ 和后缀 $\max$ 就可以 $O(1)$ 得出 $[p,p+k-1]$ 与 $[j,j+k-1]$ 不重叠时的答案，然后 $O(k)$ 枚举重叠的 $p$，得到一个复杂度 $O(nmk)$ 的 dp。

对于每一轮递推，我们用线段树动态维护每一个 $p$ 的 $f_{i-1,p}-V$ 即可，时间复杂度 $O(nm\log m)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 20010, M = N << 2;
int a[100][N], s[100][N];
ll f[100][N];

struct Node {
	ll mx, add;
} tr[M];

void pushup(int u) {
	tr[u].mx = max(tr[u << 1].mx, tr[u << 1 | 1].mx);
}

void pushdown(int u) {
	if (tr[u].add) {
		tr[u << 1].add += tr[u].add, tr[u << 1].mx += tr[u].add;
		tr[u << 1 | 1].add += tr[u].add, tr[u << 1 | 1].mx += tr[u].add;
		tr[u].add = 0;
	}
}

void modify(int u, int l, int r, int s, int t, ll v) {
	if (s <= l && r <= t) {
		tr[u].mx += v;
		tr[u].add += v;
		return;
	}
	pushdown(u);
	int mid = l + r >> 1;
	if (s <= mid) modify(u << 1, l, mid, s, t, v);
	if (t > mid) modify(u << 1 | 1, mid + 1, r, s, t, v);
	pushup(u);
}

int cover(int i, int l1, int r1, int l2, int r2) {
	if (r1 < l2 || r2 < l1) return 0;
	return s[i][min(r1, r2)] - s[i][max(l1, l2) - 1];
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i ++ )
    	for (int j = 1; j <= m; j ++ ) {
    		scanf("%d", &a[i][j]);
    		s[i][j] = a[i][j] + s[i][j - 1];
    	}
    for (int j = 1; j + k - 1 <= m; j ++ ) {
    	f[2][j] = (ll)s[2][j + k - 1] - s[2][j - 1] + s[1][j + k - 1] - s[1][j - 1];
	}
    for (int i = 3; i <= n + 1; i ++ ) {
    	for (int j = 0; j < M; j ++ ) tr[j].mx = tr[j].add = 0;
    	int l = 1, r = k;
    	for (int j = 1; j + k - 1 <= m; j ++ ) {
    		modify(1, 1, m, j, j, f[i - 1][j] - cover(i - 1, l, r, j, j + k - 1));
		}
		f[i][l] = tr[1].mx + s[i][r] + s[i - 1][r];
		while (r + 1 <= m) {
			modify(1, 1, m, max(1, l - k + 1), l, a[i - 1][l]);
			modify(1, 1, m, l + 1, r + 1, -a[i - 1][r + 1]);
			l ++ , r ++ ;
			f[i][l] = tr[1].mx + s[i][r] - s[i][l - 1] + s[i - 1][r] - s[i - 1][l - 1];
		}
	}
	long long ans = 0;
	for (int i = 1; i + k - 1 <= m; i ++ ) ans = max(ans, f[n + 1][i]);
	printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Maverik (赞：0)

# Animal Observation (hard version)

##### Statement

​	Gildong 计划拍摄森林中的野生动物们。森林被划分为 $m$ 个地区，依次编号为 $1$ 到 $m$，他的拍摄计划持续 $n$ 天。每一天，他会选择森林中连续的 $k$ 个地区，并且录一段长为 $2$ 天的录像。（如果是最后一天，那就录一段长度为 $1$ 天的录像）这样所有在这两天之内在这 $k$ 个地区中出现过的动物都会被拍摄到。他知道未来 $n$ 天内每一天每一个地区会出现多少野生动物。他想拍摄下尽可能多的野生动物。注意如果一个动物被拍摄了两次，那么只会被计算一次。你的任务是求出拍摄到的动物数量的最大值。$n\le 50,m\le 20000,k\le m$。

##### Solution

​	提供一种不用脑子还好写的维护方式。$f(i,j)$ 表示前 $i$ 行，第 $i$ 行选 $[j,j+K-1]$ 时的贡献，转移分成有交和无交。无交是容易的，有交的时候要扣去交集的重复贡献，只需要将交集的贡献转到两个端点的前缀和上，就可以把式子拆开，然后只需要写个 ```st``` 表就行了，跑的很快。

```cpp
inline int qsum(int x,int l,int r){return a[x][r]-a[x][l-1];}
inline void prework(int siz)
{
    for(int k=1;k<=__lg(siz);k++) for(int i=1;i+(1<<k)-1<=siz;i++)
        st[i][k]=max(st[i][k-1],st[i+(1<<(k-1))][k-1]);
}
inline int qmax(int l,int r){return o=__lg(r-l+1),max(st[l][o],st[r-(1<<o)+1][o]);}
inline void solve()
{
    cin>>n>>m>>K;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j],a[i][j]+=a[i][j-1];
    for(int i=1;i<=m-K+1;i++) f[1][i]=qsum(1,i,i+K-1);
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<=m-K+1;j++) val[j]=f[i-1][j]+qsum(i,j,j+K-1),f[i][j]=val[j];
        for(int j=1;j<=m-K+1;j++) st[j][0]=val[j]+a[i][j-1]; prework(m-K+1);
        for(int j=1;j<=m-K+1;j++) cmax(f[i][j],qsum(i,j,j+K-1)-a[i][j+K-1]+qmax(j,min(m-K+1,j+K-1)));
        for(int j=1;j<=m-K+1;j++) st[j][0]=val[j]-a[i][j+K-1]; prework(m-K+1);
        for(int j=1;j<=m-K+1;j++) cmax(f[i][j],qsum(i,j,j+K-1)+a[i][j-1]+qmax(max(j-K+1,1ll),j));
        for(int j=1;j<=m-K+1;j++) pre[j+K-1]=max(pre[j+K-2],val[j]);
        for(int j=m-K+1;j>=1;j--) suf[j]=max(suf[j+1],val[j]);
        for(int j=1;j<=m-K+1;j++) cmax(f[i][j],qsum(i,j,j+K-1)+max(pre[j-1],suf[j+K]));
    }
    cout<<*max_element(f[n],f[n]+maxn)<<endl;
}
```



---

## 作者：daniEl_lElE (赞：0)

考虑 $dp_{i,j}$ 表示看到第 $i$ 行，第 $i$ 行的录像是 $j\sim j+k-1$ 列。

考虑转移，暴力转移是容易的。第一个简单优化是距离大于等于 $k$ 的的转移贡献都是相同的，这个可以通过 $k$ 较小的 F1 题。

考虑从左到右，从右到左滑动转移。对于距离大于等于 $k$ 的贡献的差值是 $a_{i,j}+a_{i+1,j}-a_{i,j+k}-a_{i+1,j+k}$。对于距离小于等于 $k$ 的贡献的差值是 $a_{i,j}+a_{i+1,j}-a_{i+1,j+k}$（因为 $a_{i,j+k}$ 在上一行已经被考虑了）。线段树维护即可。复杂度 $O(nm\log m)$。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
struct sgt{
	int f[100005],lzt[100005];
	void pushdown(int i){
		f[i*2]+=lzt[i];
		f[i*2+1]+=lzt[i];
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void build(int i,int l,int r){
		lzt[i]=0;
		f[i]=0;
		if(l==r){
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]+=cg;
			lzt[i]+=cg;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=max(f[i*2],f[i*2+1]);
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(qr<l||ql>r) return 0;
		pushdown(i);
		return max(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree;
int a[52][40005],pre[52][40005],dp[52][20005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j],pre[i][j]=pre[i][j-1]+a[i][j];
	for(int i=1;i<=n;i++) for(int j=m+1;j<=2*m;j++) pre[i][j]=pre[i][j-1];
	for(int j=1;j<=m;j++) dp[1][j]=pre[1][j+k-1]-pre[1][j-1]+pre[2][j+k-1]-pre[2][j-1];
	for(int i=2;i<=n;i++){
		tree.build(1,1,m);
		for(int j=1;j<=m;j++){
			if(j!=1){
				tree.change(1,1,m,1,j-1,a[i][j+k-1]+a[i+1][j+k-1]);
				tree.change(1,1,m,max(1ll,j-k),j-1,-a[i+1][j-1]);
				if(j-k>1) tree.change(1,1,m,1,j-k-1,-a[i][j-1]-a[i+1][j-1]);
			}
			tree.change(1,1,m,j,j,dp[i-1][j]+pre[i+1][j+k-1]-pre[i+1][j-1]);
			dp[i][j]=max(dp[i][j],tree.qry(1,1,m,1,j));
		}
		tree.build(1,1,m);
		for(int j=m;j>=1;j--){
			if(j!=m){
				tree.change(1,1,m,j+1,m,a[i][j]+a[i+1][j]);
				tree.change(1,1,m,j+1,min(m,j+k),-a[i+1][j+k]);
				if(j+k<m) tree.change(1,1,m,j+k+1,m,-a[i][j+k]-a[i+1][j+k]);
			}
			tree.change(1,1,m,j,j,dp[i-1][j]+pre[i+1][j+k-1]-pre[i+1][j-1]);
			dp[i][j]=max(dp[i][j],tree.qry(1,1,m,j,m));
		}
	}
	int maxv=0;
	for(int j=1;j<=m;j++) maxv=max(maxv,dp[n][j]);
	cout<<maxv;
	return 0;
}

```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

首先想到一个 $dp$ 状态：$dp_{i,j}$ 表示第 $i$ 天在第 $j$ 个位置放摄像头的时候，能看到的动物的最大数量。

显然，我们要做的就是枚举 $i-1$ 天放在哪里，然后减去这两个摄像头重合的位置，再加上第 $i$ 个摄像头这两天能看到的总数。

首先我们假设 $p$ 是 $a$ 的前缀和数组，即 $p_i=\sum_{j=1}^{i} a_j$。

然后，分成三种情况：

1. 两个无交集，则第 $i$ 个摄像头能覆盖到 $[j,j+k-1]$ 的区域，共计两天，即 $\sum\limits_{q=i}^{i+1}\sum\limits_{r=j}^{j+k-1} a_{q,r}$，用前缀和表示即为 $\sum\limits_{q=i}^{i+1} p_{q,j+k-1}-p_{q,j-1}$。

2. $j \leq l+k-1 < j+k-1$，即 $[l,l+k-1]$ 的右边一部分和 $[j,j+k-1]$ 的左边一部分重合。此时重合的部分是 $[j,l+k-1]$，需要减去 $\sum\limits_{q=j}^{l+k-1} a_{i,q}$，用前缀和表示为 $p_{i,l+k-1}-p_{i,j-1}$。

3. $j \leq l \leq j+k-1$，即 $[l,l+k-1]$ 的左边一部分和 $[j,j+k-1]$ 的右边一部分重合。此时重合的部分是 $[l,j+k-1]$，需要减去 $\sum\limits_{q=l}^{j+k-1} a_{i,q}$，用前缀和表示为 $p_{i,j+k-1}-p_{i,l-1}$。

暴力转移的复杂度是 $O(nm^2)$。

```cpp
#include <iostream>
#include <vector>
#define ios ios::sync_with_stdio
using namespace std;
const int MAXN=55,MAXM=20005;

int a[MAXN][MAXM],pre[MAXN][MAXM];
int dp[MAXN][MAXM],g[MAXN][MAXM];
int main(){
	ios();
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			pre[i][j]=pre[i][j-1]+a[i][j]; // 记录前缀和 
		}
	for(int i=1;i<=n;i++){
		for(int j=1;j+k-1<=m;j++){
			for(int l=1;l+k-1<=m;l++){
				int cut=0; // 记录重合的部分 
				if(i!=1){ // 如果 i=1 此时不会有重合，需要特判 
					if(l<=j && l>=j-k+1) cut+=pre[i][l+k-1]-pre[i][j-1]; // 情况 2 
					else if(l>j && l<=j+k-1) cut+=pre[i][j+k-1]-pre[i][l-1]; // 情况 3 
				}
//				cout<<i<<" "<<j<<" "<<j+k-1<<" "<<l<<" "<<l+k-1<<" "<<cut<<endl;
				dp[i][j]=max(dp[i][j],dp[i-1][l]+pre[i][j+k-1]-pre[i][j-1]+pre[i+1][j+k-1]-pre[i+1][j-1]-cut);
				// 上面的转移相当于第 i 个能覆盖到的位置，减去重合的部分 
			}
		}
	}
	int ans=-1e9;
	for(int i=1;i<=m;i++) ans=max(ans,dp[n][i]); // 对答案取 max。 
	cout<<ans;
	return 0; 
}
```

然后，你发现这连 F1 都过不去。（

考虑进行优化。

- 对于 F1，我们发现 $k$ 很小，所以我们把 $i$ 和 $j$ 有交集的地方暴力转移，其他的地方由于**没有交集**所以每个点的**贡献是固定的**，记录一个前缀 $\max$ 一个后缀 $\max$，拼起来转移即可。

具体的，我们对于每个 $j$，枚举 $l \in [j-k+1,j+k-1]$ 进行暴力转移，而对于 $l \in [1,j-k]$ 我们使用前缀 $\max$ 求解，对于 $l \in [j+k,m]$ 我们用后缀 $\max$ 求解。

每次转移完成之后，再扫两遍更新前缀 $\max$ 和后缀 $\max$。

复杂度 $O(nmk)+O(nm)$。

```cpp
#include <iostream>
#include <vector>
#define ios ios::sync_with_stdio
using namespace std;
const int MAXN=55,MAXM=20005;

int a[MAXN][MAXM],pre[MAXN][MAXM];
int dp[MAXN][MAXM],g[MAXN][MAXM];

int premax[MAXM],sufmax[MAXM]; // 前缀 max 和后缀 max 数组 
int main(){
	ios();
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			pre[i][j]=pre[i][j-1]+a[i][j]; // 记录前缀和 
		}
	for(int i=1;i<=n;i++){
		for(int j=1;j+k-1<=m;j++){
			int Lef=max(1,j-k+1),Rig=min(m,j+k-1);
			dp[i][j]=max(premax[Lef-1],sufmax[Rig+1])+pre[i][j+k-1]-pre[i][j-1]+pre[i+1][j+k-1]-pre[i+1][j-1];
			// 上面相当于对 [1,Lef-1] 和 [Rig+1,m] 的 dp 取 max，然后加上贡献 
			for(int l=Lef;l<=Rig;l++){ // 暴力转移部分 
				int cut=0;
				if(i!=1){
					if(l<=j && l>=j-k+1) cut+=pre[i][l+k-1]-pre[i][j-1];
					else if(l>j && l<=j+k-1) cut+=pre[i][j+k-1]-pre[i][l-1];
				}
				dp[i][j]=max(dp[i][j],dp[i-1][l]+pre[i][j+k-1]-pre[i][j-1]+pre[i+1][j+k-1]-pre[i+1][j-1]-cut);
			}
		}
		for(int j=1;j+k-1<=m;j++) premax[j]=max(premax[j-1],dp[i][j]); // 更新前缀 max 
		for(int j=m-k+1;j>=1;j--) sufmax[j]=max(sufmax[j+1],dp[i][j]); // 更新后缀 max 
	}
	int ans=-1e9;
	for(int i=1;i<=m;i++) ans=max(ans,dp[n][i]); // 对答案取 max。 
	cout<<ans;
	return 0; 
}
```

- 对于 F2，我们发现 $k$ 变大了，这种暴力转移不可行了，因此考虑用支持 RMQ 的数据结构来维护上面那个暴力转移的东西。

### 线段树 $O(nm \log m)$ 做法

显然，如果我们把 2 和 3 两种情况放到一起，这是不好考虑的。所以我们考虑用两个线段树分别维护 2 和 3 这两个情况，然后随着 $j$ 的移动，对 2 和 3 分别进行维护，每次取一个 $\max$ 即可。

我们回顾一下之前的两个转移方程。这里以第 2 个为例，第三个情况的同理。

$$dp_{i,j}=\max_{l=1}^{m} (dp_{i-1,l}+p_{i,l+k-1}-p_{i,j-1})+\sum\limits_{q=i}^{i+1} p_{q,j+k-1}-p_{q,j-1}$$

我们把后面那一坨和 $i$ 有关的去掉，因为这些可以 $O(1)$ 转移。然后剩下：

$$\max_{l=1}^{m} (dp_{i-1,l}-p_{i,l+k-1}+p_{i,j-1})$$

考虑把和 $l$ 无关的拆出去，即这个 $-p_{i,j-1}$，剩下的 $dp_{i-1,l}+p_{i,l+k+1}$ 我们用线段树维护即可。

具体的，我们每次对于一个 $i$，在 $j$ 从 $0$ 开始的时候，我们第 2 种情况是没有的，所以这个线段树中目前为空；第 3 种情况有 $k$ 种，分别对应 $l=[1,k]$。所以我们对 $l \in [1,k]$ 分别插入，然后区间查询 $\max$。随着 $j$ 向后移，每次 2 情况的左端（如果长度满了 $k$）会失效，我们插入 `-inf`；每次 3 情况的左端也会失效，我们要把它扔到 2 情况的线段树里，并在 3 情况的线段树的对应位置插入一个 `-inf`。

然后，每次转移就从 2 情况、3 情况和前缀 $\max$、后缀 $\max$ 中找最大值就好了。（相当于就是前面那份代码中，把暴力转移换成了两个用双指针思想维护的单点修改区间查询 $\max$ 的线段树。）

---

## 作者：zzr8178541919 (赞：0)

### 题目简述
现在给你一个 $n×m$ 的矩阵，每个位置上都有一个数字 $a_{i,j}$。一开始的时候左右的格子都是白色的。对于每一行，你可以把这一行的某个格子 $(i,j)$ 作为左上角、将 $(min(i+1,n),j+k-1),$ $j\leq m-k+1$ 作为右下角的矩形区域进行染成黑色。一个格子可以被重复染色。最后你要最大化黑色格子的权值之和。

### Solution

我发现还可以用单调队列来做这题，并且复杂度比线段树快一个$log$.

首先比较暴力的$dp$都想得到，记$dp[i][j]:$前$i$行中，第$i$行选了$j$这个位置，在前i行的答案。

有状态转移方程：

```cpp
for(int i=2;i<=n;i++)
{
	for(int j=1;j<=m-k+1;j++)
	{
		int wns=0;
		for(int l=1;l<=m-k+1;l++)
		{
			if(j<=l)
			{
				if(j+k-1<l)
				wns=max(wns,(pre[i][l+k-1]-pre[i][l-1])+(pre[i][j+k-1]-pre[i][j-1])+dp[i-1][l]);
				else
				wns=max(wns,(pre[i][l+k-1]-pre[i][j-1])+dp[i-1][l]);
			}
			else
			{
				if(j>l+k-1)
				wns=max(wns,(pre[i][l+k-1]-pre[i][l-1])+pre[i][j+k-1]-pre[i][j-1]+dp[i-1][l]);
				else
				wns=max(wns,pre[i][j+k-1]-pre[i][l-1]+dp[i-1][l]);
			}
		}	
		dp[i][j]=max(dp[i][j],wns);
	}
}
```

发现中间的这一团东西，将它分成四段。

$(1):1 \ \ \ to \ \ \  j-k$

$(2):j-k+1 \ \ \ to \ \ \ j-1$

$(3):j \ \ \ to \ \ \ j+k-1$

$(4):j+k \ \ \ to \ \ \ n$

$(1),(4)$是可以直接从当前的$dp$数组用类似前缀和的方式预处理出来的,

$(2),(3)$推出状态转移方程，发现其符合类似滑动窗口的转移。

可以用单调队列优化到线性

#### $code:$ 
```cpp
#include<cmath>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#define int long long
#define reg register
using namespace std;
const int maxn=2e4+5;
const int mod=1e9;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int n,m,k;
int a[55][maxn];
int dp[55][maxn]; // dp[i][j] 
int pre[55][maxn];
int ans=0;
int f[maxn];
int g[maxn];
int dp1[maxn];
int dp2[maxn];
int q[maxn];
int head1=1,tail=0;
int yi=1;
int len1=0,len2=0;
int lin=0;
signed main()
{
	n=read(),m=read(),k=read();
	len1=k-1,len2=k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			pre[i][j]=pre[i][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=m-k+1;i++)
	{
		dp[1][i]=pre[1][i+k-1]-pre[1][i-1];
		f[i]=max(f[i-1],dp[1][i]+pre[2][i+k-1]-pre[2][i-1]);
	}
	for(int i=m-k+1;i>=1;i--)
		g[i]=max(g[i+1],dp[1][i]+pre[2][i+k-1]-pre[2][i-1]);
	head1=1,tail=0;
	for(int j=1;j<=m-k+1;j++)
	{
		while(head1<=tail && j-q[head1]+1>len1)
		head1++;
		while(head1<=tail && dp[1][j]-pre[2][j-1]>=dp[1][q[tail]]-pre[2][q[tail]-1])
		tail--;
		q[++tail]=j;
		dp1[j]=dp[1][q[head1]]-pre[2][q[head1]-1];
	}
	head1=1,tail=0;
	for(int j=m-k+1;j>=1;j--)
	{
		while(head1<=tail && q[head1]-j+1>len2)
		head1++;
		while(head1<=tail && dp[1][j]+pre[2][j+k-1]>=dp[1][q[tail]]+pre[2][q[tail]+k-1])
		tail--;
		q[++tail]=j;
		dp2[j]=dp[1][q[head1]]+pre[2][q[head1]+k-1];
	}	
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=m-k+1;j++)
		{
			int wns=0;
			int l1=max(lin,j-k);
			dp[i][j]=max(dp[i][j],f[l1]+pre[i][j+k-1]-pre[i][j-1]);
			int r=min(m-k+2,j+k);			
			dp[i][j]=max(dp[i][j],g[r]+pre[i][j+k-1]-pre[i][j-1]);
			wns=max(dp1[j-1]+pre[i][j+k-1],dp2[j]-pre[i][j-1]);
			dp[i][j]=max(dp[i][j],wns);
		}
		for(int j=1;j<=m-k+1;j++)
		f[j]=max(f[j-1],dp[i][j]+pre[i+1][j+k-1]-pre[i+1][j-1]);
		for(int j=m-k+1;j>=1;j--)
		g[j]=max(g[j+1],dp[i][j]+pre[i+1][j+k-1]-pre[i+1][j-1]);
		head1=1,tail=0;
		for(int j=1;j<=m-k+1;j++)
		{
			while(head1<=tail && j-q[head1]+1>len1)
			head1++;
			while(head1<=tail && dp[i][j]-pre[i+1][j-1]>=dp[i][q[tail]]-pre[i+1][q[tail]-1])
			tail--;
			q[++tail]=j;
			dp1[j]=dp[i][q[head1]]-pre[i+1][q[head1]-1];
		}
		head1=1,tail=0;
		for(int j=m-k+1;j>=1;j--)
		{
			while(head1<=tail && q[head1]-j+1>len2)
			head1++;
			while(head1<=tail && dp[i][j]+pre[i+1][j+k-1]>=dp[i][q[tail]]+pre[i+1][q[tail]+k-1])
			tail--;
			q[++tail]=j;
			dp2[j]=dp[i][q[head1]]+pre[i+1][q[head1]+k-1];
		}
	}
	for(int i=1;i<=m;i++)
	{	
		ans=max(ans,dp[n][i]);
	}
	printf("%lld\n",ans);
 	return 0;
}
```



---

## 作者：sunzh (赞：0)

考虑dp，用
$dp_{i,j}$表示第$i$行选第$[j,j+k)$列的最优解

首先假设一个点的贡献可以被选两次

$$dp_{i,j}=\max_{l=1}^n \{dp_{i-1,l}\}+\sum_{l=j}^{j+k-1}a_{i,l}+a_{i+1,l}$$
#### 但是要去重
对于$dp_{i-1,l}$ ,我们用了$a_{i,[l,l+k)}$这个区间内的数，而对于$dp_{i,j}$ ,我们要使用$a_{i,[j,j+k)}$

两者的交集被重复算了，所以式子就变成

$$dp_{i,j}=\max_{l=1}^n \{dp_{i-1,l}-\sum_{p=\max(l,j)}^{\min(l+k-1,j+k-1)}a_{i,p}\}+\sum_{l=j}^{j+k-1}a_{i,l}+a_{i+1,l}$$

如果我们暴力去重，用线段树维护区间和，区间max，时间复杂度$O(nmklog_2m)$，不能承受

但是每次改变j，我们只需要把$a_{i,j}$,$a_{i,j+k}$两个的影响用线段树处理，再取区间max，整体复杂度$O(nmlog_2m)$ 可以通过此题

#### update 关于如何处理$a_{i,j}$对答案的影响

根据式子可以看出，对于每个$dp_{i-1,l}$，只有$a_{i,[l,l+k-1 ]}$可能对其造成影响，那么反过来对于每一个$a_{i,j}$，他可能影响的范围就是$dp_{i-1,[j-k+1,j]}$

用一个线段树区间加减操作就可以维护这个影响

注意每次$j$右移要消除$a_{i,j-1}$的影响

贴一下代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){	if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
inline void print(int x){
	if(x<0) x=-x,putchar('-');
	if(x>=10) print(x/10);
	putchar(x%10+48);
}
struct seg{
	int sum[100010],tag[100010],maxn[100010];
	void pushup(int p){
		sum[p]=sum[p<<1]+sum[p<<1|1];
		maxn[p]=max(maxn[p<<1],maxn[p<<1|1]);
	}
	void pushdown(int p,int l,int r){
		if(tag[p]){
			int mid=l+r>>1;
			sum[p<<1]+=tag[p]*(mid-l+1);
			sum[p<<1|1]+=tag[p]*(r-mid);
			maxn[p<<1]+=tag[p];maxn[p<<1|1]+=tag[p]; 
			tag[p<<1]+=tag[p];tag[p<<1|1]+=tag[p];
			tag[p]=0;
		}
	}
	void update(int p,int l,int r,int L,int R,int k){
		if(l>=L&&r<=R){
			sum[p]+=k*(r-l+1);maxn[p]+=k;tag[p]+=k;return ;
		}
		pushdown(p,l,r);
		int mid=l+r>>1;
		if(L<=mid) update(p<<1,l,mid,L,R,k);
		if(R>mid) update(p<<1|1,mid+1,r,L,R,k);
		pushup(p);
	} 
	void build(int p,int l,int r,int *a){
		if(l==r){
			sum[p]=maxn[p]=a[l];tag[p]=0;
			return ;
		}
		int mid=l+r>>1;
		build(p<<1,l,mid,a);
		build(p<<1|1,mid+1,r,a);
		pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if(l>=L&&r<=R){
			return sum[p];
		}
		pushdown(p,l,r);
		pushup(p);
		int mid=l+r>>1;
		int res=0;
		if(L<=mid) res+=query(p<<1,l,mid,L,R);
		if(R>mid) res+=query(p<<1|1,mid+1,r,L,R);
		return res;
	}
	int qmax(int p,int l,int r,int L,int R){
		if(l>=L&&r<=R){
			return maxn[p];
		}
		pushdown(p,l,r);
		pushup(p);
		int mid=l+r>>1;
		int res=0;
		if(L<=mid) res=max(res,qmax(p<<1,l,mid,L,R));
		if(R>mid) res=max(res,qmax(p<<1|1,mid+1,r,L,R));
	}
}T[100],t[100]; 
int n,m,k;
int ans;
int a[100][10010];
int f[100][10010];
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			a[i][j]=read();
		}
		T[i].build(1,1,m,a[i]);
	}
	for(int i=1;i+k-1<=m;++i){
		f[1][i]=T[1].query(1,1,m,i,i+k-1)+T[2].query(1,1,m,i,i+k-1);
	}
	t[1].build(1,1,m,f[1]);
	for(int i=2;i<=n;++i){
		for(int j=1;j<=k;++j){
			t[i-1].update(1,1,m,max(j-k+1,1),j,-a[i][j]);
		}
		f[i][1]=t[i-1].qmax(1,1,m,1,m)+T[i].query(1,1,m,1,k)+T[i+1].query(1,1,m,1,k);
		for(int j=2;j+k-1<=m;++j){
			t[i-1].update(1,1,m,max(j-k,1),j-1,a[i][j-1]);
			t[i-1].update(1,1,m,j,j+k-1,-a[i][j+k-1]);
			f[i][j]=t[i-1].qmax(1,1,m,1,m)+T[i].query(1,1,m,j,j+k-1)+T[i+1].query(1,1,m,j,j+k-1); 
		}
		t[i].build(1,1,m,f[i]);
	}
	print(t[n].qmax(1,1,m,1,m));
	return 0;
}
```

---

