# Tricolor Triangles

## 题目描述

You are given a simple undirected graph with $ n $ vertices and $ m $ edges. Edge $ i $ is colored in the color $ c_i $ , which is either $ 1 $ , $ 2 $ , or $ 3 $ , or left uncolored (in this case, $ c_i = -1 $ ).

You need to color all of the uncolored edges in such a way that for any three pairwise adjacent vertices $ 1 \leq a < b < c \leq n $ , the colors of the edges $ a \leftrightarrow b $ , $ b \leftrightarrow c $ , and $ a \leftrightarrow c $ are either pairwise different, or all equal. In case no such coloring exists, you need to determine that.

## 样例 #1

### 输入

```
4
3 3
1 2 1
2 3 2
3 1 -1
3 3
1 2 1
2 3 1
3 1 -1
4 4
1 2 -1
2 3 -1
3 4 -1
4 1 -1
3 3
1 2 1
2 3 1
3 1 2```

### 输出

```
1 2 3 
1 1 1 
1 2 2 3 
-1```

# 题解

## 作者：Cry_For_theMoon (赞：7)

你以为是神仙构造......然后

你被骗了。

手玩很久，没有发现启发性的性质，只有一个三条边颜色之和是 $3$ 的倍数。

然后我们就想办法在这个图上对三元环乱搞对吧，结果半天了啥都没搞出来...

换种思路，这玩意就是一个巨大模 $3$ 意义下线性方程组，就和线性异或方程组一样（就和正常高斯消元一样）搞就好了......

然后我们来算复杂度，如果有 $a$ 行 $b$ 列复杂度会是 $O(ab^2)$ 的，这里 $b=m$，但是 $a$ 是三元环总数。

（经典）结论：

$a$ 是 $O(m\sqrt{m})$ 级别的。

证明：度数和是 $O(m)$ 级别的，所以度数超过 $\sqrt{m}$ 的不超过 $O(\sqrt{m})$ 个，这部分的平方和不超过 $m\sqrt{m}$。

对于度数 $<\sqrt{m}$ 的点，其平方和最大值也为 $O(m\sqrt{m})$ 的。

所以总复杂度大概 $O(m^3\sqrt{m})=2^{28}$...... 但是显然跑不满这个东西，而且常数很小，加上 CF 神仙机子，所以正常高斯消元 300ms 干掉了......

似乎可以 bitset 优化的样子，但是是不是得首先三进制 bitset 之类的啊，不懂...

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXM=300,MAXN=260*32;
int n,m,g[70][70],idx[70][70],T,cnt;
int ans[MAXM];
int a[MAXN][MAXM];
void Swap(int x,int y){
	rep(j,1,m+1){
		swap(a[x][j],a[y][j]);
	}
}
void Add(int x,int y,int k){
	rep(j,1,m+1){
		a[x][j]=(a[x][j]+a[y][j]*k)%3;
	}
}
void E(int i,int j){
	if(i>cnt || j>m)return;
	int k=0;
	rep(r,i,cnt){
		if(a[r][j]){
			k=r;break;
		}
	}
	if(!k){E(i,j+1);return;}
	Swap(i,k);
	if(a[i][j]==2)Add(i,i,1);
	rep(r,i+1,cnt){
		if(a[r][j]==0)continue;
		Add(r,i,3-a[r][j]);
	}
	E(i+1,j+1);
}
void C(){
	per(r,cnt,1){
		int pos=0;
		rep(j,1,m){
			if(a[r][j]!=0){
				pos=j;
				break;
			}
		}
		if(!pos && a[r][m+1]!=0){
			printf("-1\n");
			return;
		}
		if(pos){
			ans[pos]=a[r][m+1];
			rep(rr,1,r-1){
				a[rr][m+1]=(a[rr][m+1]-ans[pos]*a[rr][pos]%3+3)%3;
				a[rr][pos]=0;
			}
		}
	}
	rep(i,1,m)if(!ans[i])ans[i]=3;
	rep(i,1,m)printf("%d ",ans[i]);printf("\n");
}
void solve(){
	cin>>n>>m;
	memset(g,0,sizeof g);
	memset(idx,0,sizeof idx);
	memset(ans,0,sizeof ans);
	rep(i,1,m){
		int u,v,w;cin>>u>>v>>w;
		g[u][v]=g[v][u]=w;
		idx[u][v]=idx[v][u]=i;
		if(w!=-1)ans[i]=w;
	}
	cnt=0;
	rep(i,1,n)rep(j,i+1,n)rep(k,j+1,n){
		if(g[i][j] && g[i][k] && g[k][j]){
			cnt++;
			int sum=0;
			if(g[i][j]!=-1)sum+=g[i][j];
			if(g[i][k]!=-1)sum+=g[i][k];
			if(g[j][k]!=-1)sum+=g[j][k];
			sum=(-sum%3+3)%3;
			a[cnt][m+1]=sum;
			if(g[i][j]==-1)a[cnt][idx[i][j]]=1;
			if(g[i][k]==-1)a[cnt][idx[i][k]]=1;
			if(g[j][k]==-1)a[cnt][idx[j][k]]=1;
		}
	}
	E(1,1);
	C();
	rep(i,0,cnt)rep(j,0,m+2)a[i][j]=0;
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}

```

---

## 作者：CmsMartin (赞：2)

[更好的阅读体验](http://cmsblog.top/archives/cf1616ftricolortriangles)

## 题目描述

[题目传送门](http://codeforces.com/problemset/problem/1616/F)

## 思路

发现一个边权为 $1,2,3$ 的三元环三边全部相同或不相同有一个共同的条件： 三边和为 $3$ 的倍数。

注意到这点就可以暴力把所有三元环找出来，然后根据题目要求列出方程，跑模 $3$ 意义下的高斯消元即可。

根据经典结论，三元环个数为 $\mathcal{O}(m\sqrt m)$ 的，时间复杂度为 $\mathcal{O}(m^3\sqrt m)$，能过。

## 代码

采用 高斯-约旦消元 实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 330, MAXM = 1e5;

int n, m, cnt, id;
int a[MAXM][MAXN], g[MAXN][MAXN], ans[MAXN];

void Get() {
	for (int i = id + 1; i <= cnt; i++) {
		if (a[i][m + 1]) {
			cout << -1 << "\n";
			return;
		}
	}
	for (int i = 1; i <= id; i++) {
		/*
		for (int j = i; !a[i][j]; j++) {
			ans[j] = a[i][m + 1];
		}
		*/
		int p = i;
		while (!a[i][p]) p++;
		ans[p] = a[i][m + 1];
	}

	for (int i = 1; i <= m; i++) cout << (ans[i] ? ans[i] : 3) << " ";
	cout << endl;
}


void solve() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		static int u, v, w;
		cin >> u >> v >> w;
		if (w != -1) {
			cnt++;
			a[cnt][i] = 1;
			a[cnt][m + 1] = w % 3;
		}
		g[u][v] = g[v][u] = i;
	}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			for (int k = j + 1; k <= n; k++)
				if (g[i][j] && g[j][k] && g[k][i]) {
					cnt++;
					a[cnt][g[i][j]] = a[cnt][g[j][k]] = a[cnt][g[k][i]] = 1;
				}
	for (int i = 1; i <= m; i++) {
		int now = 0;
		for (int j = id + 1; j <= cnt; j++) 
			if (a[j][i])
				now = j;
		if (!now) {
			ans[i] = 0;
			continue;
		}
		swap(a[++id], a[now]);
		if (a[id][i] != 1) for (int j = i; j <= m + 1; j++) a[id][j] = 3 - a[id][j];
		for (int j = 1; j <= cnt; j++) {
			if (id != j && a[j][i]) {
				int x = a[j][i];
				for (int k = i; k <= m + 1; k++) 
					a[j][k] = (a[j][k] - x * a[id][k] + 9) % 3;
			}
		}
	}
	Get();
	return;
}

void clear() {
	memset(g, 0, sizeof g);
	memset(a, 0, sizeof a);
	cnt = id = 0;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int _;
	cin >> _;
	while (_--) {
		clear();
		solve();
	}
	return 0;
}
```

---

## 作者：C6H14 (赞：0)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF1616F)

[My blog](https://www.luogu.com.cn/blog/128433/#)

集训时做到这题，~~前来水个咕值~~

## 思路

基础理论：[三元环](https://www.luogu.com.cn/blog/KingSann/fou-chang-yong-di-hei-ke-ji-san-yuan-huan-post)与[高斯消元](https://www.luogu.com.cn/problem/P3389)

当然这题只要知道三元环最多有 $O(m \sqrt m)$ 个以及用 Floyd 可以求所有三元环就行了。

显然题目对三元环的条件等价于三条边的 $c_i$ 和能被 $3$ 整除。

那么我们可以对每一个未确定的边都设一个未知数，对每一个三元环都列一条方程。

于是这个问题就转化成了高斯消元解模 $3$ 意义下的方程组，总时间复杂度为 $O(m^3 \sqrt m)$，显然几乎跑不满，实际会比这快一点。


---

