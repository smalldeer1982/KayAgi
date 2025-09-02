# Rorororobot

## 题目描述

There is a grid, consisting of $ n $ rows and $ m $ columns. The rows are numbered from $ 1 $ to $ n $ from bottom to top. The columns are numbered from $ 1 $ to $ m $ from left to right. The $ i $ -th column has the bottom $ a_i $ cells blocked (the cells in rows $ 1, 2, \dots, a_i $ ), the remaining $ n - a_i $ cells are unblocked.

A robot is travelling across this grid. You can send it commands — move up, right, down or left. If a robot attempts to move into a blocked cell or outside the grid, it explodes.

However, the robot is broken — it executes each received command $ k $ times. So if you tell it to move up, for example, it will move up $ k $ times ( $ k $ cells). You can't send it commands while the robot executes the current one.

You are asked $ q $ queries about the robot. Each query has a start cell, a finish cell and a value $ k $ . Can you send the robot an arbitrary number of commands (possibly, zero) so that it reaches the finish cell from the start cell, given that it executes each command $ k $ times?

The robot must stop in the finish cell. If it visits the finish cell while still executing commands, it doesn't count.

## 样例 #1

### 输入

```
11 10
9 0 0 10 3 4 8 11 10 8
6
1 2 1 3 1
1 2 1 3 2
4 3 4 5 2
5 3 11 5 3
5 3 11 5 2
11 9 9 10 1```

### 输出

```
YES
NO
NO
NO
YES
YES```

# 题解

## 作者：litachloveyou (赞：10)

首先我们很容易想到，当起始点与目标点的横坐标距离和纵坐标距离不是 $k$ 的倍数时，是永远无法移动到目标点的。

------------
题目的障碍物布置很有特点，是从下往上的，也就是说，越往上，障碍物就越少。**于是我们可以先往上移动到可以移动的最上面**，再进行横向移动，只需要跟移动区间内最“高”的障碍物比较是否能经过就可以了。因为题目有说明起始点和目标点没有障碍物，也就是说目标点的**上方**和起始点的**上方**是没有障碍物的。

------------
那么每一次如何查询区间内最“高”的障碍物呢，我们可以使用稀疏表来快速查询静态区间内的最值。

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll a[N][30];
ll query(ll l, ll r)
{
	ll k = log2(r - l + 1);
	return max(a[l][k], a[r - (1 << k)+1][k]);
}
void solve()
{
	ll n, m;
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%lld", &a[i][0]);
	}
	for (int j = 1; j <= 27; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= m; i++)
		{
			a[i][j] = max(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
		}
	}
	int q;
	scanf("%d", &q);
	while (q--)
	{
		ll x1, y1, x2, y2, k;
		scanf("%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &k);
		if (abs(x1 - x2) % k != 0|| abs(y1 - y2) % k != 0)
			puts("NO");
		else
		{
			ll dis = n - x1;
			dis = (dis / k) * k + x1;
			if (y2<y1)swap(y1, y2);
			if (query(y1, y2) >= dis)
				puts("NO");
			else
				puts("YES");
		}
	}
}
int main()
{
	int T = 1;
	//scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：3)

### 1 视频题解

![](bilibili:BV1GW4y127vj)

### 2 思路

很明显，机器人应该先尽可能上到最上面，再进行左右行走到目标列，再向下走到目标点。

首先，我们要让机器人尽可能靠近第 $n$ 行。具体计算方法请参见代码。

然后，我们要让机器人进行左右行走，这是最关键的一步。

我们通过线段树，求出开始列和目标列及其之间的 $a$ 的最大值，如果机器人在左右行走时不能比它高，就直接判断无解。

否则，我们还要进行同余性判断。要求开始行和目标行同余，开始列和目标列同余。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_m 200000
#define inf 10000000007//1e10+7
int n;
int m;
long long a[max_m+2];
long long tr[max_m<<2];
int q;
void build(int o,int l,int r){
	if(l>=r){
		tr[o]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	tr[o]=max(tr[o<<1],tr[o<<1|1]);
}
long long query(int o,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr)return tr[o];
	int mid=(l+r)>>1;
	long long res=-inf;
	if(ql<=mid)res=max(res,query(o<<1,l,mid,ql,qr));
	if(qr>mid)res=max(res,query(o<<1|1,mid+1,r,ql,qr));
	return res;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1709D_1.in","r",stdin);
	freopen("CF1709D_1.out","w",stdout);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)scanf("%lld",a+i);
	build(1,1,m);
	scanf("%d",&q);
	for(int i=1;i<=q;++i){
		long long sx,sy,ex,ey,k;
		scanf("%lld%lld%lld%lld%lld",&sx,&sy,&ex,&ey,&k);
		if(sy>ey){
			swap(sx,ex);
			swap(sy,ey);
		}
		sx=sx+((n-sx)/k)*k;
		if(query(1,1,m,sy,ey)>=sx){
			printf("NO\n");
			continue;
		}
		if((ey-sy)%k>0||sx<ex||(sx-ex)%k>0)printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80713226)

By **dengziyue**

---

## 作者：linyuhuai (赞：1)

[长文~~真心推荐~~前往blog获得更好的阅读体验](https://by505244.github.io/oi_blogs/2022/07/23/CF1709D题解) & [原题链接](https://codeforces.com/contest/1709/problem/D)

~~感觉可能是最简单（？）的2D吧，没啥思维难度~~

### 题意：

机器人在一个 $n\times m$ 的地图上行驶。但这个地图第 $j$ 列的前 $a_j$ 行有障碍物遮挡。你可以操纵这个机器人上下左右移动。但是，这个机器人是坏的，他会把所有命令重复执行 $k$ 次。比如你让他向下移动一格，机器人会移动 $k$ 格。现在给定起始坐标 $(x_s,y_s)$ 和终点坐标 $(s_f,y_f)$（保证坐标上一定没有障碍物），求是否能到达。

### 思路：

因为机器人只能走 $k$ 
的倍数距离，所以机器人从 $x_1,y_1$ 前往 $x_2,y_2$ 必须满足

$$
\left \{\begin{aligned}|x_1-x_2|\\|y_1-y_2|\end{aligned}\right.\mod k=0
$$

再考虑障碍，机器人必须走到 $(\max_{i=y_s}^
{y_f}a_i)+1$ 行及以上才能保证跨越中间所有障碍。

再考虑地图边界和上面得出的结论，得出如果能到达，则需要存在一个数 $x_3((\max_{i=y_s}^
{y_f}a_i)+1\leq x_3\le n)$ 使得 $\left\{\begin{aligned}|x_3-x_s|\\|x_3-x_y|\end{aligned}\right.\mod k=0$

我们令 $x_3=n-x_s-((n-x_s)\mod k)$（即满足 $|x_3-x_s|\mod k=0$ 时 $x_3$ 能够达到的最大值）为什么要到最大值，因为 $x_3$ 在小于等于 $n$ 的情况下越大越容易满足 $(\max_{i=y_s}^
{y_f}a_i)+1\leq x_3$ 这项条件。

不难证明如果 $x_3=n-x_s-((n-x_s)\mod k)$ 时依然小于 $(\max_{i=y_s}^
{y_f}a_i)+1$ 无法到达。

最后不要忘记判断 $|y_s-y_f|\mod k$ 是否为 $0$。

最坏复杂度为 $\mathcal{O}(mq)$ 再看范围发现通过不了。

发现以上算法的瓶颈在寻找区间最大值上，可以采用线段树进行优化至 $\mathcal{O}((m+q)\log m)$。（当然 ST 表也行）

```cpp
// Problem: D. Rorororobot
// Contest: Educational Codeforces Round 132 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1709/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
 
#include<bits/stdc++.h>
#define int long long
#define ls(x) (x<<1)
#define rs(x) ((x<<1)+1)
using namespace std;
int n,m,a[200005];
struct Node{
	int l,r,maxn;
}tree[1000005];
 
void bulid(int p,int l,int r){
	tree[p].l=l,tree[p].r=r;
	if(l==r){tree[p].maxn=a[l];return;}
	bulid(ls(p),l,(l+r)/2);
	bulid(rs(p),(l+r)/2+1,r);
	tree[p].maxn=max(tree[ls(p)].maxn,tree[rs(p)].maxn);
}
int ask(int p,int l,int r){
	if(tree[p].l>=l&&tree[p].r<=r){
		return tree[p].maxn;
	}
	int mid=(tree[p].l+tree[p].r)/2,maxn=0;
	if(l<=mid)maxn=ask(ls(p),l,r);
	if(r>mid)maxn=max(maxn,ask(rs(p),l,r));
	return maxn;
}
void solve(){
	int sx,sy,fx,fy,k;
	scanf("%lld%lld%lld%lld%lld",&sx,&sy,&fx,&fy,&k);
	int maxn=ask(1,min(sy,fy),max(sy,fy));
	int d=(n-sx)/k;
	d*=k,d+=sx;
	//printf("%d %d",maxn,d);
	if(d<=maxn||(d-fx)%k!=0||abs(sy-fy)%k!=0||maxn>=d){
		puts("NO");
	}else puts("YES");
}
 
signed main(){
	scanf("%lld%lld",&n,&m);
	//printf("%d\n",(int)log(m));
	for(int i=1;i<=m;i++)scanf("%lld",&a[i]);
	bulid(1,1,m);
	int q;
	scanf("%lld",&q);
	while(q--){
		solve();
	}
}


```


---

## 作者：__vector__ (赞：1)

### UPD：已修正格式错误。
### 题外话：  
写一篇题解纪念第一次于 Div.2 切 D。  
### 题意  
给你一个 $n$ 行，$m$ 列的网格，每一列**底部**都有 $a_i$ 个障碍。  
有 $q$ 次询问，每次询问给定一个起始坐标 $(x_s,y_s)$，一个终点坐标 $(x_f,y_f)$，以及一个正整数 $k$。    
注意这里的 $x$ 代表第几行，$y$ 代表第几列。  
你可以向前，向后，向左或向右走，但是每次都必须走 $k$ 步，并且不能走出网格或通过障碍。  
问能否从起点走到终点。  

$1 \le n \le 10^9$  
$1 \le m \le 2 \cdot 10^5$  
$1 \le q \le 2 \cdot 10^5$  
$1 \le k \le 10^9$  
保证给出的起点，终点不会在网格以外。  
### 做法  
来画一张图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/5m8mdtn2.png?x-oss-process=image/resize,m_lfit,h_700,w_700)  
红色的障碍，绿色是起点，蓝色是终点。  

显然，如果到达不了，怎么绕圈子都没有用。  

先考虑一般的步骤，就是先向上走，避开障碍（到达一个没有障碍存在的行），然后向右走，走到终点所在的列，然后向下走到终点。  

但是现在必须走 $k$ 步，所以有可能无法从起点到达没有障碍的那一行。  
为了尽可能避开障碍，应该贪心的走到**能走到的**最高的，且不会越界的行。  
显然这一行的行数就是 $(n-x_s) \bmod k$。  
设 $maxh$ 代表起始列到终点列（$y_s$ 到 $y_f$）中最高的障碍的高度。  
若 $(n-x_s) \bmod k \ge n - maxh$，那么说明无论如何都无法到达没有障碍的那一行，也就无法避开障碍到达终点的那一列，所以无解。  
下一步就是判断从起点列能否通过走 $k$ 的倍数步到达 终点列，显然，如果 $\lvert y_f-y_s \rvert$ 不是 $k$ 的倍数，那么一定走不到。  
最后，如果起始点与终点的高度差不是 $k$ 的倍数，那么仍然无解。  

注：区间最高障碍可以用 st 算法求。  
### Code  
```cpp  
#include <bits/stdc++.h>
using namespace std;
namespace Main
{
    const int maxn=2e5+5;
    int n,m;
    int a[maxn];
    int q;
    int st[19][maxn];
    int log[maxn];
    void main()
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=m;i++)
        {
            st[0][i]=a[i];
        }
        for(int i=2;i<=m;i++)
        {
            log[i]=log[i>>1]+1;
        }
        for(int i=1;i<=18;i++)
        {
            for(int j=1;j<=m-(1<<i)+1;j++)
            {
                st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
        scanf("%d",&q);
        while(q--)
        {
            int x1,x2,y1,y2,k;
            scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&k);
            if(y2<y1)swap(y2,y1);
            int lo2=log[y2-y1+1];
            int imax=max(st[lo2][y1],st[lo2][y2-(1<<lo2)+1]);
            //起始列到终点列最高障碍
            int sy=n-imax;//最高障碍离顶部有多少行
            bool flag=1;
            int sy2=(n-x1)%k;//最高能到达第几行
            if(sy2>=sy)
            {//第一步判断
                flag=0;
            }
            if(abs(y2-y1)%k!=0)
            {//第二步判断
                flag=0;
            }
            if(abs(x2-x1)%k!=0)
            {//第三步判断
                flag=0;
            }
            if(flag)printf("YES\n");
            else printf("NO\n");
        }
    }
}
int main()
{
    Main::main();
    return 0;
}  
```

---

## 作者：codemap (赞：0)

## 题目分析
机器人的最佳移动方案即为向上移动到不能向上为止，然后移动到目标列，再向下移动，所以我们只需判断此方案是否合法。

首先显然当$x_s \mod q \ne x_t \mod q$ 或 $y_s \mod q \ne y_t \mod q$ 时，显然无法到达。

然后发现为了可以到达，对于任意 $i \in [y_s,y_t]$， $n-a_i$ 均需小于机器人可达到的最小行数，即为 $(n-x_t) \mod k +1$，而 $a_i$ 的区间最大值可以用 ST 表来维护，即可做。
## 代码
```cpp
#include<iostream>
using namespace std;
int f[200001][22],log2[200001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m,q,i,j,p=1,xs,ys,xt,yt,k;
    cin>>n>>m;
    for(i=1;i<=m;i++)
    {
        cin>>f[i][0];
        //求log
        if(i==p*2)
        {
            log2[i]=log2[i-1]+1;
            p=i;
        }
        else
            log2[i]=log2[i-1];
    }
    for(i=1;i<=21;i++)
        for(j=1;j<=m-(1<<i)+1;j++)
            f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
    cin>>q;
    for(i=1;i<=q;i++)
    {
        cin>>xs>>ys>>xt>>yt>>k;
        if(xs%k!=xt%k||ys%k!=yt%k)
        {
            cout<<"NO\n";
            continue;
        }
        if(ys>yt)
            swap(ys,yt);//保证ys更小
        if(n-max(f[ys][l],f[yt-(1<<l)+1][l])<(n-xt)%k+1)
        {
            cout<<"NO\n";
            continue;
        }
        cout<<"YES\n";
    }
    return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先我们可以想到，机器人应该先往上走到能走到的最上面，然后往两边走，然后往下走。这样，就可以确保机器人不能走到被封禁（原文是 `blocked`）的方块（因为这些方块都在底部）。

显然，如果水平距离除以 $k$ 的余数不等于 $0$，或者垂直距离除以 $k$ 的余数不等于 $0$，本题无解。

判断掉这一点后，我们就可以算出机器人能走到多高的地方。公式是 $x3=\left\lfloor\frac{(n-x1)}{k}\right\rfloor\times k+x1$。其实 $x1$ 换成 $x2$ 也可以。

公式详解：机器人当前位置距离最顶部是有一定距离的，$n-x1$ 是为了求出这个距离，然后接下来的整除 $k$、乘 $k$ 是为了得出机器人最大可向上移动多大距离，加上 $x1$ 求出最高坐标。

接着，求区间最大值，即被封禁方块在 $y1$ 与 $y2$ 之间最高为多少，判断即可。这一步可以使用线段树。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
struct node
{
	int l,r;
	int max_num;
}tree[1000005];
int n,m,q;
int a[200005];
void update(int o)//标准的线段树
{
	tree[o].max_num=max(tree[o<<1].max_num,tree[o<<1|1].max_num);
}
void build(int o,int l,int r)
{
	tree[o].l=l;
	tree[o].r=r;
	if(l==r)
	{
		tree[o].max_num=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	update(o);
}
int query(int o,int l,int r)
{
	if(tree[o].l==l&&tree[o].r==r)
	{
		return tree[o].max_num;
	}
	int mid=(tree[o].l+tree[o].r)>>1;
	if(mid>=r)
	{
		return query(o<<1,l,r);
	}
	else if(mid<l)
	{
		return query(o<<1|1,l,r);
	}
	else
	{
		return max(query(o<<1,l,mid),query(o<<1|1,mid+1,r));
	}
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld",&a[i]);
	}
	build(1,1,m);
	scanf("%lld",&q);
	while(q--)
	{
		int x1,y1,x2,y2,k;
		scanf("%lld%lld%lld%lld%lld",&x1,&y1,&x2,&y2,&k);
		if(y1>y2)//判断y1和y2的大小，确保y1<=y2
		{
			int temp=y1;
			y1=y2;
			y2=temp;
			temp=x1;
			x1=x2;
			x2=temp;
		}
		if(((x1-x2)%k)!=0||((y1-y2)%k)!=0)
		{
			printf("NO\n");
			continue;
		}
		int x3=(n-x1)/k*k+x1;//求出最高位置
		//printf("%lld %lld %lld\n",y1,y2,query(1,y1,y2));
		if(x3<=query(1,y1,y2))
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
	return 0;
}

```

---

## 作者：_Remake_ (赞：0)

## 题目分析
由题意可知每一列被封锁的方格都是从下到上排列的，也就是说我们可以尽可能向上走，从而减少经过被封锁的方格的可能性，因为不能离开这个网格，所以从起点出发能够到达的最大高度为 $x_s+(\left \lfloor(n-x_s) /k \right \rfloor\times k)$。

在读入每一个询问时，我们可以先对起点和终点的坐标进行检验，如果不满足 $\operatorname{abs}(x_s - x_f)$ $\operatorname{mod}$ $k=0$ 或不满足 $\operatorname{abs}(y_s - y_f)$ $\operatorname{mod}$ $k=0$ 则无解。

对坐标进行检验之后，我们可以发现，仅当 $[\min(x_s,x_f),\max(x_s,x_f)]$ 区间内 $a_i$ 的最大值严格小于起点能够到达的最大高度时，才能够从起点到达终点。

考虑使用ST表维护静态区间最大值，得出 $[\min(x_s,x_f),\max(x_s,x_f)]$ 区间内 $a_i$ 的最大值。
## 代码

注:代码中已省略快读。

```cpp
#include<bits/stdc++.h>
using namespace std;
int A[300001],n,m;
int ST[300001][32];
int lg[300001];
int Query(int L,int R)//区间查询最大值
{
	int len=lg[(R-L+1)];
	return max(ST[L][len],ST[R-(1<<(len))+1][len]);
}
int main()
{
	lg[1]=0;
	n=read();
	m=read();
	for(int r=2;r<=m;r++)
	{
		lg[r]=lg[r>>1]+1;//预处理log2(r)下取整的值
	}
	for(int r=1;r<=m;r++)
	{
		ST[r][0]=read();
	}
	for(int len=1;len<=lg[m];len++)
	{
		for(int L=1;L+(1<<(len))-1<=m;L++)
		{
			ST[L][len]=max(ST[L][len-1],ST[L+(1<<(len-1))][len-1]);
		}
	}
	int Q;
	Q=read();
	int X1,X2,Y1,Y2,K;
	while(Q--)
	{
		X1=read();
		Y1=read();
		X2=read();
		Y2=read();
		K=read();
		if(abs(X2-X1)%K)//对坐标进行检验
		{
			cout<<"NO"<<endl;
			continue;
		}
		if(abs(Y2-Y1)%K)
		{
			cout<<"NO"<<endl;
			continue;
		}
		int MAX=X1+((n-X1)/K)*K;//从起点能够到达的最大高度
		//cout<<MAX<<endl;
		if(Query(min(Y1,Y2),max(Y1,Y2))<MAX)
		{
			//cout<<Query(min(Y1,Y2),max(Y1,Y2))<<endl;
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：sixrc (赞：0)

第一次打 CF，半夜场，脑子整蒙了犯了一个 sb 错误导致 WA……

---

考虑手玩这样一组数据：

$n=10,m=10,a$ 数组元素如下图标黄部分所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/m8usblb5.png)

记从下往上第 $x$ 行，从左往右第 $y$ 列为 $(x,y)$。

现在要从 start 点跳到 end 点，即从 $(3,5)$ 跳到 $(3,9)$。规定一次跳 $4$ 步，那我们应怎么跳呢？

首先发现一个结论：所有跳的方法等价于先往上、再往右、最后往下的跳法。证明很简单，因为多次跳一个方向也等价于一次跳一个方向。比如，上、右、上、右的跳法显然是等价于上、上、右、右的跳法的。

所以我们只要先往上跳，找到第一个能往右跳的地方就行了。比如说这组数据，第 $7$ 行就是第一个能往右跳的地方。但我们还不能跳，为什么？因为一次走四步，所以，我们需要找到第一个**能往右跳，且从开始点到当前点的步数为 $nk$ 的点**。比如说这组数据，第 $7$ 行是第一个能往右跳的地方，从开始点，即第 $3$ 行到第 $7$ 行步数刚好为 $4$，它就是合法的。

---

考虑一般性结论。

令起始点为第 $l$ 列，终点为第 $r$ 列，规定 $l \le r$。第一个能往右边跳的点满足什么性质？右边没有障碍。或者说，这个点的高度要 $> \max_{i=l+1}^ra_i$。这个可以用 ST 表预处理出来（或者不嫌烦打线段树也行）接着找到第一个能跳且从起始点跳到这里步数为 $nk$ 的点，进行简单判断即可。这部分主要是细节问题，具体实现可以看代码。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, m, q, s, x, y, X, Y, k, now, a[200010], f[200010][20], Log[200010];
const int Logn = 19;
int main(){
	Log[0] = -1;
	scanf ("%d%d", &n, &m);
	for (int i=1; i<=m; i++){
		scanf ("%d", &a[i]);
		f[i][0] = a[i];
		Log[i] = Log[i>>1] + 1;
	}
	for (int j=1; j<=Logn; j++){
		for (int i=1; i+(1<<j)-1<=m; i++){
			f[i][j] = max(f[i][j-1], f[i+(1<<j-1)][j-1]);
		}
	}
	scanf ("%d", &q);
	while (q --){
		scanf ("%d%d%d%d%d", &x, &y, &X, &Y, &k);
		if (y > Y){
			swap(y, Y);
			swap(x, X);
		}
		int yy = y + 1, YY = Y;
		if (yy <= YY){
			int tmp = Log[YY - yy + 1];
			s = max(f[yy][tmp], f[YY-(1<<tmp)+1][tmp]);
		}
		else s = 0;
		if ((Y - y) % k){//横着不能跳 
			puts ("NO");
			continue;
		}
		now = x;
		if (s >= now && s){
			int div = (s - now) / k, yu = (s - now) % k;
			if (yu) div ++;
			now = now + div * k;
			if (now == s) now += k;//now就是第一个能跳且跳到此步数为nk的点 
		}
		if (now > n){
			puts ("NO");//第一个点超出边界 
			continue;
		}
		int cha2 = abs(now - X);//跳到终点的步数 
		if (cha2 % k == 0) puts ("YES");
		else puts ("NO");
	}
	return 0;
}
```

---

