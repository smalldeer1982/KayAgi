# [ARC097E] Sorted and Sorted

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc097/tasks/arc097_c

それぞれ $ 1 $ から $ N $ の整数が $ 1 $ つずつ書かれた白いボールと黒いボールが合わせて $ 2N $ 個一列に並んでいます。 左から $ i $ ($ 1 $ $ <\ = $ $ i $ $ <\ = $ $ 2N $) 個目のボールに書いてある数は $ a_i $ で、色は $ c_i $ で表されます。 $ c_i $ $ = $ `W` のとき ボールが白いことを、$ c_i $ $ = $ `B` のとき ボールが黒いことを表します。

人間の高橋君は次のような目標を達成したいです。

- $ 1 $ $ <\ = $ $ i $ $ j $ $ <\ = $ $ N $ を満たす任意の整数の組 $ (i,j) $ に対して、$ i $ が書かれた白いボールの方が $ j $ が書かれた白いボールより左にある
- $ 1 $ $ <\ = $ $ i $ $ j $ $ <\ = $ $ N $ を満たす任意の整数の組 $ (i,j) $ に対して、$ i $ が書かれた黒いボールの方が $ j $ が書かれた黒いボールより左にある

目標を達成するために高橋君は次のような操作ができます。

- 隣り合う二つのボールをスワップする

目標を達成するために必要な操作回数の最小値を求めてください。

## 说明/提示

### 制約

- $ 1 $ $ <\ = $ $ N $ $ <\ = $ $ 2000 $
- $ 1 $ $ <\ = $ $ a_i $ $ <\ = $ $ N $
- $ c_i $ $ = $ `W` または $ c_i $ $ = $ `B`
- $ i $ $ ≠ $ $ j $ なら、 $ (a_i,c_i) $ $ ≠ $ $ (a_j,c_j) $

### Sample Explanation 1

例えば次のようにすると $ 4 $ 回で可能です。 - 黒の $ 3 $ と白の $ 1 $ をスワップ - 白の $ 1 $ と白の $ 2 $ をスワップ - 黒の $ 3 $ と白の $ 3 $ をスワップ - 黒の $ 3 $ と黒の $ 2 $ をスワップ

## 样例 #1

### 输入

```
3
B 1
W 2
B 3
W 1
W 3
B 2```

### 输出

```
4```

## 样例 #2

### 输入

```
4
B 4
W 4
B 3
W 3
B 2
W 2
B 1
W 1```

### 输出

```
18```

## 样例 #3

### 输入

```
9
W 3
B 1
B 4
W 1
B 5
W 9
W 2
B 6
W 5
B 3
W 8
B 9
W 7
B 2
B 8
W 4
W 6
B 7```

### 输出

```
41```

# 题解

## 作者：Prean (赞：6)

感觉挺一眼的啊？

众所周知如果序列 $i$ 要通过相邻两项交换变成 $p_i$，那么交换次数就是 $\sum_{i<j}[p_i>p_j]$，或者说线段 $(i,p_i)$ 相交的对数。

于是一个很 naive 的想法就是枚举最终序列的黑白状态，但是这样显然行不通。

一看数据范围，$n=2000$，是不是能在上面做点手脚。

容易发现黑色球的序列和白色球的序列是单调的，所以只需要知道某个球前面有几个黑球几个白球以及这个球是什么颜色就能知道这个球的位置和权值应该是多少。

于是考虑 DP，设 $dp[n][m]$ 表示前 $n$ 个黑球和前 $m$ 个白球的线段最多有几个相交，容易发现就是 $i$ 比自己小 $p_i$ 比自己大的。

这个数线段非常容易，因为 $n$ 只有 $2000$ 所以可以直接暴力做二维偏序。

然后基本上就做完了，复杂度 $O(n^2)$，需要注意一些细节。
```cpp
#include<cstdio>
#include<cctype>
const int M=2005;
int n,S1[M][M*2],S2[M][M*2],dp[M][M],p1[M],p2[M];
inline char read_c(){
	char s;while(!isalpha(s=getchar()));return s;
}
inline int read(){
	int n(0);char s;while(!isdigit(s=getchar()));while(n=n*10+(s&15),isdigit(s=getchar()));return n;
}
inline int min(const int&a,const int&b){
	return a>b?b:a;
}
signed main(){
	n=read();
	for(int i=1;i<=n*2;++i){
		bool typ=read_c()=='W';(typ?p1:p2)[read()]=i;
	}
	for(int i=1;i<=n;++i)++S1[i][p1[i]],++S2[i][p2[i]];
	for(int i=1;i<=n;++i)for(int j=1;j<=n*2;++j)S1[i][j]+=S1[i-1][j],S2[i][j]+=S2[i-1][j];
	for(int i=1;i<=n;++i)for(int j=1;j<=n*2;++j)S1[i][j]+=S1[i][j-1],S2[i][j]+=S2[i][j-1];
	for(int i=0;i<=n;++i)for(int j=0;j<=n;++j){
		const int&w1=(j?dp[i][j-1]+(i-S1[i][p2[j]-1])+(j?j-1-S2[j-1][p2[j]-1]:0):1e9);
		const int&w2=(i?dp[i-1][j]+(i?i-1-S1[i-1][p1[i]-1]:0)+(j-S2[j][p1[i]-1]):1e9);
		dp[i][j]=!i&&!j?0:min(w1,w2);
	}
	printf("%d",dp[n][n]);
}
```

---

## 作者：幻影星坚强 (赞：5)

我们发现最后的答案为相对位置发生改变了的球的对数之和。

很明显有个$O(n^2)$的dp，$dp[i][j]$表示放了数字为$1~i$的白球，$1~j$的黑球的最小答案，$ww[i][j],wb[i][j]$分别表示放了数字为$1~i$的白球，$1~j$的黑球，加一个数字为$i+1$的白球与加一个数字为$j+1$的黑球所产生的贡献，有dp方程:

$dp[i][j] = min(dp[i - 1][j] + ww[i - 1][j], dp[i][j - 1] + wb[i][j - 1])$

现在问题是怎么求出$ww$与$wb$

如果在没有放黑球的情况下继续放白球，那么他产生的贡献就是加上这个数字后原序列增加的逆序对个数，在没有放白球的情况下放黑球也同理。

假如在放了$i$个白球，$j$个黑球的情况下再放一个白球，可以通过放了$i$个白球，$j-1$个黑球的情况下再放一个白球，如果新加进来的这个白球原来比最后一个加进来的黑球位置靠后，那么最后的这个黑球由于放在新加的白球之前，所以相对位置在此情况会多增加1。放了$i$个白球，$j$个黑球的情况下再放一个黑球同理。于是我们便能$O(n^2)$进行预处理。

```
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 2010;
int n;
char s[2];
int col[N << 1], num[N << 1];
int posb[N], posw[N];
long long dp[N][N], wb[N][N], ww[N][N];
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= 2 * n; ++ i)
	{
		scanf("%s%d", s, &num[i]);
		if(s[0] == 'B')
		col[i] = 1;
	}
	for (int i = 1; i <= 2 * n; ++ i)
	{
		if(col[i] == 1)
		posb[num[i]] = i;
		else
		posw[num[i]] = i;
	}
	for (int i = 0; i < n; ++ i)
	{
		for (int j = 1; j <= i; ++ j)
		{
			ww[i][0] += (posw[j] > posw[i + 1]);
			wb[0][i] += (posb[j] > posb[i + 1]);
		}
	}
	for (int i = 0; i <= n; ++ i)
	{
		for (int j = 1; j <= n; ++ j)
		{
			wb[j][i] += wb[j - 1][i] + (posw[j] > posb[i + 1]);
			ww[i][j] += ww[i][j - 1] + (posb[j] > posw[i + 1]);
		}
	}
	for (int i = 0; i <= n; ++ i)
	{
		for (int j = 0; j <= n; ++ j)
		{
			dp[i][j] = 1e9 * (!(i == 0 && j == 0));
			if(i)
			dp[i][j] = min(dp[i - 1][j] + ww[i - 1][j], dp[i][j]);
			if(j)
			dp[i][j] = min(dp[i][j - 1] + wb[i][j - 1], dp[i][j]);
		}
	}
	printf("%lld", dp[n][n]);
}
```


---

## 作者：shinkuu (赞：4)

套路题。想要做类似的还可以做做 P6116。

对于不断交换两个数的操作，容易发现确定开始位置 $s$ 和最终位置 $t$，操作次数固定为 $|s-t|$。所以可以考虑对答案序列进行 dp。

容易想到设 $dp_{i,j}$ 为当前已经放好了前 $i$ 个白色和 $j$ 个黑色，最少需要多少次操作。则有状态转移方程：

$$dp_{i,j}=\min(dp_{i-1,j}+pos(i,0)-(i+j),dp_{i,j-1}+pos(j,1)-(i+j))$$

其中 $pos(i,0/1)$ 表示第 $i$ 小的白/黑色球进行前面操作后坐在的位置。

然后观察此方程是否有后效性。容易发现，当前面的数固定时，$pos(i,0/1)$ 也是固定的。故方程无后效性。

进一步地，可以将 $pos(x,0/1)$ 拆成其初始位置再分别加上移到它前面的黑/白球的数量。$O(n^2)$ 预处理。最后 $O(n^2)$ dp 即可。

code：

```cpp
int n,m,e[N],c[N],d[N][2],cst[N][N][2],dp[N][N];
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n*2){
		char op[3];
		int x;
		scanf("%s%d",op,&x);
		c[i]=op[0]=='B';
		e[i]=x;
		d[x][c[i]]=i;
	}
	rep(i,1,n){
		rep(j,1,n*2){
			cst[j][i][0]=cst[j][i-1][0];
			cst[j][i][1]=cst[j][i-1][1];
		}
		rep(j,1,d[i][0]){
			cst[j][i][0]++;
		}
		rep(j,1,d[i][1]){
			cst[j][i][1]++;
		}
	}
	mems(dp,0x3f);
	dp[0][0]=0;
	rep(i,1,n*2){
		rep(j,max(i-n,0),min(i,n)){
			int k=i-j;
			if(j)
				dp[j][k]=min(dp[j][k],dp[j-1][k]+d[j][0]+cst[d[j][0]][j-1][0]+cst[d[j][0]][k][1]-i);
			if(k)
				dp[j][k]=min(dp[j][k],dp[j][k-1]+d[k][1]+cst[d[k][1]][k-1][1]+cst[d[k][1]][j][0]-i);
		}
	}
	printf("%d\n",dp[n][n]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Yansuan_HCl (赞：1)

## 想法

### Hint 1

有一个重要的转化：交换所需的次数等于**重排后原下标的逆序对数**。（可以把重排后的序列看成需要按照下标排序的序列）这样，抽象的交换操作就转化为具体的逆序对数。

### Hint 2
记颜色为 $i$ 的黑球下标 $b_i$，白球为 $w_i$。**以黑球为主体统计**，则颜色为 $i$ 的黑球构成的**下标逆序对**可能是：

- 和黑球构成的；
- 和重排后值较小而下标较大的白球构成的；
- 和重排后值较大而下标较小的白球构成的。

### Hint 3

考虑**按颜色从小到大依次放入**，这样可以通过“放入和未放入”判断大小关系。

## 题解

把同色球的逆序对单独处理，不影响答案。此后，一个黑球的逆序对默认为和其他白球的。

可以 dp. 设 $f(i,j)$ 为第 $i$ 个黑球放在第 $i+j$ 个位置（即有 $j$ 个白球）。有 $f(i,j) \gets \min\{f(i,j-1),f(i-1,j)+g(i,j)\}$，其中 $g(i,j)$ 为把第 $i$ 个黑球放在第 $i+j$ 个位置产生的逆序对数。

$g(i,j)$ 可以 $O(n^2)$ 预处理。

## 代码

```cpp
const int N = 4005;
int n;
char c[N]; int a[N];

int f[N][N], g[N][N];
int pB[N], pW[N];

int main() {
    rd(n);
    U (i, 1, n * 2) {
        scanf("%c%d\n", c + i, a + i);
        if (c[i] == 'B') pB[a[i]] = i;
        else pW[a[i]] = i;
    }
    
    // 排序后，原下标的逆序对数
    // 计算每个黑球的贡献
    // 考虑把第 i 个黑球放在 i + j
    // 会和：
    // - 黑数字大于 i, 下标小于 
    // - 黑数字小于 i, 下标大于
    // - 白数字大于 j, 下标小于
    // - 白数字小于等于 j, 下标大于
    // 大力预处理？

    U (i, 1, n) {
        int cnt = 0;
        U (j, 1, n) cnt += pW[j] < pB[i];
        U (j, 0, n) {
            g[i][j] = cnt;
            cnt -= pW[j + 1] < pB[i];
            cnt += pW[j + 1] > pB[i];
        }
    }

    ms(f, 0x3f);
    U (i, 0, n) f[0][i] = 0;
    int ans = 0;
    U (i, 1, n)
        U (j, 1, i - 1)
            ans += (pB[i] < pB[j]) + (pW[i] < pW[j]);
    U (i, 1, n) U (j, 0, n) {
        int x = j ? f[i][j - 1] : 0x3f3f3f3f, y = f[i - 1][j] + g[i][j];
        f[i][j] = min(x, y);
    }

    printf("%d", ans + f[n][n]);
}
```

---

## 作者：Inzaghi_Luo (赞：0)

### 分析
对于这种交换求最小步数的题目，我们只用关心初始和最终状态即可。而我们知道最后两个颜色都是有序的，因此只用看如何把它们合并起来即可。数据范围一眼就是 DP 做，不然不会这么小。

设 $f[i][j]$ 代表放了 $i$ 个黑球和 $j$ 个白球的最小代价。转移比较简单，只是需要维护一下每一个球放的时候会有几个球跑到它前面，预处理一下就可以了。$pls$ 是同颜色的，$oth$ 是异颜色的。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
int a[MAXN << 1], wz[MAXN][2], f[MAXN][MAXN], pls[MAXN][2], oth[MAXN][MAXN][2];
int main(){
	int n;
	scanf("%d", &n);
	char ch[3];
	for(int i = 1;i <= 2 * n;i++){
		scanf("%s%d", ch, &a[i]);
		if(ch[0] == 'B') wz[a[i]][0] = i;
		else wz[a[i]][1] = i;
	}
	for(int k = 0;k < 2;k++){
		for(int i = 1;i <= n;i++){
			for(int j = 1;j < i;j++){
				if(wz[j][k] > wz[i][k]) pls[i][k]++;
			}
		}
	}
	for(int k = 0;k < 2;k++){
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				oth[i][j][k] = oth[i][j - 1][k];
				if(wz[j][k ^ 1] > wz[i][k]) oth[i][j][k]++;
			}
		}
	}
	for(int i = 0;i <= n;i++){
		for(int j = 0;j <= n;j++){
			if(!i && !j) continue;
			if(!i){
				f[i][j] = f[i][j - 1] + abs(wz[j][1] + pls[j][1] + oth[j][i][1] - i - j);
			}
			else if(!j){
				f[i][j] = f[i - 1][j] + abs(wz[i][0] + pls[i][0] + oth[i][j][0] - i - j);
			}
			else{
				f[i][j] = min(f[i][j - 1] + abs(wz[j][1] + pls[j][1] + oth[j][i][1] - i - j), f[i - 1][j] + abs(wz[i][0] + pls[i][0] + oth[i][j][0] - i - j));
			}
		}
	}
	printf("%d", f[n][n]);
	return 0;
}
```

---

## 作者：loveJY (赞：0)

AT4132 [ARC097C] Sorted and Sorted

主要是难以发现是dp

因为我们放入的黑白球一定是权值单调递增的,所以说

$f_{i,j}$表示放入了前i个白球,前j个黑球的最小代价

然后转移考虑放入第i个白球和第j个黑球的取min

$$f_{i,j}=min{f_{i-1,j}+costw_{i-1,j},f_{i,j-1}+costb_{i,j-1}}$$

这样我们要预处理后面那个数组....就是放入白球和黑球在这个状态下的代价的增量

costw?

发现是挺难的...不能直接计算

因为我们要考虑的是所有都排好之后的代价(不会超过$n^2$),显然这里就不能很劣....比方说直接位置相减

因为你想我们dp相当于dp出原序列一个操作顺序,而我们要的就是按照这个操作顺序一定能得到一组合法的构造解

所以说拆成这一步就是考虑在之前基础上再放上一个球

$$costw_{i,j}=costw_{i,.j-1}+pb_{j}>pw_{i+1}$$

$$costb_{i,j}=costw_{i-1,j}+pb_{j+1}<pw_{i}$$

而这样我们初值$costw_{i,0}$怎么搞啊

发现其实就是逆序对增量...注意是增量,因为我们的定义就是放入$i+1$额外代价

下面是代码

code:

```cpp

#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2006;
char s[MAXN];
int n, a[MAXN * 2], pw[MAXN * 2], pb[MAXN * 2], N, c[MAXN * 2];
int cost1[MAXN][MAXN], cost2[MAXN][MAXN];
int f[MAXN][MAXN];
inline void init1() {
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j <= n; ++j) {
			cost1[i][0] += (pw[j] < pw[i + 1]);
		}
	}
	for(int j = 0; j < n; ++j) {
		for(int i = j + 1; i <= n; ++i) {
			cost2[0][j] += (pb[j + 1] > pb[i]);
		}
	}
	return;
}

inline void init() {
	init1();
	for(int i = 0; i < n; ++i) {
		for(int j = 1; j <= n; ++j) {
			cost1[i][j] = cost1[i][j - 1] + (pw[i + 1] < pb[j]);
		}
	}
	for(int j = 0; j < n; ++j) {
		for(int i = 1; i <= n; ++i) {
			cost2[i][j] = cost2[i - 1][j] + (pw[i] > pb[j + 1]);
		}
	}
	return ;
}

inline void solve() {
	memset(f, 0x3f3f3f3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 0; i <= n; ++i) {
		for(int j = 0; j <= n; ++j) {
			if(i)
				f[i][j] = min(f[i - 1][j] + cost1[i - 1][j], f[i][j]);
			if(j)
				f[i][j] = min(f[i][j - 1] + cost2[i][j - 1], f[i][j]);
		}
	}
	printf("%d\n", f[n][n]);
	return ;
}

int main() {
	scanf("%d", &n);
	N = 2 * n;
	for(int i = 1; i <= N; ++i) {
		scanf("%s", s);
		c[i] = s[0] == 'B' ? 0 : 1;
		scanf("%d", &a[i]);
		if(c[i] == 0)pb[a[i]] = i;
		else pw[a[i]] = i;
	}
	init();//预处理cost数组
	solve();//dp
	return 0;
}



```

---

