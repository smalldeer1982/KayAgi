# [ARC190C] Basic Grid Problem with Updates

## 题目描述

给定一个 $H \times W$ 的网格。从上往下第 $h$ 行、从左往右第 $w$ 列的单元格记为 $(h, w)$，其中存储了一个非负整数 $A_{h,w}$。  

高桥君初始位于单元格 $(sh, sw)$，接下来将进行 $Q$ 次修改操作。第 $i$ 次修改由字符 $d_i$（取值为 `L`、`R`、`U`、`D` 之一）和非负整数 $a_i$ 描述，具体操作如下：  
- 向 $d_i$ 方向移动 $1$ 格（`L` 为左，`R` 为右，`U` 为上，`D` 为下），将移动后的单元格 $(h, w)$ 中的 $A_{h,w}$ 修改为 $a_i$。  
（保证每次移动操作合法）  

每次修改后，请计算以下问题的答案：  
> 定义**路径** $P = ((h_1, w_1), \ldots, (h_M, w_M))$ 为满足以下条件的单元格序列：  
> - 起点 $(h_1, w_1) = (1, 1)$，终点 $(h_M, w_M) = (H, W)$，且 $M = H + W - 1$  
> - 对于任意 $1 \leq i \leq M-1$，满足 $(h_{i+1}, w_{i+1}) = (h_i + 1, w_i)$ 或 $(h_{i+1}, w_{i+1}) = (h_i, w_i + 1)$  
>  
> 所有可能的路径共有 $\binom{H + W - 2}{H - 1}$ 条。定义 $f(P) = \prod_{1 \leq i \leq M} A_{h_i, w_i}$，求所有路径 $P$ 的 $f(P)$ 之和模 $998244353$ 的结果。  

## 说明/提示

### 约束条件  
- $2 \leq H, W \leq 2 \times 10^5$  
- $H \cdot W \leq 2 \times 10^5$  
- $0 \leq A_{h,w} < 998244353$  
- $1 \leq Q \leq 2 \times 10^5$  
- $1 \leq sh \leq H$, $1 \leq sw \leq W$  
- $0 \leq a_i < 998244353$  
- 保证每次移动操作合法  

### 样例解释 1  
- 初始时高桥君位于 $(2, 2)$。  
- **第一次操作**（向上移动并修改 $A_{1,2}$ 为 $7$）：  
  - $P=((1,1),(1,2),(1,3),(2,3))$: $f(P) = 1 \times 7 \times 3 \times 6 = 126$  
  - $P=((1,1),(1,2),(2,2),(2,3))$: $f(P) = 1 \times 7 \times 5 \times 6 = 210$  
  - $P=((1,1),(2,1),(2,2),(2,3))$: $f(P) = 1 \times 4 \times 5 \times 6 = 120$  
- **第二次操作**（向右移动并修改 $A_{1,3}$ 为 $8$）：  
  - $P=((1,1),(1,2),(1,3),(2,3))$: $f(P) = 1 \times 7 \times 8 \times 6 = 336$  
  - 其他路径的 $f(P)$ 保持不变（$210$ 和 $120$）。  
- **第三次操作**（向左移动并修改 $A_{1,2}$ 为 $9$）：  
  - $P=((1,1),(1,2),(1,3),(2,3))$: $f(P) = 1 \times 9 \times 8 \times 6 = 432$  
  - $P=((1,1),(1,2),(2,2),(2,3))$: $f(P) = 1 \times 9 \times 5 \times 6 = 270$  
  - $P=((1,1),(2,1),(2,2),(2,3))$: $f(P) = 1 \times 4 \times 5 \times 6 = 120$   

翻译由 DeepSeek R1 完成  

## 样例 #1

### 输入

```
2 3
1 2 3
4 5 6
3 2 2
U 7
R 8
L 9```

### 输出

```
456
666
822```

## 样例 #2

### 输入

```
5 4
147015809 294958521 852121867 499798308
790350368 404692331 645419803 290531806
275766153 896286651 239187926 945049742
340760022 236352314 926236110 223464913
287023679 590772036 340282357 521075891
6 3 1
U 344644511
R 45812235
D 260083498
R 781118585
L 156297846
L 411901560```

### 输出

```
299123226
548055393
810247224
876210800
773990840
506814544```

# 题解

## 作者：KingPowers (赞：6)

这题哪有那么复杂啊，大家是不是都做繁了。

令 $n,m$ 分别为题面中的 $H,W$。

考虑暴力，设 $f_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 的所有路径的权值和（不带 $a_{i,j}$），容易得到 $f_{i,j}=a_{i-1,j}\times f_{i-1,j}+a_{i,j-1}\times f_{i,j-1}$，则开始的答案为 $f_{n,m}\times a_{n,m}$。

为了动态维护出答案，对称地定义 $g_{i,j}$ 表示从 $(i,j)$ 走到 $(n,m)$ 的所有路径的权值和（不带 $a_{i,j}$），同样容易得到 $g_{i,j}=a_{i+1,j}\times g_{i+1,j}+a_{i,j+1}\times g_{i,j+1}$。这样，我们可以算出去掉一个 $a_{i,j}$ 的增量是 $f_{i,j}\times g_{i,j}\times a_{i,j}$。

但是这还不够，改变一个 $a_{i,j}$ 后它左上方的 $f$ 和右下方的 $g$ 都会改变，暴力重新递推复杂度肯定是错的，因此我们没法再快速得出修改后加上 $a_{i,j}$ 的增量。

注意到题目修改的方式非常特殊，每次只会移动到相邻位置，尝试利用这一性质。由于我们走到 $(i,j)$ 时只需要关心 $f_{i,j}$ 和 $g_{i,j}$ 的值，每次都重构大片的矩阵显然很劣，尝试减少重构的规模，我们可以在每次修改 $a_{i,j}$ 之后只重新计算第 $i$ 行的 $f_{i,*}$ 和 $g_{i,*}$，这样至少能保证加上 $a_{i,j}$ 贡献时用到的 $f_{i,j},g_{i,j}$ 都是对的。下次我们移动到一个相邻位置的时候，在修改前再重新计算这个位置一整行的 $f$ 和 $g$，因为保证相邻所以当前一整行的 dp 值又肯定是对的。

注意到列数比较大的时候这样复杂度还是错的，但是因为 $nm\le 2\times 10^5$，我们可以在 $n$ 小的时候更新一整列，$m$ 小的时候更新一整行，所以最后复杂度是 $O(nm+q\sqrt{nm})$ 的，可以通过，代码无敌好写。


```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
int n, m, q, nowx, nowy, ans;
vector<int> a[N], f[N], g[N];
void upd1(int x, int y){
	if(x == 1 && y == 1) f[x][y] = 1;
	else f[x][y] = (a[x - 1][y] * f[x - 1][y] % mod + a[x][y - 1] * f[x][y - 1] % mod) % mod;
}
void upd2(int x, int y){
	if(x == n && y == m) g[x][y] = 1;
	else g[x][y] = (a[x + 1][y] * g[x + 1][y] % mod + a[x][y + 1] * g[x][y + 1] % mod) % mod;
}
void upd(int x, int y){
	if(n <= m){
		For(i, 1, n) upd1(i, y);
		Rof(i, n, 1) upd2(i, y);
	}
	else{
		For(i, 1, m) upd1(x, i);
		Rof(i, m, 1) upd2(x, i);
	}
}
void Solve(){
	cin >> n >> m;
	For(i, 0, n + 1) a[i].resize(m + 2), f[i].resize(m + 2), g[i].resize(m + 2);
	For(i, 1, n) For(j, 1, m) cin >> a[i][j];
	For(i, 1, n) For(j, 1, m) upd1(i, j);
	Rof(i, n, 1) Rof(j, m, 1) upd2(i, j);
	ans = a[n][m] * f[n][m] % mod;
	cin >> q >> nowx >> nowy;
	while(q--){
		char op; cin >> op;
		if(op == 'L') nowy--;
		if(op == 'R') nowy++;
		if(op == 'U') nowx--;
		if(op == 'D') nowx++;
		upd(nowx, nowy);
		ans = (ans + mod - a[nowx][nowy] * f[nowx][nowy] % mod * g[nowx][nowy] % mod) % mod;
		int val; cin >> val; a[nowx][nowy] = val;
		upd(nowx, nowy);
		ans = (ans + f[nowx][nowy] * a[nowx][nowy] % mod * g[nowx][nowy] % mod) % mod;
		cout << ans << '\n';
	}

}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int T = 1; //cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：ケロシ (赞：5)

先考虑只修改一次怎么做，考虑计算穿过这个点的贡献，设两个 dp，设 $f_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 的路径权值积和，其中权不计入 $a_{i,j}$，同理设 $g_{i,j}$ 为从 $(i,j)$ 到 $(h,w)$ 的路径权值积和，同样权不计入 $a_{i,j}$，转移：

$$
f_{i,j}=f_{i-1,j}a_{i-1,j}+f_{i,j-1}a_{i,j-1}
$$

$$
g_{i,j}=g_{i+1,j}a_{i+1,j}+g_{i,j+1}a_{i,j+1}
$$

那么穿过 $(i,j)$ 的路径贡献就是 $f_{i,j}g_{i,j}a_{i,j}$，每次减掉旧贡献加上新贡献即可。

若有多次修改，那么 dp 数组 $f$ 和 $g$ 的值就会改变，需要动态维护。

因为 $f$ 与 $g$ 是对称的，所以直接把 $f$ 单独拉出来考虑。

若修改点 $(x,y)$，那么 $(x,y)$ 到 $(h,w)$ 的矩形区域中的 $f$ 值会发生改变。

直接去更新这些值肯定是不行的，但是发现需要用到的 $f$ 只有 $q$ 个且是连续的，所以考虑动态更新需要的 $f$ 值。

考虑一个算法：设数组 $tag_{i,j}$，表示 $f_{i,j}$ 的值是否需要更新。显然修改点 $(x,y)$ 时需要将 $(x,y)$ 到 $(h,w)$ 的矩形区域中的 $tag$ 设为需要更新。考虑从 $(x,y)$ 开始往下往右递归，若递归到 $(i,j)$ 且 $tag_{i,j}$ 已经被设过了，那么 $(i,j)$ 到 $(h,w)$ 的 $tag$ 都被设过，那么就不用继续设了，若 $tag$ 不清空，那么时间复杂度均摊 $O(hw)$。

接下来考虑如何动态计算出 $f_{x,y}$，不难发现也可以递归求解（类似记忆化搜索），假设递归到 $(i,j)$，若 $tag_{i,j}$ 没被设过，那么 $(1,1)$ 到 $(i,j)$ 的 $tag$ 都没被设过，直接返回旧的 $f_{i,j}$ 即可，反之 $tag_{i,j}$ 被设过，那么就继续向上向左递归求得 $f_{i-1,j}$ 和 $f_{i,j-1}$，然后算出 $f_{i,j}$，然后把 $tag_{i,j}$ 清空。

这样就能动态维护出需要用到的 $f$ 的值了，但是这样复杂度并不正确。

画图或想象发现每次都在更新那些 $f$ 的值：

![](https://cdn.luogu.com.cn/upload/image_hosting/i20wvqah.png)

蓝色是询问点 $(x,y)$ 的移动路线，当在深蓝色部分移动的时候，需要更新绿色部分的 $f$ 的值，每次更新当前行中的一段，列的情况是同理的。

每次需要更新的行或列可能会很长，所以考虑经典套路：**根号重构**。

假设 $n$ 与 $hw$ 和 $q$ 同阶，设阈值 $B=\sqrt{n}$，每次若更新的行或列的长度超过了 $B$，那么就进行全局的重构。因为更新的长度肯定比操作序列要短，所以最多只有 $\frac{q}{B}$ 次重构。

所以时间复杂度 $O(n \sqrt{n})$。

```cpp
const int N = 2e5 + 5;
const int SN = sqrt(N);
const int P = 998244353;
inline int add(int x, int y) { return (x + y < P ? x + y : x + y - P); }
inline void Add(int & x, int y) { x = (x + y < P ? x + y : x + y - P); }
inline int sub(int x, int y) { return (x < y ? x - y + P : x - y); }
inline void Sub(int & x, int y) { x = (x < y ? x - y + P : x - y); }
inline int mul(int x, int y) { return (1ll * x * y) % P; }
inline void Mul(int & x, int y) { x = (1ll * x * y) % P; }
int n, m, q;
vector<vector<int>> a, f, g, tf, tg;
int cnt;
void rebuild_f() {
	FOR(i, 1, n) FOR(j, 1, m) if(i != 1 || j != 1)
		f[i][j] = add(mul(f[i - 1][j], a[i - 1][j]), mul(f[i][j - 1], a[i][j - 1]));
	FOR(i, 1, n) FOR(j, 1, m) tf[i][j] = 1;
}
void rebuild_g() {
	ROF(i, n, 1) ROF(j, m, 1) if(i != n || j != m)
		g[i][j] = add(mul(g[i + 1][j], a[i + 1][j]), mul(g[i][j + 1], a[i][j + 1]));
	FOR(i, 1, n) FOR(j, 1, m) tg[i][j] = 1;
}
void tag_f(int x, int y) {
	if(x > n || y > m || ! tf[x][y]) return;
	tf[x][y] = 0;
	tag_f(x + 1, y); tag_f(x, y + 1);
}
void tag_g(int x, int y) {
	if(x < 1 || y < 1 || ! tg[x][y]) return;
	tg[x][y] = 0;
	tag_g(x - 1, y); tag_g(x, y - 1);
}
void dp_f(int x, int y) {
	if(x < 1 || y < 1 || tf[x][y]) return;
	cnt ++;
	tf[x][y] = 1;
	if(x == 1 && y == 1) return;
	dp_f(x - 1, y); dp_f(x, y - 1);
	f[x][y] = add(mul(f[x - 1][y], a[x - 1][y]), mul(f[x][y - 1], a[x][y - 1]));
}
void dp_g(int x, int y) {
	if(x > n || y > m || tg[x][y]) return;
	cnt ++;
	tg[x][y] = 1;
	if(x == n && y == m) return;
	dp_g(x + 1, y); dp_g(x, y + 1);
	g[x][y] = add(mul(g[x + 1][y], a[x + 1][y]), mul(g[x][y + 1], a[x][y + 1]));
}
void solve() {
	cin >> n >> m;
	a = f = g = tf = tg = vector<vector<int>> (n + 2, vector<int> (m + 2));
	FOR(i, 1, n) FOR(j, 1, m) cin >> a[i][j];
	f[1][1] = g[n][m] = 1;
	rebuild_f(); rebuild_g();
	int ans = mul(f[n][m], a[n][m]);
	int x, y;
	cin >> q >> x >> y;
	REP(_, q) {
		char o; int w;
		cin >> o >> w;
		if(o == 'L') y --;
		if(o == 'R') y ++;
		if(o == 'U') x --;
		if(o == 'D') x ++;
		int cnt = 0;
		tag_f(x, y); dp_f(x, y);
		if(cnt > SN) rebuild_f();
		cnt = 0;
		tag_g(x, y); dp_g(x, y);
		if(cnt > SN) rebuild_g();
		Add(ans, mul(sub(w, a[x][y]), mul(f[x][y], g[x][y])));
		a[x][y] = w;
		cout << ans << endl;
	}
}
```

---

## 作者：良心WA题人 (赞：3)

## 题记

下方的代码里面有一车 $w+2$。

但是在赛时它们还是 $w+1$。

## 思路

这题比 D 过的少感觉纯粹就是榜歪了。

考虑如果没有修改怎么做。记 $f_{i,j}=(f_{i-1,j}+f_{i,j-1})\times a_{i,j}$ 即可。

接下来，考虑只进行一次修改。记录前缀的 $f_{i,j}$ 和后缀的 $g_{i,j}$，则位置 $(x,y)$ 的贡献为 $\dfrac{f_{i,j}\times g_{i,j}}{a_{i,j}}$，变化是可以 $O(1)$ 计算的。但是此时 $f$ 和 $g$ 的值会发生修改，所以无法扩展。

注意到我们的修改只会对相邻位置进行。而 $f$ 和 $g$ 也只对相邻的位置产生影响。若每次修改一行，则可以做到我们使用的位置的 $f$ 和 $g$ 的值是对的。这样还是没法做，但是修改一列一样可以做到这个效果，注意到 $h\times w\le 200000$，根号分治做完了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4,P=998244353,dx[5]={0,0,0,1,-1},dy[5]={0,1,-1,0,0};
vector<int>w1[NN],w2[NN],a[NN];
int h,w;
void upd1(int x,int y)
{
	if(x==1&&y==1)
		w1[x][y]=a[x][y];
	else
		w1[x][y]=1ll*(w1[x-1][y]+w1[x][y-1])%P*a[x][y]%P;
}
void upd2(int x,int y)
{
	if(x==h&&y==w)
		w2[x][y]=1;
	else
		w2[x][y]=(1ll*w2[x][y+1]*a[x][y+1]%P+1ll*w2[x+1][y]*a[x+1][y]%P)%P;
}
int main()
{
	scanf("%d%d",&h,&w);
	a[0].resize(w+2);
	w1[0].resize(w+2);
	w2[0].resize(w+2);
	for(int i=1;i<=h;i++)
	{
		a[i].resize(w+2);
		w1[i].resize(w+2);
		w2[i].resize(w+2);
		for(int j=1;j<=w;j++)
		{
			scanf("%d",&a[i][j]);
			upd1(i,j);
		}
	}
	a[h+1].resize(w+2);
	w1[h+1].resize(w+2);
	w2[h+1].resize(w+2);
	for(int i=h;i>=1;i--)
		for(int j=w;j>=1;j--)
			upd2(i,j);
	int q,x,y;
	scanf("%d%d%d",&q,&x,&y);
	int ans=w1[h][w];
	while(q--)
	{
		char op[3];
		scanf("%s",op);
		if(op[0]=='L')
			y--;
		if(op[0]=='R')
			y++;
		if(op[0]=='U')
			x--;
		if(op[0]=='D')
			x++;
		if(h<=w)
		{
			for(int X=1;X<=h;X++)
				upd1(X,y);
			for(int X=h;X>=1;X--)
				upd2(X,y);
		}
		else
		{
			for(int Y=1;Y<=w;Y++)
				upd1(x,Y);
			for(int Y=w;Y>=1;Y--)
				upd2(x,Y);
		}
		ans=(ans-1ll*w1[x][y]*w2[x][y]%P+P)%P;
		int na;
		scanf("%d",&na);
		a[x][y]=na;
		if(h<=w)
		{
			for(int X=1;X<=h;X++)
				upd1(X,y);
			for(int X=h;X>=1;X--)
				upd2(X,y);
		}
		else
		{
			for(int Y=1;Y<=w;Y++)
				upd1(x,Y);
			for(int Y=w;Y>=1;Y--)
				upd2(x,Y);
		}
		ans=(ans+1ll*w1[x][y]*w2[x][y]%P)%P;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Lavaloon (赞：2)

这里是不需要讨论 $H,W$ 大小关系的 NB 做法。

首先考虑去算单次询问的答案。

那肯定是直接 DP，设 $f_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 的所有路径 $P$ 所对应的 $f(P)$ 之和，转移方程想必大家都会。

这玩意甚至在 $H=1$ 下都是 $\mathcal{O}(HWQ)$ 的逆天复杂度，但是在 $H=1$ 时我们显然有更加优秀的做法：

将所有数乘起来，然后对于修改就除掉原数乘上新数就行了，复杂度是 $\mathcal{O}(HW+Q\log V)$，$V$ 是值域，非常优秀啊！

以另一种角度审视这个做法，其也可以被解释为：拿一段前缀、一段后缀去拼出来答案。尝试施之于 $H\neq1$ 的情况。

那我们就首先考虑定义出来前后缀到底是啥。

将 $f_{i,j}$ 视为前缀，自然定义后缀 $g_{i,j}$ 表示从 $(H,W)$ 走到 $(i,j)$ 的所有路径 $P$ 所对应的 $f(P)$ 之和。

拿这俩玩意拼答案的话，我们可以这么搞：

![](https://cdn.luogu.com.cn/upload/image_hosting/h3jfi2l9.png)

对于一条同色的斜线，任意一条路径不可能经过这条斜线两次。

于是我们用加法原理来统计答案，如下：
$$
\sum_{(i,j) \ 在斜线上}\dfrac{f_{i,j}g_{i,j}}{a_{i,j}}
$$
那我们肯定要选一条斜线去算这玩意。

题目每次询问会给我们一个点，这个点的坐标的变化是 $\mathcal{O}(1)$ 的，看起来性质不错。于是我们每次选择这个点所在的斜线来统计答案。

在预处理完 $f,g$ 后，不带修改、单纯计算答案的时间复杂度为 $\mathcal{O}(\min\{H,W\})$，这是不高于 $\mathcal{O}(\sqrt{HW})$ 的。

那接下来就要考虑如何处理修改。

我们肯定不去全部更新 $f,g$，我们只考虑回答询问所需要的信息，也就是这条斜线上的 $f,g$ 值，我们尝试维护之。

由于这个点坐标的变化的优秀性质，这条斜线一定是上移一格或下移一格。

总之一次询问一定形如：”要求你上移或下移一格并在这条斜线上修改一个位置的值“的形式。

那么在斜线发生移动的时候，我们用原来的转移方程去更新这条斜线上所有点的 $f,g$ 的值，这样是否正确？

正确性的证明如下：

读者可以感觉到，**实际上就是在维护斜线及其上方的 $f$ 值始终正确斜线及其下方的 $g$ 值始终正确**。这样在斜线发生移动的时候总能用正确的值去更新在斜线上的 $f,g$ 的值，从而正确地统计答案。

时间复杂度方面，更新对应 $f,g$ 的值的时间复杂度仍不高于 $\mathcal{O}(\sqrt{HW})$。

这就是这个做法的大致流程，还有一些不重要的比如求逆元之类的不再赘述。

综上，时间复杂度为 $\mathcal{O}(HW\log V+Q\log V+Q\sqrt{HW})$，常数也相对优秀，甚至可以在 $1$ 秒内通过此题。

代码如下：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<array>
#include<unordered_map>
#include<vector>
#include<bitset>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<random>
#include<numeric>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define lc (x<<1)
#define rc (x<<1|1)
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
#define cout (cerr<<">> ",cout)
const int Mx=500005,p=998244353;
int read(){
	char ch=getchar();
	int Alice=0,Aya=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') Aya=-Aya;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		Alice=(Alice<<3)+(Alice<<1)+(ch^48),ch=getchar();
	return (Aya==1?Alice:-Alice);
}
int n,m;
int q;
int h,l;
int Inv(int bas){
	int ex=p-2,res=1;
	while(ex){
		if(ex&1) res=res*bas%p;
		bas=bas*bas%p,ex>>=1;
	}
	return res;
}
vector<int>a[Mx],inv[Mx],f[Mx],g[Mx];
vector<pii>slash[Mx];
signed main(){
	n=read(),m=read();
	for(int i=0;i<=n+1;i++){
		a[i].resize(m+2),f[i]=g[i]=inv[i]=a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) a[i][j]=read(),inv[i][j]=Inv(a[i][j]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i==1&&j==1) f[i][j]=a[i][j];
			else f[i][j]=(f[i-1][j]+f[i][j-1])*a[i][j]%p;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(i==n&&j==m) g[i][j]=a[i][j];
			else g[i][j]=(g[i+1][j]+g[i][j+1])*a[i][j]%p;
		}
	}
	q=read(),h=read(),l=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			slash[i+j].push_back({i,j});
		}
	}
	char op[2];
	for(int Id=1,v;Id<=q;Id++){
		scanf("%s",op);
		v=read();
		if(op[0]=='U') h--;
		else if(op[0]=='D') h++;
		else if(op[0]=='L') l--;
		else l++;
		a[h][l]=v;
		inv[h][l]=Inv(v);
		for(pii _:slash[h+l]){
			int i=_.fi,j=_.se;
			if(i==1&&j==1) f[i][j]=a[i][j];
			else f[i][j]=(f[i-1][j]+f[i][j-1])*a[i][j]%p;
			if(i==n&&j==m) g[i][j]=a[i][j];
			else g[i][j]=(g[i+1][j]+g[i][j+1])*a[i][j]%p;
		}
		int ans=0;
		for(pii _:slash[h+l]){
			int i=_.fi,j=_.se;
			(ans+=f[i][j]*g[i][j]%p*inv[i][j]%p)%=p;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：wsinb (赞：2)

写篇题解，来给 THUWC 攒功德了。

这篇题解给出的做法不需要考虑 $h$ 和 $w$ 之间的大小关系，而且跑得还挺快的。

---

考虑修改一个点的权值之后整个网格图权值的变化量是什么。

显然，点权修改只会对经过这个点的路径的权值产生影响。

如果我们记 $f_{i,j}$ 表示**所有从 $(1,1)$ 走到 $(i,j)$ 的路径权值之和**，$g_{i,j}$ 表示**所有从 $(i,j)$ 走到 $(h,w)$ 的路径权值之和**，则有：

$$f_{i,j}=(f_{i-1,j}+f_{i,j-1})\times a_{i,j}$$

$$g_{i,j}=(g_{i+1,j}+g_{i,j+1})\times a_{i,j}$$

注意特判 $f_{1,1}=a_{1,1}$，$g_{h,w}=a_{h,w}$。以上两个式子本质上是 DP。

且经过点 $(x,y)$ 的所有路径的权值之和可以被表示为：

$$(f_{x-1,y}+f_{x,y-1})\times a_{x,y}\times(g_{x+1,y}+g_{x,y+1})$$

这个式子的意义是，由于一条路径可以从上方 / 左方进入点 $(x,y)$，又可以从下方 / 右方离开点 $(x,y)$，使用乘法原理计算即可。

如果我们以 $(1,1)$ 为左上角，$(n,m)$ 为右下角画出网格图 $a$，那么，在修改点 $(x,y)$ 的权值之后，所有位于 $(x,y)$ 右下方的 $f$ 值也会被修改；同理，所有位于 $(x,y)$ 左上方的 $g$ 值也会被修改。我们得到的信息只有**这些位置的 $f$ 或 $g$ 值需要被修改，至于具体修改为何值，我们目前是不知道的**。

对此，我们可以采取如下方法：新建布尔数组 $bf$、$bg$ 分别记录网格图中每一个位置的 $f$、$g$ 值是否被修改。

进一步，我们会发现题目中给的限制会带来一个非常好的性质：每次修改的位置是相邻的，这意味着每次修改之后 $bf$ 与 $bg$ 的改动不会很大。

具体地，由于每次修改的位置相邻，于是操作后 $bf$、$bg$ 中只有一个会被改动，而且它只会有一行或一列会被新赋值为 $1$。

至于究竟是 $bf$ 还是 $bg$ 会有修改，以及究竟修改一行还是一列，这个只与询问中所给出的 `UDLR` 有关，读者可以自己尝试画一画、推导结论，因为一一讲述实在很麻烦。

那么到现在，我们只剩下两个问题了。

> 在处理新的询问时，如果我们需要知道某个点的 $f$、$g$ 值，而此处的 $f$、$g$ 值恰好由于之前 $a$ 数组被修改而修改了，应该如何处理？

使用记忆化搜索解决。以 $f$ 为例，查询 $f_{x,y}$ 时，如果 $bf_{x,y}=0$，那么可以直接调用 $f_{x,y}$；否则，先递归查询 $f_{x-1,y}$、$f_{x,y-1}$，再用新的 $f_{x-1,y}$、$f_{x,y-1}$ 来更新 $f_{x,y}$，最后再将 $bf_{x,y}$ 设置为 $0$。$g$ 同理。注意特判 $f_{1,1}$ 与 $g_{h,w}$ 的处理。

> 看上去这么暴力的算法，其时间复杂度真的可以接受吗？

在上文的基础上，再加一点点剪枝就可以了。

首先注意到很重要的一点：记忆化搜索的总时间复杂度不会大于修改 $bf$、$bg$ 的总时间复杂度。这是因为记忆化搜索的时候只会访问 $bf$、$bg$ 为 $1$ 的位置，并且随即将其清零。

所以不妨计算一下我们对 $bf$、$bg$ 的总修改次数。到目前为止，每次对 $a$ 的修改会带来在 $bf$、$bg$ 上的一整行 / 列的修改，单次复杂度可以达到 $O(\max(h,w))$，总复杂度可以达到 $O(q\max(h,w))$，不可接受。

考虑剪枝，在修改 $bf$、$bg$ 时，如果发现某位置 $bf$、$bg$ 已经为 $1$ 之后，立即结束修改并处理下一个询问。这让询问的单次均摊复杂度变为 $O(\frac{hw}{h+w})=O(\min(h,w))\le O(\sqrt{hw})$。

于是我们以一个比较水到渠成的思路解决了这道难度评分 $3010$ 的题目。

只可惜因为 $f_{1,1}$、$g_{h,w}$ 等边界错误调试时间过长，我没有在赛时做出此题。

代码主要在赛时完成，仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>

const int N=2e5+10,mod=998244353;

int n,m,Q,x,y,ans;

int dx[200],dy[200];

vector<int> a[N],f[N],g[N];
vector<bool> bf[N],bg[N];

void upf(int i,int j){
	if(i==1&&j==1) f[i][j]=a[i][j];
	else f[i][j]=(f[i-1][j]+f[i][j-1])*a[i][j]%mod;
}

void upg(int i,int j){
	if(i==n&&j==m) g[i][j]=a[i][j];
	else g[i][j]=(g[i+1][j]+g[i][j+1])*a[i][j]%mod;
}

int fet(int i,int j){
	if(i==1&&j==1) return bf[i][j]=0,a[i][j];
	if(!bf[i][j]) return f[i][j];
	bf[i][j]=0;
	return f[i][j]=(fet(i-1,j)+fet(i,j-1))*a[i][j]%mod;
}

int get(int i,int j){
	if(i==n&&j==m) return bg[i][j]=0,a[i][j];
	if(!bg[i][j]) return g[i][j];
	bg[i][j]=0;
	return g[i][j]=(get(i+1,j)+get(i,j+1))*a[i][j]%mod;
}

signed main(){
	ios::sync_with_stdio(false);
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	cin>>n>>m;
	dx['U']=-1;
	dx['D']=1;
	dy['L']=-1;
	dy['R']=1;
	
	
	for(int i=0;i<=n+1;++i) a[i].resize(m+10),bf[i].resize(m+10),bg[i].resize(m+10),f[i].resize(m+10),g[i].resize(m+10);
	
	
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>a[i][j];
			upf(i,j);
		}
	}
	
	for(int i=n;i;--i){
		for(int j=m;j;--j){
			upg(i,j);
		}
	}
	
	ans=g[1][1];
	
	int x,y,v,op;
	char ch;
	cin>>Q>>x>>y;
	
	for(int i=1;i<=x;++i){
		for(int j=1;j<=y;++j){
			bg[i][j]=1;
		}
	}
	
	for(int i=x;i<=n;++i){
		for(int j=y;j<=m;++j){
			bf[i][j]=1;
		}
	}
	
	while(Q--){
		cin>>ch>>v;
		op=(int)ch;
		bf[x][y]=bg[x][y]=1;
		x+=dx[op],y+=dy[op];
		int sf=fet(x-1,y)+fet(x,y-1),sg=get(x+1,y)+get(x,y+1);
		if(x==1&&y==1) sf=1;
		if(x==n&&y==m) sg=1;
		
		ans=(ans+sf*sg%mod*(v-a[x][y])%mod+mod)%mod;
		a[x][y]=v;
		fet(x,y),get(x,y);
		
		
		cout<<ans<<'\n';
		
		if(dx[op]<0||dy[op]<0){
			for(int i=x,j=y;i<=n&&j<=m;i-=dy[op],j-=dx[op]){
				if(bf[i][j]) break;
				bf[i][j]=1;
			}
		}
		
		if(dx[op]>0||dy[op]>0){
			for(int i=x,j=y;i&&j;i-=dy[op],j-=dx[op]){
				if(bg[i][j]) break;
				bg[i][j]=1;
			}
		}
	}
	
	
	return 0;
}

```

---

## 作者：cike_bilibili (赞：0)

神秘做法，非正解。

我们发现这道题的修改非常有意思，并不是我们熟知的离散的单点修改，而是保证修改点与上一个修改点相邻，考虑从这个东西入手。

最开始想的是在修改点移动的同时，动态维护二维前缀积和后缀积，也就是边移动，边更新当前修改点的前后缀积，然后就发现这个东西是假的，因为在移动的过程中周围的信息可能错误。

延续这个思路，我们考虑操作分块，我们在每一个块先暴力重构前后缀积，然后再考虑单点如何维护，我们发现实际上修改点能影响的只有由当前块中 $x$ 坐标极大极小和 $y$ 坐标极大极小组成的矩形，我们只需要更新这一部分的数组就行了，然后维护答案变化量。

然后我们就发现这个时间复杂度假了，设块长为 $B$，$nm$ 与 $Q$ 同阶，则重构的时间复杂度为 $O(\frac{(nm)^2}{B})$，单点改的时间复杂度为 $O((nm)B^2)$，但是我们的 $B$ 没必要取 $\sqrt{nm}$ 啊，我们只需要取 $B=(nm)^{\frac{1}{3}}$，就能取到最优复杂度 $O((nm)^{\frac{5}{3}})$。

建议取 $B=90$，最大点 4216ms。


```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int ans=0,w=1;
    char ch=getchar();
    while(ch<48||ch>57){
       if(ch=='-')w=-1;
       ch=getchar();
    }
    while(ch>=48&&ch<=57){
       ans=(ans<<1)+(ans<<3)+ch-48;
       ch=getchar();
    }
    return w*ans;
}
const int mod=998244353;
ll Pow(ll x,ll y){
    ll ans=1,push=x;
    while(y){
        if(y&1)ans=ans*push%mod;
        push=push*push%mod;
        y>>=1;
    }
    return ans;
}
int n,m,Q;
vector<int>a[200005],pre[200005],suf[200005];
char ch[200005][5];
int val[200005];
int st[200005],ed[200005],id[200005],cnt;
const int B=90;
void build(){
    for(int i=1;i<=Q;i+=B){
        st[++cnt]=i,ed[cnt]=min(i+B-1,Q);
        for(int j=i;j<=ed[cnt];j++)id[j]=cnt;
    }
}
int x,y;
signed main(){
    n=read(),m=read();
    for(int i=0;i<=n+1;i++)a[i].resize(m+5),pre[i].resize(m+5),suf[i].resize(m+5);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)a[i][j]=read();
    }
    pre[0][1]=1,suf[n][m+1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            
            pre[i][j]=1ll*(pre[i-1][j]+pre[i][j-1])*a[i][j]%mod;
        }
    }
    for(int i=n;i;i--){
        for(int j=m;j;j--){
            suf[i][j]=1ll*(suf[i+1][j]+suf[i][j+1])*a[i][j]%mod;
        }
    }
    ll ans=pre[n][m];
    Q=read(),x=read(),y=read();
    
    for(int i=1;i<=Q;i++)scanf("%s",ch[i]+1),val[i]=read();
    build();
    for(int b=1;b<=cnt;b++){
        pre[0][1]=1,suf[n][m+1]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                pre[i][j]=1ll*(pre[i-1][j]+pre[i][j-1])*a[i][j]%mod;
            }
        }
        for(int i=n;i;i--){
            for(int j=m;j;j--){
                suf[i][j]=1ll*(suf[i+1][j]+suf[i][j+1])*a[i][j]%mod;
            }
        }
        int nx=x,ny=y;
        int lx=1e9,rx=0,ly=1e9,ry=0;
        for(int j=st[b];j<=ed[b];j++){
            if(ch[j][1]=='U')--nx;
            if(ch[j][1]=='D')++nx;
            if(ch[j][1]=='L')--ny;
            if(ch[j][1]=='R')++ny;
            lx=min(lx,nx),rx=max(rx,nx);
            ly=min(ly,ny),ry=max(ry,ny);
        }
        for(int j=st[b];j<=ed[b];j++){
            if(ch[j][1]=='U')--x;
            if(ch[j][1]=='D')++x;
            if(ch[j][1]=='L')--y;
            if(ch[j][1]=='R')++y;
            ans=(ans-1ll*suf[x][y]*pre[x][y]%mod*Pow(a[x][y],mod-2)%mod);
            if(ans<0)ans+=mod;
            a[x][y]=val[j];
            for(int p=x;p<=rx;p++){
                for(int q=y;q<=ry;q++){
                    pre[p][q]=1ll*(pre[p-1][q]+pre[p][q-1])*a[p][q]%mod;
                }
            }
            
            for(int p=x;p>=lx;p--){
                for(int q=y;q>=ly;q--){
                    suf[p][q]=1ll*(suf[p+1][q]+suf[p][q+1])*a[p][q]%mod;
                }
            }
            ans=(ans+1ll*suf[x][y]*pre[x][y]%mod*Pow(a[x][y],mod-2))%mod;
            cout<<ans<<'\n';
        }
    }
    return 0;
}
/*
n,m<=200000
*/
```

---

## 作者：鲤鱼江 (赞：0)

为方便起见，用 $n,m$ 代替 $W,H$。

先考虑没有修改怎么做，使用 $f_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 的路径权值之和（不包括 $a_{i,j}$），那么转移有：$f_{i,j}\leftarrow a_{i,j-1}\times f_{i,j-1}+a_{i-1,j}\times f_{i-1,j}$，答案是 $a_{n,m}f_{n,m}$。

那么有修改呢？考虑计算一个元素对答案的贡献，使用 $g_{i,j}$ 表示 $(i,j)$ 到 $(n,m)$ 的路径权值之和（不包括 $a_{i,j}$），那么同样有转移：$g_{i,j}\leftarrow a_{i+1,j}\times g_{i+1,j}+a_{i,j+1}\times g_{i,j+1}$。

那么去掉一个 $a_{i,j}$ 之后答案的的变化量为 $f_{i,j}\times g_{i,j}\times a_{i,j}$。

但是这样还不够，因为如果修改了 $a_{i,j}$，会导致其他地方的 $f,g$ 值改变，暴力修改是 $O((nm)^2)$，但是发现修改的方式非常不对劲，仔细思考之后发现如果每次只移动一格，那么这次询问的点一定是上次询问的点的周围，所以每次暴力更新到达的点的对应行或列，如果 $n$ 小就修改列，否则修改行。

时间复杂度 $O(nm\sqrt{nm})$。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+10;
const int mod=998244353;
struct modint {
    int val;
    static int norm(const int& x) { return x < 0 ? x + mod : x; }
    modint inv() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) t = a / b, swap(a -= t * b, b), swap(u -= t * v, v);
        return modint(u);
    }
    modint() : val(0) {}
    modint(const int& m) : val(norm(m)) {}
    modint(const long long& m) : val(norm(m % mod)) {}
    modint operator-() const { return modint(norm(-val)); }
    modint& operator+=(const modint& o) { return val = (1ll * val + o.val) % mod, *this; }
    modint& operator-=(const modint& o) { return val = norm(1ll * val - o.val), *this; }
    modint& operator*=(const modint& o) { return val = static_cast<int>(1ll * val * o.val % mod), *this; }
    modint operator-(const modint& o) const { return modint(*this) -= o; }
    modint operator+(const modint& o) const { return modint(*this) += o; }
    modint operator*(const modint& o) const { return modint(*this) *= o; }
	friend std::ostream& operator<<(std::ostream& os, const modint a) { return os << a.val; }
}res;
int n,m,x,y,q;
vector < int > a[N];
vector < modint > f[N],g[N];
char in;

inline void Calc1(int i,int j){
	f[i][j]=f[i-1][j]*a[i-1][j]+f[i][j-1]*a[i][j-1];
	if(i==1&&j==1) f[1][1]=1;
}
inline void Calc2(int i,int j){
	g[i][j]=g[i+1][j]*a[i+1][j]+g[i][j+1]*a[i][j+1];
	if(i==n&&j==m) g[n][m]=1;
} 
inline void DP(int x,int y){
	if(n>m){
		for(int j=1;j<=m;++j) Calc1(x,j),Calc2(x,m-j+1);
	}else {
		for(int i=1;i<=n;++i) Calc1(i,y),Calc2(n-i+1,y);
	}
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n>>m;
	for(int i=0;i<=n+2;++i){a[i].resize(m+5);f[i].resize(m+5);g[i].resize(m+5);}
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) cin>>a[i][j];
	cin>>q>>x>>y;for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) Calc1(i,j);
	for(int i=n;i;--i) for(int j=m;j;--j) Calc2(i,j);
	res=f[n][m]*a[n][m];
	for(int i=1,v;i<=q;++i){
		cin>>in>>v;
		if(in=='L') --y;
		if(in=='R') ++y;
		if(in=='U') --x;
		if(in=='D') ++x;
		swap(a[x][y],v);DP(x,y);
		res+=f[x][y]*(a[x][y]-v)*g[x][y];
		cout<<res<<'\n';
	}
	return 0;
}
```

---

