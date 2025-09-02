# Great Grids

## 题目描述

An $ n \times m $ grid of characters is called great if it satisfies these three conditions:

- Each character is either 'A', 'B', or 'C'.
- Every $ 2 \times 2 $ contiguous subgrid contains all three different letters.
- Any two cells that share a common edge contain different letters.

Let $ (x,y) $ denote the cell in the $ x $ -th row from the top and $ y $ -th column from the left.

You want to construct a great grid that satisfies $ k $ constraints. Each constraint consists of two cells, $ (x_{i,1},y_{i,1}) $ and $ (x_{i,2},y_{i,2}) $ , that share exactly one corner. You want your great grid to have the same letter in cells $ (x_{i,1},y_{i,1}) $ and $ (x_{i,2},y_{i,2}) $ .

Determine whether there exists a great grid satisfying all the constraints.

## 说明/提示

In the first test case, the following great grid satisfies all the constraints:

BABCCBCAACABIn the second test case, the two constraints imply that cells $ (1,1) $ and $ (2,2) $ have the same letter and cells $ (1,2) $ and $ (2,1) $ have the same letter, which makes it impossible for the only $ 2 \times 2 $ subgrid to contain all three different letters.

## 样例 #1

### 输入

```
4
3 4 4
1 1 2 2
2 1 3 2
1 4 2 3
2 3 3 2
2 7 2
1 1 2 2
1 2 2 1
8 5 4
1 2 2 1
1 5 2 4
7 1 8 2
7 4 8 5
8 5 4
1 2 2 1
1 5 2 4
7 1 8 2
7 5 8 4```

### 输出

```
YES
NO
YES
NO```

# 题解

## 作者：mod998244353 (赞：21)

有一个套路是，只要确定第一行和第一列内填的字母，你就可以确定整个矩阵。

所以有个自然的想法是把矩阵中格子的关系转换为第一行和第一列内格子的关系。

假设我们不填字母，改填数字 $0,1,2$，来观察一下每个 $2\times 2$ 子矩阵的性质。

不妨设左上角为 $0$ ，有如下四种情况：

$$\begin{bmatrix}0&1\\2&0\end{bmatrix}\begin{bmatrix}0&2\\1&0\end{bmatrix}\begin{bmatrix}0&2\\2&1\end{bmatrix}\begin{bmatrix}0&1\\1&2\end{bmatrix}$$

瞪眼看这四个矩阵，发现对于一个合法的矩阵 $\begin{bmatrix}a&b\\c&d\end{bmatrix}$，满足：

$$b+c\equiv a+d\pmod 3$$

$c-a\equiv d-b\pmod 3$，即相邻两行的数之差相同，$b-a\equiv d-c\pmod 3$，即相邻两列的数之差相同

这两个结论显然对整个矩阵也成立。

设 $(i,j)$ 的权值为 $a_{i,j},c_{i}=a_{i+1,j}-a_{i,j},d_i=a_{i,j+1}-a_{i,j}$。

不妨设 $a_{1,1}=0$，这个矩阵只和 $c,d$ 有关。

而且由于相邻的数不相等，所以 $c_i,d_i$ 的取值只有 $1,2$。

现在我们来看限制，限制有两种：

1. 给定 $(x,y)$，要求 $a_{x,y}=a_{x+1,y+1}$
2. 给定 $(x,y)$，要求 $a_{x,y+1}=a_{x+1,y}$

考虑分析子矩阵 $\begin{bmatrix}a_{x,y}&a_{x,y+1}\\a_{x+1,y}&a_{x+1,y+1}\end{bmatrix}$：

对于第一种限制类型，$a_{x,y},a_{x+1,y},a_{x,y+1}$ 两两不相等，所以 $a_{x,y+1}-a_{x,y}\not\equiv a_{x+1,y}-a_{x,y}\pmod3$，即 $d_y\neq c_x$

对于第二种限制类型，$a_{x+1,y}=a_{x,y+1}$，所以 $a_{x,y+1}-a_{x,y}\equiv a_{x+1,y}-a_{x,y}\pmod3$，即 $d_y=c_x$

那么我们就直接 $c_x$ 向 $d_y$ 连边权为 $w$ 的边（$w=0$ 表示 $c_x=d_y$，$w=1$ 表示 $c_x\neq d_y$）。

因为 $c_i,d_i$ 的取值只有 $1,2$，用类似二分图染色的方法就可以判断是否有解了。

时间复杂度为 $O(n+m+k)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=200005;
inline int read() {
	static int x=0,c=getchar(),f=1;
	for(f=1; c<=47||c>=58; c=getchar())f=f&&c^45;
	for(x=0; c>=48&&c<=57; c=getchar())x=(x<<3)+(x<<1)+(c&15);
	return f?x:-x;
}
vector<pair<int,int>>vec[MAXN];
int n,m,k,col[MAXN],ans;
void dfs(int u,int c) {
	if(col[u]!=-1) {
		if(col[u]^c) ans=0;
		return;
	}
	col[u]=c;
	for(pair<int,int>tmp:vec[u])
		dfs(tmp.first,tmp.second^c);
}
inline void solve() {
	n=read(),m=read(),k=read();
	for(int i=1,x,y,xx,yy,u,v,w; i<=k; ++i) {
		x=read(),y=read(),xx=read(),yy=read();
		u=min(x,xx),v=n-1+min(y,yy),w=x+y!=xx+yy;
		vec[u].push_back(make_pair(v,w)),vec[v].push_back(make_pair(u,w));
	}
	ans=1;
	for(int i=1; i<=n+m-2; ++i) col[i]=-1;
	for(int i=1; i<=n+m-2&&ans; ++i)
		if(col[i]==-1)
			dfs(i,0);
	printf(ans?"YES\n":"NO\n");
	for(int i=1; i<=n+m-2; ++i)vec[i].clear();
}
int main() {
	int t=read();
	while(t--)solve();
	return 0;
} 
```

---

## 作者：小木虫 (赞：9)

### Preface
这题是一道相当好的判定类题目。  
### Problem  
给你一个 $n\times m$ 的网格，每个格子里可以填 $\text{a,b,c}$ 三种字母中的一个。定义一个 $n\times m$ 的网格是好的当且仅当相邻（有相同边缘）的两个格子填的字母是不同的并且对于其中任意的 $2\times 2$ 子网格包含 **恰好** 三种字母。 

现在我们钦定了 $k$ 对格子，第 $i$ 对为 $(x_{i_1},y_{i_1})$ 和 $(x_{i_2},y_{i_2})$，其中保证每对的格子有且仅有一个公共顶点。  

现在问你，有没有一种方案，使得有一个好的网格满足所有 $k$ 对条件。  

### Solution  
我们发现这道题的限制是非常紧的，我们先从题目要求的 $2\times 2$ 子网格开始入手。  
然后，我们发现，满足条件的 $2\times 2$ 子网格只能是这两种情况下的一种（同构算一种）。  
$$\begin {bmatrix} {}a \ b\\c \ a\\\end{bmatrix}=0$$  
$$\begin {bmatrix} {}b \ a\\a \ c\\\end{bmatrix}=1$$  
显然，对于所有 $n\times m$ 网格矩阵中的 $2\times 2$ 子矩阵都应该满足这两者之一，记录一个 $2\times 2$ 子矩阵的坐标为其左上角坐标，将其缩进左上角，则我们会获得一个 $(n-1)\times (m-1)$ 的新 01 矩阵。  


容易发现的是，对于一个这样的 $2\times 2$ 矩阵，若我们确定了其中三个元素，则矩阵的第四个元素就会确定，而要是我们确定了两个元素，则矩阵可以满足两种可能，即上面的两种形态都是可能的。  

然后我们发现一个很重要的结论，不考虑限制，即对于第一行的所有 $2\times 2$ 矩阵，其形态可以映射成任意 01 串。  

什么意思呢？  
假如我们的第一个子矩阵为： 
$$
\begin{bmatrix}{}
a \ b\\
c \ a\\
\end{bmatrix}
$$ 
由于对于同一行的下一个子矩阵只贡献了两个元素，所以下一个矩阵两种形态都是可能的，即可能变为：  
$$
\begin{bmatrix}{}
a \ b \ a\\
c \ a \ c\\
\end{bmatrix}
$$ 
或  
$$
\begin{bmatrix}{}
a \ b \ c\\
c \ a \ b\\
\end{bmatrix}
$$  
再往后拓展也是同理的。  

然后我们考虑向下一行拓展，还是这个矩阵：  
$$
\begin{bmatrix}{}
a \ b \ c\\
c \ a \ b\\
? \ ? \ ?\\
\end{bmatrix}
$$  
第三行第一个字母显然是不确定的，我们任意钦定一个，显然有两种选择，我们随便填一个。  
$$
\begin{bmatrix}{}
a \ b \ c\\
c \ a \ b\\
a \ ? \ ?\\
\end{bmatrix}
$$  
然后我们发现一个事情，这一行剩下的所有 $2\times 2$ 矩阵都确定了，因为递推后每一个子矩阵都已经确定了三个元素了。  

我们填第一个元素的两种选择代表了两种矩阵形态，容易发现的是，这样生成的下一行的矩阵形态所映射出的 01 串等于上一行或恰好是上一行的位异或（每一位都相反），手推一下就明白了。  

那么我们便有一个结论：  
第一行的矩阵形态映射出的 01 串是任意的，从第二行开始，每一行的映射 01 串都是前一行的映射 01 串本身或位异或。  

这个性质是很强的，我们开始考虑那 $k$ 对限制。  
显然，每一对限制规定的是一个位置矩阵的形态，映射到 01 串上就是 0/1。  
那现在相当于我们已经确定了这个 01 矩阵的若干元素。  
我们来思考一下这个性质的本质是什么。  

显然，这相当于每一行的 01 串都是同构的，即元素与元素之间的相等关系是一致的，所以若我们只关心相等关系的话不同行内相同位置的元素实际上是等价的。  
所以我们把 $n-1$ 行的 01 矩阵和限制全部压进一行，维护元素与元素之间的相等关系，然后判断是否矛盾。  
我们需要一个同时可以维护元素之间不同和相同条件的数据结构，扩展域并查集是可以满足我们的需求的，简单来说就是对于每个元素拆出两个点，一个点代表和这个元素相同，另一个代表不同，最后若相同和不同在同一个集合内则条件矛盾，然后这个问题就被解决了，复杂度 $O(k\log k+m)$。  

code：  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=4e3+10;
int T,n,m,k,a,b,c,d,fa[N*2];;
struct req{int x,y,dir;}q[N];
bool cmp(req a,req b){return a.x<b.x;}
int find(int x){
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);y=find(y);
	fa[y]=x;
}
void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=2*m;i++)
		fa[i]=i;
	for(int i=1;i<=k;i++){
		cin>>a>>b>>c>>d;
		if(c==a+1&&d==b+1)q[i].x=a,q[i].y=b,q[i].dir=1;
		else q[i].x=a,q[i].y=d,q[i].dir=-1;
	}sort(q+1,q+k+1,cmp);
	for(int i=1;i<=k;i++){
		if(q[i].x==q[i-1].x){
			if(q[i].dir==q[i-1].dir){
				merge(q[i].y,q[i-1].y);
				merge(q[i].y+m-1,q[i-1].y+m-1);
			}else{
				merge(q[i].y,q[i-1].y+m-1);
				merge(q[i].y+m-1,q[i-1].y);
			}
		}
	}
	for(int i=1;i<=m-1;i++){
		if(find(i)==find(i+m-1)){
			cout<<"NO\n";
			return ;
		}
	}
	cout<<"YES\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
```


---

## 作者：Kidding_Ma (赞：4)

对每个 $2\times 2$ 分析，因为每个 $2\times 2$ 必须有三个字母，猜想存在某种性质，如：

```txt
BA
CB
```

$a_{1,1}=B,a_{1,2}=A,a_{2,1}=C,a_{2,2}=B$


$a_{1,1}-a_{1,2}\equiv a_{2,1}-a_{2,2}\pmod 3$

$a_{1,1}-a_{2,1}\equiv a_{1,2}-a_{2,2}\pmod 3$

并且每两相邻的数差值只会是 $1,2\pmod 3$，所以就是给每行每列分配 $1$ 或 $2$，若右上角和左下角相同那么行列分配的 $1,2$ 相同，若左上角和右下角相同那么行列分配的 $1,2$ 不同，那么可以使用并查集维护。

Code

```cpp
#include "bits/stdc++.h"

using namespace std;
using i64 = long long;

struct UnionFind {
    int n;
    vector<int> f;
    UnionFind(const int &n = 0) : n(n), f(n) { 
        iota(f.begin(), f.end(), 0); 
    }
    int get(int x) {
    	while (x != f[x]) {
      	    x = f[x] = f[f[x]];
    	}
    	return x;
    }
    bool unite(int x, int y) {
    	x = get(x), y = get(y);
    	if (x != y) {
      	    f[y] = x;
      	    return 1;
    	}
    	return 0;
    }
    bool united(int x, int y) {
    	return get(x) == get(y);
    }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    const int N = n + m;
    UnionFind f(N + N);

    for (int i = 0; i < k; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        x1--, y1--, x2--, y2--;
        if (y2 == y1 + 1) {
            f.unite(x2, y2 + n + N);
            f.unite(x2 + N, y2 + n);
        } else {
            f.unite(x2, y1 + n);
            f.unite(x2 + N, y1 + n + N);
        }
    }

    for (int i = 0; i < n + m; i++) {
        if (f.united(i, i + N)) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
```

---

## 作者：do_it_tomorrow (赞：3)

容易发现，确定了 $(x-1,y-1),(x-1,y),(x,y-1)$ 之后 $(x,y)$ 就是一定的了。

于是假设处理了边边然后打表发现有一些奇异的规律：

![](https://cdn.luogu.com.cn/upload/image_hosting/2alfnxjn.png)

上图为 pb 大佬亲笔书写。

注意到如果把 $A,B,C$ 看成 $0,1,2$ 那么行与行之间就是在模 $3$ 意义下增加了一个常数，列与列之间也是同理。

我们不妨设 $(1,1)$ 这个位置为 $0$，第 $i$ 行与第 $1$ 行相差 $a_i$，第 $j$ 列与第 $1$ 列相差 $b_i$。

所以我们只需要确定 $a,b$ 数组，那么整个方阵就确定了。

对于题目给出的限制无非就是类似于 $a_i-a_{i-1}=b_{j}-b_{j+1}$ 或者 $a_i-a_{i-1}=b_{j}-b_{j-1}$。

因为都是连续的，那么我们不妨维护 $A_i=a_{i}-a_{i-1}$ 和 $B_{i}=b_i-b_{i-1}$，最后用并查集 xjb 维护一下就行了。

---

## 作者：hyman00 (赞：2)

## CF1844E 题解

小清新思维题

考虑把相邻的四个位置拿出来，有两种情况：
$$
 \begin{bmatrix} x & y \\ y & z \end{bmatrix} , \begin{bmatrix} x & y \\ z & x \end{bmatrix}
$$
其中 $x,y,z$ 是不同字母，记它们分别是 0 状态和 1 状态

把原矩阵的 $(n-1)\times(m-1)$ 个状态写出来，这样原问题转化为有若干个位置状态确定，你要填满剩下的，使得这是一个**合法**的矩阵。

下面分析**合法**的条件：

把相邻四个状态写出来，可以发现类似
$$
 \begin{bmatrix} 0 & 0 \\ 0 & 1 \end{bmatrix} , \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix} 
$$
这样，的是**不合法**的。

即
$$
 \begin{bmatrix} a & b \\ c & d \end{bmatrix} 
$$
要满足 $a+b+c+d\equiv 0\pmod 2$。

这时就是一个套路题了，我们对每行每列建一个节点。

如果确定 $(i,j)$ 位置填 $t$，就从第 $i$ 行向第 $j$ 列连一条边权为 $t$ 的边。

最后跑一下是否有奇环即可。

简单证明下为什么是对的：

前面的可以推广到任意两行两列 $a_{x_1,y_1}+a_{x_1,y_2}+a_{x_2,y_1}+a_{x_2,y_2}=0$（模 2 不写了）

假如有 $(r_x,c_y,t_1),(c_y,r_z,t_2),(r_z,c_w,t_3)$ 这三条边，则一定有 $a_{x,w}=t_1+t_2+t_3$。

这样可以得到 $a_{x,y}=\begin{cases}\text{0 or 1}&\text{not connexted}\\dist(r_x,c_y)&\text{connected}\end{cases}$，显然没有奇环是充要条件。

这样做复杂度是线性的，$O(n+m+k)$，不知道出题人为什么开 $4000$ 的范围。



```c++
vector<pii>vv[4003];
int col[4003];
bool dfs(int u,int c){
	col[u]=c;
	for(pii i:vv[u]){
		if(col[i.F]<0){
			if(dfs(i.F,c^i.S))
				re 1;
		}
		else{
			if(col[i.F]!=c^i.S)
				re 1;
		}
	}
	re 0;
}
void run(){
	int n,m,k;
	cin>>n>>m>>k;
	rep(i,n+m){
		vv[i].clear();
		col[i]=-1;
	}
	rep(i,k){
		int a,b,c,d,t;
		cin>>a>>b>>c>>d;
		t=0;
		if(d<b){
			b=d;
			t=1;
		}
		vv[a].pb({b+n,t});
		vv[b+n].pb({a,t});
	}
	rep(i,n+m)if(col[i]<0){
		if(dfs(i,0)){
			cout<<"nO\n";
			re;
		}
	}
	cout<<"YeS\n";
}
```



---

## 作者：Leasier (赞：1)

一道很需要脑子的题 /tyt

------------

我们可以将符合条件的 $2 \times 2$ 分为如下两类：

1. 情况 $P$

```
AB
CA
```

2. 情况 $Q$

```
AB
BC
```

设 $(x, y, P/Q)$ 表示左上角为 $(x, y)$ 的 $2 \times 2$ 符合情况 $P/Q$，接下来不妨来观察一下样例。

- 样例 2：$(x, y, P), (x, y, Q)$ 不共存。
- 样例 4 已经确定的部分长下面这样：
```
Q??Q
????
????
????
????
????
P??Q
```
中间的问号事实上可以扔掉一大半，我们将其缩成：
```
Q?Q
???
P?Q
```
手算一下会发现这样出现了矛盾。

不妨枚举一些类似的矛盾情况，比如：
```
PP
PQ
```
或者是：
```
PP
QP
```
由此，可以猜想：对于任意的 $(x_1, y_1, z_1), (x_1, y_2, z_2), (x_2, y_1, z_3), (x_2, y_2, z_4)$，若 $z_1, z_2$ 与 $z_3, z_4$ 的**相等情况**不同（即一个相等、一个不相等）或 $z_1, z_3$ 与 $z_2, z_4$ 的**相等情况**不同，则无解。

可以发现这个条件扩展后也是充要的，不难归纳证明。

扩展域并查集判断即可。时间复杂度为 $O(\sum(k + nm(\log n + \log m))$。

代码：
```cpp
#include <stdio.h>

typedef struct {
	int root[4007];
	
	inline void init(int n){
		for (int i = 1; i <= n; i++){
			root[i] = i;
		}
	}
	
	int get_root(int x){
		if (root[x] == x) return x;
		return root[x] = get_root(root[x]);
	}
	
	inline void merge(int x, int y){
		int x_root = get_root(x), y_root = get_root(y);
		if (root[x_root] != root[y_root]) root[x_root] = y_root;
	}
} DSU;

DSU dsu1, dsu2;
int type[2007][2007], bucket1[2007], bucket2[2007];

inline void init(int n, int m){
	dsu1.init(m * 2);
	dsu2.init(n * 2);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			type[i][j] = 0;
		}
	}
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, m, k;
		bool ans = true;
		scanf("%d %d %d", &n, &m, &k);
		init(n, m);
		for (int j = 1; j <= k; j++){
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			if (y2 == y1 + 1){
				ans &= type[x1][y1] == 0;
				type[x1][y1] = 1;
			} else {
				ans &= type[x1][y2] == 0;
				type[x1][y2] = 2;
			}
		}
		for (int j = 1; j <= n; j++){
			int cnt1 = 0, cnt2 = 0;
			for (int k = 1; k <= m; k++){
				if (type[j][k] == 1){
					bucket1[++cnt1] = k;
				} else if (type[j][k] == 2){
					bucket2[++cnt2] = k;
				}
			}
			for (int k = 1; k < cnt1; k++){
				dsu1.merge(bucket1[k], bucket1[k + 1]);
				dsu1.merge(bucket1[k] + m, bucket1[k + 1] + m);
			}
			for (int k = 1; k < cnt2; k++){
				dsu1.merge(bucket2[k], bucket2[k + 1]);
				dsu1.merge(bucket2[k] + m, bucket2[k + 1] + m);
			}
			if (cnt1 > 0 && cnt2 > 0){
				dsu1.merge(bucket1[1], bucket2[1] + m);
				dsu1.merge(bucket1[1] + m, bucket2[1]);
			}
		}
		for (int j = 1; j <= m && ans; j++){
			ans &= dsu1.get_root(j) != dsu1.get_root(j + m);
		}
		for (int j = 1; j <= m; j++){
			int cnt1 = 0, cnt2 = 0;
			for (int k = 1; k <= n; k++){
				if (type[k][j] == 1){
					bucket1[++cnt1] = k;
				} else if (type[k][j] == 2){
					bucket2[++cnt2] = k;
				}
			}
			for (int k = 1; k < cnt1; k++){
				dsu2.merge(bucket1[k], bucket1[k + 1]);
				dsu2.merge(bucket1[k] + n, bucket1[k + 1] + n);
			}
			for (int k = 1; k < cnt2; k++){
				dsu2.merge(bucket2[k], bucket2[k + 1]);
				dsu2.merge(bucket2[k] + n, bucket2[k + 1] + n);
			}
			if (cnt1 > 0 && cnt2 > 0){
				dsu2.merge(bucket1[1], bucket2[1] + n);
				dsu2.merge(bucket1[1] + n, bucket2[1]);
			}
		}
		for (int j = 1; j <= n && ans; j++){
			ans &= dsu2.get_root(j) != dsu2.get_root(j + n);
		}
		if (ans){
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

好题。

设原矩阵为 $A$。

考虑到 $A$ 中的每个 $2 \times 2$ 子矩阵中，必然有两个元素相等，且这两个元素的排列方式可能是主对角线（`/`）或副对角线（`\`）。我们考虑以此定义一个 $(n - 1) \times (m - 1)$ 的，矩阵元为 `/` 和 `\` 的矩阵 $A^D$。

**重要性质.** 对于 $A^D$ 中的一个 $2 \times 2$ 子矩阵，其中必然有偶数个 `/`。

*证明.* 可以直接手玩或者机玩 $2^4$ 种情况。

**推论.** $A^D$ 中的任一个 $2 \times 2$ 子矩阵，只要知道其中 $3$ 个元素，即可确定最后一个。

*证明.* 考虑一个类似异或的操作。

**推论.** $A^D$ 中的任意两列 $r_1, r_2$，要么有 $r_1 = r_2$，要么有 $\forall i, (r_1)_i \ne (r_2)_i$。

*证明.* 若出现 $\begin{pmatrix} a & b \\ c & d \end{pmatrix}$，$a = c, b \ne d$，则不难发现 $a, b, c, d$ 中必然有 $3$ 个 $a$，与发现的重要性质矛盾。

回到题目。原题中的限制无非是给定了一个矩阵元。从已知的矩阵元，我们有：把同一行 $i$ 缩成一个点 $R_i$，则对于已知的同一列的两个矩阵元 $a_{ij}$ 和 $a_{i'j}$，我们有 $a_{ij} = a_{i'j} \iff R_i = R_{i'}$，这样我们可以得到 $R_i$ 间的若干个等/不等关系，也就得到了一个种类并查集的模板。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n) { iota(begin(parent), end(parent), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int x, int y) { parent[find(x)] = find(y); }
    bool same(int x, int y) { return find(x) == find(y); }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    m--;
    vector<tuple<int, int, bool>> req(k);
    for (auto &[x, y, z] : req) {
        int a, b;
        cin >> x >> y >> a >> b;
        x--, y--, a--, b--;
        y = min(y, b), z = (a == x + 1 && b == y + 1);
    }
    sort(begin(req), end(req));
    DSU d(2 * m);
    for (int i = 1; i < k; i++) {
        auto [x0, y0, z0] = req[i - 1];
        auto [x1, y1, z1] = req[i];
        if (x0 == x1) {
            if (z0 == z1)
                d.unite(y0, y1), d.unite(y0 + m, y1 + m);
            else
                d.unite(y0, y1 + m), d.unite(y0 + m, y1);
        }
    }
    bool ok = true;
    for (int i = 0; i < m && ok; i++)
        if (d.same(i, i + m)) cout << "NO\n", ok = false;
    if (ok) cout << "YES\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

