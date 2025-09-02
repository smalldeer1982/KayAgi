# [GCPC 2024] Dark Alley

## 题目描述

在一个寒冷而有雾的夜晚，你走在一条阴暗的小巷里。
每隔几米应该有一盏路灯，但似乎没有一盏能亮起，在这个夜晚，连月亮都无法照亮你的路。
孤身一人在黑暗中，你不禁思考：
“即使某处有一盏亮着的灯，它能照亮我多少路呢？”
现在，回到家中，你想要计算这个问题。

![](https://cdn.pixabay.com/photo/2019/06/13/05/24/the-park-at-night-4270765_1280.jpg)

:::align{center}
雾蒙蒙的小巷。[照片来自 Henryk Niestrój](https://pixabay.com/de/photos/park-in-der-nacht-dunkle-stra%C3%9Fe-4270765/)
:::

这条小巷可以被建模为一条长度为 $n$ 米的直线。
雾的密度是均匀的，每经过 $1$ 米，雾会使灯光衰减 $1-p$ 倍。
某一点的亮度等于所有灯光到达该点的光强之和。
你需要在放置一些灯之后，计算某些点的亮度。

## 说明/提示

在第一个样例中，放置灯后小巷各点的亮度如下表所示：

| $3$ | $4$ | $3$ | $2.25$ | $1.6875$ |
|:-:|:-:|:-:|:-:|:-:|

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 6 0.25
+ 4 2
? 1
? 2
? 3
? 4
? 5```

### 输出

```
3
4
3
250000004
187500003```

## 样例 #2

### 输入

```
5 7 0.33
+ 9 1
? 5
+ 4 3
? 2
? 5 
- 9 1
? 2```

### 输出

```
312342734
470000012
341542736
760000008```

# 题解

## 作者：Crazyouth (赞：0)

## 分析

设对于第 $i$ 个位置它的灯亮度总和为 $b_i$（某一时刻），那么第 $x$ 个位置的亮度就是：（以下令 $P=1-p$）

$$
\begin{aligned}
\sum_{i=1}^nb_iP^{|x-i|}
&= \sum_{i=1}^xb_iP^{x-i}+\sum_{i=x+1}^nb_iP^{i-x}\\
&= P^x\sum_{i=1}^xb_iP^{-i}+P^{-x}\sum_{i=x+1}^nb_iP^i
\end{aligned}
$$

所以我们直接开两棵线段树维护那两个求和，位置 $x$ 加上 $b$ 实际上等价于在线段树上加上 $P^x$ 或 $P^{-x}$。查询操作其实就是两次区间求和。

注意处理 $P$ 的分数形式的时候注意精度问题。

## AC Code
```cpp line-numbers
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7; 
int n,q,p,tr[200010][2],invp;
int qpow(int b,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=ret*b%mod;
		b=b*b%mod;
		p>>=1;
	}
	return ret;
}
void upd(int k,int c,int type,int s=1,int t=n,int p=1)
{
	if(s==t)
	{
		tr[p][type]+=c;
		tr[p][type]%=mod;
		return;
	}
	int m=s+t>>1;
	if(k<=m) upd(k,c,type,s,m,p<<1);
	else upd(k,c,type,m+1,t,p<<1|1);
	tr[p][type]=tr[p<<1][type]+tr[p<<1|1][type];
	tr[p][type]%=mod;
}
int qry(int l,int r,int type,int s=1,int t=n,int p=1)
{
	if(l>r) return 0;
	if(l<=s&&t<=r) return tr[p][type];
	int ans=0,m=s+t>>1;
	if(l<=m) ans=qry(l,r,type,s,m,p<<1);
	if(r>m) ans+=qry(l,r,type,m+1,t,p<<1|1);
	ans%=mod;
	return ans;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	long double pp;
	cin>>n>>q>>pp;
	pp=1-pp;
	p=((int)(pp*1000000+0.5))*qpow(1000000,mod-2)%mod;
	invp=qpow(p,mod-2);
	while(q--)
	{
		char opt;
		int b,x;
		cin>>opt;
		if(opt=='+')
		{
			cin>>b>>x;
			upd(x,b*qpow(p,x)%mod,0);
			upd(x,b*qpow(invp,x)%mod,1);
		}
		else if(opt=='-')
		{
			cin>>b>>x;
			upd(x,(-b*qpow(p,x)%mod+mod)%mod,0);
			upd(x,(-b*qpow(invp,x)%mod+mod)%mod,1);
		}
		else
		{
			cin>>x;
			cout<<(qry(1,x,1)*qpow(p,x)%mod+qry(x+1,n,0)*qpow(invp,x)%mod)%mod<<'\n';
		}
	}
}

---

## 作者：cosf (赞：0)

下文设 $p$ 为原题中的 $1-p$。

考虑操作的本质，相当于给 $x$ 的位置加上 $b$，以及对于所有 $i$，$x \pm i$ 的位置加上 $b \times p^i$。这是一个区间加等比数列的问题。

任意等比数列是做不了的，但是在本题中只有两种公比 $p, \frac{1}{p}$，于是考虑建两棵线段树。

以公比为 $p$ 的线段树为例，假设我们要求的是 $a_i$。考虑令辅助数组 $b_i = \frac{a_i}{p^i}$。如果给 $a_i$ 的一个后缀 $[j, n]$ 加入首项为 $x$，公比为 $p$ 的等比数列，相当于给 $b$ 的 $[j, n]$ 后缀加上 $\frac{x}{p^j}$。

于是对于 `+ b x` 操作，我们在公比为 $p$ 的线段树上进行 $[x, n]$ 区间 $+ \frac{b}{p^x}$，在公比为 $\frac{1}{p}$ 的线段树上进行 $[1, x - 1]$ 区间 $+ (b \times p^x)$，然后单点求值即可。（注意把 $b_i$ 转成 $a_i$ 再返回）

```cpp line-numbers lines=79,100
#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 200005
#define MOD 1'000'000'007ll

using ll = long long;

ll pow(ll b, ll p, ll m)
{
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}

int n, m;
ll p;

struct SegTree
{
    ll mul[MAXN];

    ll t[MAXN << 2];

    #define ls (p << 1)
    #define rs (p << 1 | 1)

    void pushdown(int p)
    {
        if (t[p])
        {
            (t[ls] += t[p]) %= MOD;
            (t[rs] += t[p]) %= MOD;
            t[p] = 0;
        }
    }

    void build(ll v)
    {
        mul[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            mul[i] = mul[i - 1] * v % MOD;
        }
    }

    void add(int p, int l, int r, int ql, int qr, ll v)
    {
        if (ql <= l && r <= qr)
        {
            (t[p] += v) %= MOD;
            return;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (mid >= ql)
        {
            add(ls, l, mid, ql, qr, v);
        }
        if (mid < qr)
        {
            add(rs, mid + 1, r, ql, qr, v);
        }
    }

    ll query(int p, int l, int r, int q)
    {
        if (l == r)
        {
            return t[p] * mul[l] % MOD; // 记得乘上对应的系数
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (mid >= q)
        {
            return query(ls, l, mid, q);
        }
        else
        {
            return query(rs, mid + 1, r, q);
        }
    }

} t1, t2;

int main()
{
    cin >> n >> m;
    double _p;
    cin >> _p;
    p = (MOD + 1 - (ll(round(_p * 1000000)) * pow(1000000, MOD - 2, MOD)) % MOD) % MOD; // 注意处理 p
    t2.build( p), t1.build(pow(p, MOD - 2, MOD));
    while (m--)
    {
        char ch;
        cin >> ch;
        if (ch == '+')
        {
            int b, x;
            cin >> b >> x;
            t1.add(1, 1, n, 1, x, b * pow(t1.mul[x], MOD - 2, MOD) % MOD);
            if (x < n)
            {
                t2.add(1, 1, n, x + 1, n, b * pow(t2.mul[x], MOD - 2, MOD) % MOD);
            }
        }
        else if (ch == '-')
        {
            int b, x;
            cin >> b >> x;
            b = MOD - b;
            t1.add(1, 1, n, 1, x, b * pow(t1.mul[x], MOD - 2, MOD) % MOD);
            if (x < n)
            {
                t2.add(1, 1, n, x + 1, n, b * pow(t2.mul[x], MOD - 2, MOD) % MOD);
            }
        }
        else
        {
            int x;
            cin >> x;
            cout << (t1.query(1, 1, n, x) + t2.query(1, 1, n, x)) % MOD << '\n';
        }
    }
}

```

---

