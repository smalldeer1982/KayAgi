# A BIT of an Inequality

## 题目描述

给定序列 $a_n$，求满足以下条件的三元组 $(x,y,z)$ 的数量：

* $1\le x\le y\le z\le n$.

* $f(x,y)\oplus f(y,z)>f(x,z)$.

我们规定 $f(l,r)$ 表示 $a_l\oplus a_{l+1}\oplus\dots\oplus a_{r-1}\oplus a_{r}$，$\oplus$ 表示[异或和](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=ge_ala)。

## 说明/提示

对于全部数据，满足 $1\le t\le10^4$，$1\le n\le10^5$，$1\le a_i\le10^9$，$\sum n\le10^5$。

## 样例 #1

### 输入

```
3
3
6 2 4
1
3
5
7 3 7 2 1```

### 输出

```
4
0
16```

# 题解

## 作者：Lu_xZ (赞：9)

[Link](https://www.cnblogs.com/Luxinze/p/18162677#d-a-bit-of-an-inequality)

题意：定义 $f_{l, r} = \bigoplus\limits_{i = l}^r a_i$，求满足 $f_{x, y} \oplus f_{y, z} > f_{x, z}$ 的三元组个数。

化简原式：$f_{x, z} \oplus a_y > f_{x, z}$。

区间异或，转化为前缀异或，即 $s_{z} \oplus s_{x - 1} \oplus a_y > s_{z} \oplus s_{x - 1}$。

+ $a_y$ 对左式的影响取决于最高位 $j$（低位影响的总和小于最高位）。
+ 不等式成立当且仅当 $s_{x - 1} \oplus s_{z}$ 的第 $j$ 位为 $0$，即$s_{x - 1}$ 与 $s_{z}$ 的第 $j$ 位相同。

枚举 $a_y$，$s$ 中 $[1, y)$ 与 $[y, n]$ 的 $0/1$ 个数之积即为答案。

[submission](https://codeforces.com/contest/1957/submission/258344019)

---

## 作者：KSCD_ (赞：3)

### 题意
定义 $f(l,r)$ 为 $a_l$ 到 $a_r$ 的异或和，三元组 $(x,y,z)$ 合法当且仅当 $1\le x\le y\le z\le n$，且 $f(x,y)\oplus f(y,z)>f(x,z)$，求合法三元组的个数。
### 思路
展开式子，得到 $f(x,y)\oplus f(y,z)=f(x,z)\oplus a_y$，考虑枚举每个 $i$ 作为 $y$ 的贡献，问题转化为求满足 $x\le y\le z$ 且 $f(x,z)\oplus a_y>f(x,z)$ 的二元组 $(x,z)$ 数量。

考虑 $f(x,z)$ 要怎样才能异或上 $a_y$ 后变大。发现若 $a_y$ 二进制下最高位为第 $k$ 位，则 $f(x,y)$ 的第 $k$ 位为 $0$ 即合法，否则不合法。

考虑证明，显然 $a_y$ 最高位的值一定大于 $\frac{a_y}{2}$，所以 $f(x,z)$ 异或 $a_y$ 后，第 $k$ 位增加的值一定比后面的位总共减少的值大，结果一定增加；反之也一样。

那么需要快速求出某一位为 $0$ 的 $f(x,z)$ 数量，考虑使用前缀和。设 $b_i$ 为 $a_1$ 至 $a_i$ 的异或和，那么 $f(x,z)=b_{x-1}\oplus b_z$。特别地，有 $b_0=0$。

如此 $f(x,z)$ 第 $k$ 位为 $0$ 就转化为 $b_{x-1}$ 和 $b_z$ 的第 $k$ 位相同。因此再设 $s_{i,j}$ 表示 $b_0$ 到 $b_i$ 中第 $j$ 位为 $1$ 的个数，这样用乘法原理即可快速求出合法的 $(x,z)$ 个数。 
### 代码
```cpp
#include<iostream>
#include<cmath>
#define int long long
using namespace std;
const int N=1e5+10;
const int K=30+10;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') { s=s*10+ch-'0'; ch=getchar();}
	return s*w;
}
int T,n,ans,a[N],b[N],s[N][K],h[N];//h[i]表示a[i]的最高位，其余如上述 
signed main()
{
	T=read();
	while(T--)
	{
		n=read(),ans=0;
		for(int i=1;i<=n;i++) a[i]=read(),b[i]=b[i-1]^a[i],h[i]=floor(log2(a[i]));
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=30;j++) s[i][j]=s[i-1][j];
			int ct=0;
			while(b[i])
			{
				if(b[i]&1) s[i][ct]++;
				b[i]>>=1,ct++;
			}
		}//按思路维护各数组 
		for(int i=1;i<=n;i++) 
		{
			int ta=s[i-1][h[i]],tb=s[n][h[i]]-s[i-1][h[i]];//b[x-1]与b[z]同为1的数量 
			int tc=i-ta,td=n-i+1-tb;//同为0的数量，注意x=1时b[0]也要考虑进去 
			ans+=ta*tb+tc*td;//统计方案数 
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：破壁人罗辑 (赞：3)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF1957D)/[Codeforces](https://codeforces.com/problemset/problem/1957/D)

## 题目大意

给出一个数组 $a_i$，记 $b_i$ 为数组 $a_i$ 的前缀异或和（$b_i=a_1\oplus a_2\oplus\cdots\oplus a_i$），求满足 $1\leq x\leq y\leq z\leq n$ 且 $b_{x-1}\oplus b_z\oplus a_y>b_{x-1}\oplus b_z$ 的三元组 $(x,y,z)$ 的个数。这里 $\oplus$ 表示按位异或。

## 解题思路

设 $x$ 的二进制最高位是 $2^k$，则 $x\oplus y$ 和 $y$ 的二进制第 $k$ 位一定不同，且比 $k$ 更高的位一定相同。所以 $x\oplus y>y$ 等价于 $y$ 的二进制第 $k$ 位是 $0$。

若 $b_i\oplus b_j$ 的二进制第 $k$ 位是 $0$，则 $b_i$ 和 $b_j$ 的二进制第 $k$ 位相等。

我们对于每一个数 $i$，分别预处理出小于 $i$ 和大于等于 $i$ 满足 $b_j$ 的第 $\log\text{highbit}(a_i)$ 位是 $1$ 和 $0$ 的 $j$ 的个数，然后按照乘法原理组合计数即可。

预处理复杂度为 $O(n)$，求和复杂度也为 $O(n)$，所以整个程序的复杂度为 $O(n)$。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],sum[100001],hb[100001];long long tot[100001][31][2];
int main(){
	int T;scanf("%d",&T);while(T--){
		int n;scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",a+i);sum[i]=a[i]^sum[i-1];
			for(int j=0;j<=30;j++){
				tot[i][j][1]=tot[i-1][j][1]+(1&(sum[i]>>j));
				tot[i][j][0]=tot[i-1][j][0]+(!(1&(sum[i]>>j)));
				if(1&(a[i]>>j))hb[i]=j;
			}
		}
		long long ans=0;
		for(int i=1;i<=n;i++){
			ans+=(tot[i-1][hb[i]][0]+1)*(tot[n][hb[i]][0]-tot[i-1][hb[i]][0]);
			ans+=tot[i-1][hb[i]][1]*(tot[n][hb[i]][1]-tot[i-1][hb[i]][1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：_determination_ (赞：2)

首先考虑化简式子。

$ f(x, y) \oplus f(y, z) > f(x, z) $ 

$ f(x, z) \oplus a_y > f(x, z) $

至于这一步怎么得到的，把左边拆开把贡献重写一下即可。

之后发现左右两边有相同的东西，直接枚举 $y$。

注意到异或的性质是同 0 异 1，即当 $a_y$ 的最高位满足 $f(x,z)$ 在这一位是 0 的时候这个不等式才会成立。而这一位是 0 的前提就是 $f(1,x)$ 和 $f(1,z)$ 的那一位相等。

处理异或前缀和，将每个前缀和拆位做个前缀和，然后分讨那一位是 0 还是 1 把答案一加即可。

[Link](https://codeforces.com/contest/1957/submission/264567648)

---

## 作者：kimidonatsu (赞：2)

看了题解和官方的社论还是一头雾水，自己捋一遍。

罪魁祸首在于需要考虑同时考虑 $x, y, z$，那么考虑重写不等式：

$$f(x, a_y) \oplus a_y \gt f(x, z)$$

所以问题转化为枚举包含 $a_y$ 且在包含 $a_y$ 贡献时异或值减小的子数组的总数。

为了方便叙述，记异或值为 $s$。

何时 $s$ 会降低？思考后发现，在一个子数组 $[x, z](x \leq y \leq z)$ 中，如果 $a_y$ 被包含，只有当 $a_y$ 的某一位消掉了 $f(x, y - 1) \oplus f(y + 1, z)$ 中的现有位时，$s$ 才会随着降低。那么考虑 $a_y$ 中最高位非零位为 $i$，在 $f(x, y - 1)$ 中 $i = 1$ 而 $f(y + 1, z)$ 中为零时，带上 $a_y$ 就会减少子数组的 $s$，反之亦然。

好，现在对于前缀子数组 $[x, \cdots, y - 1]$ 和后缀子数组 $[y + 1, \cdots, z]$ 都具有 $i = 1 / 0$ 的子数组，我们可以通过包含 $a_y$ 来至少对答案增加贡献，注意到即使我们包含了 $a_y$，其他的较小位都与 $a_y$ 运算后被消掉的减量总值其实也是小于 $2^i$ 的，所以包含 $a_y$ 可以使我们对答案产生正的贡献。

代码坑点笔者基本踩完了，注意多维数组的维数定义次序，避免因空间连续性问题被卡常；还有记得警惕 `memset` 的时间复杂度。

GCC 编译器提供了 `__builtin_clz(unsigned int x)` 函数用以返回 $x$ 的二进制表示下从左起最高位开始连续 $0$ 的个数，与之类似的还有 `__builtin_ctz(unsigned int x)` 和 `__builtin_popcount(unsigned int x)` 等，但是注意到它们并不包含在 std 中。

[Submission](https://codeforces.com/contest/1957/submission/260244522)

---

## 作者：susenyang (赞：2)

### 题意

给定一个序列 $a_1,a_2,\cdots,a_n$，求出满足下述条件的三元组的数量：

- $1\leq x \leq y \leq z\leq n$
- $f(x,y) \operatorname{xor}f(y,z)\gt f(x,z)$

$f(x,y)$ 表示 $a_x  \operatorname{xor} a_{x+1} \operatorname{xor} \cdots \operatorname{xor} a_y$。

### 分析

首先考虑对 $f(x,y) \operatorname{xor}f(y,z)\gt f(x,z)$ 变形。上式等价于 $f(x,z) \operatorname{xor} a_y \gt f(x,z)$。（注意不能对等式两边同时异或一个相等的数，因为异或运算不满足分配律）

我们考察，什么时候 $a \operatorname{xor} b \gt a$。事实上，这与 $b$ 的最高位（二进制，下同）有关：当 $a$ 在 $b$ 的最高位处的二进制位为 $1$ 时，$a \operatorname{xor} b$ 在这一位的运算结果将是 $0$，从而 $a \operatorname{xor} b \lt a$。

举例：

- $a:(101101001)_ 2$
- $b:(000100110)_ 2$
- $a \operatorname{xor} b:(101001111) _ 2$

反之，如果要使 $a \operatorname{xor} b \gt a$，我们就需要使得 $a$ 在 $b$ 的最高位处的二进制位为 $0$。

基于上述讨论，很自然地想到拆位的思想，枚举 $a_i$ 的最高位。我们将最高位相同的 $a_i$ 放在一起求解。对于确定的 $now$（$now$ 表示 $a_i$ 的最高位是第 $now$ 位），我们可以构造一个序列 $b_i$，其中 $b_i$ 为 $a_i$ 的第 $now$ 位。

现在我们只需要处理这样一个问题：对于给定的序列 $b_i$ 和 $q$ 次询问，每一次询问给出一个下标 $y$，试求出有多少个区间 $[l,r]$，使得 $b_l  \operatorname{xor} b_{l+1} \operatorname{xor} \cdots \operatorname{xor} b_r = 0$，其中 $l\leq y \leq r$。观察数据范围可知，我们需要在 $O(q)$ 或者 $O(qlogn)$ 的时间内求解。

首先思考，什么样的区间是满足要求的区间。我们可以自然地想到维护 $b_i$ 中的 $1$。只有区间内的 $1$ 的个数会影响结果。因为 $l\leq y \leq r$ 这一性质并不是很好维护（也可能是笔者没有想到），所以我们考虑将区间分为 $[l,y-1]$ 与 $[y+1,r]$。

当 $b_y$ 为 $0$ 的时候，区间应当满足：$b_l \operatorname{xor} b_{l+1} \operatorname{xor} \cdots \operatorname{xor} b_{y-1}$ 与 $b_{y+1} \operatorname{xor} b_{y+2} \operatorname{xor} \cdots \operatorname{xor} b_{r}$ 同为 $1$ 或者同为 $0$。以维护 $b_{y+1} \operatorname{xor} b_{y+2} \operatorname{xor} \cdots \operatorname{xor} b_{r}$ 的结果为例：我们实际上需要求出，对于给定的 $y$，有多少 $r$ 可以使得 $b_{y+1} \operatorname{xor} b_{y+2} \operatorname{xor} \cdots \operatorname{xor} b_{r}$ 的结果为 $1$（或者为 $0$）。首先对于每一个下标 $i$，维护 $b_1,b_2,\cdots,b_i$ 中 $1$ 的个数的奇偶性，记为 $c_i$，如果 $b_1,b_2,\cdots,b_i$ 中 $1$ 的个数为奇数，则 $c_i = 1$；反之 $c_i=0$。接着对 $c_i = 1$ 的情况维护前缀和 $pre1$，其中 $pre1_i$ 表示在 $c_1,c_2,\cdots,c_i$ 中有多少个 $c_i$ 为 $1$。于是，我们可以通过 `pre1[n] - pre1[y]` 来查询有多少个下标 $i$，使得 $b_{y+1},b_{y+2},\cdots,b_i$ 中 $1$ 的个数为奇数。类似地，对 $c_i = 0$ 的情况维护前缀和 $pre0$，可以维护 $1$ 的个数为偶数的情况。

同理，我们也可以类似地维护后缀和 $suf1$ 与 $suf0$。现在只需要分类讨论一下 $b_y$ 为 $1$ 还是 $0$。如果 $b_y=1$，那么合法的 $[l,r]$ 满足 $[l,y-1]$ 中 $1$ 的个数与 $[y+1,r]$ 中 $1$ 的个数的奇偶性不同；反之，若 $b_y=0$，那么两个区间的奇偶性应当相同。

本题需要开 `long long`。

### 代码
```cpp
#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 10;

int a[N];
int highest_a[N];
std::vector<int> ind[40]; 
int pre0[N], pre1[N], suf0[N], suf1[N];
int precnt[N], sufcnt[N];

void solve()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= 32; i++)
        ind[i].clear();
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        highest_a[i] = log2(a[i]) + 1;
        ind[highest_a[i]].push_back(i);
    }
    pre0[n + 1] = 0, pre1[n + 1] = 0, suf0[n + 1] = 0, suf1[n + 1] = 0;
    precnt[n + 1] = 0, sufcnt[n + 1] = 0;
    int ans = 0;
    for (int now = 1; now <= 31; now++)
    {
        bool precnt1 = 0;
        for (int i = 1; i <= n; i++)
        {
            precnt[i] = precnt[i - 1] + (((a[i] >> (now - 1)) & 1) == 1);
            if (((a[i] >> (now - 1)) & 1) == 1)
                precnt1 ^= 1;
            pre0[i] = pre0[i - 1] + (precnt1 == 0);
            pre1[i] = pre1[i - 1] + (precnt1 == 1);
        }
        bool sufcnt1 = 0;
        for (int i = n; i >= 1; i--)
        {
            sufcnt[i] = sufcnt[i + 1] + (((a[i] >> (now - 1)) & 1) == 1);
            if (((a[i] >> (now - 1)) & 1) == 1)
                sufcnt1 ^= 1;
            suf0[i] = suf0[i + 1] + (sufcnt1 == 0);
            suf1[i] = suf1[i + 1] + (sufcnt1 == 1);
        }
        for (const auto &y : ind[now])
        {
            if ((((a[y] >> (now - 1)) & 1) ^ ((precnt[y - 1] % 2 == 0) ^ (sufcnt[y + 1] % 2 == 0))) == 1)
                ans += (pre0[n] - pre0[y - 1]) * (suf1[1] - suf1[y + 1]) + (pre1[n] - pre1[y - 1]) * (suf0[1] - suf0[y + 1]);
            else
                ans += (pre0[n] - pre0[y - 1]) * (suf0[1] - suf0[y + 1]) + (pre1[n] - pre1[y - 1]) * (suf1[1] - suf1[y + 1]);
        }
    }
    std::cout << ans << std::endl;
}

signed main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int _;
    std::cin >> _;
    while (_--)
        solve();
    return 0;
}
```

---

## 作者：2020kanade (赞：2)

前情提要：赛时犯唐开 C 没开 D，赛后速通。

我们对题目里面要求的合法三元组的第二个条件进行分析，直接考虑容斥：注意给的条件不等式左边相当于 $f(x,z) \operatorname{xor} a_{y}$，由于给出的数没有 $0$，不需要考虑相等，直接把不等号反向，我们考虑一个数异或什么数的时候会变小：

根据二进制下的 $01$ 串从高到低位的截断式贪心对比法则，我们直接分析最高位：如果异或数的最高位在被异或数的最高位之上，那么被异或数的最高位会变高，数会变大；否则，若两者最高位相同，异或得 $0$，数会变小；其他情况，按照截断式比较法则易得，如果异或数最高位在被异或数对应的位上为 $1$，那么异或后被异或数一定变小，否则一定变大。

按照上述结论，我们行祖宗之法进行拆位，枚举三元组中的 $y$，之后考虑 $a_y$ 的最高位在哪些 $f(x,z)$ 的结果中为 $1$。

这一部分的计算考虑一个后缀拼 $a_y$ 再拼一个前缀构成区间，设二进制第 $x$ 位上的 $f(l,r)$ 为函数 $g(x,l,r)$,我们预处理 
$$lc_{i,x}=\sum_{l\in[1,i-1]}g(x,l,i-1)=1$$
$$rc_{i,x}=\sum_{r\in[i+1,n]}g(x,i+1,r)=1$$
$$lz_{i,x}=\sum_{l\in[1,i-1]}g(x,l,i-1)=0$$
$$rz_{i,x}=\sum_{r\in[i+1,n]}g(x,i+1,r)=0$$

设 $a_i$ 的二进制最高位为 $hp_{i}$，则对于 $a_i$，包含它的仅违反第二条限制的区间数为 :
$$lc_{i,hp_i}\times rc_{i,hp_i}+lz_{i,hp_i}\times rz_{i,hp_i}+lz_{i,hp_i}\times(i\neq 1)+rz_{i,hp_i}\times(i\neq n)+1$$

那么，考虑所有满足第一条限制的区间数量为 $i\times(n-i+1)$，用后者减去前者累加入答案即可，这一部分时间复杂度是线性的。

最后考虑预处理的四个数组，我们有递推公式：

$g(x,i,i)=1$ 时：

$$ lc_{i,x}=lz_{i-1,x}+1 $$

$$ lz_{i,x}=lc_{i-1,x} $$

否则有：

$$ lc_{i,x}=lc_{i-1,x} $$

$$ lz_{i,x}=lz_{i-1,x}+1 $$

剩下两个数组考虑将数列反转后套用上述递推公式即可，公式不再写出。

总时间复杂度 $\Theta(n\log V)$。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=1e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
int hp[N],a[N];
ll lcnt[N][31],rcnt[N][31],lcnz[N][31],rcnz[N][31];
void solve()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		for(int j=30;j>=0;--j) if((a[i]>>j)&1)
		{
			hp[i]=j;break;
		}
	}
	for(int i=1;i<n;++i)
	{
		for(int j=0;j<=30;++j)
		{
			if((a[i]>>j)&1)
			{
				lcnz[i+1][j]=lcnt[i][j];
				lcnt[i+1][j]=lcnz[i][j]+1;
			}
			else
			{
				lcnz[i+1][j]=lcnz[i][j]+1;
				lcnt[i+1][j]=lcnt[i][j];
			}
		}
	}
	for(int i=n;i>1;--i)
	{
		for(int j=0;j<=30;++j)
		{
			if((a[i]>>j)&1)
			{
				rcnz[i-1][j]=rcnt[i][j];
				rcnt[i-1][j]=rcnz[i][j]+1;
			}
			else
			{
				rcnz[i-1][j]=rcnz[i][j]+1;
				rcnt[i-1][j]=rcnt[i][j];
			}
		}
	}
	ll ans=0,pans=0;
	for(int i=1;i<=n;++i)
	{
		int HeAP=hp[i];
		pans=1ll*(i-1+1)*(n-i+1);
		if(i!=n) pans-=(rcnz[i][hp[i]]);
		if(i!=1) pans-=(lcnz[i][hp[i]]);
		if(i!=n&&i!=1)pans-=(lcnt[i][HeAP]*rcnt[i][HeAP]+lcnz[i][HeAP]*rcnz[i][HeAP]);
		pans-=1;
		ans+=pans;
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;++i)
	{
		a[i]=hp[i]=0;
		for(int j=0;j<=30;++j)
		{
			lcnt[i][j]=rcnt[i][j]=lcnz[i][j]=rcnz[i][j]=0;
		}
	}
}
int main()
{
 	t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}

```

---

## 作者：hgckythgcfhk (赞：2)

题意可化为求一段区间的异或和异或上区间内某个数使得这个结果大于这个区间的异或和的方案数，对于形如对比 $a\operatorname{xor} b$ 与 $a$ 和 $b$ 比大小的问题，我不想废话，直接摆个链接，看[这篇文章](https://www.luogu.com.cn/article/ecu40xs6)。

现在，我们得到了一个看起来比较好处理的子问题，枚举每个 $y$ 求跨过 $y$ 且在 $a_y$ 最高位上异或和为 $0$ 的区间个数，或者说是异或和异或上 $a_y$ 在 $a_y$ 最高位为 $1$ 的个数。

这个东西不难想到维护以 $y$ 结尾的前缀异或和为 $0$ 和 $1$ 与以 $y$ 开头的后缀异或和为 $0$ 和 $1$ 的数量，具体过程自然语言不太好描述，因为描述出来其实只是对着程序翻译字面意思，不太好想到这么实现，但是看完程序就能瞬间理解，实现方式可以当作为一个 trick 记住以后就不用现推了。

这个题不难，但很值得做，没见过这个 trick 的话不一定会实现，没思考过异或比大小也不好做，见过就会写了，这个题能充分的体现我们刷题的意义，起码做完这个题我知道我做的题都不是无用功，trick 是需要积累的。

实现不难，进给出核心部分，省略了很多宏定义和头文件防止因为火车头导致无法过审，但不影响阅读。
```cpp
unsigned l[N][30][2],r[N][30][2];Bool(b[N],32);unsigned char a[N];
void solve(){int n;cin>>n;memset(a,31,n+1);
	for(int i=1,x;i<=n;++i){cin>>x;b[i]=bitset<32>(x);}
	for(int i=1;i<=n;++i)while(!b[i][a[i]]&&a[i])--a[i];
	for(int i=1;i<=n+1;++i)cle(l[i]),cle(r[i]);int ll ans=0;
	for(int i=1,j;i<=n;++i)for(j=0;j<30;++j)
		l[i][j][0]=l[i-1][j][0^b[i][j]],
		l[i][j][1]=l[i-1][j][1^b[i][j]],
		++l[i][j][b[i][j]];
	for(int i=n,j;i   ;--i)for(j=0;j<30;++j)
		r[i][j][0]=r[i+1][j][0^b[i][j]],
		r[i][j][1]=r[i+1][j][1^b[i][j]],
		++r[i][j][b[i][j]];
	for(int i=1;i<=n;++i)
		ans+=1ll*l[i][a[i]][0]*r[i][a[i]][1]+1ll*l[i][a[i]][1]*r[i][a[i]][0];
	cout<<ans<<'\n';}
```

---

## 作者：sbno333 (赞：2)

我们先想办法简化题目：

$f(x,y)\oplus f(y,z)=f(x,z)\oplus a_y$。

此时问题就变得简介易懂。

我们考虑按 $z$ 枚举，发现似乎不太可做。

于是我们按 $y$ 枚举，每次寻找多少区间 $l,r$ 使得 $f(l,r)\oplus a_y>f(l,r)$，且 $l\le y\le r$。

如果我们设 $f(l,r)=p$。

此时考虑 $p\oplus y>p$ 的条件，发现 $y\not=0$，且 $y$ 的最高为 $1$ 的位 $p$ 对应位为 $0$ 为充分必要条件。

于是自然地想到按位考虑，每次枚举寻找最高位，然后查找对应位区间异或为 $0$ 且包含当前位置的区间数量。

如果以当前为末尾的后缀与当前为开头的前缀的区间异或和为 $1$，则由于当前为 $1$，此时区间异或为 $0$。

我们可以前缀和后缀维护以当前为末尾对应位异或为 $0$ 和 $1$ 的数量，这是容易维护的。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int qz[100009][31][2];//f[i][j][k] 表示以 i 为末尾的的第 j 位异或为 k 的后缀数量
int hz[100009][31][2];//f[i][j][k] 表示以 i 为开头的的第 j 位异或为 k 的前缀数量
int a[100009];
void _main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=0;j<31;j++){
			qz[i][j][0]=qz[i][j][1]=hz[i][j][0]=hz[i][j][1]=0;
		}
	}
	for(int j=0;j<31;j++){
			qz[n+1][j][0]=qz[n+1][j][1]=hz[n+1][j][0]=hz[n+1][j][1]=0;
		}
	for(int i=1;i<=n;i++){
		for(int j=0;j<31;j++){
			bool s;
			s=a[i]&(1ll<<j);
			if(!s){
				qz[i][j][0]=qz[i-1][j][0],qz[i][j][1]=qz[i-1][j][1];//直接转移
			}else{
				qz[i][j][0]=qz[i-1][j][1],qz[i][j][1]=qz[i-1][j][0];//原来的都异或 1，所以交换
			}
			qz[i][j][s]++;//只有当前的也是方案
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=0;j<31;j++){
			bool s;
			s=a[i]&(1ll<<j);
			if(!s){
				hz[i][j][0]=hz[i+1][j][0],hz[i][j][1]=hz[i+1][j][1];
			}else{
				hz[i][j][0]=hz[i+1][j][1],hz[i][j][1]=hz[i+1][j][0];
			}
			hz[i][j][s]++;
		}
	}
	int ans;
	ans=0;
	for(int i=1;i<=n;i++){
		if(!a[i]){
			continue;
		}
		int ss;
		for(int j=30;j>=0;j--){
			if(a[i]&(1ll<<j)){
				ss=j;
				break;
			}
		}
		ans+=qz[i][ss][0]*hz[i][ss][1]+qz[i][ss][1]*hz[i][ss][0];//异或为 1 的方案数，此时为区间异或和为 0的方案数，即当前 y 对答案的贡献。
	}
	cout<<ans<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：__Creeper__ (赞：2)

### 题意 

定义 $f(l,r) = a_{l} \oplus a_{l+1} \oplus \cdots \oplus a_{r}$，求三元组 $(x, y, z)$ 满足 $l \le x \le y \le z \le n$，$f(x, y) \oplus f(y,z) < f(x,z)$ 的个数。

### 思路

由异或结合律 $(a \oplus b) \oplus c = a \oplus (b \oplus c)$，可以将原式变形为 $f(x, z) \oplus a_{y} > f(x, z)$。

考虑怎样使 $f(x, y) $ 异或上 $a_{y}$ 后变大。
设 $a_{y} $ 二进制下最高位为第 $k$ 位，值为$1$，若 $f(x,z)$ 第 $k$ 位为 $0$，第 $k$ 位的异或和就比原数第 $k$ 位大，即合法，否则不合法。

因为要快速求 $f(l, r)$ 的值，所以定义一个前缀和数组 $s$，$s_{i} = s_{i-1} \oplus a_{i}$，那么 $f(l,r) = s_{r} \oplus s_{l-1} $。

对于每一个数 $i$，分别预处理出小于 $i$ 和大于等于 $i$ 满足 $s_{j}$ 的第 $\log \textup{ highbit} (s_{i})$ 位是 $1$ 和 $0$ 的 $j$ 的个数，按照乘法原理组合计数。

### Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int a[N], s[N], h[N], tot[N][31][2];

signed main()
{
	int t;
	cin >> t;
	while ( t-- )
	{
		int n;
		cin >> n;
		for ( int i = 0; i <= 30; i++ )
		{
			tot[0][i][0] = 1;
			tot[0][i][1] = 0;
		}
		s[0] = 0;
		for ( int i = 1; i <= n; i++ )
		{  
			cin >> a[i];
			s[i] = s[i-1] ^ a[i];
			for ( int j = 0; j <= 30; j++ )
			{
				tot[i][j][1] = tot[i-1][j][1] + ( 1 & ( s[i] >> j ) ); 
				tot[i][j][0] = tot[i-1][j][0] + ( !( 1 & ( s[i] >> j ) ) ); 
			}
		}
		int ans = 0;
		for ( int i = 1; i <= n; i++ )
		{
			int k = 30;
			while ( !(a[i] & ( 1 << k )) ) 
			{
				k--;
			}
			ans += ( tot[i-1][k][1] ) * ( tot[n][k][1] - tot[i-1][k][1] );
			ans += ( tot[i-1][k][0] ) * ( tot[n][k][0] - tot[i-1][k][0] );
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

[CF1957D A BIT of an Inequality](https://codeforces.com/contest/1957/problem/D)

给定 $a_{1\ldots n}$，记 $f(l,r)=\bigoplus_{i=l}^{r} a_i$，求 $\sum_{x=1}^{n}\sum_{y=x}^{n}\sum_{z=y}^{n} [f(x,y) \oplus f(y,z)>f(x,z)]$。

$\sum n\le 10^5$。

---

观察大于号左边，$a_y$ 被多异或了一次，将原式子转化成 $f(x,z)\oplus a_y>f(x,z)$。

看到异或，首先想到按位拆分。考虑 $a_y$ 的每一位对 $f(x,z)$ 的大小有什么贡献？若 $a_y$ 的最高位 $k$ 对 $f(x,z)$ 产生正的贡献，不论 $0\sim k-1$ 位产生的贡献之正负，最终的总贡献一定是正的。

什么情况下第 $k$ 位会产生贡献？若 $f(x,z)$ 的第 $k$ 位是 $1$，异或之后变成了 $0$，反而变小了。因此我们记 $s_i=\bigoplus_{j=1}^{i} a_j$，则 $f(x,z)=s_z\oplus s_{x-1}$，故 $f(x,z)$ 的第 $k$ 位是 $0$ 当且仅当 $s_{x-1}$ 和 $s_z$ 的第 $k$ 位相同。

考虑枚举 $a_y$，那么有多少组 $x$ 和 $z$ 能满足条件呢？根据乘法原理，我们分别求出 $a_y$ 左右两边 $0/1$ 的个数并相乘即可。

- 注意边界：$x-1\le y-1$，所以左区间的右端点不能取到 $y$，即应查询 $[1,y-1]$ 和 $[y,n]$。
- 注意左区间的左端点为第 $0$ 个位置，因为空区间也等价于一个 $0$。

---

## 作者：DerrickLo (赞：0)

考虑将条件转化为 $f(x,z)\oplus a_y>f(x,z)$，若 $a_y$ 的最高位是 $k$，那么很显然这个条件的实现当且仅当在第 $k$ 位上 $f(x,z)$ 是 $0$。

那么显然枚举 $y$，那么二元组 $(x,z)$ 就满足 $f(x,z)$ 的第 $k$ 位为 $0$，记 $s_{i,k}$ 表示第 $k$ 维上前 $i$ 个数的异或和，那么即统计有多少个二元组 $(x,z)$ 满足 $x\le y\le z$ 且 $s_{x-1,k}=s_{z,k}$，这可以使用前缀和解决。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[100005],sum[35][100005],sum1[35][100005],sum0[35][100005];
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=30;i++){
			sum0[i][0]=1;
			for(int j=1;j<=n;j++)sum[i][j]=sum[i][j-1]^((a[j]&(1ll<<(i-1)))!=0);;
			for(int j=1;j<=n;j++)sum1[i][j]=sum1[i][j-1]+(sum[i][j]==1);
			for(int j=1;j<=n;j++)sum0[i][j]=sum0[i][j-1]+(sum[i][j]==0);
		}
		int ans=0;
		for(int i=1;i<=n;i++){
			int now=31;
			for(int j=30;j;j--)if(a[i]&(1ll<<(j-1))){
				now=j;
				break;
			}
			ans+=sum0[now][i-1]*(sum0[now][n]-sum0[now][i-1]);
			ans+=sum1[now][i-1]*(sum1[now][n]-sum1[now][i-1]);
		}
		cout<<ans<<"\n";
		
	}
}
```

---

