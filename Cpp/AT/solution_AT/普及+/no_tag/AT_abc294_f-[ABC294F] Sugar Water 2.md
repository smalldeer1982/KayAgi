# [ABC294F] Sugar Water 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc294/tasks/abc294_f

高橋君は $ N $ 本の砂糖水を、青木君は $ M $ 本の砂糖水を持っています。  
 高橋君の持っている $ i $ 番目の砂糖水は砂糖 $ A_i $ グラムと水 $ B_i $ グラムからなります。  
 青木君の持っている $ i $ 番目の砂糖水は砂糖 $ C_i $ グラムと水 $ D_i $ グラムからなります。  
 2 人の持つ砂糖水をそれぞれ 1 本ずつ選んで混ぜる方法は $ NM $ 通りあります。そのような方法でできる砂糖水の中で、濃度が高い方から $ K $ 番目の砂糖水の濃度が何 $ \% $ であるかを求めてください。  
 ここで、砂糖 $ x $ グラムと水 $ y $ グラムからなる砂糖水の濃度は $ \dfrac{100x}{x+y}\ \% $ です。また、砂糖が溶け残ることは考えないものとします。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ M\ \leq\ 5\ \times\ 10^4 $
- $ 1\ \leq\ K\ \leq\ N\ \times\ M $
- $ 1\ \leq\ A_i,\ B_i,\ C_i,\ D_i\ \leq\ 10^5 $
- 入力される値はすべて整数
 
### Sample Explanation 1

以下では高橋君が持っている $ i $ 番目の砂糖水と青木君が持っている $ j $ 番目の砂糖水を混ぜてできる砂糖水を $ (i,\ j) $ と表します。 あり得る砂糖水の混ぜ方とその濃度を列挙すると以下のようになります。 - $ (1,\ 1) $ : $ 100\ \times\ \frac{1\ +\ 1}{(1\ +\ 1)\ +\ (2\ +\ 4)}\ =\ 25\ \% $ - $ (2,\ 1) $ : $ 100\ \times\ \frac{1\ +\ 4}{(4\ +\ 1)\ +\ (1\ +\ 4)}\ =\ 50\ \% $ - $ (3,\ 1) $ : $ 100\ \times\ \frac{1\ +\ 1}{(1\ +\ 1)\ +\ (4\ +\ 4)}\ =\ 20\ \% $ この中で濃度が高い方から $ 1 $ 番目の砂糖水は $ (2,\ 1) $ で、濃度は $ 50\ \% $ です。

## 样例 #1

### 输入

```
3 1 1
1 2
4 1
1 4
1 4```

### 输出

```
50.000000000000000```

## 样例 #2

### 输入

```
2 2 2
6 4
10 1
5 8
9 6```

### 输出

```
62.500000000000000```

## 样例 #3

### 输入

```
4 5 10
5 4
1 6
7 4
9 8
2 2
5 6
6 7
5 3
8 1```

### 输出

```
54.166666666666664```

# 题解

## 作者：泥土笨笨 (赞：16)

# 题意简述

高桥君有 $n$ 瓶糖水，编号为 $1$ 到 $n$，其中第 $i$ 瓶糖水中含有 $a_i$ 克糖和 $b_i$ 克水。青木君有 $m$ 瓶糖水，编号为 $1$ 到 $m$，其中第 $i$ 瓶糖水中含有 $c_i$ 克糖和 $d_i$ 克水。

现在高桥君随意选出一瓶水，青木君也随意选出一瓶水，混合在一起，这样总共有 $n \times m$ 种不同的混合方式。所有混合方式中，按照浓度从高到低排序，问排第 $k$ 的混合方式的浓度是多少。浓度计算方式为，如果一瓶水中有 $x$ 克糖，有 $y$ 克水，浓度为 $\frac{100 \times x}{x+y}$。

# 解题思路

本题数据范围 $n,m \le 5 \times 10^4$，总的方案太多了，如果全枚举出来，再排序一遍，复杂度是 $n \times m \log(n \times m) $，这样肯定要超时。

题目中问我们浓度第 $k$ 大的方案的浓度，不妨设为 $cc$，那么我们可以二分这个浓度 $cc$，然后计算所有混合液当中，浓度比 $cc$ 大的方案数 $cnt$。如果发现 $cnt \lt k$，说明我们选择的 $cc$ 是可行的，继续去小的那边二分。否则说明我们选择的 $cc$ 太小了，它肯定不是目标浓度，就去大的那边二分。

下面问题就是，当给定浓度的时候，如果求出浓度比它大的方案数呢？

首先对于青木君的 $m$ 瓶糖水，假设每瓶水中糖有 $x$ 克，水有 $y$ 克。我们假设要把它调整为浓度为 $cc$ 的，则在水不变的情况下，糖需要 $cc \times y / (1 - cc)$ 克，而现有的糖为 $x$ 克，那么这瓶水当中多余的糖为 $x - cc \times y / (1 - cc)$ 克。我们可以算出每一瓶里面多余的糖，然后按照这个数字对青木君的 $m$ 瓶糖水排序。请注意，这里多余的糖可能为负数，表示的是缺少多少糖。负数也没关系的，正常放到数组里排序。

接下来枚举高桥君的 $n$ 瓶糖水，对于当前这一瓶，还是用一样的方式，我们可以算出这一瓶糖水中，多余的糖是多少，然后取个负，变成缺多少糖，记为 $less$。则我们可以到刚才排好序的数组里面二分查找，找到有多少个数字是大于 $less$ 的，那么这些都可以和当前这瓶组合出浓度超过 $cc$ 的混合液。

这样排序复杂度 $O(m\log(m))$，枚举和二分查找的复杂度 $O(n\log(m))$，外面再套 $100$ 层二分浓度 $cc$ 就行了。题目中要求精度是 $10^{-9}$，我们二分 $100$ 次，精度是 $2^{-100}$，肯定够了。这样总的复杂度是 $O(100 \times ((m+n)\log(m)))$，可以通过本题。

# 代码示例
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;

ll n, m, k;
double a[MAXN], b[MAXN], c[MAXN], d[MAXN], more[MAXN];

//计算浓度大于mid的方案数
ll check(double cc) {
    //浓度是cc,对于m个瓶子，水是y，则糖需要cc * y / (1 - cc)
    //多余的糖是x - cc * y / (1 - cc)，把每个瓶子中多余的糖放到more数组里
    for (int i = 0; i < m; ++i) {
        more[i] = c[i] - cc * d[i] / (1 - cc);
    }
    //按照多余的糖排序
    sort(more, more + m);
    ll cnt = 0;
    //遍历n个瓶子，对于每个瓶子，计算它缺少的糖
    for (int i = 0; i < n; ++i) {
        double less = -(a[i] - cc * b[i] / (1 - cc));
        //二分查找，找到所有多余的糖比less多的个数
        ll t = more + m - upper_bound(more, more + m, less);
        cnt += t;
    }
    return cnt;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> c[i] >> d[i];
    }
    //二分排名第k的浓度
    double low = 0, high = 1, mid;
    for (int i = 0; i < 100; ++i) {
        mid = (low + high) / 2;
        if (check(mid) < k) {
            high = mid;
        } else {
            low = mid;
        }
    }
    printf("%.15lf\n", high*100);
    return 0;
}
```


---

## 作者：DaydreamWarrior (赞：3)

[不一定更好的阅读体验](https://rainlycoris.github.io/#/post/18)

## 题意

高橋君有 $N$ 瓶糖水，青木君有 $M$ 瓶糖水。

高橋君的第 $i$ 瓶糖水有 $A_i$ 份糖 $B_i$ 份水。

青木君的第 $i$ 瓶糖水有 $C_i$ 份糖 $D_i$ 份水。

将两人的糖水各选一瓶混合有 $NM$ 种可能，求其中浓度第 $k$ 大的糖水浓度是多少。

有 $x$ 份糖和 $y$ 份水的糖水浓度是 $\dfrac{100x}{x+y}\%$。

## 分析

二分浓度 $c$ 后，我们只需要得到混合后浓度大于等于 $c$ 的个数。

有 $a$ 份糖 $b$ 份水的糖水，再加 $(a+b)c-a$ 份糖就能变成浓度 $c$，也可能是减掉糖。

令 $(a+b)c-a$ 为 $s$，$s$ 的正负可以判断浓度和 $c$ 的关系。

那么两瓶糖水 $x,y$ 混合后，判断 $s_x+s_y$ 的正负即可。

因为 $(A_x+B_x+C_y+D_y)c-A_x-C_y=(A_x+B_x)c-A_x+(C_y+D_y)c-C_y=s_x+s_y$，所以 $s$ 是可加的。

二分浓度，将青木君糖水的 $s$ 排序，枚举高橋君的糖水，二分计算混合后浓度大于等于 $c$ 的个数。

复杂度 $O(n \log n \log v)$。

## 代码
```cpp
const int N = 50005;
const double eps = 1e-12;
vector<pair<int,int>> a,b;
int n,m,K;

inline int check(double c){
    vector<double> w1,w2;
    for(auto [x,y]:a)
        w1.push_back(x-(x+y)*c);
    for(auto [x,y]:b)
        w2.push_back(x-(x+y)*c);
    sort(w2.begin(),w2.end());
    int ans = 0;
    for(auto c:w1)
        ans += lower_bound(w2.begin(),w2.end(),-c+eps)-w2.begin();
    return ans;
}

signed main(){
    cin >> n >> m >> K;
    a.resize(n);
    b.resize(m);
    for(auto &[x,y]:a)
        cin >> x >> y;
    for(auto &[x,y]:b)
        cin >> x >> y;
    double l = 0,r = 1;
    K = n*m-K+1;
    while(abs(r-l)>eps){
        double mid = (l+r)/2;
        if(check(mid)>=K)
            r = mid;
        else
            l = mid;
    }
    printf("%.10lf",r*100);
    return 0;
}
```

---

## 作者：2huk (赞：2)

## 题意

有 $2$ 排糖和水。

第 $1$ 排有 $N$ 瓶糖和 $N$ 瓶水。糖分别有 $A_i$ 克，水分别有 $B_i$ 克。

第 $2$ 排有 $M$ 瓶糖和 $M$ 瓶水，糖分别有 $C_i$ 克，水分别有 $D_i$ 克。

若要从第 $1$ 排糖水中找到 $A_i$ 克糖和 $B_i$ 克水，第 $2$ 排中找到 $C_i$ 克糖和 $D_i$ 克水进行混合，问排名第 $K$ 甜的糖水的含糖量是多少。

## 算法

二分查找 + 二分答案

## 实现

### 主函数

令 $x$ 为糖的质量，$y$ 为水的质量，$t$ 为含糖量。

首先二分答案 $t$。

如果知道比 大于 $t$ 的 和 小于 $t$ 的 和 等于 $t$ 的 各有多少种方案，那么就可以知道 $t$ 的排名，然后根据 $t$ 的排名调整 $l$ 和 $r$ 的范围。

```cpp
double l = 0, r = 1;

while(r - l > 1e-14){
	double mid = (l + r) / 2;
	int x = check(mid);	// 如果以浓度 mid 为标准，浓度大于等于 mid 的有多少种。 
	if(x >= k){
		ans = mid;
		l = mid;	// 试着寻找更大值 
	}
	else{
		r = mid;	// 寻找更小值 
	}
}
```

### check(t) 函数

`check(t)` 函数要求的是如果以浓度 $t$ 为标准，浓度大于等于 $t$ 的有多少种。

因为 $t = \dfrac{x}{x+y}$，所以如果知道 $t$ 和 $y$，就可以知道 $x = \dfrac{t}{1-t} \times y$。

```cpp
int check(double t){	// 如果以浓度 t 为标准，浓度大于等于 t 的有多少种。
	int res = 0;
	double r = t / (1 - t);
	
	for(int i=1; i<=m; i++){
		// v[i] 存储的是第 2 排还需要多少糖才能达到 t 浓度 
		v[i] = c[i] - d[i] * r;
//相当于v[i] = c[i] - t / (1 - t) * d[i]; 
	}
	
	sort(v+1, v+m+1);
	
	for(int i=1; i<=n; i++){
		double w = a[i] - b[i] * r;
//		相当于 w = a[i] - t / (1 - t) * b[i]; 
		res += find(-w);		// 二分找 v 数组种大于等于 -w 的有多少项 
	}
	
	return res;
}
```

### find(x) 函数

`find(x)` 函数是寻找 $v$ 数组中大于等于 $x$ 的有多少项。

首先二分查找第 $1$ 个大于等于 $x$ 的值在第几个位置，设为 $res$ 。

有了 $res$ 后，不难发现小于 $x$ 的有 $x-1$ 项，那么大于等于 $x$ 的就有 $m - (res - 1)$ 项。

```cpp
int find(double x){		// 寻找 v 数组中大于等于 x 的有多少项 
	int l = 1, r = m;
/*
	如果最终发现没有大于等于 x 的值，那么 res 如果一开始设为 0 就会得到
	返回值为 m - 0 + 1的情况。因此将 res 的初始值设为 m + 1，那么最终如
	果没有寻找到将会返回 m - (m + 1) + 1，也就是 0，这样才正确。 
*/ 
	int res = m + 1;
	while(l <= r){
		int mid = (l + r) / 2;
		double pivot = v[mid];
		if(pivot >= x){
			res = mid;
			r = mid - 1;
		}
		else{
			l = mid + 1;
		}
	}
	return m - res + 1;
//	return m -(res - 1);
}
```

## 完整代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 5e4 + 10;

int n, m, k, a[N], b[N], c[N], d[N]; 

double ans, l = 0, r = 1, v[N];

int find(double x){		// 寻找 v 数组中大于等于 x 的有多少项 
	int l = 1, r = m;
/*
	如果最终发现没有大于等于 x 的值，那么 res 如果一开始设为 0 就会得到
	返回值为 m - 0 + 1的情况。因此将 res 的初始值设为 m + 1，那么最终如
	果没有寻找到将会返回 m - (m + 1) + 1，也就是 0，这样才正确。 
*/ 
	int res = m + 1;
	while(l <= r){
		int mid = (l + r) / 2;
		double pivot = v[mid];
		if(pivot >= x){
			res = mid;
			r = mid - 1;
		}
		else{
			l = mid + 1;
		}
	}
	return m - res + 1;
//	return m -(res - 1);
}

int check(double t){	// 如果以浓度 t 为标准，浓度大于等于 t 的有多少种。
	int res = 0;
	double r = t / (1 - t);
	
	for(int i=1; i<=m; i++){
		// v[i] 存储的是第 2 排还需要多少糖才能达到 t 浓度 
		v[i] = c[i] - d[i] * r;
//相当于v[i] = c[i] - t / (1 - t) * d[i]; 
	}
	
	sort(v+1, v+m+1);
	
	for(int i=1; i<=n; i++){
		double w = a[i] - b[i] * r;
//		相当于 w = a[i] - t / (1 - t) * b[i]; 
		res += find(-w);		// 二分找 v 数组种大于等于 -w 的有多少项 
	}
	
	return res;
}

signed main(){
	// 读入 
	scanf("%lld %lld %lld", &n, &m, &k);
	
	for(int i=1; i<=n; i++){
		scanf("%lld %lld", a+i, b+i);
	}
	
	for(int i=1; i<=m; i++){
		scanf("%lld %lld", c+i, d+i); 
	}
	
	while(r - l > 1e-14){
		double mid = (l + r) / 2;
		int x = check(mid);	// 如果以浓度 mid 为标准，浓度大于等于 mid 的有多少种。 
		if(x >= k){
			ans = mid;
			l = mid;	// 试着寻找更大值 
		}
		else{
			r = mid;	// 寻找更小值 
		}
	}
	
	// 输出 
	printf("%.10lf", ans * 100);
	return 0;
}
```


---

## 作者：SlyCharlotte (赞：2)

[或许更好的阅读体验？](https://zhuanlan.zhihu.com/p/615414755)

### 题意描述

给你两排糖水，每个糖水有一些质量的糖与一些一些质量的水组成。

从两排中各取一个糖水混合，得糖浓度 $\frac{x_i + x_j} {x_i + y _ i + x _ j + y _j}$。

在所有混合方案中，求第 $k$ 大浓度。

### 简要分析

考虑二分答案。

对于二分的每个浓度 $C$ 我们要求出他的排名。

求排名的过程为就是要比较 $\frac{x_i + x_j}{x_i + y_i+ x_j + y_j}$ 与 $C$ 的大小。

即要满足:
$$
\frac{x_i + x_j}{x_i + y_i+ x_j + y_j} > C
$$
才会增加 $C$ 的排名。

发现这里的除法是不好的，于是我们将除法去掉。

于是要满足: 
$$
{x_i + x_j} > C \times (x_i + y_i+ x_j + y_j)
$$


这里把 $i,j$ 分开来就变成：
$$
(1 - C) \times x_i - C \times y_i >(C - 1)\times x_j + C \times y_j
$$
另 $T_{ai} = (1 - C) \times x_i - C \times y_i$，$T_{bj} = (C - 1)\times x_j + C \times y_j$。
$$
T_{ai} > T_{bi}
$$
也就是说满足原式 $i,j$ 的数量就转化成求出上式 $i,j$ 的数量。

将 $T_{ai},T_{bi}$ 排序后使用双指针或二分求解（这里类比本场 C 题）。

时间复杂度 $O(n \log n)$。

### 代码实现

```cpp
bool check(ldb C) {
    vector<ldb> aa(n), bb(m);
    for (ll i = 0; i < n; i++)aa[i] = (1.0 - C) * a[i][0] - C * a[i][1];
    for (ll j = 0; j < m; j++)bb[j] = (C - 1.0) * b[j][0] + C * b[j][1];
    sort(aa.begin(), aa.end()), sort(bb.begin(), bb.end());
    ll cur = 0, cnt = 0;
    for (ll i = 0; i < n; ++i) {
        while (cur < m && bb[cur] < aa[i])
            ++cur;
        cnt += cur;
    }
    return cnt <= k;
}

signed main() {
//    freopen("code.in", "r", stdin);
//    freopen("code.out", "w", stdout);
    ccin >> n >> m >> k;
    for (ll i = 0; i < n; i++)ccin >> a[i][0] >> a[i][1];
    for (ll i = 0; i < m; i++)ccin >> b[i][0] >> b[i][1];
    ldb l = 0, r = 1;
    k--;
    while (r - l > EPS) {
        ldb mid = (l + r) / 2.0;
        if (check(mid))
            r = mid;
        else l = mid;
    }
    printf("%.10lf\n", r * 100);
    return 0;
}
```

## 

---

## 作者：JuRuoOIer (赞：2)

# 题解 [ABC294F] Sugar Water 2

### Part1 题意

[传送门（洛谷）](https://www.luogu.com.cn/problem/AT_abc294_f)

[传送门（原题）](https://atcoder.jp/contests/abc294/tasks/abc294_f)

- 给定 $n+m$ 杯糖水，前 $n$ 杯中第 $i$ 杯有 $a_i$ 克水和 $b_i$ 克糖，后 $m$ 杯中第 $i$ 杯有 $c_i$ 克水和 $d_i$ 克糖。

- 求从前 $n$ 杯和后 $m$ 杯糖水中各任取一杯混合起来，混合后的糖水浓度第 $k$ 大的混合方法浓度是多少？

- $1 \le n,m \le 5 \times 10^4$，$1 \le k \le nm$

### Part2 思路

~~奇怪的~~二分题。

设浓度为 $x$，则 $\dfrac{\text{糖}}{\text{糖水}}=\dfrac{x}{1}$，于是 $\dfrac{\text{糖}}{\text{水}}=\dfrac{x}{1-x}$。

于是我们可以求出使一杯有 $a$ 克糖，$b$ 克水的糖水浓度变成 $x$ 所需要的糖数 $s=a-\dfrac{x}{1-x}b$。

**二分**：
- 二分一个浓度 $x$，对于这个浓度求有多少种混合糖水的浓度不小于它；
- 如果不足 $k$ 杯则浓度太大，使 $r=mid$，反之亦然。
- 二分一定次数（$100$ 次足矣）后输出 $l$ 的值。

接着考虑如何写 `check` 函数。

既然可以求出每一杯糖水到达目标浓度所需要的糖数 $s$，那可以把前 $n$ 杯或后 $m$ 杯的 $s$ 值预处理出来并排序，另外的部分枚举每一杯，求出其 $s$ 值，并用二分查找求出选这杯时有多少种方法能使混合后浓度大于 $x$（即两个 $s$ 加起来不超过 $0$）。

这样二分的复杂度是 $\text{O}(100)$，`check` 的复杂度是 $\text{O}(n \log n + m \log n)$ 或者是 $\text{O}(m \log m + n \log m)$ 的，总共就是 $\text{O}(100 n \log m)$（一种情况）的。

### Part3 代码

注释在代码里啦！

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//二分查找 
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<iomanip>//作用见输出 
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll n,m,k,a[50010],b[50010],c[50010],d[50010];
ld l=0,r=1;
ld v[50010];
bool check(ld t){
	ld x=t/(1-t);//糖与水之比 
	ll tsum=0;//统计数量 
	for(int i=0;i<n;i++){
		v[i]=a[i]-b[i]*x;//求出还需要的糖数 
	}
	sort(v,v+n);//别忘了排序，要不没法二分查找（二分查找只支持有序数组） 
	for(int i=0;i<m;i++){
		ld tmp=c[i]-d[i]*x;//这一杯缺的糖 
		ll p=lower_bound(v,v+n,-tmp)-v;//看看有多少能补回来，注意符号 
		tsum+=n-p;//统计结果 
	}
	return tsum<k;//注意这里是小于 
}
int main(){
	//读入 
	cin>>n>>m>>k;
	for(int i=0;i<n;i++){
		cin>>a[i]>>b[i];
	}
	for(int i=0;i<m;i++){
		cin>>c[i]>>d[i];
	}
	for(int i=0;i<100;i++){//100 次精度足够 
		ld mid=(l+r)/2;
		if(check(mid))r=mid;
		else l=mid;
	}
	cout<<fixed<<setprecision(12)<<l*100;
	//我这里使用了 long double 所以只能用这种方法输出，用 double 可以用 printf 输出。
	return 0;
}
```

---

## 作者：Hell0_W0rld (赞：2)

# [ABC294F Sugar Water 2](https://www.luogu.com.cn/problem/AT_abc294_f) 题解
*1891。

~~差点就蓝了~~
## 题目大意
两组糖水：第一组有 $n$ 杯，第 $i$ 种有 $a_i$ 克糖和 $b_i$ 克水；第二组有 $m$ 杯，第 $i$ 种有 $c_i$ 克糖和 $d_i$ 克水。混合后有 $n\cdot m$ 种糖水，求出其中浓度第 $k$ 大的糖水的浓度，用百分数，不输出 `%`。
## 解题思路
我们求出所有糖水的浓度显然不可以，所以我们考虑用二分。

二分答案：给定 $0\leq p\leq 100$，判断是否有至少 $k$ 种搭配浓度 $\geq p\%$。我们找出满足以上条件的最大 $p$ 即可。因为显然满足单调性，所以可以二分。

接着我们思考：如何判断上面的条件是否成立？

用原题给的式子：假设两杯糖水的糖为 $a_1,a_2$，水为 $b_1,b_2$。所以混合后糖为 $a_1+a_2$，糖水重量为 $a_1+a_2+b_1+b_2$。我们希望把 $a_1,b_1$ 放在一起，另外两个放在一起。

依题意可得：$\frac{100(a_1+a_2)}{a_1+b_1+a_2+b_2}\geq p$

化简后得：$100a_1-a_1-pa_2\leq pa_2+pb_2-100a_2$

算出左右两边，再用二分即可。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define repD(i,u,E) for(register ll i=hd[u];i;i=E[i].nxt)
#define all(x) x.begin(),x.end()
using namespace std;
void upd_s(ll&x,ll v){x=min(x,v);}
void upd_b(ll&x,ll v){x=max(x,v);}
const ll N=50009;
const double ERR=1e-12;
ll n,m,k;
ll a[N],b[N],c[N],d[N];
double e[N],f[N]; 
bool OK(double p){
	ll ans=0;
	/*
	100(x1+x2)/(x1+x2+y1+y2) <= p
	100x1+100x2 <= px1+px2+py1+py2
	100x1-px1-py1 <= px2+py2-100x2
	*/
	rep(i,1,n)e[i]=100*a[i]-p*a[i]-p*b[i];
	rep(i,1,m)f[i]=p*c[i]+p*d[i]-100*c[i];
	sort(f+1,f+1+m);
	rep(i,1,n)ans+=(upper_bound(f+1,f+m+1,e[i])-f-1);
	return ans>=k;
}
int main(){
	cin>>n>>m>>k;
	rep(i,1,n)cin>>a[i]>>b[i];
	rep(i,1,m)cin>>c[i]>>d[i];
	double l=0,r=100,ans;
	while(r-l>=ERR){
		double mid=(l+r)/2;
		if(OK(mid))l=ans=mid;
		else r=mid;
	}
	cout<<fixed<<setprecision(12)<<ans<<endl;
	return 0;
}
```

---

## 作者：JWRuixi (赞：2)

~~双指针写反方向了，/fn。~~

- 题意

给定长度为 $n,m$ 的两个数组 $a,b$，包含两个属性 $x,y$，求 ${a_i.x+b_j.x}\over{a_i.x+a_i.y+b_j.x+b_j.y}$ 的第 $k$ 值。

- 分析

考虑二分答案，即统计 $\frac{a_i.x+b_j.x}{a_i.x+a_i.y+b_j.x+b_j.y}\ge mid$ 的方案数，化简一下式子就是 $(a_i.x+b_j.x)\times(1-mid)+(a_i.y+b_j.y)\times mid \le 0$ 的方案数。我们将第 $i$ 个点的权值设为 $w=a_i.x\times(1-mid)+a_i.y\times mid$，就是统计 $a_i.w+b_j.w\le0$ 的方案数，直接排序加双指针即可。

复杂度 $\mathcal O(n\log n\log V)$。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
#define int long long
#define writesp(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n')
#define FileIO(ch) freopen(ch".in", "r", stdin), freopen(ch".out", "w", stdout)
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read() {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    template <typename _Tp>
    inline void write(_Tp x) {
    	static char stk[64], *top = stk;
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        do *top++ = x % 10, x /= 10;
        while (x);
        while (top != stk) putchar((*--top) | 48);  
    }
}

using IO::read;
using IO::write;

const int maxn(1e5 + 500);
const long double eps(1e-12);
int n, m, k;
struct Node {
	int x, y;
	long double w;
	inline bool operator < (const Node &rhs) const { return w < rhs.w; }
} a[maxn], b[maxn];

inline bool chk (long double mid) {
	for (int i = 1; i <= n; i++) a[i].w = a[i].x * (mid - 1) + a[i].y * mid;
	for (int i = 1; i <= m; i++) b[i].w = b[i].x * (mid - 1) + b[i].y * mid;
	sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
	int res = 0;
	for (int i = n, j = 1; i; i--) {
		while (j <= m && a[i].w + b[j].w <= 0) ++j;
		res += j - 1;
	}
	return res >= k;
}

signed main() {
	n = read(), m = read(), k = read();
	for (int i = 1; i <= n; i++) a[i].x = read(), a[i].y = read();
	for (int i = 1; i <= m; i++) b[i] = {read(), read()};
	long double l = 0, r = 1, mid;
	while (r - l > eps) {
		mid = (l + r) / 2;
		if (chk(mid)) l = mid;
		else r = mid;
	}
	printf("%.12Lf", l * 100);
}
// I love WHQ!
```

---

## 作者：Mikefeng (赞：2)

## 题意

两个人分别有 $n,m$ 瓶糖水，要求从两人中各选一瓶混合后浓度第 $k$ 大的糖水的浓度。

## 做法

典型的分数规划问题，至于分数规划问题是什么，详情请见 OI-wiki。

要求输出小数，想到二分答案，简单地化简一下柿子。

$\begin{alignedat}{3}\frac{a+c}{a+b+c+d}&\ge x
\\a+c&\ge x\times(a+b+c+d)
\\(1-x)\times a-x\times b+(1-x)\times c-x\times d&\ge 0
\\A-B&\ge0
\end{alignedat}$

其中 $A=(1-x)\times a-x\times b,B=(1-x)\times c-x\times d$。

处理出 $A,B$ 数组后排序，贪心即可。

时间复杂度 $O(n\log n\log V)$。

## 代码

由于 double 神秘的精度问题，建议使用较大的 int，最后再减去。

```cpp
const ll N=5e4+5;
const ll V=1e13;
ll n,m,k,ans;
ll a[N],b[N],c[N],d[N];
LD A[N],B[N];
inline bool check(ll x){
	F(i,1,n) A[i]=(V-x)*a[i]-x*b[i];
	F(i,1,m) B[i]=(V-x)*c[i]-x*d[i];
	sort(A+1,A+n+1);
	sort(B+1,B+m+1);
	ll res=0;
	ll l=m;
	F(i,1,n){
		while(l&&A[i]+B[l]>=0) --l;
		res+=m-l;
	}
	return res>=k;
}
int main(){
	n=read();m=read();k=read();
	F(i,1,n) a[i]=read(),b[i]=read();
	F(i,1,m) c[i]=read(),d[i]=read();
	ll l=0,r=V;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	printf("%.12f\n",ans*100.0/V);
	return 0;
}
```


---

## 作者：EnofTaiPeople (赞：2)

题意要求混合 $A,B$ 两个集合中各一瓶糖水，使其浓度最大，不考虑饱和。

当时一看到这道题就想到了之前的一道[省选题](https://www.luogu.com.cn/problem/P5319)，不过似乎简单很多。

于是可以套路地二分一个 $\Delta$，检验是否存在 $\dfrac{a+c}{a+b+c+d}>\Delta$，可以将不等式拆开，得到：$(1-\Delta)a-\Delta b>(\Delta-1)c+\Delta d$，发现左式只与 $a,b$ 有关，右式只于 $c,d$ 有关。

于是对于每一个 $(a,b)$ 我们都可以二分求出 $(c,d)$ 使其浓度大于 $\Delta$ 的方案数。

其实都是平凡的，时间复杂度 $O(n\log n\log V)$，其中 $V$ 与精度有关。

当然可以卡二分次数（我用的 $200$），由于是分数域二分，所以也被成为 $0/1$ 分数规划，[赛时 AC 记录](https://atcoder.jp/contests/abc294/submissions/39860977)。

---

## 作者：cwfxlh (赞：1)

# [ABC294F](https://www.luogu.com.cn/problem/AT_abc294_f)  

考场上多打了一个等号导致挂 $5$ 发都没调出来，痛失上分好机会。   

因为对于一个浓度，浓度大于等于它的混合溶液数量具有单调性，所以考虑二分答案。    

这里令 $T_i$ 表示溶液质量，$P_i$ 表示溶液浓度。

考虑 check 函数。对于一个浓度 $w$，如果溶液 $i$ 与溶液 $j$ 的混合溶液浓度大于等于 $w$，则有：  

$$\frac{T_i\times P_i+T_j\times P_j}{T_i+T_j}\ge w$$   
$$T_i\times P_i+T_j\times P_j\ge w\times T_i+w\times T_j$$   
$$T_i\times(P_i-w)\ge T_j\times(w-P_j)$$    

对于每一次 check，我们可以 $\Theta(n+m)$ 把 $T_i\times(P_i-w)$ 与 $T_j\times(w-P_j)$ 跑出来（一个序列一种式子），排序后使用尺取法移动指针算出满足上述不等式的匹配数，如果大于等于 $w$，则合法，否则不合法。时间复杂度足以通过本题。   

Code：  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int T1[500003],nd1[500003],T2[500003],nd2[500003],k1,k2;
long double F1[500003],F2[500003];
long double l,r,mid;
int zc,sum;
bool jud(long double X){
	for(int i=1;i<=n;i++){
		F1[i]=nd1[i]-(long double)(T1[i])*X;
	}
	for(int i=1;i<=m;i++){
		F2[i]=(long double)(T2[i])*X-nd2[i];
	}
	sort(F1+1,F1+n+1);
	sort(F2+1,F2+m+1);
	zc=0;
	sum=0;
	for(int i=1;i<=n;i++){
		while(zc<m&&F2[zc+1]<=F1[i])zc++;
		sum+=zc;
	}
	return sum>=k;
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&k1,&k2);
		if(k2==0){
			n--;
			i--;
			continue;
		}
		T1[i]=k1+k2;
		nd1[i]=k1*100;
	}
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&k1,&k2);
		if(k2==0){
			m--;
			i--;
			continue;
		}
		T2[i]=k1+k2;
		nd2[i]=k1*100;
	}
	l=0.00;
	r=100.00;
	while(r-l>=10e-16){
		mid=(l+r)*0.5;
		if(jud(mid))l=mid;
		else r=mid;
	}
	printf("%.15Lf",l);
	return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/17241125.html)

[题目传送门](https://atcoder.jp/contests/abc294/tasks/abc294_f)

### 题目大意
高桥君有 $N$ 瓶糖水，第 $i$ 瓶有 $A_i$ 克糖和 $B_i$ 克水。青木君有 $M$ 瓶糖水，第 $i$ 瓶有 $C_i$ 克糖和 $D_i$ 克水。然后两人各拿出一瓶混在一起，求可能产生的第 $K$ 大的浓度百分比是多少，误差在 $10^{-9}$ 内均为正确。  
定义一瓶 $x$ 克糖 $y$ 克水的糖水浓度为 $\dfrac{100x}{x+y}\%$。  
$1\le N,M\le 5\cdot 10^4$，$1\le K \le NM$，$1\le A_i,B_i,C_i,D_i\le 10^5$，输入均为整数。
### 题目解析
考虑直接求第 $K$ 大不好算，所以考虑二分答案，然后求一个浓度比他大的数量。  
考虑两个瓶糖水混合在一起，浓度大于等于 $t$。
$$\dfrac{A_i+C_j}{A_i+B_i+C_j+D_j}\ge t$$
考虑化简，将 $A_i,B_i$ 和 $C_j,D_j$ 分到不等式两边，得到
$$A_i-(A_i+B_i)t\ge-C_j+(C_j+D_j)t$$
这样我们可以按照 $-C_j+(C_j+D_j)t$ 排序，枚举 $i$ 二分 $j$ 即可做到 $\Theta(N\log N)$ 计算。  
加上前面二分答案，复杂度就是 $\Theta(N\log M\log W)$，其中 $W=10^{12}$。

坑点：

- `long double` 防止卡精度
- $K$ 的范围是 $NM=2.5\cdot10^9$，需要 `long long`

```cpp
int n,m; ll k; ld l,r,mid,p[maxn],q[maxn];
struct JTZ{
	ld x,y;
}a[maxn],b[maxn];
#define mg(i,j) ((a[i].x+b[j].x)*1.0/(a[i].x+a[i].y+b[j].x+b[j].y))
ll js(){
	int i,le,ri,midd; ll cnt=0;
	for(i=1;i<=n;i++) p[i]=a[i].x-(a[i].x+a[i].y)*mid;
	for(i=1;i<=m;i++) q[i]=-b[i].x+(b[i].x+b[i].y)*mid;
	sort(q+1,q+m+1);
	for(i=1;i<=n;i++){
		le=0,ri=m+1;
		while(le+1<ri){
			midd=(le+ri)>>1;
			if(q[midd]<p[i]+1e-12) le=midd; else ri=midd;
		}
		cnt+=le;
	} return cnt;
}
int main(){
	n=read(); m=read(); k=read(); int i;
	for(i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
	for(i=1;i<=m;i++) b[i].x=read(),b[i].y=read();
	l=0,r=1;
	while(l+EPS<=r){
		mid=(l+r)/2;
		if(js()<k) r=mid; else l=mid;
	}
	printf("%.10Lf",l*100.0);
	return 0;
}
```

---

## 作者：_Imaginary_ (赞：0)

## Problem

有两组糖水，分别有 $n$ 杯（有 $x1_i$ 吨糖和 $y1_i$ 吨水）和 $m$ 杯（有 $x2_i$ 吨糖和 $y2_i$ 吨水），求将它们两两混合后浓度第 $k$ 大的混合浓度是多少。

## Solution

我们先对 $\frac{100x}{x+y}$ 进行变形。

$$
\frac{100x}{x+y}=\frac{100}{1+\frac y x}
$$

要求浓度第 $k$ 大，也就是求 $\frac{y1+y2}{x1+x2}$ 第 $k$ 小。

观察到数据范围是 $5\times 10^4$，不难想到应该是一个多 $\log$ 的做法。

于是，我们可以在外面套一个二分，转化求 $\frac{y1+y2}{x1+x2}\ge t$ 的混合糖水种类数。

再进行变形，首先进行通分，得到

$$
y1+y2\ge tx1+tx2 \leftrightarrow y1-tx1\ge tx2-y2
$$

这时，我们可以先用 $O(m+n)$ 的代价把所有的 $y1-tx1$ 和 $tx2-y2$ 求出来，这样问题进行了转化：

有两个数组 $a,b$，求有多少对 $i,j$ 满足 $a_i\ge b_j$。

首先用 $O(m\log m)$ 对 $b$ 数组排序，然后枚举每个 $a_i$，用 $O(n\log m)$ 的时间二分查找有多少个 $b_i$ 比它小。

这样，由于 $n$ 和 $m$ 同阶，整个问题就用 $O(n\log^2 n)$ 解决了。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define y1 y11
const int N=500005;
int n,m;
ll k;
ll x1[N],y1[N],x2[N],y2[N];
ld a[N];
int get(ld x)
{
	int L=1,R=m,mid;
	while(L<=R)
	{
		mid=(L+R)>>1;
		if(x>a[mid]) L=mid+1;
		else R=mid-1;
	}
	return R;
}
ll check(ld k)
{
	for(int i=1;i<=m;i++) a[i]=(ld)x2[i]*k-(ld)y2[i];
	sort(a+1,a+m+1);
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans+=get((ld)y1[i]-k*(ld)x1[i]);
	return ans;
}
int main()
{
	scanf("%d%d%lld",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&x1[i],&y1[i]);
	for(int i=1;i<=m;i++) scanf("%lld%lld",&x2[i],&y2[i]);
	ld L=0.0,R=1e20,mid;
	while(R-L>1e-14)
	{
		mid=(L+R)/2.0;
		if(check(mid)>=1ll*n*m-k+1) L=mid;
		else R=mid; 
	}
	printf("%.11Lf",100.0/(1.0+L));
	return 0;
}
```

## 后记

个人观点：

| 数据范围|一般的复杂度 |AtCoder 上常见的复杂度 |
|:-:|:-:|:-:|
| $5\times 10^4$ | $O(n\log^3 n)$ | $O(n\log^2 n)$ |
| $2\times 10^5$| $O(n\sqrt n)$ 或 $O(n\log^2 n)$ | $O(n\sqrt n)$ 或 $O(n\log n)$ |
|$10^6$ | $O(n\log n)$ 或 $O(n)$| $O(n)$|

---

## 作者：kelanjie (赞：0)

# 一个容易错误的贪心(仅用于警示)
一杯浓度大的糖水与另一杯糖水混合，另一杯糖水的浓度大不代表混合后的浓度大

如: $7g$ 糖, $14g$ 水为确定的一杯，称作 $W$ 杯

然后还有两杯

 $A$ 杯为 $7g$ 糖, $4g$ 水, $B$ 杯为 $3g$ 糖, $0g$ 水(浓度 $100$% ，大不大)

然后 $W$ 与 $A$ 混合后的浓度为 $43.75$%

 $W$ 与 $B$ 混合后的浓度为 $41.66666.....$%

初始思路： 先想到二分浓度，然后想到 (假) 单调性，即前面提到的，然后枚举 $n$ 杯糖水,与剩下 $m$ 杯糖水混合是有(假的)单调性的，再进行二分看有多少混合后的糖水比当前 $x$ 浓度大，不断二分，调了好久，最后终于发现了这贪心假了(估计是因为我太菜了)

下面放造的数据:

```
4 3 10
9 1
7 14
13 15
13 5
6 15
3 0
7 4
```

# 正确思路
$1.$依旧是二分浓度, 浓度设为$x$

$2.$计算有 $res$ 杯(混合后的)浓度大于 $x$

$3.$**(可以灵活变通)**,假设一杯糖水有 $a$ g糖, $b$ g水

在水不变的情况下若浓度为 $x$ ，则应有 $ x\times\frac{b}{(1-x)} g$ 糖,

那么原来的糖水多余 $s_x=$($a- x\times\frac{b}{(1-x)}$)$ g$ (化简为$\frac{a-(a+b)x}{1-x}$,然后高桥君和青木君的糖水都 $\times (1-x)$，不影响排序 ) 糖(可以是负数，表示缺少)

于是高桥君($s_x$)和青木君($s_y$)的每杯糖水都如此处理,满足$s_x+s_y>0$ 的个数即为 $res$ ，将其中一方取负就可以在另一方的糖水中二分查找（多余或缺少的糖）

## 正确代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)/2)
const int N=5e4+5;
typedef long long ll;
int n,m;
ll k;
struct node{
	int sug,tot;
}a[N],b[N];
double c[N];

bool check(double w){//浓度 
	vector<double>vec;
	for(int i=1;i<=n;i++)
		vec.push_back(a[i].tot*w-a[i].sug);//取负 判断s[x]+s[y]正负 
	for(int i=1;i<=m;i++)
		c[i]=b[i].sug-b[i].tot*w;
	sort(c+1,c+m+1);
	ll res=0;

	for(int i=0;i<n;i++){
		int j=lower_bound(c+1,c+m+1,vec[i])-c;
		res+=(m-j+1);
	}
	if(res>=k)	return false;
	return true;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].sug>>a[i].tot;
		a[i].tot+=a[i].sug;//总质量 
	}
	for(int i=1;i<=m;i++){
		cin>>b[i].sug>>b[i].tot;
		b[i].tot+=b[i].sug;
	}
	
	double l=0,r=1;
	for(int iter=1;iter<=100;iter++){//二分浓度
		 if(check(mid))	r=mid;
		 else	l=mid;
	}
	cout<<fixed<<setprecision(12)<<l*100;
	return 0;
}
```



---

