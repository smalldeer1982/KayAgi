# [ABC374D] Laser Marking

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc374/tasks/abc374_d

$ xy $ 平面に対し、レーザを照射しながら線分を印字する印字機があります。

- 印字開始時、レーザ照射位置は座標 $ (0,\ 0) $ にある。
- 線分を印字する際は、以下の流れに従う。
  
  
  - まず、レーザ照射位置を線分の端点のうちどちらか $ 1 $ つに移動させる。
      - どちらの端点から描画を始めてもよい。
  - その後、レーザ照射位置のある端点からもう一方の端点まで、レーザを照射しながらレーザ照射位置を一直線に移動させる。
      - 線分の途中で印字を中止することは許されない。
- レーザを照射していない時、レーザ照射位置は $ 1 $ 秒あたり速度 $ S $ で任意の方向に移動できる。
- レーザを照射している時、レーザ照射位置は $ 1 $ 秒あたり速度 $ T $ で印字中の線分に沿って移動できる。
- レーザ照射位置の移動にかかる時間以外の所要時間は無視できる。

高橋君はこの印字機で $ N $ 本の線分を印字したいです。  
そのうち $ i $ 本目の線分は、座標 $ (A_i,\ B_i) $ と座標 $ (C_i,\ D_i) $ を結びます。  
なお、複数の線分が重なっていることがありますが、全ての線分についてその都度重なっている部分を印字する必要があります。

うまく印字機を操作したとき、全ての線分を印字完了するまでにかかる最小の時間は何秒ですか？

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 6 $
- $ 1\ \le\ T\ \le\ S\ \le\ 1000 $
- $ -1000\ \le\ A_i,B_i,C_i,D_i\ \le\ 1000 $
- $ (A_i,B_i)\ \neq\ (C_i,D_i) $ ( $ 1\ \le\ i\ \le\ N $ )

### Sample Explanation 1

\- レーザを照射しながらレーザ照射位置を $ (0,0) $ から $ (0,2) $ まで移動させ、 $ 2 $ 本目の線分を描画する。 - この描画に要する時間は $ 2 $ 秒である。 - レーザを照射せずレーザ照射位置を $ (0,2) $ から $ (1,3) $ まで移動させる。 - この移動に要する時間は $ \sqrt{2}/2 $ 秒である。 - レーザを照射しながらレーザ照射位置を $ (1,3) $ から $ (2,1) $ まで移動させ、 $ 1 $ 本目の線分を描画する。 - この描画に要する時間は $ \sqrt{5} $ 秒である。 - レーザを照射せずレーザ照射位置を $ (2,1) $ から $ (2,0) $ まで移動させる。 - この移動に要する時間は $ 1/2 $ 秒である。 - レーザを照射しながらレーザ照射位置を $ (2,0) $ から $ (3,0) $ まで移動させ、 $ 3 $ 本目の線分を描画する。 - この描画に要する時間は $ 1 $ 秒である。 - 全体の所要時間は $ 2\ +\ (\sqrt{2}/2)\ +\ \sqrt{5}\ +\ (1/2)\ +\ 1\approx\ 6.443175 $ 秒です。

### Sample Explanation 3

複数の線分が重なっていますが、全ての線分についてその都度重なっている部分を印字する必要があります。

## 样例 #1

### 输入

```
3 2 1
1 3 2 1
0 2 0 0
3 0 2 0```

### 输出

```
6.44317475868633722080```

## 样例 #2

### 输入

```
2 1 1
0 0 10 10
0 2 2 0```

### 输出

```
20.97056274847714058517```

## 样例 #3

### 输入

```
6 3 2
-1000 -1000 1000 1000
1000 -1000 -1000 1000
-1000 -1000 1000 1000
1000 -1000 -1000 1000
1000 1000 -1000 -1000
-1000 1000 1000 -1000```

### 输出

```
9623.35256169626864153344```

## 样例 #4

### 输入

```
6 10 8
1000 1000 -1000 -1000
1000 -1000 -1000 -1000
-1000 1000 1000 1000
-1000 1000 -1000 -1000
1000 1000 1000 -1000
1000 -1000 -1000 1000```

### 输出

```
2048.52813742385702910909```

# 题解

## 作者：Zhao_daodao (赞：6)

# D - Laser Marking

## Description

在平面直角坐标系中，有 $n$ 条线段，线段由 $(A_i,B_i)$ 到 $(C_i,D_i)$。

你有一个画画机器，这个机器需要在图中画下每一个线段。

这个机器初始时在 $(0,0)$，画下一个线段的方式是**移动到一条线段的一侧，再沿着线段画到线段的另一侧**。

不在画画的时候机器的运动速度是 $S$ 单位每秒，画画的时候运动速度是 $T$ 单位每秒。

求机器画画的时间的最小值。

线段重合也要画两次。

## Solution

题目恐怖如斯，但是数据范围非常友好，只有 `6`。

所以直接枚举线段的先后顺序，再枚举每一条线段画画的方向。

枚举完之后直接计算答案，取最小值就可以了。

复杂度 $O(n!\times 2^n\times n)$。

---

## 作者：zeroflows (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc374_d)

## 思路

注意一下数据范围。

- $1 \le n \le 6$

**首先想到 dfs。**

---

按照题意，先算出位置到线段的一段所需的时间。\
再算出画线段所需的时间，就行了。\
输出后发现与答案不一样，~~没关系~~，只要小数后六位是对的就行了。\
记得要分情况，看先移动的线段的那一头。

---

## 代码

```cpp
#include<bits/stdc++.h>
using namespace zh;
double ans=double(LLONG_MAX);
bool v[100];
int a[10000],b[10000],c[10000],d[10000];
int n,s,t;
void dfs(int x,int y,int z,double ss)
{
	if(z==n)
	{
		ans=min(ans,ss);
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(!v[i])
		{
			v[i]=1;
			double q1=sqrt(double(a[i]-x)*double(a[i]-x)+double(b[i]-y)*double(b[i]-y));
			double q2=sqrt(double(a[i]-c[i])*double(a[i]-c[i])+double(b[i]-d[i])*double(b[i]-d[i]));
			dfs(c[i],d[i],z+1,ss+q1/s+q2/t);
			q1=sqrt(double(c[i]-x)*double(c[i]-x)+double(d[i]-y)*double(d[i]-y));
			dfs(a[i],b[i],z+1,ss+q1/s+q2/t);
			v[i]=0;
		}
	}
}
int main(){
	//	ios::sync_with_stdio(false);
	//	cin.tie(),cout.tie();
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i]>>c[i]>>d[i];
	dfs(0,0,0,0);
	printf("%.20lf",ans);
}
```

---

## 作者：fishing_cat (赞：4)

### 题意

起点 $(0,0)$，画 $n$ 条线段，有两个速度，分别表示在画线段时的速度和在不是线段上移动的速度。

可以从任一端点开始绘制，不允许在线段中间停止打印，可能会有多个重叠线段，但每次都必须打印所有线段的重叠部分。

### 思路

暴力枚举每一种画线顺序，枚举画线的每一个起始结点，时间复杂度 $O(n!\times 2 ^ n)$。

因为 $n$ 只有 $6$，所以可过。

### code


```cpp
#include<bits/stdc++.h>
#define ll long long

const ll inf = 1e16;
const double eps = 1e-10;

using namespace std;

ll n, s, t;
ll a[20],b[20],c[20],d[20];
double ans[20], num, knum = inf, kl;
ll dis[20];

void dfs(ll now, ll len, ll x, ll y) {
	if (len >= n) {
		knum = min(knum, kl);
		return ;
	}
	dis[now] = 1;
	for (int i = 1; i <= n; i++) {
		if (dis[i] == 1) continue;
		dis[i] = 1; 
		
		kl += sqrt(double(abs(x-c[i])*abs(x-c[i]) + abs(y-d[i])*abs(y-d[i]))) / double(s);
		dfs(i, len + 1, a[i], b[i]);
		kl -= sqrt(double(abs(x-c[i])*abs(x-c[i]) + abs(y-d[i])*abs(y-d[i]))) / double(s);
		
		kl += sqrt(double(abs(x-a[i])*abs(x-a[i]) + abs(y-b[i])*abs(y-b[i]))) / double(s);
		dfs(i, len + 1, c[i], d[i]);
		kl -= sqrt(double(abs(x-a[i])*abs(x-a[i]) + abs(y-b[i])*abs(y-b[i]))) / double(s);
		
		dis[i] = 0;
	}
}

int main() {
	read(n); read(s); read(t);
	for (int i = 1; i <= n; i++) {
		read(a[i]); read(b[i]); read(c[i]); read(d[i]);
		ans[i] = sqrt(double(abs(a[i]-c[i])*abs(a[i]-c[i]) + abs(b[i]-d[i])*abs(b[i]-d[i]))) / double(t);
		num += ans[i];
	} 
	for (int i = 1; i <= n; i++){
		double kp;
		for (int j = 1; j <= n; j++) 
			dis[j] = 0;
		kp = sqrt(double(abs(0-c[i])*abs(0-c[i]) + abs(0-d[i])*abs(0-d[i]))) / double(s);
		kl = kp;
		dfs(i, 1, a[i], b[i]);
		for (int j = 1; j <= n; j++) 
			dis[j] = 0;
		kp = sqrt(double(abs(0-a[i])*abs(0-a[i]) + abs(0-b[i])*abs(0-b[i]))) / double(s);
		kl = kp;
		dfs(i, 1, c[i], d[i]);
	}
	printf("%.10lf\n", num + knum);
 	return 0;
}
```

---

## 作者：Bobxing (赞：4)

注意到本题 $N$ 很小，考虑暴搜算法。

首先打印所需要的时间是无法避免的，可以先预处理下来。

然后暴力枚举全排列，并用二进制枚举从到达哪个端点，将所以方案枚举出来。

最后将两段时间相加得到答案。


```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define maxn 10
double ans = 0, anss = 0x3f3f3f3f;
int n, t, s, a[ maxn ];
struct node
{
    int a, b, c, d;
} seg[ maxn ];
double check( int t )
{
    double res = 0;
    double nowx = 0, nowy = 0;
    for( int i = 1; i <= n; i++ )
    {
        double x, y;
        if( t & ( 1 << ( i - 1 ) ) )
            x = nowx - seg[ a[ i ] ].a, y = nowy - seg[ a[ i ] ].b, nowx = seg[ a[ i ] ].c, nowy = seg[ a[ i ] ].d;
        else
            x = nowx - seg[ a[ i ] ].c, y = nowy - seg[ a[ i ] ].d, nowx = seg[ a[ i ] ].a, nowy = seg[ a[ i ] ].b;
        res += sqrt( x * x + y * y );
    }
    return res;
}
int main()
{
    cin >> n >> s >> t;
    for( int i = 1; i <= n; i++ )
        cin >> seg[ i ].a >> seg[ i ].b >> seg[ i ].c >> seg[ i ].d;
    for( int i = 1; i <= n; i++ )
    {
        int x = seg[ i ].c - seg[ i ].a;
        int y = seg[ i ].d - seg[ i ].b;
        ans += sqrt( x * x + y * y );
    }
    ans /= t;
    for( int i = 1; i <= n; i++ )
        a[ i ] = i;
    do
    {
        for( int i = 0; i < ( 1 << ( n + 1 ) ); i++ )
            anss = min( anss, check( i ) );
        //printf( "%.10lf\n", anss );
    } while( next_permutation( a + 1, a + n + 1 ) );
    printf( "%.10lf", ans + anss / s );
    return 0;
}

```
原谅我奇怪的马蜂~~~

---

## 作者：Cosine_Func (赞：3)

这是一道 ABC 的搜索好题。

题意：在平面直角坐标系上，有 $N$ 条线段，每条线段的端点分别是 $(A_i, B_i)$ 和 $(C_i, D_i)$。对于一个开始时位于坐标原点的动点，它在线段上的运动速度是 $T$，不在线段上时运动速度是 $S$。求动点从原点出发到完整经过每一条线段的最少用时。

数据范围 $1 \le N \le 6$，考虑 dfs。每次 dfs 时，要记录上一次是从哪一个点过来的，以便递归至下一层时计算。注意本题需要回溯。输出时建议输出至少小数点后 $8$ 位，虽然这道题目不卡精度，但是对于有浮点数的 SPJ 题目，最好养成这个习惯防止被卡。

主要代码如下：

```cpp
const int N=10;
int n,a[N],b[N],c[N],d[N];
double s,t,ans=LLONG_MAX;
bool vis[N];
void dfs(int dep,double res,int prex,int prey){
	if(dep==n){
		ans=min(ans,res);
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			double dis0=sqrt((a[i]-prex)*(a[i]-prex)+(b[i]-prey)*(b[i]-prey));
			double dis1=sqrt((c[i]-prex)*(c[i]-prex)+(d[i]-prey)*(d[i]-prey));
			double dis2=sqrt((a[i]-c[i])*(a[i]-c[i])+(b[i]-d[i])*(b[i]-d[i]));
			vis[i]=1;dfs(dep+1,res+dis0/s+dis2/t,c[i],d[i]);vis[i]=0;
			vis[i]=1;dfs(dep+1,res+dis1/s+dis2/t,a[i],b[i]);vis[i]=0;
		}
	}
}
inline void Solve(){
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i]>>c[i]>>d[i];
	dfs(0,0,0,0);
	cout<<fixed<<setprecision(14)<<ans;
}
```

[参考代码](https://atcoder.jp/contests/abc374/submissions/58478047)

---

## 作者：WuMin4 (赞：2)

## [\[ABC374D\] Laser Marking](https://atcoder.jp/contests/abc374/tasks/abc374_d)

## 题意

平面直角坐标系上有 $N$ 条线段，你的初始位置在 $(0,0)$。你需要画这 $N$ 条线段。当你没落笔时的移动速度为 $S$ 单位每秒，落笔时的速度为 $T$ 单位每秒，且画线段时必须从线段的一段画到另一端，问画完 $N$ 条线段的最小时间。

## 思路

$N\le 6$，很明显直接 dfs 即可。

dfs 时要注意以下细节：

- 记得将路程除以速度
- 记得重置选过的线段标记（回溯）
- 对于线段 $AB$ 可以从 $A$ 画到 $B$，也可以从 $B$ 画到 $A$，需要考虑 $2$ 次。

复杂度 $O(N!2^N)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define dis(x,y,xx,yy) (sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy)))
using namespace std;
int n,s,t;
double ans;
struct node{
	int x,y,xx,yy;
}a[15];
bool vis[15];
void dfs(int nw,int lx,int ly,double tot){
	if(nw==n+1){
		ans=min(ans,tot);
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=true;
			dfs(nw+1,a[i].xx,a[i].yy,tot+dis(lx,ly,a[i].x,a[i].y)/s+dis(a[i].x,a[i].y,a[i].xx,a[i].yy)/t);
			dfs(nw+1,a[i].x,a[i].y,tot+dis(lx,ly,a[i].xx,a[i].yy)/s+dis(a[i].x,a[i].y,a[i].xx,a[i].yy)/t);
			vis[i]=false;
		}
	}
}
signed main() {
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++)
		cin>>a[i].x>>a[i].y>>a[i].xx>>a[i].yy;
	ans=INT_MAX;
	dfs(1,0,0,0);
	printf("%.10lf",ans);
	return 0; 
}
```

---

## 作者：xxboyxx (赞：1)

### 题目翻译

给你 $n$ 条线段，让你从 $(0,0)$ 开始刚好画完这些线段（不能画在其他地方），顺序可以自己安排，给出绘画时的移动速度与不绘画时的移动速度，求最少画完这些线的时间。

### 思路

注意到 $n\le 6$，很小，所以可以进行暴力搜索，枚举绘画顺序。由于线可以从任意一端开始画，所以在枚举时需要记录一下从哪个端点开始绘画。最后模拟绘画过程即可。

### 注意

1. 一定要开 `long double`，否则精度会炸。

2. 如果要用 `printf` 输出，那么要写成 `Lf`。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double//一定要记住long double! 
using namespace std;
struct node
{
	double xa,ya,xb,yb;
};
int n;
double v1,v2,minn=1e9;
node a[1000005];
int b[1000005];
int f[1000005];
double query(double xa,double ya,double xb,double yb)//计算两点距离 
{
	double s=sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
	return s;
}
void dfs(int x)
{
	if (x==n+1)
	{
		double ans=0;
		double nx=0,ny=0;
		for (int i=1;i<=n;i++)//拟绘画过程 
		{
			double k=query(nx,ny,a[b[i]].xa,a[b[i]].ya)/v1;
			ans+=k;
			nx=a[b[i]].xb;
			ny=a[b[i]].yb;
			double p=query(a[b[i]].xa,a[b[i]].ya,nx,ny)/v2;
			ans+=p;
		}
		if (ans<minn)
			minn=ans;
		return;
	}
	for (int i=1;i<=n*2;i++)
	{
		int y;
		if (i<=n)//两种情况，但是线只有一条 
			y=i;
		else
			y=i-n;
		if (f[y]==0)
		{
			f[y]=1;
			b[x]=i;
			dfs(x+1);
			f[y]=0;
		}
	}
}
signed main()
{
	cin>>n>>v1>>v2;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i].xa>>a[i].ya>>a[i].xb>>a[i].yb;
		a[i+n].xa=a[i].xb;
		a[i+n].ya=a[i].yb;
		a[i+n].xb=a[i].xa;//要记录从哪一端开始 
		a[i+n].yb=a[i].ya;
	}
	dfs(1);
	printf("%.7Lf",minn);
	return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 题目大意

有 $n$ 条线，第 $i$ 条线从 $(a,b)$ 到 $(c,d)$，在线上的行走速度是 $t$，否则是 $m$，要求求出一种方案，把所有线给恰好经历一次，并且使得长度最短（两点之间是欧几里得距离）。

### 思路

由于 $n$ 特别小，我们可以通过枚举全排列来确定这 $n$ 条线的行走顺序，然后对于每一条线，我们枚举他从他的那一端进入，并对每种方案求出答案取最小值即可。

时间复杂度：$\Theta(n! \times 2^n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n,m,T;
int a[N],b[N],c[N],d[N];
int p[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m >> T;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		p[i] = i;
	}
	double res = 1e18;
	do{
		for (int i = 0; i < (1 << n); i ++ ){
			double cnt = 0;
			long long x = 0,y = 0;
			for (int j = 0; j < n; j ++ ){
				int t = p[j + 1];
				if (i >> j & 1){
					cnt += 1.0 * sqrt((x - a[t]) * (x - a[t]) + (y - b[t]) * (y - b[t]) * 1.0) / m;
					cnt += 1.0 * sqrt((c[t] - a[t]) * (c[t] - a[t]) + (d[t] - b[t]) * (d[t] - b[t]) * 1.0) / T;
					x = c[t],y = d[t];
				}
				else{
					cnt += 1.0 * sqrt((x - c[t]) * (x - c[t]) + (y - d[t]) * (y - d[t]) * 1.0) / m;
					cnt += 1.0 * sqrt((c[t] - a[t]) * (c[t] - a[t]) + (d[t] - b[t]) * (d[t] - b[t]) * 1.0) / T;
					x = a[t],y = b[t];
				}
			}	
			res = min(res,cnt);
		}
	}while (next_permutation(p + 1,p + 1 + n));
	printf("%.15lf",res);
	return 0;
}
```

---

## 作者：kkxacj (赞：1)

#### 思路

发现 $n$ 很小，考虑全排列看第 $i$ 次执行那条线段，同时在枚举每个的结尾在哪个端点。

全排列可以用函数 `next_permutation` 可以解决，其含义是将全排列从小到大排序后，假设当前是第 $i$ 个，将其变为第 $i+1$ 个，若已经是最后一个则返回 `false`，至于求每个的结尾在哪个端点用 `dfs` 暴力跑即可。

**注意：`next_permutation` 求的是下一个，第一个要提前算一遍。**

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
int n,a[10],b[10],c[10],d[10],f[10],v[10];
double ans = 1e9,s,t;
double get(int x,int y,int x1,int y1){return (double)sqrt(1.0*(x-x1)*(x-x1)+(y-y1)*(y-y1));}
inline void solve()
{
	double sum = 0; 
	if(v[1] == 1) sum += get(c[f[1]],d[f[1]],0,0)/s;
	else sum += get(a[f[1]],b[f[1]],0,0)/s;
	for(int i = 1;i <= n;i++)
	{
		sum += get(a[f[i]],b[f[i]],c[f[i]],d[f[i]])/t;
		if(i != n)
		{//v_i结尾是否是a,b 
			if(v[i] == 1 && v[i+1] == 1) sum += get(a[f[i]],b[f[i]],c[f[i+1]],d[f[i+1]])/s;
			if(v[i] == 1 && v[i+1] == 0) sum += get(a[f[i]],b[f[i]],a[f[i+1]],b[f[i+1]])/s;
			if(v[i] == 0 && v[i+1] == 1) sum += get(c[f[i]],d[f[i]],c[f[i+1]],d[f[i+1]])/s;
			if(v[i] == 0 && v[i+1] == 0) sum += get(c[f[i]],d[f[i]],a[f[i+1]],b[f[i+1]])/s;
		}
	}
	ans = min(ans,sum);
}
void dfs(int x)
{
	if(x > n)
	{
		solve();
		return;
	}
	v[x] = 0,dfs(x+1);
	v[x] = 1,dfs(x+1);
}
signed main()
{
	read(n); cin >> s >> t;
	for(int i = 1;i <= n;i++) read(a[i]),read(b[i]),read(c[i]),read(d[i]);
	for(int i = 1;i <= n;i++) f[i] = i;
	dfs(1);
	while(next_permutation(f + 1,f + 1 + n))
	{
		dfs(1);
	}
	printf("%.13f",ans);
	return 0;
}
/*
0 0 10 10 10
0 2 2 0 2sqrt(2)
*/
```

---

## 作者：stripe_python (赞：0)

D 最暴力的一集。

直接枚举全排列，然后套二进制枚举，枚举每个线段从 $(x_1,y_1)$ 走还是从 $(x_2,y_2)$ 走。然后简单模拟。复杂度 $O(n2^nn!)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, h[15];
double s, t;
struct pos {
	double x1, y1, x2, y2;
} a[15];

double dis(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void _main() {
	cin >> n >> s >> t;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
	}
	iota(h + 1, h + n + 1, 1);
	double res = 1e18;
	do {
		for (int S = 0; S < (1 << n); S++) {
			double cur = 0.0, cx = 0.0, cy = 0.0;
			for (int i = 1; i <= n; i++) {
				if (S >> (i - 1) & 1) {
					cur += dis(cx, cy, a[h[i]].x1, a[h[i]].y1) / s;
					cur += dis(a[h[i]].x1, a[h[i]].y1, a[h[i]].x2, a[h[i]].y2) / t;
					cx = a[h[i]].x2, cy = a[h[i]].y2;
				} else {
					cur += dis(cx, cy, a[h[i]].x2, a[h[i]].y2) / s;
					cur += dis(a[h[i]].x2, a[h[i]].y2, a[h[i]].x1, a[h[i]].y1) / t;
					cx = a[h[i]].x1, cy = a[h[i]].y1;
				}
			}
			res = min(res, cur);
		}
	} while (next_permutation(h + 1, h + n + 1));
	cout << fixed << setprecision(12) << res;
} 
```

---

## 作者：cqbzcjh (赞：0)

数据范围极小，$1\ \le\ N\ \le\ 6$，很容易看出这是**搜索**。

我用的是 dfs。需要注意，线段的两个端点都需要遍历。遍历线段时记得把坐标移到另一个端点。只用对线段打标记判重即可。

具体的实现请看代码。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10;
int n;
double s,t,ans=1e9;
bool vis[N];
struct segment{
	int a,b,c,d;
	double len;
}se[N];
//计算距离
double cal(double a,double b,double c,double d){
	return sqrt(fabs(a-c)*fabs(a-c)+fabs(b-d)*fabs(b-d));
}
void dfs(int x,int y,int id,double res,int d){
	//x,y坐标，id线段的编号，res为当前答案，d为已经遍历了的线段数量
	//遍历当前线段
	res+=(se[id].len/t);
	d++;
	if(x==se[id].a&&y==se[id].b){
		x=se[id].c;
		y=se[id].d;
	}else{
		x=se[id].a;
		y=se[id].b;
	}
	if(d==n){
		if(res<ans)ans=res;
		return;
	}
	//移动到下一线段，注意线段两个端点都要遍历
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			double dis=cal(x,y,se[i].a,se[i].b);
			vis[i]=1;
			dfs(se[i].a,se[i].b,i,res+(dis/s),d);
			dis=cal(x,y,se[i].c,se[i].d);
			dfs(se[i].c,se[i].d,i,res+(dis/s),d);
			vis[i]=0;
		}
	}
}
int main(){
	cin>>n>>s>>t;
	for(int i=1;i<=n;i++){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		se[i]={a,b,c,d,cal(a,b,c,d)};
	}
	//从起点开始移动
	for(int i=1;i<=n;i++){
		double dis=cal(0,0,se[i].a,se[i].b);
		vis[i]=1;
		dfs(se[i].a,se[i].b,i,(dis/s),0);
		dis=cal(0,0,se[i].c,se[i].d);
		dfs(se[i].c,se[i].d,i,(dis/s),0);
		vis[i]=0;
	}
	printf("%.7lf",ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题意
有一台印刷机要通过发射激光在平面上打印 $N$ 条线段。

打印开始时，激光位置位于坐标 $(0, 0)$ 。

在打印线段时，应遵循以下步骤。

- 首先，将激光位置移动到线段的一个端点（可以从任一端点开始绘制）。
- 然后，在发射激光的同时，将激光位置从当前端点直线移动到另一个端点（允许在线段中间停止打印）。
- 不发射激光时，激光位置可以以每秒 $S$ 个单位的速度向任意方向移动。
- 发射激光时，激光位置可以以每秒 $T$ 个单位的速度沿打印线段移动。
- 激光位置移动以外的操作所需的时间可以忽略。

高桥希望用这台印刷机印刷 $N$ 条线段。

第 $i$ 条线段两端点坐标是 $(A_i, B_i)$ 和 $(C_i, D_i)$ 。

有些线段可能会重叠，在这种情况下，他需要分别打印每个线段的重叠部分。

当他以最佳方式操作印刷机时，完成所有线段的印刷至少需要多少秒？

## 数据范围
所有输入值均为整数。

$1 \le N \le 6$

$1 \le T \le S \le 1000$

$-1000 \le A_i,B_i,C_i,D_i \le 1000$

$(A_i,B_i) \neq (C_i,D_i)(1 \leq i \leq N)$

## 分析
$N \leq 6$ 可以先用全排列枚举打印线段的顺序。

由于每条线段有 $2$ 个端点，再枚举每条线段从哪个端点开始打印。

接下来就简单了，在枚举从哪的端点开始打印时，不必使用搜索，枚举 $S \in [0,2^n-1]$。

在二进制下，若 $S$ 的第 $i$ 位为 $0$，则表示第 $i$ 条线段从 $(A_{p_i},B_{p_i})$ 开始打印，反之，从 $(C_{p_i},D_{p_i})$ 开始打印。（$p_i$ 为全排列数组）

## Code
```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define X first
#define Y second
#define que queue
#define sta stack
#define bit bitset
#define vec vector
#define gtt getchar
#define grt greater
#define p_b push_back
#define m_p make_pair
#define int long long
#define ptt(x) putchar(x)
#define pii pair<int,int>
#define Pq priority_queue
#define mem(a,x) memset(a,x,sizeof a)
#define mep(a,b) memcpy(a,b,sizeof a)
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,b,a) for(int i=b;i>=a;i--)
#define eg(i,u) for(auto i:e[u])
#define local
using namespace std;
template<typename T>void rd(T &x){
    x=0;
    int f=1;
    char ch=gtt();
    for(;ch<'0'||ch>'9';ch=gtt()) if(ch=='-') f=-1;
    for(;ch>='0'&&ch<='9';ch=gtt()) x=(x<<1)+(x<<3)+(ch^48);
    x*=f;
}
void wr(char s){ptt(s);}
void wr(const char *s){printf("%s",s);}
template<typename T>void wr(T x){
    if(x<0) ptt('-'),x=-x;
    if(x>9) wr(x/10);
    ptt(x%10+'0');
}
template<typename T,typename ...Args>void rd(T &x,Args &...args){rd(x);rd(args...);}
template<typename T,typename ...Args>void wr(T x,Args ...args){wr(x);wr(args...);}
const int N=10;
int n,s,t;
int p[N],vis[N];
int a[N],b[N],c[N],d[N];
long double ans=1e9,len[N];
bool ck(int s,int j){ // 判断二进制位
	return ((s>>(j-1))&1);
}
long double dis(int xo,int yo,int xp,int yp){ // 求两点距离
	return sqrt(pow(xo-xp,2)+pow(yo-yp,2));
}
void dfs(int x){ // 枚举全排列
	if(x>n){
		fz(i,0,(1<<n)-1){
			long double tm=0;
			fz(k,1,n){
				int j=p[k],l=p[k-1];
				if(!ck(i,k)){ // 从 (a[j],b[j]) 开始打印
					if(k==1) tm+=dis(a[j],b[j],0,0)/s+len[j]/t;
					else if(!ck(i,k-1)) tm+=dis(a[j],b[j],c[l],d[l])/s+len[j]/t; // 上一个已经打印了，坐标应反着来
					else tm+=dis(a[j],b[j],a[l],b[l])/s+len[j]/t; // 上一个已经打印了，坐标应反着来
				}
				else{ // 从 (c[j],d[j]) 开始打印
					if(k==1) tm+=dis(c[j],d[j],0,0)/s+len[j]/t;
					else if(!ck(i,k-1)) tm+=dis(c[j],d[j],c[l],d[l])/s+len[j]/t; // 上一个已经打印了，坐标应反着来
					else tm+=dis(c[j],d[j],a[l],b[l])/s+len[j]/t; // 上一个已经打印了，坐标应反着来
				}
			}
			ans=min(ans,tm);
		}
		return;
	}
	fz(i,1,n)
		if(!vis[i]){
			p[x]=i;
			vis[i]=1;
			dfs(x+1);
			vis[i]=0;
		}
}
signed main(){
#ifndef local
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	rd(n,s,t);
	fz(i,1,n) rd(a[i],b[i],c[i],d[i]),len[i]=dis(a[i],b[i],c[i],d[i]);
	dfs(1);
	printf("%.7Lf",ans);
    return 0;
}

---

## 作者：smart_kai (赞：0)

### 提示
- 提示1：$n \le 6$，数据范围很小，考虑搜索。
- 提示2：对于两点 $(x_1,y_1)$ 和 $(x_2,y_2)$，两点之间的距离为 $\sqrt{(x_1-x_2)^2 + (y_1-y_2)^2}$。
- 提示3：对于每次搜索，遍历的是已经选中的线段个数。对于剩下没被选中的线段，枚举之后递归。
- 提示4：枚举线段的时候应该枚举线段的两个端点，然后到达的是线段的另一端。

### 说明
设当前的下标位置为 $(nx,ny)$，枚举到的线段为 $(x,y)-(a,b)$，线段的长度为 $len$，打印线段速度为 $t$，任意移动的速度为 $s$。并根据**提示2**，设两点 $(x_1,y_1)$ 和 $(x_2,y_2)$ 的距离为 $f(x_1,y_1,x_2,y_2)$。
- 如果从线段的 $(x,y)$ 出发，那么走完这条线段需要 $\frac{f(x,y,nx,ny)}{s} + \frac{len}{t}$ 的时间，到达点 $(a,b)$。
- 如果从线段的 $(a,b)$ 出发，那么走完这条线段需要 $\frac{f(a,b,nx,ny)}{s} + \frac{len}{t}$ 的时间，到达点 $(x,y)$。


### 代码
```cpp
double ans = 2147483646.0;
int n, s, t, x[10], y[10], a[10], b[10];
double len[10];
bool vis[10];

void dfs(int i, int nx, int ny, double na)
{
    if (i == n+1)
    {
        ans = min(ans, na);
        return ;
    }
    if (na > ans) return ;
    for (int it = 1; it <= n; it++)
    {
        if (vis[it]) continue;
        vis[it] = 1;
        dfs(i+1, a[it], b[it], na + sqrt((x[it]-nx)*(x[it]-nx) + (y[it]-ny)*(y[it]-ny))*1.0/s + len[it]/t);
        dfs(i+1, x[it], y[it], na + sqrt((a[it]-nx)*(a[it]-nx) + (b[it]-ny)*(b[it]-ny))*1.0/s + len[it]/t);
        vis[it] = 0;
    }
}

void solve()
{
    cin >> n >> s >> t;
    for (int i=1; i<=n; i++) cin >> x[i] >> y[i] >> a[i] >> b[i];
    for (int i=1; i<=n; i++) len[i] = sqrt((x[i]-a[i])*(x[i]-a[i]) + (y[i]-b[i])*(y[i]-b[i]));
    dfs(1, 0, 0, 0.0);
    cout << fixed << setprecision(10) << ans;
    cout << "\n";
}

```

---

## 作者：yegengghost (赞：0)

该题的笑点就是：$1\le N \le 6$。

也就是说，我们可以用 ```next_permutation``` 来暴力解决问题。

其实含金量也没多少，就是暴力。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114;
const int mod=1;
int ksm(int x,int k)
{
	int ans=1,base=x;
	while(k)
	{
		if(k&1) ans=1ll*ans*base%mod;
		base=1ll*base*base%mod; k>>=1;
	}
	return ans;
}
int read()
{
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
int n;
double s,t,a[N],b[N],c[N],d[N];
int num[N];
double ans=1e10;
int cnt;
double dis(double a,double b,double c,double d)
{
	return 1.0*sqrt((a-c)*(a-c)*1.0+(b-d)*(b-d)*1.0);
}
void find_ans(int numm,double x,double y,double now)
{
	if(numm==n+1)
	{
		if(now<ans)
			ans=now;
		return ;
	}
	int val=num[numm];
	find_ans(numm+1,a[val],b[val],now+dis(x*1.0,y*1.0,c[val],d[val])/(1.0*s)+dis(c[val],d[val],a[val],b[val])/(1.0*t));
	find_ans(numm+1,c[val],d[val],now+dis(x*1.0,y*1.0,a[val],b[val])/(1.0*s)+dis(a[val],b[val],c[val],d[val])/(1.0*t));
	return ;
	
}
signed main()
{
	n=read();
	s=read();
	t=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read(),num[i]=i;
	do
	{
		find_ans(1,0.0,0.0,0.0);
	}while(next_permutation(num+1,num+1+n));
	printf("%.10lf\n",ans);
	return 0;
}
```

---

## 作者：Luxe877 (赞：0)

~~这届 ABC 搜索题挺多啊！~~

## 题目大意
有一种激光打印机，通过发射激光在平面直角坐标系上打印线段。

打印开始时，激光位于 $(0,0)$ 位置上。打印这些线段时要按照如下流程打印：

- 先将激光移动到一条线段的一个端点处，
  - 打印线段可以从任意一个端点开始打印
- 然后，在发射激光的同时，将激光位置从当前端点沿直线移动到另一个端点。
  - 不允许在线段中间停止打印

当不发射激光时，激光可以以每秒 $S$ 个单位向任意方向移动；发射激光时，激光可以以每秒 $T$ 个单位向任意方向移动。除了移动激光之外，其他操作所需的时间可忽略不计。

现在高桥君要用这种打印机打印这 $N$ 条线段。其中第 $i$ 条线段的两个端点分别为 $(A_i,B_i)$ 和 $(C_i,D_i)$。注意有的线段可能会相交或有重叠部分，这时要分别打印重叠的部分。

当高桥君以最优方式打印线段时，所用的最小时间是多少？

## 解题思路
乍一看可能是比较奇怪的算法，但是注意到 $1 \le N \le 6$，意味着端点数最多只有 $12$ 个，那么就可以直接 dfs，枚举每个线段及其开始打印的端点。结合两点间距离公式，就可以做出此题了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,s; 
int a[12],b[12],c[12],d[12];
int pos[12];
double ans=0;
double getdis(double x,double y,double u,double v)//from(x,y)to(u,v); 
{
	return sqrt((u-x)*(u-x)+(v-y)*(v-y));
}
bool vis[12];
void dfs(int p,double x,double y,double tt)
{
//	cout<<p<<" "<<x<<" "<<y<<" "<<tt<<endl;
	if(p>n)
	{
		ans=min(tt,ans);
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])//draw i-th line
		{
			vis[i]=true;
			dfs(p+1,c[i]*1.0,d[i]*1.0,tt+getdis(x,y,a[i]*1.0,b[i]*1.0)/(t*1.0)+getdis(c[i]*1.0,d[i]*1.0,a[i]*1.0,b[i]*1.0)/(s*1.0));//draw from (a,b) to (c,d)
			dfs(p+1,a[i]*1.0,b[i]*1.0,tt+getdis(x,y,c[i]*1.0,d[i]*1.0)/(t*1.0)+getdis(c[i]*1.0,d[i]*1.0,a[i]*1.0,b[i]*1.0)/(s*1.0));//draw from (c,d) to (a,b)
			vis[i]=false;
		}
	}
}
int main()
{
	cin>>n>>t>>s;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d %d %d %d",&a[i],&b[i],&c[i],&d[i]);
		pos[i]=i;
	}
	ans=1e9;
	dfs(1,0.00,0.00,0.000000);
	printf("%.9lf",ans);
	return 0;
}
/*


*/
```

---

## 作者：Liuhy2996 (赞：0)

## 题意
有一台打印机在二维平面上打印线段，不打印时的速度是 $S$ 米每秒，打印时的速度是 $T$ 米每秒，问打印 $N$ 条线段最少时间是多少。
## 思路
因为 $N\le6$，所有直接枚举打印顺序和每条线段的打印方向就行。
## 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,inf=1e15;
int n,s,t,a[N],b[N],c[N],d[N],p[7]={0,1,2,3,4,5,6};
double ans=inf;
double len(int a,int b,int c,int d){
	return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}
signed main(){
	cin>>n>>s>>t;
	for(int i=0;i<n;++i) cin>>a[i]>>b[i]>>c[i]>>d[i];
	for(int j=0;j<1<<n;++j){ //枚举方向
		for(int k=0;k<n;++k)
			if((j>>k)&1) swap(a[k],c[k]),swap(b[k],d[k]);
		do{
			int x=0,y=0;
			double sum=0;
			for(int i=0;i<n;++i) sum+=len(x,y,a[p[i]],b[p[i]])/s+len(a[p[i]],b[p[i]],c[p[i]],d[p[i]])/t,x=c[p[i]],y=d[p[i]];
			ans=min(ans,sum);
		}while(next_permutation(p,p+n)); //枚举顺序
		for(int k=0;k<n;++k)
			if((j>>k)&1) swap(a[k],c[k]),swap(b[k],d[k]);
	}
	printf("%.10f",ans);
	return 0;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc374_d)
## 思路
我们发现按原排列打印不一定最优，按从 $(a,b)$ 到 $(c,d)$ 打印也不一定最优。我们又知道 $n \le 6$，十分小。可以考虑 dfs。

dfs 中，先枚举排列，再枚举每一道线从哪里开始，哪里结束。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 10;

int n;
double s, t, ans = (double)(2e9);
int a[N], b[N], c[N], d[N];
bool vis[N];

double calc(int x, int y, int x2, int y2)
{
	return sqrt(abs(x - x2) * abs(x - x2) + abs(y - y2) * abs(y - y2));
}

void dfs(int u, int lx, int ly, double res)
{
	if (u == n)
	{
		ans = min(ans, res);
		return;
	}
	for (int i = 1; i <= n; i++) // 枚举排列
	{
		if (vis[i]) continue;
		vis[i] = true;
		double dist = calc(lx, ly, a[i], b[i]), res2 = res;
		res += dist / s;
		dist = calc(a[i], b[i], c[i], d[i]);
		res += dist / t;
		dfs(u + 1, c[i], d[i], res);
		res = res2;
		dist = calc(lx, ly, c[i], d[i]);
		res += dist / s;
		dist = calc(c[i], d[i], a[i], b[i]);
		res += dist / t;
		dfs(u + 1, a[i], b[i], res);
		res = res2;
		vis[i] = false;
	}
}

int main()
{
	scanf("%d%lf%lf", &n, &s, &t);
	for (int i = 1; i <= n; i++)
		scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
	dfs(0, 0, 0, 0.0);
	printf("%.8lf\n", ans);
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/AT_abc374_d)

简单搜索。

直接搜索我们打印线段的顺序，然后，用 $2^n$ 来枚举要走到哪个端点即可。

然后模拟。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =21;
double sum=1e18;
int n,X[N],Y[N],XX[N],YY[N],c[N],a[N],S,T;
bool vis[N];
double Dis(double x2,double y2,double x3,double y3){
	return sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
}
void rcalc(){
	double nowx=0,nowy=0;
	double ans=0;
	for(int i=1;i<=n;i++){
		int now=a[i]; 
		double xx,yy;
		if(c[i]==0)	ans+=Dis(nowx,nowy,X[now],Y[now])/S,nowx=XX[now],nowy=YY[now];
		else	ans+=Dis(nowx,nowy,XX[now],YY[now])/S,nowx=X[now],nowy=Y[now];// 
		ans+=Dis(X[now],Y[now],XX[now],YY[now])/T;
	}
	sum=min(sum,ans);
}
void rdfs(int dis){
	if(dis==n+1){
		rcalc();
		return ;
	}
	c[dis]=0,rdfs(dis+1),c[dis]=1,rdfs(dis+1);
}
void dfs(int dis){
	if(dis==n+1){
		rdfs(1);
		return ;
	}
	for(int i=1;i<=n;i++)	if(vis[i]==false)	vis[i]=true,a[dis]=i,dfs(dis+1),vis[i]=false,a[dis]=0;
}
int main(){
	cin>>n>>S>>T;
	for(int i=1;i<=n;i++)	cin>>X[i]>>Y[i]>>XX[i]>>YY[i];
	dfs(1);
	cout<<fixed<<setprecision(15)<<sum<<endl;
}
```

---

## 作者：Redamancy_Lydic (赞：0)

[博客内食用更佳](https://www.cnblogs.com/Lydic/p/18448720)

看到 $n\le6$，就知道这道题又是一道搜索了。

题面有点长，信息也给的有点多，但稍微分析就可以得到只需要搜索印刷线段的顺序即可。

具体的，我们在深搜函数里面传 $4$ 个参数，分别代表已选线段的数量，当前位置的横纵坐标，以及当前时间。为了方便，我们表示的是已经印刷完当前线段后的时间。

我们可以先预处理出来每条线段净印刷所需的时间，用一个数组标记每条线段是否已经印刷。

搜索过程中我们枚举所有未印刷的线段，然后从这条线段的两头分别开始计算时间，因为数据很小，所以我们无需确定哪种方式最优。

距离计算就使用勾股定理即可。（这个肯定都会）

有一点需要注意，题目所有数据均为浮点数，代码中不要出现整型变量。

[提交记录](https://atcoder.jp/contests/abc374/submissions/58454967)

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个初始位置为 $(0,0)$ 的点 $P$，并且在一个二维平面上有 $N$ 条端点坐标分别为 $(A_i,B_i)$ 和 $(C_i,D_i)$ 的线段。首先，点 $P$ 可以以 $S$ 个单位长度每秒的速度移动到任意一个线段的端点上，然后再以 $T$ 个单位长度每秒的速度走到另一个端点上，要求走完所有的线段，求所用时间的最小值，数据范围 $N\le 6$。

## 解题思路

首先看到这个数据范围就可以想到用暴搜来解决（OIer 离不开暴搜就像鱼离不开水~），接着考虑搜索的参数。首先我们需要记录当前的位置，还要记录当前的状态 $chk$，当 $chk=0$ 的时候说明点 $P$ 要走到另一条线段上，否则当 $chk=i$ 时就说明点 $P$ 正在线段 $i$ 上走，并且记录当前剩下几条线段没有走（作为搜索的边界）和答案。对于答案的处理，只需要用 `double` 类型存储（精度要求也没有很高），最好是写个函数计算两点间的距离，最后只需对答案取最小值即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,s,t,a[7],b[7],c[7],d[7],bz[7];
double ans=INT_MAX;
double dist(ll x, ll y, ll p, ll q)
{return sqrt((x-p)*(x-p)+(y-q)*(y-q));}

void dfs(ll x, ll y, ll chk, ll rmd, double res)
{
    if(!rmd) {ans=min(ans,res); return;}

    if(!chk)
    {
        for(R int i=1; i<=n; ++i)
        {
            if(!bz[i])
            dfs(a[i],b[i],i,rmd,res+dist(x,y,a[i],b[i])/s),
            dfs(c[i],d[i],i,rmd,res+dist(x,y,c[i],d[i])/s);
        }
    }

    else
    {
        bz[chk]=1;
        if(c[chk]==x && d[chk]==y)
        dfs(a[chk],b[chk],0,rmd-1,res+dist(x,y,a[chk],b[chk])/t);
        else dfs(c[chk],d[chk],0,rmd-1,res+dist(x,y,c[chk],d[chk])/t);
        bz[chk]=0;
    }
}

int main()
{
    n=read(); s=read(); t=read();
    for(R int i=1; i<=n; ++i)
    a[i]=read(), b[i]=read(), c[i]=read(), d[i]=read();
    dfs(0,0,0,n,0); printf("%lf",ans);
    return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路
刚看到题面觉得有点难度，但又看到 $N\le6$ 又放心了。

DFS 枚举选择画线的顺序以及从线的哪个端点开始画，使用两点间距离公式 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$ 求出点与点之间的距离，在搜索中找最小值即可。

枚举画线顺序复杂度 $O(n!)$，枚举选择端点复杂度 $O(2^n)$，总复杂度 $O(n!\times2^n)$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, num[10], vis[10];
double s, t, a[10], b[10], c[10], d[10], x, y, dis1, dis2, dis, ans = 0x3f3f3f3f;
double dist(double a, double b, double c, double d) {
	return sqrtl((a - c) * (a - c) + (b - d) * (b - d));
}//距离公式
double calc(int dep, double ans, double x, double y) {
	if (dep > n) return ans;
	double ans1 = calc(dep + 1, ans + dist(a[num[dep]], b[num[dep]], c[num[dep]], d[num[dep]]) / t + dist(a[num[dep]], b[num[dep]], x, y) / s, c[num[dep]], d[num[dep]]);
	double ans2 = calc(dep + 1, ans + dist(a[num[dep]], b[num[dep]], c[num[dep]], d[num[dep]]) / t + dist(c[num[dep]], d[num[dep]], x, y) / s, a[num[dep]], b[num[dep]]);
	return min(ans1, ans2);
}//枚举端点
void dfs(int dep) {
	if (dep > n) {
		ans = min(ans, calc(1, 0, 0, 0));
		return ;
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			num[dep] = i;
			dfs(dep + 1);
			vis[i] = 0;
		}
	}
	return ;
}//枚举选边
signed main() {
	cin >> n >> s >> t;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
	}
	dfs(1);
	printf("%.10f", ans);
	return 0;
}
```

---

## 作者：Noah2022 (赞：0)

## 题目大意
>给你 $ n $ 个线段，第 $ i $ 个线段的两个端点为 $ ( a_i , b_i ) $ 以及 $ ( c_i , d_i ) $ 。求从 $ ( 0 , 0 ) $ 点开始，至少要多少秒才能画完所有的线段。且在不画线段时每秒走 $ S $ 个单位长度，在画激光时每秒走 $ T $ 个单位长度。

## 解题思路
考虑到 $ n \le 6 $ 故采用 dfs 进行，注意：在遍历每一次的时候可以从头开始扫，也可以从为开始扫。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,bj[10];
long double t,s;
long double min1=8437575943;
struct node{
	int a,b;
}g[25],g2[25];
inline long double jsjl(node k,node g)
{
	return hypot(abs(k.a-g.a),abs(k.b-g.b));
}
inline void dfs(int step,long double sum,node n1)
{
	if(step==n)
	{
		min1=min(min1,sum);
		return ;
	}
	for(register int i(1);i<=n;i=-~i)
	{
		if(!bj[i])
		{
			bj[i]=1;
			dfs(step+1,sum+jsjl(n1,g[i])/s+jsjl(g[i],g2[i])/t,g2[i]);
			dfs(step+1,sum+jsjl(n1,g2[i])/s+jsjl(g2[i],g[i])/t,g[i]);
			bj[i]=0;
		}
	}
}
int main()
{
	cin>>n>>s>>t;
	for(register int i(1);i<=n;i=-~i)
	{
		cin>>g[i].a>>g[i].b>>g2[i].a>>g2[i].b;
	}
	dfs(0,0,{0,0});
	cout<<fixed<<setprecision(15)<<min1;
	return 0;
}
```

---

