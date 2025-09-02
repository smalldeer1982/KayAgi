# Matrix Transformation

## 题目描述

给定两个大小为 $n \times m$ 的矩阵 $A$ 和 $B$，其中元素是 $0$ 到 $10^9$ 之间的整数。你可以对矩阵 $A$ 执行以下任意次数的操作，且操作顺序不受限制：

- **按位与操作**：选择某一行 $i$ 和一个非负整数 $x$，将这一行的每个元素用 $x$ 进行按位与运算。具体来说，对于行 $i$ 的每个元素 $A_{i,j}$，都替换为 $A_{i,j} \text{ & } x$。
- **按位或操作**：选择某一列 $j$ 和一个非负整数 $x$，将这一列的每个元素用 $x$ 进行按位或运算。具体来说，对于列 $j$ 的每个元素 $A_{i,j}$，都替换为 $A_{i,j} \text{ | } x$。

可以在每次操作中选择不同的 $x$ 值。

你的任务是判断是否可以通过上述操作，将矩阵 $A$ 转变为矩阵 $B$。

## 说明/提示

以第二组输入数据为例，展示如何通过操作将矩阵 $A$ 转换为矩阵 $B$：

初始状态下，矩阵 $A$ 如下：

$$
\begin{bmatrix}
10 & 10 \\
42 & 42 \\
\end{bmatrix}
$$

1. 对第一行：应用按位与操作，选择 $x = 0$，矩阵变为：

$$
\begin{bmatrix}
0 & 0 \\
42 & 42 \\
\end{bmatrix}
$$

2. 对第二行：再次应用按位与操作，选择 $x = 0$，矩阵变为：

$$
\begin{bmatrix}
0 & 0 \\
0 & 0 \\
\end{bmatrix}
$$

3. 对第一列：应用按位或操作，选择 $x = 21$，矩阵变为：

$$
\begin{bmatrix}
21 & 0 \\
21 & 0 \\
\end{bmatrix}
$$

4. 对第二列：再次应用按位或操作，选择 $x = 21$，最终矩阵为：

$$
\begin{bmatrix}
21 & 21 \\
21 & 21 \\
\end{bmatrix}
$$

通过这一系列操作，我们成功将矩阵 $A$ 转换为矩阵 $B$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1 1
12
13
2 2
10 10
42 42
21 21
21 21
2 2
74 10
42 106
21 85
85 21
2 4
1 2 3 4
5 6 7 8
3 2 3 4
1 0 1 0```

### 输出

```
Yes
Yes
No
Yes```

# 题解

## 作者：BYR_KKK (赞：9)

提供一种简单好想好写的做法（赛时想+写花了 15 min），看上去题解区没有这种做法。

位运算下各位是独立的，所以拆位。接下来就是一个 $01$ 矩阵。考虑与操作，显然有用的只有与上 $0$（与上 $1$ 无用），因此与操作等价于将一行变成 $0$，同理或操作等价于将一列变成 $1$。

于是问题变成对于 $01$ 矩阵，可以将一行变成 $0$ 或者将一列变成 $1$，判断是否可以得到另一个矩阵。考虑逆序操作，我们每次可以将目标矩阵的全 $0$ 行或全 $1$ 列换成任何数，判断能否得到当前矩阵。

我们每次将目标矩阵的一个全 $0$ 行或全 $1$ 列删去，同时删去当前矩阵的对应行/对应列，不断进行此操作，若最后两个矩阵相同则可以完成目标，否则不可以。正确性不难证明。

于是每次暴力找全 $0$ 行/全 $1$ 列，时间复杂度 $O(Tnm\log V)$。根本跑不满。

代码写的不太精细，时间复杂度略高。

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define debug(...) fprintf(stderr,##__VA_ARGS__)

template<typename T>
void read(T &x){
	x=0;
	int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=x*10+(int)(c-'0'),c=getchar();
	x*=f;
}

std::stack<char>st;
template<typename T>
void print(T x){
	if(x==0) putchar('0');
	if(x<0) putchar('-'),x=-x;
	while(st.size()) st.pop();
	while(x) st.push((char)('0'+x%10)),x/=10;
	while(st.size()) putchar(st.top()),st.pop();
}

template<typename T>
void printsp(T x){
	print(x),putchar(' ');
}

template<typename T>
void println(T x){
	print(x),putchar('\n');
}

template<typename T,typename I>
void chkmin(T &a,I b){
	a=std::min(a,b);
}

template<typename T,typename I>
void chkmax(T &a,I b){
	a=std::max(a,b);
}

bool Mbe;

const int inf=1e18,MOD1=998244353,MOD2=1e9+7;

int T;

const int maxn=1e3+10;

int a[maxn][maxn],n,m,b[maxn][maxn],c[maxn],d[maxn],e[maxn][maxn];

bool e1[maxn],e2[maxn];

bool Men;

signed main(){
	debug("%.6lfMB\n",(&Mbe-&Men)/1048576.0);
	read(T);
	while(T--){
		read(n),read(m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) read(a[i][j]);
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) read(b[i][j]);
		bool f=1;
		for(int i=32;i>=0;i--){
			int x=0,y=0;
			for(int j=1;j<=n;j++)
				for(int k=1;k<=m;k++) e[j][k]=((b[j][k]>>i)&1);
			for(int i=1;i<=std::max(n,m);i++) c[i]=d[i]=0,e1[i]=e2[i]=0;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					if(e[i][j]==0) c[i]++;
					else d[j]++;
			while(1){
				bool g=0;
				for(int i=1;i<=n;i++){
					if(e1[i]) continue;
					if(c[i]==m){
						g=1;
						x++;
						for(int j=1;j<=m;j++)
							if((!e2[j])&&e[i][j]==0) d[j]++;
						e1[i]=1;
					}
				}
				for(int i=1;i<=m;i++){
					if(e2[i]) continue;
					if(d[i]==n){
						g=1;
						y++;
						for(int j=1;j<=n;j++)
							if((!e1[j])&&e[j][i]==1) c[j]++;
						e2[i]=1;
					}
				}
				if(!g) break;
			}
			for(int j=1;j<=n&&f;j++){
				if(e1[j]) continue;
				for(int k=1;k<=m;k++){
					if(e2[k]) continue;
					int w=((a[j][k]>>i)&1);
					if(w!=e[j][k]){
						f=0;
						break;
					}
				}
			}
			if(!f){
				// debug("i=%lld\n",i);
				break;
			}
		}
		if(f) printf("YES\n");
		else printf("NO\n");
	}
	debug("%.6lfms\n",1e3*clock()/CLOCKS_PER_SEC);
}
```

---

## 作者：__vector__ (赞：5)

### 题意  

给定大小为 $n \times m$ 的矩阵 $A,B$，两个矩阵均由不大于 $10^9$ 的非负整数组成。  

单次操作可以有以下两种形式：  

1. 选择两个数 $i,x$，满足 $1 \le i \le n,x \ge 0$。  

   对于 $1 \le \forall j \le m$，将 $A_{i,j}$ 替换为 $A_{i,j}$ 按位与 $x$，即整行按位与。  

2. 选择两个数 $j,x$，满足 $1 \le j \le m,x\ge 0$。  

   对于 $1 \le  \forall i \le n$，将 $A_{i,j}$ 替换为 $A_{i,j}$ 按位或 $x$，即整列按位或。    

问能否在任意次操作之后将 $A$ 变为 $B$。  

### 做法  

每一位都是独立的，考虑枚举每一位。  

问题简化为了，两个 $n \times m$ 的 01 矩阵 $A,B$，每次可以将 $A$ 的一整行设置为 $0$，或将 $A$ 的一整列设置为 $1$，求能否将 $A$ 变为 $B$。  

考虑对于 $(i,j)$，如果 $A_{i,j} \neq B_{i,j}$，该如何处理。  

1. $A_{i,j}=1$ 且 $B_{i,j}=0$，此时需要对 $i$ 行执行一次操作。  
2. $A_{i,j}=0$ 且 $B_{i,j}=1$，此时需要对 $j$ 列进行一次操作。  

不难注意到，每一行，每一列最多执行一次操作。  

如果对第 $i$ 行执行了操作，且存在 $j$ 满足 $B_{i,j}=1$，那么必然需要在此之后对 $j$ 列执行一次操作。  

同理，如果对第 $j$ 列执行了操作，存在 $i$ 满足 $B_{i,j}=0$，那么必然需要在此之后对第 $i$ 列执行一次操作。  

由此可以建立一个有向图，$x \rightarrow y$ 代表 $x$ 操作执行完成后必须执行 $y$ 操作。  

从每个必须执行的操作出发 dfs，如果找到环，那么必然无解。  

如果最终没有找到环，显然是有解的。

---

## 作者：cdx123456 (赞：5)

对于位运算，把矩阵按位拆成 $01$ 矩阵是显然的，考虑如何操作 $01$ 矩阵。

发现操作的本质是把一行设为 $0$，一列设为 $1$，考虑怎么做。一种正常的做法是建一张图，点是原图的行列，边是操作的先后顺序，看哪些是必须操作的，如果必须操作的在环里就寄了，拓扑排序即可。

还有一种乱搞的做法，考虑贪心，可以从左往右做，每次如果这一列必须赋成 $1$，那就赋值，然后这一列哪一行要赋为 $0$，再对行操作。然后就 Wa on test 2 了，给出一组 hack。


```
1
2 2
1 0
1 0
1 1
1 0
```

但是按照上述操作重复两遍，就能通过 hack 了。考虑多进行些操作，$15$ 次会 Wa on test 8，可以做 $30$ 次，然后就过了……

P.S. 这么直接做会被卡常，要加一句剪枝就是做若干次操作后如果变成了目标状态，那么直接停止。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1010][1010],b[1010][1010],c[1010][1010],d[1010][1010];
int main(){
	int T;
	cin>>T;
	while(T--){
		int ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>b[i][j];
		for(int k=0;k<=20;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					c[i][j]=(a[i][j]>>k)&1;
					d[i][j]=(b[i][j]>>k)&1;
				}
			}
			for(int w=1;w<=30;w++){
				int f=1;
				for(int j=1;j<=m;j++){
					int f=0;
					for(int i=1;i<=n;i++) if(!c[i][j] && d[i][j]) f=1;
					if(f) for(int i=1;i<=n;i++) c[i][j]=1;
					for(int i=1;i<=n;i++) if(c[i][j]!=d[i][j]) for(int kk=1;kk<=m;kk++) c[i][kk]=0;
				}
				for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(c[i][j]!=d[i][j]) f=0;
				if(f) break;
			}
			for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(c[i][j]!=d[i][j]) ans=1;
			if(ans) break;
		}
		if(ans) cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```

### 后话

赛时我看 Wa on test 8 以为被专门 hack 了，然后去想的拓扑做法，最后 E 题 $5$ 发遗憾离场。

---

## 作者：xiezheyuan (赞：4)

## 简要题意

给定两个 $n\times m$ 的矩阵 $A,B$，你可以进行任意次下列操作，使得 $A=B$：

1. 选定一行 $i$ 和一个自然数 $x$，将这一行每一个数按位与上 $x$。
2. 选定一列 $j$ 和一个自然数 $x$，将这一列每一个数按位或上 $x$。

输出是否存在有限次操作的方案。

$T$ 组数据。$1\leq T\leq 100,1\leq n\cdot m\leq 10^3,0\leq A_{ij},B_{ij}\leq 10^9$。

## 思路

首先由于位运算中位与位之间独立，所以可以将 $A,B$ 拆位，变成两个 $01$ 矩阵，这样每次操作的 $x$ 也缩减到了 $\{0,1\}$ 两个数。

对于操作 $1$，选择 $x=1$ 显然是没有意义的，对于操作 $2$，选择 $x=0$ 显然也是没有意义的，于是每个操作就没有了 $x$ 之分，变成了将一行赋值为 $0$ 以及将一列赋值为 $1$ 两个简单的操作。

然后考虑每一个位置 $(i,j)$，如果 $A_{ij}\neq B_{ij}$，则肯定需要对第 $i$ 行或第 $j$ 列操作，具体如何操作依据 $B_{ij}$ 的值而定。

注意到操作和操作之间会互相影响，因此需要钦定一个合理的操作顺序，如果 $B_{ij}=1$，则对行 $i$ 的操作必须在对列 $j$ 操作前，反之亦然。我们发现这是一个二元关系，于是可以建出有向图，然后如果我们需要进行的操作代表的点出发可以走到环，那么肯定是无解的。

否则按照拓扑序，很容易构造出一组解。

至于有向图判环，dfs 或者 bfs 都可以。

时间复杂度（大概是）$O(Tnm\log V)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5;
int n, m, a[N][N], b[N][N];
vector<int> g[N << 1];
bool must[N << 1], vis[N], in[N];

bool dfs(int u){
    if(in[u]) return false;
    in[u] = 1;
    for(int v : g[u]){
        if(!vis[v] && !dfs(v)) return false;
    }
    in[u] = 0, vis[u] = 1;
    return true;
}

bool solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin >> a[i][j];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin >> b[i][j];
    }
    for(int t=30;~t;t--){
        fill(must + 1, must + n + m + 1, 0);
        fill(vis + 1, vis + n + m + 1, 0);
        fill(in + 1, in + n + m + 1, 0);
        for(int i=1;i<=n+m;i++) g[i].clear();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                bool A = (a[i][j] >> t) & 1, B = (b[i][j] >> t) & 1;
                if(B) g[i].push_back(j + n);
                else g[j + n].push_back(i);
                if(A && !B) must[i] = 1;
                if(!A && B) must[j + n] = 1;
            }
        }
        for(int i=1;i<=n+m;i++){
            if(must[i] && !dfs(i)) if(!dfs(i)) return false;
        }
    }
    return true;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int t; cin >> t;
    while(t--) cout << (solve() ? "Yes" : "No") << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：RAYMOND_7 (赞：4)

连续两场 div2 过不了 E 了，只能说是 NOIP 二等水平。

不太能严谨证明其复杂度，应该是 $O(nm \log V)$

考虑调整法，对于一列，每次找所有需要补上的 bit，并对于整列补上这一部分，对于一行，找出所有的需要消除的部分，并删除。

如果有解的话应该 $O(\log V)$ 次就结束了，否则视为无解。

感觉每一轮行和列不同的数位都会减少，也许可以势能分析，复杂度希望有人严谨证明。

代码是简单的。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cassert>

using namespace std;

#define PII pair<int,int>
#define x first
#define y second
#define For(i, l, r) for(int i = l; i <= r; i ++)
#define Rep(i, l, r) for(int i = l; i >= r; i --)

bool START;

void in(int &x)
{
	char c = getchar(); int op = 1;
	while(c > '9' || c < '0') op *= (c == '-' ? -1 : 1), c = getchar();
	for(x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0'; x *= op;
}

const int N = 1010;

int Tst, n, m, a[N][N], b[N][N], c[N][N], d[N][N];

bool ENDPOS = 0;
int main()
{
	in(Tst);
	while(Tst --)
	{
		in(n); in(m);
		For(i, 1, n) For(j, 1, m) in(a[i][j]);
		For(i, 1, n) For(j, 1, m) in(b[i][j]);
		int o = 0;
		For(i, 0, 29) o |= (1 << i);
		For(w, 0, 30)
		{
			For(i, 1, m)
			{
				int res = 0;
				For(j, 1, n) res |= (b[j][i] ^ (b[j][i] & a[j][i]));
				For(j, 1, n) a[j][i] |= res;
			}
			For(i, 1, n)
			{
				int res = 0;
				For(j, 1, m) res |= (a[i][j] ^ (a[i][j] & b[i][j]));
				res ^= o;
				For(j, 1, m) a[i][j] &= res;
			}
		}
		int ok = 1;
		For(i, 1, n) For(j, 1, m) if(a[i][j] != b[i][j]) ok = 0;
		puts(ok ? "Yes" : "No");
	}
	return 0;
}
```

---

## 作者：OrinLoong (赞：2)

首先这道题两种操作都是位与位之间互不影响的位运算。所以按位考虑，题目转化为：有两种操作，操作一是把一行全变为 $0$，操作二是把一列全变成 $1$，给你两个 01 矩阵 $A$ 和 $B$，问能否在有限次操作内把 $A$ 转变为 $B$。

乍一看还是无从下手，直接暴力调整的话不知道复杂度能不能接受，我们需要对操作的范围找到一些约束。

首先我们猜想不可能有重复的操作。（这里我不会证 qaq，有巨佬会的话可以评论区留言）

然后思考某些操作的必要性。发现若 $\exist\, i,j,A_{i,j}=1 \land B_{i,j}=0$，则对第 $i$ 行操作是必要的；若 $\exist\, i,j,A_{i,j}=0 \land B_{i,j}=1$，则对列 $j$ 操作是必要的。

再考虑操作之间的先后顺序。行与行，列与列之间都没什么直接限制，而对于行 $i$ 和列 $j$ 来说，若 $B_{i,j}=1$，则对列 $j$ 的操作是不可能晚于对行 $i$ 的操作的，并且如果操作了一次行 $i$，则之后必须补一次对列 $j$ 的操作。$B_{i,j}=0$ 时反之。这样我们就确定了所有行列之间可能存在的先后关系。说是“可能”的原因在于有些操作可能是非必要的。

~~观察到 Codeforces 上 graphs 的标签，这启示我们~~这种约束关系不妨抽象为有向边。原问题转化为：给定一张有向图，上有某些必选的点，如果一个点选了则它有边指向的点也要选，问最后有没有环，有环即非法，否则合法。接下来，我们只需要对每个必选点跑一遍 bfs 就行了。

这个做法的时间复杂度倒是比较显然——$O(T(NM+(N+M)^2)=O(TNM)$（有向图的点数是 $N+M$ 的。）

代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MaxN=1e3+5,MaxLbAi=30;
int Tcn,N,M,A[MaxN][MaxN],B[MaxN][MaxN],flag;
int C[MaxN][MaxN],D[MaxN][MaxN],mus[MaxN<<1];
vector<int> G[MaxN<<1];int vis[MaxN<<1];
void addedge(int u,int v){G[u].push_back(v);}
bool check(){
    queue<int> q;
    for(int i = 1;i <= N+M;i++){
        if(!mus[i])continue;
        memset(vis,0,sizeof(vis));
        q.push(i),vis[i]=1;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v : G[u]){
                if(v==i)return false;
                if(!vis[v])q.push(v),vis[v]=1;
            }
        }
    }
    return true;
}
bool solve(int ci){
    memset(mus,0,sizeof(mus));for(int i = 0;i <= N+M;i++)G[i].clear();
    for(int i = 1;i <= N;i++)for(int j = 1;j <= M;j++)C[i][j]=(A[i][j]>>ci)&1;
    for(int i = 1;i <= N;i++)for(int j = 1;j <= M;j++)D[i][j]=(B[i][j]>>ci)&1;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            if(D[i][j]==0){addedge(N+j,i);if(C[i][j]==1)mus[i]=1;}
            if(D[i][j]==1){addedge(i,N+j);if(C[i][j]==0)mus[N+j]=1;}
        }
    }
    return check();
}
void mian(){
    scanf("%d%d",&N,&M);flag=1;    
    for(int i = 1;i <= N;i++)for(int j = 1;j <= M;j++)scanf("%d",&A[i][j]);
    for(int i = 1;i <= N;i++)for(int j = 1;j <= M;j++)scanf("%d",&B[i][j]);
    for(int i = 0;i < MaxLbAi;i++)flag&=solve(i);
    flag?puts("Yes"):puts("No");
}
int main(){
    scanf("%d",&Tcn);
    while(Tcn--)mian();
    return 0;
}
```
[Accepted Submission](https://codeforces.com/problemset/submission/2043/298483253)

---

## 作者：yvbf (赞：1)

![](bilibili:BV1oKCAYmEKy)

---

## 作者：xiaoyang222 (赞：0)

容易把这些矩阵上的每一位拆出来，拆成 $31$ 个 `01` 矩阵。把每一对矩阵判一下，最后看能否全部变完就可以了。

操作可以看成下面两个。

1. 把一行全部变成 $0$。

2. 把一列全部变成 $1$。

这样看起来不可做，考虑逆向操作。

如果一行全是 $0$，那么这一行原来可能是任何数，就不管这一行的判定，较好的实现就是假设这一行删去。如果一列全是 $1$，一样。

最后看看两个矩阵是否一样就可以了。

代码没删调试。

```cpp
#include <iostream>
#include <queue>
using namespace std;
const int N=1e3+5,B=31;
int a[B][N][N],b[B][N][N];
int cnt1[2][B][N],cnt2[2][B][N],dug1[N][N],dug2[N][N];
bool chk1[N],chk2[N];
int _;
void solve(){
	int n=1e3,m=1e3;
	cin >> n >> m;
	for (int i=1;i<=n;++i){
		for (int j=1,x;j<=m;++j){
			cin >> x;
//			x=1;
			dug1[i][j]=x;
			for (int k=0;k<B;++k){
				a[k][i][j]=(x>>k&1);
			}
		}
	}
	for (int i=0;i<N;++i) for (int j=0;j<B;++j) cnt1[0][j][i]=cnt2[0][j][i]=cnt1[1][j][i]=cnt2[1][j][i]=0;
	for (int i=1;i<=n;++i){
		for (int j=1,x;j<=m;++j){
			cin >> x;
//			x=1;
			dug2[i][j]=x;
			for (int k=0;k<B;++k){
				b[k][i][j]=(x>>k&1);
				++cnt1[b[k][i][j]][k][i],
				++cnt2[b[k][i][j]][k][j];
			}
		}
	}
	for (int k=0;k<B;++k){
//		cout<<k<<" : \n";
		for (int i=0;i<N;++i) chk1[i]=chk2[i]=0;
		queue<pair<int,int>> q;
		for (int i=1;i<=n;++i)
			if (cnt1[1][k][i]==0) q.emplace(0,i);
		for (int i=1;i<=m;++i)
			if (cnt2[0][k][i]==0) q.emplace(1,i);
		int op,x;
		while (!q.empty()){
			op=q.front().first,x=q.front().second;q.pop();
//			cout<<op<<" "<<x<<"\n";
//			cout<<op<<" "<<x<<"\n";
			if (op==0){
				chk1[x]=1;
				for (int j=1;j<=m;++j){
					--cnt1[b[k][x][j]][k][x];
					--cnt2[b[k][x][j]][k][j];
					if (cnt2[0][k][j]==0 && !chk2[j]) q.emplace(1,j),chk2[j]=1;
				}
			}else{
				chk2[x]=1;
				for (int j=1;j<=n;++j){
					--cnt1[b[k][j][x]][k][j];
					--cnt2[b[k][j][x]][k][x];
					if (cnt1[1][k][j]==0 && !chk1[j]) q.emplace(0,j),chk1[j]=1;
				}
			}
		}
		bool flg=1;
		for (int i=1;i<=n;++i){
			for (int j=1;j<=m;++j){
				if (chk1[i] || chk2[j]) continue;
				if (a[k][i][j]!=b[k][i][j])flg=0;
			}
		}
		if (!flg){
//			for (int i=1;i<=n;++i) cout<<chk1[i]<<" ";cout<<"\n";
//			for (int i=1;i<=m;++i) cout<<chk2[i]<<" ";cout<<"\n";
			cout<<"No\n";return;
		}
//		cout<<"\n\n\n\n\n";
	}
	cout<<"Yes\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin >> T;
	for (;_<T;++_) solve();
	cout.flush();
	return 0;
}
/*
1
2 2
1 0
1 0
1 1
1 1
*/
```

---

## 作者：ax_by_c (赞：0)

首先显然是拆位，原操作相当于把某行全部变成 0 或者把某列全部变成 1。

考虑把所有的 $n+m$ 个操作看成点，如果一个操作执行后另一个操作必须执行则连有向边，可以根据 $B$ 将图建出来。

接下来找到 $A,B$ 中的元素变化情况，每一个变化都对应了一个操作，只需要判断从这些操作的对应点出发是否有环即可。（有环说明要一直执行，所以无解。）

时间复杂度 $O(Tnm\log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
const int N=1e3+5;
int n,m,a[N][N],b[N][N];
vector<int>g[N*2];
bool mk[N*2];
void dfs(int u){
	if(mk[u])return ;
	mk[u]=1;
	for(auto v:g[u])dfs(v);
}
int in[N*2];
queue<int>q;
bool check(int x){
	x=1<<x;
	for(int i=1;i<=n+m;i++){
		g[i].clear();
		mk[i]=0;
		in[i]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(b[i][j]&x)g[i].push_back(n+j);
			else g[n+j].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if((a[i][j]&x)&&!(b[i][j]&x))dfs(i);
			if(!(a[i][j]&x)&&(b[i][j]&x))dfs(n+j);
		}
	}
	int cnt=0;
	for(int i=1;i<=n+m;i++){
		if(mk[i]){
			cnt++;
			for(auto v:g[i]){
				if(mk[v])in[v]++;
			}
		}
	}
	while(q.size())q.pop();
	for(int i=1;i<=n+m;i++){
		if(mk[i]&&!in[i])q.push(i);
	}
	while(q.size()){
		cnt--;
		int u=q.front();
		q.pop();
		for(auto v:g[u]){
			if(mk[v]){
				in[v]--;
				if(!in[v])q.push(v);
			}
		}
	}
	return !cnt;
}
void slv(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)scanf("%d",&b[i][j]);
	}
	for(int i=0;i<=29;i++){
		if(!check(i)){
			puts("No");
			return ;
		}
	}
	puts("Yes");
}
void main(){
	int T;
	scanf("%d",&T);
	while(T--){
		slv();
	}
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：luckyclover (赞：0)

首先按位拆成 $\log$ 个 $01$ 矩阵是显然的。然后我们发现正着做因为操作间会互相覆盖所以不好做，考虑把操作倒过来做：

操作一转化为把一个全 $0$ 的行替换成通配符，操作二转化为把一个全 $1$ 的列替换为通配符。不难发现此时操作间互相独立。

设原矩阵为 $C$，这样操作尽可能多次得到的矩阵为 $C^{'}$，则一个矩阵可以通过原题面中的操作转化为 $C$ 当且仅当它可以通过把 $C^{'}$ 中的通配符替换为 $0$ 或 $1$ 得到。

于是对 $B$ 进行上述操作，判断是否和 $A$ 相同就做完了。具体实现可以用 bfs。

时间复杂度 $\mathcal{O}(nm\log V)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=1005;
int a[30][MAX][MAX],b[30][MAX][MAX];  // 2 为通配符
int cnt0[MAX],cnt1[MAX];
int n,m;
void solve(){
    cin>>n>>m;
    fill(cnt0+1,cnt0+m+1,0);
    fill(cnt1+1,cnt1+n+1,0);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int x;
            cin>>x;
            for(int k=0;k<30;k++)
                a[k][i][j]=x>>k&1;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int x;
            cin>>x;
            for(int k=0;k<30;k++)
                b[k][i][j]=x>>k&1;
        }
    for(int i=0;i<30;i++){
        queue<pair<bool,int>> Q;
        for(int j=1;j<=n;j++){
            cnt1[j]=0;
            for(int k=1;k<=m;k++)
                cnt1[j]+=(b[i][j][k]==1);
            if(cnt1[j]==0) Q.push(make_pair(0,j));
        }
        for(int j=1;j<=m;j++){
            cnt0[j]=0;
            for(int k=1;k<=n;k++)
                cnt0[j]+=(b[i][k][j]==0);
            if(cnt0[j]==0) Q.push(make_pair(1,j));
        }
        while(Q.size()){
            bool f=Q.front().first;
            int u=Q.front().second;
            Q.pop();
            if(f)
                for(int j=1;j<=n;j++){
                    if(b[i][j][u]==1&&--cnt1[j]==0) 
                        Q.push(make_pair(0,j));
                    b[i][j][u]=2;
                }
            else
                for(int j=1;j<=m;j++){
                    if(b[i][u][j]==0&&--cnt0[j]==0) 
                        Q.push(make_pair(1,j));
                    b[i][u][j]=2;
                }
        }
        for(int j=1;j<=n;j++)
            for(int k=1;k<=m;k++)
                if(b[i][j][k]!=2&&a[i][j][k]!=b[i][j][k]){
                    cout<<"No\n";
                    return ;
                }
    }
    cout<<"Yes\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：MrPython (赞：0)

Brute force 启动！

首先，显而易见的是按二进制每一位进行拆分，接下来就是在 01 矩阵上操作。

定义一回合为：先扫描每一行，再扫描每一列，若该行/列有需要操作的就对整行/列进行操作。我们可以大胆猜测：若存在解，每次操作应该能固定一行与一列，因此最多会进行 $\min(n,m)+O(1)$ 次操作。我们完所有操作后判断是否达到目标状态即可。

赛场上我选择了 $+10$，[喜提 999 ms，险些被 hack](https://codeforces.com/contest/2043/submission/298279193)。赛后实践得 $+1$ 就足够了。

单组数据时间复杂度 $O(nm\sqrt{nm}\log V)$。

```cpp
#include <algorithm>
#include <array>
#include <bitset>
#include <cstddef>
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    size_t n, m;
    fin >> n >> m;
    vector a(n, vector<ui>(m)), b(n, vector<ui>(m));
    for (auto& i : a)
      for (auto& j : i) fin >> j;
    for (auto& i : b)
      for (auto& j : i) fin >> j;
    for (size_t t = 0; t < 32; ++t) {
      vector sa(n, vector<bool>(m)), sb(n, vector<bool>(m));
      for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
          sa[i][j] = (a[i][j] >> t) & 1, sb[i][j] = (b[i][j] >> t) & 1;
      for (size_t c = 0; c <= min(n, m); ++c) {
        for (size_t i = 0; i < n; ++i) {
          bool operate = false;
          for (size_t j = 0; j < m; ++j)
            if (sa[i][j] == 1 && sb[i][j] == 0) {
              operate = true;
              break;
            }
          if (operate)
            for (size_t j = 0; j < m; ++j) sa[i][j] = 0;
        }
        for (size_t j = 0; j < m; ++j) {
          bool operate = false;
          for (size_t i = 0; i < n; ++i)
            if (sa[i][j] == 0 && sb[i][j] == 1) {
              operate = true;
              break;
            }
          if (operate)
            for (size_t i = 0; i < n; ++i) sa[i][j] = 1;
        }
      }
      if (sa != sb) {
        fout << "No\n";
        goto end;
      }
    }
    fout << "Yes\n";
  end:;
  }
  return 0;
}
```

---

