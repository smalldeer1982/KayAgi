# [USACO22FEB] Cow Camp G

## 题目描述

为了获得参加奶牛训练营的资格，Bessie 需要在 USACOW 公开赛的最后一题中取得好成绩。这道题有 $T$ 个独立的测试用例（$2 \leq T \leq 10^3$），权重相同，其中第一个测试用例是样例。她的最终得分将等于她最后一次提交通过的测试用例数量。

不幸的是，Bessie 太累了，无法思考这个问题，但由于每个测试用例的答案要么是“yes”，要么是“no”，她想到了一个计划！具体来说，她决定反复提交以下非确定性解决方案：

```
if input == sample_input:
    print sample_output
else:
    print "yes" or "no" each with probability 1/2, independently for each test case
```

注意，对于除样例之外的所有测试用例，这个程序在重新提交时可能会产生不同的输出，因此它通过的测试用例数量会有所不同。

Bessie 知道她总共不能提交超过 $K$ 次（$1 \leq K \leq 10^9$），否则她肯定会被取消资格。假设 Bessie 遵循最优策略，她的最终得分的最大可能期望值是多少？

## 说明/提示

- 测试用例 3-6 满足 $T \leq 25$ 且 $K \leq 100$。
- 测试用例 7-9 满足 $K \leq 10^6$。
- 测试用例 10-17 没有额外限制。

## 样例 #1

### 输入

```
2 3```

### 输出

```
1.875```

## 样例 #2

### 输入

```
4 2```

### 输出

```
2.8750000000000000000```

# 题解

## 作者：I_am_Accepted (赞：9)

### Preface

Naive 的我想了一个笨拙的算法，甚至时间可能都不是最优，但是谁能拒绝**矩阵乘法**呢。（坏笑）

同时纪念第一道赛场上做出来的 Gold。

### Analysis

发现单次提交所得分数为[二项分布](https://baike.baidu.com/item/%E4%BA%8C%E9%A1%B9%E5%88%86%E5%B8%83/1442377)，我们 $O(T^2)$ 类似杨辉三角预处理出**单次分数为 $i$ 的概率 $p_i$**。

**「好耶，是预处理！再加一个前缀和就更好了。」**

然后就是柿子了，$f_i$ 表示提交限制次数为 $i$ 时最优策略下的期望得分：

$$\begin{cases}
f_1=\frac{T+1}{2}
\\
f_n=f_{n-1}\sum\limits_{i=1}^{\left\lfloor f_{n-1}\right\rfloor}p_i\ +\sum\limits_{i=\left\lfloor f_{n-1}\right\rfloor+1}^{T}i\cdot p_i
\end{cases}$$

**「我好像不明白……」**

**解读：** 如果第 $i$ 次的得分**不比**后 $K-i$ 次的期望得分**小**，那就停下；否则继续提交。

发现这样可以 $O(K)$ 递推了，但是 $K=10^9$ 过不了。

**「我知道！用矩阵快速幂就行！」**

$$\begin{bmatrix}\sum\limits_{i=1}^{\left\lfloor f_{n-1}\right\rfloor}p_i & \sum\limits_{i=\left\lfloor f_{n-1}\right\rfloor+1}^{T}i\cdot p_i\\0&1\end{bmatrix}\begin{bmatrix}f_{n-1}\\ 1\end{bmatrix}=\begin{bmatrix}f_n\\ 1\end{bmatrix}$$

但是，只有当 $\left\lfloor f_{n-1}\right\rfloor$ 不变时，前面的方阵才能实行快速幂，而 $\left\lfloor f_{n-1}\right\rfloor$ 的取值只有 $T$ 种，所以**分段快速幂**搞定。

**「具体实现看代码吧！」**

总时间 $O(T^2+2^3T\log^2 K)$

**「其实不是很慢耶……话说你时间复杂度有没有搞错啊！」**

额……只能说，欢迎指正！

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define int long long
const int N=1010;
const int lim=1e6;
int t,k;
double p[N],q[N],a[N];
void init(){
	p[1]=1;
	For(i,1,t-1){
		For(j,1,i+1) q[j]=(p[j]+p[j-1])/2;
		For(j,1,i+1) p[j]=q[j]; 
	}
	Rof(i,t,1) a[i]=a[i+1]+p[i]*i;
	For(i,2,t) p[i]+=p[i-1]; 
}
struct node{
	double a[2][2];
	node mul(node x){
		node res;
		For(i,0,1) For(j,0,1) res.a[i][j]=0;
		For(i,0,1) For(j,0,1) For(k,0,1) res.a[i][j]+=a[i][k]*x.a[k][j];
		return res;
	}
	void init(){a[0][0]=1;a[0][1]=0;a[1][0]=0;a[1][1]=1;}
	node pw(int x){
		node tmp;
		For(i,0,1) For(j,0,1) tmp.a[i][j]=a[i][j];
		while(x--) tmp=tmp.mul(tmp);
		return tmp;
	}
}m;
bool check(node x,double y){return (int)(x.a[0][0]*y+x.a[0][1])==(int)(y);}
double modi(double x,int &cnt){
	m.a[0][0]=p[(int)x];m.a[0][1]=a[(int)x+1];
	m.a[1][0]=0;m.a[1][1]=1;
	int tmp=0;
	while((1<<tmp)<=cnt) tmp++;
	node res,out;
	out.init();
	Rof(i,tmp,0){
		if((1<<i)>cnt) continue;
		res=m.pw(i);
		if(check(out.mul(res),x)){
			out=out.mul(res);
			cnt-=(1<<i);
		}
	}
	return out.a[0][0]*x+out.a[0][1];
}
void brute(double &x){x=p[(int)x]*x+a[(int)x+1];}
signed main(){IOS;
	cin>>t>>k;
	init();
	double x=(double)(t+1)/2;
	For(i,2,min(k,lim)) brute(x);
	k-=min(k,lim);
	int lst=k;
	while(lst){
		x=modi(x,lst);
		if(!lst) break;
		lst--;
		brute(x);
	}
	cout<<fixed<<setprecision(10)<<x;
return 0;}
```

---

## 作者：WeLikeStudying (赞：7)

- 好题啊！以后就按照这样的策略水分！~~等等似乎如果奶牛不那么蠢的话早就水满分了。~~
- 就是最后发现数据点多的时候得分根本上不去十分的尬。
- 为啥要用矩阵乘法啊，普及组蒟蒻表示不解。
- 普及组蒟蒻只会用 $\text{C++}$ 特性，但复杂度好像是 $O(n)$ 的呢。
- 普及组蒟蒻不知道库函数复杂度很合理吧，作者猜测由于浮点数的特性，计算方法可能与数值大小关系不大。

**[题目](https://www.luogu.com.cn/problem/P8190)**
- 你有 $T$ 道判断题，你只会做第一道，所以你打算其它的你瞎蒙。
- 你最多可以交 $K$ 次，每次你都可以得到成绩，但是你的自主权只有：是否把这次作为最终成绩，或者放弃这次结果重新提交一份？你由于智商，每次都会交随机数。
- 如果你充分利用你的自主权，使用最优策略，你期望可以拿到多少分？
- $2\le T\le 10^3,1\le K\le 10^9$。

**分析**
- 首先，你发现对于一个固定的局面：还有 $K$ 个测试点，你得到了分数 $S$，你交还是不交是固定的，那么显然有一个 $f(K)$，大于等于它你就不需要再交，否则你还是再交一次，利用组合数，我们可以 $O(n^2)$ 得到它的概率分布，枚举最优转移点，我们就得到了 $O(nk)$ 的暴力，[代码](https://www.luogu.com.cn/paste/0x4kp9ak)。
- 然后你发现你实际上是在求一个凸壳的最值，由于转移点单调，我们可以用类似旋转卡壳的方法做到 $O(k)$，[代码](https://www.luogu.com.cn/paste/gu4kd3m8)，或者你发现 $K-1$ 的期望就是 $f(K)$ 也可以，[代码](https://www.luogu.com.cn/paste/bw1nvt32)。
- 然后你发现转移点相同的迭代过程的嵌套，展开出来是这样的：比如把 $ax+b\to x$ 赋值 $n$ 次，展开是一个等比数列求和，为 $a^nx+\frac{a^n-1}{a-1}\cdot b$ 这可以用库函数直接算（需要特判 $a=1,b=0$）。
- 显然答案满足单调性，所以我们二分就得到了 $O(n^2+n\log k)$ 的方法，[代码](https://www.luogu.com.cn/paste/xeevl87k)。
- $O(n^2)$ 显然可以优化，为了考虑精度，这里对阶乘取 $\ln$，可以防止掉精度，复杂度 $O(n\log k)$，[代码](https://www.luogu.com.cn/paste/8ol000sz)，其实这份代码精度最高。
- 或许我们有更好的，不用二分的方法，那就是对函数进行分析，我们之前的做法本质上就是找到每个 $f(K)$ 的取值在 $K$ 上形成的区间，那么反正我们有强大的库函数，直接找不就行了？
- 如果函数嵌套之后没有增加，就直接跳，否则直接求出它的作用区间就好了，复杂度 $O(n)$，[代码](https://www.luogu.com.cn/paste/vhh54stu)。

---

## 作者：kradcigam (赞：7)

看到大家的做法都很暴力，码量很大，于是来写一发 40 行的小清新做法。

首先，为了方便，我们把样例去掉来考虑，即 `k--`，最后结果再加上 1 即可。

考虑朴素的 dp，设 $f_i$ 表示交 $i$ 次后的期望得分，转移是：

$$
f_i=\sum_{j=1}^{t} \frac{\dbinom{t}{j}}{2^t}\max\{f_{i-1}, j\}
$$
也就是：
$$
f_i=\sum_{j=1}^{t} \frac{\dbinom{t}{j}}{2^t}\times \begin{cases}j&j> f_{i-1}\\f_{i-1}&j\le f_{i-1}\end{cases}
$$
我们可以预处理出 $n$ 个点中过至少 $i$ 个点的概率 $p_i$，和过至少 $i$ 个点的期望得分 $s_i$，于是就变成
$$
f_i=(1-p_{\left\lfloor f_{i-1} \right\rfloor + 1}) \times f_{i-1} + s_{\left\lfloor f_{i-1} \right\rfloor + 1}
$$
我们发现虽然 $k$ 很大，但是 $0 < f_i < k$，也就是说 $0 \le \left\lfloor f_i \right\rfloor < k$，所以其实 $\left\lfloor f_i \right \rfloor$ 的变化次数是 $O(k)$ 级别的。

因为 $f_i$ 单调上升，所以我们对于 $\left\lfloor f_i \right \rfloor$ 相同时可以二分。

$\left\lfloor f_i \right \rfloor$ 相同时的转移可以 $O(\log k)$ 算。假设考虑 $f_i$ 转移到 $f_j$，设 $k = \left\lfloor f_i \right \rfloor$。$f_i$ 对于 $f_j$ 的贡献是 $(1-p_{k+1})^{j-i}$，而 $s_{k + 1}$ 的贡献是 $\sum\limits_{i=0}^{j - i - 1} (1-p_{k+1}) ^ j$，两个东西很好求。

40 行的代码：

```cpp
#include <bits/stdc++.h>
#define F(i, x, y) for (int i = (x); i <= (y); i++)
#define DF(i, x, y) for (int i = (x); i >= (y); i--)
using namespace std;
const int N = 1010;
int t, k;
double C[N][N], p[N], z[N], s[N];
inline double Quickpow(double x, int y) {
	double ans = 1;
	for (; y; x = x * x,y >>= 1)
		if (y & 1) ans = ans * x;
	return ans;
}
signed main() {
	cin >> t >> k; t--;
	double x = 1;
	F(i, 1, t) x /= 2;
	F(i, 1, t) {
		C[i][0] = C[i][i] = 1;
		F(j, 1, i - 1)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	F(i, 0, t) p[i] = C[t][i] * x;
	DF(i, t, 0) z[i] = z[i + 1] + p[i], s[i] = s[i + 1] + p[i] * i;
	double s = 0;
	int i = 0;
	while (i != k) {
		int l = i, r = k;
		int t = s;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			double tt = s * Quickpow(1 - z[t + 1], mid - i) + ::s[t + 1] * ((1 - Quickpow(1 - z[t + 1], mid - i)) / z[t + 1]);
			if (tt < t + 1) l = mid;
			else r = mid;
		}
		s = s * Quickpow(1 - z[t + 1], r - i) + ::s[t + 1] * ((1 - Quickpow(1 - z[t + 1], r - i)) / z[t + 1]);
		i = r;
	} cout << fixed << setprecision(20) << s + 1;
	return 0;
}
```

---

## 作者：蒻蒟IOOI蒟蒻 (赞：4)

## Preface

成功卡进洛谷最优解 rank1，复杂度只有 $O(2^3T\log K)$，总用时 [$51ms$](https://www.luogu.com.cn/record/72189871)，跑得飞快。

## Analysis 

经过简单的推导，我们发现它的概率符合二项分布，于是可以推出以下状态转移方程，$dp_i$ 表示提交次数最多为 $i$ 次时的最高期望得分：

$$\large{dp_i = dp_{i-1} \sum \limits ^{\lfloor dp_{i-1} \rfloor}_{j=1} \frac{C^{j-1}_{T-1}}{2^{T-1}}  +  \sum \limits ^{T}_{j=\lceil dp_{i-1} \rceil} \frac{C^{j-1}_{T-1}}{2^{T-1}}\times j}$$

再做一下预处理，可以把时间复杂度降低到 $O(K)$，我们定义

$$f_i = f_{i-1} + \frac{C^{i-1}_{T-1}}{2^{T-1}}$$
$$g_i = g_{i+1} + \frac{C^i_{T-1}}{2^{T-1}} \times (i+1)$$

然后我们注意到数据范围 $K \le 10^9$，直接递推过不了，所以我们考虑矩阵快速幂。
		
$$\large{\begin{bmatrix} dp_{i-1}&1 \end{bmatrix} \begin{bmatrix} f_{\lfloor dp_{i-1} \rfloor}&0\\g_{\lfloor dp_{i-1} \rfloor}&1 \end{bmatrix} = \begin{bmatrix} dp_i&1 \end{bmatrix}}$$

但是，只有当转移矩阵中的 $\lfloor dp_{i-1} \rfloor$ 不变时，我们才能使用矩阵快速幂来优化，而 $\lfloor dp_{i-1} \rfloor$ 取值只可能有 $T$ 种，所以用分段快速幂就搞定了。

我用倍增的方法来分段，这样可以做到 $O(\log K)$ 的时间复杂度。

所以总的时间复杂度是 $O(2^3T\log K)$ 的。

于是就愉快地通过了本题。

## Code


```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;
const int N = 1e3 + 5;
int n, m, cnt, i;
long double fac[N], sum[N], sum2[N], tmp;
struct node {
    long double a[3][3];
    int n, m;
    node() {
        memset(a, 0, sizeof(a));
    }
    node(int _n, int _m) : n(_n), m(_m) {
        memset(a, 0, sizeof(a));
    }
    long double* operator [](int x) &{
        return a[x];
    }
    node operator *(node &x) const &{
        node res(n, x.m);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= x.m; j++) {
                for (int k = 1; k <= m; k++) {
                    res[i][j] += a[i][k] * x[k][j];
                }
            }
        }
        return res;
    }
} a, o, b[40], r;
void func(int &m) {
    b[0][1][1] = sum[cnt], b[0][2][1] = sum2[cnt];
    for (i = 1; 1 << i <= m; i++) {
        b[i] = b[i - 1] * b[i - 1];
    }
    r = a;
    int u = m;
    for (i--; i >= 0; i--) {
        node t = r * b[i];
        if ((int)t[1][1] == cnt) r = t, m -= 1 << i;    
    }
    m--;
    if (m < 0) {
        int ct = 0;
        while (u) {
            if (u % 2) a = a * b[ct];
            u /= 2, ct++;
        }
        m = 0;
    } else a = r, a = a * b[0], cnt = a[1][1];
}
signed main() {
    cin >> n >> m;
    for (int i = 0; i < 40; i++) b[i] = node(2, 2);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
    tmp = pow(2, n - 1);
    for (int i = 1; i <= n; i++) {
        long double t = fac[n - 1] / fac[n - i] / fac[i - 1] / tmp;
        sum[i] = sum[i - 1] + t;
        sum2[i] = sum2[i - 1] + t * i;
    }
    for (int i = 0; i <= n; i++) sum2[i] = sum2[n] - sum2[i];
    a.m = o.n = o.m = 2, a.n = 1;
    o[1][1] = o[2][2] = a[1][2] = b[0][2][2] = 1;
    while (m) func(m);
    cout << fixed << setprecision(10) << a[1][1] << endl;
    return 0;
}
```


---

## 作者：jia_shengyuan (赞：3)

## 放在前面的废话

你谷机子太快了，$O(K+T^2)$ 暴力什么优化不加一秒过（

这份题解的做法是暴力分块打表，想要复杂度更优的做法可以移步其他题解。

## 正题

首先，样例的那个点明显啥用没有，所以后文中提到的 $T$ 实际均为 $T-1$。

我们记剩 $i$ 次机会时的期望得分为 $f_i$，则交完一次之后要不要继续的策略很明显：如果当前得分大于继续交的期望，就停止；否则，就继续交。这样我们可以~~很方便地~~写出转移方程：
$$f_i = \sum\limits_{j=\lceil f_{i-1}\rceil}^{T}\frac{j\times\dbinom{T}{j}}{2^T}+f_{i-1}\times \sum\limits_{j=0}^{\lfloor f_{i-1}\rfloor}\frac{\dbinom{T}{j}}{2^T}$$

不要被一堆组合数和求和符吓着了，这个公式的意思很简单：左半部分，就是本次得分**高于继续交的期望**的情况下**期望的得分**；右半部分，就是本次得分不如继续交的概率乘上继续交的期望得分。

于是一种 $O(K+T^2)$ 的暴力做法就很显然了：预处理出组合数，之后从 $1$ 到 $K$ 按照公式推一遍 $f$ 数组。由于 $f$ 单调递增，所以求和符里面的东西也可以边做边推，而不用每次去算。

代码中 `rate` 就是本次得分高于继续交的期望的概率，`sum` 就是本次得分高于继续交的期望的情况下的期望得分。由于组合数最终要除个 $2^T$，所以干脆预处理时就除了。

```cpp
#include <cstdio>

const int maxn = 1009;

double C[maxn][maxn],dp,sum,rate;
int n,m,mid;

void Init(){
    C[1][1] = C[1][0] = 0.5;
    for(int i=2; i<=n; i++){
        C[i][0] = C[i-1][0]/2;
        for(int j=1; j<=i; j++){
            C[i][j] = (C[i-1][j]+C[i-1][j-1])/2;
        }
    }
    dp = n*0.5;
    mid = (n+1)>>1;
    rate=sum=0;
    for(int i=mid; i<=n; i++){
        rate += C[n][i];
        sum += C[n][i]*i;
    }
}

int main(){
    scanf("%d%d",&n,&m); n--;
    Init();
    for(int i=2; i<=m; i++){
        dp = sum+(1.0-rate)*dp;
        while(dp >= mid) {
            rate -= C[n][mid];
            sum -= C[n][mid]*mid;
            mid++;
        }
    }
    printf("%.9lf",dp+1);
    return 0;
}
```

这份代码可以在洛谷上通过这道题，但我们不妨继续看看怎么优化。观察到 $f_i$ 只与 $f_{i-1}$ 有关，所以我们可以分块打表。对于每个 $T$，我们隔 $B$ 个数存一个 $f$，这样复杂度就变成了 $O(B+T^2)$。

由于洛谷的代码长度限制，我取了 $B=3.3\times 10^8$，相当于把问题规模缩小了三倍。这样处理后，这份代码能够在 $\frac13$ 秒以内通过所有测试点。代码就不放了，和上面大同小异。

---

## 作者：junxis (赞：1)

# Perface
很酷的题！我直接来一个很酷的做法！
# Analysis
在下文中，我们不考虑样例，最后直接将结果加一，并在运算时将 $T$ 减一即可。

我们不妨设：一次恰过掉 $j$ 个测试点的概率为 $\text{pr}(j)$，易得 $\text{pr}(j)=\dfrac{\binom{T}{j}}{2^T}$。

记 $f(i)$ 为答到第 $i$ 次时的最大期望分数，易得：

$$f(i)=\sum\limits_{j=0}^{T}\text{pr}(j)\max\{f(i-1),j\}$$
$$=\sum\limits_{j=0}^{\left\lceil f(i-1)\right\rceil-1}\text{pr}(j)j+f(i-1)\times\sum\limits_{j=\left\lceil f(i-1) \right\rceil}^{T}j$$

预处理一个 $\text{pr}$，一个 $\text{pr}(j)j$ 的前缀和，一个 $\text{pr}$ 的前缀和即可做到 $\mathcal{O}(T+K)$。

但这还不够，$K$ 达到了惊人的 $10^9$ 级别。

我们观察到：

1.	这是一个线性递推。

2.	她是以 $\left\lceil f(i-1) \right\rceil$ 为分界的两个 $\sum$。

3.	$\left\lceil f(i-1) \right\rceil$ 的变化次数规模是 $\Omega(T)$ 的。

所以，会有很长的一段，她们的分界点是一样的，那么就变成了连续 $x\gets kx+b$ 的经典问题，可以二分出分界点解决。

但这样子写起来太恶心了，而且不够酷。

我们有更酷的做法!

分块思想，我们考虑一个钦定一个步长 $\omega$。

递推过程中，若当前的元素以当前分界点变化 $\omega$ 次后分界点依然不变，那么就直接跳过这中间的递推，直接变到 $\omega$ 步以后。

我们要预处理 $T$ 组系数，其中 $\text{coef}(i)=(k,b)$ 表示以 $i$ 为分界点的一项元素，变化 $\omega$ 次后会乘上 $k$，加上 $b$。

这样我们便能得知假定分界点未变化，当前元素变化 $\omega$ 次后的值，从而判断出当前递推元素后 $\omega$ 项的分界点是否变化，然后快速地进行转移。

时间复杂度为 $\mathcal{O}(\omega T+\dfrac{K}{\omega})$。

事实上，$\omega$ 取到 $1000$ 时程序运行效率最优。

最后，记得开 ```long double```。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int, int> PII;
typedef long double db;
mt19937 mrand(random_device{}());
const ll mod=1000000007;
int rnd(int x) {return mrand() % x;}
ll powmod(ll b, ll e, ll md=mod) {ll a=1; b %= md; assert(e>=0); for (;e;e>>=1, b=b*b%md) if(e&1) {a=a*b%md;} return a;}
ll gcd(ll a, ll b) {return b?gcd(b,a%b):a;}
// head

const int N = 1010, st = 1000;
int T, k;
db ps[N], qs[N], pr[N];
pair<db, db> coef[N];

int main() {
	scanf("%d%d",&T, &k); --T;
	ps[0] = pr[0] = pow(0.5, T);
	rep(i,1,T+1) {
		pr[i] = pr[i - 1] * (T - i + 1) / i;
		ps[i] = ps[i - 1] + pr[i];
	}
	per(i,0,T+1) qs[i] = qs[i + 1] + pr[i] * i;
	rep(j,0,T+1) {
		db k = 1, b = 0;
		rep(_,0,st) k *= ps[j - 1], b = b * ps[j - 1] + qs[j];
		coef[j] = {k, b};
	} // 暴力处理系数
	/*rep(i,1,k+1) {
		int tt=ceil(f[i-1]);
		f[i]=f[i-1]*ps[tt-1]+qs[tt];
	}*/
	db f = 0;
	rep(i,1,k+1) {
		int j = ceil(f); // 当前分界点
		if (i + st <= k) {
			db nf = f * coef[j].fi + coef[j].se;
			if (nf<=(db)j) {
				f = nf; i += st - 1; // 分界点不变，走 omega 步
			} else f = f * ps[j - 1] + qs[j]; // 分界点变化，一步步走
		} else f = f * ps[j - 1] + qs[j];
	}
	printf("%.10lf\n",(double)f + 1);
}
```

---

## 作者：liruixiong0101 (赞：0)

# P8190 [USACO22FEB] Cow Camp G
题目链接：<https://www.luogu.com.cn/problem/P8190>

## 题意：
Bessie 有一道题共有 $T$ 个测试点，第一个测试点是样例，它一定通过该测试点，其中对于后 $T-1$ 个测试点中的每一个测试点，Bessie 都有 $\frac{1}{2}$ 的概率通过或不通过，一次提交的得分为其通过测试点的数量。Bessie 可以提交至多 $K$ 次程序，定义 Bessie 这道题的得分为它最后一次提交的分数，请问 Bessie 的得分的最大期望是多少。

## 思路：
首先考虑 $p_i$（$1\le i\le T$）为对于任意一次提交得分为 $i$ 的概率，那么显然有 ${p_i=\dfrac{{T-1}\choose{j-1}}{2^{T-1}}}$，$p_i$ 可以在 $O(T)$ 内预处理求出。

设 $f_i$ 表示 Bessie 提交了 $i$ 次的得分的最大期望，那么有转移式：
$$
f_i=\sum_{j=1}^T(\max(f_{i-1},j)\cdot p_j)
$$
简单讲一下这个式子的含义，枚举第 $i$ 次的得分 $j$，如果前 $i-1$ 次的得分的最大期望比得分 $j$ 更大，那么肯定不提交，否则就提交获得 $j$ 的得分，再乘以得分为 $j$ 的概率即可。

这样我们就会 $O(T+K)$ 的做法了。

--- 

考虑优化。可以想到矩阵快速幂优化，但是 $\max(f_{i-1},j)$ 不固定，所以不能直接矩阵快速幂。由于 $\max(f_{i-1},j)$ 的取值很特殊，所以可以将 $j$ 分为 $j\le\lfloor f_{i-1}\rfloor$ 和 $j\gt\lfloor f_{i-1}\rfloor$ 两段，接着我们可以将式子化成如下形式：
$$
f_i=\sum_{j=1}^{\lfloor f_{i-1}\rfloor}(f_{i-1}\cdot p_j)+\sum_{j=\lfloor f_{i-1}\rfloor+1}^T(j\cdot p_j)=f_{i-1}\sum_{j=1}^{\lfloor f_{i-1}\rfloor} p_j+\sum_{j=\lfloor f_{i-1}\rfloor+1}^T(j\cdot p_j)
$$

为了方便处理，我们设 $g_i=\sum_{j=1}^i p_j,h_i=\sum_{j=i+1}^T(j\cdot p_j)$（$g_i,h_i$ 也可以 $O(T)$ 预处理求出），那么：
$$
f_i=g_{\lfloor f_{i-1}\rfloor}\cdot f_{i-1}+h_{\lfloor f_{i-1}\rfloor}
$$

这就更像矩阵乘法了，矩阵乘法的式子如下：

$$
\begin{bmatrix}
f_i & 1
\end{bmatrix}

=
\begin{bmatrix}
f_{i-1} & 1
\end{bmatrix}
\times
\begin{bmatrix}
g_{\lfloor f_{i-1}\rfloor} & 0 \\
h_{\lfloor f_{i-1}\rfloor} & 1
\end{bmatrix}
$$

能够发现 $f_{i-1}\in[0,T)$，那么 $\lfloor f_{i-1}\rfloor$ 也只能有 $T$ 个值，又由：
$$
f_i=\sum_{j=1}^T(\max(f_{i-1},j)\cdot p_j)\gt\sum_{j=1}^T(f_{i-1}\cdot p_j)=f_{i-1}\cdot\sum_{j=1}^T p_j=f_{i-1}
$$
可知 $f_i$ 单调递增，那么 $\lfloor f_{i}\rfloor$ 单调不降，那么我们可以对于每一个 $\lfloor f_i\rfloor$ 的值去做矩阵快速幂，也就是分段做矩阵快速幂。

那么如何寻找段与段之间的分界点呢，我们可以倍增。假设我们现在已经到了 $j=\lfloor f_{i-1}\rfloor$ 这个值，不妨设此时的转移矩阵为 $B$，我们可以先预处理出 $B,B^2,B^4,\cdots B^{2^n}$（$2^n\le K$），我们可以从 $B^{2^n}$ 一直到 $B$ 一直尝试，设当前矩阵为 $F$，如果 $F\times B^{2^i}$ 得到的期望值向下取整的结果为 $j$，且还能过操作该次（即总操作次数小于等于 $K$），那么就将 $F\gets F\times B^{2^i}$ 即可。

## 代码：
<https://www.luogu.com.cn/record/173675684>

---

## 作者：StillEmpty (赞：0)

首先考虑 $O(K)$ 做法。

称允许提交 $i$ 次时得分期望是 $E_i$，那允许提交 $i+1$ 次的得分期望是几？其实就是说，我们先提交一次，根据这次提交的情况，决定是否使用。如果使用，得分这次的得分；如果不使用，得分的期望是 $E_i$。

也就是说，当第一次得分大于 $E_i$ 时，我们直接结束操作；否则继续提交 $i$ 次。

为了简化模型，我们称 $t=T-1$，也就是计算时不考虑样例。输出时将答案 $+1$。

根据：
$$E_{i+1}= \text{一次提交小于} E_i \text{的概率}\times E_i+\sum_{i=\lceil{E_i}\rceil}^t i \text{的概率} \times i
$$
得出：
$$
E_{i+1}=E_i\sum_{i=0}^{\lfloor{E_i}\rfloor}\frac{t \choose i}{2^t}+\sum_{i=\lceil{E_i}\rceil}^t i\frac{t \choose i}{2^t}
$$

由于 $\lfloor{E_i}\rfloor$ 是整数，两个 $\sum$ 式均可以被预处理。

我们就得到了 $O(K)$ 迭代代码：

```cpp
typedef long double ld;
const ld EPS = 1e-12;
ld x = t/2.;
for(int i = 2; i <= k; ++i) {
    int fl = floor(x+EPS), cl = ceil(x-EPS);
    x = ltrate[fl]*x+gtexpect[cl];
}
```

**我们会发现，$E_i \in (0,t)$，且 $E_i$ 单调递增，所以绝大数 `fl` 和 `cl` 都不变。如果 `fl` 和 `cl` 不变，那迭代式就可以倍增求解。**

举一个数据例子：
```
100 10000
68.755596
```
```
100 20000
69.5844688
```
确实很收敛啊这个增长率。

每次我们即是要求最多再迭代多少次，`fl` 和 `cl`不变。

根据乘法分配律，反复迭代先乘再加两个操作，可以展开成只乘一次只加一次。

预处理迭代 $1, 2, 4, 8, \cdots$ 次的展开结果，然后从大往小依次确定最多迭代次数的每个二进制位。

注意如果 `fl = cl` 要特判，别问我怎么知道的。

时间复杂度：$(T^2+T \log K)$：
```cpp
#include <bits/stdc++.h>
typedef long double ld;
using namespace std;

const ld EPS = 0.;
ld t; int k;
ld ltrate[114514], gtexpect[114514];

int main() {
    scanf("%llf%d", &t, &k); t -= 1.;
    ld tot = 1.;
    for(int i = 1; i <= t; ++i) tot *= 2.;
    for(int i = 0; i <= t; ++i) {
        ld cnt = 1.;
        for(int j = t; j >= t-i+1; --j) cnt *= (ld)j;
        for(int j = 1; j <= i; ++j) cnt /= (ld)j;
        ltrate[i] = cnt/tot; gtexpect[i] = ltrate[i]*i;
        ltrate[i] += ltrate[i-1];
    }
    for(int i = t-1; i >= 0; --i) gtexpect[i] += gtexpect[i+1];
    ld x = t/2.; --k;
    while(k > 0) {
        int fl = floor(x+EPS), cl = ceil(x-EPS), l = floor(log2(k)+EPS);
        if(fl == cl) {
            x = ltrate[fl-1]*x+gtexpect[cl]; --k;
            continue;
        }
        vector<ld> mul, add;
        mul.push_back(ltrate[fl]); add.push_back(gtexpect[cl]);
        for(int i = 1; i <= l; ++i) {
            mul.push_back(mul[i-1]*mul[i-1]);
            add.push_back(add[i-1]*mul[i-1]+add[i-1]);
        }
        for(int i = l; i >= 0; --i) {
            if((1<<i) > k || floor(x*mul[i]+add[i]+EPS) != fl) continue;
            k -= (1<<i); x = x*mul[i]+add[i];
        }
        while(k > 0 && floor(x+EPS) == fl) {
            x = x*ltrate[fl]+gtexpect[cl]; --k; // 防卡精度
        }
    }
    cout << fixed << setprecision(15) << x+1. << endl;
    return 0;
}
```

---

