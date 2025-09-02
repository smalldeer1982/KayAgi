# Annoying Present

## 题目描述

`Alice` 又得到了一个长度为 $n$ 的数组作为生日礼物！这是她得到这样的礼物的第三年了！

更令人失望的是，这个数组非常无趣，每个元素都是 $0$ 。`Bob` 决定对数组进行一些修改使 `Alice` 兴♂奋起来。

`Bob` 进行了以下的 $m$ 次修改。每次修改包含 $2$ 个整数 $ x $ 和 $d$ 。他选择一个任意位置 $i (1 \le i \le n)$，并且对于每个 $j \in [1，n]$ ，会把第 $j$ 个单元格的值加上 $x + d \cdot dist(i，j)$ 。 $dist(i，j)$ 是位置 $i$ 和 $j$ 之间的距离（即 $dist(i,j)= | i-j |$ ，其中 $|x|$ 是 $x$ 的绝对值。)

例如，如果 `Alice` 当前有着数组 $ [2,1,2,2] $，而 `Bob` 选择位置 $3$ 来执行修改 $x = -1$ 和 $d = 2$ ，则该数组将变成 $[2-1 + 2 \cdot 2，1-1 + 2 \cdot 1，2-1 + 2 \cdot 0，2-1 + 2 \cdot 1] =  [5,2,1,3]$。请注意，`Bob` 不能在数组之外选择位置 $i$（即 $i$ 必须在 $1 $ ~ $ n$ 范围内）。

当数组中的元素尽可能大时，`Alice` 将是最快乐的。 `Bob` 声称数组元素的算术平均值可以很好地用作度量。

`Bob` 可以达到的最大算术平均值是多少？

## 样例 #1

### 输入

```
2 3
-1 3
0 0
-1 -4
```

### 输出

```
-2.500000000000000
```

## 样例 #2

### 输入

```
3 2
0 2
5 0
```

### 输出

```
7.000000000000000
```

# 题解

## 作者：Wendy_Hello_qwq (赞：3)

[题目传送门。](https://www.luogu.com.cn/problem/CF1009C)

[原文食用效果更佳。](https://www.luogu.com.cn/article/4jqxue0g)

## 题意

给出数列的长度 $n$，进行 $m$ 次操作，操作具体步骤见题目，最后求此数组最大的算数平均值是多少。

## 分析

题目想让我们求尽可能大的平均值，从头到尾数字个数 $n$ 都不变，所以要让数字总和尽可能的大。根据题目可得知，每次的修改是 $x + d \cdot dist(i,j)$，所以只要 $d$ 大于 $0$，就加上算出来的最大值；如果 $d$ 小于等于 $0$，就加上算出来的最小值。

## Code

```cpp
#include <cstdio>
using namespace std;
double res;
long long n, m, x, d, max1, min1;
int main() {
	scanf ("%lld%lld", &n, &m);
	// 最大值 
	max1 = n * (n - 1) / 2;
	// 最小值 
	min1 = (n / 2) * (n / 2 + 1);
	// 个数为偶，继续减 
	if (n % 2 == 0)
		min1 = min1 - n / 2;
	for (int i = 1; i <= m; i++) {
		scanf ("%lld%lld", &x, &d);
		// 答案加进 x * n 的值 
		res = res + x * n;
		// 根据题目，d 大于 0，加上最大值 
		if (d > 0)
			res = res + max1 * d;
		// 反之加上最小值 
		else
			res = res + min1 * d;
	}
	// 保留 10 位小数输出 
	printf ("%.10lf", res / (n * 1.0));
	return 0;
}
```

完结撒花。

作者写题解不易，点个赞再走呗。

---

## 作者：__Immorta__ (赞：3)

**前言：水黄水黄啊。CF不可用，但是并不影响做题**

**一言**：~~我写题解都是打句号都是拼音输入“句号”，选择第五个的“。”awa~~不知道为甚恶魔专栏打不出正常句号。

**题目分析：**

这个问题可以通过分析每次修改对数组的影响来解决。只需要需要找到一种方式，使得数组中的所有元素尽可能大，从而使得平均值最大。

**代码使用的头文件：**

基础头文件：
```c
#include <iostream>
#include <vector>
```
使用万能头：
```c
#include <bits/stdc++.h>
```

**具体代码：**

- 首先是变量方面：
```c
int n,m;
vector<long long> num(n, 0);
```
定义 `n` 和 `m` ，作为输入变量，定义动态数组，作为后续输入。

首先，对于任意的 `i` 和 $(i,j)$ 的值都是非负的。这意味着对于任意的 `x` 和 `y` ，数组中的每个元素都会增加一个非负的值。因此，我们可以通过选择合适的 `i` 来最大化每个元素的增量。

观察发现，对于任意的 `i` ，当 `j` 越接近 `i` 时，$(i,j)$ 越小，从而增量越小。因此，为了最大化每个元素的增量，应该选择一个 `i` ，使得它距离数组中心越近越好。特别地，当 `n` 是奇数时，应该选择中间的元素；当 `n` 是偶数时，可以选择中间两个元素中的任意一个。

接下来，我们需要计算每次修改对数组的影响。对于任意的 `i` 和 `j`，第 `j` 个元素的增量是 $x+d \times dist(i,j)$ 。因此，可以遍历数组中的每个元素，计算它们的增量，并更新数组。

```c
for (int i=1;i<=m;i++){
  int x,y;
  cin>>x>>y;
  int cnt=n/2;
  for(int j=1;j<=n;j++) {
    num[j]+=x+y*abs(cnt-j);
  }
}
double sum=0;
for (int i=1;i<=n;i++) {
  sum+=num[i];
}
```

- 最后，计算数组的平均值，并输出结果。

```c
double sum=sum/n;
printf("%.10lf",sum);
```

最后的最后，总体代码[放在这里啦](https://www.luogu.com.cn/paste/n2orhqr6)，管理大大求过~

---

## 作者：Never_care (赞：1)

### 思路
每次修改数值均为 $d⋅dist(i,j)+x$，且在不可改变原本数字数量让总和尽量大，则 $d$ 应为大于 $0$ 的正整数，最后累计即可。

### code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f 
using namespace std;
ll n,m;
int main(){
	cin>>n>>m;
	ll maxx=n*(n-1)/2;
	ll minx=(n/2)*(n/2+1);
	if(n%2==0){
		minx=minx-(n/2);
	}
	double temp=0;//总和 
	for(int i=1;i<=m;i++){
		ll x,d;
		cin>>x>>d;
		temp+=n*x;//加入n*x。 
		if(d>0){
			//大于0让最大值加。
			temp+=d*maxx;
		}//小于0让最小值加。 
		else temp+=minx*d;
	}
	cout<<fixed<<setprecision(10)<<temp/(n*1.0);
	return 0;
}
```

---

## 作者：TiAmo_qwq (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1009C)



---

题目意思题目中给的很详细了，直接说思路。

# 思路
由于想让平均数尽可能的高，数量 $n$ 不变，总数就应该尽可能的高，从题目中得知修改数值为 $x+d\cdot dist(i,j)$，$x$ 不变，说明 $d$ 越大，总数越大。反之，$d$ 越小，总数越小。如果 $d$ 小于 $0$，则会越加越小，所以少加，如果 $d$ 大于 $0$，会越加越多，所以多加。

这样，一道题就做出来了。


---
# CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define LL long long
const int N = 1e6 + 10;

int main()
{
	LL n, m, x, d;//定义
	cin >> n >> m;//输入
	
	LL maxn = n * (n - 1) / 2;//最大
	LL minn = (n / 2) * (n / 2 + 1);//最小
	
	if(n % 2 == 0)
	{
		minn = minn - (n / 2);//多减就加
	}
	
	double ans = 0;//总数
	
	for(LL i = 1; i <= m; i++)
	{
		cin >> x >> d;//输入
		ans = ans + x * n;//把n * x加进去
		
		if(d > 0) ans = ans + maxn * d;//如果大于0，多加
		else ans = ans + minn * d;//反之，少加
	}
	cout << fixed << setprecision(10) << ans / (n * 1.0);输出
	return 0;
}
//cf1009c

```

---

## 作者：yuheng_wang080904 (赞：1)

## 题意

给定一个数组 $A$ 和它的元素个数 $n$。初始 $A_i=0(1\le i \le n)$。一共 $m$ 次操作，每次操作给定一个 $x$ 和一个 $d$，你可以自选一个 $i(1\le i \le n)$，对于所有 $j \in [1,n]$，让 $A_j$ 加上 $x+d \times \lvert i-j \rvert$。问操作完这 $m$ 次后，$A$ 数组最大的算数平均值是多少。

## 思路

由于 $A$ 数组的元素个数固定，因此要求其算数平均值的最大值就是要求出 $\sum_{i=1}^n {A_i}$ 的最大值。每次 $A$ 数组和增加的值为 $\sum_{j=1}^n x+d \times \lvert i-j \rvert$，因为 $x$ 和 $d$ 为常量，因此我们每次都要最大化 $d \times\sum_{j=1}^n  \lvert i-j \rvert$。

如果 $d \le 0$，那么就使 $\sum_{j=1}^n \lvert i-j \rvert$ 最小，此时 $i$ 取中间值，即若 $n=2k+1(k \in N^* )$，则取 $i=k+1$。否则若 $n=2k(k \in N^* )$，则取 $i=k$。如果 $d>0$，那么可以取 $i=1$ 使得$\sum_{j=1}^n \lvert i-j \rvert$ 最大。

这个最大化 $\sum_{j=1}^n d \times \lvert i-j \rvert$ 的正确性可以用二次函数或者绝对值的几何意义来证明，这里就不赘述了。

如果 $d \le 0$ 且 $n=2k+1(k \in N^* )$，那么可以得到 $(d \times\sum_{j=1}^n \lvert i-j \rvert)_{min}=d \times \frac{n-1}{2}\times \frac{n+1}{2}$，代码中可以写为：
```cpp
long long mini=d*(n/2)*(n/2+1);//C++自动向下取整
```

如果 $d \le 0$ 且 $n=2k(k \in N^* )$，那么可以得到 $(d \times\sum_{j=1}^n \lvert i-j \rvert)_{min}=d \times (\frac{n}{2})^2$。

如果 $d>0$，那么可以得到 $(d \times\sum_{j=1}^n \lvert i-j \rvert)_{min}=d \times \frac{n \times (n-1)}{2}$。

代码就可以对应着这几种情况写出来了，十分简短，时间复杂度为 $O(m)$，注意输出时的精度！

## 代码

接下来上我的代码。请大家掌握思路，不要抄袭！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,d,ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    long long maxi=n*(n-1)/2,mini=(n/2)*(n/2+1);
    if(n%2==0)mini-=n/2;
    while(m--){
	cin>>x>>d;
	ans+=x*n;
	if(d>0)ans+=maxi*d;
	else ans+=mini*d;
    }
    printf("%.8lf",1.0*ans/n);
    return 0;
}
```


---

## 作者：Fearliciz (赞：0)

第一眼看到这题便认为是一道 $\texttt{dp}$，可是后来在推转移的时候发现了一个规律，于是 $\texttt{dp}$ 就变成了贪心。

分析一下操作，发现不论选择哪一个位置，都要加上 $n$ 个 $x$。于是我们将它先加好，放在一边，不看。剩下的便是 $d$ 了，要想使 $d$ 最大，就要使总共加 $d$ 的次数最多（当 $d<0$ 时最少）。

首先给人的感觉就是放在哪里 $d$ 的总数都一样，经过画图才知道它们大相径庭。

以下是选择的位置在边上的情况中 $d$ 的数量（可以理解为红色部分的面积）

![](https://cdn.luogu.com.cn/upload/image_hosting/agahn8b9.png?x-oss-process=image)

而这个是选择的位置在中间的情况中 $d$ 的数量

![](https://cdn.luogu.com.cn/upload/image_hosting/7035og1t.png?x-oss-process=image)

图中的被绿色圆圈圈出的红色平行四边形就是放在边上比放在中间多出去的部分。

知道这些代码就很好写了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long mind,maxd,n,m,x,d,sum;
int main()
{
	cin>>n>>m;
	maxd=n*(n-1)/2,mind=(n/2)*(n/2+1)-(n%2==0?n/2:0);
	for(int i=1;i<=m;i++)
	{
		cin>>x>>d;
		sum+=x*n;
		if(d<0) sum+=mind*d; //如果d小于0那么就放到中间
		else sum+=maxd*d; //如果d大于0那么就放到边上
	}
	printf("%.10lf",(1.0*sum)/n);
    return 0;
}

```


---

## 作者：lichenfan (赞：0)

### 直接暴力模拟
考虑两种情况，让算数平均数最大就是让总和最大，如果 $d$ 小于 $0$，也就是说加了会让总和变小，只要让他加的最少即可，就是放在最中间。如果 $d$ 大于 $0$。就放在最边上，可以让加的最多。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,d,ans;
int main()
{
	cin>>n>>m;
	long long mx=n*(n-1)/2,mn=(n/2)*(n/2+1);      //最大与最小 
	if(n%2==0) mn-=n/2;                           //考虑多减了，得加上 
	for(int i=1;i<=m;i++){
		cin>>x>>d;
		ans+=x*n;                             //n个x 
		if(d>0) ans+=mx*d;                    //如果d大于零，就多加 
		else ans+=mn*d;                       //否则少加 
	}
	printf("%.10llf",1.0*ans/n);                  //算平均数是记得转换浮点 
 } 
```



---

## 作者：小闸蟹 (赞：0)

```cpp
// 首先我们可以观察到，x其实对于整个数组的元素之和没有太大调整空间，每次数组之和都加上x * n即可
// 然后我们再看d，由于d有正负之分，所以我们想要d为正的时候|i - j|尽量大，d为负的时候|i - j|尽量小
// 当d为正的时候，我们取的基准点j应该为1或者n，这样|i - j|就尽量大
// 当d为负的时候，我们取得基准点j应该为(n / 2)，这样|i - j|就尽量小
// 证明可以参考刘汝佳蓝书的第六页，有对于这个问题的详细说明
#include <iostream>
#include <iomanip>

using ll = long long;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll n, m;
    std::cin >> n >> m;

    ll Sum = 0, Min = (n / 2) * (n / 2 + 1) - (n % 2 ? 0 : n / 2), Max = n * (n - 1) / 2;
    while (m--)
    {
        ll x, d;
        std::cin >> x >> d;

        Sum += x * n;
        if (d > 0)
        {
            Sum += Max * d;
        }
        else
        {
            Sum += Min * d;
        }
    }
    std::cout << std::fixed << std::setprecision(15) << 1.0 * Sum / n << std::endl;

    return 0;
}
```

---

