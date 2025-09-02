# 『DABOI Round 1』Blessings Repeated

## 题目背景

@[cyh20100812](https://www.luogu.com.cn/user/1051692) 因其很有实力被尊称为圣母。

> 圣母好闪，拜谢圣母！

## 题目描述

圣母是一名辩论家，即 ENTP。

她在进行一次辩论时的观点是字符串 $S$，她为了让对方信服她的观点她会强调 $k$ 次，所以她的辩词即为 $k$ 个字符串 $S$ 依次首尾相接。

你作为反驳的人可能不能听清楚她说的所有话，所以你只能抓取关键词 $T$，你需要求出 $k$ 个首尾相接的 $S$ 中有多少个子序列（不一定连续）为 $T$，答案对 $998244353$ 取模。

---

**【形式化题意】**

给定一个正整数 $k$ 和两个字符串 $S,T$。

设字符串 $s$ 为 $k$ 个字符串 $S$ 首尾相接得到的字符串，$n=\vert s \vert , m=\vert T \vert$。

设答案集合 $P=\{ (i_0,i_1,\dots,i_{m-1})  \mid 0\le i_0 < i_1 < \dots < i_{m-1} < n, \forall~0 \le j < m, s_{i_j}=T_j \}$，请求出 $\vert P \vert \bmod 998244353$。

## 说明/提示

**【样例 1 解释】**

将 $S$ 重复 $2$ 次得到 $\texttt{stocyhorzstocyhorz}$。

答案集合 $P=\{(3,4,5),(3,4,14),(3,13,14),(12,13,14) \}$，因此 $\vert P\vert=4$。

---

**【数据范围】**

对于 $100\%$ 的数据，$0<k\le10^{18}$，$0 < \vert S \vert \le 5 \times 10^3$，$0 < \vert T \vert \le 10$，字符串 $S,T$ 均由小写英文字母组成。

| $\text{Point}$ | $k\le$ | $\vert S\vert\le$ | $\vert T\vert\le$ |
| :-: | :-: | :-: | :-: |
| $1\sim2$        | $10^{18}$ | $5 \times 10^3$     | $1$                 |
| $3$          | $1$       | $5 \times 10^3$     | $2$                 |
| $4\sim5$        | $100$     | $5 \times 10 ^3$    | $2$                 |
| $6\sim7$        | $1$       | $50$                | $4$                 |
| $8\sim10$     | $10$      | $5 \times 10^3$     | $10$                |
| $11\sim20$ | $10^{18}$ | $5 \times 10^3$     | $10$                |

## 样例 #1

### 输入

```
2
stocyhorz
cyh```

### 输出

```
4```

## 样例 #2

### 输入

```
4
c
ccc```

### 输出

```
4```

# 题解

## 作者：chenxi2009 (赞：7)

**Upd 2024.11.26：~~压行~~改进码风**

[专栏](https://www.luogu.com.cn/article/gn7tpfeq)沉浸式阅读

闲话：怎么这么多写矩阵乘法的呢？那就让我来给一个通俗的写法吧…

这是一篇保姆级的简单题解。

前置知识：组合数学，一点动态规划思想，搜索，乘法逆元

# 思路

令 $n=\vert S\vert,m=\vert T\vert$。\
首先我们可以在 $O(nm)$ 的时间内求出 $S$ 的子序列中等于 $T$ 的序列数量。

**如果你不想思考，这里有思考过程：**

令 $f_{i,j}$ 为 $S_{1\cdots i}$ 的子序列中等于 $T_{1\cdots j}$ 的序列数量。\
易得递推：

$$
f_{i,j}=f_{i-1,j}+\sum_{k=1}^{i-1}f_{k,j-1} (S_i=T_j)
$$

$$
f_{i,j}= f_{i-1,j} (S_i\ne T_j)
$$

复杂度 $O(n^2m)$。

令

$$
g_{i,j}=\sum_{k=1}^{j}f_{i,k}
$$

易得新的递推式：

$$
g_{i,j}=g_{i-1,j}+g_{i-1,j-1}(S_i=T_j)
$$

$$
g_{i,j}=g_{i-1,j}(S_i\ne T_j)
$$

复杂度 $O(nm)$。\
第二重循环倒序可以压掉第一维。空间复杂度 $O(m)$。

**继续正文**

用这个方法，我们可以得出 $T$ 的所有子串在 $S$ 里面对应的子序列个数，复杂度为 $O(nm^3)$。

这个时候，我们已经离答案非常接近了。\
因为我们发现对于每一个重复 $k$ 次的 $S$ 构成的字符串里等同于 $T$ 的子序列，都是由**把 $T$ 分成若干个子串，在不同位置的 $S$ 中取了分别等同于各个子串的子序列构成的。**

**样例理解**

**以题目样例 #1 为例：**

```
2
stocyhorz
cyh
```

我们可以把 $T$ 分成一个子串 $T_{1,2,3}$，在第一个 $S$ 中取该子串和在第二个 $S$ 中取该子串，有 `2` 种方案；\
我们可以把 $T$ 分成两个子串 $T_{1,2},T_3$，即 `cy` 与 `h`，在第一个 $S$ 中取第一个子串，第二个 $S$ 中取第二个子串，有 `1` 种方案；\
我们可以把 $T$ 分成两个子串 $T_1,T_{2,3}$，即 `c` 与 `yh`，在第一个 $S$ 里面取第一个子串，第二个 $S$ 中取第二个子串，有 `1` 种方案；\
我们可以把 $T$ 分成三个子串，但是我们没有足够的 $S$ 去分配三个子串，因而没有方案。\
综上所述，共有 `4` 种方案。

**以题目输出 #2 为例：**

```
4
c
ccc
```

唯一有方案的分割方式是把 $T=$`ccc` 分割成三个子串 `c`，分配给 $k=$ `4` 个 $S=$`c`，有 `4` 种方案。

**如果你还没有想到正解？**

**从最小的问题开始思考：**

不妨先假定我们已经确定了一种分配方案，将 $T$ 分割为了 $p$ 个子串 $T_{1\cdots r_1},T_{r_1+1\cdots r_2}\cdots T_{r_{p-1}+1\cdots m}$。

令 $h_{l,r}$ 为先前我们所计算的，一个 $S$ 中等同于 $T_{l\cdots r}$ 的子序列个数。

对于选好了 $p$ 个不同位置上的 $S$，我们在第一个选取的 $S$ 中取了 $T_{1\cdots r_1}$，有 $h_{1,r_1}$ 种方案；在第二个选取的 $S$ 中取了 $T_{r_1+1\cdots r_2}$ 有 $h_{r_1+1,r_2}$ 种方案……

最终根据乘法原理，共有

$$
\prod_{i=1}^{p} h_{r_{i-1}+1,r_i}
$$

种方案。特殊地，我们令其中 $r_0=0,r_p=n$。

**但是我们还没有确定 $p$ 个 $S$ 的位置啊？**

从 $k$ 个 $S$ 里面选 $p$ 个 $S$，显然这一步的方案数是 $C_k^p$。递推求**组合数**明显会超时，我们采用它的公式法：

$$
C_n^m=\frac{n!}{m!(n-m)!}=\frac{n(n-1)(n-2)\cdots (n-m+1)}{m!}
$$

其中 $x!$ 表示 $x$ 的阶乘。

**取模操作中怎么处理分母中的 $m!$？**

加入**乘法逆元**后同余问题的各项性质不会被打破。\
通俗地说，我们把 $\frac{1}{m!}$ 当做 $m!^{998244351}$ 处理即可。

综上，对于将 $T$ 分割为 $p$ 个子串 $T_{1\cdots r_1},T_{r_1+1\cdots r_2}\cdots T_{r_{p-1}+1\cdots m}$，有

$$
C_k^p\times \prod_{i=1}^{p} h_{r_{i-1}+1,r_i}
$$

种方案。

**但是我们还没有确定分割方案？**

打住。

看看数据范围：$m\le 10$。\
于是**搜索**分割方案，累加答案即可。

**总复杂度**

动归求 $h$ 数组复杂度：$O(nm^3)$\
搜索累加答案复杂度：$O(m!\times m)$。\
总复杂度：$O(nm^3+m!\times m)$。\
$m$ 个组合数可以预处理得出，其中逆元可以打表，复杂度不计。

~~显然跑不满，最慢测试点 5ms~~
# 代码
## 参考程序
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MOD = 998244353;
int n,m,len,jd[11],inv[11] = {0,1,499122177,332748118,748683265,598946612,166374059,855638017,873463809,443664157,299473306};
long long k,jc[11],c[11],ans,f[11][11],g[11];
char s[5001],t[11];
void sch(int w){ //搜索 T 的分割方案 
	if(w == len + 1){
		long long cnt = c[len];
		for(int i = 1;i <= len;i ++) cnt = cnt * f[jd[i - 1] + 1][jd[i]] % MOD;
		ans = (ans + cnt) % MOD;
		return; 
	}
	if(w == len){
		jd[w] = m,sch(w + 1);
		return;
	}
	for(int i = jd[w - 1] + 1;i <= m - len + w;i ++) jd[w] = i,sch(w + 1);
	return;
}
int main(){
	scanf("%lld%s%s",&k,s + 1,t + 1);
	n = strlen(s + 1),m = strlen(t + 1);
	c[1] = k % MOD;
	for(int i = 2;i <= m;i ++) c[i] = c[i - 1] * (k % MOD - i + 1) % MOD * inv[i] % MOD; //预处理组合数 
	for(int l = 1;l <= m;l ++){
		for(int r = l;r <= m;r ++){ //计算 T 的每个子串对应的 h 数组值，这里用 f 存储 
			memset(g,0,sizeof(g));
			g[0] = 1;
			for(int i = 1;i <= n;i ++) for(int j = r;j >= l;j --) if(t[j] == s[i]) g[j - l + 1] = (g[j - l + 1] + g[j - l]) % MOD;
			f[l][r] = g[r - l + 1];
		}
	}
	for(len = 1;len <= m;len ++) sch(1);
	printf("%lld",ans);
	return 0;
}
```

总结：一道颇具思维趣味性的题目，做法本身没有蓝题难度但是思维可以有，显然仍具优化空间，本题解只提供了一个基础的做法权当抛砖引玉，欢迎大家改进本蒟蒻的做法！

~~闲话：赛时 RP 爆表，第一次成绩这么好！~~

---

## 作者：cjh20090318 (赞：7)

## 前言

出题人题解。

原题目名叫 Nice God's mOther marIa(NGOI)，但是为了比赛题目命名格式统一就改了，也算是个一语双关。

灵感来自对圣母名字的字符串进行一通操作，本来出的题太简单了，加强了一下就成了现在这个样子。

难度感觉也就绿蓝的样子。

## 题意

参见形式化题意。

## 分析

令 $n = \vert S \vert , m = \vert T \vert$。

### 测试点 $1,2$

性质 $m \le 1$，即字符串 $T$ 只有一个字符。

问题就转化为了 $k$ 个首尾相接的字符串 $S$ 中出现了多少个 $T$ 字符。

于是直接统计 $S$ 中出现了多少次，答案乘 $k$ 即可，时间复杂度 $O(n)$。

```python
k=int(input())
s=input()
t=input()
print(s.count(t)*k%998244353)
```

### 测试点 $3$

性质 $k=1$，直接枚举两边字符即可，时间复杂度 $O(n ^ 2)$。

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int mod=998244353;
int n,m;
LL k;
char s[5005],t[11];
int main(){
	scanf("%lld %s %s",&k,s,t),n=strlen(s),m=strlen(t);
	int ans=0;
	for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)
		(ans+=s[i]==t[0]&&s[j]==t[1])>=mod&&(ans-=mod);
	printf("%d\n",ans);
	return 0;
}
```

### 测试点 $4,5$

和上一部分不同之处在于 $k$ 的范围扩大到了 $k \le 100$，也就是说 $k n \le 5 \times 10^5$。

统计满足的二元组数量，只需要枚举一维，快速算另一维即可。

前缀和统计一下 $T_0$ 的数量，遇到 $T_1$ 相加一下即可，时间复杂度 $O(k n)$。

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int mod=998244353;
int n,m;
LL k;
char s[5005],t[11];
int main(){
	scanf("%lld %s %s",&k,s,t),n=strlen(s),m=strlen(t);
	int ans=0,w=0;
	while(k--)for(int i=0;i<n;i++) s[i]==t[1]&&(ans+=w)>=mod&&(ans-=mod),w+=s[i]==t[0];
	printf("%d\n",ans);
	return 0;
}
```

### 测试点 $6,7$

根据测试点 $3$ 的方式直接枚举判断即可，时间复杂度 $O(n ^ {m})$，代码过于简单就不放了。

### 测试点 $8,9,10$

各种数据范围都相比前面的有所加强，所以不能暴力枚举了，考虑动态规划。

#### 状态设计

设 $f_{i,j}$ 表示字符串 $s$ 前 $i$ 个字符中 $T$ 前 $j$ 个字符组成的字符串出现的子序列方案数。

#### 初始状态

$$
f_{0,0}=1
$$

#### 状态转移

$$
f_{i,j} = f_{i-1,j} + [s_{i-1} = T_{j-1}] f_{i-1,j-1}
$$

答案即 $f_{k n,m}$。

时间复杂度 $O(k n m)$，空间复杂度可以滚动优化到 $O(m)$。

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int mod=998244353;
int n,m;
LL k;
char s[5005],t[11];
int f[11];
int main(){
	scanf("%lld %s %s",&k,s,t),n=strlen(s),m=strlen(t);
	*f=1;
	while(k--)for(int i=0;i<n;i++)for(int j=m;j>0;--j)s[i]==t[j-1]&&(f[j]+=f[j-1])>=mod&&(f[j]-=mod);
	printf("%d\n",f[m]);
	return 0;
}
```

### 测试点 $11 \sim 20$

$k \le 10^{18}$ 提示复杂度和 $k$ 的一次无关，不难想到用矩阵乘法优化 DP。

对于每一个小写字母 $x$ 构造一个 $(m+1) \times (m+1)$ 的矩阵 $A_x$：

$$
A_{x,i,j}=
\begin{cases}
1 & i=j\\
[T_i = x] & j=i+1\\
0 & \text{otherwise}
\end{cases}
$$

接着设矩阵 $B=\prod\limits_{i=0}^{n-1}A_{S_i}$。

构造 $F$ 矩阵：

$$
\begin{bmatrix}
F_0 & F_1 & \dots & F_m
\end{bmatrix}

=

\begin{bmatrix}
1 & 0 & \dots & 0
\end{bmatrix}
$$

最后将 $F \gets F \times B^k$ 即可，答案即为 $F_m$。

时间复杂度 $O(n m ^3)$，其中矩阵快速幂的时间复杂度为 $O(\log k m ^3)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long LL;
const int mod=998244353;
template<typename T>
struct Mat{//封装矩阵类。
    int n,m;
    T **a;
    Mat(int _n=0,int _m=0):n(_n),m(_m){
        a=new T*[n];
        for(int i=0;i<n;i++) a[i]=new T[m],memset(a[i],0,sizeof(T)*m);
    }
    Mat(const Mat&B){
        n=B.n,m=B.m;
        a=new T*[n];
        for(int i=0;i<n;i++) a[i]=new T[m],memcpy(a[i],B.a[i],sizeof(T)*m);
    }
    ~Mat(){delete[] a;}
    Mat&operator = (const Mat&B)&{
        delete[] a;
        n=B.n,m=B.m;
        a=new T*[n];
        for(int i=0;i<n;i++) a[i]=new T[m],memcpy(a[i],B.a[i],sizeof(T)*m);
        return *this;
    }
    Mat operator * (const Mat&B)const{//矩阵乘法。
        Mat ret(n,B.m);
        for(int i=0;i<n;++i)for(int j=0;j<B.m;++j)for(int k=0;k<m;++k)ret.a[i][j]=(ret.a[i][j]+(LL)a[i][k]*B.a[k][j]%mod)%mod;
        return ret;
    }
    Mat&operator *= (const Mat&B)&{return *this=*this*B;}
};
LL k;
int n,m;
char s[5005],t[15];
int main(){
	scanf("%lld %s %s",&k,s,t),n=strlen(s),m=strlen(t);
	Mat<int> F(1,m+1),A[26],B(m+1,m+1);
	for(int j=0;j<=m;j++) B.a[j][j]=1;
	**F.a=1;
	for(int i=0;i<26;i++){
		A[i]=Mat<int>(m+1,m+1);
		for(int j=0;j<=m;j++) A[i].a[j][j]=1;//对于每一个字母构造单位矩阵。
	}
	for(int i=0;i<m;i++) A[t[i]-'a'].a[i][i+1]=1;//将该转移位置的值为 1。
	for(int i=0;i<n;i++) B*=A[s[i]-'a'];
	for(;k;k>>=1,B*=B)if(k&1)F*=B;//矩阵快速幂
	printf("%d\n",F.a[0][m]);
	return 0;
}
```

据说还有一些其他的做法，但是我不会，欢迎大家提出自己的不同意见！

---

## 作者：Alphas (赞：5)

简单爆个标。

我们考虑 $T$ 会分成若干个连续段，每段完整的出现在一个 $S$ 中，因此，我们考虑 $dp_{l,r}$ 表示 $T_{[l, r]}$ 作为 $S$ 的一个子序列的方案数，显然可以枚举 $l$，然后通过 dp 计算出所有 $r(r\ge l)$ 的值，该部分时间复杂度为 $\Theta({nm^2})$。

下面考虑如何计算答案，假设我们分了 $x$ 段，方案为 $[l_1, r_1],[l_2, r_2]\cdots [l_x, r_x]$，满足 $l_1=1, l_x=m, l_{y+1}=r_y+1$，那么其对答案的贡献为 $\prod dp_{l_i, r_i}\times \binom{K}{x}$，即为各段方案数相乘再乘上选 $x$ 个 $S$ 的方案数。因此我们用 $f_{i, j}$ 计算前 $i$ 位划分了 $j$ 段的 $\sum (\prod dp)$，最后答案加上 $\sum f_{n, i}\times \binom{K}{i}$ 即可，该部分时间复杂度为 $\Theta({m^3})$。

总时间复杂度为 $\Theta({nm^2+m^3})$，远优于标算。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int P = 998244353;
int n, m;
long long ans, K, inv[15], f[15][15], g[5005][15], h[15][15];
string s, t;
long long fpow(long long x, int y) {
	if (!y) return 1;
	long long val = fpow(x, y >> 1);
	val = val * val % P * (y % 2 == 1 ? x : 1) % P;
	return val;
}
long long C(long long x, int y) {
    long long res = 1;
	for (long long i = x; i >= (x - y + 1); --i)
        res = res * (i % P) % P;
	for (int i = 1; i <= y; i++)
        res = res * inv[i] % P;
	return res;
}
int main() {
    cin >> K >> s >> t;
	n = s.size(), m = t.size();
	s = ' ' + s, t = ' ' + t;
	for (int i = 1; i <= m; i++)
	    inv[i] = fpow(i, P - 2);
	for (int i = 1; i <= m; i++) {
	    for (int k = i; k <= m; k++)
		    g[0][k] = 0;
		g[0][i - 1] = 1;
		for (int k = 1; k <= n; k++) {
			g[k][i - 1] = 1;
		    for (int l = i; l <= m; ++l) 
			    g[k][l] = (g[k - 1][l] + g[k - 1][l - 1] * (s[k] == t[l])) % P;
		}
		for (int j = i; j <= m; j++)
		    f[i][j] = g[n][j];
	}
	h[0][0] = 1;
	for (int i = 1; i <= m; i++)
	    for (int j = 1; j <= i; j++)
	        for (int k = 0; k < i; k++) 
		        h[i][j] = (h[i][j] + h[k][j - 1] * f[k + 1][i]) % P;
    for (int i = 1; i <= m; i++) 
	    ans = (ans + h[m][i] * C(K, i)) % P;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：SY_nzwmb83 (赞：5)

### 题意

求出 $k$ 个首尾相接的 $S$ 中有多少个子序列（不一定连续）为 $T$。

### 分析

对于在 $S$ 中出现，但是在 $T$ 中没有出现的字符，可以直接删去，因为这些字符不可能作为 $T$ 的子序列的任何一部分，下文的 $S$ 默认去除了这些字符。

我们可以将 $T$ 分割为 $x$ 个连续的部分，计为 $a_1,a_2,\dots,a_x$，即保证 $a_1,a_2,\dots,a_x$ 首尾相接可以形成 $T$。然后在 $k$ 个相同的字符串 $S$ 中，选出 $x$ 个。对于 $a_i$，求出 $S$ 有多少个子序列是 $a_i$，将这个方案数记作 $b_i$。

最终我们只需求出所有分割 $T$ 的合法方案中 $\binom{k}{x} \times \prod \limits_{i=1}^{x} b_i$ 的总和。分割可以二进制枚举。合法方案即保证 $\vert a_i \vert \le \vert S \vert$，且存在 $S$ 的子序列是 $a_i$。

现在问题在于，求出 $S$ 有多少个子序列是 $T$ 的任意一个子串 $t$。我们可以用若干个数组记录每一个在 $S$ 中出现的字符在 $S$ 中出现的位置，具体地，计 $g_c$ 为字符 $c$ 在 $S$ 中出现位置的下标构成的数组，按升序排列。这一功能可以用 `vector` 实现。

枚举子串的左端点。计 $f_i$ 为 $S$ 中有多少个子序列是**以 $t_i$ 结尾**的 $t$ 的子串。当 $t_i$ 为 $t$ 的第一个字符时，$f_i=1$。扫描子串 $t$ 除第一个字符外的每一个字符 $t_i$，在 $g_{t_{i-1}}$ 数组中寻找小于 $i$ 的数 $g_{{t_{i-1}},j}$，则 $f_i=\sum f_{g_{{t_{i-1}},j}}$，注意到 $g_{{t_{i-1}},j}$ 应是连续的一段区间，则可前缀和维护，事实上可以只记录前缀和数组。同时寻找最大的 $j$ 可以二分优化。

这样，可以求出 $S$ 有多少个子序列是 $t$。其它部分易实现。注意因为 $x$ 很小，$\binom{k}{x}$ 可以用对 $[k,k-x+1]$ 中的一些数分别除以一些乘积为 $x!$ 的数，最后求积。$k$ 过大要开 `__int128`，同时注意取模。

### 代码

赛时打错几个下标，[100](https://www.luogu.com.cn/record/176369604) -> [30](https://www.luogu.com.cn/record/176274721)，悲。代码可能抽象了，数组和分析里命名可能不同。

```cpp
#include<bits/stdc++.h>
#define int __int128
#define mod 998244353
using namespace std;
int n,m,K,cnt,s[5005],t[15],gs[15][15];
string S,T;
map<char,int>mp;
vector<int>g[15];
int C(int x)//求组合数
{
	vector<int>h;
	for(int i=K;i>=K-x+1;i--)
	{
		h.push_back(i);
	}
	int y=1;
	for(int i=1;i<=x;i++)
	{
		y*=i;
	}
	for(int i=2;i*i<=y;i++)
	{
		for(int j=0;j<h.size();j++)
		{
			while(h[j]%i==0&&y%i==0)
			{
				h[j]/=i;
				y/=i;
			}
		}
	}
	if(y)
	{
		for(int j=0;j<h.size();j++)
		{
			if(h[j]%y==0)
			{
				h[j]/=y;
				break;
			}
		}
	}
	int ans=1;
	for(int i=0;i<h.size();i++)
	{
		ans=ans*h[i]%mod;
	}
	return ans;
}
void calc(int l,int r)//以l为左端点的子串
{
	vector<int>v(15);
	vector<int>sum[15];
	int pos=0;
	for(int i=l;i<=r;i++)
	{
		v[++pos]=t[i];
	}
	for(int i=0;i<g[v[1]].size();i++)//第一位特别处理
	{
		int x=0;
		if(i)x=sum[1].back();
		sum[1].push_back(x+1);
	}
	gs[l][l]=sum[1][g[v[1]].size()-1];
	for(int i=2;i<=pos;i++)
	{
		for(int j=0;j<g[v[i]].size();j++)
		{
			int id=lower_bound(g[v[i-1]].begin(),g[v[i-1]].end(),g[v[i]][j])-g[v[i-1]].begin();
			int x=0;
			if(j)x=sum[i].back();
			if(id-1>=0)sum[i].push_back(x+sum[i-1][id-1]);
			else sum[i].push_back(x);
		}
		gs[l][l+i-1]=sum[i][g[v[i]].size()-1];
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	long long kk;
	cin>>kk>>S>>T;
	K=kk;
	n=S.size();
	m=T.size();
	S=" "+S;
	T=" "+T;
	for(int i=1;i<=m;i++)
	{
		if(!mp.count(T[i]))mp[T[i]]=++cnt;
		t[i]=mp[T[i]];
	}
	int pos=0;
	for(int i=1;i<=n;i++)
	{
		if(!mp.count(S[i]))continue;
		s[++pos]=mp[S[i]];
	}//去除多余字符
	n=pos;
	for(int i=1;i<=n;i++)
	{
		g[s[i]].push_back(i);
	}
	for(int i=1;i<=m;i++)
	{
		calc(i,m);
	}
	int an=0;
	for(int k=0;k<=(1<<(m-1))-1;k++)//枚举分割方案
	{
		int x=__builtin_popcount(k);
		int y=x+1;
		int i=k+(1<<(m-1));
		int ans=1;
		int last=1;
		for(int j=1;j<=m;j++)
		{
			if((1<<(j-1))&i)
			{
				if(j-last+1>n)//不合法
				{
					ans=0;
					break;
				}
				ans=ans*gs[last][j]%mod;
				last=j+1;
			}
		}
		ans=ans*C(y)%mod;
		an=(an+ans)%mod;
	}
	cout<<(long long)an;
	return 0;
}
```

---

## 作者：light_searcher (赞：4)

怎么还有矩阵快速幂那么神仙的做法啊。

还是记录一下我赛时的麻烦做法。

## $50$ 分做法

首先我们不难推一个 dp，用来求 $s$ 中有多少个子序列等于 $T$。

设 $f_{i,j}$，表示 $s$ 的前 $i$ 个字符中有多少个子序列等于 $T$ 的前 $j$ 个字符串。

如果 $s_i \ne T_j$，那么 $f_{i,j}=f_{i-1,j}$，直接继承上一个位置，否则 $f_{i,j}=f_{i-1,j-1}+f_{i-1,j}$，这也是好理解的，最后的答案就是 $f_{n,m}$。

那么我们就有了一个 $ \mathcal O(nm)$ 的做法，然后结合前两个点可以得到 $50$ 分。

## $100$ 分做法

注意到 $m$ 很小。根据题目，$s$ 是由 $k$ 个 $S$ 首尾相接得到的，那么我们可以说 $s$ 有 $k$ 段，所以 $T$ 最多只会被划分进 $m$ 个段，所以我们完全可以把这 $m$ 个段里的答案求出来，然后通过组合数算出在 $k$ 个段里的贡献是多少，这样的复杂度是完全可以接受的。

具体地，我们先把 $m$ 个 $S$ 首尾相接，然后求出上文提到的 $f_{i,j}$。令 $pre_i$ 表示有几个子序列被划分进了 $i$ 个段中，则有 $pre_i= f_{i*|S|,m}-\sum \limits _{j=1}^{i-1} pre_j \times C_i^j$，就是一个简单的容斥，用 $i$ 个段里的总子序列数减去没有被划分为 $i$ 段的子序列数。

然后就可以算答案了，考虑枚举被划分的段数 $i$，总共有 $C_k^i= \frac{k!}{i! \times (k-i)!}= \frac{\prod \limits _{j=k-i+1}^{k}j}{i!}$，显然上下两个都可以在常数时间内计算，那么对答案的贡献就是 $pre_i \times C_k^i$，因此答案是 $\sum \limits _{i=1}^m pre_i \times C_k^i$。

由于需要取模，所以还需要求逆元，然后还需要注意防负数取模。

Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=998244353;
int k,n,m,f[N][15],x,y,ans,pre[15];
string s,t;
void exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}
signed main(){
	cin>>k>>s>>t;
	m=t.size();
	string tmp=s;
	for(int i=1;i<min(k,m);i++) s+=tmp;
	n=s.size();
	s=' '+s;
	t=' '+t;
	for(int i=0;i<=n;i++) f[i][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i]==t[j]) f[i][j]=(f[i-1][j-1]+f[i-1][j])%mod;
			else f[i][j]=f[i-1][j];
	if(k<m){
		cout<<f[n][m];
		return 0;
	}
	pre[1]=f[tmp.size()][m];
	for(int i=2;i<=m;i++){
		pre[i]=f[i*tmp.size()][m];
		for(int j=1;j<i;j++){
			int tmp1=1ll,tmp2=1ll;
			for(int l=1;l<=j;l++) tmp1=tmp1*l%mod;
			for(int l=i-j+1;l<=i;l++) tmp2=tmp2*l%mod;
			exgcd(tmp1,mod,x,y);
			x=((x%mod)+mod)%mod;
			pre[i]=((pre[i]-(tmp2*x%mod*pre[j]%mod))%mod+mod)%mod;
		}
	}
	for(int i=1;i<=m;i++){
		int tmp1=1ll,tmp2=1ll;
		for(int j=1;j<=i;j++) tmp1=tmp1*j%mod;
		for(int j=k-i+1;j<=k;j++) tmp2=j%mod*tmp2%mod;
		exgcd(tmp1,mod,x,y);
		x=(x%mod+mod)%mod;
		ans=(ans+pre[i]*tmp2%mod*x%mod)%mod;
	}
	cout<<ans;
	return 0;
}

---

## 作者：int_R (赞：4)

考虑求出**恰好**使用了 $c$ 个 $S$ 的方案。就是说我们将 $c$ 个 $S$ 拼在一起组成 $s$，在其中取一个子序列与 $T$ 相等，同时这 $c$ 段**每一段**都至少拿出来了一个字符组成这个子序列。显然我们最多使用 $m$ 个 $S$。

这个东西简单 DP，设 $f_{c,i,j}$ 为在第 $c$ 个 $S$ 的第 $i$ 位匹配 $T$ 中第 $j$ 位的方案数，$f_{c,i,j}=\sum\limits_{x=0}^n f_{c-1,x,j-1}+\sum\limits_{x=0}^{i-1} f_{c,x,j-1}$，转移可以优化到 $O(1)$。

答案就是 $\sum f_{c,i,m}\times {k\choose c}$，意义是在那 $k$ 个 $S$ 中任意选出来 $c$ 个。总复杂度是 $O(nm^2)$ 的，不仅比官方题解少个 $m$ 还完全与 $k$ 无关，而且个人觉得比那简单。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#define int long long
using namespace std;
const int MAXN=5e3+10,mod=998244353;
int k,ans,C=1;string s,t;int n,m;
int f[15][MAXN][15],g[15],preg[15],c[15];
inline int ksm(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=a*a%mod)
        if(b&1) ans=ans*a%mod;
    return ans;
}
signed main()
{
    // freopen("in.in","r",stdin);
    // freopen("out.out","w",stdout);
    cin>>k>>s>>t,g[0]=1;
    n=s.size(),s=' '+s,m=t.size(),t=' '+t;
    for(int o=1;o<=min(m,k);++o)
    {
        C=(k-o+1)%mod*C%mod*ksm(o,mod-2)%mod;
        for(int i=0;i<=m;++i) preg[i]=g[i];
        for(int i=1;i<=n;++i)
        {
            for(int j=m;j;--j)
            {
                if(s[i]!=t[j]) continue;
                f[o][i][j]+=g[j-1],g[j]+=f[o][i][j];
                f[o][i][j]%=mod,g[j]%mod;
            }
            ans+=f[o][i][m]*C%mod;
        }
        for(int i=0;i<=m;++i) g[i]=(mod+g[i]-preg[i])%mod;
    }
    cout<<ans%mod<<'\n';return 0;
}
```

---

## 作者：Re_Star (赞：2)

[题面](https://www.luogu.com.cn/problem/P11030)

[更好的阅读体验](https://www.cnblogs.com/Re-Star/p/18828839)

首先我们注意到 $\lvert T \rvert$ 很小，所以可以考虑将 $T$ 拆分为若干个段，并钦定每一段都只被同一个 $S$ 包含。那么我们需要先处理出对于 $T$ 的每一个子段，在 $S$ 中作为子序列出现的次数。这个可以 DP 来做，我们设 $f_{i,l,r}$ 表示 $S$ 的前 $i$ 位中有多少个子序列和 $T$ 的第 $l$ 到 $r$ 位相同。转移也非常简单：
$$
f_{i,l,r}=
\begin{aligned} 
\begin{equation}
    \begin{cases}
    f_{i-1,l,r}&(s_i\ne t_r) \\
    f_{i-1,l,r}+1&(s_i=t_r,l=r)\\
    f_{i-1,l,r}+f_{i-1,l,r-1}&(s_i=t_r,l\ne r)
    \end{cases}
\end{equation}
\end{aligned}
$$
现在我们考虑统计答案，直接 dfs 就可以了，当我们搜索出一种拆分将 $T$ 拆成了 $p$ 段，第 $i$ 段从 $l_i$ 到 $r_i$，那么对答案的贡献应该是：
$$
{k\choose m}\prod_{i=1}^m f_{n,l_i,r_i}
$$
code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e3+10,mod=998244353;
ll f[N][12][12],S,T,inv[12],ans,k;
char s[N],t[12];
ll qp(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1) (res*=x)%=mod;
		(x*=x)%=mod,y>>=1;
	}
	return res;
} 
ll C(ll x)
{
	ll res=1;
	for(int i=0;i<x;i++) (res*=(k-i)%mod)%=mod;
	return res*inv[x]%mod;
}
void dfs(int l,int pos,ll res)
{
	if(l>T) return (ans+=res*C(pos))%=mod,void();
	for(int r=l;r<=T;r++) dfs(r+1,pos+1,res*f[S][l][r]%mod);
}
int main()
{
	cin>>k;inv[1]=1;
	for(int i=2;i<=10;i++) inv[i]=inv[i-1]*qp(i,mod-2)%mod;
	scanf("%s%s",s+1,t+1);
	S=strlen(s+1),T=strlen(t+1); 
	for(int i=1;i<=S;i++)
		for(int l=1;l<=T;l++)
			for(int r=l;r<=T;r++)
			{
				f[i][l][r]=f[i-1][l][r];
				if(s[i]==t[r]) (f[i][l][r]+=(l==r?1:f[i-1][l][r-1]))%=mod;
			}
	dfs(1,0,1);
	cout<<ans;
	return 0;
} 
```

---

## 作者：shanxinhan (赞：2)

# P11030 『DABOI Round 1』Blessings Repeated

## 思路

### 50 分做法

这道题拿 50 分还是很容易的，只需要把字符串 $S$ 复制 $k$ 便得到字符串 $s$，然后简单地线性 dp 一下就可以。

设 dp 状态 $f_{i,j}$ 表示当前 dp 到第 $i$ 位，拼好了字符串 $T$ 的前 $j$ 位的方案数。则有状态转移方程：

$$f_{i,j} = \begin{cases} f_{i-1,j} & S_i \ne T_j \\ f_{i-1,j} + f_{i-1,j-1} & S_i = T_j  \end{cases}$$

然后在一开始把所有 $f_{i,0}$ 都初始化为 $1$ 即可。

第一个测试点怎么做就不用讲了吧。

### 100 分做法

观察数据范围，发现 $k$ 居然有 $10^{18}$ 这么大，显然用普通的 dp 会爆炸。那有什么办法可以快速解决呢？$10^{18}$ 显然要用 $log$ 的复杂度去做，再看上面的转移方程，是不是觉得有点眼熟？

没错，这道题可以用数列加速对 dp 进行优化，如果你不会数列加速，请移步至[模板题](https://www.luogu.com.cn/problem/P1939)。

我们的思路就是构造一个单位矩阵，然后把初始矩阵乘上单位矩阵的 $k$ 次幂就是答案矩阵。

怎么构造单位矩阵呢？很明显初始是

$$I_0=\begin{pmatrix}
   1 & 0 & \cdots & 0 \\
   0 & 1 & \cdots & 0 \\
   \cdots & \cdots & \cdots & \cdots \\
   0 & 0 & \cdots & 1 \\
\end{pmatrix}$$

然后再像上面 dp 的思路一样，转移方程是

$$I_i =  I_{i-1} \times  \begin{pmatrix}
   1 & a_{1,2} & 0 &\cdots & 0 \\
   0 & 1 & a_{2,3} & \cdots & 0 \\
   0 & 0 & 1 & \cdots & 0 \\
   \cdots & \cdots & \cdots & \cdots & a_{n-1,m}\\
   0 & 0 & 0 & \cdots & 1 \\
\end{pmatrix} $$

其中，$n = \lvert S \rvert , m = \lvert T \rvert ，a_{i,j} = \begin{cases} 0 & S_i \ne T_j \\ 1 & S_i = T_j \\ \end{cases}$

对于 $a_{i,j}$ 的值，其实可以理解成上文 dp 的状态转移方程，这两个思路其实是一样的。

最后，我们得到单位矩阵 $A = I_n$，然后得到答案矩阵为

$$ANS = \begin{pmatrix}1 & 0 & \cdots & 0 \\ \end{pmatrix} \times A^k$$

最后的最后，输出 $ANS_{1,m}$ 即为答案。

## 代码

```cpp
//为了方便起见，代码中矩阵的下标是从0开始的
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005,mod=998244353;
int K,n,m,f[N][15];
char s[N],t[15];
struct matrix{
	int r,c,num[15][15];
	matrix(){
		for(int i=0;i<15;i++)
			for(int j=0;j<15;j++)
				num[i][j]=(i==j);
	}
	matrix operator*(const matrix &b)const{
		matrix res;
		res.r=r,res.c=b.c;
		memset(res.num,0,sizeof(res.num));
		for(int i=0;i<=r;i++)
			for(int j=0;j<=b.c;j++)
				for(int k=0;k<=c;k++)
					res.num[i][j]=(res.num[i][j]+num[i][k]*b.num[k][j])%mod;
		return res;
	}
}mul,ans;
matrix qpow(matrix a,int b){
	matrix res;
	res.r=a.r,res.c=a.c;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
signed main(){
	cin>>K>>(s+1)>>(t+1);
	n=strlen(s+1),m=strlen(t+1);
	mul.r=mul.c=m;
	for(int i=1;i<=n;i++){
		matrix x;
		x.r=x.c=m;
		for(int j=1;j<=m;j++)
			if(s[i]==t[j])x.num[j-1][j]=1;
		mul=mul*x;
	}//得到单位矩阵
	ans.r=0,ans.c=m;
	ans=ans*qpow(mul,K);//得到答案矩阵
	cout<<ans.num[0][m]<<endl;
	return 0;
}
```

---

## 作者：Null_h (赞：1)

## 前言

此题深化了一下自己对于倍增和区间 dp 的理解。

## 思路

看到 $k$ 的范围是第一感觉是数学，但是推了一会发现这东西非常不好维护，基本表达不出什么规律。

但是以此为破题处，想到使用倍增。具体来说，想知道复制 $2^i$ 次后拼出 $T$ 的方案，显然要将其划分为前后两段，枚举前一段的长度进行转移。

于是区间 dp 的状态表示就呼之欲出了：

令 $f_{i,l,r}$ 表示 $S$ 复制 $2^i$ 次后子序列为 $T$ 的 $l$ 至 $r$ 子串的方案数。

转移是 $f_{i,l,r}=2\times f_{i-1,l,r}+\sum_{k = l}^{r-1}(f_{i-1,l,k}+f_{i-1,k+1,r})$

至于初始值的预处理跑前缀和即可，代码里也用了一个 dp。

然后就是通过处理出的 $f$ 数组来拼凑出答案，如果使用一个数组记录当前拼凑出的长度下的方案情况，可以发现，转移方法和 $f$ 数组的思路是大同小异的。

现在再看一眼，发现其实区间 dp 和矩阵的乘法是互通的，而倍增和快速幂也是一个思想，所以这个方法和矩阵快速幂本质相同，只不过理解上可能稍微直观一点。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
string s,t;
int n,m;
int f[110][20][20],p[110];
int g[5010][20][20];
int h[110][20][20];
signed main()
{
    int k;
    cin>>k>>s>>t;
    n=s.size();
	m=t.size();
	s=' '+s;
	t=' '+t;
	for(int i=m;i>=1;i--){
		for(int j=m;j>=i;j--){
			for(int k=n;k>=1;k--){
				g[k][i][j]+=g[k+1][i][j];
				if(s[k]==t[i])g[k][i][j]+=(i+1>j)?1:g[k+1][i+1][j];	
				g[k][i][j]%=mod;
				//cout<<k<<' '<<i<<' '<<j<<' '<<g[k][i][j]<<'\n';
			}
			f[0][i][j]=g[1][i][j];
			//cout<<i<<' '<<j<<' '<<f[0][i][j]<<'\n';
		}
	}
	int y=log2((double)k);
	for(int i=1;i<=y;i++){
		for(int len=1;len<=m;len++){
			for(int l=1;l+len-1<=m;l++){
				int r=l+len-1;
				f[i][l][r]+=2*f[i-1][l][r];
				f[i][l][r]%=mod;
				for(int k=l;k<r;k++){
					f[i][l][r]+=f[i-1][l][k]*f[i-1][k+1][r];
					f[i][l][r]%=mod;
				}
				//cout<<i<<' '<<l<<' '<<r<<' '<<f[i][l][r]<<'\n';
			}
		}
	}
	p[0]=1;
	for(int i=1;i<=y;i++)p[i]=p[i-1]*2;
	int q=0,x=0;
	for(int i=y;i>=0;i--){
		if(q+p[i]<=k){
			x++;
			q+=p[i];
			for(int len=1;len<=m;len++){
				for(int l=1;l+len-1<=m;l++){
					int r=l+len-1;
					h[x][l][r]+=h[x-1][l][r]+f[i][l][r];
					h[x][l][r]%=mod;
					for(int k=l;k<r;k++){
						h[x][l][r]+=h[x-1][l][k]*f[i][k+1][r];
						h[x][l][r]%=mod;
					}
				}
			}
		}
	}
	cout<<h[x][1][m];
    return 0;
 }
```

---

## 作者：NEWSTDLRZ (赞：1)

[题目](https://www.luogu.com.cn/problem/P11030)

### 题目描述

有一个字符串 $S$，把他重复 $k$ 遍变成字符串 $Z$，求出 $Z$ 里面有多少个子序列组成的字符串等于 $T$。

先考虑部分分。

### 数据范围：$k \leq 10^{18},|S| \leq 5 \times 10^3,|T|=1$。

考虑到字符串 $T$ 的长度只有 $1$，所以只需要求出 $S$ 字符串中有多少个 $T$ 即可，最后将答案乘上 $k$ 即可。

代码：

```cpp
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#define LL long long
using namespace std;
LL k,n;
string s,t;
const LL mod=998244353;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); // 关闭输入输出流 
	cin>>k>>s>>t; // 输入 
	n=s.size(); // 存起来，避免 s.size() 所带来的常数 
	char p=t[0]; // 提取这唯一的一个字符 
	LL ans=0; // 答案
	for(int i=0;i<n;++i) ans+=(s[i]==p); // 如果当前字符跟 p 一样，++ans
	cout<<(ans%mod)*(k%mod)%mod<<"\n";
	return 0; 
}
```

### 数据范围：$k=1,|S| \leq 5 \times 10^3,|T| \leq 2$。

最简单的办法就是先枚举一个 $i$，再枚举一个 $j$，使得 $j>i$，然后判断是否为字符串 $T$ 即可。

不排除有其他办法，这个另说。

代码：

```cpp
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#define LL long long
using namespace std;
LL k,n;
string s,t;
const LL mod=998244353;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>s>>t;
	n=s.size();
	char p1=t[0],p2=t[1];
	LL ans=0;
	for(int i=0;i<n;++i){
		for(int j=i+1;j<n;++j){ // 不能让 j 在 i 前面，因为题目说的是子序列 
			ans+=(s[i]==p1 && s[j]==p2);
		}
	}
	cout<<ans%mod<<"\n";
	return 0; 
}
```

### 数据范围：$k \leq 100,|S| \leq 5 \times 10^3,|T| \leq 2$。

我们这下子不能像 $k \leq 1$ 时的方法去做了，因为复杂度为 $\mathcal O(|S|^2 \times k^2)$ 的。

考虑记录一个后缀数组 $sum_i$，表示从 $i$ 位置到最后一个位置有多少个字符等于字符串 $T$ 中的第 $2$ 个字符。

这样子的话，我们枚举第 $1$ 个字符所对应的 $S_i$，意思就是枚举 $i$ 使得 $S_i=T_1$。

其中，$T_i$ 表示 $T$ 中的第 $i$ 个字符，其他类似。

每个合法的 $i$ 所对应的答案就是 $sum_{i+1}$。

时间复杂度 $\mathcal O(|S| \times k)$。

代码：

```cpp
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#define LL long long
using namespace std;
LL k,n,ans;
string s,t,z;
const LL mod=998244353;
LL sum[1000010];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>s>>t;
	for(int i=1;i<=k;++i) z+=s; // 把 s 字符串重复 k 遍
	n=z.size();
	for(int i=n-1;i>=0;--i){ // 计算后缀和 sum[i] 
		sum[i]=sum[i+1]+(z[i]==t[1]); // 这里的 t[1] 和原文中的 t[1] 有区别  
	}
	for(int i=0;i<n-1;++i){
		if(z[i]==t[0]){ // 这个 i 合法 
			ans=(ans+sum[i+1])%mod; // 统计答案 
		}
	}
	cout<<ans<<"\n";
	return 0; 
}
```

### 数据范围：$k \leq 1,|S| \leq 50,|T| \leq 4$。

可以和在前面 $k=1,|S| \leq 5 \times 10^3,|T| \leq 2$ 该数据范围所对应的算法类推得到该算法。

时间复杂度 $\mathcal O(|S|^4)$。

相当于枚举 $a,b,c,d$，使得 $a<b<c<d$ 且 $a=t_1,b=t_2,c=t_3,d=t_4$ 就记录答案。

代码：

```cpp
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#define LL long long
using namespace std;
LL k,n,ans;
string s,t;
const LL mod=998244353;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>s>>t;
	n=s.size();
	for(int a=0;a<n;++a){
		for(int b=a+1;b<n;++b){
			for(int c=b+1;c<n;++c){
				for(int d=c+1;d<n;++d){
					ans=(ans+(s[a]==t[0] && s[b]==t[1] && s[c]==t[2] && s[d]==t[3]))%mod;
				}
			}
		}
	}
	cout<<ans<<"\n";
	return 0; 
}
```

### 数据范围：$k \leq 10,|S| \leq 5 \times 10^3,|T| \leq 10$。

其实在**这个数据范围下**，有很多种做法，这里介绍 $3$ 种做法，第 $3$ 种做法主要补充第 $2$ 种做法，看看哪种方法可以类推或优化到正解上。

#### 第 1 种做法

我们可以借助之前 $|T| \leq 2$ 的做法，做法是动态规划（在某种意义上可以叫前缀和）。

我们设 $sum_{i,j}$ 表示在 $[i,|S|]$ 区间的 $S$ 字符串中的子序列有几个是等于字符串 $Z=\sum_{k=j}^{|T|}T_k$ 的，其中 `a` 和 `b` 相加这里定义为 `a` 和 `b` 连起来，即为 `ab`。

可能有点抽象，来举个例子。

就比如说 $S=$`abccacbbc`，$T=$`abc`。

那么如果 $i=2,j=2$，那么他的意思就是在字符串 `bccacbbc` 中，有几个子序列是等于 `bc` 的。

有了这种做法，那么就先计算 $j=|T|$ 的情况，再计算 $j=|T|-1$ 的情况，一直计算到 $j=1$ 然后输出答案即可。

但是这种办法是很难类推或优化到正解上的，~~至少我不会~~。

时间复杂度 $\mathcal O(k \times |S| \times |T|)$。

代码：

```cpp
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#define LL long long
using namespace std;
LL k,n,tsiz,ans;
string s,t,z;
const LL mod=998244353;
LL sum[500100][11];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>s>>t;
	for(int i=1;i<=k;++i) z+=s; // 把 s 字符串重复 k 遍
	n=z.size(),z=" "+z,tsiz=t.size(),t=" "+t; // 做一些变量的预处理 
	for(int i=n;i>=1;--i){ // 计算后缀和 sum[i][t.size()]，他和其他的 sum 计算有区别 
		sum[i][tsiz]=sum[i+1][tsiz]+(z[i]==t[tsiz]); // 这里的 t[1] 和原文中的 t[1] 有区别  
	}
	for(int j=tsiz-1;j>=1;--j){ // 说过，按照状态定义是从大到小 
		for(int i=n;i>=1;--i){
			sum[i][j]=sum[i+1][j]; // 可以继承前面的方案数
			if(z[i]==t[j]){ // 可以继承 sum[i+1][j+1] 的方案数 
				sum[i][j]=(sum[i][j]+sum[i+1][j+1])%mod;
			}
		}
	}
	cout<<sum[1][1]<<"\n";
	return 0; 
}
```

#### 第 2 种做法

这种就是纯正的 DP 了。

设 $dp_{i,j}$ 状态表示字符串 $S$ 的前 $i$ 个字符，已经选出了 $j$ 个字符当字符串 $T$ 的前 $j$ 位的方案数。

子序列的定义是**按从左到右**的顺序选择出一些数字或字符，然后按照他们原来的先后顺序排好就是子序列。

那么这个性质就使得我们可以用这个状态进行动态规划了。

首先对于状态 $dp_{i,j}$，第 $1$ 种就是继承前面的方案数，即 $dp_{i-1,j}$。

第 $2$ 种方案数就是在当前的 $S_i$ 能够匹配 $T_j$ 的情况下，然后继承 $dp_{i-1,j-1}$。

这个节点可以类推到我们的正解——矩阵优化。

代码：

```cpp
#include<iostream>
#include<string.h>
#include<cstring>
#include<string>
#define LL long long
using namespace std;
LL k,n,tsiz,ans;
string s,t,z;
const LL mod=998244353;
LL dp[500100][11];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>s>>t;
	for(int i=1;i<=k;++i) z+=s; // 把 s 字符串重复 k 遍
	n=z.size(),z=" "+z,tsiz=t.size(),t=" "+t; // 做一些变量的预处理 
	dp[0][0]=1;
	for(int i=1;i<=n;++i){
		dp[i][0]=1;
		for(int j=1;j<=tsiz;++j){
			dp[i][j]=dp[i-1][j];
			if(z[i]==t[j]) dp[i][j]=(dp[i][j]+dp[i-1][j-1])%mod;
		}
	}
	cout<<dp[n][tsiz]<<"\n";
	return 0; 
}
```

#### 第 3 种做法

如果你不懂矩阵或者是不懂什么是单位矩阵，请移步 [Oi-wiki 矩阵](https://oi-wiki.org/math/linear-algebra/matrix/)。

这里的做法只是为了让大家感觉一下为什么这个状态不能用矩阵优化而已。

这里的状态是：$dp_{i,j}$ 表示**以** $i$ **结尾**，满足条件的子序列和字符串 $T$ 的前 $j$ 个字符匹配的方案数。

首先，为什么不能用矩阵优化？

经过观察，我们知道答案为：

$$
  \sum_{i=1}^{|S| \times k} dp_{i,|T|} \bmod 998244353
$$

但是我们发现，矩阵优化仿佛很难做到这一点。

这样子的话，我们只能通过矩阵来得到 $dp_{|S| \times k,|T|}$ 是等于几的，但是没有办法推算其他的等于几。

但是如果用 $\mathcal O(|S| \times k)$ 的时间复杂度去推算他的话，那又超时了。

这就是为什么这种办法不能用矩阵的解释，而如何让这个方法变成可以用矩阵优化的模型？

把状态中的 **以** $i$ **结尾**去掉，变成方法 2 就行了。

所以在无法矩阵优化的情况下，**请想想是不是您的状态的定义有点小问题**。

代码和转移都不放了，因为没有必要。

再来说说我们的正解。

### 数据范围：$k \leq 10^{18},|S| \leq 5 \times 10^3,|T| \leq 10$。

考虑到 $dp_{i,j}$ 状态中的 $j$ 比较小，考虑用矩阵乘法代替动态规划进行转移。

这个地方我们需要打包一下——原来是一个字符一个字符的推矩阵，然后乘起来得到答案，现在就是我们是先把整一个字符串的转移矩阵给求出来，然后再矩阵快速幂求出 $P^k$ 即可，其中 $P$ 就是得出的转移矩阵。

但是问题又来了，这个矩阵不固定，不是平常的矩阵题，怎么办？

考虑到 $|S| \leq 5 \times 10^3$，又考虑到矩阵的行列最大也就 $11$（因为 $dp_{i,0}$ 也算状态），乘起来也不会超时。

我们考虑让计算机构造矩阵。

我们设矩阵 $Ans_i$ 表示 $dp_i$ 的第 $2$ 维状态，其中 $Ans_{i,1,i}$ 对应的值就是 $dp_i$，容易看出该矩阵是 $1 \times (|T|+1)$ 的。

首先，对于固定转移 $dp_{i-1,j}$，在 $Ans_i$ 和 $Ans_{i+1}$ 中间的那个矩阵中，很明显，假设该矩阵为 $A$，那么就是 $A_{j,j}=1$。

但是如何考虑 $S_i=T_j$ 这件事情呢？我们可以直接一一判断，如果这个条件不满足，证明 $S_i$ 对应不上 $T_j$，那么也就不用管了。

但是如果他们两个能匹配，那么就是 $dp_{i-1,j-1}$ 这个转移了。

不难看出，$A_{j-1,j}$ 是等于 $1$ 的。

注意：这个地方的**矩阵下标是从** $0$ **开始**的。

那么有了这些，把这些矩阵一一乘起来，自然就是我们得到的 $P$ 矩阵了。

最后对 $P$ 做一个矩阵快速幂即可。

代码：

```cpp
#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
#define LL long long
using namespace std;
const LL mod=998244353;
struct matrix{
	LL a[12][12];
	int n,m;
	matrix(){
		for(int i=0;i<12;++i)
			for(int j=0;j<12;++j) a[i][j]=0; // 注意初始化，否则局部定义的变量的 a[i][j] 是随机的，很有可能会有问题
		n=m=0; // 初始化 n,m，一开始表示没有空间
	}
};
string s,t;
matrix operator * (matrix a,matrix b){
	matrix c;
	c.n=a.n,c.m=b.m;
	for(int i=1;i<=c.n;++i){
		for(int j=1;j<=c.m;++j){
			for(int k=1;k<=a.m;++k){ // 矩阵乘法
				c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j])%mod; // 注意取模
			}
		}
	}
	return c;
}
LL k,n,m;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>s>>t;
	n=s.size(),m=t.size();
	s=" "+s,t=" "+t; // 做好前面的准备工作
	matrix pan,ans;
	pan.n=m+1,pan.m=m+1; // 初始化 P 矩阵的大小
	for(int j=1;j<=m+1;++j) pan.a[j][j]=1; // 设置单位矩阵
	ans.n=1,ans.m=m+1; // 设置最终答案的矩阵大小
	ans.a[1][1]=1; // 即：dp[i][0]=1
	for(int i=1;i<=n;++i){
		matrix che;
		che.n=che.m=m+1;
		for(int j=1;j<=m+1;++j) che.a[j][j]=1; // 这个是默认的转移方式
		for(int j=2;j<=m+1;++j){
			if(s[i]==t[j-1]){ // 如果满足 s[i]=t[j-1]，则 dp[i-1][j-1] 可以递推到 dp[i][j] 这个位置
				++che.a[j-1][j]; // 这个地方的矩阵下标从 1 开始
			}
		}
		pan=pan*che;
	}
	while(k){ // 矩阵快速幂
		if(k&1) ans=ans*pan;
		pan=pan*pan,k>>=1;
	}
	cout<<ans.a[1][m+1]<<"\n";
	return 0; 
} 
```

### 正解代码易错点

1. 您没开 long long。
2. 您的矩阵可能是从下标 $0$ 开始的，但是你的矩阵乘法是从 $1$ 开始乘的。
3. 您的下标越界了，这是常见的事。
4. 您的矩阵状态中并没有表示 $dp_{i,0}$ 的位置。这是一个非常大的错误。
5. 您的矩阵没有初始化。
6. 您的矩阵的 $n,m$ 没有设置好就开始矩阵乘法了。
7. 您的 $P$ 矩阵的初始化并没有将其设为单位矩阵。
8. 您设置单位矩阵的时候可能也有问题，如果你的矩阵是从下标 $0$ 开始的，那么你可能会遗漏掉 $0$ 位置的初始化。

### 后言

OK，本题已经讲完了，如果有不懂的地方可以在评论区留言。

---

## 作者：AZYDLL (赞：0)

# 思路

## 朴素算法

直接计算答案是困难的，因为重复 $k$ 次的 $S$ 过长。因此我们考虑将 $T$ 分成 $k$ 段（可以为空），在每个 $S$ 中包含一段。于是令 $dp_{i,j}$ 表示 $i$ 个 $S$ 首尾相接组成的字符串中有多少个子序列为 $T_{1 \sim j}$，$f_{l,r}$ 表示 $S$ 中有多少个子序列为 $T_{l \sim r}$，得到转移方程：

$$
dp_{i,j}=dp_{i-1,j}+\sum_{k=0}^{j-1} dp_{i-1,k} \times f_{k+1,j}
$$

那么如何求出 $f$ 数组呢？我们先考虑简单一点的问题：

> 已知字符串 $S,T$，求 $S$ 中有多少个子序列为 $T$？

我们令 $g_{i,j}$ 表示 $S_{1 \sim i}$ 中有多少个子序列为 $T_{1 \sim j}$，得到转移方程：

$$
g_{i,j}=\left\{
\begin{align*}
& g_{i-1,j} & (S_i \neq T_j) \\
& g_{i-1,j}+g_{i-1,j-1} & (S_i=T_j)
\end{align*}\right.
$$

我们发现，如上的一次计算过后，我们已经得到了 $f_{1,1 \sim m}$，即 $f_{1,i}=g_{n,i}$。故同理，对于 $i \in [1,m]$，我们将 $T_{i \sim m}$ 和 $S$ 进行如上计算即可得到 $f$ 数组，时间复杂度 $O(nm^2)$。再结合前面的转移方程，就可以得到 $O(knm^2)$ 的总时间复杂度。

于是 40 分到手。

## 算法优化

$k \le 10^{18}$ 提示我们正解与线性及以上的 $k$ 无关，又注意到 $m \le 10$，于是考虑使用矩阵快速幂。还不会矩阵快速幂的朋友请移步 [P3390](https://www.luogu.com.cn/problem/P3390)。

显然当 $S$ 与 $T$ 确定时，$f$ 数组是确定的，因此可以使用矩阵快速幂。构造出初始矩阵 $K$ 与转移矩阵 $A$：

$$
K=
\begin{bmatrix}
dp_{0,0} & dp_{0,1} & dp_{0,2} & \cdots & dp_{0,m}
\end{bmatrix},
A=
\begin{bmatrix}
1 & f_{1,1} & f_{1,2} & \cdots & f_{1,m} \\
0 & 1 & f_{2,2} & \cdots & f_{2,m} \\
0 & 0 & 1 & \cdots & f_{3,m} \\
\vdots & \vdots & \vdots & \ddots & \vdots \\
0 & 0 & 0 & \cdots & 1
\end{bmatrix}
$$

显然我们要求的是 $dp_{k,m}$，于是目标矩阵为 $KA^k$，矩阵快速幂跑一遍即可。总时间复杂度 $O(nm^2+m^3 \log k)$，可以拿到满分。

# 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 5005
#define MAXM 15
#define MOD 998244353
#define int long long

using namespace std;
namespace FastIO
{
	inline string _rs()
	{
		string str="";
		int ch=getchar();
		while(ch==' ' || ch=='\n' || ch=='\r') ch=getchar();
		while(ch!=' ' && ch!='\n' && ch!='\r' && ch!=EOF){
			str.push_back(ch);
			ch=getchar();
		}
		return str;
	}
	inline void _ws(string a,char b)
	{
		int len=a.size();
		for(int i=0;i<len;i++) putchar(a[i]);
		putchar(b);
		return ;
	}
	inline int _r()
	{
		int flag=1,ans=0,ch=getchar();
		while((ch<'0' || ch>'9') && ch!=EOF){
			if(ch=='-') flag=-1;
			ch=getchar();
		}
		while(ch>='0' && ch<='9'){
			ans=(ans<<1)+(ans<<3)+(ch^48);
			ch=getchar();
		}
		return flag*ans;
	}
	inline void _w(int a,char b)
	{
		if(a<0) a=-a,putchar('-');
		int sta[22],top=0;
		do{
			sta[top++]=a%10;
			a/=10;
		}while(a);
		while(top) putchar(sta[--top]+48);
		putchar(b);
		return ;
	}
}
using namespace FastIO;

int k,n,m,dp[MAXN][MAXM],dp1[MAXN][MAXM],A[MAXM][MAXM],B[MAXM][MAXM],ANS[MAXM][MAXM];
string S,T,T1;

void DP(int p)
{
	int m1=m-p+1;
	string T1=" "+T.substr(p,m1);
	memset(dp1,0,sizeof(dp1));
	for(int i=0;i<=n;i++) dp1[i][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m1;j++){
			if(S[i]==T1[j]) dp1[i][j]=dp1[i-1][j-1];
			dp1[i][j]=(dp1[i][j]+dp1[i-1][j])%MOD;
		}
	}
	for(int i=1;i<=m1;i++) dp[p][p+i-1]=dp1[n][i];
	
	return ;
}

void mul1()
{
	for(int i=0;i<=m;i++){
		for(int j=0;j<=m;j++){
			B[i][j]=0;
			for(int kk=0;kk<=m;kk++) B[i][j]=(B[i][j]+A[i][kk]*A[kk][j])%MOD;
		}
	}
	
	for(int i=0;i<=m;i++) for(int j=0;j<=m;j++) A[i][j]=B[i][j];
	return ;
}

void mul2()
{
	for(int i=0;i<=m;i++){
		for(int j=0;j<=m;j++){
			B[i][j]=0;
			for(int kk=0;kk<=m;kk++) B[i][j]=(B[i][j]+ANS[i][kk]*A[kk][j])%MOD;
		}
	}
	
	for(int i=0;i<=m;i++) for(int j=0;j<=m;j++) ANS[i][j]=B[i][j];
	return ;
}

void init()
{
	for(int i=0;i<=m;i++) ANS[i][i]=1;
	for(int i=0;i<=m;i++){
		for(int j=0;j<i;j++) A[j][i]=dp[j+1][i];
		A[i][i]=1;
	}
	
	return ;
}

void Fpow()
{
	init();
	while(k){
		if(k&1) mul2();
		mul1();
		k=k>>1;
	}
	
	return ;
}

signed main()
{
	k=_r();
	S=" "+_rs(),n=S.size()-1;
	T=" "+_rs(),m=T.size()-1;
	for(int i=1;i<=m;i++) DP(i);
	
	Fpow();
	_w(ANS[0][m],'\n');
	return 0;
}
```

---

## 作者：orange_new (赞：0)

节选自：[DP做题记录（三）（2025.4.5 - 2025.4.19）](https://www.luogu.com.cn/article/tobtmxka)

[安利一下我的博客](https://www.cnblogs.com/JPGOJCZX/p/18834273)

由于 $m$ 小的可怜，我们考虑把 $T$ 这个字符串拆分成若干个子串，分别放入这 $k$ 个重复的 $S$ 中，然后就可以用组合数计算了。

那么问题就转变成了求出 $T$ 的所有字串在 $S$ 中作为子序列的出现次数。我们把 $T_{[l, r]}$ 单独抽出来，设 $dp_{i, j}$ 表示 $S$ 的前 $i$ 个字符中 $T_{l, j}$ 出现的次数，那么如果 $S_i = T_j$，就可以把 $dp_{i - 1, j - 1}$ 的值加进来，否则就只能赋值为 $dp_{i - 1, j}$，因此

$$
dp_{i, j} = 
\begin{cases}
dp_{i - 1, j} + dp_{i - 1, j - 1} & S_i = T_j\\
dp_{i - 1, j} & S_i \neq T_j
\end{cases}
$$

其中初值为 $dp_{0, 0} = 1$，可以发现这个式子和背包类似，因此第二维倒序枚举可以除掉 $j$ 这一维。于是我们在时间复杂度为 $O(nm^3)$，空间复杂度为 $O(n)$ 的情况下求出了 $T$ 的所有字串在 $S$ 中作为子序列的出现次数。

现在就比较好做了，我们将 $T$ 划分成若干个段，设划分了 $l$ 段，那么将这 $l$ 段放入 $k$ 个重复的 $S$ 中就有 $\displaystyle\binom kl$ 种方案，而这些方案的权值是这 $l$ 段分别在 $S$ 中作为子序列的出现次数的积，直接加入到答案中。由于 $m$ 只有 $10$，这部分的时间复杂度比较小，可以忽略不计，那么我们用 $O(nm^3)$ 的时间复杂度完成了此题。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e3 + 9, M = 19, MOD = 998244353;
int k, dp[N], tim[M][M], inv[M], fac[M], n, m, ans;
char s[N], t[M];
vector <int> vec;
int qpow(int a, int b){
	int res = 1;
	while(b > 0){
		if(b & 1)
			res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}
int binom(int a, int b){
	if(b > a)
		return 0;
	__int128 res = 1;
	for(int i = a; i >= a - b + 1; i--)
		res = res * i % MOD;
	return res * inv[b] % MOD;
}
void dfs(int now){
	if(now == 0){
		int l = 1, r, tmp = 1;
		for(int i = 0; i < (int)vec.size(); i++){
			r = l + vec[i] - 1;
			tmp = tmp * tim[l][r] % MOD;
			l = r + 1;
		}
		ans = (ans + tmp * binom(k, vec.size()) % MOD) % MOD;
		return;
	}
	for(int i = 1; i <= now; i++){
		vec.push_back(i);
		dfs(now - i);
		vec.pop_back();
	}
}
signed main(){
	scanf("%lld", &k);
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	n = strlen(s + 1);
	m = strlen(t + 1);
	fac[0] = 1;
	for(int i = 1; i <= m; i++)
		fac[i] = fac[i - 1] * i % MOD;
	inv[m] = qpow(fac[m], MOD - 2);
	for(int i = m - 1; i >= 0; i--)
		inv[i] = inv[i + 1] * (i + 1) % MOD;
	for(int l = 1; l <= m; l++){
		for(int r = l; r <= m; r++){
			memset(dp, 0, sizeof(dp));
			dp[0] = 1;
			for(int i = 1; i <= n; i++)
				for(int j = r; j >= l; j--)
					if(t[j] == s[i])
						dp[j - l + 1] = (dp[j - l + 1] + dp[j - l]) % MOD;
			tim[l][r] = dp[r - l + 1];
		}
	}
	dfs(m);
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Nazq (赞：0)

补充一下思考过程。

注意到 $|T|$ 很小。

$O(2 ^ {\lvert T \rvert})$ dfs 枚举把 $T$ 分成若干连续的区间，设有 $m$ 个。

有 $k$ 倍，每个区间在 $1$ 倍数上（类似于在 $k$ 个苹果中选 $m$ 个），为 $\dbinom{k}{m}$。

设 $g(l, r)$ 为 $T[l, r]$ 在 $S$ 上以子序列出现的数量。

转移对每个 $l$ 做一遍 $S$ 和 $T[l, n]$ 的匹配。

设 $f(i, l, r)$ 表示当前 $l$ 下，$S[1,i], T[l,r]$ 的方案数，且 $S_i = T_r$。

$$
f(i, l, r) = [S_i = T_r]\sum_{j = 1}^{i-1} f(j,l,r-1)
$$

前缀和优化 $O(|S||T|^2)$。

$m$ 个区间内部排序有 $\prod g(l_i,r_i)$（根据 $1, 2$），$l_i,r_i$ 是分割区间的左右端点。
乘法原理，有 $\dbinom{k}{m} \prod g(l_i,r_i)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353, N = 5e3 + 5, M = 15;
ll K, f[N][M][M], g[M][M], ans, res, inv[M] = {0, 1, 499122177, 166374059, 291154603, 856826403, 641926577, 376916469, 421456191, 712324701, 370705776, 305948985, 275056837};
int n, m;
vector<pair<int, int> > v;
char s[N], t[M];
ll C(const ll &n, const ll &m) {
    ll res = 1;
    for (ll i = n - m + 1; i <= n; ++i)
        res = (__int128)res * i % mod;
    res = (__int128)res * inv[m] % mod;
    return res;
}
void dfs(int cnt, int lst) {
    if (cnt == m + 1) {
        if (lst <= m)
            return;
        res = 1;
        for (pair<int, int> i : v)
            res = (__int128)res * g[i.first][i.second] % mod;
        res = (__int128)res * C(K, v.size()) % mod;
        (ans += res) %= mod;
        return;
    }
    dfs(cnt + 1, lst);
    v.push_back({lst, cnt});
    dfs(cnt + 1, cnt + 1);
    v.pop_back();
}
int main() {
    scanf("%lld%s%s", &K, s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);
    for (int i = 1; i <= m; ++i) {
        f[0][i][i - 1] = 1;
        for (int j = 1; j <= n; ++j)
            (f[j][i][i - 1] += f[j - 1][i][i - 1]) %= mod;
        for (int j = i; j <= m; ++j) {
            for (int k = 1; k <= n; ++k)
                if (s[k] == t[j])
                    f[k][i][j] = f[k - 1][i][j - 1];
            for (int k = 1; k <= n; ++k)
                (f[k][i][j] += f[k - 1][i][j]) %= mod;
            g[i][j] = f[n][i][j];
        }
    }
    dfs(1, 1);
    printf("%lld", ans);
    return 0;
}
```

---

