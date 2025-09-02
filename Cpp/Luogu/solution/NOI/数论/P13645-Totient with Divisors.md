# Totient with Divisors

## 题目背景

到底是互质还是整除？

## 题目描述

有 $T$ 组询问，每次给定 $n,m$，求：

$$
\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sigma(ij)
$$

由于答案会很大，你只需要输出答案对 $998244353$ 取模的结果。

上式中：

- $\varphi$ 是欧拉函数，$\varphi(n)$ 表示 $1\sim n$ 中与 $n$ 互质的数的个数。
- $\sigma$ 是约数和函数，$\sigma(n)$ 表示 $n$ 的所有约数之和。

## 说明/提示

**本题有捆绑测试**

- 对于 Subtask #$0$（$7$pts）：保证 $T\leq500,n,m\leq400$。
- 对于 Subtask #$1$（$8$pts）：保证 $n,m\leq450$。
- 对于 Subtask #$2$（$12$pts）：保证 $T,n,m\leq5000$。
- 对于 Subtask #$3$（$15$pts）：保证 $n,m\leq5000$。
- 对于 Subtask #$4$（$20$pts）：保证 $T\leq10$。
- 对于 Subtask #$5$（$38$pts）：无特殊限制。

对于 $100\%$ 的数据：保证 $1\leq T,n,m\leq 10^5$。

## 样例 #1

### 输入

```
8
2 2
3 3
4 4
5 5
6 6
7 7
114 514
2333 23333
```

### 输出

```
14
130
566
2310
4778
13934
603971168
547492264```

# 题解

## 作者：Feather_Moon (赞：24)

[题目传送门](https://www.luogu.com.cn/problem/P13645)

## 题意

给你多组询问，求：

$$
\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sigma(ij)
$$

其中 $1\leq T,n,m\leq 10^5$。

## 分析

不妨设 $n \leq m$。

首先我们肯定要把 $\sigma(ij)$ 拆开。

然后这里有一个结论：

$$
\sigma(ij)=\sum_{x\mid i}\sum_{y\mid j}\dfrac{iy}{x}[\gcd(x,y)=1]
$$



::::success[该结论的简要证明]
:::info[感性证明]{open}
我们有:
$$
\sigma(x)=\prod_{i}(1+p_i+p_i^2+\cdots+p_i^{a_i})
$$
每个质因子可以独立处理。

$x$ 和 $y$ 本质上枚举了 $i$ 和 $j$ 的所有质因子组合。

$\gcd(x,y)=1$ 保证了每个质因子 $x$ 和 $y$ 中有一个指数为 $0$。

那么 $\dfrac{iy}{x}$ 就可以取到一个质因子在 $ij$ 中的所有指数。
:::
:::info[理性证明]{open}
$$\sigma(x)=\prod_{i}(1+p_i+p_i^2+\cdots+p_i^{a_i})
$$

考虑每个质因子 $p$ 独立处理。

令 $v_p(n)$ 表示质因子 $p$ 整除 $n$ 的最高幂次。

由 $x\mid i,y\mid j$ 易得 $0 \leq v_p(x) \leq v_p(i),0 \leq v_p(y) \leq v_p(j)$。


由 $\gcd(x,y)=1$，易得 $ \min(v_p(x),v_p(y))=v_p(1)=0$。

- 当 $v_p(x)=0$ 且 $v_p(y) \neq 0$ 时，$v_p(\dfrac{iy}{x})=v_p(i)+v_p(y)$，恰好取得 $[v_p(i)+1,v_p(i)+v_p(j)=v_p(ij)]$ 每个数各一次。

- 当 $v_p(y)=0$ 时，$v_p(\dfrac{iy}{x})=v_p(i)-v_p(x)$，恰好取得 $[0,v_p(i)]$ 每个数各一次。

故 $v_p(\dfrac{iy}{x})$ 不重不漏的取了 $[0,v_p(ij)]$ 每个数各一次。

而所有质因子的每种组合都会被取一遍，故结论成立。
:::
::::
~~最难点已过，恭喜你切掉一道黑题。~~

接下来就是我们喜闻乐见的推式子时间：
$$\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sigma(ij)$$
用上述结论把 $\sigma(ij)$ 替掉，得：
$$\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sum_{x\mid i}\sum_{y\mid j}\dfrac{iy}{x}[\gcd(x,y)=1]$$
经典的拆 $\gcd$：
$$
\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sum_{x\mid i}\sum_{y\mid j}\dfrac{iy}{x}\sum_{d\mid \gcd(x,y)}\mu(d)
$$
交换求和顺序，把 $d$ 外提：
$$
\sum_{d=1}^n \mu(d)(\sum_{d \mid x}^n\sum_{x\mid i}^n \dfrac{i\varphi(i)}{x})(\sum_{d\mid y}^m  y\sum_{y \mid j}^m\varphi(j))
$$
令 $x=dX,i=xI,y=dY,j=yJ$：
$$
\sum_{d=1}^n \mu(d)(\sum_{X=1}^{\lfloor n/d \rfloor}\sum_{I=1}^{\lfloor n/dX \rfloor}I\varphi(dXI))(\sum_{Y=1}^{\lfloor m/d \rfloor} dY\sum_{J=1}^{\lfloor m/dY \rfloor}\varphi(dYJ))
$$
把 $dY$ 中的 $d$ 往外提，交换 $J,Y$ 的求和顺序：
$$
\sum_{d=1}^{n}d\mu(d)(\sum_{X=1}^{\lfloor n/d \rfloor}\sum_{I=1}^{\lfloor n/dX \rfloor}I\varphi(dXI))(\sum_{J=1}^{\lfloor m/d \rfloor}\sum_{Y=1}^{\lfloor m/dJ \rfloor}Y\varphi(dJY))
$$

注意两个括号是相同的形式，我们令：
$$
F(x,y)=\sum_{i=1}^x\sum_{j=1}^{\lfloor x/i \rfloor}j\varphi(ijy)
$$
令 $T=ij$：
$$
\begin{aligned}
F(x,y)&=\sum_{T=1}^x\varphi(Ty)\sum_{j \mid T}j\\
&=\sum_{T=1}^x\varphi(Ty)\sigma(T)\\
\end{aligned}
$$
注意到这东西可以递推：
$$
F(x,y)=F(x-1,y)+\varphi(xy)\sigma(x)
$$
将其带入原式，得：
$$
\sum_{d=1}^nd\mu(d) F(\lfloor \dfrac{n}{d} \rfloor,d) F(\lfloor \dfrac{m}{d} \rfloor,d)
$$
然后就可以用类似 [P4240](https://www.luogu.com.cn/problem/P4240) 的方法做了！具体的说：

然后你会发现这个时候 $F$ 里面是带 $d$ 的不能直接的数论分块。我们考虑平衡。

套路地，我们把整个式子换元换出来。我们令： 
$$
G(n,m,k)=\sum_{d=1}^kd\mu(d) F(\lfloor \dfrac{n}{d} \rfloor,d) F(\lfloor \dfrac{m}{d} \rfloor,d)
$$

然后我们发现当 $d$ 很大的时候 $\lfloor \dfrac{n}{d} \rfloor,\lfloor \dfrac{m}{d} \rfloor$ 很小，这是不是意味着我们可以预处理一部分 $G$？

首先我们可以用递推把所有的 $F$ 给预处理出来，时间复杂度是调和级数级别的即 $\mathcal{O}(n \ln n)$ 的。

设置一个阈值 $S$，$\lfloor \dfrac{n}{d} \rfloor \leq S$ 的部分预处理。用人话说，我们要把 $G(x,y,z)$ 中 $x \leq S$ 的所有 $G(x,y,z)$ 的值预处理出来。

因为第三维是可以递推 $\mathcal{O}(1)$ 求的，$x$ 有 $S$ 种取值，$y \times z \leq m$，预处理的时间复杂度是 $\mathcal{O}(mS)$ 的。

接下来我们就可以数论分块了，如果预处理过了数论分块算复杂度是 $\mathcal{O}(T \sqrt{n})$ 的，没预处理过暴力算。因为我们已经把 $\lfloor \dfrac{n}{d} \rfloor \leq S$ 的部分预处理了，所以剩下没预处理的一定满足 $d\le \lfloor\dfrac{n}{S+1}\rfloor$，时间复杂度为 $\mathcal{O}(\dfrac{nT}{S})$。

总时间复杂度 $\mathcal{O}(\dfrac{nT}{S}+T \sqrt{n}+mS+n \ln n)$。反正 $n,m$ 同阶，$S$ 取 $\sqrt{T}$ 可以达到时间复杂度 $O((n+m)\sqrt{T}+T\sqrt{n}+n \ln n)$。
::::success[代码]
~~代码写的就是一坨大家不要拿我的代码做参考~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,L=405,TT=998244353;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int pri[N],top;
int flg[N];
int mu[N],phi[N];
long long d[N],sp[N];
void init(int n){
	mu[1]=1;phi[1]=1;d[1]=1;
	for(int i=2;i<=n;i++){
		if(!flg[i]){
			pri[++top]=i;
			phi[i]=i-1;
			mu[i]=-1;
			d[i]=i+1;
			sp[i]=i+1;
		}
		for(int j=1;j<=top;j++){
			int pri_j=pri[j];
			if(i*pri_j > n)break;
			flg[i*pri_j]=1;
			if(i%pri_j==0){
				sp[i*pri_j]=sp[i]*pri_j+1;
				d[i*pri_j]=d[i]/sp[i]*sp[i*pri_j];
				phi[i*pri_j]=phi[i]*pri_j;
				mu[i*pri_j]=0;
				break;
			}
			phi[pri_j*i]=phi[i]*phi[pri_j];
			d[pri_j*i]=d[pri_j]*d[i];
			mu[i*pri_j]=-mu[i];
			sp[i*pri_j]=1+pri_j;
		}
	}
	for(int i=1;i<=n;i++)d[i]=d[i]%TT;
}//筛 
int T,n,m;
int S;
int f[L][N];
int af[N][505];
void make_f(){
	for(int i=1;i<=S;i++){
		for(int j=1;i*j<=(N-5);j++){
			f[i][j]=((long long)f[i-1][j]+((long long)phi[i*j]*d[i]%TT))%TT;
		}
	}
	for(int j=1;j<=(N-5)/S;j++){//注意是 N/S 不是 S 
		for(int i=1;i*j<=(N-5);i++){
			af[i][j]=((long long)af[i-1][j]+((long long)phi[i*j]*d[i]%TT))%TT;
		}
	}
}//预处理 f，懒得用 vector 所以我用了静态数组 
vector<int> g[L][L];
int now;
void make_g(){
	for(int i=1;i<=S;i++){
		for(int j=1;j<=S;j++){
			g[i][j].push_back(0);
			for(int k=1;i*k<=(N-5) && j*k<=(N-5);k++){
				g[i][j].push_back(((long long)g[i][j][k-1]+(long long)k*(long long)mu[k]%TT*(long long)f[i][k]%TT*f[j][k]%TT+TT)%TT);
			}
		}
	}
}//预处理 g 
int calc(int n,int m){
	int ret=0,l=1,r=0;
	while(l<=n){
		r=min(n/(int)(n/l),m/(int)(m/l));
		if(r>n)r=n;
		if((n/l)<=S && (m/l)<=S){
			ret=((long long)ret+(long long)g[n/l][m/l][r]-g[n/l][m/l][l-1]+TT)%TT;
		}else{
			for(int k=l;k<=r;k++)ret=((long long)ret+(long long)k*(long long)mu[k]%TT*(long long)af[n/l][k]%TT*af[m/l][k]%TT+TT)%TT;
			//暴力计算 
		}
		l=r+1;
	}
	return ret;
}
signed main(){
	T=read();S=200;
	init(N-5);
	make_f();make_g();
	while(T--){
		n=read(),m=read();
		if(n>m)swap(n,m);
		write(calc(n,m));putchar('\n');
	}
	return 0;
}
```
::::
## 后记

为出题喜欢用经典结论的出题人献上由衷的祝福。

~~我劝你们家里多备几个【数据删除】。~~

---

## 作者：LXcjh4998 (赞：10)

[Luogu 链接](https://www.luogu.com.cn/problem/P13645)
# 前言
推式子的部分官方题解说的已经很详细了，本篇题解主要是给出实现的一些细节。  
当然，本篇题解式子会再推一遍。

以及那个经典结论，可能是我太弱了，没见过这个结论。  
（给见过这个结论的大蛇磕头了，给场切这题的大蛇磕头了）
# 题意
求
$$\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sigma(ij)$$

多测，$1\le n,m,T\le N=10^5$。
# 思路
首先有一个不知道哪里冒出来的结论：
$$\sigma(ij)=\sum_{d_1\mid i}\sum_{d_2\mid j}\dfrac{id_2}{d_1}[\gcd(d_1,d_2)=1]$$

先给出这个结论的证明：
> 对于质数 $p$，我们设它在 $i$ 中的指数为 $x$，在 $j$ 中的指数为 $y$，在 $d_1$ 中的指数为 $x'$，在 $d_2$ 中的指数为 $y'$，所以 $p$ 在 $ij$ 中的指数为 $x+y$。（显然有 $0\le x'\le x$，$0\le y'\le y$）
>
> 则 $p$ 在 $\dfrac{id_2}{d_1}$ 的指数为 $x+y'-x'$，并且由于 $\gcd(d_1,d_2)=1$，所以有 $\min(x',y')=0$。
>
> - 当 $x'=0$ 时，有 $0\le y'\le y$，因此 $x+y'-x'$ 可以取遍 $[x,x+y]$ 中的所有整数。
> - 当 $x'\neq0$ 时，有 $y'=0$，以及 $0<x'\le x$，所以 $x+y'-x'$ 可以取遍 $[0,x)$ 中的所有整数。
> 
> 综上 $x+y'-x'$ 可以取遍 $[0,x+y]$ 中的所有整数，故原式成立。

然后我们就可以来推式子了（不妨设 $n\le m$）。

$$\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sigma(ij)\\
=&\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sum_{d_1\mid i}\sum_{d_2\mid j}\dfrac{id_2}{d_1}[\gcd(d_1,d_2)=1]\\
=&\sum_{i=1}^n\varphi(i)i\sum_{j=1}^m\varphi(j)\sum_{d_1\mid i}\sum_{d_2\mid j}\dfrac{d_2}{d_1}[\gcd(d_1,d_2)=1]\\
=&\sum_{d_1=1}^n(\sum_{i=1}^{ n/d_1}\varphi(id_1)i)\sum_{d_2=1}^md_2(\sum_{j=1}^{m/d_2}\varphi(jd_2))[\gcd(d_1,d_2)=1]\\
=&\sum_{t=1}^n\mu(t)t(\sum_{d_1=1}^{n/t}\sum_{i=1}^{n/d_1t}\varphi(id_1t)i)(\sum_{d_2=1}^{m/t}d_2\sum_{i=1}^{m/d_2t}\varphi(id_2t))\\
=&\sum_{t=1}^n\mu(t)t(\sum_{d=1}^{n/t}\sum_{i=1}^{n/dt}\varphi(idt)i)(\sum_{d=1}^{m/t}\sum_{i=1}^{m/dt}\varphi(idt)i)\\
=&\sum_{t=1}^n\mu(t)tf(\lfloor\dfrac{n}{t}\rfloor,t)f(\lfloor\dfrac{m}{t}\rfloor,t)
\end{aligned}$$
---
我们有：
$$\begin{aligned}
f(x,y)
&=\sum_{i=1}^x\sum_{j=1}^{x/i}\varphi(ijy)j\\
&=\sum_{t=1}^x\varphi(ty)\sigma(t)\\
&=(\sum_{t=1}^{x-1}\varphi(ty)\sigma(t))+\varphi(xy)\sigma(x)\\
&=f(x-1,y)+\varphi(xy)\sigma(x)
\end{aligned}$$

显然有 $f(1,y)=\varphi(y)$

注意到，$\lfloor\dfrac{n}{t}\rfloor\times t\le n\le N$，$\lfloor\dfrac{m}{t}\rfloor\times t\le m\le N$。  
因此我们需要用到的 $f(x,y)$ 都有 $1\le xy\le N$。

所以我们需要计算的 $f(x,y)$ 的个数为 $\displaystyle O(\sum_{i=1}^N\dfrac{N}{i})=O(N\log N)$

并且，在我们线性筛出 $[1,N]$ 处 $\varphi(x)$、$\sigma(x)$ 的值后，我们可以 $O(1)$ 递推算出每个 $f(x,y)$。

因此预处理所有 $f(x,y)$ 的复杂度是 $O(N\log N)$ 的。

---
注意到我们显然需要用数论分块计算答案。  
也就是说，我们需要处理 $\mu(t)tf(\lfloor\dfrac{n}{t}\rfloor,t)f(\lfloor\dfrac{m}{t}\rfloor,t)$ 在 $\lfloor\dfrac{n}{t}\rfloor$ 和 $\lfloor\dfrac{m}{t}\rfloor$ 相同时关于 $t$ 的前缀和。

但是总共有 $\displaystyle O(\sum_{t=1}^N\frac{N^2}{t^2})=O(N^2)$ 个需要计算的值，全部预处理复杂度无法接受。

但是我们肯定也要预处理一部分，不然计算的时间复杂度就无法接受。

考虑设置一个阈值 $S$，当 $\lfloor\dfrac{m}{t}\rfloor\le S$ 时将值预处理。  
复杂度是 $\displaystyle O(\sum_{i=1}^Si\times\dfrac{N}{i})=O(NS)$。

当 $\lfloor\dfrac{m}{t}\rfloor>S$ 时，此时由于 $t\le \lfloor\dfrac{m}{S+1}\rfloor$，我们可以对于每个 $t$ 处的值 $O(1)$ 计算。

当 $t>\lfloor\dfrac{m}{S+1}\rfloor$ 时，我们就可以用预处理的值进行数论分块了。

时间复杂度是 $O(NS+T\sqrt{N}+\dfrac{NT}{S})$。  
当 $S$ 取 $\sqrt{T}$ 时可以达到最优时间复杂度 $O(N\sqrt{T}+T\sqrt{N})$。

对于具体的实现，我们可以令 $\displaystyle g(x,y,t)=\sum_{i=1}^t\mu(i)if(x,i)f(y,i)$，直接递推计算即可。  
显然递推是 $O(1)$ 的，因为 $f(x,y)$ 的值我们都计算过了。

---
现在我们来理一下思路。

预处理：
- 使用线性筛筛出 $\mu(n)$、$\varphi(n)$、$\sigma(n)$ 在 $[1,N]$ 的值，复杂度 $O(N)$。
- $O(1)$ 递推出每个 $f(x,y)$ 的值，复杂度 $O(N\log N)$。
- $O(1)$ 递推出我们需要预处理的 $g(x,y,t)$ 的值，复杂度 $O(N\sqrt{T})$。

计算答案：
- 对于 $t\le \lfloor\dfrac{m}{S+1}\rfloor$，我们 $O(1)$ 计算每个值，复杂度 $O(N\sqrt{T})$。
- 对于 $t> \lfloor\dfrac{m}{S+1}\rfloor$，我们可以利用预处理的 $g(x,y,t)$ 使用数论分块计算，复杂度 $O(T\sqrt{N})$。
---
最后这道题就做完了。  
其实码量倒不是很大，就是这个结论没见过就没法做。（也可能只是我太弱了）
# 程序
[AC 记录](https://www.luogu.com.cn/record/229528639)
```cpp
#include<bits/stdc++.h>
#define forUp(i,a,b) for(int i=(a);i<=(b);++i)
#define forUP(i,a,b) for(int i=(a);i<(b);++i)
#define forDown(i,a,b) for(int i=(a);i>=(b);--i)
#define forG(i,u,v) for(int i=head[u],v=to[i];i;i=nxt[i],v=to[i])
#define pb emplace_back
using ll=long long;using ull=unsigned long long;using uint=unsigned int;using db=double;using ld=long db;using pii=std::pair<int,int>;using pdi=std::pair<db,int>;using vl=__int128;using uvl=unsigned __int128;
constexpr int INF=0x3f3f3f3f,MINF=0xcfcfcfcf;constexpr long long INFLL=0x3f3f3f3f3f3f3f3f,MINFLL=0xcfcfcfcfcfcfcfcf;constexpr double INFDB=1e50,eps=1e-9;
template<class _Tp>void chkMax(_Tp &x,const _Tp &y){x<y?x=y:0;}template<class _Tp>void chkMin(_Tp &x,const _Tp &y){x>y?x=y:0;}
constexpr int N=1e5+10,B=sqrt(1e5)+10,mod=998244353;int __test_num=1,__test_id;using namespace std;void __init();

int cnt,P[N],mu[N],phi[N],minp[N],sigma[N];bool np[N];
int S;vector<int> f[N],g[B][B];

int n,m,ans;

void __solve(int __test_id){
	scanf("%d%d",&n,&m);if(n>m)swap(n,m);ans=0;
	for(int i=1;i<=n&&i<=m/(S+1);++i)ans=(ans+(1ll*mu[i]*i*f[n/i][i]%mod*f[m/i][i]%mod+mod)%mod)%mod;
	for(int l=m/(S+1)+1,r;l<=n;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans=(ans+(g[n/l][m/l][r]-g[n/l][m/l][l-1]+mod)%mod)%mod;
	}
	printf("%d\n",ans);
}
signed main(){
	__init();
	forUp(i,1,__test_num)__solve(i);
	return 0;
}
void __init(){
	//const string __file_name="test";freopen((__file_name+".in").c_str(),"r",stdin);freopen((__file_name+".out").c_str(),"w",stdout);
	scanf("%d",&__test_num);
	int n=N-10;S=sqrt(__test_num);
	mu[1]=phi[1]=sigma[1]=minp[1]=1;
	forUp(i,2,n){
		if(!np[i])P[++cnt]=i,mu[i]=-1,phi[i]=i-1,sigma[i]=i+1,minp[i]=i;
		for(int j=1;j<=cnt&&i*P[j]<=n;++j){
			int p=P[j],x=i*p;
			np[x]=true;
			if(i%p==0){
				minp[x]=minp[i]*p;
				phi[x]=phi[i]*p;
				if(minp[x]==x)sigma[x]=p*sigma[i]+1;
				else sigma[x]=sigma[x/minp[x]]*sigma[minp[x]];
				break;
			}
			mu[x]=-mu[i],phi[x]=phi[i]*phi[p],sigma[x]=sigma[i]*sigma[p],minp[x]=p;
		}
	}
	f[1].pb(0);forUp(j,1,n)f[1].pb(phi[j]);
	forUp(i,2,n){
		f[i].pb(0);
		forUp(j,1,n/i){
			int tmp=(f[i-1][j]+1ll*phi[i*j]*sigma[i]%mod)%mod;
			f[i].pb(tmp);
		}
	}
	forUp(j,1,S)forUp(i,1,j){
		g[i][j].pb(0);
		forUp(k,1,n/j){
			int tmp=(g[i][j][k-1]+(1ll*mu[k]*k*f[i][k]%mod*f[j][k]%mod+mod)%mod)%mod;
			g[i][j].pb(tmp);
		}
	}
}
```

---

## 作者：cly312 (赞：4)

观察到 $\sigma(ij)$ 可以用莫比乌斯函数来表示：
$$\sigma(ij) = \sum_{d|\gcd(i,j)} \mu(d) \cdot d \cdot \sigma\left(\frac{i}{d}\right) \cdot \sigma\left(\frac{j}{d}\right)$$

将上式代入原式：

$$
\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sigma(ij) = \sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\left(\sum_{d|\gcd(i,j)} \mu(d) \cdot d \cdot \sigma\left(\frac{i}{d}\right) \cdot \sigma\left(\frac{j}{d}\right)\right)
$$

交换求和顺序，将 $d$ 的求和提到最外层。注意 $d$ 必须是 $\gcd(i,j)$ 的因子，即 $d|i$ 且 $d|j$：

$$
= \sum_{d=1}^{\min(n,m)} \mu(d) \cdot d \cdot \left(\sum_{\substack{i=1 \\ d|i}}^n\varphi(i) \cdot \sigma\left(\frac{i}{d}\right)\right) \cdot \left(\sum_{\substack{j=1 \\ d|j}}^m\varphi(j) \cdot \sigma\left(\frac{j}{d}\right)\right)
$$

令 $i = dk$ 和 $j = dl$，其中 $k$ 和 $l$ 为正整数。则 $i$ 的范围 $1 \leq i \leq n$ 变为 $1 \leq k \leq \lfloor n/d \rfloor$，$j$ 的范围 $1 \leq j \leq m$ 变为 $1 \leq l \leq \lfloor m/d \rfloor$：

$$
= \sum_{d=1}^{\min(n,m)} \mu(d) \cdot d \cdot \left(\sum_{k=1}^{\lfloor n/d \rfloor}\varphi(dk) \cdot \sigma(k)\right) \cdot \left(\sum_{l=1}^{\lfloor m/d \rfloor}\varphi(dl) \cdot \sigma(l)\right)
$$

定义 $A(d, N) = \sum_{k=1}^N \varphi(dk) \cdot \sigma(k)$，则上式简化为：

$$
= \sum_{d=1}^{\min(n,m)} \mu(d) \cdot d \cdot A(d, \lfloor n/d \rfloor) \cdot A(d, \lfloor m/d \rfloor)
$$

接下来，我们用线性筛法在 $O(n)$ 时间内预计算 $\mu$、$\varphi$ 和 $\sigma$ 函数。特别地，对于 $\sigma$ 函数的计算：

- 当 $i \bmod p = 0$ 时，$\sigma(ip) = p \cdot \sigma(i) + \sigma(i/p^k)$
- 当 $i \bmod p \neq 0$ 时，$\sigma(ip) = \sigma(i) \cdot \sigma(p)$

采用扁平化数组存储所有 $A(d, N)$ 值。具体地，使用 $flat$ 数组连续存储所有前缀和，$sidx_d$ 记录 $d$ 对应数据在 $flat$ 中的起始位置。

选择阈值 $K = 46$（经验值），对 $a, b < K$ 的情况预计算前缀和：
$H(a, b, d) = \mu(d) \cdot d \cdot A(d, a) \cdot A(d, b)$ 构建三维数组 $preh_{a,b,d}$，使得 $H(a, b, [l,r])$ 的查询可以在 $O(1)$ 时间内完成。

对于每组 $(n, m)$ 查询，计算阈值 $B = \max(\lfloor n/K \rfloor, \lfloor m/K \rfloor)$，将求和分为两部分：

对于 $d \leq B$ 的情况，直接使用预计算的 $A(d, N)$ 值计算：
$\sum_{d=1}^B \mu(d) \cdot d \cdot A(d, \lfloor n/d \rfloor) \cdot A(d, \lfloor m/d \rfloor)$

对于 $d > B$ 的情况，利用数论分块：

- 当 $d > B$ 时，$\lfloor n/d \rfloor < K$ 且 $\lfloor m/d \rfloor < K$
- 对每个值域块 $[l, r]$，使用预计算的 $perh$ 直接获取区间和
- 通过数论分块将 $O(n)$ 求和优化为 $O(\sqrt{n})$ 次操作


预处理时间复杂度为 $O(n \log n)$，包括线性筛法 $O(n)$ 和 $A(d, N)$ 计算 $O(n \log n)$。单次查询时间复杂度为 $O(n/K + \sqrt{n})$。

:::success[code]
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100000,mod=998244353,K=46;
using ll=long long;
vector<int>mu(MAXN+1),phi(MAXN+1),sigma(MAXN+1),spf(MAXN+1),pr(MAXN+1),sidx(MAXN+1,0);
vector<ll>flat;
vector<vector<vector<ll>>> preh(K,vector<vector<ll>>(K));
void init(){
    vector<bool>c(MAXN+1,false);
    vector<int>primes;
    mu[1]=phi[1]=sigma[1]=spf[1]=pr[1]=1;
    for(int i=2;i<=MAXN;i++){
        if(!c[i]){
            primes.push_back(i);
            mu[i]=-1;
            phi[i]=i-1;
            sigma[i]=i+1;
            spf[i]=i;
            pr[i]=i;
        }
        for(size_t j=0;j<primes.size();j++){
            int p=primes[j],next=i*p;
            if(next>MAXN) break;
            c[next]=true;
            spf[next]=p;
            if(i%p==0){
                mu[next]=0;
                phi[next]=phi[i]*p;
                pr[next]=pr[i]*p;
                sigma[next]=p*sigma[i]+sigma[i/pr[i]];
                break;
            }else{
                mu[next]=-mu[i];
                phi[next]=phi[i]*(p-1);
                sigma[next]=sigma[i]*sigma[p];
                pr[next]=p;
            }
        }
    }
    int sze=0;
    for(int d=1;d<=MAXN;d++){
        if(MAXN/d==0)break;
        sidx[d]=sze;
        sze+=MAXN/d+1;
    }
    flat.resize(sze,0);
    for(int d=1;d<=MAXN;d++){
        if(MAXN/d==0) continue;
        int idx=sidx[d];
        flat[idx]=0;
        for(int i=1;i<=MAXN/d;i++){
            flat[idx+i]=(flat[idx+i-1]+1ll*phi[d*i]*sigma[i]%mod)%mod;
        }
    }
    for(int a=1;a<K;a++){
        for(int b=1;b<K;b++){
            int dab=min(MAXN/a,MAXN/b);
            if(dab==0)continue;
            vector<ll> P(dab+1,0);
            for(int d=1;d<=dab;d++){
            	ll term=1ll*mu[d]*d%mod;
                term=term*flat[sidx[d]+a]%mod;
                term=term*flat[sidx[d]+b]%mod;
                P[d]=(P[d-1]+term)%mod;
            }
            preh[a][b]=P;
        }
    }
}
int main(){
    init();
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        int G=min(n,m);
        if(G==0){
            cout<<0<<'\n';
            continue;
        }
        int B=max(n/K,m/K);
        ll ans=0;
        for(int d=1;d<=min(B,G);d++){
        	ll term=1ll*mu[d]*d%mod;
            term=term*flat[sidx[d]+n/d]%mod;
            term=term*flat[sidx[d]+m/d]%mod;
            ans=(ans+term)%mod;
        }
        int d=B+1;
        while(d<=G){
            int a=n/d,b=m/d;
            int R=min({n/a,m/b,G});
            if(a<K&&b<K){
                ans=(ans+((preh[a][b][R]-preh[a][b][d-1]+mod)%mod))%mod;
            }else{
                for(int i=d;i<=R;i++){
                	ll term=1ll*mu[i]*i%mod;
                    term=term*flat[sidx[i]+n/i]%mod;
                    term=term*flat[sidx[i]+m/i]%mod;
                    ans=(ans+term)%mod;
                }
            }
            d=R+1;
        }
        ans=(ans%mod+mod)%mod;
        cout<<ans<<'\n';
    }
    return 0;
}
```
:::

---

## 作者：wdl_ (赞：3)

首先，有一个奇妙小结论：

$$\sigma(ij) = \sum_{d | \gcd(i,j)}d\mu(d)\sigma(\frac{i}{d})\sigma(\frac{j}{d})$$

将上式代入原式：

$$\sum_{i = 1}^{n}\sum_{j = 1}^{m}\varphi(i)\varphi(j)\sum_{d | \gcd(i,j)}d\mu(d)\sigma(\frac{i}{d})\sigma(\frac{j}{d})$$

然后就是套路化的推式子：

$$=\sum_{d = 1}^{n}d\mu(d)\sum_{i = 1}^{\left\lfloor\frac{n}{d}\right\rfloor}\sum_{j = 1}^{\left\lfloor\frac{m}{d}\right\rfloor}\varphi(id)\varphi(jd)\sigma(i)\sigma(j)$$

$$=\sum_{d = 1}^{n}d\mu(d)(\sum_{i = 1}^{\left\lfloor\frac{n}{d}\right\rfloor}\varphi(id)\sigma(i))(\sum_{i = 1}^{\left\lfloor\frac{m}{d}\right\rfloor}\varphi(id)\sigma(i))$$

令 $f(i) = i\mu(i)$，$g(d,n) = \sum_{i = 1}^{n}\varphi(id)\sigma(i)$。

代入原式：

$$\sum_{d = 1}^{n}f(d)g(d,\left\lfloor\frac{n}{d}\right\rfloor)g(d,\left\lfloor\frac{m}{d}\right\rfloor)$$

$f(d)$ 不必多说，$g(d,n)$ 能预处理，复杂度 $\Theta(n\ln n)$。

因为 $g$ 中包含 $d$，所以不能直接整除分块。然后我们发现这个式子和 [P4240](https://www.luogu.com.cn/problem/P4240) 中的式子长得一模一样，然后就可以套路化地套用这题的思路。

把整个式子用一个参数表示出来，令 $t(a,b,n) = \sum_{d = 1}^{n}f(d)g(d,a)g(d,b)$，原式就可以表示为差分形式：

$$\sum_{\left\lfloor\frac{n}{i}\right\rfloor = \left\lfloor\frac{n}{j}\right\rfloor,\left\lfloor\frac{m}{i}\right\rfloor = \left\lfloor\frac{m}{j}\right\rfloor}t(\left\lfloor\frac{n}{i}\right\rfloor,\left\lfloor\frac{m}{i}\right\rfloor,j) - t(\left\lfloor\frac{n}{i}\right\rfloor,\left\lfloor\frac{m}{i}\right\rfloor,i - 1)$$

直接做肯定是不行的，然后我们发现当 $\left\lfloor\frac{n}{d}\right\rfloor$ 增大时，$d$ 是减小的，因此考虑平衡。

设置阈值 $S$，预处理出 $t(1,1,1)$ 到 $t(S,S,n)$，当 $\left\lfloor\frac{m}{d}\right\rfloor$ 小于 $S$ 时就可以直接整除分块做。预处理复杂度 $\Theta(nS^2)$，查询复杂度 $\Theta(\sqrt n)$。

对于 $\left\lfloor\frac{m}{d}\right\rfloor$ 大于 $S$ 的部分，此时 $d$ 小于 $\left\lfloor\frac{m}{S}\right\rfloor$，直接暴力计算，复杂度为 $\Theta(\frac{n}{S})$。

综上，总复杂度为 $\Theta(n\ln n + nS^2 + T(\sqrt{n} + \frac{n}{S}))$。

通过简单计算得知，当 $S = (\frac{T}{2})^{\frac{1}{3}}$ 时，复杂度取得最小，当然还要根据实际情况进行一定调整，通过时采用 $S = 47$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1e18
#define lowbit(x) (x & -x)
#define fo(i,j,k,l) for(int i = j;i <= k;i += l)
using namespace std;
const int mod = 998244353;
int T,n,m;
int p[100005];
int mu[100005];
int phi[100005];
int sigma[100005];
bool bz[100005];
vector<int>g[100005];
vector<int>t[55][55];
int S = 47;
void init()
{
	mu[1] = 1;
	phi[1] = 1;
	fo(i,2,100000,1)
	{
		if(!bz[i])mu[i] = -1,phi[i] = i - 1,p[++ p[0]] = i;
		fo(j,1,p[0],1)
		{
			if(p[j] * i > 100000)break;
			bz[p[j] * i] = 1;
			if(i % p[j] == 0)
			{
				mu[i * p[j]] = 0;
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
			mu[i * p[j]] = mu[i] * mu[p[j]];
			phi[i * p[j]] = phi[i] * phi[p[j]];
		}
	}
	fo(i,1,100000,1)
	{
		fo(j,1,100000 / i,1)
		{
			sigma[i * j] += i;
		}
	}
	fo(i,1,100000,1)
	{
		g[i].push_back(0);
		fo(j,1,100000 / i,1)
		{
			g[i].push_back((phi[i * j] * sigma[j] + g[i][j - 1]) % mod);
		}
	}
	fo(i,1,S,1)
	{
		fo(j,1,S,1)
		{
			t[i][j].push_back(0);
			for(int k = 1;100000 / k >= max(i,j);++ k)
			{
				t[i][j].push_back((t[i][j][k - 1] + ((((k * mu[k] * g[k][i]) % mod) * g[k][j]) % mod)) % mod);
			}
		}
	}
}
int read() {
	char ch = getchar();
	int x = 0,f = 1;
  	while (ch < '0' || ch > '9') 
  	{
  	    if (ch == '-') f = -1;
  	    ch = getchar();
  	}
  	while ('0' <= ch && ch <= '9') x = x * 10 + ch - '0',ch = getchar();
  	return x * f;
}
void print(int x){
    if(x < 0){
        putchar('-');
        x *= -1;
    }
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	init();
	T = read();
	while(T --)
	{
		n = read(),m = read();
		if(n > m)swap(n,m);
		int i = 1;
		int ans = 0;
		while(i <= m / S)
		{
			ans += (((i * mu[i] * g[i][n / i]) % mod) * g[i][m / i]) % mod;
			ans %= mod;
			++ i;
		}
		while(i <= n)
		{
			int j = min(n / (n / i),m / (m / i));
			ans += t[n / i][m / i][j] - t[n / i][m / i][i - 1];
			ans %= mod;
			i = j + 1;
		}
		print((ans + mod) % mod);
		putchar('\n');
	}
	return 0;
}

```

---

## 作者：sheep65536 (赞：3)

不妨设 $n\le m$，$N$ 表示 $n,m$ 的上界。

有一个经典结论：$\sigma(ij)=\sum_{d\mid i}\sum_{k\mid j}\frac{ik}d[\gcd(d,k)=1]$。

证明的话考虑每个质因子 $p$，在 $i,d,k$ 中分别出现 $c_1,c_2,c_3$ 次，则在 $\frac{ik}d$ 中出现 $c_1-c_2+c_3$ 次，并由限制条件可得 $\min(c_2,c_3)=0$，容易发现，$c_1-c_2+c_3$ 会将 $0\sim v_p(ij)$ 都覆盖恰好一次，将所有质因子乘起来一起算就能得到所有约数。
$$
\begin{aligned}
\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sigma(ij)
&=\sum_{i=1}^n\varphi(i)i\sum_{j=1}^m\varphi(j)\sum_{d\mid i}\sum_{k\mid j}\frac{k}d[\gcd(d,k)=1]
\\&=\sum_{d=1}^n(\sum_{i=1}^{\lfloor\frac nd\rfloor}\varphi(id)i)\sum_{k=1}^mk(\sum_{j=1}^{\lfloor\frac mk\rfloor}\varphi(jk))[\gcd(d,k)=1]
\\&=\sum_{p=1}^n\mu(p)(\sum_{d=1}^{\lfloor\frac np\rfloor}(\sum_{i=1}^{\lfloor\frac n{dp}\rfloor}\varphi(idp)i))(\sum_{k=1}^{\lfloor\frac mp\rfloor}kp(\sum_{j=1}^{\lfloor\frac m{kp}\rfloor}\varphi(jkp)))
\\&=\sum_{p=1}^n\mu(p)p(\sum_{d=1}^{\lfloor\frac np\rfloor}(\sum_{i=1}^{\lfloor\frac n{dp}\rfloor}\varphi(idp)i))(\sum_{k=1}^{\lfloor\frac mp\rfloor}k(\sum_{j=1}^{\lfloor\frac m{kp}\rfloor}\varphi(jkp)))
\\&=\sum_{p=1}^n\mu(p)p(\sum_{d=1}^{\lfloor\frac np\rfloor}(\sum_{i=1}^{\lfloor\frac n{dp}\rfloor}\varphi(idp)i))(\sum_{j=1}^{\lfloor\frac mp\rfloor}(\sum_{k=1}^{\lfloor\frac m{jp}\rfloor}\varphi(jkp)k))
\end{aligned}
$$
设：
$$
\begin{aligned}
g(p,q)&=\sum_{i=1}^p\sum_{j=1}^{\lfloor\frac pi\rfloor}\varphi(ijq)j
\\&=\sum_{T=1}^p\varphi(Tq)\sigma(T)
\\&=g(p-1,q)+\varphi(pq)\sigma(p)
\end{aligned}
$$

$$
ans=\sum_{p=1}^n\mu(p)pg(\lfloor\frac np\rfloor,p)g(\lfloor\frac mp\rfloor,p)
$$

显然整除分块，但发现 $g$ 中有 $p$，考虑平衡。

设置阈值 $S$，对于 $\lfloor\frac np\rfloor,\lfloor\frac mp\rfloor\le S$ 的 $\mu(p)pg(\lfloor\frac np\rfloor,p)g(\lfloor\frac mp\rfloor,p)$ 进行预处理。考虑枚举 $\frac mp$，显然 $\frac np\le\frac mp,p\le\frac m{\frac mp}$ 发现可以做到
$$
O(\sum_{i=1}^Si\frac Ni)=O(NS)
$$
对于 $\lfloor\frac mp\rfloor>S$，容易发现 $p\le\frac m{S+1}$，直接计算。

总复杂度为 $O(NS+T\sqrt N+\frac{TN}S)$，$S$ 取 $O(\sqrt T)$ 时有最优复杂度 $O(N\sqrt T+T\sqrt N)$。

---

## 作者：fydj (赞：2)

数论题。

考虑经典结论 $\sigma (ij)=\sum_{x|i}\sum_{y|j}\frac{iy}{x}[\gcd(x,y)=1]$。这是因为对于每个因数的每个质因子考虑，如果 $i$ 中的质因子足够，那么就使用 $i$ 的，即 $\frac{i}{x}$，此时 $y$ 中它的指数为 $0$；如果不够，就额外使用 $j$ 的，即 $iy$，此时 $x$ 中它的指数为 $0$。

接下来就是推式子（假设 $n\le m$）：
$$
\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sigma(ij)\\
=&\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sum_{x|i}\sum_{y|j}\frac{iy}{x}[\gcd(x,y)=1]\\
=&\sum_{i=1}^n\sum_{j=1}^m\varphi(i)\varphi(j)\sum_{x|i}\sum_{y|j}\frac{iy}{x}\sum_{u|x,u|y}\mu(u)\\
=&\sum_{u=1}^{n}\mu(u)\sum_{x=1}^{\lfloor n/u\rfloor}\sum_{y=1}^{\lfloor m/u\rfloor}\sum_{i=1}^{\lfloor n/ux\rfloor}\sum_{j=1}^{\lfloor m/uy\rfloor}\varphi(iux)\varphi(juy)iux\frac y x\\
=&\sum_{u=1}^nu\mu(u)(\sum_{x=1}^{\lfloor n/u\rfloor}\sum_{i=1}^{\lfloor n/ux\rfloor}\varphi(iux)i)(\sum_{j=1}^{\lfloor m/u\rfloor}\sum_{y=1}^{\lfloor m/uj\rfloor}\varphi(juy)y)
\end{aligned}
$$
观察到两个括号内的形式是一样的。设 $f(n,u)=\sum_{x=1}^{n}\sum_{i=1}^{\lfloor n/u\rfloor}\varphi(ixu)i=\sum_{T=1}^n\varphi(Tu)\sigma(T)$，则 $u$ 相同的 $f$ 可以递推，这部分是 $\mathcal O(n\ln n)$ 的。

原式转换为 $\sum_{u=1}^n u\mu(u)f(\lfloor \frac n u \rfloor,u)f(\lfloor \frac m u \rfloor,u)$。

观察到当 $u$ 很小的时候 $\lfloor \frac m u\rfloor$ 很大，但是当 $u$ 很大的时候 $\lfloor \frac n u\rfloor$ 和 $\lfloor \frac m u \rfloor$ 都很小，可以联想到根号分治。

取 $B=\sqrt n$，当 $u\le B$ 时直接暴力，当 $u>B$ 时快速计算。

当 $u>\sqrt n$ 时，$\lfloor\frac m u\rfloor \le \sqrt n$，那么可以预处理出 $g(x,y,m)=\sum_{u=1}^m u\mu(u)f(x,u)f(y,u)$ 从而快速计算。由于 $y\le \sqrt n$，$xn'\le n$，这部分的时间复杂度是 $\mathcal O(n\sqrt n)$ 的。

这样本题就做完了。

实现中可以使用 vector 以优化空间，代码如下：

```cpp
int T,n,m,su[N]={},mu[N]={},phi[N]={},d[N]={}; bool flag[N]={};
vector<int> f[N],g[B+5][B+5];
int main()
{
	int i,j,k,l,r,ans;
	mu[1]=phi[1]=1;
	for(i=2;i<=100000;++i) {
		if(!flag[i]) su[++su[0]]=i,mu[i]=moder-1,phi[i]=i-1;
		for(j=1;j<=su[0]&&i*su[j]<=100000;++j) {
			flag[i*su[j]]=true;
			if(!(i%su[j])) {
				phi[i*su[j]]=phi[i]*su[j];
				mu[i*su[j]]=0;
				break;
			} else {
				phi[i*su[j]]=phi[i]*(su[j]-1);
				mu[i*su[j]]=sub(0,mu[i]);
			}
		}
	}
	for(i=1;i<=100000;++i)
		for(j=i;j<=100000;j+=i)
			d[j]+=i;
	vector<int>(100001,0).swap(f[0]);
	for(i=1;i<=100000;++i)
		vector<int>(100000/i+1,0).swap(f[i]);
	for(j=1;j<=100000;++j) {
		for(i=1;i*j<=100000;++i)
			f[i][j]=(f[i-1][j]+(ll)phi[i*j]*d[i])%moder;
	}
	for(i=1;i<=B;++i)
		for(j=i;j<=B;++j) {
			vector<int>(100000/j+1,0).swap(g[i][j]);
			for(k=1;j*k<=100000;++k)
				g[i][j][k]=(g[i][j][k-1]+(ll)k*mu[k]%moder*f[i][k]%moder*f[j][k])%moder;
		}
	read(T);
	loop : --T;
	read(n,m);
	if(n>m) swap(n,m);
	for(l=1,ans=0;l<=n;l=r+1) {
		r=min(n/(n/l),m/(m/l));
		if(m/l<=B) Add(ans,sub(g[n/l][m/l][r],g[n/l][m/l][l-1]));
		else {
			for(i=l,j=n/l,k=m/l;i<=r;++i)
				Add(ans,(ll)f[j][i]*f[k][i]%moder*i%moder*mu[i]%moder);
		}
	}
	printf("%d\n",ans);
	if(T) goto loop;
	return 0;
}
```

---

## 作者：__NULL1F1CAT10N__ (赞：2)

显然先推式子。

$\begin{aligned}\sum\limits_{i=1}^n\sum\limits_{j=1}^m\varphi(i)\varphi(j)\sigma(ij)&=\sum\limits_{i=1}^n\sum\limits_{j=1}^m\varphi(i)\varphi(j)\sum\limits_{k|i,k|j}\sigma(\frac{i}{k})\sigma(\frac{j}{k})k\mu(k)\\&=\sum\limits_{k=1}^{\min(n,m)}k\mu(k)(\sum\limits_{k|i,i\le n}\varphi(i)\sigma(\frac{i}{k}))(\sum\limits_{k|j,j\le m}\varphi(j)\sigma(\frac{j}{k}))\end{aligned}$

第一个等号的证明：

$k$ 必须为若干不同素数的乘积才能够提供非零值。设 $i=\prod\limits_{x=1}^m p_x^{\alpha_x}\prod\limits_{x=1}^sq_x^{\gamma_x},j=\prod\limits_{x=1}^m p_x^{\beta_x}\prod\limits_{x=1}^tr_x^{\delta_x}$，则 $k=\prod\limits_{x=1}^mp_x^{\theta_x}$，其中 $\theta_x=0$ 或 $1$。

$\begin{aligned}\sum\limits_{k|i,k|j}\sigma(\frac{i}{k})\sigma(\frac{j}{k})k\mu(k)&=\sum\limits_{k|i,k|j}\prod\limits_{x=1}^m\dfrac{(p_x^{\alpha_x+1-\theta_x}-1)(p_x^{\beta_x+1-\theta_x}-1)}{(p_x-1)^2}\prod\limits_{x=1}^s\dfrac{q_x^{\gamma_x+1}-1}{q_x-1}\prod\limits_{x=1}^t\dfrac{r_x^{\delta_x+1}-1}{r_x-1}\prod\limits_{x=1}^m(-p_x)^{\theta_x}\\&=\prod\limits_{x=1}^s\dfrac{q_x^{\gamma_x+1}-1}{q_x-1}\prod\limits_{x=1}^t\dfrac{r_x^{\delta_x+1}-1}{r_x-1}\prod_{x=1}^m\dfrac{\sum\limits_{\theta=0}^1(p_x^{\alpha_x+1-\theta}-1)(p_x^{\beta_x+1-\theta}-1)(-p_x)^{\theta}}{(p_x-1)^2}\\&=\prod\limits_{x=1}^s\dfrac{q_x^{\gamma_x+1}-1}{q_x-1}\prod\limits_{x=1}^t\dfrac{r_x^{\delta_x+1}-1}{r_x-1}\prod_{x=1}^m\dfrac{p_x^{\alpha_x+\beta_x+1}-1}{p_x-1}\\&=\sigma(ij)\end{aligned}$

第二个等号仅为交换求和顺序。现在我们可以预处理 $\sum\limits_{k|i,i\le n}\varphi(i)\sigma(\frac{i}{k})$，注意到其只与 $k$ 和 $\lfloor\frac{n}{k}\rfloor$ 的值有关，时空复杂度 $O(n\ln n)$，并记作 $f(k,\lfloor\frac{n}{k}\rfloor)$。

同时我们可以发现在 $k$ 很大的时候，$\lfloor\frac{n}{k}\rfloor$ 可以取到的值很少，采用整除分块的思想，设定阈值 $B$，当 $\lfloor\frac{\min(n,m)}{k}\rfloor\le B$ 时，将求和式改为前缀和，预处理 $k\mu(k)f(k,X)f(k,Y)$ 的前缀和，其中 $X,Y\le B$，时空复杂度 $O(B^2n)$。

剩余直接计算的 $k$ 共有 $O(\frac{n}{B})$ 个。总时间复杂度 $O(B^2n+\frac{1}{B}Tn)$，取 $B=T^{\frac{1}{3}}$，有时空复杂度 $O(T^{\frac{2}{3}}n)$，足以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int T, n, m;
int non_sq[100005];
int phi[100005], mobius[100005], sigma[100005];
bool isprime[100005];
int prime[50005], pcnt;
bool issq[100005];
int nsq;
void do_prime() {
	for(int i = 2; i <= 100000; ++i) {
		if(!isprime[i]) prime[++pcnt] = i;
		for(int j = 1; j <= pcnt && i * prime[j] <= 100000; ++j) {
			isprime[i * prime[j]] = 1;
			if(i % prime[j] == 0) break;
		}
	}
	for(int i = 1; i <= 100000; ++i) {
		phi[i] = i;
		int pp = i;
		for(int j = 2; j * j <= pp; ++j) {
			if(pp % j == 0) {
				phi[i] = phi[i] / j * (j - 1);
			}
			while(pp % j == 0) {
				pp /= j;
			}
		}
		if(pp >= 2) {
			phi[i] = phi[i] / pp * (pp - 1);
		}
	}
	for(int i = 2; i <= 500; ++i) {
		for(int j = i * i; j <= 100000; j += i * i) {
			issq[j] = true;
		}
	}
	for(int i = 1; i <= 100000; ++i) {
		if(!issq[i]) non_sq[++nsq] = i;
	}
	for(int i = 1; i <= 100000; ++i) {
		for(int j = i; j <= 100000; j += i) {
			sigma[j] += i;
		}
	}
	for(int i = 1; i <= 100000; ++i) {
		if(issq[i]) continue;
		int pp = i;
		mobius[i] = i;
		for(int j = 2; j * j <= pp; ++j) {
			if(pp % j == 0) {
				pp /= j;
				mobius[i] *= (-1);
			}
		} 
		if(pp >= 2) mobius[i] *= (-1);
	}
}
vector <int> qwq[100005];
int ans;
const int B = 50;
int pre[B][B][100005];
signed main() {
	ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	do_prime();
	for(int i = 1; i <= 100000; ++i) {
		qwq[i].push_back(0);
		for(int j = i; j <= 100000; j += i) {
			qwq[i].push_back((qwq[i].back() + 1ll * phi[j] * sigma[j / i] % mod) % mod);
		}
	}
	for(int i = 0; i < B; ++i) {
		for(int j = 0; j < B; ++j) {
			for(int k = 1; k <= 100000; ++k) {
				if((i >= qwq[k].size() || j >= qwq[k].size())) break;
				pre[i][j][k] = (pre[i][j][k - 1] + 1ll * mobius[k] * qwq[k][i] % mod * qwq[k][j]) % mod;
			}
		}
	}
	while(T--) {
		cin >> n >> m;
		long long ans = 0;
		int mm = min(n, m);
		for(int i = 1, s, t, nxt; i <= mm; ++i) {
			s = n / i, t = m / i;
			if(s < B && t < B) {
				nxt = min(n / s, m / t);
				ans += pre[s][t][nxt] - pre[s][t][i - 1];
				i = nxt;
			}
			else {
				ans += 1ll * mobius[i] * qwq[i][s] % mod * qwq[i][t] % mod;
			}
		}
		cout << (ans % mod + mod) % mod << '\n';
	}
	return 0;
}
```

---

