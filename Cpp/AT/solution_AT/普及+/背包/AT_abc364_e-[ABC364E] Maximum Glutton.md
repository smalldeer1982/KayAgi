# [ABC364E] Maximum Glutton

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc364/tasks/abc364_e

高橋君はすぬけ君のために $ N $ 個の料理を作りました。 料理には $ 1 $ から $ N $ までの番号がつけられていて、料理 $ i $ の**甘さ**は $ A_i $、**しょっぱさ**は $ B_i $ です。

高橋君はこれらの料理を好きな順番で並べることができます。 すぬけ君は料理を並べられた順に食べていきますが、ある時点においてそれまでに食べた料理の甘さの合計が $ X $ を超えるかしょっぱさの合計が $ Y $ を超えた場合、それ以降の料理は食べません。

高橋君は、すぬけ君にできるだけ多くの料理を食べてほしいと思っています。 高橋君がうまく料理を並べたとき、すぬけ君が最大で何個の料理を食べることになるか求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 80 $
- $ 1\leq\ A_i,B_i\ \leq\ 10000 $
- $ 1\leq\ X,Y\ \leq\ 10000 $
- 入力は全て整数

### Sample Explanation 1

高橋君が料理を $ 2,3,1,4 $ の順番で並べた場合のすぬけ君の行動を考えます。 - まず料理 $ 2 $ を食べる。ここまでに食べた料理の甘さの合計は $ 3 $、しょっぱさの合計は $ 2 $ である。 - 次に料理 $ 3 $ を食べる。ここまでに食べた料理の甘さの合計は $ 7 $、しょっぱさの合計は $ 3 $ である。 - 次に料理 $ 1 $ を食べる。ここまでに食べた料理の甘さの合計は $ 8 $、しょっぱさの合計は $ 8 $ である。 - しょっぱさの合計が $ Y=4 $ を超えたので、これ以降の料理は食べない。 よって、この並び方の場合すぬけ君は $ 3 $ 個の料理を食べることになります。 高橋君が料理をどのように並べてもすぬけ君が $ 4 $ つ全ての料理を食べることはないので、答えは $ 3 $ です。

## 样例 #1

### 输入

```
4 8 4
1 5
3 2
4 1
5 3```

### 输出

```
3```

## 样例 #2

### 输入

```
2 1 1
3 2
3 2```

### 输出

```
1```

## 样例 #3

### 输入

```
2 100 100
3 2
3 2```

### 输出

```
2```

## 样例 #4

### 输入

```
6 364 463
230 381
154 200
328 407
339 94
193 10
115 309```

### 输出

```
3```

# 题解

## 作者：Link_Cut_Y (赞：15)

数据范围 $n \le 80$ 的最优化问题天生为退火而生。

我们充分发扬人类智慧，将菜肴随机打乱，每次交换两个并且求出满足条件的最长前缀。如果这个前缀比原来长就保留。答案就是这个最长前缀。

背包什么的不会啦。

```cpp
const int N = 1010;
int n, X, Y; PII p[N]; int ans = 0;
int calc() {
	int s1 = 0, s2 = 0;
	rep(i, 1, n) {
		s1 += p[i].x, s2 += p[i].y;
		if (s1 > X or s2 > Y) {
			ans = max(ans, i); return i;
		}
	} ans = max(ans, n); return n;
}
void SA() {
	sort(p + 1, p + n + 1);
	for (double t = 1e5; t >= 1e-7; t = t * 0.998) {
		int x = calc(); int u = rand() % n + 1;
		int v = rand() % n + 1; swap(p[u], p[v]);
		int y = calc(); if (y > x) continue;
		if ((double)exp((double)(y - x) / t) > (double)rand() / RAND_MAX)
			continue;
		swap(p[u], p[v]);
	}
}
signed main() {
	srand(time(0));
	read(n, X, Y);
	rep(i, 1, n) read(p[i].x, p[i].y);
	random_shuffle(p + 1, p + n + 1);
	for (int i = 1; i <= 100; i ++ ) SA();
	cout << ans << endl; return 0;
}
```

---

## 作者：ikunTLE (赞：13)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc364_e)

### 思路

这是一道**背包**问题。定义 $f_{i,j,k}$ 为前 $i$ 道菜中吃 $j$ 道且甜度为 $k$ 时咸度的最小值。

状态转移方程：$f_{i,j,k}\gets\min(f_{i-1,j,k},f_{i-1,j-1,k-a_i}+b_i)$。

答案统计：设 $x$ 为最大的 $f_{N,j,k}\le Y$ 中的 $j$，答案即为 $\min(x+1,N)$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=100,M=1e4+10;
int a[N],b[N],f[N][N][M];
int main(){
	int n=read(),x=read(),y=read();
	for(int i=1;i<=n;++i)
		a[i]=read(),b[i]=read();
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;++i)
		f[i][0][0]=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=i;++j)
			for(int k=0;k<=x;++k){
				if(k>=a[i])
					f[i][j][k]=f[i-1][j-1][k-a[i]]+b[i];
				f[i][j][k]=min(f[i][j][k],f[i-1][j][k]);
			}
	for(int i=n;i>=0;--i)
		for(int j=0;j<=x;++j)
			if(f[n][i][j]<=y)
				return printf("%d\n",min(i+1,n)),0;
	return 0;
}
```

---

## 作者：Alex_smy (赞：5)

## 题意简述
有 $N$ 盘菜，其中第 $i$ 盘菜的甜度为 $A_i$，咸度为 $B_i$。当吃的菜甜度总和超过 $X$，或者咸度总和超过 $Y$，就不能再吃任何菜了。求最多能吃多少盘菜。
## 解题思路
这道题是典型的 01 背包问题，但是每选一盘菜都会消耗两种价值（甜度和咸度），因此我们可以使用二维费用背包解决这道题。

设 $f(i,x,y)$ 表示在前 $i$ 道菜中，甜度总和不超过 $x$，咸度总和不超过 $y$ 的情况下，最多能吃多少道菜。

但是这样做时间复杂度是 $O(NXY)$，而数据范围是 $1 \le X,Y \le 10000$，因此这个时间复杂度是无法被接受的。不过我们发现 $N$ 很小，因此我们可以考虑通过将 $X$ 和 $Y$ 中的一位替换成 $N$，从而降低时间复杂度。

那么怎么实现呢？我们必须重新设计状态。设 $f(i,j,k)$ 表示在前 $i$ 道菜中选择 $j$ 道吃掉，使得甜度总和为 $k$ 时，咸度总和最小是多少。这样，状态的前两个维度就都和 $N$ 有关，所以时间复杂度就成功降到了 $O(N^2X)$。

接着我们需要考虑如何进行状态转移。对于 $f(i,j,k)$ 来说，如果我们选择不吃第 $i$ 道菜，那么咸度总和就是 $f(i-1,j,k)$；如果我们选择吃第 $i$ 道菜，那么咸度总和就是 $f(i-1,j-1,k-A_i)+B_i$。接下来取一个最小值，于是我们就能得到状态转移方程是 $f(i,j,k)=\min(f(i-1,j,k),f(i-1,j-1,k-A_i)+B_i)$。

最后统计答案。我们只需找到满足 $f(N,j,k) \le Y$ 的 $j$，因为只有超过限制才会停止吃菜，所以最终答案应该是 $\min(N,j+1)$。

由于 $f(i)$ 的值只与 $f(i-1)$ 的值有关，因此我们还可以做一个优化，把第一维滚掉，空间复杂度从 $O(N^2X)$ 降为 $O(NX)$。
## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,y,a[85],b[85],f[85][85][10005],ans;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;i++) f[i][0][0]=0;//初始化
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			for(int k=x;k>=0;k--){
				f[i][j][k]=f[i-1][j][k];
				if(k>=a[i]) f[i][j][k]=min(f[i][j][k],f[i-1][j-1][k-a[i]]+b[i]);
			}
		}
	}//二维费用背包
	for(int i=1;i<=n;i++){
		for(int j=0;j<=x;j++){
			if(f[n][i][j]<=y) ans=i;
		}
	}//统计答案
	printf("%d",min(n,ans+1));
	return 0;
}
```

---

## 作者：2huk (赞：4)

很好很好的 DP。最暴力的是设 $f(i,j,k)$，表示前 $i$ 个物品中，甜度 $\le j$，咸度 $\le k$，能选的最多数量。

观察到定义域（状态数）过大，但是值域很小。[经典做法](https://www.bilibili.com/video/BV1fabKejErr/?share_source=copy_web&vd_source=e1044e7a01b4b54d479c00e7fea3f47d&t=1109)交换值域和某一维。于是新状态是 $f(i, j, k)$ 表示前 $i$ 个物品，选了 $j$ 个，且在甜度 $\le k$ 的情况下咸度的最小值。复杂度从 $\mathcal O(nXY)$ 优化至 $\mathcal O(n^2X)$。

<https://atcoder.jp/contests/abc364/submissions/56027126>

---

## 作者：Thomas0702 (赞：2)

一眼 dp。一个非常 naive 的思路是设 $dp_{i,j,k}$ 表示考虑到第 $i$ 种菜，背包容量分别为 $j$ 和 $k$ 的时候最多能选多少道菜。可惜值域为 $10^4$，即使使用常数优化也会 TLE 三个点。

既然值域不能作下标，就让它成为维护的值。我在考场上想到的是，设能选 $i$ 道菜，那么对于每一个 $i$ 维护一个 vector 储存二元组 $(x,y)$，表示选 $i$ 道菜的时候存在一种选法使得两种背包的值域分别为 $x$ 和 $y$。二元组的的数量仍然是 $O(N^2)$ 的，肯定不行。容易发现有非常多的多余状态，即一定有状态是不优的。考虑这样两个状态：$(x,y)$ 和 $(x+a,y+b)$，其中 $a,b\ge 0$，那么后者一定是不优的。所以，去掉 vector 中的多余元素，按照 $x$ 排序后 $y$ 一定要递减。由于 vector 中一定没有 $x$ 或者 $y$ 相同的元素，所以每个 vector 中的元素个数是 $O(\min(X,Y))$ 的。

这样就可以转移了。每遍历到一道菜 $k$，就遍历所有的 $i$ 的 vector 中的方案 $(x,y)$，新产生方案 $(x+x_k,y+y_k)$，如果合法，即 $x+x_k\le X,y+y_k\le Y$，就加入 $i+1$ 的 vector 中，并且排序去重即可。最后倒序遍历 $i$，如果 vector 不为空则答案为 $\max(i+1,N)$。

时间复杂度 $O(N^2V\log V)$，其中 $V=\min(X,Y)$。因为方案中的 $x$ 和 $y$ 大概率不连续，常数非常小，所以跑得飞快。
```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
void rd(){}
template<typename T,typename... U> void rd(T &x,U &...arg){
	x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
	x*=f;rd(arg...);
}
const int maxn=85,maxv=10005;
struct node{int x,y;}a[maxn];
int N,X,Y,ans;
typedef pair<int,int> pii; 
vector<pii> g[maxn];
int main(){
	rd(N,X,Y);
	for(int i=1;i<=N;i++) rd(a[i].x,a[i].y);
	g[0].push_back({0,0});
	for(int i=1;i<=N;i++){
		for(int j=i-1;j>=0;j--){
			vector<pii> t=g[j+1];
			for(auto k:g[j])
				if(k.first+a[i].x<=X&&k.second+a[i].y<=Y)
					t.push_back({k.first+a[i].x,k.second+a[i].y});
			sort(t.begin(),t.end());
			pii lst(-1,1e9);
			g[j+1].clear();
			for(auto k:t)
				if(k.second<lst.second)
					g[j+1].push_back(lst=k);
		}
	} 
	for(int i=N;i;i--)
		if(!g[i].empty()){
			ans=i;
			break;
		}
	printf("%d",ans<N?ans+1:ans);
	return 0;
}
```

---

## 作者：Barryb (赞：2)

# 思路
这题看一眼就是动态规划。  
我们可以定义一个三维数组 $dp_{i,j,k}$，其中 $i$ 表示当前考虑的食物数量，其中 $j$ 表示当前的总甜度，那么 $k$ 表示当前的总咸度。所以 $dp_{i,j,k}$ 的值表示在当前甜度和咸度下 Snuke 能够吃掉的最大食物数量。
# 结论
由此我们就可以得出状态转移方程。

```cpp
dp[i][j][k]=dp[i-1][j][k];
if(j&&k>=a[i]) dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-1][k-a[i]]+b[i]);
```
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,a[100],b[100],dp[90][90][10010],ans;
int main(){
	memset(dp,0x7f7f7f7f,sizeof dp);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	dp[0][0][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			for(int k=0;k<=x;k++) {
				dp[i][j][k]=dp[i-1][j][k];
				if(j&&k>=a[i]) dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-1][k-a[i]]+b[i]);
				if(dp[i][j][k]<=y) ans=max(ans,j+1);
			}
	cout<<min(ans,n);
    return 0;  
}
```

---

## 作者：da_ke (赞：1)

## 前情

当场没做 D 来做 E 是明智的，D 根本想不到的。

## 题目

翻译一下：

> 高桥准备 $n$ 个菜，每个菜肴有甜味值 $a_i$ 和 咸味值 $b_i$。高桥可以按任意顺序排放这些菜肴。Snuke 按排放的顺序吃，当吃的总甜味值大于 $X$ **或**总咸味值**大于** $Y$ 时停止。求吃的菜肴总数的最大值。

## 思路

### Step 1

这道题和 C 题如出一辙，但仔细一看发现未必。这题求的是最大值。

数据范围是 $n\le 80$ 且 $X,Y\le 1000$ 显然 dp。

> 对比 P2240 和 P1048，发现其实和分别这次 C 题和 E 题道理相同。

一眼类似于背包的 dp，不难设计状态转移：

$dp(i,x,y)=\max\{dp(i+1,x,y),1+dp(i+1,x-a_i,y-b_i)\}$。

其中 $i$ 表示考虑了前 $i$ 个菜肴，$x,y$ 分别表示能承受的甜味、咸味值还剩余多少，$t$ 表示已经选了 $t$ 个菜肴。

事实上，$x$ 确定了 $y$ 就确定了，故记忆化时忽略 $y$。否则空间肯定开不下。代码中的 `cnt` 是为了方便编写，实则不必计入状态。

同时不难写出类似于这样的代码（读者别急着写类似于这样的代码）：

```cpp
// 赛时代码
// #define EXT
#include <bits/stdc++.h>
#ifdef EXT
    #include <bits/extc++.h>
#endif

#define i64 long long
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define fdn(i,r,l) for(int i=(r);i>=(l);i--)
#define pii pair<int,int>

using namespace std;

typedef long long ll;
typedef double db;
typedef __int128 i128;

const int INF=1<<29;
const ll INFL=1ll<59;

const int N=114;
const int M=10024;

int n,x,y;
int a[N],b[N];
int mem[N][M][N];

inline int dp(int d,int xx,int yy,int cnt)
{
    if(xx<0||yy<0) return cnt;
    if(d==n+1) return cnt;
    int& ans=mem[d][xx][cnt];
    if(ans!=-1) return ans;
    int ans0=0,ans1=0;
    ans0=dp(d+1,xx-a[d],yy-b[d],cnt+1);
    ans1=dp(d+1,xx,yy,cnt);
    return ans=max(ans0,ans1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("in.out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    memset(mem,-1,sizeof(mem));
    cin>>n>>x>>y;
    rep(i,1,n) cin>>a[i]>>b[i];
    cout<<dp(1,x,y,0);
}
```

同：<https://atcoder.jp/contests/abc364/submissions/56045157>

很可惜，这样的思路是有漏洞的！

## Step 2

比赛的时候碰到这种情况一定冷静！

显然，该程序并未考虑顺序问题。

0-1 背包中物体选的顺序是不考虑的。但题目中特别说了：

> **高桥可以按任意顺序排放这些菜肴。**

反例：不妨只考虑甜味值，假设咸味值远远还没有达到极限。假设选的菜肴中有一个菜的甜味值为 $p$，另一个**在它之前**的菜肴甜味值为 $q$。假设除去这两个菜肴以外已经选了甜味值 $m$，且 $m+p+q>m+q>X>m+p>m$。

按照我们之前的方案，最大的甜味值被认为是 $m+q$。然而将 $p$ 和 $q$ 交换就得到最大甜味值 $m+p+q$，所以最大的菜肴数也比原来多 $1$，故原方法有漏洞。

很容易想到用排序法修复 Bug。

## Step 3

这是我们将咸味值加进来。我们不妨只考虑其中两个临项 $i$ 和 $i+1$ 的情况。列表得：

|项（菜）|已选甜味|已选咸味|
|:---:|:---:|:---:|
|$[1,i)$|$x$|$y$|
|$i$|$x+a_i$|$y+b_i$|
|$i+1$|$x+a_i+a_{i+1}$|$y+b_i+b_{i+1}$|

反之：

|项（菜）|已选甜味|已选咸味|
|:---:|:---:|:---:|
|$[1,i)$|$x$|$y$|
|$i$|$x+a_{i+1}$|$y+b_{i+1}$|
|$i+1$|$x+a_i+a_{i+1}$|$y+b_i+b_{i+1}$|

若 $x+a_{i+1}>X>x+a_{i}$ 且 $y+b_{i+1}>Y>y+b_{i}$ 这时一定有 $a_{i+1}+b_{i+1}>a_{i}+b_{i}$。也就是说，符合条件的满足：$a_{i+1}+b_{i+1}>a_{i}+b_{i}$。那我们可以将 $a_i+b_i$ 从小到大排序。

补充：不妨考虑满足 $x+a_{i+1}>X>x+a_{i}$ 但不满足 $y+b_{i+1}>Y>y+b_{i}$，这时交换后会出现和交换前一样的现象。

在基础上改一下就可以得到：

```cpp
// 赛时代码修改
// #define EXT
#include <bits/stdc++.h>
#ifdef EXT
    #include <bits/extc++.h>
#endif

#define i64 long long
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define fdn(i,r,l) for(int i=(r);i>=(l);i--)
#define pii pair<int,int>

using namespace std;

typedef long long ll;
typedef double db;
typedef __int128 i128;

const int INF=1<<29;
const ll INFL=1ll<59;

const int N=114;
const int M=10024;

int n,x,y;
vector<pair<int,int> > s;
int a[N],b[N];
int mem[N][M][N];

int cmp2(pair<int,int> A,pair<int,int> B)
{
    return A.second+A.first<B.first+B.second;
}

inline int dp(int d,int xx,int yy,int cnt)
{
    if(d==n+1) return cnt;
    int& ans=mem[d][xx][cnt];
    if(ans!=-1) return ans;
    int ans0=0,ans1=0;
    if(xx>=a[d]&&yy>=b[d]) ans0=dp(d+1,xx-a[d],yy-b[d],cnt+1);
    else ans0=cnt+1;
    ans1=dp(d+1,xx,yy,cnt);
    return ans=max(ans0,ans1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("in.out","w",stdout);
#endif
    ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    memset(mem,-1,sizeof(mem));
    cin>>n>>x>>y;
    rep(i,1,n){int ai,bi;cin>>ai>>bi;s.push_back({ai,bi});}
    sort(s.begin(),s.end(),cmp2);
    for(int i=0;i<s.size();++i) a[i+1]=s[i].first,b[i+1]=s[i].second;
    int ans=dp(1,x,y,0);
    cout<<ans;
}
```

代码中 `mem` 数组中 `cnt` 的维度同样可以略去不计。

## 总结

当场肯定不能像写题解一样考虑，一般来说是用直觉做的（也有一眼看穿证明的）。

这个思路阶梯是我当场[真实体验](https://atcoder.jp/contests/abc364/submissions/me?f.Task=abc364_e&f.LanguageName=&f.Status=&f.User=)。所以希望大家考虑全面。

**但是本题解给出的方法只是思考的时候用的，并不是证明**。有疑问或证明欢迎评论！

难度评级：绿或蓝。

---

## 作者：wfirstzhang (赞：1)

# ABC364E
## 思路
### 算法
考虑动态规划背包。有两种方法：
1. 状态 $dp_{i,j,k}$ 表示吃到第 $i$ 道菜，甜度不超过 $j$，咸度不超过 $k$ 时能吃到的最大道数。但是很明显，时间复杂度为 $\Theta(NXY)$，会 TLE。
2. 直接推出答案显然行不通了。那么可以间接推出：吃 $k$ 道菜，甜度不超过 $j$ 时最小的咸度，只要这个最小咸度小于 $Y$，那么就可以吃这 $k$ 道菜，最后寻找符合条件的最大值。时间复杂度 $\Theta(N^2X)$，轻松通过。
### 实现
设 $dp_{i,j,k}$ 为只能在前 $i$ 道菜里选择 $k$ 道吃，甜度不超过 $j$ 时最小的咸度。

那么状态转移方程为 
$$
dp_{i,j,k} = \min(dp_{i-1,j,k}, dp_{i-1,j-A_i,k-1} + B_i)
$$
也就是说这个状态可以不选这道菜，从上一道继承，也可以吃这道菜。取这两种的最小值。

可以滚动数组优化空间，压缩掉 $i$ 的维度。但需要让第二层循环倒着来，不然 $j-A_i$ 会在选了这道菜的基础上再选一遍，但是题目说只能吃一次。 

另外要注意，初始状态是对于每个 $0 \le i \le X$，$dp_{i,0} = 0$，表示一道菜也不吃，无论甜度最大多少，咸度都是 $0$。

最后遍历 $dp$ 数组，如果 $dp_{i,j} \le Y$，那么就可以再吃一道，即 $ans=\max(ans,i+1)$。输出时注意要取 $\min(ans,N)$，因为即使还没吃满，菜也没了。
## AC Code
```cpp
#include <algorithm>
#include <iostream>
struct dish{ int sweet, salt; };
int main() {
    using namespace std;
    //输入部分
    int n, sweet_max, salt_max, ans = 0;
    cin >> n >> sweet_max >> salt_max;
    auto arr = new dish[n];
    for(int i = 0; i < n; i++)
        cin >> arr[i].sweet >> arr[i].salt;
    //初始化 dp 数组
    auto dp = new int*[sweet_max + 1];
    for(int i = 0; i <= sweet_max; i++)
    {
        dp[i] = new int[n + 1]();
        fill_n(dp[i] + 1, n, 1073741824);
        //此时 dp[i][0] == 0
    }
    //dp
    for(int i = 0; i < n; i++)
        for(int j = sweet_max; j >= arr[i].sweet; j--) //滚动数组倒序
            for(int k = 1; k < i + 2; k++)
                dp[j][k] = min(dp[j][k], dp[j - arr[i].sweet][k - 1] + arr[i].salt);
    //找答案
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= sweet_max; j++)
            if(dp[j][i] <= salt_max)
                ans = max(ans, i + 1);
    cout << min(ans, n) << endl;
    for(int i = 0; i <= sweet_max; i++)
        delete[] dp[i];
    delete[] dp;
    delete[] arr;
    return 0;
}
```

---

## 作者：Down_syndrome (赞：1)

## 题意

共有 $n$ 碟料理，每碟料理有一个甜度 $a$ 和咸度 $b$。高桥想要吃尽量多的料理。可当他吃的料理甜度累计达到 $x$ 或咸度达到 $y$ 他就会觉得恶心，就会停止吃料理。现在请你安排他吃料理的顺序，使得他能吃尽量多的料理，并输出他最多能吃的料理的数量。

## 思路
不看数据范围，这就是一个经典二维背包问题。令 $f_{i,j}$ 表示目前累计甜度为 $i$，咸度为 $j$ 的最大值。转移方程为 $f_{i,j}=\max\{f_{i-a_k,j-b_k}+1\}$。这时候再来看数据范围，发现时空双炸。关键问题在于 $x,y$ 都很大，但是 $n$ 非常小，导致状态非常多。我们考虑改一改 dp 的状态。令 $f_{i,j}$ 为甜度为 $i$，已经吃了 $j$ 道菜的甜度最小值，也就是交换一下原先状态的第二维和答案。这样状态数大大减小。值得注意的是 dp 时循环的顺序。先枚举考虑到第 $i$ 道菜，再**从大到小**枚举累计的甜度 $j$，最后枚举吃了的菜的数量 $k$，转移方程为 $f_{j,k}=\min\{f_{j-a_i,k-1}+b_i\}$。

（其实第二层和第三层循环的位置可以调换，但是调换后 $k$ 需要从大到小枚举，至于原因留给读者思考）

[code](https://atcoder.jp/contests/abc364/submissions/56029995)

---

## 作者：Hadtsti (赞：1)

### 题意简述

给定 $n$ 个二元组 $(x_i,y_i)$，要求从中挑选尽可能多的二元组使得 $x$ 的和不超过给定的 $X$，$y$ 的和不超过给定的 $Y$。若组数为 $m$，输出 $\min(m+1,n)$。

$1\le n\le 80,1\le x_i,y_i,X,Y\le10^4$

### 题目分析

~~由于之前比赛多次被贪心干爆于是练了点贪心，结果看啥啥贪心，在另一种意义上被贪心干爆了~~

赛时歪解扔到[剪贴板](https://www.luogu.com.cn/paste/h754u5ao)里了，写得根场上心态一样魔怔，感兴趣可以当个乐子看看。

正解考虑优化 naive 的二维背包。我们发现 $n$ 非常小，相比之下值域偏大，两个值域状态太浪费。

考虑答案和 $n$ 同级别，我们不妨把 $f$ 的值和状态换一下。维护 $f_{i,j,k}$ 表示考虑前 $i$ 个二元组并从中选了 $k$ 个，$x$ 的和为 $j$ 时 $y$ 和的最小值。则得到转移方程 $f_{i,j,k}=\min\{f_{i-1,j,k},y_i+f_{i-1,j-1,k-x_i}\}$。实现时 $i$ 维可以扔掉。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,X,Y,f[85][10010],ans;
int main()
{
	scanf("%d%d%d",&n,&X,&Y);
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		for(int j=n;j;j--)
			for(int k=X;k>=x;k--)
				f[j][k]=min(f[j][k],f[j-1][k-x]+y);
	}
	for(int i=n;~i;i--)
	{
		for(int j=1;j<=X;j++)
			if(f[i][j]<=Y)
			{
				ans=i;
				break;
			}
		if(ans)
			break;
	}
	printf("%d",min(ans+1,n));
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：1)

正常动规，但是赛时死了。

## 分析

看到 $n$ 很小，但是 $X$ 和 $Y$ 有点大，所以状态稍微改变一下。

设 $dp_{i,j}$ 表示已经选到第 $j$ 个，且甜度为 $i$ 时咸度的最小值。

转移方程为：

$$dp_{j,k}=\min_{0\le k\le i,a_i\le j\le X}(dp_{j,k},dp_{j-a_i,k-1}+b_i)$$

按照 $i,j,k$ 的顺序依次枚举就行，注意 $j$ 要倒序枚举来避免后效性。

统计答案的时候遍历一遍，在所有满足条件的值里面找到最大值即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
int n,X,Y;
struct no
{
	int x,y;
}a[maxn];
int dp[10010][100],ans=0;
signed main()
{
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n>>X>>Y;
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read();
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=X;j>=a[i].x;j--)
		{
			for(int now=0;now<=i;now++)
			{
				dp[j][now]=min(dp[j-a[i].x][now-1]+a[i].y,dp[j][now]);
				if(dp[j][now]<=Y) ans=max(ans,now);
			}
		}
	}
	cout<<min(ans+1,n);
	return 0;
}

```

看完记得点个赞偶。

---

## 作者：DengStar (赞：1)

[在博客园中查看](https://www.cnblogs.com/dengstar/p/18329016) | [题目链接](https://atcoder.jp/contests/abc364/tasks/abc364_e)

看到这题，首先想到**二维费用背包**：设 $f(i, x, y)$ 表示在前 $i$ 道菜肴中，甜度不超过 $x$，咸度不超过 $y$ 的情况下，最多能吃多少道菜肴。需要注意，因为甜度或咸度超过限度时才会停止，所以在吃掉 $f(N, X, Y)$ 道菜肴之后，他还可以再吃一道（如果还有菜肴的话），因此答案为 $\min(N, f(N, X, Y) + 1)$。

但是，二维费用背包的时间复杂度是 $O(NXY)$，在本题中无法接受。注意到 $N$ 很小，这时应该考虑**改变状态设计**，并尽可能在下标中用和 $N$ 有关的量替换掉 $X$、$Y$ 有关的量，这样就可能减小时间复杂度。

重新设计状态：设 $f(i, j, k)$ 表示在前 $i$ 道菜肴中选择 $j$ 道吃掉，使得总甜度值为 $k$ 时，这些菜肴的最小总盐度值。这样，状态的前两个维度都和 $N$ 有关，又因为转移的时间复杂度是 $O(1)$（见下），所以总的时间复杂度就降到了 $O(N^{2}X)$。想到这样设计状态，接下来也就十分简单了。

答案统计：找到最大的满足 $f(N, j, k) \le Y$ 的 $j$，则答案为 $\min(N, j+1)$。（$0 \le k \le X$）

转移方程：$f(i, j, k) = \min(f(i-1, j, k), f(i-1, j-1, k-a_i)+b_i)$，括号中两项分别考虑选择和不选择第 $i$ 道菜肴。

初始化：$f(i, j, k) = \begin{cases} 0, j=k=0 \\ +\infty, \text{Otherwise} \end{cases}$

[AC 记录](https://atcoder.jp/contests/abc364/submissions/56082804)

优化：由于 $f(i,*,*)$ 只和 $f(i-1,*,*)$ 有关，所以可以把第一维滚掉，空间复杂度降到 $O(NX)$。注意循环要改成倒序。

[AC 记录]()

---

## 作者：D0000 (赞：1)

跟 C 题很像，但不能使用贪心了。发现 $N,X,Y$ 都较小，使用背包。用 $f_{i,j,k}$ 表示前 $i$ 道菜中选 $j$ 道，甜度最大为 $j$ 的情况中酸度最小为多少。那么当第 $i$ 道菜甜度为 $a$，酸度为 $b$ 时转移方程为：

$$f_{i,j,k}=\min(f_{i-1,j,k},f_{i-1,j-1,k-a}+b)$$

由于转移时只与上一个 $i$ 有关，可以省略第一维（就是 01 背包）。

答案是最大的一个 $j$，满足存在 $t\in[1,X]$ 使得 $f_{N,j,t}\le Y$。但注意若 $j\neq N$ 则答案是 $j+1$。因为要吃完后才会停止吃。

代码：


```cpp
#include<cstdio>
#include<algorithm>
int n,a,b,f[85][10005],x,y;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++)for(int j=0;j<=x;j++)f[i][j]=1e9;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		for(int j=n;j;j--)for(int k=x;~k;k--)if(k>=a)f[j][k]=std::min(f[j][k],f[j-1][k-a]+b);
	}
	for(int i=n;~i;i--)for(int j=1;j<=x;j++)if(f[i][j]<=y)return !printf("%d",i==n?n:i+1);
}
```

---

## 作者：__O_v_O__ (赞：1)

此题是简单的动态规划，考场上我直接推出了题解的式子。

看到题目，相信不少人都想到了这样的定义：$f_{i,x,y}$ 表示前 $i$ 道菜，甜度和为 $x$，咸度和为 $y$ 的最多吃的菜数。

可是，这样是 $O(nxy)$ 的，我们需要优化。

我们发现 $n$ 很小，于是可以考虑 $O(n^2)$ 记录当前计算到的菜数和选择的菜数。但是，这样甜度和咸度的信息就会丢失一些，我们可以选择让计算答案的复杂度升高，从而降低转移的复杂度。

具体来说，我们定义状态 $f_{i,j,x}$ 为前 $i$ 道菜，选择了 $j$ 道，甜度和为 $x$ 的最小咸度和（这里之所以是最小咸度，是因为题目要求咸度和要小于 $y$，所以越小越优）。

这样，求答案就需要枚举选择的菜数和甜度和，复杂度为 $O(nx)$（甜度和当然只枚举小于 $x$ 的），但是我们把转移复杂度优化为了 $O(n^2x)$。

不难写出转移方程（这里用的顺推）：

- 不选第 $i$ 道菜：$f_{i,j,x}\xrightarrow{\min}f_{i+1,j,x}$。

- 选第 $i$ 道菜：$f_{i,j,x}+b_i\xrightarrow{\min}f_{i+1,j+1,x+a_i}$。

显然，边界为 $f_{0,0,0}=0$。

最后考虑如何求答案，我们可以倒序枚举选的菜数 $j$，再枚举甜度和 $x$，如果 $f_{n,j,x}\le y$，则 $j$ 是可行的，直接输出即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x,y,a[101],b[101],f[81][81][10001],mx,fl,ma;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>x>>y;
	memset(f,0x3f,sizeof f);//初始化
	f[0][0][0]=0;//边界
	for(int i=0;i<n;i++)
		cin>>a[i]>>b[i];
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=x;k++){
				f[i+1][j][k]=min(f[i+1][j][k],f[i][j][k]);//情况1
				if(k+a[i]<=x)
					f[i+1][j+1][k+a[i]]=min(f[i+1][j+1][k+a[i]],f[i][j][k]+b[i]);//情况2
			}
		}
	}
	for(int j=n;j>=0;j--){
		bool ok=0;//是否可行
		for(int k=0;k<=x;k++){
			if(f[n][j][k]<=y){
				ok=1;//可行
				break;
			}
		}
		if(ok){
			cout<<min(j+1,n);//输出（吃了j道后还能吃一道，所以要加1，还要和总数取最小值）
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Heldivis (赞：0)

## [ABC364E] Maximum Glutton

这是一个双重限制的背包。考虑直接做，$f_{i, j}$ 表示甜味为 $i$、咸味为 $j$ 的最多吃的个数，则对于每个食物 $k$，有转移 $f_{i,j} = \max\{f_{i,j},f_{i - a_k，j - b_k}\}$ 倒序枚举防止重复吃。时间复杂度 $O(NV^2)$，不能接受。

注意到 $N\le80$，将状态 $f_{k,i,j}$ 改为**在前 $k$ 个食物中，吃了$i$个食物，甜味为 $j$ 的最小咸味**，最后枚举判断，取最大值即可。转移：

$$f_{k,i,j} = \min\{f_{k - 1, i,j},f_{k - 1, i - 1, j - a_k}+b_k\}$$

注意要求严格大于，所以统计小于等于 $Y$ 的方案的吃的食物个数，然后 $+1$，同时不能超过 $N$。

细节看代码，实现上可以倒序枚举省去一维空间：

```cpp
for (int i = 1; i <= n; ++i) s[i].a = read(), s[i].b = read();
memset(f, 0x3f, sizeof f);
f[0][0][0] = 0;
for (int id = 1; id <= n; id++)
  for (int num = 0; num <= n; num++)
    for (int i = 0; i <= x; i++) {
      f[id][num][i] = f[id - 1][num][i];
      if (num >= 1 && i >= s[id].a)
        f[id][num][i] =
            min(f[id][num][i], f[id - 1][num - 1][i - s[id].a] + s[id].b);
    }
for (int i = n; i >= 0; i--)
  for (int j = 0; j <= x; j++)
    if (f[n][i][j] <= y) {
      ans = max(ans, i);
      if (i < n) ans = max(ans, i + 1);
    }
printf("%d\n", ans);
```

另外注意读入格式，如果写成：
```cpp
for (int i = 1; i <= n; ++i) s[i].a = read();
for (int i = 1; i <= n; ++i) s[i].b = read();
```
可以通过样例和大部分测试点，但显然是错误的。

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定 $N$ 道菜，第 $i$ 道菜有 $a_i$ 和 $b_i$ 两个参数，分别表示甜度和咸度，重新排列这 $N$ 道菜，使得 $\sum_{i=1}^{k} a_i\le X$ 并且 $\sum_{i=1}^{k} b_i\le Y$，求 $k_{\max}$。

## 解题思路

tips: 把 C 题的 AC 代码中的从大到小排序改成从小到大，其它都不改，提交可以对所有的样例和 $18$ 个点。

实际上这一题是用 DP 方法求解，很容易想到朴素的 DP：设 $f_{i,j}$ 表示当总甜度为 $i$，总咸度为 $j$ 时的 $k$，此时的转移就为

$$
f_{i,j}=\max_{1\le x\le n}^{i\le a_x,j\le b_x}(f_{i,j},f_{i-a_x,j-b_x}+1)
$$

但是 $f$ 数组最大可以达到 $f_{x,y}$，所以时间和空间复杂度方面上都承受不住。这时我们可以换一种思路：设 $f_{i,j,k}$ 表示目前到第 $i$ 道菜，已经吃了 $j$ 道菜，总甜度为 $k$ 的最小咸度，此时的转移方程就为

$$
f_{i,j,k}=\min(f_{i-1,j,k},f_{i-1,j-1,k-a_i}+b_i)
$$

最后倒着枚举吃的菜数 $i$（为了使 $k$ 最大），并且还要枚举甜度 $j$，检查对应的咸度 $f_{n,i,j}$ 是否不超过 $y$，如果是的话，那么 $\min(i+1,n)$ 就是最终答案。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48); return;
}

ll n,x,y,a[81],b[81],f[81][81][10001];

int main()
{
    n=read(); x=read(); y=read();
    for(int i=1; i<=n; ++i) a[i]=read(), b[i]=read();
    memset(f,127,sizeof(f)); f[0][0][0]=0;

    for(int i=1; i<=n; ++i)
    {
        for(int j=0; j<=i; ++j)
        {
            for(int k=0; k<=x; ++k)
            {
                f[i][j][k]=f[i-1][j][k];
                if(j && k>=a[i]) f[i][j][k]=min(f[i][j][k],f[i-1][j-1][k-a[i]]+b[i]);
            }
        }
    }

    for(ll i=n; i>=0; --i)
    {
        for(int j=0; j<=x; ++j)
        {
            if(f[n][i][j]<=y)
            write(min(i+1,n)), exit(0);
        }
    }

    return 0;
}
```

---

## 作者：_O_w_O_ (赞：0)

~~怎么还有人做菜既咸又甜啊。~~

考虑 dp。

我们设 $dp_{i,j,k}$ 表示前 $i$ 个中，甜度为 $j$，咸度为 $k$ 能选的最多盘数，那么我们就可以设 $dp_{0,0,0}=0$，其余为 $+\infty$，转移为 $dp_{i,j,k}=\max\{dp_{i-1,j,k},dp_{i-1,j-a_i,k-b_i+1}\}$。

可是这样是 $O(nxy)$ 的，过不了。

我们发现最终答案一定不大，所以我们交换答案与状态中的一维，设 $dp_{i,j,k}$ 表示前 $i$ 个菜选 $j$ 个，咸度为 $k$ 时的最小酸度，除 $dp_{0,0,0}$ 初始为 $+\infty$，转移方程为 $dp_{i,j,k}=\min\{dp_{i-1,j,k},dp_{i-1,j-1,k-b_i}+a_i\}$，注意只有在甜度满足条件时才能转移。

答案为最大的满足 $dp_{n,i,y}\neq +\infty$ 的 $i$。

那么这样我们就把时间复杂度优化至 $O(n^2x)$，由于 $n$ 很小，可以通过。

---

## 作者：zengziqvan (赞：0)

# 问题简述

有一个人前来~~买瓜~~吃饭，每个饭有糖量和盐量，干饭人有最多吃的糖量和盐量，若糖量与盐量总合超过最多吃的糖量和盐量就会吐，求吃饭的最大个数，使得干饭人会吐或者全吃完。

# 题目分析

所以吃的饭只有两种情况：

- 把所有的饭吃完都没吐。

- 在不吐的情况下吃最多，再吃一个就吐。

所以原问题转化为求最多吃的饭个数，使得干饭人不吐。记答案为 $ans$。

需要输出的结果就是 $\min (n,ans+1)$。

关键在于求 $ans$。

有一个非常暴力的做法：二维费用背包。这里不再赘述。

但二维费用背包时间复杂度是 $\operatorname{O}(n\times \max a_i \times \max b_i)$ 的。

考虑把价值与第一维代价互换，设 $dp_{i,j,k}$ 表示考虑到前 $i$ 个菜，吃了 $j$ 个菜，当前甜度值为 $k$ 所能达到的最小咸度值。

所以答案就是满足 $k\le x$ 且 $dp_{n,j,k}\le y$ 的最大的 $j$，枚举判断即可。

时间复杂度降低到 $\operatorname{O}(n^2 \max a_i)$，可以通过。

```c++
#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
//#define int long long
//#define double long double
#define FOR(i,l,r) for(int i=l;i<=r;++i)
#define ROF(i,r,l) for(int i=r;i>=l;--i)
#define mkp make_pair
#define fr first
#define se second
#define pb push_back
#define cmax(a,b) a=max(a,b)
#define cmin(a,b) a=min(a,b)
using namespace std;
void IOS() {
	ios::sync_with_stdio(false);
	cin.tie(0);
}
void Document() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch^48);ch=getchar();}
	return s*w;
}
inline void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int N=1e4+10;
int n,a,b,w[100],v[100];
int dp[85][85][N];//dp i j k 表示考虑到第 i 道，吃了 j 道，甜度为 k 的最小咸度值。 
main() {
	cin>>n>>a>>b;
	FOR(i,1,n) cin>>w[i]>>v[i];
	memset(dp,0x3f,sizeof dp);
	//dp[0][0][0]=0;
	FOR(i,1,n) {
		ROF(j,i,0) {
			ROF(k,a,0) {
				dp[i][j][k]=dp[i-1][j][k];
				if(k-w[i]>=0&&j>0) dp[i][j][k]=min(dp[i][j][k],dp[i-1][j-1][k-w[i]]+v[i]);
			} 
		}
	}
	ROF(k,n,0) {
		FOR(l,0,a) {
			if(dp[n][k][l]<=b) {
				cout<<(k==n?n:k+1)<<"\n";
				return 0;
			}
		} 
	}
	return 0;
}
```

---

## 作者：lcfollower (赞：0)

和[这题](https://atcoder.jp/contests/abc364/tasks/abc364_c)有点像，只不过一个求最少可以贪心，这题不能贪心。

- 为何不能贪心？

- 因为题目需要满足两个量不超标，当遇到两者相差很大的情况下，完全可以选择甜度（咸度）更大的来保证另一种更小，能够吃到更多的菜。而最小则没有这种情况。



---

考虑 dp，首先把题目的三个量：菜品、甜度、咸度设进状态中。设 $dp_{i ,j ,k}$ 表示前 $i$ 种菜品中甜度（咸度）不超过 $j$（$k$）能吃的最多的菜品数，转移为 $dp_{i ,j ,k} = \max\{dp_{i ,j ,k} ,dp_{i - 1 ,j - a_i ,k - a_i} + 1\}$（$j\ge a_i$，$k\ge b_i$），时间复杂度为 $\mathcal O(NXY)$，会炸。

重新设计状态，把 $X$ 给消除并增加以为 $k$，设 $dp_{i ,j ,k}$ 表示前 $i$ 道菜中吃了 $k$ 碗菜，甜度为 $j$ 的最少咸度。初始化为 $dp_{0,0,0} = 0$。

那么转移为 $dp_{i ,j ,k} = \min\{dp_{i , j ,k} , dp_{i - 1 ,j - a_i ,k - 1} + b_i\}$（$j\ge a_i$，$k\ne 0$），一开始 $dp_{i ,j ,k} = dp_{i - 1 ,j ,k}$。最终答案为 $\max k + 1$（$dp_{n ,j ,k} \le y$）。

因为甜度或咸度超标时最后一晚菜已经吃下去了，所以 $k$ 需要加 $1$，但是最终和 $n$ 比个最小值即可。

时间复杂度为 $\mathcal O(N^2X)$，足以通过本题。


具体细节见[代码](https://atcoder.jp/contests/abc364/submissions/56197477)。

---

## 作者：Wei_Han (赞：0)

### 题目大意

有 $n$ 道菜，每道菜有 $a_i$ 的咸度值和 $b_i$ 的甜度值，求甜度值在 $X$ 以内，咸度值在 $Y$ 以内吃的最多的菜数。

### Solution

先不考虑数据范围，这东西是个比较显然的二维费用背包，直接背包是 $O(nXY)$ 的，好像看到有卡过去的，但是显然不是正解。

考虑优化状态，设 $f_{i,j,k}$ 表示前 $i$ 道菜，选了 $j$ 道，甜度为 $k$ 的最小咸度。那么我们的转移就可以变成：$f_{i,j+1,k}=\min(f_{i-1,j,k-a_i}+b_i)$ 这样转移的时间复杂度就是 $O(n^2Y)$，滚动数组压掉一维，空间就是 $O(nY)$ 的，可以通过。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(register ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(register ll i = a ; i >= b ; -- i )
#define fi first
#define se second
#pragma GCC optimize(2)
using namespace std;
typedef int ll;
const int N=85,M=1e7+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll n,m,f[105][10010],x,y,ai[105],bi[105];
string s,t;
/*
dp(i,j,k) 前 i 个数选了 j 个甜度最小为 k 的最小咸度 
*/

signed main(){
	read(n);read(x);read(y);
	fo(1,i,n) read(ai[i]),read(bi[i]);
	mem(f,0x3f);f[1][0]=0;
	fo(1,i,n)
		Fo(i,j,1)
			Fo(x,k,ai[i])
				f[j+1][k]=min(f[j+1][k],f[j][k-ai[i]]+bi[i]);
	ll ans=0;
	fo(1,i,n) fo(0,j,x) if(f[i][j]<=y) ans=max(ans,i);
	wr(ans);
	return 0;
}	
``````

---

## 作者：PineappleSummer (赞：0)

[[ABC364E] Maximum Glutton](https://atcoder.jp/contests/abc364/tasks/abc364_e)

一看见 $n\le 80$，果断 DP。

设 $dp_{i,j}$ 为吃掉 $i$ 道菜且甜度为 $j$ 的最小咸度。

枚举吃第 $i$ 道菜，当前共吃掉 $j$ 道菜，总甜度为 $k$，能够得到转移：
$$dp_{j,k}=\min(dp_{j,k},dp_{j-1,k-a_i}+b_i)$$

最后统计时枚举 $i,j$，取 $dp_{i,j}\le y$ 中 $i$ 的最大值。答案即为 $\min(i+1,n)$。

[代码](https://atcoder.jp/contests/abc364/submissions/56178875)，时间复杂度 $O(n^2X)$。

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc364_e [ABC364E] Maximum Glutton
---
### 题目大意
类似第三题，给定 $N$ 盘菜和最大能承受的甜度 $X$ 和咸度 $Y$，第 $i$ 盘菜甜度为 $A_i$，咸度为 $B_i$，求最多吃几盘菜。

数据范围：$1 \le N \le 80$，$1 \le X,Y,A_i,B_i \le 10^4$

---
### 题解
首先显然是个 DP，考虑枚举 $A_i$，$B_i$ 和 $N$。但由于 $A_i$ 和 $B_i$ 过大，需要转换枚举对象。我们可以发现 $N$ 非常小，所以我们考虑将甜度值与答案互换，枚举 $B_i$，$M$ 和 $N$。其中 $M$ 表示当前已经选取的菜的数量，dp 值表示最小甜度和。转移式比较明显，具体看代码。

### 代码
```cpp

#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

int dp[100][100][10010];//n, m, b 
int a[110], b[110];
int n, x, y, ans;

int main() {
	memset(dp, 0x3f, sizeof dp);
	scanf("%d%d%d", &n, &x, &y);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i], &b[i]);
	}
	dp[0][0][0] = 0;
	for (int i = 1; i <= n; ++i) {//枚举当前菜 
		for (int j = 0; j <= n; ++j) {//枚举选取过多少菜 
			for (int k = 0; k <= x; ++k) {//枚举甜度值 
				dp[i][j][k] = dp[i - 1][j][k];//不变的情况 
				if (j > 0 && k >= a[i] && dp[i - 1][j - 1][k - a[i]] + b[i] <= y) {
					//^如果选过菜，当前甜度和大于当前菜的甜度值，
					//咸度值加上当前菜的咸度值不超的话，
					//就可以从上一个没选这盘菜的状态转移过来 
					dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - 1][k - a[i]] + b[i]);
				}
			}
		}
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= x; ++j) {
			if (dp[n][i][j] <= y) {//如果当前状态满足条件就更新答案 
				//我们枚举的都合法，但理论上超了才停下，所以可以再吃一盘 
				ans = max(ans, i + 1);
			}
		}
	}
	ans = min(ans, n);//一共有n盘菜，枚举时有可能超标，特判一下 
	printf("%d", ans);
	return 0;
}

```

---

## 作者：SkyLines (赞：0)

## Solution

设 $dp_{i,j}$ 为 $i$ 个菜品甜度 $j$ 的最小辣度，设转移到第 $k$ 个菜品，则转移方程如下：

$$dp_{i,j}=\min(dp_{i,j},dp_{i-1,j-A_k}+B_k)$$

如果满足 $dp_{i,j} \le y$，则可行。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 85, M = 10005;
int n, x, y, dp[N][M], a, b;
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int main(){
	scanf("%d %d %d", &n, &x, &y);
	for(int i = 1; i < N; i++) for(int j = 0; j < M; j++) dp[i][j] = 1e9;
	for(int i = 1; i <= n; i++){
		scanf("%d %d", &a, &b);
		for(int j = i; j >= 1; j--) for(int k = x; k >= a; k--) dp[j][k] = min_(dp[j][k], dp[j - 1][k - a] + b);
	}
	for(int i = n - 1; i >= 1; i--){
		for(int j = 0; j <= x; j++){
			if(dp[i][j] <= y){
				printf("%d", i + 1);
				return 0;
			}
		}
	}
	printf("1");
	return 0;
}
```

---

## 作者：__Q_w_Q__ (赞：0)

# Maximum Glutton 题解

### 题目大意

有 $N$ 盘食物，求在食物的甜度不超过 $X$ 及咸度不超过 $Y$ 的情况下最多能吃几盘食物。

## 思路

一眼可以看出，本题无法贪心。那就只能暴力枚举了。

这就需要请出动态规划了。

### 0pts

那么确定了算法时动态规划之后就非常简单了，先来写转移方程



$F_{i,j,k}$ 表示在选到了第 $i$ 盘食物，且总甜度和总咸度**恰好**是 $j$ 和 $k$。



$F_{i,j,k}$ 的值即为在如上条件下最多能吃几盘食物。



$$F_{i,j,k} = max \begin{cases}F_{i+1,j,k} \\\ F_{i+1,j+a_i,k+b_i}+1 \end{cases}$$

*PS: $a_i$ 表示第 $i$ 盘食物的甜度 $b_i$ 表示第 $j$ 盘食物的咸度*



然后一看数据范围：$$1\leq X,Y \leq 10000$$

 ``int F[80][10000][10000]``  

![pkXe0AS.png](https://s21.ax1x.com/2024/08/01/pkXe0AS.png)

### 100pts

这就需要我们考虑优化转移方程。

那么怎么优化呢？还是把目光移到数据范围上：$1\leq N \leq 80$

$N$ 的范围是可以接受的，因此我们可以**交换 $F$ 数组的键和值** ，把咸度/甜度作为表示的值，而将吃了几盘食物作为下标，也就是说，转移方程可以优化为如下形态：



$F_{i,j,k}$ 表示在前 $i$ 盘食物中选了**恰好** $j$ 盘，且总甜度**恰好**是 $j$。



$F_{i,j,k}$ 的值即为在如上条件下最小的咸度。



$$F_{i,j,k} = min \begin{cases}F_{i+1,j+1,k+a_i} \\ F_{i,j,k}+b_i \end{cases}$$

*PS: $a_i$ 表示第 $i$ 盘食物的甜度 $b_i$ 表示第 $j$ 盘食物的咸度*



## Code

如果推出了转移方程，那么剩下的代码就很简单了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100],b[100]; 
signed main(){
	int n,x,y;
	cin>>n>>x>>y;
	for(int i=0;i<n;i++){
		cin>>a[i]>>b[i];
	}
	vector f(n+1,vector(n+1,vector<int>(x+1,1e9))) ;
	f[0][0][0]=0;// 前i个中选了k个 甜度为j 时的咸度 
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			for(int k=0;k<=x;k++){
				f[i+1][j][k]=min(f[i][j][k],f[i+1][j][k]);
				if(k+a[i]<=x){
					f[i+1][j+1][k+a[i]]=min(f[i+1][j+1][k+a[i]],f[i][j][k]+b[i]);
				}
			} 
		}
	} 
	for(int i=n;i>=0;i--){
		for(int j=0;j<=x;j++){
			if(f[n][i][j]<=y){
				cout<<min(i+1,n)<<endl;
				return 0;
			}
		}
	}
	return 0;
}
```

~~本篇题解大量参考了 Atcoder 的官方题解~~

---

## 作者：zrl123456 (赞：0)

[[ABC364E] Maximum Glutton ](https://www.luogu.com.cn/problem/AT_abc364_e)

题目考察：dp，背包。  
题目简述：  
有 $n$ 个物品，拥有第 $i$ 个物品需要花费 $a_i$ 的 A 代价，$b_i$ 的 B 代价。在满足 A 代价不超过 $x$，B 代价不超过 $y$ 的基础上，他会继续选择下一个物品。直到 A 代价大于 $x$ 或 B 代价大于 $y$。求最多拥有多少件物品。  
数据范围：  
- $1\le n\le 80$
- $1\le x,y\le 10^4$
- $\forall i\in[1,n],1\le a_i,b_i\le 10^4$
---
首先我们设在 A 代价不超过 $x$，B 代价不超过 $y$ 的情况下最多选 $tmp$ 个物品，则最终可以选择 $\min(n,tmp+1)$ 个物品。  

暴力 dp 的话，设状态 $f_{i,j,k}$ 为选择到第 $i$ 个物品，花费了 $j$ 的 A 代价和 $k$ 的 B 代价所能选择的最大物品数量，则转移方程为：  
$$f_{i,j,k}=\max(f_{i-1,j,k},f_{i-1,j-a_i,k-b_i}+1)$$
但时间复杂度为 $\Theta(nxy)$，这样即使压去第一维也无法通过。  

我们注意到他最多选 $n$ 个物品，价值非常小。那么设 $f_{i,j,k}$ 为选到第 $i$ 个物品，A 代价花费了 $j$，选出了 $k$ 个物品所花费的最小 B 代价，那么这样得到状态转移方程：  
$$f_{i,j,k}=\min(f_{i-1,j,k},f_{i-1,j-a_i,k-1}+b_i)$$
最后的时候我们压去第一维，这样时间复杂度为 $\Theta(n^2x)$，空间复杂度为 $\Theta(nx)$，可以通过。  

[代码](https://atcoder.jp/contests/abc364/submissions/56029815)

---

## 作者：IronMen (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc364_e)

[AtCoder链接](https://atcoder.jp/contests/abc364/tasks/abc364_e)

---
## 题目
高桥为斯努克准备了 $N$ 道菜。菜的编号从 $1$ 到 $N$，菜 $i$ 的**甜度**为 $A_i$，**咸度**为 $B_i$。

高桥可以按照自己喜欢的顺序排列这些菜。斯努克会按照排列顺序吃掉这些菜，但如果他吃过的菜的总甜度超过 $X$ 或总咸度超过 $Y$，他就不会再吃任何菜。

高桥希望斯努克尽可能多吃菜。求斯努克最多吃多少道菜。

---
## 思路
除最后一道菜，前面的菜的顺序不重要。

考虑一个显然 dp：用 $f(i,x,y)$ 表示考虑了前面 $i$ 道菜，当前甜度总和为 $x$，咸度总和为 $y$，此时最多能吃多少。时间复杂度为 $O(NXY)$。

因为 $Y$ 比 $N$ 大，所以考虑交换 dp 下标和 dp 值的方法。

更改状态，定义 $f(i,x,k)$ 为考虑了前面 $i$ 道菜，当前总甜度为 $x$，若吃了 $k$ 个菜，咸度最小值为多少。

对 $f(i-1,x,k)$，考虑第 $i$ 个菜要不要吃：
1. 不吃，那么 $f(i-1,x,k) \to f(i,x,k)$。
2. 吃，那么 $f(i-1,x,k)+b_i \to f(i,x+a_i,k+1)$，此时的前提是 $x \le X,f(i-1,x,k) \le Y$。

计算答案时，枚举最后一个依然满足条件的状态 $x \le X,f(n,x,k) \le Y$，答案即为 $\min(n,k+1)$。

时间复杂度为 $O(N^2X)$。

---
### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, X, Y, f[100][20010][100], a, b;

int main()
{
	scanf("%d %d %d", &n, &X, &Y);
	memset(f, 0x3f, sizeof(f));
	f[0][0][0] = 0;
	for (int i = 1; i <= n; i ++ )
	{
		scanf("%d %d", &a, &b);
		for (int k = 0; k < i; k ++ )
		{
			for (int x = 0; x <= X; x ++ )
			{
				f[i][x][k] = min(f[i][x][k], f[i - 1][x][k]);
				if (x + a <= X && f[i - 1][x][k] + b <= Y)
					f[i][x + a][k + 1] = min(f[i][x + a][k + 1], f[i - 1][x][k] + b);
			}
		}
	}
	for (int k = n; ~k; k -- )
	{
		for (int x = 0; x <= X; x ++ )
		{
			if (f[n][x][k] <= Y)
			{
				cout << min(n, k + 1) << '\n';
				return 0;
			}
		}
	}
}
```

---

