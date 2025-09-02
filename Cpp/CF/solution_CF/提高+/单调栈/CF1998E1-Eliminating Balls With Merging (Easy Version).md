# Eliminating Balls With Merging (Easy Version)

## 题目描述

_喝水_ 

—— 孙武，程序员健康指南

**这是问题的简单版本。本题中 $x=n$ 。你必须同时解决这两个版本的问题，才能  hack**。

给你两个整数 $n$ 和 $x$ ( $x=n$ )。有 $n$ 个球排成一排，从左到右编号为 $1$ 到 $n$ 。最初，在第 $i$ 个球上写着一个值 $a_i$。

对于从 $1$ 到 $n$ 的每个整数 $i$ ，我们定义一个函数 $f(i)$ 如下：

- 假设有一个集合 $S = \{1, 2, \ldots, i\}$ 。
    
- 在每次运算中，必须从 $S$ 中选择一个整数 $l$ ( $1 \leq l < i$ )，使得 $l$ 不是 $S$ 的最大元素。假设 $r$ 是 $S$ 中大于 $l$ 的最小元素。
    
    - 如果是 $a_l > a_r$ ，则令 $a_l = a_l + a_r$ 并从 $S$ 中删除 $r$ 。
    - 如果是 $a_l < a_r$ ，则令 $a_r = a_l + a_r$ ，并从 $S$ 删除 $l$ 。
    - 如果是 $a_l = a_r$ ，则从 $S$ 中选择删除整数 $l$ 或 $r$ ：
        - 如果选择从 $S$ 中删除 $l$ ，则设置 $a_r = a_l + a_r$ 并从 $S$ 中删除 $l$ 。
        - 如果您选择从 $S$ 中删除 $r$ ，则需要设置 $a_l = a_l + a_r$ ，并从 $S$ 中删除 $r$ 。
    
- $f(i)$ 表示这样的整数 $j$ ( $1 \le j \le i$ )的个数，即执行上述操作恰好 $i - 1$ 次后可以得到 $S = \{j\}$ 。

对 $x$ 到 $n$ 的每个整数 $i$ 都需要求出 $f(i)$ 。

## 样例 #1

### 输入

```
3
5 5
1 2 3 2 1
7 7
4 5 1 2 1 4 5
11 11
1 2 3 1 1 9 3 2 4 1 3```

### 输出

```
3
4
4```

# 题解

## 作者：what_can_I_do (赞：10)

[传送门](https://www.luogu.com.cn/problem/CF1998E1)

分治。很显然，对于一个区间，其最大值一定可以留到最后，并且到最后它的值为区间和。对于最大值左右的区间，如果它最后的值也就是区间和大于等于这个最大值，那么这个区间里就一定有元素可以留到最后。

现在对于一个区间，先把它的所有最大值找出来，然后对于最大值划分出的所有区间都进行判断，如果里面有元素到最后可以大于等于最大值就往这个区间里递归。

对于找区间最大值可以先对于每个值标记出现过的位置，然后求出这个区间的最大值，用二分找到这个值在该区间出现的最靠左和最靠右的位置，然后暴力枚举即可。

对于 $n=1$ 的情况要特判。

# CODE:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define lc k<<1
#define rc k<<1|1
using namespace std;
int t;
int n,x;
struct aaa
{
	int val,v,id;
}a[200010];
vector<int> wz[200010];
ll tr[800010][2];
int ans=0;
inline void build(int l,int r,int k)
{
	if(l==r)
	{
		tr[k][0]=a[l].v,tr[k][1]=a[l].val;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lc),build(mid+1,r,rc);
	tr[k][0]=max(tr[lc][0],tr[rc][0]),tr[k][1]=tr[lc][1]+tr[rc][1];
}
inline int query(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return tr[k][0];
	int mid=(l+r)>>1,sum=0;
	if(ql<=mid) sum=query(l,mid,ql,qr,lc);
	if(mid<qr) sum=max(sum,query(mid+1,r,ql,qr,rc));
	return sum;
}
inline ll querysum(int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr) return tr[k][1];
	int mid=(l+r)>>1;ll sum=0;
	if(ql<=mid) sum+=querysum(l,mid,ql,qr,lc);
	if(mid<qr) sum+=querysum(mid+1,r,ql,qr,rc);
	return sum;
}
inline void solve(int l,int r)
{
	if(l>=r) return;
	int maxx=query(1,n,l,r,1);
	int rl=lower_bound(wz[maxx].begin(),wz[maxx].end(),l)-wz[maxx].begin(),rr=upper_bound(wz[maxx].begin(),wz[maxx].end(),r)-wz[maxx].begin()-1;
	//cout<<l<<" "<<r<<" "<<rl<<" "<<rr<<endl;
	int nw=l;
	for(register int i=rl;i<=rr;i++)
	{
		ans++;
		if(nw<=wz[maxx][i]-1)
			if(querysum(1,n,nw,wz[maxx][i]-1,1)>=a[wz[maxx][i]].val)
				solve(nw,wz[maxx][i]-1);
		nw=wz[maxx][i]+1;
	}
	if(nw<=r)
		if(querysum(1,n,nw,r,1)>=a[wz[maxx][rr]].val)
			solve(nw,r);
}
int main()
{
	//freopen("qg.in","r",stdin);
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&x);
		for(register int i=1;i<=n;i++) scanf("%d",&a[i].val),a[i].id=i;
		if(n==1)
		{
			puts("1");
			continue;
		}
		sort(a+1,a+n+1,[](aaa u,aaa v){return u.val<v.val;});
		int tot=0;
		a[0].val=0;
		for(register int i=1;i<=n;i++)
		{
			if(a[i].val!=a[i-1].val) tot++;
			a[i].v=tot;
		}
		sort(a+1,a+n+1,[](aaa u,aaa v){return u.id<v.id;});
		for(register int i=1;i<=n;i++) wz[a[i].v].push_back(i);
		build(1,n,1);
		solve(1,n);
		printf("%d\n",ans);
		ans=0;
		for(register int i=1;i<=4*n;i++) tr[i][0]=tr[i][1]=0;
		for(register int i=1;i<=tot;i++) wz[i].clear();
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：4)

简单题。

考虑到一个显然的贪心，对于每个位置，我们能往左就往左加，能往右就往右加，但是这是 $O(n^2)$ 的显然会超时。

考虑使用 ST 表 $+$ 倍增 优化，假如现在已经从 $[i,i]$ 扩展到了 $[l,r]$，先要判断能不能向左扩展到 $x$，只要满足：

对于所有的 $i \in [x,i-1] $，有 $s_r - s_{i}>a_i$，其中 $s$ 是前缀和数组，移项得 $s_r>a_i + s_i$，对于每一项 $i$ 我们预处理 $fx_i = a_i+s_i$，预处理 ST 表就能快速查询能不能扩展到某个点了，向右同理。

如何查询最左最右能扩展到哪里？显然可以使用倍增。

当然，这道题并没有这么简单，有可能扩展到左边一点，右边又能扩展了，于是暴力扩展过了。

感性理解一下：如果想要卡满这个算法，一定是左边扩展一个，右边扩展一个，但是这样仅仅能卡满一个位置罢了。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, x, ans;
int a[200005], s[200005], lg[200005];
int pre[200005], suf[200005];
int fx[18][200005], fy[18][200005];
void initst () {
	For (i, 1, 17) for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
		fx[i][j] = max (fx[i - 1][j], fx[i - 1][j + (1 << i - 1)]);
		fy[i][j] = max (fy[i - 1][j], fy[i - 1][j + (1 << i - 1)]);
	}
}
int qry1 (int x, int y) {
	int l = lg[y - x + 1];
	return max (fx[l][x], fx[l][y - (1 << l) + 1]);
}
int qry2 (int x, int y) {
	int l = lg[y - x + 1];
	return max (fy[l][x], fy[l][y - (1 << l) + 1]);
}
void solve () {
	cin >> n >> x;
	For (i, 1, n) {
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
		fx[0][i] = a[i] + s[i];
		fy[0][i] = a[i] - s[i - 1];
	}
	initst ();
	ans = 0;
	For (i, 1, n) {
		int l = i, r = i;
		while (1) {
			int tl = l, tr = r;
			foR (j, 17, 0) if (l > (1 << j) && qry1 (l - (1 << j), l - 1) <= s[r]) l -= 1 << j;
			foR (j, 17, 0) if (r + (1 << j) <= n && qry2 (r + 1, r + (1 << j) ) <= -s[l - 1]) r += 1 << j;
			if (l == 1 && r == n) {
				++ ans;
				break;
			}
			if (tl == l && tr == r) break;
		}
	}
	cout << ans;
}
/*
a[l] + s[l] <= s[i];
a[r] - s[r - 1] <= - s[i - 1];
*/
signed main () {
	lg[1] = 0;
	For (i, 2, 200000) lg[i] = lg[i / 2] + 1;
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：灵乌路空 (赞：4)

枚举，分治，笛卡尔树

一个优美的笛卡尔树解法。

题意实际上即不断地选择相邻的两个数，并将他们合并到较大的数上，直到只剩一个位置，并检查有哪些位置可作为最终剩下的位置。

显然原数列中最大值的位置一定合法；又发现若位置 $i$ 合法且位置 $j$ 满足 $a_j < a_i$ 且可以通过合并使得合并后 $a'_j \ge a_i$ 且此时 $a'_j$ 与 $a_i$ 相邻，则对位置 $i$ 的操作可以同样地对 $j$ 进行，从而将 $a_i$ 完全合并到 $a'_j$ 中，则最终也可只剩下 $a'_j$ 一个元素推导出位置 $j$ 也合法。

则一个显然的想法是按照**权值递减**的顺序枚举位置 $j$，检查该位置能否通过**仅与不大于** $a_j$ 的 $a_k$ 合并，使其变为最大的 $a'_j$，使得存在 $a'_j \ge a_i > a_j$，且合并后 $a'_j$ 与 $a_i$ **相邻**，即可通过位置 $i$ 是否合法递推位置 $j$ 是否合法。

考虑对于某个位置 $j$ 应当如何操作变为最大的 $a'_j$。由于仅能相邻的两个数合并，记位置 $j$ 左右两侧第一个**大于** $a_j$ 的位置分别为 $L_i, R_i$，则其最大合并范围为 $[L_i + 1, R_i - 1]$。于是仅需检查 $\sum\limits_{L_i + 1 \le k \le R_i - 1} a_i \ge a_{L_i}$ 和 $\sum\limits_{L_i + 1 \le k \le R_i - 1} a_i \ge a_{R_i}$ 是否成立，若成立则若 $L_i, R_i$ 合法 $j$ 也一定合法即可进行递推。

发现按上述递减枚举元素，并求左右两侧第一个大于该元素的过程，可以看做不断地取区间 $[L, R]$ 的最值 $a_{\operatorname{maxp}}$，并将区间以 $\operatorname{maxp}$ 为界分治为两部分 $[L, \operatorname{maxp} - 1],[\operatorname{maxp} + 1, R]$，则两部分内权值均不大于 $a_{L - 1}, a_{R + 1}, a_{\operatorname{maxp}}$，且有 $a_{\operatorname{maxp}} = \min(a_{L - 1}, a_{R + 1})$。于是仅需递归地分治判断子区间之和是否不小于 $a_{\operatorname{maxp}}$，若不小于则子区间内的最值的位置 $\operatorname{maxp}'$ 即满足上述可以递推的条件，则可通过 $\operatorname{maxp}$ 是否合法递推。

这个过程显然可以直接放到笛卡尔树上进行。笛卡尔树上节点与区间最值位置一一对应，按照权值递减建立笛卡尔树后，初始化全局最大值位置合法，dfs 维护对应区间 $[L, R]$，比较 $[L, R]$ 之和与父节点的最值 $a_{\operatorname{maxp}}$ 的权值大小关系，即可不递推当前节点最值位置 $\operatorname{maxp}'$ 是否合法。

代码非常好写，复杂度 $O(n)$ 级别跑得飞快：[https://codeforces.com/contest/1998/submission/275679413](https://codeforces.com/contest/1998/submission/275679413)。

```cpp
//
/*
By:Luckyblock
*/
#include <bits/stdc++.h>
#define LL long long
const int kN = 2e5 + 10;
const LL kInf = 1e18 + 2077;
//=============================================================
int n, x, yes[kN];
LL a[kN], sum[kN];
int rt, son[kN][2];
int top, st[kN];
//=============================================================
void dfs(int u_, int fa_, int l_, int r_) {
  LL s = sum[r_ - 1] - sum[l_];
  if (s >= a[fa_]) yes[u_] |= yes[fa_];
  if (son[u_][0]) dfs(son[u_][0], u_, l_, u_); 
  if (son[u_][1]) dfs(son[u_][1], u_, u_, r_);
}
//=============================================================
int main() {
  // freopen("1.txt", "r", stdin);
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  int T; std::cin >> T;
  while (T --) {
    std::cin >> n >> x;
    for (int i = 1; i <= n; ++ i) {
      std::cin >> a[i];
      sum[i] = sum[i - 1] + a[i];
    }
    a[0] = a[n + 1] = kInf;
    for (int i = 0; i <= n; ++ i) son[i][0] = son[i][1] = yes[i] = 0;
  
    st[top = 0] = 0;
    for (int i = 1; i <= n; ++ i) {
      while (top && a[st[top]] < a[i]) -- top;
      son[i][0] = son[st[top]][1], son[st[top]][1] = i;
      st[++ top] = i;
    }
    rt = st[1];

    yes[rt] = 1;
    dfs(rt, 0, 0, n + 1);
    int ans = 0;
    for (int i = 1; i <= n; ++ i) if (yes[i]) ++ ans;
    std::cout << ans << "\n";
  }
  return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：2)

考虑直接怎么暴力怎么来，对于一个点 $u$ 我们左边右边能扩展就扩展，一直到不能扩展为止，再把扩展到的数贡献给加上，不难发现，假若加上之后还能扩展则再次扩展原来无法扩展的点后，数的权值翻倍，否则不能扩展则结束，又因为一个点的权值只会翻倍 $\log V$ 次，我们考虑用二分加上 ST 表维护这个过程即可做到 $O(n \log n \log V)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
const int inf = 1e18+114;
int a[maxn],pre[maxn],n;
int st[maxn][20];
int lg[maxn];
void init(){
    for(int i=1;i<=n;i++) st[i][0]=a[i];
    for(int j=1;j<20;j++)
        for(int i=1;i<=n;i++){
            if(i+(1<<(j-1))<=n) st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
            else st[i][j]=st[i][j-1];
        }
    lg[1]=0;
    for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
}
int query(int l,int r){
    int len=lg[r-l+1];
    return max(st[l][len],st[r-(1<<len)+1][len]);
}
void work(){
    cin>>n>>n;
    a[0]=a[n+1]=inf;
    for(int i=1;i<=n;i++) cin>>a[i],pre[i]=pre[i-1]+a[i];
    init();
    int ans=0;
    for(int i=1;i<=n;i++){
        int l=i,r=i;
        int now=a[i];
        while(a[l-1]<=now||a[r+1]<=now){
            int lt=0,rt=l-1;
            while(lt+1<rt){
                int mid=(lt+rt)>>1;
                if(query(mid,l-1)<=now) rt=mid;
                else lt=mid;
            }
            if(l!=1&&query(rt,l-1)<=now) now=now+pre[l-1]-pre[rt-1],l=rt;
            lt=r+1,rt=n+1;
            while(lt+1<rt){
                int mid=(lt+rt)>>1;
                if(query(r+1,mid)<=now) lt=mid;
                else rt=mid;
            }
            if(r!=n&&query(r+1,lt)<=now) now=now+pre[lt]-pre[r],r=lt;
            //cout<<i<<' '<<l<<' '<<r<<' '<<a[l-1]<<' '<<a[r+1]<<' '<<now<<'\n';
        }
        //cout<<i<<' '<<l<<' '<<r<<'\n';
        if(l==1&&r==n) ans++;
    }
    cout<<ans<<'\n';
}
signed main(){
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
11 11
1 2 3 1 1 9 3 2 4 1 3
*/

```

---

## 作者：Mirage_Insane (赞：1)

题意可以转化为：相邻的两个位置 $i$ 和 $j$，若 $a_i \geq a_j$，则将 $a_i$ 赋值为 $a_i + a_j$ 并删除 $j$，再问你最后有多少个数可以将其余所有数合并。

对原数组建立笛卡尔树，设 $L_i$ 为在 $i$ 左边的第一个比 $a_i$ 大的数的位置，$R_i$ 为在 $i$ 右边的第一个比 $a_i$ 大的数的位置。

显然 $a_i$ 可以直接把 $L_i$ 到 $R_i$ 的数合并掉，于是我们考虑当前节点 $x$ 的左右儿子。假设 $x$ 合法，当 $lson_x$ 将 $L_{lson_x}$ 和 $R_{lson_x}$ 间的数都合并掉之后比 $a_x$ 大，那么 $lson_x$ 一定也合法，否则不合法。$rson_x$ 同理。这点根据笛卡尔树的性质易得，然后就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
struct RMQ {
    int dp[200005][25], id[200005][25];
    void init(int n) {
        for(int j = 1; (1 << j) <= n; j++) {
            for(int i = 1; i + (1 << j) - 1 <= n; i++) {
                if(dp[i][j - 1] > dp[i + (1 << (j - 1))][j - 1]) {
                    dp[i][j] = dp[i][j - 1];
                    id[i][j] = id[i][j - 1];
                }
                else {
                    dp[i][j] = dp[i + (1 << (j - 1))][j - 1];
                    id[i][j] = id[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }
    int query(int l, int r) {
        if(l > r) return -0x3f3f3f3f;
        int k = log2(r - l + 1);
        if(dp[l][k] > dp[r - (1 << k) + 1][k]) return id[l][k];
        else return id[r - (1 << k) + 1][k];
    }
}ST;
int a[200005], pre[200005];
int solve(int fa, int i, int l, int r) {
    if(pre[r] - pre[l - 1] < a[fa]) return 0;
    int Le = ST.query(l, i - 1), Ri = ST.query(i + 1, r);
    return solve(i, Le, l, i - 1) + solve(i, Ri, i + 1, r) + 1;
}
signed main() {
    int T;
    SF("%lld", &T);
    while(T--) {
        int n, x;
        SF("%lld%lld", &n, &x);
        for(int i = 1; i <= n; i++) SF("%lld", &a[i]), ST.dp[i][0] = a[i], ST.id[i][0] = i, pre[i] = pre[i - 1] + a[i];
        ST.init(n);
        int Max = 0, id = 0;
        for(int i = 1; i <= n; i++) {
            if(a[i] > Max) {
                Max = a[i];
                id = i;
            }
        }
        PF("%lld\n", solve(0, id, 1, n));
    }
    return 0;
}
```

---

## 作者：jiangxinyang2012 (赞：0)

和 [这题](https://atcoder.jp/contests/arc189/tasks/arc189_d) 几乎一样。

观察样例后发现题意就是说有 $n$ 个数，每个数 $a_i$ 每次可以选择一个 $j \in \{i+1,i-1\}$，使得 $a_i \ge a_j$，将$a_i$ 变为 $a_i+a_j$ 并将 $a_j$ 删除，问有多少个 $a_i$ 可以将其它的 $n-1$ 个数全部删除。

显然我们删数是一块一块删的，能往左删就一直往左删，不能删了删右边，右边不行了再删左边，直到删完为止。

我们大概模拟一下这个过程，如果区间 $[L,i-1]$ 的最大值小于等于 $a_i$，这一段一定可以被 $a_i$ 删掉。同理，区间 $[i+1,R]$ 的最大值小于等于 $a_i$ 也一定可以被删掉。其中，用 ST 表维护处区间最大值后 $L$ 和 $R$ 是可以二分算出来的。这样就做完了。

时间复杂度我不会证，估计是两个或者三个 $\log$，反正能过。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
const int N = 200005;
const int INF = 0x3f3f3f3f;
int a[N], n;
ll s[N];
ll sum(int l, int r) {
    return s[r] - s[l - 1];
}
int st[N][30];
void st_init() {
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    int p = __lg(n);
    for (int k = 1; k <= p; k++) {
        for (int s = 1; s + (1 << k) <= n + 1; s++) {
            st[s][k] = max(st[s][k - 1], st[s + (1 << (k - 1))][k - 1]);
        }
    }
}
int mx(int l, int r) {
    int k = __lg(r - l + 1);
    int x = max(st[l][k], st[r - (1 << k) + 1][k]);
    return x;
}
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        scanf("%d%*d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
        st_init();
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int l = i, r = i;
            ll res = a[i], lr = a[i];
            while (1) {
                int L = 1, R = l - 1, p = l;
                while (L <= R) {
                    int mid = L + R >> 1;
                    if (mx(mid, l - 1) <= res) {
                        p = mid;
                        R = mid - 1;
                    } else {
                        L = mid + 1;
                    }
                }
                if (p <= l - 1) {
                    res += sum(p, l - 1);
                    l = p;
                }
                L = r + 1, R = n, p = r;
                while (L <= R) {
                    int mid = L + R >> 1;
                    if (mx(r + 1, mid) <= res) {
                        p = mid;
                        L = mid + 1;
                    } else {
                        R = mid - 1;
                    }
                }
                if (r + 1 <= p) {
                    res += sum(r + 1, p);
                    r = p;
                }
                if (res == lr) break;
                lr = res;
                if (l == 1 && r == n) break;
            }
            if (res == s[n]) ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}

```

---

## 作者：内拉组里 (赞：0)

这道题的部分分还是非常有意思的。

先考虑 $ x = n $。

# Raw

暴力枚举每个数作为最后留下的 $ j $，然后从这个数开始向两侧合并，

能并则并，不能并就换个方向继续并。

若最后被两个更大的数夹在中间两个方向都无法继续并了，那么该数一定不是 $ j $，直接跳过。

否则将 $ ans + 1 $。

不过这样只能过个样例，一个 **pts** 也拿不到。

## Analyses：

> 总时间复杂度 $ \Theta (N^2) $。
>
> 总空间复杂度 $ \Theta (N) $。

***

# ST

从 **Raw** 中不难看出，其实有些时候没必要一个一个地并，而是一块一块地并。

而一块的大小，显然前缀和存在一个单调性，故考虑二分。

- 假设右端点固定，左端点从 $ l $ 移到 $ l^\prime $，则需满足 $ \forall i \in [l^\prime,l],p[r] - p[i - 1] \ge a[i - 1] $，

  化简后得到 $ \forall i \in [l^\prime - 1,l - 1],p[r] \ge p[i] + a[i] $。

  显然令 $ f[i] = p[i] + a[i] $，则有 $ \max\limits^{l - 1}_{i = l^\prime - 1} f[i] \le p[r] $，

  这里 $ f[i] $ 只与 $ a $ 数组有关，直接预处理出来用 **ST** 表即可。

- 同样地，左端点固定，右端点从 $ r $ 移到 $ r^\prime $，

  则需满足 $ \forall i \in [r,r^\prime],p[i - 1] - p[l - 1] \ge a[i] $，

  移项得到 $ \forall i \in [r,r^\prime],p[l - 1] \le p[i - 1] - a[i] $，

  令 $ g[i] = p[i - 1] - a[i] $，则有 $ \min\limits^{r^\prime}_{i = r} g[i] \ge p[l - 1] $，

  同样可以用 **ST** 表预处理，$ \Theta (1) $ 查询。

如此，将暴力优化一下就过了。

> 有人可能会认为这样做时间复杂度是假的，
>
> 因为当每次只能一个一个地合并时，时间复杂度就退化为了 $ \Theta (N^2) $。
>
> 以一组数据为例：
>
> | 数据         | 1024 | 256  | 64   | 16   | 4    | 1    | 1    | 2    | 8    | 32   | 128  | 512  |
> | ------------ | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
> | **二分次数** | 2    | 4    | 6    | 8    | 10   | 12   | 13   | 11   | 9    | 7    | 5    | 3    |
>
> 这种情况下，每次无法合并的数字 $ a_{l - 1} $ 一定有 $ a_{l - 1} \gt 2 \sum\limits^r_{i = l} a_i $，
>
> 故在两次二分以后 $ \sum\limits^r_{i = l} a_i $ 至少会翻一倍。
>
> 而 $ a_i \le 10^9 $，所以每次二分的次数不会超过 $ \lceil \log{a_{\max}} \rceil $。
>
> 故最坏时间复杂度为 $ \Theta (N \log{a_{\max}}) $。

## Analyses：

> 总时间复杂度 $ \Theta (N \log{a_{\max}}) $。
>
> 总空间复杂度 $ \Theta (N \log{N}) $。

***

# CDQ

准确的来讲，这并不是传统意义上的 **CDQ**，只能算是分治。

从最简单的情况入手，显然一个区间里的最大值一定可以合并这整一个区间。

所以考虑最大值分治，即每次从最大值处分成两个子区间，但最大值不属于任何一个子区间。

寻找最大值位置的过程交给 **ST** 表，这里考虑跨区间信息合并。

显然地，对于一个能够并掉整个子区间的数而言，

想要合并这整个区间，那就一定要把区间内最大值并掉。

判断一下子区间数字之和能否并掉最大值即可。

## Analyses：

> 总时间复杂度 $ \Theta (N \log{N}) $，瓶颈在于 **ST** 表的预处理。
>
> 总空间复杂度 $ \Theta (N) $。

***

# Cartesian Tree

观察 **CDQ** 时递归区间的特征。

发现每个节点都大于子树中任意节点，这一点符合大根堆的性质；

同时，每个节点将当前区间分成了两段连续的区间，这一点符合二叉搜索树的性质。

故考虑**笛卡尔树**。

这题建树方法这里不再赘述，自己去翻 [**OI-Wiki**](https://oi-wiki.org/ds/cartesian-tree/)。

建完树以后从根节点 **dfs** 下去跑刚才的分治，就不需要再借助 **ST** 表找最值了。

## Analyses：

> 总时间复杂度 $ \Theta (N) $。
>
> 总空间复杂度 $ \Theta (N) $。

***

# Hard Version

如上方法都是针对 $ x = n $ 的情况的，只能通过 **Easy Version**。

**Hard Version** 的做法需要综合以上三种做法。

对于 $ x = 1 $ 的情况，直接暴力肯定不行，不妨考虑每个数对不同的 $ i $ 的贡献。

- 对于左区间的节点，假如左区间全部并起来能够并掉根节点，

  那么所有能并掉整个左区间的数字也同样能并掉整个区间。

  所以左区间的这些数字就会对根节点的 $ i $ 做出贡献，

  贡献的大小就是分治到左区间时计算出的答案，直接从左区间继承答案即可。

- 对于右区间的每个节点，需要找到最小的一个右端点，

  使得该节点至少要并掉这个右端点才能并掉根节点。

  那么该节点对对应的右端点及以后的所有 $ i $ 都有贡献。

  - 这里的二分与 **ST** 中的二分有些许不同，

    需要二分出来的是指定节点能够并掉根节点时的最小右端点，

    故对左端点的二分与 **ST** 中无异，对右端点的二分中，

    左端点固定，只有在当前区间能够并到 $ mid $，

    且（并完以后的区间依然无法向左继续并）的点才算合法。

这里只计算了根节点和右子树的贡献，左子树递归计算即可。

由于只递归左子树，故所有的递归区间的左端点都是 $ 1 $。

统计答案是跑一遍前缀和即可。

需要注意的是，所有的前缀最大值的位置的答案是固定的，不能从前缀和里求解。

因为当 $ \max_{[1,i]} $ 落在 $ i $ 上时，只有能并掉 $ [1,i - 1] $ 的数字才有可能成为答案 $ j $，

而这些数字在分治时就已经确定了。

## Analyses：

> 总时间复杂度 $ \Theta (N \log{N} \log{a_{\max}}) $。
>
> 总空间复杂度 $ \Theta (N \log{N}) $。

# Code：

不是一般的长，放在[云剪贴板](https://www.luogu.com.cn/paste/g8ysne62)里。

---

## 作者：__little__Cabbage__ (赞：0)

## Solution

显然一个区间内最大值一定有可能活到最后，于是可以考虑一个分治的策略，分别计算区间最大值左 / 右侧的和，如果这个和 $>$ 最大值，则这个区间内最大值也可能活到最后，依次往下递归就可以。区间最大值可以拿 ST 表维护，复杂度 $O(n \log n)$，瓶颈在于预处理 ST 表。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#define int long long
#define il inline
using namespace std;

const int MAXN=2e5+5,MAXlg=18; //17.609677
int n,x,a[MAXN],s[MAXN];
bitset <MAXN> b;

class __spare_table
{
private:
	
	int lg[MAXN],st[MAXN][MAXlg],pos[MAXN][MAXlg];
	
public:
	
	il void init()
	{
		for(int i=1;i<=n;++i) st[i][0]=a[i],pos[i][0]=i;
		for(int i=1;i<=MAXlg-1;++i) for(int j=1;j+(1<<i-1)<=n;++j) 
		{
			pos[j][i]=st[j][i-1]>st[j+(1<<i-1)][i-1] ? pos[j][i-1] : pos[j+(1<<i-1)][i-1];
			st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);
		}
		for(int i=2;i<=n;++i) lg[i]=lg[i>>1]+1;
	}
	
	il int q(int l,int r)
	{
		int t=lg[r-l+1];
		return st[l][t]>st[r-(1<<t)+1][t] ? pos[l][t] : pos[r-(1<<t)+1][t];
	}
} st;

il void sol(int l,int r)
{
	int mx=st.q(l,r);
	b[mx]=1;
	
	if(l==r) return;
	
	if(s[mx-1]-s[l-1]>=a[mx]) sol(l,mx-1);
	if(s[r]-s[mx]>=a[mx]) sol(mx+1,r);
}

il void solve()
{
	b&=0;
	
	cin>>n>>x;
	for(int i=1;i<=n;++i) cin>>a[i],s[i]=s[i-1]+a[i];
	
	st.init();
	
	sol(1,n);
	
	int ans=0;
	for(int i=1;i<=n;++i) ans+=b[i];
	cout<<ans<<'\n';
}

signed main()
{
	ios::sync_with_stdio(0); ios_base::sync_with_stdio(0); cin.tie(nullptr); cout.tie(nullptr);
	int T; cin>>T; while(T--) solve();
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

本题解与 E2 题解相同。

## solution

注意到这个题并不是很正经，所以我们做这题也不需要很正经（[如果你想看我口胡](https://www.cnblogs.com/alexande/articles/18389561)）。

cnblogs 上的内容于本篇博客不相同哦。

### E1

让我们先充分思考 E1。

由于 $x = n$，所以我们可以思考每个数是否可以存活到最后的暴力做法。

我们其实可以将题面中的一系列复杂操作只针对于数 $a_i$ 来说最优的策略去进行，这样我们只需要看在针对数 $a_i$ 的最优策略下，最后能否只剩下一个数 $a_i$。具体来说，我们可以将这个策略抽象为这个过程：

- 对于原始的数 $a_i$，我们先向左依次将数吃掉，我吃掉一个数就能将这个数加到 $a_i$ 上，如果左边不能再吃了，那我就掉头向右吃，吃完继续向左，以此类推。

注意到这其实是一个经典问题，假设值域是 $V$，那么我对于一个数 $a_i$ 每次能**不消化吃掉的连续段数**其实是远小于 $\log V$ 的。举个例子，假设目前 $a_i$ 向左吃，那么只要向左的一段数每个数都要 $\le a_i$，那么我们就可以把它当作一段吃掉，**但是不意味着 $a_i$ 只能吃掉这些数**（究其本质是因为没有将这些数的和加上）。

于是我们就有了一个朴素的做法了，每次二分一次不消化能够吃掉的连续段，然后吃掉继续二分，如果不能继续吃了，那我们就掉头继续吃，注意到由于在二分过程中区间最大值我们可以用 ST 表进行求解，于是对于一个 $a_i$ 进行这种的操作的单次时间复杂度为 $O(\log n \log V)$，总复杂度为 $O(n \log n \log V)$。

### E2

对 E1 进行充分思考后，我们来思考 E2。

我们发现唯一的加强点在于你需要对于每个 $i$ 都求出 $1 \sim i$ 中有多少满足条件的数，于是你还是考虑每个数对每个答案的贡献。

以下默认先向右拓展，并且将点 $i$ 拓展的过程抽象为管辖范围左端点和右端点的扩展。

考虑优化，不难发现按照 E1 的二分过程，我们其实一个数 $a_i$ 只会向右拓展 $\log V$ 个连续段，但是我们发现无法实时的维护左端点扩展的信息，咋办呢？

我们发现左端点的扩展信息其实是不那么重要的，就是我们可以先把右端点扩展完再扩展左端点，我们发现其实是对每个数的 $\log$ 个向右的连续段每段（不是上述的连续段，是向右到底再向左后的连续段）进行二分（为啥要分段二分，因为我们下一个右端点的扩展需要靠当前的这一段所供给的左端点扩展长度，比较难理解），二分到了啥时候我的当前区间值就不能覆盖整个区间了。但是我们二分左端点扩展到那时又要二分，这样就是三只 $\log$ 的了，非常的不优美。

然后我们就可以差分修改答案了。

我们发现此时我们可以对于每个前缀二分出至少当前区间总值为多少才能覆盖整个前缀，这样的预处理复杂度是两只 $\log$ 的（我好像用了线段树啥的，反正能过就行），然后我们具体计算的时候直接比大小就好了。

## code

代码写得比较狗屎，谨慎观看。

E1：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int t;
int n, x, ans;
int a[N], bin[N], logg[N], f[N][21], pre[N];

int query ( int x, int y ) {
  if ( x > y ) {
    return 1e18;
  }
  int len = y - x + 1, tmp = logg[len];
  return max ( f[x][tmp], f[y - bin[tmp] + 1][tmp] );
}

void Solve () {
  cin >> t;
  while ( t -- ) {
    ans = 0;
    cin >> n >> x;
    for ( int i = 1; i <= n; i ++ ) {
      cin >> a[i];
      f[i][0] = a[i];
      pre[i] = pre[i - 1] + a[i];
    }
    bin[0] = 1;
    logg[0] = -1;
    for ( int i = 1; i <= 20; i ++ ) {
      bin[i] = bin[i - 1] << 1;
    }
    for ( int i = 1; i <= n; i ++ ) {
      logg[i] = logg[i >> 1] + 1;
    }
    for ( int i = 1; i <= n; i ++ ) {
      for ( int j = 1;  j <= 20; j ++ ) {
        f[i][j] = 0;
      }
    }
    for ( int i = 1; i <= logg[n]; i ++ ) {
      for ( int j = 1; j <= n && j + bin[i] - 1 <= n; j ++ ) {
        f[j][i] = max ( f[j][i - 1], f[j + bin[i - 1]][i - 1] );
      }
    }
    for ( int i = 1; i <= n; i ++ ) {
      int posl = i, posr = i, sum = a[i];
      for ( int j = 1; j <= 63; j ++ ) {
        if ( j & 1 ) {
          int l = posr, r = n + 1;
          while ( l + 1 < r ) {
            int mid = l + r >> 1;
            if ( query ( posr + 1, mid ) <= sum ) {
              l = mid;
            }
            else {
              r = mid;
            }
          }
          sum += pre[l] - pre[posr];
          posr = l;
        }
        else {
          int l = 0, r = posl;
          while ( l + 1 < r ) {
            int mid = l + r >> 1;
            if ( query ( mid, posl - 1 ) <= sum ) {
              r = mid;
            }
            else {
              l = mid;
            }
          }
          sum += pre[posl - 1] - pre[r - 1];
          posl = r;
        }
      }
      if ( posl == 1 && posr == n ) {
        ans ++;
      }
    }
    cout << ans << '\n';
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

E2：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int t;
int n, x;
int a[N], bin[25], logg[N], f[N][21], pre[N], chifan[N];

struct Node {
  int l, r, ll, sum;
};

vector < Node > ans[N];

int query ( int x, int y ) {
  if ( x > y ) {
    return 4e18;
  }
  int len = y - x + 1, tmp = logg[len];
  return max ( f[x][tmp], f[y - bin[tmp] + 1][tmp] );
}

int diff[N];

void change ( int l, int r, int k ) {
  if ( l > r ) {
    return ;
  }
  diff[l] += k, diff[r + 1] -= k;
}

int tree[N << 2], tag[N << 2];

void pushup ( int node ) {
  tree[node] = max ( tree[node << 1], tree[node << 1 | 1] );
}

void addtag ( int node, int k ) {
  tree[node] += k;
  tag[node] += k;
}

void pushdown ( int node ) {
  if ( !tag[node] ) {
    return ;
  }
  addtag ( node << 1, tag[node] ), addtag ( node << 1 | 1, tag[node] );
  tag[node] = 0;
}

void update ( int node, int lt, int rt, int x, int y, int k ) {
  if ( y < lt || x > rt ) {
    return ;
  }
  if ( x <= lt && rt <= y ) {
    addtag ( node, k );
    return ;
  }
  pushdown ( node );
  int mid = lt + rt >> 1;
  update ( node << 1, lt, mid, x, y, k ), update ( node << 1 | 1, mid + 1, rt, x, y, k );
  pushup ( node );
}

int query ( int node, int lt, int rt, int x, int y ) {
  if ( y < lt || x > rt ) {
    return -4e18;
  }
  if ( x <= lt && rt <= y ) {
    return tree[node];
  }
  pushdown ( node );
  int mid = lt + rt >> 1;
  return max ( query ( node << 1, lt, mid, x, y ), query ( node << 1 | 1, mid + 1, rt, x, y ) );
}

bool Check ( int sum, int x ) {
  for ( int i = x; i >= 1; i -- ) {
    if ( sum < a[i] - ( pre[x] - pre[i] ) ) {
      return false;
    }
  }
  return true;
}

void Solve () {
  ios :: sync_with_stdio ( false );
  cin.tie ( 0 ), cout.tie ( 0 );
  cin >> t;
  while ( t -- ) {
    cin >> n >> x;
    for ( int i = 1; i <= n; i ++ ) {
      cin >> a[i];
      diff[i] = 0;
      ans[i].clear ();
      f[i][0] = a[i];
      pre[i] = pre[i - 1] + a[i];
    }
    for ( int i = 1; i <= 4 * ( n + 1 ); i ++ ) {
      tree[i] = tag[i] = 0;
    }
    for ( int i = 1; i <= n; i ++ ) {
      if ( i != 1 ) {
        update ( 1, 1, n, 1, i - 1, -a[i] );
      }
      update ( 1, 1, n, i, i, a[i] );
      chifan[i] = query ( 1, 1, n, 1, i );
    }
    bin[0] = 1;
    logg[0] = -1;
    for ( int i = 1; i <= 20; i ++ ) {
      bin[i] = bin[i - 1] << 1;
    }
    for ( int i = 1; i <= n; i ++ ) {
      logg[i] = logg[i >> 1] + 1;
    }
    for ( int i = 1; i <= n; i ++ ) {
      for ( int j = 1; j <= 20; j ++ ) {
        f[i][j] = 0;
      }
    }
    for ( int i = 1; i <= logg[n]; i ++ ) {
      for ( int j = 1; j <= n && j + bin[i] - 1 <= n; j ++ ) {
        f[j][i] = max ( f[j][i - 1], f[j + bin[i - 1]][i - 1] );
      }
    }
    for ( int i = 1; i <= n; i ++ ) {
      int posl = i, posr = i, sum = a[i];
      ans[i].push_back ( { i, i, i, 0 } );
      for ( int j = 1; j <= 85; j ++ ) {
        if ( j & 1 ) {
          int l = posr, r = n + 1;
          while ( l + 1 < r ) {
            int mid = l + r >> 1;
            if ( query ( posr + 1, mid ) <= sum ) {
              l = mid;
            }
            else {
              r = mid;
            }
          }
          ans[i].push_back ( { posr + 1, l, posl, sum } );
          sum += pre[l] - pre[posr];
          posr = l;
        }
        else {
          int l = 0, r = posl;
          while ( l + 1 < r ) {
            int mid = l + r >> 1;
            if ( query ( mid, posl - 1 ) <= sum ) {
              r = mid;
            }
            else {
              l = mid;
            }
          }
          sum += pre[posl - 1] - pre[r - 1];
          posl = r;
        }
      }
    }
    pre[n + 1] = 4e18;
    for ( int i = 1; i <= n; i ++ ) {
      for ( Node x : ans[i] ) {
        int l = x.l - 1, r = x.r + 1;
        while ( l + 1 < r ) {
          int mid = l + r >> 1;
          if ( x.sum + pre[mid] - pre[x.l - 1] < chifan[x.ll - 1] ) {
            l = mid;
          }
          else {
            r = mid;
          }
        }
        change ( l + 1, x.r, 1 );
      }
    }
    for ( int i = 1; i <= n; i ++ ) {
      diff[i] += diff[i - 1];
    }
    for ( int i = 1; i <= n; i ++ ) {
      cout << diff[i] << " ";
    }
    cout << '\n';
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

## 作者：huangboning (赞：0)

题目其实在做这样一件事情：给定 $n$ 个数，如果一个数的值大于等于两边相邻数的值，则可以将其吞并，将它的值累加到这个数。求有多少个数可以吞并所有数。

首先可以发现，每个区间中的最大值一定可以吞并区间中的所有数。此时，如果最大值到区间端点组成的小区间的数字之和小于最大值，则其中的任意一个数字都不能吞并所有数，把答案减去小区间大小。否则，就对小区间继续判断。

区间和可以用前缀和 $O(n)$ 维护，区间最大值可用线段树 $O(n \log n)$ 维护,总时间复杂度为 $O(n \log n)$ .

具体细节看代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct SegmentTree{//线段树
	int x,l,r;
	pair<int,int>maxl;//第一关键字代表最大值，第二关键字代表最大值位置
}t[800010];
int T,n,x,a[200010],s[200010],ans;
void build(int x,int l,int r){//建树
	if(l==r){//叶子节点
		t[x].l=l;
		t[x].r=r;
		t[x].maxl.first=a[l];
		t[x].maxl.second=l;
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	t[x].l=l;
	t[x].r=r;
	if(t[x*2].maxl.first>=t[x*2+1].maxl.first)t[x].maxl=t[x*2].maxl;
	else t[x].maxl=t[x*2+1].maxl;
	return;
}
pair<int,int> ask(int x,int l,int r){//查询区间最大值，返回一个二元组，表示最大值及其位置
	if(t[x].l>=l&&t[x].r<=r)return t[x].maxl;
	int mid=(t[x].l+t[x].r)/2,max1=-1e18,max2=-1e18;
	pair<int,int>p1,p2;
	if(l<=mid)p1=ask(x*2,l,r),max1=p1.first;
	if(r>mid)p2=ask(x*2+1,l,r),max2=p2.first;
	if(max1>=max2)return p1;
	else return p2;
}
void check(int l,int r){//类似于二分
	if(l==r)return;//如果只有一个数，返回
	pair<int,int>p=ask(1,l,r);
	int maxl=p.first,id=p.second;//最大值及位置
	if(maxl>s[id-1]-s[l-1])ans-=id-l;//如果最大值大于左半边区间元素和，则从答案中扣除
	else check(l,id-1);//否则继续检查左半边区间
	if(maxl>s[r]-s[id])ans-=r-id;//右半边同理
	else check(id+1,r);
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>x;
		ans=n;
		s[0]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s[i]=s[i-1]+a[i];//预处理前缀和
		}
		build(1,1,n);//建树
		check(1,n);//检查每个元素
		cout<<ans<<endl;
	}
}
```

---

