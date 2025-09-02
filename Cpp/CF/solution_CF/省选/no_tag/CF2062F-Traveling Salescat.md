# Traveling Salescat

## 题目描述

你是一位售卖趣味算法题的猫咪。今天，你打算向 $k$ 个城市推荐你的趣味算法题。

总共有 $n$ 个城市，每个城市有两个参数 $a_i$ 和 $b_i$。在任意两个城市 $i,j$（$i\ne j$）之间，有一条双向道路，其长度为 $\max(a_i + b_j , b_i + a_j)$。一条路径的成本定义为路径上每两个相邻城市之间道路长度的总和。

对于 $k=2,3,\ldots,n$，找出包含恰好 $k$ 个**不同**城市的简单路径中的最小成本。

## 说明/提示

在第一个测试用例中：

- 当 $k=2$ 时，最优路径为 $1\to 2$，其成本为 $\max(0+1,2+2)=4$。
- 当 $k=3$ 时，最优路径为 $2\to 1\to 3$，其成本为 $\max(0+1,2+2)+\max(0+3,3+2)=4+5=9$。

在第二个测试用例中：

- 当 $k=2$ 时，最优路径为 $1\to 4$。
- 当 $k=3$ 时，最优路径为 $2\to 3\to 5$。
- 当 $k=4$ 时，最优路径为 $4\to 1\to 3\to 5$。
- 当 $k=5$ 时，最优路径为 $5\to 2\to 3\to 1\to 4$。

## 样例 #1

### 输入

```
3
3
0 2
2 1
3 3
5
2 7
7 5
6 3
1 8
7 5
8
899167687 609615846
851467150 45726720
931502759 23784096
918190644 196992738
142090421 475722765
409556751 726971942
513558832 998277529
294328304 434714258```

### 输出

```
4 9 
10 22 34 46 
770051069 1655330585 2931719265 3918741472 5033924854 6425541981 7934325514```

# 题解

## 作者：masonpop (赞：10)

难点就一步。

$\max(a_i+b_j,a_j+b_i)$ 这个东西的阴间之处在于，即使我们知道了路径经过哪些点，也很难确定一个权值最小的排列方式，考虑变形。对 $\max$ 变形的一种方式是利用

$$\begin{aligned}\max(x,y)=\dfrac{(x+y)+|x-y|}{2}\end{aligned}$$

将其带入并分离一些东西，最终可以把原式变为 $\dfrac{1}{2}(c_i+c_j+|d_i-d_j|)$，其中 $c_i=a_i+b_i,d_i=a_i-b_i$。

这个式子就好看多了，考虑拆贡献。对于 $c$，就是除路径两端的点之外均贡献两次。现在考虑确定了路径上的点的 $d$ 值的集合 $S$，且起点，终点的 $d$ 分别为 $d_s,d_t$ 时，如何排列能最小化 $d$ 那部分的贡献。容易发现最小贡献就是 

$$2(\max\limits_{x\in S}x-\min\limits_{x\in S}x)-|d_s-d_t|$$

取到方式就是从某一端出发，依次走到两端的极值然后走到另一边。

容易发现关键点只有四种，即 $d$ 的极值点和起点终点。于是按 $d$ 排序后，设 $f_{i,j,c}$ 表示考虑 $1\sim i$，选择 $j$ 个点，其中选择了前 $c$ 个关键点（顺序为 $\min\to s\to t\to \max$）的最小贡献。直接做就是 $O(n^2)$。

[代码](https://codeforces.com/contest/2062/submission/303319425)。

---

## 作者：cwfxlh (赞：5)

# [CF2062F](https://www.luogu.com.cn/problem/CF2062F)     

首先进行一步转化：    

$\max(a_i+b_j,a_j+b_i)=\max(a_i-b_i,a_j-b_j)+b_i+b_j$     

令 $t_i=a_i-b_i$，则一条路径的代价就是所有 $b$ 的和的两倍减去头尾的 $b$，加上相邻两项的 $t$ 的最大值。      

考虑通过 dp 记录这个序列的权值。如果起点的 $t$ 大于终点的 $t$，把路径反过来权值也一样。通过每次把一个最大值挪到边上的操作（这样不劣），可以将除了头尾之外的内容物调整成 $t$ 不降的形式。     

接下来 dp 记录序列的头尾有 0/1/2 个被选中了，总共填进去 $j$ 个点，然后每次加的要么是端点，要么是中间的东西。因为上一段分析出的两条性质，所以对于新加入的 $x$，其系数是好分析的，与以下三个因素有关：头尾填了几个位置，$j$ 是否为 0，是否打算结束更新答案。复杂度 $O(n^2)$。      

代码：    


```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1000000000000000000ll
using namespace std;
int testcnt,n,dp[3003][3003][3],ans[3003];
pair<int,int>p[3003];
int k1,k2,k3,k4,k5,k6,k7,k8,k9;
void upd(int &x,int y){x=min(x,y);return;}
void sol(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>p[i].first>>p[i].second;
	for(int i=1;i<=n;i++)p[i].first-=p[i].second;
	sort(p+1,p+n+1);
	for(int i=0;i<=n;i++){
		ans[i]=inf;
		for(int j=0;j<=n;j++){
			for(int u=0;u<3;u++)dp[i][j][u]=inf;
		}
	}
	dp[0][0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<=n;j++){
			//不填 
			for(int u=0;u<3;u++)upd(dp[i+1][j][u],dp[i][j][u]);
			//填中间 
			upd(dp[i+1][j+1][0],dp[i][j][0]+p[i+1].second*2+p[i+1].first*(j!=0));
			upd(dp[i+1][j+1][1],dp[i][j][1]+p[i+1].second*2+p[i+1].first);
			upd(dp[i+1][j+1][2],dp[i][j][2]+p[i+1].second*2+p[i+1].first);
			upd(ans[j+1],dp[i][j][2]+p[i+1].second*2+p[i+1].first*2);
			//填端点 
			upd(dp[i+1][j+1][1],dp[i][j][0]+p[i+1].second+p[i+1].first*(j!=0));
			upd(dp[i+1][j+1][2],dp[i][j][1]+p[i+1].second);
			upd(ans[j+1],dp[i][j][1]+p[i+1].second+p[i+1].first);
		}
	}
	for(int i=2;i<=n;i++)cout<<ans[i]<<' ';
	cout<<'\n';
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>testcnt;
	while(testcnt--)sol();
	return 0;
}
```

其实起点小于等于终点的性质应该是可以不用的？但是这样会好写一些。

---

## 作者：Purslane (赞：3)

# Solution

有趣题目。

首先考虑拆个贡献，即把 $\max\{a_i+b_j,a_j+b_i\}$ 写成关于 $i$ 和 $j$ 较为独立的形式。

显然 $\max\{a_i+b_j,a_j+b_i\} = a_i + a_j + \max\{b_i-a_i,b_j-a_j\}$。所以令 $t_i = b_i - a_i$，所以可以写成 $a_i + a_j + \max\{t_i,t_j\}$。

如果固定了首尾（因为他们 $a$ 的贡献是 $1$），显然中间的按照 $t$ 排序最优（显然首尾的 $t$ 也要是同序的）。

这样就可以直接上 DP 了。

考虑插入点。两端的点只有都没确定、确定一个、确定两个三种情况。

具体细节为：加入第一个点的时候，选择它的类型——头还是第二个；插入一个点的时候，可以选择放到头上、放到尾巴上（可能得到完整解）、放到中间（如果选择和已经存在的尾巴接上，可以得到完整解）

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10;
int T,n,a[MAXN],b[MAXN],dp[2][MAXN][3],ans[MAXN];
//0 啥都没有 1 有头 2 有头有尾 
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n;
		ffor(i,1,n) cin>>a[i]>>b[i],b[i]-=a[i];	
		memset(ans,0x3f,sizeof(ans)),memset(dp,0x3f,sizeof(dp));
		vector<pair<int,int>> vc;
		ffor(i,1,n) vc.push_back({b[i],a[i]});
		sort(vc.begin(),vc.end());
		ffor(i,1,n) a[i]=vc[i-1].second,b[i]=vc[i-1].first;
		ffor(i,1,n) ffor(j,i+1,n) ans[2]=min(ans[2],a[i]+a[j]+max(b[i],b[j]));
		ffor(i,1,n) {
			int st=i&1,lst=st^1;
			ffor(j,1,i) ffor(o,0,2) dp[st][j][o]=0x3f3f3f3f3f3f3f3f;
			ffor(j,1,i-1) ffor(o,0,2) dp[st][j][o]=min(dp[st][j][o],dp[lst][j][o]);
			dp[st][1][1]=min(dp[st][1][1],a[i]);
			dp[st][1][0]=min(dp[st][1][0],2*a[i]);
			ffor(j,1,i-1) {
				//放在头上
				dp[st][j+1][1]=min(dp[st][j+1][1],dp[lst][j][0]+a[i]+b[i]);
				//放在末尾
				dp[st][j+1][2]=min(dp[st][j+1][2],dp[lst][j][1]+a[i]);
				ans[j+1]=min(ans[j+1],dp[lst][j][1]+a[i]+b[i]);
				//放在中间
				dp[st][j+1][0]=min(dp[st][j+1][0],dp[lst][j][0]+a[i]*2+b[i]);
				dp[st][j+1][1]=min(dp[st][j+1][1],dp[lst][j][1]+a[i]*2+b[i]);
				dp[st][j+1][2]=min(dp[st][j+1][2],dp[lst][j][2]+a[i]*2+b[i]); 
				ans[j+1]=min(ans[j+1],dp[lst][j][2]+a[i]*2+b[i]*2);
			}
		}
		ffor(i,2,n) cout<<ans[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

首先先把边权变成 $b_i + b_j + \max(a_i - b_i, a_j - b_j)$。令 $a_i \gets a_i - b_i$，边权变成 $b_i + b_j + \max(a_i, a_j)$。

考虑若确定了路径经过的点 $p_1, p_2, \ldots, p_k$，如何排列它们能取得最小权值。若所有 $b_i = 0$，那么显然是按 $a_i$ 排序最优。对于一般情况，发现 $\sum\limits_{i = 1}^{k - 1} b_{p_i} + b_{p_{i + 1}} = 2 \sum\limits_{i = 2}^{k - 1} b_{p_i} + b_{p_1} + b_{p_k}$，所以 $p_1$ 和 $p_k$ 是比较重要的。

考虑选出了起点 $p_1$ 和终点 $p_k$（不妨设 $a_{p_1} \le a_{p_k}$），那么 $\sum\limits_{i = 1}^{k - 1} \max(a_{p_i}, a_{p_{i + 1}})$ 取到最小值时，$p_2$ 到 $p_{k - 1}$ 之间一定是按照 $a_i$ 升序排序最优。如果 $a_{p_k}$ 都不是 $a_{p_i}$ 中的最大值，此时每个点对 $\sum\limits_{i = 1}^{k - 1} \max(a_{p_i}, a_{p_{i + 1}})$ 的贡献为：$a_i$ 第二小值到最大值（除了 $a_{p_k}$）贡献 $1$ 次，最大值贡献 $2$ 次。如果 $a_{p_1}$ 或 $a_{p_k}$ 是最大值，那么 $a_i$ 第二小值到最大值都贡献 $1$ 次。

据此可以设计 DP。将所有点按 $a_i$ 升序排序，这样方便考虑每个点对答案的贡献系数。设 $f_{i, j, 0/1/2}$ 表示考虑了 $[1, i]$ 中的点，选出 $j$ 个路径的点，路径的起点和终点都没被钦定 / 钦定了起点，未钦定终点 / 起点和终点都已被钦定，路径权值的最小值。转移大力分类讨论即可，这里不展开讲了。

时间复杂度 $O(n^2)$。

```cpp
// Problem: F. Traveling Salescat
// Contest: Codeforces - Ethflow Round 1 (Codeforces Round 1001, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2062/problem/F
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define uint unsigned
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

const int maxn = 3030;

ll n, f[2][maxn][3], g[maxn], b[maxn];
struct node {
	ll a, b;
} a[maxn];

void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld%lld", &a[i].a, &a[i].b);
		a[i].a -= a[i].b;
	}
	sort(a + 1, a + n + 1, [&](const node &a, const node &b) {
		return a.a < b.a;
	});
	b[n + 1] = 1e18;
	for (int i = n; i; --i) {
		b[i] = min(b[i + 1], a[i].a + a[i].b);
	}
	int o = 0;
	mems(f, 0x3f);
	mems(g, 0x3f);
	f[0][0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		o ^= 1;
		mems(f[o], 0x3f);
		for (int j = 0; j <= i; ++j) {
			for (int k = 0; k <= 2; ++k) {
				ll v = f[o ^ 1][j][k];
				if (v > 1e18) {
					continue;
				}
				f[o][j][k] = min(f[o][j][k], v);
				if (!k) {
					if (j) {
						f[o][j][1] = min(f[o][j][1], v + a[i].a + a[i].b);
					} else {
						f[o][j][1] = min(f[o][j][1], v + a[i].b);
					}
					g[j + 2] = min(g[j + 2], v + a[i].a + a[i].b + b[i + 1]);
				} else if (k == 1) {
					g[j + 2] = min(g[j + 2], v + a[i].a + a[i].b);
					f[o][j][2] = min(f[o][j][2], v + a[i].b);
				} else {
					g[j + 3] = min(g[j + 3], v + a[i].a * 2 + a[i].b * 2);
				}
				f[o][j + 1][k] = min(f[o][j + 1][k], v + (j ? a[i].a : (k ? a[i].a : 0)) + a[i].b * 2);
			}
		}
	}
	ll mn = 9e18;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			mn = min(mn, max(a[i].a, a[j].a) + a[i].b + a[j].b);
		}
	}
	printf("%lld", mn);
	for (int i = 3; i <= n; ++i) {
		printf(" %lld", g[i]);
	}
	putchar('\n');
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：wrkwrkwrk (赞：1)

~~显然~~原来的式子不好描述，考虑将 $(a_i,b_i)$ 放到二维平面上考虑。

![](https://cdn.luogu.com.cn/upload/image_hosting/ts6epi0v.png)

如图，当一个在左下角一个在右上角的时候，其权值为两个大的值之和。

不满足的时候，一个在左上，一个在右下，考虑 $a_i \to b_i$，$b_j \to a_j$ 的变化，能够影响区别的是变化就是 $a_i-b_i$ 的大小。

因此可以按照其分类，对于同一个 $a_i-b_i$，其可以被描述为 $a_i = b_i + k$ 的直线。

在图中可以画出向量，启示我们按照 $\begin{bmatrix} 0 \\ 1\end{bmatrix}$ ，$\begin{bmatrix} 1 \\ 1\end{bmatrix}$这组东西进行分解。解出 $x_i=a_i,y_i=b_i-a_i$。

现在重新描述式子：
$$
\max(a_i+b_j,b_i+a_j)=\max(x_i+x_j+y_j,x_j+x_i+y_i)=x_i+x_j+\max(y_i,y_j)
$$
考虑最后的每个点的贡献：对于中间点， $x_i$ 贡献 $2$ 次，$y_i$ 左右贡献。对于边点，$x_i$ 贡献一次，$y_i$ 边上贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/98avhwah.png)

显然两边和中间的贡献是不同的，对于中间的贡献，容易理解按照 $y_i$ 排序最优。

现在考虑将按照 $y_i$ 排序的中间两个点提出来，剩下的点排布在中间。按照这一过程进行构造。

容易理解被提出的点中 $y_i$ 更小的放在中间 $y_i$ 小一侧。

将点按照 $y_i$ 从小到大排序，设 $dp_{i,0/1/2}$ 表示目前中间有 $i$ 个数，两边没有/仅左侧有/两边有。

转移可以是在中间或者两边加点，注意转移存储不要计算最后一条边的 $y$，只有统计答案的时候要。

还有部分 $i=0 ,1$ 的情况的细节。

时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
pair<int,int>w[1000006];
int ans[1000006];
bool cmp(pair<int,int>a,pair<int,int>b){
	return a.second<b.second;
}
int dp[1000006][3];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			int a,b;
			cin>>a>>b;
			w[i].first=a;
			w[i].second=b-a;
		}
		sort(w+1,w+1+n,cmp);
		for(int i=0;i<=n;i++){
			dp[i][0]=dp[i][1]=dp[i][2]=ans[i]=1e17;
		}
		dp[0][0]=0;
		for(int i=1;i<=n;i++){
			for(int j=n-2;j>=0;j--){
				dp[j][2]=min(dp[j][2],dp[j][1]+w[i].first);
				ans[j]=min(ans[j],dp[j][2]+w[i].second);
				if(j)dp[j][2]=min(dp[j][2],dp[j-1][2]+2*w[i].first+w[i].second);
				ans[j]=min(ans[j],dp[j][2]+w[i].second);
				dp[j][1]=min(dp[j][1],dp[j][0]+w[i].first+w[i].second*(j!=0));
				if(j)dp[j][1]=min(dp[j][1],dp[j-1][1]+2*w[i].first+w[i].second);
				if(j)dp[j][0]=min(dp[j][0],dp[j-1][0]+2*w[i].first+w[i].second*(j!=1));
			}
		}
		for(int i=2;i<=n;i++){
			cout<<ans[i-2]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

[AC ](https://codeforces.com/contest/2062/submission/303122427)记录。

---

## 作者：Fishing_Boat (赞：1)

令 $x_i=\frac{a_i+b_i}{2}$，$y_i=\frac{a_i-b_i}{2}$，则 $a_i=x_i+y_i$，$b_i=x_i-y_i$。

可得 $\max(a_i+b_j,a_j+b_i)=\max(x_i+y_i+x_j-y_j,x_j+y_j+x_i-y_i)=x_i+x_j+|y_i-y_j|$。

先考虑 $x_i$，两个端点分别计算一次，中间的点计算两次。

再考虑 $y_i$，一定是从较小的端点递减，一直到最小值，随后递增到最大值，再递减到较大的端点。证明是容易的。

考虑 $\texttt{dp}$，先按照 $y_i$ 排序，记 $dp_{i,j,0/1/2}$，表示当前选了 $i$ 个点，选到了点 $j$，确定了 $0/1/2$ 个端点。

写的时候可以压掉第一维，时间复杂度 $O(n^2)$，空间复杂度 $O(n)$。[submission](https://codeforces.com/contest/2062/submission/303175862)

---

