# Planar Reflections

## 题目描述

Gaurang has grown up in a mystical universe. He is faced by $ n $ consecutive 2D planes. He shoots a particle of decay age $ k $ at the planes.

A particle can pass through a plane directly, however, every plane produces an identical copy of the particle going in the opposite direction with a decay age $ k-1 $ . If a particle has decay age equal to $ 1 $ , it will NOT produce a copy.

For example, if there are two planes and a particle is shot with decay age $ 3 $ (towards the right), the process is as follows: (here, $ D(x) $ refers to a single particle with decay age $ x $ )

1. the first plane produces a $ D(2) $ to the left and lets $ D(3) $ continue on to the right;
2. the second plane produces a $ D(2) $ to the left and lets $ D(3) $ continue on to the right;
3. the first plane lets $ D(2) $ continue on to the left and produces a $ D(1) $ to the right;
4. the second plane lets $ D(1) $ continue on to the right ( $ D(1) $ cannot produce any copies).

In total, the final multiset $ S $ of particles is $ \{D(3), D(2), D(2), D(1)\} $ . (See notes for visual explanation of this test case.)

Gaurang is unable to cope up with the complexity of this situation when the number of planes is too large. Help Gaurang find the size of the multiset $ S $ , given $ n $ and $ k $ .

Since the size of the multiset can be very large, you have to output it modulo $ 10^9+7 $ .

Note: Particles can go back and forth between the planes without colliding with each other.

## 说明/提示

Let us explain the first example with four test cases.

Test case 1: ( $ n = 2 $ , $ k = 3 $ ) is already explained in the problem statement.

See the below figure of this simulation. Each straight line with a different color represents the path of a different particle. As you can see, there are four distinct particles in the multiset. Note that the vertical spacing between reflected particles is for visual clarity only (as mentioned before, no two distinct particles collide with each other)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1498C/df04d989fa23babd02f74b8b57d3f2d7886e9f14.png)Test case 2: ( $ n = 2 $ , $ k = 2 $ ) is explained as follows:

1. the first plane produces a $ D(1) $ to the left and lets $ D(2) $ continue on to the right;
2. the second plane produces a $ D(1) $ to the left and lets $ D(2) $ continue on to the right;
3. the first plane lets $ D(1) $ continue on to the left ( $ D(1) $ cannot produce any copies).

Total size of multiset obtained $ \{D(1), D(1), D(2)\} $ is equal to three.

Test case 3: ( $ n = 3 $ , $ k = 1 $ ), there are three planes, but decay age is only one. So no new copies are produced while the one particle passes through the planes. Hence, the answer is one.

Test case 4: ( $ n = 1 $ , $ k = 3 $ ) there is only one plane. The particle produces a new copy to the left. The multiset $ \{D(2), D(3)\} $ is of size two.

## 样例 #1

### 输入

```
4
2 3
2 2
3 1
1 3```

### 输出

```
4
3
1
2```

## 样例 #2

### 输入

```
3
1 1
1 500
500 250```

### 输出

```
1
2
257950823```

# 题解

## 作者：Composite_Function (赞：7)

# 思路

来水 CF 思维题了

DP 很好想，但如何写状态呢

会发现，一个粒子的贡献，仅取决于它的能量，和它前面还有多少个平面

所以可做出我的方法：

1. 状态：$\text{dp[i][j]}$ 表示能量为 $i$，前面有 $j$ 个平面
2. 转移方程：$\text{dp[i][j]} = \text{dp[i][j - 1]} + \text{dp[i - 1][n - j]}$
3. $\forall i = 1, 2, ..., k, \text{dp[i][0]} = 1, \forall i = 1, 2, ..., k, \text{dp[1][i]} = 1$

时间复杂度：$O(\sum nk)$

------------

# 代码

```cpp
# include <bits/stdc++.h>
using namespace std;
# define int long long
const int N = 1010, mod = 1e9 + 7;
int T, n, k, dp[N][N];
signed main()
{
    cin >> T;
    while (T--) {
        cin >> n >> k;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= k; ++i) dp[i][0] = 1;
        for (int i = 1; i <= n; ++i) dp[1][i] = 1;
        for (int i = 1; i <= k; ++i)
        	for (int j = 1; j <= n; ++j)
        		dp[i][j] = (dp[i][j - 1] + dp[i - 1][n - j]) % mod;
        cout << dp[k][n] << endl;
    }
    return 0;
}
```

------------

# 后记

最近再刷思维题，附上有趣的：CF1733E

---

## 作者：httohu (赞：5)

**分方向讨论**

向右飞遇到平面可以生成向左飞的粒子，并且生成的粒子寿命比原粒子-1，这个粒子一直向右飞会一直撞平面生成粒子。而生成的粒子也可以继续这样生成粒子。得到如下方程,

---

$$f(k,i,0)=1+\sum\limits_{j=i}^n{f(k-1,j,1)}$$

* $k$表示当前粒子寿命，
* $i$表示当前粒子右边的第一个平面位置，
* $0$表示向右飞1表示向左飞。

同理我们可以得到向左飞的方程

$$f(k,i,1)=1+\sum\limits_{j=1}^{i-1}{f(k-1,j+1,0)}$$

一开始向左飞的方程没写$j+1$一直在调qaq，还是太菜了。画个图就知道啦。

用前缀和处理$\sum$可以得到 $\sout{O(AC)}$ $O(nk)$ 的方法

附上代码

---

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
const int maxn = 1005;
// D(k) pos 0:right/1:left
int dp[maxn][maxn][2];
int sum[maxn][maxn][2];
int mod(int x)
{
    const int mm = 1e9 + 7;
    return (x % mm + mm) % mm;
}
void solve()
{
    int N, K;
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        dp[1][i][0] = dp[1][i][1] = 1;
        sum[1][i][0] = sum[1][i - 1][0] + dp[1][i][0];
        sum[1][i][1] = sum[1][i - 1][1] + dp[1][i][1];
    }
    for (int k = 2; k <= K; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            dp[k][i][0] = 1;
            dp[k][i][1] = 1;
            // for (int j = i; j <= N; j++)
            //     dp[k][i][0] = mod(dp[k][i][0] + dp[k - 1][j][1]);
            // for (int j = 1; j <= i - 1; j++)
            //     dp[k][i][1] = mod(dp[k][i][1] + dp[k - 1][j + 1][0]);
            dp[k][i][0] = mod(1 + sum[k - 1][N][1] - sum[k - 1][i - 1][1]);
            dp[k][i][1] = mod(1 + sum[k - 1][i][0] - sum[k - 1][1][0]);

            sum[k][i][0] = mod(sum[k][i - 1][0] + dp[k][i][0]);
            sum[k][i][1] = mod(sum[k][i - 1][1] + dp[k][i][1]);
        }
    }
    cout << dp[K][1][0] << endl;
}
int mian() 
{
    int kase;
    cin >> kase;
    while (kase--)
        solve();
    return 0;
}
```

---

## 作者：vectorwyx (赞：2)

考虑 dp。令 $f_{i,j,0/1}$ 表示如果一个衰变期为 $j$ 的粒子从第 $i$ 个平面的左面/右面穿过第 $i$ 个平面会产生多少个粒子。转移方程为 $f_{i,j,0}=f_{i+1,j,0}+f_{i-1,j-1,1},f_{i,j,1}=f_{i-1,j,1}+f_{i+1,j-1,0}$。初始化 $f_{0,i,1}=f_{n+1,i,0}=1$，然后直接转移，时间复杂度为 $O(nk)$。注意要先枚举第二维。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1005,lmq=1e9+7;
int f[N][N][2],n,k;

void work(){
	cin>>n>>k;
	fo(i,1,k) f[0][i][1]=1,f[n+1][i][0]=1;
	fo(i,1,n) f[i][1][1]=f[i][1][0]=1;
	fo(j,1,k){
		go(i,n,1) f[i][j][0]=(f[i+1][j][0]+f[i-1][j-1][1])%lmq;
		fo(i,1,n) f[i][j][1]=(f[i-1][j][1]+f[i+1][j-1][0])%lmq;
	}
	cout<<f[1][k][0];
	puts("");
}

int main(){
	int T=read();
	while(T--) work(); 
	return 0;
}
```


---

## 作者：Warriors_Cat (赞：2)

upd on 2021.3.31 修改了一个小笔误。

---

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1498C) & [CF 题面传送门](https://codeforces.com/problemset/problem/1498/C)。

题意简述：

* 有 $n$ 个平台和一个衰变期为 $k$ 的粒子，初始时粒子方向向右。
* 当衰变期为 $t(t \ge 2)$ 的粒子在某一个平台时，它会分裂出一个衰变期为 $t-1$ 的粒子，方向与原粒子方向相反。当粒子衰变期为 $1$ 时就不再分裂。
* 求最后总共有多少个粒子，答案对 $10^9 + 7$ 取模。
* 多测，组数 $T \le 100$。$n, k \le 10^3$。

算是一道比较显然的 dp 题？

---

### Solution：

看到数据范围便想到 $O(nk)$ 的解法，又因为是求方案数，于是考虑 dp。

考虑 dp 数组要有哪些限制条件。首先肯定有粒子的衰变期和粒子处于的平台，其次注意到粒子还有左右两个方向，于是定义 $f_{i, j, 0/1}$ 表示一个衰变期为 $j$ 的粒子到达第 $i$ 个平台且方向向左/右时能产生多少个粒子。

接下来分析状态转移。对于 $f_{i, j, 0}$，它可以直接向左走，由 $f_{i-1, j, 0}$ 得到；它也可以分裂向右走，由 $f_{i + 1, j - 1, 1}$ 得到。因此有状态转移式：

$$f_{i, j, 0} = f_{i - 1, j, 0} + f_{i + 1, j - 1, 1}$$

同理，有另外一个转移式：

$$f_{i, j, 1} = f_{i + 1, j, 1} + f_{i - 1, j + 1, 0}$$

再考虑边界，考虑往左走走出左边界和往右走走出右边界两种情况，可得 $\forall i \in [1, k], f_{n + 1, i, 0} = f_{0, i, 1} = 1$。最后答案即为 $f_{1, k, 1}$。

over，时间复杂度为 $O(nk)$。

---

### Code：

代码实现的时候注意 $f_{i, j, 1}$ 要倒序枚举 $i$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define mpr make_pair
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = x; i >= y; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 1010, mod = 1000000007;
int n, k, f[N][N][2];
inline void mian(){
	n = read(); k = read();
	rep(i, 1, k) f[0][i][0] = f[n + 1][i][1] = 1;
	rep(j, 1, k){
		rep(i, 1, n) f[i][j][0] = (f[i - 1][j][0] + f[i + 1][j - 1][1]) % mod;
		per(i, n, 1) f[i][j][1] = (f[i + 1][j][1] + f[i - 1][j - 1][0]) % mod;
	}
	printf("%d\n", f[1][k][1]);
}
int main(){ int qwq = read(); while(qwq--) mian(); return 0; }
```


---

## 作者：Bai_R_X (赞：1)

## 思路
动态规划好题，$dp_{i,j}$ 表示能量级别为 $i$ 的粒子，在经过 $j$ 堵墙后共产生的粒子数量。

动态转移方程：$dp_{i,j}=dp_{i,j-1}+dp_{i-1,n-j}$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,k,f[1005][1005],i,j,mod=1e9+7;
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(i=1;i<=n;i++)f[1][i]=1;
		for(i=1;i<=k;i++)f[i][0]=1;
		for(i=2;i<=k;i++)
		{
			for(j=1;j<=n;j++)f[i][j]=(f[i][j-1]+f[i-1][n-j])%mod;;
		}
		cout<<f[k][n]<<endl;
	}
	return 0;
}
```

---

## 作者：cunzai_zsy0531 (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/CF1498C)

这个题我提供一个 $O(n^2 \log n)$ 的做法。

首先这个题我想 $dp$ 想了挺久，没想出来，但是用线段树维护是一个很方便、很好想，码量也不大的做法，主要是看到 $n\leq 1000$，就没有必要非要用一个严格 $O(n^2)$ 的做法，主要是要尽快写出来，一边写对。

首先，我们考虑建立 $k$ 棵线段树，每一棵线段树以 $[1,n]$ 为下标记录从这个点出发的，衰变期为 $k$ 的粒子。如果我们已经算出了第 $i+1$ 层（衰变期为 $i+1$）的每个点的值，考虑如何求第 $i$ 层？

显然应该分类讨论。如果第 $i+1$ 层的粒子是向左的，那么第 $i$ 层能够从第 $j$ 个位置出发的粒子数就有 `t[i+1].query(j+1,n)` 个。这里的 `t[i].query(l,r)` 表示第 $i$ 层出发点区间 $[l,r]$ 的粒子总数。同理，可以求出另一种情况中每个点出发的粒子总数。

这样需要用到线段树单点修改和区间查询，总复杂度 $O(n^2 \log n)$。

上代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1000+13,mod=1e9+7;
int n,k;
struct SegTree{int l,r,sum;}e[N];
struct SegmentTree{//线段树维护单点修改、区间查询
	SegTree t[N<<2];
	#define ls p<<1
	#define rs p<<1|1
	#define mid ((t[p].l+t[p].r)>>1)
	inline void refresh(int p){
		t[p].sum=(t[ls].sum+t[rs].sum)%mod;
	}
	void build(int p,int l,int r,int k){
		t[p].l=l,t[p].r=r;
		if(l==r){t[p].sum=k;return;}
		build(ls,l,mid,k);build(rs,mid+1,r,k);
		refresh(p);
	}
	void update(int p,int x,int k){
		if(t[p].l==t[p].r){t[p].sum=k;return;}
		if(x<=mid) update(ls,x,k);
		else update(rs,x,k);
		refresh(p);
	}
	int query(int p,int l,int r){
		if(l<=t[p].l&&t[p].r<=r) return t[p].sum;
		int res=0;
		if(l<=mid) res=(res+query(ls,l,r))%mod;
		if(r>mid) res=(res+query(rs,l,r))%mod;
		return res;
	}
}T[N];
int main(){
	int Tt;
	scanf("%d",&Tt);
	while(Tt--){
		scanf("%d%d",&n,&k);
		if(k==1){puts("1");continue;}//注意边界特判
		for(int i=1;i<=k-2;++i) T[i].build(1,1,n,0);
		T[k-1].build(1,1,n,1);//初始化
		for(int i=k-2;i>=1;--i){
			if((k-i)&1){//分类讨论求第i层答案
				for(int j=1;j<n;++j) T[i].update(1,j,T[i+1].query(1,j+1,n));
			}
			else{
				for(int j=2;j<=n;++j) T[i].update(1,j,T[i+1].query(1,1,j-1));
			}
		}
		int ans=1;
		for(int i=1;i<=k-1;++i) ans=(ans+T[i].t[1].sum)%mod;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：JW_Yesod (赞：0)

# CF1498C Solution

## 0x01 题意

现在有一个**能量级别**为 $k$ 的粒子将要穿过 $n$ 个平面，它每穿过一个平面便会向相反方向发射一个**能量级别**为 $k-1$ 的粒子。

特别的，当**能量级别**为 $1$ 的粒子穿过平面时，**不会**发射额外的粒子。

## 0x02 思路

考虑到每个能源级别不为 $1$ 的粒子穿过平面时会朝相反方向发射一个粒子。可以理解为一个能源等级为 $i$ 的粒子穿过平面时会**消失**，同时向**原方向**发射一个能源等级为 $i$ 的粒子，再向**相反方向**发射一个能源等级为 $i-1$ 的粒子，因此可以使用**动态规划**算法。

由此我们可以列出状态转移方程：

$$
dp_{i,j}=dp_{i,j-1}+dp_{i-1,n-j}
$$

## 0x03 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsinged long long
#define Code using
#define by namespace
#define ZXB std
Code by ZXB;
const int mod=1e9+7;
ll t,n,k;
ll dp[1005][1005];//dp[i][j]表示能量级别为i的粒子穿过j个平面后总计的粒子数量 
int main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	cin>>t;
	while(t--){
		memset(dp,0,sizeof(dp));
		cin>>n>>k;
		for(int i=1;i<=n;i++){//能量级别为1的粒子穿过平面不会产生额外的粒子 
			dp[1][i]=1;
		}
		for(int i=1;i<=k;i++){//任何能量级别的粒子不穿过平面则不会产生额外的粒子 
			dp[i][0]=1;
		}
		for(int i=1;i<=k;i++){
			for(int j=1;j<=n;j++){
				dp[i][j]=dp[i][j-1]+dp[i-1][n-j];//粒子每穿过一个平面便会产生一个朝相反方向运动的粒子，此时它的能量级别为i-1，还需要穿过n-j个平面，同时原粒子仍然会向前运动 
				dp[i][j]%=mod;
			}
		}
		cout<<dp[k][n]<<'\n';
	}
	return 0;
}
```

## 0x04 注意

1. 要对 $10^9+7$ 取模。
2. 多测要清空。

---

## 作者：KevinHu0402 (赞：0)

[原题luogu传送门](https://www.luogu.com.cn/problem/CF1498C)

[原题CF传送门](https://codeforces.com/problemset/problem/1498/C)

这道题是一道比较简单的 dp 题。
~~（本蒟蒻只想到这一种思路，巨佬勿喷）~~

首先我们要推 dp 柿子，题目中给的图可以给我们思路。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1498C/df04d989fa23babd02f74b8b57d3f2d7886e9f14.png)

它展示出了一个能级为 $3$ 的粒子（也就是 D3）的轨迹，我们发现 D3 是由 D2 与 D1 所组成的，那我们很快就可以推出从左往右粒子的 dp 转移方程：
$$
dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1]
$$
同样地，我们也可以推出从右往左粒子的转移方程。

最后模数不要忘了，dp 数组清空也请不要忘了。

 AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 1005
#define m 1000000007
#define INF 0x3f3f3f3f
ll dp[maxn][maxn];
int main(){
	int T;
	cin >> T;
	while(T--){
		int n,k;
		cin >> n >> k;
		memset(dp,0,sizeof(dp));
		int reflect = 0;
		dp[1][1] = 1;
		for(int i = 1;i <= k;i++){
			if(i % 2 == 1){
				for(int j = 2;j <= n;j++){
					dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1];
				}
				reflect = (dp[i][n] + reflect) % m;
			}
			else{
				for(int j = n - 1;j >= 1;j--){
					dp[i][j] = (dp[i - 1][j + 1] + dp[i][j + 1]) % m;
				}
				reflect = (dp[i][1] + reflect) % m;
			}
		}
		if(k == 1){
			reflect = 0;
		}
		cout << reflect + 1 << endl;
	}
	return 0;
}
```

---

## 作者：Bpds1110 (赞：0)

看到范围，发现可以支持 $O(n^2)$ 的算法，想到 DP 求解。我们采用记忆化搜索实现，用 DP 实现可能很抽象。

定义状态 $rec(i, 0/1, j)$，表示当前粒子飞到 $j$ 且值为 $i$ 时的飞出范围粒子数，其中 $0/1$ 分别表示当前的方向，即 $0$ 为左，$1$ 为右。

考虑状态转移。对于每个粒子，特别地，如果值为 $1$，或已经越界，只能产生一个贡献。否则，都能产生 $2$ 种方案，分别为向不同的方向飞。当产生的时候，要注意更改方向和更改其对应的值。可以得出以下转移。

$$
rec(i, 0, j) = rec(i, 0, j - 1) + rec(i - 1, 1, j + 1)
$$
$$
rec(i, 1, j) = rec(i - 1, 0, j - 1) + rec(i, 1, j + 1)
$$

最后，用 $dp$ 数组实现记忆即可。
```cpp
#include <bits/stdc++.h>

const int mod = 1e9 + 7, N = 1e3 + 10;

int T, n, k, dp[N][2][N];

int rec(int val, int dir, int p)
{
	if (p < 1 || p > n || val == 1) return 1;
	if (dp[val][dir][p] ^ -1)
		return dp[val][dir][p];
	if (dir == 0) 
		return dp[val][dir][p] = (rec(val, 0, p - 1) 
		+ rec(val - 1, 1, p + 1)) % mod;
	if (dir == 1)
		return dp[val][dir][p] = (rec(val - 1, 0, p - 1)
		+ rec(val, 1, p + 1)) % mod;
}

int main()
{
 	std::ios::sync_with_stdio(false);
 	std::cin.tie(nullptr);
 	std::cout.tie(nullptr);

	std::cin >> T;
	while (T --> 0)
	{
		std::cin >> n >> k;
		for (int i = 1; i <= k; ++ i)
			for (int j = 1; j <= n; ++ j)
				dp[i][0][j] = dp[i][1][j] = -1;
		std::cout << rec(k, 1, 1) << "\n";
	}

	return 0;
}

```


---

## 作者：oimaster (赞：0)

记忆化搜索模板题。

考虑 `dfs` 函数的参数，我们应该记录下当前粒子在哪里，当前粒子的能量和当前粒子的方向。

接下来，很容易发现通过分粒子的方向来讨论，我们会得到两种情况：

1. 粒子在向右飞，此时我们这个粒子撞到一个平面后会产生两个粒子，第一个是保持此方向，然而换了坐标，第二个会把 $k-1$，方向变为左。那么这两种情况可以用这样的代码来表示：
- 继续向右飞，位置加一，其他不变，`dfs(cur+1,k,1)`。这里我们假设 `cur` 是当前位置，$1$ 为右 $0$ 为左。
- 反弹。位置减一，$k-1$，方向相反。`dfs(cur-1,k-1,0)`。
2. 粒子向左飞。我们的粒子会产生两个粒子，与上面几乎相同，唯一不同的是方向正好相反。
- 继续向左飞。位置减一，其他不变。`dfs(cur-1,k,0)`。
- 反弹，向右飞行。此时位置加一，$k-1$，方向向右。`dfs(cur+1,k-1,1)`。

于是重要的部分已经写完了，不过我们还要注意，$k$ 为 $1$ 的粒子是无法分裂的，于是我们就需要特判。细节还有很多，比如说当这是最后一块玻璃或这是第一块玻璃。

挂上代码：

```cpp
#include<iostream>
using namespace std;
#define int long long
int n,k;
int dp[1010][1010][2];
#define mod 1000000007
int dfs(int cur,int k,int dir){
	if(k==1)
		return 1;
	if(dp[cur][k][dir]!=-1)
		return dp[cur][k][dir];
	int ans=2;
	if(dir==1){
		if(cur<n)
			ans+=dfs(cur+1,k,1)-1;
		ans%=mod;
		if(cur>1)
			ans+=dfs(cur-1,k-1,0)-1;
	}
	else{
		if(cur>1)
			ans+=dfs(cur-1,k,0)-1;
		ans%=mod;
		if(cur<n)
			ans+=dfs(cur+1,k-1,1)-1;
	}
	ans%=mod;
	return dp[cur][k][dir]=ans;
}
void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=k;++j)
			dp[i][j][0]=dp[i][j][1]=-1;
	cout<<dfs(1,k,1)<<endl;
}
#undef int
int main(){
	int t;
	cin>>t;
	while(t--)
		solve();
}
```

---

