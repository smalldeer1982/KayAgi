# Railguns

## 题目描述

Tema is playing a very interesting computer game.

During the next mission, Tema's character found himself on an unfamiliar planet. Unlike Earth, this planet is flat and can be represented as an $ n \times m $ rectangle.

Tema's character is located at the point with coordinates $ (0, 0) $ . In order to successfully complete the mission, he needs to reach the point with coordinates $ (n, m) $ alive.

Let the character of the computer game be located at the coordinate $ (i, j) $ . Every second, starting from the first, Tema can:

- either use vertical hyperjump technology, after which his character will end up at coordinate $ (i + 1, j) $ at the end of the second;
- or use horizontal hyperjump technology, after which his character will end up at coordinate $ (i, j + 1) $ at the end of the second;
- or Tema can choose not to make a hyperjump, in which case his character will not move during this second;

The aliens that inhabit this planet are very dangerous and hostile. Therefore, they will shoot from their railguns $ r $ times.

Each shot completely penetrates one coordinate vertically or horizontally. If the character is in the line of its impact at the time of the shot (at the end of the second), he dies.

Since Tema looked at the game's source code, he knows complete information about each shot — the time, the penetrated coordinate, and the direction of the shot.

What is the minimum time for the character to reach the desired point? If he is doomed to die and cannot reach the point with coordinates $ (n, m) $ , output $ -1 $ .

## 说明/提示

In the first test case, the character can move as follows: $ (0, 0) \rightarrow (0, 1) \rightarrow (0, 2) \rightarrow (0, 3) \rightarrow (0, 3) \rightarrow (1, 3) $ .

In the second test case, the character will not be able to leave the rectangle that will be completely penetrated by shots at the second $ 2 $ .

## 样例 #1

### 输入

```
5
1 3
4
1 2 0
2 2 1
3 2 2
4 1 1
3 3
6
2 1 0
2 1 1
2 1 2
2 2 0
2 2 1
2 2 2
2 1
3
7 1 2
2 1 1
7 2 1
2 2
5
9 1 2
3 2 0
5 1 2
4 2 2
7 1 0
4 6
7
6 1 2
12 1 3
4 1 0
17 2 3
1 2 6
16 2 6
3 2 4```

### 输出

```
5
-1
3
6
10```

# 题解

## 作者：Lucky_Xiang (赞：6)

# 题目

[CF1840F](https://www.luogu.com.cn/problem/CF1840F) 

# 思路

首先，答案一定不超过 $n+m+r$，因为最坏情况是被每一道激光拦住一次。

可以考虑 dp，$dp_{i,j,t}$ 表示在 $t$ 时刻能否到达 $i$ 行 $j$ 列，则 $dp_{i,j,t}=dp_{i,j,t-1}| dp_{i-1,j,t-1}|dp_{i,j-1,t-1}$，这种做法时间、空间复杂度均为 $O(n^2m^2)$，有一些极限，交上去果然因为数组开太大 [RE](https://codeforces.com/contest/1840/submission/209049686) 了。

那么我们就可以参考 [P1541 乌龟棋](https://www.luogu.com.cn/problem/P1541) 的思路，压缩数组的大小。假设停留的时间为 $p(p\le r)$，则 $t=i+j+p$，因此新的状态 $dp_{i,j,p}$ 表示能否停留 $p$ 次到达 $i$ 行 $j$ 列，$dp_{i,j,p}=dp_{i-1,j,p}| dp_{i,j-1,p}|dp_{i,j,p-1}$，时空复杂度为 $O(nmr)$，就能够 [AC](https://codeforces.com/contest/1840/submission/209050873) 了。

---

## 作者：氷の妖怪Cirno (赞：5)

### 题目分析

大概分析一下可知，可到达的最坏情况必定被每道激光都拦截一下，所以耗时 $n + m + r$ 秒。因此，可以枚举时间，看在当前时间 $t$ 下能到达哪些坐标。设 $dp_{i,j,k}$ 表示在第 $k$ 秒时能否到达坐标 $(i,j)$，$1$ 表示能到，$0$ 表示不能到。

状态转移方程如下：
$$dp_{i,j,k} = dp_{i-1,j,k-1} | dp_{i,j-1,k-1} | dp_{i,j,k}$$
观察发现，第三个维度可以被压缩掉，用倒序遍历或滚动数组都行。代码实现时用主动递推可能更好写。

接下来考虑怎么处理射击。如果这样设计状态就比较好处理了，每一秒都对所有坐标 dp 一次，dp 完后如果这一秒有射击操作，直接将对应的横行或竖列的所有 $dp_{i,j,k}$ 设为 $0$ 即可。如果在第 $k$ 秒的遍历中，所有的 $dp_{i,j,k}$ 都等于 $0$ 那么之后就不可能出现 $1$ 的状态了，输出 $-1$。但如果在第 $t$ 秒 $dp_{n,m,t} = 1$，输出 $t$ 即为最小答案。

### code：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct Shoot
{
	int t, d, cd;
} a[105];
bool cmp(Shoot x, Shoot y)
{
	return x.t < y.t;
}
bool f[10005][10005];//这里开 int 会爆空间
int n, m, r;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n >> m >> r;
		for (int i = 1; i <= r; i++)
		{
			cin >> a[i].t >> a[i].d >> a[i].cd;
		}
		sort(a+1, a+r+1, cmp);
		for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) f[i][j] = 0;
		f[0][0] = 1; int k = 1;
		for(int t = 1; t; t++)
		{
			bool flag = 0;
			for (int i = n; i >= 0; i--)
			{
				for (int j = m; j >= 0; j--)
				{
					if (f[i][j] == 0) continue;
					flag = 1;
					f[i+1][j] = f[i][j+1] = 1;
				}
			}
			//cout << t << ' ' << f[0][1] << endl;
			if (!flag)
			{
				cout << -1 << '\n'; break;
			}
			while(k <= r && a[k].t == t)
			{
				if (a[k].d == 1)
				{
					for (int i = 0; i <= m; i++) f[a[k].cd][i] = 0;
				}
				else
				{
					for (int j = 0; j <= n; j++) f[j][a[k].cd] = 0;
				}
				k++;
			}
			if (f[n][m] != 0)
			{
				cout << t << '\n';
				break;
			}
		}
	}return 0;
}
```


---

## 作者：Hiiragi_Utena (赞：2)

> ~~你指尖跃动的电光，是我此生不变的信仰，唯我……~~

啊不对，放错了。

---

这题有一个结论：如果可行，总时间不超过 $n+m+r$。可惜笔者很菜不会证，官方题解中也没有证明。**不过本篇题解不需要用到这个结论！**

显然可以先将射击按时间排序，将相同时间的一起处理。每次处理时，假设上一步的时间为 $t_1$，上一次处理之后的地图为一个 0/1 二维数组 $p$（$p_{i,j}$ 为 $1$ 代表这个位置可以到达，为 $0$ 代表到达不了），这一次的处理时间为 $t_2$，处理之后的地图（即本次的所求）为 $g$。

假设存在 $i,j$，使 $p_{i,j}=1$ 且 $(n-i)+(m-j)<t_2-t_1$，即在上次射击之后的 $(i,j)$ 这个点可以在这次射击之前（不含）就到终点。那么暴力找出满足条件且 $(n-i)+(m-j)$ 最小的 $i,j$，答案即为 $t_1+(n-i)+(m-j)$。

否则，在这个时间之前（不含）必然到不了终点。

注意：上面这一步需要在所有射击都处理完后再做一次。因为有可能所有在最后一次射击所在时间及其之后到达终点。

那么就需要先求出到这个时间并且假设不射击时的地图 $g'$。

构造辅助 $dp$ 数组：

$$dp_{i,j}=\max\{dp_{i-1,j}-1,dp_{i,j-1}-1,p_{i,j}\times(t_2-t_1+1)\}$$

其中若 $dp_{i,j}>0$，则代表这个点最早会在 $t_2+1-dp_{i,j}$ 这个时间到达；若 $dp_{i,j}=0$ 则代表这个点不能在 $t_2$ 之前（含）到达。

则：

$$g'_{i,j}=\begin{cases}0\ \ \ \ \ dp_{i,j}=0\\1\ \ \ \ \ dp_{i,j}>0\end{cases}$$

那么对于 $g$，只用把这回合会被~~超~~电磁炮打到的地方设为 $0$，其它地方设为 $g'_{i,j}$ 即可。

---

upd 2023/6/10：之前写的有点细节上的小问题。改完重交。

---

## 作者：_Sheepsheep (赞：1)

# Codeforces Round 878 (Div. 3) F. Railguns

- ## 题意


>Tema 在 $n·m$ 的网格内要从 $(0,0)$ 走到 $(n,m)$。第 $0$ 秒末 Tema 位于 $(0,0)$。

>假设 Tema 正位于 $(i,j)$ 每秒他可以做三种行动：	

>①该秒末移动到 $(i+1,j)$；

>②该秒末移动到 $(i,j+1)$；

>③该秒末停留在 $(i,j)$。

>机器人会发射 $r$ 次激光炮以阻挠他前进，具体为在第 $t$ 秒，向第 $x$ 行或第 $x$ 列发射激光炮，一整列或一整行都会受到炮击。若 Tema 在第 $t$ 秒末还停留在被炮击的单元格内则会被击毁。求 Tema 从 $(0,0)$ 到达 $(n,m)$ 的最短时间，若无法抵达则输出 $-1$。

>$r$ 次炮击格式为 $t$，$d$，$coord$：$t$ 表示炮击发生的时间；$d$ 表示炮击方式：$d=1$ 时攻击一整行，$d=2$ 时攻击一整列；$coord$ 表示攻击的是具体哪一行或列。

- ## 分析 


Tema 在 $(i,j)$ 处会出现的时间在 $[i+j,i+j+r]$ 范围内。

如下情况，Tema 在 $(1,1)$ 处出现的时间取到最大值 $i+j+r$。


![](https://cdn.luogu.com.cn/upload/image_hosting/c53q9ug6.png?x-oss-process=image)


所以，设 $dp[i][j][k]$ 表示 Tema 在时间 $i+j+k$ 时能否到达 $(i,j)$。

有转移方程
$$\begin{cases}dp[i][j][k]=dp[i-1][j][k]|dp[i][j][k]&&i>0\\dp[i][j][k]=dp[i][j-1][k]|dp[i][j][k]&&j>0\\dp[i][j][k]=dp[i][j][k-1]|dp[i][j][k]\end{cases}$$

其中第三条转移方程要求第 $i$ 行和第 $j$ 列在 $i+j+k$ 这个时间没有被炮击。

检查某个时间某行或列是否被炮击，用 set 维护每行或列被炮击的时间然后二分查找即可。

- ## 代码

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define ll long long
#define double long double
const ll N = 1e6+9 ;
const ll INF = 1e17 ;
const ll mod = 1e9+7 ;
//const double pi = acos(-1) ;
const double eps = 1e-7 ;
ll gcd( ll a , ll b ){ return a == 0 ? b : gcd( b%a , a ) ; }
ll lcm( ll a , ll b ){ return (a/gcd(a,b))*b ; }
ll Abs( ll x ){ return x < 0 ? -x : x ; }
ll n , m , r ;
void solve(){
    cin >> n >> m >> r ;
    vector<set<ll>>a(n+1),b(m+1) ;
    vector<vector<vector<bool>>>dp(n+1,vector<vector<bool>>(m+1,vector<bool>(r+10,0))) ;
    for( int i = 1 ; i <= r ; i ++ ){
        ll t , d , pos ; cin >> t >> d >> pos ;
        if( d == 2 ) b[pos].insert(t) ;
        if( d == 1 ) a[pos].insert(t) ;
    }

    ll up = min( ( a[0].lower_bound(0+1) == a[0].end() ? r+1 : *a[0].lower_bound(0+1) ) ,
                 ( b[0].lower_bound(0+1) == b[0].end() ? r+1 : *b[0].lower_bound(0+1) )
                ) ;
    //up:大于等于该时间点被炮击的时间，若不存在则取r+1

    for( int i = 0 ; i <= up ; i ++ ) dp[0][0][i] = 1 ;

    for( int i = 0 ; i <= n ; i ++ )
        for( int j = 0 ; j <= m ; j ++ )
            for( int k = 0 ; k <= r ; k ++ ){

                up = min( ( a[i].lower_bound(i+j+k) == a[i].end() ? r+1 : *a[i].lower_bound(i+j+k)-i-j ) ,
                          ( b[j].lower_bound(i+j+k) == b[j].end() ? r+1 : *b[j].lower_bound(i+j+k)-i-j )
                        ) ;

                if( up == k ) dp[i][j][k] = 0 ;
                else{
                    if( i > 0 ) dp[i][j][k] = dp[i][j][k] | dp[i-1][j][k] ;
                    if( j > 0 ) dp[i][j][k] = dp[i][j][k] | dp[i][j-1][k] ;
                    if( k > 0 ) dp[i][j][k] = dp[i][j][k] | dp[i][j][k-1] ;
                }
    }

    for( int i = 0 ; i <= r ; i++ ) if( dp[n][m][i] ){
        cout << n+m+i << "\n" ; return ;
    }
    cout << "-1\n" ; return ;
}
int main(){
    ios::sync_with_stdio(false) ; cin.tie(0) ; cout.tie(0) ;
    ll tt = 1 ; cin >> tt ;
    while( tt-- ) solve() ;
    return 0 ;
}

```



---

## 作者：the_Short_Path (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1840F)

~~这题是蓝题？挺水的~~

首先，应该没有人去跑 dfs 吧？~~（我比赛时干的）~~

这题是棋盘 dp，用 $dp_{i,j,k}$ 表示第 $k$ 秒从 $(0,0)$ 到达 $(i,j)$ 的最小距离，但要处理炮击（即设置第 $k$ 秒所有被炮击的 $dp_{i,j,k}=-1$）。

但是用 `int` 内存会炸掉，需要约 $381MB$ 的空间，~~但是题目给的不够~~。

所以可以压缩状态，把 `int` 换成 `bool`，判断是否能到达，用 $dp_{i,j,k}$ 表示第 $k$ 秒能否到达 $(i,j)$，转移方程为：
$$dp_{i,j,k}=dp_{i-1,j,k-1}|dp_{i,j-1,k-1}|dp_{i,j,k}$$
再加上滚动数组和倒序遍历：
$$dp_{i,j}=dp_{i-1,j}|dp_{i,j-1}|dp_{i,j}$$
最后枚举时间 $k$，若第 $k$ 秒 $dp_{n,m}=0$，则 $k$ 为答案。注意特判如果 $\forall dp_{i,j}=0$，则输出 $-1$。
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node {
    int t, d, coord;
} a[105];
bool cmp(node x, node y) {
    return x.t < y.t;
}
bool dp[10005][10005];
int n, m, r;
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);// 输入输出优化
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> r;
        for (int i = 1; i <= r; i++) cin >> a[i].t >> a[i].d >> a[i].coord;
        sort(a + 1, a + r + 1, cmp);
        // 初始化
        for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) dp[i][j] = 0;
        dp[0][0] = 1;
        int cnt = 1;
        for (int ti = 1; ; ti++) {
            bool f = 0;
            for (int i = n; i >= 0; i--) {
                for (int j = m; j >= 0; j--) {
                    if (!dp[i][j]) continue;
                    f = dp[i + 1][j] = dp[i][j + 1] = 1;
                }
            }
            if (!f) {
                cout << "-1\n";// 特判
                break;
            }
            while (cnt <= r && a[cnt].t == ti) {// 处理炮击
                if (a[cnt].d == 1) for (int i = 0; i <= m; i++) dp[a[cnt].coord][i] = 0;
                else for (int j = 0; j <= n; j++) dp[j][a[cnt].coord] = 0;
                cnt++;
            }
            if (dp[n][m]) {
                cout << ti << '\n';
                break;
            }
        }
    }
    return 0;
}
```

---

