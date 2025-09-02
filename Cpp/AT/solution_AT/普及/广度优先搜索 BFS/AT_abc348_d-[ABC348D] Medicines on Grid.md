# [ABC348D] Medicines on Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc348/tasks/abc348_d

$ H $ 行 $ W $ 列のグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマス目を $ (i,\ j) $ と表します。各マスの状態は文字 $ A_{i,j} $ で表され、意味は以下の通りです。

- `.` : 空きマス。
- `#` : 障害物。
- `S` : 空きマスかつスタート地点。
- `T` : 空きマスかつゴール地点。
 
高橋君は、今いるマスから上下左右に隣り合う空きマスへ、エネルギーを $ 1 $ 消費して移動することができます。ただし、エネルギーが $ 0 $ の状態で移動することはできず、またグリッドの外へ移動することはできません。

グリッドには合計で $ N $ 個の薬があります。$ i $ 番目の薬は空きマス $ (R_i,\ C_i) $ にあり、使うとエネルギーを **$ E_i $ にする**ことができます。必ずしもエネルギーが増えるとは限らないことに注意してください。高橋君は自分のいるマスにある薬を使うことができます。使った薬はなくなります。

高橋君ははじめエネルギー $ 0 $ の状態でスタート地点にいて、ゴール地点まで移動したいです。これが可能かどうか判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,\ W\ \leq\ 200 $
- $ A_{i,\ j} $ は `.`, `#`, `S`, `T` のいずれかである。
- `S` と `T` は $ A_{i,\ j} $ にそれぞれちょうど $ 1 $ つ存在する。
- $ 1\ \leq\ N\ \leq\ 300 $
- $ 1\ \leq\ R_i\ \leq\ H $
- $ 1\ \leq\ C_i\ \leq\ W $
- $ i\ \neq\ j $ ならば $ (R_i,\ C_i)\ \neq\ (R_j,\ C_j) $
- $ A_{R_i,\ C_i} $ は `#` でない。
- $ 1\ \leq\ E_i\ \leq\ HW $
 
### Sample Explanation 1

例えば、以下のようにしてゴール地点へ移動することができます。 - 薬 $ 1 $ を使う。エネルギーが $ 3 $ になる。 - $ (1,\ 2) $ へ移動する。エネルギーが $ 2 $ になる。 - $ (1,\ 3) $ へ移動する。エネルギーが $ 1 $ になる。 - 薬 $ 2 $ を使う。エネルギーが $ 5 $ になる。 - $ (2,\ 3) $ へ移動する。エネルギーが $ 4 $ になる。 - $ (3,\ 3) $ へ移動する。エネルギーが $ 3 $ になる。 - $ (3,\ 4) $ へ移動する。エネルギーが $ 2 $ になる。 - $ (4,\ 4) $ へ移動する。エネルギーが $ 1 $ になる。 この移動の途中には $ (2,\ 3) $ にも薬がありますが、これを使うとゴールできません。

### Sample Explanation 2

高橋君はスタート地点から移動することができません。

## 样例 #1

### 输入

```
4 4
S...
#..#
#...
..#T
4
1 1 3
1 3 5
3 2 1
2 3 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2
S.
T.
1
1 2 4```

### 输出

```
No```

## 样例 #3

### 输入

```
4 5
..#..
.S##.
.##T.
.....
3
3 1 5
1 2 3
2 2 1```

### 输出

```
Yes```

# 题解

## 作者：__ATRI__ (赞：13)

## 题目大意

有一个网格，网格中有 $H$ 行和 $W$ 列。用 $(i,j)$ 表示位于从上往下第 $i$ 行和从左往上第 $j$ 列的单元格。每个单元格的状态由字符 $A_{i,j}$ 表示，其含义如下：

- `.`：空单元格。
- `#`：一个障碍物。
- `S`：起点，可以视为空单元格。
- `T`：终点，可以视为空单元格。

高桥消耗 $1$ 能量从当前单元格移动到垂直或水平相邻的空单元格。如果能量为 $0$，他就无法移动。

网格中有 $N$ 种药物。第 $i$ 个药位于空格 $(R_i,C_i)$ 处，可以用来将能量 **设为** $E_i$。注意，能量不一定会增加。他 **可以** 在当前格子中使用药物。使用过的药品会消失。

高桥以 $0$ 的能量从起点开始，并希望到达终点。请判断这是否可行。

## 解法

如果本题没有能量，没有药（就像[这道题](https://www.luogu.com.cn/problem/P1605)），可以直接使用 bfs 解答。

但是现在有能量限制。

考虑如果当前格有药水，且喝完药水能量比之前高，那么就应该喝掉。毕竟不会返回原来的格子。

bfs 时将标记有没有走过改为记录走到当前格子的最大的剩余能量。如果走到的格子记录的能量比现在的大就舍去，否则更新记录的能量并入队。

这里使用优先队列将剩余能量较大的排在前面进行优化。

代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

int n,m,t,fx,fy,sx,sy,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0},a[205][205],b[205][205],dis[205][205];
struct node{
	int x,y,val;
	const bool operator<(const node &x)const{return val<x.val;}
};

void bfs(){
	priority_queue<node>q;//使用优先队列将剩余能量较大的排在前面进行优化
	memset(dis,-0x3f,sizeof dis);//初始化
	dis[sx][sy]=max(b[sx][sy],0);//初始化
	q.push({sx,sy,dis[sx][sy]});//起点入队
	while(q.size()){
		auto[x,y,val]=q.top();//出队
		q.pop();
		if(x==fx&&y==fy){
			cout << "Yes" << endl;//如果走到终点就结束
			return;
		}
		if(!val)continue;//如果没能量了就舍去
		if(val<dis[x][y])continue;//如果走到的格子记录的能量比现在的大就舍去
		for(int i=0;i<4;++i){
			int xx=x+dx[i],yy=y+dy[i];
			if(xx<1||xx>n||yy<1||yy>m||!a[xx][yy])continue;//判出图以及障碍
			int v=b[xx][yy]?max(b[xx][yy],val-1):val-1;//是否喝药
			if(v>dis[xx][yy]){
				//剩余能量比当前格子记录的大，更新记录的能量并入队
				q.push({xx,yy,v});
				dis[xx][yy]=v;
			}
		}
	}
	cout << "No" << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			char c;
			cin >> c;
			//标记地图
			a[i][j]=1;
			if(c=='S')sx=i,sy=j;
			if(c=='T')fx=i,fy=j;
			if(c=='#')a[i][j]=0;
		}
	}
	cin >> t;
	//标记药水
	for(int x,y,z;t--;){
		cin >> x >> y >> z;
		b[x][y]=z;
	}
	bfs();
	return 0;
}
```

---

## 作者：ivnilkkk (赞：3)

# [ABC348D] Medicines on Grid

## 思路

### 前置

我们先将输入的字符类型的二维数组进行处理，将它保存到整型数组 $a$ 中。我们遍历输入的二维数组，并定义变量 $sx$ 和 $sy$ 来保存起点的坐标，定义 $tx$ 和 $ty$ 来保存终点的坐标。然后对于障碍，我们将 $a$ 对应位置标记为 $-1$，否则就标记为 $0$。

注意到，每次使用药物后药物会消失，所以我们可以把药物能将体力加到的值填入到 $a$ 中，在判断是否可行的过程中，走到了一个位置 $(i,j)$， $a[i][j]$ 不为 $0$，我们便将它标记为 $0$（即清空）。

### 暴力思路

在前置部分的基础下，我们很容易想到暴力思路：跑一遍 bfs，并用 $dis[i][j]$ 表示走到第 $i$ 行第 $j$ 列的时候，还剩下多少体力。如果当前的体力小于 $0$ 了，说明这个位置不能往下走了，就跳过；否则，我们就看能否往上、下、左、右移动。如果当前走到的位置为终点，那么就说明可以走到终点。

### 正解思路

如果按照上面的思路写会 T 飞的！考虑优化。注意到，我们每次选择用一个位置去更新其他位置的体力值当且仅当这个位置的体力值比其他位置的体力值高。那么就有了优化思路，即如果一个位置之前的 $dis$ 就有值，并且去更新它的新的体力值，没有它之前的值高，我们就没有必要用它去更新别的点。做一个剪枝即可。

## 代码

```
#include <bits/stdc++.h>
using namespace std;

const int N = 210;
int n, m, h, sx, sy, tx, ty, a[N][N], dis[N][N];
int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool ok;
char str[N];
queue<pair<int, int>> q;

void bfs(int x, int y) {
	q.push(make_pair(x, y));
	if(a[x][y]) {
		dis[x][y] = a[x][y];
		a[x][y] = 0;
	}
	while(!q.empty()) {
		int x = q.front().first;
		y = q.front().second;
		q.pop();
		if(x == tx && y == ty) {
			ok = true;
			return;
		}
		if(dis[x][y] <= 0) return;
		for(int i = 0; i < 4; i++) {
			int X = x + d[i][0], Y = y + d[i][1];
			if(a[X][Y] == -1 || X < 1 || Y < 1 || X > n || Y > m)
				continue;
			if(X == tx && Y == ty) {
				ok = true; return;
			}
			int ma = 0;
			ma = dis[x][y] - 1;
			if(a[X][Y]) {
				ma = max(ma, a[X][Y]);
				a[X][Y] = 0;
			}
			if(ma > dis[X][Y]) {
				dis[X][Y] = ma;
				q.push(make_pair(X, Y));
			}
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%s", str + 1);
		for(int j = 1; j <= m; j++) {
			if(str[j] == 'S') sx = i, sy = j;
			if(str[j] == 'T') tx = i, ty = j;
			if(str[j] == '#') a[i][j] = -1;
		}
	}
	scanf("%d", &h);
	for(int i = 1; i <= h; i++) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		a[x][y] = z;
	}
	bfs(sx, sy);
	if(ok) printf("Yes");
	else printf("No"); 
	return 0;
}
```

---

## 作者：Fiendish (赞：2)

这道题不难，直接 bfs 即可，但因为一个格子可以重复经过，所以会 TLE。所以要思考如何打一个正确的标记。

考虑到能量越多就走得越远，同样也越有可能走到终点，所以当再一次经过某个格子时，如果这一次经过时能量比最多的一次少，那么继续搜索是没有意义的，所以记录一下过去经过这个格子时能量的最大值即可。

```cpp
#include<iostream>
#include<queue>
using namespace std;
int h,w;
int r,c,e[300][300],sx,sy,tx,ty,dx[4]={0,0,-1,1},dy[4]={1,-1,0,0},vis[300][300],n;
int ma[300][300];
char s[300];
priority_queue<pair<int,pair<int,int>> > q;
void bfs(){//广搜
	q.push({e[sx][sy],{sx,sy}});//将起点插入队列
	while(!q.empty()){
		int en=q.top().first,x=q.top().second.first,y=q.top().second.second;//分别表示当前能量值、当前横坐标、当前纵坐标
		q.pop();
		if(x==tx&&y==ty){//到达终点
			puts("Yes");
			return;
		}
		if(vis[x][y]>=en) continue;//能量值比原先最大值小就停止搜索
		vis[x][y]=en,en--;
		for(int i=0;i<4;i++){
			int x1=x+dx[i],y1=y+dy[i];
			if(ma[x1][y1]){
				if(e[x1][y1]) q.push({max(e[x1][y1],en),{x1,y1}});
				else q.push({en,{x1,y1}});
			}
		}
	}
	puts("No");
}
int main(){
	scanf("%d%d",&h,&w);
	for (int i=1;i<=h;i++){
		scanf("%s",s+1);
		for (int j=1;j<=w;j++){
			if(s[j]=='S') sx=i,sy=j,ma[i][j]=1;
			else if(s[j]=='T') tx=i,ty=j,ma[i][j]=1;
			else ma[i][j]=(s[j]=='.');
		}
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&r,&c);
		scanf("%d",&e[r][c]);
	}
	bfs();
}
```

---

## 作者：PineappleSummer (赞：2)

[[ABC348D] Medicines on Grid](https://www.luogu.com.cn/problem/AT_abc348_d)

Atcoder problems 评分：$\color{SeaGreen}{1108}$。

ABC 喜欢在 D 放搜索，实锤了。

直观而又好想的做法。搜索用的 BFS。记点 $(i,j)$ 当前剩余能量为 $c_{i,j}$，上一次到达该点的能量为 $last_{i,j}$，$last$ 数组初值为 $-1$。

首先判断起始点有没有能量包，没有直接输出 `No`。然后将起点加入队列，每次取队头，判断当前位置有没有能量包、需不需要能量包和当前是否有能量，这一部分很好写。向 $4$ 个方向拓展，若拓展点不是障碍且满足 $last_{xx,yy} < c_{x,y} - 1$，就向该点拓展，将该点加入队列。如果到达终点，输出 `Yes`，否则输出 `No`。

核心代码：
```cpp
if (!e[sx][sy]) return cout << "No", 0;//起点无能量
queue<node>q;
q.push(node{sx, sy});
while (!q.empty()) {
	int x = q.front().x, y = q.front().y;q.pop();
	if (e[x][y] && e[x][y] > c[x][y])
		c[x][y] = e[x][y], e[x][y] = 0;
	last[x][y] = c[x][y];
	if (!c[x][y]) continue;
	for (int i = 0; i < 4; i++) {
		int xx = x + dx[i], yy = y + dy[i];
		if (xx >= 1 && xx <= h && yy >= 1 && yy <= w && a[xx][yy] != '#')
		{
			if (last[xx][yy] < c[x][y] - 1) {
				if (xx == tx && yy == ty) return cout << "Yes", 0;
				last[xx][yy] = c[xx][yy] = c[x][y] - 1;
				q.push(node{xx, yy});
			}
		}
	}
}
cout << "No";
```

[完整代码](https://atcoder.jp/contests/abc348/submissions/52133153)

---

## 作者：kkxacj (赞：2)

#### 思路
考虑用求最短路的方法求出从起点到每一个点最多可以剩余多少能量，如果该点有药物就取最大值，最后看是否遍历到了终点就可以了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,n,v1[310][310],b[400],x[400],y[400],f[210][210],g[210][210],v[210][210],bj[210][210],st[10000000][5],l,cnt,fx,fy,fx1,fy1;
char a[210][210];
int c[10] = {-1,1,0,0};
int d[10] = {0,0,-1,1};
inline void bfs()
{
	while(l <= cnt)
	{
	//	cout<<st[l][0]<<" *** "<<st[l][1]<<" "<<f[st[l][0]][st[l][1]]<<endl;
		v1[st[l][0]][st[l][1]] = 0;
		if(st[l][0] == fx1 && st[l][1] == fy1)
		{
			printf("Yes");
			exit(0);
		}
		if(f[st[l][0]][st[l][1]] == 0)
		{
			l++;
			continue;
		}
		for(int i = 0;i < 4;i++)
		{
			int x = st[l][0] + c[i],y = st[l][1] + d[i];
			if(x < 1 || y < 1 || x > h || y > w || a[x][y] == '#') continue;
		//	cout<<x<<" ^^^^ "<<y<<endl;
			if(v[x][y] >= f[x - c[i]][y - d[i]] - 1 && f[x][y] < v[x][y]) 
			{
				if(!v1[x][y]) st[++cnt][0] = x,st[cnt][1] = y;
				f[x][y] = v[x][y],v1[x][y] = 1;
			}
			else if(f[x][y] < f[x - c[i]][y - d[i]] - 1) 
			{
				if(!v1[x][y]) st[++cnt][0] = x,st[cnt][1] = y,st[cnt][3] = x - c[i],st[cnt][4] = y - d[i];
				f[x][y] = f[x - c[i]][y - d[i]] - 1,v1[x][y] = 1;
			}
		}
		
		l++;
	}
}
int main()
{
	scanf("%d%d",&h,&w);
	for(int i = 1;i <= h;i++)
		for(int j = 1;j <= w;j++)
		{
			cin >> a[i][j]; f[i][j] = -100;
			if(a[i][j] == 'S') fx = i,fy = j;
			if(a[i][j] == 'T') fx1 = i,fy1 = j;
		}
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d%d%d",&x[i],&y[i],&b[i]),v[x[i]][y[i]] = b[i];
	if(!v[fx][fy])
	{
		printf("No");
		return 0;
	}
	v1[fx][fy] = 1;
	st[++cnt][0] = fx,st[cnt][1] = fy,f[fx][fy] = v[fx][fy]; l = cnt;
	bfs(); 
	printf("No");
    return 0;
}

```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc348_d)

## 思路

一道广搜，但是要用到最短路的思想。

我们用两个数组记录，一个是 ``dis``，另一个是 ``vis``。``dis`` 记录走到当前位置的时候最大剩余步数是多少，``vis`` 记录当前位置的“补给”是否用过。

我们读入数据后正常开始广搜。当我们枚举到一个点时：

- 如果这个点的“补给”被用过了，那么判断上次到这里的剩余步数和当前剩余步数哪个大。如果当前剩余步数大，那么记录 ``dis`` 为当前剩余步数，继续搜索。

- 如果这个点的“补给”没用过，我们可以**选择用或者不用**。如果不用，那么进行上面的一步。如果用，那么记录 ``vis`` 为已用过，更改剩余步数且记录 ``dis`` 值，按照更改的步数继续搜索。

当我们走到终点且步数 $\ge 0$ 时，输出 ``Yes`` 结束程序。如果没到终点步数就 $\le 0$ 了，那么这条路肯定走不了，跳过这次搜索。

如果搜索完成后也没到达过终点，输出 ``No``。

- 注意：可以**选择**用或者不用补给；如果用补给，那么是**更改**剩余步数，而不是增加。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
signed solution();
signed main(){solution();return 0;}
ll read(){//快读。
	ll k=0;bool flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag^=1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=310;
int n,m,Q,a[N][N],sx,sy,ex,ey,dis[N][N];
bool vis[N][N];
struct node{
	int x,y,step;
};queue<node>q;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
signed solution(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			char c;
			cin>>c;
			if(c=='#')dis[i][j]=1e9,vis[i][j]=1;//记录一个极值使它走不了。
			if(c=='S')sx=i,sy=j;
			if(c=='T')ex=i,ey=j;
		}
	}
	cin>>Q;
	while(Q--){
		int x=read(),y=read(),z=read();
		a[x][y]=z;
	}
	q.push({sx,sy,a[sx][sy]});//记录初始点。
	dis[sx][sy]=a[sx][sy];
	vis[sx][sy]=1;
	while(q.size()){
		node now=q.front();
		q.pop();
		if(now.x==ex&&now.y==ey&&now.step>=0){//能到终点。
			cout<<"Yes";
			return 0;
		}
		if(now.step<=0)continue;//走不了了。
		for(int i=0;i<4;++i){
			int xx=dx[i]+now.x;
			int yy=dy[i]+now.y;
			if(xx<1||xx>n||yy<1||yy>m)continue;//出图了。
			if(vis[xx][yy]){//已经用过补给。
				if(dis[xx][yy]<now.step-1){
					dis[xx][yy]=now.step-1;
					q.push({xx,yy,now.step-1});
				}
			}
			else{
				if(dis[xx][yy]<now.step-1){//不用补给就是最优解。
					dis[xx][yy]=now.step-1;
					q.push({xx,yy,now.step-1});
				}
				else{//不是最优解，用补给尝试。
					if(a[xx][yy])now.step=a[xx][yy]+1;//记得是改值，-1 要用 +1 抵消。
					dis[xx][yy]=now.step-1;
					vis[xx][yy]=1;
					q.push({xx,yy,now.step-1});
				}
			}
		}
	}
	cout<<"No";//走不通。
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/154767855)

---

## 作者：Ivan422 (赞：1)

题目大意：走迷宫，$S$ 起点 $T$ 终点，$n$ 个点上面有可以恢复体力的药，用这个药体力恢复为 $e_i$，用完药就没了，每次移动消耗 $1$ 体力，初始没有体力，判断是否能走到终点。

思路：首先想到广搜，这个可以恢复体力的迷宫实际上是一个非常经典的分层图广搜，每一层就是体力，最大为 $200\times 200$。这样存一个布尔数组大小 $1.6\times10^9$，不会炸。接着直接进行分层图广搜，这里加一个剪枝：当目前体力不是这个位置体力最大值，那说明这种情况肯定不比前面出现过的情况更优，直接剪掉即可，这样就不会超时了。

这里给没有学过分层图的讲解一下：把每种体力看为一个层，这样每次更新体力后就去到了新的层，也就是说在一个点上不同的体力其实可以记作不同的状态。每次体力消耗再根据情况更新访问数组，注意要加下体力这一维，所以题目中访问是个三维数组，第一维其实就是体力那一维。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=305,M=205,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
struct pp{int x,y,v;};
queue<pp>q;
char a[N][N];
bool vis[M*M][M][M];
int mx[N][N],n,rr[N],cc[N],ee[N],h,w,sx,sy,tx,ty;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
signed main(){
    cin>>h>>w;
    for(int i=1;i<=h;i++)for(int j=1;j<=w;j++){
        cin>>a[i][j];
        if(a[i][j]=='S')sx=i,sy=j;
        if(a[i][j]=='T')tx=i,ty=j;
    }
    cin>>n;
    for(int i=1;i<=n;i++){cin>>rr[i]>>cc[i]>>ee[i];}
    for(int i=1;i<=n;i++)if(rr[i]==sx&&cc[i]==sy){q.push(pp{sx,sy,ee[i]});vis[ee[i]][sx][sy]=1;}
    while(q.size()){
        pp f=q.front();q.pop();
        mx[f.x][f.y]=max(mx[f.x][f.y],f.v);
        if(f.v<mx[f.x][f.y])continue;
        if(f.x==tx&&f.y==ty){cout<<"Yes";return 0;}
        for(int i=0;i<4;i++){
            int nx=f.x+dx[i],ny=f.y+dy[i],nv=f.v-1;
            if(nx<1||ny<1||nx>h||ny>w)continue;
            if(a[nx][ny]=='#')continue;
            if(f.v==0)continue;
            if(nv>=0&&!vis[nv][nx][ny]){
                vis[nv][nx][ny]=1;
                q.push(pp{nx,ny,nv});
            }
            for(int j=1;j<=n;j++)if(rr[j]==nx&&cc[j]==ny){
                nv=ee[j];
                if(nv>=0&&!vis[nv][nx][ny]){
                    vis[nv][nx][ny]=1;
                    q.push(pp{nx,ny,nv});                
                }
            }
        }
    }
    cout<<"No";
    return 0;
}
```

---

## 作者：linjunye (赞：1)

### 题目简要
高桥要从一个点走到另一个点，每走一步消耗一点能量，最初他有 $0$ 点能量。

网格上有一些药，如果高桥走到那里将会被设置成新的能量值。

问他能否能走到那个点。
### 初步思路
看到这样的类似于“走迷宫”的问题，你肯定会想到 BFS 吧。

可是，程序中的 `vis` 数组将要开成：

```cpp
vis[210][210][40010]
//前二维表示坐标，最后一维表示能量(Ei<=HW)。
```

算一下，$200\times200\times40000=1600000000$，远远超出了空间限制。

那么，我们需要优化。
### 进一步优化
优化的关键点其实就在于“题目简要”的这句话：

“网格上有一些药，如果高桥走到那里将会被**设置**成新的能量值。”

注意到“**设置**”了吗，那是我们解题的关键！

于是我们再想一想：药起到什么作用呢。

答案其实也显而易见：不就是为了接下来能到达终点吗！

那么，是不是我们预处理出每个药互相之间与终点的距离，就能实现 BFS 的优化了！

若还不懂，就请让我举一个例子：

```
3 3
S..
#..
T.#
2
1 1 3
2 3 3
```
方便起见，我们把每个药用 `*` 来表示，那么网格就变成：
```
*..
#.*
T.#
```
若想一次性走到终点，显然不可能，所以需要先走到药物 $2$，再到终点。

那么，我们可以通过预处理，将走到药物 $2$ 的过程给省略掉。

验证正确性：因为每次的能量值不会增加，只会重置，所以并不存在“可以用之前剩下的能量去走这条路程”，所以可以通过预处理来优化。
### 预处理
那么，如何预处理呢？

想一想，我们发现：可以通过多次 BFS，来统计药物之间互相的距离。

所以我们需要先给药物编号（就是数组的下标，所以不用做），以及给它的坐标打上标记（知道这是第几个药物）。

当然，我们还要加入终点（后面会讲）。

重点代码：
```cpp
void BFS(int I){
	memset(vis,0,sizeof(vis));
	queue<Node>Q;
	dis[I][I]=0;
	vis[a[I].x][a[I].y]=1;
	//上述实现了初始化
	Q.push({a[I].x,a[I].y,0});
	//e在这里表示为最短路（一个结构体多用，后面会给出Node的实际用处）
	while(!Q.empty()){
		int x=Q.front().x;
		int y=Q.front().y;
		int e=Q.front().e;
		Q.pop();
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(!h(nx,ny))continue;//h函数判断有无越界
			vis[nx][ny]=1;
			if(mp[nx][ny]){//这里是药物
				int j=mp[nx][ny];
				dis[I][j]=e+1;
			}
			Q.push({nx,ny,e+1});
		}
	}
	return;
}
```
### 求答案
最终，我们就可以实现最终的 BFS 了（可以对着样例来看）。

重点代码：
```cpp
void bfs(int sx,int sy,int ex,int ey){
	if(mp[sx][sy]==0){
		cout<<"No";//见题目中的样例二
		return;
	}
	queue<int>Q;
	Q.push(k);//最后一个
   	//注：我的BFS从终点往前搜，你也可以从起点往后搜（因为我并没有记录起点的编号是几）
	vis2[k]=1;
	while(!Q.empty()){
		int i=Q.front();
		Q.pop();
		for(int j=1;j<=k;j++){
			if(vis2[j])continue;//一定要有vis！！！
			int D=dis[i][j];//距离
			if(a[j].e<D)continue;//能量值小于距离，便走不到
			int x=a[j].x,y=a[j].y;
			if(x==sx&&y==sy){
				cout<<"Yes";
				return;
			}
			Q.push(j);
			vis2[j]=1;
		}
	}
	cout<<"No";
	return;
}
```
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x7f7f7f7f;
const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};
struct Node{//原先的Node是用来记录药物的，在预处理时实现了二次利用 
	int x,y,e;//坐标与能量值 
}a[310];
int dis[310][310],mp[310][310],vis[310][310];
int n,m,k;
char ch[210][210];
bool h(int x,int y){
	return (x>0&&x<=n&&y>0&&y<=n&&ch[x][y]!='#'&&!vis[x][y]);
}
void BFS(int I){
	memset(vis,0,sizeof(vis));//一定要初始化！！！ 
	queue<Node>Q;
	dis[I][I]=0;
	vis[a[I].x][a[I].y]=1;
	Q.push({a[I].x,a[I].y,0});//e在这里表示为最短路
	while(!Q.empty()){
		int x=Q.front().x;
		int y=Q.front().y;
		int e=Q.front().e;
		Q.pop();
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(!h(nx,ny))continue;
			vis[nx][ny]=1;
			if(mp[nx][ny]){//是休息站
				int j=mp[nx][ny];
				dis[I][j]=e+1;
			}
			Q.push({nx,ny,e+1});
		}
	}
	return;
}
int vis2[310];
void bfs(int sx,int sy,int ex,int ey){
	if(mp[sx][sy]==0){
		cout<<"No";
		return;
	}
	queue<int>Q;
	Q.push(k);//最后一个
	vis2[k]=1;
	while(!Q.empty()){
		int i=Q.front();
		Q.pop();
		for(int j=1;j<=k;j++){
			if(vis2[j])continue;
			int D=dis[i][j];
			if(a[j].e<D)continue;
			int x=a[j].x,y=a[j].y;
			if(x==sx&&y==sy){
				cout<<"Yes";
				return;
			}
			Q.push(j);
			vis2[j]=1;
		}
	}
	cout<<"No";
	return;
}
int main(){
	memset(dis,0x7f,sizeof(dis));
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>ch[i][j];
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>a[i].x>>a[i].y>>a[i].e;
		mp[a[i].x][a[i].y]=i;//(x,y)是第i个药物的坐标，mp[i][j]见上述说明 
	}
	int sx,sy,ex,ey;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='S')sx=i,sy=j;
			if(ch[i][j]=='T')ex=i,ey=j;
		}
	//加上终点 	
	k++;
	a[k].x=ex;
	a[k].y=ey;
	for(int i=1;i<=k;i++)
		BFS(i);//预处理BFS 
	bfs(sx,sy,ex,ey);//求答案BFS 
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：1)

### 题目大意

现在有一个 $H$ 行 $W$ 列的网格，每个网格里面如果是 `#` 则是障碍物不能通过，`S` 和 `T` 为起点和终点，`.` 为空地，可以经过，高桥现在想从起点走到终点，如果高桥想走到相邻的格子则需要花费一个能量，如果没有能量了就不能移动了，现在有一些格子中有药物 $i$ 可以把你当前的能量重置为 $E_i$，现在高桥想知道他能不能在起点且初始能量为 $0$ 的情况下走到终点。

### 思路

暴力广搜，然后加一个数组表示当前这个位置走过的最大能量值是多少来优化一下。

### 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
#define pll pair<ll,ll>
#define prq priority_queue
using namespace std;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			f = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
char a[205][205];
vector<ll> st[205][205];
bool vis[205][205];
struct que {
	ll x, y, e;
};
ll n, m;
ll dx[10] = {0, 0, 1, -1};
ll dy[10] = {1, -1, 0, 0};
ll g[205][205];
ll tp[205][205];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n = read(), m = read();
	ll sx, sy, ex, ey;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
			if (a[i][j] == 'S') {
				sx = i, sy = j;
			}
			if (a[i][j] == 'T') {
				ex = i, ey = j;
			}
			if (a[i][j] == '#') {
				vis[i][j] = 1;
			}
		}
	}
	ll t = read();
	for (int i = 1; i <= t; i++) {
		ll x = read(), y = read(), e = read();
		g[x][y] = e;
	}
	queue<que> q;
	if (!g[sx][sy]) {
		printf("No");
		return 0;
	}
	q.push(que{sx, sy, g[sx][sy]});
	vis[sx][sy] = 1;
	memset(tp, -1, sizeof(tp));
	while (!q.empty()) {
		que u = q.front();
		q.pop();
		if (u.x == ex && u.y == ey) {
			printf("Yes");
			return 0;
		}
		if (!u.e) {
			continue;
		}
		for (int i = 0; i < 4; i++) {
			ll nx = u.x + dx[i], ny = u.y + dy[i], ne = u.e-1;
			if (nx < 1 || nx > n || ny < 1 || ny > m || vis[nx][ny]) {
				continue;
			}
			if (ne < g[nx][ny]) {
				ne = g[nx][ny];
				g[nx][ny] = 0;
			}
			if (ne > tp[nx][ny]) {
				q.push(que{nx, ny, ne});
				tp[nx][ny]=ne;
			}
		}
	}
	printf("No");
	return 0;
}
~~~

---

## 作者：___Furina___ (赞：1)

### 题意简述（可不看）：
在一个方格图中，告诉你障碍、起点、终点、可行的路和一些药的位置，经过一个药的时候，可以选择把当前的能量值**改为**一个值；只能走到相邻的格子，走到相邻的一个格子需要耗费一个能量。问是否能从起点走到终点。
### 题解：
提出一个不太一样的思路：

我们可以把有能量的位置看成一个个点，如果能从有能量的  $(x_a,y_a)$ 到另一个有能量的点 $(x_b,y_b)$，则连一条**有向边**，最后从起点到终点跑一遍深搜看是否能到达即可。

### 注意：
- 判断是否可以到达时不用回溯（就是因为这个我在考场上没打调出来）！！！
- 可以在终点建一个有能量的点，这样更好处理。
- 可以二维点转一维点。

代码如下：
```cpp
#include<bits/stdc++.h>
#define N 210
#define I_love_Furina return//发电+放抄袭
#define forever 0
#define foreverr 1
#define mk make_pair
#define se second
#define fi first
#define int long long
using namespace std;
int n,m,k,x[310],y[310],w[N*N],sx,sy,ex,ey,head[N*N],d[4][2]={{1,0},{-1,0},{0,1},{0,-1}},flag,num;
bool b[N][N],vis[N*N];
char c[N][N];
struct node{int to,nxt,w;}a[N*N*2];
queue<pair<int,pair<int,int> > > q;
inline int gt(int x,int y){I_love_Furina (x-1)*m+y;}//二维点转一维
inline void add(int u,int v,int w){a[++num].to=v,a[num].nxt=head[u],a[num].w=w,head[u]=num;}
inline void solve(int st){//对有能量的点之间连边
    while(!q.empty())q.pop();//清空
    memset(b,0,sizeof b);//清空标记
    q.push(mk(w[gt(x[st],y[st])],mk(x[st],y[st])));
    b[x[st]][y[st]]=1;//标记是否到达过某点
    int num=w[gt(x[st],y[st])];
    while(!q.empty()){
        int step=q.front().fi,xx=q.front().se.fi,yy=q.front().se.se;
        q.pop();
        if(!step)continue;
        for(int i=0;i<=3;i++){
            int tx=xx+d[i][0],ty=yy+d[i][1];
            if(b[tx][ty]||tx<1||ty<1||tx>n||ty>m||c[tx][ty]=='#')continue;
            b[tx][ty]=1,q.push(mk(step-1,mk(tx,ty)));
            if(w[gt(tx,ty)]){
                add(gt(x[st],y[st]),gt(tx,ty),num-(step-1));//连边
            }
        }
    }
}
void dfs(int x,int step){
    if(x==gt(ex,ey)||flag){//可行并且返回
        flag=1;
        I_love_Furina;//忘记有exit(0)了
    }
    step=max(w[x],step);//贪心：如果没有之前步数更优则不取
    for(int i=head[x];i;i=a[i].nxt){
        int v=a[i].to,w=a[i].w;
        if(vis[v]||step<w)continue;
        vis[v]=1,dfs(v,step-w);//千万别回溯！
    }
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
	    cin>>c[i][j];
	    if(c[i][j]=='S')sx=i,sy=j;
	    if(c[i][j]=='T')ex=i,ey=j;
    }
	cin>>k;
	for(int i=1,ww;i<=k;i++){
	    cin>>x[i]>>y[i]>>ww;
	    w[gt(x[i],y[i])]=ww;//记录药品能量
    }
    x[++k]=ex,y[k]=ey,w[gt(ex,ey)]=1;
    for(int i=1;i<=k;i++)solve(i);//连边
    vis[gt(sx,sy)]=1;
    dfs(gt(sx,sy),0);//判断可达性
    if(flag)cout<<"Yes";
    else cout<<"No";
	I_love_Furina forever;
}
```

当然，我们并不需要记录边的权值，因为我们在一开始已经判断了两个有能量点的可达性，所以我们可以简化代码（这份代码没有注释，基本和上面一样）：
```cpp
#include<bits/stdc++.h>
#define N 210
#define I_love_Furina return
#define forever 0
#define foreverr 1
#define mk make_pair
#define se second
#define fi first
#define int long long
using namespace std;
int n,m,k,x[310],y[310],w[N*N],sx,sy,ex,ey,head[N*N],d[4][2]={{1,0},{-1,0},{0,1},{0,-1}},flag,num;
bool b[N][N],vis[N*N];
char c[N][N];
struct node{int to,nxt;}a[N*N*2];
queue<pair<int,pair<int,int> > > q;
inline int gt(int x,int y){I_love_Furina (x-1)*m+y;}
inline void add(int u,int v){a[++num].to=v,a[num].nxt=head[u],head[u]=num;}
inline void solve(int st){
    while(!q.empty())q.pop();
    memset(b,0,sizeof b);
    q.push(mk(w[gt(x[st],y[st])],mk(x[st],y[st])));
    b[x[st]][y[st]]=1;
    while(!q.empty()){
        int step=q.front().fi,xx=q.front().se.fi,yy=q.front().se.se;
        q.pop();
        if(!step)continue;
        for(int i=0;i<=3;i++){
            int tx=xx+d[i][0],ty=yy+d[i][1];
            if(b[tx][ty]||tx<1||ty<1||tx>n||ty>m||c[tx][ty]=='#')continue;
            b[tx][ty]=1,q.push(mk(step-1,mk(tx,ty)));
            if(w[gt(tx,ty)]){
                add(gt(x[st],y[st]),gt(tx,ty));
            }
        }
    }
}
void dfs(int x){
    if(x==gt(ex,ey)||flag){
        flag=1;
        I_love_Furina;
    }
    for(int i=head[x];i;i=a[i].nxt){
        int v=a[i].to;
        if(vis[v])continue;
        vis[v]=1,dfs(v);
    }
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
	    cin>>c[i][j];
	    if(c[i][j]=='S')sx=i,sy=j;
	    if(c[i][j]=='T')ex=i,ey=j;
    }
	cin>>k;
	for(int i=1,ww;i<=k;i++){
	    cin>>x[i]>>y[i]>>ww;
	    w[gt(x[i],y[i])]=ww;
    }
    x[++k]=ex,y[k]=ey,w[gt(ex,ey)]=1;
    for(int i=1;i<=k;i++)solve(i);
    vis[gt(sx,sy)]=1;
    dfs(gt(sx,sy));
    if(flag)cout<<"Yes";
    else cout<<"No";
	I_love_Furina forever;
}

```

完结撒花（点个赞再走）！

---

## 作者：maokaiyu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc348_d)
## 思路
如果只是单纯 dfs 寻求路径的话，一定会 TLE 的。所以，我们可以这样优化：对于路径有贡献的点，一定是起点，终点，有药的点，这里称为关键点。如果当前关键点的能量为 $e_i$ 那么只要有有药点、起点、终点，能在 $e_i$ 步内到达，就对那个点连一条单向边。最后，我们就从起点 BFS 计算能否到达终点。
## 细节
对于建图，我们可以用 BFS 判断。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
const I D[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
vector<pair<I,I>>edges[100010];
I h,w,n,e[410][410],stx,sty,enx,eny;
char a[410][410];
bool b[410][410];
I main(){
	scanf("%d%d",&h,&w);//输入 
	for(I i = 1;i <= h;i++){
		scanf("%s",a[i] + 1);
	}
	scanf("%d",&n);
	for(I i = 1;i <= n;i++){
		I x,y,z;
		scanf("%d%d%d",&y,&x,&z);
		e[y][x] = z;
	}
	//puts("");
	for(I i = 1;i <= h;i++){//建图 
		for(I j = 1;j <= w;j++){
			if(e[i][j] || a[i][j] == 'S' || a[i][j] == 'T'){
				if(a[i][j] == 'S') stx = j,sty = i;
				else if(a[i][j] == 'T') enx = j,eny = i;
				for(I i = 1;i <= h;i++){
					for(I j = 1;j <= w;j++){
						b[i][j] = false;
					}
				}
				I head = 1,rear = 0,q[40100][3];
				q[++rear][0] = j,q[rear][1] = i,q[rear][2] = e[i][j];
				b[i][j] = true;
				while(head <= rear){
					I x = q[head][0],y = q[head][1],z = q[head++][2];
					for(I k = 0;k < 4;k++){
						I xx = x + D[k][0],yy = y + D[k][1];
						//printf("%d %d %d %d %d\n",j,i,xx,yy,z);
						if(a[yy][xx] == '#' || yy < 1 || yy > h || xx < 1 || xx > w ||z - 1 < 0 || b[yy][xx]) continue;
						if(e[yy][xx] || a[yy][xx] == 'S' || a[yy][xx] == 'T'){
							edges[i * h + j].pb({xx,yy});
						}
						b[yy][xx] = true;
						q[++rear][0] = xx,q[rear][1] = yy,q[rear][2] = z - 1;
					}
				}
			}
		}
	}
	//puts("");
	for(I i = 1;i <= h;i++){
		for(I j = 1;j <= w;j++){
			b[i][j] = false;
		}
	}
	I q[40100][2],head = 1,rear = 0;//求答案
	q[++rear][0] = stx,q[rear][1] = sty;
	b[sty][stx] = true;
	while(head <= rear){
		I x = q[head][0],y = q[head++][1];
		//printf("%d %d\n",x,y);
		for(auto i : edges[y * h + x]){
			if(b[i.se][i.fi]){
				continue;
			}
			b[i.se][i.fi] = true;
			q[++rear][0] = i.fi,q[rear][1] = i.se;
		}
	}
	if(b[eny][enx]){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
	return 0;
}
```

---

## 作者：eb0ycn (赞：1)

传送门：[AT_abc348_d](https://www.luogu.com.cn/problem/AT_abc348_d)。

## 题意

一个迷宫，某些方格上有药水，每个药水有一个能量值。走到一个格子，你可以喝掉这个药水，然后你的能量就会变成药水的能量。只有你的能量大于 $0$ 时，你才能花费一个能量走到下一格。每个药水只能喝一次。

问能否从起点走到终点。

## 思路

首先，因为药水的效果是把能量**设为**某个值，所以喝多少次药水其实都相当于喝一次。

然后，一个很显然的贪心：对于同一个位置，到这里的能量肯定越多越好。所以本题可以等价为求最长路。

注意到走一格如果不喝药水，相当于边权为 $-1$；如果喝药水，边权是一个非负数。所以这题其实是求正负边权的最长路，再看一眼数据范围，直接无脑上记忆化搜索。

这样子的话时间复杂度就是 spfa 的复杂度，即 $O(H^2W^2)$。因为是走迷宫，跑不满，而且 AT 机子神，所以跑得飞快。

## 代码

具体实现时，我还是用了优先队列。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
int h,w,n,r,c,e,mp[2001][2001],sx,sy,ex,ey,nx,ny,ne,dis[2001][2001];
char op;
struct node{
	int x,y,now;
	bool operator<(const node&cwx)const{return now<cwx.now;}
}le;
priority_queue<node>q;
bool vis[2001][2001];
int main(){
	scanf("%d%d",&h,&w);
	for(int i=1;i<=h;++i){
		getchar();
		for(int j=1;j<=w;++j){
			op=getchar(),dis[i][j]=-1;
			if(op=='S')sx=i,sy=j;
			if(op=='T')ex=i,ey=j;
			if(op=='#')mp[i][j]=1000000;
		}
	}
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d%d%d",&r,&c,&e),mp[r][c]=max(e,0);
	q.push({sx,sy,mp[sx][sy]}),dis[sx][sy]=mp[sx][sy];
	while(!q.empty()){
		le=q.top(),r=le.x,c=le.y,e=le.now,q.pop();
		if(!e||e<dis[r][c])continue;
		for(int i=0;i<4;++i){
			nx=r+dx[i],ny=c+dy[i],ne=max(mp[nx][ny],e-1);
			if(!nx||!ny||nx>h||ny>w||mp[nx][ny]==1000000)continue;
			if(ne>dis[nx][ny])q.push({nx,ny,ne}),dis[nx][ny]=ne;
		}
	}return 0&printf("%s",~dis[ex][ey]?"Yes":"No");
}
```

花絮：场上我写了一个 Dijkstra，WA 了三个点，遗憾离场，赛后上了高达五分。

---

## 作者：lunjiahao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc348_d)
### 题目大意：
给定一个 $n \times m$ 的地图，要求从起点 `S` 走到终点 `T`，每移动 $1$ 个会消耗 $1$ 点能量，障碍 `#` 不能走，空地为`.`可以走，体力消耗至 $0$ 也无法移动，地图位置 $(x_i,y_i)$ 有一瓶可以**变成** $e_i$ 体力的药，可以选择是否喝。

问能否抵达终点，可以输出 `Yes`，否则输出 `No`。

数据范围：$1 \leq n,m \leq 200,1 \leq x_i \leq n,1 \leq y_i \leq m,1 \leq e_i \leq n \times m$。
### 题目分析：
~~（一眼 bfs 板题，结果赛时用了标记是否走过+优先队列的假做法 WA 了 3 个点没调出来）~~

这题需要判断，因为吃药这个性质特殊，是变成对应的体力值 $e$，而不是增加体力值 $e$，存在后效性，不能使用标记是否走过+优先队列，所以需要开一个 `ma[][]` 数组记录走到某点的最大能量，当 $w_{x,y}>ma_{x,y}$ 才继续搜索，切记每走到有药的地方直接先让 $w_{x,y} \gets \max(w_{x,y},a_{x,y})$，再判断即可（`a` 数组存图）。

时间复杂度：$O(nm)$，含有较大常数。
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};//遍历方向
int n,m,k,bx,by,ex,ey,a[N][N],ma[N][N];
//(bx,by)为起点，(ex,ey)为终点，a[][]存图，障碍为 -1，自然数能走，正整数表示有药，ma[i][j]存走到(i,j)的最大能量
struct dat//自从打过 CF 的题结构体就再也不敢命名为 data
{
	int x,y,w;
};//结构体存走到(x,y)有 w 能量
void bfs(int x,int y)
{
	queue <dat> q;//开普通队列即可
	q.push((dat){x,y,a[x][y]});
	ma[x][y]=a[x][y];
	while(!q.empty())
	{
		dat now=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			int xx=now.x+dx[i];
			int yy=now.y+dy[i];
			int ww=now.w-1;
			if(xx==ex&&yy==ey)//是否抵达终点
			{
				printf("Yes");
				exit(0);//结束程序
			}
			ww=max(ww,a[xx][yy]);//走到 (xx,yy) 的最大能量
			if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]==-1||ww<=ma[xx][yy]||ww<=0) continue;//判断越界、障碍、能量，若当前能量不超过最大能量也要停止下传
			q.push((dat){xx,yy,ww});
			ma[xx][yy]=ww;//更新走到 (xx,yy) 的最大能量
		}
	}
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char ch;
			cin>>ch;
			if(ch=='S') bx=i,by=j;//起点
			if(ch=='T') ex=i,ey=j;//终点
			if(ch=='#') a[i][j]=-1;//障碍
		}
	cin>>k;
	for(int i=1;i<=k;i++)
	{
		int x,y,w;
		cin>>x>>y>>w;
		a[x][y]=w;//标记(x,y)有可以变成 w体力药 
	}
	if(!a[bx][by])//若初始位置没有能量，无法行动，不用进入 bfs，直接输出 -1
	{
		printf("No");
		return 0;
	}
	bfs(bx,by);
	printf("No");
	return 0;
}
```

---

## 作者：zcz0263 (赞：1)

## 思路
因为药的效果是直接将能量设为某个值，可以看出每一步可更新的位置只和能否到达当前点有关而和具体方案无关。考虑双层 BFS，用队列 `q2` 维护可以到达的有药的格子，内层队列 `q` 维护从 `q2.top()` 的位置开始并**仅**拾取对应的药后可以到达的所有格子，当更新到未被更新过的有药的格子时就同时添加到 `q1` 队列中，当 `q` 队列添加终点的时候即为有解，更新完所有可到达的有药的格子还无法到达终点即为无解。  
在此方法的基础上添加记忆化即可通过此题。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define INF INT_MAX
//#define INF LLONG_MAX
#define pii pair<int,int>
#define vi vector<int>
#define pipii pair<int,pii>
#define vpii vector<pair<int,int>>
#define _max(x,y) (((x)>(y))?(x):(y))
#define _min(x,y) (((x)<(y))?(x):(y))
#define max(...) max({__VA_ARGS__})
#define min(...) min({__VA_ARGS__})
#define link tfshtrj
#define y1 drshzhsrd
#define mkp make_pair
#define pb push_back
#define eb(x) emplace_back(x)
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define all(x) x.begin(),x.end()
#define allt(x,y,z) x.begin()+y,x.begin()+z
#define fi first
#define se second
string a[505];
int ys[505][505];
vector<vi> vis(505,vi(505,-1));
pii st,ed;
int h,w,n,r,c,e;
struct node{
	int x,y,cnt;
};
constexpr int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>h>>w;
	rep(i,1,h){
		cin>>a[i];
		a[i]=" "+a[i];
		rep(j,1,w){
			if(a[i][j]=='S') st={i,j};
			if(a[i][j]=='T') ed={i,j};
		}
	}
	cin>>n;
	rep(i,1,n){
		cin>>r>>c>>e;
		ys[r][c]=e;
	}
	queue<node> q,q2;
	q2.push({st.fi,st.se,ys[st.fi][st.se]});
	ys[st.fi][st.se]=0;
	while(q2.size()){
		q.push(q2.front());
		q2.pop();
		while(q.size()){
			auto [x,y,cnt]=q.front();
			q.pop();
			if(x==ed.fi&&y==ed.se){
				cout<<"Yes";
				return 0;
			}
			if(ys[x][y]){
				q2.push({x,y,ys[x][y]});
				ys[x][y]=0;
			}
			if(cnt<=vis[x][y]||!cnt) continue;
			vis[x][y]=cnt;
			rep(i,0,3){
				int nx=x+dx[i],ny=y+dy[i];
				if(nx>0&&nx<=h&&ny>0&&ny<=w&&a[nx][ny]!='#') q.push({nx,ny,cnt-1});
			}
			
		} 
	}
	cout<<"No";
}
```

---

## 作者：I_will_AKIOI (赞：0)

### 题目大意

给你一个 $n\times m$ 的地图，`S` 表示起点，`T` 表示终点，`.` 表示空地，`#` 表示障碍。每次你可以上下左右走，不能走出地图，同时小号一格能量，若能量为 $0$ 则无法移动。初始能量为 $0$。

在地图中，有 $k$ 个药，坐标是 $(x_i,y_i)$，走到 $(x_i,y_i)$ 时，你可以选择用药或者不用，用的话你的能量会变为 $z_i$，每个药只能用一次。问你能不能到终点。

考虑广搜。我们令 $vis_{x,y}$ 表示到达点 $(x,y)$ 时的最大能量，每次搜索往上下左右延伸，如果这个点是药，则和当前能量取最大值。

```
#include<bits/stdc++.h>
using namespace std;
struct Data
{
  int x,y,s;
}w;
int n,m,k,sx,sy,tx,ty;
int a[205][205],fx[5]={0,1,0,-1},fy[5]={1,0,-1,0};//方向数组
int vis[205][205];
char c[205][205];
queue<Data>q;
string BFS()
{
  w.x=sx,w.y=sy,w.s=a[sx][sy];
  a[sx][sy]=0;
  q.push(w);
  while(!q.empty())
  {
    w=q.front();
    if(w.x==tx&&w.y==ty) return "Yes";//到达终点
    for(int i=0;i<4;i++)
    {
      int nx=w.x+fx[i],ny=w.y+fy[i],ns=w.s-1;
      if(nx<1||nx>n||ny<1||ny>m||c[nx][ny]=='#'||ns==-1||max(ns,a[nx][ny])<=vis[nx][ny]) continue;
      ns=max(ns,a[nx][ny]);//用药
      vis[nx][ny]=ns;
      q.push(Data{nx,ny,ns});
    }
    q.pop();
  }
  return "No";
}

int main()
{
  ios::sync_with_stdio(0);
  memset(vis,-1,sizeof(vis));
  cin>>n>>m;
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
    {
      cin>>c[i][j];
      if(c[i][j]=='S') sx=i,sy=j;
      if(c[i][j]=='T') tx=i,ty=j;
    }
  }
  cin>>k;
  for(int i=1;i<=k;i++)
  {
    int x,y,z;
    cin>>x>>y>>z;
    a[x][y]=z;
  }
  cout<<BFS();
  return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 题目分析

这是一道很简单的 BFS。我们可以在 BFS 的过程中记录一个 $h_{x,y}$ 表示到达 $(x,y)$ 的最大血量。那么，这个题的做法就很明显了。在 BFS 往四周扩散的过程中，如果当前血量大于当前位置的 $h$，那么：

1. 如果这个位置有药，那么就将该位置的 $h$ 设为药能带来的能量。
2. 否则就将该位置的 $h$ 设为当前血量。

如果当前位置是终点且当前血量大于等于 $0$，则将答案设为可以，最后输出即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int h,w,n,sx,sy,ex,ey,e[205][205];
int H[205][205],l[4]={0,1,0,-1},r[4]={1,0,-1,0};
char Map[205][205];
bool flag[205][205],ans;
struct node{
	int x,y,HP;
};

void bfs(){
	queue<node>q;
	H[sx][sy]=e[sx][sy];
	q.push({sx,sy,e[sx][sy]});
	while(!q.empty()){
		node tmp=q.front();
		q.pop();
		int x=tmp.x,y=tmp.y,HP=tmp.HP;
		for(int i=0;i<4;i++){
			int xx=x+l[i],yy=y+r[i];
			if(xx<1||yy<1||xx>h||yy>w||Map[xx][yy]=='#'){
				continue;
			}
			if(HP-1>H[xx][yy]){
				if(flag[xx][yy]){
					H[xx][yy]=max(HP-1,e[xx][yy]);
				}
				else{
					H[xx][yy]=HP-1;
				}
				q.push({xx,yy,H[xx][yy]});
			}
			if(xx==ex&&yy==ey&&HP>0){
				ans=true;
				return;
			}
		}
	}
}

void init(){
	memset(H,-1,sizeof H);
	scanf("%d %d",&h,&w);
	for(int i=1;i<=h;i++){
		scanf("%s",Map[i]+1);
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		e[x][y]=z,flag[x][y]=true;
	}
}

void solve(){
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(Map[i][j]=='S'){
				sx=i,sy=j;
			}
			if(Map[i][j]=='T'){
				ex=i,ey=j;
			}
		}
	}
	bfs();

	if(ans){
		puts("Yes");
	}
	else{
		puts("No");
	}
}

int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：codingwen (赞：0)

首先看到是地图式的题目，那么我的脑海中瞬间浮现出 bfs 或dfs 。    
接着想到它其实也是从一个药跑到另外一个药，以此类推直到跑到终点。   
不就是一个隐藏的 bfs 吗？   
但你要想这样做，就要先预处理。   
考虑 $dist_{i,x,y}$ 为从第 $i$ 个药跑到 $(x,y)$ 位置上要跑多远的距离。   
对于一个药 $i$ ，以 $x_i,y_i$ 为起点做一个 bfs 。求出 dist 数组。   
接着从起点的药出发（如果起点没有药就没法跑出起点），对于 $k$ 号药，枚举接下来要到达的药的编号 $i$。如果 $e_k \geq dist_{k,x_i,y_i}$ 那么说明可以到达。   
我们可以开一个标记数组来标记是否可以到达某个药，最后对于一个可以到的药，判断一下是否能到达就行了。   

```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[210][210];
int vis[210][210],vis2[310];
int dist[310][210][210];
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int n,m,k;
struct med{
	int x,y,e;
}mes[310];
struct node{
	int x,y,dis;
};
int main(){
	cin>>n>>m;
	int sx,sy,tx,ty;
	for(int i=1;i<=n;i++){
		scanf("%s",mp[i]+1);
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='S'){
				sx=i;
				sy=j;
			}
			if(mp[i][j]=='T'){
				tx=i;
				ty=j;
			}
		}
	}
	cin>>k;
	int sid=-1;
	for(int i=1;i<=k;i++){
		int x,y,e;
		cin>>x>>y>>e;
		if(x==sx && y==sy)sid=i;
		mes[i].x=x;
		mes[i].y=y;
		mes[i].e=e;
	}
	if(sid==-1){
		puts("No");
		return 0;
	}
    memset(dist,0x3f,sizeof(dist));
	for(int i=1;i<=k;i++){
		memset(vis,0,sizeof(vis));
		queue<node> q;
		vis[mes[i].x][mes[i].y]=1;
		q.push(node{mes[i].x,mes[i].y,0});
		while(!q.empty()){
			node f=q.front();
			q.pop();
			dist[i][f.x][f.y]=f.dis;
			for(int i=0;i<4;i++){
				int ax=f.x+dx[i];
				int ay=f.y+dy[i];
				if(ax<1 || ax>n || ay<1 || ay>m)continue;
				if(vis[ax][ay] || mp[ax][ay]=='#')continue;
				vis[ax][ay]=1;
				q.push(node{ax,ay,f.dis+1});
			}
		}
	}
	memset(vis2,0,sizeof(vis2));
	queue<int> q;
	q.push(sid);
	vis2[sid]=1;
	while(!q.empty()){
		int nid=q.front();
		q.pop();
		int ne=mes[nid].e;
		for(int i=1;i<=k;i++){
			if(vis2[i])continue;
			int ae=ne-dist[nid][mes[i].x][mes[i].y];
			if(ae<0)continue;
			vis2[i]=1;
			q.push(i);
		}
	}
	for(int i=1;i<=k;i++){
		if(vis2[i]){
			if(dist[i][tx][ty]<=mes[i].e){
				puts("Yes");
				return 0;
			}
		}
	}
	puts("No");
	return 0;
}
```

#### 题外话：我赛时以为是药的能量是叠加的，写了个代码提交上去，结果得到了 42/50 (84分) 的好成绩（大雾）。或许是数据太水了……

---

## 作者：T_TLucas_Yin (赞：0)

首先这题爆搜是会超时的。

注意到既然走到一个补给点后能量会被设为一个定值，那么不管何时走到这个补给点，此时的能量一定是固定的。也就是说，从这一格继续走，以现有能量能走到的格子也是固定的。这样我们就能求出从该补给点始终可以走到哪些其他补给点。

我们对每一个补给点与从这里能走到的补给点（以及能走到的起点和终点）单向建边，形成一个图。如果这个图中从起点到终点是联通的，答案就为可以到达；否则就不能到达。

```cpp
#include<bits/stdc++.h>
using namespace std;
map<pair<int,int>,int> ma;
int n,m,p,x[1005],y[1005],a[1005],sx,sy;
char c[1005][1005];
int ver[100005],ne[100005],head[100005],tot;
void add(int x,int y){
	ver[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
bool v[10005];
queue<int> f;
bool bfs(){//判断最后得到的图是否联通
	f.push(0),v[0]=1;
	while(!f.empty()){
		int x=f.front();f.pop();
		if(x==p+1) return 1;
		for(int i=head[x];~i;i=ne[i]){
			if(!v[ver[i]]) v[ver[i]]=1,f.push(ver[i]);
		}
	}
	return 0;
}
struct node{
	int x,y,k;
};
bool flag[1005][1005];
queue<node> q;
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
bool check(int x,int y){//越界判断
	if(x<1||x>n) return 0;
	if(y<1||y>m) return 0;
	return 1;
}
void build(int k){//第k个补给站与周围的补给站建边
	int w=a[k];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
		flag[i][j]=0;
	q.push({x[k],y[k],0}),flag[x[k]][y[k]]=1;//以上为初始化
	while(!q.empty()){
		node t=q.front();q.pop();
		if(ma.count({t.x,t.y})&&ma[{t.x,t.y}]!=k)
			add(k,ma[{t.x,t.y}]);//能到达一个补给站
		if(c[t.x][t.y]=='S') add(k,0);
		if(c[t.x][t.y]=='T') add(k,p+1);
		if(t.k==w) continue;//只搜索w步以内能达到的位置
		for(int i=0;i<4;i++){
			int xx=t.x+dx[i],yy=t.y+dy[i];
			if(check(xx,yy)&&c[xx][yy]!='#'&&!flag[xx][yy])
				flag[xx][yy]=1,q.push({xx,yy,t.k+1});//纯搜索
		}
	}
}
int main(){
	scanf("%d %d",&n,&m);
	memset(head,-1,sizeof(head));
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		cin>>c[i][j];
		if(c[i][j]=='S') sx=i,sy=j;//存储起点的位置，以后有用
	}
	scanf("%d",&p);
	for(int i=1;i<=p;i++){
		scanf("%d %d %d",&x[i],&y[i],&a[i]);
		ma[{x[i],y[i]}]=i;//表示该位置上有编号为i的补给站
	}
	for(int i=1;i<=p;i++) build(i);
	if(ma.count({sx,sy})) add(0,ma[{sx,sy}]);//起点与起点上的补给站建边
	if(bfs()) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：0)

首先容易发现，一个位置上的药物只能使用一次和可以使用多次是等价的，因为：

- 如果从一个点用了一次药物之后绕了一圈回来能量变少了，那么走这个肯定不优，所以就不会影响；
- 如果从一个点用了一次药物之后绕一圈回来能量变多了，那么此时再次使用肯定是不优的，所以自然就不会使用。

于是进行 bfs，状态用一个三元组 $(x,y,h)$ 表示当前位置和能量。

注意这样仍然可能超时，于是用 $vis_{x,y}$ 记录 $(x,y)$ 位置的历史最高能量（因为如果以更低的能量出发肯定更不优）。

这个时候复杂度应该是一个类似于 SPFA 的复杂度，足以通过。

```cpp
cin>>h>>w;
for(int i=1;i<=h;i++)cin>>s[i],s[i]=" "+s[i];
int n;
cin>>n;
for(int i=1,x,y,e;i<=n;i++){
  cin>>x>>y>>e;
  tg[x][y]=max(tg[x][y],e);
}
queue<node>q;
for(int i=1;i<=h;i++)for(int j=1;j<=w;j++)if(s[i][j]=='S')q.push({i,j,tg[i][j]});
while(!q.empty()){
  int x=q.front().x,y=q.front().y,hh=q.front().h;
  q.pop();
  if(s[x][y]=='T')return YES();// 能到直接结束
  if(vis[x][y]>=hh)continue;// 不优
  vis[x][y]=hh;
  for(int i=0;i<4;i++){
    int dx=x+d[i][0],dy=y+d[i][1];
    if(dx>=1&&dx<=h&&dy>=1&&dy<=w&&s[dx][dy]!='#')q.push({dx,dy,max(tg[dx][dy],hh-1)});// 记得取 max
  }
}
return NO();
```

---

## 作者：ma_niu_bi (赞：0)

### 题意

给定一个 $H$ 行 $W$ 列的地图，每格可能有障碍。每次可向上下左右走一格，并消耗一点能量，能量为零时不能移动。部分格子可能有补充的能量，经过该格时可将当前能量值**改为**补充的能量，求能否从起点到达终点。

### 思路

考虑广搜。

注意此时一格可能经过多次，所以普通广搜的思路需要修改。把不同广搜的 ```vis``` 数组的定义改为走到当前格子的最大能量值。如果搜索时发现当前能量值小于最大能量值，继续搜索就没有意义了，否则就更新最大值，继续搜索即可。

还要注意补充能量时需要判断补充能量是否大于当前能量值，如果大于才可更新。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
char mp[500][500];
int h, w, n, sx, sy, tx, ty;
int e[500][500];
int vis[500][500];
struct node {int x, y, e;};
queue <node> q;
int xz[] = {1, 0, -1, 0};
int yz[] = {0, 1, 0, -1};
int main() {
    memset(vis, -1, sizeof(vis));
    cin >> h >> w;
    for (int i = 1; i <= h; i ++) 
        scanf("%s", mp[i] + 1);
    cin >> n;
    for (int i = 1, R, C, E; i <= n; i ++) {
        cin >> R >> C >> E;
        e[R][C] = E;
    }
    for (int i = 1; i <= h; i ++) {
        for (int j = 1; j <= w; j ++) {
            if (mp[i][j] == 'S') sx = i, sy = j;
            if (mp[i][j] == 'T') tx = i, ty = j;
        }
    }
    q.push(node{sx, sy, e[sx][sy]});
    vis[sx][sy] = e[sx][sy];
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y, E = q.front().e;
        q.pop();
        if (x == tx && y == ty) {
            puts("Yes");
            return 0;
        }
        if (E <= 0) continue;
        for (int i = 0; i < 4; i ++) {
            int xx = x + xz[i], yy = y + yz[i];
            if (xx < 1 || xx > h || yy < 1 || yy > w) continue;
            if (mp[xx][yy] == '#') continue;
            int ee = E - 1;
            ee = max(ee, e[xx][yy]);
            if (vis[xx][yy] >= ee) continue;
            vis[xx][yy] = ee;
            q.push(node{xx, yy, ee});
        }
    }
    puts("No");
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

给定一个 $H \times W$ 的网格图，其中给定起点，终点和障碍物。

初始能量为 $0$，每次可以在上下左右中选择一个方向前进一个单位，但是不能超过网格图，此时能量值 $-1$；若当前能量值为 $0$，则无法移动。

有 $n$ 个物品，第 $i$ 个物品在 $(x_i,y_i)$，可以选择或不选择使当前能量值变为 $a_i$。

判断能否从起点走到终点。

### 思路：

考虑广度优先算法，记 $f_{i,j}$ 表示到达 $(i,j)$ 的最大能量值。

初始若起点处没有物品，则无法移动；否则肯定选了起点处的物品，将能量赋值一下。

设当前在 $(x,y)$，若当前能量 $sum \le 0$，那么无法移动，退出；否则，求出上下左右的点 $(zx,zy)$，如果走过去之后的能量值 $t \le f_{zx,zy}$，即没有之前走的优，那么就可以不用走过去。

考虑如何求 $t$，设 $A_{i,j}$ 表示 $(i,j)$ 处的物品的能量；到达 $(zx,zy)$ 首先会使能量减去 $1$，即 $t = sum-1$。

若 $A_{zx,zy} \ge t$，那么是可以使用这个物品的，将 $t \to A_{zx,zy}$。

设 $N,M$ 同阶，时间复杂度为 $O(N^3) \sim O(N^4)$，但是一般都跑不满。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=305;
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
	ll x,y;
	ll data;
};
ll n,m,x,y,z,k,sx,sy,tx,ty;
char a[N][N];
ll A[N][N],f[N][N];
queue<Node> Q;
ll dx[]={0,0,1,-1},dy[]={1,-1,0,0};
void bfs(){
	Q.push({sx,sy,A[sx][sy]});
	while(!Q.empty()){
		ll x=Q.front().x,y=Q.front().y,z=Q.front().data;
		Q.pop();
		if(x==tx&&y==ty){
			puts("Yes");
			exit(0);
		}
		if(z<=0)
		  continue;
		for(int i=0;i<4;i++){
			ll zx=x+dx[i],zy=y+dy[i];
			if(zx<1||zx>n||zy<1||zy>m)
			  continue;
			if(a[zx][zy]=='#')
			  continue;
			ll t=max(A[zx][zy],z-1);
			if(f[zx][zy]>=t)
			  continue;
			f[zx][zy]=t;
			Q.push({zx,zy,t});
		}
	}
}
int main(){
	memset(f,-1,sizeof(f));
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=getchar();
			if(a[i][j]=='S')
			  sx=i,sy=j;
			if(a[i][j]=='T')
			  tx=i,ty=j;
		}
		getchar();
	}
	k=read();
	while(k--){
		x=read(),y=read();
		A[x][y]=read();
	}
	bfs();
	puts("No");
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# AT_abc348_d

## 解题思路

初看：这不 dfs 板子题。

看完：很喜欢我的一句话，啊？

如果我们直接贴一个 dfs 上去铁定是 T 的（因为不同路线中一个点可以重复走）。

既然正着想不好搞，让我们逆向思考一下，显然，从终点开始走一遍 bfs 可以直接得到每个点到终点需要的能量。

然后对于每一瓶药，判断如果它这个点到终点需要的能量小于等于这瓶药的能量值（且不为 $0$），那这个点到终点的距离可以直接设为 $0$，然后以这个点为基础再走一遍 bfs。

复杂度嘛，最开始 bfs 肯定是 $O(HW)$ 的，每瓶药最多以他为起点 bfs 一遍，这部分的复杂度是 $O(NHW)$，看一眼数据范围，完美解决。

赛时写完这道题只剩 $4$ 分钟了，所以最后这块实现上有点瑕疵，复杂度可能高一些，~~（不过还是让我过去了）~~ 所以代码就不放了。

---

## 作者：CEFqwq (赞：0)

一道比较复杂的搜索题。

直接暴力搜，记录 `vis`，然后我们很可能会发现样例 3 出了问题，当一个格子第一次访问时的能量值并不是走到这个格子时的最大能量值。

所以我们记忆化，维护走到每个格子的最大能量值即可。

我采用的是广搜。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[205][205];
int ene[205][205], f[205][205];//f 数组维护最大能量值
bool vis[205][205];
int n, m, k, sx, sy, mx, my, nm;
int dx[] = {0, 0, 0, 1, -1};
int dy[] = {0, 1, -1, 0, 0};
struct node{
	int x, y, st, en;
};
queue<node> q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)	
		for (int j = 1; j <= m; j++){
			cin >> a[i][j];
			if (a[i][j] == 'S')
				sx = i, sy = j;
			if (a[i][j] == 'T')
				mx = i, my = j;
		}
	cin >> k;
	for (int i = 1; i <= k; i++){
		int xx, yy, vv;
		cin >> xx >> yy >> vv;
		ene[xx][yy] = vv;
	}
	q.push({sx, sy, 0, ene[sx][sy]});
	while (!q.empty()){//广搜
		node u = q.front();
		int pn = 0;
		q.pop();
		if (u.en == 0)
			continue;
		for (int i = 1; i <= 4; i++){
			node v = u;
			v.x += dx[i];
			v.y += dy[i]; 
			v.st++;
			v.en--;
			if (v.x == mx && v.y == my){
				cout << "Yes";
				return 0;
			}
			if (v.x < 1 || v.x > n || v.y < 1 || v.y > m)
				continue;
			if (a[v.x][v.y] == '#' || f[v.x][v.y] >= max(v.en, ene[v.x][v.y]))
				continue;
			if (v.en < ene[v.x][v.y])//更新当前格子
				v.en = ene[v.x][v.y];
			if (!v.en)
				continue;
			f[v.x][v.y] = v.en;
			q.push(v);
			pn++;
		}	
	}
	cout << "No";
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
优先队列 BFS。首先肯定对于每个位置，能量值越大越优，优先队列中按照当前能量值从大到小排序，然后只要比当前最优解更优时可以入队，最后如果到了终点就结束了。
# 另一种解法
因为可以重复进队，所以用普通队列也行。但是普通队列会导致重复进队次数太多辣，所以虽然优先队列有 $\log$，但普通队列效率远远不及优先队列。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
struct node {
	int x, y, z;
	bool operator < (const node& t) const {
		return z < t.z;
	}
} ;
int n, m, t, x, y, z, a[205][205], vis[205][205];
string mp[205];
priority_queue <node> q;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	for (int i = 0; i < n; ++ i)
		cin >> mp[i];
	cin >> t;
	while (t --)
		cin >> x >> y >> z, a[x - 1][y - 1] = z;
	for (int i = 0; i < n; ++ i)
		for (int j = 0; j < m; ++ j) {
			vis[i][j] = -1;
			if (mp[i][j] == 'S') {
				q.push ({i, j, a[i][j]});
				vis[i][j] = a[i][j];
			}
		}
	while (! q.empty ()) {
		const node x = q.top ();
		if (mp[x.x][x.y] == 'T') {
			cout << "Yes";
			return 0;
		}
		q.pop ();
		if (x.z)
			for (int i = 0; i < 4; ++ i) {
				int X = dx[i] + x.x, Y = dy[i] + x.y, Z = max (x.z - 1, a[X][Y]);
				if (~X && ~Y && X < n && Y < m && Z > vis[X][Y] && mp[X][Y] != '#') {
					vis[X][Y] = Z;
					q.push ({X, Y, Z});
				}
			}
	}
	cout << "No";
	return 0;
}
```

---

## 作者：__HHX__ (赞：0)

# 思路
因为是地图搜索类，可以考虑 BFS。

补充：充能点为 $(R_i,L_i)$。
# 法一
我们先设计状态 $(x, y, val)$ 其中 $(x, y)$ 为坐标，$val$ 为在此坐标下的最大能量。

因为 $val$ 值无法保证下一步的值是最优的，所以考虑用优先队列。

容易观察得，在相同的 $(x, y)$ 下 $val$ 越大越好。

容易证明：下面代码的``M[t.x][t.y] = t.val``最多执行 $N$ 次。

故时间复杂度为 $O(HWN)$。
```cpp
#include <iostream>
#include <queue>
#include <set>

using namespace std;

const int N = 2e2 + 3, mod = 998244353;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

struct Node {
  int x, y, val;
  bool operator>(const Node &k) const {
    if (val == k.val) return x == k.x ? y > k.y : x > k.x;
    return val > k.val;
  }
  bool operator<(const Node &k) const {
    if (val == k.val) return x == k.x ? y < k.y : x < k.x;
    return val < k.val;
  }
};

int n, m, ex, ey;

bool f[N][N];

int E[N][N], M[N][N];

void bfs(int x, int y) {
  priority_queue<Node> q;
  q.push({x, y, 0});
  while (q.size()) {
    Node t = q.top();
    if (t.val < 0) continue;
    q.pop(); t.val = max(t.val, E[t.x][t.y]);
    if (t.x == ex && t.y == ey) {
      cout << "Yes";
      exit(0);
    }
    if (t.val <= M[t.x][t.y]) continue;
    M[t.x][t.y] = t.val;
    for (int i = 0; i < 4; i++) {
      Node p = t;
      p.x += dx[i], p.y += dy[i], p.val--;
      if (p.x >= 1 && p.y >= 1 && p.x <= n && p.y <= m && !f[p.x][p.y]) q.push(p);
    }
  }
}

int main() {
  int fx, fy, k;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      cin >> c;
      if (c == 'S') fx = i, fy = j;
      if (c == 'T') ex = i, ey = j;
      if (c == '#') f[i][j] = 1;
    }
  }
  cin >> k;
  for (int i = 1; i <= k; i++) {
    int x, y, u;
    cin >> x >> y >> u;
    E[x][y] = u;
  }
  bfs(fx, fy);
  cout << "No";
  return 0;
}
```
# 法二
法二是我后想到的方法，也是比较暴力的方法，可是在打的时候我把 $N$ 的范围看成了 $E_i$ 的范围，所以法二迟迟想不出来，所这篇题解就只给法一的代码。

因为最短路我们并不关心，所以仅需看是否到达。

因为每个能充能的点，可以使得能量值改变，且不受转移过来的影响。

所以我们可以每次 BFS 查看当前点能到那些冲能点，记录没有跑 BFS 的，再跑一边。

补充：记忆化 DFS 和递推也可以跑。

时间复杂度为 $O(HWN)$。

BFS伪代码如下:
```
queue<点> qdots;
qdot.push(S);
while 执行到 qdots 为空
  queue<(点,剩余能量)> q;
  q.push(qdots.front()), qdots.pop();
  while 执行到 q 为空
    k = q.front();
    if k 所在点为 T
      可达;
    if k 所在点为冲能点 且 没被记录
      记录 k 所在点, qdots.push(k 所在点);
    if k 剩余能量为 0
      continue;
    k 路径转移得 t;
    q.push(t);
```
# 法三
这是法二的衍生版，我刚想到的，所以也没写。

如果把他当图论来讲的话，我们先记录 $S,T$ 和充能点在当前格子能到达的 $S,T$ 和充能点。

我们仅需判断 $S$ 是否可达 $T$。

时间复杂度为 $O(HWN)$。

---

## 作者：chenzhaoxu2027 (赞：0)

# 题目大意

有一个网格，网格有 $H$ 行 $W$ 列，有以下几种格子：

- ```S```：起始点，是个空白格子

- ```T```：终点，是个空白格子

- ```.```：一个空白格子

- ```#```：障碍物

每一次小明可以从一个格子花费 1 能量来移动到与小明相邻的 4 个格子中的一个。如果小明能量为 0，则无法移动。

初始时小明能量为 0，位于 ```S``` 格处。

网格中有 $N$ 种药物，第 $i$ 个药品位于格子 $(R_i,C_i)$ 处，可以用来将能量置为 $E_i$。

注意，能量并不一定会增加。他可以在当前格子中使用药物。使用过的药物会消失。

试判断小明是否可以走到 ```T``` 格。

$1 \le H,W \le 200$

$1 \le N \le 300$

# 分析

一看到这道题目，暴力 DFS 是可以想出来的，但是这道题目的数据范围有亿点大，如果用暴力会直接 TLE。

但是它把数据范围开到了 $10^2$ 量级，说明算法时间很可能是 $HWN$ 这样的级别。

仔细一想，这道题和 P3958 似乎很像啊，都是判断走不走得通。在这道题目里，移动是需要花费 1 点能量的，然而只有在有药物的地方才能恢复能量，所以可以想到计算**药物之间的距离**来判断两个药物之间是否连通。

这样，从一个药物走到另一个药物就可以看做一条有向边，最后来判断连通性即可。

等一下！如果从一个药物走到另一个药物有残余能量怎么办？请睁大眼睛仔细看：

……，可以用来将能量**置为** $E_i$。

划重点，“置为”，这意味着前面剩下多少能量完全不重要，因为这是赋值而不是增加。

有了上面的理论，代码就好写了。

# 代码

```cpp
//我用的方法比较暴力，一共N+1次BFS，见笑了
#include <bits/stdc++.h>
using namespace std;
int h, w, n;
char C[205][205];
int e[205][205];
int id[205][205];
int r[305], c[305];
int dis[305][205][205];
int v[305];

int dx[] = {0, 1, 0, -1};

int dy[] = {1, 0, -1, 0};
vector<int> g[1005];

void bfs(int z) {//BFS搜出距离
	queue<pair<int, int> >q;
	q.push({r[z], c[z]});
	dis[z][r[z]][c[z]] = 1;
	while (!q.empty()) {
		pair<int, int> u = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int x2 = u.first + dx[i];
			int y2 = u.second + dy[i];
			if (x2 >= 1 && x2 <= h && y2 >= 1 && y2 <= w && dis[z][x2][y2] == 0x3f3f3f3f && C[x2][y2] != '#') {
				q.push({x2, y2});
				dis[z][x2][y2] = dis[z][u.first][u.second] + 1;
			}
		}
	}
}
int stx, sty, sx, sy;

int main() {
   //初始化是为了防止两个药物不连而产生的BUG
	memset(dis, 0x3f, sizeof(dis));
	cin >> h >> w;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> C[i][j];
			if (C[i][j] == 'T') {
				sx = i;
				sy = j;
			}
			if (C[i][j] == 'S') {
				stx = i;
				sty = j;
			}
		}
	}
	cin >> n;
	int fst = 0x3f3f3f3f;//记录起点有没有药物
	for (int i = 1; i <= n; i++) {
		int m;
		cin >> r[i] >> c[i] >> m;
		if (r[i] == stx && c[i] == sty) {
			fst = i;
		}
		e[r[i]][c[i]] = m;
		id[r[i]][c[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		bfs(i);
	}
   //建图
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (j == i) {
				continue;
			}
			if (dis[i][r[j]][c[j]] - 1 <= e[r[i]][c[i]]) {
				g[i].push_back(j);
			}
		}
		if (dis[i][sx][sy] - 1 <= e[r[i]][c[i]]) {
			g[i].push_back(0);//把终点看做0号节点进行建图
		}
	}
	if (fst == 0x3f3f3f3f) {
		cout << "No";
		return 0;
	}
   //判断连通性
	queue<int> q;
	q.push(fst);
	v[fst] = 1;
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (int y : g[u]) {
			if (v[y] == 0) {
				v[y] = 1;
				q.push(y);
			}
		}
	}
	if (v[0] != 0) {
		cout << "Yes";
	} else {
		cout << "No";
	}
	return 0;
}
```

---

## 作者：XP3301_Pipi (赞：0)

# ABC348D Medicines on Grid

一眼 BFS，用到了 SPFA 的思想。  

设 $val_{i,j}$ 为到达 $A_{i,j}$ 时最大能量值。  
仔细分析，发现使用普通 BFS 会出现一些问题：
- 如果只是把每个方格简单放到队列最后，队列不满足单调性；
- 如果使用优先队列，类似于 Dijkstra，此时边权既有正也有负，无法保证元素首次出队列时就是最大值。

所以，我们只能允许元素可以重复进入队列。  
也就是，每当一个方格能够被其他方格更新，就把这个方格推进队列，重复迭代，直到每个方格都不能再被更新。

假设从 $A_{i,j}$ 走到 $A_{k,l}$，$val_{k,l}$ 的更新如下：
```cpp
int tmp=max(rew[k][l],val[i][j]-1);
if(tmp>val[k][l]){
	val[k][l]=tmp;
	q.push(Node{k,l,tmp});
}
```
`rew[k][l]` 表示方格 $(k,l)$ 的药水提供的能量，若没有药水则为 $0$。

具体实现请看代码：
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define int long long
using namespace std;
const int N=515;
const long long INF=0x3f3f3f3f3f3f3f3fll;

inline void FileIO() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}

template<typename Type>
inline void read(Type& res) {
	Type x=0,f=1;
	char c=' ';
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	res=x*f;
}

int n,m,k;
char a[N][N];
bool vis[N][N];
int val[N][N];
int rew[N][N];	
int sx,sy,tx,ty;
int dx[]={-1,1,0,0},dy[]={0,0,-1,1};

bool Invalid(int x,int y){
	if(x<1||x>n||y<1||y>m) return 1;
	if(a[x][y]=='#') return 1;
	return 0;
}

struct Node{
	int x,y,z;
	bool operator<(const Node& tmp)const{
		return z<tmp.z;
	}
};

void Bfs(){
	queue<Node> q;
	q.push(Node{sx,sy,rew[sx][sy]});
	memset(val,-0x3f,sizeof(val));
	val[sx][sy]=rew[sx][sy];
	while(q.size()){
		int x=q.front().x;
		int y=q.front().y;
		q.pop();
		if(x==tx&&y==ty){
			puts("Yes");
			return;
		}
		if(val[x][y]<=0) continue;
		for(int i=0;i<4;i++){
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(Invalid(nx,ny)) continue;
			int tmp=max(rew[nx][ny],val[x][y]-1);
			if(tmp>val[nx][ny]){
				val[nx][ny]=tmp;
				q.push(Node{nx,ny,tmp});
			}
		}
	}
	puts("No");
}

signed main() {
//	不开longlong见祖宗！
//	检查数组大小！
//	禁止在int乘int时不开longlong！
//	STL数据类型拷贝赋值时间复杂度是 O(N)！
//	读入单个字符要用字符串，防毒瘤数据！
//	(1<<63)爆ll，(1<<31)爆int！！！
//	-std=c++14 -O2 -Wall -Wextra -Wshadow
	read(n),read(m);
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
	read(k);
	for(int i=1;i<=k;i++){
		int x,y,z;
		read(x),read(y),read(z);
		rew[x][y]=z;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='S') sx=i,sy=j;
			if(a[i][j]=='T') tx=i,ty=j;
		}
	}
	Bfs();
	return 0;
}







```

---

