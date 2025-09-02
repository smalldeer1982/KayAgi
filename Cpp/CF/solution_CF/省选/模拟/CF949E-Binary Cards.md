# Binary Cards

## 题目描述

It is never too late to play the fancy "Binary Cards" game!

There is an infinite amount of cards of positive and negative ranks that are used in the game. The absolute value of any card rank is a power of two, i.e. each card has a rank of either $ 2^{k} $ or $ -2^{k} $ for some integer $ k>=0 $ . There is an infinite amount of cards of any valid rank.

At the beginning of the game player forms his deck that is some multiset (possibly empty) of cards. It is allowed to pick any number of cards of any rank but the small deck is considered to be a skill indicator. Game consists of $ n $ rounds. In the $ i $ -th round jury tells the player an integer $ a_{i} $ . After that the player is obligated to draw such a subset of his deck that the sum of ranks of the chosen cards is equal to $ a_{i} $ (it is allowed to not draw any cards, in which case the sum is considered to be equal to zero). If player fails to do so, he loses and the game is over. Otherwise, player takes back all of his cards into his deck and the game proceeds to the next round. Player is considered a winner if he is able to draw the suitable set of cards in each of the rounds.

Somebody told you which numbers $ a_{i} $ the jury is going to tell you in each round. Now you want to pick a deck consisting of the minimum number of cards that allows you to win the "Binary Cards" game.

## 说明/提示

In the first sample there is the only round in the game, in which you may simply draw both your cards. Note that this sample test is the only one satisfying the first test group constraints.

In the second sample you may draw the only card $ -1 $ in the first round, cards $ 4 $ and $ -1 $ in the second round, nothing in the third round, the only card $ 4 $ in the fourth round and the whole deck in the fifth round.

## 样例 #1

### 输入

```
1
9
```

### 输出

```
2
1 8
```

## 样例 #2

### 输入

```
5
-1 3 0 4 7
```

### 输出

```
3
4 -1 4
```

## 样例 #3

### 输入

```
4
2 -2 14 18
```

### 输出

```
3
-2 2 16```

# 题解

## 作者：yijan (赞：8)

个人觉得很漂亮的一个题。

首先可以证明一个最优的方案一定有要么只出现 $2^k$ 要么只出现 $-2^{k}$ ，且不会多次出现。

证明很显然，我拿 $a,a$ 明显不如拿 $a,2a$。拿 $-a,a$ 也不如拿 $2a,-a$ 。

从低到高考虑每一位。我们维护当前数组里的所有值。如果有数为奇数，我们要么必须拿 $-1$ 要么必须拿 $1$ 。而且在拿了这两个都一种之后，所有数都会变成偶数。于是我们可以把所有数除以二并且进入一个子问题。

但是直接暴力找，大概是分治的节点个数乘以 $n$ ，难以接受。但是可以发现向下分治的时候值域折半了，所以我们给整个序列去重后，复杂度就是 $O(c\log c)$ 。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 200026
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n , m;
int A[MAXN];

vi nm;
vi sol( int mx = 0 ) {
	if( mx > 19 ) return vi(0);
	int ok = 0;
	for( int& x : nm ) if( x & 1 ) { ok = 1; break; }
	if( !ok ) {
		for( int& x : nm ) x >>= 1;
		return sol( mx + 1 );
	}
	vi cur = nm;
	for( int& x : nm ) if( x & 1 ) x = ( x + 1 ) >> 1; else x >>= 1;
	sort( all( nm ) );
	nm.erase( unique( all( nm ) ) , nm.end() );
	vi as = sol( mx + 1 );
	nm = cur;
	for( int& x : nm ) if( x & 1 ) x = ( x - 1 >> 1 ); else x >>= 1;
	nm.erase( unique( all( nm ) ) , nm.end() );
	vi tr = sol( mx + 1 );
	as.pb( -( 1 << mx ) ) , tr.pb( ( 1 << mx ) );
	return as.size() < tr.size() ? as : tr;
}

void solve() {
	cin >> n;
	rep( i , 1 , n ) scanf("%d",A + i) , nm.pb( A[i] );
	vi ret = sol();
	cout << ret.size() << endl;
	for( int x : ret ) printf("%d ",x);
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
```



---

## 作者：Hoks (赞：4)

## 前言
[题目传送门](https://www.luogu.com.cn/problem/CF949E)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-cf949e)内食用应该不会更佳。
## 题意分析
首先看到我们使用的数字是 $2^k$ 或者 $-2^k$，由此联想到二进制，既然题目说要用这些数字表示出所有的数字，那这些数字就能看做是二进制形式数字每一位的 $1$。

有了这个思路，我们再来考虑有没有可能拿两个一模一样的 $2^k$。显然，这是不可能 的，因为 $2^{k+1}$ 和 $2^k$ 可以比两个 $2^k$ 组成的数字多一个 $3\times 2^k$。肯定是取 $2^{k+1}$ 和 $2^k$ 更优。

再考虑是否存在可能性同时取 $2^k$ 与 $-2^k$，显然这也是不行的，因为它并不优于 $2^{k+1}$ 和 $-2^k$。

最后考虑什么情况我们要取这个数字，那必然是一个数它的最后一位为 $1$ 时，必然要取一个 $1$ 或者 $-1$。然后所有数的最后一位都成为了 $0$，我们就可以将这位 $0$ 砍掉考虑上一位，反复执行上述操作便可以得到可行的方案了。

因为每一位选择 $1$ 和 $-1$ 并不确定，所以考虑用深搜尝试每一种情况。再仔细观察，发现每次除以 $2$ 的时候数字的值域缩小了一倍，如果不去重会有许多重复的搜索而使得时间飞了，所以每一步除以 $2$ 之后选择去重数组。再加上超过目前最优解的剪枝优化与卡常战神 c++98，可以跑进最优解第一页。
## 代码
（有点臭，见谅）
```cpp
#include<bits/stdc++.h>
#define int long long
#define ec 114514
using namespace std;
int n,m=1145141919810,cnt;
int a[21][ec],ans[ec],lj[ec];
void dfs(int step,int len)
{
    if(a[step][1]==0&&len<=1)
    {
        if(cnt<m)
        {
            m=cnt;
            for(int i=1;i<=cnt;i++) ans[i]=lj[i];
        }
        return;
    }
    else if(cnt>m||step>20) return;
    else
    {
        bool flag=0;
        for(int i=1;i<=len;i++)
            if(a[step][i]&1){flag=1;break;}
        if(!flag)
        {
            for(int i=1;i<=len;i++) a[step+1][i]=a[step][i]/2;
            len=unique(a[step+1]+1,a[step+1]+1+len)-a[step+1]-1;
            dfs(step+1,len);
        }
        else
        {
            for(int i=1;i<=len;i++)
                if(a[step][i]&1) a[step+1][i]=(a[step][i]-1)/2;
                else a[step+1][i]=a[step][i]/2;
            lj[++cnt]=(1<<step);
            int pos=unique(a[step+1]+1,a[step+1]+1+len)-a[step+1]-1;
            dfs(step+1,pos);cnt--;
            for(int i=1;i<=len;i++)
                if(a[step][i]&1) a[step+1][i]=(a[step][i]+1)/2;
                else a[step+1][i]=a[step][i]/2;
            lj[++cnt]=-(1<<step);
            pos=unique(a[step+1]+1,a[step+1]+1+len)-a[step+1]-1;
            dfs(step+1,pos);cnt--;
        }
    }
}
int read()
{
    char c=getchar();int x=0,f=1;
    while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
signed main()
{
    n=read();
    for(int i=1;i<=n;i++) a[0][i]=read();
    sort(a[0]+1,a[0]+n+1);
    n=unique(a[0]+1,a[0]+n+1)-a[0]-1;
    dfs(0,n);
    printf("%lld\n",m);
    for(int i=1;i<=m;i++) printf("%lld ",ans[i]);
    return 0;
}
```
完结撒花！

---

## 作者：佬头 (赞：3)

## Description
给出 $n$ 个数 $a\ (n,|a|\leq 100000)$，你需要用最少的 $2^i$ 或 $-2^i(i\in N)$ 以**和**的形式表示出所有数。输出[**方案**](https://www.luogu.com.cn/problem/CF949E)。

## Solution
显然这题和**二进制**有关。

- 首先观察到同一个数只会选最多一次。因为选 $\{2^k,2^k\}$ 不如 $\{2^k,2^{k+1}\}$ 优，前者仅能表示 $\{0,2^k,2^{k+1}\}$，而后者则可以表示 $\{0,2^k,2^{k+1},2^k+2^{k+1}\}$。
- 然后可以发现 $2^k$ 和 $-2^k$ 不会同时选。不如选 $\{2^k,-2^{k+1}\}$ 或 $\{-2^k,2^{k+1}\}$，那么可以表示的数便从 $\{2^k,0,-2^k\}$ 变成了 $\{2^k,0,-2^k,-2^{k+1}\}$ 或 $\{2^k,0,-2^k,2^{k+1}\}$。同时也产生了之后暴搜时的两种情况。
- 接下来考虑缩小问题规模。如果当前所有数都是偶数，直接全部除以 $2$；否则一定要在 $1$ 和 $-1$ 中选一个（也可以理解为在 ${2^k}$ 和 ${-2^k}$ 中选一个）。直接枚举选哪一个，暴搜下去，然后每一层都把数字去个重。

由于 $|a|\le100000$，则 $k$ 最大为 $\lfloor\log_2200000\rfloor=18$，因此暴搜时界定 $k$ 的上限为 $18$。

时间复杂度为 $\mathcal{O}(n\log n)$（加了剪枝优化，比较玄学）。

## Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n, p, a[20][100005], b[20], k, ans[20], minn = 114514;
bool tf;
int read(){
	int x = 0;
	bool tf = 0;
	char a = getchar();
	while(a < '0' || '9' < a){
		if(a == '-') tf = 1;
		a = getchar();
	}
	while('0' <= a && a <= '9') x = (x << 3) + (x << 1) + (a ^ 48), a = getchar();
	return tf? -x: x;
}
void write(int x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
void solve(int base){
	if(base > 18 || minn <= k) return ;
	if(p == 1 && a[base][1] == 0){
		minn = k;
		for(int i = 1; i <= minn; ++ i) ans[i] = b[i];
		return ;
	}
	tf = 1;
	for(int i = 1; i <= p; ++ i)
		if(a[base][i] & 1){
			tf = 0;
			break;
		}
	if(tf){
		for(int i = 1; i <= p; ++ i) a[base + 1][i] = a[base][i] >> 1;
		return solve(base + 1);
	}
	int pp = p;
	b[++ k] = -(1 << base);
	for(int i = 1; i <= pp; ++ i) a[base + 1][i] = (a[base][i] + (a[base][i] & 1)) >> 1;
	p = unique(a[base + 1] + 1, a[base + 1] + pp + 1) - a[base + 1] - 1;
	solve(base + 1);
	b[k] = 1 << base;
	for(int i = 1; i <= pp; ++ i) a[base + 1][i] = (a[base][i] - (a[base][i] & 1)) >> 1;
	p = unique(a[base + 1] + 1, a[base + 1] + pp + 1) - a[base + 1] - 1;
	solve(base + 1);
	k --;
}
int main(){
	n = read();
	for(int i = 1; i <= n; ++ i) a[0][i] = read();
	sort(a[0] + 1, a[0] + n + 1);
	p = unique(a[0] + 1, a[0] + n + 1) - a[0] - 1;
	solve(0);
	write(minn);
	puts("");
	for(int i = 1; i <= minn; ++ i) write(ans[i]), putchar(' ');
	return 0;
}
```
$\texttt{2023 年 11 月 7 日 update:}$ 增加了题目链接。

---

## 作者：Epi4any (赞：3)

今天老师讲了这道题然后我就打算写一篇题解给我的博（gu）客（zhi）回回血。

不难看出，这道题需要找到一些必要的性质，否则优化会很困难。经过简单的尝试，我们可以观察到如下几条性质：
1. 一个数不会选两次。选两个 $x$ 不如选一个 $2x$ 和一个 $x$。
2. 一个数不会同时选它的正数形式和负数形式。选两个 $x$ 不如选一个 $-2x$ 和一个 $x$ 或者选一个 $2x$ 和一个 $-x$。

然后我们就可以对问题进行简化：在初始状态下，可能有几个奇数，那么我们必然会选择一个 $1$ 或者一个 $-1$，让所有的数变成偶数，否则使用其他的 $2^k$ 无法凑出这些奇数。

经过简单的尝试，我们就可以推广这个性质，每一次把序列中的所有元素都变成偶数时把所有的数都除以 $2$，然后就又可以变会初始形态。

**注：每一次除完都要去重！否则会空间**~~(好像也不)~~**会爆炸！**

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=1e9+7;
const int maxn=1e5+10;
int n,a[maxn],rec[30][maxn],save[maxn],cur,ans[maxn],mn=INF;
void dfs(int step, int len) {
    if(rec[step][1]==0 && len<=1) {
        if(cur<mn) {
            mn=cur;
            for(int i=1;i<=cur;i++) { 
                ans[i]=save[i];
            }
        }
        return;
    }
    else if(cur>mn || step>20) return;
    else {
        bool odd=0;
        for(int i=1;i<=len;i++) {
            if(rec[step][i] &1) {
                odd=1;
                break;
            }
        }
        if(!odd) {
            for(int i=1;i<=len;i++) {
                rec[step+1][i]=rec[step][i]/2;
            }
            len=unique(rec[step+1]+1,rec[step+1]+1+len)-rec[step+1]-1;
            dfs(step+1,len);
        }
        else{
            for(int i=1;i<=len;i++) {
                if(rec[step][i] & 1) {
                    rec[step+1][i]=(rec[step][i]-1)/2;
                }
                else{
                    rec[step+1][i]=rec[step][i]/2;
                }
            }
            save[++cur]=(1<<step);
            int pos=unique(rec[step+1]+1,rec[step+1]+1+len)-rec[step+1]-1;
            dfs(step+1,pos);
            cur--;
            for(int i=1;i<=len;i++) {
                if(rec[step][i] & 1){
                    rec[step+1][i]=(rec[step][i]+1)/2;
                }
                else{
                    rec[step+1][i]=rec[step][i]/2;
                }
            }
            save[++cur]=-(1<<step);
            pos=unique(rec[step+1]+1,rec[step+1]+1+len)-rec[step+1]-1;
            dfs(step+1,pos);
            cur--;
        }
    }
}
int main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    n=unique(a+1,a+n+1)-a-1;
    for(int i=1;i<=n;i++) {
        rec[0][i]=a[i];
    }
    dfs(0,n);
    cout<<mn<<endl;
    for(int i=1;i<=mn;i++) {
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return 0;
}
```


---

## 作者：EmptyAlien (赞：2)

[CF949E](https://codeforces.com/problemset/problem/949/E)。

妙妙题。

为了方便叙述，称取出的 card 集合为 $S$。

我们的做法基于以下几点观察：

1. $S$ 为不重集。

    证明：若存在两个 $2^k$ 则 $2^k$ 与 $2^{k+1}$ 一定不劣。

2. 对于 $\forall k \ge 0, 2^k \in S \Longrightarrow -2^k \notin S, -2^k \in S \Longrightarrow 2^k \notin S $。

    证明：若存在 $2^k$ 与 $-2^k$ 则取 $2^k$ 与 $-2^{k+1}$ 一定不劣。

也就是说对于一个 $k$ 只可能从 $\left\{2^k,-2^k\right\}$ 中选一个。

由此我们得到了一个 $\mathcal O(n^2)$ 的算法：

考虑枚举要拼出的数（我们称这个集合为 $T$）的二进制位从低向高搜索，搜索时，若该位全为 $0$ 则直接进入下一位的搜索。

否则枚举该位添 $2^k$ 还是 $-2^k$，将对应位为 $1$ 的加上这个值并向下递归。

但是我们发现一个问题，如果加上对应值后变成了可重集则将其去重显然是合理的，而且还能优化常数。

优化常数？

接下来我们将证明它是 $\mathcal O(n\log n)$ 的。

我们发现对于每一次递归，我们的时间复杂度都是 $\mathcal O(|T|)$ 加上两侧递归的复杂度。

但是注意到在第 $i$ 层时，$T$ 中所有数的最后 $i$ 位均为 $0$。

这限制了，在第 $i$ 层，$\mathcal O(T)= \mathcal O(2^{k - i})$。（$k$ 为总层数）

而 $O(k)=O(\log_2 n)$，所以事实上总复杂度为 $\mathcal O(n \log n)$。

代码实现：

先将 $T$ 排序。

一个递归，在全局维护集合 $T$,并在每次进入递归前存副本，枚举该位后将 $1$ 消掉并使用 `unique` 去重，进入递归。

注意，不能每次 `sort` 再 `unique`，这样时间复杂度变为 $T(n)=\mathcal O(n \log n) + 2T(\cfrac{n}{2})=\mathcal O(n\log^2 n)$。

为什么每次只用 `unique` 而不用排序？

因为每次加上对应的值后其相对位置并不会改变。

```cpp
constexpr int MAXN = 1e5 + 5;
int n, realn[20];
int a[MAXN], backup[20][MAXN];

vi solve (int dep) {
    if (dep >= 20)
        return vi(0);
    bool flg = true;
    rep (i, 1, n)
        if (a[i] & 1)
            flg = false;
    if (flg) {
        rep (i, 1, n)
            a[i] >>= 1;
        return solve(dep + 1);
    }
    rep (i, 1, n)
        backup[dep][i] = a[i];
    realn[dep] = n;
    rep (i, 1, n) {
        if (a[i] & 1)
            a[i]++;
        a[i] >>= 1;
    }
    n = unique(a + 1, a + n + 1) - a - 1;
    vi ans = solve(dep + 1);
    n = realn[dep];
    rep (i, 1, n)
        a[i] = backup[dep][i];
    rep (i, 1, n) {
        if (a[i] & 1)
            a[i]--;
        a[i] >>= 1;
    }
    n = unique(a + 1, a + n + 1) - a - 1;
    vi ans2 = solve(dep + 1);
    n = realn[dep];
    rep (i, 1, n)
        a[i] = backup[dep][i];
    ans.pb(-(1 << dep));
    ans2.pb(1 << dep);
    if (sz(ans) > sz(ans2))
        return ans2;
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    rep (i, 1, n)
        cin >> a[i];
    sort(a + 1, a + n + 1);

    vi ans = solve(0);
    cout << sz(ans) << endl;
    for (int i : ans)
        cout << i << " ";
    cout << endl;

    return 0;
}
```

---

## 作者：Z1qqurat (赞：2)

会うことができて、とても嬉しいだ！

神仙题，和同校选手集思广益想了很多做法才算是结束。鸣谢 @[yxzy4615](https://www.luogu.com.cn/user/222362)，@[ACACACACACACACACACAC](https://www.luogu.com.cn/user/374330)。省流：没切这题的话你大概率看不懂我这篇题解。

首先发现值域 $V \le 10 ^ 5$，那么可能选的数最多只有大概 $38$ 种。然后我们发现虽然说选出来的数是一个可重集，但是我们肯定不会选相同的两个数，举个例子，你选 $2^k, 2^k$，还不如 $2^k, 2^{k + 1}$。所以可以简单暴力枚举每种数选不选，然后用一个可行性 01 背包判断每种数能不能被凑出来。这很慢啊，$O(2^{38} n)$ 左右（本来判断部分是 $38n$ 的但是可以 bitset 优化去掉一个 $\omega$）。

然后再发掘一下性质，$2 ^ k$ 和 $-2 ^ k$ 可能同时选吗？假如要用 $-2 ^ k$，可以用 $2 ^ k - 2 ^ {k + 1}$ 替代，所以发现 $2 ^ k, -2^k$ 中至多选一个，那么对于一个 $k$，只有不选，选 $2^k$，选 $-2^k$ 两种可能。变成了 $O(3 ^ {18}n)$ 的样子。好的我不会优化这个暴力了。

题解做法堪称神，我们把一个例子写下来：

```
1110
1010
 101
```

我们会对 $101$ 做 $+1$ 或者 $-1$ 操作，然后变成了：

```
1110
1010
 100
```

你会发现最后那一列 $0$ 不用管了，变成了集体除 $2$ 后的值。递归地做，每次选择用 $+1 / -1$ 消掉所有奇数，将其变成偶数，然后集体右移一位，做完了。终止条件就是当所有数都是 $1 /-1$ 的时候。

那复杂度是多少？如果每次做一轮我们去掉所有 $0$（观察样例发现 $0$ 根本不用管）并且去重，值域是会减半，所以主定理一下，$T(V) = 2T(V / 2) + O(V), T(V) = O(V \log V)$。然后为了去重采用归并排序（这样就少个 $\log$），因为你只要保证一开始的序列是有序的，那么你的奇数序列和偶数序列都会保证内部有序。**所以得记得一开始对 $a$ 排序并去重**，要不然会荣获 TLE 35。

看看 Tutorial 里面的三个 Bonus：

1. $n \le 1000, V \le 10^{18}$：~~直接相同做法，复杂度为 $O(n ^ 2 \log V)$。~~ 假了，不会。

2. $n \le 10 ^ 5, V \le 10^{18}$：不会，有没有神教教我。

3. 变成 $3 ^ k$：平衡三进制应该可以一样地做？

代码是现场口糊完写的，不太难写但是看起来有点乱，凑合一下吧。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define vc vector<int>
using namespace std;
const int N = 1e5 + 5;
int n, pw[30];

vc dfs(int d, vc a) {
	if(!a.size() || d > 20) return {};
	if(a.size() == 1 && (a[0] == -1 || a[0] == 1)) return {a[0] * pw[d]};
	vc v1, v2, sol;
	for (int i : a) {
		if(i & 1) v1.emplace_back((i - 1) / 2);
		else v2.emplace_back(i / 2);
	}
	vc b; int l = 0, r = 0;
	while(l < v1.size()) {
		while(r < v2.size() && v2[r] <= v1[l]) {
			if(v2[r] != 0 && (!b.size() || v2[r] != b.back())) b.emplace_back(v2[r]); r++;
		}
		if(v1[l] != 0 && (!b.size() || v1[l] != b.back())) b.emplace_back(v1[l]); l++;
	}
	while(r < v2.size()) {
		if(v2[r] != 0 && (!b.size() || v2[r] != b.back())) b.emplace_back(v2[r]); r++;
	}
	//for (int i : b) cout << i << ' ';
 	//return {};
	sol = dfs(d + 1, b);
	if(v1.size() > 0) sol.emplace_back(pw[d]);
	//return sol;
	b.clear(), v1.clear(), v2.clear(); l = r = 0;
	for (int i : a) {
		if(i & 1) v1.emplace_back((i + 1) / 2);
		else v2.emplace_back(i / 2);
	}
	while(l < v1.size()) {
		while(r < v2.size() && v2[r] <= v1[l]) {
			if(v2[r] != 0 && (!b.size() || v2[r] != b.back())) b.emplace_back(v2[r]); r++;
		}
		if(v1[l] != 0 && (!b.size() || v1[l] != b.back())) b.emplace_back(v1[l]); l++;
	}
	while(r < v2.size()) {
		if(v2[r] != 0 && (!b.size() || v2[r] != b.back())) b.emplace_back(v2[r]); r++;
	}
	vc c = dfs(d + 1, b); int sz = c.size() + (v1.size() > 0);
	if(sz < sol.size()) {
		if(v1.size() > 0) c.emplace_back(-pw[d]);
		sol = c;
	}
	return sol;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	pw[0] = 1; for (int i = 1; i <= 20; ++i) pw[i] = (pw[i - 1] << 1);
	cin >> n; vc A;
	for (int i = 1, a; i <= n; ++i) {
		cin >> a; if(a != 0) A.emplace_back(a);
	}
	//cout << A.back() << "\n";
	vc B;
	for (int i : A) if(!B.size() || i != B.back()) B.emplace_back(i); 
	sort(B.begin(), B.end());
	vc ans = dfs(0, B);
	cout << ans.size() << "\n";
	for (int i : ans) cout << i << ' ';
	return 0;
}
```



---

## 作者：神之右大臣 (赞：2)

首先发现：一个数最多会出现1次；

然后深入推出：一个数不会既用它又用它的相反数；

这样就可以依次考虑每一位啦~:
如果所有的数都不含有这一位,那么就直接把所有的数除以2

如果含有，那么就减去这一位的数，再除以2；


当含有的时候搜索就可以了，没错，就是这么暴力！；

注意需通过去重来优化dfs，否则会TLE掉；

```cpp
#include <bits/stdc++.h>
#define N 100010
using namespace std;
int a[N],b[21][N],ans[N],st[N],top=0;
int anss=INT_MAX;
void dfs(int dep,int n){
    if(n<=1&&!b[dep][1]){
        if(top<anss){
            anss=top;
			for(int i=1;i<=top;i++){
				ans[i]=st[i];
			}
        }
        return;
    }
    if(dep>20||top>=anss){
    	return;
    }
    bool flag=1;
    for(int i=1;i<=n;i++){
    	if(b[dep][i]&1){
			flag=0;
			break;
        }
    }
    if(flag){
        for(register int i=1;i<=n;i++){
        	b[dep+1][i]=b[dep][i]/2;
        }
        n=unique(b[dep+1]+1,b[dep+1]+n+1)-b[dep+1]-1;
        dfs(dep+1,n);
        return;
    }
    else{
        for(register int i=1;i<=n;i++){
        	if(b[dep][i]&1){
        		b[dep+1][i]=(b[dep][i]-1)/2;
        	}
            else{
            	b[dep+1][i]=b[dep][i]/2;
            }
        }	            
        st[++top]=1*(1<<dep);
        register int tmp=unique(b[dep+1]+1,b[dep+1]+n+1)-b[dep+1]-1;
        dfs(dep+1,tmp);
        top--;
        for(register int i=1;i<=n;i++){
        	if(b[dep][i]&1){
        		b[dep+1][i]=(b[dep][i]+1)/2;
        	}
            else{
            	b[dep+1][i]=b[dep][i]/2;
            }
        }	            
        st[++top]=-1*(1<<dep);
        tmp=unique(b[dep+1]+1,b[dep+1]+n+1)-b[dep+1]-1;
        dfs(dep+1,tmp);
        top--;
    }   
}
int main()
{
    register int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    n=unique(a+1,a+n+1)-a-1;
    for(int i=1;i<=n;i++){
    	b[0][i]=a[i];
    }
    dfs(0,n);
    printf("%d\n",anss);
    for(int i=1;i<=anss;i++){
    	printf("%d ",ans[i]);
    }
}
```


---

## 作者：Mashu77 (赞：1)

显然，互为相反数的同时出现一定不优。

考虑分治，从低位到高位考虑，如果当前位有 $1$，那么必须选一个 $-2^i$
 或 $2^i$。
 
按照选这两种的其中一种分治下去即可。

每层至少会减少一半的数，所以时间复杂度是正确的。

```cpp
#include<bits/stdc++.h>
#define N 200050
using namespace std;
void uniq(vector<int> &a) {
    sort(a.begin(), a.end());
    vector<int> b;
    a.push_back(-114514);
    for(int i = 0; i < a.size() - 1; i ++) if(a[i] != a[i + 1]) b.push_back(a[i]);
    a.swap(b);
}
vector<int> solve(int dep, vector<int> & a) {
    if(dep > 20) return vector<int>(0);
    uniq(a);
    // printf("** %d\n", dep);
    // for(int x : a) printf("%d ", x); printf("\n");
    int f = 0;
    for(int x : a) f |= (x & 1);
    if(!f) {
        for(int &x : a) x >>= 1;
    //    printf("^");
        return solve(dep + 1, a);
    }
    vector<int> s1, s2;
    for(int x : a) if(x & 1) s1.push_back((x - 1) >> 1); else s1.push_back(x >> 1);
    for(int x : a) if(x & 1) s2.push_back((x + 1) >> 1); else s2.push_back(x >> 1);
    vector<int> ans1 = solve(dep + 1, s1), ans2 = solve(dep + 1, s2);
    ans1.push_back(1 << dep), ans2.push_back(- (1 << dep));
    if((int)ans1.size() < (int)ans2.size()) return ans1;
    return ans2;
}
int n;
vector<int> a;
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }
    vector<int> ans = solve(0, a);
    printf("%d\n", (int)ans.size());
    for(int x : ans) printf("%d ", x);
    return 0;
}

---

## 作者：lupengheyyds (赞：0)

简化搜索条件

#### 题面

给定 $a_{1\sim n}$ 让你构一个最短的序列，使得这个序列的子集和可以表示出这 $n$ 个数，这个序列的元素要求一定是 $\pm 2^k$

$n,a_i\le 2\times 10^5$

#### 题解

注意到以下操作不会使得答案更劣

- $a,a → a,2a$ 。

- $-a,a\to -a,2a$

所以对于一个 $k$，$\pm2^k$ 不会同时存在，

如果 $\forall i, 2|a_i$，就一定不会选择 $\pm1$ 否则就一定选择其中一个。

所以可以对于所有数，判断是否被 $2$ 整除。是则递归进下一个 $k$ 否则枚举是选 $1$ 还是 $-1$,并将所有不能被 $2$ 整除的数（需要这个 $1$ 的数）减去这个数再除以二，递归进入下一个 $k$。

由于每次值域减半，每次去重后再处理，复杂度 $T(n)=2T(\frac n2)+n,\mathcal O(n\log n)$

#### 方法

- 简化搜索条件，使得可能性减少。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=1e5+5;
int n,ans=INT_MAX;
int as[25],b[25];
vector<int> now;
void DFS(int x,int len){
	if(x==20){
		if(len<ans){
			ans=len;
			for(int i=0;i<=20;i++)as[i]=b[i];
		}
		return;
	}
	bool ok=false;
	for(int&x:now)if(x&1){ok=true;break;}
	if(!ok){
		for(int&x:now)x>>=1;
		b[x]=0;
		return DFS(x+1,len);
	}
	vector<int> cur=now;
	b[x]=-1;
	for(int&x:now)if(x&1)x=(x+1)>>1;else x>>=1;
	sort(now.begin(),now.end());
	now.erase(unique(now.begin(),now.end()),now.end());	
	DFS(x+1,len+1);
	b[x]=1;
	now=cur;
	for(int&x:now)if(x&1)x=(x-1)>>1;else x>>=1;
	sort(now.begin(),now.end());
	now.erase(unique(now.begin(),now.end()),now.end());
	DFS(x+1,len+1);
	return;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;cin>>a;
		now.push_back(a);
	}
	sort(now.begin(),now.end());
	now.erase(unique(now.begin(),now.end()),now.end());
	DFS(0,0);
	cout<<ans<<"\n";
	for(int i=0;i<=20;i++)if(as[i]!=0)cout<<as[i]*(1<<i)<<" ";
	return 0;
}
```

---

## 作者：Mashu77 (赞：0)

显然，互为相反数的同时出现一定不优。

考虑分治，从低位到高位考虑，如果当前位有 $1$，那么必须选一个 $-2^i$
 或 $2^i$。
 
按照选这两种的其中一种分治下去即可。

每层至少会减少一半的数，所以时间复杂度是正确的。

```cpp
#include<bits/stdc++.h>
#define N 200050
using namespace std;
void uniq(vector<int> &a) {
    sort(a.begin(), a.end());
    vector<int> b;
    a.push_back(-114514);
    for(int i = 0; i < a.size() - 1; i ++) if(a[i] != a[i + 1]) b.push_back(a[i]);
    a.swap(b);
}
vector<int> solve(int dep, vector<int> & a) {
    if(dep > 20) return vector<int>(0);
    uniq(a);
    // printf("** %d\n", dep);
    // for(int x : a) printf("%d ", x); printf("\n");
    int f = 0;
    for(int x : a) f |= (x & 1);
    if(!f) {
        for(int &x : a) x >>= 1;
    //    printf("^");
        return solve(dep + 1, a);
    }
    vector<int> s1, s2;
    for(int x : a) if(x & 1) s1.push_back((x - 1) >> 1); else s1.push_back(x >> 1);
    for(int x : a) if(x & 1) s2.push_back((x + 1) >> 1); else s2.push_back(x >> 1);
    vector<int> ans1 = solve(dep + 1, s1), ans2 = solve(dep + 1, s2);
    ans1.push_back(1 << dep), ans2.push_back(- (1 << dep));
    if((int)ans1.size() < (int)ans2.size()) return ans1;
    return ans2;
}
int n;
vector<int> a;
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++) {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }
    vector<int> ans = solve(0, a);
    printf("%d\n", (int)ans.size());
    for(int x : ans) printf("%d ", x);
    return 0;
}

---

## 作者：Sevendays_Coder (赞：0)

[Luogu](https://www.luogu.com.cn/problem/CF949E) [Codeforces](https://codeforces.com/problemset/problem/949/E)
 _2700_ 

## 题目大意：

有 $n(1\leq n\leq100000)$ 个数，每个数的绝对值不大于 $10^{5}$。

你需要选用最少的 $2^k$ 或 $-2^{k}$,使得它们能拼成这 $n$ 个数。

求最少选的数的数量与所选的数。

选用的某个 $2^{k}$ 或 $-2^{k}$ 可以重复使用。

### 考虑：

**1**、相反数不会同时选用，如选 $2$ 和 $-2$ 不如选 $4$ 和 $-2$。

**2**、根据二进制原理进行考虑，最低位必选，分取正和取负两种情况，可以暴力枚举，消除最低位的 $1$ 后，将数据整体右移一位，再消除最低位的 $1$ 即可。

**3**、换一种理解方式，如果数据中存在奇数，则必选 $1$ 或 $-1$ ，枚举选 $1$   和 $-1$ 的情况，消除奇数后整体除以 $2$，再消除奇数就行了。对于每次除以 $2$ 之后，选用的数要乘 $2$。 

### 注意：

**1、回溯的问题**：对结果数组，对于每一次的插入数据搜索要进行删除，再建立一个最优解数组存储最优解。对于状态表示数组，修改比较复杂，可以建立一个 $tmp$ 数组记录初始状态。

**2、时间复杂度的问题**：可以用**去重**的方式缩减数组规模，复杂度为 $O(a \log a)$。

**3、递归边界的问题**：由于去重的存在，最终的数组只会存在 $1$ 或 $-1$，特判即可。

### 容易被卡的点：
**1**、$0$ 的特判。

**2**、输入数据的去重。

**3**、不选任何数时输出 $0$。

**4**、状态数组中 $0$ 的删除。


```cpp
#include<vector>
#include<algorithm>
#include<cstdio>
#include<iostream>
using namespace std;
vector<int>v;
vector<int>anst;
vector<int>ans;
int ansp=1e7+1;
void work(int tmp)
{
	if(v.size()==1&&v[0]==1)
	{
		ans.push_back(1*tmp);
		if(ans.size()<ansp)
			ansp=ans.size(),anst=ans;
		ans.pop_back();
		return ;
	}
	
	if(v.size()==1&&v[0]==-1)
	{
		ans.push_back(-1*tmp);
		if(ans.size()<ansp)
			ansp=ans.size(),anst=ans;
		ans.pop_back();
		return ;
	}
	
	bool flag=false;
	for(int i=0;i<v.size();i++)
		if((v[i]&1))
		{
			flag=true;
			break;
		}
			
	if(flag)
	{
		vector<int>vtmp;
		vtmp=v;
		ans.push_back(1*tmp);
		for(int i=0;i<v.size();i++)
			if((v[i]&1))
				v[i]-=1;
		vector<int>::iterator it;
		for(it=v.begin();it!=v.end();)
		{
			if(*it==0)
				v.erase(it);
			else
				it++;
		}
		sort(v.begin(),v.end());
		v.erase(unique(v.begin(),v.end()),v.end());
		work(tmp);
		v=vtmp;
		ans.pop_back();
		
		ans.push_back((-1)*tmp);
		for(int i=0;i<v.size();i++)
			if((v[i]&1))
				v[i]+=1;
		for(it=v.begin();it!=v.end();)
			if(*it==0)
				v.erase(it);
			else
				it++;
		sort(v.begin(),v.end());
		v.erase(unique(v.begin(),v.end()),v.end());
		work(tmp);
		v=vtmp;
		ans.pop_back();
	}
	else
	{
		vector<int>vtmp;
		vtmp=v;
		for(int i=0;i<v.size();i++)
			v[i]/=2;
		work(tmp*2);
		v=vtmp;
	}
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if(x!=0)
			v.push_back(x);
	}
	if(!v.size())
	{ 
		printf("0\n");
		return 0;
	} 
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	work(1);
	printf("%d\n",ansp);
	for(int i=0;i<anst.size();i++)
		printf("%d ",anst[i]);
	return 0;
 } 
```

想到思路之后，实现其实不难，关键的是二进制的思维，这是这道题的亮点

---

