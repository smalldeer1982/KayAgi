# [CCC 2021 S1] Crazy Fencing

## 题目描述

栅栏由 $N$ 块木板组成。

因为是栅栏，所以第 $i$ 块的右边界与第 $i+1$ 块的左边界的高度一样。

告诉你这些木板的边界的高度与这些木板的宽度，输出这些木板的总面积。

## 说明/提示

样例解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/doy8i2lm.png)![](https://cdn.luogu.com.cn/upload/image_hosting/3q9oe7v5.png)

$N\leq 10000$，高度和宽度 $\leq 100$。

译自 [CCC2021 S2](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

## 样例 #1

### 输入

```
3
2 3 6 2
4 1 1
```

### 输出

```
18.5```

## 样例 #2

### 输入

```
4
6 4 9 7 3
5 2 4 1
```

### 输出

```
75.0```

# 题解

## 作者：lichenzhen (赞：5)

## 题目大意
一个由 $N$ 块木板组成的栅栏，并且相邻的两块木板的左边界和右边界是相同的，给出每块木板边界的长度和每块木板的宽度。求栅栏的总面积。
## 题目解法
我们观察样例解释可以发现，每一块木板都是一个梯形，木板的左边界就是梯形的上底，右边界就是下底。而且我们发现木板一定与地面垂直，所以木板都是直角梯形，这样我们就可以发现梯形是高就是木板的宽度。因此我们根据梯形面积公式求出每个木板的面积了，而栅栏的面积就是所有木板面积的和。

最后要注意输出的时候要记得保留 $1$ 位小数。

注：梯形的面积 $S=(a+b) \times h \div 2$（$a$ 是上底，$b$ 是下底，$h$ 是高）
### 参考代码
```cpp
#include<iostream>
using namespace std;
int a[10010],b[10010],n;
double sum;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n+1;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]); 
    for(int i=1;i<=n;i++) sum+=(double)(a[i]+a[i+1])*b[i]/2;
    printf("%.1lf",sum);
}
```


---

## 作者：zhuweiqi (赞：2)

首先，我们不妨把这 $n$ 个木板看做成 $n$ 个梯形，那么题目就变成求这 $n$ 个梯形的面积和了，然后题目描述中的“因为是栅栏，所以第 $i$ 块的右边界与第 $i+1$ 块的左边界的高度一样”就可以转换成第 $i$ 个梯形的上底和第 $i+1$ 个梯形的下底的长度一样，再用上我们求梯形面积的公式：

$$S=(a+b)\times h \div 2$$

就可以基本解决这道题目了，最后我们再来看一下数据范围：我们发现，如果当每个数据都取最大值的时候，答案应该是：$(100+100)\times 100 \div 2 \times 10000=10^8$，显然不会超出 int 的范围，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10005];
int h[10005];
int main(){
	int n;
	double ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&h[i]);
	for(int i=1;i<=n;i++) ans+=(a[i+1]+a[i])*h[i]/2.0;
	printf("%.1lf",ans);
    return 0;
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 P9024 [CCC2021 S1] Crazy Fencing](https://www.luogu.com.cn/problem/P9024)

## 解题思路

1. 每块木板都是一个直角梯形，用梯形的面积公式求出面积：

$$
S=\dfrac{h(a+b)}{2}
$$

![](https://cdn.luogu.com.cn/upload/image_hosting/zz7giudp.png)

2. 所有 $n$ 块木板的总面积即为栅栏的面积。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=10005;
int a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n+1;i++)
	{
		cin>>a[i];
	}
	double ans=0;
	for(int i=1;i<=n;i++)
	{
		int h;
		cin>>h;
		ans+=(a[i]+a[i+1])*h*0.5;
	}
	cout<<fixed<<setprecision(1)<<ans<<'\n';
	return 0;
}
```

---

## 作者：yszkddzyh (赞：1)

这是一道简单数学题。

主要应用到梯形面积公式：$S=\dfrac{1}{2}(a+b)h$，其中 $S$ 为面积， $a$ 为上底，$b$ 为下底（上下顺序无所谓），$h$ 为高，如果记得没错的话，这是小学四年级的知识。

这个公式和这道题有什么关系呢？我们来看一下这个图（其实就是题目中的原图）：

![](https://cdn.luogu.com.cn/upload/image_hosting/doy8i2lm.png)

可以把每个栅栏看作一个直角梯形，则整个栅栏由三个直角梯形组成，因此我们只需要计算这三个梯形的总面积即可。对于每一个梯形，它的上、下底即为该栅栏两个边界的高，它的高 $h$ 即为该栅栏的宽，所以我们很容易可以得出以下代码：

```cpp
#include <iostream>
using namespace std;
const int maxn=1e4+5;
int n,h[maxn],w[maxn];//h记录栅栏边界高，w记录栅栏的宽。
double ans;
int main(){
	scanf("%d",&n);
	for(int i=0;i<=n;i++) scanf("%d",&h[i]);
	for(int i=0;i<n;i++) scanf("%d",&w[i]);
	for(int i=0;i<n;i++) ans+=(double)(h[i]+h[i+1])*w[i]/2;//计算每一个梯形的面积。
	printf("%.1f",ans);//格式化输出。
	return 0;
}
```


---

## 作者：小明小红 (赞：0)

# P9024 [CCC2021 S1] Crazy Fencing题解

**前置知识**：梯形的面积。

**分析**：我们根据样例解释可以发现其实算的是梯形的面积和，学过小学的都知道，$S=\frac{(l+r)\times h}{2}$，也就是面积等于上底加下底乘高除以二。那我们就可以依次相加。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
double d,s[10009],a[10009];//记得设double 
int main() 
{
    cin>>n;
    for(ll i=1;i<=n+1;i++)
    {
    	cin>>s[i];
	}
	for(ll j=1;j<=n;j++)
	{
		cin>>a[j];
	}
	for(ll i=1;i<=n;i++)
	{
		d+=(s[i]+s[i+1])*a[i]/2;//套公式 
	}
    printf("%.1lf\n",d);//保留小数输出 
    return 0;
 } 
```


---

## 作者：lilong (赞：0)

一道简单的签到题。

每两个栅栏之间就相当于构成了一个梯形，两边的栅栏分别为上底和下底，木板的宽度为高，因此按照梯形的面积计算公式计算每块木板的面积，再计算总和即可。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,a[100001],b[100001];
double ans=0.0;
int main()
{
    cin>>n;
    for(int i=1;i<=n+1;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        cin>>b[i];
    for(int i=1;i<=n;i++)
        ans=ans+double((a[i]+a[i+1])*1.0*(b[i]*1.0)/2.0);
    printf("%.1lf",ans);
    return 0;
}
```


---

## 作者：HarryKane (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9024)。

这题依照题意模拟即可。

已知梯形面积公式：$\frac {(a+b) \times h} {2} $。其中 $a$ 和 $b$ 分别为上底和下底的长度，$h$ 为高的长度。

## Ac Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e4;
int a[N+5], h[N+5];//分别为底长度和高长度。

int main (){
	int n; cin >> n;
	for (register int i=1; i<=n+1; ++i) cin >> a[i];
	for (register int i=1; i<=n; ++i) cin >> h[i];
	double ans=0;
	for (register int i=1; i<=n; ++i) ans+=(a[i]+a[i+1])*h[i]*1./2;//计算公式。
	printf ("%.1lf", ans);
	return 0;
}
```

---

