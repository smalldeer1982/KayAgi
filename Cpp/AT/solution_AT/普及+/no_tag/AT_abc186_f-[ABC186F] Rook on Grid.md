# [ABC186F] Rook on Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc186/tasks/abc186_f

縦 $ H $ マス、横 $ W $ マスのグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,j) $ と表します。

グリッド上には $ M $ 個の障害物があり、$ i $ 番目の障害物はマス $ (X_i,Y_i) $ に置かれています。

マス $ (1,1) $ に飛車の駒が置いてあります。飛車の駒は、今いる位置から右または下方向に伸びる直線上にあり、障害物を飛び越えずに到達できるマスに $ 1 $ 手で移動することができます。

$ 2 $ 手以内の移動で飛車の駒が到達できるマスの数を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ H,W\ \leq\ 2\times\ 10^5 $
- $ 0\leq\ M\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ X_i\ \leq\ H $
- $ 1\leq\ Y_i\ \leq\ W $
- $ (X_i,Y_i)\ \neq\ (1,1) $
- $ (X_i,Y_i) $ は相異なる
- 入力は全て整数

### Sample Explanation 1

障害物のない全てのマスに $ 2 $ 手以内で移動できます。

### Sample Explanation 2

障害物のないマスのうち、$ (4,4),(5,4) $ 以外の全てのマスに $ 2 $ 手以内で移動できます。

## 样例 #1

### 输入

```
4 3 2
2 2
3 3```

### 输出

```
10```

## 样例 #2

### 输入

```
5 4 4
3 2
3 4
4 2
5 2```

### 输出

```
14```

## 样例 #3

### 输入

```
200000 200000 0```

### 输出

```
40000000000```

# 题解

## 作者：Hughpig (赞：16)

考虑其实只有两种走法：

1. 先向右再向下走
2. 先向下再向右走

![](https://cdn.luogu.com.cn/upload/image_hosting/8lsx57xv.png)

（我画了个图，其中红线经过的是第一种走法可以经过的，蓝线是第二种走法可以经过的）

统计第一种走法可以到的点，记录第 $i$ 列第一个障碍格的纵坐标，记作 $b_i$（如果没有障碍格就是边界 $W+1$）。

显然遇到了一个障碍格以后，它以及它后面的格子都到不了。所以第 $i$ 列对答案的贡献是 $b_i-1$。

统计第二种走法可以到达的点同理（先不考虑去重），用 $a_i$ 记录第 $i$ 行第一个障碍格的横坐标，对答案的贡献是 $a_i-1$。

此处要注意一个细节：如果第 $1$ 列存在障碍格，那么这个障碍格的后面的行用第二种走法都无法到达了，可以看作 $b_j\ (a_1\le j\le H)$ 都是 $1$。

但是观察一下上面的图，发现有的点会被重复统计，考虑去重。

观察发现第二种走法中，对于第 $i$ 行，重复的格子为：对于第 $j\ (1\le j<b_i)$ 列，$a_j>i$ 的数量。

可以理解为对于某个 $a_j>i$，那么这一列第一种走法就可以走到，再走就是重复的。第 $i$ 行不重复的格子个数为 $a_j\le i$ 的数量。

所以具体计算答案的步骤就是，对于第 $i$ 行，将答案加上 $a_j\le i\ (1\le j<b_i)$ 的数量。

考虑快速计算这个东西。对于第 $i$ 列，$b_i$ 后面的格子第一种走法都无法到达。

因此对于第 $j\ (j\ge i)$ 行，$b_i$ 格就是非重复格了。

在处理第 $i$ 行时，就可以把 $b_j=i$ 的列标记一下，然后对答案的贡献被标记的列中小于等于 $a_i$ 的个数。

这个东西本质就是单点加，求前缀和。可以用树状数组维护。

时间复杂度 $O(N\log N)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

constexpr ll N=2e5+7;

ll H,W,m,qwq,ans,a[N],b[N],c[N];
vector<int> v[N];

void add(ll pos){
	for(;pos<=qwq;pos+=lowbit(pos))c[pos]++;
}

ll query(ll pos){
	ll ret=0;
	for(;pos;pos-=lowbit(pos))ret+=c[pos];
	return ret;
}

int main()
{
	cin>>H>>W>>m;qwq=max(H,W);
	up(1,qwq,i)a[i]=H+1,b[i]=W+1;
	up(1,m,i){
		ll x,y;cin>>x>>y;
		b[x]=min(b[x],y);
		a[y]=min(a[y],x);
	}
	up(1,a[1]-1,i)ans+=b[i]-1,v[b[i]].pb(i);
	up(a[1],H,i)v[1].pb(i);
	up(1,b[1]-1,i){
		for(auto j:v[i])add(j);
		ans+=query(a[i]-1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cjh20090318 (赞：5)

有一点难度，但不多。

## 题意

一个 $H \times W$ 的地图上有 $M$ 个障碍物。

有一辆车在 $(1,1)$，一次行动可以向下或向右移动任意格（不得穿过障碍物）。

求这辆车在**最多两次**行动中可能到达多少个格子。

## 分析

车有四种选择：向右、向下、先向右再向下、先向下再向右。

然后设 $h_i$ 表示第 $i$ 行最右边可以到达的列，$l_j$ 表示第 $j$ 列最下边可以到达的行。

很显然总答案为 $\sum\limits_{i=1}^{h_1}l_i + \sum\limits_{i=1}^{l_1}h_i - \text{重复计算的部分}$，接下来难点就在于如何计算重复的部分。

考虑对于每一列 $i \in [1,h_1]$，被重复计算的就等于 $\sum\limits_{j=1}^{\min(l_1,l_i)}[h_j \ge i]$。

直接计算的复杂度是 $O(HW)$，无法接受。

题解区中 [Lyccrius 大佬的题解](https://www.luogu.com.cn/blog/_post/572970)使用了权值线段树，~~但是显然我不会~~，考虑换一种想法。

对于每个查询区间的左端点都是固定的，只需要让右端点单调不减，再用一个大小为 $W$ 的树状数组记录出现次数即可，均摊单次复杂度 $O(\log W)$。

总体时间复杂度 $O(W \log W)$，可以通过此题。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<cstring>
#define NDEBUG
#include<cassert>
#include<algorithm>
#define MAXN 200005
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
template<typename T>
struct fenwick_tree{//树状数组模板。
    public:
        fenwick_tree(int _SIZE=0):SIZE(_SIZE){dt=new T[SIZE+1]();memset(dt,0,sizeof(T)*(SIZE+1));}
        fenwick_tree(const fenwick_tree& y):SIZE(y.size()),dt(new T[y.size()+1]){memcpy(dt,y.get_dt(),sizeof(T)*(SIZE+1));}
        ~fenwick_tree(){delete[] dt;}
        const T&operator [] (const int&x)const{assert(0<x&&x<=SIZE);return dt[x];}
        fenwick_tree&operator = (const fenwick_tree&y){if(this!=&y){SIZE=y.size();T*new_dt=new T[SIZE+1]();memcpy(new_dt,y.get_dt(),sizeof(T)*(SIZE+1));delete[] dt;dt=new_dt;}return *this;}
        inline void resize(int _SIZE){T*new_dt =new T[_SIZE+1]();memcpy(new_dt,dt,sizeof(T)*((SIZE<_SIZE?SIZE:_SIZE)+1));delete[] dt;dt=new_dt,SIZE=_SIZE; }
        inline void clear(){SIZE=0;delete[] dt;dt=new T[SIZE+1]();memset(dt,0,sizeof(T)*(SIZE+1));}
        inline int size()const{return SIZE;}
        inline T* get_dt()const{return dt;}
        inline void add(int x,const T&v){assert(0<x&&x<=SIZE);for(;x<=SIZE;x+=x&-x)dt[x]+=v;}
        inline T sum(const int&l,const int&r)const{assert(0<l&&l<=r&&r<=SIZE);return sum(r)-sum(l-1);}
    private:
        T*dt=nullptr;
        int SIZE;
        inline T sum(int x)const{assert(0<=x&&x<=SIZE);T ret(0);for(;x;x^=x&-x)ret+=dt[x];return ret;}
};
int n,m,t;
int h[MAXN],l[MAXN];//同题解中的描述。
PII q[MAXN];//查询区间。
int main(){
	scanf("%d%d%d",&n,&m,&t);
	fill_n(h+1,n,m),fill_n(l+1,m,n);//记得初始化最远的边界。
	for(int x,y;t--;) scanf("%d%d",&x,&y),h[x]=min(h[x],y-1),l[y]=min(l[y],x-1);//注意需要减一，因为是可以到达的。
	LL ans=0;
	for(int i=1;i<=h[1];i++) ans+=l[i],q[i]=make_pair(min(l[1],l[i]),i);
	for(int i=1;i<=l[1];i++) ans+=h[i];
	sort(q+1,q+h[1]+1);//按照右端点从小到大排序。
	static fenwick_tree<int> T(m);
	for(int i=1,j=1;i<=h[1];i++){
		for(;j<=q[i].first;j++)T.add(h[j],1);//扩展查询区间。
		ans-=T.sum(q[i].second,m);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Lyccrius (赞：2)

行和列分开处理。

*   $r[i]$ 表示第 $i$ 行最小障碍物坐标
*   $c[i]$ 表示第 $j$ 列最小障碍物坐标

考虑先往下走再往右走，走到 $(i, 1)$ 时，贡献为 $r[i] - 1$，当 $r[i] = 1$ 时无法继续往下走。

找到第一个 $r[i] = 1$ 的 $i$，$(i, h]$ 行换一种方式处理：将 $i$ 加入第 $r[i] + 1$ 列的标记区。

一个行标记 $x$ 出现在第 $y$ 列的标记区，表示第 $x$ 行被障碍物阻挡，且第 $x$ 行的 $[y, w]$ 部分需要通过先往右走再往下走计算贡献。

考虑先往右走再往下走，走到 $(1, i)$ 时，贡献为标记区前缀并集内小于 $c[i]$ 的元素个数，当 $c[i] = 1$ 时无法继续往右走。

可能文字无法很好的表述，可以画图模拟尝试理解。

计算标记前缀并集元素个数可以使用权值线段树维护。

```cpp
int main() {
    std::cin >> h >> w >> m;
    for (int i = 1; i <= h; i++) r[i] = w + 1;
    for (int i = 1; i <= w; i++) c[i] = h + 1;
    for (int i = 1; i <= m; i++) {
        std::cin >> x >> y;
        r[x] = std::min(r[x], y);
        c[y] = std::min(c[y], x);
    }
    bool flag = true;
    for (int i = 1; i <= h; i++) {
        if (flag) {
            ans += r[i] - 1;
            if (r[i] <= w) t[r[i] + 1].push_back(i);
            if (r[i] == 1) flag = false;
        } else {
            t[2].push_back(i);
        }
    }
    for (int i = 1; i <= w; i++) {
        if (c[i] == 1) break;
        for (auto j : t[i]) SGT.Add(1, 1, h, j, 1);
        ans += SGT.Ask(1, 1, h, 1, c[i] - 1);
    }
    std::cout << ans << '\n';
    return 0;
}
```

---

## 作者：CodingOIer (赞：0)

## [ABC186F] Rook on Grid 题解

### 思路分析

显然，如果走了两步，则第一步的方向肯定是垂直于第二步的方向的，不然可以直接一步走到。

那么就成了对于每一个 $x = 1$ 或 $y = 1$ 作为起点，垂直于 $x$ 或 $y$ 轴走任意步。

如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/kfviv489.png)

图中绿色标注的是 $y = 1$ 能够走到的格子，而青色标注的是 $x = 1$ 能走到的格子。

显然有重复的，需要去重。

我们钦定 $y = 1$ 能够走到的格子数的贡献是**不需要撤销**的，然后撤销 $x = 1$ 的贡献。

令 $col_i$ 表示 $x = 1, y = i$ 时能够走的最远距离。

显然，对于 $i \in [1, w]$ 其中需要撤销的贡献就是 $x \in [1, col_i]$ 中所有能够走的距离 $\ge i$ 的。

显然，不考虑 $x \in [1, col_i]$ 则答案递减。

即 $t_i$ 表示 $x = i$ 目前是否仍然可以到达。

则每次需要撤销的贡献为 $\sum_{i = 1}^{col_i} [t_i]$。

则我们需要维护单点修改，区间查询，树状数组即可。

（<https://atcoder.jp/contests/abc186/submissions/59734313>）

考虑如下 Hack：

![](https://cdn.luogu.com.cn/upload/image_hosting/azg8h7vx.png)

显然，对于 $x \in [2, 3]$，无法产生横着走的贡献。

所以，对于 $x = 1$ 或 $y = 1$ 的情况，我们要记录下 $y$ 或 $x$ 的最小值，记为 $ly$ 和 $lx$。

显然，对于 $x \in [lx, h]$ 行，$y \in [ly, w]$ 列的贡献为 $0$，记得判掉。

### 代码实现

```cpp
#include <algorithm>
#include <cstdio>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int h, w, m;
int ln[MaxN];
int col[MaxN];
long long tree[MaxN];
long long answer;
std::vector<int> v[MaxN];
inline void change(int x, int val)
{
    for (; x <= h; x += x & -x)
    {
        tree[x] += val;
    }
}
inline long long query(int x)
{
    long long res = 0;
    for (; x > 0; x -= x & -x)
    {
        res += tree[x];
    }
    return res;
}
int main()
{
    scanf("%d%d%d", &h, &w, &m);
    int lh, lw;
    lh = h;
    lw = w;
    for (int i = 1; i <= h; i++)
    {
        ln[i] = w;
    }
    for (int i = 1; i <= w; i++)
    {
        col[i] = h;
    }
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ln[x] = std::min(ln[x], y - 1);
        col[y] = std::min(col[y], x - 1);
        if (x == 1)
        {
            lw = std::min(lw, y - 1);
        }
        if (y == 1)
        {
            lh = std::min(lh, x - 1);
        }
    }
    for (int i = lh + 1; i <= h; i++)
    {
        ln[i] = 0;
    }
    for (int i = lw + 1; i <= w; i++)
    {
        col[i] = 0;
    }
    for (int i = 1; i <= w; i++)
    {
        answer += col[i];
    }
    for (int i = 1; i <= h; i++)
    {
        answer += ln[i];
        v[ln[i]].push_back(i);
    }
    for (int i = 1; i <= h; i++)
    {
        change(i, 1);
    }
    for (auto val : v[0])
    {
        change(val, -1);
    }
    for (int i = 1; i <= w; i++)
    {
        answer -= query(col[i]);
        for (auto val : v[i])
        {
            change(val, -1);
        }
    }
    printf("%lld\n", answer);
    return 0;
}
```

---

## 作者：Meickol (赞：0)

本题具有一定思维量。



起点为 $(1,1)$，最多移动两步。无非就两种移动方式：

- 先向右再向下（可以向右 $0$ 步）
- 先向下再向右（可以向下 $0$ 步）



先考虑先右再下的情况：

用 $b_j$ 记录第 $j$ 列从上往下第一个障碍物对应的行号。（无障碍则初始化为 $n+1$）

则第 $j$ 列贡献为 $b_j-1$。



接着考虑先下再右的情况：

用 $a_i$ 记录第 $i$ 行从左往右第一个障碍物对应的列号。（无障碍则初始化为 $m+1$）

但这时第 $i$ 行的贡献并不能用 $a_i-1$ 算。

因为会有一些格子在前面讨论先右向下的移动方式时已经被计算过，这样会计算重复。



考虑去重。

> 首先处理先右再下

显然执行完向右时仍停留在第一行，因为第一行的首个障碍物列号为 $a_1$，即我们向右最多走到第 $a_1-1$ 列。

即第一行的第 $a_{1}$ 列至第 $m$ 列都是无法到达的。

那么我们在处理先右再下时只统计第 $1$ 列至第 $a_{1}-1$ 列的贡献即可。

并且枚举第 $1$ 列至第 $a_{1}-1$ 列的过程中，累加贡献的同时把该列对应的第一个障碍物的位置存起来。



接着再枚举第 $a_1$ 至第 $m$ 列，这时不累加贡献，但是需要把该列对应的第一个障碍物位置存起来。



其中对于位置的存储，我们定义一个二维 `vector`，用 `v[i]` 保存第 $i$ 行中出现的所有障碍物的列号。

因为我们接下来处理先下再右时就是对整行进行操作。



> 接下来处理先下再右

显然执行完向下时仍停留在第一列，因为第一列的首个障碍物行号为 $b_1$，即我们向下最多走到第 $b_{1}-1$ 行

即第一列的第 $b_1$ 行至第 $n$ 行都是无法到达的。

那么我们在处理先下再右时只统计第 $1$ 行至第 $b_{1}-1$ 行的贡献即可。

枚举第 $1$ 行至第 $b_1-1$ 行的过程中，设当前枚举到了第 $i$ 行，首先可以用 $j$ 枚举第 $1 \sim a_i-1$ 列，然后将答案加上贡献 `cnt[j]`，表示前面第 $1 \sim i-1$ 行中有多少个挡住的。因为第 $i$ 行的第 $j$ 列中，其中 $i < b_1$，若存在 $k<i$ 且 $(k,j)$ 存在障碍物，必然导致前面处理先右再下时没有统计到 $(i,j)$ 这个格子的贡献，因为在向下移动时移动到 $(k-1,j)$ 就停下了，导致无法继续向下走到 $(i,j)$。

但是分析一下易知，因为 $n,m$ 同阶，若 $j$ 直接暴力枚举，则时间复杂度将是 $O(n^2)$，会 `TLE`。

于是考虑树状数组优化。

累加完后，再枚举 `v[i]`，用变量 $j$ 遍历 `v[i]`，即将第 $i$ 行中障碍物的列号取出来，然后将 `cnt[j]++` 即可。

将上述思路用树状数组实现一下即可，实现起来还是很容易的。



**最终代码**

```c++
#define rep(x,y,z) for(int x=y;x<=z;x++)
typedef long long LL;
const int N=2e5+5;
int n,m,k;
LL tr[N];
vector<LL> v[N];
int lowbit(int x){
	return x&-x;
}
void add(int x,int v){
	for(int i=x;i<=m;i+=lowbit(i)) tr[i]+=v;
}
LL query(int x){
	LL res=0;
	for(int i=x;i;i-=lowbit(i)) res+=tr[i];
	return res;
}
void solve(){
	cin>>n>>m>>k;
	vector<int> a(n+2,m+1),b(m+2,n+1);
	rep(i,1,k){
		int x,y;
		cin>>x>>y;
		a[x]=min(a[x],y);
		b[y]=min(b[y],x);
	}
	LL ans=0;
	rep(j,1,a[1]-1){
		int i=b[j];
		ans+=i-1;
		v[i].push_back(j);
	}
	rep(j,a[1],m){
		int i=1;
		v[i].push_back(j);
	}
	rep(i,1,b[1]-1){
		ans+=query(a[i]-1);
		for(auto j:v[i]) add(j,1);
	}
	cout<<ans;
}
```

---

## 作者：This_Rrhar (赞：0)

按行计算可达的格子数。令 $f_i$ 表示能否走到当前行第 $i$ 个位置，分类讨论如下：

1. $f_1=1$，显然该行第一个障碍前的所有格子都能到达，再计算第一个障碍后可达的格子数即可。
   
2. $f_1=0$，只需计算该行中可达的格子数即可。

注意到用 $f$ 计算可达格子数等价于对 $f$ 进行区间求和，同时更新一个障碍等价于对 $f$ 进行单点修改，使用树状数组可将修改-查询的时间复杂度由 $O(1)-O(m)$ 改进为 $O(\log m)-O(\log m)$。故时间复杂度为 $O(n\log m)$。

注意第一行需要修改第一个障碍及其后所有列的 $f_i$ 值。

代码（题解与代码中的 $f$ 含义相反）：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define N 100001

ll n,m,k;

vector<ll>v[N<<1];
ll x,y;

#define cnt(l,r) (r-l+1-T.Q(l,r))
struct BIT
{
#define lowbit(x) (x&-x)
	ll C[N<<1];
	void A(ll p){while(p<=m)C[p]++,p+=lowbit(p);}
	ll Q(ll p)
	{
		ll s=0;
		while(p)s+=C[p],p-=lowbit(p);
		return s;
	}
	ll Q(ll l,ll r){return Q(r)-Q(l-1);}
}T;

ll ans;

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	while(k--)cin>>x>>y,v[x].push_back(y);
	if(!v[1].empty())
	{
		sort(v[1].begin(),v[1].end());
		for(int i=v[1].front();i<=m;i++)T.A(i);
	}
	ans=cnt(1,m);
	for(int i=2;i<=n;i++)
	{
		v[i].push_back(m+1);
		if(!T.Q(1))
		{
			sort(v[i].begin(),v[i].end());
			ans+=v[i].front()-1;
			for(ll j:v[i])if(j<=m&&!T.Q(j,j))T.A(j);
			ans+=cnt(v[i].front(),m);
		}
		else
		{
			for(ll j:v[i])if(j<=m&&!T.Q(j,j))T.A(j);
			ans+=cnt(1,m);
		}
	}
	cout<<ans;
}
```

---

## 作者：ybc2026lhy (赞：0)

只有两种方法可以在两次移动或更少的情况下到达一个方格：

1.向下移动，然后向右移动。

2.向右移动，然后向下移动。

在上述每次移动中，允许移动零个方格。由于我们可以通过两种方法到达某些方格，我们必须小心不要重复计算这些方格。

我们可以在 $O(M+W)$ 的总时间内找到后一种方法可以到达的方格，方法是找到每一列中最上面的障碍物。

前一种方法可以用类似的方式找到；但这一次，我们只需要计算那些无法通过后一种方法到达的方格。当且仅当上方有障碍物时，一个方格才能仅通过后一种方法到达（我们认为第一行最左边障碍物右侧的每个方格都有障碍物）。

因此，对于每一行，我们可以用线段树或树状数组来管理每一列是否有障碍物，这样我们就可以在 $O((H+W)\log W)$  的总时间内计算出答案。

AC Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define lowbit(x) x & (-x)

const int N = 1e6 + 10;
ll t[N];

void modify(int x, int n) {
    while(x <= n) {
        t[x]++;
        x += lowbit(x);
    }
}

ll query(int x) {
    ll ans = 0;
    while(x) {
        ans += t[x];
        x -= lowbit(x);
    }
    return ans;
}

struct Point {
    int x, y;
    friend bool operator < (const Point &a,const Point &b){
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }
    friend bool operator == (const Point &a,const Point &b){
        return a.x == b.x && a.y == b.y;
    }
}p[N];

bool vis[N];

void solve() {
    int H, W, M;
    cin >> H >> W >> M;
    int upx = H + 1, upy = W + 1;
    for(int i = 1;i <= M; i++) {
        cin >> p[i].x >> p[i].y;
        if(p[i].x == 1) upy = min(upy, p[i].y);
        if(p[i].y == 1) upx = min(upx, p[i].x);
    }
    for(int i = upx + 1;i <= H; i++) {
        p[++M].x = i; p[M].y = 1;
    }
    for(int j = upy + 1;j <= W; j++) {
        p[++M].y = j; p[M].x = 1;
    }
    sort(p + 1, p + M + 1);
    M = unique(p + 1, p + M + 1) - (p + 1);

    int h = 1;
    ll ans = 0;
    for(int i = 1;i <= M; i++) {
        // 纵向扫描
        if(vis[p[i].y] == 0) {
            vis[p[i].y] = 1;
            modify(p[i].y, W);
        }

        // 横向扫描
        if(i == M || p[i + 1].x != p[i].x) {
            ans += query(W) - query(p[h].y - 1);
            h = i + 1;
        }
    }
    cout << (1ll * H * W - ans) << endl;
}

signed main() {
    solve();
}

---

