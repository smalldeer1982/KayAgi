# [ARC137D] Prefix XORs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc137/tasks/arc137_d

長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $，及び整数 $ M $ が与えられます．

各 $ k=1,2,\cdots,M $ について，以下の操作をちょうど $ k $ 回行ったあとの $ A_N $ の値を求めてください．

- すべての $ i $ ($ 1\ \leq\ i\ \leq\ N $) について，$ A_i $ の値を $ A_1\ \oplus\ A_2\ \oplus\ \cdots\ \oplus\ A_i $ で置き換える． この置き換えはすべての $ i $ に対して同時に行う．

ただしここで，$ \oplus $ はビット単位 $ \mathrm{XOR} $ 演算を表します．

  ビット単位 $ \mathrm{XOR} $ 演算とは  非負整数 $ A,\ B $ のビット単位 $ \mathrm{XOR} $ 、$ A\ \oplus\ B $ は、以下のように定義されます。

- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の整数 $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ のビット単位 $ \mathrm{XOR} $ は $ (\dots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \dots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ p_2,\ p_3,\ \dots\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^6 $
- $ 1\ \leq\ M\ \leq\ 10^6 $
- $ 0\ \leq\ A_i\ <\ 2^{30} $
- 入力される値はすべて整数

### Sample Explanation 1

操作の度に $ A $ は以下のように変化します． - 初期状態：$ A=(2,1,3) $ - $ 1 $ 回目の操作後：$ A=(2,3,0) $ - $ 2 $ 回目の操作後：$ A=(2,1,1) $

## 样例 #1

### 输入

```
3 2
2 1 3```

### 输出

```
0 1```

## 样例 #2

### 输入

```
10 12
721939838 337089195 171851101 1069204754 348295925 77134863 839878205 89360649 838712948 918594427```

### 输出

```
716176219 480674244 678890528 642764255 259091950 663009497 942498522 584528336 364872846 145822575 392655861 844652404```

# 题解

## 作者：缪凌锴_Mathew (赞：11)

对 $a$ 数组作 $k$ 次前缀和后得到的 $a_n=\sum_{i=0}\binom{k+i-1}{i}a_{n-i}$。

在贡献为异或情况下，若 $\binom{k+i-1}{i}\mod2=1$，则对答案贡献 $a_{n-i}$。

用 Lucas 定理可得：

$\binom{n}{m}\mod2=1$ 当且仅当 $n\operatorname{bitand}m=m$，即二进制下 $m$ 为 $n$ 的子集。

于是我们写出一份暴力：

```cpp
for(int i=1;i<=m;i++)
{
    for(int j=0;j<n;j++)
    {
        if(((i-1+j)&j)==j){
            ans[i]^=a[n-j];
        }
    }
}
```
我们把 $i$ 改为从 0 开始，就可以得到一个 ```((i+j)&j)==j```，即二进制下 $j$ 为 $i+j$ 的子集。

观察这个东西我们发现其实它相当于 ```!(i&j)```，即二进制下 $i$ 与 $j$ 的交集为空。

证明：

假设二进制下 $i$ 为 $j$ 的交集不为空，则这个交集的最低位在 $i+j$ 中将为 0，但 $j$ 此位为 1，假设不成立。

根据这个结论我们可以枚举 $i$ 的二进制的补集，暴力统计答案。

时间复杂度不会证，但跑极限数据不会超时。

```cpp
const int MAXN=1e6+10;
int n,m,all;//all为二进制下与n位数相同的,每一位都为1的数
int a[MAXN];
signed main(){
    scanf("%d%d",&n,&m);
    all=(1<<__lg(n)+1)-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int i=0;i<m;i++)
    {
        int ans=a[n];//a[n]不会被枚举到
        int p=~i&all;
        for(int j=p;j;j=(j-1)&p)//枚举补集
        {
            if(j<n){
                ans^=a[n-j];
            }
        }
        printf("%d ",ans);
    }
    return 0;
}
```
然而我们发现这个暴力太慢了，很多点都跑到了 $3s$ 以上。

发现这个暴力枚举补集其实可以 DP，直接枚举转移的二进制位。

时间复杂度 $O(n\log{n})$。

```cpp
const int MAXN=2e6+10;
int n,m,lg,all;
int dp[MAXN];//要开两倍数组
signed main(){
    scanf("%d%d",&n,&m);
    lg=__lg(n);
    all=(1<<lg+1)-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&dp[n-i]);
    }
    for(int i=0;i<=lg;i++)//枚举转移的位
    {
        for(int j=1;j<=all;j++)
        {
            if(j&(1<<i)){
                dp[j]^=dp[j^(1<<i)];
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        printf("%d ",dp[~i&all]);
    }
    return 0;
}
```

---

## 作者：SJH0203 (赞：9)

# [ARC137D] Prefix XORs 题解
## Solution
这道题是我们训练的弱化版。
对于异或之类的题，考虑每个节点对最终答案的贡献。

根据前缀和的知识，$a_i$ 在第 $k$ 时刻会对答案产生 $\dbinom{k+n-i}{n-i}$ 次贡献。

不妨将原序列逆序后从 0 开始排列，那么 $a_i$ 在第 $k$ 时刻产生的贡献即为 $\dbinom{k+i}{i}$。方便起见，下文所有 $a_i$ 都以这个顺序排列。由异或的性质可知，$a_i$ 对答案产生贡献当且仅当 $\dbinom{k+i}{i}\mod 2=1$。

考虑卢卡斯定理推论：$\dbinom{n}{m}\mod 2=1\Leftrightarrow n\And m=m$。

也就是说，如果 $a_i$ 对答案产生贡献，那么在二进制下， $i$ 是 $k+i$ 的一个子集，也就是 $i\cap k=\varnothing$。

那么只需要对于每一个 $k$，求出其补集的子集异或和即可，可以用高维前缀和处理。全集只需要取最小满足 $2^s>n$ 对应的 $2^s-1$，因为更高的二进制位不影响答案。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-') 
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9') 
	{
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	return x*f;
}
void write(int x)
{
	static int st[35],top=0;
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	do
	{
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top)
	{
		putchar(st[--top]+48);
	}
	putchar(' ');
}
int n,q,a[2000010],ans[2000010],que,mx=-1;
signed main()
{
	int U=(1<<20)-1; 
	n=read();
	q=read();
	for(int i=n-1;i>=0;i--)
	{
		ans[i]=read();
	}
	for(int i=0;(1<<i)<=U;i++)
	{
		for(int j=0;j<=U;j++)
		{
			if(j&(1<<i))
			{
				ans[j]^=ans[j^(1<<i)];
			}
		}
	}
	for(int que=1;que<=q;que++)
	{
		write(ans[~(que-1)&U]);
	}
 	return 0;
}

```
## 对于卢卡斯定理推论的证明
卢卡斯定理：对于质数 $p$，有$\dbinom{n}{m}\mod p=\dbinom{\lfloor n/p\rfloor}{\lfloor m/p \rfloor}\cdot\dbinom{n\mod p}{m\mod p}\mod p$。

当 $p=2$ 时，卢卡斯定理等同于将答案乘上 $\dbinom{n\And1}{m\And1}\mod 2$ 并且对 $n$ 与 $m$ 进行二进制右移操作。

若 $\dbinom{n}{m}\mod 2=1$，那么说明对于 $n$ 与 $m$ 在二进制下每一位 $n_i$ 与 $m_i$，都有 $\dbinom{n_i}{m_i}=1\Leftrightarrow n_i\ge m_i$。

即证。

---

## 作者：Sin_Watt (赞：6)

**注意：** 为了后文方便，我们将数组翻转，求后缀异或和。

设 $f_{i,j}$ 表示 $a_j$ 是否对 $i$ 阶后缀和有贡献，若值为 $1$，则有贡献。则有 $f_{i,j}=f_{i-1,j}\oplus f_{i,j-1}$，很好理解。

不妨看看哪些 $f_{i,j}$ 的值为 $1$。

![1.png](https://image.baidu.com/search/down?url=https://tvax4.sinaimg.cn/large/008D5oyhly1hnztipeq8oj30m90k3gq6.jpg)

图中大量的 $0$ 提示我们，$1$ 的个数不多，可以考虑枚举 $1$ 的位置。这些 $1$ 有什么规律呢？

![2.png](https://image.baidu.com/search/down?url=https://tvax2.sinaimg.cn/large/008D5oyhly1hnztjdhi38j30mc0jt0ys.jpg)

因为这是一道与异或有关的题，所以 $2$ 的幂次更容易涉及规律。注意到在前 $8\times 8$ 的空间中，左上角的三个边长为 $4$ 的正方形是一模一样的，而右下角剩下的那个正方形范围内一个 $1$ 都没有。同样，在前 $4\times 4$ 的空间中，左上角的三个边长为 $2$ 的正方形是一模一样的，而右下角剩下的那个正方形范围内一个 $1$ 都没有。

$16$ 呢？$32$ 呢？规律符合，~~蒟蒻我不会证，求dalao来证明~~。

美好的分形学指引我们走向递归。

```cpp
//原数组（翻转后的）
vector<int> a;
// 答案统计
vector<int> f; 

void dfs(int x, int y, int l)
{
	if (l == 1)
	{
		f[x] ^= a[y];
		return;
	}
	l >>= 1;
	dfs(x - l, y    , l);
	dfs(x    , y - l, l);
	dfs(x - l, y - l, l);
}
```

于是我们就轻松的拿下了 [TLE](https://www.luogu.com.cn/record/152025278) 的好成绩。

别急，先算一下时间复杂度。令 $l=\lceil\log_2\max(n, m)\rceil$，递归层数为 $l+
1$，当递归到最后一层时，就对应了一个 $1$。每往上一层就要 $\times 3$，所以总的 $1$ 的个数为 $3^l$。这里的 $3^l$ 比题目中询问的范围微微大一些，但无法避免。$l$ 最大能取到 $20$，而 $3^{20}=3,486,784,401$，高了点儿。

但是啊，如果我们让它少递归一层呢？

```cpp
void dfs(int x, int y, int l)
{
	if (l == 2)
	{
		//f[x] ^= a[y];
		f[x - 1] ^= a[y    ];
		f[x    ] ^= a[y - 1];
		f[x - 1] ^= a[y - 1];
		return;
	}
	l >>= 1;
	dfs(x - l, y    , l);
	dfs(x    , y - l, l);
	dfs(x - l, y - l, l);
}
```

~~这有什么区别？你是在逃避常数吗？~~

不，你可以理解为一次系统时钟可以进行 $4$ 次异或计算，然而 $1$ 次单独出现的异或运算却会单独占用 $1$ 个系统时钟。对比前后的第七个数据点，从 2355ms 降至 1067ms。出题人也好心的给了足足 $4$ 秒的时间，放过了这个 $O(3^{\lceil\log_2\max(n, m)\rceil-1})$。

---

关于前面的分形结构，给一个简单的感性理解。

![3.png](https://image.baidu.com/search/down?url=https://tvax2.sinaimg.cn/large/008D5oyhly1hnzv67mu3fj30if0hitd9.jpg)

就是说，如果第一个要点中的条件能产生第二个要点中的结构，那么就必然会形成一个更大的第二个要点中的结构。又存在

![4.png](https://image.baidu.com/search/down?url=https://tvax4.sinaimg.cn/large/008D5oyhly1hnzv6kqfpgj30eg0a1gm7.jpg)

所以是这样。

---
ps:

在优化后如果RE，考虑一下 $n = m = 1$ 时的情况。

~~完了完了，这么难看的书写~~

---

## 作者：ZillionX (赞：6)

# Description

给定 $n,m$ 和一个长度为 $n$ 的数组 $a$。

对于 $1 \le k \le m$，问对 $a$ 做 $k$ 次异或前缀和后 $a_n$ 的值。

$n,m \le 10^6,V < 2^{30}$，时限 4s。

# Solution

很套路的题目，就是两个套路拼在了一起，赛时一眼秒了。

约定下文中的加法为异或。

众所周知，对数组 $a$ 做 $k$ 次前缀和，前面的数对得到的 $a_n$ 的贡献可以写成

$$\Sigma^k a_n= \sum_{i=0} \binom{k-1+i}{i} a_{n-i}$$

本题中的加法为异或，于是上式中若 $\dbinom{k-1+i}{i} \bmod 2=1$，则 $a_{n-i}$ 对最终答案有贡献。

如何判断一个组合数是否为奇数也是个经典套路，对 $\dbinom{n}{m}$ 在 $\bmod 2$ 意义下施以 Lucas 定理，容易发现对于一个二进制位，只有 $n,m$ 在此位同时为 $0/1$，或 $n$ 在此位为 $1$ 而 $m$ 在此位为 $0$，$\dbinom{n}{m}$ 才为奇数。即在二进制表示中 $m$ 为 $n$ 的子集。

对于本题，若二进制表示中 $i$ 为 $k-1+i$ 的子集，则 $a_{n-i}$ 对答案有贡献。观察何时满足此条件，容易发现此时必然有 $k-1 \subseteq \complement_U i$。因此对 $a$ 做一个简单的 FWT 即可。

时间复杂度 $\mathcal O(n \log n)$。

# Code

```cpp
const int N=1e6+5;
int n,m,w=1,a[N],f[N];
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	while (w<n) w<<=1;
	for (int i=1;i<=n;i++) f[w-n+i-1]=a[i];
	for (int i=2,j=1;i<=w;i<<=1,j<<=1)
		for (int k=0;k<w;k+=i)
			for (int l=0;l<j;l++)
				f[k+l]^=f[j+k+l];
	for (int i=1;i<=m;i++) printf("%d ",f[(i-1)%w]);
	return 0;
}
```


---

## 作者：pengyule (赞：3)

首先显然每一位独立，问题变成 01 串的问题。这时如果没有思路，可以考虑找规律，然后发现 $k$ 每 $2^{\lceil\log_2 n\rceil}$ 答案循环一次。而通过打表的一些信息我们又自然而然地想到背后是什么让 01 序列发生如此变化，直觉告诉我们肯定跟 FWT 有些关系。如果运气很好的话，确可找到规律，就是把下标为 $[1,n]$ 的原序列平移到下标为 $[2^{\lceil\log_2 n\rceil}-n+1,2^{\lceil\log_2 n\rceil}]$ 处，然后对 $[1,2^{\lceil\log_2 n\rceil}]$ 做一次 FWT。我运气没这么好，还差那么一点。

另一个直接的思路是看到多次前缀（异或）和便使用路径计数优化 DP（UER#11 切割冰片使用了此方法），那么 $a^0_i$ 对 $a^k_n$ 的贡献就是 ${n-i+k-1\choose n-i}a_i^0$。  
乍一看这个好像跟异或拉不上关系，实际上顺着想下去会发现由于异或是不进位加法，所以实际上贡献就是 $\left({n-i+k-1\choose n-i}\bmod 2\right)a_i^0$，前者为 $1$ 的充要条件：应用 Lucas 定理得到，$\forall b_1$，$n-i+k-1$ 的第 $b_1$ 位 $\ge n-i$ 的第 $b_1$ 位，也就是 $n-i\subseteq n-i+k-1$。  

![](https://cdn.luogu.com.cn/upload/image_hosting/xh9ugpe2.png)

结合图示可知，$(n-i+k-1)-(n-i)$ 与原来 $n-i$ 没有交集，即 $k-1$ 与 $n-i$ 没有交集，$k-1\subseteq \complement_U (n-i)$，那么 $(k-1)\bmod n\subseteq \complement_U(n-i)\bmod n$，在 $[0,n]$ 内求 FWT 即可（$+$ 改为 $\oplus$）。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2000005],ans[2000005];
int main(){
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	reverse(a+1,a+n+1);
	int nn=ceil(log2(n));n=1<<nn;
	reverse(a+1,a+n+1);
	for(int w=1;w<n;w<<=1)
		for(int i=1;i<=n;i+=w<<1)
			for(int j=i;j<(i+w);j++)
				a[j]^=a[j+w];
	for(int i=0;i<m;i++)cout<<a[i%n+1]<<' ';
}
```

---

## 作者：Graphcity (赞：2)

考虑大力生成函数。由于位运算中每一位分别独立，所以按位考虑，假设现在已经考虑到了某一位。设 $a_i$ 为原序列第 $i$ 个数 $A_i$ 在这一位的值，给序列 $\{a_i\}$ 构建生成函数：

$$
F(x)=\sum_{i=0}^na_ix^i\ (a_i\in \{0,1\})
$$

做 $k$ 次操作就相当于 $k$ 次前缀和。那么答案就是

$$
\begin{aligned}
[x^n](\frac{1}{1-x})^kF(x)&=[x^n](1-x)^{-k}F(x)\\
&=[x^n]F(x)\sum_{i\ge 0}\binom{-k}{i}(-1)^ix^i\\
&= [x^n]F(x)\sum_{i\ge 0}\binom{k+i-1}{i}x^i\\
&=\sum_{i=0}^n\binom{k+i-1}{i}a_{n-i}
\end{aligned}
$$

将 $a$ 数组翻转可得

$$
\sum_{i=0}^n\binom{k+i-1}{i}a^R_i
$$

事实上所有的运算均在 $\bmod 2$ 意义下进行。根据 Kummer 定理，组合数 $\dbinom{n+m}{n}$ 中因子 $2$ 的出现次数等于 $n+m$ 在二进制下的进位次数。

所以能够造成贡献当且仅当不存在因子 $2$，也就是不进位。更进一步地，$i\operatorname{bitand}k-1=0$。我们便可以将式子写成这样：

$$
ans_k=\bigoplus_{i=0,i\operatorname{bitand} k-1=0}^na_i^{R}
$$

由于每一位之间独立，所以 $a_i$ 就跟原序列的 $A_i$ 等价。
这是个经典的 FWT 形式。将 FWT 中的加法运算改成异或运算即可。时间复杂度 $O(n\log n)$。（设 $n$ 与值域同阶）

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6,lim=(1<<20);

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,val[Maxn+5];
int sum[lim+5];

inline void And()
{
    for(int i=2,mid=1;i<=lim;i<<=1,mid<<=1)
        for(int j=0;j<lim;j+=i)
            for(int k=0;k<mid;++k)
                sum[j+k]^=sum[j+k+mid];
}

int main()
{
    n=read(),m=read();
    For(i,1,n) val[i]=read();
    reverse(val,val+n+1);
    For(i,0,n) sum[i^(lim-1)]^=val[i];
    And();
    For(i,0,m-1) printf("%d ",sum[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：STARSczy (赞：1)

这道题可以把每个 $A_i$ 的贡献拆开看。

首先，假设这道题的 $n$ 和 $m$ 一样，且为 $2$ 的整数次幂。如果不是，可以把 $n$ 和 $m$ 向大补到整数次幂，然后再 $A$ 的 **前面** 补上多余的 $0$，且不输出多余的 $m$ 是不影响答案的。注意一定是前面补，vp 赛时就一直因此没对。

如果只看 $A_1$ 的贡献，那么我们可以把其他的 $A_i$ 都设为 $0$，则这个序列做前缀和的结果只可能为 $A_i$ 和 $0$。于是我们把 $A_i$ 看作 $1$，则整个序列为初始为 $1,0,0,0,\dots$。设 $n$ 为 $8$ 时，做 $k$ 次异或前缀和结果如下表。

|下标|1|2|3|4|5|6|7|8|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$0$ 次|$\color{red}1$|0|0|0|0|0|0|0|
|$1$ 次|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|
|$2$ 次|$\color{red}1$|0|$\color{red}1$|0|$\color{red}1$|0|$\color{red}1$|0|
|$3$ 次|$\color{red}1$|$\color{red}1$|0|0|$\color{red}1$|$\color{red}1$|0|0|
|$4$ 次|$\color{red}1$|0|0|0|$\color{red}1$|0|0|0|
|$5$ 次|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|0|0|0|0|
|$6$ 次|$\color{red}1$|0|$\color{red}1$|0|0|0|0|0|
|$7$ 次|$\color{red}1$|$\color{red}1$|0|0|0|0|0|0|
|$8$ 次|$\color{red}1$|0|0|0|0|0|0|0|

后面就是循环了，省略。

发现这是一个模 $2$ 意义下的杨辉三角。

然后 $A_i$ 的贡献就是从第 $i$ 列开始往右的这个 $(n-i+1)\times n$ 矩阵。

第 $i$ 次，下标为 $j$ 对于 $n$ 的是否有贡献的矩阵就是上面这个矩阵上下翻转，即：

|下标|1|2|3|4|5|6|7|8|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$0$ 次|$\color{red}1$|0|0|0|0|0|0|0|
|$1$ 次|$\color{red}1$|$\color{red}1$|0|0|0|0|0|0|
|$2$ 次|$\color{red}1$|0|$\color{red}1$|0|0|0|0|0|
|$3$ 次|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|0|0|0|0|
|$4$ 次|$\color{red}1$|0|0|0|$\color{red}1$|0|0|0|
|$5$ 次|$\color{red}1$|$\color{red}1$|0|0|$\color{red}1$|$\color{red}1$|0|0|
|$6$ 次|$\color{red}1$|0|$\color{red}1$|0|$\color{red}1$|0|$\color{red}1$|0|
|$7$ 次|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|$\color{red}1$|
|$8$ 次|$\color{red}1$|0|0|0|0|0|0|0|

所以我们就可以直接统计了。

但是我们发现，就这样统计还是 $n^2$ 级别的。

然后注意到这个图形有一个性质，就是有三个相同的部分，就是左上 $\frac{n}{2}\times \frac{n}{2}$，右上 $\frac{n}{2}\times \frac{n}{2}$，左下 $\frac{n}{2}\times \frac{n}{2}$ 部分时相同的。

于是，有题解就通过这个性质使用 $3^{\log_2 n}$ 的时间复杂度卡过了。

但是，明显这样不优雅。

然后又因为左上 $\frac{n}{2}\times \frac{n}{2}$ 的矩阵和左下 $\frac{n}{2}\times \frac{n}{2}$ 的矩阵一样，所以我们没必要处理左下 $\frac{n}{2}\times \frac{n}{2}$ 的矩阵。所以可以使用分治的做法，预处理出左上和右下，再把左上的贡献加到左下即可。时间复杂度 $\Theta(n \log n)$。

于是，我们愉快地做完这道题了。

AC 代码：
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define per(i,r,l) for(int i=(r),i##end=(l);i>=i##end;--i)
#define int long long
#define double long double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rbtree(way) tree<way,null_type,less<way>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
const int maxn=4e6+10,maxm=1e6+10,mod=998244353,inf=INT_MAX;
inline int ksm(int x,int k,int mod=mod){
	int ans=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1) ans=ans*x%mod;
	return ans;
}

int n,m,limit,a[maxn],ans[maxn];
void solve(int l,int r){
	if(l==r){
		ans[l]^=a[l];
		return;
	}
	int mid=l+r>>1;
	solve(l,mid),solve(mid+1,r);
	rep(i,1,mid-l+1) ans[l+i-1]^=ans[mid+i];
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m,limit=1;
	rep(i,1,n) cin>>a[i];
	for(;limit<max(n,m);limit<<=1);
	per(i,limit,limit-n+1) a[i]=a[i+n-limit];
	rep(i,1,limit-n) a[i]=0;
	solve(1,limit);
	rep(i,1,m) cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：happy_zero (赞：0)

前缀异或其实不是那么直观，不妨尝试前缀和（异或不就是前缀和的奇偶性吗）。

结论：$i$ 贡献到 $n$ 贡献了多少次？直观理解：$i$ 可以经由某些点到达 $n$，可以画出如下一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/kqreqymh.png?x-oss-process=image/resize,m_lfit,h_510,w_675)

第 $x$ 行最右边的 $y$ 代表 $i$ 第 $x$ 步停留在 $y$，那么一条从 $(1,1)\rightarrow (k,n-i+1)$ 的路径（比如图中橙色的路径）便代表了一种 $i\rightarrow n$ 的贡献方案。

令 $i'=n-i$，根据数学知识：$(1,1)\rightarrow(n-i+1)$ 方案数即 $i$ 贡献到 $n$ 次数：$\dbinom{i'+k-1}{i'}$。

转变成异或，根据 Lucas 定理：$\dbinom{i'+k-1}{i'}\bmod 2=1$ 当且仅当 $(i'+k-1)\operatorname{and} i'=i'$。

而这个又可以转化为：$(k-1)\operatorname{and} i'=0$，做高维前缀和即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5;
int f[N];
int main() {
	int n, m; cin >> n >> m; int l = __lg(n);
	for (int i = 1, x; i <= n; i++)
		cin >> x, f[n - i] = x;
	int all = (1 << (l + 1)) - 1;
	for (int i = 0; i <= l; i++) 
		for (int j = 0; j <= all; j++)
			if (j & (1 << i)) f[j] ^= f[j ^ (1 << i)];
	for (int i = 0; i < m; i++)
		cout << f[~i & all] << ' ';
	return 0;
}
```

---

## 作者：win114514 (赞：0)

### 思路

考虑前缀和时每一位的贡献是什么。

对于一个生成函数 $F(x)$。

对其作 $k$ 次前缀和，函数会变成：

$$
(\frac{1}{1-x})^kF(x)
$$

那么其 $n$ 次项系数：

$$
\begin{align}
&=[x^n](\frac{1}{1-x})^kF(x)\nonumber\\
&=[x^n]F(x)(1-x)^{-k}\nonumber\\
&=\sum_{i=0}\binom{-k}{i}(-1)^i[x^{n-i}]F(x)\nonumber\\
&=\sum_{i=0}\binom{k+i-1}{i}[x^{n-i}]F(x)\nonumber
\end{align}
$$

这样就求出了系数为 $\binom{k+i-1}{i}$。

注意到以上是在二进制每一位考虑。

所以只有 $\binom{k+i-1}{i} \bmod 2=1$ 时才有贡献。

依据 Lucas 定理，当 $i$ 为 $k+i-1$ 子集时，答案为一。

所以最终答案为：

$$
ans_i=\bigoplus_{j=0}[j\in(i+j-1)]a_{n-j}
$$

我们将 $i$ 集体减一。

$$
\begin{align}
ans_i&=\bigoplus_{j=0}[j\in(i+j)]a_{n-j}\nonumber\\
&=\bigoplus_{j=0}[j\cap i=\empty]a_{n-j}\nonumber\\
\end{align}
$$

容易发现是一个高维前缀和，直接做即可。

时间复杂度：$O(n\log n )$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[1 << 20];
int b[1 << 20];

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  int k = 1 << 20;
  for (int i = 0; i < k; i++)
    if (i < n) b[i] = a[n - i];
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < k; j++)
      if (j & (1 << i)) b[j] ^= b[j ^ (1 << i)];
  for (int i = 0; i < m; i++)
    cout << b[i ^ (k - 1)] << " \n"[i == m - 1];
}
```

---

