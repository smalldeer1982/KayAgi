# Number of Components

## 题目描述

You are given a matrix $ n \times m $ , initially filled with zeroes. We define $ a_{i, j} $ as the element in the $ i $ -th row and the $ j $ -th column of the matrix.

Two cells of the matrix are connected if they share a side, and the elements in these cells are equal. Two cells of the matrix belong to the same connected component if there exists a sequence $ s_1 $ , $ s_2 $ , ..., $ s_k $ such that $ s_1 $ is the first cell, $ s_k $ is the second cell, and for every $ i \in [1, k - 1] $ , $ s_i $ and $ s_{i + 1} $ are connected.

You are given $ q $ queries of the form $ x_i $ $ y_i $ $ c_i $ ( $ i \in [1, q] $ ). For every such query, you have to do the following:

1. replace the element $ a_{x, y} $ with $ c $ ;
2. count the number of connected components in the matrix.

There is one additional constraint: for every $ i \in [1, q - 1] $ , $ c_i \le c_{i + 1} $ .

## 样例 #1

### 输入

```
3 2 10
2 1 1
1 2 1
2 2 1
1 1 2
3 1 2
1 2 2
2 2 2
2 1 2
3 2 4
2 1 5```

### 输出

```
2
4
3
3
4
4
4
2
2
4```

# 题解

## 作者：Kubic (赞：3)

~~晚上打比赛有点困，没看到 $c_i\le c_{i+1}$，炸了。~~

进入正题：

发现每一次操作有可能会把两个连通块连起来，合为一个。

我们考虑与当前操作修改的格子相邻的四个格子，并将这四个格子所在的可以与当前格子合并的连通块都合并起来，然后统计答案。

发现这就是一个简单的并查集应用，于是直接套上模板，开心地发现样例都过不去..........

那这个做法错在哪里呢？相信很多人都已经发现了。

有一些修改操作可能会把一个连通块拆成多个连通块，但是上述做法并没有考虑这种情况。

但是并查集不能分裂，只能合并。

考虑将原矩阵 $A$ 中的某一点 $A_{i,j}$ 从 $x$ 变为 $y$，记新的矩阵为 $B$，我们发现：

$A\rightarrow B$ 对连通块总数产生的贡献等于 $B\rightarrow A$ 对连通块总数产生的贡献的相反数。（废话）

但是，我们可以利用这句废话，将分裂操作变为合并操作。

我们考虑以最终的矩阵为起点，倒着撤销修改操作。如果当前修改操作是将 $x$ 变为 $y$，那我们在撤销它的时候就是将 $y$ 变为 $x$。统计贡献时就只需要减去当前贡献就好了（由废话）。

我们这样就把分裂操作转变为了合并操作。

此时有人可能会问，我们到底在哪里用到了 $c_i\le c_{i+1}$？

注意，如果每一种数字的修改操作不是全部并在一起，此时如果我们按照数字来给操作排序，就不能保证操作顺序的正确性。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 305
#define Q 2000005
#define set(a,v) memset(a,v,sizeof(a))
const int X[]={1,-1,0,0},Y[]={0,0,1,-1};
int n,m,q,lim,ans[Q],fa[N*N],nw[N][N];struct Query {int id,x,y;};
vector<Query> q1[Q],q2[Q];
int f(int x,int y) {return (x-1)*m+y;}
bool chk(int x,int y) {return x>0 && x<=n && y>0 && y<=m;}
void clear(int n) {for(int i=1;i<=n;++i) fa[i]=i;}
int rt(int x) {return x==fa[x]?x:fa[x]=rt(fa[x]);}
bool merge(int x,int y) {x=rt(x);y=rt(y);if(x==y) return 0;fa[x]=y;return 1;}
int main()
{
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1,x,y,c;i<=q;++i)
	{
		scanf("%d %d %d",&x,&y,&c);lim=c;
		q2[nw[x][y]].push_back((Query) {i,x,y});
		q1[nw[x][y]=c].push_back((Query) {i,x,y});
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j)
		q2[nw[i][j]].push_back((Query) {0,i,j});set(nw,-1);
	for(int i=0,sz,id,x,y;i<=lim;++i)
	{
		sz=q1[i].size();if(!sz) continue;clear(n*m);
		for(int j=0;j<sz;++j)
		{
			id=q1[i][j].id;x=q1[i][j].x;y=q1[i][j].y;nw[x][y]=i;++ans[id];
			for(int k=0,gX,gY;k<4;++k)
			{
				gX=x+X[k];gY=y+Y[k];
				if(chk(gX,gY) && nw[gX][gY]==i) ans[id]-=merge(f(x,y),f(gX,gY));
			}
		}
	}set(nw,-1);
	for(int i=0,sz,x,y,id;i<=lim;++i)
	{
		sz=q2[i].size();if(!sz) continue;clear(n*m);
		for(int j=sz-1;j>=0;--j)
		{
			x=q2[i][j].x;y=q2[i][j].y;id=q2[i][j].id;nw[x][y]=i;--ans[id];
			for(int k=0,gX,gY;k<4;++k)
			{
				gX=x+X[k];gY=y+Y[k];
				if(chk(gX,gY) && nw[gX][gY]==i) ans[id]+=merge(f(x,y),f(gX,gY));
			}
		}
	}ans[0]=1;for(int i=1;i<=q;++i) printf("%d\n",ans[i]+=ans[i-1]);return 0;
}
```

---

## 作者：Sai0511 (赞：2)

这种题目第一眼想到的就是并查集。     
本质上就是加边/删边后的联通块个数问题。     
可以把增加的联通块和减少的联通块分开来算。  
一个小结论：$A$ 图变为 $B$ 图后增加的联通块个数等于 $B$ 图变为 $A$ 图后增加的联通块个数的相反数。（显然）。  
所以虽然并查集不支持分裂，但是我们可以逆序来做，从最终状态推到原始状态，每次的删边也就变成了加边。   
所以我们相当于只用处理加边的问题，容易发现某一点变为新的颜色后，增加的联通块个数就是 $1-M$，$M$ 表示和相邻点的并查集合并次数。（因为 $\forall c_i \leq c_{i+1}$ 所以一定正确）。     
最后我们就可以算出来 $\Delta_{ans}$($ans(i)$表示第 $i$ 时刻的答案)，这题就做完了。    
```cpp
#include <bits/stdc++.h>    

const int N = 305;
const int C = 2e6 + 10;
const int Q = 2e6 + 5;  
const int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};  
typedef std::pair<int, int> pii;

int n, m, i, j, k, lim, q;
std::vector<pii> add[C], del[C];
bool vst[N][N];
int a[N][N], pnt[N * N], ans[Q];

inline int ind(int x, int y) {
  return (x - 1) * m + y;  
}
inline pii unid(int z) {
  int y = z % m == 0 ? m : z % m;
  int x = (z - y) / m + 1;
  return std::make_pair(x, y);   
}
int find(int x) {
  return x == pnt[x] ? x : pnt[x] = find(pnt[x]);  
}
int merge(int x, int y) {
  int rx = find(x), ry = find(y);
  if (rx == ry) {
    return 0;
  }
  pnt[rx] = ry;
  return 1;  
}
void solve(std::vector<pii> &V, int sym) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      vst[i][j] = 0;
      pnt[ind(i, j)] = ind(i, j);   
    }
  }
  for (auto p : V) {
    int loc = p.first, id = p.second;
    pii P = unid(loc);
    int x = P.first, y = P.second, conb = 1;    
    vst[x][y] = 1;    
    for (int i = 0; i < 4; i++) {
      int nx = x + dir[i][0], ny = y + dir[i][1];
      if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && vst[nx][ny]) {
        conb -= merge(loc, ind(nx, ny));
      }
    }
    ans[id] += sym * conb;  
  }
}

int main() {
  scanf("%d %d %d", &n, &m, &q);
  for (int i = 1, x, y, c; i <= q; i++) {
    scanf("%d %d %d", &x, &y, &c); 
    if (i == q) {
      lim = c;
    }
    if (a[x][y] == c) {
      continue;
    }
    del[a[x][y]].push_back(std::make_pair(ind(x, y), i));
    add[a[x][y] = c].push_back(std::make_pair(ind(x, y), i));    
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      del[a[i][j]].push_back(std::make_pair(ind(i, j), 0));  
    }
  }
  for (int i = 0; i <= lim; i++) {
    std::reverse(del[i].begin(), del[i].end());
  }
  for (int i = 0; i <= lim; i++) {   
    solve(add[i], 1);
    solve(del[i], -1);  
  }
  ans[0] = 1;
  for (int i = 1; i <= q; i++) {
    ans[i] += ans[i - 1];
    printf("%d\n", ans[i]);
  }
  return 0;  
}
```

---

## 作者：ix35 (赞：1)

因为我实在太菜，这篇题解会在 #33 MLE，但是正确性是对的。

发现题目要维护连通块的个数，而且改变颜色其实就是支持加边和删边，所以我们可以考虑动态图。

先建边，最后来一波线段树分治+并查集即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2000010,MAXT=310;
int n,m,q,hd,x,y,z,f[MAXT*MAXT],d[MAXT*MAXT],ans[MAXN];
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}},col[MAXT][MAXT];
map < pair<int,int>,int > mp;
vector < pair<int,int> > v[MAXN*4];
pair <int,int> st[MAXN];
void modify (int p,int l,int r,int xl,int xr,pair<int,int> val) {
	if (xl>xr) {return;}
	if (xr<l||r<xl) {return;}
	if (xl<=l&&r<=xr) {v[p].push_back(val);return;}
	int mid=(l+r)>>1;
	modify(p<<1,l,mid,xl,xr,val),modify((p<<1)|1,mid+1,r,xl,xr,val);
	return;
}
int findr (int x) {return (x==f[x]?x:findr(f[x]));}
void dfs (int p,int l,int r,int siz) {
	int sz=v[p].size(),nw=hd;
	for (int i=0;i<sz;i++) {
		int x=findr(v[p][i].first),y=findr(v[p][i].second);
		if (x==y) {continue;}
		if (d[x]>d[y]) {swap(x,y);}
		st[++hd]=make_pair(x,d[y]);
		f[x]=y,d[y]=max(d[y],d[x]+1),siz--;
	}
	if (l==r) {
		ans[l]=siz;
	} else {
		int mid=(l+r)>>1;
		dfs(p<<1,l,mid,siz),dfs((p<<1)|1,mid+1,r,siz);
	}
	while (hd>nw) {
		int x=st[hd].first,z=st[hd].second;
		d[f[x]]=z;
		f[x]=x,hd--;
	}
	return;
}
int hs (int x,int y) {return (x-1)*m+y;}
int chk (int x,int y) {
	if (x<1||y<1||x>n||y>m) {return 0;}
	return 1;
}
int main () {
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=n*m;i++) {f[i]=i;}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			for (int k=0;k<=3;k++) {
				int x=i,y=j;
				int dx=x+dir[k][0],dy=y+dir[k][1];
				if (chk(dx,dy)) {
					int hs1=hs(dx,dy),hs2=hs(x,y);
					if (hs1<hs2) {swap(hs1,hs2);}
					mp[make_pair(hs1,hs2)]=1;
				}
			}
		}
	}
	for (int i=1;i<=q;i++) {
		scanf("%d%d%d",&x,&y,&z);
		if (col[x][y]==z) {continue;}
		for (int j=0;j<=3;j++) {
			int dx=x+dir[j][0],dy=y+dir[j][1];
			if (chk(dx,dy)) {
				int hs1=hs(dx,dy),hs2=hs(x,y);
				if (hs1<hs2) {swap(hs1,hs2);}
				if (col[dx][dy]==col[x][y]) {
					int tmp=mp[make_pair(hs1,hs2)];
					modify(1,1,q,tmp,i-1,make_pair(hs1,hs2));
				}
				if (col[dx][dy]==z) {
					mp[make_pair(hs1,hs2)]=i;
				}
			}
		}
		col[x][y]=z;
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			for (int k=0;k<=3;k++) {
				int x=i,y=j;
				int dx=x+dir[k][0],dy=y+dir[k][1];
				if (chk(dx,dy)) {
					int hs1=hs(dx,dy),hs2=hs(x,y);
					if (hs1<hs2) {swap(hs1,hs2);}
					if (col[x][y]==col[dx][dy]) {
						modify(1,1,q,mp[make_pair(hs1,hs2)],q,make_pair(hs1,hs2));
					}
				}
			}
		}
	}
	dfs(1,1,q,n*m);
	for (int i=1;i<=q;i++) {
		printf("%d\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：Mashu77 (赞：0)

我们将一次修改操作（将 
$a_{
x
,
y}$
 从 
$z$
 改为 
$w$）分为两步考虑：在
$w$
 的导出子图中加入 
$a_{
x
,
y}$，在 
$z$
 的导出子图中删除 
$a_{
x
,
y}$。加入操作可以用并查集，但删除操作不好处理。但由于此题的特殊性质，$z$
 一定小于 
$w$
（这里不考虑相等的情况）。我们考虑规避删除。

逆着做一遍。那么就是将 
$w$
 改为 
$z$。此时，在 
$z$
 的导出子图中加入 
$a_{
x
,
y}$
 增加的连通块个数与 上段操作中在 
$z$
 的导出子图中删除 
$a_{
x
,
y}$
 增加的连通块个数互为相反数。正确性易证。于是此题得解。

---

