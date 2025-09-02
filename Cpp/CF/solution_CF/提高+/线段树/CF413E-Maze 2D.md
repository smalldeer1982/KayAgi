# Maze 2D

## 题目描述

The last product of the R2 company in the 2D games' field is a new revolutionary algorithm of searching for the shortest path in a $ 2×n $ maze.

Imagine a maze that looks like a $ 2×n $ rectangle, divided into unit squares. Each unit square is either an empty cell or an obstacle. In one unit of time, a person can move from an empty cell of the maze to any side-adjacent empty cell. The shortest path problem is formulated as follows. Given two free maze cells, you need to determine the minimum time required to go from one cell to the other.

Unfortunately, the developed algorithm works well for only one request for finding the shortest path, in practice such requests occur quite often. You, as the chief R2 programmer, are commissioned to optimize the algorithm to find the shortest path. Write a program that will effectively respond to multiple requests to find the shortest path in a $ 2×n $ maze.

## 样例 #1

### 输入

```
4 7
.X..
...X
5 1
1 3
7 7
1 4
6 1
4 7
5 7
```

### 输出

```
1
4
0
5
2
2
2
```

## 样例 #2

### 输入

```
10 3
X...X..X..
..X...X..X
11 7
7 18
18 10
```

### 输出

```
9
-1
3
```

# 题解

## 作者：Miss_SGT (赞：16)

模拟赛该题我用倍增写，（没判负 $0$ 分），但不同于另外题解的写法

定义 $f_{i,j}$ 为第 $i$ 个格子走 $2^j$ 能到达的地方。

所谓“走”是怎么走呢，显然某一个点下一步不是唯一的。我限制一个点如果能往右走就往右走，否则往上或下走。这样为什么对呢？因为假如我们暴力走，会在每行走到底，再往上或下走（简单定理可以自己证明），倍增走是一样的。
现在确定了每一个 $i$ 的 $f_{i,0}$ 就可以以普通倍增方式求出所有 $f_{i,j}$ 了。
	
###   $f_{i,j}=f_{(f_{i,j-1}),j-1}$

最后，我们每次询问从大往小跳，只要不到 $v$，就跳。最后只要跳一步就行了。由于本题特殊，所以要判断是否最后一步是否跳到了 $v$ 的上或下边，如果是，答案加一。

然后我们就做完啦！

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,u,v,uy,vy;
char c[N<<1];
int to[N<<1][20],qa[N],ans;
inline int gety(int x){return (x>n?x-n:x);}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=2*n;i++){
    	cin >> c[i];
    	to[i][0]=-1;
    	if(i>n&&c[i-n]=='X'&&c[i]=='X') qa[i-n]=1;
		if(i>n) qa[i-n]+=qa[i-n-1];//前缀和判断是否存在竖着两个墙
	}	
	for(int i=1;i<=2*n;i++){
		if(c[i]=='X') continue;
		if(gety(i)<n&&c[i+1]!='X') to[i][0]=i+1;
		else if(i<=n){
			if(c[i+n]!='X') to[i][0]=i+n;
		}else{
			if(c[i-n]!='X') to[i][0]=i-n;
		}
	}
    for(int j=1;j<=19;j++)
    	for(int i=1;i<=2*n;i++){
    		if(to[i][j-1]!=-1) to[i][j]=to[to[i][j-1]][j-1];
    		else to[i][j]=-1;
		}
	while(m--){
		ans=0;
		scanf("%d%d",&u,&v);
		uy=gety(u),vy=gety(v);
		if(vy<uy) swap(u,v),swap(uy,vy);
		if(c[u]=='X'||c[v]=='X'||qa[vy]-qa[uy]){
			puts("-1");
			continue;
		}
		if(u==v){
			puts("0");
			continue;
		}
		if(uy==vy){
			puts("1");
			continue;
		}
		for(int j=19;j>=0&&u!=-1;j--){
			if(to[u][j]==-1) continue;
			if(gety(to[u][j])<vy) u=to[u][j],ans+=(1<<j);
		}
		if(u!=-1) u=to[u][0],++ans;
		if(u!=-1&&gety(u)==gety(v)){
			if(u!=v) ++ans;
			printf("%d\n",ans);
		}else puts("-1");
	}
	return 0;
}

```

### 注：不判 $-1$ 导致运行错误悔恨一生。

---

## 作者：⚡GG⚡ (赞：13)

### 温馨提醒:到[$QAQ$世界](https://www.cnblogs.com/Garbage-Only-one/p/11141878.html)食用更佳

竟然没人写题解?我来水一篇～～

其实感觉应该是$\colorbox{#3bb4f2}{\color{white}\text{提高+/省选-}}$的样子,233。

~~其实我没咕值子~~

先说说思路:

1. 维护一个[l,r]区间中四个角相互之间的最短路
1. 查询时用二分

思路出来了,算法也就出来了,那就是——**线段树**!

~~此处应有掌声~~

首先,我们知道线段树是二分维护区间值的。

然后,我们也知道线段树是二分查找值。

最后,我们发现这道题没有修改。

紧接着,我们开始写代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int mmp[3][200001];
#define INF 500000000
int n;
int ans;
char c[300001];
struct data{
	int d1,d2,d3,d4;			//四个最短路
};
struct tree{
    int l, r;
    data d;
}t[4*200001];					//线段树标准结构体
data merge(data a,data b)		//合并最短路
{
    data s;
    s.d1=min(INF,min(a.d1+b.d1,a.d2+b.d3)+1);
    s.d2=min(INF,min(a.d1+b.d2,a.d2+b.d4)+1);
    s.d3=min(INF,min(a.d3+b.d1,a.d4+b.d3)+1);
    s.d4=min(INF,min(a.d3+b.d2,a.d4+b.d4)+1);
    return s;
}
void init(int s,int l,int r)	//标准线段树构建
{
    t[s].l=l,t[s].r=r;
    if(l==r){
        t[s].d.d1=t[s].d.d2=t[s].d.d3=t[s].d.d4=INF;
        if(mmp[1][l]) t[s].d.d1=0;
        if(mmp[2][l]) t[s].d.d4=0;
        if(mmp[1][l]&&mmp[2][l]) t[s].d.d2=t[s].d.d3=1;
        return ;
    }
    int m=(l+r)/2;
    init(2*s,l,m);
    init(2*s+1,m+1,r);
    t[s].d=merge(t[2*s].d,t[2*s+1].d);
}
data q(int s,int x,int y)		//查询时的合并
{
    int l=t[s].l,r=t[s].r;
    if(x==l&&y==r) return t[s].d;
    int m=(l+r)/2;
    /*下面分类讨论不用讲了吧*/
    if(m>=y) return q(2*s,x,y);			//毒瘤呀,少写return
    else if(m<x) return q(2*s+1,x,y);	//毒瘤呀,少写return
    else
        return merge(q(2*s,x,m),q(2*s+1,m+1,y));
}
void ask(int x,int y)			//查询最短路
{
    int a=(x-1)%n+1,b=(y-1)%n+1;
    if(a>b){
        swap(x,y);
        swap(a,b);
    }
    data s=q(1,a,b);			//找到最短路
    /*根据情况返回四种路径的最短路*/
    if(x<=n&&y<=n) ans=s.d1;
    if(x<=n&&y>n) ans=s.d2;
    if(x>n&&y<=n) ans=s.d3;
    if(x>n&&y>n) ans=s.d4;
}
int main()						//请从这里开始阅读,这是一个好习惯
{
    int m;
    cin>>n>>m;
    int i,j;
    for(i=1;i<=2;i++)			//无脑O(2n)读入
    {
    	scanf("%s",c);
    	for(j=1;j<=n;j++)
    	   if(c[j-1]=='.') mmp[i][j]=1;
    }
    init(1,1,n);
    int x,y;
    for(i=1;i<=m;i++){			//无脑查询
        cin>>x>>y;
        ask(x,y);
        if(ans<INF) cout<<ans<<endl;
        else cout<<"-1\n";
    }
	return (0-0);				//无脑卖萌QAQ
}
```

**千万记得所有查询都要`return`!**

~~为没有出修改题的出题人喝彩!!!~~

---

## 作者：TernaryTree (赞：6)

看起来很可以用线段树。因为两个区间合并最短路是正确的，所有线段树是对的。对于一个区间 $[l,r]$ 维护左边到右边的四种最短路即可。pushup 是枚举一个中转点。很简单，没有 $2200$ 难度的。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid (l + r >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rt 1, 1, n

using namespace std;

const int maxn = 2e5 + 10;
const int inf = 1e9;

struct node {
	int uu, dd, ud, du;
	node() = default;
};

int n, q;
char s[3][maxn];
node tr[maxn << 2];

node pushup(node l, node r) {
	node u;
	u.uu = min(l.uu + r.uu + 1, l.ud + r.du + 1);
	u.dd = min(l.du + r.ud + 1, l.dd + r.dd + 1);
	u.ud = min(l.uu + r.ud + 1, l.ud + r.dd + 1);
	u.du = min(l.du + r.uu + 1, l.dd + r.du + 1);
	return u;
}

void build(int u, int l, int r) {
	if (l == r) {
		tr[u].uu = tr[u].dd = 0;
		tr[u].ud = tr[u].du = 1;
		if (s[1][l] == 'X') tr[u].uu = tr[u].ud = tr[u].du = inf;
		if (s[2][l] == 'X') tr[u].dd = tr[u].ud = tr[u].du = inf;
		return;
	}
	build(lc), build(rc);
	tr[u] = pushup(tr[ls], tr[rs]);
}

node query(int u, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return tr[u];
	node x, y;
	if (ql <= mid) x = query(lc, ql, qr);
	if (qr > mid) y = query(rc, ql, qr);
	if (ql <= mid && qr > mid) return pushup(x, y);
	if (ql <= mid) return x;
	if (qr > mid) return y;
}

void f(int x) {
	cout << (x >= inf ? -1 : x) << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> q >> (s[1] + 1) >> (s[2] + 1);
	build(rt);
	while (q--) {
		int u, v, l, r;
		cin >> u >> v, l = u, r = v;
		if (u > n) l = u - n;
		if (v > n) r = v - n;
		if (l > r) swap(l, r), swap(u, v);
		node ans = query(rt, l, r);
		if (u > n && v > n) f(ans.dd);
		else if (u > n) f(ans.du);
		else if (v > n) f(ans.ud);
		else f(ans.uu);
	}
	return 0;
}
```

---

## 作者：y_kx_b (赞：4)

~~为啥就我不会线段树啊啊啊。~~

模拟赛的时候使用了一种奇特的方法，但是因为 bfs 一个标记写挂了导致复杂度变成了指数，100pts $\to$ 25pts 并且因为忘记注释 debug 语句在本地没有 `-DONLINE_JUDGE` 的帮助下 25pts $\to$ 0pts。菜死了。

### Sol.

看样例想出了一种方法：从左边某一个点出发 bfs，记录源点到每个点的最短路 `dis`，然后查询的时候两个点的 `dis` 相减即可。因为可能有多个连通块所以要每个连通块都搜一次，记录每个点的连通块编号，询问的时候如果两个点不在同一个连通块直接输出 `-1`。这样可以完美过掉所有样例（甚至好像可以过掉前 ⑨ 个点）。

但是！考虑以下迷宫：（不得不吐槽样例甚至连这个玩意都没有……）

```
..
..
```
假设从左上角那个点开始 bfs（与从左下角开始是等价的），那么右上和左下角的格子都 $dis=1$ 相减得到 $0$ 了。这是一个格子能 bfs 到两个格子导致的。那么如果有障碍物呢？障碍物旁边的格子是不是就可以只能有一条出路，那么这个思路就正确了呢？
```
.....
..#..
```
考虑这个迷宫，$(1, 3)$ 这个点因为上面被堵住，所以只能一进一出，那么这时对于有一个点是 $(1, 3)$ 并且另一个点纵坐标 $\geqslant 3$ 的询问，两个 `dis` 相减是一定正确的。显然：从源点到第二个点的路径必定经过第一个点。

那怎么计算中间没有障碍物的点呢？直接输出哈密顿距离就行了。

然后我们猜结论猜出了另一个~~假~~算法：如果两个点之间有障碍物，输出两点 `dis` 之差，否则输出其哈密顿距离。

但是还是假了！还是上面第二个迷宫，考虑询问 $(2, 2)$ 和 $(1, 3)$，如果从左上 $(1, 1)$ 开始搜会使得这两个点 `dis` 均为 $2$。

那么怎么办呢？我们希望左边的那个点是上面或者下面被堵住的点（如上图的 $(1,3)$），然后右边就可以用上面的方法解决了。

具体的，假设询问的是 $(x_1, y_1) \to (x_2, y_2)\ (y_1\leqslant y_2)$，我们把有障碍物的每一列都记下来，然后二分第一个在 $y_1$ 右边的这种列。如果最后发现这一列在 $y_2$ 右边说明两点之间没有障碍，直接输出曼哈顿距离；否则设二分到的空位是 $(x_3, y_3)\ (y_1\leqslant y_3\leqslant y_2)$，先用曼哈顿距离计算 $(x_1, y_1) \to (x_3, y_3)$ 的距离，然后套用上面的 `dis` 相减结论计算 $(x_3, y_3) \to (x_2, y_2)$ 的距离，然后把两个距离相加即可。

完结撒花 qwq

[AC code.](https://codeforces.com/contest/413/submission/218761069)

---

## 作者：small_john (赞：4)

## 解题思路

由于只有两行，那么就将问题转换为列与列之间的关系。

考虑用线段树维护 $4$ 个值：

1. $d1$：这段区间的左上角到右上角的最短路；
2. $d2$：这段区间的左上角到右下角的最短路；
3. $d3$：这段区间的左下角到右上角的最短路；
4. $d4$：这段区间的左下角到右下角的最短路。

![](https://cdn.luogu.com.cn/upload/image_hosting/z5ckgy9t.png)

考虑维护 $k$ 节点，左儿子为 $ls$，右儿子为 $rs$，那么有：

- $d1_x=\min\{d1_{ls}+d1_{rs},d2_{ls}+d3_{rs}\}+1$；
- $d2_x=\min\{d1_{ls}+d2_{rs},d2_{ls}+d4_{rs}\}+1$；
- $d3_x=\min\{d4_{ls}+d3_{rs},d3_{ls}+d1_{rs}\}+1$；
- $d4_x=\min\{d4_{ls}+d4_{rs},d3_{ls}+d2_{rs}\}+1$。

然后对于每次询问，处理出两个点的列，在按照四个值的定义分类讨论输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls (k*2)
#define rs (k*2+1)
using namespace std;
const int N = 2e5+5,inf = 0x3f3f3f3f;
struct node{
	int d1,d2,d3,d4;
	void print()
	{
		cout<<d1<<' '<<d2<<' '<<d3<<' '<<d4<<'\n';
	}
	friend node operator + (node x,node y)
	{
		node res;
		res.d1 = min(inf,min(x.d1+y.d1,x.d2+y.d3)+1);
		res.d2 = min(inf,min(x.d1+y.d2,x.d2+y.d4)+1);
		res.d3 = min(inf,min(x.d4+y.d3,x.d3+y.d1)+1);
		res.d4 = min(inf,min(x.d4+y.d4,x.d3+y.d2)+1);
		return res;
	}
}s[N*4];
int n,m;
char a[2][N];
void pushup(int k)
{
	s[k] = s[ls]+s[rs];
}
void build(int k,int l,int r)
{
 	if(l==r)
	{
		s[k] = (node){inf,inf,inf,inf};
		if(a[0][l]=='.') s[k].d1 = 0;
		if(a[1][l]=='.') s[k].d4 = 0;
		if(a[0][l]=='.'&&a[1][l]=='.') s[k].d2 = s[k].d3 = 1;
		return;
	}
	int mid = (l+r)/2;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
node ask(int k,int l,int r,int x,int y)
{
	if(l>=x&&r<=y) return s[k];
	int mid = (l+r)/2;
	if(mid<x) return ask(rs,mid+1,r,x,y);
	if(mid>=y) return ask(ls,l,mid,x,y);
	return ask(ls,l,mid,x,y)+ask(rs,mid+1,r,x,y);
}
signed main()
{
//	freopen("family.in","r",stdin);
//	freopen("family.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>(a[0]+1)>>(a[1]+1);
	build(1,1,n);
	while(m--)
	{
		int u,v;
		cin>>u>>v;
		int x = u,y = v;
		if(x>n) x-=n;
		if(y>n) y-=n;
		if(x>y) swap(x,y),swap(u,v);
		auto now = ask(1,1,n,x,y);
		int ans;
		if(u<=n&&v<=n) ans = now.d1;
		if(u<=n&&v>n) ans = now.d2;
		if(u>n&&v<=n) ans = now.d3;
		if(u>n&&v>n) ans = now.d4;
		if(ans==inf) ans = -1;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：KILLER_AZ (赞：3)


# 这种题怎么可能没有线性做法呢？

# 题意

给一个 $2\times N$ 大小的矩形，里面有墙，用 `X` 表示，其他位置用 `.` 表示，$M$ 次询问求两点最短路，阻断输出 `-1`。  
其中每个点使用 $x\times n+y$ 表示，即范围 $[1, 2n]$。

# 思路

1. 首先划分出连通块。
2. 对每个连通块中的数字染色，具体是从左开始，一直向右扩展，颜色不变，当可以向上扩展时，从最左边开始扩展，颜色加一。
3. 大概的结果就是颜色之差加上距离之差。

但是有很多特殊情况需要特判和注意。

## 查询的两点的顺序

我写的是按照 $y$ 排序，事实证明这很对。

## 颜色的最后一段

```cpp
..X...X.
....X...
//染色结果如下
22022204
11110333
```

这里的染色结果会使得 $1,2$ 和 $8,14,15,16$ 的答案出错，原因是它不是该颜色 $2$ 的最后一段，所以加上特判拐弯，答案加 $2$。 

## 第一个点不在颜色最后一段，但是颜色相同

有两种情况，一是这两个点中间没有墙，二是有墙。后者可以直接使用上面的特判，前者只要用前缀和维护中间是否有墙即可。

## 两个点的颜色差为一

上面两种情况还是有缺陷，比如：

```cpp
.....
..X..
11111
22022
```

当两个点是 $6$ 和 $3$ 的时候就会出现问题，因为它属于特判一，答案会加 $2$，所以特判掉这种情况。发现这种情况颜色差必定为 $1$。

但是有一个反例：

```cpp
...X.
.X...
11103
20222
```

这个时候 $6$ 和 $5$ 色差仍为 $1$，但是答案要加 $2$，所以要特判掉颜色小的那个点是否位于最后一段。

# 献上私的丑陋代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define fore(i, l, r)        for (int i = (l); i <= (r); ++i)

const int MAXN = 200010;

int n, m;
int a[MAXN][2];
int col[MAXN][2];
bool last[MAXN][2];
int lstx, lsty;
bool nowlast;
int vis[MAXN][2];
int vn;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

bool check(int x, int y) { return a[x][y] != 1 && x <= n && y <= 1 && x >= 1 && y >= 0; }

struct Node
{
    int x, y, col;
};

// 对每个上下交替的.进行染色
//..x...x.
//....x...
// 22022204
// 11110333
void bfs(int x, int y)
{
    bool flag = true;
    ++vn;
    deque<Node> q;
    q.push_front(Node{x, y, 1});
    while (!q.empty())
    {
        int nx = q.front().x, ny = q.front().y, nc = q.front().col;
        if (nx == lstx && ny == lsty) last[nx][ny] = true;
        // 记录每个颜色最后的那一段，即last[][]=true
        q.pop_front();
        if (vis[nx][ny]) continue;
        vis[nx][ny] = vn;
        col[nx][ny] = nc;
        last[nx][ny] |= last[nx - 1][ny];
        if (check(nx + 1, ny)) q.push_front(Node{nx + 1, ny, nc});
        if (check(nx, !ny) && !vis[nx][!ny])
            q.push_back(Node{nx, !ny, nc + 1}), (flag && (lstx = nx, lsty = !ny)), flag = false;
        else flag = true;
    }
}

int pre[MAXN][2];

signed main()
{

    cin >> n >> m;
    char c;
    fore(i, 1, n) cin >> c, a[i][0] = (c == 'X');
    fore(i, 1, n) cin >> c, a[i][1] = (c == 'X');
    fore(i, 1, n) fore(j, 0, 1) pre[i][j] = pre[i - 1][j] + a[i][j];

    fore(i, 1, n)
    {
        lstx = i;
        if (!vis[i][0] && check(i, 0)) lsty = 0, bfs(i, 0);
        else if (!vis[i][1] && check(i, 1)) lsty = 1, bfs(i, 1);
    }
    fore(i, 1, m)
    {
        int x, y;
        cin >> x >> y;
        int x1, y1, x2, y2;
        x1 = (x - 1) % n + 1, y1 = (x - x1) / n, x2 = (y - 1) % n + 1, y2 = (y - x2) / n;
        if (vis[x1][y1] != vis[x2][y2]) cout << -1 << endl;
        else
        {
            // 特判启动
            if (x1 > x2) swap(x1, x2), swap(y1, y2);
            int ans = 0;
            if (!last[x1][y1]) ans = 2;
            if (col[x1][y1] == col[x2][y2] && (pre[x2][y2] - pre[x1][y1]) == 0) ans = 0;
            if (abs(col[x1][y1] - col[x2][y2]) == 1)
            {
                if (col[x1][y1] > col[x2][y2])
                    if (!last[x2][y2]) ans = 0;
                    else if (!last[x1][y1]) ans = 0;
            }
            // 特判结束
            cout << abs(col[x2][y2] - col[x1][y1]) + ans + x2 - x1 << endl;
        }
    }

    return 0;
}

// 刚好100行(
```

# 感谢

最后感谢 [OIdrearmer_Z](https://www.luogu.com.cn/user/479493) 和 [xieyikai2333](https://www.luogu.com.cn/user/380019) 提供的 hack 数据。


---

## 作者：registerGen (赞：3)

<https://www.luogu.com.cn/problem/CF413E>

翻译是我给的（逃

# Solution

线段树。

[这题](https://www.luogu.com.cn/problem/P4246) 的简化版。

线段树内维护四个值：每段区间左上到右上，左上到右下，左下到右上，左下到右下的最短路：

```cpp
struct Node
{
	int uu,ud,du,dd;
};
```

画个图就能得出 `pushUp`：

![](https://i.loli.net/2020/05/17/o2HOdPF5fV8ep4Q.png)

```cpp
#define CN const Node

inline Node pushUp(CN& x,CN& y)
{
	Node res;
	res.uu=std::min(inf,std::min(x.uu+y.uu,x.ud+y.du)+1);
	res.ud=std::min(inf,std::min(x.uu+y.ud,x.ud+y.dd)+1);
	res.du=std::min(inf,std::min(x.dd+y.du,x.du+y.uu)+1);
	res.dd=std::min(inf,std::min(x.dd+y.dd,x.du+y.ud)+1);
	return res;
}
```

查询的时候分类讨论判一判就行了。

具体细节见代码注释。

时间复杂度 $O(n\log n)$。

# Code

```cpp
#include<cstdio>
#include<algorithm>

#define CN const Node

const int N=2e5;
const int inf=0x3f3f3f3f;

struct Node
{
	int uu,ud,du,dd;
};

Node t[(N<<2)+10];
int n,m;
char s[N+10][2],tmp[N+10];

#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline Node pushUp(CN& x,CN& y)
{
	Node res;
	res.uu=std::min(inf,std::min(x.uu+y.uu,x.ud+y.du)+1);
	res.ud=std::min(inf,std::min(x.uu+y.ud,x.ud+y.dd)+1);
	res.du=std::min(inf,std::min(x.dd+y.du,x.du+y.uu)+1);
	res.dd=std::min(inf,std::min(x.dd+y.dd,x.du+y.ud)+1);
	return res;
}

void build(int i,int l,int r)
{
	if(l==r) // l = r 时，就是一个 2 × 1 的格子
	{
		t[i].uu=t[i].ud=t[i].du=t[i].dd=inf; // inf 表示不能走
		if(s[l][0]=='.')t[i].uu=0;
		if(s[l][1]=='.')t[i].dd=0;
		if(s[l][0]=='.'&&s[l][1]=='.')t[i].ud=t[i].du=1;
		return;
	}
	int mid=(l+r)>>1;
	build(ls(i),l,mid);
	build(rs(i),mid+1,r);
	t[i]=pushUp(t[ls(i)],t[rs(i)]);
}

Node query(int i,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)return t[i];
	int mid=(l+r)>>1;
	if(qr<=mid)return query(ls(i),l,mid,ql,qr);
	if(ql>mid) return query(rs(i),mid+1,r,ql,qr);
	return pushUp(query(ls(i),l,mid,ql,qr),query(rs(i),mid+1,r,ql,qr));
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=1;i++)
	{
		scanf("%s",tmp+1);
		for(int j=1;j<=n;j++)
			s[j][i]=tmp[j];
	}
	build(1,1,n);
	while(m--)
	{
		int u,v,a,b;
		scanf("%d%d",&u,&v);
		a=u,b=v;
		if(a>n)a-=n; // 找到 u 实际位于哪一列
		if(b>n)b-=n; // 同理
		if(a>b)std::swap(a,b),std::swap(u,v);
		Node res=query(1,1,n,a,b);
		int ans;
		if(u<=n&&v<=n)ans=res.uu; // u 在第一行，v 在第一行
		if(u<=n&&v>n) ans=res.ud; // u 在第一行，v 在第二行
		if(u>n&&v<=n) ans=res.du; // u 在第二行，v 在第一行
		if(u>n&&v>n)  ans=res.dd; // u 在第二行，v 在第二行
		printf("%d\n",ans<inf?ans:-1);
	}
	return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

两眼线段树题。

对于从第 $l$ 列走到第 $r$ 列，我们的出发、到达情况共有 $4$ 种，分别是：

- $l$ 列第 $1$ 行到 $r$ 列第 $1$ 行。
- $l$ 列第 $1$ 行到 $r$ 列第 $2$ 行。
- $l$ 列第 $2$ 行到 $r$ 列第 $1$ 行。
- $l$ 列第 $2$ 行到 $r$ 列第 $2$ 行。

这个很显然能用线段树来维护。我们令区间 $[l,r]$ 的第 $i$ 种情况下最短路长度为 $tr[now].w_i$（$now$ 是区间为 $[l,r]$ 对应线段树结构体的下标）。可以得到 `push_up` 函数：

```cpp
il void up(int now){
	tr[now].w1=min(tr[now<<1].w1+tr[now<<1|1].w1+work(1,tr[now<<1].r,1,tr[now<<1|1].l),tr[now<<1].w2+tr[now<<1|1].w3+work(2,tr[now<<1].r,2,tr[now<<1|1].l));
	tr[now].w2=min(tr[now<<1].w1+tr[now<<1|1].w2+work(1,tr[now<<1].r,1,tr[now<<1|1].l),tr[now<<1].w2+tr[now<<1|1].w4+work(2,tr[now<<1].r,2,tr[now<<1|1].l));
	tr[now].w3=min(tr[now<<1].w4+tr[now<<1|1].w3+work(2,tr[now<<1].r,2,tr[now<<1|1].l),tr[now<<1].w3+tr[now<<1|1].w1+work(1,tr[now<<1].r,1,tr[now<<1|1].l));
	tr[now].w4=min(tr[now<<1].w4+tr[now<<1|1].w4+work(2,tr[now<<1].r,2,tr[now<<1|1].l),tr[now<<1].w3+tr[now<<1|1].w2+work(1,tr[now<<1].r,1,tr[now<<1|1].l));
}
```

这里讨论每个大区间对应 $2$ 个子区间的情况就行了。例如 $tr[now].w_1$，有两种子区间的情况：

- 左子区间从左端点第 $1$ 行走到右端点第 $1$ 行，左子区间右端点第 $1$ 行走到右子区间左端点第 $1$ 行，右子区间左端点第 $1$ 行走到右子区间右端点第 $1$ 行。

- 左子区间从左端点第 $1$ 行走到右端点第 $2$ 行，左子区间右端点第 $2$ 行走到右子区间左端点第 $2$ 行，右子区间左端点第 $2$ 行走到右子区间右端点第 $1$ 行。

其实在中间跳区间的那一步也可以向左下、右上走，但步数明显更劣，故不考虑。

对于询问操作，如果当前的区间不完全被询问区间包括，则有 $3$ 种情况：

- 左右子区间都包含询问区间。

- 只有左子区间包含询问区间。

- 只有右子区间包含询问区间。

对于情况 $2,3$，我们直接返回递归值就行了。但对于情况 $1$，我们还需要将左右子区间的答案进行合并，也就是再执行一次 `push_up` 的操作。这样做的原因是我们跳了区间，且答案的分布不在同一个结构体。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define il inline
#define int long long

const int N=1e6+10,inf=1e9,M=1e6+10;
char ch[3][N];
int n=2,m,q;
struct node{
	int l,r,w1,w2,w3,w4;
	//w1:左上-右上 
	//w2:左上-右下
	//w3:左下-右上
	//w4:左下-右下 
}tr[M];

il int work(int ax,int ay,int bx,int by){
	char a=ch[ax][ay],b=ch[bx][by];
	if(a=='X'||b=='X') return inf;
	return 1;
}
il void up(int now){
	tr[now].w1=min(tr[now<<1].w1+tr[now<<1|1].w1+work(1,tr[now<<1].r,1,tr[now<<1|1].l),tr[now<<1].w2+tr[now<<1|1].w3+work(2,tr[now<<1].r,2,tr[now<<1|1].l));
	tr[now].w2=min(tr[now<<1].w1+tr[now<<1|1].w2+work(1,tr[now<<1].r,1,tr[now<<1|1].l),tr[now<<1].w2+tr[now<<1|1].w4+work(2,tr[now<<1].r,2,tr[now<<1|1].l));
	tr[now].w3=min(tr[now<<1].w4+tr[now<<1|1].w3+work(2,tr[now<<1].r,2,tr[now<<1|1].l),tr[now<<1].w3+tr[now<<1|1].w1+work(1,tr[now<<1].r,1,tr[now<<1|1].l));
	tr[now].w4=min(tr[now<<1].w4+tr[now<<1|1].w4+work(2,tr[now<<1].r,2,tr[now<<1|1].l),tr[now<<1].w3+tr[now<<1|1].w2+work(1,tr[now<<1].r,1,tr[now<<1|1].l));
	return ;
}
il node get(node a,node b,int l,int r){
	return 
	{	0,0,
		min(a.w1+b.w1+work(1,l,1,r),a.w2+b.w3+work(2,l,2,r)),
		min(a.w1+b.w2+work(1,l,1,r),a.w2+b.w4+work(2,l,2,r)),
		min(a.w4+b.w3+work(2,l,2,r),a.w3+b.w1+work(1,l,1,r)),
		min(a.w4+b.w4+work(2,l,2,r),a.w3+b.w2+work(1,l,1,r))
	};
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r){
		tr[now].w2=work(1,l,2,l),tr[now].w3=work(2,l,1,l);
		return ;
	}
	int mid=l+r>>1;
	build(now<<1,l,mid),build(now<<1|1,mid+1,r);
	up(now);
	return ; 
}
il node query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r)
		return {0,0,tr[now].w1,tr[now].w2,tr[now].w3,tr[now].w4};
	int mid=tr[now].l+tr[now].r>>1;
	int ans=inf;
	if(l<=mid&&mid<r)//两个区间都包含 
		return get(query(now<<1,l,r),query(now<<1|1,l,r),mid,mid+1);
	else if(l<=mid)//只在左区间
		return query(now<<1,l,r); 
	else if(mid<r)//只在右区间
		return query(now<<1|1,l,r); 
	return {-1,-1,-1,-1,-1,-1};
}

il void solve(){
	scanf("%lld%lld",&m,&q);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			cin>>ch[i][j];
	build(1,1,m);
	for(re int i=1,x,y;i<=q;++i){
		scanf("%lld%lld",&x,&y);
		int a=1,b=1;
		if(x>m) a=2,x-=m;
		if(y>m) b=2,y-=m;
		if(x>y) swap(x,y),swap(a,b);
		node now=query(1,x,y);
		int ans=0;
		if(a==1&&b==1) ans=now.w1;
		else if(a==1&&b==2) ans=now.w2;
		else if(a==2&&b==1) ans=now.w3;
		else ans=now.w4;
		if(ans>=inf) cout<<"-1\n";
		else cout<<ans<<"\n";
	}
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：Vanity_ (赞：1)

## 前言

居然只有一篇题解还是我同学的

~~赶紧水一波~~

## 需要知识

[线段树](https://pks-loving.blog.luogu.org/senior-data-structure-qian-tan-xian-duan-shu-segment-tree)
## 思路

~~乍一看居然想到了并查集~~

不过还是要走正常解法。

初看题目，用线段树做好像做不出。

仔细分析一下无非就是用线段树维护四个顶点的距离

没看懂的同学，我来分析一波。

设矩阵的左上角为L1左下角为L2右下角为R2右上角为R1

设

L1 TO R1 为d1

L2 TO R2为d2

L1 TO R2为d3

L2 TO R1为d4

所以我们只要线段树维护d1,d2,d3,d4便可
```cpp
struct node {
    int d1,d2,d3,d4;
}a[800001];
```

然后我们思考如何合并

设合并的两个矩阵为AB，合并后得到C由此可得

```cpp
c.d1=std::min(inf,std::min(a.d1+b.d1,a.d3+b.d4)+1);
c.d2=std::min(inf,std::min(a.d2+b.d2,a.d4+b.d3)+1);
c.d3=std::min(inf,std::min(a.d3+b.d2,a.d1+b.d3)+1);
c.d4=std::min(inf,std::min(a.d4+b.d1,a.d2+b.d4)+1);
```
没懂的同学可以手画一下图

就此可得出的代码


## 代码
个人码风不太好请见谅！
```cpp
#include <bits/stdc++.h>
#define inf 500000000
struct node
{
    int d1,d2,d3,d4;
}a[800001];
bool map[3][200001];
node add(node a,node b)
{
    node c;
    c.d1=std::min(inf,std::min(a.d1+b.d1,a.d3+b.d4)+1);
    c.d2=std::min(inf,std::min(a.d2+b.d2,a.d4+b.d3)+1);
    c.d3=std::min(inf,std::min(a.d3+b.d2,a.d1+b.d3)+1);
    c.d4=std::min(inf,std::min(a.d4+b.d1,a.d2+b.d4)+1);
    return c;
}
void build(int l,int r,int k)
{
    if(l==r)
    {
        a[k].d1=a[k].d2=a[k].d3=a[k].d4=inf;
        if(map[1][l]) a[k].d1=0;
        if(map[2][l]) a[k].d2=0;
        if(map[1][l]&&map[2][l]) a[k].d3=a[k].d4=1;
        return;
    }
    int mid=(l+r)/2;
    build(l,mid,k*2);
    build(mid+1,r,k*2+1);
    a[k]=add(a[k*2],a[k*2+1]);
    return;
}
node get(int L,int R,int l,int r,int k)
{
    if(L<=l&&R>=r)
        return a[k];
    int mid=(l+r)/2;
    node b,c;
    bool q1=0,q2=0;
    if(L<=mid) q1=1,b=get(L,R,l,mid,k*2);
    if(R>mid) q2=1,c=get(L,R,mid+1,r,k*2+1);
    if(q1&&!q2) return b;
    if(!q1&&q2) return c;
    if(q1&&q2) return add(b,c);
}
int main()
{
    int i,n,m,j,ans;
    char p;
    int xa,xb,ya,yb;
    node k;
    scanf("%d%d",&n,&m);
    for(i=1;i<=2;i++)
        for(j=1;j<=n;j++)
        {
            std::cin>>p;
            if(p=='.') map[i][j]=1;
        }
    build(1,n,1);
    for(i=1;i<=m;i++)
    {
        xa=1;xb=1;
        scanf("%d%d",&ya,&yb);
        if(ya>n) {ya-=n;xa=2;}
        if(yb>n) {yb-=n;xb=2;}
        if(ya>yb) {std::swap(xa,xb);std::swap(ya,yb);}
        k=get(ya,yb,1,n,1);
        if(xa==xb&&xa==1) ans=k.d1;
        else if(xa==xb&&xa==2) ans=k.d2;
        else if(xa>xb) ans=k.d4;
        else ans=k.d3;
        if(ans<inf) printf("%d\n",ans);
        else printf("-1\n");
    }
    return 0;
}
```

---

## 作者：7KByte (赞：0)

观察到这题并没有修改操作，所以我们可以用好写好想的倍增算法代替线段树。

定义 $f[0/1][i][j]$ 表示从第 $0/1$ 行的第 $i$ 列开始，向右移动 $2^j$ 列所花费的最小代价。定义 $g[0/1][i][j]$ 表示从第 $0/1$ 行的第 $i$ 列开始，向右移动 $2^j$ 列到达的最终位置是哪一行。

这样我们就可以倍增优化。

$$f[0/1][i][j]=f[0/1][i][j-1]+f[g[0/1][i][j-1]][i+2^{j-1}][j-1]$$
$$g[0/1][i][j]=g[g[0/1][i][j-1]][i+2^{j-1}][j-1]$$

这样就可以在 $\log N$ 的时间内回答询问。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,m,f[2][N][18],g[2][N][18],t,op[N];char s[2][N];
inline int calc(int x,int y){if(!x||!y)return 0;return x+y;}
int main(){

	scanf("%d%d",&n,&m);t=log2(n);
	scanf("%s%s",s[0]+1,s[1]+1);
	rep(i,1,n){
		if(s[0][i]=='X'&&s[1][i]=='X')op[i]=-1;
		else if(s[0][i]=='X')op[i]=0;
		else if(s[1][i]=='X')op[i]=1;
		else op[i]=2;
	}
	rep(i,1,n-1)if(~op[i]&&~op[i+1]&&(op[i]+op[i+1])!=1){
		rep(j,0,1)if(op[i]!=j){
			if(op[i+1]!=j)f[j][i][0]=1,g[j][i][0]=j;
			else f[j][i][0]=2,g[j][i][0]=j^1;
		}
	}
	rep(j,1,t)rep(i,1,n-(1<<j)){
		f[0][i][j]=calc(f[0][i][j-1],f[g[0][i][j-1]][i+(1<<(j-1))][j-1]);
		g[0][i][j]=g[g[0][i][j-1]][i+(1<<(j-1))][j-1];
		f[1][i][j]=calc(f[1][i][j-1],f[g[1][i][j-1]][i+(1<<(j-1))][j-1]);
		g[1][i][j]=g[g[1][i][j-1]][i+(1<<(j-1))][j-1];
	}
	rep(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		int u=(x-1)/n,v=(y-1)/n;
		if(x>n)x-=n;if(y>n)y-=n;
		if(x>y)swap(x,y),swap(u,v);
		int ans=1,res=y-x,cur=u;
		pre(j,t,0)if((res>>j)&1){
			ans=calc(ans,f[cur][x][j]);
			cur=g[cur][x][j];x+=1<<j;
		}
		if(!ans){puts("-1");continue;}
		printf("%d\n",ans-1+(cur!=v));
	}
	return 0;
}
```

---

## 作者：hfjh (赞：0)

# CF413E Maze 2D 题解

## 题意

给你一个 $2 \times n$ 的迷宫，有些格子可以走，有些不能走，求 $Q$ 组询问 $u\to v$ 最短路。

## 题解

倍增。

$f_{k,i,0/1,0/1}$ 表示 $i$ 向右走 $2^k$ 个走到 $i + 2^k$ 从第 1/2 行走到第 1/2 行。

转移:
枚举起点在 0/1。

终点在 0/1。

途径点在 0/1。
```cpp
for(int i = 0; i <= 1; ++i){
	for(int j = 0; j <= 1; ++j){
		for(int k = 0; k <= 1; ++k){
			c.f[i][j] = min(c.f[i][j], a.f[i][k] + b.f[k][j]);
		}
	}
}
```
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, inf = 1e9;
int n, Q, x, y, w1, w2;
char s1[N], s2[N];
struct node{
	int f[2][2];
	friend node operator +(const node a, const node b){
		node c;
		c.f[0][0] = c.f[0][1] = c.f[1][0] = c.f[1][1] = inf;
		for(int i = 0; i <= 1; ++i){
			for(int j = 0; j <= 1; ++j){
				for(int k = 0; k <= 1; ++k){
					c.f[i][j] = min(c.f[i][j], a.f[i][k] + b.f[k][j]);
				}
			}
		}

		return c;
	}
	void print(){
		cout<<f[0][0]<<' '<<f[0][1]<<' '<<f[1][0]<<' '<<f[1][1]<<'\n';	
	}
}f[20][N];
void input(){
	cin>> n >> Q;
	cin>> (s1 + 1) >> (s2 + 1);
}
void pre(){
	for(int i = 1; i <= n; ++i){
		f[0][i].f[1][0] = f[0][i].f[0][1] = 2;
		f[0][i].f[0][0] = f[0][i].f[1][1] = 1;
		if(s1[i] == 'X') f[0][i].f[0][1] = f[0][i].f[0][0] = inf;
		if(s2[i] == 'X') f[0][i].f[1][0] = f[0][i].f[1][1] = inf;
		if(s1[i + 1] == 'X') f[0][i].f[0][0] = f[0][i].f[1][0] = inf;
		if(s2[i + 1] == 'X') f[0][i].f[0][1] = f[0][i].f[1][1] = inf;
		if(s1[i] == 'X' && s2[i + 1] == 'X') f[0][i].f[1][0] = inf;
		if(s1[i + 1] == 'X' && s2[i] == 'X') f[0][i].f[0][1] = inf;
	}
	for(int k = 1; k <= 18; ++k){
		for(int i = 1; i <= n && i + (1 << (k - 1)) <= n; ++i){
			f[k][i] = f[k - 1][i] + f[k - 1][i + (1 << (k - 1))];
		}
	}
}
void op(){
	
	while(Q--){
		int flag = 0;
		w1 = w2 = 0;
		node now;
		cin >> x >> y;
		if(x > n) x -= n, w1 = 1;
		if(y > n) y -= n, w2 = 1;
		if(x > y) swap(x, y), swap(w1, w2);
		if(x == y){
			if(w1 == w2 ) cout<<0<<'\n';
			else if(s1[x] == 'X' || s2[x] == 'X') cout<<-1<<'\n';
			else if(w1 != w2) cout<<1<<'\n';
			else cout<<0<<'\n';
			continue;
		}
		for(int i = 18; i >= 0; --i){
			if(x + (1 << i) <= y){
				if(flag == 0) now = f[i][x], flag = 1;
				else now = now + f[i][x];
				x = x + (1 << i);
			}
		} 
		if(now.f[w1][w2] == inf) cout<<-1<<'\n';
		else cout<<now.f[w1][w2]<<'\n';
	}
}
int main(){
	freopen("family.in","r",stdin);
	freopen("family.out","w",stdout);
	input();
	pre();
	op();
}
```

---

## 作者：AlicX (赞：0)

## Solution

经过一些思考，发现加入对于一个区间 $(l,r)$，它的答案可以由 $(l,mid)$ 和 $(mid+1,r)$ 得来，所以考虑线段树。

因为原图的层数是 $2$ 层，不难想到 $u$ 和 $v$ 的摆放方式有 $4$ 种，也就是左上与右上，左上与右下，左下与右上，左下与右下。那么我们的线段树就维护这四个信息即可。注意在 `pushup` 的时候要与 $\infty$ 取最小值。然后询问的时候分情况讨论既可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second 
#define il inline 
#define db double
#define il inline 
#define low(x) x&-x 
#define pb(x) push_back(x) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1e6+10,INF=1e18+7; 
int n,m; 
char a[3][N]; 
struct Node{ 
	int l,r;  
	int w1,w2,w3,w4; 
}tr[N<<2]; 
struct Mind{ 
	bool operator<(Mind &Cyan)const{ } 
}; 
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il void work(Node& u,Node l,Node r){ 
	u.w1=min(INF,min(l.w1+r.w1,l.w2+r.w3)+1); 
	u.w2=min(INF,min(l.w1+r.w2,l.w2+r.w4)+1); 
	u.w3=min(INF,min(l.w3+r.w1,l.w4+r.w3)+1); 
	u.w4=min(INF,min(l.w4+r.w4,l.w3+r.w2)+1); 
} 
il void pushup(int u){ work(tr[u],tr[u<<1],tr[u<<1|1]); } 
il void build(int u,int l,int r){ 
	tr[u]={l,r}; 
	if(l==r){ 
		tr[u].w1=tr[u].w2=tr[u].w3=tr[u].w4=INF; 
		if(a[1][l]=='.') tr[u].w1=0; 
		if(a[2][l]=='.') tr[u].w4=0; 
		if(a[1][l]=='.'&&a[2][l]=='.') tr[u].w2=tr[u].w3=1; 
		return ; 
	} int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
	pushup(u); 
} 
il Node query(int u,int l,int r){ 
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u]; 
	int mid=tr[u].l+tr[u].r>>1; 
	if(r<=mid) return query(u<<1,l,r); 
	if(l>mid) return query(u<<1|1,l,r); 
	Node ans,L=query(u<<1,l,r),R=query(u<<1|1,l,r); 
	work(ans,L,R); return ans; 
} 
signed main(){ 
	n=read(),m=read(); 
	for(int i=1;i<=2;i++) for(int j=1;j<=n;j++) cin>>a[i][j]; 
	build(1,1,n); 
	while(m--){ 
		int u=read(),v=read(); 
		int l=(u-1)%n+1,r=(v-1)%n+1,ans=0; 	
		if(l>r) swap(l,r),swap(u,v); 
		Node res=query(1,l,r); 
		if(u<=n){ 
			if(v<=n) ans=res.w1; 
			else ans=res.w2; 
		} else{ 
			if(v<=n) ans=res.w3; 
			else ans=res.w4; 
		} printf("%lld\n",(ans==INF)?-1:ans); 
	} return 0;
} /* */ 
```


---

## 作者：Hadtsti (赞：0)

### 题意简述
有一个 $2\times n(1\le n\le 2\times 10^5)$ 的方格迷宫，有一些方格不能走。$m$ 次询问，每次询问迷宫中两个格子是否互相可达及其最短路长度。
### 题目分析
虽然没有修改，但是用线段树维护答案可能会更直观、清晰一些。

用线段树的每个结点维护第 $l\sim r$ 列这段 $2\times(r-l+1)$ 的方格左上到右上、左上到右下、左下到右上、左下到右下的最短路的值。实现时为了方便更新、计算，采用一个 $2\times2$ 的二维数组。

两个结点答案的合并也比较简单：对 $4$ 个最短路的值，只需要计算一下左结点对应起点经过中间的上行到右节点对应终点以及经过下行的答案取一个 $\min$ 即可。具体实现看代码。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;//最大值表示不可达 
int n,q,l,r,ans;
char op1[200010],op2[200010];
struct node
{
	int l,r;
	int mn[2][2];//两维分别是左和右，0 代表上，1 代表下。 
	friend node operator +(node a,node b)//合并 
	{
		node c;
		memset(c.mn,0x3f,sizeof c.mn);//初始化最大值 
		c.l=a.l,c.r=b.r;
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				for(int k=0;k<2;k++)//枚举中间是从哪行走 
					c.mn[i][j]=min(c.mn[i][j],a.mn[i][k]+b.mn[k][j]+1);	//答案取 min（注意从左结点到右结点时步数要再 +1）
		return c;
	}
}tr[800010];
void pushup(int p)
{
	tr[p]=tr[p<<1]+tr[p<<1|1];
}//左右子结点更新父节点 
void build(int p,int l,int r)
{
	tr[p].l=l,tr[p].r=r;
	if(l==r)
	{
		tr[p].mn[0][0]=(op1[l]=='.'?0:INF); 
		tr[p].mn[1][1]=(op2[l]=='.'?0:INF);//如果能走就是 0，否则不可达 
		tr[p].mn[0][1]=(op1[l]=='.'&&op2[l]=='.'?1:INF); 
		tr[p].mn[1][0]=(op1[l]=='.'&&op2[l]=='.'?1:INF);//如果能走就是 1，否则不可达 
		return;
	}
	int mid=l+r>>1;
	build(p<<1,l,mid);//建左子结点 
	build(p<<1|1,mid+1,r);//建右子结点 
	pushup(p);
}
node query(int p,int l,int r)//为了方便，直接返回整个结构体。 
{
	if(tr[p].l>=l&&tr[p].r<=r)
		return tr[p];//全覆盖就直接返回。 
	int mid=tr[p].l+tr[p].r>>1;
	if(mid<l)
		return query(p<<1|1,l,r);//只涉及右子结点 
	else if(mid>=r)
		return query(p<<1,l,r);//只涉及左子结点
	else
		return query(p<<1,l,r)+query(p<<1|1,l,r);//左右子结点都涉及，合并一下 
}
int main()
{
	scanf("%d%d%s%s",&n,&q,op1+1,op2+1);
	build(1,1,n);
	while(q--)
	{
		scanf("%d%d",&l,&r);
		if((l%n?l%n:n)>(r%n?r%n:n))//注意 n 在上行，2n 在下行 
			swap(l,r);
		printf("%d\n",(ans=query(1,(l%n?l%n:n),(r%n?r%n:n)).mn[(l-1)/n][(r-1)/n])==INF?-1:ans);//注意最大值是不可达，输出 -1 
	}
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：

本质上来讲是求一个 $n\times 2$ 区间上求一个四个端点之间的距离。这个信息可以直接通过拆成若干个部分进行合并，考虑使用线段树。

线段树上的每一个节点记录下当前的 $n\times 2$ 的区间上左上角，左下角分别到右上角，右下角的距离。每一次合并的时候，考虑左区间到中间的某一个位置进行中转之后再到右区间，一共有两种中转方式，都考虑一下就好了。

预处理的时候根据位置是否可走决定一个 $1\times 2$ 区间上的信息即可。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005,INF=1e9;
struct str{
	int d13,d14,d23,d24;
//	1 3
//	2 4
}t[MAXN<<2];
int n,q,m1[MAXN],m2[MAXN],x,y;
char c;
int MIN(int a,int b){return min(INF,min(a,b));}
str merge(str a,str b){//a-b
	str c={0};
	c.d13=MIN(a.d13+b.d13+1,a.d14+b.d23+1);
	c.d14=MIN(a.d13+b.d14+1,a.d14+b.d24+1);
	c.d23=MIN(a.d23+b.d13+1,a.d24+b.d23+1);
	c.d24=MIN(a.d23+b.d14+1,a.d24+b.d24+1);
	return c;
}
void build(int p,int l,int r){
	if(l==r){
		t[p].d13=0;t[p].d24=0;
		t[p].d14=1;t[p].d23=1;
		if(m1[l]==1)t[p].d13=t[p].d14=t[p].d23=INF;
		if(m2[l]==1)t[p].d24=t[p].d14=t[p].d23=INF;
		return;
	}
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	t[p]=merge(t[p<<1],t[p<<1|1]);
	return;
}
str query(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[p];
	int mid=(l+r)>>1;
	if(R<=mid)return query(p<<1,l,mid,L,R);
	if(L>mid)return query(p<<1|1,mid+1,r,L,R);
	return merge(query(p<<1,l,mid,L,R),query(p<<1|1,mid+1,r,L,R));
}
char get(){
	char c=getchar();
	while(c==' '||c=='\r'||c=='\n')c=getchar();
	return c;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){c=get();if(c=='.')m1[i]=0;else m1[i]=1;}
	for(int i=1;i<=n;i++){c=get();if(c=='.')m2[i]=0;else m2[i]=1;}
	build(1,1,n);
	for(int i=1;i<=q;i++){
		scanf("%d %d",&x,&y);
		if((x-1)%n+1>(y-1)%n+1)swap(x,y);
		str ans=query(1,1,n,(x-1)%n+1,(y-1)%n+1);
		if(x>n&&y>n)printf("%d\n",ans.d24==INF?-1:ans.d24);
		if(x<=n&&y<=n)printf("%d\n",ans.d13==INF?-1:ans.d13);
		if(x>n&&y<=n)printf("%d\n",ans.d23==INF?-1:ans.d23);
		if(x<=n&&y>n)printf("%d\n",ans.d14==INF?-1:ans.d14);
	}
	return 0;
}
```


---

