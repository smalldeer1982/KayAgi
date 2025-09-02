# [USACO24DEC] It's Mooin' Time P

## 题目描述

**注意：本题的时间限制为 3 秒，通常限制的 1.5 倍。**

Bessie 有一个长度为 $N$（$1\le N\le 3\cdot 10^5$）的字符串，仅由字符 M 和 O 组成。对于字符串中的每个位置 $i$，需要花费 $c_i$ 来将该位置上的字符修改为另一种字符（$1\le c_i\le 10^8$）。

Bessie 认为，如果字符串包含更多长度为 $L$（$1\le L\le \min(N, 3)$）的哞叫会看起来更好。一个长度为 $L$ 的哞叫指的是一个 M 后面跟着 $L-1$ 个 O。

对于从 $1$ 到 $\lfloor N/L\rfloor$ 的每一个正整数 $k$，计算将字符串修改至包含至少 $k$ 个等于长度为 $L$ 的哞叫的子串的最小花费。

## 说明/提示

- 测试点 $5$：$L=3, N\le 5000$。
- 测试点 $6$：$L=1$。
- 测试点 $7\sim 10$：$L=2$。
- 测试点 $11\sim 18$：$L=3$。

## 样例 #1

### 输入

```
1 4
MOOO
10 20 30 40```

### 输出

```
0
20
50
90```

## 样例 #2

### 输入

```
3 4
OOOO
50 40 30 20```

### 输出

```
40```

## 样例 #3

### 输入

```
2 20
OOOMOMOOOMOOOMMMOMOO
44743602 39649528 94028117 50811780 97338107 30426846 94909807 22669835 78498782 18004278 16633124 24711234 90542888 88490759 12851185 74589289 54413775 21184626 97688928 10497142```

### 输出

```
0
0
0
0
0
12851185
35521020
60232254
99881782
952304708```

## 样例 #4

### 输入

```
3 20
OOOMOMOOOMOOOMMMOMOO
44743602 39649528 94028117 50811780 97338107 30426846 94909807 22669835 78498782 18004278 16633124 24711234 90542888 88490759 12851185 74589289 54413775 21184626 97688928 10497142```

### 输出

```
0
0
0
44743602
119332891
207066974```

# 题解

## 作者：ケロシ (赞：11)

还是我，我又来介绍复杂度与 $L$ 无关的算法了（喜提最劣解）。 

首先是朴素的 dp，设 $f_{i,j}$ 为在字符串前 $i$ 位中，选了 $j$ 个哞叫子串的最小代价，那么转移很明显：

$$
w(l,r)=[s_l=\mathrm{O} ]a_l+\sum_{i=l+1}^{r}[s_i=\mathrm{M} ]a_i
$$

$$
f_{i,j}=\min(f_{i-1,j},f_{i-L,j-1}+w(i-L+1,i))
$$

然后不难发现每个 $f_i$ 都是凸的，所以考虑使用 Slope Trick 维护这个。

套路的，设 $f_i$ 的差分数组 $g_i$，那么 $g_{i,j}=f_{i,j}-f_{i,j-1}$。然后用 $g_i$ 反代 $f_i$，即 $f_{i,j}=\sum_{k=1}^{j}g_{i,k}$，然后代入 dp 式子，然后就能写出关于 $g_{i,j}$ 的转移式：

$$
\begin{aligned}
g_{i,j}&=f_{i,j}-f_{i,j-1}\\

&=\min(f_{i-1,j},f_{i-L,j-1}+w(i-L+1,i))\\

&-\min(f_{i-1,j_1},f_{i-L,j-2}+w(i-L+1,i))\\

&=\min(\sum_{k=1}^{j}g_{i-1,k},\sum_{k=1}^{j-1}g_{i-L,k}+w(i-L+1,i))\\

&-\min(\sum_{k=1}^{j-1}g_{i-1,k},\sum_{k=1}^{j-2}g_{i-L,k}+w(i-L+1,i))\\

\end{aligned}
$$

左右两个 $\min$ 差不多，所以直接观察 $\sum_{k=1}^{j}g_{i-1,k}$ 与 $\sum_{k=1}^{j-1}g_{i-L,k}+w(i-L+1,i))$ 的关系。

我们发现一个东西，就是对于上面的式子，存在一个分割点 $p$，满足 $j \le p$ 的 $\min$ 取到前者，$j>p$ 的取到后者。

这个比较难证明，大概的理解就是左边的式子 $f_{i-1}$ 相较右边 $f_{i-L}$ 右移了一位，导致了这个 $f_{i-1}$ 的变化更大，也就是更凸，到了分割点后就一直比 $f_{i-L}$ 小了。

知道了存在分割点 $p$ 后，不难发现上面关于 $g_{i,j}$ 的转移可以按照 $p$ 进行分类：

$$
g_{i,j}=
\left\{\begin{matrix}
g_{i-1,j} & j \le p\\
\sum_{k=1}^{j-1} g_{i-L,k}+w(i-L+1,i)-\sum_{k=1}^{j-1} g_{i-1,k} & j=p+1\\
g_{i-L,j-1}  & j > p + 1
\end{matrix}\right.
$$

接下来讲讲实现。

对于这个 $g_{i,j}$ 的转移，一段是从 $g_{i-1}$ 拉过来，还有一段从 $g_{i-L}$ 拉过来，所以需要持久化平衡树维护。

对于找分割点 $p$，需要先二分这个 $p$，然后去平衡树上查询一遍，这一部分是瓶颈，是 $O(\log^2 n)$ 的。

本人使用了 Leafy Tree 进行实现，还需注意这题的空间很小，需要定期把无用的点删掉。

时间复杂度 $O(n \log^2 n)$，与 $L$ 无关。

平衡树常数很大，跑很慢。

```cpp
const int N = 3e5 + 5;
const int M = 1e7 + 5;
const ll LNF = 1e18;
int n, k, m; 
string t;
ll a[N], s[N];
int rub[M], tp, lim;
int rt[N], tot, ls[M], rs[M], sz[M]; ll F[M];
bool vis[M];
int add() {
	lim ++;
	if(tp) return rub[tp --];
	return ++ tot;
}
int add(ll x) {
	int u = add();
	ls[u] = rs[u] = 0;
	sz[u] = 1;
	F[u] = x;
	return u;
}
void up(int u) {
	sz[u] = sz[ls[u]] + sz[rs[u]];
	F[u] = F[ls[u]] + F[rs[u]];
}
int up(int l, int r) {
	int u = add();
	ls[u] = l, rs[u] = r;
	up(u);
	return u;
}
int merge(int u, int v) {
	if(! u || ! v) return u | v;
	if(sz[u] <= sz[v] * 4 && sz[v] <= sz[u] * 4) {
		return up(u, v);
	}
	if(sz[u] >= sz[v]) {
		int l = ls[u], r = rs[u];
		if(sz[l] * 4 > (sz[u] + sz[v])) return merge(l, merge(r, v));
		return merge(merge(l, ls[r]), merge(rs[r], v));
	}
	else {
		int l = ls[v], r = rs[v];
		if(sz[r] * 4 > (sz[u] + sz[v])) return merge(merge(u, l), r);
		return merge(merge(u, ls[l]), merge(rs[l], r));
	}
}
void split(int u, int p, int & x, int & y) {
	if(! u || ! p) {
		x = 0, y = u;
		return;
	}
	if(sz[u] == p) {
		x = u, y = 0;
		return;
	}
	if(p <= sz[ls[u]]) {
		split(ls[u], p, x, y);
		y = merge(y, rs[u]);
	}
	else {
		split(rs[u], p - sz[ls[u]], x, y);
		x = merge(ls[u], x);
	}
}
ll query(int u, int r) {
	if(! u || ! r) return 0;
	if(sz[u] <= r) {
		return F[u];
	}
	if(r <= sz[ls[u]]) return query(ls[u], r);
	return F[ls[u]] + query(rs[u], r - sz[ls[u]]);
}
ll ans[N]; int cnt;
void print(int u) {
	if(! ls[u]) {
		ans[++ cnt] = F[u];
		return;
	}
	print(ls[u]);
	print(rs[u]);
}
void dfs(int u) {
	vis[u] = 1;
	if(! ls[u]) {
		return;
	}
	dfs(ls[u]);
	dfs(rs[u]);
}
void recycle(int l, int r) {
	FOR(i, 1, tot) vis[i] = 0;
	FOR(i, l, r) dfs(rt[i]);
	FOR(i, 1, tot) if(sz[i] && ! vis[i]) {
		sz[i] = 0; 
		rub[++ tp] = i;
		lim --;
	}
}
void solve() {
	cin >> k >> n; m = n / k;
	cin >> t; t = ' ' + t;
	FOR(i, 1, n) cin >> a[i];
	FOR(i, 1, n) s[i] = s[i - 1] + (t[i] == 'O' ? 0 : a[i]);
	REP(i, k) rt[i] = add(LNF);
	FOR(i, k, n) {
		if(lim > M - 200) recycle(i - k, i - 1);
		int L = 1, R = i / k, pos = 0;
		ll cost = s[i] - s[i - k + 1] + (t[i - k + 1] == 'M' ? 0 : a[i - k + 1]);
		while(L <= R) {
			int mid = L + R >> 1;
			ll vl = query(rt[i - 1], mid);
			ll vr = query(rt[i - k], mid - 1) + cost;
			if(vl <= vr) {
				pos = mid;
				L = mid + 1;
			}
			else {
				R = mid - 1;
			}
		}
		ll vl = query(rt[i - 1], pos + 1);
		ll vr = query(rt[i - k], pos) + cost;
		if(pos == i / k) {
			rt[i] = rt[i - 1];
		}
		else if(! pos && vl > vr) {
			rt[i] = merge(add(cost), rt[i - k]);
		}
		else {
			int x, y, z;
			split(rt[i - 1], pos, x, z);
			split(rt[i - k], pos, z, y);
			ll val = query(rt[i - k], pos) - query(rt[i - 1], pos) + cost;
			rt[i] = merge(merge(x, add(val)), y);
		}
	}
	print(rt[n]);
	FOR(i, 1, n / k) ans[i] += ans[i - 1];
	FOR(i, 1, n / k) cout << ans[i] << endl;
}
```

---

## 作者：_Ch1F4N_ (赞：8)

首先可以计算出每个区间选入答案的代价，然后考虑到答案区间不交，问题变为选出若干个长度为 $L$ 的不交区间，最小化代价和。

打表可以发现答案对选出区间数量存在凸性。

为什么呢，观察用来打表的 dp，即 $dp_{i,j}$ 表示考虑 $[1,i]$ 选出 $j$ 个区间的代价，你发现 $dp_{i,j}$ 的转移形如先把 $dp_{i-1,j}$ 复制过来，再把 $dp_{i-k,j}$ 向右上平移后与其取 $\min$，假若 $dp_{p,j}$ 在 $p<i$ 时存在凸性，那么两个上凸壳在做平移和取 $\min$ 操作后仍然是一个上凸壳，故 $dp_{i,j}$ 也是凸的，所以我们可以向下归纳证明凸性存在。

对于任意一个子区间显然也都存在凸性，考虑对序列分治，分治的过程中维护 $f_{i,j,k}$ 表示选出的最左边和最右边的区间距离区间端点的距离分别为 $i,j$ 的情况下，选出 $k$ 个区间最小化代价之和，合并就直接闵可夫斯基和，时间复杂度 $O(L^3 n \log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int L,n;
const int maxn = 3e5+114;
const int inf = 1e18;
char S[maxn];
int c[maxn];
struct info{
    vector<int> dp[3][3];//0 1 2 | 0 1 2
    info(){
        for(int i=0;i<L;i++)
            for(int j=0;j<L;j++) dp[i][j].push_back(0);
    }
};
vector<int> merge(vector<int> a,vector<int> b){
    vector<int> da,db;
    for(int i=1;i<(int)a.size();i++) da.push_back(a[i]-a[i-1]);
    for(int i=1;i<(int)b.size();i++) db.push_back(b[i]-b[i-1]);
    vector<int> dc;
    dc.push_back(a[0]+b[0]);
    int ta=0,tb=0;
    while(ta<(int)da.size()||tb<(int)db.size()){
        if(ta<(int)da.size()&&tb<(int)db.size()){
            if(da[ta]<db[tb]){
                dc.push_back(da[ta]);
                ta++;
            }else{
                dc.push_back(db[tb]);
                tb++;
            }
        }else if(ta<(int)da.size()){
            dc.push_back(da[ta]);
            ta++;
        }else{
            dc.push_back(db[tb]);
            tb++;
        }
    }
    for(int i=1;i<(int)dc.size();i++) dc[i]+=dc[i-1];
    /*
    cout<<"merge ----------------------\n";
    for(int x:a) cout<<x<<' ';
    cout<<'\n';
    for(int x:b) cout<<x<<' ';
    cout<<'\n';
    for(int x:dc) cout<<x<<' ';
    cout<<'\n';*/
    return dc;
}
vector<int> min(vector<int> a,vector<int> b){
    if(a.size()>b.size()) swap(a,b);
    for(int i=0;i<a.size();i++) b[i]=min(b[i],a[i]);
    return b;
}
void work(info &x){
    for(int i=L-1;i>=1;i--){
        for(int j=0;j<L;j++){
            x.dp[i-1][j]=min(x.dp[i-1][j],x.dp[i][j]);
        }
    }
    for(int j=L-1;j>=1;j--){
        for(int i=0;i<L;i++){
            x.dp[i][j-1]=min(x.dp[i][j-1],x.dp[i][j]);              
        }
    }    
}
int W[maxn];
int w(int p){
    int res=0;
    res+=(S[p]!='M')?c[p]:0;
    for(int i=1;i<=L-1;i++){
        res+=(S[p+i]!='O')?c[p+i]:0;
    }   
    return res;
}
info solve(int l,int r){
    if(r-l+1<2*L){
        info res=info();
        for(int i=0;i<L;i++){
            int lt=l+i;
            if(lt+L-1<=r) res.dp[i][r-(lt+L-1)].push_back(W[lt]);
        }
        work(res);
        return res;
    }
    int mid=(l+r)>>1;
    info ldp=solve(l,mid),rdp=solve(mid+1,r);   
    info res=info();
    for(int i=0;i<L;i++){
        for(int j=0;j<L;j++) res.dp[i][j]=merge(ldp.dp[i][0],rdp.dp[0][j]);
    }
    for(int i=0;i<L;i++){
        for(int j=0;j<L;j++){
            for(int k=1;k<L;k++){
                res.dp[i][j]=min(res.dp[i][j],merge(merge(ldp.dp[i][k],rdp.dp[L-k][j]),{0,W[mid-k+1]}));
            }
        }
    }
    work(res);
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>L>>n;
    for(int i=1;i<=n;i++) cin>>S[i];
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i+L-1<=n;i++) W[i]=w(i);
    info dp=solve(1,n);
    for(int i=1;i<=(n/L);i++) cout<<dp.dp[0][0][i]<<'\n';
    return 0;
}
```

---

## 作者：Purslane (赞：5)

# Solution

设 $v_i$ 表示，变出一个以 $i$ 开头的 $\rm MOO$ 需要的代价。

则我们需要选出 $1 \le p_1 < p_2 < \cdots < p_k$，满足 $\forall 1 \le i < k$ 都有 $p_{i+1} - p_i \ge L$，并且 $\text{minimize} \sum_{i=1}^k v_{p_i}$。

先考虑 $L=1$，这个太简单了，直接使用小根一个堆，每次**选出转化代价最小的点**即可。

而我们声称答案具有凸性。

证明（来自官网，感觉很有意思）：

设选 $i$ 个点需要的最小代价是 $f_i$，我们想证明凸性，即 $f_{i-1} + f_{i+1} \ge 2 f_i$。

对于这种问题的证明，**我们可以将其转化为：给定 $k=i-1$ 和 $k=i+1$ 的解，就一定对 $k=i$ 构造一组解，其代价小于等于 $\dfrac{f_{i-1}+f_{i+1}}{2}$**。

假设你已经知道 $i-1$ 和 $i+1$ 的构造。**将两种构造的 $2i$ 条线段当成点，重叠的线段连边，会得到一个二分图，如下图所示**

![](https://s21.ax1x.com/2024/12/25/pAvF5yF.png)

重要性质：

1. 所有连通块**都是一条链**，分为四种情况：两个完全相同的线段的配对；减少连通块（最左边的情形）；不变连通块（中间的情形）；增加连通块（最右边的情形）。
2. 当 $i-1$ 的构造固定时，我们**可以调整 $i+1$ 的构造使得这三种连通块不会太多**。具体而言，对于不变连通块，**显然两侧的连通块的代价是一样的，否则可以调整**，而此时又可以将两侧调整成完全对齐；如果有减少连通块，一定有增加连通块，那这两个连通块两侧的代价和还是一样的，那么也可以用类似的手段调整为完全对齐。因此我们可以选择一个 $i+1$ 的构造，使得只有两个增加连通块。
3. 在上述的所有调整中，并不会产生新的边。因为我们可以对每个连通块想象一个左右边界，每次调整边界只会缩小不会增多，因此不会新增边，也不可能产生矛盾。

因此，$f_{i+1}-f_{i-1}=\Delta_1 + \Delta_2$，这两个 $\Delta$ 是上升链的增量。我们调整使得权值增加 $\min\{\Delta_1,\Delta_2\}$ 即可达成目的。

回到本题，我们知道了凸性，可以考虑分治。设 $s_{l,r,\ge 0/\ge 1/\ge 2,\ge 0/\ge 1/\ge 2}$ 表示的是区间 $[l,r]$ 中，选择了若干个点，最左、右端的点离左右端点的距离为 $0/1/\ge 2$，所需要的最小代价。

这个东西是凸的，因此可以使用**闵可夫斯基和进行合并**，复杂度为 $O(n \log n L^2)$。（注意长度为 $len$ 的区间中只有 $\lfloor \dfrac{len}{L} \rfloor$ 个元素）

可能有一些 Corner Case，所以我选择对长度 $\le 6$ 的区间进行暴力。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10,INF=1e16;
int n,L,c[MAXN],v[MAXN];
vector<int> operator +(vector<int> a,vector<int> b) {
	vector<int> ans;
	int p1=0,p2=0;
	while(p1<a.size()&&p2<b.size()) {
		ans.push_back(a[p1]+b[p2]);
		if(p1+1<a.size()&&p2+1<b.size()) {
			if(a[p1+1]-a[p1]<b[p2+1]-b[p2]) p1++;
			else p2++;	
		}
		else if(p1+1<a.size()) p1++;
		else p2++;
	}
	return ans;
}
vector<int> get_min(vector<int> a,vector<int> b) {
	while(a.size()<b.size()) a.push_back(INF);
	ffor(i,0,(int)b.size()-1) a[i]=min(a[i],b[i]);
	return a;
}
struct INFO {vector<int> vc[3][3];};
int dp[6][6];
INFO solve(int l,int r) {
	if(r-l+1<=5) {
		INFO res;
		ffor(d1,0,L-1) ffor(d2,0,L-1) {
			memset(dp,0x3f,sizeof(dp));
			ffor(i,l,r) if(i-l>=d1&&r-i>=d2) {
				dp[i-l+1][1]=v[i];
				ffor(j,2,i-l+1) if(i-l+1-L>=0) dp[i-l+1][j]=min(dp[i-l+1][j],dp[i-l+1-L][j-1]+v[i]);
				ffor(j,1,i-l+1) dp[i-l+1][j]=min(dp[i-l+1][j],dp[i-l][j]);
			}
			vector<int> ans;
			ans.push_back(0);
			ffor(j,1,r-l+1) {
				int mn=INF;
				ffor(p,l,r) mn=min(mn,dp[p-l+1][j]);
				if(mn<=1e10) ans.push_back(mn);
				else break ;	
			}
			res.vc[d1][d2]=ans;
		}
		return res;
	}
	int mid=(l+r>>1);
	INFO li=solve(l,mid),ri=solve(mid+1,r);
	INFO res;
	ffor(d1,0,L-1) ffor(d2,0,L-1) ffor(j,0,L-1) res.vc[d1][d2]=get_min(res.vc[d1][d2],li.vc[d1][j]+ri.vc[L-1-j][d2]);
	return res;
}
string S;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>L>>n>>S,S="&"+S;
	ffor(i,1,n) cin>>c[i];
	ffor(i,1,n-L+1) {
		if(S[i]=='O') v[i]+=c[i];
		ffor(j,i+1,i+L-1) if(S[j]=='M') v[i]+=c[j];	
	}
	auto info=solve(1,n-L+1);
	ffor(i,0,L-1) ffor(j,0,L-1) info.vc[0][0]=get_min(info.vc[0][0],info.vc[i][j]);
	ffor(i,1,n/L) cout<<info.vc[0][0][i]<<'\n';
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：5)

比较明显的凸优化 dp 题。

首先处理一个长度为 $n-L+1$ 的数组 $b_i$ 表示区间 $[i,i+L-1]$ 修改到正确形式的代价是什么。那么就是要求两两至少间隔 $L$ 地选取 $b_i$，这样保证不交，然后最小化代价和。即：选取一个长度为 $L$ 的子序列 $p$ 要求任意 $p_{i+1}-p_i\ge L$，明显可以 dp，发现具有凸性，可以见[此](https://www.cnblogs.com/SoyTony/p/Learning_Notes_about_DP_Optimization_3.html)。

然后直接分治做即可，两边的合并是 $(\max,+)$ 卷积，而其具有凸性，因此可以闵可夫斯基和优化。时间复杂度 $\mathcal O(L^3n\log n)$，因为你可能需要设计一个，两边的首个选取位置距离分治中心有多远的，来完成合并。

---

## 作者：LastKismet (赞：0)

# Sol
记 $f_i$ 表示使存在 $i$ 个要求区间的最小代价，不难发现 $f$ 是有单调性的。

考虑对序列分治，合并时除了两边的答案整合更新，还需要额外考虑跨越中界的新块。

先说两边答案整合更新吧，其实就是 Min-Add 卷积，直接闵可夫斯基和优化即可。

考虑中间的情况，发现 $L$ 很小，我们额外开两维状态，维护两个边界距最近的被选中字符串的距离。这个可以顺手后缀取 $\min$ 一下。合并时令中间空出足够一个新区间的长度并更新相应答案即可。具体实现可以参考代码。

除此之外就没什么了，预处理区间贡献是简单的。

注意为了方便代码中重载了多项式 `+=`。

# Code
```cpp
int len,n;
string s;
ll c[N],b[N];
struct node{
    vec<ll> v[L][L];
    node(){rep(i,0,2)rep(j,0,2)v[i][j].resize(1,0);}
};
inline void operator+=(vec<ll> &a,const vec<ll> &b){
    if(a.size()<b.size())a.resize(b.size(),INF);
    repl(i,0,b.size())chmin(a[i],b[i]);
}
inline vec<ll> mincowski(vec<ll> a,vec<ll> b){
    per(i,a.size()-1,1)a[i]-=a[i-1];
    per(i,b.size()-1,1)b[i]-=b[i-1];
    vec<ll> c(a.size()+b.size()-1);
    merge(a.begin()+1,a.end(),b.begin()+1,b.end(),c.begin()+1);
    c[0]=a[0]+b[0];
    repl(i,1,c.size())c[i]+=c[i-1];
    return c;
}

node solve(int l,int r){
    node res;
    if(r-l+1<(len<<1)){
        rep(i,0,r-l+1-len)res.v[i][r-(l+i+len-1)].resize(2,b[l+i]);
    }else{
        int m=l+r>>1;
        node lres=solve(l,m),rres=solve(m+1,r);
        repl(lf,0,len)repl(rt,0,len){
            res.v[lf][rt]+=mincowski(lres.v[lf][0],rres.v[0][rt]);
            rep(k,1,len-1)res.v[lf][rt]+=mincowski(mincowski(lres.v[lf][k],rres.v[len-k][rt]),{0,b[m-k+1]});
        }
    }
    per(i,len-1,1)repl(j,0,len)res.v[i-1][j]+=res.v[i][j];
    per(j,len-1,1)repl(i,0,len)res.v[i][j-1]+=res.v[i][j];
    return res;
}

inline void Main(){
    read(len,n,s);s=" "+s;
    rep(i,1,n)read(c[i]);
    rep(i,1,n-len+1){
        b[i]=(s[i]!='M')*c[i];
        repl(j,1,len)b[i]+=(s[i+j]!='O')*c[i+j];
    }
    auto f=solve(1,n);
    rep(k,1,n/len)put(f.v[0][0][k]);
}
```

---

