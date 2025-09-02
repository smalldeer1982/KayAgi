# 団子職人 (Dango Maker)

## 题目描述

你是一个包団子（日本传统食物，不要在意）的工匠。现在你要把団子串起来了。

所有的団子都放在一个正方形中，分为 $N$ 行和 $M$ 列。 每个点上有 $1$ 个団子。 每个団子的颜色为红色（R）、绿色（G）或白色（W）其中一种。你可以从左到右或从上到下连续取出 $3$ 个団子，然后按取出的顺序将 $3$ 个団子粘在 $1$ 个串上。

现在你想串尽可能多的串，但这些串上的団子必须按照 $1$ 个红、$1$ 个绿、$1$ 个白的顺序。另外，一个団子只能放在一个串上。

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

## 样例 #3

### 输入

```
5 5
RGRGW
GRRGW
WGGWR
RWRGW
RGWGW```

### 输出

```
6```

# 题解

## 作者：Starrykiller (赞：3)

简单题。

对于每个团子建一个点，对于冲突的团子连边。

任意构造出一棵生成树，直接做最大独立集（没有上司的舞会）即可。

感谢指正：构造出来的不一定是树。

但是我不会证明正确性，如果有人证明出来了或者 hack 掉了可以联系我（）。当然感性理解一下感觉还是挺对的？

时间复杂度 $\Theta(nm)$。[代码](https://loj.ac/s/2118210)。需要注意空间常数。

---

## 作者：CAO654321 (赞：2)

## Solution:

我们会发现两个重合团子的 $G$ 一定是在从右上到左下的对角线上的，且距离小于等于 1，根据这个性质就可以发现任意两个对角线上的团子肯定互不影响，那么对于每一个对角线进行 dp 即可。


其中
 $f[i][0/1/2]$
 表示当前对角线上前 $i$ 行，第 $i$ 行的团子的三种情况（不放/横放/竖放）的最大团子数，依次递推即可。


## CODE:
```c
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

## 作者：菲斯斯夫斯基 (赞：1)

### 前言

既然题目是双倍经验，那么题解应该也可以是双倍经验吧。

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

## 作者：Asedwai (赞：0)

## 思路
  贪心大法好。  
  
  做这种题首先想到要枚举团子 `G`，那么要么是横着的 `RGW`，要么是竖着的。如果只有横着的或者竖着的，那么我们就直接消掉。考虑到什么时候需要在两者中选择，当且仅当位置 $(i,j)$ 构成横着与竖着的 `RGW`，并且位置 $(i-1,j-1)$ 同样满足，所以相互影响的会在同一条斜线上。考虑下面的数据（`*` 可以是任意颜色）：  
  
  数据 $1$：
```txt
***R*
**RGW
*RGW*
RGW**
```
  数据 $2$：  
```txt
**R* 
*RGW
RGW*
GW**
W***
```
  显而易见，对于数据 $1$，我们都会选则消掉横着的 `RGW`。而对于数据 $2$，我们都会选择消掉竖着的 `RGW`。由此我们可以想到直接跑到那个不能够再选择的 `G` 点消掉 `RGW`，然后用同样的方式将这条斜线上的所有 `RGW` 消掉。如果都是需要选择的，任意一种方式即可。  
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define endl "\n"
#define fer(i, a, b) for(int i = (a); i <= (b); i ++)
#define LL long long
const auto Maxn = (LL) 3e3 + 10;
int n, m; 
char a[Maxn][Maxn]; 
LL ans; 
bool check(int i, int j, char c) {
	if(i > 0 && j > 0 && i <= n && j <= m) return a[i][j] == c; 
	return 0; 
}
int dfs(int i, int j) {
	if(check(i, j, 'G')) {
		bool f1 = check(i - 1, j, 'R') && check(i + 1, j, 'W'); 
		bool f2 = check(i, j - 1, 'R') && check(i, j + 1, 'W'); 
		int k = 0; 
		if(f1 && f2) {
			int k = dfs(i + 1, j - 1); 
			if(k <= 1) {
				a[i][j] = ' '; 
				a[i - 1][j] = ' '; 
				a[i + 1][j] = ' '; 
				++ ans; 
			}
			if(k == 2) {
				a[i][j] = ' '; 
				a[i][j - 1] = ' '; 
				a[i][j + 1] = ' '; 
				++ ans; 
			}
			return k; 
		}
		if(f1) {
			a[i][j] = ' '; 
			a[i - 1][j] = ' '; 
			a[i + 1][j] = ' '; 
			++ ans; 
			return 1; 
		}
		if(f2) {
			a[i][j] = ' '; 
			a[i][j - 1] = ' '; 
			a[i][j + 1] = ' '; 
			++ ans; 
			return 2; 
		}
	}
	return 0; 
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr); 
	cin >> n >> m; 
	fer(i, 1, n) {
		fer(j, 1, m) {
			cin >> a[i][j]; 
		}
	}
	fer(i, 1, n) {
		fer(j, 1, m) {
			dfs(i, j); 
		}
	}
	cout << ans << endl; 
	return 0; 
}
```

---

