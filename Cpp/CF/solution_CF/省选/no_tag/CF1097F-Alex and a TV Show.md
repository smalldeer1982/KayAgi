# Alex and a TV Show

## 题目描述

Alex 决定试试自己的电视节目运气。他曾经参加过一个名为“What's That Word?!”的知识竞赛。在完美回答了“在互联网中，化名通常被称为什么？”（“呃……昵称？”）、“磁场强度的单位是以哪位著名发明家命名的？”（“呃……Nikola Tesla？”）以及“哪支摇滚乐队演唱了《How You Remind Me》？”（“呃……Nickelback？”）这些问题后，他决定报名参加一个更有难度的电视节目：“What's in This Multiset?!”

这个节目的规则如下：有 $n$ 个多重集，编号从 $1$ 到 $n$。每个多重集初始时都是空的。接下来会发生 $q$ 个事件，每个事件属于以下四种类型之一：

- 1 x v —— 将第 $x$ 个多重集设置为只包含 $v$ 的单元素多重集 $\{v\}$。
- 2 x y z —— 将第 $x$ 个多重集设置为第 $y$ 个和第 $z$ 个多重集的并集。例如：$\{1, 3\} \cup \{1, 4, 4\} = \{1, 1, 3, 4, 4\}$。
- 3 x y z —— 将第 $x$ 个多重集设置为第 $y$ 个和第 $z$ 个多重集的积。两个多重集 $A$ 和 $B$ 的积 $A \times B$ 定义为 $\{\gcd(a, b) \mid a \in A,\, b \in B\}$，其中 $\gcd(p, q)$ 表示 $p$ 和 $q$ 的最大公约数。例如：$\{2, 2, 3\} \times \{1, 4, 6\} = \{1, 2, 2, 1, 2, 2, 1, 1, 3\}$。
- 4 x v —— 询问第 $x$ 个多重集中数字 $v$ 出现了多少次。由于之前的节目太难，现在参赛者只需要给出答案对 $2$ 取模后的结果即可。

注意，上述的 $x$、$y$ 和 $z$ 不一定互不相同。在第 $2$ 和第 $3$ 种事件中，先计算并集或积，然后再赋值。

Alex 被节目的复杂规则搞糊涂了。你能帮他回答所有第 $4$ 类事件的询问吗？

## 说明/提示

以下是示例测试中每次事件后多重集的状态；$i$ 表示已经处理的询问数量：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1097F/bb0eac849013dab5244df53f599116382077f937.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 13
1 1 1
1 2 4
1 3 6
4 4 4
1 4 4
2 2 1 2
2 3 3 4
4 4 4
3 2 2 3
4 2 1
4 2 2
4 2 3
4 2 4
```

### 输出

```
010101
```

# 题解

## 作者：9AC8E2 (赞：16)

值域很小,并且求的是个数 $\mod 2$ 的值,显然使用`bitset`维护每个值出现次数 $\mod 2$ 的值

设 $val_{A,i}$表示可重集 $A$ 中 $i$ 的出现次数 $\mod 2$ 的值

对于操作 $1,2,4$,直接做即可.

对于操作 $3$,要求令 $A$ 为 $B,C$ 的积,即 $\forall i,val_{A,i}\equiv \sum_j\sum_kval_{B,j}\times val_{C,k}[\gcd(j,k)=i]\mod 2$

emmmm,这样似乎没法做

看到有关 $\gcd$,不妨考虑反演.

设 $f_{A,i}=\sum_{i|j}val_{A,j}$

那么有 $val_{A,i}=\sum_{i|j}f_{A,j}\mu(\frac{j}{i})$

所以只要维护 $f$ 和 $\mu$ 也能做

## 操作1
预处理,直接赋值即可
## 操作2
$$\forall i,f_{A,i}=f_{B,i}{\color{red}{xor}}f_{C_i}$$
## 操作3
$$\forall i,f_{A,i}\equiv \sum_j\sum_kval_{B,j}\times val_{C,k}[i|\gcd(j,k)]\mod 2$$
$$\equiv \sum_jval_{B,j}[i|j]\times\sum_k val_{C,k}[i|k]\mod 2$$
$$\equiv f_{B,i}\times f_{C,i}\mod 2$$
$$=f_{B,i}{\color{red}{and}}f_{C,i}$$
## 操作4
$$val_{A,i}\equiv \sum_{i|j}f_{A,j}\mu(\frac{j}{i})\mod 2$$

不妨预处理 $g_{i,j}\equiv \left\{\begin{aligned}\mu(\frac{j}{i})&&&i|j\\0&&&otherwise\end{aligned}\right.\mod 2$

$$val_{A,i}\equiv \sum_jf_{A,j}\times g_{i,j}\mod 2$$

${\color{red}{and}}$ 之后使用 `count()`就好了

---

## 作者：FjswYuzu (赞：9)

考虑到答案向 $2$ 取模，并且值域较小，集合中存在两个一样的数就可以消去，类似于异或。需要想一些另类的办法。

记 $S_i$ 表示 $S$ 集合里是否存在 $i$ 这个数。再记 $\displaystyle f(S,i) = \sum_{d=1} S_{id}$，这个东西的意义即为 $S$ 集合里面为 $d$ 的倍数的数的个数。

然后考虑几个操作。

第一个操作可以直接赋值。第二个是可重集并，相当于异或。

第三个操作比较迷惑，我们先求出 $S = A \times B$ 的每一位。

$$
\begin{aligned}
S_i 
&= \sum_{j} \sum_{k} [\gcd(j,k) = i] a_jb_k \\
&= \sum_{j} \sum_{k} [\gcd(j,k) = 1] a_{ij}b_{jk} \\
&= \sum_{j} \sum_{k} a_{ij} b_{jk} \sum_{d|\gcd(i,j)} \mu(d) \\
&= \sum_{d} \mu(d) \sum_{j} a_{ijd} \sum_{k} b_{ikd} \\
&= \sum_{d} \mu(d) f(A,id) f(B,id)
\end{aligned}
$$

推到这里差不多告一段落，可以发现 $S_i$ 没法快速维护并算出。我们考虑算 $f(S,i)$。

显然 $\displaystyle f(S,i) = \sum_{d} S_d$，所以有：

$$
\begin{aligned}
f(S,i)
&= \sum_{i|p} \sum_{d=1} \mu(d) f(A,pd) f(B,pd) \\
&= \sum_{p=1} f(A,pi) f(B,pi) \sum_{d|p} \mu(d) \\
&= \sum_{p=1} f(A,pi) f(B,pi) [p=1] \\
&= f(A,i) f(B,i)
\end{aligned}
$$

这个东西看起来就赏心悦目多了，两东西对位相乘在模 $2$ 意义下相当于 $\operatorname{and}$ 运算。

到这里已经不难想到用 `bitset` 去维护 $f$ 了。

最后考虑怎么处理操作四。注意到要求 $\displaystyle S_v = \sum_{d} \mu(d) f(S,dv)$。不可能对每个 $v,d$ 都处理，那么考虑优化掉这个东西。我们构造一个 $M(v)$ 使得 $M(v) \times f(S) \bmod 2 = S_v$。有一个显然的方法是 $M(v,dv) = \mu(d)$，那么又变成相乘算 $1$ 的个数，用了 `bitset` 就很好处理。

时间复杂度 $O(V \ln V + \frac{mV}{\omega})$，其中 $V$ 为值域，$\omega = 64$ 或 $32$。

```cpp
int cnt,prime[7005],mu[7005];
bool vis[7005];
bitset<7005> B[100005],F[7005],M[7005];
void hisa(int up)
{
	vis[mu[1]=1]=true;
	for(int i=2;i<=up;++i)
	{
		if(!vis[i])	prime[++cnt]=i,mu[i]=1;
		for(int j=1;j<=cnt && prime[j]*i<=up;++j)
		{
			vis[prime[j]*i]=true;
			if(i%prime[j]==0)	break;
			mu[prime[j]*i]=mu[i];
		}
	}
}
int n,m;
int main(){
	hisa(7000);
	for(int i=1;i<=7000;++i)	for(int j=1;j*i<=7000;++j)	F[j*i][i]=1;
	for(int i=1;i<=7000;++i)	for(int j=1;j*i<=7000;++j)	M[i][j*i]=mu[j];
	n=read(),m=read();
	while(m-->0)
	{
		int op=read(),x=read();
		if(op==1)	B[x]=F[read()];
		else if(op==2)	B[x]=B[read()]^B[read()];
		else if(op==3)	B[x]=B[read()]&B[read()];
		else	putchar('0'+((B[x]&M[read()]).count()&1));
	}
	return 0;
}
```

---

## 作者：Nemlit (赞：9)

妙妙题……

这道题这要求%2的个数，肯定有什么性质

~~于是我们想到了用$bitset$来处理~~

由于三操作有$gcd$，~~于是我们又想到用反演来解决~~

我们回忆一下反演的柿子

设$f(x)$为x出现了多少次，$F(x)$为x的倍数出现了多少次

$$F(d) = \sum_{d|x}f(x)$$

跟据反演，我们有：

$$f(x) = \sum_{x |d}F(d) * \mu(\frac{d}{x})$$

我们要求的数即为$f(v)$

由于$\mu$的取值只有$-1, 0, 1$，在膜二意义下只有$0, 1$

我们用$a[x][y]$表示$x$集合内的y即y的倍数出现了多少次（$F(y)$），再用$u[x][y]$表示$\mu(\frac{y}{x})$，我们要求的$f(v) = a[x]\&u[v]$

再来重新考虑所有操作：

对于1操作，预处理出每一个v的所有约数的$bitset$，赋值即可

对于2操作，直接用$a[x]=a[y]^a[z]$即可

对于3操作，$a[x] = a[y]\&a[z]$

对于4操作，用上述方法求出$bitset$后的$1$的数量
## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i, s, t) for(re int i = s; i <= t; ++ i)
#define maxn 7001
#define maxm 100005
int n, m, prim[maxn], vis[maxn], mu[maxn], cnt;
bitset<maxn>G[maxn], a[maxm], u[maxn];
int main() {
	n = read(), m = read(), mu[1] = 1;
	rep(i, 2, 7000) {
		if(!vis[i]) prim[++ cnt] = i, mu[i] = -1;
		for(re int j = 1; j <= cnt && prim[j] * i <= 7000; ++ j) {
			vis[i * prim[j]] = 1;
			if(i % prim[j] == 0) break;
			mu[i * prim[j]] = -mu[i];
		}
	}
	rep(i, 1, 7000) {
		for(re int j = i; j <= 7000; j += i) G[j][i] = 1, u[i][j] = mu[j / i] != 0;
	}
	while(m --) {
		int opt = read(), x = read();
		if(opt == 1) a[x] = G[read()];
		if(opt == 2) a[x] = a[read()] ^ a[read()];
		if(opt == 3) a[x] = a[read()] & a[read()];
		if(opt == 4) printf("%d", (u[read()] & a[x]).count() & 1);
	}
	return 0;
}
```

---

## 作者：igAC (赞：3)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1097F)

[CFlink](https://codeforces.com/problemset/problem/1097/F)

简要题意：

原题意就很简要了。

维护 $n$ 个初始为空的可重集，支持以下操作：

`1 x v`：令集合 $x$ 等于 $\{v\}$。

`2 x y z`：令集合 $x$ 等于集合 $y$ 与 $z$ 的并。

`3 x y z`：令集合 $x$ 等于集合 $y$ 与 $z$ 的积，$A \times B= \{\gcd(a,b)|a\in A,b\in B\}$

`4 x v`：询问 $v$ 在集合 $x$ 中出现次数模 $2$ 的结果。

# $\text{Solution}$

前置知识：[莫比乌斯反演](https://oi-wiki.net/math/number-theory/mobius/)

思路和已有的题解一样，给大家分享一下我思考的路程。

如果我们用 `bitset` 维护每个集合内每个数的出现次数，我们会发现操作三不太好做，于是我们把注意放在操作三上。

以下的所有式子都在模 $2$ 意义下进行。

我们记 $S_x$ 表示在集合 $S$ 中 $x$ 的出现次数。

$$S_x=\sum_{i}\sum_{j}A_i \times B_j[\gcd(i,j)=x]$$

套路地从枚举数转换为枚举倍数。

$$S_x=\sum_{i}\sum_{j}A_{i \times x} \times B_{j \times x}[\gcd(i,j)=1]$$

接下来就是套路的莫反。

$$S_x=\sum_{i}\sum_{j} A_{i \times x} \times B_{j \times x} \sum_{d|\gcd(i,j)} \mu(d)$$

$$S_x=\sum_d \mu(d) \sum_{d|i} A_{i \times x} \sum_{d|j} B_{j \times x}$$

$$S_x=\sum_d \mu(d) \sum_{i} A_{i \times x \times d} \sum_{j} B_{j \times x \times d}$$

发现后面两项 $\sum$ 长得很像，并且下标都有 $x \times d$ 于是考虑用一个函数表示它，我们设：

$$f(S,x)=\sum_{d} S_{x \times d}$$

然后代回去：

$$S_x=\sum_d \mu(d) \times f(A,x \times d) \times f(B,x \times d)$$

推到这里我们回头看这个式子：

$$f(S,x)=\sum_{d} S_{x \times d}$$

对这个进行莫反：

$$f(S,x)=\sum_{x|d} S_x$$

$$S_x=\sum_{x|d} \mu(\frac{d}{x}) \times f(S,d)$$

枚举倍数：

$$S_x=\sum_{d} \mu(d) \times f(S,x \times d)$$

然后看从上往下第七个式子，能得到：

$$f(S,x)=f(A,x) \times f(B,x)$$

这启发了我们用 `bitset` 维护 $f$ 函数。

然后我们一个一个操作考虑。

- 操作一

预处理一下只有一个数组成的集合的 $f$，直接赋值即可。

- 操作二

直接加就行，模 $2$ 意义下的加法是异或。

- 操作三

上面推过了，是两个集合的乘积，模 $2$ 意义下的乘法是与运算。

- 操作四

$$S_x=\sum_d \mu(d) \times f(S,x \times d)$$

因为我们是用 `bitset` 维护的 $f$，前面的系数尽量也用 `bitset` 维护，考虑把 $\mu(d)$ 换成 $g(x \times d)$，考虑如何构造 $g$ 函数。

其实是简单的，$g(x \times d)=\mu(d)$ 其它为 $0$ 即可，但是 $x$ 不定，所以对于每个 $x$ 都要算一下。

式子就变成了：

$$S_x=\sum_d g(x,x \times d) \times f(S,x \times d)$$

然后整道题就做完了，感觉我的思路很自然/hanx。

# $\text{Code}$

时间复杂度 $O(V \ln V +\dfrac{qV}{w})$，$V$ 是值域。

```cpp
#include<bits/stdc++.h>
#define M 7005
#define D 7000
#define N 100005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
void print(int x){
	if(x<0) putchar('-'),x=~(x-1);
	if(x>9) print(x/10);
	putchar(x%10+48);
}
int n,q,mu[M],prime[M],tot;
bool vis[M];
bitset<M>f[N],g[M],t[M],tmp;//t 是每个数单独一个集合的 f
void get_prime(){
	mu[1]=1;
	for(int i=2;i<=D;++i){
		if(!vis[i]) prime[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot && i*prime[j]<=D;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0){
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=D;++i) if(mu[i]==-1) mu[i]=1;//-1 在 mod 2 意义下为 1
}
void init(){
	for(int i=1;i<=D;++i) for(int j=1;i*j<=D;++j) g[i][i*j]=mu[j];//get_g
	for(int i=1;i<=D;++i) for(int j=1;i*j<=D;++j) t[i*j][i]=1;//get_t
}
int main(){
	n=read(),q=read(),get_prime(),init();
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),y=read();
			f[x]=t[y];
		}
		if(op==2){
			int x=read(),y=read(),z=read();
			f[x]=f[y]^f[z];
		}
		if(op==3){
			int x=read(),y=read(),z=read();
			f[x]=f[y]&f[z];
		}
		if(op==4){
			int x=read(),y=read();
			tmp=f[x]&g[y];
			printf("%d",tmp.count()&1);
//			puts("");
		}
	}
	return 0;
}
```

---

## 作者：_lbw_ (赞：3)

这题的难点在于乘法操作。

我们发现它其实是 gcd 卷积。

根据某著名原理，gcd 相当于位运算上的与。

于是我们考虑在每一个质因数维度进行 $\textsf{FMT}$。

而这里 $\textsf{FMT}$ 相当于 $\sum\limits_{j|i}f_j$，我叫它 $\textsf{FGT}$。

于是我们用 bitset 寄录每个点的 $\textsf{FGT}$，
然后 1 操作直接预处理每个值对应的 $\textsf{FGT}$。

2 操作 $\textsf{FGT}(C)=\sum\limits_{j|i}C_j=\sum\limits_{j|i}A_j+B_j=\textsf{FGT}(A)+\textsf{FGT}(B)$ 相当于 bitset 里的 xor。

3 操作因为我们 $\textsf{FGT}$ 完就直接相乘就可以了，相当于 and。

4 操作查询单点 $\textsf{IFGT}$ 后的值，可以直接暴力。

（实际上 $\textsf{FGT}$ 相当于反演？）。

```cpp
const int maxn = 7e3+5;const int maxm = 1e5+5;
ll n,T,U[maxn],t,x,y,z;bitset<maxn>p[maxn],q[maxn],a[maxm];
int main(){
	n=read();T=read();U[1]=1;
	F(i,1,7e3)for(int j=i*2;j<=7e3;j+=i)U[j]^=U[i];
	F(i,1,7e3)F(j,1,7e3){if(i%j==0)p[i][j]=1;if(j%i==0)q[i][j]=U[j/i];}
	while(T--){
		t=read();x=read();y=read();
		if(t==1)a[x]=p[y];
		else if(t==2)a[x]=a[y]^a[read()];
		else if(t==3)a[x]=a[y]&a[read()];
		else cout<<((a[x]&q[y]).count()&1);
	}
	return 0;
}
```


---

## 作者：bsdsdb (赞：1)

题意：你需要维护 $n$ 个初始为空的可重集 $\{S_i\}_{i=1}^n$：

1. $S_x\gets\{v\}$；
2. $S_x\gets S_y\cup S_z$；
3. $S_x\gets\{\gcd(u,v)\mid u\in S_y,v\in S_z\}$；
4. 询问 $\#_vS_x\bmod2$。

$n\le10^5,q\le10^6,V=7000$。

不难发现一个数在一个集合里面出现 $2$ 次等于不出现，所以考虑对每个集合开一个 bitset 维护数出现的次数模 $2$，下记 $v$ 在 $S_x$ 中出现的次数模 $2$ 为 $f_x(v)$，函数 $f_x,f_y$ 及其值 $f_x(u),f_y(u)$ 之间的加法为 $\mathrm{xor}$，乘法为 $\cap$。那么操作 1 就是直接赋值，操作 2 就是 $f_x\gets f_yf_z$，操作 4 就是直接输出。至于操作 3：

$$
\begin{aligned}
f_x(u)\gets&\sum_{u\mid v}\sum_{u\mid w}[\gcd(v,w)=u]f_y(v)f_z(w)\\
=&\sum_{v=1}^{\frac Vu}\sum_{w=1}^{\frac Vu}f_y(uv)f_z(uw)[v\perp w]\\
=&\sum_{v=1}^{\frac Vu}\sum_{w=1}^{\frac Vu}f_y(uv)f_z(uw)\sum_{\substack{d\mid v\\d\mid w}}\mu(d)\\
=&\sum_{d=1}^{\frac Vu}\mu(d)\left(\sum_{d\mid v}f_y(uv)\right)\left(\sum_{d\mid w}f_z(uw)\right)\\
=&\sum_{d=1}^{\frac Vu}\mu(d)\left(\sum_{du\mid v}f_y(v)\right)\left(\sum_{du\mid w}f_z(w)\right)\\
\end{aligned}
$$

看到后面那个求和的形式，可以设 $g_x(u)\coloneqq\sum_{u\mid p}f_x(p)$，那么：

$$
\begin{aligned}
g_x(u)=&\sum_{u\mid p}f_x(p)\\
=&\sum_{u\mid p}\sum_{d=1}^{\frac Vp}\mu(d)g_y(dp)g_z(dp)
\end{aligned}
$$

怎么推不下去了？

$$
\begin{aligned}
g_x(u)=&\sum_{u\mid p}f_x(p)\\
=&\sum_{u\mid p}\sum_{p\mid v}\sum_{p\mid w}[\gcd(v,w)=p]f_y(v)f_z(w)\\
=&\sum_{u\mid v}\sum_{u\mid w}f_y(v)f_z(w)\\
=&g_y(u)g_z(u)
\end{aligned}
$$

~~蓦然回首，那人却在，灯火阑珊处~~

那其他操作咋维护 $g$ 呢？

操作 1，把 $V$ 中可能的情况预处理出来；

操作 2，还是 $g_x\gets g_yg_z$；

操作 4：已知所有 $g_x(i)$ 求 $f_x(v)$，不会了？

> 算法，就是在人脑计算的基础上，将流程标准化与高度抽象化。—— [Wozki Shode](https://bilibili.com/video/BV1GJ411x7h7)

所以我们不妨来想想，如果让人脑去解决这个问题，他会怎么解决。为了让结果包含一项 $f_x(v)$，先把 $g_x(v)$ 加上：

| 加上的 $g_x$ \\ 每一项 $f_x(kv)$ 对答案的贡献 | $v$ | $2v$ | $3v$ | $4v$ | $5v$ | $6v$ | $7v$ | $8v$ | $9v$ | $10v$ | $12v$ | $15v$ | $30v$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $g_x(v)$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ |

但是 $f_x(2v)$ 多出来了，把他减掉：

| 略 | $v$ | $2v$ | $3v$ | $4v$ | $5v$ | $6v$ | $7v$ | $8v$ | $9v$ | $10v$ | $12v$ | $15v$ | $30v$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $g_x(v)$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ |
| $-g_x(2v)$ | $1$ |  | $1$ |  | $1$ |  | $1$ |  | $1$ |  |  | $1$ |  |

$f_x(3v)$ 也多了，减掉（后面文字描述略）：

| 略 | $v$ | $2v$ | $3v$ | $4v$ | $5v$ | $6v$ | $7v$ | $8v$ | $9v$ | $10v$ | $12v$ | $15v$ | $30v$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $g_x(v)$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ |
| $-g_x(2v)$ | $1$ |  | $1$ |  | $1$ |  | $1$ |  | $1$ |  |  | $1$ |  |
| $-g_x(3v)$ | $1$ |  |  |  | $1$ | $-1$ | $1$ |  |  |  | $-1$ |  | $-1$ |
| $-g_x(5v)$ | $1$ |  |  |  |  | $-1$ | $1$ |  |  | $-1$ | $-1$ | $-1$ | $-2$ |
| $g_x(6v)$ | $1$ |  |  |  |  |  | $1$ |  |  | $-1$ |  | $-1$ | $-1$ |
| $g_x(7v)$ | $1$ |  |  |  |  |  |  |  |  | $-1$ |  | $-1$ | $-1$ |
| $g_x(10v)$ | $1$ |  |  |  |  |  |  |  |  |  |  | $-1$ |  |
| $g_x(15v)$ | $1$ |  |  |  |  |  |  |  |  |  |  |  | $1$ |
| $-g_x(30v)$ | $1$ |  |  |  |  |  |  |  |  |  |  |  |  |

不难看出规律：$g_x(kv)$ 的贡献是 $\mu(k)$ 倍的。

> 归纳证明也不难，如果 $k$ 有平方因子，那么找到最小的 $p\in\mathbb P$ 满足 $p\mid\frac kp$，那么 $k$ 的贡献会随着 $\frac kp$ 的的贡献一起变动，同时归 $0$，不用额外计算；否则，设 $k$ 有 $q$ 个质因子，假设命题对 $q-1$ 成立，那么轮到 $k$ 算之前 $k$ 的贡献为 $\sum_{i=0}^{q-1}(-1)^i\binom qi=(1-1)^q-1=-(-1)^q$，为了归零贡献上 $--(-1)^q=(-1)^q=\mu(k)$。

也就是说：

$$
f_x(v)=\sum_{k=1}^{\frac Vv}\mu(k)g_x(kv)
$$

定义一个函数

$$
\mu_v(k)=
\begin{aligned}\begin{cases}
\mu\left(\frac kv\right),\quad&v\mid k\\
0,\quad&\text{otherwise.}
\end{cases}\end{aligned}
$$

那么：

$$
\begin{aligned}
f_x(v)=&\sum_{k=1}^{\frac Vv}\mu(k)g_x(kv)\\
=&\sum_{k=1}^{\frac Vv}\mu_v(kv)g_x(kv)\\
=&\sum_{k=1}^{\frac Vv}|\mu_v(kv)|g_x(kv)\\
=&\sum_{k=1}^V|\mu_v(k)|g_x(k)\\
=&\mathrm{popcount}(\lvert\mu_v\rvert g_x)\bmod 2
\end{aligned}
$$

其中，第二行到第三行是因为 $\sum$ 被我们定义成了异或和，$g_x$ 又是布尔值，所以减就是加，可以直接带绝对值。

时间 $\Omicron(V\log V+\frac{qV}w)$，空间 $\Omicron(\frac{V^2+nV}w)$。

---

## 作者：daniEl_lElE (赞：1)

$\gcd$ 非常的可爱。考虑如何得到两个集合的积。不难发现可以求出是 $x$ 倍数的数的个数，相乘，然后容斥回去。

考虑只需要求模 $2$ 的结果，考虑 `bitset` 维护每个序列是 $x$ 的倍数的数的个数模 $2$。求积相当于 `and`，求和相当于 `xor`。查询答案相当于预处理出每个位置的系数。这个可以莫比乌斯反演预处理，当然暴力也行。

复杂度 $O(\frac{qV}{w})$，可以通过。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2,3,"Ofast","inline")
#define int long long
using namespace std;
int isp[8005],prm[8005],mu[8005],top;
bitset<8005> pre[8005],dvs[8005],st[100005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	for(int i=2;i<=8000;i++) isp[i]=1;
	mu[1]=1;
	for(int i=2;i<=8000;i++){
		if(isp[i]) prm[++top]=i,mu[i]=1;
		for(int j=1;i*prm[j]<=8000;j++){
			isp[i*prm[j]]=0;
			mu[i*prm[j]]=mu[i];
			if(i%prm[j]==0){
				mu[i*prm[j]]=0;
				break;
			}
		}
	}
	for(int i=1;i<=8000;i++){
		for(int j=i;j<=8000;j+=i){
			if(mu[j/i]) pre[i].set(j);
			dvs[j].set(i);
		}
	}
	int n,q; cin>>n>>q;
	while(q--){
		int opt; cin>>opt;
		if(opt==1){
			int x,v; cin>>x>>v;
			st[x]=dvs[v];
		}
		if(opt==2){
			int x,y,z; cin>>x>>y>>z;
			st[x]=st[y]^st[z];
		}
		if(opt==3){
			int x,y,z; cin>>x>>y>>z;
			st[x]=st[y]&st[z];
		}
		if(opt==4){
			int x,v; cin>>x>>v;
			cout<<((st[x]&pre[v]).count()&1);
		}
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：1)

~~这个难度是假的吧。~~

由于“在模 $2$ 意义下”，很自然想到 `bitset` 维护。

操作一可以直接赋值，操作二由于模 $2$ ，可以直接异或起来，至于操作四直接查询即可。

操作三不会做了。

我们可以尝试维护**每个可重集的所有约数构成的可重集**，此时操作三明显就是按位与。

此时为了解决操作一，考虑把值域内每个数的约数构成的 `bitset` 预处理出来。然后操作二不变，操作四咋办？

不妨设原可重集为 $S$ ，其约数构成的可重集为 $T$ ，我们要求 $S$ 中 $p$ 的个数：

$$\begin{aligned}&\ \ \ \ \sum\limits_{q\in S}[p=q]\\&=\sum\limits_{q\in S}[\frac{q}{p}=1]\\&=\sum\limits_{q\in S}\sum\limits_{d\mid \frac{q}{p}}\mu(d)\\&=\sum\limits_{q\in T,p\mid q}\mu(q)\end{aligned}$$

前两步直接反演，最后塞到 $T$ 里面即可。

根据前人的经验我们知道 $-1\equiv 1\mod 2$ ，于是我们只需要知道 $p$ 是否含有平方因子即可。

考虑对每个数预处理出**其倍数中除以它不含平方因子的位置构成集合**，求答案的时候先按位与再找 $1$ 的个数就好了。


顺便说一句，这个预处理是可以 $O(v\ln v)$ 的，方法如下：

$$\sum\limits_{i=1}^{\sqrt{v}}\frac{v}{i^2}+\sum\limits_{i=1}^{v}\frac{v}{i}=v(\sum\limits_{i=1}^{\sqrt v}\frac{1}{i^2}+\sum\limits_{i=1}^{v}\frac{1}{i})\le 2v\ln v$$

后面那步调和级数易得。

总复杂度 $O(v\ln v+\frac{v}{w}\times q)$

- $\mathtt{code:}$

```cpp
mu.set();// 预处理mu是否有平方因子
for (int i = 2; i * i <= maxw - 1; i++) {
	for (int j = 1; j * i * i <= maxw - 1; j++) {
		mu[i * i * j] = 0;
	}
}
for (int i = 1; i <= maxw - 1; i++) {
	for (int j = 1; i * j <= maxw - 1; j++) {
		pre[i * j][i] = 1;// 还是预处理
		fac[i][i * j] = mu[j];
	}
}
for (int i = 1, op, x, y, z; i <= m; i++) {
	scanf("%d%d%d", &op, &x, &y);
	if (op == 1) s[x] = pre[y];// 处理每个集合约数构成的可重集，直接赋值
	else if (op == 2) {
		scanf("%d", &z);
		s[x] = s[y] ^ s[z];// 直接异或
	} else if (op == 3) {
		scanf("%d", &z);
		s[x] = s[y] & s[z];// 直接按位与
	} else {
		ans += ((s[x] & fac[y]).count() & 1) + '0';// 统计答案
	}
}
printf("%s", ans.c_str());
```

---

## 作者：Phartial (赞：0)

好题。

对于一个多重集 $S$，考虑记录每个元素在 $S$ 中的出现次数，由于查询是 ${\!}\bmod 2$ 的，第二种操作等价于按位异或。

考虑 $\gcd$ 卷积怎么做。对序列进行莫比乌斯变换 $\displaystyle c'_i=\sum_{i\mid j}c_j$，则卷积变为点乘，${\!}\bmod 2$ 意义下等价于按位与，且第二种操作仍然对应着按位异或。

考虑如何还原，我们有莫比乌斯逆变换 $\displaystyle c_i=\sum_{i\mid j}c'_j\mu\left(\frac{j}{i}\right)$，在 ${\!}\bmod 2$ 意义下等价于将 $c'$ 和某个和 $i$ 有关的位掩码做按位与。对所有 $i$ 预处理出对应的位掩码，使用 bitset 维护所有集合，即可做到时间复杂度 $\Theta(\frac{(q+v)v}{w})$，空间复杂度 $\Theta(\frac{(n+v)v}{w})$。

```cpp
#include <iostream>
#include <bitset>

using namespace std;

const int kN = 1e5 + 1, kV = 7001;

int n, q, m[kV];
bitset<kV> a[kN], c[kV], b[kV];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int i = 1; i < kV; ++i) {
    for (int j = i; j < kV; j += i) {
      c[j].set(i);
    }
  }
  for (int i = 1; i < kV; ++i) {
    m[i] = 1;
    for (int j = 2; j * j <= i; ++j) {
      if (i % (j * j) == 0) {
        m[i] = 0;
        break;
      }
    }
  }
  for (int i = 1; i < kV; ++i) {
    for (int j = 1; j * i < kV; ++j) {
      b[i][j * i] = m[j];
    }
  }
  cin >> n >> q;
  for (int o, x, y, z; q--; ) {
    cin >> o >> x >> y;
    if (o == 1) {
      a[x] = c[y];
    } else if (o == 2) {
      cin >> z;
      a[x] = a[y] ^ a[z];
    } else if (o == 3) {
      cin >> z;
      a[x] = a[y] & a[z];
    } else {
      cout << ((a[x] & b[y]).count() & 1);
    }
  }
  return 0;
}
```

---

