# Two Round Dances

## 题目描述

有一天，$n$ 人（$n$ 是偶数）在广场上相遇，跳了两支圆舞曲，每支圆舞曲正好由$\frac{n}{2}$人组成。你的任务是找出 $n$ 人可以跳两支圆舞的方案数量。每个人应该正好属于这两种圆舞中的一种。

圆舞是由 $1$ 人或更多的人组成的舞蹈圈。如果两个圆舞可以通过选择第一个参与者转化为另一个圆舞，则两个圆舞是无法区分（相等）的。例如，圆舞 $[1,3,4,2]$ ，$[4,2,1,3] $和 $[2,1,3,4] $是不可区分的。

例如，如果 $n=2$，那么方式的数量是 $1$：一个圆舞曲由第一个人组成，第二个人的圆舞曲由第二个人组成。

例如，如果 $n=4$，那么路数是  $3$ 。可能的方案：

- 一个圆舞曲 $[1,2]$ , 另一个 $[3,4]$ 。
-  一支圆舞 $[2,4]$ ，另一支 $ [3,1] $。
- 一个圆舞$ [4,1]$，另一个 $ [3,2]$ 。

你的任务是：如果每个圆舞曲正好由$\frac{n}{2}$人组成，找出 $n$ 人可以跳两支圆舞曲的方案数量。

## 样例 #1

### 输入

```
2```

### 输出

```
1```

## 样例 #2

### 输入

```
4```

### 输出

```
3```

## 样例 #3

### 输入

```
8```

### 输出

```
1260```

## 样例 #4

### 输入

```
20```

### 输出

```
12164510040883200```

# 题解

## 作者：rouxQ (赞：10)

## 题意
将 $n$ 个正整数 $1\sim n$ 分为个数均为 $\dfrac{n}{2}$ 的两组，每组内元素排成一个环，求不同的方案数。
## $\operatorname{Sol}$
先不考虑环的排列，显然一组可以有 $C_n^\frac{n}{2}$ 种选法。

对于每一种选法，若不考虑环带来的重复，显然排列方法为 $(\dfrac{n}{2})!$。对于每一个环，它显然可以把每 $\dfrac{n}{2}$ 种情况缩为一种。所以对于每一种选法，一组的合法方案为：
$$\dfrac{(\dfrac{n}{2})!}{\dfrac{n}{2}}=(\dfrac{n}{2}-1)!$$
所以总答案为：
$$\dfrac{C_n^\frac{n}{2}\times [(\dfrac{n}{2}-1)!]^2}{2}$$

（因为两组互换是同一种情况，所以除以二）

式子有点丑，化一下：
$$\begin{aligned}\dfrac{C_n^\frac{n}{2}\times [(\dfrac{n}{2}-1)!]^2}{2} & = \dfrac{1}{2}\times \dfrac{{n!}}{[(\dfrac{n}{2})!]^2}\times [\dfrac{(\dfrac{n}{2})!}{\dfrac{n}{2}}]^2 \\ & = \dfrac{2\times (n-1)!}{n}\end{aligned}$$

## $\operatorname{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int main (){
    long long n, ans = 1;
    cin >> n;
    for (int i = 1; i < n; i++)ans *= i;
    cout << ans * 2 / n << endl;
    return 0;
}
```

---

## 作者：Rainy7 (赞：8)

- **前言**

  upt2020/10/23:修改了一个笔误。感谢 [@vectorwyx](https://www.luogu.com.cn/user/238408) 。

  手玩那个逆时针顺时针半天，以为是圆排列+镜面，结果突然来消息改题了（雾）。

------------

- **分析**

  $n$ 个人可以分成 $2$ 组，且组别没有任何区别。
  
  假设先单看组合，那分成两组的数量就是 $\dfrac{1}{2} \times C_n^ \frac{n}{2}$ 。
  
  现在看单个组。
  
  一个组可以通过转圈圈来改变不同的阵容，写的很清楚了，就是圆排列。
  
  因为 $n$ 的圆排列为 $(n-1)!$ 。然后这里又有 $2$ 组。
  
  所以答案为 $\dfrac{1}{2} \times C_n^ \frac{n}{2} \times ((\dfrac{n}{2}-1)!)^2$ 。
  
  因为数据较小 $n \le 20$ ，所以开头阶乘直接预处理即可。
  
  复杂度 $O(n)$ 。

------------

- **代码**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const ll Maxn=20+5;
ll n,mul[Maxn];
int main()
{	scanf("%lld",&n);
	mul[0]=1;
	for(ll i=1;i<=n;i++)mul[i]=1ll*mul[i-1]*i;
	printf("%lld\n",mul[n]/mul[n/2]/mul[n/2]/2*mul[n/2-1]*mul[n/2-1]);
	return 0;
}
```

---

## 作者：vectorwyx (赞：4)

简单排列组合，做这题之前请先了解[排列组合之圆桌问题](https://wenku.baidu.com/view/6f73cb0e10661ed9ad51f393.html#)。

参与舞蹈的人不同，方案肯定算作不同。因此我们可以把整个问题划分为两个部分：选人，排列。

先看选人的部分。我们给这两支舞蹈队确定一个顺序，先从 $n$ 个人中选 $\frac{n}{2}$ 个人组成第一支舞蹈队，方案数为 $C_{n}^{\frac{n}{2}}$，剩下的人组成第二支舞蹈队，方案数只有 $1$ 种。但实际上我们的舞蹈队是没有顺序的，因此还要把总方案数除以 $2$，也就是 $\frac{1}{2}\times C_{n}^{\frac{n}{2}}$ 种不同的方案。

接下来，我们需要对两支舞蹈队里的人员分别进行排列。注意，这里要求一个方案顺时针和逆时针任意旋转得到的方案都算作是相同的，因此是两个圆桌问题（有人可能会对逆时针感到困惑，但逆时针旋转就是另一种顺时针旋转，因此并不影响），方案数均为 $(\frac{n}{2}-1)!$ 种。根据乘法原理，排列部分的方案数就是 $((\frac{n}{2}-1)!)^{2}$ 种。

综上，答案为 $\frac{1}{2}\times C_{n}^{\frac{n}{2}}\times ((\frac{n}{2}-1)!)^{2}$，化简一下，答案为 $\prod_{i=\frac{n}{2}+1}^{n-1}\times \prod_{i=2}^{\frac{n}{2}-1}$

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ull unsigned long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}


int main(){
	int n=read();
	ull sum=1;
	fo(i,n/2+1,n-1) sum*=i;
	fo(i,2,n/2-1) sum*=i;
	cout<<sum;
	return 0;
}
```


---

## 作者：cute_overmind (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1433E)

### 题目大意
将 $n$ 个人分成 $2$ 组，每个组中有 $\frac{n}{2}$ 人，求找出 $n$ 人可以跳两支圆舞曲的方案数量。

题目说那么多，其实就是让我们去求出两个**圆环全排列**的方案数。

### 题目分析
一道简单的**组合数学**题，不了解的可以先去[这里](https://baike.baidu.com/item/%E7%BB%84%E5%90%88%E6%95%B0%E5%AD%A6/821134?fr=aladdin)或者[这里](https://wenku.baidu.com/view/6f73cb0e10661ed9ad51f393.html?_wkts_=1717132159224&needWelcomeRecommand=1#)了解有关知识。

看到题目的数据，发现是 $2 \le n \le 20$。如果直接暴力搜索会**超时**，所以这里我们可以尝试**推导公式**。

注意：既然题目样例那么大，我们就不应该选择 `int`，而要选择 `long long` 进行求解。

### 推导过程

在考虑圆环排列之前我们先看到普通排列，发现每一组中刚好是算到 $n \div 2$ 次。

所以当我们分成两组的时候一共就会有 $\large\frac{1}{2}(\frac{n}{2}-1)!$。

但这并不是**最终答案**，显然可得两个圆环的排列数要把其中一个排列数的值再乘上它的**平方倍**才能得出最终答案。

所以可得：
$$\frac{1}{2}\times\frac{n!}{(\frac{n}{2}!)^2}\times \begin{bmatrix}(\frac{n}{2}-1)!\end{bmatrix}$$

我们进一步化简公式可得：
$$\frac{2 \times(n-1)!}{n}$$
所以我们就可以得到一个靠**阶乘**求解的代码，时间复杂度也是足以让我们通过这道题。

### [代码](https://www.luogu.com.cn/record/160798599)
~~都直接是阶乘了还要贴代码。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n , ans = 1;
int solve()
{
	for (int i = 1;i < n;i++) ans *= i;
	return ans;
}
signed main()
{
    cin >> n;
    cout << solve() * 2 / n;
    return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

## 题解：CF1433E Two Round Dances
## 思路
要解决这个问题，我们需要将 $n$ 人分成两个大小为 $\frac{n}{2}$  的组，并确保每个组形成一个圆舞曲的方式。我们将利用组合数和阶乘来实现这一点。

1. **组合数**

首先计算将 $n$ 人分成两个大小为 $\frac{n}{2}$ 的组的方式，使用组合数公式 $C_{n}^{\frac{n}{2}}$。

2. **圆舞曲的排列**

对于每个组，由于每个组是一个环形排列（圆舞曲），而环形排列的方式为 $(\frac{n}{2} - 1)!$。因此，每个组的圆舞曲排列数为 $(\frac{n}{2} - 1)!$。

3. **考虑重复**

由于两个组是对等的，所以我们在计算总方案数时需要除以2。总方案数可以表示为：$\frac{C_{n}^{\frac{n}{2}} \times ((\frac{n}{2} - 1)!)^2}{2} $
## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
#define pb emplace_back
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;

ll n;

ll f(ll n)
{
    ll ans = 1;
    ll i;
    for (i = 2; i <= n; i++)
	{
        ans *= i;
    }
    return ans;
}

ll AK(ll n, ll k)
{
	ll i;
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    ll ans = 1;
    for (i = 1; i <= k; i++)
	{
        ans *= (n - k + i);
        ans /= i;
    }
    return ans;
}

int main()
{
	//freopen("xxx.in","r",stdin);
	//freopen("xxx.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll i, j;
    cin >> n;
    ll cnt1 = AK(n, n / 2);
    ll cnt2 = f(n / 2 - 1);
    ll ans = (cnt1 * cnt2 * cnt2) / 2;
    cout << ans << endl;
	return 0;
}
```

---

## 作者：GeYang (赞：1)

# 题意

求 $n$ 人中寻找不同的 $\frac{n}{2}$ 人组合的数量。

# 思路

考虑**排列组合**，其实就是求 $\frac{1}{2} \times C^\frac{n}{2}_n \times [(\frac{n}{2}-1)!]^2$ 的值。

化简:

$$\frac{1}{2}\times\frac{n!}{(\frac{n}{2})^2} \times[(\frac{n}{2}-1)!]$$

可得：

$$ \frac{2\times(n-1)!}{n}$$

所以用阶乘即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,ans=1;
int solve()
{
	for(int i=1;i<a;++i)
		ans*=i;
	return ans;
}
int main()
{
	cin>>a;
	cout<<solve()*2/a;
	return 0;
}
```

---

## 作者：sea_bird (赞：1)

# 一道环形的排列组合题

[题目传送门](https://www.luogu.com.cn/problem/CF1433E)。

## 题目分析

一开始我对着数据是有些愣的，后来我看了英文题面，发现要注意两点。

1 圆舞是由一个人或多个人组成的**舞蹈圈**。

2 是分为 $2$ 组，每组有 $\frac{n}{2}$ 人。

好，看完题目我们来看看如何具体的去写，首先我们不考虑环形，只考虑直线的情况，这是小学便学过的，运用~~百度优先搜索~~小学知识可以得出公式 $(n-1)!$ 从而算出结果，至于如何推出的，首先我们先考虑第一个，第一个需要跟自己以外的所有人配对，所以是 $n-1$ 个，第二个因为不能重复，所以是 $n-2$ 个，以此类推，最后相乘，从而得到这个公式。

考虑完线，再考虑环，在使用百度~~优先搜索~~后，我们发现，环形的问题是位置不确定，但只要有一个确定其它的相对位置便能确定，当然，首先还是按线来处理 $(n-1)!$，因为是两组，所以每组有 $\frac{n}{2}$ 人，在按普通组合来看时会发现每一组算了 $\frac{n}{2}$ 次，所以写出 $\frac{1}{2}×(\frac{n}{2}-1)!$。

接下来是第二步，因为是两个环形，所以要把其中一个圆环的排列数的值乘上其平方倍 $[(\frac{n}{2}-1)!]^2$，接着列出完整的式子得 $\frac{1}{2}×\frac{n!}{\frac{n}{2}!×(n-\frac{n}{2})!}×[(\frac{n}{2}-1)!]^2$ 化简完后得出式子 $2×(n−1)!÷n$ 写出阶乘后再处理一下就可以了。

## Code

```
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<math.h>
#include<queue>
#include<stack>
#include<cstdio>
#include<stdio.h>
#include<string>
#include<vector>
using namespace std;
unsigned long long int fac(unsigned long long int a){//递归函数 
	if(a<=1){//终止条件
		return 1;
	}
	else{
		return fac(a-1)*a;//计算阶乘 
	}
}
unsigned long long int ans(unsigned long long int a,unsigned long long int b){
	return a*2/b; 
}
int main(){
	unsigned long long int n,cnt=1;//记得long long
	cin>>n;
	cout<<ans(fac(n-1),n)<<endl;
	return 0;
}
```

## 总结

这道题有很多种写法，直接搜索也行~~超时警告~~，不过推导出公式后更方便，更省时间~~主要是不知道如果用搜索这个怎么写~~。

[AC](https://www.luogu.com.cn/record/161246478)。

---

## 作者：Cheese_int (赞：1)

## 题目传送门
[CF1433E](https://www.luogu.com.cn/problem/CF1433E)
 
**请读完题目再食用**。如果不了解这道题，可以先看一下[组合数学](https://baike.baidu.com/item/%E7%BB%84%E5%90%88%E6%95%B0%E5%AD%A6/821134?fr=aladdin)。

## 题意：
这是一道很经典的**圆桌排列问题(组合数学)**。题目要求我们求出两个环全排列的方案。


## 强调问题：
在做这道题的时候要看好**数据范围**， 20 会炸 `int`，一定要记得开 `long long`。

## 题解：
1. 这是一道基础的**组合数学**。
1. 首先我们看到数据范围，$2\leq n \leq20$。 在看样例输入3，测试点巨大，所以我们不能**爆搜**~~（也因为我不会）~~，如果你非要爆搜，那你就喜提 TLE。所以我们优先考虑**推导数学式**。
1. 我们需要把 $n$ 个人分成**两组**，因为这是两个圆舞曲。那么每组就是 $n \div 2$ 个人。我们就推算出来了第一步。
1. 接下来对于每一组，我们先**不管圆排列**，直接按照**基础排列**计算，那么可以发现每一种情况都恰好算了 $n \div 2$ 遍。所以**分成两组**的答案就是：
	
    $\dfrac{1}{2}\cdot(\dfrac{n}{2}-1)!$ 
    
1. 因为在上一点中我们求得是一个圆舞曲的排列数，所以我们求两个圆舞曲的排列数要把一个排列数的值再乘上**平方倍**，这样我们就求出了两个圆舞曲排列的个数。
1. 那么最终的答案就是：

 	$\dfrac{1}{2}\cdot\dbinom{n}{\frac{n}{2}}\cdot\left[(\dfrac{n}{2} - 1)!\right]^2$
    
1. 接下来那我们**化简**一下式子：
    
    $\dfrac {1}{2}\cdot\dbinom{n}{\frac{n}{2}}\cdot\left[(\dfrac{n}{2} - 1)!\right]^2 $
    
  
    $=\dfrac{1}{2}\cdot\dfrac{n!}{(\frac{n}{2}!)^2} \cdot \left[\dfrac{(\frac{n}{2})!}{\frac{n}{2}}\right]^2$
    
    $=\dfrac{\dfrac{n!}{(\frac{n}{2}!)^2}\cdot \left[\dfrac{(\frac{n}{2})!}{\frac{n}{2}}\right]^2}{2}$
    
    $=\dfrac{2\cdot(n - 1)!}{n}$
    
1. 最后说一下这道题的时间复杂度是 $O(n)$ (推算阶乘)。 
1. 这道题推荐大家自己尝试推出式子。锻炼一下大家的思考能力。



## 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
long long n;
long long ans = 1;	//求阶乘要用 

long long j (long long x) {	//求阶乘函数
	long long ans = 1;
	for (int i = 1; i <= x; i++) {
		ans *= i;
	}
	return ans;
} 

int main () {
    scanf ("%lld", &n);
    /*套用数学公式*/
    printf ("%lld\n", j (n - 1) * 2 / n); 
    return 0;
}
```



---

## 作者：KSToki (赞：1)

~~看到数据范围发现可以打表~~

于是：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	while(ch<'0'||ch>'9')
	    ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
int n;
ll ans[21]={0,0,1,2,3,12,40,240,1260,10080,72576,725760,6652800,79833600,889574400,12454041600,163459296000,2615348736000,39520825344000,711374856192000,12164510040883200};
int main()
{
	n=read();
	printf("%lld\n",ans[n]);
	return 0;
}
```
咳咳，言归正传，这是一道数学（排列组合）题。分成两半，每一半都可以随意调换顺序，简单化一化式子即可，还算比较简单，~~代码也很优美~~。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	while(ch<'0'||ch>'9')
	    ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res;
}
int n;
ll ans=1;
int main()
{
	n=read();
	for(register int i=n/2+1;i<=n-1;++i)
		ans*=i;
	for(register int i=2;i<=n/2-1;++i)
		ans*=i;
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1433E)

# 前置知识

[圆排列](https://oi-wiki.org//math/combinatorics/combination/#%E5%9C%86%E6%8E%92%E5%88%97)

# 解法

$\dfrac{Q_{n}^{\frac{n}{2}}Q_{\frac{n}{2}}^{\frac{n}{2}}}{A_{2}^{2}}$ 即为所求。

同时因为 $n \le 20$ 和没有模数，所以不需要处理逆元，暴力算即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
int main()
{
    ll n,ans=1,i;
    cin>>n;
    for(i=n-n/2+1;i<=n;i++)
    {
        ans*=i;
    }
    ans/=(n/2);
    for(i=1;i<=n/2-1;i++)
    {
        ans*=i;
    }
    ans/=2;
    cout<<ans<<endl;
    return 0;
}
```

---

