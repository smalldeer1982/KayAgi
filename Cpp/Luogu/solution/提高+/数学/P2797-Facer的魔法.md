# Facer的魔法

## 题目背景

Facer 误闯入禁地，学会了魔法。

## 题目描述

Facer 闯入禁地之后，遇到了对手。

具体来说，Facer 魔法是一串数字。

但是 Facer 能力有限，这串数字只能从给定的 $n$ 个数中选择，能产生的魔法值为选择出的这些数字的平均数。

他的对手不会像 Facer 这样的强大的魔法，但是他会克制招数，即从 Facer 选出的数字中找出中位数，便是他的魔法值。

求 Facer 最多能克制对方多少点魔法。

一句话题意：给你 $n$ 个数，你可以选若干个数，使得平均数减中位数最大。

## 说明/提示

- 对于 $20\%$ 的数据，$n \leq 100$；
- 对于 $50\%$ 的数据，$n \leq 2000$；
- 对于 $100\%$ 的数据，$n \leq 10^5$，$0 \leq x_i \leq 10^6$。

## 样例 #1

### 输入

```
4
1 2 3 4```

### 输出

```
0.33```

## 样例 #2

### 输入

```
4
1 2 3 9```

### 输出

```
2.00```

## 样例 #3

### 输入

```
2
1 2```

### 输出

```
0.00```

# 题解

## 作者：lots_of_laugh (赞：11)

萌新第一篇题解QWQ

楼下大佬都是三分做的，实际上不用三分的QWQ

我们先对数组降(升)序排序

实际上对于每个中位数，要使平均数的最大，要么是只取中位数、最大数、小于中位数的最大数，要么是在由中位数分割的两个递增区间内，从大到小尽可能多取直到一个区间被取完

证明如下：设数组为不上升序列

A1>=A2>=A3......An......A2n-1
显然An是中位数

我们先取A1、An、An+1

平均数为(A1+An+An+1)/3，记为B1

我们再取A1、A2、An、An+1、An+2

平均数为(A1+A2+An+An+1+An+2)，记为B2

若要使B1<=B2
可以化简得到

(A1-A2)+(An+1-An+2)+An>=(A2+An+2)
但是我们没法判断这个不等式是否成立啊！

别急我们继续往下推，若要使Bm>=Bm-1
可以化简得到

(A1+A2+....+Am-1-(m-1)Am)+(An+1+An+2+....+An+m-1-(m-1)An+m)+An>=(Am+An+m)/2

由数组单调递减得，不等号左边随m增大而增大，右边随m增大而减小

也就是说，{Bn}要么先减后增，要么一直增，要么一直减！

这个时候大家很容易就想到用三分求解了，但是，我们不妨想一下我们如何求开口向上的二次函数在一个区间内的最大值

只要比较一下区间端点的函数值就可以了！

于是做法来了：排序，求前缀和，枚举每个数作为中位数，并找它的最大平均数，计入答案

附上弱鸡代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
int a[100010],s[100010];
int n;double ans;
void solve1(int mid)
{
	int midn=a[mid];
	double tot1=(double)(midn+a[mid-1]+a[n])/3.0;
	int maxl=mid-1,maxr=n-mid,num=min(maxl,maxr);
	double tot2=s[mid]-s[mid-num-1]+s[n]-s[n-num];//用前缀和快速算出全取情况下平均值 
	tot2/=(double)(2*num+1);
	ans=max(ans,max(tot1,tot2)-(double)midn);
	return;
}
void solve2(int rmid)
{
	int lmid=rmid-1;
	double midn=(double)(a[lmid]+a[rmid])/2.0;
	double tot1=(double)(a[n]+a[lmid-1]+a[lmid]+a[rmid])/4.0;
	int maxl=lmid-1,maxr=n-rmid,num=min(maxl,maxr);
	double tot2=s[rmid]-s[lmid-num-1]+s[n]-s[n-num];
	tot2/=(double)(2*num+2);
	ans=max(ans,max(tot1,tot2)-midn);
	return;
}
int main()
{
	scanf("%d",&n);
	for(ri i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(ri i=1;i<=n;i++)s[i]=s[i-1]+a[i];
	for(ri i=2;i<=n-1;i++)solve1(i);//取奇数个数时 
	for(ri i=3;i<=n-1;i++)solve2(i);//取偶数个数时 
	printf("%.2f",ans);//别忘了保留两位！ 
	return 0;
}
```
萌新第一篇题解 大佬们有错误帮忙改正啊QWQ

---

## 作者：XG_Zepto (赞：10)

## 思路

推广个人博客[【Codeforces 626E】 Simple Skewness / 题解](https://www.xgzepto.cn/post/codeforces-626e)

原题是这个：[【Codeforces 626E】 Simple Skewness](http://codeforces.com/problemset/problem/626/E)

题意：从数列里选出若干个数，使得他们的平均数减中位数最大。

这个问题有三个性质：

-  答案一定是非零数。因为你只选择一个数的时候，答案为0；
-  选出的数一定为奇数个。我们可以通过这个方法来证明：
	
假设原来我们选了$2k$个数，这些数升序排列是$a_1$ ~ $a_{2k}$,我们现在去掉$a_{k+1}$这个数，答案一定不会变劣。

设原来的平均数为$ av $，平均数的增量为：$$ΔAverage=\frac{av*2k-a_{k+1}}{2k-1}-av $$

中位数的增量为：$$ΔMedian=a_k-\frac{a_k+a_{k+1}}{2}$$

整理得：$$ΔAverage - ΔMedian = \frac{2av+(2k-1)(a_{k+1}-a_k)-a_{k+1}}{2(2k-1)}$$

上式显然大于零，证毕。

-  选定中位数后，向选定数列中添加新数字，一定是选择了两边可选的最大数。不断添加新数字，平均数的变化是先增后减的，所以我们可以通过二分找到它的峰值。

结合以上三点，算法就非常地显然了：枚举每一个中位数，然后二分找到对应的平均数的最大值，更新答案。

## 代码

用VS写的，提交的时候要记得注释掉第一个库。

```
// Facer's Magic.cpp: 定义控制台应用程序的入口点。
// XG_Zepto, 5/25/2018
// All rights reserved.
#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define mid (l+(r-l)/2)
#define ll long long
#define maxn 1000005 
ll s[maxn],a[maxn];
int n;
double ans;
using namespace std;
ll sum(int x,int l){
    return s[n]-s[n-l]+s[x]-s[x-l-1];
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+1+n);
    for (int i=1;i<=n;i++)
        s[i]=s[i-1]+a[i];
    for (int i=2;i<n;i++){
        int l=1,r=min(n-i,i-1);
        while(l<r){
            ll s1=sum(i,mid)*(2*mid+3);
            ll s2=sum(i,mid+1)*(2*mid+1);
            //为了避免精度问题，用乘法代替除法比较大小。
            if (s1>s2){
                r=mid;
            }
            else{
                l=mid+1;
                if (s1==s2) break;
            }
        }
        if (1.0*sum(i,l)/(2*l+1)-a[i]>ans)
            ans=1.0*sum(i,l)/(2*l+1)-a[i];
    }
    printf("%.2f",ans);
    //记得保留两位小数
    return 0;
}
```

---

## 作者：ButterflyDew (赞：5)

（楼下的证明实在是看不懂，逃

原题CF626E

很容易想到枚举一个中位数，但是如果选取的数字的个数是偶数个该怎么办呢？

下面证明选取奇数个时一定可以作为答案

当选取一个数字时，答案为0，所以最优答案不可能小于0，这点很重要

现在，我们假设选取了$2k$个有序的数成为了答案

## 设中位数为$M_0=\frac{a_k+a_{k+1}}{2}$,平均数为$A_0=\frac{\sum a}{2k}$

拿掉一个$a_{k+1}$后答案会变差吗

设拿掉一个$a_{k+1}$后

## $M_1=a_k,A_1=\frac{\sum a-a_{k+1}}{2k-1}$

## $\Delta M=M_1-M_0=\frac{a_k-a_{k+1}}{2}$

## $\Delta A=\frac{A_0-a_{k+1}}{2k-1}$

现在要证$\Delta A \ge \Delta M$

因为最优答案大于0，所以有

## $2 \times A_0 \ge a_k+a_{k+1}$

继续证明

## $\Delta A \ge \Delta M $

## $\Rightarrow \frac{A_0-a_{k+1}}{2k-1}+\frac{a_{k+1}-a_k}{2} \ge 0$

## $\Rightarrow \frac{2A_0-2a_{k+1}+(2k-1)(a_{k+1}-a_k)}{(2k-1) \times 2} \ge 0$

## $\Rightarrow a_k-a_{k+1} +(2k-1)(a_{k+1}-a_k) \ge 0$

这一步用了上面的东西，并把正的分母去掉了

## $\Rightarrow 2 \times (k-1)(a_{k+1}-a_k) \ge 0$

------------
然而仅仅枚举中位数，就算我们贪心每次选大的数也需要$O(n^2)$的时间啊

我们从枚举的中位数的左边第一位和右边最后一位 一位一位的向左多选

因为选取的数字越来越小，所以平均数的增量肯定越来越小，其实这个不那么显然，但是证起来比较麻烦

而大家基本上可以理解理解啦

增量减少，值一定有一个峰顶，这是一个单峰函数，我们可以通过三分法找到这个峰顶

注意在整数域上三分要注意边界问题

我们可以这么写
$lmid=(l*2+r)/3,rmid=(l+r*2+2)/3$

---

## 作者：zhn_666 (赞：4)

这四篇题解里面好像没有拿三分写得QAQ

我来补一个三分的代码把

首先题意很好理解，然后我们手玩几组数据

阔以证明一个结论，选择奇数个一定比选择偶数个更优，

比如你选了偶数个，我们把中间两个较大的数去掉，对平均数的影响

必然更小（阔以证明）~~楼下的大佬证的太好了，我就不献丑了~~

之后呢由于这题的数据范围决定了这个应该是个nlog的算法，

所以我们阔以枚举中位数，

之后用三分求最大值（因为这个题满足单峰函数的性质。)

之后就是三分板子题啦（我的题解好久不过了这次能不能过一个嘤）

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int a[100005];
int sum[100005];
double ans;
double max_1(double x,double y){return x>y?x:y;}
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline void solve(int tmp){//单峰函数，三分算法天下第一 
	int zhongwei=a[tmp];
	int l=1,r=min(tmp-1,n-tmp);
	int mid,midr;
	int maxx1,maxx2;
	double anss=0;
	while(r>l){
		mid=(l*2+r)/3;
		midr=(l+r*2+2)/3;
		maxx1=sum[n]-sum[n-mid]+sum[tmp]-sum[tmp-mid-1];
		maxx2=sum[n]-sum[n-midr]+sum[tmp]-sum[tmp-midr-1];
		if(maxx1*(2*midr+1)<maxx2*(2*mid+1)) l=mid+1;
		else r=midr-1;
	} 
	anss=(double)1.0*(sum[n]-sum[n-l]+sum[tmp]-sum[tmp-l-1])/(l*2+1);
	ans=max_1(ans,anss-(double)(1.0)*zhongwei);
}
int main(){
	n=read();
	sum[0]=0; 
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);//排序么么哒 
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	for(int i=2;i<=n-1;i++)solve(i);//枚举中位数 选择奇数个数字 
	printf("%.2lf",ans);
	return 0;
}

```


---

## 作者：lightup37 (赞：2)

咕值没了水篇题解.

我们有性质: 对于任意一个长度为偶数的子序列, 存在一个答案不劣于它的长度为奇数的子序列.

采用反证法证明: 假设某个长度为偶数的子序列成为了最优, 不妨假设其长度为 $2n$, 元素为$a_1, a_2, \cdots a_{2n}$ 且 $a_1 < a_2 < \cdots a_{2n}$. 有$n>0$, 否则任意选出一个长度为 1 的子序列即可举出反例. 那么他的答案就是$A = \frac{\sum\limits_{i=1}^{2n} a_i}{2n}-\frac{a_n+a_{n+1}}{2}$, 有 $A \ge 0$, 否则任意选择一个长度为 1 的子序列即可举出反例.

现在删去 $a_{n+1}$, 答案为 $B = \frac{\sum\limits_{i=1}^{2n} a_i-a_{n+1}}{2n-1}-a_n$.

有 $A-B = \sum\limits_{i=1}^{2n} \frac{1}{2n(2n-1)} a_i + \frac{a_{n+1}-a_n}{2} - \frac{a_{n+1}}{2n-1}$.

因为 $A \ge 0$, 所以$\sum\limits_{i=1}^{2n} \frac{1}{2n(2n-1)} a_i \ge \frac{a_n+a_{n+1}}{2(2n-1)}$.

所以 $A-B \ge \frac{a_n+a_{n+1}+(2n-1)(a_{n+1}-a_n)}{2(2n-1)} - \frac{a_{n+1}}{2n-1} = \frac{(n-1)(a_{n+1}+a_n)}{2n-1} \ge 0$.

排序后枚举中位数位置, 使用倍增算法 (使用观察法可得单峰性质) 即可在 $O(n\log n)$ 的时间复杂度下完成本题. 倍增常数小啊 qwq.

```cpp
#include<bits/stdc++.h>
#define f(i,x,y) for(int i=x, i##end=y; i<=y; ++i)
#define d(i,x,y) for(int i=y, i##end=x; i>=y; --i)
#define ll long long
#define _ 100005
char ch;
int rd() {
  int f=1, x=0; ch=getchar();
  while(!isdigit(ch)) { f=((ch=='-')?-1:f); ch=getchar(); }
  while(isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
  return x*f;
}
void rd(int& x) { x=rd(); }
using namespace std;
int a[_], sum[_], k, n; double Q;
int main() {
  rd(n); f(i,1,n) rd(a[i]);
  sort(a+1, a+1+n); f(i,1,n) sum[i]=sum[i-1]+a[i];
  f(i,1,n) {
    int x=0; double ans=0;
    for(int j=20; j>=0; --j) {
      int len=(1<<j)+x;
      if(i+len>n || i-len<=0) continue ;
      double A=double(sum[i-1]-sum[i-len-1]+sum[n]-sum[n-len]+a[i])/(2*len+1);
      if(A>ans) x=len, ans=A;
    }
    Q=max(Q, ans-a[i]);
  }
  printf("%.2lf\n", Q);
  return 0;
}
```

---

## 作者：TonyYin (赞：1)

## 题意

给定 $n$ 个非负整数，选一个子集，使得子集的平均值减去中位数最大。

求这个最大值。

## $\rm{Subtask}$ $\rm{1 - 50pts}$

因为需要考虑中位数，容易想到按照子集大小的奇偶性分类讨论。

#### 子集大小为奇数

先来考虑奇数的情况。

容易想到 $\mathcal{O}(n)$ 枚举中位数。

![](https://pic.tonyyin.top/2021/04/05/9b79d51da9e7a.png)

如上图，对数列按照升序排序。选定中位数后，我们每次从中位数左侧添加一个点，再从中位数右侧添加一个点。又因为我们想要子集的**平均值最大**，所以**贪心地，每次分别从两侧取一个最大的数**，也就是取最靠右的点，直到有一个区间被取完。

比如上图中，$(4, 10)$，$(3, 9)$，$(2, 8)$ 两两为一组，每次分别被取出。

于是对于每个中位数，只需要 $\mathcal{O}(n)$ **枚举两侧添加点的个数**，就可以确定出选取的情况，求出平均值与中位数的差。

这样可以得到整体复杂度为 $\mathcal{O}(n^2)$ 的算法，期望得分 $\rm{50pts}$.

#### 子集大小为偶数

##### 结论

对于大小为偶数的子集，观察可以得到结论：**对于任意大小为偶数的子集，一定存在大小为奇数的子集比其更优**，下面进行证明。

##### 分析

按照上面的贪心策略任取一个大小为奇数的子集，将其升序排序，设为 $\{a_1, a_2, \cdots a_{2n-1}\}$.

现在向子集中添加一个数，使其大小变为偶数。根据上面提到的**贪心策略**，新加入的数 $x$ 有以下两种情况：

1. $x$ 在 $a_1$ 左侧，即 $x\leq a_1$，
2. 紧邻中位数右侧，即 $a_n\leq x\leq a_{n+1}$.

在上面的图里，可以形象地看到，$x$ 的第一种情况是选择 $1$，第二种情况是在 $6, 7$ 中选一个。

第一种情况，显然不会使答案变大，因为 $x$ 对平均值的影响太大了。

对于第二种情况，下面进行详细证明。

##### 证明

为了方便，我们把加入 $x$ 后的数列重新升序排序，不妨设为 $\{b_1, b_2, \cdots b_{2n}\}$.

加入 $x$ 前的答案为：
$$
A=\frac{\sum_{i=1}^{2n}b_i-b_{n+1}}{2n-1}-b_{n}
$$
加入后的答案为： 
$$
B=\frac{\sum_{i=1}^{2n}b_i}{2n}-\frac{b_{n} + b_{n + 1}}{2}
$$


两者作差并化简后得到：
$$
A-B=\frac{\sum_{i=1}^{2n}b_i}{2n(2n-1)}+\frac{b_{n+1}-b_n}{2}-\frac{b_{n+1}}{2n-1}
$$
又因为 $B\geq 0$，所以：
$$
\frac{\sum_{i=1}^{2n}b_i}{2n}\geq \frac{b_n+b_{n+1}}{2}
$$
即：
$$
\frac{\sum_{i=1}^{2n}b_i}{2n(2n-1)}\geq \frac{b_n+b_{n+1}}{2(2n-1)}
$$
代入 $A-B$ 中得到：
$$
\begin{aligned}
A-B&\geq \frac{b_n+b_{n+1}}{2(2n-1)}+\frac{b_{n+1}-b_n}{2}-\frac{b_{n+1}}{2n-1}\\
&=\frac{b_n+b_{n+1}+(2n-1)(b_{n+1}-b_n)-2b_{n+1}}{2(2n-1)}\\
&=\frac{b_n+b_{n+1}+2n\cdot b_{n+1}-2n\cdot b_n-b_{n+1}+b_n-2b_{n+1}}{2(2n-1)}\\
&=\frac{(n-1)(b_{n+1}-b_n)}{(2n-1)}\geq 0
\end{aligned}
$$
于是我们证明了：加入 $x$ 前的答案一定不小于加入 $x$ 后的答案，也就是：**对于任意大小为偶数的子集，一定存在大小为奇数的子集比其更优**。

#### $\rm{50pts}$ 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10;
const int inf = 0x3f3f3f3f3f3f3f3f;
inline int read() {}//快读
int n, a[MAXN], sum[MAXN];
signed main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	double ans = (-1.0) * inf;
	for(int i = 1; i <= n; i++) {//枚举中位数，两侧同时添加点，尽可能靠右
        double mmax = (double)(a[i]);//只取中位数
        for(int j = 1; j <= min(i - 1, n - i); j++) {//subtask1 暴力枚举两侧加2*j个点
            int add_l = sum[i - 1] - sum[i - j - 1];
            int add_r = sum[n] - sum[n - j];
            mmax = max(mmax, (double)(add_l + add_r + a[i]) / (double)(2 * j + 1));
        }
        ans = max(ans, mmax - (double)(a[i]));
	}
	printf("%.2lf\n", ans);
	return 0;
}
```



## $\rm{Subtask}$ $\rm{2 - 100pts}$

考虑如何把时间复杂度优化到 $\mathcal{O}(n\log n)$ 级别。

$\mathcal{O}(n^2)$ 的做法中，我们先枚举中位数 $mid$，再枚举两侧添加的元素个数 $len$.

在此基础上，设第 $i$ 次添加的两个元素**下标**分别为 $x_i$ 和 $y_i$. 

当确定中位数时，答案只与平均值有关，考虑计算添加 $(x_i, y_i)$ 对平均值的贡献。

贡献，也就是添加这两个数之后，**平均值的变化量**，若平均值变大，则贡献为正，反之为负。

显然地，**随着 $i$ 的增长**，$a_{x_i}+a_{y_i}$ 会持续下降，**对平均值的贡献也会越来越少**。

我们最后一次选取的两个元素 $x_{len}, y_{len}$，必定满足贡献大于 $0$，并且是最接近 $0$ 的。

因此我们可以通过**二分**，找到贡献紧邻 $0$ 的右侧的数。

具体实现时，我们不需要准确地计算出每两个元素的贡献。若**加入两个元素后的平均值大于原数列的平均值，则贡献为正**，否则贡献为负。

这样就得到了 $\mathcal{O}(n\log n)$ 的算法，期望得分 $\rm{100pts}$.

## $\rm{100pts}$ 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10;
const int inf = 0x3f3f3f3f3f3f3f3f;
inline int read() {}//快读
int n, a[MAXN], sum[MAXN];
signed main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	double ans = (-1.0) * inf;
	for(int i = 1; i <= n; i++) {//枚举中位数，两侧同时添加点，尽可能靠右
        int l = 1, r = min(i - 1, n - i), mid;
        double mmax = (double)(a[i]);
        while(l <= r) {
            mid = (l + r) >> 1;
            int sum1 = sum[i - 1] - sum[i - mid] + sum[n] - sum[n - mid + 1];
            //j = mid - 1，即加入前的平均值
            int sum2 = sum[i - 1] - sum[i - mid - 1] + sum[n] - sum[n - mid];
            //j = mid，加入两个元素后的平均值
            if((double)(sum1 + a[i]) / (double)(2 * mid - 1) < (double)(sum2 + a[i]) / (double)(2 * mid + 1)) {
                //若贡献为正
                mmax = max(mmax, (double)(sum2 + a[i]) / (double)(2 * mid + 1));
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans = max(ans, mmax - (double)(a[i]));
	}
	printf("%.2lf\n", ans);
	return 0;
}
```



---

## 作者：A524 (赞：0)

先是证明取单数个一定比取偶数个要更优。（以下证明过程建议看下面的大佬）

再从小到大排序，枚举中位数，从 $1$ 到 $n$ 遍历一遍。

每次左边取1个，右边取1个。利用贪心的思想，每次都是两边最大值。

我们又可以通过证明发现这样取会有一个极值！

这时我们可以用三分或者是二分！

我这里采用二分，二分只需要比较 $f(x-1)$ 和 $f(x)$ 就行。如果前者小于等于后者，就把指针往前；否则指针往后！

最终，我们只需要取一个最大值即可。

总结一句：这题难点主要在于证明过程。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
long long a[100100],b[100100];
int i,n,l,r,mid,X;db maxn;
double f(int x){return db(b[n]-b[n-x]+b[i]-b[i-x-1])/db(x*2+1)-db(a[i]);}
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for (i=1;i<=n;i++) b[i]=b[i-1]+a[i];
	for (i=1;i<=n;i++){
		l=1;r=min(i-1,n-i);X=0;
		while (l<=r){
			mid=(l+r)>>1;
			if (f(mid-1)<=f(mid))
				l=mid+1,X=mid;
			else r=mid-1;
		}
		if (f(X)>maxn)
			maxn=f(X);
	}
	printf("%.2lf\n",maxn);
	return 0;
}
```


---

## 作者：benny (赞：0)

这题是**三分查**， n\*log3(n)。主要思想是：

在nlgn从小到大**排序**的基础下，

先O(n)确定一个中位数a[j]，

设左边右边各k个，则

k一定时，为了使平均数大，总和应当尽量大，所以肯定要选最后的k个数（因为越到后面越大）

即要选：a[j-k],a[j-k+1]..a[j-1]**;** a[j]** ;** a[n-k+1],a[n-k+2]..a[n]  共(2k+1)个数（可以看成长度为 k、1、k 的区间）

设k个数的平均数为p(k)，则函数p的执行只需借助前缀和，很快；

而且函数p一定是个单峰函数，三分查。再加上之前枚举中位数，一共  n\*log3(n)


至于为什么是单峰函数，读者自行证明

```pascal
const max=100000;
var
a,h:array[0..max] of longint;
n,i,tot,t,j,l,r,m1,m2:longint;
x:real;
function f(l,r:longint):longint;
begin
  exit(h[r]-h[l-1]);
end;
function p(l:longint):real;
begin
  exit( (a[j]+f(j-l,j-1)+f(n-l+1,n)) /(2*l+1) );
end;
function min(x,y:longint):longint;
begin
  if x<y then exit(x) else exit(y);
end;
procedure down(i:longint);
var j,t:longint;
begin
while i<=tot shr 1 do
begin
j:=2*i;
if (j<tot) and (a[j+1]<a[j]) then inc(j);
if a[i]>a[j] then
begin
t:=a[i];
a[i]:=a[j];
a[j]:=t;
i:=j;
end
else break;
end;
end;
begin           //writeln(maxlongint);
readln(n);
for i:=1 to n do read(a[i]);
tot:=n;
for i:=n shr 1 downto 1 do down(i);
for i:=1 to n do
begin
t:=a[1]; a[1]:=a[tot]; a[tot]:=t;
dec(tot);
down(1);
end;

  for i:=1 to n div 2 do
    begin
      t:=a[i]; a[i]:=a[n+1-i]; a[n+1-i]:=t;
    end;
   //for i:=1 to n do write(a[i],' ');  writeln
  h[0]:=0;
  for i:=1 to n do h[i]:=h[i-1]+a[i];

  x:=0;
  for j:=2 to n-1 do
    begin
      l:=1; r:=min(j-1,n-j);
      repeat
        m1:=l+(r-l+1) div 3;
        m2:=m1+(r-l+1) div 3;
        if ( p(l)>=p(m1) )and( p(m1)>=p(m2) )and( p(m2)>=p(r) ) then
          begin l:=l; r:=l end else
        if ( p(l)<=p(m1) )and( p(m1)>=p(m2) )and( p(m2)>=p(r) ) then
          begin l:=l; r:=m1 end else
        if ( p(l)<=p(m1) )and( p(m1)<=p(m2) )and( p(m2)>=p(r) ) then
          begin l:=m2; r:=r end else
        //if ( p(l)<p(m1) )and( p(m1)<p(m2) )and( p(m2)<p(r) ) then
          begin l:=r; r:=r end;
      until r-l=0;
      if p(l)-a[j]>x then x:=p(l)-a[j];
    end;
  writeln(x:0:2);
end.
```

前面一坨是堆排，

h是前缀和数组，

f(l,r)是区间l,r的和,

p(l)是 以a[j]为中位数、2l+1 个数的平均数(l相当于之前讲的k)

三分查查的就是之前讲的k


---

## 作者：dingshengyang (赞：0)

……该题解分为 $3$ part：


------------
1.证明单数比双数更优：

楼上比我巨，此处略去。


---------
2.贪心思想——我们要悄悄的干，悄悄的把平均数提高，然后饿死中位数。

解决方法：先选第一个，然后定义前指针 ```pos1```，后指针 ```pos2```，然后每次 ```pos1++;pos2--``` 取最大值。

$90$ pts code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 1e5 + 5;
int a[N];
double ans = 0,sum = 0;
int pos1 = 2,pos2 = n;
int cnt = 1;
int main(){
	cin >> n;
	for(int i = 1;i <= n;i ++)cin >> a[i];
	sort(a+1,a+n+1);
	pos2 = n;sum += (double)a[1];
	while(pos1 < pos2){
		cnt += 2;
		sum += a[pos1];
		sum += a[pos2];
		if(ans < (sum/double(cnt))-double(a[pos1])){
			ans = (sum/double(cnt))-double(a[pos1]);
		}
		pos1++;pos2--;
	}
	printf("%.2lf\n",ans);
	return 0;
}
```

---------

3.最后 $10$ 分

没法下样例诶……

（尝试 hack 自己 ing.JPG）

等会，答案（除了 $0$）好像都大于等于 $0.33$！好神奇！

为什么呢？

因为，假设排序后的结果是 $a_1,a_2,a_3...a_n$；

然后现在我们知道，答案一定大于等于 $0$。因为只要选一个数就行了。

重头戏来啦~ 首先现在我们有 $3$ 个数：$a_1,a_2,a_3$，并且 $a_1 \le a_2 \le a_3$。

分类讨论：

case $1$：$a_1=a_2=a_3$：那么答案为 $0$。

case $2$：$a_1=a_2<a_3$：因为都是整数，所以 $a_3-a_2\ge1$。平均数就是 $a_2+\frac{k}{3}$，其中 $k$ 是 $a_3-a_2$；中位数就是 $a_2$。由于 $a_3-a_2\ge1$，然后二者相减得 $\frac{k}{3}$，大于等于 $\frac{1}{3}$，四舍五入得 $0.33$。

case $3$：$a_1<a_2<a_3$：再分类讨论。


case $3.1$：$a_2-a_1<a_3-a_2$：因为都是整数，自然前面那个式子两项相差大于等于 $1$。然后答案大于等于 $\frac{1}{3}$。得 $0.33$。

case $3.2$：$a_2 - a_1 \ge a_3 - a_2$：答案不会比 $0$ 更优。讨论结束。

然后就乱搞 AC 啦~

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 1e5 + 5;
int a[N];
double ans = -12,sum = 0;
int pos1 = 2,pos2 = n;
int cnt = 1;bool WA=1;
int main(){
	cin >> n;
	for(int i = 1;i <= n;i ++)cin >> a[i];
	sort(a+1,a+n+1);
	if(n<=2){
		printf("0.00\n");
		exit(0);
	}
	pos2 = n;sum += (double)a[1];
	while(pos1 < pos2){
		cnt += 2;
		sum += double(a[pos1]);
		sum += double(a[pos2]);
		if(ans < (sum/double(cnt))-double(a[pos1])){
			ans = (sum/double(cnt))-double(a[pos1]);
		}
		pos1++;pos2--;WA = 0;
	}
	sum = double(a[n]);
	cnt = 1;
	pos1 = 1;
	pos2 = n-1;
	while(pos1 < pos2){
		cnt += 2;
		sum += double(a[pos1]);
		sum += double(a[pos2]);
		if(ans < (sum/double(cnt))-double(a[pos2])){
			ans = (sum/double(cnt))-double(a[pos2]);
		}
		WA = 0;
		pos1++;pos2--;
	}
	if(ans < 0)ans = 0.33;
	printf("%.2lf\n",ans);
	return 0;
}
```

---

