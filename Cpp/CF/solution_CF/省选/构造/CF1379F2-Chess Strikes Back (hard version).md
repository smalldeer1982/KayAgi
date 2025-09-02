# Chess Strikes Back (hard version)

## 题目描述

Note that the difference between easy and hard versions is that in hard version unavailable cells can become available again and in easy version can't. You can make hacks only if all versions are solved.

Ildar and Ivan are tired of chess, but they really like the chessboard, so they invented a new game. The field is a chessboard $ 2n \times 2m $ : it has $ 2n $ rows, $ 2m $ columns, and the cell in row $ i $ and column $ j $ is colored white if $ i+j $ is even, and is colored black otherwise.

The game proceeds as follows: Ildar marks some of the white cells of the chessboard as unavailable, and asks Ivan to place $ n \times m $ kings on the remaining white cells in such way, so that there are no kings attacking each other. A king can attack another king if they are located in the adjacent cells, sharing an edge or a corner.

Ildar would like to explore different combinations of cells. Initially all cells are marked as available, and then he has $ q $ queries. In each query he either marks a cell as unavailable, or marks the previously unavailable cell as available. After each query he would like to know whether it is possible to place the kings on the available cells in a desired way. Please help him!

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
3 2 10
4 2
6 4
1 3
4 2
6 4
2 2
2 4
1 3
4 4
3 1```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：王熙文 (赞：5)

居然想出了 2800 /cy

其实这道题就是一个简单的思维和数据结构题，感觉评不上 2800。

## 思路

首先，对于一个 $2 \times 2$ 的块里，一定会放且仅放一个国王，因为首先每个块最多放一个（否则会攻击），而因为一共只有 $n$ 个块，所以每个格子必须放。

现在考虑禁止一个块放国王会产生什么贡献。

如果禁止放的这个在块的右下角，则这个块的左上角一定放国王。此时这个块上面的块的右下角、左上角的块的右下角、左面的块的右下角都不能放了，而这些块就只能放左上角了。一直进行这样的操作，最终会使当前这个块左上角的那个矩形内的块都只能放左上角。

![](https://cdn.luogu.com.cn/upload/image_hosting/n71i2una.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

如上图，圆表示黑色格子，粗的线段画出了 $2 \times 2$ 的块。此时在 $(4,4)$ 处禁止放国王，则上面都确定了。

同理，如果禁止放的这个在块的左上角，则这个块右下的所有块都只能放右下角。

对于没有撤销操作，则只需对每个放的操作检查它覆盖的位置之前是否有不一样的覆盖。比如当前禁止了某个块的右下角，则它上面的位置如果有之前已经禁止了某个块的左上角，则产生冲突。

对于撤销操作，减去现在冲突的个数即可。

也就是说我们需要解决以下的问题：有若干个四元组 $(op_i,t_i,x_i,y_i)$，对于每个三元组求出来：

* 若 $op_i=1$，求满足 $op_j=2,t_j \le t_i, x_j\le x_i, y_j\le y_i$ 的 $j$ 的个数。

* 若 $op_i=2$，求满足 $op_j=1,t_j \le t_i, x_j \ge x_i,y_j \ge y_j$ 的 $j$ 的个数。

这显然是三维偏序，直接 cdq 分治即可。

## 参考代码

代码中的 ```op``` 与上文中的恰好相反。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,q;

int cnt=0;
struct CDQ
{
	int op,t,x,y,f;
} c[1000010];
bool cmp1(CDQ x,CDQ y)
{
	return x.t<y.t;
}
bool cmp2(CDQ x,CDQ y)
{
	return x.x==y.x?x.y<y.y:x.x<y.x;
}

int ans[1000010];

int tot=0,cl[10000010];

int tree[1000010];

void upd(int wz,int x)
{
	while(wz<=1e6+5)
	{
		cl[++tot]=wz;
		tree[wz]+=x;
		wz+=wz&-wz;
	}
}

int get_sum(int wz)
{
	int sum=0;
	while(wz)
	{
		sum+=tree[wz];
		wz-=wz&-wz;
	}
	return sum;
}

void clear()
{
	for(int i=1; i<=tot; ++i) tree[cl[i]]=0;
	tot=0;
}

void cdq(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(c+l,c+mid+1,cmp2),sort(c+mid+1,c+r+1,cmp2);
	int now=l;
	clear();
	for(int i=mid+1; i<=r; ++i)
	{
		while(now<=mid && c[now].x<=c[i].x)
		{
			if(c[now].op==1) upd(c[now].y,c[now].f);
			++now;
		}
		if(c[i].op==2)
		{
			ans[c[i].t]+=c[i].f*get_sum(c[i].y);
		}
	}
	clear();
	now=mid;
	for(int i=r; i>mid; --i)
	{
		while(now>=l && c[now].x>=c[i].x)
		{
			if(c[now].op==2) upd(c[now].y,c[now].f);
			--now;
		}
		if(c[i].op==1)
		{
			ans[c[i].t]+=c[i].f*(get_sum(1e6)-get_sum(c[i].y-1));
		}
	}
}

map<int,map<int,int> > vis;

int main()
{
	ios::sync_with_stdio(false),cin.tie(0);
	int n,m,q,x,y;
	cin>>n>>m>>q;
	for(int i=1; i<=q; ++i)
	{
		cin>>x>>y;
		int op=(x%2==1?1:2);
		if(!vis[x][y])
		{
			c[i]={op,i,x,y,1};
			vis[x][y]=1;
		}
		else
		{
			c[i]={op,i,x,y,-1};
			vis[x][y]=0;
		}
	}
	sort(c+1,c+q+1,cmp1);
	cdq(1,q);
	int sum=0;
	for(int i=1; i<=q; ++i)
	{
		sum+=ans[i];
		puts(sum?"NO":"YES");
	}
	return 0;
}
```

---

## 作者：yuzhechuan (赞：4)

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

## 作者：chenwenmo (赞：3)

### 题意
给定 $n$，$m$，为一个 $2n\times 2m$ 的棋盘，所有行号 $i$ 加列号 $j$ 为偶数的格子为白色格子。  
$q$ 组询问，每组询问 $(x,y)$，若之前未询问过，表示把该格子禁用，反之撤销禁用。  
一共要在白色格子中放 $n\times m$ 个棋子，且每个棋子周围八格不能有其他棋子。  
对于每组询问，判断当前是否有方案合法放置棋子，禁用的格子不能放。
### 思路
* 关键性质：将整个格子划分成 $n\times m$ 个 $2\times 2$ 的子结构，对于每个子结构，如果禁用右下角，那么以它为右下角的左上方整个矩形中的子结构都只能放左上角。禁用左上角，类似的，就是右下方整个矩形的子结构都只能放右下角。
![](https://cdn.luogu.com.cn/upload/image_hosting/cwpfskiv.png)
图中表示禁用子结构的右下角。绿色为可以放的，红色是禁用的，紫色小方格是子结构。禁用左上角同理。

可以看出，不合法的时候，当且仅当两种禁用方式产生的矩形出现交集。就是又必须放左上又必须放右下，矛盾了。

对于这种判断是否有交集的操作，可以维护左端点的最小值，右端点的最大值，而这题是二维的，那么就是左上矩形的最右下角，右下矩形的最左上角。  
然而它有删有增，直接维护两个变量肯定不行，考虑用一些数据结构。
![](https://cdn.luogu.com.cn/upload/image_hosting/qawd3v2r.png)
对于每一行，用 set 维护，然后对于每个 set，再放到线段树上就可以了。
### 代码

```cpp
const int N = 2e5 + 10;

typedef pair <int, int> pii; 
int n, m, q;
map <pii, int> mp;
set <int> ql[N << 1], qr[N << 1];

struct SegmentTree{
	int l, r, flag, mx, mn;//mx：这一段的所有set的最远的左上矩形中最远的
						   //mn：这一段的所有set的最近的右下矩形中最近的 
}t[N << 4];

void push_up(int x){
	t[x].mx = max(t[x << 1].mx, t[x << 1 | 1].mx);
	t[x].mn = min(t[x << 1].mn, t[x << 1 | 1].mn);
	t[x].flag = t[x << 1].flag || t[x << 1 | 1].flag || (t[x << 1 | 1].mx >= t[x << 1].mn);
	//flag：如果两个子段有一个不合法，或，左子段的右下矩形和右子段的左上有交集，那一整段都不合法 
}

void build(int x, int l, int r){
	t[x].l = l, t[x].r = r;
	if(l == r){
		t[x].mx = 0, t[x].mn = m + 1, t[x].flag = 0;
		return;
	}
	int mid = l + r >> 1;
	build(x << 1, l, mid);
	build(x << 1 | 1, mid + 1, r);
	push_up(x);
}

void update(int x, int pos){
	if(t[x].l == pos && t[x].r == pos){
		t[x].mx = ql[pos].size() ? (*ql[pos].rbegin()) : 0;
		t[x].mn = qr[pos].size() ? (*qr[pos].begin()) : m + 1;
		t[x].flag = (t[x].mx >= t[x].mn);
		return;
	}
	int mid = t[x].l + t[x].r >> 1;
	if(pos <= mid) update(x << 1, pos);
	else update(x << 1 | 1, pos);
	push_up(x);
}

void Solve(){
	cin >> n >> m >> q;
	build(1, 1, n);
	while(q--){
		int x, y;
		cin >> x >> y;
		x++, y++;
		if(mp[mk(x, y)] == 0){//禁用 
			if(y & 1){
				ql[x >> 1].insert(y >> 1);//禁用左上，只能放右下 
			}else{
				qr[x >> 1].insert(y >> 1);//禁用右下，只能放左上 
			}
		}else{//撤销 
			if(y & 1){
				ql[x >> 1].erase(y >> 1);//撤销左上 
			}else{
				qr[x >> 1].erase(y >> 1);//撤销右下 
			}
		}
		mp[mk(x, y)] ^= 1;
		update(1, x >> 1);
		if(t[1].flag) cout << "NO" << endl;
		else cout << "YES" << endl;
	}
}
```

---

## 作者：Exp10re (赞：2)

其实比起 F1 也没难多少……

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

对于删除操作，使用 map 来维护一个格子是否被删除，然后用 erase 维护即可。

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
map<long long,long long> tmap[MAXN*2];
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
		if(tmap[ta][tb])
		{
			if(ta%2==0)
			{
				L[ta/2].erase(L[ta/2].find(tb/2));
			}
			else
			{
				R[ta/2].erase(R[ta/2].find(tb/2));
			}
		}
		else
		{
			if(ta%2==0)
			{
				L[ta/2].insert(tb/2);
			}
			else
			{
				R[ta/2].insert(tb/2);
			}
		}
		tmap[ta][tb]^=1;
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

## 作者：Niko！ (赞：1)

打 div2 试了下从 F 开始开，然后ABF分数还没有ABC高/yun

考虑把棋盘分割为 $2 \times 2$ 的小块，显然一个小块中必须恰好选一个。

你发现，如果一个小块被钦定了不能选右下角的那个白点，就意味着左上角必须选。你发现它左边的，上面的和左上的小块的右下角都不能选，也都必须选左上角...以此类推，它到左上角的子矩形中的小块都必须选左上角。被钦定不能选左上角的小块也可以类似的得到：它到右下角的子矩形中的小块都必须选右下角。

称被钦定选取左上角的小块为红点，被钦定选取右下角的小块为蓝点，那么也就是：不能有一个红点在蓝点的右下角。

如果只有插入，可以建一棵线段树，支持区间取 max，单点查询来维护这个信息，如果同时还有删除，可以对上述做法线段树分治。

```cpp
//Author: Niko
#include <bits/stdc++.h>
#define maxn 200005
struct Evnt {
	int x,y,p;
}; Evnt event(int x1,int y1,int p1) { Evnt E;E.x=x1; E.y=y1;E.p=p1;return E;}
std::vector<Evnt>inc[maxn<<2];
int n,m,q,x,y,flag=0;
std::map<int,int>pre[3][maxn];
struct segmentTree_Max {
	int max[maxn<<2]={0},P[maxn*100],W[maxn*100],tl=0;
	void record(int x) { P[++tl] = x; W[tl] = max[x]; }
	void cancel() {
		max[P[tl]] = W[tl];
		tl--;
	} void back_to(int x) { while (tl>x) cancel(); }
	void modify(int l,int r,int L,int R,int v,int rt) {
		if(l>R||r<L)return;
		if(l<=L&&R<=r) { if (max[rt] < v) record(rt); max[rt] = std::max(max[rt],v); return ;}
		modify(l,r,L,(L+R)>>1,v,rt<<1);
		modify(l,r,((L+R)>>1)+1,R,v,rt<<1|1);
	} int query(int x,int l,int r,int rt) {
		if(l == r) { return max[rt]; }
		int mid = (l+r)>>1;
		if (x <= mid) return std::max(max[rt],query(x,l,mid,rt<<1));
		else return std::max(max[rt],query(x,mid+1,r,rt<<1|1));
	}
}R,B;
 
void insert(int l,int r,int L,int R,int x,int y,int p,int rt) {
//	if (L == 1 && R == q) { printf("add [%d %d] %d %d %d\n",l,r,x,y,p); }
	if (l>R||r<L) return;
	if (l<=L&&R<=r) { inc[rt].push_back(event(x,y,p)); return; }
	insert(l,r,L,(L+R)>>1,x,y,p,rt<<1);
	insert(l,r,((L+R)>>1)+1,R,x,y,p,rt<<1|1);
}
 
void dfs(int rt,int l,int r) {
	int preflag = flag, tl1 = R.tl, tl2 = B.tl;
//	printf("%d %d %d\n",rt,l,r);
	 if (!flag) {
		for (auto E:inc[rt]) {
			int x = E.x, y = E.y, p = E.p;
		//	printf("+ %d %d %d\n",x,y,p);
			if (p == 1) {
				R.modify(1,x,1,n,y,1);
				if (B.query(x,1,n,1) + y > m) flag = 1; 
			} else {
				B.modify(x,n,1,n,m-y+1,1);
				if (R.query(x,1,n,1) + (m-y+1) > m) flag = 1;
			}
		} //printf(">>%d\n",flag);
	}
	if (l == r) { if (!flag) puts("YES"); else puts("NO"); }
	else { dfs(rt<<1,l,(l+r)>>1); dfs(rt<<1|1,((l+r)>>1)+1,r); }
	flag = preflag;
	R.back_to(tl1); B.back_to(tl2);
}
	
 
int main() {
	scanf("%d%d%d",&n,&m,&q);
	for(int i = 1; i <=q ; ++ i) {
		scanf("%d%d",&x,&y);
		int x1 = (x+1)/2; int y1 = (y+1)/2;
		int p = 2-(1^(x%2));
		if (pre[p][x1][y1]) { 
			int l = pre[p][x1][y1], r = i-1;
			insert(l,r,1,q,x1,y1,p,1);
			pre[p][x1][y1] = 0;
		} else { pre[p][x1][y1] = i; }
	//	printf(">%d %d %d\n",x1,y1,p);
	} for (int i = 1; i <= 2; ++ i) {
		for(int j=1;j<=n;++j) 
		for (auto k:pre[i][j]) {
			int y = k.first; int l = k.second;
			if (l) insert(l,q,1,q,j,y,i,1);
		}
	}
	dfs(1,1,q);
	return 0;
}
```




---

## 作者：daniEl_lElE (赞：0)

注意到 $(2x-1,2y-1)$ 和 $(2x,2y)$ 不能同时选，总共有 $nm$ 组 $(2x-1,2y-1)$ 和 $(2x,2y)$，也就是说每组必须选至少一个。

考虑一个 $n\times m$ 的网格，每个位置有一个 $1$ 或 $2$ 的数，$1$ 表示这一组选择了 $(2x-1,2y-1)$，$2$ 表示这一组选择了 $(2x,2y)$。注意到对于一个格子 $(i,j)$，如果这个位置选择了 $1$，那么 $(i-1,j),(i,j-1),(i-1,j-1)$ 均不能选择 $2$，进而推出不存在 $(i_1,j_1),(i_2,j_2)$ 使得 $i_1\leq i_2,j_1\leq j_2$ 且 $(i_1,j_1)$ 位置选择 $2$，$(i_2,j_2)$ 位置选择 $1$。事实上，这是充要条件，充分性是很显然的。

于是问题转化为计数 $i_1\leq i_2,j_1\leq j_2$ 且 $(i_1,j_1)$ 位置需要选择 $2$，$(i_2,j_2)$ 位置需要选择 $1$ 的格子组数。动态二维偏序转静态三维偏序 CDQ 分治即可，总复杂度 $O(n\log^2n)$。

有点卡常，但是自然溢出啥事没有。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
map<pair<int,int>,int> mp;
struct node{
	int a,b,c,x,ans,tp;
}q[200005];
bool cmp1(node x,node y){
	return x.a<y.a;
}
bool cmp2(node x,node y){
	if(x.b==y.b) return x.tp>y.tp;
	return x.b<y.b;
}
bool cmp3(node x,node y){
	if(x.b==y.b) return x.tp<y.tp;
	return x.b>y.b;
}
struct sgt{
	int f[1000005];
	void rchange(int pos,int cg){
		while(pos<=200000){
			f[pos]+=cg;
			pos+=lowbit(pos);
		}
	}
	int rqry(int pos){
		int ans=0;
		while(pos){
			ans+=f[pos];
			pos-=lowbit(pos);
		}
		return ans;
	}
	void change(int i,int l,int r,int pos,int cg){
		rchange(pos,cg);
	}
	int qry(int i,int l,int r,int ql,int qr){
		return rqry(qr)-rqry(ql-1);
	}
}tree;
void solve1(int l,int r){
	if(l==r){
		return ;
	}
	solve1(l,mid),solve1(mid+1,r);
	sort(q+l,q+r+1,cmp2);
	for(int i=l;i<=r;i++){
		if(q[i].tp==2&&q[i].a<=mid) tree.change(1,1,200000,q[i].c,q[i].x);
		if(q[i].tp==1&&q[i].a>mid) q[i].ans+=tree.qry(1,1,200000,1,q[i].c);
	}
	for(int i=l;i<=r;i++) if(q[i].tp==2&&q[i].a<=mid) tree.change(1,1,200000,q[i].c,-q[i].x);
}
void solve2(int l,int r){
	if(l==r){
		return ;
	}
	solve2(l,mid),solve2(mid+1,r);
	sort(q+l,q+r+1,cmp3);
	for(int i=l;i<=r;i++){
		if(q[i].tp==1&&q[i].a<=mid) tree.change(1,1,200000,q[i].c,q[i].x);
		if(q[i].tp==2&&q[i].a>mid) q[i].ans+=tree.qry(1,1,200000,q[i].c,200000);
	}
	for(int i=l;i<=r;i++) if(q[i].tp==1&&q[i].a<=mid) tree.change(1,1,200000,q[i].c,-q[i].x);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n,m,qdeyaosi; cin>>n>>m>>qdeyaosi;
	for(int i=1;i<=qdeyaosi;i++){
		int x,y; cin>>x>>y;
		if(mp[make_pair(x,y)]){
			if(x&1) q[i].tp=2;
			else q[i].tp=1;
			q[i].x=-1;
			q[i].a=i;
			q[i].b=(x+1)/2,q[i].c=(y+1)/2;
		}
		else{
			if(x&1) q[i].tp=2;
			else q[i].tp=1;
			q[i].x=1;
			q[i].a=i;
			q[i].b=(x+1)/2,q[i].c=(y+1)/2;
		}
		mp[make_pair(x,y)]^=1;
	}
	solve1(1,qdeyaosi);
	sort(q+1,q+qdeyaosi+1,cmp1);
	solve2(1,qdeyaosi);
	sort(q+1,q+qdeyaosi+1,cmp1);
	int tot=0;
	for(int i=1;i<=qdeyaosi;i++){
		tot+=q[i].ans*q[i].x;
		if(tot==0) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

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

