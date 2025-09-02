# Cookies

## 题目描述

圣诞老人共有 $M$ 个饼干，准备全部分给 $N$ 个孩子。

每个孩子有一个贪婪度，第 $i$ 个孩子的贪婪度为 $g_i$。

如果有 $a_i$ 个孩子拿到的饼干数比第 $i$ 个孩子多，那么第 $i$ 个孩子会产生 $g_i\times a_i$ 的怨气。

给定 $N$、$M$ 和序列 $g$，圣诞老人请你帮他安排一种分配方式，使得每个孩子至少分到一块饼干，并且所有孩子的怨气总和最小。

## 说明/提示

数据保证，$1\leq N\leq 30$，$N\leq M\leq 5000$，$1\leq g_i\leq 10^7$。

## 样例 #1

### 输入

```
3 20
1 2 3```

### 输出

```
2
2 9 9```

# 题解

## 作者：liuChF (赞：6)

首先考虑贪心邻项交换，设有 $i$，$j$ 两个人，他们的 $g$ 固定，饼干数 $a$ 大的给 $g$ 更大的一个人才能使总怨气更少，所以降序排序 $g$。然后考虑 dp 的状态，常规的，$f_{i,j}$ 表示前 $i$ 个人花费 $j$ 块饼干的最小怨气，怎么转移呢？对于 $a_i<a_{i+1}$ 的，直接加上 $i\times g_i$ 即可，那如果 $a_i=a_{i+1}$ 呢？我们还要计算末尾饼干数相等的个数才能转移，在这种 dp 状态下很难快速维护（话说好像可以 $O(n)$ 维护，跟输出方案一样？）。所以我们可以考虑枚举后几位 $a$ 全为 $1$ 的情况，具体来说就是：
$$
f_{i,j}=\min_{0\le k<i}\{f_{k,j-(i-k)}+k\times\sum_{p=k+1}^{i}g_{p}\}\tag1
$$
其中 $f_{k,j-(i-k)}+\sum_{p=k+1}^{i}g_{p}$ 表示最后 $k+1\sim i$ 的位置只有一个饼干的怨气值，枚举 $k$ 从而转移到 $f_{i,j}$。这样就解决了吗？其实并没有，**还要和 $f_{i,j-i}$ 取 $\min$ 才行**。这一类状态也是合法的转移状态。为什么呢？考虑**缩放状态**。可以发现**将前 $i$ 个人的饼干数全都加减一个数时，由于相对大小不变，怨气值是不变的**，所以有 $f_{i,j}=f_{i,j-i}$，因为我们在计算 $f_{i,j}$ 时，所有的 $f_{i',j'(i'\le i,j'<j)}$ 都是已知的，所以可以转移，那要不要考虑 $f_{i,j-2\times i}$ 呢？并不用，因为这个状态已经包含在 $f_{i,j-i}$ 了，而 $f_{i,j-i}$ 又转移到了 $f_{i,j}$ 了。

在输出方案时是最有趣的地方，解决了我看书做题时不懂的地方（输出方案是书上没有涉及的）。首先根据常规套路，用 `pre` 数组记录方案的转移，然后递归输出，得到：

```cpp
0 0
2 2
2 4
3 5
3 8
3 11
3 14
3 17
3 20
```

啊，这是什么意思？仔细理解一下，发现当 $i$ 相等时，是通过 $f_{i,j}=f_{i,j-i}$ 转移的；而当 $i$ 变化时，是通过上面的 $(1)$ 式进行的转移，那最终的 $a$ 数组是多少呢？再想一下，通过第一种转移过来的就相当于将 $a_{1\sim i}$ 全部加 $1$，而当 $i$ 变化时，就是将 $a_{i_1+1}\sim a_{i_2+1}$ 全部加 $1$（在前 $i$ 个数固定的情况下，再将这后面的数变成 $1$，现在反着变回去）。什么意思？模拟一下：

```cpp
i j	    a[1~3]	
0 0		0 0 0
2 2		1 1 0 // 转移过程: i = 2 时,在 0 0 0 的基础上将最后 2 位改为 1
2 4		2 2 0 // 转移过程: i = 2 时,在 1 1 0 的基础上全部增加 1
3 5		2 2 1 // 转移过程: i = 3 时,在 2 2 0 的基础上将最后 1 位改为 1
3 8		3 3 2 // 转移过程: i = 3 时,在 2 2 1 的基础上全部增加 1
3 11	4 4 3 // 以此类推...
3 14	5 5 4
3 17	6 6 5
3 20	7 7 6
```

这样就很好理解了转移的过程，递归时修改用前缀和就行。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define fq(i,d,u) for(int i(d); i <= u; ++i)
#define fr(i,u,d) for(int i(u); i >= d; --i)
using namespace std;
const int N = 35, M = 5e3+5;
struct from {
	int i, j;
} pre[N][M];
struct node {
	int v, id;
} g[N];
int n, m, f[N][M], s[N], idx[N], ans[N];
// 前 i 个人,花费 j 个饼干的最小怨气
bool cmp(node a, node b) {
	return a.v > b.v;
}
void back(from p, from fa) {
	if (p.i == fa.i) idx[1]++, idx[p.i + 1]--;
	else idx[p.i + 1]++, idx[fa.i + 1]--;
	if (p.i == 0) return ;
	back(pre[p.i][p.j], p);
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	fq(i, 1, n) cin >> g[i].v, g[i].id = i;
	sort(g + 1, g + 1 + n, cmp);
	fq(i, 1, n) s[i] = s[i - 1] + g[i].v;
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	fq(i, 1, n) fq(j, i, m) {
		int ret = f[i][j - i];
		pre[i][j] = {i, j - i};
		fq(k, 0, i - 1) { // 枚举 k ~ i 都为 1 的 f 最小值
			int val = f[k][j - (i - k)] + k * (s[i] - s[k]);
			if (val < ret) {
				ret = val;
				pre[i][j] = {k, j - (i - k)}; // (i - k) 表示 后面 1 的费用
			}
		}
		f[i][j] = min(f[i][j], ret);
	}
	cout << f[n][m] << '\n';
	back(pre[n][m], from {n, m});
	fq(i, 0, n) idx[i] += idx[i - 1];
	fq(i, 1, n) ans[g[i].id] = idx[i];
	fq(i, 1, n) cout << ans[i] << ' ';
	return 0;
}
```

---

## 作者：floris (赞：4)

## 思路

注：本题思路参考自蓝书。

这个题解法并不是很多，主要的便是 dp 方法。

首先，比较显然的是，贪婪度较大的孩子一定会得到较多的饼干。因此，我们先将孩子的贪婪度从大到小排列。

我们再考虑转移。可以设 $f[i,j]$ 表示前 $i$ 个孩子一共分配 $j$ 个饼干时怨气的最小值。转移时分两种情况：

第一种：第 $i+1$ 个孩子获得的饼干数比第 $i$ 个少。

第二种：第 $i+1$ 个孩子获得的饼干数和第 $i$ 个相同。

而在两种情况下，我们需要知道第 $i$ 个孩子的饼干数，以及 $i$ 之前与第 $i$ 个孩子饼干数相同的孩子的个数。由于数据较大我们很难维护，于是我们可以做一个等价代换：

>若第 $i$ 个孩子的饼干数大于 $1$，由于 $i$ 之前孩子的饼干数也大于 $1$，则等价于分配 $j-i$ 个饼干给前 $i$ 个孩子，这样的代换并不会影响怨气值，因为两两孩子饼干数差不变。

所以，我们可以得到状态转移方程：

$f[i,j]=$ $\min$ $\begin{cases}f[i,j-i]\\ \min\limits_{0\le k<i} \left\{f[k,j-(i-k)]+k\times \sum_{p=k+1}^{i}g[p] \right\} \end{cases}$

最小值就是 $f[n,m]$ 了。

而对于方案，我们在求最小值是顺便记录每个孩子饼干数变化，最后使用一个递推函数找出方案即可。

## code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 31
int n,m,b[N][5005],ans[N];
struct node{
	int x,id;
}e[N];
bool cmp(node x,node y){
	return x.x>y.x;
}
int f[N][5005];
void print(int x,int y){
	if(x==0) return ;
	for(int i=1;i<=x;i++){
		e[i].x++;
	}
	print(b[x][y],y-x);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>e[i].x;
		e[i].id=i;
	}
	sort(e+1,e+n+1,cmp);
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			if(j-i<0) continue;
			int minn=1e9;
			for(int k=0;k<=i;k++){
				int sum=0;
				for(int p=k+1;p<=i;p++)  sum+=e[p].x;
				if(f[k][j-i]+k*sum<minn){
					minn=f[k][j-i]+k*sum;
					b[i][j]=k;
				}
				//minn=min(minn,f[k][j-(i-k)]+k*sum);
			}
			f[i][j]=(f[i][j-i],minn);
		}
	}
	for(int i=1;i<=n;i++) e[i].x=0;
	print(n,m);
	for(int i=1;i<=n;i++){
		ans[e[i].id]=e[i].x;
	}
	cout<<f[n][m]<<'\n';
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}

```

---

## 作者：CatFromMars (赞：2)

首先考虑如何确定 dp 的顺序，不难想到可以按照 $g$ 从大到小排序，对于 $g$ 越大，$a$ 要越小，获得的饼干就要越多。

有了这个前提就能够想到，每个孩子拿到的饼干数量是单调的。所以可以有这样两种做法：
### Sol1
将 $g$ 从大到小排序，设 $f[i, j, L]$ 为前 $i$ 个孩子，一共有了 $j$ 个饼干，最后一个孩子的饼干数量为 $L$ 个。那么方程也容易得到

$f[i, j, L] = \min\limits_{0 \le k < i}\{\min\limits_{L \le H \le m}\{f[k, j - (i - k)L, H]\} + (q[i] - q[k])k\}$。注意到应该是 $L < H \le m$，但是很显然 $H = i$ 的时候是不优的。这样可以让式子更好看（划掉）（对下面式子转化也有帮助）

这个式子有 $O(nm^2)$ 个状态，每个状态转移又需要 $O(nm)$ 的复杂度。当然过不去，我们先考虑状态的优化。

很显然，$i,j$ 看上去是必须要有的状态，考虑把阶段 $L$ 砍掉。$L$ 的作用是保证单调不降的。如果两个吃饼干的方案使得相邻两个小朋友相对的大小不变，那么它们的 $f$ 值也相等。这可以给我们一个启发：如果我们将每个小朋友吃的饼干数同时减去 $(L-1)$，那么它的相对大小不变，$f$ 也相等。

也就是说，$f[i, j, L] = f[i, j - i(L - 1), 1]$，所以只要转移 $f[i, j, 1]$ 即可。我们重新写一下方程。

$f[i, j, 1] = \min\limits_{0 \le k < i}\{\min\limits_{1\le  H \le m}\{f[k, j - (i - k), H]\} + (q[i] - q[k])k\}$。

设 $g[i, j] = \min\limits_{1\le H \le m}\{f[i, j, H]\} = \min\limits_{1\le H \le m}\{f[i, j - i(H-1), 1]\} = \min\limits_{0\le H \le m}\{f[i, j - iH, 1]\}$，则 $f[i, j] = \min\limits_{0\le k < i}\{g[k,  j - (i - k)] + (q[i] - q[k])k\}$。

对于 $f$ 的转移变成了 $O(n^2m)$ 的了，考虑对 $g$ 的转移。容易发现 $g[i, j] = \min\limits_{0\le H \le m}\{f[i, j-iH, 1]\} = \min\{g[i, j - i], f[i, j, 1]\}$。这样子 $g$ 的转移就是 $O(nm)$ 的了。因此总时间复杂度是 $O(n^2m)$。

代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 30, M = 5000;
int a[N + 10], qz[N + 10], n, m;
int f[N + 10][M + 10], g[N + 10][M + 10], cs[N + 10][M + 10], pre[N + 10][M + 10];
struct node {
	int val, ind;
} A[N + 10];
bool cmp(node &x, node &y) {
	return x.val > y.val;
}
int qry(int i, int j, int L) {
	return f[i][j - i * (L - 1)];
}
int ans[N + 10];
void print(int n, int m) {
	if(!n) return ;
	int v = cs[n][m];
	int l = pre[n][m - (v - 1) * n];
	for(int i = l + 1; i <= n; i++) 
		ans[A[i].ind] = v;
	print(l, m - (n - l) * v);
}

signed main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> a[i], a[i] *= -1;
		A[i].val = -a[i], A[i].ind = i;
	}
	sort(a + 1, a + n + 1);
	sort(A + 1, A + n + 1, cmp);

	for(int i = 1; i <= n; i++)
		a[i] *= -1, qz[i] = qz[i - 1] + a[i];

	memset(g, 0x3f, sizeof(g));
	memset(f, 0x3f, sizeof(f));
	for(int i = 1; i <= n; i++)
		f[i][i] = 0, pre[i][i] = 0;
	for(int j = 1; j <= m; j++) {
		g[1][j] = 0;
		cs[1][j] = j;
	}
	

	for(int i = 2; i <= n; i++) {
		for(int j = i; j <= m; j++) {

			for(int k = 0; k < i; k++)
				if(j >= (i - k)) {
					if(g[k][j - (i - k)] + (qz[i] - qz[k]) * k <= f[i][j]) {
						f[i][j] = g[k][j - (i - k)] + (qz[i] - qz[k]) * k;
						pre[i][j] = k;
					}
				}

			if(f[i][j] < g[i][j - i]) {
				g[i][j] = f[i][j];
				cs[i][j] = 1;
			}
			else {
				g[i][j] = g[i][j - i];
				cs[i][j] = cs[i][j - i] + 1;
			}
		}
	}
	cout << g[n][m] << endl;
	print(n, m);
	for(int i = 1; i <= n; i++)
		cout << ans[i] << ' ';
}
```

### Sol2

回顾上面的优化过程围绕着砍掉 $L$ 这一个维度展开。$L$ 这个维度的作用是为了保证单调。上面利用的是状态的等效砍掉了这一维度。

保证单调的技巧还可以利用差分。如果我们按照 $g$ 从小到大排序，那么得到的饼干单调不降，这个时候得到的饼干的差分数组都大于等于 $0$。这样就消除了相互之间的影响，也就不用记录 $L$ 了。对于 $j$ 这个维度则要提前计算这个全局的贡献。

具体而言，$f[i, j]$ 代表前 $i$ 个小朋友，全局有 $j$ 个饼干的最小代价。

假设我们得到了每个小朋友的饼干数量 $d$，我们对 $d$ 进行差分得到 $c$。由于 $d$ 单调不降，因此 $c$ 全部大于等于 $0$。对于一个形如 ```a 0 0 0``` 这一段代表这里面所有的小朋友分到了同一个数量的饼干。

此时第二维 $j = \sum\limits_{w = 1}^id_w = \sum\limits_{w = 1}^i\sum\limits_{v = 1}^wc_v = \sum\limits_{w = 1}^i(i - w+1)c_i$。

对于 $[k+1, i]$ 这一段小朋友假设他们的吃饼干数量相同。转移考虑 $c[k+1] = C$，那么 $f[i, j] = \min\limits_{1 \le C \le m}\{f[k, j - (n - k)C] + (n - i)(q[i]-q[k])\}$

考虑优化这个式子。假设 $i, k$ 为常量。类似于单调队列优化多重背包，将 $j$ 按照对 $(n - k)$ 取模的结果分类。$g[x]$ 为 $j \bmod (n - k) = x$ 中的最小 $f[k, j - (n - k)C]$。那么也就不难得到优化之后的转移

1. $j < (n - k)$ 的时候 $g[j] = f[k, j]$
2. $j \ge (n - k)$ 的时候，$f[i, j] = \min\{f[i, j], g[j \bmod (n - k)] +(n - i)(q[i] - q[k])\}$。接下来 $g[j \bmod (n - k)] = \min\{g[j \bmod(n- k), f[i, j]\}$（这两步的顺序是为了让 $C \not= 0$）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 30, M = 5000;
int f[N + 10][M + 10], g[N + 10], n, m, qz[N + 10];
int prek[N + 10][M + 10], prec[N + 10][M + 10];
int h[N + 10], c[N + 10], ans[N + 10];
struct node {
	int val;
	int ind;
} A[N + 10];
bool cmp(node &x, node &y) {
	return x.val < y.val;
}

void print(int i, int j) {
	if(!i) return ;
	int k = prek[i][j], c = prec[i][j];
	for(int l = k + 1; l <= n; l++)
		ans[A[l].ind] += c;
	print(k, j - (n - k) * c);
}
int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> g[i];
		A[i].val = g[i];
		A[i].ind = i;
	}
	sort(g + 1, g + n + 1);
	sort(A + 1, A + n + 1, cmp);
	for(int i = 1; i <= n; i++)
		qz[i] = qz[i - 1] + g[i];
	
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
			
	for(int i = 1; i <= n; i++) {
		for(int k = 0; k < i; k++) {
			memset(h, 0x3f, sizeof(h));
			memset(c, 0, sizeof(c));
			for(int j = 0; j < (n - k); j++)
				h[j] = f[k][j];
			
			for(int j = (n - k); j <= m; j++) {
				int w = h[j % (n - k)] + (qz[i] - qz[k]) * (n - i);
				if(w < f[i][j]) {
					prek[i][j] = k;
					prec[i][j] = c[j % (n - k)] + 1;
					f[i][j] = w;
				}
				
				if(f[k][j] < h[j % (n - k)]) {
					c[j % (n - k)] = 0;
					h[j % (n - k)] = f[k][j];
				}
				else c[j % (n - k)]++;
			} 
		}
	}
	
	cout << f[n][m] << endl;
	print(n, m);
	for(int i = 1; i <= n; i++)
		cout << ans[i] << ' '; 
}
```

这种利用差分数组的非负性维护单调性可以消除与前一个数之间的影响。在别的题目里也有应用（比如[这个](https://www.luogu.com.cn/problem/P7519)）

萌新才学疏浅，写的不太清楚，希望大家多多包涵 qwq

---

## 作者：hgckythgcfhk (赞：2)

提供一个能卡过，甚至能到最优解，不用 ```dp``` 的暴力乱搞做法。

其他题解说的很清楚了，每个人分配到的饼干个数随 $g_i$ 递增。

下面我默认先强制给每个人分一个然后令 $m=m-n$，这样可以取到 $0$。

我们先按 $g$ 降序，按所有人分配到的饼干的个数的个数分类讨论。

## 1. 所有人可以分配一样多

这种情况显然答案为 $0$，判定条件是 $m\equiv 0\pmod n$。

## 2. 一共有两种不同个数

当 $\lfloor \dfrac{m}{n-1}\rfloor\ge m\bmod (n-1)$ 时，我们可以，给前 $n-1$ 个分配 $\lfloor \dfrac{m}{n-1}\rfloor$ 个，给最后一个分配 $m\bmod (n-1)$ 个。

考虑满足不这个条件的 $m$ 的上界，由于 $m\bmod (n-1)\le n-2$，则有 $\lfloor \dfrac{m}{n-1}\rfloor\le n-1$，所以 $m\ge (n-1)^2+(n-2)=n^2-n+1$。

这样，我们把 $m$ 在 $O(n^2)$ 以上的情况干掉了，后面的 $O(m)$ 与 $O(n^2)$ 同级。

## 3. 一共有 $3$ 种不同个数

不难发现，把最小的个数全都清零分配到大的从而多造几个最大值显然更优，所以最小值一定是 $0$，但考虑到会有剩下一部分饼干的情况，可能会出现一个次大值，也就是说，我们最优策略是尽可能多造最大值，同时还可以发现，我们还要尽可能减少非最大值，于是我们可以直接枚举有多少个最大值，为了确定最大值具体是几，我们还得多枚举一下最大值或者次大值的值，多少个 $0$，$0$ 的个数从小到大枚举，只要搜到就停。

另外考虑到一些奇怪的奇偶性和边界的问题，次大值可能不止一个，但最多有两个，这个结论我没证出来，但我经过了又臭又长的巨型分讨后证明了在数据范围内是成立的，所以我们要把有一个次大值和两个的情况分别枚举。

分析一下时间复杂度，最后一种情况是瓶颈，所以只分析这一种就行，我们要枚举有多少个最大值这个是 $O(n)$ 的，多少个次大值，由于次大值的个数只有两种可能，所以是 $O(1)$ 的，还要枚举最大值或者次大值的具体值，只需要枚举一个就行，另一个可以算出来，这个是 $O(m)$ 的，由于 $O(m)$ 与 $O(n^2)$ 同级，总时间复杂度是 $O(n^3)$ 的，而目前已有的题解是 $O(n^2m)$ 也就是 $O(n^4)$ 的，所以这个做法可以很轻松卡过。

关于正确性，我有一个很长的证明，但考虑到这个构造比较自然，而且证明太过麻烦，所以不放了，我希望看到一个简洁的证明或者证伪，不过，即使你 ```hack``` 掉了我次大值最多两个的情况，我再多枚举一个次大值的个数只会使时间复杂度多带一个 $\ln n$，依然是严格优于正解的，同时，这里面有很多优化比如如果找到最大值比较多的就停，常数极小，大部分情况下我可以直接去掉一个 $O(n)$，而且 $m$ 一般是远小于 $n^2$ 的，可以证明，由于数据过小，一定造不出来能 ```hack``` 掉我不同个数不超过 $3$ 个这条性质，经过实测，$n$ 开到 $10^3$ 也很难造这样的数据，反正我随了近 $10^3$ 组数据没随出来，自己造了一些特殊数据都过了。

说句闲话，如果你不判次大值有两个可以拿到 $91$ pts。

截至到现在：

最优解时间 $102$ ms，空间 $680$ kb。

正解最优时间 $116$ ms，空间 $684$ kb。

```cpp
#include <bits/stdc++.h>
#define il inline
#define rg register
#define cit const rg unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int rg unsigned
#define void il void
#define ll long long
#define ull unsigned ll
#define vector basic_string
#define vint vector<unsigned>
#define sca(a) for(int $=0;$<n;cin>>a[++$])using namespace std;constexpr unsigned N=30+1;
unsigned n,m,a[N],id[N],ans[N],b[N];
void init(){sca(a);
	for(int i=1;i<=n;++i)id[i]=i;
	for(int i=1;i<=n;++i)
		for(int j=1;j<n;++j)
			if(a[id[j+1]]>a[id[j]])swap(id[j],id[j+1]);
}
void solve(){cin>>n>>m;m-=n;init();
	if(m%n==0){cout<<"0\n";
		for(int i=1;i<=n;++i)cout<<m/n+1<<' ';
		return;
	}if(m%(n-1)<=m/(n-1)){
		ans[id[n]]=m%(n-1);int cnt=0;
		for(int i=1;i<n;++i)ans[id[i]]=m/(n-1);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(ans[j]>ans[i])cnt+=a[i];
		cout<<cnt<<'\n';for(int i=1;i<=n;++i)cout<<ans[i]+1<<' ';
		return;
	}if(n==2){cout<<a[id[1]]<<'\n';
		ans[id[1]]=m,ans[id[2]]=0;
		cout<<ans[1]<<' '<<ans[2];return;
	}int ll cnt=0;
	for(int l=n-2,r=n;l;--l,--r){
		for(int i=0;i<m;++i){
			cit t=m-i,tl=t/l,tr=(t-tl*l)/(n-r+1);
			if(((tl*l+i+tr*(n-r+1))^m)||i<tr||i>tl)continue;
			ans[id[l+1]]=i;
			for(int j=1;j<=l;++j)ans[id[j]]=tl;
			for(int j=n;j>=r;--j)ans[id[j]]=tr;
			for(int j=l+1;j<=n;++j){
				if(ans[id[l]]>ans[id[j]])cnt+=a[id[j]]*l;
				if(ans[id[l+1]]>ans[id[j]])cnt+=a[id[j]];
			}l=1;break;
		}
	}for(int l=n-3,r=n;l;--l,--r){
		for(int i=0;i+i<m;++i){
			cit t=m-i-i,tl=t/l,tr=(t-tl*l)/(n-r+1);
			if(((tl*l+i+i+tr*(n-r+1))^m)||i<tr||i>tl)continue;
			b[id[l+1]]=i;b[id[l+2]]=i;
			for(int j=1;j<=l;++j)b[id[j]]=tl;
			for(int j=n;j>=r;--j)b[id[j]]=tr;int ll _=0;
			for(int j=l+1;j<=n;++j){
				if(b[id[l]]>b[id[j]])_+=a[id[j]]*l;
				if(b[id[l+1]]>b[id[j]])_+=a[id[j]]<<1;
			}if(_<cnt){cnt=_;memcpy(ans,b,sizeof b);}
			else continue;l=1;break;
		}
	}cout<<cnt<<'\n';for(int j=1;j<=n;++j)cout<<ans[j]+1<<' ';	
}signed main(){open;int t=1;//cin>>t;
	while(t--)solve();}
```

为过审，删除了部分用不到的宏定义，不保证没有不小心多删

---

## 作者：dci66666 (赞：2)

今年CSP-S第三题没写出来，一气之下怒写蓝题动规。

## 题目理解
圣诞老人共有 $M$ 个饼干，准备全部分给 $N$ 个孩子。

每个孩子有一个贪婪度，第 $i$ 个孩子的贪婪度为 $g_i$。

如果有 $a_i$ 个孩子拿到的饼干数比第 $i$ 个孩子多，那么第 $i$ 个孩子会产生 $g_i\times a_i$ 的怨气。

给定 $N$、$M$ 和序列 $g$，圣诞老人请你帮他安排一种分配方式，使得每个孩子至少分到一块饼干，并且所有孩子的怨气总和最小（来自题面）。

怨气值最小，我们考虑贪心。如果 $g_i<g_j$ 且 $a_i>a_j$ 的话，那么两个值交换一定是较优的，因为当一个存在的 $a_i$ 值必将对所有比它小的值产生一的贡献，所以，当我们保证 $a_i$ 的产生贡献（也就是 $g_i$ 之和）最小时，因为 $g_i<g_j$，所以贡献值之和会变小。

但是如果不会相等的话这种思路确实是对的，可是事与愿违。

如果两个值相等的话那么两个值都不会产生相对的贡献，所以相等的贡献值很优。

那能不能使他们先全相等，再将多的改呢？

不行，很容易构造一组样例，相差非常大，那么改小的反而更优。

~~（人崩了，去看一眼题解）。~~

嗯，不愧是蓝题动规，就是难。

首先先考虑怎么设状态，虽然可能全相等的思路不对，但是区间之间可以相对相等，即一个区间的值可以相对平衡（其实就是加一个值减一个值该区间内贡献不变）。

设置 $f_{i,j}$ 表示前 $i$ 个值用 $j$ 的代价所用的最小值，因为这里面的 $n$ 值非常小，所以我们可以考虑将从所有点开始后面的值区间相等，将区间整体加 $1$，毕竟初始值为 $1$，对每一步考虑最优的操作，用数组记录。

但是还要每个点的值？不慌记录一个 $pre$ 数组差分就行了。

最后的操作也有要说的，比如该 $pre$ 值的 $i$ 相等，那么，一定是对该从一开始的节点区间进行加一操作，不然就是对 $pre$ 值的 $i$ 开始到该点的值区间加一。

好了，上代码吧（挺难的）。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int id,num;
}a[35];
int mp[35],n,m,sum_g[35],ans[35];
int cf[35],f[35][5005];
struct from{
	int id,val;
}pre[35][5005];
bool cmp(node x,node y){
	return x.num>y.num;
}
void get(from last,from now){
    if(last.id==now.id)cf[1]++,cf[last.id+1]--;
    else cf[last.id+1]++,cf[now.id+1]--;
    if(last.id==0)return ;
    get(pre[last.id][last.val],last);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].num;
		a[i].id=i;
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			f[i][j]=1e9+50;
		}
	}
	f[0][0]=0;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)sum_g[i]=sum_g[i-1]+a[i].num;
	for(int i=1;i<=n;i++){
		for(int j=i;j<=m;j++){
			int tp=f[i][j-i];
			pre[i][j]={i,j-i};
			for(int k=0;k<=i-1;k++){
				int v=(f[k][j-i+k]+k*(sum_g[i]-sum_g[k]));
				if(v<tp){
					pre[i][j]={k,j-i+k};
					tp=v;
				}
			}
			f[i][j]=min(f[i][j],tp);
		}
	}
    cout<<f[n][m]<<endl;
    get(pre[n][m],{n,m});
    int num=cf[0];
    for(int i=1;i<=n;i++){
    	num+=cf[i];
    	ans[a[i].id]=num;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
} 
```

---

## 作者：OldDriverTree (赞：2)

# Solution

好题。

不难发现一个性质，按 $g_i$ 从大到小排序，那么分到的饼干数也单调不升。

排序后 $\texttt{DP}$，设 $f_{i,j}$ 表示考虑前 $i$ 个人，分了 $j$ 块饼干的最小怨气值之和。

考虑如何转移，众所周知，单调不升的序列可以通过多个前缀相加组成。

例如序列 $3,2,2,1$ 就可以由 $1$ 个 $[1,1]$ 前缀，$1$ 个 $[1,3]$ 前缀和 $1$ 个 $[1,4]$ 前缀组成。

考虑枚举上一个前缀的位置 $k$（当前前缀就为 $[1,i]$），由于 $[1,k]$ 前缀都至少比 $[k+1,i]$ 多一个饼干，且 $[k+1,i]$ 分到的饼干数相同，那么对于 $[k+1,i]$ 的人，$a_i$ 就都等于 $k$，对答案的贡献就是 $(\sum_{o=k+1}^i a_o)\times k$，这里可以用前缀和优化，就是 $(s_i-s_k)\times k$。

所以状态转移方程就是 $f_{i,j}=\min_{0\le k\le i} f_{k,j-i}+(s_i-s_k)\times k$，求方案也不难，转移过程中记录一下由哪个位置转移过来，再。递归暴力加一下就行了。

时间复杂度 $O(n^2m)$，注意 $\texttt{DP}$ 完还要按原来的顺序输出，因为 $\texttt{DP}$ 前进行了一次排序。

# Code

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=31,M=5001;
int n,m,s[N],ans[N],pre[N][M];
struct node {
    int x,id;
    bool operator <(node o)const {
        return x>o.x;
    }
}a[N];
long long f[N][M];

void solve(int x,int y)
{
    if (!x) return;
    for (int i=1;i<=x;i++) a[i].x++;
    solve(pre[x][y],y-x);
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&a[i].x),a[i].id=i;
    sort(a+1,a+n+1);
    for (int i=1;i<=n;i++) s[i]=s[i-1]+a[i].x;
    memset(f,0x3f,sizeof f),f[0][0]=0;
    for (int i=1;i<=n;i++)
        for (int j=i;j<=m;j++)
            for (int k=0,t;k<=i;k++)
                if ( (t=f[k][j-i]+1ll*(s[i]-s[k])*k)<f[i][j])
                    f[i][j]=t,pre[i][j]=k;
    
    printf("%lld\n",f[n][m]);
    for (int i=1;i<=n;i++) a[i].x=0; solve(n,m);
    for (int i=1;i<=n;i++) ans[a[i].id]=a[i].x;
    for (int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：aCssen (赞：1)

### Solution
设 $f_{i,j}$ 表示考虑了前 $i$ 个人，分配了 $j$ 个饼干时的最小怨气，那么答案为 $f_{n,m}$。这个东西没法直接计算，所以我们考虑上一点手段。

考虑已经确定了一种饼干数量的分配方式，那么显然贪婪度大的孩子需要得到更多的饼干，用贪心交换可以证明这一点。

那么我们先把孩子按贪婪度排序，分配的饼干数一定是一个单调不增的序列。考虑给第 $i$ 个孩子分几块饼干，可这样还是不好算，再进行一个转化。

+ 如果第 $i$ 个孩子的饼干数大于 $1$，那么可以考虑将这 $i$ 个人都少分配一块饼干，这样相对大小关系不变从而怨气值也不变，此时 $f_{i,j}=f_{i,j-i}$，对于每个 $i$，$f_{i,j}$ 是随着 $j$ 的增大而计算的，所以没有问题。

+ 如果第 $i$ 个孩子的饼干数为 $1$，则可以考虑有多少个孩子得到了一块饼干。即枚举一个 $k$，$k$ 后的孩子都只有 $1$ 块饼干，则第 $i$ 个孩子产生的怨气值就是 $k \times \sum_{X=k+1}^i g_X+f_{k,j-(i-k)}$。

综上，经过一系列转化，我们得到：

$$f_{i,j}=\min(f_{i,j-i}[j>i],\min _{\max(i-j+1,0) \le k <i}\{k \times \sum_{X=k+1}^i g_X+f_{k,j-(i-k)}\}$$

输出方案与其他题一样，记下选定 $f$ 数组的两维的值即可。

时间复杂度 $\mathcal{O}(n^2 m)$。

### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxm=5005;
struct node{int g,id;}a[35];
int f[35][maxm],ans[35],s[35],id[35],n,m;
pair<int,int>pre[35][maxm];
void print(int N,int M){
    if(!N) return;
    int i=pre[N][M].first,j=pre[N][M].second;
    print(i,j);
    if(i==N) for(int p=1;p<=i;p++) ans[id[p]]++;
    else for(int p=i+1;p<=N;p++) ans[id[p]]=1;
}
int main(){
    memset(f,0x3f,sizeof(f));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i].g),a[i].id=i;
    f[0][0]=0;
    sort(a+1,a+n+1,[](node x,node y){return x.g>y.g;});
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+a[i].g;
        id[i]=a[i].id;
    }
    for(int i=1;i<=n;i++){
        for(int j=i;j<=m;j++){
            if(f[i][j-i]<f[i][j]){
                f[i][j]=f[i][j-i];
                pre[i][j]=make_pair(i,j-i);
            }
            for(int k=0;k<i;k++){
                int w=k*(s[i]-s[k])+f[k][j-(i-k)];
                if(w<f[i][j]){
                    f[i][j]=w;
                    pre[i][j]=make_pair(k,j-(i-k));
                }
            }

        }
    }
    printf("%d\n",f[n][m]);
    print(n,m);
    for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：hinin (赞：0)

### 思路

一个显然的结论：愤怒值高的小朋友分配的饼干要更多一些。

设出状态转移的数组 $dp_{i, j}$：意味将前 $j$ 个饼干分给前 $i$ 个人（已排序），为了保持最优，饼干数单调下降。

易得状态转移方程：$f_{i, j} = \min(f_{i, j - i}, f_{i - k, j - k} + (s_i - s_{i - k}) \times (i - k))$。

### 代码

``` cpp
#include <bits/stdc++.h>
// #pragma GCC optimize("Ofast", "-funroll-all-loops")
#define ll long long 
#define pii pair<int, int>
 
#define y1 gigay 
#define x first 
#define y second 
 
using namespace std;

const int N = 3e1 + 1, M = 5e3 + 1;
int n, m, s[N], f[N][M], ans[N];
pii g[N];

int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 

	cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		cin >> g[i].first;
		g[i].second = i;
	}

	sort(g + 1, g + n + 1);
	reverse(g + 1, g + n + 1);

	for (int i = 1; i <= n; i ++) { s[i] = s[i - 1] + g[i].first; }

	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;

	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) {
			if (j >= i) { f[i][j] = f[i][j - i]; }
			for (int k = 1; k <= i && k <= j; k ++)
			{ f[i][j] = min(f[i][j], f[i - k][j - k] + (s[i] - s[i - k]) * (i - k)); }
		}
	}

	cout << f[n][m] << endl;

	int i = n, j = m, h = 0;

	while (i && j) {
		if (j >= i && f[i][j] == f[i][j - i]) { j -= i, h ++; }
		else for (int k = 1; k <= i && k <= j; k ++) {
			if (f[i][j] == f[i - k][j - k] + (s[i] - s[i - k]) * (i - k)) {
				for (int u = i; u > i - k; u --)
				{ ans[g[u].second] = 1 + h; }
				
				i -= k; 
				j -= k;
				break;
			}
		}
	}

	for (int i = 1; i <= n; i ++) { cout << ans[i] << ' '; }
	cout << endl;

	return 0;
}
```

---

## 作者：SmileMask (赞：0)

贪心的，考虑按 $g$ 排序，那么整个序列一定为不降的。直接 $dp$ 不好统计，考虑将其差分，此时序列为 $x_1,0,0,\dots,x2,0,\dots,x3,0,\dots$，不妨考虑将其分为若干段统计。

正序做不好统计，考虑倒序。记 $f_{i,j}$ 为后 $i$ 个数用了 $j$ 块饼干的方案数，边界为 $f_{n+1,0}$，转移式有：
$$
f_{i,j}\leftarrow \min\limits_{k=i+1}^{n+1} \min_{w=1}^{j} f_{k,j-(n-i+1)\times w}+(S_i-S_k)\times (n-k+1)
$$
其中 $S$ 为 $g$ 的后缀和数组，总复杂度 $O(n^2m^2)$。

发现这个式子其实是完全背包的形式，即大小为 $(n-i+1)$ 的物品，权值为 $(S_i-S_k)\times (n-k+1)$，不用担心重复，因为这里取 $k=i$ 时权值为 $0$，考虑转化为完全背包的转移式，即自己能从小向大转移：
$$
f_{i,j}=\min_{k=i}^{n+1} f_{k,j-(n-i+1)}+(S_i-S_k)\times (n-k+1)
$$
答案为 $f_{1,m}$，求方案记录每个状态从哪里转移来即可，复杂度 $O(n^2m)$。

---

## 作者：OIer_ACMer (赞：0)

# 题目解析：

额，这道题的状态设定，就让人费解，不过闫氏动态规划分析法，还是好用，我们首先设 $dp_{i, j}$ 表示此时到了第 $i$ 个人有 $j$ 个饼干的最小怨恨值是多少。

所以，我们便不难发现，如果此时在人数为 $i$，饼干数是 $j$，则 $dp_{i, j}$ 和 $dp_{i, j +i}$ 的值相等。

如果原来有 $k$ 人，新加进来 $i-k$ 个人，则方程式根据上面的规律推导为：

$$ dp_{i, j}=dp_{k, j - (i - k)}+k\times\sum^i_{x=k+1}qzh_x$$

第二部分就是对应着第一种情况，即给每个人都发一颗糖，总怨恨值不会变，但只是对于 $dp_{i, j - 1}$ 不变，对于 $dp_{i, j}$ 还是要有所考虑，由于 $dp_{i, j}$ 参与了第一部分的转移，就要在两者之间去最优值，即最小值，若原先的 $dp_{i, j - 1}$ 比转以后的 $dp_{i,j}$ 小，则再复原。

最后，我们确立边界条件，很简单，$dp_{i, i}$ 就和 $dp_{0, 0}$ 一样，都是 $0$，毕竟没有比较没有伤害，答案便是 $dp_{n, m}$。

对于第二问，我们知道第一问就不难搞出，**根据动态规划若有方案发生变化必然对应着最优解状态的转换**，即在第二步 $dp_{i, j}$ 和 $dp_{i, j - i}$ 中发生与原来不一样的变化，我们用两个数组 $g1$ 和 $g2$ 分别记录转移前的状态，对于第一种情况是 $i$ 和 $j - i$，第二种是 $j$ 和 $j - (i - k)$，根据记录结果逆推就行了。

# 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
// #define int long long
int qzh[1000009], dp[109][1000009];
int g1[109][1000009], g2[109][1000009], ans[1000009];
struct Node
{
    int val, id;
    const bool operator<(Node another)
    {
        return val > another.val;
    }
} a[1000009];
void find(int x, int y)
{
    if (x == 0)
    {
        return;
    }
    find(g1[x][y], g2[x][y]);
    if (x != g1[x][y])
    {
        for (int i = g1[x][y] + 1; i <= x; i++)
        {
            ans[a[i].id] = 1;
        }
    }
    else
    {
        for (int i = 1; i <= x; i++)
        {
            ans[a[i].id]++;
        }
    }
}
signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].val;
        a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    {
        qzh[i] = qzh[i - 1] + a[i].val;
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= m; j++)
        {
            for (int k = 0; k < i; k++)
            {
                if (dp[k][j - (i - k)] + k * (qzh[i] - qzh[k]) < dp[i][j])
                {
                    dp[i][j] = dp[k][j - (i - k)] + k * (qzh[i] - qzh[k]);
                    g1[i][j] = k;
                    g2[i][j] = j - (i - k);
                }
            }
            if (dp[i][j - i] < dp[i][j])
            {
                dp[i][j] = dp[i][j - i];
                g1[i][j] = i;
                g2[i][j] = j - i;
            }
        }
    }
    cout << dp[n][m] << '\n';
    find(n, m);
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
```

---

