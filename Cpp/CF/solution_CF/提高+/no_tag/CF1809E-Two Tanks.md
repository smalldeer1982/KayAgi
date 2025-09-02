# Two Tanks

## 题目描述

There are two water tanks, the first one fits $ a $ liters of water, the second one fits $ b $ liters of water. The first tank has $ c $ ( $ 0 \le c \le a $ ) liters of water initially, the second tank has $ d $ ( $ 0 \le d \le b $ ) liters of water initially.

You want to perform $ n $ operations on them. The $ i $ -th operation is specified by a single non-zero integer $ v_i $ . If $ v_i > 0 $ , then you try to pour $ v_i $ liters of water from the first tank into the second one. If $ v_i < 0 $ , you try to pour $ -v_i $ liters of water from the second tank to the first one.

When you try to pour $ x $ liters of water from the tank that has $ y $ liters currently available to the tank that can fit $ z $ more liters of water, the operation only moves $ \min(x, y, z) $ liters of water.

For all pairs of the initial volumes of water $ (c, d) $ such that $ 0 \le c \le a $ and $ 0 \le d \le b $ , calculate the volume of water in the first tank after all operations are performed.

## 说明/提示

Consider $ c = 3 $ and $ d = 2 $ from the first example:

- The first operation tries to move $ 2 $ liters of water from the second tank to the first one, the second tank has $ 2 $ liters available, the first tank can fit $ 1 $ more liter. Thus, $ \min(2, 2, 1) = 1 $ liter is moved, the first tank now contains $ 4 $ liters, the second tank now contains $ 1 $ liter.
- The second operation tries to move $ 1 $ liter of water from the first tank to the second one. $ \min(1, 4, 3) = 1 $ liter is moved, the first tank now contains $ 3 $ liters, the second tank now contains $ 2 $ liter.
- The third operation tries to move $ 2 $ liter of water from the first tank to the second one. $ \min(2, 3, 2) = 2 $ liters are moved, the first tank now contains $ 1 $ liter, the second tank now contains $ 4 $ liters.

There's $ 1 $ liter of water in the first tank at the end. Thus, the third value in the fourth row is $ 1 $ .

## 样例 #1

### 输入

```
3 4 4
-2 1 2```

### 输出

```
0 0 0 0 0 
0 0 0 0 1 
0 0 1 1 2 
0 1 1 2 3 
1 1 2 3 4```

## 样例 #2

### 输入

```
3 9 5
1 -2 2```

### 输出

```
0 0 0 0 0 0 
0 0 0 0 0 1 
0 1 1 1 1 2 
1 2 2 2 2 3 
2 3 3 3 3 4 
3 4 4 4 4 5 
4 5 5 5 5 6 
5 6 6 6 6 7 
6 7 7 7 7 8 
7 7 7 7 8 9```

# 题解

## 作者：yshpdyt (赞：6)

## 题意
两个水桶 $A$，$B$，最大容量分别为 $a,b$，设桶内分别有 $c,d$ 升水，$n$ 次倒水操作：

- $v_i<0$ 将 $B$ 内 $\min(a-c,d,-v_i)$ 升水倒入 $A$。
- $v_i>0$ 将 $A$ 内 $\min(b-d,c,v_i)$ 的升水倒入 $B$。

求对于任意合法的初始水量 $(c,d)$，求出 $n$ 次操作后 $A$ 桶内的剩余水量。

## Sol
很有意思的题。

注意到对于确定的 $(c,d)$，其不管如何操作，$c+d$ 是不会变的，模拟倒水的过程，每次其实相当于把 $c+d$ 升水向 $A$ 偏一点，或向 $B$ 偏一点。

这个操作很像平移线段，如果把我们的操作刻画在数轴上（借用知乎用户 [@Ueanaya](https://www.zhihu.com/people/xihuan-xw) 几张图）：

![](https://pic3.zhimg.com/80/v2-696fe3257de7e6ff9e337c5c90f4be30_1440w.webp)

即对于蓝色线段（后续称为水条），其长度为 $c+d$，$A$ 桶的区间视为 $[-a,0]$，$B$ 桶的区间视为 $[0,b]$，原点视为每个桶的桶底。

考虑我们的平移操作，相当于每次左移右移水条，使得水条既不脱离原点，也不超过端点，考虑边界情况：
![](https://pic1.zhimg.com/80/v2-b9b235dc929484d69e73b8cea0e0ab42_1440w.webp)
![](https://pica.zhimg.com/80/v2-e7ea06d70b4f9de5792d54a9dde5e504_1440w.webp)
![](https://pic1.zhimg.com/80/v2-912a09cd02b47378e63669908b1699d2_1440w.webp)
![](https://pic4.zhimg.com/80/v2-51cd7fbc837293d1f14acf432f64711b_1440w.webp)

**这个过程适用于所有 $c+d$ 相同的初始情况，于是我们可以对所有 $c+d$ 相同的情况统计答案。**

考虑如何平移才能不越界，如果我们记 $c+d=x$，蓝条初始左右端点为 $[p,p+x]$，记 $sum_i$ 表示操作数组前缀和，于是根据图片有以下不等式关系：

$$\forall i\in[1,n],-a\le p+sum_i\le 0$$

$$\forall i\in[1,n],0 \le p+x+sum_i\le b$$

如果我们把 $sum_i$ 替换成前缀和最小值 $mi$ 和前缀和最大值 $mx$，就省去了枚举的步骤。

然后我们就得到了一段无论如何操作都不会越界的初始左端点范围：

$$l=\max(-a-mi,-x-mi)$$
$$r=\min(-mx,b-mx-x)$$

对 $p$ 的初始位置进行分类讨论：

- $l\le p\le r $，既然不会碰到边界，答案就是 $p+sum_n$。
- $-x\le p<l$，会碰到左边界，碰到后和 $l$ 之后的过程相同，答案就是 $res_l$。
- $r<p\le0$，会碰到右边界，碰到后和 $r$ 之后的过程，相同答案就是 $res_r$。

注意当 $x$ 很大时一定会碰到边界所以可能 $l>r$，此时$l$ 或 $r$ 答案不是简单的 $l+sum_n$ 或 $r+sum_n$，而是要模拟一遍倒水过程后得到的 $res_l,res_r$。

## Code
需要注意一些非法的 $p$ 导致越界：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 3005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;

ll n,a,b;
ll res[N][N],f[N*10];
ll mi[N*10],mx[N*10],sum[N*10];

ll calc(ll le,ll ri){
    for(int i=1;i<=n;i++){
        if(f[i]>0){
            ll p=min(b-ri,min(-le,f[i]));
            le+=p,ri+=p;
        }else{
            ll p=min(le+a,min(ri,-f[i]));
            le-=p,ri-=p;
        }
    }
    return -le;
}
void sol(ll x){
    ll l=max(-a-mi[n],-x-mi[n]),r=min(b-mx[n]-x,-mx[n]);
    for(int i=min(l,0ll);i<=min(r,0ll);i++)res[-i][x+i]=-i-sum[n];
    ll vall=calc(l,l+x);
    ll valr=calc(r,r+x);
    for(int i=-x;i<l&&i<=0;i++)res[-i][x+i]=vall;
    for(int i=max(r+1,-x);i<=0;i++)res[-i][x+i]=valr;
}
int main(){
    cin>>n>>a>>b;
    mi[0]=inf,mx[0]=-inf;
    for(int i=1;i<=n;i++){
        cin>>f[i];
        sum[i]=sum[i-1]+f[i];
        mi[i]=min(mi[i-1],sum[i]);
        mx[i]=max(mx[i-1],sum[i]);
    }
    for(int i=1;i<=a+b;i++)sol(i);
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++) cout<<res[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：Leasier (赞：5)

显然我们不能对每个 $(c, d)$ 分开暴力算，考虑对 $c + d$ 相同的项一起处理。

与 [[ARC149D] Simultaneous Sugoroku](https://www.luogu.com.cn/problem/AT_arc149_d) 类似地，注意到当某两个 $(c_1, d_1), (c_2, d_2)$ 在某一时刻处于同一位置，则他们此后的状态就一定完全相同。

于是一个直观的想法就是去维护现在位置不同的所有连续段，但事实上连续段个数是 $O(\max(a, b))$ 的，没法直接维护。

但很快你就会注意到其实完全没有必要这么做，因为连续段的构成事实上只有两种形式：

- 全局全部碰到过左 / 右侧，因而全部相同。
- 全局左边一部分碰到过左侧，右边一部分碰到过右侧，中间全部进行了 $\displaystyle\sum_{i = 1}^n v_i$ 的平移。

对碰到左 / 右侧的情况跑一遍暴力，平移的情况直接赋值即可。时间复杂度为 $O(n(a + b) + ab)$。

代码：
```cpp
#include <stdio.h>

int v[10007], ans[1007][1007];

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline int calc(int a, int b, int c, int d, int n){
	int ans = c;
	for (int i = 1; i <= n; i++){
		if (v[i] > 0){
			ans -= min(v[i], min(ans, b - (c + d - ans)));
		} else {
			ans += min(-v[i], min(c + d - ans, a - ans));
		}
	}
	return ans;
}

void write(int n){
	if (n >= 10) write(n / 10);
	putchar(n % 10 + '0');
}

int main(){
	int n, a, b, ab;
	scanf("%d %d %d", &n, &a, &b);
	ab = a + b;
	for (int i = 1; i <= n; i++){
		scanf("%d", &v[i]);
	}
	for (int i = 0; i <= ab; i++){
		int sum = 0, l = max(i - b, 0), L = l, r = min(i, a), R = r;
		for (int j = 1; j <= n; j++){
			sum -= v[j];
			L = max(L, max(-sum, i - b - sum));
			R = min(R, min(a - sum, i - sum));
		}
		if (L > R){
			int t = calc(a, b, l, i - l, n);
			for (int j = l; j <= r; j++){
				ans[j][i - j] = t;
			}
		} else {
			int t1 = calc(a, b, l, i - l, n), t2 = calc(a, b, r, i - r, n);
			for (int j = l; j < L; j++){
				ans[j][i - j] = t1;
			}
			for (int j = L; j <= R; j++){
				ans[j][i - j] = j + sum;
			}
			for (int j = R + 1; j <= r; j++){
				ans[j][i - j] = t2;
			}
		}
	}
	for (int i = 0; i <= a; i++){
		for (int j = 0; j <= b; j++){
			write(ans[i][j]);
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：729hao (赞：3)

[**luogu 传送门**](https://www.luogu.com.cn/problem/CF1809E) [**codeforces 传送门**](https://codeforces.com/problemset/problem/1809/E)

~~吉司机线段树板子题~~


---

## 思路
容易发现无论怎么操作，两个水桶的总水量不会变化，所以考虑将总和相同的情况一起考虑。

设总水量为 $w$，分 $v>0$ 和 $v<0$ 两种情况。

当 $v<0$ 时，第一个水桶会最多增加 $-v$ 的水量，有两种情况会影响它接收的水量：
1. 第一个桶的剩余空间不够，这时应该将第一个桶的水量与 $a$ 取 $\min$。
2. 第二个桶的水不够 $-v$，这时应该将第一个桶的水量与 $w$ 取 $\min$。

所以当 $v<0$ 时，先全局加 $-v$，再与 $\min(a,w)$ 取 $\min$。

$v>0$ 时同理，先减少 $v$ 的水量：
1. 第一个水桶水不够，与 $0$ 取 $\max$。
2. 第二个桶的剩余空间不够，与 $(w-b)$ 取 $\max$。

所以，我们要使用一种支持全局加，全局取 $\min$，全局取 $\max$ 的数据结构，吉司机线段树即可。

虽然所有操作都是全局，有单调性，但是~~无脑一点~~锻炼自己的码力，何乐而不为呢。

最终时间复杂度：$O(n(a+b)\log n)$。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace cs{
	#define LL long long
	#define fir first
	#define sec second
	typedef pair<int,int> PII;
	const int N=1e4;
	const int INF=2e9;
	int n,a,b,v[N+5],w,Beg,End,ans[1005][1005];
	struct Segment{
		int l,r;
		int ma,sma,mi,smi;
		int lzyadd,lzymax,lzymin;
		void init(){
			l=r=0;
			ma=sma=-INF;
			mi=smi=INF;
			lzyadd=0;
			lzymax=-INF;
			lzymin=INF;
		}
		void add(int d){
			ma+=d;
			if(sma!=-INF) sma+=d;
			mi+=d;
			if(smi!=INF) smi+=d;
			lzyadd+=d;
			if(lzymax!=-INF) lzymax+=d;
			if(lzymin!=INF) lzymin+=d;
		}
		void getmin(int d){
			if(ma<=d) return;
			ma=d;
			if(mi>=d){
				mi=d;
				smi=INF;
			}
			else if(smi>d) smi=d;
			if(lzymax>=d) lzymax=d;
			lzymin=d;
		}
		void getmax(int d){
			if(mi>=d) return;
			mi=d;
			if(ma<=d){
				ma=d;
				sma=-INF;
			}
			else if(sma<d) sma=d;
			if(lzymin<=d) lzymin=d;
			lzymax=d;
		}
	}Tree[4010];
	void Pushup(int id){
		Tree[id].ma=max(Tree[id<<1].ma,Tree[id<<1|1].ma);
		if(Tree[id<<1].ma>Tree[id<<1|1].ma){
			Tree[id].sma=max(Tree[id<<1].sma,Tree[id<<1|1].ma);
		}
		else if(Tree[id<<1|1].ma>Tree[id<<1].ma){
			Tree[id].sma=max(Tree[id<<1|1].sma,Tree[id<<1].ma);
		}
		else{
			Tree[id].sma=max(Tree[id<<1].sma,Tree[id<<1|1].sma);
		}
		Tree[id].mi=min(Tree[id<<1].mi,Tree[id<<1|1].mi);
		if(Tree[id<<1].mi<Tree[id<<1|1].mi){
			Tree[id].smi=min(Tree[id<<1].smi,Tree[id<<1|1].mi);
		}
		else if(Tree[id<<1|1].mi<Tree[id<<1].mi){
			Tree[id].smi=min(Tree[id<<1|1].smi,Tree[id<<1].mi);
		}
		else{
			Tree[id].smi=min(Tree[id<<1].smi,Tree[id<<1|1].smi);
		}
	}
	void Pushdown(int id){
		if(Tree[id].lzyadd){
			Tree[id<<1].add(Tree[id].lzyadd);
			Tree[id<<1|1].add(Tree[id].lzyadd);
			Tree[id].lzyadd=0;
		}
		if(Tree[id].lzymax!=-INF){
			Tree[id<<1].getmax(Tree[id].lzymax);
			Tree[id<<1|1].getmax(Tree[id].lzymax);
			Tree[id].lzymax=-INF;
		}
		if(Tree[id].lzymin!=INF){
			Tree[id<<1].getmin(Tree[id].lzymin);
			Tree[id<<1|1].getmin(Tree[id].lzymin);
			Tree[id].lzymin=INF;
		}
	}
	void Build(int id,int L,int R){
		Tree[id].init();
		Tree[id].l=L;
		Tree[id].r=R;
		if(L==R){
			Tree[id].ma=L;
			Tree[id].mi=R;
			if(id<<1<=4004){
				Tree[id<<1].init();
				Tree[id<<1|1].init();
			}
			return;
		}
		int mid=L+R>>1;
		Build(id<<1,L,mid);
		Build(id<<1|1,mid+1,R);
		Pushup(id);
	}
	void Getmin(int id,int d){
		if(Tree[id].ma<=d) return;
		if(Tree[id].sma<d){
			Tree[id].getmin(d);
			return;
		}
		Pushdown(id);
		Getmin(id<<1,d);
		Getmin(id<<1|1,d);
		Pushup(id);
	}
	void Getmax(int id,int d){
		if(Tree[id].mi>=d) return;
		if(Tree[id].smi>d){
			Tree[id].getmax(d);
			return;
		}
		Pushdown(id);
		Getmax(id<<1,d);
		Getmax(id<<1|1,d);
		Pushup(id);
	}
	void trv(int id){
		if(Tree[id].l==Tree[id].r){
			ans[Tree[id].l][w-Tree[id].r]=Tree[id].ma;
			return;
		}
		Pushdown(id);
		trv(id<<1);
		trv(id<<1|1);
	}
	int main(){
		ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
		cin>>n>>a>>b;
		w=a+b;
		for(int i=1;i<=n;i++){
			cin>>v[i];
		}
		while(w>=0){
			Beg=max(0,w-b);
			End=min(a,w);
			Build(1,Beg,End);
			for(int i=1;i<=n;i++){
				Tree[1].add(-v[i]);
				if(v[i]<0) Getmin(1,End);
				else Getmax(1,Beg);
			}
			trv(1);
			w--;
		}
		for(int i=0;i<=a;i++){
			for(int j=0;j<=b;j++){
				cout<<ans[i][j]<<" ";
			}
			cout<<"\n";
		}
		return 0;
	}
}
int main(){
	cs::main();
	return 0;
}
```

---

## 作者：2018ljw (赞：3)

关注到对于一组 $(c,d)$，无论中间怎么折腾，水的总量始终有 $V=c+d$。考虑枚举总量 $V$，如何一次处理出所有 $c+d=V$ 的答案。

因为总量确定，所以第一桶水的水量始终维持在区间 $[\max\{0,V-b\},\min\{V,a\}]$ 内。考虑操作编号为 $x$ 轴，第一桶水量为 $y$ 轴建系。$x=0$，$y$ 在范围内的整点为起点，则点轨迹可以刻画为 $y=y+v_i$，然后和上下边界分别取极值。

关注到每次移动后，总有一些点的轨迹会贴到上下边界。而对于始终没碰过上下边界的点，它们的位移量是相同的，任取一点计算即可。

因此对于一个 $V$ 我们只需要计算三个点的终值，而这是很容易完成的。接下来就是确定每个点最后是哪类。

考虑把点的运动变成上下边界的运动，计算上边界运动的最低点和下边界运动的最高点。当这两部分不交的时候，三类很自然的被划分开。有交的时候，考虑交点那一侧先贴一侧边界，中间又变道到另一侧边界。换而言之此时所有起点的终点均相同，直接算即可。

复杂度 $O(n(a+b)+ab)$。[record](https://codeforces.com/contest/1809/submission/210503956)。 

---

## 作者：fast_photon (赞：3)

**0. 前言**  
没啥好说的。  
Upd 2023.4.20 21:38 修正了线段举例的表述及 LaTeX。  
Upd 2023.4.21 6:22  把题解改得正常了然后拿大号交。

**1. 分析**  
首先不难注意到一点，两个容器的总水量不变。  
这个也算是一个典型套路，记住就好。  
我们假装将两个容器底部接通。  
那么一次体积为 $v$ 的挪水操作就相当于 $v$ 次体积为 $1$ 的挪水操作，除非某一个容器满了或空了。  
我们可以认为，在数轴上 $-a$ 和 $b$ 分别有两个点，称为“容积上限点”。  
而原点是 “分隔点”。  
若干体积水可以理解为一条线段，挪水则是线段的左右滑动。但是：  
+ 线段不会挪出 $[-a,b]$ 的区间，即容器的水最多是满的。 
+ 原点始终在线段上（含端点），即容器的水最少是空的。  

考虑何种线段可以合并处理。例如，两个分别是左 $0$ 右 $5$ 和左 $1$ 右 $4$ 的线段，进行左到右的 $1$ 的挪水后重合。因此同长度的线段可以统一考虑。  
即一系列的相邻两个左端点最初差 $1$ 的同长度的线段在数轴上进行滑动。假设左端点初始为 $\{a_k\}$，那么操作之后的左端点必然为 $\{a_x+r,a_x+r,\dots,a_x+r,a_{x+1}+r,a_{x+2}+r,\dots,a_y+r,a_y+r,\dots,a_y+r\}$，即左边一段重叠，中间两两差 $1$，右边一段重叠。其中 $r$ 为挪水量的总和。  
> 若当前状态符合这个定义，因为操作被拆分成了若干左 $1$ 或右 $1$。  
当左 $1$ 时，若若干线段受 $-a$ 限制。  
则它们的左侧不可能有更多线段（否则超出 $-a$ 限制），此时右侧的线段因为平移量只有 $1$ 所以全部不受限。即左端进行了额外一格的吞并。  
同理可以证明右 $1$ 的 $b$ 限制和左右的原点限制。

也就是只要算出左右的重叠长度即可。  

**2. AC Code**  
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm> 
#define int long long
#define maxn 10005
#define maxv 1005

using namespace std;

int _, n, a, b, v[maxn], ans[maxv][maxv];
void work() {
	int sum = 0;
	cin >> n >> a >> b;
	for(int i = 1; i <= n; i++) cin >> v[i], sum += v[i];
	for(int w = 0; w <= a + b; w++) { //枚举线段长度
		int l = max(a - w, 0ll), r = min(a + b - w, a); //因为显然数组不能访问负的位置，所以将左右中的限制和线段都向右平移 $a$。
		int L = l, R = r;//初始状态的左端点上下界
		for(int i = 1; i <= n; i++) {
			r += v[i];
			l += v[i];
 			r = min(r, R);
			l = min(l, R);
			r = max(r, L); 
			l = max(l, L);
		}
		if(l == r) {
			for(int i = L; i <= R; i++) {
				ans[a - i][i + w - a] = a - l;
			}
			continue;
		} 
		for(int i = L; i < l - sum; i++) {
			ans[a - i][i + w - a] = a - l;
		}
		for(int i = l - sum; i < r - sum; i++) {
			ans[a - i][i + w - a] = a - (i + sum);
		}
		for(int i = r - sum; i <= R; i++) {
			ans[a - i][i + w - a] = a - r;
		}
                //l-sum 和 r-sum 分别是当前合并后左端点上下界的线段在平移前的左端点值。因为这个表是要根据初始值绘制的。
	}
	for(int i = 0; i <= a; i++) {
		for(int j = 0; j <= b; j++) {
			cout << ans[i][j] << ' ';
		}cout << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(false);
	_ = 1;
	while(_--) work();
}
```

---

## 作者：不知名用户 (赞：1)

随了一道 *2400 DP，但是这题和 DP 有多大关系吗？/yiw

### 题意

有两个水箱，容量分别为 $a,b$ 升。一次倒水为从一个桶向另一个桶转移 $v$ 升水，直到倒水桶空/接水桶满/倒了 $v$ 升三个条件之一满足结束。给定倒水序列，长度为 $n$。问每一组 $(c,d)(0\le c\le a,0\le d \le b)$，两桶初始水量为 $c,d$，最终 $a$ 桶的水量。

$|a|,|b|\le1000,n\le1000。0$

### 做法

考虑固定总水量 $c$，容易发现 $a$ 桶水量范围为 $[\max(0,c-b),\min(a,c)]$（记为 $[L,R]$）。若某次向 $a$ 桶倒入 $v$ 升水（倒出则 $v$ 负），原水量为 $x$，则 $x$ 变为 $\min(R,\max(L,a+v))$。（其实交换一下 $\min,\max$ 写成 $\max(L,\min(R,a+v))$ 也可以）

无脑 $O(n^2\log^2 n)$ 做法：吉老师线段树维护初始水量为 $i(L\le i\le R)$ 时现在的水量。（没写过，不知道能不能冲过去）

加入把某个时刻的线段树写成一个序列，显然是这个形式：$x,x,\cdots,x,x+1,x+1,\cdots,y-1,y,y,\cdots,y$。证明略。考虑维护最右边的 $x$ 和最左边的 $y$ 的位置及 $x,y$ 即可，具体见代码。大概思路是若此时 $x$ 对应水量比 $L$ 小就要更新 $x$，右端点同理。可能要特判只有一种数的情况。

对于每种和是 $\Theta(n)$ 的，所以时间复杂度 $\Theta((a+b)n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, M = 1e3 + 10;
int ans[M][M], v[N];

int main()
{
	int n, a, b, _, i, j;
	scanf("%d%d%d", &n, &a, &b);
	for(i=1;i<=n;i++) scanf("%d", &v[i]);
	for(_=0;_<=a+b;_++)
	{
		int l = max(_-b,0), r = min(a,_), L, R, ll, rr;
		L = ll = l, R = rr = r; 
		for(i=1;i<=n;i++)
		{
			l -= v[i], r -= v[i];
			if(r<=ll||rr<=l)
			{
				if(r<=ll) L = R = l = r = ll;
				else L = R = l = r = rr;
			}
			else
			{
				if(l<ll)
				{
					int d = ll - l;
					l += d, L += d;
				}
				if(rr<r)
				{
					int d = r - rr;
					r -= d, R -= d;
				}
			}
		}
		for(i=ll;i<L;i++) ans[i][_-i] = l;
		for(i=L;i<=R;i++) ans[i][_-i] = l + i - L;
		for(i=R+1;i<=rr;i++) ans[i][_-i] = r;
	}
	for(i=0;i<=a;i++) for(j=0;j<=b;j++) printf("%d%c", ans[i][j], " \n"[j==b]);
	return 0;
}
```

---

## 作者：蒟蒻君HJT (赞：0)

$\mathcal{O}(n(n+a+b))$ 的屑做法，但感觉没那么抽象，是较自然的。

注意到进行完某次操作后，若两种初始状态此时的 A 水量和 B 水量都相同，则他们的最终答案相同。

于是考虑设 $o=c+d$，对 $o$ 相同的初始状态一并计算。

在此前提下，A 中水量最大值为 $u=\min(a,o)$，B 中水量最大值为 $v=\min(b,o)$。则所有操作的过程中，一定会若干次达到 A/B 水量的最大值，最后一段（可能为空）正常倒水。

设 $f_i$ 表示进行完第 $i$ 次操作后若 A 水量达到最大值的最终答案是多少；$g_i$ 表示进行完第 $i$ 次操作后若 B 水量达到最大值的最终答案是多少。

设 $s_i=\sum_{j=1}^i v_j$，倒序考虑每个 $i\in[1,n]$，计算 $f_i$ 和 $g_i$。

$f_i$ 能转移到 $g_j,j>i$ 的条件为 $j$ 是满足 $s_x-s_i\geq \min(a,o,a+b-o)$ 的最小的 $x$；

$f_i$ 能转移到 $f_j,j>i$ 的条件为 $j$ 是满足 $s_x-s_i<0$ 的最小的 $x$；

$g_i$ 能转移到 $g_j,j>i$ 的条件为 $j$ 是满足 $s_x-s_i>0$ 的最小的 $x$；

$g_i$ 能转移到 $f_j,j>i$ 的条件为 $j$ 是满足 $s_x-s_i\leq -\min(b,o,a+b-o)$ 的最小的 $x$。

以上情况，令 $f_i/g_i \leftarrow f_j/g_j$，注意 $j$ 要取最小的那个。

怎么快速找 $j$ 呢？注意到 $\min(a,o,a+b-o),-\min(b,o,a+b-o)$ 都是单峰/单谷函数，在 $o$ 变化时，用两个指针暴力移动即可。复杂度瓶颈在这里，指针要移动 $\mathcal{O}(n^2)$ 次。

若这样的 $j$ 不存在，说明 $f_i/g_i$ 之后都是正常倒水，可得 $f_i=\min(o,a)+s_i-s_n$，$g_i=\max(0,o-b)+s_i-s_n$。

处理完 $f_i/g_i$ 后，考虑枚举初始状态 $(x,y),x+y=o$。计算下一次达到 A 水量最大值的时刻，即最小的满足 $s_x\leq -\min(a-c,d)$ 的 $x$；以及下一次达到 B 水量最大值的时刻，即最小的满足 $s_y\geq \min(c,b-d)$ 的 $y$；

（1）$x,y$ 均不存在，则答案为 $c-s_n$。

（2）$x<y$，则答案为 $f_x$；

（3）$x>y$，则答案为 $g_y$。

具体实现：注意到 $\min(a-c,d),\min(c,b-d)$ 都不超过 $2000$，预处理 $h_z$ 表示满足 $s_p\leq z$ 的最小的 $p$，$k_w$ 表示满足 $s_q\geq w$ 的最小的 $q$ 即可。

code

```cpp
#include <bits/stdc++.h>
#define dbg printf("here\n");
int n, a, b, v[10005], ans[1005][1005], s[10005];
int f[10005], g[10005], ra[10005], ri[10005], st[10005], tp = 0;
int ita[10005], iti[10005], la[10005], li[10005];
int m1[2005], m2[2005];
int main(){
  scanf("%d%d%d", &n, &a, &b);
  for(int i = 1; i <= n; ++i) scanf("%d", &v[i]);
  for(int i = 1; i <= n; ++i) s[i] = s[i - 1] + v[i];
  for(int i = 0; i <= 2001; ++i) m1[i] = m2[i] = n + 1;
  for(int i = 1; i <= n; ++i){
    if(s[i] >= 0){
      for(int j = 0; j <= std::min(s[i], 2001); ++j)
        m1[j] = std::min(m1[j], i);
    }
    if(s[i] <= 0){
      for(int j = 0; j <= std::min(-s[i], 2001); ++j)
        m2[j] = std::min(m2[j], i);
    }
  }
  tp = 0; st[0] = n + 1;
  for(int i = n; i >= 1; --i){
    while(tp && s[st[tp]] <= s[i]) --tp;
    ra[i] = st[tp];
    st[++tp] = i;
  }
  tp = 0; st[0] = n + 1;
  for(int i = n; i >= 1; --i){
    while(tp && s[st[tp]] >= s[i]) --tp;
    ri[i] = st[tp];
    st[++tp] = i;
  }
  tp = 0; st[0] = 0;
  for(int i = 1; i <= n; ++i){
    while(tp && s[st[tp]] <= s[i]) --tp;
    la[i] = st[tp];
    st[++tp] = i;
  }
  tp = 0; st[0] = 0;
  for(int i = 1; i <= n; ++i){
    while(tp && s[st[tp]] >= s[i]) --tp;
    li[i] = st[tp];
    st[++tp] = i;
  }
  ra[n + 1] = ri[n + 1] = n + 1;
  for(int i = 1; i <= n; ++i){
    ita[i] = i;
    iti[i] = i;
  }
  for(int o = a + b; o >= 0; --o){
    int s1 = std::min(std::min(o, a), a + b - o);
    int s2 = -std::min(std::min(o, b), a + b - o);
    for(int i = 1; i <= n; ++i){
      while(ra[ita[i]] != n + 1 && s[ita[i]] - s[i] <= s1) ita[i] = ra[ita[i]];
      while(ita[i] > i && s[li[ita[i]]] - s[i] > s1) ita[i] = li[ita[i]];
      while(ri[iti[i]] != n + 1 && s[iti[i]] - s[i] >= s2) iti[i] = ri[iti[i]];
      while(iti[i] > i && s[la[iti[i]]] - s[i] < s2) iti[i] = la[iti[i]];
    }
    for(int i = n; i >= 1; --i){
      int c = ri[i], d = ita[i];
      if(s[d] - s[i] <= s1) d = n + 1;
      
      c = std::min(c, d);
      if(c == n + 1) f[i] = std::min(o, a) + s[i] - s[n];
      else if(c == ri[i]) f[i] = f[c];
      else f[i] = g[c];
      c = ra[i], d = iti[i];
      if(s[d] - s[i] >= s2) d = n + 1;
      c = std::min(c, d);
      if(c == n + 1) g[i] = std::max(o - b, 0) + s[i] - s[n];
      else if(c == ra[i]) g[i] = g[c];
      else g[i] = f[c];
    }
    for(int x = 0; x <= a; ++x)
      if(o - x >= 0 && o - x <= b){
        int y = o - x;
        int c = std::min(x, b - y), d = std::min(y, a - x);
        int it1 = m1[c], it2 = m2[d];
        if(it1 == n + 1 && it2 == n + 1) ans[x][y] = x - s[n];
        else if(it1 < it2) ans[x][y] = g[it1];
        else ans[x][y] = f[it2];
      }
  }
  for(int i = 0; i <= a; ++i){
    for(int j = 0; j <= b; ++j)
      printf("%d ", ans[i][j]);
    printf("\n");
  }
  return 0;
}
```


---

