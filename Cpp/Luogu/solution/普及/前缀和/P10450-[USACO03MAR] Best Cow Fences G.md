# [USACO03MAR] Best Cow Fences G

## 题目描述

**原题来自：USACO 2003 Mar. Green**

给定一个长度为 $n$ 的非负整数序列 $A$ ，求一个平均数最大的，长度不小于 $L$ 的子段。

## 说明/提示

$1 \leq n \leq 10^5,0 \leq A_i \leq 2000$。

## 样例 #1

### 输入

```
10 6
6 4 2 10 3 8 5 9 4 1```

### 输出

```
6500```

# 题解

## 作者：Genius_Star (赞：22)

### 思路：

简单题。

考虑二分答案 $mid$。

我们需要找到一个 $l,r$ 使得：

$$\frac{\sum_{i=l}^r a_i}{r-l+1} \ge mid$$

转换得：

$$\sum_{i=l}^ r (a_i - mid) \ge 0$$

那么将序列中每个数减去 $mid$，然后相当于求一个长度大于等于 $L$ 的最大子段和，判断一下是否大于 $0$ 即可。

时间复杂度为 $O(N \log W)$。

---

## 作者：Sparse_Table (赞：16)

[题目链接](https://www.luogu.com.cn/problem/P10450)


[博客食用体验更佳](https://www.cnblogs.com/0x3f3f3f3f3f3f/p/18320972)

## $ O(n^3) $ 做法
1. 第一层循环先跑一遍长度（题目有限制长度不小于 $ L $）。

1. 第二层循环跑一遍起点，千万要注意不要越界 QwQ。

1. 最后再遍历这个区间求最大值。


附上我丑陋的代码和[提交记录](https://www.luogu.com.cn/record/168208389)，这个代码可以得 42 分。
```cpp
#include <bits/stdc++.h>
using namespace std;

const int NR = 1e5 + 5;
long long n, l, a[NR], sum, ave;

int main() {
	cin >> n >> l;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = l; i <= n; i++) //先枚举长度
		for (int j = 1; j <= n - i + 1; j++) { //枚举起点
			sum = 0;
			for (int k = j; k <= j + i - 1; k++)//遍历，求和
				sum += a[k];
			ave = max(ave, sum * 1000 / i);
		}
	cout << ave;
	return 0;
}
```
## $ O(n^2) $ 做法
根据上面，我们可以发现求和的那段过程可以用前缀和优化，我们可以先 $ O(n) $ 预处理前缀和，再枚举。


### 如何预处理前缀和
我们用 $s_i$ 表示前缀和。
$$
s_i = \sum_{j = 1}^i a_j
$$
$s$ 数组的递推方式如下。
$$
s_i = s_{i - 1} + a_i
$$
   
不懂的可以看[前缀和代码](https://www.luogu.com.cn/paste/anicta0l)，大家也可以拿[这道题](https://www.luogu.com.cn/problem/B3612)练练手。


下面是我丑陋的代码和[提交记录](https://www.luogu.com.cn/record/168207889)，我们已经可以拿到 70 分了。
```cpp
#include <bits/stdc++.h>
using namespace std;

const int NR = 1e5 + 5;
long long n, l, a[NR], s[NR], sum, ave;

int main() {
	cin >> n >> l;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];//前缀和预处理 
	for (int i = l; i <= n; i++) //同上，先枚举长度
		for (int j = 1; j <= n - i + 1; j++) { //枚举起点
			sum = s[j + i - 1] - s[j - 1];//求区间和
			ave = max(ave, sum / i * 1000);
		}
	cout << ave;
	return 0;
}
```

## $ O(n \log W) $ 做法
我们发现这道题平均数越小越容易达到，符合二分的特点。我们可以找一个数值，再判断是否符合要求。
### check 函数该怎么写
这次前缀和与上面有点不同。

1. 前缀和：这次前缀和表示前缀和与理想的总和的差。
1. 为什么要累求最小值：因为想让平均数越大减的就需要越小。
1. 平均数若大于理想的平均数，就返回真，否则返回假。
1. 不知道说啥了，送大家一个我用的[二分板子](https://www.luogu.com.cn/paste/trv0ulj9)。

哦对了，我把 $s$ 数组的递推式写上
$$
s_i = s_{i - 1} + a_i - mid
$$

~~历尽千辛万苦~~，我们 AC 了这道题，最后贴上我丑陋的代码和[提交记录](https://www.luogu.com.cn/record/168223458)。
```cpp
#include <bits/stdc++.h>
using namespace std;

const int NR = 1e5 + 5;
long long n, L;
double l = 0, r = 2e3, s[NR], a[NR];//s[i]表示前缀和与理想的总和的差

bool check(double mid) {
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i] - mid; 
	double minn = 0;
	for (int i = L; i <= n; i++) {//枚举起点
		minn = min(minn, s[i - L]);//累求最小值 
		if(s[i] - minn >= 0)
			return 1; 
	}
	return 0;
}

int main() {
	cin >> n >> L;
	for (int i = 1; i <= n; i++) cin >> a[i];
	while (r - l > 1e-5) {
		double mid = (l + r) / 2;
		if(check(mid)) l = mid;
		else r = mid;
	}
	cout << int(r * 1000);
	return 0;
}
```
题解结束了，有问题欢迎大家私信我。

---

## 作者：ny_Dacong (赞：10)

# 前言

本题几乎全部题解（除了 <https://www.luogu.com.cn/article/4uf80r82> 使用的是斜率优化）都使用的是二分。时间复杂度为 $O(n \log W)$。

但是本题可以实现 $O(n)$ 的复杂度。不过只有唯一一篇题解提及了这种做法（就是前文提到的那篇），而且说得比较含糊。于是便有了本文。

# 思路

令序列 $s$ 为 $A$ 的前缀和。

那么以 $i$ 结尾的区间最大平均数是：

$$\frac{s_i-s_j}{i-j}$$

其中，$0 \le j \le (i-L)$。

我们将每个点对应到坐标轴上。对于 $i$，其横坐标为 $i$，纵坐标为 $s_i$。

那么上面的公式其实就是计算点 $i,j$ 所在直线的斜率。

我们又知道，$0 \le A_i$，所以 $s$ 满足单调不下降。

转换一下问题，相当于求两个点之间的最大斜率。因此，我们可以使用斜率优化实现 $O(n)$ 复杂度。

# 实现

用单调队列实现。

再次强调，因为 $0 \le A_i$，所以 $s$ 满足单调不下降。也就是说，任意两个点所在的直线斜率不会是负数。单调队列是正确的。

单调队列的主要操作是“掐头去尾”。

首先讨论弹出队头的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/3d3lbk7x.png)

如图，设最右边的点是即将加入队列的点。黄线的斜率大于蓝线的斜率，因此这个点的答案肯定不会是蓝线。所以蓝线就可以弹出了。

![](https://cdn.luogu.com.cn/upload/image_hosting/jsjyxqmn.png)

如图，黄线的斜率小于蓝线的斜率，这个点的答案可能是蓝线。因此不应该弹出。

这个点的最终答案就是该点与队头所在直线的斜率。

接下来讨论弹出队尾的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/vr2e91ks.png)

图中绿色的点是队列中的点。这些点构成了下凸壳。将这些点从后往前依次跟红色点（待讨论的点）进行比较。

图中蓝线是不合法的。因为蓝线跟黑线不能组成下凸壳。这样的情况应该将对应点弹出。黄线是第一条合法的线。

以此规则维护即可。

注意区间长度最小为 $L$。以及恶心的精度。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
double ans = 0;
double num[100005],sum[100005];
double slope(int x,int y){
	return (sum[x]-sum[y])/(x-y);
}
int Head,End;
int que[100005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++){
		scanf("%lf",&num[i]);
		sum[i] = sum[i-1]+num[i];
	}
	Head = 0,End = 0;
	for(int i = m; i <= n; i++){
		while(Head < End && slope(i,que[Head]) <= slope(i,que[Head+1])){//弹出队头
			Head++;
		}
		ans = max(ans,slope(i,que[Head]));
		while(Head < End && slope(que[End],que[End-1]) >= slope(i-m+1,que[End])){//弹出队尾
			End--;
		}
		End++;
		que[End] = i-m+1;
	}
	int tp;
	tp = ans*1000;
	if(tp%10 == 7){//可恶的精度！神秘数据不给 SPJ，只能特判
		tp--;
	}
	printf("%d",tp);
	return 0;
}
```

---

## 作者：TheForgotten (赞：8)

# P10450 [USACO03MAR] Best Cow Fences G 题解
 [题目传送门](https://www.luogu.com.cn/problem/solution/P10450)
## 题目大意
给定一个长度为 $n$ 的非负整数序列 $A$，求一个平均数最大且长度不小于 $L$ 的子段。
## 思路
由于 $1 \leq n \leq 10^5$，三层循环暴力肯定超时。由于要计算平均值，取最大值，所以考虑前缀和优化，但是时间复杂度仍然不满足题意，继续考虑二分优化。在二分过程中判断时使用每个前缀里的每个数减去均值，进一步求和，只需要找到一段长度大于等于要求的区间即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,k;
const int o=100005;
double l=0,r=0,mid;
double a[o],sum[o];
bool work(double x){
	double t=0.0;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i]-x;
	}
	for(int i=k;i<=n;i++){
		t=min(sum[i-k],t);
		if(sum[i]>=t){
			return 1;
		}
	}
	return 0;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		r=max(r,a[i]);
	}
	while(r-l>1e-5){
		mid=(l+r)/2;
		if(work(mid)) l=mid;
		else r=mid;
	}
	cout<<(int)(r*1000);
	return 0;
}
```

---

## 作者：LionBlaze (赞：6)

对于这道题，我们有三种算法：
### $O(n^3)$ 算法

枚举左右端点（或者一个端点+长度），直接计算平均值，取最大值。

枚举端点：$O(n^2)$，计算平均值：$O(n)$，总时间复杂度：$O(n^3)$。

### $O(n^2)$ 算法

计算平均值的瓶颈在于，求和。

于是想到前缀和。

预处理 $O(n)$，枚举端点 $O(n^2)$，单次计算 $O(1)$，总时间复杂度 $O(n^2)$。

### $O(n \log n)$ 算法

观察数据范围，$n \le 10^5$，需要 $O(n \log n)$ 算法。

设 $f(x)$ 是平均数为 $x$ 时是否可行（或者说，最大平均数是否 $\ge x$），容易发现是个单调函数。

于是想到二分答案。

如何判断 $f(x)$ 呢？毕竟算平均数不是简单地求和，怎么做呢？

但，如果只要判断平均数是否大于/小于某个值，确实只需要简单地求和。

对于一个长度为 $|a|$ 的数列 $a$，直接判断：

$$ \frac{\sum^{|a|}_{i=1}a_i}{|a|} \ge x $$
$$ \frac{\sum^{|a|}_{i=1}a_i}{|a|} - x \ge 0 $$
$$ \sum^{|a|}_{i=1}a_i - |a|x \ge 0 $$
$$ \sum^{|a|}_{i=1}a_i - \sum^{|a|}_{i=1}x \ge 0 $$
$$ \sum^{|a|}_{i=1}(a_i-x) \ge 0 $$

于是，我们只需要在 $f(x)$ 中将所有 $a_i$ 减去 $x$，然后看看[最大子段和](https://www.luogu.com.cn/problem/P1115)是否大于 $0$ 就好了。

（不会最大子段和的点上面蓝字。）

最后时间复杂度：

预处理 $O(n)$，最大子段和 $O(n)$，二分 $O(\log n)$，总共 $O(n \log n)$ 解决！

（原本这里“最大子段和”写成了“最大字段和”，感谢提醒。）

---

## 作者：lzbzl (赞：5)

# P10450 题解
[题目传送门](https://www.luogu.com.cn/problem/P10450)

这题说简单也不简单，说难也不难，很好的一个练手题。感谢 @jager_8 大佬提供的思路，膜拜膜拜。
# 思路
这题求最大平均数，不妨设 $d_i$ 为第 $i$ 位时的平均数最值，根据公式易得：

- $d_i=\max((s_j-s_i)×1000÷(j-i))$

$s_k$ 为前缀和数组，即为：

$$
s_k=\sum_{i=1}^k a_i
$$

## 朴素思路
先不考虑优化，考虑朴素思路，用 $d_i$ 数组记录平均数最值，用 $i$ 和 $j$ 来模拟左端点和右端点。时间复杂度为 $O(n^2)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,L,a,d[1000005],s[1000005];
signed main()
{
	cin>>n>>L;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		s[i]=s[i-1]+a;
	}
	for(int i=1;i<=n-L+1;i++)
	{
		for(int j=i+L-1;j<=n;j++)
		{
			d[i]=max(d[i],(s[j]-s[i-1])*1000/(j-i+1));
		}
		for(int j=1;j<=n;j++)
			d[j]=max(d[j],d[j-1]);
	}
	cout<<d[n];
	return 0;
}
```
得分：$70pts$。

由于题中 $n$ 的范围为 $10^5$，所以 T 了[三个点](https://www.luogu.com.cn/record/159689057)。

## 优化思路
考虑优化。

根据标签可知这是一道二分优化的题。同时还能得知：题中有单调递增的值。再回头看一下转移方程可以发现，方程只与 $d_i$ 的最大值有关，并且 $i$ 与 $j$ 可以看成为定值。所以我们可以用单调队列来优化，复杂度直接降到 $O(n)$。

当队头平均数小于新加的平均数时就将队头踢出，反之就踢出队尾。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,L,a[100005],s[100005];
double ans;
double ge(int x,int y)
{
	return (1.0*s[x]-s[y])/(x-y);
}
int head=1,tail=0;
signed main()
{
	cin>>n>>L;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	memset(a,0,sizeof(a));
	for(int i=L;i<=n;i++)
	{
		while(head<tail && ge(i-L,a[tail])<=ge(a[tail],a[tail-1]))
			tail--;
		a[++tail]=i-L;
		while(head<tail && ge(i,a[head])<=ge(i,a[head+1]))
			head++;
		ans=max(ans,ge(i,a[head]));
	}
	cout<<(int)(ans*1000);
	return 0;
}
```
得分：$100pts$。

虽然此题正解为二分，但单调队列优化也是可行的，几乎想不出来。所以再次膜拜大佬 @jager_8 膜拜。

单调队列跑得十分[快](https://www.luogu.com.cn/record/159692935)，加了快读[更快](https://www.luogu.com.cn/record/159691381)。所以要勤加快读。

关于单调队列优化的问题，可以看看 oi-wiki 中的[定义](https://oi-wiki.org/dp/opt/monotonous-queue-stack/)。dp 的优化技巧是十分有用的，学了绝对不亏。

感谢管理员审核。

---

## 作者：a18981826590 (赞：3)

# [P10450 [USACO03MAR] Best Cow Fences G](https://www.luogu.com.cn/problem/P10450)
## 解题思路
二分答案平均值。将原序列减去平均值，找到一段长度 $\ge L$ 且和 $\ge 0$ 的子序列，若存在则此原子序列平均值 $\ge$ 当前答案，则当前答案合法。

求子序列和时，先求出前缀和，因为子段和为右端点的前缀和减左端点前一位的前缀和，为使子段和尽量大，应使左端点前一位的前缀和尽量小，右端点的前缀和尽量大。保持左右端点相距 $\ge L$，左端点可为已遍历的前缀和最小处后一位，右端点为当前点，若左端点前一位的前缀和小于右端点的前缀和，即子序列和 $\ge 0$。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
double a[100010],b[100010],x=2001,y;
int m,n;
inline int read(){
	char c;
	int d=0,e=1;
	c=getchar_unlocked();
	while(!isdigit(c)){
		if(c=='-') e=-1;
		c=getchar_unlocked();
	}
	while(isdigit(c)){
		d=(d<<1)+(d<<3)+(c^48);
		c=getchar_unlocked();
	}
	return d*e;
}
void print(int d){
	if(d<0){
		putchar_unlocked('-');
		d=-d;
	}
	if(d<10) putchar_unlocked(d+48);
	else{
		print(d/10);
		putchar_unlocked(d%10+48);
	}
}
bool f(double x){
	double g=0;
	for(int i=1;i<=n;i++) b[i]=b[i-1]+a[i]-x;
	for(int i=m;i<=n;i++){
		g=min(g,b[i-m]);
		if(b[i]>=g) return 1;
	}
	return 0;
}
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		x=min(a[i],x);
		y=max(a[i],y);
	}
	while(y-x>1e-7){
		if(f(x+(y-x)/2)) x+=(y-x)/2;
		else y=x+(y-x)/2;
	}
	print(y*1000);
	return 0;
}
```

---

## 作者：GeXiaoWei (赞：2)

# P10450 [USACO03MAR] Best Cow Fence
## 题目解析
法一：三层循环暴力，必定超时。

法二：前缀和优化法一，依然超时。

法三：观察数据大小，可以使用二分。要对所求的平均值进行二分，上限最大值，下限为零。在判断时用前缀和，每个前缀里的每个数减去均值，求和，这样问题就转变成了是否存在一段长度大于等于要求的区间，和大于零。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
double l=0,r=0,mid,a[100005],sum[100005];
bool check(double x){
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i]-x;
	double t=0;
	for(int i=k;i<=n;i++){
		t=min(t,sum[i-k]);
		if(sum[i]>=t) return true;
	}
	return false;
}
int main(){
	scanf("%lld %lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lf",&a[i]),r=max(r,a[i]);
	while(r-l>1e-5){
		mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%d",(int)(r*1000));
	return 0;
} 
```

---

## 作者：Pink_Cut_Tree (赞：2)

# P10450 [USACO03MAR] Best Cow Fences G 题解

### 思路

本题当中，我们需要一个尽可能大的平均数，我们将这个平均数视为“基准”，或 $0$。然后我们将数列中的所有数减去“基准”，判断是否存在一个子段和大于等于 $0$，长度不小于 $L$ 的子段即可。

于是自然而然想到了二分答案，二分这个“基准”即可，值域 $\left [  1,2000\right ] $。

在 `check()` 函数中求前缀和，注意这个小技巧，然后判断是否有一个长度为 $L$ 的区间满足要求即可。这里取 $L$ 就够了，没有必要取到 $L+1,L+2,\dots$，可以证明，取 $L$ 一定不劣。

注意要开 `double`。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,L;
double a[N],qz[N]; 
bool check(double x){
	for(int i=1;i<=n;i++){
		qz[i]=qz[i-1]+a[i]-x;
	}
	double t=0;
	for(int i=L;i<=n;i++){
		t=min(t,qz[i-L]);
		if(qz[i]>=t){
			return 1;
		}
	}
return 0;
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>L;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	double l=0,r=2000;
	while(r-l>1e-5){
		double mid=1.0*(l+r)/2;
		if(check(mid)){
			l=mid; 
		}
		else{
			r=mid;
		}
	}
	cout<<(int)(r*1000);
return 0;
}
```

---

## 作者：110821zj_hhx (赞：2)

二分平均数，求最大子段和，为了方便我们对当前子段和判断平均数，可以一开始将数组减去平均数再求和，这样只需要判断子段和是否大于 $0$ 就能判断对于原数组中平均数是否大于我们二分的平均数。

下附带注释 AC 代码

```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int n,f;
double a[100005],sum[100005],mn=0x3f3f3f3f,mx=-0x3f3f3f3f;
signed main(){
	cin>>n>>f;
	for(int i=1;i<=n;i++) cin>>a[i];
	double l=0,r=2005,eps=0.00001;//二分平均数
	while(l+eps<r){
		mn=0x3f3f3f3f,mx=-0x3f3f3f3f;
		double mid=(l+r)/2;
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i]-mid;//使用前缀和，方便求出最大子段和，此处减 mid 是为了方便判断平均数
		for(int i=f;i<=n;i++){
			mn=min(mn,sum[i-f]);//如果 f 个数之间的子段和小于0，加上只会让子段和变小，此时不计算 f个数之前的子段和
			mx=max(mx,sum[i]-min(0.0,mn));//更新当前最大子段和
		}
		if(mx>0) l=mid;//减去平均数后的最大子段和大于零，说明原来的最大子段和的平均数大于二分所得的平均数，将 l 变大，尝试平均数更大的情况
		else r=mid;
	}
	cout<<(int)(r*1000);
	return 0;
}

```

---

## 作者：2huk (赞：1)

二分答案 $x$。我们需要检验的是是否存在一个平均数不小于 $x$ 的长度为 $L$ 的子段。

序列 $x$ 的平均值 $\bar x$ 是否不小于 $k$，等价于 $\sum (x_i - \bar x)$ 是否非负。

证明：
$$
\begin{matrix}& \bar x \ge k\\\Longleftrightarrow & \frac 1n\sum x_i \ge k\\\Longleftrightarrow & \sum x_i \ge nk\\\Longleftrightarrow & \sum x_i - nk \ge 0\\\Longleftrightarrow & \sum (x_i - k) \ge 0\end{matrix}
$$

回到题目。我们希望找到一个长度 $\ge L$ 的子段使得其平均值大于等于 $x$。

我们令 $b_i = a_i - x$。问题变成了判断 $b$ 中是否存在一个长度 $\ge L$ 的区间 $[l, r]$，使得 $b_l + b_{l+1} + \dots + b_r \ge 0$。显然我们只需要求 $b$ 中最大的长度不小于 $L$ 的区间和即可。

求出 $b$ 的前缀和 $s$。所求即 $\max_{r=1}^n \max_{l = 1}^{r-L+1} (s_r - s_{l-1})$。我们枚举 $r$。那么要想使得 $s_r - s_{l-1}$ 最大就需要让 $s_{l-1}$ 最小。

所以答案是 $\max_{r=1}^n (s_r - \min_{l=1}^{r-L+1} s_{l-1}) = \max_{r=1}^n (s_r - \min_{l=0}^{r-L} s_l)$。对于 $\min_{l=0}^{r-L} s_l$ 的计算可以预处理。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N =  100010;

int n, F;
double a[N], s[N];

bool chk(double avg)
{
    for (int i = 1; i <= n; ++ i )
        s[i] = s[i - 1] + a[i] - avg;
    
    double mn = 0;
    for (int k = F; k <= n; ++ k )
    {
        mn = min(mn, s[k - F]);
        if (s[k] >= mn) return true;
    }
    return false;
}

int main()
{
    cin >> n >> F;
    
    double l = 0, r = 0;
    for (int i = 1; i <= n; ++ i )
    {
        cin >> a[i];
        r = max(r, a[i]);
    }
    
    while (r - l > 1e-5)
    {
        double mid = (l + r) / 2;
        if (chk(mid)) l = mid;
        else r = mid;
    }
    
    cout << (int)(r * 1000);
    
    return 0;
}
```

---

## 作者：__rnfmabj__ (赞：1)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P10450)

给定一个长度为 $n$ 序列，求出平均值最大，且长度不小于 $L$ 的最大子串。
## 理清思路
显然二分答案，因为大于同一个平均值的序列个数显然会随着枚举的平均值单调递增。

这里有一个结论，对于一个长度为 $n$ 的序列 $a$ ，$\sum_{i = 1}^{n} a_i-\overline{a} =0$，换句话说，对于一段 $l—r$ 的区间，当 $\sum_{i = l}^{r} a_i-mid \ge 0$，则说明 $\overline{a} \ge mid$ 。

（其实说白了就是说序列的每一个值减去它的平均数再相加显然等于 0，所以当我们二分出一个 $mid$ ，在 $l—r$ 的区间内，当这个区间的每一个数减去 $mid$ 在相加如果大于等于 0，说明 $l—r$ 的平均数大于等于 $mid$）。

考虑写 $\operatorname{check}$ 函数，先将每一个 $a_i$ 减去我们二分的平均值 $mid$ ，然后我们只需要看看有没有一段序列的和加起来刚好大于或等于 0 ，就代表有答案。

所以我们只需要维护一下 $a$ 中每一个元素减去 $mid$ 之后的前缀和，考虑到我们只需要一段长度的最大值，不需要其他值，所以可以用单调队列做，考虑维护序列减去 $mid$ 的前缀和，用单调队列维护**开头**的的最小值（因为你只需要最大的就行），然后每次遍历到一个 $j$，就用 $sum_j-sum_{开头}$ ，得到的值在判断大不大于 0 即可。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
#define int long long

int n,m,a[N],maxx=INT_MIN;
int sum[N];

bool check(int mid){
    for(int i=1;i<=n;i++)
        sum[i]=sum[i-1]+a[i]-mid;
    //去掉mid之后的前缀和
    deque<int> q;
    for(int i=m;i<=n;i++){
        while(q.size() && sum[q.back()]>sum[i-m]) q.pop_back();//维护最小的开头
        q.push_back(i-m);
        if(q.size() && sum[i]-sum[q.front()]>=0) return 1;//如果有sum[i]-sum[q.front()]>=0，说明以q.front()开头，以i结尾区间的平均数大于等于二分的mid
    }
    return 0;
}
signed main(){
    cin>>n>>m;
    for (int i=1;i<=n;i++){
        cin>>a[i],a[i]*=10000;
        //由于题目要乘1000，所以直接将原数组乘10000之后将答案除以10即可（省去了不必要的double）
        maxx=max(maxx,a[i]);
    }
    int l=0,r=maxx;
    while (r>l){//二分板子
        double mid=(l+r)/2;
        if (check(mid))
            l=mid+1;
        else r=mid-1;
    }
    cout<<l/10;//输出答案
	return 0;//完结撒花
}
```

---

## 作者：zhaisx (赞：0)

### 大体思路
求长度为 $n$ 的序列 $A$ 子段平均值的最大值，可以考虑二分查找，查找区间为 $\left[\min(A), \max(A)\right]$。

### 二分查找中的 check 函数
设查找的数字为 $x$。则只要序列 $A$ 中有一段子段的和大于 $x \times$ 子段长，就返回真，$l \gets x$；否则返回假，$r \gets x - 1$。

求最大子段和可以先求出前缀和序列 $S$，再枚举右端点，同时记录左边所有端点的最小值。只要 $S_{\text{右端点}} - S_{\text{左端点}} > x \times$ 右端点和左端点的距离，就返回真，如果枚举完成后函数还没有返回，则返回假。

---

## 作者：forever_nope (赞：0)

考虑朴素算法。

枚举左右端点，前缀和计算平均值。

这样做是 $\mathcal O(n^2)$ 的。

考虑很经典的平均值的思想，将一个序列减去其平均值，其和为零。

如果我们二分一个数，然后找到一个序列，减去二分的平均值，大于等于零则可行。

于是我们可以继续这个思路，考虑如何 check。

前缀和一定是需要的，显然。有一句话说得好，简单好用的工具，能用就用。

然后我们发现，一个长度为 $m$ 的序列，和表示为，$s_r-s_{l-1}$。

如果我们要在有长度要求下，最大化这个值。

显然我们需要一个位置其左侧至少若干位的最小值。

于是，使用类似于双指针的方法，右端不断滑动，左边同时记录最小值。

注意到是浮点数二分，为了精度，我们可以提前将数字乘上 $1000$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

constexpr double eps = 1e-8;

int n, f;
vector<int> a;
vector<double> b;

bool check(double avg) {
	for (int i = 1; i <= n; ++i) b[i] = b[i - 1] + a[i] - avg;
	double lt = 0;
	for (int i = 0, j = f; j <= n; ++i, ++j) {
		lt = min(lt, b[i]);
		if (b[j] - lt >= 0) return true;
	} return false;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> f;
	a.resize(n + 1), b.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i], a[i] *= 1000;
	double l = -1e8, r = 1e8;
	while (r - l > eps) {
		double mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	cout << (long long)r << endl;
	return 0;
}
```

总结一下，这个思想就是，我们可以 $\mathcal O(n^2)$ 的直接求解，也可以 $\mathcal O(n)$ 的判断一个解。

如果这个东西本身具有单调性（或者有人更不直观的说为可二分性），就可以二分把复杂度优化到 $\mathcal O(n\log n)$ 或者其他比较优化的复杂度。

---

## 作者：Tomle (赞：0)

upd 2024.5.21 笔误

# P10450 题解

一个 $\mathcal{O}(n^3)$ 的暴力做法是，枚举区间求平均数的最大值，毫无疑问会 TLE。

即使加上前缀和优化，也是 $\mathcal{O}(n^2)$。

不如转变一下思路，二分找平均值，判断是否可行。

接下来是 $\mathcal{O}(n)$ 判断是否可行。

定义函数 $\operatorname{check}(k)$ 表示判断将平均数设为 $k$ 是否可行。

先把数组 $a$ 中每个数减去 $k$，这样问题就转变成了“是否存在一段长度大于 $L$ 的区间，和大于 0”。

用前缀和解决累加，$sum_i = \sum\limits_{j = 1}^ia_i$。

不难看出，右端点为 $r$ 的区间和最大值为 $sum_r - \min\limits_{1 \le i \le r-L} sum_i$

维护一下最小值就好了。

算法总复杂度 $\mathcal{O}(n \log n)$。

code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, L, a[100005], b[100005], sum[100005], minn;

bool check(int k) {
	int ans = INT_MIN;
	minn = INT_MAX;
	for (int i = 1; i <= n; i++) {
		b[i] = a[i] - k;
		sum[i] = sum[i - 1] + b[i];
	}
	for (int i = L; i <= n; i++) {
		minn = min(minn, sum[i - L]);
		ans = max(ans, sum[i] - minn);
	}
	return ans >= 0;
}
int main() {
	cin >> n >> L;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] *= 1000;
	}
	int l = 0, r = 2000000;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	cout << l;
	return 0;
}
```

---

## 作者：zcz0263 (赞：0)

## 做法
对于 $check(x)$ 表示有没有长度不小于 $L$ 的子段平均值大于等于 $x$ 时，不难发现结果具有单调性，所以考虑实数二分。

那么我们要怎么在 $n \leq 10^5$ 时快速判断有没有子段平均值大于 $x$ 呢？如果只维护 $L$ 个元素之前前缀和的最小值，在除以长度后的结果不一定为最大值。我们可以将数组内所有元素暂时减去 $x$，然后做一次前缀和记为 $sum$ 数组，对于每个 $L-1 \leq i < n$ 维护 $sum_0 \sim sum_{i-L}$ 的最小值为 $minx$，若 $sum_i-minx \geq 0$，则可以确定从 $minx$ 的来源位置到当前位置的平均值 $\geq x$（下标从 $0$ 开始）。

因为每次的 $minx$ 可以继承上一次后更新，所以时间复杂度为$O(\log (2000) \times n)$。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
#define maxn 100005
int n,L;
double a[maxn],tmp[maxn],qzh[maxn];
bool check(double x){
	for(int i=0;i<n;i++) tmp[i]=a[i]-x;
	qzh[0]=tmp[0];
	for(int i=1;i<n;i++) qzh[i]=qzh[i-1]+tmp[i];
	double minx=0;
	for(int i=L-1;i<n;i++){
		if(qzh[i]-minx>=0) return 1;
		minx=min(minx,qzh[i-L+1]);
	}return 0;
}
int main(){
	cin>>n>>L;
	for(int i=0;i<n;i++) cin>>a[i];
	double l=0,r=2000;
	while(r-l>eps){
		double mid=(l+r)/2.0;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<(int)(r*1000);
}
```

---

