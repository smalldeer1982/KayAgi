# Little Pony and Expected Maximum

## 题目描述

暮暮刚刚在和她的朋友——AJ（苹果杰克）、FS（小蝶）、RD（云宝黛西）玩Ludo游戏。但是她马品没攒够总是输。回到城堡过后，她对游戏用的骰子产生了兴趣。


这个骰子有M面：骰子的第一面有一个点，第二面有两个点，以此类推，第m面含有M点。暮暮确信的是，当掷骰子时，每一面都有1/m的可能性出现，并且每次投掷的概率都是都是独立的。请你帮助她计算掷N次骰子后每次得到的点数中最大值的期望。

## 样例 #1

### 输入

```
6 1
```

### 输出

```
3.500000000000
```

## 样例 #2

### 输入

```
6 3
```

### 输出

```
4.958333333333
```

## 样例 #3

### 输入

```
2 2
```

### 输出

```
1.750000000000
```

# 题解

## 作者：da32s1da (赞：27)

一道期望DP

如果投$n$次，最大点数是$k$，那么情况共有$k^n-(k-1)^n$种。

若$n$次投掷的点数都在$1$到$k$内，共有$k^n$种情况。

若$n$次投掷的点数都在$1$到$k-1$内，共有$(k-1)^n$种情况。

这两个数值相减即可得到最大值是$k$的情况。

所以我们的期望$ans=\frac{\sum_{i=1}^mi\times (i^n-(i-1)^n)}{m^n}=\sum_{i=1}^mi\times((\frac{i}{m})^n-(\frac{i-1}{m})^n).$


```
#include<cstdio>
#include<cmath>
using namespace std;
double n,m,ans;
int main(){
	scanf("%lf%lf",&m,&n);
	for(double i=1;i<=m;i++)
	ans+=i*(pow(i/m,n)-pow((i-1)/m,n));
	printf("%.12lf\n",ans);
}
```

---

## 作者：Steadywelkin (赞：11)

### 题意

题目的意思可以转化为有 $n$ 个随机变量 $X_1,X_2,X_3,\dots{X_n}$，每个随机变量的取值范围都为 $[1,m]$ ，求出 $\max\{X_1,X_2,X_3,\dots{X_n}\}$ 的期望。

### 思路

对于离散变量的概率，有以下的前缀和性质：

> $P(X=K)=P(X\le{K})-P(X\le{K-1})$

我们考虑用上式对本题进行化简：

> $\begin{aligned}E(\max)&=\sum\limits_{i=1}^{m}P(\max=i)\times{i}\\
&=\sum\limits_{i=1}^{m}(P(\max\le{i})-P(\max\le{i-1}))\times{i}\\
&=\sum\limits_{i=1}^{m}(\frac{i^n}{m^n}-\frac{(i-1)^n}{m^n})\times{i}\\
&=\sum\limits_{i=1}^{m}((\frac{i}{m})^n-(\frac{i-1}{m})^n)\times{i}\end{aligned}$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <ctime>
#include <algorithm>
using namespace std;
typedef long long ll;

inline ll read()
{
	ll a=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);ch=getchar())
		a=(a<<3)+(a<<1)+ch-'0';
	return a*f;
}

void write(ll x)
{
	if(x<0)x=-x;putchar('-');
	if(x>9)write(x/10);
	putchar((x%10)^48);
}

const int mod=1e9+7;
const int N=1e6+5;
double ans;

inline double qpow(double a,ll n)
{
	double ans=1.00;
	for(;n;n>>=1,a=a*a)
		if(n&1)ans=ans*a;
	return ans;
}

signed main()
{
	ll m=read(),n=read();
	for(int i=1;i<=m;i++)
		ans+=(qpow((double)i/m,n)-qpow((double)(i-1)/m,n))*i;
	printf("%lf\n",ans);
	return 0;
}

```


---

## 作者：傅思维666 (赞：7)


## 题解：

对于这种数学期望类的题目，思路往两个方向去：第一种思考可不可以递推地DP转移，也就是我们常说的期望DP。第二种就是直接从期望的定义进行探究，用数学方法推导一个公式然后求解。

这道题首先想到期望DP，但是没有设置出一个比较好的状态来进行转移。

那么直接考虑可不可以推导。

期望的定义：概率乘权值。

那么现在权值已知，我们只需要找每个权值的概率即可。

首先总事件数为$m^n$，很好理解。

假设扔了n次之后，扔到的最大值是k。那么在这$m^n$种情况中，符合要求的情况就是$k^n-(k-1)^n$种。

为什么呢？

扔到1-k的情况是$k^n$，扔到1-(k-1)的情况是$(k-1)^n$，容斥可得。

所以期望就是：
$$
\sum_{i=1}^m\frac{i\times (i^n-(i-1)^n)}{m^n}
$$
化简可得代码：

注意，不要用long double

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
double n,m,ans;
int main()
{
	scanf("%lf%lf",&m,&n);
	for(double i=1;i<=m;i++)
	    ans+=i*(pow(i/m,n)-pow((i-1)/m,n));
	printf("%.12lf\n",ans);
    return 0;
}
```

---

## 作者：tongyf (赞：6)

[题面](https://www.luogu.com.cn/problem/CF453A)

$upd$:2020-8-1 21:07:41 更正了最后答案式子的错误

~~麻麻我会做期望的题了~~

思路：

首先想期望$DP$

然后发现我们经常见到的期望$DP$方程形如这样：

$f(i)=\sum p(j)*f(j)$，$p(i)$为概率

但是这个题似乎不太好套用这个东西

然后我们回到期望最朴素的计算式：

$E(x)=\sum p(i)*a(i)$，$p(i)$为概率，$a(i)$为事件的值

对于$n$次投骰子，总共有$m^n$种情况，则每一种情况的概率为$\frac{1}{m^n}$

现在考虑计算每一种情况下的最大值

我们不妨手膜$m=6$，$n=2$的数据，然后得到这样的表格：

![aGnu4g.png](https://s1.ax1x.com/2020/08/01/aGnu4g.png)

其中彩色格子内为两次扔骰子之后得到的最大值

发现最大值为$i$的情况数为$i^2-(i-1)^2$

令$n=3$，相似地，也能得到最大值为$i$的情况数为$i^3-(i-1)^3$

把这个结论推广到$n$为任意值的情况，就是最大值为$i$的情况数为$i^n-(i-1)^n$

下面来证明一下：

不妨把某种扔骰子的结果设为$n$维坐标系中的坐标，设为$(a,b,c,…,z)$

显然，坐标对应的结果为坐标中这些数的最大值，而且每一维的坐标都为正整数

设当前要求的是最大值为$i$的情况数

不妨令各维坐标的上限为$i-1$

那么显然坐标系里有$(i-1)^n$个点

现在把各维的上限增加为$i$

则坐标系里有$i^n$个点

新增了$i^n-(i-1)^n$个点

显然新增的这些点不重不漏地包含了至少1维坐标为$i$的点

证明毕

那么答案就是：

$\frac{\sum^{m}_{i=1} i*(i^n-(i-1)^n)}{m^n}$

化简一下，可以得到：

$m-\sum^{m-1}_{i}(\frac{m-i}{m})^n$

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
double n,m,ans=0;
double qpow(double x,int y){
	double ans=1.00;
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return ans;
}
int main(){
	cin>>m>>n;
	ans=m;
	for(int i=1;i<=m-1;i++){
		ans-=pow((m-i)/m,n);
	}
	printf("%.12lf",ans);
	return 0;
}

```

---

## 作者：loverintime (赞：3)

设最大的数为 $i$ 的概率为 $f(i)$， 考虑这个最大数是第几个出现的，可以得到：


$$
f(i)=\frac{1\cdot i^{n-1}+(i-1)\cdot 1\cdot i^{n-2}+(i-1)^2\cdot 1\cdot i^{n-3}+...}{m^n}
$$
答案：
$$
\sum_{i=1}^mif(i)
$$
时间复杂度是： $\Theta(nm)$， 需要优化。

我们可以看出来 $f(i)$ 的分子部分是一个等比数列， 用公式化简可以得到：

$$
f(i)=\frac{i^n-(i-1)^n}{m^n}
$$


这样时间复杂度就是 $\Theta(m)$。

考虑后面得到的这个式子的简单理解方式：

在 $[1,i]$ 的范围方位内任意选 $n$ 个有 $i^n$ 种情况，在 $[1,i-1]$ 的范围方位内任意选 $n$ 个有 $(i-1)^n$ 种情况， 相减就是使得 $f(i)$ 成立的总方案数。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
double ans;
int main()
{
	scanf("%d%d",&m,&n);
	for(int i=1; i<=m; i++) ans+=1.0*i*(pow(1.0*i/m,1.0*n)-pow(1.0*(i-1)/m,1.0*n));
	printf("%.5f",ans);
	return 0;
}



---

## 作者：摸鱼酱 (赞：1)

假设扔到m面的概率均为$\frac{1}{m}$，扔n次就会有$m^n$种情况，每种情况出现概率均等，需要求每一轮扔到的最大值乘上$\frac{1}{m^n}$，但显然是不能枚举所有情况的。

正难则反，那么我们考虑每轮最大值的情况。

先假设每轮的最大值都是$m$，然后减去实际最大值小于$m$的情况。举个例子，考虑$n$次都只扔出$[1,m-1]$的概率，显然是$(\frac{m-1}{m})^n$，对应需要减去的权值是1。同理，$n$次都只扔出$[1,m-i],i\le m-1$对答案的贡献就是$-(\frac{m-i}{m})^n$，i从1到m-1枚举，但是要考虑i时的情况都被i-1时的包括，所以权值省去即可，原因可以自行举例理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	double res=m;
	for(int i=1;i<m;i++){
		res-=pow((m-i*1.0)/m,n);
	}
	printf("%.8lf",res);
	return 0;
}
```

---

## 作者：Froranzen (赞：0)

很显然有：
$$ \mathbb{E} = \sum_{i=1}^{m} p_i $$
$p_i$ 表示经过 $n$ 轮后最大值大于等于 $i$ 的概率。

又有 
$$ p_i = 1 - (\frac{i-1}{m})^n $$

即 $1$ 减去得到点数都小于 $i$ 的概率。  
那么这道题就做完了。

```cpp
int main () {
    io >> m >> n;
    for(double i = 0; i <= m-1; i += 1.0) {
        ans = ans + (1.0 - pow(i / m, n));
    }
    io << ans;
}
```

---

## 作者：RockyYue (赞：0)

# 解题思路

水一发题解，辛苦管理大大审核啦~

由结论 $[1,x]$ 共有 $x^n$ 种方案可知：

若我们取的 $n$ 次中最大值为 $x$，共有 $\frac{x^n-(x-1)^n}{m^n}$ 种,

则总方案数为：

$\sum_{i=1}^m{\frac{i^n-(i-1)^n}{m^n} \times i} = \sum_{i=1}^m \left [{\left ( \frac{i}{m} \right)^n- \left (i-1 \right )^n} \right ] \times i$	


这道~~水~~题运用了简单的概率 DP 思想，加上一点点的数学推到即可，作为蓝题还是~~很水~~不太难哒~

# 代码实现

简洁。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios :: sync_with_stdio(0);
	int n, m;
	cin >> m >> n;
	double res = 0;
	for (int i = 1; i <= m; ++i) {
		res += (pow(1.0 * i / m, n) - pow(1.0 * (i - 1) / m, n)) * i;
	}
	cout << fixed << setprecision(4) << res << '\n';
	return 0;
}
```

Good Good 贺题，Day Day Up！！


---

## 作者：Celebrimbor (赞：0)

夭寿啦 brony 入侵你谷啦！

### 题意

掷 $n$ 次 $m$ 面的骰子，求点数最大值的期望。

### 分析

记最大值为 $X$，则 $X$ 的期望 $E \left[ X\right] = \Sigma_{i=1}^{m}i\times P(X=i)$。

发现 $P(X=i)$ 不好直接算，但是 $P(X\leq i) = (\frac{i}{m})^{n}$ 是显然的。

我们又有 $P(X\leq i) = \Sigma_{j=1}^i P(X=j)$，差分一下就得到 $P(X=i)=P(X\leq i)-P(X\leq i-1) = (\frac{i}{m})^{n}-(\frac{i-1}{m})^{n}$。

那么可以 $O(mlogn)$ 计算。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 100005;
typedef long double db;
int n, m;
db ans;

db ksm(db x, int a) {
	db res = 1;
	while (a) {
		if (a&1) res *= x;
		x *= x;
		a >>= 1;
	}
	return res;
}

db P(int x) {
	return ksm((db)x/m, n)-ksm((db)(x-1)/m, n);
}

int main() {
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= m; i++) ans += i*P(i);
	printf("%Lf\n", ans);
	return 0;
}
```


---

## 作者：天梦 (赞：0)

# CF453A

[链接](https://www.luogu.com.cn/problem/CF453A)

这个题比较水。~~连我都能做出来~~

这个题我们直接考虑最大值为 $k$ 时的概率是多少。

我们设 $p_k$ 为最大值为 $k$ 时的概率。令 $f_k$ 表示 $m$ 到 $k$ 的所有值一个也没有出现的概率。

如果最大值为 $k$ ，那么说明比 $k$ 大的数一个也没有出现，而 $k$ 至少出现一次。

也就是说，$f_{k+1}$ 这个概率里包含两个部分，其中一个部分是 $f_k$ ，也就是 $k$ 没有出现，另一个部分是 $k$ 至少出现一次。也就是说 $f_{k+1}-f_{k}$ 就是 $k$ 为最大值的概率。

我们用快速幂一算就可以。

代码：

```c++
#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define N 100010
#define M number
using namespace std;

const int INF=0x3f3f3f3f;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int m,n;
dd p[N],ans;

inline dd ksm(dd a,int b){
    dd res=1.0;
    while(b){
        if(b&1) res*=a;
        a=a*a;
        b>>=1;
    }
    return res;
}

int main(){
    read(m);read(n);
    p[m+1]=1;
    for(int i=m;i>=1;i--){
        p[i]=ksm((dd)(i-1)/(dd)m,n);
        ans+=(p[i+1]-p[i])*i;
    }
    printf("%lf\n",ans);
    return 0;
}
```


---

## 作者：pigstd (赞：0)

考虑最大值为 $i$ 时的概率 $f_i$。显然答案为 $\sum\limits_{i=1}^nf_i\times i$。

但是直接考虑最大值非常麻烦，我们考虑最大值 $\le i$ 的几率 $g_i$，那么 $g_i$ 为每个数都 $\le i$ 的情况，对于一次投掷，显然答案为 $\frac{i}{m}$，那么便有 $g_i = (\frac{i}{m})^n$。

然后根据差分我们得到：$f_i=g_i-g_{i-1}$，直接计算即可。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=1e5+10;
int n,m;
double f[M],ans;

double poww(double a,int b)
{
	double res=1;
	while(b)
	{
		if (b&1)res*=a;
		a*=a;b>>=1;
	}return res;
}

int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		f[i]=poww(i*1.0/n,m);
	for (int i=1;i<=n;i++)
		ans+=(f[i]-f[i-1])*i;
	printf("%.12lf",ans);
	return 0;
}
```

---

## 作者：寒鸽儿 (赞：0)

#### 思路

记随机变量 $X$ 为骰子的点数 , 有 :   
$$
E(X) = \sum_k kP(X = k)
$$
考虑计算 $P(X = K)$ :  

根据古典概型易有 : 
$$
P(X \leqslant k) = \frac{k^n}{m^n}
$$
根据经典和差原理 :   
$$
P(X = k) = P(X \leqslant k) - P(X \leqslant k-1)
=\frac{ k^n - k^{n - 1} }{ m^n }
$$
故 :   
$$
E(X) = \sum_k kP(X = k)
=\sum_k k \frac{ k^n - k^{n - 1} }{ m^n }
$$

#### 事项

1. 注意精度问题

$m^n$ 显然会爆掉 `double` , 考虑把分母并到分子中 : 
$$
E(x) = \sum_k k \frac{ k^n - (k - 1)^n}{ m^n }
= \sum_k k((\frac{k}{m})^n - ((\frac{k-1}{m})^n)
$$

2. 不要用 `int` 除 `int` : 

    `ans += k * (pow(k / m, n) - pow((k - 1) / m, n))`  $\times$

    `ans += k * (pow((double)k / m, n) - pow((double)(k - 1) / m, n))`  $\sqrt{}$

#### code

```cpp
#include <bits/stdc++.h>

int main() {
	cout.setf(ios::fixed);
	cout.precision(13);
	int m, n;
	double ans = 0, mn = 0;
	cin >> m >> n;
	for(int k = 1; k <= m; ++k)
		ans += k * (pow((double)k / m, n) - pow((double)(k - 1) / m, n));
	cout << ans << endl;
	return 0;
}
```



---

## 作者：Azazеl (赞：0)

具体分析掷出最大值的可能：  
当掷出的数字在 $[1,k]$ 时，丢 $n$ 次有 $k^n$ 种可能；  
当掷出的数字在 $[1,k-1]$ 时，丢 $n$ 次有 $(k-1)^n$ 种可能；  
那么就有 $k^n-(k-1)^n$ 种可能掷出的点数有 $k$ ，此时最大值即为 $k$ 。  
而总共 $m^n$ 种可能。  
得到有 $\dfrac{i^n-(i-1)^n}{m^n}$ 的概率最大值为 $i$。  
所以当最大值为 $i$ 时，对期望的贡献为 $\dfrac{i\times(i^n-(i-1)^n)}{m^n}$ ，其中 $i$ 能取得的最大值为 $m$;  
综上，本题答案就是  

$\sum^{m}_{i=1} \dfrac{i\times[i^n-(i-1)^n]}{m^n}=\sum^{m}_{i=1} i\times [(\dfrac{i}{m})^n- (\dfrac{i-1}{m})^n]$  

注意最后的化简，否则会因为精度问题 WA 掉。   

$$\mathcal{CODE}$$  
```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
int main() {
	double n,m;
	scanf("%lf %lf",&m,&n);
	double ans=0;
	for(double i=1;i<=m;i++) ans+=i*(pow(i/m,n)-pow((i-1)/m,n));
	printf("%.12lf",ans);
	return 0;
}
```

---

