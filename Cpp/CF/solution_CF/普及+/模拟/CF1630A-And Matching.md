# And Matching

## 题目描述

You are given a set of $ n $ ( $ n $ is always a power of $ 2 $ ) elements containing all integers $ 0, 1, 2, \ldots, n-1 $ exactly once.

Find $ \frac{n}{2} $ pairs of elements such that:

- Each element in the set is in exactly one pair.
- The sum over all pairs of the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of its elements must be exactly equal to $ k $ . Formally, if $ a_i $ and $ b_i $ are the elements of the $ i $ -th pair, then the following must hold: $ $$$\sum_{i=1}^{n/2}{a_i \& b_i} = k, $ $  where  $ \\&amp; $  denotes the bitwise AND operation. </li></ul><p>If there are many solutions, print any of them, if there is no solution, print  $ -1$$$ instead.

## 说明/提示

In the first test, $ (0\&3)+(1\&2) = 0 $ .

In the second test, $ (0\&2)+(1\&3) = 1 $ .

In the third test, $ (0\&1)+(2\&3) = 2 $ .

In the fourth test, there is no solution.

## 样例 #1

### 输入

```
4
4 0
4 1
4 2
4 3```

### 输出

```
0 3
1 2
0 2
1 3
0 1
2 3
-1```

# 题解

## 作者：8atemak1r (赞：15)

## Description

$t$ 组数据，每组数据给定 $n$ 和 $k$（ $n$ 为 $2$ 的 $m$ 次幂，$m ∈ [1, 16]$ ），求一种将 $0,1,2,\dots,n-1$ 这 $n$ 个数分成 $\frac{n}{2}$ 对数字的分法，使得每对数字的位运算与（ `&` ）之和恰好等于 $k$。



## Solution

首先给出这道题中用到的十分重要的几个性质：

1. `i & (n - i - 1) = 0`

这个性质十分好证，将 $i$ 以及 $n - i - 1$ 的二进制写出来你就会发现他们的 $0$ 和 $1$ 是“插空站”的，或者反过来想，当你有这样的两个 $n$ 位二进制数，你将他们相加时每一位都会进位，最后得到的结果自然是 $2^n$，而且我们发现，$i$ 和 $n - i - 1$ 是关于 $\frac{n}{2}$ 对称的。

2. `(n - 1) & k = k`

这个性质也十分好证，易得 $n - 1$ 的二进制表示为连续的 $\log_{2}{n}$ 个 $1$， 它和任何数做位运算与自然是这个数本身了。

3. `0 & p = p`

证明略。

那如何将这个性质运用在这道题当中呢？

首先，当 $k < n - 1$，我们将 $k$ 与 $n - 1$ 配成一对，由性质 $2$ 得这一对数字对答案的贡献恰好为 $k$，再将 $n - k - 1$ 和 $0$ 配成一对，由性质 $3$ 得这一对数字对答案的贡献为 $0$。接下来，我们只需要使剩下的数对对答案的贡献均为 $0$ 就可以了，这不是有性质 $1$ 吗？枚举剩下的数字并输出相应的数对就可以了。

接下来是当 $k = n - 1$ 的情况。~~由样例得~~我们自己手推了一下发现，当 $n = 2$ 和 $n = 4$ 找不出合法的分法，接下来思考 $n > 4$ 的情况。我们可以把 $0$ 至 $n - 1$ 的二进制表示列出来，如下表：

[![HZYqs0.png](https://s4.ax1x.com/2022/02/04/HZYqs0.png)](https://imgtu.com/i/HZYqs0)

由性质 $2$ 结合表格可得，`(n - 1) & (n - 2) = n - 2` ，这时候还剩下一个最低位的 $0$ 要补上，正好，$n - 3$ 的最低位是 $1$，$1$ 只有最低位是 $1$， 于是易得 `(n - 3) & 1 = 1` ，这下把 $k$ 凑齐了，而根据性质 $1$ 中的“对称性”可得，我们需要把 $0$ 和 $2$ 凑成一对，剩下的数只需要由性质 $1$ 输出对应数对就好了。



## Code

```cpp
#include<iostream>
using namespace std;
int t, n, k;
int main() {
    cin >> t;
    while(t --) {
        cin >> n >> k;
        if(k == n - 1) {
            if(k <= 4) {
                cout << "-1\n";
                continue;
            }
            cout << 1 << ' ' << n - 3 << '\n';
            cout << n - 1 << ' ' << n - 2 << '\n';
            cout << "0 2\n";
            for(int i = 3; i < (n >> 1); ++ i) cout << i << ' ' << n - i - 1 << '\n';
            continue;
        }
        cout << k << ' ' << n - 1 << '\n';
        if(k != 0) cout << "0 " << n - k - 1 << '\n';
        for(int i = 1; i < (n >> 1); ++ i) {
            if(i == k || i == n - k - 1) continue;
            cout << i << ' ' << n - i - 1 << '\n';
        }
    }
    return 0;
}
```

---

## 作者：tongziyu (赞：2)

## Description
共 $T$ 组数据。

对于每组数据给定一个 $n$（$n$ 是 $2$ 的幂且 $4 \le n \le 2^{16}$）和一个 $k$ （$0 \le k \le n  - 1$），你需要在 $[0,n - 1]$ 中每次选出两个数 $a
_i$，$b_i$，共 $\frac{n}{2}$ 组。

求一种分组方式，使所有 $a_i,b_i$ $(1 \le i \le \frac{n}{2})$ 的按位与结果之和等于 $k$。

输出正确的分组方式，每组一行，两个数字用空格隔开。如果有多组答案，输出任意一种即可，如果不存在合法的分组方式，输出 $-1$。


------------

## Solution

考虑不合法的情况有哪些。

不合法就是所有组合所能取到的最大值仍然小于 $k$。

那么最大值怎么求？

最大的情况就是所有相邻的数配对，奇数和自己 $-1$ 之后的数配对。

这样配对每组得到的值是一个等差数列：$n - 2$，$n - 4$ … $2$，$0$。

相加的结果就是 $\frac{(n - 2)\cdot(\frac{n}{2})}{2}$。

只要 $k$ 大于这个值，就说明不合法。

~~（事实上在数据范围内只有 n = 4 且 k = 3 是不合法的）~~


------------


对于合法的情况如何组合？

首先由于 $n$ 是 $2$ 的幂，所以 $n - 1$ 的二进制表示一定是从末尾开始有若干个 $1$。也就是说，如果我们设和它配对的数为 $x$，那么这一组按位与的值就是 $x$。

这样的话，对于 $0 \le k \le n - 2$ 的情况，我们只需要将 $k$ 和 $n - 1$ 配一对（按位与结果是 $k$），$k$ 按位取反后的数与 $0$ 配一对（按位与结果是 $0$），其它的数都和自身取反配一对（按位与结果全部为 $0$）就可以达成目的。

那么当 $k = n - 1$ 的时候怎么做呢？

这时我们就可以先用 $n - 2$ 和 $n - 1$ 配一对（按位与结果是 $n - 2$）。再用 $n - 3$ 和 $1$ 配对（按位与结果是 $1$），最后将 $2$ 和 $0$ 配对（按位与结果是 $0$）。这样这三组的按位与之和正好是 $n - 1$。

其余的数与自身取反配对（按位与结果全部为 $0$）即可。


------------
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, t, k;
inline int read()
{
	register int r = 0, c = getchar(), f = 1;
	while (c < '0' || c > '9')
	{
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') r = (r << 3) + (r << 1) + (c ^ 48), c = getchar();
	return r * f;
}
int main()
{
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	t = read();
	while (t--)
	{
		n = read(), k = read();
		long long x = (n - 2) * (n >> 1) >> 1;
		if (k > x) 
		{
			puts("-1");
			continue;
		}
 		if (k < n - 1)
 		{
 			printf("%d %d\n", k, n - 1);
 			for (int i = n - 2; i >= n >> 1; --i)
 			{
 				if (i == k) printf("%d %d\n", n - k - 1, 0);
				else if (i == n - k - 1) printf("%d %d\n", 0, i);
				else printf("%d %d\n", i, n - i - 1); 
			}
		}
		else if (n >= 8)
		{
		 	printf("%d %d\n", n - 1, n - 2);
		 	printf("%d %d\n", n - 3, 1);
		 	printf("%d %d\n", 2, 0);
		 	for (int i = n - 4; i >= (n >> 1); --i) printf("%d %d\n", i, n - i - 1);
		}
	} 
	return 0;
}
```

---

## 作者：IvanZhang2009 (赞：1)

## 题意
将 0 到 $n-1$ 共 $n$ 个数分成 $\frac{n}{2}$ 组（ **$n$ 为 2 的整数次幂**），使每组各有两数且每组两数按位与的结果之和为 $k$。给出一种构造方案，无解 -1。
## 解法
先介绍按位与的几个性质：

1： $0\&k=0$；

2： $k\&(n-1-k)=0$ （$n$ 为 2 的整数次幂）；

3： $(n-1)\&k=k$ （$n$ 为 2 的整数次幂）；

可以考虑分类讨论：

1、当 $k=0$：

由性质 1，可将 $n$ 个数分成 $(0,n-1),(1,n-2),(2,n-3),\dots,(\frac{n}{2}-1,\frac{n}{2})$，这样每组按位与结果都是 0。

2、当 $0<k<n-1$：

考虑将 $k=0$ 的情况进行微调，使其中一组按位与得到 $k$，且保持其它所有组按位与结果为 0。

由性质 3，可以让 $k$ 和 $n-1$ 放在一组使按位与结果是 $k$。这时对于 $k=0$ 时情况的分组，相当于拆掉了 $(0,n-1),(k,n-k-1)$ 两组。让 $k$ 和 $n-1$ 放在一组，那么 0 和 $n-k-1$ 放在一起，按位与结果正好是 0（性质 1）。其他保持不变。

3、当 $k=n-1$：

插个题外话：听说很多大佬比赛的时候看到样例 $n=4,k=3$ 无解，就认为 $k=n-1$ 时都无解，于是这题挂了。

按照情况 2 的方法，让 $k$ 和 $n-1$ 放在一组，可当 $k=n-1$ 时无效。这时我们考虑将 $k$ 拆成 $k-1$ 和 1，$n-1$ 和 $n-2$ 放在一组得到 $k-1$，1 和一个奇数放在一起得到 $k-1$(也就是 $n-2$)。

依然借助情况 1 的分组方法，若 $n-1$ 和 $n-2$ 放在一组，1 和一个奇数放在一起，则拆掉了 $(0,n-1)$，$(1,n-2)$两组。选取一个奇数与 1 搭配，容易想到用 $n-3$ 来搭配，这时 0 与 2 搭配。所以最终结果就是：

$(0,2)$,$(1,n-3)$,$(n-1,n-2)$,$(3,n-4)$,$\dots$,$(\frac{n}{2}-1,\frac{n}{2})$。

## 代码
代码主要部分：
```cpp
	int n,k;
	cin>>n>>k;
	if(!k){
		REP(i,0,n/2)
		cout<<i<<' '<<n-1-i<<endl;
		return;
	}
	if(k&&k<n-1){
		cout<<0<<' '<<n-1-k<<endl;
		cout<<n-1<<' '<<k<<endl;
		REP(i,1,n/2)
		if(i!=k&&i!=n-1-k)cout<<i<<' '<<n-1-i<<endl;
	}
	if(k==n-1){
		if(n==4)cout<<-1<<endl;
		else{
			cout<<0<<' '<<2<<endl;
			cout<<n-1<<' '<<n-2<<endl;
			cout<<n-3<<' '<<1<<endl;
			REP(i,3,n/2)cout<<i<<' '<<n-1-i<<endl;
		}
	}
```

---

## 作者：Morgen_Kornblume (赞：1)

## 前言

**只要理论扎实，这个代码就能过！**

这种构造题不会怎么办？

打一个暴力，把所有可行解打出来，跟着暴力学啊。

然后注意找到一类可以在各种情况下通用的（一般的）构造方法。

## 本题构造方法

先发现一个性质，$ i \&(  (n-1)\oplus i ) == 0 $ 。

（$ \oplus $ 意为异或运算）

然后又知道 $\forall x \in [0,n-1]$ ，满足：$(n-1)\&x=x$

好，然后在后面用它。

分类讨论常用到。

### 1.k=n-1

首先选取 $ (n-2) \& (n-1) $ 为一组。

然后选取 $ 1 \& (n-3) $ 为一组。

由题意可知这两组的结果和加起来就等于 $k$ 了，所以剩余的组必须结果为 $0$。

然后运用性质，发现 $1$ 和 $(n-2)$ 这一组已经被占掉了，另外被占掉的是 $(n-1)$ 和 $(n-3)$。

与 $(n-1)$ 在“性质”中相对的是 $0$。

因为 $0 \&  $ $(\forall x \in Z)=0$。

所以将 $0$ 和与 $(n-3)$ 相对的 $2$ 作为一对。

可以发现剩下的成对异或为 $0$ 的对并没有被占用，输出它们即可。

由上面过程又可以得出：只有 $n=4$ 且 $k=3$ 的情况无解。

### 2.k<n-1
            
与上面的其实同理。
            
直接取 $k$ 与 $(n-1)$ 为一对，$0$ 和 $(n-1)\oplus k$ 为另一对。
            
可知这样做以后原来成对的仍然没有被占用，照样输出即可。
          
            
CF 提交代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int T;

int n,k; 

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	
	cin>>T;
	
	while(T--){
		
		cin>>n>>k;
		
		if(n==4&&k==3){
			cout<<-1<<endl;	
			continue;
		}
		
		if(k==n-1){
			cout<<n-1<<" "<<n-2<<endl;
			cout<<1<<" "<<n-3<<endl;
			cout<<0<<" "<<((n-3)^(n-1))<<endl;
			for(int i=3;i<n/2;i++){
				cout<<i<<" "<<((n-1)^i)<<endl;
			}
		}
		else{
			cout<<n-1<<" "<<k<<endl;
			if(k!=0)cout<<0<<" "<<((n-1)^k)<<endl;
			for(int i=1;i<n/2;i++){
				if(i==k||i==((n-1)^k))continue;
				cout<<i<<" "<<((n-1)^i)<<endl;
			}
		}
	}
	
	return 0;
}
```


---

## 作者：FiraCode (赞：0)

## 题解思路：
有一个很显然的性质：

$x\ n - x$ 的二进制每一位都是相反的。

所以我们可一构造出 $k=0$ 时的情况。

当$k \ne n-1$ 的时候：
>  我们就可以让 $k$ 和 $n - 1$ 组成一组。

>  再让 $n - k + 1$ 和 $0$ 构成一组

接下来就是 $k = n-1$ 的情况：

若 $k=n-1$，那我们就不能 $n - 1$ 和 $n - 1$，$0$ 和 $0$ 分成一组。

因为要 $n\ge 4$，即二进制至少有两位。

$(0)_{10} = (0)_{2}$，
$(1)_{10} = (1)_{2}$，
$(2)_{10} = (10)_{2}$，
$(3)_{10} = (11)_{2}$。

$(n - 4)_{10} = ((??????...-1)11)_{2}$、

$(n - 3)_{10} = (?????...00)_{2}$、

$(n - 2)_{10} = (?????...01)_{2}$、

$(n - 1)_{10} = (?????...10)_{2}$、

$(n)_{10} = (??????... 11)_{2}$。

>那么我们可以 $n - 2$ 和 $3$。

>$n - 4$ 和 $1$。

>$n - 1$ 和 $n - 3$。

>$2$ 和 $0$。

特殊情况 $n = 4 , k = 3$ 时构造不出来，输出 $-1$，其他情况都有解，把这种情况特判掉就可以了。

## AC CODE:
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1 << 20;
int a[N];
int main() {
    int T;
    scanf ("%d" , &T);
    while (T --) {
        int n , k;
        scanf ("%d%d" , &n , &k);
        if (n == 4 && k == 2)puts("-1");//无解情况
        else if (k == 0) {//k=0时
            for (int i = 0; i < n / 2; ++ i)
                printf ("%d %d\n" , i , n - 1 - i);
        }else if (k != n -1) {//k!=n-1时
            printf ("%d %d\n" , n - 1 , k);
            printf ("%d %d\n" , n - 1 - k , 0);
            for (int i = 1; i < n / 2; ++ i)
                if (i != k && i != n - 1 - k)
                    printf ("%d %d\n" , i , n - 1 - i);
        }else {//k=n-1的情况
            printf ("%d %d\n" , n - 2 , 3);
            printf ("%d %d\n" , n - 4 , 1);
            printf ("%d %d\n" , n - 1 , n - 3);
            printf ("%d %d\n" , 2 , 0);
            for (int i = 4; i < n / 2; ++ i)
                printf ("%d %d\n" , i , n - i - 1);
        }
    }
    return 0;
}
```

---

## 作者：PosVII (赞：0)

**前言**

------------

讲点不一样的做法。

本题使用异或。

**思路**

------------

先考虑 $n-1 \neq k$ 的情况，我们知道，$n-1$ 的二进制形式每一位都是一，那么我们可以使用 $k$ 与 $n-1$ 这一对来构造要求的 $k$，那么剩下的每一对的值必须为 $0$。不难发现，我们可以使其中每一对按位或的值都为 $n-1$，即构造形如 $(i,(n-1) \mathbin{\mathrm{xor}} i)$ 的对，这样还剩下 $0$ 和 $(n-1)\mathbin{\mathrm{xor}} k$ 没有组队，把它们放在一起即可。

再考虑 $n-1 = k$ 的情况，这时候刚刚的方法就不管用了，所以我们将其分为两部分得到：$((n-2),(n-1))$ 和 $(1,(n-3))$。这样我们又可以套用刚刚的方法了。

注意，很坑人的是，无解的情况有且只有 $n=4$ 且 $k=3$。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
template<typename G> inline void read(G &x) {x=0;G f=1;char ch=getchar();while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();if(ch=='-') f=-1,ch=getchar();while(ch>='0'&&ch<='9') {x=x*10+(ch^48);ch=getchar();}x*=f;}
const int MAXN=1e6+5;
int T,n,k,l,r;
bool f[MAXN];
int main() {
	read(T);
	while(T--) {
		memset(f,0,sizeof(f));
		read(n),read(k);
		if(n==4&&k==3) {
			puts("-1");
			continue;
		}
		if(k==n-1) {
			printf("%d %d\n",n-2,n-1);
			printf("%d %d\n",1,n-3);
			printf("%d %d\n",0,(n-3)^(n-1));
			f[n-2]=f[n-1]=f[1]=f[n-3]=f[0]=f[(n-3)^(n-1)]=1;
			for(int i=0;i<n;++i) {
				if(!f[i]) {
					f[i]=f[(n-1)^i]=1;
					printf("%d %d\n",i,(n-1)^i);
				}
			}
		}
		else {
			printf("%d %d\n",k,n-1);
			if(k!=0) printf("%d %d\n",0,(n-1)^k);
			f[k]=f[n-1]=f[0]=f[(n-1)^k]=1;
			for(int i=0;i<n;++i) {
				if(!f[i]) {
					f[i]=f[(n-1)^i]=1;
					printf("%d %d\n",i,(n-1)^i);
				}
			}
		}
	}
	return 0;
} 
```



---

## 作者：XL4453 (赞：0)

注意本题 $k$ 最多为 $n-1$，没看到这个卡了好久。

---
### 解题思路：

不妨当 $n$ 等于 $2^i$ 时能最大取到数的设为 $f_i$，易知 $f_1=0$。对于其它的有递推式 $f_i=2^{2n-3}+2f_{i-1}$。

可以发现，函数 $f_i$ 是一个增长极快的函数，在 $i=2$ 的时候就已经突破了 $n-1$，所以实际上需要的构造并不是要求结果很大的，直接用大的几个结合 $k$ 就行了。

---

由于 $n=2^i$，则 $n-1$ 在二进制下是形如 $111..111$ 
的。那么直接将 $n-1$ 和 $k$ 一组就直接得到了 $k$，然后就只要考虑如何剩下的若干数组合成几个和为 $0$ 的组合就行了。

注意到二进制下有这样一个性质，对于任意数 $x$ 和形如 $2^k-1$ 的数 $y$（其中 $k$ 足够大），$x \&(y- x)=0$。

再结合刚才构造，发现整个数列中的大多数都是存在于剩下的数中，也就是绝大多数都是可以用刚才的性质直接构造出来的。

特别的，有 $0$ 和 $n-k-1$这两个数不能直接用性质构造。随即发现直接将这两个数放一起就是一个合法的构造。

---
但是在刚才的构造中默认了 $k\ne n-1$，也就是绝大多数情况，那么直接给 $k=n-1$ 一个特殊额的构造即可。

不妨先将最大的两个数，即 $n-1$ 和 $n-2$，放在一起，直接得到 $n-2$。接下来用 $1$ 和 $3$ 放一组构造出 $1$，得到了  $n-1$，也就是 $k$。

剩下的数中不能直接用之前的 $x \&(y- x)=0$ 方法构造的数有：$0$ 和 $n-4$，直接用这两个数形成一组即可。

特殊地，当 $n=4$ 时，这一段的构造不可行。

---
另外注意特判 $k=0$。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
int T,n,k,book[10000005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=0;i<=n;i++)book[i]=0;
		if(n==4&&k==3){
			printf("-1\n");
			continue;
		}
		if(k==n-1){
			printf("%d %d\n",n-1,n-2);
			printf("%d %d\n",1,3);
			printf("%d %d\n",0,n-4);
			book[n-1]=book[n-2]=book[1]=book[3]=book[0]=book[n-4]=1;
			for(int i=1;i<n;i++){
				if(book[i]==0){
					printf("%d %d\n",i,n-1-i);
					book[n-1-i]=1;
				}
			}
			continue;
		}
		printf("%d %d\n",n-1,k);
		if(k!=0)printf("%d %d\n",0,n-1-k);
		book[n-1-k]=1;book[0]=1;book[k]=1;book[n-1]=1;
		for(int i=1;i<n;i++){
			if(book[i]==0){
				printf("%d %d\n",i,n-1-i);
				book[n-1-i]=1;
			}
		}
	}
	return 0;
}
```


---

## 作者：wzy2021 (赞：0)

## 思路分析

首先我们设 $c(i)$ 为在 $i$ 的二进制表示下，按位取反的结果，

例如：$c(50) = c((110010)_2) = (001101)_2 = 13$，

显然 $c(i) = (n - 1) - i$，

因为 $c(i)$ 是 $i$ 按位取反的结果，所以 $c(i) \& i = 0$ 

回到原题，我们分 $3$ 种情况：

1. $k = 0$，那我们将 $c(i)$ 与 $i$ 进行配对，总和为 $\sum_{i=0}^{n/2-1} c(i) \& i = 0$
2. $1 \le k \le n-2$，将 $c(i)$ 与 $i$ 进行配对，考虑把 $0,k,c(k),n-1$ 提取出来，将 $k$ 与 $n - 1$ 配，$k \& (n - 1) = k$，$0$ 与 $c(k)$ 配，$0 \& c(k) =0$，故总和为 $k$，
3. $k = n -1$，将 $c(i)$ 与 $i$ 进行配对，考虑把 $0, 1, 2, (n - 3),(n - 2),(n - 1)$ 提取出来，$(n - 1)$ 与 $(n - 2)$ 配对，$(n - 1) \& (n - 2) = (n - 2)$，$1$ 与 $(n - 3)$ 配对，由于 $(n - 3)$ 是奇数，所以 $1 \& (n - 3) = 1$，再将 $0$ 与 $2$ 配对，结果为 $0$，那么总和为 $(n - 2) + 1 + 0+\cdots+0=(n-1)$ 

注意：在第 $3$ 种情况中，要有至少 $6$ 个数才可以做，所以当 $n=4,k=3$ 时是无解的（样例有）。

这样我们就把题目做完了，复杂度 $O(n)$

## 代码环节

~~~cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = (1 << 20);
int a[maxn], b[maxn];

int c (int x, int n) {
	return (n - 1) - x;

int main() {
	int T; scanf ("%d", &T);
	while (T --) {
		int n, k; scanf ("%d%d", &n, &k);
		if (k == 0) {
			for (int i = 0; i < n / 2; ++i) {
				a[i + 1] = i; b[i + 1] = c(i, n);
			}
		} else if (k > 0 && k < n - 1) {
			a[1] = 0; b[1] = c(k, n);
			a[2] = k; b[2] = n - 1;
			int cnt = 2;
			for (int i = 1; i < n / 2; ++i) {
				if (i == c(k, n) || i == k) continue;
				a[++cnt] = i; b[cnt] = c(i, n);
			}
		} else {
			if (n == 4) {
				printf ("-1\n"); continue;
			}
			a[1] = 0; b[1] = 2;
			a[2] = 1; b[2] = n - 3;
			a[3] = n - 2; b[3] = n - 1;
			for (int i = 3; i < n / 2; ++i) {
				a[i + 1] = i; b[i + 1] = c(i, n);
			}
		}
		for (int i = 1; i <= n / 2; ++i) {
			printf ("%d %d\n", a[i], b[i]);
		}
	}
	return 0;
} 
~~~



---

## 作者：TianTian2008 (赞：0)

需要对位运算有一定理解。

注意到 $n$ 一定是 $2$ 的幂，因此 $n-1$ 在二进制下形式如 $111\cdots1$，于是有结论：对于 $a\in[0,n)$，与其“对称”的数 $n-1-a$，有 $a\operatorname{and}\ (n-1-a)=0$。

考虑一种构造思路：先把所有数与其“对称”的数配对（两者按位与的结果为 $0$，不会对结果产生影响），再构造出一对按位与结果为 $k$ 的数对。

发现按位与运算的单位元为 $n-1$，想到把 $k$ 和 $n-1$ 配对。同时，由于原本与两者配对的为 $n-1-k$ 和 $0$，有 $(n-1-k)\operatorname{and}0=0$，故把剩下的两者配对也不会对结果产生影响。

可是这种构造方法有缺陷，若 $k=n-1$，按上述构造方法，会把 $n-1$ 与自己配对，显然不合法。于是考虑另一种构造方法：先把所有数与其“对称”的数配对，再构造出两对按位与结果和为 $k$ 的数对，最简单的情况便是让两对数对按位与的结果为 $n-2$ 和 $1$。

可以把 $n-2$ 和单位元 $n-1$ 配对，原本配对的数 $1$ 和 $0$ 配对后不对结果产生影响，如此可以使结果变为 $n-2$。于是只需再构造一对按位与结果为 $1$ 的数对即可，注意到 $n-3$ 在二进制下形式如 $111\cdots101$，与 $3$ 配对后会使结果增加 $1$，而与两者“对称”的数 $2$ 和 $n-4$ 配对后也不对结果产生影响。如此即可使最终结果为 $n-1$。

注意到上述构造方法也有限制，即 $n-4>3$（否则会导致配对冲突的情况出现），所以有前提条件 $n>7$。换而言之，当且仅当 $n\leqslant7$ 时 $k=n-1$，会出现无解的情况，否则用上述方法便可构造出解。

到此，得出了此题的思路。

```
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
ll t,n,k;
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		if(k==n-1)
		{
			if(n<=7) puts("-1");
			else
			{
				puts("0 1");
				printf("%lld %lld\n",n-1,n-2);//(n-1) and (n-2)=n-2
				printf("%lld 3\n",n-3);//(n-3) and 3=1
				printf("%lld 2\n",n-4);
				for(ll i=4;i<(n>>1);++i) printf("%lld %lld\n",i,n-i-1);//把剩余数与“对称”的数配对 
			}
		}
		else if(!k)//k=0时直接把所有数与“对称”的数配对
		{
			for(ll i=0;i<(n>>1);++i) printf("%lld %lld\n",i,n-i-1);
		}
		else
		{
			printf("%lld %lld\n",k,n-1);
			printf("%lld 0\n",n-k-1);
			for(ll i=1;i<(n>>1);++i)
			{
				if(i==k||i==n-k-1) continue;//避免重复配对
				printf("%lld %lld\n",i,n-i-1);
			}
		}
	}
	return 0;
}
```

---

