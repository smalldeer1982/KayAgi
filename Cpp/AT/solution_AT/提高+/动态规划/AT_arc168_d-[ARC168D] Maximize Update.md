# [ARC168D] Maximize Update

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc168/tasks/arc168_d

$ N $ 個のマスが横一列に並んでおり，左から順に $ 1 $ から $ N $ の番号がついています． 最初，すべてのマスは白色です．

あなたは以下の $ M $ 種類の操作を**好きな順序で好きな回数**行うことができます．

- $ i $ 種類目の操作: マス $ L_i $ からマス $ R_i $ までを黒色で塗る．
 
マス目の状態を変化させるような操作の回数の最大値を求めてください． なお，操作を行った結果色が変化したマスが $ 1 $ つでもあれば，その操作はマス目の状態を変化させたとみなします．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ M\ \leq\ N(N+1)/2 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ (L_i,R_i)\ \neq\ (L_j,R_j) $ ($ i\ \neq\ j $)
- 入力される値はすべて整数．
 
### Sample Explanation 1

以下のように操作すると，マス目の状態を変化させる操作が $ 3 $ 回行われます． - $ 2 $ 種類目の操作を行う．新たにマス $ 1 $ が黒色で塗られる． - $ 3 $ 種類目の操作を行う．新たにマス $ 3 $ が黒色で塗られる． - $ 1 $ 種類目の操作を行う．新たにマス $ 2 $ が黒色で塗られる．

## 样例 #1

### 输入

```
3 3
1 3
1 1
3 3```

### 输出

```
3```

## 样例 #2

### 输入

```
4 3
1 2
3 4
1 4```

### 输出

```
2```

## 样例 #3

### 输入

```
5 5
4 5
1 1
2 4
1 2
2 5```

### 输出

```
4```

## 样例 #4

### 输入

```
20 15
2 4
16 19
7 13
1 15
3 18
10 11
1 10
1 7
14 16
1 16
2 17
1 17
12 14
3 17
4 10```

### 输出

```
11```

# 题解

## 作者：OldDriverTree (赞：5)

# Solution

看到数据范围 $1\le N\le 500$，多半就是区间 DP 了。

设 $f_{l,r}$ 表示考虑只用 $l\le L\le R\le r$ 的操作，最多能操作多少次。

再预处理 $g_{l,r,i}$ 表示能否用 $l\le L\le R\le r$ 的操作对方格 $i$ 涂色，输入 $m$ 次操作时先把区间内的 $g_{L,R,i}$ 设为 $\texttt{true}$，输入完再枚举区间，$g_{l,r,i}=g_{l+1,r,i}\vee g_{l,r-1,i}$ 即可。

枚举最后涂色的方格，$f_{l,r}=\max\limits_{i=l}^r f_{l,i-1}+f_{i+1,r}+g_{l,r,i}$。

时间复杂度为 $O(N^3+nm)$。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=502;
bool g[N][N][N];
int n,m,f[N][N];

int main()
{
	scanf("%d%d",&n,&m);
	while (m--) {
		int l,r;
		scanf("%d%d",&l,&r);
		for (int i=l;i<=r;i++)
		g[l][r][i]=true;
	}
	for (int len=2;len<=n;len++)
		for (int l=1,r=len;r<=n;l++,r++)
			for (int i=l;i<=r;i++) {
				g[l][r][i]|=g[l+1][r][i];
				g[l][r][i]|=g[l][r-1][i];
			}
	for (int len=1;len<=n;len++)
		for (int l=1,r=len;r<=n;l++,r++)
			for (int i=l;i<=r;i++)
				f[l][r]=max(f[l][r],f[l][i-1]+f[i+1][r]+g[l][r][i]);
	
	printf("%d",f[1][n]);
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：4)

[12. [ARC168D] Maximize Update](https://www.luogu.com.cn/problem/AT_arc168_d)

可能区间 DP 在国外是高科技吧。

考虑到这个操作是在区间涂颜色，再观察一下 $n\le 500$，再观察一下发现操作数量很少，于是考虑区间 DP（喜）。这类顺序影响性的问题显然都是可以区间 DP 解决的。

设 $f[l][r]$ 为区间 $[l,r]$ 已经被涂完颜色的最多操作次数，尝试转移。

显然可以枚举两个子区间转移；但是还不够，我们发现还要枚举一个中间空位，选择某个能够跨过中间空位的区间。显然，后者可以通过前缀和优化。

于是这个题就做完了，比第三题要简单好多。唉，这种题还是要看一眼的。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I N=505;
I n,m,l,r,c[N][N],f[N][N];
#define y1 SMT0x400
I ss(I x1,I y1,I x2,I y2){--x1;--y1;
	return c[x2][y2]+c[x1][y1]-c[x2][y1]-c[x1][y2]>0;}
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	while(m--)cin>>l>>r,++c[l][r];
	fo(i,1,n)fo(j,1,n)c[i][j]+=c[i][j-1];
	fo(i,1,n)fo(j,1,n)c[i][j]+=c[i-1][j];
	fo(len,1,n)for(I l=1,r=len;r<=n;++l,++r){I&nw=f[l][r];
		fo(k,l,r-1)nw=max(nw,f[l][k]+f[k+1][r]);
		fo(k,l,r)nw=max(nw,f[l][k-1]+f[k+1][r]+ss(l,k,k,r));}
	printf("%d\n",f[1][n]);
	return 0;}
```



---

## 作者：WaterSky (赞：2)

## [[ARC168D] Maximize Update ](https://www.luogu.com.cn/problem/AT_arc168_d)

区间 $\text{DP}$。

设状态：$f_{i,j}$ 表示只用满足 $i \le l < r \le j$ 的操作的最大次数。

预处理 $g_{l,r,i}$ 表示能否通过满足 $i \le l < r \le j$ 的操作覆盖第 $i$ 个点。

再 $\text{DP}$，状态转移为：
$$f_{l,r}=\max_{i=l}^{r} f_{l,i-1}+f_{i+1,r}+g_{l,r,i}$$
有点抽象，再加以解释：其实就是在一段区间中找到一个断点（也就是进行操作时必要的白点） $i$ 将此节点分割为两部分，然后递推左右两个部分，只考虑 $i$，要加上是否有操作能够包含这个区间。

最终的 $f_{1,n}$ 即为正解。

接下来是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long l,r;
long long g[505][505][505],f[1005][1005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>l>>r;
		for(int i=l;i<=r;i++)
			g[l][r][i]=1;//在操作区间内的肯定满足
	}
	for(int len=2;len<=n;len++)
		for(int l=1,r=len;r<=n;l++,r++)
			for(int i=l;i<=r;i++)
				g[l][r][i]|=g[l+1][r][i]|g[l][r-1][i];
	for(int len=1;len<=n;len++)
		for(int l=1,r=len;r<=n;l++,r++)
			for(int i=l;i<=r;i++)
				f[l][r]=max(f[l][r],f[l][i-1]+f[i+1][r]+g[l][r][i]);//DP
	cout<<f[1][n];
	return 0;
} 
```

---

## 作者：roger_yrj (赞：2)

## 题解

区间 DP+前缀和优化。

设 $f_{i,j}$ 为只把 $[i,j]$ 全部涂黑，其他全为白的最多操作次数。

对于一个区间 $[i,j]$：

- 分成两半。$f_{i,j}=\max\limits_{k=i}^{r-1}f_{i,k}+f_{k+1,r}$。
- 枚举区间内的最后覆盖的白格子。$f_{i,j}=\max\limits_{k=i}^rf_{i,k-1}+f_{k+1,r}+$ 区间内是否有覆盖该格子。

用前缀和处理”区间内是否有覆盖该格子“。

时间复杂度 $O(n^3)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=510;
int n,m,sum[N][N],f[N][N];
int main(){
	cin>>n>>m;
	for(int i=1,l,r;i<=m;i++){
		scanf("%d%d",&l,&r);
		sum[l][r]++; 
	} 
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)sum[i][j]+=sum[i-1][j];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)sum[i][j]+=sum[i][j-1];
	for(int len=1;len<=n;len++)
		for(int i=1,j=i+len-1;j<=n;i++,j++){
			for(int k=i;k<j;k++)f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]);
			for(int k=i;k<=j;k++)f[i][j]=max(f[i][j],f[i][k-1]+f[k+1][j]+bool(sum[k][j]-sum[k][k-1]-sum[i-1][j]+sum[i-1][k-1]));
		}
	cout<<f[1][n];
}
```

---

## 作者：littlebug (赞：1)

这有蓝？这有蓝？这有蓝？这有蓝？这有蓝？这有蓝？这有蓝？这有蓝？这有蓝？这有蓝？这有蓝？这有蓝？

## Solution

显然是区间 dp。

设 $f_{l,r}$ 为涂黑区间 $[l,r]$ 的最大操作次数。

首先显然可以切成两半转移。然后第二种情况，考虑**只有** $[l,r]$ 这段区间能产生的贡献，可以枚举一个断点 $i$，然后 $i$ 左右两边分别单独做，对于 $i$ 看看有没有 $\subseteq [l,r]$ 且包含 $i$ 的区间，如果有则操作次数 $+1$ 即可。

至于有没有 $\subseteq [l,r]$ 且包含 $i$ 的区间，可以看成是左端点为 $[l,i]$，右端点 $\le r$ 的区间，于是可以想到统计对于每个 $l,i$，其能到达的 $r$ 的最小值，显然这个也可以直接 dp 出来。设 $g_{l,i}$ 为左端点为 $[l,i]$ 中的一个，区间包含 $i$ 所能达到的 $r$ 的最小值，类似于一个后缀最小值转移即可。

时间复杂度 $O(n^2 \log m) - O(n^3)$，精细实现好像可以把 $\log m$ 去掉，不过没什么必要。

## Code

```cpp
int n,m,f[N][N],g[N][N];
vector <int> a[N];

signed main()
{
	read(n,m); {int l,r; rep(i,1,m) read(l,r),a[l].pb(r);}
	rep(i,1,n) sort(all(a[i])),a[i].pb(inf);
	
	memset(g,0x3f,sizeof(g));
	rep(i,1,n) rpe(l,i,1) g[i][l]=min(g[i][l+1],*lower_bound(all(a[l]),i));
	
	rep(len,1,n) rep(l,1,n-len+1)
	{
		int r=l+len-1;
		f[l][r]=0;
		rep(i,l,r-1) chmax(f[l][r],f[l][i]+f[i+1][r]);
		rep(i,l,r) chmax(f[l][r],f[l][i-1]+f[i+1][r]+(g[i][l]<=r));
	}
	
	write(f[1][n]);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：qhr2023 (赞：1)

## soltion

典型的区间动态规划，那么我们设 $f_{i, j}$ 为 $i$ 到 $j$ 区间的最大操作次数。

套路的想，对于当前区间，我们分成两个子区间，通过两个子区间的答案以及跨过两区间的答案推出大区间的答案。对于本题，设 $g_{i, j, k}$ 表示 $i$ 到 $j$ 区间是否有一种方案可以覆盖 $k$，枚举 $k$，答案即 $\max(f_{i, j}, f_{i, k-1}+f_{k+1, j}+g_{i, j, k})$ 的最大值。

现在问题转化成如何处理 $g$，我们考虑，如果 $g_{i, j, k}$ 为 $1$，则 $g_{i+1, j, k}$ 和 $g_{i, j-1, k}$ 都为 $1$，那我们逆过来，这两个区间只要有一个为 $1$ 那 $g_{i, j, k}$ 就为 $1$，由此得到了 $g$ 数组的转移，这也是个区间 dp，对于初始化，在 $g$ 输入时处理即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, g[505][505][505], f[505][505], l, r;
int main () {
	cin >> n >> m;
	while (m--&&cin >> l >> r)
		for (int j=l; j<=r; ++j)
			g[l][r][j]=1;
	for (int len=1; len<=n; ++len)
		for (int i=1, j=i+len-1; i+len-1<=n; ++i, ++j)
			for (int k=i; k<=j; ++k)
				g[i][j][k]|=(g[i+1][j][k]|g[i][j-1][k]);
	for (int len=1; len<=n; ++len)
		for (int i=1, j=i+len-1; i+len-1<=n; ++i, ++j)
			for (int k=i; k<=j; ++k)
				f[i][j]=max(f[i][j], f[i][k-1]+f[k+1][j]+g[i][j][k]);
	cout << f[1][n];
	return 0;
}
```

---

## 作者：tony0530 (赞：1)

一看范围, $1 \le N \le 500$ , 我们就可以优先考虑区间DP。

设 $f_{i, j}$ 表示为只把 $[i,j]$ 全部涂黑，其他全部为白色的能操作的最大次数。

对于区间 $[i,j]$ 我们发现 $f_{i,j} = \mathop{\max}\limits_{k=i}^{j}f_{i, k -1} + f_{k + 1, r} + $ 区间内是否有覆盖该格子。

我们只需要再预处理 "区间内是否有覆盖该格子" 就好了。

讲得比较清楚,就不给予代码了。

---

## 作者：Ascnbeta (赞：0)

## ARC168D

很好一道区间 dp 练手题。由于题面很裸，这里不分析题意。

### 思路分析

容易发现，每一次操作都是修改的区间，并且修改后会将原方格分割为多个方格区间，而题面又要我们求最值，联系 $N \le 500$ 的数据范围，考虑使用区间 dp。

于是我们设 $f_{i,j}$ 为区间 $[i,j]$ 的最大可操作次数，联系区间 dp 很容易得到状态转移方程。不过要注意的是，由于题目要求每次操作必须保证操作区间内至少有一个白色方格，因此枚举断点 $k$ 时要注意 $f_{i,j}$ 应当从 $f_{i,k-1}+f_{k+1,j}+g_{i,j,k}$ 转移而来（设 $g_{i,j,k}$ 为是否有一个操作区间满足包含于 $[l,r]$ 且覆盖点 $k$），所以状态转移方程为：
$$
f_{i,j} \gets \max(f_{i,j},f_{i,k-1}+f_{k+1,j}+g_{i,j,k})
$$
现在问题转化为如何求 $g_{i,j,k}$，注意到 $g$ 实际上也是对于区间的一个判断，运用顺推的思想，如果 $g_{i,j,k} = 1$，那么 $g_{i-1,j,k}$ 和 $g_{i,j+1,k}$ 也一定为 $1$。因此我们可以同样使用区间 dp 求数组 $g$，状态转移方程为（为了便于书写代码，使用逆推形式）：
$$
g_{i,j,k} \gets g_{i,j,k} \lor g_{i+1,j,k} \lor g_{i,j-1,k}
$$
现在关键的问题解决了，最后只需考虑初始化、边界和答案。

$g$ 数组在每次读入新的区间后就可以对区间内遍历初始化，$f$ 数组只需要对于区间长为 $1$ 的赋值为对应的 $g$ 数组值即可。

至于边界，如果我们运用以上状态转移方程，非法值均为 $0$，不用考虑。

答案即为 $f_{1,n}$。

### AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int l[125030],r[125030];
int f[504][504],g[504][504][504];
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) cin >> l[i] >> r[i];
	for (int i = 1; i <= m; i++) {
		for (int j = l[i];j <= r[i]; j++) {
			g[l[i]][r[i]][j] = 1;//初始化 g 数组
		}
	}
	for (int len = 2; len <= n; len++) {
		for (int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			for (int k = i; k <= j; k++) {
				g[i][j][k] |= (g[i+1][j][k]|g[i][j-1][k]); //对 g 数组 dp
			}
		}
	}
	for (int i = 1; i <= n; i++) f[i][i] = g[i][i][i];//初始化 f 数组
	for (int len = 2; len <= n; len++) {
		for (int i = 1; i + len - 1 <= n; i++) {
			int j = i + len - 1;
			for (int k = i; k <= j; k++) {
				f[i][j] = max(f[i][j],f[i][k-1]+f[k+1][j]+g[i][j][k]);//对 f 数组 dp
			}
		}
	}
	cout << f[1][n] << '\n';
	return 0;
}
```
### 另外想说的
这题其实有一道双倍经验：[P5851](https://www.luogu.com.cn/problem/P5851)，只不过那道题 $g$ 数组将不再只是 $1$ 或 $0$ 的变化，但是思路基本一致，完成本题后可以去看看。

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc168_d)

翻 kenkoooo 发现这是个 2400，感觉区间 dp 是不是在国外算是比较困难啊。（怎么计数题却偏低 qwq）

考虑设 $f(L, R)$ 表示只考虑 $[L, R]$ 中的格子（其他格子不涂）的最大操作次数。

那么转移显然是枚举一个白色格子 $i$，那么答案就是两边的答案加上是否存在一种方案可以覆盖 $i$，即是否存在一个操作 $[x, y]$ 满足 $L\le x\le i\le y\le R$。

设这个东西为 $g(L, R, i)$，可以发现这个东西也是一个区间 dp 啊，只需要看 $g(L + 1, R, i)$ 和 $g(L, R - 1, i)$ 是否有一个合法即可。

时间复杂度 $O(n ^ 3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 505;
#define ll long long
int inline read() {
	int num = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + (ch ^ 48);
		ch = getchar();
	}
	return num * f;
}
int n, m, f[N][N], g[N][N][N];
int main() {
#ifdef file
	freopen("ARC168D.in", "r", stdin);
	freopen("ARC168D.out", "w", stdout);
#endif
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) {
		int L = read(), R = read();
		for(int j = L; j <= R; ++j) g[L][R][j] = 1; 
	}
	for(int len = 2; len <= n; ++len) {
		for(int L = 1, R = len; R <= n; ++L, ++R) {
			for(int i = L; i <= R; ++i) {
				g[L][R][i] |= g[L + 1][R][i]; 
				g[L][R][i] |= g[L][R - 1][i];
			}
		}
	}
	for(int len = 1; len <= n; ++len) {
		for(int L = 1, R = len; R <= n; ++L, ++R) {
			for(int i = L; i <= R; ++i) {
				f[L][R] = max(f[L][R], f[L][i - 1] + f[i + 1][R] + g[L][R][i]);
			}
		}
	}
	printf("%d", f[1][n]);
	return 0;
}
```

~~怎么和其他题解代码这么像？~~

---

