# Buses and People

## 题目描述

The main Bertown street is represented by a straight line. There are $ 10^{9} $ bus stops located on the line. The stops are numbered with integers from $ 1 $ to $ 10^{9} $ in the order in which they follow on the road. The city has $ n $ buses. Every day the $ i $ -th bus drives from stop number $ s_{i} $ to stop number $ f_{i} $ ( $ s_{i}< f_{i} $ ), it stops on all intermediate stops and returns only at night. The bus starts driving at time $ t_{i} $ and drives so fast that it finishes driving also at time $ t_{i} $ . The time $ t_{i} $ is different for all buses. The buses have infinite capacity.

Bertown has $ m $ citizens. Today the $ i $ -th person should get from stop number $ l_{i} $ to stop number $ r_{i} $ ( $ l_{i}< r_{i} $ ); the $ i $ -th citizen comes to his initial stop ( $ l_{i} $ ) at time $ b_{i} $ . Each person, on the one hand, wants to get to the destination point as quickly as possible, and on the other hand, definitely does not want to change the buses as he rides. More formally: the $ i $ -th person chooses bus $ j $ , with minimum time $ t_{j} $ , such that $ s_{j} \leq l_{i} $ , $ r_{i}\leq f_{j} $ and $ b_{i} \leq t_{j} $ .

Your task is to determine for each citizen whether he can ride to the destination point today and if he can, find the number of the bus on which the citizen will ride.

## 样例 #1

### 输入

```
4 3
1 10 10
5 6 2
6 7 3
5 7 4
5 7 1
1 2 1
1 10 11
```

### 输出

```
4 1 -1
```

## 样例 #2

### 输入

```
1 1
1 1000000000 1000000000
1 1000000000 1000000000
```

### 输出

```
1
```

# 题解

## 作者：Grisses (赞：5)

[题面](https://www.luogu.com.cn/problem/CF160E)

本题可以用离线线段树来做。首先，我们将所有车和人的左右端点和时间存储下来，再按照左端点排序，对时间离散化后线段树以时间点为节点进行维护在这一时间能到达的右端点的最大值。

对于排序后的车和人。如果它是车，我们就用线段树更新这辆车到达时间的右端点最值。如果他是人，就查询在这个人到达的时间到时间值域的最大值中**可以最早到达这个人的目的地的车的编号**。因为我们已经按左端点从小到大排序，所以目前我们存储在线段树中的所有车的时间都是在这个人之前或同时，又因为我们是以时间为节点，所以左子树一定优于右子树。然后输出查询的结果即可。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,p[200005],tot,Tot,ans[100005];
inline char gc(){static char buf[1000010],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;}
inline int read(){register int x=0;static char s=gc();while(s<'0'||s>'9')s=gc();while(s>='0'&&s<='9'){x=(x<<3)+(x<<1)+(s^48);s=gc();}return x;}
inline void write(int x){if(x>9)write(x/10);putchar(x%10^48);}//快读快写
struct ST{//线段树
	struct node{
		int l,r,m,op;//l是节点维护的左端点，r是右端点，m是区间的可到达右端点最大值
	}c[800005];//op是一个叶子节点维护的车的编号，如果c[i]不是叶子节点，op就是0
	void Build(int q,int l,int r){//建树
		c[q].l=l,c[q].r=r;//存储节点的左右端点
		if(l==r)return;//已是叶子节点，返回
		int mid=l+r>>1;
		Build(q<<1,l,mid);
		Build(q<<1|1,mid+1,r);//递归建树
	}
	void Add(int q,int x,int y,int id){//单点修改，id是这俩车的编号
		if(c[q].l==c[q].r){//到了叶子节点
			c[q].m=max(c[q].m,y);
			c[q].op=id;//更新op
			return;
		}
		int mid=c[q].l+c[q].r>>1;
		if(x<=mid)Add(q<<1,x,y,id);
		else Add(q<<1|1,x,y,id);//如果不是叶子节点，递归修改
		c[q].m=max(c[q<<1].m,c[q<<1|1].m);//修改节点维护的最大值
	}
	int Getsum(int q,int l,int r,int M){//区间查询，M是人要到达的地方
		if(c[q].m<M)return 0;//如果压根到不了，返回0
		if(c[q].l==c[q].r)return q;//找到一个符合的叶子节点，返回编号
		int a=0,b=0,mid=c[q].l+c[q].r>>1;//寻找答案
		if(l<=mid)a=Getsum(q<<1,l,r,M);//左子树优于右子树
		if(c[a].m>=M)return a;
		if(mid<r)b=Getsum(q<<1|1,l,r,M);
		if(c[b].m>=M)return b;
		return 0;//没有合适的答案，返回0
	}
}T;
map<int,int>M;
struct Node{
	int l,r,t,f,id;//f标记是人是车，id是在人/车里的编号
	bool operator<(const Node &m)const{
		return l<m.l;
	}
}a[200005];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[++tot].l=read(),a[tot].r=read(),a[tot].t=read(),p[tot]=a[tot].t,a[tot].id=i,a[tot].f=0;
	for(int i=1;i<=m;i++)a[++tot].l=read(),a[tot].r=read(),a[tot].t=read(),p[tot]=a[tot].t,a[tot].id=i,a[tot].f=1;
	stable_sort(a+1,a+tot+1);//车和人在其它条件相同时车要在前面
	sort(p+1,p+tot+1);
	for(int i=1;i<=tot;i++){
		if(p[i]!=p[i-1]){
			M[p[i]]=++Tot;
		}
	}//离散化
	T.Build(1,1,Tot);
	for(int i=1;i<=tot;i++){
		if(a[i].f==0)T.Add(1,M[a[i].t],a[i].r,a[i].id);
		else{
			int s=T.Getsum(1,M[a[i].t],Tot,a[i].r);
			ans[a[i].id]=T.c[s].op;//存储答案
		}
	}
	for(int i=1;i<=m;i++){
		if(ans[i])write(ans[i]),putchar(' ');
		else putchar('-'),putchar('1'),putchar(' ');//输出
	}
	return 0;
}
```

---

## 作者：jljljl (赞：2)

上面这位看成三维数点蒟蒻表示瑟瑟发抖
## 题意

已知n辆公交车，有 $s_i,f_i,t_i$ 三个属性，表示在 $t_i$ 时刻从 $s_i$ 到达 $f_i$，途中可以任意上下车。  
已知m个人，有 $l_i,r_i,b_i$ 三个属性，表示要在 $b_i$ 时刻及以后乘坐一辆公交车从 $l_i$ 到达 $r_i$。求 $t_i$ 最小的可行的公交车的编号。  
更正式的说法：求 $i$ 使得 $b \leq t_i \space and \space s \leq l_i \space and \space r \leq f_i$ 且 $t_i$ 最小，若没有则输出-1。

## 思路

首先把公交车和乘客都看作一个有时间的区间。合起来按照左端点排序，再线性扫描。  
注意左端点相同时乘客应在公交车之后。  
则扫到的乘客之前的公交车必然满足 $s_i \leq l_i$ 。  
若扫到公交车，则加入数据结构；若扫到乘客，则查询已经加入数据结构的公交车，在 $\ge b_i$ 的时间范围中，满足 $f_i \ge r_i$ 的最小的 $t_i$ 的id。

于是可以用线段树维护区间时间内 $f_i$ 的最大值。时间可能很大，可以离散化。  
查询时在 $f_i \ge r_i$ 的条件下寻找尽可能小的叶子节点即可。  


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100003
#define mid ((l + r) >> 1)
#define ln (nod << 1)
#define rn (nod << 1 | 1)
int n, m, ans[N], t[N << 1], val[N << 3];
struct A{
	int l, r, t, i;
	bool operator < (const A x) const { return l == x.l ? i < x.i : l < x.l; }
} a[N << 1];
void pushup(int nod) {
	if (a[val[ln]].r > a[val[rn]].r) val[nod] = val[ln];
	else val[nod] = val[rn];
}
void modify(int nod, int l, int r, int p, int vi) {
	// printf("m %d %d %d %d %d\n",nod,l,r,p,vi);
	if (l == r) {
		if (a[val[nod]].r < a[vi].r)
			val[nod] = vi;
		return;
	}
	if (p <= mid) modify(ln, l, mid, p, vi);
	else modify(rn, mid + 1, r, p, vi);
	pushup(nod);
}
int query(int nod, int l, int r, int p, int vi) {
	// printf("q %d %d %d %d %d (%d)\n",nod,l,r,p,vi,val[nod]);
	if (a[val[nod]].r < a[vi].r || t[r] < a[vi].t) return -1;
	if (l == r) return a[val[nod]].i;
	int lq = query(ln, l, mid, p, vi);
	if (lq != -1) return lq;
	return query(rn, mid + 1, r, p, vi);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n + m; ++i) {
		scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].t);
		a[i].i = i;
		t[i] = a[i].t;
	}
	sort(a + 1, a + n + m + 1);
	sort(t + 1, t + n + m + 1);
	// for(int i=1;i<=n+m;++i)printf("-%d %d %d (%d)\n",a[i].l,a[i].r,a[i].t,a[i].i);
	// for(int i=1;i<=n+m;++i){printf("%d ",t[i]);}puts("");
	for (int i = 1, pos; i <= n + m; ++i) {
		// printf("i = %d\n", a[i].i);
		pos = lower_bound(t + 1, t + n + m + 1, a[i].t) - t;
		if (a[i].i <= n) modify(1, 1, n + m, pos, i);
		else ans[a[i].i - n] = query(1, 1, n + m, pos, i);
	}
	for (int i = 1; i <= m; ++i) printf("%d ", ans[i]);
	return 0;
}

```

---

## 作者：Islauso (赞：1)

## 题目大意

给定 $n$ 个元素，每个元素有 $s_i,f_i,t_i$ 三个属性，再给定 $m$ 个元素，每个元素有 $l_j,r_j,b_j$ 三个属性，对于每一个 $j$ 求出满足 $s_i\le l_j$ 且 $f_i\ge r_j$ 且 $t_i\ge b_j$ 且 $t_i$ 最小的 $i$。

## Solution 1

根据题面，我们把前 $n$ 个元素称为公交车，后 $m$ 个元素称为人，同时为了方便，我们把 $t_i$ 和 $b_j$ 统称为时间，$s_i$ 和 $l_j$ 称为左端点，$f_i$ 和 $r_j$ 称为右端点。

### 思路

看到这道题首先想到的是三维偏序，继而可以想到直接 CDQ 分治搞过去，如果您不会 CDQ 分治，建议先把 Solution 2 看了，再去学习一下。

其实个人感觉这道题就是 CDQ 的板子题，这里提醒两点就够了，由于求的是最小的 $t_i$ 的编号，所以用树状数组存的应该是 $t_i$ 的最小值以及这个最小的 $t_i$ 的编号，还有就是在一开始根据时间排序的时候，如果有两个时间相同的，那么公交车应该排在人的前面，具体的可以看代码。

### 参考代码

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define pii pair<int,int>
#define mp make_pair
using namespace std;
const int N = 1e5 + 10, inf = 0x3f3f3f3f;
struct ALTXDY
{
	int tp, t, x, y, id;//tp 表示这是公交车还是人，t 是时间，x 是左端点，y 是右端点，id 是编号
	bool operator < (const ALTXDY &a) const
	{
		return t == a.t ? tp < a.tp : t > a.t;
	}
};
ALTXDY q[N<<1], tmp[N<<1];
int n, m, k, c[N<<2];//c 数组和 k 拿来对右端点离散化
pii tree[N<<1], ans[N];
void reset(int x)//cdq 时用来重置树状数组的
{
	for(; x <= k; x += lowbit(x))
		tree[x] = mp(inf, inf);
}
void update(int x, pii val)
{
	for(; x <= k; x += lowbit(x))
		tree[x] = min(tree[x], val);
}
pii query(int x)
{
	pii ans = mp(inf, inf);
	for(; x >= 1; x -= lowbit(x))
		ans = min(ans, tree[x]);
	return ans;
}
void cdq(int l, int r)
{
	if(l == r)
		return;
	int mid = (l+r)>>1;
	cdq(l, mid);
	cdq(mid+1, r);
	int i = l, j = mid+1, cnt = l-1;
	while(i <= mid && j <= r)
	{
		if(q[i].x <= q[j].x)
		{
			tmp[++cnt] = q[i];
			if(q[i].tp == 0)
				update(k-q[i].y+1, mp(q[i].t, q[i].id));
            	//由于公交车的右端点要大于人的右端点，但我不会树状数组求区间最值，所以把右端点取个反再加上 k 就变成了小于，也就是一般的树状数组写法
			i++;
		}
		else
		{
			tmp[++cnt] = q[j];
			if(q[j].tp == 1)
				ans[q[j].id] = min(ans[q[j].id], query(k-q[j].y+1));
			j++;
		}
	}
	while(i <= mid)
	{
		tmp[++cnt] = q[i];
		i++;
	}
	while(j <= r)
	{
		tmp[++cnt] = q[j];
		if(q[j].tp == 1)
			ans[q[j].id] = min(ans[q[j].id], query(k-q[j].y+1));
		j++;
	}
	for(int i = l; i <= r; i++)
		reset(k-q[i].y+1);
	for(int i = l; i <= r; i++)
		q[i] = tmp[i];
}
int main()
{
	memset(ans, inf, sizeof(ans));
	memset(tree, inf, sizeof(tree));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		int t, s, f;
		scanf("%d%d%d", &s, &f, &t);
		q[i]=(ALTXDY){0, t, s, f, i};//公交车 tp 为 0
		c[++k] = f;
	}
	for(int i = 1; i <= m; i++)
	{
		int b, l, r;
		scanf("%d%d%d", &l, &r, &b);
		q[i+n] = (ALTXDY){1, b, l, r, i};//人 tp 为 1
		c[++k] = r;
	}
	sort(c+1, c+1+k);
	k = unique(c+1, c+1+k)-c-1;
	for(int i = 1; i <= n+m; i++)
		q[i].y = lower_bound(c+1, c+1+k, q[i].y)-c;
	sort(q+1, q+1+n+m);
	cdq(1, n+m);
	for(int i = 1; i <= m; i++)
		if(ans[i].first == inf)
			printf("-1 ");
		else
			printf("%d ", ans[i].second);
	return 0;
}
```

时间复杂度 $O((n+m)\log^2(n+m))$，跑个 $1\times 10^5$ 问题不大。

## Solution 2

因为看见我这个代码是洛谷上的最劣解，去看了一下题解区，才发现原来有一个 $O((n+m)\log(n+m))$ 的做法。

### 思路

这道题用 CDQ 分治其实有点可惜，因为对于每一个人，我们要找的只是满足条件的最小的那个 $t_i$，至于其他的，我们根本不用考虑，这就有了第二种做法。

首先，我们根据**左端点**排个序，相同的还是公交车排在人的前面，然后我们从前往后扫一遍，如果遇到公交车，我们就以它的时间为下标，右端点和其编号为值塞到一棵线段树里，并维护右端点的最大值。

接下来是重点，如果遇到人，显然此时塞到线段树里的公交车的左端点都小于等于这个人，那么我们就在线段树上找一个叶子节点，满足这个叶子节点所代表的 $t_i$（也就是它这个位置所代表的下标）比这个人的时间大，并且它所存的右端点也比这个人的右端点大，而且这个叶子节点**尽量靠左**。

具体来说，我们在 $b_j$（也就是这个人的时间）到 $k$（此时 $k$ 用来离散化时间）这个区间里操作，对于当前节点 $i$，如果它的左儿子是合法的（即这个儿子是存在的，并且所代表的区间与 $[b_j,k]$ 有交集，并且这个儿子所代表的区间中的右端点的最大值比这个人的右端点大），那么我们就继续对这个儿子进行递归，如果它不合法，我们再判断右儿子是否合法，如果两个都不合法，那么就直接返回 $-1$，如果递归到了叶子节点，就说明这个叶子节点所代表的就是满足所有条件且 $t_i$ 最小的那一个公交车，直接返回它所存的编号即可。

为什么这样是对的呢？首先，对于节点 $i$，如果其左儿子是合法的，那我们一定不会去考虑它的右儿子，如果左儿子不合法，我们才会考虑右儿子，其次，如果某个节点所代表的区间中的最大值还没有要求值大，那它肯定是不合法的（~~其实个人感觉这很显然吧~~）。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO
{
	char buf[1<<22], *p1 = buf, *p2 = buf;
	#define getchar() (p1 == p2 && (p2 = (p1 = buf)+fread(buf, 1, 1<<21, stdin), p1==p2) ? EOF : *p1++)
	#define isdigit(c) (c >= 48 && c <= 57)
	#define isalpha(c) ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	template<typename T> inline void read(T &x)
	{
		x = 0;
		register char ch = getchar();
		while(!isdigit(ch))
			ch = getchar();
		while(isdigit(ch))
		{
			x = (x<<1)+(x<<3)+(ch^48);
			ch = getchar();
		}
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args)
	{
		read(t);read(args...);
	}
}
using namespace IO;
const int N = 1e5 + 10, inf = 0x3f3f3f3f;
struct ALTXDY
{
	int tp, t, x, y, id;
	bool operator < (ALTXDY const &a) const
	{
		return x == a.x ? tp < a.tp : x < a.x;
	}
};
ALTXDY q[N<<1];
int n, m, tot, bus[N], ans[N], c[N<<1], dat[N<<2], ls[N<<2], rs[N<<2];
void update(int &i, int l, int r, int x, int k)
{
	if(!i)
		i=++tot;
	if(bus[dat[i]] < bus[k])
		dat[i] = k;
	if(l == r)
		return;
	int mid = (l+r)>>1;
	if(x <= mid)
		update(ls[i], l, mid, x, k);
	else
		update(rs[i], mid+1, r, x, k);
}
int query(int i, int l, int r, int x, int y, int val)
{
	if(l == r)
		return dat[i];
	int mid = (l+r)>>1, t = -1;
	if(x <= mid && ls[i] && bus[dat[ls[i]]] >= val)
		t = query(ls[i], l, mid, x, y, val);
	if(t == -1 && y >= mid+1 && rs[i] && bus[dat[rs[i]]] >= val)
		t = query(rs[i], mid+1, r, x, y, val);
	return t;
}
int main()
{
	read(n, m);
	for(int i = 1; i <= n; i++)
	{
		int s, f, t;
		read(s, f, t);
		q[i] = (ALTXDY){0, t, s, f, i};
		c[i] = t;
		bus[i] = f;
	}
	for(int i = 1; i <= m; i++)
	{
		int b, l, r;
		read(l, r, b);
		q[i+n] = (ALTXDY){1, b, l, r, i};
		c[i+n] = b;
	}
	sort(c+1, c+1+n+m);
	register int k = unique(c+1, c+1+n+m)-c-1;
	for(int i = 1; i <= n+m; i++)
		q[i].t = lower_bound(c+1, c+1+k, q[i].t)-c;
	sort(q+1, q+1+n+m);
	register int rt = 0;
	for(int i = 1; i <= n+m; i++)
		if(q[i].tp == 0)
			update(rt, 1, k, q[i].t, q[i].id);
		else
			ans[q[i].id] = query(rt, 1, k, q[i].t, k, q[i].y);
	for(int i =1; i <= m; i++)
		printf("%d ", ans[i]);
	return 0;
}
```

因为常数不太优秀，加了一发 fread，又把原来的 pair 换了一下，最后 CF 上 rk4，洛谷上 rk1。

#### Update

今天机房里一个大佬对这个算法的时间复杂度提出了质疑，他认为根据一个节点的最大值来判断这个区间里有没有合法的解是不对的，原因如下。

![](https://cdn.jsdelivr.net/gh/xiao-lin52/image-upload/20210129114621.png)

考虑有这样一个节点 $u$（就是图中最上面的那个长方形），它包含了一部分要查询的这个区间（也就是图中的下面那条线段），而被这个节点包含的这部分区间中的值最大只有 $6$，但在这个节点代表的区间中还存在一个数，它不被包含在要查询的区间里，但它的值是 $7$，假设此时我们需要使找到的叶子结点的值大于等于 $7$，那么对于 $u$，我们就会查询失败，需要回溯以后重新查找，而那位大佬认为这个过程是可以卡掉的。

但是，实际上查找的过程还是 $O(\log n)$ 的！

为什么呢？我们考虑在什么情况下这个节点会查找失败，显然只有上面这一种情况，也就是一个节点只包含了一部分要查询的区间。

然后思考如果查询失败，我们会回到哪一个节点开始重新查找。

显然，对于这样一类节点 $u$，它的右儿子一定是被完全包含于要查询的区间内的，此时我们就可以通过它所存的最大值来判断它是否合法，而在这个右儿子的子树中一定不会存在和 $u$ 相同的情况，所以，如果右儿子合法，那我们就一定能找到一个合法的解，而如果右儿子不合法，那我们也无须再递归了，所以，我们最多只会出现一次查询失败的情况，最终时间复杂度还是 $O(\log n)$ 的。

顺便说一句，由于我们查找的这个区间的右端点总是和整棵线段树所代表的区间的右端点相同，所以在右端点并不会出现上述情况。

## 反思

CDQ 分治还是有点不太熟练，从写到 AC 花了三节课的时间，以后还是应该多练习一下。


---

## 作者：Coros_Trusds (赞：0)

$upd$ 已将所有 $and$ 更换为 $\operatorname{and}$。

# 题目大意

给定$t_i,s_i,f_i$ 和 $l_i,r_i, b_i$。

求 $i$ 使得 $b_i \leq t_i \space \operatorname{and} \space s_i \leq l_i \space \operatorname{and} \space r_i \leq f_i$ 且 $t_i$ 最小。

$1 \leq n,m \leq 10^5,1 \leq t_i,s_i,f_i \leq 10^9,1 \leq l_i,r_i,b_i \leq 10^9$。
# 题目分析

数据范围过大，我们先离散化。

把所有车和人的操作一起离线下来，按照左端点排序，如果左端点相等那么车在人前面，因为要尽可能的有 $s_i\le l_i$。排序后，如果当前是一辆车，那就加入线段树里。反之若是一个人，则在 **当前的** 线段树中找到大于等于 $r_i$ 的最小的 $f_i$。线段树的下标是 $t_i,b_i$，线段树维护 $f_i$ 的最大值。这样之前的排序保证了 $s_i\le l_i$，线段树查询时划定区间保证了 $b_i\le t_i$，线段树保证了 $r_i\le f_i$ 最小。

然后发现很板，注意一些细节即可。

注意代码最后要加 `fflush(stdout);`，否则会 $\verb!Idleness limit exceeded!$。

# 代码

```cpp
// Problem: CF160E Buses and People
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF160E
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Date:2022-06-29 22:29
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	#ifndef ONLINE_JUDGE
	#define getc getchar
	#endif
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getc();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getc();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getc();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 2e5 + 5;
struct Node {
	int id,l,r,t;
} node[N];
int b[N],ans[N];
int n,m;
struct Segment_Tree {
	struct Tree {
		int l,r;
		int Max,id;
	} tr[N << 2];
	#define lson (p << 1)
	#define rson (p << 1 | 1)
	inline void pushup(int p) {
		if (tr[p].Max < tr[lson].Max) tr[p].Max = tr[lson].Max,tr[p].id = tr[lson].id;
		if (tr[p].Max < tr[rson].Max) tr[p].Max = tr[rson].Max,tr[p].id = tr[rson].id;
	}
	inline void build(int p,int l,int r) {
		tr[p].l = l,tr[p].r = r;
		if (l == r) {
			tr[p].Max = tr[p].id = 0;
			return;
		}
		int mid = l + r >> 1;
		build(lson,l,mid),build(rson,mid + 1,r);
		pushup(p);
	}
	//查找第一个小于等于 k 的位置 
	inline int query(int x,int y,int p,int k) {
		if (tr[p].l == tr[p].r && tr[p].Max >= k) {
			return tr[p].id;
		}
		int mid = tr[p].l + tr[p].r >> 1;
		if (x <= mid && tr[lson].Max >= k) {
			int le = query(x,y,lson,k);
			if (le != -1) return le; 
		} 
		if (y > mid && tr[rson].Max >= k) {
			int ri = query(x,y,rson,k);
			if (ri != -1) return ri;
		}
		return -1;
	}
	inline void update(int x,int p,int k,int id) {
		if (tr[p].l == tr[p].r) {
			if (tr[p].Max < k) {
				tr[p].Max = k,tr[p].id = id;
			}
			return;
		}
		int mid = tr[p].l + tr[p].r >> 1;
		if (x <= mid) update(x,lson,k,id);
		else update(x,rson,k,id);
		pushup(p); 
	}
	#undef lson
	#undef rson
} seg;
int main(void) {
	n = read(),m = read();
	for (register int i = 1;i <= n + m; ++ i) {
		node[i].l = read(),node[i].r = read(),node[i].t = read();
		node[i].id = i,b[i] = node[i].t;
	}
	std::sort(node + 1,node + n + m + 1,[&](Node x,Node y)mutable {
		return x.l == y.l ? x.id < y.id : x.l < y.l;
	});
	std::sort(b + 1,b + n + m + 1);
	int num = std::unique(b + 1,b + n + m + 1) - b - 1;
	seg.build(1,1,num);
	for (register int i = 1;i <= n + m; ++ i) node[i].t = std::lower_bound(b + 1,b + num + 1,node[i].t) - b;
	for (register int i = 1;i <= n + m; ++ i) {
		if (node[i].id <= n) seg.update(node[i].t,1,node[i].r,node[i].id);
		else ans[node[i].id - n] = seg.query(node[i].t,num,1,node[i].r);
	}
	for (register int i = 1;i <= m; ++ i) printf("%d ",ans[i]);
	fflush(stdout);
	
	return 0;
}
```

---

## 作者：TulipeNoire (赞：0)

这道题的限制条件很多：$l,r,t\dots$ 所以我们要设法一个一个解决这些限制。容易知道，当我们以其中某一个为关键字将人和车排序过后就只剩下两个限制了。这里我是对右端点排序。

排完过后，我们就只用找合法的车的左端点（小于等于某个人的左端点）和合法的时间（大于等于某个人的时间）。我们发现时间可以二分。那我们就二分时间，因为这时我们需要找的是左端点的最小值。现在复杂度是 $O(n\log n)$，问题是如何维护。

最小值？单点修改？区间查询？可以 $O(\log n)$？不打线段树还打什么？那么我们就维护时间轴上（需离散化）的左端点最小值。将二分出来的 $t$ 值再对应到车的编号上，就OK了，复杂度 $O(n\log^2n)$，但肯定是跑不满的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,m,cnt,tim[N<<1],ans[N],enh,lft,idx[N<<1];
struct P{
	int t,l,r,id;
	int p;
}a[N<<1];
int val[N<<3];//线段树
bool cmp(P x,P y) {
	if (x.r>y.r) return false;
	if (x.r==y.r&&x.p>y.p) return false;//需要注意的是，如果人和车t值相等，需先考虑车
	return true;
}
inline void pushup(int p) {
	val[p]=min(val[p<<1],val[p<<1^1]);
	return;
}
void upd(int p,int l,int r,int x,int d) {
	if (l==r) {
		val[p]=min(val[p],d);
		return;
	}
	int mid=(l+r)>>1;
	if (x<=mid) upd(p<<1,l,mid,x,d);
	if (x>mid) upd(p<<1^1,mid+1,r,x,d);
	pushup(p);
	return;
}
int get(int p,int l,int r,int L,int R) {
	if (L<=l&&r<=R) return val[p];
	int mid=(l+r)>>1,res=2e9;
	if (L<=mid) res=min(res,get(p<<1,l,mid,L,R));
	if (R>mid) res=min(res,get(p<<1^1,mid+1,r,L,R));
	return res;
}
inline bool check(int x) {//二分合法的t
	return get(1,1,cnt,lft,x)<=enh;//区间查询
}
int binary_search(int l,int r) {
	if (l==r) return l;
	if (l==r-1) {
		if (check(l)) return l;
		return r;	
	}
	int mid=(l+r)>>1;
	if (check(mid)) return binary_search(l,mid);
	return binary_search(mid+1,r);
}
int main() {
	memset(val,127,sizeof val);
	scanf("%d %d",&n,&m);
	for (int i=1;i<=n;i++) {
		scanf("%d %d %d",&a[i].l,&a[i].r,&a[i].t);
		a[i].p=1, a[i].id=i;
		tim[++cnt]=a[i].t;
	}
	for (int i=n+1;i<=n+m;i++) {
		scanf("%d %d %d",&a[i].l,&a[i].r,&a[i].t);
		a[i].id=i-n;
		tim[++cnt]=a[i].t;
	}
	stable_sort(a+1,a+n+m+1,cmp);
	sort(tim+1,tim+cnt+1);//离散化
	for (int i=1;i<=n+m;i++) {
		a[i].t=lower_bound(tim+1,tim+cnt+1,a[i].t)-tim;//t值对应到编号
		if (a[i].p) idx[a[i].t]=a[i].id;
	}
	for (int i=n+m;i>=1;i--) {
		if (a[i].p) upd(1,1,cnt,a[i].t,a[i].l);//单点修改
		else {
			lft=a[i].t;
			enh=a[i].l;
			int k=binary_search(a[i].t,cnt+1);
			if (k>cnt) ans[a[i].id]=-1;
			else ans[a[i].id]=idx[k];//记录答案
		}
	}
	for (int i=1;i<=m;i++) {
		printf("%d ",ans[i]);
	}
	return 0;
}  
```

---

## 作者：_Felix (赞：0)

题意：

给定n辆公交车 $t_i$时间从$s_i$出发去$f_i$,

有m个人，$b_i$时间或之后从$l_i$去$r_i$

求每个人最早搭哪辆车。

即：对于每个人 求公交车$t_i$最小，且$t_i\ge b_i$,$l_i\ge s_i$,$f_i\le r_i$。


分析：

离散化时间。按照$l_i$排序，再按照公交->人 排序

按时间建立线段树。

按照排好序的将车插入线段树，线段树维护$f_i$的最大值。

查询时，查询$[1,b_i]$区间中满足$f_i\le r_i$的最小$t_i$

(按照顺序插入，保证了$l_i\ge s_i$)

再次体会到线段树的强大。

~~@jljljl 太强了 我看ta题解懂的。代码可能会相似。~~

```
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define rd(x) scanf("%d",&x)
typedef long long LL;
const int N=1e5+10,inf=0x3f3f3f3f;
int n,m,lsh[N<<1],ans[N],tr[N<<3]; 
struct pos{
	int t,l,r,tp,id;
}tmp[N<<1];
bool cmp(pos x,pos y){ return (x.l==y.l)?(x.tp>y.tp):(x.l<y.l); }
void pushup(int rt){ tr[rt]=(tmp[tr[rt<<1]].r>tmp[tr[rt<<1|1]].r)?tr[rt<<1]:tr[rt<<1|1]; }
void update(int rt,int l,int r,int x,int id){
	if(l==r){
		if(tmp[tr[rt]].r<tmp[id].r) tr[rt]=id; //维护最大r(以序号形式) 
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) update(rt<<1,l,mid,x,id);
	else update(rt<<1|1,mid+1,r,x,id);
	pushup(rt);
}
int query(int rt,int l,int r,int x,int id){
	if(tmp[tr[rt]].r<tmp[id].r||lsh[r]<tmp[id].t) return -1;
	//公交车的最大r还不如查询r 或者公交车的t小于查询t
	if(l==r) return tmp[tr[rt]].id;
	int mid=l+r>>1;
	int ret=query(rt<<1,l,mid,x,id);
	if(ret!=-1) return ret; 
	ret=query(rt<<1|1,mid+1,r,x,id);
	return ret;
}
int main(){
	rd(n);rd(m);
	rep(i,1,n){
		rd(tmp[i].l),rd(tmp[i].r),rd(tmp[i].t);
		tmp[i].tp=1,tmp[i].id=i;
		lsh[i]=tmp[i].t;
	}
	rep(i,1,m){
		rd(tmp[i+n].l),rd(tmp[i+n].r),rd(tmp[i+n].t);
		tmp[i+n].tp=0,tmp[i+n].id=i;
		lsh[i+n]=tmp[i+n].t;
	}
	
	sort(lsh+1,lsh+n+m+1);sort(tmp+1,tmp+n+m+1,cmp);
	int tot=unique(lsh+1,lsh+n+m+1)-lsh-1;
	
	for(int i=1;i<=n+m;i++){
		int nwt=lower_bound(lsh+1,lsh+tot+1,tmp[i].t)-lsh;
		if(tmp[i].tp) update(1,1,tot,nwt,i);
		else ans[tmp[i].id]=query(1,1,tot,nwt,i);
	}
	rep(i,1,m) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Kewth (赞：0)

  问题可以看做三维数点，直接做 3 个 log ，众所周知扫描线或者 cdq 分治可以通过离线干掉
一维做到两个 log ，但不在讨论范围内，因为有更优秀的做法。

  这个问题比较特殊，数点是数最小值，并且是数某一个维度的最小值，那么在该维度上使用扫描
线的同时可以贪心，具体的，按时间从小到大加入元素，如果扫描的是被询问的元素，那么在所有
当前被扫描到的另外两个维度满足条件的未确定答案的询问元素的答案就是当前扫描到这个元素。
用一个数据结结构维护所有未确定答案的询问元素，每扫描一个被询问元素就逐个查询满足条件的
询问元素确定答案并删除之，每扫描一个询问元素就加入这个数据结构。

  这个数据结构只关心另外两个维度，需要在二维空间中支持：

1. 查询一个矩形内的任意一个点（这个矩形实际上只确定一个端点和两个方向无限延伸的半平面）

2. 加入一个点

3. 删除查询的点

  乍一看还是要两个 log ，但事实上由于此时点没有任何权值标识，可以将一个维度用键值，另一
个维度用权值放在一个一维数据结构内维护起来，一颗普通的线段树就足以胜任。

  具体的，线段树的第 $x$ 个叶子节点维护的是第一维为 $x$ 的所有点，每个非叶子节点维护的
是第一维在对应键值区间内的所有点中第二维的最小值。这样查询的时候就只需要查询第一维对应
键值范围内是否有第二维满足条件的点即可。

另外由于一个叶子节点可能有多个点要维护点，需要另外用堆维护。

时间复杂度 $O((n+m)\log(n+m))$ ，其实好像也没卡两个 log 的做法。

参考实现：

```cpp
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 400005;
struct shit {
	int l, r, t, i, o;
} a[maxn << 1];
int ans[maxn];
int tmp[maxn];
par seg[maxn << 2], INF = par(1000000000, 1000000000);
std::set<par> set[maxn];

void insert (int now, int L, int R, int p, par x) {
	if (L == R) {
		set[p].insert(x);
		seg[now] = *set[p].begin();
		return;
	}
	int M = (L + R) >> 1;
	if (p <= M) insert(now << 1, L, M, p, x);
	else insert(now << 1 | 1, M + 1, R, p, x);
	seg[now] = std::min(seg[now << 1], seg[now << 1 | 1]);
}

void pop (int now, int L, int R, int p) {
	if (L == R) {
		set[p].erase(set[p].begin());
		seg[now] = *set[p].begin();
		return;
	}
	int M = (L + R) >> 1;
	if (p <= M) pop(now << 1, L, M, p);
	else pop(now << 1 | 1, M + 1, R, p);
	seg[now] = std::min(seg[now << 1], seg[now << 1 | 1]);
}

par query (int now, int L, int R, int l, int r) {
	if (r < L or l > R) return INF;
	if (l <= L and R <= r) return seg[now];
	int M = (L + R) >> 1;
	return std::min(query(now << 1, L, M, l, r),
			query(now << 1 | 1, M + 1, R, l, r));
}

void build (int now, int L, int R) {
	seg[now] = INF;
	if (L == R)
		return set[L].insert(INF), void();
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
}

int main () {
	int n = read, m = read, p = 0;
	for (int i = 1; i <= n; i ++) {
		a[++ p].o = 1;
		read(a[p].l, a[p].r, a[p].t);
		a[p].i = p;
	}
	for (int i = 1; i <= m; i ++) {
		a[++ p].o = 2;
		read(a[p].l, a[p].r, a[p].t);
		a[p].i = p;
	}

	int t = 0;
	for (int i = 1; i <= p; i ++) {
		tmp[++ t] = a[i].l;
		tmp[++ t] = a[i].r;
	}

	std::sort(tmp + 1, tmp + t + 1);
	for (int i = 1; i <= p; i ++) {
		a[i].l = int(std::lower_bound(tmp + 1, tmp + t + 1, a[i].l) - tmp);
		a[i].r = int(std::lower_bound(tmp + 1, tmp + t + 1, a[i].r) - tmp);
	}

	std::sort(a + 1, a + p + 1, [] (shit x, shit y) {
				return x.t == y.t ? x.o > y.o : x.t < y.t;
			});

	build(1, 1, t);

	for (int i = 1; i <= p; i ++) {
		if (a[i].o == 1) {
			par x = query(1, 1, t, a[i].l, a[i].r);
			while (x.first <= a[i].r) {
				int j = x.second;
				ans[a[j].i] = a[i].i;
				pop(1, 1, t, a[j].l);
				x = query(1, 1, t, a[i].l, a[i].r);
			}
		}
		if (a[i].o == 2)
			insert(1, 1, t, a[i].l, par(a[i].r, i));
	}

	for (int i = n + 1; i <= n + m; i ++)
		printf("%d ", ans[i] ? ans[i] : -1);
	puts("");
}
```

---

