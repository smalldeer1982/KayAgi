# [JOI 2025 Final] 缆车 / Mi Teleférico

## 题目背景


译自 [第24回日本情報オリンピック 本選](https://contests.ioi-jp.org/joi-ho-2025/index.html) T3。

Mi Teleférico 指的是连接玻利维亚拉巴斯市（La Paz）及埃尔阿尔托市（El Alto）的缆车系统。


## 题目描述


给定一张 $N$ 个点 $M$ 条边的有向无环图。这张有向图的边是由 $P$ 个公司（编号 $1\sim P$）修建的，每条边恰好被一个公司修建。

节点标号 $1\sim N$，第 $i$（$1\le i\le M$）条边由节点 $A_i$ 指向节点 $B_i$，且是公司 $C_i$ 修建的。这里，保证 $A_i\lt B_i$。

有 $Q$ 个询问，每个询问给定区间 $[L,R]$（$1\le L\le R\le P$）和钱数 $X$。目标是从 $1$ 号点只经过编号 $\in [L,R]$ 的公司修建的边，可以到达其他任意一个节点。

为此，可以选择一个新的区间 $[l',r']$（$1\le l'\le r'\le P$），将 $[L,R]$ 变为 $[l',r']$。这会花费 $|L'-l'|+|R-r'|$ 的代价，这个操作**至多只能执行一次**。操作的代价必须不大于钱数 $X$。

对于每个询问，判断是否能够达成目标。

## 说明/提示


### 样例解释

#### 样例 $1$ 解释

第 $1$ 个询问中，$[3,7]$ 已经可以满足条件，无需进行操作。

第 $2$ 个询问中，$[5,6]$ 不满足条件，然后无法进行任何操作，所以无法达成目标。


该样例满足所有子任务的限制。


#### 样例 $2$ 解释

第 $1$ 个询问中，选择 $l'=1,r'=5$，花费 $5$ 的代价可以达成目标。

该样例满足子任务 $2,3,5\sim 7$ 的限制。


#### 样例 $3$ 解释
该样例满足子任务 $6,7$ 的限制。



#### 样例 $4$ 解释

该样例满足子任务 $5\sim 7$ 的限制。



### 数据范围

- $2\le N\le 3\times 10^5$。
- $1\le M\le 3\times 10^5$。
- $1\le P\le 10^9$。
- $1\le A_i\lt B_i\le N$（$1\le i\le M$）。
- $1\le C_i\le P$（$1\le i\le M$）。
- $1\le Q\le 4\times 10^5$。
- $1\le L_i\le R_i\le P$（$1\le i\le Q$）。
- $0\le X_i\le 10^9$（$1\le i\le Q$）。
- 输入的都是整数。

### 子任务

1. （7pts）$N,M,Q\le 50$，$X_i=0$（$1\le i\le Q$）。
2. （8pts）$P\le 10$。
3. （11pts）$P\le 100$。
4. （23pts）$P\le 3\times 10^5$，$X_i=0$（$1\le i\le Q$）。
5. （9pts）$P\le 3\times 10^5$。
6. （22pts）$N,M\le 8,000$。
7. （20pts）无额外限制。

## 样例 #1

### 输入

```
4 6 10
1 2 3
2 4 7
1 2 6
2 3 5
3 4 2
3 4 8
4
3 7 0
5 6 0
3 4 0
1 9 0```

### 输出

```
Yes
No
No
Yes```

## 样例 #2

### 输入

```
4 6 10
1 2 3
2 4 7
1 2 6
2 3 5
3 4 2
3 4 8
3
5 6 10
3 4 1
7 8 3```

### 输出

```
Yes
No
Yes```

## 样例 #3

### 输入

```
3 1 1000000000
1 2 6
1
1 1000000000 1000000000```

### 输出

```
No```

## 样例 #4

### 输入

```
5 9 2000
2 3 1814
2 3 457
1 2 1226
3 4 1354
1 5 1050
1 2 1725
2 3 1383
1 5 1626
1 4 1795
5
850 1872 128
82 428 1217
487 924 573
1639 1926 202
202 420 25```

### 输出

```
Yes
Yes
Yes
Yes
No```

# 题解

## 作者：lovely_nst (赞：7)

# P11664 [JOI 2025 Final] 缆车

## 前言

vector 还是太好用了，二分跳了一晚上。

## 正文

这里定义 $[l,r]$ 为好的区间即从 $1$ 号点只经过编号 $\in[l,r]$ 的公司修建的边，可以到达其他任意一个节点。

该图为一个 DAG，若要满足从 $1$ 号点可以到达所有点，就要满足除 $1$ 号点外所有点都有至少一条边通向它。因此问题就转化为了每个点所有通向它的权值是否有至少一个在 $[l,r]$ 中。

设 $r_i$ 为满足 $[i,r_i]$ 为好区间的最小值。那该如何求 $r_i$？

发现该问题具有单调性，若 $L\le l\le r\le R$ 且 $[l,r]$ 是好区间，则 $[L,R]$ 也是好区间。

因此，$r_i\le r_j(i<j)$。

证明：因为 $i<j\le r_j=r_j$，那 $[i,r_j]$ 也一定是好区间因此 $r_i\le r_j$。

用双指针+线段树求即可。

回到题目，思考 $X=0$ 时如何求解，即 $r_L\le R$ 时为 `Yes`，否则为 `No`。

当 $X\ne 0$ 时，可以得出区间长度越大则越优。询问可以转化为是否存在 $i$ 满足 $r_{L-X+i}\le R+i(0\le i\le X)$，继续转化：

$$
r_{L-X+i}\le R+i\\
R+i-r_{L-X+i}\ge 0\\
R-(L-X)+L-X+i-r_{L-X+i}\ge 0\\
f_i=i-r_i\\
R-L+X+f_{L-X+i}\ge 0\\
$$

发现前面是定值，后面的一定越大越好，那就可以用 RMQ 求 $[L-X,L]$ 中最大的 $f_i$。

因为原题的数据较大，要离散化，在两个点间的 $r_i$ 是不变的，那 $i$ 越大 $f_i=i-r_i$ 就越大，特殊处理 $f_R$ 就可以了。

## AC Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n , m , p , q;
const int N = 4e5 + 5 , inf = 0x7f7f7f7f7f7f7f7f;
vector <int> a[N] , g[N];
int d[4 * N] , R[N] , f[N][21] , lg[N] , s[N] , cc = 0;
void update (int l , int c , int s , int t , int p)
{
	if (s == t)
  	{
    	d[p] = c;
    	return;
  	}
	int m = s + t >> 1;
	if (l <= m) update (l , c , s , m , p << 1);
	if (l > m) update (l , c , m + 1 , t , p << 1 | 1);
	d[p] = min (d[p << 1] , d[p << 1 | 1]);
}
int getmax (int l , int r)
{
	int fl = lower_bound (s , s + cc , l) - s + 1 , fr = lower_bound (s , s + cc , r) - s + 1;
	if (fl == fr)
		return r - R[fr - 1];
	int Lg = lg[fr - fl];
	return max (max (f[fl][Lg] , f[fr - (1 << Lg)][Lg]) , r - R[fr - 1]);
}
signed main ()
{
	ios::sync_with_stdio (0) , cin.tie (0) , cout.tie (0);
	cin >> n >> m >> p;
	for (int i = 1;i <= m;i ++)
	{
		int v , w;
		cin >> v >> v >> w;
		g[v].push_back (w);
		s[cc ++] = w;
	}
	sort (s , s + cc) , cc = unique (s , s + cc) - s;
	for (int i = 1;i <= n;i ++)
		for (int j : g[i])
			a[lower_bound (s , s + cc , j) - s].push_back (i);
	int l = 0 , p = cc;
	memset (R , 0x7f , sizeof R);
	memset (d , -1 , sizeof d);
	update (1 , inf , 1 , n , 1);
	for (int r = 0;r < p;r ++)
	{
		for (int i : a[r])
			update (i , r , 1 , n , 1);
		while (l <= d[1]) R[l ++] = s[r];
	}
	s[p] = inf;
	lg[0] = -1;
	for (int i = 0;i < p;i ++) f[i + 1][0] = s[i] - R[i] , lg[i + 1] = lg[i + 1 >> 1] + 1;
	for (int k = 1;k <= lg[p];k ++)
		for (int i = 1;i + (1 << k) - 1 <= p;i ++)
			f[i][k] = max (f[i][k - 1] , f[i + (1 << k - 1)][k - 1]);
	cin >> q;
	for (int i = 1;i <= q;i ++)
	{
		int x , y , c;
		cin >> x >> y >> c;
		cout << (y - x + c + getmax (x - c , x) >= 0 ? "Yes\n" : "No\n");
	}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：6)

**观察 $1$**：对于一张 DAG，从 $1$ 号点出发能到达所有点的充要条件是 $1$ 号点入度为 $0$ 且其它点入度均不为 $0$。

> - 必要性显然：如果存在边 $u \to 1$ 那 $1$ 号点一定到不了 $u$；如果点 $u(u \ne 1)$ 没有入度那 $1$ 显然到不了 $u$。
> - 充分性证明：考虑设 $f_u = 0/1$ 表示 $1$ 能否到达 $u$。如果 $u$ 有入度并且 $f_u = 0$，那么其所有入点 $v$ 都要有 $f_v = 0$。由于图没有环，一直推下去一定会到一个没有入度的点。

**观察 $2$**：合法区间有单调性，即如果 $[l,r]$ 合法所有包含 $[l,r]$ 的区间都合法。

至此 $x_i = 0$ 的部分分已经可以解决：将所有边按照 $c_i$ 排序，考虑双指针求出 $l_i$ 表示最大的 $l$ 满足 $[l,i]$ 是合法区间。根据第一条观察，只需要维护入度为 $0$ 的点的数量，容易在加入和删除边的时候 $\mathcal O(1)$ 维护。

我们希望求出使得 $[l,r]$ 变得合法的最小代价，显然 $l$ 只会变小 $r$ 只会变大。特判掉 $l,r$ 中某一个不改变的情况后，$[l,r]$ 一定只会变成 $\mathcal O(n)$ 个极小区间中的某一个。相当于要求 $l' \le l,r' \ge r$ 的有用区间里，$r' - r + l - l'$ 的最小值。随着 $r'$ 的增加 $l'$ 也增加，因此满足上述条件的有用区间在序列上也是一个区间，可以直接 RMQ 维护 $r' - l'$ 的最小值。

颜色的值域比较大，在离散化的时候可能有一些细节需要注意。

总复杂度 $\mathcal O((n + m + q) \log m)$。


```cpp
/**
 *    author: sunkuangzheng
 *    created: 03.02.2025 11:20:53
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
template <class S,S (*op)(S,S)> struct rmq{
    /*
        init : time O(n log n) memory O(n log n)
        query: O(1)
    */
    private:
        vector<vector<S>> st; int n,lg;
    public:
        rmq() : rmq(0){}
        rmq(int _n){
            n = _n,lg = __lg(n),st.resize(lg + 1,vector<S>(n + 1));
        }void init(vector<S> a){ // 1-indexd
            for(int i = 1;i <= n;i ++) st[0][i] = a[i];
            for(int j = 1;j <= lg;j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
                st[j][i] = op(st[j-1][i],st[j-1][i+(1<<j-1)]);
        }void init(S *a){
            vector<S> tmp(n + 1);
            for(int i = 1;i <= n;i ++) tmp[i] = a[i];
            init(tmp);
        }S qry(int l,int r){
            int k = __lg(r - l + 1);
            return op(st[k][l],st[k][r-(1<<k)+1]);
        }
};
int T,n,m,p,u,v,w,a[N],c[N],d[N],l[N],q,L,R,x,t[N]; 
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m >> p; vector<int> b; vector<pair<int,int>> g;
    for(int i = 1;i <= m;i ++) cin >> u >> v >> w,g.emplace_back(w,v),b.push_back(w);
    sort(g.begin(),g.end()),sort(b.begin(),b.end()),b.erase(unique(b.begin(),b.end()),b.end());
    for(int i = 0;i < m;i ++) c[i+1] = g[i].first,a[i+1] = g[i].second;
    int j = 1,cnt = 0;
    auto upd = [&](int v,int p){
        if(p == 1 && !(d[v] ++)) cnt ++;
        if(p == -1 && !(-- d[v])) cnt --;
    }; c[0] = -1e9;
    rmq<int,[](int x,int y){return min(x,y);}> st(m);
    for(int i = 1;i <= m;i ++){
        upd(a[i],1);
        while(cnt == n - 1) upd(a[j],-1),j ++;
        l[i] = c[j - 1],t[i] = c[i] - l[i];
    }st.init(t);
    for(cin >> q;q --;){
        cin >> L >> R >> x; int mc = 2e9;
        int pos = upper_bound(c+1,c+m+1,R) - c - 1;
        if(pos && l[pos] >= L) {cout << "Yes\n"; continue;}
        if(pos) mc = L - l[pos];
        int sop = lower_bound(l+1,l+m+1,L) - l;
        if(pos + 1 != sop) mc = min(mc,st.qry(pos + 1,sop - 1) - R + L);
        if(sop <= m) mc = min(mc,c[sop] - R);
        cout << (mc <= x ? "Yes\n" : "No\n");
    }
}
```

---

## 作者：Starrykiller (赞：4)

SpadeA261 姐姐生日快乐！

对于 $\forall 1\le i\le P$，求出最小的 $r_i$，使得 $[i,r_i]$ 符合条件（特别地，若不存在，则为 $+\infty$）。这个不难利用双指针 $\Theta(P+m)$ 求出。

判掉当前区间已经被包含的情况后，题目中的操作可以看成一次可以花费 $1$ 的代价将左/右端点移动 $1$。拍到二维平面上就是查询 Manhattan 距离最近点，而这是平凡的，直接树状数组+扫描线即可。

时间复杂度线性对数。

---

## 作者：Your_Name (赞：2)

### 题解
* 事实：在 DAG 上，$\forall i\in [2,n]$ 满足 $in_i>0$（其中 $in_i$ 表示 $i$ 这个点的入度）是从 $1$ 号点可以到达其他任意一个节点的充要条件。

所以，我们发现可以把所有边按公司编号离线下来，然后使用双指针就可以轻松算出以公司 $i$ 为右端点时满足能从 $1$ 号点到所有点的最大左端点，我们记为 $mx_i$。具体实现可以用线段树加减边，但我们发现其实只有单点修改全局查询，直接用 multiset 存一下每个点的入度即可。

然后我们就解决了询问中 $X=0$ 的情况。对于其他情况，我们考虑我们的查询区间其实就变成了 $[L-a,R+b]$ 且 $a+b=X$。

那么我们把二式带入，就变成了 $[L-X+b,R+b]$，那么有解的条件也就是 $mx_{R+b}\ge L-X+b$。

这时我们发现还是不太好判断，那么我们考虑把式子两边都减去一个 $R+b$。也就变成：$mx_{R+b}-(R+b)\ge L-R-X$。

这也是个比较经典的套路，把变量和下标一起考虑。那么我们用 st 表直接维护 $f_i=mx_i-i$，查询 $i\in [R,R+X]$ 中 $f_i$ 的最大值有没有满足上式的就行。
### AC_Code
代码比较简短，思路也比较清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;//开大点，有可能全不一样
int n, m, p, t, in[N], mx[N], f[N][22];
struct node{int a, b, c;};
vector<node>e, q;
vector<int> v;
multiset<int> s;
int find(int x){return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;}
void add(node x){if(x.b == 1)return;s.erase(s.find(in[x.b])), s.insert(++ in[x.b]);}
void del(node x){if(x.b == 1)return;s.erase(s.find(in[x.b])), s.insert(-- in[x.b]);}
int get(int l, int r){int k = log2(r - l + 1);return max(f[l][k], f[r - (1 << k) + 1][k]);}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> p;
    for(int i = 1; i <= m; i ++){
        int a, b, c;
        cin >> a >> b >> c;
        v.push_back(c);
        e.push_back({a, b, c});
    }
    cin >> t;
    for(int i = 1; i <= t; i ++){
        int a, b, c;
        cin >> a >> b >> c;
        v.push_back(a), v.push_back(b), v.push_back(b + c);
        q.push_back({a, b, c});
    }
    sort(v.begin(), v.end());
    sort(e.begin(), e.end(), [](auto a, auto b){return a.c < b.c;});
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 0; i < m; i ++)e[i].c = find(e[i].c);
    for(int i = 2; i <= n; i ++)s.insert(in[i]);//别加 1 号点
    for(int i = 1, j = 0, k = 0; i <= v.size(); i ++){
        while(j < e.size() && e[j].c <= i)add(e[j ++]);//更新新边
        while(*s.begin() > 0 && k < e.size())mx[i] = e[k].c, del(e[k ++]);//找最大的左端点
        mx[i] = max(mx[i], mx[i - 1]);//显然要继承
        if(mx[i])f[i][0] = v[mx[i] - 1] - v[i - 1];//是用原来的差
        else f[i][0] = -2e9;//这里肯定是负值所以当不存在的时候要小一点
    }
    for(int j = 1; j < 22; j ++)for(int i = 1; i + (1 << j) - 1 <= v.size(); i ++)f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);//st表初始化
    for(int i = 0; i < t; i ++){
        if(q[i].c == 0){cout << ((mx[find(q[i].b)] >= find(q[i].a)) ? "Yes\n" : "No\n");}
        else cout << ((get(find(q[i].b), find(q[i].b + q[i].c)) >= q[i].a - q[i].b - q[i].c) ? "Yes\n" : "No\n");
    }//上面的式子
    return 0;
}
```
_完结撒花。_

---

## 作者：whx2009 (赞：1)

## 本题思路：
这道题难度不大（离散化需要特别注意，一步出问题直接调一天），我们可以知道一个有向无环的图只要除了一号节点的入度都大于等于一那么从一开始就一定能到所有节点。

我们考虑先离散化，然后求出合法区间。这是容易的，我们可以直接开一棵线段树，记录每个节点连向他的边中公司编号最大的，显然当前公司到除一号节点之外的其他节点被连边的最小编号之间是合法的。

处理完了合法区间，我们再分类讨论一下几种情况。首先我们现在要走的公司区间中间已经包含了一个好的区间，那么显然是不用移动直接就可以了。然后就是两者不相互包含，我们分讨合法区间在当前区间右边和左边的情况即可，在左边就只用移左端点，右边就是右端点直接扫描线就行。最后就是他被包含的情况，我们还是用扫描线，右端点从大到小排序，把比当前右端点右的合法线段左端点上打上贡献（这里自己推一下，也不难，想一想线段包含的情况合法线段的左右端点和需要线段的左右端点的大小关系），树状数组维护每一条要求的线段的左端点左边的点的贡献最小的值即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mid (tr[p].l+tr[p].r)/2
using namespace std;
int b[400005];
struct f{int x,y,k;}a[400005];
vector<int>s[400005];
struct f1{int id,l,r,x;}c[400005];
bool cmp(f1 x,f1 y){return x.r<y.r;}
int dp[400005],dis[400005];
struct f2{int l,r,mi;}tr[400005*4];
void wei(int p){tr[p].mi=min(tr[p*2].mi,tr[p*2+1].mi);}
void jianshu(int p,int l,int r){
	tr[p].l=l,tr[p].r=r;
	if(l==r){tr[p].mi=0;return;}
	jianshu(p*2,l,mid),jianshu(p*2+1,mid+1,r);
	wei(p);
}
void xiugai(int p,int l,int k){
	if(tr[p].l==tr[p].r){tr[p].mi=k;return;}
	if(l<=mid) xiugai(p*2,l,k);
	if(l>mid) xiugai(p*2+1,l,k);
	wei(p);
}
int ans[400005];
int tr1[400005],cnt;
int suan(int p){return p&(-p);}
void add(int p,int k){for(int i=p;i<=cnt;i+=suan(i)) tr1[i]=min(tr1[i],k);}
int cha(int p){int ans=1e18;for(int i=p;i;i-=suan(i)) ans=min(ans,tr1[i]);return ans;}
bool cmp1(f1 x,f1 y){return x.l>y.l;}
signed main(){
	int n,m,p;cin>>n>>m>>p;
	for(int i=1;i<=m;i++){
		cin>>a[i].x>>a[i].y>>a[i].k;
		b[i]=a[i].k;
	}
	sort(b+1,b+1+m);jianshu(1,2,n);
	cnt=unique(b+1,b+1+m)-b-1;
	for(int i=1;i<=cnt;i++) tr1[i]=1e18;
	for(int i=1;i<=m;i++){
		a[i].k=lower_bound(b+1,b+1+cnt,a[i].k)-b;
		s[a[i].k].push_back(i);
	}
	int q;cin>>q;
	for(int i=1;i<=q;i++){cin>>c[i].l>>c[i].r>>c[i].x;c[i].id=i;}
	sort(c+1,c+1+q,cmp);
	for(int i=1;i<=cnt;i++){
		for(int j=0;j<s[i].size();j++){
			int r=a[s[i][j]].y;
			xiugai(1,r,i);
		}
		if(tr[1].mi!=0){dp[i]=tr[1].mi;}
		else dp[i]=1e18;
	}
	int l=1,mi=-1e18;
	for(int i=1;i<=q;i++){
		while(b[l]<=c[i].r&&l<=cnt){if(dp[l]!=1e18)mi=max(mi,b[dp[l]]);l++;}
		if(mi>=c[i].l) ans[c[i].id]=1;
		else if(c[i].l-mi<=c[i].x) ans[c[i].id]=1;
	}
	l=cnt;
	for(int i=q;i>=1;i--){
		while(b[l]>=c[i].r&&l){if(dp[l]!=1e18)add(dp[l],b[l]-b[dp[l]]);l--;}
		if(c[i].l<=b[cnt]){
			int id=lower_bound(b+1,b+1+cnt,c[i].l)-b;
			if(b[id]>c[i].l) id--;
			if(-c[i].r+c[i].l+cha(id)<=c[i].x) ans[c[i].id]=1;
		}
	}
	mi=1e18;sort(c+1,c+1+q,cmp1);l=cnt;
	for(int i=1;i<=q;i++){
		if(dp[l]==1e18) l=0;
		while(l>0&&b[dp[l]]>=c[i].l){mi=min(mi,b[l]);l--;if(dp[l]==1e18)l=0;}
		if(mi<=c[i].r) ans[c[i].id]=1;
		else if(mi-c[i].r<=c[i].x) ans[c[i].id]=1;
	}
	for(int i=1;i<=q;i++){
		if(ans[i]==1) cout<<"Yes"<<'\n';
		else cout<<"No"<<'\n';
	}
	return 0;
}
```

---

## 作者：hahaxiang (赞：1)

# P11664 [JOI 2025 Final] 缆车 / Mi Teleférico 题解

贪心的希望选择的区间尽量长。

问题等价于询问是否存在合法区间，满足长度为 $R-L+1+X$，且右端点在 $[R,R+X]$ 内。 

$1$ 号点可以到达其他任意一个节点当且仅当除了 $1$ 号点的所有节点入度至少为一。

记 $p_i$ 表示最大的 $p_i\le i$ 满足 $[p_i,i]$ 合法。

由于 $p$ 数组具有单调性，显然可以用双指针快速计算。

维护合法的右端点集合，考虑按照 $i-p_i+1$ 从小到大加入节点 $i$，只需要查询 $[R,R+X]$ 内是否存在合法的右端点，用树状数组维护即可。

需要注意一些离散化的细节。

---

## 作者：ty_mxzhn (赞：1)

考虑什么时候可以联通。假设现在 $1$ 可以到 $2 \sim i$，如果连到 $i+1$ 还有边则 $i+1$ 显然还可以到达。

于是充要条件是 $2\sim n$ 点的入度不为 $0$，$1$ 点的出度不为 $0$。

固定 $r$，则合法的区间左端点是 $1\sim l_{\max}$ 这一段。用双指针求。

考虑所谓的 $|l-u|+|r-v|\le c$ 其实一定有 $u \le l,r\le v$。所以其实是 $l-u+v-r\le c$。

我们其实要找的是 $v-u$ 最小的区间并且包含了 $[l,r]$，这个不是扫描线随便求了？因为 $l_{\max}$ 单调则扫描线以后套二分即可解决。

---

## 作者：徐晨轩✅ (赞：1)

容易观察到一个引理：

* 当且仅当通票可以乘坐的缆车的终点集合为 $\left\{2,3,\cdots,n\right\}$ 时符合题意。

> 证明：
> 
> * 充分性：如果终点是 $2$，则这条路线一定是 $1 \to 2$，则 $2$ 是可达的。而如果 $2 \sim k$ 是可达的，且终点集合中包含 $k+1$，则这个终点所对应起点必定在 $1 \sim k$ 中，故 $k+1$ 也是可达的。
> * 必要性：如果终点集合中不包含 $2 \sim n$ 中的某个点，则这个点显然是不可达的。

有了这个引理之后，我们就可以只考虑每一条线路的终点了。考虑怎么判断通票 $(l,r)$ 是否**不**合法。

不难注意到，不合法的充要条件是：

* 有一个终点所对应的公司集合中，存在相邻的两个元素 $l', r'$，且 $l'<l, r'>r$。

以样例举例，终点 $4$ 所对应的公司集合为 $\left\{2,7,8\right\}$，对于 $(l,r)=(3,4)$，存在 $l'=2<l, r'=7>r$，故通票 $(3,4)$ 不合法。同时易证如果 $(l,r)$ 不合法，则所有满足 $l' \ge l, r' \le r$ 的 $(l',r')$ 都不合法。

将不合法的极大区间预处理（可以证明这样的区间只有不超过 $N$ 个），问题可以转换如下：

> 给定一些区间 $[l_i,r_i]$，询问：给定 $l,r,x$，求是否存在 $l', r'$，使得 $[l',r']$ 不是任何给定的区间的子区间，且 $|l'-l|+|r'-r|\le x$。

将这些区间按左端点排序，由于这些区间是极大区间，则右端点也有序。询问时，二分第一个 $r_i \ge r$ 的区间，编号记为 $lp$，和最后一个 $l_i \le l$ 的区间，编号记为 $rp$。有如下几种定出 $l', r'$ 的方案：

* 仅将 $l$ 左移，即 $l'<l, r'=r$。
* 仅将 $r$ 右移，即 $l'=l, r'>r$。
* 将 $l$ 左移，$r$ 右移，即 $l'<l, r'>r$。

前两者是简单的，只需要调整之后的 $[l',r']$ 不是 $lp$ 和 $rp$ 的子区间即可。具体地，对于第一种情况，令 $l' = l_{lp} - 1$。对于第二种情况，令 $r' = r_{rp} + 1$。

下面考虑第三种情况。我们要保证调整之后的 $[l', r']$ 不是 $[lp, rp]$ 中任何区间的子区间。简单模拟后不难得出结论：对于任意 $lp \le i < rp$，令 $l' = l_{i+1} - 1, r' = r_i + 1$ 都满足条件。于是我们需要求出这些情况的最小值。写出式子：

$$
|l-l'|+|r-r'| = l-(l_{i+1}-1) + (r_i+1)-r = (r_i - l_{i+1})-r+l+2
$$

与 $i$ 有关的只有 $r_i-l_{i+1}$。使用 ST 表或线段树维护均可。注意考虑边界情况（即判掉 $r'>P$ 或 $l'<1$）。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 300005, M = 20;

template <class T, T (*op)(T, T)>
struct RMQ {
    T a[N][M];
    void build(int* w, int n) {
        for (int i = 1; i <= n; i++)
            a[i][0] = w[i];
        for (int j = 1; j <= 19; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                a[i][j] = op(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
    }
    int query(int l, int r) {
        int k = __lg(r - l + 1);
        return op(a[l][k], a[r - (1 << k) + 1][k]);
    }
};

int min(int a, int b) { return a < b ? a : b; }

int n, m, p, q, mx, prel, w[N];
vector<int> mp[N];
vector<pair<int, int>> tmp, seg;
RMQ<int, min> rmq;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> p;
    for (int i = 1, a, b, c; i <= m; i++) {
        cin >> a >> b >> c;
        mp[b].push_back(c);
    }
    for (int x = 2; x <= n; x++) {
        auto& v = mp[x];
        v.push_back(0);
        v.push_back(p + 1);
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size() - 1; i++) {
            if (v[i] + 1 <= v[i + 1] - 1)
                tmp.emplace_back(v[i] + 1, v[i + 1] - 1);
        }
    }
    sort(tmp.begin(), tmp.end());
    seg.emplace_back(0, 0);
    for (auto [l, r] : tmp) {
        if (r <= mx) continue;
        mx = r;
        if (l == prel) seg.pop_back();
        seg.emplace_back(l, r);
        prel = l;
    }
    seg.emplace_back(p + 1, p + 1);
    for (int i = 1; i < seg.size(); i++) {
        auto [l1, r1] = seg[i - 1];
        auto [l2, r2] = seg[i];
        if (r1 + 1 <= p && l2 - 1 >= 1) w[i] = r1 - l2;
        else w[i] = 2e9;
    }
    rmq.build(w, seg.size() - 1);
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        int lp = lower_bound(seg.begin(), seg.end(), make_pair(0, r), [](auto x, auto y){ return x.second < y.second; }) - seg.begin();
        int rp = lower_bound(seg.begin(), seg.end(), make_pair(l + 1, 0)) - seg.begin() - 1;
        if (lp > rp) cout << "Yes" << '\n';
        else {
            if (x == 0) cout << "No" << '\n';
            else {
                auto [l1, r1] = seg[lp];
                auto [l2, r2] = seg[rp];
                int mn = x + 1;
                if (r2 + 1 <= p) mn = min(mn, (r2 + 1) - r);
                if (l1 - 1 >= 1) mn = min(mn, l - (l1 - 1));
                if (lp < rp) mn = min(mn, rmq.query(lp + 1, rp) - r + l + 2);
                if (mn <= x) cout << "Yes" << '\n';
                else cout << "No" << '\n';
            }
        }
    }
    return 0;
}
```

---

## 作者：shinzanmono (赞：0)

显然，给出的有向图是个 DAG，如果每个非 $1$ 点都有入度，那么说明这个是一个合法状态。从而显然发现，如果 $[L,R]$ 是满足条件的区间那么 $[L,R+1]$ 也是满足条件的区间。双指针维护 $r_{L}$ 表示对于 $l$ 的第一个满足条件的右端点，不存在则为 $+\infty$。

然后考虑拓展长度 $\leq X$ 的限制，设左端点向左拓展 $p$ 个颜色，则要查询是否存在 $p$ 满足 $\max(0,L-(L-p))+\max(0,r_{L-p}-R)\leq X$，发现 $p\in[0,X]$ 的时候这个式子才成立，此时式子可以拆为 $L-(L-p)+r_{L-p}-R\leq X$，即 $r_{L-p}-(L-p)\leq R-L+X$，维护 $f_i-i$ 的 RMQ 即可。



```cpp
#include<iostream>
#include<algorithm>
using ll=long long;
const int sz=3e5+10;
const int lgsz=std::__lg(sz)+1;
int rs[sz],A[sz],B[sz],C[sz],cnt[sz];
ll f[lgsz][sz],c[sz];
std::basic_string<int>tt[sz];
ll qmin(int l,int r){
  if(l>r)return 0x7fffffffffffffff;
  int lg=std::__lg(r-l+1);
  return std::min(f[lg][l],f[lg][r-(1<<lg)+1]);
}
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n,m,V,q;
  std::cin>>n>>m>>V;
  for(int i=1;i<=m;i++)std::cin>>A[i]>>B[i]>>C[i],c[i]=C[i];
  std::sort(c+1,c+m+1);
  V=std::unique(c+1,c+m+1)-c-1;
  for(int i=1;i<=m;i++)
    C[i]=std::lower_bound(c+1,c+V+1,C[i])-c,tt[C[i]]+=i;
  int N=0;
  for(int l=1,r=0;l<=V;l++){
    while(r<=V&&N!=n-1){
      r++;
      for(int id:tt[r])N-=cnt[B[id]]!=0,cnt[B[id]]++,N+=cnt[B[id]]!=0;
    }
    rs[l]=r;
    for(int id:tt[l])N-=cnt[B[id]]!=0,cnt[B[id]]--,N+=cnt[B[id]]!=0;
  }
  rs[V+1]=V+1,c[V+1]=0x7fffffffffffffff;
  for(int i=1;i<=V;i++)f[0][i]=c[rs[i]]-c[i];
  for(int i=1;i<=std::__lg(V);i++)
    for(int j=1;j+(1<<i)-1<=V;j++)f[i][j]=std::min(f[i-1][j],f[i-1][j+(1<<i-1)]);
  std::cin>>q;
  while(q--){
    ll L,R,X;
    std::cin>>L>>R>>X;
    int l=std::lower_bound(c+1,c+V+1,L-X)-c,r=std::lower_bound(c+1,c+V+1,L)-c;
    std::cout<<(std::min(qmin(l,r-1),c[rs[r]]-L)<=R-L+X?"Yes\n":"No\n");
  }
  return 0;
}
```

---

## 作者：DerrickLo (赞：0)

假设 $n,m,q$ 同阶。

一个 DAG 如果满足 $1$ 号点可以到达其余任意点当且仅当除了一号点，其余点的入度都 $>0$，证明考虑拓扑排序的过程即可。

那么我们对于每个 $i$，预处理出 $r_i$ 表示对于左端点是 $i$ 的情况，右端点需要 $\ge r_i$ 才能满足条件。这个是简单的，只需要对于每个点维护一个 set，然后每次就是要找到所有点的 set 中的最小值的最大值是多少，再维护一个全局的 set 即可。

然后对于每次询问，不难发现 $l'\le L,r'\ge R$，除了 $l'=L$ 或者 $r'=R$ 的情况，我们发现 $[l',r']$ 必然是上面这 $n$ 个 $[i,r_i]$ 区间中的一个，直接二分出满足 $[L,R]\subset [i,r_i]$ 的区间，然后使用 st 表维护区间最小的 $r_i-i$ 即可。

还有离散化等若干细节，时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,p,u[1100005],v[1100005],w[1100005],q,ans[1100005],l[1100005],r[1100005],x[1100005],dg[1100005],R[1100005],flag,f[1100005][25],pos,lg[1100005],b[1100005];
multiset<int>st[1100005],st2;
vector<int>ve[1100005];
int query(int l,int r){
	int k=lg[r-l+1];
	return min(f[l][k],f[r-(1<<k)+1][k]);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>p;
	for(int i=1;i<=m;i++)cin>>u[i]>>v[i]>>w[i],b[i]=w[i];
	cin>>q;
	for(int i=1;i<=q;i++)cin>>l[i]>>r[i]>>x[i],b[m+2*i-1]=l[i],b[m+2*i]=r[i];
	sort(b+1,b+m+2*q+1);
	for(int i=1;i<=m;i++)w[i]=lower_bound(b+1,b+m+2*q+1,w[i])-b,dg[v[i]]++,st[v[i]].insert(w[i]),ve[w[i]].emplace_back(i);
	for(int i=1;i<=q;i++)l[i]=lower_bound(b+1,b+m+2*q+1,l[i])-b,r[i]=lower_bound(b+1,b+m+2*q+1,r[i])-b;
	for(int i=2;i<=n;i++)if(!dg[i])flag=1;
	if(flag){
		while(q--)cout<<"No\n";
		return 0;
	}
	for(int i=2;i<=n;i++)st2.insert(*st[i].begin());
	for(int i=1;i<=m+2*q;i++)R[i]=1e18;
	for(int i=1;i<=m+2*q;i++){
		for(int x:ve[i-1]){
			st[v[x]].erase(st[v[x]].find(i-1));
			st2.erase(st2.find(i-1));
			if(st[v[x]].size())st2.insert(*st[v[x]].begin());
			else flag=1;
		}
		if(flag)break;
		R[i]=*st2.rbegin(),pos=i,f[i][0]=b[R[i]]-b[i];
	}
	for(int i=2;i<=pos;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=20;i++)for(int j=1;j+(1<<i)-1<=pos;j++)f[j][i]=min(f[j][i-1],f[j+(1<<i-1)][i-1]);
	for(int i=1;i<=q;i++){
		int l=::l[i],r=::r[i],x=::x[i];
		int ans=1e18;
		if(R[l]!=1e18&&b[R[l]]<=b[r]){cout<<"Yes\n";continue;}
		int xx=lower_bound(R+1,R+pos+1,r)-R;
		if(xx<=l&&xx!=pos+1)ans=min(ans,query(xx,min(l,pos)));
		if(xx!=1)ans=min(ans,b[r]-b[xx-1]);
		cout<<(ans-b[r]+b[l]<=x?"Yes\n":"No\n");
	}
	return 0;
}
```

---

