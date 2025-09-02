# [ABC108D] All Your Paths are Different Lengths

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc108/tasks/arc102_b

整数 $ L $ が与えられます。以下の条件を満たす有向グラフをひとつ構成してください。構成したグラフに多重辺が含まれていても構いません。 なお、条件を満たす有向グラフは必ず存在することが証明できます。

- 頂点数 $ N $ は $ 20 $ 以下で、すべての頂点には $ 1 $ 以上 $ N $ 以下の相異なる番号が付けられている
- 辺数 $ M $ は $ 60 $ 以下で、すべての辺には $ 0 $ 以上 $ 10^6 $ 以下の整数の長さが付けられている
- 全ての辺は番号の小さい方の頂点から大きい方の頂点に向かって向きづけられている。すなわち、$ 1,2,...,N $ はこのグラフの頂点の番号を適当なトポロジカル順序で並べてできる列である
- 頂点 $ 1 $ から頂点 $ N $ への異なるパスはちょうど $ L $ 個あり、それらの長さは $ 0 $ から $ L-1 $ までの相異なる整数である

ただし、パスの長さとは、そのパス上の辺の長さの和を表します。また、$ 2 $ つのパスが異なるとは、パス上の辺の集合が異なることを指します。

## 说明/提示

### 制約

- $ 2\ \leq\ L\ \leq\ 10^6 $
- $ L $ は整数である

### Sample Explanation 1

出力例のグラフには 頂点 $ 1 $ から $ N=8 $ への $ 4 $ 本のパスがあり、 - パス $ 1 $ → $ 2 $ → $ 3 $ → $ 4 $ → $ 8 $ の長さは $ 0 $ - パス $ 1 $ → $ 2 $ → $ 3 $ → $ 7 $ → $ 8 $ の長さは $ 1 $ - パス $ 1 $ → $ 2 $ → $ 6 $ → $ 7 $ → $ 8 $ の長さは $ 2 $ - パス $ 1 $ → $ 5 $ → $ 6 $ → $ 7 $ → $ 8 $ の長さは $ 3 $ となります。これ以外にも、正答として認められる出力があります。

## 样例 #1

### 输入

```
4```

### 输出

```
8 10
1 2 0
2 3 0
3 4 0
1 5 0
2 6 0
3 7 0
4 8 0
5 6 1
6 7 1
7 8 1```

## 样例 #2

### 输入

```
5```

### 输出

```
5 7
1 2 0
2 3 1
3 4 0
4 5 0
2 4 0
1 3 3
3 5 1```

# 题解

## 作者：zhylj (赞：7)

为了更好的阅读体验，你可以前往[我的博客](http://zhylj.cc/index.php/archives/17/)。

## 分析

考虑若 $L = 2^k - 1$，则我们显然可以建 $k + 1$ 个点，$i$ 号点到 $i + 1$ 号点连两条边，一条权值为 $0$，一条权值为 $2^{i-1}$.

接下来我们考虑一般的情况，考虑枚举路径长度的卡着 $L$ 最高的若干位，在第 $i$ 位处变为了 $0$（而 $L$ 在对应位的值是 $1$），那么从这位开始往下可以取遍 $[0,2^i)$ 中的整数，即连一条从 $i$ 号点到 $n$ 号点的，权值为 $L$ 抹去这一位以下的所有数后的值的边。

至多建 $3\lfloor \log_2 L\rfloor$ 条边，$\lfloor \log_2 L\rfloor + 1$ 个点，可以通过本题。

## 代码

```cpp
int main() { 
	int T = 1; //rd(T);
	while(T--) {
		int n, L; rd(L);
		for(n = 0; 1 << n <= L; ++n); --n;
		printf("%d %d\n", n + 1, 2 * n + __builtin_popcount(L) - 1);
		for(int i = 1; i <= n; ++i) {
			printf("%d %d %d\n", i, i + 1, 0);
			printf("%d %d %d\n", i, i + 1, 1 << (i - 1));
		}
		for(int i = 0; i < n; ++i) if((L >> i) & 1) {
			printf("%d %d %d\n", i + 1, n + 1, L & ~((1 << (i + 1)) - 1));
		}
	} return 0;
}
```

---

## 作者：Eaoci (赞：2)

[AT4361](https://www.luogu.com.cn/problem/AT4361)

先考虑 $n$ 个点全连 $0$，$i→i+1$ 连 $2^{i-1}$ 这样 $n$ 个点就可以表示 $[0,2^{n-1}-1)$ 之间的所有数。然后发现 $1 ∼ i$ 所有点能表示 $[0,2^{i-1}-1)$ 的所有数，故考虑把原数拆位，对于是 $1$ 的非最高位就向终点连一条高位之和的边，这样就可以是表示 $[$高位之和，高位之和加此位$)$ 的所有数，$\log$ 个点，$3\log$ 个边。

code：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
int u[100],v[100],w[100];
void add(int a,int b,int c){
	u[++m]=a;
	v[m]=b;
	w[m]=c;
}
int main(){
	cin>>n;
	int nn=20;
	for(int i=2;i<=nn;i++){
		add(i-1,i,0);
	}
	int lst=0,cnt=0;
	for(int i=21;i>=0;i--){
		if((1<<i)&n){
			for(int j=0;j<i;j++){
				add(j+1,j+2,(1<<j));
			}
			lst=i+1,cnt=(1<<i);break;
		}
	}
	for(int i=lst-2;i>=0;i--){
		if(n&(1<<i)){
			add(i+1,lst,cnt);
			cnt+=(1<<i);
		}
	}
	cout<<nn<<" "<<m<<"\n";
	for(int i=1;i<=m;i++){
		cout<<u[i]<<" "<<v[i]<<" "<<w[i]<<"\n";
	}
	return 0;
}
```


---

## 作者：xxr___ (赞：1)

首先考虑 $L = 2^n$ 的时候怎么做？

我们发现可以建立 $n$ 个点，且 $i → i + 1$ 连 $0$ 和 $2^{i - 1}$ 权值的边，这样就可以凑出 $[0,2^n)$ 了。

推广到一般的情况，与原来一样，我们设 $L$ 的二进制展开是 $d_1,d_2...d_k$ 满足 $L = \sum 2^{d_i}$ 且 $d_i < d_{i + 1}$。

我们让 $0 - d_k$ 都和特殊情况一样连边，此时可以满足 $[0,2^{d_k})$ 是可以填满的。

并且此时一共有 $2^{d_k}$ 种路径，为了获得 $L$ 条路径，我们把每个 $d_i$ 都向 $n$ 连边，每次连边可以贡献 $2^{d_i}$ 种路径，这样可以保证最后路径总数是可行的。

那么连边的边权该如何保证可行？

我们从小到大考虑，对于每个 $d_i$ 都让 $d_i → n$ 连边权是 $L - 2^{d_i}$ 的边权，并且修改此时的 $L ← L - 2^{d_i}$ 这样做的目的是为了填满前面没有填过的，和不填之前类似的操作填过的数。

一些细节：
1. 因为编号是从 $1$ 开始，所以要把每个点编号加一。
2. 最后 $d_k$ 的时候不要连边，不然路径数量就不是 $L$ 条了。

代码：
```cpp
#include<iostream>

const int N = 21;
int d[N];
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int L,cnt = 0,n = 0,m = 0;
	std::cin >> L;
	for(int j = 0;j <= 20; ++ j){
		if(L >> j & 1){
			d[++ cnt] = j;
			++ m;
		}
	}
	d[0] = 0;
	n = d[cnt] + 1,m += n * 2 - 3;
	std::cout << n << ' ' << m << '\n';
	for(int i = 1;i <= cnt; ++ i){
		for(int j = d[i - 1];j < d[i]; ++ j){
			std::cout << j + 1 << ' ' << j + 2 << ' ' << (1 << j) << '\n';
			std::cout << j + 1 << ' ' << j + 2 << ' ' << 0 << '\n';
		}
		if(i != cnt){
			std::cout << d[i] + 1 << ' ' << n << ' ' << (L - (1 << d[i])) << '\n';
			L -= 1 << d[i];
		}
	}
	return 0;
}
```

---

## 作者：xukehg (赞：1)

vp 时写了一个半小时，构造题是真恶心。

考虑一共只有 $20$ 个点，恰好有 $2^{19} \leq l < 2^{20}$，我们可以构建一个总长 $20$ 个点的链，恰好能覆盖 $[0,2 ^ {19} - 1]$，多了就只取一部分。但有一个问题：还剩一些数，但我们没点了。

~~某人就开始想用三进制甚至四进制了。~~

我们坚信二进制是正确的，考虑不加入新的点怎么做。注意到如果有 $2 ^ {c} - 1 \leq l < 2 ^ {c + 1} - 1$，我们只要加上一条长度为 $2 ^ {c} - 1$，剩下的子结构与之前相同。为了让编号小的连到编号大的，我们不妨将链的权值翻转，让权值大的离 $1$ 更近，我们就可以通过加边不断重复上述过程。边数最大为 $44$，绰绰有余。

[记录。](https://atcoder.jp/contests/arc102/submissions/61705073)

---

## 作者：hfjh (赞：1)

# [ABC108D] All Your Paths are Different Lengths 题解
## 题意

请你构造一个 DAG，$n \le20$ 是点数，$m\le60$ 是边数。

起点是 $1$，终点是 $n$，使得起点到终点刚好有 $L$ 条路径，并且路径长度从 $[0,L-1]$。

## 题解

一眼二进制，数据范围也提示二进制。

考虑构造这样的图，现在满足了 $[0,2^k -1]$，继续构造剩余，例如 $25$ 条路径考虑 $25 = 16 + 8 + 1$，最开始连完 $16$ 条剩余 $8$ 和 $1$，直接在中间节点连到终点，权值就是之前还没构造过最小的长度。

![](https://cdn.luogu.com.cn/upload/image_hosting/gscbsw3d.png)![](https://cdn.luogu.com.cn/upload/image_hosting/p7c09ibm.png)

## 代码
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
int g, qd;
int n, now, w, f[110], cn, cm;
struct node{
	int x, y, v;
};
vector <node> a;
void pre(){
	now = 1;
	while(now * g <= n + 1){
		now = now * g;
		++w;
	}
	now = now / 2, ++w;
	
	for(int i = 1, j = 1; i < w - 1; ++i, j = j * 2){
		a.push_back({i, i + 1, j});
		a.push_back({i, i + 1, 0}); 
	}
	a.push_back({w - 1, w, now});
	a.push_back({w - 1, w, 0}); 
	qd = now * 2;
	for(int i = w - 1, j = now; i >= 1; --i, j /= 2){
		if(n - qd >= (j - 1)){
			a.push_back({i, w, qd});
			qd = qd + j;
		} 
	}
}
void print(int x, int y, int z){
	cout<<x<<' '<<y<<' '<<z<<'\n';
}
void op(){
	cout<<w<<' '<<a.size()<<'\n'; 
	for(auto i : a){
		print(i.x, i.y, i.v);
	}
}
int main(){
	cin>>n;
	--n;
	g = 2;
	pre();
	op();
	return 0;
}
```

---

## 作者：Theresia (赞：0)

### 题目链接

[All Your Paths are Different Lengths](https://www.luogu.com.cn/problem/AT_arc102_b)

### 思路

我们先对输入的 $L$ 作二进制拆分，不妨设 $\displaystyle L = \sum_{i=1}^D 2^{d_i}$，其中 $d_1 < d_2 < \cdots < d_D$。

我们注意到，题目没有禁止我们创建重边。

那么，我们便可以建立 $D$ 个中间点，对于其中每个点 $i$，都向下一个点连接两条边，边权分别为 $0$ 和 $2^{i-1}$。

而对于每一个 $d_i$ 来说，为了满足边权能够取到每一个数，需要使第 $d_i + 1$ 个点向第 $n$ 个点再连一条边，边权为 $\displaystyle \sum_{j=i+1}^D 2^{d_j}$。

这样便可以满足条件，同时点数个数在 $3\left\lfloor\log_2(L)\right\rfloor$ 级别，不会超出限制。

### 参考代码

对于 $d_i$ 连边的边权处理直接由小到大从 $L$ 中扣除更为简便。

```cpp
// 谁不曾拥抱过一阵风 谁又曾拥有一段醒不过来的梦
int L=rd(),d[30],len;
int n,m;
void Input()
{
	for(int i=0;i<=20;i++)
	{
		if(L>>i&1)
		d[++len]=i-1,m++;
	}
	n=d[len]+2;
	m=m+n*2-3;
	wr(n,m);puts("");
	d[0]=-1;
	for(int i=1;i<=len;L-=(1<<d[i]+1),i++)
	{
		for(int j=d[i-1];j<d[i];j++)
		wr(j+2,j+3,0),puts(""),wr(j+2,j+3,1<<(j+1)),puts("");
		if(i==len)
		break;
		wr(d[i]+2,n,L-(1<<d[i]+1));puts("");
	}
}
void Solve()
{
	// Hello
}
void Output()
{
	// Hello
}
int main()
{
	Input();
	Solve();
	Output();
	return 0;
}
```

---

## 作者：Terac (赞：0)

你为了让路径数指数增长，自然想构造一条链，链上每条边都有一条重边，这样路径数就是 $2^{n-1}$ 的。

记 $n=\lfloor\log_2 n\rfloor+1$。对 $\forall i\in[1,n-1]$，连一条 $(i,i+1,0)$ 和一条 $(i,i+1,2^{n-i-1})$ 的边，这样就能构造出 $2^{n-1}$ 条路径，覆盖了 $[0,2^{n-1})$ 的路径长度。

剩下部分也很简单，对于 $i\in[0,n-2]$，若 $L$ 的第 $i$ 位为 $1$ 就连一条 $(1,n-i,lst)$ 的边，并让 $lst\gets lst+2^i$，初始 $lst=2^{n-1}$。注意到边数最多为 $3n$，可以通过。

---

