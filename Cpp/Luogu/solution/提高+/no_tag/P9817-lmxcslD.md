# lmxcslD

## 题目背景

欢迎新斗友@[lmxcslD](https://www.luogu.com.cn/user/358957)

## 题目描述

定义一个长度为 $m$ 的非空序列 $p_1,p_2,...,p_m$ 是**乱**的当且仅当满足以下两个条件。

- 所有元素之和不超过 $n$，即 $\sum_{i=1}^m p_i\le n$。
- 对于任意一个元素 $p_i$ 满足 $p_i=1$ 或 $p_i$ 为质数。

定义一个**乱**的序列 $p_1,p_2,...,p_m$ 的**乱斗值**为该序列中所有元素减 $k$ 的平方和，即 $\sum_{i=1}^m (p_i-k)^2$。

特别的，定义一个**不乱**的序列的乱斗值为 $0$。

现在给定两个正整数 $n,k$，问所有序列中**乱斗值**最大的序列的**乱斗值**是多少。

## 说明/提示

#### 样例解释

对于样例第 $1,2,3,4$ 组数据，其中一种**乱斗值**最大的序列分别为 $(1),(2),(1,3),(5)$。

#### 数据范围与约定

|测试点编号|$T$|$n$|$k$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$=100$|$\le 10$|$\le 10$|无|
|$2$|$=200$|$\le 30$|$\le 10$|无|
|$3$|$=300$|$\le 10^3$|$\le 5\times 10^4$|无|
|$4$|$=400$|$\le 10^5$|$\le 5\times 10^4$|无|
|$5$|$=500$|$\le 10^7$|$\le 5\times 10^4$|无|
|$6$|$=600$|$\le 10^9$|$=1$|$n$ 为质数|
|$7$|$=700$|$\le 10^9$|$=1$|无|
|$8$|$=800$|$\le 10^9$|$=44444$|无|
|$9$|$=900$|$\le 10^9$|$\le 5\times 10^4$|$n$ 为质数|
|$10$|$=10^3$|$\le 10^9$|$\le 5\times 10^4$|无|

对于所有测试点，保证 $1\le T\le 10^3$，$1\le n\le 10^9$，$1\le k\le 5\times 10^4$。

## 样例 #1

### 输入

```
5
1 1
2 1
4 1
5 2
10 10```

### 输出

```
0
1
4
9
810```

# 题解

## 作者：dehsirehC (赞：18)

## $n$ 为质数

解法：其中一种答案序列为 $n$ 个 $1$ 或一个 $n$ ，将两者的较大值输出即可。

证明：对于一个恰好包含 $m$ 个 $1$ 的序列，它的**乱斗值**不超过 $f(m)=m(k-1)^2+(n-m-k)^2$ 。

容易发现上述解法的答案即为 $\max(f(0),f(n))$ 。考虑随着 $m$ 的增大 $f(m)$ 的变化规律。

$$f(m+1)-f(m)=(k-1)^2-2(n-m-k)+1$$

根据上式容易得到当某一个 $m'$ 满足 $f(m')\ge f(m'-1)$ 时，对于任意 $m\ge m'$ 都满足 $f(m)\ge f(m-1)$ 。

换句话说，函数 $f(m)$ 是一个单谷函数，而对于它的极值，必定会在其定义域的两个极值处取到，即 $f(0)$ 或 $f(n)$ 。

## $k=1$

现在我们不需要考虑 $p_i-k<0$ 的情况。感觉一下，发现 $p_i$ 越大性价比越高。

设不超过 $n$ 的最大质数为 $P$ ，如果答案序列包含 $P$ ，我们将问题递归到 $(n-P,k)$ ，否则 $p_i<P$ 。

我们首先忽略掉 $p_i$ 为质数这一条件，若一个序列存在两个数 $1\le p_i\le p_j<P-1$ ，将 $p_j\gets p_j+1$ ， $p_i\gets p_i-1$ 一定更优。

这样一直调整下去，当 $n-P+1<P$ 时，最终一定会调整到 $p=(P-1,n-P+1)$ 。

容易发现当 $n$ 比较大时， $P$ 远大于 $n-\sqrt n$ ，即 $(P-1)^2\ge (P-2)^2+(n-P)^2$ 。

具体而言 $n-P$ 的最大值取决于质数间隙，在 $n$ 取到 $10^9$ 时最大质数间隙也不过几百。

当 $n$ 比较小的时候可以暴力 `DP` ，~~但实践证明答案序列必定包含 $P$ 。~~

至于 $P$ 怎么找，可以直接暴力枚举，再 $O(\frac{\sqrt n}{\ln n})$ 判断是否为质数，由于质数间隙很小且跑不满，故可以通过。

顺带一提，如果 $O(\sqrt n)$ 判断是否为质数也可以通过，感觉很难卡......

## 正解

我们延续 $k=1$ 时的思路，找到不超过 $n$ 的最大质数 $P$ 。

若答案序列包含超过 $n-P$ 个 $1$ ，则答案序列必定为 $n$ 个 $1$ ，证明类似 $n$ 为质数时的思路。

接下来考虑答案序列中 $1$ 的数量不超过 $n-P$ 的情况，如果答案序列包含 $P$ 则依旧将问题递归到 $(n-P,k)$ 。

否则的话首先忽略掉 $p_i$ 为质数这一条件，还是按照 $k=1$ 的思路不断调整序列 $p$ 。

注意可以忽略掉 $1<p_i<k$ 时的情况，因为可以将它们调成 $1$ 使**乱斗值**更大。

设序列 $p$ 中有 $m$ 个 $1$ ，当 $n-m-P+1<P$ 时，最终 $p$ 除 $1$ 外仅包含 $P-1$ 和 $n-m-P+1$ 。

根据 $n$ 为质数中的思路，容易得到若 $p$ 包含 $P-1$ 时，剩下的数必定为 $n-P+1$ 个 $1$ 或一个 $n-P+1$ ， $m\ge 1$ 时矛盾。

现在我们说明了该情况下 $m$ 必定为 $0$ ，接下来考虑 $(P-k)^2$ 与 $(P-k-1)^2+(n-P-k+1)^2$ 的大小关系。

考虑当 $n\le (k-1)^2$ 时， $n^2\le n(k-1)^2$ ，即答案序列必定由 $n$ 个 $1$ 组成。

当 $n>(k-1)^2$ 时且 $n$ 比较大时，依旧由于质数间隙很小，故 $(P-k)^2$ 必定大于 $(P-k-1)^2+(n-P-k+1)^2$ 。

当 $n$ 比较小的时候可以暴力 `DP` ，~~但实践证明答案序列在这种情况下必定包含 $P$ 。~~

---

## 作者：noi2077 (赞：7)

可以发现，将序列中的数从大到小排序后，第 $i$ 个数 $p_i$ 要么是 $1$，要么是不超过 $n-\sum_{j=1}^{i-1}p_j$ 的最大的质数。



我们发现满足这个要求的序列并不太多，直接枚举所有满足这个要求的序列，对乱斗值取 $\max$ 就行。

找不超过 $x$ 的最大的质数可以暴力枚举从 $x$ 到 $1$ 的每个数，然后用 `Miller-Rabin` 判断是否是质数，如果是就 `break`。

```cpp
using namespace std;
typedef long long ll;
typedef long double ld;
ll qp(ll a, ll b, ll mod)
{
    ll ans = 1;
    a %= mod;
    while(b)
    {
        if(b&1) ans = ans*a%mod;
        a = a*a%mod;
        b >>= 1;
    }
    return ans;
}
ll pri[10] = {2,3,5,7,11,13,17,19,23};
inline bool judge(ll x)
{
    for(int i = 0; i <= 8; i++)
    {
        if(pri[i] == x) return true;
        else if(pri[i] > x) return false;
        ll cnt = qp(pri[i], x-1, x);
        if(cnt != 1) return false;
        else {
            ll now = x-1;
            while(now%2 == 0 && cnt == 1)
            {
                now /= 2;
                cnt = qp(pri[i], now, x);
                if(cnt != 1 && cnt != x-1) return false;
            }
        }
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--)
    {
        ll n, k;
        cin >> n >> k;
        ll ans = n*(k-1)*(k-1);
        ll cur = 0;
        for(int i = n; i >= k; i--)
        {
            if(judge(i))
            {
                ans = max(ans, cur+(i-k)*(i-k)+(n-i)*(k-1)*(k-1));
                cur += (i-k)*(i-k);
                n -= i;
                i = min(n, (ll)i)+1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：int_R (赞：4)

[P9817 lmxcslD](https://www.luogu.com.cn/problem/P9817)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/P9817.html)

这题感觉是有意思的。

先考虑构造 $m$ 个 $p_i$，答案为 $m\times (1-k)^2$。

然后考虑什么情况下是更优的。尽可能使 $(p_i-k)^2$ 大，那就要尽可能与 $k$ 的差值大，当 $p_i\leq k$ 时肯定是全为 $1$ 最优。那么如果我们要写出一个 $p_i>k$，我们对答案的更改是 $(p_i-k)^2-p_i\times (1-k)^2$，就相当于是删掉了 $p_i$ 个 $1$，添加了一个 $p_i$。所以只有当 $(p_i-k)^2>p_i\times (1-k)^2$ 我们才有必要写上 $p_i$。再说对于两个均满足条件的 $p_i,p_j(p_i<p_j)$ 我们一定是贪心的先添加 $p_j$ 更优。

所以，我们设 $f(x)$ 为 $n=x$ 时最大的答案，$p_i$ 为最大的小于等于 $x$ 的质数，则

$$
f(x)=\begin{cases} f(x-p_i)+(p_i-k)^2 & (p_i-k)^2>p_i\times (1-k)^2\\ x\times (1-k)^2 & (p_i-k)^2\leq p_i\times (1-k)^2\end{cases}
$$

我们直接暴力递归进行，暴力找到当前 $p_i$。要有优化，即若当前 $(p_i-k)^2\leq p_i\times (1-k)^2$ 我们直接结束（$p_i$ 越大越有可能满足条件），返回 $x\times (1-k)^2$。同时判断是否是质数时若找到了一个因子就直接跳出。

因为 $x-p_i$ 不会很大，所以暴力找 $p_i$ 的复杂度是正确的，递归因此也不会很多次，所以时间复杂度为 $O(\text{良好})$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#define int long long
using namespace std;
int T,n,k;
int DO(int x)
{
    if(2*k<=x)
    {
        for(int tmp=x;2*k<=tmp&&(tmp-k)*(tmp-k)>tmp*(k-1)*(k-1);--tmp)
        {
            bool flag=false;
            for(int i=2;i<=sqrt(tmp);++i) 
                if(!(tmp%i)){flag=true;break;}
            if(!flag) return (tmp-k)*(tmp-k)+DO(x-tmp);
        }
    }
    return x*(k-1)*(k-1);
}
main()
{
#ifdef ONLINE_JUDGE
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
#endif
    cin>>T;
    while(T--)
    {
        cin>>n>>k;
        cout<<DO(n)<<'\n';
    }
}
```

---

## 作者：NBest (赞：1)

这里提供一个非常暴力但是期望复杂度很低的算法。

不难想到要么就是全部放 $1$，要么就是取出一个最大的质数，然后对于剩下的部分继续按照这样的策略求答案。

因为质数间隔不大，然后暴力判断质数复杂度是 $O(\sqrt n)$ 的，再加上 IOI 的 buff，我们可以直接考虑从大到小枚举质数，因为取到最后取的次数也不多，预期复杂度就是 $O(\sqrt n)$ 乘上一个比较大的常数，实际情况跑的很快。
## $Code$
```cpp
bool check(int x){//暴力判断质数（1也算）
    if(x<=2)return 1;
    if(x+1&1)return 0;
    for(int j=3;j*j<=x;j+=2)if(x%j==0)return 0;
    return 1;
}
ll work(int n,int k,int i=0){//暴力递归求解
    if(!n)return 0;
    for(i=n;!check(i);--i);
    if(1ll*(i-k)*(i-k)<=1ll*i*(k-1)*(k-1))return 1ll*n*(k-1)*(k-1);
    return work(n-i,k)+1ll*(i-k)*(i-k);
}
int main(){
    for(int T=read();T--;){
        int n=read(),k=read();
        printf("%lld\n",work(n,k));
    }
    return 0;
}
```

---

## 作者：flyingfrog (赞：1)

可以将题目理解成一个长度为 $n$ 且全为 $1$ 的序列，每次选择 $x\in P$ 个 $1$ 合并成一个 $x$，求最大的 $\sum (p_i - k)^2$。

记该序列的乱斗值为 $s$，则初始时 $s = n(k - 1)^2$，合并 $x$ 个 $1$ 所得到序列的 $s'$ 与 合并前序列的 $s_0$ 的差值为 $(x - 1)(x - k^2)$，故只有当 $x > k^2$ 时合并更优，且合并一个大 $x$ 所产生的贡献一定大于多个小 $x$ 产生贡献之和，故从大到小贪心地合并序列。

合并的 $x$ 直接枚举并判断是否为质数即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline void FileIO(string s){
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int T, n, k, s;

bool check(int x){
	if(x == 2 || x == 3)  return 1;
	for(int i = 2; i <= sqrt(x); i ++){
		if(x % i == 0)  return 0;
	}
	return 1;
}

signed main(){
	//FileIO();
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	while(T --){
		cin >> n >> k;
		s = n * (k - 1) * (k - 1);//初始值
		while(n > k * k){
			bool flag = 0;//记录是否有合并操作
			for(int t = n; t > k * k; t --){
				if(check(t)){
					flag = 1;
					n -= t;
					s += (t - 1) * (t - k * k);
					break;
				}
			}
			if(!flag)  break;
			//若未产生合并操作，则说明无法产生更大的 s，直接 break
		}
		cout << s << '\n';
	}

	return 0;
}

```

---

## 作者：_saltFish_ (赞：0)

# 简要题意

给出 $n,k$，求一个任意长度的序列 $p$。假设该序列长为 $m$，要求 $\sum\limits_{i=1}^{m}p_i\le n,p\in {\{1,prime\}}$。最大化 $\sum\limits_{i=1}^{m} (p_{i}-k)^2$，输出这个最大值。

# 思路

可以填 $1$ 是一个很有用的性质，这代表着对于任何的 $n,k$，答案最大的序列中一定有满足 $\sum\limits_{i=1}^{m} p_{i}=n$ 的序列。

因为对于每一种序列，我们一定可以通过在后面不断添加 $1$ 使得上述成立。

所以我们可以考虑填完质数之后在后面疯狂塞 $1$ 的方式来凑数。

那么接下来我们考虑怎么填质数。

首先，这个质数 $pri$ 一定要满足 $(pri-k)^2>pri(k-1)^2$，否则把这个质数换成 $pri$ 个 $1$ 会更优。稍微转化一下可以得到 $(pri-k^2)(pri-1)>0$，显然有 $pri-1>0$，所以 $pri>k^2$。

现在我们解决了选什么样的质数更好，但是当几个质数相冲突怎么办呢。

假设我们现在有三个质数 $a,b,c$，满足 $a=b+c,b>c$，那么很容易可以证明 $(a-k)^2>(b-k)^2+(c-k)^2$。

综上所述，我们选择更大的满足 $pri>k^2$ 的素数是最优的。考虑贪心地从大到小选质数，假设当前找到的最大的质数是 $pri$，如果它满足 $pri>k^2$，那么我们就将问题规模转化为 $\Delta n=n-pri,k$。否则就代表其余的质数全都不合法，我们直接舍弃不考虑，转而将 $\Delta n$ 的贡献全部当做 $1$ 来考虑，贡献就是 $\Delta n(k-1)^2$。

找比一个数小的最大的质数我们直接从大到小暴力枚举判断就行，顺便开个 map 存一下（其实都一样）。

# Code

```cpp
#include <iostream>
#include <map>

#define LL long long

using namespace std;

LL n, k;
map<int, int> s;

bool check(int x) {
	for(int i = 2; i * i <= x; i++) {
		if(x % i == 0) return 0;
	}
	return 1;
}

int getpri(int x) {
	if(s[x]) return s[x];
	
	s[x] = -1;
	for(int i = x; i > 1; i--) {
		if(check(i)) return (s[x] = i);
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int _T;
	cin >> _T;
	
	while(_T--) {
		cin >> n >> k;
		
		LL ans = 0;
		
		while(114514) {
			int pri = getpri(n);
			
			if(pri == -1 || pri <= k * k) break;
			
			ans += (pri - k) * (pri - k);
			n -= pri;
		}
		
		ans += n * (k - 1) * (k - 1);
		
		cout << ans << '\n';
	}
}
```

---

## 作者：cabbyblue (赞：0)

我们看这两句话 $\sum_{i=1}^m p_i\le n$，$\sum_{i=1}^m (p_i-k)^2$。

显然，我们可以贪心，具体如下:

首先，保证 $\sum_{i=1}^m p_i= n$

当 $k$ 为 $1$，$m$ 为二时，对于两种拆分 $p_1=p_2$ 或 $p_1=n-1,p_2=1$。

显然，通过计算，第二种方法更优，不难证明没有更有方法。

通过类比，当 $k=1$ 时，我们每次选取 $\le n'$ （其中 $n'$ 初始为 $n$，每次选完后减去选的数）的最大的质数或 $1$，作为 $p$ 中的一员，选取可以暴力枚举。

我们此时要想 $k\not=1$ 时应当怎么做。

此时除了向上找，还可以向下，显然此时 $1$ 为最优解。

显然每一次我们可以找最大质数或 $1$，如果选 $1$，不难证明继续选下去最大质数的贡献单调不降，而 $1$ 的贡献不变，因此后续都应当选 $1$。

```cpp
int _main(int n){//计算答案，k在局外，但局内计算询问n',k的答案，函数内n表示n'。
	if(!n){
		return 0;
	}
	int fs;
	fs=fd(n);//计算小于等于n'的最大质数fs
	return max(_main(n-fs)+(fs-k)*(fs-k),(k-1)*(k-1)*n);//选取fs为p数组中的一个_main(n-ps)计算剩下的解，在增加(fs-k)*(fs-k)，即当前数的贡献。同时考虑1的情况，后续不用递归。
}
```
可以枚举小于等于 $n'$ 的所有数，从 $n'$ 开始，用 $\sqrt{h}$ 的时间复杂度来判定是否为质数，其中 $h$ 为此时枚举到的质数。

```cpp
bool ck(int s){//判定
	if(s==1){
		return 1;//在这里，1也算质数
	}
	for(int i=2;i*i<=s;i++){
		if(s%i==0){
			return 0;
		}
	}
	return 1;
}
int fd(int n){//枚举
	int x;
	x=n;
	while(!ck(x)){
		x--;
	}
	return x;
}
```

因此代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int k;
bool ck(int s){
	if(s==1){
		return 1;
	}
	for(int i=2;i*i<=s;i++){
		if(s%i==0){
			return 0;
		}
	}
	return 1;
}
int fd(int n){
	int x;
	x=n;
	while(!ck(x)){
		x--;
	}
	return x;
}
int _main(int n){
	if(!n){
		return 0;
	}
	int fs;
	fs=fd(n);
	return max(_main(n-fs)+(fs-k)*(fs-k),(k-1)*(k-1)*n);
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n>>k;
		cout<<_main(n)<<endl;
	} 
	return 0;
}
```

---

## 作者：_farawaystar_ (赞：0)

不难通过一些基本的数感和简单的不等式知识发现从大到小选择第 $i$ 个数字 $p_i$，$p_i$ 只可能在两种情况下最优：

1. 选择 $1$。

2. 选择不大于 $n-\Sigma_{j=1}^{i-1}p_j$ 的最大质数。


通过不等式的推导和变形就可以发现如果一个质数 $t$ 满足 $t>k^2$ 时选择它更合适，否则选择 $1$。然而我们选择数字是不增的，故可以直接在循环语句中判断退出。

然而线性筛素数是筛不下的，但是质数间隙很小，所以：

1. 第 $i$ 个数字远远大于第 $i+1$ 个数字。

2. 当前不大于 $n-\Sigma_{j=1}^{i-1}p_j$ 的最大质数必然接近于 $n-\Sigma_{j=1}^{i-1}p_j$。

故直接暴力查询即可，完全不会超时。

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int t,n,k,p;
long long k2,ans;
void del(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
bool prime(int x){
	for(int i=2;i<=sqrt(x);i++)
		if(x%i==0)
			return 0;
	return 1;
}
int main(){
	del();
	cin>>t;
	while(t--){
		cin>>n>>k;
		k2=1ll*k*k;
		while(n){
			for(p=n;!prime(p);p--);
			if(p>k2)ans+=1ll*(p-k)*(p-k);
			else break;
			n-=p;
		}
		ans+=1ll*n*(k-1)*(k-1);
		cout<<ans<<endl;
		ans=0;
	}
	return 0;
}
```

注：记得一些ll的细节

---

## 作者：哈哈人生 (赞：0)

## 题外话
没人写 dp 题解？其实 dp 也是很好写的。

## 思路
一道很好 dp 题，我们就考虑凑出 $n$，则一定要用到 $n$ 以下的质数，且贪心易猜是正确的（即最大的质数一定在答案序列里）。要注意的是，负数是可以出现的，且 $1-k$ 是唯一需要考虑的，所以可以考虑 dp，需要用到的是 $n$ 以下的质数的最大乱斗值，加起来即可。赛时我写的是递归式 dp，循环式的请读者自己思考。

## 代码
还是比较容易写出来的。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k;
bool pr(int x) {
	for(int i=2; i*i<=x; i++) {
		if(x%i==0)return false;
	}
	return true;
}
int dg(int x) {
	if(pr(x))return max((1-k)*(1-k)*x,(x-k)*(x-k));
	int a=(1-k)*(1-k)*x,b=0;
	while(x) {
		int x2=x;
		while(!pr(x2))x2--;
		b+=dg(x2);
		x-=x2;
	}
	return max(a,b);
}
signed main() {
	cin>>t;
	while(t--) {
		cin>>n>>k;
		cout<<dg(n)<<endl;
	}
	return 0;
}
```
点个赞呗。

---

