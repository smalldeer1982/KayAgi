# [Algo Beat Contest 001 E] Experiments on Collatz

## 题目背景

|               Problem               | Score |                         Idea                          |                             Std                              |                      Data                       |                            Check                             |                           Solution                           |
| :---------------------------------: | :---: | :---------------------------------------------------: | :----------------------------------------------------------: | :---------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| $\text{E - Experiments on Collatz}$ | $475$ |    [joe_zxq](https://www.luogu.com.cn/user/623577)    |       [joe_zxq](https://www.luogu.com.cn/user/623577)        | [joe_zxq](https://www.luogu.com.cn/user/623577) |     [fcy20180201](https://www.luogu.com.cn/user/866154)      | [Link](https://www.luogu.com.cn/article/1bqxjjm6) by [joe_zxq](https://www.luogu.com.cn/user/623577) |

有朝一日，当星辰与智慧交相辉映，那些曾经的数学难题终将在人类不懈的探索下迎刃而解。那一刻，不仅是难题的征服，更是心灵与理性的飞跃。人类将在数学的浩瀚宇宙中，以无畏的勇气与无尽的好奇，继续前行，越走越远，于未知中播种希望，于挑战中绽放辉煌，书写属于全人类的智慧篇章。

------------

这使你充满了决心。

## 题目描述

角谷猜想由日本数学家角谷静夫提出，是指对于每一个正整数 $n$，如果它是奇数，则对它乘 $3$ 再加 $1$，如果它是偶数，则对它除以 $2$，如此循环，最终都能够得到 $1$，故又称为 $3n+1$ 猜想。

如 $n = 6$，根据上述操作，得出 $6 \to 3 \to 10 \to 5 \to 16 \to 8 \to 4 \to 2 \to 1$。

小 Z 对这个猜想十分感兴趣，因为如此简单易懂的猜想却从来无人证明，也无人推翻。于是他决定开始研究这个问题。

定义 $f(n)$ 表示正整数 $n$ 变为 $1$ 需要的操作次数，例如 $f(6)=8$。保证在 $1 \sim 10^7$ 的范围内，角谷猜想是正确的。

形象地说，$f(n)$ 的计算步骤如下图所示：

![](https://pic.imgdb.cn/item/6697b7d8d9c307b7e96ddbbf.png)

小 Z 的计算能力很差，于是想让你帮他进行计算。他将会对你进行 $Q$ 次询问，类型为 $t \in \{1,2\}$：

- 若 $t=1$，读入整数 $x$，请你求出最小的 $y$，使得 $f(y) \ge x$。
- 若 $t=2$，读入正整数 $l$ 和 $r$，请你求 $ \prod\limits_{i=l}^{r} f(i) \bmod 1145141923$。
- 若 $t=3$，请你判断角谷猜想是否是正确的。当然啦，小 Z 知道这个问题对于你太难了，所以不存在这样的询问。但是聪明的你能解决这个数学难题吗？

## 说明/提示

#### 样例解释 #1

如表所示，是 $1 \le n \le 6$ 的 $f(n)$ 的值。

|  函数  | 函数值 |
| :----: | :----: |
| $f(1)$ |  $0$   |
| $f(2)$ |  $1$   |
| $f(3)$ |  $7$   |
| $f(4)$ |  $2$   |
| $f(5)$ |  $5$   |
| $f(6)$ |  $8$   |

对于第一次询问，$f(2) \ge 1$，可以证明没有 $y < 2$ 使得 $f(y) \ge 1$。

对于第二次询问，$f(3) \ge 2$，可以证明没有 $y < 3$ 使得 $f(y) \ge 2$。

对于第三次询问，$f(3) \ge 7$，可以证明没有 $y < 3$ 使得 $f(y) \ge 7$。

对于第四次询问，$f(6) \ge 8$，可以证明没有 $y < 6$ 使得 $f(y) \ge 8$。

对于第五次询问，$f(2) \times f(3) \times f(4) = 1 \times 7 \times 2 = 14$。

#### 样例解释 #2

对于 $t=2$ 的询问，注意对 $1145141923$ 取模。

#### 数据范围

对于 $100\%$ 的数据，保证 $1 \le Q \le 10^6$。对于每次询问，$t \in \{1,2\}$。对于每次 $t=1$ 的询问，$0 \le x \le 685$。对于每次 $t=2$ 的询问，$1 \le l \le r \le 10^7$。

#### 提示

请使用较快的读写方式。

## 样例 #1

### 输入

```
5
1 1
1 2
1 7
1 8
2 2 4```

### 输出

```
2
3
3
6
14```

## 样例 #2

### 输入

```
3
1 114
1 514
2 114514 1919810```

### 输出

```
73
837799
248276873```

# 题解

## 作者：_O_v_O_ (赞：4)

乐，这种题咋还能被出出来的。

哦原来是仿 **abc** 的比赛啊，那正常了。

建议喜欢角谷猜想就去研究角谷猜想，别把角谷猜想出成一道烂题。

我们注意到可以用记忆化来预处理出 $f(1)\sim f(10^7)$。

那么这样就巨简单了：

- $t=1$：设 $ans_i$ 为 $i$ 的答案，那么初始令 $g_i=\min_{j=1}^{10^7}\{f(j)[f(j)=i]\}$，然后直接令 $ans_i=\max_{j=i}^{10^7} g_j$，后缀和一遍就行了。
- $t=2$：前缀积，令 $h_i=\prod_{j=2}^i f(j)$，那么答案为 $\frac{h_r}{h_l}$，逆元求一下即可，记得特判 $l=1$ 的情况。

---

## 作者：joe_zxq (赞：3)

出题人确实对角谷猜想很感兴趣呢。希望总有一天这个数学谜题被解开。

---

# Part 1 - 预处理函数值

首先，可以很容易用递归暴力一一求解出所有的函数值，但是这样的效率显然很低，因为相同的函数值可能会在求解过程中被计算多次。

于是考虑记忆化剪枝优化。对于小于等于 $x \le 10^7$ 的 $f(x)$ 可以记忆化，用数组存储。那对于一些计算过程中出现的 $x$ 很大的函数值的该怎么办呢？注意到这类的 $x$ 出现次数较少，不会太多地被重复计算，于是可以直接暴力解决。

以上可以在一秒内处理。

# Part 2 - 第一种询问

这个非常简单啦，直接进行预处理即可。

# Part 3 - 第二种询问

这个可以考虑预处理前缀积，令 $P_x$ 表示 $ \prod\limits_{i=1}^{x} f(i)$，则 $ \prod\limits_{i=l}^{r} f(i)=\frac{P_r}{P_{l-1}}$。由于需要取模，根据费马小定理，改除法为乘逆元即可。

# Part 4 - Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int q, dp[10000005], ans[10000005];
ll pre[10000005], mn = 2e9;
const int mod = 1145141923;

ll qp(ll x, ll y) {
	if (y == 0) {
		return 1;
	}
	ll res = qp(x, y / 2);
	res *= res;
	res %= mod;
	if (y % 2) {
		res *= x;
		res %= mod;
	}
	return res;
}

int f(long long x) {
	if (x == 1) {
		return dp[x] = 0;
	}
    if (x <= 10000000 && dp[x]) {
        return dp[x];
    }
	if (x % 2 == 0) {
		ll res = f(x / 2) + 1;
		if (x <= 10000000) {
			dp[x] = res;
		}
		return res;
	} else {
		ll res = f(x * 3 + 1) + 1;
		if (x <= 10000000) {
			dp[x] = res;
		}
		return res;
	}
}

int inv(int x) {
	return qp(x, mod - 2);
}

int main() {

	ans[0] = 1;
	pre[0] = pre[1] = 1;
	for (int i = 1; i <= 10000001; i++) {
        dp[i] = f(i);
        ans[i] = 2e9; 
        if (i != 1) {
        	pre[i] = pre[i - 1] * dp[i];
        	pre[i] %= mod;
		}
	}
	for (int i = 1; i <= 10000000; i++) {
		ans[dp[i]] = min(ans[dp[i]], i);
	}
	for (int i = 10000000; i >= 0; i--) {
		ans[i] = min(ans[i], ans[i + 1]);
	}
	cin >> q;
	for (int i = 1, t, x, y; i <= q; i++) {
		cin >> t;
		if (t == 1) {
			cin >> x;
			cout << ans[x] << endl;
		} else {
			cin >> x >> y;
			if (x == 1) {
				cout << 0 << endl;
			} else {
				cout << pre[y] * inv(pre[x - 1]) % mod << endl;
			}
		}
	}

	return 0;
}
```

---

## 作者：yedalong (赞：2)

一堆模板的组合体。

## Solution

这道题目，我们可以先计算出 $f$ 数组，可是要计算到 $10^7$，早就超时了。那咋办呢？我们可以用上**十分模板的记忆化搜索**，搜索时如果当前数字的操作次数已经计算过，就没必要继续递归下去了，直接将当前数字的操作次数返回即可。对于大于 $10^7$ 的部分，由于没用，我们可以不用数组存，到这一步我们直接递归下去即可，不做记忆化。\
于是这一部分的实现就十分简单了，代码如下：

```cpp
//记忆化搜索函数
int dfs(int now){
    if(now<=1e7&&f[now]) return f[now];
    if(now%2){
        if(now<=1e7) return f[now]=dfs(now*3+1)+1;
        else return dfs(now*3+1)+1;
    }
    else{
        if(now<=1e7) return f[now]=dfs(now/2)+1;
        else return dfs(now/2)+1;
    }
}
//主函数内的基本操作
f[2]=1;
for(int i = 3;i<=10000000;i++) if(!f[i]) dfs(i);
```

接下来，我们考虑 $t=1$ 时如何快速找到解。很容易想到，可以使用二分，但是 $f$ 数组并不满足单调性，那咋办？既然它不满足单调性，那我们把它整成满足单调性的不就好了吗？我们可以再使用一个数组 $ff$，专门用来处理 $f$ 数组的。对于 $ff_i$ 我们可以令 $ff_i=\max(ff_{i-1},f_i)$，这样做出来的 $ff$ 数组就满足单调性了，这样做不影响答案的原因很简单，大家可以停下来思考一下。\
然后我们可以再做一个预处理，只需要用一个**十分模板的二分**实现即可，这里就直接用函数了。。。

```cpp
//计算 ff 数组
for(int i = 1;i<=10000000;i++) ff[i]=max(ff[i-1],f[i]);
//预处理答案
for(int i = 0;i<=685;i++) ans[i]=lower_bound(ff+1,ff+1+10000000,i)-ff;
//直接输出
if(opt==1) cin>>x,cout<<ans[x]<<'\n';
```

接下来处理 $t=2$ 的情况，观察到这玩意就是**十分模板的前缀积**，按照前缀和的思路，还得用到除法，这又涉及到了**十分模板的乘法逆元**，直接用费马小定理解决即可，这里的费马小定理又要用到**十分模板的快速幂**。\
这一部分代码如下：

```cpp
//快速幂模板
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
//前缀积
for(int i = 2;i<=10000000;i++) qzj[i]=qzj[i-1]*f[i]%mod;
//输出答案
if(opt==2) cin>>l>>r,cout<<qzj[r]*qpow(qzj[l-1],mod-2)%mod<<'\n';
```

## AC code

将这一堆代码结合起来，就能得到这一道题的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1145141923;
int Q,opt,x,l,r,f[10000005],ff[10000005],ans[686],qzj[10000005];
int dfs(int now){
    if(now<=1e7&&f[now]) return f[now];
    if(now%2){
        if(now<=1e7) return f[now]=dfs(now*3+1)+1;
        else return dfs(now*3+1)+1;
    }
    else{
        if(now<=1e7) return f[now]=dfs(now/2)+1;
        else return dfs(now/2)+1;
    }
}
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=res*a%mod;
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    f[2]=1,qzj[1]=1;
    for(int i = 3;i<=10000000;i++) if(!f[i]) dfs(i);
    for(int i = 1;i<=10000000;i++) ff[i]=max(ff[i-1],f[i]);
    for(int i = 0;i<=685;i++) ans[i]=lower_bound(ff+1,ff+1+10000000,i)-ff;
    for(int i = 2;i<=10000000;i++) qzj[i]=qzj[i-1]*f[i]%mod;
    cin>>Q;
    while(Q--){
        cin>>opt;
        if(opt==1) cin>>x,cout<<ans[x]<<'\n';
        if(opt==2) cin>>l>>r,cout<<qzj[r]*qpow(qzj[l-1],mod-2)%mod<<'\n';
    }
}
```

## Example

最后将涉及到本题的模板题亮出来 ~~（特别水的）~~\
[P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)\
[P1464 Function（记忆化搜索）](https://www.luogu.com.cn/problem/P1464)\
[P2249 【深基 13. 例 1】查找（二分）](https://www.luogu.com.cn/problem/P2249)\
[B3612 【深进 1. 例 1】求区间和（前缀和）](https://www.luogu.com.cn/problem/B3612)\
[P3811 【模板】模意义下的乘法逆元](https://www.luogu.com.cn/problem/P3811)

---

## 作者：_Tea (赞：2)

## 最优解
~~[目前最优解](https://www.luogu.com.cn/record/list?pid=P11683&orderBy=1&status=&page=1)~~


## 废话
~~为什么赶脚E比D简单？~~


## 分析
(下面设 $ N = 10^7 $ , $ Q = 10^6 $ )   
**预处理**出 $ f(i) $ , $ s(i) $ 代表 $ f(i) $ 的前缀积，时间复杂度 $ O(N)$   
对于**第一类**询问，我们额外用一个数组 $mf$ 处理出 $ f(1) \thicksim f(i)$ 的最大值 ， 然后**二分查找**，单次查询复杂度 $ O(\log N)$    
对于**第二类**询问，我们直接计算 $ s(r) \div s(l - 1) $ 的**逆元** $  s(r) \times inv_{s(l - 1)} $ ，单次查询复杂度 $ O(\log mod)$  
总和复杂度 $ O(N + Q \log mod )$ 可以通过

剩余细节都在代码中了↓
## CODE ~
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rint register int
#define F(i, x, y) for (rint i = (x); i <= (y); i++)
#define int long long
const int N = 1e7+10 , mod = 1145141923;
int n;
int f[N],s[N];

int rd()
{
    int x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = - 1;
    for (; isdigit(c); c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x *= f;
}

void pt(int x)
{
	if(x < 0)putchar('-'),x = -x;
	if(x <= 9)putchar(x + '0');
	else
	{
		pt(x / 10);
		putchar(x % 10 + '0');
	}
}

int calc(int x) // 计算 f(x)
{
	int n = x,cnt = 0;
	while(x>=n)
	{
		if(x & 1)x = (x << 1) + x + 1;
		else x = x >> 1;  // 卡常就是优化了这里
		cnt++;
	}
	return f[x] + cnt; // x < n （即原来的x）直接记忆化
}

int qmi(int a,int k)
{
	int ans=1;
	while(k)
	{
		if(k & 1)ans = (ans * a) % mod;
		a=(a * a) % mod;
		k >>= 1;
	}
	return ans;
}

void init() // 预处理 f(i) , s(i)  
{
	f[1] = 0 , f[2] = 1; 
	s[1] = 1 ,s[2] = 1;
	F(i,3,N-10)
	{
		f[i] = calc(i);
		s[i] = (s[i-1] * f[i]) % mod ;
	}
	F(i,2,N-10) // 为了节约空间 直接 将f(i) 变为 max( f(1,2...i) ) 
		f[i] = max(f[i-1],f[i]);
}

signed main()
{
	init();
	
	int T;T=rd();
	while(T--)
	{
		int op;
		op=rd();
		if(op==1)
		{
			int x;x=rd();
			int y = lower_bound(f+1,f+N,x) - f; // 二分查找 
			pt(y);puts("");
		}
		else
		{
			int l,r;l=rd(),r=rd();
			pt(s[r]*qmi(s[l-1],mod-2)%mod);puts("");  // f(l)*...f(r) = s[r] / s[l-1]  
		}
	}
	return 0;
}
```
**Update**：2025.2.7 优化代码，增加了“**最优解**”板块

---

## 作者：nightwatch.ryan (赞：2)

### Analysis
对于 $1 \leq n \leq 10^7$，可以通过记忆化搜索求出在时限内求出所有 $f(n)$ 的值。

对于操作 $1$，预处理出所有答案即可。

对于操作 $2$，可以考虑前缀积。记 $S_i$ 为 $(f(1) \times f(2) \times \dots f(i)) \bmod 1145141923$ 的值。对于 $\prod\limits_{i=l}^{r} f(i) \bmod 1145141923$ 这个式子，可以通过 $\dfrac{S_r}{S_{l-1}} \bmod 1145141923$ 来计算得到。注意不能直接除以 $S_{l-1}$，我们可以通过乘以 $S_{l-1}$ 在模 $1145141923$ 意义下的逆元来计算。这也是本题的难点。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int V = 1e7, N = V + 5;
const int mod = 1145141923;
int dp[N], ans[N]; ll pre[N];
ll qpow(ll x, ll y){
    ll result = 1;
    while(y){
        if(y & 1) result = (result * x) % mod;
        x = (x * x) % mod, y >>= 1;
    }
    return result;
}
ll inv(ll x){ return qpow(x, mod - 2); }
ll f(ll x){
    if(x == 1) return dp[x] = 0;
    if(x <= V && dp[x]) return dp[x];
    if(x % 2 == 1){
        ll result = f(x * 3 + 1) + 1;
        if(x <= V) dp[x] = result;
        return result;
    }
    ll result = f(x / 2) + 1;
    if(x <= V) dp[x] = result;
    return result;
}
int main(){
    cin.tie(0) -> sync_with_stdio(0);
    pre[0] = pre[1] = 1, ans[0] = 1;
    for(int i = 1; i <= V + 1; i ++){
        dp[i] = f(i), ans[i] = INT_MAX;
        if(i != 1) (pre[i] = pre[i - 1] * dp[i]) %= mod;
    }
    for(int i = 1; i <= V; i ++) ans[dp[i]] = min(ans[dp[i]], i);
    for(int i = V; i >= 1; i --) ans[i] = min(ans[i], ans[i + 1]);
    int q; cin >> q;
    while(q--){
        int op; cin >> op;
        if(op == 1){
            int x; cin >> x;
            cout << ans[x] << "\n";
        }else{
            int l, r; cin >> l >> r;
            if(l == 1) cout << 0 << "\n";
            else cout << pre[r] * inv(pre[l - 1]) % mod << "\n";
        }
    }
}
```

---

## 作者：wangliu (赞：1)

# 题目思路

题意已经很明确，这里不过多阐释。

可以开两个数组 $f$ 和 $mul$，其中 $f_i$ 用于预处理 $1 \sim i$ 的操作数的最大值，这个过程可以记忆化降低时间复杂度，而 $mul_i$ 预处理 $1 \sim i$ 的操作数的积。

记忆化代码如下：
```cpp
int dfs(int x){
	int y=x,tot=0;
	while(y>=x){//对于小于x的操作数是已知的，故当y<x时得到答案
		if(y&1) y=y*3+1;
		else y>>=1;
		tot++;
	}
	return f[y]+tot;
}
```

然后分别处理两种询问。

- 若 $t=1$，直接二分查找答案，可以使用 $\operatorname{lower\_bound}$ 得到答案。

- 若 $t=2$，答案即为 $\frac{mul_r}{mul_{l-1}}$。但是直接除是错误的，因为 $mul$ 里面的操作数都是取模后的结果，需要计算乘法逆元 ~~蒟蒻在这里卡住了，然后发现需要用性质~~。因为模数为素数，可以直接用费马小定理。

  $$ b^{p-1} \equiv 1\pmod p $$

  $$ b\times b^{p-2} \equiv 1\pmod p $$

  这里需要引入一个概念 **逆元**：对于 $ab \equiv 1\pmod p$，且 $\gcd(a,p)=1 (a\perp p)$，$b$ 即为 $a$ 关于 $p$ 的乘法逆元。因此，$\frac{a}{b}=a\times b^{p-2} \bmod p$。

代码如下：
```cpp
int qpow(int x,int mi){//快速幂模板
	int res=1;
	while(mi){
		if(mi&1) res=(res*x)%mod;
		x=(x*x)%mod;
		mi>>=1;
	}
	return res%mod;
}

while(T--){
		int op;cin>>op;
		if(op==1){
			int x,ans=1;
            cin>>x;
			ans=lower_bound(maxn+1,maxn+sbCCF,x)-maxn;
			printf("%lld\n",ans);
		}
		else{
			int l,r,ans;
            cin>>l>>r;
			if(l==1) ans=0;//特判
			else ans=(mul[r]*qpow(mul[l-1],mod-2)*1LL)%mod;//费马小定理
			printf("%lld\n",ans);
		}
	}
```

然后就能愉快 AC 了。[link](https://www.luogu.com.cn/record/211731167)

一道不错的题目，融合了挺多模板，拿来练手正好。

---

## 作者：xplor (赞：1)

## 思路

先用类似于记忆化搜索的方法求出 $f_i$ 
接着分类求解问题。

当 $t = 1$ 时

我们考虑使用二分，先将 $f$ 处理成递增的序列，使用 lower_bound 求出第一个 $f_i \ge x$ 的 $i$ 即为答案。

当 $t = 2$ 时

先用 $s$ 数组求出 $f$ 的前缀积，那么答案为 $s_r \div s_{l - 1}$ 即 $s_r \times s_{l - 1}^ {-1} \bmod 1145141923$ 因为 $1145141923$ 为质数，所以直接使用费马小定理求解逆元即可。

## code

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const LL N = 1e7 + 10, mod = 1145141923;
LL f[N], s[N];
LL get_val (LL x) {
	LL res = 0;
	while (x > 1) {
		if (x <= 10000000 && f[x]) {
			return (res + f[x]);
		}
		res ++ ;
		if (x % 2 == 0) x /= 2;
		else x = x * 3 + 1;
	}	
	return res;
}

LL qpow (LL a, LL b) {
	LL res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return res;
}

LL inv (LL x) {
	return qpow(x, (LL)(mod - 2));
}
int main () {
	s[1] = 1;
	for (LL i = 2; i <= 10000000; i ++ ) {
		f[i] = get_val (i);
		s[i] = s[i - 1] * f[i] % mod;
	}
	for (LL i = 1; i <= 10000000; i ++ ) {
        if (f[i] < f[i - 1]) f[i] = f[i - 1];
    }
	int T;
	scanf ("%d", &T);
	while (T -- ) {
		int op;
		scanf ("%d", &op);
		if (op == 1) {
			LL x;
			scanf ("%lld", &x);
			printf ("%lld\n", lower_bound (f + 1, f + 1 + 10000000, x) - f);		
		} else {
			LL l, r;
			scanf ("%lld%lld", &l, &r);
			printf ("%lld\n", s[r] * inv(s[l - 1]) % mod);
		}
	}	
	return 0;
}
```

---

## 作者：Milthm (赞：1)

最后 30min 的时候进去的，做了这一个题就走了，感觉很忍俊不禁。

首先看到询问 $2$ 的范围是 $10^7$，考虑直接把 $10^7$ 以内打表出来。打表的过程可以采用记忆化，如果这个位置是 $10^7$ 以内就用数组存一下，这样可以省去很多步骤。

通过打表我们发现 $10^7$ 以内的最大 $f$ 值已经到达了询问一的 $685$，且打表中途涉及到的最大数也没有超过 $10^{18}$ 范围，而且打表速度还很快。

所以我们第一个询问预处理出来 $686$ 个答案，第二个询问预处理前缀积即可。算的时候需要算逆元。

打表复杂度不知道（反正能过，大概是 $O(n)$ 多一些？），预处理复杂度 $O(n)$，询问复杂度 $O(q\log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 10000005
using namespace std;
signed q,g[N],ans[700],mul[N],ff[N];
const int mod=1145141923;
int f(int x){
	if(x<=1e7&&(ff[x]||x==1))return ff[x];
	if(x%2){
		if(x<=1e7)return ff[x]=f(x*3+1)+1;
		else return f(x*3+1)+1;
	}
	else{
		if(x<=1e7)return ff[x]=f(x/2)+1;
		return f(x/2)+1;
	}
}
int qpow(int x,int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;y>>=1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ff[1]=0;mul[1]=1;
	for(int i=2;i<=1e7;++i)f(i),g[i]=max(g[i-1],ff[i]),mul[i]=1ll*mul[i-1]*ff[i]%mod;int n=1e7;
	for(int i=0;i<=685;++i)ans[i]=lower_bound(g+1,g+n+1,i)-g;
	cin>>q;
	while(q--){
		int op,x,l,r;
		cin>>op;
		if(op==1)cin>>x,cout<<ans[x]<<"\n";
		else{
			cin>>l>>r;
			if(l==1)cout<<"0\n";
			else cout<<mul[r]*qpow(mul[l-1],mod-2)%mod<<'\n';
		}
	}
	return 0;
}

```

---

## 作者：ARIS2_0 (赞：1)

### 思路

我们可以用记忆化搜索 $O(T)$ 地求出 $1\le x\le T$ 的 $f(x)$，其中 $T=10^7$。

但是有一个问题：记忆化搜索的时候，如果遇到一个很大的奇数，这个奇数乘 $3$ 再加 $1$ 是会超过 $10^7$ 的。那么，我们记忆化搜索时，如果有 $x$ 是奇数且 $3\times x+1>10^7$，我们直接暴力求出 $f(x)$ 的值，否则继续搜索。

这个复杂度比较玄学，但开了 O2 跑的还挺快，欢迎证明。

求出所有的 $f(x)$ 后，问题就显得简单许多了：

对于询问 $1$，我们维护一个 $mins_{i}$ 表示满足 $f(x)\ge i$ 的最小 $x$，初始值为 $\inf$。实现上，我们先对于 $\forall 1\le i\le 10^7,mins_{f_i}=\min(mins_{f_i},i)$，然后再对于 $0\le x\le 685,mins_x=\min\limits_{i=x}^{685}mins_i$ 即可。

对于询问 $2$，我们维护 $s_i=\prod\limits_{j=2}^if(j)\bmod 1145141923$，因为 $1145141923$ 是质数，所以在 $10^7$ 范围内所有 $s_i$ 都不为 $0$。

询问时，特判 $l=1$（输出 $0$）与 $l=2$（输出 $s_r$），其他情况输出 $s_r\times \operatorname{inv}(s_{l-1})\bmod 1145141923$，其中 $\operatorname{inv}(x)$ 为 $x$ 在模 $1145141923$ 意义下的逆元，即 $x^{1145141921}$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define debug1(x) cerr<<#x<<"="<<x<<" "
#define debug2(x) cerr<<#x<<"="<<x<<"\n"
const int inf=1e16,maxn=1e7+10,mod=1145141923;
int f[maxn],s[maxn],mins[700];
int kpow(int a,int b){
    if(!b)return 1;
    int t=kpow(a,b/2);
    (t*=t)%=mod;
    if(b&1)(t*=a)%=mod;
    return t;
}
int inv(int x){return kpow(x,mod-2);}
int bf(int x){
    int cnt=0;
    while(x!=1){
        cnt++;
        if(x&1)x=x*3+1;
        else x/=2;
    }
    return cnt;
}
int check(int x){
    if(f[x]!=-1)return f[x];
    if(x&1){
        if(3*x+1>(int)(1e7))return f[x]=bf(x);
        return f[x]=check(x*3+1)+1;
    }
    return f[x]=check(x/2)+1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(f,-1,sizeof(f));
    f[1]=0;
    for(int i=2;i<=1e7;i++)f[i]=check(i);
    // for(int i=1;i<=10;i++)debug1(f[i]);
    // debug2("");
    s[2]=f[2];
    for(int i=3;i<=1e7;i++)s[i]=s[i-1]*f[i]%mod;
    for(int i=0;i<=685;i++)mins[i]=inf;
    for(int i=1;i<=1e7;i++){
        if(mins[f[i]]==inf)mins[f[i]]=i;
    }
    for(int i=684;i>=0;i--)mins[i]=min(mins[i],mins[i+1]);
    int q;cin>>q;
    while(q--){
        int op;cin>>op;
        if(op==1){
            int x;cin>>x;
            cout<<mins[x]<<"\n";
        }
        else{
            int l,r;cin>>l>>r;
            if(l==1)cout<<"0\n";
            else if(l==2)cout<<s[r]<<"\n";
            else cout<<s[r]*inv(s[l-1])%mod<<"\n";
        }
    }
	return 0;
}
/*
g++ -std=c++14 -Wall -Wextra -Wshadow -Wconversion -Wl,--stack=512000000
*/

```

---

## 作者：Hy13_xsm (赞：0)

## 题目大意

这道题大概可以分成两个版块。

1. 给定一个数 $x$，求一个最小的整数，这个数满足通过角谷猜想进行**不少于** $x$ 次变化过后变成 $1$。
2. 令 $f(i)$ 为 $i$ 通过角谷猜想进行变换使它变为 $1$ 需要的步数，给定 $l$ 和 $r$，求出 $[l,r]$ 区间内所有整数 $i$ 所对应的 $f(i)$ 的乘积对 $1145141923$ 取模。

## Solution

1. 初始化 $f(i)$ 数组，数组大小开到 $10^7$。然后从左到右扫一遍，求出前缀最大值。按照第一版块的要求，接下来需要找出第一个大于 $x$ 的 $f(i)$ 的位置，这个位置就代表了我们找的那个数。
2. 很容易想到前缀和，只不过换一种用法，变成乘积形式。考虑到前缀和的过程中有取模操作，而且前缀和求值的表达式是 `s[r]/s[l-1]`，其中有除法的参与，所以必须使用乘法逆元。表达式就换成了乘法形式 `s[r]*inv(s[l-1])`。

具体还是看代码操作。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define N 10000005
#define int long long
#define mod 1145141923
using namespace std;
int t,f[N],s[N],h[N];
int cal(int x)
{
	int rel=0;
	while(x>1)
	{
		if(x<=N&&f[x])return rel+f[x];
		if(x%2)x=x*3+1;
		else x/=2;
		rel++;
	}return rel;
}
int ksm(int x,int y)
{
	if(y==0)return 1;
	int k=ksm(x,y/2);
	if(y&1)return k*k%mod*x%mod;
	return k*k%mod;
}
int inv(int x){
	return ksm(x,mod-2);
}//费马小定理的求法
signed main()
{
	cin>>t;
	s[1]=1;
	for(int i=2;i<=N-5;i++)
	{
		f[i]=cal(i);
		s[i]=s[i-1]*f[i]%mod;
	}
	for(int i=1;i<N-5;i++)
	{
		if(f[i]<f[i-1])
			f[i]=f[i-1];
	}
	while(t--)
	{
		int op,x,l,r;
		scanf("%lld",&op);
		if(op==1)
		{
			scanf("%lld",&x);
			printf("%lld\n",lower_bound(f+1,f+N-4,x)-f);//家喻户晓的二分函数
		}else{
			cin>>l>>r;
			printf("%lld\n",s[r]*inv(s[l-1])%mod);//乘法逆元
		}
	}
	return 0;
}
```

---

## 作者：ylch (赞：0)

不难想到先用记忆化搜索预处理出所有 $f(x)$ 的值，前提是 $x \le 10^7$。对于 $x>10^7$ 的情况需要递归求值，但不用记录到数组中。（$x$ 别忘了开 long long）

对于操作一，看样子像二分查找。但发现 $f(x)$ 不具有单调性，考虑预处理一个前缀最大值数组 $Mx$，这样就有单调性了。

对于操作二，考虑预处理出所有 $f(x)$ 的前缀积数组 $s$，在询问 $[l,r]$ 时的答案即为 $s_r \div s_{l-1}$。因为取模，所以要用逆元。

注意 $x$ 的范围最大到 $10^7$，开 long long 数组可能空间不够，只能开 int 数组。

这道题的难点：
1. 对第一个位置的处理（见预处理部分的注释）。
2. 因为 $0$ 的特殊性，预处理时无法一并处理。询问 $0$ 时的答案要特判（见代码里询问的两个特判）。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e7 + 7;
const int mod = 1145141923;

int f[maxn], Mx[maxn], s[maxn];

int dfs(ll x){
    if(x == 1) return 0;
    if(x <= 1e7 && f[x]) return f[x];
    if(x % 2 == 0){
        ll tmp = dfs(x / 2) + 1;
        if(x <= 1e7) f[x] = tmp;
        return tmp;
    }
    else{
        ll tmp = dfs(x * 3 + 1) + 1;
        if(x <= 1e7) f[x] = tmp;
        return tmp;
    }
}

ll Pow(ll x, ll y){
    if(y == 0) return 1;
    if(y == 1) return x % mod;
    ll sq = Pow(x, y / 2);
    if(y & 1){
        return sq * sq % mod * x % mod;
    }
    return sq * sq % mod;
}

void solve()
{
    int n = 1e7;
    s[1] = 1, f[1] = 0; // 因为s[1]=0的话后面全是0，而f[1]=0，所以预处理第一个位置
    for(int i = 2; i <= n; i ++){
        f[i] = dfs(i);
        Mx[i] = max(Mx[i - 1], f[i]);
        s[i] = 1LL * s[i - 1] * f[i] % mod;
    }
    int Q;
    for(cin >> Q; Q --; ){
        int t; cin >> t;
        if(t == 1){
            int x; cin >> x;
            if(x == 0) cout << 1 << '\n'; // 特判一下
            else cout << lower_bound(Mx + 1, Mx + n + 1, x) - Mx << '\n';
        }
        else{
            int l, r; cin >> l >> r;
            if(l == 1) cout << 0 << '\n'; // 特判一下
            else cout << 1LL * s[r] * Pow(s[l - 1], mod - 2) % mod << '\n';
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}

```

---

