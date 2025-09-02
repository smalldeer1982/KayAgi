# variance

## 题目描述

给定序列 $a_1,a_2,\cdots,a_n$，定义 $f(l,r)=(a_l\oplus a_{l+1}\oplus \cdots \oplus a_r)+(a_l\vee a_{l+1}\vee \cdots \vee a_r)$，其中 $\oplus$ 表示 **按位异或** 运算，$\vee$ 表示 **按位或** 运算。

你需要求出所有满足 $1\le l \le r \le n$ 的 $f(l,r)$ 的方差 $v$。为避免精度误差，以及答案可能很大，请输出 $(v\times \frac{n^2\times (n+1)^2}{4}) \kern{3pt}\mathrm {mod}\kern{3pt} 998244353$。

**注意：运算过程中不取模，仅将结果取模。**

## 说明/提示

方差的定义：对于 $n$ 个数 $a_1,a_2,\cdots,a_n$，它们的方差是：

$$
\frac 1 n\sum_{i=1}^n (a_i-\bar{a})^2
$$

其中 $\bar{a}$ 为 $a_1,a_2,\cdots,a_n$ 的平均数，即 $\dfrac {1} {n} \displaystyle\sum\limits_{i=1}^n a_i$。

----

对于 $10\%$ 的数据，$n \le 50$。

对于 $30\%$ 的数据，$n \le 5000$。

对于另 $20\%$ 的数据，$a_i \le 100$。  

对于 $100\%$ 的数据，$1\le n\le 10^5,1\le a_i < 2^{31}$。

## 样例 #1

### 输入

```
3
2 1 3```

### 输出

```
80```

## 样例 #2

### 输入

```
4
4 1 3 2```

### 输出

```
1244```

## 样例 #3

### 输入

```
5
1 2 3 2 1```

### 输出

```
444```

# 题解

## 作者：Galex (赞：4)

#### 先考虑简化所求答案：

对与原序列的 $m=\large\frac{n(n+1)}2$ 个区间，设区间按位或的值为 $o_1,o_2,\dots,o_m$，对应的按位异或的值为 $x_1,x_2,\dots,x_m$，则每个区间的 $f$ 值为 $f_i=o_i+x_i\kern{3pt} (i=1,2,\dots,m)$，所求答案即为 $f_1,f_2,\dots,f_m$ 这 $m$ 个数的方差的 $m^2$ 倍 $\kern{1pt}\mathrm {mod}\kern{3pt} 998244353$ 的值。

设这 $m$ 个数的平均数为 $\bar{f}=\frac{1}{m}\sum_{i=1}^{m}f_i$，方差为 $s^2=\frac{1}{m}\sum_{i=1}^m(f_i-\bar{f})^2$，考虑简化所求答案 $m^2s^2$：
$$
\begin{aligned}
&m^2s^2\\
&=m\sum_{i=1}^m(f_i-\bar f)^2\\
&=m\sum_{i=1}^m(f_i^2-2f_i\bar f+\bar f^2)\\
&=m\sum_{i=1}^mf_i^2-2m\bar f\sum_{i=1}^mf_i+m^2\bar f^2\\
&=m\sum_{i=1}^mf_i^2-2\times(\sum_{i=1}^mf_i)^2+(\sum_{i=1}^mf_i)^2\\
&=m\sum_{i=1}^mf_i^2-(\sum_{i=1}^mf_i)^2
\end{aligned}
$$
又由 $f_i=o_i+x_i$，有：
$$
\begin{aligned}
&m^2s^2\\
&=m\sum_{i=1}^mf_i^2-(\sum_{i=1}^mf_i)^2\\
&=m\sum_{i=1}^m(o_i+x_i)^2-(\sum_{i=1}^m(o_i+x_i))^2\\
&=m\times(\sum_{i=1}^m o_i^2+\sum_{i=1}^m 2o_ix_i+\sum_{i=1}^m x_i^2)-(\sum_{i=1}^m o_i+\sum_{i=1}^m x_i)^2
\end{aligned}
$$
所以答案可转化为求各个区间五部分和：
$$
A=\sum_{i=1}^m o_i^2\quad
B=\sum_{i=1}^m 2o_ix_i\quad
C=\sum_{i=1}^m x_i^2\quad
D=\sum_{i=1}^m o_i\quad
E=\sum_{i=1}^m x_i
$$

#### 首先考虑仅与 $o_i$ 相关的 $A,D$：

一种暴力的方法是：对于每个左端点 $l$，初始化区间按位或和为 $o=0$。接下来右端点 $r$ 依次遍历 $l,l+1,\dots,n$，每次遍历到新的 $r$ 就将 $o$ 赋值为 $o\vee a_r$，就得到了区间 $[l,r]$ 对应的按位异或和，分别累加 $o$ 和 $o^2$ 即可。

仔细考虑整个过程，可以发现 $o$ 的变化是存在约束的。详细地说，在二进制下，$o$ 不断按位或并赋值的过程中，$o$ 中已经为 $1$ 的二进制位不会变为 $0$，只有仍然为 $0$ 的位可能在某次按位或后变成 $1$，并保留到当前左端点处理完。这么看来在 $n$ 较大时，$o$ 在右端点遍历过程中很多时候是不变的。具体地描述 $o$ 的改变次数，设 $a$ 的值域为 $V$，每次改变会使 $o$ 二进制下 $0$ 的个数至少减少 $1$（由于位运算特点，此处包括以下讨论只考虑每个数二进制下最低的 $\lceil\log V\rceil+1$ 位），所以对于一个左端点，$o$ 的改变次数至多为 $\lceil\log V\rceil+1$ 次。据此对右端点分段，可得到 $O(\log V)$ 段。每段中 $o$ 为定值，则对于 $A,D$ 的贡献易求。

#### 接下来考虑仅与 $x_i$ 相关的 $C,E$：

按位异或没有上述按位或的性质，但区间按位异或可以用异或前缀和转化为两个数的异或。

设 $s_i=a_1\oplus a_2\oplus\dots\oplus a_i$，特别地，$s_0=0$。则对于区间 $[l,r]$，$a_l\oplus a_{l+1}\oplus\dots\oplus a_r=s_{l-1}\oplus s_r$。

仍然固定左端点 $l$。设 $\mathrm{bit}(x,i)\in \{0,1\}$ 为自然数 $x$ 二进制下从低至高第 $i$ 位（从 $0$ 开始）上的值，则对于每个位数 $i$ 和右端点 $r$，若 $\mathrm{bit}(s_{l-1}, i)\oplus \mathrm{bit}(s_r,i)=1$，会对 $E$ 产生 $2^i$ 的贡献。进一步地，若有 $\mathrm{cnt}1_{i,j}$（其中 $0\leq i\leq\lceil\log{V}\rceil,j\in\{0,1\}$） 个右端点 $r$ 满足 $l\leq r\leq n$ 且 $\mathrm{bit}(s_r,i)=j$，那么左端点 $l$ 对 $E$ 的贡献为 $\sum_{i=0}^{\lceil\log{V}\rceil}2^i\times \mathrm{cnt}1_{i,\mathrm{bit}(s_{l-1},i)\oplus1}$。

$C$ 的计算与此类似。设 $\mathrm{val}(x,i)=2^i\times \mathrm{bit}(x,i)$，则

$x=\sum_{i=0}^{\lceil\log{V}\rceil}\mathrm{val}(x,i)$，$x^2=\sum_{0\leq i,j\leq\lceil\log{V}\rceil}\mathrm{val}(x,i)\times \mathrm{val}(x,j)=\sum_{0\leq i,j\leq\lceil\log{V}\rceil}\mathrm{bit}(x,i)\times \mathrm{bit}(x,j)\times2^{i+j}$。

对于每两个位数 $i,j$ 和右端点 $r$，若 $\mathrm{bit}(s_{l-1},i)\oplus \mathrm{bit}(s_r,i)=1$ 且 $\mathrm{bit}(s_{l-1},j)\oplus \mathrm{bit}(s_r,j)=1$，会对 C 产生 $2^{i+j}$ 的贡献。进一步地，若有 $\mathrm{cnt}2_{i,u,j,v}$（其中 $0\leq i,j\leq\lceil\log{V}\rceil,u,v\in\{0,1\}$）个右端点 $r$ 满足 $l\leq r\leq n$ 且 $\mathrm{bit}(s_{l-1},i)=u$ 且 $\mathrm{bit}(s_{l-1},j)=v$，那么左端点 $l$ 对 $C$ 的贡献为 $\sum_{0\leq i,j\leq\lceil\log{V}\rceil}\mathrm{cnt}2_{i,\mathrm{bit}(s_{l-1},i)\oplus1,j,\mathrm{bit}(s_{l-1},j)\oplus1}\times2^{i+j}$。

而 $\mathrm{cnt1,cnt2}$ 在 $l$ 从大到小的遍历过程中不难求得，故 $C,E$ 可求。

#### 最后考虑 $B$

固定左端点 $l$，并将右端点按照按位或的性质分段。设右端点 $r$ 在 $i\leq r\leq j$ 的区间中，所得区间 $[l,r]$ 按位或的值都是 $o$，则这段的贡献为 $\sum 2o_kx_k=2o\sum x_k$（即提出固定的 $2o$，不写出确切的上下界）。$\sum x_k$ 仍考虑按二进制位计算贡献。设 $1,2,...,k$ 中有 $\mathrm{cnt}3_{k,u,v}$ 个位置 $x$ 满足 $\mathrm{bit}(s_x,u)=v$，则固定的 $l$ 与 $i\leq r\leq j$ 的 $r$ 对 $B$ 的贡献为 $2o\sum_{k=0}^{\lceil\log{V}\rceil}2^i\times(\mathrm{cnt}3_{j-1,\mathrm{bit}(s_{l-1},k)\oplus1}-\mathrm{cnt}3_{i-1,\mathrm{bit}(s_{l-1},k)\oplus1})$。

$\mathrm{cnt}3$ 可以在读入后初始化，故 $B$ 的计算可以与 $A,D$ 一同完成。

#### 复杂度分析

对于 $A,B,D$ 分段过程的实现可以借助预处理数组 $b_{i,j}$： 表示最小的 $k\geq i$ 满足 $\mathrm{bit}(a_k,j)=1$。对于固定左端点 $l,r$，从 $l$ 开始，借助 $b$ 找到下一个分段点 $rr$，使得右端点在 $[r,rr)$ 中时对应区间的按位或为定值。由于有 $O(n\log V)$ 段，而次寻找下一个断点的时间复杂度为 $O(\log V)$，故分段过程总时间复杂度为 $O(n\log^2{V})$。

每一段中，$A,D$ 的贡献计算是 $O(1)$ 的，而 $B$ 的计算需要枚举每个二进制位，时间复杂度为 $O(\log V)$，故 $A,B,D$ 的计算总时间复杂度为 $O(n\log^2 V)$。

对于 $C,E$ 的计算，在从大到小遍历左端点的过程中，$\mathrm{cnt}1$ 的计算是每次 $O(\log V)$，$\mathrm{cnt}2$ 的计算是每次 $O(\log^2 V)$。而通过 $\mathrm{cnt}1$ 计算 $E$ 需要枚举每个二进制位，每个左端点时间复杂度为 $O(\log V)$；通过 $\mathrm{cnt}2$ 计算 $C$ 需要枚举每对二进制位，每个左端点时间复杂度为 $O(\log^2 V)$。故计算 $C$ 的时间复杂度是 $O(n\log^2 V)$，计算 $E$ 的时间复杂度是 $O(n\log V)$。

对于空间复杂度，容易发现整个过程中数组开销最大为 $O(n\log V)$。

#### 总结

综上所述，我们以 $O(n\log^2 V)$ 的时间复杂度，$O(n\log V)$ 的空间复杂度解决了这个问题。

---

## 作者：Celtic (赞：2)

求方差只需要求出 $\sum_{l=1}^n\sum_{r=l}^{n} f(l,r)$ 和 $\sum_{l=1}^n\sum_{r=l}^{n} f(l,r)^2$。因为第一个明显弱于第二个所以只考虑第二个怎么求。

考虑将贡献拆位，并将平方拆成两位的乘积。枚举两位 $i,j$，设分别 $b_k,c_k$ 表示 $a_k$  第 $i,j$ 位的值，于是 $f_{l,r}$ 在第一位为 $i$，第二位为 $j$ 时的贡献就是 
$$((b_l⊕b_{l+1}⊕\cdots ⊕b_r)+(b_l∨b_{l+1}∨\cdots ∨b_r))\times((c_l⊕c_{l+1}⊕\cdots ⊕c_r)+(c_l∨c_{l+1}∨\cdots ∨c_r))$$

分别对左右两个括号为 $1/2,1/2$ 的四种情况计数即可。计数的方法可以维护最后一个 $1$ 的位置和前缀和的奇偶性，这里不懂的可以看代码。

时间 $O(n\log^2 V)$，空间 $O(n)$。

```cpp

#include<bits/stdc++.h>
#define N 1001001
#define MAX 2001
#define inf 1e18
using namespace std;
typedef long long ll;
typedef long double db;
const ll mod=998244353,inv2=(mod+1)/2;
inline void read(ll &ret)
{
    ret=0;char c=getchar();bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,a[N],sum,sum2,b[N],b1[N],b2[N],c[N][2][2];
signed main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i]);
	for(int k=0;k<=31;k++)//和
	{
		for(int i=1;i<=n;i++)
			b[i]=((a[i]>>k)&1);
		ll res=0;
		ll cnt0=0,cnt1=0;
		cnt0++;
		ll s=0;
		ll las=0;
		for(int r=1;r<=n;r++)
		{
			s+=b[r];
			s&=1;
			if(s==1)
				res+=cnt0,cnt1++;
			else
				res+=cnt1,cnt0++;
			if(b[r])
				las=r;
			res+=las;
			res%=mod;
		}
		sum+=res*((1ll<<k)%mod)%mod;
		sum%=mod;
		sum-=sum>=mod?mod:0;
	}
	for(int k1=0;k1<=31;k1++)//平方和
	{
		for(int k2=0;k2<=31;k2++)
		{
			ll res=0;
			for(int i=1;i<=n;i++)
				b1[i]=(a[i]>>k1)&1,b2[i]=(a[i]>>k2)&1;
			c[0][0][0]=1;
			ll las1=0,las2=0,s1=0,s2=0;
			for(int i=1;i<=n;i++)
			{
				memcpy(c[i],c[i-1],sizeof(c[i]));
				if(b1[i])
					las1=i;
				if(b2[i])
					las2=i;
				s1+=b1[i],s2+=b2[i];
				s1&=1,s2&=1;
				c[i][s1][s2]++;
				if(min(las1,las2)==0)
					continue;
				res+=1*1*(c[min(las1,las2)-1][s1][s2]);
				res+=1*2*(c[min(las1,las2)-1][s1][s2^1]);
				res+=2*1*(c[min(las1,las2)-1][s1^1][s2]);
				res+=2*2*(c[min(las1,las2)-1][s1^1][s2^1]);
				res%=mod;
			}
			sum2+=((1ll<<k1)%mod)*((1ll<<k2)%mod)%mod*res%mod;
			sum2%=mod;
			sum2-=sum2>=mod?mod:0;
		}
	}
	printf("%lld\n",(sum2*n%mod*(n+1)%mod*inv2%mod-sum*sum%mod+mod)%mod);
    exit(0);
}
```

---

