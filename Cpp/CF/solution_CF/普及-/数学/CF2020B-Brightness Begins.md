# Brightness Begins

## 题目描述

想象你有 $n$ 个编号为 $1, 2, \ldots, n$ 的灯泡。最初，所有灯泡都是开着的。翻转一个灯泡的状态意味着如果它原来是开着的，就把它关掉；否则就把它打开。

接下来，您需要执行以下操作：

对于每个 $i=1,2,\ldots,n$，翻转所有灯泡 $j$ 的状态，使得 $j$ 能被 $i^\dagger$ 整除。

在执行完所有操作后，将会有一些灯泡仍然亮着。你的目标是使这个数量恰好为 $k$。

找到最小的合适 $n$，使得执行操作后，灯泡的数量恰好为 $k$。我们可以证明答案总是存在的。

$ ^\dagger $ 如果存在一个整数 $ z $ 使得 $ x = y\cdot z $ ，那么一个整数 $ x $ 可以被 $ y $ 整除。

## 说明/提示

在第一个测试用例中，最小数量的灯泡是 $2$。让我们用一个数组来表示所有灯泡的状态，其中$1$对应于打开的灯泡，$0$ 对应于关闭的灯泡。最初，数组是 $[1, 1]$。

- 在执行了 $i=1$ 的操作后，数组变成了 $[\underline{0},\underline{0}]$。
- 在执行了 $i=2$ 的操作后，数组变成了 $[0,\underline{1}]$。

最后，有 $k=1$ 个灯泡亮着。我们还可以证明答案不可能小于 $2$。

在第二个测试用例中，最小数量的灯泡是 $5$。最初，数组是 $[1, 1, 1, 1, 1]$。

- 在执行了 $i=1$ 的操作后，数组变成了 $[\underline{0},\underline{0},\underline{0},\underline{0},\underline{0}]$。
- 在执行了 $i=2$ 的操作后，数组变成了 $[0,\underline{1},0,\underline{1},0]$。
- 在执行了 $i=3$ 的操作后，数组变成了 $[0,1,\underline{1},1,0]$。
- 在执行了 $i=4$ 的操作后，数组变成了 $[0,1,1,\underline{0},0]$。
- 在执行了 $i=5$ 的操作后，数组变成了 $[0,1,1,0,\underline{1}]$。

最后，有 $k=3$ 个灯泡亮着。我们还可以证明答案不可能小于 $5$。

翻译者：[jiangyunuo](https://www.luogu.com.cn/user/1061050)。

## 样例 #1

### 输入

```
3
1
3
8```

### 输出

```
2
5
11```

# 题解

## 作者：mc_xiexie (赞：9)

我给出一种 $O(1)$ 方案。

我们通过推论推出了在 $1$ 到 $n$ 中有 $\sqrt{n}$ 个完全平方数，此时我们只需要找到一个 $n$ 使 $n-\sqrt{n}=k$ 即可。

但我们发现最终 $n$ 其实是 $k$ 加上完全平方数个数，所以 $n=k+\sqrt{k}$。

AC 代码:
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long x;
		cin>>x;
		cout<<x+(long long)(sqrtl(x)+0.5)<<"\n";
	}
}
```

---

## 作者：NEKO_Daze (赞：6)

[洛谷CF2020B](https://www.luogu.com.cn/problem/CF2020B) || [CodeForces 2020 B](https://codeforces.com/contest/2020/problem/B)

### 简要题意
房间中有 $n$ 盏灯，它们初始状态都是亮着的。

接下来进行 $n$ 次操作，第 $i$ 次操作会将编号为 $i$ 的倍数的灯改变状态。改变状态是指如果灯是亮的，那么改变后就变成关的；如果灯是关的，那么改变后就变成亮的。

设 $n$ 次操作后有 $k$ 盏灯是亮着的。现在仅给出 $k$，请问最少需要多少盏灯，才能保证有 $k$ 盏灯最后是亮着的？

### 思路
众所周知，一盏灯最后的状态如何取决于它有几个因数。而一盏灯如果最后是亮的，那么其因数数量一定为偶数，即非完全平方数。

因此，问题可以简化为：**寻找第 $k$ 个非完全平方数。**

前半部分非常典，所以走到这一步并不难，本题的难点在如何快速找到这个数。

审题得知 $k\le 10^{18}$，所以直接枚举必然超时，选择二分答案是一个不错的选择。

那么如何得知 $1,2,3,\dots,n-1,n$ 中共有多少个非完全平方数呢？

> 引理：在 $1,2,3,\dots,n-1,n$ 中一共有 $\lfloor\sqrt{n}\rfloor$ 个完全平方数。

由上述定理可得推论：**在 $1,2,3,\dots,n-1,n$ 中一共有 $n-\lfloor\sqrt{n}\rfloor$ 个非完全平方数。**

综上所述，我们将二分的左边界定为 $1$，右边界定为 $2k$ 左右即可，接着跑二分，判定 $mid-\lfloor\sqrt{mid}\rfloor$ 与 $k$ 的大小关系，逐步缩小区间，最后区间只包含两个数时跳出，此时左边界为完全平方数，右边界即为最小化答案。

说句闲话，这个二分还挺坑（也有可能是我太菜了）。

![](https://cdn.luogu.com.cn/upload/image_hosting/980xjp5b.png)

```cpp
//改了改码风
#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>
using namespace std;
long long find(long long k)
{
    long long l = 1, r = k*2, mid, cnt;
    while (r - l > 1) //两端点重合会超时，只需枚举到两端点相邻即可
    {
        mid = (r + l) >> 1;
        cnt = mid - int(sqrtl(mid)); //非完全平方数的数量
        if (cnt < k) l = mid; //数量不够，n还要更大。
        else r = mid; //已经够了，尝试将n缩小。
    }
    return r;
}
long long t, k;
int main()
{
	cin>>t;
	while (t--)
    {
        cin >> k;
        cout << find(k) << endl;
    }
    return 0;
}
```

---

## 作者：Gongyujie123 (赞：2)

## [CF2020B Brightness Begins](https://www.luogu.com.cn/problem/CF2020B) 题解
### 1. 题意概括
有 $n$ 个灯泡，编号为 $1, 2, \ldots, n$。**最初，所有灯泡都亮着**。对于每个 $i = 1, 2, \ldots, n$，翻转所有 $i$ 的倍数的灯泡的状态。

找出最小的 $n$，使得完成 $n$ 次操作后仍有 $k$ 个灯泡亮着。

### 2. 思路分析
因为每次操作能翻转所有 $i$ 的倍数的灯泡的状态，所以，我们可以发现每个灯泡的最终状态取决于它的因数数量：**如果这个灯泡有奇数个因数，它的最终状态就是关闭；反之，如果有偶数个因数，它的最终状态就是开启**。

这样，我们的问题就变成了：**求第 $k$ 个非完全平方数**。

那我们该怎么找到第 $k$ 个非完全平方数呢？

首先，因为 $k \le 10^{18}$，所以枚举肯定会超时，但是我们可以用**二分答案**。

对于 $1 \sim n$ 中的非完全平方数的数量，我们可以用一条数学定理：**在 $1 \sim n$ 中，共有 $\sqrt{n}$ 个完全平方数**。

知道了这条定理，我们就可以得出：**在 $1 \sim n$ 中，共有 $n - \sqrt{n}$ 个非完全平方数**。

### 3. AC 代码
![AC 记录](https://cdn.luogu.com.cn/upload/image_hosting/8zlszwta.png)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int k;
		cin>>k;
		int l=1,r=2*k; //设置左右边界
		while(l+1<r){  //二分答案
			int m=(l+r)/2;
			if(m-(int)(sqrtl(m))>=k){ 
				r=m;
			}else{
				l=m;
			}
		}
		cout<<r<<endl;
	}
	return 0;
}
```

---

## 作者：_qumingnan_ (赞：2)

[题目跳楼机](https://www.luogu.com.cn/problem/CF2020B)

# 正文开始

## 阅读理解

房间内有一些灯，它们初始时是开着的。有 $N$ 次操作，第 $i$ 次操作会改变所有编号为 $i$ 的倍数的灯的状态（开变关，关变开）。

现在知道最后有 $K$ 盏灯亮着，求房间内最少有多少盏灯。

## 思路
我们发现，第 $i$ 次操作会改变所有编号为 $i$ 的倍数的灯的状态，也就是说，如果这个灯有奇数个因数，它就会关上；反之，如果有偶数个因数，他就会打开。那这道题就变成了第 $K$ 个非完全平方数是多少。

注意到 $K\le10^{18}$，暴力肯定是不可能的。那怎么办呢？想想我们知道的时间优化大师，不难想到，**二分答案**可以使用，那现在问题就在于怎么 $O(1)$ 求 $1\sim i$ 中有多少个完全平方数了。

我们可以用到数学中的一条定理:

**在 $1\sim n$ 中，有 $\lfloor\sqrt  n \rfloor$ 个完全平方数。**

那知道了这条定理，代码就很好写了。

## 代码实现
~~二分答案还有人不会写？！自己去写！~~
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int k;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>k;
		int l=0,r=2*k,mid;
		while(l<=r){
			mid=l+r>>1;//取中间值 
			int s=mid-sqrt(mid);//求有多少个非完全平方数 
			if(s>=k)r=mid-1;//已经够了 
			else l=mid+1;//还不够 
		}
		cout<<r<<'\n';
	}
	return 0;
}
```

---

## 作者：zhoujunchen (赞：1)

题意
--

$t$ 次询问，每次给你一个 $k$，让你求出一个 $n$，使得 $n- \lfloor \sqrt n\rfloor=k$。

思路
--

二分+数学。

- 完全平方数有奇数个因子。

所以 $1,2,3,\dots,n-1,n$ 中有 $n-\lfloor\sqrt n\rfloor$ 个非完全平方数。



我们可以直接二分答案。

code:


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int l=1,r=2e18;
		while(l+1<r){
			int mid=l+r>>1;
			int cnt=mid-(int)(sqrtl(mid));//sqrt 精度低 
			if(cnt<n)l=mid;
			else r=mid;
		}
		cout<<r<<"\n";
	}
	return 0;
}
```

[AC 记录。](https://codeforces.com/problemset/submission/2020/295340044)

---

## 作者：lw393 (赞：1)

赛时成功的吃了一车罚分，我太菜了……

题目要求第 $k$ 个有偶数个因子的数。通过数学知识，我们知道只有完全平方数有奇数个因子，且在 $x$ 以下的完全平方数有 $\lfloor\sqrt{x}\rfloor$ 个，于是就可以开始二分答案了。

（不知为什么，好像“math.h”头文件中的 sqrt() 函数有精度问题，我因为这个吃了罚分，所以只能手打二分求平方根了。

代码（含二分求平方根


```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define int long long

int sqrt(int x){
    if(x == 1) return 1;
    int l = 0, r = 1e9 + 5;
    while(l + 1 < r){
        int mid = (l + r) >> 1;
        if(mid * mid < x) l = mid;
        else if(mid * mid > x) r = mid;
        else return mid;
    }
    return l;
}

void solve(){
    int k;
    cin >> k;
    int l = 1, r = 2e18;
    while(l < r){
        int mid = (l + r) >> 1;
        if(mid - sqrt(mid) < k) l = mid + 1;
        else r = mid;
    }
    cout << r << '\n';
}

signed main(){
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
```

知道为什么精度出问题的可以评论区里说一下。

---

## 作者：wawatime1 (赞：1)

### 题目大意
寻找第 $k$ 个非完全平方数，也是第 $k$ 个有偶数个因子的数。
### 题目分析
完全平方数有奇数个因子，在 $n$ 以下的完全平方数有 $⌊\sqrt{n}⌋$ 个，直接二分答案即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, k;
long long calc(long long x) {
	long long l = 1, r = x * 2, cnt;
	while (l < r) {
		long long mid = (r + l) / 2;
		cnt = mid - int(sqrt(mid));
		if (cnt < x) 
			l = mid + 1;
		else 
			r = mid;
	}
	return r;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> k;
		cout << calc(k) << '\n';
	}
	return 0;
}
```

---

## 作者：yuxinrui0618 (赞：0)

# 题解：CF2020B Brightness Begins
## 1. 题目大意
- 求一个数 $n$，求 $1$ 到 $n$ 中有多少非完全平方数。

## 2. 思路
- 有一个数学公式：  
  $\text{在1到n中，必有 } ⌊\sqrt{n}⌋ \text{个完全平方数 } f(x) > 0 \text{。}$
  也就是说从 $1$ 到 $n$ 中，有不超过 $\sqrt{n}$ 个   完全平方数；
- 我们来证明一下这个数学公式：设 $k^{2} \le n$ 且 $(k+1)^{2} >n$，则 $1$ 到 $n$ 中的完全平方数为 $1^{2}$,$2^{2}$,$3^{2}$,⋯,$k^{2}$；因为 $k^{2} \le n$，所以 $k \le \sqrt{n}$，即 $k=⌊\sqrt{n}⌋$；
- 那么，就可得：$n=k+\sqrt{k}$；

## 3. 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while (t--)
    {
    	long long k;
    	cin>>k;
    	cout<<(long long)(sqrtl(k)+0.5)+k<<endl;
	}
    return 0;
}
```

## 4. 总结
谢谢观赏！  
若有不完善的地方还请各位大佬指出！

---

## 作者：mcturtle (赞：0)

[题目传送门](https://codeforces.com/problemset/problem/2020/B)
## 题目大意
给定你 $t$ 次询问，每次给你一个数 $k$，让你求出一个数 $n$，使得 $n-\left\lfloor\sqrt{n}\right\rfloor = k$。
## 解题思路
数学当中有这么一个定理：
> 在 $1,2,3,\ldots,n-1,n$ 中必有 $\left\lfloor\sqrt{n}\right\rfloor$ 个完全平方数。

怎么应用到这道题里呢？

因为一盏灯最后的状态是取决于它有多少个因数，所以说，若这盏灯最后是亮着的，那么它一定被按了偶数次，它拥有偶数个因子。

因此，这道题就是求第 $k$ 个**非完全平方数**。

把前面的定理带入即可，可得：
> 在 $1,2,3,\ldots,n-1,n$ 中必有 $n-\left\lfloor\sqrt{n}\right\rfloor$ 个非完全平方数。

## 代码

这里提供一个函数：`sqrtl()`，此函数用于长双精度型数据。因此，这将返回 `long double` 类型的平方根，比 `sqrt()` 精度更高。[引用此文章](https://blog.csdn.net/Piyriq0108/article/details/135315101)。

~~妈妈再也不用担心我爆精度啦!~~
```cpp
//仅提供部分代码
while(t--){
  long long n;
  cin>>n;
  long long ans=(sqrtl(n)+0.5);//高精函数+下取整
  ans+=n;
  cout<<ans<<endl;
}
```
~~完结撒花！~~

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

题目要求第 $k$ 个有偶数个因子的数。

众所周知，完全平方数有奇数个因子，且在 $x$ 以下的完全平方数有 $⌊\sqrt{x}⌋$ 个。

考虑二分答案。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
ll Sqrt ();
ll T, k;
ll Sqrt (ll x) {
    if(x == 1) return 1;
    ll l = 0, r = 1e9 + 5;
    while (l + 1 < r) {
        ll mid = (l + r) / 2;
        if (mid * mid < x) l = mid;
        else if (mid * mid > x) r = mid;
        else return mid;
    }
    return l;
}
void read () {
    cin >> k;
    ll l = 1, r = 2e18;
    while (l < r) {
        ll mid = (l + r) / 2;
        if (mid - Sqrt (mid) < k) l = mid + 1;
        else r = mid;
    }
    cout << r << endl;
}
int main () {
    cin >> T;
    while (T --) read ();
    return 0;
}
```

---

## 作者：furina_yyds (赞：0)

## 前置铺垫
要想使得这个灯还亮着，这个灯被按了偶数次，那么他的编号 $i$ 必然有**偶数个**因数。

那么，这个数必然为**非完全平方数**。

可以证明：将这个数小于 $\sqrt{i}$ 的所有因数 $x$ 和 $\frac{i}{x}$ 配成一对，故 $i$ 必有偶数个因数。由于不是完全平方数，所以 $x$ 和 $\frac{i}{x}$ 不可能相等。
## 解法
本题采用[二分答案](https://blog.csdn.net/m0_74099951/article/details/129348379)。

由于 $n - ⌊\sqrt{n} ⌋$ 满足单调性，故以这个数为 $mid$ 二分查找 $k$，从而枚举出 $n$ 就好了。

注：本篇不提供代码！

---

## 作者：for3to1 (赞：0)

赛时因为 $\mathrm{int}$ 和 $\mathrm{long\ long}$ 的问题卡在这题好久……

### Description

求第 $k$ 个有偶数个因子的数。

### Solution

数学+二分。

- 完全平方数有奇数个因子。

- 在比 $n$ 小的数中，完全平方数有 $\left \lfloor  \sqrt{n}\right \rfloor$ 个。

由此，我们知道：

- 在 $1,2,3,...,n-1,n$ 中，共有 $n-\left \lfloor  \sqrt{n}\right \rfloor$ 个非完全平方数。

由此即可二分答案。

### Code


```cpp
/*
Author:for3to1
Luogu uid:1028608
*/

#include <bits/stdc++.h>
using namespace std;
long long check(long long k){
    long long l=1,r=k*2,mid,cnt;
    while(r-l>1){
        mid=(r+l)>>1;
        cnt=mid-int(sqrt(mid));
        if(cnt<k) l=mid;
        else r=mid;
    }
    return r;
}
long long t,k;
int main(){
	cin>>t;
	while(t--){
        cin>>k;
        cout<<check(k)<<'\n';
    }
    return 0;
}
```

---

## 作者：jiangyunuo (赞：0)

### 题目大意：
十分简单，有 $n$ 个灯泡，一开始都是亮的，接下来，将会从 $1$ 到 $n$ 开始操作，第 $i$ 次操作，将会把编号为 $i$ 的倍数的灯泡状态反转，即亮的变暗，暗的变亮。  
现在给出操作完后亮的灯泡的数量 $k$，求 $n$ 的最小值。
### 大体思路：
非常简单，我们会发现，当灯泡的编号为平方数时，那么这个灯泡最终是暗的，反之，最终就是亮的。  
那么我们，可以在 $k$ 的基础上增加 $1 \sim k$ 中平方数的数量。
注意，加上这些平方数的数量时，可能又会包含其他平方数，因此，我们还要考虑新包含的平方数，如：$k=8$ 时，$k$ 加上 $2$（即 $1$ 和 $4$ 的数量）时，$9$ 又会被包含进来，因此还要再加 $1$。  
### 代码：
```cpp
#include<bits/stdc++.h>  
using namespace std;  
int main(){    
    int t;
    cin>>t;
    long long k;
    int a,b;
    for(int i=1;i<=t;i++){
        cin>>k;
        a=sqrt(k);
        k+=a;
        b=sqrt(k)-a;   //先加上原来 k 中包含的平方数数量。
        while(b){     //考虑新加入的平方数数量。
            k+=sqrt(k)-a;
            a=sqrt(k);
            b=sqrt(k)-a;
        }
        cout<<k<<endl;
    }
    return 0;  
}
```
注：考虑后来是否加入的平方数方法，如果 $k$ 中包含的平方数比原来多，则说明新加入了。

---

## 作者：RaymondOccam (赞：0)

### 题意简述
有编号为 $1, 2, \ldots, n$ 的 $n$ 个灯泡。起初，所有灯泡都亮着。操作灯泡意味着如果它之前是开着的话就关掉它，否则就打开它。

接下来，执行以下操作:

- 对于每个 $i = 1, 2, \ldots, n$ ，翻转所有灯泡 $j$ 的状态，使 $j$ 可被 $i$ 整除。

求最小的 $n$ ，以便在执行操作之后，正好有 $k$ 灯泡亮着。

### 思路
不难发现，$i$ 的最终状态取决于其因子的个数的奇偶性,而与 $n$ 无关。

如果为奇数个数则关闭，否则打开。

所以可以转化为：如果 $i$ 不是完全平方数，那么 $i$ 就会被打开。

定义存在一个 $x$ 使得 $y=x^2$，那么 $y$ 就是完全平方数，那么其就会拥有奇数个因子。因为如果在 $x$ 为质数的情况下，$y$ 的因子包括 $1,x,y$，有奇数个因子。如果 $x$ 为合数，那么 $y$ 的因子就会包括 $1,y,x$，以及 $x$ 的偶数个因子。

因为出现了一个 $k(k\ne 1,k\ne x)$ 为 $x$ 的因子，一定会存在一个 $\frac{x}{k}$，其为 $x$ 的因子。因此不管怎么分，$x$ 一定有偶数个因子，而 $1$ 又同时为 $x,y$ 的因子，那么 $y$ 的因子数量就为奇数。

所以问题就演化成了求第 $k$ 个为非完全平方数，可以保证最后操作剩下 $k$ 个开关，也就是说找到 $n$ 使得 $k+\sqrt{n}=n$。

使用二分实现，因此时间复杂度为 $O(t\times \log_2n)$。

### 代码
```cpp
#include <iostream>
#define ll long long
using namespace std;

ll t, k, l, r;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--)
    {
        cin >> k;

        l = 1, r = 2000000000000000000;
        while (r - l >= 2)
        {
            ll mid = (l + r) >> 1;
            ll res = mid - (ll)sqrt(mid);

            if (res >= k)
                r = mid;
            else
                l = mid;
        }

        cout << r << '\n';
    }
    return 0;
}
```

---

## 作者：DrAlfred (赞：0)

摘要：数学，二分

[传送门：https://www.luogu.com.cn/problem/CF2020B](https://www.luogu.com.cn/problem/CF2020B)

## 题意

有一排共 $n$ 盏灯，编号为 $1 \sim n$，一开始全是开着的。我们将会进行 $n$ 轮操作，对于第 $i$（$i = 1, 2, \dots, n$）轮操作，我们将所有编号为 $i$ 的倍数的灯翻转状态，即从开变成关或从关变成开。已知最后有 $k$ 盏灯仍然亮着，求满足条件的 $n$ 的最小值。

## 分析思路

考虑编号为 $i$ 的灯会被翻转 $\mathrm{d}(i)$ 次。如果 $x$ 号灯最后变为了关的状态，那就意味着 $\mathrm{d}(x)$ 为奇数。设 $x = p_1^{a_1} \times p_2^{a_2} \times \cdots \times p_k^{a_k}$。有 $\mathrm{d}(x) = \prod_{i = 1}^k (a_i + 1)$ 为奇数，那也就是说 $a_i$ 全部都是偶数，即 $x$ 为完全平方数。我们知道 $n$ 以内完全平方数的个数为 $\left\lfloor \sqrt n \right\rfloor$。所以有 $n - \left\lfloor \sqrt n \right\rfloor = k$。由于 $n - \left\lfloor \sqrt n \right\rfloor$ 单调不降，我们可以对 $n$ 进行二分。注意二分上界需要开大，因为 $k = 10^{18}$ 时有 $n = 10^{18} + 10^9$。时间复杂度 $O(\log k)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <class T>
inline T floor_sqrt(T x) {
    T res = std::sqrt(x);
    if (res * res > x) res--;
    return res;
}
inline void solve(void) {
    i64 k;
    cin >> k;
    i64 L = 0, R = LLONG_MAX, mid;
    while (L < R) {
        mid = (L + R) >> 1;
        if (mid - floor_sqrt(mid) < k) {
            L = mid + 1;
        } else {
            R = mid;
        }
    }
    cout << L << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    int t = 1;
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

