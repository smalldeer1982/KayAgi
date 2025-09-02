# Square-free division (hard version)

## 题目描述

This is the hard version of the problem. The only difference is that in this version $ 0 \leq k \leq 20 $ .

There is an array $ a_1, a_2, \ldots, a_n $ of $ n $ positive integers. You should divide it into a minimal number of continuous segments, such that in each segment there are no two numbers (on different positions), whose product is a perfect square.

Moreover, it is allowed to do at most $ k $ such operations before the division: choose a number in the array and change its value to any positive integer.

What is the minimum number of continuous segments you should use if you will make changes optimally?

## 说明/提示

In the first test case it is possible to change the array this way: $ [\underline{3}, 6, 2, 4, \underline{5}] $ (changed elements are underlined). After that the array does not need to be divided, so the answer is $ 1 $ .

In the second test case it is possible to change the array this way: $ [6, 2, \underline{3}, 8, 9, \underline{5}, 3, 6, \underline{10}, \underline{11}, 7] $ . After that such division is optimal:

- $ [6, 2, 3] $
- $ [8, 9, 5, 3, 6, 10, 11, 7] $

## 样例 #1

### 输入

```
3
5 2
18 6 2 4 1
11 4
6 2 2 8 9 1 3 6 3 9 7
1 0
1```

### 输出

```
1
2
1```

# 题解

## 作者：Fairicle (赞：13)

updated on 3.22 修了点小锅

****

看到 $k\leq 20$ 考虑 $O(nk^2)$ 或者 $O(nk)$ 的 DP。

显然转移是通过划分整段进行的，所以第一维应当是表示划分到 $i$，而第二维显然应该是记录当前改变数的个数 $j$，则 $f[i][j]$ 表示的就是划分到 $i$，当前改变过 $j$ 个数能够划分出的最小段数。

考虑怎么转移。一个很明显的思路就是枚举上次划分到 $k$，则从 $f[k][p]$ 转移到 $f[i][j]$，且如果假定把 $[k+1,i]$ 作为一个整段，**在这段中**需要改变的数为 $num$，则有 $p+num=j$。

所以可以考虑枚举上个划分点到 $i$ **消耗了多少次修改**，设 $l[i][x]$ 表示**最小**的 $pos$ 使得 $[pos,i]$ 作为一个整段时消耗了 $x$ 次修改，所以枚举不同的修改次数时，**对于一个修改次数只有一种转移（因为最远所以最优）**，这样大大简化了 DP 过程。

写出转移方程就是 $f[i][j]=\min(f[i][j],f[l[i][x]][j-x]+1)$

怎么求 $l$ 数组？很简单，在 $l[i][j]$ 中，对于一个确定的 $j$，当 $i$ 增时，$l[i][j]$ 必然单调不减，所以对于一个 $j$ 能双指针 $O(n)$ 求，所以预处理 $l$ 的复杂度是 $O(nk)$。

DP 的复杂度是 $O(nk^2)$，所以本做法复杂度是 $O(nk^2)$。

code：

```cpp
#define ll long long
#define ul unsigned long long
#define N 200010
#define K 21
int n,k,a[N],f[N][K],t,vis[10000010],lef[N][K];
int main()
{
	t=rd();
	while(t--){
        n=rd();k=rd();
        for(ri i=1;i<=n;++i){
            a[i]=rd();
            int tmp=a[i];a[i]=1;
            for(ri j=2;j*j<=tmp;++j){
                if(tmp%j==0){
                    int cnt=0;
                    while(tmp%j==0) tmp/=j,cnt++;
                    if(cnt&1) a[i]*=j;
                }
            }
            if(tmp>1) a[i]*=tmp;
        }
        for(ri lim=0;lim<=k;++lim){
            int cnt=0;
            for(ri i=1,j=1;i<=n;++i){
                vis[a[i]]++;
                if(vis[a[i]]>=2) cnt++;
                if(cnt>lim){
                    while(cnt>lim){
                        if(vis[a[j]]>=2) cnt--;
                        vis[a[j]]--;
                        j++;
                    }
                }
                lef[i][lim]=j;
            }
            for(ri i=1;i<=n;++i) vis[a[i]]=0;
        }
        for(ri i=0;i<=n;++i) for(ri j=0;j<=k;++j) f[i][j]=0x3f3f3f3f;
        f[0][0]=0;
        for(ri i=1;i<=n;++i)
        for(ri j=0;j<=k;++j)
        for(ri x=0;x<=j;++x) f[i][j]=min(f[i][j],f[lef[i][x]-1][j-x]+1);
        int ans=0x3f3f3f3f;
        for(ri i=0;i<=k;++i) ans=min(ans,f[n][i]);
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：zcz0263 (赞：7)

NOIP 模拟赛 T4 遇到这个题，赛时想出了这个 $O(V+T(n\log V+nk))$ 做法，应该是现在题解里面复杂度最优的了。

注：本文公式书写可能较乱。

首先考虑什么情况下两个数之积是完全平方数，发现当且仅当这两个数去掉所有非 1 的完全平方数因子后相等。

这里很多其他题解都是直接 $O(\sqrt V)$ 暴力分解，不过注意到只需要去除以质数为底的完全平方数即可，相当于分解质因子后给每个指数 $\bmod\ 2$。  
所以先用线性筛预处理每个数的最小质因子，然后将 $a_i$ 向下分解最小质因子，遇到奇数次的就留着，最后留下来数的积就是我们要比较的东西。  

然后可以将题意转化为：
> 修改数组中至多 $k$ 个位置，分割成最少的连续子段使得任意一个子段中没有相同的值，最小化段数。

设 $f_{i,j}$ 表示考虑前 $i$ 个数，修改了 $j$ 个数时最小分割次数；$g_{i_j}$ 表示考虑前 $i$ 个数，修改了 $j$ 个数时在分割次数为 $f_{i,j}$ 的情况下，上一段右端点的最大值。$pre_i$ 表示 $a$ 中上一个出现 $a_i$ 的位置。

为了方便转移，定义函数
$$F((f_1,g_1),(f_2,g_2))=\begin{cases}
  (f_1,g_1)\qquad  &f_1<f_2\vee(f_1=f_2\wedge g_1>g_2)\\
  (f_2,g_2) &otherwise.
\end{cases}$$


枚举所有 $i\leq n,j\leq k$：
- 如果 $pre_i\leq g_{i-1,j}$，表示当前这一段没有相同的，直接继续延长当前段，转移为
$(f_{i,j},g_{i,j})=F((f_{i,j},g_{i,j}),(f_{i-1,j},g_{i-1,j}))$。
- 否则，当前段出现了重复值，转移分两种情况：   
从 $i-1$ 处截断：   
$$(f_{i,j},g_{i,j})=F((f_{i,j},g_{i,j}),(f_{i-1,j}+1,i-1))$$   
修改当前位置：   
$$(f_{i,j+1},g_{i,j+1})=F((f_{i,j+1},g_{i,j+1}),(f_{i-1,j},g_{i-1,j}))$$
  - 考虑以上转移的正确性：当修改一个位置后，并不会影响后续转移方式的判断；因为每一段中的每一种数一定会留下一个，判断 $pre$ 时和前一段结尾的大小关系不会变化。  

初始状态 $f_{0,0}=g_{0,0}=0$，$f_{i,j}=g_{i,j}=inf$。



总复杂度 $O(V+T(n\log V+nk))$，踩了标算。

以下代码中 $dp$ 二元组数组的中第一个即为 $f$，第二个为 $g$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf INT_MAX
#define vi vector<int>
#define pii pair<int,int>
#define vpii vector<pii>
#define vvpii vector<vpii>
#define mkp make_pair
#define eb emplace_back
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define fi first
#define se second
void solve();
#define N 200005
#define X 10000007
vi p;
bitset<X+2> vis;
vi mind(X+2),mp(X+2);
void sieve(){
    rep(i,2,X){
        if(!vis[i]) p.eb(i),mind[i]=i;
        for(int&j:p){
            if(i*j>X) break;
            vis[i*j]=1;
            mind[i*j]=j;
            if(!(i%j)) break;
        }
    }
}
main(){
    ios::sync_with_stdio(0),cin.tie(nullptr);
    int _;
    sieve();
    for(cin>>_;_--;solve());
}
void solve(){
    int n,k;
    cin>>n>>k;
    vi a(n+2),aa(n+2,1);
    rep(i,1,n) cin>>a[i];
    rep(i,1,n){
		for(;1^a[i];){
            int t=mind[a[i]];
            a[i]/=t;
            if(a[i]%t==0){
                a[i]/=t;
            }else{
                aa[i]*=t;
            }
        }
    }
    vvpii dp(n+2,vpii(k+2,mkp(inf,inf)));
    dp[0][0]={0,0};
    a=aa;
    vi pre(n+2);
    rep(i,1,n){
        pre[i]=mp[a[i]];
        mp[a[i]]=i;
    }
    const auto mn=[&](pii x,pii y)->pii{
        if(x.fi^y.fi) return x.fi<y.fi?x:y;
        return x.se>y.se?x:y;
    };
    rep(i,1,n){
        rep(j,0,k){
            if(pre[i]<=dp[i-1][j].se) dp[i][j]=mn(dp[i][j],dp[i-1][j]);
            else{
                auto t=dp[i-1][j];
                t.fi++;
                t.se=i-1;
                dp[i][j]=mn(dp[i][j],t);
                dp[i][j+1]=mn(dp[i][j+1],dp[i-1][j]);
            }
        }
    }
    int ans=inf;
    rep(i,0,k){
        ans=min(ans,dp[n][i].fi+1);
    }
    cout<<ans<<"\n";
	rep(i,1,n) mp[a[i]]=0;
}
```

---

## 作者：L01001101 (赞：6)

[$\color{9D3DCF}\text{CF1497E2 Square-free division (hard version)}$](https://www.luogu.com.cn/problem/CF1497E2)

[$\color{000000}\text{1497 E2. Square-Free Division (hard version)}$](https://codeforces.com/problemset/problem/1497/E2)

首先发现题目中要求使得两个数之积都不是完全平方数，那么我们可以先预处理 $a_i$，将 $a_i$ 中的构成平方的因子先除掉（即将 $a_i$ 中次数大于 $1$ 的质因子的次数 $\bmod\ 2$），显然去除每个数的平方因子后，两个数相乘为完全平方数当且仅当它们相等。

看到 $n\leq 2\times 10^5,k\leq 20$，自然想到 $O(nk)$ 或 $O(nk^2)$ 的 DP。

设 $f_{i,j}$ 表示前 $i$ 个数中修改 $j$ 个划分的最小段数，$g(i,j)$ 表示表示以 $i$ 为**终点**，在 $i$ 所在的划分段内修改了 $j$ 次往回最远能扩充到的点。

则有

$$
f_{i,j}=\min^j_{x=0}\{f_{g(i,x)-1,j-x}+1\}
$$

时间复杂度 $O(nk^2)$。

那么如何求 $g$ 呢？

我们发现在 $g(i,j)$ 中，对于一个确定的 $j$，当 $i$ 增大时，$g(i,j)$ 必然单调不减，所以对于一个 $j$，我们能够用双指针 $O(n)$ 求出。

具体实现为开一个桶记录 $a_i$ 出现的次数，用双指针维护一个满足修改次数小于等于 $j$ 的区间，即可求出 $g(i,j)$，时间复杂度 $O(nk)$。

总时间复杂度是 $O(nk^2)$，可以通过本题。

---

**后记：**

在本题中，尽量不要使用 `memset` 函数给数组进行赋初值~~（都是血泪教训）~~。

`memset` 函数的时间复杂度为 $O(n)$，其中 $n$ 为数组的字节大小，具体可以看[这篇文章](https://blog.csdn.net/wengjianhong2099/article/details/132046118)。

本题可以通过构造数据使得 `memset` 函数 TLE。

[TLE on #15](https://codeforces.com/contest/1497/submission/236464915)。

---

```cpp
#include<cstdio>
#include<cstring>
const int N=2e5+10,K=25,S=1e7+10;
const int inf=0x3f3f3f3f;
int T,n,k;
int ans;
int a[N];
int num[S];
int f[N][K],g[N][K];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')ch=='-'?f=0:0,ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?x:-x;
}
inline int min(int a,int b){return a<b?a:b;}
int main(){
	T=read();
	while(T--){
		n=read(),k=read(),ans=inf;
		for(int i=1;i<=n;++i){
			a[i]=read();
			for(int j=2;j*j<=a[i];++j)while(a[i]%(j*j)==0)
				a[i]/=j*j;
		}
		for(int i=0;i<=k;++i){
			for(int j=1;j<=n;++j)num[a[j]]=0;
			for(int l=1,r=1,t=0;r<=n;++r){
				++num[a[r]],t+=(num[a[r]]>1);
				while(t>i&&l<r)
					t-=(num[a[l]]>1),--num[a[l]],++l;
				g[r][i]=l;
			}
		}
		for(int i=1;i<=n;++i)for(int j=0;j<=k;++j){
			f[i][j]=inf;
			for(int x=0;x<=j;++x)
				f[i][j]=min(f[i][j],f[g[i][x]-1][j-x]+1);
		}
		for(int i=0;i<=k;++i)
			ans=min(ans,f[n][i]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Creeper_l (赞：3)

题意：给定一个长度为 $n$ 的序列，求最少能将这个序列分成多少段使得任意一段中不存在两个数的积为完全平方数。你还可以将其中 $k(k \le 20)$ 个数修改为任意的值。

一个小 Trick：如果两个数乘起来为平方数，可以先将每个数的平方因子除掉，然后这两个数必然相等。于是可以先将每个 $a_{i}$ 的平方因子除掉，然后这道题被转化为了一个区间不能有相等的值。

首先考虑没有修改的情况怎么做，设 $pos_{a_{i}}$ 表示上一个 $a_{i}$ 出现在哪里（也就是最远可以满足条件的位置），那么有 dp 转移方程 $dp_{i}=dp_{pos_{a_{i}}}+1$，时间复杂度 $O(n)$。

然后考虑有修改操作的情况，我们可以稍微改变一下 $pos$ 数组的定义，改为 $pos_{i,j}$ 表示当前点为 $i$，修改 $j$ 次后可以到达的最远的满足条件的位置。那么怎么转移呢？$pos_{i,j}=\min(pos_{i-1,j-1},last+1)$，$last$ 表示上一个 $a_{i}$ 出现的位置。因为 $pos_{i-1,j-1}$ 和 $last+1$ 这两个位置都有可能是修改次数的分界点，看哪个更小即可。然后就可以用 $pos$ 数组来 dp 转移了：$dp_{i,j}=dp_{pos_{i,k},j-k}+1$。最终的答案就是 $dp_{n,k}$，时间复杂度 $O(nk^{2})$。

注意分解质因数的时候可以先将质数线性筛出来，这样效率更高。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
const int MAXN = 2e5 + 10,MAXM = 25;
int T,n,k,dp[MAXN][MAXM],a[MAXN],prime[MAXN],cnt,b[MAXN];
int pos[MAXN],last,p[MAXN];
bool is_prime[MAXN];
inline void Get_prime(int n)
{
	memset(is_prime,1,sizeof is_prime);
	is_prime[1] = 0;
	for(re int i = 2;i <= n;i = -~i)
	{
		if(is_prime[i] == 1) prime[++cnt] = i;
		for(re int j = 1;j <= cnt && i * prime[j] <= n;j = -~j)
		{
			is_prime[i * prime[j]] = 0;
			if(i % prime[j] == 0) break;
		}
	}
}
signed main()
{
	cin >> T;
	Get_prime(10000);
	while(T--)
	{
		cin >> n >> k;
		for(re int i = 1;i <= n;i = -~i) cin >> a[i];
		for(re int i = 1;i <= n;i = -~i)
		{
			for(re int j = 1;j <= cnt;j = -~j)
			{
				re int val = prime[j];
				while(a[i] % (val * val) == 0) a[i] /= (val * val);
				if(prime[j] * prime[j] > a[i]) break;
			}
			b[i] = a[i];
		}
		sort(b + 1,b + n + 1);
		int q = unique(b + 1,b + n + 1) - b - 1;
		for(re int i = 1;i <= n;i = -~i) a[i] = lower_bound(b + 1,b + q + 1,a[i]) - b,pos[a[i]] = 0;
		for(re int i = 0;i <= k;i = -~i) p[i] = 1,dp[0][i] = 0;
		for(re int i = 1;i <= n;i = -~i)
		{
			re int last = pos[a[i]];
			for(re int j = k;j >= 0;j--)
			{
				if(p[j] > last) continue;
				if(j == 0) p[j] = last + 1;
				else p[j] = min(last + 1,p[j - 1]);
			}
			for(re int j = 0;j <= k;j = -~j)
			{
				dp[i][j] = 1e18;
				for(re int k = 0;k <= j;k++) dp[i][j] = min(dp[i][j],dp[p[k] - 1][j - k]);
				dp[i][j] = dp[i][j] + 1; 
			} 
			pos[a[i]] = i;
		}
		cout << dp[n][k] << endl;
	}
	return 0;
}
```


---

## 作者：ran_qwq (赞：2)

## easy version

先考虑什么情况两个数乘积为完全平方数。

显然，乘积所有质因子次数为偶数时为完全平方数。

将所有 $a_i$ 的平方因子去掉，不影响质因子个数的奇偶性。

设此时两个数的某个质因子次数分别为 $x,y$，显然 $x,y\in[0,1]$。

当 $x\ne y$ 时，$x+y=1$，乘积不为完全平方数。

所以两个数所有质因子次数相等，即两个数相等。

这样，就转化为：

> 划分为最少的段，使得每段 $a_i$ **互不相同**。

贪心做就行。

## hard version

注意 $k\le20$，这提示着可能是 $O(nk)$ / $O(nk^2)$ 的 DP。

定义 $dp_{i,j}$ 为前 $i$ 个数，修改 $j$ 个数的**最小段数**。

常规思路是枚举当前段起始点，但是会 TLE。

考虑枚举之前的修改个数 $k$，则当前段修改 $j-k$ 个数。

也就是当前段**长度减去种数**为 $j-k$。

找出长度减去种数小于 $j-k$ 的左端点 $l$，则 $dp_{i,j}=\min(dp_{l-1,k}+1)$。

$l$ 可以双指针维护。

---

## 作者：EuphoricStar (赞：1)

感觉和 [CF1889C2 Doremy's Drying Plan (Hard Version)](https://www.luogu.com.cn/problem/CF1889C2) 有异曲同工之妙。

显然去除每个数的平方因子后，两个数相乘为完全平方数当且仅当它们相等。

考虑若确定了分段方案，那么修改次数就是，每一段重复出现的数的个数。

那么我们设 $f_{i, j}$ 为 $[1, i]$ 修改了 $j$ 次的最小分段次数。然后我们枚举上一个分段点 $k$，那么有 $f_{i, j} \gets f_{k, j - g(k + 1, i)} + 1$，其中 $g(l, r)$ 为 $[l, r]$ 中重复出现的数的个数。

显然对于一个 $j$，$f_{\ast, j}$ 单调不降，那么我们可以找到 $\forall p \in [0, m]$，使得 $g(k + 1, i) = p$ 的 $k$ 的最小值，然后直接从这个 $k$ 转移过来。

时间复杂度就是 $O(nk^2)$。去除平方因子我写了 $O(n \sqrt{V})$，也能过。

[code](https://codeforces.com/problemset/submission/1497/235985891)

---

## 作者：naroto2022 (赞：1)

# CF1497E2题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1497E2)

### 思路

看到 $n\leqslant2\times10^5,k\leqslant20$，自然想到 $O(nk)$ 或 $O(nk^2)$ 的 DP。

设 $f[i][j]$ 表示前 $i$ 个数中修改 $j$ 个划分的最小段数，$g[i][j]$ 表示表示以 $i$ 为终点，在 $i$ 所在段内修改了 $j$ 次向左最远能扩充到的点。

则有 $f[i][j]=\min(f[g[i][x]-1,j-x]+1)$，那么如何求 $g$ 呢？

我们发现在 $g[i][j]$ 中，对于一个确定的 $j$，当 $i$ 增加时，$g[i][j]$ 必然单调不减，所以对于一个 $j$ 能双指针 $O(n)$ 求，所以预处理 $g$ 的复杂度是 $O(nk)$。

DP 的复杂度是 $O(nk^2)$，故我们使用 $O(nk^2)$ 的复杂度通过本题。

### 后记

1. 在本题中，尽量不要使用 memset 函数给数组进行赋值。memset 函数的时间复杂度为 $O(n)$，其中 $n$ 为数组的字节大小。本题可以通过构造数据使得 memset 函数 TLE。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=2e5+10,K=25,S=1e7+10,INNF=0x3f3f3f3f;
int T,n,k,ans,a[N],num[S],f[N][K],g[N][K];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
} 
int main(){
	T=read();
	while(T--){
		n=read();k=read();ans=INNF;
		for(int i=1; i<=n; i++){
			a[i]=read();
			for(int j=2; j*j<=a[i]; j++) 
				while(a[i]%(j*j)==0)
					a[i]/=j*j;
		}
		for(int i=0; i<=k; i++){
			for(int j=1; j<=n; j++) num[a[j]]=0;
			for(int l=1,r=1,t=0; r<=n; r++){
				num[a[r]]++;
				t+=(num[a[r]]>1);
				while(t>i&&l<r){
					t-=(num[a[l]]>1);
					num[a[l]]--;
					l++;
				}
				g[r][i]=l;
			}
		}
		for(int i=1; i<=n; i++)
			for(int j=0; j<=k; j++){
				f[i][j]=INNF;
				for(int x=0; x<=j; x++)
					f[i][j]=min(f[i][j],f[g[i][x]-1][j-x]+1);
		}
		for(int i=0; i<=k; i++) ans=min(ans,f[n][i]);
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：冷却心 (赞：0)

给一个大常数垃圾做法。

我们先把原序列的每个数质因子分解之后对指数是奇数的质因子保留一个，这样得到新序列 $\{a'_n\}$，有性质满足当 $a'_i=a'_j$ 时 $a_i \cdot a_j$ 是完全平方数。这个时候我们的限制就是要求每一段的 $a'_i$ 都互不相同。也就是说把一段数修正为合法的花费次数是每种数都只保留一个，即总数减去种类数。我们记 $l_i$ 表示上一个恰好等于 $a'_i$  的位置。

考虑 dp。设状态 $f_{i,j}$ 表示把前 $i$ 个数分段，更改了 $j$ 个位置，最小划分段数。转移考虑以 $i$ 结尾的区间的左端点。如果我们把 $j \in [1,i]$ 里所有的 $l_j$ 都标记为 $1$，那么把 $[p,i]$ 划分为一段的代价就是区间 $[p,i]$ 的和。显然这个区间和不能超过 $k$，不然没有状态可供转移。那么我们只需要枚举最后 $k$ 个 $1$，设当前枚举的 $1$ 的位置在 $p$，它后继的 $1$ 在 $q$，且 $p$ 是倒数 $w$ 个 $1$。那么有转移：

$$
f_{i,j+w-1} \gets \min_{p \le a < q} f_{a,j} + 1.
$$

这样的转移每次 $O(k)$，枚举 $k$ 个位置转移，取 $\min$ 开 $k$ 棵线段树维护，时间复杂度 $O(k^2\log n)$，枚举 $1$ 的位置可以用链表或者 `set`。总时间复杂度 $O(nk^2\log n)$，倒闭。但是我们注意到这个每次插入 $l_i$ 为 $1$ 的时候，对于 $1$ 之间的先后关系改变只有 $O(1)$ 个，也就是说这个取 $\min$ 很多位置的结果不变，只会改变 $l_i$ 的前驱和其自身。所以我们提前保存取 $\min$ 的结果即可，这样转移复杂度 $O(k^2)$，每次插入 $l_i$ 的复杂度 $O(k \log n)$，总复杂度 $O(nk^2+nk\log n)$。线段树不要写的太劣就可以轻松跑过。

[Accepted submission.](https://codeforces.com/problemset/submission/1497/320313279)

---

## 作者：small_john (赞：0)

## 思路

神仙 DP 题。

首先简化题面，因为要求不能出现平方数，我们就把每个数的平方因子去掉。这样不出现平方数就被转换为了不出现相同的数。这部分可以 $O(n\sqrt{V})$ 做，其中 $V$ 是值域。

注意到 $k$ 的范围十分小，考虑一些 $O(nk^2)$ 的做法。

设 $f_{i.j}$ 表示前 $i$ 个数分成 $j$ 段的方案数。那么有转移：$\displaystyle f_{i,j}=\min_{k=0}^{j}f_{g_{i,k}-1,j-k}+1$，其中 $g_{i,k}$ 表示前 $i$ 个数操作 $k$ 次，$i$ 所在的段的最小左端点。

如何求出 $g$ 呢？容易发现 $g_{i,j}\ge g_{i,j+1}$ 并且 $g_{i,j}\le g_{i+1,j}$。既然有这么强的性质那就用双指针吧。

用第一种来维护是不好做的，因为需要枚举每个 $i$ 再去双指针，然后就成 $O(n^2)$ 的。

所以考虑第二种。记一个 $p$ 表示现在的左端点，而右端点从 $i$ 移到 $i+1$ 时先考虑上 $i+1$ 对次数的贡献，当现在总次数大于枚举的 $j$ 时往右移左端点即可。

时间复杂度 $O(nk^2+n\sqrt V)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 2e5+5,M = 25,V = 1e7+5;
int n,k,a[N],f[N][M],g[N][M],ton[V];
inline void solve()
{
	read(n),read(k);
	for(int i = 1,x;i<=n;i++)
	{
		read(x);
		a[i] = 1;
		for(int j = 2;j*j<=x;j++)
			if(x%j==0)
			{
				bool fl = 0;
				while(x%j==0) x/=j,fl^=1;
				if(fl) a[i]*=j;
			}
		if(x>1) a[i]*=x; 
	}
	for(int j = 0;j<=k;j++)
	{
		for(int i = 1;i<=n;i++) ton[a[i]] = 0;
		int now = 0;
		for(int i = 1,p = 1;i<=n;i++)
		{
			now+=(ton[a[i]]>0),ton[a[i]]++;
			while(now>j&&p<i) ton[a[p]]--,now-=(ton[a[p]]>0),p++;
			g[i][j] = p;
		}
	}
	for(int i = 1;i<=n;i++)
		for(int j = 0;f[i][j] = 2e9,j<=k;j++)
			for(int k = 0;k<=j;k++)
				f[i][j] = min(f[i][j],f[g[i][k]-1][j-k]+1);
	int ans = 2e9;
	for(int i = 0;i<=k;i++)
		ans = min(ans,f[n][i]);
	writen(ans); 
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int T;read(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：lsj2009 (赞：0)

### Solution

dp 好题。

容易发现当一个端点被确定时，另一个端点和修改次数是单调的。我们考虑设一个 $g_{i,j}$ 表示以 $i$ 为右端点，最多修改 $j$ 次，左端点最远能到哪里。

我们考虑统计一下 $a_i$ 有哪些因子是出现奇数次的，即记 $a_i=\prod\limits_{j=1}^m p_j^{c_j}$ 那么 $b_i=\prod\limits_{j=1}^m p_j^{c_j\bmod{2}}$。

现在我们考虑固定修改次数，显然当一个端点移动时，另一个端点必然不会回退，所以说直接双指针即可。每次扫到一个之前没有出现过的 $b_i$，则需要修改的次数应当加一，因为前面已经被我们修改成符合要求了，我们只需要修改这一个数就能使其再符合要求。

这样子我们就 $\Theta(nk)$ 求出了 $g$。

然后我们设 $f_{i,j}$ 为前 $i$ 个数最多修 $j$ 次，最少分几段，易得的是：

$$f_{i,j}=\min\limits_{k=0}^j f_{g_{i,k}-1,j-k}+1$$

然后就做完了，复杂度 $\Theta(nk)$。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=2e5+5,M=25,V=1e7+5;
int f[N][M],last[N][M],cnt[V],a[N];
int calc(int x) {
    int m=sqrt(x)+0.5,res=1;
    rep(i,2,m) {
        int cnt=0;
        while(x%i==0)
            x/=i,++cnt;
        if(cnt&1)
            res*=i;
    }
    if(x!=1)
        res*=x;
    return res;
}
signed main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int n,m;
        scanf("%d%d",&n,&m);
        rep(i,1,n) {
            int x;
            scanf("%d",&x);
            a[i]=calc(x);
        }
        rep(j,0,m) {
            int p=1,res=0;
            rep(i,1,n) {
                if(cnt[a[i]])
                    ++res;
                ++cnt[a[i]];
                while(res>j) {
                    --cnt[a[p]];
                    if(cnt[a[p]])
                        --res;
					++p;
                }
				last[i][j]=p;
            }
			rep(i,1,n)
				cnt[a[i]]=0;
        }
        rep(i,0,n) {
            rep(j,0,m)
                f[i][j]=INF;
        }
        f[0][0]=0;
        rep(i,1,n) {
            rep(j,0,m) {
                rep(k,0,j)
                    chkmin(f[i][j],f[last[i][k]-1][j-k]+1);
            }
        }
        int ans=INF;
        rep(i,0,m)
            chkmin(ans,f[n][i]);
        printf("%d\n",ans);
    }
    return 0;
}

```

---

## 作者：UperFicial (赞：0)

考虑 dp，设 $f_{i,j}$ 表示考虑了前 $i$ 个数，修改了 $j$ 个分割的最小数量的子段。枚举上一个子段的结尾 $k$，并设 $val(i,j)$ 表示 $[i,j]$ 这一段最少修改多少个数使得其变成合法子段，那么一个 $O(n^2)$ 的 dp 式子就出来了，$f_{i,j}\leftarrow \min\{f_{k,j-val(k+1,i)}+1\}$。

注意到 $k\le 20$，所以可以枚举 $val(k+1,i)$ 的取值 $m$，我们只需要找到一个下标 $k$ 使得 $f_{k,j-m}$ 最小，不妨设 $g_{i,j}$ 表示一个最长的后缀 $[g_{i,j},i]$ 使得修改恰好 $j$ 个数能成为合法子串。那么 $k$ 这个决策点的取值应为 $g_{i,m}$。

为什么 $k$ 取最小就是最优呢，注意到 $f$ 是单调不降的，所以越往左的 $k$ 对应的 dp 值就越小。

$g_{i,j}$ 的求法考虑双指针，即 $j$ 固定的情况，$g_{i,j}$ 是随着 $i$ 的增加而增加的。我们把每个 $a_i$ 的平方因子扔掉，那么两个数乘积为完全平方数这一条件就可以化成两个数是否相等。

复杂度 $O(nk^2)$。

```cpp
const int MAXN(2e5+10);
const int MAXM(30);
const int MAXV(1e7+10);

int T;

int n,k,a[MAXN];
int g[MAXN][MAXM],f[MAXN][MAXM];
int vis[MAXV];

inline void solve()
{
    n=read(),k=read();
    rep(i,1,n)
    {
    	a[i]=read();
    	for(register int j=2;j*j<=a[i];++j) if(a[i]%j==0)
    	{
    		int cnt(0);
    		while(a[i]%j==0) a[i]/=j,++cnt;
    		if(cnt&1) a[i]*=j;
    	}
    }
    rep(j,0,k)
    {
    	int used=0,lst=1;
    	rep(i,1,n)
    	{
    		++vis[a[i]];
    		if(vis[a[i]]>=2) ++used;
    		while(used>j)
    		{
    			if(vis[a[lst]]>=2) --used;
    			--vis[a[lst]],++lst;
    		}
    		g[i][j]=lst;
    	}
    	rep(i,1,n) vis[a[i]]=0;
    }
    rep(i,1,n) rep(j,0,k) f[i][j]=INF;
    f[0][0]=0;
    rep(i,1,n) rep(j,0,k) rep(m,0,j) f[i][j]=Min(f[i][j],f[g[i][m]-1][j-m]+1);
    printf("%d\n",f[n][k]);
    return;
}

int main()
{
	T=read();
	while(T--) solve();
	return 0;
}
/*
Date : 2022/11/1
Author : UperFicial
Start coding at : 15:46
finish debugging at : 16:14
*/
```

---

## 作者：intel_core (赞：0)

回顾一下 $\text{E1}$ 的双指针做法，本质就是在新增左端点固定的情况下，尽可能往右拉右端点。

现在我们可以更改 $k$ 个数；因为 $10^7$ 以内的质数明显超过了 $2\times 10^5$ 个，所以我们更改完之后可以使改过的数不和任何数的乘积是平方数。

记 $f[i][j]$ 为当前最后一个区间的右端点为 $i$，用了 $j$ 次更改时区间数的最小值。

由于 $k \le 20$，所以枚举当前区间内用了多少次修改；这时候发现需要预处理出 $i$ 为右端点，修改 $j$ 次时左端点最左在哪里。

可以把所有数扫一遍，把平方因子扔掉，然后 $O(nk)$ 双指针求出上述信息。

最后就是一个 $O(nk^2)$ 的 $\text{DP}$。

---

