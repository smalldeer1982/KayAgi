# [USACO06JAN] The Grove S

## 题目描述

The pasture contains a small, contiguous grove of trees that has no 'holes' in the middle of the it.  Bessie wonders: how far is it to walk around that grove and get back to my starting position? She's just sure there is a way to do it by going from her start location to successive locations by walking horizontally, vertically, or diagonally and counting each move as a single step. Just looking at it, she doesn't think you could pass 'through' the grove on a tricky diagonal. Your job is to calculate the minimum number of steps she must take.


Happily, Bessie lives on a simple world where the pasture is represented by a grid with R rows and C columns (1 <= R <= 50, 1 <= C <= 50). Here's a typical example where '.' is pasture (which Bessie may traverse), 'X' is the grove of trees, '\*' represents Bessie's start and end position, and '+' marks one shortest path she can walk to circumnavigate the grove (i.e., the answer):

```cpp
...+...
..+X+..
.+XXX+.
..+XXX+
..+X..+
...+++*
```
The path shown is not the only possible shortest path; Bessie might have taken a diagonal step from her start position and achieved a similar length solution. Bessie is happy that she's starting 'outside' the grove instead of in a sort of 'harbor' that could complicate finding the best path.

牧场里有树林，林子里没有坑，贝茜很想知道，最少几步能绕树林走一圈，最后回到起点.她能上下左右走，也能走对角线格子.

牧场被分成 $R$ 行 $C$ 列 $(1\leq R\leq 50,\ 1\leq C\leq 50)$ 。下面是一张样例的地图，其中 `.` 表示贝茜可以走的空地， `X` 表示树林，表示起点.而贝茜走的最近的路已经特别地用 `+` 表示 出来.

题目**保证存在最短路径**，且森林形成一个联通块。

## 样例 #1

### 输入

```
6 7
.......
...X...
..XXX..
...XXX.
...X...
...*...```

### 输出

```
11```

# 题解

## 作者：AutumnKite (赞：18)

#为什么每人发题解？#

##来发Pascal##

当然这是BFS的题。但是怎么BFS呢？我们要绕这个树林走一圈，而裸的BFS实现不了。怎么办？

都说了只是**裸的**BFS过不了而已。现在来讲正解：

我们随便挑一棵树，在它的右边往下建一堵“墙”。比如样例，如下图所示：

 ![](https://cdn.luogu.com.cn/upload/pic/7635.png) 

棕色的表示选的那棵树，在他右边往下面建一堵墙。

建了这堵墙以后，BFS时我们就强制让它不穿过这堵墙。

我们在BFS时，用a[i,j]表示从起点出发（不穿过墙）的最短路径（最少步数）。

比如样例（墙就建在那个地方），a数组的值应该是：

```cpp
  8  7  6  5  5  5  5
  8  7  6 -1  4  4  4
  8  7 -1 -1 -1  3  3
  8  8  8 -1 -1 -1  2
  9  9  9 -1  2  1  1
 10 10 10  3  2  1  0
```
最后我们再把墙拆掉，两边能连起来的最小的和就是答案。具体见程序

献上我那丑陋的代码：

```cpp
uses math;
const //坐标增量，八个方向
  dx:array[1..8]of -1..1 = (-1,0,1,0,-1,-1,1,1);
  dy:array[1..8]of -1..1 = (0,-1,0,1,-1,1,-1,1);
var
  n,m,i,j,sx,sy,zx,zy,h,t,ans:longint; //sx,sy是起点，zx,zy是“墙”的位置
  b:array[0..51,0..51]of boolean;
  a:array[0..51,0..51]of longint;
  q:array[0..10001,1..2]of longint;
  c:char;
procedure bfs(x,y:longint);
var
  k,i,j:longint;
begin
  h:=0; t:=1; q[t,1]:=x; q[t,2]:=y; b[x,y]:=false; a[x,y]:=0;
  while h<t do 
    begin
      inc(h); x:=q[h,1]; y:=q[h,2];
      if (x>=zx) and (y=zy) then continue; //如果在墙相邻的左边，这个值就不应该扩展
      for k:=1 to 8 do 
        begin
          i:=x+dx[k]; j:=y+dy[k];
          if (i>0) and (i<=n) and (j>0) and (j<=m) and b[i,j] then 
            begin
              if (i>=zx) and (j=zy) and (dy[k]=-1) then continue; //墙相邻的右边其实不能过来
              a[i,j]:=a[x,y]+1; b[i,j]:=false;
              inc(t); q[t,1]:=i; q[t,2]:=j;
            end;
        end;
    end;
end;
begin
  randomize;
  readln(n,m);
  for i:=0 to n+1 do 
    for j:=0 to m+1 do 
      a[i,j]:=-1; //全部置为-1，处理边界问题和树林
  for i:=1 to n do 
    begin
      for j:=1 to m do 
        begin
          read(c);
          if c='*' then begin sx:=i; sy:=j; end;
          if c='X' then b[i,j]:=false else b[i,j]:=true;
        end;
      readln;
    end;
  repeat zx:=random(n)+1; zy:=random(m)+1; until not b[zx,zy];
  bfs(sx,sy);
  writeln(zx,' ',zy);
  for i:=1 to n do 
    begin
      for j:=1 to m do write(a[i,j]:3);
      writeln;
    end;
  ans:=maxlongint shr 1;
  for i:=zx+1 to n do 
    if a[i,zy]>=0 then //不是树林
      for j:=-1 to 1 do 
        if a[i+j,zy+1]>=0 then ans:=min(ans,a[i,zy]+a[i+j,zy+1]); //不是树林也没有超出（超出自动是-1，上面说过了），比较出较小值
  write(ans+1); //起点本身加上去
end.

```

---

## 作者：一颗赛艇 (赞：12)

**虚拟射线法**：

虚拟出一条射线，然后搜索图中看其是否穿过，穿过奇数次为在多边形内，偶数次为多边形外，自己可以画图看看效果，另外判断是否穿过的函数容易写错，因为状态很容易覆盖


\_ps:这种做法推荐，是一般解法，适合各种变形，而且代码简单。\_


代码：

  
  
```cpp
#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <cmath>  
#include <string>  
#include <map>  
#include <stack>  
#include <vector>  
#include <set>  
#include <queue>  
//#pragma comment (linker,"/STACK:102400000,102400000")  
#define maxn 105  
#define mod 1000000007  
#define INF 0x3f3f3f3f  
using namespace std;  
typedef long long ll;  
int n,m,ans,flag;  
int sx,sy,gx,gy,nx,ny,tx,ty;  
int dx[]= {-1,1,0,0,-1,-1,1,1};  
int dy[]= {0,0,-1,1,-1,1,-1,1};  
int dp[maxn][maxn][2];  
char mp[maxn][maxn];  
char s[maxn];  
struct Node  
{  
    int x,y,k; // k-是否包围  
} cur,now;  
bool issur()  // 向下穿过包围 向上解包围  
{  
    if(tx==gx&ty<gy)  
    {  
        if(nx<gx) return true;  
    }  
    else if(nx==gx&&ny<gy)  
    {  
        if(tx<gx) return true ;  
    }  
    return false;  
}  
void bfs()  
{  
    int i,j,t,k,nk;  
    queue<Node>q;  
    memset(dp,-1,sizeof(dp));  
    cur.x=sx;  
    cur.y=sy;  
    cur.k=0;  
    dp[sx][sy][0]=0;  
    q.push(cur);  
    while(!q.empty())  
    {  
        now=q.front();  
        q.pop();  
        nx=now.x;  
        ny=now.y;  
        nk=now.k;  
        for(i=0; i<8; i++)  
        {  
            tx=nx+dx[i];  
            ty=ny+dy[i];  
            k=nk;  
            if(tx<1||tx>n||ty<1||ty>m||mp[tx][ty]=='X') continue ;  
            if(issur()) k^=1;  
            if(dp[tx][ty][k]!=-1&&dp[tx][ty][k]<=dp[nx][ny][nk]+1) continue ;  
            cur.x=tx;  
            cur.y=ty;  
            cur.k=k;  
            dp[tx][ty][k]=dp[nx][ny][nk]+1;  
            q.push(cur);  
        }  
    }  
    ans=dp[sx][sy][1];  
}  
int main()  
{  
    int i,j,t;  
    while(~scanf("%d%d",&n,&m))  
    {  
        flag=0;  
        for(i=1; i<=n; i++)  
        {  
            scanf("%s",s);  
            for(j=1; j<=m; j++)  
            {  
                mp[i][j]=s[j-1];  
                if(mp[i][j]=='*') sx=i,sy=j;  
                if(!flag&&mp[i][j]=='X') flag=1,gx=i,gy=j;  
            }  
        }  
        bfs();  
        printf("%d\n",ans);  
    }  
    return 0;  
}
```

---

## 作者：Limit (赞：6)

~~坎坷的做题旅程~~
先用bfs码了一个计算绕森林最小路程
找到最上点，最右点，最下点，最左点。利用凸包特性去写。
```
const z:array[1..8,1..2]of -1..1=((0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1),(-1,0),(-1,1));
var i,j,k:longint;
    m,n:longint;
    x,y:array[0..10000]of longint;
    fax,fay:array[0..100,0..100]of longint;
    a,b:array[0..100,0..100]of boolean;
    fx,fy,h,t:longint;
    x1,y1:longint;
    ch:char;
    limx,limy:array[1..4]of longint;
    can:array[1..4,1..8]of boolean;
    now:array[0..10000]of longint;
    ans:longint;
function pd(x,y,x1,y1:longint):boolean;
var i:longint;
begin
  for i:=1 to 8 do
  if i mod 2=1 then
  if (x+z[i,1]=x1) and (y+z[i,2]=y1) then exit(true);
  exit(false);
end; 
begin
  for i:=1 to 3 do//每种可以走的方向
  can[1,i]:=true;
  for i:=3 to 5 do
  can[2,i]:=true;
  for i:=5 to 7 do
  can[3,i]:=true;
  for i:=7 to 8 do
  can[4,i]:=true;
  can[4,1]:=true;
  readln(m,n);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='X' then
      begin
        a[i][j]:=true;
        if limx[1]=0 then
        begin
          limx[1]:=i;
          limy[1]:=j;
        end;
        limx[3]:=i;
        limy[3]:=j;
        if(j>limy[2])or(limx[2]=0)
        then
        begin
          limx[2]:=i;
          limy[2]:=j;
        end;
        if(j<limy[4])or(limx[4]=0)
        then
        begin
          limx[4]:=i;
          limy[4]:=j;
        end;    
      end
      else b[i,j]:=true;
      if ch='*' then
      begin
        fx:=i;
        fy:=j;
      end;
    end;
    readln;
  end;
  h:=1;
  t:=1;
  x[1]:=limx[1]-1;
  y[1]:=limy[1];
  now[1]:=1;
  repeat
    if (now[t]=4) and (x[t]+1=limx[1]) and (y[t]=limy[1]) then//到终点
    begin
      break;
    end;
    if (now[t]=1) and (x[t]=limx[2]) and (y[t]-1=limy[2]) then//改变
    begin
      now[t]:=2;
    end;
    if (now[t]=2) and (x[t]-1=limx[3]) and (y[t]=limy[3]) then//改变
    begin
      now[t]:=3;
    end;
    if (now[t]=3) and (x[t]=limx[4]) and (y[t]+1=limy[4]) then//改变
    begin
      now[t]:=4;
    end;
    for i:=1 to 8 do//八个方向查找
    if can[now[t],i] then
    if b[x[t]+z[i,1],y[t]+z[i,2]] then
    begin
      inc(h);
      b[x[t]+z[i,1],y[t]+z[i,2]]:=false;
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      fax[x[h],y[h]]:=x[t];//记录father
      fay[x[h],y[h]]:=y[t];
      now[h]:=now[t];
    end;
    inc(t);
  until h<t;
  for i:=1 to m do
  for j:=1 to n do
  a[i,j]:=true;
  x1:=x[t];
  y1:=y[t];
  x[0]:=x1;
  y[0]:=y1;
  x1:=fax[x[0],y[0]];
  y1:=fay[x[0],y[0]];
  while (x1<>limx[1]-1)or(y1<>limy[1]) do//倒退找路径
  begin
    a[x1,y1]:=false;
    x[0]:=x1;
    y[0]:=y1;
    x1:=fax[x[0],y[0]];
    y1:=fay[x[0],y[0]];
    inc(ans);
  end;
  a[limx[1]-1,limy[1]]:=false;
  h:=1;
  t:=1;
  x[1]:=fx;
  y[1]:=fy;
  now[1]:=0;
  for i:=1 to m do
  for j:=1 to n do
  b[i,j]:=true;
  b[fx,fy]:=false;
  repeat
    if not a[x[t],y[t]] then//找到解
    begin
      write(ans+now[t]+2);//凑
      exit;//30分
    end;
    for i:=1 to 8 do
    if b[x[t]+z[i,1],y[t]+z[i,2]] then
    begin
      inc(h);
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      b[x[h],y[h]]:=false;
      now[h]:=now[t]+1;
    end;
    inc(t);
  until t>h;
end.
```
又改进了一下

```
const z:array[1..8,1..2]of -1..1=((0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1),(-1,0),(-1,1));
var i,j,k:longint;
    m,n:longint;
    x,y:array[0..10000]of longint;
    fax,fay:array[0..100,0..100]of longint;
    min:array[0..100,0..100]of longint;
    a,b,c,d:array[0..100,0..100]of boolean;
    fx,fy,h,t:longint;
    x1,y1:longint;
    ch:char;
    limx,limy:longint;
    can:array[1..8]of boolean;
    now:array[0..10000]of longint;
    ans:longint;
    sum:longint;
    x2,y2:longint;
procedure dfs(x,y:longint);
var i:longint;
begin
  if not c[x,y] then exit;
  c[x,y]:=false;
  a[x,y]:=true;
  for i:=1 to 8 do
  if min[x+z[i,1],y+z[i,2]]=min[x,y]-1 then
  dfs(x+z[i,1],y+z[i,2]);
end;
begin
  readln(m,n);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='*' then
      begin
        fx:=i;
        fy:=j;
      end;
      if ch='X' then
      begin
        if limx=0 then
        begin
          limx:=i-1;
          limy:=j;
        end;
      end
      else b[i,j]:=true;
    end;
    readln;
  end;
  c:=b;
  d:=b;
  x[1]:=limx;
  y[1]:=limy;
  sum:=0;
  x2:=limx;
  y2:=limy;
  while x2>0 do
  begin
    x2:=x2-1;
    inc(sum);
    min[x2,y2]:=sum;
    b[x2,y2]:=false;
  end;
  h:=1;
  t:=1;
  now[1]:=0;
  can[1]:=true;
  can[2]:=true;
  can[8]:=true;
  for i:=1 to 8 do
  if can[i] then
  if b[x[t]+z[i,1],y[t]+z[i,2]] then
  begin
    b[x[t]+z[i,1],y[t]+z[i,2]]:=false;
    inc(h);
    x[h]:=x[t]+z[i,1];
    y[h]:=y[t]+z[i,2];
    min[x[h],y[h]]:=now[t]+1;
    now[h]:=now[t]+1;
    fax[x[h],y[h]]:=limx;
    fay[x[h],y[h]]:=limy;
  end;
  inc(t);
  repeat
    if (x[t]=limx) and (y[t]=limy) then
    break;
    for i:=1 to 8 do
    if b[x[t]+z[i,1],y[t]+z[i,2]] and
    (((x[t]+z[i,1])<>fax[x[t],y[t]])
    or ((y[t]+z[i,2])<>fay[x[t],y[t]])) then
    begin
      inc(h);
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      now[h]:=now[t]+1;
      min[x[h],y[h]]:=now[h];
      b[x[h],y[h]]:=false;
    end;
    inc(t);
  until t>h;
  dfs(limx,limy);
  x[1]:=fx;
  y[1]:=fy;
  t:=1;
  h:=1;
  now[1]:=0;
  repeat
    if a[x[t],y[t]] then
    begin
      write(now[t]+min[limx,limy]);
      exit;
    end;
    for i:=1 to 8 do
    if d[x[t]+z[i,1],y[t]+z[i,2]] then
    begin
      inc(h);
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      now[h]:=now[t]+1;
      d[x[h],y[h]]:=false;
    end;
    inc(t);
  until h<t;
end.
因为路径不止一条，这个可以把所有都找出来
```
~~这时才发现题目看错了~~QAQ
不过，还好，很快就AC了

```
const z:array[1..8,1..2]of -1..1=((0,1),(1,1),(1,0),(1,-1),(0,-1),(-1,-1),(-1,0),(-1,1));
var i,j,k:longint;
    m,n:longint;
    x,y:array[0..10000]of longint;
    fax,fay:array[0..100,0..100]of longint;
    min:array[0..100,0..100]of longint;
    a,b,c,d:array[0..100,0..100]of boolean;
    fx,fy,h,t:longint;
    x1,y1:longint;
    ch:char;
    limx,limy:longint;
    can:array[1..8]of boolean;
    now:array[0..10000]of longint;
    ans:longint;
    sum:longint;
    x2,y2:longint;//很多变量没用，只是懒得删，顺便见证一下坎坷的做题旅途
function small(m,n:longint):longint;//min用掉了
begin
  if m>n then exit(n) else exit(m); 
end;
begin
  readln(m,n);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='*' then//起点
      begin
        fx:=i;
        fy:=j;
      end;
      if ch='X' then
      begin
        if limx=0 then
        begin
          limx:=i-1;
          limy:=j;
        end;
        min[i,j]:=9999999;//永远也到不了
      end
      else b[i,j]:=true;
    end;
    readln;
  end;
  c:=b;
  d:=b;
  x2:=limx;
  y2:=limy;
  sum:=0;
  b[limx,limy]:=false;
  while x2>0 do//把环打破,一边的加另一边便是最优解
  begin
    x2:=x2-1;
    inc(sum);
    min[x2,y2]:=sum;
    b[x2,y2]:=false;
  end;
  h:=1;//队列
  t:=1;
  now[1]:=0;
  x[1]:=fx;
  y[1]:=fy;
  repeat
    for i:=1 to 8 do
    if b[x[t]+z[i,1],y[t]+z[i,2]] then
    begin
      inc(h);
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      now[h]:=now[t]+1;
      min[x[h],y[h]]:=now[h];
      b[x[h],y[h]]:=false;
    end;
    inc(t);
  until t>h;
  write(small(min[limx,limy-1],min[limx+1,limy-1])+small(min[limx,limy+1]{左边最优解},min[limx+1,limy+1]){同理，右边最优解}+2{其中漏算的两个点});//最优解必然在这些位置
end.
```
~~呀AC了~~
做题之路一路坎坷


---

## 作者：Big_Dinosaur (赞：3)

模拟赛试题，过了，~~反而黄题没过~~。

### 做法
考虑 BFS。首先，找到树林的最顶端、最左端、最下端和最右端，记录为 $x1$、$x2$、$x3$ 和 $x4$。起点位于 $x5$。

考虑如何使路最短，通过计算，发现答案在 $x5\to x4\to x3\to x2\to x1\to x5$、$x5\to x3\to x2\to x1\to x4\to x5$、$x5\to x2\to x1\to x4\to x3\to x5$ 和 $x5\to x1\to x4\to x3\to x2\to x5$ 四条路径之间。

用 BFS 计算 $x1\to x2$、$x2\to x3$、$x3\to x4$、$x4\to x1$、$x5\to x1$、$x5\to x2$、$x5\to x3$、$x5\to x4$ 的最短路径，再计算上述四条路径长度，取最小值。

### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
namespace IO {
	inline int r() {
		char Z=getchar();
		int Y=1,T=0;
		while(Z<'0'||Z>'9') {
			if(Z=='-')Y=-1;
			Z=getchar();
		}
		while(Z>='0'&&Z<='9') {
			T=(T<<3)+(T<<1)+(Z^48);
			Z=getchar();
		}
		return T*Y;
	}
	inline void PO(int F) {
		if(F==0)return;
		if(F<0) {putchar('-');F=-F;}
		PO(F/10);
		putchar(48+F%10);
	}
	inline void ww(int L) {if(L==0)putchar('0');else PO(L);putchar(' ');}
	inline void wln(int L) {if(L==0)putchar('0');else PO(L);putchar('\n');}
	inline void w(int L) {if(L==0)putchar('0');else PO(L);}
}
using namespace IO;
namespace bd {
	string s[99];
	int vis[99][99],xx[9]= {1,0,-1,0,1,1,-1,-1},yy[9]= {0,1,0,-1,-1,1,-1,1};
	int n,m,a1,b1,b2,a2,a3,b3,a4,b4,a5,b5;
	inline int bfs(int X,int Y,int a,int b) {
		memset(vis,0,sizeof(vis));
		queue<int>x,y,z;
		vis[X][Y]=1;
		x.push(X);y.push(Y);z.push(0);
		while(!y.empty()) {
			int o=x.front(),p=y.front(),q=z.front();
			x.pop(),y.pop(),z.pop();
			if(o==a&&p==b)return q;
			for(int i=0; i<8; ++i) {
				int oo=o+xx[i],pp=p+yy[i],qq=q+1;
				if(oo>=n||pp>=m||oo<0||pp<0)continue;
				if(vis[oo][pp]||s[oo][pp]=='X')continue;
				vis[oo][pp]=1;
				x.push(oo);y.push(pp);z.push(qq);
			}
		}
		return 114514;
	}
	inline void _() {
		n=r(),m=r();
		a1=b1=a2=b2=114514;
		a3=b3=a4=b4=0;
		for(int i=0; i<n; ++i) {
			cin>>s[i];
			for(int j=0; j<m; ++j)if(s[i][j]=='X') {
					if(i<a1)a1=i,b1=j;
					if(j<b2)a2=i,b2=j;
					if(i>a3)a3=i,b3=j;
					if(j>b4)a4=i,b4=j;
				} else if(s[i][j]=='*')a5=i,b5=j;
		}
		--a1,--b2;
		++a3;
		++b4;
		int x1=bfs(a1,b1,a2,b2),x2=bfs(a2,b2,a3,b3),x3=bfs(a3,b3,a4,b4),x4=bfs(a1,b1,a4,b4);
		int x5=bfs(a1,b1,a5,b5),x6=bfs(a2,b2,a5,b5),x7=bfs(a3,b3,a5,b5),x8=bfs(a5,b5,a4,b4);
		wln(min(min(min(x5+x6+x2+x3+x4,x6+x7+x1+x3+x4),x7+x8+x1+x2+x4),x5+x8+x1+x2+x3));
	}
}
signed main() {
	bd::_();
}
```

---

## 作者：QinYulang (赞：1)

# 题意
其实就是求从 $*$ 开始绕 $X$ 走一圈的最短路。
# 思路
首先先引出一个判断一个点是否在多边形内的算法：射线法。

比如说，我就随便涂了一个多边形和一个点，请告诉我它在多边形的内部还是外部 ~~（别告诉我用肉眼观察……）。~~
![](https://cdn.luogu.com.cn/upload/image_hosting/pe4l3i49.png)

引出条射线不难发现其与多边形边界的交点个数为2个，且在多边形的外部。
![](https://cdn.luogu.com.cn/upload/image_hosting/b9gvo87p.png)

多试几个不难猜出结论：从这个点做一条射线，计算它跟多边形边界的交点个数，如果交点个数为奇数，那么点在多边形内部，否则点在多边形外。原理可以看[这个](https://blog.csdn.net/qq_27161673/article/details/52973866)。

由此就诞生了我们的正解。

# 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <climits>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cmath>

#define LOCAL
// #define int long long
namespace ly{
    namespace IO{
        #ifndef LOCAL
            constexpr auto maxn = 1 << 20;
            char in[maxn], out[maxn], *p1 = in, *p2 = in, *p3 = out;
            #define getchar() (p1 == p2 && (p2 = (p1 = in) + fread(in, 1, maxn, stdin), p1 == p2) ? EOF : *p1++)
            #define flush() (fwrite(out, 1, p3 - out, stdout))
            #define putchar(x) (p3 == out + maxn && (flush(), p3 = out), *p3++ = (x))
            class Flush{public: ~Flush(){flush();}}_;
        #endif
        namespace usr{
            template <typename type>
            inline type read(type &x){x = 0; bool flag(0); char ch = getchar(); while(!isdigit(ch)) flag ^= ch == '-', ch = getchar(); while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); return flag ? x = -x : x;}
            template <typename type>
            inline void write(type x){x < 0 ? x = -x, putchar('-') : 0; static short Stack[50], top(0); do Stack[++top] = x % 10, x /= 10; while(x); while(top) putchar(Stack[top--] | 48);}
            inline char read(char &x){do x = getchar(); while(isspace(x)); return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch; read(ch); do *(x++) = ch; while(!isspace(ch = getchar()) && ~ch);}
            template <typename type> inline void write(type *x){while(*x) putchar(*(x++));}
            inline void read(std::string &x){static char ch; read(ch), x.clear(); do x += ch; while(!isspace(ch = getchar()) && ~ch);}
            inline void write(const std::string &x){for(int i = 0, len = x.length(); i < len; ++i)putchar(x[i]);}
            template <typename type, typename...T> inline void read(type &x, T&...y){read(x), read(y...);}
            template <typename type, typename...T>
            inline void write(const type &x, const T&...y){write(x), putchar(' '), write(y...), sizeof...(y) ^ 1 ? 0 : putchar('\n');}
            template <typename type>
            inline void put(const type &x, bool flag = 0){write(x), flag ? putchar('\n') : putchar(' ');}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    } using namespace IO::usr;
} using namespace ly::IO::usr;

constexpr int mx[8] = {-1, 1, 0, 0, -1, -1, 1, 1}, my[8] = {0, 0, -1, 1, -1, 1, -1, 1};
int n, m;
char c[105][105];
struct Node{
    int x, y, k;
} cur, now;
std::queue <Node> q;
int dx, dy, nx, ny, bx, by, sx, sy;
bool sur(){
    if(dx == bx && dy < by) {if(nx < bx) return 1;}
    else if(nx == bx && ny < by) {if(dx < bx) return 1;}
    return 0;
}
int dp[105][105][2];
int nk, k;
void bfs(){
    memset(dp, -1, sizeof dp);
    cur = {sx, sy, k};
    q.push(cur);
    dp[sx][sy][0] = 0;
    while(!q.empty()){
        now = q.front();
        q.pop();
        nx = now.x, ny = now.y, nk = now.k;
        for(int i = 0; i < 8; ++i){
            dx = nx + mx[i], dy = ny + my[i], k = nk;
            if(dx < 1 || dx > n || dy < 1 || dy > m || c[dx][dy] == 'X') continue;
            if(sur()) k ^= 1;
            if(dp[dx][dy][k] != -1 && dp[dx][dy][k] <= dp[nx][ny][nk] + 1) continue;
            cur = {dx, dy, k};
            dp[dx][dy][k] = dp[nx][ny][nk] + 1;
            q.push(cur);
        }
    }
}

int main(){
    bool flag = 0;
    read(n, m);
    for(int i = 1; i <= n; ++i){
        std::cin >> (c[i] + 1);
        for(int j = 1; j <= m; ++j){
            if(!flag && c[i][j] == 'X') flag = 1, bx = i, by = j;
            if(c[i][j] == '*') sx = i, sy = j;
        }
    }
    bfs();
    put(dp[sx][sy][1], 1);
    return 0;
}
```

---

## 作者：Tracy_Loght (赞：1)

**注意**：本篇是 BFS 题解。

直入主题。

## 思路：

**找中转点（将答案分成多份相加）：**


---


如此：

```cpp
9 8
.........
..XX.....
...X.....
..XXX....
..XXXX...
...X.X...
...X..*..
.........
```

先进行压缩，指去除一定没用的一些行和列，使得最近的树离删除的点也至少有一个可以走的地方（`#` 表示删除部分）：

```cpp
#......##
#.XX...##
#..X...##
#.XXX..##
#.XXXX.##
#..X.X.##
#..X..*##
#......##
```

此时离删除的点或边界距离为一的点都是中转点（中转点表示为 `@`）：

```cpp
#.@@...##
#@XX...##
#..X...##
#@XXX..##
#@XXXX@##
#..X.X@##
#..X..*##
#..@...##
```

---


**移动并封装：**


等等。

首先注意到这些中转点是可以经过的且在删除无用的行列时一定会走到的（仔细读一下）。

为什么经过时是最优的呢：

```cpp
......           ...... 
.XXM..           .XXM..
..X|..           ..X.>.
..X*..           ..X*..
```

如图，左图与右图同理是最优的，但是一个是直着向上，一个是移到另一列再回去。

体会一下。

懂了没，在起点与目标一定时，虽然图二的移动更有价值（同时移动了行列，而图一只移动了行），但是不优，虽然在结果与次数上确实最少，但是会多占用一个列。

（终点与起点不在同一行列时，斜着走一定是好的）。

可能你觉得这个对“**这些中转点是可以经过的且在删除无用的行列时一定会走到的**”用处不大，但确实。

再抽象来看：

![](https://cdn.luogu.com.cn/upload/image_hosting/m08ljn5c.png)

对于两个相邻的中转点，有且只有一条最优路径（其余的都是延申状态，及上文的左右图）。

那么答案不就是所有中转点依次相连然后计算移动次数的和吗（起点也算中转点）。

同理，对于其它别的题解所讲，找到一个一定被经过后最优的点，并计算起点到这个点，然后在将这个点封掉（删除无用的行列后），再计算这个点另一种回去的步数，最终相加。

最终找到的中转点至少有两个，够用了。

## 代码：

删除无用行列和找中转点：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mx=51;
int n,m,jl;
int nl,nr,ml,mr;
char o[Mx][Mx];
struct{int a,b;}k[Mx*Mx];
void pit(){
	for(int i=nl;i<=nr;i++){
		for(int j=ml;j<=mr;j++)
			cout<<o[i][j];
		cout<<"\n";
	}
}
void actop(){
	nl=1;nr=n;
	ml=1;mr=m;
	for(int i=ml;i<=mr;i++){int f=0;
		for(int j=nl;j<=nr;j++) if(o[j][i]=='X') {f=1;break;}
		if(f==1) {ml=i-1; break;} }
	for(int i=mr;i>=ml;i--){int f=0;for(int j=nl;j<=nr;j++) if(o[j][i]=='X') {f=1;break;}if(f==1) {mr=i+1; break;}}
	for(int i=nl;i<=nr;i++){int f=0;for(int j=ml;j<=mr;j++) if(o[i][j]=='X') {f=1;break;}if(f==1) {nl=i-1; break;}}
	for(int i=nr;i>=nl;i--){int f=0;for(int j=ml;j<=mr;j++) if(o[i][j]=='X') {f=1;break;}if(f==1) {nr=i+1; break;}}
}
void ap(int l,int r){jl++;k[jl].a=l;k[jl].b=r;}
int main(){
	ios::sync_with_stdio(0);
	std::cin.tie(0); 
	std::cout.tie(0); 
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>o[i][j];
	actop();
	for(int i=nl;i<=nr;i++){
		for(int j=ml;j<=mr;j++){
			if(i==nl||i==nr||j==ml||j==mr){
				if(o[i+1][j]=='X'||o[i-1][j]=='X') ap(i,j);
				else if(o[i][j-1]=='X'||o[i][j+1]=='X') ap(i,j);
			}
		}
	}
	return 0;
}
```

---

## 作者：Tang_chao (赞：1)

## P2864 [USACO06JAN] The Grove S 题解
题目中有这样一句话：
> 题目保证存在最短路径，且森林形成一个连通块。

这是一个挺关键的性质。

不难发现我们要找一个能包住这个连通块的环。  

考虑找到森林的最上、下、左、右的位置，再枚举起点插在哪个位置，绕一圈求距离最小值即可。  

比如下面一个例子：
```cpp
.U...
LX...
.XSXR
.XXX.
.D...
```
四个位置用 $U,D,L,R$ 表示，起点用 $S$ 表示。发现 $S-R-D-L-U-S$ 或 $S-U-L-D-R-S$ 的路径最短。  

实现中要找到所有挨着树林但不是树林的位置，然后在这些位置中找到最边上的四个位置（可能不唯一但没关系）。然后求出这几个点两两之间的距离，我用了广搜。最后绕一圈求距离最小值。

奉上代码，写的~~极其~~奇怪。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 55
int n,m,p,ans = 2e9,stx,sty,up,dn,lf,rt,r[4],x[N * N],y[N * N],dst[6][N][N];
int dx[9] = {0,0,1,-1,1,-1,1,-1},dy[9] = {1,-1,0,0,1,1,-1,-1};
bool vst[N][N];
char mp[N][N];

int STID(int xx,int yy){
	if(xx == x[0] && yy == y[0]) return 0;
	if(xx == x[up] && yy == y[up]) return 1;
	if(xx == x[rt] && yy == y[rt]) return 2;
	if(xx == x[dn] && yy == y[dn]) return 3;
	if(xx == x[lf] && yy == y[lf]) return 4;
}
int DST(int a,int b){ return dst[STID(x[a],y[a])][x[b]][y[b]]; }

int cal(int a,int b,int c,int d,int e){
	return DST(a,b) + DST(b,c) + DST(c,d) + DST(d,e) + DST(e,a);
}
void print(int a){ cout<<x[a]<<" "<<y[a]<<"  "; }


void bfs(int stx,int sty){
	queue<int> qx,qy;
	qx.push(stx); qy.push(sty);
	int stid = STID(stx,sty);
	while(!qx.empty()){
		int x = qx.front(),y = qy.front();
		qx.pop(); qy.pop();
		for(int i = 0;i < 8;i++){
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
			if(dst[stid][nx][ny] || (nx == stx && ny == sty)) continue;
			if(mp[nx][ny] == 'X') continue; 
			dst[stid][nx][ny] = dst[stid][x][y] + 1;
			qx.push(nx); qy.push(ny);
		}
	}
}

void input(){
	cin>>n>>m;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++){
			cin>>mp[i][j];
			if(mp[i][j] == '*') stx = i,sty = j;
		}
}
void findUDLR(){
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++){
			if(mp[i][j] != 'X') continue;
			for(int k = 0;k < 4;k++)
				if(mp[i + dx[k]][j + dy[k]] != 'X')
					x[++p] = i + dx[k],y[p] = j + dy[k];
		}
	x[0] = 0; y[0] = 0; x[p + 1] = n + 1; y[p + 1] = m + 1;
	up = p + 1; dn = 0; lf = p + 1; rt = 0;
	for(int i = 1;i <= p;i++){
		if(x[up] > x[i]) up = i;
		if(x[dn] < x[i]) dn = i;
		if(y[lf] > y[i]) lf = i;
		if(y[rt] < y[i]) rt = i;
	}
}
void findROUTE(){
	x[0] = stx; y[0] = sty;
	bfs(x[up],y[up]); bfs(x[dn],y[dn]); bfs(x[lf],y[lf]); bfs(x[rt],y[rt]);
	bfs(x[0],y[0]);
	ans = min(ans,cal(0,up,rt,dn,lf));
	ans = min(ans,cal(0,lf,up,rt,dn));
	ans = min(ans,cal(0,dn,lf,up,rt));
	ans = min(ans,cal(0,rt,dn,lf,up));
	cout<<ans<<endl;
}
int main(){
	input();
	findUDLR();
	findROUTE();
	return 0;
}
```

---

## 作者：Rain_cyl (赞：1)

首先，我们可以想到，要让路径绕过整个森林，可以找一个特殊点，使路径必须经过这个点。

以样例为例：
```
...O...
...X...
..XXX..
...XXX.
...X...
...*...
```
我们规定路径必须经过 `O`，并且不存在走到这里就原路返回的情况，那么一定能绕过森林。

然而，找到这个 `O` 并不容易，首先你很难不让路径原路返回，也很难保证其最优性。

那么，如果将 `O` 从一个点变为一条线呢？
```
.......
...X___
..XXX..
...XXX.
...X...
...*...
```
如图，在最上方的树的右边画一道线，那么路径绕过树林等价于其穿过了这条线并回到原点。因此，在 bfs 的时候，规定不能越过这条线，计算原点到达每个点的距离 $d[i][j]$,然后枚举线两旁的点对，计算他们的距离之和再加 $1$ 就是总路径长度。加 $1$ 是因为要算上走回原点的那一步。

我在实现中将这条线规定为最靠上，且在此基础上最靠右的树向右发射的一条射线，而实际上任意一条类似的线都能达到相同效果。

时间复杂度 $O(nm)$。
```
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef pair<int,int> PII;
const int N=55,dx[8]={-1,-1,0,1,1,1,0,-1},dy[8]={0,1,1,1,0,-1,-1,-1};

int n,m;
PII p,start;
char g[N][N];
int d[N][N];
bool st[N][N];

bool check(int x1,int y1,int x2,int y2){ //判断从(x1,y1)到(x2,y2)是否越过规定的线
    if(x1>x2) swap(x1,x2),swap(y1,y2);
    if(x1==p.x&&x2==p.x+1&&y1>p.y) return 1;
    return 0;
}

void bfs(){
    queue<PII> q;
    q.push(start);
    memset(d,0x3f,sizeof d);
    d[start.x][start.y]=0,st[start.x][start.y]=1;
    while(q.size()){
        int x=q.front().x,y=q.front().y;
        q.pop();
        for(int i=0; i<8; i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(nx<1||nx>n||ny<1||ny>m) continue;
            if(st[nx][ny]) continue;
            if(check(x,y,nx,ny)) continue;
            if(d[nx][ny]>d[x][y]+1){
                d[nx][ny]=d[x][y]+1;
                st[nx][ny]=1;
                q.push({nx,ny});
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    p={n,1};
    for(int i=1; i<=n; i++){
        scanf("%s",g[i]+1);
        for(int j=1; j<=m; j++){
            if(g[i][j]=='X'){
                st[i][j]=1;
                if(i<p.x) p={i,j};
                else if(i==p.x&&j>p.y) p={i,j};
            }
            else if(g[i][j]=='*') start={i,j};
        }
    }
    
    bfs();
    
    int res=0x3f3f3f3f;
    for(int j=p.y+1; j<=m; j++){
        res=min(res,d[p.x][j]+d[p.x+1][j]);
        res=min(res,d[p.x][j]+d[p.x+1][j-1]); //注意线两旁的点的y可以差1，因为能走对角
        res=min(res,d[p.x][j]+d[p.x+1][j+1]);
    }
    printf("%d\n",res+1);
    return 0;
}
```

---

## 作者：ouyuki (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P2864)

# 题目大意
这道题目~~言简意赅~~，就是要我们求以 $*$ 为起点绕 $X$ 走一圈的最短路。
# 思路分析
下面介绍 建墙法。  
以一个简单的样例为例：  

```cpp
.......
...X...
..XXX..
...XXX.
...X...
......*
```
最后一棵树为原点，向下建墙。

最后一棵树 $X$  的 $X$ 坐标 $+1$ 记为 $ltx$，$Y$ 记为 $lty$。

注：$X$ 坐标需 $+1$，以不与树重合。

如下所示：
```cpp
.......
...X...
..XXX..
...XXX.
...X...
...|..*
```
$|$ 为墙。  
建好墙后，以贝茜为原点，进行 BFS。  
所走的步数如下所示：
```cpp
8  7  6  5  5  5  5
8  7  6  X  4  4  4
8  7  X  X  X  3  3
8  8  8  X  X  X  2
9  9  9  X  2  1  1
10 10 10 |  2  1  0
```
BFS 后，就是统计答案了！  
那么答案记为 $sum$，统计步数的数组为 $ans$。  
$sum=\min(ans_{ltx−1,lty−1},ans_{ltx,lty−1},ans_{ltx+1,lty−1})+\min(ans_{ltx−1,lty+1},ans_{ltx,lty+1},ans_{ltx+1,lty+1})+2$
### tips

1. 墙不能与贝茜重合  
2. BFS 时注意墙与树 一样不能走。   
3. BFS 注意边界。  
4. 统计过的点无需再次访问。  
5. 墙不能与树重合。
## 附上 AC 代码
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
#define ll long long
#define INF 0x7f7f7f7f7f
ll min(ll a, ll b) {//手打min
	return a < b ? a : b;
}
ll r, c; //见题面，r:长 c：宽
char a[100][100]; //地图
ll sx, sy, ltx, lty; //*的坐标，及最后一棵树的坐标
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1}; //8个方向
ll ans[110][110]; //见前文
ll q[100100][3], h, t; //手打BFS队列
int main() {
	cin >> r >> c; //读入
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			cin >> a[i][j];
			if (a[i][j] == '*')sx = i, sy = j; //*坐标
			else if (a[i][j] == 'X')ltx = i + 1, lty = j; //最后一棵树的坐标
		}
	}
	for (int i = 0; i < 110; i++)for (int j = 0; j < 110; j++)ans[i][j] = INF; //ans赋值为最大值
	if (ltx == sx && lty == sy) { //特判，墙不能与*重合
		bool f = 0;
		for (int i = 1; i <= r; i++){
			for (int j = 1; j <= c; j++){
				if (a[i][j] == 'X' && !f) {
					ltx = i;
					lty = j;
					f = 1;
					break;
				}
			}
		}
		for (int i = 1; i <= ltx; i++)a[i][lty] = '|';
	}
	for (int i = ltx; i <= r; i++)a[i][lty] = '|';
	
	ll x, y, s, xx, yy; //BFS开始
	ans[sx][sy] = 0;
	t = 1;
	q[0][0] = sx;
	q[0][1] = sy;
	while (h < t) {
		x = q[h][0], y = q[h][1], s = q[h][2]; //取队首
		for (int i = 0; i < 8; i++) { //8个方向搜
			xx = x + dx[i], yy = y + dy[i]; //替死鬼
			if (ans[xx][yy] != INF)continue; //不重复搜
			if ((xx >= 1 && xx <= r && yy >= 1 && yy <= c) && a[xx][yy] == '.') { //边界及能否走
				ans[xx][yy] = s + 1; //记入答案
				q[t][0] = xx; //入队
				q[t][1] = yy; //入队
				q[t++][2] = s + 1; //入队
			}
		}
		h++; //出队
	} //BFS结束
	
	cout << min(ans[ltx - 1][lty - 1], min(ans[ltx][lty - 1], ans[ltx + 1][lty - 1])) + min(ans[ltx - 1][lty + 1], min(ans[ltx][lty + 1], ans[ltx + 1][lty + 1])) + 2; //输出答案
	return 0;
}
```

---

## 作者：zmza (赞：1)

这个是建墙法。就是建一座墙，然后bfs。就变成了从出发点到墙，再从墙到出发点的问题。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[8]={-1,1,0,0,-1,-1,1,1};
const int dy[8]={0,0,-1,1,-1,1,-1,1};
struct node
{
	int x,y,k;
	node(int a,int b,int c):x(a),y(b),k(c)
	{
	}
	node(){
	}
	friend bool operator <(node a,node b)
	{
		return a.k > b.k;
	}
};
priority_queue<node>q;
char mp[55][55];
bool vis[55][55];
int r,c;
int gx,gy,tx,ty,d[55][55][2];
bool across(node a,node b)//判断是否穿过墙
{
	if(gx == a.x && gy > a.y && gx > b.x)
	{
		return 1;
	}
	if(gx == b.x && gy > b.y && gx > a.x)
	{
		return 1;
	}
	return 0;
}
void bfs()//广搜
{
	while(q.size())
	{
		node bei = q.top(),yong;
		q.pop();
		int x = bei.x;
		int y = bei.y;
		int k = bei.k;
		for(int i = 0; i < 8; i++)
		{
			int xx = dx[i] + x;
			int yy = dy[i] + y;
			yong = node(xx,yy,k);
			if(xx < 0 || xx >= r || yy < 0 || yy >= c || vis[xx][yy] == 1)
			{
				continue;
			}
			if(across(bei,yong))
				yong.k ^= 1;
			if(d[yong.x][yong.y][yong.k] <= d[bei.x][bei.y][bei.k] + 1)
			{
				continue;
			}
			d[yong.x][yong.y][yong.k] = d[bei.x][bei.y][bei.k] + 1;
			q.push(yong);
		}
	}
}
int main()
{
	freopen("grove.in","r",stdin);
	freopen("grove.out","w",stdout);
	scanf("%d%d",&r,&c);
	memset(d,0x7f,sizeof(d));
	for(int i = 0; i < r; i++)
	{
		scanf("%s",mp[i]);
		for(int j = 0; j < c; j++)
		{
			if(mp[i][j] == 'X')//建墙
			{
				vis[i][j] = 1;
				if(!gy)
				{
					gx = i,gy = j;
				}
			}
			else if(mp[i][j] == '*')//出发点
			{
				tx = i,ty = j;
				d[i][j][0] = 0;
				q.push(node(i,j,0)); 
			}
		}
	}
	bfs();//开始广搜
	printf("%d",d[tx][ty][1]);//输出答案
	return 0;
}

```


---

## 作者：Hughpig (赞：0)

题解区基本都是建墙法？我写篇不一样的。

直接广搜的话会直接走最短路径，不满足绕森林一圈这一限制。

考虑在森林边设置几个存档点，需要依次走到这几个存档点旁边再回到起点。可以取树林最上方、最下方、最左方、最右方的点，由于行走的路径是联通的，所以这样必然可以将森林包裹在内。

广搜依次求出从起点到这些点再回到起点的最短路径，然后寻找总路径长最短的方案即可。

代码：

```cpp
/*
*Author: Hughpig
*made in China
*/
#include<bits/stdc++.h>
using namespace std;
#define up(l,r,i) for (int i=(l);(i)<=(r);++i)
#define left OwO
#define right UwU
constexpr int N=55,dx[]= {
	1,1,1,0,-1,-1,-1,0
}
,dy[]= {
	1,0,-1,-1,-1,0,1,1
}
;
int n,m,dist[N][N],d[12][12],cnt,ans=1e9;
char grid[N][N];
struct point {
	int x,y;
}
s,left,right,up,down,qaq[12];
bool check(int x,int y,int x_,int y_) {
	if((int)abs(x-x_)==1&&(int)abs(y-y_)==1) {
		if(grid[x][y_]=='X'&&grid[x_][y]=='X')return 1;
		return 0;
	} else return 0;
}
void distbfs(point p) {
	memset(dist,0,sizeof(dist));
	up(1,n,i)up(1,m,j)if(grid[i][j]=='X')dist[i][j]=-1;
	dist[p.x][p.y]=0;
	queue<point> q;
	q.push(p);
	while(q.size()) {
		auto tmp=q.front();
		q.pop();
		int x=tmp.x,y=tmp.y;
		up(0,7,i) {
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<1||nx>n||ny<1||ny>m||(nx==p.x&&ny==p.y)||grid[nx][ny]=='X'||dist[nx][ny]||check(x,y,nx,ny))continue;
			dist[nx][ny]=dist[x][y]+1;
			q.push( {
				nx,ny
			}
			);
		}
	}
}
int main() {
	cin>>n>>m;
	left.y=m;
	right.y=0;
	up.x=n;
	down.x=0;
	up(1,n,i) {
		up(1,m,j) {
			cin>>grid[i][j];
			if(grid[i][j]=='*')s=(point) {
				i,j
			}
			;
			if(grid[i][j]=='X') {
				dist[i][j]=-1;
				if(j<=left.y)left=(point) {i,j-1};
				if(j>=right.y)right=(point) {i,j+1};
				if(i<=up.x)up=(point) {i-1,j};
				if(i>=down.x)down=(point) {i+1,j};
			}
		}
	}
	qaq[1]=s,qaq[2]=left,qaq[3]=up,qaq[4]=right,qaq[5]=down;
	up(1,5,i) {
		distbfs(qaq[i]);
		up(1,5,j)d[i][j]=dist[qaq[j].x][qaq[j].y];
	}
	ans=min(d[1][2]+d[2][3]+d[3][4]+d[4][5]+d[5][1],ans);
	ans=min(d[1][3]+d[3][4]+d[4][5]+d[5][2]+d[2][1],ans);
	ans=min(d[1][4]+d[4][5]+d[5][2]+d[2][3]+d[3][1],ans);
	ans=min(d[1][5]+d[5][2]+d[2][3]+d[3][4]+d[4][1],ans);
	cout<<ans;
	return 0;
}
```

---

