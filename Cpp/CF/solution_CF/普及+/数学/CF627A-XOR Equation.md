# XOR Equation

## 题目描述

两个合法的正整数 $a$ 和 $b$ 的和为 $s$，它们的按位异或和为 $x$。请计算出所有可能的有序数对 $(a,b)$ 的个数。

## 样例 #1

### 输入

```
9 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 2
```

### 输出

```
0
```

# 题解

## 作者：_stellar (赞：3)

不得不说和[dalao](https://www.luogu.org/space/show?uid=52356)探讨一番立刻就懂了..



------------
这道题是思路比较巧的位运算，总体思路是分类讨论,算法是简单枚举。

在切掉这道题前您得知道这几条性质（好像都知道吧qwq）:

+ $1$.$a$+$b$=($a$&$b$)*$2$+($a$^$b$)

【证明】：很好理解对吧，相当于把两个数的不同部分和相同部分的拆开，其中相同部分占了两份。

+ $2$.$a$&$1$用来判断一个数的所有位上1的个数

~~这道题就被您$1s$切掉了~~


------------

题目已知$a$+$b$和$a$^$b$，**我们不妨用$sum$表示$a$&$b$=($s$-$x$)/$2$.**
我们来看一下**a,b每一位上的**$a_i$和$b_i$。对于$ai$^$bi$和$a$^$b$各有两种情况，即$a_i$^$b_i$ $\in${0,1}，$a_i$&$b_i$ $\in${0,1}。

+ ### $Special$ $Judge$：不合法的$a$,$b$.
  + 1.$a$,$b$都为正整数,如果($s$-$x$)/$2$并不是整数直接$puts$($0$) 
  + 2.$s$<$x$的情况，不多赘述原因
  + 3.($a$^$b$)&($a$&$b$)！=0,显然如果不等于0肯定是不合法的，但是为什么会出现这种数据呢？
  
  
+ ### $Case$ $1$：$a_i$^$b_i$=$0$。
   + 易知$a_i$=$b_i$=$a_i$&$b_i$=$1$.这一位只有一种情况，直接被钦定了。此时我们发现如果**$a$完全等于$x$**或者**$b$完全等于$x$**，那么a,b都是$0$，是不符合的，$ans$要-=$2$.
+ ### $Case$ $2$: $a_i$^$b_i$=$1$。
   + 此时$a_i$&$b_i$=$0$，不符合的情况被踢进了$Special$ $Judge$的第三种情况了。所以我们可以大力枚举了。枚举每一位是否符合
$ai$^$bi$=$1$，即判断($x$&$1$)==$true$即可。而且由于是两种情况（$a_i$=$0$,$b_i$=$1$||$a_i$=$1$,$b_i$=$0$）,ans要*$2$.


------------


$AC$代码如下：
```
#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
ll s,x;
int main() {
    while (scanf("%lld%lld",&s,&x)==2) {
        ll sum=(s-x)/2;//sum=a&b
        if(x>s||sum*2+x!=s||(x&sum)!=0) {puts("0");continue;}
        ll cnt=0;
        while (x) {if (x&1)++cnt;x>>=1;}//枚举 
        ll ans=1LL<<cnt;if (!sum) ans-=2;//a==b==a&b
        printf("%lld\n",ans);
    }
    return 0;
}

```



------------

其实还有个小疑问：

为什么会出现($a$^$b$)&($a$&$b$)!=0的情况呢？

经过打表发现的数据好像都没有规律..望详解qwq

---

## 作者：Jayun (赞：2)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF627A)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14518315.html)

# 题目大意：

两个正整数 $b$ 和 $c$ 的和为 $s$，它们的按位异或和为 $x$。请计算出所有可能的有序数对 $(b,c)$ 的个数。

$2\leq x,s\leq10^{12}$。

# 正文：

因为 $b+c=2(b\land c)+(b\oplus c)$，所以有了 $s,x$ 我们可以算出两个数的与值 $a=\frac{s-x}{2}$。

如果不存在合法方案，就是上面的流程除了问题：

1. 如果 $s<x$，$a$ 肯定就是负数了，这种情况肯定不合法。
1. 如果 $2\nmid(s-x)$，$a$ 就不是整数，这种情况也不合法。
1. 如果 $a\land x\neq0$，两个数的与值的二进制的第 $i$ 位是两者二进制第 $i$ 位都等于 $1$ 是等于 $1$ 否则为 $0$。而异或值二进制第 $i$ 位在两者二进制第 $i$ 位都等于 $1$ 时肯定为 $0$，所以 $a\land x$ 肯定为 $0$。如果不为零，这种情况也不合法。

接下来如果 $x_i=1$，那么 $b_i,c_i$ 都有 $0,1$ 两种情况故答案乘二，否则只有 $b_i=c_i=1$ 的情况。另外如果 $a=0$，还需要特判 $b=c=0,c=b=0$ 的两种情况。

# 代码：

```cpp
ll s, x;
ll ans;

int main()
{
	scanf ("%lld%lld", &s, &x);
	ll a = (s - x) / 2, cnt = 0;
	if ((s - x) % 2 || (a & x) || x > s) {puts("0"); return 0;} 
	for (; x; cnt += x % 2, x >>= 1);
	ans = (1ll << cnt) - (a? 0: 2);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：wflhx2011 (赞：1)

# Solution

首先，我们看到题目给的是 $a+b$ 和 $a\operatorname{and}b$ 这两个后，熟悉位运算的就能想到 $a+b=2\times(a\operatorname{and}b)+(a\operatorname{xor}b)$。不难理解，相同部分有 $2$ 个，不同部分有  $1$ 个。

于是，我们用一个变量 $x$ 来表示 $a\operatorname{and}b$，即 $(a+b-(a\operatorname{xor}b))/2$。

现在，知道 $a\operatorname{and}b$ 和 $a\operatorname{xor}b$，我们就能对二进制每一位上进行讨论。但在此之前，我们先来思考：

### 什么时候无解

不难想到，因为 $a$ 和 $b$ 为正整数，所以 $x<0$ 或 $x$ 不为整数都无解。

除此之外，当 $(a\operatorname{xor}b)\operatorname{and}  (a\operatorname{and}b)\ne0$ 时也不行。

接下来，对二进制每一位进行讨论：

### 1. 异或为 $1$，即不相同

此时这一位上两个数 $\operatorname{and}=0$，否则就是无解。因为这是有序数对，即 $(a,b)$ 和 $(b,a)$ 是两对，所以这一位上的 $1$ 可以是 $a$ 的，也可以是 $b$ 的。所以我们看 $a\operatorname{xor}b$ 中有几个 $1$ ，答案就要 $\times$ 几个 $2$。

### 2. 异或为 $0$，即相同

此时换不换都一样，也就对答案没有贡献，但要注意如果 $a\operatorname{and}b$ 为 $0$，说明 $a$ 和 $b$ 都为 $0$，不合题意，所以答案总数要 $-2$。

最后，代码比较简洁：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long cnt,ans;
int main()
{	
	long long s,x;
	cin>>s>>x;
	long long k=(s-x)/2;
	if(x>s||(s-x)%2||(x&k)!=0)
	{
		cout<<0;
		return 0;
	}
	long long cnt=0;
	while(x)
	{
		if(x&1)
			cnt++;
		x>>=1;	
	}
	ans=1ll<<cnt;
	if(!k)
		ans-=2;
	cout<<ans;
	return 0;
}

```

---

## 作者：樱雪喵 (赞：1)

为什么题解都是奇怪的位运算性质，来一发无脑 dp。

## Description

给定 $s$ 和 $x$，求有序二元组 $(a,b)$ 的个数，满足 $a,b>0,a+b=s,a\oplus b=x$。

$s,x\le 10^{12}$。

## Solution

最低位没有加法进位产生的影响，考虑从低位向高位 dp。

设 $f_{i,0/1}$ 表示正在考虑第 $i$ 位，前 $i-1$ 位都满足限制，有无进位的方案数。

转移的时候枚举这一位两个数分别填 $a,b$，$x_i$ 表示 $x$ 在二进制下的第 $i$ 位，有
$$
f_{i,[a+b+j>1]}=\sum f_{i-1,j}[a\oplus b=x_i,(a+b+j)\bmod 2=s_i]
$$

特判一下 $s=x$，因为这样 $a,b$ 会有 $0$。

```cpp
#define int long long
const int N=105;
int f[N][2],s,x;
il int get(int x,int i) {return x>>i&1;}
signed main()
{
    s=read(),x=read();
    int n=__lg(max(x,s))+1;
    f[0][0]=1;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=1;j++)
            for(int a=0;a<2;a++)
                for(int b=0;b<2;b++)
                {
                    if((a^b)!=get(x,i)) continue;
                    if((a+b+j)%2!=get(s,i)) continue;
                    f[i+1][(a+b+j)/2]+=f[i][j];
                }
    if(s==x) f[n][0]-=2;
    printf("%lld\n",f[n][0]);
    return 0;
}
```

---

## 作者：Merge_all (赞：0)

# Solution
考虑无解的情况：

$$a + b = 2 \times (a \  \rm and \  b) + a \  \rm xor \  b$$
$$s = 2 \times (a \  \rm and \  b) + x$$
$$a \  \rm and \  b = \frac{s - x}{2}$$

1. 如果 $s - x$ 为奇数，肯定答案为 $0$。
2. 显然如果 $s < x$，答案为 $0$。
3. 已知 $a \  \rm xor \  b$ 和 $a \  \rm and \  b$ 以后，如果说相同二进制位上都是 $1$，说明无解。原因是 $a \  \rm xor \  b$ 中的 $1$ 表示满足答案的 $(a, b)$ 这一位二进制位是不同的，而 $a \  \rm and \  b$ 中的 $1$ 表示满足答案的 $(a, b)$ 这一位二进制位的数是相同且为 $1$，明显不可能有答案满足。

如果说有解的话，那么在 $a \  \rm xor \  b$ 中每一个 $1$ 的位置都可以让 $(a, b)$ 随意挑选 $0$ 和 $1$，因此根据乘法原理，答案为 $2 ^ {cnt}$，$cnt$ 是 $x$ 二进制中的 $1$ 的个数。

- 注意：如果 $s = x$，说明前面记录的答案中肯定包含了 $a = 0$ 和 $b = 0$ 这 $2$ 种情况（其实就是 $a \  \rm and \  b = 0$，那么 $a, b$ 有可能分到全 $0$ 的情况）。
## Code
```
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using Int = __int128;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
mt19937 rnd (time(nullptr));
ll s, x, ans = 1;
ll count (ll val) {
    ll cnt = 0;
    for (; val; val -= val & -val, cnt ++);
    return cnt;
}
int main (int argc, char *argv[]) {
    *cin.tie(nullptr) << fixed << setprecision (20);
    cout.tie(nullptr) -> ios_base::sync_with_stdio (false);
    
    cin >> s >> x;
	if ((s - x) % 2 || s < x || x & s - x >> 1) return cout << "0\n", 0;
	ans = 1ll << count (x);
    if (s == x) ans -= 2;
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：WuMin4 (赞：0)

## 思路

注意到 $a+b=(a\operatorname{xor}b)+2\times(a\operatorname{and}b)$，其中 $(a\operatorname{xor}b)$ 可以理解为不进位加法，$2\times(a\operatorname{and}b)$ 可以理解为加上进位的数。

于是将 $s$ 与 $x$ 带入得到 $2\times(a\operatorname{and}b)=s-x$，因为 $2\times(a\operatorname{and}b)$ 必定为一个非负整数，且为偶数，于是得到第一个无解条件：

- 当 $s-x$ 为负数或奇数时，不存在合法的数对。

当 $s-x$ 为偶数时，可以得到 $(a\operatorname{and}b)=\frac{s-x}{2}$，于是我们便知道了 $(a\operatorname{xor}b)$ 与 $(a\operatorname{and}b)$ 的值，下面对这两个数的二进制的每一位进行分类讨论：

1. $(a\operatorname{xor}b)$ 和 $(a\operatorname{and}b)$ 的第 $i$ 位均为 $0$。

此时根据 $(a\operatorname{xor}b)$ 可以知道 $a,b$ 的第 $i$ 位只能全为 $0$ 或全为 $1$，又因为 $(a\operatorname{and}b)$ 的第 $i$ 位为 $0$，所以 $a,b$ 的第 $i$ 位只能全为 $0$。

2. $(a\operatorname{xor}b)$ 的第 $i$ 位为 $0$，$(a\operatorname{and}b)$ 的第 $i$ 位为 $1$。

同理可得 $a,b$ 的第 $i$ 位均为 $1$。

3. $(a\operatorname{xor}b)$ 的第 $i$ 位为 $1$，$(a\operatorname{and}b)$ 的第 $i$ 位为 $0$。

此时 $a,b$ 的第 $i$ 位有两种选择（即 $(0,1)$ 或 $(1,0)$）。

4. $(a\operatorname{xor}b)$ 和 $(a\operatorname{and}b)$ 的第 $i$ 位均为 $1$。

当 $(a\operatorname{and}b)$ 的第 $i$ 位为 $1$ 时，$(a\operatorname{xor}b)$ 一定为 $0$，则此时无解。

因为 $a,b$ 均为正整数，则当 $s=x$（即 $(a\operatorname{and}b)=0$ 时），答案会包含 $a=0$ 与 $b=0$ 的情况，需要减去这两种情况。

## 总结

当 $s-x$ 为负数或奇数或 $(a\operatorname{xor}b)$ 和 $(a\operatorname{and}b)$ 二进制下第 $i$ 位均为 $1$ 时，不存在合法的数对。

当 $(a\operatorname{xor}b)$ 的第 $i$ 位为 $1$，$(a\operatorname{and}b)$ 的第 $i$ 位为 $0$ 时，答案需要乘 $2$。

当 $s=x$ 时，答案需要减 $2$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int s,x,ans=1;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>s>>x;
	if((s-x)&1ll||s-x<0)
		cout<<0;
	else{
		for(int i=63;i>=0;i--){
			if(!((((s-x)>>1ll)&(1ll<<i))!=0)&&(x&(1ll<<i)))
				ans*=2;
			if(((((s-x)>>1ll)&(1ll<<i))!=0)&&(x&(1ll<<i)))
				ans=0;
		}
		if(s==x) ans-=2;
		cout<<ans;
	}
	return 0; 
}
```

---

## 作者：lkjzyd20 (赞：0)

### 简要题意
给定两个正整数 $ a $ 和 $ b $，它们的和为 $ s $，按位异或和为 $ x $。需要计算满足条件的有序数对 $ (a, b) $ 的个数。

---

### 分析

   - $∵ a + b = 2(a \& b) + (a \oplus b) $，
   - $∴ a \& b = \frac{s - x}{2}$
     - 则 $ s - x $ 必须是非负的偶数（否则无法分解为 $ 2(a \& b) $）。
     - 则 $ a \& b = \frac{s - x}{2} \geq 0 $。
     - 则 $ x $ 和 $ a \& b $ 的二进制表示不能有重叠（即 $ (a \& b) \& x = 0 $）。
   - 为了保证 $ a $ 和 $ b $ 都是正整数，必须满足以下条件：
     - $ s + x $ 和 $ s - x $ 都是偶数。
     - $ a > 0 $ 且 $ b > 0 $。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
using namespace std;
int ss(int s, int x) {
    if ((s - x) < 0 || (s - x) % 2 != 0) return 0;
    long long a_and_b = (s - x) / 2;
    if ((a_and_b & x) != 0) return 0;
    long long ans = 1LL << __builtin_popcountll(x);
    if (a_and_b == 0) ans -= 2;
    return ans;
}
main()
{
    long long s, x;
    cin >> s >> x;
    cout << ss(s, x);
}
```

---

## 作者：him的自我修养 (赞：0)

~~洛谷的 rmj 炸了……~~

## 解法
题目给了两个数的和与异或和。那么我们就可以求出 $a \operatorname{and} b$ 的值。因为 $a+b=(a \operatorname{and}b )\times2+(a \operatorname{xor}b)$。所以就能求出啦。

接下来对异或在二进制下的每一位讨论：
1. 这位是 $1$，那么这一位可以分配给第一个数，也可以给第二个数，所以答案翻倍。

2.这位是 $0$，没有贡献，~~忽略掉它。~~

最后如果两数的按位与之和是 $0$，$a=b=0$，不符合题意，答案减去 $2$。

## 无解
**理论**上只有 $(a \operatorname{and}b )\operatorname{and}b \neq 0$ 的时候。但因为数据是乱给的，所以要判断异或和大于和以及两数的按位与的奇偶性。

## code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){	
	int a,b,cnt=0;
	cin>>a>>b;
	int c=(a-b)/2;
	if(b>a||(a-b)%2||(b&c)!=0){
		cout<<0;
		return 0;
	}
	while(b) cnt+=(b&1),b>>=1;
	int ans=1ll<<cnt;
	cout<<ans-(c==0?2:0);
	return 0;
}
```

---

