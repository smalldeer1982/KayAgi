# Binary Subsequence Value Sum

## 题目描述

[Last | Moment - onoken](https://www.youtube.com/watch?v=l_fXX3Y0Pis)

对于一个二进制字符串 $^{\text{∗}}$ $v$，其分数定义为以下值的最大值：

$$ \max_{0 \leq i \leq |v|} \left[ F(v, 1, i) \cdot F(v, i+1, |v|) \right] $$

其中 $F(v, l, r) = r - l + 1 - 2 \cdot \operatorname{zero}(v, l, r)$，这里 $\operatorname{zero}(v, l, r)$ 表示子串 $v_lv_{l+1}\ldots v_r$ 中 $\mathtt{0}$ 的数量。若 $l > r$，则 $F(v, l, r) = 0$。

给定一个长度为 $n$ 的二进制字符串 $s$ 和一个正整数 $q$。你需要处理 $q$ 次修改查询。

每次查询给出一个整数 $i$（$1 \leq i \leq n$），你必须翻转 $s_i$（将 $\mathtt{0}$ 改为 $\mathtt{1}$ 或 $\mathtt{1}$ 改为 $\mathtt{0}$）。每次修改后，计算 $s$ 所有非空子序列 $^{\text{†}}$ 的分数之和。

由于结果可能很大，请输出对 $998\,244\,353$ 取模后的答案。注意所有修改是持久化的。

$^{\text{∗}}$ 二进制字符串是仅由 $\mathtt{0}$ 和 $\mathtt{1}$ 组成的字符串。

$^{\text{†}}$ 二进制字符串 $x$ 是 $y$ 的子序列，当且仅当 $x$ 可以通过删除 $y$ 中的若干字符（可能为零或全部）得到。

## 说明/提示

### 示例解释

第一个测试用例中，首次修改后 $s = \texttt{110}$。所有子序列的分数计算如下：

| 索引       | 子序列 | 分数 |
|------------|--------|------|
| 1          | 1      | 0    |
| 2          | 1      | 0    |
| 1, 2       | 11     | 1    |
| 3          | 0      | 0    |
| 1, 3       | 10     | 0    |
| 2, 3       | 10     | 0    |
| 1, 2, 3    | 110    | 0    |

总和为 $0 + 0 + 1 + 0 + 0 + 0 + 0 = 1$。

第二次修改后 $s = \texttt{111}$。所有子序列的分数计算如下：

| 索引       | 子序列 | 分数 |
|------------|--------|------|
| 1          | 1      | 0    |
| 2          | 1      | 0    |
| 1, 2       | 11     | 1    |
| 3          | 1      | 0    |
| 1, 3       | 11     | 1    |
| 2, 3       | 11     | 1    |
| 1, 2, 3    | 111    | 2    |

总和为 $0 + 0 + 1 + 0 + 1 + 1 + 2 = 5$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3 2
010
1
3
10 3
0101000110
3
5
10
24 1
011001100110000101111000
24```

### 输出

```
1
5
512
768
1536
23068672```

# 题解

## 作者：Gold14526 (赞：14)

$\rm Problem:$[Binary Subsequence Value Sum](https://www.luogu.com.cn/problem/CF2077C)

源神场给的组合数学基础式子练习题。

### 题意

对于一个 $01$ 串 $v$，设 $\operatorname{zero}(v,l,r)$ 表示 $v$ 中区间 $[l,r]$ 中 $0$ 的数量，设 $F(v,l,r)=r-l+1-2\operatorname{zero}(v,l,r)$，特别的，当 $l>r$ 时，$F(v,l,r)=0$。

定义 $01$ 串 $v$ 的权值为：

$$\max_{i=1}^{|v|}F(v,1,i-1)\times F(v,i,|v|)$$

现在给出一个长度为 $n$ 的 $01$ 串 $s$，$q$ 次修改，每次反转一位 $01$，每次修改后回答 $s$ 所有子序列的权值和，答案对 $998244353$ 取模。

$n,q\le2\times10^5$。

### 做法

需要用到的两个式子：$\sum_{i=0}^nC_{n}^ii=n2^{n-1}$,$\sum_{i=0}^nC_n^ii^2=n(n+1)2^{n-2}$。

（如果你并不理解上述两个式子，可以看文章最后的证明部分）

首先我们发现 $F(v,l,r)$ 实际就是区间 $[l,r]$ 内 $1$ 的个数减 $0$ 的个数，于是 $F(v,1,i-1)+F(v,i,|v|)=F(v,1,|v|)$。

设 $F(v,1,|v|)=\delta_v$，我们知道两个数的和一定时两者差越小乘积越大，所以 $v$ 的权值等于 $\lfloor\frac{\delta_v}{2}\rfloor\lceil\frac{\delta_v}{2}\rceil$。

这个一看就比较难受，按 $\delta_v$ 的奇偶性讨论一下：

- 当 $\delta_v$ 为奇数时，上式等于 $\frac{(\delta_v-1)(\delta_v+1)}{4}$
- 当 $\delta_v$ 为偶数时，上式等于 $\frac{\delta_v^2}{4}$

所以上述式子等于 $\frac{\delta_v^2-[\delta_v\equiv1\pmod2]}{4}$。

发现 $\delta_v$ 为奇数当且仅当 $v$ 的长度为奇数，所以我们可以算出需减一的总数量为 $2^{n-1}$，即长度为奇数的子序列数量，于是我们只需解决每个子序列的 $\delta_v$ 平方和。

设 $cnt_{0/1}$ 表示 $v$ 中 $0/1$ 的数量，那么 $\delta_v^2=(cnt_0-cnt_1)^2=cnt_0^2+cnt_1^2-2cnt_0cnt_1$。

设 $tot_{0/1}$ 表示 $s$ 中 $0/1$ 的个数。

我们分别解决 $cnt_{0/1}^2$ 之和以及 $cnt_0cnt_1$ 之和：

---

#### $cnt_{0/1}^2$ 之和

以 $cnt_0^2$ 为例，$cnt_1^2$ 同理。

显然答案为 $2^{tot_1}\sum_{i=0}^{tot_0}C_{tot_0}^ii^2$，即我们枚举 $cnt_0$ 的大小，然后算有这么多 $0$ 的子序列个数乘 $cnt_0^2$。

根据开头提到的 $\sum_{i=0}^nC_n^ii^2=n(n+1)2^{n-2}$ 可以得到上式等于 $2^{tot_1}tot_{0}(tot_0+1)2^{tot_0-2}=tot_{0}(tot_0+1)2^{n-2}$。

那么同理，$cnt_1^2$ 之和等于 $tot_1(tot_1+1)2^{n-2}$。

#### $cnt_0cnt_1$ 之和

显然答案为 $\sum_{i=0}^{tot_0}\sum_{j=0}^{tot_1}C_{tot_0}^iC_{tot_1}^jij=\sum_{i=0}^{tot_0}C_{tot_0}^ii\times\sum_{j=0}^{tot_1}C_{tot_1}^jj$。

用开头提到的 $\sum_{i=0}^nC_n^ii=n2^{n-1}$ 可以得到上式等于 $tot_0tot_12^{n-2}$。

---

那么答案就等于：

$$\frac{(\sum cnt_0^2)+(\sum cnt1^2)-2(\sum cnt_0cnt_1)-2^{n-1}}{4}$$

等于（为了简洁，以下以 $x,y$ 分别代表 $cnt_0,cnt_1$）：

$$\frac{x(x+1)2^{n-2}+y(y+1)2^{n-2}-xy2^{n-1}-2^{n-1}}{4}$$

在修改过程中维护 $tot_0$ 和 $tot_1$，然后直接输出上式即可，时间复杂度 $O(\sum n+q)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return x;
}
void print(cint x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
void princh(cint x,const char ch)
{
	print(x);
	putchar(ch);
}
cint mod=998244353,iv2=499122177,iv4=1ll*iv2*iv2%mod;
int n,q,c[2];
bool a[200001];
int pw[400001];
void init()
{
	pw[0]=1;
	for(int i=1;i<=4e5;++i)
	{
		pw[i]=(pw[i-1]<<1)%mod;
	}
}
int PW(cint x)
{
	if(x==-1)return iv2;
	if(x==-2)return iv4;
	return pw[x];
}
int calc(cint x,cint y)
{
	return 1ll*iv4*(1ll*x*(x+1)%mod*PW(x+y-2)%mod+1ll*y*(y+1)%mod*PW(x+y-2)%mod+(mod-1ll*x*y%mod*PW(x+y-1)%mod)%mod+(mod-PW(x+y-1)))%mod;
}
void query()
{
	cint x=read();
	--c[a[x]];
	a[x]^=1;
	++c[a[x]];
	princh(calc(c[0],c[1]),'\n');
}
void solve()
{
	n=read();
	q=read();
	char ch=getchar();
	while(ch!='0'&&ch!='1')ch=getchar();
	c[0]=c[1]=0;
	for(int i=1;i<=n;++i)
	{
		a[i]=ch-'0';
		++c[a[i]];
		ch=getchar();
	}
	while(q--)query();
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	init();
	int T=read();
	while(T--)solve();
	return 0;
}

```

### 证明

#### 证明 $\sum_{i=0}^nC_n^ii=n2^{n-1}$

$i=C_i^1$，则原式等于 $\sum_{i=0}^nC_n^iC_i^1$，考虑其组合意义，即先从 $n$ 个元素中选若干个，再从若干个元素里选出一个的方案数。那我们先选这一个，有 $n$ 种方案，再从剩下 $n-1$ 个元素中选出若干个，有 $2^{n-1}$ 种方案，所以是 $n2^{n-1}$。

#### 证明 $\sum_{i=0}^nC_n^ii^2=n(n+1)2^{n-2}$

考虑 $i^2=i+i(i-1)=i+2\times\frac{i(i-1)}{2}=C_i^1+2C_i^2$，则原式等于 $\sum_{i=0}^nC_n^iC_i^1+2C_n^iC_i^2$，等于 $n2^{n-1}+2\sum_{i=0}^nC_n^iC_i^2$，则我们只需解决 $\sum_{i=0}^nC_n^iC_i^2$。

考虑组合意义，即从 $n$ 个元素里选出若干个，再从若干个元素里选出两个的方案数。那我们先选出这两个，有 $\frac{n(n-1)}{2}$ 种方案，然后再从剩下的元素中选出若干个，有 $2^{n-2}$ 种方案，所以有 $n(n-1)2^{n-3}$ 种方案。

则原式等于 $n2^{n-1}+2\times n(n-1)2^{n-3}=2n\times 2^{n-2}+n(n-1)\times2^{n-2}=n(n+1)2^{n-2}$。

---

## 作者：WaterSun (赞：3)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18772052)

感谢此题将我送上 Master。

# 思路

注意观察 $F(v,l,r)$ 的定义，容易将其刻画成 $v_{l \sim r}$ 中 $1$ 的数量减去 $0$ 的数量。

不妨将 $1$ 的权值记作 $1$，$0$ 的权值记作 $-1$，令这个序列的权值序列为 $val_i$。则对于一个子序列 $v$ 的得分是 $\lfloor \frac{S^2}{4} \rfloor$，其中 $S = \sum val_i$。考虑如下证明：因为无论选择哪一个点作为分界点其左右两边的 $F$ 函数的和不变，由均值不等式得到该函数的最大值。

那么问题转化为了求所有子序列的 $\lfloor \frac{S^2}{4} \rfloor$ 的和，将下取整去掉，即：

$$
\frac{\sum_{T}{\sum S_T^2 - S_T \bmod 2}}{4}
$$

注意到 $val_i$ 的取值并不会影响 $\sum_T (S_T \bmod 2)$ 的结果，因此原式等价于：

$$
\frac{\sum_{T}{\sum S_T^2 - |T| \bmod 2}}{4} = \frac{(\sum_{T} \sum S_T^2) - 2^{n - 1}}{4}
$$

接下来只需要维护所有子序列的 $\sum S^2$，即 $\sum_T(\sum_{x \in T} val_x)^2$。考虑拆掉平方项，得：

$$
\sum_T(\sum_{x \in T}val_x^2 + 2\sum_{x,y \in T \wedge x < y}val_x val_y)
$$

分别计算 $\sum_T\sum_{x \in T}val_x^2$ 和 $2\sum_T\sum_{x,y \in T \wedge x < y}val_x val_y$。

- 对于前者，注意到 $\forall i \in T,val_i \in \{1,-1\}$，因此无论给定字符串是什么 $val_i^2$ 恒为 $1$。即计算 $\sum_T |T|$，因为 $T$ 要非空，因此贡献为 $n \times 2^{n - 1}$。
- 对于后者，考虑计算每一对 $i < j$ 的贡献和，即计算 $2 \sum_{i < j}2^{n - 2}val_i val_j = 2^{n - 1}\sum_{i < j}val_i val_j$。接下来只需化简 $\sum_{i < j}val_i val_j$，注意到如下等式：

$$
(\sum_{i = 1}^{n}val_i)^2 = \sum_{i = 1}^{n}val_i^2 + 2\sum_{i < j}val_i val_j
$$

即 $sum = \sum_{i = 1}^{n}val_i$，则移项易得 $\sum_{i < j}val_i val_j = \frac{sum^2 - n}{2}$。

整理一下可以得到 $\sum S^2 = n \times 2^{n - 1} + 2^{n - 2} \times (sum^2 - n) = 2^{n - 2} \times (sum^2 + n)$。答案为：$\frac{2^{n - 2} \times (sum^2 + n) - 2^{n - 1}}{4}$。

动态维护 $sum$ 是容易的。~~其实完全可以做到区间修改。~~

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define Add(a,b) (((a) + (b)) % mod)
#define Sub(a,b) (((a) - (b) + mod) % mod)
#define Mul(a,b) ((a) * (b) % mod)
#define chMul(a,b) (a = Mul(a,b))

using namespace std;

const int mod = 998244353;
const int inv = 748683265;
const int N = 2e5 + 10;
int n,q;
int val[N];
char s[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline int qmi(int a,int b){
    int res = 1;
    while (b){
        if (b & 1) chMul(res,a);
        chMul(a,a); b >>= 1;
    } return res;
}

inline void solve(){
    n = read(),q = read();
    scanf("%s",s + 1);
    int sum = 0;
    for (re int i = 1;i <= n;i++) sum += (val[i] = (s[i] == '1') ? 1 : -1);
    while (q--){
        int x; x = read();
        sum -= (2 * val[x]); val[x] = -val[x];
        printf("%lld\n",Mul(Sub(Mul(qmi(2,n - 2 + mod - 1),Add(Mul(sum,sum),n)),qmi(2,n - 1)),inv));
    }
}

signed main(){
    int T; T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：biyi_mouse (赞：1)

首先注意到 $F(v, l, r)$ 其实就是 $l \sim r$ 中 $1$ 的数量减去 $0$ 的数量。

接着考虑令 $S = F(v, 1, n) = F(v, 1, i) + F(v, i + 1, n)$，那么 $F(v, 1, i) \times F(v, i + 1, n)$ 的最大值就是 $\lfloor \frac{S}{2} \rfloor \lceil \frac{S}{2} \rceil$。

这种形式不好处理，可以分 $S$ 的奇偶性讨论。当 $S$ 为奇数时就是 $\frac{(S + 1)(S - 1)}{4}$，即 $\frac{S^2 - 1}{4}$；当 $S$ 为偶数时就是 $\frac{S^2}{4}$。所以我们可以把最大值记作 $\frac{S^2 - S \bmod 2}{4}$。

接下来要计算所有子序列的分数和（下文为了方便先不除以 $4$），可以发现对于所有长度为奇数的串都减一，一共要剪掉 $2^{n - 1}$。然后我们只需要算 $\sum S^2$ 即可。

记 $cnt_0$ 为一个子序列中 $0$ 的数量，$cnt_1$ 为一个子序列中 $1$ 的数量，则 $\sum S^2 = \sum(cnt_1 - cnt_0)^2 = \sum(cnt_0^2 + cnt_1 ^2 - 2cnt_0cnt_1)$。

为了计算上面的式子，我们可以分别求出 $\sum cnt_0^2$ 和 $\sum cnt_1^2$ 和 $\sum cnt_0cnt_1$。

下文记 $s_0$ 为整个序列中 $0$ 的数量，$s_1$ 同理。

先考虑 $\sum cnt_0^2$。为 $1$ 的位可以任意取，然后枚举选多少个 $0$，答案是 $2^{s_1}\sum_{i = 0}^{s_0} C_{s_0}^{i} \times i^2$。

循环跑组合数显然烂完了，但是有一个组合数公式是 $\sum_{i = 0}^{n}C_{n}^{i}i^2 = n(n+1)2^{n - 2}$。原理是 $i^2$ 可以看作 $i(i - 1) + i$，也就是 $2C_{i}^{2} + C_{i}^{1}$，那么原式就是 $2\sum_{i = 0}^{n}C_{n}^{i}C_{i}^{2} + \sum_{i = 0}^{n}C_{n}^{i}C_{i}^{1}$。对于右边的式子，是从 $n$ 个数中选 $i$ 个再从 $i$ 个数中选 $1$ 个，可以看作先选 $1$ 个，再从剩下 $n - 1$ 个中随便选，所以是 $n\times 2^{n - 1}$。左边的式子同理是 $n(n-1)\times 2^{n - 2}$，二者相加就得到了上述公式。

所以 $\sum cnt_0^2 = 2^{s_1}s_0(s_0 + 1)2^{s_0 - 2} = s_0(s_0 + 1)2^{n - 2}$，$\sum cnt_1^2$ 同理可得等于 $s_1(s_1 + 1)2^{n - 2}$。

接着考虑 $\sum cnt_0cnt_1$，思考过程与上述类似，应该是 $\sum_{i = 0}^{s_0} \sum_{j = 0}^{s_1}C_{s_0}^{i}C_{s_1}^{j} \times ij = \sum_{i = 0}^{s_0} C_{s_0}^{i} \times i \times (\sum_{j = 0}^{s_1} C_{s_1}^{j} \times j)$。

公式的推导过程中我们其实也得到了 $\sum_{i = 0}^{n}C_{n}^{i}i = n\times 2^{n - 1}$，代入原式就是 $s_0s_1 2^{n - 2}$。

综上，$\sum S^2 = s_0(s_0 + 1)2^{n - 2} + s_1(s_1 + 1)2^{n - 2} - s_0s_1 2^{n - 1}$。

所以答案就是 $\frac{\sum S^2 - 2^{n - 1}}{4} = \frac{2^{n - 2}[(s_0 - s_1) ^2 + s_0 + s_1 - 2]}{4}$。我们动态维护 $s_0$ 和 $s_1$ 然后直接代入公式就做完了。

---

## 作者：wishapig (赞：1)

#### 题目大意

对一个 $0,1$ 串 $v$，记
$$
f(v)=\max_{i=0}^{|v|}\{F(v,1,i)\times F(v,i+1,|v|)\}\\
F(v,l,r)=r-l+1-2\times zero(v,l,r)
$$
给出一个长为 $n$ 的 $0,1$ 串 $s$，支持：

- 将一个位置 $0/1$ 翻转
- 求出 $s$ 所有子序列的 $f$ 值之和，输出答案对 $998244353$ 取模的结果

$1\le T\le 10^4,1\le n,q,\sum n,\sum q\le 2\times 10^5$

---

显然这个 $F$ 代表的就是区间内 $1$ 个数减去 $0$ 个数，因此可以前缀和，用 $p_r-p_{l-1}$ 来表示

那么来看一下一个长度为 $n$ 的字符串如何求出其 $f$ 值：
$$
\begin{aligned}
f(v)&=\max_{i=1}^{n-1}\{(p_i-p_0)(p_n-p_i)\}\\
&=\max_{i=1}^{n-1}\{-p_i^2+p_np_i\}
\end{aligned}
$$
这个二次函数的最大值在对称轴 $\dfrac{p_n}{2}$ 处取到，而这不一定是整数，因此还要分情况讨论一下：

- 若 $p_n$ 为偶数，那么对称轴位置为整数，可以发现，由于 $|p_i-p_{i-1}|=1$，因此在 $1\sim n$ 中一定有一个 $p_i=\dfrac{p_n}{2}$，于是 $f(v)=\dfrac{p_n^2}{4}$

- 若 $p_n$ 为奇数，那么最优位置应当为 $\dfrac{p_n-1}{2}$，与上面的分析相同，一定存在一个 $p_i$ 可以取到这个位置，此时有 $f(v)=\dfrac{p_n^2-1}{4}=\dfrac{p_n^2}{4}-\dfrac{1}{4}$

发现 $\dfrac{p_n^2}{4}$ 这个部分是相同的，于是可以对所有子序列求出 $\dfrac{p_n^2}{4}$，再求出所有 $p_n$ 为奇数的子序列个数 $c$，减去 $\dfrac{c}{4}$ 即可

同时容易发现 $p_n$ 的奇偶性与 $n$ 相同，因此 $c=\binom{n}{1}+\binom{n}{3}+\binom{n}{5}+\cdots$

于是问题就变成了求前面这个部分

由于有单点修改，因此考虑使用数据结构进行维护，可以使用线段树，每个节点维护区间长度 $l$，区间内所有子序列的 $s_1=\sum p,s_2=\sum p^2$ 即可

合并与修改都是容易的

```cpp
struct dat{
	int len;
	int ans1,ans2;
} tr[N<<2];
dat operator + (const dat& a, const dat& b){
	return {a.len+b.len,
			(a.ans1+b.ans1+1ll*a.ans1*pw[b.len]+1ll*b.ans1*pw[a.len])%mod,
			(a.ans2+b.ans2+1ll*a.ans2*pw[b.len]+2ll*a.ans1*b.ans1+1ll*b.ans2*pw[a.len])%mod};
}
//pw[i]=2^i-1
```

---

## 作者：未来姚班zyl (赞：1)

官解把式子化成了：

- $\sum {\frac{(cnt_0-cnt_1)^2}{4} - \frac{((cnt_0-cnt_1) \bmod 2)}{4}}$

到这里其实已经做完了。

不管分母 $4$，求分子和最后除以 $4$ 即可。

后面一段其实就是 $len\bmod 2$，其值是 $2^{n-1}$。

前面那一段把分子拆开，就变成了 $\sum cnt_0^2+\sum cnt_1^2-2\sum cnt_0cnt_1$，经典矩阵维护即可，用线段树维护单点修改，复杂度 $O(n+q\log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
//#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=2e5+5,M=1e6+5,inf=(1LL<<29)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m;
string s;
struct mac{
	int a[6][6];
	mac(){
		memset(a,0,sizeof(a));
	}
	mac friend operator*(mac a,mac b){
		mac c;
		rep(i,0,5)rep(k,0,5)if(a.a[i][k])rep(j,0,5)add(c.a[i][j],mul(a.a[i][k],b.a[k][j]));
		return c; 
	}
}K1,K0,S,Ans;
mac xd[N<<2];
inline void getup(int x){
	xd[x]=xd[L]*xd[R];
}
inline void build(int x,int l,int r){
	if(l==r)return xd[x]=s[l]=='0'?K0:K1,void();
	build(lc),build(rc),getup(x);
}
inline void modify(int x,int l,int r,int p){
	if(l==r)return xd[x]=s[l]=='0'?K0:K1,void();
	p<=mid?modify(lc,p):modify(rc,p),getup(x);
}
inline void Main(){
	n=read(),m=read();
	cin>>s,s='#'+s;
	build(Root);
	int iv4=INV(4);
	while(m--){
		int ps=read();
		if(s[ps]=='1')s[ps]='0';
		else s[ps]='1';
		modify(Root,ps);
		Ans=S*xd[1];
		int Tot=Add(Ans.a[0][0],Ans.a[0][2]);
		red(Tot,mul(2,Ans.a[0][5]));
		red(Tot,qp(2,n-1));
		cout <<mul(Tot,iv4)<<'\n';
	}
}
signed main(){
	S.a[0][4]=1;
	rep(i,0,5)K0.a[i][i]=K1.a[i][i]=2;
	K1.a[1][0]=K0.a[3][2]=2;
	K1.a[4][0]=K0.a[4][2]=1;
	K1.a[4][1]=K0.a[4][3]=1;
	K1.a[3][5]=K0.a[1][5]=1;
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：冷却心 (赞：1)

容易发现这个 $F(s,l,r)$ 事实上就是字符串 $s$ 中 $[l,r]$ 这一段的 $\mathtt{1}$ 的个数减去 $\mathtt{0}$ 的个数。先考虑一个字符串怎么求出分数。

我们需要找到一个分界点 $p$，然后把左边的 $F$ 值和右边的 $F$ 值乘起来要求最大。观察到左右 $F$ 值之和为定值，即整个字符串 $\mathtt{1}$ 的个数减去 $\mathtt{0}$ 的个数。于是猜想当左右 $F$ 值各取一半时最大，或者当和为奇数的时候一个是一半上取整，一个是一半下取整是最大。答案确实如此，因为一定能找到一个 $p$，使得左右的 $F$ 值满足这个。简单说明一下，能发现 $p$ 每向后移动一位，左边的 $F$ 值只会加一或减一，变化是连续的，因此一定能找到一个 $p$ 使得左边的 $F$ 值为一半，此时右边也相应满足。于是记 $c_0$ 表示字符串 $\mathtt{0}$ 的个数，$c_1$ 表示字符串 $\mathtt{1}$ 的个数，则价值为：

$$\left\lfloor\frac{(c_1-c_0)^2}{4}\right\rfloor=\frac{(c_1-c_0)^2}{4}-\frac{(c_1-c_0)\bmod 2}{4}.$$

你能发现一个序列的价值只和 $\mathtt{01}$ 个数之差有关。我们再来计算原序列的子序列的价值之和。我们考虑记 $\mathtt{0}$ 权值为 $-1$，$\mathtt{1}$ 权值为 $1$，然后一个字符串的价值就是其权值之和平方的下取整。对于一个 $c_0$ 个 $\mathtt{0}$，$c_1$ 个 $\mathtt{1}$ 的字符串，我们统计它价值为 $k$ 的子序列个数。我们枚举他选择了 $i$ 个 $\mathtt{0}$，那么此时他选择了 $k+i$ 个 $\mathtt{1}$，那么总子序列个数就是：

$$\sum_{i=0}^{c_0}\binom{c_0}{i}\binom{c_1}{k+i}=\sum_{i=0}^{c_0}\binom{c_0}{c_0-i}\binom{c_1}{k+i}=\binom{c_0+c_1}{k+c_0}=\binom{n}{k+c_0}.$$

左边的求和是一个范德蒙德卷积的推论。所以这个字符串所以子序列的价值之和就是：

$$\sum_{i=-c_0}^{n-c_0}\binom{n}{c_0+i}\left(\frac{i^2}{4}+\frac{i\bmod 2}{4}\right).$$

预处理出所有 $c_0$ 的答案即可 $O(1)$ 询问，总复杂度 $O(n\log n+q)$，因为这里的处理需要简单 poly，具体可以看[官解的代码（Python）](https://codeforces.com/contest/2077/submission/310298025)。

我是 poly 菜鸡，于是我没有场切，所以我开始推狮子。这里需要的一些组合数性质可以先看 [oiwiki](https://oi-wiki.org/math/combinatorics/combination/#%E7%BB%84%E5%90%88%E6%95%B0%E6%80%A7%E8%B4%A8--%E4%BA%8C%E9%A1%B9%E5%BC%8F%E6%8E%A8%E8%AE%BA)。

我们把后面的取模分开处理。先求前面的平方除以四，再求后面的取模求和，这里我们可以把除以四放在最后，所以推式子里面没写。

$$
\begin{aligned}
\sum_{i=-c_0}^{n-c_0}\binom{n}{c_0+i}i^2&=\sum_{i=0}^n\binom{n}{i}(i-c_0)^2\\
&=\sum_{i=0}^n\binom{n}{i}i^2-2c_0\sum_{i=0}^n\binom{n}{i}i+c_0^2\sum_{i=0}^n\binom{n}{i}\\
&=n(n+1)2^{n-2}-2c_0n2^{n-1}+c_0^22^n.\\
\sum_{i=-c_0}^{n-c_0}\binom{n}{i+c_0}(i\bmod 2)&=\sum_{i=0}^n\binom{n}{i}\left((i-c_0)\bmod 2\right)=2^{n-1}.
\end{aligned}
$$

说明一下后面这个式子。他的具体意义就是求出所有 $i$ 为偶数或奇数的组合数之和。不论奇数还是偶数，组合数之和都是 $2^{n-1}$ 次方。

> 证明：考虑二项式定理，我们有 $(1+x)^n=\sum_{i=0}^n \binom{n}{i}x^i$，代入 $x=-1$：
>
> $$(1-1)^n=\sum_{i=0}^n \binom{n}{i}(-1)^i=0.$$
>
> 即：
>
> $$\sum_{i\bmod 2=0}\binom{n}{i}-\sum_{i\bmod 2=1}\binom{n}{i}=0$$
>
> 也就是 $i$ 为奇数和偶数分别求和是相等的，并且我们知道所有组合数之和是 $2^n$，从而 $i$ 为奇或偶是的和都是 $2^{n-1}$。

最后把两个式子加起来。

$$\begin{aligned}
4\text{Answer}&=n(n+1)2^{n-2}-2c_0n2^{n-1}+c_0^22^n+2^{n-1},\\
\text{Answer}&=2^{n-4}(n^2+n-4c_0n-4c_0^2+2).
\end{aligned}$$

然后直接做了，每次询问 $O(1)$ 算一下即可。代码就不放了，十分甚至九分的简单罢。

---

## 作者：sususy (赞：0)

一种比较复杂的做法，但不需要发现 $\left\lfloor\frac s2\right\rfloor\left\lceil\frac s2\right\rceil=\frac{s^2-(s\bmod 2)}{4}$。

$F(v,l,r)$ 为 $v_{[l\dots r]}$ 中 $1$ 的个数减去 $0$ 的个数。记 $s=F(v,1,|v|)$，$x=F(v,1,i)$，那么 $v$ 的分数为 $x(s-x)$，当 $x=\left\lfloor\frac s2\right\rfloor$ 时取最大值，因为当 $i$ 增加 $1$ 时，$x$ 要么 $+1$ 要么 $-1$，所以显然能取到。因此，$v$ 的权值为 $\left\lfloor\frac s2\right\rfloor\left\lceil\frac s2\right\rceil$。

可以枚举子序列中 $0,1$ 的个数，分别记为 $c_0,c_1$，记整个字符串中 $0,1$ 的个数分别为 $t_0,t_1$，则答案为 

$$\sum_{c_0}\sum_{c_1}\left\lfloor\frac{c_1-c_0}{2}\right\rfloor\left\lceil\frac{c_1-c_0}{2}\right\rceil\binom{t_0}{c_0}\binom{t_1}{c_1}$$

（注意形如 $\sum_i$ 的式子中 $i$ 的范围是所有整数，包括负数。）

改为枚举 $s=c_1-c_0$ 和 $c_0$：

$$\begin{aligned}&\sum_s\left\lfloor\frac s2\right\rfloor\left\lceil\frac s2\right\rceil\sum_{c_0}\binom{t_0}{c_0}\binom{t_1}{c_0+s}\\
=&\sum_s\left\lfloor\frac s2\right\rfloor\left\lceil\frac s2\right\rceil\sum_{c_0}\binom{t_0}{t_0-c_0}\binom{t_1}{c_0+s}\\
=&\sum_s\left\lfloor\frac s2\right\rfloor\left\lceil\frac s2\right\rceil\binom{n}{s+t_0}
\end{aligned}$$

最后一步是根据范德蒙德卷积得到的。设

$$f(t_0)=\sum_s\left\lfloor\frac s2\right\rfloor\left\lceil\frac s2\right\rceil\binom{n}{s+t_0}$$

考虑如果已经算出了 $f(t_0)$，怎么算出 $f(t_0+2)$（因为式子中有 $\frac s2$，所以选取 $t_0+2$ 比较方便，而不是 $t_0+1$）：

$$\begin{aligned}f(t_0+2)
&=\sum_s\left\lfloor\frac s2\right\rfloor\left\lceil\frac s2\right\rceil\binom{n}{s+t_0+2}\\
&=\sum_s\left\lfloor\frac {s-2}2\right\rfloor\left\lceil\frac {s-2}2\right\rceil\binom{n}{s+t_0}\\
&=\sum_s\left(\left\lfloor\frac s2\right\rfloor-1\right)\left(\left\lceil\frac s2\right\rceil-1\right)\binom{n}{s+t_0}\\
&=\sum_s\left(\left\lfloor\frac s2\right\rfloor\left\lceil\frac s2\right\rceil-s+1\right)\binom{n}{s+t_0}\\
&=f(t_0)-\sum_ss\binom{n}{s+t_0}+\sum_s\binom{n}{s+t_0}\\
&=f(t_0)-\sum_ss\binom{n}{s+t_0}+2^n
\end{aligned}$$

接下来计算 $\sum_ss\binom{n}{s+t_0}$：

$$\begin{aligned}
\sum_ss\binom{n}{s+t_0}&=\sum_s(s+t_0)\binom{n}{s+t_0}-\sum_st_0\binom{n}{s+t_0}\\
&=\sum_sn\binom{n-1}{s+t_0-1}-\sum_st_0\binom{n}{s+t_0}\\
&=n2^{n-1}-t_02^n
\end{aligned}$$

所以，$f(t_0+2)=f(t_0)-n2^{n-1}+t_02^{n}+2^n$。先暴力计算 $f(0),f(1)$，之后用这个式子预处理出所有 $f(t_0)$，询问时只要维护 $t_0$，然后直接输出即可。

---

