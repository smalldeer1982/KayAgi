# [NOISG 2023 Qualification] Burgers

## 题目描述

龙虾 Kai 经营着一家汉堡店。做一个汉堡需要 $n$ 种原料，第 $i$ 种原料他有 $x_i$ 份。

他手中有两种汉堡食谱，这两种汉堡对于第 $i$ 种原料分别需要 $a_i$ 份和 $b_i$ 份来制作。

计算 Kai 最多能用这些原料制作多少个汉堡。

## 说明/提示

### 【样例 #1 解释】

Kai 可以制作 $3$ 个第一种汉堡和 $2$ 个第二种汉堡。

### 【样例 #2 解释】

Kai 可以制作 $24$ 个第一种汉堡或 $24$ 个第二种汉堡。

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$9$|对于所有的 $1 \le i \le n$，$a_i=b_i$。|
|$2$|$17$|$n,x_i\le100$|
|$3$|$25$|$n,x_i\le1500$|
|$4$|$49$|无|

对于 $100\%$ 的数据，$1\le n\le100000,1\le x_i,a_i,b_i\le10^9$。

## 样例 #1

### 输入

```
3
14 10 100
3 1 1
2 3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
2
83 72
1 3
1 3```

### 输出

```
24```

# 题解

## 作者：rhn7 (赞：4)

模拟赛时忘写上取整 100->50，警示后人。

贪心、枚举都不行，但我们发现答案有单调性，尝试一下二分。

设第一个汉堡买了 $x$ 个，第二个汉堡买了 $y$ 个，要 check 的答案为 $t$，得到不等式：

$xa_i+yb_i \le x_i$

显然 $x+y=t$，所以 $y=t-x$。

$xa_i+(t-x)b_i \le x_i$

$xa_i+tb_i-xb_i \le x_i$

$x(a_i-b_i) \le x_i-tb_i$

若 $a_i=b_i$，$x_i<tb_i$ 时无解，否则 $x$ 取任意值。

若 $a_i>b_i$，$x \le \frac{(x_i-tb_i)}{a_i-b_i}$

若 $a_i<b_i$，$x \ge \frac{(x_i-tb_i)}{a_i-b_i}$

最后看不等式组是否冲突即可，且 $x$ 必须是 $[0,t]$ 中的正整数。


```cpp
#include<bits/stdc++.h>
#define rd(x) scanf("%lld",&x)
using namespace std;
typedef long long ll;
const ll N=1e5+5;
ll n,x[N],a[N],b[N];
bool chk(ll mid){
    ll l=0,r=1e18;
    for(ll i=1;i<=n;i++){
        if(a[i]==b[i]){
            if(mid*b[i]>x[i]) return 0;
        }else if(a[i]>b[i]){
            if(mid*b[i]>x[i]) return 0;
            r=min(r,(x[i]-mid*b[i])/(a[i]-b[i]));
        }else{
            l=max(l,(mid*b[i]-x[i]+b[i]-a[i]-1)/(b[i]-a[i]));
        }
    }
    if(l>r||r<0||l>mid) return 0;
    return 1;
}
int main(){
    rd(n);
    for(ll i=1;i<=n;i++) rd(x[i]);
    for(ll i=1;i<=n;i++) rd(a[i]);
    for(ll i=1;i<=n;i++) rd(b[i]);
    ll l=0,r=5e9,ans;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(chk(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_EternalRegrets_ (赞：3)

[传送门](https://www.luogu.com.cn/problem/P10730)

### 题意描述：
>给定 $n$ 种原料，有两种汉堡可以用这些原料制作，分别需要 $a_i$ 和 $b_i$ 个第 $i$ 种原料。求最多可以制作几个汉堡。

### Solution:
可以~~比较容易地~~发现可以制作的汉堡的个数是单调的。

所以，就可以考虑二分答案。

现在只需要解决 ```check``` 就可以切掉本题。

可以发现，对于一对 $a_i$ $b_i$，想要用总共 $mid$ 个 $a_i$ 或者 $b_i$ 凑出比 $x_i$ 小的数字，对于两个数字的个数均有限制。

1. 对于比较小的数字，它的 $mid$ 倍不能超过 $x_i$。
2. 对于较大数字，因为数字之和不能超过 $x_i$，会有一个数量上限，可以通过计算得出。（同样的，这使得较小的数字有一个下限）
3. 若两个数字相等，只要求其中一个数字的 $mid$ 倍不能超过 $x_i$ 即可。

具体见代码。

### code:
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n;
int x[100005];
int a[100005];
int b[100005];

int check(int mid){
    int mxa,mxb,mna,mnb;
    mxa=mxb=INT_MAX; mna=mnb=0;

    for(int i=1;i<=n;i++){
        if(a[i]<b[i]){
            if(a[i]*mid>x[i]){
                return 0;
            }

            int tmp; tmp=b[i]-a[i];
            mna=max(mna,mid-(x[i]-a[i]*mid)/tmp);
            mxb=min(mxb,(x[i]-a[i]*mid)/tmp);
        }
        else if(a[i]>b[i]){
            if(b[i]*mid>x[i]){
                return 0;
            }

            int tmp; tmp=a[i]-b[i];
            mxa=min(mxa,(x[i]-b[i]*mid)/tmp);
            mnb=max(mnb,mid-(x[i]-b[i]*mid)/tmp);
        }
        else{
            if(a[i]*mid>x[i]){
                return 0;
            }
        }
    }

    if(mna<=mxa && mnb<=mxb){
        return 1;
    }

    return 0;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //freopen("burger.in","r",stdin);
    //freopen("burger.out","w",stdout);

    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>x[i];
    }

    int mx; mx=-1;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mx=max(mx,x[i]/a[i]);
    }

    for(int i=1;i<=n;i++){
        cin>>b[i];
        mx=max(mx,x[i]/b[i]);
    }

    int l,r; l=0;r=mx+1;
    int ans; ans=0;
    while(l<=r){
        int mid; mid=(l+r)/2;

        if(check(mid)){
            l=mid+1;
            ans=mid;
        }
        else{
            r=mid-1;
        }

        //cout<<l<<" "<<r<<endl;
    }

    cout<<ans;
    return 0;
}
```

---

## 作者：Handezheng (赞：3)

# 题解：P10730
## 前言
[题目传送门](https://www.luogu.com.cn/problem/P10730)

[博客食用更佳](https://www.luogu.com.cn/article/m3pd4bv6)

本题解借鉴了部分[楼上大佬的内容](https://www.luogu.com.cn/article/69a9atwp)，但是我想详细讲一下~~赚点估值~~，以便理解（楼上的题解我看了两天才看懂）。
## 题意
两种汉堡，一个汉堡对于原料 $x_i$ 需要使用 $a_i$ 或 $b_i$ 份（根据汉堡是哪种决定使用份数），求最大能做的汉堡个数。
## 思路
首先想到贪心，很明显，贪心是错的。因为你在选择原料时并不知道是优先选哪个汉堡，也不知道每种汉堡要选多少个。  
其次想到 DP。如此你会发现，转移方程不知道怎么写，而且时间会超。

我们发现，对于一个整数 $k$,如果可以做成 $k$ 个汉堡，那么也一定能做出数量小于 $k$ 的汉堡；反之，如果 $k$ 个汉堡不可做，那么数量大于 $k$ 的汉堡也一定不可做——这不就是**单调性**嘛！  
有了单调性，下意识想到**二分**。可是难题又来了：我们的 $check$ 函数怎么写呢？

我们发现，如果 $a_i$ 比 $b_i$ 小并且在 $x_i$ 范围内能够取到 $k$ 个汉堡的话，会对 $a_i$ 有一个**下界**要求：总量为 $k$ 个汉堡，$a_i$ 取到的越少 $b_i$ 取到的就越多（~~废话~~），这样用到的原料总数就会更多，就有可能超出 $x_i$ 的范围。所以要求 $a_i$ 至少要取到多少个才能使汉堡总数达到 $k$（在 $x_i$ 范围内），这便是 $a_i$ 的下界要求。  
同理，当 $b_i<a_i$ 时，对 $b_i$ 有也一个下界要求，我们可以转换为对 $a_i$ 的**上界要求**。  

![](https://cdn.luogu.com.cn/upload/image_hosting/dk8q0q9m.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在 $a$ 的上下界中去选，如图，红色为上界，蓝色为下界，如果上下界不相交（最大下界小于等于最小上界），即存在 $a$ 的一个取值，满足它大于等于所有下界且小于等于所有上界，那么便可以取到 $k$ 个汉堡，$check$ 函数返回值为 $true$。

## 袋马
与楼上大佬大差不差（感觉我的更简洁），注释请看楼上
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define F(i,l,r) for(int i = l;i <= r;i++)
const int N = 1e6 + 50,M = 1e3 + 50;
const int INF = 0x3f3f3f3f3f3f3f3f,INT = 0x7fffffff;
const int mod = 1e9 + 7;

int n,x[N],a[N],b[N];

inline bool check(int k){
	int mi=0,ma=1e9;
	//上界和下界
	F(i,1,n){
		if(a[i]==b[i]){
			if(a[i]*k>x[i]) return 0;
		}else if(a[i]<b[i]){
			if(a[i]*k>x[i]) return 0;
			if(b[i]*k<=x[i]) continue;
			mi=max(mi,k-(x[i]-a[i]*k)/(b[i]-a[i]));
//			a[i]的下界
		}else{
			if(b[i]*k>x[i]) return 0;
			if(a[i]*k<=x[i]) continue;
			ma=min(ma,(x[i]-b[i]*k)/(a[i]-b[i]));
		}
	}
	return (mi <= ma);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>n;
	F(i,1,n) cin>>x[i];
	F(i,1,n) cin>>a[i];
	F(i,1,n) cin>>b[i];
	int l=0,r=1e9;
	while(l<=r){
		int mid = (l+r) >>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	cout<<r;

	return 0;
}
``````
[AC记录](https://www.luogu.com.cn/record/176480760)


——$2024.9.10,9:10$ 完笔

---

## 作者：H_Kaguya (赞：2)

凸包。  

直接把题面形式化。  
设两种汉堡分别制作了 $x,y$ 个，则有 $\forall i, a_ix + b_iy \le c_i$。  
也就是现在有若干条线段，需要在线段下面取一个点 $(x, y)$，最大化 $x+y$。  
合法区域是一个上凸壳，直接把凸包建出来即可。  
建凸包的算法有很多，这里使用 Andrew。  
最后枚举凸包上的边统计答案。  

复杂度 $O(n \log n)$，瓶颈是排序。  
可以使用基数排序做到 $O(n)$。  

---
朴素实现  
```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
const int sz = 100005;
const int md = 1e9 + 7;
struct node
{
	int a, b, c;
};
node line[sz], sta[sz];
int n, top;
long ans;
int read();
bool cmp(const node&, const node&);
long ano(node, node);
long geans(node, int);
int main()
{
	n = read();
	for (int i = 1; i <= n; ++i)
		line[i].c = read();
	for (int i = 1; i <= n; ++i)
		line[i].a = read();
	for (int i = 1; i <= n; ++i)
		line[i].b = read();
	sort(line + 1, line + 1 + n, cmp);
	top = 1;
	sta[1].a = 0; sta[1].b = md; sta[1].c = 1;
	for (int i = 2; i <= n; ++i)
	{
		while (top)
		{
			long tmp = ano(line[sta[top].c], line[i]);
			if (tmp > sta[top].b)
				break;
			if (tmp <= sta[top].a)
				--top;
			else
			{
				sta[top].b = tmp - 1;
				break;
			}
		}
		if (top == 0 || sta[top].b < md)
		{
			sta[top + 1].a = sta[top].b + 1;
			++top;
			sta[top].b = md;
			sta[top].c = i;
		}
	}
	ans = line[1].c / line[1].a;
	for (int i = 2; i <= n; ++i)
		ans = min(ans, (long)line[i].c / line[i].a);
	long tp = line[1].c / line[1].b;
	for (int i = 2; i <= n; ++i)
		tp = min(tp, (long)line[i].c / line[i].b);
	ans = max(ans, tp);
	for (int i = 1; i <= top; ++i)
		if (line[sta[i].c].a >= line[sta[i].c].b)
			ans = max(ans, geans(line[sta[i].c], sta[i].a));
		else
			ans = max(ans, geans(line[sta[i].c], sta[i].b));
	printf ("%ld\n", ans);
	return 0;
}

int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0') c = getchar();
	do {
		x = x * 10 + (c & 15);
		c = getchar();
	}while (c >= '0');
	return x;
}

bool cmp(const node &a, const node &b)
{
	if ((long)a.a * b.b == (long)a.b * b.a)
		return (long)a.c * b.b > (long)a.b * b.c;
	return (long)a.a * b.b < (long)a.b * b.a;
}

long ano(node a, node b)
{
	long x = (long)a.b * b.c - (long)b.b * a.c;
	long y = (long)a.b * b.a - (long)a.a * b.b;
	if (y == 0 || (x < 0 && y > 0) || (x > 0 && y < 0))
		return 0;
	return x / y + (x % y != 0);
}

long geans(node a, int b)
{
	long x = (a.c - (long)b * a.a);
	if (x < 0)
		return 0;
	return x / a.b + b;
}

```

---

## 作者：船酱魔王 (赞：1)

## 题意回顾

$ n $ 元价值双物品背包，值域 $ 10^9 $，$ n \le 10^5 $。

## 分析

物品很少考虑暴力枚举一个物品，设物品一有 $ t $ 个，则物品二的个数上限可以表示为 $ \min\{\lfloor\frac{x_i-ta_i}{b_i}\rfloor\}=\min{\lfloor \frac{x_i}{b_i}-\frac{a_i}{b_i}t \rfloor} $。即 $ n $ 条直线的与 $ x=t $ 的交点 $ y $ 坐标最小的一个是物品二的上限。

把斜率和截距都不小于其他直线的线删除，之后斜率从大到小截距从小到大，排除掉与下一条直线交点在上一条直线之前的直线。所以每条直线作为最低直线的 $ t $ 范围都是一个端点为与前后直线交点的区间，且区间起点依次递增。

因此找出每个直线的区间，一次函数有实数域上的单调性，所以容易找到最值。**注意 $ t $ 必须为整数且 $ 0 \le t \le \min\{\lfloor \frac{x_i}{a_i} \rfloor\} $。**

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ld long double
using namespace std;
const int N = 1e5 + 5;
int n;
int x[N], a[N], b[N];
struct node {
    ld ki;
    ld bi;
} c[N];
bool operator<(node p1, node p2) {
    if(p1.ki == p2.ki) return p1.bi > p2.bi;
    return p1.ki > p2.ki;
}
ld mip(node p1, node p2) {
    return (p1.bi - p2.bi) / (p2.ki - p1.ki);
}
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &x[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &b[i]);
    for(int i = 1; i <= n; i++) {
        c[i].ki = (ld)1 - (ld)a[i] / b[i];
        c[i].bi = (ld)x[i] / b[i];
    }
    sort(c + 1, c + n + 1);
    int mxt = 1e9 + 5;
    for(int i = 1; i <= n; i++) mxt = min(mxt, x[i] / a[i]);
    int cn = 0;
    for(int i = 1; i <= n; i++) {
        while((cn && c[cn].ki == c[i].ki) || (cn >= 2 && mip(c[cn - 1], c[cn]) >= mip(c[cn], c[i]))) cn--;
        c[++cn] = c[i];
    }
    ld lf, rt;
    int lmq = 1e9 + 5;
    for(int i = 1; i <= n; i++) lmq = min(lmq, x[i] / b[i]);
    ld ans = max(lmq, mxt);
    for(int i = 1; i <= cn; i++) {
        if(i > 1) lf = (c[i].bi - c[i - 1].bi) / (c[i - 1].ki - c[i].ki);
        else lf = 0;
        if(i < cn) rt = (c[i + 1].bi - c[i].bi) / (c[i].ki - c[i + 1].ki);
        else rt = mxt;
        lf = max((ld)0, lf), rt = min((ld)mxt, rt);
        if(lf > (int)lf) lf = (int)lf + 1;
        rt = (int)rt;
        if(lf <= rt) {
            if(c[i].ki < 0) ans = max(ans, lf * c[i].ki + c[i].bi);
            else ans = max(ans, rt * c[i].ki + c[i].bi);
        }
    }
    printf("%d\n", (int)ans);
    return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有两种汉堡，$n$ 种食材，食材 $i$ 有 $x_i$ 份。

第一种汉堡需要用 $a_i$ 份食材 $i$，第二种汉堡需要用 $b_i$ 份食材 $i$。求出你最大可以做出多少个汉堡。

$1\leq n\leq 10^5$。

## 思路

设 $f(x)$ 表示钦定做 $x$ 个第一种汉堡，最多可以做出多少个汉堡，那么不难写出式子：

$$
f(x)=x+\min_{k=1}^{n}\left\lfloor\frac{x_i-a_ix}{b_i}\right\rfloor
$$

其中值域 $\left[0,\min_i \lfloor\frac{x_i}{a_i}\rfloor\right]\cap \mathbb{Z}$。

根据下取整的性质，不难稍作变形：

$$
f(x)=x+\min_{k=1}^{n}\left\lfloor\frac{x_i-a_ix}{b_i}\right\rfloor=x+\left\lfloor\min_{k=1}^{n} -\frac{a_i}{b_i}x+\frac{x_i}{b_i}\right\rfloor=\left\lfloor\min_{k=1}^{n}(-\frac{a_i}{b_i}+1)x+\frac{x_i}{b_i}\right\rfloor
$$

那么我们需要解决下面一个问题：

> 给定 $n$ 个一次函数 $f_i$，你需要在给定值域 $S$ 中找到一个 $x$，使得 $\min_i f_i(x)$ 最大。求出这个最大值。

一些比较笨的方法是李超线段树或者凸包，但是更加容易想到的方法是二分这个最大值 $v$，那么只需要判断 $S$ 与所有 $\{x\mid f_i(x)\geq v\}$ 的交是否为 $\varnothing$，而这是容易的。

时间复杂度 $O(n\log V)$，其中 $V$ 为值域。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
using f64 = double;
const f64 eps = 1e-9;

int dcmp(f64 x){ return x < -eps ? -1 : x > eps; }

struct line {
    f64 k, b;
} l[N];
int n, a[N], b[N], x[N], maxR;

bool check(f64 v){
    f64 L = 0, R = maxR;
    for(int i=1;i<=n;i++){
        if(!dcmp(l[i].k)){
            if(dcmp(v - l[i].b) > 0) return false;
            continue;
        }
        f64 x = (v - l[i].b) / l[i].k;
        if(dcmp(l[i].k) == 1) L = max(L, x);
        else R = min(R, x);
        if(dcmp(L - R) > 0) return false;
    }
    return ceil(L) <= floor(R);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n, maxR = 1e9;
    for(int i=1;i<=n;i++) cin >> x[i];
    for(int i=1;i<=n;i++) cin >> a[i], maxR = min(maxR, x[i] / a[i]);
    for(int i=1;i<=n;i++) cin >> b[i];
    for(int i=1;i<=n;i++) l[i] = {-1.0 * a[i] / b[i] + 1, 1.0 * x[i] / b[i]};
    int L = 0, R = 1e9;
    while(L < R){
        int mid = (L + R + 1) / 2;
        if(check(mid)) L = mid;
        else R = mid - 1;
    }
    cout << R << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：fzs7 (赞：0)

题意：给定数组 $a,b,c$，求两个整数使得 $x+y$ 最大且满足 $\forall 1 \leq i \leq n,xa_i + yb_i \leq c_i$。

给这个式子换个形式：$y \leq \frac{c_i-xa_i}{b_i}$。

得到 $x+y \leq (1-\frac{a_i}{b_i})x + \frac{c_i}{b_i}$。

发现这相当于给一些线段，求线段下方最大点。

建出凸包简单维护即可。

$Code$

~~~cpp
#include <bits/stdc++.h>
using namespace std;

inline long long read(void) {
	long long x = 0, f = 1; char c = getchar();
	while (c > '9' || c < '0') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - 48, c = getchar();
	return x * f;
}

struct node {
	long double k, b, bg;
} stk[100005];

struct line {
	long double k, b;
	friend bool operator< (line x, line y) {
		if (x. k == y. k) return x. b < y. b;
		return x. k > y. k;
	}
} lne[100005];

long long n, cnt, cct, c[100005], a[100005], b[100005], ans;

int main(void) {
	n = read();
	for (int i = 1; i <= n; i++) c[i] = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) b[i] = read();
	if (a[1] < b[1]) for (int i = 1; i <= n; i++) swap(a[i], b[i]);
	for (int i = 1; i <= n; i++) lne[i]. k = (long double)1 - (long double)(a[i]) / b[i], lne[i]. b = (long double)c[i] / b[i];
	sort(lne + 1, lne + 1 + n);
	for (int i = 1; i <= n; i++)
		if (i == 1 || lne[i]. k != lne[i - 1]. k)
			lne[++cct] = lne[i];
	n = cct;
	stk[++cnt] = {lne[1]. k, lne[1]. b, 0};
	for (int i = 2; i <= n; i++) {
		while (cnt && (lne[i]. b - stk[cnt]. b) / (stk[cnt]. k - lne[i]. k) <= stk[cnt]. bg) cnt--;
		if (!cnt) stk[++cnt] = {lne[i]. k, lne[i]. b, 0};
		else cnt++, stk[cnt] = {lne[i]. k, lne[i]. b, (lne[i]. b - stk[cnt - 1]. b) / (stk[cnt - 1]. k - lne[i]. k)};
	}
	for (int i = 1; i <= cnt; i++) {
		if (i == cnt || ceill(stk[i]. bg) < stk[i + 1]. bg) ans = max(ans, (long long)(ceill(stk[i]. bg) * stk[i]. k + stk[i]. b));
		if (i < cnt && floor(stk[i + 1]. bg) >= stk[i]. bg) ans = max(ans, (long long)((floor(stk[i + 1]. bg)) * stk[i]. k + stk[i]. b));
	}
	printf("%lld", ans);
	return 0;
}
~~~

---

## 作者：Error_Eric (赞：0)

### Statement

为了避免歧义，这里用 $x, y$ 分别指代两种糖数量，用 $c_i$ 表示原文 $x_i$。

可以认为是 $\forall i, a_i x + b_i y \le c_i$， 求最大的 $x + y$。

### Sol

几何意义上这是求一个（二维）凸包内 $x+y$ 最大的点，可以用一些很 fancy 的算法解决，但是都很难。考虑转化一下。

二分答案，假设 $x + y = d$。思考下怎么验证。

可以通过消掉 $y$ 的方式求出 $x$ 的范围。 

$$ \begin{aligned}
   &a_ix + b_i y \le c_i \\
   
   \Rightarrow & (a_i - b_i) x + b_i(x+y) \le c  \\ \Rightarrow & (a_i - b_i) x \le c - b_i d  \\
   \end{aligned} 
   $$

分类讨论 $a_i - b_i$。不难得到

$$
\begin{cases}
 x &\le \dfrac{c-b_id}{a_i - b_i} & \ \ \ \  a_i > b_i\\
 0 &\le c - b_id  & \ \ \ \ a_i = b_i \\
 x &\ge \dfrac{c-b_id}{a_i - b_i} & \ \ \ \  a_i < b_i\\
\end{cases}
$$

check 的时候只需要保证第二种情况得到满足，第一、三种解出来不是空集就可以。当然注意 $x$ 是整数，第一种情况下商直接下取整，第二种上取整即可。

### Code 

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
using namespace std;
int n, ans = 0;
vector<long long> a, b, c;
bool check(int d){ // if x + y = d has solution
	long long maxx = d, minx = 0;
	for(int i = 0; i < n && minx <= maxx; i++){
		if(a[i] > b[i]) 
			maxx = min(maxx, (c[i] - b[i] * d) / (a[i] - b[i]));
		else if (a[i] < b[i])
			minx = max(minx, (c[i] - b[i] * d -1) / (a[i] - b[i]) + 1);
		else if (a[i] * d > c[i]) return false;
	}
	return minx <= maxx;
}
int main(){
	ios::sync_with_stdio(0),
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(auto vec:{&c, &a, &b}){
		vec->resize(n);
		for(long long&vx:(*vec))
			cin >> vx;
	}
	for(int k = (1<< 30); k; k>>=1){
		if(ans + k < 1e9 && check(ans+k))
			ans += k;
	}
	cout << ans << endl;
}
```

---

