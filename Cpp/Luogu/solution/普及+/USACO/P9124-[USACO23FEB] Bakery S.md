# [USACO23FEB] Bakery S

## 题目描述

Bessie 开了一家面包店!

在她的面包店里，Bessie 有一个烤箱，可以在 $t_C$ 的时间内生产一块饼干或在 $t_M$ 单位时间内生产一块松糕。
$(1 \le t_C,t_M \le 10^9)$。由于空间限制，Bessie 一次只能生产一种糕点，所以要生产 $A$ 块饼干和 $B$ 块松饼，需要 $A\cdot t_C+B\cdot t_M$ 单位的时间。

Bessie的 $N (1\le N\le 100)$ 朋友都想一个一个地去面包店。第 $i$ 个朋友一进门就会点 $a_i(1 \le a_i \le 10^9)$ 块饼干和 $b_i(1 \le b_i \le 10^9)$ 块松饼。Bessie 没有空间来储存糕点，所以她只有在接到订单后才开始制作糕点。此外，Bessie 的朋友都很忙，所以第 $i$ 个朋友只愿意等 $c_i(a_i+b_i \le c_i \le 2 \cdot 10^{18})$ 个单位的时间，然后就伤心地离开。

Bessie 真的不希望她的朋友们伤心，她可以用一块钱升级她的烤箱，让它少花一个单位的时间来生产一块饼干或少花一个单位的时间来生产一个松饼。她不能将她的烤箱升级到花费小于等于 $0$ 的时间，但她可以选择在她的朋友到来之前将她的烤箱升级多少次，只要生产一块饼干和生产一个松饼所需的时间都严格保持为正数。

对于每一个 $T(1\le T\le 100)$ 的测试案例，请帮助 Bessie 找出她必须花费的最小的钱数量，以便她的面包店能够满足所有的朋友。

## 样例 #1

### 输入

```
2

3 7 9
4 3 18
2 4 19
1 1 6

5 7 3
5 9 45
5 2 31
6 4 28
4 1 8
5 2 22```

### 输出

```
11
6```

# 题解

## 作者：MiPloRAs_3316 (赞：17)

[题目传送门](/problem/P9124) | [珂能更好的食用体验](/blog/560595/solution-p9124)

### 题意概述
- 奶牛需要为 TA 的 $n$ 个朋友制作糕点（$a_i$ 个 $A$ 和 $b_i$ 个 $B$）。每个朋友最多等待 $c_i$ 个单位时间，如果没有拿到糕点，TA 就会伤心地离开。
- 制作 $1$ 个 $A$ 需要 $t_c$ 个单位时间，制作 $1$ 个 $B$ 需要 $t_m$ 个单位时间。
- 奶牛可以花费 ￥$1$ 去升级 TA 的烤箱。升级后，可以少花 $1$ 个单位时间来生产 $1$ 个  $A$ 或少花 $1$ 个单位时间来生产 $1$ 个 $B$。
- 求出她必须花费的最少的 money，以便她的面包店能够满足所有朋友的需求。

---
### 解题思路
我们可以先假设对于第 $i$ 个朋友（订单），需要升级 $x$ 次 $A$ 烤箱， $y$ 次 $B$ 烤箱。

于是，显而易见的：~~（看起来很简洁但一点都不好解）~~

$$a_i \times (t_c-x) + b_i \times (t_m-y) \leqslant c_i$$

令 $mid=x+y$，于是：
$$
a_i \times t_c-a_i \times x+b_i \times t_m - b_i \times mid+b_i \times x \leqslant c_i
$$
$$
\therefore (b_i-a_i)\times x \leqslant c_i-a_i \times t_c-b_i\times t_m+b_i\times mid
$$
令 $k_i=c_i-a_i \times t_c-b_i\times t_m+b_i\times mid$，


所以，就可以根据上述不等式进行**二分答案**了。（二分的当然是 $x+y$。）

接下来，浅浅说一下不等式的解集：

$$
\begin{cases}x=\varnothing, &b_i-a_i=0 \\ x\leqslant \dfrac{k_i}{b_i-a_i} , &b_i-a_i>0\\ x\geqslant \dfrac{k_i}{b_i-a_i} , &b_i-a_i<0\end{cases}
$$

上述第 $2$ 个式子用于锁定解集的**上限**，第 $3$ 个式子用于锁定解集的**下限**。

同时，$x$ 与 $y$ 的值应该为整数。所以为了便于大家理解程序，解集应该写成下面这个亚子。

$$
\begin{cases}x=\varnothing, &b_i-a_i=0 \\\\ 
x\leqslant \left\lfloor\dfrac{k_i}{b_i-a_i}\right\rfloor , &b_i-a_i>0\\\\
x\geqslant \left\lceil\dfrac{k_i}{b_i-a_i}\right\rceil, &b_i-a_i<0\end{cases}
$$

---
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,tc,tM,a[110],b[110],c[110];
bool check(long long x)
{
	long long maxx=min(tc-1,x);
	long long minn=max(0LL,x-tM+1);
	for(int i=1; i<=n; i++)
	{
		long long k=c[i]-a[i]*tc-b[i]*tM+b[i]*x;
		if(b[i]-a[i]==0)
		{	
			if(k<0) return false;
		}
		else if(b[i]-a[i]>0) maxx=min(maxx,(long long)floor(k*1.0/(b[i]-a[i])));//二式
		else minn=max(minn,(long long)ceil(k*1.0/(b[i]-a[i])));//三式
	}
	return maxx>=minn;//判断是否有解
}
int main()
{
	for(cin>>T;T;T--)
	{
		cin>>n>>tc>>tM;
		for(int i=1; i<=n; i++)
			cin>>a[i]>>b[i]>>c[i];
		long long l=-1,r=tc+tM-1;
		while(l+1<r)//简单的二分答案
		{
			long long mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=mid;
		}
		cout<<r<<endl;
	}
	return 0;
}
```

---

## 作者：_Spectator_ (赞：10)

[可能更好的食用体验](/blog/523641/P9124) $|$ 
[题目传送门](/problem/P9124) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{思路}}$

设升级饼干 $x$ 次，升级松糕 $y$ 次。考虑使用二分答案。然而，单独的 $x$ 或 $y$ 都不具有单调性。但是题目所求的总钱数，即 $x+y$ 是具有单调性的。也就是说，可以对 $x+y$ 进行二分答案。

接下来考虑如何判断答案正确性。设当前二分的答案 $mid=x+y$，则 $y=mid-x$。对于第 $i$ 个朋友，要满足他的需求，则需要满足：
$$a_i\times(tc-x)+b_i\times(tm-y)\le c_i$$
将 $y=mid-x$ 代入，得：
$$a_i\times(tc-x)+b_i\times[tm-(mid-x)]\le c_i$$
再将这个式子展开，得：
$$a_i\times tc-a_i\times x+b_i\times tm-b_i\times mid+b_i\times x \le c_i$$
稍微变形一下，得：
$$(b_i-a_i)\times x \le c_i-a_i\times tc-b_i\times tm+b_i\times mid$$
令 $t=b_i-a_i$，$k=c_i-a_i\times tc-b_i\times tm+b_i\times mid$，得 $t\times x\le k$。接下来对这个式子进行分类讨论。

- 若 $t=0$，则当 $k<0$ 时，$x$ 无解。
- 若 $t>0$，则 $x \le \lfloor\frac{k}{t}\rfloor$。据此可求得 $x$ 的上限 $ma$。
- 若 $t<0$，则 $x \ge \lceil\frac{k}{t}\rceil$。据此可求得 $x$ 的下限 $mi$。

最后，若 $ma\ge mi$，则该答案可行，反之则不可行。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL T,n,tc,tm;
LL a[105],b[105],c[105];
bool ok(LL mid)
{
    LL ma=min(tc-1,mid),mi=max(0,mid-tm+1);//注意ma和mi的初值
    for(int i=1;i<=n;i++)
    {
        LL t=b[i]-a[i],k=c[i]-a[i]*tc-b[i]*tm+b[i]*mid;
        if(t==0&&k<0)return false;
        if(t>0)ma=min(ma,(LL)floor(k*1.0/t));
        if(t<0)mi=max(mi,(LL)ceil(k*1.0/t));
    }
    return ma>=mi;
}
int main()
{
    for(cin>>T;T;T--)
    {
        cin>>n>>tc>>tm;
        for(int i=1;i<=n;i++)
            cin>>a[i]>>b[i]>>c[i];
        LL l=-1,r=tc+tm;//r能取到0，所以l要从-1开始
        while(l+1<r)
        {
            LL mid=(l+r)/2;
            if(ok(mid))r=mid;
            else l=mid;
        }
        cout<<r<<endl;
    }
    return 0;
}
```

---

## 作者：Usada_Pekora (赞：6)

如果 $t_c$ 减少了，二分一个最小的 $t_m$ 的减少量是容易的，所以暴力是好做的：枚举 $\Delta t_c$，二分$\Delta t_m$，然后取相加的最小值。

容易发现，如果 $\Delta t_c$ 和 $\Delta t_m$ 可以是实数的，那么这个东西其实是下凸的。这启发我们继续~~乱搞~~ 往三分的方向考虑。我们三分一次 $t_c$，然后三分 $t_m$，复杂度 $O(n\log^2 V)$。

```cpp

#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int N = 100 + 5;
int n, Tc, Tm, a[N], b[N];
ll c[N];
inline bool check(int x, int y) {
    for (int i = 1; i <= n; i++)
        if (1ll * (Tc - x) * a[i] + 1ll * (Tm - y) * b[i] > c[i])
            return false;
//  cerr << x << ' ' << y << '\n';
    return true;
}
inline ll calc(int x) {
    int l = 0, r = Tm - 1, y = INT_MAX;
//  cerr << x << '\n';
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(x, mid))
            y = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    if (y == INT_MAX)
        return INT_MAX;
    return 1ll * x + y;
}
inline ll Solve() {
    int l = 0, r = Tc - 1;
    ll res = INT_MAX;
    while (l <= r) { // 一开始有一些 delta tc 是不合法的，先找到一个合法的
        int mid = (l + r) >> 1;
        if (calc(mid) == INT_MAX)
            l = mid + 1;
        else
            res = mid, r = mid - 1;
    }
    l = res, r = Tc - 1;
    res = INT_MAX;
    while (l < r) {
        int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (calc(m1) > calc(m2))
            l = m1 + 1;
        else
            r = m2 - 1;
    }
    return calc(l);
}
inline void solve() {
    cin >> n >> Tc >> Tm;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i] >> c[i];
    ll ans = Solve();
    swap(Tc, Tm);
    for (int i = 1; i <= n; i++)
        swap(a[i], b[i]);
    ll Ans = Solve();
    cout << min(ans, Ans) << '\n';
}
signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```

---

## 作者：Bulyly (赞：3)

- [原题链接](https://www.luogu.com.cn/problem/P9124)
### 思路
- 最小的升级次数与 $tc'$ 和 $tm'$ 为多少没有直接关系。最小的升级次数 $T=(tc+tm)-(tc'+tm')$。所以答案只与 $A=tc'+tm'$ 的大小有关。

- $A$ 何时成立？需要在每一个客人的要求下满足。用 $A$ 和 $tc'$ 建立与等待时间的不等关系即可。

- 想到这一步后就没有什么难的了，显然 $A$ 满足二分性质，考虑二分 $A$ 的大小，然后去判断 $tc'$ 是否可以成立即可。

代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long

using namespace std;

const int N=110;

int T;
int n,tc,tm;
struct Node
{
	int a,b,c;
}w[N];
int c[N];
bool check(int x)
{
	int Max=0,Min=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
	{
		
		int m=w[i].c-x*w[i].b;
// 		cout<<m<<" "<<c[i]<<" ";
		if(c[i]>0) Min=min((m/c[i]),Min);
		else if(c[i]==0)
		{
		    if(m<0)  return false;
		}
		else if(c[i]<0)
		{
		    int q=0;
		    if(m%c[i])  q=1;
		    Max=max(m/c[i]+q,Max);
// 			cout<<Max<<" "<<Min<<endl;
		    
		}
	
	}
	if(Max>Min||Max>=x||Max>tc||Min<1||Min<x-tm)  return false;
	
	return true;
}

signed main()
{
// 	cout<<-10/-5<<endl;
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&n,&tc,&tm);
		for(int i=1;i<=n;i++)
		{
			int x,y,z;
			scanf("%lld%lld%lld",&x,&y,&z);
			w[i]={x,y,z};
			c[i]=x-y;
		}
		int l=2,r=tm+tc;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(check(mid))  l=mid+1;
			else r=mid-1;
		}
        int ans=tm+tc-r;
//        for(int i=r;i>=2;i--)  
//		    if(check(i))
//			{
//				ans=i;
//				break;
//			}
// 		cout<<ans<<endl;
		printf("%lld\n",ans);
	}
	
	return 0;
}
```





---

## 作者：快斗游鹿 (赞：3)

2023.4.13 修改了一处错误。

## 思路

显然最小升级次数与对每个烤箱升级了几次无关，而最小升级次数满足二分的性质，所以我们可以考虑二分这个值，再来判断能否满足条件，假设我们给烤饼干的烤箱升级了 $t_c-x$ 次，给烤松饼的烤箱升级了 $t_m-y$ 次。

如何判断呢？对于每个请求，有 $ax+by\le c$，根据不等式的性质，可得 $ax-bx\le c-bx-by$，即 $(a-b)x\le c-b(x+y)$，其中 $x+y$ 就是我们要二分的值。

当 $a-b>0$ 时，有 $x\le \dfrac{c-b(x+y)}{a-b}$，可以用来求出 $x$ 的上界 $r$。当 $a-b=0$ 时，不等式左侧为 $0$，当 $c-b(x+y)<0$ 时，则无解。当 $a-b<0$ 时，有 $x\ge \dfrac{c-b(x+y)}{a-b}$，可以用来求出 $x$ 的下界 $l$。

接着判断是否有解，当 $r>l$ 时，因为 $l\le x\le r$，所以无解。当 $l\ge m$ 或 $r\le 0$ 时，同样无解。当 $l> t_c$ 或 $r< x+y-t_m$ 时，因为 $x\le t_c$ 且 $y\le t_m$，所以无解。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200;
int T,n,a,b,s[N],x[N],y[N],t[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
bool check(int m){
	//ax+by<=c
	//ax-bx<=c-by-bx
	//(a-b)x<=c-b(x+y)
	int minn=1000000005,maxx=0;
	for(int i=1;i<=n;i++){
		int X=t[i]-y[i]*m;
		if(s[i]>0){
			minn=min(X/s[i],minn);
		}
		else if(s[i]==0){
			if(X<0)return 0;
		}
		else{
			if(X%s[i]==0){
				maxx=max(X/s[i],maxx);
			}
			else maxx=max(X/s[i]+1,maxx);
		}
	}
	if(maxx>minn||maxx>=m||minn==0||maxx>a||minn<m-b)return 0;
	return 1;
}
void solve(){
	int l=2,r=a+b,id;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			l=mid+1;id=mid;
		}
		else r=mid-1;
	}
	printf("%lld\n",a+b-id);
}
signed main(){
	T=read();
	while(T--){
		n=read();a=read();b=read();
		for(int i=1;i<=n;i++){
			x[i]=read();y[i]=read();t[i]=read();s[i]=x[i]-y[i];
		}
		solve();
	}
}
```


---

## 作者：是青白呀 (赞：3)

## 题目大意

奶牛的糕点店有 $A$ 和 $B$ 两种糕点，她每次要耗费 $t_c$ 的时间制作一个 $A$，耗费 $t_m$ 的时间制作一个 $B$，且一次只能同时制作一个糕点。奶牛可以花费 $1$ 元将制作 $A$ 或 $B$ 的时间减少 $1$ 分钟，且制作时间必须为正整数。现有 $n$ 个订单，每个订单包含 $a_i$ 个糕点 $A$ 和 $b_i$ 个糕点 $B$，且**从开始处理该订单开始**，顾客最多等待 $c_i$ 分钟后就会离开。奶牛按顺序依次处理每一个订单。为了让每一位顾客都不会因为等待太久而离开，问奶牛至少需要花费多少元？

## 解决方案

若只有一种糕点，很明显可以直接二分时间，并判断每一个订单是否能够满足。现有两种糕点，问两种糕点需要减少的时间之和，我们可以考虑二分减少的总时间（即花的钱的总数）。设二分到要减少的总时间为 $c$，考虑如何判断是否能通过。

考虑订单 $i$，设该订单需要减少的时间至少为 $m_i$，有 $m_i=a_i\times t_c +b_i\times t_m-c_i$。假设减少制作蛋糕 $A$ 的时间为 $x$，减少制作蛋糕 $B$ 的时间为 $y$，我们可以列出下面的式子。

$$
\begin{cases}
x+y=c\\
a_i\times x+b_i\times y ≥m\\
\end{cases}
$$

最终化简得到

$$
\begin{cases}
\displaystyle x≥\frac{m-b_i\times c}{a_i-b_i}, \quad a_i-b_i>0\\
\displaystyle x≤\frac{m-b_i\times c}{a_i-b_i}, \quad a_i-b_i<0\\
a_i \times c≥m, \ \quad \ \ \ \ \ \ \ a_i=b_i
\end{cases}
$$

每个订单都对应一个不等式。

注意为了保证两种糕点的制作时间均为正整数,需满足 $x\in [0,\min(t_c-1,c)]$ 且 $y\in [0,\min(t_m-1,c)]$。化简得到下面的式子。

$$
\begin{cases}
x≥\max(0,c-t_m+1) \\
x≤\min(c,t_c-1)\\
\end{cases}
$$
最后看是否存在一个整数 $x$ 使得所有不等式都成立即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
void read(long long &p){
	long long x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
struct query{
	int a,b,t;
}q[N]; 
int t,n,tc,tM;

bool check(int c){
    int minn=0,maxn;
    minn=max(minn,c-tM+1),maxn=min(c,tc-1);
	for(int i=1;i<=n;i++){
		if(minn>maxn)return 0;
		int a=q[i].a,b=q[i].b;
		int m=tc*a+tM*b-q[i].t;
		if(m<=0)continue;
                if(a==b){
			if(a*c<m)return 0;//x y取值随意 
		}
		int x=(m-b*c)/(a-b);
		if(a-b>0){
			if((m-b*c)%(a-b)&&(m-b*c)/1.0/(a-b)>0)x++;//若有小数，则应大于等于比真实值大的整数
			if(x>maxn)return 0;
			minn=max(minn,x);
		}
		else{
			if((m-b*c)%(a-b)&&(m-b*c)/1.0/(a-b)<0)x--;
			if(x<minn)return 0;
            maxn=min(x,maxn);
		} 
	}
	return 1;
}

signed main(){
	read(t);
	while(t--){
		read(n),read(tc),read(tM);
		for(int i=1;i<=n;i++)
		    read(q[i].a),read(q[i].b),read(q[i].t);
		int le=0,ri=tc+tM-2,ans=tc+tM-2;
		while(le<=ri){
			int mid=(le+ri)>>1;
			if(check(mid))ri=mid-1,ans=mid;
			else le=mid+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：_Cheems (赞：2)

### 题目简介
有 $n$ 个人来买两种东西，要使 $ a_i \times t_c +b_i \times t_m \leq c_i $，你可用一块钱减少 $t_c$ 或 $t_m$ 一个单位时间，但不能减到零。

求最少要花费多少钱，才能使上式成立。

### 思路
假设操作后，$tc$ 减去 $x$，$tm$ 减去 $y$，答案就是 $x+y$。

很容易想到二分，那么二分什么呢？

二分 $x$（或 $y$）吗？不对，不具有单调性，因为还可以调整 $y$。可能把 $x$ 调大点，$y$ 调小点，说不定更优？

但 $x+y$ 一定具有单调性，显而易见。于是问题变为了检验正确性。

怎么检验啊？设 $mid = x+y$，推下不等式呗。

$ a \times (t_c-x)+b \times [t_m-(mid-x)]≤c $。

拆括号得：

$ a \times t_c-a \times x+b \times t_m-b \times mid+b \times x≤c $。

下一步怎么搞？不妨试试：移项把 $a$ 和 $b$ 凑在一起。

$ b \times x-a \times x≤c-a \times t_c-b \times t_m+b \times mid $。 

即：

$ (b-a) \times x≤c-a \times t_c-b \times t_m+b \times mid $。

为了方便，设：

$ k = c-a \times t_c-b \times t_m+ b \times mid $。

于是就能对 $a-b$ 的取值分类讨论啦。

- 若 $a-b>0$：原式不变，$x \leq \frac{k}{a-b}$，向下取值（ floor ）。
- 若 $a-b=0$：若$k<0$，则无解。
- 若 $a-b<0$：变号即可，$x ≥ \frac{k}{a-b}$，向上取值（ ceil ）。

最终会得到一大堆与 $x$ 有关的大小关系式，判断是否有解即可。

关于上下界：

设 $mi \leq x \leq ma$。

- 对于 $mi$：可以一个不减。但如果另一个数没法再减了，则必须要减它了，另一个数可以减去 $y-1$ 次，因此取 $0$ 和 $mid-t_m+1$ 的最大值。
- 对于 $ma$：至多把 $t_c$ 减到 $1$，不过 $mid$ 得够大，因此取 $ t_c-1$ 和 $mid$ 的最小值。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,mid,tic,tim,a[105],b[105],c[105],l,r;
long long dan()
{
	long long mi,ma;
	ma=min(tic-1,mid);
	mi=max((long long)(0),mid-tim+1);  
	for(long long i=1; i<=n;i++)
	{
		long long k=c[i]-a[i]*tic-b[i]*tim+b[i]*mid;
		if(a[i]==b[i]&&k<0) return 0; 
		if(b[i]-a[i]>0) ma=min(ma,(long long)floor(k*1.0/(b[i]-a[i])));
		if(b[i]-a[i]<0) mi=max(mi,(long long)ceil(k*1.0/(b[i]-a[i]))); 
	}
	return mi<=ma;
}
int main()
{
	cin>>t;
	while(t--)
	{
    	scanf("%lld%lld%lld",&n,&tic,&tim);
    	for(long long i=1; i<=n;i++)
    	{
    		scanf("%ld%lld%lld",&a[i],&b[i],&c[i]);
		}
		l=-1,r=tic+tim-1;
		while(l+1<r)
		{
			mid=(l+r)/2;
			if(dan()) r=mid;
			else l=mid; 
		}
		cout<<r<<endl;
	}
    return 0;
}
```

---

## 作者：sane1981 (赞：1)

## 题目解读
**[题目传送门](https://www.luogu.com.cn/problem/P9124)**

简化一下题意：对于已知的 $tc$ 与 $tm$。每次可以把他们变成 $tc-y$ 和 $tm-x$。使得不等式组：
$\begin{cases}a_1(tc-x)+b_1(tm-y)\leq c_1\\a_2(tc-x)+b_2(tm-y)\leq c_2\\\dots\\a_n(tc-x)+b_n(tm-y)\leq c_n\\0 \leq x <tc\\0 \leq y<tm\end{cases}$ 存在正整数解，最小化 $x+y$。

这个这么办？我们可以知道单单二分答案 $x$ 或 $y$ 是不存在单调性的，因为我可以把 $x$ 减去的多一点而把 $y$ 减去的少一点。

但是我们可以肯定 $x+y$ 是一定具有单调性的。毕竟我总和越大，分给 $x$ 与 $y$ 也会越多，也就越容易满足不等条件。（以上为感性理解，巨佬不喜勿喷）。

这样我们就可以去二分答案 $x+y$ 了，也就是把求解问题转化为判断是否满足，假设我们判断一个答案 $key=x+y$ 是否满足不等式组有解。将其代入不等式组得出（这里只是讨论其中一个不等式）

$a_i(tc-key+y)+b_i(tm-y) \leq c_i$

化简整理得：

$(a_i-b_i)y \leq c_i+key \cdot a_i-a_i \cdot tc-b_i \cdot tm$

不妨令 $S=c_i+key \cdot a_i-a_i \cdot tc-b_i \cdot tm$

解 $(a_i-b_i)y \leq S$ ，得出（都在 $y \in \mathbb{Z}$ 的条件下）：

- 当 $a_i=b_i$ 时
	1. 当 $S \geq 0$ 时，$y \in \mathbb{Z}$。
   1. 当 $S < 0$ 时，$y= \varnothing$。
- 当 $a_i<b_i$ 时，$y \in \left[\left\lceil \dfrac{S}{a_i-b_i}\right\rceil,\infty \right)$。
- 当 $a_i>b_i$ 时，$y \in \left(-\infty,\left\lfloor\dfrac{S}{a_i-b_i}\right\rfloor\right]$。

同时，由于 $\begin{cases}0 \leq x<tc\\0 \leq y<tm\\key=x+y \end{cases}$，解得： $\operatorname{max}\{key-tc+1,0\} \leq y \leq \operatorname{min}\{tm-1,key\}$。

那么这个不等式组解就是所有不等式的解的并，判断是否为空。
具体实现详见代码：
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,n;
LL a[105],tC,tM,b[105],c[105];
bool check(LL key){
	LL left=max(key-tC+1,(LL)0),right=min(tM-1,key);
	for(int i=1;i<=n;i++){
		LL S=c[i]+a[i]*key-a[i]*tC-b[i]*tM;
		if(a[i]==b[i]){
			if(S<0) return false;
		}
		else if(a[i]>b[i]) right=min(right,(LL)floor(S*1.0/(a[i]-b[i])));
		else left=max(left,(LL)ceil(S*1.0/(a[i]-b[i])));
//		printf("y∈[%lld,%lld]\n",left,right);
	}
	return right>=left;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld%lld",&n,&tC,&tM);
		for(int i=1;i<=n;i++)
			scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
		LL l=0,r=tC+tM-1,mid,ans;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid)) ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
} 
```
如有不足，则在评论区提出，谢谢。

---

## 作者：cjrqwq (赞：1)

#### 题意概述

有 $n$ 个人来买两种东西，你要使 $a_i \times t_c +b_i \times t_m \leq C_i$，但是不一定成立，所以可用一块钱减少 $t_c$ 或 $t_m$ 一个单位时间。

求最少要花费多少钱，才能使上式成立。

----
#### 思路
不妨解这个不等式。既然要求答案，就将最小花费设为 $k$，将升级 $t_c$ 的次数设为 $x$。（注意：**此处设的 $x$ 只是用于解不等式，不需要枚举。当 $x$ 有解时，$k$ 的值合法**。）

则升级 $t_m$ 的次数为 $k-x$。

之前的式子可以表示为：
$$a_i \times (t_c-x) +b_i \times (t_m-k-x) \leq C_i$$

拆括号，移项得：
$$a_i \times x-b_i \times x \leq C_i-a_i \times t_c-b_i\times t_m+b_i \times k$$

提取公因式，得：
$$(b_i-a_i) \times x \leq C_i-a_i \times t_c-b_i\times t_m+b_i \times k$$

然后要对各种情况分类讨论，以下将右式表示为 $r$，$b_i-a_i$ 表示为 $l$，原式可表示为 $l\times x=r$：

- 当 $l=0$ 时，当 $0 \leq r$ 时，$x$ 有无数解（不用管），当 $r<0$ 时，$x$ 无解。

- 当 $l>0$ 时，移项得：$x \leq \frac{r}{l}$（取上界）。

- 当 $l<0$ 时，移项得，$x \geq \frac{r}{l}$（取下界）。

这样我们就获得了 $x$ 的取值范围。当处理完所有客人，$x$ 仍有正整数解时，说明 $k$ 合法。

只要枚举 $k$，就可以取到 $k$ 的最小值。但是 $0 \leq k \leq t_c+t_m-2$，$2 \leq t_c+t_m \leq 2 \times 10^9$，超时了。

但是，$k$ 是有单调性的！不可能花了更多的钱，但不能解决花更少钱能解决的问题啊！所以直接二分答案。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T;
ll N,TCN,TMN,maa,mab;
ll a[111],b[111],c[111];
bool check(ll mid) {
	ll maax=min(TCN-1,mid),miax=max(0LL,-TMN+mid+1);//最小上界，最大下界
	for(int i=1;i<=N;i++) {
		ll k=c[i]-a[i]*TCN-b[i]*TMN+b[i]*mid;
		if(b[i]-a[i]==0&&k<0) return 0;
        //此处将上界向下取，将下界向上取，可以杜绝 1.3<=1.4
		if(b[i]-a[i]>0) maax=min((ll)floor(k*1.0/(b[i]-a[i])),maax);
		if(b[i]-a[i]<0) miax=max((ll)ceil(k*1.0/(b[i]-a[i])),miax);
	}
	return miax<=maax;
}
int main() {
    cin>>T;
    while(T--) {
        cin>>N>>TCN>>TMN;
        for(int i=1;i<=N;i++) {
            cin>>a[i]>>b[i]>>c[i];
        }
        ll l=-1,r=TCN+TMN-1;//取两个取不到的值
        while(l+1<r) {
            ll mid=l+r>>1;
            if(check(mid)) {
                r=mid;
            }
            else {
                l=mid;
            }
        }
        cout<<r<<"\n";
    }
    return 0;
}
```

---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9124)

其他大佬说得很清楚了，就是二分。

刚开始一看，一个 $t_C$，一个 $t_M$，似乎要二分套二分，但是我们可以把 check 中的式子转换：

$$a\times t_C+b\times t_M\leq c$$

$$a\times t_C\leq c-b\times t_M$$

$$a\times t_C-b\times t_C\leq c-(b\times t_M+b\times t_C)$$

$$(a-b)\times t_C\leq c-b\times (t_M+t_C)$$

其中，$a$、$b$、$c$、$t_C$ 都是确定的，而 $t_C+t_M$ 是时间总和，我们要二分的就是它减去了多少，即 $t_C+t_M-mid$。

从这就能看出只要 $t_C+t_M$ 一定，$t_C$ 和 $t_M$ 分别是多少其实没意义。

因为 $mid$ 和小于等于号右边是反着来的，所以满足 check 时，$mid$ 小了。

于是一个看似正确的代码就能打出来了：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,tc,TM,a[111],b[111],c[111];
bool check(int misu)
{
	for(int i=1;i<=n;i++)
	{
		int p=(a[i]-b[i])*tc;
		int w=c[i]-b[i]*(TM+tc-misu);
		if(p<w)return false;
	}
	return true;
}
int main()
{
	int g;
	cin>>g;
	while(g--)
	{
		cin>>n>>tc>>TM;
		for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
		int l=0,r=tc+TM+10,mid;
		while(l<=r)
		{
			mid=(l+r)/2;
			if(check(mid))r=mid-1;   
			else l=mid+1;
		}
		cout<<mid<<endl;
	}
	return 0;
}
```

这个代码是样例都过不了的，为什么这么说呢，因为这是一个**不等式**，而我们都知道，解一个不等式有小于、等于、大于三种情况。

我们知道，$t_C\geq 1$，所以我们判断 $a-b$ 的值。

当 $a-b>0$，根据不等式的性质，能算出 $t_C$ 的上界是多少。

当 $a-b<0$，同样根据不等式的性质，能算出 $t_C$ 的下界是多少。

当 $a-b=0$，有两种情况：

第一种是 $c-b\times (t_M+t_C)\geq 0$，这种情况下算上界、下界毫无意义，跳过。

第二种是 $c-b\times (t_M+t_C)< 0$，这种情况不用说，直接不满足了，返回 0。

有了上界和下界，我们就能判断 $mid$ 是否合法了。

代码如下：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,tc,TM,a[111],b[111],c[111];
bool check(int misu)
{
	int xj=2147483647,sj=0;
	for(int i=1;i<=n;i++)
	{
		int rig=c[i]-b[i]*misu,hal=a[i]-b[i];
		if(hal>0)xj=min(xj,rig/hal);
		else if(hal==0&&rig<0)return false;
		else if(hal<0)
		{
			if(rig%hal==0)sj=max(sj,rig/hal);
			else sj=max(sj,rig/hal+1);
		}
	}
	if(sj>xj||sj>=misu||xj==0)return false;
	if(sj>tc||xj<misu-TM)return false;
	return true;
}
int main()
{
	int g;
	cin>>g;
	while(g--)
	{
		cin>>n>>tc>>TM;
		for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i];
		int l=2,r=tc+TM,mid,div;
		while(l<=r)
		{
			mid=(l+r)/2;
			if(check(mid))l=mid+1,div=mid;
			else r=mid-1;
		}
		cout<<tc+TM-div<<endl;
	}
	return 0;
}
```

某些大佬可能会想到二分套二分的做法，但是这样会喜提 9 pts。这是因为二分套二分的单调性无法确定，对于小数据也许能过，但对于毒瘤数据就过不了了，可以考虑三分，模板在[这](https://www.luogu.com.cn/problem/P3382)。

---

