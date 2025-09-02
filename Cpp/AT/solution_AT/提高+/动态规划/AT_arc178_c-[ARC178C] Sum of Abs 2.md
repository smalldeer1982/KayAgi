# [ARC178C] Sum of Abs 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc178/tasks/arc178_c

正整数 $ N,L $ と長さ $ N $ の正整数列 $ A\ =\ (A_{1},\ A_{2},\ \dots\ ,\ A_{N}) $ が与えられます。

$ i\ =\ 1,\ 2,\ \dots\ ,\ N $ について、以下の問いに答えてください。

> $ \displaystyle\ \sum_{j\ =\ 1}\ ^\ {L\ -\ 1}\ \sum_{k\ =\ j\ +\ 1}\ ^\ {L}\ |B_{j}\ -\ B_{k}|\ =\ A_{i} $ を満たす、長さ $ L $ の非負整数列 $ B\ =\ (B_{1},\ B_{2},\ \dots\ B_{L}) $ が存在するか判定し、存在するならそのような $ B $ に対する $ \max(B) $ の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\ \times\ 10\ ^\ {5} $
- $ 2\leq\ L\ \leq\ 2\ \times\ 10\ ^\ {5} $
- $ 1\leq\ A_{i}\ \leq\ 2\ \times\ 10\ ^\ {5} $
- 入力は全て整数
 
### Sample Explanation 1

$ A_{1}\ =\ 10 $ について、 $ B=(1,0,2,3) $ としたとき、$ \displaystyle\ \sum_{j\ =\ 1}\ ^\ {L\ -\ 1}\ \sum_{k\ =\ j\ +\ 1}\ ^\ {L}\ |B_{j}\ -\ B_{k}|\ =\ 10 $ となり、このとき $ \max(B)\ =\ 3 $ となります。 $ \max(B)\ <\ 3 $ かつ、条件を満たす非負整数列 $ B $ は存在しないので、$ 1 $ 行目には $ 3 $ を出力してください。 $ A_{2}\ =\ 5 $ について、 条件を満たす非負整数列 $ B $ は存在しないので、 $ 2 $ 行目には `-1` を出力してください。

## 样例 #1

### 输入

```
2 4
10 5```

### 输出

```
3
-1```

## 样例 #2

### 输入

```
6 8
167 924 167167 167924 116677 154308```

### 输出

```
11
58
10448
10496
7293
9645```

# 题解

## 作者：Jelly_prx (赞：7)

下文中的 $V=\max A_i$。

首先钦定 $B$ 不下降，以 $n=5$ 为例，每个位置的贡献系数就是 $C=[-4,-2,0,2,4]$。但是这样不好计算最大值，所以我们后缀和一下，变成了 $C=[0,4,6,6,4]$，这时候操作就变成了选择一端后缀 $[i,n]$ 加一，价值为 $C_i$，问最小操作次数。显然前半部分是无用的，所以砍半后变成 $C=[6,4]$，跑个背包就可以了。

复杂度好像为 $O(VL)$ 不太对？感性理解 $C$ 从后往前增长的速度很快，所以不用枚举很多项，交上去就 A 了。

不过后来想象确实可以严谨证明，先把 $C$ 翻转，我们有通项公式：$C_i=i\times(L-i),
~i\le{L\over 2}$，然后分讨：

1. 当 $L\le2\sqrt V$ 时，复杂度显然正确。
2. 当 $L>2\sqrt V$ 时，当 $i$ 取到 $\sqrt V$ 项时，就有 $C_i$ 为 $O(V)$ 级别的，所以只用枚举 $\sqrt V$ 项。

所以背包复杂度就是 $O(V\sqrt V)$ 的。

``` cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=2e5+5;
int Q,L;
int f[N];
int main(){
	scanf("%d%d",&Q,&L);
	for(int i=1;i<N;i++){
		f[i]=N;
		for(int j=1;i>=j*(L-j)&&j<=L/2;j++) f[i]=min(f[i],f[i-j*(L-j)]+1);
	}
	while(Q--){
		int x;scanf("%d",&x);
		if(f[x]==N) printf("%d\n",-1);
		else printf("%d\n",f[x]);
	}
}

```

---

## 作者：roBotic (赞：4)

> 给定 $n$ 次询问以及一个整数 $L$，询问给定一个 $A_i$，问是否有一个长度为 $L$ 的非负整数序列 $\{B_L\}$ 满足以下的和式等于 $A_i$，如果没有输出 $-1$，否则输出该序列最大值最小是多少。
>
> $$\sum_{i=1}^{L-1}\sum_{j=i+1}^L|B_i-B_j|=A_i.$$

首先经典套路把绝对值去了，考虑钦定 $B$ 是单调不降的，然后发现每一个绝对值相当于数轴的一段距离，我们考虑每一小段，即相邻两个数的距离对总答案的贡献。考虑 $B_i,B_{i+1}$ 这一段的贡献，经过这一段的距离一共有 $i\cdot(L-i)$ 条（左边 $i$ 个，右边 $L-i$ 个），则贡献是 $i\cdot(L-i)\cdot(B_{i+1}-B_i)$。所以总共的求和是：

 $$\sum_{i=1}^{L-1}\sum_{j=i+1}^L|B_i-B_j|=\sum_{i=1}^{L-1}i\cdot(L-i)\cdot(B_{i+1}-B_i).$$

然后题目让我们使最大值最小，显然这时候 $B_1$ 肯定是 $0$，否则不优，可以把全体 $B$ 向左移动，答案更小。那么最大的 $B_L$ 就等于 $\sum (B_{i+1}-B_i)$，所以就是使 $\sum(B_{i+1}-B_i)$ 最小。

这里我们把上面的求和看成一个背包，$i\cdot(L-i)$ 为第 $i$ 个物品的体积，$(B_{i+1}-B_i)$ 则为其个数，那么对应相乘求和的结果就是背包的容量，也就是 $A_i$，而题目要求最小化的和就是背包装物品的个数。所以题目就是让我们在背包容量为 $A_i$ 的时候最小化装物品的个数。直接跑背包即可。

记 $V=\max A_i$，这样一看复杂度是 $O(LV)$ 的，但是会发现物品的体积 $i\cdot(L-i)\leq V$，所以 $i,L-i>\sqrt{V}$ 的时候都是不用转移的，则复杂度其实是 $O(V^{1.5})$。

[My Submission](https://atcoder.jp/contests/arc178/submissions/60238927).

---

## 作者：AsiraeM (赞：4)

首先将 $B$ 从小到大排序，式子可以化为 $\sum\limits_{i=1}^{L-1}\sum\limits_{j=i+1}^L(B_j-B_i)$。拆开式子，容易计算出第 $i$ 个数贡献的次数为 $(i-1)-(L-i)=2i-L-1$。  
但是这样第 $i$ 个数必须不小于第 $i-1$ 个数，且贡献有正有负，若进行 `dp` 需记下当前总贡献，时间复杂度太高，难以优化。  

$A_i$ 较小，容易想到 $B$ 中很多数都是重复的，于是考虑设 $C$ 为 $B$ 的差分序列，即 $C_i=B_{i+1}-B_i$，那么第 $i$ 个数贡献的次数为 $C$ 中包含它的区间个数，即 $i*(L-i)$；$\max(B_i)=\sum\limits_{i=1}^{L-1}C_i$。  
这样所有贡献都是正的，且最多只有 $\sqrt{A_i}$ 个数的贡献次数小于等于 $A_i$，因此设 $f_{i,j}$ 表示 $C_1$ 到 $C_j$ 贡献总和为 $i$ 时 $\sum\limits_{k=1}^{j}C_k$ 的最小值。直接进行 `dp`，每个 $A_i$ 可以 $O(1)$ 查询答案。时间复杂度为 $O\left(\max(A_i)\sqrt{\max(A_i)}\right)$。  

code:
```cpp
//Talk is cheap.Show me the code.
#include<bits/stdc++.h>
namespace xcy{
typedef long long ll;
const ll MAXN=200005;
ll f[MAXN],g[MAXN],b[MAXN],v[MAXN],cnt,n,m,mx,l,i,j,k,ans;

inline void fread(ll &X){ll A=1;X=0;char C=getchar();while(!isdigit(C)&&C!='-')C=getchar();if(C=='-')A=-1,C=getchar();while(isdigit(C))X=(X<<1)+(X<<3)+(C^48),C=getchar();X*=A;}
inline void fout(ll X){if(X<0)putchar('-'),X=-X;if(!X){putchar('0'),putchar(' ');return;}char C[25]{};int Len=0;while(X)C[++Len]=X%10+'0',X/=10;for(;Len;--Len)putchar(C[Len]);putchar(' ');}

int mian()
{
    fread(n);fread(m);memset(f,0x3f,sizeof(f));f[0]=0;
    for(i=1;i<=n;++i)fread(b[i]),mx=std::max(mx,b[i]);
    for(i=1,--m;i<=m;++i)if(i*(m-i+1)<=mx&&i<=(m-i+1))v[++cnt]=i*(m-i+1);
    for(i=1;i<=mx;++i)for(j=1;j<=cnt;++j)
        if(i-v[j]>=0)f[i]=std::min(f[i],f[i-v[j]]+1);
    for(i=1;i<=n;++i)fout(f[b[i]]<0x3f3f3f3f3f3f3f3f?f[b[i]]:-1),putchar('\n');
    return 0;
}}
int main(){return xcy::mian();}
```

---

## 作者：suzhikz (赞：2)

来发别样的的理解方式。

首先钦定 B 单调递增，感性理解下题面，题目要我们求得就是任意两个位置之间的差的和，那么相邻两个 B 之间的贡献是 $i*\times(l-i)$，原因就是我们可以在左边选 $i$ 个数，右边选 $l-i$ 个数，所以贡献就是这个 $i*\times(l-i)$ ，那我们就可以直接存下这玩意然后 bfs 了。

然后这样的数字满足小于 $2\times 10^5$ 的个数级别是根号的，别的题解有证明这里就不放了，复杂度 $O(n \sqrt{n})$。

---

## 作者：Creeper_l (赞：2)

> 题意：给定 $n$ 和 $L$ 以及 $n$ 个数 $a_i$。对于每个 $1 \le i \le n$，求出一个长度为 $L$ 的 $b$ 序列满足：$\sum_{i=1}^{L-1}\sum_{j=i+1}^{L} |b_j-b_i|=a_i$，并最小化 $b$ 中的最大值。

显然 $b$ 中元素的顺序不影响原式的结果，所以我们可以假定 $b$ 是不降的。

那么原式可以化简为 $\sum_{k=1}^{L-1}k \times(L-k)\times (b_{k + 1}-b_{k})$。

设 $c_i=b_{i+1}-b_{i}$。会发现 $b_1=0$，那么原问题就变为了求一个长度为 $L-1$ 的序列 $c$ 满足 $\sum_{k=1}^{L-1}k\times (L-k) \times c_k=a_i$ 并且最小化 $\sum_{k} c_k$。

这可以用背包 dp 来解决。因为 $k\times (L-k) \le V $，所以 $k$ 是 $\sqrt{V}$ 级别的，总时间复杂度 $O(V \sqrt{V})$。

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
int n,l,a[MAXN],dp[MAXN];
signed main() {
	memset(dp,0x3f,sizeof dp);
	cin >> n >> l;
	dp[0] = 0;
	for(int k = 1;k * (l - k) <= 200000 && k <= l - 1;k++) 
		for(int i = k * (l - k);i <= 200000;i++)
			dp[i] = min(dp[i],dp[i - k * (l - k)] + 1);
	for(int i = 1;i <= n;i++) 
		cin >> a[i],
		cout << (dp[a[i]] > 1e9 ? -1 : dp[a[i]]) << endl;
	return 0;
}
```

---

## 作者：FReQuenter (赞：1)

两个求和和一个绝对值显然不方便算。所以把式子拆一拆：

首先假定 $B_1=0$，且 $B$ 单调不降。这样能使得 $\max(B)$ 最小。去绝对值：

$$\sum^{L-1}_{i=1}\sum^{L}_{j=i+1}(B_i-B_j)$$

两个求和可以通过拆贡献的方式去掉一个。

考虑到 $\max(B)$ 只和相邻两个数的差有关，且 $B_{i}-B_{j}=(B_{i}-B_{i-1})+(B_{i-1}-B_{i-2})+\cdots+(B_{j+1}-B_j)$，之后去数原式中包含 $B_{i+1}-B_i$ 的区间个数，即数对 $(l,r)(1\le l\le i,i+1\le r\le L)$ 的个数，原式化为：

$$\sum^{L-1}_{i=1}i(L-i)(B_{i+1}-B_{i})$$

现在只要求原式和为 $A_x$，最小的 $\sum^{L-1}_{i=1}(B_{i+1}-B_{i})$ 的值。

它可以看作一个无限背包：共 $L-1$ 种物品，每种物品大小为 $i(L-i)$，价值为 $1$，有无限个，求背包大小为 $A_x$ 的最小价值。直接 dp 就做完了。

复杂度 $O(N+\max(A)\sqrt{ \max(A)})$，因为 $i(L-i)\le \max(A)$，所以 $i$ 在 $\sqrt{\max(A)}$ 级别。即 dp 复杂度 $O(\max(A)\sqrt{ \max(A)})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,f[200005];
int Main(){
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    cin>>n>>l;
    for(int j=1;j*(l-j)<=200000&&j<l;j++){
        for(int i=j*(l-j);i<=200000;i++){
            f[i]=min(f[i],f[i-j*(l-j)]+1);
        }
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        cout<<(f[x]==0x3f3f3f3f?-1:f[x])<<'\n';
    }
    return 0;
}
signed main(){
    int T=Main();
    #ifdef LOCAL_PAUSE
    system("pause");
    #endif
    return T;
}
```

---

## 作者：Gapple (赞：0)

设值域是 $V$，且数列 $B$ 单调不降。为了让最大值最小，$B_1 = 0$，此时最大值为 $\sum \limits_{j = 1}^{L - 1} B_{j + 1} - B_j$。

把限制变一下形：

> **变形思路**：把数列 $B$ 放到数轴上。注意到，区间 $[B_j, B_{j + 1})$ 在和式中被加了 $j \cdot (L - j)$ 次。

$$
\begin{aligned}
    \sum_{j = 1}^{L - 1} \sum_{k = j + 1}^L |B_j - B_k|
    &= \sum_{j = 1}^{L - 1} \sum_{k = j + 1}^L B_k - B_j \\
    &= \sum_{j = 1}^L j \cdot (L - j) \cdot (B_{j + 1} - B_j) \\
    &= \sum_{j = 1}^{\lfloor L / 2 \rfloor} j \cdot (L - j) \cdot (B_{j + 1} - B_j + B_{L - j + 1} - B_{L - j})
\end{aligned}
$$

这是一个有 $\lfloor L / 2 \rfloor$ 个物品的完全背包，其中第 $i$ 个物品的体积是 $i \cdot (L - i)$、价值是 $1$，且总容量是 $A_i$。

这为什么不会 TLE 呢？因为体积是 $O(V^2)$ 的，而 $A_i$ 只有 $O(V)$。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int main()
{
    int q, n;
    cin >> q >> n;

    vector<int> query(q);

    for (auto& x : query)
        cin >> x;

    int mx = ranges::max(query);
    vector<i64> dp(mx + 1);

    for (int i = 1; i <= mx; ++i) {
        dp[i] = INF;

        for (int j = 1; i >= j * i64(n - j) && j <= (n >> 1); ++j)
            dp[i] = min(dp[i], dp[i - j * (n - j)] + 1);
    }

    for (auto x : query) {
        if (dp[x] >= INF)
            cout << "-1\n";
        else
            cout << dp[x] << '\n';
    }

    return 0;
}
```

时间复杂度：$O(V \sqrt{V})$。

---

## 作者：wfc284 (赞：0)

首先想到能不能用差分搞搞，但是给自己绕进去了 /kel

我们不妨给 $\{b_L\}$ 定个不降的序（如果打在数轴上，显然序和答案无关），于是可以拿掉绝对值。  
注意到这个和式（记其结果为 $x$ ）中每个 $b_i$ 的贡献系数 $c_i = 2i - L - 1$，于是有：
$$ x = \sum_{i = 1}^{L}b_ic_i $$
直接做不好处理最大值。$\{b_n\}$ 有序，想到 Abel 变换（记 $b_0=0,s_i = \sum_{j = i}^{L} c_j,d_i = b_i - b_{i-1}$
）：
$$ 
\begin{aligned}
x & = \sum_{i = 1}^{L}(b_i-b_{i-1})\sum_{j = i}^{L}c_j \\
& = \sum_{i = 1}^{L} d_is_i
\end{aligned}
$$
答案等价于最小化 $\sum d_i$。  
显然 $d_i\ge0$，且可以证明（~打表~） $s_i \ge 0$，于是就可以把上面的式子看做背包的过程，跑一遍背包即可。  

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
#define int long long
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)
//#define multi_cases 1

namespace Traveller {
	const int N = 2e5+2;
	
	int n, L;
	int sum[N], f[N];
	
	void main() {
		cin >> n >> L;
		for(int i = L; i >= 1; --i) sum[i] = sum[i+1] + 2*i - L - 1;
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;
		for(int i = 1; i <= L; ++i)
			for(int j = sum[i]; j <= 2e5; ++j)	//完全背包
				f[j] = min(f[j], f[j - sum[i]] + 1);
		for(int i = 1, a; i <= n; ++i) {
			scanf("%lld ", &a);
			printf("%lld\n", f[a] > 1e9 ? -1 : f[a]);
		}
	}
}

signed main() {
#ifdef filename
	FileOperations();
#endif
	
	signed _ = 1;
#ifdef multi_cases
	scanf("%d", &_);
#endif
	while(_--) Traveller::main();
	return 0;
}
```

关于时间复杂度：  
记值域为 $V$。  
我的代码中双重循环看起来什么没加，是 $O(VL)$ 的，但是注意到 `sum` 数组增速很快，是平方级别的，也就是说他会在 $O(\sqrt{V})$ 次就超出 $2 \times 10^5$，不进行二重循环。  
于是复杂度就是 $O(V \sqrt{V})$，可能带点常数。

---

## 作者：weilycoder (赞：0)

# 题意简述

给定 $L$，对于每个 $A_i$，构造一个长为 $L$ 的非负整数序列 $B$，使 $\sum_{j=1}^{L-1}\sum_{k=j+1}^{L}|B_j-B_k|=a_i$，同时最小化 $\max(B)$，输出 $\max(B)$。

# 思路

和式 $\sum_{j=1}^{L-1}\sum_{k=j+1}^{L}|B_j-B_k|$ 就是 $B$ 中元素两两间差的绝对值的和，为了最小化 $\max(B)$，同时方便计算，不妨令：
1. $B_1=0$；
2. 序列 $B$ 单调不降。

这时，和式变为：
$$\begin{aligned}\sum_{j=1}^{L-1}\sum_{k=j+1}^{L}|B_j-B_k|&=\sum_{j=1}^{L-1}\sum_{k=j+1}^{L}(B_k-B_j)\\&=\sum_{k=1}^{L-1}k(L-k)(B_{k+1}-B_k)\end{aligned}$$

不妨令 $C_i=B_{i+1}-B_i$，于是：
1. $C_i>0$；
2. $\sum_{k=1}^{L-1}k(L-k)(B_{k+1}-B_k)=\sum_{k=1}^{L-1}k(L-k)C_k$；
3. $\max(B)=\sum_{k=1}^{L-1}C_k$。

问题变为：构造 $C$ 使 $\sum_{k=1}^{L-1}k(L-k)C_k=A_i$，同时最小化 $\sum_{k=1}^{L-1}C_k$。

这个问题可以用类似背包问题的 dp 解决。

# code

```cpp
#include <cstring>
#include <iostream>
using namespace std;

const int M = 2e5 + 10;
int n, l;
int f[M];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  memset(f, 0x3f, sizeof(f));
  cin >> n >> l;
  f[0] = 0;
  for (int k = 1; k * (l - k) < M && k < l; ++k) {
    int w = k * (l - k);
    for (int i = w; i < M; ++i) f[i] = min(f[i], f[i - w] + 1);
  }
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    cout << (f[a] == 0x3f3f3f3f ? -1 : f[a]) << "\n";
  }
  return 0;
}
```

---

