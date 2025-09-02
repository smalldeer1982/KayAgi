# Average Sleep Time

## 题目描述

It's been almost a week since Polycarp couldn't get rid of insomnia. And as you may already know, one week in Berland lasts $ k $ days!

When Polycarp went to a doctor with his problem, the doctor asked him about his sleeping schedule (more specifically, the average amount of hours of sleep per week). Luckily, Polycarp kept records of sleep times for the last $ n $ days. So now he has a sequence $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the sleep time on the $ i $ -th day.

The number of records is so large that Polycarp is unable to calculate the average value by himself. Thus he is asking you to help him with the calculations. To get the average Polycarp is going to consider $ k $ consecutive days as a week. So there will be $ n-k+1 $ weeks to take into consideration. For example, if $ k=2 $ , $ n=3 $ and $ a=[3,4,7] $ , then the result is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF808B/86ab5f462dc3fdaf9fb78d24cfe814007844dab2.png).

You should write a program which will calculate average sleep times of Polycarp over all weeks.

## 说明/提示

In the third example there are $ n-k+1=7 $ weeks, so the answer is sums of all weeks divided by 7.

## 样例 #1

### 输入

```
3 2
3 4 7
```

### 输出

```
9.0000000000
```

## 样例 #2

### 输入

```
1 1
10
```

### 输出

```
10.0000000000
```

## 样例 #3

### 输入

```
8 2
1 2 4 100000 123 456 789 1
```

### 输出

```
28964.2857142857
```

# 题解

## 作者：EnofTaiPeople (赞：3)

此题适合用于新手学浮点数，细节很多。

AC 时间：5 分钟。

做法很简单，定义一个数 now，表示当前的位置的前 k 个数字的和。到第 i 位时，进行如下操作：
```
now=now+num[i]-num[i-k];
ans+=now/(n-k+1);
```
最后的 ans 就是正确答案。注意，这里 ans 要用 long double，并且必须在 now 的时候就除，否则会爆。

于是得到了 AC 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
	long double ans=0,now=0;int n,num[200005],k,i;
	scanf("%d%d",&n,&k);num[0]=0;
	for(i=1;i<=n;++i)scanf("%d",num+i);
	for(i=1;i<k;++i)now+=num[i];
	for(i=k;i<=n;++i){
		now+=num[i]-num[i-k];
		ans+=now/(n-k+1);
	}
	printf("%.9Lf\n",ans);
	return 0;
}
```
切记占位符是 Lf！！！

---

## 作者：_Harrisonwhl_ (赞：2)

这道题第一眼看到可以想到是计算出每个区间的和去除以区间总数，但是如果暴力枚举的话，最坏情况为 $k=\dfrac{n}{2}$，此情况下时间复杂度为 $O(\dfrac{n^2}{4})$，必定超时啦，所以我们要想到优化，最简单直接的就是**前缀和**啦！

注意一点细节：记得开`long long`哦，求和变量不开`long long`会WA#17，
前缀和数组不开`long long`会WA#21哦！

# Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[200005];
long long s[200005];
int main()
{
	cin >> n >> k;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		s[i]=s[i-1]+a[i];//计算前缀和。
	}
	long long sum=0;
	for (int i=1;i<=n-k+1;i++)
		sum += s[i+k-1]-s[i-1];//加上每个区间。
	printf("%.9f",sum * 1.0 / (n-k+1));//算平均数，保留九位小数。
	return 0;	
}
```

---

## 作者：Eason_AC (赞：1)

## Content
给定 $n$ 个数 $a_1,a_2,a_3,...,a_n$，求所有长度为 $k$ 的连续区间 $[a_1,a_k],[a_2,a_{k+1}],...[a_{n-k+1},a_n]$ 的和的平均值。

**数据范围：$1\leqslant n,k\leqslant 2\times 10^5,1\leqslant a_i\leqslant 10^5$。**
## Solution
首先，我们可以发现，直接暴力枚举的 $\mathcal{O}(nk)$ 的复杂度是不可能通过这道题目的。那么怎么办？

答案是：前缀和。前缀和是指从 $1$ 开始到每个位置的和，也就是从 $1$ 到 $2,3,4,...,n$ 的前缀和，一般用 $s_i$ 来表示 $[1,i]$ 的和，下面的 $s_i$ 意义与此相同。

那么这道题目就有办法了：先预处理出所有 $s_i$，然后答案就是 $\dfrac{\sum\limits_{i=1}^{n-k+1}s_{i+k-1}-s_{i-1}}{n-k+1}$。
## Code
```cpp
ll n, k, a[200007], s[200007], sum;

int main() {
	getll(n), getll(k);
	for(ll i = 1; i <= n; ++i) {
		getll(a[i]);
		s[i] = s[i - 1] + a[i];
	}
	for(ll i = 1; i <= n - k + 1; ++i)
		sum += s[i + k - 1] - s[i - 1];
	printf("%.9lf", (sum * 1.0 / (n - k + 1)));
	return 0;
}
```

---

## 作者：Remake_ (赞：1)

这题，有人用前缀和。

我这个蒟蒻无论如何都不能把此题与前缀和联系在一起qwq，所以，我来为前缀和没学懂的人补一篇题解。

我的思路是数$a_i$能在多少个连续的$k$个数字中出现，然后再用$a_i$乘上这个系数，$a_i$能在多少个连续的$k$个数字中出现的公式显（shi）而（fen）易（xuan）见（xue），如下：

$min(i,n-i+1,k,n-k+1)$

用c++写就是这样：

$min(min(i,n-i+1),min(k,n-k+1))$

一切准备就绪，Code呈上（改了变量名）：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum,a,b,c[200005],k;
int main(){
	cin>>a>>b;
	k=a-b+1;
	for(long long i=1;i<=a;i++){
		cin>>c[i];
		sum+=c[i]*min(min(i,a-i+1),min(b,k));
	}
	printf("%.10f",sum*1.0/k);
}
```


## 最后说一句，十年OI一场空，不开long long见祖宗！我就因为没开long long WA 了半个小时qwq。

---

## 作者：qwq___qaq (赞：0)

### Update

2022/7/28 修改了一个笔误（$sum_l\rightarrow sum_{l-1}$）并删去了不友好且没有优势的线段树做法
***
前缀和可以很快地求出静态区间和，例如求区间 $[l,r]$ 的和，可以直接用 $sum_r-sum_{l-1}$，其中 `sum` 表示前缀和，即为用区间 $[1,r]$ 的和减去区间 $[1,l-1]$ 的和，即为求出 $r$ 前面所有数的包括它本身的和，再减去 $l$ 前面的数的不包括它本身的和。时间复杂度为 $O(n)$。最后要注意，我的代码保留 $9$ 位过不了，保留了 $10$ 位才过（最后一个样例也是 $10$ 位）。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int n,m,a[maxn];
double sum;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),a[i]+=a[i-1];//前缀和
	double k=n-m+1;
	for(int i=1;i<=k;i++)
		sum+=(a[i+m-1]-a[i-1]);//带公式
	printf("%.10lf",sum*1.0/k);
	return 0;
}
```

---

## 作者：pandaSTT (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF808B)

## 温馨提醒

十年  OI  一场空，不开  long long  见祖宗！！

## 思路

### 寻找题眼：连续数字的和！

由此联想到前缀和，用 $ sum[i] $ 记录前 $ i $ 个数字的和，从第 $ i-k $ 到第 $ i $ 个数的和为 $ sum[i]-sum[i-k] $ ，最后用 $ ans $ 求和计算平均数就行了。

## 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long n,k,sum[200005],a[200005];//一定要开 long long 
  double ans;
  int main(){
      cin>>n>>k;
      for(int i=1;i<=n;i++){
          cin>>a[i];
          sum[i]=sum[i-1]+a[i];
      }
      for(int i=k;i<=n;i++){
          ans+=(sum[i]-sum[i-k])*1.0;//利用前缀和计算每连续 k 个数字的和
      }
      printf("%.9lf",ans/(n-k+1));//平均数=总和/数量，题目给出了数量为 (n-k+1)
      return 0;
  }
```




---

## 作者：流绪 (赞：0)

前缀和!

如果直接每一段求和再加起来,那么最大是 (n-k+1)*k，根据题目的范围来看极限可能是 n=k=1e5，那么 1e10 的复杂度，肯定 T 了，所以我们考虑怎么简化它！
所以我们考虑前缀和，它可以 O(n) 求和，然后 O(1) 查询,这时候复杂度是 O(n) 最大 2e5 可以接受。

还有一种方法是滑动窗口，好像和前缀和也差不多...滑动窗口可以在洛谷题库里搜，前缀和百度有很详细的解释

下面是 AC 代码，细节注释在代码里了
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
ll sum[maxn]={0};
int main()
{
	ios::sync_with_stdio(false);
	int n,k;
	cin >> n >> k;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin >> x;
		sum[i] = sum[i-1]+x;//计算前缀和
	}
	ll ans=0.0;//总的和
	for(int i=k,j=i-k;i<=n;i++,j++)//i 是左端点,j是右端点,构成长度k的一段
		ans += sum[i]-sum[j];
	printf("%.10lf",ans/(n-k+1.0));//整型转化为浮点型
	return 0; 
}  
```


---

