# [ABC241F] Skate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc241/tasks/abc241_f

$ H $ 行 $ W $ 列のグリッド型のスケート場があります。上から $ i $ 行目、左から $ j $ 行目のマスを $ (i,j) $ で表します。

スケート場には $ N $ 個の障害物があり、$ i $ 個目の障害物は $ (X_i,Y_i) $ に置かれています。

高橋君は $ 1 $ 回の移動において、上下左右いずれかの方向を選んで、障害物に当たるまで進み続けます。  
 障害物に当たるとその $ 1 $ つ手前のマスで停止します。 なお、スケート場の周りは崖になっており、障害物に当たらないような移動は禁止とします。

高橋君ははじめ $ (s_x,s_y) $ にいて、何回か移動することで $ (g_x,g_y) $ で停止したいと考えています。

$ (g_x,g_y) $ へ辿り着くには最小で何回の移動が必要ですか？辿り着けないときはその旨を伝えてください。

## 说明/提示

### 制約

- $ 1\leq\ H\ \leq\ 10^9 $
- $ 1\leq\ W\ \leq\ 10^9 $
- $ 1\leq\ N\ \leq\ 10^5 $
- $ 1\leq\ s_x,g_x\leq\ H $
- $ 1\leq\ s_y,g_y\leq\ W $
- $ 1\leq\ X_i\ \leq\ H $
- $ 1\leq\ Y_i\ \leq\ W $
- $ (s_x,s_y)\neq\ (g_x,g_y) $
- $ (s_x,s_y)\neq\ (X_i,Y_i) $
- $ (g_x,g_y)\neq\ (X_i,Y_i) $
- $ i\neq\ j $ ならば、$ (X_i,Y_i)\neq\ (X_j,Y_j) $
- 入力は全て整数である

### Sample Explanation 1

!\[\](https://img.atcoder.jp/ghi/c376ca3813eb4c947eb605dea2d30454.png) 図は、$ (s_x,s_y) $ を `S` で、$ (g_x,g_y) $ を `G` で表しています。 $ (3,4)\rightarrow(2,4)\ \rightarrow(2,2)\ \rightarrow(5,2)\ \rightarrow(5,6) $ と移動すると、$ 4 $ 回の移動で $ (g_x,g_y) $ に辿り着くことができます。

### Sample Explanation 2

!\[\](https://img.atcoder.jp/ghi/07ab8a3e7c94525cd52704dd43e43b87.png) $ (g_x,g_y) $ で停止する必要があります。 通過しただけでは $ (g_x,g_y) $ へ辿り着いたとみなされないことに注意してください。

### Sample Explanation 3

!\[\](https://img.atcoder.jp/ghi/a423524262f4a075b94e2ab5f9e61164.png) 左を選んで進むと、高橋君は $ (g_x,g_y) $ を通過したのちに崖に落ちてしまいます。 スケート場の周りは崖になっており、障害物に当たらないような移動は禁止されていることに注意してください。

## 样例 #1

### 输入

```
7 8 7
3 4
5 6
1 4
2 1
2 8
4 5
5 7
6 2
6 6```

### 输出

```
4```

## 样例 #2

### 输入

```
4 6 2
3 2
3 5
4 5
2 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
1 10 1
1 5
1 1
1 7```

### 输出

```
-1```

# 题解

## 作者：卷王 (赞：4)

## 题目大意
[传送门](https://www.luogu.com.cn/problem/AT_abc241_f)

## 大体思路

这是一道比较基础的 bfs 题。

但是本题的 **移动** 是根据障碍物的位置而变化，所以我们只需要记录第 $i$ 行的障碍物的列值，和第 $i$ 列的障碍物的行值，用两个 map 数组存储即可，其余跟基本 bfs 没有太大区别，只需要 map 自带的函数 `lower_bound` 来查询当前方向上离现在的位置最近的障碍物即可。

翻了翻题解，代码都有点长，主要是移动方面写的很乱，我的应该比较好理解吧。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int h, w, n, sx, sy, fx, fy, ans = 0;
map<pr, int> dis; //范围大，要开 map
map<int, set<int> > row, col; //分别记录每一行的障碍物和每一列的障碍物
queue<pr> q; //bfs 用的队列

inline void add(int x, int y, int dist) {
	if (dis.find(pr(x, y)) == dis.end()) { //判重
		dis[pr(x, y)] = dist;
		q.push(pr(x, y));
	}
}

signed main() {
	h = read(), w = read(), n = read(), sx = read(), sy = read(), fx = read(), fy = read();
	up(i, 1, n) {
		int x = read(), y = read();
		row[x].insert(y), col[y].insert(x);
	}
	q.push(pr(sx, sy));
	dis[pr(sx, sy)] = 0;
	while (!q.empty()) {
		pr u = q.front();
		q.pop();
		int ux = u.first, uy = u.second;
		int dist = dis[pr(ux, uy)];
		if (ux == fx && uy == fy) {
			cout << dist;
			return 0;
		}
		auto it = row[ux].lower_bound(uy); //二分查询
		if (it != row[ux].end()) add(ux, *it - 1, dist + 1); //如果找到了
		if (it != row[ux].begin()) add(ux, *(--it) + 1, dist + 1);
		it = col[uy].lower_bound(ux);
		if (it != col[uy].end()) add(*it - 1, uy, dist + 1);
		if (it != col[uy].begin()) add(*(--it) + 1, uy, dist + 1);
	}
	cout << -1;
	return 0;
}
```

---

## 作者：Mikran (赞：3)

# 题意

有人滑冰，他会往一个方向一直滑动直到碰见障碍物，碰见障碍物后他就可以转弯继续滑，问从 $ (S_x,S_y)$ 到 $ (G_x,G_y) $ 的最小滑动数。

# 思路

考虑用 bfs，直接做肯定会 TLE，那么就二分出能碰到的石头。

# 做法

把障碍物分别按照横坐标和纵坐标为关键字排序，在 bfs 时可以直接二分出能碰到哪个石头。

# Code
 
```cpp
#include<bits/stdc++.h>
#define int long long
#define mkp make_pair
using namespace std;
const int N=2e5+11,inf=1e9;
struct node{
	int x,y,dis;
};
queue<node>q;
map<pair<int,int>,bool>vis;
pair<int,int>X[N],Y[N];
int h,w,n;
int sx,sy,tx,ty;
signed main(){
	cin>>h>>w>>n;
	cin>>sx>>sy>>tx>>ty;
	q.push((node){sx,sy,0});
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		X[i]=mkp(x,y);//以横坐标为关键字
		Y[i]=mkp(y,x);//以纵坐标为关键字
	}
   //排序
	sort(X+1,X+n+1);
	sort(Y+1,Y+n+1);
	while(!q.empty()){
		node u=q.front();
		q.pop();
		int x=u.x,y=u.y;
		if(vis[mkp(x,y)])continue;
		vis[mkp(x,y)]=1;
		if(x==tx&&y==ty){
			cout<<u.dis;
			return 0;
		}
		auto it=lower_bound(X+1,X+n+1,mkp(x,y));//二分出横坐标的障碍物
		int dx=it->first,dy=it->second;
		if(dx==x&&dy-1!=y/*判断是否已经在这个点*/)q.push((node){dx,dy-1,u.dis+1});//往上面的障碍物走
		it--;
		dx=it->first,dy=it->second;
		if(dx==x&&dy+1!=y)q.push((node){dx,dy+1,u.dis+1});//往下面的障碍物走
		it=lower_bound(Y+1,Y+n+1,mkp(y,x));//同理
		dx=it->second,dy=it->first;
		if(dx-1!=x&&dy==y)q.push((node){dx-1,dy,u.dis+1});
		it--;
		dx=it->second,dy=it->first;
		if(dx+1!=x&&dy==y)q.push((node){dx+1,dy,u.dis+1});
	}
	cout<<-1;
	return 0;
}

```

---

## 作者：joe_zxq (赞：2)

# Part 1 题面翻译

高桥来到了一个 $H \times W$ 的溜冰场，场上有 $N$ 个障碍物，第 $i$ 个障碍物的位置是 $(X_i,Y_i)$，高桥想从 $ (s_x,s_y)$ 出发，走到 $(g_x,g_y)$。

高桥每一步可以从上、下、左、右四个方向中选择一个，一直移动，直到碰到障碍物为止，他会停在障碍物之前的格子上。由于溜冰场四周都是悬崖峭壁，因此他不能向一个没有障碍物的方向移动。

输出最少的移动步数，若不能到达目标点，输出 `-1`。（必须正好停在目标点上，经过目标点没停下不算到达）

- $ 1\leq\ H,W\ \leq\ 10^9 $
- $ 1\leq\ N\ \leq\ 10^5 $
- $ 1\leq\ s_x,g_x\leq\ H $
- $ 1\leq\ s_y,g_y\leq\ W $
- $ 1\leq\ X_i\ \leq\ H $
- $ 1\leq\ Y_i\ \leq\ W $
- $ (s_x,s_y)\neq\ (g_x,g_y) $
- $ (s_x,s_y)\neq\ (X_i,Y_i) $
- $ (g_x,g_y)\neq\ (X_i,Y_i) $

# Part 2 解法思路

这道题求最优解，一看就知道是 BFS。

然而溜冰场很大，若是一步步地挪去找障碍显然会 TLE 到到飞起。

于是我们可以用 set 记录下每一行和每一列 分别有哪些障碍，这样向四个方向移动是就可以直接二分出该方向最近的障碍即可，可以使用 lower_bound。这就是为什么题目里说“必须正好停在目标点上，经过目标点没停下不算到达”了。

记录每一行和每一列分别有哪些障碍和从起点到各个点的距离等数据时，若是直接用数组存，显然直接 MLE 炸掉。我们可以用 map 代替数组存数据。

这道题看似是 BFS 模板题，其实也教会我们要学习使用 STL 帮助算法的实现。

# Part 3 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll h, w, n, sx, sy, ex, ey;
map<ll, set<ll> > x, y;
map<pair<ll, ll>, ll> d;
queue<pair<ll, ll> > q;

int main() {

	cin >> h >> w >> n >> sx >> sy >> ex >> ey;
	for (ll i = 1; i <= n; i++) {
		ll u, v;
		cin >> u >> v;
		x[u].insert(v);
		y[v].insert(u);
	}
	
	q.push({sx, sy});
	d[{sx, sy}] = 0;
	
	while (!q.empty()) {
		ll u = q.front().first, v = q.front().second;
		q.pop();
		if (u == ex && v == ey) {
			cout << d[{u, v}];
			return 0;
		}
		auto it = x[u].lower_bound(v);
		if (it != x[u].begin()) {
			if (d.find({u, *prev(it) + 1}) == d.end()) {
				q.push({u, *prev(it) + 1});
				d[{u, *prev(it) + 1}] = d[{u, v}] + 1; 
			}
		}
		if (it != x[u].end()) {
			if (d.find({u, *it - 1}) == d.end()) {
				q.push({u, *it - 1});
				d[{u, *it - 1}] = d[{u, v}] + 1; 
			}
		}
		it = y[v].lower_bound(u);
		if (it != y[v].begin()) {
			if (d.find({*prev(it) + 1, v}) == d.end()) {
				q.push({*prev(it) + 1, v});
				d[{*prev(it) + 1, v}] = d[{u, v}] + 1; 
			}
		}
		if (it != y[v].end()) {
			if (d.find({*it - 1, v}) == d.end()) {
				q.push({*it - 1, v});
				d[{*it - 1, v}] = d[{u, v}] + 1; 
			}
		}
	}
	cout << -1;

	return 0;
}

```


---

## 作者：封禁用户 (赞：1)

## 分析

一道 BFS 题。

对于某个点 $(x,y)$，我们可以通过二分找到其上下左右的第一个障碍物。由于我们不能在障碍物上面，所以我们在一直往方向 $k$ 走到障碍物时，最终的位置是 $(x',y')$，满足走到障碍物的过程中经过 $(x',y')$ 且 $(x',y')$ 距离障碍物的距离为 $1$。而在二分的时候，我们只需要对满足 $X=x$ 或 $Y=y$ 的障碍物进行二分，所以可以把 $x,y$ 分开来做。剩下的和 BFS 模板相同，第一次到终点必定最优，即走到终点时就可以结束代码，而无解就是 BFS 完还没有走到过终点的情况。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,pair<int,int> >
#define x first
#define y second
const int N=1e6+1000;
int n,m,k;
map<int,int> mpx,mpy;
map<int,map<int,int> > mp;
struct node{
	int x,y;
}x[N],y[N];
int idx,idy,cnt1,cnt2;
int sx,sy,tx,ty;
int a[N],b[N];
map<int,map<int,bool> > vis;
bool cmp1(node a,node b){//按x排序 
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
bool cmp2(node a,node b){//按y排序 
	if(a.y!=b.y) return a.y<b.y;
	return a.x<b.x;
}
priority_queue<PII,vector<PII>,greater<PII> > qu;
map<int,int> l_x,r_x,l_y,r_y;//l_x[i]存结构体中x坐标为i的起始坐标，r_x[i]为终点坐标；l_y,r_y同理 
int find1(int X,int l,int r){//最后一个y坐标小于X的位置 
	int L=l,R=r;
	int ans=-1;
	while(L<=R){
		int mid=L+R>>1;
		if(x[mid].y<X) L=mid+1,ans=mid;
		else R=mid-1;
	}
	return ans;
}
int find2(int X,int l,int r){//第一个y坐标大于X的位置 
	int L=l,R=r;
	int ans=-1;
	while(L<=R){
		int mid=L+R>>1;
		if(x[mid].y>X) R=mid-1,ans=mid;
		else L=mid+1;
	}
	return ans;
}
int find3(int X,int l,int r){//最后一个x坐标小于X的位置 
	int L=l,R=r;
	int ans=-1;
	while(L<=R){
		int mid=L+R>>1;
		if(y[mid].x<X) L=mid+1,ans=mid;
		else R=mid-1;
	}
	return ans;
}
int find4(int X,int l,int r){//第一个y坐标大于X的位置 
	int L=l,R=r;
	int ans=-1;
	while(L<=R){
		int mid=L+R>>1;
		if(y[mid].x>X) R=mid-1,ans=mid;
		else L=mid+1;
	}
	return ans;
}
void solve(){
	cin>>n>>m>>k;
	cin>>sx>>sy>>tx>>ty;
	for(int i=1;i<=k;i++){
		cin>>a[i]>>b[i];
		mp[a[i]][b[i]]=1;
		mpx[a[i]]++,mpy[b[i]]++;
		x[++idx]={a[i],b[i]},y[++idy]={a[i],b[i]};
	}
	if(mp[sx][sy]||mp[tx][ty]){//起止点是障碍物 
		cout<<"-1\n";
		return ;
	}
	sort(x+1,x+idx+1,cmp1),sort(y+1,y+idy+1,cmp2);
	for(int i=1;i<=idx;i++){
		if(!l_x[x[i].x]) l_x[x[i].x]=i,r_x[x[i].x]=i;
		else r_x[x[i].x]=i;
	}
	for(int i=1;i<=idy;i++){
		if(!l_y[y[i].y]) l_y[y[i].y]=i,r_y[y[i].y]=i;
		else r_y[y[i].y]=i;
	}
	qu.push({0,{sx,sy}});
	while(!qu.empty()){
		PII now=qu.top();qu.pop();
		if(vis[now.y.x][now.y.y]) continue;
		vis[now.y.x][now.y.y]=1;
		if(now.y.x==tx&&now.y.y==ty){
			cout<<now.x<"\n";
			return ;
		}
		if(mpx[now.y.x]||(now.y.x==sx&&now.y.y==sy)){
			int l=l_x[now.y.x],r=r_x[now.y.x];
			//向左 
			int where=find1(now.y.y,l,r);
			if(where>0){
				int nowx=x[where].x,nowy=x[where].y;
				qu.push({now.x+1,{nowx,nowy+1}});
			}
			//向右 
			where=find2(now.y.y,l,r);
			if(where>0){
				int nowx=x[where].x,nowy=x[where].y;
				qu.push({now.x+1,{nowx,nowy-1}});
			}
		}
		if(mpy[now.y.y]||(now.y.x==sx&&now.y.y==sy)){
			int l=l_y[now.y.y],r=r_y[now.y.y];
			//向上 
			int where=find3(now.y.x,l,r);
			if(where>0){
				int nowx=y[where].x,nowy=y[where].y;
				qu.push({now.x+1,{nowx+1,nowy}});
			}
			//向下 
			where=find4(now.y.x,l,r);
			if(where>0){
				int nowx=y[where].x,nowy=y[where].y;
				qu.push({now.x+1,{nowx-1,nowy}});
			}			
		}
	}
	cout<<"-1\n";
	return ; 
}
signed main(){
	solve();
	return 0;
}
```


---

## 作者：igAC (赞：1)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc241_f)

[ATlink](https://atcoder.jp/contests/abc241/tasks/abc241_f)

简要题意：

一个 $H \times W$ 的网格中有 $n$ 个障碍物。

你要从起点走到终点，行走的方式为：选定一个方向一直走，直到撞到一个障碍物（不允许选择没有障碍物的方向）。

询问最后能否正好停在终点。

# $\text{Solution}$

~~为什么这么水的一道题没人写题解呢。~~

看到一的第一眼觉得是道 BFS 板题，但是发现 $1 \le H,W \le 10^9$。

稍加思考发现~~确实是道 BFS 板题~~。

这道题 $H,W$ 非常大，但是障碍物个数 $n \le 10^5$。

于是我们可以用 ``map`` 套 ``set`` 存储每行障碍物的位置以及每列障碍物的位置。

左右走就是找这一行在当前位置左边的第一个障碍物以及第一个右边的障碍物，上下走同理。

我们可以使用 ``set`` 中的 ``lower_bound`` 进行查找，然后跑 BFS 即可。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
map<int,set<int>>mp1,mp2;
int n,m,k,sx,sy,tx,ty;
struct node{
	int x,y;
	int stp;
};
void BFS(){
	queue<node>q;
	set<pair<int,int>>vis;
	q.push({sx,sy,0});
	vis.insert({sx,sy});
	while(!q.empty()){
		node now=q.front();q.pop();
		int x=now.x,y=now.y,stp=now.stp;
		if(x==tx && y==ty){
			printf("%d",stp);
			return;
		}
		//right
		auto it1=mp1[x].lower_bound(y);
		if(it1!=mp1[x].end()){
			if(vis.find({x,*it1-1})==vis.end()){
				q.push({x,*it1-1,stp+1});
				vis.insert({x,*it1-1});
			}
		}
		//left
		if(it1!=mp1[x].begin()){
			--it1;
			if(vis.find({x,*it1+1})==vis.end()){
				q.push({x,*it1+1,stp+1});
				vis.insert({x,*it1+1});
			}
		}
		//down
		auto it2=mp2[y].lower_bound(x);
		if(it2!=mp2[y].end()){
			if(vis.find({*it2-1,y})==vis.end()){
				q.push({*it2-1,y,stp+1});
				vis.insert({*it2-1,y});
			}
		} 
		//up
		if(it2!=mp2[y].begin()){
			--it2;
			if(vis.find({*it2+1,y})==vis.end()){
				q.push({*it2+1,y,stp+1});
				vis.insert({*it2+1,y});
			}
		}
	}
	puts("-1");
}
int main(){
	n=read(),m=read(),k=read();
	sx=read(),sy=read(),tx=read(),ty=read();
	for(int i=1;i<=k;++i){
		int x=read(),y=read();
		mp1[x].insert(y);
		mp2[y].insert(x);
	}
	BFS();
	return 0;
}
```

---

## 作者：AlicX (赞：1)

## Solution

一道伪装的广搜题。发现它与普通的广搜唯一差别只有边长，而障碍物的数据是可以接受的。另外发现一个性质：到达一个点都与它所对的障碍物有关，所以我们可以考虑通过障碍物转移。对于每一个障碍物，用两个数组将他们存起来，当我们做决策时，分四个方向进行二分，找到某个方向最近的障碍物然后移动过去。总的时间复杂度为 $\mathcal{O(n\log n)}$。

注意判断数组越界。

```cpp
// Celestial Cyan 
  

#include<bits/stdc++.h>
//#define int long long
#define x first
#define y second
#define il inline 
#define db double
#define low(x) x&-x
#define ls(x) x<<1
#define rs(x) x<<1|1 
#define pb(x) push_back(x)
#define gcd(x,y) __gcd(x,y) 
#define lcm(x,y) x*y/gcd(x,y) 
#define debug() puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1e5+10,K=4,INF=1e9+7;  
int n,m,k; 
int sx,sy; 
int tx,ty; 
pii del[N];   
//int dx[K]={1,-1,0,0},dy[K]={0,0,1,-1}; 
unordered_map<int,bool> st1,st2;  
map<int,vector<pii> > vex,vey; 
unordered_map<int,unordered_map<int,bool> > mp; 
struct Mind{ 
	int x,y,w; 
	il bool operator<(Mind &Cyan)const{ }  
}; 
il void bfs(){
	queue<Mind> q; 
	q.push({sx,sy,0}); mp[sx][sy]=true; 
	while(!q.empty()){ 
		int x=q.front().x,y=q.front().y;
		int w=q.front().w; q.pop(); //cout<<x<<" "<<y<<" "<<w<<endl; 
		if(x==tx&&y==ty){ 
			printf("%d\n",w); 
			exit(0); 
		} int id,x0,y0; 
		id=upper_bound(vex[x].begin(),vex[x].end(),pii(x,y))-vex[x].begin(); 
		if(!vex[x].empty()&&vex[x][id].x!=INF){ 
			x0=vex[x][id].x,y0=vex[x][id].y-1; 
			if(!mp[x0][y0]) mp[x0][y0]=true,q.push({x0,y0,w+1}); 
		} id=lower_bound(vex[x].begin(),vex[x].end(),pii(x,y))-vex[x].begin()-1; 
		if(!vex[x].empty()&&vex[x][id].x){ 
			x0=vex[x][id].x,y0=vex[x][id].y+1; 
			if(!mp[x0][y0]) mp[x0][y0]=true,q.push({x0,y0,w+1}); 
		} id=upper_bound(vey[y].begin(),vey[y].end(),pii(y,x))-vey[y].begin(); 
		if(!vey[y].empty()&&vey[y][id].x!=INF){
			x0=vey[y][id].y-1,y0=vey[y][id].x; 
			if(!mp[x0][y0]) mp[x0][y0]=true,q.push({x0,y0,w+1}); 
		} id=lower_bound(vey[y].begin(),vey[y].end(),pii(y,x))-vey[y].begin()-1; 
		if(!vey[y].empty()&&vey[y][id].x){ 
			x0=vey[y][id].y+1,y0=vey[y][id].x;    
			if(!mp[x0][y0]) mp[x0][y0]=true,q.push({x0,y0,w+1}); 
		} 
	} return ; 
} 
signed main(){ 
//	freopen("skate.in","r",stdin); 
//	freopen("skate.out","w",stdout);
	cin>>n>>m>>k; 
	cin>>sx>>sy>>tx>>ty; 
	for(int i=1,x,y;i<=k;i++){ 
		cin>>del[i].x>>del[i].y; x=del[i].x,y=del[i].y;  
		vex[x].push_back({x,y}),vey[y].push_back({y,x}); 
	} for(int i=1;i<=k;i++){ 
		int x=del[i].x,y=del[i].y; 
		if(!st1[x]){ 
			vex[x].push_back({0,0}),vex[x].push_back({INF,INF}); 
			st1[x]=true; sort(vex[x].begin(),vex[x].end()); 
		} if(!st2[y]){ 
			vey[y].push_back({0,0}),vey[y].push_back({INF,INF}); 
			st2[y]=true; sort(vey[y].begin(),vey[y].end()); 
		} 
	} bfs(); puts("-1"); 
	return 0;
} /* 
7 8 7 
3 4
5 6
1 4
2 1
2 8
4 5
5 7
6 2
6 6

4 6 2
3 2
3 5
4 5
2 5
*/ 
```


---

## 作者：zyc418 (赞：0)

# Skate

[题目](https://www.luogu.com.cn/problem/AT_abc241_f)

这是一道一眼的 **Bfs** 但单单是搜索就很容易爆 **TLE**。

于是我们可以~~很容易~~想到用 `set` 记录下每一行和每一列 分别有哪些障碍，这样向四个方向移动是就可以直接二分出该方向最近的障碍即可，可以使用 `lower_bound`。

记录每一行和每一列分别有哪些障碍和从起点到各个点的距离等数据时，若是直接用数组存，显然直接 **MLE** 炸掉。我们可以用 `map` 代替数组存数据。

# Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll h,w,n,sx,sy,ex,ey,ans=-1;
map<ll,set<ll> > x,y;
map<pair<ll,ll>,ll> d;
queue<pair<ll,ll> > q;
void bfs() {
    q.push({sx,sy});
	d[{sx,sy}]=0;
	while(!q.empty()) {
        pair<ll,ll> pl=q.front();
		ll u=pl.first,v=pl.second;
		q.pop();
		if(u==ex&&v==ey) {
			ans=d[{u,v}];
			break;
		}
		auto it=x[u].lower_bound(v);
		if(it!=x[u].begin()) {
			if(d.find({u,*prev(it)+1})==d.end()) {
				q.push({u,*prev(it)+1});
				d[{u,*prev(it)+1}]=d[{u,v}]+1; 
			}
		}
		if(it!=x[u].end()) {
			if(d.find({u,*it-1})==d.end()) {
				q.push({u,*it-1});
				d[{u,*it-1}]=d[{u,v}]+1; 
			}
		}
		it=y[v].lower_bound(u);
		if(it!= y[v].begin()) {
			if(d.find({*prev(it)+1,v})==d.end()) {
				q.push({*prev(it)+1,v});
				d[{*prev(it)+1,v}]=d[{u,v}]+1; 
			}
		}
		if(it!=y[v].end()) {
			if(d.find({*it-1,v})==d.end()) {
				q.push({*it-1,v});
				d[{*it-1,v}]=d[{u,v}]+1; 
			}
		}
	}
}
int main() {
	cin>>h>>w>>n>>sx>>sy>>ex>>ey;
	for (ll i = 1; i <= n; i++) {
		ll ul,vl;
		cin>>ul>>vl;
		x[ul].insert(vl);
		y[vl].insert(ul);
	}
    bfs();
	cout<<ans;
	return 0;
}
```

---

## 作者：Gaochenxi103_QWQ (赞：0)

## 解题思路
首先我们发现这道题目乍一看就是到简单的搜索，但仔细一看数据范围发现 $N\times M=10^{18}$，就根本存不下。

那这道题目的突破口就是每一步搜索的转移是和障碍物息息相关的，并且障碍物的数量 $N=10^5$，而 $10^5$ 一般都是在复杂度上带个 $log$ 的。由此我们可以想到转移的时候要用到二分。（这里不懂也没关系）

其次对于一个在 $(x,y)$ 位置的点，它可以到 $[1,x-1],[1,y-1],[x+1,n],[y+1,m]$ 这上下左右四个方向的离它最近的障碍物那里。

但我们不可能直接存障碍物的坐标，所以我们可以想到一个简单的离散化，将每行和每列的障碍物存到映射表里面。但它又不是按照从小到大的顺序依次输入障碍物的，所以我们可以在套一个集合来排序。

就是这样。
```cpp
map<int,set<int> > a;//a[x]表示第x行的障碍物集合
map<int,set<int> > b;//b[x]表示第x列的障碍物集合
```
而在找障碍物的时候就可以用二分来找，找第一个左边和上面的第一个小于我的障碍物时，找到右边和下面的第一个大于我的值在往前减一位就是了。

就是这样。
```cpp
//往下找
p=b[u.y].lower_bound(u.x);
if(p!=b[u.y].begin())
{
    p--;
    if(!fd[*p+1][u.y])
    {
        fd[*p+1][u.y]=true;
        q.push({u.bs+1,*p+1,u.y});
    }
}
```

最后记的标记一下避免绕圈就行了。
## AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
map<int,set<int> > a;
map<int,set<int> > b;
map<int,map<int,bool> > fd;
int xd,yd,xs,ys,h,w,n;
struct S{
    int bs,x,y;
};
signed main()
{
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    cin>>h>>w>>n>>xs>>ys>>xd>>yd;
    for(int i=1;i<=n;i++)
    {
        int x,y;
        cin>>x>>y;
        a[x].insert(y);
        b[y].insert(x);
    }
    // dfs({0,xs,ys});
    // cout<<-1;
    queue<S> q;
    q.push({0,xs,ys});
    while(q.size())
    {

        S u=q.front();
        q.pop();
        if(u.x==xd && u.y==yd)
        {
            cout<<u.bs;
            return 0;
        }
        // cout<<u.x<<" "<<u.y<<" "<<u.bs<<"\n";
        //左
        auto p=a[u.x].lower_bound(u.y);
        if(p!=a[u.x].begin())
        {
            p--;
            // cout<<"left "<<*p<<" "<<fd[u.x][*p]<<" ";
            if(!fd[u.x][*p+1])
            {
                fd[u.x][*p+1]=true;
                q.push({u.bs+1,u.x,*p+1});
            }
        }
        //右
        p=a[u.x].lower_bound(u.y);
        if(p!=a[u.x].end())
        {
            // cout<<"right "<<*p<<" "<<fd[u.x][*p]<<" ";
            if(!fd[u.x][*p-1])
            {
                fd[u.x][*p-1]=true;
                q.push({u.bs+1,u.x,*p-1});
            }
        }

        //上
        p=b[u.y].lower_bound(u.x);
        if(p!=b[u.y].begin())
        {
            p--;
            // cout<<"up "<<*p<<" "<<fd[*p][u.y]<<" ";
            if(!fd[*p+1][u.y])
            {
                fd[*p+1][u.y]=true;
                q.push({u.bs+1,*p+1,u.y});
            }
        }

        //下
        p=b[u.y].lower_bound(u.x);
        if(p!=b[u.y].end())
        {
            // cout<<"down "<<*p<<" "<<fd[*p][u.y]<<" ";
            if(!fd[*p-1][u.y])
            {
                fd[*p-1][u.y]=true;
                q.push({u.bs+1,*p-1,u.y});
            }
        }
        // cout<<"\n";
    }
    cout<<-1;
}
```

---

## 作者：cwxcplh (赞：0)

一道~~经典~~的 bfs 题。

**提醒：本题解是为小白专做的，不想看的大佬请离开。**

这道题首先一看就知道是 bfs，但是数据点不让我们过： $1\le H,W\le10^9$。

那么我们就需要优化了，从哪儿下手呢？看数据点第三行：$1\le N\le10^5$。

图很大，但是石头不多，那么我们就可以从石头下手。这里需要我们把思维方式转换过来一下。

正常的 bfs 是去找路，那我们就找石头！那石头在哪儿呢？

首先，我们不可能在 bfs 的时候把所有的石头全扫一遍然后找，这样很明显会 TLE。而我们再回忆一下 bfs 的过程：**上下左右**全走一遍，然后……

对啊！bfs 只扫这个点的这一行、这一列，我们为什么不能把每一行、每一列的石头所在的列数、行数保存下来呢？但还是有个问题：如果我要跑一行的数据，很有可能会被数据点卡，怎么再优化呢？这就要请出查询时间复杂度最低的算法了：**二分！**

总时间复杂度：最差情况下 $O(n\log_2(n))$。

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t,x,y,stx,sty,edx,edy;
map<pair<int,int>,int>dis;
map<int,set<int>>h,l;
queue<pair<int,int>>q;
void add(int u,int v,int now) {
	if(dis.find(make_pair(u,v))==dis.end()) {
		dis[make_pair(u,v)]=now;
		q.push(make_pair(u,v));
	}
}
signed main() {
	cin>>n>>m>>t>>stx>>sty>>edx>>edy;
	while(t--) {
		cin>>x>>y;
		h[x].insert(y);//保存行和列
		l[y].insert(x);
	}
	dis[make_pair(stx,sty)]=0;
	q.push(make_pair(stx,sty));
	while(!q.empty()) {
		pair<int,int>p=q.front();
		q.pop();
		int u=p.first,v=p.second;
		int now=dis[make_pair(u,v)];
		if(u==edx&&v==edy) {
			cout<<now;
			return 0;
		}
		auto it=h[u].lower_bound(v);//二分
		if(it!=h[u].end()) {
			add(u,(*it)-1,now+1);//这里我试过把函数中的部分放下来，但就是不知道为什么会错
		}
		if(it!=h[u].begin()) {
			add(u,(*(--it))+1,now+1);
		}
		it=l[v].lower_bound(u);
		if(it!=l[v].end()) {
			add((*it)-1,v,now+1);
		}
		if(it!=l[v].begin()) {
			add((*(--it))+1,v,now+1);
		}
	}
	cout<<"-1";
	return 0;
}
```

---

