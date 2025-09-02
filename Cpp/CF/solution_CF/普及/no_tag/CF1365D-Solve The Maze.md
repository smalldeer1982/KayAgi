# Solve The Maze

## 题目描述

给出一个 $n$ 行 $m$ 列的网格，每个格子上有四种情况：
- `.` 表示这个格子是空地。
- `#` 表示这个格子是墙。
- `G` 表示这个格子是好人。
- `B` 表示这个格子是坏人。

`G`，`B`格子都可以认为是空地。

你需要判断能否 `.` 格子上放任意数量的墙，保证所有好人可以通过在空地间移动到达点 $(n,m)$ 而所有坏人都不行。

## 样例 #1

### 输入

```
6
1 1
.
1 2
G.
2 2
#B
G.
2 3
G.#
B#.
3 3
#B.
#..
GG.
2 2
#B
B.```

### 输出

```
Yes
Yes
No
No
Yes
Yes```

# 题解

## 作者：Refined_heart (赞：4)

题目大意：能否将坏人包围起来，不让他们走到$(n,m).$

$\text{Solution:}$

对于一个$\text{Bad Point.}$如果有一个$\text{Good Point}$可以和他走到一起的话，显然这个游戏是不可能胜利的。

那么，我们直接将每一个$\text{Bad Point.}$封锁在里面，让他哪里都不能去。

如果在这种情况下有$\text{Good Point.}$到达不到终点，那么显然的是，它一定会和一个$\text{Bad Point}$走到一起。

那么，进行这样一次全方位封锁后，从终点开始$bfs$走到所有可以到达的点，最后判断一下是不是所有的$\text{Good Point}$都可以到达终点即可。

时间复杂度$O(Tnm).$

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a[60][60],vis[60][60];
vector<pair<int,int> >v,b;
char s[60][60];
const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
void bfs(int x,int y){
	vis[x][y]=1;
	for(int i=0;i<4;++i){
		int nx=x+dx[i],ny=y+dy[i];
		if(vis[nx][ny]||nx<1||ny<1||nx>n||ny>m||a[nx][ny]==1)continue;
		bfs(nx,ny);
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);v.clear(),b.clear();
		for(int i=1;i<=50;++i)for(int j=1;j<=50;++j)vis[i][j]=a[i][j]=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				cin>>s[i][j];
				if(s[i][j]=='G')v.push_back(make_pair(i,j)),a[i][j]=2;
				if(s[i][j]=='B')b.push_back(make_pair(i,j)),a[i][j]=3;
				if(s[i][j]=='#')a[i][j]=1;
				if(s[i][j]=='.')a[i][j]=0;
			}
		}
		if(!v.size()){
			puts("YES");
			continue;
		}
		int fg=0;
		for(int i=0;i<(int)b.size()&&!fg;++i){
			int x=b[i].first,y=b[i].second;
			for(int j=0;j<4;++j){
				int nx=x+dx[j],ny=y+dy[j];
				if(a[nx][ny]==2){
					fg=1;puts("NO");break;
				}
				if(a[nx][ny]==3)continue;
				a[nx][ny]=1;
			}
		}
		if(fg)continue;
		if(a[n][m]){
			puts("NO");
			continue;
		}
		bfs(n,m);
		for(int i=0;i<(int)v.size();++i){
			if(!vis[v[i].first][v[i].second]){
				puts("NO");fg=1;break;
			}
		}
		if(!fg)puts("YES");
	}
	return 0;
}
```


---

## 作者：Eason_cyx (赞：2)

简单搜索 + 贪心题。

考虑怎样能使好人能全部走出去的概率最大。

那肯定是空的格子最多啊！

怎样使坏人都被拦住，又要使空的格子最多呢？

对每一个坏人实行 "特殊照顾"，直接将他的四面都围住，就可以了。

以上，贪心完毕。接下来剩下的就是二维 BFS 板子了。

**注意：从 $(n,m)$ 开始跑 BFS，最后的结果应该是所有好人都被跑到，所有坏人都没被跑到。**

时间复杂度 $O(Tnm)$。

```cpp
#include <queue>
#include <iostream>
#include <algorithm>
#include <cstring>
#define _rep(i,a,b) for(int i = a;i <= b;i++)
#define _for(i,a,b) for(int i = a;i < b;i++)
using namespace std;
struct node {
	int x,y;
};
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
int n,m;
char a[55][55];
bool vis[55][55];
queue<node> q;
bool Check(int x,int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m && !vis[x][y] && a[x][y] != '#';
}
bool BFS() {
	_rep(i,1,n) _rep(j,1,m) {
		if(a[i][j] != 'B') continue;
		_for(k,0,4) {
			int nx = i + dx[k],ny = j + dy[k];
			if(a[nx][ny] == '.') a[nx][ny] = '#';
		}
	}
	memset(vis,false,sizeof vis);
	while(!q.empty()) q.pop();
	if(a[n][m] != '#') {
		q.push({n,m});
	}
	vis[n][m] = true;
	while(!q.empty()) {
		node u = q.front(); q.pop();
		int x = u.x,y = u.y;
		_for(i,0,4) {
			int nx = x + dx[i],ny = y + dy[i];
			if(!Check(nx,ny)) continue;
			vis[nx][ny] = true;
			q.push({nx,ny});
		}
	}
	_rep(i,1,n) _rep(j,1,m)
		if((a[i][j] == 'G' && !vis[i][j]) || (a[i][j] == 'B' && vis[i][j])) return false;
	return true;	
}
void Solve() {
	cin >> n >> m;
	_rep(i,1,n) _rep(j,1,m)
		cin >> a[i][j];
	cout << (BFS() ? "Yes" : "No") << endl;
}
int main() {
	int T; cin >> T;
	while(T--) Solve();
	return 0;
}

```

总结：本题思维难度适中，代码难度较高，适合锻炼代码能力。

---

## 作者：Lemon_zqp (赞：2)

### 思路
这道题使用广度优先搜索，我们先找到所有所有坏人，然后把坏人的上下左右全部放上障碍物，使得每个坏人动弹不得，记得判断边界条件和本来有没有障碍物，接着从终点开始走，看看可不可以到达好人，如果可以就在标记数组里标记，那么最后判断一下坏人是不是都不能走到终点并且所有好人是不是都可以到达起点即可，最后，多组数据记得初始化。

### 代码 + 注释

```
#include<bits/stdc++.h>
using namespace std;

int n, m;
char c[55][55];
bool vis[55][55];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Node{
	int x, y;
};

queue<Node> q;

bool check(int x, int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m && !vis[x][y] && c[x][y] != '#';
}

bool bfs()
{
	//多组数据记得初始化
	memset(vis, false, sizeof(vis));
	//. --> #
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(c[i][j] != 'B')
			{
				continue;
			}
			for(int k = 0; k < 4; k++)//(i, j) --> (nx, ny)
			{
				int nx = dx[k] + i;
				int ny = dy[k] + j;
				//只改.
				if(c[nx][ny] == '.')
				{
					c[nx][ny] = '#';
				}
			}
		}
	}
	if(c[n][m] != '#')
		q.push({n, m});
	//标记初始状态
	vis[n][m] = true;
	while(!q.empty())
	{
		Node u = q.front();
		q.pop();
		int x = u.x, y = u.y;
		for(int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(!check(nx, ny))
			{
				continue;
			}
			vis[nx][ny] = true;
			q.push({nx, ny});
		}
	}
	//!(判断好人全部走到，坏人全部没有走到) --> false
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if((c[i][j] == 'G' && !vis[i][j]) || (c[i][j] == 'B' && vis[i][j]))
				return false;
	return true;
}

int main(){
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n >> m;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				cin >> c[i][j];
			}
		}
		if(bfs())
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}
	return 0;
}
```


---

## 作者：Ash_Dr (赞：2)

## 没人发$DFS$版本的，那我来一发$DFS$版本的题解
---
首先考虑这样一件事，**如果$B$和$G$都能走到同一处的格子，那么一定不满足题目的要求，因为你既要让所有的$G$都走到$(n,m)$,又要让所有的$B$都不能走到，一但出现一个$B$和$G$都能走到的格子，自然是不行的**

那么我们再考虑，如何保证尽可能的去消除这样的格子呢？

### 自然是贪心

**我们可以贪心的去把每一个$B$周围的空地都变为$#$,这样我们就尽可能的将每一个B都封闭了起来，那你可能会问这样做的正确能保证吗？**


$Proof:$

**我们考虑，如果去掉B周围的一个空地导致某一些$G$无法到达$(n,m)$,这时候结合我们之前分析的，B周围的这个空地就是我们上面讨论的格子，自然就算这样的操作使得$G$到不了$(n,m)$,原来的地图也是无法满足需求的，也就是说，我们贪心的改变B周围的空地并不影响答案的正确性，那么我们的做法就是正确的。**

然后就是朴素的$DFS$, 记得用一个小优化，即从终点$(n,m)$开始搜
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+50;
const int xx[] = {-1,1,0,0};
const int yy[] = {0,0,1,-1};
int T,n,m;
char mp[100][100];
int vis[100][100];
int tag[100][100];
void dfs(int x, int y) {
    if(x<1 || x>n || y<1 | y>m) return ;
    if(mp[x][y]=='#') return ;
    if(mp[x][y]=='G' || mp[x][y]=='B') tag[x][y]=1;
    for(int i=0; i<4; i++) {
        if(!vis[x+xx[i]][y+yy[i]]) {
            vis[x+xx[i]][y+yy[i]]=1;//记得标记
            dfs(x+xx[i],y+yy[i]);
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>T;
    while(T--) {
        cin>>n>>m;
        memset(vis,0,sizeof(vis));
        memset(tag,0,sizeof(tag));
        for(int i=1; i<=n; i++) {
             for(int j=1; j<=m; j++) {
                 cin>>mp[i][j];
             }
        }
        bool flag = true;
        for(int i=1 ;i<=n; i++) {
            for(int j=1; j<=m; j++) {
                if(mp[i][j]=='B') {
                    if(mp[i+1][j]=='.') mp[i+1][j]='#';
                    if(mp[i-1][j]=='.') mp[i-1][j]='#';
                    if(mp[i][j+1]=='.') mp[i][j+1]='#';
                    if(mp[i][j-1]=='.') mp[i][j-1]='#';
                }
            }
        }
        vis[n][m]=1;
        dfs(n,m);
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=m; j++) {
                if(mp[i][j]=='G') {
                    if(tag[i][j]) continue;
                    else {
                        flag = false;
                        break;
                    }
                }
                if(mp[i][j]=='B') {
                    if(tag[i][j]) {
                        flag = false;
                    }//分别判断每一个G和B
                }
            }
            if(!flag) break;
        }
        if(flag)  cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}
```
$End$


---

## 作者：do_while_true (赞：2)

考虑到如果有解，好人和坏人不能走在一起。如果可以走在一起的话，好人能走到 $(n,m)$，坏人也能走到。所以我们要保证好人和坏人不能走在一起。

这个时候建墙的策略就很清楚了，考虑贪心，因为我们不能让好人和坏人走在一起，而我们想要好人有更多的路（使得他能够走到 $(n,m)$ ），我们只需要让坏人走的路最少就行了。让坏人走的路最少即为把坏人上下左右的四个位置建墙。

然后从 $(n,m)$ 开始 `bfs` 或者 `dfs` 看是否能够搜到全部的好人，能搜到即为有解，反之无解。其他的`bfs`或者`dfs`的方法，只要复杂度正确也是可以过的。

[$\mathcal{Code}$](https://codeforces.com/contest/1365/submission/83226149)

---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1365D)

[CF传送门](https://codeforces.com/problemset/problem/1365/D)

[AC记录](https://codeforces.com/problemset/submission/1365/296832953)
# 题意简述
~~（翻译挺简洁的，直接上题面吧）~~

给出一个 $n$ 行 $m$ 列的网格，每个格子上有四种情况：
- `.` 表示这个格子是空地。
- `#` 表示这个格子是墙。
- `G` 表示这个格子是好人。
- `B` 表示这个格子是坏人。

`G`，`B`格子都可以认为是空地。

你需要判断能否 `.` 格子上放任意数量的墙，保证所有好人可以通过在空地间移动到达点 $(n,m)$ 而所有坏人都不行。
# 题解
1. 首先考虑不让坏人走到 $(n,m)$  
不能走到 $(n,m)$ 的最最最暴力的方法就是**不让坏人走到任何一个地方**。  
聪明的你一定想到了，直接在坏人身边放四面墙就可以困住 ta。
2. 此时判断好人能不能走到 $(n,m)$  
从每一个好人开始 dfs 显然不太行，那怎么办呢？  
此时我们可以用逆向思维：既然好人的目的地都是 $(n,m)$，那我们直接从 $(n,m)$ 开始搜索每个好人就可以了。
# 注意
困住坏人时，墙的位置有坏人就跳过，有好人直接输出 No。搜索时，先看看 $(n,m)$ 是不是墙。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
#define CLOSE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define F first
#define S second
#define lowbit(x) x&-x
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int Stack[105];
inline void print(ll x){
    int cnt=0;
    if(x<0) putchar('-'),x=-x;
    while(x){
    	Stack[++cnt]=x%10;
    	x/=10;
    }
    while(cnt--) putchar((char)Stack[cnt+1]+'0');
    return;
}
char a[1005][1005];
int vis[1005][1005];
int dx[]={0,1,0,-1};
int dy[]={-1,0,1,0};
int n,m,t,cnt;
void dfs(int x,int y){
	//cout<<x<<' '<<y<<' '<<cnt<<'\n';
	if(a[x][y]=='G') --cnt;//记录还有几个好人没搜到
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int xx=x+dx[i],yy=y+dy[i];
		if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]=='#'||vis[xx][yy]) continue;
		dfs(xx,yy);
	}
}
int main(){
    CLOSE
    cin>>t;
    while(t--){
    	cnt=0;
    	bool flag=0;
    	cin>>n>>m;
    	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
    	for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++) vis[i][j]=0;//初始化
    	for(int i=1;i<=n;i++)
    		for(int j=1;j<=m;j++){
    			if(a[i][j]=='G') ++cnt;//统计好人个数
    			if(a[i][j]=='B'){//若是坏人，就困住ta
    				for(int k=0;k<4;k++){
    					if(a[i+dx[k]][j+dy[k]]=='B'||i+dx[k]<1||i+dx[k]>n||j+dy[k]<1||j+dy[k]>m) continue;//墙的位置有坏人就跳过
    					if(a[i+dx[k]][j+dy[k]]=='G'){//墙的位置有好人就标记下来
    						flag=1;
    						break;
						}
						a[i+dx[k]][j+dy[k]]='#';//放墙
					}
				}
			}
		if(flag){//墙的位置有好人就输出No
			cout<<"No\n";
			continue;
		}
		if(a[n][m]!='#') dfs(n,m);//从(n,m)开始dfs
		if(!cnt) cout<<"Yes\n";
		else cout<<"No\n";
	}
    return 0;
}
```

---

## 作者：TruchyR (赞：1)

考虑好人要怎么走到 $(n,m)$ 才能存在方案：  

显然，路径上或者路径旁边的格子不能有坏人，否则没有办法堵住坏人。  

那么对于每个坏人，他和他四周的格子不能走。 

然后判断一下所有好人能不能走到 $(n,m)$ 即可，这里是用了并查集。  

[代码在这里](https://codeforces.com/contest/1365/submission/254028359)，其中 `Z(int i,int j)` 是将每个格子转化成一个数字的函数。

---

## 作者：_H17_ (赞：1)

## 题目大意

有个迷宫，你需要一开始给一些空格子变成障碍物使得坏人被困住，好人可以出逃，如果完成不了输出 `No`，否则输出 `Yes`。

## 思路分析

~~不可以，总司令是不是能过 $45\%$ 的测试点呢。~~

我们可以首先对坏人包夹（即把坏人边上的空格子改成障碍物），然后从出口 $(n,m)$ 进行 `BFS` 搜索每一个位置，如果有坏人那么则证明包夹失败。如果没有坏人可以出逃那么我们需要看看好人有没有被困住的，最后输出。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define Pair pair<int,int>
#define st first
#define nd second
//蒟蒻很懒，所以简写
using namespace std;
int T,n,m;
char c[51][51];//存
bool u[51][51];//广搜用来标记重复
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};//广搜的下一个位置
bool check(int x,int y){
	return 1<=x&&x<=n&&1<=y&&y<=m&&!u[x][y]&&c[x][y]!='#';
}//判断这个点广搜是否合法
bool solve(){//可以理解为输入好的主函数
	for(int i=1,nx,ny;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(c[i][j]=='B')
				for(int k=0;k<4;k++)
					if(check(nx=i+dx[k],ny=j+dy[k])&&c[nx][ny]=='.')
						c[nx][ny]='#';
	//包夹坏人
	queue<Pair>q;
	if(c[n][m]=='.'){
		q.push({n,m});
		u[n][m]=1;
		while(!q.empty()){
			Pair t=q.front();
			q.pop();
			for(int i=0,nx,ny;i<4;i++){
				nx=t.st+dx[i],ny=t.nd+dy[i];
				if(check(nx,ny)){
					if(c[nx][ny]=='B')
						return 0;
					if(c[nx][ny]=='G')
						c[nx][ny]='.';//将可以出来的好人忽略
					q.push({nx,ny});
					u[nx][ny]=1;
				}
			}
		}
	}
	//广搜每一个可能出逃的坏人
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(c[i][j]=='G')
				return 0;
   //防止好人被困
	return 1;//成功
}
void Main(){//单组数据的main
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>c[i]+1;
	memset(u,0,sizeof(u));
	bool x=solve();
	puts(x?"Yes":"No");
}
int main(){
	for(cin>>T;T;--T)
		Main();
	return 0;
}
```

---

## 作者：SegTree (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/CF1365D)

## 题目思路

考虑让坏人无法移动到 $(n,m)$ 需要将坏人的坐标 $(x,y)$ 周围的四个点 $(x-1,y),(x+1,y),(x,y-1),(x,y+1)$ 全部设为障碍。之后 `BFS` 考虑每个好人是否能够到达终点。

注意：设为障碍时不能覆盖原数组，否则可能会覆盖原来的好人和坏人的信息。

每次询问的回答时间复杂度为 $O(nm)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T;
char a[55][55],f[55][55];
int ans[55][55];
bool flag;
struct edge {
    int x,y,d;
};
vector<int>v;
vector<int>v2;
bool check(int x,int y){
    return (x<=n&&x>=1&&y<=m&&y>=1);
}
void bfs(){
    memset(ans,-1,sizeof(ans));
    queue<edge>Q;
    if(f[n][m]=='#')return;
    Q.push((edge){n,m});
    ans[n][m]=0;
    while(!Q.empty()){
        edge now=Q.front();
        Q.pop();
        if(check(now.x+1,now.y)&&f[now.x+1][now.y]!='#'&&ans[now.x+1][now.y]==-1){
            Q.push((edge){now.x+1,now.y,now.d+1});
            ans[now.x+1][now.y]=now.d+1;
        }
        if(check(now.x-1,now.y)&&f[now.x-1][now.y]!='#'&&ans[now.x-1][now.y]==-1){
            Q.push((edge){now.x-1,now.y,now.d+1});
            ans[now.x-1][now.y]=now.d+1;
        }
        if(check(now.x,now.y+1)&&f[now.x][now.y+1]!='#'&&ans[now.x][now.y+1]==-1){
            Q.push((edge){now.x,now.y+1,now.d+1});
            ans[now.x][now.y+1]=now.d+1;
        }
        if(check(now.x,now.y-1)&&f[now.x][now.y-1]!='#'&&ans[now.x][now.y-1]==-1){
            Q.push((edge){now.x,now.y-1,now.d+1});
            ans[now.x][now.y-1]=now.d+1;
        }
    }
}
signed main(){
    scanf("%d",&T);
    while(T--){
        v.clear();
        v2.clear();
        flag=0;
        scanf("%d %d",&n,&m);
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                cin>>a[i][j];
                f[i][j]=a[i][j];
                if(a[i][j]=='G'){
                    v.push_back(i);
                    v2.push_back(j);
                }
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                if(a[i][j]=='B'){
                    if(check(i-1,j))f[i-1][j]='#';
                    if(check(i+1,j))f[i+1][j]='#';
                    if(check(i,j-1))f[i][j-1]='#';
                    if(check(i,j+1))f[i][j+1]='#';
                }
            }
        }
        bfs();
        for(int i=0;i<v.size();++i){
            if(ans[v[i]][v2[i]]==-1){
                flag=1;
                break;
            }
        }
        if(flag)puts("No");
        else puts("Yes");
    }
    return 0;
}
```

---

## 作者：ATION001 (赞：0)

## 题目描述
给定一个 $n\times m$ 的网格，每个格子有四种状态：

- `.` 表示这个格子是空的。
- `#` 表示这个格子是墙。
- `G` 表示这个格子上的人是好人。
- `B` 表示这个格子上的人是坏人。

注：除标记 `#` 以外的格子都可以通过。

现要求在网格中的空地上放入任意数量的墙，使得所有坏人均不可逃出，所有好人均可逃出。

**本题有多组测试数据。**
## 思路
要想满足题目要求，一种办法就是直接把坏人围起来，这样占用的格子数量最少。

但是如果这个坏人四周至少有一个好人，那么无法围起来，无解。

所有坏人围起来之后，从节点 $n,m$ 开始跑 BFS/DFS，如果某一个好人没有被遍历到，说明无解。否则有解。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,b[60][60],xyx[5][5]={{0,1},{0,-1},{1,0},{-1,0}};
char a[60][60];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    for(cin>>t;t;t--){
        queue<pair<int,int>>q;
        cin>>n>>m;
        fill(b[0],b[60],INT_MAX);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
            }
        }
        bool flag=true;
        for(int i=1;i<=n&&flag;i++){
            for(int j=1;j<=m&&flag;j++){
                if(a[i][j]=='B'){
                    for(int k=0;k<4;k++){
                    	if(i+xyx[k][0]&&j+xyx[k][1]&&j+xyx[k][1]<=m&&i+xyx[k][0]<=n&&a[i+xyx[k][0]][j+xyx[k][1]]=='G'){
                    		flag=false;
                    		break;
						}
                        if(a[i+xyx[k][0]][j+xyx[k][1]]=='.'){
                            a[i+xyx[k][0]][j+xyx[k][1]]='#';
                        }
                    }
                }
            }
        }
        if(a[n][m]!='#'){
        	q.push({n,m});
		}
        while(q.size()&&flag){
            auto p=q.front();
            q.pop();
            for(int i=0;i<4;i++){
                int dx=p.first+xyx[i][0],dy=xyx[i][1]+p.second;
                if(dx&&dy&&dx<=n&&dy<=m&&a[dx][dy]!='#'&&b[dx][dy]==INT_MAX){
                    b[dx][dy]=b[p.first][p.second]+1;
                    q.push({dx,dy});
                }
            }
        }
        for(int i=1;i<=n&&flag;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]=='G'&&b[i][j]==INT_MAX){
                    flag=false;
                    break;
                }
            }
        }
        cout<<(flag?"Yes":"No")<<'\n';
    }
    return 0;
}
```

---

## 作者：luan341502 (赞：0)

考虑将每个 ```B``` 用 ```#``` 围起来，让他们不能接触到 ```G```，然后从 $(n,m)$ 开始 bfs 即可。

特判一些特殊情况，例如 ```B``` 与 ```G``` 相连，没有 ```G```，点 $(n,m)$ 被围住。

时间复杂度为 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int tt;
int n,m,cnt=0;
char s[55][55];
bool a[55][55],vis[55][55];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
bool bfs(){
	queue<pair<int,int> > q;
	q.push(make_pair(n,m));
	int sum=cnt;
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;
		q.pop();
		if(a[x][y]) sum--;
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(vis[nx][ny]||!nx||!ny||nx>n||ny>m) continue;
			vis[nx][ny]=true;
			q.push(make_pair(nx,ny));
		}
	}
	return sum==0;
}
void solve(){
	cnt=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>(s[i]+1);
		for(int j=1;j<=m;j++) vis[i][j]=a[i][j]=false;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='B'){
				if(s[i][j-1]=='G'||(j<m&&s[i][j+1]=='G')||(i<n&&(s[i-1][j]=='G'||s[i+1][j]=='G'))){
					cout<<"NO\n";
					return;
				}
				vis[i][j]=vis[i][j-1]=vis[i][j+1]=vis[i-1][j]=vis[i+1][j]=true;
			}else if(s[i][j]=='G') cnt++,a[i][j]=true;
			else if(s[i][j]=='#') vis[i][j]=true;
		}
	}
	if(!cnt) cout<<"YES\n";
	else if(vis[n][m]) cout<<"NO\n";
	else if(bfs()) cout<<"YES\n";
	else cout<<"NO\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>tt;while(tt--)solve();
} 
```


---

