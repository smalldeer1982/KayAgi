# [ABC034D] 食塩水

## 题目描述

有$N$ $(1≤N≤1000)$个装有食盐水的容器。容器从$1$到$N$标号。第$i$号容器有浓度为$p_i\%$ $(0≤p_i≤100)$的食盐水$w_i$ $(1≤w_i≤10^9)$克。高桥君需要选择$K$ $(1≤K≤1000)$个容器，并把选择的容器里的食盐水全部混合在一起。请你编程求出高桥君可以获得的盐水的最大浓度。

## 样例 #1

### 输入

```
3 2
100 15
300 20
200 30
```

### 输出

```
25.000000000
```

# 题解

## 作者：Karry5307 (赞：9)

### 题意

有 $n$ 瓶食盐水，第 $i$ 瓶为质量 $w_i$，浓度 $p_i\%$ 的食盐水，需要选出 $k$ 瓶食盐水混合在一起，问最大浓度。

$\texttt{Data Range:}1\leq n,k\leq 1000$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13877461.html)

二分答案。

一开始在想各种贪心，然后各种贪心都假了，但是注意到这个东西是有单调性，（如果存在一种方案混合出来的食盐水浓度大于 $p$ 那么也一定存在一种方案的浓度大于比 $p$ 小的值），所以可以二分答案变成判定性问题。

现在考虑能不能选出 $k$ 瓶食盐水混合起来浓度大于某个二分到的 $p$，也即：

$$\frac{\sum\limits_{i=1}^{k}w_ip_i}{\sum\limits_{i=1}^{k}w_i}\geq p$$

乘过去再移过来

$$\sum\limits_{i=1}^{k}w_i(p_i-p)\geq 0$$

所以说我们只需要对 $w_i(p_i-p)$ 排序然后贪心选最大的 $k$ 个即可，实现可能有一些细节需要注意。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
typedef long double db;
const ll MAXN=2e5+51;
const db eps=1e-10;
struct Node{
	ll p,w;
};
Node x[MAXN];
ll n,kk;
db l,r,mid;
db c[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
    	neg=-1;
    	ch=getchar();
	}
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll check(db mid)
{
	db c2=0;
	for(register int i=1;i<=n;i++)
	{
		c[i]=(x[i].p-mid)*x[i].w;
	}
	sort(c+1,c+n+1,greater<db>());
	for(register int i=1;i<=kk;i++)
	{
		c2+=c[i];
	}
	return c2>=0;
}
int main()
{
	n=read(),kk=read(),l=0,r=100;
	for(register int i=1;i<=n;i++)
	{
		x[i].w=read(),x[i].p=read();
	}
	while(r-l>=eps)
	{
		mid=(l+r)/2;
		check(mid)?l=mid:r=mid;
	}
	printf("%.9Lf\n",l);
}
```

---

## 作者：NinT_W (赞：3)

# ATcoder ABC034D 食盐水

## 杂项

[题目链接](https://www.luogu.com.cn/problem/AT_abc034_d)

~~挺水的么这玩应不是 感觉远远不是是紫题难度~~

[更好的阅读体验？](https://www.cnblogs.com/SitoASK/p/16829021.html)

## 题意

> 给你 $ N $ 个装食盐水的容器，每个容器对应的食盐水浓度和食盐水的质量也给出，选几个混合起来，求可得最大浓度

## 分析

题目中要求是最大浓度，通过最大向贪心，DP，二分这些方向考虑

很明显，贪心的做法我是不知道可不可行的（因为我根本没贪出来），DP 么，不会

然后就剩下二分了

我们可以发现其单调性：设一个方案的浓度 $ x $,使得 $ x> k $ ,易得到一定有一种方案可以使其浓度大于 $ y $ ( $ y\leq k $ )

所以我们可以二分浓度

check函数怎么写呢？我们考虑一个事实：每个容器中食盐的质量等于其对应的浓度乘上食盐水的质量，对于当前二分到的浓度mid，我们应该满足如下要求

$$\frac{\sum_{i=1}^{k}w_i\times p_i}{\sum_{i=1}^{k}w_i} \geq mid$$

然后移项得到这个式子

$$\sum_{i=1}^{k}w_i\times (p_i-mid) \geq 0$$

然后就可以预处理一个g，代表上面的 $ w_i\times (p_i-mid) $ ，然后按这个值从小到大排序，最后选出前k大的值求和与 $ 0 $ 比较即可

~~这题真的是紫题么qwq~~

AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

const int maxn=1010;
const double eps=1e-10;

int n,k;
struct water
{
	double p,w,g;
}w[maxn];

bool cmp(water x,water y)
{
	return x.g>y.g;
}

bool check(double x)
{
	for(int i=1;i<=n;i++) w[i].g=(w[i].p-x)*w[i].w;
	
	sort(w+1,w+n+1,cmp);
	
	double ans=0;
	
	for(int i=1;i<=k;i++)
	{
		ans+=w[i].g;
	}
	
	return ans>=0;
}

int main()
{
	cin>>n>>k;
	
	for(int i=1;i<=n;i++)
	{
		cin>>w[i].w>>w[i].p;
	}
	
	double l=0,r=100;
	
	while(r-l>=eps)
	{
		double mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	
	printf("%.9lf",l);
	
	return 0;
}
```


---

## 作者：VitrelosTia (赞：2)

01 分数规划板题，二分答案 $x$，按照题意有

$$\dfrac{\sum w_ip_i}{\sum w_i} \ge x$$

把分子乘过去，并把 $x$ 乘进 sigma

$$\sum w_ip_i \ge \sum w_ix$$

移项，并提一个公因式

$$\sum w_i(p_i - x) \ge 0$$

check 的时候把前 $k$ 大的加起来看是否满足即可。

~~没有想到没关系，这种 trick 基本只能见过才会。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1005;
const double eps = 1e-6;
int n, k; double p[N], w[N];

double a[N];
bool check(double x) {
	for (int i = 1; i <= n; i++) a[i] = w[i] * (p[i] - x);
	sort(a + 1, a + n + 1, [](double x, double y) { return x > y; });
	double s = 0;
	for (int i = 1; i <= k; i++) s += a[i];
	return s >= 0;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> w[i] >> p[i];
	double l = 0, r = 100;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf ("%.6lf", l);
	return 0;
}
```

---

## 作者：2huk (赞：2)

> 有 $n$ 杯盐水，第 $i$ 杯盐水的浓度为 $p_i \%$，质量为 $w_i$。你需要选择 $k$ 杯盐水，使得它们混合后的浓度最大。

假如说我们需要选的盐水第 $i_1, i_2, \dots, i_k$ 杯，那么它的浓度是多少呢？

~~由幼儿园知识可得~~浓度为盐的总质量比盐水的总质量，显然也就是 $\dfrac {\sum_{j=1}^k w_{i_j} \times p_{i_j} \%}{\sum_{j = 1}^k w_{i_j}}$。

回到问题。我们可以二分这个答案 $x$。然后判断这个是否满足：

- 是否存在 $(i_1, i_2, \dots, i_k)$，使得 $\dfrac {\sum_{j=1}^k w_{i_j} \times p_{i_j} \%}{\sum_{j = 1}^k w_{i_j}} \ge x$。

如果满足，那么 $x$ 就是一个可行的答案。否则不可行。然后二分找下一个 $x$ 判断即可。

问题是如何判断。

将这个条件稍微变形：

$$
\dfrac {\sum_{j=1}^k w_{i_j} \times p_{i_j} \%}{\sum_{j = 1}^k w_{i_j}} \ge x \\
\sum_{j=1}^k w_{i_j} \times p_{i_j} \% \ge x\sum_{j = 1}^k w_{i_j} \\
\sum_{j=1}^k w_{i_j} \times p_{i_j} \% - x\sum_{j = 1}^k w_{i_j} \ge 0 \\
\sum_{j = 1}^k w_{i_j}(p_{i_j} \% - x) \ge 0
$$
那么这个问题就非常好做了。我们令 $b_i = w_i(p_i\% - x)$，然后找前 $k$ 大的 $b_i$，然后看它们的和是否非负即可。

---

## 作者：残阳如血 (赞：1)

### $\textbf{Description}$

给定 $n$ 个数对 $(w_i,p_i)$，请从中选出 $k$ 个数对构成集合 $S$，最大化下面式子的值：
$$
\dfrac{\sum\limits_{i\in S}w_ip_i}{\sum\limits_{i\in S}w_i}
$$

### $\textbf{Solution}$

显然是[分数规划](https://oi-wiki.org/misc/frac-programming/)。

二分式子的值 $x$，检查下面的式子是否满足：
$$
\begin{aligned}
\dfrac{\sum\limits_{i\in S}w_ip_i}{\sum\limits_{i\in S}w_i}&\ge x\\
\sum\limits_{i\in S}w_ip_i&\ge x\sum\limits_{i\in S}w_i\\
\sum\limits_{i\in S}w_ip_i&\ge \sum\limits_{i\in S}w_ix\\
\sum\limits_{i\in S}w_i(p_i-x)&\ge 0
\end{aligned}
$$

令每个数对的权值为 $w_i(p_i-x)$，对数对从大到小排序，求出前 $k$ 个数的权值之和，最后判断其是否 $\ge 0$ 即可。

### $\textbf{Code}$

[record](https://atcoder.jp/contests/abc034/submissions/62483740)。

```cpp
#include <bits/stdc++.h>
const int N = 1e3 + 10;

struct Data {
	int w, p;
	long double val;
	
	bool operator<(Data t) const {
		return val > t.val;
	}
} a[N];

int n, k;

bool check(long double x) {	
	for (int i = 1; i <= n; ++i)
		a[i].val = a[i].w * (a[i].p - x);
	std::sort(a + 1, a + n + 1);
	long double sum = 0;
	for (int i = 1; i <= k; ++i)
		sum += a[i].val;
	return sum >= 0;
}

int main() {
	std::cin >> n >> k;
	for (int i = 1; i <= n; ++i) std::cin >> a[i].w >> a[i].p;
	
	long double l = -1, r = 101;
	for (int i = 0; i < 100000; ++i) {
		long double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	
	std::cout << std::fixed << std::setprecision(9) << l << std::endl;
	return 0;
}
```

---

## 作者：0x00AC3375 (赞：1)

## 1. 题意

有 $n$ 瓶食盐水，第 $i$ 瓶的浓度为 $p_i$，质量为 $w_i$，从中取出 $k$ 瓶，求混合后最大可能的浓度（质量分数）。

## 2. 分析

需要说明的是，本题提到的浓度从含义上存在一定的不妥。本题的浓度的准确的表述是**溶质的质量分数**（溶质质量与溶液质量的比值），以下全部使用“质量分数”。

首先是溶液（solution）混合后的溶质质量分数变化关系。如果将质量分别为 $w_1\sim w_t$，食盐质量分数分别为 $p_1\sim p_t$ 的溶液混合均匀，那么总体的质量分数是

$$P=\dfrac{\sum_{i=1}^{t} w_ip_i}{\sum_{i=1}^{t} w_i}\times 100\%$$

也即选定的这些盐水质量分数的**加权平均值**。权重的存在使得我们需要**在“提高溶质含量”和“减小溶液质量”二者之间找到一个平衡点**。因此“直接选择前 $k$ 个最浓的盐水”是最常见的错误思路。

这题我们考虑使用二分法求解。我们设目标质量分数为 $p_\text{target}$，那么对于选定的 $k$ 份盐水而言，每一份都会对这个目标值产生一定的贡献（contribute），如果这份盐水的质量分数高于目标，则贡献为正（因为加进去后一定会让质量分数提升），否则为负（加进去后就拖了后腿），而盐水的质量就是权重（很明显质量越大越有影响力）。

因此某一份盐水**对质量分数的提升的贡献**是 $w_i(p_i-p_\text{target})$，总体的贡献就是

$$\sum_{i=1}^{k}w_i(p_i-p_\text{target})$$

从贪心的角度来讲，若要让总体的质量分数尽可能提高，肯定要优先选择贡献大的。将所有的盐水**按照贡献由大到小排序**，选出贡献值前 $k$ 大的，如果总体的贡献大于或等于 $0$，意味着可以考虑进一步提升，反之则不行。

思路上和 [P1570](https://www.luogu.com.cn/problem/P1570) 非常类似。

## 3. 代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class solution {
public:
    double weight;       // 质量
    double concentration;// 质量分数
    double contribute;   // 贡献
    solution(double weight = 0, double concentration = 0) : weight(weight), concentration(concentration) { }
};

bool compare(const solution& s1, const solution& s2) { return s1.contribute > s2.contribute; } 

int n, k;
solution* containers;

inline double status_sum()
{
    double result = 0;
    for(int i = 1; i <= k; i++) result += containers[i].contribute;
    return result;
}

bool available(double target)
{
    for (int i = 1; i <= n; i++) containers[i].contribute = (containers[i].concentration - target) * containers[i].weight;
    sort(containers + 1, containers + n + 1, compare);
    return status_sum() >= 0;
}

int main()
{
    scanf("%d%d", &n, &k);
    containers = new solution[n + 10];
    for (int i = 1; i <= n; i++) scanf("%lf%lf", &containers[i].weight, &containers[i].concentration);
    double left = 0.0, right = 100.0, middle = 50.0;
    while (fabs(right - left) >= 1e-11)
    {
        middle = (left + right) * 0.5;
        if (available(middle)) left = middle;
        else right = middle;
    }
    printf("%.10lf\n", middle);
}

```

## 4. Trivia
- 常温常压（20℃，1 atm）下食盐（主要成分为 NaCl）的溶解度约为 36g/100ml。若认为 100ml 的水的质量为 100g，则常温下氯化钠溶液中氯化钠质量分数不会超过 26.5%；
- 也就是说**常温状态下，样例中出现的 30% 的盐水会发生沉淀**（~~如果这样的话也不能叫溶液了~~）。

---

## 作者：zjinze (赞：1)

#### 前置知识：分数规划

#### 思路：

二分答案，设二分值为 $mid$。考虑如何检查 $mid$ 是否合法，设 $s_i$ 为是否选第 $i$ 个容器，$s_i$ 为 $0$ 表示不选，$s_i$ 为 $1$ 表示选。显然，只要 $\frac {\sum_{i=1}^n w_i \times p_i \times s_i} {\sum_{i=1}^n w_i} \ge mid$，$mid$ 就合法。考虑化解式子，得到 $\sum _{i=1}^n w_i \times (p_i \times s_i- mid)  \ge 0 $，所以我们可以按 $\sum _{i=1}^n w_i \times (p_i - mid)$ 从大到小排序，选前 $k$ 大的，在判断前 $k$ 个的和是否大于等于 $0$ 即可。

#### code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int N=1010;
struct node{
	double p;
	double w;
}a[N];
int n,k;
const double eps=1e-10;
double c[N],l,r,mid;
bool cmp(double x,double y){
	return x>y;
}
bool check(double mid){
	for(int i=1;i<=n;i++)c[i]=a[i].w*(a[i].p-mid);
	sort(c+1,c+n+1,cmp);
	double sum=0;
	for(int i=1;i<=k;i++)sum+=c[i];
	return sum>=eps;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].w>>a[i].p;
	}
	l=0,r=1e12;
	while(r-l>=eps){
		mid=(l+r)/2.0;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.9lf\n",l);
	return 0;
}
```

---

## 作者：Leaves_xw (赞：1)

**思路：**

二分答案加贪心。

我们设 $nondu$ 代表二分后的浓度，那么可以得出下面这个式子：

$$\frac{\displaystyle\sum_{i=1}^{k}w_i\times p_i}{\displaystyle\sum_{i=1}^{k}w_i}\geq nondu$$

然后进行移项：

$$\displaystyle\sum_{i=1}^{k}w_i\times (p_i-nondu)\geq 0$$

随后我们设 $G=w_i\times(p_i-nondu)$，之后给 $G$ 进行排序，最后贪心思想选最大的 $k$ 个即可。

---

## 作者：hanzhongtlx (赞：1)

## [更好的阅读体验点这里](https://www.cnblogs.com/tlx-blog/p/12513967.html)
题目链接：[AT1807 食塩水](https://www.luogu.com.cn/problem/AT1807)     
其实是很裸的二分最大化平均值，这里讲一下思路。     
很容易发现$check$函数很难写，这就是因为找不到用单调性或是什么性质来判断，那我们构造一下不就得了？        
假设我们对于一个数$x$进行$check$,      
我们设所选的$k$个数$a_1$～$a_k$满足构成的集合为$S$，那显然只需满足
$$\dfrac{\sum\limits_{i\in S}p_i}{\sum\limits_{i\in S}w_i}\geqslant x$$           
分数很别扭，乘过去，即得：
$$\sum\limits_{i\in S}p_i\geqslant \sum\limits_{i\in S}xw_i$$  
移项，然后把求和合并起来：
$$\sum\limits_{i\in S}(p_i-xw_i)\geqslant 0$$    
维护下每个$p_i-xw_i$，从大到小排序贪心取前$k$大的即可（或后$k$小的）。 

其他的事：   
注意这里的$p_i$是浓度，我们要把它处理成溶质的质量；      
另外，最后的答案是要$×100$，因为我们是要用百分数表示答案的。    
时间复杂度显然是$O(n\log n\log eps)$(这里的$eps$指的是精度，$\log eps$即二分次数，自己估算一下即可，反正$100$准是没问题的。)   
## $Code$：
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm> 
#include<cstring>
using namespace std;
const int MAXN=1005;
const double EPS=1e-10;
int n,k;
double p[MAXN],w[MAXN];
double r=100.0,l=0.0,mid;
bool check(double x)
{
	double rt[MAXN],sum=0;
	memset(rt,0,sizeof(rt));//这里的清空是至关重要的，否则数组在函数中会任意赋值
	for(int i=1;i<=n;i++) rt[i]=p[i]-x*w[i];
	sort(rt+1,rt+n+1);
	for(int i=n;i>=n-k+1;i--) sum+=rt[i];//倒序就不用打cmp了
	return (sum-0)>EPS;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lf%lf",&w[i],&p[i]),p[i]*=w[i]/100;
   //处理溶质的质量，另外记得用double读入
	for(int i=1;i<=100;i++)//二分
	{
		mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%.9lf\n",mid*100);//转化为百分数
	return 0;
}
```


------------
$update\;:2020.3.18$式子写错了，改一下

---

## 作者：encore (赞：1)

先说吧，这题是二分答案。~~你不知道我DP做了多久QAQ。~~

一道很有意思的二分题。我们假设最终答案为$x$。显然有 $ 0 \leq x \leq 100 $。当然你可以说$x$一定大于最小的那个浓度之类，不过无所谓，反正不差那么点时限。

然而只知道二分并没有什么卵用，解决这题还需要一个贪心策略。如果你稍微做过一会儿你就知道，并不是浓度越大越好的。

设所有盐水的集合为$S$。我们假设选取了$S_{a_1}$、$S_{a_2}$、$S_{a_3}$、……$S_{a_k}$这$k$瓶。现在我们来判断这$k$瓶盐水能不能混合出浓度大于$x\%$的盐水。很显然，新的盐水的浓度为：

$\frac{w_{a_1} p_{a_1} +w_{a_2} p_{a_2} +w_{a_3} p_{a_3} +...+w_{a_k} p_{a_k}}{w_{a_1}+w_{a_2}+w_{a_3}+...+w_{a_k}}$
。

那么只要 $\frac{w_{a_1} p_{a_1} +w_{a_2} p_{a_2} +w_{a_3} p_{a_3} +...+w_{a_k} p_{a_k}}{w_{a_1}+w_{a_2}+w_{a_3}+...+w_{a_k}} \geq x$就说明当前选取的$x$可行。

然后我们将上面的式子变形：

$w_{a_1} p_{a_1} +w_{a_2} p_{a_2} +w_{a_3} p_{a_3} +...+w_{a_k} p_{a_k} - x\times (w_{a_1} +w_{a_2}+w_{a_3}+...+w_{a_k}) \geq 0$

然后……

$w_{a_1} (p_{a_1}-x) +w_{a_2} (p_{a_2}-x) +w_{a_3} (p_{a_3}-x) +...+w_{a_k} (p_{a_k}-x) \geq 0$

好像没什么啊？但是我们可以发现，当$x$确定的时候，对于所有的$S_i$，它的$w_i (p_i - x)$ 都是确定的。选取$S_i$对应的$w_i (p_i - x)$一定是越大越好啦。所以在我们二分答案$x$的时候，只要处理出所有的$w_i (p_i - x)$，再按照$w_i (p_i - x)$的值从大到小选取盐水，就可以得到对于当前的$x$最优解。如果这个解符合，说明我们的$x$小于等于答案，如果不符合则相反。

基本差不多了，不过要注意精度之类的细节啊。下面贴AC代码：

````cpp
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

typedef long double ld;

const int maxn = 1001, maxk = 1001;
int n, k;
ld p[maxn], w[maxn];

inline ld check(ld val) {
	priority_queue<ld> v;//用来排序，vector加sort也一样的
	for (register int i = 1; i <= n; ++ i) {
		v.push(w[i] * (p[i] - val));
	}
	ld sum = 0;
	for (register int i = 1; i <= k; ++ i) {
		sum += v.top();
		v.pop();
	}
	return sum;
}

int main(void) {
	cin >> n >> k;
	for (register int i = 1; i <= n; ++ i)
	  cin >> w[i] >> p[i];
	ld l = 0, r = 100, mid = 1, mid_old = 0;
	while (abs(mid - mid_old) >= 1e-10) { //自创沙雕二分
		mid_old = mid;
		mid = 0.5 * (l + r);
		ld tmp = check(mid);
		if (tmp > 0) l = mid;
		else r = mid;
	}
	cout.setf(ios::fixed);
	cout << setprecision(9) << mid << endl; //保留九位小数，
	cout.unsetf(ios::fixed);  //头文件<iomanip>
	return 0;
}
````

最后给你们看看我的WA提交记录。。。

[https://www.luogu.org/recordnew/show/16347998](https://www.luogu.org/recordnew/show/16347998)

[https://www.luogu.org/recordnew/show/16348654](https://www.luogu.org/recordnew/show/16348654)

---

## 作者：jinhangdong (赞：0)

考虑二分，要求：$\frac{\displaystyle\sum_{i=1}^{k}w_ip_i}{\displaystyle\sum_{i=1}^{k}w_i}≥mid$。

$\displaystyle\sum_{i=1}^{k}w_ip_i≥mid\times\displaystyle\sum_{i=1}^{k}w_i$

$\displaystyle\sum_{i=1}^{k}w_i(p_i-mid)≥0$

我们对 $w_i(p_i-mid)$ 从大到小排序,然后选 $k$ 个，只要总和大于 $0$ 那么满足条件左端点右移。
```
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
const double eps=1e-12;
double w[N],p[N],a[N],l,r=100;
int n,k;
bool cmp(double x,double y)
{
	return x>y;
}
bool check(double x)
{
	double sum=0;
	for(int i=1;i<=n;++i) a[i]=w[i]*(p[i]-x);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=k;++i) sum+=a[i];
	if(sum>=0) return 1;
	return 0;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;++i) cin>>w[i]>>p[i];
	while(r-l>eps)
	{
		double mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%.9lf\n",l);
	return 0;
}
```

---

## 作者：xz001 (赞：0)

- ~~核废水~~
- 首先知道，合成的盐水浓度为（这里的 $p_i$ 和 $w_i$ 都是假定选出的）：
$$
\frac{\sum_{i=1}^{k}p_iw_i}{\sum_{i=1}^{k}w_i}
$$
- 我们二分想要达成的浓度 $x$，我们推一下式子：
$$
x\le \frac{\sum_{i=1}^{k}p_iw_i}{\sum_{i=1}^{k}w_i}
$$
$$
x\times {\sum_{i=1}^{k}w_i}\le {\sum_{i=1}^{k}p_iw_i}
$$
$$
0\le {\sum_{i=1}^{k}p_iw_i}- {\sum_{i=1}^{k}x\times w_i}
$$
$$
0\le \sum_{i=1}^{k}(p_i-x)\times w_i
$$
- 好了，这样我们求每个数字的 $(p_i-x)\times w_i$，排序求前 $k$ 大即可。
- 代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5;

int n, k, w[N], p[N];

bool check (double mid) {
	vector <double> v;
	for (int i = 1; i <= n; ++ i) v.push_back((p[i] - mid) * w[i]);
	sort(v.begin(), v.end());
	reverse(v.begin(), v.end());
	double ans = 0;
	for (int i = 0; i < k; ++ i) ans += v[i];
	return ans >= 0;
}

signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; ++ i) scanf("%lld%lld", w + i, p + i);
	double l = 0, r = 100, ans;
	while (r - l >= 0.00000001) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			ans = mid;
			l = mid;
		} else {
			r = mid;
		}
	}
	printf("%.9lf\n", ans);
	return 0;
}
```

---

## 作者：_AyachiNene (赞：0)

# 思路：
看到这道题，首先想到是贪心。根据小学数学知识，很容易推出计算最终答案的式子:

$$\dfrac{\sum\limits_{i=1}^kW_iP_i}{\sum\limits_{i=1}^kW_i}$$

其中 $W$ 和 $P$ 为选出来的 $k$ 项。

但是做了之后发现没法贪（至少我不知道怎么贪）。于是考虑换种思路。很好发现，这个东西有单调性，如果能得到更大的答案，更小的答案也能得到。于是问题转化为了给你一个浓度判断是否能配的出来。

设二分的答案为 $x$，那么需要满足：

$$x\leq\dfrac{\sum\limits_{i=1}^kW_iP_i}{\sum\limits_{i=1}^kW_i}$$

移项再化简得：

$$0\leq\sum\limits_{i=1}^kW_i(P_i-x)$$

把式子推出来就很好做了，只需要对于每一次二分的答案算出每一项的贡献，在取 $k$ 个最大的就行了。
# Code：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int n,k;
db w[114514],p[114514];
db val[114514];
db ans;
bool cmp(db x,db y)
{
	return x>y;
}
int check(db x)
{
	for(int i=1;i<=n;i++)
		val[i]=1.0*(p[i]-x)*w[i];
	sort(val+1,val+n+1,cmp);
	db res=0;
	for(int i=1;i<=k;i++)
		res+=val[i];
	return res>=0;
}
signed main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++)
		w[i]=read(),p[i]=read();
	db l=0,r=100;
	for(int i=1;i<=100;i++)
	{
		db mid=(l+r)/2;
		if(check(mid))
			l=mid,ans=mid;
		else
			r=mid;
	}
	printf("%.10lf",ans);
}
```


---

## 作者：Erica_N_Contina (赞：0)

# [ABC034D] 食塩水


## 思路

一个区别于二分的其他思路。



首先我们考虑贪心——优先选择浓度较大的容器。但很显然，这种贪心是不正确的，从样例中我们就知道。

```Plain Text
3 2
100 15
300 20
200 30
```


贪心会让我们优先选择浓度为 $20$ 和 $30$ 的容器，这样计算出来的浓度为 $24$，而不是答案 $25$。答案 $25$ 是选择浓度为 $15$ 和 $30$ 的容器计算出来的。



首先我们找到所有容器中浓度最高的一个，我们考虑把其他 $K-1$ 个容器加入到这个容器中来。

选择的问题就是，我们怎么样选择才能让最终的浓度最高。

假设浓度最高的容器质量为 $w_1$，浓度为 $p_1$，现在我们有容器 $i$ 质量为 $w_i$，浓度为 $p_i$。我们把容器 $i$ 加入到容器 $1$ 中——我们可以得到质量为 $w_1+w_i$，浓度为 $\frac{w_1\times p_1+w_i\times p_i}{w_1+w_i}$。我们考虑选择怎样的 $i$ 才能人最终浓度最大化。

首先，对于浓度相同的，我们优先选择质量小的。

其次，对于浓度不同的，我们假设为 $p_i$ 和 $p_j$，那么最终的浓度为 $a=\frac{w_1\times p_1+w_i\times p_i}{w_1+w_i}$ 和 $b=\frac{w_1\times p_1+w_j\times p_j}{w_1+w_j}$。

我们通分，得到。

$a=\frac{w_1^2\times p_1+w_iw_1\times p_i+w_1w_j\times p_1+w_iw_j\times p_i}{(w_1+w_i)\times (w_1+w_j)}$

$b=\frac{w_1^2\times p_1+w_jw_1\times p_j+w_1w_i\times p_1+w_jw_i\times p_j}{(w_1+w_j)\times (w_1+w_i)}$

消去分母和同项目。

$a'=w_iw_1\times p_i+w_1w_j\times p_1+w_iw_j\times p_i$

$b'=w_jw_1\times p_j+w_1w_i\times p_1+w_iw_j\times p_j$

所以在不断往容器 $1$ 中加入其他容器时，我们每次继续一次 sort 排序，以 $a'>b'$ 的 cmp 顺序排序，然后我们选择最前面的那个容器，把它加入到容器 $1$ 中。

时间复杂度为 $O(n^2\log n)$ 可过。

## 代码

```C++
/*////////ACACACACACACAC///////////
	   . Coding by Ntsc .
	   . ToFind Chargcy .
	   . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define ll long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=2e5+5;
const int M=1e3;
const int MOD=903250223;
const int INF=1e9;
//变量
int n,m,b[N],c,ton[N],y[N],w1,t,k,sum,sp,mx,res,tmp,cnt,web[M][M];
double p1;

struct node{
	int m,p;
} a[N];

bool cmp(node a,node b){
	return a.p>b.p;
}

bool cmp2(node a,node b){
	if((!a.m)||(!b.m))return a.m>b.m;
	return a.m*w1*a.p+w1*b.m*p1+a.m*b.m*a.p>b.m*w1*b.p+w1*a.m*p1+a.m*b.m*b.p;
}

signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].m>>a[i].p;
	}
	sort(a+1,a+n+1,cmp);

	w1=a[1].m,p1=a[1].p;
	a[1].m=a[1].p=0;
	for(int i=1;i<k;i++){
		sort(a+1,a+n+1,cmp2);
		// for(int j=1;j<=n;j++)cout<<a[j].m<<' ';
		// cout<<endl;

		p1=1.00*w1*p1+a[1].m*a[1].p;
		p1/=1.00*(w1+a[1].m);
		w1+=a[1].m;
		a[1].p=a[1].m=0;
	}

	printf("%.8lf\n",p1);
#ifdef PAUSE_ON_EXIT
	system("pause");
#endif
	return 0;
}
```






---

