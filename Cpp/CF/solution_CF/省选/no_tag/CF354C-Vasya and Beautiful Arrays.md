# Vasya and Beautiful Arrays

## 题目描述

Vasya's got a birthday coming up and his mom decided to give him an array of positive integers $ a $ of length $ n $ .

Vasya thinks that an array's beauty is the greatest common divisor of all its elements. His mom, of course, wants to give him as beautiful an array as possible (with largest possible beauty). Unfortunately, the shop has only one array $ a $ left. On the plus side, the seller said that he could decrease some numbers in the array (no more than by $ k $ for each number).

The seller can obtain array $ b $ from array $ a $ if the following conditions hold: $ b_{i}&gt;0; 0<=a_{i}-b_{i}<=k $ for all $ 1<=i<=n $ .

Help mom find the maximum possible beauty of the array she will give to Vasya (that seller can obtain).

## 说明/提示

In the first sample we can obtain the array:

 $ 3 6 9 12 12 15 $

In the second sample we can obtain the next array:

 $ 7 21 49 14 77 $

## 样例 #1

### 输入

```
6 1
3 6 10 12 13 16
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 3
8 21 52 15 77
```

### 输出

```
7
```

# 题解

## 作者：Wf_yjqd (赞：9)

上周模拟赛的题，被虐爆了。。

------------

首先考虑暴力的优化，可以构造一种情况。

由于最多可以减 $k$，如果都大于 $k+1$，一定可以把所有树都变成 $k+1$ 的倍数，所以答案最小为 $k+1$。

如果有小于等于 $k+1$ 的或其他情况都不可行，答案最大为 $\min(a_1,\ldots,a_n)$。

考虑如何优化判定一个答案是否可行的复杂度。

如果当前判断 $i$ 是否满足，只要 $\sum\limits_{j=1}^{n}[a_j\mod i\le k]$ 等于 $n$，即所有数都可以表示为 $i$ 的倍数加上一个小于等于 $k$ 的数，显然可行。

发现所有可行的数值 $a_j$ 都在 $\frac{\max(a_1,\ldots,a_n)}{i}$ 个长度为 $k$ 的区间内。

所有维护序列 $a$ 的桶数组的前缀和，枚举每个区间求和。

如果和等于 $n$，该答案成立。

根据调和级数，复杂度约为 $\operatorname{O}(n\log n)$（其实是$\operatorname{O}(n\ln n)$）。

------------
代码就挺短的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+84;
int n,k,cnt,a[maxn],s[maxn],minn=0x7f7f7f7f,maxx;
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        s[a[i]]++;
        maxx=max(maxx,a[i]);
        minn=min(minn,a[i]);
    }
    for(int i=1;i<=1e6;i++)
        s[i]+=s[i-1];
    for(int i=minn;i>=k+1;i--){
        cnt=0;
        for(int j=0;j*i<=maxx;j++)
            cnt+=s[min(maxx,j*i+k)]-s[j*i-1];
        if(cnt==n){
            printf("%d",i);
            return 0;
        }
    }
    printf("%d",minn);
    return 0;
}
```

又忍不住想写题解了。

---

## 作者：demon_yao (赞：4)

题单里说是$DP$想了半天硬是没想出来，可能是我太菜了，~~无耻的借鉴了题解~~发现了一样神奇的事情：暴力可过！
### 思路
- 由于它们的最大公约数只能在$0$到$min(a[i])$中出现，所以思路很简单：暴力枚举答案直到所有数都符合就可以啦qwq

- 考虑哪些答案一定是不符合的：对于每一个答案$ans$，我们枚举$a[i]$,记$tmp=ans%a[i]$,若$tmp<=k$,那么一定是可以改变$a[i]$使之符合的，用为对于此情景我们可以让$a[i]$减去$tmp$,而$tmp<=k$。若反之则不符合，我们只要让$ans-1$;直到所有都符合。

$code$炒鸡简单的qwq!!!

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e6+5;
int n,k,tmp=1e9+7,a[N];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) {a[i]=read();tmp=min(a[i],tmp);}
	bool f=1;
	while(f){
		f=0;
		for(int i=1;i<=n;i++)
			while(a[i]%tmp>k) tmp--,f=1;
	}
	cout<<tmp;
	return 0;
}

```



---

## 作者：lgswdn_SA (赞：2)

不懂题解区两位老哥的题解的复杂度怎么证。我这篇题解是cf的 official tutorial 的做法。

首先设 $m=\min a_i$。如果 $m<=k+1$ 那么很明显我们的答案为 $m$。于是接下来考虑 $m>k+1$ 的情况。

我们考虑枚举 $\gcd$。设其为 $g$。判断一个 $g$ 是否合法，需要满足所有 $a$ 都满足 $a_i\in [g,g+k]\cup[2g,2g+k]\cup...\cup [yg,yg+k]$ 中。我们枚举每一个 $[ig,ig+k]$，设 $cnt_i$ 表示 $[ig,ig+k]$ 中有多少个在 $a$ 中的数，那么上述条件等价于 $\sum_{i} cnt_i=n$。我们用前缀和能很方便地处理出 $c$ 并对它求和。

复杂度很好证明。复杂度为 $O(\sum i\times \frac{a}{i})=O(a\log a)$，用调和级数容易证明。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=2e6+9;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,k,m=0x3f3f3f3f,mx,a[N],c[N];

int main() {
	n=read(), k=read();
	rep(i,1,n) a[i]=read(), m=min(m,a[i]), mx=max(mx,a[i]);
	if(m<=k+1) {
		printf("%d\n",m);
		return 0;
	}
	rep(i,1,n) c[a[i]]++;
	rep(i,1,mx+k) c[i]+=c[i-1];
	per(g,m,k+1) {
		int cnt=0;
		for(int d=g;d<=mx;d+=g) cnt+=(c[d+k]-c[d-1]);
		if(cnt==n) {printf("%d\n",g); break;}
	}
	return 0;
}
```

---

## 作者：Rainbow_qwq (赞：2)

[CF354C Vasya and Beautiful Arrays](https://www.luogu.com.cn/problem/CF354C)

---

# 思路

看了以后，以为是道数论题，结果呢，就是暴力。

~~果然是~~$\text{Div.2.C}$

先取$res=\min \{ a[i] \}$，然后再用$res$去试除$a[i]$，如果$a[i]\ \text{mod}\ res>k$就将$res$减一，继续试除。

记录一个$f$表示是否需要下一轮试除。若有一次$a[i]\ \text{mod}\ res>k$那就$f=1$。

代码，注释在代码中：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int n,k,res=0x3f3f3f3f;
int a[300005];
signed main()
{
	n=read(),k=read();
	For(i,1,n){
		a[i]=read();
		res=min(res,a[i]);
	}
	bool f=1;
	while(f)
	{
		f=0;//是否需要下一轮试除
		For(i,1,n)
			while(a[i]%res>k)
				res--,f=1;//试除失败，res减一
      //如果f=0 res就是答案。
	}cout<<res;
    return 0;
}
```

---

## 作者：violin_wyl (赞：1)

## CodeForces354C



#### 解析：

###### 题目大意：

给你一个长度为 $n$ 的正整数数组 $a$, 你可以对于任意一个元素 $a[i]$ 减一个 $\leq k$的数，并保证 $a[i] \geq 0$

输出操作后所有数的最大公约数的最大值

###### 思路

我们考虑枚举最大公约数，并判断 $\forall a_i \in [v \times gcd, v \times gcd+k] (1 \leq i \leq n)$ ，也就是对于任意 $a_i (1 \leq i \leq n)$，他都可以通过减去一个小于 $k$ 的元素 $s$ 使  $gcd\vert a_i - s$，我们设 $sum(v\times gcd,v\times gcd+k)$ 表示闭区间 $[v\times gcd,v\times gcd+k] $内包括多少个 $a_i$，若 $\sum_{v=1}^{v\times gcd\leq n}[v\times gcd,v\times gcd+k]=n$，则直接输出当前 $gcd$。

但我们会发现一个问题，如果在枚举到 $gcd\leq k$ 时，$sum(v\times gcd,v\times gcd+k)$ 和 $sum((v+1)\times gcd,(v+1)\times gcd+k)$ 会有交集，有一些数会被重复计算，但是事实上 $gcd$ 最差情况也能取到 $k+1$ ~~这里请读者自证~~（其实也可以看面的式子）
$$
(v\times gcd\cdots v\times gcd+k)\cdots (v\times gcd + k + 1)\cdots
$$
则当 $a_i = v\times gcd+k$ 时 $a_i-k=v\times gcd$

----------------------------------------------------

## code

~~ps:跟楼下的差不多哦~~

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10, M = 2e6 + 10;
const int INF = INT_MAX;
const int mods = 1e9 + 7;
inline int read ()
{
    int x = 0, f = 1;
    char ch = getchar ();
    while (ch < '0'|| ch > '9') {if (ch == '-') f = -1; ch = getchar ();}
    while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar ( );}
    return x * f;
}
int a[N];
int cnt[M], mx, mn;
signed main()
{
    int n, k;
    n = read ( ), k = read ( );
    mn = INF;
    for (int i = 1; i <= n; i++) a[i] = read ( ), cnt[a[i]]++, mx = max (mx, a[i]), mn = min (mn, a[i]);
    if (mn <= k + 1) { printf("%d\n", mn); return 0; }//特判掉0
    for (int i = 1; i <= mx + k; i++) cnt[i] += cnt[i - 1];
    for (int v = mn; v > k; v--)
    {
        int sum = 0;
        for (int s = 1; s * v <= mx; s++) sum += (cnt[s * v + k] - cnt[s * v - 1]);
        if (sum == n) {printf ("%d\n", v); return 0;}
    }
    return 0;
}
```



---

## 作者：hzx360 (赞：0)

若 $g$ 为答案应满足：$n=\sum (ai \in [v\times g,v\times g+c]),v\in N^+,c \le k$。

先来看特殊情况：$k\ge a_{min}$。

很显然 $g=a_{min}$，因为 $g \in [1,a_{min}]$，答案最大为 $a_{min}$，而且由于: 
$$a_i\div a_{min}=v\cdots c$$

所以有：$v\ge1$ 且 $c< a_{min}\le k$，对每个 $a_i$ 减去一个对应的 $c$ 就行，所以肯定可以满足上述条件。


------------

对于 $k+1\le a_{min}$：

我们可以先枚举用桶记录前缀和，再枚举 $g$，对于每个 $g$ 又可以通过结合桶算出是否满足上面的条件。

易知：$g \in [1,a_{min}]$，每次枚举 $v$ 复杂度 $\Theta (\frac{a_{max}}{g} )$，所以复杂度是 $\Theta(n \ln n)$。

然而，上述成立的前提条件是你枚举的区间没有交集。

先分类：

1. $v\times g+g \ge v\times g+k+1$，即 $g\ge k+1$: 无交集可以放心枚举。

2. $1\le g\le k$：有交集，由：
	$$a_i\div g=v\cdots c$$

	这个式子可知， $g=k$ 时：$g=k \le a_{min}$，所以 $v\ge 1$ 且 $c\le k$。每个 $a_i$ 减去对应的 $c$ 后同样可以满足限制条件，所以这部分无需枚举，至少可以取到 $k$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+100;
int n,k,mi=10000000,mx=0,a[N],sum[N*10];
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[a[i]]++;
		mi=min(mi,a[i]),mx=max(mx,a[i]);
	}
	for(int i=1;i<=mx+k+2;i++) sum[i]+=sum[i-1];
	//g belongs to [1,mi]
	if(k+1<=mi){
		int ans=k;
		for(int g=mi;g>=k+1;g--){
			int res=0;
			for(int v=g;v<=mx;v+=g){
				res+=sum[v+k]-sum[v-1];
			}
			if(res==n){
				ans=g;
				break;
			}
		}
		cout<<ans;
	}
	else{
		cout<<mi<<endl;
	}
	return 0;
}

---

