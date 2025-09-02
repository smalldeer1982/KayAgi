# Progress Bar

## 题目描述

A progress bar is an element of graphical interface that displays the progress of a process for this very moment before it is completed. Let's take a look at the following form of such a bar.

A bar is represented as $ n $ squares, located in line. To add clarity, let's number them with positive integers from $ 1 $ to $ n $ from the left to the right. Each square has saturation ( $ a_{i} $ for the $ i $ -th square), which is measured by an integer from $ 0 $ to $ k $ . When the bar for some $ i $ ( $ 1<=i<=n $ ) is displayed, squares $ 1,2,...\ ,i-1 $ has the saturation $ k $ , squares $ i+1,i+2,...\ ,n $ has the saturation $ 0 $ , and the saturation of the square $ i $ can have any value from $ 0 $ to $ k $ .

So some first squares of the progress bar always have the saturation $ k $ . Some last squares always have the saturation $ 0 $ . And there is no more than one square that has the saturation different from $ 0 $ and $ k $ .

The degree of the process's completion is measured in percents. Let the process be $ t $ % completed. Then the following inequation is fulfilled:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF71B/4e9efb78cef50edf8afa424b4903c5e6bf3cc77f.png)An example of such a bar can be seen on the picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF71B/151c399de3b500275514615e73a7da37fbaf060b.png)For the given $ n $ , $ k $ , $ t $ determine the measures of saturation for all the squares $ a_{i} $ of the progress bar.

## 样例 #1

### 输入

```
10 10 54
```

### 输出

```
10 10 10 10 10 4 0 0 0 0 ```

## 样例 #2

### 输入

```
11 13 37
```

### 输出

```
13 13 13 13 0 0 0 0 0 0 0 ```

# 题解

## 作者：ZM____ML (赞：10)

## 题意
构造一个数列，分成3个部分，使这个序列满足：

$\dfrac {\sum_{i = 1}^{n} a_i}{n\cdot k}\le \dfrac{t}{100}\le \dfrac {(\sum_{i = 1}^{n} a_i) +1}{n\cdot k}$

## 分析

通过读题我们可以发现，输出分为：

1. $k$
1. $0 \sim k$ 中的任意一个数
1. $0$

这三个部分。

我们可以发现，在原题的式子中，求和的部分只有前面几个值为 $k$ 的和中间一个值为 $0 \sim k$ 中间一个数这几个部分，具体过程不在赘述，[这篇题解](https://www.luogu.com.cn/blog/576817/solution-cf71b)讲的很详细。

我来说说具体是怎么求出前面有几个 $k$ 的。

下面这个式子显然，不用证明。

$\dfrac {\sum_{i = 1}^{n} a_i}{n\cdot k}\le \dfrac {(\sum_{i = 1}^{n} a_i) +1}{n\cdot k}$

我们来看看左边两个式子：

我们设中间那个值为 $p$ ，那么原来这个式子：

$\dfrac {\sum_{i = 1}^{n} a_i}{n\cdot k}\le \dfrac{t}{100}$

可以先化成：

$\dfrac {k\cdot m +p}{k}\le \dfrac{n\cdot t}{100}$

也就是：

$m+\dfrac {p}{k}\le \dfrac{n\cdot t}{100}$

同理，把右边两个式子化简可以得到：

$\dfrac{n\cdot t}{100}\le m+1+\dfrac {p}{k}$

因为 $p$ 是 $0 \sim k$ 中间的一个数，所以把上面的式子结合一下，可以得出：

$m = \dfrac{n\cdot t}{100}$

然后中间的一个 $p$ 就是总和减去前面的 $m\cdot k$ 的值。

### 最后贴上代码
```c
#include<cstdio>
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int n,k,t,m,p;
int main(){
	n=read(),k=read(),t=read();
	m=n*t/100;
	for(int i=1;i<=m;i++)printf("%d ",k);
	if(m>n)return 0;//注意判断一下全是k的情况 
	p=n*k*t/100-m*k;
	printf("%d ",p);
	for(int i=m+2;i<=n;i++)printf("0 ");
	return 0;
}
```


---

## 作者：linjinkun (赞：0)

考虑暴力，由于精度问题所以要把式子转化一下。

$$ \frac {\sum_{i = 1}^{n} a_i}{n\cdot k}\le \frac{t}{100}< \frac {(\sum_{i = 1}^{n} a_i) +1}{n\cdot k} $$

$$\sum_{i = 1}^{n} a_i \times 100 \le n \times k \times t < ((\sum_{i = 1}^n a_i)+1) \times 100$$

代码
```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	int n,k,t;
	scanf("%d %d %d",&n,&k,&t);
	for(int i = 1;i<=n;i++)
	{
		for(int j = 0;j<=k;j++)//枚举第i个数选什么
		{
			int sum = (i-1)*k+j;
			if(sum*100<=n*k*t&&t*n*k<(sum+1)*100)//对应上面的式子
			{
				for(int l = 1;l<=n;l++)
				{
					if(l<i)
					{
						printf("%d ",k);
					}
					else if(l>i)
					{
						printf("0 ");
					}
					else
					{
						printf("%d ",j);
					}
				}
				exit(0);
			}
		}
	}
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

观察了一下，好像没有用相同做法的。

考虑原式：$\frac {\sum_{i = 1}^{n} a_i}{n\cdot k}\le \frac{t}{100}\le \frac {(\sum_{i = 1}^{n} a_i) +1}{n\cdot k}$

然后不等式同时乘 $100nk$ 得 $100\sum_{i = 1}^{n}a_i \le tnk \le 100(\sum_{i=1}^na_i) + 1$。

然后枚举题目中的 $i$ 是哪一位，然后 $100\sum_{i = 1}^{n}a_i = 100(i-1)k + a_i$，然后用 $\frac{tnk-100(i-1)k}{100}$ 算出当前位填多少即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k, t;

signed main() {
	scanf("%d%d%d", &n, &k, &t);
	for (int i = 1; i <= n; ++i) {
		int cha = t * n * k - 100 * (i - 1) * k;
		// cout << cha << endl;
		if (cha > k * 100) continue;
		for (int j = 1; j < i; ++j) {
			cout << k << ' ';
		}
		cout << cha / 100 << ' ';
		for (int j = i + 1; j <= n; ++j) {
			cout << 0 << ' ';
		}
		break;
	}
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

设变化的位置在 $p + 1$，$p + 1$ 的值为 $x$，这里 $0 \le x < k$。为什么是小于号？如果 $x = k$ 等同于变化的位置在 $p + 2$。

把式子抄一遍。
$$\frac {\sum_{i = 1}^{n} a_i}{nk}\le \frac{t}{100}\le \frac {(\sum_{i = 1}^{n} a_i) +1}{nk}$$

按照条件改一下。
$$\frac {(\sum_{i = 1}^{p} k) + x}{nk}\le \frac{t}{100}\le \frac {(\sum_{i = 1}^{p} k) + x + 1}{nk}$$
$$\frac {pk + x}{nk}\le \frac{t}{100}\le \frac {pk + x + 1}{nk}$$

注意到 $p$ 的系数是 $k$，而由于 $0 \le x < k$，$\dfrac{x}{k} < 1$，这在不等式中有很好的性质。那么我们考虑把 $n$ 拿走，直接除下来。
$$p + \dfrac{x}{k} \le \dfrac{nt}{100} \le p + \dfrac{x}{k} + 1$$

这就可以用到刚刚说到的性质了，因为 $p$ 是整数，可以直接把 $\dfrac{x}{k}$ 去掉。
$$p \le \dfrac{nt}{100} \le p + 1$$

我们就得到了 $p$ 的值。
$$p = \lfloor \dfrac{nt}{100} \rfloor$$

同时，由第三条式子，我们可以得到 $x$ 的值。
$$x \le \dfrac{nkt}{100} - pk \le x + 1$$
$$x = \lfloor \dfrac{nkt}{100} \rfloor - pk$$

那么这道题就愉快的做完了。
```cpp
int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> k >> t;
	int p = n * t / 100; int x = n * k * t / 100 - p * k;
	for (int i = 1; i <= p; i++) a[i] = k;
	if (p + 1 <= n) a[p + 1] = x;
	for (int i = 1; i <= n; i++) cout << a[i] << ' ';
	return 0;
}
```

---

## 作者：albccpp6 (赞：0)

## 题目大意：
让你构造一个长度为n的数组，找出一个 $i$，下标比 $i$ 小的数都是 $k$，下标是 $i$ 的数可以是 $0$ 到 $k$ 之间任意一个数，下标比 $i$ 大的数都是 $0$，并且这个数组要满足 $ \frac { \sum _ { i = 1 } ^ n a_i} {n \cdot k} \le \frac{ t }{ 100 } \le \frac{( \sum _ { i = 1 } ^ n a_i ) + 1}{n \cdot k}$。
## 思路：
这题只要能求出 $i$ 就很简单了，我们很容易就能得出 $ i = \frac { n \times t }{ 100 } $，而第 $i$ 个数就是总的减去前面的$i$ 个 $k$，那么就是 $ \frac { n \times k \times t } { 100 } -  i \times k $。
## Code:
```cpp
#include <iostream>
using namespace std;
int a[100001]; 
int main(){
	int n,k,t;
	cin >> n >> k >> t ;
	int i = n * t / 100 ;		//求 i 
	for (int j = 0 ; j < i ; j ++) a[j] = k ;		//前 i 个都是 k 
	a[i] = n * k * t / 100 - i * k ;		// 求第 i 个数 
	for (int j = i + 1 ; j < n ; j ++) a[j] = 0 ;		//后面的都是 0 
	for (int j = 0 ; j < n ; j ++) cout << a[j] << ' ' ;		//输出 
	return 0;
}

```


---

## 作者：Lyrella (赞：0)

# 题意
给你 $n,k,t$，让你找一个 $i$，让所有 $a_{1,2,3...i - 1}$ 变成 $k$，$a_i$ 变成 $ 0 \sim k$ 的任意数字，$a_{i+1,i+2,i+3...n}$ 变成 $0$。使得 $\frac {\sum_{i = 1}^{n} a_i}{n\cdot k}\le \frac{t}{100}\le \frac {(\sum_{i = 1}^{n} a_i) +1}{n\cdot k}$。

# 思路
这道题的**关键**就是找到分界点。不妨前 $m$ 个数为 $k$、第 $m+1$ 个数为 $h(h\in [0,k))$，接下来开始推狮子。

把上面的狮子写成：
$$\frac {(\sum_{i = 1}^{m} k)+h}{n k}\le \frac{t}{100}\le \frac {(\sum_{i = 1}^{m} k)+h+1}{nk}$$

不管后面看前面，移项，得：
$$\frac{\sum_{i = 1}^{m}k}{n k}\le\frac{t}{100}-\frac{h}{nk}$$

左柿约分，得：
$$\frac{m}{n}\le\frac{t}{100}-\frac{h}{nk}$$

移项，得：
$$m\le\frac{nt}{100}-\frac{nh}{nk}$$

右柿约分，得：
$$m\le\frac{nt}{100}-\frac{h}{k}$$

因为 $h<k$，所以：
$$m\le\frac{nt}{100}$$

将原式按同理化简后两项，得：
$$\frac{nt}{100}-1\le m$$

所以 $m=\left \lfloor  \frac{nt}{100} \right \rfloor $

所以：
$$m=\frac{nt}{100}-\frac{h}{k}$$

移项，得：
$$\frac{h}{k}=\frac{nt}{100}-m$$

再移项，得：
$$h=\frac{nkt}{100}-mk$$

**至此**，所有的都已求解，上代码。
# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define Fl(i, l, r) for(int i = l; i <= r; i++)
#define Fr(i, r, l) for(int i = r; i >= l; i--)
using namespace std;
int n, k, t;
void solve(){
	cin >> n >> k >> t;
	int m = t * n / 100;
	vector < int > a(n + 1);
	Fl(i, 1, m)a[i] = k;
	if(m < n)a[m + 1] = n * k * t / 100 - m * k;
	Fl(i, 1, n)cout << a[i] << ' ';
}
signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：ofsl (赞：0)

题目链接：[CF71B Progress Bar](https://www.luogu.com.cn/problem/CF71B)

宣传一下[我的博客](https://www.luogu.com.cn/blog/302437/)
## 思路：
我们通过输出样例可以发现：前 p 个输出都是 k，之后的 1 个位置是多余的进度 ans，后面的位置都是 0。所以完成这道题只需要求出 p 就行了。容易得出 $p=n\times t\%$，然后就可以知道**多余的进度是总进度减去 p 个格的进度**，也就是说 $ans= n\times k\times t\%-p\times k$。

代码时间复杂度为 $O(n)$。

题目难度大概是入门。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,i,p,ans; 
int main(){
	scanf("%d%d%d",&n,&k,&t);
	p=n*t/100;
	for(i=1;i<=p;i++)
		printf("%d ",k);
	if(i>n)
		return 0;
	ans=n*k*t/100-p*k;
	printf("%d ",ans);
	for(i++;i<=n;i++)
		printf("0 ");
	return 0;
} 
```
求赞qwq

---

## 作者：wxy11130 (赞：0)



#### *这道题的关键是找到分界点。*

**$∵$** $p$ 是 $0 \sim k$ **中间** 的一个数，

**$∴$ 设前 $m$ 个数为 $k$、第 $m+1$ 个数为 $h(h\in [0,k])$。**

$∴$

$$\frac {(\sum_{i = 1}^{m} k)+h}{n k}\le \frac{t}{100}\le \frac {(\sum_{i = 1}^{m} k)+h+1}{nk}$$

**$∵$ $h<k$，化简得：**
$$\frac{nt}{100}-1\le m$$

**所以：**

$m=\left \lfloor  \frac{nt}{100} \right \rfloor $

**移项，得：**
$$h=\frac{nkt}{100}-mk$$

**综上所述：**

$m = (n * t)/100$ 

------------

也就是说，我们只需要求出 $p$ 的值，前 $p$ 个输出都是 $k$，特判之后的 $1$ 个位置是多余的进度 $ans$。

显然，**后面**的位置都是 $0$。

### 送上最短代码

```
#import<iostream>
using namespace std;
int n,k,t,i,a;
main() {
	cin>>n>>k>>t;
	for(i=1;i<=n*t/100;i++)
		cout<<k<<" ";
	if(i>n)
		return 0;
	cout<<n*k*t/100-n*t/100*k<<" ";
	for(i++;i<=n;i++)
		cout<<"0 ";/*直接输出 i 后的所有数*/
	return 0; 
}

```


---

