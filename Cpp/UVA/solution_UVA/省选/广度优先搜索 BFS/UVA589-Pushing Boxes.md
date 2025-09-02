# Pushing Boxes

## 题目描述

### 题面翻译

想象你站在一个二维的迷宫里，迷宫由 $R$ 列 $C$ 行共 $R\times C$ 个方格组成，有些方格里是岩石（所以你与箱子不能走到这些格子上），而另外的则是空格子。你可以在一个空格子上向北（上）、南（下）、东（右）、西（左）移动到另外一个相邻的空格子上，这个操作叫做**步行**。

有一个空格子上放着一个箱子，你可以站在盒子旁边，向盒子的方向移动，使得你和箱子共同平移一格（当然平移到的地方不能有岩石）。我们把这样的操作叫做**推**。你只能用推的方式来移动箱子，这意味着，如果你把箱子推到了死角里，你就无法将它推出来了。

现在给定你的起始坐标、箱子的起始坐标和箱子要被推到的坐标，请你找出一个最优的推箱子的操作序列，或报告无解。具体地说：

1. 这个操作序列的**推**操作的次数是最少的。

2. 在满足 (1) 的条件下，若存在不止一个操作序列，则要求操作序列的**总操作次数**（包括**步行**操作和**推**操作）最少。

3. 若在满足 (1) (2) 的条件下，操作序列仍然不唯一，任意输出一个均可。

## 说明/提示

$R,C \leq 20$。

## 样例 #1

### 输入

```
1 7
SB....T
1 7
SB..#.T
7 11
###########
#T##......#
#.#.#..####
#....B....#
#.######..#
#.....S...#
###########
8 4
....
.##.
.#..
.#..
.#.B
.##S
....
###T
0 0```

### 输出

```
Maze #1
EEEEE

Maze #2
Impossible.

Maze #3
eennwwWWWWeeeeeesswwwwwwwnNN

Maze #4
swwwnnnnnneeesssSSS```

# 题解

## 作者：☯☯枫☯☯ (赞：15)

[UVA589 Pushing Boxes](https://www.luogu.com.cn/problem/UVA589)

为什么题解里都是建图或者奇妙的双 $BFS$ ？明明一个 $BFS$ 就可以解决了嘛。

## 注意题意
-	把推的数量减到最少（一般的 $BFS$ 中距离是第一关键字，但是本题中推的数量才是第一关键字）。

-	如果有不止一个这样的序列，那么选择一个最小化总移动次数（步行和推送）的序列（也就是说，在记录推的次数的同时也要记录走的步数）。

- 	**在每个测试用例之后输出一个空行（意思就是，	每一组输入和输出后面要有额外的一个空行）**。

- 	$Maze$ #+ 数字 也是输出的一部分。

- 	每组数据处理之前记得对标记数组进行清空。


## 进入正题
一个 $BFS$ 解决本题的关键在于使用堆（优先队列），将推的次数作为第一关键字。

   **（当推的次数相同时，应当根据走的次数进行排序）**

部分代码如下：

```cpp
struct sta {//state:状态 
	int x,y;//人的位置 
	int bx,by;//箱子的位置(b:box) 
	string s="";/*用于记录走到当前位置的走法
	(这样写比较浪费空间，但是可以过，毕竟数据范围只
  	有20*20） 
	 */ 
	int ps,step;//ps:push用于记录推箱子的次数
	//step 记录走的总次数 
	bool operator <(const sta &a)const {
		if(ps==a.ps)return step>a.step;
		return ps>a.ps;
	//由于直接用大根堆写起来比较短，所以直接重载<
	//注意：如果要使用小根堆，必须将 > 和 < 都重载一遍 
	}
} s;//s记录初始状态 
```
    
采用四维数组 $vis$ 来记录是否走过

（ $BFS$ 板子：）
```
void bfs(sta s,int num) {
	priority_queue<sta> q;
	q.push(s);
	vis[s.x][s.y][s.bx][s.by]=1;
	while(!q.empty()) {
		sta t=q.top();
		q.pop();
		for(int i=0; i<4; i++) {
			sta P=t;
			P.x=t.x+g[i][0],P.y=t.y+g[i][1];
			if(check(P,i)) {
				if(pc[P.bx][P.by]=='T') {
					cout<<"Maze #"<<num<<endl;
					cout<<P.s<<endl;
					f=0;//此处f用于标记能否在走
   					到，f=0表示走到了，f=1表走不到 
					return ;
				}
				q.push(P);
			}
		}
	}
}
    
```

## 难点来了（敲黑板）

（好吧其实只要小心一点写起来并不难）

可以看出来，代码的成败在于上面 $BFS$ 板子里的 $check$ 函数。

（$check$ 函数用于判断能不能走，这里采用了直接在 $check$ 函数里	面对参数进行修改的技巧，可以使 $BFS$ 显得干净清楚。推荐大家多写函数，可以增强代码的可读性，易于调试）

- 	首先是边界的判断，不需要多讲。

- 	第二，当人往前走到空地上时，直接将走的步数加 $1$ ，	将走法和当前状态标记一下，比较简单。

- 	第三，当遇到箱子时，应当先“尝试”将箱子往同方向移动，进行边界判断，如果能推，就将相关参数进行修改。

代码如下：

```
bool check(sta &t,int i) {
	//t是需要判断能否走的状态，i是人走的方向 
	//用mk 代替了vis[t.x][t.y][t.bx][t.by]，写起来方便点 
	if(t.x<1||t.x>n||t.y<1||t.y>m||pc[t.x][t.y]=='#'||mk)return false;//边界判定 
	if(t.x==t.bx&&t.y==t.by) {//遇到箱子 
		int xx=t.bx+g[i][0],yy=t.by+g[i][1];
		//箱子走一步
		//事先定义了g数组，用于向四个方向走 
	if(pc[xx[yy]=='#'||xx<1||xx>n||yy<1||yy>m)return false;
		//箱子的边界判定 
		t.bx=xx,t.by=yy;
		t.ps++;
		t.s+=c[i];//记录走法 
	} else t.s+=c[i]-'A'+'a';
	t.step++;
	mk=1;//对新状态进行标记 
	return true;
}
```

其实，只要搞清楚了题目中各种关系，这道题目并不难（暴搜就行）。

完整代码如下：

```
#include<bits/stdc++.h>
#define mk vis[t.x][t.y][t.bx][t.by]
using namespace std;
const int N=21;
int n,m,g[4][2] {0,1,0,-1,1,0,-1,0};
bool vis[N][N][N][N],f;
char pc[N][N],c[4] {'E','W','S','N'};
struct sta {//state:状态
	int x,y;//人的位置
	int bx,by;//箱子的位置(b:box)
	string s="";/*用于记录走到当前位置的走法
	(这样写比较浪费空间，但是可以过，毕竟数据范围只有20*20）
	 */
	int ps,step;//ps:push用于记录推箱子的次数
	//step 记录走的总次数
	bool operator <(const sta &a)const {
		if(ps==a.ps)return step>a.step;
		return ps>a.ps;
		//由于直接用大根堆写起来比较短，所以直接重载 <
		//注意：如果要使用小根堆，必须将 > 和 < 都重载一遍
	}
} s;//s记录初始状态
void input() {
	//读入 
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			cin>>pc[i][j];
			if(pc[i][j]=='S')s.x=i,s.y=j;
			if(pc[i][j]=='B')s.bx=i,s.by=j;
		}
	}
}
bool check(sta &t,int i) {
	//t是需要判断能否走的状态，i是人走的方向 
	//用mk 代替了vis[t.x][t.y][t.bx][t.by]，写起来方便点 
	if(t.x<1||t.x>n||t.y<1||t.y>m||pc[t.x][t.y]=='#'||mk)return false;//边界判定 
	if(t.x==t.bx&&t.y==t.by) {//遇到箱子 
		int xx=t.bx+g[i][0],yy=t.by+g[i][1];
		//箱子走一步
		//事先定义了g数组，用于向四个方向走 
		if(pc[xx][yy]=='#'||xx<1||xx>n||yy<1||yy>m)return false;
		//箱子的边界判定 
		t.bx=xx,t.by=yy;
		t.ps++;
		t.s+=c[i];//记录走法 
	} else t.s+=c[i]-'A'+'a';
	t.step++;
	mk=1;//对新状态进行标记 
	return true;
}
void bfs(sta s,int num) {
	priority_queue<sta> q;
	q.push(s);
	vis[s.x][s.y][s.bx][s.by]=1;
	while(!q.empty()) {
		sta t=q.top();
		q.pop();
		for(int i=0; i<4; i++) {
			sta P=t;
			P.x=t.x+g[i][0],P.y=t.y+g[i][1];
			if(check(P,i)) {
				if(pc[P.bx][P.by]=='T') {
					cout<<"Maze #"<<num<<endl;
					cout<<P.s<<endl;
					f=0;//此处f用于标记能否在走到，f=0表示走到了，f=1表示走不到 
					return ;
				}
				q.push(P);
			}
		}
	}
}
int main() {
	int num=1;//记录测试组数 
	while(scanf("%d%d",&n,&m)&&n&&m) {
		f=1;//前面说过，标记是否能 走到 
		memset(vis,0,sizeof(vis));
		//对标记和各种参数进行清空，以免产生影响 
		s.s="";
		s.ps=0;
		s.step=0;
		input();
		bfs(s,num);
		if(f)cout<<"Maze #"<<num<<endl<<"Impossible."<<endl;
		cout<<endl;//记得换行，否则UVA会判WA 
		num++;
	}
	return 0;
}
```

（不加注释的话大约 1600 $B$ ）[AC](https://www.luogu.com.cn/record/43961163)

（本蒟首 $A$ 的紫题，写本蒟的第一篇题解纪念下）
  ## 感谢观看
  
  $ update 2021.1.31$ 修正了关于“分块”的不严谨说法（防止被误解为算法：分块）。

---

## 作者：Chester (赞：5)

$poj1475$ & $uva589$
码代码+调试耗了挺多时间，还给一个网上的题解拍出了错误（$push$次数相同，但人有走更少的路径）
  

明显的一个广搜，然而对象有两个-人和箱子。  
由于答案首先要保证$push$最少， 则可以考虑$bfs$箱子，将箱子的位置作为状态，建立$fbox[x][y][dir]$ 表示箱子在$(x,y)$上一步是向$dir$方向走的$push$次数，  
$fman[x][y][dir]$ 为人行走的步数  
在外层首先$bfs$箱子，然后再$bfs$人能否从当前位置走到推箱子的位置  

需要注意的是，$x,y,dir$如果相同，那么后遍历到的$fbox[x][y][dir]$只会更大或者相同，但是$fman[x][y][dir]$可能会比已知的更小，所以需要记录
贴代码  


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#define cl(a) memset(a,-1,sizeof(a))
using namespace std;
const int N=25,INF=~0U>>1;
int fbox[N][N][6],fman[N][N][6];
int n,m,dx[6]={-1,1,0,0,0,0},dy[6]={0,0,-1,1,0,0};
char s[N][N];
struct pos{
	int x,y;
}st,ed,stbx,last[N][N];
struct dp{
	int x,y,dir;
}pre[N][N][6];
inline pos mknd(int x,int y){
	pos ans;
	ans.x=x;ans.y=y;
	return ans;
}
inline dp make(int x,int y,int dir){
	dp ans;
	ans.x = x;
	ans.y = y;
	ans.dir = dir;
	return ans;
}

inline int jud(int x,int y){
	if(x<0 || x>=n || y<0 ||y>=m)return 0;
	if(s[x][y]=='#')return 0;
	return 1;
}
inline int bfs(pos S, pos T, pos bx){
	if(S.x== T.x && S.y== T.y)return 0;
	int dis[N][N];cl(dis);
	queue<pos>q;
	while(!q.empty())q.pop();
	q.push(S);
	dis[S.x ][S.y ]=0;
	for(pos nt,u; !q.empty() ;){
		u=q.front();q.pop();
		for(int i=0;i<4;++i){
			nt=mknd(u.x + dx[i], u.y + dy[i]);
			if( !jud(nt.x , nt.y ) )continue;//¿É×ß 
			if(nt.x == bx.x && nt.y== bx.y)continue;//²»ÓëÏä×ÓÖØºÏ 
			if(dis[nt.x ][nt.y ] != -1)continue;
			
			dis[nt.x ][nt.y ] = dis[u.x ][u.y ]+1;
			last[nt.x ][nt.y ]=mknd(u.x ,u.y );
			if(nt.x == T.x && nt.y == T.y) return dis[nt.x ][nt.y ];
			q.push(nt);
		}
	}
	return INF;
}
dp BFS(){
	int flag=INF,MIN=INF;
	queue<dp>qq;
	while(!qq.empty())qq.pop();
	for(int i=0,cnt;i<4;++i){
		if( !jud( stbx.x-dx[i], stbx.y-dy[i]) )continue;
		if( !jud(stbx.x+dx[i], stbx.y+dy[i]) )continue;
		dp nt=make( stbx.x+dx[i], stbx.y+dy[i], i);
		cnt=bfs( st, mknd(stbx.x-dx[i], stbx.y-dy[i]) , stbx);
		if(cnt==INF)continue;
		fman[nt.x ][nt.y ][nt.dir ]=cnt+1;
		fbox[nt.x ][nt.y ][nt.dir ]=1;
		pre[nt.x ][nt.y ][nt.dir ]=make( st.x, st.y, 4);
		qq.push(nt);
		if(nt.x==ed.x &&nt.y==ed.y)flag=1,MIN=cnt+1;
	}
	for(dp u,nt; !qq.empty() ;){
		u=qq.front();qq.pop();
		if(fbox[u.x ][u.y ][u.dir ]==flag)break;
		
		for(int i=0,cnt;i<4;++i){
			nt=make(u.x+dx[i], u.y+dy[i], i);
			if( !jud(nt.x, nt.y) )continue;
			if( !jud(u.x-dx[i], u.y-dy[i]) )continue;
			if(fbox[nt.x ][nt.y ][nt.dir ] <= fbox[u.x ][u.y ][u.dir ] && fbox[nt.x ][nt.y ][nt.dir ]!=-1)continue;
			cnt=bfs(mknd(u.x-dx[u.dir], u.y-dy[u.dir]), mknd(u.x-dx[i], u.y-dy[i]), mknd(u.x ,u.y ) );
			if(cnt==INF)continue;
			cnt++;
			if(fman[nt.x ][nt.y ][nt.dir]==-1 || fman[nt.x ][nt.y ][nt.dir]>fman[u.x ][u.y ][u.dir ]+cnt){
				fman[nt.x ][nt.y ][nt.dir]=fman[u.x ][u.y ][u.dir ]+cnt;
				pre[nt.x ][nt.y ][nt.dir ]=u;
			}
			if(fbox[nt.x ][nt.y ][nt.dir ]==-1){
				fbox[nt.x ][nt.y ][nt.dir ]=fbox[u.x ][u.y ][u.dir ]+1;
				qq.push(nt);
			}
			if(nt.x==ed.x && nt.y==ed.y){
				flag=fbox[nt.x ][nt.y ][nt.dir];
				MIN=min(MIN , fman[nt.x ][nt.y ][nt.dir ]);
			}
			
		}
	}
	for(int i=0;i<4;++i)if(fman[ed.x ][ed.y ][i ]==MIN)return make(ed.x ,ed.y ,i);
	return make(INF,0,0);
}
void print2(pos des,pos nxt){
	if(des.x==nxt.x && des.y==nxt.y)return;
	pos now=last[nxt.x ][nxt.y];
	print2(des, now);
	if(now.x==nxt.x){
		if(nxt.y==now.y+1)putchar('e');
		else putchar('w');
	}
	else{
		if(nxt.x==now.x+1)putchar('s');
		else putchar('n');
	} 
}
void print(dp nt){
	dp u=pre[nt.x ][nt.y ][nt.dir ];
	pos now=mknd(u.x-dx[u.dir], u.y-dy[u.dir]);
	pos nxt=mknd(nt.x-2*dx[nt.dir], nt.y-2*dy[nt.dir]);
	if(nt.dir==4)return;
	print(u);
	
	int cnt=bfs(now, nxt, mknd(nt.x-dx[nt.dir], nt.y-dy[nt.dir]));
	if(cnt!=INF && cnt)print2(now,nxt);
	if(u.dir==4){
		if(stbx.x==nt.x){
			if(nt.y==stbx.y+1)putchar('E');
			else putchar('W');
		}
		else {
			if(nt.x==stbx.x+1)putchar('S');
			else putchar('N');
		}
		return;
	}
	if(u.x==nt.x){
		if(nt.y==u.y+1)putchar('E');
		else putchar('W');
	}
	else{
		if(nt.x==u.x+1)putchar('S');
		else putchar('N');
	}
}
int main()
{
	for(int T=1;;T++){
		scanf("%d%d",&n,&m);
		if(!n&&!m)return 0;
		for(int i=0;i<n;++i)scanf("%s",s[i]);
		for(int i=0;i<n;++i)for(int j=0;j<m;++j){
			if(s[i][j]=='S')st=mknd(i,j);
			if(s[i][j]=='B')stbx=mknd(i,j);
			if(s[i][j]=='T')ed=mknd(i,j);
		}
		cl(fbox);cl(fman);
		dp ans=BFS();
		printf("Maze #%d\n",T);
		if(ans.x==INF){
			printf("Impossible.\n\n");
			continue;
		}
		print(ans);
		putchar('\n');putchar('\n');
	}
}
```

---

## 作者：Baihua (赞：4)

### UVA589 Pushing Boxes

#### 题意 ： 推箱子游戏

* 这里提供一种**图论**解法 。

* 设计状态为四元组$(Px,Py,Bx,By)$ 分别代表人的坐标和箱子的坐标 。

* 设计路程为二元组$Dis(Push,Walk)$ 分别代表推箱子的次数和走路的次数。

* 路程$A$大于路程$B$ 

  ```c++
  bool Cmp (const Dis &A , const Dis &B) {
      if (A.Push != B.Push ) return A.Push > B.Push ;
      else return A.Walk > B.Walk;
  }
  ```
* 两个路程叠加，需要把两个属性分别叠加：

  ```cpp
  Dis Plus (Dis &A , Dis &B) {
      Dis C ;
      C.Push = A.Push + B.Push ;
      C.Walk = A.Walk + B.Walk ;
      return C ;
  }
  ```

* 然后用~~死了的~~ $SPFA$ 就可以解决图论问题了

#### CODE

```c++
#include <stdio.h>
#include <string.h>
#define re register
#define Clean(X,K) memset(X,K,sizeof(X))
#define Jud(X,Y) (X<1||X>N||Y<1||Y>M||A[X][Y])
#define GC getchar()
int Qread () {
    int X = 0 ;
    char C = GC ;
    while (C > '9' || C < '0') C = GC ;
    while (C >='0' && C <='9') {
        X = X * 10 + C - '0' ;
        C = GC ;
    }
    return X ;
}
const int Maxn = 25 , Maxq = Maxn * Maxn , INF = 20021020 * 5 , Dx[]= {-1,1,0,0} , Dy[]= {0,0,-1,1};
const char C[]= {'N','S','W','E'} , c[]= {'n','s','w','e'} ;
char  Ans[Maxn * Maxn] = "";
int   Vis[Maxn][Maxn][Maxn][Maxn] ,N , M ,A[Maxn][Maxn] , Ex , Ey , Px[Maxn * Maxn * Maxn * Maxn] , Py[Maxn * Maxn * Maxn * Maxn] , Bx[Maxn * Maxn * Maxn * Maxn] , By[Maxn * Maxn * Maxn * Maxn];
char Nxt[Maxn][Maxn][Maxn][Maxn];
struct Node {
    int X1 ,Y1 , X2 , Y2 ;
};
Node FT[Maxn][Maxn][Maxn][Maxn] , E;
Node Findf(Node X) {
    if (FT[X.X1][X.Y1][X.X2][X.Y2].X2!=0)FT[X.X1][X.Y1][X.X2][X.Y2] = Findf(FT[X.X1][X.Y1][X.X2][X.Y2]) ;
    int Ln = strlen (Ans) ;
    Ans[Ln] = Nxt[X.X1][X.Y1][X.X2][X.Y2];
    Ans[Ln + 1] = '\0' ;
    return FT[X.X1][X.Y1][X.X2][X.Y2] ;
}
struct Dis {
    int Push , Walk ;
};
Dis Plus (Dis &A , Dis &B) {
    Dis C ;
    C.Push = A.Push + B.Push ;
    C.Walk = A.Walk + B.Walk ;
    return C ;
}
bool Cmp (const Dis &A , const Dis &B) {
    if (A.Push != B.Push ) return A.Push > B.Push ;
    else return A.Walk > B.Walk;
}
/*
头文件和准备工作
1. SPFA用到的队列分别是 Px[Maxn * Maxn * Maxn * Maxn] , Py[Maxn * Maxn * Maxn * Maxn] , Bx[Maxn * Maxn * Maxn * Maxn] , By[Maxn * Maxn * Maxn * Maxn];
各自代表了人的坐标，箱子的坐标。
2.定义距离为二元组（推动的次数，走的步数）
3.定义比较和叠加函数Plus和Cmp ；
4.Nxt数组记录了每一步所走的方向，用于递归输出路径。 
*/ 
Dis Mdis[Maxn][Maxn][Maxn][Maxn] ;
Dis One , Zero , _INF ;
Dis SPFA() {
    int H = 0 , T = 1 ;
    Dis Ans = _INF ;
    Clean( Vis , 0) , Clean(Mdis , 0x3f ) ;
    Clean(FT, 0) ;
    Mdis[Px[1]][Py[1]][Bx[1]][By[1]] = Zero ;
    Vis[Px[1]][Py[1]][Bx[1]][By[1]] = 1 ;
    while (H < T) {
        ++ H ;
        Vis[Px[H]][Py[H]][Bx[H]][By[H]] = 0 ;
        Node XX;
        XX.X1 = Px[H] , XX.Y1 = Py[H] , XX.X2 = Bx[H] , XX.Y2 = By[H] ;
        if (Bx[H] == Ex && By[H] == Ey) {
            if (Cmp (Ans , Mdis[Px[H]][Py[H]][Bx[H]][By[H]] ) ) {
                Ans = Mdis[Px[H]][Py[H]][Bx[H]][By[H]] ;
                E.X1 = Px[H] , E.Y1 = Py[H] , E.X2 = Bx[H] , E.Y2 = By[H] ;
            }
        }

        for (re int i = 0 ; i < 4 ; ++ i) {
            int Kx = Dx[i] + Px[H] , Ky = Dy[i] + Py[H];
            if (Jud (Kx , Ky)) continue ;
            if (Kx == Bx[H] && Ky == By[H]) {
                int Tx = Dx[i] + Bx[H] , Ty = Dy[i] + By[H] ;
                if (Jud (Tx , Ty)) continue ;
                if (Cmp (Mdis[Kx][Ky][Tx][Ty] , Plus (Mdis[Px[H]][Py[H]][Bx[H]][By[H]] , One))) {
                    Mdis[Kx][Ky][Tx][Ty] = Plus (Mdis[Px[H]][Py[H]][Bx[H]][By[H]] , One) ;
                    FT[Kx][Ky][Tx][Ty] = XX ;
                    Nxt[Kx][Ky][Tx][Ty] = C[i] ;
                    if (Vis[Kx][Ky][Tx][Ty]) continue ;
                    ++ T ;
                    Vis[Kx][Ky][Tx][Ty] = 1 ;
                    Px[T] = Kx , Py[T] = Ky , Bx[T] = Tx , By[T] = Ty;
                }
                continue ;
            }
            if (Cmp (Mdis[Kx][Ky][Bx[H]][By[H]]  ,Mdis[Px[H]][Py[H]][Bx[H]][By[H]] )) {
                Mdis[Kx][Ky][Bx[H]][By[H]] = Mdis[Px[H]][Py[H]][Bx[H]][By[H]] ;
                FT[Kx][Ky][Bx[H]][By[H]] = XX ;
                Nxt[Kx][Ky][Bx[H]][By[H]] = c[i] ;
                if (Vis[Kx][Ky][Bx[H]][By[H]]) continue ;
                ++ T ;
                Vis[Kx][Ky][Bx[H]][By[H]] = 1 ;
                Px[T] = Kx , Py[T] = Ky , Bx[T] = Bx[H] , By[T] = By[H] ;
            }
        }
    }
    return Ans;
}
/*
SPFA求最短路
实际上还是SPFA的模板，修改了路线长短的判断。 
*/
int main () {
    One.Push = 1 ;
    One.Walk = 0 ;
    Zero.Push = Zero.Walk = 0;
    _INF.Push = _INF.Walk = INF;
    
/*
这里定义了One和Zero，分别是0步和推1步，可以直接用在SPFA里面。 
*/
    //freopen ("UVA589.in" , "r" , stdin) ;
    N = Qread () , M = Qread() ;
    int T = 0 ;
    while (N + M) {
        ++T ;
        Clean(Ans,  0) ;
        Ans[0] = '\0' ;
        Clean(A , 0)  ;
        Clean(Nxt , 0) ;
        for (re int i = 1 ; i <= N; ++ i)
            for (re int j = 1 ; j <= M; ++ j) {
                char C = GC ;
                while (C != '.' && C != '#' && C !='S' && C != 'T' && C != 'B') C = GC ;
                A[i][j] = (C == '#' ? 1 : 0) ;
                if (C == 'S') Px[1] = i , Py[1] = j ;
                if (C == 'B') Bx[1] = i , By[1] = j ;
                if (C == 'T') Ex= i , Ey = j ;
            }
//读入数据
        Dis MinL = SPFA() ;//SPFA 计算最短路 
        Findf(E) ;//递归查找路径 
        printf ("Maze #%d\n" , T) ;
        if (MinL.Push  == INF) printf ("Impossible.\n");
        else
        printf ("%s\n" , Ans) ;
        putchar(10) ;
        N = Qread() , M = Qread() ;
    }
    fclose (stdin) ;
    fclose (stdout);
    return 0;
}
```

### Thanks! 

---

## 作者：雨幕散影_小初 (赞：1)

**UVA589 【Pushing Boxes】**

这是我写过比较长的搜索题了

简直就是毒瘤题，细节多，但写完之后对宽搜以及最短路会有更深刻的理解

第一眼看到题毫无思路，认真思考发现可以将问题转化，推一次箱子的代价尽量大100000就够了，走路代价为一，这样就转化为了简单最短路（dis）。每次记录到达当前状态的上一个状态（pre），以及由上一个状态如何走转移到当前状态（tp）。

输出是递归输出，注意UVA的毒瘤输出endl不要忘
```cpp
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=25;
int c,r,cas,dis[N][N][N][N],cost,ans;
char mp[N][N],tp[N][N][N][N];
int stax,stay,boxx,boxy,endx,endy,ansx,ansy;
struct node{int x,y,xx,yy;}pre[N][N][N][N];
bool vis[N][N][N][N];
queue<node> q;
inline void exp(int nex,int ney,int nexx,int neyy,char c,node now)
{
	if(dis[nex][ney][nexx][neyy]>dis[now.x][now.y][now.xx][now.yy]+cost)
	{
		dis[nex][ney][nexx][neyy]=dis[now.x][now.y][now.xx][now.yy]+cost;
		pre[nex][ney][nexx][neyy]=now;
		tp[nex][ney][nexx][neyy]=c;
		if(nexx==endx&&neyy==endy)//到达终点更新答案
		{
			if(dis[nex][ney][nexx][neyy]<ans)
			ans=dis[nex][ney][nexx][neyy],ansx=nex,ansy=ney;
			return;
		}
		if(!vis[nex][ney][nexx][neyy])
		vis[nex][ney][nexx][neyy]=1,q.push(node{nex,ney,nexx,neyy});
	}
}
inline void spfa()//spfa板子
{
	q=queue<node>();//队列不支持clear所以用赋值
	q.push(node{stax,stay,boxx,boxy});
	vis[stax][stay][boxx][boxy]=true;
	dis[stax][stay][boxx][boxy]=0;
	while(!q.empty())
	{
		node now=q.front();q.pop();
		vis[now.x][now.y][now.xx][now.yy]=0;
     //向四个方向扩展这里不想开方向数组于是循环展开，还能加速
		if(now.x+1<=c&&mp[now.x+1][now.y]!='#')
		{
			if(now.x+1==now.xx&&now.y==now.yy)
			{
				cost=100000;//有箱子
				if(now.xx+1<=c&&mp[now.xx+1][now.yy]!='#')//能推
				exp(now.x+1,now.y,now.xx+1,now.yy,'S',now);
			}
			else cost=1,exp(now.x+1,now.y,now.xx,now.yy,'s',now);//没箱子
		}
		if(now.y+1<=r&&mp[now.x][now.y+1]!='#')
		{
			if(now.x==now.xx&&now.y+1==now.yy)
			{
				cost=100000;
				if(now.yy+1<=r&&mp[now.xx][now.yy+1]!='#')
				exp(now.x,now.y+1,now.xx,now.yy+1,'E',now);
			}
			else cost=1,exp(now.x,now.y+1,now.xx,now.yy,'e',now);
		}
		if(now.x-1>=1&&mp[now.x-1][now.y]!='#')
		{
			if(now.x-1==now.xx&&now.y==now.yy)
			{
				cost=100000;
				if(now.xx-1>=1&&mp[now.xx-1][now.yy]!='#')
				exp(now.x-1,now.y,now.xx-1,now.yy,'N',now);
			}
			else cost=1,exp(now.x-1,now.y,now.xx,now.yy,'n',now);
		}
		if(now.y-1>=1&&mp[now.x][now.y-1]!='#')
		{
			if(now.x==now.xx&&now.y-1==now.yy)
			{
				cost=100000;
				if(now.yy-1>=1&&mp[now.xx][now.yy-1]!='#')
				exp(now.x,now.y-1,now.xx,now.yy-1,'W',now);
			}
			else cost=1,exp(now.x,now.y-1,now.xx,now.yy,'w',now);
		}
	}
}
inline void output(node now)
{//递归输出
	if(now.x==stax&&now.y==stay&&now.xx==boxx&&now.yy==boxy)return;
	output(pre[now.x][now.y][now.xx][now.yy]);
	cout<<tp[now.x][now.y][now.xx][now.yy];
}
int main()
{
	ios::sync_with_stdio(false);//关同步，加速读入
	while(cin>>c>>r)
	{
		ans=0x7fffffff;
		if(!c && !r)return 0;
		memset(dis,0x3f,sizeof(dis));
		memset(vis,0,sizeof(vis));//初始化
		for(int i=1;i<=c;i++)for(int j=1;j<=r;j++)
		{
			cin>>mp[i][j];
			if(mp[i][j]=='S')stax=i,stay=j;
			if(mp[i][j]=='T')endx=i,endy=j;
			if(mp[i][j]=='B')boxx=i,boxy=j;
		}
		spfa();
		cout<<"Maze #"<<++cas<<endl;
		if(ans==0x7fffffff)cout<<"Impossible."<<endl;
		else output(node{ansx,ansy,endx,endy}),cout<<endl;
		cout<<endl;//毒瘤输出
	}
}
```

---

