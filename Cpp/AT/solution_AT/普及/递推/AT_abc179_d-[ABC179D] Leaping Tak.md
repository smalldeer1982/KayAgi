# [ABC179D] Leaping Tak

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc179/tasks/abc179_d

一列に並んだ $ N $ マスから成るマス目があり、マスには左から順番に$ 1,\ 2,\ \ldots,\ N $ の番号がついています。

このマス目で暮らしている高橋君は、現在マス $ 1 $ にいて、後述の方法で移動を繰り返してマス $ N $ へ行こうとしています。

$ 10 $ 以下の整数 $ K $ と、共通部分を持たない $ K $ 個の区間 $ [L_1,\ R_1],\ [L_2,\ R_2],\ \ldots,\ [L_K,\ R_K] $ が与えられ、これらの区間の和集合を $ S $ とします。ただし、区間 $ [l,\ r] $ は $ l $ 以上 $ r $ 以下の整数の集合を表します。

- マス $ i $ にいるとき、$ S $ から整数を $ 1 $ つ選んで ($ d $ とする)、マス $ i\ +\ d $ に移動する。ただし、マス目の外に出るような移動を行ってはならない。

高橋君のために、マス $ N $ に行く方法の個数を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1 \leq\ K\ \leq\ \min(N,\ 10) $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ [L_i,\ R_i] $ と $ [L_j,\ R_j] $ は共通部分を持たない ($ i\ \neq\ j $)
- 入力はすべて整数である

### Sample Explanation 1

集合 $ S $ は 区間 $ [1,\ 1] $ と区間 $ [3,\ 4] $ の和集合であり、$ S\ =\ \{\ 1,\ 3,\ 4\ \} $ です。 マス $ 5 $ へ移動する方法は次の $ 4 $ 通りが考えられます。 - マス $ 1,\ 2,\ 3,\ 4,\ 5 $ の順に移動する。 - マス $ 1,\ 2,\ 5 $ の順に移動する。 - マス $ 1,\ 4,\ 5 $ の順に移動する。 - マス $ 1,\ 5 $ の順に移動する。

### Sample Explanation 2

$ S\ =\ \{\ 3,\ 5\ \} $ であり、そもそもマス $ 5 $ にたどり着けないので $ 0 $ を出力してください。

### Sample Explanation 4

$ 998244353 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
5 2
1 1
3 4```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2
3 3
5 5```

### 输出

```
0```

## 样例 #3

### 输入

```
5 1
1 2```

### 输出

```
5```

## 样例 #4

### 输入

```
60 3
5 8
1 3
10 15```

### 输出

```
221823067```

# 题解

## 作者：Nicrobot (赞：5)

upd：更新代码错误。

---
首先有显然的 DP:

$$f(i)=\sum_{j \in S \  \text{and}\ i-j>0}f(i-j)$$


因为 $|S|$ 最大为 $n$，这样时间复杂度为 $O(n^2)$，不能通过。

注意到 $S$ 是 $k$ 段**不交**区间组成的，且 $k$ 很小。把原转移方程转换下：

$$f(i)=\sum_{1\le j\le k} \sum_{l_j\le m \le r_j \ \text{and}\  i-m>0}f(i-m)$$

显然第二个 $\sum$ 可以前缀和优化，把 $f$ 数组进行前缀和，然后省掉第二个求和。

时间复杂度 $O(nk)$。


细节：

- 注意判断边界 $f(1)=1$。
- 注意可能有取不到的 $m$，要和 $0$ 取 $\max$。
- 注意涉及到减，一定要 `(ans + mod) % mod`。

核心代码：


```cpp
f[1] = s[1] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= k; j++) {
			f[i] += s[max(0, i - l[j])] - s[max(0, i - r[j] - 1)];
			f[i] += mod;
			f[i] %= mod;
		}
		s[i] = s[i - 1] + f[i];
		s[i] %= mod;
	}
	cout << (f[n] + mod) % mod;
```

---

## 作者：Down_syndrome (赞：3)

## 思路
对于这道题，可以利用 dp 的思想。令 $f_i$ 表示走到 $i$ 的方案数，则有以下式子。
$$f_i=\sum\limits_{j=1}^k\sum\limits_{h=L_j}^{R_j}f_{\max(i-h,0)}$$
因为 $\sum\limits_{h=L_j}^{R_j}f_{\max(i-h,0)}$ 是连续的，所以以上式子可以用前缀和优化，则有以下式子。
$$f_i=f_{i-1}+\sum\limits_{j=1}^kf_{\max(i-l_j,0)}-f_{\max(i-r_j-1,0)}$$
最后的答案则为 $f_n-f_{n-1}$。时间复杂度 $O(nk)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int mod=998244353;
int n,k,l[15],r[15],f[N];
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=k;i++) scanf("%lld%lld",&l[i],&r[i]);
	f[1]=1;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=k;j++) f[i]=(f[i]+(f[max(i-l[j],0ll)]-f[max(i-r[j]-1ll,0ll)]+mod)%mod)%mod;
		f[i]=(f[i]+f[i-1])%mod;
	}
	printf("%lld",(f[n]-f[n-1]+mod)%mod);
	return 0;
} 
```


---

## 作者：lilong (赞：0)

### 题意

给定 $n$ 和 $k$ 个区间，并且保证 $ k \le 10$ 且互不相交。可以进行任意次操作，每次可以选择一个整数 $j$，$j$ 要满足在其中一个给定的区间上，从当前位置向右移动 $j$ 的距离。求 $1$ 到 $n$ 的方案数。

### 思路

提供一种数据结构的做法。

依次枚举 $1$ 到 $n$ 的每个点，对于每个点，先查询其方案数（已知），然后枚举每个区间，确定从当前点出发能跳到的区间，对其进行修改，最后查询 $n$ 的方案数即可。

在本题中，需要支持区间修改和单点查询，树状数组是最佳选择。因此实现就非常简单了。

代码如下：
```cpp
#include <iostream>
#include <cstdio>
#define MOD 998244353
using namespace std;
int n,m,l[101],r[101],b[1000001],t,ll,rr;
int lowbit(int x)
{
	return x & -x;
}
int qh(int x)
{
	int ans = 0;
	for( int i = x ; i >= 1 ;i -= lowbit(i) )
		ans = ( ans + b[i] ) % MOD;
	return ans;
}
void xg(int x,int y)
{
	for( int i = x ; i <= n ;i += lowbit(i) )
		b[i] = ( ( b[i] + y ) % MOD + MOD) % MOD;
	return;
}
int main()
{
	cin >> n >> m;
	for( int i = 1 ; i <= m ; i++ )
		cin >> l[i] >> r[i];
	xg ( 1 , 1 );//初始值为1
	xg ( 2 , -1 );
	for(int i = 1;i <= n;i++)
	{
		t = qh(i);
//		cout << qh(n) << ' ' << t << endl; 
		for( int j = 1 ; j <= m ; j++ )
		{
			ll = i + l[j];
			rr = min ( i + r[j] , n );
			if ( ll <= n )
			{
				xg ( ll , t );
				xg ( rr + 1 , -t );
			}
		}
	}
	cout << qh(n);
	return 0;
}
```


---

## 作者：LiJinLin_AFO (赞：0)

# AT_abc179_d 题解
仔细观察本题，本题考察 DP 算法。

设 $a_i$ 为从 $1$ 开始到达 $n$ 的方案数，则可以枚举所有范围的所有数。如果数 $m$ 在某个范围内，则判断 $n-m$ 是否大于 $0$，是则加上 $a_{n-m}$。

温馨提示：别忘记除以~~那个像谢特一样的~~ $998244353$。

```cpp
#include<stdio.h>
const int mod=998244353;
struct r{
    int l,r;
}all[15];
int a[200005];
int f(int n){
    if(n<1) return 0;
    return a[n];
}//返回a[n-m]
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++){
        scanf("%d%d",&all[i].l,&all[i].r);
    }
    a[1]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=k;j++){
            for(int l=all[j].l;l<=all[j].r;l++) a[i]=(a[i]+f(i-l))%mod;
        }
    }//行云流水的操作
    printf("%d",a[n]%mod);
    return 0;
}
```


---

