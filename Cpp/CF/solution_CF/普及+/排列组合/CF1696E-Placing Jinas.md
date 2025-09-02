# Placing Jinas

## 题目描述

We say an infinite sequence $ a_{0}, a_{1}, a_2, \ldots $ is non-increasing if and only if for all $ i\ge 0 $ , $ a_i \ge a_{i+1} $ .

There is an infinite right and down grid. The upper-left cell has coordinates $ (0,0) $ . Rows are numbered $ 0 $ to infinity from top to bottom, columns are numbered from $ 0 $ to infinity from left to right.

There is also a non-increasing infinite sequence $ a_{0}, a_{1}, a_2, \ldots $ . You are given $ a_0 $ , $ a_1 $ , $ \ldots $ , $ a_n $ ; for all $ i>n $ , $ a_i=0 $ . For every pair of $ x $ , $ y $ , the cell with coordinates $ (x,y) $ (which is located at the intersection of $ x $ -th row and $ y $ -th column) is white if $ y<a_x $ and black otherwise.

Initially there is one doll named Jina on $ (0,0) $ . You can do the following operation.

- Select one doll on $ (x,y) $ . Remove it and place a doll on $ (x,y+1) $ and place a doll on $ (x+1,y) $ .

Note that multiple dolls can be present at a cell at the same time; in one operation, you remove only one. Your goal is to make all white cells contain $ 0 $ dolls.

What's the minimum number of operations needed to achieve the goal? Print the answer modulo $ 10^9+7 $ .

## 说明/提示

Consider the first example. In the given grid, cells $ (0,0),(0,1),(1,0),(1,1) $ are white, and all other cells are black. Let us use triples to describe the grid: triple $ (x,y,z) $ means that there are $ z $ dolls placed on cell $ (x,y) $ . Initially the state of the grid is $ (0,0,1) $ .

One of the optimal sequence of operations is as follows:

- Do the operation with $ (0,0) $ . Now the state of the grid is $ (1,0,1),(0,1,1) $ .
- Do the operation with $ (0,1) $ . Now the state of the grid is $ (1,0,1),(1,1,1),(0,2,1) $ .
- Do the operation with $ (1,0) $ . Now the state of the grid is $ (1,1,2),(0,2,1),(2,0,1) $ .
- Do the operation with $ (1,1) $ . Now the state of the grid is $ (1,1,1),(0,2,1),(2,0,1),(1,2,1),(2,1,1) $ .
- Do the operation with $ (1,1) $ . Now the state of the grid is $ (0,2,1),(2,0,1),(1,2,2),(2,1,2) $ .

Now all white cells contain $ 0 $ dolls, so we have achieved the goal with $ 5 $ operations.

## 样例 #1

### 输入

```
2
2 2 0```

### 输出

```
5```

## 样例 #2

### 输入

```
10
12 11 8 8 6 6 6 5 3 2 1```

### 输出

```
2596```

# 题解

## 作者：lenlen (赞：13)

一道关于杨辉三角的结论题。

### Problem

题目大意：给定 $n+1$ 个数 $a_i$，即第 $i$ 行前 $a_i$ 个格子是白色的，其余点是黑色的，你可以花费 $1$ 的代价使第 $i,j$ 格子内的数 $-1$，$i+1,j$ 和 $i,j+1$ 格子内的数 $+1$，问最少要多少次使白格中都为 $0$。初始状态：第 $0$ 行第一个数为 $1$。

数据范围： $n \leq 2 \times 10^5,a_i \leq 2 \times 10^5$。

### Solution

习惯性地，我把行数从 $[0,n]$ 变成了 $[1,n+1]$，不变也行，而且还简单些。

首先这就是个杨辉三角，第 $i,j$ 个格子的值等于 $i-1,j$ 和 $i,j-1$ 格子之和。所以我们可以把第 $i$ 行 $j$ 列的数表示出来：

原杨辉三角中，第 $i$ 行第 $j$ 个的值为 $C_{i-1}^{j-1}$，这个不知道的话就需要自己补补数论了。然后我们可以推导出来第 $x$ 行第 $y$ 列的公式：

```latex
      1      1      1      1      1      1      1      1      1      1
      1      2      3      4      5      6      7      8      9     
      1      3      6     10     15     21     28     36     
      1      4     10     20     35     56     84    
      1      5     15     35     70    126    
      1      6     21     56    126    
      1      7     28     84    
      1      8     36    
      1      9     
      1  
```

可以发现，第 $x$ 行第 $y$ 列满足下面两个条件：

$$\begin{cases}
	&x+y-1=i\\
    &y=j
\end{cases}$$

所以我们可以推出第 $x$ 行第 $y$ 列的计算公式： $C_{i-1}^{j-1}=C_{x+y-2}^{y-1}$。

我们设 $f(x,y)=C_{x+y-2}^{y-1}$。

所以我们最后要求 $\sum\limits_{i=1}^{n+1} \sum\limits_{j=1}^{a_i} f(i,j)$。

可以证明： 

$$f(i+1,j)+f(i,j+1)=C_{i+j-1}^{j-1}+C_{i+j-1}^j=C_{i+j}^j=f(i+1,j+1)$$

可以发现复杂度是 $O(n^2)$ 的，所以我们还要进行优化，我们把 $\sum\limits_{j=1}^{a_i} f(i,j)$ 拆开，也就变成了：

$$\begin{aligned}
\sum\limits_{j=1}^{a_i} f(i,j)& = f(i,1)+f(i,2)+ \cdots f(i,a_i)\\
&=C_{i-1}^0+f(i,2)+ \cdots +f(i,a_i)\\
&=1+f(i,2)+ \cdots +f(i,a_i)\\
&=C_i^0+f(i,2)+ \cdots +f(i,a_i)\\
&=f(i+1,1)+f(i,2)+ \cdots +f(i,a_i)\\
&=f(i+1,2)+f(i,3)+ \cdots +f(i,a_i)\\
&=f(i+1,a_i)\\
&=C_{a_i+i-1}^{a_i-1}
\end{aligned}$$

所以最后就变成了求 $\sum\limits_{i=1}^{n+1} C_{a_i+i-1}^{a_i-1}$，可以 $O(n)$ 求解。

### Code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=5e5+7232,mod=1e9+7;
long long n,a[N];
long long inv[N],deinv[N],ans;
long long po(long long x,long long y)
{
    long long sum=1;
    while(y) 
    {
        if(y&1) sum=sum*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return sum;
}
long long C(long long n,long long m)
{
    if(m<0) return 0;//记得特判，不然会RE
    return inv[n]*deinv[m]%mod*deinv[n-m]%mod;
}
int main()
{
	scanf("%lld",&n);++n;
    for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);
    inv[0]=1;deinv[0]=1;
    for(long long i=1;i<=N-10;i++)//预处理逆元
    {
        inv[i]=inv[i-1]*i%mod;
        deinv[i]=po(inv[i],mod-2);
    }
    for(long long i=1;i<=n;i++) ans=(ans+C(a[i]+i-1,a[i]-1))%mod;//公式
    printf("%lld\n",ans);
}

```


---

## 作者：liangbowen (赞：5)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1696E)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17278408.html)

结论题。

## 思路

很明显这是计数题而不是最小值。手玩样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/x97uaapo.png)

很容易发现以下性质：

+ 第一步肯定是操作 $(1, 1)$。
+ 上边缘与左边缘（也就是 $(1, x)$ 与 $(x, 1)$ 的点）操作次数必为 $1$。
+ 对于一个元素，如果上方的值为 $x$，左方的值为 $y$，操作 $(x + y)$ 次后，自己就会变成 $(x + y)$。
+ 对于右下角，若值为 $x$，操作 $x$ 次后清空，操作结束。

转化成数学语言，设 $(x, y)$ 号格子的值为 $v_{x, y}$（此处 $x$ 是行，$y$ 是列），则有：

$$
v_{x, y} =
\begin{cases}
1  &  x=1 \operatorname{or} y=1  \\
v_{x-1,y}+v_{x,y-1}  &  \text{otherwise}
\end{cases}
$$

画出来，斜着看，发现就是杨辉三角。众所周知杨辉三角的每一项都可以对应 $C(n, m)$，画一个图方便理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/2vtvche3.png)

容易发现 $v_{x,y} = C(x+y-2, x-1)$（第一行貌似不属于这个规律）。

综上所述，

$$
\begin{aligned}
\text{answer}
& = a_1 + \sum\limits_{i=2}^{n+1}\sum\limits_{j=1}^{a_i} v_{i,j}  \\
& = a_1 + \sum\limits_{i=2}^{n+1}\sum\limits_{j=1}^{a_i} C(i+j-2, i-1)  \\
& = a_1 + \sum\limits_{i=2}^{n+1}\sum\limits_{j=1}^{a_i}\Big(C(i+j-1,i)-C(i+j-2,i)\Big)  \\
& = a_1 + \sum\limits_{i=2}^{n+1}\Big(C(i,i)-C(i-1,i)+C(i+1,i)-C(i,i)+\cdots+C(i+a_i-1,i)-C(i+a_i-2,i)\Big)  \\
& = a_1 + \sum\limits_{i=2}^{n+1} C(i+a_i-1,i)-C(i-1,i)  \\
& = a_1 + \sum\limits_{i=2}^{n+1} C(i+a_i-1,i)  \\
& = \sum\limits_{i=1}^{n+1} C(i+a_i-1,i)
\end{aligned}
$$

其中，第二步到第三步是使用 $C(x,y)=C(x-1,y-1)+C(x-1,y)$ 变形成 $C(x-1,y-1)=C(x,y)-C(x-1,y)$ 得到的。

于是预处理一下组合数就做完了。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int qpow(int x, int y)
{
	int ans = 1;
	while (y)
	{
		if (y & 1) ans = (1ll * ans * x) % mod;
		x = (1ll * x * x) % mod;
		y >>= 1;
	}
	return ans;
}
int fac[N << 1], invfac[N << 1];
//void init() //O(nlogn)
//{
//	fac[0] = invfac[0] = 1;
//	for (int i = 1; i <= n + N; i++)
//		fac[i] = (1ll * fac[i - 1] * i) % mod,
//		invfac[i] = (1ll * invfac[i - 1] * qpow(i, mod - 2)) % mod;
//}
void init(int n) //O(n)
{
	fac[0] = invfac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = (1ll * fac[i - 1] * i) % mod;
	invfac[n] = qpow(fac[n], mod - 2);
	for (int i = n - 1; i; i--) invfac[i] = 1ll * invfac[i + 1] * (i + 1) % mod;
}
int C(int a, int b)
{
	if (a < 0 || b < 0 || a - b < 0) return 0;
	return 1ll * fac[a] * invfac[a - b] % mod * invfac[b] % mod;
}
int main()
{
	int n;
	scanf("%d", &n), init(N + n);
	int ans = 0;
	for (int i = 1; i <= n + 1; i++)
	{
		int x;
		scanf("%d", &x);
		ans = (ans + C(i + x - 1, i)) % mod;
	}
	cout << ans;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：Erinyes (赞：4)

说是求最小，实际上是一到计数题。

## 解题思路
分析一下性质，很容易就会发现每一行的 $1$ 都是连续的，所以可以把每一行直接平推。

写个暴力打个表，把第二个样例输出一下，移动的时候不把 $cnt$ 清零。

```
  1   1   1   1   1   1   1   1   1   1   1   1   1
  1   2   3   4   5   6   7   8   9  10  11  12   0
  1   3   6  10  15  21  28  36  45  10  11   0   0
  1   4  10  20  35  56  84 120 120   0   0   0   0
  1   5  15  35  70 126 210 120   0   0   0   0   0
  1   6  21  56 126 252 252   0   0   0   0   0   0
  1   7  28  84 210 462 462   0   0   0   0   0   0
  1   8  36 120 330 792   0   0   0   0   0   0   0
  1   9  45 165 330   0   0   0   0   0   0   0   0
  1  10  55   0   0   0   0   0   0   0   0   0   0
  1  11   0   0   0   0   0   0   0   0   0   0   0
```
然后就会发现把这个东西斜着看就是一个杨辉三角。

其实也很好理解，因为对于一个点 $(i,j)$ 来说，在 $(i-1,j)$ 和 $(i,j-1)$ 往后推的时候会把 $cnt$ 加到这个点，所以 $cnt_{i,j}$ 就等于 $cnt_{i-1,j}+cnt{i,j-1}$，然后就成了杨辉三角。

接下来就简单了，根据杨辉三角第 $n$ 层 $m$ 个的值是 $\binom{n-1}{m-1}$，那么转过来变成矩形的 $n$ 行 $m$ 列就是 $\binom{n+m-2}{n-1} $。

所以对于每一行，产生的答案就是杨辉三角第 $i+1$ 行前 $a_i+1$ 个数的和，其实就是第 $i+2$ 行第 $a_i$ 个。

答案就是 $\sum\limits_{i-1}^{n} \binom{i+a_i}{i+1}$。

## 代码
注意题目给的下标是从 $0$ 开始的，其实没必要改，题目怎么给就怎么用就行了。

```cpp
#include<bits/stdc++.h>
#define maxn 500005
#define int long long
#define mod 1000000007
using namespace std;
int n;
int a[maxn],fac[maxn],inv[maxn];
int power(int x,int k){
	if(!k) return 1ll;
	int res=power(x*x%mod,k>>1);
	return res*(k&1?x:1ll)%mod;
}
void init(){
	fac[0]=1; for(int i=1;i<=500000;i++) fac[i]=fac[i-1]*i%mod;
	inv[0]=1; for(int i=1;i<=500000;i++) inv[i]=power(fac[i],mod-2);
}
int C(int n,int m){return n<m?0:fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main(){
	cin>>n; init();
	for(int i=0;i<=n;i++) cin>>a[i];
	int ans=0;
	for(int i=0;i<=n;i++) ans+=C(i+a[i],i+1),ans%=mod;
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：老莽莽穿一切 (赞：3)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16427416.html)

---

首先发现操作次数固定，不管使用什么策略每个位置上的总操作数总是固定的，问题就转化成求每个位置的操作数。

然后再进行一步转化，既然题面中是按行单调递减，我们也考虑按行考虑，当我们开始处理第 $i$ 行时每个位置的**棋子数**。

可以通过手模几组数据显然地得知每行每个位置的初始棋子数都是上一行的前缀和，然后是一个经典的套路，就是高阶前缀和可以用组合数解决，所以预处理组合数，再直接算就好了。

具体而言，第 $i$ 行的第 $j$ 个位置的棋子数（$i,j$ 都从 $0$ 开始）是只有 $a_0=1$ 的序列的 $i$ 阶前缀和的第 $j$ 位，结果是 $\dbinom{i+j-1}j$。

然后计算每个位置的操作数，可以通过前面的棋子数推出，第 $i$ 行的第 $j$ 个位置的**操作数**是第 $i$ 前 $j$ 个位置的棋子数，所以要再做一遍前缀和，答案就是 $\dbinom{i+j}j$。

最后一个一个位置算肯定是不行的，所以要一行一行算，所以每行对前面的式子做前缀和，注意因为上面的 $[0,a_i)$ 是开区间，所以答案就是：

$$
\sum_{i=0}^n\dbinom{i+a_i}{a_i-1}
$$

[**代码**](https://codeforces.com/contest/1696/submission/162000775)实现比上一题还简单得多。

---

## 作者：jia_shengyuan (赞：1)

磕了一个小时D不会，第二天看E，就这（

首先注意到题目要求 $a_i$ 不增，但不难发现 $a_i$ 的单调性不会影响暴力的正确性。这告诉我们正解一定是对于每一列用一个公式算出来，因为公式计算才需要保证之前的 $a$ 不对后面产生影响。

回到题目，$(x,y)$ 对答案的贡献 $=(x,y)$ 上的娃娃数 $=(x-1,y)$ 的娃娃数 $+(x,y-1)$ 上的娃娃数 $=(0,0)\to(x,y)$ 的路径数 $=\dbinom{x+y}{x}$（因为一共走 $x+y$ 步，其中向右走 $x$ 步）。

因此，第 $x$ 列的答案就是 $\sum\limits_{y=0}^{a_x-1}\dbinom{x+y}{x}$，接下来我们要化简。好像有大佬直接组合数裂项了，我太菜了，不会，于是用了小奥学的整数裂项。举个例子，要计算 $1\times2\times3+2\times3\times4+\cdots+8\times9\times10$，利用 $x(x+1)(x+2)=\frac{x(x+1)(x+2)(x+3)-(x-1)x(x+1)(x+2)}{4}$，可以将上式化为 $\frac{8\times9\times10\times11}{4}$。

由于要计算的组合数中分母都是 $x!$，而分子就是一个类似上方的整数裂项形式，只不过是相邻 $x$ 项相乘，于是预处理出所有阶乘以及其逆元，问题就解决了。（字打错了，重交了一遍（（

```cpp
#include <cstdio>
#define ll long long

const int maxn = 2e5+9, mod = 1e9+7;

ll inv[maxn<<1],jc[maxn<<1],ijc[maxn<<1];
int a[maxn],n;

int main(){
    scanf("%d",&n);
    for(int i=0; i<=n; i++) scanf("%d",&a[i]);
    inv[1]=jc[0]=ijc[0]=1;
    for(int i=2; i<maxn<<1; i++) inv[i] = (ll)(mod-mod/i)*inv[mod%i]%mod;
    for(int i=1; i<maxn<<1; i++){
        jc[i] = jc[i-1]*i%mod;
        ijc[i] = ijc[i-1]*inv[i]%mod;
    }
    ll ans = 0;
    for(int i=0; i<=n; i++){
        // for(int j=0; j<a[i]; j++) ans += C[i+j][i]; 这是暴力
        ll x = i+a[i]-1;
        ans = (ans+jc[x+1]*ijc[x-i]%mod*ijc[i+1]%mod)%mod;
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16420744.html)

[题目传送门](http://codeforces.com/problemset/problem/1696/E)

upd on 2022.9.13：好像有点小问题在评论里面被指出，已经修改。

### 题目大意
给定一个 **单调不增** 的序列 $a$，第 $0$ 到 $n$ 项为 $a_1,a_2,\dots,a_n$，之后的为全 $0$。  
对平面直角坐标系上的每个整点进行染色，对于一个点 $(x,y)$ 如果 $y<a_x$ 那么这个点位白色，否则为黑色。  
每次操作你可以使点 $(x,y)$ 上的娃娃数量减一，同时 $(x,y+1)$ 和 $(x+1,y)$ 上的娃娃数量都会加一。  
现在在 $(0,0)$ 上有一个娃娃，求让所有的白色点上都没有娃娃的操作数量，对 $10^9+7$ 取模。  
$n\le 2\times10^5,0\le a_i\le 2\times10^5$
### 题目解析
设 $f(x,y)$ 为对点 $(x,y)$ 实行的操作次数。  
我们发现，当 $x=0$ 或者是 $y=0$ 的时候，$f(x,y)=1$，否则 $f(x,y)=f(x-1,y)+f(x,y-1)$。  
我们发现这个递推式像杨辉三角的递推式，不难得到 $f(x,y)=C_{x+y}^{x}$。  

那么答案就是
$$\sum_{i=0}^{n}\sum_{j=0}^{a_i-1}f(i,j)$$
但是这样求是 $O(n^2)$ 的，所以需要考虑化简这个式子。  
注意到
$$
\begin{aligned}
& \sum_{i=0}^{n}f(x,i)\\
= & f(x,0)+f(x,1)+f(x,2)+ f(x,3)+\cdots+f(x,n)\\
= & f(x+1,0)+f(x,1)+f(x,2)+ f(x,3)+\cdots +f(x,n)\\
= & f(x+1,1)+f(x,2)+ f(x,3) + \cdots f(x,n) \\
\vdots &\\
= & f(x+1,n)
\end{aligned}
$$

所以答案就是
$$
\begin{aligned}
& \sum_{i=0}^{n}\sum_{j=0}^{a_i-1}f(i,j)\\
= & \sum_{i=0}^{n}f(i+1,a_i-1)\\
= & \sum_{i=0}^{n}C_{a_i+i}^{i+1}
\end{aligned}
$$

代码：
```cpp
int n,a[maxn]; ll fact[maxn],inv[maxn],ans;
ll mpow(ll x,ll y){
	ll res=1,tmp=x%MOD;
	while(y){
		if(y&1) res=res*tmp%MOD;
		y>>=1; tmp=tmp*tmp%MOD;
	} return res;
}
void init(){
	int i; inv[0]=fact[0]=1; for(i=1;i<=N;i++) fact[i]=fact[i-1]*i%MOD;
	inv[N]=mpow(fact[N],MOD-2); for(i=N-1;i>=1;i--) inv[i]=inv[i+1]*(i+1)%MOD; return;
}
ll C(int x,int y){ return fact[x]*inv[y]%MOD*inv[x-y]%MOD; }
int main(){
	n=read(); int i; for(i=0;i<=n;i++) a[i]=read(); init();
	for(i=0;i<=n;i++) if(a[i]>=1) ans+=C(a[i]+i,i+1),ans%=MOD;
	print(ans%MOD); return 0;
}
```

---

## 作者：stripe_python (赞：0)

本题解摘自 [OI 中的数学基础](https://www.luogu.com.cn/article/bhxqoy6g)。

显然是从格子 $(0,0)$ 开始操作，一路递推，故设 $(x,y)$ 的末值为 $f_{x,y}$，则
$$
f_{x,y}=f_{x-1,y}+f_{x,y-1}
$$
对比杨辉三角的计算方法（组合数性质 2）
$$
C_{n}^{m}=C_{n-1}^{m}+C_{n-1}^{m-1}
$$
发现两者很像，考虑用组合数表示 $f_{x,y}$。对比两者系数可得
$$
f_{x,y}=C_{x+y}^{x}
$$
因此答案为
$$
\sum_{i=0}^{n} \sum_{j=0}^{a_i-1} f_{i,j}=\sum_{i=0}^{n} \sum_{j=0}^{a_i-1} C^{i}_{i+j}
$$
预处理逆元后复杂度为 $O(nV)$，无法通过。所以得推波式子：
$$
\begin{aligned}
ans&=\sum_{i=0}^{n} \sum_{j=0}^{a_i-1} f_{i,j}\\
&=\sum_{i=0}^{n} (f_{i,0}+f_{i,1}+\cdots+f_{i,a_i-1})\\
&=\sum_{i=0}^{n} (f_{i+1,0}+f_{i,1}+\cdots+f_{i,a_i-1})\\
&=\sum_{i=0}^{n} (f_{i+1,1}+f_{i,2}+\cdots+f_{i,a_i-1})\\
&=\sum_{i=0}^{n} (f_{i+1,2}+f_{i,3}+\cdots+f_{i,a_i-1})\\
&=\sum_{i=0}^{n} f_{i+1,a_i-1+1}\\
&=\sum_{i=0}^{n} C_{i+a_i}^{i+1}
\end{aligned}
$$
在推式子的过程中，利用 $f_{x,y}=f_{x-1,y}+f_{x,y-1}$ 不断合并相邻两项即可。还有一种方法是化成组合数求和后裂项。

采用预处理逆元求组合数，复杂度可以做到 $O(n)$。注意 $a_i+i$ 可以到 $4\times 10^{5}$，预处理范围要开大。

```cpp
const int N = 4e5 + 5;
int n, a[N];
mint fac[N], ifac[N];
mint C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * ifac[m] * ifac[n - m]; 
}

void _main() {
	cin >> n;
	for (int i = 0; i <= n; i++) cin >> a[i];
	fac[0] = ifac[0] = 1;
	for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i, ifac[i] = ~fac[i];
	mint res = 0;
	for (int i = 0; i <= n; i++) res += C(i + a[i], i + 1);
	cout << res;
}
```

---

## 作者：wqc2011 (赞：0)

[传送门(CF)](https://codeforces.com/problemset/problem/1696/E)

[传送门(洛谷)](https://www.luogu.com.cn/problem/CF1696E)

### 思路

通过转换法，这道题的答案就是在求每一个有效格子上会出现多少个“1”，因为每一次操作都会在当前格子上减去一个“1”，所以如果想要这个格子上没有“1”，就至少要操作这个格子上“1”的个数次，因而我们可以推出一个 $dp$ 式。
$$\begin{cases}  dp_{0,0} = 1 \\ dp_{i,j} = dp_{i - 1,j} + dp_{i,j - 1} \\ \begin{aligned} ans = \sum_{i = 0}^{n} \sum_{j = 0}^{a_i - 1} dp_{i,j} \end{aligned} \end{cases}$$
其中 $dp_{1,j}$ 表示为在格子 $(i,j)$ 上会出现多少个“1”，因为每个“1”都只能从 $(i - 1,j)$ 和 $(i,j - 1)$ 上转过来。

### 改进与优化

我们通过观察每个 $dp_{i,j}$ 的值（如下图）和 $dp$ 
递推式。
||j:|0|1|2|3|4|5|6|...|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|i:||||||||||
|0||1|1|1|1|1|1|1|...|
|1||1|2|3|4|5|6|7|...|
|2||1|3|6|10|15|21|28|...|
|3||1|4|10|20|35|56|84|...|
|4||1|5|15|35|70|126|...|...|
|5||1|6|21|56|126|...|...|...|
|6||1|7|28|84|...|...|...|...|
|...||...|...|...|...|...|...|...|...|

我们可以发现，每一个 $dp_{i,j}$ 其实就是一个组合数 $C_{i,i+j}$ 我们对它们进行求和即可。我们又发现，其实有如下奇特的转化。
$$\begin{aligned} \sum_{i = 0}^{n} \sum_{j = 0}^{a_i - 1} C_{i,i+j} = \sum_{i = 0}^{n} C_{i + 1,i + a_i} \end{aligned}$$
因此我们可以运用组合数求解即可，在时间复杂度之内。

### 代码附上

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optimize(3)
using namespace std;
const int maxn = 400010;
const int inf = 1e9 + 7;
//unsigned long long 
//cout << fixed << setprecision(3)
//cout << setw(5) << 
//continue
int a[maxn];
int dp[maxn], dp1[maxn];
int pow1(int x, int d){
	if(d == 1) return x % inf;
	if(d == 0) return 1 % inf;
	int p = pow1(x, d / 2) % inf;
	if(d % 2) return p * p % inf * x % inf;
	return p * p % inf;
}
void into(){
	dp[0] = dp1[0] = 1;
	for(int i = 1;i < maxn;i++){
		dp[i] = dp[i - 1] * i % inf;
		dp1[i] = dp1[i - 1] * pow1(i, inf - 2) % inf;
	}
}
int C(int m, int n){
	if(m > n) return 0;
	if(m == n) return 1;
	return dp[n] * dp1[n - m] % inf * dp1[m] % inf;
}
signed main(){
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int n, ans = 0;
	cin >> n;
	for(int i = 0;i <= n;i++) cin >> a[i];
	into();
	// cout << C(2, 6) << endl;
	for(int i = 0;i <= n;i++){
		ans = (ans + C(i + 1, a[i] + i)) % inf;
		//cout << i << ' ' << C(i, a[i] + i - 1) << endl;
	}
	cout << ans;
    return 0;
}
```
感谢阅读。

---

## 作者：complete_binary_tree (赞：0)

首先，由题意，我们可以（手推）发现一个性质：

```
\|1 2 3 4 5 ...
---------
0|1 1 1 1 1 ...
1|1 2 3 4 5 ...
2|1 3 6 10 15 ...
3|1 4 10 20 35 ...
...
```

其中，第 $i$ 行第 $j$ 列表示如果第 $i$ 行有第 $j$ 个格子，第 $j$ 个格子清零所需要的最小操作次数。

那么，由于这是前缀和的关系，如果第 $i$ 行有 $a_i$ 个数，那么这行清零的操作次数为 $(i,a_1)+(i,a_2)+\dots+(i,a_i)=(i+1,a_i)$。

然后，你再看看这个表格，是不是好像在哪里见过呢？

没错——

```
 |0 1 2 3
----------
0|1
1|1 1
2|1 2 1
3|1 3 3 1
...
```

就是杨辉三角。

于是，你就可以得到：$(i+1,a_i)=C_{a_i+i}^{a_i-1}$。

那么答案就是：

$$\sum_{i=0}^nC_{a_i+i}^{a_i-1}$$

时间复杂度 $O(n)$。最后别忘了预处理到 $2n$！

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5, mod = 1e9 + 7;

int ksm(int a, int b){
	long long x = a, ans = 1;
	while(b){
		if(b & 1) ans = ans * x % mod;
		x = x * x % mod, b >>= 1;
	}
	return ans;
}

int jc[N], ny[N];

void csh(){
	jc[0] = 1;
	for(int i = 1; i <= 4e5+1; ++i) jc[i] = 1ll * jc[i - 1] * i % mod;
	ny[int(4e5+1)] = ksm(jc[int(4e5+1)], mod - 2);
	for(int i = 4e5; i >= 0; --i) ny[i] = 1ll * ny[i + 1] * (i + 1) % mod;
}

int C(int n, int m){
	return 1ll * jc[n] * ny[m] % mod * ny[n - m] % mod;
}

int a, n;
int ans = 0;

int main(){
	scanf("%d", &n);
	csh();
	for(int i = 0; i <= n; ++i){
		scanf("%d", &a);
		ans = (0ll + ans + C(a + i, a - 1)) % mod;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

纯纯数学题。

最小值就是把白格子里的东西走出去。

首先，如果 $a_i=0$ 就相当于全是黑格子，不妨 $a_n>0$。

把格子补全，看看是什么情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/bqc7mlw2.png)

熟悉杨辉三角的人已经发现了，就是斜着的杨辉三角。

由于 $a_i\ge a_{i+1}$，所以左边转移到右边一定成立。

同时，根据题目意思，从上面转移到下面一定成立。

所以，就是杨辉三角，然后搞一个奇奇怪怪的格子纸，让你求限定范围内的总和。

先求一下每一个格子的表达式吧。下面求解的过程中认为行和列都从 $0$ 开始标号（所以不妨先另 $a_i'\leftarrow a_i-1$）。

$(0,0)$ 到 $(x,y)$ 总共走了 $x+y$ 步，总共有 $C_{x+y}^y$ 种走法。发现每一种走法对应在该点会多一个东西，所以该点的贡献就是 $C_{x+y}^y$。

所以可以列出表达式 $ans=\sum\limits_{i=0}^n\sum\limits_{j=0}^{a_i}C_{i+j}^j$（注意 $a_i$ 不是原来输入的，已经减小了）。

同时，只要发现一个组合恒等式 $C_{n}^k+C_n^{k+1}=C_{n+1}^{k+1}$ 即可。

> 证明：
> 
> $LHS=\dfrac{n!}{k!(n-k)!}+\dfrac{n!}{(n-k-1)!(k+1)!}=n!\cdot\dfrac{n-k+k+1}{(n-k)!(k+1)!}=\dfrac{(n+1)!}{(n-k)!(k+1)!}=RHS$。

所以，$\sum\limits_{j=0}^{a_i}C_{i+j}^j=\sum\limits_{j=0}^{a_i}C_{i+j}^i=C_i^i+C_{i+1}^i+\cdots+C_{i+a_i}^i=C_{i+1}^{i+1}+C_{i+1}^i+\cdots+C_{i+a_i}^i=C_{i+2}^{i+1}+C_{i+2}^i+\cdots+C_{i+a_i}^i=C_{i+a_i+1}^{i+1}$。

答案很好求了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7, N = 2e5 + 5, maxn = 4e5;
int n, a[N], fac[N << 1], inv[N << 1], ans;
inline void init(){
    n = maxn;
    fac[0] = fac[1] = inv[0] = inv[1] = 1ll;
    for(int i = 2; i <= n; i++){
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        fac[i] = fac[i - 1] * i % mod;
    }
    for(int i = 2; i <= n; i++) inv[i] = inv[i - 1] * inv[i] % mod;
}
inline int C(int x, int y){
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
}
signed main(){
    init();
    scanf("%lld", &n);
    for(int i = 0; i <= n; i++) scanf("%lld", &a[i]), a[i]--;
    while(a[n] < 0) n--;
    for(int i = 0; i <= n; i++){
        (ans += C(i + a[i] + 1, i + 1)) %= mod;
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

[CF1696E](https://www.luogu.com.cn/problem/CF1696E)

[Placing Jinas](https://codeforces.com/problemset/problem/1696/E)

### 思路

数学题。

答案是唯一的。操作过程从左上到右下不可逆。每个点操作次数的贡献即每个点数的最大值。

类似于递推：

$$dp_{i,0}=dp_{0,i}=1$$

$$dp_{i,j}=dp_{i-1,j}+dp_{i,j-1}$$

则答案为划定范围内所有 $dp$ 数组值的和。

但这样是 $O(n^2)$ 的。

又发现斜着看这其实是杨辉三角。

$$C_{i+j}^{i}=dp_{i,j}$$

$$ans=\sum_{i=0}^n \sum_{j=0}^{a_i-1} C_{i+j}^{i}=\sum_{i=0}^n \sum_{j=0}^{a_i-1} dp_{i,j}$$

经过打表和 [OEIS](https://oeis.org/)，发现：

$$\sum_{j=0}^{a_i-1} dp_{i,j}=dp_{i+1,a_i-1}$$

补证明：


$$\sum_{j=0}^{a_i-1} dp_{i,j}=dp_{i,0}+\sum_{j=1}^{a_i-1}dp_{i,j}=dp_{i+1,0}+\sum_{j=1}^{a_i-1}dp_{i,j}=dp_{i+1,a_i -1}$$


于是可以 $O(n)$。

### code

```cpp

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,a[maxn],ans;
int pw[maxn],inv[maxn];
inline int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){
	return pw[m]*inv[n]%mod*inv[m-n]%mod;
}

signed main(){
	n=read();
	for(int i=0;i<=n;i++)a[i]=read();
	pw[0]=inv[0]=1;
	for(int i=1;i<=maxn-10;i++)pw[i]=pw[i-1]*i%mod,inv[i]=ksm(pw[i],mod-2);
	for(int i=0;i<=n;i++)ans+=C(a[i]+i,i+1),ans%=mod;
	printf("%lld\n",ans);
}

```


---

## 作者：daniEl_lElE (赞：0)

## 思路

考虑到在 $(x,y)$ 进行一次操作等价于删去 $(x,y)$ 位置的棋子并在 $(x+1,y),(x,y+1)$ 各放置一颗，于是我们的问题变成了在每一个位置总共有的棋子数之和。

我们发现对于每一条从 $(0,0)$ 到 $(x,y)$ 的路径均对应着到 $(x,y)$ 的一颗棋子。理由也很简单，就是相当于每次分裂时走两个点中的一个最后到了 $(x,y)$，自然对应着这里的一个棋子。于是问题变成了对于所有 $(x,y)$，从 $(0,0)$ 到 $(x,y)$ 的路径数之和。

注意到 $(0,0)$ 到 $(x,y)$ 的路径数由基本的组合数学可知是 $\binom{x+y}{x}$。于是问题再一次转化成求 $\binom{x+y}{x}$ 之和。

对于第 $i$ 行：

$$\sum_{j=0}^{a_i-1} \binom{i+j}{j}=\sum_{j=0}^{a_i-1}\binom{i+j+1}{j}-\binom{i+j}{j-1}=\binom{i+a_i}{a_i}-0=\binom{i+a_i}{a_i}$$

那么问题的答案就是：

$$\sum_{i=1}^n\binom{i+a_i}{a_i}$$

复杂度 $\Theta(n)$，预处理逆元即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
signed main(){
	init();
	int n;
	cin>>n;
	int a[n+2],tot=0;
	for(int i=1;i<=n+1;i++) cin>>a[i];
	for(int i=1;i<=n+1;i++){
		tot+=C(a[i]+i-1,i);
		tot%=mod; 
	}
	cout<<tot;
	return 0;
}
```

---

