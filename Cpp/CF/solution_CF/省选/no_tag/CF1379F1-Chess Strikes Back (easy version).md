# Chess Strikes Back (easy version)

## 题目描述

Note that the difference between easy and hard versions is that in hard version unavailable cells can become available again and in easy version can't. You can make hacks only if all versions are solved.

Ildar and Ivan are tired of chess, but they really like the chessboard, so they invented a new game. The field is a chessboard $ 2n \times 2m $ : it has $ 2n $ rows, $ 2m $ columns, and the cell in row $ i $ and column $ j $ is colored white if $ i+j $ is even, and is colored black otherwise.

The game proceeds as follows: Ildar marks some of the white cells of the chessboard as unavailable, and asks Ivan to place $ n \times m $ kings on the remaining white cells in such way, so that there are no kings attacking each other. A king can attack another king if they are located in the adjacent cells, sharing an edge or a corner.

Ildar would like to explore different combinations of cells. Initially all cells are marked as available, and then he has $ q $ queries. In each query he marks a cell as unavailable. After each query he would like to know whether it is possible to place the kings on the available cells in a desired way. Please help him!

## 说明/提示

In the first example case after the second query only cells $ (1, 1) $ and $ (1, 5) $ are unavailable. Then Ivan can place three kings on cells $ (2, 2) $ , $ (2, 4) $ and $ (2, 6) $ .

After the third query three cells $ (1, 1) $ , $ (1, 5) $ and $ (2, 4) $ are unavailable, so there remain only 3 available cells: $ (2, 2) $ , $ (1, 3) $ and $ (2, 6) $ . Ivan can not put 3 kings on those cells, because kings on cells $ (2, 2) $ and $ (1, 3) $ attack each other, since these cells share a corner.

## 样例 #1

### 输入

```
1 3 3
1 1
1 5
2 4```

### 输出

```
YES
YES
NO```

## 样例 #2

### 输入

```
3 2 7
4 2
6 4
1 3
2 2
2 4
4 4
3 1```

### 输出

```
YES
YES
NO
NO
NO
NO
NO```

# 题解

## 作者：yuzhechuan (赞：7)

很好玩的一道题，~~码量短的让人觉得EF反了~~

---

### 题解：

首先是一个转化：题目给出的矩阵是$2n\times2m$的，很古怪，于是把每个$2\times 2$的小矩阵看做一个，并行处理，于是现在要处理的是一个$n\times m$的大矩阵，在每一个小矩阵中放入一个国王

注意到一个小矩阵有且只会有两个白格子，一个左上，一个右下

于是一个小矩阵会有四种状态：

1. 没有限制：不用管

2. 只有右下能放：记这个小矩阵为一个L点

3. 只有左上能放：记这个小矩阵为一个R点

3. 都不能放：显然为NO

注意到当前答案为NO的充要条件是**存在一个R点在一个L点的右下方（即横纵坐标都大于等于）**

证明很好证，简单来说就是两端限定了，那么中间矩形部分的状态都是唯一的，且在这种情况下是必定冲突的

于是可以对行建立线段树，维护L点的最左点，R点的最右点，想要合法就要靠下部分的最右R点大于等于靠上部分的最左L点，这个东西只要pushup的时候维护一下就好了

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx,avx2")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t,class ...A> inline void read(t &x,A &...a){
	read(x);read(a...);
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

#define pii pair<int,int>
#define x first
#define y second

const int N=2e5+5;
int n,m,q,mi[N<<2],ma[N<<2];
map<pii,bool> mp;
bool fl[N<<2];
set<int> lset[N],rset[N]; //lset:L点点集，rset：R点点集

void pushup(int x){
	ma[x]=max(ma[x<<1],ma[x<<1|1]);
	mi[x]=min(mi[x<<1],mi[x<<1|1]);
	fl[x]=fl[x<<1]|fl[x<<1|1]|(ma[x<<1|1]>=mi[x<<1]); //注意是取或
}

void build(int x,int l,int r){
	if(l==r){
		ma[x]=0;mi[x]=m+1;
		return ;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}

void up(int x,int l,int r,int p){
	if(l==r){
		ma[x]=rset[l].size()?*rset[l].rbegin():0; //维护该行最右点
		mi[x]=lset[l].size()?*lset[l].begin():m+1; //维护该行最左点
		fl[x]=ma[x]>=mi[x];
		return ;
	}
	int mid=l+r>>1;
	if(p<=mid) up(x<<1,l,mid,p);
	else up(x<<1|1,mid+1,r,p);
	pushup(x);
}

void doit(){
	int x,y;
	read(x,y);x++;y++; //都+1方便下面/2
	if(mp[pii(x,y)]){ //用map暴力存点是否被限制
		if(y&1) rset[x>>1].erase(y>>1); //注意+1后奇偶翻转了
		else lset[x>>1].erase(y>>1);
	}
	else{
		if(y&1) rset[x>>1].insert(y>>1);
		else lset[x>>1].insert(y>>1);
	}
	mp[pii(x,y)]^=1;
	up(1,1,n,x>>1);
	puts(fl[1]?"NO":"YES"); //fl=1表示不合法
}

signed main(){
	read(n,m,q);
	build(1,1,n);
	while(q--) doit();
}
```

---

## 作者：Eric159357 (赞：2)

提供一个树状数组的思路。码量比其他题解小。

将棋盘划分成 $2 \times 2$ 的大方块。容易注意到的是：一个大方块里有且仅有一个国王。

- 情况1：如果将奇数列的白格拿走，那么处在这个大方块的国王就只能放在偶数列上，并且这个国王右下方的所有国王位置也要在偶数列上。

![](https://cdn.luogu.com.cn/upload/image_hosting/b6imrb0l.png)

- 情况2：如果将偶数列的白格拿走，那么处在这个大方块的国王就只能放在奇数列上，并且这个国王左上方的所有国王位置也都要在奇数列上。

![](https://cdn.luogu.com.cn/upload/image_hosting/qo5ox86k.png)

因此，只要能判断拿掉的这个白格子上面是否一定有国王，问题就解决了。

定义 $f_i$ 表示第 $i$ 列中所有“左上”大格子的纵坐标最大值。 $g_i$ 表示第 $i$ 列中所有“右下”大格子的纵坐标最小值。

显然，在更新 $f_i$ 和 $g_i$ 时，要不然对 $1 \sim i$ 取最大值，要不然对 $i \sim m$ 取最小值，完全可以用树状数组维护。

---

**代码：**

```cpp
#include <iostream>
#define MAXN 200050
#define ll long long
using namespace std;
int n,m,q,x,y,z;
 
struct BIT{
    ll t[MAXN],l;
    void init(int le,int num)
    {
        for (int i=1;i<=le;i++) t[i]=num;
        l=le;
    }
    void updata(int p,ll k,int mode)
    {
        for (int i=p;i<=l;i+=i&-i)
            t[i]=(mode==1)?max(t[i],k):min(t[i],k);
    }
    ll getans(int p,int mode)
    {
        ll ans=(mode==1)?-1e9:2e9;
        for (int i=p;i>=1;i-=i&-i)
            ans=(mode==1)?max(ans,t[i]):min(ans,t[i]);
        return ans;
    }
}a,b;
 
int main()
{
    int flag=0;
    cin>>n>>m>>q;
    a.init(n,0);
    b.init(n,1e9);
    for (int i=1;i<=q;i++)
    {
        cin>>x>>y;
        if (flag)
        {
            cout<<"NO"<<endl;
            continue;
        }
        z=x%2;
        x=(x+1)/2;
        y=(y+1)/2;
        if (z==0)
        {
            if (b.getans(x,2)<=y)
            {
                flag=1;
                cout<<"NO"<<endl;
                continue;
            }
            a.updata(n-x+1,y,1);
        }
        else
        {
            if (a.getans(n-x+1,1)>=y)
            {
                flag=1;
                cout<<"NO"<<endl;
                continue;
            }
            b.updata(x,y,2);
        }
        cout<<"YES"<<endl;
    }
    return 0;
}
```



---

## 作者：Erica_N_Contina (赞：1)

## 思路

王的走法是**横直斜走均可**，与后的走法相同，但每次只能走一格。

我们先把每个 $2\times 2$ 的格子看作一个大格子，每个大格子左上角和右下角都是白色。题目要求我们只能把王放在白格子上，所以每个大格子有两种放法，$4$ 种状态。

- 左上角和右下角都可以放。

- 只有左上角可以放。

- 只有右下角可以放。

- 都不可以放。

很显然每一个大格子中最多只能放一个王，因此如果出现说明第 $4$ 种情况就直接无解。

那么还有什么情况是无解的呢？很显然是对于两个大格子，记 $a$ 在 $b$ 的左上角，如果 $a$ 是情况 $3$ 且 $b$ 是情况 $2$，那么一定无解。或者记 $a$ 在 $b$ 左侧，如果 $a$ 是情况 $3$ 且 $b$ 是情况 $2$，那么也无解。竖直方向雷同。

讨论这三种情况有一点复杂，实际上我们可以把它们合成为一种情况。

如果这个大格子为情况 $2$，那么我们就把左上角的格子标记为 $a$。如果这个大格子为情况 $3$，那么我们就把左上角的格子标记为 $b$。那么如果有一个 $a$ 格子在一个 $b$ 格子右下角或者右上角，就无解。

更进一步地，如果只有一组大格子不合法而其他大格子之间都合法，那么一定存在一个 $a$ 点在 $b$ 点的右下方（不一定要相邻，横纵坐标都大于等于即可）。这样的话上面的两种情况都可以用这一种情况来代表。

---

对于实现方法，我们可以使用线段树。我们维护最左上方的 $b$ 点为 $b'$ 和最右下方的 $a$ 点为 $a'$（这里的 $a,b$ 指代性质，$a',b'$ 指代特定的点），如果 $a'$ 在 $b'$ 的右下方，那么就是不合法了。否则就是合法的。

我们维护一棵线段树，记录每一行 $i$ 中最右边的 $a$ 点为 $mx_i$ 和最左边的 $b$ 点为 $mn_i$。并且数组 $mx_i$ 满足后缀性质，$mn_i$ 满足前缀性质（前缀性质：如果当前位置没有值，则从后面的值继承过来）。



## 代码

```C++
#include<bits/stdc++.h>
#define rep(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define per(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
#define int long long
#define pii pair<int,int>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int N=1e6+15;
const int INF=1e18+5;
const int MOD=998244353;

int n,q;
int stk[N],top;

int m;
int mn[N],mx[N];
map<pii,int> vis;
bool f[N];
set<int> a[N],b[N];

void pushup(int x){
	mx[x]=max(mx[x<<1],mx[x<<1|1]);
	mn[x]=min(mn[x<<1],mn[x<<1|1]);
	f[x]=(mx[x<<1|1]>=mn[x<<1]);
	f[x]=f[x]||f[x<<1]||f[x<<1|1]; //维护当前区间是否合法，可以继承
}

void change(int x,int l,int r,int p){
	if(l==r){
		mx[x]=a[l].size()?*a[l].rbegin():0;
		mn[x]=b[l].size()?*b[l].begin():m+1;
		f[x]=mx[x]>=mn[x];
		return ;
	}
	int mid=l+r>>1;
	if(p<=mid)change(x<<1,l,mid,p);
	else change(x<<1|1,mid+1,r,p);
	pushup(x);
}

void build(int x,int l,int r){
	if(l==r){
		mx[x]=0;mn[x]=m+1;
		return ;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}

signed main(){
	n=rd,m=rd,q=rd;
	build(1,1,n);
	while(q--){
		int x=rd+1,y=rd+1;//为了划分大格子方便
		if(vis[make_pair(x,y)]){
			if(y&1) a[x>>1].erase(y>>1);
			else b[x>>1].erase(y>>1);
		}
		else{
			if(y&1) a[x>>1].insert(y>>1);
			else b[x>>1].insert(y>>1);
		}
		
		vis[pii(x,y)]^=1;//修改点的限制状态
		change(1,1,n,x>>1);
		
		if(f[1])cout<<"NO\n";
		else cout<<"YES\n";
		
	}
}
/*
10 2
1 4 6 7 8 10 15 120 199 222

*/
```




---

## 作者：RockyYue (赞：0)

### 1379F1

$2n\times 2m$ 棋盘黑板染色，$(1,1)$ 白色。$q$ 次操作，每次将一个白格染黑，且影响后续操作，问是否能在余下的白格中放入 $n\times m$ 个棋子，使其两两之间无共角，要求 $O(q\log n)$。

### Sol

- 一次操作不可行则后续都不可行，只需判断在之前操作基础上再染黑这个白格的影响。

- 需要放入的棋子数量恰好是初始白格一半，且不能有选两个对角白格，故将棋盘划分成若干 $2\times 2$ 块，则每块至多放一个，同时要求每块恰好放一个。
- 一次操作则相当于强制一个白格不选，强制另一个选，则这个白格被强制不选时不可行。
  - 限制会蔓延，强制选的白格的另一个对角白格不能选，最终：若强制选的白格在块内左上，整个棋盘中 $(1,1)$ 左上，这个各右下的矩形中所有块只能选左上白格；强制右下选则整个棋盘右下一部分只能选块内右下。
  - 细节上，$(x,y)$ 在块内左上当且仅当 $x,y$ 同奇，右下同偶。
- 问题转化为，维护这样一种覆盖，查询本次操作中强制不选的点是否被强制选。
  - 以块内左上点为例，维护 $maxyzs_{1\dots n}$，$maxyzs_i$ 表示 $x=i$（$x$ 行 $y$ 列）满足块内左上，且强制选的点中，$y$ 最大值，对于块内左上的点 $(x_0,y_0)$， $\max_{x_0\le x\le n}\{maxyzs_x\}\ge y_0$ 等价与其被强制选。
  - 同样，维护 $minyyx_{1\dots n}$，可以树状数组。
- 写法上：树状数组无论前缀后缀，`upd` 和 `qry` 中操作范围相反（原因：覆盖查询）。

---

## 作者：_Cheems (赞：0)

注意到棋盘大小为 $2n\times 2m$，共 $2nm$ 个白格，同时国王数量为 $nm$，尝试将 $2$ 个国王捆绑在一块，即将棋盘均匀划分为若干个 $2\times 2$ 大小的大格子。

在此基础上观察，显然同一个大格子内的两个白格不能同时放置国王，同时大格子数量为 $nm$，因此问题转化为判定能否使得所有大格子都有一个国王，这是此题不易想到但是很必要的一步。

初始情况下必定满足条件，那么移去一个白格，显然这个白格所属的大格子只能将国王安置在另一个白格上。

对移去的白格在大格子中的位置分类讨论，设左上角的被移去，则当前大格子正下方和正右方的大格子的左上角也无法放置，也就是说这个两个大格子的安置方案也被唯一确定了。以此类推，可以发现当前大格子到棋盘右下角的矩形内的所有大格子都无法将国王安置到左上白格。

同理，假如移去白格位于右下，则当前大格子到棋盘左上角的矩形内的所有大格子都无法将国王安置到右下白格。

考虑什么时候无解，即存在某个大格子的左上、右下白格均无法安置国王。换句话说，我们定义左上白格被移去的大格子为 $1$ 类格子，右下白格被移去的为 $2$ 类白格，那么无解当且仅当存在 $2$ 类格子在 $1$ 类格子的右下方。

这个问题可用树状数组解决。若当前操作的是 $2$ 格子 $x,y$，则查找 $x$ 坐标在 $[1,x]$ 内的、纵坐标最小的大格子并进行比较，之后将当前格子插入树状数组即可。$1$ 类格子同理。

复杂度 $O(q\log n)$。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, inf = 1e9;
int n, m, q, x, y, xx, yy;
bool flag; 

namespace BIT{
	int t[N], t2[N];
	inline void init(int t[]) {for(int i = 0; i < N; ++i) t[i] = inf;}
	inline void upd(int t[], int a, int k) {for(; a < N; a += a & (-a)) t[a] = min(t[a], k);}
	inline int qry(int t[], int a) {int res = inf; for(; a > 0; a -= a & (-a)) res = min(res, t[a]); return res;}
}
using namespace BIT;
signed main(){
    init(t), init(t2);
    cin >> n >> m >> q;
    while(q--){
        scanf("%d%d", &x, &y);
        xx = (x + 1) >> 1, yy = (y + 1) >> 1;
        if(x & 1){
            if(-qry(t2, n - xx + 1) >= yy) flag = true;
            upd(t, xx, yy);
        }
        else{
            if(qry(t, xx) <= yy) flag = true;
            upd(t2, n - xx + 1, -yy);
        }
        (flag == true) ? printf("NO\n") : printf("YES\n");
    }
	return 0;
}
```

---

## 作者：Exp10re (赞：0)

非常好玩线段树。

F2 加了一个删除其实没难多少，建议去写一下，思路是一样的。

## 解题思路

我们记 $2\times2$ 的黑白格子为一个大格子。那么一整个棋盘就可以视为 $n\times m$ 个大格子。

显然如果棋盘中有大格子两个白格都不能放棋子显然无解。

除此之外任意一个大格子有三个状态：

- 两个白格都可以放棋子。这个大格子影响不大，先不管他。

- 只有左上方的格子能放棋子（记为 R）。这个大格子左上方的所有大格子里面的棋子都必须放在这个大格子的左上方。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/o5s6n1am.png)

- 只有右上方的格子能放棋子（记为 L）。这个大格子右下方的所有大格子里面的棋子都必须放在这个大格子的右下方。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0ancmmpp.png)

那么显然的，如果存在一个 L 格子在一个 R 格子的左上方，则无解。否则有解。

使用线段树维护区间最靠左的 L 以及最靠右的 R，在线段树合并时判断左节点最靠左的 L 是否小于右节点最靠右的 R ，如果是，那么无解。

对于如何计算每一行最靠左的 L 以及最靠右的 R，使用 set 维护每一行的所有 L 和 R 即可。

详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=200100;
struct segtree
{
	long long l,r,lmin,rmax,tag;
};
segtree a[MAXN*4];
set<long long> L[MAXN],R[MAXN];
long long n,m,N;
void pushup(long long x)
{
	a[x].lmin=min(a[x*2].lmin,a[x*2+1].lmin);
	a[x].rmax=max(a[x*2].rmax,a[x*2+1].rmax);
	if(a[x*2].tag||a[x*2+1].tag)
	{
		a[x].tag=1;
	}
	else if(a[x*2].lmin<=a[x*2+1].rmax)
	{
		a[x].tag=1;
	}
	else
	{
		a[x].tag=0;
	}
	return;
}
void build(long long x,long long l,long long r)
{
	a[x].l=l;
	a[x].r=r;
	if(l==r)
	{
		a[x].lmin=N+1;
		a[x].rmax=-1;
		a[x].tag=0;
		return;
	}
	long long mid=(a[x].l+a[x].r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	pushup(x);
	return;
}
void inc(long long x,long long l,long long r)
{
	if(a[x].l==l&&a[x].r==r)
	{
		a[x].lmin=*L[a[x].l].begin();
		a[x].rmax=*R[a[x].l].rbegin();
		if(a[x].lmin<=a[x].rmax)
		{
			a[x].tag=1;
		}
		else
		{
			a[x].tag=0;
		}
		return;
	}
	long long mid=(a[x].l+a[x].r)/2;
	if(l<=mid)
	{
		inc(x*2,l,min(mid,r));
	}
	if(r>=mid+1)
	{
		inc(x*2+1,max(l,mid+1),r);
	}
	pushup(x);
	return;
}
int main()
{
	long long ta,tb,i,j;
	scanf("%lld%lld%lld",&n,&N,&m);
	for(i=1;i<=n;i++)
	{
		L[i].insert(N+1);
		R[i].insert(-1);
	}
	build(1,1,n);
	for(i=1;i<=m;i++)
	{
		scanf("%lld%lld",&ta,&tb);
		ta++;
		tb++;
		if(ta%2==0)
		{
			L[ta/2].insert(tb/2);
		}
		else
		{
			R[ta/2].insert(tb/2);
		}
		inc(1,ta/2,ta/2);
		if(a[1].tag)
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
		}
	}
	return 0;
}
```

---

## 作者：Find_Yourself (赞：0)

数据结构之小清新思维题。

容易想到把 $2n\times2m$ 棋盘中每个 $2\times 2$ 的部分压缩，其中必须含有恰好一个棋子。

对于每个 $2\times 2$ 分两种情况讨论（可能同时具备或不具备以下两种）：

1. 左上角不能用，记为 $L$。

2. 右下角不能用，记为 $R$。

然后通过画图可以发现，如果一个点为 $R$，那么它的左上方确定了，且不能含有 $L$。如果一个点为 $L$，那么它的右下方确定了，且不能含有 $R$。

所以可以得出结论，当且仅当没有一个 $L$ 在 $R$ 的左上方时，存在合法的放置方法。

接下来就是数据结构的事了，方法有很多种，这里介绍线段树的做法。

我们根据横坐标建立线段树。

对于每个节点，维护 $(mi,ma,no)$ 分别表示 $L$ 的最小值，$R$ 的最大值，以及是否合法。

$mi,ma$ 可以直接转移。$no$ 可以根据左儿子的 $no$，右儿子的 $no$，以及左儿子 $mi$ 和右儿子 $ma$ 的大小关系确定。

最后还要在每行用 set 维护所有 $L$ 和 $R$。

复杂度 $O(n\log n)$。

code:

```cpp
#include<bits/stdc++.h>
#define ls (id*2)
#define rs (id*2+1)
using namespace std;
const int N=2e5+5;
int n,m,q;
set<int>L[N],R[N];
struct node{int l,r,mi,ma,no;}t[4*N];
void build(int id,int l,int r){
  t[id].l=l;t[id].r=r;t[id].mi=1e9;
  if(l==r)return;
  int mid=(l+r)>>1;build(ls,l,mid);build(rs,mid+1,r);
}
void pushup(int id){
  t[id].mi=min(t[ls].mi,t[rs].mi);t[id].ma=max(t[ls].ma,t[rs].ma);
  t[id].no=t[ls].no|t[rs].no|(t[ls].mi<=t[rs].ma);
}
void change(int id,int w,int mi,int ma){
  if(t[id].l==t[id].r){
    t[id].mi=mi;t[id].ma=ma;t[id].no=(t[id].mi<=t[id].ma);
    return;
  }
  int mid=(t[id].l+t[id].r)>>1;
  if(w<=mid)change(ls,w,mi,ma);
  else change(rs,w,mi,ma);
  pushup(id);
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m>>q;
  build(1,1,n);
  while(q--){
    int x,y,wx,wy;cin>>x>>y;wx=(x-1)/2+1;wy=(y-1)/2+1;
    if(x&1){
      if(L[wx].count(wy))L[wx].erase(wy);
      else L[wx].insert(wy);
    }else{
      if(R[wx].count(wy))R[wx].erase(wy);
      else R[wx].insert(wy);
    }
    int mi=1e9,ma=0;
    if(L[wx].size())mi=(*L[wx].begin());
    if(R[wx].size())ma=(*--R[wx].end());
    change(1,wx,mi,ma);
    if(t[1].no)cout<<"NO"<<endl;
    else cout<<"Yes"<<endl;
  }
  return 0;
}

```


---

