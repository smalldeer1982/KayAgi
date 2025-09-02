# Il Derby della Madonnina

## 题目描述

米兰德比即将上演，你被选为比赛的助理裁判，负责在场边移动，密切关注比赛中的越位位置和其他违规行为。

在意大利，足球极其重要，因此需要你尽可能长时间地密切关注比赛中的每一次踢球。为了实现这一点，你希望尽可能多地监控这些踢球。你能够密切监控某次踢球，当且仅当踢球发生时你距离踢球位置最近。

幸运的是，专家分析师已经精确预测了比赛中的所有踢球事件。你获得了两个整数列表 $ t_1, \ldots, t_n $ 和 $ a_1, \ldots, a_n $，分别表示从比赛开始到第 $ i $ 次踢球的时间为 $ t_i $ 秒，以及必须在场边位置 $ a_i $ 才能密切监控第 $ i $ 次踢球。

比赛开始时，你位于位置 0，你每秒最多可以在场边移动 $ v $ 个单位。那么，你能密切监控的最大踢球次数是多少？

## 说明/提示

在第一个样例中，你可以在前 $ 3.5 $ 秒内以最大速度向右移动到位置 $ 7 $，等待第一次踢球发生，然后立即再以最大速度向右移动去监控第二次踢球在位置 $ 17 $。在监控完第二次踢球后，由于时间限制无法赶到第三次踢球的位置，因此最多可以密切监控 $ 2 $ 次踢球。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 2
5 10 15
7 17 29```

### 输出

```
2```

## 样例 #2

### 输入

```
5 1
5 7 8 11 13
3 3 -2 -2 4```

### 输出

```
3```

## 样例 #3

### 输入

```
1 2
3
7```

### 输出

```
0```

# 题解

## 作者：Tmbcan (赞：4)

## [CF1662L Il Derby della Madonnina](https://www.luogu.com.cn/problem/CF1662L)

### 题目描述

有 $n$ 个点，第 $i$ 个点在 $t_i$ 时出现在 $a_i$ 位置然后消失。你第 $0$ 秒时在位置 $0$，速度为 $v$，问最多能赶上多少个点出现。

### 思路

设 $dp_j$ 表示到了第 $j$ 个点，且能赶上点 $j$ 的时候，最多能赶上多少点，

则 $dp_j = \max_{i=0}^{j-1}\{ dp_i \space [v \cdot (t_j-t_i) \ge \lvert x_j-x_i \rvert ]\}+1$。


当 $i<j$ 有 $t_i < t_j$，所以 $v \cdot (t_j-t_i) = \lvert v \cdot t_j - v \cdot t_i \rvert$，

可以把限制条件看作点 $A \space (v \cdot t_i,x_i)$ 与点 $B \space (v \cdot t_j,x_j)$ 两点的切比雪夫距离为其横坐标的距离，且 $B$ 在 $A$ 右侧。画出来图像这样，蓝色区域是 $B$ 点的限制区域。

![](https://cdn.luogu.com.cn/upload/image_hosting/8ufvfgcy.png)

我们发现，$B$ 点的范围是个边缘与坐标轴夹 $\frac {\pi}{4} $ 的半平面交，这个边缘不与坐标轴垂直很烦，所以我们将坐标系顺时针旋转 $\frac {\pi}{4} $。

![](https://cdn.luogu.com.cn/upload/image_hosting/3enn06gp.png)

原坐标系 $(x,y)$ 对应新坐标系 $(x\cos(- \frac {\pi}{4} )+y\sin(- \frac {\pi}{4} ),y\cos(- \frac {\pi}{4} ) - x\sin(- \frac {\pi}{4} ))$。  
我们实际只在乎两点间的相对位置，将坐标轴整体扩大 $\cos(- \frac {\pi}{4} )$ 后不会对限制产生影响。  
现在原坐标系的点 $(x,y)$ 对应新坐标系的 $(x-y,x+y)$。

新坐标系下，$B$ 的限制变为了需在 $A$ 的右上部分。

不难发现，原问题变为了求平面最长不下降链，起始点强制为 $(0,0)$，二维偏序即可。

### 代码


```cpp
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
int n,ans,cnt;
ll v,t[N],a[N],dp[N];
struct node{
	ll x,y;
	inline int operator < (const node&G) const{
		if(x^G.x) return x < G.x;
		return y < G.y;
	}
}g[N];
int main(){

	scanf("%lld%lld",&n,&v);
	for(int i=1;i<=n;++i) scanf("%lld",t+i);
	for(int i=1;i<=n;++i){
		scanf("%lld",a+i); // 求新坐标系下点的坐标
		g[i].x = v*t[i]-a[i];
		g[i].y = v*t[i]+a[i];
	}
	g[++n] = {0,0};
	sort(g+1,g+1+n); // 排序掉第一维
	for(int i=1;i<=n;++i){ // 只留下(0,0)能到达的点
		if(g[i].x>=0 && g[i].y>=0) g[++cnt] = g[i];
	}
	for(int i=1;i<=cnt;++i){ // 第二维求最长不下降子序列
		if(dp[ans]<=g[i].y) dp[++ans] = g[i].y;
		else *upper_bound(dp+1,dp+1+ans,g[i].y) = g[i].y;
	}
	printf("%d",ans-1); // 减去强制选的(0,0)
	
	return 0;
}

```

---

## 作者：wgyhm (赞：2)

## Description

有 $n$ 个点，在时刻 $t_i$ 时出现在 $a_i$ 位置上。

你的最大速度为 $v$ 。时刻 $0$ 时的位置在 $0$。

求最多有几个点能在出现时处在其位置上。

## Solution

设 $f_i$ 为第 $i$ 点出现时在 $a_i$ 上时的最多答案。

$f_i=\max\limits_{j=0}^{i-1} \{f_j(|a_i-a_j|\le v(t_i-t_j)\}$

考虑优化。

$|a_i-a_j|\le v(t_i-t_j)$ 等价于 $v(t_j-t_i)\le a_i-a_j\le v(t_i-t_j)$

整理得

$$\begin{cases}v\cdot t_j+a_j\le v\cdot t_i+a_i\\v\cdot t_j-a_j\le v\cdot t_i-a_i\\t_j<t_i\end{cases}$$

三维数点。

考虑到如果第一个第二个条件成立，那么第三个条件也同样成立。所以只需要二位数点。树状数组解决即可。

#### code

```cpp
#include<bits/stdc++.h>
#define maxn 400005
#define int long long
#define put() putchar('\n')
using namespace std;
inline void read(int &x){
	int f=1;x=0;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
	x*=f;
}
int n,v,t[maxn],a[maxn],tot,dp[maxn];
struct yyy{
	int x,y,id;
}h[maxn];
int g[maxn*2];
inline bool cmp(yyy x,yyy y){return x.x==y.x?x.y<y.y:x.x<y.x;}
struct BIT{
	#define lowbit(x) ((x)&(-x))
	int f[maxn];
	BIT(void) {memset(f,-0x3f,sizeof(f));}
	inline void add(int x,int y) {for (;x<=tot;x+=lowbit(x)) f[x]=max(f[x],y);}
	inline int query(int x) {int ans=-1e9;for (;x;x-=lowbit(x)) ans=max(f[x],ans);return ans;}
}tr;
signed main(void){
	int i,ans=0,flag=0;
	read(n);read(v);
	for (i=1;i<=n;i++) read(t[i]);t[0]=0;
	for (i=1;i<=n;i++) read(a[i]);a[0]=0;
	for (i=0;i<=n;i++) h[i].x=a[i]+1ll*v*t[i],h[i].y=1ll*v*t[i]-a[i],g[++tot]=h[i].y;
	sort(g+1,g+1+tot);tot=unique(g+1,g+1+tot)-g-1;
	for (i=0;i<=n;i++) h[i].id=i,h[i].y=lower_bound(g+1,g+1+tot,h[i].y)-g;
	sort(h,h+1+n,cmp);
    for (i=0;i<=n;i++) {
    	dp[i]=tr.query(h[i].y)+1;
    	if (h[i].x==0&&g[h[i].y]==0) dp[i]=0,tr.add(h[i].y,dp[i]);
		tr.add(h[i].y,dp[i]);
		ans=max(ans,dp[i]);
	}
	printf("%lld ",ans);
	return 0;
}
```



---

## 作者：I_am_Accepted (赞：2)

将每一个 Kick 看作二维平面上的点。若一个 Kick 在时间 $t$，在位置 $x$，人的速度为 $v$，则 Kick 的坐标为

$$
(v\cdot t,x)
$$

这样，当人现在在坐标 $(x,y)$（当然人初始坐标为 $(0,0)$），她能够赶到的 Kick 在她的右上 $45^{\circ}$ 到右下  $45^{\circ}$ 的半平面交里。

![](https://cdn.luogu.com.cn/upload/image_hosting/yzfdwk0w.png)

（↑样例中的三个 Kick 坐标）

当然，这样还是难于计算，我们将所有点按原点顺时针旋转 $45^{\circ}$。具体地，我们将每一个坐标

$$
(x,y)\to (x+y,-x+y)
$$

（这样每个点到原点的距离会扩大至原来的 $\sqrt2$ 倍，但是无伤大雅不影响计算）

这样每个平面上的点能到达的区域为右下角 $90^{\circ}$ 的半平面交。

![](https://cdn.luogu.com.cn/upload/image_hosting/04krnyjd.png)

（↑三个 Kick 坐标进行变换）

我们将 Kick 按照当前坐标排序，先按 $x$ 升序，次按 $y$ 降序。

这样排序在后的 Kick 不可能赶到排序在前的 Kick，满足了 DP 的**无后效性**。

设 $f_i$ 表示当前在排序后第 $i$ 个 Kick 的位置上，最多能看几个 Kick（包括 $i$ 本身）。

然后从后往前 $n\to1$ 枚举 Kick，其

$$
f_i=\max_{j\in[i+1,n],y_j\le y_i}f_j+1
$$

我们用 BIT（树状数组）维护每个 $y$，$f_j(\text{s.t.}\ y_j=y)$ 的最大值（当然 $y$ 坐标要离散化）。

即可 $O(n\log n)$ 求解所有 $f$。最后 $O(n)$ 枚举第一个看的 Kick 求答案即可。 

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 200010
#define Pos pair<int,int>
#define low (x&(-x))
int n,lim,b[N],c[N];
Pos a[N];
void add(int x,int y){
	while(x<=lim){
		ckmx(c[x],y);
		x+=low;
	}
}
int que(int x){
	int res=0;
	while(x){
		ckmx(res,c[x]);
		x-=low;
	}
	return res;
}
bool cmp(Pos x,Pos y){
	if(x.fir!=y.fir) return x.fir<y.fir;
	else return x.sec>y.sec;
}
signed main(){IOS;
	int x,y;
	cin>>n>>x;
	For(i,1,n) cin>>a[i].fir;
	For(i,1,n) cin>>a[i].sec;
	a[0]=mkp(0,0);
//	For(i,0,n) cout<<i<<":"<<a[i].fir<<" "<<a[i].sec<<endl; cout<<endl;
	For(i,0,n) a[i].fir*=x;
	For(i,0,n){
		x=a[i].fir+a[i].sec;
		y=a[i].sec-a[i].fir;
		a[i]=mkp(x,y);//rotate 45 clockwise
	}
	For(i,0,n) b[i+1]=a[i].sec;
	sort(b+1,b+2+n);
	lim=unique(b+1,b+2+n)-b-1;
	For(i,0,n) a[i].sec=lower_bound(b+1,b+1+lim,a[i].sec)-b;
	int qx=a[0].fir,qy=a[0].sec;
	sort(a,a+1+n,cmp);
	Rof(i,n,0){
		x=que(a[i].sec);
		if(a[i].fir==qx && a[i].sec==qy){
			cout<<x<<endl;
			return 0;
		}
		add(a[i].sec,x+1);
	}
return 0;}
```



---

