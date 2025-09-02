# Frog 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_z

$ N $ 個の足場があります。 足場には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、足場 $ i $ の高さは $ h_i $ です。 ここで、$ h_1\ <\ h_2\ <\ \cdots\ <\ h_N $ です。

最初、足場 $ 1 $ にカエルがいます。 カエルは次の行動を何回か繰り返し、足場 $ N $ まで辿り着こうとしています。

- 足場 $ i $ にいるとき、足場 $ i\ +\ 1,\ i\ +\ 2,\ \ldots,\ N $ のどれかへジャンプする。 このとき、ジャンプ先の足場を $ j $ とすると、コスト $ (h_j\ -\ h_i)^2\ +\ C $ を支払う。

カエルが足場 $ N $ に辿り着くまでに支払うコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ C\ \leq\ 10^{12} $
- $ 1\ \leq\ h_1\ <\ h_2\ <\ \cdots\ <\ h_N\ \leq\ 10^6 $

### Sample Explanation 1

足場 $ 1 $ → $ 3 $ → $ 5 $ と移動すると、コストの総和は $ ((3\ -\ 1)^2\ +\ 6)\ +\ ((5\ -\ 3)^2\ +\ 6)\ =\ 20 $ となります。

### Sample Explanation 2

答えは 32-bit 整数型に収まらない場合があります。

### Sample Explanation 3

足場 $ 1 $ → $ 2 $ → $ 4 $ → $ 5 $ → $ 8 $ と移動すると、コストの総和は $ ((3\ -\ 1)^2\ +\ 5)\ +\ ((5\ -\ 3)^2\ +\ 5)\ +\ ((10\ -\ 5)^2\ +\ 5)\ +\ ((13\ -\ 10)^2\ +\ 5)\ =\ 62 $ となります。

## 样例 #1

### 输入

```
5 6
1 2 3 4 5```

### 输出

```
20```

## 样例 #2

### 输入

```
2 1000000000000
500000 1000000```

### 输出

```
1250000000000```

## 样例 #3

### 输入

```
8 5
1 3 4 5 10 11 12 13```

### 输出

```
62```

# 题解

## 作者：lottle1212 (赞：47)

# [原题传送门](https://www.luogu.com.cn/problem/AT_dp_z)

- **Update on 2023.7.24，修复了图床。**

## Part 0

斜率优化本质上就是[单调队列优化](https://xyzl.blog.luogu.org/DQ-OP-DP)的升级版。

在学习斜率优化之前，请先熟练掌握单调队列优化。

## Part 1

对于这一道题，我们很容易得出朴素 DP 的做法。不难发现：

$$dp_i = \min_{0 \leq j < i} \{dp_j + (h_i - h_j)^2 + C\}$$

于是我们可以先写下朴素 DP，以便对拍。

时间复杂度 $O(n^2)$。

**TLE Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mxn = 2e5;
const int N = mxn + 10;
ll n, h[N], dp[N], C;
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> C;
	for(int i = 1; i <= n; ++ i) cin >> h[i];
	for(int i = 2; i <= n; ++ i){
		dp[i] = 1e16;
		for(int j = 0; j < i; ++ j)
			dp[i] = min(dp[i], dp[j] + (h[i] - h[j]) * (h[i] - h[j]) + C);
	}
	cout << dp[n];
	return 0;
} 
```

## Part 2

观察上面的动态转移方程，我们可以将 $\min$ 以内的式子化简为：

$$dp_j + h_i^2 + h_j^2 - 2h_ih_j + C$$

其中，$h_i^2, C$ 这些项与 $j$ 无关，我们可以将其看作常量取出，则式子剩下：

$$dp_j + h_j^2 - 2h_ih_j$$

而 $dp_j, h_j^2$ 仅与 $j$ 有关，设 $\operatorname{f}(j) = dp_j + h_j^2$，则式子变为：

$$\operatorname{f}(j) - 2h_ih_j$$

再设 $k = -2h_i$，则：

$$\operatorname{f}(j) + h_j \times k$$

至此，动态转移方程已化简完成。

## Part 3

此时，设 $j1 < j2$，且 $j2$ 不比 $j1$ 优，仅当：

$$\operatorname{f}(j1) + h_{j1} \times k \leq \operatorname{f}(j2) + h_{j2} \times k$$

移项得：

$$h_{j1} \times k - h_{j2} \times k \leq \operatorname{f}(j2) - \operatorname{f}(j1)$$

两边同时除以 $h_{j1} - h_{j2}$，由于 $h_{j1} - h_{j2} < 0$，所以不等式要变号：

$$k \geq \frac{\operatorname{f}(j2) - \operatorname{f}(j1)}{h_{j1} - h_{j2}}$$

将 $k = -2h_i$ 代入：

$$-2h_i \geq \frac{\operatorname{f}(j2) - \operatorname{f}(j1)}{h_{j1} - h_{j2}}$$

不等式两边同时乘 $-1$：

$$2h_i \leq \frac{\operatorname{f}(j1) - \operatorname{f}(j2)}{h_{j1} - h_{j2}}$$

$$\frac{\operatorname{f}(j1) - \operatorname{f}(j2)}{h_{j1} - h_{j2}} \geq 2h_i$$

此时不等式的左边类似于求斜率的公式，故称为**斜率优化**。

## Part 4

本文开头已经说过，斜率优化本质上是单调队列优化。因此，我们必须时刻维护队列中元素的单调性。

设 $\operatorname{slope}(i, j) = \frac{\operatorname{f}(i) - \operatorname{f}(j)}{h_{i} - h_{j}}$，表示 $i, j$ 两点之间的斜率。

若有 $pre, mid, nxt$ 三个节点，且 $pre < mid < nxt$，若使 $mid$ 为最优决策点，必须满足：

$$\operatorname{slope}(pre, mid) \leq 2h_i$$

表示不满足 $pre$ 比 $mid$ 优，且：

$$\operatorname{slope}(mid, nxt) \geq 2h_i$$

表示满足 $mid$ 比 $nxt$ 优，即：

$$\operatorname{slope}(pre, mid) \leq \operatorname{slope}(mid, nxt)$$

这时，若有三点状态如下图：

![](https://s1.ax1x.com/2023/07/13/pChqnsg.png)

通过观察，易得：

$$\operatorname{slope}(1,2) \geq \operatorname{slope}(2,3)$$

因此，$2$ 号点一定不是最优决策点，我们可以将其删去。

![](https://s1.ax1x.com/2023/07/13/pChqZz8.png)

最后，你会发现这东西就被维护成了一个**凸包**。

![](https://s1.ax1x.com/2023/07/13/pChqmQS.png)

## Part 5

当维护成一个凸包后，我们就可以对队列中的元素进行二分，找到斜率大于等于 $2h_i$ 的最小节点，然后进行转移。时间复杂度 $O(n \log n)$。

但此题中，$h$ 是一个递增序列，并不是无序的，因此，我们可以直接以单调队列的形式不断扔掉头元素，从而找到最优决策点，而无需二分。时间复杂度 $O(n)$。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mxn = 2e5;
const int N = mxn + 10;
ll C, h[N], dp[N]; int head, tail, q[N], n;
double Y(int i) { return dp[i] + h[i] * h[i]; }
double X(int i) { return h[i]; }
double slope(int i, int j) { return (Y(i) - Y(j)) / (X(i) - X(j)); }//计算斜率
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> C;
	for(int i = 1; i <= n; ++ i) cin >> h[i];
	q[head = tail = 1] = 1;//单调队列初始化，青蛙原来在位置1
	for(int i = 2; i <= n; ++ i) {
		while(head < tail && slope(q[head], q[head + 1]) <= 2 * h[i]) ++ head; //若前两个元素不满足前一个元素更优，将前一个元素出队
		int j = q[head]; dp[i] = dp[j] + (h[i] - h[j]) * (h[i] - h[j]) + C; //进行转移
		while(head < tail && slope(q[tail - 1], q[tail]) >= slope(q[tail], i)) -- tail; //维护凸包
		q[++ tail] = i; //入队
	}
	cout << dp[n];
	return 0;
}
```

---

## 作者：GaryH (赞：15)

# AT4547 题解
## Upd 9.19.2021:修改了一个表述问题
可能是楼上的巨佬认为斜率优化太简单了，就讲的非常简略，那作为一个刚学斜率优化的新手，我就来略微详细一点的讲讲斜率优化是如何优化动态规划的转移的。

看到题面，我们首先可以显然的推出一个DP式：

记 $dp_i$ 为跳到第 $i$ 个位置的最小花费，则我们有：

$dp_i=min(dp_j+(h_j-h_i)^2+c) ,0<j<i$.

我们注意到，将式子中的 $(h_j-h_i)^2$ 可以拆开为：

$(h_j-h_i)^2 = h_j^2 - 2 \times h_j \times h_i + h_i^2$.

而原转移式中的 $h_i^2+c$ 与 $j$ 的取值并无关联, 故我们可以将它们从 $min$ 式中提出来：

$dp_i=min(dp_j+h_j^2-2 \times h_j \times h_i)+h_i^2+c$.

我们发现， $h_i^2+c$ 与 $h_j^2$ 两项都很好处理，但就是中间的 $2 \times h_j \times h_i$ 这个与 $i$ 和 $j$ 都有关联的项很不好处理。

我们假设转移式中，使得 $dp_i$ 最小的一个 $j$ 值为 $k$ ,那么我们此时就可以把 $min$ 给去掉，即：

$dp_i=dp_k+h_k^2-2 \times h_k \times h_i+h_i^2+c$

对式子变一个形，就有：

$dp_k+h_k^2=(2 \times h_i) \times h_k+dp_i-h_i^2-c$.

发现这个很像什么？是不是很像一个 $dp_k+h_k^2$ 关于 $h_k$ 的一次函数？

那么这时候我们就用一个二维坐标系来显式地表示这个状态转移方程：

将 $(x=h_k,y=dp_k+h_k^2)$ 这个二元组抽象成在二维坐标系上的一个点，而

$dp_k+h_k^2=(2 \times h_i) \times h_k+dp_i-h_i^2-c$

就是一个形如 $y=kx+b$ 的一次函数，其中：

$k=2 \times h_i$ ,

$b=2 \times dp_i-h_i^2-c$ .

我们再观察一下函数的特征，就可发现，函数的截距，即 $b$ 竟然只与我们需要最小化的 $dp_i$ 和一些常数有关！

那么，此时问题就转化为了一个线性规划问题：

有一条斜率固定，最初位置对应截距为 $-inf$ 的直线，将直线慢慢上挪，直到直线第一次碰到某一个点，求出此时直线的截距。

更形式化的说，就是给定了直线的斜率，要求从已有的 $n$ 个点中找出一个点使直线经过该点，并要求这样确定的直线是所有 $n$ 种不同的可能直线中，截距最小的一条，并求出该直线的截距。

这个又怎么做呢？我们可以想到，如果 $n$ 个点形成了一个下凸壳，

即对于任意 $i$ ，都有

$((y_i-y_{i-1})/(x_i-x_{i-1})>(y_i-y_{i+1})/(x_i-x_{i+1}))$ ，

那么此时我们就只需要找到当前凸壳中的某个点，是该点与其左边点斜率比 $k$ 小，右边的比 $k$ 大，那么这个点就是答案直线所对应的点了。

当然，若是有一个点与其相邻的点间没有形成凸壳，即若有 $i$ 不满足上述对于斜率的要求，那么这个点不可能作为最优点被选择，因为无论在什么情况下，其两个相邻点中必有一个比它更优。

所以，我们要实现一个快速维护支持插入，弹出的下凸壳的数据结构，这里我们使用单次均摊复杂度 $O(1)$ 的单调队列来维护凸壳，故时间复杂度是 $O(N)$ 的。

**code：**

```
const int N(2e5+10);

int n,c;

int h[N];
int q[N];
int dp[N];

inline double X(int i){return h[i];}
inline double Y(int i){return (dp[i]+(h[i]*h[i]));}
inline double K(int i,int j){return ((Y(j)-Y(i))/(X(j)-X(i)));}

signed main(){
	n=read(),c=read();
	rep(i,1,n)h[i]=read();
	int head=1,tail=1;
	q[1]=1+(dp[1]=0);
	rep(i,2,n){
		while(head<tail&&(h[i]<<1)>=K(q[head],q[head+1]))++head;
		dp[i]=dp[q[head]]+(h[q[head]]-h[i])*(h[q[head]]-h[i])+c;
		while(head<tail&&K(i,q[tail])<=K(q[tail],q[tail-1]))--tail;
		q[++tail]=i;
	} cout<<dp[n];
	return 0;
}

```

---

## 作者：DengDuck (赞：5)

最近在学李超线段树，相对于优雅理性的斜率优化，李超线段树主打的就是一个嗯造。

时间复杂度为 $\mathcal O(n \log^2n)$，不过李超线段树优化 DP 能解决的问题更多，而且更简单，无脑嗯造真的非常好啊！

首先我们来看看 $\mathcal O(n^2)$ 的式子：

$$
f_i=\min_{j=1}^{i-1}({f_j+(h_i-h_j)^2})+C
$$

考虑变形。

$$
\begin{aligned}
&f_j+(h_i-h_j)^2+C\\
&=f_j+h_i^2-2h_ih_j+h_j^2+C\\
&=(f_j+h_j^2)-2h_ih_j+(C+h_i^2)
\end{aligned}
$$

注意，第一个括号的值只受 $j$ 影响，第二个括号不收 $j$ 影响。

我们建立 $n$ 个一次函数 $F_j(x)$，表示选择第 $j$ 项时受 $j$ 影响的项的值。

得:

$$
F_j(x)=-2h_jx+f_j+h_j^2
$$

因此我们求解 $f_i$ 相当于求前 $i-1$ 的一次函数在平面直角坐标系上经过 $x=h_i$ 的最小纵坐标值，再加上定值即可。

直接李超线段树即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long long 
using namespace std;
const LL N=2e5+5;
const LL M=1e6;
const LL inf=1e18;
LL n,c,a[N],f[N],cnt,tot,rt;
struct seg
{
	LF k,b;
}s[N];
struct node
{
	LL l,r,id;
}t[N<<4];
bool pd(LL x,LL y,LL k)
{
	LF k1=s[x].k*k+s[x].b;
	LF k2=s[y].k*k+s[y].b;
	if(k1==k2)return x<y;
	return k1<k2;
}
void ins(LL &rt,LL l,LL r,LL x,LL y,LL id)
{
	if(rt==0)rt=++cnt;
	LL mid=(l+r)/2;
	if(x<=l&&r<=y)
	{
		if(pd(id,t[rt].id,l)&&pd(id,t[rt].id,r))
		{
			t[rt].id=id;
			return;
		}
		if(pd(t[rt].id,id,l)&&pd(t[rt].id,id,r))return;
		if(pd(id,t[rt].id,mid))swap(id,t[rt].id);
		if(pd(id,t[rt].id,l))ins(t[rt].l,l,mid,x,y,id);
		if(pd(id,t[rt].id,r))ins(t[rt].r,mid+1,r,x,y,id);
	}
	else
	{
		if(x<=mid)ins(t[rt].l,l,mid,x,y,id);
		if(mid+1<=y)ins(t[rt].r,mid+1,r,x,y,id);
	}
}
LL query(LL rt,LL l,LL r,LL x)
{
	if(l==x&&r==x)return t[rt].id;
	LL mid=(l+r)/2,ans=0;
	if(x<=mid)ans=query(t[rt].l,l,mid,x);
	else ans=query(t[rt].r,mid+1,r,x);
	if(pd(t[rt].id,ans,x))ans=t[rt].id;
	return ans;
}
int main()
{
	scanf("%lld%lld",&n,&c);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	s[0]={0,inf};
	s[++tot]={-2*a[1],a[1]*a[1]};
	ins(rt,1,M,1,M,tot);
	for(int i=2;i<=n;i++)
	{
		LL t=query(rt,1,M,a[i]);
		f[i]=s[t].k*a[i]+s[t].b+a[i]*a[i]+c;
		s[++tot]={-2*a[i],f[i]+a[i]*a[i]};
		ins(rt,1,M,1,M,tot);
	}
	printf("%lld",f[n]);
}

```

---

## 作者：Gorenstein (赞：5)

提供一种和题解区相比更加机械的斜率优化的方法。

设 $f_i$ 为至 $i$ 为止的最小花费，显然有转移：

$$
f_i=\min_{j<i}\left\{f_j+(h_i-h_j)^2\right\}+C
$$

假设有两个决策 $j,k(j<k)$，直接令 $k$ 优于 $j$，考虑 $k$ 需要满足的条件：

$$
f_j+(h_i-h_j)^2>f_k+(h_i-h_k)^2
$$

$$
f_j+h_i^2-2h_ih_j+h_j^2>f_k+h_i^2-2h_ih_k+h_k^2
$$

因为我们需要最小化 $f_i$，因此需要分离和 $i$ 有关的项：

$$
f_j-f_k+h_j^2-h_k^2>2h_i(h_j-h_k)
$$

由于 $j<k$，因此 $h_j-h_k<0$。从而：

$$
\frac{f_j+h_j^2-f_k-h_k^2}{h_j-h_k}<2h_i
$$

现在假设有三个点 $j_1,j_2,j_3$，设前后两边上左式分别为 $k_1,k_2$。考虑：
- 若 $k_1<2h_i$，则 $j_2$ 优于 $j_1$；
- 若 $k_2\geqslant 2h_i$，则 $j_3$ 不优于 $j_2$。

由此可得，当这三个决策点在 $h_i$ 为横坐标、$f_i+h_i^2$ 为纵坐标的坐标系上构成下凸壳时，$j_2$ 才有可能成为最优决策。因此新的决策点进入时，用一个单调队列去维护。

转移时，在队首不断比较队首两点斜率和 $2h_i$，如果满足上式，说明 $k$ 优于 $j$，弹出 $j$，直至不满足为止。

---

## 作者：_Ponder_ (赞：3)

[Frog 3](https://www.luogu.com.cn/problem/AT_dp_z)

### 题目大意

~~题意都这么明确了还要这个干什么。~~

存在 $n$ 个点，每个点有一个属性 $h_i$，$h_i$ 单增，从点 $i$ 移动到点 $j(j>i)$ 的代价是 $(h_i-h_j)^2+C$，其中 $C$ 是给定的常数，求从点 $1$ 移动到点 $n$ 的最小代价。

### 思路分析

[斜率优化 DP](https://www.cnblogs.com/TKXZ133/p/17532085.html) 板题。

设 $f_i$ 表示从点 $1$ 移动到点 $i$ 的最小代价，容易列出状态转移方程：

$$f_i=\min_{j<i}(f_j+(h_i-h_j)^2+C)$$

直接转移是 $O(n^2)$ 的，考虑斜率优化：

$$\begin{aligned}f_i&=f_j+h_i^2-2h_ih_j+h_j^2+C\\(f_i-h_i^2)&=(f_j+h_j^2+C)-(2h_i)(h_j)\end{aligned}$$

将第 $i$ 个状态视为平面上的点 $(h_i,f_i+h_i^2+C)$，问题转化为求斜率固定的直线的截距的最小值，考虑到 $h_i$ 单增，故点的横坐标单增，斜率也单增。使用单调队列维护下凸壳即可。

### 代码

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N=200200;
#define int long long
#define y(i) (i[f]+i[h]*i[h]+C)
#define x(i) (i[h])
#define k(i) (2*i[h])

int n,C,hh,tt;
int q[N],f[N],h[N];

double slope(int i,int j){
    return 1.0*(y(i)-y(j))/(x(i)-x(j));
}

signed main(){
    scanf("%lld%lld",&n,&C);
    for(int i=1;i<=n;i++) scanf("%lld",&i[h]);
    hh=1;tt=1;hh[q]=1;
    for(int i=2;i<=n;i++){
        while(hh<tt&&slope(hh[q],(hh+1)[q])<k(i)) hh++;
        i[f]=hh[q][f]+(i[h]-hh[q][h])*(i[h]-hh[q][h])+C;
        while(hh<tt&&slope(i,(tt-1)[q])<slope((tt-1)[q],tt[q])) tt--;
        (++tt)[q]=i;
    }
    cout<<n[f]<<'\n';
    return 0;
}
```

---

## 作者：novax (赞：3)

[题面](https://www.luogu.com.cn/problem/AT4547)

### 题意

从 $i$ 号石头跳到 $j$ 号石头的费用为 $(h_i - h_j)^2 + C$，求从 $1$ 号跳到 $N$ 号的最小费用。

### 思路

设 $F_i$ 表示跳到 $i$ 号石头所需最小花费，则根据题意，可列 $O(N^2)$ 的转移方程：

$F_i= \min(F_j + ( h_i - h_j )^2 + C ) ,1 \leq j < i$.

化简方程，得：

$F_i= \min( F_j +  {h_i}^2 - 2h_ih_j + {h_j}^2 + C ) ,1 \leq j < i$.

于是 $F_i$ 即为在所有合法范围内的 $F_j +  {h_i}^2 - 2h_ih_j + {h_j}^2 + C$ 中最小的值，当此式取得最小值时，$\min$ 可以去掉，于是原式化为：

$F_i= F_j +  {h_i}^2 - 2h_ih_j + {h_j}^2 + C $.

对于每一个 $i$，我们都需要找到相应的令右侧取得最小值的 $j$，而当 $i$ 固定时，原转移方程中所有与 $i$ 相关的量是不变的，可以看作常量；而与 $j$ 相关的量在变化，可以看作变量。因此，可以将方程中与 $i$ 相关的量移到一侧：

$F_j + {h_j}^2 =  2 h_i h_j + F_i - {h_i}^2 - C$.

等号左侧只有变量，$2 h_i h_j$ 项是常量与变量相乘，而等号右侧其余部分都是常量。

此时，可以令 $y = F_j + {h_j}^2$，$k = 2h_i$，$x = h_j$，$b = F_i - {h_i}^2 - C$。于是原方程可以被表示为 $y = kx + b$ 的一次函数直线形式。

我们成功把朴素的转移方程化成了“斜率式”。

因为我们要求的 $F_i$ 在斜率式的 $b$ 一项中，而又希望 $F_i$ 尽可能大，所以我们所取的斜率式的截距也要尽可能大。

此时的每一个 $j$，都可以在平面上表示为坐标 $(h_j,F_j + {h_j}^2)$ 的一个点。而对于每一个 $i$，其在斜率式中对应的斜率 $2h_i$ 是固定不变的。当某个 $i$ 对应斜率的直线正好经过了某个 $j$ 对应的点时，可以根据斜率方程求出此时对应的截距 $b$，进而根据 $i$ 求出此时所得的 $F_i$ 值，即使用斜率式完成了一次动规的状态转移。

但仅仅这样还不够。我们观察到斜率式中的 $k,x$ 两项都具有单调性。即 $i$ 所对应的直线斜率随 $i$ 递增；$j$ 所对应点的横坐标也随 $j$ 递增。由此我们可知为使截距最小，符合条件的点一定在所有 $j$ 对应点的下凸包上。

因此我们可以根据斜率维护一个下凸包。下凸包的性质是点的斜率单调递增，由此想到可用单调队列维护。当队首斜率小于当前斜率时弹出队首，当新点插入时弹出队尾维护单调性。然后转移 $F_i$，取队首元素，用斜率式计算新的 $F_i$ 完成转移。

这样我们就用**斜率优化**将转移的总复杂度降为了 $O(N)$。

### 代码

```cpp
#include <cstdio>
const int Nx=200010;
int N;
long long C,H[Nx],F[Nx],K[Nx],Y[Nx];
int que[Nx],L,R;
double slope(int a,int b)
{
	double xx,yy;
	yy=Y[b]-Y[a];
	xx=H[b]-H[a];
	return yy/xx;
}
int main()
{
	scanf("%d%lld",&N,&C);
	int i,j,k;
	for(i=1;i<=N;i++)
	{
		scanf("%lld",&H[i]);
		K[i]=2*H[i];
	}
	F[1]=0;Y[1]=H[1]*H[1];
	que[1]=1;
	L=1;R=1;
	for(i=2;i<=N;i++)
	{
		while(L<R&&slope(que[L],que[L+1])<K[i]*1.0)
			L++;
		j=que[L];
		F[i]=Y[j]-K[i]*H[j]+H[i]*H[i]+C;
		Y[i]=F[i]+H[i]*H[i];
		while(L<R&&slope(que[R-1],que[R])>slope(que[R],i))
			R--;
		que[++R]=i;
	}
	printf("%lld\n",F[N]);
}
```


---

## 作者：longlinyu7 (赞：2)

# 分析题意
题目很简短，也很容易理解，青蛙需要从 $1$ 跳到 $n$，保证高度单调递增，一次可以跳任意格，但是每次跳跃需要耗费 $(h_{i}-h_{j})^2+c$，求最小消耗。

# 思路
很明显可以看出来使用动态规划，设 $f_{i}$ 表示跳到第 $i$ 个石头上最小花费，则朴素的转移方程为：
$$f_{i}=\min_{1<j<i}f_j+(h_i-h_j)^2+c$$

拆开二次项得：
$$ f_i=\min_{1<j<i}f_j+ h_j^2-2h_ih_j+h_i^2+c$$

这样转移的时间复杂度为 $O(n^2)$，无法接受。

易知，当 $f_j+ h_j^2-2h_ih_j+h_i^2+c$ 最小时 $f_i$ 取得最优，而 $f_j+h_j^2$ 只与 $j$ 有关，将这两项移动到左边，取消 $\min$。

$$f_j+h_j^2=2h_ih_j+f_i-h_i^2-c$$
观察发现，上述式子很像一次函数 $y=kx+b$，以平面直角坐标系表示。
- $f_j+h_j^2$ 就是 $y$ 即纵坐标。
- $h_j$ 就是 $x$ 即横坐标。 
- $2h_i$ 就是 $k$ 即斜率。
- $f_i-h_i^2-c$ 就是 $b$ 即该直线的截距。

每个决策点 $j$ 可以对应坐标为 $(h_j,f_j+h_j^2)$ 的点。

在 $i$ 不变的情况下，截距 $h_i^2-c$ 是不变的，因此要求 $f_i$ 最小，可以转化为求某一条直线的截距最小。

则目标转为，找到一个 $j$ 使得经过该点，斜率为 $2h_i$ 的一次函数的截距最小。

因为 $h_i$ 满足严格单增，所以斜率 $2h_i$ 也是单增的。下面规定线段 $AB$ 的斜率为 $K_{AB}$。

易知选哪个决策点与 $K_{i},K_{AB},K_{BC},K_{AC}$ 的大小有关。目前知道 $K_{BC} < K_{AC}<0<K_{AB}$。讨论 $K_{i}$ 的大小。

当 $K_{i} \le K_{BC}$ 时。 过 $A$ 点时截距最小，$A$ 点最优。
![](https://pic1.zhimg.com/80/v2-9fc4d3f9028b4841efe3f66a695ee2d0_720w.webp)

当 $K_{BC} \le K_{i} \le K_{AC}$ 时。过 $A$ 点的直线截距最小，$A$ 点最优。 
![](https://pic4.zhimg.com/80/v2-a203e37eb49c71403fef3ef13b5f16c3_720w.webp)

当 $K_{AC} \le K_{i} \le K_{AB}$ 时，无论 $K_{i}$ 取正或是取负，都是 $C$ 点最优。
![](https://pic2.zhimg.com/80/v2-2b9134536d7b7685614defd1675f2f8d_720w.webp)

![](https://pic4.zhimg.com/80/v2-36688312042efe7be5b97d9a1f3e55ab_720w.webp)

当 $K_{AB}\le K_{i}$ 时，过 $C$ 点的直线截距最小，$C$ 点最优。
![](https://pic1.zhimg.com/80/v2-cdefd6d780a9e0720532cf6daf4d5474_720w.webp)

根据上述讨论，我们可以发现两个结论。
1. 无论 $K_{i}$ 取何值，最优点都不可能是 $B$，事实上，$B$ 这样的点，相对于 $A$ 和 $B$ 来说，被称作“上凸点”,在取最小值时，上凸点永远不可能是最优的。对于本题而言，我们只需要维护一个下凸包就可以了。
1. 发现当 $K_{i} \le K_{AC}$ 时，永远是 $A$ 点最优，而当 $K_{i} \ge K_{AC}$ 时，永远是 $C$ 点最优。$K_{i}=K_{AC}$ 就是分界线。

利用第二条结论，还有 $K_{i}$ 是单增的这条性质。如果找到一个点$p_{i}$，其左边的点是 $p_{i-1}$，其右边的点是 $p_{i+1}$，满足 $K_{p_{i-1}p_{i}} \le K_{i} \le K_{p_{i}p_{i+1}}$。 则 $p_{i}$ 就是当前的全局最优点。 
- 因为 $K_{i} \ge K_{p_{i-1}p_{i}}$，所以 $p_{i}$ 比前面所有的点都要优。
- 因为 $K_{i} \le K_{p_{i}p_{i+1}}$，所以 $p_{i}$ 比后面所有的点都要优。

那我们如何找到这个最优点，答案就是用**单调队列**来维护，因为 $K_{i}$ 满足单调性，其是单增的。
- 对于头部而言，需要保证头部前两个节点间的斜率大于  $K_{i}$，如果斜率小于等于 $K_{i}$ 则移出队列，因此可以保证队首是最优解。
- 对于尾部而言，加入新节点时，需要进行去除上凸点操作。设 $t$ 为尾部节点，$p$ 为新加入的最优点，则需要满足 $K_{t-1,t}\le K_{t,p}$。

#### 复杂度分析

利用单调队列维护转移是 $O(1)$，动态规划枚举是 $O(n)$，总复杂度是 $O(n)$，完全可以通过此题。

## 总结
本题目不难，属于斜率优化裸题，不过需要注意一个坑，青蛙从 $1$ 开始跳，需要直接从 $2$ 开始枚举。

如果你通过此题发现了斜率优化的魅力，可以尝试一下 [P3195 玩具装箱](https://www.luogu.com.cn/problem/P3195)，这也是一个斜率优化模板题，比本题稍难一些。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long //观察数据范围，明显要开 long long 
const int N=300005;
int n,h[N],head=1,tail,q[N],c,f[N];
double  slope(int i,int j){  // 计算两点间斜率
    return (((f[j]+h[j]*h[j])-(f[i]+h[i]*h[i]))*1.0/(2*h[j]-2*h[i]));
}
signed main(){
    cin>>n>>c;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    tail++;
    q[tail]=1;
    for(int i=2;i<=n;i++){  // 从2开始枚举
        while(head<tail && slope(q[head],q[head+1])<= h[i])head++; // 维护头部
        f[i]=f[q[head]]+(h[i]-h[q[head]])*(h[i]-h[q[head]])+c;  //赋值
        while(head<tail && slope(q[tail-1],q[tail]) >=slope(q[tail],i))tail--;  // 维护尾部
        q[++tail]=i;
    }
    cout<<f[n];
    return 0;
}
```

---

## 作者：Super_Cube (赞：2)

# Solution

斜率优化 dp 的模板题。

设 $dp_i$ 表示跳到了第 $i$ 块石头上的最小花费，那么有：$dp_i=\displaystyle\min_{j=1}^{i-1}\lbrace dp_j+(h_i-h_j)^2+C\rbrace$，因为可以从之前的 $1\sim i-1$ 中的任意一块石头跳过来进行转移。

直接做复杂度过不去，考虑斜率优化，先将 $\min$ 去掉，改写此式为：$dp_j+{h_j}^2=2h_ih_j+dp_i-{h_i}^2-C$。

然后我们对于上式进行换元：

$$
\begin{cases}
y=dp_j+{h_j}^2\\
k=2h_i\\
x=h_j\\
b=dp_i-{h_i}^2-C\\
\end{cases}
$$

这样就可以很清晰的看出上式是类似于一次函数的。

我们为了让 $dp_i$ 能够取得最小值，那么就要最小化截距 $b$，因为截距中除了 $dp_i$ 都是定值，只要截距最小，$dp_i$ 肯定也是最小的。

所以我们要对于所有的决策点维护一个下凸包，这样我们拿斜率为 $k$ 的直线去切的时候截距 $b$ 才能最小化。

这道题还有一个很舒服的地方就是保证了 $h$ 单增，那么说明我们刚刚的斜率 $k$ 是单增的，就可以直接用单调队列维护凸包斜率，时间复杂度 $O(n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define X(i) (a[i])
#define Y(i) (dp[i]+1ll*a[i]*a[i])
long long dp[200005];
int a[200005];
inline double slope(int l,int r){
	return (Y(r)-Y(l))*1.0/(X(r)-X(l));
}
std::deque<int>q;
int n;
long long m;
int main(){
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	q.push_back(1);//注意是从第一块石头开始跳
	for(int i=2;i<=n;++i){
		while(q.size()>1&&slope(q[0],q[1])<=(a[i]<<1))q.pop_front();//把斜率比当前切线小的直接删掉
		dp[i]=dp[q[0]]+1ll*(a[i]-a[q[0]])*(a[i]-a[q[0]])+m;//最优决策点转移
		while(q.size()>1&&slope(*(q.end()-2),q.back())>=slope(q.back(),i))q.pop_back();//维护斜率单增
		q.push_back(i);
	}
	printf("%lld",dp[n]);
	return 0;
}
/*
dp[i]=dp[j]+(h[i]-h[j])^2+C
dp[j]+h[j]^2=2*h[i]*h[j]+dp[i]-h[i]^2-C
*/
```
# Afterword

这道题的加强版 [P4655](/problem/P4655)，dp 式子长的差不多，区别在于斜率不单调，所以要用一些高级的东西来维护，有兴趣可以去做一下。

~~我就是从这道题翻双倍经验过来的。~~

---

## 作者：zhicheng (赞：2)

### 分析

首先可以列出最基础的 DP 式子。设 $dp_i$ 表示跳到 $i$ 的最小花费，有：
$$dp_i=\min\limits_{1\leq j < i
}\{dp_j+(h_i-h_j)^2\}+C$$

$$dp_1=0$$

直接算的话时间复杂度 $O(n^2)$。

然后化简一下式子，有：

$$dp_i=\min\limits_{1\leq j<i}\{dp_j+h_j^2-2h_ih_j\}+h_i^2+C$$

然后就可以使用李超线段树维护了。具体地，计算出一个 $dp_j$ 之后，我们并不知道后面的哪个 $h_i$ 会从它转移过去，因此我们对 $h$ 维护一棵李超线段树，把 $h_i$ 看作自变量，插入一条斜率为 $-2h_j$，截距为 $dp_j+h_j^2$ 的直线。每次要求 $dp_i$ 时询问 $h_i$ 处值最小的一条直线的值再加上 $h_i^2+C$ 即可。时间复杂度 $O(n\log n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200010,M=1000010;
int h[N],p[M<<2];
struct line{
	ll k,b;
}pp[N];
ll calc(int now,int x){
	return pp[now].k*x+pp[now].b;
}
bool cmp(int a,int b,int x){
	return calc(a,x)<calc(b,x);
}
void update(int now,int l,int r,int rt){
	int mid=(l+r)>>1;
	if(cmp(now,p[rt],l)&&cmp(now,p[rt],r)){
		p[rt]=now;
		return;
	}
	else if(!cmp(now,p[rt],l)&&!cmp(now,p[rt],r)){
		return;
	}
	if(cmp(now,p[rt],mid)){
		swap(now,p[rt]);
	}
	if(cmp(now,p[rt],l)){
		update(now,l,mid,rt<<1);
	}
	if(cmp(now,p[rt],r)){
		update(now,mid+1,r,rt<<1|1);
	}
}
int query(int x,int l,int r,int rt){
	int mid=(l+r)>>1,res;
	if(l==r){
		return p[rt];
	}
	if(x<=mid){
		res=query(x,l,mid,rt<<1);
	}
	else{
		res=query(x,mid+1,r,rt<<1|1);
	}
	if(cmp(p[rt],res,x)){
		res=p[rt];
	}
	return res;
}
int main(){
	int n,summ=0,maxx=0;
	ll ans,c;
	scanf("%d%lld",&n,&c);
	for(int i=1;i<=n;i++){
		scanf("%d",&h[i]);
		maxx=max(maxx,h[i]);
	}
	pp[0].b=1e18;
	pp[++summ].k=-2*h[1];
	pp[summ].b=1ll*h[1]*h[1];
	update(summ,1,maxx,1);
	for(int i=2;i<=n;i++){
		ans=calc(query(h[i],1,maxx,1),h[i])+1ll*h[i]*h[i]+c;
		pp[++summ].k=-2*h[i];
		pp[summ].b=ans+1ll*h[i]*h[i];
		update(summ,1,maxx,1);
	}
	printf("%lld",ans);
}
```

---

## 作者：xueruo (赞：2)

# 题意
有 $N$ 个石头，编号为 $1,2,\dots,N$，第 $i$ 个高为 $h_i$。保证 $h_i$ 严格单调递增。  
青蛙在第一个石头上，可以跳到石头编号为 $i+1,i+2,\dots,N$。当他跳到编号 $j$ 石头时的花费是 $(h_i-h_j)^2+C$。求跳到编号为 $N$ 个石头的**最小花费**。 
# 思路
首先考虑暴力。   
我们可以直接暴力枚举每个 $i$，然后计算 $f_i = \min(f_i, f_j + (h_i - h_j) \times (h_i - h_j) + C \times (h_i - h_j) \times (h_i - h_j) + C)$。  
```cpp
for (int i = 2; i <= n; i++) { 
	f[i] = 1e18; 
	for (int j = 1; j < i; j) { 
	f[i] = min(f[i], f[j] + (h[i] - h[j]) * (h[i] - h[j]) + C * (h[i] - 	h[j]) * (h[i] - h[j]) + C); 
	}
}
```
暴力的时间复杂度为 $\Theta(n^2)$。  
原式子可以化成 $dp_k + h_k^2 =(2 \times h_i) \times h_k + dp_i - h_i^2 -c$ 的一次函数式子。用单调队列维护下凸壳即可就好了。    
此时斜率为定值，求出截距。
```cpp
#include <iostream> 
#include <cstring> 
#include <algorithm> 
#define int long long
using namespace std; 
const int N = 4e5 + 10; 
int n, q[N], hh, tt; 
int h[N], f[N], C; 
double slope(int j, int k) { //计算斜率
	return (double)(f[j] + h[j] * h[j] - f[k] - h[k] * h[k]) / (h[j] - h[k]);
} 
signed main() { 
	cin >> n >> C; 
	for (int i = 1; i <= n; i++) cin >> h[i];
	hh = 1, tt = 1; q[tt] = 1;
	for (int i = 2; i <= n; i++) { 
    	//单调队列维护最值
		while (hh < tt && slope(q[hh], q[hh + 1]) <= 2 * h[i]) hh++; 
		int j = q[hh];
		f[i] = f[j] + (h[i] - h[j]) * (h[i] - h[j]) + C;
		while (hh < tt && slope(q[tt - 1], q[tt]) >= slope(q[tt], i)) tt--;
		q[++tt] = i; 
	}
   cout << f[n];
   return 0; 
}
```  
~~已经很认真地看过没有空格错误了，求过。~~

---

## 作者：spire001 (赞：1)

## 思路

没什么可说的，这是一道斜率优化模板题。

重点就是推式子。

可以很容易的得到普通的状态转移方程为：$dp_i = \max(dp_i , dp_{j-1} + (h_i-h_j)^2+C),i\in[1 , n],j\in[1 , i]$。

然后就是化成分式：

我们记 $f(x)=dp_i
+sum_i^2$ ，其中 $sum$ 为前缀和数组。

若存在 $j$ 比 $i$ 更优，斜率即为:
$
\frac{f(i) - f(j)}{sum_i-sum_j}
$。

## CODE

```cpp
# include <iostream>
# include <cstring>
# include <cstdlib>
# include <ctime>
# include <algorithm>
# include <queue>
# include <stack>
# include <iomanip>
# include <cctype>
# include <vector>
# include <bitset>
# include <climits>
# include <random>

using namespace std;
# define int long long
template <typename T>
void Read(T & num)
{
	num = 0;short f = 1;char c;
	for(c = cin.get(); c < '0' || c > '9'; c = cin.get()) if(c == '-') f = -f;
	for(; c <= '9' && c >= '0'; c = cin.get()) num = (num << 1) + (num << 3) + (c ^ 48);
	num *= f;return;
}
template <typename T>
void Write(T num)
{
	if(num < 0) {num = ~num + 1;cout.put('-');}
	if(num > 9) Write(num / 10);
	cout.put((num % 10) ^ 48);
}
template <typename T>
void Write(T num , char __c)
{
	Write(num);
	cout.put(__c);return;
}
constexpr int N = 500001;
int n , m;
int a[N] , sum[N];
template <typename T>
struct _deque{
	_deque() {p = head = tail = nullptr;}
	size_t SIZE;//
	T *p;
	T *head , *tail;
	T & operator [] (int num) const
	{
		return *(head + (num - 1));
	}
	void Init(T num)
	{
		p = new T [num * 2 + 2];
		T *tmp = p;
		tmp += num;
		head = tail = tmp;
		tail--;SIZE = num;
		return;
	}
	int size() {return tail - head + 1;}
	void push_front(T num)
	{
		head--;
		*head = num;
		return;
	}
	void push_back(T num)
	{
		tail++;
		*tail = num;
		return;
	}
	void pop_back()  {tail--;return;}
	void pop_front() {head++;return;}
	bool empty() {return tail >= head;}
	void resize(size_t new_size)
	{
		delete [] p;
		Init(new_size);
		return;
	}
	void clear() {delete [] p;}
	bool fail_bad()
	{
		return abs(tail - p <= SIZE) && abs(p - head) <= SIZE;
	}
	T back() {return *tail;}
	T front() {return *head;}
	T * begin() {return head;}
	T * end() {return tail + 1;}
};
int dp[N];
# define sum a
inline int getdp(int i , int j)
{
	return dp[j] + m + (sum[i] - sum[j]) * (sum[i] - sum[j]);
}
inline int getfz(int i , int j)
{
	return dp[i] - dp[j] + (sum[i] - sum[j]) * (sum[i] + sum[j]);//平方差公式稍微化简一下。。
}
inline int getfm(int i , int j)
{
	return sum[i] - sum[j];
}
inline int getk(int i)
{
	return sum[i] << 1;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	Read(n);Read(m);
	_deque <int> q;//STLdeque太慢
	q.Init(n << 1);
	for(int i = 1; i <= n; i++) Read(a[i]);
	q.push_back(1);
	for(int i = 2; i <= n; i++)
	{
		while(q.size() > 1 && getfz(q[2] , q.front()) <= getk(i) * getfm(q[2] , q.front())) q.pop_front();
		dp[i] = getdp(i , q.front());

		while(q.size() > 1 && getfz(i , q.back()) * getfm(q.back() , q[q.size() - 1]) <= getfz(q.back() , q[q.size() - 1]) * getfm(i , q.back())) q.pop_back();//这都是斜率优化模板
		q.push_back(i);
//		Write(q.front() , '\n');
//		Write(q.back() , '\n');
	}
	Write(dp[n]);
	return 0;
}
```

---

## 作者：reclusive (赞：1)

## 题目描述

将一个序列分成若干段，每一段的价值为 $(h_i-h_j)^2+C$，求价值和的最小值。

## 具体思路

设 $f_i$ 表示前 $i$ 个数分成若干段的价值和的最小值，并且 $j+1 \sim i$ 被分成了一段。

那么 $f_i$ 的状态应该由 $f_j$ 转移过来。

状态转移方程：

$$f_i=\min \limits_{0 \le j<i} \{ {f_j+(h_i-h_j)^2+C} \}$$

形如：

$$f_i=\min \limits_{0 \le j<i} \{ {f_j+val} \}$$

这一类动态规划的优化分为三种：**单调队列**，**斜率优化**，**四边形不等式**。

而这几种优化方式对应的状态转移方程是不同的。

**单调队列**：单调队列对应的 $val$ 一般是一次的，这题不符合。

**斜率优化**：斜率优化对应的 $val$ 一般是二次的，这题符合。

**四边形不等式**：四边形不等式对应的 $val$ 需要满足四边形不等式。

我们现在面临选择斜率优化还是四边形不等式优化。显然斜率优化的时间复杂度 $O(n)$ 是要优于四边形不等式的时间复杂度 $O(n \log n)$ 的，因此我们考虑斜率优化。

这里考虑将状态转移方程式化为截距式：$b=y-kx$。

$$f_i-C=\min \limits_{0 \le j<i} \{ {f_j+h_i^2+h_j^2-2h_ih_j} \}$$

$$f_i-h_i^2-C=\min \limits_{0 \le j<i} \{ {f_j+h_j^2-2h_ih_j} \}$$

令 $b=f_i-h_i^2-C$，$y=f_j+h_j^2$，$k=2h_i$，$x=h_j$。

由于题目中说 $h_i$ 单调递增，这里的斜率 $k$ 应该是单调递增的，因此维护下凸壳。

那么我们该怎么维护呢？

我们说了，斜率是单调的，那么自然就想到用单调队列维护下凸壳。

显然，我们每次的最优决策点，即让截距 $b$ 取到的最小值的点 $j$，应当满足它左边的斜率小于当前的斜率，右边的斜率大于当前的斜率。

![](https://cdn.luogu.com.cn/upload/image_hosting/5foyjypa.png?x-oss-process=image)

因此我们取队头时应当将所有斜率小于等于 $k$ 的点全部踢出单调队列。

然后我们在队尾维护单调队列的斜率单调递增，即每次将斜率比当前直线斜率大的踢出单调队列。

## 注意

青蛙一开始站在第一块石头上，因此 dp 要从 $2$ 开始。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=211000;
LL h[N],f[N];
int l,r,Q[N];
double X(int j){return 1.0*h[j];}
double Y(int j){return 1.0*(f[j]+h[j]*h[j]);}
double slop(int j1,int j2){
	if(X(j2)==X(j1))return 1e18;
	return (Y(j2)-Y(j1))/(X(j2)-X(j1));
}
int main(){
	int n;LL c;scanf("%d%lld",&n,&c);
	for(int i=1;i<=n;i++){
		scanf("%lld",&h[i]);
	}
	memset(f,0x3f,sizeof(f));
	f[1]=0;
	l=1,r=1,Q[l]=1;
	for(int i=2;i<=n;i++){
		while(l<r&&slop(Q[l],Q[l+1])<=2.0*h[i])l++;
		int j=Q[l];
		f[i]=f[j]+(h[i]-h[j])*(h[i]-h[j])+c;
		while(l<r&&slop(Q[r-1],Q[r])>=slop(Q[r],i))r--;
		Q[++r]=i;
	}
	printf("%lld",f[n]);
	return 0;
}
```

---

## 作者：Walter_Fang (赞：1)

### 大致题意

有 $n$ 个点，每个点有一个属性 $h_i$，$h_i$ 单调递增，从 $i$ 点移动到大于 $i$ 的 $j$ 点，需要付出 $(h_i-h_j)^2+c$ 的代价，其中 $c$ 题中已给出，求点 $1$ 移动到点 $n$ 的最小代价。

### 思路/解析

设 $f_i$ 表示从点 $1$ 移动到点 $i$ 的最小代价，容易列出状态转移方程为 $f_i=\min_{j<i}(f_j+(a_i-a_j)^2+c)$。

直接转移的时间复杂度是 $O(n^2)$，无法通过本题，于是运用斜率优化，公式就变为了

$$\begin{aligned}f_i&=f_j+a_i^2-2a_ia_j+a_j^2+c\\(f_i-a_i^2)&=(f_j+a_j^2+c)-(2a_i)(a_j)\end{aligned}$$

将状态 $i$ 视为平面上的点 $(a_i,f_i+a_i^2+c)$，问题就变成了求最小的斜率固定的直线的截距，因为 $a_i$ 单调递增，所以点的坐标也单调递增，斜率也单调递增。使用单调队列维护下凸壳，即可通过本题。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+10;
ll n,c,i,l,r,h[N],q[N],dp[N];
double Y(ll j){return dp[j]+h[j]*h[j];}
double X(ll i){return h[i]<<1;}
double K(ll i,ll j){return (Y(i)-Y(j))/((X(i)-X(j)));}
int main(){
	cin>>n>>c;
	for(i=1;i<=n;i++)cin>>h[i];
	l=r=q[1]=1;
	for(i=2;i<=n;i++){
		while(l<r&&h[i]>=K(q[l],q[l+1]))l++;
		dp[i]=dp[q[l]]+c+(h[i]-h[q[l]])*(h[i]-h[q[l]]);
		while(l<r&&K(q[r-1],q[r])>=K(q[r],i))r--;
		q[++r]=i;
	}
	cout<<dp[n]<<'\n';
}
```

---

## 作者：Night_sea_64 (赞：0)

不得不说，这题是十分板子的斜率优化。

首先一眼 dp。状态没的说，$f$ 为 dp 数组，$f_i$ 就表示第 $1$ 个点到第 $i$ 个点的最小花费。先列出暴力算法的状态转移，以下 $a$ 数组表示原来的 $h$：

$$f_i=\min\limits_{1\le j<i}f_j+a_i^2-2a_ia_j+a_j^2+C$$

可以看到我把平方式拆开了，这样有利于进一步优化。

将上式变为 $y=kx+b$ 的形式，其中 $x,y$ 只与 $j$ 有关，其他只与 $i$ 有关或是常数。

$$f_j+a_j^2=2a_ia_j-a_i^2-C+f_i$$

$f_j+a_j^2$ 为 $y$，$2a_i$ 为 $k$，$a_j$ 为 $x$，剩下的部分为 $b$。

题目中说了 $a$ 单调递增，所以 $x,k$ 都是单调递增的，也就只需要维护一个上凸壳，每次将斜率 $\le k$ 的从队头删除，并从队尾插入即可。

```cpp
#include<iostream>
#define int long long
using namespace std;
int n,c,a[200010],f[200010];
struct node{int x,y;}q[200010];
int head=1,tail=0;
double slope(node x,node y){
    return (x.y-y.y)*1.0/(x.x-y.x);
}
signed main()
{
    cin>>n>>c;
    for(int i=1;i<=n;i++)cin>>a[i];
    q[++tail]={a[1],a[1]*a[1]};
    for(int i=2;i<=n;i++)
    {
        int k=2*a[i];
        while(head<tail&&slope(q[head],q[head+1])<=k)head++;
        int x=q[head].x,y=q[head].y;
        f[i]=y-k*x+a[i]*a[i]+c;
        node now={a[i],f[i]+a[i]*a[i]};
        while(head<tail&&slope(q[tail],q[tail-1])>=slope(q[tail],now))tail--;
        q[++tail]=now;
    }
    cout<<f[n]<<endl;
    return 0;
}
```

---

## 作者：Supor__Shoep (赞：0)

我们先排除掉数据范围，思考一下如何朴素地 DP。

设 $dp_i$ 表示到达 $i$ 石头的最小花费，考虑枚举 $j\in[1,i-1]$ 并用 $dp_j$ 去更新 $dp_i$。不难得到转移式：

$$dp_i=\min\{dp_j+(h_i-h_j)^2+C\}$$

这样，$O(n^2)$ 的朴素做法就完成了。

但是 $n\leq 2\times 10^5$，有点爆炸，考虑优化 DP。

发现其中的平方式很烦，我们尝试把它拆掉：

$$dp_i=\min\{dp_j+h_i^2+h_j^2-2h_ih_j+C\}$$

猛然发现这就是一个典型的斜率式子！于是我们把**仅与 $i$ 有关**的变量放在等号左边，剩下的放在右边，则有了下面的式子：

$$dp_i-h_i^2=-2h_ih_j+dp_j+h_j^2+C$$

将其转换成一次函数解析式 $y=kx+b$：

$$\begin{cases} y=dp_i-h_i^2\\ x=h_i \\k=-2h_j\\ b=dp_j+h_j^2+C \end{cases}$$

这个时候我们就可以使用比斜率优化更无脑的**李超线段树**了！我们每次更新完 $i$ 的答案之后，我们插入一条 $y=-2h_ix+dp_i+h_i^2+C$ 的一次函数。以后每次查询时，就查询 $x=h_i$ 时 $y$ 值最大的函数，这个时候通过 $dp_i=y+h_i^2$ 直接转移就行了。

代码如下：

```cpp
#include<bits/stdc++.h>
#define inf 1000000
#pragma GCC optimate(2,3,"Ofast")
using namespace std;
const int MAXN=1e6+5;
template<typename T>
void read(T &x)
{
	x=0;
	short flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	x*=flag;
}
int n;
long long C;
struct Lines
{
	long long k,b;
}ls[MAXN];
long long Get(int id,long long x){ return ls[id].k*x+ls[id].b; }
struct Segment_Tree
{
	int cnt;
    struct Node
	{
        int lc,rc,val;
    }c[MAXN<<5];
    int New()
	{
        cnt++;
        c[cnt].val=c[cnt].lc=c[cnt].rc=0;
        return cnt;
    }
    int down(int q,int L,int R,int id)
	{
        if(!q)	q=New();
        int mid=L+R>>1;
        if(Get(id,mid)<Get(c[q].val,mid))	swap(c[q].val,id);
        if(Get(id,L)<Get(c[q].val,L))	c[q].lc=down(c[q].lc,L,mid,id);
        if(Get(id,R)<Get(c[q].val,R))	c[q].rc=down(c[q].rc,mid+1,R,id);
        return q;
    }
    int Add(int q,int L,int R,int l,int r,int id)
	{
        if(!q)	q=New();
        if(l<=L&&R<=r)
		{
            q=down(q,L,R,id);
            return q;
        }
        int mid=L+R>>1;
        if(l<=mid)	c[q].lc=Add(c[q].lc,L,mid,l,r,id);
        if(mid<r)	c[q].rc=Add(c[q].rc,mid+1,R,l,r,id);
        return q;
    }
    long long query(int q,int L,int R,int x)
	{
        if(!q)	return 1e18;
        if(L==R)	return Get(c[q].val,x);
        int mid=L+R>>1;
		long long res;
        if(x<=mid)	res=query(c[q].lc,L,mid,x);
        else	res=query(c[q].rc,mid+1,R,x);
        if(res>Get(c[q].val,x))	res=Get(c[q].val,x);
        return res;
    }
}T;
long long a[MAXN];
long long dp[MAXN];
int main()
{
	read(n),read(C);
	for(int i=1;i<=n;i++)   read(a[i]);
	int num=0;
	T.New(),ls[0].b=1e18;
	ls[++num]=(Lines){-2*a[1],a[1]*a[1]+C},T.Add(1,1,inf,1,inf,num);
	for(int i=2;i<=n;i++)
	{
		dp[i]=T.query(1,1,inf,a[i])+a[i]*a[i];
		ls[++num]=(Lines){-2*a[i],dp[i]+a[i]*a[i]+C},T.Add(1,1,inf,1,inf,num);
	}
	cout<<dp[n];
	return 0;
}
```

---

## 作者：KidA (赞：0)

这题的朴素 dp 是显然的。

令 $dp_i$ 表示跳到第 $i$ 个石头的最小花费，有转移方程：

$$
dp_i=\min_{j=1}^{i-1}\{dp_j+(h_i-h_j)^2+C\}
$$

直接转移是 $O(n^2)$ 的，考虑优化。

首先对于 $\min$ 以内的式子化简，得：

$$
dp_j+h_i^2+h_j^2-2h_ih_j+C
$$

将与 $j$ 无关的项剔除，得：

$$
dp_j+h_j^2-2h_ih_j
$$

令 $f_i$ 表示 $dp_i+h_i^2$，$k$ 表示 $-2h_i$，得：

$$
f_j+kh_j
$$

此时，我们考虑有两个转移点 $j_1,j_2$。

若 $j_1<j_2$ 且 $j_2$ 一定不比 $j_1$ 更优，仅当：

$$
f_{j_1}+kh_{j_1} \le f_{j_2}+kh_{j_2} 
$$

移项，得：

$$
kh_{j_1}-kh_{j_2} \le f_{j_2}-f_{j_1}
$$

两边同时除以 $h_{j_1}-h_{j_2}$（不等式要变号，因为 $h_{j_1}-h_{j_2}<0$）得：

$$
k \ge \dfrac{f_{j_2}-f_{j_1}}{h_{j_1}-h_{j_2}}
$$

代入 $k=-2h_i$，得：

$$
-2h_i \ge \dfrac{f_{j_2}-f_{j_1}}{h_{j_1}-h_{j_2}}
$$

两边同时乘以 $-1$，得：

$$
2h_i \ge \dfrac{f_{j_1}-f_{j_2}}{h_{j_1}-h_{j_2}}
$$

然后我们发现这个式子与斜率的计算公式十分相似，于是考虑斜率优化。

具体地，我们分析三个候补转移节点 $p_1,p_2,p_3$，它们满足 $p_1<p_2<p_3$。

令 $\operatorname{slope}(i,j)$ 表示 $\dfrac{f_i-f_j}{h_i-h_j}$。

若 $p_2$ 是最优转移节点，则有：

$$
2h_i \ge \operatorname{slope}(p_1,p_2)
$$

表示 $p_1$ 一定不比 $p_2$ 更优，并且有：

$$
2h_i \le \operatorname{slope}(p_2,p_3)
$$

表示 $p_3$ 一定不比 $p_2$ 更优，也即，当：

$$
\operatorname{slope}(p_1,p_2) \le \operatorname{slope}(p_2,p_3)
$$

时，有 $p_2$ 为 $p_1,p_2,p_3$ 中的最优转移节点。

这样每次选取最优转移节点，它们便组成了一个凸包。

由于题目保证 $h_i$ 单调递增，

于是我们采用单调队列维护此凸包，

每次转移时从队头寻找最优转移节点，

转移完成后再从队尾弹出不是最优转移节点的节点即可。

这样转移的单次均摊时间复杂度降至 $O(1)$，总时间复杂度为 $O(n)$。

[实现](https://www.luogu.com.cn/paste/tdoydyz0)是简单的。

---

## 作者：Aisaka_Taiga (赞：0)

~~第一次自己推出来斜率优化。~~

设 $f_i$ 表示在石头 $i$ 落脚的最小花费。

看到题目咱可以写出一个 $O(n^2)$ 的 DP 式子：

$$
f_i= \min_{j=1}^{i-1}\{f_j + (h_i - h_j)^2 + C\}
$$

然后咱给他拆一下：

$$
f_i = f_j + h_{i}^2 + h_{j}^2 -2\times h_i \times h_j + C
$$

咱设两个决策点 $a,b$ 且 $a < b$，如果 $a$ 优于 $b$，那么要满足：

$$
f_a + h_{i}^2 + h_{a}^2 -2\times h_i \times h_a + C < f_b + h_{i}^2 + h_{b}^2 -2\times h_i \times h_b + C
$$

$$
f_a - f_b + h_a^2 - h_b^2 < 2\times h_i\times(h_a-h_b)
$$

$$
\frac{f_a - f_b + h_a^2 - h_b^2}{h_a - h_b} < 2\times h_i
$$

因为 $h_i$ 严格单调递增，所以咱可以维护一个下凸壳进行斜率优化。

**注意青蛙在第一块石头上！**

```cpp
/*
 * @Author: Aisaka_Taiga
 * @Date: 2023-11-15 17:08:33
 * @LastEditTime: 2023-11-15 17:38:43
 * @LastEditors: Aisaka_Taiga
 * @FilePath: \Desktop\ATDPZ.cpp
 * The heart is higher than the sky, and life is thinner than paper.
 */
#include <bits/stdc++.h>

#define pf(x) ((x)*(x))
#define int long long
#define DB double
#define N 200010

using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){if(c == '-') f = -1; c = getchar();}
    while(c <= '9' && c >= '0') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return x * f;
}

int n, m, q[N], f[N], h[N];

/*
f[i] = min(f[j] + (h[i] - h[j])^2 + C);
f[i] = f[j] + h[i]^2 + h[j]^2 - 2 * h[i] * h[j] + C;
*/

inline int X(int x){return h[x];}

inline int Y(int x){return f[x] + pf(h[x]);}

inline DB xl(int i, int j){return (Y(j) - Y(i)) * 1.0 / (X(j) - X(i));}

signed main()
{
    int n = read(), m = read();
    for(int i = 1; i <= n; i ++) h[i] = read();
    int H = 1, t = 1;
    q[1] = 1;
    for(int i = 2; i <= n; i ++)
    {
        while(H < t && xl(q[H], q[H + 1]) <= 2 * h[i]) H ++;
        f[i] = f[q[H]] + pf(h[i] - h[q[H]]) + m;
        while(H < t && xl(q[t], i) <= xl(q[t - 1], q[t])) t --;
        q[++ t] = i;
    }
    cout << f[n] << endl;
    return 0;
}
```

---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_dp_z)

## 分析

根据题意我们很好设计出 DP 状态。用 $f_i$ 表示当前在第 $i$ 个石头的最小花费。得出转移方程：

$$f_i = \min_{j<i} \{ f_j + (h_i - h_j)^2 + C \}$$

朴素做是 $O(n^2)$ 的。

观察 DP 式子，发现状态数已经是 $O(n)$ 的了，现在得要优化转移。发现它长的像个斜率优化。先拆括号：

$$f_i = \min_{j<i} \{ f_j + h_i^2 - 2h_ih_j+ h_j^2+ C \}$$

与 $j$ 有关的保留在一起 ：

$$f_i = \min_{j<i} \{ f_j - 2h_ih_j+ h_j^2 \} + h_i^2+ C$$

根据套路，对于两个决策 $j>k$，若 $j$ 更优，则有：

$$f_j - 2h_ih_j + h_j^2 < f_k - 2h_ih_k + h_k^2$$

$$\dfrac{(f_j+h_j^2) - (f_k+h_k^2)}{h_j-h_k} <2h_i$$

用单调队列维护下凸包即可 $O(n)$ 及解决问题。

## 注意
由于青蛙一开始就在 $1$ 石头，代码里记得提前把 $1$ 放入队列中

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 10;
int n, q[N];
ll h[N], f[N], c;

double slope(int i, int j) {
	return 1.0 * (f[i] + h[i] * h[i] - f[j] - h[j] * h[j]) / (h[i] - h[j]);
}

int main() {
	cin >> n >> c;
	for (int i = 1; i <= n; i++) cin >> h[i];
	int head = 1, tail = 1;
	q[++tail] = 1;
	for (int i = 2; i <= n; i++) {
		while (head < tail && slope(q[head + 1], q[head]) < 2 * h[i]) head++;
		f[i] = f[q[head]] + (h[i] - h[q[head]]) * (h[i] - h[q[head]]) + c;
		while (head < tail && slope(i, q[tail]) < slope(q[tail], q[tail - 1])) tail--;
		q[++tail] = i;
	}
	cout << f[n];
	return 0;
}
```


---

## 作者：Forg1weN (赞：0)

# 题面


有 $N$ 个石头，编号为 $1,2,\dots,N$，第 $i$ 个高为 $h_i$。保证 $h$ 严格单调递增。

有一只青蛙在第一个石头上，它可以跳到石头编号为 $i+1,i+2,\dots,N$。当他跳到编号 $j$ 石头时的花费是
$(h_i-h_j)^2+C$。求跳到编号为 $N$ 石头的最小花费。


- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ C\ \leq\ 10^{12} $
- $ 1\ \leq\ h_1\ <\ h_2\ <\ \cdots\ <\ h_N\ \leq\ 10^6 $

# Solution
记 $f_{i}$ 为青蛙跳到编号为 $i$ 的石头后的最小花费。

由于跳到石头 $i$ 之前必须跳到之前的一个石头 $j$，所以有转移方程：

$f_{i}=f_{j}+(h_{i}-h_{j})^2+C$

这个式子明显符合**斜率优化**，往这方面考虑。

对于两个决策 $j,k$，令 $j<k$，则决策 $j$ 严格优于决策 $k$ 时有：

$f_{j}+(h_{i}-h_{j})^2+C  \geq f_{k}+(h_{i}-h_{k})^2+C$

拆括号，简单变换后移项可得：

$-2\times h_{i}\times h_{j}+2\times h_{i}\times h_{k} \geq f_{k}+h_{k}^2-f_{j}-h_{j}^2$

继续推可得：

$2\times h_{i} \geq \dfrac{f_{k}+h_{k}^2-f_{j}-h_{j}^2}{h_{k}-h_{j}}$

令 $a_{i}=f_{i}+h{_i}^2$

则有：$2\times h_{i} \geq \dfrac{a_{k}-a_{j}}{h_{k}-h_{j}}$

也就是说，满足如上条件的情况下，决策 $j$ 一定劣于决策 $k$。

由于 $h_{i}$ 单调递增，满足单调性，使用普通算法即可。

## 实现
斜率优化的基本流程如下：

- 弹出队列首端满足如上条件的队头，这是因为队内明显有优于队头的决策。
- 求出 $f_{i}$ 值。
- 更新队列。

代码如下所示：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL maxn=2e5+10;
LL n,c,hd,tl;
LL f[maxn],h[maxn];
LL q[maxn];
double a(LL i) {
	return f[i]*1.0+h[i]*h[i];
}
double k(LL i,LL j) {
	return (a(j)*1.0-a(i))/(h[j]*1.0-h[i]);
}
LL query(LL i,LL j) {
	return (h[i]-h[j])*(h[i]-h[j]);
}
int main() { 
	scanf("%lld%lld",&n,&c);
	for(LL i=1;i<=n;i++)
		scanf("%lld",&h[i]);
	hd=1,tl=1;
	q[hd]=1;
	for(LL i=2;i<=n;i++) {
		while(hd<tl && 2*h[i]>=k(q[hd],q[hd+1]))hd++;
		f[i]=f[q[hd]]+query(q[hd],i)+c;
		while(hd<tl && k(q[tl-1],q[tl]) >= k(q[tl-1],i) )tl--;
		q[++tl]=i; 
	}
	printf("%lld",f[n]);
	return 0; 
} 
```


---

## 作者：EastPorridge (赞：0)

斜率优化 dp 好题，提供一种李超线段树的写法。

### 题目分析：

首先我们很容易的到一个 $O(n^2)$ 的转移式：

$$dp[i] = \min ((h_i - h_j)^2 + dp[j]) +c,(j < i)$$


考虑将式子拆开变成：

$$dp[i]= \min (-2 \times h_i \times h_j + {h_j}^2 +dp[j] ) + c$$

下面就可以直接上李超线段树了，将 $h_i$ 看做横坐标，斜率就是 $-2 \times h_j$，截距就是 ${h_j}^2+dp[j]$，每次更新 $dp[i]$ 就是在 $h[i]$ 上的最小值。

时间复杂度：$O(n \log n)$。

其实，进一步观察可以发现这是一个一次函数，我们可以用单调队列维护一下下凸壳，做到整体复杂度 $O(n)$。

### Code.

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e6+10,M=2e5+10;
int tr[N<<2],n;  ll c,h[N],f[M];
struct node
{
	ll k,b;
	ll calc(ll x) {return x*k+b;}
} a[M];
void modify(int u,int l,int r,int x)
{
	int mid =(l + r) >> 1;
	if(a[x].calc(mid) < a[tr[u]].calc(mid)) swap(tr[u],x);
	if(a[x].calc(l) < a[tr[u]].calc(l)) modify(u<<1,l,mid,x);
	if(a[x].calc(r) < a[tr[u]].calc(r)) modify(u<<1|1,mid+1,r,x);
}
ll query(int u,int l,int r,int x)
{
	if(l == r) return a[tr[u]].calc(x);
	int mid = (l + r) >> 1; ll res=a[tr[u]].calc(x);
	if(x <= mid) res=min(res,query(u<<1,l,mid,x));
	else res=min(res,query(u<<1|1,mid+1,r,x));
	return res; 
}
int main()
{
	scanf("%d%lld",&n,&c); a[0].b=1e18;
	for(int i=1;i<=n;i++) scanf("%lld",h+i);
	a[1].k=-2*h[1]; a[1].b=h[1]*h[1];
	modify(1,0,1e6,1);
	for(int i=2;i<=n;i++)
	{
		f[i]=query(1,0,1e6,h[i])+h[i]*h[i]+c;
		a[i].k=-2*h[i]; a[i].b=h[i]*h[i]+f[i];
		modify(1,0,1e6,i);
	}
	printf("%lld\n",f[n]);
	return 0;
}
```


---

## 作者：_Dreamer_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT4547)

[ATcoder DP 专题 传送门](https://atcoder.jp/contests/dp/tasks)

### 题意简述
有 $N$ 个石头，编号为 $1,2,\dots,N$ ，第 $i$ 个高为 $h_i$ **注意 $h_i$ 递增**

有一只青蛙在第一个石头上，它可以跳到石头编号为 $i+1,i+2,\dots,N$ 当他跳到编号 $j$ 石头时的花费是 $(h_i-h_j)^2$+C  求跳到第 $n$ 块石头上的最小花费

### Solution

既然是 DP 专题 首先 设计状态

设 $dp[i]$ 表示 跳到 第 $i$ 个石头上的最小花费

可得转移方程

$$ dp[i]=\min_{j<i}\{dp[j]+(h_j-h_i)^2+c\} $$

时间复杂度 $O(n^2)$ 不能接受

考虑优化 发现这个式子  可以斜率优化

转化后式子变成  形如 $y=k\,x+b$ 的

$$ dp[j] +h^2_j=dp[i] +2\times h_i\times h_j-h_i^2-C$$

维护最小值

用单调队列维护一个 下凸壳即可

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200005;
int dp[N],h[N];
int n,c;
double Y(int j){return dp[j]+h[j]*h[j];}
double b(int i){return dp[i]-h[i]*h[i]-c;}
double X(int i){return 2*h[i];}
double K(int i,int j){return (Y(i)-Y(j))/((X(i)-X(j)));}
int q[N];
int head,tail;
signed main()
{
	scanf("%lld%lld",&n,&c);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&h[i]);
	}
	memset(dp,0x3f,sizeof dp);
	dp[1]=0;head=tail=q[1]=1;
	for(int i=2;i<=n;i++)
	{
		while(head<tail&&h[i]>=K(q[head],q[head+1]))head++;
		dp[i]=dp[q[head]]+c+(h[i]-h[q[head]])*(h[i]-h[q[head]]);
		while(head<tail&&K(q[tail-1],q[tail])>=K(q[tail],i))tail--;
		q[++tail]=i;
	}
	printf("%lld",dp[n]);
	return 0;
}
```

---

