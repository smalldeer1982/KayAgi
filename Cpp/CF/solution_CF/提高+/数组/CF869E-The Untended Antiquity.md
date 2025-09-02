# The Untended Antiquity

## 题目描述

Adieu l'ami.

Koyomi is helping Oshino, an acquaintance of his, to take care of an open space around the abandoned Eikou Cram School building, Oshino's makeshift residence.

The space is represented by a rectangular grid of $ n×m $ cells, arranged into $ n $ rows and $ m $ columns. The $ c $ -th cell in the $ r $ -th row is denoted by $ (r,c) $ .

Oshino places and removes barriers around rectangular areas of cells. Specifically, an action denoted by " $ 1\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's placing barriers around a rectangle with two corners being $ (r_{1},c_{1}) $ and $ (r_{2},c_{2}) $ and sides parallel to squares sides. Similarly, " $ 2\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means Oshino's removing barriers around the rectangle. Oshino ensures that no barriers staying on the ground share any common points, nor do they intersect with boundaries of the $ n×m $ area.

Sometimes Koyomi tries to walk from one cell to another carefully without striding over barriers, in order to avoid damaging various items on the ground. " $ 3\ r_{1}\ c_{1}\ r_{2}\ c_{2} $ " means that Koyomi tries to walk from $ (r_{1},c_{1}) $ to $ (r_{2},c_{2}) $ without crossing barriers.

And you're here to tell Koyomi the feasibility of each of his attempts.

## 说明/提示

For the first example, the situations of Koyomi's actions are illustrated below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869E/5930e5689d91726564d05581955bbc9acf5a8c98.png)

## 样例 #1

### 输入

```
5 6 5
1 2 2 4 5
1 3 3 3 3
3 4 4 1 1
2 2 2 4 5
3 1 1 4 4
```

### 输出

```
No
Yes
```

## 样例 #2

### 输入

```
2500 2500 8
1 549 1279 1263 2189
1 303 795 1888 2432
1 2227 622 2418 1161
3 771 2492 1335 1433
1 2017 2100 2408 2160
3 48 60 798 729
1 347 708 1868 792
3 1940 2080 377 1546
```

### 输出

```
No
Yes
No
```

# 题解

## 作者：dAniel_lele (赞：6)

容易发现两个点可以到达当且仅当他们被相同的矩形包含。

考虑使用 sum hash 维护，对于每个矩形随机一个权值 $val_i$，对整个矩形中的位置加上 $val_i$。判断两个点是否权值相等即可。

可以使用二维树状数组解决，复杂度 $O(q\log n\log m)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define lowbit(i) (i&(-i))
#define mid ((l+r)>>1)
using namespace std;
mt19937 rng(time(0));
int n,m;
struct bit{
	int f[2505][2505];
	void chang(int x,int y,int c){
		for(int i=x;i<=n;i+=lowbit(i)) for(int j=y;j<=m;j+=lowbit(j)) f[i][j]+=c;
	}
	int qry(int x,int y){
		int ans=0;
		for(int i=x;i;i-=lowbit(i)) for(int j=y;j;j-=lowbit(j)) ans+=f[i][j];
		return ans;
	}
	void change(int x1,int y1,int x2,int y2,int c){
		chang(x1,y1,c);
		chang(x1,y2+1,-c);
		chang(x2+1,y1,-c);
		chang(x2+1,y2+1,c);
	}
}tree;
map<pair<pair<int,int>,pair<int,int>>,int> mp;
signed main(){
	cin>>n>>m; int q; cin>>q;
	while(q--){
		int opt,x1,y1,x2,y2; cin>>opt>>x1>>y1>>x2>>y2;
		if(opt==1){
			mp[make_pair(make_pair(x1,y1),make_pair(x2,y2))]=rng();
			tree.change(x1,y1,x2,y2,mp[make_pair(make_pair(x1,y1),make_pair(x2,y2))]);
		}
		else if(opt==2){
			tree.change(x1,y1,x2,y2,-mp[make_pair(make_pair(x1,y1),make_pair(x2,y2))]);
		}
		else{
			cout<<((tree.qry(x1,y1)==tree.qry(x2,y2))?"Yes":"No")<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：YuRuiH_ (赞：6)

肯定是打标记操作了，将每一行单独视为一个序列，拆建围墙只需要将x=r1打上标记i，r2+1打上标记-1

在询问的时候，只需要判断该点所处的那一行，就可以知道其处于第几个区域中，如果区域相同，那么就输出yes

**And else 这题的卡常很恶心啊，建议使用读入优化，数组不要开大了，否则绝对会TLE啊**

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int maxn=2506;
int was[maxn][maxn];
 
inline int read()
{
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
 
int main()
{
    int n=read(),m=read(),q=read();
    rep(i,1,q){
    	int t=read(),r1=read(),c1=read(),r2=read(),c2=read();
		if(t==1)rep(r,r1,r2){was[r][c1]=i;was[r][c2+1]=-1;}
		else if(t==2)rep(r,r1,r2)was[r][c1]=was[r][c2+1]=0;
		else{
		    int st=0,res1=0,res2=0;
			dep(i,c1,0)
			    if(was[r1][i]>0)
				    if(st==0){res1=was[r1][i];break;}
				    else st++;
				else if(was[r1][i]<0)st--;
			st=0;
			dep(i,c2,0)
			    if(was[r2][i]>0)
				    if(st==0){res2=was[r2][i];break;}
					else st++;
				else if(was[r2][i]<0)st--; 
			printf("%s",res1==res2?"Yes\n":"No\n");
		}
	}
	return 0;
}
```


---

## 作者：Aleph1022 (赞：5)

由于没有公共点这一性质，我们可以想到用二维树状数组来解决此题。

此题涉及二维树状数组的区间修改单点查询。

如果为增加障碍操作，就可以给这个障碍一个 ID，然后让这个区域内所有数字加上这个 ID。  
很容易想到使用差分。

如果为拆除障碍操作，就把这个区域内所有数字减去这个 ID。

如果为查询操作，就查询这两个点的值是否相同。  
不需要在意 ID 叠加，因为这样也是在同一个障碍之内。

于是有了第一版代码：
```cpp
#include <cstdio>
#include <map>
#define lowbit(x) ((x) & -(x))
using namespace std;
int n,m,q,tot;
struct matrix
{
    int x1,y1,x2,y2;
    inline bool operator<(const matrix &a) const
    {
        if(x1 < a.x1)
            return 1;
        if(y1 < a.y1)
            return 1;
        if(x2 < a.x2)
            return 1;
        if(y2 < a.y2)
            return 1;
        return 0;
    }
};
int c[2510][2510];
map<matrix,int> hs;
inline void update(int x,int y,int k)
{
    for(register int i = x;i <= n;i += lowbit(i))
        for(register int j = y;j <= m;j += lowbit(j))
            c[i][j] += k;
}
inline int query(int x,int y)
{
    int ret = 0;
    for(register int i = x;i;i -= lowbit(i))
        for(register int j = y;j;j -= lowbit(j))
            ret += c[i][j];
    return ret;
}
inline void init()
{
    scanf("%d%d%d",&n,&m,&q);
}
inline void work()
{
    int opt,x1,y1,x2,y2;
    while(q--)
    {
        scanf("%d%d%d%d%d",&opt,&x1,&y1,&x2,&y2);
        if(opt == 1)
        {
            hs[(matrix){x1,y1,x2,y2}] = ++tot;
            update(x1,y1,tot);
            update(x1,y2 + 1,-tot);
            update(x2 + 1,y1,-tot);
            update(x2 + 1,y2 + 1,tot);
        }
        else if(opt == 2)
        {
            int num = hs[(matrix){x1,y1,x2,y2}];
            update(x1,y1,-num);
            update(x1,y2 + 1,num);
            update(x2 + 1,y1,num);
            update(x2 + 1,y2 + 1,-num);
        }
        else
        {
            if(query(x1,y1) == query(x2,y2))
                puts("Yes");
            else
                puts("No");
        }
    }
}
int main()
{
    init();
    work();
    return 0;
}
```

但是这个代码会在第 8 个点 WA 掉。

仔细思考后发现原来是 ID 的问题，这种 ID 分配方式使得有可能出现 $1+3=2+2$ 的尴尬问题。

然后可以想到替代方案  
$\ \ \ \ \ \ \ \ \ \ \ \ $哈希。

我选择把它当做一个 $691$ 进制数，至于为什么取这个数字，是因为我的小号zclclWJN借给了一个中二病同学，他的女友名字谐音为 $691$。

```cpp
#include <cstdio>
#include <map>
#define lowbit(x) ((x) & -(x))
using namespace std;
int n,m,q,tot;
long long c[2510][2510];
inline void update(int x,int y,long long k)
{
    for(register int i = x;i <= n;i += lowbit(i))
        for(register int j = y;j <= m;j += lowbit(j))
            c[i][j] += k;
}
inline long long query(int x,int y)
{
    long long ret = 0;
    for(register int i = x;i;i -= lowbit(i))
        for(register int j = y;j;j -= lowbit(j))
            ret += c[i][j];
    return ret;
}
inline void init()
{
    scanf("%d%d%d",&n,&m,&q);
}
inline void work()
{
    int opt,x1,y1,x2,y2;
    while(q--)
    {
        scanf("%d%d%d%d%d",&opt,&x1,&y1,&x2,&y2);
        if(opt == 1)
        {
            long long num = x1 + y1 * 691 + x2 * 691 * 691 + y2 * 691 * 691 * 691;
            update(x1,y1,num);
            update(x1,y2 + 1,-num);
            update(x2 + 1,y1,-num);
            update(x2 + 1,y2 + 1,num);
        }
        else if(opt == 2)
        {
            long long num = x1 + y1 * 691 + x2 * 691 * 691 + y2 * 691 * 691 * 691;
            update(x1,y1,-num);
            update(x1,y2 + 1,num);
            update(x2 + 1,y1,num);
            update(x2 + 1,y2 + 1,-num);
        }
        else
        {
            if(query(x1,y1) == query(x2,y2))
                puts("Yes");
            else
                puts("No");
        }
    }
}
int main()
{
    init();
    work();
    return 0;
}

```

完美 AC。

---

## 作者：your_bug_fired (赞：2)

可以对矩阵中每一个点打上标记来表示这个点所在的最小的矩形（矩形的边不能重叠，所以这样的矩形存在），将未包含在任何矩阵内的点标记为 $0$。这样当且仅当两个点的标记相同时它们才联通。
  
  使用二维树状数组可以完成矩阵的区间修改（使用差分即可），下面主要考虑如何打标记。
  
  考虑每次建围墙时将对应的矩阵的元素加上一个值（每次加的值当然不同），如果每次加的值相差 $1$（比如第一次加 $1$，第二次加 $2$，以此类推），可能会出现 $1+4=2+3$ 的情况（即一个点在值为 $1$ 和 $4$ 的两道围墙内而另一个点在值为 $2$ 和 $3$ 的两道围墙内，此时这两个点不联通但是他们的值一样），为了避免这种情况，需要每次加的值中任取一些出来，取出数的和是唯一的，自然想到用 $2$ 的幂。而为了不超出整形的范围，对 $2$ 的幂取模处理（我取的是 $10^9+7$）。
  代码如下：
  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 2510;
int n, m, q;
ll c[N][N];
const int mod = 1e9 + 7;

inline int lowbit(int x){
    return x & -x;
}

void update(int x, int y, ll w){
    for(int i = x; i <= n; i += lowbit(i)){
        for(int j = y; j <= m; j += lowbit(j)){
            c[i][j] += w;
        }
    }
}

ll getsum(int x, int y){
    ll ans = 0ll;
    for(int i = x; i; i -= lowbit(i)){
        for(int j = y; j; j -= lowbit(j)){
            ans += c[i][j];
        }
    }
    return ans;
}

int main(){
    cin >> n >> m >> q;
    int cnt = 1;
    while(q--){
        int t, x1, y1, x2, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        if(t == 1){
            update(x1, y1, cnt);
            update(x1, y2 + 1, -cnt);
            update(x2 + 1, y1, -cnt);
            update(x2 + 1, y2 + 1, cnt);
            cnt = (cnt << 1) % mod;
        }
        if(t == 2){
            ll qq = ((getsum(x1, y1) - getsum(x1 - 1, y1 - 1)) % mod + mod) % mod;
            update(x1, y1, -qq);
            update(x2 + 1, y1, qq);
            update(x1, y2 + 1, qq);
            update(x2 + 1, y2 + 1, -qq);
        }
        if(t == 3){
            ll q1 = (getsum(x1, y1) % mod + mod) % mod;
            ll q2 = (getsum(x2, y2) % mod + mod) % mod;
            if(q1 == q2)cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    return 0;
}
```

---

## 作者：lkjzyd20 (赞：1)

### CF869E The Untended Antiquity
二维异或哈希和二维树状数组板题。

给定 $n\times m$ 的网格，$q$ 次操作：

+ 将第 $[x_1,x_2]$ 行，第 $[y_1,y_2]$ 列的矩形框起来。
+ 删掉第 $[x_1,x_2]$ 行，第 $[y_1,y_2]$ 列的矩形框，保证该矩形框存在。
+ 询问 $(x_1,y_1)$ 和 $(x_2,y_2)$ 是否连通。

思路：
一个很显然的性质，我们查询的两个点只有在围在同样的围墙中才能联通，那我们可以给每个矩形框赋值，然后标记一下，使用二维树状数组维护即可。

但是可能会遇到哈希冲突的情况，所以要使用随机数来减小哈希冲突。
```cpp
map<tuple<int,int,int,int>,int>vis;
mt19937 rd(time(0));
int f[N][N];
void add(int x,int y,int v){
    for(int i=x;i<=n;i+=i&-i)
        for(int j=y;j<=m;j+=j&-j)
            f[i][j]^=v;
}
int ask(int xx,int yy){
    int ans=0;
    for(int i=xx;i;i-=i&-i)
        for(int j=yy;j;j-=j&-j)
            ans^=f[i][j];
    return ans;
}
void change(int xx1,int yy1,int xx2,int yy2,int v){
    add(xx1,yy1,v);
    add(xx2+1,yy1,v);
    add(xx1,yy2+1,v);
    add(xx2+1,yy2+1,v);
}
void solve(){
    int opt,xx1,yy1,xx2,yy2;
    cin>>opt>>xx1>>yy1>>xx2>>yy2;
    if(opt==1){
        vis[{xx1,yy1,xx2,yy2}]=rd();
        change(xx1,yy1,xx2,yy2,vis[{xx1,yy1,xx2,yy2}]);
    }
    else if(opt==2){
        change(xx1,yy1,xx2,yy2,vis[{xx1,yy1,xx2,yy2}]);
    }
    else {
        int fx=ask(xx1,yy1),fy=ask(xx2,yy2);
        puts(fx==fy?"Yes":"No");
    }
}
```

---

## 作者：zzwdsj (赞：1)

### 思路
记所有围住点 $a$ 的墙构成的集合为 $A$，记所有围住点 $b$ 的墙构成的集合为 $B$。

若 $A \ne B$，则必然存在墙 $t$，满足 $t \in A,t \notin B$ 或 $t \notin A,t \in B$，把点 $a$ 和点 $b$ 分隔开。

所以 $a$ 和 $b$ 连通当且仅当 $A = B$。
### 实现
使用二维树状数组维护墙。为每个墙计算一个哈希值，当围住 $a$ 的所有墙的哈希值之和与围住 $b$ 的所有墙的哈希值之和相等就认为 $a$ 和 $b$ 联通。

#### 建墙
把墙内的所有格子标记为被它围住。

`updata(a,b,k),updata(a,d+1,-k),updata(c+1,b,-k),updata(c+1,d+1,k)`

#### 拆墙
与建墙相反。

`updata(a,b,-k),updata(a,d+1,k),updata(c+1,b,k),updata(c+1,d+1,-k)`

#### 查询

判断围住 $a$ 的所有墙的哈希值之和与围住 $b$ 的所有墙的哈希值之和是否相等。

`cout<<(getsum(a,b)==getsum(c,d)?"Yes":"No")<<endl`

### code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) (x&(-x))
int n,m,t,a,b,c,d,q,k,tree[2501][2501];
void updata(int x,int y,int d)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=m;j+=lowbit(j))
			tree[i][j]+=d;
}
int getsum(int x,int y)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		for(int j=y;j;j-=lowbit(j))
			res+=tree[i][j];
	return res;
}
//使用查分实现单点查询，区间修改 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>q;
	while(q--&&cin>>t>>a>>b>>c>>d)
	{
		if(t==1) k=(a+b*n+c*n*n+d*n*n*n)%1000000009/*计算这堵墙的哈希值*/,updata(a,b,k),updata(a,d+1,-k),updata(c+1,b,-k),updata(c+1,d+1,k);
		else if(t==2) k=(a+b*n+c*n*n+d*n*n*n)%1000000009/*计算这堵墙的哈希值*/,updata(a,b,-k),updata(a,d+1,k),updata(c+1,b,k),updata(c+1,d+1,-k);
		else cout<<(getsum(a,b)==getsum(c,d)?"Yes":"No")<<endl;
	}
	return 0;
}
```

---

## 作者：Claire0918 (赞：0)

我们注意到两个点互相连通当且仅当包含它们的墙所构成的集合相等。

下面给出证明。

首先是充分性：如果两个点互相连通，那么包含它们的墙所构成的集合相等。运用反证法，假设两集合不相等，那么两点之间至少有一条墙的边，故假设不成立。

然后是必要性：如果包含两点的墙所构成的集合相等，那么两点互相连通。

我们先证明一个引理：任意一点都可以到达其所在最内层的墙的边界。假设不能到达，那么需要若干个不同的墙的部分边将其围住，即这些边连在一起，这与任意两个墙不相交是矛盾的，所以都可以到达。

我们不难证明，一个墙边界上的任意两点都是可以互相到达的，这还是因为任意两个墙不相交。于是，对于集合相等的两点，我们先使它们都走到最内层墙的边界上，随后在边界上互相到达。

这样，我们完整地证明了这个性质。$\square$

根据这个性质，我们考虑维护包含每个点的墙的集合。运用哈希，对于每一个墙，修建时将该墙每一个包含的点加上一个哈希值，拆除时减去。判断是否连通只需判断两个点的哈希值是否相等即可。

我们需要在二维平面内支持矩形内每一个点的加和单点的查询，使用二维树状数组即可。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

mt19937 rnd(time(0));

const int maxn = 2500 + 10;

int n, m, q;
map<pair<pair<int, int>, pair<int, int> >, int> table;

inline int lowbit(int x){
    return x & -x;
}

struct{
    long long tree[maxn][maxn];
    inline void add(int x, int y, int k){
        for (int i = x; i <= n; i += lowbit(i)){
            for (int j = y; j <= m; j += lowbit(j)){
                tree[i][j] += k;
            }
        }
    }
    inline long long query(int x, int y){
        long long res = 0;
        for (int i = x; i; i -= lowbit(i)){
            for (int j = y; j; j -= lowbit(j)){
                res += tree[i][j];
            }
        }
        return res;
    }
    inline void add(int x1, int y1, int x2, int y2, int k){
        add(x1, y1, k);
        add(x2 + 1, y1, -k);
        add(x1, y2 + 1, -k);
        add(x2 + 1, y2 + 1, k);
    }
} tree;

int main(){
    scanf("%d %d %d", &n, &m, &q);
    int p = 0;
    while (q--){
        int op, x1, y1, x2, y2;
        scanf("%d %d %d %d %d", &op, &x1, &y1, &x2, &y2);
        if (op == 1){
            const int val = table[make_pair(make_pair(x1, y1), make_pair(x2, y2))] = rnd();
            tree.add(x1, y1, x2, y2, val);
        }else if (op == 2){
            tree.add(x1, y1, x2, y2, -table[make_pair(make_pair(x1, y1), make_pair(x2, y2))]);
        }else if (op == 3){
            printf(tree.query(x1, y1) == tree.query(x2, y2) ? "Yes\n" : "No\n");
        }
    }

return 0;
}
```

---

## 作者：Felix72 (赞：0)

看到是维护连通性，想到用一个数据结构维护每个区域。这里用树状数组。

我们给每堵墙围成的区域都加上一个值，拆掉的时候撤销即可。判断连通性时看两个坐标的值是否相同。

然而这样的哈希可能被卡。~~受到不可以，总司令启发~~我们使用随机数哈希就能切掉了。

此处使用双哈希。

```
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 2510;
int n, m, q;
struct node
{
	int first, second, third, fourth;
	bool operator < (const node &w) const {
		if(first != w.first) return first < w.first;
		if(second != w.second) return second < w.second;
		if(third != w.third) return third < w.third;
		return fourth < w.fourth;
	}
};
map < node, int > mp1, mp2;
struct Tree
{
	int c[N][N];
	inline void add(int x, int y, int num)
	{
		for(int i = x; i <= n; i += lowbit(i))
			for(int j = y; j <= m; j += lowbit(j))
				c[i][j] += num;
	}
	inline void cover(int ax, int ay, int bx, int by, int num)
	{
		add(ax, ay, num);
		add(ax, by + 1, -num);
		add(bx + 1, ay, -num);
		add(bx + 1, by + 1, num);
	}
	inline int ask(int x, int y)
	{
		int ans = 0;
		for(int i = x; i; i -= lowbit(i))
			for(int j = y; j; j -= lowbit(j))
				ans += c[i][j];
		return ans;
	}
}T1, T2;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	srand(time(0));
	cin >> n >> m >> q;
	for(int i = 1; i <= q; ++i)
	{
		int opt, n1, n2, n3, n4; cin >> opt >> n1 >> n2 >> n3 >> n4;
		if(opt == 1)
		{
			mp1[{n1, n2, n3, n4}] = rand();
			mp2[{n1, n2, n3, n4}] = rand() * rand();
			T2.cover(n1, n2, n3, n4, mp2[{n1, n2, n3, n4}]);
		}
		if(opt == 2)
		{
			T1.cover(n1, n2, n3, n4, -mp1[{n1, n2, n3, n4}]);
			T2.cover(n1, n2, n3, n4, -mp2[{n1, n2, n3, n4}]);
			mp1[{n1, n2, n3, n4}] = 0;
			mp2[{n1, n2, n3, n4}] = 0;
		}
		if(opt == 3)
		{
			if(T1.ask(n1, n2) == T1.ask(n3, n4) && T2.ask(n1, n2) == T2.ask(n3, n4)) cout << "Yes" << '\n';
			else cout << "No" << '\n';
		}
	}
	return 0;
}
```

---

## 作者：lsw1 (赞：0)

首先，两个点肯定要被围在同样的围墙中，否则两个点显然无法互相到达。

明确了这个事实，我们来看看这道题。

不妨把建墙看成二维区间加，拆墙看成二维区间减，把判断两个点是否被围在同样的围墙中看成判断这两个点的值是否相同。这个过程可以用二维树状数组解决。

但是，新的问题又出现了：区间加什么？从 $1$ 开始逐个加显然不行，因为 $2+3=1+4$ ，如果一个点被墙 $2,3$ 围住，另一个点被墙 $1,4$ 围住，那么这两个点就会被判为可以互相到达，但是这两个点显然是无法互相到达的。

一个方法是把一个操作看成一个 $BASE$ 进制数，每次加上这个数。这样重复的概率比较小。另一个方法是用随机数，这样重复的概率更小。

这里给出第一种方法的代码实现。

```cpp
#include <iostream>
using namespace std;
const int MAXN = 25e2;
const int BASE = 666;//我这里是666进制数，当然其他进制的也可以
/***************树状数组模板********************/
int tree[MAXN + 5][MAXN + 5];
int n,m,q;
int lowbit(int x)
{
	return x & -x;
}
void add(int x,int y,int k)
{
	for(int i = x;i <= n;i += lowbit(i))
	{
		for(int j = y;j <= m;j += lowbit(j))
		{
			tree[i][j] += k;
		}
	}
}
int query(int x,int y)
{
	int sum = 0;
	for(int i = x;i > 0;i -= lowbit(i))
    {
		for(int j = y;j > 0;j -= lowbit(j))
		{
			sum += tree[i][j];
		}
	}
	return sum;
}
/***************树状数组模板********************/
int main()
{
	cin >> n >> m >> q;
	while(q--)
	{
		int opt,x1,y1,x2,y2;
		cin >> opt >> x1 >> y1 >> x2 >> y2;
		if(opt == 1)//区间加
		{
			int k = x1 * BASE * BASE * BASE + y1 * BASE * BASE + x2 * BASE + y2;//666进制数
			add(x1,y1,k);//利用差分数组的思想区间加
			add(x1,y2 + 1,-k);
			add(x2 + 1,y1,-k);
			add(x2 + 1,y2 + 1,k);
		}
		else if(opt == 2)//区间减
		{//同理
			int k = x1 * BASE * BASE * BASE + y1 * BASE * BASE + x2 * BASE + y2;
			add(x1,y1,-k);
			add(x1,y2 + 1,k);
			add(x2 + 1,y1,k);
			add(x2 + 1,y2 + 1,-k);
		}
		else
		{
			if(query(x1,y1) == query(x2,y2))//判断
			{
				cout << "Yes\n";
			}
			else
			{
				cout << "No\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：Zemu_Ooo (赞：0)

怎么硕呢。。。。。。

按我的思路来讲的话，有两种解法，我直接讲用哈希+二维树状数组的方法的行了。

其实很简单，当覆盖两点的最小矩形不同时，一定不可达，这样的问题不难想到经典的二维树状数组+差分来支持二维区间覆盖+查询。

对于覆盖操作，我们可以差分的给这个矩阵里加上一个编号。

对于操墙操作，我们可以反着减去这个编号。

对于查询，就查询这两个点的值是否相同，编号的累积不影响，因为只有在同一个墙内才会累积。
（注意：如果只是单单的把编号从1开始标号是不够的 因为会出现$1+3=2+2$这类情况
）

别的不多说，直接上代码

```cpp
#include<bits/stdc++.h>
#define uint unsigned int
#define N 2505
#define lowbit(x) x&(-x)
#define base 19260817
using namespace std;
template<class T>
inline void read(T &x)
{
    x=0; int f=1;
    static char ch=getchar();
    while((!isdigit(ch))&&ch!='-')  ch=getchar();
    if(ch=='-') f=-1;
    while(isdigit(ch))  x=x*10+ch-'0',ch=getchar();
    x*=f;
}
int tree[N][N],n,m,id;
inline void add(int x,int y,int z)
{
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=m;j+=lowbit(j))
            tree[i][j]+=z;
}
inline int query(int x,int y)
{
    int ans=0;
    for(int i=x;i;i-=lowbit(i))
        for(int j=y;j;j-=lowbit(j))
            ans+=tree[i][j];
    return ans;
}
/*struct matrix
{
    int x1,y1,x2,y2;
    inline bool operator<(const matrix &a) const
    {
        if(x1 < a.x1)
            return 1;
        if(y1 < a.y1)
            return 1;
        if(x2 < a.x2)
            return 1;
        if(y2 < a.y2)
            return 1;
        return 0;
    }
};
map <matrix,int> M;*/
int main()
{
    int Q;
    read(n),read(m),read(Q);
    for(int i=1,x1,y1,x2,y2,opt;i<=Q;i++)
    {
        read(opt),read(x1),read(y1),read(x2),read(y2);
        uint num=x1*base*base*base+x2*base*base+y1*base+y2;
        //当覆盖两点的最小矩形不同时，一定不可达
        if(opt==1)
        {
        //  M[(matrix){x1,y1,x2,y2}]=++id;
            add(x1,y1,num);
            add(x1,y2+1,-num);
            add(x2+1,y1,-num);
            add(x2+1,y2+1,num);
        }
        if(opt==2)
        {
        //  int num=M[(matrix){x1,y1,x2,y2}];
            add(x1,y1,-num);
            add(x1,y2+1,num);
            add(x2+1,y1,num);
            add(x2+1,y2+1,-num);
        }
        if(opt==3)
        {
            if(query(x1,y1)==query(x2,y2)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
```


---

