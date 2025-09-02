# Array Rearrangment

## 题目描述

You are given two arrays $ a $ and $ b $ , each consisting of $ n $ positive integers, and an integer $ x $ . Please determine if one can rearrange the elements of $ b $ so that $ a_i + b_i \leq x $ holds for each $ i $ ( $ 1 \le i \le n $ ).

## 说明/提示

In the first test case, one can rearrange $ b $ so it'll look like $ [1, 2, 1] $ . In this case, $ 1 + 1 \leq 4 $ ; $ 2 + 2 \leq 4 $ ; $ 3 + 1 \leq 4 $ .

In the second test case, one can set $ b $ to $ [5, 2] $ , then $ 1 + 5 \leq 6 $ ; $ 4 + 2 \leq 6 $ .

In the third test case, no matter how one shuffles array $ b $ , $ a_4 + b_4 = 4 + b_4 > 4 $ .

In the fourth test case, there is only one rearrangement of array $ b $ and it doesn't satisfy the condition since $ 5 + 5 > 5 $ .

## 样例 #1

### 输入

```
4
3 4
1 2 3
1 1 2

2 6
1 4
2 5

4 4
1 2 3 4
1 2 3 4

1 5
5
5```

### 输出

```
Yes
Yes
No
No```

# 题解

## 作者：小王子2021 (赞：3)

## 分析

一个简单的贪心问题


题目要求 $a_i + b_j \leq x$ $( 1\leq i \leq n,1 \leq j \leq n$即可。

这题的关键是贪心证明，考场上想了想就直接写了，考后才分析了一下，这里给出我这个蒟蒻都看得懂的贪心证明：

1. 如果 $a$ 与 $b$ 中的最小值相加，那么之后就会出现两个大数相加的情况，但实际上是可以匹配成功的，这明显是不对的（舍去）。

2. 如果 $a$ 最小值与 $b$ 最大值的和必定小于 $a$ 的其他元素与 $b$ 最大值的和。这种情况是成立的

这里就给出结论：
		
        匹配，判断 $a_i$ 最小值与 $b_i$ 的最大值是否小于等于 $x$ 即可。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,a[51],b[51];
int main()
{
	cin>>T;
	while(T--)
	{
		int flag=1;
		cin>>n>>x;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]+b[n-i+1]>x)
			{
				cout<<"NO"<<endl;
				flag=0;
				break;
			}
		}
		if(flag){cout<<"Yes"<<endl;}
	} 
} 
```





---

## 作者：洛璟 (赞：1)

~~比赛签到题~~

其实是一道简单的数学题，大概思路就是把两个数组都排一遍序，然后a数组中最小的数与b数组中最大的配对，这样的话可以使加起来的  最大的数  尽可能小。

代码很简单：
```
#include<bits/stdc++.h>
using namespace std;
int n,t;
int x;
int a[55],b[55];
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		x=(x<<1)+(x<<3)+(c^'0');
		c=getchar();
	}
	return x*f;
}
int main()
{

	t=read();
	while(t--)
	{
		bool fg=0;
		n=read();
		x=read();
		for(int i=1; i<=n; i++)
		{
			a[i]=read();
		}
		for(int i=1; i<=n; i++)
		{
			b[i]=read();
		}
		sort(a+1,a+n+1,greater<int>());//greater是c++自带函数，这样使a数组从大到小排序
		sort(b+1,b+n+1);
		for(int i=1; i<=n; i++)
		{
			if(a[i]+b[i]>x)
			{
				printf("No\n");
				fg=1;
				break;
			}
		}
		if(fg==1) continue;
		else printf("Yes\n");
	}
	return 0;
}
```


---

## 作者：—维尼— (赞：0)

## 题目大意

给定两个非降序数组$a$,$b$和一个$x$，让你判断是否可以通过重新排列让任意一个$a_i+b_i\le x$

## 题目思路

因为是有序的，而且题目范围小的离谱，乱搞就能过

这里写一种$o(n)$的，我们直接贪心将$b$数组反转，让最大值与$a$组的最小值，次大值与$a$组的次小值……一一对应，然后$o(n)$枚举每个下标下的$a_i+b_i$就行了

这次div2A比较简单，思路就是这样

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int a[55],b[55],c[55];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,x;
		bool ans=true;
		cin>>n>>x;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		for(int i=1;i<=n;i++){
			c[i]=b[n-i+1];
		}
		for(int i=1;i<=n;i++){
			if(a[i]+c[i]>x){
				ans=false;
			}
		}
		if(ans){
			cout<<"Yes"<<endl;
		}
		else
			cout<<"No"<<endl;
	}
	return 0;
} 
```

---

## 作者：Eason_AC (赞：0)

## Content
有 $t$ 组询问，每组询问给定两个长度为 $n$ 的数列 $\{a_i\}_{i=1}^n,\{b_i\}_{i=1}^n$ 和一个整数 $x$，求是否能够重新对两个数列进行排列，使得 $\forall i\in[1,n],a_i+b_i\leqslant x$。

**数据范围：$1\leqslant t\leqslant 100,1\leqslant n\leqslant 50,1\leqslant x\leqslant 1000,1\leqslant a_i\leqslant x,1\leqslant b_i\leqslant x,a_i\leqslant a_{i+1},b_i\leqslant b_{i+1}$。**
## Solution
因为 $a,b$ 两个数列都已经非降序排列，所以我们直接扫过去，看是否存在 $i\in[1,n]$，使得 $a_i+b_{n-i+1}>x$ 或者是否存在 $i'\in[1,n]$，使得 $a_{n-i'+1}+b_{i'}>x$。如果上面的两个 $i,i'$ 都存在，那么就无法满足题目的要求了，否则就可以。
## Code
```cpp
int t, n, x, a[100007], b[100007], a1[100007], b1[100007];

int main() {
	//This program is written in Windows 10 by Eason_AC
	getint(t);
	while(t--) {
		getint(n), getint(x);
		_for(i, 1, n) getint(a[i]);
		_for(i, 1, n) getint(b[i]); 
		int flag1 = 1, flag2 = 1;
		_for(i, 1, n) if(a[i] + b[n - i + 1] > x) {flag1 = 0; break;}
		_for(i, 1, n) if(a[n - i + 1] + b[i] > x) {flag2 = 0; break;}
		if(flag1 || flag2) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：yzy1 (赞：0)

题目思路
---

使用二分法, 首先将 $a, b$ 扔进两个 `std::multiset` 里.

因为要满足的条件是 $a_i + b_i \le x$, 即 $b_i \le x - a_i$,
我们可以遍历 $a$,
每次找到 $b$ 中最后一个 $\le x - a_i$ 的值,
并将其删除,
如果找不到这样的一个值, 说明无解.

时间复杂度 $\mathcal O (t \cdot n \log n^2)$

注意
---

- 由于原数组中元素可重, 所以不能用 `set`, 要用 `multiset`.
- C++ 没有提供找到 multiset 中最后一个 $\le x$ 元素的函数,
    但是它提供了找到第一个 $> x$ 元素的函数 `std::upper_bound`,
    我们可以直接用 `std::upper_bound` 函数返回的结果 $- 1$,
    来实现找到最后一个 $\le x$ 的元素.

Code
---

```cpp
inline void Solve() {
  for (const auto &item: a) {
    auto it = b.upper_bound(x - item);
    if (it == b.begin()) {
      // 这里需要特别判断一下, 如果 it == b.begin,
      // 那么 *(--it) 就会越界, 会导致程序 RE 出错
      puts("No");
      return;
    }
    --it;
    b.erase(it);
  }
  puts("Yes");
}
```


---

## 作者：K2sen (赞：0)

### 简化题面
题目中给你两个数组，分别记为 a 和 b，都有 n 个元素。

现在问你，让 a,b 数组重新排序最后，能不能使得 $\forall i \in [1,n]. a_i +b_i \leq x$。

### 思路
大概就是一个贪心的思想，我们让 a 中最大的与 b 中最小的加起来，a 中次大的与 b 中次小的加起来这样的答案更优，考虑如何证明。

我们令 $a_1, a_2$ 分别表示 a 中的最大元素与次大元素， $b_1,b_2$ 分别为 b 中的最小元素和次小元素，如果按照上述的方法加起来，那么就是 $a_1 + b_1$ 和 $a_2+b_2$ 这两个。

如果我们试最大的加上次小的，次大的加上最小的他就会变成 $a_1+b_2$ 和 $a_2 + b_1$，显然这两个都比上边的两个更大，而我们求的是任意的 $a_i + b_i \leq x$，肯定是使加和越小越好，所以我们让 a 中最大的与 b 中最小的加起来，a 中次大的与 b 中次小的加起来。

### code
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
#define N 100010
#define M 60

using namespace std;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
int T, a[M], b[M], n, x;

int read() {
  int s = 0, f = 0; char ch = getchar();
  while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
  while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
  return f ? -s : s;
}

bool cmp(int a, int b) {
  return a > b;
}

int main() {
  T = read();
  while (T--) {
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    n = read(), x = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) b[i] = read();
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1, cmp);
    int flag = 0;
    for (int i = 1; i <= n; i++)
      if (a[i] + b[i] > x) flag = 1;
    if (flag) puts("No");
    else puts("Yes");
  }
}
```

---

## 作者：Dementor (赞：0)

## 题解

这道题，要判断能不能将给定的两个序列构造成任意两个相同位置的数的和小于等于一个给定的值。

为了让任意相同位置的值的和尽量小于 $x$ ，那么我们将 $a$ 从小到大排、将 $b$ 从大到小排，这样能保证所有的 $a_i + b_i$ 尽量小。

也算是一个贪心策略吧。

当然将 $a$ 从大到小、 $b$ 从小到大也可以，随大家喜欢 ~

那么我们来看看简单的代码吧（也有一段时间没写这么简单的代码了 $……$）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int a[N], b[N];
int t, n, x;
int main () {
	scanf ("%d", &t);
	while (t --) {
		scanf ("%d %d", &n, &x);
		for (int i=1;i<=n;i++) scanf ("%d", &a[i]);
		for (int i=1;i<=n;i++) scanf ("%d", &b[i]);
		sort (a + 1, a + n + 1);
		sort (b + 1, b + n + 1);
		for (int i=1;i<=n;i++) {
			if (a[i] + b[n - i + 1] > x) {
				puts ("No");
				goto nxt;
			}
		}
		puts ("Yes");
		nxt :
			continue;
	}
}
```

---

## 作者：Su_Zipei (赞：0)

比赛的时候题目之看懂了大意所以可能写的有点麻烦。。。

因为最后只问有没有解，所以可以让每个$a$与能和它配对的最小的$b$进行贪心配对，如果这样配对都还有数字不能满足，那么就一定无解。

事实上只需要一个正着扫一个倒着扫就行了因为数组有序并且个数一样，然而我没看见。。。

```
#include<set>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+10;
int n,val,a[N];
multiset<int> s;
multiset<int>::iterator it;
bool pd(){
	for(int i=1;i<=n;i++){
		it=s.lower_bound(a[i]-val);
		if(it==s.end())return 0;
		s.erase(it);
	}
	return 1;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		s.clear();
		scanf("%d%d",&n,&val);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int j=1;j<=n;j++){
			int x;
			scanf("%d",&x);
			s.insert(-x);
		}
		puts(pd()?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：ql12345 (赞：0)

## 贪心结论严谨证明

没有别的限制，只要$a_i+b_i<=x$，显然是$a_i+b_i$越小越好，判断最小的最大值是否小于等于$x$即可。

如何求最小的最大值呢？二分？太麻烦了，CF构造题很多，想是否能构造出来一种最大值最小的$a$与$b$的排列方式，**不妨**现将$a$升序排列，考虑如何组合$b$，最终的答案一定满足：如果$b$交换两项，答案一定不会更优，即最大值不会变小，即：

$max(a_i+b_i,a_j+b_j)<=max(a_i+b_j,a_j+b_i)$

考虑让这个式子不成立，不妨令$i<j$，于是$a_i<=a_j$，所以$a_i+b_i<=a_j+b_i$且$a_i+b_j<=a_j+b_j$，所以左式的最大值应让它为$a_j+b_j$且大于$a_j+b_i$，于是就有：

$b_j>b_i$时不成立，即如果令$b$非严格降序排序，答案最优（最大值最小）

有了构造方法，即可模拟（实际上就是两个排序）求出最小的最大值，与x比较得出答案

#### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[23333],b[23333];

signed main()
{
	int t;
	cin >>t;
	while(t --)
	{
		int n,k,flag=1;
		cin>>n>>k;
		for(int i=1;i<=n;++i)cin>>a[i];
		for(int j=1;j<=n;++j)cin>>b[j];
		
		sort(a+1,a+n+1);sort(b+1,b+n+1);reverse(b+1,b+n+1);
		for(int i=1;i<=n&&flag;++i)if(a[i]+b[i]>k)flag=0;
		puts(flag?"Yes":"No");
		
		for(int i=1;i<=n;++i)a[i]=0;
		for(int j=1;j<=n;++j)b[j]=0;
	}
	
	return 0;
}
```

养成好习惯：

多测清空

$#define int long long$

写上$return 0$

---

## 作者：vеctorwyx (赞：0)

### 题目大意

给你两个长度为$n$数组$a,b$，求一种排列方式使得$\forall 1\le i\le n,  a_i+b_i<x$（x给出）。

### sol

既然是要最小，那就要让$a$数组中最大的与$b$数组中最小的相加以保证和最小。

简单证明一下：

如果$a$中取最小值，与$b$中的最小值（或其他非最大值）相加，那么之后就会出现两个大数相加的情况，一定不如大小相加优。

换句话说，设$a$最大值与$b$最小值的和为$c$，那么$c$一定小于$a$最大值与其他$b$中元素的和。

~~证毕~~。

因为给出的数组是有序的（非降序），则直接一正一反枚举求和比较就好了。

code：

```

#include<bits/stdc++.h>
using namespace std;
int read()
{
    int x=0,y=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')y=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    return x*y;
}
int t,n,x,a[60],b[60];
int main()
{
	t=read();
	while(t--)
	{
		n=read(),x=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		for(int j=1;j<=n;j++)
			b[j]=read();
		bool flag=0;
		for(int i=1;i<=n;i++)
		{
			if(b[n-i+1]+a[i]>x)
			{
				flag=1;
				break;
			}
		}
		if(!flag)
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
}
```

---

