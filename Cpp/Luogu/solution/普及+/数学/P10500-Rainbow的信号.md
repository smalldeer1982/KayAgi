# Rainbow的信号

## 题目描述

Freda 发明了传呼机之后，rainbow 进一步改进了传呼机发送信息所使用的信号。

由于现在是数字、信息时代，rainbow 发明的信号用 $N$ 个自然数表示。

为了避免两个人的对话被大坏蛋 VariantF 偷听，rainbow 把对话分成 $A、B、C$ 三部分，分别用 $a、b、c$ 三个密码加密。

现在 Freda 接到了 rainbow 的信息，她的首要工作就是解密。

Freda 了解到，这三部分的密码计算方式如下：

在 $1 \sim N$ 这 $N$ 个数中，等概率地选取两个数 $l、r$，如果 $l>r$，则交换 $l、r$。

把信号中的第 $l$ 个数到第 $r$ 个数取出来，构成一个数列 $P$。

$A$ 部分对话的密码是数列 $P$ 的 $xor$ 和的数学期望值，$xor$ 和就是数列 $P$ 中各个数异或之后得到的数； $xor$ 和的期望就是对于所有可能选取的 $l、r$，所得到的数列的 $xor$ 和的平均数。

$B$ 部分对话的密码是数列 $P$ 的 $and$ 和的期望，定义类似于 $xor$ 和。

$C$ 部分对话的密码是数列 $P$ 的 $or$ 和的期望，定义类似于 $xor$ 和。

请你帮忙计算这三个密码。

## 说明/提示

### 样例解释

样例 1 共包含四种可能的 $l,r$：

|c|c|c|c|
|-|-|-|-|
|$l, r$ | xor 和 | and 和 | or 和 |
|1,1 | 4 | 4 | 4 |
|1,2 | 1 | 4 | 5 |
|2,1 | 1 | 4 | 5 |
|2,2 | 5 | 5 | 5 |

以上每一对 $l,r$ 出现的概率均相同, 因此分别对 xor 和、and 和、or 和取平均数就是数学期望值。

## 数据范围与约定

对于 $20 \%$ 的数据， $1 \le N \le 100$ 。  
对于 $40 \%$ 的数据， $1 \le N \le 1000$ 。  
对于另外 $30 \%$ 的数据, $N$ 个数为 $0$ 或 $1$ 。  
对于 $100 \%$ 的数据, $1 \le N \le 100000$，$N$ 个自然数均不超过 $10^9$ 。

## 样例 #1

### 输入

```
2
4 5```

### 输出

```
2.750 4.250 4.750
```

# 题解

## 作者：Elaina_0 (赞：11)

# P10500 Rainbow的信号

谢谢管理大大的审核，

顺便无耻的推一下 [blog](https://www.cnblogs.com/Elaina-0)。

## 思路
因为位运算当前位的结果只与当前位有关，所以可以单独考虑每一位，最后将每一位的贡献相加就是答案。

由于 $l$，$r$ 是等概率选取，所以选取长度为 $1$ 的区间（$l = r$）的概率是 $\frac{1}{n^2}$，选取其他区间（$l \neq r$）的概率是 $\frac{2}{n^2}$。

设 $a_i,a_j$ 表示第 $i$ 个数字的第 $j$ 个二进制位的值；$last[k] (k=0,1)$ 表示 $k$ 最后出现的位置。

分别讨论三种运算的期望：

- $\operatorname{and}$  的期望

	

  - 若第 $x$ 个数字的第 $k$ 位是 $1$，以 $x$ 为右端点，在 $[last[0]+1,r]$ 区间内任取两个数组成的区间 $\operatorname{and}$ 和都是 $1$，因此她的贡献为：
  
    $$\begin{cases}
      last[0] = x 　2^k \times \frac{1}{n^2}\\
      
      last[0]+1 \neq x　2^k \times (x-(last[0]+1)) \times \frac{2}{n^2}
    \end{cases}$$  

  
  - 若第 $x$ 个数字的第 $k$ 为是 $0$，不存在左端点与 $x$ 的组合使得区间的 $\operatorname{and}$ 和为 $1$。

- $\operatorname{or}$ 的期望

  - 若第 $x$ 个数字的第 $k$ 位是 $1$，前面所有点都可以与 $x$ 组成区间使得 $\operatorname{or}$ 和为 $1$，所以她的贡献为：
  	$$\begin{cases}
      l = x　2^k \times \frac{1}{n^2}\\
      
      l \neq x　2^k \times (x−1) \times \frac{2}{n^2}
  	 \end{cases}$$  

 	- 若第 $x$ 个数字的第 $k$ 位是 $0$，以 $x$ 为右端点，$≤last[1]$ 的数字可以选作左端点，所以她的贡献为：
    
    $$2^k \times last[1] \times \frac{2}{n^2}$$
  
- $\operatorname{xor}$ 的期望

  设 $t$ 是 $[l,x]$ 区间的 $\operatorname{xor}$ 和, $c1$ 表示 $[l,x]$ 区间 $\operatorname{xor}$ 和为 $0$ 的 $l$ 个数，$c2$ 表示 $[l,x]$ 区间 $\operatorname{xor}$ 和为 $1$ 的 $l$ 个数。
  
  从 $l = x$ 开始，将 $l$ 向左移动，若第 $l$ 位是 $1$ 则 $t$ 取反，否则 $t$ 不变。
  
  - 若第 $x$ 个数字的第 $k$ 位是 $1$，则 $l$ 只能选择 $c1$ 表示的部分，所以她的贡献为：
  
  	$$2^k \times c1 \times \frac{2}{n^2}$$
  
  - 若第 $x$ 个数字的第 $k$ 位是 $0$，则 $l$ 只能选择 $c2$ 表示的部分，所以她的贡献为：
  
  	$$2^k \times c2 \times \frac{2}{n^2}$$
  
  	最后还要加上 $l = x$ 的贡献：
    
    $$2^k \times \frac{1}{n^2}$$

 	当右端点 $r$ 增加 $1$，令 $c1$ 增加 $1$。
  
  	若 $a[r] = 1$，则还需交换 $c1,c2$。


## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Elaina 0
const int N=100010;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}

int n,a[N];
int last[3],c1,c2;
double ansand,ansor,ansxor;

main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	
	for(int i=0;i<=30;i++){
		last[0]=last[1]=0;
		c1=c2=0;
		for(int j=1;j<=n;j++){
			int now=(a[j]>>i)&1;
			double ret=(double)(1<<i)/(n*n);
			if(now){
				ansand+=ret+2.0*ret*(j-(last[0]+1));
				ansor+=ret+2.0*ret*(j-1);
				ansxor+=ret+2.0*ret*c1;
			}else{
				ansor+=2.0*ret*last[1];
				ansxor+=2.0*ret*c2;
			}
			last[now]=j;
			c1++;
			if(now) swap(c1,c2);
		}
	}
	
	printf("%.3lf %.3lf %.3lf",ansxor,ansand,ansor);
	return Elaina;
}
```

---

## 作者：azaa414 (赞：6)

**思路来源：《算法竞赛进阶指南》--lyd**

## 题意解析

给你一个数列 $A$，从中等概率地选取一个左端点为 $l$，右端点为 $r$ 的区间，得到的数组成一个新数列 $P$。

求数列 $P$ 的 ```xor```，```and```，```or``` 和的期望。

## 题目分析
我们都知道，期望这东西实质上就是带权平均值，权重是这个值出现的概率（不了解的同学可以自行百度[期望的概念](https://baike.baidu.com/item/%E6%95%B0%E5%AD%A6%E6%9C%9F%E6%9C%9B/5362790)）。所以我们需要从概率下手。

### 概率

考虑 $l=r$ 的情况，显然从 $1 \sim n$ 中同时选到 $l,r$ 的概率为

$$\frac{1}{n} \times \frac{1}{n} = \frac{1}{n^2} $$

（根据乘法原理，同时选到 $l,r$ 的概率就是，选到 $l$ 的概率乘以选到 $r$ 的概率）。

考虑 $l \ne r$ 的情况，显然从 $1 \sim n$ 中选到 $l,r$ 的概率为

$$\frac{1}{n} \times \frac{1}{n} + \frac{1}{n} \times \frac{1}{n}= \frac{2}{n^2}$$

有的同学就问了，为什么这里要乘以 $2$？因为题目中说到

> 如果 $l > r$，则交换 $l,r$。

所以这里相当于两种情况归并到一种，概率就要乘以 $2$ 了。

那这个时候我们就把概率搞清楚了，该搞期望了。

### 期望

期望无非就是在概率的基础上乘以值，这里才用逐位操作的方法，即把所有 $A_i$ 拆分成二进制的形式。

这样，我们可以一层一层地算，假设当前枚举到了第 $k$ 位，对于每个 $A_i$ 的第 $k$ 位，我们用 $B_i$ 表示。

为什么这样做？因为位运算不进位，不同位都是独立的，互不影响；这题又涉及位运算，相同位是可以影响的。所以我们不妨拆开每个数来算。

这么一来，根据期望是线性的，累加每一位的贡献即可。

先考虑 $l=r$，因为每一位的实际意义是整数的第 $k$ 位，所以当 $B_i=1$ 时，对答案的贡献是

$$2^k \times \frac{1}{n^2}$$

计算过程中顺手加上即可。

再考虑 $l \ne r$，我们分 ```and```，```or```，```xor``` 三部分，从易到难来讲。

#### and

根据 ```and``` 的定义，不难发现，只要区间内有一个 $0$，最后得到的这一位就是 $0$，期望也是 $0$，所以考虑 $B_r=1$ 的情况即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/qc9bp2go.png)

以这个为例，显然两个 $0$ 中间夹的区间只有 $(2,3)$，$(2,4)$，$(2,5)$ 对答案有贡献，并且贡献值一样。

设 $last[0]$ 表示上一个最近的 $0$ 的位置，所以整个下来的 ```and``` 期望值为

$$2^k \times ((r-1)-(last[0]+1)+1) \times \frac{2}{n^2}$$

其中 $2^k$ 的意义同上所述，$(r-1)-(last[0]+1)+1$ 是满足结果为 $1$ 的区间总数 $sum-1$，$-1$ 是为了忽略掉 $l=r$ 的情况，最后乘以概率 $\frac{2}{n^2}$ 就有上述式子了。

#### or

根据 ```or``` 的定义，如果区间内有 $1$ 最后就是 $1$ 了，所以分开讨论。

考虑 $B_r=1$ 的情况，无论 $l$ 怎么取，都对答案有贡献，所以同 ```and```，有贡献为

$$2^k \times (r-1) \times \frac{2}{n^2}$$

考虑 $B_r \ne 1$，那么只有 $l \sim r$ 有至少一个 $1$，结果才有贡献。

设 $last[1]$ 表示上一个最近的 $1$ 的出现位置，那么只要 $l \in [1,last[1]]$，结果就有贡献。

这里 $l$ 是有 $1 \sim last[1]$ 一共 $last[1]$ 种选择，贡献就为

$$2^k \times last[1] \times \frac{2}{n^2}$$

#### xor

根据 ```xor``` 的定义，遇到 $0$ 时结果不变，遇到 $1$ 时取反，所以我们以 $1$ 为界来分割，每个割出来的部分 ```xor``` 和都是 $1$。

我们定义两个变量 $c_1,c_2$，分别记录奇数段和偶数段的长度，不难发现 $B_r=0$ 时，每次 ```xor``` 到偶数段时结果为 $1$，所以拿偶数段总长计算即可，期望为

$$2^k \times c_2 \times \frac{2}{n^2}$$

同理，$B_r=1$ 时为

$$2^k \times c_1 \times \frac{2}{n^2}$$

并且遇见 $1$ 时，要将 $c_1,c_2$ 互换，因为此时分出来了新段，奇数偶数段互换。

#### 综上

将所有期望分情况计算累加，最后保留三位小数输出即可。

## 代码实现

需要注意的是，因为涉及 ```*``` 运算，不要忘记开 ```long long```！

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
inline long long read()
{
    char c = 0; int x = 0; bool f = 0;
    while (!isdigit(c)) f = c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    return f ? -x : x;
}
long long a[100010], n, last[2], c1, c2;//别忘了开long long
double ansxor, ansor, ansand;
int main()
{
    n = read();
    for (register int i = 1; i <= n; ++i)
        a[i] = read();
    for (register int k = 0; k <= 30; ++k)
    {
        last[0] = last[1] = c1 = c2 = 0;
        for (register int i = 1; i <= n; ++i)
        {
            int now = (a[i] >> k) & 1;
            double temp = 1.0 * (1 << k) / (n * n);
            if (now)
            {
                ansand += temp + 2.0 * temp * (i - last[0] - 1);
                ansor += temp + 2.0 * temp * (i - 1);
                ansxor += temp + 2.0 * temp * c1;
                ++c1;
                swap(c1, c2);
            }
            else
            {
                ansor += 2.0 * temp * last[1];
                ansxor += 2.0 * temp * c2;
                ++c1;
            }
            last[now] = i;
        }
    }
    printf("%.3lf %.3lf %.3lf", ansxor, ansand, ansor);
    return 0;
}
```

---

## 作者：粥2414 (赞：2)

# 题目描述
给你一个序列，每次选定一个区间，要求其 ``xor`` 和、``and`` 和、``or`` 和的期望。
# 思路
由于位运算不牵扯进位，所以可以把每一个数的各个二进制位分开来求，也就是转换为 $31$ 个 $0$ 或 $1$。依据**数学期望是线性函数**的性质得到最终答案。

显然每个长度大于 $1$ 的区间被选择的概率是 $\frac 2 {n^2}$，而每个长度为 $1$ 的区间被选择的概率是 $\frac 1 {n^2}$，所以我们只需要计算区间位运算和即可。

考虑如何处理答案。  
设 $ans$ 为位运算的结果，它的二进制第 $i$ 位为 $p_i$，那么它的期望：
$$
\mathbb{E}(ans)=\mathbb{E}(2^0p_1+2^1p_2+\cdots+2^{30}p_{31})=2^0\mathbb{E}(p_1)+\cdots+2^{30}\mathbb{E}(p_{31})
$$
$\mathbb{E}(0)$ 显然为 $0$，所以只需要当当前位的位运算和为 $1$ 时计算答案即可。我们要求的就是哪些区间的位运算和为 $1$。
# 朴素算法
暴力枚举区间 $[l,r]$，暴力计算答案，时间复杂度 $O(n^3)$，显然不可通过此题。考虑优化。
# 优化
首先对于每个位运算，当当前位的数为 $1$ 时，会对答案产生一个长度为 $1$ 的区间的贡献，累加答案即可。

接下来讨论区间长度不为 $1$ 的情况。
## or
先从最简单的开始。

显然当第 $r$ 位的值为 $1$ 时，对于 $\forall l\in [1,r-1]$，区间 $[l,r]$ 的 ``or`` 和为 $1$。

当第 $r$ 位的值为 $0$ 时，记 $last_1$ 为 $r$ 之前距离 $r$ 最近的 $1$ 的位置。显然对于 $\forall l\in [1,last_1]$，区间 $[l,r]$ 的 ``or`` 和为 $1$。
## and
``and`` 的情况与 ``or`` 类似。

显然当第 $r$ 位的值为 $0$ 时，不存在满足 $[l,r]$ 的 ``and`` 和为 $1$ 的 $l$。

当第 $r$ 位的值为 $1$ 时，显然满足条件的区间 $[l,r]$ 内必须全部为 $1$，那么可以记 $last_0$ 为 $r$ 之前距离 $r$ 最近的 $0$ 的位置。显然区间 $[last_0+1,r]$ 中的数全为 $1$，对于 $\forall l\in [last_0+1,r]$，区间 $[l,r]$ 的 ``and`` 和为 $1$。
## xor
``xor`` 的情况是最复杂的，这题的难点就在于此。

这时候如果还按照上面的思路，记录上一个 $0$ 或 $1$ 出现的位置再计算，那么会得到错误的结果。所以我们需要转变思路。

~~手动模拟~~演算几次后发现，对于一个固定的 $r$，使得区间 $[l,r]$ 的 ``xor`` 和为 $1$ 的 $l$ 们并不在某一个区间，而是分布于若干个分开的区间。再仔细观察后可发现，使区间 $[l,r]$ 的 ``xor`` 和为 $0$ 或为 $1$ 的 $l$ 们以 $1$ 为分界点。

于是想到设 $c_0$ 为对于当前的 $r$，能使区间 $[l,r-1]$ 的 ``xor`` 和为 $0$ 的 $l$ **个数**，$c_1$ 也是类似。

那么当第 $r$ 位为 $0$ 时，此时对于 $\forall l\in [1,r-1]$，区间 $[l,r-1]$ 再异或上第 $r$ 位**不会**改变结果，所以共有 $c_1$ 个 $l$ 是符合条件的。同时区间 $[r,r]$ 的 ``xor`` 和为 $0$，所以 $c_0$ 需要加 $1$。

当第 $r$ 位为 $1$ 时，此时对于 $\forall l\in [1,r-1]$，区间 $[l,r-1]$ 再异或上第 $r$ 位**会**改变结果。所以共有 $c_0$ 个 $l$ 是符合条件的。注意由于结果会改变，所以需要交换 $c_0$ 和 $c_1$，然后让 $c_1$ 加 $1$。

---

然后就可以愉快地 AC 啦！
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define dd double
inline int read() {
	int x = 0, f = 1;
	char ch;
	while ((ch = getchar()) < 48 || ch > 57)if (ch == '-')f = -1;
	while (ch >= 48 && ch <= 57)x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
char __sta[1009], __len;
inline void write(int x, bool bo) {
	if (x < 0)putchar('-'), x = -x;
	do __sta[++__len] = x % 10+48, x /= 10;
	while (x);
	while (__len)putchar(__sta[__len--]);
	putchar(bo ? '\n' : ' ');
}
const ll N=1e5+9;
ll n;
ll a[N];
ll last[2];
dd qp[32]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648,};
ll now[N];
dd ansx,ansa,anso;
inline void solvexor(ll k){
	ll c1=0,c0=0;//使l~r-1区间xor和为1或0的l的数量
	for(int i=1;i<=n;i++){
		if(now[i]==0){
			ansx+=c1*qp[k]*2/(n*n);
			c0++;
		}else{
			ansx+=qp[k]/(n*n);
			ansx+=c0*qp[k]*2/(n*n);
			swap(c0,c1);
			c1++;
		}
	}
}
inline void solveand(ll k){
	for(int i=1;i<=n;i++){
		if(now[i]==1){
			ansa+=qp[k]/(n*n);
			ansa+=qp[k]*(i-last[0]-1)*2.0/(n*n);
		}
		last[now[i]]=i;
	}
}
inline void solveor(ll k){
	last[0]=last[1]=0;
	for(int i=1;i<=n;i++){
		if(now[i]==1){
			anso+=qp[k]/(n*n);
			anso+=qp[k]*(i-1)*2/(n*n);
//			cout<<"dhw "<<last[1]<<' ';
		}else{
			anso+=qp[k]*last[1]*2/(n*n);
//			cout<<"lh  "<<last[1]<<' ';
		}
//		cout<<anso<<endl;
		last[now[i]]=i;
	}
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int k=1;k<=31;k++){
		for(int i=1;i<=n;i++){
			now[i]=(a[i]>>(k-1))&1;
		}
		last[0]=last[1]=0,
		solvexor(k-1),solveand(k-1),solveor(k-1);
	}
	printf("%.3lf %.3lf %.3lf",ansx,ansa,anso);
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：2)

难得能不看题解的情况下做出一道绿题，来写篇题解。    

---
简要题意：给一个序列，求其中所有的子区间的 xor、and、or 的和的平均数。左右端点交换也算一次。    
比如样例中要计算的区间为 $[1,1],[1,2],[2,1],[2,2]$。  
（当然了 $[1,2]$ 和 $[2,1]$ 是等价的。）     
~~本来呢它丢给你一个“期望”怪吓人的，但是它告诉你期望就是平均数，这令题目难度下降了不少。~~     
~~好吧因为取到每一种情况的概率是相同的，所以期望和平均数没啥区别。~~

---
由于在每一个二进制位上的运算不影响别的二进制位，所以考虑拆位处理。       
数据范围 $10^5$，我的想法是固定一个右端点，计算以它为结尾的区间们在当前位的运算结果是否有贡献。因为它前面的点的情况是已知的（前面已经扫描过），而固定左端点的话，后面的情况我们不知道，很难计算。     
对于一个数对全局的贡献，我没想到怎么做，可以在讨论区讨论。       

---
假设我们已经把当前的所有数位剥离出来，从左到右排成一列：$1,0,0,1,0$。      
下面我们举例子尝试摸索规律。       

|区间的结尾|区间包含的数|异或和|与和|或和|
|:-:|:-:|:-:|:-:|:-:|
|以位置 $1$ 结尾|$1$|$1$|$1$|$1$|
|以位置 $2$ 结尾|$10,0$|$1,0$|$0,0$|$1,0$|
|以位置 $3$ 结尾|$100,00,0$|$1,0,0$|$0,0,0$|$1,0,0$|
|以位置 $4$ 结尾|$1001,001,01,1$|$0,1,1,1$|$0,0,0,1$|$1,1,1,1$|
|以位置 $5$ 结尾|$10010,0010,010,10,0$|$0,1,1,1,0$|$0,0,0,0,0$|$1,1,1,1,0$|

我们可以依稀看到一些规律：
1. 对于异或和，如果当前位是 $1$，那么继承前面的结果的同时全部取反，最后加上自己的贡献 $1$；如果当前位是 $0$，那么直接继承前面的结果（自己没有贡献）。     
想象一下往一个区间后面加 $1$，异或和改变，加 $0$ 则不变。     
此时需要维护前面的贡献。
2. 对于与和，如果当前位是 $0$，那么贡献清零，否则继承前面的贡献并加上自己。
再举个例子，$00111$ 以最后一个 $1$ 的区间们的贡献分别为 $0,0,1,1,1$。     
此时需要维护最后一个 $0$ 的位置（它后面就是最后一段连续的 $1$，只是比较好维护而已）。
3. 对于或和，如果当前位是 $0$，那么继承前面的贡献（当前位没有贡献），否则因为当前位对每一个以它结尾的区间都有贡献，贡献会被拉满。        
此时需要维护最后一个 $1$ 的位置，它以及其前面的区间们都是有贡献的，而后面则没有（全是 $0$）。

---

这样每一位、每一个数扫一遍就可以得到全部答案。（记得乘上当前位的权值。）      
**但是！** 我们只得到了所有形如 $(l,r)(l \le r)$ 的点对所对应的区间！我们并没有计算 $(l,r)(l>r)$ 们的贡献！       
很简单，我们只需要把最终答案 $\times 2$ 就可以了。    
但这样一来我们又重复计算了 $(i,i)$ 们的贡献，显然，它们的贡献是数字本身，减去就可以了。     
最后除以 $n^2$（总点对个数）。     
诶对了记得开 long long。

```cpp
#include<stdio.h>
long long n,s[100005],summ,s1,s2,s3;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&s[i]),summ+=s[i];
	for(int j=0;j<=27;j++)//注意二进制位数的枚举，
    //我就是调试的时候改成了 2，然后 30pts 半天调不出来。
	{
		long long bef1=0,bef2=0,bef3=0;
		for(long long i=1;i<=n;i++)
		bef1=((s[i]>>j)&1)?i-bef1:bef1,s1+=bef1*(1ll<<j),
		s2+=(((s[i]>>j)&1)?i-bef2:0)*(1ll<<j),bef2=((s[i]>>j)&1)?bef2:i,
		bef3=((s[i]>>j)&1)?i:bef3,s3+=bef3*(1ll<<j);
	}s1=s1*2-summ,s3=s3*2-summ,s2=s2*2-summ;
	printf("%.3f %.3f %.3f",s1*1.0/n/n,s2*1.0/n/n,s3*1.0/n/n);
}
```

---

## 作者：Cyx20110930 (赞：2)

# 前言

这题唯二两篇题解都不能让我这个蒟蒻看懂，于是我自己写一篇专属我们蒟蒻的题解了！

# 题意简述

有一个长度为 $n$ 的数组，现在要随机取一段 $[l,r]$ 出来，算出这一段的期望 `xor` 值、期望 `and` 值、期望 `or` 值。即把这一段进行异或，与，或运算。

# Sol

本蒟蒻一共想出来三档分数段的解法：

## 20% 

$n\le100$ 易知应用 $O(n^3)$。

十分简单，枚举 $l,r$ 并 $O(n)$ 算出期望 `xor` 值、期望 `and` 值、期望 `or` 值就行了。

## 另 30%

全由 $0,1$ 构成是启发正解的一档部分分：

+ 要想对期望 `and` 值有贡献，只能在连续 `1` 区间里选段。

+ 要相对期望 `or` 值没有贡献，只能在连续 `0` 区间里选段。

那么，最难的期望 `xor` 值呢？

明显 dp 可做，设 $dp_i$ 为 $1$ 到 $i$ 内所有区间的期望 `xor` 值。则有转移方程 $dp_i=dp_{i-1}+res$，其中 $res$ 是一个增量。

来讲解一下：明显 $dp_i$ 比 $dp_{i-1}$ 多了 $a_1|a_2| ... |a_i + a_2|a_3| ... |a_i + ... + a_i$，$res$ 就是记录这个，又易得若 $a_i=1$ 则 $res = a_1|a_2| ... |a_i + a_2|a_3| ... |a_i + ... + a_i=a_i+(i- (a_1|a_2| ... |a_{i-1} + a_2|a_3| ... |a_{i-1} + ... + a_{i-1}))$； $a_i=0$ 则 $res$ 不变。

这样，我们就 $O(n)$ 算出来期望 `xor` 值、期望 `and` 值、期望 `or` 值了！

## 100%

$n\le 10^5$ 易得 $O(n)$，由前一档部分分可知，正解就是拆位用 60% 解法算答案，当然代码中有许多细节，要注意！（我一个蒟蒻在 CSP-S 模拟上这题 100->20 呜呜呜）

# Code

十年 OI 一场空，不开 long long 见祖宗！（int 会让你 100->20 血的教训！）

```
//三档分数都在里面咯
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, l, r) for (int i = l; i >= r; i--)
#define int long long
int a[100005], ejz[100005][32], dp[100005], dp2[100005][32];
double totxo = 0, totan = 0, toto = 0;
signed main() {
    //freopen("interval.in", "r", stdin);
    //freopen("interval.out", "w", stdout);
    int n;
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    if (n <= 100) {
        rep(i, 1, n) totxo += a[i], totan += a[i], toto += a[i];
        rep(i, 1, n) {
            rep(j, i + 1, n) {
                int xo = a[i], an = a[i], o = a[i];
                rep(k, i + 1, j) {
                    xo = xo ^ a[k];
                    an = an & a[k];
                    o = o | a[k];
                }
                totxo += 2 * xo, totan += 2 * an, toto += 2 * o;
                // cout<<xo<<' '<<an<<' '<<o<<endl<<totxo<<' '<<totan<<' '<<toto<<endl;
            }
        }
        cout << fixed << setprecision(3) << totxo / 1.0 / (n * n) << " " << totan / 1.0 / (n * n) << " "
             << toto / 1.0 / (n * n);
    } else {
        int fl = 1, sum = 0;
        rep(i, 1, n) {
            if (a[i] != 0 && a[i] != 1)
                fl = 0;
            sum += a[i];
        }
        if (fl) {
            int lst = a[1], l = 1, ans1 = n * n, ans2 = 0;
            for (int i = 2; i <= n; i++) {
                if (a[i] == lst)
                    l++;
                else {
                    if (lst == 0) {
                        ans1 -= l * l;
                    } else {
                        ans2 += l * l;
                    }
                    lst = a[i];
                    l = 1;
                }
            }
            if (lst == 0) {
                ans1 -= l * l;
            } else {
                ans2 += l * l;
            }
            // 10101011100011
            // 01100110100001 ans=6;
            // 101010111000110
            // 011001101000010 ans=6;
            // 101010111000111
            // 100110010111101 i=15;ans=i-ans;
            int res = 0;
            dp[1] = a[1];
            res = a[1];
            for (int i = 2; i <= n; i++) {
                if (a[i])
                    res = i - res;
                dp[i] = dp[i - 1] + res;
            }
            cout << fixed << setprecision(3) << (dp[n] * 2 - sum) / 1.0 / (n * n) << ' '
                 << ans2 / 1.0 / (n * n) << ' ' << ans1 / 1.0 / (n * n);
        } else {
            for (int i = 0; i <= 31; i++) {
                for (int j = 1; j <= n; j++) {
                    if ((1 << i) & a[j])
                        ejz[j][i] = 1;
                }
            }
            /*
            for(int j=1;j<=n;j++){
                    for(int i=0;i<=31;i++){
                            cout<<ejz[j][i];
                    }
                    cout<<endl;
            }*/
            int totan1 = 0, toto1 = 0, totxo1 = 0;
            for (int i = 0; i <= 31; i++) {
                int lst = ejz[1][i], l = 1, ans1 = n * n, ans2 = 0;
                for (int j = 2; j <= n; j++) {
                    if (ejz[j][i] == lst)
                        l++;
                    else {
                        if (lst == 0) {
                            ans1 -= l * l;
                        } else {
                            ans2 += l * l;
                        }
                        lst = ejz[j][i];
                        l = 1;
                    }
                }
                if (lst == 0) {
                    ans1 -= l * l;
                } else {
                    ans2 += l * l;
                }
                toto1 += ans1 << i;
                totan1 += ans2 << i;
                int res = 0;
                dp2[1][i] = ejz[1][i];
                res = ejz[1][i];
                // cout<<res<<' '<<dp2[1][i]<<endl;
                for (int j = 2; j <= n; j++) {
                    if (ejz[j][i])
                        res = j - res;
                    dp2[j][i] = dp2[j - 1][i] + res;
                    // cout<<res<<' '<<dp2[j][i]<<endl;
                }
                // cout<<endl;
                int sum1 = 0;
                for (int j = 1; j <= n; j++) {
                    sum1 += ejz[j][i];
                }
                totxo1 += (dp2[n][i] * 2 - sum1) << i;
            }
            cout << fixed << setprecision(3) << totxo1 / 1.0 / (n * n) << ' ' << totan1 / 1.0 / (n * n) << ' '
                 << toto1 / 1.0 / (n * n);
        }
    }
}
```

---

## 作者：Usstzqqch_Iroha (赞：0)

**来源：《算法竞赛进阶指南》，李煜东著，$\texttt{0x38}$**。

**原题：$\texttt{AcWing216}$。**

蒟蒻刚开始做的时候没看懂题解和小蓝皮。后来自己琢磨了一会自己就想通了（其实可能是书里的表述没太看懂），所以现在写一篇比较浅显的题解。

由于这可以算是数学期望的模板题，所以首先对于数学期望，我们来做一些解释。先来看前置知识。
* 随机事件 $A$：可能有多种结果的事件。
* 样本点：事件 $A$ 的某种可能结果。
* 样本空间 $\Omega$：指某随机事件 $A$ 的所有可能达成的状态（样本点）组成的集合。
* 概率 $P(A)$：指事件 $A$ 发生的结果个数占总结果个数（即样本空间）的比重。
* 随机变量 $X$：将样本点映射为实数的函数。我们讨论取值有限的离散型随机变量。

有了这些知识，我们来了解数学期望的定义。

> 若随机变量 $X$ 的取值有 $x1,x2...$，一个随机事件可表示成 $X=X_i$，其概率为 $P(X=X_i)=p_i$，则称 $E(x)=\Sigma p_ix_i$ 为随机变量 $X$ 的**数学期望**。*摘自《算法竞赛进阶指南》，李煜东著。*

说白了，数学期望就是带权求和，只是权值变成了事件发生的概率，这需要你自己求；而随机变量通常题目里面会给你求法或者定义。

譬如：本题当中给定了你随机变量 $X$ 的求法，即任意选定的区间 $[L,R]$ 中所有的 $N_i$ 的按位 $\text{xor,or,and}$ 和，而概率则需自己计算。

首先计算概率。根据题意，显然 $l<r$ 时会有一个 $r<l$ 的对称情况，$P(A)=\displaystyle \frac{1}{n}\times \displaystyle \frac{1}{n}\times 2 = \displaystyle \frac{2}{n^2}$ 。同理 $l=r$ 时 $P(A)=\displaystyle \frac{1}{n^2}$。

现在的问题就是处理区间内的位运算。显然采用前缀异或/与/或数组会达到 $O(n^2)$ 的时间复杂度，会爆。考虑到位运算不进位，我们可以将整数转换为二进制，按位进行计算，最后合并每一位的贡献即可。

有了这个思路，接下来就是分类讨论了。（然后挂了我很久）

首先我们设目前枚举到了$N_i$ 的第 $k$ 个二进制数位（从 $1$ 开始）为右边界，目前称之为 $B_i$（因为我们之后还要更新）。我们先对朴素的按位与和按位或进行讨论。

记该位之前数字 $g$ 最后一次出现过的位置为 $last[g]$，那么我们稍加思索可以推出以下结论：

1. 按位或：当 $B_i=1$ 时，对于任意的 $l\le r$，区间 $[l,r]$ 内的 $\text{or}$ 和的结果一定为 $1$。这是因为按位或“有 $1$ 全 $1$”的性质（即 $1\ \text{or}\ x = 1$）。此时将 $2^{k-1}\times P(A)\times (r-1)$ 累加到 $\text{or}$ 的答案中。
2. 按位与：当 $B_i=0$ 时，对于任意的 $l\le r$，区间 $[l,r]$ 内的 $\text{and}$ 和的结果一定为 $0$。这是因为按位与“有 $0$ 全 $0$”的性质（即 $0\ \text{and}\ x=0$）。此时对 $\text{and}$ 的答案什么都不做。
3. 当 $B_i=0$ 时，将 $2^{k-1}\times P(A)\times last[1]$ 累加到 $\text{or}$ 的答案中（如果出现过 $1$ 的话）。
4. 当 $B_i=1$ 时，将 $2^{k-1}\times P(A)\times (k-last[0]-1)$ 累加到 $\text{and}$ 的答案中（如果出现过 $0$ 的话）。

接下来我们开始讨论 $\text{xor}$ 的情况。

我们知道 $\text{xor}$ 运算和其它运算都不太一样。 $\text{xor}$ 运算不仅仅和当前数位有关，它和前面的所有数位 $\text{xor}$ 的结果也有关系。所以我们可以开两个变量 $c_0$、$c_1$ 来记录所有的 $l$ 的个数，分别满足 $ \text{xor}^{k-1}_{i=l} B_i=0$ 和 $ \text{xor}^{k-1}_{i=l} B_i=1$。那么当 $B_i=0$ 时，将 $2^{k-1}\times P(A)\times c_1$ 累加到答案中，反之将 $2^{k-1}\times P(A)\times c_0$ 累加到答案中，并需要将 $c_0$ 和 $c_1$ 进行交换（因为原来 $[l,k-1]$ 的 $\text{xor}$ 结果为 $0$，$\text{xor}\ 1$ 运算过后结果变成了 $1$，而原来 $c_1$ 对应的区间 $\text{xor}$ 的结果就变成了 $0$）。注意我们需要在交换之前 $c_0\gets c_0+1$ 来更新之后的 $c_1$。

代码其实写出来也差不多，但还是粘上来吧。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5 + 5;
int n;
int N[maxn];
int pre_xor[maxn],pre_and[maxn],pre_or[maxn];
int /*B[maxn],*/last[2];//开一个B变量就够了
double ans_xor,ans_and,ans_or;
int maxk = -1,len;
/*int calc(int x){
	int y=x;
	len = 0;
	while(y){
		y>>=1;
		len++;
	}
	return len;
}*/
//试图计算最大位数发现没有必要 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>N[i];
	}
	/*for(int i=1;i<=n;i++){
		maxk = max(maxk,calc(N[i]));
	}*/
  //调试代码
	int c1,c2;
    for(int k=0;k<=30;k++){//这里是从第0位开始的
    	last[0]=0;
    	last[1]=0;
    	c1=0;
    	c2=0;
    	for(int i=1;i<=n;i++){
    		int B = (N[i]>>k)&1;
    		double ret = (double)(1<<k)/(n*n);
    		if(B==0){
    			ans_and+=ret+2.0*ret*(i-last[0]-1);
    			ans_or+=ret+2.0*ret*(i-1);
    			ans_xor+=ret+2.0*ret*c1;
			}
			else{
				ans_or+=2.0*ret*last[1];
				ans_xor+=2.0*ret*c2;
			}//按上面的结论模拟
			last[B]=i;
			c1++;
			if(B) swap(c1,c2);
		}
	}
	printf("%.3f %.3f %.3f",ans_xor,ans_and,ans_or);
}
```
# **一些提醒**

1. 注意浮点数类型不要开 $\texttt{long double}$。因为你会发现你的程序除了 $0.000$ 什么都不输出。~~是的我第一遍就挂在这里~~ 
2. 涉及乘法，记得开 $\texttt{long long}$。否则你会由 $40\gets 100$，这很不好笑。[实例](https://www.luogu.com.cn/record/232263564)。

---

## 作者：bianshiyang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10500)

提供一种异或期望部分更好理解的写法。

# 分析
首先观察到这三种运算都有不进位的特点，于是可以一位一位单独进行考虑，最后把每一位的期望加起来即可。考虑每一位时，每个数字都只取其在该二进制位下的数字进行运算，这样子参与运算的数字就只有 $0$ 和 $1$ 了，题目本质变成求出有多少个区间满足该区间内的所有数做对应运算后为 $1$，称满足此条件的区间为合法区间。

一个很套路的想法就是枚举区间的右端点，统计有多少个左端点满足条件，注意若左右端点不同需要统计两次。假设现在考虑到了第 $k$ 位且右端点枚举到了 $r$。

## and
区间合法的条件即区间内所有数均为 $1$，可以使用变量记录上一个 $0$ 出现的位置 $\operatorname{last}_0$，那么 $[\operatorname{last}_0+1,r]$ 都可以作为左端点。当 $r$ 位置上的数为 $1$ 时，贡献为 $2^k(\frac{1}{n^2}+\frac{2}{n^2}(r-\operatorname{last}_0-1))$，否则不产生贡献。

## or
区间合法的条件即区间内存在 $1$ 即可，仍然可以使用变量记录上一个 $1$ 出现的位置 $\operatorname{last}_1$，那么 $[1,\operatorname{last}_1]$ 都可以作为左端点。当 $r$ 位置上的数为 $1$ 时（此时 $\operatorname{last}_1=r$），贡献为 $2^k(\frac{1}{n^2}+\frac{2}{n^2}(r-1))$，否则贡献为 $2^k\cdot \frac{2}{n^2}\cdot \operatorname{last}_1$。

## xor
记 $s_i$ 表示位置 $1\sim i$ 上的数异或的结果，其实就是异或前缀和，此时所有满足 $(s_{l-1} \operatorname{xor} s_r=1)\wedge (l\le r)$ 的 $l$ 可作为区间左端点。为了满足 $l=r$ 的区间只统计一次可以采用下面两种解决方案：

方案一：先只统计满足 $(s_{l-1} \operatorname{xor} s_r=1)\wedge (l<r)$ 的贡献，若 $s_{r-1} \operatorname{xor} s_r=1$，则再加上这部分贡献。

方案二：直接加上满足 $(s_{l-1} \operatorname{xor} s_r=1)\wedge (l\le r)$ 的贡献，若 $s_{r-1} \operatorname{xor} s_r=1$，则再减去这部分多算的贡献。

两种方案都好实现，以第二种方案为例，我们维护两个变量 $c_0$ 和 $c_1$，分别表示满足 $(s_{l-1} =0)\wedge (l\le r)$ 的 $l$ 的数量和 $(s_{l-1} =1)\wedge (l\le r)$ 的数量。当 $s_r=0$ 时，贡献为 $2^k\cdot \frac{2}{n^2}\cdot c_1$，否则贡献为 $2^k\cdot \frac{2}{n^2}\cdot c_0$，要注意当 $r$ 位置上的数为 $1$ 时，应该减去 $2^k\cdot \frac{1}{n^2}$。

# 代码实现
```cpp
#include<bits/stdc++.h>
#define double long double
using namespace std;
const int N=1e5+100;
int n,a[N],s,c0,c1,lst[2];
double ans1,ans2,ans3,p1,p2;

void XOR(int x,int k,int op)
{
	if(s) ans1+=(double)p2*(1<<k)*c0;
	else ans1+=(double)p2*(1<<k)*c1;
	if(op) ans1-=(double)p1*(1<<k);
}

void AND(int x,int k,int op)
{
	if(op) ans2+=(double)p1*(1<<k)+p2*(1<<k)*(x-lst[0]-1);
}

void OR(int x,int k,int op)
{
	if(op) ans3+=(double)p1*(1<<k)+p2*(1<<k)*(x-1);
	else ans3+=(double)p2*(1<<k)*lst[1];
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	p1=(double)1.0/n/n;p2=(double)2.0*p1;//l=r和l<r的概率
	for(int j=30;j>=0;j--)
	{
		lst[0]=lst[1]=0;//lst[i]表示i上一次出现的位置
		c0=1,c1=0,s=0;//s是前缀和
		for(int i=1;i<=n;i++)
		{
			int op=(a[i]>>j)&1;
			s^=op;
			XOR(i,j,op);AND(i,j,op);OR(i,j,op);
			lst[op]=i;
			if(s) c1++;
			else c0++;//先算再统计
		}
	}
	printf("%.3Lf %.3Lf %.3Lf\n",ans1,ans2,ans3);
	return 0;
}
```

---

## 作者：huhangqi (赞：0)

求位运算的期望，很常见的思路是计算出每一位的期望。

那么直接分开处理，异或的答案我们可以通过异或一个数两次相当于抵消了的特性，直接得到有多少种可行的情况。

而取并则需要这一段全都是 $1$，那么直接处理前面连续的 $1$ 的数量即可。

取或与上一步类似，我们将全部都是 $0$ 的情况减掉，那么剩下来的就是为 $1$ 的情况。

最后即可直接计算得到。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	double ans1=0,ans2=0,ans3=0;
	for(int i=0;i<=30;i++){
		int cnt0=0,cnt1=0,l=0,sum=0;
		for(int j=1;j<=n;j++){
			if((a[j]>>i)&1)sum++;
			int la=l;
			l^=((a[j]>>i)&1);
			if(l)sum+=cnt0*2;
			else sum+=cnt1*2;
			if(la)cnt1++;
			else cnt0++;
		}
		ans1+=1.0*sum*(1<<i)/n/n;
		l=sum=0;
		for(int j=1;j<=n;j++){
			int tmp=((a[j]>>i)&1);
			if(!tmp){
				l=0;
				continue;
			}
			else {
				sum+=2*l+1;
				l++;
			}
		}
		ans2+=1.0*sum*(1<<i)/n/n;
		l=0,sum=n*n;
		for(int j=1;j<=n;j++){
			int tmp=((a[j]>>i)&1);
			if(tmp){
				l=0;
				continue;
			}
			else {
				sum-=2*l+1;
				l++;
			}
		}
		ans3+=1.0*sum*(1<<i)/n/n;
	}
	printf("%.3lf %.3lf %.3lf",ans1,ans2,ans3);
	return 0;
}

``````

---

## 作者：lzdll (赞：0)

## 转化题意

拿到题目就看到了数学期望，但是分析后发现其实就是算出所有区间每个数按位与、按位或、按位异或和。

值得注意的是，他是等概率的选取左右端点，如果 $l>r$ 他就会交换，所以长度大于一的区间贡献应该乘二。

由于是在比赛中做的题，我将不是很详细地简要分析从部分分到正解的过程和可能导致挂分的原因。

## 20

$n$ 才 $100$，枚举区间左右端点然后算，复杂度为 $O(n^3)$ 就不展示代码了。

## 40

这个时候 $O(n^3)$ 肯定过不去了，但是 $O(n^2)$ 可以过去，突然想到区间 DP 的时候做的操作，用小区间推大区间。

```cpp
if(n<=1000) {
	double ans1,ans2,ans3;
	for(int i=1; i<=n; ++i) {
		dp[i][i][0]=dp[i][i][1]=dp[i][i][2]=a[i];
	}
	for(int len=2; len<=n; ++len) {
		for(int l=1; l+len-1<=n; ++l) {
			int r=l+len-1;
			dp[l][r][0]=dp[l+1][r][0]^a[l];
			dp[l][r][1]=dp[l+1][r][1]&a[l];
			dp[l][r][2]=dp[l+1][r][2]|a[l];
			ans1+=dp[l][r][0]*2.0/n/n;
			ans2+=dp[l][r][1]*2.0/n/n;
			ans3+=dp[l][r][2]*2.0/n/n;
		}
	}
	printf("%.3lf %.3lf %.3lf\n",ans1,ans2,ans3);
	ans1=ans2=ans3=0;
	return 0;
}

```
其中 $ans1$、$ans2$、$ans3$ 分别代表异或、与、或的答案，先加起来最后除。与 $dp$ 数组第三维下标 $0$，$1$，$2$ 分别对应，一开始 $ans$ 提前加上长度为 $1$ 的区间的值，后面 $len$ 从 $2$ 开始。

## 70

70分的特殊条件：$N$ 个数为 $0$ 或 $1$。

这已经非常接近正解了。

这个时候我们要按位考虑，如果我们从 $1$ 到 $n$ 枚举以每一位为结尾，他的贡献就操作后能够形成结果是 $1$ 的区间的数量的两倍（前面说过了），区间长度为 $1$ 的仍然预处理。

先考虑异或，异或是一种奇特的操作，怎么样可以让结果为 $1$？$1$ 个数为奇数就行。考虑每一个 $1$ 他前面肯定跟若干个 $0$（可能是 $0$ 个），把每个 $1$ 和这若干个 $0$ 分成一组，之后能当左端点的区间肯定是隔一个取一个的。


![](https://cdn.luogu.com.cn/upload/image_hosting/gaooed19.png?x-oss-process=image/resize,m_lfit,h_500,w_1000)

比如说我们现在到了这个黄色的 $1$，能贡献的就是红色部分的长度。当考虑到了一后面的 $0$，贡献就变成了红色加黄色的长度。

我们用 $g$ 数组记录长度，$l$ 表示要加的话加哪一个。

```cpp
//这一位是1
ans1+=g[l];
g[l]++;
l^=1;
```
注意这里 $l$ 要在 $g$ 数组加了之后再变。

```cpp
//这一位是0
ans1+=g[l^1];
g[l]++;
```
这为啥要 $l$ 异或 $1$，因为上一次碰见 $1$ 的时候 $l$ 已经变化了，但还是要加原来的。

现在考虑与和或，都很简单。因为只要有一个 $1$，或结果就是 $1$，按位与与正好相反，让 $lst_i$ 为 $i$（$0$ 或 $1$）。

这样如果这一位是 $1$。

```cpp
ans2+=i-1-lst[0];//到左边第一个0之前都行
ans3+=i-1;//这一位已经是一了，前面的都行
```

否则

```cpp
ans3+=lst[1];//左端点必须在从开头到从左往右最后一个1之间

//这一位已经是0所以按位与结果一定是0，不用管
```

每次循环一次后，更新 $lst$ 的值即可。

## 正解

前面的做出来后正解就很简单了，只需把 $a_i$ 按位拆开，假设这是第 $j$ 位，每一次算的时候乘上 $2^{j-1}$ 就好了。


```cpp
#include<bits/stdc++.h>
#define R(x) x=read()
#define int long long
#define N 100005
using namespace std;
inline int read() {
	int x=0,y=1;
	char e=getchar();
	while(e<'0'||e>'9') {
		if(e=='-')y=-1;
		e=getchar();
	}
	while(e>='0'&&e<='9') {
		x=(x<<1)+(x<<3)+(e-'0');
		e=getchar();
	}
	return x*y;
}
int n,a[N];
bool f[N][35];
int mx;
int dp[1005][1005][3];
int ans1,ans2,ans3;
main() {
	R(n);
	for(int i=1; i<=n; ++i) {
		R(a[i]);
		int t=a[i],j=0;
		while(t) {
			f[i][++j]=t&1;
			t>>=1;
		}
		mx=max(mx,j);
	}
	int lst[2],g[2],l;
	for(int j=1; j<=mx; ++j) {
		lst[0]=lst[1]=g[0]=g[1]=0,l=0;
		for(int i=1; i<=n; ++i) {
			if(f[i][j]==1) {
				ans1+=g[l]*(1ll<<(j-1));
				g[l]++;
				l^=1;
				ans2+=(i-1-lst[0])*(1ll<<(j-1));
				ans3+=(i-1)*(1ll<<(j-1));
			} else {
				ans1+=g[l^1]*(1ll<<(j-1));
				g[l]++;
				ans3+=lst[1]*(1ll<<(j-1));
			}
			lst[f[i][j]]=i;
		}
	}
	ans1<<=1;
	ans2<<=1;
	ans3<<=1;
	for(int i=1; i<=n; ++i) {
		ans1+=a[i];
		ans2+=a[i];
		ans3+=a[i];
	}
	printf("%.3lf %.3lf %.3lf\n",(double)ans1/(n*n),(double)ans2/(n*n),(double)ans3/(n*n));
	return 0;
}
```

## 进食后人

$ans$ 一定不要用浮点，加的时候用整形的（否则精度不对)

我赛时用的浮点导致挂了30。

警钟吃掉。

---

## 作者：Erica_N_Contina (赞：0)

我们对每一位拆开考虑。

假设当前考虑到了 $a_x$ 的第 $i$ 位，我们记为 $cur$（值为 $1$ 或者 $0$）。我们只考虑将 $x$ 作为右端点的情况。使用**期望的定义**。

对于不同的区间，其出现的概率分为以下两种：

- $l=r$ 的区间出现的概率为 $\frac{1}{n^2}$。

- $l≠r$ 的区间出现的概率为 $\frac{2}{n^2}$。

我们记 $pre1$ 为上一个 $1$ 的下标，$pre0$ 同理。

下面我们来分类讨论：

- xor

  xor 的情况最为复杂。
我们要记录 $c0$ 为 $[1,x]$ 中使得区间 $[l,x]$ 的 xor 为 $0$ 的 $l$ 的个数。$c1$ 同理。
如果 $cur=1$，左端点可以为 $c0$。那么概率就是 $c0\times \frac{2}{n^2}$，期望的话再乘上一个 `cur<<i` 即可。交换 $c1,c0$。
如果 $cur=0$，左端点可以为 $c1$。那么概率就是 $c1\times  \frac{2}{n^2}$，期望的话再乘上一个 `cur<<i` 即可。
最后，若 $cur=0$，则 `c0++`，否则 `c1++`。

- and

  如果 $cur=1$，左端点可以为 $[pre0+1,x]$。那么概率就是 $ \frac{1}{n^2}+(pre0-x-1)\times  \frac{2}{n^2}$，期望的话再乘上一个 `cur<<i` 即可。

  如果 $cur=0$，无贡献。

- or

  如果 $cur=1$，左端点可以为 $[1,x]$。那么概率就是 $ \frac{1}{n^2}+(x-1)\times  \frac{2}{n^2}$，期望的话再乘上一个 `cur<<i` 即可。

  如果 $cur=0$，左端点可以为 $[1,pre1]$。那么概率就是 $pre1\times \frac{2}{n^2}$，期望的话再乘上一个 `cur<<i` 即可。


```C++
/*
                      Keyblinds Guide
                                ###################
      @Ntsc 2024

      - Ctrl+Alt+G then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'

*/
#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define rep(i, l, r) for (int i = l, END##i = r; i <= END##i; ++i)
#define per(i, r, l) for (int i = r, END##i = l; i >= END##i; --i)
#define pb push_back
#define mp make_pair
#define int long long
#define pii pair<int, int>
#define ps second
#define pf first
#define ull unsigned long long

#define itn int
// #define inr int
// #define mian main
// #define iont int

#define rd read()
int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
void write(int out) {
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}

#define ell dbg('\n')
const char el = '\n';
const bool enable_dbg = 1;
template <typename T, typename... Args>
void dbg(T s, Args... args) {
    if constexpr (enable_dbg) {
        if (1)
            cerr << ' ';
        cerr << s;
        if constexpr (sizeof...(Args))
            dbg(args...);
    }
}

#define zerol = 1
#ifdef zerol
#define cdbg(x...)            \
    do {                      \
        cerr << #x << " -> "; \
        err(x);               \
    } while (0)
void err() { cerr << endl; }
template <template <typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) {
    for (auto v : a) cerr << v << ' ';
    err(x...);
}
template <typename T, typename... A>
void err(T a, A... x) {
    cerr << a << ' ';
    err(x...);
}
#else
#define dbg(...)
#endif

const int N = 3e5 + 5;
const int INF = 1e18;
const int M = 1e7;
const int MOD = 1e9 + 7;

/*
我们对每一位拆开考虑：
假设当前考虑到了aq_x的第i位，我们记为cur(1/0)。我们只考虑将x作为右端点的情况。使用期望的定义
对于不同的区间，其出现的概率分为以下两种：
- l=r   1/n^2
- l!=r  2/n^2
下面我们来分类讨论：
我们记pre1为上一个1的下标，pre0同理
- xor
xor的情况最为复杂
我们要记录c0为[1,x]中使得区间[l,x]的xor为0的l的个数。c1同理。
如果cur=1，左端点可以为c0。那么概率就是c0*2/n^2，期望的话再乘上一个cur<<i即可。交换c1,c0
如果cur=0，左端点可以为c1。那么概率就是c1*2/n^2，期望的话再乘上一个cur<<i即可。
最后，若cur=0，则c0++，否则c1++
- and
如果cur=1，左端点可以为[pre0+1,x]。那么概率就是1/n^2+(pre0-x-1)*2/n^2，期望的话再乘上一个cur<<i即可。
如果cur=0，无贡献
- or
如果cur=1，左端点可以为[1,x]。那么概率就是1/n^2+(x-1)*2/n^2，期望的话再乘上一个cur<<i即可。
如果cur=0，左端点可以为[1,pre1]。那么概率就是(pre1)*2/n^2，期望的话再乘上一个cur<<i即可。


*/

itn pre[3];
int a[N];
double ansxor, ansor, ansand;

void solve() {
    int n = rd;
    for (int i = 1; i <= n; i++) {
        a[i] = rd;
    }

    for (itn i = 0; i < 31; i++) {
        pre[0] = pre[1] = 0;

        int c0 = 0, c1 = 0;

        for (int j = 1; j <= n; j++) {
            itn cur = (a[j] >> i) & 1;
            double res = 1. * (1 << i) / (n * n);
            //			cdbg(res);
            if (cur) {
                ansxor += res + 2. * res * c0;
                ansand += res + 2. * res * (j - pre[0] - 1);
                ansor += res + 2. * (res * (j - 1));
            } else {
                ansxor += 2. * res * c1;
                ansor += 2. * (res * pre[1]);
            }

            pre[cur] = j;
            c0++;
            if (cur)
                swap(c0, c1);
        }
    }

    printf("%.3lf %.3lf %.3lf\n", ansxor, ansand, ansor);
}

signed main() {
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);

    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：dengjunhaodejia09 (赞：0)

这是一道套了期望的题。

首先我们分别考虑询问。

对于异或，我们可以先异或前缀和，区间异或可以通过两个位置不同的数的异或前缀和得到。我们依次考虑每一位，然后对于每一位求出异或前缀和在这一位上为一的个数与为零的个数，然后一找零统计，零找一统计。

对于与操作，我们一次考虑每一位，然后快速求出在每一个数前在这一个二进制位下离他最近的这一位为零的数，然后统计答案。

对于或操作我们和与操作差不多，只是改为快速找到在每个数前的在当前考虑的这个二进制位上为一的数，然后换一种方式统计答案。

我的题解讲了答题思路，而细节要大家自己补充，我认为这才是有收获的。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
long double ans_daan;
int a[1919810],sum[1919810];
int n;
void get1(){
	for(int i=0;i<=30;i++){
		int ans=1,anss=0;
		for(int j=1;j<=n;j++){
			sum[j]=sum[j-1]^((a[j]&(1<<i))>>i);
			ans+=(sum[j]==0);
			anss+=(sum[j]==1); 
		}
		for(int j=0;j<=n;j++){
			if(sum[j]==0){
				ans_daan+=anss*(1<<i)*1.0/n/n;
			}else{
				ans_daan+=ans*(1<<i)*1.0/n/n;
			}
		}
//		cout<<i<<' '<<ans_daan<<' '<<ans<<' '<<anss<<endl;
	}
	for(int i=1;i<=n;i++){
		ans_daan-=a[i]*1.0/n/n;
	}
	printf("%.3Lf ",ans_daan);
}
void get2(){
	ans_daan=0;
	for(int i=0;i<=30;i++){
		int lst=0;
		for(int j=1;j<=n;j++){
			sum[j]=((a[j]&(1<<i))>>i);
			if(sum[j]==0){
				lst=j;
			}
			ans_daan+=2*(j-lst)*(1<<i)*1.0/n/n;
		}
		for(int j=1;j<=n;j++){
			ans_daan-=sum[j]*(1<<i)*1.0/n/n;
		} 
	}
	printf("%.3Lf ",ans_daan);
}
void get3(){
	ans_daan=0;
	for(int i=0;i<=30;i++){
		int lst=0;
		for(int j=1;j<=n;j++){
			sum[j]=((a[j]&(1<<i))>>i);
			if(sum[j]==1){
				lst=j;
			}
			ans_daan+=2*lst*(1<<i)*1.0/n/n;
		}
		for(int j=1;j<=n;j++){
			ans_daan-=sum[j]*(1<<i)*1.0/n/n;
		} 
	}
	printf("%.3Lf ",ans_daan);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	get1();
	get2();
	get3();
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

没有题解，我来瞎说一下。

我们先考虑 $l < r$。显然，此时每个序列出现的概率相等。因此关键在需要求出 $\forall 1 \le l < r \le n$，从 $l$ 到 $r$ 的异或和的和 / 或和的和 / 与和的和。

以异或和为例。一个显然的思路是，固定序列的右端点 $r$，枚举左端点 $l$。那么右端点为 $r$ 的序列的异或和的和就是 $a_1 \oplus a_r + a_2 \oplus a_r + \cdots + a_{r - 1} \oplus a_r$。


很遗憾，异或与加法之间没有分配关系，因此不能把 $a_r$ 提出来。

可以考虑拆位。对于二进制下的第 $i$ 位，若 $a_r$ 该位为 $1$，则只需要求出 $r$ 前面第 $i$ 位为 $0$ 的数的个数。反之只需要求出 $r$ 前面第 $i$ 位为 $1$ 的数的个数。复杂度 $O(n \log V)$。

对于 $l > r$ 的情况是对称的。对于 $l = r$ 的情况可以特殊处理。对于与和或的做法相同。

---

