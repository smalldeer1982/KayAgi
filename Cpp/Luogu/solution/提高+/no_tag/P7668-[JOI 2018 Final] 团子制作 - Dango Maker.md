# [JOI 2018 Final] 团子制作 / Dango Maker

## 题目背景

你是一名专业的糕点师，制作团子，日本甜饺子。现在，你要串饺子了。

## 题目描述

饺子被放置在具有 $N$ 行和 $M$ 列的单元格网格上。每个单元格包含一个饺子。每个饺子的颜色是红色（$\texttt{R}$）、绿色（$\texttt{G}$）或 白色（$\texttt{W}$）。  
您将从单元格中选择三个连续的饺子，并将它们串成一根棍子。所选的三个连续饺子的方向必须是从左到右，或从上到下。  
现在，您要按此顺序制作颜色为红色、绿色、白色的饺子串。你想做尽可能多的饺子串。串到棍子上的饺子的顺序必须与从单元格中选择的饺子的顺序相同。一个饺子上不能串多根棍子。 
你能做多少串饺子？  
现给定放置在单元格上的饺子的颜色，请编写一个程序来计算您可以制作的饺子的最大数量。颜色必须按此顺序为红色、绿色、白色。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq N \leq 3000$，$1 \leq M \leq 3000$，$1 \leq i \leq N$，$1 \leq j \leq M$。  
- Subtask $1$（$13$ points）：$N \leq 4$，$M \leq 4$。  
- Subtask $2$（$20$ points）：$N \leq 10$，$M \leq 10$。  
- Subtask $3$（$67$ points）：没有额外的限制。  
#### 样例说明  
**对于样例 $1$**：你能制作 $3$ 串饺子。 
- 您从顶部的第一行和左侧的第一列中选择三个连续的饺子。方向是从左到右。然后，你按照这个顺序把它们串成一串。  
- 您从上数第一行和左数第 $4$ 列中选择三个连续的饺子。方向是从上到下。然后，你按照这个顺序把它们串成一串。  
- 您从上数第三行和左数第一列中选择三个连续的饺子。方向是从左到右。然后，你按照这个顺序把它们串成一串。  

因为你不能做 $4$ 串，所以输出 $3$。  
**对于样例 $2$**：你能制作 $4$ 串饺子。 
- 您从顶部的第一行和左侧的第一列中选择三个连续的饺子。方向是从左到右。然后，你按照这个顺序把它们串成一串。  
- 您从顶部的第一行和左侧的第 4 列中选择三个连续的饺子。方向是从上到下。然后，你按照这个顺序把它们串成一串。  
- 您从上数第二行和左数第二列中选择三个连续的饺子。方向是从上到下。然后，你按照这个顺序把它们串成一串。  
- 您从上数第二行和左数第三列中选择三个连续的饺子。方向是从上到下。然后，你按照这个顺序把它们串成一串。  

因为你不能做 $5$ 串，所以输出 $4$。  
#### 题目说明：  
来源于 The 17th Japanese Olympiad in Informatics (JOI 2017/2018) Final Round 的 [T3：Dango Maker](https://www.ioi-jp.org/joi/2017/2018-ho/2018-ho-t3-en.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
3 4
RGWR
GRGG
RGWW```

### 输出

```
3```

## 样例 #2

### 输入

```
4 4
RGWR
GRRG
WGGW
WWWR```

### 输出

```
4```

# 题解

## 作者：菲斯斯夫斯基 (赞：5)

### 前言

模拟赛的 T2，20 min 想出来的，怎么在 T2 放绿题。

### 思路

首先观察一波冲突多的情况:

```txt
RGWRGW
GWRGWR
WRGWRG
RGWRGW
GWRGWR
WRGWRG
```

考虑用 `R`、`G` 和 `W` 的其中一个字母来计算贡献。就是说假如选了一串，那么把这一串的贡献记录在其中一个字母的位置上。

可以发现 `R` 和 `W` 如果取了竖的饺子串，那么会影响上面的 $2$ 行和下面的 $2$ 行不能选横的饺子串。比如下面这个：选了左下角的 `W` 就不能选右上角的 `W` 了。可以自己手搓一下 `R` 和 `G` 的情况。

```txt
RGW
GWR
WRG
```

但是 `G` 只会影响右上一个和左下一个，处理起来比较方便。于是我们选 `G` 来计算贡献。

然后就是很明显的 dp 了，设 $dp_{i,0/1/2}$ 分别表示当前的 `G` 不选 / 选横的饺子串 / 选竖的饺子串。

动态转移方程显然：

$$dp_{i,0}=\max\{dp_{i-1,0},dp_{i-1,1},dp_{i-1,2}\}$$
$$dp_{i,1}=\max\{dp_{i-1,0},dp_{i-1,1}\}+f(x,y)$$
$$dp_{i,2}=\max\{dp_{i-1,0},dp_{i-1,2}\}+g(x,y)$$

其中 $f(x,y)$ 和 $g(x,y)$ 指 $(x,y)$ 这个点能不能放横的 / 竖的饺子串。

### 代码

不过注意是在斜线上会发生冲突，所以要在斜线上 dp。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3010;
int n,m,ans;
int dp[N<<1][5];
char c[N][N];
bool f(int x,int y)
{
	return y>=2&&y<=m-1&&c[x][y-1]=='R'&&c[x][y]=='G'&&c[x][y+1]=='W';
} 
bool g(int x,int y)
{
	return x>=2&&x<=n-1&&c[x-1][y]=='R'&&c[x][y]=='G'&&c[x+1][y]=='W';
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>c[i][j];
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<=max(n,m);j++)
			dp[j][0]=dp[j][1]=dp[j][2]=dp[j][3]=0;
		int id=0,x=1,y=i;
		while(x>=1&&x<=n&&y>=1&&y<=m)
		{
			id++;
			dp[id][0]=max(dp[id-1][0],max(dp[id-1][1],max(dp[id-1][2],dp[id-1][3])));
			dp[id][1]=max(dp[id-1][0],dp[id-1][1])+f(x,y);
			dp[id][2]=max(dp[id-1][0],dp[id-1][2])+g(x,y);
			x++,y--;
		}
		ans+=max(dp[id][0],max(dp[id][1],max(dp[id][2],dp[id][3])));
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<=max(n,m);j++)
			dp[j][0]=dp[j][1]=dp[j][2]=dp[j][3]=0;
		int id=0,x=i,y=m;
		while(x>=1&&x<=n&&y>=1&&y<=m)
		{
			id++;
			dp[id][0]=max(dp[id-1][0],max(dp[id-1][1],max(dp[id-1][2],dp[id-1][3])));
			dp[id][1]=max(dp[id-1][0],dp[id-1][1])+f(x,y);
			dp[id][2]=max(dp[id-1][0],dp[id-1][2])+g(x,y);
			x++,y--;
		}
		ans+=max(dp[id][0],max(dp[id][1],max(dp[id][2],dp[id][3])));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Starrykiller (赞：4)

简单题。

对于每个团子建一个点，对于冲突的团子连边。

任意构造出一棵生成树，直接做最大独立集（没有上司的舞会）即可。

感谢指正：构造出来的不一定是树。

但是我不会证明正确性，如果有人证明出来了或者 hack 掉了可以联系我（）。当然感性理解一下感觉还是挺对的？

时间复杂度 $\Theta(nm)$。[代码](https://loj.ac/s/2118210)。需要注意空间常数。

---

## 作者：TonviaSzt (赞：3)

简约风。

**分析**

首先想到二维前缀和，然后发现转移会算重，遂弃之。


启发考虑上述做法在什么条件下会算重，容易发现只有三种概型：

```
RGW    R       R
G     RGW      G
W      W     RGW
```

考虑处理交叉时选择横向串还是竖向串。

为了方便，用一个点表示一个串的位置，不妨举 $G$ 为串的象征点，可知每个 $G$ 点可能与其右上方的 $G$ 点产生冲突，设 $f_{i,j,0/1}$ 表示格子 $(i,j)$ 能否得到横向 $/$ 竖向串。

于是扫一遍 $n\times m$ 的网格，从右上方贪心转移 $f$，答案即 $\sum f_{i,j,0}|f_{i,j,1}$。

**正确性显然，每个 $G$ 点只可能与右上方的 $G'$ 点冲突，如果 $G'$ 可以转向以使 $G$ 合法则必转向。**

用 $R$ 或 $W$ 作象征点的转移同理。


**Code**

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=3e3+5;
int n,m,f[N][N][2],ans;
char s[N][N];
int main(){
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%s",s[i]+1);
    rep(i,1,n) rep(j,1,m) if(s[i][j]=='G'){
        f[i][j][0]=(s[i][j-1]=='R'&&s[i][j+1]=='W');
        f[i][j][1]=(s[i-1][j]=='R'&&s[i+1][j]=='W');
        if(f[i-1][j+1][0]|f[i-1][j+1][1]) f[i][j][0]&=f[i-1][j+1][0],f[i][j][1]&=f[i-1][j+1][1];
        ans+=f[i][j][0]|f[i][j][1];
    }printf("%d",ans);
}
```

---

## 作者：Epoch_L (赞：3)

## Solution
我们可以把一个符合要求的团子记录在中间那个 `G` 中，那么两个团子可能冲突，只有可能当前 `G` 竖着可以横着也可以，或者说两个或多个 `G` 在同一条 右上-左下 的对角线上。

![](https://cdn.luogu.com.cn/upload/image_hosting/1yd4iwwa.png?x-oss-process=image/resize,m_lfit,h_500,w_500)

如图，只有这两种情况会冲突，当然两种情况也有可能重叠。

于是我们把所有符合要求的 右上-左下 对角线的所有 `G` 全抠出来做 dp，最后合并答案即可。

设 $f(i,0/1/2)$ 表示每个 `G` 不选、横选、竖选，线性做一遍就没了。时间复杂度 $O(nm)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=3007,inf=1e9;
int n,m,f[N][3],tot,ans;
char c[N][N];
struct node{
  bool ok1,ok2;
}a[N][N],b[N];
bool used[N][N];
int dp(int n){
  for(int i=1;i<=n;i++)f[i][0]=f[i][1]=f[i][2]=-inf;
  f[1][0]=0;f[1][1]=b[1].ok1?1:-inf;f[1][2]=b[1].ok2?1:-inf;
  for(int i=2;i<=n;i++){
    f[i][0]=max({f[i-1][0],f[i-1][1],f[i-1][2]});
    if(b[i].ok1)f[i][1]=max(f[i-1][0],f[i-1][1])+1;
    if(b[i].ok2)f[i][2]=max(f[i-1][0],f[i-1][2])+1;
  }
  return max({f[n][0],f[n][1],f[n][2]});
}
int main(){
  read(n);read(m);
  for(int i=1;i<=n;i++)scanf("%s",c[i]+1);
  for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
    if(c[i][j]=='G'&&c[i][j-1]=='R'&&c[i][j+1]=='W')a[i][j].ok1=1;
    if(c[i][j]=='G'&&c[i-1][j]=='R'&&c[i+1][j]=='W')a[i][j].ok2=1;
  }
  for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
    tot=0;
    int x=i,y=j;
    while((a[x][y].ok1||a[x][y].ok2)&&x>0&&x<=n&&y>0&&y<=m&&!used[x][y])
      b[++tot]=a[x][y],used[x][y]=1,x++,y--;
    if(tot)ans+=dp(tot);
  }
  cout<<ans;
  return 0;
}
```

---

## 作者：LiveZoom (赞：2)

## Description

[link](https://www.luogu.com.cn/problem/P7668)

## Solution

如果两个团子重合肯定是下面三种情况：

```
  R          RGW          R
  G          G           RGW
RGW          W            W
```

我们会发现两个重合团子的 `G` 一定是在从右上到左下的对角线上的，且距离小于等于 $1$。根据这个性质就可以发现任意两个对角线上的团子肯定互不影响，那么对于每一个对角线进行 dp 即可。

其中 $f[i][0/1/2]$ 表示当前对角线上前 $i$ 行，第 $i$ 行的团子 不放/横放/竖放 的最大团子数，依次递推即可。

时间复杂度：$O(nm)$，吊打二分图。

## Code

```cpp
#include <bits/stdc++.h>

#ifdef ORZXKR
#include <debug.h>
#else
#define debug(...) 1
#endif

#define file(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)

using namespace std;

int read() {
  int x = 0, f = 0; char ch = getchar();
  while (ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
  while (ch >= '0' && ch <= '9') x = (x * 10) + (ch ^ 48), ch = getchar();
  return f ? -x : x;
}

const int kMaxN = 3005;

int n, m, ans;
int f[kMaxN][3]; // 0/1/2 : 不放/横放/竖放
char s[kMaxN][kMaxN];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
  }
  for (int sm = 2; sm <= n + m; ++sm) {
    memset(f, 0, sizeof(f));
    int tmp = 0;
    for (int i = max(1, sm - m), j = sm - i; i <= n && j; ++i, --j) {
      f[i][0] = max({f[i - 1][0], f[i - 1][1], f[i - 1][2]});
      if (s[i][j] == 'G') {
        if (s[i - 1][j] == 'R' && s[i + 1][j] == 'W') 
          f[i][1] = max(f[i][1], max(f[i - 1][0], f[i - 1][1]) + 1);
        if (s[i][j - 1] == 'R' && s[i][j + 1] == 'W')
          f[i][2] = max(f[i][2], max(f[i - 1][0], f[i - 1][2]) + 1);
      }
      tmp = max(tmp, max({f[i][0], f[i][1], f[i][2]}));
    }
    ans += tmp;
  }
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：7KByte (赞：2)

JOISC 2020 有一个团子提交题是个加强版，可以看下。

如果我们将可以得团子得地方看成一个点，如果两个团子有交点，则连边，我们要求得就是最大独立集。

由于只有横竖团子之间有边，所以是二分图，直接跑最大匹配即可。不知道时间是否卡的过去，没有试。

但是观察一下发现相交只有三种情况。

```
RGW   R     R
G    RGW    G
W     W   RGW
```

相交的团子 ``R`` 在同一条对角线上，不在一条对角线上的互不影响。

所以我们将所有相同对角线上的团子拎出来跑线性 $\rm DP$ 即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 3005
using namespace std;
int n,m;char s[N][N];
inline bool check(int x,int y,int op){
	if(!op)return s[x][y]=='R'&&s[x][y+1]=='G'&&s[x][y+2]=='W';
	return s[x][y]=='R'&&s[x+1][y]=='G'&&s[x+2][y]=='W';
}
int f[N][3][3];
inline void ck(int &x,int y){if(y>x)x=y;}
int main(){
	scanf("%d%d",&n,&m);int ans = 0;
	rep(i,1,n)scanf("%s",s[i] + 1);
	rep(i, 2, n + m - 2){
		int l = max(1, i - m), r = min(n, i - 1);
		memset(f,0xcf,sizeof(f));
		f[0][0][0] = 0;
		rep(j, l, r){
			if(check(j, i - j, 1))rep(p,0,2)rep(q,0,2)
				ck(f[j - l + 1][2][q], f[j - l][q][p] + 1);
			if(check(j ,i - j, 0))rep(p,0,1)rep(q,0,1)
				ck(f[j - l + 1][1][q], f[j - l][q][p] + 1);
			rep(p,0,2)rep(q,0,2)ck(f[j - l + 1][0][q], f[j - l][q][p]);
		}
		int cur = 0;
		rep(p,0,2)rep(q,0,2)ck(cur, f[r - l + 1][p][q]);
		ans += cur;
	}
	printf("%d\n",ans);return 0;
}
```

---

## 作者：Daniel_yao (赞：1)

根据手模样例有所启发，造成贡献矛盾的情况如以下情况：

```
   R
  RGW
 RGW
RGW
 W
```
造成矛盾的对象为 $\texttt{R}$ 或 $\texttt{W}$，本质上是以 $\texttt{G}$ 为中心，竖直还是横向放置的矛盾。于是记 $dp_{i,j,0/1}$ 表示以 $(i,j)$ 为中心，是否能横向/竖直放置。当 $a_{i,j}=\text{G}$ 时，先判断以它为中心是否能横向/竖直放置。然后再贪心决策：

- 如果 $a_{i-1,j+1}=\text{G}$ 且 $(i+1,j-1)$ 不能同时竖直和横向放置，则 $(i,j)$ 按照 $(i+1,j-1)$ 的放置方向保持一致（若无法一致则不放置）。
- 如果 $a_{i-1,j+1}=\text{G}$ 且 $(i+1,j-1)$ 能同时竖直和横向放置，则 $(i,j)$ 放置方式随意（若无法放置则不放置）。

考虑正确性，每一步都符合放置要求，且不存在放置重叠的情况，正确性正确。

考虑最优性，每一步决策无非两种：放与不放。按照以上放置方法，不会存在放置之后冲突需要重构的情况。假设以上做法不是最优的，即需要放置之后暴力重构。则重构之后一定会存在有原来能够放置，重构之后不能放置的情况，且个数 $\ge 1$。所以不重构不会使答案变得更劣。说明以上方法是最优的，最优性正确。

贪心模拟即可。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 3e3 + 10;

int n, m, ans;

bool dp[N][N][2];

char a[N][N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  For(i,1,n) For(j,1,m) cin >> a[i][j];
  For(i,1,n) {
    For(j,1,m) {
      if(a[i][j] == 'G') {
        if(a[i][j-1] == 'R' && a[i][j+1] == 'W') dp[i][j][0] = 1;
        if(a[i-1][j] == 'R' && a[i+1][j] == 'W') dp[i][j][1] = 1;
        if(a[i-1][j+1] == 'G' && (dp[i-1][j+1][0] ^ dp[i-1][j+1][1])) {
          dp[i][j][0] &= dp[i-1][j+1][0];
          dp[i][j][1] &= dp[i-1][j+1][1];
        }
      }
      ans += (dp[i][j][0] | dp[i][j][1]);
    }
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：lkjzyd20 (赞：0)

### 题意
给出一个由 `R G W` 组成的表格，问你能取出多少串 `RGW`。
### 思路
如果两个团子重合是下面三种情况
```
RGW   R    R
G     G   RGW
W   RGW    W
```
我们发现相交的团子在同一条对角线上，不在一条对角线上的互不影响，所以我们设 $f_{i,j,0/1/2}$ 为选 $[i,j],[i-1,j+1],[i-2,j+1]$ 的最大方案，转移为
$$
f_{i,j,0} = \max(f_{i-1,j+1,0},f_{i-1,j+1,1}, f_{i-1,j+1,2})\\
f_{i,j,1} = \max(f_{i-1,j+1,1}, f_{i-1,j+1,0}) + 1\\
f_{i,j,2} = \max(f_{i-1,j+1,2}, f_{i-1,j+1,0}) + 1\\
\text{ans} = \max(f_{i-1,j+1,0},f_{i-1,j+1,1},f_{i-1,j+1,2})\\
$$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)

const int N = 3010;
char s[N][N];
int f[N][N][4], ans, n, m;
void check(int i, int j) 
{
	for (; i <= n && j >= 1; ++ i, -- j) 
    {
        int ti = i - 1, tj = j + 1;
		f[i][j][0] = max({f[ti][tj][0], f[ti][tj][1], f[ti][tj][2]});
		if(i - 1 >= 1 && i + 1 <= n && s[i][j] == 'G' && s[i - 1][j] == 'R' && s[i + 1][j] == 'W')
		    f[i][j][1] = max(f[ti][tj][1], f[ti][tj][0]) + 1;
		if(j - 1 >= 1 && j + 1 <= m && s[i][j] == 'G' && s[i][j - 1] == 'R' && s[i][j + 1] == 'W')
			f[i][j][2] = max(f[ti][tj][2], f[ti][tj][0]) + 1;
	}
	ans += max({f[-- i][++ j][0], f[i][j][1], f[i][j][2]});
}
main() 
{
	scanf("%d %d", &n, &m);
	rep(i, 1, n) scanf("%s", s[i] + 1);
    rep(i, 1, m) check(1, i);
    rep(i, 2, n) check(i, m);
    printf("%d", ans);
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：0)

# Solution

由于 `G` 在中间，我们考虑将一串选不选记在 `G` 上。我们发现会互相影响的 `G` 一定是 $(i,j),(i-1,j+1)$。

记 $f_{i,j,0/1/2}$ 是选了 $(i,j),(i-1,j+1),(i-2,j+2),\cdots$，$(i,j)$ 没选 / 选了竖的 / 选了横的的最大方案，转移显然。

建议阅读代码。

# Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 3005;
	int n, m, rs, chk[N][N][2], f[N][N][3]; char a[N][N];
	int main() {
		cin >> n >> m;
		REP(i, 1, n) REP(j, 1, m) cin >> a[i][j];
		REP(i, 1, n) REP(j, 1, m) {
			chk[i][j][0] = (a[i - 1][j] == 'R' && a[i][j] == 'G' && a[i + 1][j] == 'W');
			chk[i][j][1] = (a[i][j - 1] == 'R' && a[i][j] == 'G' && a[i][j + 1] == 'W');
		}
		REP(i, 1, n) DEP(j, m, 1) {
			int *p = f[i][j], *q = f[i - 1][j + 1];
			p[0] = max({q[0], q[1], q[2]});
			p[1] = max({q[0], q[1]}) + chk[i][j][0];
			p[2] = max({q[0], q[2]}) + chk[i][j][1];
			if (i == n || j == 1) rs += max({p[0], p[1], p[2]});
		}
		cout << rs << '\n';
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：Miku_QwQ (赞：0)

首先我们还是先把原题建模成图，有冲突的 $\texttt{RGW}$ 之间连边。为了表述方便，我们记新图的点数为 $V$，边数为 $E$。则原问题等价于新图上的最大独立集问题。

## 算法1：

我会做 NP 问题！

直接暴力，复杂度 $O(2^V)$，得分 $13$ pts。

## 算法2：

我会分析！

我们发现由于 $\texttt{RGW}$ 是一个每一位不同的字符串，所以不可能存在两个同向的 $\texttt{RGW}$ 冲突，所以原图是一个二分图。

又发现因为每个 $\texttt{RGW}$ 最多与三个异向的 $\texttt{RGW}$ 冲突，所以 $V$ 和 $E$ 同阶。

直接匈牙利即可，复杂度 $O(VE)$，得分 $33$ pts。

## 算法3：

我会优化！

匈牙利可以换成 Dinic，戳 [这里](https://oi-wiki.org/graph/graph-matching/bigraph-match/)。

时间复杂度可以做到 $O(\sqrt{V}E)$，得分 $33$ pts。

## 算法4：

我会观察！

在下文中，我们用 $\texttt{R}$ 的位置来给 $\texttt{RGW}$ 定位，并且我们钦定二分图左半部分为横向 $\texttt{RGW}$，右半部分为纵向 $\texttt{RGW}$。

我们发现，产生冲突的 $\texttt{RGW}$ 一定是如下的：

$$\texttt{..R}$$

$$\texttt{.RG}$$

$$\texttt{RGW}$$

$$\texttt{GW.}$$

$$\texttt{W..}$$

如上，中间的横向 $\texttt{RGW}$ 被三个纵向 $\texttt{RGW}$ 覆盖。

比如在上图中，三个 $\texttt{R}$ 的坐标分别为 $(1,3)$，$(2,2)$ 和 $(3,1)$，和都是 $4$。

接下来我们就可以对二分图两边的点按照 $x+y$ 从小到大排序，相等的按照 $x$ 从小到大排序，容易发现此时左半部分的一个点必定连向右半部分的一个区间。

而最大独立集问题可以转化为最小点覆盖问题，于是问题转化为下面的形式：

> 有 $t$ 个整区间 $[l_i,r_i]$，选出其中的 $k$ 个区间，满足可以找到 $k$ 个不同整点 $x_i$，满足 $x_i \in [l_i,r_i]$，求 $k$ 的最大值。

容易发现这个问题可以直接贪心。由于在前面的过程中已经将区间从小到大处理了，所以不需要排序。

贪心策略就是尽量选择靠左的点匹配，容易发现这样一定不劣。

时间复杂度 $O(nm)$，得分 $100$ pts。

附上代码。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char ch[3010][3010];
int id[3010][3010];
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch[i][j];
		}
	}
	int ans=0;
	for(int k=2;k<=n+m-2;k++){
		for(int i=1;i<=n;i++){
			int j=k-i;
			if(j>=1  &&  j<=m){
				if(ch[i][j]=='R'  &&  ch[i][j+1]=='G'  &&  ch[i][j+2]=='W'){
					id[i][j]=++ans;
				}
			}
		}
	}
	int tot=0,maxn=0;
	for(int k=2;k<=n+m-2;k++){
		for(int i=1;i<=n;i++){
			int j=k-i;
			if(j>=1  &&  j<=m){
				if(ch[i][j]=='R'  &&  ch[i+1][j]=='G'  &&  ch[i+2][j]=='W'){
					ans++;
					int l=0x3f3f3f3f,r=-0x3f3f3f3f;
					for(int pre=0;pre<3;pre++){
						if(j-pre>=1  &&  id[i+pre][j-pre]){
							l=min(l,id[i+pre][j-pre]);
							r=max(r,id[i+pre][j-pre]);
						}
					}
					if(l!=0x3f3f3f3f){
						if(l>maxn){
							maxn=l;
							tot++;
						}
						else if(r>maxn){
							maxn++;
							tot++;
						}
					}
				}
			}
		}
	}
	printf("%d",ans-tot);
	return 0;
}
```

---

## 作者：山田リョウ (赞：0)

萌新不会 dp，直接贪的

相当于选择尽可能多的竖着或横着的 `RGW` 块使得互不相交。考虑到抽象成点，将相交的块对应点间连边，发现由于 `R`、`G`、`W` 互不相同所以同方向块不会相交，故构成二分图，即求二分图最大独立集。

根据经典结论，二分图最大独立集大小为总点数减去最大匹配数，故求最大匹配即可。

发现这个图具有良好性质，大胆猜测在原矩阵上从上至下、从左至右依次枚举横向块，从右至左枚举出度，能匹配就匹配后并退出即可，正确性显然。

[code](https://www.luogu.com.cn/paste/4sfh82zt)

---

