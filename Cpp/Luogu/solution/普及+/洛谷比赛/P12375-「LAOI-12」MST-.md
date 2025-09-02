# 「LAOI-12」MST?

## 题目背景

![](bilibili:BV1xw6mYEEaN)

## 题目描述

给定 $n,m$ 两个正整数，构造无重边**无自环**的一张连通无向图，共 $n$ 个结点和 $m$ 条边权分别为 $1\sim m$ 的边，使得其最小生成树的边权和最大。

你只需要输出最小生成树的边权和对 $998244353$ 取模的值即可。

## 说明/提示

### 样例解释

对于样例一中的第一组测试数据，构造如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/ngx4j1fr.png)

此时答案为 $1+2+4=7$。

### 数据范围

**本题采用捆绑测试。**

|子任务编号|$T$|$n$|特殊性质|分值|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$\le5$|$\le5$|无|$5$|
|$2$|$\le10^6$|$\le10^3$|无|$10$|
|$3$|$\le5$|$\le10^6$|无|$15$|
|$4$|$\le10^6$|$\le10^6$|无|$20$|
|$5$|$\le10^6$|$\le10^{18}$|$n=m$|$5$|
|$6$|$\le10^6$|$\le10^{18}$|无|$45$|

对于 $100\%$ 的测试数据，满足 $1\le T \le 10^6$，$4\le n\le m\le 10^{18}$，$m\le \frac{n\times(n-1)}{2}$。

## 样例 #1

### 输入

```
3
4 6
4 5
5 8```

### 输出

```
7
7
14```

# 题解

## 作者：MPLN (赞：2)

推导题，难点在找到规律后推出公式，代码可以极为简洁地实现，也不需要二分之类。

（闲话：本文最后是挑战最短解的代码，欢迎大佬评论来爆）

## 思路

我们先观察 Kruskal 是怎么选边的：边权从小到大，如果两个端点没有连起来就选这条边。

所以我们也从小到大加边，过程中对于每条边贪心地：若存在点 $i,j$ **连通但是没有直接相连的边**，就把它们连起来，然后这条边不会在 MST 里，成功浪费掉目前这个边权较小的边；否则就只能采用这条边将另外一个不连通的点连过来。

持续直到剩下的所有边都必须采用到 MST，否则就连不出连通图，就全部加到答案里。

## 选边规律

所以假设边足够时，先设 $k=1$，发现这个过程是：

1. 把当前 $k$ 个点连成完全图，浪费掉这些边权太小的边；
2. 现在无论怎么连都会在 MST 里面用到，就只能用这条边连一个没有进入并查集的点，然后 $k\gets k+1$；
3. 继续步骤 1。

假设边足够时，哪些边会被选呢？

1. 连 1 和 2，被选。$k=2$（此时 2 个点成完全图）。
2. 连 2 和 3，被选。$k=3$。
3. 连 1 和 3，不被选。$k=3$（此时 3 个点成完全图）。
4. 连 3 和 4，被选。$k=4$。
5. 连 1 和 4，不被选。$k=4$。
6. 连 2 和 4，不被选。$k=4$（此时 4 个点成完全图）。
7. 连 4 和 5，被选。$k=5$。
8. 连 1 和 5，不被选。$k=5$。
9. 连 2 和 5，不被选。$k=5$。
10. 连 3 和 5，不被选。$k=5$（此时 5 个点成完全图）。
11. 连 5 和 6，被选。$k=6$。
12. 连 1 和 6，不被选。$k=6$。
13. 连 2 和 6，不被选。$k=6$。
14. 连 3 和 6，不被选。$k=6$。
15. 连 4 和 6，不被选。$k=6$（此时 6 个点成完全图）。
16. 连 6 和 7，被选。$k=7$。
17. 连 1 和 7，不被选。$k=7$。
18. $\dots$

假设边足够时，被选的边固定在数列 $a$：$1,2,4,7,11,16,22\dots$ 不难发现是二阶等差数列，通项公式次数为 2。可以用解三元一次方程组等方式发现：

$$
a_i=\frac{1}{2}i^2-\frac{1}{2}i+1
$$

$a$ 的前 $n$ 项和可以用平方数列和，等差数列求和等公式来得到，具体是啥可以参考[我的文章](https://www.luogu.com.cn/article/07cwcsl2)数列求和部分：

$$
\begin{aligned}
\sum_{i=1}^na_i&=\frac{(2n+1)(n+1)n}{12}-\frac{(n+1)n}{4}+n\\
&=\frac{(n-1)(n+1)n}{6}+n\\
&=\frac{(n^2+5)n}{6}
\end{aligned}
$$

## 计算答案

那么什么时候是边不足够呢？假设我们已经选了第 $a_x$ 条边，如果再用中间的边拼完全图然后选第 $a_{x+1}$ 条的话，剩余的边不足以连通所有 $n$ 个点，就不足够了。具体来说，此时边权最大的 $n-1-x$ 条边都可以用在最小生成树里。

接下来就是需要确定这个 $x$ 了，有不等式：

$$
m-a_x(剩余边)\ge n-1-x(需要边)
$$

化简得：

$$
\frac{1}{2}x^2-\frac{3}{2}x-m+n\le 0
$$

求根公式取正根向下取整即为 $x$。

此时首先计算答案中 $a_1$ 到 $a_x$ 得边权和，用之前的公式：

$$
sum_1=\frac{(x^2+5)x}{6}
$$

然后最大的 $n-1-x$ 条边边权和可以用等差数列求和公式得到：

$$
sum_2=\frac{(2m-n+x+2)(n-1-x)}{2}
$$

最终答案就是：

$$
ans=sum_1+sum_2
$$

## 实现

1. 解一元二次方程，确定 $x$。
2. 用 $x$ 计算答案。

So easy!

唯一注意的就是假如用 long long，计算分数时，必须先除以 $2$ 或者 $6$ 再取模。这怎么办，乘之前不取模不会溢出吗？那就先单独判断分子中的哪个因式可以除以分母（或者分母的因数，对于 $6$ 就先判断除以 $2$ 再除以 $3$）。或者用 ```__int128```。这里两种方法都提供。

时间复杂度 $O(T\operatorname{log}n)$，瓶颈在于开根号。

int128 版：

```cpp
#include<bits/stdc++.h>
#define l __int128
l M = 998244353, T, n, m;
signed main() {
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld%lld", &n, &m);
        l x = 1.5 + sqrt(2.25 - 2 * (n - m));
        printf("%lld\n", ((x * x + 5) * x / 6 + (2 * m - n + x + 2) * (n - 1 - x) / 2) % M);
    }
    return 0;
}
```
**目前最短解** int128 压行版（长度 205B）：
```cpp
#import<bits/stdc++.h>
#define l __int128
l M=998244353,T,n,m;main(){scanf("%lld",&T);while(T--){scanf("%lld%lld",&n,&m);l x=1.5+sqrt(2.25-2*(n-m));printf("%lld\n",((x*x+5)*x/6+(2*m-n+x+2)*(n-1-x)/2)%M);}}
```

[提交记录](https://www.luogu.com.cn/record/215414723)

另一 long long 实现（其实有很多可以省略的代码）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;
int t, n, m;
int cal() {
    double a = 0.5, b = -1.5, c = -m + n;
    double res = (-b + sqrt(b * b - 4 * a * c)) / 2 / a;
    return (int) res;
}
void frac(int &a, int &b, int c) { // 取模前先除以
    if (a % c == 0) a /= c;
    else b /= c;
}
signed main() {
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &n, &m);
        int x = cal(), t1, t2, ans = 0;
        t1 = x * x + 5, t2 = x; // 第一部分答案（a_1 到 a_x）
        frac(t1, t2, 2), frac(t1, t2, 3);
        ans = (ans + (t1 % MOD * (t2 % MOD) % MOD)) % MOD;
        t1 = m + m - n + x + 2, t2 = n - 1 - x; // 第二部分答案（最后 n-1-x 条边权和）
        frac(t1, t2, 2);
        ans = (ans + (t1 % MOD * (t2 % MOD) % MOD)) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Sliarae (赞：1)

观察样例可知，最优构造方案是：维护一个集合 $S$，初始 $S = \{1\}$，依次枚举 $i = 2, 3, \ldots, n$，将 $i$ 与 $S$ 集合中所有点连边，并且让边权尽量小。但是由于只有 $m$ 条边，最后如果边不够用了，就每个 $i$ 与 $S$ 中任意一个点连边。

二分一个最小的 $x$，使得无法连出大小为 $x$ 的完全图。即要求 $m < \frac{x(x + 1)}{2} + (n - x)$。此时前 $x$ 个点可以近似地看成一个完全图，而第 $x + 1 \sim n$ 个点一定向这个完全图中恰好一个点连边，且这些边的边权构成 $[1, m]$ 的一段后缀。

对于前 $x$ 个点的贡献。考虑根据样例，将第 $2$ 个点加入 $S$ 时产生的贡献是 $1$，加入 $3$ 是贡献是 $3$，依次类推，我们可以写出一个数列 $1, 2, 4, 7, 11, \ldots$，我们要求的就是这个数列的前 $x - 1$ 项和。

稍作观察，这个数列可以写成 $f_{n} = \frac{n(n - 1)}{2} + 1$，于是把 $n^2, n, 1$ 三项拆开，用一些小学求和公式可以快速求出 $f_n$ 的前 $x - 1$ 项和。

对于第 $x + 1 \sim n$ 个点的贡献是简单的，它们连边的权值分别为 $m, m - 1, \ldots, m - (n - k) + 1$，用一个等差数列求和公式即可。

最后贴一下答案为：

$$

\frac{(x^2 - 2x + 6)(x - 1)}{6} + \frac{(n - x)(2m - n + x + 1)}{2}

$$

```cpp
#include <iostream>

using namespace std;
using LL = long long;
using i128 = __int128;

int main () {
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--) {
    LL n, m;
    cin >> n >> m;
    LL L = 1, R = min(n - 1, LL(2e9));
    while (L <= R) {
      LL mid = (L + R) >> 1;
      if (m < mid * (mid - 1) / 2 + (n - mid)) R = mid - 1;
      else L = mid + 1;
    }
    LL x = L;
    i128 ans = i128(x * x - x * 2 + 6) * (x - 1) / 6 + i128(n - x) * (m * 2 - n + x + 1) / 2; 
    cout << int(ans % 998244353) << '\n';
  }
  return 0; 
}
```

---

## 作者：lllyyykkk (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P12375)

对于最小生成树的本质进行思考，就是对于 $n$ 个点只会选取最小的 $n-1$ 条边。

结合题目要求，应该贪心地选取边，即应该对于前面的点选成完全图。  
对于后面的点，显然用大边构成一条长链是最优的。

所以整张图由三部分组成：
- 一个完全子图
- 一根长链
- 一个用来凑边数的东西。

由于第三部分并没有贡献，所以我们要分别计算第一和第二部分的贡献。  
在第一部分中，对于 $x$ 个点，会有 $ \sum_{i=1}^{x}  {\frac{x(x-1)}{2}+1} $ 的贡献。  
注意到边数是单调不降的，所以可以二分求出点数 $x$。  
统计结果时，用平方和加等差数列求和计算，具体式子如下：
$$
\sum_{i=1}^{x}  {\frac{x(x-1)}{2}+1}=\sum_{i=1}^{x} \frac{x^2}{2}-\sum_{i=1}^{x} \frac{x}{2}+1=\frac{x(x+1)(2x+1)}{12}-\frac{x(x+1)}{4}+x=\frac{x(x-1)(x+1)}{6}+x
$$

在第三部分中，会有 $n-x$ 条待加入的有效边，令他们为最大的 $n-x$ 条，同样用等差数列求和即可，式子如下：
$$
\sum_{i=m-n+x+1}^{m}i=\frac{(2m-n+x+1)(n-x)}{2}
$$
代码细节有点多，注意二分的边界。  
### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
__int128 B=1;
const int mod=998244353,inv2=499122177,inv6=166374059;
ll T,n,m;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		ll ans=3,L=3,R=n,res=n;
		while(L<=R){
			ll mid=L+R>>1;
			if(B*mid*(mid-1)/2+n-mid>=m) res=mid,R=mid-1;
			else L=mid+1;
		}
		ans=((res-2)*(res-1)%mod*res%mod*inv6%mod+res-1+mod)%mod;
		if(B*res*(res-1)/2+n-res>=m) ans=(ans+B*(2*m-n+res+1)*(n-res)%mod*inv2%mod)%mod;
		cout <<ans<<'\n';
	}
	return 0;
}
``````

---

## 作者：Anemones (赞：0)

我们考虑 kruskal 求最小生成树的过程：将边从小到大排序后枚举，如果这条边的两个端点 $u,v$ 已在一个并查集里就不连。

既然从小到大，那我们便要让边权 $w$ 的边选定后，接下来边权 $w+1,w+2,w+3\dots$ 的边尽可能不被选上，那就是往之前已经在并查集里的边连边（这样就失效了）。

由于无重边，所以我们会得到 $1+2+4+7+11+16\dots$ 这样的一串求和，而这些数的差是 $1,2,3,4,5\dots$。注意，这里当消耗完足够的边后就对后面的直接求和。

令 $t=1+\lfloor\frac{-1+\sqrt{1+8(m-n+1)}}{2}\rfloor$（其中 $m-n+1$ 是因为要保证图连通连 $n-1$ 条边），则答案为 $1+t+\sum\limits_{i=1}^t \frac{(i+1)\times i}{2}$ 再加上后面的等差数列求和即可。

对于 $\sum\limits_{i=1}^t \frac{(i+1)\times i}{2}$ 可以用 $\sum\limits_{i=1}^ni^2=\frac{n(n+1)(2n+1)}{6}$ 求。


应该是要用 `__int_128_t` 的，开根还得手写二分/lh。

```cpp
#include<bits/stdc++.h>
#include<ext/rope>
using namespace __gnu_cxx;
#define mp make_pair
#define pb push_back
#define dbg puts("-------------qaqaqaqaqaqaqaqaqaq------------")
#define pl (p<<1)
#define pr ((p<<1)|1)
#define pii pair<int,int>
#define int __int128_t
#define mod 998244353
#define eps 1e-9
#define ent putchar('\n')
#define sp putchar(' ')
using namespace std;
inline int read(){
    char c=getchar(),f=0;int t=0;
    for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
    for(;c>='0'&&c<='9';c=getchar()) t=(t<<1)+(t<<3)+(c^48);
    return f?-t:t;
}
inline void write(int x){
    static int t[25];int tp=0;
    if(x==0) return(void)(putchar('0'));else if(x<0) putchar('-'),x=-x;
    while(x) t[tp++]=x%10,x/=10;
    while(tp--) putchar(t[tp]+48);
}
int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
int sqrti(int x){
    int l=1,r=x,ans=0;
    while(l<r){
        int mid=(l+r)>>1;
        if(x>=mid*mid){
            ans=mid;
            l=mid+1;
        }
        else r=mid;
    }
    return ans;
}
signed main(){
    for(signed p=1;p<=1;p++){
        char awa[30];
		//sprintf(awa,"mst%d.in",p);
		//freopen(awa,"r",stdin);
		//sprintf(awa,"mst%d.out",p);
	    //freopen(awa,"w",stdout);
        int T=read();
        //int inv2=qpow(2,mod-2),inv6=qpow(6,mod-2);
        while(T--){
            int n=read(),m=read();
            int pwp=m-n+1,qaq;
            qaq=(sqrti(1+8*pwp)-1)/2+1; // 这里记录的是能直接处理的个数去掉 1
            if(qaq==n-1) qaq--; //要保证最后一个有数
            int lp=qaq*(qaq+1)*(2*qaq+1)/6,rp=qaq*(qaq+1)/2;
            int sum=(lp+rp)/2;
            int cwc=n-qaq-2; // 还要多少个数
            int ovo=m-cwc+1; // 末位。
            int res=(ovo+ovo+cwc-1)*cwc/2;
            //write(qaq),sp,write(sum),sp,write(cwc),sp,write(ovo),ent;
            write((qaq+1+sum+res)%mod),ent;
            // 1+2+4+7+11=25
            // 0+1+2+3
            // 1 2 3
        }
    }
    return 0;
}
```

---

