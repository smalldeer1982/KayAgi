# Zbazi in Zeydabad

## 题目描述

A tourist wants to visit country Zeydabad for Zbazi (a local game in Zeydabad).

The country Zeydabad is a rectangular table consisting of $ n $ rows and $ m $ columns. Each cell on the country is either 'z' or '.'.

The tourist knows this country is named Zeydabad because there are lots of ''Z-pattern"s in the country. A ''Z-pattern" is a square which anti-diagonal is completely filled with 'z' and its upper and lower rows are also completely filled with 'z'. All other cells of a square can be arbitrary.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF628E/1dd3a4a39a26eabd5113af3bad685b4a12148713.png)Note that a ''Z-pattern" can consist of only one cell (see the examples).

So he wants to count the number of ''Z-pattern"s in the country (a necessary skill for Zbazi).

Now your task is to help tourist with counting number of ''Z-pattern"s.

As input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use gets/scanf/printf instead of getline/cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 样例 #1

### 输入

```
4 4
zzzz
zzz.
.z..
zzzz
```

### 输出

```
16
```

## 样例 #2

### 输入

```
1 4
z.z.
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 2
zz
zz
```

### 输出

```
5
```

# 题解

## 作者：HDWR (赞：8)

挺有意思一题。

> 定义 z 线：指一条连续的全部由字符 z 组成的线段，可能是斜的也可能是横的。

首先我们可以预处理出所有点往左 `tl[i][j]`、往右 `tr[i][j]`，往左下 `tld[i][j]` 的最长横 z 线长度，这对于我们判断 Z 字形有很大的用处。

注意到 Z 字形的结构是正方形，所以确定了一个角和长度就可以确定整个图形的位置；而且对角线角（左下、右上）是和图形的对角线部分直接相关的，所以考虑枚举图形的右上角 $(i, j)$。

可以发现，这个图形可能的最大长度即是往左和往左下 z 线长度的较小值 `l = min(tl[i][j], tld[i][j])`，于是接下来我们的任务就是判断这条长为 $l$ 的斜 z 线上有多少满足，经过它的横 z 线向右伸展达到（或超过）这个右上角所在列 $j$，的点，以这些点作为左下角即可确定一个 Z 字形。直接枚举是 $O(n^3)$ 级别的，考虑能不能优化。

[![5bfa7Q.png](https://z3.ax1x.com/2021/10/28/5bfa7Q.png)](https://imgtu.com/i/5bfa7Q)

注意到以我们枚举的点为右上角的所有 Z 字形有两个性质：

> 它们下面那一条横 z 线都至少向右伸展达到（或超过）了右上角所在列 $j$。

> 它们所有的左下角一定分布在这条长为 $l$ 的斜 z 线上，也就是在对角线上的一个区间查询。

因此我们可以考虑去寻找**所有**右端点在 $j$ 上（或右边）的横 z 线，它们的左端点如果在这条对角线斜 z 线上，就说明这个左端点是满足要求的一个左下角。

这个**所有**线是 $O(n^3)$ 级别的，但是发现相同左端点的横 z 线只会产生一个贡献，而且右端点肯定尽量靠右最好，所以我们就只保留每一个点往右伸展最长长度的横 z 线，也就是对于点 $(x, y)$，我们要存的线段是 $(x, y) \rightarrow (x, y + \mathrm{tr}_{x, y} - 1)$（如果存在的话）。

接下来的任务就是，对于这个右上角 $(i, j)$，枚举所有右端点也在列 $j$ 上（或超过）的线段，判断它的左端点是不是在这条对角线上，而且属于这个长为 $l$ 的区间。

类似树状数组求逆序对，这里我们也可以使用类似于边插入边查询的思想，考虑对每一条对角线维护一个树状数组，$b_{x + y, y}$ 表示**当前**第 $x + y$ 条对角线上是否存在以第 $y$ 列的点为左端点的线段（0 或 1），通过以合适的顺序枚举线段并修改树状数组，我们可以实现在对角线上的区间查询。

为了满足线段所有右端点都在当前枚举的列右边，我们修改枚举右上角 $(i, j)$ 的顺序，先从右往左枚举列 $j$，找到所有右端点在列 $j$ 上的线段，将左端点插入对应对角线的树状数组；再从上到下枚举行 $i$，确定右上角 $(i, j)$，在对应对角线的树状数组上进行区间查询，累计答案即可。

```cpp
const int MAXN = 3000 + 10;

int n, m;
char mat[MAXN][MAXN];

int tl[MAXN][MAXN], tr[MAXN][MAXN], tld[MAXN][MAXN];
std::vector<std::pair<int, int> > segs[MAXN]; // segs[r][x] -> LeftNode(i, j)
void pre() {
    rep (i, 1, n) {
        rep (j, 1, m) if (mat[i][j] == 'z') tl[i][j] = tl[i][j - 1] + 1;
        for (int j = m; j >= 1; --j) if (mat[i][j] == 'z') tr[i][j] = tr[i][j + 1] + 1;
    }
    for (int i = n; i >= 1; --i) {
        rep (j, 1, m) if (mat[i][j] == 'z') tld[i][j] = tld[i + 1][j - 1] + 1;
    }
    rep (i, 1, n) {
        rep (j, 1, m) {
            int r = j + tr[i][j] - 1;
            if (j <= r) segs[r].push_back({i, j});
        }
    }
}

struct BIT {
    lli seq[MAXN];
    #define lb(x) ((x) & (-(x)))
    void mo(int x) {
        for (; x <= m; x += lb(x)) ++seq[x];
    }
    lli qr(int x) {
        int r = 0; for (; x; x -= lb(x)) r += seq[x]; return r;
    }
} diagonals[MAXN << 1];

int main() {
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    rep (i, 1, n) cin >> (mat[i] + 1);
    pre();
    lli ans = 0;
    for (int j = m; j >= 1; --j) {
        for (auto seg : segs[j]) {
            int x = seg.fi, y = seg.se;
            diagonals[x + y].mo(y);
        }
        for (int i = 1; i <= n; ++i) {
            // (i, j) as the upperright corner
            if (mat[i][j] != 'z') continue;
            int maxlen = std::min(tl[i][j], tld[i][j]);
            int ql = j - maxlen + 1, qr = j;
            ans += diagonals[i + j].qr(qr) - diagonals[i + j].qr(ql - 1);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Avakos (赞：3)

这题可以用 bitset 或者树状数组做。

但是题解区里并没有 bitset 的思路所以蒟蒻来水一发（

前置知识：[bitset](https://oi-wiki.org/lang/csl/bitset/)。

首先因为 bitset 是二进制结构所以把 z 设为 $1$ ，空点设为 $0$。

先初始化出每个点向 $→$ 以及 $↗$ 两个方向分别可以延伸多少个 $1$，向右延伸的设为 $r(i,j)$，向右上延伸的设为 $d(i,j)$。

然后我们会发现，可以对于每一列**从上至下**枚举 Z 形的**左下角拐点**来统计合法矩阵数。

在枚举过程中，设当前拐点为 $(i,j)$，其向右和右上最多能延伸的 $1$ 数已经被初始化，而以 $(i,j)$ 为左下角构建一个大小为 k 的 Z 形还需要矩阵中坐标为 $(i-k+1,j)$~$(i-k+1,j+k-1)$ 的点全部为 $1$。

所以向下枚举时，我们考虑用 bitset 将当前拐点 $(i,j)$ 不断向右上方延伸直到碰到矩形上边界形成的直线（可以越过右边界）进行按位与，而这样的直线也是可以初始化出来的。因为每次这样的直线长度会增加 $1$，所以我们将之前已完成统计的 bitset 左移 $1$。结果再与上前 $\min(r(i,j),d(i,j))$ 位都是 $1$ 的 bitset 后，剩下 $1$ 的个数就是答案。

复杂度 $O(n^3/w)$。

AC 代码，因为常数较大所以加了 O2 和 Ofast。
```cpp
#pragma GCC optimize(2,"Ofast")
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define DU double
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define nep(i,x,n) for(int i=x;i>=n;i--)
using namespace std;
const int N=3010,M=6010;
int n,m,r[N][N],d[N][N],minx[N][N];
int x,y,now;
int belong[N][N],id[N][N];
bitset<N>tmp,mp[N],djx[M];//当前bitset，初始化的前i位全1bitset，提到的直线
char s[N][N];
inline int read(){
	int s=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		s=(s<<3)+(s<<1)+ch-'0';
		ch=getchar();
	}
	return s*f;
}
inline void print(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline void Solve(){
	rep(i,1,3000){
		rep(j,1,i){
			mp[i][j]=1;
		}
	}
	n=read(),m=read();
	rep(i,1,n){
		scanf("%s",s[i]+1);
	}
    //初始化
	rep(i,1,n){
		nep(j,m,1){
			if(s[i][j]=='.') r[i][j]=0;
			else r[i][j]=r[i][j+1]+1;
			if(s[i][j]=='.') d[i][j]=0;
			else d[i][j]=d[i-1][j+1]+1;
			minx[i][j]=min(r[i][j],d[i][j]);
		}
	}
    //将直线分为两类处理
	rep(i,1,n){
		x=i,y=1,now=0;
		while(x>0&&y<=m){
			now++;
			djx[i][now]=(s[x][y]=='z');
            //初始化这条直线的第now位
			belong[x][y]=i;
            //(x,y)属于哪条直线
			id[x][y]=now;
            //(x,y)在这条直线中的编号
			x--,y++;
		}
	}
    //同上
	rep(i,2,m){
		x=n,y=i,now=0;
		while(x>0&&y<=m){
			now++;
			djx[i+n-1][now]=(s[x][y]=='z');
			belong[x][y]=i+n-1;
			id[x][y]=now;
			x--,y++;
		}
	}
    //统计答案，注意要开long long
	ll ans=0;
	rep(j,1,m){
		tmp.reset();
		rep(i,1,n){
			tmp[1]=1;
            //默认将当前位设为1
			tmp&=(djx[belong[i][j]]>>id[i][j]-1);
            //因为提取出的是整条直线，所以要把这条直线对应的二进制表示右移(i,j)的编号-1位来表示以(i,j)为左下角向右上延伸的直线
			if(s[i][j]=='z') ans+=(tmp&mp[minx[i][j]]).count();
           //统计答案
			tmp<<=1;
            //向左移一格为下一行做准备
		}
	}
	print(ans);
}
int main(){
	ios::sync_with_stdio(false);
	int Tests=1;
	while(Tests--) Solve();
	return 0;
}
```

---

## 作者：Yuno (赞：3)


~~这是一个奇慢无比的做法.~~

容易发现上下两行非常好判断，于是考虑枚举对角线.

先对于每一个 $"z"$ 格，算出他向左向右以及向左下最多能拓展几个 $"z"$.分别记为 $left、right、max$

然后枚举每一个点，计算它作为右上角对答案的贡献.

在这个点所能向左下拓展的区域内，一个点可以产生贡献当且仅当它所能向右拓展的长度大于等于它与左上角的点的对角线长度.

$zzz.$

$.z..$

$zzzz$

大概是这个样子。

设右上角点横坐标为 $x_1$，每个可能产生答案的点的横坐标为 $x_2$

则一个点有贡献当且仅当 $x_2-x_1\leq right$

移项得到 $x_2-right\leq x_1$

这样就可以维护了！具体地，先把一个二维数组中的每个数重新标一个 $id$.

像这样

1 2 4

3 5 7

6 8 9

保证每次询问都是一个区间.

然后把每个点的横坐标减 $right$ 放入一个数组中.

那么现在我们要做的事情就是求出一个区间中小于等于一个数的数有几个.

离线，把询问按 $x$ 排序.

把每个比 $x$ 小的数在树状数组上做修改.

然后用一下前缀和思想，$l$ 到 $r$ 的答案就是 $1$ 到 $r$ 的答案减去 $1$ 到 $l-1$ 的答案.

于是做好了.

复杂度：$O(n\times m\ log(n\times m))$

常数奇大无比，最慢的点跑了 $3s$ 多.

### $Code:$

```cpp
#include <bits/stdc++.h>
using std::cin;
using std::cout;

const int N = 3007;
int n, m, ret, col[N][N], left[N][N], right[N][N], max[N][N], id[N][N];
int c[N * N];

void add(int x, int v) {for (; x <= ret; x += x & -x) c[x] += v;}
int query(int x) {int res = 0; for (; x; x -= x & -x) res += c[x]; return res;} 

struct node  
{  
    int id,num;  
    bool operator < (const node &other) const  
    {  
        return num < other.num;  
    }  
}a[N * N];

struct note  
{  
    int l,r,id,value;  
    bool operator < (const note &other)const  
    {  
        return value <other.value;  
    }  
}b[N * N];

signed main() {
	std::ios::sync_with_stdio(0);
	cin >> n >> m;
	long long tot = 0;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			char ch;
			cin >> ch;
			if (ch == 'z') col[i][j] = 1, ++ tot;
			else col[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) if (col[i][j] == 1) left[i][j] = left[i][j - 1] + 1;
		for (int j = m; j >= 1; -- j) if (col[i][j] == 1) right[i][j] = right[i][j + 1] + 1;
	}
	for (int i = n; i >= 1; -- i) {
		for (int j = 1; j <= m; ++ j) {
			if (col[i][j] == 1) max[i][j] = max[i + 1][j - 1] + 1;
		}
	}
	for (int st = 1; st <= m; ++ st) {
		int i = 1, j = st;
		while (j >= 1 && i <= n) {
			id[i][j] = ++ ret;
			a[ret].num = i - right[i][j] + 1;
			a[ret].id = ret;
			++ i;
			-- j;
		}
	}
	for (int st = 2; st <= n; ++ st) {
		int i = st, j = m;
		while (j >= 1 && i <= n) {
			id[i][j] = ++ ret;
			a[ret].num = i - right[i][j] + 1;
			a[ret].id = ret;
			++ i;
			-- j;
		}
	} 
	long long ans = 0;
	int q = 0;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			int len = std::min(left[i][j], max[i][j]);
			if (len == 0) continue;
			b[++ q].l = id[i][j];
			b[q].r = id[i + len - 1][j - len + 1];
			b[q].value = i + 1;
			b[q].id = q;
		}
	}
	std::sort(a + 1, a + 1 + ret);
	std::sort(b + 1, b + 1 + q);
	int k = 1;
	for (int i = 1; i <= q; ++ i) {
		while (k <= ret && a[k].num < b[i].value) {
			add(a[k].id, 1);
			++ k;
		}
		long long x = query(b[i].r) - query(b[i].l - 1);
		ans += x;
	}
	cout << ans << '\n';
	return 0;
}
```

$date:2020.9.16$



---

## 作者：ilibilib (赞：2)

## 分析：

先对图形进行~~树链~~剖分，大概变成这个形式。

| １z  | ２z  | ３z  | ４z  |
| ---- | ---- | ---- | ---- |
| ２z  | ３z  | ４z  | ５.  |
| ３.  | ４z  | ５.  | ６.  |
| ４z  | ５z  | ６z  | ７z  |



$f_{i,j}$ 表示 $i,j$ 所属的斜链，$l_{i,j}$,$r_{i,j}$ 分别为 $i,j$ 向左右扩展最长的连续 `z`。

记录每条链上每个位置向右扩展的最远距离，用树状数组维护。

枚举每一个右上角，这个点最多能向下拓展的距离就等于向左最多能拓展的距离。

如果向下拓展了 $x$，同时这个点能向又拓展大于等于 $x$ 格时那就有了一个合法的 `z`。

一层层扩展的话，枚举就是 $O(n^3)$ 的复杂度了，如果用树状数组维护贡献就可以做到 $O(n^2\log n)$。

注意：

枚举完后一个点后就应该删掉这个点的贡献，还有就是如果斜链不是连续的 `z` 的话，也没有贡献。分别判断一下就行了。

## code：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int N=3e3+10;
typedef long long ll;
char s[N][N];
int f[N][N],l[N][N],r[N][N],cnt=0,n,m;
bool vis[N][N];ll ans=0;
vector<int>v[N<<1][N];
struct BIT
{
    int c[N];
    void add(int x,int w) 
    {
        for(;x<=n;x+=lowbit(x)) c[x]+=w;
    }
    int ask(int x)
    {
        int ans=0;
        for(;x;x-=lowbit(x)) ans+=c[x];
        return ans;
    }
}c[N<<1];
void solve(int x,int y,int z)
{
    f[x][y]=z;
    if(x<n&&y>1) solve(x+1,y-1,z);
}
void check(int x,int y,int z)
{
    vis[x][y]=true;
    v[f[x][y]][max(z,x-(r[x][y]-y)+1)].push_back(x);
    if(x<n&&y>1&&s[x+1][y-1]=='z') check(x+1,y-1,z);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i) cin>>s[i]+1;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(s[i][j]=='z')    l[i][j]=l[i][j-1];
            else                l[i][j]=j;
        }
        r[i][m+1]=m+1;
        for(int j=m;j>=1;--j)
        {
            if(s[i][j]=='z')    r[i][j]=r[i][j+1];
            else                r[i][j]=j;
        }
    }
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(!f[i][j]) solve(i,j,++cnt);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(s[i][j]!='z') continue;
            if(!vis[i][j]) check(i,j,i);
            for(auto x:v[f[i][j]][i]) c[f[i][j]].add(x,1);
            v[f[i][j]][i].clear();
            ans+=c[f[i][j]].ask(min(n,i+j-l[i][j]-1));
            c[f[i][j]].add(i,-1);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：operator_ (赞：2)

# CF628E Zbazi in Zeydabad

[题目传送门](https://www.luogu.com.cn/problem/CF628E)

## 题解

这是一种用树状数组二维数点的做法。

遇到这种题，优先考虑预处理出从每一个点向左 ```l[i][j]```、向右 ```r[i][j]```、向左下 ```ld[i][j]``` 的**最长**的全由 z 组成的线段长度，这有利于我们进行判定。

观察到数据范围支持 $O(n^2)$，我们可以接受枚举一个点的复杂度，所以我们枚举第一个拐点（即 Z 字形的右上点）。

假设我们枚举了点 $(i,j)$。

现在我们要确定下边界，显然地，下边界 $x$ 一定在 $i\le x\le i+\min(l_{i,j},ld_{i,j})$ 的范围内，不过当中会有一些点取不到。很容易发现，只要满足 $j-l_{x,j}+1\le j-(x-i)$ 那么下边界 $x$ 就可以被取到。

上式明显可以化简，我们把和 $x$ 无关的都移到一边，有 $x-l_{x,j}+1\le i$。

发现了吗？对于每一列，都是一个经典的二维数点问题，用树状数组解决即可，略卡空间但够用（记得给记录答案的变量开 ```long long```）。

时间复杂度是 $O(nm\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long ans;
char c[3005][3005];
int l[3005][3005],ld[3005][3005];
struct BIT {
	int t[3005];
	int lb(int x) {return x&-x;}
	int sum(int x) {
	    int s=0;
		for(int i=x;i;i-=lb(i)) 
            s+=t[i];    
	    return s;
	}
	int query(int x,int y) {
		return sum(y)-sum(x-1);
	}
	void add(int x,int k) {
		for(int i=x;i<=n;i+=lb(i)) 
            t[i]+=k;
	}
} t[3005];
struct QWQ {int l,r,x,y,p;} a[9000005],q[9000005];
int cnt1,cnt2;
bool cmp(QWQ a1,QWQ a2) {return a1.p<a2.p;}
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			cin>>c[i][j];
			if(c[i][j]=='z')
				l[i][j]=l[i][j-1]+1;
		}
	for(int i=n;i>=1;i--)
		for(int j=1;j<=m;j++)
			if(c[i][j]=='z')
				ld[i][j]=ld[i+1][j-1]+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			a[++cnt1]={0,0,i,j,i-l[i][j]+1};
			q[++cnt2]={i,i+min(l[i][j],ld[i][j])-1,i,j,i};
		}
	sort(a+1,a+cnt1+1,cmp);
	sort(q+1,q+cnt2+1,cmp);
	for(int i=1,j=1;j<=cnt2;j++) {
		while(a[i].p<=q[j].p&&i<=cnt1)
			t[a[i].y].add(a[i].x,1),i++;
		ans+=t[q[j].y].query(q[j].l,q[j].r);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：_edge_ (赞：2)

一道简单的 $2300$。

难度虚高，可能因为数据结构的原因。

看到这种题么，一个经典的套路就是枚举拐点。

这个套路在 NOIP 2022 T1 中也用到了。

比如说我们枚举左下角这个拐点，那么很容易确定两个值，一个是这个点能延伸到最右边是哪个，另外一个是右上角能延伸到哪一个。

这两个东西可以随手递推解决。

然后我们大致确定了这个 `Z` 的大小上界。

那么这里我们需要去寻找另外一个拐点，就是右上角的。

到这里你可能会 $O(n^2m^2)$ 去枚举这个拐点，这样会显得非常愚蠢。

思考这两个拐点的特殊性质，肯定是在从右上角到左下角的对角线，那么我们把每一条对角线单独搞出来，这样就满足了很多性质。

设 $R$ 表示该 `Z` 在左下角这个拐点确定的大小上界。

设 $L_{i,j}$ 表示 $(i,j)$ 能延伸到的最左边的点。

$(x,y)$ 表示当前我们枚举的左下角的点。

我们从右上角到左下角，那么就是要数有多少个 $L_{i,j} \ge x$ 并且 $i \le x-R$。

这东西是典型的二维偏序，可以随手做。

这里再提供一种好实现的方法，就是对于每个 $(i,j)$ 都在 $L_{i,j}$ 标记一下，然后遇到这个 $x=L_{i,j}$ 那就把 $(i,j)$ 的贡献消除掉，这样就变成查询后缀，可以直接上树状数组维护。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define pb push_back
using namespace std;
const int INF=3e3+5;
int n,m,sum[INF][INF],ans,L[INF][INF],R[INF][INF],U[INF][INF];
char Map[INF][INF];
int tree[INF];
vector <int> cnt[INF];
void add(int x,int y) {for (int i=x;i;i-=i&-i) tree[i]+=y;}
int query(int x) {int sum=0;for (int i=x;i<=3e3;i+=i&-i) sum+=tree[i];return sum;}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			cin>>Map[i][j];
			sum[i][j]=sum[i][j-1]+(Map[i][j]=='z');
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++) {
			if (Map[i][j-1]=='z') L[i][j]=L[i][j-1];
			else if (Map[i][j]=='z') L[i][j]=j;
		}
		
	for (int i=1;i<=n;i++)
		for (int j=m;j;j--) {
			if (Map[i][j+1]=='z') R[i][j]=R[i][j+1];
			else if (Map[i][j]=='z') R[i][j]=j;
		}
	
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			if (Map[i-1][j+1]=='z') U[i][j]=U[i-1][j+1];
			else if (Map[i][j]=='z') U[i][j]=i;
		}
	}
		
	for (int i=1;i<=n+m;i++) {
		memset(tree,0,sizeof tree); 
		for (int x=1;x<=m;x++) cnt[x].clear();
		for (int x=1;x<=n;x++) {
			int y=i-x;
			if (y<1 || y>m) continue;
			if (Map[x][y]=='z') ans++;
			else continue;
			int K=min(x-U[x][y],R[x][y]-y);
			ans+=query(x-K);
			add(x,1);
			cnt[L[x][y]].pb(x);
			for (int i:cnt[y]) add(i,-1);
		} 
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：gesong (赞：1)

题目传送门：[CF628E Zbazi in Zeydabad](https://www.luogu.com.cn/problem/CF628E)。
# 思路

先计算 $1\times 1$ 的 Z 图案个数，之后的计算不会计算这些。

我们可以先预处理每个位置左侧和右侧的最长 Z 连续段长度，可以用二分或者 dp 轻松解决。

然后我们枚举所有的对角线，将对角线上的连续的 Z 存成一个序列进行操作，记 $l_i,r_i$ 表示对角线序列上的 $i$ 点左侧和右侧的最长 Z 连续段长度，根据题意即为满足下式的个数：

$$\begin{cases}
l_i\ge j-i+1 \\
r_i\ge j-i+1 \\
j>i
\end{cases}$$

化简得：

$$\begin{cases}
i < j \le l_i+i-1 \\
j-r_j+1\le i

\end{cases}$$

我们将每个位置拆分成 $i-r_i+1$ 和 $i$ 并排序，这样直接满足第二条限制，然后将拆分成 $i-r_i+1$ 的位置的 $i$ 加入树状数组，将拆分成 $i$ 的位置计算 $i+1$ 到 $l_i+i-1$ 的区间和即可。

# 代码

在代码的最后放了几个小样例方便大家调试。

```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&-x
using namespace std;
const int N=3010;
int a[N][N],l[N][N],r[N][N],n,m,b[N],c[N];
int L[N],R[N];
int X[N],Y[N];
inline void add(int i,int x){
	for (;i<=max(n,m);i+=lowbit(i)) c[i]+=x;
}
inline int sum(int i){
	int ans=0;
	for (;i;i-=lowbit(i)) ans+=c[i];
	return ans;
}
struct nord{
	int a,op,id;
	bool operator <(const nord &x) const{
		if (x.a==a) return op<x.op;
		return a<x.a;
	}
}A[N];
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	n=read(),m=read();
	int ans=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			char x;cin>>x;
			if (x=='z') a[i][j]=1,ans++;
		}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++) b[j]=b[j-1]+a[i][j];
		for (int j=1;j<=m;j++) if (a[i][j]){
			int l=1,r=j,ans=-1;
			while(l<=r){
				int mid=l+r>>1;
				if (b[j]-b[mid-1]==j-mid+1) ans=mid,r=mid-1;
				else l=mid+1;
			}
			::l[i][j]=j-ans+1;
			l=j,r=m,ans=-1;
			while(l<=r){
				int mid=l+r>>1;
				if (b[mid]-b[j-1]==mid-j+1) ans=mid,l=mid+1;
				else r=mid-1;
			}
			::r[i][j]=ans-j+1;
		}
	}	
	for (int i=1;i<=n;i++){
		int x=i,y=1;
		int cnt=0;
		while(x>0&&x<=n&&y>0&&y<=m) X[++cnt]=x,Y[cnt]=y,x--,y++;
		for (int i=1;i<=cnt;i++) if (a[X[i]][Y[i]]){
			int l=i;
			while(i+1<=cnt&&a[X[i+1]][Y[i+1]]) i++;
			int r=i;
			int cntt=0;
			for (int j=l;j<=r;j++) L[++cntt]=::l[X[j]][Y[j]],R[cntt]=::r[X[j]][Y[j]];//,cout <<X[j]<<" "<<Y[j]<<endl;
			reverse(L+1,L+cntt+1);
			reverse(R+1,R+cntt+1);
			int xx=0;
			for (int i=1;i<=cntt;i++){
				A[++xx]={i-R[i]+1,0,i};
				A[++xx]={i,1,i};
			}
			sort(A+1,A+xx+1);
			for (int i=1;i<=xx;i++){
				if (A[i].op==1) ans+=sum(L[A[i].id]+A[i].id-1)-sum(A[i].id);
				else add(A[i].id,1);
			}
			for (int i=1;i<=xx;i++)
				if (A[i].op==0) add(A[i].id,-1);
		}
	}
	for (int i=2;i<=m;i++){
		int x=n,y=i;
		int cnt=0;
		while(x>0&&x<=n&&y>0&&y<=m) X[++cnt]=x,Y[cnt]=y,x--,y++;
		for (int i=1;i<=cnt;i++) if (a[X[i]][Y[i]]){
			int l=i;
			while(i+1<=cnt&&a[X[i+1]][Y[i+1]]) i++;
			int r=i;
			int cntt=0;
			for (int j=l;j<=r;j++) L[++cntt]=::l[X[j]][Y[j]],R[cntt]=::r[X[j]][Y[j]];
			reverse(L+1,L+cntt+1);
			reverse(R+1,R+cntt+1);
			int xx=0;
			for (int i=1;i<=cntt;i++){
				A[++xx]={i-R[i]+1,0,i};
				A[++xx]={i,1,i};
			}
			sort(A+1,A+xx+1);
			for (int i=1;i<=xx;i++){
				if (A[i].op==1) ans+=sum(L[A[i].id]+A[i].id-1)-sum(A[i].id);
				else add(A[i].id,1);
			}
			for (int i=1;i<=xx;i++)
				if (A[i].op==0) add(A[i].id,-1);
		}
	}	
	cout <<ans;
    return 0;
}
/*
2 3
..z
zzz
4

3 4
..zz
.z.z
.zzz
7

4 6
...zzz
.zz.z.
zzz.zz
.zzz.z
17

2 3
.zz
.z.
3
*/
```

---

## 作者：Loser_Syx (赞：0)

考虑 $L_{l,r},R_{l,r}$ 为对于 $(l,r)$ 所能延伸到最左边的 $(l,L_{l,r})$ 和最右边的 $(l,R_{l,r})$。$g_{l,r}$ 为 $(l,r)$ 所能延伸到最右上的 $(l-g_{l,r},r+g_{l,r})$。

倘若枚举 $l,r$ 为左下角，于是答案只可能在 $1 \sim \min(R_{l,r},g_{l,r})$ 中出现。而对于每个可能的答案 $i$，又需要保证 $L_{l-i,r+i} \leq l$，这个我们可以枚举每条斜线二位数点做。

复杂度 $O(n^2 \log n)$。

[code](https://codeforces.com/contest/628/submission/289013474)。

---

## 作者：Msents (赞：0)

考虑枚举合法矩阵的大小。

一个矩阵要对答案产生贡献，需要同时满足三个条件：

- 第一行全是 `Z`。
- 最后一行全是 `Z`。
- 从矩阵右上角到左下角全是 `Z`。

开两个二维布尔数组 $a$ 和 $b$，设 $k$ 为当前大小，$a_{i,j}$ 表示原矩阵第 $i$ 行的第 $j$ 列到 $j+k-1$ 列是否都是 `Z`，$b_{i,j}$ 表示从 $i$ 行 $j$ 列向右上是否有 $k$ 个 `Z`。

设当前矩阵大小为 $k$，那么对答案的贡献为 $\sum_{i=1}^{n-k+1}\sum_{j=1}^{m-k+1}a_{i,j}\times a_{i+k-1,j}\times b_{i+k-1,j}$。

直接做复杂度是 $O(n^3)$ 的。（$n$ 和 $m$ 同阶）

由于数组元素只有 0 和 1，所以上面式子乘法可以用逻辑且代替，因此可以使用 bitset 优化。

跑了 4s 多，复杂度 $O(\frac{n^3}{w})$。

其实就是暴力做法上 bitset 优化。

码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MaxN=3000;
int n,m;
bitset<MaxN>a[MaxN],b[MaxN],c[MaxN];
void Solve(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			char ch;
			cin>>ch;
			a[i][j]=b[i][j]=c[i][j]=(ch=='z');
		}
	}
	long long ans=0;
	for(int l=1;l<=min(n,m);l++){
		for(int i=0;i+l-1<n;i++)ans+=(b[i]&b[i+l-1]&c[i+l-1]).count();
		for(int i=0;i<n;i++)b[i]&=(b[i]>>1);
		c[l-1]=0;
		for(int i=l;i<n;i++)c[i]&=(a[i-l]>>l);
	}
	cout<<ans;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
//	int T;
//	cin>>T;
//	while(T--)
		Solve();
	return 0;
}
```

---

## 作者：jzh817 (赞：0)

此题可以用bitset或树状数组来编写，其中bitset代码短，速度慢——3354ms；树状数组要快很多——374ms。

此处发一下树状数组版代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
	ll a=0,b=getchar(),c=1;
	while(!isdigit(b))c=b=='-'?-1:1,b=getchar();
	while(isdigit(b))a=a*10+b-'0',b=getchar();
	return a*c;
}
const int N=3008;
struct node{
	int x,y;
}t;
vector<node> d[N];
int n,m,a[N][N],b[N][N][2],c[N][N];
char s[N];
void add(int x,int y,int k){
	while(x<N)c[x][y]+=k,x+=x&(-x);
}
int sum(int x,int y){
	int res=0;
	while(x>0)res+=c[x][y],x-=x&(-x);
	return res;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
			a[i][j]=s[j]=='z';
	}
	for(int i=1;i<=n;i++)
		for(int j=m;j>0;j--)
			if(a[i][j])b[i][j][0]=b[i][j+1][0]+1,b[i][j][1]=b[i-1][j+1][1]+1;
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=m;j>0;j--)
			if(a[i][j]){
				add(i,j,1),t.x=i,t.y=j;
				if(i+b[i][j][0]-1<N)d[i+b[i][j][0]-1].push_back(t);
				ans+=sum(i,j)-sum(i-min(b[i][j][0],b[i][j][1]),j);
			}
		for(int j=0;j<d[i].size();j++)
			add(d[i][j].x,d[i][j].y,-1);
	}
	printf("%lld",ans);
	return 0;
}
```


---

