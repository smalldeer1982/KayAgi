# [ABC344F] Earn to Advance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc344/tasks/abc344_f

縦 $ N $ 行横 $ N $ 列のグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,j) $ と表します。

高橋君は最初マス $ (1,1) $ におり、所持金は $ 0 $ です。

高橋君はマス $ (i,j) $ にいるとき、$ 1 $ 回の**行動**で以下のいずれかを行うことができます。

- 同じマスにとどまり、所持金を $ P_{i,j} $ 増やす。
- 所持金から $ R_{i,j} $ 払ってマス $ (i,j+1) $ に移動する。
- 所持金から $ D_{i,j} $ 払ってマス $ (i+1,j) $ に移動する。

所持金が負になる移動、グリッドの外に出る移動はできません。

高橋君が最適に行動したとき、何回の行動でマス $ (N,N) $ にたどり着くことができますか。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 80 $
- $ 1\ \leq\ P_{i,j}\ \leq\ 10^9 $
- $ 1\ \leq\ R_{i,j},D_{i,j}\ \leq\ 10^9 $
- 入力は全て整数である

### Sample Explanation 1

!\[図\](https://img.atcoder.jp/abc344/ec8d878cbf8ad189f178d8b5a3262974.png) 以下のようにして $ 8 $ 回の行動でマス $ (3,3) $ にたどり着くことができます。 - マス $ (1,1) $ にとどまり、所持金を $ 1 $ 増やす。所持金は $ 1 $ になる。 - 所持金から $ 1 $ 払ってマス $ (2,1) $ に移動する。所持金は $ 0 $ になる。 - マス $ (2,1) $ にとどまり、所持金を $ 3 $ 増やす。所持金は $ 3 $ になる。 - マス $ (2,1) $ にとどまり、所持金を $ 3 $ 増やす。所持金は $ 6 $ になる。 - マス $ (2,1) $ にとどまり、所持金を $ 3 $ 増やす。所持金は $ 9 $ になる。 - 所持金から $ 4 $ 払ってマス $ (2,2) $ に移動する。所持金は $ 5 $ になる。 - 所持金から $ 3 $ 払ってマス $ (3,2) $ に移動する。所持金は $ 2 $ になる。 - 所持金から $ 2 $ 払ってマス $ (3,3) $ に移動する。所持金は $ 0 $ になる。

## 样例 #1

### 输入

```
3
1 2 3
3 1 2
2 1 1
1 2
4 3
4 2
1 5 7
5 3 3```

### 输出

```
8```

## 样例 #2

### 输入

```
3
1 1 1
1 1 1
1 1 1
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000
1000000000 1000000000 1000000000
1000000000 1000000000 1000000000```

### 输出

```
4000000004```

# 题解

## 作者：Otue (赞：18)

update at 2023/3/10：更新了一些正确性说明。

场切。贪心+动态规划。

先把图建出来，可以将问题转化为在图上行走，抽象为如下问题（这是原题的严格强化）：

> 一个人在一张有向图的 $1$ 号结点，他要去到 $n$ 结点。每条边 $(a_i,b_i)$ 有边权 $s_i$，表示走过这条边需要花 $s_i$ 元。这个人一开始有 $0$ 元，到了一个点 $u$，他可以进行若干次停留，每次停留收获 $w_u$ 元。问到达 $n$ 的最小停留次数，并将答案加上 $2\times n-2$。若无解输出 ```-1```。

为什么答案要加 $2\times n-2$，因为我们只算了停留次数。但是中间行走的步数是确定的为 $2\times n-2$。


考虑贪心，考虑从 $u$ 点走到 $v$ 点（$u,v$ 不一定是一条边），且在 $u,v$ 两点都赚钱停留。如果 $u$ 停留一次赚的钱比 $v$ 停留一次赚的钱多，那么不如不在 $v$ 这里停留（不如在 $u$ 点先把钱赚了）。那么就先将 $w_i$ 从小到大排序，**路径中停留的点的 $w_i$ 是递增关系**，如果当前点走不到比它更赚钱的点，直接走到 $n$ 号点。

---

预处理出 $d_{i,j}$ 代表 $i$ 走到 $j$ 的最小路径长度（边权）。

从 $u$ 号点赚钱完毕走到 $v$ 去赚钱，是把钱赚够就走（赚够代表当前的钱可以支付 $d_{u,v}$），还是可以在 $u$ 号点多赚一点，并使得到达 $v$ 号点时钱更多？

答案是赚够就走，因为在 $u$ 点多赚一点钱，不如走到 $v$ 号点去赚，因为 $w_u<w_v$。


---

既然赚够就走，那么 $u$ 到 $v$ 的路径，到达 $v$ 点后有许多种状态，用二元组 $(f,g)$ 表示。$f$ 代表到达 $v$ 点后停留次数，$g$ 代表到达 $v$ 点后所剩的钱。到底哪种方案更优？停留次数 $f$ 最小的更优？赚的钱 $g$ 越多更优？停留次数越少的答案越少，赚的钱越多后面就能越少停留。

考虑 $(f_1,g_1)$ 和 $(f_2,g_2)$ 两种状态，若 $f_1<f_2$ 且 $g_1<g_2$，此时我们怎么判断谁更优？

事实上，$(f_1,g_1)$ 只需要到达 $v$ 后再多停留一次，所剩余的钱就比 $g_2$ 多。

因为 $0\leq g_1< g_2\leq w_u<w_v$（$g_1\leq g_2\leq w_u$ 是因为赚够就走），所以 $g_1+w_v>g_2$。这就说明 $(f_1,g_1)$ 优于 $(f_2,g_2)$。

综上：停留次数越少，方案越优。如果停留次数相等，则剩的钱越多越优。

于是直接定义 $(f_i,g_i)$ 代表 $i$ 号点的最少停留次数与最多赚钱数，按照 w 从小到大的顺序转移即可。

复杂度 $O(n^4)$。但是，这道题不排序也是对的，可能本题是一个拓扑图的缘故。

```c++
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define int long long
const int N = 6405;

int T, n, m, p, w[N], f[N], g[N], st[N];
// f_i,g_i 即为i号点(最少停留次数，最多赚钱数)
int dist[N][N]; 
vector<pair<int, int> > G[N];

struct edge {
	int x, id;
}a[N];
bool cmp(edge x, edge y) { return x.x < y.x; }

void dijstra(int s) {
	priority_queue<PII, vector<PII>, greater<PII> > q;
	memset(st, 0, sizeof st);
	dist[s][s] = 0; q.push({0, s});
	while (q.size()) {
		auto t = q.top();
		q.pop();
		int u = t.second;
		if (st[u]) continue;
		st[u] = 1;
		for (auto e : G[u]) {
			auto v = e.first, d = e.second;
			if (dist[s][v] > dist[s][u] + d) {
				dist[s][v] = dist[s][u] + d;
				q.push({dist[s][v], v});
			}
		}
	}
}

void change(int x, int nf, int ng) {
	if (nf < f[x]) f[x] = nf, g[x] = ng;
	else if (nf == f[x] && ng > g[x]) f[x] = nf, g[x] = ng;
}

int get(int x, int y) {
	return (x - 1) * n + y;
} 

signed main() {
	memset(dist, 0, sizeof dist);
	cin >> n; p = 0;
	for (int i = 1; i <= n * n; i++) {
		for (int j = 1; j <= n * n; j++) {
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = 1e18;
		}
	}
	for (int i = 1; i <= n * n; i++) cin >> w[i], a[i].x = w[i], a[i].id = i;
	sort(a + 1, a + n * n + 1, cmp);
	a[n * n + 1].x = 0, a[n * n + 1].id = n * n; // 要加入 n 号点，因为如果一个点走不到比它更赚钱的点，直接走到 n 好点
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n - 1; j++) {
			int x;
			cin >> x;
			G[get(i, j)].push_back({get(i, j + 1), x}); 
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			int x;
			cin >> x;
			G[get(i, j)].push_back({get(i + 1, j), x}); 
		}
	}
	for (int i = 1; i <= n * n; i++) {
		dijstra(i); // 预处理最短路，当然，这是一个拓扑图，直接递推也可以
	}
	for (int i = 1; i <= n * n; i++) f[i] = 1e18, g[i] = 0;
	f[1] = 0, g[1] = p;
	for (int i = 1; i <= n * n; i++) {
		for (int j = i + 1; j <= n * n + 1; j++) {
			int x = a[i].id, y = a[j].id;
			if (dist[x][y] == 1e18) continue;
			if (g[x] >= dist[x][y]) change(y, f[x], g[x] - dist[x][y]); // 如果钱足够，直接走
			else {
				int t = dist[x][y] - g[x];
				int k = (t + w[x] - 1) / w[x];
				change(y, f[x] + k, g[x] + k * w[x] - dist[x][y]);
			}
		}
	}
	if (f[n * n] <= 3e12) cout << f[n * n] + 2 * n - 2 << endl;
	else puts("-1"); 
}
```

---

## 作者：cjh20090318 (赞：9)

感觉不难，但是没能场切。

## 题意

[题目翻译](https://www.luogu.com.cn/problem/AT_abc344_f)非常清晰。

## 分析

观察到最优路径上停留获取金币点的 $P$ 一定是单调递增的，正确性显然。

简单证明一下，设停留获取金币点的序列为 $p$，如果存在 $i<j,P_{p_i}>P_{p_j}$，那么就可以在 $p_i$ 的位置上花比 $p_j$ 更少的步数来获取在 $p_j$ 上获得同样多的钱。

设 $h_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 所需的最小步数，$q_{i,j}$ 表示从 $(1,1)$ 走到 $(i,j)$ 步数的最小情况下剩余最多前的数量，$g_{i,j,k,l}$ 表示从 $(k,l)$ 到 $(i,j)$ 需要最少钱的数量（需要保证 $k \le i,l \le j$）。

$g$ 非常好求，递推即可。然后就可以写出 $h$ 的转移方程：
$$
h_{i,j} = \min\limits_{k \le i,l \le j}
\left( h_{k,l} + \left\lceil\dfrac{\max(g_{i,j,k,l}-q_{k,l},0)}{P_{k,l}}\right\rceil + i-k + j-l \right)
$$
最终的答案就是 $h_{n,n}$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
int n;
int p[88][88],r[88][88],d[88][88];//分别对应题目中的 P,R,D。
LL g[88][88][88][88],h[88][88],q[88][88];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++) scanf("%d",&p[i][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<n;j++) scanf("%d",&r[i][j]);
	for(int i=1;i<n;i++)for(int j=1;j<=n;j++) scanf("%d",&d[i][j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		memset(g[i][j],0x3f,sizeof(g[i][j]));
		g[i][j][i][j]=0;//从 (i,j) 往 (k,l) 逆序递推。
		for(int k=i;k>0;--k)for(int l=j-(k==i);l>0;--l)
			g[i][j][k][l]=min(g[i][j][k+1][l]+d[k][l],g[i][j][k][l+1]+r[k][l]);//从下方和右方转移。
	}
	memset(h,0x3f,sizeof h);
	h[1][1]=r[1][1]=0;
	for(int i=1;i<=n;i++)for(int j=1+(i==1);j<=n;j++){
		for(int k=1;k<=i;k++)for(int l=1;l<=j;l++){//枚举最后停留获取钱的位置。
			LL t=max((g[i][j][k][l]-q[k][l]+p[k][l]-1)/p[k][l],0ll);//需要停留的步数，向上取整使用鸽巢原理转为向下取整。
			if(h[k][l]+t+i-k+j-l<h[i][j])
				h[i][j]=h[k][l]+t+i-k+j-l,//更新最短步数。
				q[i][j]=t*p[k][l]+q[k][l]-g[i][j][k][l];//更新剩余的钱。
			else if(h[i][j]==h[k][l]+t+i-k+j-l && t*p[k][l]+q[k][l]-g[i][j][k][l]>q[i][j])//步数相等就求钱剩的最多。
				q[i][j]=t*p[k][l]+q[k][l]-g[i][j][k][l];
		}
	}
	printf("%lld\n",h[n][n]);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：6)

## 分析

这把开挂了。这里给一个通俗易懂的题解。

看到 $n \le 80$，不难想到是 $O(n^4)$ 的。因为我们走到相邻格子会花费 $r_{i,j}$ 或 $d_{i,j}$ 的代价，所以根据贪心，可以想到状态函数在 $i,j$ 的基础上再增加两维：$f_{i,j,k,w}$ 表示走到 $(i,j)$，且经过 $p_{x,y}$ 最大的点为 $p_{k,w}$ 时的最小时间与最大剩余金币。时间的优先级大于剩余金币优先级。然后就是暴力 DP。通过刷表法枚举 $i,j,k,w$。

对于向右走的情况，若当前最大剩余金币不小于 $r_{i,j}$，我们显然是没必要在原地等待的，直接走过去。花费 $1$ 的时间。若当前最大剩余金币小于 $r_{i,j}$，找到最小的时间 $t$，使得最大剩余金币 $s$ 满足 $s+p_{k,w} \times t \ge r_{i,j}$，转换一下式子就是：$t = \lceil \frac{r_{i,j}-s}{p_{k,w}}\rceil$。花费 $1+t$ 时间。**在走到相邻点时需要将 $p_{w,k}$ 的大小与 $p_{i+1,j}$ 的大小进行比较，更新后两维。**

向下走的情况同理。答案就是在所有 $p_{i,j}$ 为最大的 $p_{x,y}$ 时，$f_{n,n,i,j}$ 所需最小时间的最小值。复杂度 $O(n^4)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=105;
int n,p[N][N];
int r[N][N],d[N][N];
pii f[N][N][N][N];

il pii Min(pii a,pii b){
	pii ans={0,0};
	if(a.x<b.x) ans=a;
	else if(b.x<a.x) ans=b;
	else if(a.y>b.y) ans=a;
	else ans=b;
	return ans;
}

il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=n;++j)
		p[i][j]=rd;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<n;++j)
		r[i][j]=rd;
	for(re int i=1;i<n;++i)
	for(re int j=1;j<=n;++j)
		d[i][j]=rd;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=n;++j)
	for(re int k=1;k<=n;++k)
	for(re int w=1;w<=n;++w)
		f[i][j][k][w]={1e18,0};
	f[1][1][1][1]={0,0};
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=n;++j)
	for(re int k=1;k<=i;++k)
	for(re int w=1;w<=j;++w){
		//往右边走
		if(j<n){
			int cha=f[i][j][k][w].y-r[i][j];
			int k1=k,w1=w;
			if(p[i][j+1]>p[k][w]) k1=i,w1=j+1;
			if(cha>=0) f[i][j+1][k1][w1]=Min(f[i][j+1][k1][w1],{f[i][j][k][w].x+1,cha});
			else{
				int cha2=r[i][j]-f[i][j][k][w].y;
				int bushu=(cha2-1)/p[k][w]+1;
				cha=bushu*p[k][w]+f[i][j][k][w].y-r[i][j];
				f[i][j+1][k1][w1]=Min(f[i][j+1][k1][w1],{f[i][j][k][w].x+bushu+1,cha});
			}
		}
		//往下边走 
		if(i<n){
			int cha=f[i][j][k][w].y-d[i][j];
			int k1=k,w1=w;
			if(p[i+1][j]>p[k][w]) k1=i+1,w1=j;
			if(cha>=0) f[i+1][j][k1][w1]=Min(f[i+1][j][k1][w1],{f[i][j][k][w].x+1,cha});
			else{
				int cha2=d[i][j]-f[i][j][k][w].y;
				int bushu=(cha2-1)/p[k][w]+1;
				cha=bushu*p[k][w]+f[i][j][k][w].y-d[i][j];
				f[i+1][j][k1][w1]=Min(f[i+1][j][k1][w1],{f[i][j][k][w].x+bushu+1,cha});
			}
		}
	}
	int minn=1e18;
	for(re int i=1;i<=n;++i)
	for(re int j=1;j<=n;++j)
		minn=min(minn,f[n][n][i][j].x);
	printf("%lld\n",minn);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

## 作者：OldDriverTree (赞：4)

# Solution
可以发现这道题很像 [CSP-J 2023 公路](https://www.luogu.com.cn/problem/P9749)，只是由一维改为二维，但是改为二维后最大值无法确定，考虑 $\texttt{DP}$，用那道题的做法，来设计 $\texttt{DP}$ 的状态。

设 $f_{i,j,x,y}$ 表示从 $(1,1)$ 到 $(i,j)$，途中经过的 $P$ 最大的位置为 $(x,y)$ 时的最小步数，$g_{i,j,x,y}$ 表示这种情况下走到 $(i,j)$ 时剩余的钱数最多是多少。

转移到相邻的方格就选择在 $(x,y)$ 上停留，直到钱数大于等于 $R_{i,j+1}$ 或 $D_{i+1,j}$，状态转移方程就不放了，答案为 $\min\limits_{i=1}^N\max\limits_{j=1}^N f_{N,N,i,j}$，时间复杂度为 $O(N^4)$。

# Code
```c++
#include<bits/stdc++.h>
#define P pair<int,int>
#define int long long
using namespace std;
const int N=81;
int f[N][N][N][N];
int g[N][N][N][N];
int d[N][N],r[N][N];
int n,w[N][N];

int read() {
	int x=0; bool f=true; char c=0;
	while (!isdigit(c) ) f&=(c!='-'),c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return f?x:-x;
}
main()
{
	n=read();
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) w[i][j]=read();
	for (int i=1;i<=n;i++) for (int j=1;j<n;j++) r[i][j]=read();
	for (int i=1;i<n;i++) for (int j=1;j<=n;j++) d[i][j]=read();
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int x=1;x<=i;x++)
				for (int y=1;y<=j;y++)
					f[i][j][x][y]=2e14,g[i][j][x][y]=-2e14;
	
	f[1][1][1][1]=g[1][1][1][1]=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int x=1;x<=i;x++)
				for (int y=1;y<=j;y++) {
					if (i<n&&w[x][y]>w[i+1][j]) {
						int t=max(0ll,(d[i][j]-g[i][j][x][y]+w[x][y]-1)/w[x][y]),v=(g[i][j][x][y]+t*w[x][y])-d[i][j];
						if (f[i+1][j][x][y]>f[i][j][x][y]+t+1||(f[i+1][j][x][y]==f[i][j][x][y]+t+1&&g[i+1][j][x][y]<v) ) f[i+1][j][x][y]=f[i][j][x][y]+t+1,g[i+1][j][x][y]=v;
					}
					else if (i<n) {
						int t=max(0ll,(d[i][j]-g[i][j][x][y]+w[x][y]-1)/w[x][y]),v=(g[i][j][x][y]+t*w[x][y])-d[i][j];
						if (f[i+1][j][i+1][j]>f[i][j][x][y]+t+1||(f[i+1][j][i+1][j]==f[i][j][x][y]+t+1&&g[i+1][j][i+1][j]<v) ) f[i+1][j][i+1][j]=f[i][j][x][y]+t+1,g[i+1][j][i+1][j]=v;
					}
					if (j<n&&w[x][y]>w[i][j+1]) {
						int t=max(0ll,(r[i][j]-g[i][j][x][y]+w[x][y]-1)/w[x][y]),v=(g[i][j][x][y]+t*w[x][y])-r[i][j];
						if (f[i][j+1][x][y]>f[i][j][x][y]+t+1||(f[i][j+1][x][y]==f[i][j][x][y]+t+1&&g[i][j+1][x][y]<v) ) f[i][j+1][x][y]=f[i][j][x][y]+t+1,g[i][j+1][x][y]=v;
					}
					else if (j<n) {
						int t=max(0ll,(r[i][j]-g[i][j][x][y]+w[x][y]-1)/w[x][y]),v=(g[i][j][x][y]+t*w[x][y])-r[i][j];
						if (f[i][j+1][i][j+1]>f[i][j][x][y]+t+1||(f[i][j+1][i][j+1]==f[i][j][x][y]+t+1&&g[i][j+1][i][j+1]<v) ) f[i][j+1][i][j+1]=f[i][j][x][y]+t+1,g[i][j+1][i][j+1]=v;
					}
				}
	int ans=LONG_LONG_MAX;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			ans=min(ans,f[n][n][i][j]);
	
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：kczw (赞：2)

# 题意
给定一由 $N\times N$ 个点组成的图。

对于点 $(i,j)$，你可以选择一下三种操作。
- 留在点 $(i,j)$，并获得 $P_{i,j}$ 钱。
- 前往点 $(i,j+1)$，需消耗 $R_{i,j}$ 钱。
- 前往点 $(i+1,j)$，需消耗 $D_{i,j}$ 钱。

不可移动出图外，钱不可为负。

问，最少需要多少次操作可以从 $(1,1)$ 抵达 $(N,N)$。
# 思路
一眼动态规划，然后开始分析。

易知，对于点 $(i,j)$ 来说，用一次操作次数换来的最多的钱并非一定是 $P_{i,j}$，而是从点 $(1,1)$ 开始到点 $(i,j)$ 的路径上所有点 $P$ 的最大值。

通俗点解释，令 $V$ 是所有经过点的坐标集合，对于点 $(i,j)$ 一次操作次数可以换来的最多的钱为 $\max_{x,y}^VP_{x,y}$。

有如上结论，便易得在 $(1,1)$ 到 $(N,N)$ 的路径上最优操作流程应为在目前 $P$ 值最大点刷钱，等刚好获得足够的钱前往下一个 $P$ 值更大的点时再前往，然后重复上述过程。

于是，对于点 $(i,j)$，可以枚举这个刷钱点，然后可以转移状态 dp 出从点 $(1,1)$ 到达点 $(i,j)$ 的最小操作数了。但实际实现的过程中会发现为了完成转移，实际上还需要存储一下到达点 $(i,j)$ 后余额。

可能有人会疑惑，现在状态有二，一为操作数，二为余额，那么比较时怎样的状态才算最优呢？此处比较的余额是在上一刷钱点刷到刚好足够到达此点后剩余的，那么即使两个比较的状态的操作次数刚好差一，操作次数少的一方用这一次操作次数用于刷钱后，钱也会比操作次数多的另一个状态多，所以毋庸置疑的，操作数越小越优，操作数相同再比较余额。

有了上述分析后，代码大概就可以写出来了。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=85,inf=1e18;
int n,p[N][N],r[N][N],d[N][N],f[N][N][2],dis[N][N],mk,tmm,ov;
main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		scanf("%lld",&p[i][j]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<n;j++)
		scanf("%lld",&r[i][j]);
	for(int i=1;i<n;i++)
	for(int j=1;j<=n;j++)
		scanf("%lld",&d[i][j]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		f[i][j][0]=inf;
	f[1][1][0]=0;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		for(int x=1;x<=i;x++)
		for(int y=1;y<=j;y++)
			dis[x][y]=inf;
		dis[i][j]=0;
		for(int x=i;x>=1;x--)
		for(int y=j;y>=1;y--){
			if(y<j)dis[x][y]=min(dis[x][y],r[x][y]+dis[x][y+1]);
			if(x<i)dis[x][y]=min(dis[x][y],d[x][y]+dis[x+1][y]);
          		//计算刷钱点到达当前点最短距
			mk=(int)ceil(max(0ll,dis[x][y]-f[x][y][1])/p[x][y]);
        		//最少刷钱次数
			tmm=f[x][y][0]+mk+i+j-x-y;
          		//用在路上的操作次数
			ov=f[x][y][1]+mk*p[x][y]-dis[x][y];
          		//计算余额
			if(tmm<f[i][j][0]||(tmm==f[i][j][0]&&ov>f[i][j][1])){
				f[i][j][0]=tmm;
				f[i][j][1]=ov;
			}
          		//比较转移
		}
	}
	printf("%lld",f[n][n][0]);
}
```

---

## 作者：Phartial (赞：1)

考虑枚举最后一个停留的位置 $(x,y)$，假设我们已经知道了从 $(1,1)$ 走到 $(x,y)$ 的最优路径（步数 $s$ 与剩的钱 $c$），就可以简单的算出来需要在 $(x,y)$ 停留多久才能直接走到 $(N,N)$。

然后“从 $(1,1)$ 走到 $(x,y)$ 的最优路径”是一个子问题，直接 dp 即可。

```cpp
#include <iostream>

using namespace std;
using LL = long long;
using Pll = pair<LL, LL>;

const int kN = 82;

int n;
LL p[kN][kN], r[kN][kN], d[kN][kN], b[kN][kN];
Pll f[kN][kN];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> p[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < n; ++j) {
      cin >> r[i][j];
    }
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cin >> d[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      f[i][j] = {1e18, 0};
    }
  }
  f[1][1] = {0, 0};
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i == 1 && j == 1) {
        continue;
      }
      for (int x = 1; x <= i + 1; ++x) {
        for (int y = 1; y <= j + 1; ++y) {
          b[x][y] = 1e18;
        }
      }
      b[i][j] = 0;
      for (int x = i; x >= 1; --x) {
        for (int y = j; y >= 1; --y) {
          if (x == i && y == j) {
            continue;
          }
          b[x][y] = min(b[x][y + 1] + r[x][y], b[x + 1][y] + d[x][y]);
        }
      }
      for (int x = 1; x <= i; ++x) {
        for (int y = 1; y <= j; ++y) {
          if (x == i && y == j) {
            continue;
          }
          LL c = f[x][y].second, v = max(0LL, (b[x][y] + c + p[x][y] - 1) / p[x][y]);
          f[i][j] = min(f[i][j], {f[x][y].first + v + (i - x) + (j - y), b[x][y] + c - p[x][y] * v});
        }
      }
    }
  }
  cout << f[n][n].first;
  return 0;
}
```

---

## 作者：Kevin911 (赞：0)

赛时想出了正解，时间不够了，以此纪念。
## 思路
想必第一眼就能看出是 dp 吧，考虑定义状态和转移方程。
预处理 $dp1[k][p][i][j]$ 表示 $(k,p)$ 到 $(i,j)$ 的最少花费，$dp2[i][j][0]$ 表示到 $(i,j)$ 的最少操作次数，$dp2[i][j][1]$ 表示到 $(i,j)$ 最少操作次数下能省下的最多的钱，枚举从节点 $(k,p)$ 来的，如果 $(k,p)$ 处的节余满足 $(k,p)$ 到 $(i,j)$ 的花费，就不用再等了，否则算出至少要在 $(k,p)$ 等多久。而转移条件就是操作次数更少或者操作次数相等，节余更多。最终的答案就是 $(1,1)$ 到 $(i,j)$ 的最少操作次数加上带着节余的情况下等待完直接从 $(i,j)$ 到 $(n,n)$ 的和的最小值。

这里有一个小优化，如果 $(i,j)$ 的等待效益还不如 $(p,k)$ 就不用转移了，因为直接在 $(p,k)$ 等待还更优。

时间复杂度是 $O(n^4)$，代码如下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int p1[81][81],r[81][81],d[81][81],dp1[81][81][81][81],dp2[81][81][2];
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>p1[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<n;j++) cin>>r[i][j];
	for(int i=1;i<n;i++)
		for(int j=1;j<=n;j++) cin>>d[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			memset(dp1[i][j],0x7f,sizeof(dp1[i][j]));
			dp1[i][j][i][j]=0;
			for(int k=i;k<=n;k++)
				for(int p=j;p<=n;p++)
					if(k!=i||p!=j) dp1[i][j][k][p]=min(dp1[i][j][k-1][p]+d[k-1][p],dp1[i][j][k][p-1]+r[k][p-1]);
		}
	memset(dp2,0x7f,sizeof(dp2));
	dp2[1][1][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) dp2[i][j][1]=0;
	int ans=1e18;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i==1&&j==1) continue;
			for(int k=1;k<=i;k++)
				for(int p=1;p<=j;p++)
				{
					if((k==i&&p==j)||p1[i][j]<p1[k][p]) continue;
					int x=0;
					if(dp1[k][p][i][j]>dp2[k][p][1]) x=(dp1[k][p][i][j]-dp2[k][p][1]+p1[k][p]-1)/p1[k][p];
					if(dp2[i][j][0]>dp2[k][p][0]+x+i-k+j-p)
					{
						dp2[i][j][0]=dp2[k][p][0]+x+i-k+j-p;
						dp2[i][j][1]=dp2[k][p][1]+x*p1[k][p]-dp1[k][p][i][j];
					}
					else if(dp2[i][j][0]==dp2[k][p][0]+x+i-k+j-p&&dp2[i][j][1]<dp2[k][p][1]+x*p1[k][p]-dp1[k][p][i][j])
					{
						dp2[i][j][0]=dp2[k][p][0]+x+i-k+j-p;
						dp2[i][j][1]=dp2[k][p][1]+x*p1[k][p]-dp1[k][p][i][j];
					}
				}
			int x=0;
			if(dp1[i][j][n][n]>dp2[i][j][1]) x=(dp1[i][j][n][n]-dp2[i][j][1]+p1[i][j]-1)/p1[i][j];
			ans=min(ans,dp2[i][j][0]+x+n*2-i-j);
		}
	cout<<ans;
}
```

---

## 作者：Liyunze123 (赞：0)

# 1.题意
有一个 $N \times N$ 的正方形，你可以选择花费 $b_{i,j}$ 元钱往右走一格，或者花费 $c_{i,j}$ 元往下走一格。你也可以不走，赚 $a_{i,j}$ 元钱。问你最少需要多少此操作才能从左上角走到右下角（初始钱为 $0$）？
# 2.解题思路
设 $dp_{i,j}$ 是走到 $(i,j)$ 时的最小操作次数，$m_{i,j}$ 为走到 $(i,j)$ 时，满足操作次数最少时钱的最大值，$s_{i,j,k,l}$ 为 $(i,j)$ 走到 $(k,l)$ 的最短路。

求 $dp_{i,j}$ 时，枚举 $(k,l)$，就是最后一次选择赚钱时你的位置（$k \le i,l \le j$ 并且 $(i,j)$ 和 $(k,l)$ 不是一个点）。

设定变量 $t$，表示最后一次在 $k,l$ 选择赚钱，花费的步数。$t = dp_{k,l} + f(s_{k,l,i,j}-m_{k,l},a_{k,l}) + i - k + j - l$。其中 $f$ 为向上取整函数。

另设变量 $p$，表示最后一次在 $k,l$ 选择赚钱，剩下的钱数。$p = f(s_{k,l,i,j} - m_{k,l},a_{k,l}) \times a_{k,l} - s_{k,l,i,j}$。

如果 $dp_{i,j} > t$，更新 $dp_{i,j} = t,m_{i,j} = p$。如果 $dp_{i,j} = t$，$m_{i,j} = \max(m_{i,j},p)$。
# 3.代码展示
```
#include<bits/stdc++.h>
#include<cmath>
using namespace std;
int n,a[82][82],b[82][82],c[82][82];
long long ans=9e18,k,s[82][82][82][82];
struct toij{
    long long m,t;
}dp[82][82],p;//dp和m，用结构体
long long f(long long a,long long b){
    long long t=(a%b)?a/b+1:a/b;
    if(t>=0)return t;
    else return 0;
}//向上取整，注意有时会出现负数，负数时应设为0
int main(){
    scanf("%d",&n);
    for(int w=1;w<=n;w++)for(int x=1;x<=n;x++)scanf("%d",&a[w][x]),dp[w][x].t=1e18,dp[w][x].m=0;
    dp[1][1].t=0;//输入和初始化合在一起
    for(int w=0;w<=n;w++)
        for(int x=0;x<=n;x++)
            for(int y=0;y<=n;y++)s[0][w][x][y]=s[w][0][x][y]=s[x][y][w][0]=s[x][y][0][w]=1e18;//出界设为1e18
    for(int w=1;w<=n;w++)for(int x=1;x<n;x++)scanf("%d",&b[w][x]);
    for(int w=1;w<n;w++)for(int x=1;x<=n;x++)scanf("%d",&c[w][x]);
    for(int w=1;w<=n;w++)
        for(int x=1;x<=n;x++)
            for(int y=1;y<=n;y++)
                for(int z=1;z<=n;z++)
                    if(w<=y&&x<=z&&(w!=y||x!=z))s[w][x][y][z]=min(s[w][x][y][z-1]+b[y][z-1],s[w][x][y-1][z]+c[y-1][z]);
                    else if(w!=y&&x!=z)s[w][x][y][z]=1e18;//(k,l)不在(i,j)右下方，不成立，应设为1e18
    for(int w=1;w<=n;w++)
        for(int x=1;x<=n;x++)
            for(int y=1;y<=w;y++)
                for(int z=1;z<=x;z++)
                    if(y!=w||z!=x){
                        p.t=dp[y][z].t+w-y+x-z+f(s[y][z][w][x]-dp[y][z].m,a[y][z]);
                        p.m=f(s[y][z][w][x]-dp[y][z].m,a[y][z])*a[y][z]+dp[y][z].m-s[y][z][w][x];
                        if(p.t<dp[w][x].t||p.t==dp[w][x].t&&p.m>dp[w][x].m)dp[w][x]=p;
                    }//dp转移
    printf("%lld",dp[n][n].t);
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

该题弱化版是去年 J 组 T2，做法是反悔贪心，即如果当前需要钱，就去反悔在前面经过的收益最大的地方多得到些收益。

但是本题并不是只有唯一的路径，上述做法相当于本题的暴力。

于是考虑动态规划算法，定义 $dp_{i,j,x,y}$ 表示从 $(1,1)$ 走到 $(i,j)$ 且路上最大的 $p_{i`,j`}=p_{x,y}$ 时最少停留数，$f_{i,j,x,y}$ 表示当前剩下的钱的相反数。

设 $w$ 为 $dp_{i,j,x,y}+D_{i,j}$ 或者 $dp_{i,j,x,y}+R_{i,j}$ 表示当前需要的钱数。

如果 $w>0$，则需要反悔到 $(x,y)$ 那里去收钱，需要待在那 $sum=\lceil \frac{w}{p_{x,y}} \rceil$ 次。

此时钱数 $w \to w - sum \times p_{x,y}$，注意因为要使得 $p_{x,y}$ 最大，则设 $(zx,zy)$ 表示 $(x,y)$ 和 $(dx,dy)$ 中 $p$ 的较大值的位置。

则状态转移方程为：

$$dp_{dx,dy,zx,zy} = \min dp_{i,j,x,y}+sum$$

$$f_{dx,dy,zx,zy}=\min w$$

最后答案为 $\min dp_{n,n,i,j} + 2 \times (n-1)$。

时间复杂度为 $O(N^4)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=85,INF=1e18;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,ans=INF;
ll P[N][N],S[2][N][N];
pair<ll,ll> dp[N][N][N][N];
ll X[]={1,0},Y[]={0,1};
int main(){
	n=read();
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    P[i][j]=read();
	for(int i=1;i<=n;i++)
	  for(int j=1;j<n;j++)
	    S[1][i][j]=read();	
	for(int i=1;i<n;i++)
	  for(int j=1;j<=n;j++)
	    S[0][i][j]=read();	
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=n;j++)
	    for(int x=1;x<=i;x++)
	      for(int y=1;y<=j;y++)
	        dp[i][j][x][y]={INF,INF};
	dp[1][1][1][1]={0,0};
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=n;j++){
		    for(int x=1;x<=i;x++){
		    	for(int y=1;y<=j;y++){
		    		if(dp[i][j][x][y].first>=INF)
		    		  continue;
		    		for(int k=0;k<2;k++){
			            ll dx=i+X[k],dy=j+Y[k],w=0,sum=0;
			            if(dx>n||dy>n)
			              continue;
			            w=dp[i][j][x][y].second+S[k][i][j];
			            if(w>0){
			        		sum=(w+P[x][y]-1)/P[x][y];
			            	w-=P[x][y]*sum;
			            }
			            ll zx=x,zy=y;
			            if(P[zx][zy]<P[dx][dy]){
							zx=dx;
							zy=dy;
						}
			            dp[dx][dy][zx][zy]=min(dp[dx][dy][zx][zy],make_pair(dp[i][j][x][y].first+sum,w));
//			            cerr<<w<<' '<<sum<<'\n';
					} 
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=n;j++){
	    	ans=min(ans,dp[n][n][i][j].first);
//	    	cerr<<dp[n][n][i][j].first<<' ';
		}
//		cerr<<'\n';
	}
	write(ans+2*(n-1));
	return 0;
}
```

---

