# Uniformly Branched Trees

## 题目描述

A tree is a connected graph without cycles.

Two trees, consisting of $ n $ vertices each, are called isomorphic if there exists a permutation $ p:{1,...,n}→{1,...,n} $ such that the edge $ (u,v) $ is present in the first tree if and only if the edge $ (p_{u},p_{v}) $ is present in the second tree.

Vertex of the tree is called internal if its degree is greater than or equal to two.

Count the number of different non-isomorphic trees, consisting of $ n $ vertices, such that the degree of each internal vertex is exactly $ d $ . Print the answer over the given prime modulo $ mod $ .

## 样例 #1

### 输入

```
5 2 433416647
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 3 409693891
```

### 输出

```
2
```

## 样例 #3

### 输入

```
65 4 177545087
```

### 输出

```
910726
```

# 题解

## 作者：one_cell (赞：9)

# 题意
给定三个数$n,d,mod$。现在需要你求出，满足有$n$个节点，除了度数为$1$的节点，其它节点的度数都为$d$的不同构的树的数量。输出答案对$mod$取模的结果。
$$n\leq 1000, \;d\leq 10, \;10^8\leq mod \leq 10^9$$
# Solution
一般来说，计数类问题需要满足的条件是**不能重复，不能遗漏**。

所以我们首先要确定一棵树的根，否则这棵树可能会被重复算多次。
## 确定根节点
但是根节点并不能随便的挑选一个。这里我们挑选**重心**作为根节点。

原因就在于：重心在一棵树上是唯一的（当然有特殊情况是两个，这个我们后面会陈述），所以对于一棵树来说，它只会在以其重心为根时会被算一次，从而避免了算重复。

而重心还满足什么性质？我们知道，重心将整棵树分成的联通块中最大的那个不超过整棵树大小的一半。

而根据重心的这几条性质，我们就可以考虑进行DP。
## 考虑DP
状态设计：
首先，因为我们最终要得到一颗$n$个节点的树，所以第一维状态表示这棵树有$i$个节点。

其次，由于最终每个点的度数都为$d$，所以第二维状态表示根节点有$j$棵子树。

最后，由于我们要满足根节点是重心的条件，所以第三维状态表示根节点下面的子树大小都不超过$k$

综上所述。$f_{i,j,k}$表示$i$个节点，其中根节点有$j$棵子树，且子树大小都不超过$k$的树的数量。

状态转移：

由于树是不同构的，所以我们并不关心子树之间的相对顺序，所以我们DP的时候默认子树是从小到大排的。

因为子树大小都是不超过$k$的，而若子树大小都小于$k$，那么状态转移可得：$f_{i,j,k}=f_{i,j,k-1}$

否则说明有若干棵子树大小是等于$k$的，则我们枚举有$t$棵这样的子树，那么除去这$t$棵子树，剩下部分的状态即为$f_{i-t\times k,j-t,k-1}$。

而由于子树之间是可以相同的。

所以这$t$棵子树的方案数，实际就是从$f_{k,d-1,k-1}$这么多数量中选出$t$棵且**可以重复**的方案数，即为：$C(f_{k,d-1,k-1}+t-1,t)$

那么状态转移可得：$f_{i,j,k}=f_{i-t\times k,j-t,k-1} \times C(f_{k,d-1,k-1}+t-1,t)$
## 统计答案
直接输出$f_{n,d,\lfloor \frac{n}{2} \rfloor}$？那说明你太天真了~

注意：这里的DP是基于一棵树只有一个重心的情况。而对于那些有双重心的树，是会被会算两遍的，所以我们要将这种情况减去一遍。

那么我们来分析，什么时候会出现双重心的情况？

显然，只有可能是一条边连接的两个点分别挂着两颗**点数相同**的子树

而我们发现，这种情况一定有**偶数**个节点。

而对于这种情况的数量，如何求呢？

因为是两个节点分别挂着两颗点数相同的子树，而这样树的数量显然就是$f_{n/2,d-1,n/2-1}$

而此时方案数即为从$f_{n/2,d-1,n/2-1}$这么多数量选出**不重复**的两个，即为$C(f_{n/2,d-1,n/2-1},2)$

为什么这里必须是不重复？

因为按照我们DP的过程，两边子树相同这样的情况只会被我们算一遍。（因为儿子是可以交换的）

这个地方还需读者稍微理解一下。

综上所述：

当$n$为奇数时，$Ans = f_{n,d,\lfloor \frac{n}{2} \rfloor}$

当$n$为偶数时，$Ans = f_{n,d,\lfloor \frac{n}{2} \rfloor}-C(f_{n/2,d-1,n/2-1},2)$

那么整道题就做完了。

但有一些DP的边界条件还是要多多注意，细节都在代码里。

而且不要忘记要特判，当$n\leq 2$时直接输出$1$即可
## Code
    #include <bits/stdc++.h>
    const int N = 1010;
    int n, d, mod, f[N][20][N], fac[20], Inv[20];
    int ksm(int a, int b)
    {
        int ans = 1;
        while(b)
        {
            if(b & 1) ans = 1LL * ans * a % mod;
            a = 1LL * a * a % mod;
            b >>= 1;
        }
        return ans;
    }
    int C(int n, int m)
    {
        if(m > n) return 0;
        int ans = 1;
        for(int i=n-m+1;i<=n;i++) ans = 1LL * ans * i % mod;
        ans = 1LL * ans * Inv[m] % mod;
        return ans;
    }
    int main()
    {
        scanf("%d%d%d", &n, &d, &mod);
        if(n == 1 || n == 2)
        {
            puts("1");
            return 0;
        }
        fac[0] = Inv[0] = 1;
        for(int i=1;i<=d;i++) fac[i] = 1LL * fac[i - 1] * i % mod;
        Inv[d] = ksm(fac[d], mod - 2);
        for(int i=d-1;i>=1;i--) Inv[i] = 1LL * Inv[i + 1] * (i + 1) % mod;
        for(int i=0;i<=n;i++) f[1][0][i] = 1;
        for(int i=2;i<=n;i++)
        {
            for(int j=1;j<=std::min(d,i-1);j++)
            {
                for(int k=1;k<=n;k++)
                {
                    f[i][j][k] = f[i][j][k - 1];
                    for(int t=1;t<=j;t++)
                    {
                        if(i >= t * k && j >= t && k - 1 >= 0)
                        {
                            //printf("%d\n", C(f[k][d - 1][k - 1] + t - 1, t));
                            if(k > 1)
                            f[i][j][k] = (f[i][j][k] + 1LL * f[i - t * k][j - t][k - 1] * 
                            C(f[k][d - 1][k - 1] + t - 1, t) % mod) % mod;
                            else
                            {
                                f[i][j][k] = (f[i][j][k] + 1LL * f[i - t * k][j - t][k - 1] * 
                                C(f[k][0][k - 1] + t - 1, t) % mod) % mod;
                            }
                        }
                    }
                }
            }
        }
        int res;
        if(n & 1) 	
            res = f[n][d][n / 2];
        else
            res = (f[n][d][n / 2] - C(f[n / 2][d - 1][n / 2 - 1], 2) + mod) % mod;
        printf("%d", res);
        return 0; 
    } 

---

## 作者：ywy_c_asm (赞：6)

这题确实是一道计数好题。

首先让我们明确一下啥叫“不同构”，比如下面两个树是同构的：

![](https://cdn.luogu.com.cn/upload/pic/53103.png)

对于一棵**有根树**，如果我们能够通过交换每个点儿子的顺序是这两棵树一样，那就是同构的。

于是就会有这么个想法：我们只要保证每个点的儿子的大小都是从小到大的不就行了？

哦这显然不对因为这题让我们求的是无根树，其实无根树和有根树同构的差别就是无根树能够换根，这两棵无根树在某个根的意义下确实不同构，但是换个根就同构了。

所以我们应该找个方法使得他们不会随便换根，再转化成有根树的计数，因为有根树是能够dp的。

有了，我们可以让这个树的**重心**当根！重心不是唯一确定的吗？

哦对于$n$为奇数的情况下确实是这样，但是$n$为偶数的时候你发现重心在有些情况下会有两个，比如这个：

![](https://cdn.luogu.com.cn/upload/pic/53106.png)

但是这个时候这棵树被一条唯一确定的**中心边**分为了两个完全相等的部分，你这个时候不妨就以这个中心边为根，然后找出一半的方案设为$f$，显然不能交换这两棵子树的话答案就是$\frac {f(f+1)} 2$。

那么我们现在的问题就完全转化为了对有根树的计数，这个不难想到在dp状态里记这棵树的大小，根的度数，并且刚才说了要把儿子从小到大排，还要再记一个最大的儿子size是啥，或者为方便计数你可以把这个改成最大的儿子size不能超过啥。

然后我们这样dp一波发现WA了，因为这个里面存在一个严重的问题：**儿子的size可能是相同的！**

为啥这个会出问题呢？因为你这样把儿子排序之后size相同的儿子会构成连续的一段，但是他们内部的顺序就不好处理了，举个例子，假如根有两个儿子$i$和$j$，他们size相同，所以方案的选择集合是相同的，假如$i$选了方案$A$，$j$选了方案$B$，那么$i$选方案$B$，$j$选方案$A$这个就是同构的方案就不对了……

所以你必须枚举相同的儿子有多少个，那么现在的问题是，我有$m$个方案数都为$f$的size相同的儿子，求不同构的排列方案。

其实这个玩意你可以把这$f$个方案看做从1开始编号的有序的方案，我们假设把这些方案排成一列，那么我要把这些size相同的儿子按照他们取的方案的编号排序，这样就完全不会同构了。我们不妨用小球与盒子那套理论看这个问题，就是我现在有$f-1$个球，显然有$f$个空隙，我有$m$个板，显然有$m-1$个盒子，两个板可以插到同一个空隙里，求方案数（我把这些球和这些板都看作完全相同的，只是他们的排列有先后而已，所以我不管怎么插都可以把这些板板从左到右依次为第1个、第二个……第$m$个子树，这样插出来的方案一定是按顺序排的），这显然就是$C_{f+m-1}^m$了。

这里有个问题就是$f$是模p意义下的，但是$C_{f+m-1}^m=\frac{(f-1+m)!}{m!(f-1)!}=\frac 1{m!}\prod_{i=1}^m (f-1+i)$，显然后者那个积式在$f$取模的情况下再取模的结果还是一样的……这个东西可以$O(m)$递推出来。

于是我们就可以愉快的dp了！设$dp[i][j][k]$为$size=i$，最大的子树size**不超过**$j$，根的度数为$k$，转移如下：

$dp[i][j][k]=dp[i][j-1][k]+\sum_{m<=k\&\&mj<i}dp[i-mj][j-1][k-1]C_{dp[j][j][d-1]}$

这玩意用个记搜会好写的多，注意dp的时候特判$i=1$与$j=1$的情况，另外记得特判$n<=2$时直接输出1……不愧是cf题……

哦这个复杂度是$O(n^2d^2)$的但是他跑不满还挺快的……

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
namespace ywy {
	int p;
	unsigned char bv[1001][1001][11];
	ll f[1001][1001][11];
	int d;
	inline ll mi(int a, int b) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = (ans * tmp) % p;
	        tmp = (tmp * tmp) % p;
	        b >>= 1;
	    }
	    return (ans);
	}
	ll ny[1001];
	ll dp(int sz, int mx, int dk) {
	    if (bv[sz][mx][dk])
	        return (f[sz][mx][dk]);
	    bv[sz][mx][dk] = 1;
	    if (sz == 1) {
	        return (f[sz][mx][dk] = (dk == 0));
	    }
	    if (!dk || !mx || dk >= sz)
	        return (f[sz][mx][dk] = 0);
	    if (mx == 1) {
	        return (f[sz][mx][dk] = (sz == dk + 1));
	    }
	    ll ans = dp(sz, mx - 1, dk);
	    ll h = dp(mx, mx, d - 1);
	    if (!h)
	        return (f[sz][mx][dk] = ans);
	    ll ji = 1;
	    for (register int i = 1; i <= dk && i * mx < sz; i++) {
	        ji *= ny[i];
	        ji %= p;
	        ji *= (h + i - 1);
	        ji %= p;
	        ans = (ans + dp(sz - i * mx, mx - 1, dk - i) * ji) % p;
	    }
	    return (f[sz][mx][dk] = ans);
	}
	void ywymain() {
	    int n;
	    cin >> n >> d >> p;
	    for (register int i = 1; i <= d; i++) ny[i] = mi(i, p - 2);
	    if (n <= 2) {
	        cout << 1 << endl;
	        return;
	    }
	    if (n & 1) {
	        cout << dp(n, n / 2, d) << endl;
	        return;
	    }
	    ll cjr = dp(n / 2, n / 2 - 1, d - 1);
	    cjr = ((cjr + 1) * cjr) / 2;
	    cjr %= p;
	    cjr %= p;
	    cjr += dp(n, n / 2 - 1, d);
	    cjr %= p;
	    cout << cjr << endl;
	}
}
signed main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：AlanSP (赞：3)

非常 **有意思** 的计数。

从重心考虑，钦定一棵树的重心为根，进行计数 $dp$。

这样每棵子树的大小不超过 $\frac n 2$，并且方便去重。

由于要考虑不同构的情况，所以我们按子树的大小从小向大计算。

我们设 $f[i][j][k]$ 表示当前有 $i$ 个节点的树，根节点的度为 $j$，子树大小不超过 $k$ 的方案数。

那么显然有转移：$f[i][j][k]=f[i][j][k-1]$，不超过 $k-1$ 的一定不超过 $k$ 。

接下来我们就要考虑大小恰好为 $k$ 的子树了。

枚举我们选了 $t$ 棵大小为 $k$ 的子树，那么剩下的方案数就是 $f[i-tk][j-t][k-1]$，注意剩下的子树大小不能超过 $k-1$。

而这 $t$ 棵树有不同的形态，我们知道大小为 $k$，且合法的树的形态是 $f[k][d-1][k-1]$。 

除去根节点，子树总大小为 $k-1$，并且因为这棵树要作为子树，根节点的度有一条是连向 $father$ 的。所以有 $d-1$ 棵子树。

那么我们要从这么多种形态的树种选择 $t$ 棵，同时这些树的形态可以重复，这就是一个可重组合，方案数为
$$
\binom{f[k][d-1][k-1]+t-1}{t}
$$
在转移时还要乘上上面的组合数。

根据重心的定义，最终答案为 $f[n][d][n/2]$ 。

这样我们就处理完一个重心的问题了，但是还没有结束。因为当 $n$ 为偶数时，可能这棵树有两个重心。

其他题解里对为什么会算重讲得不是很详细，这里我细说一下。

我们在考虑 **树的同构** 的时候，将子树的大小从小到大考虑，但这样真的考虑了所有情况吗？我们来看下面的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/utb3fyzb.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/eb57ejor.png)

如上图，它们子树的大小的确是递增的，但是这两棵树却是同构的。

这是因为在两个重心分别当作根时，**它与那些大小小于 $\frac n 2$ 的子树共同成的树**形态是不同的，即去掉重心之间连边形成的两棵树形态不同。这样就会被重复计数。

统计这种情况，可以将两个重心的连边看成点，它连接着两棵大小为 $\frac n 2$ 的子树。

同上，大小为 $\frac n 2$ 的树形态有 $f[\frac n 2][d-1][\frac n2 -1]$ 种，我们要从这些形态里选出两种**不重复的**。

这样的方案数是：
$$
\binom{f[\frac n 2][d-1][\frac n2 -1]}{2}
$$
统计答案时减掉就好了。

注意特判 $n\leqslant2$ 的情况。

### Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1009;
int f[N][12][N/2],n,d,mod;
int inv[N],fac[N];

inline void Plus(int &x,int y){x=(x+y>=mod?x+y-mod:x+y);}
inline int mins(int &x,int y){return (x-y<0?x-y+mod:x-y);}

void Init()
{
	inv[1]=1;
	for(int i=2;i<N;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<N;i++) inv[i]=1ll*inv[i-1]*inv[i]%mod;
}

inline int C(int n,int m)
{
	if(m>n) return 0;
	int res=1;
	for(int i=n-m+1;i<=n;i++) res=1ll*res*i%mod;
	return 1ll*res*inv[m]%mod;
}

int main()
{
	scanf("%d%d%d",&n,&d,&mod);
	if(n<=2) return puts("1"),0;
	Init();
	for(int i=0;i<=n/2;i++) f[1][0][i]=1;
	f[1][d-1][0]=1;
	for(int i=2;i<=n;i++)
		for(int j=1;j<=min(d,i-1);j++)
			for(int k=1;k<=n/2;k++)
			{
				f[i][j][k]=f[i][j][k-1];
				for(int t=1;t*k<=i&&t<=j;t++)
					Plus(f[i][j][k],1ll*f[i-t*k][j-t][k-1]*C(f[k][d-1][k-1]+t-1,t)%mod);
			}
	if(n&1) printf("%d",f[n][d][n/2]);
	else printf("%d",mins(f[n][d][n/2],C(f[n/2][d-1][n/2-1],2)));
	return 0;
}
```



---

## 作者：Felix72 (赞：1)

由于无标号，直接设 $f_{i, j}$ 表示 $i$ 个点，根节点有 $j$ 棵子树的方案是无法考虑到子树之间的顺序的。还要加设一维 $k$ 表示最大子树的大小**不超过** $k$。

按照定义转移。当 $n$ 是奇数，可以令重心为无根树的根，答案是 $f_{n, d, \frac{n - 1}{2}}$；如果是偶数，还要减去两个重心重复计算的情况，即选两个**不同**的树拼起来，方案是 $f_{\frac{n}{2}, d - 1, \frac{n}{2} - 1} \choose 2$。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 1010, M = 15;
int n, m, mod; long long fac[N], inv[N], f[N][M][N];
inline void Plus(long long &now, long long add)
{now += add; while(now >= mod) now -= mod;}
inline long long qpow(long long a, long long b)
{
	long long res = 1;
	while(b) {if(b & 1) res = res * a % mod; b >>= 1, a = a * a % mod;}
	return res;
}
inline void init_math()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 1000; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[1000] = qpow(fac[1000], mod - 2);
	for(int i = 999; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}
inline long long C(int n, int m)
{
	if(n < m) return 0;
	long long res = 1;
	for(int i = n; i > n - m; --i) res = res * i % mod;
	res = res * inv[m] % mod; return res;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> mod; init_math();
	if(n <= 2) {cout << 1 << '\n'; return 0;}
	f[1][0][0] = 1;
	for(int num = 1; num <= n; ++num)
	{
		for(int cnt = 0; cnt <= m; ++cnt)
		{
			for(int lim = 1; lim <= n; ++lim)
			{
				Plus(f[num][cnt][lim], f[num][cnt][lim - 1]);
				for(int ex = 1; ex <= cnt; ++ex)
				{
					if(num - ex * lim < 0) break;
					Plus(f[num][cnt][lim], f[num - ex * lim][cnt - ex][lim - 1] * C((f[lim][m - 1][lim - 1] + f[lim][0][lim - 1]) % mod + ex - 1, ex) % mod);
				}
			}
		}
	}
	if(n % 2 == 1) cout << f[n][m][n / 2] << '\n';
	else cout << (f[n][m][n / 2] - C(f[n / 2][m - 1][n / 2 - 1], 2) + mod) % mod << '\n';
	return 0;
}
/*

*/
```

随便说说：我们老师一年前就布置了这道题，但是我一直没去动，直到现在才真正会这个题。想这一年来我疏于高强度的训练，老师布置的题目也少做了很多，或许联赛爆炸是咎由自取。

---

## 作者：A_Pikachu (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF724F)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf724f-uniformly-branched-trees)）

upd on 23/7/16：修正了错误的公式。

$\Large\mathscr{Part\,\,1\;\;}\text{基本思路}$

直接获取两棵树的信息时似乎无法判断它们是否同构，考虑确定每棵树的特性，发现树的重心既有唯一（唯二）性，又确保了子树的大小限制，利于判断，所以不妨令这棵有根树的根为重心，判断时按子树大小递增判断。

题意其实就是求不同构的有 $n$ 个节点的根节点有 $d$ 个儿子的 $d-1$ 叉树个数。按照我们计算时不算重的思想，转移需要用到三个维度：节点个数，根节点儿子个数，子树大小上限（利用重心）。

设 $f[i][j][k]$ 表示节点个数为 $i$，根节点儿子个数为 $j$，子树大小上限为 $k$ 时的方案数。

先考虑状态继承：$f[i][j][k]=f[i][j][k-1]$，因为当只有子树大小上限增加时原方案一定合法。

再考虑状态转移：在 $f[i][j][k-1]$ 中未被计算的方案只有存在子树大小恰为 $k$ 时的方案，由于可能存在多棵同大小子树，看到 $2 \leq d \leq 10$ 时果断选择枚举子树大小为 $k$ 的个数，设其为 $x$，则先有原来 $f[i-kx][j-x][k-1]$ 种缺少 $x$ 个子树大小为 $k$ 的方案，再知道大小为 $k$ 的树的形态有 $f[k][d-1][k-1]$ 种，且需要从其中选取 $x$ 种的不重复方案，易知（插板法）有 $\dbinom{f[k][d-1][k-1]+x-1}{x}$ 种方案，相加即可。

由重心的性质可知理论最终答案为 $f[n][d][\frac{n}{2}]$。

但此时问题又归到了根节点上。当节点数为偶数时，会出现两个重心，但因为此时有可能生成了大小恰为 $\frac{n}{2}$ 的子树，再以这棵子树的根为根节点时，会发现此时虽然两棵树是同构的，但却在转移中被算了两遍，故最终答案要减去多余部分，即在 $f[\frac{n}{2}][d-1][\frac{n}{2}-1]$ 种方案中任选两个不相同的，为 $\dbinom{f[\frac{n}{2}][d-1][\frac{n}{2}-1]}{2}$ 种。

当然，如果不可能存在度数为 $d$ 的节点时直接特判掉就好了。

$\Large\mathscr{Part\,\,2\;\;}\text{Code}$

```cpp
#include <cstdio>
const int N=1005,D=12;
int n,d,mod,f[N][D][N>>1],invp[D];
int min(int x,int y){return x<y?x:y;}
int C(int x,int y){ // C_x^y
	int now=x;
	for(int i=x-1; i>x-y; i--) now=1LL*now*i%mod;
	return 1LL*now*invp[y]%mod;
}
int qpow(int x,int y){
	int z=1;
	while(y){
		if(y&1) z=1LL*z*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return z;
}
int main(){
	scanf("%d%d%d",&n,&d,&mod);
	if(n<=2){
		puts("1");
		return 0;
	}
	invp[1]=1;
	for(int i=2; i<=d; i++) invp[i]=1LL*invp[i-1]*i;
	for(int i=2; i<=d; i++) invp[i]=qpow(invp[i],mod-2); // invp[i] 为 i! 的逆元
	for(int k=0; k<=n>>1; k++) f[1][0][k]=1;
	f[1][d-1][0]=1; // 初始化只有一个节点的情况
	for(int i=2; i<=n; i++){
		for(int j=1,ed=min(d,i-1); j<=ed; j++){
			for(int k=1; k<=n>>1; k++){
				f[i][j][k]=f[i][j][k-1];
				for(int x=1; x*k<=i&&x<=j; x++){
					f[i][j][k]=(f[i][j][k]+1LL*f[i-k*x][j-x][k-1]*C(f[k][d-1][k-1]+x-1,x)%mod)%mod;
				}
			}
		}
	}
	if(!(n&1)) f[n][d][n>>1]=(f[n][d][n>>1]-C(f[n>>1][d-1][n-2>>1],2)+mod)%mod;
	printf("%d\n",f[n][d][n>>1]);
	return 0;
}
```

时间复杂度看似 $\Theta(n^2d^3)$，但到第三层循环次数过大时内层循环就会减少，实际分析下来还是 $\Theta(n^2d^2)$ 的。

---

## 作者：lfxxx (赞：0)

非常牛啊。

当 $n>2$ 时，注意到只有叶子会是 $1$ 度点。所以先把 $n \leq 2$ 的特判掉。

划分无根树是困难的，但是划分有根树是简单的，不妨先当有根树做最后钦定根是重心。

考虑划分问题的方式是对于当前树将其的子树一个个剥掉，对于一棵树我们关注其大小，根的度数，而由于要计算不同构的树，我们需要钦定将所有子树按照子树大小加入，也就是我们还关心当前树的最大子树大小，于是设计状态 $f_{i,j,k}$ 表示大小为 $i$ 的树，子树大小不超过 $j$，根的度数为 $k$ 的方案。转移就是枚举从 $f_{i',j-1,k'} \to f_{i,j,k}$ 时有没有放以及放了多少个大小为 $j$ 的子树，假若放了 $l$ 个就要乘上 $f_{j,j-1,d-1} + l-1 \choose l$ 的转移系数（$l$ 个无标号球放入 $f_{j,j-1,d-1}$ 个有标号盒子，可以不放，插板即可得到系数），由于 $l$ 很小可以暴力组合数，这一步是 $O(n^2 \times d^2)$ 的。这里注意特判一下放入一个叶子以及将子树剥掉之后只剩下一个孤点（剥完了）的情况。

假若 $n$ 是奇数答案就是 $f_{n,\frac{n}{2},d}$，但是假若 $n$ 是偶数会有两个重心，怎么办？

注意到两个重心一定形如 $u,v$ 而 $u,v$ 是原树一条边，当割去边 $u,v$ 后，假若两个连通块不同构则以两个重心作为根的树不同构，否则同构，所以减去 $f_{\frac{n}{2},\frac{n}{2},d-1}$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int mod;
const int maxn = 1e3+114;
int fac[maxn],inv[maxn];
int qpow(int a,int b){
	if(b==0) return 1;
	if(b==1) return a;
	int res=qpow(a,b/2);
	res=res*res%mod;
	if(b%2==1) res=res*a%mod;
	return res;
}
int dp[maxn][maxn][11];//dp[i][j][d] 大小为 i 的子树/子树大小不超过 j 根度数为 d
//n>2 时只有叶子会是一度点
int C(int n,int m){
	if(n<m) return 0;
	int res=1;
	for(int i=n;i>n-m;i--) res=res*(i%mod)%mod;
	res=res*inv[m]%mod;
	return res; 
}
int n,d;
signed main(){
	cin>>n>>d>>mod;
	if(n<=2){
		cout<<1<<'\n';
		return 0;
	}
	fac[0]=inv[0]=1;
	for(int i=1;i<maxn;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
	dp[1][0][d-1]=1;
	for(int i=2;i<=n;i++){
		for(int k=1;k<i;k++){
			for(int lst=1;lst<=d;lst++) dp[i][k][lst]=dp[i][k-1][lst];
			for(int l=1;l<=d&&k*l<i;l++){
				int ch=C(dp[k][k-1][d-1]+l-1,l);
				for(int D=l+1;D<=d;D++){
					dp[i][k][D]=(dp[i][k][D]+dp[i-k*l][k-1][D-l]*ch%mod)%mod;
				}
				if(i==k*l+1) dp[i][k][l]=(dp[i][k][l]+ch)%mod;
			}
		}
		for(int k=i;k<=n;k++){
			for(int lst=1;lst<=d;lst++) dp[i][k][lst]=dp[i][k-1][lst];
		}
	}
	if(n%2==1) cout<<dp[n][n/2][d]<<'\n';
	else cout<<(dp[n][n/2][d]+mod-C(dp[n/2][n/2][d-1],2))%mod;
	return 0;
}
 
```

---

## 作者：daniEl_lElE (赞：0)

容易发现在题目限制下树中度数为 $1$ 和 $d$ 的点的个数是唯一确定的。

判掉不可能的情况，容易发现度数为 $1$ 的点没有意义，不会影响树的形态。

于是问题转化成度数小于等于 $d$ 的无标号无根树个数。

考虑 $dp_{i,j}$ 表示子树有 $i$ 个点，根度数为 $j$ 的树的数量。

考虑转移，枚举某个其他的子树有多少个子树大小为 $k$ 的儿子，算出从所有子树大小为 $k$ 的子树中取出 $l$ 个的方案数，从 $dp_{i,j}$ 转移到 $dp_{i+k\times l,j+l}$。

记录最终计算出来子树有 $i$ 个点的树个数，为 $f_i$。

最后我们钦定根是重心：

* $n$ 为奇数时，有唯一重心，用总方案数减去其中一棵子树大小大于等于 $\frac{n+1}{2}$ 的情况。
* $n$ 为偶数时，可能会有两个重心，于是额外再减掉 $\binom{f_{\frac{n}{2}}}{2}$ 即可。

具体可以参见模板题。

总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define min(i,j) ((i<j)?i:j)
#define mid ((l+r)>>1)
using namespace std;
int dp[1005][11],C[1005][11],tot[1005];
int mod;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
signed main(){
    int n,d; cin>>n>>d>>mod;
    if(n==1){
    	cout<<1;
    	return 0;
	}
    if((n-2)%(d-1)!=0){
    	cout<<0;
    	return 0;
	}
	n=(n-2)/(d-1);
	if(n==0){
		cout<<1;
		return 0; 
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		int tot=0;
		for(int j=0;j<d;j++){
			(tot+=dp[i-1][j])%=mod;
		}
		C[i][0]=1;
		for(int j=1;j<=d;j++){
			C[i][j]=C[i][j-1]*qp(j,mod-2)%mod*(tot+j-1)%mod;
		} 
		for(int j=n;j>=0;j--){
			for(int k=0;k<d;k++){
				for(int l=1;(k+l<=d)&&(j+i*l<=n);l++){
					(dp[j+i*l][k+l]+=dp[j][k]*C[i][l])%=mod;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		tot[i]=dp[i][1];
	}
	(tot[n]+=dp[n-1][d])%=mod;
	int ans=tot[n];
	if(n&1){
		for(int i=1;i<=n/2;i++){
			(ans+=mod-tot[i]*tot[n-i]%mod)%=mod;
		}
	}
	else{
		for(int i=1;i<n/2;i++){
			(ans+=mod-tot[i]*tot[n-i]%mod)%=mod;
		}
		(ans+=mod-tot[n/2]*(tot[n/2]-1)%mod*((mod+1)/2)%mod)%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：OtoriEmu (赞：0)

先提出一个思路，以重心为根计数，可以对计算有多少种不同构的树的问题起到去重的作用。

那么有一个基本的想法是，将所有和题目有关的要素加入到 DP 定义。定义 $dp_{i,j,k}$ 表示，用了 $i$ 个结点，根结点度数为 $j$，其 $j$ 棵子树大小全部**不超过** $k$。

发现这样竟然就能转移了……分两种情况：

1. 没有大小为 $k$ 的子树：$dp_{i,j,k}=dp_{i,j,k-1}$；   
2. 枚举有 $p$ 个大小为 $k$ 的子树：$\displaystyle dp_{i,j,k}=\sum_{l} dp_{i-kl,j-l,k-1}\dbinom{dp_{k,d-1,k-1}+dp_{k,0,k-1}+l-1}{l}$。

欸欸，那个组合数是什么意思呢？其实是我们往下接上 $l$ 个大小为 $k$ 的子树（不必要满足子树的根是子树的重心哦）的方案数。首先 $dp_{k,d-1,k-1}+dp_{k,0,k-1}$ 就是往下接一个子树的方案数，因为下面的点要么没有儿子要么有 $d-1$ 个儿子；然后接 $l$ 个的方案数就是这个组合数了，可以看作网格图向右向上的路径模型，从 $(1,0)$ 出发到 $(dp_{dp_{k,d-1,k-1}+dp_{k,0,k-1},l})$（其中纵坐标表示已经确定了多少个子树，横坐标表示当前选的子树种类；向上就是再选一个当前横坐标代表的子树，向右就是去考虑选下一种合法的子树）。

然后就能暴力转移啦\~答案就是 $dp_{n,d,n/2}$。（其中 $a/b$ 表示 $a$ 除以 $b$ 向下取整，下同。）

但是有一点让 emu 非常困扰呢！就是 $n$ 是偶数的时候重心可能有两个呢。我们需要进一步的去重。注意到这种情况会被多计数一次，我们只需要算一下出现两个重心的方案数就好了！以某一个重心为根的子树大小为 $n/2$，度数为 $d-1$，且与另外一个重心相连，要求相似，那就是在 $dp_{n/2,d-1,n/2-1}$ 里面选出两种树，然后连上他们的根。注意没有顺序，所以这个需要减去的贡献还得除以 $2$。

这样我们就做到不重不漏啦！是不是非常 wonderhoy☆ 呢？

但是有一个很严重的问题！组合数怎么算呢，上面的数不仅非常大，而且会取模 \>\_\<，是不是算不了了？

根据 Lucas 定理，因为 $l \leq 10$，所以 $\dbinom{n}{d}$ 中就算 $n$ 咚、轰轰的大，贡献也只会是 $\dbinom{n/mod}{d/mod} = \dbinom{n/mod}{0} = 1$（沿用题目定义，不用正体），所以可以直接取模，没有问题啦！

完整代码点这里哦：[酸っぱい顔　＞＿＜](https://www.luogu.com.cn/paste/d6capgm1)。

---

