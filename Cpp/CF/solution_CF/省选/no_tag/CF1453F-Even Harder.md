# Even Harder

## 题目描述

Gildong is now developing a puzzle game. The puzzle consists of $ n $ platforms numbered from $ 1 $ to $ n $ . The player plays the game as a character that can stand on each platform and the goal of the game is to move the character from the $ 1 $ -st platform to the $ n $ -th platform.

The $ i $ -th platform is labeled with an integer $ a_i $ ( $ 0 \le a_i \le n-i $ ). When the character is standing on the $ i $ -th platform, the player can move the character to any of the $ j $ -th platforms where $ i+1 \le j \le i+a_i $ . If the character is on the $ i $ -th platform where $ a_i=0 $ and $ i \ne n $ , the player loses the game.

Since Gildong thinks the current game is not hard enough, he wants to make it even harder. He wants to change some (possibly zero) labels to $ 0 $ so that there remains exactly one way to win. He wants to modify the game as little as possible, so he's asking you to find the minimum number of platforms that should have their labels changed. Two ways are different if and only if there exists a platform the character gets to in one way but not in the other way.

## 说明/提示

In the first case, the player can only move to the next platform until they get to the $ 4 $ -th platform. Since there is already only one way to win, the answer is zero.

In the second case, Gildong can change $ a_2 $ , $ a_3 $ , and $ a_4 $ to $ 0 $ so that the game becomes $ 4 $ $ 0 $ $ 0 $ $ 0 $ $ 0 $ . Now the only way the player can win is to move directly from the $ 1 $ -st platform to the $ 5 $ -th platform.

In the third case, Gildong can change $ a_2 $ and $ a_8 $ to $ 0 $ , then the only way to win is to move in the following way: $ 1 $ – $ 3 $ – $ 7 $ – $ 9 $ .

## 样例 #1

### 输入

```
3
4
1 1 1 0
5
4 3 2 1 0
9
4 1 4 2 1 0 2 1 0```

### 输出

```
0
3
2```

# 题解

## 作者：George1123 (赞：13)

宰鸽子 $\to$ [`George1123`](https://www.cnblogs.com/George1123/p/14336794.html)

---

## 题面

> [CF1453F Even Harder](https://www.luogu.com.cn/problem/CF1453F)

> 有一行 $n$ 个鸽子，每个鸽子有个跳跃能力 $a_i$，表示站在这个鸽子上的人可以跳到每个满足 $i+1\le j< i+a_i$ 的第 $j$ 个鸽子。现在有个人在第 $1$ 只鸽子身上，他的目标是跳到第 $n$ 子鸽子身上。请问您最少杀死几只鸽子（使 $a_i$ 变成 $0$），使得这个人到最后一个鸽子有正好 $1$ 种方案。 

> 数据范围：$2\le n\le 3000$，$0\le a_i\le n-i$。

---

## 题解

什么时候 `Codeforces` 有这么 `AtCoder` 的题了 `/yiw`。

为了方便，令 $a_i=a_i+1$（题面中条件是已经加过了的）。

---

有一种基于暴力的 `naive` 做法，可是是错的：

设 $f_{i,k}$ 表示到第 $i$ 个鸽子，有 $k$ 种方案的最小宰鸽数（如果有 $>2$ 种方案当作 $2$）。

可是数据 `1\n5\n3 1 2 1 0\n` 把我宰了，因为这种做法会重复统计宰鸽。 

---

考虑分析这个唯一的被人踩了的鸽子的序列 $p_1,p_2,\dots ,p_m$，会发现以下性质：

1. 对于每个 $p_i$，这只鸽子肯定没有被宰掉，且 $p_i+a_{pi}>p_{i+1}$。

2. 每个 $p_i$ 必须满足 $p_i+a_{pi}\le p_{i+2}$。否则如下图最下面的红边，就会多产生一种方案。

3. 每个 $p_i<j<p_{i+1}$ 必须满足 $j+a_j\le p_{i+1}$。否则 $p_i$ 先走橙色边，再走短的红边，就会多产生一种方案。

![CF1453F.jpg](https://i.loli.net/2021/01/27/KT6czile9hH4QDd.jpg)

---

所以可以尝试维护 $f[u][v]$ 表示最后两个 $p_i$ 是 $u,v$ 的方案数，然后就有了一个 $\Theta(n^3)$ 的做法。

然后可以发现，如果给 $u$（从左往右第 $2$ 个黄鸽）向右延伸的边（绿边）一个右滑的机会，那么转移可以变成 $\Theta(n^2)$。

即设 $f[v][j]$ 表示当前最后一个 $p_i=v$，然后 $p_{i-1}$ 可以跳到 $j$ 之前的最小宰鸽数。

$v$ 即是图中间的黄鸽子，$j$ 即所有绿鸽子。转移的下一个 $v'$ 即最右端的肉鸽子。

转移过程就是枚举 $v'$ 和 $v$，然后从 $f[v][v']$ 转移到 $f[v'][v+a_v]$，代价是把 $v$ 和 $v'$ 之间可以跳到 $v'$ 右边的鸽子全部宰掉。

然后把第二维前缀最小值一下，表示一个滑的过程。

---

## 代码

```cpp
//George1123
#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef vector<int> vi;
typedef pair<int,int> pii;

#define x first
#define y second
#define sz(a) (int)((a).size())
#define all(a) (a).begin(),(a).end()
#define R(i,n) for(int i=0;i<(n);++i)
#define L(i,n) for(int i=(n)-1;i>=0;--i)

constexpr int inf32=0x3f3f3f3f;
constexpr i64 inf64=0x3f3f3f3f3f3f3f3f;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);

    int t;
    for(cin>>t;t--;){
        int n;
        cin>>n;
        vi a(n);
        R(i,n) cin>>a[i],++a[i];
        vector<vi> f(n,vi(n+1,inf32));
        R(i,n)if(i) f[0][i]=0; 
        R(i,n)if(i){
            int c=0;
            L(j,i){
                if(j+a[j]<=i) continue;
                f[i][j+a[j]]=min(f[i][j+a[j]],f[j][i]+(c++));
            }
            for(int j=i+1;j<n;++j)
                f[i][j+1]=min(f[i][j+1],f[i][j]);
        }
        cout<<f[n-1][n]<<'\n';
    }
    
    return 0;
}

/*
1
5
3 1 2 1 0 
*/

/* stuff you should look for
    * int overflow, array bounds
    * special cases (n=1?)
    * do smth instead of nothing and stay organized
    * WRITE STUFF DOWN
    * DON'T GET STUCK ON ONE APPROACH
*/
```

---

**祝大家能踩着我这只被杀死的鸽子，越飞越远！**

---

## 作者：DPair (赞：8)

一眼 DP，然后发现直接处理 $a$ 序列不是很好搞。

注意到最终只剩下一条路径，因此可以直接对最后的跳跃序列跑 DP。

考虑设 $f_{i,j}$ 表示 $i, j$ 为跳跃序列最后两个元素要删除的 $j$ 之前的点的个数。

考虑转移：（默认 $i$ 能到达 $j$，不能到达直接设为 $\infty$）
$$
f_{i,j}=\min_{k\in[1,i)\land j>(a_k+k)}\{f_{k,i}\}+\sum_{p=i+1}^{j-1}[p+a_p\ge j]
$$
这个式子显然 $\mathcal{O}(n^3)$，因此考虑优化。

后面一项很好处理，我们考虑前一项的处理方式。

然后我们考虑 $k$ 合法的条件，首先发现 $k$ 是一个 $[1,i)$ 区间内的前缀。

我们考虑枚举 $k$，然后拿它对所有 $j > (a_k+k)$ 产生贡献，注意到这是一个后缀。

因此可以考虑在对应的 $(a_k+k)+1$ 上打上 tag 然后用前缀 $\min$ 的方式贡献所有合法的位置。

最后递推地把第二项加上就行，复杂度 $\mathcal{O}(n^2)$。

代码只放关键部分：

```cpp
int n, a[MAXN], f[MAXN][MAXN], cnt[MAXN];

inline void work() {
    read(n); rep(i, 1, n) a[i] = i + read();

    memset(f[0], 63, sizeof(f[0]));
    f[0][1] = 0;
    
    rep(i, 1, n - 1) {
        memset(f[i], 63, sizeof(f[i]));
        memset(cnt, 0, sizeof(cnt));
        rep(j, 0, i - 1) if(a[j] + 1 <= a[i]) chmin(f[i][a[j] + 1], f[j][i]);
        rep(j, i + 1, a[i]) chmin(f[i][j], f[i][j - 1]);
        int s = 0; rep(j, i + 1, a[i]) {
            f[i][j] += s;
            ++ cnt[a[j]]; ++ s;
            s -= cnt[j];
        }
    }

    int ans = INF;
    rep(i, 1, n - 1) chmin(ans, f[i][n]);
    print(ans);
}

signed main() {
    a[0] = 1;
    int T = read();
    while(T --) work();
}
```



---

## 作者：acb437 (赞：7)

# 题解: [CF1453F Even Harder](https://www.luogu.com.cn/problem/CF1453F)
## 题目大意
>给定数组 $a$，$a_i$ 表示从 $i$ 能走到 $[i+1, i+a_i]$，问至少需要把几个 $a_i$ 改成 $0$，才能使得 $1$ 到 $n$ 有且仅有一条路径。  
$n \le 3000$。

## 思路简述
显然是一道 DP 问题。可以考虑对唯一路径进行 DP。

先研究一下要把最终路径上的点要满足的条件。不妨设最后的唯一路径上的点分别为 $p_1=1,p_2,\cdots,p_t=n$，则对于每一个 $p_i$，从 $1$ 到达它的路径同样是唯一的。因此，限制条件如下：

1. 对于路径上相邻三个点 $p_{i-1}$，$p_i$ 和 $p_{i+1}$ 都有 $p_i+a_{p_i}\ge p_{i+1} > p_{i-1}+a_{p_{i-1}}$，即 $p_i$ 能到达 $p_{i+1}$ 且 $p_{i-1}$ 无法到达 $p_{i+1}$，否则，从 $1$ 到 $p_{i+1}$ 的路径就会有从 $p_{i-1}$ 到 $p_{i+1}$ 和从 $p_i$ 到 $p_{i+1}$ 两条。
2. 对于所有 $p_{i-1}<j<p_i$，都有 $j+a_j<p_i$。由于上一个条件，$p_{i-1}+a_{p_{i-1}}\ge p_i>j$，所以如果不满足 $j+a_j<p_i$，从 $1$ 到 $p_{i+1}$ 的路径就会有从 $p_{i-1}$ 到 $p_i$ 和从 $p_{i-1}$ 到 $j$，再从 $j$ 到达 $p_i$ 两条。

由于上述两条限制条件都与 $p$ 上的相邻两点有关，可以考虑建立以相邻两点确定状态的转移方程。设 $dp_{i,j}$ 表示在从 $1$ 到 $j$ 的唯一路径上，$j$ 的上一个点是 $i$ 的情况下最少要把几个 $a_x(1 < x < j)$ 改成 $0$。转移方程如下：

$$dp_{i,j}=\min_{k\in[1,i)\land k+a_k<j}dp_{k,i}+\sum_{x=i+1}^{j-1}[x+a_x\ge j]$$

前半段的 $\min$ 是对路径的倒数第二和第三个点进行枚举转移，后半段的 $\sum$ 是计算 $(i,j)$ 中需要清零的数量。这个转移方程是 $O(n^3)$ 的，考虑进行优化。由于转移方程的前后两段基本独立，可以分开考虑。

发现从 $dp_{i,j}$ 的角度考虑前半部分的转移不好优化，从 $dp_{k,i}$ 的角度考虑，可以发现对于每一个 $dp_{k,i}$，它能更新所有满足 $i+a_i\ge j>k+a_k$ 的 $j$，因此，可以在枚举 $i$ 时，枚举 $k$ 对每一个 $k$ 所能更新的 $j_{min}=k+a_k+1$ 进行更新，然后通过递推的方式更新到每一个 $j(i<j\le i+a_i)$。

接着考虑后半部分的优化，同样可以发现，对于每一个 $x$，只会对满足 $x+a_x\ge j$ 的 $j$ 造成贡献，又因为 $x$ 和 $j$ 的枚举范围大致相同，于是可以以标记的形式进行贡献的计算。为了方便起见，下文以 $j$ 代指当前枚举的 $j$，而以 $nxt$ 代指后面的 $j$。具体地，枚举 $j$ 进行更新时，会对每一个 $j<nxt\le j+a_j$ 造成贡献，于是可以在 $j+a_j$ 的位置打一个标记，并将当前贡献（设为 $s$）增加 $1$，表示这个位置给后面的 $nxt$ 造成的贡献，而经过 $j+a_j$ 时，令 $s$ 减去标记，表示打标记的位置（即 $j$）造成的贡献到此结束。

代码参考了 [DPair 大佬的这篇题解](https://www.luogu.com.cn/article/8tvlofry)：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#define N 3005
using namespace std;
int t, n, ans, a[N], cnt[N], dp[N][N];

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for(int i = 1;i <= n;i++)scanf("%d", &a[i]);
        memset(dp, 0x3f, sizeof(dp));
        dp[0][1] = 0;
        for(int i = 1;i < n;i++)
        {
            int s = 0;
            memset(cnt, 0, sizeof(cnt));
            //a[i] + i:用i更新的最大j
            for(int j = 0;j < i;j++)//一下4行的j实际上就是上文的k
                if(j + a[j] < a[i] + i) //用j更新它能更新的最小值
                    dp[i][j + a[j] + 1] = min(dp[i][j + a[j] + 1], dp[j][i]);
            for(int j = i + 1;j <= a[i] + i;j++)dp[i][j] = min(dp[i][j], dp[i][j - 1]); //用j - 1递推更新
            for(int j = i + 1;j <= a[i] + i;j++)
            {
                dp[i][j] += s;
                cnt[j + a[j]]++;s++;
                s -= cnt[j];
            }
        }
        ans = 0x3f3f3f3f;
        for(int i = 1;i < n;i++)ans = min(ans, dp[i][n]);
        printf("%d\n", ans);
    }
    return 0;
}
```
谨以此篇题解作为二十余天前君堡陷落 $571$ 周年的纪念。

---

## 作者：睿智的憨憨 (赞：3)

# CF1453F 解题报告

## 原题链接

https://codeforces.com/problemset/problem/1453/F

## 题目大意

给定数组 $a$，$a_i$ 表示从 $i$ 能走到 $[i+1,\max(i+a_i,n)]$，问至少需要把几个 $a_i$ 改成 $0$，才能使得 $1$ 到 $n$ 有且仅有一条路径，$n \le 3000$。

## 算法分析

我们称从某一点到 $n$ 的唯一路径为**主链**。显然这条唯一路径是一条链，否则就不满足题目要求。有一个不成熟的想法：考虑倒着 dp，设 $dp_i$ 表示 $i$ 为主链起点时，$[i,n]$ 中最多能保留几个元素。转移时枚举起点 $i$ 和下一个主链上的点 $j$，$dp_i$ 可从 $dp_j$ 转移，因为 $[i+1,j-1]$ 中的点都不是主链上的点，我们又想尽可能多保留点，所以 $[i+1,j-1]$ 中的点 $k$ 能保留当且仅当 $k+a_k<j$。

然而这个做法有后效性：若 $dp_i$ 从 $dp_j$ 转移而来，$dp_j$ 由 $dp_k$ 转移而来，我们此时只能保证 $i$ 到 $j$ 有唯一路径，但是却不能保证 $i$ 到 $k$ 也只有唯一路径，即路径不是一条链了。所以 dp 状态要增设一维变成 $dp_{i,j}$，表示主链以 $i$ 为起点，以 $j$ 为第二个点时，最多能保留几个元素。

虽然这个做法时间爆炸，但是可以优化。增设两个数组 $s_{i,j}$ 和 $mx_{i,j}$。$s_{i,j}$ 表示前 i 个点中，$k+a_k \le j$ 的个数，$mx_{i,j}$ 表示 $\max(dp_{i,j \sim n})$。现在我们就可以 $O(n^2)$ 解决这道题啦！

建议先把转移式子在纸上或注释中写出来，进行 dp 的优化时可以有效提高正确率。另外，~~亲测~~用线段树取代 $mx$ 数组同样能过。

## 参考代码
```cpp
#pragma GCC optimize(2, "inline", "Ofast")
#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
int T, n, a[3010];
//dp[i][j]:i到n只有一条路径，且下一个主链上的点是j，最多保留几个 
//s[i][j]:前i，k+a[k]<=j个数 
//mx[i][j]:max(dp[i][j~n])
int dp[3010][3010], s[3010][3010], mx[3010][3010];
//初始化 
void init(){
	for (int i = 1; i <= n + 1; i++)
		for (int j = 1; j <= n + 1; j++)
			mx[i][j] = dp[i][j] = ~inf;
	dp[n][n] = dp[n][n] = 1;
}
int main(){
	scanf("%d", &T);
	for (int it = 1; it <= T; it++){
		scanf("%d", &n);
		for (int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			for (int j = 1; j <= n; j++)
				s[i][j] = s[i - 1][j] + ((i + a[i]) <= j);
		}
		init();
		for (int i = n - 1; i >= 1; i--){
			if (n <= i + a[i])
				dp[i][n] = s[n - 1][n - 1] - s[i][n - 1] + 2;
			for (int j = i + 1; j <= min(n - 1, i + a[i]); j++)
				dp[i][j] = mx[j][i + a[i] + 1] + s[j - 1][j - 1] - s[i][j - 1] + 1;
			for (int j = n; j > i; j--)
				mx[i][j] = max(mx[i][j + 1], dp[i][j]);
		}
		int ans = 0;
		for (int i = 2; i <= n; i++)
			ans = max(ans, dp[1][i]);
		printf("%d\n", n - ans);
	}
	return 0;
} 
```

---

## 作者：弦巻こころ (赞：3)

设$f[i][j]$跳到$i$号点的最小的改变次数,$j=a[k]+k$,$k$是上一个跳到的位置,$a[k]+k$就是指$k$最远能跳到的位置


那么对于$i$只要上上次跳不到它,就会产生贡献,所以我们可以有一个很$naive$的转移式

$$
f[i][j]=min(f[j][k]+c) (j\in[1,i-1] ,k\in[j,i-1],c=a[k]+k>=i)
$$
然后我们发现这是$n^3$的,考虑优化转移式子,我们可以将$f$前缀$min$得到$g$,然后转移式子就变成了
$$
g[i][j]=min(f[i][k]) (k\in [i,j])
$$
$$
f[i][j]=g[j][i-1]+c (j\in[1,i-1])
$$
至于$c$我们可以倒着枚举,就不用每次都去扫一遍得到了,最后输出$g[n][n]$就是答案.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3145;
int n,a[N],f[N][N]; 
int main(){int t;cin>>t;while(t--){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]+=i;//直接将a[i]+i,就不在后面加了.
	for(int i=2;i<=n;i++){int c=0;
		for(int j=i;j<=n;j++)f[i][j]=1919810;
		for(int j=i-1;j>=1;j--){
			if(a[j]<i)continue;//如果a[j]都跳不到,那必然没有贡献
			f[i][a[j]]=min(f[i][a[j]],f[j][i-1]+c);c++;
		}for(int j=i+1;j<=n;j++)f[i][j]=min(f[i][j],f[i][j-1]);//后缀min
	}printf("%d\n",f[n][n]);
}} 
```



---

## 作者：_YangZJ_ (赞：2)

来点和其他题解不一样的做法，目前是提交中的最优解。

倒过来做，首先记 $vr_i =i + a_i$，那么考虑所有能到 $n$ 的点，这些点 **只能保留一个，其余都要将 $a_i$ 置为 $0$**。证明考虑反证：

假设存在 $i<j$，满足 $i,j$ 都能到达 $n$。观察一下可以发现如果 $1$ 能到达 $j$ 那么 $1$ 必能到达 $i$，而 $i$ 显然还可以到达 $j$，因此至少存在：$1\rightarrow i\rightarrow n,1\rightarrow i\rightarrow j\rightarrow n$  这两条路径，不合法。

那么我们问题就变成了，只保留一个点 $x$ 能到达 $n$，并且 $1\rightarrow x$ 的方案数唯一，于是就可以 $\text{dp}$ 了。

注意在递归去求解 $x$ 的时候，其他所有 $vr\geq n$ 的边都被删除了，因此设状态 $f_{i,j}(j>i)$ 表示 $vr\geq j$ 的边都被删除了的情况下，$1\rightarrow i$ 的路径唯一的最小代价。$j$ 的实际意义就是 $1\rightarrow n$ 的那条唯一路径中，$i$ 的后继节点。

转移正着来做，所有 $i\leq vr_x<j$ 的 $x$，保留一个将剩下的全部删除，由这些点的 $f_{x,i}$ 转移过来。

转移每个点的时候，从小到大枚举 $j$，依次将可行的 $x$ 加入，复杂度 $O(n^2)$。

code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define vc vector
#define pb emplace_back

const int N = 3005, P = 1e9+7;
const int inf = 0x3f3f3f3f;
mt19937 gen(time(0));

//in&out
inline int read() {
	int x = 0, w = 0; char ch = getchar(); while(!isdigit(ch)) w |= (ch=='-'), ch = getchar();
	while(isdigit(ch)) x = (x*10)+(ch^48), ch=getchar(); return w?-x:x;
}

int n, vr[N], f[N][N];
vc<int> o[N];

inline void solve() {
	n = read();
	for(int i = 1; i <= n; i++) o[i].clear();
	for(int i = 0; i <= n + 1; i++) for(int j = 0; j <= n + 1; j++) f[i][j] = inf;
	for(int i = 1; i <= n; i++) vr[i] = min(n, i + read());
	for(int i = 2; i <= vr[1]; i++) f[1][i] = 0; o[vr[1]].pb(1);	
	for(int i = 2; i < n; i++) {
		int val = inf, cnt = 0;
		for(int j = i + 1; j <= vr[i]; j++) {
			for(auto u:o[j - 1]) val = min(val, f[u][i]), ++cnt;
			if(cnt) f[i][j] = val + cnt - 1;
		}
		o[vr[i]].pb(i);
	}
	int val = inf, cnt = 0;
	for(auto u:o[n]) val = min(val, f[u][n]), ++cnt;
	cout << val + cnt - 1 << endl;
}

signed main() {
	int t = read(); while(t--) solve();
	return 0;
}
```



---

## 作者：Felix72 (赞：1)

可以对最后的路径 DP，$i \to j$ 的代价是他们俩之间之间 $p + a_p \leq j$ 的 $p$ 的个数，且对于 $i \to j \to k$ 要满足 $i + a_i < k$，那么 $O(n^3)$ 的做法就呼之欲出了：每次枚举 $i, j, k$，做 $f_{i, j} + w(j, k) \to f_{j, k}$ 转移，答案是 $f_{?, n}$。

$i \to j \to k$ 的转移中，之所以要记录 $i$，是因为它对于 $k$ 有限制。因此我们想要对于 $k$ 快速找到所有 $i + a_i < k$ 的 $i$ 的最小 $f_{i, j}$。这个 $i + a_i$ 是个定值，因此不妨把 $f_{i, j}$ 这个状态修改为 $f_{p, j}$，其中 $p$ 记录的就是 $i + a_i$ 这一类的限制。这样用前缀 $\min$ 就可以快速找到了。

实际上，这种思想是一次转移有多步时的常用优化方式。即分析 $i, j, k$ 之间的相互影响，通过分别处理 $i \to j$ 和 $j \to k$，使得复杂度从相乘变成并列。

---

## 作者：daniEl_lElE (赞：1)

考虑唯一路径是哪条。不妨设为 $p_1=1,p_2,p_3,\dots,p_m=n$。

考虑我们要满足哪些条件：

* $p_i<j<p_{i+1}$ 中所有 $j$ 均无法到达 $p_{i+1}$。
* $p_i$ 无法到达 $p_{i+2}$。

于是设计 $dp_{i,j}$ 表示目前考虑的 $p_k=i$，$p_{k-1}+a_{p_{k-1}}=j$ 的情况下至少要将多少 $a_i$ 清零。

转移可以枚举 $p_{k+1}$，但是这样是 $O(n^3)$ 的。

考虑转移要啥，不难发现转移到的位置要在 $j$ 之后，且转移系数 $tr$ 是 $i+1$ 到转移位置前一个中，能到转移位置的数量。对于每个位置产生贡献的显然是一段区间。

于是，前者可以前缀 $\max$ 优化，后者可以维护一个前缀和。

总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int a[3005];
int dp[3005][3005],pre[3005];
signed main(){
	int t; cin>>t;
	while(t--){
		int n; cin>>n; for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=0;i<=n+1;i++) for(int j=0;j<=n+1;j++) dp[i][j]=1e18;
		dp[1][2]=0;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++) pre[j]=0;
			int tmp=0;
			for(int j=i+1;j<=i+a[i];j++){
				dp[i][j]=min(dp[i][j],dp[i][j-1]);
				dp[j][i+a[i]+1]=min(dp[j][i+a[i]+1],dp[i][j]+tmp);
				pre[j+a[j]]--,tmp+=pre[j],tmp++;
			}
		}
		cout<<dp[n][n+1]<<"\n";
	}
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

感觉没有 *2700。

观察题目，要求是有且仅有一条路径。第一反应正向做，那就不可避免地需要记录若干个位置的路径情况，非常麻烦。于是此时一个常见的思路是从最终状态入手，也就是考虑最后这条路径长什么样。

考虑如果最后仅有的一条路径为 $b_1,b_2,\cdots,b_m$，那么对于 $a_i$ 有什么限制：

- 对于一个不在 $b$ 里的 $i$，设其下一个在 $b$ 中的位置为 $b_j$，则若 $i+a_i\ge b_j$，则显然有到达 $b_{j-i}\to a_i\to b_j$。于是限制即为 $\forall j<m,\forall i\in(b_j,b_{j+1}),i+a_i<b_{j+1}$。

- 对于一个在 $b$ 里的 $i=b_j$，若 $b_{j-2}+a_{b_{j-2}}\ge b_j$ 则显然会多路径。于是限制即为 $\forall j>2,b_{j-2}+a_{b_{j-2}}<b_j\le b_{j-1}+a_{b_{j-1}}$。

那么就可以先设计一个简单的 dp：设 $dp_{i,j}$ 表示当前路径走到 $b_k=i$，且 $b_{k-1}+a_{b_{k-1}}=j$ 的最少操作次数。则有 $dp_{i,j+a_j}=\min_{k<i\le j+a_j}(dp_{j,k}+f(j,i))$。其中 $f(l,r)$ 表示 $(l,r)$ 内需要的操作次数之和，可以 $O(n^2)$ 预处理。

现在是 $O(n^3)$ 的，但是发现 $i,k$ 之间的限制仅有 $k<i$，所以容易记录一个变量，前缀 $\min$ 优化，就可以 $O(n^2)$ 解决了。

同时，有一篇题解对这样的优化思路说的很好：

> 实际上，这种思想是一次转移有多步时的常用优化方式。即分析 $i,j,k$ 之间的相互影响，通过分别处理 $i\to j$ 和 $j\to k$，使得复杂度从相乘变成并列。

我认为这是一个非常有启发性的思维方式。

code：

```cpp
int n,m,a[N],dp[N][N],f[N][N];
void Yorushika(){
	read(n);
	rep(i,1,n){
		read(a[i]);
	}
	rep(i,1,n){
		f[i-1][i]=0;
		drep(j,i-2,1){
			f[j][i]=f[j+1][i]+(j+1+a[j+1]>=i);
		}
	}
	rep(i,1,n){
		rep(j,1,n){
			dp[i][j]=inf;
		}
	}
	dp[1][1]=0;
	rep(i,1,n-1){
		int mn=dp[i][i];
		rep(j,i+1,n){
			dp[j][a[i]+i]=min(dp[j][a[i]+i],mn+f[i][j]);
			mn=min(mn,dp[i][j]);
		}
	}
	printf("%d\n",dp[n][n]);
}
signed main(){
	int t=1;
	read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：luogubot (赞：0)

给定数组 $a$，$a_i$ 表示从 $i$ 能走到 $[i+1, i+a_i]$，问至少需要把几个 $a_i$ 改成 $0$，才能使得 $1$ 到 $n$ 有且仅有一条路径。

$n \leq 3000$。

这道题设计到了合适的 dp 状态就能比较简单地转移，而 dp 状态的选取一般可以从比较初步的想法逐步优化得到。题目的关键信息是“有且仅有一条路径”，那么就有两种直观的方式刻画：把路径数放在状态里，或是把路径数为一在转移中始终满足。前者无非设计状态 $f_{i,j}$ 表示从 $1$ 到 $i$ 有 $j$ 条路径最少删掉的点数，而转移就很难计算 $j$ 一维新的值；后者则设计状态 $f_i$ 表示 $1$ 到 $i$ 仅有一条路径最少删掉的点数，发现这样难以设计转移：$f_i$ 转移到某个 $f_j$ 时，需要强制让 $1$ 号点能到达的“其它”点不能到达 $j$，其它指的是唯一路径上除去 $i$ 以外的点。这导出了一个需要额外记录的信息：$1$ 号点能到哪些点。

仅关注唯一的 $1$ 到 $i$ 的路径 $p_1,p_2,\cdots p_k$，$p_1=1,p_k=i,p_i+a_{p_i}\ge p_{i+1}$，考虑 $p_{1\cdots k-1}$ 能到达的点： $i<k,[p_i+1,p_i+a_{p_i}]$ 的并集再添上 $1$。由于 $p_i+a_{p_i}\ge p_{i+1}$，它们能到达 $j\ge i$ 的一个前缀 $[1,j]$，也就是说只需要一个值 $j$ 就能描述“$1$ 号点能到哪些点”这个信息，则用二元组 $(i,j)$ 表示 $1$ 到 $i$ 只有一条路径，且路径上的点 $i$ 以外的点最远恰好能到达 $j$ 的状态。那么枚举 $i$ 下一步到达的点 $k\in(j,i+a_i]$，需要删掉的是 $(i,k)$ 中能通过一步到达 $k$ 的所有点，因为它们可以由 $i$ 一步走到之后再到达 $k$，创造了超过一条路径，新的最远点是 $i+a_i$。至此已经得到了一个多项式复杂度的做法，接下来可以加入一些套路地优化。

每个状态都枚举后继是不优的，这会导致复杂度始终至少是 $O(n^3)$，考虑枚举前驱转移，即枚举状态 $(i,k+a_k)$ 的前一步 $(k,x)$，满足 $k+a_k\ge i$，$x<i$，现在需要枚举的是 $i,k,x$，不妨通过优化状态设计来避免 $x$ 的枚举：由于 $j$ 影响的只有 $k$ 的范围，把最远恰好能到达 $j$ 改为最远到达不超过 $j$，则 $x$ 可以固定到 $i-1$。现在的贡献可以记为 $c(L,R)$ 表示 $[L,R]$ 内能一步到达 $R+1$ 的个数，查询的就是 $c(k+1,i-1)$，$c$ 可以预处理，也可以在倒序枚举 $k$ 时统计。

复杂度 $O(n^2)$。

---

## 作者：t162 (赞：0)

从后往前考虑，如果一个位置 $i$，满足有至少两个能到 $n$ 的位置在 $[i+1,i+a_i]$ 中，这个位置一定要改成 $0$（不然原本确定的那一条路径就可能借道这个位置以找到更多路径），如果没有一个能到 $n$ 的位置，则这个位置保留不会让答案更劣。

于是一个显然的 DP，设 $f(i,j)$ 表示第 $i$ 个数能到达 $n$，最近的能到 $n$ 的位置是 $j$ 时的最多不改成 $0$ 的个数。

转移：
$$
f(i,j)\leftarrow f(j,p)+1+w(i,j)\quad(p>i+a_i)
$$
转移取 $\max$，其中 $w(i,j)$ 表示 $i,j$ 之间无法走到 $j$ 的位置个数，做 DP 的时候直接计算即可。然后后缀 $\min$ 优化一下就行了。

[code](https://codeforces.com/contest/1453/submission/174050227)

---

## 作者：OMG_wc (赞：0)

题意是数轴上有 $n$  个点，每个点可以往右移动到 $[i+1,i+a_i]$ ，现在要把某些位置的 $a_i$ 清零，使得从 $1$ 号点到 $n$ 号点只有唯一一条路径。求改变的最小次数，$n\le 3000$。



定义状态 $f_{i,j}$ 表示到 $i$ 号点的最小的改变次数，并且 $j=a_k+k$，其中 $k$ 表示上一个位置。

设 $g_{i,j}=\min\limits_{i\le k\le j} f_{i,k}$ ，也就是 $f_{i,j}$ 的后缀最小值。

初始值 $f_{1,1}=0$，要求的答案就是 $f_{n,n}$。

那么转移方程为 $f_{i,a_k+k}=\min\limits_{k<i}\{g_{k,i-1}+cnt\}$，其中 $cnt$ 表示 $t+a_t\ge i$ 个数量 （ $t\in[k+1,i-1]$ ）。

因为这样的 $t$ 会导致存在路径 $k\rightarrow t \rightarrow i$ ，而 $g_{k,i-1}$ 能保证 $k$ 的前继点不会直接到 $i$。

计算 $cnt$ 需要 $O(n)$ 时间，但没必要对每个 $(i,j)$ 重新算一次，只需从 $i-1$ 倒叙枚举 $k$ 然后顺势累计即可。

总时间复杂度 $O(n^2)$，代码如下：

```c++
int f[N][N], a[N];
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            a[i] += i;
        }
        for (int i = 2; i <= n; i++) {
            for (int j = i; j <= n; j++) f[i][j] = INF;
            int cnt = 0;
            for (int k = i - 1; k >= 1; k--) {
                if (a[k] < i) continue;
                f[i][a[k]] = min(f[i][a[k]], f[k][i - 1] + cnt);
                cnt++;
            }
            for (int j = i + 1; j <= n; j++) f[i][j] = min(f[i][j], f[i][j - 1]);
        }
        printf("%d\n", f[n][n]);
    }
    return 0;
}
```





---

