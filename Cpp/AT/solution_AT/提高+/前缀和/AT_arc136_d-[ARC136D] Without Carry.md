# [ARC136D] Without Carry

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc136/tasks/arc136_d

長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます．

整数の組 $ (i,j) $ ($ 1\ \leq\ i\ <\ j\ \leq\ N $) であって，$ A_i+A_j $ を筆算で計算する際に繰り上がりが発生しないものの個数を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^6 $
- $ 0\ \leq\ A_i\ \leq\ 10^6-1 $
- 入力される値はすべて整数

### Sample Explanation 1

数えるべき組 $ (i,j) $ は，$ (1,3),(1,4),(2,4) $ の $ 3 $ つです． 例えば，$ A_1+A_3=4+12 $ を計算する際には繰り上がりが発生しないので，$ (i,j)=(1,3) $ は数えます． 反対に，$ A_3+A_4=12+90 $ を計算する際には繰り上がりが発生するので，$ (i,j)=(3,4) $ は数えません．

## 样例 #1

### 输入

```
4
4 8 12 90```

### 输出

```
3```

## 样例 #2

### 输入

```
20
313923 246114 271842 371982 284858 10674 532090 593483 185123 364245 665161 241644 604914 645577 410849 387586 732231 952593 249651 36908```

### 输出

```
6```

## 样例 #3

### 输入

```
5
1 1 1 1 1```

### 输出

```
10```

# 题解

## 作者：Galois_Field_1048576 (赞：4)

## 题目描述
给定一个长度为 $n$ 的数列 $S$，设 $A_{i,j}$ 代表 $S_i$ 十进制表示法中从右往左数第 $j$ 位的数，如果字符串长度 $<j$ 则 $A_{i,j} = 0$。

求满足 $\forall k \in [1, 7], A_{i, k} + A_{j, k} < 10$ 的二元数对 $(i, j)$ 的个数。
## 题解
首先本题要求 $6$ 位数。首先我们考虑 $1$ 位数的情况：  
求 $A_i + A_j < 10$ 的 $(i,j)$ 的个数。  
考虑锁定一个特定的 $i$，有：$A_i + A_j < 10 \iff A_j < 10 - A_i \iff A_j \le 9 - A_i$。于是考虑维护桶数组的前缀和。由于条件的对称性，我们得到了如下算法：

> 算法目的：求 $A_i + A_j < 10$ 的 $(i,j)$ 的个数。  
> 算法实现：  
> 1. 首先计算 $A$ 的桶数组 $B_i = \sum\limits_{j=1}^n [A_j = i]$。 
> 2. 枚举每一个 $i \in [1, n]$，检查是否 $A_i \leq 4$，如果有，则 $l \gets l + 1$。
> 3. 计算 $B$ 的前缀和数组 $C_i = \sum\limits_{j=1}^i B_j$。
> 4. 枚举每一个 $i \in [1, n]$，$a \gets a + C_{9-A_i}$
> 5. 输出 $\dfrac{a-l}{2}$。

考虑更高位数。我们需要快速求出满足如下条件的 $i$ 的数目：
$$\forall j \in [1, 7], A_{i,j} \le T_j$$
，其中 $T$ 数组给定。  
我们发现，这实际上是求一个高维桶数组的高维前缀和。考虑如下算法：
> 1. 将数组 $P$ 转化为一个 $\mathbb N^D \to \mathbb N$ 的形式，方便下列运算
> 2. 枚举 $d \in [1, D]$，其中 $D$ 为总维度数。
> 3. 枚举 $\overrightarrow v \in [1, n]^D$。设 $\overrightarrow {t_i} \in \{0,1\}$ 且 $\overrightarrow {t_i} = 1 \iff i = D$，则 $P'(\overrightarrow v + \overrightarrow t) = P'(\overrightarrow v) + P(\overrightarrow v + \overrightarrow t)$。
> 4. $P \gets P'$。

考虑归纳地证明正确性：
- $D = 1$ 时，可以发现：$\overrightarrow t = [1]$。于是可以发现显然返回的 $P$ 是原来的 $P$ 的前缀和。
- $D > 1$ 时，设我们已经求出了前 $D-1$ 维度的前缀和，即
$$P'(x_1, \dots, x_D) = \sum_{y_1 = 1}^{x_1} \sum_{y_2 = 1}^{x_2} \dots \sum_{y_{D-1} = 1}^{x_{D_1}} P(y_1, y_2, \dots, y_{D - 1}, x_D)$$
，则算法会得到
$$P''(x_1, \dots, x_D) = \sum_{y_D = 1}^{x_D} \sum_{y_1 = 1}^{x_1} \sum_{y_2 = 1}^{x_2} \dots \sum_{y_{D-1} = 1}^{x_{D_1}} P(y_1, y_2, \dots, y_{D - 1}, y_D)$$
，由于所有求和符号都是有限求和，所以可以交换。证毕。

于是我们得解。

[AT提交记录（PyPy3）](https://atcoder.jp/contests/arc136/submissions/33407271)

---

## 作者：Liar_Dancer (赞：2)

超级暴力大王。

考虑暴力怎么做，我们从左往右加数，并查询与当前数相加合法的数字个数，设 $f_i$ 为与 $i$ 相加合法的数字个数，加数时暴力更新 $f$，复杂度 $O(nV)$。

考虑平衡复杂度，设 $g_{a,b}$ 为前三位为 $a$，后三位与 $b$ 相加合法的数字个数，加数时枚举后三位，查询时枚举前三位，复杂度 $O(n\sqrt{V})$，因为常数很小并且大部分时候跑不满，可以轻松跑进一秒以内。

[submission](https://atcoder.jp/contests/arc136/submissions/58604453)

---

## 作者：lfxxx (赞：2)

考虑对于一个数 $x$ 能与其相加满足不进位的数 $y$，所应该满足的条件应该是两个数每一位之和不超过 $9$，那么我们可以考虑对桶数组在 $10$ 进制下的高维前缀和数组处理出来，然后枚举 $x$ 计算合法的 $y$ 数量，减去 $x$ 与 $x$ 自己匹配的数量再除以 $2$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e6+114;
int a[maxn],pre[maxn],n;
int ans;
int f[6]={1,10,100,1000,10000,100000};
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		pre[a[i]]++;
		bool flag=true;
		for(int j=0;j<6;j++){
			if(a[i]/f[j]%10>=5) flag=false; 
		}
		if(flag==true) ans--;
	}
	for(int i=0;i<6;i++){
		for(int j=0;j<1000000;j++){
			if(j/f[i]%10!=0) pre[j]+=pre[j-f[i]];
		}
	}
	for(int i=1;i<=n;i++){
		ans+=pre[999999-a[i]];
	}
	cout<<ans/2<<'\n';
	return 0;
}
```

---

## 作者：BFSDFS123 (赞：1)

一个不需要太多脑子的做法。

我们称满足题目条件的两个数为“一对”。

定义 $p_{a_1,a_2,a_3,a_4,a_5,a_6}$ 为满足 $\forall 1\le i \le 6$，第 $i$ 位小于等于 $a_i$ 的数的个数。

如果两个数是“一对”（不妨设这两个数的每一位分别是 $p_i$ 与 $q_i$），那么有 $p_i+q_i \le 10$，即 $p_i + q_i < 9$，即 $p_i<9-q_i$。

依据以上结论，我们可以得到：对于一个六位分别为 $\{b_1,b_2,b_3,b_4,b_5,b_6\}$ 的数来说，能与它成为“一对”的数有 $p_{9-b_1,9-b_2,9-b_3,9-b_4,9-b_5,9-b_6}$ 个。

下一个问题是，如何计算前缀和？

对每位分别是 $\{c_1,c_2,c_3,c_4,c_5,c_6\}$ 的数，给 $p_{c_1,c_2,c_3,c_4,c_5,c_6}$ 加一。最后直接六次六层循环暴力。

> 如果需要求 $k$ 维前缀和，可通过 $k$ 次 $k$ 层循环求出。

```cpp
for(int i=1;i<=n;i++)
{
    int nums=0,x=Ar[i];
    vector<int> vc;
    while(nums<6)
    {
        nums++;
        vc.push_back(x%10);
        x/=10;
    }
    // cout<<vc[0]<<" "<<vc[1]<<" "<<vc[2]<<" "<<vc[3]<<" "<<vc[4]<<" "<<vc[5]<<endl;
    pre[vc[0]][vc[1]][vc[2]][vc[3]][vc[4]][vc[5]]++;
}
for(int a=0;a<=9;a++)
    for(int b=0;b<=9;b++)
        for(int c=0;c<=9;c++)
            for(int d=0;d<=9;d++)
                for(int e=0;e<=9;e++)
                    for(int f=0;f<=9;f++)
                        pre[a][b][c][d][e][f]+=(a==0?0:pre[a-1][b][c][d][e][f]);
for(int a=0;a<=9;a++)
    for(int b=0;b<=9;b++)
        for(int c=0;c<=9;c++)
            for(int d=0;d<=9;d++)
                for(int e=0;e<=9;e++)
                    for(int f=0;f<=9;f++)
                        pre[a][b][c][d][e][f]+=(b==0?0:pre[a][b-1][c][d][e][f]);
for(int a=0;a<=9;a++)
    for(int b=0;b<=9;b++)
        for(int c=0;c<=9;c++)
            for(int d=0;d<=9;d++)
                for(int e=0;e<=9;e++)
                    for(int f=0;f<=9;f++)
                        pre[a][b][c][d][e][f]+=(c==0?0:pre[a][b][c-1][d][e][f]);
for(int a=0;a<=9;a++)
    for(int b=0;b<=9;b++)
        for(int c=0;c<=9;c++)
            for(int d=0;d<=9;d++)
                for(int e=0;e<=9;e++)
                    for(int f=0;f<=9;f++)
                        pre[a][b][c][d][e][f]+=(d==0?0:pre[a][b][c][d-1][e][f]);
for(int a=0;a<=9;a++)
    for(int b=0;b<=9;b++)
        for(int c=0;c<=9;c++)
            for(int d=0;d<=9;d++)
                for(int e=0;e<=9;e++)
                    for(int f=0;f<=9;f++)
                        pre[a][b][c][d][e][f]+=(e==0?0:pre[a][b][c][d][e-1][f]);
for(int a=0;a<=9;a++)
    for(int b=0;b<=9;b++)
        for(int c=0;c<=9;c++)
            for(int d=0;d<=9;d++)
                for(int e=0;e<=9;e++)
                    for(int f=0;f<=9;f++)
                        pre[a][b][c][d][e][f]+=(f==0?0:pre[a][b][c][d][e][f-1]);
```

剩下的就非常好做了。[代码](https://atcoder.jp/contests/arc136/submissions/58647642)。

---

## 作者：CQ_Bob (赞：0)

题解摘自[做题记录](https://www.luogu.com.cn/article/3frkfgyz)。

## 分析

考虑对于 $a_i$，一个 $a_j$ 与其相加不会进位，当且仅当对于每个 $k$，都有：$a_{i,k}+a_{j,k} \le 9$。

那么我们对于每个 $i$ 就得到了 $\log_{10} a_i$ 个限制，第 $j$ 个限制 $b_j$ 表示与其相加不进位的数第 $j$ 位不能超过 $b_j$。那么做一个 $6$ 维的前缀和就行了。

这里对于一个 $k$ 维的前缀和，我们可以在 $O(kn^k)$ 内求解。一共跑 $k$ 次前缀和，第 $i$ 次前缀和有：$s_{a_1,a_2,\dots,a_k}\to s_{a_1,a_2,\dots,a_k}+s_{a_1,a_2,\dots,a_{i}-1,a_{i+1},\dots,a_k}$。

## 代码

```cpp
il void solve(){
	n=rd;int ans=0;
	for(re int i=1;i<=n;++i){
		int x=rd,k=0;
		for(re int j=1;j<=6;++j) b[i][++k]=9-(x%10),x/=10;
		++s[9-b[i][1]][9-b[i][2]][9-b[i][3]][9-b[i][4]][9-b[i][5]][9-b[i][6]];
	}
	for(re int a=0;a<=9;++a)
	for(re int b=0;b<=9;++b)
	for(re int c=0;c<=9;++c)
	for(re int d=0;d<=9;++d)
	for(re int e=0;e<=9;++e)
	for(re int f=0;f<=9;++f)
		if(a>0) s[a][b][c][d][e][f]+=s[a-1][b][c][d][e][f];
	for(re int a=0;a<=9;++a)
	for(re int b=0;b<=9;++b)
	for(re int c=0;c<=9;++c)
	for(re int d=0;d<=9;++d)
	for(re int e=0;e<=9;++e)
	for(re int f=0;f<=9;++f)
		if(b>0) s[a][b][c][d][e][f]+=s[a][b-1][c][d][e][f];
	for(re int a=0;a<=9;++a)
	for(re int b=0;b<=9;++b)
	for(re int c=0;c<=9;++c)
	for(re int d=0;d<=9;++d)
	for(re int e=0;e<=9;++e)
	for(re int f=0;f<=9;++f)
		if(c>0) s[a][b][c][d][e][f]+=s[a][b][c-1][d][e][f];
	for(re int a=0;a<=9;++a)
	for(re int b=0;b<=9;++b)
	for(re int c=0;c<=9;++c)
	for(re int d=0;d<=9;++d)
	for(re int e=0;e<=9;++e)
	for(re int f=0;f<=9;++f)
		if(d>0) s[a][b][c][d][e][f]+=s[a][b][c][d-1][e][f];
	for(re int a=0;a<=9;++a)
	for(re int b=0;b<=9;++b)
	for(re int c=0;c<=9;++c)
	for(re int d=0;d<=9;++d)
	for(re int e=0;e<=9;++e)
	for(re int f=0;f<=9;++f)
		if(e>0) s[a][b][c][d][e][f]+=s[a][b][c][d][e-1][f];
	for(re int a=0;a<=9;++a)
	for(re int b=0;b<=9;++b)
	for(re int c=0;c<=9;++c)
	for(re int d=0;d<=9;++d)
	for(re int e=0;e<=9;++e)
	for(re int f=0;f<=9;++f)
		if(f>0) s[a][b][c][d][e][f]+=s[a][b][c][d][e][f-1];	
	for(re int i=1;i<=n;++i){
		bool fl=1;
		for(re int j=1;j<=6;++j) if(((9-b[i][j])*2>9)) fl=0;
		if(fl) --ans;
		ans+=s[b[i][1]][b[i][2]][b[i][3]][b[i][4]][b[i][5]][b[i][6]]; 
	}
	printf("%lld\n",ans/2);
    return ;
}
```

---

