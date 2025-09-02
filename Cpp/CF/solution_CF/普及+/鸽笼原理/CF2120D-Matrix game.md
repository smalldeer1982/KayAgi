# Matrix game

## 题目描述

Aryan 和 Harshith 玩一个游戏。他们都从三个整数 $a$、$b$ 和 $k$ 开始。然后 Aryan 给 Harshith 两个整数 $n$ 和 $m$。接着，Harshith 给 Aryan 一个 $n$ 行 $m$ 列的矩阵 $X$，其中 $X$ 的每个元素都在 $1$ 到 $k$（包含 $k$）之间。之后，如果 Aryan 能在 $X$ 中找到一个 $a$ 行 $b$ 列的子矩阵 $Y$，且 $Y$ 的所有元素都相等，则 Aryan 获胜。

例如，当 $a=2$，$b=2$，$k=6$，$n=3$ 且 $m=3$ 时，如果 Harshith 给 Aryan 如下矩阵，则 Aryan 获胜，因为其中存在一个所有元素都为 $1$ 的 $2\times 2$ 子矩阵，如下所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120D/ff9ee31dfc04aa73a7daca458dede1d4462758ef.png)

Aryan 给你 $a$、$b$ 和 $k$ 的值。他让你帮他找到字典序最小的二元组 $(n, m)$，使得无论 Harshith 如何选择矩阵 $X$，Aryan 都能获胜。请帮助 Aryan 赢得游戏。假设 Harshith 总是最优地选择矩阵。$n$ 和 $m$ 的值可能很大，请输出它们对 $10^9+7$ 取模后的结果。

一个二元组 $(n_1, m_1)$ 被认为比 $(n_2, m_2)$ 字典序更小，当且仅当 $n_1 < n_2$，或者 $n_1 = n_2$ 且 $m_1 < m_2$。

$^*$ 矩阵的子矩阵是通过从原矩阵中去除若干行和/或列得到的。

## 说明/提示

对于第一个测试用例，任意 $n\times m$ 的矩阵都包含一个 $1\times 1$ 的所有元素相等的子矩阵。$(1,1)$ 是所有可能二元组中字典序最小的。

对于第二个测试用例，可以验证，无论 Harshith 如何选择 $3\times 7$ 的矩阵，Aryan 总能找到一个 $2\times 2$ 的所有元素相等的子矩阵。$(3,7)$ 也是所有可能二元组中字典序最小的。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 1 5
2 2 2
90000 80000 70000```

### 输出

```
1 1
3 7
299929959 603196135```

# 题解

## 作者：_O_v_O_ (赞：6)

赛时唐了，看到组合数不会算了。

先考虑 $n$。

根据鸽笼原理，每列中至少应有一种数出现 $a$ 次。

那么很显然，$n$ 最少为 $k\times(a-1)+1$。

再考虑 $m$。

设 $x$ 为每列中能出现的不同方案数，很显然 $x={n\choose a}\times k$。这个组合是可以暴力算的。

根据鸽笼原理，这个矩阵中最少要有一种方案出现了 $b$ 次，那么 $m=x\times (b-1)+1$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7;
int a,b,k;
int n,m; 

int fp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
} 
int inv(int x){
	return fp(x,mod-2)%mod;
}

int calc(int x,int y){
	int res=1;
	for(int i=1;i<=y;i++) (res*=inv(i)*((n-i+1+mod))%mod)%=mod;
	return res;
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int T;cin>>T;while(T--){
		cin>>a>>b>>k;
		n=(a-1)*k+1;n%=mod;
		m=calc(n,a);m=m*k%mod*(b-1)%mod+1;m%=mod;
		cout<<n<<' '<<m<<endl;
	}
	return 0;
}

```

---

## 作者：w9095 (赞：4)

[CF2120D Matrix game](https://www.luogu.com.cn/problem/CF2120D)

我不理解为什么两篇题解关键的地方都直接用显然和简单计算带过了，看来我水平过于低下已经无法理解大佬在说什么了。

字典序要求 $n$ 最小，所以考虑最小化 $n$。由于获胜需要的子矩阵中每一行有 $a$ 个相同元素，根据鸽笼原理，有 $k$ 种取值的元素中出现 $a$ 个相同的元素至少需要 $k(a-1)+1$。

这是 $n$ 的下界，如果此时存在 $m$ 满足题设条件，证明 $n$ 可以取到 $k(a-1)+1$，最小性也就证明了。于是我们考虑在这种情况下最小化 $m$。

考虑最小化 $m$。还是考虑鸽笼，如果对手每取 $x+1$ 个就会出现一对可以同时的被包含在获胜需要的子矩阵中，同上计算答案为 $x(b-1)+1$。

由于对手会采取最优行动，所以考虑求 $x$ 的最大值。首先考虑 $x$ 的上界，我们只考虑获胜需要的子矩阵中的元素，这种元素只有 $n\choose a$ 种选法。但原矩阵中每个元素有 $k$ 种选法，所以 $x$ 的上界为 $k{n\choose a}$。

接下来考虑证明 $x$ 可以取到上界。由于 $n=k(a-1)+1$，去掉 $a$ 个获胜需要的子矩阵中的元素还剩 $(k-1)(a-1)$ 个位置，其他每种取值 $c$ 各取 $a-1$ 个，由于其他取值 $c$ 与取值 $c$ 作为获胜需要的子矩阵中的元素时的数量不同，所以一定不会产生冲突。

于是我们证明了 $x$ 的上界，通过鸽笼得出了 $m$ 的下界，进而证明了 $n$ 的下界。

实现的时候组合数暴力计算即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,a,b,k,jc[200000],inv[200000];
const long long mod=1e9+7;
long long power(long long a,long long p)
{
	long long x=a,ans=1;
	while(p)
	   {
	   	if(p&1)ans=ans*x%mod;
	   	p>>=1;
	   	x=x*x%mod;
	   }
	return ans;
}

int main()
{
	jc[0]=1;
	for(int i=1;i<=100000;i++)jc[i]=jc[i-1]*i%mod;
	inv[100000]=power(jc[100000],mod-2);
	for(int i=99999;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld%lld%lld",&a,&b,&k);
		long long n=k*(a-1)+1,m=inv[a]*k%mod*(b-1)%mod;
		for(long long i=n;i>=n-a+1;i--)m=m*(i%mod)%mod;
		m=(m+1)%mod;
		printf("%lld %lld\n",n%mod,m); 
	   }
	return 0;
}
```

---

## 作者：yitinboge_fan (赞：2)

# CF2120D Matrix game

观察题目，题目要求**按字典序**最小化矩阵大小。换句话说，优先判断行数。因此，我们先最小化 $n$。

考虑行数时，需要保证每一列都必然存在 $a$ 个数相同，否则根据题意 Harshith 就可以构造出不满足条件的矩阵。于是有 $n$ 的下界为 $k(a-1)+1$。

接下来考虑 $m$。我们发现，对于 Harshith 来说，每一列中重复出现至少 $a$ 次的数出现次数越少越好。例如 $a=k=2$ 时，根据上面的式子算出 $n\ge 3$，那么如果 $n=3$，假设在一列中 $1$ 出现至少两次，那么对于 Harshith 来说最优解就是 $1$ 出现两次，$2$ 出现一次。

假设 Harshith 已经构造出了矩阵，那么对于 Aryan 来说，每一列只需要考虑那个重复出现了 $a$ 次的数和其出现的 $a$ 个位置即可，简单计算得这些共有 $k\dbinom{n}{a}$ 种情况。于是，可以计算得到当 $n$ 取下界时，$m$ 的下界为 $k(b-1)\dbinom{n}{a}+1$。由于 $a\le10^5$，组合数暴力计算即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 1e9+7;
ll fastpow (ll a, ll b)
{
    ll r = 1;
    while (b)
    {
        if (b & 1) r = r * a % p;
        a = a * a % p; b >>= 1;
    }
    return r;
}
int main (void)
{
    int $; scanf ("%d", &$);
    while ($--)
    {
        int a, b, k, i; scanf ("%d%d%d", &a, &b, &k);
        ll n = (a-1ll) * k + 1; n %= p;
        ll m = 1;
        for (i=1; i<=a; i++) m = m * fastpow (i, p-2) % p * ((n-i+1+p) % p) % p;
        m = m * k % p * (b-1) % p + 1;
        printf ("%lld %lld\n", n, m%p);
    }
}

```

---

