# Ice Cave

## 题目描述

你在一个 $n \times m$ 的网格中，有些格子是完整的冰块，有些是破碎的冰块。如果你走到完整的冰块上，下一秒它会变成碎冰；如果你在碎冰上，你会掉下去。你不能在原地停留。

现在你在 $(r_1,c_1)$ 上，保证该位置是一块碎冰。你要从 $(r_2,c_2)$ 掉下去，问是否可行。

## 说明/提示

$1 \le n,m \le 500$。  

$1 \le r_1,r_2 \le n,1 \le c_1,c_2 \le m$。

## 样例 #1

### 输入

```
4 6
X...XX
...XX.
.X..X.
......
1 6
2 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 4
.X..
...X
X.X.
....
.XX.
5 3
1 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 7
..X.XX.
.XX..X.
X...X..
X......
2 2
1 6
```

### 输出

```
YES
```

# 题解

## 作者：zhangqiuyanAFOon2024 (赞：4)

### 思路
直接暴力 `bfs`。

先从起点开始，然后向四个方向拓展，再修改一下状态。

如果能走到重点就是成功。

实在没什么好说的，直接上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e2+10;
char mp[N][N];
int qx,qy,zx,zy,dx[5]={0,0,-1,1},dy[5]={-1,1,0,0};
void solve(){
	queue<pair<int,int> >q;
	q.push({qx,qy});
	while(q.size()){
		int tx=q.front().first,ty=q.front().second;
		for(int i=0;i<4;i++){
			int xx=tx+dx[i],yy=ty+dy[i];
			if(xx==zx&&yy==zy&&mp[xx][yy]=='X'){
				cout<<"YES";
				return;
			}
			if(mp[xx][yy]=='.') mp[xx][yy]='X',q.push({xx,yy});
		}
		q.pop();
	}//bfs
	cout<<"NO";
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>mp[i][j];
	cin>>qx>>qy>>zx>>zy;
	solve();
	return 0;
}

---

## 作者：Miraik (赞：2)

给一个可能更加直观的做法？

题目保证起点是碎冰，考虑分别考虑终点是碎冰/整冰的情况：

- 终点是碎冰

这个很好做，因为我们只要走到终点就可以掉下去，所以直接 dfs 判断是否能从起点到达终点即可。

- 终点是整冰

实际上也就是上面一种情况的扩展。

考虑到我们如果来到了终点，肯定要再往自己周围走一步，然后走回来掉下去。

也就是说：当我们来到终点时，终点周围的四个点必须还有至少一个点是整冰。

那我们只需要先枚举这个终点周围的整冰位置，再 dfs 判断不经过这个点的前提下能否从起点到达终点即可。

$\texttt{corner case：}$ 请注意 $n=m=1$ 的情况。如果 dfs 时直接判断当前点是否为终点，可能就会寄（WA on #5）。可以特判，或者改为在 dfs 拓展新的点时判断是否为终点。

[简短的代码](https://codeforces.com/problemset/submission/540/167655926)

---

## 作者：OIer_Hhy (赞：1)

CF *2000 水蓝一道。

一开始我以为 dfs 能过，结果 TLE on #14 了。

TLE CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+100;
int n,m,sx,sy,fx,fy;
char a[maxn][maxn];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
void dfs(int x,int y){
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++) cout<<a[i][j];
//		puts("");
//	}
//	puts("");
	if(x==fx&&y==fy&&a[x][y]=='K'){
		puts("YES");
		exit(0);
	}
	for(int i=0;i<4;i++){
		int nx=x+dx[i];
		int ny=y+dy[i];
		if(nx==fx&&ny==fy&&a[nx][ny]=='X'){
			a[nx][ny]='K';
			dfs(nx,ny);
		} 
		if(nx>0&&nx<=n&&ny>0&&ny<=m&&a[nx][ny]=='.'){
			a[nx][ny]='X';
			dfs(nx,ny);
			a[nx][ny]='.'; 
		}
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	} 
	cin>>sx>>sy>>fx>>fy; 
	dfs(sx,sy);
	cout<<"NO";
	return 0;
}
```

于是我只能 bfs（不会 bfs 的来[这里](https://blog.csdn.net/aliyonghang/article/details/128724989?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522171799639816800180645086%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=171799639816800180645086&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-128724989-null-null.142^v100^pc_search_result_base6&utm_term=bfs&spm=1018.2226.3001.4187)）……

显然，没到终点却踩到了碎冰，就 GAME OVER 了。

所以，我们只能走正常的冰块（`a[nx][ny]=='.'`），经过一次之后变成一块碎冰（`a[nx][ny]='X'`）。

如果下一步能走到终点并且终点是一块碎冰（能掉下去），就输出 YES。

若无法走到终点或无法从终点掉下去，输出 NO。


AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+100;
int n,m,sx,sy,fx,fy;
char a[maxn][maxn];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
struct node{
	int x,y; 
};
void bfs(){
	queue<node> q;
	node tmp=node{sx,sy};
	q.push(tmp);
	while(!q.empty()){
		tmp=q.front();
		for(int i=0;i<4;i++){
			int nx=tmp.x+dx[i];
			int ny=tmp.y+dy[i];
			if(nx==fx&&ny==fy&&a[nx][ny]=='X'){
				cout<<"YES";
				exit(0);
			} 
			if(nx>0&&nx<=n&&ny>0&&ny<=m&&a[nx][ny]=='.'){
				node res;
				res.x=nx;
				res.y=ny;
				a[nx][ny]='X';
				q.push(res);
			}
		}
		q.pop();
	} 
	cout<<"NO";
	return ;
} 
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	} 
	cin>>sx>>sy>>fx>>fy; 
	bfs();
	return 0;
}

```

---

## 作者：迟暮天复明 (赞：1)

[题面](https://codeforces.com/contest/540/problem/C)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16196084.html)

题意：
地图上有一些点是完好的，有一些点是破损的，破损的点踩了会掉下去，完好的点踩了会破损。问：从点 $(sx,sy)$ 出发能不能在 $(ex,ey)$ 点掉下去？

-----
分类讨论。

满足条件的有三种可能。

1. 起点到终点有一条只经过完好点的路径，终点完好，且与终点相邻的点中存在两个完好的点。

比如下面这组数据：
```text
3 3
...
.XX
...
3 3
1 1
```
合理的路径是 $(3,3)\to(3,2)\to(3,1)\to(2,1)\to(1,1)\to(1,2)\to(1,1)$ .

明显的，第一次走到 $(ex,ey)$ 让其破损，这时且与终点相邻的点中至少存在一个完好的点。这样能保证走到那个点再踩回终点掉下去。

2. 起点到终点有一条只经过完好点的路径，终点破损。

比如下面这组数据：
```text
3 3
XXX
.XX
...
3 3
1 1
```
合理的路径是 $(3,3)\to(3,2)\to(3,1)\to(2,1)\to(1,1)$ .

明显的，直接走到 $(ex,ey)$ 就掉下去了。

3. 起点与终点相邻，终点完好，且与终点相邻的点中存在一个完好的点。

比如下面这组数据：
```text
2 2
..
XX
2 1
1 1
```
与第一种情况相比，这里的起点承担了与终点相邻的其中一个完好点的作用。可以从起点一步走到终点使其破损。
其他不存在合理可能。

于是这个题的解法就明朗了。做一遍 BFS 判断起点到终点之间是否存在只经过完好点的路径，再判断是否满足上述三种情况之一即可。

[代码](https://paste.ubuntu.com/p/vvY7FPZ2dj/)

---

## 作者：封禁用户 (赞：1)

这道题翻译有点错误，最后应该是掉进终点。

## 基本思路:$\text{DFS}$

由于好冰踩了一下就变成碎冰了，所以我们可以把所有的碎冰看成是被经过了一次的好冰，因此可以先设一个$\text{vis}$数组，记录把所有的冰被经过了几次。(好冰的$\text{vis}$设为$0$，碎冰的$\text{vis}$设为$1$)，再从起点开始$\text{DFS}$。

$\text{DFS}$时若遇到一个点在$\text{vis}$中的值为$0$，把它标记为$1$(把好冰标成经过一次，也就是碎冰)，然后继续从这个点往下搜索；当遇到一个点在$\text{vis}$中的值为$1$(它已经成为碎冰，踩一次就会掉下去)，如果它是终点，就输出$\text{YES}$，然后结束程序。如果不是终点，就不用往下搜索了。(但不结束搜索，因为还有其它可走的点)

如果$\text{DFS}$结束但程序还没结束，直接输出$\text{NO}$就可以了。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,vis[1005][1005];
char mp[1005][1005];
int dx[]={0,0,-1,1};
int dy[]={-1,1,0,0};//四个方向
int nx,ny,mx,my;//nx和ny是起点,mx和my是终点
void dfs(int ex,int ey)
{
	for(int i=0;i<4;i++)
	{
		int zx=ex+dx[i];
		int zy=ey+dy[i];
		if(zx>0&&zx<=n&&zy>0&&zy<=m)//没有越界
		{
			if(vis[zx][zy]==1)//如果是碎冰
			{
				if(zx==mx&&zy==my)//如果是终点
				{
					cout<<"YES";//输出YES
					exit(0);//结束程序
				}
			}
			else//如果是好冰
			{
				vis[zx][zy]=1;//记为碎冰
				dfs(zx,zy);//继续搜索
			}
		}
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>mp[i][j];
			if(mp[i][j]=='X')
				vis[i][j]=1;//碎冰标记为好冰经过一次
		}
	}
	cin>>nx>>ny>>mx>>my;
	dfs(nx,ny);
	cout<<"NO";//程序未结束输出NO
	return 0;
}
```


---

## 作者：Limit (赞：1)

~~题目有毒呀，翻译有问题...~~...
先码了一个DFS ~~瞄了一眼题解里都是dfs~~
```pascal
const z:array[1..4,1..2]of -1..1=((1,0),(0,1),(-1,0),(0,-1));
var i,j,k:longint;
    m,n:longint;
    ch:char;
    a,b:array[0..100,0..100]of boolean;
    x,y:array[0..10000]of longint;
    fx,fy,lx,ly:longint;
procedure yes;
begin
  write('YES');
  halt;
end;
procedure pd(x,y:longint);//判断是否可以落到终点
var i:longint;
begin
  if not a[x,y] then yes;//如果终点就是碎冰那么可以直接掉下去
  for i:=1 to 4 do if a[x+z[i,1],y+z[i,2]] then yes;//不是碎冰要看看旁边有没有浮冰
end;
procedure dfs(x,y:longint);//深度优先搜索,就是暴力呀QAQ
var i:longint;
begin
  if(x=lx)and(y=ly)then//到终点了
  begin
  pd(x,y);
  exit;
  end;
  if not a[x,y] then exit;
  a[x,y]:=false;
  for i:=1 to 4 do
  dfs(x+z[i,1],y+z[i,2]);
  a[x,y]:=true;
end;
begin
  readln(m,n);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='X' then a[i,j]:=false;
      if ch='.' then a[i,j]:=true;
    end;
    readln;
  end;
  readln(fx,fy,lx,ly);
  a[fx,fy]:=true;
  dfs(fx,fy);
  write('NO');//到不了QAQ
end.
```
~~成功TLE祭~~
又费力改成bfs

```pascal
const z:array[1..4,1..2]of -1..1=((1,0),(0,1),(-1,0),(0,-1));
var i,j,k:longint;
    m,n,h,t:longint;
    ch:char;
    a,b:array[0..601,0..601]of boolean;
    x,y:array[0..1000000]of longint;
    fx,fy,lx,ly:longint;
procedure yes;
begin
  write('YES');
  halt;
end;
procedure no;
begin
  write('NO');
  halt;
end;
begin
  readln(m,n);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='X' then a[i,j]:=false;
      if ch='.' then a[i,j]:=true;
    end;
    readln;
  end;
  readln(fx,fy,lx,ly);
  a[fx,fy]:=true;
  if (fx=lx)and(fy=ly) then//如果起点就是终点(玄学)，那么要去旁边跳一下
  begin
    k:=0;
    for i:=1 to 4 do
    if a[lx+z[i,1],ly+z[i,2]] then inc(k);
    if k<1 then no else yes;
  end;
  if a[lx,ly] then//如果终点是浮冰，那么需要从一个浮冰过来，再去一个浮冰跳一下
  begin
    k:=0;
    for i:=1 to 4 do
    if a[lx+z[i,1],ly+z[i,2]] then inc(k);
    if k<2 then no;//浮冰数>=2有可能才行
  end else
  a[lx,ly]:=true;//终点赋值为true
  h:=1;
  t:=1;
  x[1]:=fx;
  y[1]:=fy;
  repeat//裸的bfs
    if(x[t]=lx)and(y[t]=ly)then yes;
    for i:=1 to 4 do
    if a[x[t]+z[i,1],y[t]+z[i,2]] then
    begin
      inc(h);
      a[x[t]+z[i,1],y[t]+z[i,2]]:=false;
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
    end;
    inc(t);
  until t>h;
  no;
end.
```
~~除了题目翻译有问题，其他都还行...吧~~

---

## 作者：liangjindong0504 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF540C)\
[CF 题目传送门](https://codeforces.com/problemset/problem/540/C)

CF 难度：2000

~~这道题真不错，成功解决了我找不到题的烦恼。~~

其实这题评蓝有点高了。

前置知识：搜索（你没看错，就是爆搜）

### 大体思路

首先，如果你踩到碎冰上（当然不是起点或终点），你就直接掉下去了，到不了终点了。（废话）

于是，我们便得出了，要规划一条路径从起点到终点，且除去这两个点，其他都是完整冰块。

以上这条，直接搜索即可。

到了终点，怎么判断能不能掉下去呢？

首先，如果这一个点就是碎冰，直接掉下去，输出 ```YES```。

接下来，就是终点是完整的冰块的情况了。

明确一点，即如果可以到达终点，且终点旁边有大于一块完整的冰块，则一定可行。（因为可以到达终点，所以可以走到其中一个，然后走到终点，再走到另一个，最后回到终点，掉下去）。

当然，如果你只考虑了这么多，那么你会得到一个~~很好的~~结果：WA on 23。

具体是什么原因呢？~~点开数据~~显然，如果起点和终点挨在一起，而起点是碎冰，终点旁边有一块完整冰块，那么肯定可行。但是，此时没有特判，所以因为终点旁边仅有一块完整冰块，程序还是会给出 ```NO```。

于是，再将这种情况特判一下，就可以快乐地 AC 了。

### 完整代码

码风较丑，勿喷。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y;
};
int n,m,qx,qy,zx,zy,cnt;
int func[4][2]={1,0,0,1,-1,0,0,-1};
bool vis[510][510],find_ans;
char a[510][510];
queue<node>q;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j];
	}
	scanf("%d%d%d%d",&qx,&qy,&zx,&zy);
	//统计终点旁边完整冰块个数 
	for(int i=0;i<4;i++){
		int xx=zx+func[i][0],yy=zy+func[i][1];
		if(xx&&yy&&xx<=n&&yy<=m&&a[xx][yy]=='.') cnt++;
	}
	//搜索 
	q.push((node){qx,qy});
	while(!q.empty()){
		if(find_ans) break;
		int kx=q.front().x,ky=q.front().y;
		q.pop(); 
		for(int i=0;i<4;i++){
			int xx=kx+func[i][0],yy=ky+func[i][1];
			if(!vis[xx][yy]&&xx&&yy&&xx<=n&&yy<=m){
				if(a[xx][yy]=='.'){
					vis[xx][yy]=1;
					q.push((node){xx,yy});
				}else if(xx==zx&&yy==zy){
					vis[xx][yy]=find_ans=1;
					break;
				}
			}
		}
	}
	if(!vis[zx][zy]) printf("NO");//到不了，当然是NO 
	else if(a[zx][zy]=='X') printf("YES");//是碎冰，当然是YES 
	else if(abs(qx-zx)+abs(qy-zy)==1&&cnt>=1) printf("YES");//这就是那个特判 
	else if(cnt<=1) printf("NO");//如果只有一个碎冰在它周围，是NO（到终点了，走不了） 
	else printf("YES");//剩下的当然就是YES了 
	return 0;
}
```

---

## 作者：xixike (赞：0)

[博客食用更佳](https://www.cnblogs.com/xixike/p/15509464.html)

# Description

> [Luogu传送门](https://www.luogu.com.cn/problem/CF540C)
>
> [Codeforces传送门](https://codeforces.com/problemset/problem/540/C)

题目翻译有一点问题，应该是问能否掉进**终点**。

# Solution

考虑直接 dfs，蒟蒻第一遍写时，是先从搜到起点搜到终点，然后再从终点开始搜，判断能否搜回来，然而…… ```Time limit exceeded on test 14```

然后我就想为什么会 T，后来我发现搜到终点之后就不用再搜了，直接判断终点的上下左右有没有**好冰**即可。

代码里有注释。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n, m, flag;
char s[510][510];
int sx, sy, ex, ey;
int vis[510][510];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

inline bool judge(int x, int y){
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

inline int check(int x, int y){//判断 (x, y) 上下左右有没有好冰
    if(vis[x][y] == 2) return 1;//自己就是碎冰，直接 YES
    for(int i = 0; i < 4; ++i){
        int mx = x + dx[i];
        int my = y + dy[i];
        if(judge(mx, my) && !vis[mx][my]) return 1;
    }
    return 0;
}

inline void dfs(int x, int y){
    if(flag) return;
    if(x == ex && y == ey)//到终点直接判
        return flag = check(x, y), void();
    for(int i = 0; i < 4; ++i){//向 4 个方向搜索
        int mx = x + dx[i];
        int my = y + dy[i];
        if(judge(mx, my) && (!vis[mx][my] || (mx == ex && my == ey))){//没有走过的点 或 终点
            vis[mx][my]++;
            dfs(mx, my);
        }
    }
    return;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i){
        scanf("%s", s[i] + 1);
        for(int j = 1; j <= m; ++j)
            vis[i][j] = (s[i][j] == 'X');//把为碎冰的点 vis 初值赋为 1，表示不能走了。
    }
    scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
    dfs(sx, sy);
    puts(flag ? "YES" : "NO");
    return 0;
}
```

# End


---

## 作者：Alarm5854 (赞：0)

首先这道题目翻译有点问题，应为掉进终点，而不是掉进起点，其他没什么问题，希望翻译的人能改一下。
### 解题思路：
1. 做这道题目要学会深搜与回溯~~(其实我也不会很多，这是我AC的第一道搜索题)~~，但是不能暴搜，否则时间复杂度为$O(2^{n+m})$，第14个点就[**TLE**](https://www.luogu.org/recordnew/show/20639887)了，需要剪枝，额外开一个**int**型数组，可以的标0，不行的标-1，这样时间复杂度为$O(nm)$，能**AC**本题了。
1. 在搜索时要注意，没到终点时需要的是好冰，到终点时要碎冰，需要特判。
1. 搜索时往4个方向依次搜索，只要有一个路径可行，那就整体可行了，可用或运算。
1. 不要被错误的翻译误导，到了终点就好了，不需要回到起点。
### 完整代码如下：
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    bool finds;
    int n,m,sx,sy,tx,ty,flag,pos[505][505];//剪枝用
    char str[505][505];//储存字符串，下标从0开始
    bool work(int _1,int _2,int _3,int _4)//_1代表当时的x点，_2代表当时的y点，_3代表目标x点，_4代表目标y点
    {
        if(!~pos[_1][_2]) return false;//如果这个点不可行，直接返回假值
        if(_1==_3-1&&_2==_4)//第一种情况，当前位置在终点正上方
        {
            if(str[_3-1][_4-1]=='X') return true;//如果为碎冰，直接返回真值；否则，要判断三个方向有无好冰
            if(_3<n&&str[_3][_4-1]=='.') return true;
            if(_4<m&&str[_3-1][_4]=='.') return true;
            if(_4>1&&str[_3-1][_4-2]=='.') return true;
            return false;
        }
        if(_1==_3&&_2==_4-1)//第二种情况，当前位置在终点正左方
        {
            if(str[_3-1][_4-1]=='X') return true;
            if(_3<n&&str[_3][_4-1]=='.') return true;
            if(_4<m&&str[_3-1][_4]=='.') return true;
            if(_3>1&&str[_3-2][_4-1]=='.') return true;
            return false;
        }
        if(_1==_3+1&&_2==_4)//第三种情况，当前位置在终点正下方
        {
            if(str[_3-1][_4-1]=='X') return true;
            if(_4<m&&str[_3-1][_4]=='.') return true;
            if(_3>1&&str[_3-2][_4-1]=='.') return true;
            if(_4>1&&str[_3-1][_4-2]=='.') return true;
            return false;
        }
        if(_1==_3&&_2==_4+1)//第四种情况，当前位置在终点正右方
        {
            if(str[_3-1][_4-1]=='X') return true;
            if(_3<n&&str[_3][_4-1]=='.') return true;
            if(_3>1&&str[_3-2][_4-1]=='.') return true;
            if(_4>1&&str[_3-1][_4-2]=='.') return true;
            return false;
        }
    /*如果四种情况都不是，说明还没到终点*/
        bool ans=false;
        if(_1<n&&str[_1][_2-1]=='.') str[_1][_2-1]='X',ans|=work(_1+1,_2,_3,_4),str[_1][_2-1]='.';//判断下方向是否能走，注意判断是否越界，否则RE
        if(_2<m&&str[_1-1][_2]=='.') str[_1-1][_2]='X',ans|=work(_1,_2+1,_3,_4),str[_1-1][_2]='.';//判断右方向是否能走
        if(_1>1&&str[_1-2][_2-1]=='.') str[_1-2][_2-1]='X',ans|=work(_1-1,_2,_3,_4),str[_1-2][_2-1]='.';//判断上方向是否能走
        if(_2>1&&str[_1-1][_2-2]=='.') str[_1-1][_2-2]='X',ans|=work(_1,_2-1,_3,_4),str[_1-1][_2-2]='.';//判断左方向是否能走
        if(!ans) pos[_1][_2]=-1;//最重要的一句，在无解的情况下，一定要做标记，否则TLE
        return ans;
    }
    int main()
    {
        scanf("%d%d",&n,&m);
        while(getchar()!='\n');//把一行剩下来的换行符吃掉
        for(int i=0;i<n;i++)
            scanf("%s",str[i]);
        scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
        finds=work(sx,sy,tx,ty);
        if(finds) printf("YES");
        else printf("NO");
        return 0;
    }
```
[**结果**](https://www.luogu.org/recordnew/show/20640242)  
这是我发的第二篇题解，希望这篇题解能够帮助你们AC这道题，这道题目难度不低，谢谢。

---

## 作者：ljk_Elaina (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;

int read() {
	int xx=0,ww=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') ww=-ww;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		xx=10*xx+ch-48;
		ch=getchar();
	}
	return xx*ww;
}

int n,m,tmp;
char ch,mp[510][510];
int sx,sy,ex,ey;
bool vis[510][510];
bool flag;
int dx[]= {0,1,-1,0},dy[]= {1,0,0,-1};

bool check(int x,int y) {
	if(x==ex&&y==ey) return true;
	if(x>n||y>m||x<1||y<1||vis[x][y]) return false;
	if(mp[x][y]=='X') return false;
	return true;
}

void dfs(int x,int y) {
	if(flag) return ;
	vis[x][y]=true;
	if(x==ex&&y==ey) {
		flag=true;
		puts("YES");
		exit(0);
	}
	for(int i=0; i<4; i++) {
		int xx=x+dx[i];
		int yy=y+dy[i];
		if(check(xx,yy)) dfs(xx,yy);
		if(xx==ex&&yy==ey) {
			flag=true;
			puts("YES");
			exit(0);
		}
	}
}

int main() {
	memset(vis,false,sizeof(vis));
	n=read();
	m=read();
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			ch=getchar();
			mp[i][j]=ch;
		}
		getchar();
	}
	sx=read();
	sy=read();
	ex=read();
	ey=read();
	for(int i=0; i<4; i++) {
		int X=ex+dx[i];
		int Y=ey+dy[i];
		if(check(X,Y)) tmp++;
		if(X==sx&&Y==sy) tmp++;
	}
	if(sx==ex&&sy==ey) {
		if(tmp>0) puts("YES");
		else puts("NO");
		return 0;
	} else if(mp[ex][ey]=='.') {
		if(tmp<2) {
			puts("NO");
			return 0;
		}
	} else if(mp[ex][ey]=='X') {
		if(tmp<1) {
			puts("NO");
			return 0;
		}
	}
	flag=false;
	for(int i=0; i<4; i++) {
		int X=sx+dx[i];
		int Y=sy+dy[i];
		if(check(X,Y)) dfs(X,Y);
	}
	if(!flag) puts("NO");
	return 0;
}
```

一道$DFS$爆搜题。

如果终点是$"."$ 看有无两个通它的点。

如果终点是$"X"$ 看有无一个通它的点。

起点也算一个点！！！

如果可以，$DFS$

不行，输出$NO$。

$DFS$可以，输出$YES$

否则，$NO$

---

## 作者：aRenBigFather (赞：0)

这是简单的dfs,可以看下dfs的写法,还是比较经典
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;
int n,m;
char G[maxn][maxn];
int vis[maxn][maxn];
int dir[4][2] = {{0,-1},{0,1},{1,0},{-1,0}};
int sx,sy,ex,ey;
inline bool inG(int x,int y){
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
bool dfs(int nowx,int nowy){
	//cout << "vis:" << nowx << " " << nowy << endl; 
	for(int i=0;i<4;i++){
		int tx = nowx + dir[i][0];
		int ty = nowy + dir[i][1];
		if(!inG(tx,ty)) continue;
		if(vis[tx][ty] == 1){
			//如果破裂处
			if(tx == ex && ty == ey) return true;
			else continue; 
		}else{
			vis[tx][ty] = 1;
			if(dfs(tx,ty)) return true;
			//vis[tx][ty] = 0;
		}
	}
	return false;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin >> G[i][j];
			if(G[i][j] == 'X') vis[i][j] = 1;
		}
	}
	cin >> sx >> sy >> ex >> ey;
	if(dfs(sx,sy)) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
```

---

## 作者：CHENRUIJIE (赞：0)

算法：dfs                                        
这是一道很好的dfs题目，思路很简单：即把所有的点给dfs一遍，再是否能到达终点，然后再做处理。             
话不多说，附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
bool used[N][N];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int n,m,a1,a2,b1,b2,use;
char c[N][N];
inline bool ok(int x2,int y2){return (x2>=0 && y2>=0 && x2<n && y2<m);}//判断是否在表格内 
inline void dfs(int x,int y)//dfs看是否能从起点到这个点 
{
	used[x][y]=true;
	for(int i=0;i<4;i++)
	{
		int x2=x+dx[i];
		int y2=y+dy[i];
		if(ok(x2,y2)&&c[x2][y2]=='.'&&!used[x2][y2])dfs(x2,y2);
	}
}
inline bool check()//判断是否能到达终点并且掉进去 
{
	int res=0;
	for(int i=0;i<4;i++)
	{
		int x2=a2+dx[i];
		int y2=b2+dy[i];
		if(ok(x2,y2)&&used[x2][y2])res++;
	}
	return res>=2||(res>=1&&c[a2][b2]=='X');
}
int main()//主函数，输入输出
{
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>c[i];
	cin>>a1>>b1>>a2>>b2;
	a1--,b1--,a2--,b2--;
	dfs(a1,b1);
	bool judge=check();
	if(judge)
		cout<<"YES\n";
	else
		cout<<"NO\n";
	return 0;
} 
```

---

## 作者：Anby_ (赞：0)

简单搜索题。  
按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF540C)。
### 题目大意
简化一下问题。  
给你一个图，$X$ 代表不能走，除终点外的每一个点只能经过一次。问是否存在一条路径，使得这条路径从起始点出发，两次经过终点。
### 思路
我们只需判断一下经过终点时，终点是否为 $X$，否则每一次经过一个点就将它改为 $X$。   
由于不需要回溯，所以可以使用 `BFS` 实现。

### AC code
```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=500+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int n,m,sx,sy,ex,ey,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
char g[N][N];
void bfs(int x,int y){
	queue<pii> q;
	q.push({x,y});
	while(!q.empty()){
		pii t=q.front(); q.pop();
		for(int i=0;i<4;i++){
			int nx=t.x+dx[i],ny=t.y+dy[i];
			if(nx<1||nx>n||ny<1||ny>m) continue;
			if(nx==ex&&ny==ey&&g[nx][ny]=='X'){
				cout<<"YES";
				exit(0);
			}
			if(g[nx][ny]=='X') continue;
			q.push({nx,ny});
			g[nx][ny]='X';
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>g[i][j];
	cin>>sx>>sy>>ex>>ey;
	bfs(sx,sy);
	cout<<"NO";
	return 0;
}
```

---

