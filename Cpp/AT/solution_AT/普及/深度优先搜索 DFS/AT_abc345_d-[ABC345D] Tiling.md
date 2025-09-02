# [ABC345D] Tiling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc345/tasks/abc345_d

一辺の長さが $ 1 $ のマスからなる $ H $ 行 $ W $ 列のマス目と、$ N $ 枚のタイルがあります。  
$ i $ $ (1\leq\ i\leq\ N) $ 枚目のタイルは $ A_i\times\ B_i $ の長方形です。  
以下の条件をすべてみたすようにタイルをマス目に置くことができるか判定してください。

- 全てのマスがちょうど $ 1 $ 枚のタイルで覆われている。
- 使用されないタイルがあっても良い。
- 使用するタイルは **回転したり裏返したりして置かれていても良い**。ただし、各タイルはマスの線に合わせてマス目からはみ出ることがないように置かれていなければならない。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 7 $
- $ 1\ \leq\ H,W\ \leq\ 10 $
- $ 1\leq\ A_i,B_i\leq\ 10 $
- 入力はすべて整数

### Sample Explanation 1

$ 2,4,5 $ 枚目のタイルを使用して次のように置くと、マス目の各マスをちょうど $ 1 $ 枚のタイルで覆うことができます。 !\[\](https://img.atcoder.jp/abc345/0a0f2829d0485013deabba0103dbd906.png) よって、`Yes` を出力します。

### Sample Explanation 2

マス目からはみ出さないようにタイルを置くことはできません。 よって、`No` を出力します。

### Sample Explanation 3

全てのマスを覆うようにタイルを置くことができません。 よって、`No` を出力します。

### Sample Explanation 4

全てのマスはちょうど $ 1 $ 枚のタイルで覆われている必要があることに注意してください。

## 样例 #1

### 输入

```
5 5 5
1 1
3 3
4 4
2 3
2 5```

### 输出

```
Yes```

## 样例 #2

### 输入

```
1 1 2
2 3```

### 输出

```
No```

## 样例 #3

### 输入

```
1 2 2
1 1```

### 输出

```
No```

## 样例 #4

### 输入

```
5 3 3
1 1
2 2
2 2
2 2
2 2```

### 输出

```
No```

# 题解

## 作者：Vocaloid世末歌者 (赞：12)

本文同步发表于 [cnblogs](https://www.cnblogs.com/cppom/p/-/ABC345D-tijie)。

是个逆天搜索。

最开始：爆搜，启动！

然后 TLE 到飞起。

赛后：我【数据删除】这么简单的吗？！

`dfs` 每个位置，试着把没放过的块放到以这个位置为左上角的区域里面。

好了没了，就是这么简单！

对了记得这个块可以旋转！

-----------------

Posted on [cnblogs](https://www.cnblogs.com/cppom/p/-/ABC345D-tijie) too. But I didn't write English solution there.

It's such a strange DFS.

I used an exhaustive DFS, and got TLE.

But actually it's easy.

DFS every cell, and try to put a tile that we haven't used it before(this tile's top left corner is this cell).

Oh, and remember that the tile can spin.

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define N 1000010
#define MOD 998244353
#define esp 1e-8
#define INF 999999999999999999
#define LL long long
#define rep(i,a,b,g) for(LL i=a;i<=b;i+=g)
#define rem(i,a,b,g) for(LL i=a;i>=b;i-=g)
#define repn(i,a,b,g) for(LL i=a;i<b;i+=g)
#define remn(i,a,b,g) for(LL i=a;i>b;i-=g)
#define pll pair<LL,LL>
#define mkp(x,y) make_pair(x,y)
#define i128 __int128
#define lowbit(x) ((x)&(-(x)))
#define lc (u<<1)
#define rc (u<<1|1)
using namespace std;
void read(i128 &x)
{
	i128 f=1;
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
void writing(i128 x)
{
	if(x>=10)writing(x/10);
	putchar(x%10+'0');
}
void write(i128 x)
{
	if(x<0)
	{
		cout<<'-';
		x=-x;
	}
	writing(x);
}
LL n,h,w,a[20],b[20];
bool vis[20][20],u[20];
void dfs(LL x,LL y)
{
	if(y>w)dfs(x+1,1);
	if(x>h)
	{
		cout<<"Yes"<<endl;
		exit(0);
	}
	if(vis[x][y])dfs(x,y+1);
	rep(i,1,2*n,1)
	{
		if(!u[(i-1)%n+1])
		{
			bool f=1;
			repn(xx,x,x+a[i],1)
			{
				repn(yy,y,y+b[i],1)
				{
					if(xx>h||yy>w||vis[xx][yy])f=0;
				}
			}
			if(!f)continue;
			u[(i-1)%n+1]=1;
			repn(xx,x,x+a[i],1)
			{
				repn(yy,y,y+b[i],1)
				{
					vis[xx][yy]=1;
				}
			}
			dfs(x,y+1);
			u[(i-1)%n+1]=0;
			repn(xx,x,x+a[i],1)
			{
				repn(yy,y,y+b[i],1)
				{
					vis[xx][yy]=0;
				}
			}
		}
	}
}
int main()
{
	cin>>n>>h>>w;
	rep(i,1,n,1)cin>>a[i]>>b[i];
	rep(i,n+1,2*n,1)
	{
		a[i]=b[i-n];
		b[i]=a[i-n];
	}
	dfs(1,1);
	cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：vanyou (赞：5)

## 题目大意

有 $n$ 个矩形，每个矩形长 $a_i$ 宽 $b_i$，你需要用这些矩形填满 $h \times w$ 的格子，每个矩形只能用一次且不能有矩形重叠，询问能否填满。

- $ 1\leq N \leq 7 $
- $ 1\leq H,W\leq 10 $
- $ 1\leq A_i,B_i\leq 10 $

## 思路

因为数据范围较小，考虑直接暴力 dfs。

对于每个点，枚举覆盖这个点的矩形是哪一个，满足条件即不重叠不出界就放，放完了就可以，反之不行。

由于矩形可以横着或竖着放，分情况考虑即可。

## code

```cpp

#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,h,w;
bool vis[20][20],use[20];
struct node{
	int x,y;
}a[20];

bool ck(int x,int y,int ex,int ey){
	do{for(int i=y;i<=ey;i++) if(vis[x][i]) return 0;}while(++x<=ex);
	return 1;
}

void put(int x,int y,int ex,int ey,int col){
	do{for(int i=y;i<=ey;i++) vis[x][i]=col;}while(++x<=ex);
}

void dfs(int x,int y){
	if(y>w) y=1,x++;
	if(x==h+1){cout<<"Yes",exit(0);} //放完了
	if(vis[x][y]){ //被放过了就直接搜下一个
		dfs(x,y+1);
		return;
	}
	for(int i=1;i<=n;i++){
		if(use[i]) continue; //已经用过了
		int ex=x+a[i].x-1,ey=y+a[i].y-1;
		if(ex>h||ey>w) continue; //越界
		if(!ck(x,y,ex,ey)) continue; //有点被放了
		use[i]=1;
		put(x,y,ex,ey,1);
		dfs(x,y+1);
		put(x,y,ex,ey,0);
		use[i]=0;
	}
	for(int i=1;i<=n;i++){ //考虑横着放
		if(use[i]||a[i].x==a[i].y) continue;
		int ex=x+a[i].y-1,ey=y+a[i].x-1;
		if(ex>h||ey>w) continue;
		if(!ck(x,y,ex,ey)) continue;
		use[i]=1;
		put(x,y,ex,ey,1);
		dfs(x,y+1);
		put(x,y,ex,ey,0);
		use[i]=0;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>h>>w;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	dfs(1,1);
	cout<<"No";
	return 0;
}

```

---

## 作者：2huk (赞：4)

省流：爆搜。

---

有一个 $n \times m$ 网格和 $k$ 块拼图，第 $i$ 块拼图的大小为 $a_i \times b_i$。问能否用拼图填满网格。

$1 \le k \le 7$，$1 \le n, m, a_i, b_i \le 10$。

---

最朴素的，暴力枚举每个拼图的左上角放在哪个位置，需要保证这个位置以前没有被填过。实现得优秀可能会过。

[代码](https://www.luogu.com.cn/paste/57kx63hq)。

注意到如果当前拼图的状态是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/khn05v15.png)

如果接下来能用拼图将其填满，那么一定存在某些拼图，它们的左上角为 $(1, 4), (2, 3), (4, 2), (5, 1)$。即「拐角」一定会有某个拼图用左上角填。

其中，如果一个位置 $(i, j)$ 是「拐角」，那么会满足：

- 网格中位置 $(i, j)$ 没填；
- 网格中位置 $(i - 1, j)$ 已填（如果存在）；
- 网格中位置 $(i, j - 1)$ 已填（如果存在）；
- 网格中位置 $(i - 1, j - 1)$ 已填（如果存在）；


所以在枚举当前哪个位置填拼图的左上角时，只在「拐角」的地方填即可。

[代码](https://www.luogu.com.cn/paste/uncw8wg2)。

---

## 作者：封禁用户 (赞：2)

[更好的阅读体验](https://www.doittomorrow.xyz/post/abc345d-tiling-de-ti-jie/)
## 题目大意
有一个由 $H$ 行和 $W$ 列组成的网格，每个单元格的边长为 $1$ ，我们有 $N$ 块瓷砖。第 $i$ 个图块 ($1\le i\le N$) 是一个大小为 $A_i\times B_i$ 的矩形。请判断是否有可能将这些图块放置在网格中，从而满足以下所有条件：

- 每个单元格都正好被一个图块覆盖。
- 有未使用的瓦片也没关系。
- 瓦片在放置时可以旋转或翻转。但是，每块瓦片必须与单元格的边缘对齐，不得超出网格。

其中 $1\le N\le 7,1 \le H,W \le 10,1\leq A_i,B_i\leq 10$。
## 思路
显而易见的这个题目是一个 dfs 搜索题，毕竟 $H,W$ 只有可怜的 $10$。

对于每一块，可以选或者不选。如果不选择，那么就直接对下一块进行递归搜索。

如果选择，那么枚举这一块的方向和左上角的位置，判断这些区域是否没有被覆盖。

如果是空的，那么就将这里覆盖并且递归下一块。

但是不可避免的，这道题目还需要进行剪枝才可以通过。
#### 剪枝 $1$
对于瓷砖排列的顺序，显然按面积从大到小排序是最优的。

因为在搜索时现将较大的放入后可以放置的区域就变少了，那么如果放置较小的瓷砖时就回更快的发现无解。
#### 剪枝 $2$
在搜索的过程中，我们可以记录下一共覆盖的地板的数量。

如果将剩下来所有的瓷砖全部的体积加起来还是不能将他们放满的话，那么就直接返回。
## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
void io(){ios::sync_with_stdio(false);cin.tie(nullptr);}
template<typename T>void write(T x){if(x<0) cout<<'-', x=-x;if(x>9) write(x/10);cout<<(char)(x%10+48);}
const int N=20;
int num,n,m,s[N];
struct node{int x,y;}a[N];
bool cmp(node a,node b){return a.x*a.y>b.x*b.y;}
bool vis[N][N];
bool ck(){ //判断是否全部覆盖
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(!vis[i][j]) return 0;
	return 1;
}
bool emp(int x,int xx,int y,int yy){ //判断从是否为空的
	for(int i=x;i<xx;i++) for(int j=y;j<yy;j++) if(vis[i][j]) return 0;
	return 1;
}
void fill(int x,int xx,int y,int yy,bool val){ //将这个区域覆盖
	for(int i=x;i<xx;i++) for(int j=y;j<yy;j++) vis[i][j]=val;
}
void dfs(int k,int sum){
	if(ck()) cout<<"Yes\n",exit(0);
	if(k==num+1) return; 
	if(sum+s[k]<n*m) return; //剪枝 2
	dfs(k+1,sum);
	for(int i=1;i+a[k].x<=n+1;i++){ //竖着
		for(int j=1;j+a[k].y<=m+1;j++){
			if(emp(i,i+a[k].x,j,j+a[k].y)){
				fill(i,i+a[k].x,j,j+a[k].y,1);
				dfs(k+1,sum+a[k].x*a[k].y);
				fill(i,i+a[k].x,j,j+a[k].y,0);
			}
		}
	}
	for(int i=1;i+a[k].y<=n+1;i++){ //横着
		for(int j=1;j+a[k].x<=m+1;j++){
			if(emp(i,i+a[k].y,j,j+a[k].x)){
				fill(i,i+a[k].y,j,j+a[k].x,1);
				dfs(k+1,sum+a[k].x*a[k].y);
				fill(i,i+a[k].y,j,j+a[k].x,0);
			}
		}
	}
}
void solve(){
    cin>>num>>n>>m;
    for(int i=1;i<=num;i++) cin>>a[i].x>>a[i].y;
    sort(a+1,a+1+num,cmp); //剪枝 1
    for(int i=num;i>=1;i--) s[i]=s[i+1]+a[i].x*a[i].y;
    dfs(1,0);
    cout<<"No\n";
}
signed main(){io();
    int T=1;
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：2)

对于一个合法方案，发现我们可以按矩形的左上角所在坐标，从左到右，从上到下地放置矩形。这样可以用 $\mathcal O(N!)$ 的复杂度枚举矩形的放置顺序。

我们直接暴力寻找每一个尚未被覆盖的格子，对于一个未被覆盖的格子，用当前排列中第一个尚未被放置的矩形来覆盖并暴力更新。每次都要扫一遍格子，复杂度 $\mathcal O(HW)$。

还要注意矩形可能旋转，暴力枚举所有情况，复杂度 $\mathcal O(2^N)$。

最后把这一堆都套在一起，复杂度 $\mathcal O(N!2^NHW)$。完全过得了，而且很难卡满。
```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=200007,ee=1000000000000000007ll;
ll n,m,k,a[17],b[17],now[17][17],id[17];
bool check(void){
	//for(int i=1;i<=n;i++) cout<<id[i]<<" "; cout<<"\n";
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++) now[i][j]=0;
	ll top=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(!now[i][j]){
		if(i+a[id[top]]-1>n||j+b[id[top]]-1>m) return 0;
		for(int p=i;p<=i+a[id[top]]-1;p++)for(int q=j;q<=j+b[id[top]]-1;q++) now[p][q]++;
		top++;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(now[i][j]!=1) return 0;
	return 1;
}
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll Tccs=1;
	//cin>>Tccs;
	for(int tcs=1;tcs<=Tccs;tcs++){
		cin>>k>>n>>m;
		for(int i=1;i<=k;i++) cin>>a[i]>>b[i],id[i]=i;
		do{
			for(int s=0;s<(1<<k);s++){
				for(int i=1;i<=k;i++)if((s>>(i-1))&1) swap(a[i],b[i]);
				if(check()) cout<<"Yes\n",exit(0);
				for(int i=1;i<=k;i++)if((s>>(i-1))&1) swap(a[i],b[i]);
			}
		}while(next_permutation(id+1,id+1+k));
		cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：xz001 (赞：2)

直接暴力枚举必然超时，但是因为 $n\le 7$，所以折半查找，再加一个小优化，搜索前先将矩形按照面积排序，即可通过此题。

代码：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define fi			first
#define co          const
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, h, w, a[N], b[N];

struct node {
	short a[11];
};

vector <unsigned long long> s;

il void dfs1 (co int i, co node x) {
	if (i > n / 2) {
		re unsigned long long g = 0;
	    for (re int i = 1; i <= h; ++ i )
	        for (re int j = 1; j <= w; ++ j )
	            g = g * 33331 + (x.a[i] >> j & 1);
	            
		s.push_back(g);
		return;
	}
	dfs1 (-~i, x);
	re int sum[11][11];
	memset(sum, 0, sizeof(sum));
	for (re int ii = 1; ii <= h; ++ ii )
	    for (re int j = 1; j <= w; ++ j )
	        sum[ii][j] = sum[ii - 1][j] + sum[ii][j - 1] - sum[ii - 1][j - 1] + (x.a[ii] >> j & 1);
	        
	for (re int ii = 1; ii <= h - a[i] + 1; ++ ii ) { 
		for (re int j = 1; j <= w - b[i] + 1; ++ j ) {
			if (sum[ii + a[i] - 1][j + b[i] - 1] - sum[ii - 1][j + b[i] - 1] - sum[ii + a[i] - 1][j - 1] + sum[ii - 1][j - 1] == 0) {
				node tmp = x;
				for (re int xx = ii; xx <= ii + a[i] - 1; ++ xx )
				    for (re int y = j; y <= j + b[i] - 1; ++ y)
				        tmp.a[xx] |= 1 << y;
				        
				dfs1 (-~i, tmp);
			}
		}
	}
	swap(a[i], b[i]);
	for (re int ii = 1; ii <= h - a[i] + 1; ++ ii ) { 
		for (re int j = 1; j <= w - b[i] + 1; ++ j ) {
			if (sum[ii + a[i] - 1][j + b[i] - 1] - sum[ii - 1][j + b[i] - 1] - sum[ii + a[i] - 1][j - 1] + sum[ii - 1][j - 1] == 0) {
				re node tmp = x;
				for (re int xx = ii; xx <= ii + a[i] - 1; ++ xx )
				    for (re int y = j; y <= j + b[i] - 1; ++ y)
				        tmp.a[xx] |= 1 << y;
				        
				dfs1 (-~i, tmp);
			}
		}
	}
	swap(a[i], b[i]);
	return;
}

bool is;
 
il void dfs2 (co int i, co node x) {
	if (is) return;
	if (i > n) {
		re unsigned long long g = 0;
		for (re int t = 1; t <= h; ++ t )
		    for (re int y = 1; y <= w; ++ y )
		        g = g * 33331 + !(x.a[t] >> y & 1);
		        
		if (binary_search(s.begin(), s.end(), g)) {
			is = true;
		}
		return;
	}
	dfs2 (i + 1, x);
	if (is) return;
	re int sum[11][11];
	memset(sum, 0, sizeof(sum));
	for (re int ii = 1; ii <= h; ++ ii )
	    for (re int j = 1; j <= w; ++ j )
	        sum[ii][j] = sum[ii - 1][j] + sum[ii][j - 1] - sum[ii - 1][j - 1] + (x.a[ii] >> j & 1);
	        
	for (re int ii = 1; ii <= h - a[i] + 1; ++ ii ) { 
		for (re int j = 1; j <= w - b[i] + 1; ++ j ) {
			if (sum[ii + a[i] - 1][j + b[i] - 1] - sum[ii - 1][j + b[i] - 1] - sum[ii + a[i] - 1][j - 1] + sum[ii - 1][j - 1] == 0) {
				re node tmp = x;
				for (re int xx = ii; xx <= ii + a[i] - 1; ++ xx )
				    for (re int y = j; y <= j + b[i] - 1; ++ y)
				        tmp.a[xx] |= 1 << y;
				        
				dfs2 (-~i, tmp);
				if (is) return;
			}
		}
	}
	swap(a[i], b[i]);
	for (re int ii = 1; ii <= h - a[i] + 1; ++ ii ) { 
		for (re int j = 1; j <= w - b[i] + 1; ++ j ) {
			if (sum[ii + a[i] - 1][j + b[i] - 1] - sum[ii - 1][j + b[i] - 1] - sum[ii + a[i] - 1][j - 1] + sum[ii - 1][j - 1] == 0) {
				re node tmp = x;
				for (re int xx = ii; xx <= ii + a[i] - 1; ++ xx )
				    for (re int y = j; y <= j + b[i] - 1; ++ y)
				        tmp.a[xx] |= 1 << y;
				        
				dfs2 (-~i, tmp);
				if (is) return;
			}
		}
	}
	swap(a[i], b[i]);
	
	return;
}

node t;

int sum;

pair <int, int> c[N];

bool operator < (pair <int, int> a, pair <int, int> b) {
	return a.first * a.second < b.first * b.second;
}

signed main() {
    scanf("%d%d%d", &n, &h, &w);
    for (int i = 1; i <= n; ++ i ) scanf("%d%d", a + i, b + i), sum += a[i] * b[i], c[i] = {a[i], b[i]};
    sort(c + 1, c + n + 1);
    for (int i = 1; i <= n; ++ i ) a[i] = c[i].first, b[i] = c[i].second;
    if (sum < h * w) {
    	puts("No");
    	return 0;
	}
    dfs1 (1, t);
    sort(s.begin(), s.end());
    dfs2 (n / 2 + 1, t);
    if (is) puts("Yes");
    else puts("No");
    return 0;
}

```

---

## 作者：__Dist__ (赞：2)

#### 翻译

有一个由 $h$ 行和 $w$ 列组成的网格，每个单元格的边长为 $1$ ，我们有 $n$ 块瓷砖。第 $i$ 个瓷砖 $(1\leq i\leq N)$ 是一个大小为 $a_i \times b_i$ 的矩形。
请判断是否有可能在网格上放置瓷砖，从而满足以下所有条件：

- 每个单元格都正好被一个图块覆盖。
- 有未使用的瓷砖也没关系。
- 瓷砖在放置时可以旋转或翻转。但是，每块瓷砖必须与单元格的边缘对齐，不得超出网格。

#### 思路

ABC 经典大模拟。

深度优先搜索，但是和不同深搜不太一样。

每次搜索按照从上到下、从左到右的顺序找到第一个没有铺的网格位置。然后枚举所有剩下没有用过的瓷砖，看看横着放、竖着放怎么能放进去。如果有合法方案往下搜。

看代码吧。

```cpp
#include <bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long
using namespace std;
const int MAXN = 1e5 + 5;
ll read() {
    ll x = 0, f = 1;char ch = gt();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1;ch = gt();}
    while (ch >= '0' && ch <= '9') {x *= 10;x += ch - '0';ch = gt();}
    return x * f;
}

bool f[15][15];//f[i][j] 表示 (i,j) 有没有铺过
ll n, h, w;
ll a[15], b[15];
bool use[15];//use[i] 表示第 i 块砖是否用过

void dfs() {
    ll x = -1, y = -1;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if(!f[i][j]) {
                x = i;
                y = j;
                break;
            }
        }
        if(x != -1) break;
    }

    if(x == -1 && y == -1) {
        //铺满了
        cout << "Yes\n";
        exit(0);
    }

    for (int now = 1; now <= n; now++) {
        if(use[now]) continue;
        //枚举没有用过的格子
        for (int p = 1; p <= 2; p++) {
            //横着放/竖着放
            bool flag = true;
            for (int i = 0; i < a[now]; i++) {
                for (int j = 0; j < b[now]; j++) {
                    if(i + x > h || j + y > w || f[i + x][j + y]) {
                        flag = false;
                        break;
                    }
                }
                if(!flag) break;
            }
            if(flag) {
                //这么铺合法
                for (int i = 0; i < a[now]; i++) {
                    for (int j = 0; j < b[now]; j++) {
                        f[i + x][j + y] = true;
                    }
                }
                use[now] = true;
                dfs();
                for (int i = 0; i < a[now]; i++) {
                    for (int j = 0; j < b[now]; j++) {
                        f[i + x][j + y] = false;
                    }
                }
                use[now] = false;
                //别忘改回来
            }
            swap(a[now], b[now]);
        }
    }
}

int main() {
    n = read(), h = read(), w = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read(), b[i] = read();
    }
    dfs();
    cout << "No\n";
    return 0;
}
```

---

## 作者：ykzzldz (赞：1)

这题有点恶心的，暴力不难（~~我是不会说我错了好几发的~~），主要是优化。

我们用一个 $s$ 前缀和数组来记录**从后往前**瓷砖的面积和，当 $s_i+num<H\times W$（$num$ 为之前瓷砖铺过的面积），直接返回，这也比较好理解，因为加上后面所有的瓷砖都不能铺满，那么就肯定不行。另一个优化就是按面积从大到小排序，因为肯定是现将大块的瓷砖铺完后再铺小砖较优。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int l,r;
}a[10];
int N,M,n,vis[20][20],ans,s[20];
bool cmp(node a,node b){
	return a.l*a.r>b.l*b.r;
}
void dfs(int x,int num){
	if(num+s[x]<N*M)return;
	if(num==N*M)ans=1;
	if(ans==1)return;
	if(x>n)return;
	for(int i=1;i+a[x].l-1<=N;i++){
		for(int j=1;j+a[x].r-1<=M;j++){
			int flag=0;
			for(int k=i;k<=i+a[x].l-1;k++){
				if(flag)break;
				for(int o=j;o<=j+a[x].r-1;o++){
					if(vis[k][o])flag=1;
					if(flag)break;
				}
			}
			if(flag==0){
				for(int k=i;k<=i+a[x].l-1;k++){
					for(int o=j;o<=j+a[x].r-1;o++){
						vis[k][o]=1;
					}
				}
				dfs(x+1,num+a[x].l*a[x].r);
				for(int k=i;k<=i+a[x].l-1;k++){
					for(int o=j;o<=j+a[x].r-1;o++){
						vis[k][o]=0;
					}
				}
			}
		}
	}
	for(int i=1;i+a[x].r-1<=N;i++){
		for(int j=1;j+a[x].l-1<=M;j++){
			int flag=0;
			for(int k=i;k<=i+a[x].r-1;k++){
				if(flag)break;
				for(int o=j;o<=j+a[x].l-1;o++){
					if(vis[k][o])flag=1;
					if(flag)break;
				}
			}
			if(flag==0){
				for(int k=i;k<=i+a[x].r-1;k++){
					for(int o=j;o<=j+a[x].l-1;o++){
						vis[k][o]=1;
					}
				}
				dfs(x+1,num+a[x].l*a[x].r);
				for(int k=i;k<=i+a[x].r-1;k++){
					for(int o=j;o<=j+a[x].l-1;o++){
						vis[k][o]=0;
					}
				}
			}
		}
	}
	dfs(x+1,num);
}
signed main(){
	cin>>n>>N>>M;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=n;i>=1;i--){
		s[i]=s[i+1]+a[i].l*a[i].r;
	}
	dfs(1,0);
	if(ans==1)cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：IJN_Shokaku (赞：1)

先定义一个 check 函数，用于检查当前放置方式是否符合要求：每个格子被恰好一个矩形覆盖，未使用的矩形不影响结果，矩形不能超出网格范围。

然后枚举所有可能的放置方式：

 dfs 判断是否已经尝试放置了所有的矩形，如果是，则调用 check 函数进行检查。如果符合条件，则将结果标记为真，并结束递归。
 
如果还有矩形没有放置，则在当前可选的矩形中选择一个尚未使用的矩形，尝试将其放置在网格的某个位置上。然后递归调用 dfs 函数，继续放置下一个矩形。

在递归调用结束后，需要撤销对当前矩形的放置，以便尝试其他的放置方式。

最后在主函数中调用 dfs 函数并输出结果。如果存在符合条件的放置方式，则输出  "Yes" ， 否则输出 "No" 。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, h, w, cnt, num;
int a[10], b[10];
bool pd, vis[10], m[15][15];
pair<int, int> l[10], q[10];
bool check(int x) {
	if (x > cnt) {
		memset(m, 0, sizeof m);
		for (int k = 1; k <= num; k++) {
			for (int i = 1; i <= h; i++) {
				for (int j = 1; j <= w; j++) {
					if (!m[i][j]) {
						for (int ii = i; ii <= i + q[k].first - 1; ii++) {
							for (int jj = j; jj <= j + q[k].second - 1; jj++) {
								if (ii > h || jj > w) return false;
								if (m[ii][jj]) return false;
								m[ii][jj] = true;
							}
						}
						goto Next;
					}
				}
			}
			return false;
			Next:
			x = x;
		}
		for (int i = 1; i <= h; i++)
			for (int j = 1; j <= w; j++)
				if (!m[i][j]) return false;
		return true;
	}
	bool is = false;
	for (int i = 1; i <= cnt; i++) {
		if (vis[i]) continue;
		vis[i] = true;
		q[++num] = l[i];
		is = is || check(x + 1);
		num--;
		vis[i] = false;
	}
	return is;
}
void dfs(int now) {
	if (now > n) {
		if (check(1)) pd = true;
		return;
	}
	dfs(now + 1);
	l[++cnt] = {a[now], b[now]};
	dfs(now + 1);
	l[cnt] = {b[now], a[now]};
	dfs(now + 1);
	cnt--;
}
signed main() {
	cin >> n >> h >> w;
	for (int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
	}
	dfs(1);
	cout << (pd?"Yes":"No");
	return 0;
}
```

---

## 作者：kevinZ99 (赞：1)

## 题意

给你一个 $h \times w$ 的矩阵。

在给你 $n$ 个瓷砖，第 $i$ 个瓷砖的大小为 $a_i \times b_i$。

然你选择一些瓷砖来填满，$h \times w$ 的地板。

瓷砖可以翻转。

## 思路

这么小的数据范围明显 dfs 暴力即可。

dfs 搜索：按照顺序尝试，类似于添数独的方式，按照从左上到右下的方式填，即可。

## 代码

因为是用赛时的代码改的所以比较乱

```cpp
/*
  Author:Kevin Z K Y
  t_limit:
  m_limit:
*/
//mod 998244353 \ 1e9+7 \ 1e9+9 \ 19260817 \ 104857601
#include <bits/stdc++.h>
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
using namespace std;
using pii = pair<int,int> ;
namespace my{
	#define fst first
	#define sed second
	const int N=10;
	string ot;
	pii a[N];
	bool vis[15][15];
	bool used[N];
	int n,h,w;
	void dfs(int have){
		if(have==h*w){
			cout<<"Yes\n";
			exit(0);
		}
		up(choose,1,n){
			if(used[choose])continue;
			bool in=false;
			up(x,1,h){
				up(y,1,w){
					if(vis[x][y])continue;
					if(x+a[choose].fst-1<=h&&y+a[choose].sed-1<=w){
						bool can=false;
						up(i,x,x+a[choose].fst-1){
							up(j,y,y+a[choose].sed-1)
								if(vis[i][j]){
									can=true;
									break;
								}
							if(can)break;
						}
						if(!can){
							in=true;
							up(i,x,x+a[choose].fst-1)up(j,y,y+a[choose].sed-1)
								vis[i][j]=true;
							used[choose]=true;
							dfs(have+a[choose].fst*a[choose].sed);
							used[choose]=false;
							up(i,x,x+a[choose].fst-1)up(j,y,y+a[choose].sed-1)
								vis[i][j]=false;
						}
					}
					if(x+a[choose].sed-1<=h&&y+a[choose].fst-1<=w){
						bool can=false;
						up(i,x,x+a[choose].sed-1){
							up(j,y,y+a[choose].fst-1)
								if(vis[i][j]){
									can=true;
									break;
								}
							if(can)break;
						}
						if(!can){
							in=true;
							up(i,x,x+a[choose].sed-1)up(j,y,y+a[choose].fst-1)
								vis[i][j]=true;
							used[choose]=true;
							dfs(have+a[choose].fst*a[choose].sed);
							used[choose]=false;
							up(i,x,x+a[choose].sed-1)up(j,y,y+a[choose].fst-1)
								vis[i][j]=false;
						}
					}
					if(in)break;
				}
				if(in)break;
			}
		}
	}
	bool flag=false;
	void judge(int x,int s){
		if(flag)return ;
		if(s==h*w){
			flag=true;
			return ;
		}
		if(x>n)return ;
		judge(x+1,s);
		judge(x+1,s+a[x].fst*a[x].sed);
		return ;
	}
	void solve(){
		srand(time(0));
		cin>>n>>h>>w;
		int sum=0;
		up(i,1,n)cin>>a[i].fst>>a[i].sed,sum+=a[i].fst*a[i].sed;
		if(sum<h*w){
			cout<<"No\n";
			return ;
		}
		judge(1,0);
		if(!flag){
			cout<<"No\n";
			return ;
		}
		dfs(0);
		cout<<"No\n";
	}
	#undef fst	
	#undef sed
}
int main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int _=1;
	while(_--)my::solve();
	return 0;
}

```

---

## 作者：kczw (赞：1)

# 题意
现在有一 $H\times W$ 格局的地板以及 $N$ 块 $A_i\times B_i(1\le i\le N)$ 的地砖。

你可择其任意块砖用于铺设，同时，你可将它们旋转后使用。

问是否有方案使得每个格子都仅由一块地砖覆盖且无地砖超出 $H\times W$ 的范围。
# 思路
对于一张图，假设我们已经铺设了一些地砖。

此时定有点 $(x,y)$ 左、上方都不用铺设地砖，易得点 $(x,y)$ 定是某块地砖的左上角，否则该点不可被覆盖。于是我们可以枚举哪块砖会用于铺设该点，以及它的摆放方式。

根据上述步骤，不难看出可用深搜实现。

每次枚举需要找到一个类上述点 $(x,y)$ 的点才可以开始枚举，为了方便，我们设该点为从上往下，从左往右数的第一个未被覆盖的点。

若枚举时，砖块重叠或是出界则不合法，否则继续枚举。若整张图被填完且合法，退出深搜输出答案。

枚举砖的使用顺序需要 $O(N!)$，枚举砖的旋转需要 $O(2^N)$ ，抛开对于点是否被覆盖的处理不谈，总时间复杂度为 $O(N!\times2^N)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h,w,a[10],b[10],v[10],vis[15][15],sum;
inline bool dfs(int x,int y){
	if(y>w)return dfs(x+1,1);
	if(x>h)return true;
	if(vis[x][y])return dfs(x,vis[x][y]);
	for(int i=1;i<=n;i++)
		if(!v[i]){
			if(x-1+a[i]<=h&&y-1+b[i]<=w&&!vis[x][y-1+b[i]]){
				v[i]=1;
				for(int j=x;j<=x-1+a[i];j++)
				for(int l=y;l<=y-1+b[i];l++)
					vis[j][l]=y+b[i];
				if(dfs(x,y+b[i]))return true;
				for(int j=x;j<=x-1+a[i];j++)
				for(int l=y;l<=y-1+b[i];l++)
					vis[j][l]=0;
				v[i]=0;
			}
			if(x-1+b[i]<=h&&y-1+a[i]<=w&&!vis[x][y-1+a[i]]){
				v[i]=1;
				for(int j=x;j<=x-1+b[i];j++)
				for(int l=y;l<=y-1+a[i];l++)
					vis[j][l]=y+a[i];
				if(dfs(x,y+a[i]))return true;
				for(int j=x;j<=x-1+b[i];j++)
				for(int l=y;l<=y-1+a[i];l++)
					vis[j][l]=0;
				v[i]=0;
			}
	}
	return false;
}
main(){
	scanf("%d%d%d",&n,&h,&w);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		sum+=a[i]*b[i];
	}
	if(sum<h*w)puts("No"),exit(0);
	if(dfs(1,1))puts("Yes");
	else puts("No");
	return 0;
}
```

---

## 作者：Lu_xZ (赞：1)

### [[ABC345D] Tiling](https://www.luogu.com.cn/problem/AT_abc345_d)

原题解地址：[Editorial by Kiri8128](https://atcoder.jp/contests/abc345/editorial/9614)

神写法。

将 $H \times W$ 的网格展开为 $H \times (W + 1)$ 的序列， 每行多出来的一格表示换行。

```cpp
W += 1;
```

令 $F(a, b)$ 表示长为 $a$，宽为 $b$ 的矩形填满网格左上角的状态，直接给出公式，可以模拟检验正确性。

```cpp
i128 F(int a, int b) {
	return (((i128)1 << a * W) - 1) / ((1 << W) - 1) * ((1 << b) - 1);
}
```

搜索过程：
+ 枚举每个矩形出现顺序。
+ 初状态 $s = F(H, W - 1)$。
+ 二进制枚举每个矩形是否旋转。
+ 设 $x$ 为矩形的值，如果 $x \operatorname{and} s = x$，那么 $x$ 能填入，否则结束循环。
+ 当一个矩形能够填入时，更新左上角，除以 $\operatorname{lowbit}$(s) 去掉 $s$ 末尾的 $0$。
+ $s = 0$ 即找到一组合法解。



写法较于一些冗长的搜索显得极为优雅。

> 注意 `next_permutation` 是按字典序判的，因此先排序。

```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
#define pb emplace_back
using namespace std;
using i128 = __int128;

int N, H, W;

i128 F(int a, int b) {
	return (((i128)1 << a * W) - 1) / ((1 << W) - 1) * ((1 << b) - 1);
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> N >> H >> W;
	W += 1;
	vector<pair<i128, i128>> a;
	rep(i, 1, N) {
		int x, y; cin >> x >> y;
		a.pb(F(x, y), F(y, x));
	}
	i128 S = F(H, W - 1);
	ranges::sort(a);
	do {
		for(int i = 0; i < 1 << N; ++ i) {
			i128 s = S;
			for(int j = 0; j < N; ++ j) {
				i128 x = (i >> j & 1) ? a[j].first : a[j].second;
				if((x & s) != x) break;
				if((s ^= x) == 0) {
					cout << "Yes";
					exit(0);
				}
				s /= s & -s;
			}
		}
	} while(ranges::next_permutation(a).found);
	cout << "No";
	return 0;
}
```

---

## 作者：Ivan422 (赞：1)

这题我做了很久，最后还是改出来了。

思路一：很好想，枚举瓷砖选和不选，接着判断是否能铺成完整的矩形。但是呢，我赛时按照这个写，获得了差一点通过的成绩：[链接](https://atcoder.jp/contests/abc345/submissions/51351114)。超时，不要踩坑哦！

思路二：也很好像，按照地板一个一个点计算，枚举瓷砖，这样放的点一定是可以放瓷砖的，不会**枚举要放的点**，就不会超时了。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
bool p[11][11],u[11];
int n,h,w,a[M],b[M],su,asu;
bool ans,cdfs;
void dfs(int stp){
    if(stp>h*w){
        if(su!=h*w)return;
        cout<<"Yes";
        exit(0);
    }
    int i=(stp-1)/w+1;
    int j=(stp-1)%w+1;
    if(p[i][j]){dfs(stp+1);return;}
    for(int id=1;id<=n;id++)if(!u[id]){
        cdfs=1;
        for(int k=i;k<=i+a[id]-1;k++)for(int l=j;l<=j+b[id]-1;l++){if(p[k][l]){cdfs=0;}}
        if(cdfs){
            for(int k=i;k<=i+a[id]-1;k++)for(int l=j;l<=j+b[id]-1;l++){p[k][l]=1;}
            u[id]=1;su+=a[id]*b[id];dfs(stp+1);su-=a[id]*b[id];u[id]=0;
            for(int k=i;k<=i+a[id]-1;k++)for(int l=j;l<=j+b[id]-1;l++){p[k][l]=0;}
        }
        if(a[id]==b[id])continue;
        cdfs=1;
        for(int k=i;k<=i+b[id]-1;k++)for(int l=j;l<=j+a[id]-1;l++){if(p[k][l]){cdfs=0;}}
        if(cdfs){
            for(int k=i;k<=i+b[id]-1;k++)for(int l=j;l<=j+a[id]-1;l++){p[k][l]=1;}
            u[id]=1;su+=a[id]*b[id];dfs(stp+1);su-=a[id]*b[id];u[id]=0;
            for(int k=i;k<=i+b[id]-1;k++)for(int l=j;l<=j+a[id]-1;l++){p[k][l]=0;}
        }
    }
}
signed main(){
    cin>>n>>h>>w;
    for(int i=1;i<=n;i++){cin>>a[i]>>b[i];asu+=a[i]*b[i];}
    dfs(1);
    cout<<"No";
    return 0;
}
```

---

## 作者：zaochen (赞：0)

## ABC345D：搜索剪枝

有一篇题解使用折半搜索解决这道题，方法值得学习。我写一篇用搜索剪枝解决这道题的题解。  

## 搜索部分

数据范围很小，尝试用搜索解决。  
考虑深度优先搜索，`dfs(x)` 表示当前放置第 $x$ 个矩形，枚举不放这个矩形，或者这个矩形放的位置。位置要满足这个矩形所覆盖的位置都没有被其他矩形覆盖。然后把这个矩形放下来，搜索下一个矩形。回溯时，从棋盘上拿掉这个矩形。注意矩形可以旋转。最后进行判断，整个棋盘都被覆盖就说明找到解。  
以上深度优先搜索的步骤写成代码如下：  
```cpp

pair<int, int> a[10];                                 // 矩形大小
bool vis[10][10];                                     // 是否放置了矩形
void down(int xl, int xr, int yl, int yr, bool state) // 放置或拿掉矩形
{
    for (int hc = xl; hc <= xr; hc++)
        for (int wc = yl; wc <= yr; wc++)
            vis[hc][wc] = state;
}
bool dfs(int x)
{
    if (x == n + 1) // 搜索完成
    {
        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
                if (!vis[i][j])
                    return false;
        return true;
    }
  	if (dfs(x + 1)) return true; // 不选这个矩形
    int hh = a[x].first, ww = a[x].second;
    for (int i = 1; i + hh - 1 <= h; i++) // 枚举放的位置
        for (int j = 1; j + ww - 1 <= w; j++)
        {
            bool flag = 1;
            for (int hc = i; flag && (hc <= i + hh - 1); hc++)
                for (int wc = j; flag && (wc <= j + ww - 1); wc++)
                    flag &= !vis[hc][wc];
            if (!flag)
                continue;
            down(i, i + hh - 1, j, j + ww - 1, true);
            if (dfs(x + 1))
                return true;
            down(i, i + hh - 1, j, j + ww - 1, false); // 回溯
        }
	swap(hh, ww); // 旋转
    for (int i = 1; i + hh - 1 <= h; i++)
        for (int j = 1; j + ww - 1 <= w; j++)
        {
            bool flag = 1;
            for (int hc = i; flag && (hc <= i + hh - 1); hc++)
                for (int wc = j; flag && (wc <= j + ww - 1); wc++)
                    flag &= !vis[hc][wc];
            if (!flag)
                continue;
            down(i, i + hh - 1, j, j + ww - 1, true);
            if (dfs(x + 1))
                return true;
            down(i, i + hh - 1, j, j + ww - 1, false);
        }
    return false;
}
```

时间复杂度分析：$n$ 个矩形，每个矩形选或不选共有 $2^n$ 种方案，每种方案的判断需要枚举每个矩形放的位置，随着放的矩形越来越多可选方案数会越来越少，增长方式类似阶乘但是低于阶乘。  
总而言之时间复杂度过高，容易超时，考虑剪枝优化。  

## 可行性剪枝  

容易发现，在共 $2^n$ 种方案中，大部分方案是可以容易判断不可行的。例如，把所选矩形的面积相加，若面积不等于整个棋盘的面积则一定不可行，可以直接剪枝。  
以样例 #1 为例，在 $2^5 = 32$ 种方案中，只有两种方案满足面积相加等于整个棋盘面积，搜索范围大大减少，剪枝行之有效。  
具体地，可以在开始搜索前二进制枚举选哪些矩形，再计算面积来判断是否一定不可行。  
二进制枚举的代码实现如下：
```cpp
vector<int> card; // 选的矩形
int get_bit(int x, int id) // 获取集合 x 二进制表示的第 id 位
{
    return (x >> (id - 1)) & 1;
}
bool check(int o)
{
    int area = 0; // 选的矩形的面积和
    card.clear();
    for (int i = 1; i <= n; i++)
        if (get_bit(o, i))
            card.push_back(i), area += a[i].first * a[i].second;
    if (area != h * w) // 一定不可行
        return false;
    memset(vis, 0, sizeof vis);
    return dfs(0);
}
```

## 搜索顺序

显然矩形的放置顺序不影响求解问题。  
在枚举矩形放的位置的时候，若先放大的矩形，则后面矩形可以选的位置就少了，搜索树就会窄很多。  
所以，我们可以对所有矩形按面积从大到小排序，再搜索求解问题。  
```cpp
using pii = pair<int, int>;
sort(a + 1, a + 1 + n, [&](pii x, pii y) { return x.first * x.second > y.first * y.second; });
    
```

## 最终代码

将搜索与剪枝结合起来，就可以通过这题。参考代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, h, w;
using pii = pair<int, int>;

pii a[10];        // 矩形大小
bool vis[10][10]; // 是否放置了矩形

void down(int xl, int xr, int yl, int yr, bool state) // 放置或拿掉矩形
{
    for (int hc = xl; hc <= xr; hc++)
        for (int wc = yl; wc <= yr; wc++)
            vis[hc][wc] = state;
}

vector<int> card; // 选的矩形
bool dfs(int x)
{
    if (x == card.size()) // 搜索完成
    {
        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
                if (!vis[i][j])
                    return false;
        return true;
    }
    int hh = a[card[x]].first, ww = a[card[x]].second;
    for (int i = 1; i + hh - 1 <= h; i++) // 枚举放的位置
        for (int j = 1; j + ww - 1 <= w; j++)
        {
            bool flag = 1;
            for (int hc = i; flag && (hc <= i + hh - 1); hc++)
                for (int wc = j; flag && (wc <= j + ww - 1); wc++)
                    flag &= !vis[hc][wc];
            if (!flag)
                continue;
            down(i, i + hh - 1, j, j + ww - 1, true);
            if (dfs(x + 1))
                return true;
            down(i, i + hh - 1, j, j + ww - 1, false); // 回溯
        }
    swap(hh, ww); // 旋转
    for (int i = 1; i + hh - 1 <= h; i++)
        for (int j = 1; j + ww - 1 <= w; j++)
        {
            bool flag = 1;
            for (int hc = i; flag && (hc <= i + hh - 1); hc++)
                for (int wc = j; flag && (wc <= j + ww - 1); wc++)
                    flag &= !vis[hc][wc];
            if (!flag)
                continue;
            down(i, i + hh - 1, j, j + ww - 1, true);
            if (dfs(x + 1))
                return true;
            down(i, i + hh - 1, j, j + ww - 1, false);
        }
    return false;
}

int get_bit(int x, int id) // 获取集合 x 二进制表示的第 id 位
{
    return (x >> (id - 1)) & 1;
}
bool check(int o)
{
    int area = 0;
    card.clear();
    for (int i = 1; i <= n; i++)
        if (get_bit(o, i))
            card.push_back(i), area += a[i].first * a[i].second;
    if (area != h * w) // 一定不可行
        return false;
    memset(vis, 0, sizeof vis);
    return dfs(0);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin >> n >> h >> w;
    for (int i = 1; i <= n; i++)
        cin >> a[i].first >> a[i].second;
    sort(a + 1, a + 1 + n, [&](pii x, pii y) { return x.first * x.second > y.first * y.second; });
    for (int o = 1; o < 1 << n; o++)
        if (check(o))
        {
            cout << "Yes" << endl;
            return 0;
        }
    cout << "No" << endl;
    return 0;
}
```

## 总结

在搜索问题中，可行性剪枝和适当改变搜索顺序都可以有效提升程序效率。给不熟悉搜索剪枝的同学推荐一道经典例题：P1120 小木棍

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
因为数据特别小，我们直接暴力 dfs 就行。

$1 \leq N \leq 7$ 的数据随便乱搞就行。

记得每个块都有 $4$ 种方式排放，但在我的代码中保证了上边和左边都是被标记过的，所以只用枚举 $2$ 种。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,h,w,a[500005],b[500005],bz[50][50],bz2[5005],ans;
int check(long long x,long long y,long long aa,long long bb,long long pos)
{
	for(int i=min(x,x+aa-1);i<=max(x,x+aa-1);i++)
	   for(int j=min(y,y+bb-1);j<=max(y,y+bb-1);j++)
	   {
	   	    if(bz[i][j]>0&&bz[i][j]!=pos)return 1;
	   }
	return 0;
}
void work(long long x,long long y,long long aa,long long bb,long long pos)
{
	for(int i=min(x,x+aa-1);i<=max(x,x+aa-1);i++)
	   for(int j=min(y,y+bb-1);j<=max(y,y+bb-1);j++)
	   {
	   	    bz[i][j]=pos;
	   }
}

pair<int,int> find()
{
    for(int i=1;i<=h;i++)
       for(int j=1;j<=w;j++)
       {
       	   if(bz[i][j]==0)return {i,j};//空位
	   }
	return {-1,-1};//填满则返回-1
}
void dfs(long long x,long long y)
{
	pair<int,int> t;
	for(int i=1;i<=n;i++)
	{
		if(bz2[i]==1)continue;
		if(a[i]+x-1<=h&&b[i]+y-1<=w&&check(x,y,a[i],b[i],i)==0)
		{
			bz2[i]=1;
			work(x,y,a[i],b[i],i);
			t=find();
			if(t.first==-1)
			{
				cout<<"Yes";
//				for(int i=1;i<=n;i++)
//				{
//					if(bz2[i]==1)cout<<i<<" ";
//				}
//				for(int i=1;i<=h;i++)
//				{
//					for(int j=1;j<=w;j++) 
//			           cout<<bz[i][j]<<" ";
//			        cout<<endl;
//		        }
//		        cout<<endl;
				exit(0);
			}
			dfs(t.first,t.second);
			bz2[i]=0;
			work(x,y,a[i],b[i],0);
		}
	    if(a[i]+y-1<=w&&b[i]+x-1<=h&&check(x,y,b[i],a[i],i)==0)//a[i]和b[i]调换相当于翻转90度。
		{
			bz2[i]=1;
			work(x,y,b[i],a[i],i);
			t=find();
			if(t.first==-1)
			{
				cout<<"Yes";
//				for(int i=1;i<=h;i++)
//				{
//					for(int j=1;j<=w;j++) 
//			           cout<<bz[i][j]<<" ";
//			        cout<<endl;
//		        }
//		        cout<<endl;
				exit(0);
			}
			dfs(t.first,t.second);
			bz2[i]=0;
			work(x,y,b[i],a[i],0);
		}
	}
}
int main()
{
	cin>>n>>h>>w;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i],ans+=a[i]*b[i]; 
	if(ans<h*w)
	{
		cout<<"No";
		return 0;
	}
	dfs(1,1);
	cout<<"No";
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

**设 $H,M$ 同阶。**

首先考虑枚举每一块砖放进去的顺序共 $N!$ 种方案，以及每个方块是否旋转一下共 $2^N$ 种方案，总方案数是 $N! \times 2^N$。

现在知道了马上要放的砖块是什么，找到第一个可以放的地方，将这个砖放上去后会后重叠或者超过了边界就不合法；那么一次验证是 $O(H^4)$。

总时间复杂度约为 $O(H^4 \times N! \times 2^N)$，但是我们只需要找一组解，所以是完全跑不满的，可以放心通过。

**实现时可以考虑状压或者搜索。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=15;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,h,w,sum;
ll a[N],b[N],t[N];
ll A[N][N];
bool f[N];
bool check(ll S){
    ll id=1;
    for(int i=1;i<=h;i++)
      for(int j=1;j<=w;j++)
        A[i][j]=0;
    for(int i=1;i<=h;i++){
    	for(int j=1;j<=w;j++){
            if(A[i][j])
			  continue;
            if(id>sum)
			  return 0;
            ll X=a[t[id]],Y=b[t[id]];
            if(S>>(id-1)&1ll)
              swap(X,Y);
            if(i+X-1>h)
			  return 0;
            if(j+Y-1>w)
			  return 0;
            for(int i2=i;i2<=i+X-1;i2++){
            	for(int j2=j;j2<=j+Y-1;j2++){
                    if(A[i2][j2])
                      return 0;
                    A[i2][j2]=1;
                }
            }
            id++;
        }
    }
    for(int i=1;i<=h;i++)
      for(int j=1;j<=w;j++)
        if(!A[i][j])
		  return 0;
    return 1;	
}
bool check(){
	for(int S=0;S<(1ll<<sum);S++)
	  if(check(S))
	    return 1;
	return 0;
}
void dfs(ll x,ll y){
	if(x==n+1){
		if(!sum||y!=h*w)
		  return ;
		if(check()){
			puts("Yes");
			exit(0);
		}
		return ;
	}
	for(int i=1;i<=n;i++){
		if(f[i])
		  continue;
		f[i]=1;
		t[++sum]=i;
		dfs(x+1,y+a[i]*b[i]);
		f[i]=0;
		--sum;
	}
	dfs(x+1,y);
}
int main(){
	n=read(),h=read(),w=read();
	for(int i=1;i<=n;i++)
	  a[i]=read(),b[i]=read();
	dfs(1,0);
	puts("No");
	return 0;
}
```

---

## 作者：wenlebo (赞：0)

一道很好的暴力题。

我们可以像俄罗斯方块一样把一个个方块落到一个地面上，这个地面可以用一维数组记录，内容为这一列覆盖区域的“高度”。放置即为把数组的一个区间加上一个数（要求这个区间数相同（否则会有空隙）且加上以后不会越界）。

不停搜索，每次枚举放的位置和方块，如果放的块数达到要求（满了），就停止。

注意方块可以正着放也可以反着放。

还要进行一些优化，比如如果方块是正方形就无需旋转，如果这个方块和上一个一样且上一个没用过就不用（先排下序）。

```
#include <bits/stdc++.h>
using namespace std;
int n,h,w;
int co[14];
bool OK;
bool ok(int x,int a,int b){
	if(x+a-1>h){
		return 0;
	}
	if(co[x]+b>w){
		return 0;
	}
	for(int i=x,j=1;j<=a;j++,i++){
		if(co[i]!=co[x]){
			return 0;
		}
	}
	return 1;
}
void dr(int x,int a,int b){
	for(int i=x,j=1;j<=a;j++,i++){
		co[i]+=b;
	}
}
void ke(int x,int a,int b){
	for(int i=x,j=1;j<=a;j++,i++){
		co[i]-=b;
	}
}
int jd=0;
int fal;
int a[11],b[11],fe[11];
bool ot[11];
void dfs(){
	if(jd==fal){
		OK=1;
		return ;
	}
	if(OK){
		return;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==a[i-1]&&b[i]==b[i-1]&&ot[i-1]==0){
			continue;
		}
		if(ot[i]==0){
			for(int j=1;j<=h;j++){
				if(ok(j,a[i],b[i])){
					dr(j,a[i],b[i]);
					jd+=fe[i];
					ot[i]=1;
					dfs();
					if(OK){
						return;
					}
					ke(j,a[i],b[i]);
					jd-=fe[i];
					ot[i]=0;
				}
				if(a[i]!=b[i]){
					if(ok(j,b[i],a[i])){
						dr(j,b[i],a[i]);
						jd+=fe[i];
						ot[i]=1;
						dfs();
						if(OK){
							return;
						}
						ke(j,b[i],a[i]);
						jd-=fe[i];
						ot[i]=0;
					}
				}
			}
		}
	}
}
int allfe;
struct sss{
	int fi,se;
};
bool cmp(sss aa,sss bb){
	if(aa.fi==bb.fi){
		return aa.se<bb.se; 
	} 
	return aa.fi<bb.fi;
}
sss tot[11];
int main(){
	cin.tie(0);
	cout.tie(0); 
	cin>>n>>h>>w;
	fal=h*w;
	for(int i=1;i<=n;i++){
		cin>>tot[i].fi>>tot[i].se;
		if(tot[i].fi>tot[i].se){
			swap(tot[i].fi,tot[i].se);
		}
	}
	sort(tot+1,tot+1+n,cmp);
	for(int i=1;i<=n;i++){
		a[i]=tot[i].fi;
		b[i]=tot[i].se;
		fe[i]=a[i]*b[i];
		allfe+=fe[i];
	}
	if(allfe<fal){
		cout<<"No";
		return 0;
	}
	dfs();
	if(OK){
		cout<<"Yes";
	}else{
		cout<<"No";
	}
	return 0;
} 
```

---

## 作者：FBW2010 (赞：0)

# 前言

[传送门](https://www.luogu.com.cn/problem/AT_abc345_d)

一道不错的搜索题，比较考验剪枝等优化的能力，本蒟蒻赛时花了不少时间才做出来。这边提供一下我的思路，不喜勿喷。

# 思路

首先，题目范围很小，我们可以考虑搜索。搜索过程很简单，每个瓷砖考虑不放、正着放和反着放三种情况，然后更新哪些地方被覆盖就行了。

但由于有判断修改等操作，复杂度已经很高了。此时我们需要考虑一些剪枝和优化：

+ 搜索时统计当前**已选瓷砖总面积**，如果大于**网格总面积**就退出，**等于**就输出 `Yes` 后结束。

+ 存下瓷砖面积的**前缀和**，如果**当前使用瓷砖总面积**加上**之后所有瓷砖的总面积**小于**网格总面积**，就直接退出。

+ 将所有瓷砖的面积从**大到小排**，这样可以尽快地排除一些无解情况。

+ 只有瓷砖为**长方形**时才考虑倒过来。

+ 如果当前位置放不下这个瓷砖，找到**最右下角的不能放**的位置，下一次就直接从**那个位置后面**枚举。

基本操作已经说完了，接下来详见代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h,w,flag/*有没有解*/,sum[10]/*前缀和*/,t[15][15]/*保存网格情况*/;
struct node{
	int x,y;
}a[10];
bool cmp(node x,node y){
	return x.x*x.y>y.x*y.y;
}
int check(int x,int y,int l1,int l2){ //检测能不能放下 
	for(int i=min(h,x+l1-1);i>=x;i--){
		for(int j=min(w,y+l2-1);j>=y;j--){
			if(t[i][j])return (i-1)*w+j;
		}
	}
	return 0;
}
void work(int x,int y,int l1,int l2,int v){ //修改t数组的值 
	for(int i=x;i<=min(h,x+l1-1);i++){
		for(int j=y;j<=min(w,y+l2-1);j++){
			t[i][j]+=v;
		}
	}
}
void DFS(int x,int s){
	if(s==h*w)flag=1;
	if(flag||s>h*w||x>n||s+sum[n]-sum[x-1]<h*w)return; //一堆剪枝 
	DFS(x+1,s);
	if(flag)return;
	for(int i=1;i<=h-a[x].x+1;i++){
		for(int j=1;j<=w-a[x].y+1;j++){
			int k=check(i,j,a[x].x,a[x].y);
			if(k==0){
				work(i,j,a[x].x,a[x].y,1);
				DFS(x+1,s+a[x].x*a[x].y);
				if(flag)return;
				work(i,j,a[x].x,a[x].y,-1);
			}
			else{ //找右下角的点 
				int p=k%w;
				if(p==0)p=w;
				j=p; 
			}
		}
	}
	if(a[x].x!=a[x].y){ //翻转的情况 
		for(int i=1;i<=h-a[x].y+1;i++){
			for(int j=1;j<=w-a[x].x+1;j++){
				int k=check(i,j,a[x].y,a[x].x);
				if(k==0){
					work(i,j,a[x].y,a[x].x,1);
					DFS(x+1,s+a[x].x*a[x].y);
					if(flag)return;
					work(i,j,a[x].y,a[x].x,-1);
				}
				else{
					int p=k%w;
					if(p==0)p=w;
					j=p; 
				}
			}
		}
	}
}
int main(){
	scanf("%d %d %d",&n,&h,&w);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&a[i].x,&a[i].y);
	}
	sort(a+1,a+n+1,cmp); //排序 
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i].x*a[i].y; //前缀和方便剪枝 
	}
	DFS(1,0);
	if(flag)printf("Yes");
	else printf("No");
	return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc345_d)

## 思路

看完题意，不难想出，此题需要我们用搜索来实现，实现方法如下：

- 枚举矩形的左上端点，如果当前端点为空，同时可以装下第 $i$ 个东西，那么就更新当前矩形的状态和第 $i$ 个东西的状态，即是否在矩形中。向后搜索时，如果发现方案不行，需要先撤回当时对矩阵的更新，同时对第 $i$ 个东西的状态进行回溯。如果最后方案可行，直接输出 ``Yes``。

- 注：此题中，每个东西**都是可以进行翻转**的，即有两种情况，一种是长为 $a_i$，宽为 $b_i$，另一种则是长为 $b_i$，宽为 $a_i$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 15;

int a[N], b[N], k, n, m;

bool vis[N][N], flag[N];

bool check(int x, int y, int t){//长为 a，宽为 b时是否能放下
	if(x + a[t] - 1 > n || y + b[t] - 1 > m)return false;//超过范围
	for(int i = 1; i <= a[t]; i++){
		for(int j = 1; j <= b[t]; j++){
			if(vis[x + i - 1][y + j - 1])return false;//有东西覆盖过了
		}
	}
	return true;
}

bool check2(int x, int y, int t){//长为 b，宽为 a时是否能放下
	if(x + b[t] - 1 > n || y + a[t] - 1 > m)return false;//超过范围
	for(int i = 1; i <= b[t]; i++){
		for(int j = 1; j <= a[t]; j++){
			if(vis[x + i - 1][y + j - 1])return false;//有东西覆盖过了
		}
	}
	return true;
}

void add(int x, int y, int a, int b){//更新矩阵状态
	for(int i = 1; i <= a; i++){
		for(int j = 1; j <= b; j++){
			vis[x + i - 1][y + j - 1] = 1;
		}
	}
}

void del(int x, int y, int a, int b){//撤回更新的矩阵状态
	for(int i = 1; i <= a; i++){
		for(int j = 1; j <= b; j++){
			vis[x + i - 1][y + j - 1] = 0;
		}
	}
}

bool p(){//判断当前矩阵是否被东西全部覆盖
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(!vis[i][j])return false;
		}
	}
	return true;
}

void dfs(int x, int y){
	if(x == n + 1 && vis[n][m]){
		if(p()){
			puts("Yes");
			exit(0);
		}
	}
	if(y == m + 1){//换行
		dfs(x + 1, 1);
		return ;
	}
	if(vis[x][y])dfs(x, y + 1);
	for(int i = 1; i <= k; i++){
		if(!flag[i]){//判断第 i 个东西是否用过
			if(check(x, y, i)){//第一种情况
				flag[i] = true;
				add(x, y, a[i], b[i]);
				dfs(x, y + 1);
				del(x, y, a[i], b[i]);//回溯
				flag[i] = false;
			}if(check2(x, y, i)){//第二种情况
				flag[i] = true;
				add(x, y, b[i], a[i]);
				dfs(x, y + 1);
				del(x, y, b[i], a[i]);//回溯
				flag[i] = false;
			}
		}
	}
}

int main(){
	cin >> k >> n >> m;
	for(int i = 1; i <= k; i++){
		cin >> a[i] >> b[i];//第 i 个东西的长和宽
	}
	dfs(1, 1);
	puts("No");//没有可行方案
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc345_d)

## 思路

这题和[拼图](https://www.luogu.com.cn/problem/P3969)很像啊。我们考虑加回溯的 dfs。

读入数据后保存在一个结构体中。结构体要保存这个矩形的长、宽、是否放入标记。

在 dfs 中每次传递当前已经拼好的大小，如果全拼完了就输出 ``Yes`` 并结束程序；否则如果没有找到任何一种情况就输出 ``No``。

之后从 $1$ 到 $N$ 遍历每个矩形，如果已经在图中放过了或放不进图就跳过；反之就放进图（把图中要放入的部分记录为当前矩形的编号），并把这个矩形标记为已放入。

- 提示：放入的时候要分两种情况**分别** dfs，否则另一种情况可能没记录，会 WA。

回溯的时候删除图中的信息和这个矩形的放入标记即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50;
int n,m,k,g[N][N];
struct node{
	int r,c;
	bool use;
}a[N];
/*
变量名解释：
n 为题中的 H。
m 为题中的 W。
k 为题中的 N。
g[][] 是当前图的样子。
a[].r 是这个矩形的长。
a[].c 是这个矩形的宽。
a[].use 是这个矩形是否已经放进图的标记。
*/
inline void del(int id){//删除对应矩形。
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(g[i][j]==id)g[i][j]=0;
		}
	}
	return ;
}
inline bool check(node now,int id){//判断横着放并放入。
	for(int i=1;i<=n-now.r+1;++i){//找位置。
		for(int j=1;j<=m-now.c+1;++j){
			for(int x=i;x<=i+now.r-1;++x){//遍历当前位置开始是否能放。
				for(int y=j;y<=j+now.c-1;++y){
					if(g[x][y])goto next;//放不了。
				}
			}
			for(int x=i;x<=i+now.r-1;++x){//能放就修改。
				for(int y=j;y<=j+now.c-1;++y)g[x][y]=id;
			}
			return 1;
			next:;
		}
	}
	return 0;
}
inline bool check2(node now,int id){//判断竖着放并放入。
	for(int i=1;i<=n-now.c+1;++i){//找位置。
		for(int j=1;j<=m-now.r+1;++j){
			for(int x=i;x<=i+now.c-1;++x){//遍历当前位置开始是否能放。
				for(int y=j;y<=j+now.r-1;++y){
					if(g[x][y])goto next;//放不了。
				}
			}
			for(int x=i;x<=i+now.c-1;++x){//能放就修改。
				for(int y=j;y<=j+now.r-1;++y)g[x][y]=id;
			}
			return 1;
			next:;
		}
	}
	return 0;
}	
void dfs(int siz){
	if(siz==n*m){//放完了直接输出并结束程序。
		puts("Yes");
		exit(0);
	}
	for(int i=1;i<=k;++i){
		if(a[i].use)continue;
		if(check(a[i],i)){//横放。
			a[i].use=1;
			dfs(siz+a[i].r*a[i].c);
			a[i].use=0;
			del(i);
		}
		if(check2(a[i],i)){//竖放。
			a[i].use=1;
			dfs(siz+a[i].r*a[i].c);
			a[i].use=0;
			del(i);
		}
	}
    return ;
}
int main(){
	cin>>k>>n>>m;
	for(int p=1;p<=k;++p)cin>>a[p].r>>a[p].c;
	dfs(0);
    puts("No");//如果放不下，输出。
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/151231737)

---

