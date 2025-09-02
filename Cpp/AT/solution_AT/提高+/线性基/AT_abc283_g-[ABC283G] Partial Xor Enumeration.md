# [ABC283G] Partial Xor Enumeration

## 题目描述

给定一个长度为 $N$ 的非负整数序列 $A=(A_1,A_2,\ldots,A_N)$。

对于非负整数序列 $(a_1,a_2,\ldots,a_n)$，其 $\operatorname{xor}$ 定义为：存在一个整数 $X$，使得对于所有非负整数 $j$，满足以下条件：

- 当且仅当 $a_1,\ldots,a_n$ 中，用二进制表示时第 $2^j$ 位为 $1$ 的数的个数为奇数时，$X$ 的第 $2^j$ 位为 $1$。

设非负整数集合 $\lbrace s_1,s_2,\ldots,s_k\rbrace\ (s_1<s_2<\cdots<s_k)$ 为可以通过 $A$ 的（不一定连续，可以为空）子序列的 $\operatorname{xor}$ 得到的所有整数的集合。

给定整数 $L,R$，请按顺序输出 $s_L,s_{L+1},\ldots,s_R$。

## 说明/提示

### 数据范围

- $1\leq N\leq2\times10^5$
- $0\leq A_i<2^{60}\ (1\leq i\leq N)$
- $1\leq L\leq R\leq k$
- $R-L\leq2\times10^5$
- 输入均为整数

### 样例解释 1

$A$ 的所有可能的（不一定连续）子序列有 $(),(2),(17),(21),(2,17),(2,21),(17,21),(21,17),(21,21),(2,17,21),(2,21,17),(2,21,21),(21,17,21),(2,21,17,21)$ 共 $14$ 种。它们的 $\operatorname{xor}$ 分别如下：

- 空序列的 $\operatorname{xor}$ 为 $0$。
- $(2)$ 的 $\operatorname{xor}$ 为 $2$。
- $(17)$ 的 $\operatorname{xor}$ 为 $17$。
- $(21)$ 的 $\operatorname{xor}$ 为 $21$。
- $(2,17)$ 的 $\operatorname{xor}$ 为 $19$。
- $(2,21)$ 的 $\operatorname{xor}$ 为 $23$。
- $(17,21)$ 的 $\operatorname{xor}$ 为 $4$。
- $(21,17)$ 的 $\operatorname{xor}$ 为 $4$。
- $(21,21)$ 的 $\operatorname{xor}$ 为 $0$。
- $(2,17,21)$ 的 $\operatorname{xor}$ 为 $6$。
- $(2,21,17)$ 的 $\operatorname{xor}$ 为 $6$。
- $(2,21,21)$ 的 $\operatorname{xor}$ 为 $2$。
- $(21,17,21)$ 的 $\operatorname{xor}$ 为 $17$。
- $(2,21,17,21)$ 的 $\operatorname{xor}$ 为 $19$。

因此，$A$ 的子序列的按位异或可能得到的值的集合为 $\lbrace0,2,4,6,17,19,21,23\rbrace$。

### 样例解释 5

请注意，输入或输出的数值可能超出 $32\operatorname{bit}$ 整数范围。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 1 8
2 21 17 21```

### 输出

```
0 2 4 6 17 19 21 23```

## 样例 #2

### 输入

```
4 3 7
2 21 17 21```

### 输出

```
4 6 17 19 21```

## 样例 #3

### 输入

```
5 1 1
0 0 0 0 0```

### 输出

```
0```

## 样例 #4

### 输入

```
6 21 21
88 44 82 110 121 80```

### 输出

```
41```

## 样例 #5

### 输入

```
12 26 48
19629557415 14220078328 11340722069 30701452525 22333517481 720413777 11883028647 20926361028 24376768297 720413777 27999065315 13558621130```

### 输出

```
13558621130 14220078328 14586054825 15518998043 15970974282 16379590008 17091531049 17412316967 17836964726 18263536708 18965057557 19629557415 20282860278 20926361028 21302757781 21908867832 22333517481 22893781403 23595304394 23723463544 24376768297 24885524507 25261923402```

# 题解

## 作者：Raisetsu41 (赞：5)

其实比较容易看出是线性基模板题。   
那就讲讲线性基与其扩展。

## $\mathbb{Definition}$
现有一正整数集 $S$ ，关于 $S$ 构造的线性基可以视为另一个集合，且满足以下性质

- 可以通过线性基中子集的异或值得到 $S$ 中所有子集的异或值，且线性基的元素个数在满足条件的情况下最小
- 线性基中子集异或值不存在 $0$
- 线性基中不同子集的异或值不同
- 线性基中不同元素的二进制最高位互不相同

不严谨的一句话概述：线性基与原集合在关于异或的问题上等价，且元素个数小于原集合。

## $\mathbb{Build}$

首先令线性基元素集合为 $Base$ 。

### $\mathbb{Insert}$

在插入某个数 $val$ 时，从二进制最高位往最低位扫。   

在第 $i$ 位有值的情况下，若 $base_i$ 不存在，就 $base_i := val$，否则 $val \otimes base_i$ 。   

```cpp
void insert (LL val) {
	for (int i = BIT; i >= 0; i--) {
		if ((1ll << i) & val) {
			if (base[i] == 0) {
				base[i] = val;;
				break;
			} else val ^= base[i];
		}
	}
}
```

### $\mathbb{Min/Max \ Query}$

贪心思想

```cpp
LL query_min() {
	for (int i = 0; i <= BIT; i++) if (base[i]) return base[i];
	return 0;
}
LL query_max() {
	LL res = 0;
	for (int i = BIT; i >= 0; i--) if ((res ^ base[i]) > res) res ^= base[i];
	return res;
}
```

### $\mathbb{Kth \ query}$

首先对线性基进行改造，使得线性基的每一位都相互独立。   
目标是在改造后使得二进制的每一位 $i$ 上，除了 $base_i$ 是 $1$ 其他的均为 $0$ 。   
具体来说，从高往低扫，如果存在 $i < j$ ，且 $a_j$ 的第 $i$ 位是 $1$，就将 $a_j$ 异或上 $a_i$。   
查询就是二进制拆分。   

```cpp
void rebuild() {
	for (int i = BIT; i >= 0; i--)
		for (int j = i - 1; j >= 0; j--) if (base[i] & (1ll << j))
			base[i] ^= base[j];
	for (int i = 0; i <= BIT; i++) if (base[i]) p[cnt++] = base[i];
}
int querykth(int k) {
	int res = 0;
	if (k >= (1ll << cnt)) return 0x3f3f3f3f;
	for (int i = BIT; i >= 0; i--) if (k & (1ll << i)) {
		res ^= p[i];
	}
	return res;
}
```

---

## 作者：joke3579 (赞：4)

## $\text{Statement}$

对于一个非负整数序列 $a = (a_1, a_2, \dots, a_n)$，我们定义其的异或是一个非负整数 $X$，使得对于任意非负整数 $j$ 有 $X$ 二进制的第 $j$ 位为 $1$ 当且仅当 $a$ 中有奇数个元素满足二进制的第 $j$ 位为 $1$。

给定一个 $n$ 长度序列 $A = (A_1, A_2, \dots, A_n)$。令 $\{s_1, s_2, \dots, s_k\}\ (s_1 < s_2 < \cdots < s_k)$ 为 $A$ 的所有可空子序列的异或组成的集合。注意子序列不一定连续。

再给定两个整数 $l, r$，请输出 $s_l, s_l + 1,\dots, s_r$。

$1\le n \le 2\times 10^5, \ 0\le A_i < 2^{60},\ 1\le l \le r \le k, \ r - l \le 2\times 10^5$。

## $\text{Solution}$

重写题意如下：
给定 $\mathbb F_2^{60}$ 空间内的 $n$ 个向量，你需要求出它们的张成中第 $[l,r]$ 小的元素。

首先考虑第 $k$ 小如何求得。

我们求出该张成的一组异或线性基 $L$，满足任意一维只存在一个向量在这一维取 $1$。由于张成中任意向量 $\textbf u$ 都可以被唯一地表示为线性基中一组向量的异或，$L$ 中任意一个子集都可以不重不漏地构成原张成中一个向量。

记 $L$ 的大小为 $x$，$L$ 中第 $0\le i < x$ 小的元素为 $L_i$，$k$ 在二进制下的第 $i$ 位为 $k_i$。不难发现第 $k$ 小即为
$$\bigoplus _{i = 0}^{x-1} k_i \times L_i$$

其中 $\bigoplus$ 表示异或。

随后考虑如何由第 $k$ 小生成第 $k + 1$ 小。

将 $k$ 与 $k + 1$ 写作二进制后可以发现，$+1$ 使得 $k$ 最后的一段 $1$ 变为了 $0$，最低的 $0$ 变成了 $1$。记 $k$ 中最低的 $0$ 位于第 $p$ 位，我们只需要将原先的答案异或 $\bigoplus_{0\le i\le p} L_i$ 即可得到 $+1$ 后的答案。这点可以通过预处理 $L_i$ 的前缀异或值在 $O(1)$ 的复杂度内完成。

总时间复杂度为 $O(n\log n + (r - l))$，其中线性基的大小为 $O(\log n)$。

[Submission](https://atcoder.jp/contests/abc283/submissions/37532674).

---

## 作者：_Kenma_ (赞：1)

# abc283_g 解题报告

## 前言

首先这个题面就很抽象。

其实就是求序列任意数的异或和中，第 $l$  小到第 $r$ 小的数。

## 思路分析

其实是模板题。

考虑线性基可以求异或第 $k$ 小，直接循环枚举 $[l,r]$，直接求就行了。

复杂度 $O(n \log v)$。

所以这篇题解主要讲线性基为什么能以及怎样求异或第 $k$ 小。

首先其实我们写的最多的，从高位到低位贪心插入的线性基并没有很好的性质。

比如说，线性基中的一个元素 $a_i$，只能满足它的最高位是 $i$，但是对它的低位并没有限制，也就是说，它不是所有可能的 $a_i$ 中最小的一个。

考虑这样修改我们贪心构建的线性基。

对于每一个线性基中的元素 $a_i$，枚举它在线性基中的所有低位元素 $a_j$，将 $a_i$ 异或上 $a_j$，以此消去 $a_i$ 的低位 $1$。这样 $a_i$ 依然是合法的，但是 $a_i$ 变成了所有可能的 $a_i$ 中最小的一个。


值得一提的是，这样依次消去 $a_i$ 的低位 $1$ 的操作和高斯消元构建线性基的本质是相同的。因为消去低位 $1$ 的过程也可以被理解为构建上三角矩阵。

这样重新构建的线性基就有了很好的性质。

不难发现，这样构造，使得线性基中的每一个元素 $a_i$，有且只有它在第 $i$ 位上是 $1$。

可能文字还是比较苍白，上图：

![](https://cdn.luogu.com.cn/upload/image_hosting/n95gepwt.png)


~~放错了。~~


![](https://cdn.luogu.com.cn/upload/image_hosting/qdnhr2vb.png)

这张是对的。

从左往右由高到低，和高斯消元的结果应该是一样的。

然后考虑怎样求第 $k$ 小。

注意到调整后线性基中的元素只会越异或越大，并且越高位的线性基，它和别人异或的结果会严格大于它不参与异或的结果。

所以第 $k$ 小元素就是将 $k$ 二进制拆分后，选择 $k$  这一位是 $1$ 的若干个线性基中的元素异或起来的结果。

比如求上图的线性基的异或第 $3$ 小值，应该让第三个元素和第四个元素异或，结果是 $5$。

具体实现看代码。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,r,a[200005];
int base[65],flag;
void insert(int a){
	for(int i=61;i>=1;i--){
		if(a&(1ll<<(i-1))){
			if(base[i]) a^=base[i];
			else{
				base[i]=a;
				break;
			}
		}
	}
	flag=1;
}
void rebuild(){
	for(int i=1;i<=61;i++){
		for(int j=1;j<i;j++){
			if(base[i]&(1ll<<(j-1))) base[i]^=base[j];
		}
	}
}
int query_k(int k){
	int ans=0;
	k-=flag;
	if(!k) return 0;
	for(int i=1;i<=61;i++){
		if(base[i]){
			if(k&1) ans^=base[i];
			k>>=1;
		}
	}
	return ans;
}
signed main(){
	cin>>n>>l>>r;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		insert(a[i]); 
	}
	rebuild();
	for(int i=l;i<=r;i++){
		cout<<query_k(i)<<' ';
	}
	return 0;
}
```

## 后记

终于把线性基的技能点点满啦！

---

## 作者：39xiemy (赞：1)

## 题目大意

给定一个长度为 $n$ 的序列 $A$，集合 $s$ 是由 $A$ 所有可空子序列的元素的异或组成的。将集合 $s$ 排序后，给出 $l$ 和 $r$，求 $s_l,s_{l+1}, \dots ,s_r$ 的值。

## 分析

线性基~~模板~~题。

线性基的基础操作是查询异或最大最小值，无法直接求出异或第 $k$ 小。于是考虑重构线性基数组 $p$，使得 $p_i = 2^i$，然后将**非 $\bm0$ 的线性基**加入一个新数组 $c$ 中。再将 $k$ 二进制拆分，第 $i$ 位上有 $1$，答案就异或上 $c_i$ 即可，注意特判 $0$。重构时间复杂度为 $O(\log^2 V)$。 

由于 $r-l \le 2 \times 10^5$，查询第 $k$ 小的时间复杂度为 $O(\log V)$，$V$ 为值域。所以可以直接求 $r-l+1$ 次异或第 $k$ 小，时间复杂度为 $O((r-l+1)\log V)$。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,l,r,b,p[61],tot,c[61],ans;
inline void add(int n) //构造线性基 
{
	for(int i=60;i>=0;i--)
	{
		if(n&(1ll<<i))
		{
			if(!p[i])
			{
				p[i]=n;
				break;
			}
			n^=p[i];
		}
	}
	return;
}
inline void chong() //重构操作 
{
	for(int i=60;i>=0;i--)
	{
		for(int j=i-1;j>=0;j--)//枚举比i小的每一位 
		{
			if(p[i]&(1ll<<j))
			{
				p[i]^=p[j];//如果pi的二进制的第j位上为1，就异或上pj,使第j位变为0 
			}
		}
	}
	for(int i=0;i<=60;i++)
	{
		if(p[i])  
		{
			c[tot++]=p[i];//存入数组c里
		}
	}
	return;
}
inline int kth(int k)
{
	ans=0;
	for(int i=tot-1;i>=0;i--)
	{
		if(k&(1ll<<i))
		{
			ans^=c[i]; //若k的第i位上是1，答案就异或上ci 
		}
	}
	return ans;
}
signed main()
{
	cin>>a>>l>>r;
	for(int i=1;i<=a;i++)
	{
		cin>>b;
		add(b);
	}
	chong();
	for(int i=l;i<=r;i++)
	{
		cout<<kth(i-1)<<' ';//由于有0的存在，真实排名要加1，也就是查询时要减1
	}
	return 0;
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc283_g)

# 前置知识

[线性基](https://oi-wiki.org/math/linear-algebra/basis/) 

# 解法

考虑线性基。

因为有可空子序列也参与运算，所以第 $1$ 小的数是 $0$；但线性基中是不允许有异或和为 $0$ 的存在，故线性空间内第 $k-1$ 小的数就是所求的第 $k$ 小的数。

令每一个二进制位仅在它这一位的基底上出现，其他位上的基底直接异或掉。

将 $k$ 二进制分组后取每一位的基底异或起来即可。

观察到 $r-l \le 2 \times 10^{5}$，暴力处理每一组询问即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll d[70];
vector<ll>dd;
void insert(ll x)
{
    for(ll i=60;i>=0;i--)
    {
        if((x>>i)&1)
        {
            if(d[i]==0)
            {
                d[i]=x;
                break;
            }
            x^=d[i];
        }
    }
}
ll ask(ll x)
{
    x--;
    ll ans=0;
    for(ll i=0;i<dd.size();i++)
    {
        if((x>>i)&1)
        {
            ans^=dd[i];
        }
    }
    return ans;
}
int main()
{
    ll n,l,r,x,i,j;
    cin>>n>>l>>r;
    for(i=1;i<=n;i++)
    {
        cin>>x;
        insert(x);
    }
    for(i=0;i<=60;i++)
    {
        if(d[i]!=0)
        {
            for(j=0;j<=i-1;j++)
            {
                if((d[i]>>j)&1)
                {
                    d[i]^=d[j];
                }
            }
            dd.push_back(d[i]);
        }
    }
    for(i=l;i<=r;i++)
    {
        cout<<ask(i)<<" ";
    }
    return 0;
}
```

# 后记

多倍经验： [HDU3949 XOR](https://vjudge.net/problem/HDU-3949)

---

