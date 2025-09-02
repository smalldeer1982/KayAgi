# Double Elimination

## 题目描述

The biggest event of the year – Cota 2 world championship "The Innernational" is right around the corner. $ 2^n $ teams will compete in a double-elimination format (please, carefully read problem statement even if you know what is it) to identify the champion.

Teams are numbered from $ 1 $ to $ 2^n $ and will play games one-on-one. All teams start in the upper bracket.

All upper bracket matches will be held played between teams that haven't lost any games yet. Teams are split into games by team numbers. Game winner advances in the next round of upper bracket, losers drop into the lower bracket.

Lower bracket starts with $ 2^{n-1} $ teams that lost the first upper bracket game. Each lower bracket round consists of two games. In the first game of a round $ 2^k $ teams play a game with each other (teams are split into games by team numbers). $ 2^{k-1} $ loosing teams are eliminated from the championship, $ 2^{k-1} $ winning teams are playing $ 2^{k-1} $ teams that got eliminated in this round of upper bracket (again, teams are split into games by team numbers). As a result of each round both upper and lower bracket have $ 2^{k-1} $ teams remaining. See example notes for better understanding.

Single remaining team of upper bracket plays with single remaining team of lower bracket in grand-finals to identify championship winner.

You are a fan of teams with numbers $ a_1, a_2, ..., a_k $ . You want the championship to have as many games with your favourite teams as possible. Luckily, you can affect results of every championship game the way you want. What's maximal possible number of championship games that include teams you're fan of?

## 说明/提示

On the image, each game of the championship is denoted with an English letter ( $ a $ to $ n $ ). Winner of game $ i $ is denoted as $ Wi $ , loser is denoted as $ Li $ . Teams you're a fan of are highlighted with red background.

In the first example, team $ 6 $ will play in 6 games if it looses the first upper bracket game (game $ c $ ) and wins all lower bracket games (games $ h, j, l, m $ ).

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1310B/9ee2bb4deee8b324336a21a0835a043711b7ea68.png)In the second example, teams $ 7 $ and $ 8 $ have to play with each other in the first game of upper bracket (game $ d $ ). Team $ 8 $ can win all remaining games in upper bracket, when teams $ 1 $ and $ 7 $ will compete in the lower bracket.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1310B/3e96a3072cf58c9d1765796c239254696af4a375.png)In the third example, your favourite teams can play in all games of the championship.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1310B/f343fb6ded3df4fb4c1fe8856c248b5ed43eed75.png)

## 样例 #1

### 输入

```
3 1
6```

### 输出

```
6```

## 样例 #2

### 输入

```
3 3
1 7 8```

### 输出

```
11```

## 样例 #3

### 输入

```
3 4
1 3 5 7```

### 输出

```
14```

# 题解

## 作者：yijan (赞：3)

推荐在 luogu 博客或者 [这里](https://www.yijan.co/cf1310b/) 查看

$dp[i][j][0/1][0/1]$ 表示当前在第 $i$ 轮，进行到了第 $j$ 场（我们把失败组的比赛和失败组胜利者与胜利组失败者的比赛压缩到一场），这一场打完了你是否是胜利者的粉丝，是否是失败者的粉丝。

然后发现这是一个类似线段树的结构，如果从 $0$ 编号，第 $i$ 轮的第 $j$ 场会由 $i-1$ 轮的 $2j,2j+1$ 转移过来。

如果是一个队的粉丝，那么显然我们会贪心地让这个队伍存活下去，不会出现一个非粉丝的队伍在失败组淘汰掉一个粉丝的队伍。因此我们不需要关心作为粉丝的队伍的数量，只需要关心是否存在。

转移，失败者里如果有粉丝队伍，那么打完后失败者一定还粉丝队伍，胜利者里有粉丝队伍，要么它维持是个粉丝的状况，要么从胜利者变成失败者。

---

upd：讨论貌似有人说看不太懂，更新了一下

每场比赛必然会剩下一个胜利者和一个失败者。我们考虑按照我题解写的设dp，对于第 i 轮 的 第 j 场，考虑上一轮的第 j<<1,j<<1|1 这两场比赛，会剩一对胜利者和一对失败者。

这个时候会进行三局比赛，并且通过三局比赛决定出胜利和失败者，于是把这三局比赛捆绑到一起计算。

考虑转移，由于我们希望作为粉丝的队伍参加的比赛尽量多。设1表示作为粉丝，0表示并不。于是我们要么会让1的队伍作为胜利者继续存在于胜利组，让较小的失败。还有一种决策是让胜利者的比赛中一个作为粉丝的队伍进入败者组，然后在败者组中必然可以获取一次胜利。具体实现可以参考代码。

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "list"
#include "queue"
using namespace std;
#define MAXN 400006
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
int n , k;
int A[MAXN] , w[MAXN];
int dp[18][1 << 18][2][2];

inline void chkmx( int& x , int y ) {
    x = ( x > y ? x : y );
}

void solve() {
    cin >> n >> k;
    rep( i , 1 , k ) scanf("%d",A + i) , -- A[i] , w[A[i]] = 1;
    memset( dp , -0x3f , sizeof dp );
    rep( i , 0 , ( 1 << n - 1 ) - 1 ) {
        dp[1][i][w[i << 1]][w[i << 1 | 1]] = w[i << 1] | w[i << 1 | 1];
        dp[1][i][w[i << 1 | 1]][w[i << 1]] = w[i << 1] | w[i << 1 | 1];
    }
    int s , t;
    rep( i , 2 , n ) {
        s = ( 1 << n - i ) - 1;
        rep( j , 0 , s )
        rep( wl , 0 , 1 ) rep( dl , 0 , 1 ) rep( wr , 0 , 1 ) rep( dr , 0 , 1 ) {
            t = dp[i - 1][j << 1][wl][dl] + dp[i - 1][j << 1 | 1][wr][dr];
            chkmx( dp[i][j][wl | wr][dl | dr] , t + ( ( dl | dr ) << 1 ) + ( wl | wr ) );
            if( wl | wr ) chkmx( dp[i][j][wl + wr - 1][1] , t + ( dl | dr ) + ( wl | wr ) + 1 );
        }
    }
    int mx = 0;
    rep( wl , 0 , 1 ) rep( dl , 0 , 1 ) chkmx( mx , dp[n][0][wl][dl] + ( wl | dl ) );
    cout << mx << endl;
}

signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
```



---

## 作者：jhdonghj (赞：2)

# CF1314B解题报告

这是个妙题

刚开始想写贪心然后发现考虑条件太多了。。。然后咕咕咕

## 题目大意

$2^n$个人比赛，你可以决定每场比赛胜负，每场胜者组比赛胜者进胜者组，败者进败者组；败者组胜者与胜者组败者比赛，胜者继续，否则淘汰。

其中有$k$个人是你喜欢的，你要让有他们的比赛最多，求最多比赛数

## 题解

发现对于一段区间来说，我们只关心这段区间最后的胜者和败者，于是考虑$DP$，$f[l\dots r][0/1][0/1]$表示$[l\dots r]$中最终胜者是否喜欢，败者是否喜欢下的最多比赛场数。
$$
\begin{aligned}
	init:f[2k\dots 2k+1][0][0]&=0\\
	       f[2k\dots 2k+1][0][1]&=1\quad if \ like\ 2k\ or\ 2k+1\\
	       f[2k\dots 2k+1][1][0]&=1\quad if \ like\ 2k\ or\ 2k+1\\
	       f[2k\dots 2k+1][1][1]&=2\quad if\ like\ 2k\ ans\ 2k+1\\
\end{aligned}
$$
转移时只需分类讨论考虑情况即可

我们将比赛过程看成一个二叉树，那么我们就可以用二叉树的先序遍历方便地标号比赛，又注意到后两维可以压缩为一个$[0,3]$之间的数字

于是新$DP$转移方程如下
$$
f[i][x|y]=max(f[i][x|y],f[2i][x]+f[2i+1][y]+(x|y))
$$
最后答案$Ans=max(f[1][1]+1,f[1][2]+1,f[1][3]+1,0)$，其中的$+1$是最后一场比赛的$+1$。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k, bit, inf = 1e9;
	scanf("%d %d", &n, &k);
	bit = 1 << n - 1;
	vector<vector<int>> f(bit * 2, {0, -inf, -inf, -inf});
	for(int i = 1; i <= k; i++) {
		int a; scanf("%d", &a);
		a = bit + (a - 1) / 2;
		f[a][3] = f[a][1]; f[a][1] = f[a][2] = 1;
	}
	for(int i = bit - 1; i > 0; i--)
		for(int x = 0; x < 4; x++)
			for(int y = 0; y < 4; y++)
				f[i][x | y] = max(f[i][x | y], f[2 * i][x] + f[2 * i + 1][y] + (x | y));
	printf("%d\n", max({f[1][1], f[1][2], f[1][3], -1}) + 1);
	return 0;
}
```



---

## 作者：daniEl_lElE (赞：0)

考虑 $dp_{i,j,0/1,0/1}$ 表示目前第 $i$ 层，第 $(j-1)\times2^i\sim(j\times2^i-1)$ 个人决出了 $2$ 个赢家（一个没输过，一个输过一次）且分别是/不是粉丝队伍时，粉丝队伍至多参加多少场比赛。

考虑转移，我们只需要 $dp_{i,j,0/1,0/1},dp_{i,j+1,0/1,0/1}\to dp_{i+1,\frac j 2,0/1,0/1}$。

分别枚举两边的 $0/1$ 状态与发生的三场比赛中胜负情况即可。

总复杂度 $O(2^n\times n)$，常数比较大（枚举 $0/1$）。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int dp[18][131072][2][2];
int a[131072];
signed main(){
	memset(dp,-1,sizeof(dp));
	int n,k; cin>>n>>k;
	for(int i=1;i<=k;i++){
		int p; cin>>p;
		p--;
		a[p]=1;
	}
	for(int i=0;i<(1<<n);i+=2){
		dp[1][i][a[i]][a[i+1]]=a[i]|a[i+1];
		dp[1][i][a[i+1]][a[i]]=a[i]|a[i+1];
	}
	for(int j=2;j<=n;j++){
		for(int k=0;k<(1<<n);k+=(1<<j)){
			int l=k+(1<<(j-1));
			for(int q1=0;q1<=1;q1++){
				for(int q2=0;q2<=1;q2++){
					for(int p1=0;p1<=1;p1++){
						for(int p2=0;p2<=1;p2++){
							if(dp[j-1][k][q1][q2]==-1||dp[j-1][l][p1][p2]==-1) continue;
							for(int w1=0;w1<=1;w1++){
								for(int w2=0;w2<=1;w2++){
									for(int w3=0;w3<=1;w3++){
										int e1,e2,e3,ex=0;
										if(q1|p1) ex++;
										e1=w1?q1:p1;
										e2=w1?p1:q1;
										if(q2|p2) ex++;
										e3=w2?q2:p2;
										if(e2|e3) ex++;
										e2=w3?e2:e3;
										dp[j][k][e1][e2]=max(dp[j][k][e1][e2],dp[j-1][k][q1][q2]+dp[j-1][l][p1][p2]+ex);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout<<max(max(dp[n][0][0][0]-1,dp[n][0][0][1]),max(dp[n][0][1][0],dp[n][0][1][1]))+1;
	return 0;
}
```

---

## 作者：zhylj (赞：0)

**为了更好的阅读体验，你可以前往我的博客：[链接](http://zhylj.cc/2020/02/26/33/#more)**

注意到我们并不关心某场比赛是谁参加的，只关心这场比赛有没有我们喜欢的队伍参赛：（下面把所有队伍编号减一方便处理）

设 $f(l,r,0/1,0/1)$ 代表区间 $[l,r)$（$l,r$ 形如 $a\cdot 2^t, (a+1)\cdot 2^t$，即这段区间都会在第 $t$ 场参加比赛）内，最后一场比赛胜者组的胜者是不是我们喜欢的队伍/败者组的胜者是不是我们喜欢的队伍，这段区间内的答案。

使用记忆化搜索，实现时可能有些细节。

```cpp
#include <bits/stdc++.h>

typedef std::pair<int, int> pii;

const int kN = 18;
const int kT = 1 << kN;
const int kInf = 0x3f3f3f3f;

int a[kT]; bool fan_of[kT]; std::map<pii, int> cal[4];
int Cal(int l, int r, int st) {
    if(r == l + 2) {
        int cnt_fan = (int)fan_of[l] + fan_of[l + 1], cnt_st = (st & 1) + (st >> 1);
        return cnt_fan == cnt_st ? std::min(cnt_st, 1) : -kInf;
    }
    pii tmp = std::make_pair(l, r);
    if(cal[st].count(tmp)) return cal[st][tmp];
    int mid = (l + r) >> 1, ret = -kInf;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j) {
            int v1 = ((i << 1) | (i & 2) | j) & 3, v2 = ((j << 1) | (j & 2) | i) & 3;
            if(v1 == st || v2 == st)
                ret = std::max(ret, Cal(l, mid, i) + Cal(mid, r, j));
        }
    return cal[st][tmp] = ret + st;
}

int main() {
    int n, k, t, ans = 0;
    scanf("%d%d", &n, &k); t = 1 << n;
    for(int i = 1; i <= k; ++i) scanf("%d", a + i), fan_of[--a[i]] = true;
    for(int i = 0; i < 4; ++i) ans = std::max(ans, Cal(0, t, i));
    printf("%d", ans + !(!k));
    return 0;
}
```

---

