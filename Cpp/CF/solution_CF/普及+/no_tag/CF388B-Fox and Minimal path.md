# Fox and Minimal path

## 题目描述

Fox Ciel wants to write a task for a programming contest. The task is: "You are given a simple undirected graph with $ n $ vertexes. Each its edge has unit length. You should calculate the number of shortest paths between vertex 1 and vertex 2."

Same with some writers, she wants to make an example with some certain output: for example, her birthday or the number of her boyfriend. Can you help her to make a test case with answer equal exactly to $ k $ ?

## 说明/提示

In first example, there are 2 shortest paths: 1-3-2 and 1-4-2.

In second example, there are 9 shortest paths: 1-3-6-2, 1-3-7-2, 1-3-8-2, 1-4-6-2, 1-4-7-2, 1-4-8-2, 1-5-6-2, 1-5-7-2, 1-5-8-2.

## 样例 #1

### 输入

```
2```

### 输出

```
4
NNYY
NNYY
YYNN
YYNN```

## 样例 #2

### 输入

```
9```

### 输出

```
8
NNYYYNNN
NNNNNYYY
YNNNNYYY
YNNNNYYY
YNNNNYYY
NYYYYNNN
NYYYYNNN
NYYYYNNN```

## 样例 #3

### 输入

```
1```

### 输出

```
2
NY
YN```

# 题解

## 作者：XiangyuHu (赞：4)

### 题目大意

请你输出一张图，使得从 $1$ 号节点到 $2$ 号节点之间最短路条数为 $k$。

### 题目解析

看到这道题，立马反应过来，这是一道构造题。

很多构造题都可以用二进制解决，这题也不例外。

我们考虑先构造出 $k=2^m$ 的情况。那每过一轮乘 $2$ 就可以了。于是就有了如下的构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/vfi6bm9n.png)

其中，$1$ 号节点到 $2,3$ 号节点距离为 $1$，到 $4,5$ 号节点距离为 $2$，到 $6,7$ 号节点距离为 $4$，到 $8,9$ 号节点距离为 $8$ ……

这样就解决了 $k=2^m$ 的情况。~~为什么没有部分分~~

将 $k$ 进行二进制拆分，很多个这样的图拼接起来，就可以构造出 $O(\log^2k)$ 点数的图了。

但是，如果题目要求更苛刻一点，要求 $n\le130$ 怎么办呢？

这时，就要求 $O(\log n)$ 的点数了。我们思考一种更方便合并每个 $2^m$ 的构造。

我们可以额外再拉一条链，将这些有 $2^m$ 种走法的点“汇”到新增的一条链上。但是要注意一点，即使这个二进制位上为 $0$，也要在链上建点。如果只有二进制位为 $1$ 的点，就不满足最短路了。同理，可以发现每条由起点到终点的路径长度都一样，因为总是要往下走 $1$ 格，且走到最右边。

构造：

![](https://cdn.luogu.com.cn/upload/image_hosting/ujvezo1m.png)

注意到这里的编号与上个构造有一点不同，为了简化编码，同时为了直观的看到程序生成的图。（程序使用一层生成三个点）

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int k;
bool G[1010][1010];
void addEdge(int u, int v) {
	G[u][v] = G[v][u] = 1;
}
int main() {
	scanf("%d", &k);
	int used = 6;
	for (int i = 2, tmp = 2; tmp <= k; i++, tmp <<= 1) {
		addEdge(i * 3 + 1, i * 3 - 1); // 建 2^(i-1) 的方案数的点
		addEdge(i * 3 + 1, i * 3 - 2);
		addEdge(i * 3 + 2, i * 3 - 1);
		addEdge(i * 3 + 2, i * 3 - 2);
		addEdge(i * 3, i * 3 + 3); // 建额外链的点、边
		if (k & tmp) {
			addEdge(i * 3 + 3, i * 3 + 2); // 建从 2^(i-1) 汇方案数的边
		}
		used = i * 3 + 3;
	}
	addEdge(3, 4); addEdge(3, 5); // 建开始的两条边
	if (k & 1) {
		addEdge(5, 6); // 特殊处理之前没有处理的情况
	}
	addEdge(1, 3); // 连从 1 到 3 的边
	addEdge(2, used); // 将路径数转移到 2
	printf("%d\n", used);
	for (int i = 1; i <= used; i++) {
		for (int j = 1; j <= used; j++) {
			printf(G[i][j] ? "Y" : "N");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：TKXZ133 (赞：3)

[Fox and Minimal path](https://www.luogu.com.cn/problem/CF388B)

### 题目大意

构造一张无向图，使得从 $1$ 到 $2$ 的最短路数量为 $k$。

### 思路分析

我们首先可以发现当 $k = 2^t$ 时的构造方式：

![](https://user-images.githubusercontent.com/110758650/267942158-dae53430-cd0b-4004-ac9c-2050ebd39dcd.png)

其中只有 $O(\log k)$ 个点。

当 $k\not = 2^t$ 时，我们可以将 $k$ 二进制拆分，对于每一个二进制位重复上述操作，就可以得到：

![](https://user-images.githubusercontent.com/110758650/267942170-46e3f9c6-1152-4d60-81ef-96eb3847e9d8.png)

当然，为了保证最短路长度相同，少的部分需要用一条链补齐。

算一下发现点数为 $O(\log^2k)$，当 $k$ 达到极限数据 $2^{29}-1$ 时点数会超过 $1000$，无法通过。

我们发现，那些用链补齐的部分是相当浪费的，也就是说，我们可以将所有用于补齐的链合并成一条：

![](https://user-images.githubusercontent.com/110758650/267942178-37bf3e2b-61e6-487d-ad4d-1d16a2222831.png)

这样我们的点数虽然依然是 $O(\log^2 k)$ 的，但减少了一部分点，在极限数据时只需要 $900$ 个点，可以通过。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
 
using namespace std;
const int N = 2010, M = 50;
#define inf 0x3f3f3f3f
 
int n, k, len, tot = 3;
int G[N][N], a[M], need[M];
 
void add(int u, int v){
    G[u][v] = G[v][u] = 1;
}
 
void solve(int x){
    int num = tot;
    if (x == 0) {
        add(num, num + 1);
        add(num + 1, num + 2);
        add(num + 2, num + 3);
        tot += 3;
        if (x == len - 1) add(num + 3, 2);
        else add(num + 3, need[len - 3]);
        return ;
    }
    if (x == 1) {
        add(num, num + 1);
        add(num, num + 2);
        add(num + 1, num + 3);
        add(num + 2, num + 4);
        add(num + 3, num + 5);
        add(num + 4, num + 5);
        tot += 5;
        if (x == len - 1) add(num + 5, 2);
        else add(num + 5, need[len - 3]);
        return ;
    }
    add(num, num + 1);
    add(num, num + 2);
    tot += 2;
    for (int i = 1; i < x; i ++) {
        add(tot - 1, tot + 1);
        add(tot - 1, tot + 2);
        add(tot, tot + 1);
        add(tot, tot + 2);
        tot += 2;
    }
    add(tot - 1, tot + 1);
    add(tot, tot + 1);
    tot ++;
    add(tot, need[len - x - 1]);
}
 
int main(){
    cin >> k;
    while (k) {
        a[++ len] = (k & 1);
        k >>= 1;
    }
    for (int i = 1; i <= len; i ++) add(tot, tot + 1), tot ++;
    add(tot, 2);
    need[0] = 2;
    for (int i = 1; i <= len; i ++) need[len - i + 1] = i + 3;
    for (int i = 1; i <= len; i ++)
        if (a[i]) {
            add(1, ++ tot);
            solve(i - 1);
        }
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i ++) {
        for (int j = 1; j <= tot; j ++) 
            printf("%c", G[i][j] ? 'Y' : 'N');
        printf("\n");
    }    
    return 0;
}
```

---

## 作者：hexu2010 (赞：3)

# CF388B Fox and Minimal path 题解

## 题目大意
要求构造一个含有 $N(1\leqslant N\leqslant 1000)$ 个节点的简单无向图，使得从 $1$ 号节点到 $2$ 号节点恰有 $K$ 条最短路径（ $1\le K\le 10^9$ ）。输出你构造图的邻接矩阵表示。

## 解析

### step 1:建层连边

这道题要求我们构造一个图，使得从 $1$ 号节点到 $2$ 号节点恰有 $K$ 条最短路径。我们可以想到二进制拆分来做。我们联想到 Dijkstra ，将 $1$ 号节点看做是源点。如果将 $k$ 拆分成二进制的形式，那我们只需构造出距离源点有 $2^0$，$2^1$，$2^2$，……条最短路就可以了。

接下来的目标，就是想办法构造出距离源点为 $2^0$，$2^1$，$2^2$，…… 的节点。通过观察发现，这是等比数列，公比为 $2$ 。于是，我们可以分出 $s=log_2 k+1$ 层，每层有 $2$ 个节点，每层节点之间不相连，相邻两层之间都要连上边，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/inndqw4m.png)

但是，我们还要将源点放上去，也就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/ebwqsfsa.png)

于是，可以得出，源点到第 $i$ 行的节点有 $2^{i-1}$ 条最短路。然后，在考虑每个节点的编号问题。首先， $1$ 号和 $2$ 号已经被用掉了，所以从 $3$ 号开始考虑。从简单方便的方面去想，第 $i$ 层的节点分别是 $2i+1$ 和 $2i+2$ 。接着，再是连边的事情。刚才提到了，第 $i$ 层的节点分别是 $2i+1$ 和 $2i+2$ ，可以得出第 $i$ 层的节点分别是 $2i+3$ 和 $2i+4$ ，所以有这几条边：$(2i+1,2i+3)$，$(2i+1,2i+4)$，$(2i+2,2i+3)$，$(2i+2,2i+4)$。 

### 2.建链拉边

建好了几个点之后，就想办法把这些点连在一起。我们在旁边再拉一条链出来，那就是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/fowc5a8k.png)

为了方便研究，我们在点上标**源点到这个点的路径数**。

![](https://cdn.luogu.com.cn/upload/image_hosting/814kl5dx.png)

接下来就好办了。假设 $k=5=1+4=2^0+2^2$，那就把第 $1$ 层和第 $3$ 层的其中**一个**节点与链上对应的点连边即可，就像这样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/yf345fjp.png)

就达到了目的。接下来，还是考虑节点编号的问题。首先，之前已经用掉了 $2s+2$ 个点，那么这一条链就从 $2s+3$ 开始。注意，最后一个点的编号应该是 $2$ ，这里需要特判一下。

那么思路上大体就是这样了。

## 算法流程

![](https://cdn.luogu.com.cn/upload/image_hosting/q5az4jb5.png)

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s = 0, w = 1;
	char ch = getchar();
	for(; ch < '0' || ch > '9'; w *= (ch == '-') ? -1 : 1, ch = getchar());
	for(; ch >= '0' && ch <= '9'; s = 10 * s + ch - '0', ch = getchar());
	return s * w;
}
const int MAXN = 1005;
bool G[MAXN][MAXN];
void add(int u, int v){
	G[u][v] = G[v][u] = 1;
}
signed main(){
	int k = read(), s = log2(k);
	add(1, 3), add(1, 4);
	for(int i = 1; i <= s; i++){
		add(i * 2 + 1, i * 2 + 3);
		add(i * 2 + 1, i * 2 + 4);
		add(i * 2 + 2, i * 2 + 3);
		add(i * 2 + 2, i * 2 + 4);
	}
	for(int i = 1; i <= s; i++){
		add(2 * s + 4 + i, 2 * s + i + 5);
	}
	add(3 * s + 4, 2);
	for(int i = 0; i <= s; i++){
		if((k & (1 << i)) == 0) continue;
		if(i == s) add(2 * i + 4, 2);
		else add(2 * i + 4, 2 * s + i + 5);
	}
	cout << 3 * s + 4 << endl;
	for(int i = 1; i <= 3 * s + 4; i++){
		for(int j = 1; j <= 3 * s + 4; j++){
			cout << (G[i][j] ? "Y" : "N");
		}
		puts("");
	}
	return 0;
}
```

制作不易，顺手点个赞吧。

---

## 作者：Locix_Elaina_Celome (赞：2)

# [CF388B Fox and Minimal path](https://www.luogu.com.cn/problem/CF388B) 题解
## 题意

> 构造一个不超过 $1000$ 个节点的简单无向图，使得从 1 号节点到 2 号节点恰有 $k$ 条最短路径。


## 题解

在一条路径上，如果在一条边之间插入 $x$ 个并排点，则这条路径的走法 $\times x$。

这一点引发我们去思考进制拆分。

先考虑二进制。我们要凑出一个 $2^x$ 个走法的路径，只需要把 $2x$ 个点两两一组放在路径上就可以了。我们对于 $x\in [0,29]$ 的所有 $x$ 都构造一条这样的路径，再根据需要进行取舍。因为限制要最短路才参与计数，所以对于一条长 $x$ 的陆路径要额外加入 $29-x$ 个点来凑长度。

发现这样总点数会炸。

发现只需要增大进制即可。这里使用十进制。如果想卡一下，可以把 $10$ 拆为 $2\times 5$。这样的话点数大概在 $300$ 左右。

## 代码

```cpp



#include<bits/stdc++.h>
#define N 1005
#define LL long long
#define int LL
#define lb(i) ((i)&(-i))
#ifdef int
constexpr int INF=11451541919;
#else
constexpr int INF=1e18;
#endif
using namespace std;
template<typename T>T Max(T x,T y){return (x<y?y:x);}
template<typename T>T Min(T x,T y){return (x<y?x:y);}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int n,m;
int mp[N][N];
int tot=2;
void add(int x,int y){
	mp[x][y]=mp[y][x]=1;
}
#undef int
int main(){
#define int LL
	read(m);
	n=1000;
	#define TTT 9
	for(int i=0,nw=1;i<=TTT;i++,nw*=10){
		int x=(m/nw)%10;
		if(x==0)continue;
		for(int j=1;j<=i;j++){
			if(j==1){
				for(int k=1;k<=5;k++){
					add(1,tot+k);
					add(tot+k,tot+6);
					add(tot+k,tot+7);
				}
			}
			else {
				for(int k=1;k<=5;k++){
					add(tot-1,tot+k);
					add(tot,tot+k);
					add(tot+k,tot+6);
					add(tot+k,tot+7);
				}
			}
			tot+=7;
		}
		int nxt=tot+x+1;
		if(i==0){
			for(int j=1;j<=x;j++){
				add(1,tot+j);
				add(tot+j,nxt);
			}
		}
		else{
			for(int j=1;j<=x;j++){
				add(tot-1,tot+j);
				add(tot,tot+j);
				add(tot+j,nxt);
			}
		}
		tot=nxt;
		for(int j=i+1+1;j<=TTT+1;j++){
			add(tot,tot+1);
			add(tot+1,tot+2);
			tot+=2;
		}
		add(tot,2);
	}
	write(n);
	putchar('\n');
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)putchar(mp[i][j]?'Y':'N');
		putchar('\n');
	}
	return 0;
}

```

---

## 作者：Kirisame_Marisa_ (赞：2)

考虑构造如下图所示的一张图：
![](https://cdn.luogu.com.cn/upload/image_hosting/24wu6ojw.png)

通过手玩可以发现：点$1$到点$s_i$的最短路长度为$2i$，路径数为$2^{i-1}$。

这样，如果我们需要得到恰好$k$条$1\rightarrow 2$的路径，只需要对$k$进行二进制分解，将对应的$s_i$向$2$连边。现在就需要让我们连出的路径等长。

考虑类似右半边，构造一条长链。这个时候，每次我们不直接将$s_i$与$2$相连，而是退而求其次，令最短路长为$d$，将$s_i$与链上与$2$的距离等于$d-2i$的点相连（如下图）。
![](https://cdn.luogu.com.cn/upload/image_hosting/ui2r9yi0.png)

可以证明这样补全后得到的$k$条路径一定等长，且一定是最短路。

这个时候如果多出了一些$s_i$要怎么办呢？既然有`Special Judge`，而且这些多的部分一定不能直接到达右侧，所以它们对最短路长度没有影响，留在那里就可以了。

以及注意输出麻烦人的邻接矩阵。

---

## 作者：Imiya (赞：2)

![](https://cdn.luogu.com.cn/upload/image_hosting/j0gl5tgi.png)

对于这个图，为了保证最短路长度不变，每一层的点指向下一层，而每一层中的任意点到下一层有两种走法，那么根据乘法原理，从 $1$ 到 $2$ 的最短路数量就是 $2^3=8$ 种。可以推广，若 $k=2^h$，按照上图的样式建 $h$ 层（下文统称为若干层的图）即是答案。

发现可以将 $k$ 二进制拆分。

![](https://cdn.luogu.com.cn/upload/image_hosting/fkcq7nbi.png)

举个例子，$k=12$ 时，可以将 $k$ 分成 $8+4=2^3+2^2$，根据加法原理，答案可以是一个 $4$ 种走法的图和一个 $8$ 种走法的图并列，与 $1,2$ 相连。套用上面的结论就是一个二层的图和一个三层的图。但由于层数不同所以路的长度也不同，所以需要在二层的图下补一层只有一个点，使其层数与三层的图相同且不影响路径数量。

这个做法难以通过此题，图的点数在 $\frac 3 2\log^2 n$ 左右。

考虑优化，如下图 $k=13$，发现将层数补齐用了不少点，可以把用于补层数的点合并，在下图中就是将 $16$ 和 $13$ 合为一点，这样点数就只有 $\log^2 n+\log n$，能够通过此题。

![](https://cdn.luogu.com.cn/upload/image_hosting/h8jsetcd.png)

还可以进一步优化。上图中的 $9,10,11,12$ 号点和 $3,4,6,7$ 号点完全相同，因此可以将两部分合并，形成下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/zehgwvlk.png)

对于更复杂的例子也可以使用这种方法简化，如 $k=27=(11011)_2$ 时，就是在第 $0,1,3$ 层合并，如下图。
 
![](https://cdn.luogu.com.cn/upload/image_hosting/ubr5i8qh.png)

这样一来，点的数量就是 $3\times\lfloor\log k\rfloor+2$，妥妥能过。

代码

```cpp
#include<iostream>
using namespace std;
const int N=1000;
int k,a[N],b[N],c[N],t=2,h=30;
bool g[N][N];
int main(){
	cin>>k;	
	if(k==1){
		printf("2\nNY\nYN");
		return 0;
	}
	for(;!((1<<h)&k);h--);//求图的层数
	for(int i=1;i<=h;i++)a[i]=++t;//按优先从上到下，其次从右到左的顺序对每个点编号
	for(int i=1;i<=h;i++)b[i]=++t;
	for(int i=1;i<=h;i++)c[i]=++t;
	g[a[1]][1]=g[1][a[1]]=true;//对1,2点连别
	g[b[1]][1]=g[1][b[1]]=true;
	if(k&1)g[c[1]][1]=g[1][c[1]]=true;
	g[a[h]][2]=g[2][a[h]]=true;
	g[b[h]][2]=g[2][b[h]]=true;
	g[c[h]][2]=g[2][c[h]]=true;
	for(int i=1;i<h;i++){
		g[a[i]][a[i+1]]=g[b[i]][b[i+1]]=g[c[i]][c[i+1]]=true;//每一列从上到下连边
		g[a[i+1]][a[i]]=g[b[i+1]][b[i]]=g[c[i+1]][c[i]]=true;
		g[a[i]][b[i+1]]=g[b[i]][a[i+1]]=true;//右边两列交叉连别
		g[b[i+1]][a[i]]=g[a[i+1]][b[i]]=true;
		if(k&(1<<i))g[c[i+1]][a[i]]=g[a[i]][c[i+1]]=g[c[i+1]][b[i]]=g[b[i]][c[i+1]]=true;//上文中的合并
	}
	cout<<t<<endl;
	for(int i=1;i<=t;i++){
		for(int j=1;j<=t;j++)printf("%c",g[i][j]?'Y':'N');
		putchar('\n');
	}
	return 0;
}
		
```

------------
update：新加了一个 $\log^2 n$ 的优化

---

## 作者：木木！ (赞：2)

这里发一个比较劣的构造方法（点数 $\Theta(\log^2 n)$），顺便 orz 楼上那个点数 $\Theta(\log n)$ 的 dalao。

我看完题目之后第一个想到的图是这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/na8j2k9q.png)

显然，将 $k$ 个这样的链节拼起来就可以构造一个最短路个数为 $2^k$ 的结点了，然后连向 2 就可以了……吗？

定义链节的宽度为它在一个链节中所并列的结点个数，很明显，如果每条链节宽度为 $w$（如上图为 2），我们需要 $\Theta(\log_w n)$ 个链，每个链要 $\Theta(w\times\log_w n)$ 长，所以总结点需求是 $\Theta(w\times \log_w^2x)$ 的。

经计算，如果每条链节宽度为 2，处理 `536870911` 的时候，结点需求可以达到 1570 左右，显然不能容忍。

解决方式很简单：增加链节宽度。经过计算，只需要将链节宽度增加为 4 就可以将开销降到 1000 以下。

关于链节宽度在什么时候最小，可以这么计算：

$$w\times \log_w^2x=\frac{w}{\ln^2w}\times \ln^2x$$

然后计算 $\frac{w}{\ln^2w}$ 的最小值就好了，经计算，在 8 的时候取到最小。

具体实现很简单不赘述，这里给出的是链节宽度为 4 的版本（4 能过就没想写 8）：

```cpp
#include <cstdio>
using namespace std;

#define rn 4

int ch[1005][1005];
int top = 2;

int buildroad(int x,int lev)
{
	for(int i=1; i<=rn; ++i) ++top, ch[1][top] = ch[top][1] = 1;
	for(int k=1; k<=x; ++k)
	{
		for(int i=1; i<=rn; ++i)
		{
			for(int j=1; j<=rn; ++j)
			{
				ch[top-i+1][top+j] = ch[top+j][top-i+1] = i;
			}
		}
		top += rn;
	}
	for(int k=x+1; k<=lev; ++k)
	{
		for(int i=1; i<=rn; ++i)
		{
			ch[top-i+1][top+i] = ch[top+i][top-i+1] = 1;
		}
		top += rn;
	}
	return top;
}

int main()
{
	int k;
	scanf("%d",&k);

	const int lev = (31-__builtin_clz(k))/2;
	for(int i=0; k; ++i,k>>=2)
	{
		if(k&3)
		{
			int x = buildroad(i,lev);
			if(k&1) ch[x][2] = ch[2][x] = 1;
			if(k&2) ch[x-1][2] = ch[2][x-1] = ch[x-2][2] = ch[2][x-2] = 1;
		}
	}

	printf("%d\n",top);
	for(int i=1; i<=top; ++i)
	{
		for(int j=1; j<=top; ++j)
		{
			putchar(ch[i][j] ? 'Y' : 'N');
		}
		putchar('\n');
	}
}
```

---

## 作者：RiceFruit (赞：1)

## 题目大意

请你构造一张图，使得其中的 $1$ 号点和 $2$ 号点之间共有 $K(K\le 10^9) $ 条最短路。

## 主题思路

这道题是一道显然的构造题，看到 $K$ 这么大，便想到了二进制。于是我们考虑先构造一张图，使得 $1$ 号点到 $i\times 2$ 点共有 $2^{i-2}$ 条最短路。

对了，给大家推荐一个好用的[网站](https://csacademy.com/app/graph_editor/)，遇到图论题可以在上面作图，很方便。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/cu9eusqf.png)

如此延伸下去，这样即可满足上面所说的条件。

接下来我们将 $K$ 二进制拆分。如果它某一位为 $1$，则从这一位对应的节点连出一条链。

具体过程如图：

设这是我们开始建好的图，且 $K=5$。

![](https://cdn.luogu.com.cn/upload/image_hosting/nlimumlz.png)

因为 $K=5=2^0+2^2$。

我们先将 $2^0$ 对应的节点( $4$ 号节点)拉出来一条链，连到 $9$ 号节点，因为 $1$ 到 $4$ 号节点之间共有共有 $2^0$ 条最短路。

![](https://cdn.luogu.com.cn/upload/image_hosting/jplrgofb.png)

再将 $2^2$ 对应的节点（ $8$ 号节点）拉出来一条链，连到 $10$ 号节点，因为 $1$ 到 $8$ 号节点之间共有 $2^2$ 条最短路。

![](https://cdn.luogu.com.cn/upload/image_hosting/cf2kqgu2.png)

最后我们把拉出来的链合并到一起，并连接到 $2$ 号节点，即可完成。

![](https://cdn.luogu.com.cn/upload/image_hosting/bzdzl8xa.png)

## 算法分析

其实我们开始构造出一张从 $1$ 号点到 $i\times 2$ 点共有 $2^{i-2}$ 条最短路的图就是为了进行后面的拉链过程，而链只有一条，相当于从 $2$ 的次方中选择一些，使其变成 $K$，这就是先讲 $K$ 二进制拆分，然后选择即可。于是，这道题就解决了！

## 代码

本人代码写的有点丑，希望大家不要介意。

```cpp

#include<bits/stdc++.h>
using namespace std;
#define R register
#define ri register int
void swap(int &x,int &y){int t=x;x=y;y=t;}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
const int N=3000;
inline int read();
int k;
int n;
int s[N][N];
void add(int u,int v){
	s[u][v]=1;
	s[v][u]=1;
	return;
}
vector<int>use;
bool b[N];
signed main(){
	ios_base::sync_with_stdio(0);
	k=read();
	int x=1,cnt=0;
	while(x*2<=k){
		x*=2;
		cnt++;
	}
	add(1,3);add(1,4);//先构造起点 
	int nowu=3,nowv=4;
	for(int i=1;i<=cnt;i++){
		add(nowu,nowu+2);
		add(nowv,nowv+2);
		add(nowu,nowu+3);
		add(nowv,nowv+1);//构造开始的图 
		nowu+=2;
		nowv+=2;
	}
	for(int i=0;i<=cnt;i++){//二进制拆分 
		if(k&(1<<i)){
			use.push_back(i+2);
			b[i+2]=1;
		}
	}
	add(use[0]*2,++nowv);
	if(use.size()>1)
	for(ri i=use[0]+1;i<=use[use.size()-1];i++){//将链连起来
		int u1=nowv,u2=nowv+1;
		add(u1,u2);
		nowv++;
		if(b[i]){
			add(nowv,i*2);
		}
	}
	add(nowv,2);//将链尾和2号点相连
	cout<<nowv<<'\n';
	for(int i=1;i<=nowv;i++){
		for(int j=1;j<=nowv;j++){
			if(s[i][j])cout<<'Y';
			else cout<<'N';
		}
		cout<<'\n';
	}
	return 0;
}
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x;}
```

---

## 作者：Milmon (赞：0)

[Milmon Page 链接：https://molmin.github.io/problem?id=32#solution](https://molmin.github.io/problem?id=32#solution)

首先容易构造 $k=2^x$ 的情况，如图：

![](https://molmin.github.io/problem/32/1.png)

用数学归纳法证明照这样构造最短路数量必然是 $2^x$。

- 当 $x=0$ 时，显然只可以从点 $1$ 直接到达点 $2$；

- 当 $x>0$ 时，必然先要到达点 $2x+1$ 或点 $2x+2$，各有 $2^{x-1}$ 条最短路。而从这两个点都可以到达点 $2$，共有 $2^x$ 条最短路。

略微改造一下，就变成了：

![](https://molmin.github.io/problem/32/2.png)

对 $k$ 进行二进制拆分处理即可。

[Code 链接：https://molmin.github.io/problem?id=32#code](https://molmin.github.io/problem?id=32#code)

---

