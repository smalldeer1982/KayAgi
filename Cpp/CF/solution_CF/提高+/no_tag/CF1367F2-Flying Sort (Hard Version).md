# Flying Sort (Hard Version)

## 题目描述

This is a hard version of the problem. In this version, the given array can contain equal elements and the constraints on $ n $ are greater than in the easy version of the problem.

You are given an array $ a $ of $ n $ integers (the given array can contain equal elements). You can perform the following operations on array elements:

1. choose any index $ i $ ( $ 1 \le i \le n $ ) and move the element $ a[i] $ to the begin of the array;
2. choose any index $ i $ ( $ 1 \le i \le n $ ) and move the element $ a[i] $ to the end of the array.

For example, if $ n = 5 $ , $ a = [4, 7, 2, 2, 9] $ , then the following sequence of operations can be performed:

- after performing the operation of the first type to the second element, the array $ a $ will become $ [7, 4, 2, 2, 9] $ ;
- after performing the operation of the second type to the second element, the array $ a $ will become $ [7, 2, 2, 9, 4] $ .

You can perform operations of any type any number of times in any order.

Find the minimum total number of operations of the first and second type that will make the $ a $ array sorted in non-decreasing order. In other words, what is the minimum number of operations must be performed so the array satisfies the inequalities $ a[1] \le a[2] \le \ldots \le a[n] $ .

## 说明/提示

In the first test case, you first need to move two 2, to the beginning of the array. Therefore, the desired sequence of operations: $ [4, 7, 2, 2, 9] \rightarrow [2, 4, 7, 2, 9] \rightarrow [2, 2, 4, 7, 9] $ .

In the second test case, you need to move the 1 to the beginning of the array, and the 8 — to the end. Therefore, the desired sequence of operations: $ [3, 5, 8, 1, 7] \rightarrow [1, 3, 5, 8, 7] \rightarrow [1, 3, 5, 7, 8] $ .

In the third test case, the array is already sorted.

## 样例 #1

### 输入

```
9
5
4 7 2 2 9
5
3 5 8 1 7
5
1 2 2 4 5
2
0 1
3
0 1 0
4
0 1 0 0
4
0 1 0 1
4
0 1 0 2
20
16 15 1 10 0 14 0 10 3 9 2 5 4 5 17 9 10 20 0 9```

### 输出

```
2
2
0
0
1
1
1
1
16```

# 题解

## 作者：F_Mu (赞：13)

**题意**

给一个长度为$n$的数组，你可以有两种操作

+ 将某一个数放置在数组开头
+ 将某一个数放置在数组结尾

问最小操作多少次可以得到一个非递减数列

（比$F1$难在$n$变大，且数组中元素可以有相同的）

**分析**

因为数组中的数很大，我们可以将其离散化然后操作，则$a[i]$为连续的整数，设$tot$种不同的数，则$1\leq a[i] \leq tot$

每个数最多操作一次，否则第一次可以不操作，那么我们就要找最多的不需要操作的数，如果不需要操作，则元素的位置不变，如果有这么一组不需要操作的数，我们可以发现，中间的数字是不能插进去的，所以这组数是在排序后仍相邻的数，则要找到最长的子序列，这个子序列在排序后仍然相邻，考虑以下几种情况

+ 这组数相同，则没有限制
+ 这组数中含有两种数，则要形如$i,i,i,i+1,i+1$这种形式，即排序后仍相邻
+ 这组数含有三种以上的数，即形如$i,i,i+1,i+2,i+2,i+3$这种形式，那么中间的数（$i+1$，$i+2$）一定是被取完了，否则其他的$i+1$或者$i+2$要插进去只能重新排序，与中间数字不能插进去不符，即这几个数并不是相邻，例如$i,i+1,i+2,i+1$这种序列，$i,i+1,i+2$并不满足条件，因为$i+1$并没取完

设$dp[i][0]$为只取相同的数且以$a[i]$为结尾所得到的最长子序列，$dp[i][1]$为$a[i]$还没取完且所得到的以$a[i]$为结尾最长子序列，$dp[i][2]$为$a[i]$取完且以$a[i]$为结尾所得到的最长子序列，我们用$pos[i]$表示数字$i$上次出现的位置，因为离散化了，所以数组可以满足，状态转移方程为（​$r[a[i]]$表示$a[i]$最后出现的位置，$l[a[i]]$表示$a[i]$最早出现的位置，$num[a[i]]$表示$a[i]$的个数，$pos[a[i]]$表示上一个$a[i]$出现的位置）：

```cpp
dp[i][0] = dp[pos[a[i]]][0] + 1;
dp[i][1] = max(dp[pos[a[i]]][1] + 1, max(dp[pos[a[i] - 1]][0] + 1, dp[pos[a[i] - 1]][2] + 1));
if (i == r[a[i]])
    dp[i][2] = dp[l[a[i]]][1] + num[a[i]] - 1;
```

+ $dp[i][0]$，方程表示上一个位置的$a[i]$接着取
+ $dp[i][1]$，方程表示上一个$a[i]$接着取，或者上一个$a[i]-1$接着取，或者$a[i]-1$已经全部取完后接着取
+ $dp[i][2]$，方程表示从最早出现的$a[i]$开始，后面都只取$a[i]$

```cpp
#pragma GCC optimize(3, "Ofast", "inline")

#include <bits/stdc++.h>

#define start ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ll long long
#define int ll
#define ls st<<1
#define rs st<<1|1
#define pii pair<int,int>
#define rep(z, x, y) for(int z=x;z<=y;++z)
#define com bool operator<(const node &b)
using namespace std;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int maxn = (ll) 2e5 + 5;
const int mod = 998244353;
const int inf = 0x3f3f3f3f;
int T = 1;
int a[maxn], b[maxn];
int dp[maxn][3];
int l[maxn], r[maxn];
int pos[maxn], num[maxn];

void solve() {
    int n;
    cin >> n;
    rep(i, 1, n)cin >> a[i], b[i] = a[i], dp[i][0] = dp[i][1] = dp[i][2] = 0, l[i] = r[i] = 0, num[i] = 0;
    sort(b + 1, b + n + 1);
    int tot = unique(b + 1, b + n + 1) - (b + 1);
    rep(i, 1, n) {
        a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
        r[a[i]] = i;
        if (!l[a[i]])
            l[a[i]] = i, pos[a[i]] = i;
        ++num[a[i]];
    }
    int maxx = 1;
    rep(i, 1, n) {
        dp[i][0] = dp[pos[a[i]]][0] + 1;
        dp[i][1] = max(dp[pos[a[i]]][1] + 1, max(dp[pos[a[i] - 1]][0] + 1, dp[pos[a[i] - 1]][2] + 1));
        if (i == r[a[i]])
            dp[i][2] = dp[l[a[i]]][1] + num[a[i]] - 1;
        pos[a[i]] = i;
        rep(j, 0, 2)maxx = max(maxx, dp[i][j]);
    }
    cout << n - maxx << '\n';
}

signed main() {
    start;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
```


---

## 作者：老莽莽穿一切 (赞：7)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16131199.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/CF1367F2)

[**CF link**](http://codeforces.com/problemset/problem/1367/F2)

题解区都是一些 dp 做法，这里带来一种**贪心+双指针**的做法。

### 正片开始

题面不多做赘述，直接讲做法。

首先题面等价于选出一个单调递增的子序列，满足剩下的所有数要么比该子序列中最小的数小，要么比该子序列中最大的数大，求子序列最长长度。

发现这个东西可以 dp，但是其实也可以不 dp，直接贪心也可以。

首先一个性质，就是离散化完后选出的子序列在值域上是连续的，且子序列中出现的数除了左右端点的数，别的数只要在序列中出现了，那么所有和这个数相等的数都被必须选中了。

所以形如 $x,x,\cdots,x,x+1,x+1,\cdots,x+1,\cdots,y-1,\cdots,y-1,y,\cdots,y$，且所有 $a$ 满足 $a\in[x+1,y-1]$ 都在该子序列中出现了。

利用这个性质，我们可以先将所有值离散化，然后将每个数出现的所有位置都记下来，然后枚举**值的右端点的前一个**，即上面的 $y-1$，发现可以贪心地找到最靠前的 $x+1$，满足任意 $a\in[x+1,y-2]$ 满足 $r_a<l_{a+1}$，即出现区间无交集。

这个显然可以双指针扫一遍得到，然后左右两边的 $x$ 和 $y$ 直接二分就可以了，其实也可以预处理，即在前面统计每个值出现位置时顺便记录，但二分写着更方便，且本处也不是时间复杂度瓶颈。

但是这样还会算漏一部分，就是当解形如 $x,x,\cdots,x,x+1,\cdots,x+1$ 时，即没有中间全取的区间，两边都取得不完整，这样也可以做，就是直接枚举中间点，即第一个 $x+1$ 的位置，然后二分前面 $x$ 的个数和之后 $x+1$ 的个数。

这样时间复杂度就是 $\mathcal O\left(n\log n\right)$。

接下来就是[**代码**](https://codeforces.com/contest/1367/submission/153361884)。

---

## 作者：endswitch (赞：2)

### 简化题意

选择一个最长的不降子序列满足剩下的数要么大于所选序列的最大值要么小于所选序列的最小值。

### 思路

[简单版题解](https://www.luogu.com.cn/article/qp8rqo6j)。

和简单版的区别在于原序列元素可重。

沿用简单版的思路，我们仍然对答案序列的最后一位讨论。

考虑到题意要求，我们大致可以将答案序列分为 $3$ 种情况：

* 只有一种元素的。
* 后缀元素全部出现的。
* 不知道状态需要后续 dp 求出的。

那么我们设 $dp_{i,0/1/2}$ 分别表示以 $a_i$ 为结尾的答案序列且只有一种元素 / 正在选择元素并拼接到之前答案序列 / 后缀元素全部出现的序列。

设 $lst_{a_i}$ 表示 $a_i$ 上一次出现的位置，$L_{a_i}$ 表示 $a_i$ 第一次出现的位置，$R_{a_i}$ 表示 $a_i$ 最后一次出现的位置，$val_{a_i}$ 表示 $a_i$ 在原序列中出现的次数。

于是便有转移：

$$
dp_{i, 0} = dp_{lst_{a_i}, 0} + 1\\
dp_{i, 0} = \max \{ dp_{lst_{a_i}, 1}, dp_{lst_{a_i - 1}, 0}, dp_{lst_{a_i- 1}, 2} \} + 1\\
dp_{i, 2} = [i = R_{a_i}] \times dp_{L_{a_i}, 1} + val_{a_i} - 1
$$

每次动态维护 $lst_{a_i}$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;
int T, n, a[N], L[N], R[N], lsh[N], lst[N], val[N], dp[N][3];

signed main() {
    ios_base :: sync_with_stdio(NULL);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> T;

    while(T --) {
        for(int i = 1 ; i <= n ; ++ i)
            a[i] = L[i] = R[i] = lsh[i] = lst[i] = val[i] = dp[i][0] = dp[i][1] = dp[i][2] = 0;

        cin >> n;
        for(int i = 1 ; i <= n ; ++ i)
            cin >> a[i], lsh[i] = a[i];

        sort(lsh + 1, lsh + 1 + n);

        int tot = unique(lsh + 1, lsh + 1 + n) - lsh - 1;

        for(int i = 1 ; i <= n ; ++ i)
            a[i] = lower_bound(lsh + 1, lsh + 1 + tot, a[i]) - lsh;
        
        for(int i = 1 ; i <= n ; ++ i) {
            if(! L[a[i]]) L[a[i]] = i;

            ++ val[a[i]];
        }
        
        for(int i = n ; i ; -- i)
            if(! R[a[i]]) R[a[i]] = i;
        
        for(int i = 1 ; i <= n ; ++ i) {
            dp[i][0] = dp[lst[a[i]]][0] + 1;
            dp[i][1] = max({dp[lst[a[i]]][1], dp[lst[a[i] - 1]][0], dp[lst[a[i] - 1]][2]}) + 1;
            if(i == R[a[i]]) dp[i][2] = dp[L[a[i]]][1] + val[a[i]] - 1;

            lst[a[i]] = i;
        }

        int ans = 0;

        for(int i = 1 ; i <= n ; ++ i)
            for(int j = 0 ; j <= 2 ; ++ j)
                ans = max(ans, dp[i][j]);

        cout << n - ans << '\n';
    }

    return 0;
}
```

---

## 作者：Yansuan_HCl (赞：1)

怎么贪心[这篇题解](https://www.luogu.com.cn/blog/LaoMangnoblog/solution-cf1367f2)讲得很好，这里补充一下为什么

> 题面等价于选出一个单调递增的子序列，满足剩下的所有数要么比该子序列中最小的数小，要么比该子序列中最大的数大，求子序列最长长度。

。

显然，如果这样构造，只需要按顺序把没选中的数往前放或往后放即可。

假设我们选中了一个递增序列，但是夹着一个 $x$ 值域在这个序列中但没有被选中。设选中了 $y$ 个数小于 $x$，则需要把这 $y$ 个数都移到后面去，把 $x$ 前移，再把这 $y$ 个数往前移，总共需要 $2y+1$ 次操作。而直接选中所有大于 $x$ 的数显然只需要 $y+1 \le 2y+1$ 次操作。

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

**题意**

给你一个长度为 $N$ 的数列 $A$，每次可以选一个数把它放到序列的起点和终点。问你最少多少次操作能把数列变成单调不降的。序列有重复数字。

序列里的数很大，考虑离散化。设离散化后有 $m$ 种元素。

注意到操作次数必定不多于 $N$（直接重构序列是 $N$ 次）。而直接重构序列时每个点只操作一次。这还是不优化的情况。所以每个点操作更多次只会更劣。

维护哪些点被操作难搞。考虑维护那些点不操作。

首先考虑一个[**更简单的版本**](https://codeforces.com/problemset/problem/1367/F1)：如果没有重复的数字。

注意到往两个数中间插入一个数不如直接按照 $i,i+1,i+2,\cdots$ 的顺序插，防止额外交换。

所以保留的子序列就是原序列的最长的不下降的且元素相邻的子序列。答案就是 $N$ 与子序列长度的差。

设 $dp_i$ 表示以 $i$ 结尾的最长的保留序列。由于保证序列相邻，它一定从 $dp_{i-1}$ 转移。只要在 $dp_{i-1}$ 上加一个 $1$ 即可。

答案就是 $N-\max_{i=1}^m dp_i$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10; 
int a[N],dp[N],n,len,p[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int T;cin>>T;while(T--){
		cin>>n;
		for(int i=1;i<=n;++i)cin>>a[i],p[i]=a[i];
		sort(p+1,p+1+n);int m=unique(p+1,p+1+n)-p-1;
		for(int i=1;i<=n;++i)a[i]=lower_bound(p+1,p+1+m,a[i])-p;
		len=0;
		for(int i=1;i<=m;++i)dp[i]=0;
		for(int i=1;i<=n;++i){
			dp[a[i]]=max(dp[a[i]],dp[a[i]-1])+1;
			len=max(len,dp[a[i]]); 
		}
		len=n-len;
		cout<<len<<'\n';
	}
	return 0;
}
```

接下来考虑有重复数字的情况。

这个时候上面的转移就不行了。由于两数之间不能插入新的数，对于 $1,2,3,2$ 这种序列来说 $1,2,3$ 这样的子序列是不可行的，因为第二个 $2$ 就需要插入。

所以如果有 $i,i+1,i+1,\cdots,i+1,i+2$ 这种保留序列，此时 $i+1$ 必须取完。

由此，我们需要维护 $3$ 个状态：

- $dp_{i,0}$ 表示前 $i$ 个数以 $A_i$ 结尾且只取 $A_i$ 的最大保留长度。
- $dp_{i,1}$ 表示前 $i$ 个数以 $A_i$ 结尾且 $A_i$ 本身没有取完的最大保留长度。
- $dp_{i,2}$ 表示前 $i$ 个数以 $A_i$ 结尾且 $A_i$ 本身已经取完的最大保留长度

如果 $dp_{i,1}$ 要取 $A_i-1$ 的部分的答案那么 $A_i-1$ 的部分一定被取完了。

$dp_{i,2}$ 的转移方式是在 $A_i$ 取完时从最左边出现的 $A_i$ 的位置的 $1$ 种状态增加 $A_i$ 的个数（此时只能取 $A_i$）。

最大长度就是所有状态的最大值。

挺好的思维题。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10; 
int a[N],dp[N][3],n,len,p[N],l[N],r[N],c[N],ls[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int T;cin>>T;while(T--){
		cin>>n;
		for(int i=1;i<=n;++i)cin>>a[i],p[i]=a[i];
		sort(p+1,p+1+n);int m=unique(p+1,p+1+n)-p-1;
		for(int i=1;i<=n;++i)dp[i][1]=dp[i][2]=dp[i][0]=0;
		for(int i=1;i<=m;++i)ls[i]=c[i]=l[i]=r[i]=0;
		for(int i=1;i<=n;++i){
			a[i]=lower_bound(p+1,p+1+m,a[i])-p,++c[a[i]];
			if(!l[a[i]])l[a[i]]=i;r[a[i]]=i;
		}
		len=0;
		for(int i=1;i<=n;++i){
			dp[i][0]=dp[ls[a[i]]][0]+1;
			dp[i][1]=max(dp[ls[a[i]]][1]+1,max(dp[ls[a[i]-1]][0],dp[ls[a[i]-1]][2])+1);
			if(i==r[a[i]])dp[i][2]=dp[l[a[i]]][1]+c[a[i]]-1;
			ls[a[i]]=i;
			len=max(len,max(dp[i][0],max(dp[i][1],dp[i][2])));
		}
		cout<<n-len<<'\n';
	}
	return 0;
}
```

---

## 作者：Mirasycle (赞：0)

先看简单版，其实我们发现答案下阶是序列长度减去最长连续数字上升子序列长度，能否达到呢，因为我们移动数字的顺序是可以自己选择的，所以我们必然可以满足除了最长上升子序列外剩下数字可以在下阶操作次数下完成。

然后是困难版，因为数字可重复了这就麻烦了，如果形如 $x-1~x~x+1~x$ 这样的形式，虽然前三个可以构成上升子序列，但是我们无法把最后一个 $x$ 插入进去，因此简单版的做法在困难版不可取。可以发现这里要求的新最长上升子序列中的每一项（除了第一和最后一项）必须保证所有与之相同的数字都在该序列里出现了。开头和结尾的出现几个无所谓。

于是我们设置出状态 $dp(i,j)$，其中 $j$ 取 $0/1/2$ 分别表示 $a_i$ 作为序列的第一项，中间项和最后一项时序列的最长长度。其中中间项的要求必须是 $i=end_{ai}$。 然后记录上次出现的位置转移即可。

---

## 作者：wangyibo201026 (赞：0)

## soluiton

不是很明白为啥这个题要这么复杂。

首先肯定是要离散化的。

然后我们观察一下，发现题目等价于让你保留一个长度尽可能长的子序列，使得其单调不降且剩下的数要么小于等于这个子序列的最小值，要么大于等于这个子序列的最大值。

再然后我们按照元素值排序，如果相同我们按照下标排序。

然后简单画一下就会发现貌似是一段连续的值域区间？其实不完全是，对于开头和结尾的相同元素段，你可以对于开头只取一段前缀，结尾只取一段后缀（其实也可以任意取区间，不过这样肯定是最优的），然后你每次枚举开头的元素块以及前缀长度，然后二分到最远的结尾块（这个地方就看一看能不能接起来就好），然后再二分一个最长的后缀。

不难发现这样贪心正确性显然，因为你肯定是能选就选，不能选才选一段后缀，因为一个元素块内下标是递增的。

具体过程可以参照代码实现。

## code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int t, n, cnt, ans;
int b[N], l[N], r[N], tmp[N], pre[N], pre2[N];

struct Node {
  int x, id;
} a[N];

void Solve () {
  cin >> t;
  while ( t -- ) {
    ans = cnt = 0;
    cin >> n;
    for ( int i = 1; i <= n; i ++ ) {
      cin >> a[i].x;
      b[++ cnt] = a[i].x;
      a[i].id = i;
    }
    sort ( b + 1, b + 1 + cnt );
    for ( int i = 0; i <= cnt + 1; i ++ ) {
      l[i] = r[i] = 0;
    }
    cnt = unique ( b + 1, b + 1 + cnt ) - b - 1;
    for ( int i = 1; i <= n; i ++ ) {
      a[i].x = lower_bound ( b + 1, b + 1 + cnt, a[i].x ) - b;
    }
    sort ( a + 1, a + 1 + n, [] ( Node x, Node y ) { return x.x == y.x ? x.id < y.id : x.x < y.x; } );
    for ( int i = 1; i <= n; i ++ ) {
      r[a[i].x] = i;
    }
    for ( int i = n; i >= 1; i -- ) {
      l[a[i].x] = i;
    }
    for ( int i = 1; i <= cnt; i ++ ) {
      tmp[i] = ( a[l[i]].id < a[r[i - 1]].id );
      pre[i] = pre[i - 1] + tmp[i];
      pre2[i] = pre2[i - 1] + r[i] - l[i] + 1;
    }
    for ( int i = 1; i <= cnt; i ++ ) {
      ans = max ( ans, r[i] - l[i] + 1 );
    }
    for ( int i = 1; i <= cnt; i ++ ) {
      for ( int j = l[i]; j <= r[i]; j ++ ) {
        int L = l[i + 1] - 1, R = r[i + 1] + 1;
        while ( L + 1 < R ) {
          int mid = L + R >> 1;
          if ( a[mid].id > a[j].id ) {
            R = mid;
          }
          else {
            L = mid;
          }
        }
        ans = max ( ans, j - l[i] + 1 + r[i + 1] - R + 1 );
      }
    }
    for ( int i = 1; i < cnt; i ++ ) {
      for ( int j = l[i]; j <= r[i]; j ++ ) {
        if ( a[l[i + 1]].id < a[j].id ) {
          break;
        }
        int L = i + 1, R = cnt + 1;
        while ( L + 1 < R ) {
          int mid = L + R >> 1;
          if ( pre[mid] - pre[i + 1] <= 0 ) {
            L = mid;
          }
          else {
            R = mid;
          }
        }
        int pos = L;
        L = l[pos + 1] - 1, R = r[pos + 1] + 1;
        while ( L + 1 < R ) {
          int mid = L + R >> 1;
          if ( a[mid].id > a[r[pos]].id ) {
            R = mid;
          }
          else {
            L = mid;
          }
        }
        ans = max ( ans, j - l[i] + 1 + pre2[pos] - pre2[i] + max ( r[pos + 1] - R + 1, 0ll ) );
      }
    }
    cout << n - ans << '\n';
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
### 解题思路：

由于每一个数最多被操作一次，所以可以将题意转化为求出最多的数使得这些数不被变动。而不被变动的条件是选出的这些数以外的数不超过被选的数的最小值或者不小于被选出的数的最大值，只有这样才能将其它的数放到最前面或者最后面。

---

由于数据范围较大，考虑先将所有的数离散化一下，记离散化之后的数组为 $num_i$，并记一种数 $i$ 第一个出现的位置为 $l_i$，最后一次出现的位置为 $r_i$。

记 $f_{i,j\in\{0,1,2\}}$ 表示以第 $i$ 个数结尾，并且有：

1. $j=0$，表示只有 $num_i$ 这一个数出现。

2. $j=1$，表示有 $num_i$ 和其它的至少一个数出现， $num_i$ 是最大的且 $num_i$ 已经全被选了。

3. $j=2$，表示有 $num_i$ 和其它的至少一个数出现， $num_i$ 是最大的但是 $num_i$ 有可能有一部分没有被选中。

---

然后考虑如何转移。对于任意的 $j=0$ 的转移都是容易的，直接将 $i$ 以前的所有的等于 $num_i$ 的数全都取走即可。

对于 $j=1$，这个位置只能出现在 $i=r_{num_i}$，因为之后的数一定不可能被取到。直接将 $f_{l_{num_i},2}$ 转移过来就行了，表示从第一个开始往后一直取 $num_i$。

对于最后一种情况 $j=2$，并不一定要求在 $i=r_{num_i}$ 的位置转移，对于转移点的要求也没有 $j=1$ 那么严格。一种可能的情况就是 $num_i$ 的出现不完全，直接从前一个 $num_i$ 的位置 $k$ 的 $f_{k,2}$ 转移，价值为 $1$。另一种可能就是直接将当前位置的前面的所有 $num_i$ 舍去，从前一个 $num_i-1$ 的位置 $k$ 的 $f_{k,1}$ 或者 $f_{k,0}$ 转移过来。

---
### 代码：

```cpp
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;
int T,n,a[MAXN],b[MAXN],cnt,la[MAXN],l[MAXN],r[MAXN],f[MAXN][3],num[MAXN],maxn;
map <int,int> mp;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			b[i]=a[i];
		}
		sort(b+1,b+n+1);
		b[0]=-1;mp.clear();cnt=0;
		for(int i=1;i<=n;i++)
		if(b[i]!=b[i-1])
		mp[b[i]]=++cnt;
		for(int i=1;i<=n;i++)
		a[i]=mp[a[i]];
		for(int i=1;i<=n;i++)
		f[i][0]=f[i][1]=f[i][2]=0;
		for(int i=1;i<=n;i++)
		l[i]=r[i]=num[i]=la[i]=0;
		for(int i=1;i<=n;i++){
			r[a[i]]=i;
			num[a[i]]++;
			if(l[a[i]]==0)l[a[i]]=i;
		}
		maxn=0;
		for(int i=1;i<=n;i++){
			f[i][0]=f[la[a[i]]][0]+1;
			f[i][2]=max(f[la[a[i]]][2],max(f[la[a[i]-1]][1],f[la[a[i]-1]][0]))+1;//顺序 
			if(i==r[a[i]])f[i][1]=f[l[a[i]]][2]+num[a[i]]-1;
			maxn=max(max(maxn,f[i][2]),max(f[i][0],f[i][1]));
			la[a[i]]=i;
		}
		printf("%d\n",n-maxn);
	}
	return 0;
}
```


---

