# Table Tennis

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-finala-open/tasks/indeednow_2015_finala_a

 Indeed 社のオフィスには卓球台がある。  
 $ n $ 人の社員が卓球のダブルスで試合をすることにした。  
 $ 2 $ 人ずつのペアを作ることにしたが、みんなが楽しめるようにできるだけ各ペアの強さを均等にしたいと考えている。  
 $ i $ 番目の人の卓球の強さは $ a_i $ で表され、ペアの強さは $ 2 $ 人の強さの和で決まる。  
 一番強いペアと一番弱いペアの強さの差が最小になるようにペアを作ったときに、その差はいくつになるだろうか。

## 说明/提示

### Sample Explanation 1

{$ (1,3),\ (4,10) $}, {$ (1,4),\ (3,\ 10) $}, {$ (1,10),\ (3,4) $} の $ 3 $ 通りのチーム分けが考えられる。 このうち、もっともペアの強さの差が小さいものは {$ (1,10),\ (3,4) $} であり、その差は $ 4 $ である

## 样例 #1

### 输入

```
4
1 3 4 10```

### 输出

```
4```

## 样例 #2

### 输入

```
4
1 3 4 4```

### 输出

```
2```

# 题解

## 作者：gzkeylucky (赞：4)

这是一道典型的贪心，可能因为做的人少就暂无评定，个人认为该题最多橙题的难度。

------------

# 思路
------------

由题得：要使得每队的实力**差距最小**，即需要保证两队的实力总和尽可能靠近两队实力的平均值。

```
以样例1为例：
两队总实力平均值：(1+3+4+10)/2=9；
再根据样例说明，这四个数可以分成三组：{(1,3),(4,10)},{(1,4),(3,10)},{(1,10),(3,4)}；
其中，差距最小的组是：{(1,10),(3,4)}，它们的实力总和分别为11和7，与两队的总实力平均值都分别相差2。

```
那么，为了保证两队的实力总和尽可能相近，通过将整个数组排序后，第一个元素与最后一个元素相加，第二个元素与倒数第二个元素相加，以此类推，使得较大的那个数的增长不那么快，保证每组数据的浮动不会太大，使得两数之和尽可能向中间靠拢，最后将最大值和最小值保存起来，进行减法。


# 代码
------------

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
const int maxn=1e7+5,INF=0x3f3f3f3f;
int a[maxn];
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
	}
	sort(a+1,a+n+1);
	int Max=-INF,Min=INF,l=1,r=n;
	while(l<r) //从两端开始统计和
		{
			Max=max(Max,a[l]+a[r]);
			Min=min(Min,a[l]+a[r]);
			l++; //查找下一组
			r--;
		}
	
	printf("%d\n",Max-Min);
	return 0;
}
```


---

## 作者：jiyuanzhiguang (赞：2)

# 思路

要让每个队的实力差距最小，就要让一个最大的和一个最小的人进行组队，次最大和次最小的进行组队,以此类推退。这样一大一小就可以均匀分配实力，达到实力差距最小。

有了上面这个思路，我们来看看代码如何实现：

首先读入 $n$ 个数字，将它们进行从大到小排序。让 $i$ 从左边开始扫 $j$ 从右面开始扫，这样每次循环的时候 $i$ 和 $j$ 分别指的是最小值和最大值。用 $maxn$ 记录实力之和最大的，$minn$ 记录实力之和最小的，循环完成之后 $maxn$ $-$ $minn$ 就是所求了。


# 代码
```
/*

*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <set>
#include <ctime>
#include <iomanip>

using namespace std;
const int N = 1e2 + 10;
int a[N];

int main()
{
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	
	sort(a + 1, a + n + 1);
	
	int maxn = -1, minn = 0x3f3f3f3f;
	for(int i = 1, j = n; i <= n / 2, j >= 1; i++, j--)//左右同时循环，同时记录实力最大最小值
	{
		maxn = max(maxn, a[i] + a[j]);
		minn = min(minn, a[i] + a[j]);
	}
	
	cout << maxn - minn << endl;//因为是AtCoder的题目，不要忘记换行 
	return 0;
}

```


---

## 作者：A_Bit_Cold (赞：1)

本题评估**难度**：**红题**吧，橙题也行。

## 具体思路

首先第一眼看到题就知道是**贪心**，可是怎么贪心呢？

为了要让每队的实力**差距最小**，我们可以先按照每一位队员的实力**从小到大排序**。

因为一共有 $n$ 个人，两人一队，共分成 $\dfrac{n}{2}$ 队，接着，我们设 $s_i$ 表示第 $i$ 组的**实力和**，则有：

$s_i=a_i+a_{n-i+1}$

即**最弱和最强一队**，**第二弱和第二强一队**，这样，我们算出了这 $\dfrac{n}{2}$ 队的实力值。

接着，我们设 $max$ 为这 $\dfrac{n}{2}$ 队最大实力值，$min$为这 $\dfrac{n}{2}$ 队最小实力值，则我们在这 $\dfrac{n}{2}$ 队中找到 $max,min$ 即可。

最后，输出 $max-min$，即为最大实力值减去最小实力值。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int a[N],s[N];
int main() {
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
	    cin>>a[i];
	}
	sort(a+1,a+n+1);//把每个人的实力值按从小到大排序
	for(int i=1;i<=n/2;i++) {//求这n/2队每队的实力值
	    s[i]=a[i]+a[n-i+1];//第i小+第n-i+1小组一队
	}
	int maxn=0,minn=1e9;//定义n/2队中的最大值，最小值
	for(int i=1;i<=n/2;i++) {//在n/2队中寻找最大值与最小值
	    maxn=max(maxn,s[i]),minn=min(minn,s[i]);
	}
	cout<<maxn-minn<<endl;//输出最大值与最小值
        return 0;//结束程序
}
```

完结撒花！！！

---

## 作者：panyanppyy (赞：0)

橙题水平，一道典中典贪心。

## Problem
给你 $n$ 个数（$n$ 是偶数），将它们分成 $\dfrac{n}{2}$ 组，每组两个数。

使和最大的组与和最小的组之间的差最小。
## Solution
先排序，然后每次最小的数和最大的数组队，这样就是最优解。

尝试证明这个结论：

为了减小最大组，到 $i$ 为止的人需要和 $n-i+1$ 及以后的数组对。

因为到 $i$ 的数与 $n-i$ 的数成为一组，不能减小最大组的值。

对于最小的组，也同样不能变大。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
const int N=107;
int n,a[N];
vector<int>b;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n>>1;i++)b.emplace_back(a[i]+a[n-i+1]);
	sort(all(b));
	cout<<b.back()-b.front()<<'\n'; 
	return 0;
}
```

---

