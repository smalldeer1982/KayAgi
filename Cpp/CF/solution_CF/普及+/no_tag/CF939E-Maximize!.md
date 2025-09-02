# Maximize!

## 题目描述

You are given a multiset $ S $ consisting of positive integers (initially empty). There are two kind of queries:

1. Add a positive integer to $ S $ , the newly added integer is not less than any number in it.
2. Find a subset $ s $ of the set $ S $ such that the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF939E/6f55d1af0b4bb2f506e26b52edc60c22c6c89cc4.png) is maximum possible. Here $ max(s) $ means maximum value of elements in $ s $ , ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF939E/41a32d216cf052c5a047afb797c2b693c1941a38.png) — the average value of numbers in $ s $ . Output this maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF939E/6f55d1af0b4bb2f506e26b52edc60c22c6c89cc4.png).

## 样例 #1

### 输入

```
6
1 3
2
1 4
2
1 8
2
```

### 输出

```
0.0000000000
0.5000000000
3.0000000000
```

## 样例 #2

### 输入

```
4
1 1
1 4
1 5
2
```

### 输出

```
2.0000000000
```

# 题解

## 作者：DarkMoon_Dragon (赞：8)

# $CF939E$ Maximize!

## 题意
+ 对于一个只包含正整数的 $multiset$ $S$，你需要支持以下 2 种操作：
    1. 加入一个新数 $x$ 到 $S$ 中，满足加入的数是递增的;
    2. 找出 $S$ 的一个子集 $s$ ，使其 $max(s)-mean(s)$ 最大，并输出这个最大值。

## $Solution$
+ 比较显然的贪心，为了避免错误，考虑证明。

###### 猜想**对于一个加入的新数一定要选**。

> $Proof$   
+ 原式 $ans=Max-\frac{sum}{n}$ 
+ 考虑用新的最大替换掉原来的最大，设新的最大比原来最大大 $\Delta(x)$
$$ans=\frac{(Max+\Delta(x))\times n-(sum+\Delta(x))}{n}$$
+ 因为 $n\geq 1$，$ans$一定变大（优秀）

###### 猜想对于集合 $s$ 剩下的数，一定是**选前面几个小的数**，并且选的数的个数是**单调不减**的。

+ 可以意会一下证明，一定是选比当前集合平均数小的数加进来，使平均数更小，答案才会变得更大。

> $Proof$
+ 原式 $ans=Max-\frac{sum}{n}$ 
+ 考虑新加一个数 $\Delta(x)$
+ 新的式子 $ans=Max-\frac{sum+\Delta(x)}{n+1}$
+ 若新式减去原式$>0$，则新式更优秀
+ 新式减原式得 
+ $$-\frac{sum+\Delta(x)}{n+1}+\frac{sum}{n}$$
+ 等于 
+ $$\frac{sum-n\times \Delta(x)}{n\times(n+1)}>0$$
+ 得出更优秀条件为：$sum-n\times \Delta(x)>0$，即 $\Delta(x) <\frac{sum}{n}$
+ 两种贪心方案证毕（~~感觉比官方简洁许多~~）。尺取法统计答案即可。
+ 代码就特别~~简洁~~了。

```cpp
const int N = 5e5 + 50;
int op;
ll sum = 0;
ll maxn, l;
int sz;
ll a[N];
int main() {
    int q = read();
    while (q--) {
        op = read();
        if (op == 1) {
            a[++sz] = read();
            sum += (a[sz] - maxn);
            maxn = a[sz];
            while (l < sz && a[l + 1] * (l + 1) < sum) {
                sum += a[++l];
            }
        } else {
            double ans = maxn - double(sum) / double(l + 1);
            printf("%.14lf\n", ans);
        }
    }
}
```


---

## 作者：Ayano_Kimishima (赞：4)

# 二分做法
## 思考：
显然，每次集合都包含当前最大值。~~如果不明白为什么要包含最大值，可以看看其他题解的说法，这里不多说了~~。于是问题转化为了包含最大值时，平均数最小的问题。我们应该尽可能取小的数使平均数更小。

## 做法：
考虑前缀和统计，再遍历一遍所有数使平均值最小。但是这样子的时间复杂度是 $O(n^2)$ 的，一定会超时，那么我们要如何优化呢？再看看题目，保证数是递增的，这很容易让人想到**二分**，用二分优化，时间复杂度为 $O(n\log_2n)$。

### 最后得到AC代码如下：

```cpp
#include<iostream>
#include<algorithm> 
using namespace std;
double st[500005],summ[500005];
int top;
int main()
{
	int q;
	cin>>q;
	while(q--)
	{
		int opt,cnt=1;
		double x;
		cin>>opt;
		if(opt==1)
		{
			scanf("%lf",&x); 
			st[++top]=x;
			summ[top]=summ[top-1]+x;//前缀和
		}
		else
		{
			double ping=st[top];//初始化时平均数为最大值
			int mid,l=1,r=top;
			while(l<r)//二分
			{
				mid=l+r>>1;
				if((summ[mid]+st[top])/(mid+1)*1.0>(summ[mid+1]+st[top])/(mid+2)*1.0)//如果再多取一个数平均值会更小，就再多取一点
					l=mid+1;
				else
					r=mid;
			}
			printf("%.10llf\n",st[top]-(summ[r]+st[top])/(r+1)*1.0);
		}
	}
	return 0;
}
```

---

## 作者：培淇2021 (赞：3)

贪心好题。

因为这道题比较数学，所以要用数学的方式证一下。

（证明下方都有证明的结论，不想看证明的可以直接往下看）

用到的符号：

$A/B:A/B=\{x|x\in A,x \notin B\}$

$S_{\max}:{\exists} S_{\max}\in S,{\forall} x_0\in S/\{S_{\max}\},x_0\le S_{\max}$

$\displaystyle S_{len}:S_{len}=\sum^{x\in S}1$

$\displaystyle S_{sum}:S_{sum}=\sum^{x\in S}x$

$\displaystyle S_{avg}:S_{avg}=\dfrac{\sum^{x\in S}x}{\sum^{x\in S}1}$

------

猜想一：$f(S)=S_{\max}-S_{avg},f(S)>f(S/{S_{\max}})$

证：

设 $\Delta=S_{\max}-(S/{S_{\max}})_{\max}$

${\because}f(S)=S_{\max}-S_{avg}$

$=\dfrac{S_{len}((S/{S_{\max}})_{\max}+\Delta)-((S/{S_{\max}})_{sum}+\Delta)}{S_{len}}$

$=\left((S/{S_{\max}})_{\max}-\dfrac{(S/{S_{\max}})_{sum}}{(S/{S_{\max}})_{len}+1}\right )+\dfrac{S_{len}-1}{S_{len}}\times \Delta$

${\because}(S/{S_{\max}})_{\max}-\dfrac{(S/{S_{\max}})_{sum}}{(S/{S_{\max}})_{len}+1}\gt f(S/{S_{\max}}),S_{len}\ge 1$

${\therefore}f(S)>f(S/{S_{\max}})$

**结论一：一定要选新加入的数**

------

猜想二：$T=S/{S_{\max}},{\forall} x_{0}\in Z,x_{0} \le T_{\max},f(T\cup \{x_{0}\})>f(T)\Rightarrow x_{0}<T_{avg}$

证：

${\because}f(T)=T_{\max}-\dfrac{T_{sum}}{T_{len}}$

${\because}f(T\cup \{x_{0}\})=T_{\max}-\dfrac{T_{sum}+x_{0}}{T_{len}+1}$

${\therefore}f(T\cup \{x_{0}\})>f(T)\Leftrightarrow f(T\cup \{x_{0}\})-f(T)\ge 0$

$\Leftrightarrow\dfrac{T_{sum}}{T_{len}}-\dfrac{T_{sum}+x_{0}}{T_{len}+1}\ge 0$

$\Leftrightarrow \dfrac{T_{sum}-T_{len} x_{0}}{T_{len}(T_{len}+1)}>0$

$\Leftrightarrow x_0<T_{avg}$

**结论二：一定要选比集合的平均数小的数加进来**

------

这样的话，就可以使用尺取法了，主要代码：

```cpp
if(ch==1)
{
    cnt++;
    cin>>a[cnt];
    sum+=a[cnt]-maxn;
    maxn=a[cnt];
    while(poi<cnt&&(poi+1)*a[poi+1]<sum)
    {
        poi++;
        sum+=a[poi];
    }
}
else
    printf("%.10lf\n",(double)maxn-(double)sum/((double)poi+1.00000));
```



---

## 作者：XL4453 (赞：2)

开 long long！
------------

题目分析：

考虑贪心。

首先发现序列单调增，那么取数的规则一定是从前面取若干个数，然后再去取最后一个数。注意从前往后取不一定不能取到倒数第二个值，但倒数第二个值一定不是因为要扩大最大值而取得。

由题中给出的公式：集合最大值减去集合平均值最大可知，减小减数（即集合的平均值），或者增大被减数（即集合的最大值），都可以使得这样的一个式子的值更大。

那么与之相对应的，取前面的数是为了减小平均值，取最后的一个数是为了增大最大值。取数时，再往集合里加一个未选的最小值也不能使得平均值更小时就说明这样的集合已经是满足要求的最大集合了。

------------
实现上，记录下前面取到的总值 $ans$，用一个指针 $len$ 维护当前从前往后取到第几个值，每有一个新的值加入，尝试将指针后移，直到新加入数会使得平均值变大为止。

------------
代码：

```cpp
#include<cstdio>
using namespace std;
long long T,num[500005],len,k,ans,tot,x;
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&k);
		if(k==1){
			scanf("%lld",&x);
			num[++len]=x;
			while(((double)ans+(double)num[len])/((double)tot+1)>
			((double)ans+(double)num[len]+num[tot+1])/((double)tot+2))
			tot++,ans+=num[tot];
		}
		else{
			printf("%lf\n",(double)num[len]-((double)ans+(double)num[len])/((double)tot+1));
		}
	}
	return 0;
}
```


---

## 作者：kingho11 (赞：1)

# CF939E Maximize! 题解

这道题洛谷上的题面翻译得不是很好，建议去看 codeforces 或 vjudge 的题面

## 思路

这道题需要我们最大化在集合中选取的值组成子集后的最大值 $-$ 平均值，此时最大值显然是选择集合中的最大值，我们假设这个值是 $x$，
证明：把 $x$ 加入子集对子集最大值的贡献是 $x$，但对子集平均值的贡献一定 $\le x$，这是显而易见的。

那么我们只需要想一想怎么选择值使得平均值最小了。

我们可以往平均值的性质方向想一想，假设我们要把 $a_i$ 加入子集，如果 $a_i \le$ 子集平均值，那么子集的平均值会因为 $a_i$ 的加入而变小，反之变大，那么又因为要加入的序列是递增的，那么这个子集的平均值就会一直减小，一直减到一个最小值之后再一直增大，所以我们可以把问题抽象成如何求一个开口向上的二次函数的最小值点。

那么就很好二分了，我们只需要判断这个如果把这个点加入子集是否比上一个点加入子集最小值要小，如果是那么就让```l=mid;```，否则让```r=mid-1;```，那么如何加入点算平均值呢，当然是用前缀和了，求的时候再除以项数就可以了。

至此，这道题就做完了。

## CODE：
```
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
mt19937 myrand(chrono::system_clock::now().time_since_epoch().count());
long double a[N],pre[N],ans=0;
int top;
void add(int x)
{
	a[++top]=x;
	pre[top]=pre[top-1]+x;//维护前缀和 
}
long double query()
{
	long double mean=0,maxn=0;//mean是平均值，maxn是最大值 
	maxn=a[top]*1.0;
	mean=(a[top]*1.0+a[1]*1.0)/2.0;//先存个显而易见的平均值，不存的话遇到二次函数全部都是往上升的mean就=0了，就是错的了 
	int l=0,r=top;
	while(l<r)//二分，题解前面说过是干什么的了 
	{
		int mid=l+r+1>>1;//这里记得要+1，只是提醒一下，学过二分的都知道为什么，就是防止死循环 
		if((pre[mid-1]*1.0+a[top]*1.0)/(mid*1.0)>(pre[mid]*1.0+a[top]*1.0)/(mid*1.0+1.0))
		{
			l=mid;
			mean=(pre[mid]*1.0+a[top]*1.0)/(mid*1.0+1);
		}else
		{
			r=mid-1;
		}
	}
	return maxn-mean;
}
int main()
{
	int _;
	cin>>_;
	while(_--)
	{
		int opt;
		cin>>opt;
		if(opt==1)
		{
			int x;
			cin>>x;
			add(x);//加点，同时要记得维护前缀和 
		}else
		{
			printf("%.10Lf\n",query());//小技巧：尽量保留更多位小数让答案尽量和标准答案相差的小一些 
		}
	}
}
```

---

## 作者：luogu_gza (赞：1)

我们考虑问题的性质。

1. 子集中最大的数替换为更大的数是更好的。

2. 原序列中有小于子集平均数的数一定要加进来。

那么，每一次询问一定是选择原序列的一个前缀和最后一个元素。

原序列加数的时候，把最后一个数替换掉，并判断是否可以扩展前缀。

这里，我使用一个指针来代表前缀。

有几个要注意的点：

1. 数组坐标的加一减一一定要搞清楚。

2. 为了计算方便，你可以多开几个变量。

### [提交记录](https://codeforces.com/contest/939/submission/213644315)

---

## 作者：bmatrix (赞：1)

题意：
> 维护一个可重集 $S$，支持以下两种操作：
> - 插入一个数，保证插入的数不降。
> - 找出 $S$ 的一个子集 $s$，使 $\max(s) - \operatorname{mean}(s)$ 最大，输出这个最大值。其中 $\max(s)$ 表示 $s$ 中元素的最大值，$\operatorname{mean}(s)$ 表示 $s$ 中元素的平均值。

由于我太菜了，并没有想到贪心，所以我的做法带两个 $\log$，最慢点要花 1.5s 才能过。

假设 $s$ 中的元素从小到大已经排好序，设 $n=|s|$，将式子变成分式形式：
$$\begin{aligned}
\max(s) - \operatorname{mean}(s)&=s_{n}-\frac{\sum^{n-1}_{i=1}s_i}{n}\\
&=\frac{(n-1)s_{n}-\sum^{n-1}_{i=1}s_i}{n}
\end{aligned}$$

考虑分数规划，设上式 $\ge k$，则有：
$$\begin{aligned}
(n-1)s_{n}-\sum^{n-1}_{i=1}s_i&\ge n k\\
(n-1)(s_n-k)-\sum^{n-1}_{i=1}s_i&\ge k
\end{aligned}$$
先对 $k$ 二分，不难发现当 $k$ 确定时，$s_n$ 越大越好、$\sum^{n-1}_{i=1}s_i$ 越小越好，因此可以二分 $n$ 来判断一个 $k$ 是否合法，时间复杂度 $O(q\log^2q)$，这题时限松，能过。

注意实数二分的 eps 不要太小，要不然因为精度问题可能死循环。

代码：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
#define int ll
#define gmin(x, y) ((x > (y)) && (x = (y)))
#define gmax(x, y) ((x < (y)) && (x = (y)))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double f128;
typedef pair<int, int> pii;
constexpr int N = 5e5 + 5;
int q, n, a[N], s[N];
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    cin >> q;
    while(q--) {
        int op; cin >> op;
        if(op == 1) {
            int x; cin >> x;
            a[++n] = x;
            s[n] = s[n - 1] + x;
        }
        else {
            if(n == 1) {
                cout << "0\n";
                continue;
            }
            int mx = a[n];
            double l = 0, r = 1e10;
            while(r - l > 1e-6) {
                double mid = (l + r) / 2;
                int p = lower_bound(a + 1, a + n, mx - mid) - a;
                --p;
                if(p * mx - p * mid - s[p] >= mid) l = mid;
                else r = mid;
            }
            cout << fixed << setprecision(8) << l << endl;
        }
    }
    return 0;
}
```

---

## 作者：aimcf (赞：1)

容易发现，为了让选出部分的最大值减去平均值最小，选出的部分一定是最大值和一个连续前缀。

证明：连续的前缀是为了使得选出部分的平均数尽量的小，而最大值则是为了让 $\max$ 变成序列的最大值。

序列具有单调性，可以使用双指针，二分等单调的算法进行枚举。这里使用的是双指针维护选择前缀的右端点。由于一直插入更大的，所以也许可以继续往右边选择一些新的数，满足平均值变得更小。注意平均数是小数。

时间复杂度 $\Theta(n + q)$。

---

## 作者：YuntianZhao (赞：1)

# CF939E

mutiset 是一个可以有重复元素的 set 。

贪心的想，显然最大值就是最大值，那么如果要使得结果最大，就要让平均值最小。如果当只有两个元素的时候，就是$avg_{min} = max - min$ ，但是当有三个及三个以上元素的时候，此时的思路是，从小到大排序，只要当前元素小于平均值，就加上，平均值一定会变小，直到无法再减小。

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const double eps = 1e-6;

int n, m, k;

int minv = inf, maxv = 0;

map<int, int> mp;

void add(int x) {
  mp[x]++;
  minv = min(minv, x);
  maxv = max(maxv, x);
}

double query() {
  int sz = 1;
  double maxx = double(maxv);
  double avg = double(maxv);
  for (auto it = mp.begin(); it != mp.end(); it++) {
    if (it->first > avg) break;
    if (it->first < avg && it->second > 0) {
      avg *= sz;
      avg += it->first * it->second;
      sz += it->second;
      avg /= sz;
    }
  }
  return maxx - avg;
}

int main() {
  int q;
  scanf("%d", &q);
  int opt, x;
  while (q--) {
    scanf("%d", &opt);
    if (opt == 1) {
      scanf("%d", &x);
      add(x);
    } else {
      double ans = query();
      printf("%.10lf\n", ans);
    }
  }
  return 0;
}

```

---

## 作者：chala_tea (赞：0)

## 题意：
对可重集 $S$ 做两个操作：

1. 将元素加入 $S$ 中，保证加入元素递增；

1. 找出 $S$ 中最大值 $\max(s)$ 与平均数 $\operatorname{mean}(s)$ 差值最小的子集。


## 总体思路：贪心+双指针

**对于本题可考虑三则贪心思路：**

设题意中所有 $n$ 个元素依次加入组成数组 $a_i$，可重集为 $S$，当前答案子集为 $s$，则容易看到：

1. $S$ 由**一个最大值**（$tmax$）和**众多较小值**（$a_{1} \sim a_{r}$）组成（$r$ 作指针，初值为 $0$）；

1. 每次加入新元素，就一定要将其把 $s$ 内的原最大值 $\max(s)$ 顶替掉（很容易证明，不断更新最大值带来的增益，比其对平均值的拉高更大）；

1. 若 $a_{r-1} \leq \operatorname{mean}(s)$，则将其加入以拉低平均值。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 514514
#define int long long

int q,a[MAXN]={0},tmax=0,n=0,sum=0;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	int op,x,r=0;
	cin>>q;
	while(q--){
		cin>>op;
		if(op==1){
			cin>>x;
			//策略2
			sum+=(-tmax+x);
			tmax=x,a[++n]=x;
			//策略3（尺取法）
			while(r<n && a[r+1]<(double(sum)/double(r+1))){
				sum=(sum+a[++r]);
			}
		}else if(op==2){
			printf("%.7f\n",(double(tmax+0.0)-(double(sum)/double(r+1))));
		}
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

为了让 $\max(s)-mean(s)$ 最大，首先我们可以想到的是每次新加入的最大值我们是一定要选的，然后我们把以前旧的最大值抛出。即 $\max(s)=\max(S)$。

**证明**

设旧的最大值为 $maxn$，新的最大值为 $maxn'$，已知 $maxn'>maxn$。设原集合 $s$ 除去 $maxn$ 的子集为 $s'$。记原答案为 $ans$，新答案为 $ans'$。

$ans=\frac{maxn}{s'+maxn}=1-\frac{s'}{s'-maxn},ans'=\frac{maxn'}{s'+maxn'}=1-\frac{s'}{s'-maxn'}$。

很明显 $ans'>ans$。



其次，$s$ 中除了 $S$ 的最大值以外，还应该包含 $S$ 中的若干个极小值。为什么不能只包含最小值呢？举一个很显然的例子，$t=\{1,1000\},s=\{1,2,1000\}$，很显然 $s$ 的答案更优。并且我们可以证明，$s$ 中包含 $S$ 中的极小值的个数单调不降。



故本题可以使用单指针的做法。指针位置为 $p$，那么我们就取 $s={S_1,\dots,S_p,S_{cnt}}$（$cnt$ 为目前 $S$ 的大小）。

## 代码

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long


#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}


const int N=5e5+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;

int q;
int t,p;
int cnt,r;
double s[N],sum;
int a,b;

bool f2;


signed main(){
	int Q=rd;
	while(Q--){
		int op=rd;
		if(op==1){
			sum-=s[cnt];
			s[++cnt]=rd;
			sum+=s[cnt];
			while(s[cnt]-sum/(p+1)<s[cnt]-(sum+s[p+1])/(p+2))p++,sum+=s[p];
		}else{
			printf("%.10lf\n",1.00*s[cnt]-1.00*sum/(p+1));
		}
	}
}


```




---

## 作者：codeLJH114514 (赞：0)

# Problem

你需要维护一个可重集 $s$，给你 $n$ 个操作：

- `1 x` 在 $s$ 的最后插入 $x$。（保证 $x$ 单调不降）
- `2` 在 $s$ 中选一个子集 $k$，输出 $\max\{\max\{k\} - \text{average}\{k\}\}$，换句话说就是，选择一个子集 $k$ 使得 $k$ 的最大值 $-$ $k$ 的平均值最大，输出这个最大值。

假设标准答案是 $b$，你的答案是 $a$，只要 $\frac{|a - b|}{\max({1, |b|})} \le 10^{-6}$ 就是对的。

数据范围：$1 \le n \le 5 \times 10^5$

# Analysis

题目要求的是最大值减去平均值，如果这个值最大就是最大值尽量大，平均值尽量小。

不难想到只选最大的和一段前缀最小的，否则永远可以把中间的换成较小的以增加这个值。

所以解法就是我们记录三个值，$P,S,A$，其中 $P$ 是我们还没取到的、最小的那个数的下标，$S$ 是前缀的和，$A$ 是当前的答案。

每次插进一个数，我们计算如果不选 $a_p$ 的答案和选 $a_p$ 的答案（$a$ 是集合），如果选了更小那么 $P \gets P + 1$ 然后循环直到不选更小或者已经全选完了。

对于操作 $2$ 就很简单了，直接输出 $A$ 即可。

时间复杂度？因为 $P$ 只有加 $+1$，$P$ 也一定不会小于集合大小，所以这个算法表面上是二重循环实际还是 $\mathcal{O}(n)$。

# Code

```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#define int int64_t
int N;
std::vector<long double> vec;
int Pre;
long double Ans, Sum;
signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        int mode, x;
        std::cin >> mode;
        if (mode == 1) {
            std::cin >> x;
            vec.push_back(x);
            while (true) {
                if (Pre == vec.size() - 1)
                    break;
                long double NewAns = x - (x + Sum + vec[Pre]) / (Pre + 2);
                long double OldAns = x - (x + Sum) / (Pre + 1);
                if (NewAns >= OldAns)
                    Pre += 1, Sum += vec[Pre - 1];
                Ans = std::max(OldAns, NewAns);
                if (OldAns == Ans)
                    break;
            }
        } else
            std::cout << std::fixed << std::setprecision(20) << Ans << "\n";
    }
    return 0;
}
```

---

