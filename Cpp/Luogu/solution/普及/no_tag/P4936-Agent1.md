# Agent1

## 题目背景

2018年11月17日，中国香港将会迎来一场`XM大战`，是世界各地的`ENLIGHTENED`与`RESISTANCE`开战的地点，某地 的`ENLIGHTENED总部`也想派`Agent`去参加这次的`XM大战`，与世界其他地方的`ENLIGHTENED`并肩作战。

## 题目描述

某地的`ENLIGHTENED总部`总部有$N$个`Agent`，每个`Agent`的能力值互不相同，现在`ENLIGHTENED行动指挥`想要派出$A,B$两队`Agent`去参加`XM大战`。但是参加大战的两个队伍要满足两个要求：

1. $A$队中能力最大的`Agent`的能力值要小于$B$队能力最弱的`Agent`的能力值。
2. $A,B$两队都要有人参战。

并不一定所有的`Agent`都要去参加`XM大战`的，心急的`ENLIGHTENED行动指挥`想知道有多少种安排`Agent`参加大战的方案。由于答案可能很大，所以只需要你求出答案模$(10^9+7)$的值就可以了。

## 说明/提示

对于$20\%$的数据 $N \leq 10$

对于$40\%$的数据 $N \leq 10^3$

对于$60\%$的数据 $N \leq 10^5$

对于$100\%$的数据 $N \leq 10^9$

## 样例 #1

### 输入

```
3```

### 输出

```
5```

## 样例 #2

### 输入

```
6```

### 输出

```
129```

# 题解

## 作者：Hiraeth (赞：8)

我说我看着数据想到了通项公式你信吗。。。

这是真的。。

因为这是一条比赛题。。

快速幂取模运算的模板题

~~比赛的时候没有想到用快速幂取模 然后只有20分 手动滑稽~~

我觉得我这应该是全网最短代码

遛了 遛了 

```cpp
#include<bits/stdc++.h>
#define LL long long
#define Mod 1000000007
LL Pow(LL a,LL k){
	if(k==0)
		return 1;
	if(k&1)
		return Pow(a*a%Mod,k/2)*a%Mod;
	return Pow(a*a%Mod,k/2)%Mod;
}
using namespace std;
LL n;
int main (){
	scanf("%lld",&n);
	printf("%lld\n",1ll*(n-2)*Pow(2,n-1)%Mod+1);
	return 0;
}
```

---

## 作者：nth_element (赞：4)

## $\text{Update}$(2019.10.05):

1. 递推公式推法更详细；
2. 通项公式更新详细版；
3. 单位矩阵的推法更加详细。

> 特别鸣谢 @[Smallbasic](https://www.luogu.org/space/show?uid=98096) 苣佬，是他教会了我推递推公式和通项公式。

***

吐槽：来自同机房巨佬的嘲讽——~~这道题这么简单，观察法显然可得通项公式~~

***

## 题目分析：

1. 分析题面，原题意思如下：

   > 从$n$个互不相同的数中取出某些数，将这些数分成两个集合$A,B$，这两个集合满足两个条件：
   >
   > - $ A$集合中的最大的数小于$B$集合中最小的数
   >
   > - $A,B \neq  \emptyset $ 
   >
   > 求共有多少种分法(结果对 $10^9+7$ 取模)
   >

2. 显然可以发现这题是一道组合数学的题，先手算 $n \leq 10$ 的数据，在找规律推出公式。我给一下我的思路：

   1. 当 $n=2$ 时，答案显然为1

   2. 当 $n=3$ 时，设这些数为 $a_1,a_2,a_3$ ,不妨设 $a_1<a_2<a_3$

      1. 当取3个数时，有以下分法：

         $$A=\{a_1 \},B=\{a_2,a_3\}$$

         $$A=\{a_1,a_2\},B=\{a_3\}$$

         共 $C^3_3 \times (3-1)=2$ 种

      2. 当取2个数时，有以下分法：

         $$A=\{a_1\},B=\{a_2\}$$

         $$A=\{a_1\},B=\{a_3\}$$

         $$A=\{a_2\},B=\{a_3\}$$

         共 $C_3^2 \times (2-1)=3$ 种

      综上，当 $n=3$ 时，有 $C^3_3 \times (3-1)+C_3^2 \times (2-1)=5$ 种分法。

   3. 当 $n=4$ 时，设这些数为 $a_1,a_2,a_3,a_4$ ,不妨设 $a_1<a_2<a_3<a_4$

      1. 当取4个数时，有以下分法：

         $$A=\{a_1\},B=\{a_2,a_3,a_4\}$$

         $$A=\{a_1,a_2\},B=\{a_3,a_4\}$$

         $$A=\{a_1,a_2,a_3\},B=\{a_4\}$$

         共 $C^4_4 \times (4-1)=3$ 种

      2. 当取3个数时，有以下分法：

         $$A=\{a_1\},B=\{a_2,a_3\}$$

         $$A=\{a_1\},B=\{a_2,a_4\}$$

         $$A=\{a_1\},B=\{a_3,a_4\}$$

         $$A=\{a_2\},B=\{a_3,a_4\}$$

         $$A=\{a_1,a_2\},B=\{a_3\}$$

         $$A=\{a_1,a_2\},B=\{a_4\}$$

         $$A=\{a_1,a_3\},B=\{a_4\}$$

         $$A=\{a_2,a_3\},B=\{a_4\}$$

         共 $C^3_4 \times (3-1)=8$ 种

      3. 当取2个数时，有以下分法：

         $$A=\{a_1\},B=\{a_2\}$$

         $$A=\{a_1\},B=\{a_3\}$$

         $$A=\{a_1\},B=\{a_4\}$$

         $$A=\{a_2\},B=\{a_3\}$$

         $$A=\{a_2\},B=\{a_4\}$$

         $$A=\{a_3\},B=\{a_4\}$$

         共 $C^2_4 \times (2-1)=6$ 种

      综上，当 $n=4$ 时，有 $C^4_4 \times (4-1)+C^3_4 \times (3-1)+C^2_4 \times (2-1)=17$ 种分法。

   4. 通过数学归纳（~~找规律~~），可得公式：

      $$F(n)=\sum_{i=1}^{n-1}C^{i+1}_n \cdot i$$

   具体实现的代码就不写了，其他dalao有写。

   时间复杂度：$O(n^2)$

   空间复杂度：$O(n^2)$

   预计得分：40 points

3. 考虑优化。

   发现公式中的瓶颈在于如何快速处理组合数，于是开始推递推公式：

   $$F(n+1)-2F(n)$$

   $$ =\sum_{i=1}^{n}C^{i+1}_{n+1} \cdot i-(\sum_{i=1}^{n-1}C^{i+1}_n \cdot i)\times 2 $$

   $$=\sum_{i=1}^{n}C^{i}_{n+1}=2^{n}-1$$
   
   故得：$F(n+1)=2F(n)+2^n-1$
   
   代码就不写了
   
   时间复杂度：$O(n)$
   
   空间复杂度：$O(n)$
   
   预计得分：60 points
   
4. 继续考虑优化。

   已经写出递推公式的话有两种思路：1. 数学方法推通项公式；2. 矩阵快速幂加速递推公式。

   - 方法一：数学方法推通项公式：

     $$F(n)=\sum_{i=1}^{n-1}C_n^{i+1}\cdot i$$
    $$=\sum_{i=1}^{n-1}{n!\over(i+1)!(n-i-1)!}\cdot i$$
     $$=\sum_{i=2}^n{n!\over i!(n-i)!} \cdot i+{n!\over i!(n-i)!}$$
    $$=\sum_{i=2}^n{n!\over(i-1)!(n-i)!}+C_n^i$$
     $$=\sum_{i=2}^n{C_n^{i-1}\over n-i+1}+C_{n}^i$$
    $$={\sum_{i=2}^n{C_n^{i-1}}+(n-i+1)(2^n-n-1)\over n-i+1}$$
     $$={2^{n-1}-n-2+(n-i+1)(2^n-n-1)\over n-i+1}$$

     化简即为：$F(n)=(n-2)\cdot 2^{n-1}+1$ 

     这里 $2^{n-1}$ 用快速幂实现（注意，不能用 $<<$ 来做，会爆 long long）

     代码见code1

     时间复杂度：$O(\text{log}n)$

     空间复杂度：$O(1)$

     预计得分：100 points

   - 方法二：矩阵快速幂优化：

     个人认为这个方法可能鲜有人能想到（~~太麻烦了~~），我就仔细讲一讲。

     首先，观察递推公式中有如下几个影响值：$F(n-1),2^{n-1},1$ ,故与单位矩阵相乘的矩阵为

       $$\begin{bmatrix} F(n-1)\\ 2^{n-1}\\ 1\\ \end{bmatrix}$$

     得到的矩阵为

       $$\begin{bmatrix} F(n)\\ 2^{n}\\ 1\\ \end{bmatrix}$$

     有递推式显然可得：

     $$\begin{cases}F(n)=F(n-1)\times 2+2^{n-1}\times 1+1\times(-1)\\2^n=F(n-1)\times0+2^{n-1}\times 2+1\times 0 \\1=F(n-1)\times 0+2^{n-1}\times 0+1\times 1\end{cases}$$

     （不会矩阵加速的可以做一做 [P1939 【模板】矩阵加速（数列）](https://www.luogu.org/problem/P1939)和 [P1962 斐波那契数列](https://www.luogu.org/problem/P1962)）

     推出单位矩阵：

       $$\begin{bmatrix} 2&1&-1\\ 0&2&0\\ 0&0&1\\ \end{bmatrix}$$

     故矩阵递推式为：

     $$\begin{bmatrix} F(n-1)\\ 2^{n-1}\\ 1\\ \end{bmatrix} \times \begin{bmatrix} 2&1&-1\\ 0&2&0\\ 0&0&1\\ \end{bmatrix} =\begin{bmatrix} F(n)\\ 2^{n}\\ 1\\ \end{bmatrix}$$

     化为矩阵幂形式得：
   
     $$\begin{bmatrix} F(2)\\ 2^2\\ 1\\ \end{bmatrix} \times \begin{bmatrix} 2&1&-1\\ 0&2&0\\ 0&0&1\\ \end{bmatrix}^{n-2} =\begin{bmatrix} F(n)\\ 2^{n}\\ 1\\ \end{bmatrix}$$
     
     套魔板即可。
     
     代码见code2
     
     时间复杂度：$O(\text{log}n)$
   

  空间复杂度：$O(1)$

> 两种方法的优劣：
   >
   > - 第一种方法难算，需要较好的数学基础，但最后实现时时间复杂度在 $O(1)$ — $O(\text{log}n)$ ,常数极小。
   > - 第二种方法是数列加速的常用方法，简单易想，但常数较大，本题为常数为27，即在大数据下比第一种方法慢2—3倍

***

   Code1:

  ```cpp
   #include<bits/stdc++.h>
	//#define file
	#define modn (int)(1e9+7)
	#define int long long
	using namespace std;
	int n;
	inline int ksm(int x,int y,int p)
	{
		if(y==0) return 1%p;
		if(y==1) return x%p;
		int rst=ksm(x,y/2,p)%p;
		if(y%2==0)
		{
			return rst*rst%p;
		}else
		{
			int tmp=rst*rst%p;
			return tmp*x%p;
		}
	}
	signed main()
	{
		#ifdef file
		freopen("Agent1.in","r",stdin);
		freopen("Agent1.out","w",stdout);
		//F(n)=\sum_{i=1}^{n-1}C^(i+1)_n*i
		//F(n)=F(n-1)*2+2^{n-1}-1
		#endif
		scanf("%lld",&n);
		int ans=(n-2)*ksm(2,n-1,modn)%modn+1;
		printf("%lld\n",ans);
		return 0;
	} 
  ```

   [AC,49ms /  800.00KB](https://www.luogu.org/record/24724029)

***

   Code2(本代码为我的教练所写，码风可能有些许不同):

   ```cpp
   #include <bits/stdc++.h>
   using namespace std;
   #define int long long
   #define mod 1000000007
   int jz[3][3] = {{2,1,-1},{0,2,0},{0,0,1}}, 
       jz1[3][3] = {{2,1,-1},{0,2,0},{0,0,1}};
   int base[3][3];
   void cheng()
   {
       memset(base,0,sizeof(base));
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               for(int k=0;k<3;k++)
               {
                   base[i][j] += jz1[i][k]*jz1[k][j];
                   base[i][j] = (base[i][j]+mod)%mod;
               }
           }
       }
        memcpy(jz1,base,sizeof(base)); 
   }
   void chengjz()
   {
       memset(base,0,sizeof(base));
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               for(int k=0;k<3;k++)
               {
                   base[i][j] += jz1[i][k]*jz[k][j];
                   base[i][j] = (base[i][j]+mod)%mod;
               }
           }
       }
       memcpy(jz1,base,sizeof(base)); 
   }
   void quickpow(int k)
   {
       if(k==1) return;
       quickpow(k/2);
       cheng();
       if(k%2!=0) chengjz();
   }
   signed main()
   {
       int n;
       cin>>n;
       if(n==2)
       {
           printf("1");
           return 0;
       }
       quickpow(n-2);
       int ans = (jz1[0][0]+ 4*jz1[0][1]%mod + mod + 1*jz1[0][2]) mod;
       cout<<ans;
       return 0;
   }  
   ```

   [AC，48ms /  796.00KB](https://www.luogu.org/record/24727181)





---

## 作者：xiaohuang (赞：4)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/08/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8F%E6%B4%9B%E8%B0%B7P4936%20Agent1)

### Solution

根据题意，我们要取两组数，使$A$组的最大值小于$B$组的最小值，那么我们在一个有序的数列（不妨设为$1, 2, 3, \cdots , n$）里，我们可以取一个数$p$，表示分界线（不妨把它放在$A$组），$A$组的取数范围就是$p$以及$p$左边的所有数，$B$组的取数范围就是$p$右边的所有数，因此当$p = i$时$A$组取数的方案总数就是$2 ^ {i - 1}$（前面的每个数要么取，要么不取），而$B$组取数的方案数就是$2 ^ {n - i} - 1$（为什么要减$1$，因为不允许$B$队没有人参战，而我们把$p$归入$A$队，因此$A$组不会空）。我们用代数的形式表示出来：

$$\begin{aligned} \text{答案} & = \sum^{n}_{i = 1}{2 ^ {i - 1} \times (2 ^ {n - i} - 1)} \\ & = \sum^{n}_{i = 1}{2 ^ {n - 1} - 2^{i - 1}} \\ & = n \times 2 ^ {n - 1} - \sum^{n}_{i = 1}{2 ^ {i - 1}} \\ & = n \times 2 ^ {n - 1} -\sum^{n - 1}_{i = 0}{2 ^ i} \\ & = n \times 2 ^ {n - 1} - (2 ^ 0 + \sum^{n - 1}_{i = 1}{2 ^ i}) & = n \times 2 ^ {n - 1} - (1 + 2 ^ n - 2) \\ & = n \times 2 ^ {n - 1} - 2^ n + 1 \\ & = n \times 2 ^ {n - 1} - 2 \times 2 ^ {n - 1} + 1 \\ & = (n - 2) \times 2 ^ {n - 1} + 1 \end{aligned}$$

于是我们就可以直接通过快速幂直接求出答案了。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

typedef long long LL;
const int mod = 1000000007;
LL n;
inline LL power(LL x, LL p) {//快速幂
    LL ret = 1;
    for (; p; p >>= 1) {
        if (p & 1) ret = ret * x % mod;
        x = x * x % mod;
    }
    return ret;
}
int main() {
    scanf("%lld", &n);
    printf("%lld\n", ((n - 2) % mod * power(2, n - 1) % mod + 1) % mod);//公式
    return 0;
}
```

---

## 作者：zhangyuanxiao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P4936)

## 题意
+ $N$ 个人按能力值升序排成一行，从中选出 $i$ 个人（$i \in [2,n]$），将这 $i$ 个人中按能力值升序排列的前 $j$ 个人（$j \in [1,i-1]$）分到 A 队，剩余的 $i-j$ 个人分到 B 队，求分队的方案数模 $(10^9+7)$ 的值。
+ $N \le 10^9$。

## 分析
从 $N$ 个人中选 $i$ 个人，共有 $C_N^i$ 种方案。将这 $i$ 个人分成两队，由插板法，有 $C_{i-1}^1=i-1$ 种方案。记总方案数为 $ans$，则：
$$\begin{aligned} ans &= \sum_{i=2}^{N} C_N^i \cdot (i-1) \\&= C_N^N \cdot (N-1)+\sum_{i=1}^{N-1} C_N^i \cdot (i-1) \\&= N-1+ \frac{1}{2} \cdot \left\{ \left[ \sum_{i=1}^{N-1} C_N^i \cdot (i-1) \right] + \left[ \sum_{i=1}^{N-1} C_{N}^{N-i} \cdot (i-1) \right] \right\} \\&= N-1+ \frac{1}{2} \cdot \left[ \sum_{i=1}^{N-1} C_N^i \cdot (N-2) \right] \\&= N-1+ \frac{N-2}{2} \cdot \sum_{i=1}^{N-1} C_N^i \\&= N-1+ \frac{N-2}{2} \cdot \left( 2^N-C_N^0-C_N^N \right) \\&= N-1+ \frac{N-2}{2} \cdot \left( 2^N-2 \right) \\&= N-1+2^{N-1} \cdot (N-2)-(N-2) \\&= 2^{N-1} \cdot (N-2) +1 \end{aligned}$$

因此，我们只需要用快速幂求出 $2^{N-1}$ ，即可以 $O( \log n)$ 的时间复杂度通过此题。

## 代码
```cpp
#include<iostream>
#define int long long
using namespace std;

int N;
const int mod=1e9+7;

int qpow(int a,int p){
	int base=a,ans=1;
	while(p){
		if(p&1){
			ans*=base;
			ans%=mod;
		}
		base*=base;
		base%=mod;
		p>>=1;
	}
	return ans;
}

signed main(){
	cin>>N;
	cout<<((N-2)*qpow(2,N-1)%mod+1)%mod;
	return 0;
}
```

---

## 作者：囧仙 (赞：2)

## 题目大意

> 从 $1\sim n$ 这 $n$ 个数中，选出若干个数分为两个非空集合 $A,B$ ，使得 $\max\{A\}<\min\{B\}$ 。求方案数。

## 题解

由于 $A$ 的最大值不超过 $B$ 的最小值，因此假如我们把选出来的数字排序，那么 $A$ **必然**是前若干个数，而剩余数字都在 $B$ 中。因此假设选出了 $x$ 个数，那么方案数应为 $(x-1)$ （即枚举 $A$ 集合的大小）。

根据组合数学，从 $n$ 个数当中选出 $x$ 个数的方案数为 $\displaystyle\binom{n}{x}$ 。

于是，

$$\begin{aligned}
ans &=\sum_{i=1}^n(i-1)\binom{n}{i} \cr
&=\sum_{i=1}^n i\binom{n}{i}-\sum_{i=1}^n\binom{n}{i} \cr
&=\sum_{i=0}^n i\binom{n}{i}-\sum_{i=0}^n\binom{n}{i}+1
\end{aligned}$$

考虑二项式定理。构造函数 $F(x)$ ，使得：

$$\begin{aligned}
F(x)&=(1+x)^n \cr
&=\sum_{i=0}^n\binom{n}{i}x^i
\end{aligned}$$

对两边求导。可以发现：

$$\begin{aligned}
F'(x)&=n(1+x)^{n-1} \cr
&=\sum_{i=0}^ni\binom{n}{i}x^{i-1}
\end{aligned}$$

于是我们令 $x=1$ ，可以发现：

$$\begin{aligned}
&\sum_{i=0}^n\binom{n}{i} &=&(1+1)^n &=&2^n \cr
&\sum_{i=0}^n i \binom{n}{i} &=&n(1+1)^{n-1} &=&n\cdot 2^{n-1}
\end{aligned}$$

因此，

$$\begin{aligned}
ans &=\sum_{i=0}^n i\binom{n}{i}-\sum_{i=0}^n\binom{n}{i}+1 \cr
&=n\cdot 2^{n-1}-2^n+1 \cr
&=(n-2)\cdot 2^{n-1}+1
\end{aligned}$$

所以写个快速幂，这题就做完啦！

## 参考代码


```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
const int MOD =1e9+7;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int n,t=2,r=1;
int main(){
    n=qread(); up(0,30,i){if((n-1)&(1<<i)) r=1ll*r*t%MOD;t=1ll*t*t%MOD;}
    printf("%d\n",(1ll*(n-2)*r+1)%MOD);
    return 0;
}
```

---

## 作者：muller (赞：2)

这题好像有通项公式

但是juruo太菜了，不太会

其实就是写一下以前的题解罢啦

直接写个brute找一下规律

发现有点奇怪的规律

就是搞一个快速幂

然后记得%一下即可

否则会只有30pts

唉！好像代码有点长。。。

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p=1e9+7;
ll n;
ll qpow(ll a,ll b){
	if (!b) return 1;
	ll tmp=qpow(a,b/2);
	tmp=(tmp*tmp)%p;
	if (b%2) tmp=(tmp*a)%p;
	return tmp; 
}
int main(){
	cin>>n;
	cout<<(qpow(2,n-1)*(n-2)%p+1)%p<<endl;
	return 0;
}

```

---

## 作者：msy66 (赞：1)

本文已更新于2019.2.15

暴力的搜索，只有20分……


------------

显然搜索是无法解决本题的大数据的。我们枚举A组的最后一个人，设他是k强大的，那么A组有2^(k-1)种方案，B组有2^(n-k)-1种方案（因为两队都要有人参战）。

由加法原理和乘法原理，得答案是∑2^(i-1)(2^(n-i)-1)          (1<=i<n）

于是有了两个得部分分的方案

------------
40分：直接枚举i，2的幂直接算就好了。时间复杂度O(n^2）

------------
60分：快速幂或预处理，时间复杂度O(nlogn)或O(n)

------------
满分：展开合并，

ans

=∑(2^(n-1)-2^(i-1)) (1<=i<n）

=n*2^(n-1)-∑2^(i-1) (1<=i<n）

=n*2^(n-1)-(2^n-1) 

=2^(n-1)*(n-2)+1;

使用快速幂时间复杂度O(logn)，可以AC了~~（不用欧拉定理）~~。

注意要开long long！！！！！！

代码双手捧上：

------------


```cpp
#include<iostream>
#include<cstdio>
#define maxd 1000000007
using namespace std;
long long n;
long long t;
long long ans;
long long count(long long x,long long y){
    long long a=x,b=y;
    a%=maxd;
    long long s=1;
    while (b>0){
        if(b%2==1) {s*=a;s%=maxd;}
        a*=a;
        a%=maxd;
        b/=2;
    }
    return s;  
}
int main(){
  cin>>n;
  t=count(2,n-1);
  ans=t*(n-2)+1;
  ans%=maxd;
  cout<<ans<<endl;
  return 0;
}

```

---

## 作者：Fireworks_Rise (赞：0)

# 解题思路

题目意思不用多讲，从序列 $1,2 \dots n$ 中取出若干个数，分成 $A,B$ 两组，使得 $A$ 中最大值小于集合 $B$ 中的最小值，求方案数。

很显然，这是一道组合排列题，我们设 $i$ 为两组的分界点，$i$ 属于集合 $A$。

由于两个集合都不能为空，对于集合 $A$，因为 $i$ 为分界点，是必须要选的，所以 $i$ 左边的数可选可不选，即 $2^{i-1}$；对于集合 $B$，同理，但要去除所有数都不选的情况，故需要 $-1$，那么这两个集合对答案的贡献为 $2^{i-1}\times 2^{n-i}-1$。

$Ans=\sum_{i=1}^{n}2^{i-1}\times 2^{n-i}-1$

$=\sum_{i=1}^{n}2^{n-1}-2^{i-1}$

$=n\times 2^{n-1}-\sum_{i=1}^{n} 2^{i-1}$

$=n\times 2^{n-1}-\sum_{i=0}^{n-1} 2^{i}$

$=n\times 2^{n-1}-(2^0+\sum_{i=1}^{n-1} 2^{i})$

$=n\times 2^{n-1}-(1+2^{n}-2)$

$=n\times 2^{n-1}-2^{n}+1$

$=n\times 2^{n-1}-2\times 2^{n-1}+1$

$=(n-2)\times 2^{n-1}+1$

最后运用快速幂求出答案即可。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n;
inline int power(int a,int p) {
	int ret=1;
	while(p) {
		if(p&1)
			ret=ret*a%mod;
		a=a*a%mod;
		p>>=1;
	}
	return ret;
}
signed main() {
	scanf("%lld",&n);
	printf("%lld\n",((n-2)%mod*power(2,n-1)%mod+1)%mod);
	return 0;
}
```


---

## 作者：scp020 (赞：0)

### 题意

给定一个整数 $n$，代表有 $n$ 个数（不妨设为 $1,2,\ldots,n$）。

让你把这些数分为两组（考虑直接左右切成两半），其中每一组要保证有数，每一个数不一定要用。

求有多少种分组方式。

**答案对 $1000000007$ 取模。**

### 推导

对于 $n$ 个数，我们有 $n$ 种切割方法。考虑对于第 $i$ 种切割（切割的临界值要选，归为），每一个数可选可不选，所以左边一组共有 $2^{i-1}$ 种选法，右边有 $2^{n-i}-1$ 种选法。

$\begin{aligned} ans&=\sum\limits_{i=1}^{n} 2^{i-1} \times (2^{n-i}-1)\\ &=\sum\limits_{i=1}^{n} 2^{n-1}-2^{i-1} \\ &= (n-2) \times 2^{n-1}+1 \end{aligned}$

### 代码

$16$ 行代码，如果需要可以压到 $14$ 行。

```cpp
#include<bits/stdc++.h>
long long m,mod=1000000007,ans=1;
void fastpow(long long a,long long b)
{
	while(b)
	{
		if(b&1) ans=(ans*a)%mod,b--;
		b/=2,a=a*a%mod;
	}
}
int main()
{
	scanf("%lld",&m),fastpow(2,m-1);
	printf("%lld",(m-2)*ans%mod+1);
	return 0;
}
```


---

## 作者：Chivas_Regal (赞：0)

(第一眼看到这个题不知道 $O(1)$ 怎么写，硬着头皮搞了个 $O(n^2)$ 的柿子然后推来推去...（竟然推出来了 

# 排列组合

$AB$ 两队，每队必派一个人  
我们可以枚举每队是谁必派， $A$ 派 $i$ ， $B$ 派 $j$ ，然后为了保证  $max\{A\}<min\{B\}$ 我们让每队派的两个人中间的人 （也就是 $i\lt x\lt j$ ） 必不出，两侧的数 （也就是 $x\lt i\;\vee\;j\lt x$ ） 选择性出  
这样的话就是  $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(2^{i-1}\times 2^{n-j})$     
这是一个 $O(n^2)$ 的柿子，我们优化一下  

# 优化柿子

$\begin{aligned}&\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(2^{i-1}\times 2^{n-j})\\=&\sum\limits_{i=1}^n\sum\limits_{j=0}^{n-i-1}(2^{i-1}\times 2^j)\\=&\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-i-2}(2^i\times 2^j)\\=&\sum\limits_{i=0}^{n-1}2^i\sum\limits_{j=0}^{n-i-2}2^j\\=&\sum\limits_{i=0}^{n-1}(2^i\times(2^{n-i-1}-1))\\=&\sum\limits_{i=0}^{n-1}(2^{n-1}-2^i)\\=&n2^{n-1}-(2^n-1)\end{aligned}$  
   

好了，这么一个可以 $O(logn)$ 的柿子就出来了   

# 代码 

就..和上面的柿子一模一样...  

```cpp
#include <iostream>

#define ll long long

using namespace std;

const int mod = 1e9 + 7;
inline ll ksm ( ll a, ll b ) {
        ll res = 1;
        while ( b > 0 ) {
                if ( b & 1 ) res = res * a % mod;
                a = a * a % mod;
                b >>= 1;
        }
        return res;
}

int main () {
        ll n; cin >> n;
        cout << (n * ksm(2, n - 1) % mod 
                 - (ksm(2, n) - 1 + mod) % mod 
                 + mod
                ) % mod << endl;
}
```

---

## 作者：似镜流年 (赞：0)

### 很显然这是一道数学题
 然而看到下面大佬都没有太通俗易懂的讲法，于是乎本蒟蒻就来水一篇题解。
 
### 首先考虑直观的解法
# 也就是说最后的答案是$\Sigma_{i=1}^{n}(i-1)C^{i}_{n}$
#### 即每次从$n$中选出$i$个数，对于这$i$个数，符合要求的个数显然是$i-1$个。

但是~~蒟蒻不会算这个式子的求和~~比较难算，也比较难推出递推式。

于是就开始直接找递推规律。

## 令$f[i]$表示$n=i$时的答案，则有$f[i]=2f[i-1]+2^{i-1}-1$

我们考虑如何直观地得出上面这个式子。假设我们已经求出了$f[1...i-1]$的值，接下来要求$f[i]$。(假设序列单调递增，容易知道这对结果并不影响)

那么首先考虑 $i$ 一个人被分成一队，则共有$2^{i-1}-1$种情况(只要前面不为空，那么就一定合法)。

再考虑 $ i $ 被分入其他队的情况，则共有$f[i-1]$种情况( $i$ 只能被分入$B$组)

最后考虑 $ i $ 不被用的情况，显然有$f[i-1]$种.

综上，$f[i]=2f[i-1]+2^{i-1}-1$

## 然后就有两种写法了

首先既然有项数不算多的递推式，那么就可以用矩阵快速幂了。

~~然而这只是道蓝题。(矩乘平均紫题)~~

但是我们还可以直接推通项公式——

$\qquad\qquad\qquad f[i]=2f[i-1]+2^{i-1}-1$

$\qquad\qquad\qquad 2f[i-1]=4f[i-2]+2^{i-1}-2$

$\qquad\qquad\qquad 4f[i-2]=8f[i-3]+2^{i-1}-4$

$\qquad\qquad\qquad ……$

$\qquad\qquad\qquad 2^{i-2}f[2]=2^{i-1}f[1]+2^{i-1}-2^{i-2}$

将这几条式子累加可以得到

### $f[i]=(i-2)* 2^{i-1}+1(i>=2)$  

### $f[1]=0$

### $=>f[i]=(i-2)* 2^{i-1}+1(i>=1)$

然后用快速幂就可以AC了。~~代码太简单就不放了。~~

---

## 作者：_WD_ (赞：0)

## 题面简化
1.有$N$个不重复的数
2.从$N$个数中取两个非空集合 $A$ $B$
3.$\forall a\in A,\forall b\in B,a>b$
#### 数据范围
对于$20\%$的数据 $N\leq10$
对于$40\%$的数据 $N\leq10^3$
对于$60\%$的数据 $N\leq10^5$
对于$100\%$的数据 $N\leq10^9$

一看就看出要 $O(1)$ 的时间复杂度，明显是**数学题**
## 思路
### 若$N\leq10^3$
看到n个数不相同，选数和大小相关，就发现需要排序。

把$N$个数排成一数列，用 $1,0$ 表示 取 或 不取 。（只是更直观了些）

因为$\forall a\in A,\forall b\in B,a>b$
所以可以记录 $B$中的最大值、$A$中的最小值 在数列中的位置，这里设为$i$和$j$，要枚举所有 $i<j$ 的情况。

选定$i,j$后，易得 
$集合A的选择方案数=2^{i-1}$，
$集合B的选择方案数=2^{N-j}$,
则有
$$\sum_{i=1}^{N-1}\sum_{j=i+1}^{N} 2^{N-(j-i+1)}$$
快速幂复杂度先忽略~~我不会算~~ ，到这里是 $O(n^2)$
### 若$N\leq10^5$
观察上一个式子，我们可以发现 **有的指数是被重复计算的** ，
所以可以换一种枚举方式，枚举 原 $i$ $j$ 间的不选的数字个数（包括i和j），
设为 $k$ ，则 $k=j-i+1$
则有
$$\sum_{i=2}^{N}(N-i+1)*2^{N-i}$$
即
$$\sum_{i=1}^{N-1}i*2^{i-1}$$
连快速幂都不需要，到这里是 $O(n)$
### 若$N\leq10^9$
从$O(n)$到$O(1)$是极难跨越的一步（废话）

众所周知，
$$\sum_{i=0}^{n}2^{i}=2^{n+1}-1$$
所以，
$$\sum_{i=1}^{N-1}i*2^{i-1}=\sum_{i=0}^{N-2}(2^{N-1}-1)-(2^{i}-1)=(N-1)*2^{N-1}-2^{N-1}=(N-2)*2^{N-1}-1$$
第二步时用了前缀和的思想，之后就很简单地推出来了

复杂度 $O(1)$ ，要加一个快速幂取模
### 代码
快速幂模板

---

## 作者：Epworth (赞：0)

这是一道~~数列大题~~$QwQ$

我们令$a_n$表示有$n$个$Agent$时的作战方案数。

显然$a_1=0$($A,B$两队都要有人参战)。

考虑加入一个新的$Agent$后增加的方案：

①在$n-1$的情况下将其放在每种情况的$B$组中：$a_{n-1}$种方案。

②单独放在$B$组，$A$组在剩下的$n-1$个中任意选择：

排除$A$组为空的情况后共有$2^{n-1}-1$种方案。

于是我们可以写出递推式：
$$
a_n=2\times a_{n-1}+2^{n-1}-1\ \ \ \ \ (a_1=0)
$$
因为$N \leq 10^9$，$O(n)$肯定要超时。

所考虑写出它的通项：

两边同除$2^n$得
$$
\frac{a_n}{2^n}=\frac{a_{n-1}}{2^{n-1}}+\frac{1}{2}-\frac{1}{2^n}
$$
令$b_n=\frac{a_n}{2^n}$移项得
$$
b_n-b_{n-1}=\frac{1}{2}-\frac{1}{2^n}
$$
列项相加得
$$
b_n-b_{1}=\frac{n-1}{2}-(\frac{1}{2^2}+\frac{1}{2^3}+...\frac{1}{2^n})
$$
进一步转化得
$$
b_n-b_{1}=\frac{n}{2}+\frac{1}{2^n}-1
$$
将$\frac{a_n}{2^n}=b_n$代入变形得
$$
a_n=(n-2)\times2^{n-1}+1\ \ \ \ \ (n\ge 1)
$$
快速幂解决。

就当复习数列通项了$QwQ$

## 代码

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define ll long long
using namespace std;
int n;
ll qkpow(int n,int m){
	ll ans=1,base=n;
	while(m){
		if(m&1) ans*=base,ans%=mod;
		base*=base;base%=mod;
		m>>=1;
	}
	return ans;
}
int main(){
	//freopen("agent.in","r",stdin);
	//freopen("agent.out","w",stdout);
	scanf("%d",&n);
	printf("%d\n",((n-2)*qkpow(2,n-1)+1)%mod);
	return 0;
}
```



---

## 作者：ljcljc (赞：0)

【分析】

很显然树状数组+差分

树状数组我不多提了，主要讲讲差分

设数组$a[]=$${$$1,3,6,9,13$$}$，那么差分数组$b[]=$${$$1,2,3,3,4$$}$

从上面可以看出$b[i]=a[i]-a[i-1]$ (我们令$a[0]=0$)，那么不难发现$a[i]=b[1]+....+b[i]$;。

假如区间$[2,4]$都加上$2$的话

$a$数组变为$a[]=$${$$1,5,8,11,13$$}$，$b$数组变为$b[]=$${$$1,4,3,3,2$$}$;

不知道你有没有发现只有$b[2]和b[5]$变了，因为区间$[2,4]$是同时加上$2$的,所以在区间内$b[i]-b[i-1]$是不变的.

所以对区间$[x,y]$进行修改,只用修改$b[x]$与b$[y+1]$:

$b[x]=b[x]+k;b[y+1]=b[y+1]-k;$


【AC代码】
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
#define lowbit(x) x&-x
#define LL long long
const int MAXN = 100000010;
int n, m;
LL bit[MAXN];
//板子不多讲了
void add(int x,int v) {
    while(x <= n) {
        bit[x] += v;
        x += lowbit(x);
    }
}
LL sum(int x) {
    LL ret = 0;
    while(x > 0) {
        ret += bit[x];
        x -= lowbit(x);
    }
    return ret;
}
int main()
{
	scanf("%d %d", &n, &m);
    while(m--) {
    	int otp, x, y;
    	scanf("%d", &otp);
        if(!otp) {
        	scanf("%d %d", &x, &y);
            add(x,1);//差分
            add(y+1,-1);
        } else {
        	scanf("%d", &x);
        	printf("%lld\n", sum(x));
        }
    }
    return 0;
}
```


---

