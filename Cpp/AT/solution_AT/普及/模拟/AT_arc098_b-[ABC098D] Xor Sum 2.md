# [ABC098D] Xor Sum 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc098/tasks/arc098_b

長さ $ N $ の整数列 $ A $ があります。

次の条件を満たす整数 $ l $, $ r $ ( $ 1\ \leq\ l\ \leq\ r\ \leq\ N $ ) の組の個数を求めてください。

- $ A_l\ xor\ A_{l+1}\ xor\ ...\ xor\ A_r\ =\ A_l\ +\ A_{l+1}\ +\ ...\ +\ A_r $

xorの説明

整数 $ c_1,\ c_2,\ ...,\ c_m $ の $ xor $ は以下のように定義されます。

- $ xor $ の値を $ X $ とおく。$ X $ を $ 2 $ 進数表記したときの $ 2^k $ ( $ 0\ \leq\ k $, $ k $ は整数 ) の位の値は、$ c_1,\ c_2,\ ...c_m $ のうち、$ 2 $ 進数表記したときの $ 2^k $ の位の値が $ 1 $ となるものが奇数個ならば $ 1 $、偶数個ならば $ 0 $ となる。

例えば、$ 3 $ と $ 5 $ の $ xor $ の値は、$ 3 $ の $ 2 $ 進数表記が $ 011 $、$ 5 $ の $ 2 $ 進数表記が $ 101 $ のため、$ 2 $ 進数表記が $ 110 $ の $ 6 $ となります。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i $
- 入力はすべて整数である

### Sample Explanation 1

明らかに、$ (l,r)=(1,1),(2,2),(3,3),(4,4) $ は条件を満たします。 また、$ (l,r)=(1,2) $ の場合、$ A_1\ xor\ A_2\ =\ A_1\ +\ A_2\ =\ 7 $ となるので、これも条件を満たします。 ほかに条件を満たす組はないので、答えは $ 5 $ になります。

## 样例 #1

### 输入

```
4
2 5 4 6```

### 输出

```
5```

## 样例 #2

### 输入

```
9
0 0 0 0 0 0 0 0 0```

### 输出

```
45```

## 样例 #3

### 输入

```
19
885 8 1 128 83 32 256 206 639 16 4 128 689 32 8 64 885 969 1```

### 输出

```
37```

# 题解

## 作者：Cylete (赞：11)

感觉其他题解没讲清楚

我们考虑什么时候

$A[l] xor A[l + 1] xor … xor A[r] = A[l] + A[l + 1] + … + A[r] = s$

对于$s$二进制中每个位置的1，在$A[l]  A[l + 1]  …  A[r]$中只能出现一次

因为出现两次异或会变0，而加法会进位，此时就不相等了

再用尺取法就比较显然了

```cpp
const int N = 2e5 + 10;

int n, s1, s2, ans;
int a[N];

signed main()
{
	read(n);
	for(R int i = 1; i <= n; i++) read(a[i]);
	for(R int i = 1, j = 0; i <= n; i++)
	{
		while(j + 1 <= n && s1 + a[j + 1] == (s2 ^ a[j + 1])) j++, s1 += a[j], s2 ^= a[j];
		ans += j - i + 1;
		s1 -= a[i];
		s2 ^= a[i];
	}
	writeln(ans);
	return 0;
}
```

---

## 作者：耶耶小朋友 (赞：6)

## 题解 T3970([AtCoder - arc098_b]Xor Sum 2)

[vjudge链接](https://vjudge.net/problem/AtCoder-arc098_b)

### 方法：尺取法（双指针）+ 前缀和

一个前置芝士： $a$ ^ $a$ ^ $b$ =  $b$，$a$ ^ $a$ = $0$，$a$ ^ $b$ $≤$ $a$ + $b$。

这个知道就好。

首先定义两个数组记录前缀和，$suma$ 记录数组元素之和，$sumb$ 记录数组元素异或之和。

我们定义右端点 $j$ 从 $1$ 到 $n$ 中枚举，找到第一个符合条件的最小的左端点 $i$ ，更新答案就好了。

我们的最小左端点每次更新 $j$ 不用重新查找过只需沿用上次的 $i$ 即可。

为什么捏？

因为 $a$ ^ $b$ $≤$ $a$ + $b$ 此条性质，当之前的某对数满足 $a$ ^ $b$ $<$ $a$ + $b$，后面的数也无法弥补之前的小于的缺陷，只能抛弃之前的数了。

即 $i_{l} ≤ i_{k}(j_{l} ≤ j_{k})$。

该块具体代码：

``` cpp
//sumb[j] ^ sumb[i - 1]中^ sumb[i - 1]表示抵消之前的数
while((suma[j] - suma[i	- 1]) != (sumb[j] ^ sumb[i - 1])) {
	i++;
}
```

十年OI一场空，不开 $long\ long$ 见祖宗！

[AC记录](https://vjudge.net/solution/29563908)

## Code:

``` cpp
#include<bits/stdc++.h>
using namespace std;
//考虑unsigned long long
typedef long long ll;
inline ll read(){
	ll z=0,x=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') x=-x; c=getchar();}
	while(c>='0'&&c<='9') z=z*10+c-'0',c=getchar();
	return z*x;
}

const int N = 200010;
ll a[N];
ll suma[N],sumb[N];
int main () {
	std::ios::sync_with_stdio(false);
	ll n = read();
	for (int i = 1;i <= n;i++) {
		a[i] = read();
		suma[i] = suma[i - 1] + a[i];
		sumb[i] = sumb[i - 1] ^ a[i];
	} 
	ll i = 1;
	ll ans = 0;
	for (ll j = 1;j <= n;j++) {
		while((suma[j] - suma[i	- 1]) != (sumb[j] ^ sumb[i - 1])) {
			i++;
		}
		ans += j - i + 1;
	}
	cout << ans << endl;
	return 0;
}

```

$The\ end.$



---

## 作者：RainFestival (赞：5)

我们可以发现 $x \operatorname{xor} y\le x+y$

所以我们可以用尺取法

每次扫两个哨兵 $l,r$

$l$ 从 $1$ 到 $n$ 扫一遍

每次如果 $r+1$ 满足条件就 $r=r+1$

最后 $[l,x],x\in[l,r]$ 就是答案

所以 $ans=ans+(r-l+1)$

$O(n)$

代码 305B：

```cpp
#include<cstdio>
int n,f[200005];
long long ans=0;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&f[i]);
	int l=1,r=0,x=0,y=0;
	for (;l<=n;x=x^f[l],y=y-f[l],l++)
	{
		while ((x^f[r+1])==(y+f[r+1])&&r<n) ++r,x=x^f[r],y=y+f[r];
		ans=ans+(r-l+1);
	}
	printf("%lld\n",ans);
}
```

然后就AC了

QAQ

---

## 作者：yzy1 (赞：4)

作为一个不会双指针的蒟蒻，我们考虑用二分来做这道题。

由于异或运算相当于二进制不进位加法，所以对于两个正整数 $a,b$，一定有 $a\oplus b \le a+b$。同时由于异或满足交换律和结合律，我们可以用类似前缀和的方法预处理出「前缀异或」。

由于「异或运算相当于二进制不进位加法」，我们可以得出一个结论：如果
$$
\sum_{i=l}^ra_i=\bigoplus_{i=l}^ra_i(l<r),
$$
则一定满足
$$
\sum_{i=l}^{r-1}a_i=\bigoplus_{i=l}^{r-1}a_i.
$$
换句话说，如果区间 $[l,r]$ 满足条件，则区间 $[l,l],[l,l+1],\cdots,[l,r-1],[l,r]$ 均满足条件。即右端点是满足二分性质的。考虑枚举左端点 $i$，二分右端点 $j$，则对答案造成的贡献是 $j-i+1$，对于每个 $1\le i \le n$，将贡献累加即可得出答案。

时间复杂度 $O(n \log n)$，可以通过此题。

```cpp
inline bool Ck(int i, int mid) { return qzh[mid] - qzh[i - 1] == (qzxor[mid] ^ qzxor[i - 1]); }

signed main() {
  in(n)(a, n);
  re(i, n) qzh[i] = qzh[i - 1] + a[i], qzxor[i] = qzxor[i - 1] ^ a[i];
  re(i, n) {
    int l = i, r = n;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (Ck(i, mid))
        l = mid;
      else
        r = mid - 1;
    }
    int res = Ck(i, r) ? r : l;
    ans += res - i + 1;
  }
  out(ans)('\n');
  return 0;
}
```





---

## 作者：Light_snow (赞：1)

本文同步自：[[ARC098B] Xor Sum 2](https://i.cnblogs.com/posts/edit-done;postId=14994478)

关于异或运算和代数和运算有很不错的性质：

>$xor_{i = 1} ^ {n}a_i \leq \sum_{i = 1} ^ n a_i$

所以我们考虑一段区间按题目来说是合法的，即 $xor_{i = 1} ^ {n}a_i = \sum_{i = 1} ^ n a_i$ 是满足一段不符合，则整段不符合的性质的。
那么可以用 two-point。

```cpp
#include<iostream>
#include<cstdio>
#define ll long long 
#define N 200005

ll n;
ll a[N];
ll sum[N],xsum[N];//sum >= xsum

int main(){
	scanf("%lld",&n);
	for(int i = 1;i <= n;++i){
		scanf("%lld",&a[i]);
		sum[i] = sum[i - 1] + a[i];
		xsum[i] = xsum[i - 1] ^ a[i];
	}
	ll l = 0;
	ll ans = 0;
	for(int r = 1;r <= n;++r){
		while(l < r && (sum[r] - sum[l] != (xsum[r] ^ xsum[l])))
		l ++ ;
		ans += r - l;
	}
	std::cout<<ans<<std::endl;
}

```



---

## 作者：胡金梁 (赞：1)

在2021年AHOI的小学组中，此人用了个众人皆知的方法，结果他挂了。

以上是前言
****
好吧，其实2021年AHOI小学组第三题就是这道题，题面几乎没变，题目名称一点没变，对于一个什么都不会的蒟蒻来说，这道题的正解就是——暴力！俗话说，暴力出奇迹，打表过样例。但是此次暴力没出奇迹，只拿了十分，改进后只拿四十分。
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],sum[200005],xsum[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,s=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		xsum[i]=xsum[i-1]^a[i];
		if(!a[i])
		{
			s++;
		}
	}
	if(s==n)
	{
		cout<<n*(n+1)/2;
		return 0;
	}
	s=n;
	for(int l=2;l<=n;l++)
	{
		for(int i=1;i<=n-l+1;i++)
		{
			if((xsum[i+l-1]^xsum[i-1])==(sum[i+l-1]-sum[i-1]))
			{
				s++;
			}
		}
	}
	cout<<s;
}
```
虽然只能拿四十分，但是我用尽浑身解数也没能让它多加几分。这时候我突然意识到：暴力枚举时间复杂度是不可能降低的。这时，一位大佬提醒了我：可以用尺取法。

要想用尺取法，得先知道一个东西：前缀异或。前缀异或建立在这样一个基础上： $a⊕b⊕a=b$

既然这样，那么前缀异或的思路就出现了： $a_i⊕a_{i+1}⊕a_{i+2}⊕……⊕a_j=(a_1⊕a_2⊕a_3⊕……⊕a_j)⊕(a_1⊕a_2⊕a_3⊕……⊕a_i)$ 

我们定义右端点 $j$ 从 $1$ 到 $n$ 中枚举，找到第一个符合条件的最小的左端点 $i$ ，更新答案就好了。

我们的最小左端点每次更新 $j$ 不用重新查找过只需沿用上次的 $i$ 即可。

为什么？

因为 $a$ ^ $b≤a+b$ 此条性质，当之前的某对数满足 $a$ ^ $b<$ $a$ + $b$，后面的数也无法弥补之前的小于的缺陷，只能抛弃之前的数了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005],sum[200005],xsum[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,s=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
		xsum[i]=xsum[i-1]^a[i];
		if(!a[i])
		{
			s++;
		}
	}
	if(s==n)
	{
		cout<<n*(n+1)/2;
		return 0;
	}
	s=0;
	int i=1;
	for(int j=1;j<=n;j++)
	{
		while((xsum[j] xor xsum[i-1])!=(sum[j]-sum[i-1]))
		{
			i++;
		}
		s+=j-i+1;
	}
	cout<<s;
}
```


---

## 作者：冰糖鸽子 (赞：1)

**观前提示：本题解中，异或用 $\oplus$ 表示**

----

众所周知，异或具有以下两条性质：

- $a \oplus b \le a+b$

- $a\oplus b =a+b \ $ 成立，当且仅当 $a$ 与 $b$ 的二进制的加法中不会进位（也就是两数同一位置上最多只有 $1$ 个 $1$）

这是因为异或相当于不进位二进制加法，所以若相加时进了位，异或的结果就会缺失掉进的这一位，也就是小于相加的结果。

反之，若相加时一次也没有进位，异或的结果与相加的结果就会相等。

我们可以发现：若 $a+b+c= a \oplus b \oplus c$ ，则有 $a + b = a \oplus b$ 。因为去掉了 $c$ 之后原来就不进位的位置一定仍不进位。

考虑尺取法。取两个指针 $l$ ，$r$ ，枚举 $l$ 的同时移动 $r$ 至最远的能让 $[l,r]$ 满足条件的位置。 $l$ 移动时，由于以上性质，所以 $r$ 不需向后移动。

代码：

```cpp

// Problem: AT4142 Xor Sum 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT4142
// Memory Limit: 1000 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define M 200005
#define int long long
int n,a[M],r,l=1,ans,sum,SUM;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	while(l<=n)
	{
		while(r<n&&sum==SUM)
		{
			r++;
			sum^=a[r];SUM+=a[r];
			if(sum!=SUM)
			{
				sum^=a[r];SUM-=a[r];r--;break;
			}
		}
		if(r>n) break;
		// cout<<l<<' '<<r<<endl;
		sum^=a[l];SUM-=a[l];
		ans+=(r-l+1);
		l++;r=max(r,l-1);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Plozia (赞：1)

~~无耻的~~宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/111145890)

本题首先需要注意到几个性质：

1. $x \oplus y \leq x+y$ 。
2. $x \oplus y = z$ 等价于 $x \oplus z = y$ 。

搞清楚这两点，题目就好做了。

首先，对于满足要求的连续区间 $[l,r]$ ，如果加入数 $a_{r+1}$ 之后不平衡了，那么我们直接弹出 $a_l$ 即可，根据性质 2 以及众所周知的加减法逆运算更新即可。

因此根据上述描述，可以采用 **尺取法** 解决本题。

着重讲一讲更新答案：

假设两个指针为 $pos1,pos2$ ，答案为 $ans$ ,那么我们令 $ans += pos2 - pos1 + 1$ 。为什么只需要加入区间长度？是因为之前的数对我们已经在之前的区间中统计过了，因此这里不需要重新统计，只需要计算 $pos2$ 对区间 $[pos1,pos2-1]$ 的贡献即可。

Q：如果这么说，难道答案不是 $pos2-pos1$ 吗？为什么还要再加 1？
A：这是因为还有自己异或自己的答案。

```cpp
友善的作者在此贴心提醒您：
道路千万条，long long 第一条。
结果存 int ，爆零两行泪。
```

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
int n, a[MAXN];
typedef long long LL;
LL ans;

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	int pos1 = 1, pos2 = 0, s1 = 0, s2 = 0;
	while (pos1 <= n && pos2 <= n)
	{
		while(pos2 + 1 <= n && (s1 + a[pos2 + 1]) == (s2 ^ a[pos2 + 1])) {pos2++; s1 += a[pos2]; s2 ^= a[pos2];}
		ans += (LL)pos2 - pos1 + 1;
		s1 -= a[pos1]; s2 ^= a[pos1];
		pos1++;
	}
	printf ("%lld\n", ans);
	return 0;
}
```

---

## 作者：Leasier (赞：1)

其他题解似乎都是用的双指针维护从当前位置所能扩展到的最远位置。

事实上，也可以用二分答案来维护。

对于起始位置 $i$ 和当前二分结果 $mid$，若 $\operatorname{xorsum}_{mid} \operatorname{xor} \operatorname{xorsum}_{i - 1} = \operatorname{sum}_{mid} - \operatorname{sum}_{i - 1}$，最远位置显然就是 $mid$ 或在 $mid$ 右侧，此时 $mid + 1 \to l$，$mid \to x$；否则，$mid - 1 \to r$。二分结束后，所得 $x$ 即为最远位置下标，将答案加上 $x - i + 1$ 即可。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

int a[200007], xor_sum[200007];
ll sum[200007];

int main(){
	int n;
	ll ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		xor_sum[i] = xor_sum[i - 1] ^ a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++){
		int l = i, r = n, x = i;
		while (l <= r){
			int mid = (l + r) >> 1;
			if ((xor_sum[mid] ^ xor_sum[i - 1]) == sum[mid] - sum[i - 1]){
				l = mid + 1;
				x = mid;
			} else {
				r = mid - 1;
			}
		}
		ans += x - i + 1;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：windrizzle (赞：0)

一道较简单的题目。

### 题意
给你一些数字，求有多少区间的异或和等于区间的数字之和。

### 题解
如果直接枚举的话，时间复杂度略高。怎么办呢？可以用两指针，一个指针固定，一个指针滑动。而后，就可以找到最大满足条件的端点了。

代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=200020;
long long s,n,a[N],ans=0;
int main()
{
	cin>>n;
	//memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++) cin>>a[i];
	long long j=0;
	long long suma=0,sumb=0;
	for(int i=1;i<=n;i++)
	{
		while(j+1<=n&&sumb+a[j+1]==(suma^a[j+1]))//指针滑动
		{
			suma^=a[j+1];
			sumb+=a[j+1];
			j++;
		}
		ans+=j-i+1;
		suma^=a[i];
		sumb-=a[i];
	}
	cout<<ans;
	return 0;
}
```



---

