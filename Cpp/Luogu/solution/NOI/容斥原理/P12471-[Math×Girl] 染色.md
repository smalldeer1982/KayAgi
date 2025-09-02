# [Math×Girl] 染色

## 题目背景

>“等下，米尔嘉，你是什么时候拿到这道题的啊？”我问道。  
>“是中午我去老师办公室的时候，你现在就在这里从零开始思考吧。我到那边去想，再见。”米尔嘉朝我挥挥手，优雅的移到窗边的座位上。我的目光紧紧的追随着米尔嘉，透过窗户，我可以看到凋零的梧桐树，梧桐树的上面是广阔的冬季的蓝天，虽然是个晴天，但是外面看上去还是很冷。

## 题目描述

现在有一张 $a\times a$ 的网格，每个格子只能是黑色或白色。  
请问：对于其中每个 $b\times b$ 的网格，都恰好有 $n$ 个格子是黑色的颜色分布方案有几种？  
_为了不让题目太难，米尔嘉只需要你解决 $n\in\{1,2\}$ 的情况即可。_  

由于答案可能很大，你只需要输出方案数对 $998244353$ 取模后的结果就可以了。  

## 说明/提示

### 样例解释

第一个例子中的 $8$ 种方案分别是：

![样例解释1](https://cdn.luogu.com.cn/upload/image_hosting/b2jppnoc.png)

第三个例子取模前的结果是：$55590605665555221$

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $5$ | $a\in[1,5]$ |
| $1$ | $15$ | $T=10,\text{答案}\in[1,10^6]$ |
| $2$ | $15$ | $T=10,b\le a\le2b\le10^3$ |
| $3$ | $10$ | $n=1,b\mid a$ |
| $4$ | $15$ | $n=1$ |
| $5$ | $15$ | $n=2,b\mid a$ |
| $6$ | $25$ | $n=2$ |

对于 $100\%$ 数据，保证 $T\in[1,10^5],n\in\{1,2\},1\le n\le b^2\le a^2\le (10^{18})^2$。  

## 样例 #1

### 输入

```
8
3 2 1
10 3 1
100 3 1
1145141919810 23333333 1
3 2 2
10 3 2
100 3 2
1145141919810 23333333 2```

### 输出

```
8
261
792303199
491969808
14
16316
968654202
961966479```

# 题解

## 作者：Naszt (赞：12)

# 染色

## 观前提醒

> 以前的网格染色题都弱爆尔，看看我的（

原本这题是为了衔接，为了避免难度 gap 过大。  
但是由于 E 题过于复杂，工作量太大，将其删掉了，  
而且原本的 D 题（C 题）去掉一个比较复杂的技巧后难度就没这么大了，  
所以这题被迫换到了 D 题。  

我只推了 $n\in\{1,2\}$ 的公式。  
如果你有实力，也可以出一出此题的加强版在主题库中。  
如果再加上颜色，就有加强加强版了（

还有一点比较离谱的是这个数列的几乎任何一行都在 OEIS 上找不到。

## 思路分析

## 当 $n=1$ 时

我们先考虑转换一下这个问题，可以在每个黑色格子上补一个 $b\times b$ 的正方形。  
例如这这里是两种合法的铺法：

![](https://cdn.luogu.com.cn/upload/image_hosting/9ssq5btt.png)

显然，这个问题变成了一个正方形的密铺问题。  
那么整体要么呈纵向分布，要么呈横向分布。

我们把一张图状压成一个二进制数字，定义：

$$X=\{x:x\text{的黑色方块呈横向分布}\}$$
$$Y=\{x:x\text{的黑色方块呈纵向分布}\}$$
$$I=X\cap Y$$
$$U=X\cup Y$$
$$ans=|U|=|X|+|Y|-|I|$$

对于集合 $X$ 中的图，只用考虑第一列，即可确定整张图。  
集合 $Y$ 同理，有：

$$|X|=|Y|=a \bmod b \times b^{\lfloor a/b+1 \rfloor} + (b - a \bmod b) \times b^{\lfloor a/b \rfloor}$$
$$|I|=b^2$$

那么就有：

$$ans=2\left(a \bmod b \times b^{\lfloor a/b+1 \rfloor} + (b - a \bmod b) \times b^{\lfloor a/b \rfloor}\right)-b^2$$

## 叠加原理

对于更一般的情况，显然有一个充分条件：
把 $n$ 张 $n=1$ 的网格叠加再一起且没有恰好重叠的黑色。

而这也是个必要条件，即任意张图都可以拆回 $n$ 张图。

### 新定义

于是我们定义两集合的乘法为其中图的叠加，即：

$$AB=\{i|j:i\&j=0,i\in A,j\in B\}$$

_Tips:这里的 `|`，`&` 指的是 按位或，按位与。_

那么：
$$ans=|U^n|$$

## 当 $n=2$ 时

我们可以使用容斥原理：
$$
\begin{aligned}
ans&=|U^2|=|XX\cup XY\cup YY|\\
&=|XX|+|XY|+|YY|-|II|-|XI|-|IY|+|II|\\
&=2|X^2|+|XY|-2|XI|\\
\end{aligned}
$$

### 当 $b\mid a$ 时

以下式子的组合意义比较简单，我就不做详细推导了：

$$B:=\frac{a}{b}$$
$$|X^2|=b\binom{b}{2}^B+\binom{b}{2}b^{2B}$$
$$|I^2|=\binom{b^2}{2}$$

以下式子的组合意义有点复杂，所以我们「代数推导保平安」：

对于集合 $X$ 中的图，因为只用考虑第一列，所以可以用 $B+1$ 个变量表示，也可以知道黑色格子的坐标：

$$K,A_0,A_1,\dots,A_{B-1}\in[0,b-1]\quad\text{坐标: }(bi+A_j,bj+K)$$

_Tips:从零开始标号。_  

同理，集合 $Y$ 中的图也可以这么表示：

$$K,A_0,A_1,\dots,A_{B-1}\in[0,b-1]\quad\text{坐标: }(bi+K,bj+A_i)$$

那么我们就可以暴力的进行代数推导了：

$$
\begin{aligned}
|XY|
&=\sum_{\substack{K^{[1]},A^{[1]}_0,A^{[1]}_1,\dots,A^{[1]}_{B-1}\in[0,b-1]\\[3pt]K^{[2]},A^{[2]}_0,A^{[2]}_1,\dots,A^{[2]}_{B-1}\in[0,b-1]}}\left(\prod_{i,j\in[0,B-1]}\left[(bi+A^{[1]}_j,bj+K^{[1]})\not=(bi+K^{[2]},bj+A^{[2]}_i)\right]\right)-|I^2|\\
&=\sum_{\dots}\left(\prod_{i,j}\left[A^{[1]}_j\not=K^{[2]}\right]\lor\left[A^{[2]}_i\not=K^{[1]}\right]\right)-\binom{b^2}{2}\\
&=\sum\left(\left[\forall A^{[1]}\not=K^{[2]}\right]\lor\left[\forall A^{[2]}\not=K^{[1]}\right]\right)-\binom{b^2}{2}\\
&=\sum\left(\left[\forall A^{[1]}\not=K^{[2]}\right]+\left[\forall A^{[2]}\not=K^{[1]}\right]-\left[\forall A^{[1]}\not=K^{[2]}\right]\left[\forall A^{[2]}\not=K^{[1]}\right]\right)-\binom{b^2}{2}\\
&=b^2\left(2b^B(b-1)^B-(b-1)^{2B}\right)-\binom{b^2}{2}\\
\end{aligned}
$$

按照类似的推导过程，有：

$$
\begin{aligned}
|XI|&=\sum\left(\left[A^{[1]}\not=K^{[2]}\right]+\left[A^{[1]}=K^{[2]}\right]\left[\forall A^{[2]}\not=K^{[1]}\right]\right)-\binom{b^2}{2}\\
&=b^2\left((b-1)b^B+(b-1)^B\right)-\binom{b^2}{2}
\end{aligned}
$$

不过这个式子的组合意义还算比较简单：  
首先先确定属于 $I$ 的图，共有 $b^2$ 种可能。  
另一张图要么始终和这张图纵向分布的列相同，要么不是。  
再减去 $|I^2|$ 种重复的情况即可。

那么就有：

$$ans=2\left(b\binom{b}{2}^B+\binom{b}{2}b^{2B}\right)+b^2\left(2b^B(b-1)^B-(b-1)^{2B}\right)+\binom{b^2}{2}-2b^2\left((b-1)b^B+(b-1)^B\right)$$

### 当 $b\nmid a$ 时

$$B:=\left\lfloor\frac{a}{b}\right\rfloor,T:=a\bmod b$$
$$\therefore bB+T=a$$

对于集合 $X$ 或 $Y$ 中的一张图，  
当 $K<T$ 时，要用到 $B+2$ 个变量；  
当 $K\ge T$ 时，要用到 $B+1$ 个变量。

于是我们可以分类讨论，稍加修改 $b\mid a$ 时的答案即可：

$$
\begin{aligned}
|X^2|&=T\binom{b}{2}^{B+1}+(b-T)\binom{b}{2}^B\\
&+\binom{T}{2}b^{2B+2}+T(b-T)b^{2B+1}+\binom{b-T}{2}b^{2B}
\end{aligned}
$$

$$
\begin{aligned}
|XY|&=T^2\left(2b^{B+1}(b-1)^{B+1}-(b-1)^{2B+2}\right)\\
&+2T(b-T)\left(b^B(b-1)^{B+1}+b^{B+1}(b-1)^B-(b-1)^{2B+1}\right)\\
&+(b-T)^2\left(2b^B(b-1)^B-(b-1)^{2B}\right)\\
&-\binom{b^2}{2}
\end{aligned}
$$

$$
\begin{aligned}
|XI|&=bT\left((b-1)b^{B+1}+(b-1)^{B+1}\right)\\
&+b(b-T)\left((b-1)b^B+(b-1)^B\right)\\
&-\binom{b^2}{2}
\end{aligned}
$$

那么就有：

$$
\begin{aligned}
ans&=2\left(T\binom{b}{2}^{B+1}+(b-T)\binom{b}{2}^B\right)\\
&+2\left(\binom{T}{2}b^{2B+2}+T(b-T)b^{2B+1}+\binom{b-T}{2}b^{2B}\right)\\
&+T^2\left(2b^{B+1}(b-1)^{B+1}-(b-1)^{2B+2}\right)\\
&+2T(b-T)\left(b^B(b-1)^{B+1}+b^{B+1}(b-1)^B-(b-1)^{2B+1}\right)\\
&+(b-T)^2\left(2b^B(b-1)^B-(b-1)^{2B}\right)\\
&+\binom{b^2}{2}\\
&-2bT\left((b-1)b^{B+1}+(b-1)^{B+1}\right)\\
&-2b(b-T)\left((b-1)b^B+(b-1)^B\right)\\
\end{aligned}
$$

~~我相信没人会打算化简它的。~~

## 代码实现

### 数值计算

以下代码可以进行数值计算，  
$a,b$ 作为宏定义放在了 $2,3$ 行。

计算方法是暴力计算，如果你想推 $n\ge3$ 时的公式，可以用来验算公式。

```cpp
#include<bits/stdc++.h>
#define a 6
#define b 3
typedef unsigned long long i8;
typedef std::bitset<a*a> MAP;
typedef std::unordered_set<MAP> SET;
SET X,Y,U,I;//X,Y,并,交
inline i8 p(i8 x,i8 y){return x+a*y;}
inline void out(MAP x){
	std::cout<<"\n";
	for(i8 i=0;i!=a;i++){
		for(i8 j=0;j!=a;j++)
			std::cout<<x[p(i,j)];
		std::cout<<"\n";
	}
	std::cout<<"\n";
}
inline SET S_intersection(const SET&A,const SET&B){
	SET V;
	for(auto i:A)
		if(B.count(i))V.insert(i);
	return V;
}
inline SET S_union(const SET&A,const SET&B){
	SET V=A;
	V.insert(B.begin(),B.end());
	return V;
}
inline SET operator *(const SET&A,const SET&B){
	SET V;
	for(auto i:A){
		for(auto j:B){
			if((i&j).count())continue;
			V.insert(i|j);
		}
	}
	return V;
}
int main(){
	for(i8 k=0;k<b;k++){
		for(i8 x=0;x<=i8(pow(b,a/b+1));x++){
			MAP node;
			for(i8 v=x,t1=0;b*t1+k<a;t1++,v/=b){
				for(i8 t2=0;v%b+b*t2<a;t2++)
					node[p(v%b+b*t2,b*t1+k)]=1;
			}
			X.insert(node);
		}
	}
	for(i8 k=0;k<b;k++){
		for(i8 x=0;x<=i8(pow(b,a/b+1));x++){
			MAP node;
			for(i8 v=x,t1=0;b*t1+k<a;t1++,v/=b){
				for(i8 t2=0;v%b+b*t2<a;t2++)
					node[p(b*t1+k,v%b+b*t2)]=1;
			}
			Y.insert(node);
		}
	}
	I=S_intersection(X,Y);
	U=S_union(X,Y);
	
//	for(auto i:X)out(i);
	std::cout<<"|U|="<<U.size()<<"\n";
	std::cout<<"|X|="<<X.size()<<"\n";
	std::cout<<"|Y|="<<Y.size()<<"\n";
	std::cout<<"|I|="<<I.size()<<"\n";
	std::cout<<"|X|+|Y|-|I|="<<X.size()+Y.size()-I.size()<<"\n";
	std::cout<<"\n";
	std::cout<<"|U*U|="<<(U*U).size()<<"\n";
	std::cout<<"|X*X|="<<(X*X).size()<<"\n";
	std::cout<<"|X*Y|="<<(X*Y).size()<<"\n";
	std::cout<<"|Y*Y|="<<(Y*Y).size()<<"\n";
	std::cout<<"|X*I|="<<(X*I).size()<<"\n";
	std::cout<<"|I*Y|="<<(I*Y).size()<<"\n";
	std::cout<<"|I*I|="<<(I*I).size()<<"\n";
	
	return 0;
}
```

### 出题人代码

```cpp
#include<bits/stdc++.h>
typedef unsigned long long i8;
const i8 P=998244353;
i8 fpow(i8 a,i8 n){
  if(!a)return 0;i8 ans=1;
  for(n%=P-1;n;n>>=1,(a*=a)%=P)if(n&1)(ans*=a)%=P;
  return ans;
}
i8 slove(){
  i8 a,b,n,ans=0;
  std::cin>>a>>b>>n;
  i8 B=a/b%(P-1),T=a%b%P,b_T=(b%P+P-T)%P;
  a%=P,b%=P;
  i8 bb=b*b%P,bpB=fpow(b,B);
  if(n==1)return (2*(T*bpB%P*b+b_T*bpB)+P-bb)%P;
  i8 bC2=b*(b-1)/2%P,TC2=T*(T-1)/2%P,b_TC2=b_T*(b_T-1)/2%P;
  i8 Tb_T=T*b_T%P,TT=T*T%P,b_Tb_T=b_T*b_T%P,b_1=(b+P-1)%P;
  i8 bC2pB=fpow(bC2,B),b_1pB=fpow(b_1,B);
  i8 bpB1=bpB*b%P,b_1pB1=b_1pB*b_1%P;
  i8 bp2B=bpB*bpB%P,bp2B1=bp2B*b%P,bp2B2=bp2B1*b%P;
  i8 b_1p2B=b_1pB*b_1pB%P,b_1p2B1=b_1p2B*b_1%P,b_1p2B2=b_1p2B1*b_1%P;
  ans=(ans+2*(T*bC2pB%P*bC2+b_T*bC2pB)%P)%P;
  ans=(ans+2*(TC2*bp2B2+Tb_T*bp2B1+b_TC2*bp2B))%P;
  ans=(ans+TT*(2*bpB1*b_1pB1%P+P-b_1p2B2))%P;
  ans=(ans+2*Tb_T*((bpB*b_1pB1+bpB1*b_1pB)%P+P-b_1p2B1))%P;
  ans=(ans+b_Tb_T*(2*bpB*b_1pB%P+P-b_1p2B))%P;
  ans=(ans+bb*(bb-1)/2)%P;
  ans=(ans+P-2*b*T%P*(b_1*bpB1%P+b_1pB1)%P)%P;
  ans=(ans+P-2*b*b_T%P*(b_1*bpB%P+b_1pB)%P)%P;
  return ans;
}
int main(){
  std::ios::sync_with_stdio(0);
  std::cin.tie(0),std::cout.tie(0);
  i8 T;std::cin>>T;
  while(T--)std::cout<<slove()<<"\n";
  return 0;
}
```

### 验题人代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std; 

ll Read(){
  ll res = 0; char c = getchar();
  while(c < '0' || c > '9') c = getchar();
  while(c >= '0' && c <= '9') res = res * 10 + c - 48, c = getchar();
  return res;
}

const int Mod = 998244353, Nod = Mod - 1;

ll a, b, B, T; // < 10 ^ 9
// B = a // b, T = a mod b

ll FastPow(ll x, int y = B){ // return x^y		x < Mod
  if(!x) return 0;
  int res = 1;
  while(y){
    if(y & 1) res = res * x % Mod;
    y >>= 1, x = x * x % Mod;
  }
  return res;
}

ll Easy(){
  ll ans = (2 * (b * T + b - T) % Mod * FastPow(b) - b * b) % Mod;
  return ans < 0 ? ans + Mod : ans;
}

ll Binom(ll x){ return (x * (x - 1) / 2) % Mod;} // x < Mod
ll Hard(){
  ll bbp = FastPow(Binom(b)); // binom(b) ^ B
  ll bbp1 = bbp * Binom(b) % Mod; // binom(b) ^ (B + 1)
  ll bp = FastPow(b); // b ^ B
  ll bp1 = bp * b % Mod; // b ^ (B + 1)
  ll bps = bp * bp % Mod; // b ^ 2B
  ll bps1 = bp * bp1 % Mod; // b ^ (2B + 1)
  ll bps2 = bp1 * bp1 % Mod; // b ^ (2B + 2)
  ll ans1 = (T * bbp1 % Mod + (b - T) * bbp + Binom(T) * bps2 + T * (b - T) % Mod * bps1 + Binom(b - T) * bps) % Mod;
  ll c = b - 1;
  ll cp = FastPow(c); // (b - 1) ^ B
  ll cp1 = cp * c % Mod; // (b - 1) ^ (B + 1)
  ll cps = cp * cp % Mod; // (b - 1) ^ 2B
  ll cps1 = cp * cp1 % Mod; // (b - 1) ^ (2B + 1)
  ll cps2 = cp1 * cp1 % Mod; // (b - 1) ^ (2B + 2)
  ll bsm = Binom(b * b % Mod); // binom(b ^ 2)
  ll ans2 = (T * T % Mod * ((2 * bp1 * cp1 - cps2) % Mod) + 2 * T * (b - T) % Mod * ((bp * cp1 + bp1 * cp - cps1) % Mod) + (b - T) * (b - T) % Mod * ((2 * bp * cp - cps) % Mod) - bsm) % Mod;
  ll ans3 = (((c * bp1 + cp1) % Mod * T + (c * bp + cp) % Mod * (b - T)) % Mod * b - bsm) % Mod;
  ll ans = (2 * ans1 + ans2 - 2 * ans3) % Mod;
  return ans < 0 ? ans + Mod : ans;
}

int main(){
  int tt = Read();
  while(tt--){
    a = Read(), b = Read();
    B = (a / b) % Nod, T = (a % b) % Mod;
    a %= Mod, b %= Mod;
    int op = Read();
    if(op == 1) printf("%lld\n", Easy());
    else printf("%lld\n", Hard());
  }
  return 0;
}
```

---

