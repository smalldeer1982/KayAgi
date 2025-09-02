# Dynamic Mex Problem

## 题目背景

你对 $\text{min}\times \text{mex}$ 问题颇有研究！

## 题目描述

小 A 给你了一个数字 $n$，要求你求解 $\text{mex}$ 问题！你当然对 $\text{min}\times \text{mex}$ 问题颇有研究，决定来秒掉这道题！



定义集合 $S(A)$，$A$ 是一个序列，当且仅当以数字 $x$ 作为最小值的 $A$ 的子区间的个数为奇数时，$x$ 属于集合 $S(A)$。你需要对于每一个 $i=0,1,2,\dots,n$ 分别求出 $\text{mex}\{S(a)\}=i$ 的序列 $a$ 的数量，其中序列 $a$ 是 $0$ 到 $n-1$ 的任意一个排列。

答案可能较大，请对 $10^9+7$ 取模。


---

$\text{mex}$ 函数定义：设 $S$ 是一个非负整数集合，则 $\text{mex}(S)$ 定义为不在集合 $S$ 中的最小非负整数。用数学符号表示为：$\operatorname{mex}(S)=\min\{x\in\mathbb{N}:x\notin S\}$。


## 说明/提示

**【样例解释 $\mathbf 1$】**

可以得到，$S([1,0])=S([0,1])=\{1\}$。

* 当 $i=0$ 时，$\text{mex}\{S(a)\}=0$ 的序列 $a$ 有两种，分别是 $[0,1]$ 和 $[1,0]$。
* 当 $i=1$ 时，$\text{mex}\{S(a)\}=1$ 的序列 $a$ 不存在。
* 当 $i=2$ 时，$\text{mex}\{S(a)\}=2$ 的序列 $a$ 不存在。



---

**【数据规模与约定】**

**本题开启子任务捆绑测试**。本题自动开启 O2 优化。请注意使用较快的输出方式。



* Subtask 1（30 pts）：$n\leq 10$。
* Subtask 2（20 pts）：$n\leq 100$。
* Subtask 3（20 pts）：$n\leq 1000$。
* Subtask 4（30 pts）：$n\leq 5\times 10^6$。

对于所有测试点满足 $1\leq n\leq 5\times  10^6$。


## 样例 #1

### 输入

```
2```

### 输出

```
2
0
0```

# 题解

## 作者：_LFL_ (赞：6)

出题人题解。

### 方法思路

我们可以轻松得出以下结论：

1. **当 $n$ 是偶数时**：所有排列的 $mex$ 值都是 $0$。这是因为每个排列中以序列最小值0作为最小值的子区间数总是偶数（因为一共有 $i \times (n - i + 1)$ 个区间以序列最小值 $0$ 为最小值，而 $i$ 和 $n - i + 1$ 之中一定有一个偶数），因此 $0$ 不会出现在集合 $S(a)$ 中，$mex$ 值为 $0$，此时 $mex=0$ 的方案数为 $n!$，其他为 $0$。

2. **当 $n$ 是奇数时**：$0$ 可能出现在集合 $S(a)$ 中，也可能不出现。如果 $0$ 出现，则 $mex$ 值一定为 $1$ （就相当于把 $a$ 分为了两个长度为偶数的序列，其中有一个包含 $1$，而根据上文，此时，$1$ 一定不在 $S(a)$ 中）。如果 $0$ 不出现，则 $mex$ 值为 $0$。具体来说：

   - 当 $0$ 前面有偶数个数时，集合 $S(a)$ 的 $mex$ 值为 $1$。
   - 当 $0$ 前面有奇数个数时，集合 $S(a)$ 的 $mex$ 值为 $0$。

   此时 $mex=0$ 的方案数为$\dfrac{(n-1)}{2}\times(n-1)!$。$mex=1$ 的方案数为$\dfrac{n+1}{2}\times(n-1)!$。其他为 $0$。



```c++
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;

const int mod = 1e9 + 7;
int n;

signed main(){
	IOS;
	cin >> n;
	int ans = 1, las;
	for(int i = 1; i <= n; i++) las = ans, ans *= i, ans %= mod;
	if(n % 2 == 0){
		cout << ans << '\n';
		for(int i = 1; i <= n; i++) cout << 0 << '\n';
	}
	else{
		cout << (n - 1) / 2 * las % mod << '\n';
		cout << (n + 1) / 2 * las % mod << '\n';
		for(int i = 2; i <= n; i++) cout << 0 << '\n';
	}
	return 0;
} 
```

---

## 作者：Dream_Realizer (赞：5)

注意到：

- 当 $n$ 为偶数时，$0$ 的位置无论奇偶，其作为最小值的子区间数目总是偶数，则所有排列的 $\text {mex}$ 值均为 $0$；
- 当 $n$ 为奇数时，$\text{mex}$ 值可能为 $0$ 或 $1$（$0$ 的位置为奇数时 $\text{mex}$ 值为 $0$，位置为偶数时 $\text{mex}$ 值为 $1$）。

则只需预处理阶乘后，根据 $n$ 的奇偶性分别处理结果即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;

    vector<long long> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    if (n % 2 == 0) {
        for (int i = 0; i <= n; ++i) {
            if (i == 0) {
                cout << fact[n] << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
    } else {
        long long k = (n - 1) / 2;
        long long ans0 = k * fact[n - 1] % MOD;
        long long ans1 = (k + 1) * fact[n - 1] % MOD;
        for (int i = 0; i <= n; ++i) {
            if (i == 0) {
                cout << ans0 << '\n';
            } else if (i == 1) {
                cout << ans1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        }
    }

    return 0;
}
```

---

## 作者：Walrus (赞：4)

同学出的很好题目，作为出题人的好同学来帮帮他补充证明。

## Solution

比较好的是通过 $n\leq 10$ 的部分分加上强大的观察能力可以引导选手想到正解。

这个题打表是一个不错的方案，这里大概解释一下为什么。

考虑一个 $0\sim n-1$ 的排列 $0$ 这个数会在多少个子区间出现，如果出现了它就一定是最小值，显然，若 $0$ 位于第 $i$ 个数，根据简单的组合数学可以得到其出现次数：
$$i\times (n-i+1)$$

其含义是左端点可以在 $1\sim i$ 中选择，右端点可以在 $i\sim n$ 中选择，乘法原理计算即可。

根据观察不难发现若：
- $n\equiv 0\pmod 2$，则上述式子一定是偶数，这对答案的贡献意义是 **$0$ 这个数一定不会在集合 $S$ 中**！那么显然对于任意排列 $\operatorname{mex}\{S\}=0$，故答案当且仅当 $i=0$ 时有答案为 $n!$，其余为 $0$。
- $n\equiv 1 \pmod 2$，上述式子当且仅当 $i\equiv 0\pmod 2$ 的时候为偶数，这时候 $\operatorname{mex} \{S\}=0$，根据简单计算（或打表）可得这种情况的方案数是（$i=0$）
  $$\dfrac{n-1}{2}\times (n-1)!$$
   证明方法大概口胡一下，因为我是打表看出来的，我们考虑先把 $0$ 扣出去，这样的话**这个剩下的序列的 $\operatorname{mex}$ 一定为 $0$**，然后你考虑把 $0$ 插进去，根据上述推导，只有 $0$ 在偶数位置时这个序列的 $\operatorname{mex}$ 才为 $0$，只有 $\dfrac{n-1}{2}$ 个偶数位置，所以应该是对的吧？如果我是唐诗可以指出。
  
  然后考虑剩下的序列的 $\operatorname{mex}$ 是啥？如果不是 $0$ 的话首先考虑 $1$，一个子区间的 $\min$ 怎么才能是 $1$？显然根据官方题解说了 **$0$ 将整个序列划成了两半**，这样的话 $1$ 可能会出现在剩下的左右两部分区间里，假设 $0$ 在第 $i$ 位，考虑将 $1$ 在两边的贡献加起来，发现一定是偶数，这里我不想证了，读者可以自行证明。

  这样的话你发现 $ans_0+ans_1=n!$，所以这个序列的 $\operatorname{mex}$ 不是 $0$ 就是 $1$，考虑算出 $ans_0$ 反推出 $ans_1$。

[code](https://www.luogu.com.cn/paste/i9cgvf1g)

## 鲜花

终于写完了，给你一道拓展题目，让你练练手！

给你一个长度为 $n$ 的序列 $a$，$q$ 次询问，每次询问给定 $l,r$，求 $\min_{\forall i \in S} a_i\times \operatorname{mex}\limits_{\forall i \in S}a_i$，其中 $S$ 是 $a_l,a_{l+1}\cdots a_r$ 的集合。

不知道为啥 `operatorname` 不支持 `\limits_`？为了统一都不用了。

其中 $1\leq n,q,\forall a_i \leq 5\times 10^5$。

假定 $n,q$ 同阶。

由于作者太菜了，只会 $O(N\log N)$ 的线段树加上扫描线的做法，有更好的做法欢迎投稿作者（投稿时禁止使用暴戾语言包括但不限于唐）！

---

## 作者：_lmh_ (赞：4)

考虑 $0$ 放在哪。

假设它放在第 $i$ 个位置，那么 $0\in S(A)$ 等价于 $[2\nmid i]$ 且 $[2\nmid n-i+1]$，这样必须有 $n$ 为奇数且 $i$ 为奇数。

此时，$0$ 把这个序列分割成两个长为偶数的段，类似地讨论可以得出 $1$ 不可能属于 $A$。

这样 $n$ 为奇数时，位置 $0$ 和 $1$ 的答案分别为 $(n-1)!\frac{n-1}{2}$ 和 $(n-1)!\frac{n+1}{2}$；$n$ 为偶数时，位置 $0$ 的答案为 $n!$。其余位置输出 $0$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=5000007,MOD=1e9+7;
ll n,ans=1;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for (int i=1;i<n;++i) (ans*=i)%=MOD;
	if (n&1) cout<<((n-1)/2*ans)%MOD<<'\n'<<((n+1)/2*ans)%MOD<<'\n';
	else cout<<n*ans%MOD<<"\n0\n";
	for (int i=2;i<=n;++i) cout<<"0\n";
	return 0;
}
```

---

## 作者：lzx111218 (赞：1)

# P11742 Dynamic Mex Problem

[题目传送门](https://www.luogu.com.cn/problem/P11742)

## 思路

考虑递归。

$10^{9}+7=1000000007$。
- **阶乘计算：**

  计算 $f(n-1) = (n-1)! \bmod 1000000007$，因为这是排列的数量。

- **奇偶判断：**

  - 如果 $n$ 是偶数，$\text{mex}(S(A)) = 0$ 时的排列数量是 $n \times \text{ans} \bmod 1000000007$，其他都为 $0$。
  
  - 如果 $n$ 是奇数，$\text{mex}(S(A)) = 0$ 和 $\text{mex}(S(A)) = 1$ 时有排列数量，其他都为 $0$。

注意这几个**坑点**即可，其他地方都比较简单。

**时间复杂度为** $O(n)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MOD = 1e9 + 7;

int f(int n) {
    if (n == 0 || n == 1) return 1;
    return (n * f(n - 1)) % MOD;
}

void output(int n, int ans) {
    if (n & 1) {
        cout << ((n - 1) / 2 * ans) % MOD << '\n' << ((n + 1) / 2 * ans) % MOD << '\n';
    } else {
        cout << n * ans % MOD << "\n0\n";
    }
    for (int i = 2; i <= n; i++) {
        puts("0");
    }
}

int main() {
    int n;
    scanf("%lld", &n);
    int ans = f(n - 1);
    output(n, ans);
    return 0;
}

---

## 作者：poembelief (赞：1)

# 前言
硬控我一个小时，我讨厌推导！！！！！！
# 题意
[题目传送门](https://www.luogu.com.cn/problem/P11742)
# 分析
这题乍一眼看非常吓人，但进行推导之后就会发现它就是外强中干。

题目要求 $\text{mex}$，因此最直观的想法就是从小往大推导答案。

因为 $0$ 是最小的非负整数，因此我们考虑包含它的子区间数量——假设 $a_i=0$，则包含 $0$ 的子区间数为 $i\times (n-i+1)$。

要使子区间数量为奇数，则 $i$ 和 $n-i+1$ 都得是奇数，因此 **$n+1$ 必须为偶数，$i$ 必须为奇数**！

考虑完 $0$，再以同样的方式考虑 $1$。假设 $a_i=0,a_j=1$，则包含 $1$ 的子区间数为 $(j-i)\times (n-j+1)$。

同理可得 $n-i+1$ 必须为偶数，则 $i$ 必须为奇数，与上述条件矛盾了。

因此，只有当 $i=0/1$ 时可能有答案，分类讨论一下即可。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
/*
*/
const int N=5e6+5,mod=1e9+7,inv2=5e8+4;
int n;
long long sum[N];
long long qpow(long long x,int t){
	long long f=1ll;
	while(t){
		if(t&1) f=f*x%mod;
		x=x*x%mod;
		t>>=1;
	}
	return f;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	freopen("tx.in","r",stdin);
	scanf("%d",&n);
	sum[0]=sum[1]=1ll;
	for(int i=2;i<=n;i++) sum[i]=sum[i-1]*i%mod;
	if((n&1)==0){
		printf("%lld\n",sum[n]);
		for(int i=1;i<=n;i++) printf("0\n");
		return 0;
	}
	else{
		printf("%lld\n",sum[n-1]*(n-1)%mod*inv2%mod);
		printf("%lld\n",sum[n-1]*(n+1)%mod*inv2%mod);
		for(int i=2;i<=n;i++) printf("0\n");
	}
	return 0;
}

```

---

