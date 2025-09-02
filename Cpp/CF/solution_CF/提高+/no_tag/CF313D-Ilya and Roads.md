# Ilya and Roads

## 题目描述

Everything is great about Ilya's city, except the roads. The thing is, the only ZooVille road is represented as $ n $ holes in a row. We will consider the holes numbered from 1 to $ n $ , from left to right.

Ilya is really keep on helping his city. So, he wants to fix at least $ k $ holes (perharps he can fix more) on a single ZooVille road.

The city has $ m $ building companies, the $ i $ -th company needs $ c_{i} $ money units to fix a road segment containing holes with numbers of at least $ l_{i} $ and at most $ r_{i} $ . The companies in ZooVille are very greedy, so, if they fix a segment containing some already fixed holes, they do not decrease the price for fixing the segment.

Determine the minimum money Ilya will need to fix at least $ k $ holes.

## 样例 #1

### 输入

```
10 4 6
7 9 11
6 9 13
7 7 7
3 5 6
```

### 输出

```
17
```

## 样例 #2

### 输入

```
10 7 1
3 4 15
8 9 8
5 6 8
9 10 6
1 4 2
1 4 10
8 10 13
```

### 输出

```
2
```

## 样例 #3

### 输入

```
10 1 9
5 10 14
```

### 输出

```
-1
```

# 题解

## 作者：流水行船CCD (赞：4)

一个不同于其他题解的完全不动脑子的方法。

不难发现 $m$ 就是个幌子，直接令 $w_{l,r}$ 表示小区间为 $[l,r]$ 的权值的最小值，此时 $m$ 变为 $\mathcal{O}(n^2)$ 级别。

设 $f_{i,j}$ 表示前 $i$ 个点，被覆盖 $j$ 个点最小贡献和。

发现 $f$ 难以转移，这是因为有些区间是有交的，因此我们考虑把有交的区间抡一起算。又设 $g_{l,r}$ 表示精确覆盖 $[l,r]$ 所需要的最小贡献和。

此时，$f$ 转移方程易写：

$$f_{i,j} = \min(f_{i-1,j},\min_{1\le k\le i}(f_{i-k,j-k}+g_{i-k+1,i}))$$

此时，由于 $g$ 不用管区间有交对覆盖点数的影响了，$g$ 朴素转移方程也易写：  

$$g_{l,r} = \min(w_{l,r},\min_{l \le p \le q \le r}(g_{l,q}+g_{p,r}))$$

优化就考虑定一求一，从小到大枚举 $q$，维护 $\operatorname{Min} = \min\limits_{1\le p \le q} g_{p,r}$，每次把新增的 $g_{p,r}$ 和 $\operatorname{Min}$ 取个最小值就可以了。

## AC Code

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse4.2,avx,avx2,bmi,bmi2,popcnt,lzcnt,tune=native")
using namespace std;
namespace fast_IO{
...
} using namespace fast_IO;
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
#define bitcount(x) __builtin_popcount(x)
#define albit(x) ((1 << (x)) - 1)
#define mkbit(x) (1 << (x - 1))
#define gtbit(x, id) (((x) >> (id - 1)) & 1)
// #define ld cin
// #define jyt cout
// #define int long long
const int N = 300 + 7;
const int inf = 1e9 + 7;
const ll linf = 1e18 + 7;
const int P = 99824435
namespace JoKing {
    int n, m, K; ll f[N][N], g[N][N], cost[N][N];
    signed main() { int l, r, w;
    	ld >> n >> m >> K, memset(cost, 0x3f, sizeof(cost)), memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g)), f[0][0] = 0;
    	REP(i, 1, m) ld >> l >> r >> w, cost[l][r] = min(cost[l][r], (ll)w);
		REP(len, 1, n) for (int l = 1, r = len; r <= n; ++l, ++r) {
			ll Min = linf; g[l][r] = cost[l][r]; 
			REP(k, l, r) Min = min(Min, g[k][r]), g[l][r] = min(g[l][r], g[l][k] + Min);
		} 
		REP(i, 1, n) REP(j, 0, i) {
			f[i][j] = f[i - 1][j];
			REP(k, 1, min(i, j)) f[i][j] = min(f[i][j], f[i - k][j - k] + g[i - k + 1][i]);
		}
		ll Ans = linf;
		REP(i, K, n) Ans = min(Ans, f[n][i]);3;
		const ll B = 1e16 + 3;
        return jyt << (Ans > B ? -1 : Ans) << '\n', 0; 
    }
}
signed main() {
//	freopen("std.in", "r", stdin);
//	freopen("user.out", "w", stdout);
//	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    JoKing::main(); return 0;
}
```

---

## 作者：yinianxingkong (赞：2)

感觉这道题的思路还蛮顺的。

本题难点显然在于如何去掉重复区间的贡献。

并集信息去重的一个想法就是钦定元素只被特定的决策产生贡献。

从左往右扫描线时，考虑覆盖一个元素的决策，我们要求这个决策优先级最高，这会导致整个区间被当前元素划分的左半部分都要计算贡献。此时对更前面的元素作贡献的只能是左端点比当前区间左端点小的区间。

于是设计状态时考虑将左端点比当前点小设入状态内，这样就可以划分成子问题了。

具体地，设 $f_{i,j}$ 表示前 $i$ 个点内只使用左端点小于 $i$ 的区间覆盖 $j$ 个点的最小代价。转移时每个点考虑覆盖它的区间即可。复杂度 $O(n^2m)$，无法通过。

实际上转移只和左端点有关，贪心一下贡献不同的区间只有 $O(n)$ 个，预处理一下就好了，复杂度 $O(n^3)$。

应该不需要代码吧，需要私信。

---

## 作者：TruchyR (赞：2)

个人认为会更容易想到，但是 $O(n^3\log{n})$。

设 $a_{l,r}$ 为选择区间 $[l,r]$ 的代价，$f_{i,j}$ 为 $[1,i]$ 中恰好覆盖 $j$ 个的最小代价。  

按照右端点从小到大，左端点从小到大的顺序更新答案：  
- 设 $f'_{l,r,j}$ 为 $[1,r]$ 中选择 $[l,r]$ 这一区间，恰好覆盖 $j$ 个的最小代价。  
- 先考虑其他区间与 $[l,r]$ 不交的情况，可以 $O(1)$ 求出：
  - 当 $j\leq r-l+1$ 时，答案显然为 $a_{l,r}$。
  - 当 $j> r-l+1$ 时，$a_{l,r}+\min_{i=1}^{l-1} f_{i,j-(r-l+1)}$ 也可以更新答案。 
- 然后是其他区间与 $[l,r]$ 有交的情况：
  - $a_{l,r}+\min_{i=l}^{r} f_{i,j-(r-i)}$ 可以更新答案，但似乎不好快速求。
  - 由于时间限制允许，我们可以无脑线段树，做到 $O(\log{n})$。
- $f_{r,j}=\min_{l=1}^{r} f'_{l,r,j}$。  
- 最终答案即为 $\min_{i=k}^n f_{n,i}$。  


```cpp
#include<bits/stdc++.h>
#define int long long
#define MX 100005
#define INF 1000000000000000ll
using namespace std;int read();
int n,m,K,l,r,a[301][301],f[301][301];
int res=INF;
class Array{
	public:
		int Tree[1201];
		void build(int t,int L,int R){
			Tree[t]=INF;
			if(L>=R) return;
			int mid=(L+R)>>1;
			build(t*2,L,mid);
			build(t*2+1,mid+1,R);
		}
		void change(int t,int L,int R,int i,int j){
			if(L>=R){Tree[t]=min(Tree[t],j);return;}
			int mid=(L+R)>>1;
			if(i<=mid) change(t*2,L,mid,i,j);
			else change(t*2+1,mid+1,R,i,j);
			Tree[t]=min(Tree[t*2],Tree[t*2+1]);
		}
		int sum(int t,int L,int R,int i,int j){
			if(i<=L && R<=j) return Tree[t];
			int mid=(L+R)>>1;
			int ans=INF;
			if(i<=mid) ans=min(ans,sum(t*2,L,mid,i,min(mid,j)));
			if(j>mid) ans=min(ans,sum(t*2+1,mid+1,R,max(i,mid+1),j));
			return ans;
		}
}F[301];
signed main(){
	n=read();m=read();K=read();
	memset(a,0x3f,sizeof(a));memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;i++){f[i][0]=0;F[i].build(1,1,n);}
	for(int i=1;i<=m;i++){
		l=read();r=read();
		a[l][r]=min(a[l][r],read());
	}
	for(r=1;r<=n;r++){for(l=1;l<=r;l++){
		for(int j=1;j<=r;j++){
			int ans=F[r-j].sum(1,1,n,l,n);
			if(j>(r-l+1)) ans=min(ans,f[l-1][j-(r-l+1)]);
			else ans=0;
			ans+=a[l][r];F[r-j].change(1,1,n,r,ans);
			f[r][j]=min(f[r][j],ans);
		}
	}for(int j=1;j<=r;j++) f[r][j]=min(f[r][j],f[r-1][j]);}
	int res=INF;
	for(int i=K;i<=n;i++) res=min(res,f[n][i]);
	printf("%lld\n",(res>=INF?-1:res));
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```


---

## 作者：LRL65 (赞：1)

题意：

有一个 $1 \sim n$ 的区间，有 $m$ 个 $l_i \sim r_i$ 的小区间，覆盖第 $i$ 个区间需要花费 $c_i$ 。问当 $1 \sim n$ 中有 $k$ 个被覆盖时的最小花费。

思路：

这明显是道dp。

我们设 $f_{i,j}$ 表示前 $i$ 个覆盖了 $j$ 个时的最小花费。

我们用 $a_{i,j} $ 表示覆盖第 $i$ 个到第 $j$ 个所需的最小花费。那么 $a_{l_i,r_i}=c_i$ ，并且对任意的 $left \leq l_i \leq right \leq j$，都有 $a_{left,right}=c_i$ 。

那么状态转移方程如下：

1. 对于 $j \leq k <i$ ， $f_{i,j}=\min(f_{i,j},f_{i-1,k})$ 。
1. 枚举 $p<i$ ，$f_{i,j}=\min(f_{i,j},f_{p,j-(i-p)}+a_{p+1,i})$ 。

最后只需输出 $f_{n,k}$ 。

代码如下:
```cpp
#include<bits/stdc++.h>
#define INF 10000000000000
using namespace std;
long long n,m,k,f[305][305],a[305][305];
int main() {
	cin>>n>>m>>k;
    for(int i=0;i<=n;i++)
		for(int j=1;j<=n;j++) {
			a[i][j]=INF;
            f[i][j]=INF;
        }
	for(int i=1;i<=m;i++) {
		long long l,r,c;
		cin>>l>>r>>c;
		for(int l1=l;l1<=r;l1++)
            for(int r1=l1;r1<=r;r1++)
                a[l1][r1]=min(a[l1][r1],c);
	}	
	for(int i=1;i<=n;i++) 
		for(int j=0;j<=i;j++) {
			for(int k=j;k<i;k++)
                f[i][j]=min(f[i][j],f[i-1][k]);
			for(int p=0;p<i;p++)
				if(j-(i-p)>=0)
					f[i][j]=min(f[i][j],f[p][j-(i-p)]+a[p+1][i]);
            //cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
		}
    if(f[n][k]==INF)cout<<-1<<endl;
	else cout<<f[n][k]<<endl;
}
```



---

