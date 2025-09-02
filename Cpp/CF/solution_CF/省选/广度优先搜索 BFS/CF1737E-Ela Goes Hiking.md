# Ela Goes Hiking

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737E/26fe6dcc65cc8eb40dd577f056ea16ecbcb4a28b.png)Ela likes to go hiking a lot. She loves nature and exploring the various creatures it offers. One day, she saw a strange type of ant, with a cannibalistic feature. More specifically, an ant would eat any ants that it sees which is smaller than it.Curious about this feature from a new creature, Ela ain't furious. She conducts a long, non-dubious, sentimental experiment.

She puts $ n $ cannibalistic ants in a line on a long wooden stick. Initially, the ants have the same weight of $ 1 $ . The distance between any two consecutive ants is the same. The distance between the first ant in the line to the left end and the last ant in the line to the right end is also the same as the distance between the ants. Each ant starts moving towards the left-end or the right-end randomly and equiprobably, at the same constant pace throughout the experiment. Two ants will crash if they are standing next to each other in the line and moving in opposite directions, and ants will change direction immediately when they reach the end of the stick. Ela can't determine the moving direction of each ant, but she understands very well their behavior when crashes happen.

- If a crash happens between two ants of different weights, the heavier one will eat the lighter one, and gain the weight of the lighter one. After that, the heavier and will continue walking in the same direction. In other words, if the heavier one has weight $ x $ and walking to the right, the lighter one has weight $ y $ and walking to the left ( $ x > y $ ), then after the crash, the lighter one will diminish, and the heavier one will have weight $ x + y $ and continue walking to the right.
- If a crash happens between two ants with the same weight, the one walking to the left end of the stick will eat the one walking to the right, and then continue walking in the same direction. In other words, if one ant of weight $ x $ walking to the left, crashes with another ant of weight $ x $ walking to the right, the one walking to the right will disappear, and the one walking to the left will have to weight $ 2x $ and continue walking to the left.

Please, check the example in the "Note" section, which will demonstrate the ants' behavior as above.

We can prove that after a definite amount of time, there will be only one last ant standing. Initially, each ant can randomly and equiprobably move to the left or the right, which generates $ 2^n $ different cases of initial movements for the whole pack. For each position in the line, calculate the probability that the ant begins in that position and survives. Output it modulo $ 10^9 + 7 $ .

Formally, let $ M = 10^9 + 7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

Here is the example of $ 6 $ ants moving on the branch. An ant's movement will be denoted by either a character $ L $ or $ R $ . Initially, the pack of ants on the branch will move as $ RLRRLR $ . Here's how the behavior of the pack demonstrated:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737E/f21f8e2e4fc60059a73573f8369ce1e0c22fa549.png)Initially, the ants are positioned as above.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737E/c80f08134a96c45265eb426e79341773c35563a2.png)After a while, the ant with index $ 2 $ (walking to the left) will crash with the ant with index $ 1 $ (walking to the right). The two ants have the same weight, therefore, ant $ 2 $ will eat ant $ 1 $ and gain its weight to $ 2 $ . The same thing happens with ant $ 5 $ and ant $ 4 $ .

The ant $ 6 $ will walk to the end of the stick, therefore changing its direction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737E/d6d86850388bf6066d31d19dea38cea3f51c263c.png)After that, the ant with index $ 5 $ will crash with the ant with index $ 3 $ . Since ant $ 5 $ is more heavy (weight= $ 2 $ ) than ant $ 3 $ (weight= $ 1 $ ), ant $ 5 $ will eat ant $ 3 $ and gain its weight to $ 3 $ .

Ant $ 2 $ will walk to the end of the stick, therefore changing its direction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737E/ccb7c407541459c45790148ee2eed17a32198269.png)After that, the ant with index $ 5 $ will crash with the ant with index $ 2 $ . Since ant $ 5 $ is more heavy (weight= $ 3 $ ) than ant $ 2 $ (weight= $ 2 $ ), ant $ 5 $ will eat ant $ 2 $ and gain its weight to $ 5 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737E/6539252f8626c992523504c9e36d3f871c33e146.png)Lastly, after ant $ 5 $ walk to the end of the branch and changes its direction, ant $ 5 $ will eat ant $ 6 $ and be the last ant standing.

## 样例 #1

### 输入

```
3
4
5
2```

### 输出

```
0
250000002
250000002
500000004
0
250000002
250000002
250000002
250000002
0
1```

# 题解

## 作者：周子衡 (赞：3)

手动模拟一下整个过程。不难发现：

- 每只向左的蚂蚁一定会先吃掉初始时它面前连续的右向蚂蚁。特别地，最右边那只蚂蚁一开始的方向是无关紧要的，即使它一开始向右，最后也会转到左边；我们不妨认为这只蚂蚁一定向左。
- 在上面的过程结束后，数轴上还剩下若干只大蚂蚁，每只蚂蚁对应原来一只向左的蚂蚁和若干只（被吃掉）的向右的蚂蚁，称它们构成一个 **连续段**。接下来这些蚂蚁会依次 决战：第 $1$ 只大蚂蚁和第 $2$ 只大蚂蚁决战，胜者和第 $3$ 只大蚂蚁决战，胜者再和第 $4$ 只大蚂蚁决战……直到分出胜负。

------------

考虑如何计算概率。注意到每种字符串恰好对应唯一一种将 $n$ 只蚂蚁划分连续段的方案，我们计算能让第 $i$ 只蚂蚁站到最后的连续段方案数 $c_i$，那么所求概率即为 $p_i=\dfrac{c_i}{2^{n-1}}$（其中 $2^{n-1}$ 为总的划分方案数）。

第 $i$ 只蚂蚁能站到最后等价于：它吃掉了所有编号小于它的蚂蚁，并且之后一直没有被吃掉。这两部分是互相独立的，可以分开计算。吃掉所有编号小于它的蚂蚁等价于 $\lceil\dfrac{i}{2}\rceil\sim i$ 的蚂蚁全部分到了一起，计算一下可以知道前半段的总方案数为 $2^{\lfloor\frac{i}{2}\rfloor}$。后半部分可以采用 DP 来计算：设 $g_i$ 表示某蚂蚁在统一 $1\sim i$ 的所有蚂蚁后，接着吃下其他全部蚂蚁的划分方案数，有

$$
g_i=\sum_{j=i+1}^{2i-1}g_j
$$

用前缀和优化即可做到 $O(n)$ 求解。

```cpp
#include<cstdio>
#include<algorithm>

using namespace std;

const long long MOD=1e9+7,INV2=(MOD+1)>>1;

int add(int x,int y){return x+y>=MOD?x+y-MOD:x+y;}
int sub(int x,int y){return x>=y?x-y:x+MOD-y;}

long long fast_pow(long long b,long long p)
{
	long long ans=1;while(p){if(p&1)ans=ans*b%MOD;b=b*b%MOD;p>>=1;}
	return ans;
}
long long INV(long long x){return fast_pow(x,MOD-2);}

long long pw2[2000000],inv2[2000000];
void init(int n)
{
	pw2[0]=inv2[0]=1;
	for(int i=1;i<=n;i++)pw2[i]=pw2[i-1]*2%MOD,inv2[i]=inv2[i-1]*INV2%MOD;
}

long long dp[2000000],sdp[2000000];

int main()
{
	init(1000000);
	int TT=0;scanf("%d",&TT);
	while(TT--)
	{
		int n=0;scanf("%d",&n);
		dp[n]=1;sdp[n]=1,sdp[n+1]=0;
		for(int i=n-1;i>=1;i--)
		{
			int l=i+1,r=min(2*i-1,n);
			dp[i]=sub(sdp[l],sdp[r+1]);
			sdp[i]=add(dp[i],sdp[i+1]);
		}
		for(int i=1;i<=n;i++)
		{
			printf("%lld\n",dp[i]*pw2[i/2]%MOD*inv2[n-1]%MOD);
		}
	}
}
```

---

## 作者：Polaris_Australis_ (赞：3)

[题目传送门（洛谷）](https://www.luogu.com.cn/problem/CF1737E)

[题目传送门（codeforces）](https://codeforces.com/problemset/problem/1737/E)

## 题意

$n$ 只蚂蚁站成一排，第 $1$ 只蚂蚁左边和第 $n$只蚂蚁右边各有一个挡板，相邻两只蚂蚁的距离、第 $1$ 只蚂蚁与左边挡板的距离和第 $n$ 只蚂蚁与右侧挡板的距离相等。初始时每只蚂蚁重量相等，每只蚂蚁有 $\frac{1}{2}$ 概率向左运动，$\frac{1}{2}$ 概率向右运动，每只蚂蚁速度相同。中途蚂蚁不可主动改变方向，如果碰到挡板则向相反方向运动，若两只蚂蚁相遇，重量大的蚂蚁会把重量小的蚂蚁吃掉，重量变为两者之和，如果重量相同，向左运动的蚂蚁会吃掉向右运动的蚂蚁。求对于所有 $i\le1\le n$，第 $i$ 只蚂蚁成为最终的存活者的概率对 $10^9+7$ 取模。

## 思路

首先这题需要一些性质：

1. 除了第 $n$ 只蚂蚁以外，向右运动的蚂蚁一定赢不了。

   证明：显然向右运动的蚂蚁一定会被它右侧第一只向左运动的蚂蚁吃掉，且第 $n$ 只蚂蚁即使向右运动也会碰到挡板，可以视为向左运动。

2. 第 $i$ 只蚂蚁要想赢，其左侧第一只向左运动的蚂蚁 $j$ 必须满足 $j\le\lfloor\frac{i}{2}\rfloor$，且保证对于所有满足 $k\ge2\times i$ 的蚂蚁赢不了。

   证明：根据性质 $1$ 可知，钦定第 $n$ 只蚂蚁向左运动后，向右运动的蚂蚁会最先被吃掉，之后所有的蚂蚁都会向左运动，这样一定满足靠左的蚂蚁会最先交战，而交战后胜者的重量为两者重量之和，若要满足第 $i$ 只蚂蚁胜利，先前交战后胜者的重量为 $j$，第 $i$ 只蚂蚁的重量为 $i-j$，所以必须满足 $i-j\ge i$ 即 $j\le\lfloor\frac{i}{2}\rfloor$ 才能使第 $i$ 只蚂蚁不被左面蚂蚁吃掉，也就是说对于所有 $\lfloor\frac{i}{2}\rfloor+1\le l\le i$，第 $l$ 只蚂蚁必须向右运动。而想要胜利还要保证右边的蚂蚁不会吃掉它，但右边就不能只保证第一只蚂蚁吃不掉它，而是所有蚂蚁都不能吃掉它他才能赢。

跟据这两个性质，不难想到倒着处理，设 $f_i$ 表示第 $i$ 只蚂蚁赢的概率，转移也很明显：

$$
f_i=(1-\sum\limits_{j=2\times i}^{n}f_j)\times\frac{1}{2^{i-1-\frac{i}{2}}}
$$

很好理解，第一部分是保证所有满足 $j\ge2\times i$ 的蚂蚁 $j$ 赢不了，第二部分是求对于所有 $\lfloor\frac{i}{2}\rfloor+1\le l\le i$，第 $l$ 只蚂蚁必须向右运动，其余蚂蚁随意的概率。

有了转移方程，倒着扫一遍就可以了。

## 代码

```cpp
// Problem: E. Ela Goes Hiking
// Contest: Codeforces - Dytechlab Cup 2022
// URL: https://codeforces.com/contest/1737/problem/E
// Memory Limit: 256 MB
// Time Limit: 2500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

const int N = 1000010, mod = 1000000007, iv2 = 500000004;
int T, n;
long long php[N], ans[N];

int main() {
    php[0] = 1;
    for (int i = 1; i < N; ++i) php[i] = php[i - 1] * iv2 % mod;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        long long rest = 1;
        int now = n + 1;
        for (int i = n; i; --i) {
            int t1 = i - 1 - i / 2;
            int t2 = (i << 1);
            while (now > t2) {
                --now;
                rest = (mod + rest - ans[now]) % mod;
            }
            long long tmp = php[t1];
            if (i != n) tmp = tmp * iv2 % mod;
            ans[i] = tmp * rest % mod;
        }
        for (int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
    }
}
```


---

## 作者：huazai676 (赞：1)

[link](https://www.luogu.com.cn/problem/CF1737e)

模拟一下，发现第 $i$ 只蚂蚁能存活仅当：
1. 开始时这只蚂蚁向左移动，否则一定会被最右边的吃掉。
2. 设 $i$ 往左第一个向左移动的蚂蚁为 $j$，则 $i$ 会先吃掉 $(j,i]$ 的蚂蚁再与 $[1,j]$ 组成的蚂蚁抗衡，所以需要满足 $j \leq i-j$。概率为给 $\lfloor \frac{i}{2}\rfloor$ 到 $i$ 定向的概率 $2^{-\lceil \frac{i}{2}\rceil}$。
3. 此时这只蚂蚁的大小已经为 $i$，需要向右吃掉其他蚂蚁。考虑右边的蚂蚁初始方向一定形如 $\longrightarrow\longrightarrow\longrightarrow\longleftarrow \ \ \ \longrightarrow\longrightarrow\longleftarrow \ \  \ \longleftarrow \ \ \ \longrightarrow\longleftarrow$，此时形成的蚂蚁大小依次是 $4,3,1,2$，$i$ 在吃掉每个前应该保证已经大于它。问题转化为对上述合法的划分方案计数。考虑枚举划分出的第一段蚂蚁的长度 $j \in [1,i)$，发现剩下的划分方案已经转化为子问题，可以递归求解。于是设 $f_i$ 表示将 $(i,n]$ 划分为若干段，大小为 $i$ 的蚂蚁可以依次吃完的合法方案数。转移：$f_i=\sum\limits_{j \in (i,2i)}f_j$，可以前缀和优化。

注意最后一只蚂蚁可以选择碰壁反弹，初始方向可以随意选，所以令 $f_n=2$。

[code](https://codeforces.com/contest/1737/submission/232592874)

---

## 作者：zuytong (赞：1)

[CF1737E](https://www.luogu.com.cn/problem/CF1737E)


------------
## 思路

我们考虑第 $i$ 只蚂蚁能否获胜。

首先，如果它往右走，那只有被吃掉的命运（最后一只蚂蚁除外，因为它向左或向右走没有区别）。

因此，它开始只能往左走，那么首先会遇到的就是 $< i$ 的蚂蚁，我们左边怎么构造能让他胜出：

我们从 $i-1$ 处向左找，找到第一个向左走的蚂蚁 $j$。

显然，无论 $1\sim j$ 的蚂蚁中谁胜出，都会变成一只体重为 $j$ 的蚂蚁。

而原本的第 $i$ 只蚂蚁此时的体重为 $i - j$，如果要让它获胜，必须有 $j\le i-j$。

那么其实就是 $1$ 到 $\lfloor\frac{i}{2}\rfloor$ 的蚂蚁方向可以任选，而 $\lfloor\frac{i}{2}\rfloor + 1\sim i-1$ 的蚂蚁必须向右走（去给 $i$ 送吃的）。

因此左边的方案数为 $2^{\lfloor\frac{i}{2}\rfloor}$。



------------
我们再来考虑右边的情况。

我们假设 $i$ 到 $n$ 中向左走的蚂蚁的位置为 $b_0,b_1,b_2,...,b_k$，其中 $b_0=i$。

如果 $i$ 要获胜，那么需要满足以下条件：

$$b_x>b_{x+1}-b_x$$

这是保证时刻能吃掉对方。

实际上，当我们吃掉 $b_1$ 后，就相当于将 $i$ 变成 $b_1$，然后变成一个子问题。

因此我们可以考虑从 $n$ 开始跑一次 DP，设 $f_i$ 为位置 $i$ 要获胜，右边蚂蚁有多少种排列方法。

转移为：

$$f_i=\sum_{j=i+1}^{2i-1} f_j$$

可以用前缀和优化 DP。


------------
## 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
#define FOR(i, x, y) for(int i = (x); i <= (y); i++)
#define ROF(i, x, y) for(int i = (x); i >= (y); i--)
#define PFOR(i, x) for(int i = he[x]; i; i = r[i].nxt)
inline int rd()
{
    int sign = 1, re = 0; char c = getchar();
    while(!isdigit(c)){if(c == '-') sign = -1; c = getchar();}
    while(isdigit(c)){re = re * 10 + (c - '0'); c = getchar();}
    return sign * re;
}
namespace MOD
{
    const int mod = 1e9 + 7;
    inline int add(int a, int b) {return a + b >= mod ? a + b - mod : a + b;}
    inline int mul(int a, int b) {return 1ll * a * b % mod;}
    inline int sub(int a, int b) {return a - b < 0 ? a - b + mod : a - b;}
    inline int fast_pow(int a, int b = mod - 2)
    {
        int re = 1;
        while(b)
        {
            if(b & 1) re = mul(re, a);
            a = mul(a, a);
            b >>= 1;
        }
        return re;
    }
} using namespace MOD;
inline void solve()
{
    int n = rd();
    std::vector<int> f(n + 5, 0), sum(n + 5, 0);
    f[n + 1] = sum[n + 1] = 1;
    ROF(i, n, 1)
    {
        int p = std::min(n + 1, (i << 1) - 1);
        f[i] = sub(sum[i + 1], sum[p + 1]);
        if(p == n) f[i]++;
        sum[i] = add(sum[i + 1], f[i]);
    }
    int inv = fast_pow(500000004, n);
    f[n]++;
    FOR(i, 1, n)
    {
        int ans = mul(f[i], fast_pow(2, i - ((i + 1) >> 1)));
        printf("%d\n", mul(ans, inv));
    }
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    int T = rd();
    while(T--) solve();
    return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

容易发现，一开始所有向左走的会吃掉左边连续的向右走的。不妨设之后每个位置的大小是 $x_i$。

接下来，我们手摸会发现经过每一次操作，最左边的两个会发生碰撞，不论谁赢大小一定会变成他们的和。也就是说，在若干次操作之后，每个位置的大小会变成 $x_1+x_2+\dots+x_i,x_{i+1},x_{i+2},\dots,x_m$。

容易发现如果某个位置想吃掉所有前面的一大坨，他需要比前面的都大，也就是说要满足前一个向左的 $j$ 满足 $2j\leq i$。

$n$ 位置的答案是容易计算的，考虑前面的，计每个位置答案为 $f_i$。

我们有两个要求：他能吃掉前面所有的，他不被后面的吃。也就是说 $f_{2i},f_{2i+1},\dots,f_n$ 不应该成为最后的。同时他前面的连续的向右段要至少是前面的一半。

容易推出转移方程 $f_i=\dfrac{1-\sum_{j=2i}^nf_j}{2^{\lfloor\frac 2 i\rfloor}}$。前缀和优化可以做到 $O(n\log n)$ 或 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[3000005],inv[3000005];
void init(){
	fac[0]=1; for(int i=1;i<=3000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[3000000]=qp(fac[3000000],mod-2); for(int i=2999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
int dp[1000005],pre[2000005],inv2=(mod+1)/2;
signed main(){
	int t; cin>>t;
	while(t--){
		int n; cin>>n;
		for(int i=1;i<=2*n;i++) pre[i]=0;
		dp[n]=qp(inv2,(n-1)/2);
		pre[n]=dp[n];
		for(int i=n-1;i>=1;i--){
			dp[i]=(1+mod-pre[i*2])*qp(inv2,(i-1)/2+1)%mod;
			pre[i]=(pre[i+1]+dp[i])%mod;
		}
		for(int i=1;i<=n;i++) cout<<dp[i]<<"\n";
		cout<<'\n';
	}
	return 0;
}

```

---

## 作者：Glacial_Shine (赞：0)

更好的[阅读体验](https://blog.csdn.net/weixin_46700592/article/details/129673733?spm=1001.2014.3001.5502)。

# 思路
我们先将题目看成 $n$ 个点的问题。

首先我们知道，如果一个点初始方向是向右，那么他无论如何都不可能活到最后。

所以我们只需要考虑向左的情况。

我们可以求出它初始方向向左时活到最后的方案数，然后除于所有的方案，就是我们要求的概率了，接下来我们考虑如何求出活到最后的方案数。

我们可以将整个过程分为两部分，首先向左走到底，此时右边的无论如何变化都不会影响到当前左边的部分，然后再转向向右。

设当前点为 $i$，对于左边的部分，如果有一个点的编号大于 $\lfloor\frac{i}{2}\rfloor$ 并且它的初始方向向右，则当前节点一定会被这个节点吃掉。

所以编号大于 $\lfloor\frac{i}{2}\rfloor$ 的点的初始方向都要向右，所以左边一共有 $2^{\lfloor\frac{i}{2}\rfloor}$ 种方案。

再考虑右边的部分，我们设当前的方案数为 $f_i$（不考虑左边的部分），则如果对于所有小于 $2\cdot i$ 的点的方向全部向右，则说明当前节点一定会被吃掉（如果最后一个点向右，那么在吞掉别人之前一定会碰到墙回头，所以可以看成向左），为了防止当前节点被吃掉，则无论如何在小于 $2\cdot i$ 的节点中有向左的，我们便可以写出关于 $f_i$ 的式子：

$$
f_i = \sum_{j=i+1}^{2\cdot i} f_j
$$

可以用前缀和优化到 $O(n)$ 的时间复杂度。

然后将左边和右边的方案数乘起来，在除于所有的方案数，就是答案了。


# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 1e9 + 7;
int T, n;
LL f[3000005], g[3000005];
LL Pow(LL a, LL b) {
    LL s = 1;
    while (b) {
        if (b & 1)
            s = s * a % MOD;
        a = a * a % MOD, b = b >> 1;
    }
    return s;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= 2 * n; i++)
            f[i] = g[i] = 0;
        f[n] = g[n] = 1;
        for (int i = n - 1; i; i--)
            f[i] = (g[i + 1] - g[i * 2] + MOD) % MOD, g[i] = (g[i + 1] + f[i]) % MOD;
        for (int i = 1; i <= n; i++)
            printf("%lld\n", f[i] * Pow(2, i / 2) % MOD * Pow(Pow(2, n - 1), MOD - 2) % MOD);
    }
    return 0;
}
```



---

## 作者：hejianxing (赞：0)

[题目(cf)](http://codeforces.com/problemset/problem/1737/E)

[题目(洛谷)](https://www.luogu.com.cn/problem/CF1737E)

# 题目大意

有 $n$ 只蚂蚁等距站成一排，两边有挡板。每只蚂蚁等概率地选择一个运动方向（向左或向右），初始重量为 $1$. 每只蚂蚁速度相同，当两只蚂蚁相遇，重量大的吃掉重量小的，重量相等则向左的吃掉向右的，重量变为两者之和。若撞到挡板，则向相反方向运动。求每只蚂蚁活到最后的概率 $\bmod 10^9+7$.

# 题解

对于每只蚂蚁需求存活的方案数除以总方案数。

首先明确：第 $1$ 只蚂蚁和第 $n$ 只蚂蚁可以认为方向确定。第 $1$ 只蚂蚁一定向右，第 $n$ 只蚂蚁一定向左。第 $1$ 只蚂蚁向左或向右的效果都是一样的，如果向左则会撞墙反弹。也即第 $1$ 只蚂蚁有向左向右两种方案，而这两种方案得出的结果是完全一样的。当第 $2$ 只蚂蚁到第 $n$ 只蚂蚁的方向都确定，若第 $1$ 只蚂蚁向右有 $x$ 种方案，那么向左也是 $x$ 种方案，总共 $2x$ 种方案，答案为 $\frac {2x}{2^n}=\frac x {2^{n-1}}$. 也就可以看做方向确定。第 $n$ 只蚂蚁同理。

考虑对于蚂蚁 $i$，它必须吃掉除了它之外的所有蚂蚁。若 $i$ 左边第一只向左走的蚂蚁为 $j$，那么无论怎样，$1$ 到 $j$ 都会变成一只重量为 $j$ 的蚂蚁，$i$ 的重量为 $i-j$. 如果 $i$ 要存活，那么满足 $j\le i-j$，也即 $j\le \lfloor \frac i 2\rfloor$. 那么第 $2$ 只蚂蚁到第 $\lfloor \frac i 2\rfloor$ 只蚂蚁方向任意，第 $\lfloor \frac i 2\rfloor+1$ 只蚂蚁到第 $i-1$ 只蚂蚁一定向右，那么 $i$ 左边的方案数为 $2^{\lfloor \frac i 2\rfloor-1}$.

接下来考虑右边的方案。

设 $i$ 右边第一只向左走的蚂蚁为 $j$，同上推理得 $i$ 存活的条件为 $j<2i$.

设 $f_i$ 为蚂蚁 $i$ 存活时右边的方案数。

有 $f_i=\sum\limits_{j=i+1}^{2i-1}f_j$.

这东西显然可以前缀和（实际上是后缀和）$O(n)$ 搞。

$ans_i=\dfrac {2^{\lfloor \frac i 2\rfloor-1}\times f_i}{2^{i-2}}=\dfrac {2^{\lfloor \frac i 2\rfloor}\times f_i}{2^{i-1}}$.

直接快速幂 $O(n\log n)$ 有概率寄掉。预处理后时间复杂度为 $O(n)$. 总的时间复杂度为 $O(\sum n)$.

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1000005;
const LL mod = 1e9 + 7;
int T, n;
LL f[N], sum[N], inv[N], mi[N];
LL qpow(LL x, LL y) {
    LL sum = 1;
    while (y) {
        if (y & 1) sum = sum * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return sum;
}
void init() {
    mi[0] = inv[0] = 1;
    LL inv2 = qpow(2, mod - 2);
    for (int i = 1; i < N; i++) mi[i] = mi[i - 1] * 2 % mod, inv[i] = inv[i - 1] * inv2 % mod;
}
int main() {
    init();
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        memset(f, 0, sizeof(f)), memset(sum, 0, sizeof(sum)), f[n] = sum[n] = 1, sum[n + 1] = 0;
        for (int i = n - 1; i >= 1; i--) f[i] = ((sum[i + 1] - sum[min(n + 1, i * 2)]) % mod + mod) % mod, sum[i] = (sum[i + 1] + f[i]) % mod;
        for (int i = 1; i <= n; i++) printf("%lld\n", f[i] * mi[i / 2] % mod * inv[n - 1] % mod);
    }
    return 0;
}
```
# END


---

## 作者：OtoriEmu (赞：0)

首先模拟几个小情况，记 `L` 表示第 $i$ 只蚂蚁向左走，`R` 表示向右走。比如 `RLLRRLRRLLLRRLRRR`，最后一个 `R` 可以直接变成 `L` 不影响，那么假设当前的 `L` 位置在 $r$，左边最近的 `L` 在 $l$，这样就会形成一个向左的重量为 $r-l$ 的蚂蚁。现在就相当于若干个向左走的蚂蚁，比如上面那种情况就应该表示成 $2,1,3,3,1,1,3,3$。

据此可以得到 $O(n^3)$ 的 DP，但是这样很菜。

注意到上面这种转化的方式本质上可以被看做将一个大块切成若干个小块，首先可以发现有效的方案数只有 $2^{n-1}$ 个（最后一个是什么不影响），并且发现比较的方式类似于，“取出队头的两个数，将值小的合并到大的（有偏序关系），求出和并放回队头”，直接考虑倒推。定义 $f_i$ 表示当前队头蚂蚁重量为 $i$，这只蚂蚁获胜的方案数。可以发现有 $f_i = \sum_{j=i+1}^{2i-1} f_j$，可以后缀和优化（不乘系数的原因是，$f_i \to f_j$ 的方案只有一种，后面的没确定的在 $f_j$ 里处理）。

接下来要算的是第 $i$ 只蚂蚁要在前 $i$ 只蚂蚁中活下来的概率，注意到要获胜一定要有至少 $\lceil \frac{i}{2} \rceil$ 的重量，所以方案数是 $2^{\lfloor \frac{i}{2} \rfloor}$。两者独立，乘起来再除以总方案数即可。

[评测记录](https://codeforces.com/contest/1737/submission/180262300)。

---

