# Dungeon Master

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=7&page=show_problem&problem=473

[PDF](https://uva.onlinejudge.org/external/5/p532.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA532/f5204064f9aec4c41d412eb29fbc006dac1f717c.png)

## 样例 #1

### 输入

```
3 4 5
S....
.###.
.##..
###.#
#####
#####
##.##
##...
#####
#####
#.###
####E
1 3 3
S##
#E#
###
0 0 0```

### 输出

```
Escaped in 11 minute(s).
Trapped!```

# 题解

## 作者：微稂_小哥 (赞：11)

输入时找到终点和起点，用f三维数组来保存3维的图。

开始BFS。。。。

注意N的大小是100。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
struct que{
	int x,z,y;
}b[10000];//队列 
char c[101][101][101];//输入保存，后转化为 f 
bool f[101][101][101];//记录图的信息 
int v[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};//方向 
int nu[10000],n,m,k;//nu计数器 
int bfs(int z1,int x1,int y1,int z2,int x2,int y2)//起点 终点 
{
	int head=0,tail=1,i,x,y,z;
	b[head].x=x1,b[head].y=y1,b[head].z=z1;
	nu[head]=0;
	f[z1][x1][y1]=1;
	while(head<tail)
	{
		for(i=0;i<6;i++)
		{
			z=b[head].z+v[i][0];
			x=b[head].x+v[i][1];
			y=b[head].y+v[i][2];
			if(x>=0&&y>=0&&z>=0&&x<n&&y<m&&f[z][x][y]==0&&z<k)//判断是否可行，防止越界！ 
			{
				f[z][x][y]=1;
				nu[tail]=nu[head]+1;
				b[tail].z=z;b[tail].x=x;b[tail].y=y;
				if(z==z2&&x==x2&&y==y2)	return nu[tail];//返回广搜的层数，也是最短路径的长度。 
				tail++;
			}
		}
		head++;
	}
	return -1;//没有找到终点的情况 
}
int main(){
	int i,j,q,x,y,x1,y1,z,z1;
	while(cin>>k>>n>>m)
	{
		memset(f,0,sizeof(f));
		if(k==0&&n==0&&m==0)	break;//结束 
		for(i=0;i<k;i++)
			for(j=0;j<n;j++)	cin>>c[i][j];
		for(i=0;i<k;i++)//处理c字符数组，找起点和终点 
			for(j=0;j<n;j++)
				for(q=0;q<m;q++)
				{
					if(c[i][j][q]=='S')	z=i,x=j,y=q;
					else if(c[i][j][q]=='E')	z1=i,x1=j,y1=q;
					else if(c[i][j][q]=='#')	f[i][j][q]=1;
				}
		int t=bfs(z,x,y,z1,x1,y1);
		if(t==-1)	printf("Trapped!\n");
		else	printf("Escaped in %d minute(s).\n",t);
	}
	return 0;
}
```
第一篇题解，写的不好，请见谅。
//为了防止抄袭，本代码的数组略开小。

---

## 作者：hezhijin (赞：9)

	 c++写法：
     对于题目给出的数据的含义就是驶入l,r,c，分别代表迷宫有1层，每层长宽分别是c,r。
     用BFS解，每次去队首元素，如果是终点则输出结果移动次数，否则，从该点开始分别向东南西北上下移动（如果可以走的话）并继续搜索，如果到队列为空还没没搜索到解法，测说明无解。
     以下为源代码：（请参考）
     #include <bits/stdc++.h>
 	using namespace std;
 	int xx[6]={-1,1,0,0,0,0},
	yy[6]={0,0,-1,1,0,0},
	zz[6]={0,0,0,0,-1,1};
	int h[27001][5];
	bool a[31][31][31];
 	int main()
	{
	#### int l,r,c,t,w,x,y,z,fx,fy,fz;
	char ch;
	bool s;
	#### while(cin>>l>>r>>c)
	{
		if(l==0&&r==0&&c==0)
		return 0;
		for(x=1;x<=l;++x)
		for(y=1;y<=r;++y)
		for(z=1;z<=c;++z)
	{
		cin>>ch;
		if(ch=='S')
		{
			a[x][y][z]=false;
			h[1][1]=x;
			h[1][2]=y;
			h[1][3]=z;
			h[1][4]=0;
		}
		else if(ch=='E')
		{
			a[x][y][z]=true;
			fx=x;
			fy=y;
            fz=z;
		}
		else if(ch=='#') a[x][y][z]=false;
		else a[x][y][z]=true;
	}
	t=0;w=1;
	s=false;
	do
	{
		t++;
		for(int i=0;i<6;++i)
		{
			x=h[t][1]+xx[i];
			y=h[t][2]+yy[i];
			z=h[t][3]+zz[i];
			if(x>0&&x<=l&&y>0&&y<=r&&z>0&&z<=c&&a[x][y][z])
			{
				a[x][y][z]=false;
				w++;
				h[w][1]=x;
				h[w][2]=y;
				h[w][3]=z;
				h[w][4]=h[t][4]+1;
				if(x==fx&&y==fy&&z==fz)
				{
					
		cout
 		<<"Escaped in "
    	<<h[w][4]<<" minute(s)."<<endl;
				s=true;
				break;
				}
			}
		}
	}while(t<w&&s==false);
	if(s==false)
	cout<<"Trapped!"<<endl;
	}
	return 0;
}

---

## 作者：Atmizz (赞：7)

### 三维BFS+STL
其实这是一道简单的三维BFS+queue的题目，相比较与其他二维BFS迷宫问题，三维只是多加了一个楼层，那么我们就把二维转化为三维，其他的与二维迷宫差不了太多。详细解释在代码中，我已经解释得很详尽了，希望各位可以听懂。
### 然后的话，我就想说一句话，拒绝抄袭！！
```cpp
#include<cstdio>//不建议使用万能头文件
#include<iostream>
#include<queue>
#include<cmath>
#include<cstring>
using namespace std;
int n,k,m,fl,bf,bx,by,ef,ex,ey,flag,ff[6]={1,-1,0,0,0,0},xx[6]={0,0,1,-1,0,0},yy[6]={0,0,0,0,1,-1};
//ff是楼层的移动方式，xx是x坐标的移动方式，yy是y坐标的移动方式。
//flag看他能否到达指定的终点
char map[101][101][101];
//map是来输入地图，如果使用了<map>的头文件，那么map的数组名字就不能用了
bool v[101][101][101];
//v来看当前坐标是否已经走了一次
struct node
//结构体来表明走到的楼层，当前楼层的坐标和现在已经走了几分钟。
{
	int f,x,y,step;
};
void bfs(int f,int x,int y)//其实不带参也行。
{
	node now,net;//结构体定义
	queue<node>q;//BFS是依靠队列的，但是我喜欢用STL的queue，好用。
	now.f=f;now.x=x;now.y=y;now.step=0;
    //类似于初始化
	q.push(now);//放入队列中
	while(!q.empty()) {
		now=q.front();
		q.pop();
		if(now.f==ef && now.x==ex && now.y==ey) {//到达目的地，不仅只是x对应，y对应了，f（floor楼层）也要对应
			printf("Escaped in %d minute(s).\n",now.step);//输出当前所用的时间
			flag=1;//一定要改变flag，说明可以走到
			break;
		}
		for(int i=0;i<6;i++) {//从二维变成三维，又加了两种走法，上下楼，所以是6、种。
			net.f=now.f+ff[i];net.x=now.x+xx[i];net.y=now.y+yy[i];//先走一步试试，下面开始是否出界。
			if(net.f>=1 && net.f<=fl && net.x>=1 && net.x<=n && net.y>=1 && net.y<=m && v[net.f][net.x][net.y]==0 && map[net.f][net.x][net.y]!='#') {//判断是否出界或者走过或者是障碍。
				v[net.f][net.x][net.y]=1;net.step=now.step+1;//访问置1，时间加一分钟。
				q.push(net);//放入队列中
			}
		}
	}
}
int main()
{
	while(scanf("%d%d%d",&fl,&n,&m)!=EOF && fl && n && m) {//输入方法要注意
		flag=0;//一定要置零
		memset(v,0,sizeof(v));//初始化访问。
		for(int y=1;y<=fl;y++)//开始输入三维迷宫
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++) {
					cin>>map[y][i][j];
					if(map[y][i][j]=='S'){//记录起点
						bf=y;bx=i;by=j;
					}
					if(map[y][i][j]=='E'){//记录终点
						ef=y;ex=i;ey=j;
					}
				}
		v[bf][bx][by]=1;//起点置1
		bfs(bf,bx,by);//开始广搜
		if(flag==0)//判断是否可以到达目的地
			printf("Trapped!\n");
	}
}
```

---

## 作者：Nartsam (赞：5)

三维的迷宫虽然看上去好像比二维的难了一点，但其实只要在广搜的时候多枚举一个维度就好了。。。

二维迷宫的走法是搜索最基础的应用，在许多算法竞赛入门书籍中都有详细的解释，这里我主要结合代码讲一下如何把走二维迷宫的程序拓展到可以走三维迷宫

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=30+7;
const int dx[6]={-1,0,1,0,0,0},dy[6]={0,1,0,-1,0,0},dz[6]={0,0,0,0,1,-1}; //方向数组，方便搜索的时候计算下一个状态
struct Point{  //用结构体保存三维空间中的一个点
	int x,y,z;
	void init(int i=0,int j=0,int k=0){
		x=i; y=j; z=k;
	}
}sp,ep;   //起点，终点
int n,m,h;  //长，宽，高
int a[MAXN][MAXN][MAXN],dis[MAXN][MAXN][MAXN]; //a数组用来存地图，dis数组用来保存起点到该点的最短距离
bool check(Point p){  //判断一个点是否合法（是否超出范围？是否是障碍物点？是否已经被搜索过？）
	if(p.x>n||p.x<1||p.y>m||p.y<1||p.z>h||p.z<1) return 0;
	if(a[p.x][p.y][p.z]!=1) return 0;
	if(dis[p.x][p.y][p.z]!=-1) return 0;
	return 1; 
}
Point Next(Point p,int i){  //走到相邻的点
	Point res;
	res.init(p.x+dx[i],p.y+dy[i],p.z+dz[i]);
	return res;
}
void SerachPath(){  //广搜主体
	memset(dis,-1,sizeof(dis));  //初始化，dis为-1代表该点还没有被搜索到
	dis[sp.x][sp.y][sp.z]=0;
	queue<Point> q;
	q.push(sp);
	while(!q.empty()){
		Point hed=q.front(); q.pop();
		int cur=dis[hed.x][hed.y][hed.z]; //起点走到hed点的代价
		for(int twd=0;twd<6;twd++){
			Point now=Next(hed,twd);
			if(!check(now)) continue; //不合法就跳过
			dis[now.x][now.y][now.z]=cur+1;
			q.push(now);
		}
	}
}
int main(){
	while(scanf("%d %d %d",&h,&n,&m)&&n&&m&&h){
		for(int k=1;k<=h;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=m;j++){
					char c; scanf(" %c",&c);
					if(c=='#') a[i][j][k]=0;
					else a[i][j][k]=1; //1代表该点可以走
					if(c=='S') sp.init(i,j,k);
					if(c=='E') ep.init(i,j,k);
                                        //记录起点，终点 ↑↑↑
				}
			}
		}
		SerachPath();     //出发了！
		if(dis[ep.x][ep.y][ep.z]==-1) puts("Trapped!");  //找不到路径
		else printf("Escaped in %d minute(s).\n",dis[ep.x][ep.y][ep.z]);
	}
	return 0;
}
```


---

## 作者：AuroraIris (赞：5)

这是一道三维的广搜题，要注意的就是要在一般的二位广搜下的拓展方式多加两种，还有要记录步数(其实和二位差不多，并没有什么好说的)。
```pascal
const hhx:array[1..6] of longint=(0,0,0,0,1,-1);
      hhy:array[1..6] of longint=(0,0,1,-1,0,0);
      hhz:array[1..6] of longint=(1,-1,0,0,0,0);
var
	l,r,c,i,j,k,ansx,ansy,ansz:longint;
	a:array[0..100,0..100,0..100] of char;
	pd:array[0..100,0..100,0..100] of boolean;
	ll:array[0..1000000,1..4] of longint;
procedure find(x,y,z:longint);
var ii,h,t,xx,yy,zz:longint;
begin
	ll[1,1]:=x;
	ll[1,2]:=y;
	ll[1,3]:=z;
	ll[1,4]:=0;
	pd[x,y,z]:=false;
	h:=0;
	t:=1;
	while h<t do
	begin
		inc(h);
		for ii:=1 to 6 do
		begin
				xx:=ll[h,1]+hhx[ii];
				yy:=ll[h,2]+hhy[ii];
				zz:=ll[h,3]+hhz[ii];
				if a[xx,yy,zz]<>'#' then
				if pd[xx,yy,zz] then
				if (xx<=l) and (xx>=1) then
                if (yy<=r) and (yy>=1) then
                if (zz<=c) and (zz>=1) then
				begin
					inc(t);
					ll[t,1]:=xx;
					ll[t,2]:=yy;
					ll[t,3]:=zz;
					ll[t,4]:=ll[h,4]+1;//当前的步数为为拓展过来的ll[h,4]+1
					pd[xx,yy,zz]:=false;
					if a[xx,yy,zz]='E' then
					begin
						writeln('Escaped in ',ll[t,4],' minute(s).');
					exit;
					end;
				end;
		end;
	end;
	writeln('Trapped!');
end;
begin
	while true do
	begin
	fillchar(pd,sizeof(pd),true);
	readln(l,r,c);
	if (l=0) or (r=0) or (c=0) then halt;
	for i:=1 to 31 do
	for j:=1 to 31 do
	for k:=1 to 31 do
		a[i,j,k]:='#';
	for k:=1 to l do
	begin
		for i:=1 to r do
		begin
			for j:=1 to c do
			begin
				read(a[k,i,j]);
				if a[k,i,j]='S' then
                begin
                ansx:=k;
                ansy:=i;
                ansz:=j;
                end;
			end;
				readln;
		end;
		if k=l then
		readln;//奇奇怪怪的读入格式
	end;
	find(ansx,ansy,ansz);
end;
end.

```

---

## 作者：zhangzhaoke (赞：3)

蒟蒻的第二篇题解，管理大大求过

一道广搜，比较困难，我这个蒟蒻没想出更好的


~~求过！！！~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,x,y,h,t,tot,ans[100],mkkk=1;
char mp[35][35][35];//保存地图 
int f[40000],s[40000][4];//保存父结点和结点 
int walk[7][4]={{0,0,0,0},{0,0,0,1},{0,0,0,-1},{0,0,1,0},{0,0,-1,0},{0,1,0,0},{0,-1,0,0}};//保存走法 
void back(int t){
	if(t==1)return;
	tot++;
	back(f[t]);
}//统计次数 
void bfs(){
	h=1;t=1;//头尾指针 
	while(h<=t){
	for(int i=1;i<=6;i++){
		int l1,x1,y1;
		l1=s[h][1]+walk[i][1];
		x1=s[h][2]+walk[i][2];
		y1=s[h][3]+walk[i][3];
		if(l1>=1&&l1<=l&&x1>=1&&x1<=x&&y1>=1&&y1<=y&&mp[l1][x1][y1]!='#'&&mp[l1][x1][y1]!='E'){
		//满足要求 
		t++;//尾指针++
 		}
		mp[l1][x1][y1]='#';//标记为不能走 
		s[t][1]=l1;
		s[t][2]=x1;
		s[t][3]=y1;
		f[t]=h;//记录该结点的父结点 
	}
	if(mp[l1][x1][y1]=='E'){//找到了终点 
		t++;
		f[t]=h;
		tot=0;
		back(t);//统计次数 
		ans[mkkk]=tot;
		mkkk++;//保存答案 
		return;//返回 
	}
}
	h++;
}
	if(h>=t){
		ans[mkkk]=0;
		mkkk++;//找不到则记为零 
	}
}
int main(){
	cin>>l>>x>>y;
	while(l!=0&&x!=0&&y!=0){ 
		memset(s,0,sizeof(s));
		memset(f,0,sizeof(f));
	for(int i=1;i<=l;i++)
	for(int j=1;j<=x;j++)
	for(int k=1;k<=y;k++){
		cin>>mp[i][j][k];
		if(mp[i][j][k]=='S'){
			s[1][1]=i;
			s[1][2]=j;
			s[1][3]=k;
		}//找出起点 
	}
	bfs();//广搜 
	cin>>l>>x>>y;
	}//输入及广搜 
	for(int i=1;i<=mkkk-2;i++){
		if(ans[i]>0)
			printf("Escaped in %d minute(s).\n",ans[i]);
		else
			cout<<"Trapped!\n";
	}
	if(ans[mkkk-1]>0)
		printf("Escaped in %d minute(s).",ans[mkkk-1]);
	else
		cout<<"Trapped!";//输出结果 
	return 0;
}
```



---

## 作者：wabcy (赞：2)

三维的BFS，看起来难，~~其实很水~~，注意一些细节，套上BFS的模板即可，附上代码~~（P党福音）~~：

```pascal
const //六个移动的方向，上下前后左右
  dx:array[1..6] of longint=(1,-1,0,0,0,0);
  dy:array[1..6] of longint=(0,0,1,-1,0,0);
  dz:array[1..6] of longint=(0,0,0,0,-1,1);
var
  a:array[0..270000,0..5] of longint; 
  map:array[0..50,0..50,0..50] of char; 
  c:array[0..50,0..50,0..50] of boolean; 
  i,j,k,x,y,z,x1,y1,z1,x2,y2,z2:longint;
  d:array[0..100,0..100,0..100] of longint;

procedure bfs;
var
  h,t,nx,ny,nz,i:longint;
begin
  h:=1; t:=1;
  fillchar(c,sizeof(c),true); //地图重置
  c[x1,y1,z1]:=false; //走过的点标记
  a[t,4]:=0; //步数
  a[1,1]:=x1; a[1,2]:=y1; a[1,3]:=z1;
  while t>=h do begin
    for i:=1 to 6 do
      begin
        nx:=a[h,1]+dx[i]; ny:=a[h,2]+dy[i]; nz:=a[h,3]+dz[i]; //移动
        if (nx>=1) and (nx<=x) and (ny>=1) and (ny<=y) and 
           (nz>=1) and (nz<=z) and (c[nx,ny,nz]) and (map[nx,ny,nz]<>'#') then //是否能走
             begin
               inc(t);
               a[t,1]:=nx; a[t,2]:=ny; a[t,3]:=nz; a[t,4]:=a[h,4]+1; //入队列，加步数
               c[nx,ny,nz]:=false;
               if (map[nx,ny,nz]='E') then //如果达到终点，输出
                 begin
                   writeln('Escaped in ',a[t,4],' minute(s).');
                   exit;
                 end;
             end;
      end;
    inc(h);
  end; 
  writeln('Trapped!'); //结束了也没到终点
end;
begin
  readln(x,y,z);  //读入
  while (x<>0) and (y<>0) and (z<>0) do begin
    for i:=1 to x do begin
      for j:=1 to y do begin
        for k:=1 to z do begin 
          read(map[i,j,k]);
          if map[i,j,k]='S' then begin x1:=i; y1:=j; z1:=k; end; //标记起点
        end;
        readln;
      end;
    end;
    bfs; //开始BFS
    readln(x,y,z); 
  end;
end.
```

---

## 作者：做梦想Peach (赞：1)

这一题应该是一道简单的`BFS`，虽然是三维的，但是我们可以当成二维的来想，这样就只是从四个方向变成六个方向了。

于是，我们就可以很轻松的写出方向增量
```cpp
int dx[10]={-1,1,0,0,0,0},
	dy[10]={0,0,-1,1,0,0},
	dz[10]={0,0,0,0,-1,1};
```
然后枚举所有可以到达的点就可以了。

但是要注意一点：**这一题是多组数据，所以每一次都要初始化`vis`（记录这个点是否走过）数组。**

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
struct Node {
    int x;
	int z;
	int y;
	int step;
}queue[1000010]; 
char c;
int dx[10]={-1,1,0,0,0,0},
	dy[10]={0,0,-1,1,0,0},
	dz[10]={0,0,0,0,-1,1};
int n,m,o,i,j,k,X1,Y1,Z1,X2,Y2,Z2; 
bool vis[110][110][110],map[110][110][110]; 
void bfs (int X1,int Y1,int Z1,int X2,int Y2,int Z2) {
    int nx,ny,nz,i,head=0,tail=1;
    queue[tail].x=X1;
    queue[tail].y=Y1;
    queue[tail].z=Z1;
	queue[tail].step=0;
	vis[X1][Y1][Z1]=true;
	while (head<tail) {
		head++;
		for (i=0;i<6;i++) {
			nx=queue[head].x+dx[i];
			ny=queue[head].y+dy[i];
			nz=queue[head].z+dz[i];
			if (nx>=1&&nx<=n&&ny>=1&&ny<=m&&nz>=1&&nz<=o&&vis[nx][ny][nz]==false&&map[nx][ny][nz]==true) {
				tail++;
				queue[tail].x=nx;
				queue[tail].y=ny;
				queue[tail].z=nz;
				queue[tail].step=queue[head].step+1;
				vis[nx][ny][nz]=true;
				if (nx==X2&&ny==Y2&&nz==Z2) {
					printf ("Escaped in %d minute(s).\n",queue[tail].step);//到达了终点，输出。
					return;
				}
			}
		}
	}
	puts ("Trapped!");
	return;
}
int main () {
	while (1) {
		for (i=0;i<1000010;i++)
			queue[i].step=0;
		memset (vis,false,sizeof (vis));//这一步很重要。 
		scanf ("%d%d%d",&n,&m,&o);
		if (n==0&&m==0&o==0) 
			return 0;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				for (k=1;k<=o;k++) {
					cin>>c;
					if (c=='.') map[i][j][k]=true;
					if (c=='#') map[i][j][k]=false;
					if (c=='S') {X1=i;Y1=j;Z1=k;map[i][j][k]=false;}
					if (c=='E') {X2=i;Y2=j;Z2=k;map[i][j][k]=true;} 
				}
		bfs (X1,Y1,Z1,X2,Y2,Z2);
	}
	return 0;
}
```

---

## 作者：玄月映宸s犇 (赞：1)

# 蒟蒻的题解啦


~~思路应该可以一眼望穿吧。。~~
### 那我就不解释啦
##### 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[101][101][101];
bool b[101][101][101];
int step[101][101][101];
int dx[6]= {0,0,0,0,1,-1};
int dy[6]= {0,0,1,-1,0,0};
int dz[6]= {1,-1,0,0,0,0};
struct node {
    int x,y,z,t;
};
int h,n,m,nx,ny,nz;
queue<node> q;
node fa,son,S,E;
void bfs() {
    q.push(S);
    b[S.x][S.y][S.z]=1;
    while(!q.empty()) {
        fa=q.front();
        q.pop();
        for(int i=0; i<6; i++) {
            nx=fa.x+dx[i];
            ny=fa.y+dy[i];
            nz=fa.z+dz[i];
            if(nx>=1&&nx<=h&&ny>=1&&ny<=n&&nz>=1&&nz<=m&&!b[nx][ny][nz]&&a[nx][ny][nz]!='#') {
                b[nx][ny][nz]=1;
                son.x=nx;
                son.y=ny;
                son.z=nz;
                son.t=fa.t+1;
                step[nx][ny][nz]=son.t;
                if(step[E.x][E.y][E.z]) {
                    while(!q.empty())q.pop();
                }
                q.push(son);
            }
        }
    }
}
int main() {
    while(1) {
        cin>>h>>n>>m;
        if(h==0&&n==0&&m==0)return 0;
        for(int i=1; i<=h; i++)
            for(int j=1; j<=n; j++)
                for(int k=1; k<=m; k++) {
                    cin>>a[i][j][k];
                    b[i][j][k]=0;
                    step[i][j][k]=0;
                    if(a[i][j][k]=='S') {
                        S.x=i;
                        S.y=j;
                        S.z=k;
                    }
                    if(a[i][j][k]=='E') {
                        E.x=i;
                        E.y=j;
                        E.z=k;
                    }
            }
        bfs();
        if(step[E.x][E.y][E.z]>0) {
            printf("Escaped in %d minute(s).\n",step[E.x][E.y][E.z]);

        } else printf("Trapped!\n")	;
    }
}
```
###### 溜了

---

## 作者：TLE_ooo (赞：1)



------------分割线镇楼------------


# 	三维的广搜板子，对于刚开始学习广搜的童鞋良心推荐
######    	（不过UVA这个oj是真的卡。。。）
##    	下面直接给代码吧，附带详细讲解
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][105][105],n,m,o;//数据较水，直接开三维数组 
char p;
int dx[15]={0,0,0,0,1,-1};/*三个方向的方向数组，一共上下左右前后六个拓展维度*/ 
int dy[15]={0,0,1,-1,0,0};
int dz[15]={1,-1,0,0,0,0};
struct	kk//结构体用于记录每个点的数据 
{
	int x;
	int y;
	int z;
	int step;
};
kk	q[1000005];//队列，拒绝STL 
bool check(int x,int y,int z)// 检验这个点是否越界，是否已经走过 
{
	if(x<1 || x>n || y<1 || y>m || z<1 || z>o)
		return 0;
	if(a[x][y][z])
		return 0;
	return 1;
}
void bfs(int x1,int y1,int z1,int x2,int y2,int z2)//bfs函数 
{
	int head=1,tail=1;//头尾指针初始化 
	bool flag=1;//是否有答案 
	q[1].x=x1;//第一个点入队 
	q[1].y=y1;
	q[1].z=z1;
	q[1].step=0;
	a[x1][y1][z1]=1;//地图标记 
	while(head<=tail)//广搜板子来了 
	{
		for(int i=0;i<6;i++)//循环六个方向 
		{
			int tx=q[head].x+dx[i];
			int ty=q[head].y+dy[i];
			int tz=q[head].z+dz[i];
			if(check(tx,ty,tz))//检验，check函数见上 
			{
				tail++;//符合条件，尾指针++
				 
				q[tail].x=tx;
				q[tail].y=ty;
				q[tail].z=tz;
				q[tail].step=q[head].step+1;//新的点入队 
				
				a[tx][ty][tz]=1;//地图标记 
				
				if(tx==x2 && ty==y2 && tz==z2)//检验是否为终点 
				{
					printf("Escaped in %d minute(s).\n",q[tail].step);
					flag=0;//存在答案，flag=false 
				}
			}
		}
		head++;//头指针++，切记切记，初学者很容易忘记导致死循环 
	}
	if(flag)
		printf("Trapped!\n");//无答案输出Trapped!
	return;
}
int main()
{
	int x1,y1,z1,x2,y2,z2;
	while(1)//无限循环处理多组数据 
	{
		memset(a,0,sizeof(a));//地图清零 
		
		cin>>n>>m>>o;//读入终点坐标 
		
		if(n==0 && m==0&& o==0)//循环结束条件 
			break;
		else
		{
			for(int i=1;i<=n;++i)
				for(int j=1;j<=m;++j)
					for(int k=1;k<=o;++k)
					{
						cin>>p;
						if(p=='.')
							a[i][j][k]=0;
						else if(p=='#')
							a[i][j][k]=1;
						else if(p=='S')//记录起点 
						{
							a[i][j][k]=0;
							x1=i;
							y1=j;
							z1=k;
						}
						else if(p=='E')//记录终点 
						{
							a[i][j][k]=0;
							x2=i;
							y2=j;
							z2=k;
						}
					}//读入地图 
			bfs(x1,y1,z1,x2,y2,z2);	//bfs（起点三个坐标，终点三个坐标）		
		}
	}	
	return 0;//完美结束！！！ 
}
```
	祝各位能学好bfs！！！

---

## 作者：zzx42121 (赞：0)

### 题意
三维迷宫，S为起点，E为终点，#为障碍物，.代表可走。走一步用时一分钟，求最小用时，或者永远走不出。
### 思路
bfs，开三维数组，做法和二维迷宫差不多。就是mov数组要多写两个方向。六个方向可走，不能走对角线。开了一个ans数组存步数，遇到终点就输出并清空队列跳出bfs的循环。

### AC代码（需要注意的写在注释里了）
```cpp
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
int a,b,c;
struct hhh{ 
	int x,y,z;
	hhh(int a,int b,int c):x(a),y(b),z(c){
	}
};//存坐标的结构体 
bool pdm[101][101][101];//判断是否走过 
char m[101][101][101]; 
int ans[101][101][101];//用来存步数的数组 
queue<hhh> q;
hhh qd(0,0,0),zd(0,0,0);//起点终点 
const int mov[6][3]={{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
int main()
{
	while(cin>>a>>b>>c)
	{
		if(a==b&&b==c&&a==0)
			return 0;
		memset(pdm,0,sizeof(pdm));
		memset(ans,0,sizeof(ans));//记得初始化 
		for(int i=1;i<=a;i++)
			for(int j=1;j<=b;j++)
				for(int k=1;k<=c;k++)
				{
					cin>>m[i][j][k];
					if(m[i][j][k]=='S')
					{
						qd.x=i;
						qd.y=j;
						qd.z=k;
					}
					if(m[i][j][k]=='E')//记录起点终点坐标 
					{
						zd.x=i;
						zd.y=j;
						zd.z=k;
					}
				}//输入 
		q.push(qd);
		while(!q.empty())
		{
			hhh ls=q.front();
			q.pop();
			for(int i=0;i<6;i++)
			{
				int xx=ls.x+mov[i][0];
				int yy=ls.y+mov[i][1];
				int zz=ls.z+mov[i][2];
				if(xx>0&&yy>0&&zz>0&&xx<=a&&yy<=b&&zz<=c&&!pdm[xx][yy][zz]&&m[xx][yy][zz]!='#')//不要写=='.'因为有可能是'S"或'E' 
				{
					q.push(hhh(xx,yy,zz));
					pdm[xx][yy][zz]=true; 
					ans[xx][yy][zz]=ans[ls.x][ls.y][ls.z]+1;
					if(xx==zd.x&&yy==zd.y&&zz==zd.z)//如果走到了终点 
					{
						cout<<"Escaped in "<<ans[zd.x][zd.y][zd.z]<<" minute(s)."<<endl;//注意格式 
						while(!q.empty())
							q.pop();//清空队列 
						break;
					}		
				}
			}
		}
		if(!ans[zd.x][zd.y][zd.z])//之前忘了判断，wa了好多次，眼瞎没看见多输出了trapped 。。 
			cout<<"Trapped!"<<endl;
	}
	return 0;
 } 
```


---

## 作者：Cesare (赞：0)

简单bfs。

就是三维的bfs，先预处理出起点终点和能走的点，标为1，然后将起点入队，开始

bfs，就是数组要开三维，判断变成三个而已。坑点在于多组数据需要清空队列、标记

数组，以及存储状态的数组需要开大一点，我最开始就是存状态的数组开小了，结果

WA了。

```cpp
#include <bits/stdc++.h>
#define re sort()
#define For(i,j,k) for(re int i=j;i<=k;i--)
using namespace std;
typedef long long ll;

bool flag=0;
char mp[210][210];
ll dx[]={ 1,-1,0,0,0,0 };
ll dy[]={ 0,0,1,-1,0,0 };
ll dz[]={ 0,0,0,0,1,-1 };
ll a,b,c,sx,sy,sz,ex,ey,ez,head=0,tail=1,mmp[210][210][210];

struct node {
    ll x,y,z,st;
}q[100010];

inline ll read() {
    ll x=0;bool f=0;char ch=getchar();
    for( ;!isdigit(ch); ch=getchar() )f^=( ch=='-' );
    for( ;isdigit(ch); ch=getchar() )x=( x<<3 )+( x<<1 )+( ch^48 );
    return f? -x: x;
}

int main() {
//	freopen("dungeon.out","w",stdout);
    while( cin>>a>>b>>c && a && b && c ) {
        memset( mmp,0,sizeof( mmp ) ) ;
        For( i,1,a )For( j,1,b )For( k,1,c ) {
            cin>>mp[i][j];
            if( mp[i][j]=='#' )mmp[i][j][k]=0;
            if( mp[i][j]=='.' )mmp[i][j][k]=1;
            if( mp[i][j]=='S' )mmp[i][j][k]=1,sx=i,sy=j,sz=k;
            if( mp[i][j]=='E' )mmp[i][j][k]=1,ex=i,ey=j,ez=k;
        }q[1].x=sx,q[1].y=sy,q[1].z=sz,q[1].st=0,head=0,tail=1;
        while( head<tail ) {
            head++;
            for(re int i=0;i<6;i++) {
                ll nx=q[head].x+dx[i],ny=q[head].y+dy[i],nz=q[head].z+dz[i];
                if( nx<=0 || nx>a || ny<=0 || ny>b || nz<=0 || nz>c )continue;
                if( mmp[nx][ny][nz] ) {
                    tail++;mmp[nx][ny][nz]=0;
                    q[tail].x=nx,q[tail].y=ny,q[tail].z=nz;q[tail].st=q[head].st+1;
                }if( nx==ex && ny==ey && nz==ez ) { flag=1;cout<<"Escaped in "<<q[tail].st<<" minute(s).";puts("");break; }
            }if(flag)break;
        }if(!flag)puts("Trapped!");flag=0;
    }return 0;
}
```

温馨提醒：不要抄题解。

---

## 作者：yxinh (赞：0)

赤裸裸的广搜题啊！！！

这道题与其他板子题最大的不同就是三维的。。。

所以考虑bfs:到一个点后，向各个能走的方向试探，如果没越界，也没走到不可以走的地方，就推入队列。

还有要注意的是队列中要有结构体记录路径，以便输出答案。。。





```
#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
int map[31][31][31],ans=0;
bool record[31][31][31];//记录有没有走过
int movx[]={0,1,0,-1,0,0,0};
int movy[]={0,0,-1,0,1,0,0};
int movz[]={0,0,0,0,0,1,-1};//记录各个方向的数组
int a,b,h;//长，宽，高
struct MOV
{
	int x,y,z,step;
};
void bfs(int sx,int sy,int sz,int ex,int ey,int ez)
{
	queue<MOV> q;
	MOV n;
	n.x=sx;
	n.y=sy;
	n.z=sz;
	n.step=0;
	q.push(n);
	while(!q.empty())
	{
		for(int i=1;i<=6;i++)
		{
		    n=q.front();
			if(n.x+movx[i]>=1 && n.y+movy[i]>=1 && n.z+movz[i]>=1 && n.x+movx[i]<=a && n.y+movy[i]<=b && n.z+movz[i]<=h && map[n.x+movx[i]][n.y+movy[i]][n.z+movz[i]]==0 && record[n.x+movx[i]][n.y+movy[i]][n.z+movz[i]]==false)//一堆的限制性条件。。。
			{
				n.x+=movx[i];
				n.y+=movy[i];
				n.z+=movz[i];
				n.step++;
				record[n.x][n.y][n.z]=true;
				if(n.x==ex && n.y==ey && n.z==ez)//到达终点
				{
					cout<<"Escaped in "<<n.step<<" minute(s)."<<endl;//输出答案
					return;
				}
				else
				q.push(n);//否则推进队列
			}
		} 
		q.pop();
	}
	cout<<"Trapped!"<<endl;//队列空了说明走不到
}
int main()
{
	int sx,sy,sz,ex,ey,ez;
	while(true)
	{
		cin>>h>>b>>a;
		if(h==0 && b==0 && a==0)
		return 0;
	    memset(map,-1,sizeof(map));//-1表示不能走
	    memset(record,false,sizeof(record));
		for(int i=1;i<=h;i++)
		{
			for(int j=1;j<=b;j++)
			{
				for(int k=1;k<=a;k++)
				{
					char tmp;
					cin>>tmp;
					if(tmp=='.')
					map[k][j][i]=0;//能走
					else if(tmp=='#')
					map[k][j][i]=1;//不能走
					else if(tmp=='S')
					{
						sx=k;
						sy=j;
						sz=i;
						record[k][j][i]=true;
						map[k][j][i]=0;//记录起点
					}
					else if(tmp=='E')
					{
						ex=k;
						ey=j;
						ez=i;
						map[k][j][i]=0;//记录终点
					}
				}
			}
		}
		bfs(sx,sy,sz,ex,ey,ez);
	}
}
```

---

## 作者：羽儇 (赞：0)

常规bfs题
```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define ok(x,y,z) (x>=1&&x<=pile&&y>=1&&y<=len&&z<=wid&&z>=1)//判断是否越界
const int maxn = 31;
using namespace std;
struct node 
{
	int p,l,w,now;//now是指到这一步，花了多少步，由于广搜先到的，一定步数最小
	node(int p,int l,int w,int now):p(p),l(l),w(w),now(now){};//方便快速重新定义个结构体进进队
};
char G[maxn][maxn][maxn];
int e1,e2,e3,pile,len,wid,s1,s2,s3;
int disx[] = {1,-1,0,0,0,0};
int disy[] = {0,0,1,-1,0,0};
int disz[] = {0,0,0,0,-1,1};
bool vis[maxn][maxn][maxn];
bool bfs()
{
	queue<node>q;
	q.push(node(s1,s2,s3,0));//详见函数
	while(!q.empty())
	{
		node tmp = q.front();
		q.pop();
		if(tmp.p == e1 && tmp.l == e2 && tmp.w == e3)//到终点惹，直接输出即可qwq
		{
			printf("Escaped in %d minute(s).\n",tmp.now);//不用count，用printf写方便些
			return true;
		}
		for(int i = 0 ; i <= 5; i++)
		{
			if(ok(tmp.p+disx[i],tmp.l+disy[i],tmp.w+disz[i])&&G[disx[i]+tmp.p][disy[i]+tmp.l][disz[i]+tmp.w]!='#'&&!vis[disx[i]+tmp.p][disy[i]+tmp.l][disz[i]+tmp.w])//先判是否越界，再判是否有障碍，最后判是否访问过惹QAQ
			{
				q.push(node(tmp.p+disx[i],tmp.l+disy[i],tmp.w+disz[i],tmp.now+1));
				vis[disx[i]+tmp.p][disy[i]+tmp.l][disz[i]+tmp.w]=true;
			}
		}
	}
	return false;
}
int main()
{
	while(scanf("%d%d%d",&pile,&len,&wid)&&pile != 0)
	{
		ans=0x7fffffff;
	    memset(G,'.',sizeof(G));
	    memset(vis,false,sizeof(vis));
	    for(int i = 1 ; i <= pile ; i++)
	    {
		    for(int j = 1 ; j <= len ; j++)
		    {
			    for(int k = 1 ; k<=wid ; k++)
			    {
				    cin>>G[i][j][k];
				    if(G[i][j][k] == 'S')s1 = i,s2 = j,s3 = k;
				    else if(G[i][j][k] == 'E')e1 = i,e2 = j,e3 = k;//常规输入
			    }
		    }
	    }
	    if(!bfs())puts("Trapped!");
	}
	return 0;
}
```

---

