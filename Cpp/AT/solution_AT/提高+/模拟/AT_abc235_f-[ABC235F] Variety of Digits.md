# [ABC235F] Variety of Digits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc235/tasks/abc235_f

$ M $ 個の数字 $ C_i $ が与えられます。

$ 1 $ 以上 $ N $ 以下の整数のうち、先頭に余分な $ 0 $ をつけずに $ 10 $ 進法で表した時に $ C_1,\ldots,C_M $ を全て含むようなもの全ての和を、 $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ <\ 10^{10^4} $
- $ 1\ \leq\ M\ \leq\ 10 $
- $ 0\ \leq\ C_1\ <\ \ldots\ <\ C_M\ \leq\ 9 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

$ 1 $ 以上 $ 104 $ 以下の整数のうち、$ 10 $ 進法で表した時に `0`, `1` を共に含むようなものは、$ 10,100,101,102,103,104 $ の $ 6 $ 個あります。 これらの和は $ 520 $ です。

### Sample Explanation 2

$ 1 $ 以上 $ 999 $ 以下の整数で、`1`, `2`, `3`, `4` を全て含むようなものは存在しません。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めてください。

## 样例 #1

### 输入

```
104
2
0 1```

### 输出

```
520```

## 样例 #2

### 输入

```
999
4
1 2 3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
5
0 2 4 6 8```

### 输出

```
397365274```

# 题解

## 作者：_sunkuangzheng_ (赞：3)

这道数位 dp 题怎么还没有记忆化搜索的题解 qwq。

如果只计数就是非常板的数位 dp 题，设 $f_{p,s,l,pr}$ 表示到了第 $p$ 位，数字出现状态是 $s$，是否有最高位限制 $l$，是否是前导零 $pr$ 时的方案数，直接记忆化搜索即可。但是要求和。

一般对于要求和的题，常见套路是设 $g_{p,s,l,pr}$ 表示该状态下合法数字的和，我们有：$g_p = \sum \limits_{i=0}^{up} g_{p-1}+i \cdot 10^{p-1}f_{p-1}$（其他状态以省略，$up$ 指上界），含义是这一位的所有和等于后面位的和加上这一位填的数字的总贡献，可以在记忆化搜索时一并转移。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 08.11.2023 09:47:20
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
#define int long long
const int mod = 998244353;
using namespace std;
int t,n,m,a[12],f[10005][1025][2][2],g[10005][1025][2][2],p10[10005];string st;
pair<int,int> dfs(int p,int s,int l,int pr){
    if(!p) {
        for(int i = 1;i <= m;i ++) if(!((s >> a[i]) & 1)) return {0,0};
        return {1,0};
    }if(f[p][s][l][pr] != -1) return {f[p][s][l][pr],g[p][s][l][pr]};
    int u = (l ? (st[p] - '0') : 9),ans1 = 0,ans2 = 0;
    for(int i = 0;i <= u;i ++){
        int np = (!i && pr);
        auto [x,y] = dfs(p-1,s | (np ? 0 : (1 << i)),l && (i == u),np);
        ans1 = (ans1 + x) % mod,ans2 = (ans2 + y + p10[p-1] * i % mod * x) % mod;
    }return {f[p][s][l][pr] = ans1,g[p][s][l][pr] = ans2};
}signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> st >> m,n = st.size(),memset(f,-1,sizeof(f));
    reverse(st.begin(),st.end()),st = " " + st;
    for(int i = 1;i <= m;i ++) cin >> a[i];p10[0] = 1;
    for(int i = 1;i <= n;i ++) p10[i] = p10[i-1] * 10 % mod;
    cout << dfs(n,0,1,1).second;
}
```

---

## 作者：CQ_Alice (赞：2)

#### 题意

给定整数 $n$，和 $m$ 个整数 $c_1,c_2,…,c_M$。

$1\le N<10^{10^4}$，$M\le10$。

$0\le C_1<…<C_M\le9$。

$x$ 为整数并满足：

1. $1\le x\le n$ 。
2. $m$ 个整数，$c_1,c_2,…,c_M$ 中每一个都要在 $x$ 中至少出现一次。

求所有满足条件的 $x$ 的和。


#### 思路

首先给定 $n$ 的范围恐怖至极，但是我们发现任意相邻的两个位数，他们之间是完全可以互相转移答案的。

比如说有 $233$ 这个数字，我们发现 $233$ 可以通过 $23\times10+3$，即从前两位的数字 $23$ 转移成了前三位的数字 $233$。那么我们在计算答案的时候可不可以也用上这样的方式呢？

$f_{i}$：从最高位到第 $i$ 高位共 $i$ 位的所有数字的和为多少。

$g_{i}$：从最高位到第 $i$ 高位共 $i$ 位的数字共多少个。

#### 举个例子 ：

按照上述的定义，$f_2$ 就表示从最高位到第 $2$ 高位，一共 $2$ 位的所有数字的和。

那么可以发现一共是有两位的话，那么就会有这些数字满足要求：
$10,11,12,13,14,15…99$，所以 $f_2$ 的值即为满足要求的所有数字的和，即 $10+11+12+…+100=5005$，而此时的 $g_2$ 则应该等于上述满足要求的数字个数即 $100-10+1$ 共 $91$ 个。

那么我们现在知道 $f_2$ 和 $g_2$ 的值，想要推 $f_3$ 和 $g_3$ 的值该如何转移？

对于此时的 $f_3$，也就是此时的最高位到第 $3$ 高位，共 $3$ 位的所有数字之和，那么前两位填的数字是可以直接转移前三位填的数字的，但是现在我们只知道填的数字的和，和与和之间如何转移？

假设此时我们希望第 $3$ 位填 $8$ 这个数字，那么我们来看一下将会是如何转移：

从最高位到第 $2$ 高位，共两位的填法有 $k$ 种，分别为 
$$\begin{cases}
s_1\\
s_2\\
s_3\\
\vdots\\
s_k\end{cases}$$

由于第 $3$ 高位我们填入了 $8$，所以这 $k$ 个方案将会变成

$$\begin{cases}
s_1\times10+8\\
s_2\times10+8\\
s_3\times10+8\\
\vdots\\
s_k\times10+8\end{cases}$$

然后上述 $k$ 个式子的和则可以根据乘法分配律得到为：$10\times(s_1+s_2+....+s_k)+8\times k$，此时 $s_1+s_2+....+s_k$ 就是我们所定义的 $f_2$ 的值；而 $k$ 则为 $g_2$，因此对于第 $i+ 1$ 高位填 $s$，则前 $i$ 位与前 $i+1$ 位的转移方程即为 $f_{i+1}=f_{i+1}+f_{i} \times10+g_{i}\times s$ 和 $g_{i+1}=g_{i+1}+g{i}$。

那么我们可以初始化令 $f_1=1+2+3+....+9$（注意最高位我们一定不能填 $0$,但是其他位填几都可以），$g_1=9$，然后从第 $2$ 高位开始推。

于是便有了以下代码：

```cpp
//mod 是题目中要求的取余数
for(int s = 1 ;  s <= 9 ; s ++ ) {
    f[1] = ( f[1] + s ) % mod ;
    g[1] = ( g[1] + 1 ) % mod ;                  
}          
//n 表示我们要填满的数的位数                      
for(int i = 1 ; i <= n - 1 ; i ++ ) {
	for(int s = 0 ; s <= 9 ; s ++ ) {
   		f[i + 1] = ( f[i + 1] + f[i] * 10 + g[i] * s ) % mod ;
     	       g[i + 1] = ( g[i + 1] + g[i] ) % mod ;              
    }
}
                      
```

恭喜你已经完成了这道题的 $30\%$ 。

------------

### 重点板块

回到题意，我们已经令 $x$ 的位数不超过 $n$ 的位数，接下来我们要使 $m$ 个整数，$c_1,c_2,…,c_M$ 中每一个数字都要在 $x$ 中至少出现一次。


对于上述题意中的第二个条件，由于 $M$ 的范围极小，所以我们考虑用状压的方式，来表示 $0,1,....,9$ 是否出现过的这么一个状态。

状压是啥？

一个数字在被二进制表示时，第 $i$ 位数的值 $0/1$，就可以用来表示第 $i$ 个数是与否的状态；而对于这题，第 $i$ 位的 $0/1$ 表示的是数字 $i$ 是否出现过。

$f_{i,l}$ 表示从最高位到第 $i$ 高位的数字出现状态为 $l$ 的所有数字之和。

$g_{i,l}$ 表示从最高位到第 $i$ 高位的数字出现状态为 $l$ 的所有数字的个数。

掏出我们 $30\%$ 的转移：

$f_{i+1} = f_{i+1} + f_{i} \times 10 + g_{i} \times k$

$g_{i+1} = g_{i+1} + g{i}$

如果说第 $i+ 1$ 位我们想填 $k$，然后前 $i$ 位的数字出现状态为 $l$ 的话，那么我们现在想要得到前 $i+ 1$位的数字出现状态，那么分两种情况：
1. $k$ 这个数字在最高位到第 $i$ 高位都没出现过，即 $l$ 的二进制形式下的第 $k$ 位为 $0$。

2. $k$ 这个数字在最高位到第 $i$ 高位出现过，即 $l$ 的二进制形式下的第 $k$ 位为 $1$。

可以发现不管是第一种情况还是第二种情况，我们前 $i+1$ 位的数字出现状态的二进制形式下的第 $k$ 位都应该为 $1$，因为 $k$ 这个数字在第 $i+ 1$ 高位上出现了，所以前 $i+ 1$ 位的数字出现状态直接可以用 $l|2^k$ 来表示，$2^k$ 表示的是一个二进制中只有第 $k$ 位为 $1$ 的这么一个数，将 $l$ 或上 $2^k$ 即是将状态 $l$ 二进制形式下的第 $k$ 位赋值为 $1$。

那么第 $i+1$ 高位填 $k$，便可得以下两个转移方程：

$f_{i+1 , l|(1<<k)}=f_{i+1 , l|(1<<k)}+f_{i,l}\times10 +g_{i,l}\times k$

$g_{i+1 , l|(1<<k)}=g_{i+1, l|(1<<k)}+g_{i,l}$

初始化令

对于 $k$ （$1 \le k\le9$）

$f_{1 , 2^k}=k$ 

$g_{1 , 2^k}=1$

代码如下 ：

```cpp
//mod 是题目中要求的取余数
for(int k = 1 ;  k <= 9 ; k ++ ) {
    f[1][1<<k] = k % mod ;
    g[1][1<<k] = 1 % mod ;                  
}          
( 1 << 10 ) - 1 表示二进制下从第0位到第9位全是1的数
for(int l = 0 ; l <= ( 1 << 10 ) - 1 ; l ++ ) { 
   for(int i = 1 ; i <= n - 1 ; i ++ ) {
       for(int k = 0 ; k <= 9 ; k ++ ) {
          f[i + 1][l | ( 1 << k )] = ( f[i + 1][1 | ( 1 << k )] + f[i][l] * 10 + g[i][l] * k ) % mod ;
          g[i + 1][l | ( 1 << k )] = ( g[i + 1][l | ( 1 << k )] + g[i] ) % mod ;              
       }
   }
}
                      
```

恭喜你完成了该题的 $60\%$



------------

我们已经求出了任意位数，任意数字出现状态的所有答案，此时
我们需要令 $x$ 的值在 $1$ 到 $n$ 的范围以内。

于是对于第 $i$ 高这一位，如果说前 $i$ 高位与 $n$ 的前 $i$ 高位完全一致，那么此时第 $i+1$ 高位的选择就要受到 $n$ 的限制，反之如果前 $i$ 高位小于 $n$ 的前 $i$ 高位则第 $i+1$ 不受到任何约束。

例如此时 $n$ 为 $1283$，前 $3$ 高位我们选择填 $128$，我们会发现 $n$ 的前 $3$ 高位的数是 $128$，与我们的选择完全一致，此时的第 $4$ 高位就不能填超过 $3$ 的数了，比如 $128$ 后面填的是 $4$，此时变成 $1284$，但是很明显 $1284>1283$，不满足$1 \le x\le n$的要求。

于是我们在两维动态规划的基础上再加一维 $j$（$j=0/1$），$f_{i,l,j}$，当 $j$ 等于 $0$ 时就表示前 $i$ 高位与 $n$ 完全一致，当 $j$ 等于 $1$ 时就是前 $i$ 高位与 $n$ 不一致的所有情况 。

那么对于第 $i+1$ 高位，如果前 $i$ 高位跟 $n$ 完全一致，那么此时第 $i+1$ 高位就只能填 $0$ 到 $n$ 的第 $i+1$ 高位这个数；如果前 $i$ 高位跟 $n$ 不一致，那么此时第 $i+1$ 高位就能填 $0$ 到 $9$ 的任意一个数。

如果第 $i+ 1$ 高位填 $k$，且 $n$ 的第 $i+1$ 高位为 $p$，则得到转移式：

如果前 $i+ 1$ 位都要和 $n$ 一致，那么前 $i$ 位也一定与 $n$ 一致，并且第 $i+1$ 高位填的数也要和 $n$ 的第 $i+ 1$位相同，所以得到以下方程：

$f_{i+1 , l|2^p,1}=f_{i+1 , l|2^p,1}+f_{i,l,1}\times 10+g_{i,l,1}\times p$ 

$g_{i+1,l|2^p,1}=g_{i+1,l|2^p,1}+g_{i,l,1}$

如果前 $i$ 位都要和 $n$ 一致，那么在 $j=0$ 的情况之下，首先 $k$ 不能等于 $p$，因为 $k$ 等于 $p$ 的情况统计在了 $f_{i+1,l|2^p,1}$ 里，其次 $k$ 也不能大于 $p$，因为大于之后求到的值就不在 $1$ 到 $n$ 的范围内了。

当 $k$ 小于 $p$ 时，执行下面两行转移：

$f_{i+1 ,l|2^k,0}=f_{i+1 ,l|2^k,0}+f_{i,l,1}\times10+g_{i,l,1}\times k$

$g_{i+1 , l|2^k,0}=g_{i+1,l|2^k,0}+g_{i,l,1}$。

当然，如果我们前 $i$ 位不与 $n$ 一致，那么 $k$ 的范围就是 $0$ 到 $9$。

$f_{i+1 ,l|2^k,0}=f_{i+1 , l|2^k,0}+f_{i,l,0}\times 10+g_{i,l,0}\times k$

$g_{i+1 ,l|2^k,0}=g_{i+1, l|2^k,0}+g_{i,l,0}$


这样这道题就完成 $80\%$ 了！

接下来就是答案应该是啥？

首先对于每种数字出现状态，都会有一个答案，题目中要求的是有$M$个数字都必须出现，那么我们的数字出现状态中的那$M$位，即$c_1,c_2,…,c_M$都应该为 $1$，这样在我们求出的答案中才一定会存在那 $M$ 个数，那该如何判断那 $M$ 位是否都为 $1$？

首先我们考虑设 $Plu=2^{c_1}+2^{c_2}+…2^{c_M}$，那么对于数字出现状态 $l$，如果 $l$ 的 $c_1,c_2,…,c_M$ 都为 $1$,那么当 $l \And Plu$ 后，二进制下的 $c_1,c_2,…c_M$ 位也都应该为 $1$ , 并且由于其他的几位在 $Plu$ 里都为 $0$，所以$l \And Plu$ 会等于 $Plu$ , 那么 $Plu \And l = Plu$ 就成为了判断条件。那么对于所有的满足条件的状态，我们去求一遍答案，对于一个满足条件的状态 $l$，它对答案的贡献是

设 $len$ 表示 $n$ 的位数。

$\sum_{{1≤i \le len}} f_{i,l,0}+f_{i,l,1}$ 

然后你会得 $0$ 分，原因是因为当位数不足 $len$ 的时候，我们就不需要考虑每一位的约束，但是在求解的过程中，每种位数都被 $n$ 进行了限制，所以我们去求一下所有满足条件的，位数小于 $len$ 的答案：

因为没有限制，所以每一位都可以随便填，除了第一位不能填零。

那么

$f1_{i,j}$ 表示 $i$ 位数，数字出现状态为$j$的所有数字之和。

$g1_{i,j}$ 表示 $i$ 位数，数字出现状态为$j$的所有数字的数量。

转移不变，$k$不受限制（除了第一位 $k$ 不能为 $0$)；

$f1_{i+1,l|2^k}=f1_{i+1,l|2^k}+f1_{i,l}\times10+g1_{i,l}\times k$

$g1_{i+1,l|2^k}=g1_{i+1,l|2^k}+g{i,l}$

那么最后的答案便是：

对于所有包含 $M$ 个数字的数字出现状态 $l$。

$((\sum_{{1≤i<len}} f1_{i,l} )+f_{len,l,0} + f_{len,l,1})$ 的和。

$u$ 是常数,可以确定 $u$ 小于 $10$。

时间复杂度是 $O(10^4\times2^{10}\times u)$，大约 $10^8$ 左右。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2) // O2启动
using namespace std ;
const int Max = 2e4 + 10 , Nax = ( 1 << 10 ) , mod = 998244353 ; 
long long f[Max][Nax + 10][2] , g[Max][Nax + 10][2] ;
long long f1[Max][Nax + 10] , g1[Max][Nax + 10] ;
int Pin[Max] , n ;
int C[Max] , m ;
bool Fal[Max] ;
long long Ans ; 
char a[Max] ;
int Plu ; 
int main( ) {
	scanf("%s" , ( a + 1 ) ) ;
	n = strlen( a + 1 ) ;  // 注意，这里的n表示题目中n的位数
	for(int i = 1 ; i <= n ; i ++ ) 
		Pin[i] = a[i] - '0' ;//Pin[i]表示题目中n的第i高位的数字
	scanf("%d" , &m ) ; 
	for(int i = 1 ; i <= m ; i ++ ) {
		scanf("%d" ,  &C[i] ) ;
		Fal[C[i]] = true ;
		Plu |= ( 1 << C[i] ) ; 
	}
	for(int i = 1 ; i <= Pin[1] ; i ++ ) { // 初始化
		if( i < Pin[1] ) f[1][ ( 1 << i ) ][0] = i , g[1][ ( 1 << i ) ][0] = 1 ; 
		else if( i == Pin[1] ) f[1][ ( 1 << i ) ][1] = i , g[1][ ( 1 << i ) ][1] = 1 ; 
	} 
	for(int l = 1 ; l <= 9 ; l ++ ) f1[1][(1 << l)] = l , g1[1][(1 << l)] = 1 ;
   //Nax - 1 = ( 1 << 10 ) - 1 
	for(int l = 0 ; l <= Nax - 1 ; l ++ ) { 
		for(int i = 1 ; i <= n - 1 ; i ++ ) { 
			for(int k = 0 ; k <= 9 ; k ++ ) { 		
				int p = i + 1 , t = l | ( 1 << k ) ; 
				if( k == Pin[i + 1] ) {
					f[p][t][1] = ( f[p][t][1] + ( f[i][l][1] * 10 % mod + g[i][l][1] * k % mod ) % mod ) % mod ; 
					g[p][t][1] = ( g[p][t][1] + g[i][l][1] ) % mod ; 
				}
				if( k < Pin[i + 1] ) {
					f[p][t][0] = ( f[p][t][0] + ( f[i][l][1] * 10 % mod + g[i][l][1] * k % mod ) % mod  ) % mod ; 
					g[p][t][0] = ( g[p][t][0] + g[i][l][1] ) % mod ; 
				}
				f[p][t][0] = (	f[p][t][0] + ( f[i][l][0] * 10 % mod + g[i][l][0] * k % mod ) % mod ) % mod ; 
				g[p][t][0] = ( g[p][t][0] + g[i][l][0] ) % mod ; 
				
				f1[p][t] = ( f1[p][t] + ( f1[i][l] * 10 % mod + g1[i][l] * k % mod ) % mod ) % mod ; 
				g1[p][t] = ( g1[p][t] + g1[i][l] ) % mod ;
			}
			
		}
	}
	for(int l = 0 ; l <= Nax - 1 ; l ++ ) {
		if( ( l & Plu ) != Plu ) continue ; // 判断状态是否满足 M 个数的限制
		Ans = ( Ans + ( f[n][l][1] + f[n][l][0] ) % mod ) % mod ; 
		for(int i = 1 ; i <= n - 1 ; i ++ ) Ans = ( Ans + f1[i][l] ) % mod ; 
	}
	printf("%lld\n" , Ans ) ; 
	return false ; 
}
```



---

## 作者：igAC (赞：1)

# $\text{Description}$

唉。

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc235_f)

[AT link](https://atcoder.jp/contests/abc235/tasks/abc235_f)

简要题意：

$[1,n]$ 内包含 $c_1,\dots,c_m$ 的所有数之和。

# $\text{Solution}$

数位 dp。

$ m \le 10$，显然压成二进制数。

记 $f_{i,mask,lim,zero}$ 表示枚举到第 $i$ 位，出现集合为 $mask$，是否为上限，是否为前导零的答案，$g_{i,mask,lim,zero}$ 表示方案数。

转移显然，当前位填 $dig$ 的贡献为 $dig$ 乘方案数，转移的时候可以用结构体做。

然后注意一下前导零的问题。

代码很唐，和它的 coder 一样。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 10005
#define S 1024
#define Mod 998244353
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
string s;
struct node{
	int sum,cnt;
	friend node operator + (const node &a,const node &b){
		return (node){(a.sum+b.sum)%Mod,(a.cnt+b.cnt)%Mod};
	}
	friend bool operator != (const node &a,const node &b){
		return (a.sum!=b.sum || a.cnt!=b.cnt);
	}
};
int a[N],tot,m,pos[10],pw[N]={1};
bool vis[10];
node f[N][S][2][2];
node dfs(int now,int mask,bool lim,bool zero){
	if(!now) return (node){0,mask==(1<<m)-1};
	if(f[now][mask][lim][zero]!=(node){-1,-1}) return f[now][mask][lim][zero];
	node res=(node){0,0};int l=lim?a[now]:9;
	for(int i=0;i<=l;++i){
		if(!i && vis[i]){
			if(zero){
				node t=dfs(now-1,mask,lim && i==l,zero && !i);
				t.sum=(t.sum+(pw[now-1]*i)%Mod*t.cnt)%Mod;
				res=res+t;
			}
			else{
				node t=dfs(now-1,mask|(1<<pos[i]),lim && i==l,zero && !i);
				t.sum=(t.sum+(pw[now-1]*i)%Mod*t.cnt)%Mod;
				res=res+t;
			}
			continue;
		}
		if(vis[i]){
			node t=dfs(now-1,mask|(1<<pos[i]),lim && i==l,zero && !i);
			t.sum=(t.sum+(pw[now-1]*i)%Mod*t.cnt)%Mod;
			res=res+t;
		}
		else{
			node t=dfs(now-1,mask,lim && i==l,zero && !i);
			t.sum=(t.sum+(pw[now-1]*i)%Mod*t.cnt)%Mod;
			res=res+t;
		}
	}
	return f[now][mask][lim][zero]=res;
}
signed main(){
	cin>>s;reverse(s.begin(),s.end());
	while(s.back()=='0') s.pop_back();
	for(char c:s) a[++tot]=c-48;
	for(int i=1;i<=tot;++i) pw[i]=(pw[i-1]*10)%Mod;
	m=read();
	for(int i=0;i<m;++i){
		int x=read();
		vis[x]=true,pos[x]=i;
	}
	for(int i=0;i<=tot;++i) for(int j=0;j<(1<<m);++j) for(int p=0;p<=1;++p) for(int q=0;q<=1;++q) f[i][j][p][q]=(node){-1,-1};
	printf("%lld",dfs(tot,0,1,1).sum);
	return 0;
}
```

---

## 作者：Disjoint_cat (赞：1)

# [ABC235F](https://www.luogu.com.cn/problem/AT_abc235_f)

## 题意

求 $1\sim n$ 中，十进制表示（不含前导 $0$）同时包含数字 $c_1,c_2,\ldots,c_m$ 的数字个数。

$n\le10^{10^4}$。

## 题解

看到这么大的 $n$，立刻想到数位 dp。设 $n$ 的位数为 $w$，$\{c_1,\ldots,c_m\}=C$。

由于位数不固定（而依次考虑位数会使复杂度升高），考虑从低到高填数位。

令 $cnt_{i,S,0/1/2,0/1},sum_{i,S,0/1/2,0/1}$ 为：

> 已经填了最后 $i$ 位，出现过的数集合为 $S$，这 $i$ 位（组成的数）小于/等于/大于 $n$ 的最后 $i$ 位，最后填的那一位是/不是 $0$
>
> 的整数的个数，与这些数的和。（~~怕别人念起来费劲，换个行~~）

设现在的状态是 $(i,S,j,k)$，则转移的时候：

> 枚举下一位的值，假设为 $o$，且 $n$ 的对应位为 $x$，则计算由此达到的状态 $(i',S',j',k')$；
>
> - 显然 $i'=i+1,S'=S\cup\{o\}$；
>
> - 如果 $o<x$，则 $j'=0$；如果 $o>x$，则 $j'=2$；如果 $o=x$，则 $j'=j$。（~~这不也是显然的吗~~）
>
> - 如果 $o=0$，则 $k'=0$；否则 $k'=1$。（即 $k'=[o>0]$）

转移方程也不难写：

$$cnt_{i',S',j',k'}\gets cnt_{i',S',j',k'}+cnt_{i,S,j,k},$$

$$sum_{i',S',j',k'}\gets sum_{i',S',j',k'}+sum_{i,S,j,k}+o\cdot cnt_{i,S,j,k}\cdot 10^i.$$

而最后统计答案时，一个 $(i,S,j,k)$ 被计入答案当且仅当：

$$C\subseteq S\land k=1\land(i<w\lor j\le1).$$

也很显然。

时间复杂度 $\Theta(n2^{|\Sigma|}|\Sigma|)$，其中 $|\Sigma|=10$。但理论上转移次数可达到 $10^4\times2^{10}\times3\times2\times10\approx6\times10^8$，需要卡常才能通过。

## Code

[Submission](https://atcoder.jp/contests/abc235/submissions/47172363)，跑了 $1796$ 毫秒（还经过卡常），可以直观看到转移次数较大。

## 总结

感觉只要想到这个状态设计之后就很顺畅。~~但是这个状态貌似并不容易想到。~~

也许有更优做法，只是我太弱了。

---

