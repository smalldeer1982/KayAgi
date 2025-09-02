# D - Domino Covering XOR

## 题目描述

有一个网格，网格中有 $H$ 行和 $W$ 列。让 $(i,j)$ 表示从顶部 $(1\leq i\leq H)$ 起第 $i$ 行的单元格，从左侧 $(1\leq j\leq W)$ 起第 $j$ 列的单元格。

单元格 $(i,j)\ (1\leq i\leq H,1\leq j\leq W)$ 上写有一个非负整数 $A_{i,j}$ 。

让我们在网格上放置零块或更多块多米诺骨牌。一块多米诺骨牌覆盖两个相邻的单元格，即以下两对中的一对：

- 单元格 $(i,j)$ 和 $(i,j+1)$ 为 $1\leq i\leq H,1\leq j\lt W$ ；
- 单元格 $(i,j)$ 和 $(i+1,j)$ ，代表 $1\leq i\lt H,1\leq j\leq W$ 。

任何一个单元格都不能被一块以上的多米诺骨牌覆盖。

对于多米诺骨牌的摆放，其**分数**定义为写在***未被任何骨牌覆盖的单元格中的所有整数的位XOR。

找出可能的最大得分。

什么是位XOR？

对于非负整数 $A$ 和 $B$ ，它们的位向 XOR $A \oplus B$ 定义如下：

- 在二进制中，如果 $A$ 和 $B$ 中正好有一个位有 $1$ ，则 $A \oplus B$ 的 $2^k$ 位（ $k \ge 0$ ）为 $1$ ，否则为 $0$ 。

例如， $3 \oplus 5 = 6$ （二进制为 $011 \oplus 101 = 110$ ）。  
对于 $k$ 非负整数 $p_1, p_2, p_3, \dots, p_k$ ，它们的位 XOR 为 $(\dots ((p_1 \oplus p_2) \oplus p_3) \oplus \dots \oplus p_k)$ ，可以证明这与操作数的顺序无关。

## 说明/提示

- $1 \le H$
- $1 \le W$
- $HW \le 20$
- $0 \le A_{i,j} \lt 2^{60}$ ( $1 \le i \le H,\ 1 \le j \le W$ )
- 所有输入值均为整数。

## 样例 #1

### 输入

```
3 4
1 2 3 8
4 0 7 10
5 2 4 2```

### 输出

```
15```

## 样例 #2

### 输入

```
1 11
1 2 4 8 16 32 64 128 256 512 1024```

### 输出

```
2047```

## 样例 #3

### 输入

```
4 5
74832 16944 58683 32965 97236
52995 43262 51959 40883 58715
13846 24919 65627 11492 63264
29966 98452 75577 40415 77202```

### 输出

```
131067```

# 题解

## 作者：Clover_Lin (赞：5)

博客：https://blog.csdn.net/ArmeriaLeap/article/details/148196638 ，欢迎阅读。
## 题目大意
$H\times W$ 的矩阵，第 $i$ 行第 $j$ 列的数记为 $a_{i,j}$，现在要往上面铺若干（可以为零）块多米诺骨牌。多米诺骨牌是一个 $1\times2$ 或者 $2\times1$ 的长方形，能盖住两个数。问没有被盖住的数的异或和的最大值是多少。
## 思路
发现数据范围中保证了 $HW\le20$，然后考虑到多米诺骨牌只能是相邻的两个格，所以爆搜就能过。由于数据范围太小了，所以可以采用如下的结构进行搜索：
```cpp
dfs(x, y, k): 
	如果已经全部搜完
		ans = max(ans, k)
		返回
	如果这个格已经被多米诺骨牌盖住
		搜索下一个
		返回
	不放置多米诺骨牌，搜索下一个
	放置多米诺骨牌，标记当前位置，枚举所有可能的位置
		如果越界或者已经被盖住
			跳过
		标记
		计算异或和并搜索下一个
		取消标记
```
标记可以使用回溯法，用一个二维数组；计算异或和直接使用 `^` 符号。
## 代码
AC 记录：[Submission #66114498](https://atcoder.jp/contests/abc407/submissions/66114498)。

由于已经给出了伪代码，不再给出详细代码，如有需要请私信联系。

---

## 作者：Tomwsc (赞：3)

# AT_abc407_d [ABC407D] Domino Covering XOR 题解

## 前言

你要相信 AtCoder 的评测机……

## 思路

注意到 $HW\le 20$，且一个骨牌会占两个格子，同时时限为两秒，所以考虑直接暴搜。


具体的实现方法如下，在输入的时候，计算出全部数的异或值，存到 $num$ 中。对于 dfs 函数，传四个参数 $x$、$y$、$num$、$flag$，分别表示当前的行、列、此时的异或值、该格子被覆盖的情况。其中，$flag$ 只能为 $1$ 或 $0$。设此时 dfs 到第 $x$ 行，第 $y$ 列且将要转移到第 $xx$ 行，第 $yy$ 列，则：

- 当 $flag=1$ 时，表示当前是第一个被覆盖的格子，所以 $num\leftarrow num\oplus a_{xx,yy}$，因为一个骨牌不能覆盖超过连续的两个格子，所以 $flag\leftarrow 0$。
- 当 $flag=0$ 时，表示该格子不是第一个被覆盖的，但 $a_{xx,yy}$ 可能被第一个覆盖，也可能没有，所以分两种情况：
  
    - $num\leftarrow num\oplus a_{xx,yy}$，$flag\leftarrow 1$。
    - $num$、$flag$ 均不变。

答案即为当前格不是在第一个被覆盖时的 $num$ 的最大值。

## 代码

只跑了两百多毫秒……

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
#define regint register int
#define pb push_back
#define mp make_pair
#define PII pair<int , int>
using namespace std;
const int MAXN = 2e5 + 10 , dx[4] = {0 , 1 , -1 , 0} , dy[4] = {1 , 0 , 0 , -1};
int n , m , tot , ans;
int a[50][50];
bool flag[50][50];

inline int max(int a , int b) {
	return a > b ? a : b;
}

void dfs(int x , int y , int num , int k) {
	if(!k) ans = max(ans , num);
	flag[x][y] = true;
	for(regint i = 0;i < 4;i ++) {
		int xx = x + dx[i];
		int yy = y + dy[i];
		if(xx < 1 || xx > n || yy < 1 || yy > m || flag[xx][yy]) continue;
		if(k == 1) dfs(xx , yy , num ^ a[xx][yy] , 0);
		else {
			dfs(xx , yy , num , 0);
			dfs(xx , yy , num ^ a[xx][yy] , 1);
		}
	}
	flag[x][y] = false;
}

void solve() {
	cin >> n >> m;
	for(regint i = 1;i <= n;i ++) {
		for(regint j = 1;j <= m;j ++) {
			cin >> a[i][j];
			tot ^= a[i][j];
		}
	}
	dfs(1 , 1 , tot , 0);
	dfs(1 , 1 , tot ^ a[1][1] , 1);
	cout << ans << '\n';
	return;
}

signed main() {
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}
```

---

## 作者：boluo2014 (赞：2)

这道题其实并不难。
### 思路

你会发现题目中 $nm \le 20$，你每次可以放一个 $1 \times 2$ 的多米诺骨牌。那么可以举个例子，比如 $n=4$，$m=5$。你会发现，到后来，拜访的方法越来越少了，因此对应的时间复杂度也降低了。所以我们可以用 dfs 来实现。
### 具体实现

先看看现在这幅图有没有和之前重复，方法是用一个数组记录下每一个图的情况，用 $0$ 表示没有铺上，$1$ 表示铺上了，再用二进制转化成一个不是特别大的十进制就可以了。如果这个数被标记了，则退出（避免重复做）。

每次先判断原来的形状是否还可以继续添加。如果不能，算出答案，和最大值比较，并结束这一次运算。如果还可以，也算出来当前异或值，和最大值比较。继续从图中找到一个 $1 \times 2$ 的没有标记的空位，标记上，然后继续搜索，搜索完成了就取消标记。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=25;
int a[maxn][maxn],n,m,mx=INT_MIN;
bool f[maxn][maxn];//记录当前情况（1表示被覆盖了，0表示没有被覆盖） 
bool doit[4000005]; //不小心开打了一点 
int p(){//对应的二进制值 
	int c=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			c+=(1<<((i-1)*m+j))*f[i][j];
		}
	}
	return c;
}
void dfs(){
	int cnt=n*m,ans=0,tmp=p();
	if(doit[tmp])return ;
	doit[tmp]=true;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!f[i][j]){
				ans^=a[i][j],cnt--;
			}
		}
	}
	if(cnt==n*m-(n*m%2)){//就是判断剩余0个或1个空格 
		mx=max(mx,ans);
		return ;
	}
	if(ans>mx){
		mx=ans;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(j!=m&&!f[i][j]&&!f[i][j+1]){//横着摆 
				f[i][j]=1,f[i][j+1]=1;
				dfs();
				f[i][j]=0,f[i][j+1]=0;
			}
			if(i!=n&&!f[i][j]&&!f[i+1][j]){//竖着摆 
				f[i][j]=1,f[i+1][j]=1;
				dfs();
				f[i][j]=0,f[i+1][j]=0; 
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	int i,j;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	dfs();
	cout<<mx<<endl;
	return 0;
} /*
3 4
1 2 3 4
5 6 7 8
9 7 1 5*/
```
### 感谢观看

---

## 作者：xiaoyin2011 (赞：2)

## AT_abc407_d [ABC407D] 多米诺覆盖异或 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc407_d)

### 题目大意

给定 $H \times W$ 的矩阵，$H \times W \le 20$，用能覆盖 $1 \times 2$ 格子且可以水平或竖直放在矩阵中的多米诺骨牌覆盖一些格子，可以不覆盖，问露出数字的异或和最大值。骨牌必须恰好盖住两个格子，并且不能叠。

### 思路及实现

异或和最大值显然不容易预处理，发现 $H \times W \le 20$，考虑 DFS 所有覆盖情况。

用一个掩码 $mask < 2^{20}$ 来记录当前有多少格子被覆盖，一是覆盖，零是没有。DFS 中如果当前格子没覆盖，并且它的向右或向下相邻的格子没覆盖，就可以考虑覆盖这两个格子。可以证明，这样铺可以不重不漏考虑过每一种覆盖可能。

统计答案，这里可以预处理从掩码对应的异或和。只需要求得掩码的补集的异或和即可。

最后套一个记忆化，时空复杂度 $O(HW \times 2^{HW})$，可以通过。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll H, W, B[25];
ll cxs[1050005];
ll memo[25][1050005];
ll dfs(int pos, ll mask)
{
    if (pos == H * W)
        return cxs[(1 << (H * W)) - 1] ^ cxs[mask];
    if (memo[pos][mask] != -1)
        return memo[pos][mask];
    ll res = dfs(pos + 1, mask);
    if (mask & (1 << pos))
        return memo[pos][mask] = res;
    if (pos % W + 1 <= W - 1 && !(mask & (1 << (pos + 1))))
	{
        ll new_mask = mask | (1 << pos) | (1 << (pos + 1));
        res = max(res, dfs(pos + 1, new_mask));
    }
    if (pos / W + 1 <= H - 1 && !(mask & (1 << (pos + W))))
	{
        ll new_mask = mask | (1 << pos) | (1 << (pos + W));
        res = max(res, dfs(pos + 1, new_mask));
    }
    return memo[pos][mask] = res;
}
int main()
{
    scanf("%lld%lld", &H, &W);
    for (int i = 0; i <= H - 1; i++)
        for (int j = 0; j <= W - 1; j++)
        	scanf("%lld", &B[i * W + j]);
    for (int mask = 0; mask <= (1 << (H * W)) - 1; mask++)
        for (int k = 0; k <= H * W - 1; k++)
            if (mask & (1 << k))
            	cxs[mask] ^= B[k];
    for (int i = 0; i <= H * W - 1; i++)
    	for (int j = 0; j <= (1 << (H * W)) - 1; j++)
    		memo[i][j] = -1;
    printf("%lld\n", dfs(0, 0));
    return 0;
}
```

---

## 作者：Jerry20231029 (赞：1)

## 思路

看到 $HW \le 20$，果断爆搜！

开一个 `vis` 数组记录每个格子是否被覆盖，防止重复覆盖。

搜索过程中，对于每个点 $(x,y)$：

- 如果放骨牌，只考虑它作为右下角的情况：

  - 放在 $(x-1,y),(x,y)$ 两个位置
  - 放在 $(x,y-1),(x,y)$ 两个位置

  如果放了，当前位置就不计入答案，用异或运算去掉，然后继续搜。

- 如果不放，就计入答案，然后继续搜。

所有网格搜完后，找到所有答案的最大值即可。

## 代码

[AC 记录](https://atcoder.jp/contests/abc407/submissions/66147702)

```cpp
#include<iostream>
using namespace std;

typedef long long lld;
lld a[110][110],ans;
bool f[110][110];
int n,m;

void dfs(int x,int y,lld s){
	if(x > n){
		ans = max(ans,s);
		return;
	}
	if(y > m){
		dfs(x+1,1,s);
		return;
	}
	if(x-1>=1 && !f[x-1][y]){
		f[x-1][y] = f[x][y] = 1;
		dfs(x,y+1,s^a[x-1][y]);
		f[x-1][y] = f[x][y] = 0;
	}
	if(y-1>=1 && !f[x][y-1]){
		f[x][y-1] = f[x][y] = 1;
		dfs(x,y+1,s^a[x][y-1]);
		f[x][y-1] = f[x][y] = 0;
	}
	dfs(x,y+1,s^a[x][y]);
}

int main(){
	cin>>n>>m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin>>a[i][j];
		}
	}
	dfs(1,1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：xy_mc (赞：1)

这道题用我独创的 CFS（Crazy First Search 乱搜）都能过（bushi）。

好吧，其实是 DFS，我们分析三种情况：

- 当前位置不放置骨牌：
    - 将当前的值亦或到答案里，因为当前位置不放；
    - 再搜下一个格。
- 当前位置横向放置骨牌：
    - 标记覆盖的两个单元格；
    - 搜索横向的下下个单元格；
    - 回溯，标记清空。
- 当前位置纵向放置骨牌：
    - 标记覆盖的两个单元格；
    - 搜索横向的下个单元格，因为是竖向放置的，所以搜横向的下一个单元格；
    - 回溯，标记清空。

现在我们需要分析递归终止条件，依旧是三种情况：

- 搜完所有行：
    - 更新答案。
- 搜完当前这一行：
    - 搜索下一行的第一个。
- 当前位置被标记：
    - 搜索当前行的下一个。
 
那么现在就可以易得代码：

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int,int>
#define pll pair<ll,ll>
#define yes "Yes"
#define no "No"
#define debug(x) cout<<#x<<" = "<<x<<"\n"
#define rep(i,x,y) for(int i=x;i<=(y);++i)
#define per(i,x,y) for(int i=x;i>=(y);--i)

typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const int INF=0x3f3f3f3f;
const ll LNF=0x3f3f3f3f3f3f3f3f;

inline int sf(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
inline void out(int n){
	if(n<0){putchar('-');n=-n;}
	if(n>9)out(n/10);
	putchar(n%10^48);
}

int n,m;
ll a[30][30],ans;
bool vis[30][30];

void dfs(int x,int y,ll ppp){
	if(x>n){
		ans=max(ans,ppp);
		return;
	}
	if(y>m){
		dfs(x+1,1,ppp);
		return;
	}
	if(vis[x][y]){
		dfs(x,y+1,ppp);
		return;
	}
	dfs(x,y+1,ppp^a[x][y]);
	if(y<m&&!vis[x][y+1]){
		vis[x][y]=vis[x][y+1]=1;
		dfs(x,y+2,ppp);
		vis[x][y]=vis[x][y+1]=0;
	}
	if(x<n&&!vis[x+1][y]){
		vis[x][y]=vis[x+1][y]=1;
		dfs(x,y+1,ppp);
		vis[x][y]=vis[x+1][y]=0;
	}
}
void solve(){
    cin>>n>>m;
    rep(i,1,n) rep(j,1,m) cin>>a[i][j];
    dfs(1,1,0);
    cout<<ans;
}

int main(){
	int t=1;
	while(t--){
		solve();
	}
	return 0;
}
```

据说用状压 dp 也可以过，但是小蒟蒻不会 QWQ。

---

## 作者：N1tr0us_Acid (赞：1)

这篇题解来自一位赛时死磕贪心忘记算模拟复杂度的蒟蒻。

# $\texttt{Solution}$
先看数据范围，可以发现这个 $HW \le 20$，看起来就很模拟对吧。  
然后算一下，总共可以放置多少张不同的多米诺骨牌，可以发现，由于最后一行不能向下放多米诺骨牌，最后一列不能往最右边放，所以总数应该是小于 $HW$ 的。  
欸这不就是个 dfs？

所以我们可以预处理出每块多米诺骨牌所占的位置和每块牌所覆盖的两个数的异或和，然后枚举每一块多米诺骨牌放不放。

复杂度应该是 $O(HW2^{HW})$，可以通过此题。

# $\texttt{Code}$
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 25;

int h, w;
int a[N][N];

int tot;

int ans;

typedef pair <int, int> pii;

map <pii, int> mp;

struct node {
    pii pos1, pos2;
    int val;
} blo[N * N];

int cnt;

void dfs(int now, int sum) {
    if(now > cnt) {
        ans = max(ans, sum);

        return ;
    }

    dfs(now + 1, sum);

    if(mp[blo[now].pos1] + mp[blo[now].pos2] == 0) {
        mp[blo[now].pos1] = mp[blo[now].pos2] = 1;
        dfs(now + 1, (sum ^ blo[now].val)); // 由于同一个数异或两次相当于不变，所以这样相当于是扣去了多米诺骨牌下盖着的两个数对全局的贡献。

        mp[blo[now].pos1] = mp[blo[now].pos2] = 0;
    }
}

signed main(void) {
    cin >> h >> w;

    for (int i = 1; i <= h; i ++) {
        for (int j = 1; j <= w; j ++) {
            cin >> a[i][j];

            tot ^= a[i][j]; // 先求总异或和，然后以异或上某一多米诺骨牌的异或值的形式来表示选择这一张牌，因为按这样做以后的，这个异或出来的值相当于剩下没有被盖住的的异或和。
        }
    }

    for (int i = 1; i < h; i ++) {
        for (int j = 1; j < w; j ++) {
            blo[++ cnt] = {{i, j}, {i, j + 1}, (a[i][j] ^ a[i][j + 1])};
            blo[++ cnt] = {{i, j}, {i + 1, j}, (a[i][j] ^ a[i + 1][j])};
        }
    }

    for (int i = 1; i < h; i ++) { // 预处理每张牌。
        blo[++ cnt] = {{i, w}, {i + 1, w}, (a[i][w] ^ a[i + 1][w])};
    }

    for (int j = 1; j < w; j ++) {
        blo[++ cnt] = {{h, j}, {h, j + 1}, (a[h][j] ^ a[h][j + 1])};
    }

    for (int i = 1; i <= cnt; i ++) {
        mp[blo[i].pos1] = mp[blo[i].pos2] = 0;
    }

    dfs(1, tot);

    cout << ans;

    return 0;
}

```

---

## 作者：CNzzc (赞：0)

### 思路：

暴力枚举每一种情况，取最大值。

### 具体实现：

为了方便枚举，我们将二维转为一维。

若当前节点未访问，枚举向右覆盖和向下覆盖或不选择三种情况。

若当前节点已访问，则跳过该节点，保证补充不重不漏。

### 注意：

若当前节点为最后一列，只枚举向下覆盖。

若当前节点为最后一行，只枚举向右覆盖。

AC Code：


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define pr(x) pair<x,x>
#define up(i,j,k,l) for(int i=j;i<=k;i+=l)
#define down(i,j,k,l) for(int i=j;i>=k;i-=l)
using namespace std;
const int N=2e1+10;
int n,m,c,t[N];
int a[N][N],ans;
int f()
{
	int res=-1;
	int u;
	up(i,1,n,1){
		up(j,1,m,1){
			u=(i-1)*m+j;
			if(t[u]==0){
				if(res==-1){
					res=a[i][j];
				}
				else{
					res^=a[i][j];
				}
			}
		}
	}
	return res;
}
void dfs(int u)
{
	int v;
	if(u>c){
		ans=max(ans,f());
		return;
	}
	if(t[u]){
		dfs(u+1);
		return;
	}
	dfs(u+1);
	if(u%m!=0){
		v=u+1;
		if(t[v]==0){
			t[u]++;
			t[v]++;
			dfs(u+1);
			t[u]--;	
			t[v]--;			
		}
	}
	if(u<=(n-1)*m){
		v=u+m;
		if(t[v]==0){
			t[u]++;
			t[v]++;
			dfs(u+1);
			t[u]--;	
			t[v]--;			
		}
	}		
	return;
}
void solve()
{
	cin>>n>>m;
	up(i,1,n,1){
		up(j,1,m,1){
			cin>>a[i][j];
		}
	}
	c=n*m;
	dfs(1);
	cout<<ans;
	return;
}
signed main()
{
    //ios::sync_with_stdio(false);
	//cin.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int _=1;
	//cin>>_;
	up(i,1,_,1){
		solve();
	}
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：0)

题目传送门：[AT_abc407_d [ABC407D] Domino Covering XOR](https://www.luogu.com.cn/problem/AT_abc407_d)

这题放在 D 过于简单了吧。

### 做题过程

观察到 $n,m$ 极小，所以考虑暴搜。

在 dfs 时，对于每个 $i,j$，若存在能放下一个多米诺骨牌的空间，就将这两个地方设为访问过，然后继续搜。

剪枝：将访问矩阵转成字符串存起来，每次比较一下是否完全相同。

时间复杂度约 $O(2^{nm})$，可以通过。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long a[21][21],ans;
bool vis[21][21];
map<string,bool>p;
void dfs(){
	string str="";
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			str+=vis[i][j]+'0';
	if(p.count(str))return;
	p[str]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(i<n&&!(vis[i][j]||vis[i+1][j])){//第一种
				vis[i][j]=vis[i+1][j]=1;
				dfs();
				vis[i][j]=vis[i+1][j]=0;
			}
			if(j<m&&!(vis[i][j]||vis[i][j+1])){//第二种
				vis[i][j]=vis[i][j+1]=1;
				dfs();
				vis[i][j]=vis[i][j+1]=0;
			}
		}
	long long s=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(!vis[i][j])
				s^=a[i][j];
		}
	ans=max(ans,s);
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++)
    		cin>>a[i][j];
    dfs();
    cout<<ans;
    return 0;
}
```

[AC  on At](https://atcoder.jp/contests/abc407/submissions/66119784)。

---

## 作者：Your_Name (赞：0)

### 题解
首先每个格子都可以被竖着横着覆盖或者不被覆盖，一共三种方法。

那暴搜的复杂度就是 $O(3^{NM})$ 吗？不是。

我们发现每放一个就可以占两个格子，那么最后的复杂度显然远小于这个数，而更接近于 $O(2^{NM})$。更严格的复杂度证明可以参考官方题解。

这里提供的做法是深搜剪枝。
### AC_Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans,a[25][25];
set<vector<vector<bool>>> t;
void dfs(vector<vector<bool>> msk){
    int res=0;
    t.insert(msk);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(!msk[i][j]) res^=a[i][j];
    ans=max(ans,res);
    for(int i=0;i<n;i++)
        for(int j=0;j<m-1;j++)
            if(!msk[i][j]&&!msk[i][j+1]){
                auto nmsk=msk;
                nmsk[i][j]=nmsk[i][j+1]=true;
                if(!t.count(nmsk)) dfs(nmsk);
            }
    for(int i=0;i<n-1;i++)
        for(int j=0;j<m;j++)
            if(!msk[i][j]&&!msk[i+1][j]){
                auto nmsk=msk;
                nmsk[i][j]=nmsk[i+1][j]=true;
                if(!t.count(nmsk)) dfs(nmsk);
            }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) cin>>a[i][j];
    vector<vector<bool>> b(n);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) b[i].push_back(0);
    dfs(b);
    cout<<ans;
    return 0;
}
```
_完结撒花。_

---

