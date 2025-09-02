# [EPXLQ2024 fall round] Simple Math Problem

## 题目背景


![](https://cdn.luogu.com.cn/upload/image_hosting/v0535jal.png)

于是原先的 C 变成了 A，原先的 D 变成了 B，原先的 F 变成了 E，然后就有了这道题。

注：想拿到**快速 AK 变换奖**请在代码注释部分写明本题代码复杂度证明。

## 题目描述

Cute_QiQi 有一个可爱的整数 $n$。

现在，Cute_QiQi 想知道有多少个 $m \in (0,n)$，满足 $nm$ 能被 $n-m$ 整除。

## 说明/提示

### 样例解释

当 $n = 114$ 时，可有 $m \in \{38,57,76,78,95,96,102,105,108,110,111,112,113\}$。

当 $n = 1919$ 时，可有 $m \in \{1558,1818,1900,1918\}$。

### 数据规模与约定

**本题采用捆绑测试与子任务依赖。**

设 $p$ 为 $n$ 质因数分解后最大的质数，$p,q$ 均为质数。

| $\text{Subtask}$ | $n \le$ | 特殊性质 | 分值 | 依赖子任务
| :-: | :-: | :-: | :-: | :-: |
| $0$ | $10^{14}$ | $n = p$ | $2$ | |
| $1$ | $10^3$ | |  $7$ | |
| $2$ | $10^6$ | |$11$ | $1$ |
| $3$ | $10^9$ | |$24$ | $1,2$ |
| $4$ | $10^{14}$ | $n = pq$ |  $12$ | |
| $5$ | $10^{14}$ | $p \le 10^6$ |   $15$ | |
| $6$ | $10^{14}$ | |  $29$ | $0,1,2,3,4,5$ |

对于所有数据，$1 \le n \le 10^{14}, 1 \le T \le 10$。

## 样例 #1

### 输入

```
2
114
1919```

### 输出

```
13
4```

# 题解

## 作者：Eason_cyx (赞：5)

@junjie_zhao 在我写这题的时候一直嘲讽我 /kel

感谢 @Augenstern5 提供的指导。

------

记 $n-m=x$，则题目中的条件变为

$$n(n-x) \bmod x = 0$$

展开，得 

$$n^2-nx \bmod x = 0$$

显然有 $nx \bmod x = 0$，所以问题变成了 $n^2 \bmod x = 0$，也就是找 $n^2$ 的所有因数，且由于 $1 \le m \lt n$，所以我们要找的就是 $1 \le x \lt n$ 中所有 $n^2$ 因数的个数。

记 $n^2$ 共有 $p$ 个因子，那么显然 $p$ 是奇数。注意到 $n^2$ 的因子中除了 $n$ 以外一定可以分成 $\frac{p-1}{2}$ 组，每组的两个数 $a,b$ 都可以有 $a \times b = n^2$。那么显然一定有 $\max(a,b) > n$，所以这样每一组对答案的贡献就是 $1$；那么最后答案就是 $\frac{p-1}{2}$。

又因为显然有如下结论：

假设 $n=p_1^{q_1}p_2^{q_2}\dots p_k^{q_k}$，那么 $n^2=p_1^{2\times q_1}p_2^{2\times q_2}\dots p_k^{2\times q_k}$。

所以最终直接对 $n$ 进行质因数分解即可。假设我们得到了 $n=p_1^{q_1}p_2^{q_2}\dots p_k^{q_k}$，则有一个定理：$n$ 的质因数个数为 $\displaystyle\prod_{i=1}^{k}(q_i+1)$。所以有 $p=\displaystyle\prod_{i=1}^{k}(2\times q_i+1)$。

时间复杂度 $O(T\sqrt n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
unordered_map<int, int> mp;
signed main() { ios::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--) {
		int n; cin >> n; mp.clear();
		for(int i = 2;i * i <= n;i++)
			if(n % i == 0) {
				while(n % i == 0) n /= i, mp[i]++;
			} if(n != 1) mp[n]++; for(auto i : mp) mp[i.first] *= 2;
		long long num = 1; for(auto i : mp) num = (num * (mp[i.first] + 1)); cout << num / 2 << "\n";
	}
	return 0;
}
```

---

## 作者：Tachanka233 (赞：4)

赛时打表猜了 $1h$ 的结论终于猜出来了……
## 题意
对于任意正整数 $n$ 求有多少个数 $m\in[1,n)$ 满足 $(n-m)\mid nm$。
## 思路
设 $k=n-m$，则 $(n-m)\mid nm\Leftrightarrow k\mid n\times(n-k)$，而考虑到 $n\times(n-k)=n^2-nk$，所以 $k\mid n\times(n-k)\Leftrightarrow k\mid n^2$。  
那么接下来就非常显然了，因为 $m\in[1,n)$，所以 $k\in[1,n)$，那么 $k$ 就是 $n^2$ 的所有 $<n$ 的因数。我们只需要找出 $n^2$ 小于 $n$ 的因数个数就可以了。注意到 $\forall x\mid n,x\in[1,n)$，有 $n\div x\mid n,x\in(n,n^2]$，即 $>n$，$<n$ 的因数有一一对应关系，于是答案即为 $n^2$ 的因数个数 $-1$ 再 $\div2$。  
于是求出 $n^2$ 的因数个数即可。可以对 $n$ 进行质因数分解。设 $n=p_1^{c_1}\times p_2^{c_2}\times\dots\times p_t^{c_t}$（$p_1,p_2,\dots,p_t$ 是不同质数），则 $n^2$ 的因数个数为 $(2c_1+1)\times(2c_2+1)\times\dots\times(2c_t+1)$，答案为 $\frac{(2c_1+1)\times(2c_2+1)\times\dots\times(2c_t+1)-1}{2}$。  
update：实现时，先用线性筛筛出质数是更优的。这会使你代码的复杂度从 $O(T\sqrt n)$ 变为 $O(\sqrt n)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
signed fac[102],prime[10000007],cnt;
bool b[10000007];
inline void solve(){
    signed tmp=0;
    int ans=1;
    cin>>n;
    for(int i=1;i<=cnt;i++){//枚举质因数
        if(prime[i]*prime[i]>n)break;
        if(n%prime[i]==0){
            fac[++tmp]=0;
            while(n%prime[i]==0)n/=prime[i],fac[tmp]++;//计算个数
        }
    }
    if(n>1)fac[++tmp]=1;//特判最后的质数
    while(tmp--){
        ans*=(2*fac[tmp+1]+1);//计算答案
    }
    ans=(ans-1)/2;
    cout<<ans<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    b[1]=1;
    for(int i=2;i<=10000007;i++){
        if(!b[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt;j++){
            if(i*prime[j]>10000007)break;
            b[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
    cin>>t;
    while(t--)solve();
}
```

---

## 作者：ARIS2_0 (赞：4)

### 前言

有一说一，题面确实很 Simple，证明也很 Simple，但是赛时切不 Simple。

### 前置知识

对于一个数 $n$，把它分解质因数后得到 $n=p_1^{c_1}\times p_2^{c_2}\times\dots\times p_q^{c_q}$，其中 $p_1,p_2,\dots,p_q$ 为互不相同的质数，则 $n$ 的因数个数为 $\prod\limits_{i=1}^q(c_i+1)$。

### 思路

设 $x=n-m$，得 $x\in[1,n)$，则题目转化为求满足 $\frac{n(n-x)}{x}$ 为整数的 $x$ 的个数。

发现 $\frac{n(n-x)}{x}=\frac{n^2}{x}-n$，实质上是求 $n^2$ 小于 $n$ 的因数个数。

考虑到 $n^2$ 的因数一定是由 $p$ 个小于 $n$ 的数，$p$ 个大于 $n$ 的数，与一个 $n$ 组成的，则 $n^2$ 小于 $n$ 的因数个数即为 $n^2$ 的因数个数除于 $2$ 向下取整。

因为对 $n$ 分解质因数后，我们能得到 $n^2$ 的质因数组成，计算 $n^2$ 的因数个数显然是 $O(\sqrt n)$ 的，于是就做完了。

~~是不是很 Simple，然而我赛时没切~~

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int inf=1e16,maxn=70;
int cnt[maxn];
int solve(int n){//返回n^2的因数个数/2
//没有使用prime数组，因为计算因数不需要
    int tot=0;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            cnt[++tot]=0;
            while(n%i==0)n/=i,cnt[tot]++;
        }
    }
    if(n>1)cnt[++tot]=1;
    int ans=1;
    for(int i=1;i<=tot;i++)ans*=(cnt[i]*2+1);
    return ans/2;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;cin>>t;
    while(t--){
        int n;cin>>n;
        cout<<solve(n)<<"\n";
    }
	return 0;
}
```

---

## 作者：CaiZi (赞：3)

### 思路分析
记 $k=n-m$，则条件变化为 $k\mid nk-n^2$。显然 $k\mid nk$，所以实际条件即为 $k\mid n^2$，即求 $n^2$ 的满足 $\in[1,n-1]$ 的因子个数。

考虑质因数分解，令 $n=\prod_i p_i^{\alpha_i}$，那么 $n^2=\prod_i p_i^{2\alpha_i}$。对于每一个 $p_i$，你可以选择它的 $[0,2\alpha_i]$ 次幂，再把每个 $p_i$ 的每种次幂选择的方案组合，可以组合出 $\prod_i(2\alpha_i+1)$ 个不同的数（由于质因数分解的唯一性，所以选择组合出的数也是互不相同的），且这些数都是 $n^2$ 的因子。

然后就 Simple 了，因为要求满足 $\in[1,n-1]$，所以先把因子 $n$ 去掉，然后对于每个因子 $t$，若 $t<n$，则 $\dfrac{n^2}{t}>n$，所以答案再除以 $2$ 即可。

最终答案为 $\dfrac{\prod_i(2\alpha_i+1)-1}{2}$。
### 代码展示
时间复杂度 $O(T\sqrt n)$。如果线性筛预处理，可以做到 $O(T+\sqrt n)$，但是没必要。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a,b;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>t;
	while(t--){
		a=1;
		cin>>n;
		for(int i=2;i<=n/i;i++){
			b=0;
			while(n%i==0){
				n/=i;
				b++;
			}
			a=a*(2*b+1);
		}
		if(n>1){
			a=a*3;//注意特判没筛干净的情况，此时只剩下一个质因子，所以答案要乘(2*1+1)
		}
		cout<<(a-1)/2<<'\n';
	}
	return 0;
}
```

---

## 作者：hgcnxn (赞：3)

## P11416 [EPXLQ2024 fall round] Simple Math Problem题解

### 思路

我们推一下式子：

$$nm=k(n-m)$$
$$kn-nm-km=0$$
$$kn-nm-km+m^2=m^2$$
$$(n-m)(k-m)=m^2$$

由于 $k$ 的值可以任意取，所以只要 $(n-m)\mid m^2$ 即可。

设 $s=n-m$，则

$$s\mid (n-s)^2$$
$$s\mid n^2-2ns+s^2$$
$$s\mid n^2$$
$$(n-m)\mid n^2$$

**所以，答案即为 $n^2$ 在 $[1,n)$ 中的因子个数！**

下面计算答案：

设 $n=\prod\limits_{i=1}^q p_i^{a_i}$，其中 $p_i$ 为质数。那么 $n^2$ 共有 $\prod\limits_{i=1}^q{(2a_i+1)}$ 个因子。其中，有一个因子为 $n$，剩下的因子可以两两配对，使每一对的乘积为 $n^2$，所以剩下的因子只有一半小于 $n$。所以答案为 $\dfrac{1}{2}(\prod\limits_{i=1}^q{(2a_i+1)}-1)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,i,ans,k,t;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		ans=1;
		for(i=2;i*i<=n;i++){
			if(n%i==0){
				k=0;
				while(n%i==0){
					k+=2;
					n/=i;
				}
				ans=ans*(k+1);
			}
		}
		if(n>1)ans*=3;//处理分解后剩下的数 
		cout<<(ans+1)/2-1<<"\n";	
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：2)

建议评黄。

设 $n-m=x$，则 $x=n-m\in(0,n)$。题目即求使 $x\mid n(n-x)$ 则 $x\mid n^2$ 的 $x$ 个数，即 $n^2$ 小于 $n$ 的因子个数。

这里会用到一个小技巧，设 $n=p_1^{a_1}p_2^{a_2}\cdots p_s^{a_s}$。则 $n^2=p_1^{2a_1}p_2^{2a_2}\cdots p_s^{2a_s}$ 共有 $\sum\limits_{i=1}^s(2a_i+1)$ 个因子，其中有一个为 $n$，其他的 $\sum\limits_{i=1}^s(2a_i+1)-1$ 个因子可以两两配对，乘积为 $n^2$，因此 $n^2$ 共有 $\dfrac{1}{2}(\sum\limits_{i=1}^s(2a_i+1)-1)$ 个小于 $n$ 的因子。将 $n$ 分解质因数，算出 $a_i$ 后直接计算即可。

---

## 作者：naught (赞：2)

[更好的阅读体验](https://www.cnblogs.com/naughty-naught/p/18470774) 

## (E)[EPXLQ2024 fall round] Simple Math Problem 题解

## 题外话

出题人题解。

~~被比赛负责人爆标了，原本的标算还被卡了。~~

## 题意

对于一个正整数 $n$，求有多少个 $m \in (0,n)$，满足 $nm$ 能被 $n-m$ 整除。

## Solution

下面所有时间复杂度中的 $d$ 表示 $d(n)$，即 $n$ 的因数个数，$V$ 表示答案；其它公式中的 $d$ 表示 $\gcd(m,n)$。

### Subtask 0

观察可得（后面会给详细证明），答案始终为 $1$，输出即可。

时间复杂度：$O(T)$。

### Subtask 1 ~ 2

枚举每个可能的 $m$，每个验证即可。

时间复杂度：$O(n)$。

### Subtask 3

先进行一些小小的推导。设 $n = dx, m = dy, gcd(x, y) = 1$，则：

$$ 

(n-m) \mid nm \\

d(x-y) \mid d^2 xy \\

(x-y) \mid dxy \\

\because gcd(x, y) = 1 \\

\therefore gcd(x, x-y) = gcd(y, x-y) = 1\\

\therefore (x-y) \mid d

$$

因此，我们要对于每个 $d \mid n$ 找到所有 $s \mid x$ 满足 $ s \in (0, {x \over d})$，$ \operatorname{Card}( \{x \in Z \mid x = ds\} )$ 就是答案。

这也可以解释为什么 **Subtask 0** 的答案是 $1$：只有 $s=1$ 可行。

因此，我们可以考虑枚举每个 $n$ 的可能因数 $d$，再二分确定哪些 $n$ 的因数能被选择，最后进行去重即可。记 $s$ 为 $n$ 的因数个数，时间复杂度与之有关。

时间复杂度：$O(T \times (\sqrt n \times d^2))$。

### Subtask 4

注意到此时可能的因数只有 $1,p,q,pq$。考虑如何找到 $p$（这样即可找到 $q$）。直接枚举 $10^7$ 内的因数并判断即可。

事实上，如果 $p \ne q$，这四个数都各自没有额外的因数，故答案就是 $4$；如果 $p=q$ 则答案为 $2$。

时间复杂度：$O(T \sqrt p)$。

### Subtask 5

注意到因数个数不会很多，但 $O(\sqrt n)$ 枚举因数的复杂度无法接受。由于 $p \le 10^6$，可以通过质数筛先筛出 $10^6$ 内的质数。

注意，此时我们不能再使用 $O(d^2)$ 的做法计算。观察到 $d,s$ 一定都是 $n$ 的因数，因此如果 $n$ 的质因数分解为 $n = p_1^{q_1} \times p_2^{q_2} \times \dots \times p_s^{q_s}$，所有可能答案 $x$ 的分解 $x=p_1^{k_1} \times p_2^{k_2} \times \dots \times p_s^{k_s}$ 一定有 $\forall i \in [1,s], k_i \le 2q_i$，同时还要满足 $x < n$。因此，我们可以考虑 DFS 搜索每个可能的 $(k_1,k_2,\dots,k_s)$ 并加以剪枝。由唯一分解定理可知，此时搜索到的 $x$ 不会重复，每个搜索到的 $x$ 均为答案。

接下来是对时间复杂度的估计。当 $d(n)$ 较大且 $p_1,p_2,\dots,p_s$ 都较小时，答案将较大，因为此时大量 $p_i$ 的乘积仍然在 $[1,n]$ 范围内的概率增大（这也是测试点 $2$ 数据的构造方式）。因此，可以通过构造数据得出，本题中可以认为 $V \le 10^6$。

时间复杂度：$O(T \times (p + V))$。

### Subtask 6

从 Subtask 4 的做法出发。我们现在只需要质因数，因此我们枚举因数时只需要枚举 $10^7$ 内的质因子，如果出现整除直接除到无法整除为止，可以证明取到的因子一定是质因子（因为合数全被除掉了）。

时间复杂度：$O(T \times (\sqrt n + V))$。事实上时间复杂度会比这个小很多，因为 $\le 10^{14}$ 的数能产生的本质不同质因子的个数是有限的。


## Code

```cpp
//written by Naught
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 it;
#define Maxn 65
#define fo(i, l, r) for (ll i = l; i <= r; ++i)
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
inline ll lread(ll x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

ll n, a[Maxn], b[Maxn];
int ans, sum;

void dfs(int cnt, ll num)
{
    if(num > n) return ; // 剪枝
    if(cnt > sum) return ++ans, void();
    it s = num;
    fo(i, 0, b[cnt])
    {
        if(s > n) break;
        dfs(cnt + 1, (ll)s);
        s *= a[cnt];
    }
}

void Init(ll n)
{
    sum = 0;
    for(int i = 2; 1ll * i * i <= n; ++i) if(n % i == 0)
    {
        a[++sum] = i, b[sum] = 0;
        while(n % i == 0) ++b[sum], n /= i; 
    }
    if(n - 1) a[++sum] = n, b[sum] = 1;
    fo(i, 1, sum) b[i] <<= 1;
}

void Solve()
{
    ans = 0;
    dfs(1, 1);
    printf("%d\n", ans-1);
}

signed main()
{
    int _ = read();
    while(_--) n = lread(), Init(n), Solve();
	return 0;
}
```

## Tips

记得开 `__int128`。

---

## 作者：GSQ0829 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P11416)

---
### 题目大意
---
需要知道有多少个 $m \in (0,n)$，能满足 $nm$ 能被 $n-m$ 整除。

---
### 题目思路
---
在看到这道题是比赛的第五题之后，我在想，是我太菜了吗，前面四题都没看懂，就第五题最简单，于是我写了一写第五题。

按照题意大概写了一个枚举法，时间复杂度太高了。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t, n, ans = 0;

signed main() {
	cin >> t;
	while (t--) {
		ans = 0;
		cin >> n;
		for(int i = 1; i <= n; i++){
			if (n * i % (n - i) == 0) ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
```
就看这数据量，$10^{14}$ ，那么大，直接就零分了。
 
但是仔细想了想之后，就会发现这题就是只因数分解而已。

所以这是我的思路：

我们设一个 $x = n - m$ ，也就是 $n$ 与 $m$ 的差。
那么就可以将 $n - m$ 化简为 $x$。
整个题目条件就变化成了 $x | n(n - x)$。
那么还可以化成 $x | n^2 - x * m$。
那么如果 $x | n^2$。
那把 $x$ 替换回 $n - m$。
算式就变成了 $(n - m) | n^2$。
这样程序里就需要求出 $n^2$ 内的质数了，后面的过程就去自己推吧（我都推二十分钟了）！


最后，根据过程就可以写出：

- 质因数分解程序
  ```cpp
  for (int i = 2; i * i <= n; i++) {
		int cnt = 0;
		while (n % i == 0) {
			n /= i;
			cnt++;
		}
	}
  ```
- 特判程序
   ```cpp
   if (n > 1) ans *= 3;// //若n大于1，则还出现了质因数，但不会大于1个
   ```
- 输出
   ```cpp
   cout << (ans - 1) / 2 << endl;// 根据推理得出
   ```
---
### code
---
最后把这些拼在一起，再将主要程序放进一个函数里，就得出了我的专属代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t, n;

int solve(int n) {
	int ans = 1;
	for (int i = 2; i * i <= n; i++) {
		int cnt = 0;
		while (n % i == 0) {
			n /= i;
			cnt++;
		}
		ans *= (2 * cnt + 1);
	}
	if (n > 1) ans *= 3;
	return (ans - 1) / 2;
}

signed main() {
	cin >> t;
	while (t--) {
		cin >> n;
		cout << solve(n) << endl;
	}
	return 0;
}

```
谁说这题差啊，这题可太棒了。

---

## 作者：RAY091016 (赞：0)

### 1. 题目解释

给出一个正整数 $n$，求使得 $(n-m)\mid nm$ 的 $m$ 的个数

### 2. 思路

推式子启动！

我们设 $t=n-m$。

故题目条件变为 $t\mid n(n-t)$。

即 $t\mid n^2-tn$。

故有 $t\mid n^2$，即 $(n-m)\mid n^2$。

由于 $m>0$，故所求即为 $n^2$ 在 $[1,n)$ 内的因数个数。

我们令 $n=\prod\limits_{i=1}p_i^{a_i}$，则 $n^2=\prod\limits_{i=1}p_i^{2a_i}$，其因数个数为 $\prod\limits_{i=1}(2a_i+1)$。

容易知道其中一个为 $n$，剩下的以 $n$ 为分界线，两两相乘后得到 $n^2$，故有一半在 $[1,n)$ 范围内。

因而答案为 $\dfrac{1}{2}(\prod\limits_{i=1}(2a_i+1)-1)$。

### 3. 代码实现

```cpp
#include<bits/stdc++.h>  
#define int long long
using namespace std;  
int t,n;
signed main(){  
    cin>>t;
    while(t--){
    	cin>>n;
    	int ans=1;
    	int x=n;
    	for(int i=2;i<=sqrt(x);i++){
    		int cnt=0;
    		while(n%i==0){
    			n/=i;
    			cnt++;
			}
			ans*=(2*cnt+1);
		}
		if(n>1){
			ans*=3;//若n不为1，则还有质因数，但不超过1个
		}
		cout<<(ans-1)/2<<endl;
	}
    return 0;  
}
```

---

