# [ARC147D] Sets Scores

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc147/tasks/arc147_d

長さ $ N $ の整数の集合の列 $ S=(S_1,S_2,\dots,S_N) $ のうち、以下の条件を全て満たすものを「素晴らしい集合の列」と呼びます。

- $ S_i $ は $ 1 $ 以上 $ M $ 以下の整数のみからなる集合(空集合でもよい)である。$ (1\ \le\ i\ \le\ N) $
- $ S_i $ と $ S_{i+1} $ のうち、ちょうど片方にのみ含まれる要素の個数は $ 1 $ 個である。$ (1\ \le\ i\ \le\ N-1) $

ここで、素晴らしい集合の列 $ S $ のスコアを $ \displaystyle\ \prod_{i=1}^{M} $ $ (S_1,S_2,\dots,S_N $ のうち、$ i $ を含む集合の個数 $ ) $ と定義します。

全ての素晴らしい集合の列に対するスコアの総和を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N,M\ \le\ 2\ \times\ 10^5 $
- 入力は全て整数である。

### Sample Explanation 1

素晴らしい集合の列のうち、スコアが正であるものは以下の $ 6 $ 個です。 - $ S_1=\{1,2\},S_2=\{1,2,3\} $ - $ S_1=\{1,3\},S_2=\{1,2,3\} $ - $ S_1=\{2,3\},S_2=\{1,2,3\} $ - $ S_1=\{1,2,3\},S_2=\{1,2\} $ - $ S_1=\{1,2,3\},S_2=\{1,3\} $ - $ S_1=\{1,2,3\},S_2=\{2,3\} $ 全てスコアは $ 4 $ であるため、解は $ 24 $ です。

## 样例 #1

### 输入

```
2 3```

### 输出

```
24```

## 样例 #2

### 输入

```
12 34```

### 输出

```
786334067```

# 题解

## 作者：DaiRuiChen007 (赞：6)

# ARC147D 题解

## 思路分析

粗体字母表示集合

显然，在已知 $\mathbf S_1$ 的情况下，只需要确定每一组 $\mathbf S_i,\mathbf S_{i+1}$ 之间不同的元素 $p_i$ 就可以得到 $\mathbf S_{2}\sim \mathbf S_n$

考虑固定 $p_1\sim p_{n-1}$，对于此时所有的 $\mathbf S_i$ 都只和 $\mathbf S_1$ 有关系，因此对于每一个 $[1,m]$ 中的元素 $i$，其在 $\mathbf S_1\sim S_n$ 中出现的次数之和 $c_i$ 只和 $i$ 是否在 $\mathbf S_1$ 中有关系，因此我们可以得到 $i$ 在或者不在 $\mathbf S_1$ 中时 $c_i$ 的值：$a_i,b_i$

我们有 $a_i+b_i=n$

> 证明：
>
> 假设 $i$ 在 $\mathbf S_1$ 中时，定义 $\mathbf A_i:\{x|i\in\mathbf S_x\}$，即所有满足 $i\in \mathbf S_x$ 的 $x$ 构成的集合，若 $i$ 不在 $\mathbf S_1$ 中，则这些 $x$ 构成 $\mathbf B_i$，根据定义有 $|\mathbf A_i|=a_i,|\mathbf B_i|=b_i$
>
> 事实上：对于每一个 $[1,n]$ 的 $x$，$x\in \mathbf A_i$ 和 $x\in \mathbf B_i$ 中**有且仅有**一个成立
>
> 采用数学归纳法，对于 $n=1$ 的情形，显然 $x\in \mathbf A_1,x\not\in \mathbf B_1$
>
> 接下来假设对于某一个 $k$ 这种情况成立，不妨设 $x\in \mathbf A_k,x\not\in\mathbf B_k$：
>
> 接下来我们只需要考虑 $i=p_k$ 或者 $i\neq p_k$
>
> - $i\neq p_k$ 时，此时 $x\in \mathbf A_{k+1},x\not\in\mathbf B_{k+1}$
> - $i=p_k$ 时，此时 $x\not\in \mathbf A_{k+1},x\in\mathbf B_{k+1}$
>
> 综上，对于 $k+1$ 同样成立
>
> 故原命题得证 

显然对于此时所有的 $\mathbf S_1$ 的情况，每种序列的总价值之和应该为：
$$
a_1\times a_2\times \cdots\times a_m+b_1\times a_2\times \cdots\times a_m\cdots\cdots+ b_1\times b_2\times\cdots\times b_{m-1}\times a_m+b_1\times b_2\times\cdots\times b_m
$$
即对于每个数 $i$，选择 $a_i$ 或者 $b_i$ 乘进总价值里面，对应的就是 $i$ 是否在 $\mathbf S_1$ 里面，对上式进行提取公因数可得上式实际上等于下式：
$$
\prod_{i=1}^m(a_i+b_i)=n^m
$$
因此对于每一种 $p_1\sim p_{n-1}$ 的序列，都有 $n^m$ 的权值之和，又因这样的 $x$ 序列共有 $m^{n-1}$ 种，故答案为 $n^m\times m^{n-1}$

快速幂，时间复杂度 $\Theta(\log n+\log m)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=998244353;
inline int ksm(int a,int b,int m=MOD) {
	int res=1;
	while(b) {
		if(b&1) res=res*a%m;
		a=a*a%m;
		b=b>>1;
	}
	return res;
}
signed main() {
	int n,m;
	scanf("%lld%lld",&n,&m);
	printf("%lld\n",ksm(n,m)*ksm(m,n-1)%MOD);
	return 0;
}
```

---

## 作者：Phartial (赞：4)

诈骗题。

把 $S_i$ 用二进制表示，$S_i$ 到 $S_{i+1}$ 的变化相当于异或了一个数 $2^{x_i}$，对于每个集合考虑变化有点困难，不妨考虑对于每种长度为 $n-1$ 的变化序列 $x_i$，统计不同的初始集合对应的答案。

设 $p_i$ 表示初始集合 $s_1$ 有元素 $i$ 时，所有集合里 $i$ 出现的次数。

对应的答案即为 $\sum_{S}(\prod_{i\in S}p_i)(\prod_{i\not\in S}n-p_i)$，$S$ 为初始集合 $s_1$。运用乘法分配律可以得到答案即为 $\prod_{i=1}^mp_i+n-p_i=n^m$，而不同的变化序列有 $m^{n-1}$ 种。所以总答案为 $n^mm^{n-1}$。

---

## 作者：CrTsIr400 (赞：1)

题意：构造 $n$ 个集合，其中的数范围 $[1,m]$，相邻两个集合之间有且仅有一个不同的数。

定义这 $n$ 个集合的分数为 $∏\limits_{i=1}^{m}cnt(i)$，$cnt(i)$ 为 $i$ 数字出现的次数。

---

思路：没有看到题解的时候我想了很久，没什么出路。后来题解分析了一下方案，豁然开朗。

做法：首先可以发现相邻两个只相差一个数，记录这个数，设其为 $x_i$。

这个数有什么用呢？观察到 $x_i$ 就是在第 $i+1$ 个集合中对于数 $x_i$ 状态的改变。即 $i$ 位置有，$i+1$ 位置就没有了；或者 $i$ 位置没有，$i+1$ 位置就有了。

因为确定了一个长度为 $n-1$ 的序列 $x$，所以只需要确定第一个位置上的集合，权值就出来了。

设 $a_x$ 为第一个集合中包含 $x$ 时，**所有的集合**包含 $x$ 的个数，同理可以设置 $b_x$ 为第一个集合中不包含 $x$ 时，剩下的集合包含 $x$ 的个数。

于是我们就有了选择第一个集合的方案数：$∏\limits_{i=1}^{m}{(a_i+b_i)}$。

然后，因为 $x$ 序列固定，又知道 $x_i$ 的性质，所以决定它出现次数的，只有某个数在第一个集合中出现与否：如果出现了，就选择 $a_i$；否则选择 $b_i$。经过一番观察，我们发现 $a_i+b_i=n$。

于是对于一个可行的 $x$ 序列，答案就是 $n^m$。

所以对于全局的答案，就是 $n^m\times m^{n-1}$。

---

这题在思考的时候，觉得有点困难，没有深入挖掘性质。同时欠缺了观察和设计状态。

希望之后解这种数学题的时候，能够思维与观察、性质相结合。

另外，对于解这种英文题，理解切忌偏差。

---

## 作者：pokefunc (赞：0)

题意：你要构造 $n$ 个集合 $S_1,S_2,\dots,S_n$，满足所有集合元素都是 $[1,m]$ 内的整数，且对于 $i \in [1,n)$ 有 $S_i$ 与 $S_{i+1}$ 相差恰好一个元素。记一种集合的构造方案的权值为 $\prod_{i=1}^{m}c_i$（其中 $c_i$ 为在所有集合中的出现次数），求所有满足条件的构造方案的权值和。

一开始还以为是啥神秘容斥，结果发现被骗了，哈哈。

由于转移到下一个位置的集合时要么加一个元素要么减一个元素，我们考虑把每一次发生变化的那个元素记下来，这样得到了一个长度为 $n-1$ 的序列 $P$。由于这个绝妙的定义，所有长为 $n-1$ 且 $P_i \in [1,m]$ 的所有序列都是合法的。

此时只需要确定 $S_1$ 即可。考虑 $S_1$ 包含的元素，定义 $a_{x,0/1}$ 分别表示 $x \in S_1$ 与 $x \not \in S_1$ 时 $x$ 在所有集合内的出现次数。我们发现，$x$ 在 $P$ 中每出现一次，就代表它在集合中的状态翻转一次。由于 $S_1$ 包含/不包含 $x$ 是两种相反的初始情况，因此无论出现多少次，在两种初始情况下都不可能出现某次翻转后 $x$ 在两边的两个集合的出现状态相同，进而推出 $a_{x,0}+a_{x,1}=n$，也就是说对于 $P$ 确定的情况，每一种 $x$ 都贡献 $n$ 的出现次数，则这一部分的答案为 $n^m$。又有 $P$ 一共有 $m^{n-1}$ 种，因此答案为 $n^mm^{n-1}$。

---

## 作者：littleqwq (赞：0)

# [ARC147D] Sets Scores 题解

### 大致思路：

每个集合之间可能会有不同的数 $k$，而我们可以直接找出任意一个集合 $S_i$，找出它里面是否存在 $k$，找出所有的可能性 $x$。对于一个序列 $S_i$，它的可能性为 $n ^ m$，而一共不同的数会存在 $n - 1$ 次的比较，因为是每相邻两个比较，所以总次数为 $m ^ {n - 1}$，合起来就为 $n ^ m × m ^ {n - 1}$，而由于数据过于大，我们要采用快速幂，并且最终注意变量类型。

如果以上方法不太懂可以使用列举的方法，一个个列举，接着和样例进行校对，接着得出规律。

当然如果比较空的时候也可以尝试一下打表。

### 代码实现：

```
#include<bits/stdc++.h>
using namespace std;
long long n,m,s;
const long long p=998244353;
long long f(long long a,long long b){
	long long x=1,y=a;
	while(b>0){
		if(b%2==1){
			x=(x*y)%p;
		}
		y=(y*y)%p;
		b=b>>1;//位运算更快的除2，千万不要b>>1,会TLE的
	}
	return x; 
}
int main(){
	cin>>n>>m;
	s=f(m,n-1)*f(n,m)%p;
	cout<<s<<endl;
	return 0;
}
```

这道题就完成啦！！！

---

## 作者：LiveZoom (赞：0)

## Description

[link](https://www.luogu.com.cn/problem/AT_arc147_d)

## Solution

设第 $i$ 个和第 $i+1$ 个集合不同的数是 $x_i$。

那么我们知道 $S_1$ 和 $x$ 后就相当于知道了所有集合。

然后可以先固定 $x$，易知不同元素之间是不会互相影响的，所以可以对每种元素算它在或不在 $S_1$ 的方案数。

感性理解一下会发现两种方案和是 $N$，所以对于一个固定的 $x$，答案就是 $N^M$。

而 $x$ 有 $M^{N-1}$ 种方案，所以总数就是 $N^M\times M^{N-1}$。

## Code

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

const int kMod = 998244353;

int n, m;

int qpow(int bs, int idx) {
  int ret = 1;
  for (; idx; idx >>= 1, bs = 1ll * bs * bs % kMod)
    if (idx & 1)
      ret = 1ll * ret * bs % kMod;
  return ret;
}

int main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  cout << 1ll * qpow(n, m) * qpow(m, n - 1) % kMod << '\n';
  return 0;
}
```

---

