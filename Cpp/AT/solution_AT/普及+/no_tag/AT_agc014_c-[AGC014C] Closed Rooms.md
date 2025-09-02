# [AGC014C] Closed Rooms

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc014/tasks/agc014_c

高橋君は建物の中に閉じ込められてしまいました。

この建物は $ H $ 行 $ W $ 列に並んだ $ H×W $ 個の部屋からなり、上から $ i $ 行目、左から $ j $ 列目の部屋は $ (i,j) $ で表され、その部屋の状態は $ A_{i,j} $ で表されています。 $ A_{i,j}= $ `#` の場合は、この部屋は閉じられており、$ A_{i,j}= $ `.` の場合は、この部屋には自由に出入りできます。 そして、 $ A_{i,j}= $ `S` となる部屋が高橋君の今いる部屋です。ただし、高橋君が今いる部屋も自由に出入りできる部屋です。

また、$ 1 $ 行目、$ 1 $ 列目、$ H $ 行目、$ W $ 列目のいずれかに含まれる部屋は建物の外につながっており、 それ以外の各部屋 $ (i,j) $ は $ 4 $ つの部屋 $ (i-1,j) $ $ , $ $ (i+1,j) $ $ , $ $ (i,j-1) $ $ , $ $ (i,j+1) $ と隣接しています。

高橋君はこの建物から脱出するために魔法を使うことにしました。一回の魔法で高橋君は以下の操作ができます。

- 高橋君は今いる部屋から隣り合う部屋に移動することを $ K $ 回まで繰り返す。ただし、閉じられている部屋には移動することはできない。
- その後、閉じられている部屋を $ K $ 個まで選び、それらを開いた状態にする。それらの部屋は以降自由に出入りできるようになる。

ただし、これらの操作では、全く動かなかったり、閉じられている部屋があっても開かなかったりしてもよいです。

高橋君の目標は建物の外につながっている部屋のいずれかにたどり着くことです。そのために必要な魔法の回数の最小値を求めてください。

ただし、はじめに高橋君がいる部屋は建物の外とはつながっていないことが保証されています。

## 说明/提示

### 制約

- $ 3\ ≦\ H\ ≦\ 800 $
- $ 3\ ≦\ W\ ≦\ 800 $
- $ 1\ ≦\ K\ ≦\ H×W $
- $ A_{i,j} $ は `#` , `.` , `S` のいずれかである。
- $ A_{i,j}= $ `S` となる $ (i,j) $ は一意に存在し、$ 2\ ≦\ i\ ≦\ H-1\ ,\ 2\ ≦\ j\ ≦\ W-1 $ を満たす。

### Sample Explanation 1

高橋君は最初の魔法で部屋 $ (1,2) $ に移動することができるので、$ 1 $ 回の魔法で十分です。

### Sample Explanation 2

高橋君は最初の魔法では移動することができないですが、部屋 $ (1,2) $ を $ 1 $ 回目の魔法で開けることができます。 そして、次の魔法で部屋 $ (1,2) $ に移動することで、$ 2 $ 回の魔法で目標を達成できます。

## 样例 #1

### 输入

```
3 3 3
#.#
#S.
###```

### 输出

```
1```

## 样例 #2

### 输入

```
3 3 3
###
#S#
###```

### 输出

```
2```

## 样例 #3

### 输入

```
7 7 2
#######
#######
##...##
###S###
##.#.##
###.###
#######```

### 输出

```
2```

# 题解

## 作者：Rigel (赞：10)

## 思路

每轮先移动至多 $K$ 步，再解锁 $K$ 个格子。这等价于第 $1$ 轮先移动至多 $K$ 次，此后每轮先解锁 $K$ 个格子，再移动至多 $K$ 步。不难发现，从第 $2$ 轮开始可以自由移动，因为走到的每个格子均可先解锁。

我们使用 BFS 找出第 $1$ 轮在 $K$ 步之内能到达的所有格子，再找出这些格子中离边界最近的格子。

设一个格子与边界的距离为 $dis$，则通过这段距离需要 $\lceil \displaystyle{\frac{dis}{K}}\rceil$ 轮。

加上第 $1$ 轮，最终答案为 $\lceil \displaystyle{\frac{dis}{K}}\rceil + 1$。

时间复杂度为 $\mathcal{O}(H \times W)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x7fffffffffffffff
#define maxn 805

using namespace std;

int n,m,k,a[maxn][maxn],ans=INF;
int sx,sy;
int vis[maxn][maxn];

struct node{
	int x,y,stp;
}q[maxn*maxn];

const int f[4][2]={{-1,0},{0,-1},{1,0},{0,1}};

inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}

inline int read1(int x,int y){
	char ch=getchar();
	while(ch!='#'&&ch!='.'&&ch!='S')ch=getchar();
	if(ch=='S')sx=x,sy=y;
	return ch=='#';
}

bool chk(int x,int y){
	if(x<1||y<1||x>n||y>m)return 0;
	return !(a[x][y]||vis[x][y]);
}

void bfs(){
	int hed=0,til=1;
	q[1]=(node){sx,sy,0},vis[sx][sy]=1;
	while(hed!=til){
		hed++;
		if(q[hed].stp==k)continue;
		int x=q[hed].x,y=q[hed].y;
		for(int i=0;i<=3;i++){
			int _x=x+f[i][0],_y=y+f[i][1],stp=q[hed].stp+1;
			if(!chk(_x,_y))continue;
			q[++til]=(node){_x,_y,stp};
			vis[_x][_y]=1;
		}
	}
}

void _solve(int x,int y){
	int dis=min(min(x-1,n-x),min(y-1,m-y)); // 该格子与边界的最短距离
	int t=dis/k;
	if(dis%k)t++;
	ans=min(ans,t);
}

signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=read1(i,j);
	bfs();
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(vis[i][j])_solve(i,j);
	printf("%lld\n",ans+1);
	return 0;
}

---

## 作者：installb (赞：5)

一轮为先移动至多 $K$ 次再把 $K$ 个 `#` 变为 `.`。  

这样感觉不好处理，我们把它转换一下：  
- 在最开始的时候先走，至多走 $K$ 步。  
- 第一次走完后，每一轮解开 $K$ 个 `#`，然后走至多 $K$ 步。  

如果这么做，在接下来的每一轮中，直接解开我要走的那 $K$ 步的格子上的锁就可以了。  

所以这题就是问第一轮最多可以走到离边界多近的地方。  
直接 bfs 走 $K$ 层，问题解决。  
设最近距离为 $x$，一轮走 $K$，再加上第一步，答案就是 $\lceil \frac{x}{K} \rceil+1$。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;

LL vis[805][805] = {0};
char ch[805][805];
LL n,m,k,ans = INF;
LL dx[4] = {0,0,1,-1};
LL dy[4] = {1,-1,0,0};

struct node{
	LL x,y,stp;
}h,t; queue <node> q;
void bfs(LL x,LL y){
	t.x = x; t.y = y; t.stp = 0; q.push(t);
	while(!q.empty()){
		h = q.front(); q.pop();
		if(h.stp > k) continue;
		vis[h.x][h.y] = 1;
		ans = min(ans,min(min(h.x - 1,h.y - 1),min(n - h.x,m - h.y)));
		for(LL i = 0;i < 4;i ++){
			LL tx = h.x + dx[i],ty = h.y + dy[i];
			if(!tx || !ty || tx > n || ty > m) continue;
			if(vis[tx][ty] || ch[tx][ty] == '#') continue;
			vis[tx][ty] = 1;
			t.x = tx; t.y = ty; t.stp = h.stp + 1;
			q.push(t);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	LL sx = 0,sy = 0;
	cin >> n >> m >> k;
	for(LL i = 1;i <= n;i ++){
		for(LL j = 1;j <= m;j ++){
			cin >> ch[i][j];
			if(ch[i][j] == 'S'){ sx = i; sy = j; }
		}
	}
	bfs(sx,sy);
	cout << (ans + k - 1) / k + 1 << endl;
	return 0;
}
```

原评分 $\sf{\color{blue}1905}$  
感觉没这个难度吧，还是比较好想的，前置知识只有 bfs，代码难度（实现难度）低。

---

## 作者：chen_kun (赞：2)

# 题解：AT_agc014_c [AGC014C] Closed Rooms

[AC 记录。](https://atcoder.jp/contests/agc014/submissions/65999059)

## 思路简述

其实挺简单的，主要是要把题目的意思简化一下。

虽然题目说每次走完 $k$ 步才能解锁其他上锁的位置，但是仔细观察就会发现其实这个限制只对第一轮有效，从第二轮开始这个限制就可以转化为想走到哪就走到哪，因为你走的步数与解锁的格子数是相同的。

那么我们就用 **BFS** 把第一轮可以到的格子都遍历一遍，把其中离边缘最近的距离一次记录下来。最后用这个距离除以 $k$ 再判断一下整除就可以算出接下来走到边缘所需的轮数。

## 代码呈现


### C++


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,ax,ay,mmin=LLONG_MAX,dx[5]={1,-1,0,0},dy[5]={0,0,1,-1},vis[888][888];
char a[888][888];
void bfs(){
	queue<pair<int,pair<int,int> > >q;
	q.push({0,{ax,ay}});
	vis[ax][ay]=1;
	while(!q.empty()){
		int cnt=q.front().first,x=q.front().second.first,y=q.front().second.second;//cnt用于判断第一轮所走的步数是否超过了k 
		q.pop();
		mmin=min(mmin,min(min(x-1,n-x),min(y-1,m-y)));//判断离边缘最近的一次时的距离。 
		for(int i=0;i<4;i++){
			int tx=x+dx[i],ty=y+dy[i];
			if(!vis[tx][ty]&&tx>0&&ty>0&&tx<=n&&ty<=m&&a[tx][ty]!='#'&&cnt<k) vis[tx][ty]=1,q.push({cnt+1,{tx,ty}});
		}
	}
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j]=='S') ax=i,ay=j;//记录起点 
		}
	}
	bfs();
	cout<<mmin/k+1+(!(mmin%k==0));//在走第一轮的基础上加上之后所需轮数，如果不能整除还要再来一轮 
    return 0;
}
```
## The end.

---

## 作者：huhexuan (赞：2)

做出的第一道AGC的题，写篇题解纪念一下。

首先就这题而言，很明显是一道搜索题，但这题常数较大不能用 DFS 来写，那就用 BFS。

容易发现，对于除了第一次操作之外的每一次操作，都可以理解为边走边开锁。因为第一次操作会把第二次操作要经过的锁打开，第二次操作会把第三次操作要经过的锁打开，以此类推。

换句话说，除了第一次操作之外，其他的每一次操作都完全不受锁的影响。这道题也就可以转换为求出第一次操作后距离边界的最近距离，用 BFS 求解即可。

设这个距离为 $ans$,则答案为 $\lceil ans/k \rceil+1$。 

其中 $\lceil ans/k \rceil$ 就是除了第一轮之外的轮数，这个式子在代码中可以用 $(ans+k-1)/k$ 实现。

代码如下：
```cpp
//在这道题中，'#'为未解锁的格子，'S'为起点，'.'为已解锁的格子
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,k,stx,sty,cnt=2e9;
char a[1000][1000]; 
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
struct node{
	int x,y,step;
};
bool vis[1000][1000];
queue<node>q;
void bfs(int x,int y,int step)
{
	q.push({x,y,step});
	while(!q.empty())
	{
		node h=q.front();
		q.pop();
		if(h.step>k) continue;
		cnt=min(cnt,min(n-h.x,m-h.y));
		cnt=min(cnt,min(h.x-1,h.y-1));//这里求的是距离边界的最小距离 
		vis[h.x][h.y]=1;
		for(int i=0;i<4;i++)
		{
			int fx=dx[i]+h.x,fy=dy[i]+h.y;
			if(fx>=1&&fy>=1&&fx<=n&&fy<=m&&!vis[fx][fy]&&a[fx][fy]!='#')
			{
				q.push({fx,fy,h.step+1});
				vis[fx][fy]=1;
			}
		}
	}
}
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='S') stx=i,sty=j; 
		} 
	}
	if(stx==1||sty==1)
	{
		cout<<0;
		return 0;
	} 
	bfs(stx,sty,0); 
	cout<<(cnt+k-1)/k+1<<"\n";
    return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 前言
~~该长脑子了~~。
# 思路
首先我们可以分析题面发现一次最多走 $k$ 次二最多也能开 $k$ 个锁所以我们考虑将每一次开锁弄到走之前这也很简单，先提前走一次即可，因为这样做可以保证以后走的路都畅通无阻，那么对于第一次直接暴搜即可，然后求出每一个点到四面的最短距离，假如为 $res$，那么答案就是 $\lceil \frac{res}{k} \rceil+1$ 因为要加上第一轮。
# 代码
关于深搜啊，他死掉了，还是写广搜吧。
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define int long long
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
int n,m,k;
const int N=810;
char c[N][N];
int tx[]={0,-1,0,1};
int ty[]={-1,0,1,0};
int qx,qy,res=INT_MAX;
int vis[N][N];
struct node{
	int x,y,s;
};
queue<node>q;
void bfs() {
	while(q.size()) {
		node s=q.front();
		q.pop();
		int x=s.x,y=s.y,z=s.s;
		if(z>k) continue;
		res=min(res,min(min(x-1,y-1),min(n-x,m-y)));
		vis[x][y]=1;
		rep(i,0,3) {
			int dx=x+tx[i],dy=y+ty[i];
			if(dx<1||dy<1||dx>n||dy>m||c[dx][dy]=='#'||vis[dx][dy]) continue;
			vis[dx][dy]=1;
			q.push({dx,dy,z+1});
		}
	}
}
void solve() {
	in(n),in(m),in(k);
	rep(i,1,n) rep(j,1,m) {
		cin>>c[i][j];
		if(c[i][j]=='S') qx=i,qy=j;
	}
	q.push({qx,qy,0});
	bfs();
	cout<<(res+k-1)/k+1<<endl;
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：_FL_ (赞：1)

## $ \texttt{AT2375} $  

---

### 思路：  

第一道自己做出的 AGC 题，虽然这道题比较水。  

仔细观察会发现，在第一轮之后可以打开 $ k $ 个点和走 $ k $ 步，这就相当于没有障碍物直接走。  

所以主要保证第一轮尽量走到靠近边界的位置就行。  

那么直接 BFS，找到和边界距离的最小值 $ min $，则答案为 $ 1+\lceil\dfrac{min}{k}\rceil $  

---

### 代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 8e2 + 5;
struct Node {
	int Xi, Yi, DIS;
};
int n, m, k1, ans = 1, minn, sx, sy;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
char str1[N][N], ch;
bool vis[N][N];
queue<Node> q1;
void BFS();
int main() {
	scanf("%d%d%d", &n, &m, &k1);//循环有的时候要用k所以k1好习惯
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ch = getchar();
			while (ch != '.' && ch != '#' && ch != 'S') {
				ch = getchar();
			}
			if (ch == 'S') {
				ch = '.';
				sx = i;
				sy = j;
				minn = min(min(i - 1, n - i), min(j - 1, m - j));
				//起点,第一轮可以不动
			}
			str1[i][j] = ch;//getchar读入比较优秀
		}
	}
	BFS();
	ans += (minn + k1 - 1) / k1;//向上取整
	printf("%d", ans);
	return 0;
}
void BFS() {
	//都来刷AGC了不至于不会BFS
	while (!q1.empty()) {
		q1.pop();//清空好习惯
	}
	vis[sx][sy] = 1;
	q1.push((Node){sx, sy, 0});//存下点的位置和走了多少步
	while (!q1.empty()) {
		int x = q1.front().Xi;
		int y = q1.front().Yi;
		int dis = q1.front().DIS;
		q1.pop();
		minn = min(minn, min(min(x - 1, n - x), min(y - 1, m - y)));
		//注意与边界的距离别写错
		if (dis >= k1) {
			continue;//走够k步就不能再走
		}
		for (int i = 0; i < 4; i++) {
			int tx = x + dx[i];
			int ty = y + dy[i];
			if (tx < 1 || ty < 1 || tx > n || ty > m || vis[tx][ty] || str1[tx][ty] == '#') {
				continue;
			}
			vis[tx][ty] = 1;
			q1.push((Node){tx, ty, dis + 1});
		}
	}
	return;
}
```


---

## 作者：勿忘安己 (赞：1)

## 题目大意
一个网格图，从一个起点出发。有些格子上锁。每一轮你都可以不断往一个已解锁的四个方向的相邻格子走，最多走k次走完后你可以选择至多k个未解锁的格子，将它们解锁。求最少多少轮，你能走到一个边界格子。
## 思路
因为只有第一次的前k次是无法自己解锁格子的，但是之后我们完全可以通过解锁格子然后走到任何地方（走的次数和可以解锁的次数相等），因此bfs求出第一轮能走到的格子，然后计算到边界最小轮数。
```cpp
#include<bits/stdc++.h>
const int maxn=8e2+10;
using namespace std;
char a[maxn][maxn];
int stmp[maxn][maxn];//代表这是bfs的第几步
int direction[4][2]={1,0,-1,0,0,1,0,-1};//四个方向
int n,m,k;
int ans=99999999;
bool check(int x,int y)//判断这个点是否可行
{
    if(x>=0&&x<n&&y>=0&&y<m&&stmp[x][y]==0&&a[x][y]=='.')
    {
       return 1;
    }
    return 0;
}
queue<pair<int,int> >po;
int main()
{
    cin>>n>>m>>k;
    int sx,sy;
    getchar();
    for(int i=0;i<n;i++)//输入顺便找到起点
    {
        for(int j=0;j<m;j++)
        {
            scanf("%c",&a[i][j]);
            if(a[i][j]=='S')
            {
                sx=i;
                sy=j;
            }
        }
        getchar();
    }
    stmp[sx][sy]=1;
    po.push(make_pair(sx,sy));
    while(!po.empty())
    {
        int x=po.front().first;
        int y=po.front().second;
        ans=min(ans,min(min(x,n-x-1),min(y,m-y-1)));
        po.pop();
        for(int i=0;i<4;i++)
        {
            int xx=x+direction[i][0];
            int yy=y+direction[i][1];
            if(check(xx,yy)&&stmp[x][y]<=k)
            {
               stmp[xx][yy]=stmp[x][y]+1;
               po.push(make_pair(xx,yy));
            }
        }
    }
    int anss;
    anss=1+(ans+k-1)/k;//向上取整
    cout<<anss<<endl;
    return 0;
}

```


---

## 作者：听取MLE声一片 (赞：1)

注意是先移动再清。

容易想到的，我们可以从起点走到一个位置，然后朝一个方向解锁，之后朝着那个方向一直冲过去即可。而且第一次走是不能解锁的。

题目转化为在 $k$ 步之内移动使得其距离边界最小并求出最小值。

我们从起点开始 bfs，保证到起点距离不超过 $k$，每移动一次更新一次最小值。

答案显然是最小距离需要走多少步再加上 $1$，注意要向上取整。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=810;
int n,m,k,x,y,xx[4]={-1,1,0,0},yy[4]={0,0,-1,1},len=1e9,vis[N][N];
char a[N][N];
void find(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='S'){
				x=i;
				y=j;
				return;
			}
}
struct point{
	int x,y,s;
};
void bfs(){
	queue<point>q;
	q.push({x,y,0});
	vis[x][y]=1;
	while(!q.empty()){
		point p=q.front();
		q.pop();
		int res=min(min((p.x-1),(n-p.x)),min((p.y-1),(m-p.y)));
		len=min(len,res);
		if(p.s==k)
			continue;
		for(int i=0;i<4;i++){
			int tx=p.x+xx[i],ty=p.y+yy[i];
			if(a[tx][ty]!='.'||vis[tx][ty])
				continue;
			vis[tx][ty]=1;
			q.push({tx,ty,p.s+1});
		}
	}
}
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		scanf("%s",a[i]+1);
	find();
	bfs();
	int ans=1+(len+k-1)/k;
	cout<<ans;
	return 0;
}

```


---

## 作者：Celtic (赞：0)

由于每一轮结束时能解锁的房间数和能走的步数相同，都为 $k$，所以除了第一天外，每天晚上解锁的房间都应该是给第二天走的房间做准备的。于是枚举第一天走到哪，这可以通过 bfs 来实现。然后求一下他到四个边界的最短距离就行了。复杂度 $O(nm)$

```cpp
// ubsan: undefined
// accoders
#include<bits/stdc++.h>
#define N 501001
#define MAX 2005
char buf[1<<18],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++)
using namespace std;
typedef long long ll;
typedef double db;
const ll mod=998244353,inf=1e18;
inline void read(ll &ret)
{
	ret=0;char c=getchar();bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
char a[MAX][MAX];
ll t,n,m,k,sx,sy,dis[MAX][MAX];
ll dx[5]={0,-1,0,1,0};
ll dy[5]={0,0,1,0,-1};
struct node
{
	ll x,y,deep;
};
signed main()
{
		read(n);
		read(m);
		read(k);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				dis[i][j]=inf;
				a[i][j]=getchar();
				while(a[i][j]!='#'&&a[i][j]!='S'&&a[i][j]!='.')
					a[i][j]=getchar();
				if(a[i][j]=='S')
					sx=i,sy=j;
			}
		queue<node>q;
		q.push(node{sx,sy,0});
		dis[sx][sy]=0;
		while(!q.empty())
		{
			ll x=q.front().x,y=q.front().y,deep=q.front().deep;
			q.pop();
			for(int i=1;i<=4;i++)
			{
				ll nx=x+dx[i],ny=y+dy[i];
				if(nx<=0||nx>n||ny<=0||ny>m||a[nx][ny]=='#'||dis[nx][ny]!=inf)
					continue;
				dis[nx][ny]=deep+1;
				q.push(node{nx,ny,deep+1});
			}
		}
		ll ans=inf;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(dis[i][j]<=k)
					ans=min(ans,(dis[i][j]||(i!=1&&i!=n&&j!=1&&j!=m))+min({(i-1)/k+((i-1)%k!=0),(j-1)/k+((j-1)%k!=0),(n-i)/k+((n-i)%k!=0),(m-j)/k+((m-j)%k!=0)}));		
			}
		}
		printf("%lld\n",ans);
	exit(0);
}
```

---

