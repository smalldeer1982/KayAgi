# [ABC317E] Avoid Eye Contact

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc317/tasks/abc317_e

$ H $ 行 $ W $ 列のグリッド状に分割されたフィールドがあります。  
北 (上側) から $ i $ 行目、西 (左側) から $ j $ 列目のマスは文字 $ A_{i,\ j} $ で表されます。各文字の意味は次の通りです。

- `.` : 空きマス。進入できる。
- `#` : 障害物。進入できない。
- `>`, `v`, `<`, `^` : それぞれ東・南・西・北を向いている人がいるマス。進入できない。人の視線は $ 1 $ マス分の幅を持ち、人が向いている方向にまっすぐ伸び、障害物や別の人に遮られる。(入出力例 $ 1 $ にある説明も参考にしてください。)
- `S` : スタート地点。進入できる。ちょうど $ 1 $ ヵ所だけ存在する。人の視線に入っていないことが保証される。
- `G` : ゴール地点。進入できる。ちょうど $ 1 $ ヵ所だけ存在する。人の視線に入っていないことが保証される。

ナオヒロくんはスタート地点にいて、東西南北への $ 1 $ マス分の移動を好きな回数行えます。ただし、進入できないマスへの移動やフィールドの外への移動はできません。  
彼が人の視線に一度も入らずにゴール地点に到達できるか判定して、できる場合はそのために最小で何回の移動が必要か求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ H,\ W\ \leq\ 2000 $
- $ A_{i,j} $ は `.`, `#`, `>`, `v`, `<`, `^`, `S`, `G` のいずれかである
- `S`, `G` は $ A_{i,\ j} $ の中にちょうど $ 1 $ 回ずつ現れる
- スタート地点・ゴール地点はともに人の視線に入っていない

### Sample Explanation 1

入力例 $ 1 $ について、$ 1 $ 人以上の視線に入っている空きマスを `!` で表すと次の図のようになります。 !\[image2\](https://img.atcoder.jp/abc317/8a40fc4c621cfef326cc25a1f69c0300.jpg) いくつかのマスについて具体的に説明すると次のようになります。(ここで、北から $ i $ 行目、西から $ j $ 列目のマスを $ (i,\ j) $ と表します。) - $ (2,\ 4) $ は $ (2,\ 2) $ にいる東を向いている人からの視線に入っているマスである。 - $ (2,\ 6) $ は $ (2,\ 2) $ にいる東を向いている人と $ (1,\ 6) $ にいる南を向いている人の $ 2 $ 人の視線に入っているマスである。 - $ (4,\ 5) $ は誰の視線にも入っていないマスである。$ (4,\ 7) $ にいる西を向いている人の視線は $ (4,\ 6) $ の障害物に遮られていて、$ (4,\ 1) $ にいる東を向いている人の視線は $ (4,\ 4) $ の人に遮られている。 ナオヒロ君は進入できないマス・視線に入っているマスのどちらも通らずにゴール地点へ行く必要があります。

### Sample Explanation 2

ナオヒロ君がゴール地点に到達できない場合は `-1` を出力してください。

## 样例 #1

### 输入

```
5 7
....Sv.
.>.....
.......
>..<.#<
^G....>```

### 输出

```
15```

## 样例 #2

### 输入

```
4 3
S..
.<.
.>.
..G```

### 输出

```
-1```

# 题解

## 作者：ran_qwq (赞：12)

[题目传送门](https://atcoder.jp/contests/abc317/tasks/abc317_e)

这场的 E 怎么那么水啊？

---
有一个 $n\times m$ 的迷宫，起点是 `S`，终点是 `G`，`#` 表示障碍物，不能走。你可以移动到相邻的格子。

此外，还有一些人，用 `>`，`v`，`<`，`^` 分别表示视线往东、南、西、北。视线会被障碍物或其他人挡住。

你不能被任何一个人看到，求最小步数。如果不能到达终点，输出 $-1$。

---
对于每个人，把他视线范围内的格子标记为不可走。跑一遍 bfs 即可。

因为每个格子最多只可能被 $4$ 个人看见，所以时间复杂度为 $O(nm)$。

[AT 提交记录](https://atcoder.jp/contests/abc317/submissions/44961307)

---

## 作者：FinderHT (赞：2)

### 题面描述

有一个田字格，分为 $H$ 行和 $W$ 列。

从上数第 $i$ 行，从左数第 $j$ 列的方格用字符 $A_{i, j}$ 表示。每个字符代表以下内容：

- `.` : 空方格。可通过。

- `#` : 障碍物。无法通过。

- `>`, `v`, `<`, `^` : 分别有人朝东、南、西、北的方格。无法通过。人的视线为一个正方形宽，沿人面对的方向笔直延伸，并被障碍物或其他人阻挡。

- `S` : 起点，可通过。起点只有一个，保证不在人的视线范围内。
- `G` : 终点，可通过。终点只有一个，保证不在人的视线范围内。

直弘位于起点，可以向东、西、南、北任意移动一格。但是，他不能进入无法通过的方格或离开场地。 
请判断他是否可以在不进入他人视线的情况下到达终点，如果可以，请找出这样做所需的最少移动次数。

### 思路

我们读入时记录起点和终点的坐标，然后遍历这个田字格，一旦发现字符 `>` `v` `<` `^`，就把这一行或这一列按题目要求标记。接着用广度优先搜索，建一个队列，我们先把起始位置（起点的坐标）入队，每次搜索取出队首坐标，然后用 $dx,dy$ 数组，分别判断从队首位置向四个方向前进一步是否满足条件所有条件（没超过边界，不为 `>` `v` `<` `^` `#` 以及这一行没被标记过）。如果满足，则把这个位置的坐标入队，并记录从起点走到这个位置的步数为从起点走到队首位置的步数 $+1$，最后判断从起点走到终点的步数是否不为 $0$，如果是，则输出答案；如果不是，则无解，输出 $-1$。

### 代码：

```cpp
#include<bits/stdc++.h>
#define fst first
#define snd second
using namespace std;
typedef pair<int,int> pii;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
char s[2005][2005];
bool use[2005][2005];
int ans[2005][2005];
int a,b,c,d;
signed main(){
    int h,w;
    cin>>h>>w;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cin>>s[i][j];
            if(s[i][j]=='S')a=i,b=j;//起点位置
            else if(s[i][j]=='G')c=i,d=j;//终点位置
        }
    }
    for(int i=1;i<=h;i++){//按要求标记有 > < ^ v 的行或列
        for(int j=1;j<=w;j++){
            if(s[i][j]=='>'){//这一行，向右标记
                int y=j+1;
                while(s[i][y]=='.'||use[i][y]&&y<=w)use[i][y++]=true;
            }
            else if(s[i][j]=='<'){//这一行，向左标记
                int y=j-1;
                while(s[i][y]=='.'||use[i][y]&&y>0)use[i][y--]=true;
            }
            else if(s[i][j]=='^'){//这一列，向上标记
                int x=i-1;
                while((s[x][j]=='.'||use[x][j])&&x>0)use[x--][j]=true;
            }
            else if(s[i][j]=='v'){//这一列，向下标记
                int x=i+1;
                while((s[x][j]=='.'||use[x][j])&&x<=h)use[x++][j]=true;
            }
        }
    }
    queue<pii>q;
    q.push(make_pair(a,b));//起点坐标入队
    while(q.size()){//广度优先搜索
        pii tmp=q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int xx=tmp.fst+dx[i];
            int yy=tmp.snd+dy[i];
            if(xx>0&&xx<=h&&yy>0&&yy<=w&&
            s[xx][yy]!='#'&&s[xx][yy]!='<'&&s[xx][yy]!='>'&&s[xx][yy]!='^'&&s[xx][yy]!='v'&&
            !ans[xx][yy]&&!use[xx][yy]){//如果满足所有条件
                q.push(make_pair(xx,yy));
                //把这个位置的坐标入队
                ans[xx][yy]=ans[tmp.fst][tmp.snd]+1;
                //记录答案
            }
        }
    }
    if(ans[c][d])cout<<ans[c][d];//如果从起点走到终点的步数不为0，输出答案
    else cout<<-1;//无解
    return 0;
}
```

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc317_e)

#### 思路

把每个守卫能看的地方标记为 $1$，包括他自己，可以提前预处理，然后跑个最短路就过了，注意无解输出 $-1$。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,xx,yy,a[30000010],b[30000010],c[30000010],h,t,kk,kk1,l,v[3010][3010]; 
int fx[11]={-1,0,1,0};///方向数组 
int fy[11]={0,1,0,-1};
char d[3010][3010];
void bfs()//spfa跑最短路 
{
	while(t <= h)
	{
		for(int i = 0;i <= 3;i++)
		{
			kk = a[t] + fx[i];
			kk1 = b[t] + fy[i];
			if(kk < 1 || kk1 < 1 || kk > n || kk1 > m || d[kk][kk1] == '#' || v[kk][kk1]) continue;
			a[++h] = kk;
			b[h] = kk1;
			v[a[h]][b[h]] = 1;
			c[h] = c[t] + 1;
		}
		if(a[t] == x && b[t] == y)
		{
			cout << c[t] << endl;
			l = 1;
			return;	
		}
		t++;
	}
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
		{
			cin >> d[i][j];
			if(d[i][j] == 'S') xx = i,yy = j;//找到起点和终点 
			else if(d[i][j] == 'G') x = i,y = j;
		}
	for(int i = 1;i <= n;i++)//预处理 
	{
		for(int j = 1;j <= m;j++)
		{
			if(d[i][j] == '^')
			{
				v[i][j] = 1;
				for(int z = i - 1;z >= 1;z--)
				{
					if(d[z][j] == '.' || d[z][j] == 'G' || d[z][j] == 'S') v[z][j] = 1;
					else break;
				}
			}
			if(d[i][j] == 'v')
			{
				v[i][j] = 1;
				for(int z = i + 1;z <= n;z++)
				{
					if(d[z][j] == '.' || d[z][j] == 'G' || d[z][j] == 'S') v[z][j] = 1;
					else break;
				}
			}
			if(d[i][j] == '<')
			{
				v[i][j] = 1;				
				for(int z = j - 1;z >= 1;z--)
				{
					if(d[i][z] == '.' || d[i][z] == 'G' || d[i][z] == 'S') v[i][z] = 1;
					else break;
				}
			}
			if(d[i][j] == '>')
			{
				v[i][j] = 1;
				for(int z = j + 1;z <= m;z++)
				{
					if(d[i][z] == '.' || d[i][z] == 'G' || d[i][z] == 'S') v[i][z] = 1;
					else break;
				}
			}
		}
	}
	t = h = 1;
	a[h] = xx,b[h] = yy;
	bfs(); 
	if(!l) cout << "-1" << endl;//无解 
	return 0;
}
```

---

## 作者：bryce (赞：1)

## 思路分析
先预处理出网格上能走和不能走的地方，再通过广搜搜寻起点到终点的最短距离。
## 代码
```cpp
#include<iostream>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 2e3 + 10;
int n, m, sx, sy, fx, fy;
int a[N][N], ax[4000001], ay[4000001], step[4000001];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
bool b[2001][2001];
void bfs(){
	int head = 0, tail = 1;
	b[sx][sy] = 1;
	ax[1] = sx;
	ay[1] = sy;
	while (head < tail){
		head++;
		for (int i = 0; i < 4; i++){
			int nx = ax[head] + dx[i], ny = ay[head] + dy[i];
			if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && !b[nx][ny] && a[nx][ny]){
				tail++;
				b[nx][ny] = 1;
				ax[tail] = nx;
				ay[tail] = ny;
				step[tail] = step[head] + 1;
			}
			if (nx == fx && ny == fy){
				cout << step[tail];
				return;
			}
		}
	}
    cout << -1;
}

signed main(){
    n = read(), m = read();
    for (int i = 1; i <= n; i++){
        int k;
        for (int j = 1; j <= m; j++){
            char c;
            cin >> c;
            if (c == '.') a[i][j] = 1;
            if (c == 'S') a[i][j] = 1, sx = i, sy = j;
            if (c == 'G') a[i][j] = 1, fx = i, fy = j;
            if (c == '>') a[i][j] = 2;
            if (c == '<') a[i][j] = 3;
            if (c == 'v') a[i][j] = 4;
            if (c == '^') a[i][j] = 5;
        }
    }
    //预处理部分
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (a[i][j] == 2){
                for (int k = j + 1; k <= m; k++){
                    if (a[i][k] != 1 && a[i][k] != -1){
                        break;
                    }
                    a[i][k] = -1;
                }
            }
            if (a[i][j] == 3){
                for (int k = j - 1; k >= 1; k--){
                    if (a[i][k] != 1 && a[i][k] != -1){
                        break;
                    }
                    a[i][k] = -1;
                }
            }
        }
    }
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++){
            if (a[j][i] == 4){
                for (int k = j + 1; k <= n; k++){
                    if (a[k][i] != 1 && a[k][i] != -1){
                        break;
                    }
                    a[k][i] = -1;
                }
            }
            if (a[j][i] == 5){
                for (int k = j - 1; k >= 1; k--){
                    if (a[k][i] != 1 && a[k][i] != -1){
                        break;
                    }
                    a[k][i] = -1;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++) if (a[i][j] == -1 || a[i][j] == 2 || a[i][j] == 3 || a[i][j] == 4 || a[i][j] == 5) a[i][j] = 0;
    }
    //广搜
    bfs();
    return 0;
}
```


---

## 作者：Dream_poetry (赞：1)

### 题意简述：
简单地说，就是从起点 $S$ 走到终点 $G$，其中 ```#``` 是障碍物不能走，且不能走到在别人的视线中，如果可以走过去，输出步数，否则输出 $-1$。

### 思路：
这道题还是很水的，一个 bfs 就能直接过。

首先先记录一下起点的坐标和终点的坐标。

但是要注意对四个符号的判断，这部分的话只需要不断把他们视线内的东西变为 ```!``` 即可。

以下是以 ```^``` 为例的代码。

```cpp
if(ch[i][j]=='^'){
   int ii=i-1,jj=j;
   while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&ii>=1) 
		ch[ii--][jj]='!';
}
```

处理完之后，直接 bfs，我们使用队列和 pair 的组合，用 pair 来储存坐标，用偏移量来辅助移动，用二维数组 $f$ 来储存步数，最后输出终点坐标的步数即可。

如果终点坐标的步数为零，说明无法到达，输出 $-1$ 即可。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int h,w,sx,sy,ex,ey;
char ch[2005][2005];
int fff[2005][2005];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
void bfs(){
    queue<pair<int,int> > q;
    q.push({sx,sy});
    while(q.size()){
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int xx=x+dx[i];
            int yy=y+dy[i];
            if(xx>=1 && xx<=h && yy>=1 
				&& yy<=w && !fff[xx][yy] && ch[xx][yy]!='!' 
				&& ch[xx][yy]!='#' && ch[xx][yy]!='<' && ch[xx][yy]!='>'  
				&&ch[xx][yy]!='^'&&ch[xx][yy]!='v'){
					
                q.push({xx,yy});
                fff[xx][yy]=fff[x][y]+1;
            }
        }
    }
}
signed main(){
    cin>>h>>w;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            cin>>ch[i][j];
            if(ch[i][j]=='S') 
				sx=i,sy=j; // 记录起点位置 
            if(ch[i][j]=='G') 
				ex=i,ey=j; // 记录终点位置 
        }
    }
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            if(ch[i][j]=='<'){
                int ii=i,jj=j-1;
                while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&jj>=1) 
					ch[ii][jj--]='!';
            }
			else if(ch[i][j]=='>'){
                int ii=i,jj=j+1;
                while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&jj<=w) 
					ch[ii][jj++]='!';
            }
			else if(ch[i][j]=='v'){
                int ii=i+1,jj=j;
                while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&ii<=h) 
					ch[ii++][jj]='!';
            }
			else if(ch[i][j]=='^'){
                int ii=i-1,jj=j;
                while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&ii>=1) 
					ch[ii--][jj]='!';
            }
        }
    }
    bfs();
    if(fff[ex][ey]!=0) 
		cout<<fff[ex][ey];
    else 
		cout<<-1;
    return 0;
}
```


---

## 作者：__Dist__ (赞：1)

### 题目描述

[Luogu](https://www.luogu.com.cn/problem/AT_abc317_e) | [Atcoder](https://atcoder.jp/contests/abc317)

### 思路讲解

用 $ch$ 数组来存每个字符。遍历 $ch$ 数组，找到每个 $ch_{i,j}$ 是 `^`、`v`、`<`、`>` 中的一个的位置，并按照指向的方向把这个人能看到的所有位置标记为 `!`，然后跑一遍 $bfs$，用 $step_{i,j}$ 代表 $(i,j)$ 到起点 $(sx,sy)$ 的最短距离。最后判断：如果终点 $step_{ex,ey} \ne 0$ 就输出 $step_{ex,ey}$，否则输出 $-1$。

个人觉得应该评橙。

### 代码环节
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int h,w;
int sx,sy,ex,ey;//起点、终点坐标
char ch[2005][2005];
int step[2005][2005];
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
void bfs()
{
    queue<pair<int,int> > q;//可能扩展的点
    q.push({sx,sy});//加入起点
    while(q.size())
    {
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        for(int i=0;i<4;i++)
        {
            int xx=x+dx[i];
            int yy=y+dy[i];
            if(xx>=1&&xx<=h&&yy>=1&&yy<=w&&!step[xx][yy]
            &&ch[xx][yy]!='!'&&ch[xx][yy]!='#'&&ch[xx][yy]!='<'&&ch[xx][yy]!='>'
            &&ch[xx][yy]!='^'&&ch[xx][yy]!='v')
            {
                q.push({xx,yy});
                step[xx][yy]=step[x][y]+1;
            }
        }
    }
}
signed main()
{
    cin>>h>>w;
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {
            cin>>ch[i][j];
            if(ch[i][j]=='S') sx=i,sy=j;
            if(ch[i][j]=='G') ex=i,ey=j;
        }
    }
    for(int i=1;i<=h;i++)
    {
        for(int j=1;j<=w;j++)
        {
            if(ch[i][j]=='<')
            //处理不同指向的箭头
            {
                int ii=i,jj=j-1;
                while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&jj>=1) ch[ii][jj--]='!';
            } else if(ch[i][j]=='>')
            {
                int ii=i,jj=j+1;
                while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&jj<=w) ch[ii][jj++]='!';
            } else if(ch[i][j]=='v')
            {
                int ii=i+1,jj=j;
                while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&ii<=h) ch[ii++][jj]='!';
            } else if(ch[i][j]=='^')
            {
                int ii=i-1,jj=j;
                while((ch[ii][jj]=='.'||ch[ii][jj]=='!')&&ii>=1) ch[ii--][jj]='!';
            }
        }
    }
    bfs();//广搜
    if(step[ex][ey]!=0) cout<<step[ex][ey];
    else cout<<-1;
    return 0;
}
```

---

## 作者：liruixiong0101 (赞：0)

## P0 题意：
有一个 $H\times W$ 的网格图，Naohiro 一开始在起点格子，他要走到终点格子，他可以上下左右移动，但是不可已被众人的目光所及，而墙壁可以阻挡目光。请问 Naohiro 从起点格子到终点格子的最短路径的长度是多少，如果无法到达终点格子，输出 `-1`。

## P1 思路：
看到这种题，第一眼就知道这肯定是 bfs，但是他不会给出被目光所及的格子，需要自己求。  
- 如果采用暴力，对于每一个人用 $O(H)$ 或 $O(W)$ 的时间复杂度求出他目光所及之处，这样的做法的时间复杂度为 $O(H^2\times W)$ 或 $O(H\times W^2)$，铁定超时。
- 但是我们可以将人的目光所及之处的位置用动态规划求解。  
  设 $f_{i,j,0/1/2/3}$ 为被 `v/>/^/<` 所及之处，然后按照各自的转移过程即可，时间复杂度 $O(H\times W)$。

bfs 就正常 bfs 即可。

## P2 代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
using Pii = pair<int, int>;

const int kMaxN = 2005, dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};

int n, m, sx, sy, ex, ey, dis[kMaxN][kMaxN];
char c[kMaxN][kMaxN];
bool f[kMaxN][kMaxN][4];
queue<Pii> q;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> c[i][j];
      c[i][j] == 'S' && (sx = i, sy = j);
      c[i][j] == 'G' && (ex = i, ey = j);
      dis[i][j] = -1;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      f[i][j][0] |= c[i][j] == 'v' | f[i - 1][j][0];  // 转移从上面来的
      f[i][j][1] |= c[i][j] == '>' | f[i][j - 1][1];  // 左边来的
      f[i][j][0] &= c[i][j] == 'v' | c[i][j] == '.';  // 不能是墙，但是可以让自己为开始
      f[i][j][1] &= c[i][j] == '>' | c[i][j] == '.';
    }
  }
  for (int i = n; i; i--) {
    for (int j = m; j; j--) {                         // 注意这里i,j要倒序
      f[i][j][2] |= c[i][j] == '^' | f[i + 1][j][2];  // 转移从下面来的
      f[i][j][3] |= c[i][j] == '<' | f[i][j + 1][3];  // 转移从右边来的
      f[i][j][2] &= c[i][j] == '^' | c[i][j] == '.';  // 与之前同理
      f[i][j][3] &= c[i][j] == '<' | c[i][j] == '.';
    }
  }
  for (dis[sx][sy] = 0, q.push({sx, sy}); q.size(); q.pop()) {
    int x = q.front().first, y = q.front().second;
    if (f[x][y][0] || f[x][y][1] || f[x][y][2] || f[x][y][3]) {
      continue;
    }
    for (int i = 0, nx, ny; i < 4; i++) {
      nx = x + dx[i], ny = y + dy[i];
      if (!f[nx][ny][0] && !f[nx][ny][1] && !f[nx][ny][2] && !f[nx][y][3] &&
          nx > 0 && ny > 0 && nx < n + 1 && ny < m + 1 && !~dis[nx][ny] && c[nx][ny] != '#') {
        q.push({nx, ny}), dis[nx][ny] = dis[x][y] + 1;
      }
    }
  }  // bfs
  cout << dis[ex][ey];
  return 0;
}
```

## P3 AC 记录：
<https://atcoder.jp/contests/abc317/submissions/44971043>

---

## 作者：tbdsh (赞：0)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-at-abc317-e)

[洛谷原题面](/problem/at_abc317_e)

[AtCoder 原题面](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc317_e)

有一个 $H$ 行 $W$ 列的网格场地。第 $i$ 行 $j$ 列是字符 $A_{i, j}$。每个字符的含义如下：

- `.`：一个空方块，可以通过。
- `#`：一个障碍物，无法通过。
- `>`、`v`、`<`、`^`：朝东、朝南、朝西、朝北的人所在的方块，无法通过。人的视线宽度为一个方块，并且沿着人的朝向直线延伸，直到被障碍物或其他人阻挡。
- `S`：起点方块，可以通过。只有一个起点方块，保证不会出现在任何人的视线中。
- `G`：目标方块，可以通过。只有一个目标方块，保证不会出现在任何人的视线中。

Naohiro 位于起点方块，可以任意次数地向东、向西、向南、向北移动一格。然而，他不能进入障碍方块或离开场地。  

请判断他是否可以到达目标方块而不进入任何人的视线。如果可以，找出所需的最小移动次数，否则，输出 `-1`。

# 分析
本题也是一道暴力题。

我们在读入完后预处理出每个点是否可以通行。因为要求出最小移动次数，同时每次移动一格，那么我们就可以使用 BFS 来解决。

最后输出答案即可。

那么，时间复杂度是多少呢？

实际上，一格格子最多被四个人扫到。那么预处理的时间复杂度实际上是 $O(H\times W)$ 而不是 $O(H^2\times W^2)$。

BFS 的时间复杂度为 $O(H\times W)$。

那么，总时间复杂度是 $O(H\times W)$ 的。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e3 + 5;
int n, m;
int fx[2][4] = {{1, -1, 0, 0}, {0, 0, 1, -1}};
bool vis[MAXN][MAXN];
int dis[MAXN][MAXN];
string s[MAXN];
struct Node{
  int x, y;
};
queue<Node> a;
void jl(int x, int y, int l){
  if (dis[x][y]){
    return ;
  }
  a.push({x, y});
  dis[x][y] = l;
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  int bx, by, ex, ey;
  for (int i = 1; i <= n; i++){
    cin >> s[i];
    s[i] = ' ' + s[i];
    for (int j = 1; j <= m; j++){
      if (s[i][j] == 'S'){
        bx = i, by = j;
      }else if (s[i][j] == 'G'){
        ex = i, ey = j;
      }else if (s[i][j] != '.'){
        vis[i][j] = 1;
      }
    }
  }
  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= m; j++){
      if (s[i][j] == '<'){
        int tmp = j - 1;
        while (tmp >= 1 && s[i][tmp] == '.'){
          vis[i][tmp] = 1;
          tmp--;
        }
      }else if (s[i][j] == '>'){
        int tmp = j + 1;
        while (tmp <= m && s[i][tmp] == '.'){
          vis[i][tmp] = 1;
          tmp++;
        }
      }else if (s[i][j] == '^'){
        int tmp = i - 1;
        while (tmp >= 1 && s[tmp][j] == '.'){
          vis[tmp][j] = 1;
          tmp--;
        }
      }else if (s[i][j] == 'v'){
        int tmp = i + 1;
        while (tmp <= n && s[tmp][j] == '.'){
          vis[tmp][j] = 1;
          tmp++;
        }
      }
    }
  }
  jl(bx, by, 1);
  while (a.size()){
    auto x = a.front();
    a.pop();
    vis[x.x][x.y] = 1;
    for (int i = 0; i < 4; i++){
      int dx = x.x + fx[0][i], dy = x.y + fx[1][i];
      if (dx >= 1 && dy >= 1 && dx <= n && dy <= m && vis[dx][dy] == 0){
        jl(dx, dy, dis[x.x][x.y] + 1);
      }
    }
  }
  cout << dis[ex][ey] - 1;
  return 0;
}
```

---

## 作者：happybob (赞：0)

提供一个非常无脑但不太好写的做法。

考虑每一个点是否在一个人视线中，只需要考虑四个方向不遇到障碍物的情况下第一个人的方向即可。

那就直接四个方向，每个方向二分一次，找到那个人的位置就做完了。复杂度 $O(n^2 \log n)$，假设 $n,m$ 同阶。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long

const int N = 2005, MOD = 1e9 + 7; // Remember to change

int n, m;
char c[N][N];

namespace FastIo
{
	#define QUICKCIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
	int read()
	{
		char ch = getchar();
		int x = 0, f = 1;
		while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
		while (ch == '-')
		{
			f = -f;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9')
		{
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	template<class T>
	void write(T x)
	{
		if (x < 0)
		{
			putchar('-');
			x = -x;
		}
		if (x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	template<class T>
	void writeln(T x)
	{
		write(x);
		putchar('\n');
	}
}

int sx, sy, ex, ey;
bool can[N][N];

int s1[N][N],s2[N][N],s3[N][N],s4[N][N],s5[N][N],s6[N][N];

int dis[N][N];

int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};

void bfs()
{
	queue<pair<int, int> > q;
	q.push(make_pair(sx,sy));
	memset(dis,-1,sizeof dis);
	dis[sx][sy]=0;
	while(q.size())
	{
		auto u=q.front();
		q.pop();
		for(int i=0;i<4;i++)
		{
			int nx=u.first+dx[i],ny=u.second+dy[i];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&can[nx][ny])
			{
				if(dis[nx][ny]==-1)
				{
					dis[nx][ny]=dis[u.first][u.second]+1;
					q.push(make_pair(nx,ny));
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++) 
		{
			can[i][j]=1;
			cin>>c[i][j];
			if(c[i][j]=='S') sx=i,sy=j;
			else if(c[i][j]=='G') ex=i,ey=j;
			else if(c[i][j]=='#'||c[i][j]=='>'||c[i][j]=='v'||c[i][j]=='<'||c[i][j]=='^') can[i][j]=0;
			s1[i][j]=s1[i][j-1]+s1[i-1][j]-s1[i-1][j-1]+(c[i][j]=='#');
			s2[i][j]=s2[i][j-1]+s2[i-1][j]-s2[i-1][j-1]+(c[i][j]=='>'||c[i][j]=='v'||c[i][j]=='<'||c[i][j]=='^');
			s3[i][j]=s3[i][j-1]+s3[i-1][j]-s3[i-1][j-1]+(c[i][j]=='>');
			s4[i][j]=s4[i][j-1]+s4[i-1][j]-s4[i-1][j-1]+(c[i][j]=='v');
			s5[i][j]=s5[i][j-1]+s5[i-1][j]-s5[i-1][j-1]+(c[i][j]=='<');
			s6[i][j]=s6[i][j-1]+s6[i-1][j]-s6[i-1][j-1]+(c[i][j]=='^');
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]=='.'&&can[i][j])
			{
				// 从上方
				bool f=0;
				int l=1,r=i-1;
				while(l<=r)
				{
					int mid=l+r>>1;	
					if(s1[i][j]-s1[i][j-1]-(s1[mid-1][j]-s1[mid-1][j-1])>=1)
					{
						l=mid+1;
					}
					else if(s2[i][j]-s2[i][j-1]-(s2[mid-1][j]-s2[mid-1][j-1])>1)
					{
						l=mid+1;
					}
					else
					{
						if(s4[i][j]-s4[i][j-1]-(s4[mid-1][j]-s4[mid-1][j-1])>0)
						{
							f=1;
							break;
						}
						r=mid-1;
					}
				}
				// 从左边
				l=1,r=j-1;
				while(l<=r)
				{
					int mid=l+r>>1;
					if(s1[i][j]-s1[i-1][j]-(s1[i][mid-1]-s1[i-1][mid-1])>=1)
					{
						l=mid+1;
					}
					else if(s2[i][j]-s2[i-1][j]-(s2[i][mid-1]-s2[i-1][mid-1])>1)
					{
						l=mid+1;
					}
					else
					{
						if(s3[i][j]-s3[i-1][j]-(s3[i][mid-1]-s3[i-1][mid-1])>0)
						{
							f=1;
							break;
						}
						r=mid-1;
					}
				} 
				// 从下方
				l=i+1,r=n;
				while(l<=r)
				{
					int mid=l+r>>1;
					if(s1[mid][j]-s1[mid][j-1]-(s1[i-1][j]-s1[i-1][j-1])>=1)
					{
						r=mid-1;
					}
					else if(s2[mid][j]-s2[mid][j-1]-(s2[i-1][j]-s2[i-1][j-1])>1)
					{
						r=mid-1;
					}
					else
					{
						if(s6[mid][j]-s6[mid][j-1]-(s6[i-1][j]-s6[i-1][j-1])>0)
						{
							f=1;
							break;
						}
						l=mid+1;
					}
				} 
				//从右边
				l=j+1,r=m;
				while(l<=r)
				{
					int mid=l+r>>1;
					if(s1[i][mid]-s1[i-1][mid]-(s1[i][j-1]-s1[i-1][j-1])>=1)
					{
						r=mid-1;
					}
					else if(s2[i][mid]-s2[i-1][mid]-(s2[i][j-1]-s2[i-1][j-1])>1)
					{
						r=mid-1;
					}
					else
					{
						if(s5[i][mid]-s5[i-1][mid]-(s5[i][j-1]-s5[i-1][j-1])>0)
						{
							f=1;
							break;
						}
						l=mid+1;
					}
				 }
				can[i][j]=!f;
			}
		}
	}
	bfs();
	cout<<dis[ex][ey]<<"\n";
	return 0;
}

/*
7 7
S..>.>.
G.^.#<.
....#<<
##<<#<<
##.#<##
..#<>.^
^.>.#.<
*/


```


---

## 作者：CJ_Fu (赞：0)

E 题现在水得离谱。

## 题目链接

[洛谷](https://www.luogu.com.cn/problem/AT_abc317_e)

[AtCoder](https://atcoder.jp/contests/abc317/tasks/abc317_e)

## 题目大意

给你一个 $H$ 行 $W$ 列的网格 $A$，其中 $A_{i,j}$ 是以下字符的一种：

- `.`：可以正常到达的区域。
- `#`：障碍，无法到达。
- `>`、`^`、`v`、`<`：表示这里有一个人，他视线的方向是右/上/下/左，定义他的**视线范围**为从他本身开始到他视线方向的第一个障碍物（`#`、边界或另一个人）。
- `S`：起点，保证不在**视线范围**内。
- `G`：终点，保证不在**视线范围**内。

Naohiro 从起点出发，每次可以向上下左右四个方向中走一格，求 Naohiro 到达终点且不经过**视线范围**的最短距离，若无法到达输出 $-1$。

$2\le H,W\le 1000$
## 思路分析

应该很容易想到这是广搜板子吧。

首先预处理出所有**视线范围**，然后把人和**视线范围**都看成障碍，然后以起点跑 BFS，就求出了起点到终点的最短距离。

预处理复杂度貌似是立方级别的？其实不然。考虑最劣的情况：最外围一圈站满了向内看的人，这时的人数是 $O(H+W)$ 级的，而遍历**视线范围**的复杂度是 $O(H)/O(W)$ 级的，所以总复杂度仍然是平方级的。

时间复杂度 $O(HW)$，常数巨大，但是不加优化都只跑了两百多毫秒，因为预处理的巨大常数基本上跑不满。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[2003][2003];
const int wall=1;
const int see=-1;
const int pass=0;
const int L=2;
const int R=5;
const int U=3;
const int D=4;
int sx,sy,ex,ey;
queue<pair<int,int> >q;
#define x first
#define y second
int dxl[]={0,0,1,-1};
int dyl[]={1,-1,0,0};
int vis[2003][2003];
signed main(){
	cin>>n>>m;
	for(int i=0;i<=n+1;i++){
		for(int j=0;j<=m+1;j++){
			a[i][j]=wall;
		}
	}// 先全部初始化为障碍，判断边界更方便
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch;
			cin>>ch;
			if(ch=='.') a[i][j]=pass;
			else if(ch=='<') a[i][j]=L;
			else if(ch=='>') a[i][j]=R;
			else if(ch=='^') a[i][j]=U;
			else if(ch=='v') a[i][j]=D;
			else if(ch=='S') a[sx=i][sy=j]=pass;
			else if(ch=='G') a[ex=i][ey=j]=pass;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==L){
				int ny=j-1;
				while(a[i][ny]==pass||a[i][ny]==see) a[i][ny]=see,ny--;
			}else 
			if(a[i][j]==R){
				int ny=j+1;
				while(a[i][ny]==pass||a[i][ny]==see) a[i][ny]=see,ny++;
			}else 
			if(a[i][j]==U){
				int nx=i-1;
				while(a[nx][j]==pass||a[nx][j]==see) a[nx][j]=see,nx--;
			}else 
			if(a[i][j]==D){
				int nx=i+1;
				while(a[nx][j]==pass||a[nx][j]==see) a[nx][j]=see,nx++;
			}
		}
	}// 预处理视线范围
	q.push({sx,sy}); vis[sx][sy]=1;
	while(!q.empty()){
		int nx=q.front().x,ny=q.front().y;
		q.pop();
		for(int i=0;i<4;i++){
			int Nx=nx+dxl[i],Ny=ny+dyl[i];
			if(vis[Nx][Ny]||a[Nx][Ny]!=pass) continue;
			vis[Nx][Ny]=vis[nx][ny]+1;
			q.push({Nx,Ny});
		}
	}// BFS
	cout<<(vis[ex][ey]?vis[ex][ey]-1:-1);
} 
```

---

## 作者：umcalla (赞：0)

## 题意

给定一个 $ H \times W$ 的矩阵，求出不经过人的视线从起点走到终点的最小步数，如果无法到达输出 $-1$。

## 思路

这道题 $H$ 和 $W$ 最大到 $2000$，所以用 $n^3$ 的预处理显然不行。

因为人看的方向有四种，那我们就可以正向并且反向处理每行每列上面人能看到的视线，随后正常搜索就可以了。

每行（或列）处理方式：设 $flag$ 为当前格子是否不能通过，如果该行（或列）的第 $i$ 项是人或障碍，那么就将当前格子设为无法通过,如果是人并且朝向与遍历方向一致，那么就将 $flag$ 设为 $true$，并将当前格子设为无法通过，否则将 $flag$ 设为 $false$。如果当前格子没有障碍或人并且 $flag = true$，那么就将当前格子设为无法通过。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sx,sy,ex,ey;
char a[2010][2010];
bool v[2010][2010];
int pos[6][4]={{1,0},{0,1},{-1,0},{0,-1}};
struct node{
	int x,y,step;
};
void bfs()
{
	queue<node> q;
	v[sx][sy]=1;
	q.push({sx,sy,0});
	while(q.size())
	{
		auto cur=q.front();
		q.pop();
		if(cur.x==ex&&cur.y==ey)
		{
			printf("%d",cur.step);
			return;
		}
		for(int i=0;i<4;i++)
		{
			int tx=cur.x+pos[i][0],ty=cur.y+pos[i][1];
			if(tx>=0&&tx<n&&ty>=0&&ty<m&&!v[tx][ty])
			{
				v[tx][ty]=1;
				q.push({tx,ty,cur.step+1});
			}
		}
	}
	printf("-1");
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		scanf("%s",a[i]);
		bool flag=0;
		for(int j=0;j<m;j++)
		{
			if(a[i][j]=='S')
				sx=i,sy=j;
			if(a[i][j]=='G')
				ex=i,ey=j;
			if(a[i][j]=='>')
			{
				v[i][j]=1;
				flag=1;
			}else if(a[i][j]=='<'||a[i][j]=='^'||a[i][j]=='v'||a[i][j]=='#')
			{
				v[i][j]=1;
				flag=0;
			}else
				v[i][j]=max(v[i][j],flag);
		}
		flag=0;
		for(int j=m-1;j>=0;j--)
		{
			if(a[i][j]=='<')
			{
				v[i][j]=1;
				flag=1;
			}else if(a[i][j]=='>'||a[i][j]=='^'||a[i][j]=='v'||a[i][j]=='#')
			{
				v[i][j]=1;
				flag=0;
			}else
				v[i][j]=max(v[i][j],flag);
		}
	}
	for(int j=0;j<m;j++)
	{
		bool flag=0; 
		for(int i=0;i<n;i++)
		{
			if(a[i][j]=='v')
			{
				v[i][j]=1;
				flag=1;
			}else if(a[i][j]=='<'||a[i][j]=='^'||a[i][j]=='>'||a[i][j]=='#')
			{
				v[i][j]=1;
				flag=0;
			}else
				v[i][j]=max(v[i][j],flag);
		}
		flag=0; 
		for(int i=n-1;i>=0;i--)
		{
			if(a[i][j]=='^')
			{
				v[i][j]=1;
				flag=1;
			}else if(a[i][j]=='<'||a[i][j]=='v'||a[i][j]=='>'||a[i][j]=='#')
			{
				v[i][j]=1;
				flag=0;
			}else
				v[i][j]=max(v[i][j],flag);
		}
	}	
	bfs(); 
	return 0;
}

```

---

## 作者：Failure_Terminator (赞：0)

## Solution

对于四个视野方向，我们分别对于每一行处理朝左看与朝右看的人，对于每一列处理向上看和向下看的人，将会被看到的可通过格子打上标记。

接着从起点开始 bfs，找到一条路径或判断没有可行的路径。

但是要注意，标记不要覆盖原数组，会导致一些错误，过不去下面的 hack。

时间复杂度为 $O(nm)$。

## Code

[hack](https://www.luogu.com.cn/paste/g0c59cz0)

[Code](https://atcoder.jp/contests/abc317/submissions/44979937)

---

## 作者：God_Max_Me (赞：0)

## 题意

一个地图，其中有一些守卫，他们的视线是一个直线，直到碰到障碍物，现在主角在 $\left(qx,qy\right)$，在地图上是 `S`，现在要去终点 $\left(zx,zy\right)$，不能出现在守卫视线中，问能否到达，若能，输出最小花费，若不能，输出 $-1$。

## 思路

首先处理一下守卫的问题，每找到一个守卫就将他视线内的直线变成 `#`，然后朴素 bfs，没什么好讲的，但是要注意，守卫的视线只能在 `.` 的方格内穿过，遇到其他方格会被挡住。

## 代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
template<typename P>
inline void read(P &x){
   	P res=0,f=1;
   	char ch=getchar();
   	while(ch<'0' || ch>'9'){
   		if(ch=='-') f=-1;
   		ch=getchar();
   	}
   	while(ch>='0' && ch<='9'){
   		res=res*10+ch-'0';
   		ch=getchar();
	}
	x=res*f;
}
int T=1;
char mapp[2020][2020];
int n,m;
int xx[4]={1,0,-1,0};
int yy[4]={0,-1,0,1};
map<char,int> fx;
bool vis[2020][2020];
bool pd[2020][2020];
void Init(int x,int y,int fx){
	pd[x][y]=1;
	int nx=x+xx[fx];
	int ny=y+yy[fx];
	if(nx>=1 && nx<=n && ny>=1 && ny<=m && mapp[nx][ny]=='.') Init(nx,ny,fx);
}
int qx,qy,zx,zy;
struct node{
	int x,y,s;
};
void bfs(int x,int y){
	queue<node> q;
	q.push(node{x,y,0});
	vis[x][y]=1;
	while(!q.empty()){
		int X=q.front().x;
		int Y=q.front().y;
		int S=q.front().s;
		q.pop();
		if(X==zx && Y==zy){
			cout<<S<<endl;
			exit(0);
		}
		
		for(int i=0;i<=3;++i){
			int nx=X+xx[i];
			int ny=Y+yy[i];
			if(nx>=1 && nx<=n && ny>=1 && ny<=m && !vis[nx][ny] && (mapp[nx][ny]=='.' || mapp[nx][ny]=='G')){
				vis[nx][ny]=1;
				q.push(node{nx,ny,S+1});
			}
		}
	}
}
signed main(){
	read(n),read(m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>mapp[i][j];
			if(mapp[i][j]=='S') qx=i,qy=j;
			if(mapp[i][j]=='G') zx=i,zy=j;
		}
	}
	fx['v']=0;
	fx['<']=1;
	fx['^']=2;
	fx['>']=3;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(mapp[i][j]!='.' && mapp[i][j]!='S' && mapp[i][j]!='#' && mapp[i][j]!='G'){
				int ff=fx[mapp[i][j]];
				Init(i,j,ff);
			}
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(pd[i][j]==1) mapp[i][j]='#';
		}
	}
	bfs(qx,qy);
	cout<<-1<<endl;
	return 0;
}
~~~

---

## 作者：Imken (赞：0)

题意：给定一个 $H\times W$ 的网格、起点和终点，其中包含空方块、障碍物以及朝向不同方向的人物及视线。目标是确定一个人从特定点出发是否能够在不进入任何人的视线范围的情况下到达目标点。这个人可以向任意方向移动，但不能移动到障碍物上或进入别人的视线范围。如果存在有效的路径，则任务是找到达到目标所需的最小移动次数。

依照题意模拟即可，把在他人视线内的点标记一下，跑一遍广搜就可以出答案。

Code:

```cpp
vector<pair<int, int> > watchers;
queue<pair<int, int> > q;

int delta_x[] = { -1, 1, 0, 0 },
	delta_y[] = { 0, 0, -1, 1 };

int main()
{
	init_io();
	memset(res, 0x3f, sizeof res);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> mp[i][j];
			if (mp[i][j] == 'S') begin_x = i, begin_y = j;
			else if (mp[i][j] == 'G') end_x = i, end_y = j;
			else if (mp[i][j] != '.' && mp[i][j] != '#') watchers.push_back({ i, j });
		}
	}
	mp[end_x][end_y] = '.';

	// 标记被监视的格点
	for (pair<int, int> watch : watchers) {
		int x = watch.first, y = watch.second;
		char direction = mp[x][y];
		switch (direction) {
		case '>':
			for (int i = y + 1; i <= m; i++) {
				if (mp[x][i] == '.' || mp[x][i] == 'X') mp[x][i] = 'X';
				else break;
			}
			break;
		case '<':
			for (int i = y - 1; i >= 1; i--) {
				if (mp[x][i] == '.' || mp[x][i] == 'X') mp[x][i] = 'X';
				else break;
			}
			break;
		case 'v':
			for (int i = x + 1; i <= n; i++) {
				if (mp[i][y] == '.' || mp[i][y] == 'X') mp[i][y] = 'X';
				else break;
			}
			break;
		case '^':
			for (int i = x - 1; i >= 1; i--) {
				if (mp[i][y] == '.' || mp[i][y] == 'X') mp[i][y] = 'X';
				else break;
			}
			break;
		}
	}

	q.push({ begin_x, begin_y });
	res[begin_x][begin_y] = 0;
	while (!q.empty()) {
		pair<int, int> tp = q.front(); q.pop();
		int x = tp.first, y = tp.second;
		for (int i = 0; i < 4; i++) {
			int new_x = x + delta_x[i], new_y = y + delta_y[i];
			if (new_x > n || new_x < 1 || new_y > m || new_y < 1) continue;
			if (mp[new_x][new_y] != '.') continue;
			if (res[new_x][new_y] >= 0x3f3f3f3f) {
				q.push({ new_x, new_y });
				res[new_x][new_y] = res[x][y] + 1;
			}
		}
	}

	if (res[end_x][end_y] >= 0x3f3f3f3f) cout << -1 << '\n';
	else cout << res[end_x][end_y] << '\n';
	return 0;
}
```


---

