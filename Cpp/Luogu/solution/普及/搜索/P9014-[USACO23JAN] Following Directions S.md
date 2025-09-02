# [USACO23JAN] Following Directions S

## 题目描述

**注：本题时限为 8s，是默认时限的四倍。**

Farmer John 有一个正方形的草地，草地被划分为了 $(N + 1) \times (N + 1)(1 \leq N \leq 1500)$ 的格子。设 $(i, j)$ 为从上到下、从左到右第 $i$ 行，第 $j$ 列的格子。每个满足 $1 \leq i, j \leq n$ 的格子 $(i, j)$ 之中都住着一头牛，而且每个这样的格子上都有一个路标指向右或下。除此之外，所有满足 $i = N + 1$ 或 $j = N + 1$ 的格子，除了 $(N + 1, N + 1)$ 都会有一个饲料桶。牛在每个饲料桶进食需要的价格不同；位置 $(i, j)$ 上的桶喂饱一只牛需要价格 $c_{i, j}(1 \leq c_{i, j} \leq 500)$。

每天晚饭时间，Farmer John 摇响晚餐铃时，所有牛都沿着路标的指向前进，直到它们遇到了饲料桶，之后它们会在它们自己遇到的饲料桶那里进食。第二天，所有牛又会回到自己原来的位置。

为了维持预算，Farmer John 想要知道每天喂食需要的价钱。然而，每天晚饭之前，总会有一头牛 $(i, j)$ 翻转它那里的路标（原来向下则变成向右，反之亦然）。被翻转的路标指向将在后面的日子里保持不变，除非它又被进行了翻转。

给出每天被翻转的路标的坐标，请输出每天喂食需要的价格（总共有 $Q$ 天，$1 \leq Q \leq 1500$）。

## 说明/提示

### 样例 1 解释

在第一次翻转之前，喂养在位置 $(1, 1)$ 和 $(1, 2)$ 的牛需要的价格都为 $1$，喂养在 $(2, 1)$ 的牛需要的价格为 $100$，喂养在 $(2, 2)$ 的牛需要的价格为 $500$。总价格为 $602$。第一次翻转后，在 $(1, 1)$ 处的路标由 `R` 变为 `D`，此时在位置 $(1, 1)$ 的牛喂养的价格变为 $100$（其它牛的价格没有变化），所以总价为 $701$。第二次和第三次翻转都在来回翻转同一个路标。第四次翻转后，在位置 $(1, 1)$ 和位置 $(2, 1)$ 的牛喂养的价格变为 $500$，总价变为 $1501$。


- 测试点 $2 - 4$ 中：$1 \leq N, Q \leq 50$。

- 测试点 $5 - 7$ 中：$1 \leq N, Q \leq 250$。

- 测试点 $2 - 10$ 中：每个路标初始朝向以及被翻转的路标为随机生成。

- 测试点 $11 - 15$ 中：无特殊条件。

## 样例 #1

### 输入

```
2
RR 1
DD 10
100 500
4
1 1
1 1
1 1
2 1```

### 输出

```
602
701
602
701
1501```

# 题解

## 作者：yujinning (赞：10)

# 前言

一道 USACO-Ag 的题目，T2。

总体难度不大，~~码量惊人~~。


# 解题

首先理解题意。

* 刚开始每个格子都有一个方向标。

* 每次操作修改一个方向标，并实时更新答案。

样例答案如下图所示。

![样例1](https://cdn.luogu.com.cn/upload/image_hosting/tj8eijii.png)

# 解法


可以注意到，对于刚开始的图，每个点所对的饲料桶是确定的。

若将竖列的饲料桶标记为 $1\sim n$，横行的饲料桶标记为 $n+1\sim 2\times n$，则对于每个点，刚开始都有一个确定的饲料桶，可以看成根。

如果把一张图看做成一片森林，则对于样例而言，$(1,1), (1,2)$ 的根为 $1$，$(2,1)$ 的根为 $3$，$(2,2)$ 的根为 $4$。

* 初始计算：对于每个根依次遍历，对于竖列的根第 $n$ 列必须为 $R$，对于横行的根第 $n$ 行必须为 $D$，记录每个点的根，每个根和点的子树大小，每个节点最多遍历一遍，时间复杂度 $O(n^2)$；计算为每个根的子树大小乘对应饲料桶的值。

* 修改计算：对于定点，这个点的子树从原本指向的点的根变为现在指向的点，若原根饲料桶大小为 $i$，现根饲料桶大小为 $j$，上一次操作答案为 $ans$，这个点的子树大小为 $sz$，则操作后答案为 $ans+(j-i)\times sz$，同时遍历子树，修改根。每次操作可以理解为一棵树中的一棵子树被接到了另一棵树里。

* 每次计算实际最多遍历 $2n-1$ 遍，遍历 $Q$ 次，共遍历 $2nQ-Q$ 次。


计算下来，时间复杂度和为 $O(n^2+nQ)$。

# 代码

本代码内为方便表示点，将点对 $(i,j)$ 表示为数 $(i-1)\times n+j$，可以将所有点表示为 $1-n^2$ 内的数。

另外，给出一组较强的调试数据。

```cpp
3
RRR 10
DDR 20
RRD 30
40 50 60
4
3 3
1 1
3 3
1 1
```
输出：

```cpp
350
200
220
400
350
```
-----

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1509;
ll n,Q,p[N*2],sz[N*N+2*N],f[N*N+2*N],ans;
char a[N][N];
vector<ll> son[N*N+2*N];
inline ll id(ll x,ll y){
	if(x<=n&&y<=n) return (x-1)*n+y;
	if(x==n+1) return n*n+n+y;
	return n*n+x;
}
inline void dfs(ll x,ll y,ll fa){
	ll ider=id(x,y),iderx=id(x-1,y),idery=id(x,y-1);
	sz[ider]=1;
	f[ider]=fa;
	if(a[x][y-1]=='R'){
		son[ider].push_back(idery);
		dfs(x,y-1,fa);
		sz[ider]+=sz[idery];
	}
	if(a[x-1][y]=='D'){
		son[ider].push_back(iderx);
		dfs(x-1,y,fa);
		sz[ider]+=sz[iderx];
	}
}
inline void dfs_bao(ll x,ll y,ll fa,ll cha){
    ans+=cha;
    f[id(x,y)]=fa;
    if(a[x][y-1]=='R')
		dfs_bao(x,y-1,fa,cha);
	if(a[x-1][y]=='D')
		dfs_bao(x-1,y,fa,cha);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(register ll i=1;i<=n;i++){
		for(register ll j=1;j<=n;j++) cin>>a[i][j];
		cin>>p[i];
	}
	for(register ll i=n+1;i<=2*n;i++) cin>>p[i];
	for(register ll i=1;i<=n;i++){
		if(a[i][n]=='R'){
		    son[n*n+i].push_back(id(i,n));
			dfs(i,n,i);
			sz[n*n+i]=sz[id(i,n)];
		}
	}
	for(register ll i=n+1;i<=2*n;i++){
		if(a[n][i-n]=='D'){
			son[n*n+i].push_back(id(n,i-n));
			dfs(n,i-n,i);
			sz[n*n+i]=sz[id(n,i-n)];
		}
	}
	for(register ll i=1;i<=2*n;i++)
		ans+=p[i]*sz[n*n+i];
	cout<<ans<<endl;
	for(register ll i=1;i<=n;i++){
		f[id(n+1,i)]=i+n;
		f[id(i,n+1)]=i;
	}
	int q=0;
	cin>>Q; q=Q;
	while(Q--){
		ll opx,opy;
		cin>>opx>>opy;
		ll faxyer=0;
		if(a[opx][opy]=='R') faxyer=f[id(opx+1,opy)],a[opx][opy]='D';
		else faxyer=f[id(opx,opy+1)],a[opx][opy]='R';
		ll val=p[faxyer];
		ll cha=val-p[f[id(opx,opy)]];
		dfs_bao(opx,opy,faxyer,cha);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Nuyoah_awa (赞：7)

### 题目大意

给定一个 $n+1$ 行 $n+1$ 列的地图，前 $1 \sim n$ 行 $1 \sim n$ 列每个点一只奶牛和一个路标，路标指向右边或下边，最后一行和最后一列有草料，每个草料有对应的价格，每头奶牛都会沿着路标去寻找草料。求每天喂养所有奶牛的总成本。然而，在每天晚饭前，一些奶牛 $(i,j)$ 会翻转路标的方向（从右到下，反之亦然）。在接下来的几天里，路标也保持在这个方向上。

### 题目分析

#### 解法一

从每头奶牛开始遍历，求出这头奶牛的吃饭代价，每次更改都遍历一遍。

但是最坏情况下时间效率是 $O ( n ^ 3 \times q ) $ 的。

#### 解法二

我们可以发现每头奶牛都只能向右和向下走，所以每次更改一个路标都只会影响它左上的奶牛吃草的代价，每次更改后只需遍历它左上的点。

#### 解法三

上两个解法每个奶牛都需要花 $O(n)$ 去遍历，一共就是 $O(n^3)$，会重复遍历很多点，太慢了。于是我们想每个奶牛都唯一对应着一个草料，如果从每个草料开始遍历就不会重复遍历点了，就是 $O(n^2)$ 的时间效率。

所以可以考虑从最后一行和最后一列向左上 dfs 从而知道每个点的最终代价。对于每次修改，依然向左上 dfs 更改它所改变的点的最终代价。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1505;
long long n, ans, a[N][N], q, x, y;
char c[N][N];
bool cnt[N][N];

void dfs(long long x, long long y, long long sum)
{
	if(x == 0 || y == 0)
		return ;
	a[x][y] = sum;
	ans += sum;
	if(c[x-1][y] == 'D')
		dfs(x-1, y, sum);
	if(c[x][y-1] == 'R')
		dfs(x, y-1, sum);
	return ;
}

void dfs1(long long x, long long y, long long sum)
{
	if(x == 0 || y == 0)
		return ;
	ans -= a[x][y];
	a[x][y] = sum;
	ans += a[x][y];
	if(c[x-1][y] == 'D')
		dfs1(x-1, y, sum);
	if(c[x][y-1] == 'R')
		dfs1(x, y-1, sum);
	return ;
}

int main(int argc, char** argv)
{
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= n;j++)
			cin >> c[i][j];
		scanf("%d", &a[i][n+1]);
	}
	for(int i = 1;i <= n;i++)
		scanf("%d", &a[n+1][i]);
	for(int i = 1;i <= n;i++)
	{
		if(c[i][n] == 'R')
			dfs(i, n, a[i][n + 1]);
		if(c[n][i] == 'D')
			dfs(n, i, a[n + 1][i]);
	}
	printf("%d\n", ans);
	cin >> q;
	while(q--)
	{
		cin >> x >> y;
		if(c[x][y] == 'R')
		{
			c[x][y] = 'D';
			ans -= a[x][y];
			a[x][y] = a[x+1][y];
			ans += a[x][y];
			dfs1(x, y, a[x][y]);
		}
		else
		{
			c[x][y] = 'R';
			ans -= a[x][y];
			a[x][y] = a[x][y+1];
			ans += a[x][y];
			dfs1(x, y, a[x][y]);
		}
		cout << ans << endl;
	}
	return 0;
}

```

---

## 作者：EricWan (赞：7)

先暴力求解第一个答案，$O(n^2)$，记录 $cow_{i, j}$ 为经过 $(i, j)$ 的牛数。

之后对于一次操作，更新从当前节点开始走两个不同方向是的两条路径上的 $cow$ 和答案即可。

更具体的：

假设一个走到 $(i,j)$ 的奶牛在改变路牌前经过 $(bax_1, bay_1), (bax_2, bay_2), ..., (bax_{brlen}, bax_{brlen})$，到达 $(bex, bey)$。

改变路牌后就需要经过 $(aax_1, aay_1), (aax_2, aay_2), ..., (aax_{arlen}, bax_{arlen})$，到达 $(aex, aey)$。

那么结果的计算为

$$ans = ans - cow_{i, j} \times c_{bex, bey} + cow_{i, j} \times c_{aex, aey}
$$

而对于 $cow_{bax_1, bay_1}, cow_{bax_2, bay_2}, ..., cow_{bax_{brlen}, bax_{brlen}}$，每个减少 $cow_{i, j}$，对于 $cow_{aax_1, aay_1}, cow_{aax_2, aay_2}, ..., cow_{aax_{arlen}, aax_{arlen}}$，每个增加 $cow_{i, j}$。

这题好好想想都能做，没啥太多可说的，时间 $O(n^2 + n \times q)$。

至今不明白为什么给 8 秒。

---

## 作者：FFTotoro (赞：4)

因为本题时限高达 $8s$，我们就大胆地想如何较为简单地维护本题的操作。

显然，每一次翻转标志操作，为了减少运算次数，我们只需更改本次操作有影响到的坐标即可。

为了便利解题，我们定义几个数组：

- $f_{x,y}$ 表示初始坐标为 $(x,y)$ 的奶牛能吃到的饲料的价值；

- $r_{x,y}$ 表示吃到饲料需要经过坐标 $(x,y)$ 的奶牛头数（包括坐标为 $(x,y)$ 的奶牛）；

同时，我们定义一个点的“前驱”为可以通过一步直接走到这个坐标的坐标，“后继”为这个坐标能一步走到的下一个坐标。

第一次操作前，先预处理出 $f,r$ 数组，暴力搜索求出所有奶牛吃到的饲料的价值和（记为 $s$）。

考虑每次操作后，$f,r$ 数组和答案 $s$ 会怎么改变；不妨设改变的坐标为 $(x,y)$，且路标是由“向下”改为“向右”（“向右”变“向下”同理）：

- 对于 $f$ 数组：首先 $f_{x,y}$ 要从 $f_{x+1,y}$ 变为 $f_{x,y+1}$。其次吃饲料必须经过 $(x,y)$ 的所有奶牛的 $f$ 的值也需要相应的改变，可以通过一次 dfs 实现；

- 对于 $c$ 数组：可以看出必须经过 $(x+1,y)$ 的奶牛减少了 $c_{x,y}$ 头，必须经过 $(x,y+1)$ 的奶牛增加了 $c_{x,y}$ 头，同时它们的后继、后继的后继……的 $c$ 的值也要更新，同样可以通过 dfs 实现；

- 对于答案 $s$：因为必须经过 $(x,y)$ 的奶牛有 $c_{x,y}$ 头，而这些奶牛坐标的 $f$ 的值都由 $f_{x+1,y}$ 变为了 $f_{x,y+1}$，所以 $s\leftarrow s+c_{x,y}(f_{x,y+1}-f_{x+1,y})$；每次操作后输出 $s$ 即可。

放代码：

```cpp
/*
ID: CrowMatrix
TASK: Following Directions
LANG: C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1502][1502],f[1502][1502],r[1502][1502];
void dfs(int x,int y,int u){
  f[x][y]=u; r[x][y]=1;
  if(x&&a[x-1][y]==-1)dfs(x-1,y,u),r[x][y]+=r[x-1][y];
  if(y&&a[x][y-1]==-2)dfs(x,y-1,u),r[x][y]+=r[x][y-1];
}
void update1(int x,int y,int u){
  f[x][y]=u;
  if(a[x-1][y]==-1)update1(x-1,y,u);
  if(a[x][y-1]==-2)update1(x,y-1,u);
}
void update2(int x,int y,int u){
  r[x][y]+=u;
  if(a[x][y]==-1)update2(x+1,y,u);
  if(a[x][y]==-2)update2(x,y+1,u);
}
main(){
  ios::sync_with_stdio(false);
  int n,s=0; cin>>n;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      char c; cin>>c;
      if(c=='D')a[i][j]=-1;
      else a[i][j]=-2;
    }
    cin>>a[i][n+1];
  }
  for(int i=1;i<=n;i++)cin>>a[n+1][i];
  for(int i=1;i<=n;i++)dfs(i,n+1,a[i][n+1]),dfs(n+1,i,a[n+1][i]);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)s+=f[i][j];
  cout<<s<<endl;
  int q; cin>>q;
  while(q--){
    int x,y; cin>>x>>y;
    if(a[x][y]==-1){
      s+=(f[x][y+1]-f[x+1][y])*r[x][y];
      a[x][y]=-2; update1(x,y,f[x][y+1]);
      update2(x+1,y,-r[x][y]); update2(x,y+1,r[x][y]);
    }
    else{
      s+=(f[x+1][y]-f[x][y+1])*r[x][y];
      a[x][y]=-1; update1(x,y,f[x+1][y]);
      update2(x,y+1,-r[x][y]); update2(x+1,y,r[x][y]);
    }
    cout<<s<<endl;
  }
  return 0;
}
```

---

## 作者：SolIII (赞：3)

## 题目分析
预处理每个点经过的牛数 $cnt_{i, j}$，每次更改一个点的指向时，计算更改前的终点坐标 `Old` 和更改后的终点坐标 `New`（不要忘了修改是一直保留的，在计算终点的过程中要顺便更改途经点的牛数和出发点的路牌方向 ~~，某蒟蒻在这个问题上调了 10min~~）。

新答案是旧答案 $ans$ 减去出发点牛数 $cnt_{x, y}$ 与 旧终点花费 `a[oldx][oldy].x` 的积， 加上出发点牛数 $cnt_{x, y}$ 与 新终点花费 `a[newx][newy].x` 的积。

## 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long NR = 15 * 1e2 + 1;
struct Node{
    Node(){
        c = '@';
    }
    char c;
    long long x;
}a[NR + 10][NR + 10];   //结构体存储输入
char s[NR + 10];
long long cnt[NR + 10][NR + 10];

int main(){
    long long n;
    scanf("%lld", &n);
    //读入
    for(long long i = 1;i <= n;i++){
        scanf("%s", s + 1);
        for(long long j = 1;j <= n;j++){
            a[i][j].c = s[j];
        }
        scanf("%lld", &a[i][n + 1].x);
    }
    for(long long j = 1;j <= n;j++){
        scanf("%lld", &a[n + 1][j].x);
    }
    //预处理每个点经过的牛数
    for(long long i = 1;i <= n + 1;i++){
        for(long long j = 1;j <= n + 1;j++){
            if(i == n + 1 && j == n + 1) continue;
            if(i <= n && j <= n){   //住所
                if(a[i - 1][j].c == 'D'){
                    cnt[i][j] += cnt[i - 1][j];
                }
                if(a[i][j - 1].c == 'R'){
                    cnt[i][j] += cnt[i][j - 1];
                }
                cnt[i][j]++;
            }
            else{   //饲料桶
                if(i == n + 1){
                    if(a[i - 1][j].c == 'D'){
                        cnt[i][j] += cnt[i - 1][j];
                    }
                }
                else if(j == n + 1){
                    if(a[i][j - 1].c == 'R'){
                        cnt[i][j] += cnt[i][j - 1];
                    }
                }
            }
        }
    }
    //计算最初花费
    long long sum = 0;
    for(long long i = 1;i <= n;i++){
        sum += 1ll * cnt[n + 1][i] * a[n + 1][i].x;
        sum += 1ll * cnt[i][n + 1] * a[i][n + 1].x;
    }
    printf("%lld\n", sum);   //输出
    //处理更改
    long long T;
    scanf("%lld", &T);
    while(T--){
        long long x, y;
        scanf("%lld%lld", &x, &y);   //读入
        //计算旧路径
        long long posx = x, posy = y;
        while(posx != n + 1 && posy != n + 1){
            if(a[posx][posy].c == 'D'){
                posx++;
            }
            else if(a[posx][posy].c == 'R'){
                posy++;
            }
            cnt[posx][posy] -= cnt[x][y];
        }
        long long tmpx = posx, tmpy = posy;
        posx = x, posy = y;
        //更改方向
        if(a[posx][posy].c == 'D'){
            a[posx][posy].c = 'R';
        }
        else if(a[posx][posy].c == 'R'){
            a[posx][posy].c = 'D';
        }
        //计算新路径
        while(posx != n + 1 && posy != n + 1){
            if(a[posx][posy].c == 'D'){
                posx++;
            }
            else if(a[posx][posy].c == 'R'){
                posy++;
            }
            cnt[posx][posy] += cnt[x][y];
        }
        //计算并输出
        printf("%lld\n", sum - cnt[x][y] * a[tmpx][tmpy].x
                             + cnt[x][y] * a[posx][posy].x);
        sum -= cnt[x][y] * a[tmpx][tmpy].x;
        sum += cnt[x][y] * a[posx][posy].x;
    }
    return 0;
}
```


---

## 作者：ForwardStar (赞：3)

#### 核心：递推
如果我们反着走，会发现——  
如果那个格子是 “R” 那么这个格子的奶牛和他右侧的奶牛或饲料桶的饲料相同，反之如果是 “D” 就和下面的奶牛或饲料桶相同。  
用 $f(i,j)$ 表示第 $i$ 行 $j$ 列的奶牛吃的饲料的价钱，我们可以得到——
```cpp
if(c[i][j]=='R')f[i][j]=f[i][j+1];
else f[i][j]=f[i+1][j];
```
注意我们是反着推的！

将所有的价钱累加在一块，就是答案。   
每次更改路牌都重新计算一遍，输出答案。   
~~恭喜你~~，TLE……   
仔细研究发现，每次更改路牌，都不会影响在他右边或下边的奶牛。
![pic](https://cdn.luogu.com.cn/upload/image_hosting/b2qs8adl.png)
所以我们每次从修改的那个点开始计算就可以了（第一次从最右下角开始）。
$sum(x,y)$ 表示所有 $i\geq x$ 或 $j\geq y$ 的奶牛吃的饲料的总价格。  
用二维前缀和代替总计数，不会二维前缀和的可以看看这张图。   
![pic2](https://cdn.luogu.com.cn/upload/image_hosting/u4d9ofiw.png)  
蓝框 = 蓝格子 + 红框 + 黄框 - 绿框 。  
也就是 $sum_{i,j}=f_{i,j}+sum_{i,j+1}+sum_{i+1,j}-sum_{i+1,j+1}$。  
最后答案存在了 $sum_{1,1}$。  
### AC 代码
```cpp
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdio>
#define N 1502
using namespace std;
int n,T,x,y;
int f[N][N],sum[N][N];
char c[N][N];
string s;
int main(){
	scanf("%d",&n);	
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=1;j<=n;j++)c[i][j]=s[j-1];
		scanf("%d",&f[i][n+1]); 
	}
	for(int i=1;i<=n;i++)scanf("%d",&f[n+1][i]);
	scanf("%d",&T);	
	for(int t=0;t<=T;t++){
		if(t){
			scanf("%d%d",&x,&y);
			c[x][y]=c[x][y]=='R'?'D':'R';//修改路牌。
		}
		else x=y=n;//第一次从（n,n）开始。 
		for(int i=x;i>=1;i--){
			for(int j=y;j>=1;j--){
				//递推 
				if(c[i][j]=='R')f[i][j]=f[i][j+1];
				else f[i][j]=f[i+1][j];
				sum[i][j]=f[i][j]+sum[i][j+1]+sum[i+1][j]-sum[i+1][j+1]; 
			}	
		}
		printf("%d\n",sum[1][1]);
	}
	return 0;
}

```
这种思路较为简单，但并不完美，需要开 O2 优化才能 AC，否则会超时。

---

## 作者：Yujinhe469 (赞：3)

**终于升金组了，特此纪念。**

## 题意简述

每头奶牛每天按照路标的方向（右或下）走知道走到边缘上，该格对应的饲料桶会被食用，Farmer John 花费相应的钱，每天也会有一块方向牌被翻转，求每天花费的钱数。

## 题目分析

* 首先要对初始答案进行计算。

若是对每个奶牛单独进行 dfs，会超时。

注意到每只奶牛和走向它所在点的奶牛必会走到同一饲料桶，可以用一个数组 $a$ 记录有多少奶牛会走到这个点（包括自己）。


时间复杂度 $O(n^2)$。

* 接着处理每一个改动后的数据。

每天改动后和前一天区别不大，所以我们可以由前一天的解推出后一天的解。

若 $(i,j)$ 的方向牌改动了，则只有所有会经过此点的奶牛（共 $a[i][j]$ 个）的去向可能会发生改变。

于此同时还要更新原来和当前去向上的点的 $a$ 值。

每次更新后的答案即为所有边缘点乘以其所对应的花费之和，经过优化可以在 $O(1)$ 的时间复杂度内处理（实际上 $O(n)$ 的时间复杂度也可接受）。

故总时间复杂度为 $O(n^2+nm)$。

### AC代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1509;
int n,q,l[N],r[N],a[N][N];
char c[N][N];
inline void init(){//此处若dfs会超时（常数）
	for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            a[i][j]++;
            if(c[i][j]=='R')
                a[i][j+1]+=a[i][j];
            else if(c[i][j]=='D')
                a[i+1][j]+=a[i][j];
        }
}
inline void dfs(int x,int y,int cnt,bool ok){
	if(ok) a[x][y]+=cnt;
	if(y==n&&c[x][y]=='R')
		a[x][y+1]+=cnt;
	else if(x==n&&c[x][y]=='D')
		a[x+1][y]+=cnt;
	else if(c[x][y]=='R')
		dfs(x,y+1,cnt,1);
	else if(c[x][y]=='D')
		dfs(x+1,y,cnt,1);
}
int ans(){
	int sum=0;
	for(int i=1;i<=n;i++)
        sum+=a[i][n+1]*l[i]+a[n+1][i]*r[i];
    return sum;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=n;j++)
			cin>>c[i][j];
		cin>>l[i];
	}
	for(register int i=1;i<=n;i++)
		cin>>r[i];
	init();
	cout<<ans()<<endl;
	cin>>q;
	while(q--){
		int i,j;
		cin>>i>>j;
		dfs(i,j,a[i][j]*(-1),0);
		if(c[i][j]=='D') c[i][j]='R';
		else c[i][j]='D';
		dfs(i,j,a[i][j],0);
		cout<<ans()<<endl;
	}
	return 0;
}
```

upd:2023.2.12

**特别感谢：**

@[syLph](https://www.luogu.com.cn/user/545026) 提出了原题解的问题；

@[xiaozhang2022](https://www.luogu.com.cn/user/479459) 给出了正确的代码并提出了原思路的问题。

---

## 作者：IYSY2009I (赞：3)

考虑建图解决这个问题。我们建立 $(N+1)(N+1)-1$ 个点，分别代表 $n^2$ 头奶牛和 $2N$ 个饲料桶。如果有一个路标从 $(x_1,y_1)$ 指向 $(x_2,y_2)$，则我们在这两个点直接连一条边。

容易发现，连完边后的图是一个由 $2N$ 个树组成的森林，且每一个饲料桶所对应的点都在不同的树内。我们把这 $2N$ 个点视为根，则以某个点为根的所有树内的非根节点对应的奶牛都会吃这个饲料桶，则这个饲料桶所贡献的价钱花费就为 $(size-1) \cdot cost$（$size$ 表示这棵树的大小，$cost$ 表示该饲料桶喂饱一只牛所需的价格）。

接下来我们考虑修改操作。可以看出来，如果一个路标改变了方向，则以该处所对应的节点为根的子树都会一起被修改。于是我们只需要支持以下两种操作，就可以解决该问题：

1. 将一棵树的某个子树接到另一棵树的某个节点上面（即让这颗子树的根节点成为另一个节点的儿子）。

2. 查询某棵树的大小。

因为 $N,Q \le 1500$，所以我们只需要在 $O(NQ)$ 的时间内解决该问题即可。我们考虑维护两个信息，$f_i$ 表示 $i$ 号节点的父亲，$siz_i$ 表示以 $i$ 为根的子树的大小，则对于一次查询操作，我们输出 $siz$ 即可。对于一次令 $x$ 成为 $y$ 的儿子的修改操作，我们要把 $x$ 原来的所有祖先的 $siz$ 全部减 $siz_x$，然后将 $f_x$ 修改为 $y$，然后将新的 $x$ 的祖先的 $siz$ 全部加 $siz_x$，然后就搞定了。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int c1[1505];
int c2[1505];
char s[1505][1505];
int ans[1505][1505];
struct edge{
	int nxt;
	int to;
};
edge e[5000005];
int h[2500005];
int cnt;
void add(int x,int y){
	cnt++;
	e[cnt].nxt=h[x];
	h[x]=cnt;
	e[cnt].to=y;
	return;
}
int size[2500005];
int f[2500005];
void dfs(int x,int fa){
	f[x]=fa;
	size[x]=1;
	for(int i=h[x];i;i=e[i].nxt)
		if(e[i].to!=fa){
			dfs(e[i].to,x);
			size[x]+=size[e[i].to];
		}
	if(!fa) size[x]--;
	return;
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		cin>>s[i]+1;
		scanf("%d",&c1[i+1]);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&c2[i]);
	for(int i=0;i<n;i++)
		for(int j=1;j<=n;j++){
			if(s[i][j]=='R'){
				add(i*(n+1)+j,i*(n+1)+j+1);
				add(i*(n+1)+j+1,i*(n+1)+j);
			}
			else{
				add((i+1)*(n+1)+j,i*(n+1)+j);
				add(i*(n+1)+j,(i+1)*(n+1)+j);
			}
		}
	size[0]=-1;
	for(int i=1;i<=n;i++){
		dfs(n*(n+1)+i,0);
		dfs((i-1)*(n+1)+n+1,0);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=c1[i]*size[(i-1)*(n+1)+n+1]+c2[i]*size[n*(n+1)+i];
	printf("%d\n",ans);
	int q;
	scanf("%d",&q);
	for(int k=1;k<=q;k++){
		int i,j;
		scanf("%d%d",&i,&j);
		i--;
		int x=i*(n+1)+j,y=f[x];
		while(y){
			size[y]-=size[x];
			y=f[y];
		}
		if(s[i][j]=='R'){
			s[i][j]='D';
			f[x]=(i+1)*(n+1)+j;
		}
		else{
			s[i][j]='R';
			f[x]=i*(n+1)+j+1;
		}
		y=f[x];
		while(y){
			size[y]+=size[x];
			y=f[y];
		}
		ans=0;
		for(int i=1;i<=n;i++)
			ans+=c1[i]*size[(i-1)*(n+1)+n+1]+c2[i]*size[n*(n+1)+i];
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：2)

暴力题。

首先预处理出 $sz_{i,j}$ 表示经过 $(i,j)$ 点的奶牛的数量。

然后考虑对于每一组修改，对于这个点原来需要经过的所有的点的 $sz$ 的值全部减去现在的要修改的那一个点的 $sz$ 的值。

然后修改这个点的方向。

然后对于 $(i,j)$ 每一个需要经过的点，这一个需要经过的点的 $sz$ 值全部加上现在的要修改的那一个点的 $sz$ 的值。

时间复杂度 $O(n^2+nq)$。

~~代码咕咕咕了~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e3+10;
int a[N][N];
char ch[N][N];
int sz[N][N];
signed main(){
  int n,q;
  cin>>n;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++)
      cin>>ch[i][j];
    cin>>a[i][n+1];
  };
  for(int i=1;i<=n;i++)
    cin>>a[n+1][i];
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
      sz[i][j]++;
      if(ch[i][j]=='R')sz[i][j+1]+=sz[i][j];
      else sz[i+1][j]+=sz[i][j];
    }
  int sum=0;
  for(int i=1;i<=n;i++)
    sum+=sz[n+1][i]*a[n+1][i]+sz[i][n+1]*a[i][n+1];
  cout<<sum<<'\n';
  cin>>q;
  while(q--){
    int x,y;
    cin>>x>>y;
    int p=sz[x][y];
    int xx=x,yy=y;
    while(true){
      if(ch[xx][yy]=='R')yy++;
      else xx++;
      sz[xx][yy]-=sz[x][y];
      if(xx>n||yy>n)break;
    }
    sum-=a[xx][yy]*p;
    if(ch[x][y]=='R')ch[x][y]='D';
    else ch[x][y]='R';
    xx=x,yy=y;
    while(true){
      if(ch[xx][yy]=='R')yy++;
      else xx++;
      sz[xx][yy]+=sz[x][y];
      if(xx>n||yy>n)break;
    }
    sum+=a[xx][yy]*p;
    cout<<sum<<'\n';
  }
  return 0;
}
```


---

## 作者：12345678hzx (赞：1)

## 思路
对于第 $1$ 至 $7$ 个测试点，$N,Q \le 250$，可以每次询问都 $O(N^2)$ 地计算答案，总时间复杂度为 $O(N^2Q)$。

对于上面的算法可以做一些优化，容易发现，改变坐标为 $(x,y)$ 的路标最多只会对坐标为 $(1\sim x,1\sim y)$ 的奶牛进行影响，所以在循环时只需要循环一部分就行了。

对于第 $1$ 至 $10$ 个测试点，$N,Q \le 1500$，但数据为随机生成，在理想状态下，每个点的前驱只有一个，则可以对询问点进行搜索，理想状态下时间复杂度为 $O(NQ)$。

对于所有测试点，$N,Q \le 1500$，对于每次询问考虑 $O(N)$ 预处理，最后 $O(1)$ 回答，可以用 $f_{i,j}$ 表示经过坐标为 $(i,j)$ 的点的奶牛有多少头，询问时将原先奶牛往下走的路都减去经过询问地点奶牛的数量，将反转后的奶牛往下走的路都加上经过询问地点奶牛的数量，就可以维护这个数组，时间复杂度为 $O(NQ)$。
## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int n,Q,a[1505][1505],b[1505][1505],ans;
char c;
bool v[1505][1505];
int x,y;
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			scanf(" %c",&c);
			v[i][j]=(c=='R');
		}
		scanf("%d",&a[i][n+1]);
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[n+1][i]);
	for(int i=n;i;i--) for(int j=n;j;j--) {
		if(v[i][j]==1) ans+=a[i][j+1],a[i][j]=a[i][j+1];
		else ans+=a[i+1][j],a[i][j]=a[i+1][j];
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
		b[i][j]++;
		if(v[i][j]==1) b[i][j+1]+=b[i][j];
		else b[i+1][j]+=b[i][j];
	}
	printf("%d\n",ans);
	scanf("%d",&Q);
	while(Q--) {
		scanf("%d%d",&x,&y);
		int tx=x,ty=y;
		while(1) {
			if(v[tx][ty]==1) b[tx][ty+1]-=b[x][y],ty++;
			else b[tx+1][ty]-=b[x][y],tx++;
			if(tx>n||ty>n) break;
		}
		ans-=b[x][y]*a[tx][ty];
		v[x][y]=!v[x][y];
		tx=x,ty=y;
		while(1) {
			if(v[tx][ty]==1) b[tx][ty+1]+=b[x][y],ty++;
			else b[tx+1][ty]+=b[x][y],tx++;
			if(tx>n||ty>n) break;
		}
		ans+=b[x][y]*a[tx][ty];
		printf("%d\n",ans);
	}
    return 0;
}
```

---

## 作者：Demeanor_Roy (赞：1)

- 摘自 [here](https://www.luogu.com.cn/blog/261213wrh/usaco-2023-jan-sliver-ti-xie)。

------------

考虑预处理出 $now_{i,j}$ 表示当前会经过 $(i,j)$ 的牛的数量。不难发现如果能时刻维护 $now_{i,j}$ 即可做到快速回答询问。

思考一次变化对 $now$ 数组带来的影响是什么。发现如果 $(i,j)$ 这个位置方向改变，影响为原来从 $(i,j)$ 出发那条路上点 $now$ 值减少 $now_{i,j}$，现在
从 $(i,j)$ 出发那条路上点 $now$ 值增加 $now_{i,j}$，由于这样的点只有 $O(n)$ 级别个，所以暴力修改即可。

时间复杂度 $O(nQ)$。[代码](https://www.luogu.com.cn/paste/acnufpcl)

---

## 作者：ztntonny (赞：1)

## 思路

我们考虑用 $cost_{i,j}$ 表示从方格 $(i,j)$ 最后会吃多少价值的饲料，用 $cnt_{i,j}$ 表示从方格 $(i,j)$ 有多少个奶牛会经过（包含本来在方格中的）。

不难发现，此时奶牛走的路线类似于根据每一块饲料形成的许多树，而每一次改变路标相当于是“嫁接”了一段树枝。所以实际上改变的只是这一条树枝上奶牛吃的饲料价值总和，设树枝最接近树根的坐标 $(x,y)$，则树枝上奶牛吃的饲料价值总和其可以被表示为 $cost_{x,y}\times cnt_{x,y}$，容易发现在“嫁接”过程中 $cnt_{x,y}$ 不变，只有 $cost_{x,y}$ 换了，所以总和实际上 $+(cost_{x,y}{before}-cost_{x,y}{after})\times cnt_{x,y}$。

那么我们思路清晰：先找到最开始的价值和，以后每一次修改都对应着修改 $\{cnt_{n,n}\},\{cost_{n,n}\}$，并对答案进行上述修改。

## 实现

- 我们在考虑计算开始价值总和的时候，采用记忆化，对于搜索过的就直接赋值，并且在搜索过程中一旦遇到被赋值了的直接赋相同的值并结束，$\mathcal{O}(n^2)$。
- 我们在考虑 $\{cnt_{n,n}\}$ 时，显然要向树根方向遍历修改，时间复杂度 $\mathcal{O}(n)$ 过得去。
- 我们在考虑 $\{cost_{n,n}\}$ 时，实际上不需要修改，因为如果修改是向树梢方向遍历，时间复杂度最大 $\mathcal{O}(n^2)$ 会炸，但是每一次查找只需要向树根方向遍历 $\mathcal{O}(n)$  搞定。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n , ans , cmp , drc[2005][2005] , q , xx , yy , cost[2005][2005] , cnt[2005][2005] , mak[2005][2005];
char x1;

ll cntfnd( int x , int y )
{
	if ( mak[x][y] )	return cnt[x][y];
	if ( x == 0 || y == 0 )	return 0;
	ll s = 1;
	if ( drc[x - 1][y] == 1 )	s += cntfnd( x - 1 , y );
	if ( drc[x][y - 1] == 0 )	s += cntfnd( x , y - 1 );
	cnt[x][y] = s , mak[x][y] = 1;
	return s;
}

void cntmark( int x , int y , ll z )
{
	if ( x == n + 1 || y == n + 1 )	return;
	cnt[x][y] += z;
	cntmark( x + drc[x][y] , y + !drc[x][y] , z );
	return;
}

ll fnd( int x , int y )
{
	if ( cost[x][y] )	return cost[x][y];
	if ( x == n + 1 || y == n + 1 )	return cost[x][y];
	cost[x][y] = fnd( x + drc[x][y] , y + !drc[x][y] );
	return cost[x][y];
}

ll costfnd( int x , int y )
{
	if ( x == n + 1 || y == n + 1 )	return cost[x][y];
	return costfnd( x + drc[x][y] , y + !drc[x][y] );
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL) , cout.tie(NULL);
	cin >> n;
	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= n; j++ )	cin >> x1 , drc[i][j] = ( x1 == 'D' );
		cin >> cost[i][n + 1];
	}
	for ( int i = 1; i <= n; i++ )	cin >> cost[n + 1][i];
	for ( int i = 1; i <= n; i++ )	for ( int j = 1; j <= n; j++ )	cost[i][j] = fnd( i , j ) , ans += cost[i][j];
	cin >> q;
	cout << ans << endl;
	for ( int i = 1; i <= q; i++ )
	{
		cin >> xx >> yy;
		ll befx = xx + drc[xx][yy] , befy = yy + !drc[xx][yy] , aftx = xx + !drc[xx][yy] , afty = yy + drc[xx][yy] , cntxxyy = cntfnd( xx , yy );
		drc[xx][yy] = !drc[xx][yy];
		ans += ( costfnd( aftx , afty ) - costfnd( befx , befy ) ) * cntxxyy;
		cntmark( befx , befy , -cntxxyy );
		cntmark( aftx , afty , cntxxyy );
		cout << ans << endl;
	}
    return 0;
}
```

---

## 作者：zac2010 (赞：1)

### 思路

这题很简单，预处理加暴力 $O(n)$ 修改维护和 $O(1)$ 查询，总的 $O(n^2 + n \times q)$。

具体的，我们首先一遍计算出一个 $f_{i,j}$ 表示初始有 $f_{i,j}$ 头牛会经过 $(i,j)$ 这个点。并记录 $v_{i,j}$ 表示 $(i,j)$ 这个位置最后会走到多少价格的饲料桶。

然后每次暴力对 $f$ 和 $v$ 两个数组修改即可，记得还要更新那个操作位置的方向。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 1510;
int n, q, c[N][N], v[N][N], f[N][N];
ll ans;
int Upd(int x, int y, int v){//暴力修改f数组
	if(x == n + 1 || y == n + 1) return v * c[x][y];
	f[x][y] += v;
	if(!c[x][y]) return Upd(x, y + 1, v);
	else return Upd(x + 1, y, v);
}
int main(){
	scanf("%d", &n);
	L(i, 1, n){
		L(j, 1, n){
			char ch; scanf(" %c", &ch);
			c[i][j] = (ch == 'D'); 
		}
		scanf("%d", &c[i][n + 1]);
	} 
	L(i, 1, n) scanf("%d", &c[n + 1][i]);
	L(i, 1, n){
		L(j, 1, n){
			f[i][j]++;
			if(!c[i][j]) f[i][j + 1] += f[i][j];
			else f[i + 1][j] += f[i][j];
		}
	}
	R(i, n, 1){
		R(j, n, 1){
			if(!c[i][j]) v[i][j] = (j == n? c[i][j + 1] : v[i][j + 1]);
			else v[i][j] = (i == n? c[i + 1][j] : v[i + 1][j]);
			ans += v[i][j];
		}
	}
	printf("%lld\n", ans);
	scanf("%d", &q);
	L(i, 1, q){
		int x, y;
		scanf("%d%d", &x, &y);
		if(!c[x][y]){
			c[x][y] = 1;
			ans = ans + Upd(x + 1, y, f[x][y]) + Upd(x, y + 1, -f[x][y]);
		}
		else{
			c[x][y] = 0;
			ans = ans + Upd(x, y + 1, f[x][y]) + Upd(x + 1, y, -f[x][y]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：__11jiang08__ (赞：0)

### 思路

可以先预处理到每个饲料缸的牛的数量，存在数组 $s$ 中，然后依次处理每次翻转，第 $i$ 次翻转 $(i,j)$，可以顺着原来走的路，依次减去 $s_{i,j}$，然后顺着翻转后的路，依次加上 $s_{i,j}$，这样的话总成本就是 $\sum\limits_{i=1}^{n}s_{i,n+1}\times c_{i,n+1} + \sum\limits_{i=1}^{n}s_{n+1,i}\times c_{n+1,i}$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
ll q,n,s[1509][1509],cst[1509][1509];
char to[1509][1509];
void init(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			s[i][j]+=1;
			if(to[i][j]=='D')  s[i+1][j]+=s[i][j];
			else  s[i][j+1]+=s[i][j];
		}
	}
	return ;
}
ll count(){
	ll res=0;
	for(int i=1;i<=n;i++)  res=res+s[i][n+1]*cst[i][n+1];
	for(int i=1;i<=n;i++)  res=res+s[n+1][i]*cst[n+1][i];
	return res; 
}
void mnus(int x,int y,int cnt){
	if(to[x][y]=='R'){
		s[x][y+1]-=cnt;
		mnus(x,y+1,cnt);
	}
	if(to[x][y]=='D'){
		s[x+1][y]-=cnt;
		mnus(x+1,y,cnt);
	}
}
void pls(int x,int y,int cnt){
	if(to[x][y]=='R'){
		s[x][y+1]+=cnt;
		pls(x,y+1,cnt);
	}
	if(to[x][y]=='D'){
		s[x+1][y]+=cnt;
		pls(x+1,y,cnt);
	}
}
void change(int sx,int sy){
	mnus(sx,sy,s[sx][sy]);
	to[sx][sy]=to[sx][sy]=='R'?'D':'R';
	pls(sx,sy,s[sx][sy]);
	return ;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)  cin>>to[i][j];
		cin>>cst[i][n+1];
	}
	for(int i=1;i<=n;i++)  cin>>cst[n+1][i];
	init();
	cin>>q;
	cout<<count()<<endl;
	for(int i=1;i<=q;i++){
		int x,y;
		cin>>x>>y;
		change(x,y);
		cout<<count()<<endl;
	}
	return 0;
}
```


---

