# Xor

## 题目描述

### 题意翻译

给定四个长度为 $n$，下标从 $1$ 到 $n$ 的数组 $a$，$b$，$k$，$p$，保证 $p_1, p_2,\cdots, p_n$ 是 $1, 2,\cdots, n$ 的一个排列。

你要对数组 $a$ 进行恰好 $u$ 次操作，每次可以在以下两种操作中选择一种：

1. 对所有 $i = 1, 2,\cdots, n$，将 $a_i$ 修改为 $a_i \oplus b_i$。($\oplus$ 表示异或)

1. 对所有 $i = 1, 2,\cdots, n$，将 $a_i$ 修改为 $a_{p_i} + r$。

请问，$u$ 次操作之后 $\sum \limits _{i=1}^n a_i \times k_i$ 最大为多少。

## 样例 #1

### 输入

```
3 2 1
7 7 7
8 8 8
1 2 3
1 3 2
```

### 输出

```
96
```

## 样例 #2

### 输入

```
2 1 0
1 1
1 1
1 -1
1 2
```

### 输出

```
0
```

# 题解

## 作者：CaiXY06 (赞：6)

看波数据范围，$n,u\leq30$，显然很暴搜，但是直接做的话，复杂度是 $O(n\times 2^u)$ 的，当场阵亡，所以我们考虑如何优化。

我们注意到异或的性质：连续异或两次等于啥也没干。为了尽可能获得最大的答案，我们当然希望少做，或不做无用功。所以我们可以在暴搜的时候存一个标记，表示当前是否可以异或，如果这次操作异或了，那么下次就不需要了。但是如果这样优化的话会出现一些问题，就是如果这个数列已经最优，也就是要给他保持原样，你一打标记，显然就会出现问题。那么当还有偶数次操作机会时，我们就可以直接计算当前的答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,R,A[40],B[40],K[40],P[40],ans=-1e18;
inline void dfs(int x,int *A,int t){
	if(x==m+1){
		int res=0;
		for(int i=1;i<=n;i++)res+=A[i]*K[i];
		ans=max(ans,res);
		return;
	}
	int C[40];
	if(!((m-x+1)&1))dfs(m+1,A,1);
	if(t){
		for(int i=1;i<=n;i++)C[i]=A[i]^B[i];
		dfs(x+1,C,0);
	}
	for(int i=1;i<=n;i++)C[i]=A[P[i]]+R;
	dfs(x+1,C,1);
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&R);
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&B[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&K[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&P[i]);
	dfs(1,A,1);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：chaynflow (赞：1)

## Description

给你一串序列和两种操作，求最后一个序列乘上对应权值的最大值。

## Solution

为什么题面这么简单呢？因为本质上就是爆搜，当然，如果你直接 $O(n \times 2^{n})$ 去搜肯定会炸，考虑优化。

我们知道异或的一个性质，$a \oplus b \oplus b = a$，所以连续异或两次毫无意义，我们直接在爆搜是打上标记 $x$，表示上一次是不是异或，如果 $x=1$ 就不异或了。

但是这样会喜提 wa on #10，为什么？

考虑这样一种情况，在还剩 $2t$ 次操作时，已经达到了最优，此时可以一直用异或运算来保持这个最优解，但是因为你的标记，让他无法异或。所以我们考虑在每次剩余操作数量 $k \bmod 2 = 0$ 时就计算答案，这样就可以保住最优解。

时间复杂度为 $O(f_{n+1} \times n)$，$f_n$ 是第 $n$ 个斐波那契数，大概是 $1346269 \times 30$ 的，可以通过。

## Code

~~不要变量重名了~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 35;
int n, u, R, a[N], b[N], k[N], p[N];
int ans = -2e18;
void calc(vector <int> num)
{
	int res = 0;
	for (int i = 1; i <= n; i++) res += num[i] * k[i];
	ans = max(ans, res);
}
void dfs(vector <int> num, int r, bool x) // r = 剩余次数 k
{
	if (r % 2 == 0) calc(num);
	if (!r) return;
	vector <int> A = num, B = num;
	if (!x)
	{
		for (int i = 1; i <= n; i++) A[i] ^= b[i];
		dfs(A, r - 1, 1);
		for (int i = 1; i <= n; i++) A[i] ^= b[i];
	}
	for (int i = 1; i <= n; i++) A[i] = B[p[i]] + R;
	dfs(A, r - 1, 0);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> u >> R; vector <int> num; num.push_back(0);
	for (int i = 1; i <= n; i++) cin >> a[i], num.push_back(a[i]);
	for (int i = 1; i <= n; i++) cin >> b[i];
	for (int i = 1; i <= n; i++) cin >> k[i];
	for (int i = 1; i <= n; i++) cin >> p[i];
	dfs(num, u, 0);
	cout << ans;
    return 0;
}
```


---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF193B)

duel bot.duel bot.duel bot.

$u$ 这么小，爆搜！

当然要剪枝，连续两次 xor 是毫无意义的，不如留点操作次数去更大化答案，于是传个标记表示现在能不能 xor。

但是如果从某个状态起不操作为最优，这是不会被算法考虑到的，那么就通过偶数次 xor 操作来模拟“不操作”，其实就是直接计算答案。

然后就可以过了，复杂度玄学。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=40;
int n,m,r,a[N],b[N],p[N],k[N];
long long ans=-1e18;
void dfs(int u,int l[40],bool op){
    if(u>m){
        long long res=0;
        for(int i=1;i<=n;i++)res+=1ll*l[i]*k[i];
        ans=max(ans,res);
        return;
    }
    if(!(m-u+1&1))dfs(m+1,l,1);
    int h[N];
    if(op){
        for(int i=1;i<=n;i++)h[i]=l[i]^b[i];
        dfs(u+1,h,0);
    }
    for(int i=1;i<=n;i++)h[i]=l[p[i]]+r;
    dfs(u+1,h,1);
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d%d",&n,&m,&r);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)scanf("%d",&k[i]);
    for(int i=1;i<=n;i++)scanf("%d",&p[i]);
    dfs(1,a,1);
    printf("%lld\n",ans);
    system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/123666890)

---

