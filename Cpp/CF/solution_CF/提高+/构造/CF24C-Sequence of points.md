# Sequence of points

## 题目描述

题目给出一个点 $M_0$ 和 $N$ 个点 $N_0,N_1...N_{n-1}$ 。

已知 $M_1$ 和 $M_0$ 关于 $N_0$ 对称，$M_2$ 和 $M_1$ 关于 $N_1$ 对称，以此类推，即 $M_{j-1}$ 和 $M_j$ 关于 $N_{(j-1) \bmod n}$ 对称。现在问 $M_x$ 是多少。

## 样例 #1

### 输入

```
3 4
0 0
1 1
2 3
-5 3
```

### 输出

```
14 0
```

## 样例 #2

### 输入

```
3 1
5 5
1000 1000
-1000 1000
3 100
```

### 输出

```
1995 1995
```

# 题解

## 作者：XL4453 (赞：2)

您要能像别的题解一样一眼看出这个性质，那这篇推导过程就可以跳过了。

---
### 解题思路：

首先给出对称的公式：点 $(a,b)$ 关于 $(c,d)$ 的对称点是 $(2c-a,2d-b)$。这个是显然的，过程就不写了，比较简单的可以用中点公式或者全等三角形推出来。

然后考虑对于更多点的连续对称，点 $(a,b)$ 关于 $(c,d)$ 对称一次，然后关于 $(e,f)$ 对称一次的坐标是 $(2e-2c+a,2f-2d+b)$，再关于点 $(g,h)$ 对称一次的坐标是 $(2g-2e+2c-a,2h-2f+2d-b)$。以此类推。

这样就立刻可以写出一个更漂亮的形式了。

如果设起始坐标为 $(x_0,x_0)$，一共对称了 $n$ 次，每一次的坐标为 $(x_i,y_i)$，则最终的坐标为：
$((-1)^nx_0+\sum_{i=1}^n2\times(-1)^{i+1}x_i,(-1)^ny_0+\sum_{i=1}^n2\times(-1)^{i+1}y_i)$

发现根本没有办法做，所以回去看题，注意到 $n$ 保证为奇数，于是就简单了。

发现当 $n$ 为奇数时，将一次 $n$ 长度的对称的最终对称坐标带入到下一次 $n$ 长度的的对称中，得到：$((-1)^n((-1)^nx_0+\sum_{i=1}^n2\times(-1)^{i+1}x_i)+\sum_{i=1}^n2\times(-1)^{i+1}x_i,(-1)^n((-1)^ny_0+\sum_{i=1}^n2\times(-1)^{i+1}y_i)+\sum_{i=1}^n2\times(-1)^{i+1}y_i)$

根据 $n$ 为奇数，得到 $(-1)^{n}$ 是 $-1$，回带。

立刻有：$(x_0-\sum_{i=1}^n2\times(-1)^{i+1}x_i+\sum_{i=1}^n2\times(-1)^{i+1}x_i,y_0-\sum_{i=1}^n2\times(-1)^{i+1}y_i+\sum_{i=1}^n2\times(-1)^{i+1}y_i)$

化简，得到：$(x_0,y_0)$，就是翻了 $2n$ 次结果相当于没翻。

那么就直接将对称次数对 $2n$ 取模，然后数据范围就是 $10^5$ 数量级的，暴力做一下就行了。

---

注意开 long long。

---
### 代码：

```cpp
#include<cstdio>
#define int long long 
using namespace std;
int n,m,x[100005],y[100005],nowx,nowy,now;
signed main(){
	scanf("%I64d%I64d",&n,&m);
	m=(m%(2*n));
	scanf("%I64d%I64d",&nowx,&nowy);
	for(int i=1;i<=n;i++)scanf("%I64d%I64d",&x[i],&y[i]);
	for(int i=1;i<=m;i++){
		now++;
		if(now==n+1)now=1;
		nowx=2ll*x[now]-nowx;
		nowy=2ll*y[now]-nowy;
	}
	printf("%I64d %I64d",nowx,nowy);
	return 0;
}
```

---

## 作者：312_de_cat (赞：2)

```cpp
#include<iostream>
using namespace std;
long long m,n;
struct point{
    long long x,y;
}cat[100005];//坐标存法
point a,tmp;
int main(){
    cin>>n>>m;
    cin>>a.x>>a.y;
    for(int i=0;i<n;i++){
        cin>>cat[i].x>>cat[i].y;
    }
    m%=(2*n)//经找规律得：2n次又回到原点，模拟即可
    for(long long i=0;i<m;i++){//模拟
        tmp.x=cat[i%n].x*2-a.x;
        tmp.y=cat[i%n].y*2-a.y;
        a.x=tmp.x;
        a.y=tmp.y;
    }
    cout<<a.x<<" "<<a.y;
    return 0;
}
```


---

## 作者：Melo_DDD (赞：1)

[不会有更好的食用体验（。](https://www.cnblogs.com/Tomoyuki-Mizuyama/p/18326204)

感性理解法很好，但是我觉得还是用理性证明说服一下自己更靠谱。

前置芝士：两点间距离公式。

我们设 $A_{i\bmod n}$ 坐标为 $(\lambda_{i\bmod n},w_{i\bmod n})$，那么 $M_0$ 对称 $n$ 次之后（注意到 $n$ 是奇数）他的坐标为：
$$
M_n=(2\times\sum_{i=0}^{n-1}(-1)^{n-i+1}\times\lambda_i-a,2\times\sum_{i=0}^{n-1}(-1)^{n-i+1}\times w_i-b)
$$
再对称 $n$ 次之后：
$$
M_{2\times n}=((-1)^n\times x_{M_n}+2\times\sum_{i=n}^{2\times n-1}(-1)^{2\times n-i+1}\times\lambda_{i\bmod n},(-1)^n\times y_{M_n}+2\times\sum_{i=n}^{2\times n-1}(-1)^{2\times n-i+1}\times w_{i\bmod n})=(a,b)
$$
所以对称两次后等于没变，那直接对 $2\times n$ 取模后暴力算就可以了。

代码：
```
#include <bits/stdc++.h>
#define int long long 
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
int n ,t ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ; 
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = -x : 0 ;
}
const int N = 1e5 + 7 ;
int a ,b ,x[N] ,y[N] ;
signed main () {
	read (n) ,read (t) ;
	read (a) ,read (b) ;
	f (i ,0 ,n - 1 ,1) {
		read (x[i]) ,read (y[i]) ;
	}
	t %= n << 1 ;
	f (i ,0 ,t - 1 ,1) {
		a = (x[i % n] << 1) - a ; 
		b = (y[i % n] << 1) - b ;
	}
	cout << a << " " << b << '\n' ;
	return 0;
}
```

---

## 作者：_Dreamer_ (赞：1)


[传送门](https://www.luogu.com.cn/problem/CF24C)

朴素做法是 $O(x)$ 模拟

发现 $x$ 比较大 $n$ 比较小

尝试优化时间复杂度

我们知道, $a$ 关于 $b$ 的对称点 $c$ 关于 $b$ 对称 的点 是 $a$ 

一句话  对称两次该点不变

只需要判断 哪些点使用了奇数次  哪些点使用了 偶数次 即可

因为每次是从 $1$ 开始枚举的 所以输入的 $x$ 对 $2n$ 取模答案不变 模拟剩下的部分即可

时间复杂度  $O(n)$

code : 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long X;
int x[100005],y[100005];
int nx,ny;
int main()
{
	scanf("%d%lld",&n,&X);
	X%=2*n;
	scanf("%d%d",&nx,&ny);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x[i],&y[i]);
	}
	for(int i=1;i<=X;i++)
	{
		nx=x[(i-1)%n+1]*2-nx;
		ny=y[(i-1)%n+1]*2-ny;
	}
	printf("%d %d",nx,ny);
	return 0;
}

```

---

## 作者：myster1ous (赞：0)

## CF24C Sequence of points 题解

题意：给定 $n$ 个点 $A_1,\dots,A_n$，和一个初始状态点 $M_0$，求 $M_0$ 依次关于 $A_1,\dots,A_n,A_1,\dots$ 中心对称后 $x$ 次的点。

数据保证 $n \leqslant 10^5, n \bmod 2 = 1,x \leqslant 10^{18}$。

### 解法

我们手摸一下样例：

```plain
A1 = (+1, +1)
A2 = (+2, +3)
A3 = (-5, +3)
M0 = (+0, +0)
```

第一次对称：$M_1 = (2, 2)$。\
第二次对称：$M_2 = (2, 4)$。\
第三次对称：$M_3 = (-12, 2)$。\
第四次对称：$M_4 = (14, 0)$。\
第五次对称：$M_5 = (-10, 6)$。\
第六次对称：$M_6 = (0, 0)$。

我们发现，第六次对称就出循环节了 $M_6 = M_1$。

我们考虑将对称化为具体式子：

$(m_x,m_y)$ 关于 $(a_x, a_y)$ 对称，记对称后的节点为 $(m_x', m_y')$，则有：
- $m_x' = 2a_x - m_x$；
- $m_y' = 2a_y - m_y$。

带入 $(m_x, m_y) = M_0$：（因为此时 $x,y$ 对称所以简写了）

$$
\begin{aligned}
M_1 &= 2A_1 - M_0\\
M_2 &= 2A_2 - M_1\\
&= 2A_2 - 2A_1 + M_0 \\ 
M_3 &= 2A_3 - M_2\\
&= 2A_3 - 2A_2 + 2A_1 - M_0 \\
\vdots\\
M_k &= (-1)^{k}\times M_0+2\sum^{k}_{i=1}(-1)^{k-i} \times A_i\\
\vdots\\
M_n &= (-1)^n \times M_0 + 2\sum_{i=1}^k (-1)^{n-i} \times A_i\\
\end{aligned}
$$

我们再计算 $M_{n+1} \sim M_{2n}$ 试试？

$$
\begin{aligned}
M_{n+1} &= 2A_1 - M_n\\
M_{n+2} &= 2A_2 - M_{n+1}\\
&= 2A_2 - 2A_1 + M_n\\
\vdots\\
M_{2n} &= (-1)^n \times M_n + 2\sum_{i=1}^k (-1)^{n-i} \times A_i\\
\end{aligned}
$$

我们发现，$M_2n$ 和 $M_n$ 的式子很像啊！

$$
\begin{aligned}

M_{2n} &= (-1)^n \times M_n + 2\sum_{i=1}^k (-1)^{n-i} \times A_i\\

M_n &= (-1)^n \times M_0 + 2\sum_{i=1}^k (-1)^{n-i} \times A_i\\

\end{aligned}
$$

后两部分完全一样，而且，由于题面告诉我们 $n$ 必定是奇数，所以 $(-1)^n = -1$，我们将 $(-1)^n = -1$ 和 $M_n$ 带入 $M_{2n}$ 中：

$$
\begin{aligned}

M_{2n} &= (-1)^n \times M_n + 2\sum_{i=1}^k (-1)^{n-i} \times A_i\\
&= -M_n + 2\sum_{i=1}^k (-1)^{n-i} \times A_i\\
&= -\left((-1)^n \times M_0 + 2\sum_{i=1}^k (-1)^{n-i} \times A_i\right) + 2\sum_{i=1}^k (-1)^{n-i} \times A_i\\

&= M_0
\end{aligned}
$$

所以，我们便证明了一个解决问题的关键引理：

>
> $M_{2n} = M_0$
>

那这下就简单啦！虽然 $x$ 可以达到 $10^{18}$ 的量级，但是 $M$ 有循环节 $2n$，我们便可以将 $x \gets x \bmod 2n$。

然后暴力算 $M_1 \sim M_{2n}$ 即可。

时间复杂度：$\mathcal{O}(n)$，可以通过本题。

```cpp
#include <bits/stdc++.h>
#define int long long 

struct point {
    int x, y;
    point(int a=0, int b=0): x(a), y(b) {}

    bool operator<(const point& o) const& {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

int n, x;
std::vector<point> m;
std::vector<point> a;

signed main() {
    std::cin.tie(0);
    std::cin.sync_with_stdio(0);

    std::cin >> n >> x;

    x %= 2 * n;

    point start;
    std::cin >> start.x >> start.y;
    m.emplace_back(start.x, start.y);

    for (int i = 0; i < n; i++) {
        std::cin >> start.x >> start.y;
        a.emplace_back(start.x, start.y);
    }

    start = m.back();

    for (int j = 0; m.size() <= x; j++)
        for (int i = 0; i < n; i++) {
            int left = start.x - a[i].x;
            int right = start.y - a[i].y;
            m.emplace_back(start.x - left * 2, start.y - right * 2);
            start = m.back();
        }

    std::cout << m[x].x << " " << m[x].y << "\n";
    return 0;
}
```

---

## 作者：liuzhongrui (赞：0)

~~交发题解致敬老大！~~

## 题意分析

这道题要求我们通过点对称的定义，计算一个点序列中的某个特定点 $M_x$。也就是说，从一个给定的起始点 $M_0$ 开始，以 $N$ 个点 $N_0, N_1 \cdots N_{n-1}$ 为对称点，不断生成新的点 $M_1, M_2 \cdots$。

## 思路

我们要先搞清楚两个概念：

**1.对称点的定义**

根据题意，$M_j$ 的生成过程为：
- $M_1$ 是 $M_0$ 关于 $N_0$ 对称的点，数学上可以表示为：
  
  $$M_1 = M_0 + 2 \cdot (N_0 - M_0)$$
  
- $M_2$ 是 $M_1$ 关于 $N_1$ 对称的点，依次类推：
  
  $$M_2 = M_1 + 2 \cdot (N_1 - M_1)$$
  
据此我们可以得出一般的推导公式：
  
  $$M_{j} = M_{j-1} + 2 \cdot (N_{(j-1) \mod n} - M_{j-1})$$

通过观察我们发现，每一步都在随着轮换的对称点进行更新。

**2. 周期性**

在计算的过程中，可以观察到对称操作的周期性。

由于 $N$ 是奇数，随着循环 $N$ 次后，$M_j$ 的变化会出现规律，这就意味着在很多情况下，计算 $M_j$ 的值实际上是可以简化为先计算 $2n$ 次，因为 $M_j$ 最终是与这些对称点的和的某种组合。

如果直接计算很多次对称的更新，实际上我们只需要计算 $M_{j \mod 2n}$ 次，这是因为在每 $2n$ 次后，产生的点的关系开始重复。

---

我们要清楚一个事情，这道题的重点在于 $M_j$ 的计算。

因为我们有周期性这一性质，所以我们只需计算 $j \mod (2n) = k$ 次点的变化：

- 如果 $k < n$，我们就是对称于 $N_0$ 到 $N_{k-1}$ 再加上 $M_0$；

- 如果 $k \geq n$，我们实际上可以算出第二轮的对称。

计算过程中，我们要维护一个当前点的累积坐标，并在每一步中应用对称公式，实现坐标变化。

---




## 代码
如果没算错，可以用 $O(n)$ 的时间复杂度干掉这题。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct point {
	ll x,y;
	point(ll _x =0,ll _y = 0) {
		x = _x,y = _y;
	}
	point operator + (const point &p) {
		return {x+p.x,y+p.y};
	}
	point operator - (const point &p) {
		return {x-p.x,y-p.y};
	}
	point operator * (long long m) {
		return {x*m,y*m};
	}
	void scan() {
		scanf("%lld%lld", &x,&y);
	}
};
int main() {
	ll n,j;
	point m,ans,pt;
	scanf("%lld%lld", &n,&j);
	j--;
	j%=2*n;
	m.scan();
	auto coef = [&](ll i) {
		if(j<i || j>=i+n) return 0;
		if(j%2==i%2) return 1;
		return -1;
	};
	for(ll i=0; i<n; i++) {
		pt.scan();
		ans = ans + (pt - m)*coef(i);
	}
	ans = (ans*2)+m;
	printf("%lld %lld\n",ans.x,ans.y );
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
先解释一下什么叫关于对称。若 $A$ 和 $B$ 关于 $C$ 对称，设 $C$ 的坐标为 $C_x$ 和 $C_y$，其他点也为同一格式，那么 $2C_x=B_x+A_x$ 和 $2C_y=B_y+A_y$。

再来分析题目，观察到一个性质：$A$ 关于 $C$ 的对称点为 $B$，则 $B$ 关于 $C$ 的对称点为 $A$。所以我们发现其实对称两次之后又会回到原点，所以循环节就是 $2N$，故 $x$ 对 $2N$ 取模后答案不变。
### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std; 
int n,x,M_x[N<<1],M_y[N<<1],N_x[N],N_y[N];
signed main(){
	cin>>n>>x;
	cin>>M_x[0]>>M_y[0];
	for(int i=0;i<n;i++){
		cin>>N_x[i]>>N_y[i];
	}
	x=x%(2*n);
	for(int i=1;i<=x;i++){
		M_x[i]=2*N_x[(i-1)%n]-M_x[i-1];
		M_y[i]=2*N_y[(i-1)%n]-M_y[i-1];
	}
	cout<<M_x[x]<<" "<<M_y[x];
	return 0;
}
```

---

## 作者：PeterBei (赞：0)

题解区大部分人在一眼出结论，只有第一篇做出了证明，但实际上在赛场上当看到形似 $1 \leq x \leq 10^{18}$ 这种数据范围时应该第一时间考虑打表找规律，然后再反推结论。

``` cpp
int main(){
	long long n = read(), x = read();
	long long mx = read(), my = read();
	for(long long i = 0; i < n; i++){
		dat[i].x = read(), dat[i].y = read();
	} cout << "---------\n";
	for(long long i = 0; i < x; i++){
		mx = dat[i % n].x * 2 - mx;
		my = dat[i % n].y * 2 - my;
		cout << i + 1 << ": " << mx << ' ' << my << '\n';
	} cout << mx << ' ' << my << '\n';
	return 0;
}
```

输入较大的 $x$，会发现 $M_x$ 的坐标存在循环，其循环节长度为 $2n$。这时可以尝试推导结论，在发现了循环节的情况下该题结论（见其他题解）也不难推导；也可以直接按照发现的规律进行模拟。

这里我们选择模拟。由于循环节长度是 $2n$，那么在输入 $x$ 后加上语句 ``x = x % (2 * n);`` 即可。

``` cpp
int main(){
	long long n = read(), x = read(); x = x % (2 * n);
	long long mx = read(), my = read();
	for(long long i = 0; i < n; i++){
		dat[i].x = read(), dat[i].y = read();
	}
	for(long long i = 0; i < x; i++){
		mx = dat[i % n].x * 2 - mx;
		my = dat[i % n].y * 2 - my;
	} cout << mx << ' ' << my << '\n';
	return 0;
}
```

---

## 作者：Fhr123456 (赞：0)

## 思路
首先看数据范围 $x \le10^{18}$，暴力肯定不行，但是 $n$ 只有 $10^5$，考虑如何优化。手造几个数据推一下会发现经过 $2\times n$ 次对称后会回到原点。所以我们只需要将 $x$ 对 $2\times n$ 取模，剩下的暴力做即可。设点 $M_0(x_0,y_0)$ 和 $M_1(x_1,y_1)$ 对于点 $p(a,b)$ 对称，那么显然 $x_0+x_1=2 \times a $，且 $y_0+y_1=2 \times b$。用中点公式推一下就出来了。
## AC代码
```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
inline int read(){
	int f=1,sum=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		sum=sum*10+ch-'0';
		ch=getchar();
	}
	return f*sum;
}
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,q;
struct NODE{
	int x,y;
}m,a[100004];
signed main(){
	n=read();q=read();
	m.x=read();m.y=read();
	for(int i=1;i<=n;i++){a[i].x=read();a[i].y=read();}
	q=q%(n+n);
	for(int i=0;i<q;i++){
		int x=a[i%n+1].x+a[i%n+1].x,y=a[i%n+1].y+a[i%n+1].y;
		m.x=x-m.x;
		m.y=y-m.y;
	}
	printf("%lld %lld",m.x,m.y);
	return 0;
}
```


---

## 作者：ttwyzz (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF24C)

~~大概就是求对称点。~~

给出对称点公式。

$\,M_0\,$，$\,M_1\,$，关于 $\,N_0\,$对称，
那么$\,M_1\,$的坐标就是$\,N_0\,$的坐标乘$\,2\,$减去$\,M_0$的坐标。
 
注意一个细节，在循环$\,2\,$乘$\,n\,$次后就会回到起点，所以我们只要前$\,2n\,$次就够了，~~不然会超时~~。

还有记得要开 long long。

------------

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 20;

ll n,m;
struct N{
	ll x, y;
}a[maxn],ans;
int cnt;
// N*2 - M 
int main()
{
	scanf("%lld%lld",&n,&m);
	scanf("%lld%lld",&ans.x,&ans.y);
	for(int i = 0; i < n; ++i)
	{
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
	m %=(2*n);
	ll md;
	while(cnt++ != m)
	{
		md = (cnt - 1)%n;
		ans.x = a[md].x*2 - ans.x;
		ans.y = a[md].y*2 - ans.y;
	}
	printf("%lld %lld",ans.x,ans.y);
	return 0;
}
```



------------
 完结撒花！


---

