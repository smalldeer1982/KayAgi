# [ABC224E] Integers on Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc224/tasks/abc224_e

縦 $ H $ 行、横 $ W $ 列のマス目があります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,\ j) $ と呼びます。

それぞれのマスには整数が書かれています。 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、マス $ (r_i,\ c_i) $ には正整数 $ a_i $ が書かれており、それら以外のマスには $ 0 $ が書かれています。

はじめ、マス $ (R,\ C) $ にコマが置かれています。 高橋君は、コマを「いま置かれているマスから別のマスに移動させる」ことを好きな回数だけ行うことができます。 ただし、コマを移動する際には下記の $ 2 $ つの条件をともに満たさなければなりません。

- 移動先のマスに書かれている整数は、移動前のマスに書かれている整数より真に大きい。
- 移動先のマスは移動前のマスと同じ行にある、または、移動先のマスは移動前のマスと同じ列にある。

$ i\ =\ 1,\ 2,\ \ldots,\ N $ のそれぞれについて、$ (R,\ C)\ =\ (r_i,\ c_i) $ の場合に高橋君がコマの移動を行うことができる回数の最大値を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ N\ \leq\ \min(2\ \times\ 10^5,\ HW) $
- $ 1\ \leq\ r_i\ \leq\ H $
- $ 1\ \leq\ c_i\ \leq\ W $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $
- $ i\ \neq\ j\ \Rightarrow\ (r_i,\ c_i)\ \neq\ (r_j,\ c_j) $
- 入力はすべて整数

### Sample Explanation 1

マス目に書かれた整数は下記の通りです。 ``` 4 7 0 3 0 5 2 5 5 ``` - $ (R,\ C)\ =\ (r_1,\ c_1)\ =\ (1,\ 1) $ の場合、$ (1,\ 1)\ \rightarrow\ (1,\ 2) $ と移動すると、コマの移動を $ 1 $ 回行うことができます。 - $ (R,\ C)\ =\ (r_2,\ c_2)\ =\ (1,\ 2) $ の場合、一度もコマの移動を行うことができません。 - $ (R,\ C)\ =\ (r_3,\ c_3)\ =\ (2,\ 1) $ の場合、$ (2,\ 1)\ \rightarrow\ (1,\ 1)\ \rightarrow\ (1,\ 2) $ と移動すると、コマの移動を $ 2 $ 回行うことができます。 - $ (R,\ C)\ =\ (r_4,\ c_4)\ =\ (2,\ 3) $ の場合、一度もコマの移動を行うことができません。 - $ (R,\ C)\ =\ (r_5,\ c_5)\ =\ (3,\ 1) $ の場合、$ (3,\ 1)\ \rightarrow\ (2,\ 1)\ \rightarrow\ (1,\ 1)\ \rightarrow\ (1,\ 2) $ と移動すると、コマの移動を $ 3 $ 回行うことができます。 - $ (R,\ C)\ =\ (r_6,\ c_6)\ =\ (3,\ 2) $ の場合、$ (3,\ 2)\ \rightarrow\ (1,\ 2) $ と移動すると、コマの移動を $ 1 $ 回行うことができます。 - $ (R,\ C)\ =\ (r_7,\ c_7)\ =\ (3,\ 3) $ の場合、一度もコマの移動を行うことができません。

## 样例 #1

### 输入

```
3 3 7
1 1 4
1 2 7
2 1 3
2 3 5
3 1 2
3 2 5
3 3 5```

### 输出

```
1
0
2
0
3
1
0```

## 样例 #2

### 输入

```
5 7 20
2 7 8
2 6 4
4 1 9
1 5 4
2 2 7
5 5 2
1 7 2
4 6 6
1 4 1
2 1 10
5 6 9
5 3 3
3 7 9
3 6 3
4 3 4
3 3 10
4 2 1
3 5 4
1 2 6
4 7 9```

### 输出

```
2
4
1
5
3
6
6
2
7
0
0
4
1
5
3
0
5
2
4
0```

# 题解

## 作者：SunburstFan (赞：3)

### E - Integers on Grid

#### 解题思路

考虑设 $rmax_i$ 表示第 $i$ 列的最大值，$cmax_i$ 表示第 $i$ 行的最大值。

对数组进行排序，然后进行状态转移：

$f_i=\max \{ rmax_{r_i},cmax_{c_i} \}$

$rmax_i=\max \{ rmax_{r_i},f_i+1 \}$

$cmax_i=\max \{ cmax_{c_i},f_i+1 \}$

答案依次输出 $f_i$ 即可。

```cpp
cin>>h>>w>>n;
for(int i=1;i<=n;i++){
    cin>>r[i]>>c[i]>>a[i];
    mp[INF-a[i]].push_back(i);
}

for(auto p:mp){
    vector<int> now=p.second;

    for(auto v:now){
        f[v]=max(f[v],max(rmax[r[v]],cmax[c[v]]));
    }
    for(auto v:now){
        rmax[r[v]]=max(rmax[r[v]],f[v]+1);
        cmax[c[v]]=max(cmax[c[v]],f[v]+1);
    }
}    

for(int i=1;i<=n;i++){
    cout<<f[i]<<"\n";
}
```

---

## 作者：wusixuan (赞：1)

观察题目可以发现这类似一个图论的问题，我们可以把可以到达的位置对建有向边，这显然是一个 DAG，所以直接跑拓扑排序最长路即可。

这样的复杂度是 $O(n^2)$ 的，显然无法通过，而瓶颈在于建边部分。

考虑优化建边的复杂度。发现我们其实可以不用把这个格子 $x$ 可以到达的格子全部连上，只需要连上最小的比它大的格子 $y$ 即可，因为 $y$ 一定可以到达更大的格子，也就优化了建边，这里可以使用 set 来记录那个格子。从此，建边的复杂度变成了 $O(n \log n)$。

那么会有一个问题：如果碰到有很多个 $y$ 怎么办？这个很简单，我们只需要向最长路最长的 $y$ 连边即可，因为这样一定更优。

还会有一个问题：那么最长路怎么实时算出来？由最长路的值就可以想到可以无实物建图，那么此时 DAG 上的 DP 就变成了普通的 DP。我们设 $dp_i$ 表示以 $i$ 开始的路径的最长长度，为了保证无后效性，一开始要把所有格子的 $a_i$ 从大到小排序，然后把 $i$ 和 $dp_i$ 的值压到 set 里面维护（注意要重载运算符），转移异常简单，每一次我们取出的 $y$，都有 $dp_i=\max(dp_i,dp_y+1)$，这样就结束了。

另外还有一个小细节，就是我们在取 $y$ 的时候，可能会取到和它相同的值（因为我们这里设最长路值更大的更优），这样我们判断一下就可以了。

---

## 作者：I_LOVE_MATH (赞：1)

### 题目大意

给出一个矩形，上面有一些点上有数 $w$，每个数可以到达当前行或列比它大的数，问从每个数出发最多能走几步。

### 解题思路

考虑将所有点建图，每个数只能变大，说明这是一个 DAG。

因此，我们考虑使用 DAG 上 dp。

但在编码时可以不用建图，减少编码难度。

发现当这个数在当前行和当前列都为最大时一步都走不了，因此可以以这些状态为初始，然后逐步更新相邻点，也就是将这个过程倒过来看，由大数往小数跳。

所以可以将所有点按 $w$ 排序，然后从后往前遍历，消除后效性。

我们定义 $dp[i]$ 为 $i$ 点最多能走多少步，$a[i]$ 为 $i$ 行当前的最大值，$b[i]$ 为 $i$ 列当前的最大值，$c[i]$ 为 $i$ 行最大值的格点上的数（也是当前最小 $w$），$d[i]$ 为 $i$ 列最大值的格点上的数。

每遍历到一个点，就有转移方程：$dp[i] = max(a[q[i].x], b[q[i].y]) + 1$，然后更新最大值：$a[q[i].x] = b[q[i].y] = dp[i]$。

特别地，如果当前行或列最大值还没有被更新，可以将其初始化为 $-1$，使上面的式子仍然成立。

但是我们考虑到会有重复值，便不能从当前行最大值转移，因此上面算法并不完全正确。

由于我们遍历从大到小，因此如果和最小的 $w$ 重复，即 $w = c[i]$ 或 $w = d[i]$，那么它一定小于次小的 $w$，可以转移。

因此我们只要再存储次小的 $w$ 的信息即可，将上面的数组都开两维，第二维为 $0/1$ 表示是最小值还是次小值。

转移时如果 $w$ 小于 $c[i][0]$ 就将最小值变为次小，然后更新当前节点：$dp[i] = max(dp[i], a[q[i].x][0] + 1)$，列同理，大于 $c[i][0]$ 就从次小值转移：$dp[i] = max(dp[i], a[q[i].x][1] + 1)$。

时间复杂度 $O(n)$。

### 代码

``` cpp
#include<bits/stdc++.h>
#define endl "\n"
#define ll long long 
using namespace std;

const int N = 2e5 + 10;

struct node
{
	int x, y, w, id;
} q[N];

int h, w, n, tot;
int a[N][2], b[N][2], c[N][2], d[N][2], dp[N];

bool cmp(node x, node y)
{
	return x.w < y.w;
}

int main()
{
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> h >> w >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> q[i].x >> q[i].y >> q[i].w;
		q[i].id = i;
	}
	sort(q + 1, q + n + 1, cmp);
	memset(a, -1, sizeof a);
	memset(b, -1, sizeof b);
	memset(c, 0x7f, sizeof c);
	memset(d, 0x7f, sizeof d);
	for (int i = n; i >= 1; i--)
	{
		if (q[i].w < c[q[i].x][0])
		{
			dp[q[i].id] = a[q[i].x][0] + 1;
			c[q[i].x][1] = c[q[i].x][0];
			c[q[i].x][0] = q[i].w;
			a[q[i].x][1] = a[q[i].x][0];
		}
		else
		{
			dp[q[i].id] = a[q[i].x][1] + 1;
		}
		if (q[i].w < d[q[i].y][0])
		{
			dp[q[i].id] = max(dp[q[i].id], b[q[i].y][0] + 1);
			d[q[i].y][1] = d[q[i].y][0];
			d[q[i].y][0] = q[i].w;
			b[q[i].y][1] = b[q[i].y][0];
		}
		else
		{
			dp[q[i].id] = max(dp[q[i].id], b[q[i].y][1] + 1);
		}
		a[q[i].x][0] = max(a[q[i].x][0], dp[q[i].id]);
		b[q[i].y][0] = max(b[q[i].y][0], dp[q[i].id]);
	}
	for (int i = 1; i <= n; i++)
	{
		cout << dp[i] << endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 分析

定义 $\mathit{row}_{i}$ 表示第 $i$ 行中，从任意一个有香蕉的格子出发，能够走到的格子数量的最大值；$\mathit{column}_{i}$ 表示第 $i$ 列中，从任意一个有香蕉的格子出发，能够走到的格子数量的最大值；$\mathit{f}_{i}$ 表示从格子 $i$ 出发，能够走到的格子数量的最大值。

我们不难推出状态转移方程：$\mathit{row}_{i}=\max\{\mathit{f}_{j}|r_j=i\},\mathit{column}_{i}=\max\{\mathit{f}_{j}|c_j=i\},\mathit{f}_{i}=\max\{\mathit{row}_{r_i},\mathit{column}_{l_i}\}+1$。而对于第 $i$ 只猴子的答案，就是 $\mathit{f}_{i}-1$，因为在转移的时候我们将这只猴子自己所在的格子算进去了。

为了使转移方程满足：每次走到的格子所拥有的香蕉数量不小于当前格子所拥有的香蕉数量。我们需要将所有有香蕉的格子按照香蕉的数量从大到小排序，以此来保证可行性。

注：在这里有一个优化。如果有格子 $i,j$ 所拥有的香蕉数量相同，且 $j$ 在 $i$ 之后便利，则我们是不需要再将 $\mathit{row},\mathit{column}$ 更新的。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define x first
#define y second
const int N=2e5+10;
int h,w,n;
int row[N],column[N],f[N];
struct banana{
	int r,c,s,id;
}mk[N];
inline bool cmp(banana a,banana b){
	return a.s>b.s;
}
inline void read(){
	cin>>h>>w>>n;
	for(int i=1;i<=n;++i)
		cin>>mk[i].r>>mk[i].c>>mk[i].s,mk[i].id=i;
	sort(mk+1,mk+n+1,cmp);return ;
}
inline void solve(){
	int last=1;
	for(int i=1;i<=n;++i){
		if(mk[i].s==mk[i-1].s){
			f[mk[i].id]=max(row[mk[i].r],column[mk[i].c])+1;
			continue;
		}
		for(int j=last;j<i;++j)
			row[mk[j].r]=max(row[mk[j].r],f[mk[j].id]),
			column[mk[j].c]=max(column[mk[j].c],f[mk[j].id]);
		last=i;
		f[mk[i].id]=max(row[mk[i].r],column[mk[i].c])+1;		
	}
	return ;
}
inline void print(){
	for(int i=1;i<=n;++i)
		cout<<f[i]-1<<"\n";
	return ;
}
signed main(){
	read(),solve(),print();return 0;
}
```


---

## 作者：Tairitempest (赞：0)

## [ABC224E] Integers on Grid
数字大的点可以从数字小的点到达，但是数字小的点不可以从数字大的点到达，因此数字大的点一定不会被数字小的点更新。对于同一行的两个比它大的数字，一定会选择相对较小的数字，这样可以得到较多的步数。

考虑按数字从大到小遍历（这样无后效性），记录每个点的步数，并记录在每行或每列可以走的最多步数。对于每个点，比较选择去到这一行内比它大的最小的数的步数最大值和去到这一列内比它大的最小的数的步数最大值（用在每行或每列可以走的最多步数来维护），并选择较大的方案，其可以走的最多步数就相当于上述较大的方案再加一。

由于存在相同数字的情况，我们可以先把所有相同数字的方案更新，然后再更新这一行和这一列的最大步数值就可以了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll h,w,n,dp[200010];
ll xmax[200010],ymax[200010];
struct G{
	ll x,y,a;
} g[200010];
map<int, vector<int> > mp;
int main(){
	cin>>h>>w>>n;
	for(int i=1;i<=n;i++){
		cin>>g[i].x>>g[i].y>>g[i].a;
		mp[g[i].a].push_back(i);
	}
	for(auto i=mp.rbegin();i!=mp.rend();i++){
		for(auto k:(*i).second) dp[k]=max(xmax[g[k].x],ymax[g[k].y]);
		for(auto k:(*i).second){
			xmax[g[k].x]=max(dp[k]+1,xmax[g[k].x]);
			ymax[g[k].y]=max(dp[k]+1,ymax[g[k].y]);
		}
	}
	for(int i=1;i<=n;i++) cout<<dp[i]<<endl;
	return 0;
}
```

---

## 作者：highkj (赞：0)

# 前言
这道题还是比较简单的，只要想到了 Dp。
# 思路
我们首先可以转化为一种加点操作，首先将每一个有猴子的方格的 $val$ 从大到小排序，这样就可以将 Dp 的后效性给去掉了。然后我们可以发现对于一只猴子，它的转移方程为这一行和这一列中的最大值，又因为把值给排序了所以直接处理出每一行和每一列的最大值即可。

但是，这里有一种情况需要考虑，因为排完序之后我们没有去重，所以我们还需要考虑延迟更新，相当于就是将一段连续相等的给用原来的更新，然后当遇到第一个不同的时候就将要更新的更新掉即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define pb push_back
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
const int N=5e5+10;
int Maxl[N],Maxh[N];
int n,m,k;
struct node{
	int l,r,sum,id;
	friend bool operator<(const node&a,const node&b) {
		return a.sum>b.sum;
	}
}s[N];
struct Node{
	int l,r,id;
};
int f[N];
vector<Node>v;
fire main() {
//	freopen("move.in","r",stdin);
//	freopen("move.out","w",stdout);
	in(n),in(m),in(k);
	rep(i,1,k) in(s[i].l),in(s[i].r),in(s[i].sum),s[i].id=i;
	sort(s+1,s+1+k);
	memset(Maxl,-1,sizeof Maxl);
	memset(Maxh,-1,sizeof Maxh);
	int lst=false;
	rep(i,1,k) {
		f[s[i].id]=max(Maxl[s[i].r],Maxh[s[i].l])+1;
		if(s[i+1].sum!=s[i].sum){
			Maxl[s[i].r]=max(Maxl[s[i].r],f[s[i].id]);
			Maxh[s[i].l]=max(Maxh[s[i].l],f[s[i].id]);
			for(auto x:v) {//延迟更新
				Maxl[x.r]=max(Maxl[x.r],f[x.id]);
				Maxh[x.l]=max(Maxh[x.l],f[x.id]);
			}
			v.clear();
		}else {
			v.pb({s[i].l,s[i].r,s[i].id});
		}
	}
	rep(i,1,k) cout<<f[i]<<endl;
	return false;
}
```

---

## 作者：WaterSun (赞：0)

~~比较符合 CCF 造数据水平的题。~~

# 思路

首先可以用两个 `vector<pair<int,int>> v[N]` 分别将每一行、每一列的元素的权值与编号存储下来。

那么可以对所有的 $v_i$ 按照权值从小到大排序。那么发现对于所有的满足 `v[i][p].fst < v[i][q].fst` 的 $(p,q)$ 都可以建一条从 $p$ 指向 $q$ 的有向边。按照这种方式建图，最坏情况下会有 $\Theta(n^2)$ 级别的边。

考虑一种比较显然的贪心策略，对于一个 $p$ 显然只需要与 $p$ 之后第一个满足 `v[i][p].fst < v[i][q].fst` 连边。因为如果不这么连，将 $p$ 连向一个拥有更大权值的点 $k$，显然你可以通过 $p \to q \to k$ 的方式获得更大的答案。

于是你写完过后交上去，发现会[WA 1](https://atcoder.jp/contests/abc224/submissions/48089022)。这其中的原因就是对于权值相同的几个点，你直接取第一个是不优的。（不难发现，这种写法是很容易被卡的，但是 AT 只卡了一个点，同时放了一些写法比较优秀的 $\Theta(n^2)$ 算法）

不难发现，我们希望将所有满足条件的相同权值的点都要连边，同时保证边数尽量小。不妨考虑将这些点直接看作一个点，实现的话可以直接将这些权值相同的点连向一个超级原点，在后面连边的时候用超级原点与现在的点连边即可。

现在问题就很简单了，直接建反图，跑一边拓扑就完了。

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 1e6 + 10,inf = 1e9 + 10;
int n,H[2];
int d[N],rt[N],dp[N];
int id,idx,h[N],ne[N],e[N],w[N];
vector<pii> v[2][N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 1) + (r << 3) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void add(int a,int b,int c){
    d[b]++;
    ne[idx] = h[a];
    e[idx] = b;
    w[idx] = c;
    h[a] = idx++;
}

inline void f(int ty){
    for (re int i = 1;i <= H[ty];i++){
        sort(v[ty][i].begin(),v[ty][i].end());
        int len = v[ty][i].size();
        for (re int j = 0;j < len;j++){
            int p = v[ty][i][j].snd;
            if (!j) rt[p] = ++id;
            else{
                if (v[ty][i][j].fst == v[ty][i][j - 1].fst) rt[p] = rt[v[ty][i][j - 1].snd];
                else rt[p] = ++id;
            }
            add(p,rt[p],0);
        }
        for (auto x:v[ty][i]){
            auto it = upper_bound(v[ty][i].begin(),v[ty][i].end(),make_pair(x.fst,inf));
            if (it == v[ty][i].end()) break;
            int a = rt[(*it).snd],b = x.snd;
            add(a,b,1);
        }
    }
}

inline void top_sort(){
    queue<int> q;
    for (re int i = 1;i <= id;i++){
        if (!d[i]){
            dp[i] = 0;
            q.push(i);
        }
    }
    while (!q.empty()){
        int t = q.front();
        q.pop();
        for (re int i = h[t];~i;i = ne[i]){
            int j = e[i];
            dp[j] = max(dp[j],dp[t] + w[i]);
            d[j]--;
            if (!d[j]) q.push(j);
        }
    }
}

int main(){
    memset(h,-1,sizeof(h));
    memset(dp,-1,sizeof(dp));
    for (re int i = 0;i <= 1;i++) H[i] = read();
    n = id = read();
    for (re int i = 1;i <= n;i++){
        int x,y,val;
        x = read();
        y = read();
        val = read();
        v[0][x].push_back({val,i});
        v[1][y].push_back({val,i});
    }
    f(0);
    f(1);
    top_sort();
    for (re int i = 1;i <= n;i++) printf("%d\n",dp[i]);
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

首先显然可以暴力建图，然后拓扑排序即可，对每个可以转移到的后继 $ j $ 显然有 $ dp_{i}=\max \{ dp_{j}+1\} $，这是最朴素的 dp 方法，但是复杂度过大难以接受。

考虑优化：实际上有很多计算是重复的，可以简化这个计算过程。维护一个列最大值 $ rmax $ 和行最大值 $ cmax $，按照递减的顺序枚举 $ x $ 的取值，然后按以下方法 dp：

初始时初始化所有状态为 $ 0 $，然后对于所有当前枚举到等于 $ x $ 的格子，更新 $ dp_{i}=\max \{ rmax_{r_i},cmax_{c_i} \} $，然后令 $ rmax,cmax $ 同时与 $ dp_{i}+1 $ 取较大值更新即可。因为相邻的格子只能转移到相邻的行和列，所以这么做显然是对的。

需要预先对数组排序，所以时间复杂度 $ \mathcal{O}(n\log{n}+h+w) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct dat
{
	int x,y,a,pos;
}c[200010];
int h,w,n,pre=1;
int row[200010],line[200010];
int ans[200010];
bool cmp(dat x,dat y)
{
	return x.a>y.a;
}
int main()
{
	scanf("%d%d%d",&h,&w,&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&c[i].x,&c[i].y,&c[i].a);
		c[i].pos=i;
	}
	sort(c+1,c+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		if(c[i-1].a!=c[i].a)
		{
			for(int j=pre;j<i;j++)
			{
				row[c[j].x]=max(row[c[j].x],ans[c[j].pos]);
				line[c[j].y]=max(line[c[j].y],ans[c[j].pos]);
			}
			pre=i;
		}
		ans[c[i].pos]=max(row[c[i].x],line[c[i].y])+1;
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]-1);
}
```


---

## 作者：yqr123YQR (赞：0)

### 题意
在 $H\times W$ 平面上有 $n$ 个特殊点 $(x_i,y_i)$，点 $i$ 有属性值 $v_i$。对于 $\forall i\in[1,n]\cap Z$，求出从点 $i$ 出发，每次移动至其他特殊点，最多能移动几次。

能从点 $i$ 移动至点 $j\Leftrightarrow v_j\geqslant v_i$ 且 $x_i=x_j\vee y_i=y_j$。

### 思路
由于点的顺序没有影响，为了方便确定顺序，完全可以以 $v$ 为第一关键字排序。此时对 $v$ 的大小关系限制就变为是否相等的限制。

因为每次移动都要求是同行 / 列，我们可以探讨该取该行 / 列中哪一个点。记点 $i$ 的最大步数为 $dp_i$，可以证明，取 **$v$ 值最小且 $dp$ 值最大**的点 $p$ 一定不比其他点劣。下证：

> - 若点 $p$ 本来就是最优的点，显然成立
> - 否则取 $v$ 非最小的最优点 $q$，则必有 $v_q > v_p$，所以有 $dp_p\geqslant dp_q+1$，点 $p$ 更优，矛盾

> 证毕。

所以我们可以记录每行 / 列的最优点，以此转移即可。

Tips：$v$ 值相等的点不可以转移，怎么处理？~~自己想想。~~

### 代码
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 200000;
char gtchar()
{
	static char buf[100005], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100005, stdin)) == buf? EOF: *p1++;
}
int read()
{
	int ret = 0;
	char ch = gtchar();
	while(ch < '0' || ch > '9') ch = gtchar();
	while(ch >= '0' && ch <= '9') ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
	return ret;
}
struct node
{
	int x, y, id, value;
	friend bool operator < (node a, node b) {return a.value > b.value;}
}s[maxn + 5];
int h, w, n, dp[maxn + 5], r[maxn + 5], c[maxn + 5], pr[maxn + 5], pc[maxn + 5];
int max(int a, int b) {return a < b? b: a;}
int main()
{
// 	freopen("move.in", "r", stdin);
// 	freopen("move.out", "w", stdout);
	s[0].value = 1e9 + 5;
	dp[0] = -1;//方便转移
	h = read(), w = read(), n = read();
	for(int i = 1; i <= n; i++) s[i].x = read(), s[i].y = read(), s[i].value = read(), s[i].id = i;
	sort(s + 1, s + 1 + n);
	for(int i = 1; i <= n; i++)
	{
		int &row = r[s[i].x], &prow = pr[s[i].x], &col = c[s[i].y], &pcol = pc[s[i].y];//r,c 记录当前的最优点，pr,pc 记录上一个最优点（v 值与当前最优点不等），以解决 v 相等的问题
		dp[s[i].id] = max(dp[s[s[row].value == s[i].value? prow: row].id], dp[s[s[col].value == s[i].value? pcol: col].id]) + 1;
		if(s[row].value > s[i].value) prow = row, row = i;
		else if(dp[s[row].id] < dp[s[i].id]) row = i;
		if(s[col].value > s[i].value) pcol = col, col = i;
		else if(dp[s[col].id] < dp[s[i].id]) col = i;
	}
	for(int i = 1; i <= n; i++) printf("%d\n", dp[i]);
	return 0;
}
```

---

## 作者：_XHY20180718_ (赞：0)

提供一种奇葩的 map 乱搞做法。

## 题意简述：

给定一个 $H\times W$ 的矩形，有 $n$ 个格子里分别有 $a_i$ 个香蕉，每次猴子可以到同一行或同一列中的比当前格子香蕉多的格子，求猴子最多可以动几步。

## 思路：

考虑建图，对每个格子连单向边到可以移动到的格子，然后 top 排序一遍求最长路，但直接建图可以卡到 $O(n^2)$，会炸，考虑优化，由于我们只要求最长路，只需要连这一行和这一列中第一个比它大的即可，但是我们会发现对于相等的元素很难处理，因为这样连边依旧可能会炸。

我们考虑使用 map 维护一堆东西：

用来记录答案：

```map<pair<int,int>,int>res;```

在第 $x$ 行值为 $w$ 或第 $y$ 列值为 $w$ 的最长路：

```map<int,int>mpx[N],mpy[N];```

值为 $w$ 的坐标们（其实是方便进行排序）：

```map<int,vector<pair<int,int> > >mp;```

接下来只要按 $w$ 从大到小依次递推最长路即可，每次找到这一行/列第一个比当前 $w$ 大的点，进行最长路递推。

注意，这里每个坐标的答案和横纵坐标的最长路并不是相绑定的，因为有相同坐标依然会炸，所以要一次分开记录答案，最后再集体输出。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int c,r,n,id;
map<int,vector<pair<int,int> > >mp;
map<int,int>mpx[N],mpy[N];
map<pair<int,int>,int>res;
struct node{
    int x,y,w;
}nd[N];
signed main(){
    cin>>c>>r>>n;int x,y,w;
    for(int i=1; i<=n; ++i){
        cin>>x>>y>>w;nd[i]={x,y,w};
        mpx[x][w]=mpy[y][w]=0;
        mp[w].push_back({x,y});
    }vector<pair<int,int> >t;
    for(auto it=mp.end();it!=mp.begin();){
        --it;w=it->first,t=it->second;
        for(auto xy:t){
            x=xy.first,y=xy.second;
            auto itx=mpx[x].find(w),ity=mpy[y].find(w);++itx,++ity;
            if(itx!=mpx[x].end()){
                mpx[x][w]=max(mpx[x][w],(itx->second)+1);
                mpy[y][w]=max(mpy[y][w],(itx->second)+1);
                res[{x,y}]=max(res[{x,y}],(itx->second)+1);
            }
            if(ity!=mpy[y].end()){
                mpx[x][w]=max(mpx[x][w],(ity->second)+1);
                mpy[y][w]=max(mpy[y][w],(ity->second)+1);
                res[{x,y}]=max(res[{x,y}],(ity->second)+1);
            }
        }
    }
    for(int i=1; i<=n; ++i)
        cout<<res[{nd[i].x,nd[i].y}]<<'\n';
    return 0;
}
```


---

