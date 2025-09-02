# Colored Cubes

## 题目描述

Vasya 通过了所有考试！出乎意料的是，Vasya 并不感到疲惫，反而已经准备好迎接新的挑战。然而，他并不想在难题上花费太多精力。

Vasya 想起了自己有一个不太难的谜题：在一个 $n \times n$ 的国际象棋棋盘上，放置着 $m$ 个有颜色的立方体。事实上，$m \leq n$，并且所有立方体的颜色都不同。每个立方体正好占据一个格子。此外，棋盘上为每个立方体都指定了一个目标格子，谜题的目标是将每个立方体移动到它的指定位置。立方体很脆弱，因此每次操作只能将一个立方体移动到它相邻的四个格子之一，并且目标格子必须是空的。Vasya 想要小心操作，因此每次操作恰好需要一秒钟。

Vasya 曾经为 VK Cup 决赛刻苦训练过，所以他最多能专注于这个谜题 $3$ 小时，也就是 $10800$ 秒。请帮助 Vasya 找到一组操作序列，使得所有立方体都被移动到它们的指定位置，并且 Vasya 不会失去注意力。

## 说明/提示

在第四个样例中，所给的移动序列（如下图所示）是合法的，但不是最短的方案。实际上存在只需 $3$ 步的解法。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1025E/705fb965c7c6d8d56f3f95db4ad4b3fd4732a6b5.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
1 1
2 2
```

### 输出

```
2
1 1 1 2
1 2 2 2
```

## 样例 #2

### 输入

```
2 2
1 1
2 2
1 2
2 1
```

### 输出

```
2
2 2 2 1
1 1 1 2
```

## 样例 #3

### 输入

```
2 2
2 1
2 2
2 2
2 1
```

### 输出

```
4
2 1 1 1
2 2 2 1
1 1 1 2
1 2 2 2
```

## 样例 #4

### 输入

```
4 3
2 2
2 3
3 3
3 2
2 2
2 3
```

### 输出

```
9
2 2 1 2
1 2 1 1
2 3 2 2
3 3 2 3
2 2 1 2
1 1 2 1
2 1 3 1
3 1 3 2
1 2 2 2
```

# 题解

## 作者：Sampson_YW (赞：2)

考虑枚举每个棋子，把它向所对应的终点按最短距离移动，重复做这操作直到所有棋子都在自己的位置上。

假如当前要向右移动，如果右边有棋子，那么尝试把这个棋子往上推或往下推。因为 $m\leq n$ 所以必然能空出来这个位置。其他方向同理。

直接做可能会在样例 3 类似的情况死循环，那么考虑每次随机一个排列，按排列的顺序做，如果一个棋子要移动到的那个位置上有已经在之前移动过的棋子就不移动了。然后每次把横纵坐标的顺序也随机一下。

毛估估一下操作次数大概是 $m\times (2n+2m) + 2\sum_{i=1}^{m}i=15100$ 次操作，但是很难卡满。在 cf 上只要 $4000$ 次左右就过了。

[code](https://www.luogu.com.cn/paste/gootqebn)

---

## 作者：9AC8E2 (赞：2)

构造题，考虑将棋子 $i$ 从初始位置移到 $(i,i)$,再移到最终位置即可。第二个过程与第一个本质相同，倒序输出即可。

考虑如何方便地将棋子 $i$ 从初始位置 $(x_i,y_i)$ 移到 $(i,i)$。

将棋子按 $x$ 排序，即可保证存在一种移动方式使得可以仅改变棋子的 $x$ 坐标就将其移动到 $x_i$ 行，下面给出证明。

>假设棋子 $i$ 在向下移给过程中碰到了 $j$,显然 $j$ 也是应该向下移的，那为什么不先移 $j$ 呢？

将所有棋子移到对应行后，$y$ 坐标即可随意变动。终止位置同理。

需要注意的是，移完之后同一个位置上的不一定是同一个棋子，毕竟两边排序的结果可能不同，再冒泡排序随便做一下就行。

次数限制很弱。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Ri register
#define log(a) cerr<<"[DEBUG] "<<#a<<'='<<(a)<<" at line "<<__LINE__<<endl
template<typename T>inline T read(Ri T&t)
{Ri T f=1;Ri char ch=getchar();t=0;
while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
while(ch>='0'&&ch<='9')t=t*10+ch-'0',ch=getchar();t*=f;return t;}
template<typename T,typename...Args>
inline void read(T&t,Args&...args)
{read(t);read(args...);}
const long long p=1e9+7;
inline long long power(Ri long long x,Ri long long k=p-2)
{Ri long long re=1;for(;k;k>>=1,x=x*x%p)if(k&1)re=re*x%p;return re;}
int n,m;
struct SOL
{
	int arr[55];
	int x[55],y[55];
	int v[55][55];
	vector<pair<int,int> >ans1,ans2;
	inline void print(int id,int X,int Y)//id->(X,Y)
	{
//		printf("point %d (%d,%d)->(%d,%d)\n",id,x[id],y[id],X,Y);
//		assert(X==x[id]||Y==y[id]);
		if(X!=x[id]&&Y!=y[id])exit(233);
		if(x[id]==X)
			while(y[id]!=Y)
			{
				int _y=y[id]+(y[id]>Y?-1:1);
				ans1.push_back({x[id],y[id]});
				ans2.push_back({x[id],_y});
				v[x[id]][y[id]]=0;
				y[id]=_y;
//				assert(v[x[id]][y[id]]==0);
				if(v[x[id]][y[id]])exit(114);
				v[x[id]][y[id]]=id;
			}
		else
			while(x[id]!=X)
			{
				int _x=x[id]+(x[id]>X?-1:1);
				ans1.push_back({x[id],y[id]});
				ans2.push_back({_x,y[id]});
				v[x[id]][y[id]]=0;
				x[id]=_x;
//				assert(v[x[id]][y[id]]==0);
				if(v[x[id]][y[id]])exit(514);
				v[x[id]][y[id]]=id;
			}
	}
	void Init()
	{
		for(int i=1;i<=m;i++)read(x[i],y[i]),v[x[i]][y[i]]=i;
		for(int i=1;i<=m;i++)arr[i]=i;
		sort(arr+1,arr+m+1,[&](int a,int b){return x[a]<x[b];});
		int cnt=1;
		while(cnt)
		{
			cnt=0;
			for(int i=1;i<=m;i++)
			{
				if(i==x[arr[i]])continue;
				bool flag=1;
				for(int X=x[arr[i]]+1;X<=i;X++)
					if(v[X][y[arr[i]]])
						flag=0;
				for(int X=i;X<=x[arr[i]]-1;X++)
					if(v[X][y[arr[i]]])
						flag=0;
				if(flag)
				{
					cnt++;
					print(arr[i],i,y[arr[i]]);
				}
			}
		}
		for(int i=1;i<=m;i++)
			print(arr[i],i,i);
	}
}a,b;
int pos[55];
int main()
{
	read(n,m);
	a.Init();
//	log("-------------------------------------\n");
	b.Init();
	vector<pair<int,int> >ans1,ans2;
	
	for(int i=1;i<=m;i++)pos[b.arr[i]]=i;
	for(int i=1;i<=m;i++)
		for(int j=2;j<=m;j++)
			if(pos[a.arr[j-1]]>pos[a.arr[j]])
				ans1.push_back({j-1,j-1}),
				ans2.push_back({j,j-1}),
				
				ans1.push_back({j,j}),
				ans2.push_back({j-1,j}),
				
				ans1.push_back({j,j-1}),
				ans2.push_back({j,j}),
				
				ans1.push_back({j-1,j}),
				ans2.push_back({j-1,j-1}),
				
				swap(a.arr[j-1],a.arr[j]),
				swap(a.v[j-1][j-1],a.v[j][j]);
	
//	log("----------------------------------------------\n");
//	for(int i=1;i<=m;i++)printf("%d %d\n",a.arr[i],b.arr[i]);
	reverse(b.ans1.begin(),b.ans1.end());
	reverse(b.ans2.begin(),b.ans2.end());
	printf("%d\n",ans1.size()+a.ans1.size()+b.ans1.size());
	for(int i=0;i<a.ans1.size();i++)printf("%d %d %d %d\n",a.ans1[i].first,a.ans1[i].second,a.ans2[i].first,a.ans2[i].second);
//	log("----------------------------------------------\n");
	for(int i=0;i<ans1.size();i++)printf("%d %d %d %d\n",ans1[i].first,ans1[i].second,ans2[i].first,ans2[i].second);
//	log("----------------------------------------------\n");
	for(int i=0;i<b.ans1.size();i++)printf("%d %d %d %d\n",b.ans2[i].first,b.ans2[i].second,b.ans1[i].first,b.ans1[i].second);
}
```


---

## 作者：SegTree (赞：1)

提供一个操作次数为 $3.5n^2$ 的做法。

考虑设计一个中间态，所有棋子都在第一行上，按照列顺序依次排序。则从一个中间态切换到另一个中间态只需要换到不同行在内部移动最后换回去即可。

于是转化成如何达到这样。如果随意按照一个顺序操作可能出现相撞的情况，考虑按行的顺序，对于每个极长向右的从右向左，反之从左向右即可。

---

## 作者：Yansuan_HCl (赞：1)

$m\le n$ 意味着我们可以把棋子放得比较均匀。具体地，一定存在很多方式，使每个棋子不同行不同列。

本题中，S $\to$ T 和 T $\to$ S 只需要反转操作序列即可。**从一个状态到另一个状态，考虑用中间状态转移。** 尝试从一个固定的起点出发，走到所有状态。尝试一些行不同、列不同的特殊状态：对角线。

对角线上可以 $O(m^2)$ 把所有棋子按行排序。排序完就可以直接移到对应列；同一列的棋子行有序，可以无交换地走到相应的位置。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define IC isdigit(c)
#define GC c=getchar()
void rd(auto &x) { x = 0; char GC; bool f = 0;
	for (; !IC; GC) f |= c == '-';
	for (; IC; GC) x = x * 10 + c - 48;
	if (f) x = -x;
}
void rd(auto &x, auto &...y) { rd(x); rd(y...); }
#define U(i,l,r) for (int i(l),END##i(r); i<=END##i; ++i)
#define D(i,l,r) for (int i(l),END##i(r); i>=END##i; --i)
using ll = long long;
 
const int N = 55;
using Pos = pair<int, int>;
using Stat = pair<Pos, Pos>;
 
int n, m;
void done(int c, vector<pair<int, int>> d, vector<Stat> &op) {
	if (d.empty()) return;
	vector<int> dif;
	for (auto [from, to] : d) {
		if (from < to)
			dif.push_back(1);
		else if (from == to)
			dif.push_back(0);
		else if (from > to)
			dif.push_back(-1);
	}
	U (i, 0, dif.size() - 1) {
		if (dif[i] == 0)
			continue;
		int j = i;
		while (j < dif.size() - 1 && dif[j + 1] == dif[i])
			++j;
		if (dif[i] == 1) {
			D (k, j, i) {
				for (int j = d[k].first; j < d[k].second; ++j)
					op.push_back({{j, c}, {j + 1, c}});
			}
		} else {
			U (k, i, j)
				for (int j = d[k].first; j > d[k].second; --j)
					op.push_back({{j, c}, {j - 1, c}});
		}
		i = j;
	}
}

vector<Stat> moveTo(vector<Pos> ter) {
	vector<Stat> op;
	vector<int> sa(m + 1);
	U (i, 1, m) sa[i] = i;
	sort(++sa.begin(), sa.end(), [&](int u, int v) {
		return ter[u].first < ter[v].first; });
	vector<int> rk(m + 1);
	U (i, 1, m)
		rk[sa[i]] = i;
	U (i, 1, m) {
		int toc = rk[i];
		for (int j = i; j < toc; ++j)
			op.push_back({{i, j}, {i, j + 1}});
		for (int j = i; j > toc; --j)
			op.push_back({{i, j}, {i, j - 1}});
	}
	U (i, 1, m) {
		int tor = rk[i];
		for (int c = i; c < tor; ++c)
			op.push_back({{c, rk[i]}, {c + 1, rk[i]}});
		for (int c = i; c > tor; --c)
			op.push_back({{c, rk[i]}, {c - 1, rk[i]}});
	}
	
	U (i, 1, m)
		rk[sa[i]] = i;
	U (i, 1, m) {
		int toc = ter[sa[i]].second, r = ter[sa[i]].second;
		for (int j = i; j < toc; ++j)
			op.push_back({{i, j}, {i, j + 1}});
		for (int j = i; j > toc; --j)
			op.push_back({{i, j}, {i, j - 1}});
	}
	
	vector<pair<int, int>> mov[N];
	U (i, 1, m) {
		int tor = ter[sa[i]].first, c = ter[sa[i]].second;
		mov[c].push_back({i, tor});
	}
	U (c, 1, n)
		done(c, mov[c], op);
		
	return op;
}
 
int main() {
//	freopen("1025E.in", "r", stdin);
//	freopen("1025E.out", "w", stdout);
	
	rd(n, m);
	vector<Stat> op1, op2;
	vector<Pos> pos1(1, {-1, -1}), pos2(1, {-1, -1});
	U (i, 1, m) {
		int r, c; rd(r, c);
		pos1.emplace_back(r, c);
	}
	U (i, 1, m) {
		int r, c; rd(r, c);
		pos2.emplace_back(r, c);
	}
	
	op1 = moveTo(pos1);
	op2 = moveTo(pos2);
	reverse(op1.begin(), op1.end());
	cout << (op1.size() + op2.size()) << endl;
	for (auto [y, x] : op1) {
		auto [a, b] = x;
		auto [c, d] = y;
		cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
	} 
	for (auto [x, y] : op2) {
		auto [a, b] = x;
		auto [c, d] = y;
		cout << a << ' ' << b << ' ' << c << ' ' << d << endl;
	}
}
```

---

## 作者：xxzx (赞：1)

[在我的博客查看](https://xxzx.moe/2023/09/23/cf1025e/)

### Solution

一个很有启发性的思路是，我们可以找到中间状态，然后问题就变成了两个子问题：由起点到中间态，由中间态到终点。

本题中，操作可逆，若我们选择将点移动到对角线上作为中间态，则问题变成两个完全相同的子问题。

考虑如何把若干对角线上的点移到目标点。

对角线有很好的性质，每个点可以任意上移下移或左移右移（但不能同时），而不会撞到别的点，其本质在于，这一行与列只有这一个点。在后续构造，我们继续使用这样的思想。

考虑这样的构造方法：

- 首先移动每个点的横坐标，使得移动后，任意两点的横坐标均不同，并且一个点它的终点横坐标越小，它目前的横坐标就越小。按终点横坐标排序一下，移动即可。

- 接着我们把每个点的纵坐标都移到与终点纵坐标相同，由于上述构造每个点横坐标不同，因此这一列只有这一个点，不会有点相撞。

- 最后，由于当前横坐标与终点横坐标相对大小相同，因此按当前横坐标顺序/逆序分两次依次调整每个点一定不会相撞。

移动步数远小于 $O(4nm+2n^2)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=60;
bool mem1;
int n,m,p[N],pos[N][N];
struct node {
    int x,y,ex,ey;
}nd[N];
vector<node> ans[2];
bool move(int op,int u,int dx,int dy) {
    int x=nd[u].x,y=nd[u].y;
    if(pos[x+dx][y+dy]) return false;
    pos[x][y]=0, pos[x+dx][y+dy]=1;
    ans[op].push_back({x,y,x+dx,y+dy});
    nd[u].x+=dx, nd[u].y+=dy;
    return true;
}
void sol(int op) {
    for(int i=1;i<=m;i++) p[i]=i;
    sort(p+1,p+m+1,[](const int &a,const int &b) { return nd[a].ex<nd[b].ex; });
    for(int i=1;i<=m;i++) {
        while(nd[p[i]].x<i&&move(op,p[i],1,0));
        while(nd[p[i]].x>i&&move(op,p[i],-1,0));
    }
    for(int i=1;i<=m;i++) {
        while(nd[i].y<nd[i].ey&&move(op,i,0,1));
        while(nd[i].y>nd[i].ey&&move(op,i,0,-1));
    }
    for(int i=1;i<=m;i++) {
        while(nd[p[i]].x<nd[p[i]].ex&&move(op,p[i],1,0));
        while(nd[p[i]].x>nd[p[i]].ex&&move(op,p[i],-1,0));
    }
    for(int i=m;i>=1;i--) {
        while(nd[p[i]].x<nd[p[i]].ex&&move(op,p[i],1,0));
        while(nd[p[i]].x>nd[p[i]].ex&&move(op,p[i],-1,0));
    }
}
void input(int op) {
    memset(pos,0,sizeof(pos));
    for(int i=1;i<=m;i++) cin>>nd[i].ex>>nd[i].ey, nd[i].x=nd[i].y=i, pos[i][i]=1;
    sol(op);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    input(0), input(1);
    cout<<ans[0].size()+ans[1].size()<<endl;
    reverse(ans[0].begin(),ans[0].end());
    for(auto i:ans[0]) cout<<i.ex<<" "<<i.ey<<" "<<i.x<<" "<<i.y<<endl;
    for(auto i:ans[1]) cout<<i.x<<" "<<i.y<<" "<<i.ex<<" "<<i.ey<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
```

---

