# Increasing Subsequences

## 题目描述

Let's recall that an increasing subsequence of the array $ a $ is a sequence that can be obtained from it by removing some elements without changing the order of the remaining elements, and the remaining elements are strictly increasing (i. e $ a_{b_1} < a_{b_2} < \dots < a_{b_k} $ and $ b_1 < b_2 < \dots < b_k $ ). Note that an empty subsequence is also increasing.

You are given a positive integer $ X $ . Your task is to find an array of integers of length at most $ 200 $ , such that it has exactly $ X $ increasing subsequences, or report that there is no such array. If there are several answers, you can print any of them.

If two subsequences consist of the same elements, but correspond to different positions in the array, they are considered different (for example, the array $ [2, 2] $ has two different subsequences equal to $ [2] $ ).

## 样例 #1

### 输入

```
4
2
5
13
37```

### 输出

```
1
0
3
0 1 0
5
2 2 3 4 2
7
-1 -1 0 0 2 3 -1```

# 题解

## 作者：KAMIYA_KINA (赞：8)

## Tag

构造，位运算。

## Preface
D 被群友误导了半天的线段树，于是去做 E，结果做得比 A 还快。

## Description

给定一个数 $X$，要求构造一个长度不超过 $200$ 的数列使得这个数列的所有严格上升子序列的数量等于 $X$。

$\texttt{data range:} 2\leq X \leq 10^{18}$.

## Solution

### 想法一

我们发现一个单调递增数列的严格上升子序列的数量等于 $2^{N}$，这里的 $N$ 是数列的长度。

于是我们就可以构造出若干个单调递增数列如 $\text{\{3, 4, 5, 1, 2\}}$，这个数列的严格上升子序列的数量为 $2^3-1+2^2-1+1=11$ 个。

此时前序列一个序列对于后一个序列是没有影响的，所以可以独立计算，但是我们此时需要的数列的长度为 $(\log_2X)^2$，显然过不去这个题目。

### 想法二
在上面的想法中进行优化，使得小的与大的数列尽量有交。

我们可以构造出一个最长的数列，也就是 $1\sim \lfloor\log_2X\rfloor$ 这个数列，然后在这个数列中插入若干数去满足条件。

进一步想到我们此时插入的数在子序列**存在时**，后面的数都不会进入子序列中，对于前面数的可能就是 $2^n$，这里的 $n$ 等于这个数前面小于他的数的数量。

于是我们得到了如下构造。

先构造出 $1\sim \lfloor\log_2X\rfloor$ 的数列。此时我们设一个无穷大的数 $M$，当 $X$ 的第 $i$ 位为 $1$ 时，我们在数字 $i$ 的后面加上一个 $M-i$，最高位除外，当第 $0$ 位存在时需要在序列前加入一个 $M$。这里 $X$ 的第 $i$ 位为 $1$ 指的是 $X$ 右移 $i$ 位后**与运算** $1$ 的结果为 $1$。

最后整体的数列的长度不超过 $2\log_2X$，可以通过本题。

## Code

```cpp
inline void solve() {
  ll x = rd;
  ll lim = 1, tim = 0;
  while((lim << 1) <= x) lim <<= 1, tim++;
  vector <int> ans;
  int M = 10000;
  for(int i = 0; i < tim; i++) {
    if(i != 0) ans.push_back(i);
    if(x & (1ll << i)) ans.push_back(M - i);
  }
  ans.push_back(tim);
  cout << ans.size() << '\n';
  for(auto x : ans) cout << x << ' ';
  cout << '\n';
}
```

## Final

感觉讲的有点抽象，建议自己手玩一下。

---

## 作者：mango2011 (赞：5)

一次考虑每一个数对于整个数组的“递增子序列”的个数的贡献。这件事情其实很有趣，因为如果我们考虑了太多的情形，反而做不出来，我们只需要考虑：如果新增加的数是最小的，则贡献为 $+1$；若新增加的数是最大的，则贡献为 $\times2$。

于是考虑从答案 $n$ 倒推，如果是奇数，则变为 $n-1$ 的情形，末尾再加最小的数；若是偶数，则变为 $n/2$ 的情形，末尾再加最大的数即可。

同志们，有了上面的分析，我们就可以发现这与二进制类似（不类似也没有关系），于是给出递归代码 $\times1$：

```cpp
#include<bits/stdc++.h>
using namespace std;
int mi(vector<int> v)
{
    int i,mi=INT_MAX;
    for(i=0;i<v.size();i++)
    {
        mi=min(mi,v[i]);
    }
    return mi;
}
int mx(vector<int> v)
{
    int i,mx=INT_MIN;
    for(i=0;i<v.size();i++)
    {
        mx=max(mx,v[i]);
    }
    return mx;
}
vector<int> solve(long long x)
{
    vector<int>res;
    if(x==2)
    {
        res.push_back(0);
    }
    else
    {
        if(x&1)
        {
            res=solve(x-1);
            res.push_back(mi(res)-1);
        }
        else
        {
            res=solve(x>>1);
            res.push_back(mx(res)+1);
        }
    }
    return res;
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
    int T,i;
    long long n;
    vector<int>v;
    cin>>T;
    while(T!=0)
    {
        T--;
        cin>>n;
        v=solve(n);
        cout<<v.size()<<'\n';
        for(i=0;i<v.size();i++)
        {
            cout<<v[i]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}

```
注意上面的代码，我们特判剩余的需要个数为 $2$ 时，直接给出 $0$（其实任意的整数都可以），这是因为 $[0]$ 是一个递增子序列，$[]$ 也是一个递增子序列。

根据本人不到两年半的 CF 经验，想这种题目，迭代实现应该也是可以的。

---

## 作者：zmza (赞：3)

首先，一个长为 $n$ 的递增串能贡献的数量是 $2^n-1$。但是如果直接做是 $\log^2$ 的，过不了。考虑每次在前 $x$ 个数的后面插入一个比它们都大的值的贡献是 $2^x$，所以最开始直接插入 $n$ 个数，将 $X$ 减去 $2^n-1$，然后再将 $X$ 二进制拆分即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e3 + 5;
int os[maxn], sum[maxn], pp[maxn];
void solve()
{
	for (int i = 0; i <= 200; i++) pp[i] = 0;
	int x;
	cin >> x;
	x--;
	int now = 59, lst = 0;
	while (x)
	{
		if (x - sum[now] >= 0)
		{
			x -= sum[now], lst = now;
			break;
		}
		now--;
	}
	for (int i = 59; i >= 0; i--)
		if (x >> i & 1) pp[i]++;
	vector<int> vec;
	now = 1e9;
	for (int i = 0; i <= lst; i++)
	{
		while (pp[i]--) vec.emplace_back(now--);
		vec.emplace_back(i);
	}
	assert(vec.size() <= 200);
	cout << vec.size() << '\n';
	for (int i : vec) cout << i << ' ';
	cout << '\n';
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	os[0] = sum[0] = 1;
	for (int i = 1; i <= 200; i++)
	{
		for (int j = 0; j < i; j++) os[i] += os[j];
		os[i]++;
		sum[i] = sum[i - 1] + os[i];
		if (sum[i] >= 1e18) break;
	}
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：Eraine (赞：2)

编号：CF1922E

tag：构造

考场上一眼一种做法，机房的 @tobie @Codepenguin @huangziqin 想到了第二种做法。Orz。

**【做法一】**

考虑在当前递增子序列个数为 $sum$，值域为 $[l,r]$ 的序列添加 $l-1$ 和 $r+1$ 后缀，对答案的贡献分别是 $+1$ 和 $\times 2$。

随即想到二进制拆分。

在迭代求解过程中，当 $2\mid n$ 时，在后缀加一个 $r+1$ 即可（此时 $sum$ 会左移一位），将 $n\div2$ 迭代至下一层。当 $2\nmid n$ 时，在后缀加一个 $l-1$ 即可（此时 $sum$ 会减一），将 $n-1$ 迭代至下一层。

$\Theta(\log n)$。

考场代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int l,r;
vector<int>ans;
void dfs(ll n){
	if(n==1){//n=1 此时为空串，退出迭代
		return;
	}
	if(n&1){//n 为奇数
		dfs(n^1);//向 n-1 递归
		ans.push_back(--l);//添加一个 l-1 后缀
	}else{
		dfs(n>>1);//向 n/2 递归
		ans.push_back(++r);//添加一个 r+1 后缀
	}
}
void solve(){
	ans.clear();//答案序列，多测不清空，爆零两行泪
	l=1,r=0;
	ll n;
	scanf("%lld",&n);
	dfs(n);
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++){
		printf("%d ",ans[i]);
	}
	printf("\n");
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
	return 0;
}
```


**【做法二】**

在递增序列 $1,2,...,n$ 添加一串值域在 $[0,n)$ 的严格递减序列的后缀。

前面一串（不考虑与后面一起的贡献）的总贡献为 $2^n$。后面一串不会互相造成贡献。

后面的每个数字 $x$ 的单独贡献（即与前面部分结合的贡献）为 $2^x$。

随即同做法一，将 $n$ 二进制拆分后，最高位作为前半部分长度，然后其他位从高到低枚举，只要出现 $1$，就添加一个与当前位数码（从 $0$ 开始）相同的后缀。

$\Theta(\log n)$。

做法二就不放代码了（没写），简单理解下自己写吧 =)

各位看官点个赞再走吧 awa

---

## 作者：Zemu_Ooo (赞：1)

这场没太来得及打，只写了一些较为好写的，所以多写几篇这场的题解发泄一下（大哭

首先通过不断右移 $X$ 找到 $X$ 的最高有效位（即最左边的 $1$）。接着，我们构造一个长度为 $m$ 的基础序列，每个元素为 $2$ 的倍数，因为长度为 $L$ 的递增序列可以贡献 $2^L$ 个子序列。然后根据 $X$ 的二进制表示来调整这个序列。

如果二进制中的某一位是 $1$（从最低位开始检查），就在序列的前面插入一个特定的数，这个数是使得包含这个数的子序列数量正好为 $2^i$。这是通过计算 $2 \times m - 2 \times i - 1$ 来实现的，其中 $i$ 是当前正在处理的二进制位。

最后，我们输出调整后的序列。这个方法可以确保所构造的序列的子序列数量恰好等于给定的 $X$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    int t; cin >> t;
    while (t--) {
        int x; 
        cin >> x;
        int m = 0; // 最高位
        int y = x;
        while (y) {
            m++;
            y >>= 1;
        }
        m--;
        deque<int> ans;
        for (int i = 0; i < m; i++) {
            ans.push_back(2 * i);
        }
        for (int i = m - 1; i >= 0; i--) {
            if (~x & ((int)1 << i)) continue;
            ans.push_front(2 * m - 2 * i - 1);
        }

        cout << ans.size() << '\n';
        for (auto e : ans) {
            cout << e << ' ';
        }
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：robinyqc (赞：1)

和 A 题做的时间一样，有点难绷。

### 题意简述

构造一个长度不超过 200 的序列，使其严格上升子序列个数为 $x$（$2\leq x\leq 10^{18}$）。多测，询问数不超过 $1000$ 个。

### 解法

设 $h = \lfloor \log_2 x\rfloor$，也就是 $x$ 的最高位。我们先构造一个 $[0, h)$ 的严格上升序列 $s$。从 $h - 1$ 到 $0$，若 $x$ 的第 $i$ 位是 $1$，那么就在末尾放一个 $i$。得到的 $s$ 即为答案。

### 解题思路

如何求一个序列的严格上升子序列个数？dp 即可。只需要 $dp_i = 1 + \sum_{j < i, a_j < a_i} dp_j$。那怎么构造严格上升子序列个数为 $x$ 的序列呢？

首先若有一个长度为 $n$ 的严格上升序列，那么包括空串它有 $2^n$ 个严格上升子序列。这启示我们对 $x$ 二进制分解，在一个严格上升序列的基础上，构造答案。此时 $dp_i = 2^i$，总共有 $2^h$ 个严格上升子序列。

然后，你发现，若在 $s$ 后面放一个数 $z\in [0, h)$，那么按照 dp 的公式计算一下，得到新的 dp 值为 $2^z$。于是做法就出来了：从 $h - 1$ 到 $0$，若 $x$ 的第 $i$ 位是 $1$，那么就在末尾放一个 $i$。由于新加入的数是递减的，所以它们之间不互相影响。最后就能构造出 $x$ 个上升子序列了。

$s$ 最大长度为 $2h$，可以通过。

### 代码实现

```cpp
#include <iostream>
#include <vector>
using namespace std;

void solve()
{
    long long x;
    cin >> x;
    int top = 63 ^ __builtin_clzll(x);
    vector<int> ans;
    for (int i = 0; i < top; i++) ans.emplace_back(i);
    for (int i = top - 1; i >= 0; i--) 
        if ((x >> i) & 1) ans.emplace_back(i);
    cout << ans.size() << '\n';
    for (int i: ans) cout << i << ' ';
    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

很容易想到的做法是对 $X$ 二进制拆分。取一组单调递增的 $n$ 个数是可以构成非空的子串 $2^n-1$ 个。

> 证明：每个数取/不取，去掉空串。

但是，如果直接做就会使用到 $\log_2^2X$ 的长度，明显超标。

一个小聪明是超过 $200$ 次就 $-1$，我试过，WA 了。

发现上面那个 $-1$ 让人看着很烦，容易想到只用构造一组序列，这样就可以和空串的那个 $+1$ 抵消。

同样还是二进制拆分，另 $(X)_{10}=(\overline{a_pa_{p-1}\cdots a_2a_1})_2$，其中强制 $a_p=1$。

首先，$p$ 个数构成 $2^p$ 是逃不掉了，要求就是对于 $\forall q,a_q=1$，如何尽量减少构建第 $q$ 位需要的花费。

显然，是要借助我们开始构建的 $p$ 位 $1,2,3,\cdots,p$。

比如我们要构建第 $1$ 位，可以来一个局部的极大值，是的这个极大值和后面都不能形成子序列，比如就来一个 $\inf$。

那么，如果这个 $\inf$ 差在 $2,3$ 中间，$1,2,\inf,3,\cdots,p$，那么多出的子串就是 $(1,2,\inf),(1,\inf),(2,\inf),(\inf)$，发现刚好是 $2^2$ 个。

所以我们可以插入 $\inf$！

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 1e9;
int x, T, t, l;
inline int _log2(int x){
    int res = 0;
    while(x > 1){
        x >>= 1;
        res++;
    }
    return res;
}
inline void solve(){
    t = _log2(x);
    l = t;
    for(int i = 0; i < t; i++){
        if(x >> i & 1) l++;
    }
    printf("%lld\n", l);
    for(int i = 0; i < t; i++){
        if(i) printf("%lld ", i);
        if(x >> i & 1) printf("%lld ", inf);
    }
    printf("%lld ", t);
    puts("");
}
signed main(){
    scanf("%lld", &T);
    while(T--){
        scanf("%lld", &x);
        solve();
    }
    return 0;
}

```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路
因为可以有空集，那么我们首先构造第一段最长的连续上升的序列，那么这段序列中共有 $2^{\mid s \mid}$ 个上升子序列。接下来我们考虑补全剩余的，我们不妨将剩余的部分全部设为连续不增序列，那么设当前位置在第一段中有 $k$ 个小于它的，那么添加这个数后可以增加 $2^{k-1}$ 个子序列，那么直接循环添加，如果增加后超过 $x$ 了，那么 $k\gets k-1$ 即可。在循环结束后，如果 $x$ 任然有剩，那么输出 `-1`。

### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#define ll long long
#define N 205
ll x;int a[N];
int _2[N];
inline void work(){
    scanf("%lld",&x);
    int ce=0;ll y=x;
    while(y){
        _2[++ce]=y&1;
        y>>=1;
    }
    for(register int i=1;i<ce;++i)
        a[i]=i;int n=ce-1;
    x-=1ll*(1ll<<(ce-1));
    int now=ce-1;
    while(x>0){
        while(x<(1ll<<(now-1))&&now>0)
            --now;
        if(now==0) break;
        while(x>=(1ll<<(now-1))&&now>0)
            a[++n]=now,x-=(1ll<<(now-1));
    }if(x){
        puts("-1");
        return;
    }printf("%d\n",n);
    for(register int i=1;i<=n;++i)
        printf("%d ",a[i]);
    putchar('\n');
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```

---

