# Paint Charges

## 题目描述

A horizontal grid strip of $ n $ cells is given. In the $ i $ -th cell, there is a paint charge of size $ a_i $ . This charge can be:

- either used to the left — then all cells to the left at a distance less than $ a_i $ (from $ \max(i - a_i + 1, 1) $ to $ i $ inclusive) will be painted,
- or used to the right — then all cells to the right at a distance less than $ a_i $ (from $ i $ to $ \min(i + a_i - 1, n) $ inclusive) will be painted,
- or not used at all.

Note that a charge can be used no more than once (that is, it cannot be used simultaneously to the left and to the right). It is allowed for a cell to be painted more than once.

What is the minimum number of times a charge needs to be used to paint all the cells of the strip?

## 说明/提示

In the third test case of the example, it is sufficient to use the charge from the $ 1 $ -st cell to the right, then it will cover both cells $ 1 $ and $ 2 $ .

In the ninth test case of the example, you need to:

- use the charge from the $ 3 $ -rd cell to the left, covering cells from the $ 1 $ -st to the $ 3 $ -rd;
- use the charge from the $ 5 $ -th cell to the left, covering cells from the $ 4 $ -th to the $ 5 $ -th;
- use the charge from the $ 7 $ -th cell to the left, covering cells from the $ 6 $ -th to the $ 7 $ -th.

In the eleventh test case of the example, you need to:

- use the charge from the $ 5 $ -th cell to the right, covering cells from the $ 5 $ -th to the $ 10 $ -th;
- use the charge from the $ 7 $ -th cell to the left, covering cells from the $ 1 $ -st to the $ 7 $ -th.

## 样例 #1

### 输入

```
13
1
1
2
1 1
2
2 1
2
1 2
2
2 2
3
1 1 1
3
3 1 2
3
1 3 1
7
1 2 3 1 2 4 2
7
2 1 1 1 2 3 1
10
2 2 5 1 6 1 8 2 8 2
6
2 1 2 1 1 2
6
1 1 4 1 3 2```

### 输出

```
1
2
1
1
1
3
1
2
3
4
2
3
3```

# 题解

## 作者：wxzzzz (赞：14)

### 思路

DP。

令 $f_i$ 表示将 $1\sim i$ 染色的最小代价。

考虑分类讨论答案。

1. 将 $[i-a_i+1,i]$ 染色。代价为 $\displaystyle\min_{j=i-a_i+1}^i f_{j-1}+1$。

1. 将 $[j,j+a_j-1]\ (j+a_j-1\ge i)$ 染色。代价为 $\displaystyle\min_{j=1}^{i-1}[j+a_j-1\ge i]f_{j-1}+1$。

但仅仅这样转移会有遗漏。

显然可以将 $[k-a_k+1,k]\ (k>j)$ 和 $[j,j+a_j-1]\ (j+a_j-1\ge i)$ 染色，从而使 $[k-a_k+1,i]$ 被染色。

因此，在转移完 $f_i$ 还要考虑将 $[i,i+a_i-1]$ 染色后在 $i+1\sim i+a_i-1$ 中选择一个 $j$，将 $[j-a_j+1,j]$ 染色的最小代价。

具体转移详见代码。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[1005], f[1005];
int main() {
    cin >> t;

    while (t--) {
        memset(f, 0x3f, sizeof f);
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        f[0] = 0;

        for (int i = 1, k, minn; i <= n; i++) {
            for (int j = max(i - a[i] + 1, 0); j <= i; j++)
                f[i] = min(f[i], f[j - 1] + 1);

            for (int j = 1; j < i; j++)
                if (j + a[j] - 1 >= i)
                    f[i] = min(f[i], f[j - 1] + 1);

            k = i - 1, minn = f[i - 1];

            for (int j = i + 1; j <= min(i + a[i] - 1, n); j++) {
                while (k > max(j - a[j], 0))
                    minn = min(minn, f[--k]);

                f[j] = min(f[j], minn + 2);
            }
        }

        cout << f[n] << '\n';
    }

    return 0;
}
```

---

## 作者：快乐的大童 (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF1927G)

[cnblogs](https://www.cnblogs.com/dcytrl/p/18014075)

~~洛谷的无序列表排版貌似有点 bug~~

### 题意简述
你有 $n$ 个道具，对于第 $i$ 个道具，你可以选择覆盖 $[i-a_i+1,i]$ 或 $[i,i+a_i-1]$，或者什么都不做。

求覆盖所有 $1\sim n$ 所需要的道具的最小数目。

$n\le 100$。
### $O(n^3)$ 解法
首先明确一个事实：被一个或多个区间包含的区间，使用该区间对应的道具是没有用的。

设 $f_{i,l,r}$ 表示使用前 $i$ 个道具，最左端没覆盖到的点是 $l$，最右端覆盖到的点是 $r$ 的最小代价。

转移：

- 以下令 $lft_i=\max(i-a_i+1,1),rht_i=\min(n,i+a_i-1)$
- 若不使用：$f_{i-1,l,r}\rightarrow f_{i,l,r}$。
- 若使用左覆盖：
  - 若 $lft_i\le l$，则 $f_{i-1,l,r}+1\rightarrow f_{i,R+1,R},R=\max(i,r)$。
  
    - 解释：在之前的某个位置 $j(j<i)$ 使用右覆盖道具时已经将 $[j,r]$ 全部覆盖掉了，最左端未覆盖的点就是 $r+1$。而转移到 $R=\max(i,r)$ 的目的，是为了判掉 $r<i$ 的情况。
    
  - 否则，此次覆盖一定是没有用的，因为之后需要有 $lft_j\le l(j>i)$，此时 $[lft_j,j]$ 包含 $[lft_i,i]$。
  
- 若使用右覆盖：
  - 若 $rht_i\le r$，显然没用。
  
  - 若 $rht_i>r$：
  
    - 若 $l<i$，此时覆盖不会波及最左端没覆盖到的点，$f_{i-1,l,r}+1\rightarrow f_{i,l,rht}$
    
    - 否则，此次覆盖会将最左端没覆盖到的点也被覆盖，$f_{i-1,l,r}+1\rightarrow f_{i,rht+1,rht}$
    
      - 解释：由于 $l\le r$ 不一定满足（反例是当某前缀 $[1,k]$ 全部恰好覆盖完时，$l=k+1,r=k$），所以之前的某个位置 $j(j<i)$ 使用右覆盖道具时的覆盖区间 $[j,r]$ 不一定波及 $l$。

答案即为 $f_{n,n+1,n}$，足以通过本题。

[code](https://codeforces.com/contest/1927/submission/245419411)

### $O(n^2)$ 解法

~~以下解法仅代表个人理解，解释不一定正确，因为我太弱了想不到这种解法。~~

设 $f_{i,j}$ 为使用前 $i$ 种道具，覆盖了 $[1,j]$ 的最小代价。

首先转移显然有：
- 若使用左覆盖，且满足 $lft_i\le j+1,j<i$，则有 $f_{i-1,j}+1\rightarrow f_{i,i}$。
- 若使用右覆盖，且满足 $j\ge i-1,j<rht_i$，则有 $f_{i-1,j}+1\rightarrow f_{i,rht_i}$。

但也显然，这两种转移是无法表述 $j<i$，$j$ 使用右覆盖，$i$ 使用左覆盖的情况。

考虑再多一项转移：

当 $i$ 要使用左覆盖时，枚举 $j<i$ 要使用右覆盖，则有转移 $f_{i,rht_j}\leftarrow f_{j-1,lft_i-1}+2$。

有没有可能最优解需要三个及以上区间都相交？

实际上，在上述情况下，若插入第三个区间，在保证三个区间两两有交的前提下，要么第三个区间被原先两个区间的并所包含，要么原先的两个区间之一会被第三个区间和另外一个区间的并包含。而我们会枚举所有的 $j<i$，那么第三个区间的贡献也会被算上，因此无需插入第三个区间。


[code](https://codeforces.com/contest/1927/submission/245421229)

---

## 作者：EuphoricStar (赞：4)

看到 $n \le 100$ 考虑 $O(\text{poly}(n))$ dp。发现从左向右决策，因为一个点可以向左或向右覆盖，所以需要记最靠左的未覆盖的位置 $j$ 和最靠右的已覆盖位置 $k$，状态就是 $f_{i, j, k}$，dp 最小的覆盖次数。

转移的讨论很简单。考虑不覆盖还是向左或向右覆盖，若向左或向右覆盖看能否覆盖到 $j$ 或 $k$。这样转移是 $O(1)$ 的。总时间复杂度 $O(n^3)$。

[code](https://codeforces.com/contest/1927/submission/245282756)

---

## 作者：MaxBlazeResFire (赞：3)

div3？真不熟。

一个 naive 的思路是，记 $f_{i,j}$ 表示考虑前 $i$ 个涂色器，涂满前缀 $j$ 的最小操作次数。但是我们发现如果存在两个涂色器 $i<j$，最优情况下 $i$ 向后涂，$j$ 向前涂就寄了。

我们发现，如果要动用之后的涂色器向之前的格子涂，只用考虑最靠左的未涂色格子是否能被这个涂色器涂到。同时为了转移这个状态，新设计 $f_{i,j,k}$ 表示考虑前 $i$ 个涂色器，最左侧未被涂色的格子在 $j$，最右侧的已经被涂色的格子在 $k$ 时的最小操作次数。

转移用刷表比填表简单，枚举 $j,k$。

对于第 $i$ 个涂色器，如果不用，$f_{i-1,j,k}\rightarrow f_{i,j,k}$；

如果向左使用，范围到 $L$，当 $j<L$ 时，$f_{i-1,j,k}+1\rightarrow f_{i,j,\max\{k,i\}}$；否则贡献到 $f_{i,\max\{k,i\}+1,\max\{k,i\}}$；

如果向右使用，范围到 $R$，当 $j<i$ 时，$f_{i-1,j,k}+1\rightarrow f_{i,j,\max\{k,R\}}$，否则贡献到 $f_{i,\max\{j,R+1\},\max\{k,R\}}$。

复杂度 $O(\sum n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 105

const int INF = 1000000000;

//f[i][j] 表示考虑前 i 个涂色器，最靠左的没染色的位置在 j，最靠右的已染色位置在 k 的最小代价
int n,m,a[MAXN],f[MAXN][MAXN][MAXN];

inline void chkmin( int &x , int k ){ x = min( x , k ); }

inline void solve(){
	scanf("%lld",&n);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%lld",&a[i]);
	for( int i = 0 ; i <= n + 1 ; i ++ )
		for( int j = 0 ; j <= n + 1 ; j ++ )
			for( int k = 0 ; k <= n + 1 ; k ++ ) f[i][j][k] = INF;
	f[1][1][0] = 0,f[1][2][1] = f[1][a[1] + 1][a[1]] = 1;
	for( int i = 2 ; i <= n ; i ++ ){
		//不使用第 i 个涂色器
		for( int j = 0 ; j <= n + 1 ; j ++ )
			for( int k = 0 ; k <= n + 1 ; k ++ ) f[i][j][k] = f[i - 1][j][k];
		int L = max( 1ll , i - a[i] + 1 ),R = min( n , i + a[i] - 1 );
		//第 i 个涂色器向左涂色
		for( int j = 0 ; j <= n + 1 ; j ++ )
			for( int k = 0 ; k <= n + 1 ; k ++ )
				chkmin( f[i][j < L ? j : max( j , max( i + 1 , k + 1 ) )][max( k , i )] , f[i - 1][j][k] + 1 );
		//第 i 个涂色器向右涂色
		for( int j = 0 ; j <= n + 1 ; j ++ )
			for( int k = 0 ; k <= n + 1 ; k ++ )
				chkmin( f[i][j < i ? j : max( j , R + 1 )][max( k , R )] , f[i - 1][j][k] + 1 );
	}
	printf("%lld\n",f[n][n + 1][n]);
}

signed main(){
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：Z1qqurat (赞：1)

今年第一篇题解 qwq。

难绷，赛时由于 F 写假了一直在调没怎么想 G，赛后重做就自己切了，所以按照自己做题的心路历程来写。为了方便，下文记 $L_i=\max(1,i-a_i+1),R_i=\min(n,i+a_i-1)$。

进行一些观察，先不管可以往右染，我们就从左往右直接考虑每个 $i$ 的选择。由于 $a_i$ 没有单调性，容易发现我们在考虑 $i$ 的时候可能出现 $i$ 所在的某个往前连续段 $[j,i]$ 已经被染，但是在 $j$ 之前的某些段没有被染。但是我们容易发现，这样的未染段至多有一个，为什么呢？考虑到如果存在 $x<y$，我们都选择将它们往左染了，但是 $[L_x,x]\in[L_y,y]$，那么 $x$ 根本没有染的必要了。

![](https://pic.imgdb.cn/item/65c6f4f69f345e8d036ee7ac.jpg)

如果前面有两段没被染的独立段，那么之后一定要染一段大的 $[L_i,i]$ 整个染完才行，那么中间的隔开的就没必要染了。所以至多有一段这样的。

接下来我们考虑往右染，其实更简单，由于我们从小到大考虑 $i$，所以 $i$ 之后的未被染段一定是一个连续区间 $[p,n]$ 的形式。

最优化，考虑 dp 求解。设 $f_{l,r,p}$ 表示 $1\sim i$ 中那个未被染段是 $[l,r]$，$i+1\sim n$ 中那个未被染段是 $[p,n]$。那么转移的时候仔细考虑边界，分 $i$ 往左，往右，不染三种情况，刷表法转移即可（由于这里不用动太多脑子所以不再赘述）。

转移的时候容易发现，$r$ 对转移根本没有影响，所以变成 $f_{l,p}$ 就行了，转移复杂度 $\mathcal{O}(n^3)$，空间复杂度 $\mathcal{O}(n^2)$（$f$ 只有两维实际上是把 $i$ 这一维滚掉了）。

只要想清楚了代码写起来很容易的！[Submission.](https://codeforces.com/contest/1927/submission/245660919)

---

## 作者：__vector__ (赞：1)

距离上次赛时 AC 提交被 hack 过去了近 1.5 年，写篇题解纪念一下。~~分类讨论漏了一种情况都能过 pretests，难怪最终只过了这么点人。~~  
在此感谢 [160cm 对我赛时代码的 hack 数据](https://codeforces.com/contest/1927/hacks/980339)，帮我找出我的错误。  
### 大概思路   
相信很多人读完题就能想到用 dp。  
由于有 $n$ 个格子从左到右，每个格子分别决策，所以初步设想使用 $dp_i$ 代表假如以 $i$ 结尾（换句话说，$n=i$），答案是多少。   

那么转移则从 $1$ 到 $n$ 枚举 $i$，然后从 $[0,i-1]$ 依次枚举 $j$，计算从 $dp_j$ 转移到 $dp_i$ 的答案。   

这里有一个致命的问题，因为即使是最优方案下解决前 $i$ 个，但前 $i$ 个格子的涂色有可能延伸到 $i+1$ 或以后，而刚才设计的状态无法考虑此情况，从而导致答案算大。   

另外，是否可以将状态更改为 $dp_i$ 表示答案？这里进行一些分析。前 $i$ 个涂满的考虑到每个格子只能决策一次，转移的时候（假设当前计算 $n = i$ 的答案，从第 $n = j$ 的答案转移），新操作的格子只能在 $[j+1,i]$ 选择，而这样既需要考虑最多前多少个格子可能被操作过，也需要考虑实际覆盖了前多少个格子。而本段开头设计的状态不能表示最多前多少个格子可能被操作过，所以是错误的。    

另外如果有大佬设计了一维状态的 dp，请评论区回复。  

最后，我设计的状态是 $dp_{i,j}$ 代表 $n=i$（即最多只操作前 $i$ 个格子），覆盖了前 $j$ 个格子的最小操作次数。  

转移方法（**以下方程默认等于号的实际作用是 checkmin**）：  

- 第 $i$ 个向左涂：  
	$dp_{i,\max(y,i)} = \min(dp_{k,y})$，注意 $k \lt i,y \ge i-a_i$  
- 第 $i$ 个向右涂：  
	$dp_{i,\max(y,\min(n,i+a_i-1))} = \min(dp_{k,y})$，注意 $k \lt i,y \ge i-1$  
- 第 $i$ 个不涂：  
	$dp_{i,y} = \min(dp_{k,y})$，注意 $k \lt i,y \ge i$  

还有一种特殊情况，在样例的 testcase11 中可以看见。  
这种情况就是 $a_i \ge i$，此时可以这样转移：  
$dp_{i,\min(n,k+a_k-1)} = 2$，注意 $k  \lt i$

此时好像可以结束了？  

如果你是这场比赛的选手，并且是 rated，那么这将是一个沉痛的教训（~~对不起我赛前临时改成了 unrated~~），因为这里漏掉了一种 pretests 中没有出现的情况。  

注意，对于当前需要求解的 $dp_{i,j}$，不仅可以从 $dp_{k \lt i,y \in [1,n]}$ 等第一维小于 $i$ 的状态转移，还有可能从 $dp_{i,l \lt j}$ 通过选择一个位置在 $[j+1,i-1]$ 的格子向后涂色得到。  

[最后我的解决方案](https://codeforces.com/contest/1927/submission/245540356)。  


---

## 作者：Zemu_Ooo (赞：0)

赛场上难倒我班上众多英雄汉的题目。当然，A 了 G 这道题是我 AK Div.3 的重要一环（

简述：给定的是一系列涂料的大小，这些涂料可以向左或向右使用，或者根本不使用，每种涂料最多只能使用一次。目标是最小化使用涂料的次数，以便覆盖整个单行格子。

我们简单地把状态定义为 $f[i][j][k]$，用于存储到目前为止最少使用的涂料次数。其中：

$i$ 代表当前考虑到的格子编号（从 $1$ 开始）。

$j$ 代表下一个可以向左使用涂料覆盖到的格子编号，如果没有这样的格子，则为 $i+1$。

$k$ 表示当前已经覆盖到的最右边的格子编号。

转移规则是这样：

 如果涂料向右使用，更新状态 

$$f[i + 1][i + 2][\min(n, \max(k, i + 1 + a[i + 1] - 1))]$$

，次数加 $1$。


如果当前涂料不使用，转移到 

$$f[i + 1][i + 1 + (k \geq (i + 1))][k]$$
，使用次数不变。

如果涂料向左使用，需要判断是否能够覆盖到j指向的格子。

如果可以，更新状态 

$$f[i + 1][i + 2][\min(n, \max(k, i + 1))]$$

，次数加 $1$。

否则，转移到 

$$f[i + 1][j][\min(n, \max(k, i + 1))]$$

，同样次数加 $1$。

最后通过遍历 $f[n][n + 1][n]$ 得到最终答案。

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <ctime>
#include <bitset>
using namespace std;
// #define int double
#define lb(x) ((x) & (-x))
 #define int long long
// #define ll long long
#define lo long long
#define double long double
#define ff first
#define ss second
#define mr make_pair
#define l(x) T[x].l 
#define r(x) T[x].r 
#define lz(x) t[x].lz
const int mod = 998244353 ;
const int dlt = 1e6 + 2 ;
int read() {
    char ch ;int s = 0 ;int w = 1;
    while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
    while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
    return s * w ;
}
void print(int x) {
    if(x < 0) putchar('-'), x = -x ;                  
    if(x > 9)print(x / 10) ;
    putchar(x % 10 + '0') ;
}                     
void prn(int x) {      
    print(x) ;                                          
    putchar('\n') ;            
} 
int pows(int x, int k) {
    int bace = x%mod, ans = 1 ;
    while(k) {
        if(k & 1) ans *= bace, ans %= mod ;
        bace *= bace ;bace %= mod ;
        k >>= 1 ;
    }
    return ans ;
}
void cmax(auto &a, auto b) {
    a = max(a, b) ;
}
void cmin(auto &a, auto b) {
    a = min(a, b) ;
}
int TT ;
int n, k ;
int m, q ;
string s ;
int f[105][105][105] ;
int a[105] ;
void work() {
    n = read() ;
    for(int i = 1 ; i <= n ; i++) {
        a[i] = read() ;
    }
    memset(f, 0x3f, sizeof(f)) ;
    f[1][2][min(n, a[1])] = 1 ;
    f[1][2][1] = 1 ;
    f[1][1][0] = 0 ;
    for(int i = 1 ; i < n ; i++) {
        for(int j = 1 ; j <= i + 1 ; j++) {
            for(int k = 0 ; k <= n ; k++) {
                if(j == i + 1) {
                    cmin(f[i + 1][i + 2][min(n, max(k, i + 1 + a[i + 1] - 1))], f[i][j][k] + 1) ;
                    cmin(f[i + 1][i + 1 + (k >= (i + 1))][k], f[i][j][k]) ;
                }
                else {
                    if(max(1ll, i + 1 - a[i + 1] + 1) <= j) {
                        cmin(f[i + 1][i + 2][min(n, max(k, i + 1))], f[i][j][k] + 1) ;
                        // cout << "?" << i << ' ' << j << ' ' << k << endl ;
                    }
                    else {
                        cmin(f[i + 1][j][min(n, max(k, i + 1))], f[i][j][k] + 1) ;
                    }
                    cmin(f[i + 1][j][min(n, max(k, i + 1 + a[i + 1] - 1))], f[i][j][k] + 1) ;
                    cmin(f[i + 1][j][k], f[i][j][k]) ;
                }
            }
        }
    }
    int ans = 1e9 ;
    cmin(ans, f[n][n + 1][n]) ;
    cout << ans << endl ;
}   
signed main() {
    TT = read() ;
    while(TT--) {

        work() ;
    }

    return 0 ;
}
```

---

