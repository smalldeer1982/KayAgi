# [ABC366G] XOR Neighbors

## 题目描述

### 问题陈述

给出一个具有 $N$ 个顶点和 $M$ 个边的简单无向图。第 $i$ 个棱双向连接顶点 $u_i$ 和 $v_i$ 。

确定是否存在一种方法可以在此图的每个顶点上写入 $1$ 和 $2^{60} - 1$ 之间的整数，以满足以下条件:

对于每个至少有 $1$ 度的顶点 $v$ ，写在其相邻顶点(不包括 $v$ 本身)上的数字的总异或为 $0$。

## 说明/提示

- $1 \leq N \leq 60$
- $0 \leq M \leq N(N-1)/2$
- $1 \leq u_i < v_i \leq N$
- 如果 $i \neq j$，那么 $(u_i, v_i) \neq (u_j, v_j)$。
- 所有输入值都是整数。

## 样例 #1

### 输入

```
3 3
1 2
1 3
2 3```

### 输出

```
Yes
4 4 4```

## 样例 #2

### 输入

```
2 1
1 2```

### 输出

```
No```

## 样例 #3

### 输入

```
1 0```

### 输出

```
Yes
1```

## 样例 #4

### 输入

```
4 5
1 2
1 3
2 3
2 4
3 4```

### 输出

```
Yes
12 4 4 8```

# 题解

## 作者：Starrykiller (赞：12)

简要题意：给定矩阵 $\boldsymbol{A}$，求 $\mathrm{xor}$ 意义下 $\boldsymbol{Ax}=\boldsymbol{0}$ 的一组解 $\boldsymbol{x}$，满足 $\boldsymbol{x}$ 的任意一维中的元素均 $\in [\textcolor{red}{1}, 2^{60}) \cap \mathbb{Z}$。$N\le 60$。

$N$ 只有 $60$，考虑拆位。由于解不能包含 $0$，我们不妨钦定点 $i$ 的解中的第 $i$ 位为 $1$，这样刚好够用。

那么一共有 $(N+1)$ 个方程，$N$ 个变量，直接做 ${}\bmod 2$ 意义下的 Gauss 消元即可，无解就是出现形如 $0=1$ 的方程。这样，时间复杂度 $\Theta(N^4)$。

可以用一个 $64$ 位二进制数来压下一个方程，从而做到 $\Theta(N^3)$，不过这是不必要的。

[代码](https://atcoder.jp/contests/abc366/submissions/56582418)。

「希望和绝望的平衡相抵为零，又有谁，能来救赎我们呢。」

---

## 作者：Heldivis (赞：3)

## [ABC366G] XOR Neighbors

前置知识：高斯消元解异或线性方程组[^1]。

[^1]: [OI-Wiki：高斯消元—高斯消元法解异或方程组](https://oi-wiki.org/math/numerical/gauss/#%E9%AB%98%E6%96%AF%E6%B6%88%E5%85%83%E6%B3%95%E8%A7%A3%E5%BC%82%E6%88%96%E6%96%B9%E7%A8%8B%E7%BB%84)

对于给定 $N$ 个点，每个点所连的点的异或和为 $0$，其实就是有 $N$ 个方程。如对于点 $u$ 就是 $\bigoplus\limits_{u\to v}W_v=0$，其中 $W_i$ 表示点 $i$ 的数字。

对于一般的异或方程组，存在一组解 $\forall i,W_i=0$，但不符合本题题意。所以对于一个解出来为 $0$ 的变量，若不受已知变量约束的变量，令其为一个不会干扰其他二进制位的值（见下一段）；若受到已知变量约束的变量，则判定为无解。

对于第 $i$ 次赋值操作，将当前变量赋值为 $2^{i-1}$。由于异或的不进位性质，这样一定不干扰其他二进制位。并且由于 $N\le60$，这样赋值不会超出 $2^{60} - 1$ 的上限。

时间复杂度 $O(N^3)$，可以用 `std::bitset` 优化到 $O(\dfrac{N^3}\omega)$。

$O(N^3)$ 版本代码如下，Exec Time $1\text{ ms}$。

```cpp
n = read(), m = read();
for (int i = 1; i <= m; ++i) {
  int x = read(), y = read();
  a[x][y] = a[y][x] = 1;
}
for (int i = 1; i <= n; i++) {
  int r = i;
  for (int j = i + 1; j <= n; j++)
    if (abs(a[r][i]) < abs(a[j][i])) r = j;
  if (i != r) swap(a[i], a[r]);
  for (int j = i + 1; j <= n; j++)
    if (a[j][i] != 0)
      for (int k = i; k <= n + 1; k++) a[j][k] ^= a[i][k];
}
for (int i = n; i; i--) {
  ans[i] = a[i][n + 1];
  for (int j = i + 1; j <= n; j++) ans[i] ^= (a[i][j] * ans[j]);
  if ((ans[i] && !a[i][i]) || (!ans[i] && a[i][i])) return puts("No"), 0;
  // ans[i] && !a[i][i]：实际的 W[i] 是 ans[i] / 0，出现除以零，故无解
  // !ans[i] && a[i][i]：计算出来 W[i] = ans[i] 的确是 0，不符合题目约束，所以无解
  if (!ans[i]) ans[i] = 1ll << (tot++);
  // 这个 ans[i] == 0 是在 a[i][i] == 0 条件下计算得到的，实际上可以为任意值
}
puts("Yes");
for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
```

---

## 作者：Engulf (赞：2)

题目相当于给了一个线性异或方程组，高斯消元解它即可。

若 $x_i$ 是自由元，为了不影响其他的位，每个自由元都分配不同的 $2$ 的整数次幂即可。

时间复杂度 $O(n^3)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 65;

int n, m;

ll a[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        a[u][v] = a[v][u] = 1;
    }

    int r = 1;
    for (int c = 1; c <= n; c++) {
        int t = r;
        for (int i = r + 1; i <= n; i++)
            if (a[i][c] > a[t][c])
                t = i;
        swap(a[r], a[t]);

        for (int i = r + 1; i <= n; i++)
            if (a[i][c])
                for (int j = n + 1; j >= c; j--)
                    a[i][j] ^= a[r][j] * a[i][c];
        r++;
    }

    int tot = 0;
    for (int i = n; i; i--) {
        for (int j = i + 1; j <= n; j++)
            a[i][n + 1] ^= a[i][j] * a[j][n + 1];
        if (!a[i][i] && a[i][n + 1] || a[i][i] && !a[i][n + 1]) {
            cout << "No\n";
            exit(0);
        }
        if (!a[i][n + 1]) a[i][n + 1] = 1ll << tot++;
    }

    cout << "Yes\n";
    for (int i = 1; i <= n; i++)
        cout << a[i][n + 1] << " ";

    return 0;
}
```

---

## 作者：fydj (赞：2)

发现题目实质上就是让你构造一组 $a_{1,2,\dots,n}$，有一些限制，要求一些 $a$ 异或起来是 $0$。

看到 $n\le 60$，果断列异或方程组，用异或高斯消元。

具体地，有 $n$ 个方程组，$a_{i,j}$ 表示第 $i$ 个方程中 $j$ 的系数。对于每一个变量 $i$，要把 $j>i$ 的方程中的第 $i$ 项用第 $i$ 个方程异或起来消掉（如果 $a_{i,i}=0$ 就把一个 $a_{j,i}\ne 0$ 且 $j>i$ 的方程和第 $i$ 个方程交换），因为等号右边是 $0$ 所以可以不用处理。

从后往前构造解，如果 $a_{i,i}=0$，这是可能的，那么就令 $ans_{i}=2^i-1$；否则，就令 $ans_i=\bigoplus_{j>i} ans_j\times a_{i,j}$。

> 后一点比较容易理解，前一点不太容易理解，我认为这样子填 $ans_i$ 的话对于 $j<i$ 的 $ans_j$ 的第 $i$ 位反映的是 $ans_i$ 对 $ans_j$ 是否有影响，如果 $ans_j=0$，$ans_j$ 的第 $i$ 位一定是 $0$，这样子 $ans_i$ 对 $ans_j$ 没有影响，这样子 $ans_j$ 是 $0$ 这件事就和 $ans_i$ 无关的。类似的，可以发现这和每一个填 $ans_i=2^i-1$ 的 $ans_i$ 都没有关系，那么只能说明 $ans_j=0$ 是命中注定的，该局面无解。
>
> 事实上有人在 $a_{i,i}=0$ 时填 ```rand``` 也过了。

如果存在一个 $ans_i=0$，那么一定无解。

```cpp
const int N=65;
int n,m,a[N][N]={};
ll ans[N]={};
int main()
{
//	usefile("G");
	int i,j,k,x,y;
	read(n,m);
	for(i=1;i<=m;++i)
		read(x,y),a[x][y]^=1,a[y][x]^=1;
	for(i=1;i<=n;++i) {
		if(!a[i][i]) {
			for(j=i+1;j<=n;++j)
				if(a[j][i]) {
					swap(a[i],a[j]);
					break;
				}
		}
		if(!a[i][i]) continue;
		for(j=i+1;j<=n;++j)
			if(a[j][i]) {
				for(k=1;k<=n;++k)
					a[j][k]^=a[i][k];
			}
	}
	for(i=n;i;--i) {
		if(!a[i][i]) {
			ans[i]=(1ll<<i)-1;
			continue;
		}
		ans[i]=0;
		for(j=i+1;j<=n;++j)
			if(a[i][j])
				ans[i]^=ans[j];
	}
	for(i=1;i<=n;++i)
		if(!ans[i]) {
			printf("No\n");
			return 0;
		}
	printf("Yes\n");
	for(i=1;i<=n;++i)
		printf("%lld ",ans[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：SJZ2010 (赞：2)

## 题意

在图的点上写数字，使每个点相邻的点的异或和为 $0$，或报告无解。

## 做法

首先很明显的一点是这玩意是个线性异或方程组。

于是我们试图高斯消元。数据范围小，直接用 `long long` 存方程 $O(n^2)$ 消。

然后就发现，如何处理自由元？一个直觉是随便赋值比如 $1$，但是这样显然会发生矛盾。因为看起来更容易理解的 Gauss-Jordan 的斜线，并不能维护自由元的关系，即，Gauss-Jordan 只能告诉你有哪些自由元，不能告诉你它们构成的不定方程。

所以咋做啊？

——不要偷懒，使用 Gauss 消元，消成上三角。因为这样能维护更多的信息。（实际上现在这玩意已经是个线性基了，所以我们用不着高斯消元，用码量更小的线性基即可）

然后，我们就要构造解。如果不是自由元，那么解是显然的。是自由元的话，我们构造 $2^i$ 可以保证不会出现矛盾。因为 $x_{i + 1} \dots x_n$ 最高位 $<i$。

[AC.](https://atcoder.jp/contests/abc366/submissions/56585112)

---

## 作者：irris (赞：1)

## Preface

> 位运算, 拆位 / 高斯消元

$*900$，$6$。

这不是一个 $\tt 01$（[TernaryTree](https://www.luogu.com.cn/user/362750) 最喜欢的一类题目捏）串问题，但是这确实是一个 $\tt 01$（[TernaryTree](https://www.luogu.com.cn/user/362750) 最喜欢的一类题目捏）问题。

## Solution

异或运算按位独立，不妨考虑每一位，变成一个只和 $\tt 01$（[TernaryTree](https://www.luogu.com.cn/user/362750) 最喜欢的一类题目捏）有关的问题。

因为构造得的每个数都是 **正整数**，所以至少有一位是 $\tt 1$（[TernaryTree](https://www.luogu.com.cn/user/362750) 最喜欢的半类题目捏）。看到 $n \leq 60$，而值域范围是 $2^{60} - 1$ 最多恰好有 $60$ 位，不难想到对于第 $i$ 位，钦定第 $i$ 个数一定为 $\tt 1$（[TernaryTree](https://www.luogu.com.cn/user/362750) 最喜欢的半类题目捏），对剩下的数进行构造使得符合条件。

图其实是假的，事实上可以看做 $n$ 个关于某个集合里的数异或和为 $\tt 0$（[TernaryTree](https://www.luogu.com.cn/user/362750) 最喜欢的半类题目捏）的约束。发现包括钦定第 $i$ 个数为 $\tt 1$（[TernaryTree](https://www.luogu.com.cn/user/362750) 最喜欢的半类题目捏），所有条件都可以用异或线性方程组描述，于是直接高斯消元求出一组可行解（或者判断无解，直接退出）即可。

时间复杂度 $\mathcal O(\frac{n^4}{w})$。所以为啥不开到 $n \leq 400$？

---

## 作者：Lavaloon (赞：1)

**这里是并不那么本质的随机构造做法，同样获得了 1ms 的优秀战绩。**

## $\text{Analysis}$

题目的限制看起来很难处理，不妨考虑暴力一点的方法：**表示出所有限制。**

你需要给每个点赋一个值，满足任何一个点旁边的点的权值异或和为 $0$ ——这说明，每个限制的形式是一个异或方程，我们要解出这个方程组的一组合法解。

具体来说，建立方程组 $A$ 如下：

- 对于一条图中存在的边 $(u,v)$，令 $A_{u,v}=1,A_{v,u}=1$。

这个玩意和 [SDOI2010 外星千足虫](https://www.luogu.com.cn/problem/P2447) 也太像了，这启示我们使用**高斯消元**。

但是那个题并不需要构造一组解。

回过头来分析消元后的上三角矩阵。

**下称“位置”表示一个第 $i$ 行，第 $j$ 列对应的 $j$，即该坐标的纵坐标。**

假如存在一行，只有一个位置消元之后为 $1$，那么这个方程组一定无解，因为每个点的权值是 $>0$ 的。

异或的优秀性质告诉我们：

- 假如一行上为 $1$ 的 $k$ 个位置中，有 $k-1$ 个位置的权值已经确定了，那么最后一个位置的权值也是确定的——因为我们要使一行上为 $1$ 的 $k$ 个位置对应的权值异或和为 $0$。

尝试通过随机化进行构造。具体来说：

- 从最后一行开始逐个确定每个位置对应的值。
- 假如这个位置的值已经确定，那么跳过；否则给这个位置随机一个满足条件的值。
- 对于这一行的最后一个没有被赋值的位置，**直接将其赋值为这一行其余为 $1$ 的位置的异或和**——这保证了每一行异或和为 $0$ 的限制。
- 对于直到最后都没有被赋值的位置，随便赋一个值即可——其对整个方程组的正确性是无关紧要的。

接下来评估这个算法的正确率。

这个算法出错，当且仅当存在一行，在进行“直接将其赋值为这一行其余为 $1$ 的位置的异或和”这一步时，**恰好发现这个位置被赋值为 $0$ 了。**

这个东西发生的概率要低于随机两个数，它们相等的概率。

因为随机的值域很大，可以认为这种情况几乎不可能发生。

具体实现有三种：

- 暴力实现高斯消元，$\mathcal{O}(n^3+m)$。
- bitset 优化高斯消元，$\mathcal{O}(\dfrac{n^3}{w}+m)$。
- 压位高斯消元，$\mathcal{O}(n^2+m)$。

实际上第二种和第三种做法的复杂度是一样的。

这三种做法均可通过此题。

## $\text{Code}$

这里使用第二种方法实现，嘎嘎好写！

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<unordered_map>
#include<vector>
#include<bitset>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<random>
#include<numeric>
#include<assert.h>
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
bitset<1805>a[1805];
mt19937_64 rd(time(0));
uniform_int_distribution<int>dist(1,(1ll<<60)-1);
bool Gauss(){
	for(int j=1;j<=n;j++){
		int mx=j;
		for(int i=j+1;i<=n;i++) if(a[i][j]) mx=i;
		if(mx!=j) swap(a[j],a[mx]);
		for(int i=1;i<=n;i++){
			if(i==j) continue;
			if(a[i][j]) a[i]^=a[j];//嘎嘎好写！
		}
	}
	for(int i=1;i<=n;i++) if(a[i].count()==1) return 0;
	return 1;
}
int c[Mx];
signed main(){
	n=read(),m=read();
	for(int i=1,u,v;i<=m;i++){
		u=read(),v=read();
		a[u][v]=1,a[v][u]=1;
	}
	if(Gauss()){
		cout<<"Yes\n";
		for(int i=n;i>=1;i--){
			int v=0;
			int cnt=a[i].count();
			for(int j=n;j>=i;j--){
				if(a[i][j]==1){
					cnt--;
					if(cnt==0) c[j]=v;//最后一个未被赋值的位置
					else if(!c[j]) c[j]=dist(rd);//未被赋值，但不是最后一个
					v^=c[j];
				}
			}
		}
		for(int i=1;i<=n;i++) if(!c[i]) c[i]=1;//随便赋值
		for(int i=1;i<=n;i++) cout<<c[i]<<" ";
	}
	else cout<<"No";
	return 0;
}
```

---

## 作者：Richard_Whr (赞：1)

首先发现根据每个点可以列出 $n$ 个异或方程组。

然后就大力高斯消元（线性基即可实现），可以得到一个上三角。

发现需要赋值自由元，为了保证正确性，设是 $i$ 个权值是个自由元，那么就设为 $2^i$。

无解的情况仅存在于消成对角线后某个元只有自己这一位是 $1$，他就必须是 $0$，寄了。

其实也可以不消成对角线，直接判断是否异或了这一行所有元后自己变成 $0$ 了就行了，因为如果不是消完后只有自己一个 $1$ 的话，我们赋的权值是肯定保证不会成 $0$ 的。

代码还是很好写的，考察了对异或方程组构造合法可行解的方法。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=61;
bitset<N> A[N];
bitset<N> B[N];
vector<int> e[N];
int val[N];
int n,m;

void insert(bitset<N> f)
{
	for(int i=n-1;i>=0;i--)
	{
		if(!f[i]) continue;
		if(!B[i].count()) return B[i]=f,void(0);
		f=f^B[i];
	}
}

bool Gauss()
{
	for(int i=0;i<n;i++)
	{
		if(!B[i].count()) 
		{
			val[i]=(1ll<<i);
			continue;
		}
		for(int j=0;j<i;j++) if(B[i][j]) val[i]^=val[j];
		if(val[i]==0) return false;
	}
	return true;
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>n>>m;
	for(int i=1,a,b;i<=m;i++) cin>>a>>b,a--,b--,e[a].push_back(b),e[b].push_back(a);
	
	for(int u=0;u<n;u++)
	{
		for(auto v:e[u]) A[u][v]=1;
		insert(A[u]);
	}
	
	if(!Gauss()) cout<<"No\n";
	else
	{
		cout<<"Yes\n";
		for(int i=0;i<n;i++) cout<<val[i]<<" ";
	}
	
	return 0;
}
```

---

## 作者：TernaryTree (赞：1)

比较有趣的题啊，不算很难想。

显然不考虑权值不能为 $0$ 的限制，每位是独立的。那我们先拆出来一位，填上 $0,1$ 的权值（不能全填 $0$），让你构造一种方案。这等价于我们选了若干个位置权值为 $1$，然后每个点的所有相邻点里恰好有偶数个被选。我们算贡献，对每个选了的点，会对相邻的所有点造成 $1$ 的贡献，而我们只关心奇偶，不妨用异或来表示。令 $b_u$ 表示 $u$ 的所有相邻点的“状态”，那么选几个点满足限制的充要条件是，这几个点的 $b_u$ 异或和为 $0$。

那我们又需要让权值非 $0$，这等价于每个点至少被一位的构造点集覆盖到。因为恰好有 $60$ 位供你构造，容易想到给每个点分配一个位，钦定这个位上必选这个点，其余的点乱选，异或和为 $0$。我们使用线性基，同时维护基上每个元素由哪些原来的 $b$ 异或得到，即可简单地查询。时间复杂度 $\Theta(n^3)$。

```cpp
void insert(int x, int S) {
	per(i, maxn - 1, 0) {
		if (!(x >> i & 1)) continue;
		if (!p[i]) {
			p[i] = x, q[i] = S;
			return;
		}
		x ^= p[i], S ^= q[i];
	}
}

int query(int x) {
	int S = 0;
	per(i, maxn - 1, 0) {
		if (!(x >> i & 1)) continue;
		if (!p[i]) return -1;
		x ^= p[i], S ^= q[i];
	}
	return S;
}

void fake_main() {
	n = read(), m = read();
	rep(i, 1, m) {
		int u = read() - 1, v = read() - 1;
		b[u] |= (1ll << v), b[v] |= (1ll << u);
	}
	rep(i, 0, n - 1) {
		rep(j, 0, maxn - 1) p[j] = q[j] = 0;
		rep(j, 0, n - 1) {
			if (i == j) continue;
			insert(b[j], 1ll << j);
		}
		int S = query(b[i]);
		if (!~S) return void (puts("No"));
		rep(j, 0, n - 1) if ((j == i) || (S >> j & 1)) ans[j] |= (1ll << i);
	}
	puts("Yes");
	rep(i, 0, n - 1) write(ans[i]), pc(' ');
}
```

---

## 作者：Double_Light (赞：0)

考虑高斯消元。

对于节点 $x$ 而言，$x$ 受到所有直接连边的节点影响。设这些节点为 $a_1,a_2,\dots,a_k$，则可列得方程 $a_1\oplus a_2\oplus\dots\oplus a_k=0$，由于共有 $n$ 个节点，所以就有 $n$ 个方程。此时直接高斯消元即可。

异或高斯消元的过程可以参照 [P10499 开关问题](https://www.luogu.com.cn/problem/P10499)。


```cpp
#include<iostream>
#define int long long
using namespace std;
int n,m;
int a[105][105],cnt;
int f;
int ans,Ans[100005];
signed main(){
	cin>>n>>m;
	f=1;
	ans=1;
	for(int i=1;i<=n+1;i++){
		for(int j=1;j<=n+1;j++){
			a[i][j]=0;
		}
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		a[u][v]++;
		a[v][u]++;
	}
	for(int i=1;i<=n;i++){
		int t=i;
		for(int j=i+1;j<=n;j++){
			if(a[j][i]>a[t][i])t=j;
		}
		swap(a[i],a[t]);
		if(a[i][i]==0)continue;
		for(int j=i+1;j<=n;j++){
			int x=a[j][i];
			for(int k=i;k<=n+1;k++){
				a[j][k]^=a[i][k]*x;
			}
		}
	}
	Ans[n]=a[n][n+1];
	if(a[n][n]==0){
		if(Ans[n]>0)f=0;
		else{
			Ans[n]=114514;
			cnt++;
		}
	}
	for(int i=n-1;i;i--){
		for(int j=i+1;j<=n;j++){
			a[i][n+1]^=a[i][j]*Ans[j];
		}
		Ans[i]=a[i][n+1];
		if(a[i][i]==0){
			if(Ans[i]>0)f=0;
			else{
				Ans[i]=114514+cnt;
				cnt++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(Ans[i]==0)f=0;
	}
	if(f)cout<<"Yes\n";
	else cout<<"No\n";
	if(f)for(int i=1;i<=n;i++)cout<<Ans[i]<<' ';
	return 0;
}
```

---

## 作者：denominator (赞：0)

[原题 in luogu](https://www.luogu.com.cn/problem/AT_abc366_g) / [原题 in atcoder](https://atcoder.jp/contests/abc366/tasks/abc366_g)

> 给图上的每个点赋一个 $1\sim2^{60}-1$ 的点权，使得对所有节点，其 xor 和为 $0$，或报告无解。
>
> $1\leq n\leq60$。

没看到 $n\leq60$，一直在想点权 $\mathcal O(1)$ 的方法，没想出来自闭了。挺水一道 G。

妈妈我不知道矩阵的基！

考虑最烦人的条件，就是点权不能为 $1$，不能拆位啊。

但是考虑点权上限是 $2^n-1$，自然有一种想法：每次钦定一个节点的权值为 $1$，再将节点的答案按位拼在一起（具体见代码）！

想想这么做的充要性，即每个位有解等价于原题有解：我们一定能找出一组解。同时，对于原题的一组合法解，考虑对于每个点 $i$，必然存在某个二进制位为 $1$，将所有数的这一位拆出来，即为上面情况在钦定 $i$ 的权为 $1$ 的情况。

随即枚举 $i$，将第 $i$ 位放在后面，进行 Gauss-Jordan 消元，就完了。时间复杂度 $\mathcal O(n^4)$，可以接受。

放个 code：


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 70;
typedef long long ll;
int n, m, a[N][N], mat[N][N], x[N];
ll w[N];
bool ok = true;
int main () {
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf ("%d%d", &u, &v);
		a[u][v] = a[v][u] = 1;
	}
	for (int p = 1; p <= n; p++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (p > j) {
					mat[i][j] = a[i][j];
				} else if (p < j) {
					mat[i][j - 1] = a[i][j];
				}
			}
			mat[i][n] = a[i][p];
		} // 构造矩阵以进行 Gauss 消元
		int nowid = 0;
		for (int i = 1; i < n; i++) {
			int cur = 0;
			for (int j = nowid + 1; j <= n; j++) {
				if (mat[j][i] == 1) {
					cur = j;
					break;
				}
			}
			if (cur == 0) {
				continue;
			}
			swap (mat[++nowid], mat[cur]);
			for (int j = nowid + 1; j <= n; j++) {
				if (mat[j][i] == 0) {
					continue;
				}
				for (int k = i; k <= n; k++) {
					mat[j][k] ^= mat[nowid][k];
				}
			}
		} // Gauss 消元板子
		for (int i = nowid + 1; i <= n; i++) {
			if (mat[i][n] == 1) {
				puts ("No");
				ok = false;
				break;
			}
		}
		if (!ok) {
			break;
		} // 判无解
		for (int i = 1; i < n; i++) {
			x[i] = -1;
		}
		for (int i = nowid; i >= 1; i--) {
			int cur = 0;
			for (int j = 1; j < n; j++) {
				if (x[j] == -1) {
					cur += mat[i][j];
				} else {
					mat[i][n] ^= mat[i][j] & x[j];
				}
			}
			if ((cur & 1) ^ mat[i][n]) {
				for (int j = 1; j < n; j++) {
					if (x[j] == -1 && mat[i][j] == 1) {
						if (--cur) {
							x[j] = 1;
						} else {
							x[j] = 0;
						}
					}
				}
			} else {
				for (int j = 1; j < n; j++) {
					if (x[j] == -1 && mat[i][j] == 1) {
						x[j] = 1;
					}
				}
			}
		}
		for (int i = 1; i < n; i++) {
			if (x[i] == -1) {
				x[i] = 0;
			}
		} // 求出一组解（使用一点技巧？）
		for (int i = 1; i <= n; i++) {
			if (i == p) {
				w[i] |= 1ll << (p - 1);
			} else if (i < p) {
				w[i] |= (ll) x[i] << (p - 1);
			} else {
				w[i] |= (ll) x[i - 1] << (p - 1);
			}
		} // 把解拼入答案
	}
	if (ok) {
		puts ("Yes");
		for (int i = 1; i <= n; i++) {
			printf ("%lld%c", w[i], " \n"[i == n]);
		}
	}
	return 0;
}
```

因为忘开 `long long` 没能在 CF 开始前打完（（（

---

