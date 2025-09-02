# 【MX-X5-T1】「GFOI Round 1」Inverted World

## 题目背景

原题链接：<https://oier.team/problems/X5B>。

---

> [Inverted World - ARForest](https://music.163.com/#/song?id=2099631232)

## 题目描述

给定一个长度为 $n$ 的正整数序列 $(a_1, \ldots, a_n)$，**保证该序列是等差数列**。  
（如果你不知道等差数列的定义，请参阅题目末尾处的提示。）

请求出该序列中满足如下条件的连续非空子串 $(a_l, \ldots, a_r)$（$1 \le l \le r \le n$）的数量：
- 该子串中的元素的平均值是整数。  
  （即 $(a_l + \cdots + a_r) \div (r - l + 1)$ 是整数。）

该序列可能很长，即 $n$ 可能很大，故不会给出该序列的每一项，而是只给出长度 $n$、首项 $k$ 和公差 $d$。**保证 $\bm{k, d}$ 都是正整数**。

## 说明/提示

**【样例解释】**

在第一组数据中，$a = [1, 3]$。共有 $3$ 个连续非空子串满足要求：

- $[1]$，其平均值为 $1$；
- $[3]$，其平均值为 $3$；
- $[1, 3]$，其平均值为 $2$。

在第二组数据中，$a = [2, 7, 12]$。共有 $4$ 个连续非空子串满足要求：

- $[2]$，其平均值为 $2$；
- $[7]$，其平均值为 $7$；
- $[12]$，其平均值为 $12$；
- $[2, 7, 12]$，其平均值为 $7$。

**【数据范围】**

| 测试点编号 | $n \le$ | $k \le$ | $d \le$ | 分值 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $10$ | $10$ | $10$ | $28$ |
| $2$ | $10^9$ | $10^9$ | $1$ | $35$ |
| $3$ | $10^9$ | $10^9$ | $10^9$ | $37$ |

对于所有数据，满足 $1 \le T \le 10^3$，$1 \le n, k, d \le 10^9$。

**【提示】**

长度为 $n$、首项为 $k$、公差为 $d$ 的等差数列定义为 $a_1 = k$ 且 $a_i = a_{i - 1} + d$（对每个 $2 \le i \le n$）。

## 样例 #1

### 输入

```
3
2 1 2
3 2 5
11451 41 91981```

### 输出

```
3
4
32787076```

# 题解

## 作者：Eason_cyx (赞：5)

借此题介绍一种打在线比赛快速过规律题的技巧。本题解没有严谨证明，想看证明请移步其他题解。

-----

首先写出暴力程序：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100005];
int main() {
	int t; cin >> t;
	while(t--) {
		int n,k,d; cin >> n >> k >> d;
		a[1] = k;
		for(int i = 2;i <= n;i++) a[i] = a[i-1] + d;
		ll num = 0;
		for(ll i = 1;i <= n;i++) {
			for(ll j = i;j <= n;j++) {
				ll sum = 0;
				for(int k = i;k <= j;k++) sum += a[k];
				if(sum % (j-i+1) == 0) num++;
			}
		}
		cout << num << endl;
	}
	return 0;
}
```

此时提交可以获得 $28$ 分的高分。

-----

看部分分：此时 $k=1$。

那么我们先将所有的 $k=1,2,3,\dots$ 和 $n=5,d=1$ 输入，容易发现 $k$ 的值和答案没有关系。

那么我们接着将 $n=1,2,3,4,\dots$ 和 $k=1,d=1$ 输入，得到如下式子：

$$1,2,4,6,9,12,\dots$$

如果你瞪眼能力强，那么应该可以看出答案了。但是，如果没看出来呢？我们可以使用一个在线查询数列的网站 [oeis.org](https://oeis.org/)，进入后在输入框输入 $1,2,4,6,9,12$，根据查询结果我们可以得到通项为 $ans = \frac{(n+1)^2}{4}$，于是我们就可以拿到这档部分分了。此时能拿到 $63$ 分。

-----

那么让我们将这种结论继续扩展：还是用之前的暴力程序，取 $n=6,k=1,d=1,2,3,4,\dots$ 进行求解。可以发现，令 $q \in \N$，当 $d=2q+1$ 时，答案相同；当 $d=2q$ 时，答案也相同。那么当 $d=2q+1$ 时，显然答案和上面 $d=1$ 时答案相同；于是我们取 $d=2,4,6,\dots$ 求解，这个数列很好瞪出来（看不出来，同理使用 `OEIS` 即可），通项公式即为 $ans=\frac{n(n+1)}{2}$。那么我们只需判断一下 $d$ 的奇偶性即可。至此，我们在本题获得了 $100$ 分。

时间复杂度 $\Theta(1)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int t; cin >> t;
	while(t--) {
		int n,k,d; cin >> n >> k >> d;
		cout << (d % 2 ? 1ll * (n+1) * (n+1) / 4 : 1ll * (n+1) * n / 2) << endl;
	}
	return 0;
}
```

---

## 作者：InfiniteRobin (赞：3)

## 分析

我们先来看一下式子：

设选取的等差数列的项数为 $n$，首项为 $x$，末项为 $y$，则该数列的平均数为：  
$$\large{\frac{n(x+y)}{2n} = \frac{x+y}{2}。}$$

若该式子的结果为整数，那就代表 $x+y$ 为偶数，我们又不难发现，若 $d$ 为偶数，则该等差数列中每一个连续的子序列都满足要求，那么易得答案为：

$$\large{n+ \frac{n(n-1)}{2}}。$$

那如果 $d$ 为奇数呢？我们不难发现，所选取的长度不为 $1$  的连续的子序列的长度必为奇数。

我们可以写出以下程序找一找规律。


```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n=15;
	
	while(n>=3){
		int ans=0;
		for(int j=1;j<=n;j++){
			for(int i=j+2;i<=n;i+=2){
				ans++;
			}	
		}
		cout<<"n="<<n<<" ans="<<ans<<"\n";
		n--;
	}
} 
```

所得到的结果如下：



|$n$|$3$|$4$|$5$|$6$|$7$|$8$|$9$|$10$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$ans$|$1$|$2$|$4$|$6$|$9$|$12$|$16$|$20$|

我们不难发现，若 $n$ 为奇数，所得到的的答案就是 $\Large{\lfloor{\frac{n}{2}} \rfloor}^{2}$。  

接下来，我们抽出 $n$ 为偶数的部分。列出相邻两个的增加量：

$$+4,+6,+8,+10 \cdots  。$$

没错！这部分构成了一个公差为 $2$ 的等差数列！
而且该数列的末项就是 $n-2$，且其项数为 $\Large{\frac{n-4}{2}}$。


那么，我们就可以得到一个有关增加量 $a$ 的式子：

$$\large{a=\frac{\frac{1}{2}(4+n-2)(n-4)}{2}}。$$

稍微整理得： 

$$a=\large{\frac{(n+2)(n-4)}{4}}。$$

那么答案就呼之欲出啦！

$$\large{ans=a+2}。$$

## 代码

最后别忘了加上长度为 $1$ 的子序列！

以下是本题的完整代码。


```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin>>t;
	
	while(t--){
		long long n,k,d,ans=n;
		cin>>n>>k>>d;
		
		if(d%2==0){
			ans=n*(n-1)/2;
			cout<<ans+n<<"\n";
		}
		else{
			if(n%2==0){
				ans=(2+n)*(n-4)/4+2; 
			}
			else{
				ans=(n/2)*(n/2);
			}
			cout<<ans+n<<"\n";
		}
	}
	return 0;
	
	
}
```

[评测记录。](https://www.luogu.com.cn/record/178966197)

---

## 作者：SkyLines (赞：3)

## Solution

由题可得，$a_n=k+(n-1) \times d$。

首先，当 $d$ 为偶数时，对于 $a_l$ 到 $a_r$ 的和为 $k \times (r-l+1) + \frac{(l + r - 2) \times (r - l + 1)}{2} \times d$（$1 \le l \le r \le n$），显然此时平均值为整数，平均值为 $k+(l+r-2) \times \frac{d}{2}$。所以此时直接输出 $\frac{n \times (n+1)}{2}$。

否则，$l+r-2$ 要为 $2$ 的倍数，即 $l+r$ 为 $2$ 的倍数。例如，$l=1$ 时，则 $r$ 为奇数，有 $\frac{n+1}{2}$（向下取整） 个 $r$，$l=2$ 时，则 $r$ 为偶数，有 $\frac{n}{2}$（向下取整）个 $r$。设 $A=\frac{n+1}{2}$（向下取整），$B=\frac{n}{2}$（向下取整），显然输出 $\frac{A \times (A+1)}{2} \times \frac{B \times (B+1)}{2}$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
int t, n, k, d, tmp1, tmp2;
signed main(){
	scanf("%lld", &t);
	for(int kk = 1; kk <= t; kk++){
		scanf("%lld %lld %lld", &n, &k, &d);
		if(!(d & 1)) printf("%lld\n", n * (n + 1) / 2);
		else{
			tmp1 = (n + 1) / 2;
			tmp2 = n / 2;
			printf("%lld\n", tmp1 * (tmp1 + 1) / 2 + tmp2 * (tmp2 + 1) / 2);
		}
	}
	return 0;
}
```

---

## 作者：xiaoke2021 (赞：2)

难度并不大，主要是等差数列相关知识。

---

其实结果和 $k$ 并没有关系。下面会有严格证明。

分类讨论。首先考虑公差为偶数。感性来想发现此时答案为等差数列的子段总数。但还是来严格证明一下。

设公差为 $2t$（$t$ 为正整数）。那么该数列为

$$k,k+2t,k+2 \times 2t,\dots,k+(n-1) \times 2t$$

总和为

$$
\begin{aligned}
  \sum_{i=0}^{n-1}(k+i \times 2t) &=nk + \sum_{i=0}^{n-1}i \times 2t\\
  &=nk+\frac{n(n-1)}{2} \times 2t
\end{aligned}
$$

提取 $n$，得

$$n \times (k+\frac{n-1}{2} \times 2t)=n \times [k+t(n-1)]$$

除以 $n$，得

$$k+t(n-1)$$

显然为整数，说明能被 $n$ 整除。所以，只要公差为偶数，不论首项或项数为多少，数列都符合要求。上面的结论就很好证明了。

这一步也就能看出公差为偶数的重要性。由于公差为偶数，所以可以与分母约分，保证结果为整数。这也进一步证明，一个数列是否符合要求，
与首项无关。

我们很轻松地解决了公差为偶数时的证明。那么若公差为奇数呢？

仍然可以用上面的公式，但此时公差为 $2t-1$。

那么总和变为：

$$n \times [k+\frac{n-1}{2} \times (2t-1)]$$

除以 $n$，得

$$k + \frac{n-1}{2} \times (2t-1)$$

如果想要它符合要求，就要保证其为整数，就要约掉分母 $2$。

公差为奇数，自然没法约分了。但如果 $n-1$ 为偶数，即项数 $n$ 为奇数，数列就符合要求了。

这也就得出结论：若公差为奇数，要使数列符合要求，那么项数为奇数。

进一步地，公差为奇数的数列的答案为此数列中 **项数为奇数** 的子串的数量。

有了结论就很好推式子了。我的代码把公差为奇数的部分写复杂了（用子串总数减去公差为偶数的子串数量），仅供参考。


```cpp
#include<bits/stdc++.h>
#define int long long //十年 OI 一场空，不开______见祖宗
using namespace std;
int T;
int n,k,d;
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>k>>d;
		if(d%2==0) cout<<n*(n+1)/2<<endl;
		else{ //这里最好分讨
			if(n%2==1) cout<<n*(n+1)/2-(2+(n-1))*((n-1-2)/2+1)/2<<endl;
			else cout<<n*(n+1)/2-(1+(n-1))*((n-1-1)/2+1)/2<<endl;
		}
	}return 0;
}
```

---

## 作者：cff_0102 (赞：2)

首先显然的我们可以忽略 $k$，它是多少不影响平均值是不是整数。

长度为 $n$ 的等差数列的平均值为它的和除以 $n$。设首项为 $0$（因为它不重要），则等差数列各项之和为 $\frac{(0+(n-1)d)\times n}{2}$，平均值为其再除以 $n$，也就是 $\frac{(n-1)d}{2}$。我们要求它是整数，即 $(n-1)d$ 是偶数。当 $d$ 是偶数则平均数必然是整数；当 $d$ 是奇数时则要求 $n$ 需要是奇数。

不难发现长度为 $n$ 的等差数列的子串包含 $1$ 个长度为 $n$ 的等差数列，$2$ 个长度为 $n-1$ 的等差数列，……，$n$ 个长度为 $1$ 的等差数列。

所以答案应该分类讨论：当 $d$ 是偶数，答案就是 $1+2+\dots+n=\frac{n(n+1)}{2}$，如果是奇数，则答案为 $n+(n-2)+\dots+(n\bmod2)$（即，$n$ 个长度为 $1$ 的序列，$n-2$ 个长度为 $3$ 的序列，……），这个等差数列的项数为 $\lfloor\frac{n+2}2\rfloor$，和即为 $\frac{(n+(n\bmod2))\times\lfloor\frac{n+2}2\rfloor}{2}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;while(t--){
		int n,k,d;cin>>n>>k>>d;
		if(d%2==0)cout<<n*(n+1)/2<<endl;
		else{
			cout<<(n+(n%2))*((n+2)/2)/2<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ycy1124 (赞：2)

### 题意
有 $T$ 个首项为 $d$，公差为 $k$，$n$ 项的等差数列，现在求这个等差数列有多少个连续的子段的平均数为整数。
### 思路
先按题意列出答案的式子：
$$
 ans = \sum_{l=1}^{n}\sum_{r=l}^n (r-l+1)\times((a_l+a_{l+1}\cdots+a_r) \bmod (r-l+1)=0)
$$
然后利用等差数列求和公式简化一下：
$$
 ans = \sum_{l=1}^{n}\sum_{r=l}^n (r-l+1)\times((a_l+a_r)\times(r-l+1)\div2 \bmod (r-l+1)=0)
$$
一个数乘上一个数再模上一个相同的数一定等于 $0$，于是又可以在简化一下式子：
$$
 ans = \sum_{l=1}^{n}\sum_{r=l}^n (r-l+1)\times((a_l+a_r) \bmod 2 = 0)
$$
把 $a_l,a_r$ 用 $n,k,d$ 表示出来：
$$
 ans = \sum_{l=1}^{n}\sum_{r=l}^n (r-l+1)\times((2\times d + (l+r-2)\times k) \bmod 2 = 0)
$$
对于这个式子，我们不难发现，$2\times d$ 模 $2$ 是一定等于 $0$ 的，所以不用考虑它，此时式子变成了：
$$
 ans = \sum_{l=1}^{n}\sum_{r=l}^n (r-l+1)\times(((l+r-2)\times k) \bmod 2 = 0)
$$

$k,n$ 的奇偶性已知，并且对最后的答案有影响，所以我们需要分类讨论一下。

首先如果 $k$ 模 $2$ 等于 $0$ 时，所有的 $l,r$ 肯定都满足，因此答案等于：
$$
\sum_{l=1}^{n}\sum_{r=l}^n (r-l+1)
$$
化简为：
$$
\dfrac{(n+1)\times n}{2}
$$

如果 $k$ 模 $2$ 不等于 $0$ 时，只有 $l+r-2$ 为偶数时答案增加，也就是 $r-l+1$ 为奇数时答案增加。$r-l+1$ 就是子段的长度，事实上答案就等于所有长度为奇数的子段个数。长度为 $len$ 的子段个数为 $n-len+1$，因此长度为 $1,3,5\cdots 2^m-1$ 的子段个数分别为 $n,n-2,n-4\cdots n-2^m+1$ （$2^m-1\le n$）。此时，答案的计算等于：
$$
\sum_{m}^{2^m-1\le n} n-2^m+1
$$
当 $n$ 为奇数时，答案可以简化为：
$$
\dfrac{(n+1)\times(n+1)}{4}
$$
否则，当 $n$ 为偶数时，答案可以简化为：
$$
\dfrac{(n+2)\times n}{4}
$$
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	scanf("%lld",&t);
	int n,k,d;
	long long ans=0;
	while(t){
		t--;
		scanf("%lld%lld%lld",&n,&d,&k);
		if(k%2==0){
			ans=(n+1)*n/2;
		}
		else if(n%2==1){
			ans=(1+n)*(n+1)/4;
		}
		else if(n%2==0){
			ans=(n+2)*n/4;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/178975774)。

---

## 作者：vectorxyz (赞：1)

一道思维好题。

#### 题目解析
发现题目让我们求平均数，因为是等差数列，我们直接套用等差数列求和公式，也就是 $(a_l + a_r) \times (r - l + 1) \div 2 \div (r - l + 1)$，可以发现 $(r - l + 1)$ 可以消去。由此，题目就转化为了求 $(a_l + a_r) \div 2$ 是整数的连续子序列个数。

我们再来研究一下 $(a_l+a_r) \div 2$，要使它是整数，那么就得让 $a_l+a_r$ 是偶数，通过小学数学可知，当 $a_l$ 和 $a_r$ 奇偶性相同的时候和才是偶数，又因为题目中是个等差数列，那么就很好处理了，分类讨论如下：

1. $k$ 和 $d$ 奇偶性不同。

不难发现这种情况每个数都是奇数，那么任意两个数都可以构成合法的序列，答案就是 $(1+n) \times n \div 2$。

2. $k$ 和 $d$ 奇偶性相同。
如果序列长度是奇数，那就有 $n \div 2 + 1$ 个奇数，$n \div 2 - 1$ 个偶数，计算贡献，累加即可。长度是偶数的情况同理。

还不明白可以自己模拟几个数据就明白了。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int T; cin >> T;
    while(T -- ){
        int n, k, d; cin >> n >> k >> d;
        if(k % 2 && d % 2 == 0 || k % 2 == 0 && d % 2 == 0){
            cout << (1 + n) * n / 2 << endl;
        }
        else {
            if(n % 2){
            int j = n / 2 + 1, o = n - (n / 2 + 1);
            cout << (1 + j) * j / 2 + (1 + o) * o / 2 << endl;}
            else {
                int j = n / 2;
                cout << (1 + j) * j << endl;
            }
        }
    }
    return 0;
}
```

---

## 作者：_H17_ (赞：1)

## 前言

赛时切掉黄题，没有挂分，比较爽，感觉题目比较好。

## 题目分析

考虑什么样的序列平均数是整数：$(a_l+a_{l+1}+\dots+a_r)\div(r-l+1)$ 是整数的就是。

考虑把式子用 $n,k,d$ 表示，$a_i=k+(i-1)\times d$。

然后我们用等差数列求和公式：$(first+last)\times element\div 2$ 带入这个式子。

得到 $\{[k+(l-1)\times d]+[k+(r-1)\times d]\}\times (r-l+1)\div 2\div (r-l+1)$。

化简得到 $(2\times k+(r+l-2)\times d)\div 2$。

当这个东西是整数的时候 $2\times k+(r+l-2)\times d$ 必然是偶数。

去除偶数的项最后得到 $(l+r)\times d$ 需要是偶数。

$d$ 是偶数：所有子串都是，共 $(n+1)\times n\div 2$ 个。

否则取 $l+r$ 是偶数的串都要。

此时分情况讨论 $n$ 是奇数还是偶数。

偶数：$(1+2+\dots+\frac{n}{2})\times 2=(n+2)\times n\div 4$。

奇数：$l$ 是奇数时向上取整，否则向下取整。这里把整合之后的答案放上来：$(2+\lfloor\frac{n}{2}\rfloor)\times(\lfloor\frac{n}{2}\rfloor)+1$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,k,d;
signed main(){
    for(cin>>T;T;--T){
        cin>>n>>k>>d;
        if(d&1){
            if(n&1)
                cout<<1+(2+n/2)*(n/2);
            else
                cout<<(2+n)*n/4;
        }
        else
            cout<<n*(n+1)/2;
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：dlzlj_2010 (赞：1)

首先，原数列是等差数列，因此可得 
$$\sum\limits_{i=l}^r a_i=\dfrac{(a_l+a_r)\times(r-l+1)}{2}$$
所以子串 $(a_l,\dots,a_r)$ 的平均值为 
$$\dfrac{\sum\limits_{i=l}^ra_i}{r-l+1}=\dfrac{a_l+a_r}{2}$$
那么问题就变为求等差数列中有多少对相加后为偶数的数对。

1. **当 $d$ 为偶数时**，由于公差为偶数，所以数列中任意一对数的奇偶性都相同，而任意一对奇偶性相同的数之和一定是偶数，因此共有 $n\times(n-1)$ 对符合条件的数对。
1. **当 $d$ 为奇数时**，对于任意整数 $i$，且 $1\le i\le n-2$，都有 $a_i+a_{i+2}$ 为偶数。

对于第二种情况，我们可以根据 $n$ 的奇偶性将 $a$ 分组。

1. **当 $n$ 为奇数时**，我们将 $a$ 分为 $(a_1,a_3,\dots,a_n)$ 和 $(a_2,a_4,\dots,a_{n-1})$ 两组，长度分别为 $\lceil\frac{n}{2}\rceil$ 和 $\lfloor\frac{n}{2}\rfloor$，此时两组中的数奇偶性均相同，我们记 $f(x)=x\times(x-1)$，那么两组就共有 $f(\lceil\frac{n}{2}\rceil)+f(\lfloor\frac{n}{2}\rfloor)$ 组数对满足条件。
2. **当 $n$ 为偶数时**，可以将 $a$ 分为 $(a_1,a_3,\dots,a_{n-1})$ 和 $(a_2,a_4,\dots,a_n)$ 两组，长度均为 $\frac{n}{2}$，同理可得共有 $2\times f(\frac{n}{2})$ 组数对满足条件。

最后将结果加 $n$ 即为答案 （因为只含一个值的子串的平均值也是整数）。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//#define int ll
typedef pair<int,int>pii;
typedef pair<pii,int>piii;
inline ll f(ll n){return n*(n-1)/2;}
signed main(){
	int T;
	cin>>T;
	while(T--){
		ll n,k,d;
		cin>>n>>k>>d;
		if(d%2==0)cout<<n+f(n);
		else{
			if(n&1)cout<<n+f(n/2+1)+f(n/2);
			else cout<<n+f(n/2)*2;
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：1)

若要满足 $\dfrac{a_l + \cdots + a_r}{ r - l + 1}=\dfrac{(a_l+a_r)(r - l + 1)}{ 2(r - l + 1)}=\dfrac{a_l+a_r}{2}=\dfrac{a_l+a_l+d(r-l)}{2}=a_l+\dfrac{d(r-l)}{2}$ 为整数，$(r-l)d$ 必须为偶数，即项数为奇数或者公差为偶数。

因此，如果公差为偶数，则所有子串都满足条件，答案为 $n+(n-1)+(n-2)+\cdots+1=\dfrac{n(n+1)}2$。

若公差为奇数，则所有项数为偶数的子串满足条件。这时要以 $n$ 的奇偶性分两种情况。若 $n$ 为偶数，则答案为 $n+(n-2)+\cdots+2=\dfrac{\frac{n}{2}(n+2)}{2}=\dfrac{n(n+2)}{4}$；若 $n$ 为奇数，则答案为 $(n-1)+(n-3)+\cdots+2=\dfrac{(n+1)(\left\lfloor\dfrac{n}{2}\right\rfloor+1)}2$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		long long n,k,d;cin>>n>>k>>d;
		if(d%2==0) cout<<n*(n+1)/2;
		else{
			if(n%2==0) cout<<(n+2)*n/4;
			else cout<<(n+1)*(n/2+1)/2;
		}
		cout<<"\n";
	}
	return 0;
}
/*
(k-1)d
*/
```

---

## 作者：cly312 (赞：0)

题目要求：$(a_l + \cdots + a_r) \div (r - l + 1)$ 是整数。

即 $\frac{(a_l + a_r)\cdot(r-l+1)\div 2}{r-l+1}$ 为整数。

即 $\frac{(a_l + a_r)}{2}$ 为整数。

即 $a_l+a_r$ 为偶数。

即 $m+(l-1)\cdot d + m+(r-1)\cdot d$ 为偶数。

即 $2m+(l+r-2)\cdot d$ 为偶数。

即 $2m+(l+r)\cdot d -2d$ 为偶数。

因为 $2m,-2d$ 为偶数，所以也就是 $(l+r)\cdot d$ 为偶数。

- 当 $d$ 为偶数时：所有的区间都可以，答案为 $\frac{n\cdot (n+1)}{2}$。
- 当 $d$ 为奇数时：要求 $l+r$ 为偶数，即 $2\cdot l+r-l$ 为偶数，即 $r-l$ 为偶数，也就是这个区间的长度为奇数。

  - 当 $n$ 为偶数时：答案为 $n+(n-2)+\dots 2  =(\frac{n}{2}+1)\cdot \frac{n}{2}$。
  - 当 $n$ 为奇数时：答案为 $n+(n-2)+\dots 1  =\frac{(n+1)\cdot (\frac{n}{2}+1)}{2}$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n,k,d;
	cin>>n>>k>>d;
	if(d&1){
		if(n%2==0) 
			cout<<(n/2+1)*(n/2)<<'\n';
		else cout<<(n+1)*(n/2+1)/2<<'\n';
	}else{
		cout<<(n)*(n+1)/2<<endl;
	}
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}

```

---

## 作者：gh_AC (赞：0)

## 思路：

这道题我们能发现当 $d$ 是偶数时，等差数列中的数不是全都是奇数就全都是偶数。

当数列中的数不是全都是奇数就全都是偶数时，我们任意选两个位置的数取中间的平均值就一定是整数，那总共的方案数就是在 $n$ 个数中选两个数的方案数。

当 $d$ 是奇数时，等差数列中的数就是奇偶数交叉排列，那总共的方案数就会是所有奇数中选两个的方案数加所有偶数中选两个的方案数。

## 代码：


```cpp
#include<iostream>
using namespace std;
int t;
long long n,k,d;
long long ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k>>d;
		ans=n;
		if(d%2==0) ans+=n*(n-1)/2;
		else{
			if(n%2==0) ans+=(n/2)*(n/2-1);
			else{
				ans+=(n/2)*(n/2-1)/2;
				ans+=(n/2+1)*(n/2)/2;
			}	
		}
		cout<<ans<<endl;
	}
} 
```

---

## 作者：xixisuper (赞：0)

# P11129 【MX-X5-T1】「GFOI Round 1」Inverted World 题解

一道数学题，只需要知道等差数列的求和式就能做。

## 思路

转述一下题意：

- 给定一个长度为 $n$ 的等差数列 $a$，询问有多少个区间 $[l,r](l\le r)$ 满足：

$$
\frac{\sum_{i=l}^ra_i}{r-l+1}\in \Z
$$

实际上 $r-l+1$ 就是区间 $[l,r]$ 的长度，我们不妨记其为 $len$，然后注意到分子上是等差数列的一段进行求和，实际上这一段也是等差数列，于是我们心中默念等差数列的求和公式，并把其代入上述公式中：

$$
\begin{aligned}
\frac{\sum_{i=l}^ra_i}{r-l+1}&=\frac{(a_l+a_r)\times len}{2len}\\
&=\frac{a_l+a_r}{2}\\
&=\frac{2a_l+(r-l)\cdot d}{2}\\
&=a_l+\frac{(r-l)d}{2}
\end{aligned}
$$

这里的 $d$ 是原等差数列的公差，所以实际上我们只需要限定 $\frac{(r-l)d}{2}$ 是个整数即可，我们分情况讨论。

### $d$ 是偶数

那么显然 $\frac{(r-l)d}{2}$ 为一个正整数，所以任意区间都满足条件，直接输出区间个数即可。

如果有人不会求区间个数的话，我提一嘴，我们发现长度为 $1$ 的区间共有 $n$ 个，长度为 $2$ 的区间共有 $n-1$ 个，长度为 $i$ 的区间共有 $n-i$ 个，于是一共有：

$$
n+(n-1)+(n-2)+\cdots+2+1=\frac{n(n+1)}{2}
$$

个区间。

### $d$ 是奇数

这是我们需要限定 $(r-l)$ 是一个偶数，也就是 $len$ 是一个奇数，换句话说就是这个数列中所有长度为奇数的区间个数，这个数怎么算呢？我们依然分情况讨论一下。

- 如果 $n$ 是奇数，那么满足条件的区间长度应该是 $n,n-2,n-4,\cdots,3,1$，相对应的，在该区间长度下的区间个数分别是 $1,3,5,\cdots,n-2,n$，是一个以 $1$ 为首项，公差是 $2$，末项是 $n$ 的等差数列求和，很容易能计算出这个式子的和为 $\frac{(n+1)^2}{4}$。
- 如果 $n$ 是偶数，那么满足条件的区间长度应该是 $n-1,n-3,n-5,\cdots,4,2$，相对应的，在该区间长度下的区间个数分别是 $2,4,6,\cdots,n-3,n-1$，是一个以 $2$ 为首项，公差是 $2$，末项是 $n-1$ 的等差数列求和，很容易能计算出这个式子的和为 $\frac{(n+2)n}{4}$。

综上所述，我们只需要根据 $d$ 与 $n$ 的奇偶性分类讨论即可，时间复杂度 $O(T)$。

## 代码

当时怕 `long long` 存不下，于是开了 `__int128`。

```cpp
#include <iostream>
#include <vector>
#define ll __int128
using namespace std;
const ll N=1e6+10;
inline ll read(){
	register long long x=0,f=1;
	register char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
ll T,n,k,d;
int main(){
	T=read();
	while(T--){
		n=read();k=read();d=read();
		ll ans;
		if(!(d&1)) ans=(n+1)*n/2;
		else{
			if(n&1)	ans=(n+1)*(n+1)/4;
			else ans=(n+2)*n/4;
		}
		long long outt=ans;
		cout<<outt<<"\n";
	}
	return 0;
}
```

---

## 作者：zhoumurui (赞：0)

### 题面展示

给定正整数 $n,k,d$，求长度为 $n$，首项为 $k$，公差为 $d$ 的等差序列 $(a_1, \ldots, a_n)$ 中，满足如下条件的连续非空子串 $(a_l, \ldots, a_r)$（$1 \le l \le r \le n$）的数量：
- 该子串中的元素的平均值是整数。  
  （即 $(a_l + \cdots + a_r) \div (r - l + 1)$ 是整数。）

$n$，$k$，$d$ 都是正整数。

### 解题思路

本题是一个结论题。

考虑子串 $(a_l, \ldots, a_r)$，它显然是一个等差数列，它的所有项的和为 $ \frac{(a_l + a_r )  (r-l+1)}{2}$。

它是 $(r-l+1)$ 的倍数自然等价于 $a_l+a_r$ 是偶数。

只需要统计数列中有几个奇数、几个偶数，就可以完成此题。

- $d$ 是偶数：所有项的奇偶性一致，$a_l+a_r$ 必是偶数，答案为 $\frac{n(n+1)}{2}$。

- $d$ 是奇数：$a_l+a_r$ 为偶数等价于 $l+r$ 是偶数。

  我们观察当 $n=7$ 的情况，不难得出 $l$ 的取值对应 $r$ 的方案数的表格：

  

  |$l$ 的取值|$1$|$2$|$3$|$4$|$5$|$6$|$7$|
  |:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
  |$r$ 的方案数|$4$|$3$|$2$|$1$|$2$|$3$|$4$|

  我们立即总结出了规律，$r$ 的方案数成一个先递减再递增的构型，根据等差数列公式，$r$ 的方案数的求和公式自然也能得出：

  $$\frac{\frac{n+1}{2} \times \frac{n+3}{2}}{2}+\frac{\frac{n}{2}\times \frac{n+2}{2}}{2}$$





### 核心代码展示

要开 long long。
```cpp
cin>>t;
while (t--){
    cin>>n>>k>>d;
    int ans;
    if (d&1)ans=((n+1)/2)*((n+3)/2)/2+(n/2)*((n+2)/2)/2;
    else ans=n*(n+1)/2;
    cout<<ans<<"\n";
}
```

---

## 作者：Your_Name (赞：0)

## 题意
用 $n,k,d$ 描述一个等差数列，为有多少个连续子段的平均数为整数。
## 思路
手玩样例发现：
* 答案要么是长度为奇数的子串的个数要么是所有子串的个数。
* 当 $a_1$ 与 $a_2$ 的平均数为整数则所有子串都满足条件。

正确性显然。

求长度为奇数的子串个数也很显然。
找规律发现：
* 长度为 $1$ 的子串个数为 $n$。
* 长度为 $1$ 的子串个数为 $n$。
* 长度为 $1$ 的子串个数为 $n$。

加一下可以得出：长度为奇数的子串个数为 $(g \div 2 + 1) \times n - (2 + g) \times (g \div 2) \div 2$（$g$ 为最大的，不大于 $n$ 的偶数）。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t, n, k, d, g, ans, j, o;
int main(){
    cin >> t;
    while(t --){
        cin >> n >> k >> d;
        if(n % 2 == 1){
            g = n - 1;
        }else{
            g = n;
        }
        j = 1ll * (g / 2 + 1) * n - 1ll * ((2 + g) * (g / 2)) / 2ll;
        o = 1ll * n * (n - 1) / 2 + 1ll * n;
        if((k + k + d) % 2 == 1){
            ans = j;
        }else{
            ans = o;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：NingMeng_yang (赞：0)

# [题目传送](https://www.luogu.com.cn/problem/P11129)

题意为在长度为 $ n $ 的正整数等差序列中 ，求出子串中的元素的平均值是整数的连续非空子串个数 。

$ a_{l} $ 到 $ a_{r} $ 之间元素之和为 $ \tfrac{( a_{l} + a_{r} ) \times ( r - l + 1 )}{2} $ ，所以子串的平均值为 $ \tfrac{( a_{l} + a_{r} )}{2} $ 。
因为 $ a_{1} = k $ ，所以 $ a_{l} = k + ( l - 1 ) \times d  $ ，$ a_{r} = k + ( r - 1 ) \times d  $ 。平均值就可以化简为 $ k - d + \tfrac{( l + r ) \times d }{ 2 } $ ，如果为整数 ，只需要判断 $ ( l + r ) \times d $ 是否为偶数即可 。

当 $ d $ 为偶数的话 ，答案为 $ \tfrac{ n \times ( n - 1 ) }{ 2 } $ 。
当 $ d $ 为奇数时 ，分析只有 $ l $ 和 $ r $ 同为偶数或奇数时 ，才会使 $ l + r $ 为偶数 。只需要将 $ n $ 个数中的奇偶数的个数计算出来 ，计算出两两配对的个数即可 ：

1. 当 $ n $ 为奇数时 ，奇数的个数为 $ \tfrac{ n + 1 }{ 2 } $ ，偶数的个数为 $ \tfrac{ n - 1 }{ 2 } $ ，所以奇数两两配对的个数为 $ \tfrac{ n ^ 2 - 1 }{ 8 } $ ，偶数两两配对的个数为 $ \tfrac{ n ^ 2 - 4 \times n + 3 }{ 8 } $ ，结果为 $ \tfrac{ ( n - 1 ) ^ 2 }{ 4 } $ 。

3. 当 $ n $ 为偶数时 ，奇数的个数为 $ \tfrac{ n }{ 2 } $ ，偶数的个数为 $ \tfrac{ n }{ 2 } $ ，所以奇数两两配对的个数为 $ \tfrac{ n \times ( n - 2 ) }{ 8 } $ ，偶数两两配对的个数为 $ \tfrac{ n \times ( n - 2 ) }{ 8 } $ ，结果为 $ \tfrac{ n \times ( n - 2 ) }{ 4 } $ 。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n,k,d;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>k>>d;
		int ans=n;
		if(d&1)
		{
			if(n&1) ans+=(n-1)*(n-1)/4;
			else ans+=n*(n-2)/4;
		}
		else ans+=n*(n-1)/2;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：篮网总冠军 (赞：0)

本题是一道结论题。

首先，我们来计算，从这个等差数列第 $l \sim r$ 项的和是多少？

当然是 $(r-l+1) \times k  + (l-1+r-1) \times (r-l+1) \div 2 \times d$。

再思考，因为这个式子要求被 $r-l+1$ 整除，那我们就可以把其中 $r-l+1$ 的倍数去掉。

我们发现，当 $d$ 是偶数时，所有序列都可以满足条件，直接计算序列总数即可。

而当 $d$ 是奇数时，要求 $l+r-2$ 是 $2$ 的倍数，即 $l+r$ 是 $2$ 的倍数，也就是指 $l,r$ 同奇同偶。

也就是指，这个序列的长度是奇数。

那么我们只要求出长度是奇数的序列个数即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--){
		long long n,k,d;
		cin>>n>>k>>d;
		if (d%2==0){
			cout<<n*(n+1)/2<<endl;
		}
		else{
			if (n%2==0){
				cout<<(n+2)*n/4<<endl;
			}
			else cout<<(n+1)*(n+1)/4<<endl;
		}
	}
	return 0;
}
```

---

## 作者：keatsli (赞：0)

用等差数列求和公式转化条件，即为首项加尾项是偶数，考虑分类讨论：

## 若 $2\mid d$

此时所有项都是奇数或者都是偶数，故任选两项加起来都是偶数，答案为 $C_{n+1}^2$。

## 若 $2\nmid d$

### 若 $2\mid n$

此时奇数偶数个数相同，都为 $\dfrac{n}{2}$，故答案为 $2\times C_{\frac{n}{2}+1}^2$。

### 若 $2\nmid n$

此时奇数偶数一个有 $\lfloor\dfrac{n}{2}\rfloor$，另一个有 $\lceil\dfrac{n}{2}\rceil$ 个，故答案为 $C_{\lfloor\frac{n}{2}\rfloor+1}^2+C_{\lceil\frac{n}{2}\rceil+1}^2$。

如果你观察力不错的话可以发现最后两种情况可以合并，不过为了实现简单就没有合并。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int T;cin>>T;
	while(T--){
		int n,k,d;cin>>n>>k>>d;
		if(d%2==0)cout<<n*(n+1)/2<<'\n';
		else{
			int tmp=n/2;
			if(n%2==0)cout<<(tmp+1)*tmp<<'\n';
			else cout<<(tmp+2)*(tmp+1)/2+(tmp+1)*(tmp)/2<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：__youzimo2014__ (赞：0)

## 思路

首先，等差数列的子串一定也是等差数列。

**声明：以下称 $a$ 为等差数列的首项， $b$ 为等差数列的末项。**

首先，等差数列的子串一定也是等差数列。

等差数列的平均数为 $\frac{(a+b)}{2}$。~~这个应该不需要证明了吧。~~

也就是说，一个等差数列的平均数为整数，当且仅当 $a+b$ 为偶数。

我们这里可以分两种情况讨论。

### 第一种情况：公差 $d$ 为偶数

根据题目给出的信息，我们知道 $a = k$，$b = k +d(n-1)$。

那么 $a + b = 2k + d(n-1)$。

不难发现 $2k$ 必然为偶数，$d(n-1)$ 也必然为偶数，也就是说，当 $d$ 为偶数时，所有子串的平均值都是整数。

现在就剩最后一个问题：这个等差数列有多少个子串。

答案是 $\sum^n_{i=1} n-i+1$，因为以第 $i$ 个元素开头的子串就有 $n-i+1$ 个。

当 $i = 1$ 时，$n-i+1=n$，当 $i = n$ 时，$n-i+1=1$。

根据等差数列求和公式，我们可以求出答案为 $\frac{(1+n)\times n}{2}$。

### 第一种情况：公差 $d$ 为奇数

在这里 $a + b = 2k + d(n-1)$ 也同样适用。

$2k$ 一样必然为偶数，但是 $d(n-1)$ 就不一定为偶数了。

只有当这个子串的长度为奇数时，这个子串的平均值才是整数。

不难发现第 $i$ 个元素开头的子串，有 $\lceil \frac{n-i+1}{2} \rceil$ 个是满足条件的。

也就是说答案是 $\sum^n_{i=1}\lceil \frac{n-i+1}{2} \rceil$。

我们把最后几个 $\lceil \frac{n-i+1}{2} \rceil$ 倒着列出来：

`1 1 2 2 3 3 4 4 5`


为什么会这样呢，因为 $n-i+1$ 为奇数时，$\lceil \frac{n-i+1}{2} \rceil = \frac{n-i+2}{2}$，这是常识。

根据等差数列求和公式，我们得到，在 $n$ 为奇数时，答案为 $(1+\frac{n}{2})\times(\frac{n}{2}) + (\frac{n}{2}+1)$，在 $n$ 为偶数时，答案为 $(1+\frac{n}{2})\times(\frac{n}{2})$。

附上代码：

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    int T;
    cin >> T;
    while (T--) {
        int n, k, d;
        cin >> n >> k >> d;
        long long ans = 0ll;
        if (d & 1ll) {
            if (n & 1ll) {
                ans = (1ll+n/2ll)*(n/2ll)+(n/2ll+1ll);
            } else {
                ans = (1ll+n/2ll)*(n/2ll);
            }
        } else {
            ans = (1ll+n)*n/2ll;
        }
        cout << ans << endl;
    }
    return 0;
}


```

---

