# 『MdOI R2』Quo Vadis

## 题目背景

「终于……终于要到离别的时候了呢。」

『好吧。这一次过去之后，我们可能就再也不能相会了呢……』

「无论如何，还是要离别的……」

『我理解你。感谢你这些天陪伴在我身旁。』

「我也一样。如果可以的话，我真希望能继续陪伴在你身边。」

『分别之后，我也不是现在的我了……』

『至少不像现在这样。』

「离开你之后，我也不会像现在这样了……」

『君往何处？君欲往何处？君莫走，君莫走！若要走，请带上我！』

……

「所以……所以现在我们该怎么办？」

『就让我们纵然歌舞于其中吧！』

耳畔响起了小提琴和手风琴的声音，它是那么熟悉，而又那么陌生……

## 题目描述

在小 M 离别之前，他给小 K 留了一张纸条——

如果你能完成他的话，我将有可能会再次与你相遇。

给定一个**无限大**的矩阵 $A$，其中 $A_{i,j}=ij\gcd(i,j)$。

接下来有 $m$ 个操作，每行 $1$ 至 $3$ 个整数，意义如下：

$1$：对矩阵 $A$ 进行高斯消元，使之成为一个上三角矩阵。

**注意**：这里，高斯消元中只允许将一行的某一个倍数加到另一行上，不允许交换任意两行，不允许将某行乘上一个倍数，保证这样之后仍然可以得到上三角矩阵，并且保证消元之后的矩阵的每个元素均为非负整数。

$2\ x\ y$：求出当前矩阵的 $A_{x,y}$。

$3\ x$：求出 $\sum\limits_{i=1}^{x}\sum\limits_{j=1}^{x}A_{i,j}$。

$4\ x$：设 $B$ 是一个 $x$ 阶矩阵，其中 $B_{i,j}=A_{i,j}$，你需要求出 $\det B$。   

**上述所有答案对 $998244353$ 取模**。

如果你不知道什么是行列式，请点[这里](https://oi-wiki.org/math/gauss/#_12)，其中 $\text{det}$ 表示求矩阵的行列式。

~~在你完成了小 M 给小 K 的任务之后，你可以来看小提琴和手风琴的谱子。~~

## 说明/提示

【帮助与提示】     

为方便选手测试代码，本题额外提供两组附加样例供选手使用。

[样例输入1](https://www.luogu.com.cn/paste/p2w7kxik) [样例输出1](https://www.luogu.com.cn/paste/2tqpm5zj)

[样例输入2](https://www.luogu.com.cn/paste/u20duxjv) [样例输出2](https://www.luogu.com.cn/paste/jcn7ohaw)

-----

【样例解释】

注意到询问的 $x$ 和 $y$ 范围都不大于 $4$，所以我们考虑使用 $A$ 左上角的 $4\times 4$ 子矩阵进行解释，容易证明这不会造成任何影响。

在高斯消元之前，矩阵为 $\begin{pmatrix}1&2&3&4\\2&8&6&16\\3&6&27&12\\4&16&12&64\end{pmatrix}$，高斯消元后则为 $\begin{pmatrix}1&2&3&4\\0&4&0&8\\0&0&18&0\\0&0&0&32\end{pmatrix}$。

----

【数据范围】

| 子任务编号 | $1$ 操作是否存在 | $1$ 操作前 $2$ 操作中 $x,y \leq$ | $1$ 操作后 $2$ 操作中 $x,y \leq$ | $1$ 操作前 $3$ 操作中 $x \leq$ | $1$ 操作后 $3$ 操作中 $x \leq$ | $4$ 操作中 $x \leq$ | 分值 |
| :--------: | :--------------: | :------------------------------: | :------------------------------: |  :------------------------------:  | :----------------------------: | :-------------------: | :----: |
| Subtask 1  |        否        |              $5000$              |              不存在              |             $500$              |             不存在             | 不存在              | $4$  |
| Subtask 2  |        否        |            $10^{18}$             |              不存在              |             $500$              |             不存在             | 不存在              | $13$ |
| Subtask 3  |        否        |            $10^{18}$             |              不存在              |        $5 \times 10^6$         |             不存在             | $50$                | $15$ |
| Subtask 4  |        否        |            $10^{18}$             |              不存在              |             $10^8$             |             不存在             | $100$               | $16$ |
| Subtask 5  |        是        |            $10^{18}$             |              $100$               |        $5 \times 10^6$         |             $100$              | 不存在              | $17$ |
| Subtask 6  |        是        |            $10^{18}$             |          $5\times 10^5$          |             $10^8$             |             $10^3$             | $100$               | $17$ |
| Subtask 7  |        是        |            $10^{18}$             |              $5 \times 10^6$              |             $10^8$             |         $5\times 10^6$         | $5\times 10^6$      | $18$ |

对于 $100\%$ 的数据，$1 \leq m\leq 10^5$，$1$ 操作前的所有 $3$ 操作中 $\sum x$ 不大于每一个测试点 $x$ 范围的 $10$ 倍。

保证 $1$ 操作出现不超过 $1$ 次。

## 样例 #1

### 输入

```
6
4 4
2 4 4
3 4
1
2 4 4
3 4```

### 输出

```
2304
64
186
32
72```

# 题解

## 作者：Karry5307 (赞：12)

### 题意

题面写的非常清晰，不解释，摆数据范围太麻烦

### 题解

永远滴神 EA 的题解可能含有一点错误，写一个至少看上去比较对的官方题解。

日常给大家推荐 M2U 的歌呢/cy

首先直接证明结论，消元后的 $A_{i,j}$ 可以表示成

$$
A^\prime_{i,j}=
\begin{cases}
ij\varphi(i),&i\mid j
\\
0,&i\nmid j
\end{cases}
$$

考虑利用一下高斯消元的性质（~~线性代数常识~~）提出每行每列的 $i$ 和 $j$，构造新的矩阵 $B_{i,j}=\gcd(i,j)$，那么消元后的 $B_{i,j}$ 为

$$
B^\prime_{i,j}=
\begin{cases}
\varphi(i),&i\mid j
\\
0,&i\nmid j
\end{cases}
$$

这个是 $200$ 年前某篇论文的研究成果，这里简要的给大家证明一下。

考虑数学归纳法。

由于上述结论在 $1$ 到 $n-1$ 行成立，考虑第 $n$ 行，注意到只有 $n$ 的约数行才会给 $n$ 带来贡献，于是我们得到

$$B^\prime_{n,k}=B_{n,k}-\sum\limits_{d\mid n,d<n}\varphi(d)$$

讨论一下，当 $n\nmid k$ 的时候，$B_{n,k}=\gcd(n,k)$

此时注意到 $\gcd(n,k)\mid n$，所以 $B_{\gcd(n,k),k}$ 一定会给 $B_{n,k}$ 带来的贡献，并且系数为 $1$。

对于 $\gcd(n,k)$ 前面的一些行数给 $B^\prime_{n,k}$ 和 $B^\prime_{\gcd(n,k),k}$ 带来相同的贡献，所以消元到第 $\gcd(n,k)-1$ 行的时候有 $B^\prime_{n,k}=B^\prime_{\gcd(n,k),k}$。

于是第 $\gcd(n,k)$ 行向第 $n$ 行贡献完之后 $B^\prime_{n,k}$ 就为 $0$。

否则考虑这样一个事实，每一行消元结束的时候都有 $B^\prime_{n,k}=B^\prime_{n,n}$

所以根据上式，得到

$$B^\prime_{n,k}=B^\prime_{n,n}=n-\sum\limits_{d\mid n,d<n}\varphi(d)=n+\varphi(n)-\sum\limits_{d\mid n}\varphi(d)$$

于是根据狄利克雷卷积的基本公式得到

$$B^\prime_{n,k}=\varphi(n)$$

同时该结论在第一行也成立，于是结论就对任何情况下都成立了。

然后我们来考虑每一个操作。

$1$ 操作前的 $2$ 操作答案为 $ij\gcd(i,j)$，$1$ 操作后的 $2$ 操作根据这个结论来就好了。

$1$ 操作前的 $3$ 操作是 P3768，也就是让我们求这个东西（为了复习莫比乌斯反演就把过程写在这里）

$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}ij\gcd(i,j)$$

枚举 $\gcd$ 并且提出来得到

$$\sum\limits_{d=1}^{n}d^3\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{n}{d}\rfloor}ij[\gcd(i,j)=1]$$

后面是套路反演

$$\sum\limits_{d=1}^{n}d^3\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{n}{d}\rfloor}ij\sum\limits_{x\mid\gcd(i,j)}\mu(x)$$

提出来一下什么的

$$\sum\limits_{d=1}^{n}d^3\sum\limits_{x=1}^{\lfloor\frac{n}{d}\rfloor}x^2\mu(x)\left(\sum\limits_{i=1}^{\lfloor\frac{n}{xd}\rfloor}i\right)^2$$

我们设 $f(n)=\left(\sum\limits_{i=1}^{n}i\right)^2$，则有

$$\sum\limits_{d=1}^{n}d\sum\limits_{x=1}^{\lfloor\frac{n}{d}\rfloor}(xd)^2\mu(x)f(\lfloor\frac{n}{xd}\rfloor)$$

接下来记 $T=xd$，得到

$$\sum\limits_{T}^{n}T^2f(\lfloor\frac{n}{T}\rfloor)\sum\limits_{d\mid T}d\mu(\frac{T}{d})$$

右边是 $id$ 与 $\mu$ 的狄利克雷卷积，所以答案为

$$\sum\limits_{T}^{n}T^2f(\lfloor\frac{n}{T}\rfloor)\varphi(T)$$

这个可以整除分块和杜教筛搞定。

然后 $1$ 操作后的 $3$ 操作，考虑一列一列的搞，设 $g(n)$ 为第 $n$ 列的答案，得到

$$g(n)=n\sum\limits_{d\mid n}d\varphi(d)$$

设 $h(n)=\sum\limits_{d\mid n}d\varphi(d)$，对于质数 $p$ 和正整数 $k$ 我们有

$$h(p^k)=\sum\limits_{i=0}^{k}p^i\varphi(p^i)=\frac{p^{2k+1}+1}{p+1}$$

然后通过对 $n$ 质因数分解可以证明 $h(n)$ 是积性函数，于是线性筛即可。

行列式的话答案为 $(n!)^2\prod\limits_{i=1}^{n}\varphi(i)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=5e6+51,MOD=998244353,INV6=166374059,INV4=748683265;
unordered_map<ll,ll>resP;
ll n,op,gauss,ptot;
li x,y;
ll prime[348521],phi[MAXN],np[MAXN],p[MAXN],low[MAXN],f[MAXN];
ll invPr[348521],prefixF[MAXN],prod[MAXN];
inline li read()
{
    register li num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline ll qpow(ll base,ll exponent)
{
    ll res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=(li)res*base%MOD;
        }
        base=(li)base*base%MOD,exponent>>=1;
    }
    return res;
}
inline void sieve(ll limit)
{
	ll pp;
	phi[1]=f[1]=prod[0]=1;
	for(register int i=2;i<=limit;i++)
	{
		if(!np[i])
		{
			low[i]=prime[++ptot]=i,phi[i]=i-1,f[i]=((li)i*i%MOD-i+1+MOD)%MOD;
			invPr[ptot]=qpow(prime[ptot]+1,MOD-2);
		}
		for(register int j=1;j<=ptot&&prime[j]*i<=limit;j++)
		{
			np[prime[j]*i]=1;
			if(!(i%prime[j]))
			{
				low[i*prime[j]]=low[i]*prime[j];
				phi[i*prime[j]]=phi[i]*prime[j];
				if(low[i]==i)
				{
					pp=i*prime[j];
					f[pp]=(li)((li)pp*pp%MOD*prime[j]%MOD+1)*invPr[j]%MOD;
				}
				else
				{
					f[i*prime[j]]=(li)f[i/low[i]]*f[low[i]*prime[j]]%MOD;
				}
				break;
			}
			low[i*prime[j]]=prime[j],f[i*prime[j]]=(li)f[i]*f[prime[j]]%MOD;
			phi[i*prime[j]]=phi[i]*phi[prime[j]];
		}
	}
	for(register int i=1;i<=limit;i++)
	{
		p[i]=(p[i-1]+(li)i*i%MOD*phi[i]%MOD)%MOD;
		prefixF[i]=(prefixF[i-1]+(li)i*f[i]%MOD)%MOD;
		prod[i]=(li)prod[i-1]*i%MOD*i%MOD*phi[i]%MOD;
	}
}
inline ll calc2(ll x)
{
	return (li)x*(x+1)%MOD*(2*x+1)%MOD*INV6%MOD;
}
inline ll calc3(ll x)
{
	return (li)x*(x+1)%MOD*x%MOD*(x+1)%MOD*INV4%MOD;
}
inline ll prefixP(ll num)
{
	if(num<=5e6)
	{
		return p[num];
	}
	if(resP[num])
	{
		return resP[num];
	}
	ll res=calc3(num);
	for(register int l=2,r;l<=num;l=r+1)
	{
		r=num/(num/l);
		res=(res-(li)prefixP(num/l)*(calc2(r)-calc2(l-1)+MOD)%MOD+MOD)%MOD;
	}
	return resP[num]=res;
}
inline ll calc(ll num)
{
	ll res=0;
	for(register int l=1,r;l<=num;l=r+1)
	{
		r=num/(num/l);
		res=(res+(li)calc3(num/l)*(prefixP(r)-prefixP(l-1)+MOD)%MOD)%MOD;
	}
	return res;
}
inline ll getPhi(ll x)
{
	ll res=x;
	for(register int i=2;i<=sqrt(x);i++)
	{
		if(x%i==0)
		{
			res=res/i*(i-1);
			while(x%i==0)
			{
				x/=i;
			}
		}
	}
	if(x!=1)
	{
		res=res/x*(x-1);
	}
	return res;
}
int main()
{
	sieve(5000010),n=read();
	for(register int i=0;i<n;i++)
	{
		op=read();
		if(op==1)
		{
			gauss=1;
		}
		if(op==2)
		{
			x=read(),y=read();
			if(gauss)
			{
				printf("%lld\n",y%x?0:(li)x*y%MOD*getPhi(x)%MOD);
			}
			else
			{
				printf("%lld\n",(li)(x%MOD)*(y%MOD)%MOD*(__gcd(x,y)%MOD)%MOD);
			}
		}
		if(op==3)
		{
			x=read();
			if(gauss)
			{
				printf("%d\n",prefixF[x]);
			}
			else
			{
				printf("%d\n",calc(x));
			}
		}
		if(op==4)
		{
			x=read();
			printf("%d\n",prod[x]);
		}
	}
}
```

---

## 作者：EternalAlexander (赞：5)


### 题解区的多行公式挂了，请点博客查看

卡多项的官方题解简直不是人看的，写个人能看的题解。

## 结论

首先你要知道 $\sum_{d \mid i} \varphi(d) = i$。

我们首先断言，对于矩阵 $A$ 满足 $A_{i,j}=\gcd(i,j)$，在进行消元之后，有

 $A'_{i,j} = \left\{
			\begin{aligned}
			 \varphi(i), i \mid j\\
			0, i \nmid j\\
			\end{aligned}
			\right.$

考虑这样进行消元：在第 $i$ 次变换中，将第 $2i, 3i \ldots ki$ 行减去第 $i$ 行。

我们使用数学归纳法，证明这一结论对前 $n$ 行成立。

假设对于前 $i-1$ 行，这一结论成立。

我们考虑前 $i-1$ 行对 $A_{i,j}$ 的贡献，第 $i$ 行减去过 $k$ 行，当且仅当 $k \mid i$。同时，$A'_{k,j} \neq 0$ 当且仅当 $k \mid j$。综上可得，$A'_{i,j} = \gcd(i,j) - \sum_{d \mid \gcd(i,j), d < i} \varphi(d)$

当 $\gcd(i,j) \neq i$ 时，$\sum_{d \mid \gcd(i,j), d < i} \varphi(d) = \sum_{d \mid \gcd(i,j)} \varphi(d) = \gcd(i,j)$，即 $A'_{i,j} = 0$。

否则，$\sum_{d \mid \gcd(i,j), d < i} \varphi(d) = \sum_{d \mid \gcd(i,j)} \varphi(d) - \varphi(i) = \gcd(i,j)-\varphi(i)$，即 $A'_{i,j} = \varphi(i)$。

易知，$\gcd(i,j) = i$ 当且仅当 $i \mid j$。同时，这也证明了消元后的 $A'$ 是一个上三角矩阵。

综上，该结论对第 $i$ 行成立。
	
若要变换为本题中的情况，使用倍法变换，将第 $i$ 行的所有元素除以 $i$，第 $j$ 列的所有元素除以 $j$，即得到前面所说的情况。在按上一部分的做法消元之后，再逆变换回来即可。即，对于矩阵 $A$ 满足 $A_{i,j}=ij\gcd(i,j)$，在进行消元之后，有

$A'_{i,j} = \left\{
			\begin{aligned}
			ij\varphi(i), i \mid j\\
			0, i \nmid j\\
			\end{aligned}
			\right.$

## 做法

### 消元前

对于 $2$ 操作，输出 $\gcd(i,j)$。

对于 $3$ 操作，即求 $\sum_{i=1}^n \sum_{j=1}^n ij\gcd(i,j)$。使用 $\varphi$ 反演

$\sum_{i=1}^n \sum_{j=1}^n ij\gcd(i,j) $

$= \sum_{i=1}^n \sum_{j=1}^n \sum_{d \mid \gcd(i,j)} \varphi(d) $
    
$= \sum_{d=1}^n \varphi(i) \sum_{d \mid i} \sum_{d \mid j} ij $

$= \sum_{d=1}^n \varphi(i) \cdot d^2 \cdot  (\sum_{i=1}^{\lfloor \frac{n}{d} \rfloor})^2$
    
整除分块，使用亚线性筛法（例如杜教筛）筛出 $i^2 \varphi(i)$ 的前缀和即可。

对于 $4$ 操作，行列式即消元后主对角线上元素乘积，即 $\prod_{i=1}^n i^2 \varphi(i)$

### 消元后

操作 $2$ 即按给出结论输出即可。

对于操作 $3$，设 $f(i) = \sum_{d \mid i} d \varphi(d)$，所求即 $\sum_{i=1}^n i \cdot f(i)$。

不难发现 $f$ 为积性函数，考虑如何在 $p^k$ 处快速计算。有 $f(p^k) = \sum_{i=1}^k p^i \varphi(p^i) + 1$

化简一下，得到 $\sum_{i=1}^k p^{2i-1}(p-1)+1$，不难将此写为等比数列求和的形式，最后的结果是 $\frac{p^{2k+1}+1}{p+1}$。使用线性筛求解 $f$ 即可，对于更大的数据范围，可以使用 min25 筛进行计算，不过这不在本题考察范围内。


---

## 作者：无名之雾 (赞：2)

[devout](https://www.luogu.com.cn/user/97344) 讲的有趣矩阵行列式题目。

这是一篇在你不知道本题结论的情况下推导出本题的做题过程。

## Solution


### Step $1$
不难发现没有操作 $1$ 的这题是好做的。

看到操作 $1$ 常识手玩得出性质。

尝试手玩 $n=6$：

$$\begin{matrix}
 1 & 2 & 3 & 4 & 5 & 6\\
 2 & 8 & 6 & 16 & 10 & 24\\
 3 & 6 & 27 & 12 & 15 & 54\\
 4 & 16 & 12 & 64 & 20 & 48\\
 5 & 10 & 15 & 20 & 125 & 30\\
 6 & 24 & 5 & 48 & 30 & 216
\end{matrix}$$

第一次消元：

$$\begin{matrix}
 1 & 2 & 3 & 4 & 5 & 6\\
 0 & 4 & 0 & 8 & 0 & 12\\
 0 & 0 & 18 & 0 & 0 & 36\\
 0 & 8 & 0 & 48 & 0 & 24\\
 0 & 0 & 0 & 0 & 100 & 0\\
 0 & 12 & 36 & 24 & 0 & 180
\end{matrix}$$

注意到，在第一次消元后，第 $j$ 列所有与 $j$ 互质的位置变为 $0$。

进一步发现所有位置乘上了 $1-\dfrac{1}{\gcd(i,j)}$， 为了进一步探究我们的猜想，考虑继续消元：

$$\begin{matrix}
 1 & 2 & 3 & 4 & 5 & 6\\
 0 & 4 & 0 & 8 & 0 & 12\\
 0 & 0 & 18 & 0 & 0 & 36\\
 0 & 0 & 0 & 32 & 0 & 0\\
 0 & 0 & 0 & 0 & 100 & 0\\
 0 & 0 & 36 & 0 & 0 & 144
\end{matrix}$$

发现所有位置乘上了 $1-\dfrac{1}{\gcd(i/2,j/2)}$，继续消元：

$$\begin{matrix}
 1 & 2 & 3 & 4 & 5 & 6\\
 0 & 4 & 0 & 8 & 0 & 12\\
 0 & 0 & 18 & 0 & 0 & 36\\
 0 & 0 & 0 & 32 & 0 & 0\\
 0 & 0 & 0 & 0 & 100 & 0\\
 0 & 0 & 0 & 0 & 0 & 72
\end{matrix}$$

将每行每列提取公因式方便观察：

$$\begin{matrix}
 1 & 1 & 1 & 1 & 1 & 1\\
 0 & 1 & 0 & 1 & 0 & 1\\
 0 & 0 & 2 & 0 & 0 & 2\\
 0 & 0 & 0 & 2 & 0 & 0\\
 0 & 0 & 0 & 0 & 4 & 0\\
 0 & 0 & 0 & 0 & 0 & 2
\end{matrix}$$

得出结论：仅有 $i|j$ 的位置有值，且值为 $\varphi(i)$。数学归纳法易证。

### Step $2$

考虑操作 $1$ 之前的其余操作。

操作 $2$ 的答案容易得到为：

$$ij\gcd(i,j)$$

考虑操作 $3$：

$$ \sum_{i=1}^{n}  \sum_{j=1}^{n} ij \gcd(i,j) = \sum_{d=1}^{n}d^3\sum_{i=1}^{\left \lfloor \frac{n}{d} \right \rfloor }  \sum_{j=1}^{\left \lfloor \frac{n}{d} \right \rfloor}ij[\gcd(i,j)=1]$$

$$= \sum_{d=1}^{n}d^3\sum_{i=1}^{\left \lfloor \frac{n}{d} \right \rfloor }  \sum_{j=1}^{\left \lfloor \frac{n}{d} \right \rfloor}ij \sum_{k|\gcd(i,j)}\mu (x)= \sum_{d=1}^{n}d^3\sum_{i=1}^{\left \lfloor \frac{n}{d} \right \rfloor }  \mu (x) k^2( \sum_{i=1}^{\left \lfloor \frac{n}{kd} \right \rfloor}i)^2$$

$$=\sum_{kd=1}^{n}k^2d^2( \sum_{i=1}^{\left \lfloor \frac{n}{kd} \right \rfloor } i)^2 \sum_{k|kd}d\mu (\dfrac{kd}{d})=\sum_{kd=1}^{n}k^2d^2( \sum_{i=1}^{\left \lfloor \frac{n}{kd} \right \rfloor } i)^2 \varphi(kd)$$

杜教筛 $k^2d^2\varphi(kd)$ 前缀和，整数分块处理即可。

### Step $3$

考虑操作 $1$ 之后的操作。

操作 $2$ 根据之前的性质可以得到答案：

$$ij\varphi(i)$$

对于操作 $3$：

简单的推出式子：

$$ \sum_{i=1}^n \sum_{j=1}^nij\varphi(i)\cdot [i\mid j]=\sum_{i=1}^n\sum_{i\mid j}ij \varphi(i)$$

不难发现可以继续杜教筛+数论分块，但是过不去。

我们枚举列，对于第 $k$ 列答案应该为：

$$\sum^{}_{d|k}kd\varphi(d)$$ 

我们大力笛卡尔卷积：

$$f(k)=\sum^{}_{d|k}d\varphi(d)$$

这东西显然是个积性函数，跑欧拉筛就行了。

考虑如何欧拉筛：

$$f(k)= \sum_{i=1}^kp^i\cdot p^{i-1}\cdot (p-1)+1={p\over p+1}\cdot (p^{2k}-1)+1$$

所以我们欧拉筛的时候，除了维护数字 $n$ 的最小质因数 $fc_{n}$，同时维护最小值因数的出现次数次方 $pk_{n}$。

### Step $4$

看操作 $4$ 会发现其不受操作 $1$ 影响，因为行列式就是高斯消元后主对角线上元素的乘积。

所以答案应该是：

$$det B=∏_{i=1}^{n}i^2\varphi(i)$$


### Step $5$
[code](https://www.luogu.com.cn/paste/no7199sw)

---

## 作者：orz_z (赞：2)

[更好的阅读体验](https://blog.csdn.net/qq_46258139/article/details/122084436)


## 题目大意

给定一个 **无限大** 的矩阵 $A$，其中 $A_{i,j}=ij\gcd(i,j)$。

接下来有 $m$ 个操作，每行 $1$ 至 $3$ 个整数，意义如下：

* $1$：对矩阵 $A$ 进行高斯消元，使之成为一个上三角矩阵。（**注意**：这里，高斯消元中只允许将一行的某一个倍数加到另一行上，不允许交换任意两行，不允许将某行乘上一个倍数，保证这样之后仍然可以得到上三角矩阵，并且保证消元之后的矩阵的每个元素均为非负整数。）
* $2\ x\ y$：求出当前矩阵的 $A_{x,y}$。
* $3\ x$：求出 $\sum\limits_{i=1}^{x}\sum\limits_{j=1}^{x}A_{i,j}$。
* $4\ x$：设 $B$ 是一个 $x$ 阶矩阵，其中 $B_{i,j}=A_{i,j}$，你需要求出 $\det B$。

**上述所有答案对 $998244353$ 取模**。

## 解题思路

首先，对于矩阵 $A$ 满足 $A_{i,j}=i j \gcd(i,j)$，在进行高斯消元后，有：
$$
A'_{i,j}=\begin{cases}i j \varphi(i) && i \mid j \\0 && i \nmid j\end{cases}
$$
对于矩阵 $B$，满足 $B_{i,j}=\gcd(i,j)$，在进行高斯消元后，有：
$$
B'_{i,j}=\begin{cases}\varphi(i) && i \mid j\\0 && i \nmid j\end{cases}
$$
那么，对于 $1$ 操作前的 $2$ 操作答案为 $i j \gcd(i,j)$，对于 $1$ 操作后的 $2$ 操作答案为 $i j \varphi(i)$。

再看 $1$ 操作前的 $3$ 操作，答案为：
$$
\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}i j \gcd(i,j)\\
=\sum\limits_{d=1}^{n}d\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}i j [\gcd(i,j=1)]\\
=\sum\limits_{d=1}^{n}d^3\sum\limits_{i=1}^{\lfloor \frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor \frac{n}{d} \rfloor}i j [\gcd(i,j)=1]\\
=\sum\limits_{d=1}^{n}d^3 \sum\limits_{i=1}^{\lfloor \frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor \frac{n}{d}\rfloor}i j \sum\limits_{p|\gcd(i,j)}\mu(p)\\
=\sum\limits_{d=1}^{n}d^3\sum\limits_{p=1}^{\lfloor\frac{n}{d}\rfloor} \mu(p)\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{n}{d}\rfloor}i j\\
=\sum\limits_{d=1}^{n}d^3\sum\limits_{p=1}^{\lfloor\frac{n}{d}\rfloor}p^2 \mu(p)\sum\limits_{i=1}^{\lfloor\frac{n}{pd}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{n}{pd}\rfloor}i j\\
=\sum\limits_{d=1}^{n}d^3\sum\limits_{p=1}^{\lfloor\frac{n}{d}\rfloor}p^2 \mu(p)\left(\sum\limits_{i=1}^{\lfloor\frac{n}{pd}\rfloor}i\right)^2\\
\sum\limits_{d=1}^{n}d\sum\limits_{p=1}^{\lfloor\frac{n}{d}\rfloor}(pd)^2 \mu(p)\left(\sum\limits_{i=1}^{\lfloor\frac{n}{pd}\rfloor}i\right)^2
$$
设 $f(n)=\left(\sum\limits_{i=1}^{n}i\right)^2$，则有：
$$
\sum\limits_{d=1}^{n}d\sum\limits_{p=1}^{\lfloor\frac{n}{d}\rfloor}(pd)^2 \mu(p)f(\lfloor\frac{n}{pd}\rfloor)
$$
设 $T=pd$，有：
$$
\sum\limits_{T}^{n}T^2f(\lfloor\frac{n}{T}\rfloor)\sum\limits_{d|T}d \mu(\frac{T}{d})
$$
根据狄利克雷卷积，有：
$$
\sum\limits_{T}^{n}T^2f(\lfloor\frac{n}{T}\rfloor)\varphi(T)
$$
数论分块套杜教筛即可。

对于 $1$ 操作后的 $3$ 操作，设 $g(n)$ 为第 $n$ 列的和，那么有：
$$
g(n)=n\sum\limits_{d|n}d\varphi(d)
$$
设 $h(n)=\sum\limits_{d|n}d \varphi(d)$，显然， $h(n)$ 是个积性函数，线性筛即可。

答案即为：
$$
\sum\limits_{i=1}^{n}g(i)\\
=\sum\limits_{i=1}^{n}\left(i \times h(i)\right)
$$
对于操作 $4$，行列式即消元后主对角线上元素乘积，所以答案即为：
$$
\prod\limits_{i=1}^{n}i^2\varphi(i)
$$


## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

const int MOD = 998244353, _ = 5e6 + 51, INV6 = 166374059, INV4 = 748683265, MAXM = 4e5 + 7;

unordered_map<int, int> resP;

int n, op, flag, tot;

int x, y;

int prime[MAXM], phi[_], vis[_], p[_], low[_], g[_];

int invPr[MAXM], prefix[_], prod[_];

inline int qpow(int x, int y)
{
    int res = 1;
    while (y)
    {
        if (y & 1)
            res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}

inline void solve(int n)
{
    int pp;
    phi[1] = g[1] = prod[0] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!vis[i])
        {
            low[i] = prime[++tot] = i, phi[i] = i - 1, g[i] = (i * i % MOD - i + 1 + MOD) % MOD;
            invPr[tot] = qpow(prime[tot] + 1, MOD - 2);
        }
        for (int j = 1; j <= tot && i * prime[j] <= n; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                low[i * prime[j]] = low[i] * prime[j];
                phi[i * prime[j]] = phi[i] * prime[j];
                if (low[i] == i)
                {
                    pp = i * prime[j];
                    g[pp] = (pp * pp % MOD * prime[j] % MOD + 1) * qpow(prime[j] + 1, MOD - 2) % MOD;
                }
                else
                {
                    g[i * prime[j]] = g[i / low[i]] * g[low[i] * prime[j]] % MOD;
                }
                break;
            }
            low[i * prime[j]] = prime[j], g[i * prime[j]] = g[i] * g[prime[j]] % MOD;
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        p[i] = (p[i - 1] + i * i % MOD * phi[i] % MOD) % MOD;
        prefix[i] = (prefix[i - 1] + i * g[i] % MOD) % MOD;
        prod[i] = prod[i - 1] * i % MOD * i % MOD * phi[i] % MOD;
    }
}


inline int get_phi(int x)
{
    int res = x;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            res = res / i * (i - 1);
            while (x % i == 0)
                x /= i;
        }
    if (x != 1)
        res = res / x * (x - 1);
    return res;
}

inline int calc2(int x)
{
    return x * (x + 1) % MOD * (2 * x + 1) % MOD * INV6 % MOD;
}

inline int calc3(int x)
{
    return x * (x + 1) % MOD * x % MOD * (x + 1) % MOD * INV4 % MOD;
}

inline int prefixP(int num)
{
    if (num <= 5e6)
        return p[num];
    if (resP[num])
        return resP[num];
    int res = calc3(num);
    for (int l = 2, r; l <= num; l = r + 1)
    {
        r = num / (num / l);
        res = (res - prefixP(num / l) * (calc2(r) - calc2(l - 1) + MOD) % MOD + MOD) % MOD;
    }
    return resP[num] = res;
}

inline int calc(int num)
{
    int res = 0;
    for (int l = 1, r; l <= num; l = r + 1)
    {
        r = num / (num / l);
        res = (res + calc3(num / l) * (prefixP(r) - prefixP(l - 1) + MOD) % MOD) % MOD;
    }
    return res;
}

signed main()
{
    solve(5000010);
    n = read();
    while(n--)
    {
        op = read();
        if (op == 1)
            flag = 1;
        if (op == 2)
        {
            x = read(), y = read();
            if (flag)
                printf("%lld\n", y % x ? 0 : x * y % MOD * get_phi(x) % MOD);
            else
                printf("%lld\n", (x % MOD) * (y % MOD) % MOD * (__gcd(x, y) % MOD) % MOD);
        }
        if (op == 3)
        {
            x = read();
            if (flag)
                printf("%lld\n", prefix[x]);
            else
                printf("%lld\n", calc(x));
        }
        if (op == 4)
        {
            x = read();
            printf("%lld\n", prod[x]);
        }
    }
    return 0;
}
```

 

---

## 作者：Prean (赞：0)

大家好啊，我是 lmpp，今天来点大家想看的 $O(n+m)$ 的东西

冲刺！冲刺！冲！冲！

根据线性代数知识，设消元前后的矩阵分别为 $A$ 和 $B$，那么可以知道存在一个系数矩阵 $C$ 满足 $A\times C=B$，手动找规律即可发现有：
$$C_{i,j}=[i\mid j]\frac{j}{i}$$
$$B_{i,j}=[i\mid j]ij\varphi(i)$$
不难验证这是对的。

那么第 $4$ 类询问的答案就是 $\prod_{i=1}^ni^2\varphi(i)$。

### case1
$$S1(n)=\sum_{i=1}^n\sum_{j=1}^nij\gcd(i,j)$$
$$S1(n)=\sum_{d=1}^{n}d^3\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}ij[\gcd(i,j)=1]$$
$$S1(n)=\sum_{d=1}^{n}d^3\sum_{k=1}^{\lfloor\frac{n}{d}\rfloor}k^2\mu(k)(\frac{\lfloor\frac{n}{dk}\rfloor(\lfloor\frac{n}{dk}\rfloor+1)}{2})^2$$
$$S1(n)=\sum_{T=1}^{n}(id^2\times\varphi)(T)(\frac{\lfloor\frac{n}{T}\rfloor(\lfloor\frac{n}{T}\rfloor+1)}{2})^2$$
$$S1(n)-S1(n-1)=\sum_{d\mid n}(id^2\times\varphi)(\frac{n}{d})\times\frac{1}{4}d^2((d+1)^2-(d-1)^2)$$
$$S1(n)-S1(n-1)=\sum_{d\mid n}(id^2\times\varphi)(\frac{n}{d})\times d^3=(id^2\times(\varphi*id))(n)$$
线性筛 $id^2\times(\varphi*id)$ 后求前缀和即可。
### case2
$$S2(n)=\sum_{i=1}^n\sum_{j=1}^n[i\mid j]ij\varphi(i)$$
$$S2(n)=\sum_{i=1}^ni^2\varphi(i)\frac{\lfloor\frac{n}{i}\rfloor(\lfloor\frac{n}{i}\rfloor+1)}{2}$$
$$S2(n)-S2(n-1)=\sum_{d\mid n}(\frac{n}{d})^2\varphi(\frac{n}{d})\times(\frac{d(d+1)}{2}-\frac{(d-1)d}{2})$$
$$S2(n)-S2(n-1)=((id^2\times\varphi)*id)(n)$$
线性筛 $(id^2\times\varphi)*id$ 即可。

但是因为一个 $10^8$ 的数组空间就有 381MB，所以需要稍微对线性筛进行变形，枚举 $i\times p^k\leq n\And p<\mathrm{minp}(i)$ 而不是正常线性筛的枚举 $i\times p\leq n\And p<\mathrm{minp}(i)$。
```cpp
inline void sieve(const int n,const int m){
    phi[1]=f[1]=g[1]=h[0]=1;
    for(int i=2;i<=n;++i){
    	const int lmt=n/i;
        if(!f[i]){
            const int p3=1ll*i*i%mod*i%mod;
            pri[++top]=i;
            for(int pk=1,p3k=1;pk<=lmt;pk*=i,p3k=1ll*p3k*p3%mod){
            	const int x=pk*i,i2phi=(p3+1ll*(mod-i)*i)%mod*p3k%mod;
            	f[x]=(i2phi+1ll*p3*f[pk])%mod;
            	if(x<=m){
	            	g[x]=(i2phi+1ll*i*g[pk])%mod;
	            	phi[pk*i]=pk*(i-1);
				}
			}
        }
        for(int j=1;i*pri[j]<=n&&i%pri[j];++j){
        	const int p=pri[j],lim=lmt/p;
        	for(int pk=1;pk<=lim;){
	        	const int x=(pk*=p)*i;
                f[x]=1ll*f[i]*f[pk]%mod;
                if(x<=m){
                    g[x]=1ll*g[i]*g[pk]%mod;
		    		phi[x]=phi[i]*phi[pk];
				}
			}
        }
    }
    for(int i=1;i<=m;++i){
        f[i]=Add(f[i-1],f[i]);
        g[i]=Add(g[i-1],g[i]);
        h[i]=1ll*h[i-1]*i%mod*i%mod*phi[i]%mod;
    }
    for(int i=m+1;i<=n;++i)f[i]=Add(f[i-1],f[i]);
}
```

---

## 作者：bluewindde (赞：0)

upd 2024-09-02：LaTeX 炸了，已修。

upd 2024-11-26：添加了证明，删了一些批话，修了一些病句。

---

容易发现需要分类讨论操作 $1$ 前后的其他操作。

对于操作 $1$ 之前的操作 $2$，答案为 $ij \gcd(i, j)$。

对于操作 $1$ 之前的操作 $3$，答案为（令 $T = kd$，设 $f(x) = \frac 1 2 x (x + 1)$）

$$
\begin{aligned}
&\sum\limits_{i = 1}^x \sum\limits_{j = 1}^x ij \gcd(i, j) \\
= &\sum\limits_{k = 1}^n k^3 \sum\limits_{i = 1}^{\lfloor \frac x k \rfloor} \sum\limits_{j = 1}^{\lfloor \frac x k \rfloor} ij [\gcd(i, j) = 1] \\
= &\sum\limits_{k = 1}^n k^3 \sum\limits_{d = 1}^{\lfloor \frac x k \rfloor} d^2 \mu(d) f \left( \left\lfloor \frac n {kd} \right\rfloor \right)^2 \\
= &\sum\limits_{T = 1}^x T^2 f \left( \left\lfloor \frac x T \right\rfloor \right)^2 \sum\limits_{k \mid T} \mu(k) \frac T k \\
= &\sum\limits_{T = 1}^x \varphi(T) T^2 f \left( \left\lfloor \frac x T \right\rfloor \right)^2 \\
\end{aligned}
$$

函数 $\varphi \cdot \operatorname{id}_2$ 与 $\operatorname{id}_2$ 的狄利克雷卷积为 $\operatorname{id}_3$，数论分块 + 杜教筛可以计算此和式。

---

注意到（可以打表观察），设操作 $1$ 结束后得到矩阵 $B = (b_{ij})$，则 $b_{ij}$ 满足

$$b_{ii} = i^2 \varphi(i)$$

$$b_{ij} = \frac j i b_{ii} [i \mid j] = ij \varphi(i) [i \mid j]$$

此时操作 $2$ 的答案如上所述。

对于操作 $1$ 之后的操作 $3$，答案为

$$
\begin{aligned}
&\sum\limits_{i = 1}^x \sum\limits_{j = 1}^x ij \varphi(i) [i \mid j] \\
= &\sum\limits_{i = 1}^x \varphi(i) i^2 \sum\limits_{j = 1}^{\lfloor \frac x i \rfloor}  j \\
= &\sum\limits_{i = 1}^x \varphi(i) i^2 f \left( \left\lfloor \frac x i \right\rfloor \right) \\
\end{aligned}
$$

~~该式亦可使用数论分块 + 杜教筛~~。前述方法时间复杂度过高，不可通过。设 $g(x) = \sum\limits_{d \mid x} d \varphi(d)$，操作 $3$ 答案即为 $\sum\limits_{i = 1}^n i g(i)$。考虑枚举每个 $d$ 的倍数求 $g$ 得到 $O(n \ln n)$ 的时间复杂度（$g$ 也是积性函数，也可以线性筛求），可以通过。

最后，操作 $1$ 不会改变操作 $4$ 的答案，从始至终，操作 $4$ 答案为

$$\sum\limits_{i = 1}^x i^2 \varphi(i)$$

处理完上述所有式子，即可解决本题。

---

接下来说明消元结果，首先考虑一个定理。

> **定理**
>
> 对矩阵 $A = (a_{ij}), a_{ij} = \gcd(i, j)$，消元后的矩阵 $B = (b_{ij})$ 满足
>
> $$\sum\limits_{d \mid n} b_{dd} = n$$
>
> **证明**
>
> 初始 $b_{ii} = i$。
>
> 对于第 $i$ 列，高斯消元将第 $i$ 行与第 $j$ 行辗转相减。
>
> 当 $i = 1$ 时，因为矩阵第一行全部为 $1$，所以矩阵会被整体减 $1$。
>
> 于是对于 $i > 1$ 的所有行 $i$，只有满足 $i \mid j$ 的 $b_{ij} \ne 0$；对于 $j > 1$ 的所有列 $j$，只有满足 $j \mid i$ 的 $b_{ij} \ne 0$。
>
> 继续对 $i > 1$ 的行消元时，会被修改的只有 $i \mid x$ 且 $i \mid y$ 且 $x > i$ 的 $x, y$，此时 $b_{xy} \leftarrow b_{xy} - b_{ii}$。
>
> 综上，结束时的矩阵有
>
> $$b_{nn} = n - \sum\limits_{d \mid n \land d \ne i} b_{dd}$$
>
> 移项后得到
>
> $$\sum\limits_{d \mid n} b_{dd} = n$$
>
> Q.E.D.

原矩阵可以通过对第 $i$ 行除以 $i$，对第 $j$ 行除以 $j$，变化为 $a'_{ij} = \gcd(i, j)$。对新矩阵 $A'$ 消元后，再分别乘回来。根据矩阵的初等变换知识，这样操作不会改变消元结果。

接下来证明定理给出的式子可以推出 $b_{nn} = \varphi(n)$。

> **证明**
>
> 考虑归纳，知 $b_{11} = 1$，假设对 $k < n$ 此定理成立，则
>
> $$
> \begin{aligned}
> b_{nn} &= n - \sum\limits_{d \mid n \land d \ne n} b_{dd} \\
> &= n - \sum\limits_{d \mid n \land d \ne n} \varphi(d) \\
> &= n - \left( \sum\limits_{d \mid n} \varphi(d) - \varphi(n) \right) \\
> &= n - (n - \varphi(n)) \\
> &= \varphi(n) \\
> \end{aligned}
> $$
>
> Q.E.D.

综上所述，消元结果

$$b_{nn} = n^2 \varphi(n)$$

得到证明。

---

