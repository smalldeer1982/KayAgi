# [ARC119D] Grid Repainting 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc119/tasks/arc119_d

$ H $ 行 $ W $ 列のマス目で表されるキャンバスがあり、上から $ i $ $ (1\ \leq\ i\ \leq\ H) $ 行目・左から $ j $ $ (1\ \leq\ j\ \leq\ W) $ 列目のマスを $ (i,\ j) $ と表します。最初、マス $ (i,\ j) $ は $ s_{i,\ j}= $ `R` のとき赤色で、$ s_{i,\ j}= $ `B` のとき青色で塗られています。

あなたは「次の $ 2 $ つのうち一方を選んで操作すること」を何回でも行うことができます。

> **操作X** 赤色で塗られているマスを $ 1 $ つ選び、そのマスと同じ行にあるすべてのマス（自分自身を含む）を白色に塗り替える。  
> **操作Y** 赤色で塗られているマスを $ 1 $ つ選び、そのマスと同じ列にあるすべてのマス（自分自身を含む）を白色に塗り替える。

最終的に白色で塗られたマスの個数を最大にするような、操作手順の一例を示してください。

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 2500 $
- $ 1\ \leq\ W\ \leq\ 2500 $
- $ s_{i,\ j} $ は `R` または `B` である $ (1\ \leq\ i\ \leq\ H,\ 1\ \leq\ j\ \leq\ W) $
- $ H,\ W $ は整数

### Sample Explanation 1

たとえば次のように操作を行うことで、$ 10 $ 個のマスを白色にすることができます。 - まず、マス $ (1,\ 1) $ を選び、\*\*操作X\*\*を行う。 - 次に、マス $ (4,\ 3) $ を選び、\*\*操作Y\*\*を行う。 - 次に、マス $ (4,\ 1) $ を選び、\*\*操作X\*\*を行う。 なお、$ 11 $ 個以上のマスを白色にする方法は存在しません。 !\[ \](https://img.atcoder.jp/arc119/b0fde87f879b9dc90ca8788945f21bf2.png)

### Sample Explanation 2

すべてのマスを白色に塗り替えることができます。

### Sample Explanation 3

赤色のマスが $ 1 $ つも存在しないため、そもそも操作を行うことができません。

## 样例 #1

### 输入

```
4 4
RBBB
BBBB
BBBB
RBRB```

### 输出

```
3
X 1 1
Y 4 3
X 4 1```

## 样例 #2

### 输入

```
1 119
BBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBBBBBRBBB```

### 输出

```
4
Y 1 60
Y 1 109
Y 1 46
X 1 11```

## 样例 #3

### 输入

```
10 10
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB```

### 输出

```
0```

# 题解

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc119_d)

**题目大意**

> 给定 $n\times m$ 矩阵，每个格子是红或蓝，每次可以选择一个红格子将其所在行或列涂白。
>
> 构造一组方案最大化白格子数量。
>
> 数据范围：$n,m\le 1000$。

**思路分析**

对于一个 $(i,j)$ 上的红格子看成左部第 $i$ 个点对右部第 $j$ 个点的连边。

一次染色就是选择一个非孤立点，将其邻边全部删除。

对于一个连通块，显然无论怎么删都会留下一个点，并且可以构造方案：以该点为根求出 dfs 树，每次删叶子即可。

那么设有 $k$ 个连通块，直接枚举有多少个连通块剩下的点是行，非孤立的行、列分别有 $r,c$ 个，那么答案就是 $\max_{i=0}^k(n-r+i)(m-c+k-i)$。

构造方案是简单的，直接 dfs。

时间复杂度 $\mathcal O(nm)$。

**代码呈现**

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2505;
char a[MAXN][MAXN];
int n,m,c=0,sl=0,sr=0;
vector <int> G[MAXN<<1];
vector <int> ver[MAXN<<1];
bool vis[MAXN<<1];
void dfs(int u) {
	vis[u]=true,++(u<=n?sl:sr),ver[c].push_back(u);
	for(int v:G[u]) if(!vis[v]) dfs(v);
}
void out(int u,int fz) {
	vis[u]=true;
	for(int v:G[u]) if(!vis[v]) out(v,u);
	if(fz) {
		if(u<=n) printf("X %d %d\n",u,fz-n);
		else printf("Y %d %d\n",fz,u-n);
	}
}
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) {
		scanf("%s",a[i]+1);
		for(int j=1;j<=m;++j) if(a[i][j]=='R') {
			G[i].push_back(j+n),G[j+n].push_back(i);
		}
	}
	for(int i=1;i<=n+m;++i) if(!vis[i]&&!G[i].empty()) ++c,dfs(i);
	int x=0;
	for(int i=1;i<=c;++i) if((n-sl+x)*(m-sr+c-x)>(n-sl+i)*(m-sr+c-i)) x=i;
	printf("%d\n",sl+sr-c);
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=x;++i) {
		for(int z:ver[i]) if(z<=n) { out(z,0); break;}
	}
	for(int i=x+1;i<=c;++i) {
		for(int z:ver[i]) if(z>n) { out(z,0); break; }
	}
	return 0;
}
```

---

## 作者：Sampson_YW (赞：3)

如果 $(i,j)=R$，那么将 $i$ 和 $j$ 连边建二分图。每次选择一个有至少一条边的点，并删掉和它相连的所有边。

设左边删了 $X$ 个点，右边删了 $Y$ 个点，那么答案为 $HW-(H-X)(W-Y)$。

怎么删呢？假如图是一棵树，因为每次删一个点至少会删一条边，那么最后至少会留下一个点。可以通过构造来证明最后剩下恰好一个点。

每次删掉叶子节点，直到最后剩下一条边。此时这两个点分别位于左边和右边。那么对于一棵树，可以让左边或右边保留一个点。

当图是一个森林呢？假如有 $K$ 个连通块，且左边有 $A$ 个点有边，右边有 $B$ 个点有边，那么最后假设左边保留了 $x$ 个点，最终的答案就是 $HW-(H-(A-x))(W-(B-(K-x)))$。由于这个函数是下凸的，所以 $x=0$ 或 $x=K$。

当每棵树变成了联通图的情况呢？将图看成一棵树增加了许多边，那么这些边不会改变答案。于是提取出任意一棵生成树就做完了。

[code](https://atcoder.jp/contests/arc119/submissions/47979410)

---

## 作者：王江睿 (赞：2)

### 引理

对于图上的每一个极大的连通块，除去任意一行或一列后，剩余的部分可以全部涂白。

### 证明

不妨设它是一行。构造涂色方法：以该行为根**深度优先**地遍历连通块，并按边的**完成顺序**染色。对于每一条边，以它深度更高的端点为作用点，清除对应的行（列）。一个例子是：

![](https://cdn-fusion.imgimg.cc/i/2024/047e952552c9a15e.png)

**方法显然合法**。对任意一个连通块实行的最后一次操作所在点的转置方向，必然未被消除过；否则无法操作该点。

----

令总量 $ S $ 为 $ \{(i,j) | N\{i\} \neq \emptyset \text{且} N(n+j) \neq \emptyset\} $ 的大小，连通块总数为 $ k $。考虑全选行时和全选列时，一个连通块对答案的**负贡献**：某一行（列）上所有非空列（行）都会被它所在的列（行）消除，空行是全同的，故选任意一行（列）的负贡献都是**空列（行）的数量**。

假设选择的点集是 $ T $，共有 $ a $ 个选列、$ b $ 个选行，空行数量为 $ x $、空列数量为 $ y $。让 $ M $ 为 $ T $ 对原图的导出子图上边集的大小。则答案为

$$
S - a \times x - b \times y - (a \times b - M)
$$

其中 $ a \times b - M \geq 0 $ 且仅在 $ a = k $ 或 $ b = k $ 时取等；显然，答案取最大值时必有 $ a = k $ 或 $ b = k $。当 $ x > y $ 时，全选行；当 $ y > x $ 时，全选列。

代码 (with C++14)：

```cpp
#include<bits/stdc++.h>
using namespace std;
int constexpr _n=5e3+7;
bitset<_n>vis;
int n,m,c1,c2;
wstring E[_n];
basic_string<tuple<char,int,int>>ans;
void dfs(int x){
	vis[x]=1;
	for(int y:E[x]) if(!vis[y])
		dfs(y),x>n?ans+={'X',y,x-n}:
				   ans+={'Y',x,y-n};
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			char c;cin>>c;
			if(c=='R'){
				c1+=E[i].empty(),c2+=E[j+n].empty();
				E[i]+=j+n,E[j+n]+=i;
			}
		}
	for(int i=1;i<=n+m;++i)
		if((i>n)^(n-c1>m-c2)) 
			dfs(i);
	cout<<ans.size()<<'\n';
	for(auto[a,b,c]:ans)
		cout<<a<<" "<<b<<" "<<c<<'\n';
}
```

---

## 作者：freoepn (赞：0)

考虑每删除一行或一列相当于把这一行或这一列的红点全删除，将每一行每一列拆点，红点转换成行和列之间的边，删一行或一列相当于删掉一个有边相连的点和与他连着的所有边，可以发现所有联通块都可以被删的只剩一个点，算出可以删点联通块个数，枚举保留列的个数即可求出答案，方案直接以保留点为根往下删即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 1e4;
int c[kMaxN];
bool vis[kMaxN];
vector<int> v[kMaxN],e[kMaxN];
void dfs(int x, int y) {
  c[x] = y;
  //cout << x  << " "<< y << '\n';
  e[y].push_back(x);
  for (int i = 0; i < v[x].size(); i++) {
    if (c[v[x][i]] == 0) {
      dfs(v[x][i], y);
    }
  }
}
struct node{
  char c;
  int x,y;
};
  int n, m;
vector<node> u;
void DFS(int x,int fa){
  //cout << x <<" "<< fa << "!\n";
  vis[x] = 1;
  for(int i = 0;i < v[x].size();i++){
    if(vis[v[x][i]] == 0){
      DFS(v[x][i],x);
    }
  }
  if(fa){
    if(fa <= n){
      u.push_back((node){'Y',fa,x-n});
    }else{
      u.push_back((node){'X',x,fa-n});
    }
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0),cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      cin >> c;
      if (c == 'R') {
        v[i].push_back(j + n);
        v[j + n].push_back(i);
       // cout << i << ":"<< j + n << '\n';
      }
    }
  }
  int suma = 0, sumb = 0, sumc = 0;
  for (int i = 1; i <= n; i++) {
    suma += (!v[i].empty());
  }
  for (int i = n + 1; i <= n + m; i++) {
    sumb += (!v[i].empty());
  }
  for (int i = 1; i <= n + m; i++) {
    if (!c[i]&&!v[i].empty()) {
      dfs(i, ++sumc);
    }
  }
  int maxn = 1e9, p = 0;
  for (int i = 0; i <= sumc; i++) {
    if ((n - suma + i) * (m - sumb + (sumc - i)) < maxn) {
      maxn = (n - suma + i) * (m - sumb + (sumc - i));
      p = i;
    }
  }
  for(int i = 1;i <= p;i++){
    for(int j = 0;j < e[i].size();j++){
      if(e[i][j] <= n){
        DFS(e[i][j],0);
        break;
      }
    }
  }
  for(int i = p+1;i <= sumc;i++){
    for(int j = 0;j < e[i].size();j++){
      if(e[i][j] > n){
        DFS(e[i][j],0);
        break;
      }
    }
  }
  cout << u.size()<< '\n';;
  for(int i =0;i < u.size();i++){
    cout << u[i].c << " "<< u[i].x << " "<< u[i].y << '\n';
  }
  return 0;
}
```

---

## 作者：Inui_Sana (赞：0)

一个稍复杂一点的做法。

首先，若最后选了 $x$ 行 $y$ 列，则白色格子数为 $xm+yn-xy$。这个式子不太好求最值，所以考虑的方向就是枚举 $x$ 算 $y$ 最大值。

然后考虑如何判断一个方案是否合法，先套路化地在行和列之间连边，若 $(i,j)$ 为红色，则连 $(i,j+n)$ 的双向边，每条边都代表一个点，然后给每条边定向，若方向为 $u\to v$ 则表示，这条边操作的是 $u$，并且 $u$ 要比 $v$ 先进行操作，否则操作 $v$ 时会把这条边所代表的点染成白色。

于是就有结论：合法的操作中一定不会出现环，更进一步，会形成一棵内向树。若这个连通块不是一棵树，则任意选一棵生成树。并且根所代表的行/列不会被操作。也就是说，一个联通块内一定会有一个点不会被操作。同时又发现，我们不关心操作的行/列具体是哪些，只关心个数。

所以设一个联通块 $i$ 内代表行的点的个数为 $x_i$，列为 $y_i$。则对 $(x,y)$ 的贡献只可能是 $(x_i-1,y)$ 或 $(x_i,y_i-1)$，而且必须 $>0$。于是可以进行一个简单的背包 dp 解决。最后输出方案也是平凡的，只用对于每个连通块找到一个根，然后后序遍历生成树输出即可。

code：

```cpp
int n,m,k,b[N],dp[N][N],frm[N][N];
bool vis[N];
pii a[N];
char s[N];
int tot,head[N];
struct node{
	int to,nxt;
}e[M];
il void add(int u,int v){
	e[++tot]={v,head[u]},head[u]=tot;
}
struct DSU{
	int fa[N],f[N],g[N];
	void init(){
		rep(i,1,n+m){
			fa[i]=i;
			if(i<=n){
				f[i]=1;
			}else{
				g[i]=1;
			}
		}
	}
	int fd(int x){
		return fa[x]==x?x:fa[x]=fd(fa[x]);
	}
	il bool mrg(int x,int y){
		x=fd(x),y=fd(y);
		if(x==y){
			return 0;
		}
		fa[x]=y,f[y]+=f[x],g[y]+=g[x];
		return 1;
	}
}D;
void dfs(int u,int f){
	vis[u]=1;
	go(i,u){
		int v=e[i].to;
		if(vis[v]){
			continue;
		}
		dfs(v,u);
	}
	if(!f){
		return;
	}
	if(u<=n){
		printf("X %d %d\n",u,f-n);
	}else{
		printf("Y %d %d\n",f,u-n);
	}
}
void Yorushika(){
	read(n,m);
	D.init();
	rep(i,1,n){
		scanf("%s",s+1);
		rep(j,1,m){
			if(s[j]=='R'){
				if(D.mrg(i,j+n)){
					add(i,j+n),add(j+n,i);
				}
			}
		}
	}
	rep(i,1,n+m){
		if(D.fa[i]==i){
			a[++k]=Mp(D.f[i],D.g[i]);
			b[k]=i;
		}
	}
	mems(dp,-0x3f);
	dp[0][0]=0;
	rep(i,1,k){
		rep(j,0,n){
			dp[i][j]=dp[i-1][j];
		}
		rep(j,a[i].fi-1,n){
			if(a[i].fi){
				int w=dp[i-1][j-a[i].fi+1]+a[i].se;
				dp[i][j]=max(dp[i][j],w);
				if(dp[i][j]==w){
					frm[i][j]=1;
				}
			}
			if(j>=a[i].fi&&a[i].se){
				int w=dp[i-1][j-a[i].fi]+a[i].se-1;
				dp[i][j]=max(dp[i][j],w);
				if(dp[i][j]==w){
					frm[i][j]=2;
				}
			}
		}
	}
	int ans=0,p=0;
	rep(i,0,n){
		if(dp[k][i]>=0){
			int w=i*m+dp[k][i]*n-i*dp[k][i];
			ans=max(ans,w);
			if(ans==w){
				p=i;
			}
		}
	}
	cerr<<ans<<'\n';
	printf("%d\n",p+dp[k][p]);
	drep(i,k,1){
		if(!frm[i][p]){
			continue;
		}
		int u=0;
		if(frm[i][p]==1){
			rep(j,1,n){
				if(D.fd(j)==b[i]){
					u=j;break;
				}
			}
			dfs(u,0);
			p-=a[i].fi-1;
		}else{
			rep(j,n+1,n+m){
				if(D.fd(j)==b[i]){
					u=j;break;
				}
			}
			dfs(u,0);
			p-=a[i].fi;
		}
	}
	assert(!p);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

