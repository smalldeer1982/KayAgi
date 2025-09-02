# Bots

## 题目描述

Sasha and Ira are two best friends. But they aren’t just friends, they are software engineers and experts in artificial intelligence. They are developing an algorithm for two bots playing a two-player game. The game is cooperative and turn based. In each turn, one of the players makes a move (it doesn’t matter which player, it's possible that players turns do not alternate).

Algorithm for bots that Sasha and Ira are developing works by keeping track of the state the game is in. Each time either bot makes a move, the state changes. And, since the game is very dynamic, it will never go back to the state it was already in at any point in the past.

Sasha and Ira are perfectionists and want their algorithm to have an optimal winning strategy. They have noticed that in the optimal winning strategy, both bots make exactly $ N $ moves each. But, in order to find the optimal strategy, their algorithm needs to analyze all possible states of the game (they haven’t learned about alpha-beta pruning yet) and pick the best sequence of moves.

They are worried about the efficiency of their algorithm and are wondering what is the total number of states of the game that need to be analyzed?

## 说明/提示

Start: Game is in state A.

- Turn 1: Either bot can make a move (first bot is red and second bot is blue), so there are two possible states after the first turn – B and C.
- Turn 2: In both states B and C, either bot can again make a turn, so the list of possible states is expanded to include D, E, F and G.
- Turn 3: Red bot already did N=2 moves when in state D, so it cannot make any more moves there. It can make moves when in state E, F and G, so states I, K and M are added to the list. Similarly, blue bot cannot make a move when in state G, but can when in D, E and F, so states H, J and L are added.
- Turn 4: Red bot already did N=2 moves when in states H, I and K, so it can only make moves when in J, L and M, so states P, R and S are added. Blue bot cannot make a move when in states J, L and M, but only when in H, I and K, so states N, O and Q are added.

Overall, there are 19 possible states of the game their algorithm needs to analyze.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF575H/fe492a4b59f95857f16ee99d37e8da94ed083cf9.png)

## 样例 #1

### 输入

```
2
```

### 输出

```
19
```

# 题解

## 作者：Siegerkranz_2735 (赞：4)

#### 前置知识

差分运算：

$$\Delta f(x)=f(x+1)-f(x)$$

定和式：

$$\Sigma_{a}^{b}f(x)\delta x=\sum_{k=a}^{b-1}f(k)$$

$$\Sigma_{a}^{b}\Delta f(x)\delta x=f(b)-f(a)$$

下降幂：

$$x^{\underline{n}}=\begin{cases}
  x(x-1)(x-2)\dots(x-n+1) & (x >0) \\
  1 & (x=0) \\
  \frac{1}{(x+1)(x+2)\dots(x-n)} & (x <0)
\end{cases}$$

$$x^{\underline{n}}=\Delta (\frac{x^{\underline{n+1}}}{n+1})$$

#### 正文

可以把它想象成网格，起点在红点 $(0,0)$。如果是 $A$ 机器人走就是向上，如果是 $B$ 机器人走就向右。最终走到 $(n,n)$，题目要求的就是所有到达 $(n,n)$ 的路径经过的点的到达方案数之和。

对于任意一点 $(i,j)$ 他从 $(0,0)$ 到达他的路径个数是 $C_{i+j}^{i}$（或者  $C_{i+j}^{j}$）所以答案就是 $\sum_{i=0}^{n}\sum_{j=0}^nC_{i+j}^i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ejobak8e.png)

$$\begin{aligned}
\sum_{i=0}^{n}\sum_{j=0}^nC_{i+j}^i&=\sum_{i=0}^{n}\sum_{j=0}^n\frac{(i+j)^{\underline{i}}}{i!}\\

&=\sum_{i=0}^{n}\sum_{j=i}^{n+i}\frac{j^{\underline{i}}}{i!}\\

&=\sum_{i=0}^{n}\frac{1}{i!}\sum_{j=i}^{n+i}j^{\underline{i}}\\

&=\sum_{i=0}^{n}\frac{\Sigma_{i}^{n+i+1}x^{\underline{i}}\delta x}{i!}\\

&=\sum_{i=0}^{n}\frac{\Sigma_{i}^{n+i+1}\Delta(\frac{x^{\underline{i+1}}}{i+1})^{\underline{i}}\delta x}{i!}\\

&=\sum_{i=0}^{n}\frac{1}{i!}\frac{(n+i+1)^{\underline{i+1}}-i^{\underline{i+1}}}{i+1}\\

&=\sum_{i=0}^{n}\frac{(n+i+1)^{\underline{i+1}}}{(i+1)!}\\

&=\sum_{i=0}^{n}C_{i+n+1}^{i+1}\\

&=\sum_{i=1}^{n+1}C_{i+n}^{n}\\
\end{aligned}$$

同理可得（现在的格式和一开始的时候是一样的）：

$$\sum_{i=1}^{n+1}C_{i+n}^{n}=C_{2n+2}^{n+1}-C_{n}^{n}=C_{2n+2}^{n+1}-1$$

然后乘法逆元就结束了。

---

## 作者：yuanzhiteng (赞：2)

~~前言 : 如有笔误 , 期以不吝赐教 , 增鄙之博识也 。~~       
### 一. 题目大意   
给定一个正整数 $n(1\le n\le 10^6)$，若两个机器人每回合可以任一方走一步，任一方最多走 $n$ 步，求所有状态数 $\bmod\ 10^9+7$。     
   
---    
### 二. 题目转换   
观察题目后不难发现两个机器人**均走且仅走 $n$ 步**，与它们走的顺序无关。   
因此联想到**在网格图上从 $(0,0)$ 走到 $(n,n)$ 的方案数**。  
我们只需要令向右走一步代表红色机器人走一步，向上走一步代表蓝色机器人走一步即可。    
    
但还有一个问题，题目求的是总状态数，如何办 ?  
不难发现，对于 $(n,n)$ 以内的任意一个格点 $(i,j)$   
即红色共走 $i$ 步，蓝色共走 $j$ 步所到达的状态。   
但由于走的顺序是不一定的，   
因此**从 $(0,0)$ 走到 $(i,j)$ 的方案总数便是红色共走 $i$ 步，蓝色共走 $j$ 步所包含的状态总数** （借助图可以理解一下）。   
     
而由组合知识可以知道，从 $(0,0)$ 走到 $(i,j)$ 的方案总数 = $C_{i+j}^i$。    
故题目可以转换为：   
$$\sum_{i=0}^n \sum_{j=0}^n C_{i+j}^i$$     
    
----  
### 三. 组合恒等式的应用   
接下来就是纯数学知识了，考察对组合式化简的熟悉程度。   
先考虑第二个 $\sum$ 的化简。   
     
##### **法一 . 组合恒等式**   
$\because \sum_{k=0}^{i-1} C_{k}^i=0$，故 :    
$$\sum_{j=0}^n C_{i+j}^i = \sum_{k=0}^{n+i} C_{k}^i=C_{n+i+1}^{i+1}$$   
这里用到的是组合恒等式 $11$：   
$$\sum_{i=0}^n C_{j}^m = C_{n+1}^{m+1}$$   
     
##### **法二 . 构造 + 杨辉三角 ( pascal 公式 )**   
由杨辉三角知 :  
$$C_n^m=C_{n-1}^{m-1}+C_{n-1}^m$$   
故 :  
$$\begin{aligned}
\sum_{j=0}^n C_{i+j}^i&=C_{i}^i+C_{i+1}^i+C_{i+2}^i+...+C_{i+n}^i  \\
&=C_{i+1}^{i+1}+C_{i+1}^i+C_{i+2}^i+...+C_{i+n}^i   \\
&=(C_{i+1}^{i+1}+C_{i+1}^i)+C_{i+2}^i+...+C_{i+n}^i  \\
&=C_{i+2}^{i+1}+C_{i+2}^i+...+C_{i+n}^i  \\  
&=...   \\
&=C_{n+i+1}^{i+1}   \\
\end{aligned}$$
     
再考虑第二个 $\sum$ 的化简，跟第一个类似，也有两种方法， 这里给出第一种恒等式的方法：   
$$\begin{aligned}  
\sum_{i=0}^n C_{n+i+1}^{i+1}&=\sum_{i=0}^n C_{n+i+1}^{n}\\    
&=\sum_{k=0}^{2n+1} C_{k}^{n}-C_{n}^{n}  \\ 
&=C_{2n+2}^{n+1}-1 \\
\end{aligned}$$    
   
剩下的就好办了，逆元筛出组合数，直接套公式即可。  

----   
### 四. 代码实现    
~~这就不需要了吧......(雾)~~    
[代码](https://www.luogu.com.cn/paste/wwqovk8h)   

---

## 作者：262620zzj (赞：1)

# 总体框架
每个状态等价于一个红蓝操作的序列，并且所有的状态构成一个二叉树，类似样例解释。如果每个机器人移动次数不限，只要求总共走 $2n$ 步，那么状态数是满二叉树节点数量 $2^{2n+1}-1$，在此基础上减去不合法状态数量就是答案。

# 不合法状态数
可以知道，一个点如果不合法，那么它的子树自然全都不合法。

在这颗二叉树上，不合法其实就是有一个机器人走的步数超过 $n$，那么我们可以枚举一个深度 $i$，找到在第 $i$ 轮**恰好**有机器人的步数超过了 $n$ 的节点，减去以它们为根的子树内所有节点。红色与蓝色操作是对称的，不妨先计算第 $i$ 轮恰好红色操作数超过 $n$ 的情况，再翻倍。既然要正好超过 $n$，那么前 $i-1$ 轮一定有 $n$ 次红色操作，其余为蓝色操作，可以用组合数计算数量。所以不合法状态数量就是
$$2\times\sum_{i=n+1}^{2n}\binom{i-1}{n}\times (2^{2n-i+1}-1)$$
记得预处理一下阶乘计算组合数，还有要计算乘法逆元。时间复杂度 $O(n\log mod)$。

#代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
ll n,ans,fac[2000005]; 
template<typename T>
ll qpow(T a,int b){
	ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
ll C(int n,int k){
	ll res=fac[n]*qpow(fac[n-k],mod-2)%mod;
	res=res*qpow(fac[k],mod-2)%mod;
	return res;
}
int main(){
	fac[0]=1;
	for(int i=1;i<=2000000;i++)fac[i]=fac[i-1]*i%mod;
	cin>>n;
	ans=(qpow(2ll,2*n+1)-1+mod)%mod;
	for(int i=n+1;i<=2*n;i++)
		ans=(ans-C(i-1,n)*(qpow(2ll,2*n-i+1)-1+mod)*2%mod+mod)%mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：qwq___qaq (赞：1)

考虑容斥。

总的情况显然是一棵深度为 $2n+1$ 的满二叉树，那么总的节点数就是 $2^{2n+1}-1$，考虑有哪些情况不符合：

- 对于 $[0,n-1]$ 层，显然不会有步数超过 $n$ 的情况。

- 对于 $[n,2n]$ 层，第 $i$ 层到根节点的边数是 $i$，那么这里面若恰好有 $n$ 个是同一个机器人走的，方案数就是 $C_i^n$，又因为有 $2$ 个机器人，所以还要 $\times2$，那么就有一个儿子不能选，这个儿子是一棵深度为 $2n-i$ 的二叉树，节点数就是 $2^{2n-i}-1$。最后的答案就需要减去 $2C_i^n(2^{2n-i}-1)$。

组合数、$2$ 的幂都可以预处理，时间复杂度 $O(n)$。

---

## 作者：Zack_zhu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF575H)  
## 题目分析
对于题目，我们发现最极端的情况（如 $(0,n)$ 或 $(n,0)$）也会在 $n$ 层前产生两条边，即前 $n$ 层为满二叉树。故前面的 $n$ 层答案为 $\sum_{i=1}^{n}{2^i}$，也可以用 $2^{i+1}-1$ 来计算。  
讨论后 $n$ 层，发现其实只有所有 $i$ 层上选出 $n$ 层走同一个机器人达到限制才会在下一层出现一条边的情况，即这种情况有 $\dbinom{n}{i}$ 个，而剩下的有两个边，设前一层答案为 $cnt$，故每次答案加 $2 \times (cnt - \dbinom{n}{i-1}) + \dbinom{n}{i-1}$ 即 $cnt \times 2 - \dbinom{n}{i-1}$。  
注意：
1. 这里应该用前一层的答案乘二而不是 $2^n$ 来乘二，原因是我们讨论的是前一层有两条边的情况。
2. 这里是 $i-1$ 而不是 $i$，因为现在这层点的个数由上一层的边决定，也就是上一层的点决定。
## 代码
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN = 2e6+5;
const int MOD = 1e9+7;
int n;
ll ans,cnt,c[MAXN];
template <typename T>
inline void read(T &s)
{
      s = 0;
      char ch = getchar();
      while(ch < '0'||ch > '9')
          ch = getchar();
      while(ch >= '0'&&ch <= '9')
      {
          s = (s<<3) + (s<<1) + (ch^48);
          ch = getchar();
      }
      return;
}
inline int inv(int a)
{
      int p = 1,q = 0,b = MOD,c,d;
      while(b>0)
      {
          c = a / b;
          d = a;
          a = b;
          b = d % b;
          d = p;
          p = q;
          q = d - c * q;
      }
      return p < 0 ? p + MOD:p;
}
inline ll qpow(ll x,ll y)
{
      ll ans = 1;
      while(y)
      {
          if(y & 1)
              ans = ans * x % MOD;
          x = x * x % MOD;
          y >>= 1;
      }
      return ans;
}
int main()
{
      read(n);
      c[n] = 1;
      for(int i = n+1;i <= (n<<1);i++)
          c[i] = c[i-1] * i % MOD * inv(i-n) % MOD;
      ans = (qpow(2,n+1) - 1 + MOD) % MOD;
      cnt = qpow(2,n);
      for(int i = n+1;i <= (n << 1);i++)
      {
          cnt = (((cnt - c[i-1] + MOD) % MOD) << 1) % MOD;
          ans = (ans + cnt) % MOD;
      }
      printf("%lld\n",ans);
      return 0;
}
```

---

