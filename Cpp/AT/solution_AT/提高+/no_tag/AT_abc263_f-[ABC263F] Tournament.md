# [ABC263F] Tournament

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc263/tasks/abc263_f

$ 1 $ から $ 2^N $ の番号がついた $ 2^N $ 人でじゃんけん大会を行います。

大会は以下の形式で行われます。

- 参加者を人 $ 1 $、人 $ 2 $、 $ \ldots $、人 $ 2^N $ の順に横一列に並べる。
- 現在の列の長さを $ 2M $ として、各 $ i\ (1\leq\ i\ \leq\ M) $ について左から $ 2i-1 $ 番目の人と左から $ 2i $ 番目の人で試合を行い、負けた $ M $ 人を列から外す。これを $ N $ 回繰り返す。

ここで、人 $ i $ はちょうど $ j $ 回試合に勝つと $ C_{i,j} $ 円獲得できます。$ 1 $ 回も勝たなかった場合は何も貰えません。全ての試合の勝敗を自由に決められるとき、人 $ 1 $、人 $ 2 $、 $ \ldots $、人 $ 2^N $ が貰えるお金の合計の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 16 $
- $ 1\ \leq\ C_{i,j}\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

初めの列は $ (1,2,3,4) $ です。 人 $ 1 $ と人 $ 2 $ の試合で人 $ 2 $ が勝ち、人 $ 3 $ と人 $ 4 $ の試合で人 $ 4 $ が勝ったとすると、列は $ (2,4) $ になります。 次に人 $ 2 $ と人 $ 4 $ の試合で人 $ 4 $ が勝ったとすると、列は $ (4) $ になり、これで大会が終了となります。 このとき、人 $ 2 $ はちょうど $ 1 $ 回勝ち、人 $ 4 $ はちょうど $ 2 $ 回勝ったので、貰えるお金の合計は $ 0+6+0+9=15 $ となります。 これが貰えるお金の合計の最大値です。

## 样例 #1

### 输入

```
2
2 5
6 5
2 1
7 9```

### 输出

```
15```

## 样例 #2

### 输入

```
3
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1```

### 输出

```
4```

# 题解

## 作者：Eibon (赞：6)

设 $f_{i,j}$ 表示第 $j$ 个人在前 $i$ 次比赛中均胜利时的方案的最大值。则 $ans = \max f_{n,i} $。

因为在前 $i$ 次比赛中均胜利，所以必从 $f_{i-1,j}$ 转移过来，并且加上 $c_{j,i} - c_{j,i-1}$。

对于 $j$ 参与的比赛之外的比赛，没有特殊限制，所以选择最大的就行。

例如假设 $x$ 为左半部分的人，$y$ 为右半部分的人，则 $f_{i,x} = f_{i-1,x} + c_{j,i} - c_{j,i-1} + \max f_{i-1,y}$。反之同理。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=(1<<17)+5;
int n,ans;
int dp[20][maxn],c[maxn][20],mx[20][maxn];
int power(int a,int b)
{
    if(!b)return 1;
    int tmp=power(a,b/2);
    tmp=tmp*tmp;
    if(b&1)tmp=tmp*a;
    return tmp;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=0;i<(1<<n);i++){
		for(int j=1;j<=n;j++){
			scanf("%lld",&c[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<n);j++){
            dp[i][j]=dp[i-1][j]+c[j][i]-c[j][i-1]+mx[i-1][(j/power(2,i-1))^1];
            mx[i][j/power(2,i)]=max(mx[i][j/power(2,i)],dp[i][j]);
        }
	}
	for(int i=0;i<(1<<n);i++){
		ans=max(ans,dp[n][i]);
	}
	printf("%lld\n",ans);
}
//dyyyyds
```

---

## 作者：zlqwq (赞：4)

首先，按照题意造一课满二叉树，模拟对战图。

也就是说，对于点 $p$ 的左右儿子，就分别是 $2p$ 和 $2p+1$。

并设 $f_{p,cnt}$ 为遍历完 $p$ 的子树，一共赢了 $cnt$ 场比赛的最大结果。

每次将左右子树获胜的结果取 $\max$ 即可。


```cpp
#include<iostream>
#include<cstring>
#include<cmath>
#define int long long
#define inf 2e9
#define debug cout << "zlqwq"

using namespace std;
const int N = 5e5 + 5,M = 20;
int c[N][M],n;
int f[N][M];//dp数组，f[i][j]表示编号为i的点,到现在已经赢了j次比赛，我们可以获得的最大结果
int dfs(int p,int cnt) {//记忆化搜索 
	//p表示现在正在遍历的节点编号
	//cnt表示赢了几场
	int num = pow(2,n);
	if(~f[p][cnt]) return f[p][cnt];//已经搜到过 
	else if(p >= num) return c[p ^ num][cnt];//不存在 
	else return f[p][cnt] = max(/*左子树赢*/dfs(p * 2,cnt + 1) + dfs(p * 2 + 1,0),/*右子树赢*/dfs(p * 2,0) + dfs(p * 2 + 1,cnt + 1));//将左右子树赢的两种情况取最大值，并记录下来 
}
signed main() {
	memset(f,-1,sizeof(f));
	cin >> n;
	int num = pow(2,n);//满二叉数一共有2 ^ n个点 
	for(int i = 0;i < num;++i) {
		for(int j = 1;j <= n;++j) {
			cin >> c[i][j];
		}
	} 
	int ans = dfs(1,0);//开始搜 
	cout << ans;
	return 0;
}

```

---

## 作者：Chengjintian (赞：4)

###  AT_abc263_f [ABC263F] Tournament 题解

## 树形DP

[题目传送门](https://www.luogu.com.cn/problem/AT_abc263_f)

一种码量比较小，比较好理解的做法。

考虑一场比赛的奖金贡献如何计算。

>
>  我们首先需要知道这场比赛谁赢了，以及输掉的一方的最大贡献，这样我们才知道一场比赛中，赢家给出的贡献。
>

先定义：第 $j$ 层的第 $k$ 次决斗：指在第 $j$ 层中从左至右（枚举顺序）的第 $k$ 个节点，比如：

```
 	1 2  3 4       1,2,3,4 分别是第 1 层的第1,2,3,4次决斗
         \/  \/
          5  6         5，6 分别是第 2 层的第1，2次决斗
           \/ 
            7        7 是第 3 层的第 1 次决斗
```

于是我们引出 $f_{i,j}$ 表示第 $i$ 个人赢到了第 $j$ 层，以及 $maxn_{k,j}$ 表示第 $j$ 层中第 $k$ 次决斗所带来的最大贡献。

那么显而易见

$f_{i,j}=f_{i,j-1}-c_{i,j-1}+c_{i,j}+输家的最大贡献$

//（理解： $i$ 第 $j$ 层的贡献先继承上一层的 $i$ 贡献，然后因为每个人只能领一次奖金，于是 $i$ 要把上一场赢的奖金吐出来，即 $f_{i,j-1}-c_{i,j-1}$，然后领取这场的奖金，即 $f_{i,j-1}-c_{i,j-1}+c_{i,j}$。）

输家的贡献如何计算？

结合代码：

```
inline ll ask(ll id,ll l,ll r,ll di,ll cnt){
//id 赢家编号；l,r这场比赛有哪些编号在l~r范围的人参与了竞争；
//di，现在是第几层;cnt 这一层的第几次决斗
	ll mid=l+r>>1;
   	//l~mid 代表左侧，mid+1~r代表右侧
	if(id<=mid)return maxn[2*cnt][di-1];//赢家来自左侧，输家为右侧
	return maxn[2*cnt-1][di-1];//反之
}
```

则

$f_{i,j}=f_{i,j-1}-c_{i,j-1}+c_{i,j}+ask(i,l,r,di,cnt)$

$maxn_{k,j}=\max^{r}_{t=l}f_{t,j-1}$

接下来放代码：

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll f[(1<<16)+15][18],c[(1<<16)+15][17],n;
ll maxn[(1<<16)+15][17];
inline ll ask(ll id,ll l,ll r,ll di,ll cnt){
	ll mid=l+r>>1;
	if(id<=mid)return maxn[2*cnt][di-1];
	return maxn[2*cnt-1][di-1];
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=(1<<n);i++)for(int j=1;j<=n;j++)cin>>c[i][j];
       //注意递推顺序：层数，决斗场次由小及大
	for(int i=1;i<=n;i++){//i表示现在是第几层
		ll cnt=0;
		for(int l=1,r=(1<<i);r<=(1<<n);l=r+1,r+=(1<<i)){
        		//l,r 通过计算可得
			cnt++;
			for(int k=l;k<=r;k++){//k枚举赢家
				f[k][i]=f[k][i-1]-c[k][i-1]+c[k][i]+ask(k,l,r,i,cnt);
				maxn[cnt][i]=max(f[k][i],maxn[cnt][i]);
                		//递推
			}
		}
	}
	cout<<maxn[1][n];
	return 0;
}

```

比较详细的题解，使我的大脑旋转着向您讨要点赞。

---

## 作者：Tsawke (赞：2)

# [[ABC263F] Tournament](https://www.luogu.com.cn/problem/AT_abc263_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC263F)

## 题面

给定 $ n $，存在 $ 2^n $ 个人站成一排进行比赛，比赛赛制按照类满二叉树进行，即每 $ 2i $ 和 $ 2i - 1 $ 两人进行比赛，胜利者进入下一层继续按照相同赛制比赛，直至最终剩余一人。若第 $ i $ 人获得了 $ j $ 场比赛的胜利，那么将获得 $ C_{i, j} $ 的奖金。你可以任意安排每场比赛的输赢，以最大化所有人的奖金和，求最大值。

## Solution

挺有意思的一道题，不难但是需要一点智慧。

显然 DP，但 DP 的状态有多种均可，这里主要介绍一个写起来较为简单易懂的。

令 $ dp(p, i) $ 表示比赛进行到了满二叉树节点的 $ p $ 节点处，此时还需要比赛 $ i $ 次，定义为还需要比赛主要是为了在叶子节点的时候便于处理。

发现这个东西和朴素线段树十分相似，则对于满二叉树的叶子节点编号 $ leaf $，其代表的人的编号（这里从 $ 1 $ 开始编号）即为 $ leaf - 2^n + 1 $，也就是 $ leaf \oplus 2^n + 1 $。

所以对于所有叶子节点有 $ dp(leaf, i) = C_{leaf \oplus 2^n + 1, i} $，中间的转移也十分类似线段树，显然为：
$$
dp(p, i) = \max(dp(lson_p, i + 1) + dp(rson_p, 0), dp(lson_p, 0) + dp(rson_p, i + 1))
$$
显然最终答案在根节点且剩余的比赛次数为 $ 0 $，即 $ dp(1, 0) $。

不难发现这个东西通过记忆化搜索来实现会更便捷一些。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define LS (p << 1)
#define RS (LS | 1)
#define MID ((gl + gr) >> 1)

template < typename T = int >
inline T read(void);

int N, powN;
ll dp[(1 << 16) << 2][20];
ll C[(1 << 16) + 10][20];

ll MakeDP(int p, int i){
    if(~dp[p][i])return dp[p][i];
    if(p >= N)return dp[p][i] = C[(p ^ N) + 1][i];
    return dp[p][i] = max(MakeDP(LS, i + 1) + MakeDP(RS, 0), MakeDP(LS, 0) + MakeDP(RS, i + 1));
}

int main(){
    memset(dp, -1, sizeof dp);
    N = 1 << (powN = read());
    for(int i = 1; i <= N; ++i)for(int j = 1; j <= powN; ++j)C[i][j] = read();
    printf("%lld\n", MakeDP(1, 0));
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_30 初稿

---

## 作者：bryce (赞：1)

## 思路
注意到只会有一个人获胜，所以考虑动态规划，设 $dp_{j, i}$ 表示第 $j$ 个人连续胜利了 $i$ 次时的最大贡献，所以最终答案就为 $\max{dp_{j,n}}$。

再进一步分析一下，$dp_{j, i}$ 的贡献由两部分组成，一个是来自自己胜利的贡献。另一个是打输了的那一方的贡献，首先我们来分析自己胜利的贡献，状态转移方程为 $dp_{j, i} = dp_{j, i - 1} - C_{j, i - 1} + C_{j, i}$，感性的理解就是去掉连续胜利 $i - 1$ 场的贡献，加上连续胜利 $i$ 场的贡献。

接下来分析打输了的那一方的贡献，由于是满二叉树，这场比赛打输的那一方由其下面两场比赛打赢的比赛中的最大贡献，因为我们并不关心其他比赛，其他比赛已经被统计完了，所以只需记录下面两场胜利的比赛中的最大贡献，并加入答案。

## 代码
```cpp
#include<iostream>
#include<cmath>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 18;
int n, ans;
int c[(1 << N)][N], dp[(1 << N)][N], other[N][(1 << N)];
int qpow(int a, int b){
    int ans = 1;
    while (b){
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

signed main(){
    n = read();
    for (int i = 1; i <= (1 << n); i++)
        for (int j = 1; j <= n; j++) c[i][j] = read();
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= (1 << n); j++){
            int x = (j - 1) / qpow(2, i - 1), y = (j - 1) / qpow(2, i);
            dp[j][i] = dp[j][i - 1] - c[j][i - 1] + c[j][i] + other[i - 1][(x % 2 == 0 ? x + 1 : x - 1)];
            other[i][y] = max(other[i][y], dp[j][i]);
        }
    }
    for (int i = 1; i <= (1 << n); i++) ans = max(ans, dp[i][n]);
    cout << ans;
    return 0;
}
```

---

## 作者：WaterSun (赞：1)

[先为大家毙掉一个错解](https://www.luogu.com.cn/paste/yn595mmc)

# 思路

首先不难发现，如果将整棵比赛的对战图画出来，一定是一个满二叉树。

不妨将令一个节点 $u$ 的左右儿子编号分别为 $2u$ 和 $2u + 1$。

然后定义 $dp_{u,d}$ 表示将 $u$ 为根的子树内的选手全部比赛完，并且 $u$ 已经赢了 $d$ 场的最大结果。发现对于 $u$ 要么是从左子树中赢上来的，要么是从右子树中赢上来的，只需从中去一个最大值即可。

发现这个过程可以用 DFS 计算，并有较多的重复计算，加一个记忆化即可。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long
#define pot(x) (1ll << x)

using namespace std;

const int N = 5e5 + 10,M = 24;
int n,m;
int arr[N][M],dp[N][M];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 1) + (r << 3) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline int dfs(int u,int d){
    if (~dp[u][d]) return dp[u][d];
    if (u >= pot(n)) return dp[u][d] = arr[u - pot(n) + 1][d];
    return dp[u][d] = max(dfs(u << 1,d + 1) + dfs(u << 1 | 1,0),dfs(u << 1,0) + dfs(u << 1 | 1,d + 1));
}

signed main(){
    memset(dp,-1,sizeof(dp));
    n = read();
    for (re int i = 1;i <= pot(n);i++){
        for (re int j = 1;j <= n;j++) arr[i][j] = read();
    }
    printf("%lld",dfs(1,0));
    return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

一眼 DP。

定义状态函数 $f_{i,j}$ 表示在第 $i$ 此比赛中，获胜者为 $j$ 时的最大奖学金。把比赛过程看成一棵倒着的满二叉树，就能发现：第 $i$ 场比赛只会是其左儿子为根的子树中叶子节点的某一个与其右儿子为根的子树中叶子节点的某一个进行比赛。然后就可以得到转移方程：$f_{i,j}=f_{lst,j}-c_{j,dep_{lst}}+c_{j,dep_i}+\max\{f_{lst',k}\}$。其中 $lst$ 表示 $j$ 上一次获胜的场次，$dep_i$ 表示从叶子节点到 $i$ 的距离，$k$ 为与 $lst$ 相对的子树中的某一个叶子节点，$lst'$ 就是 $i$ 的另一个儿子。

可以预处理出来 $dep_i,lst,lst'$。答案就是 $\max\{f_{1,i}|1 \le i \le 2^{n}\}$。这里令根节点编号为 $1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=2e5+10,M=20;
int n,c[N][M];
map<int,int> f[N];
int lson[N],rson[N];
vector<int> ve[N];
int dep[N];

il void solve(){
	cin>>n;
	for(re int i=1;i<=pow(2,n);++i)
	for(re int j=1;j<=n;++j)
		cin>>c[i][j];
	for(re int i=pow(2,n+1)-1;i>1;--i){
		if(i&1) lson[i/2]=i;
		else rson[i/2]=i;
	}
	int nowdep=1,lst=pow(2,n-1);
	for(re int i=pow(2,n)-1;i>=1;--i){
		if(!lst) ++nowdep,lst=pow(2,n-nowdep);
		dep[i]=nowdep;
		--lst;
	}
	for(re int i=pow(2,n+1)-1,k=1;i>=pow(2,n+1)-1-pow(2,n)+1;--i,++k) ve[i].push_back(k);
	for(re int i=pow(2,n)-1;i>=1;--i){
		int maxlson=0,maxrson=0;
		for(re int j=0;j<ve[lson[i]].size();++j){
			int x=ve[lson[i]][j];ve[i].push_back(x);
			maxlson=max(maxlson,f[lson[i]][x]);
		}
		for(re int j=0;j<ve[rson[i]].size();++j){
			int x=ve[rson[i]][j];ve[i].push_back(x);
			maxrson=max(maxrson,f[rson[i]][x]);
		}
		for(re int j=0;j<ve[lson[i]].size();++j){
			int x=ve[lson[i]][j];
			f[i][x]=max(f[i][x],f[lson[i]][x]-c[x][dep[lson[i]]]+c[x][dep[i]]+maxrson);
		}
		for(re int j=0;j<ve[rson[i]].size();++j){
			int x=ve[rson[i]][j];
			f[i][x]=max(f[i][x],f[rson[i]][x]-c[x][dep[rson[i]]]+c[x][dep[i]]+maxlson);
		}
	}
	int maxx=0;
	for(re int i=1;i<=pow(2,n);++i) maxx=max(maxx,f[1][i]);
	cout<<maxx;
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：YANGHU4299 (赞：1)

### 思路：
按照题意，我们可以先建出一棵 $(N + 1)$ 层的满二叉树，其中最后一层从左往右依次为 $1 \sim 2^N$。

那么从第一层开始往下搜索，枚举是左子树赢还是右子树赢，取 $\max$ 就可以得到答案。我们再记录一个数 $\text{win}$，表示目前连胜的场数。那么当访问到最后一层时，我们就可以知道该叶子往上能赢多少场。

加个记忆化 $\text{dp}(p, \text{win})$ 表示到节点 $p$，连胜 $\text{win}$ 场时的最大收益即可。

### Code:
```cpp
#include<bits/stdc++.h>
#define Max(a,b) ((a<b)&&(a=b))
#define Min(a,b) ((a>b)&&(a=b))
#define ls p<<1
#define rs p<<1|1
using namespace std;

typedef long long ll;
const int M=(1<<17)+5;

inline int read()
{
	int x=0,f=1;static char ch;
	while(ch=getchar(),ch<48)if(ch==45)f=0;
	do x=(x<<1)+(x<<3)+(ch^48);
	while(ch=getchar(),ch>=48);
	return f?x:-x;
}

int n,c[M][18];
ll dp[M][18];

ll dfs(int p,int win)
{
	if(p>=(1<<n))return c[p^(1<<n)][win];
	if(~dp[p][win])return dp[p][win];
	ll res=max(dfs(ls,win+1)+dfs(rs,0),dfs(ls,0)+dfs(rs,win+1));
	return dp[p][win]=res;
}

int main()
{
	memset(dp,-1,sizeof(dp));
	
	n=read();
	for(int i=0;i<(1<<n);i++)
		for(int j=1;j<=n;j++)
			c[i][j]=read();
	printf("%lld",dfs(1,0));
	
	return 0;
}
```


---

## 作者：AlicX (赞：1)

## Solution 

考虑 $f_{i,j}$ 表示第 $i$ 个人赢下了第 $j$ 场的最大价值，答案即为 $\max_{i=1}^{n}f_{i,m}$。

然后考虑状态转移，令 $l,r$ 为第 $i$ 个人在打第 $j$ 场比赛时的区间，$mid$ 为区间中点，然后分为两种情况：

1. 第 $i$ 个人在左半部分，转移即为 $f_{i,j}=f_{i,j-1}+\max_{k=mid+1}^{r}f_{k,j-1}+a_{i,j}-a_{i,j-1}$。

2. 第 $i$ 个人在右半部分，转移即为 $f_{i,j}=f_{i,j-1}+\max_{k=l}^{mid}f_{k,j-1}+a_{i,j}-a_{i,j-1}$。

注意此时应该先枚举 $j$，否则会有后效性。

发现式子里带有区间 $\max$，预处理一下即可。时间复杂度为 $O(n \times 2^n)$。

考场代码奇丑无比。

```cpp
#include<bits/stdc++.h> 
#define ll long long 
#define int long long  
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=1e5+10,M=20;  
int n,m; 
ll a[N][M],f[N][M]; 
ll g1[N][M],g2[N][M]; 
int Pow(int x,int k){ 
	int res=1; 
	while(k){
		if(k&1) res=res*x; 
		x=x*x; k>>=1;  
	} return res; 
} 
pii get(int i,int j){ 
	int l=(i-1)/j+1,r=l*j; 
	l=(l-1)*j+1; return pii(l,r); 
} 
signed main(){ 
//	freopen("game.in","r",stdin); 
//	freopen("game.out","w",stdout); 
	scanf("%lld",&m); n=pow(2,m); ll ans=0; 
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) scanf("%lld",&a[i][j]); 
	for(int j=1;j<=m;j++){ 
		for(int i=1;i<=n;i++){ 
			int l=get(i,Pow(2,j)).x,r=get(i,Pow(2,j)).y,mid=l+r>>1; 
			if(i<=mid){ 
				ll res=g1[mid+1][j-1]+a[i][j]; 
//				if(j>=2){ 
//					int L=get(i,Pow(2,j-1)).x,R=get(i,Pow(2,j-1)).y,Mid=L+R>>1;
//					if(i<=Mid) res+=g2[Mid+1][j-2]; else res+=g2[L][j-2]; 
//				} 
				f[i][j]=max(f[i][j],res+f[i][j-1]-a[i][j-1]); 
//				 for(int k=mid+1;k<=r;k++){ ll res=0; 
//				 	if(j>=2) for(int p=l;p<=mid;p++) if(get(p,pow(2,j-2))!=get(i,pow(2,j-2))) res=max(res,f[p][j-2]); 
//				 	f[i][j]=max(f[i][j],f[i][j-1]+f[k][j-1]+a[i][j]-a[i][j-1]); 
//				 } 
			} else{ 
				ll res=g1[l][j-1]+a[i][j]; 
//				if(j>=2){
//					int L=get(i,Pow(2,j-1)).x,R=get(i,Pow(2,j-1)).y,Mid=L+R>>1;
//					if(i<=Mid) res+=g2[Mid+1][j-2]; else res+=g2[L][j-2]; 
//				} 
				f[i][j]=max(f[i][j],res+f[i][j-1]-a[i][j-1]); 
//				 for(int k=l;k<=mid;k++){
//				 	ll res=0;
//				 	if(j>=2) for(int p=mid+1;p<=r;p++) if(get(p,pow(2,j-2))!=get(i,pow(2,j-2))) res=max(res,f[p][j-2]);
//				 	f[i][j]=max(f[i][j],f[i][j-1]+f[k][j-1]+a[i][j]-a[i][j-1]); 
//				 }
			} ans=max(ans,f[i][j]); 
		} int p=Pow(2,j); 
		for(int i=1;i<=n;i+=p){ 
			for(int k=i;k<=i+p-1;k++) 
				g1[i][j]=max(g1[i][j],f[k][j]);  
		} p=Pow(2,j-1); 
		for(int i=1;i<=n;i+=p){ 
			for(int k=i;k<=i+p-1;k++) 
				g2[i][j-1]=max(g2[i][j-1],f[k][j-1]); 
		} 
	} printf("%lld\n",ans); return 0; 
} /*
2
2 5
6 5
2 1
7 9

3
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1
1 1 1

3
7 8 6
9 5 3
9 6 5
4 3 3 
2 1 3
5 6 7 
9 1 2
10 8 9

2
4 9
3 6 
5 3 
2 7
*/
```



---

## 作者：LastKismet (赞：0)

## [ABC263F](https://atcoder.jp/contests/abc263/tasks/abc263_f)

### **Tournament** | **竞赛**

#### Points

1.  树形DP



#### Analysis

~~根据生活经验~~，我们可以将整个比赛流程视作一棵满二叉树，那么就可以用树形DP解决这道题。

首先，我们考虑状态：

>    毫无疑问，我们需要储存以每个节点为根的子树能获得的最大权值。

接下来，我们考虑转移：

>    对于每一场比赛，我们都考虑**让谁赢**，从而取得最大的价值。
>
>   假如这是甲（$i$）赢的第 $j$ 场，那么他在这场比赛中就可以**额外创造 $C_{i,j}-C_{i,j-1}$** 的价值。至于这是第几场，我们可以通过**树的高度**判断。
>
>   但是问题来了，我们考虑的是**以每个节点为根的子树能获得的最大权值**。
>
>   所以，我们考虑新建一个数组，用来储存 **某人赢了某场之后，以那一场比赛为根的子树能创造的最大价值。** 毫无疑问，**如果某人赢了这一场，那他一定赢了上一场。**
>
>   但是，我们发现数据量有点大，所以我们可以改存**某人赢了几场之后，以最新一场比赛为根的子树能创造的最大价值。**由于这是树状结构，每个人能赢的比赛都是固定的。
>
>   另外，我们发现，每个节点都有两个子树，而如果 $A$ 子树中的人赢了， $B$ 子树所能创造的最大价值是固定的（反之亦然），也就是 $B$ 子树能获得的最大权值。

#### Solution

设 $i$ 赢了 $j$ 场之后，以最新一场比赛为根的子树能创造的最大价值为 $f_{i,j}$ ，以节点 $i$为根的子树能获得的最大权值为 $mx_i$ 。另外，特别设这一场比赛节点号为 $A$ ，另一棵子树的根节点为 $B$ ，我们可以得到：
$$
f_{i,j}=c_{i,j}-c_{i,j-1}+f_{i,j-1}+mx_B
$$
此外，每次都更新 $mx$ 即可。

####  Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=998244353,N=20,P=7e5;

int n,p;
ll c[P][N],f[P][N];
ll mx[P];
int l[P],r[P],m[P],h[P];

void solve(){
	cin>>n;
	p=(2<<(n-1));
	for(int i=1;i<=p;i++){
		for(int j=1;j<=n;j++){
			cin>>c[i][j];
		}
	}
	l[1]=1;r[1]=p;h[1]=0;
	for(int i=1;i<p;i++){
		m[i]=l[i]+r[i]>>1;
		l[i*2]=l[i];r[i*2]=m[i];
		l[i*2+1]=m[i]+1;r[i*2+1]=r[i];
		h[i*2]=h[i]+1;h[i*2+1]=h[i]+1;
	}
	for(int i=1;i<p;i++)h[i]=n-h[i];//de->hi
	for(int i=p-1;i>=1;i--){
		for(int j=l[i];j<=m[i];j++){
			f[j][h[i]]=f[j][h[i]-1]+c[j][h[i]]-c[j][h[i]-1]+mx[i*2+1];
			mx[i]=max(mx[i],f[j][h[i]]);
		}
		for(int j=m[i]+1;j<=r[i];j++){
			f[j][h[i]]=f[j][h[i]-1]+c[j][h[i]]-c[j][h[i]-1]+mx[i*2];
			mx[i]=max(mx[i],f[j][h[i]]);
		}
	}
	cout<<mx[1];
}

int main(){
	int t;t=1;
	while(t--){
		solve();
	}
	return 0;
}

```

#### Essentials

1.  None

---

