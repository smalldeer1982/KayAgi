# Hossam and a Letter

## 题目描述

Hossam bought a new piece of ground with length $ n $ and width $ m $ , he divided it into an $ n \cdot m $ grid, each cell being of size $ 1\times1 $ .

Since Hossam's name starts with the letter 'H', he decided to draw the capital letter 'H' by building walls of size $ 1\times1 $ on some squares of the ground. Each square $ 1\times1 $ on the ground is assigned a quality degree: perfect, medium, or bad.

The process of building walls to form up letter 'H' has the following constraints:

- The letter must consist of one horizontal and two vertical lines.
- The vertical lines must not be in the same or neighboring columns.
- The vertical lines must start in the same row and end in the same row (and thus have the same length).
- The horizontal line should connect the vertical lines, but must not cross them.
- The horizontal line can be in any row between the vertical lines (not only in the middle), except the top and the bottom one. (With the horizontal line in the top row the letter looks like 'n', and in the bottom row like 'U'.)
- It is forbidden to build walls in cells of bad quality.
- You can use at most one square of medium quality.
- You can use any number of squares of perfect quality.

Find the maximum number of walls that can be used to draw the letter 'H'.

Check the note for more clarification.

## 说明/提示

In the first test case, we can't build the letter 'H'.

For the second test case, the figure below represents the grid and some of the valid letters 'H'. Perfect, medium, and bad squares are represented with white, yellow, and black colors respectively.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1771E/7ab52d112de710667f4c7cf4e814613751fe43eb.png)

## 样例 #1

### 输入

```
2 3
#m.
.#.```

### 输出

```
0```

## 样例 #2

### 输入

```
7 8
...#.m..
..m...m.
.#..#.m#
...m..m.
m.......
..#.m.mm
......m.```

### 输出

```
16```

# 题解

## 作者：uid_310801 (赞：2)

本题和 NOIP2022 T1 有点相似。

首先注意到数据范围支持我们 $O(n^3)$ 处理，这就说明我们可能不用搞那些奇怪的前缀和之类的东西了。

先预处理出 $up_{i,j,k}$ 表示从 $(i,j)$ 出发，往上走，至多经过 $k$ 个 $m$，能走到的最远的位置。这里直接暴力求就行了。$dn_{i,j,k}$ 同理。

一个细节：由于之后判断无解可能比较麻烦，如果某一个位置答案是 $0$，那么就将它设为负无穷好了。

将 H 拆分成一个横线和四个竖线。

枚举中间一横的位置，可以 $O(n^3)$ 枚举。

假设我们枚举的横的两端的坐标是 $(i,j),(i,k)$，且横线覆盖了一个 `m`，那么我们钦定四个竖线必须没有覆盖 `m`。这个位置的答案就是：

$$(k-j+1)+\min(up_{i-1,j,0},up_{i-1,k,0})\times 2+\min(dn_{i+1,j,0},dn_{i+1,k,0})\times2$$

若横线未覆盖 `m`，则允许至多一个`m`出现在另外四个竖线上，枚举出现在哪一个上即可。

虽然代码较长，但大多是复制粘贴，实现起来还是比较容易的。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define deb(x) cerr<<"Line: "<<__LINE__<<", val= "<<x<<"; \n"
typedef long long ll;
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=400+10;
ll n,m,ans=0;
char ma[N][N];
ll up[N][N][2],dn[N][N][2];
signed main(){
	scanf("%lld %lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",ma[i]+1);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ll flag=0,cnt=0;
			for(int k=i;k>=1;k--){
				if(ma[k][j]=='#')	break;
				if(ma[k][j]=='m'){
					if(flag==1)	break;
					else flag=1;
				}
				cnt++;
				if(!flag)	up[i][j][0]=cnt;
				up[i][j][1]=cnt;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ll flag=0,cnt=0;
			if(ma[i][j]=='#'){
				dn[i][j][0]=dn[i][j][1]=up[i][j][0]=up[i][j][1]=-1e18;
			}
			if(ma[i][j]=='m'){
				dn[i][j][0]=up[i][j][0]=-1e18;
			}//为了方便，我们这样处理无解的情况。
			for(int k=i;k<=n;k++){
				if(ma[k][j]=='#')	break;
				if(ma[k][j]=='m'){
					if(flag==1)	break;
					else flag=1;
				}
				cnt++;
				if(!flag)	dn[i][j][0]=cnt;
				dn[i][j][1]=cnt;
			}
		}
	}
	for(int i=2;i<n;i++){
		for(int j=1;j<=m;j++){
			ll flag=0;
			for(int k=j;k<=m;k++){
				if(ma[i][k]=='#')	break;
				if(ma[i][k]=='m'){
					if(flag==1)	break;
					else flag=1;
				}
				if(k-j>=2){
					ans=max(ans,k-j+1+min(up[i-1][j][0],up[i-1][k][0])*2+min(dn[i+1][j][0],dn[i+1][k][0])*2);
					if(!flag){
						ans=max(ans,k-j+1+min(up[i-1][j][1],up[i-1][k][0])*2+min(dn[i+1][j][0],dn[i+1][k][0])*2);
						ans=max(ans,k-j+1+min(up[i-1][j][0],up[i-1][k][1])*2+min(dn[i+1][j][0],dn[i+1][k][0])*2);
						ans=max(ans,k-j+1+min(up[i-1][j][0],up[i-1][k][0])*2+min(dn[i+1][j][1],dn[i+1][k][0])*2);
						ans=max(ans,k-j+1+min(up[i-1][j][0],up[i-1][k][0])*2+min(dn[i+1][j][0],dn[i+1][k][1])*2);
					}
				}
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
/*give my heart to 7f*/
```


---

## 作者：StayAlone (赞：2)

### 前言

有人说比种花困难，那应该高估此题了。此题相对种花细节多一些，但是思维量更低。

### 题意

给定一个仅包含 `#`、`.`、`m` 的 $n$ 行 $m$ 列的矩阵，你需要找到一些能组成 `H` 的格子。这个 `H` 需满足以下要求：

- 由两条竖直的线段和一条水平的线段组成。

- 两条竖直的线段由同一行开始，在同一行结束，且不能在同一列或相邻列。

- 水平的线段将两条竖直线段相连，但不在竖直线段的最后一行或第一行。注意水平的线段不能跨越竖直的线段。

- 不得包含 `#`，最多包含一个 `m`。

在满足条件的 `H` 中，找到所占格子数量最多的那个。输出其所占格子的数量。不存在输出 $0$。

$1\leq n,m \leq 400$。

### 思路

先想到枚举水平线段的左端点以及水平线段的长度，同时就确定了两条竖直线段所在列。

因此先预处理

- $gu_{0/1,i,j}$ 表示从 $(i, j)$ 开始向上走，经过最多 0/1 个 `m` 能走的最长长度。

- $gd_{0/1,i,j}$ 表示从 $(i, j)$ 开始向下走，经过最多 0/1 个 `m` 能走的最长长度。

本文中 $(i, j)$ 本身要算。

在枚举的过程中，记录一下水平线段是否经过了 `m`。若经过了，则竖直的两条线段都不能含有 `m`；反之，枚举一下 `m` 在哪条线段上，对于水平线段的端点正好是 `m` 的情况特殊处理，几种情况取 $\max$ 即可。

看起来代码有点长，其实都是复制粘贴，细节也并非难以处理。时间复杂度 $\Theta(nm^2)$。

[AC code record](https://www.luogu.com.cn/record/98058881)
```cpp
int n, m; char s[410][410];
int gu[2][410][410]; // 向上用 0/1 个 m 能走的最远长度
int gd[2][410][410]; // 向下用 0/1 个 m 能走的最远长度

int main() {
	read(n, m);
	rep1(i, 1, n) scanf("%s", s[i] + 1);
	rep1(j, 1, m) {
		rep1(i, 1, n) {
			if (s[i][j] == '#');
			else if (s[i][j] == 'm') {
				gu[1][i][j] = gu[0][i - 1][j] + 1;
				gu[0][i][j] = 0;
			} else {
				gu[1][i][j] = gu[1][i - 1][j] + 1;
				gu[0][i][j] = gu[0][i - 1][j] + 1;
			}
		}
	}
	rep1(j, 1, m) {
		rep2(i, n, 1) {
			if (s[i][j] == '#');
			else if (s[i][j] == 'm') {
				gd[1][i][j] = gd[0][i + 1][j] + 1;
				gu[0][i][j] = 0;
			} else {
				gd[1][i][j] = gd[1][i + 1][j] + 1;
				gd[0][i][j] = gd[0][i + 1][j] + 1;
			}
		}
	} int ans = 0;
	rep1(i, 1, n) rep1(j, 2, m - 1) { // 枚举 H 横杠的左端点
		if (s[i][j] == '#') continue;
		int mcnt = s[i][j] == 'm', x = i, y = j - 1; // 表示 H 横杠使用的 m 数量
		rep1(len, 1, m) { // 枚举 H 横杠的长度
			if (s[i][j + len] == '#' || j + len > m) break;
			if (s[i][j + len] == 'm') {
				if (!mcnt) ++mcnt;
				else break;
			}
			int nx = i, ny = j + len;
			auto cal = [&](int lend, int lenu, int p) {return lend > 1 && lenu > 1 ? p + (lend - 1) * 2 + lenu * 2 : -1;};
			if (mcnt) {
				ans = max(ans, cal(min(gd[0][x][y], gd[0][nx][ny]), min(gu[0][x][y], gu[0][nx][ny]), len));
			} else {
				ans = max({ans, cal(min(gd[0][x][y], gd[0][nx][ny]), min(gu[0][x][y], gu[0][nx][ny]), len),
				cal(min(gd[1][x][y], gd[0][nx][ny]), min(gu[0][x][y], gu[0][nx][ny]), len),
				cal(min(gd[0][x][y], gd[1][nx][ny]), min(gu[0][x][y], gu[0][nx][ny]), len),
				cal(min(gd[0][x][y], gd[0][nx][ny]), min(gu[1][x][y], gu[0][nx][ny]), len),
				cal(min(gd[0][x][y], gd[0][nx][ny]), min(gu[0][x][y], gu[1][nx][ny]), len)});
				if (s[x][y] == 'm') {
					ans = max(ans, cal(min(gd[1][x][y], gd[0][nx][ny]), min(gu[1][x][y], gu[0][nx][ny]), len));
				}
				if (s[nx][ny] == 'm') {
					ans = max(ans, cal(min(gd[0][x][y], gd[1][nx][ny]), min(gu[0][x][y], gu[1][nx][ny]), len));
				}
			}
		}
	} printf("%d", ans);
	rout;
}
```

---

## 作者：Cxny (赞：1)

$\text{NOIP2022\ T1}$ 加强版？

一样的套路，先预处理出每个点向上或向下经过 $0$ 或 $1$ 个 `m` 能达到的最远距离。

然后枚举水平线的端点，经过 `m` 和不经过 `m` 取 $\max$ 即可。

~~一开始以为是计数……还调了半天。~~

可能有一点点细节。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 410;
int n, m, up[maxn][maxn][2], dw[maxn][maxn][2];
char s[maxn][maxn];
signed main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++){
        if(s[i][j] == '#') up[i][j][0] = up[i][j][1] = 0;
        else if(s[i][j] == '.') up[i][j][0] = up[i - 1][j][0] + 1, up[i][j][1] = up[i - 1][j][1] + 1;
        else up[i][j][0] = 0, up[i][j][1] = up[i - 1][j][0] + 1;
    }
    for(int i = n; i >= 1; i--) for(int j = 1; j <= m; j++){
        if(s[i][j] == '#') dw[i][j][0] = dw[i][j][1] = 0;
        else if(s[i][j] == '.') dw[i][j][0] = dw[i + 1][j][0] + 1, dw[i][j][1] = dw[i + 1][j][1] + 1;
        else dw[i][j][0] = 0, dw[i][j][1] = dw[i + 1][j][0] + 1;
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++){
        if(s[i][j] == 'm') up[i][j][0] = up[i][j][1], dw[i][j][0] = dw[i][j][1];
        // printf("%d %d: %d %d %d %d\n", i, j, up[i][j][0], up[i][j][1], dw[i][j][0], dw[i][j][1]);
    }
    int ans = 0;
    for(int i = 2; i < n; i++) for(int j = 1; j <= m - 2; j++) if(s[i][j] != '#'){
        int cnt = (s[i][j] == 'm') + (s[i][j + 1] == 'm');
        if(cnt > 1 || s[i][j + 1] == '#' || s[i][j + 2] == '#') continue;
        for(int k = j + 2; k <= m; k++){
            if(s[i][k] == '#') break;
            cnt += (s[i][k] == 'm');
            if(cnt > 1) break;
            int det = 0;
            if(up[i][j][0] == 1 || up[i][k][0] == 1 || dw[i][j][0] == 1 || dw[i][k][0] == 1);
            else det = 2 * (min(up[i][j][0], up[i][k][0]) + min(dw[i][j][0], dw[i][k][0])) + k - j - 3;
            if(!cnt){
                if(up[i][j][1] > 1 && up[i][k][0] > 1 && dw[i][j][0] > 1 && dw[i][k][0] > 1) det = max(det, 2 * (min(up[i][j][1], up[i][k][0]) + min(dw[i][j][0], dw[i][k][0])) + k - j - 3);
                if(up[i][j][0] > 1 && up[i][k][1] > 1 && dw[i][j][0] > 1 && dw[i][k][0] > 1) det = max(det, 2 * (min(up[i][j][0], up[i][k][1]) + min(dw[i][j][0], dw[i][k][0])) + k - j - 3);
                if(up[i][j][0] > 1 && up[i][k][0] > 1 && dw[i][j][1] > 1 && dw[i][k][0] > 1) det = max(det, 2 * (min(up[i][j][0], up[i][k][0]) + min(dw[i][j][1], dw[i][k][0])) + k - j - 3);
                if(up[i][j][0] > 1 && up[i][k][0] > 1 && dw[i][j][0] > 1 && dw[i][k][1] > 1) det = max(det, 2 * (min(up[i][j][0], up[i][k][0]) + min(dw[i][j][0], dw[i][k][1])) + k - j - 3);
            }
            // if(det) printf("%d %d %d - %d\n", i, j, k, det);
            ans = max(ans, det);
        }
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Mugino_Shizuri (赞：0)

[link](https://www.luogu.com.cn/problem/CF1771E)

比较简单的题，奇为暴力。

首先发现 $n\leq 400$ 猜测到应该是用一个什么东西来优化纯暴力，然后便能想到 DP。

可以发现该数据范围支持我们枚举位置后再枚举一个东西，在这里我选择枚举横条的长度，因为比较方便。考虑枚举出来横条后，不能直接找暴力竖条，于是考虑通过提前预处理来得到竖条长度。

设 $f[i][j][0/1]$ 表示从 $(i,j)$ 向下走，经历 $0/1$ 个 'm' 点的最长路径（不包括起点）。向下走同理，不包括起点这一点不用想太多，就是怕算重。记录答案时别忘了必须要朝上下走，否则不合法。

然后就可以 $O(n^3)$ 暴力预处理，再 $O(n^3)$ 暴力统计答案。

在格子周围加了一圈 '#' 来规避边界分讨。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=410;
int n,m,f[N][N][2],g[N][N][2],Ans,a[N][N];
char x;

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			cin>>x;a[i][j]=(x=='#'?2:(x=='m'));
		}
	for(int i=0;i<=n+1;++i) a[i][0]=a[i][m+1]=2;
	for(int i=0;i<=m+1;++i) a[0][i]=a[n+1][i]=2;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			for(int k=i+1,ct=0;k<=n+1;++k){
				if(a[k][j]) {
					if(!ct) f[i][j][0]=k-i-1;
					else f[i][j][1]=k-i-1;
					if(a[k][j]==2) break;
					if((++ct)==2) break;
				}
			}
			for(int k=i-1,ct=0;~k;--k){
				if(a[k][j]){
					if(!ct) g[i][j][0]=i-k-1;
					else g[i][j][1]=i-k-1;
					if(a[k][j]==2) break;
					if((++ct)==2) break;
				}
			}
		} 
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			int fg=(a[i][j]==1)+(a[i][j+1]==1);
			if(a[i][j]==2||a[i][j+1]==2) continue;
			for(int k=j+2;k<=m;++k){
				fg+=(a[i][k]==1);
				if(fg>=2||a[i][k]==2) break;
				if(fg){
					if(f[i][j][0]&&g[i][j][0]&&f[i][k][0]&&g[i][k][0]) Ans=max(Ans,k-j+1+min(f[i][j][0],f[i][k][0])*2+min(g[i][j][0],g[i][k][0])*2);
				}else {
					if(f[i][j][1]&&g[i][j][0]&&f[i][k][0]&&g[i][k][0]) Ans=max(Ans,k-j+1+min(f[i][j][1],f[i][k][0])*2+min(g[i][j][0],g[i][k][0])*2);
					if(f[i][j][0]&&g[i][j][1]&&f[i][k][0]&&g[i][k][0]) Ans=max(Ans,k-j+1+min(f[i][j][0],f[i][k][0])*2+min(g[i][j][1],g[i][k][0])*2);
					if(f[i][j][0]&&g[i][j][0]&&f[i][k][1]&&g[i][k][0]) Ans=max(Ans,k-j+1+min(f[i][j][0],f[i][k][1])*2+min(g[i][j][0],g[i][k][0])*2);
					if(f[i][j][0]&&g[i][j][0]&&f[i][k][0]&&g[i][k][1]) Ans=max(Ans,k-j+1+min(f[i][j][0],f[i][k][0])*2+min(g[i][j][0],g[i][k][1])*2);
					if(f[i][j][0]&&g[i][j][0]&&f[i][k][0]&&g[i][k][0]) Ans=max(Ans,k-j+1+min(f[i][j][0],f[i][k][0])*2+min(g[i][j][0],g[i][k][0])*2);
				}
			}
		}
	}
	cout<<Ans<<endl;
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

没意思题，完全不值 *2500。

---

首先考虑计算出一个点向上向下经过零或一个 ``m`` 能延伸的最大长度，此处直接 $O(n^3)$ 枚举，但是实现的好一点可以 $O(n^2)$。

然后考虑枚举这个“H”形的左边那个拐点，向右去递推，然后计算答案。

计算答案的时候直接分讨：

1. 假如已经有一个 ``m`` 了，显然四个都只能不选 ``m``。
2. 否则，枚举这个 ``m`` 在这个“H”形延伸出去的四个边中的那个。

[示例代码。](https://codeforces.com/contest/1771/submission/244539662)

---

