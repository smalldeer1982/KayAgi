# Magic Formulas

## 题目描述

People in the Tomskaya region like magic formulas very much. You can see some of them below.

Imagine you are given a sequence of positive integer numbers $ p_{1} $ , $ p_{2} $ , ..., $ p_{n} $ . Lets write down some magic formulas:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/bc5cfed2fc930604306d4050665204f7083b9e3e.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/7e1ac84d84d4d0097a495218327d72c2379cae8d.png)Here, "mod" means the operation of taking the residue after dividing.

The expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF424C/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying the bitwise $ xor $ (excluding "OR") operation to integers $ x $ and $ y $ . The given operation exists in all modern programming languages. For example, in languages C++ and Java it is represented by "^", in Pascal — by "xor".

People in the Tomskaya region like magic formulas very much, but they don't like to calculate them! Therefore you are given the sequence $ p $ , calculate the value of $ Q $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
3
```

# 题解

## 作者：ZolaWatle (赞：4)

## CF424C 题解

校内模拟赛的 $\text{T1}$，考试时A了，觉得这是道好题，于是写题解再次梳理了自己的解题思路。

这里介主要绍一种复杂度为 $ O(n) $ 的做法。

### 50pts

直接暴力，按照题意模拟即可。

当然可以维护一个前缀异或稍稍地优化一下，然而并没有什么用。

### 100pts

我们知道，异或运算同样满足类似于加法运算中的**交换律**和**结合律**。

定义 $ \sum\limits_{i=1}^{n}{a_i} $ 表示 $ a_1 \oplus a_2 \oplus ... \oplus a_n $ 的值。其中 $ \oplus $ 符号表示异或运算。

对于最终的答案 $ Q $，我们考虑：

$$ Q = \sum\limits_{i=1}^{n}{q_i} $$

$$ Q = \sum\limits_{i=1}^{n}{p_i} \oplus \sum\limits_{i=1}^{n}{\sum\limits_{j=1}^{n}{i\%j}} $$

对于本式子的前半部分，可以直接在输入的过程中求出。另外，我们注意到异或运算的一个性质：$ 0 \oplus k = k, k\in N^+ $。因而，对于我们要求的答案 $ Q $，我们将它的初值设为 $ 0 $。

对于后半部分，显然，暴力求解的时间复杂度是难以接受的，我们考虑优化。

为了方便，我们令 $ S_1 = \sum\limits_{i=1}^{n}{p_i} $，$ S_2 = \sum\limits_{i=1}^{n}{\sum\limits_{j=1}^{n}{i\%j}} $。显然，$ Q = S_1 \oplus S_2 $。

为了优化，我们考虑对式子 $ S_2 $ 进行变形。由异或运算的交换律和结合律可以得到：

$$ S_2 = \sum\limits_{j=1}^{n}{\sum\limits_{i=1}^{n}{i\%j}} $$

看起来没有什么区别。下面我解释一下：

我们将式子稍稍变形，就相当于先前我们对于每一个 $ i $，将其模每一个 $ j $ 的值的异或先求出，再把每个 $ i\%j $ 的结果异或起来得到答案。我们现在的思路简单来说就是换了一个方向看问题，先对于每一个 $ j $ 求出其异或 $ i\%j $ 的结果异或起来，再把每个 $ j $ 的结果异或起来得到答案。

这样说来说去感觉很绕，我们可以尝试着去举一个例子。不妨以样例 $n=3$ 时为例：

按原来的思路：

$$ S_2 = (1\%1)\oplus(1\%2)\oplus(1\%3)\oplus(2\%1)\oplus(2\%2)\oplus(2\%3)\oplus(3\%1)\oplus(3\%2)\oplus(3\%3) $$

现在，根据交换律，可以得到：

$$ S_2 = (1\%1)\oplus(2\%1)\oplus(3\%1)\oplus(1\%2)\oplus(2\%2)\oplus(3\%2)\oplus(1\%3)\oplus(2\%3)\oplus(3\%3) $$

这样做有什么好处呢？我们这样考虑：

我们定义数组 $ b_i = \sum\limits_{j=1}^{i}{j} $，即在暴力做法中提到过的**前缀异或**。

对于每一个 $ j $，形如 $ i\%j $ 这样的值必定出现 $n$ 次，其中 $ i\in [1,n] $ 且 $ i\in N^+ $。我们将这 $ n $ 次划分为如下两部分：

- 有 $ \lfloor \dfrac{n}{j} \rfloor $ 组的 $ b_j $ 互相异或。

- 对于剩下的则有 $ \sum_{i=1}^{n - j\cdot \lfloor \frac{n}{j} \rfloor - 1}{i} $。实际上，也就是 $ b_{n - j\cdot \lfloor \frac{n}{j} \rfloor - 1} $ 的值。为什么要减去一呢？容易想到，任何正整数对 $1$ 取模的值为 $0$，因而实际上这个值是从 $0$ 异或到 $ {n - j\cdot \lfloor \frac{n}{j} \rfloor - 1} $，而不是从 $1$ 异或到 $ {n - j\cdot \lfloor \frac{n}{j} \rfloor} $。但共同点是，都有 $ {n - j\cdot \lfloor \frac{n}{j} \rfloor} $ 个数参与了异或运算。

- 两者相异或即为这个 $ j $ 的答案。

对于第二种情况，由于已经处理好了前缀异或，因而容易求得。对于第一种情况，我们考虑异或运算的另一种性质：$ x \oplus x = 0 $。能够知道，如果组数 $ \lfloor \frac{n}{j} \rfloor $ 为偶数，则其值为 $0$，为奇数则是 $ b_j $。

至此，我们求出了 $ S_1, S_2 $。答案 $Q$ 则为两者的异或，我们便求出了答案。

再此给出一份完整代码作为参考：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN=1e6+1;
int n,ans,a[MAXN],b[MAXN];

inline int read()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
	return x*f;
}

int main()
{
	n=read();
	
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		b[i]=b[i-1]^i;
		ans=ans^a[i];
	}
	
	for(int i=2;i<=n;i++)
	{
		int num=n/i;
		if(num&1) ans^=b[i-1];
		if(num*i<n)
		{
			int k=n-num*i;
			ans^=b[k];
		}
	}
	
	printf("%d",ans);
	return 0;
}
```

------------

感谢阅读，有什么不理解的可以私信问我氩~

萌新的公式有点丑，还请多多包涵！（鞠躬）

---

## 作者：一叶知秋。 (赞：2)

来个 $O(n \ln n)$ 的。。。（貌似跑的飞快？）

考虑对于一个余数，能算出来它的首先模数比它大，设

$a=r+b \times mod$

所以我们可以找到大于余数的模数的倍数（ $0$ 也算），且保证该倍数小于等于 $n-r$ （不然和就大于 $n$ 了）

然后就倒着枚举，慢慢加就是了，时间复杂度为 $O( \sum\limits_{i=1}^{n} \frac{n}{i})=O(n \ln n)$

具体实现看代码：

```cpp
#include<cstdio>
#include<cctype>

#define maxn 1001001

template<typename T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

int n,s,ans,d[maxn];

int main(){
	n=read<int>();
	for(int i=n;i>=1;i--){//反着枚举
		s^=d[n-i];//加上当前的n-i
		ans^=i*s;
		for(int j=0;j<=n;j+=i)
			d[j]^=1,(s^=(j<=n-i));//这里还要统计一下小于等于n-i的j的个数
	}
	for(int i=1;i<=n;i++)
		ans^=read<int>();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：osfly (赞：1)

简单题。CF 评分才 *1600。

可以直接先把 $Q$ 拆成两部分。

$$
\begin{aligned}
\large a&=\oplus^n_{i=1}p_i\\
\large b&=\oplus^n_{i=1}\oplus^n_{j=1}\ \ \ (i\bmod j)\\
\large Q&=a\oplus b
\end{aligned}
$$

$a$ 很好算，我们看一下 $b$ 具体要怎么算。

把 $b$ 所有项写出来：

$$
\begin{aligned}
b=&(1\bmod 1)\oplus(1\bmod 2)\oplus...(1\bmod n)\oplus\\
  &(2\bmod 1)\oplus(2\bmod 2)\oplus...(2\bmod n)\oplus\\
  &...\\
  &(n\bmod 1)\oplus(n\bmod 2)\oplus...(n\bmod n)\\
 =&(1\bmod 1)\oplus(2\bmod 1)\oplus...(n\bmod 1)\oplus\\
  &(1\bmod 2)\oplus(2\bmod 2)\oplus...(n\bmod 2)\oplus\\
  &...\\
  &(1\bmod n)\oplus(2\bmod n)\oplus...(n\bmod n)\\
\end{aligned}
$$

发现 $i$ 和 $j$ 的位置互换并不会有什么影响。

所以我们有：

$$
\large b=\oplus^n_{i=1}\oplus^n_{j=1}\ \ \ (i\bmod j)=\oplus^n_{i=1}\oplus^n_{j=1}\ \ \ (j\bmod i)
$$

记 $\large pre_i=\oplus^i_{s=1}s$，根据异或的性质，我们有 $a\oplus a=0$。

那么

$$
\oplus^n_{j=1}\ \ \ (j\bmod i)=
\left\{
\begin{aligned}
pre_{n\bmod i}\ \ \ \ \ \ \ \lfloor \frac{n}{i}\rfloor\bmod 2=0\\
pre_{n\bmod i}\oplus pre_i\ \ \ \ \ \ \ \lfloor \frac{n}{i}\rfloor\mod2=1
\end{aligned}
\right.
$$

则

$$
\begin{aligned}
\large b&=\oplus^n_{i=1}\oplus^n_{j=1}\ \ \ (j\bmod i)\\
\large  &=pre_{n\bmod i}\oplus^n_{i=1\&\lfloor \frac{n}{i}\rfloor\bmod 2=1}\ pre_i
\end{aligned}
$$

那么代码就很好写了。

```cpp
#include<cstdio>
#define ll long long
const int N=1e6+10;
int n;
ll pre[N],ans;
ll p;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&p),ans^=p,pre[i]=pre[i-1]^i;
	for(int i=1;i<=n;i++)
	{
		if((n/i)&1) ans^=pre[i-1];
		ans^=pre[n%i];
	}
	printf("%lld",ans);
	return 0;
}
```

时间复杂度 $O(n)$。

---

## 作者：Perfonster (赞：1)

预处理$1...n$的异或前缀和$sum_i$。
```cpp
容易发现：
(1%1)^(1%2)^...^(1%n)^
(2%1)^(2%2)^...^(2%n)^
...
(n%1)^(n%2)^...^(n%n)=

(1%1)^(2%1)^...^(n%1)^
(1%2)^(2%2)^...^(n%2)^
...
(1%n)^(2%n)^...^(n%n)^

```
上方代码等式右边的值，第$i$行从$1\mod i$开始每$i$项异或和为$sum_i$，原因是$j \mod i=(j+i)\mod i$。

第$i$行有$\frac{n}{i}$个$sum_{i-1}$的异或值（为什么不是$sum_i$呢？因为对于第$i$行的$i\mod i$，其值为$0$，异或上0不用考虑），则若$\frac{n}{i} \mod 2=1$，这些异或值总和为$sum_i$，否则为$0$。

第$i$行除此之外，应该异或上$sum_{n\mod i}$。因此，第i行的值为
```
((n/i)%2==1?sum[i]:0)^sum[n%i]
```
对每一行进行这一个操作，再异或上每一个$p_i$，即得答案。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define maxn 1000009
using namespace std;
int n,a[maxn],sum[maxn],q;
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	return x;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		q^=a[i];
		sum[i]=sum[i-1]^i;
	}
   //此时q即为p[1..n]的异或和
	for(int i=1;i<=n;i++){
		int t=n%i,p=n/i;
		if(p%2){
			q^=sum[i-1];
		}
		q^=sum[t];
	}
	printf("%d\n",q);
	return 0;
}
```


---

## 作者：wimg6_ (赞：0)

## CF424C 题解

记 $s_i=\sum\limits_{i=1}^ni$。

**前置知识**

模数的性质：

对于一个模数 $i$，$[1+ki,i+ki](k\in \mathbb{N})$ 是其最小的完整周期。

模数的常用结论：

$$\sum\limits_{j=1}^n\sum\limits_{i=1}^n{i\ \mathrm{mod}\ j}=\sum\limits_{j=1}^n(\left\lfloor\dfrac{n}{j}\right\rfloor s_{j-1}+s_{n\ \mathrm{mod}\ j})$$

证明：

由模数的性质的第一条，可以知道对于模数 $j$，在 $1$ 到 $n$ 内恰有 $\left\lfloor\dfrac{n}{j}\right\rfloor$ 个最小完整周期，且对于每个最小完整周期，其取模后计算结果为 $s_{j-1}$。而 $s_{n\ \mathrm{mod}\ j}$ 即为不组成完整周期的部分取模后的值。

异或的性质：

第一条 异或满足交换律和结合律。

第二条 $x\oplus x=0$。

**解法**

由于加法与异或均满足交换律和结合律，不妨从加法入手。

假设将所有异或符号均替换为加号，则如下：

$$Q$$

$$=\sum\limits_{i=1}^nq_i$$

$$=\sum\limits_{i=1}^n(p_i+\sum\limits_{j=1}^ni\ \mathrm{mod}\ j)$$

$$=\sum\limits_{i=1}^np_i+\sum\limits_{j=1}^n\sum\limits_{i=1}^ni\ \mathrm{mod}\ j$$

$$=\sum\limits_{i=1}^np_i+\sum\limits_{j=1}^n(\left\lfloor\dfrac{n}{j}\right\rfloor s_{j-1}+s_{n\ \mathrm{mod}\ j})$$

接下来将所有加号替换为异或符号，同时注意异或的第二条性质。

也就是说若 $j$ 是奇数，可以将 $\left\lfloor\dfrac{n}{j}\right\rfloor s_{j-1}\oplus s_{n\ \mathrm{mod}\ j}$ 替换为 $s_{j-1}\oplus s_{n\ \mathrm{mod}\ j}$；若 $j$ 是偶数，则可以将 $\left\lfloor\dfrac{n}{j}\right\rfloor s_{j-1}\oplus s_{n\ \mathrm{mod}\ j}$ 替换为  $s_{n\ \mathrm{mod}\ j}$。

那么此时的 $Q$ 就可以通过 $O(n)$ 的时间复杂度求出来。

```
#include<bits/stdc++.h>
using namespace std;
long long n,ans,s[100010],p[100010];
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&p[i]);
	s[1]=1,ans=p[1];
	for(long long i=2;i<=n;i++)
		s[i]=s[i-1] xor i;
	for(long long i=2;i<=n;i++)
		ans=ans xor p[i];
	for(long long i=1;i<=n;i++)
		if((n/i)&1) ans=ans xor s[n%i] xor s[i-1];
		else ans=ans xor s[n%i];
	return !printf("%lld",ans);
}
```


---

## 作者：cppcppcpp3 (赞：0)

### Problem

给出 $n$ 个数 $a_1$，$a_2$，$\cdots$，$a_n$。
令 $b_i=a_i \oplus (i \bmod 1) \oplus \cdots \oplus (i \bmod n)$，求 $Q=b_1 \oplus b_2 \oplus \cdots \oplus b_n$。


------------


### Solution

因为 $1 \le n \le 10^6$，暴力过不去，尝试简化式子。

由于异或运算满足**交换律**和**结合律**，令 $c_i=(1 \bmod i) \oplus \cdots \oplus (n \bmod i) $（注意并非 $a_i \oplus b_i$），则 $Q=(a_1 \oplus \cdots \oplus a_n) \oplus (c_1 \oplus \cdots \oplus c_n)$。其中前面括号里的可以直接算出。

考虑求 $c_i$。

我们发现，因为 $[1+ki,i+ki] (k \in \mathbb{N})$ 为对 $i$ 取模的一个周期，所以 $c_i$ 可以拆成两部分异或起来：

- $(1 \bmod i) \oplus \cdots \oplus (i \times \lfloor \frac{n}{i} \rfloor \bmod i) $，恰好含 $\lfloor \frac{n}{i} \rfloor$ 个最小取模周期。此时分两种情况：如果 $\lfloor \frac{n}{i} \rfloor$ 为偶数，则该式子等于 $0$；否则等于 $1 \oplus \cdots \oplus (i-1)$。

- $[(i \times \lfloor \frac{n}{i} \rfloor+1) \bmod i]\oplus \cdots \oplus (n \bmod i)$，即 $1 \oplus 2 \oplus \cdots \oplus (n \bmod i)$。

预处理**前缀异或**即可。


------------


### Code
```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=1e6+5;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return x*f;
}

int n,ans,a[N],orz[N];

main(){
	n=wrd();
	for(int i=1;i<=n;++i) a[i]=wrd(),ans^=a[i];
	for(int i=1;i<=n;++i) orz[i]=orz[i-1]^i; //前缀异或。
	
	for(int i=2;i<=n;++i){
		if((n/i)&1) ans^=orz[i-1]; //见上述求c[i]。
		ans^=orz[n%i];
	}
	return printf("%lld",ans),0;
}
```

---

## 作者：_HMZ_ (赞：0)

## 解题思路：

这题是跟同学比手速打着玩的，不过还是有一些思维含量的。

首先我们知道异或满足交换律，所以可以提前将 $p$ 拿出来，只留下下标。

再看下标的取模，我们这时只考虑 $a \bmod b$ 中的 $b$。

很容易发现，$1$ 到 $n$ 对 $b$ 取模一定有周期性。

比如对 $5$ 取模，一定是 $0$ 到 $4$ 循环。

此时异或还有一个性质，两个相同的值异或起来得 $0$。

那么我们就可以暴力枚举 $b$，然后求出周期循环几次，再差分。

若一个值异或的次数为偶数则不用管，否则加进答案。

## AC代码：

```cpp
#include<iostream>
using namespace std;
int n,val[1000005],nowsum,qf[1000005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>val[i];//别忘了异或上原数组。
        nowsum^=val[i];
    }
    for(int i=1;i<=n;i++)
    {
        int t1=n/i,t2=n%i;//t1 代表周期循环次数,t2 代表后面的余数。
        qf[0]+=t1,qf[i]-=t1;
        qf[0]++,qf[t2+1]--;//典型差分。
    }
    int now=0;
    for(int i=0;i<=n;i++)
    {
        now+=qf[i];
        if(now%2==1)
            nowsum^=i;
    }
    cout<<nowsum;
    return 0;
}
```


---

## 作者：_Clown_ (赞：0)

这道题目我觉得还是比较容易的。

首先，我们来看一下思路：

因为**异或满足交换律，**

所以我们可以开始推导。

~~原式~~=$P_1$^$P_2$^$P_3$$\ldots$^$P_n$^$(1$~$n$分别^$1$~$n)$

~~略去过程$\mathcal{QED}$。~~

不过这也还是比较明了的了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int Total;
int Array[1000001];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	register int i;
	register int Ans;
	Ans=0;
	cin>>Total;
	register int X;
	for(i=1;i<=Total;i++)
	{
		cin>>X;
		Ans^=X;
	}
	for(i=1;i<=Total;i++)
	{
		Array[i]=Array[i-1]^i;
	}
	for(i=1;i<=Total;i++)
        {
		X=Total%(i<<1);
		if(X==i)
		{
			Ans^=Array[i-1];
		}
    	        else
		{
			if(X>i)
			{
				Ans^=Array[i-1]^Array[X-i];
			}
	  	        else
			{
			  	Ans^=Array[X];
			}
		}
        }
        cout<<Ans<<endl;
	return 0;
}
```

---

## 作者：ql12345 (赞：0)

考试因为中途得知打表程序超过大小限制被迫想正解。。。

其实正解并不难 ~~（只是毒瘤的csp模拟赛一开始没有草稿纸）~~

先从打表说起：直接打表会T，考虑优化打表，可以把答案这样划分：一个数%所有数，%后面数为它自身，对答案的贡献为$( ( i & 1 ) ^ ( n & 1 ) ) ? i : 0$，只需处理%前面数的即可，复杂度$O(n^2)$

考虑正解：可以将答案转化为所有数%一个数，可以发现答案为$1,2,3,4,...,j-1,0,1,2,...,j-1,0,1,...,k$于是可以预处理前缀异或和，判断前面段数奇偶，再算上末尾不成段的贡献即可

#### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long

const int N = 1233333;

int xo[N];

signed main()
{
	
	LL n, ans = 0;
	scanf("%lld", &n);
	for(int i = 1; i <= n; ++i) xo[i] = xo[i - 1] ^ i;
	for(int i = 1; i <= n; ++i)
	{
		LL x;
		scanf("%lld", &x);
		ans ^= x;
		ans ^= ((n / i) & 1) ? xo[i - 1] : 0;
		ans ^= xo[n % i];
	}
	printf("%lld", ans);
	
	return 0;
}
```

---

