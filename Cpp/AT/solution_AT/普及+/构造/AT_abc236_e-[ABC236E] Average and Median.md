# [ABC236E] Average and Median

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc236/tasks/abc236_e

$ N $ 枚のカードがあり、$ i\ \,\ (1\ \leq\ i\ \leq\ N) $ 番目のカードには整数 $ A_i $ が書かれています。

高橋君は、これらのカードから好きな枚数選びます。ただし、各 $ i\ \,\ (1\ \leq\ i\ \leq\ N\ -\ 1) $ について、$ i $ 番目のカードと $ i\ +\ 1 $ 番目のカードの少なくとも一方を選ぶ必要があります。

以下の値を求めてください。

- 選んだカードに書かれた整数の平均値としてあり得る最大値
- 選んだカードに書かれた整数の中央値としてあり得る最大値

ただし、$ n $ 個の整数の中央値は、それらのうち小さい方から数えて $ \lceil\ \frac{n}{2}\ \rceil $ 番目であるものとします。ここで、$ \lceil\ x\ \rceil $ は $ x $ 以上の最小の整数を表します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^{9} $
- 入力は全て整数である。

### Sample Explanation 1

$ 2 $ 番目、$ 4 $ 番目、$ 6 $ 番目のカードを選ぶと、書かれた整数の平均は $ \frac{12}{3}\ =\ 4 $ となり、これが最大です。 $ 1 $ 番目、$ 3 $ 番目、$ 5 $ 番目、$ 6 $ 番目のカードを選ぶと、書かれた整数の中央値は $ 2 $ となり、これが最大です。

### Sample Explanation 2

平均値の出力については誤差が認められるので、例えば $ 5.2491 $ と出力しても正答とみなされます。ただし、中央値は正確な値を出力しなければなりません。

## 样例 #1

### 输入

```
6
2 1 2 1 1 10```

### 输出

```
4
2```

## 样例 #2

### 输入

```
7
3 1 4 1 5 9 2```

### 输出

```
5.250000000
4```

# 题解

## 作者：chengning0909 (赞：10)

# abc 236 e

## 题意

$n$ 个数 $a_{1} \dots a_n$ 排成一列。现在要选出一些数，满足 **任意两个相邻的数中至少有一个数被选择**。

请求出：

- 所有选择方案中，被选中的数字平均值的最大值，误差在 $10 ^ {-3}$ 以内视为正确；

- 所有选择方案中，被选中的数字中位数的的最大值。在这里，偶数 $2k$ 个数的中位数视作第 $k$ 小的数。

- $2 \le n \le 10 ^ 5$

- $1 \le a_i \le 10 ^ 9$

## 思路

二分 + dp

### 平均值

二分平均值（实数二分），$Check(x)$ 表示平均值为 $x$ 是否合法。

所以，我们设选择的数的下标为 $p_1, p_2, \dots , p_k$，那么就有：

$$\frac{a_{p_1} + a_{p_2} + \dots + a_{p_k}}{k} \ge x$$

$$\frac{a_{p_1} + a_{p_2} + \dots + a_{p_k}}{k} - x \ge 0$$

$$\frac{(a_{p_1} - x) + (a_{p_2} - x) + \dots + (a_{p_k} - x)}{k} \ge 0$$

$$(a_{p_1} - x) + (a_{p_2} - x) + \dots + (a_{p_k} - x) \ge 0$$

所以，$b_i = a_i - x$，$dp_i$ 表示子序列末尾为 $b_i$ 的满足要求的子序列的最大子序列和。

那么有转移：$dp_i = \max(dp_{i - 1}, dp_{i - 2}) + b_i$。

### 中位数

二分中位数（整数二分），$Check(x)$ 表示中位数为 $x$ 是否合法。

我们将小于 $x$ 的数都看做成 $-1$，大于等于 $x$ 的数看作 $1$，用序列 $b$ 记录这些映射后的值。

如果要使得中位数可以是 $x$，就是使得满足要求的子序列的和大于 $0$。

那么，$dp_i$ 为以 $b_i$ 结尾的满足要求的子序列的最大子序列和。

所以就有转移：$dp_i = \max(dp_{i - 1}, dp_{i - 2}) + b_i$。

---

## 作者：jerry1717 (赞：6)

## [ABC236E] Average and Median 题目做法

这道题大致上就是一道二分与 dp。赛时只调了半个小时就出来了。

首先是二分平均数，可是像本题有后效性，我们不好直接判断。所以，我们可以稍微变化一下。
$$
	\sum_{i=1}^{k}a_i\le k\times mid 
$$

$$
	\sum_{i=1}^{k}a_i-mid\le0
$$
其中，$\sum_{i=1}^{k}a_i-mid$ 可以通过 dp 计算。$f_{i,1}$ 表示前 $i$ 个中选第 $i$ 个的最大值，$f_{i,0}$ 表示前 $i$ 个不选第 $i$ 个的最大值。

明显有转移方程:

$$

f_{i,1}=\max(f_{i-1,0}+a_i-mid,f_{i-1,1}+a_i-mid) , f_{i,0}=f_{i-1,1}

$$

然后中位数也是一样的二分，如果 $a_i \ge mid$，$a_i$ 就赋值为 $1$ 反之则赋值为 $-1$，然后跑一遍 dp ,最后判断结果是否大于 $1$ 就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double a[100001],f[100001][2];//记得开double
bool cheak(double x){//注意类型
	memset(f,0,sizeof(f));//初值一定要赋
	for(int i=1;i<=n;i++){
		f[i][0]=f[i-1][1];
		f[i][1]=max(f[i-1][0]+a[i]-x,f[i-1][1]+a[i]-x);
	}
	return max(f[n][1],f[n][0])>=0;
}
bool chaek(int x){
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		if(a[i]>=x) f[i][1]=max(f[i-1][0]+1,f[i-1][1]+1);
		else f[i][1]=max(f[i-1][0]-1,f[i-1][1]-1);//开始转移
		f[i][0]=f[i-1][1];
	}
	return max(f[n][1],f[n][0])>=1;//注意是大于等于1,因为是向前取中位数
}
int main(){
	scanf("%d",&n);
	double l=0,r=0;
	int r1=0,l1=0;
	for(int i=1;i<=n;i++){
		scanf("%lf",&a[i]);
		r=max(a[i],r);
		r1=max(r1,(int)a[i]);//必须要强制转换
	}
	while(r-l>=0.00001){//精度开高一点好
		double mid=(l+r)/2;//注意变量类型
		if(!cheak(mid))r=mid-0.00001;
		else l=mid+0.00001;
	}
	while(l1<=r1){
		int mid=(l1+r1)/2;
		if(!chaek(mid))r1=mid-1;
		else l1=mid+1;
	}
	printf("%lf\n%d",r,r1);//注意输出r不是L
}
```

---

## 作者：2huk (赞：4)

> 给定一个长度为 $n$ 的序列 $\{a_i\}$。你需要从中选出若干个数，使得任意两个相邻的数中至少有一个数被选择。分别求选出的数的最大的平均值和中位数。

均为二分答案。先看平均值。

若当前二分的答案为 $x$，那么需要判断「是否存在一种方案，使得平均值大于等于 $x$」。也就是说若令选出来的数的下标为 $(i_1, i_2, \dots, i_k)$，则需要满足：

$$
\dfrac{\sum_{j = 1}^k a_{i_j}}k \ge x
$$

移项有：

$$
\sum_{j = 1}^k (a_{i_j} - x) \ge 0
$$

所以令 $b_i = a_i - x$，然后需要选择若干个 $b_i$，使得它们的和大于等于 $0$，而且还需要满足「任意两个相邻的数中至少有一个数被选择」这个条件。

显然 DP。令 $f_i$ 表示在 $1 \sim i$ 中选数，且 $b_i$ 一定选的最大的和。那么 $b_{i - 1}$ 是否选择无所谓（因为 $b_i$ 已经选了），所以转移 $f_i = \max(f_{i - 1}, f_{i - 2}) + b_i$。然后判断是否 $\max(f_n, f_{n - 1}) \ge 0$ 即可。

中位数类似。仍然二分答案 $x$，然后重新令 $b_i = \left\{\begin{matrix} 1 & a_i \ge x\\ -1 & a_i < x\end{matrix}\right.$，DP 不变，然后判断是否 $\max(f_n, f_{n - 1}) > 0$ 即可。

[代码](https://atcoder.jp/contests/abc236/submissions/49212768)。

---

## 作者：qzmoot (赞：3)

# [ABC236E] Average and Median
## 题目介绍
给你一个序列，你每次必需取相邻两个数中的一个数。让你求：

1. 这些数的平均数最大是多少。
2. 这些数的中位数最大是多少。

## 分析
我们发现如果要我们通过计算得出的十分困难，但恰巧，我们发现这题我们是可以二分答案，然后再来求解的。
### 平均数
题目中说的平均数可以是小数的，所以我们得写一个实数二分。然后，通过平均数的概念，我们知道，集合的总和是等于集合中的元素个数乘上平均数的。就可以把题目转化成，将集合中的每一个数都减去平均数，再求一个子序列的和能否大于等于 $0$。

这个看起来就可以 dp，状态设计为选择第 $i$ 的时候，目前的最大子序列减去平均数的值为多少。因为我们是一定选择第 $i$ 个的，所以就可以从第 $i-1$ 和 $i-2$ 个中的最大值来转移，再加上一个 $a[i]-mid$ 就行了。

转移方程式即为：$f_i=\max(f_{i-1},f_{i-2})+1.0\times a_i-mid$。
### 中位数
对于中位数，我们有一个很好的转化技巧，对于小于中位数的数，我们设它的贡献为 $-1$；等于中位数的数，我们设它的贡献为 $0$；大于中位数的数，我们设它的贡献为 $1$。那么这个序列所有数的贡献加起来是一定为 $0$ 的。

但是因为序列长度为偶数的时候，中位数是第 $\frac{k}{2}$ 大的。所以我们把等于中位数的数也设成 $1$ 即可，最后的判断条件就变成了大于等于 $1$。

转移方程即为：$f_i=\max(f_{i-1},f_{i-2})+calc(a_i,mid)$，$calc$ 为上面所讲的判断方法。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,a[N];
int mx,mn=1e9;
double ans1,dp[N];
int ans2;
bool chk1(double mid)
{
	for(int i=1;i<=n;i++)
		dp[i]=max(dp[i-1],dp[i-2])+1.0*a[i]-mid;
	return max(dp[n],dp[n-1])>=0;
}
int f[N];
bool chk2(int mid)
{
	for(int i=1;i<=n;i++)
		f[i]=max(f[i-1],f[i-2])+(a[i]>=mid?1:-1);
	return max(f[n],f[n-1])>=1;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),mx=max(mx,a[i]),mn=min(mn,a[i]);
	double l=1.0*mn,r=1.0*mx;
	for(int i=1;i<=200;i++)
	{
		double mid=(l+r)/2;
		if(chk1(mid))
			l=mid,ans1=mid;
		else
			r=mid;
	}
	printf("%.4lf\n",ans1);
	int ll=mn,rr=mx;
	while(ll<=rr)
	{
		int mid=ll+rr>>1;
		if(chk2(mid))
			ll=mid+1,ans2=mid;
		else
			rr=mid-1;
	}
	printf("%d",ans2);
	return 0;
}
```

---

## 作者：masonpop (赞：2)

简单题。

对于第一问，考虑二分答案。然后给所有数减去 $x$。问题转化为满足一定限制的子序列元素和能否 $\ge 0$。很典的 dp。设 $f_i$ 表示以 $i$ 结尾的最大值，转移式 $f_i=\max\{f_{i-1},f_{i-2}\}+(a_i-x)$。

对于第二问，仍然二分答案。然后就和 [CF1486D](https://www.luogu.com.cn/problem/CF1486D) 几乎一样了。二分中位数 $x$，令 $b_i=\begin{cases}
 1,a_i\ge x\\
 -1,\text{otherwise}
\end{cases}$ 

此时就是问是否存在 $b$ 的一个满足条件的子序列使得和 $>0$。仿照上面的 dp 即可。

注意一个是实数二分，一个是整数二分。卡精度，用 `long double`。还有二分中途可能越界，开 `long long`。复杂度 $O(n\log \epsilon^{-1})$。[代码](https://www.luogu.com.cn/record/125085552)。

---

## 作者：GZXUEXUE (赞：1)

### 思路

观察到两问都要求满足条件的最大值，满足单调性，且答案较大，考虑使用二分。

#### 第一问

对于第一问，我们应使用**实数**二分。根据平均数的概念（数列中所有数之和除以数列中数的数量），我们可以把「能否使选出的数的平均数是这个数」转换为「将选出的数都减去平均数后总和是否大于 $0$」。那么，根据这个变形后的问题，我们可以考虑使用 dp 求解。

据第一问变形后的题面，我们设 $f_{i,j}$ 表示当前选到第 $i$ 个数，第 $i$ 个数选或不选（当  $j = 0$ 时不选，$j = 1$ 时选），易得状态转移方程为：

$$
f_{i,j} = 
\begin{cases}
f_{i-1,1} & \operatorname{if} j = 0 \\
\max(f_{i-1,0},f_{i-1,1}) + (a_i - avg) & \operatorname{if} j = 1
\end{cases}
$$

其中 $avg$ 表示我们枚举出来的平均数。

#### 第二问

跟第一问一样，我们可以试着转化问题。我们把比我们当前枚举的中位数与 $a_i$ 相比较，小于它的记作 $-1$，否则记作 $1$。要使中位数为我们当前枚举的中位数，那么最后我们记下的序列总和应当大于 $0$。

根据这个变形后的问题，我们仍然可以考虑使用 dp 求解。我们设 $f_{i,j}$ 表示当前选到第 $i$ 个数，第 $i$ 个数选或不选（当  $j = 0$ 时不选，$j = 1$ 时选），易得状态转移方程为：

$$
f_{i,j} = 
\begin{cases}
f_{i-1,1} & \operatorname{if} j = 0 \\
\max(f_{i-1,0},f_{i-1,1}) + x_i & \operatorname{if} j = 1
\end{cases}
$$

其中 $x_i$ 表示我们记下的第 $i$ 个数字（$1$ 或 $-1$）。

总的来说，这个程序的复杂度为 $O(n \log m)$，其中 $m = 10^9$。

### 实现

```cpp
# include <iostream>
using namespace std;
const double eps = 1e-5;
int n,MAx,a[100005],f2[100005][2]; double f1[100005][2];
bool check1(double avg){
	for (int i = 1;i <= n;i++){
		double num = (double)a[i] - avg;		
		f1[i][0] = f1[i-1][1],f1[i][1] = max(f1[i-1][0],f1[i-1][1]) + num;
	}return max(f1[n][0],f1[n][1]) >= 0;
}bool check2(int mid){
	for(int i = 1;i <= n;i++){
		int num;
		if (a[i] > mid) num = 1;
		else num = -1;
		f2[i][0] = f2[i-1][1],f2[i][1] = max(f2[i-1][0],f2[i-1][1]) + num;
	}return max(f2[n][0],f2[n][1]) >= 1;
}void quest1(){
	double l = 0,r = 1e9;
	while (r - l >= eps){
		double mid = (l + r) / 2.00;
		if (check1(mid)) l = mid;
		else r = mid;
	}cout << l << endl;
}void quest2(){
	int l = 1,r = 1e9;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (check2(mid)) l = mid + 1;
		else r = mid - 1;
	}cout << l;
}int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n; for (int i = 1;i <= n;i++) cin >> a[i];
	quest1(); quest2();
	return 0;
}
```

---

## 作者：ttq012 (赞：1)

先考虑第一问。

设 $f_{i,0/1}$ 表示前面的 $i-1$ 个数选完了，现在选第 $i$ 个数，选择第 $i$ 个数或者不选择第 $i$ 个数。

那么有转移方程 $f_{i,0}=\max(f_{i-1,0},f_{i-1,1})+b_i$，$f_{i,1}=f_{i-1,0}$。

然后二分。

对于每一个二分得到的 $\rm{mid}$ 构造一个数组 $b$，满足 $b_i=a_i-\rm{mid}$。然后执行上面的 dp。如果 $\max({f_{n,0},f_{n,1}})\ge 0$，那么平均值就 $\ge k$。否则就 $<k$。

时间复杂度 $O(n\log n)$。

第二问也同理。二分得到的每一个 $\rm{mid}$，$b$ 数组满足当 $a_i\ge \rm{mid}$ 的时候 $b_i = 1$，否则 $b_i=-1$。然后dp，判断 $\max({f_{n,0},f_{n,1}})$ 是否 $> 0$ 即可。

时间复杂度也是 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
double a[N],b[N],f[N][2];
int n;
bool check(double x){
  for(int i=1;i<=n;i++){
    f[i][0]=max(f[i-1][0],f[i-1][1])+b[i];
    f[i][1]=f[i-1][0];
  }
  return max(f[n][0],f[n][1])>0;
}
signed main(){
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i];
  double l=0,r=1e9,best=-1;
  for(int c=1;c<=250;c++){
    double mid=(l+r)/2;
    for(int i=1;i<=n;i++)
      b[i]=a[i]-mid;
    if(check(mid))
      l=mid,best=mid;
    else
      r=mid;
  }
  cout<<best<<'\n';
  int ll=0,rr=1e9,bestbb=-1;
  while(ll<=rr){
    int mid=ll+rr>>1;
    for(int i=1;i<=n;i++)
      if(a[i]>=mid)b[i]=1;
      else b[i]=-1;
    if(check(mid)){
      ll=mid+1,bestbb=mid;
      // if(mid==5){
      //   cout<<'\n';
      //   for(int i=1;i<=n;i++)
      //     cout<<f[i][0]<<' '<<f[i][1]<<'\n';
      //   cout<<'\n';
      // }
    }
    else
      rr=mid-1;
  }
  cout<<bestbb<<'\n';
  return 0;
}
```



---

## 作者：YuYuanPQ (赞：0)

## 平均值

看到题目中的最值，首先想到二分答案（即分别二分平均值和中位数）。

思考一下二分里的 $\text{check}$ 函数。

看到选择的限制条件：“任意两个相邻的数中至少有一个数被选择”。\
这显然是 DP，转化一下题意大概就是：求最大的子序列和，但是对于第 $i$ 位，$i-1$ 或 $i-2$ 是必须选择其一的。

对于二分到的 $mid$，其需要满足的条件是（此处令数组 $b$ 包含了选中的数，其长度为 $l$）：
$$\frac{\sum\limits_{i=1}^{l}b_i}{l}\geq mid$$
移项：
$$\sum\limits_{i=1}^{l}b_i\geq l\times mid$$
再变一下：
$$\sum\limits_{i=1}^{l}(b_i-mid)\geq 0$$

这个时候 DP 一下。
设 $f_i$ 表示到第 $i$ 位所有子序列的和（准确来说是转化后的值）的最大值，那么状态转移方程就呼之欲出了：$f_i=\max(f_{i-1},f_{i-2})+a_i-x$。

为啥是对 $f_{i-1}$ 和 $f_{i-2}$ 取最大值呢？因为题目限制必选其一，那就选最大的一个。\
最后判断 $\max(f_n,f_{n-1})\geq 0$，之所以是 $2$ 个是因为最后一个是可以不选的。

## 中位数
同理，用二分和 DP。

看了题解区的处理方法，感觉挺妙：对于小于中位数的，将其转化为 $-1$；而大于等于的，则转化为 $1$。解释一下：之所以等于的也要是 $1$，是因为本题长度为偶数时不是常规的中位数计算方法，而是以左边的为中位数，在最后判断的时候判断是否 $\geq 1$ 即可。

设 $dp_i$ 表示到第 $i$ 位所有子序列（转化后的值）的最大值。\
同理，判断 $\max(dp_n,dp_{n-1})\geq 1$。

## Code
[Link](https://atcoder.jp/contests/abc236/submissions/62201218)

---

## 作者：Louis_lxy (赞：0)

二分加朴素 dp。

对于第一问，显然十分套路，$\frac{\sum_{i=1}^n a}{n}\ge k$ 成立当且仅当 $(\sum_{i=1}^n a-k)\ge0$，于是二分之后将整个序列减去 $mid$ 然后 dp 就好了，状态就是这个数选或者不选，选的话上一个数可选可不选，不选上一个数一定要选，然后就完成了。

对于第二问，我们将大于 $k$ 的值记作 $1$，小于等于 $k$ 的值记做 $-1$，然后用上面的 dp 判断是否存在一个子序列大于 $k$ 的数大于 $0$。

然后这题就做完了，很水的题目。

---

## 作者：WaterSun (赞：0)

# 思路

直接将输出的答案分为两个分考虑。

## (1)

考虑二分 + DP。

设当前二分出的平均数为 $x$，如果合法，那么有（其中 $p$ 为选出数下标的集合）：

$$
\frac{a_{p_1} + a_{p_2} + \dots + a_{p_k}}{k} \geq x
$$

即：

$$
\frac{(a_{p_1} - x) + (a_{p_2} - x) + \dots + (a_{p_k} - x)}{k} \geq 0
$$

所以：

$$
(a_{p_1} - x) + (a_{p_2} - x) + \dots + (a_{p_k} - x) \geq 0
$$

不妨令 $A_i = a_i - x$，那么 $dp_i$ 表示在 $A$ 的前 $i$ 个数中选，并且必须选 $A_i$ 的最大子序列和（在满足题意的情况下）。

那么，得出状态转移方程：

$$
dp_{i} = \max(dp_{i - 1},dp_{i - 2}) + A_i
$$

最后，如果 $\max(dp_n,dp_{n - 1}) \geq 0$ 说明当前的 $x$ 合法。

## (2)

同理，二分 + DP。

设当前二分出的中位数为 $x$。

1. 如果 $a_i < x$，令 $B_i = -1$。

2. 否则，令 $B_i = 1$。

那么 $dp_i$ 表示在 $B$ 的前 $i$ 个数中选，并且必须选 $A_i$ 的最大子序列和（在满足题意的情况下）。

如果 $\max(dp_n,dp_{n - 1}) > 0$ 说明当前的 $x$ 合法。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
const double eps = 1e-6;
int n;
double arr[N],A[N],dp1[N];
int B[N],dp2[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline bool check1(double x){
	for (re int i = 1;i <= n;i++) dp1[i] = max(dp1[i - 2],dp1[i - 1]) + A[i];
	return max(dp1[n],dp1[n - 1]) >= 0;
}

inline bool check2(double x){
	for (re int i = 1;i <= n;i++) dp2[i] = max(dp2[i - 2],dp2[i - 1]) + B[i];
	return max(dp2[n],dp2[n - 1]) > 0;
}

int main(){
	n = read();
	for (re int i = 1;i <= n;i++) scanf("%lf",&arr[i]);
	double l = 0,r = 1e9;
	while (r - l > eps){
		double mid = (l + r) / 2;
		for (re int i = 1;i <= n;i++) A[i] = arr[i] - mid;
		if (check1(mid)) l = mid;
		else r = mid;
	}
	printf("%.4lf\n",l);
	int ll = 0,rr = 1e9;
	while (ll < rr){
		int mid = ll + rr + 1 >> 1;
		for (re int i = 1;i <= n;i++){
			if (arr[i] >= mid) B[i] = 1;
			else B[i] = -1;
		}
		if (check2(mid)) ll = mid;
		else rr = mid - 1;
	}
	printf("%d",ll);
	return 0;
}
```

---

