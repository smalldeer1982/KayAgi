# Enormous Atcoder Railroad

## 题目描述

[problemUrl]: https://atcoder.jp/contests/s8pc-4/tasks/s8pc_4_e



## 说明/提示

### 制約

- $ 2\ <\ =\ K\ <\ =\ 2500 $.
- $ 1\ <\ =\ X\ <\ =\ 2500 $.
- $ S_0\ =\ 0,\ S_{K-1}\ =\ N $.
- $ 1\ <\ =\ S_{i\ +\ 1}\ -\ S_i\ <\ =\ 10000 $.

### 得点

 小課題1 \[$ 120 $ 点\]

- $ N,\ K,\ X\ <\ =\ 15 $.
 
 小課題2 \[$ 90 $ 点\]   
- K, X &lt;= 15
. - $ S_{i\ +\ 1}\ -\ S_i\ <\ =\ 15 $.
 
 小課題3 \[$ 260 $ 点\]   
- $ K,\ X\ <\ =\ 40 $.
- $ S_{i\ +\ 1}\ -\ S_i $ ≦ $ 40 $.
 
 小課題4 \[$ 160 $ 点\]   
- $ K,\ X\ <\ =\ 300 $.
- $ S_{i\ +\ 1}\ -\ S_i\ <\ =\ 300 $.
 
 小課題5 \[$ 370 $ 点\]   
- 追加の制約はない。

### Sample Explanation 1

目的を達成できない駅の集合は、$ [0,\ 7],\ [0,\ 1,\ 7],\ [0,\ 1,\ 2,\ 7],\ [0,\ 1,\ 6,\ 7],\ [0,\ 1,\ 2,\ 6,\ 7],\ [0,\ 1,\ 2,\ 3,\ 6,\ 7],\ [0,\ 1,\ 2,\ 5,\ 6,\ 7],\ [0,\ 1,\ 2,\ 3,\ 5,\ 6,\ 7],\ [0,\ 1,\ 2,\ 3,\ 4,\ 5,\ 6,\ 7] $ の $ 9 $ 個です。 よって、合計で $ 2^6\ -\ 9\ =\ 55 $ 個となります。

## 样例 #1

### 输入

```
7 2 3
0 7```

### 输出

```
55```

# 题解

## 作者：Union_of_Britain (赞：3)

首先一定是先坐地铁到某个地铁区间再公交/走路。

设要求为 $k$ 步。一个两端需要 $a,b$ 步走到的公交区间长度至多是 $2k+1-a-b$。因此设 $F_a=x+x^2+...+x^a$，

则第一个地铁区间（长度为 $L$）的答案是 $[x^L]F_{2k}+F_{2k}F_{2k-1}+F_{2k}F_{2k-2}^2+F_{2k}F_{2k-2}^2F_{2k-3}+\dots$。第 $i$ 段则是 $k\gets k-i+1$ 的结果。

注意答案式奇偶项分拆开（代码里是 $F,G$）之后可以写成秦九韶算法的形式，因此直接从小到大处理 $k$ 同时统计每段答案即可。$F_a$ 的乘法当然不需要 FFT，而是前缀和优化。

时间复杂度 $O(V(K+X))$，其中 $V=\max (S_i-S_{i-1})$。

也有更简单的 dp 做法。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int n,m,k,p[2505],V=10000;
struct Poly{
	int s[10005],f[10005];
	inline int Get(int l,int r){
		if(l<0)l=0;if(l>r)return 0;
		return l==0?s[r]:(s[r]-s[l-1]+mod);
	}
	inline void mul(int a){
		for(int i=0;i<=V;i++){
			f[i]=Get(i-a,i-1);
			if(f[i]>=mod)f[i]-=mod;
		}
		s[0]=f[0];for(int i=1;i<=V;i++){
			s[i]=(s[i-1]+f[i]);
			if(s[i]>=mod)s[i]-=mod;
		}
	}
	inline void pre(int p){
		for(int i=0;i<=V;i++)f[i]=s[i]=0;f[p]=1;
		for(int i=p;i<=V;i++)s[i]=1;
	}
};
inline Poly operator +(Poly A,const Poly &B){
	for(int i=0;i<=V;i++)(A.f[i]+=B.f[i]),(A.s[i]+=B.s[i]);
	for(int i=0;i<=V;i++){
		if(A.f[i]>=mod)A.f[i]-=mod;
		if(A.s[i]>=mod)A.s[i]-=mod;
	}
	return A;
}
Poly F,G;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	int ans=1;
	for(int i=1;i<=m;i++)cin>>p[i];
	if(m>k+1)return cout<<0<<endl,0;
	if(m==k+1&&p[m]-p[m-1]!=1)return cout<<0<<endl,0;	
	F.pre(1);
	for(int i=2;i<=2*k;i+=2){
		int t=(2*k+1-i)/2+1;
		F.mul(i),F.mul(i-2);
		G.mul(i),G.mul(i-2);
		Poly cur;cur.pre(0);
		cur.mul(i);F=F+cur;
		cur.mul(i-1);G=G+cur;
		if(t<m){
			int L=p[t+1]-p[t];
			(ans*=(F.f[L]+G.f[L]))%=mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Y204335 (赞：3)

# AT\_s8pc\_4\_e Enormous Atcoder Railroad

## 题目大意

有 $N+1$ 个点，编号为 $0\sim N$，相邻的点可以花 $1$ 的时间互相到达，有一条经过 $K$ 个点的线路 $A$，在线路上相邻的点也可以花 $1$ 的时间互相到达。现在要求再加入一条线路 $B$，要经过 $A$ 经过的所有点，且使得从 $0$ 点到每个点的时间不超过 $X$。求符合条件的方案数。（注意点呈直线排列，同一种方式只能走到最近的点之一）

## 题目分析

可以很容易地发现，由于 $A$ 经过的点 $B$ 也要经过，所以 $A$ 所经过的点将所有点分为了**互不影响的小段**（显然可以先从 $A$ 路线到达这一段的左端点，再走 $B$ 路线或直接走，这样一定不劣），所以只要求出满足每一段条件的方案数，再相乘即可。又因为每一段的地位都是等价的，所以可以尝试**统一处理**。

显然一个小段的答案只和到达这一段左端点的**最短时间**以及这一段的**长度**有关，并且数据范围中 $K$ 与 $\Delta S$ 并不算大，可以尝试 dp。

设 $f_{i,j}$ 为区间长度为 $i$，到达左端点的最短时间为 $j$ 的方案数。

1. $B$ 不经过中间。当 $i-1\le \left(x-j\right)+\left(x-j-1\right)$ 时，不用经过中间也能满足条件。

2. $B$ 经过中间。枚举断点，设当前已经有长度为 $k$ 的一段满足条件（钦定右边一段已经满足，因为从右边转移时间一定不劣），则要能转移需要满足 $i-k-1\le\left(x-j\right)+\left(x-j-1\right)$，如图。![1](https://cdn.luogu.com.cn/upload/image_hosting/025513qq.png)

可以注意到此时需要从**两端到达时间相同**的段进行转移，而我们只考虑了两端到达时间相差 $1$ 的情况，因此要修改 dp 状态。

设 $f_{i,j,0/1}$ 为区间长度为 $i$，到达左端点的最短时间为 $j$，到达右端点的最短时间为 $j+0/1$ 的方案数。

$f_{i,j,1}$ 的情况和上面一样，现在分析 $f_{i,j,0}$ 的情况。

1. $B$ 不经过中间。当 $i-1\le \left(x-j\right)+\left(x-j\right)$ 时，不用经过中间也能满足条件。

2. $B$ 经过中间。同样枚举断点，设当前已经有长度为 $k$ 的一段满足条件（从左、右转移都行，这里钦定从左边转移），则要能转移需要满足 $i-k-1\le\left(x-j\right)+\left(x-j-1\right)$，如图。![2](https://cdn.luogu.com.cn/upload/image_hosting/j38xxzx0.png)

所以总的转移方程为。

$$f_{i,j,1}=\sum_{k}^{}f_{k,j+1,0}+\left[i-1\le \left(x-j\right)+\left(x-j-1\right)\right]\left(i-k-1\le\left(x-j\right)+\left(x-j-1\right)\right)$$

$$f_{i,j,0}=\sum_{k}^{}f_{k,j,1}+\left[i-1\le \left(x-j\right)+\left(x-j\right)\right]\left(i-k-1\le\left(x-j\right)+\left(x-j-1\right)\right)$$

可以发现求和是个前缀的形式，求前缀和就可以把转移优化为 $O(1)$。

边界条件为 $f_{1,x,0}=1$，时间复杂度为 $O\left(\Delta SK\right)$，dp 处理完后再根据给出的 $A$ 线路情况取用相应的数据即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int S = 1e4 + 10, X = 2510, mod = 1e9 + 7;
ll n, k, x, dp[S][X][2], pre[2], ans = 1, lst, s;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k >> x;
    dp[1][x][0] = 1;
    for (int i = x - 1; i >= 0; i--) {
        pre[0] = pre[1] = 0;
        for (int j = 1; j <= S - 10; j++) {
            pre[0] += dp[j - 1][i + 1][0];
            if (2 * i - 2 * x + j - 1 >= 0)
                pre[0] += mod - dp[2 * i - 2 * x + j - 1][i + 1][0]; // 只要有不符合条件的就删去，现在不符合条件，之后也一定不符合
            pre[0] %= mod;
            dp[j][i][1] = pre[0];
            if (j <= 2 * x - 2 * i)
                dp[j][i][1]++;
            dp[j][i][1] %= mod;
        }
        for (int j = 1; j <= S - 10; j++) {
            pre[1] += dp[j - 1][i][1];
            if (2 * i - 2 * x + j - 1 >= 0)
                pre[1] += mod - dp[2 * i - 2 * x + j - 1][i][1];
            pre[1] %= mod;
            dp[j][i][0] = pre[1];
            if (j <= 2 * x - 2 * i + 1)
                dp[j][i][0]++;
            dp[j][i][0] %= mod;
        }
    }
    for (int i = 1; i <= k; i++) {
        cin >> s;
        if (i > 1) {
            ans = ans * dp[s - lst][i - 2][1] % mod;
        }
        lst = s;
    }
    cout << ans << endl;
    return 0;
}
```

---

