# [ABC363E] Sinking Land

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc363/tasks/abc363_e

$ H\ \times\ W $ の大きさの島があり、島は周りを海で囲まれています。  
 島は 縦 $ H $ 個 $ \times $ 横 $ W $ 個の $ 1\times\ 1 $ の区画に分けられており、上から $ i $ 番目かつ左から $ j $ 番目の区画の（現在の海面を基準にした）標高は $ A_{i,j} $ です。

現在から $ 1 $ 年ごとに海面の高さが $ 1 $ ずつ上昇します。  
 このとき、海または海に沈んだ区画に上下左右に隣接する区画であって、標高が海面の高さ **以下** の区画は海に沈みます。  
 ここで、ある区画が新しく海に沈んだときそれと上下左右に隣接する区画であって海面の高さ以下のものも同時に海に沈み、これによって新しく沈んだ区画についてもこれは繰り返されます。

$ i=1,2,\ldots,\ Y $ それぞれについて、現在から $ i $ 年後に、島のうち海に沈まず残っている部分の面積を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ H,W\leq\ 1000 $
- $ 1\leq\ Y\leq\ 10^5 $
- $ 1\leq\ A_{i,j}\leq\ 10^5 $
- 入力はすべて整数
 
### Sample Explanation 1

島の上から $ i $ 番目かつ左から $ j $ 番目の区画を $ (i,j) $ で表します。このとき、次のようになります。 - $ 1 $ 年後、海面は現在より $ 1 $ 上昇しますが、海に面している標高 $ 1 $ の区画は存在しないため、どの区画も沈みません。よって、$ 1 $ 行目には $ 9 $ を出力します。 - $ 2 $ 年後、海面は現在より $ 2 $ 上昇し、$ (1,2) $ が海に沈みます。これによって、$ (2,2) $ は海に沈んだ区画に隣接する区画となりますが、その標高は $ 2 $ 以下であるため、これも海に沈みます。これら以外にこの時点で他に沈む区画はありません。よって、$ 2 $ つの区画が沈むため、$ 2 $ 行目には $ 9-2=7 $ を出力します。 - $ 3 $ 年後、海面は現在より $ 3 $ 上昇し、$ (2,1) $ が新しく海に沈みます。他に沈む区画はありません。よって、$ 3 $ 行目には $ 6 $ を出力します。 - $ 4 $ 年後、海面は現在より $ 4 $ 上昇し、$ (2,3) $ が新しく海に沈みます。他に沈む区画はありません。よって、$ 4 $ 行目には $ 5 $ を出力します。 - $ 5 $ 年後、海面は現在より $ 5 $ 上昇し、$ (3,2) $ が新しく海に沈みます。他に沈む区画はありません。よって、$ 5 $ 行目には $ 4 $ を出力します。 よって、$ 9,7,6,5,4 $ をこの順に各行に出力します。

## 样例 #1

### 输入

```
3 3 5
10 2 10
3 1 4
10 5 10```

### 输出

```
9
7
6
5
4```

## 样例 #2

### 输入

```
3 5 3
2 2 3 3 3
2 1 2 1 3
2 2 3 3 3```

### 输出

```
15
7
0```

# 题解

## 作者：cqbzcjh (赞：8)

看到这道题，很容易想到使用**泛洪填充**。  

我们可以每一年都跑一遍 BFS 来计算答案。但这样的做法肯定会超时，优化如下：

使用优先队列，先将岛屿的边缘全部入队，BFS 每次先遍历最低的区域。如果当前连最低的区域都淹没不了就直接跳到下一年。并且，这一年没有被淹没但被遍历到的区域也要入队，这样下一年只需要在这一年的基础上继续搜索新淹没的区域即可。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
struct node{
	int v,x,y;
	//重载运算符，小根堆
	bool operator<(const node &T)const{
		return v>T.v;
	}
};
int h,w,y,a[N][N],ans;
bool vis[N][N];
priority_queue<node> q;
int main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);cout.tie(NULL);
	cin>>h>>w>>y;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>a[i][j];
			//将边缘入队
			if((i==1)||(i==h)||(j==1)||(j==w)){
				vis[i][j]=true;
				q.push({a[i][j],i,j});
			}
		}
	}
	ans=h*w;
	for(int i=1;i<=y;i++){
		//bfs
		while(!q.empty()&&q.top().v<=i){
			node u=q.top();
			q.pop();
			ans--;
			for(int j=0;j<4;j++){
				int tx=u.x+dx[j];
				int ty=u.y+dy[j];
				if(tx>=1&&tx<=h&&ty>=1&&ty<=w&&!vis[tx][ty]){
					vis[tx][ty]=true;
					q.push({a[tx][ty],tx,ty});
				}
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Crsuh2er0 (赞：4)

看到此题不难想到在一个地段沉没时可以搜索旁边的地段，并不断进行下去。因此我们考虑搜索。

由于沉没总是从边缘开始，即搜索的起点在边缘，因此我们可以考虑将边缘地段装进队列里来方便搜索。

考虑沉没总是从最低的边缘地段开始，我们使用一个优先队列来方便我们找到这个最低的边缘地段。

### 一些 Corner Case

- 访问堆顶时不检测堆是否为空。
- 地段放入堆时不检测之前是否放入过。

```cpp
#include <bits/extc++.h>
using namespace std;
#define debug(...) fprintf(stderr, __VA_ARGS__)
const int MAXN = 1010;
int h, w, t, a[MAXN][MAXN], ans;
bitset<MAXN> vis[MAXN], inq[MAXN];
struct edge {
    int x, y;
    bool operator>(const edge &tmp) const { return a[x][y] > a[tmp.x][tmp.y]; }
};
priority_queue<edge, basic_string<edge>, greater<edge> > q;

void dfs(int x, int y) {
    if (vis[x][y] || x > h || y > w || !x || !y) return;
    if (a[x][y] <= a[h + 1][w + 1]) {
        vis[x][y] = 1, ans--;
        // debug("sink %d %d\n", x, y);
        dfs(x + 1, y), dfs(x, y + 1);
        dfs(x - 1, y), dfs(x, y - 1);
    } else if (!inq[x][y])
        q.push({x, y}), inq[x][y] = 1;
}

int main() {
    cin >> h >> w >> t;
    ans = h * w;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) cin >> a[i][j];
    }
    for (int i = 1; i <= w; i++)
        q.push({1, i}), q.push({h, i}), inq[1][i] = inq[h][i] = 1;
    for (int i = 2; i < h; i++)
        q.push({i, 1}), q.push({i, w}), inq[i][1] = inq[i][w] = 1;
    a[h + 1][w + 1] = 1;
    for (int i = 1; i <= t; i++, a[h + 1][w + 1]++) {
        while (q.size() && a[h + 1][w + 1] >= a[q.top().x][q.top().y]) {
            int tmpx = q.top().x, tmpy = q.top().y;
            q.pop();
            dfs(tmpx, tmpy);
        }
        cout << ans << '\n';
    }
}
```

---

## 作者：2011FYCCCTA (赞：2)

[原题](https://www.luogu.com.cn/problem/AT_abc363_e)

某人赛时因细节错误痛失首次 abc 赛时切五题和首次 abc 赛时无伤切五题。

---
### 思路

最暴力的思路：对于每个海平面高度进行 bfs，在队列中找到不大于海平面的区域就拓展，并统计，此方法会 TLE。

如果你稍加观察，就会发现，海平面为 $a$ 时沉没的区域，在海平面为 $(a+1)$ 时一定也会沉没。所以，不需要每次都重新 bfs，直接按着上一次的结果继续即可（笔者没测试过会不会 TLE）。

还可以继续优化，找到不大于海平面的区域这一步，可以使用堆进行优化，一直取出当前堆内海拔最低的区域看是否被淹没，如果是就拓展，否则结束。

整个过程类似 dijkstra 算法诶。

---
### [代码](https://atcoder.jp/contests/abc363/submissions/55867222)

---

## 作者：joe_zxq (赞：2)

# Part 0 - 前言闲话

恭喜这只彩笔喜提几乎最劣解！时限 $2$ 秒，本彩笔 $1870$ 毫秒。

一种不同寻常的解法，欢迎小伙伴们点赞，支持一下这只彩笔！

# Part 1 - 算法思路

## 1-1 算法概述

本题解讲述的方法并非大多数人都写的 BFS，而是选择用 set 进行维护。

虽然除去常数外，算法的时间复杂度理论上是可行的。但是 set 的操作次数较多，常数的叠加就导致算法运行时间长。

## 1-2 结构体对每个位置的存储

下面定义一个位置临海，当且仅当这个位置上下左右四个位置中有至少一个位置是海或已经被淹没。

用结构体存储每一个位置的数据：

- $h$ 表示该点的海拔高度。
- $f$ 表示该点的状态。若 $f=1$，表示该点临海；若 $f=10^6$，表示该点不临海。至于为什么这么设置，参见后文。
- $x$ 和 $y$ 表示该点的横纵坐标。

## 1-3 遍历和模拟

我们遍历海平面 $1 \sim Y$。对于每次海平面的升高，我们从低到高海拔遍历临海的位置，那么：

- 若这个位置可以淹没，那就将该位置删除，答案增加，将其上下左右四个位置更新为临海状态。
- 若不可以淹没，那么后面的位置海拔更高，显然更不能淹没，于是跳出遍历。

## 1-4 结构体大小关系的定义

如何直接从低到高海拔遍历临海的位置？

我们可以将每个位置的结构体放到 set 里，因为它有排序的功能。既然要放到 set 里排序，就固然要定义结构体的大小关系。

两个结构体的大小关系定义为两者的 $h \times f$ 的大小关系。这样的话，$f=1$ 的临海位置就可以自然地排在 $f=10^6$ 的非临海位置之前。对于所有临海位置，显然海拔越低，即 $h$ 越小，那么 $h \times f$ 就越小，可以实现海拔从低到高的排序。

## 1-5 卡常

你说得对，但是 set 的常数太大。这样的代码很容易超时。

对于这道题的卡常，有很多方式：

- 卡常手段千千万，快读快写占一半。
- 用数组存储是否淹没，替代 set 的查找函数。
- 或许你可以手动开 O2 或 O3。
- 对于更多的卡常方式，就请各位读者各显神通啦。

# Part 2 - 代码实现

代码实现就很容易啦。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, c[1024][1024];
bool vis[1024][1024];
struct node {
    int h, f, x, y;
    bool operator < (const node &a) const {
        if (1ll*h * f != 1ll*a.h * a.f) {
            return 1ll*h * f < 1ll*a.h * a.f;
        }
        if (x != a.x) {
            return x < a.x;
        }
        return y < a.y;
    }
};
set<node> s;

void del(int x, int y) {
    if (x && x<=n && y && y<=m && !vis[x][y]) {
        vis[x][y]=true;
        s.erase({c[x][y], 1000000, x, y});
        s.insert({c[x][y], 1, x, y});
    }
}
int read(){
    char c;
    while(!isdigit(c=getchar()));
    int res=(c^48);
    while(isdigit(c=getchar()))res=(res<<3)+(res<<1)+(c^48);
    return res;
}
int main() {
    n=read(),m=read(),k=read();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            c[i][j]=read();
            int ff = 1000000;
            if (i == 1 || j == 1 || i == n || j == m) {
                ff = 1;
            }
            s.insert({c[i][j], ff, i, j});
        }
    }
    for (int i = 1; i <= k; i++) {
        node nw = *s.begin();
        while (nw.h <= i && nw.f == 1) {
            s.erase(s.begin());
            del(nw.x - 1, nw.y);
            del(nw.x + 1, nw.y);
            del(nw.x, nw.y - 1);
            del(nw.x, nw.y + 1);
            nw = *s.begin();
        }
        printf("%d\n", s.size());
    }

    return 0;
}
```

---

## 作者：incra (赞：1)

### 前言
D > E > F。

AT 【数据删除】。

### Sol
简单题，赛时【数据删除】没切 D。

考虑从小到大枚举海平面高度并 BFS，显然高度为 $d$，可以在 $d-1$ 的基础上进行淹没城市，所以我们枚举 $d$，每次把高度 $\le d$ 的点淹没并扔到 BFS 队列中，然后就做完了。

注意到每个点最多只进队和出队一次，故复杂度为 $O(nm)$。
### Code
```
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << s << endl
const int N = 1010;
int n,m,k;
int a[N][N];
bool vis[N][N];
int main () {
	cin >> n >> m >> k;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) cin >> a[i][j];
	}
	using p = pair <int,PII>;
	priority_queue <p,vector <p>,greater <p> > q;
	for (int i = 0;i <= n + 1;i++) q.push ({0,{i,0}}),q.push ({0,{i,m + 1}});
	for (int i = 0;i <= m + 1;i++) q.push ({0,{0,i}}),q.push ({0,{n + 1,i}});
	int ans = n * m;
	for (int i = 1;i <= k;i++) {
		while (q.size () && q.top ().x <= i) {
			PII u = q.top ().y;
			ans -= q.top ().x != 0;
			q.pop ();
			for (int i = 0;i < 4;i++) {
				int x = u.x + dx[i],y = u.y + dy[i];
				if (x < 1 || x > n || y < 1 || y > m || vis[x][y]) continue;
				q.push ({a[x][y],{x,y}});
				vis[x][y] = true;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：DengStar (赞：1)

[题目链接](https://atcoder.jp/contests/abc363/tasks/abc363_e)

依题意，可以得到一个地块沉没所需的两个条件：

1. 该地块的海拔小于等于海平面。
2. 该地块临海，或者与某个已沉没的地块相邻。（下面简单地把这个条件成为“临海”）

第一个条件中，海拔是一开始就确定的。而第二个条件中，一个地块什么时候临海，是动态的。并且一个地块只要在某个时刻开始临海，它在之后的时刻就会一直临海，直到沉没。

我们可以用优先队列维护地块的“临海”状态——把所有临海的地块都加入优先队列中。具体地，在优先队列中，我们按地块的海拔从小到大排序。每次海平面升高，就弹出队首的所有海拔不超过海平面的地块，同时计数以得到答案。如果某个地块沉没了，就把它的所有相邻地块都加入到优先队列中（如果这些地块还未被加入），表示这些地块也开始临海。

在这一过程中，需要记录每个地块是否被加入到队列中，以防重复统计。同时，由于每个地块只会被加入一次，所以时间复杂度为 $O(n^2 \log n^2)$（这里的 $n^2$ 指题目中的 $H\times W$）。

[参考代码](https://atcoder.jp/contests/abc363/submissions/55798181)

---

## 作者：Lydia1010__ (赞：1)

## 本题思路：
这道题其实并不复杂，我们知道一座岛沉下去的条件是他要临海且海平面高于他，这样我们就可以开一个小根堆，存储当前临海岛的高度有多高，枚举每一个高度，如果海平面的高度比一些临海岛的高度要高，就踢出堆，把与他相邻的没有入过堆的元素放进堆，直到没有比当前海平面高度低的临海岛。

这样做每个岛只会进堆一次，出堆一次，答案就在出堆的时候减去即可，时间复杂度正确。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<pair<int,int> >q;
struct f{
	int x,y;
}a[1000005];
int vis[1001][1001],num[1001][1001],cnt;
bool sum[1001][1001];
int main(){
	int h,w,y;
	cin>>h>>w>>y;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>vis[i][j];
			num[i][j]=++cnt;
			a[cnt].x=i,a[cnt].y=j;
		}
	}
	for(int i=1;i<=w;i++) if(!sum[1][i]) sum[1][i]=1,q.push(make_pair(-vis[1][i],num[1][i]));
	for(int i=1;i<=w;i++) if(!sum[h][i]) sum[h][i]=1,q.push(make_pair(-vis[h][i],num[h][i]));
	for(int i=1;i<=h;i++) if(!sum[i][1]) sum[i][1]=1,q.push(make_pair(-vis[i][1],num[i][1]));
	for(int i=1;i<=h;i++) if(!sum[i][w]) sum[i][w]=1,q.push(make_pair(-vis[i][w],num[i][w]));
	int siz=h*w;
	for(int i=1;i<=y;i++){
		while(q.size()&&-q.top().first<=i){
			siz--;
			int l=a[q.top().second].x,r=a[q.top().second].y;
//			cout<<l<<" "<<r<<endl;
			q.pop();
			if(l+1<=h) if(!sum[l+1][r]) sum[l+1][r]=1,q.push(make_pair(-vis[l+1][r],num[l+1][r]));
			if(l-1>=1) if(!sum[l-1][r]) sum[l-1][r]=1,q.push(make_pair(-vis[l-1][r],num[l-1][r]));
			if(r+1<=w) if(!sum[l][r+1]) sum[l][r+1]=1,q.push(make_pair(-vis[l][r+1],num[l][r+1]));
			if(r-1>=1) if(!sum[l][r-1]) sum[l][r-1]=1,q.push(make_pair(-vis[l][r-1],num[l][r-1]));
			
		}
		cout<<siz<<endl;
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 思路

考虑使用优先队列存下每一个目前边界的高度和坐标。

每次把可以淹没的陆地都淹没，再将新的边界入队。

### 代码

```cpp
#include<bits/stdc++.h>
#define run(x,y,t) {f[x][y]=0;vis[x][y]=1;dfs(x,y,t);}
using namespace std;
const int N=1005;
int n,m,k,a[N][N],vis[N][N],ans,f[N][N];//用vis标记是否被淹没，f标记是否在队列中
struct T
{
	int x,y,w;
	bool operator <(const T b)const
	{
		return w>b.w;
	}
};
priority_queue<T>q;
bool ok(int x,int y,int t)//判断在第t时刻是否能淹没坐标为(x,y)的陆地
{
	if(x<1||y<1||x>n||y>m)return 0;
	if(vis[x][y])return 0;
	if(a[x][y]>t)//如果陆地太高则为新的海岸
	{
		if(!f[x][y])
		{
			q.push({x,y,a[x][y]});
			f[x][y]=1;
		}
		return 0;
	}
	return 1;
}
void dfs(int x,int y,int t)
{
	ans--;
	if(ok(x-1,y,t))run(x-1,y,t)
	if(ok(x+1,y,t))run(x+1,y,t)
	if(ok(x,y-1,t))run(x,y-1,t)
	if(ok(x,y+1,t))run(x,y+1,t)
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(i==1||j==1||i==n||j==m)
			{
				f[i][j]=1;
				q.push({i,j,a[i][j]});
			}
		}
	}
	ans=n*m;//用ans记录每次的答案
	for(int i=1;i<=k;i++)
	{
		while(!q.empty()&&q.top().w<=i)//判断每一个海岸是否能被淹没
		{
			int x=q.top().x,y=q.top().y;
			q.pop();
			f[x][y]=0;
			if(vis[x][y])continue;//若已经被淹没则不用再淹
			vis[x][y]=1;
			dfs(x,y,i);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：1)

~~这么简单的题我考场上居然没想出来。~~

肯定能想到可能会沉没的是与海面相邻的岛屿。最开始与海面相邻的是四周的一圈。当有一个岛屿的海拔低于海平面而沉没后，与它相邻的未沉没岛屿就会成为可能沉没的岛屿。

这样我们就能建一个堆，其中记录了所有可能沉没的岛屿，按岛屿海拔由低到高排序。枚举每一时刻，将每一时刻变得比海平面低的岛屿弹出堆、计数并把与它相邻的未沉没岛屿加入堆，再输出当前时刻的计数即可。

注意最开始将四周的岛屿加入堆中时要特判 $n=1$ 或 $m=1$ 的情况，不要加重了。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,a[1005][1005];
bool flag[1005][1005];
struct node{
	int x,y,k;
	bool operator <(const node &b) const{
		return k>b.k;
	}
};
priority_queue<node> q;
bool in(int x,int y){
	if(x<1||x>n) return 0;
	if(y<1||y>m) return 0;
	return 1;
}
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int main(){
	cin>>n>>m>>t;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
	if(m==1) for(int i=1;i<=n;i++) q.push({i,1,a[i][1]}),flag[i][1]=1;
	else for(int i=1;i<=n;i++) q.push({i,1,a[i][1]}),q.push({i,m,a[i][m]}),flag[i][1]=flag[i][m]=1;
	if(n==1) for(int i=2;i<m;i++) q.push({1,i,a[1][i]}),flag[1][i]=1;
	else for(int i=2;i<m;i++) q.push({1,i,a[1][i]}),q.push({n,i,a[n][i]}),flag[1][i]=flag[n][i]=1;
	int sum=n*m;
	for(int i=1;i<=t;i++){
		while(!q.empty()&&q.top().k<=i){
			node t=q.top();q.pop();
			sum--;
			for(int k=0;k<4;k++){
				int xx=t.x+dx[k],yy=t.y+dy[k];
				if(in(xx,yy)&&!flag[xx][yy]) q.push({xx,yy,a[xx][yy]}),flag[xx][yy]=1;
			}
		}
		cout<<sum<<"\n";
	}
	return 0;
}
```

---

## 作者：hayzxjr (赞：0)

[link]((https://atcoder.jp/contests/abc363/tasks/abc363_e))

先分享我的赛时比较差的做法。

注意到题目中 $H, W$ 是 $10^3$ 的，$Y$ 是 $10^5$ 的，可以考虑 $\mathcal{O}(HW\log HW)$ 的做法。

注意复杂度，关键是 $Y$ 对复杂度无关键作用。

但是不妨碍我们枚举每一天。（具体见下文的复杂度解释）

于是考虑将 **当前靠海的位置** 放入队列，每次取出队首，判断该位置是否下沉。

- 若下沉，则将其相邻点放入队尾；
- 若不下沉，选择放入另一个队列中。

然后两个队列滚动即可。时间复杂度是 $\mathcal{O}(TLE)$。

下面考虑优化。

注意到每次取出的元素只有 $\le i$（$i$ 为当前枚举到的天数）的才有用，故考虑用优先队列。

只开一个即可。每次取出所有 $h \le i$ 的元素进行判断及更新操作。

结束了。由于每个点最多出队一次，时间复杂度是 $\mathcal{O}(HW \log HW)$ 的。

稍微总结一下。

开 E 的时候还剩不到 20 min（D 细节写挂好几次），不过还是想着先写简单的做法。

事实证明这是不对的，还是应当调整做题节奏，争取做到思考时间 + 写代码时间的最优化。

就像均值不等式那样，目前多花一点时间思考，是可以得到更好结果的。

[Code](https://atcoder.jp/contests/abc363/submissions/55821612)

---

## 作者：_sin_ (赞：0)

注意到一个点被淹没要满足一下两个条件：
- 这个点的海拔小于等于海平面高度。
- 这个点在边缘或者四周存在一个点海拔比自己高且那个店被淹没。

将岛上所有点按照海拔高度排序，逐层模拟海水上涨的过程。当一个点低于海平面时如果这个点是在边缘，直接就会被淹没。然后枚举它旁边的点，如果旁边的点海拔比它低，那么就合并两个点。可以用并查集维护。为了方便维护，不妨令 $0$ 号节点为海洋，边缘的节点低于海平面直接与 $0$ 号节点相邻。最终答案就是所有的点减去被淹没的点。被淹没的点个数显然就是 $0$ 号节点所在连通块大小减一。

代码实现是非常简单的，由于 `beg` 只会增加，所以时间复杂度是 $O(HW\log(HW))$ 的，瓶颈在排序，可以通过此题。


```cpp
#include<bits/stdc++.h>
#define at(x,y) (id[x][y])
using namespace std;

int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return f*x;
}

const int N = 1005;
int n,m,q,beg=1;
int a[N][N],fa[N*N],sz[N*N],cnt=0,id[N][N];
int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
struct Node{int x,y,a;bool operator<(const Node x)const{return a<x.a;};}b[N*N];

int find(int x){return fa[x]=(fa[x]==x?x:find(fa[x]));}
void merge(int x, int y){
	int fx=find(x),fy=find(y);if(fx==fy)return;
	if(sz[fx]>sz[fy])swap(fx,fy);fa[fx]=fy,sz[fy]+=sz[fx];
}

int main(){
	n=read(),m=read(),q=read();fa[0]=0,sz[0]=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		a[i][j]=read();b[++cnt]=Node{i,j,a[i][j]};id[i][j]=cnt;
		fa[at(i,j)]=at(i,j),sz[at(i,j)]=1;		
	}sort(b+1,b+1+cnt);
	for(int i=1;i<=q;i++){
		while(beg<=cnt){
			if(b[beg].a<=i){
				for(int j=0;j<4;j++){
					int nx=b[beg].x+dx[j],ny=b[beg].y+dy[j];
					if(1<=nx&&nx<=n&&1<=ny&&ny<=m)
					if(a[nx][ny]<=i)
					merge(at(b[beg].x,b[beg].y),at(nx,ny));
				}
				if(b[beg].x==1||b[beg].x==n||b[beg].y==1||b[beg].y==m)
				merge(at(b[beg].x,b[beg].y),0);
				beg++;
			}else break;
		}
		printf("%d\n",n*m-sz[find(0)]+1);
//	for(int i=0;i<=cnt;i++)printf("%d ",fa[i]);puts("");
//	for(int i=0;i<=cnt;i++)printf("%d ",sz[i]);puts("");		
	}

	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
我们要用优先队列来实现这道题。

首先将所有临海的地块全都加进优先队列，注意这个优先队列是按海拔从低到高排的，也就是说，海拔月底的在优先队列中的优先级越高。

然后设 $i$ 从 $1$ 枚举到 $Y$。如果当前状态下未被水淹的地块的最低的海拔大于第 $i$ 年的海平面高度或者队列空了，那么立即结束循环（因为现在这样水淹不到任何任何地块）。取出队列顶端元素，将答案加一（因为这个地块已经被水淹了），并且将这个区块周围的所有区块都加入队列里，因为这些区块已经临海了。

结束循环后，输出 $H \times W$ 减去已经被水淹了的地块的个数。

时间复杂度 $O(HW \log HW)$。
### 代码
```cpp
#include<iostream>
#include<queue>
#define int long long
#define N 1005
struct Node{
	int x,y;
	int height;
};
struct cmp{
	bool operator()(const Node&x,const Node&y) {
 return x.height>y.height;
 }
};
int n,m,y,h[N][N],ans;
bool vis[N][N];
const int dx[]={1,0,-1,0};
const int dy[]={0,1,0,-1};
signed main(){
	std::priority_queue<Node,std::vector<Node>,cmp>q;
	std::cin>>n>>m>>y;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			std::cin>>h[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i==1||j==1||i==n||j==m){
				q.push({i,j,h[i][j]});
				vis[i][j]=1;
			}
		}
	}
	for(int i=1;i<=y;i++){
		while(q.size()){
			if(q.top().height>i)break;
			Node node=q.top();
			q.pop();
			ans++;
			for(int k=0;k<4;k++){
				int nx=node.x+dx[k];
				int ny=node.y+dy[k];
				if(nx>=1&&ny>=1&&nx<=n&&ny<=m&&!vis[nx][ny]){
					if(!vis[nx][ny]){
						q.push({nx,ny,h[nx][ny]});
						vis[nx][ny]=1;
					}
				}
			}
		}
		std::cout<<n*m-ans<<"\n";
	}
}
```

---

## 作者：Liyunze123 (赞：0)

# 题意
有一个 $n\times m$ 的岛屿，第 $i$ 行第 $j$ 列的海拔为 $a_{i,j}$。一开始海平面高度为 $0$，每年上升 $1$，上升 $P$ 年。在边界且海拔 $\le$ 海平面高度的点会沉没。问你每年结束有多少个点没沉没？
# 解法
如果一个边界点沉没了，那么相邻的点，如果没沉没就变成边界。我们对边界维护一个优先队列，将坐标、海拔存进去，按海拔递增排序。每次将优先队列里所有海拔 $\le i$ 的点取出并沉没该点。之后，如果相邻的四个点没出界、没沉没、没放进队列中，就把它放进去。最后统计下没沉末的点的个数就行了。统计点个数要 $O(nm)$，总时间复杂度 $O(nmP)$，超时。

我们可以计一个变量 $ans$，初始值是 $nm$，每沉没一个点就减一。$ans$ 就是没沉没的点个数。
# 代码
```
#include<bits/stdc++.h>
#include<queue>
using namespace std;
int n,m,k,a[1010][1010],ans,f[1010][1010];
typedef pair<int,pair<int,int> >P;
priority_queue<P,vector<P>,greater<P> >t;
int main(){
	scanf("%d%d%d",&n,&m,&k),ans=n*m;
	for(int w=1;w<=n;w++)for(int x=1;x<=m;x++){
		scanf("%d",&a[w][x]);
		if(w==1||w==n||x==1||x==m)t.push({a[w][x],{w,x}}),f[w][x]=1;
	}
	for(int w=1;w<=k;w++){
		while(t.top().first<=w&&t.size()){
			int i=t.top().second.first,j=t.top().second.second;
			f[i][j]=2,ans--,t.pop();
			if(i-1>=1&&!f[i-1][j])t.push({a[i-1][j],{i-1,j}}),f[i-1][j]=1;
			if(i+1<=n&&!f[i+1][j])t.push({a[i+1][j],{i+1,j}}),f[i+1][j]=1;
			if(j-1>=1&&!f[i][j-1])t.push({a[i][j-1],{i,j-1}}),f[i][j-1]=1;
			if(j+1<=m&&!f[i][j+1])t.push({a[i][j+1],{i,j+1}}),f[i][j+1]=1;
		}
		printf("%d\n",ans);
	}
    return 0;
}
```

---

## 作者：cqbzhr (赞：0)

这道题容易想到泛洪填充。可以用它来计算海岛每一年高于海平面的面积。

先读取岛的高度信息，构建一个二维数组来表示岛的每个位置的海拔高度。

从任意一个起始点开始，遍历所有与起始点相连且高度高于海平面的区域，并用 $vis$ 数组将它们标记为已访问过的状态。然后，从海平面初始高度开始，每年海平面上升 $1$。并且对于每次海平面上升，需要重新计算每个高于海平面的区域。最后计算岛屿经过 $i$ 年后仍高于海平面的面积即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
queue<int> q[100005];
int h,w,y,ans,a[1005][1005],mp[1005][1005];
void bfs(int i){
	while(!q[i].empty()){
		ans--;
		int z=q[i].front();
		int sx=z/w,sy=z%w;
		q[i].pop();
		for(int j=0;j<4;j++){
			if(sx+dx[j]>=0&&sx+dx[j]<h&&sy+dy[j]>=0&&sy+dy[j]<w&&mp[sx+dx[j]][sy+dy[j]]){
				q[max(a[sx+dx[j]][sy+dy[j]],i)].push(w*(sx+dx[j])+(sy+dy[j]));
				mp[sx+dx[j]][sy+dy[j]]=0;
			}
		}
	}
}
int main(){
	cin>>h>>w>>y;
	ans=h*w;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cin>>a[i][j];
			if(i==0||i==h-1||j==0||j==w-1){
				q[a[i][j]].push(w*i+j);
				mp[i][j]=0;
			}
			else mp[i][j]=1;
		}
	}
	for(int i=1;i<=y;i++){
		bfs(i);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

在下面我们定义 $n$ 为题面中的 $H$，$m$ 为题面中的 $W$，$q$ 为题面中的 $Y$

一种 dfs 做法，场上不到 $10$ 分钟就场切了。

我们定义“沿海城市”为在它四联通的的范围内有水的城市，那么一开始在第 $1$ 行，第 $1$ 列，第 $n$ 行，第 $m$ 列都是沿海的。

那么我们设 $vis_{i,j}$ 表示 $(i,j)$ 是否被淹没，$ans$ 为没被淹没的城市数：

我们在第 $x$ 天可以在整个网格中寻找满足下述条件的城市：

- $(i,j)$ 沿海；
- $a_{i,j}\le x$；
- $vis_{i,j}=0$。

那么这样 $(i,j)$ 肯定会被淹没，把 $vis_{i,j}$ 设为 $1$，这一步可以用 dfs 解决，注意最劣总共需要扩展 $nm$ 次。

可是这样是 $O(nmq)$ 的，需要优化。

我们注意到一个点最多被成功扩展一次，那么我们就可以用一个堆来存储所有的“沿海城市”，每次轮流取出堆顶即可。

这样复杂度是 $O(nm\log nm+q)$ 完美通过。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,pair<int,int>>

const int N=1005;
int n,m,Y,ans;
int a[N][N];
bool vis[N][N];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
priority_queue<pii,vector<pii>,greater<pii>> qp;

void dfs(int x,int y,int z){
	vis[x][y]=1;
	ans--;
	for(int i=0;i<4;i++){
		int fx=x+dx[i],fy=y+dy[i];
		if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!vis[fx][fy]&&a[fx][fy]<=z){
			dfs(fx,fy,z);
		}
		else if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&!vis[fx][fy]){
			qp.push({a[fx][fy],{fx,fy}});
		}
	}
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m>>Y;
	ans=n*m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(i==1||i==n||j==1||j==m) qp.push({a[i][j],{i,j}});
		}
	}
	for(int i=1;i<=Y;i++){
		while(!qp.empty()&&qp.top().first<=i){
			pii f=qp.top();
			qp.pop();
			if(!vis[f.second.first][f.second.second]){
				dfs(f.second.first,f.second.second,i);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Otue (赞：0)

因为水只会从边界开始往中间蔓延，所以先将边界的所有点加入队列，用优先队列维护边界线。

每次弹出海拔最小的点，再把周围没有遍历的点加进去。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 1005;

int n, m, K, a[N][N], vis[N][N], vv[N][N], ans, vvv[N][N];


struct stu {
	int val, x, y;
	bool operator > (const stu &a) const {
		return val > a.val;
	}
};

priority_queue<stu, vector<stu>, greater<stu>> q;
int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};
	


signed main() {
	cin >> n >> m >> K;
	_for(i, 1, n) _for(j, 1, m) cin >> a[i][j];
	_for(i, 1, n) _for(j, 1, m) {
		if (i == 1 || i == n || j == 1 || j == m) q.push({a[i][j], i, j}), vv[i][j] = 1, vvv[i][j] = 0;
	}
	ans = n * m;
	_for(i, 1, K) {
		while (q.size() && q.top().val <= i) {
			auto t = q.top();
			int x = t.x, y = t.y;
			if (a[x][y] <= i) {
				ans--;
				q.pop();	
				_for(j, 0, 3) {
					int dx = x + dir[j][0], dy = y + dir[j][1];
					if (dx < 1 || dx > n || dy < 1 || dy > m) continue;
					if (!vv[dx][dy]) vv[dx][dy] = 1, q.push({a[dx][dy], dx, dy});
				}
			}  
		}
		cout << ans << endl;
	}
}
```

---

## 作者：__O_v_O__ (赞：0)

这里，我们称第一行，最后一行，第一列，最后一列的城市为岸边城市。

显然，我们可以得到一个性质：一个城市被淹没，当且仅当存在一条此城市到岸边城市的路径，使得路径上所有城市高度都小于当前年数。

所以，我们使用 bfs 的思想，先把所有岸边城市的高度加入优先队列，每次取出最小的高度，向四周扩散。如果扩散到的城市高度小于当前年数，则将沉没数增加 1，否则跳过。直到优先队列中最矮的城市都大于当前年数再停止。

注意，这里需要维护一个标记数组，存储每个城市有没有访问过，否则一个高度很矮的城市会被多次入队。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,y,a[1001][1001],an;
struct A{
	int x,y;
	bool operator<(const A&o)const{
		return a[x][y]>a[o.x][o.y];
	}
};
priority_queue<A>q;
bool vi[1001][1001];
int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>y,an=n*m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			cin>>a[i][j];
			if(i==1||i==n||j==1||j==m)
				q.push({i,j}),vi[i][j]=1;
		}
	for(int i=1;i<=y;++i){
		while(!q.empty()){
			A t=q.top();
			int x=t.x,y=t.y;
			if(a[x][y]>i)break;
			q.pop(),an--;
			for(int k=0;k<4;++k){
				int tx=x+dx[k],ty=y+dy[k];
				if(tx<1||tx>n||ty<1||ty>m||vi[tx][ty])continue;
				vi[tx][ty]=1,q.push({tx,ty});
			}
		}
		cout<<an<<'\n';
	}
	return 0;
}
```

---

## 作者：fydj (赞：0)

用一个优先队列维护和海相邻的位置，每次海面上升就判断一下队列中海拔最低的那个位置会不会被淹没，如果会，就删除，同时它上下左右的位置也是和海相邻的（或者就在海里），把它们加进优先队列里，记得判断一下加入的格子曾经有没有被加入过队列，不要加重复了。

```cpp
const int N=1099;
int n,m,q,h[N][N]={},ans;
bool ind[N][N]={};
struct note {
	int x,y;
	friend bool operator < (const note a,const note b) {
		return h[a.x][a.y]>h[b.x][b.y];
	}
}; priority_queue<note> que;
void put(int x,int y) {
	if(x<1||y<1||x>n||y>m)
		return ;
	if(!ind[x][y])
		que.push((note){x,y}),
		ind[x][y]=true;
	return ;
}
int main()
{
	int i,j,x,y;
	read(n,m,q);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			read(h[i][j]);
	ans=n*m;
	for(i=1;i<=n;++i)
		put(i,1),put(i,m);
	for(i=1;i<=m;++i)
		put(1,i),put(n,i);
	for(i=1;i<=q;++i) {
		while(!que.empty()&&h[que.top().x][que.top().y]<=i)
			--ans,x=que.top().x,y=que.top().y,que.pop(),
			put(x+1,y),put(x,y+1),put(x-1,y),put(x,y-1);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

注意到可以记录值为 $i$ 的格子的位置，可以使用 vector 存一下，然后考虑搜索，具体的如果周围有海洋就加入队列，其中扩展的时候还要考虑一下周围的格子有没有会沉的即可。

时间复杂度为 $O(nm)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e3+5,M=1e5+5;
struct Point{
	int x,y;
};
int n,m,k,a[N][N],ans,dx[]={0,0,-1,1},dy[]={-1,1,0,0};
bool vis[N][N],bj[N][N];
vector <Point> e[M];
queue <Point> q;
void work(int tmp){
	for(int i = 0;i < e[tmp].size();i++){
		Point tlh=e[tmp][i];
		if(!vis[tlh.x][tlh.y])continue;
		for(int j = 0;j < 4;j++){
			int nowx=tlh.x+dx[j],nowy=tlh.y+dy[j];
			if(!vis[nowx][nowy]){
				bj[tlh.x][tlh.y]=1;
				q.push((Point){tlh.x,tlh.y});
				break;
			}
		}
	}
	while(!q.empty()){
		Point head=q.front();
		q.pop();
		if(!vis[head.x][head.y])continue;
		vis[head.x][head.y]=0;
		ans--;
		for(int i = 0;i < 4;i++){
			int nowx=head.x+dx[i],nowy=head.y+dy[i];
			if(nowx<1||nowx>n||nowy<1||nowy>m)continue;
			if(!vis[nowx][nowy])continue;
			if(a[nowx][nowy]<=tmp){
				if(!bj[nowx][nowy]){
					bj[nowx][nowy]=1;
					q.push((Point){nowx,nowy});
				}
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> k;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> a[i][j];
			vis[i][j]=1;
			e[a[i][j]].push_back((Point){i,j});
		}
	}
	ans=n*m;
	for(int i = 1;i <= k;i++){
		work(i);
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：UnfortunatelyDead (赞：0)

考虑使用一个小根堆存储与海面相邻的位置，然后枚举 $i$，表示这是第 $i$ 天。

对于当前 $i$，小根堆里每个 $\leq i$ 的数都会被淹没，那么与该位置四个方向的位置也会变成临海。

不难发现小根堆里的数每次取堆顶一定可以代表一个最小的数，而如果它无法被水淹没，其他肯定也不可能。

[代码](https://atcoder.jp/contests/abc363/submissions/55801436)，赛时降智吃了一发罚时。

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑对于每个点求出其被淹没的最早时间。

注意到是图论问题，可以使用 dijkstra 算法，每次找到淹没时间最早的点去更新其它点的答案。

时间复杂度为 $O(NM \log NM)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=1010,M=1e7+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll u;
	ll dis;
	bool operator<(const Node&rhs)const{
		return dis>rhs.dis;
	}
};
ll n,m,k,cnt;
ll a[N][N],id[N][N],ans[M];
ll dis[M];
pair<ll,ll> h[M];
bool f[M];
ll dx[]={0,0,1,-1},dy[]={1,-1,0,0};
priority_queue<Node> Q;
void bfs(){
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    if(i==1||j==1||i==n||j==m)
	      Q.push({id[i][j],a[i][j]}),dis[id[i][j]]=a[i][j];
	while(!Q.empty()){
		ll u=Q.top().u,w=Q.top().dis;
		Q.pop();
		if(f[u])
		  continue;
		f[u]=1;
		for(int i=0;i<4;i++){
			ll zx=h[u].first+dx[i],zy=h[u].second+dy[i];
			if(zx<1||zx>n||zy<1||zy>m)
			  continue;
			if(dis[id[zx][zy]]>w&&w>=a[zx][zy]){
				dis[id[zx][zy]]=w;
				Q.push({id[zx][zy],w});
			}
			else if(w<a[zx][zy]){
				dis[id[zx][zy]]=a[zx][zy];
				Q.push({id[zx][zy],a[zx][zy]});
			}
		}
	}
}
bool End;
int main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=m;j++){
	    	a[i][j]=read();
	    	id[i][j]=++cnt;
	    	h[cnt]={i,j};
	    	dis[cnt]=1e18;
		}
	}
	bfs();
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=m;j++){
//			write(dis[id[i][j]]);
//			putchar(' ');
//		}
//		putchar('\n');
//	}
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    if(dis[id[i][j]]<=k)
	      ans[dis[id[i][j]]]++;
	for(int i=1;i<=k;i++){
		ans[i]+=ans[i-1];
		write(n*m-ans[i]);
		putchar('\n');
	}
	cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

