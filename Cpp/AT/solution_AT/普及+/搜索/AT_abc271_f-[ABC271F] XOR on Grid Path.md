# [ABC271F] XOR on Grid Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc271/tasks/abc271_f

$ N $ 行 $ N $ 列のマス目があり、上から $ i\ \,\ (1\ \leq\ i\ \leq\ N) $ 行目、左から $ j\ \,\ (1\ \leq\ j\ \leq\ N) $ 列目のマスを $ (i,\ j) $ と表します。  
 マス $ (i,\ j) $ には非負整数 $ a_{i,\ j} $ が書かれています。

マス $ (i,\ j) $ にいるとき、マス $ (i+1,\ j),\ (i,\ j+1) $ のいずれかに移動することができます。ただし、マス目の外に出るような移動はできません。

マス $ (1,\ 1) $ から移動を繰り返してマス $ (N,\ N) $ にたどり着く方法であって、通ったマス（マス $ (1,\ 1),\ (N,\ N) $ を含む）に書かれた整数の排他的論理和が $ 0 $ となるようなものの総数を求めてください。

 排他的論理和とは 整数 $ a,\ b $ の排他的論理和 $ a\ \oplus\ b $ は、以下のように定義されます。 - $ a\ \oplus\ b $ を二進表記した際の $ 2^k\ \,\ (k\ \geq\ 0) $ の位の数は、$ a,\ b $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。

 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります（二進表記すると $ 011\ \oplus\ 101\ =\ 110 $）。  
 一般に $ k $ 個の整数 $ p_1,\ \dots,\ p_k $ の排他的論理和は $ (\cdots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \cdots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ \dots,\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 20 $
- $ 0\ \leq\ a_{i,\ j}\ \lt\ 2^{30}\ \,\ (1\ \leq\ i,\ j\ \leq\ N) $
- 入力は全て整数

### Sample Explanation 1

次の二通りの方法が条件を満たします。 - $ (1,\ 1)\ \rightarrow\ (1,\ 2)\ \rightarrow\ (1,\ 3)\ \rightarrow\ (2,\ 3)\ \rightarrow\ (3,\ 3) $ - $ (1,\ 1)\ \rightarrow\ (2,\ 1)\ \rightarrow\ (2,\ 2)\ \rightarrow\ (2,\ 3)\ \rightarrow\ (3,\ 3) $

## 样例 #1

### 输入

```
3
1 5 2
7 0 5
4 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 2
2 1```

### 输出

```
0```

## 样例 #3

### 输入

```
10
1 0 1 0 0 1 0 0 0 1
0 0 0 1 0 1 0 1 1 0
1 0 0 0 1 0 1 0 0 0
0 1 0 0 0 1 1 0 0 1
0 0 1 1 0 1 1 0 1 0
1 0 0 0 1 0 0 1 1 0
1 1 1 0 0 0 1 1 0 0
0 1 1 0 0 1 1 0 1 0
1 0 1 1 0 0 0 0 0 0
1 0 1 1 0 0 1 1 1 0```

### 输出

```
24307```

# 题解

## 作者：Felix72 (赞：6)

~~赛时没切，所以来写题解了~~

## [原题通道](https://atcoder.jp/contests/abc271/tasks/abc271_f)

首先看范围可以发现这是一道搜索题，然而 $O(2^{2n})$ 一定会 T。  

可以考虑双向往中间搜索，这样时间变为 $O(2^n)$。第一次搜索从 $(1,1)$ 开始，在对角线时 $(x+y=n+1)$ 停止，用 map 和 pair 计数。第二次从 $(n,n)$ 开始，在对角线时更新答案就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair < pair < long long, long long >, long long > PII;
long long n, a[25][25], ans;
map < PII, long long > mp;
void dfs1(long long x, long long y, long long cur)
{
	cur = cur ^ a[x][y];
	if(x + y == n + 1)
	{
		++mp[{{x, y}, cur}];
		return ;
	}
	dfs1(x + 1, y, cur);
	dfs1(x, y + 1, cur);
}
void dfs2(long long x, long long y, long long cur)
{
	if(x + y == n + 1)
	{
		ans += mp[{{x, y}, cur}];
		return ;
	}
	cur = cur ^ a[x][y];
	dfs2(x - 1, y, cur);
	dfs2(x, y - 1, cur);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			cin >> a[i][j];
	dfs1(1, 1, 0);
	dfs2(n, n, 0);
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：翼德天尊 (赞：3)

数据范围太小，但是如果暴力的话， $O(2^{2n})$ 的复杂度又太高，稍微有点接受不了。

于是考虑异或的一个性质，如果路径异或和为 $0$，则随意找一个切线切开路径就可以得到两条异或和相同的路径。

所以我们可以考虑一个叫作 meet in the middle 的 trick，将网格从右上到左下斜着切开，分别对于左上和右下到对角线作一遍 dfs。

具体来说，我们可以对于这条对角线的每一个方格开一个 map，将左上走到方格 $p$ 的所有路径的异或和都存在方格 $p$ 的 map 里。

从右下到左上搜的时候只需要从 map 中进行查询即可。

时间复杂度 $O(n2^n\log 2^n)$，常数好像不大。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=24;
int n,a[N][N];
ll ans;
map<int,int> ma[N];
ll read(){
	ll w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
void dfs1(int x,int y,int now){
	if (x+y==n){
		ma[x][now]++;
		return;
	}
	dfs1(x+1,y,now^a[x+1][y]);
	dfs1(x,y+1,now^a[x][y+1]);
}
void dfs2(int x,int y,int now){
	if (x+y==n){
		ans+=ma[x][now];
		return;
	}
	dfs2(x-1,y,now^a[x][y]);
	dfs2(x,y-1,now^a[x][y]);
}
int main(){
	n=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			a[i][j]=read();
	dfs1(1,1,a[1][1]);
	dfs2(n,n,0);
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

首先你一路爆搜过去结果肯定是对的。

但是你从左上角走到右下角需要 $2(n-1)$ 步，而每一步有两种选择，则总共有 $2^{2(n-1)}$ 种路径~~搜不死你~~。

如何优化呢？我们连接右上角和左下角，钦定这一条对角线上的点是“转折点”。

当我们的搜搜搜程序到达某个转折点时，就可以了！

再钦定一个计数器 $f[x][y][val]$，表示从左上角到转折点 $(x,y)$ 时路径异或值为 $val$ 的方案数。

由于异或有性质：$a\oplus a=0$（$\oplus$ 表示异或，即 `^` 运算符）

那么只要我们再从右下角搜搜搜到转折点，然后看能结出几条路就可以了。

```cpp
#include <map>
#include <stdio.h>
int val[25][25];
int n,i,j;
long long res;
std::map<long long,int> f[25][25];//注意long long。
const int dx[5]={0,1,0,-1,0};
const int dy[5]={0,0,1,0,-1};
inline void fill(int x,int y,int dep)//从左上角搜！搜！搜！
{
	dep^=val[x][y];//注意这两段程序中这句话的位置是不同的。
	if(x+y==n+1)
	{
		++f[x][y][dep];
		return ;
	}
	fill(x+dx[1],y+dy[1],dep);
	fill(x+dx[2],y+dy[2],dep);
	return ;
}
inline void solve(int x,int y,int dep)//从右下角搜！搜！搜！
{
	if(x+y==n+1)//对角线性质：行列数相加为n+1.
	{
		res+=f[x][y][dep];//现在路上是dep，dep^dep=0
		return ;
	}
	dep^=val[x][y];
	solve(x+dx[3],y+dy[3],dep);
	solve(x+dx[4],y+dy[4],dep);
}
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;++i)
		for(j=1;j<=n;++j)
			scanf("%d",val[i]+j);
	fill(1,1,0);
	solve(n,n,0);
	printf("%lld",res);
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

现在觉得自己是个脑残，比赛时用 `vector` 维护然后时超了...

首先分析题目，只可以向右或者向下，总共要走 $2n-2$ 步，暴力的时间复杂度略低于 $O(2^{2n-2})$，实际上是一个组合数，但是确实是过不了的。

但是我们可以考虑将这 $2n-2$ 步分解为两个 $n-1$ 步，一半从 $(1,1)$ 往右下方向走，一半从 $(n,n)$ 往左上方向走。

我们在 $(1,1)$ 走到尽头的时候，将累计的路径上的异或和标记在格子上，这里建议使用 `map`，我就是脑残写 `vector` 挂了。

然后在 $(n,n)$ 走到尽头时，我们就可以查询格子上记录的等同于 $(n,n)$ 路径的异或和的路径数量有多少。

由于 $x \oplus x =0$，所以两条异或和相等的路径融起来就是异或和为零的路径，问题解决。

这个算法叫做 Meet in the Middle，是好的。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[105][105],ans;
map<long long,long long>v[105][105];
void dfs(long long x,long long y,long long sum,long long k)
{
    sum^=a[x][y];
    if(k==0)
    {
        v[x][y][sum]++;
        return;
    }
    dfs(x+1,y,sum,k-1);
    dfs(x,y+1,sum,k-1);
}
void dfs2(long long x,long long y,long long sum,long long k)
{   
    if(k==0)
    {
        ans+=v[x][y][sum];
        return;
    }
    sum^=a[x][y];
    dfs2(x-1,y,sum,k-1);
    dfs2(x,y-1,sum,k-1);
}
int main()
{
  //  freopen("grid.in","r",stdin);
  //  freopen("grid.out","w",stdout);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)scanf("%lld",&a[i][j]);
    }
    dfs(1,1,0,n-1);
    dfs2(n,n,0,n-1);
    printf("%lld",ans);
}
```

---

## 作者：uid_310801 (赞：0)

爆搜肯定是不行的。考虑优化。

#### 本题要使用 **Meet-In-Middle** 算法。

通俗来说来说就是从起点正着 dfs 一半，从终点反着 dfs 一半，最后在中间汇总答案。

首先要知道一个性质：$x\otimes x=0$.

我们在矩阵中从右上到左下画一条对角线，代表搜索到这里时要统计答案。

开 $n$ 个映射表。记 $f_{i,j}$ 表示第一遍搜索到第 $i$ 行的对角线上的格子的异或和为 $j$ 的方案数有多少。这是好求的。

然后倒着搜索一遍，顺路统计答案。假设当前搜到了第 $i$ 行的对角线上的格子**右边或下面的格子**，异或和为 $j$，那么答案就加上 $f_{i.j}$.

时间复杂度 $O(2^{\frac {n+m} 2})=O(2^n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=22;
ll n,a[N][N],ans;
map<ll,ll> b[N];
void dfs1(ll x,ll y,ll p){
	if(x+y==n+1){
		b[x][p]++;
		return;
	}
	dfs1(x+1,y,p^a[x+1][y]);
	dfs1(x,y+1,p^a[x][y+1]);
}
void dfs2(ll x,ll y,ll p){
	if(x+y==n+2){
		ans+=b[x][p]+b[x-1][p];
		return;
	}
	dfs2(x-1,y,p^a[x-1][y]);
	dfs2(x,y-1,p^a[x][y-1]);
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%lld",&a[i][j]);
		}
	}
	dfs1(1,1,a[1][1]);
	dfs2(n,n,a[n][n]);
	printf("%lld\n",ans);
}
```


---

## 作者：xiaoPanda (赞：0)

## F - XOR on Grid Path

### Problem

给出一个 $n\times n$ 的矩阵，起点在 $(1,1)$ ，终点在 $(n,n)$，每次可以向下或向右走，求要多少条路径满足路径上的数异或值为 $0$。

$1\le n\le 20$

### Solution

数据很小，考虑 DFS（注意到状态很大，所以难以 dp），直接爆搜是 $2^{2n}$ 的，难以通过，考虑用双向 DFS （又叫 meet-in-the-middle）优化。

从起点开始，对于每个点 $(i,j)$，用  `map` 记一下当前异或值 $v$ 的方案个数，只搜 $n$ 步，`map` 最多只有 $2^n$ 个，时间复杂度为 $O(2^n\log 2^n)=O(2^nn)$。

然后再从终点开始搜索，如果搜玩 $n$ 步以后到了 $(i,j)$ ，异或值为 $v$ ，那么答案就可以加上之前搜到 $(i,j)$ 并且异或值为 $v$ 的个数了，因为一个数异或自己等于 $0$，时间复杂度仍然是 $O(2^nn)$。

### Code
```cpp
const int N=20;
int n,a[N+10][N+10];
map<int,int> p[N+10][N+10];
void dfs1(int x,int y,int v) {
    v^=a[x][y];
    if(x+y==n+1) return p[x][y][v]++,void();
    if(x<=n) dfs1(x+1,y,v);
    if(y<=n) dfs1(x,y+1,v);
}
ll ans=0;
void dfs2(int x,int y,int v) {
    if(x+y==n+1) return ans+=p[x][y][v],void();
    v^=a[x][y];
    if(x>=1) dfs2(x-1,y,v);
    if(y>=1) dfs2(x,y-1,v);
}
int main() {
    n=read();
    FOR(i,1,n) FOR(j,1,n) a[i][j]=read();
    dfs1(1,1,0),dfs2(n,n,0);
    printf("%lld\n",ans);
}
```


---

