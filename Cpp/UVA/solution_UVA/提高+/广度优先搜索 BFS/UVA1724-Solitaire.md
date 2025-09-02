# Solitaire

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=859&page=show_problem&problem=4862

[PDF](https://uva.onlinejudge.org/external/17/p1724.pdf)

## 样例 #1

### 输入

```
4 4 4 5 5 4 6 5
2 4 3 3 3 6 4 6```

### 输出

```
YES```

# 题解

## 作者：yuruilin2026 (赞：4)

## 一些闲话：
有的时候我们应该对自己有信心，即使不会双向广搜也能 AC。\
给大家隆重介绍我们今天的主角：双向深搜。\
~~（没错，还是双向）。~~
## 题意：
$8 \times 8$ 的棋盘上有 $4$ 个完全相同的棋子。\
对于每个棋子，它能移动到旁边的四个位置。\
若某个位置上已经有一个棋子了，那就可以跳过这个棋子，相当于走两步。\
若跳跃的终点已经有了棋子，则不能跳跃。\
求一个给定的棋局 $8$ 步之后是否可以形成另外一种给定的棋局。\
（棋子都在相同的位置就是相同的棋局）。
## 做法：
由于双向广搜对喜欢深搜的同学有点不友好（比如说我）。\
所以说双向深搜应运而生（其实是自己菜）。\
双向广搜的思路是先把从起点四步可达的节点标记，再判断从终点四步是否可达已经标记过的节点。\
深搜也能做到标记，也能做到判断可达。\
建立一个八维数组 $vis1_{x1,y1,x2,y2,x3,y3,x4,y4}$，用于标记是否能搜到。\
当然，如果使用 bool 类型会莫名其妙 WA。\
这是因为深搜不能保证搜到的就是最短路径，可能会导致真正最短的被剪掉。\
比如说第一次走到这里时走了 $3$ 步，第二次只走了 $2$ 步，但在第一次是导致节点被标记，所以无法正确扩展。\
实际上应该使用 int 类型，记录最短路径，像这样：

```cpp
if(vis2[c[1].x][c[1].y][c[2].x][c[2].y][c[3].x][c[3].y][c[4].x][c[4].y] <= step) return 0;
for(int i = 1;i <= 4;++i){
    for(int j = 1;j <= 4;++j){
        if(i == j) continue;
        for(int k = 1;k <= 4;++k){
            if(i == k || j == k) continue;
            for(int l = 1;l <= 4;++l){
                if(i == l || j == l || k == l) continue;
                vis2[c[i].x][c[i].y][c[j].x][c[j].y][c[k].x][c[k].y][c[l].x][c[l].y] = step;
            }
        }
    }
}
```
这里 $c$ 存储的是棋子的坐标，全排列是因为棋子是相同的，要将所有可以代表这个棋局的状态都设置为当前步数。\
基本就完了，剩下看代码吧，有注释：
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int mp1[10][10],mp2[10][10];//从起点，终点分别出发的两张地图 
int fx[5] = {0,1,0,-1,0},fy[5] = {0,0,1,0,-1};//方向 
int vis1[9][9][9][9][9][9][9][9];//标记（去重） 
int vis2[9][9][9][9][9][9][9][9];//去重 
struct ppp{
	int x;
	int y;
}a[6],b[6];
void sou1(int step){
	if(step >= 6) return;//超过5步不搜索 
	ppp c[6] = {};
	int cnt = 0;
	for(int i = 1;i <= 8;++i){
		for(int j = 1;j <= 8;++j){
			if(mp1[i][j] == 1){//mp1[i][j] == 1 代表棋子 
				c[++cnt].x = i;//存贮棋子行 
				c[cnt].y = j;//存贮棋子列 
			}
		}
	}
	if(vis1[c[1].x][c[1].y][c[2].x][c[2].y][c[3].x][c[3].y][c[4].x][c[4].y] <= step) return;//搜过 
	for(int i = 1;i <= 4;++i){
		for(int j = 1;j <= 4;++j){
			if(i == j) continue;
			for(int k = 1;k <= 4;++k){
				if(i == k || j == k) continue;
				for(int l = 1;l <= 4;++l){
					if(i == l || j == l || k == l) continue;
					vis1[c[i].x][c[i].y][c[j].x][c[j].y][c[k].x][c[k].y][c[l].x][c[l].y] = step;
					//全排列将所有情况考虑到才能正确去重 
				}
			}
		}
	}
	for(int i = 1;i <= 4;++i){//移动哪一个棋子 
		for(int j = 1;j <= 4;++j){//枚举方向 
			int xx = c[i].x + fx[j],yy = c[i].y + fy[j];
			if(xx <= 0 || xx >= 9 || yy <= 0 || yy >= 9){
				continue;
			} 
			if(mp1[xx][yy] == 0){//下一步是空地 
				swap(mp1[xx][yy],mp1[c[i].x][c[i].y]);
				sou1(step+1);
				swap(mp1[xx][yy],mp1[c[i].x][c[i].y]);//回溯 
			}
			//下一步是棋子且跳过去是空地
			//跳过去就相当于走两步 
			else if(mp1[xx+fx[j]][yy+fy[j]] == 0 && xx+fx[j] >= 1 && xx+fx[j] <= 8 && yy+fy[j] >= 1 && yy+fy[j] <= 8){
				swap(mp1[xx+fx[j]][yy+fy[j]],mp1[c[i].x][c[i].y]);
				sou1(step+1);
				swap(mp1[xx+fx[j]][yy+fy[j]],mp1[c[i].x][c[i].y]);//回溯 
			}
		}
	}
	return;
}
bool sou2(int step){
	if(step >= 6) return 0;
	ppp c[6];
	int cnt = 0;
	for(int i = 1;i <= 8;++i){
		for(int j = 1;j <= 8;++j){
			if(mp2[i][j] == 1){
				c[++cnt].x = i;
				c[cnt].y = j;
			}
		}
	}
	//if(cnt != 4) return 0;
	if(vis2[c[1].x][c[1].y][c[2].x][c[2].y][c[3].x][c[3].y][c[4].x][c[4].y] <= step) return 0;
	for(int i = 1;i <= 4;++i){
		for(int j = 1;j <= 4;++j){
			if(i == j) continue;
			for(int k = 1;k <= 4;++k){
				if(i == k || j == k) continue;
				for(int l = 1;l <= 4;++l){
					if(i == l || j == l || k == l) continue;
					vis2[c[i].x][c[i].y][c[j].x][c[j].y][c[k].x][c[k].y][c[l].x][c[l].y] = step;
				}
			}
		}
	}
	if(vis1[c[1].x][c[1].y][c[2].x][c[2].y][c[3].x][c[3].y][c[4].x][c[4].y] != vis1[0][0][0][0][0][0][0][0]){
		return 1;//如果遇到了之前从起点开始搜过的地图，返回搜到了 
	}
	for(int i = 1;i <= 4;++i){
		for(int j = 1;j <= 4;++j){
			int xx = c[i].x + fx[j],yy = c[i].y + fy[j];
			if(xx <= 0 || xx >= 9 || yy <= 0 || yy >= 9){
				continue;
			} 
			if(mp2[xx][yy] == 0){
				swap(mp2[xx][yy],mp2[c[i].x][c[i].y]);
				if(sou2(step+1)){//如果下一个状态能搜到 
					swap(mp2[xx][yy],mp2[c[i].x][c[i].y]);//标记搜到了 
					return 1;
				}
				swap(mp2[xx][yy],mp2[c[i].x][c[i].y]);
			}
			else if(mp2[xx+fx[j]][yy+fy[j]] == 0 && xx+fx[j] >= 1 && xx+fx[j] <= 8 && yy+fy[j] >= 1 && yy+fy[j] <= 8){
				swap(mp2[xx+fx[j]][yy+fy[j]],mp2[c[i].x][c[i].y]);
				if(sou2(step+1)){
					swap(mp2[xx+fx[j]][yy+fy[j]],mp2[c[i].x][c[i].y]);
					return 1;
				}
				swap(mp2[xx+fx[j]][yy+fy[j]],mp2[c[i].x][c[i].y]);
			}
		}
	}
	return 0;
}
int main(){
	cin.tie(0),cout.tie(0);
	while(1){
		memset(vis1,0x3f,sizeof(vis1));//初始化 
		memset(vis2,0x3f,sizeof(vis2));
		memset(mp1,0,sizeof(mp1));
		memset(mp2,0,sizeof(mp2));
		for(int i = 1;i <= 4;i++){
			if(!(cin >> a[i].x && cin >> a[i].y)) return 0;
			mp1[a[i].x][a[i].y] = 1;//初始化第一张地图 
		}
		for(int i = 1;i <= 4;i++){
			cin >> b[i].x >> b[i].y;
			mp2[b[i].x][b[i].y] = 1;//初始化第二张地图
		}
		sou1(1);//先把从起点四步可达的节点标记 
		if(sou2(1) == 0){//判断从终点四步是否可达已经标记过的节点 
			cout << "NO" << endl;
		}
		else{
			cout << "YES" << endl; 
		}
	}
	return 0;
}
```

---

## 作者：zyx912 (赞：4)

## 这道题原题描述的很好
大家来看一下
[HDU1401 Solitaire](https://cn.vjudge.net/problem/HDU-1401)
下面直接看一下代码吧
```cpp
#include<bits/stdc++.h>
using namespace std;
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
char mark[8][8][8][8][8][8][8][8];
struct point{
	int x,y;
}; 
struct node{
	point p[4];
	int step;
}s,e;
bool cmp(point a,point b){
	if(a.x==b.x) return a.y<b.y;
	return a.x<b.x;
}
int judge(node &k,int biao,int fx,int cishu){
	if(cishu==0){
		if(k.step>=4) return 0;
		k.step++;
	}
	int xx=(k.p[biao].x+=dx[fx]);
	int yy=(k.p[biao].y+=dy[fx]);
	if(xx<=0||yy<=0||xx>8||yy>8) return 0;
	for(int i=0;i<4;i++){
		if(i==biao){
			continue;
		}
		if(xx==k.p[i].x&&yy==k.p[i].y){
			if(cishu==0){
				return judge (k,biao,fx,cishu+1);
			}
			else{
				return 0;
			}
		}
	}
	sort(k.p,k.p+4,cmp);
	return 1;
}
int bfs(){
	queue<node>fr;
	queue<node>ba;
	sort(s.p,s.p+4,cmp);
	sort(e.p,e.p+4,cmp);
	fr.push(s);
	ba.push(e);
	mark[s.p[0].x][s.p[0].y][s.p[1].x][s.p[1].y][s.p[2].x][s.p[2].y][s.p[3].x][s.p[3].y]='1';
	mark[e.p[0].x][e.p[0].y][e.p[1].x][e.p[1].y][e.p[2].x][e.p[2].y][e.p[3].x][e.p[3].y]='2';
	while(!fr.empty()||!ba.empty()){
		if(!fr.empty()){
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){		
					node k=fr.front();
					if(judge(k,i,j,0)){
						if(mark[k.p[0].x][k.p[0].y][k.p[1].x][k.p[1].y][k.p[2].x][k.p[2].y][k.p[3].x][k.p[3].y]=='\0'){
							fr.push(k);
						}
						else if(mark[k.p[0].x][k.p[0].y][k.p[1].x][k.p[1].y][k.p[2].x][k.p[2].y][k.p[3].x][k.p[3].y]=='2'){
							return 1;
						}
						mark[k.p[0].x][k.p[0].y][k.p[1].x][k.p[1].y][k.p[2].x][k.p[2].y][k.p[3].x][k.p[3].y]='1';
					}
				}
			}
			fr.pop();
		}
		if(!ba.empty()){
			for(int i=0;i<4;i++){
				for(int j=0;j<4;j++){
					node k=ba.front();
					if(judge(k,i,j,0)){
						if(mark[k.p[0].x][k.p[0].y][k.p[1].x][k.p[1].y][k.p[2].x][k.p[2].y][k.p[3].x][k.p[3].y]=='\0'){
							ba.push(k);
						}
						else if(mark[k.p[0].x][k.p[0].y][k.p[1].x][k.p[1].y][k.p[2].x][k.p[2].y][k.p[3].x][k.p[3].y]=='1'){
							return 1;
						}
						mark[k.p[0].x][k.p[0].y][k.p[1].x][k.p[1].y][k.p[2].x][k.p[2].y][k.p[3].x][k.p[3].y]='2';
					}
				}
			}
			ba.pop();
		}
	}
	return 0;
}
int main(){
	int x,y;
	while(scanf("%d%d",&x,&y)!=EOF){
		memset(mark,0,sizeof(mark));
		s.p[0].x=x;
		s.p[0].y=y;
	for(int i=1;i<4;i++){
		scanf("%d%d",&s.p[i].x,&s.p[i].y);
	}
	for(int i=0;i<4;i++){
		scanf("%d%d",&e.p[i].x,&e.p[i].y);
	}
	s.step=0;
	e.step=0;
	if(bfs()){
		cout<<"YES"<<endl;
	}
	else{
		cout<<"NO"<<endl;
		}
	}
	return 0;
}
```
我在vjudge上提交成功了，但我没有UVA账号，也绑不上去，于是有大佬的话帮我试一下QAQ！！！

最后@管理员，这道题还没有题解啊！！！求求您大发慈心放我过了吧[可怜][可怜][可怜]

---

## 作者：SuperCowHorse (赞：3)

### 题目大意
一个 $8$ $\times$ $8$ 的棋盘上有 $4$ 个棋子，给出起点与终点坐标，求 $8$ 步之内能否走到终点。
### 题目分析
一道 bfs 搜索水题。

因为题目有多组数据，所以我们先进行初始化，再进行搜索。初始化很重要！不加初始化过不了。

下面是不加初始化的后果：

![](https://cdn.luogu.com.cn/upload/image_hosting/lgvcmtzh.png)
``` cpp
memset(vis,0,sizeof(vis));//标记有没有到过某状态（8个一起）
memset(f,0,sizeof(f));//标记棋子终点
a.step=0;//开始步数为0
```
输入完后就是进行搜索。

枚举每一个棋子，并枚举四个方向，进行标记，向四周扩展，并作以下判断：
1. 有无到达边界？
1. $4$ 个棋子此时状态有无到达过？
1. 可不可以跳子？
1. 有无到达终点？
``` cpp
void sign(node tmp){//标记此时四个棋子的状态
	vis[tmp.x[1]][tmp.y[1]][tmp.x[2]][tmp.y[2]][tmp.x[3]][tmp.y[3]][tmp.x[4]][tmp.y[4]]=1;
}
bool judge1(node tmp){//判断有无越界、状态有无到达过
	for(int i=1;i<=4;++i)
		if(tmp.x[i]<0||tmp.x[i]>7||tmp.y[i]<0||tmp.y[i]>7)
			return 1;
	return vis[tmp.x[1]][tmp.y[1]][tmp.x[2]][tmp.y[2]][tmp.x[3]][tmp.y[3]][tmp.x[4]][tmp.y[4]];
}
bool judge2(node tmp,int i){//判断能否跳子
	for(int j=1;j<=4;++j)
		if(i!=j)
			if(tmp.x[i]==tmp.x[j]&&tmp.y[i]==tmp.y[j])
				return 1;
	return 0;
}
bool judge3(node tmp){//判断是否到达终点
	for(int i=1;i<=4;i++)
		if(!f[tmp.x[i]][tmp.y[i]])
			return 0;
	return 1;
}
bool bfs(){
	queue<node>q;
	sign(a);q.push(a);
	while(!q.empty()){
		a=q.front();q.pop();
		if(a.step>=8) return 0;//步数大于等于8直接return
		for(int i=1;i<=4;++i)
			for(int j=1;j<=4;++j){
				tmp=a;++tmp.step;
				tmp.x[i]+=dx[j];//向四周扩展
				tmp.y[i]+=dy[j];
				if(judge1(tmp)) continue;//若超过边界
				if(judge2(tmp,i)){//若可以跳子
					tmp.x[i]+=dx[j];
					tmp.y[i]+=dy[j];
					if(judge1(tmp)||judge2(tmp,i)) continue;//如果越界或后面还有棋子
				}
				if(judge3(tmp)) return 1;//到达终点
				sign(tmp);q.push(tmp);
			}
	}
	return 0;
}
```
贴上无注释代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x[5],y[5],step;
}a,tmp;
int x,y;
bool vis[8][8][8][8][8][8][8][8],f[8][8];
const int dx[]={0,-1,0,1,0};
const int dy[]={0,0,1,0,-1};
void sign(node tmp){
	vis[tmp.x[1]][tmp.y[1]][tmp.x[2]][tmp.y[2]][tmp.x[3]][tmp.y[3]][tmp.x[4]][tmp.y[4]]=1;
}
bool judge1(node tmp){
	for(int i=1;i<=4;++i)
		if(tmp.x[i]<0||tmp.x[i]>7||tmp.y[i]<0||tmp.y[i]>7)
			return 1;
	return vis[tmp.x[1]][tmp.y[1]][tmp.x[2]][tmp.y[2]][tmp.x[3]][tmp.y[3]][tmp.x[4]][tmp.y[4]];
}
bool judge2(node tmp,int i){
	for(int j=1;j<=4;++j)
		if(i!=j)
			if(tmp.x[i]==tmp.x[j]&&tmp.y[i]==tmp.y[j])
				return 1;
	return 0;
}
bool judge3(node tmp){
	for(int i=1;i<=4;i++)
		if(!f[tmp.x[i]][tmp.y[i]])
			return 0;
	return 1;
}
bool bfs(){
	queue<node>q;
	sign(a);q.push(a);
	while(!q.empty()){
		a=q.front();q.pop();
		if(a.step>=8) return 0;
		for(int i=1;i<=4;++i)
			for(int j=1;j<=4;++j){
				tmp=a;++tmp.step;
				tmp.x[i]+=dx[j];
				tmp.y[i]+=dy[j];
				if(judge1(tmp)) continue;
				if(judge2(tmp,i)){
					tmp.x[i]+=dx[j];
					tmp.y[i]+=dy[j];
					if(judge1(tmp)||judge2(tmp,i)) continue;
				}
				if(judge3(tmp)) return 1;
				sign(tmp);q.push(tmp);
			}
	}
	return 0;
}
int main(){
	while(cin>>a.x[1]>>a.y[1]){
		memset(vis,0,sizeof(vis));
		memset(f,0,sizeof(f));
		a.step=0;
		for(int i=2;i<=4;++i)
			scanf("%d%d",&a.x[i],&a.y[i]);
		for(int i=1;i<=4;++i)
			--a.x[i],--a.y[i];
		for(int i=1,u,v;i<=4;++i){
			scanf("%d%d",&u,&v);
			f[--u][--v]=1;
		}
		if(bfs())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
```

---

## 作者：meifan666 (赞：2)

### 题目大意
在一个
$8\times8$
的棋盘里有
$4$
个棋子，给定初始状态与目标状态，问能否在
$8$
步以内实现。
### 思路
最朴素的广搜很容易想到，从起点走，枚举所有情况，看能否到终点，但理论上复杂度为
$O((x\times y)^n)$，其中
$x$
为棋子数，应该是
$4$；$y$
为可走的方向，应该是
$4$；$n$
为走的次数，应该是
$8$。显然会超时。

于是我们可以想到用**折半搜索**的方法解决，分别从起点和终点走，各自走最多
$4$
步，并测试是否有一种情况能使二者重合，若可以则能在
$8$
步内到达，否则不行。如此，我们就能把复杂度降低至
$O((x\times y)^n\times t)$，其中
$x$
为棋子数，应该是
$4$；$y$
为可走的方向，应该是
$4$；$n$
为走的次数，应该是
$4$；$t$
为搜几次，要搜起点和终点
$2$
个点，所以应该是
$2$。如此，我们就避免了超时。

值得一提的是在搜索过程中要标记每个棋子的位置，这样就能处理出现跳过棋子的情况了。

最后，注意多测的清空。下面贴上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
bool ok;
int x9,y9;
bool vis[8][8][8][8][8][8][8][8];
int waya[5]={1,-1,0,0};
int wayb[5]={0,0,1,-1};
struct chess{
	int x,y;
}aaa[5],bbb[5];
bool check(int xi,int yi,int opt){
	if(xi<0||xi>7||yi<0||yi>7)return 0;
	if(opt==1){
		for(int i=1;i<=4;i++){
			if(aaa[i].x==xi&&aaa[i].y==yi)return 0;
		}
	}else{
		for(int i=1;i<=4;i++){
			if(bbb[i].x==xi&&bbb[i].y==yi)return 0;
		}
	}
	return 1;
}
void join(){
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(i==j)continue;
			for(int k=1;k<=4;k++){
				if(i==k||j==k)continue;
				for(int l=1;l<=4;l++){
					if(i==l||j==l||k==l)continue;
					vis[aaa[i].x][aaa[i].y][aaa[j].x][aaa[j].y][aaa[k].x][aaa[k].y][aaa[l].x][aaa[l].y]=1;
				}
			}
		}
	}
}
void DFS1(int deep){
	join();
	if(deep>4)return;
	for(int k=1;k<=4;k++){
		for(int i=0;i<4;i++){
			int xx=waya[i]+aaa[k].x,yy=wayb[i]+aaa[k].y;
			for(int j=1;j<=4;j++){
				if(aaa[j].x==xx&&aaa[j].y==yy){
					xx+=waya[i];
					yy+=wayb[i];
					break;
				}
			}
			if(check(xx,yy,1)){
				int tx=aaa[k].x,ty=aaa[k].y;
				aaa[k].x=xx,aaa[k].y=yy;
				DFS1(deep+1);
				aaa[k].x=tx,aaa[k].y=ty;
			}
		}
	}
}
void DFS2(int deep){
	if(ok)return;
	if(vis[bbb[1].x][bbb[1].y][bbb[2].x][bbb[2].y][bbb[3].x][bbb[3].y][bbb[4].x][bbb[4].y]){
		ok=1;
		return;
	}
	if(deep>4)return;
	for(int k=1;k<=4;k++){
		for(int i=0;i<4;i++){
			int xx=waya[i]+bbb[k].x,yy=wayb[i]+bbb[k].y;
			for(int j=1;j<=4;j++){
				if(bbb[j].x==xx&&bbb[j].y==yy){
					xx+=waya[i];
					yy+=wayb[i];
					break;
				}
			}
			if(check(xx,yy,2)){
				int tx=bbb[k].x,ty=bbb[k].y;
				bbb[k].x=xx,bbb[k].y=yy;
				DFS2(deep+1);
				bbb[k].x=tx,bbb[k].y=ty;
			}
		}
	}
}
signed main(){
	while(cin>>x9>>y9){
		memset(vis,0,sizeof(vis));
		memset(aaa,-1,sizeof(aaa));
		memset(bbb,-1,sizeof(bbb));
		ok=0;
		aaa[1].x=x9-1,aaa[1].y=y9-1;
		for(int i=2;i<=4;i++){
			cin>>aaa[i].x>>aaa[i].y;
			aaa[i].x--,aaa[i].y--;
		}
		DFS1(1);
		for(int i=1;i<=4;i++){
			cin>>bbb[i].x>>bbb[i].y;
			bbb[i].x--,bbb[i].y--;
		}
		DFS2(1);
		if(!ok)cout<<"NO"<<'\n';
		else cout<<"YES"<<'\n';
	}
	return 0;
}
```

---

## 作者：Silence_water (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/UVA1724)


------------

### Description

> 有四个棋子，可以跳过 $1$ 个棋子，问能否在 $8$ 步内走到目标状态


------------

### Analyse

- 这道题询问能否在 $8$ 步内走到，所以我们要用到 BFS。这里我使用的是单向宽搜。


------------

### Pay attention

1. 四个棋子一样，因此只要**每个终点都有棋子**就算到达。

2. 为了防止出现重复的状态，需要一个八维数组 $mark$ 来标记该状态是否已经存在。

3. 最多只能跳过一个棋子，故当跳过一个仍不满足条件的状态不需要储存。

4. 为了节省空间，我选择将每个坐标的下标从 $0$ 开始，因此在代码中坐标减 $1$。

5. 多组数据题，记得清空数组。


------------

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int d[4][2]={{0,1},{0,-1},{1,0},{-1,0}};//4个方向 
struct p
{
	int x[4],y[4],step;
}st;
bool final[8][8];//终点坐标 
bool mark[8][8][8][8][8][8][8][8];
void store(p a)
{
	mark[a.x[0]][a.y[0]][a.x[1]][a.y[1]][a.x[2]][a.y[2]][a.x[3]][a.y[3]]=true;
}//存储状态 
bool stop(p a,int to)
{
	for(int i=0;i<4;i++)
	{
		if(i==to)continue;
		if(a.x[to]==a.x[i]&&a.y[to]==a.y[i])return true;
	}
	return false;
}//是否有棋子挡住 
bool check(p a)
{
	for(int i=0;i<4;i++)
		if(a.x[i]<0||a.x[i]>7||a.y[i]<0||a.y[i]>7)return false;
	if(mark[a.x[0]][a.y[0]][a.x[1]][a.y[1]][a.x[2]][a.y[2]][a.x[3]][a.y[3]])return false;
	return true;
}//当前坐标是否越界、当前状态是否已存在 
bool win(p a)
{
	for(int i=0;i<4;i++)
		if(!final[a.x[i]][a.y[i]])return false;
	return true;
}//是否到达终点 
bool bfs()
{
	queue<p> q;
	store(st);
	q.push(st);
	while(!q.empty())
	{
		st=q.front();
		q.pop();
		if(st.step>7)return false;//都大于7步了还走啥 
		for(int i=0;i<4;i++)//枚举4个棋子 
		{
			for(int j=0;j<4;j++)//枚举4个方向 
			{
				p next=st;
				next.x[i]+=d[j][0],next.y[i]+=d[j][1],next.step++;
				if(!check(next))continue;
				if(stop(next,i))//有棋子挡住 
				{
					next.x[i]+=d[j][0],next.y[i]+=d[j][1];
					if(!check(next)||stop(next,i))continue;//仍被挡住或越界 
				}
				if(win(next))return true;
				store(next);
				q.push(next);
			}
		}
	}
	return false;
}
int main()
{
	while(~scanf("%d%d",&st.x[0],&st.y[0]))//先读入1组 
	{
		memset(mark,false,sizeof(mark));
		memset(final,false,sizeof(final));
		st.x[0]--,st.y[0]--;
		for(int i=1;i<4;i++)//再读入3组 
		{
			scanf("%d%d",&st.x[i],&st.y[i]);
			st.x[i]--,st.y[i]--;
		}
		st.step=0;
		for(int i=0;i<4;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			x--,y--;
			final[x][y]=true;
		}
		if(bfs())printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


------------
谢谢观看！

---

## 作者：封禁用户 (赞：1)

本题数据过水，导致普通的 bfs 也可以通过本题。

## 思路

如果直接 bfs，复杂度就是 $\mathcal{O}(16^8)$（走 $8$ 步，每步有 $16$ 种选择），在正常数据下会 TLE。所以考虑采用更高效的双向广搜。

那怎么双向广搜呢？我们可以从起点和终点交替搜索，标记棋子走过的位置。如果发现重复了，就说明起点出发的这条路径就能和终点接上。如果超过 $8$ 步还没接上就是无解了。

讲的不好，细节不懂可以看我代码里的注释。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
struct Chess{
	int x,y;
};
struct ChessBoard{
	Chess a[5];
}s,t;
const int N=9;
bool viss[N][N][N][N][N][N][N][N];
bool vist[N][N][N][N][N][N][N][N];
void fzs(ChessBoard X){//对s赋值（全排列）
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(i==j)continue;
			for(int k=1;k<=4;k++){
				if(i==k||j==k)continue;
				for(int l=1;l<=4;l++){
					if(l==i||l==j||l==k)continue;
					viss[X.a[i].x][X.a[i].y][X.a[j].x][X.a[j].y][X.a[k].x][X.a[k].y][X.a[l].x][X.a[l].y]=1;
				}
			}
		}
	}
}
void fzt(ChessBoard X){//对t赋值（全排列）
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(i==j)continue;
			for(int k=1;k<=4;k++){
				if(i==k||j==k)continue;
				for(int l=1;l<=4;l++){
					if(l==i||l==j||l==k)continue;
					vist[X.a[i].x][X.a[i].y][X.a[j].x][X.a[j].y][X.a[k].x][X.a[k].y][X.a[l].x][X.a[l].y]=1;
				}
			}
		}
	}
}
//是否可以跳子 
bool jump_over(ChessBoard x,int y,int z){//移动第y颗棋子，方向为z 
	int xx=x.a[y].x+dx[z];
	int yy=x.a[y].y+dy[z];
	for(int i=1;i<=4;++i){
		if(i==y){
			continue;
		}
		if(x.a[i].x==xx&&x.a[i].y==yy){
			return 1;
		}
	}
	return 0;
}
bool wrong(ChessBoard x,int y){//移动的第y颗棋子 
	int xx=x.a[y].x;
	int yy=x.a[y].y;
	for(int i=1;i<=4;++i){
		if(i==y){
			continue;
		}
		if(x.a[i].x==xx&&x.a[i].y==yy){
			return 1;//跳到另一个棋子上了 
		}
	}
	return 0;
}
void bfs(ChessBoard start,ChessBoard end){//双向广搜 
	int time=0;
	queue<ChessBoard> qs,qt;//起始\终止 
//	viss[start.a[1].x][start.a[1].y][start.a[2].x][start.a[2].y]
//		[start.a[3].x][start.a[3].y][start.a[4].x][start.a[4].y]=1;
	fzs(start);
//	vist[end.a[1].x][end.a[1].y][end.a[2].x][end.a[2].y]
//		[end.a[3].x][end.a[3].y][end.a[4].x][end.a[4].y]=1;
	fzt(end);
	qs.push(start);
	qt.push(end);
	while(!qs.empty()&&!qt.empty()){
		++time;
		if(time>8){//超过8步了
			cout<<"NO"<<endl;
			return ;
		}
		if(qs.size()>qt.size()){
			int w=qt.size();
			while(w--){
				ChessBoard tmp=qt.front();
				qt.pop();
				for(int i=1;i<=4;++i){//第i颗棋子 
					for(int j=0;j<4;++j){//j是方向 
						int xx=dx[j];
						int yy=dy[j];
						if(jump_over(tmp,i,j)){
							xx*=2,yy*=2;
						}
						ChessBoard to=tmp;
						to.a[i].x+=xx,to.a[i].y+=yy;
						if(to.a[i].x<1||to.a[i].x>8||to.a[i].y<1||to.a[i].y>8) continue;//越界判断
						if(vist[to.a[1].x][to.a[1].y][to.a[2].x][to.a[2].y]
						[to.a[3].x][to.a[3].y][to.a[4].x][to.a[4].y]) continue;//走重了
						
						if(viss[to.a[1].x][to.a[1].y][to.a[2].x][to.a[2].y]
						[to.a[3].x][to.a[3].y][to.a[4].x][to.a[4].y]){//可以和另一条路径接上
							cout<<"YES"<<endl;
							return ;
						}
						if(wrong(to,i)) continue;
						//
						fzt(to);
						//
						
						qt.push(to);
					}
				}
			}
		}
		else{
			int w=qs.size();
			while(w--){
				ChessBoard tmp=qs.front();
				qs.pop();
				for(int i=1;i<=4;++i){//第i颗棋子 
					for(int j=0;j<4;++j){//j是方向 
					
						int xx=dx[j];
						int yy=dy[j];
						if(jump_over(tmp,i,j)){
							xx*=2,yy*=2;
						}
						ChessBoard to=tmp;
						to.a[i].x+=xx,to.a[i].y+=yy;
						if(to.a[i].x<1||to.a[i].x>8||to.a[i].y<1||to.a[i].y>8) continue;
						if(viss[to.a[1].x][to.a[1].y][to.a[2].x][to.a[2].y]
						[to.a[3].x][to.a[3].y][to.a[4].x][to.a[4].y]) continue;
						if(vist[to.a[1].x][to.a[1].y][to.a[2].x][to.a[2].y]
						[to.a[3].x][to.a[3].y][to.a[4].x][to.a[4].y]){
							cout<<"YES"<<endl;
							return ;
						}
					    if(wrong(to,i)) continue;
//						//
//						viss[to.a[1].x][to.a[1].y][to.a[2].x][to.a[2].y]
//							[to.a[3].x][to.a[3].y][to.a[4].x][to.a[4].y]=1;
//							//
						fzs(to);
						qs.push(to);
					}
				}
			}
		}
	}
	cout<<"NO"<<endl;
	return ;
}
signed main(){
	while(cin>>s.a[1].x>>s.a[1].y){
		memset(viss,0,sizeof(viss));
		memset(vist,0,sizeof(vist));
		for(int i=2;i<=4;++i){
			cin>>s.a[i].x>>s.a[i].y;
		}
		for(int i=1;i<=4;++i){
			cin>>t.a[i].x>>t.a[i].y;
		}
		bfs(t,s);
	}
	return 0;
}
```

---

## 作者：小恐 (赞：1)

由于数据范围非常小，考虑搜索。

如果直接爆搜，则有 $8$ 步，每步有 $4$ 个棋子可以选择，每个棋子有 $4$ 个方向可以选。

一共复杂度为 $O((4\times4)^8)$，理论上会超时。

此时考虑剪枝，从起点搜 $4$ 步，从终点搜 $4$ 步，如果重合则代表可以。那如何判断是否重合呢？可以开一个数组 $vis_{x_1,y_1,x_2,y_2,x_3,y_3,x_4,y_4}$ 来代表是否被访问，即可判断是否重合。

注意每个终点只要有棋子就可以了，所以还要记录一个所有它的排列都要记录。

还有注意是多测。

~~代码可读性较差~~

code:
```cpp
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int NR=1e5+5;
const int MR=1e5+5;
const int INF=0x3f3f3f3f;
const int MOD=1e9+7;
const double eps=1e-8;
inline int read()
{
	int x=0;
	int bei=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')bei=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*bei;
}
bool vis[9][9][9][9][9][9][9][9];
struct Node
{
	int x[5],y[5];
	int cnt;
};
queue<Node> q;
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int a[5];
bool book[5];
void dfs(int x,Node t)
{
	if(x==5)
	{
		vis[t.x[a[1]]][t.y[a[1]]][t.x[a[2]]][t.y[a[2]]][t.x[a[3]]][t.y[a[3]]][t.x[a[4]]][t.y[a[4]]]=1;
		return;
	}
	for(int i=1;i<=4;++i) if(!book[i]) a[x]=i,book[i]=1,dfs(x+1,t),book[i]=0;
}
int main()
{
	//freopen("1.out","w",stdout);
	int x[3][5],y[3][5];
	while(scanf("%d",&x[1][1])!=EOF)
	{
		memset(vis,0,sizeof(vis));
		y[1][1]=read();
		for(int j=2;j<=4;++j)
			x[1][j]=read(),y[1][j]=read();
		for(int j=1;j<=4;++j)
			x[2][j]=read(),y[2][j]=read();

	Node t;
	while(!q.empty()) q.pop();
	t.cnt=0;
	for(int i=1;i<=4;++i) t.x[i]=x[1][i],t.y[i]=y[1][i];
	q.push(t);
	while(!q.empty())
	{
		t=q.front();
		q.pop();
		dfs(1,t);
		//printf("%d %d %d %d %d %d %d %d\n",t.x[1],t.y[1],t.x[2],t.y[2],t.x[3],t.y[3],t.x[4],t.y[4]);
		if(t.cnt==4) continue;
		for(int j=1;j<=4;++j)
		{
			for(int i=0;i<4;++i)
			{
				int tx=t.x[j]+dx[i],ty=t.y[j]+dy[i];
				if(tx>8||tx<1||ty>8||ty<1) continue;
				for(int k=1;k<=4;++k)
					if(tx==t.x[k]&&ty==t.y[k]) tx=tx+dx[i],ty=ty+dy[i];
				if(tx>8||tx<1||ty>8||ty<1) continue;
				bool flag=1;
				for(int k=1;k<=4;++k)
					if(tx==t.x[k]&&ty==t.y[k]) flag=0;
				if(!flag) continue;
				Node tt;
				tt.cnt=t.cnt+1;
				for(int k=1;k<=4;++k) tt.x[k]=(k==j?tx:t.x[k]),tt.y[k]=(k==j?ty:t.y[k]);
				q.push(tt);
			}
		}
	}
	while(!q.empty()) q.pop();
	t.cnt=0;
	for(int i=1;i<=4;++i) t.x[i]=x[2][i],t.y[i]=y[2][i];
	q.push(t);
	//puts("-------------------------------------------");
	bool flagg=0;
	while(!q.empty())
	{
		t=q.front();
		q.pop();
		//printf("%d %d %d %d %d %d %d %d\n",t.x[1],t.y[1],t.x[2],t.y[2],t.x[3],t.y[3],t.x[4],t.y[4]);
		if(vis[t.x[1]][t.y[1]][t.x[2]][t.y[2]][t.x[3]][t.y[3]][t.x[4]][t.y[4]]) {flagg=1;break;}
		if(t.cnt==4) continue;
		for(int j=1;j<=4;++j)
		{
			for(int i=0;i<4;++i)
			{
				int tx=t.x[j]+dx[i],ty=t.y[j]+dy[i];
				if(tx>8||tx<1||ty>8||ty<1) continue;
				for(int k=1;k<=4;++k)
					if(tx==t.x[k]&&ty==t.y[k]) tx=tx+dx[i],ty=ty+dy[i];
				if(tx>8||tx<1||ty>8||ty<1) continue;
				bool flag=1;
				for(int k=1;k<=4;++k)
					if(tx==t.x[k]&&ty==t.y[k]) flag=0;
				if(!flag) continue;
				Node tt;
				tt.cnt=t.cnt+1;
				for(int k=1;k<=4;++k) tt.x[k]=(k==j?tx:t.x[k]),tt.y[k]=(k==j?ty:t.y[k]);
				q.push(tt);
			}
		}
	}
	if(flagg)
	puts("YES");
	else
	puts("NO");
	}
	return 0;
}
```


---

## 作者：rainbow_cat (赞：0)

数据范围很小，考虑直接直接搜素，枚举量为 $(4 \times 4)^8$，超时。   
这里使用双向搜索，从起始状态和终止状态分别搜索 $4$ 步，状态可以用哈希记录，如果状态有重合则有解。   
因此枚举量为 $2 \times (4 \times 4)^4$，即 $2^{17}$。  
代码过于丑陋，这里就不展示了。

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA1724)

## 思路

其实这题不用双向广搜也能过，看似时间复杂度很大，会超时，实际上有很多地方都不能走，所以时间复杂度远小于它，可以在 $1.5\mathrm{s}$ 内跑过。这题时间限制是不准的，比 $896\mathrm{ms}$ 要大。

确定了单向的思路之后就是愉快的按题意来搜索了。我们可以用 $8$ 维数组来标点，每一维表示一个棋子的横坐标或纵坐标。

### 变量名解释

```cpp
const int N=9;
struct node{
	int x[N],y[N],step;//每个点横纵坐标，搜索步数。
}a;
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
bool vis[N][N][N][N][N][N][N][N];//标记数组。
bool mp[N][N];//目标棋盘。
````

### 1. 读入数据

本题有多组测试数据，记得清空。

```cpp
signed solution(){
	while(scanf("%d%d",&a.x[1],&a.y[1])!=EOF){
		memset(vis,0,sizeof vis);
		memset(mp,0,sizeof mp);
		a.step=0;//当前步数也清零。
		for(int i=2;i<=4;++i)a.x[i]=read(),a.y[i]=read();
		for(int i=1;i<=4;++i){
			int x=read(),y=read();
			mp[x][y]=1;
		}
	}
	return 0;
}
```

### 2. 搜索主体部分

这题由于是 $8$ 维标记，所以单开一个函数更加方便。

```cpp
bool checkvis(node k){//判断标记。
	return vis[k.x[1]][k.y[1]][k.x[2]][k.y[2]][k.x[3]][k.y[3]][k.x[4]][k.y[4]];
}
void updvis(node k){//做标记。
	vis[k.x[1]][k.y[1]][k.x[2]][k.y[2]][k.x[3]][k.y[3]][k.x[4]][k.y[4]]=1;
	return ;
}
```

判断是否在图内也可以写个函数。

```cpp
bool inmap(int x,int y){return x>=1&&x<=8&&y>=1&&y<=8;}
```

搜索主体如下。

```cpp
queue<node>q;
while(q.size())q.pop();
q.push(a);
updvis(a);//标记
while(q.size()){
    node now=q.front();
    q.pop();
    if(now.step>=8)break;//超过 8 步就不能再走了。
    for(int i=1;i<=4;++i){
        for(int j=0;j<4;++j){
            node tmp=now;
            tmp.x[i]+=dx[j];
            tmp.y[i]+=dy[j];
            if(checkjump(tmp.x[i],tmp.y[i],tmp,i,j))continue;//跳子见 3.
            if(!inmap(tmp.x[i],tmp.y[i])||checkvis(tmp))continue;//判断是否出图与是否打过标记。
            if(checkans(tmp)){//判断是否走完见 4.
                puts("YES");
                goto next;
            }
            ++tmp.step;//步数增加。
            q.push(tmp);
            updvis(tmp);//标记。
        }
    }
}
puts("NO");
next:;//这样为了方便。
```

### 3. 跳子

要注意跳子的条件是当前移动后**有棋子**，且跳到的位置**没棋子**。如果当前移动后和跳到的目标位置都有棋子，那么这个方向**不能进行任何移动**。

```cpp
bool checkjump(int &x,int &y,node a,int i,int j){
	for(int k=1;k<=4;++k){
		if(i==k)continue;//不和自己比较。
		if(x==a.x[k]&&y==a.y[k]){//移动后有棋子就跳。
			x+=dx[j];
			y+=dy[j];
			break;
		}
	}
	for(int k=1;k<=4;++k){
		if(i==k)continue;//不和自己比较。
		if(x==a.x[k]&&y==a.y[k])return 1;//跳后还有棋子就走不成。
	}
	return 0;//跳子后返回。
}
```

### 4. 判断是否走完

遍历当前每个棋子位置，如果有一个棋子没在其中任意一个目标位置，那么肯定没走完。

```cpp
bool checkans(node k){
	for(int i=1;i<=4;++i){
		if(!mp[k.x[i]][k.y[i]])return 0;
	}
	return 1;
}
```

## 完整无注释代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll read(){
	ll k=0,flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	return k*flag;
}
const int N=9;
struct node{
	int x[N],y[N],step;
}a;
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
bool vis[N][N][N][N][N][N][N][N],mp[N][N];
bool checkans(node k){
	for(int i=1;i<=4;++i){
		if(!mp[k.x[i]][k.y[i]])return 0;
	}
	return 1;
}
bool checkvis(node k){
	return vis[k.x[1]][k.y[1]][k.x[2]][k.y[2]][k.x[3]][k.y[3]][k.x[4]][k.y[4]];
}
void updvis(node k){
	vis[k.x[1]][k.y[1]][k.x[2]][k.y[2]][k.x[3]][k.y[3]][k.x[4]][k.y[4]]=1;
	return ;
}
bool inmap(int x,int y){return x>=1&&x<=8&&y>=1&&y<=8;}
bool checkjump(int &x,int &y,node a,int i,int j){
	for(int k=1;k<=4;++k){
		if(i==k)continue;
		if(x==a.x[k]&&y==a.y[k]){
			x+=dx[j];
			y+=dy[j];
			break;
		}
	}
	for(int k=1;k<=4;++k){
		if(i==k)continue;
		if(x==a.x[k]&&y==a.y[k])return 1;
	}
	return 0;
}
signed main(){
	while(scanf("%d%d",&a.x[1],&a.y[1])!=EOF){
		memset(vis,0,sizeof vis);
		memset(mp,0,sizeof mp);
		a.step=0;
		for(int i=2;i<=4;++i)a.x[i]=read(),a.y[i]=read();
		for(int i=1;i<=4;++i){
			int x=read(),y=read();
			mp[x][y]=1;
		}
		queue<node>q;
		while(q.size())q.pop();
		q.push(a);
		updvis(a);
		while(q.size()){
			node now=q.front();
			q.pop();
			if(now.step>=8)break;
			for(int i=1;i<=4;++i){
				for(int j=0;j<4;++j){
					node tmp=now;
					tmp.x[i]+=dx[j];
					tmp.y[i]+=dy[j];
					if(checkjump(tmp.x[i],tmp.y[i],tmp,i,j))continue;
					if(!inmap(tmp.x[i],tmp.y[i])||checkvis(tmp))continue;
					if(checkans(tmp)){
						puts("YES");
						goto next;
					}
					++tmp.step;
					q.push(tmp);
					updvis(tmp);
				}
			}
		}
		puts("NO");
		next:;
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/166518632)

---

## 作者：qinmingze (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA1724)

### 思路

#### 1. 方法

这是一道搜索题。

首先我们考虑爆搜，根据题目，我们有 $4$ 颗棋子，每个棋子总共有 $4$ 种走法，总步数要在 $8$ 步之内，那么运算次数最多就是 $16^8$，理论上是会超时的。

既然爆搜不行，我们便可以考虑**折半搜索**的方法。起始状态和目标状态各走 $4$ 步，如果中间有重合，便可以直接输出 ``YES``；如果没有重合，输出 ``NO`` 就可以了。

#### 2. 标记

- 首先，为了让我们在确定中间有重合的时候更加的方便，我们可以考虑用一个八维的数组 ``vis`` 来进行标记，其中如果 $vis_{{x_1},{y_1}{x_2},{y_2}{x_3},{y_3}{x_4},{y_4}}$ 的值为 $1$ 时，便说明中间出现了重合，便可以输出了。

- 其次，我们为了避免中间有重合，但却因为我们两边所对应的点的顺序不对应，我们便需要将**所有点的顺序**都进行标记，这样在判断中间有重合的情况时会更加的方便，具体如下：

```cpp
void dfs(){
	do{//枚举点的所有顺序，我们可以用 next_permutation 来实现。
		vis[tmp[c[1]].fi][tmp[c[1]].se][tmp[c[2]].fi][tmp[c[2]].se][tmp[c[3]].fi][tmp[c[3]].se][tmp[c[4]].fi][tmp[c[4]].se] = 1;//对当前的顺序进行标记。
	}while(next_permutation(c + 1, c + 5));
}
```


#### 3. 搜索

搜索我们需要分为两部分进行，一个是从起始状态开始，另一个则是从目标状态开始，这里我们主要说一下从起始状态开始的搜索的写法，从目标状态开始的写法类似。具体写法见下：

```cpp
void bfs1(){
	dfs();//对所有顺序进行标记。
	q.push({a[1], a[2], a[3], a[4], 0});
	while(!q.empty()){
		node now = q.front();
		q.pop();
		if(now.step >= 4) continue;//过半了。
		tmp[1] = now.a; tmp[2] = now.b; tmp[3] = now.c; tmp[4] = now.d;
		for(int i = 1; i <= 4; i++){//四个棋子。
			for(int j = 0; j < 4; j++){//四个方向。
				int x = tmp[i].fi, y = tmp[i].se;
				int nx = tmp[i].fi + dx[j];//第一种走法的横坐标。
				int ny = tmp[i].se + dy[j];//第一种走法的纵坐标。
				if(in(nx, ny)){//第一种走法的坐标在图内。
					bool flag1 = 0, flag2 = 0;
					int nnx = tmp[i].fi + dx[j] * 2;//第二种走法的横坐标。
					int nny = tmp[i].se + dy[j] * 2;//第二种走法的纵坐标。
					for(int k = 1; k <= 4; k++){
						if(tmp[k].fi == nx && tmp[k].se == ny) flag1 = 1;//第一种走法的落点是否有点。
					}
					if(in(nnx, nny)){//第二种走法的坐标在图内。
						for(int k = 1; k <= 4; k++){
							if(tmp[k].fi == nnx && tmp[k].se == nny) flag2 = 1;//第二种走法的落点是否有点。
					    }
					}
					if(flag1 == 0){//第一种走法。
						tmp[i] = {nx, ny};//更新。
						dfs();//标记。
						q.push({tmp[1], tmp[2], tmp[3], tmp[4], now.step + 1});
						//cout << tmp[1].fi << " " << tmp[1].se << " " << tmp[2].fi << " " << tmp[2].se << " " << tmp[3].fi << " " << tmp[3].se << " " << tmp[4].fi << " " << tmp[4].se << endl;
						tmp[i] = {x, y};//还原。
					}else if(flag1 == 1 && flag2 == 0 && in(nnx, nny)){//第二种走法。
						tmp[i] = {nnx, nny};//更新。
						dfs();
						q.push({tmp[1], tmp[2], tmp[3], tmp[4], now.step + 1});
						tmp[i] = {x, y};//还原。
					}
				}
			}
		}
	}
}
```

注意：在新的状态入队后，我们需要对我们刚刚改变了值的数组**进行还原操作**。

### 代码

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second

using namespace std;

const int N = 9;

int cnt;

pii a[N], b[N], tmp[N];

bool vis[N][N][N][N][N][N][N][N], F = 0;

int c[N];

struct node{
	pii a, b, c, d;
	int step;
};

queue<node> q;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool in(int x, int y){//判断是否在图内。
	return x >= 1 && x <= 8 && y >= 1 && y <= 8;
}

void dfs(){
	do{
		vis[tmp[c[1]].fi][tmp[c[1]].se][tmp[c[2]].fi][tmp[c[2]].se][tmp[c[3]].fi][tmp[c[3]].se][tmp[c[4]].fi][tmp[c[4]].se] = 1;
	}while(next_permutation(c + 1, c + 5));
}

void bfs1(){//从起始状态走。
	dfs();
	q.push({a[1], a[2], a[3], a[4], 0});
	while(!q.empty()){
		node now = q.front();
		q.pop();
		if(now.step >= 4) continue;
		tmp[1] = now.a; tmp[2] = now.b; tmp[3] = now.c; tmp[4] = now.d;
		for(int i = 1; i <= 4; i++){
			for(int j = 0; j < 4; j++){
				int x = tmp[i].fi, y = tmp[i].se;
				int nx = tmp[i].fi + dx[j];
				int ny = tmp[i].se + dy[j];
				if(in(nx, ny)){
					bool flag1 = 0, flag2 = 0;
					int nnx = tmp[i].fi + dx[j] * 2;
					int nny = tmp[i].se + dy[j] * 2;
					for(int k = 1; k <= 4; k++){
						if(tmp[k].fi == nx && tmp[k].se == ny) flag1 = 1;
					}
					if(in(nnx, nny)){
						for(int k = 1; k <= 4; k++){
							if(tmp[k].fi == nnx && tmp[k].se == nny) flag2 = 1;
					    }
					}
					if(flag1 == 0){
						tmp[i] = {nx, ny};
						dfs();
						q.push({tmp[1], tmp[2], tmp[3], tmp[4], now.step + 1});
						//cout << tmp[1].fi << " " << tmp[1].se << " " << tmp[2].fi << " " << tmp[2].se << " " << tmp[3].fi << " " << tmp[3].se << " " << tmp[4].fi << " " << tmp[4].se << endl;
						tmp[i] = {x, y};
					}else if(flag1 == 1 && flag2 == 0 && in(nnx, nny)){
						tmp[i] = {nnx, nny};
						dfs();
						q.push({tmp[1], tmp[2], tmp[3], tmp[4], now.step + 1});
						tmp[i] = {x, y};
					}
				}
			}
		}
	}
}

void bfs2(){//从目标状态走。
	q.push({b[1], b[2], b[3], b[4], 0});
    if(vis[tmp[1].fi][tmp[1].se][tmp[2].fi][tmp[2].se][tmp[3].fi][tmp[3].se][tmp[4].fi][tmp[4].se]){
		F = 1;
		return ;
	}
	//dfs(1);
	while(!q.empty()){
		node now = q.front();
		q.pop();
		if(now.step >= 4) continue;
		tmp[1] = now.a; tmp[2] = now.b; tmp[3] = now.c; tmp[4] = now.d;
		for(int i = 1; i <= 4; i++){
			for(int j = 0; j < 4; j++){
				int x = tmp[i].fi, y = tmp[i].se;
				int nx = tmp[i].fi + dx[j];
				int ny = tmp[i].se + dy[j];
				if(in(nx, ny)){
					bool flag1 = 0, flag2 = 0;
					int nnx = tmp[i].fi + dx[j] * 2;
					int nny = tmp[i].se + dy[j] * 2;
					for(int k = 1; k <= 4; k++){
						if(tmp[k].fi == nx && tmp[k].se == ny) flag1 = 1;
					}
					if(in(nnx, nny)){
						for(int k = 1; k <= 4; k++){
							if(tmp[k].fi == nnx && tmp[k].se == nny) flag2 = 1;
					    }
					}
					if(flag1 == 0){
						tmp[i] = {nx, ny};
						if(vis[tmp[1].fi][tmp[1].se][tmp[2].fi][tmp[2].se][tmp[3].fi][tmp[3].se][tmp[4].fi][tmp[4].se]){//重合了。
							F = 1;
							return ;
						}
						q.push({tmp[1], tmp[2], tmp[3], tmp[4], now.step + 1});
						tmp[i] = {x, y};
					}else if(flag1 == 1 && flag2 == 0 && in(nnx, nny)){//重合了。
						tmp[i] = {nnx, nny};
						if(vis[tmp[1].fi][tmp[1].se][tmp[2].fi][tmp[2].se][tmp[3].fi][tmp[3].se][tmp[4].fi][tmp[4].se]){
							F = 1;
							return ;
						}
						q.push({tmp[1], tmp[2], tmp[3], tmp[4], now.step + 1});
						tmp[i] = {x, y};
					}
				}
			}
		}
	}
}

int main(){
	int T;
	//cin >> T;
	while(cin >> a[1].fi){ 
	    cin >> a[1].se;
		for(int i = 2; i <= 4; i++) cin >> a[i].fi >> a[i].se;
		for(int i = 1; i <= 4; i++) cin >> b[i].fi >> b[i].se;
		for(int i = 1; i <= 4; i++) tmp[i] = a[i], c[i] = i;
		F = 0;
		memset(vis, 0, sizeof vis);//多测清空。
		while(!q.empty()){q.pop();}
		bfs1();
		while(!q.empty()){q.pop();}
		for(int i = 1; i <= 4; i++) tmp[i] = b[i];
		bfs2();
		if(F == 1) puts("YES");//可以走到。
		else puts("NO");
	}
}
```

---

## 作者：一只书虫仔 (赞：0)

#### Description

> $8 \times 8$ 的棋盘上，给定 $4$ 个棋子的起点和终点，每次一个棋子可以向上下左右挪一位，或者跳过上下左右的一个棋子挪一位。求在 $8$ 步内每个棋子能不能挪到终点。

#### Solution

直接爆搜是不可接受的（$\mathcal O(16^8)$），所以直接考虑剪枝。

首先注意这 $8$ 个棋子是一模一样的，所以只需要考虑每个终点上是否有棋子即可。

然后考虑折半，这里该怎么折半呢？每个棋子可以从起点向 $4$ 个方向去走，终点也可以向 $4$ 个方向去迎合棋子，每个走过的地方都进行标记就可以判断路径是否重合。这两个部分理论上是不互相影响的，因此，$\mathcal O(16^4)$ 就可以解决。

---

## 作者：Mooncrying (赞：0)

# UVA1724 Solitaire 题解

### 题目大意

给定一个 $8$ $×$ $8$ 的棋盘，上面有 $4$ 个棋子，求能否在 $8$ 步之内到达题目所给的终点。

### 分析

- 因为数据范围很小，而且是求可行性问题，我们考虑 bfs。

- 开一个八维数组 $vis$，用来记录当前状态是否走过。但因为 $9^8$ 太大，我们选择将坐标减 $1$，让数组能开成八维 $8$ 位。

- 用一个 $chess$ 数组和 $pos$ 数组，来记录当前四个棋子的位置，来判断是否应当跳一格棋。

- 再加上一些常用的剪枝。

- 多测，注意初始化。

- 然后就没啥了。

**代码奉上：**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct point
{
	int x,y;
}pos[5];
struct Node
{
	int t,x[5],y[5];
}k;
bool vis[8][8][8][8][8][8][8][8];
bool ed[8][8],chess[8][8];
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};
void sign(Node k)
{
	vis[k.x[1]][k.y[1]][k.x[2]][k.y[2]][k.x[3]][k.y[3]][k.x[4]][k.y[4]]=1;
}//标记当前状态
bool jud_vis(Node k)
{
	if(vis[k.x[1]][k.y[1]][k.x[2]][k.y[2]][k.x[3]][k.y[3]][k.x[4]][k.y[4]]) return 1;
	return 0;
}//判断当前状态是否被遍历过
bool jud_ed(Node k)
{
	for(int i=1;i<=4;++i)
		if(!ed[k.x[i]][k.y[i]]) return 0;
	return 1;
}//判断是否全部到达终点
bool bfs()
{
	queue<Node> q;
	sign(k);
	q.push(k);
	while(!q.empty())
	{
		k=q.front();q.pop();
		if(k.t>=8) return 0;
		for(int i=1;i<=4;++i) chess[pos[i].x][pos[i].y]=0;
		for(int i=1;i<=4;++i)
		{
			chess[k.x[i]][k.y[i]]=1;
			pos[i].x=k.x[i];
			pos[i].y=k.y[i];
		}更新棋子位置
		for(int i=1;i<=4;++i)
		{
			for(int j=0;j<4;++j)
			{
				Node kk=k;kk.t++;
				kk.x[i]+=dx[j];
				kk.y[i]+=dy[j];
				if(chess[kk.x[i]][kk.y[i]])
				{
					kk.x[i]+=dx[j];
					kk.y[i]+=dy[j];
				}//判断是否跳棋
				if(kk.x[i]<0||kk.x[i]>=8||kk.y[i]<0||kk.y[i]>=8) continue;//判断边界
				if(chess[kk.x[i]][kk.y[i]]) continue;
				if(jud_vis(kk)) continue;
				if(jud_ed(kk)) return 1;
				sign(kk);q.push(kk);
			}
		}	
	}
}//单向宽搜
int main()
{
	while(scanf("%d%d",&k.x[1],&k.y[1])!=EOF)
	{
		k.t=0;
		memset(ed,0,sizeof(ed));
		memset(vis,0,sizeof(vis));
		for(int i=2;i<=4;++i) scanf("%d%d",&k.x[i],&k.y[i]);
		for(int i=1;i<=4;++i)
		{
			k.x[i]--;k.y[i]--;
			int x,y;
			scanf("%d%d",&x,&y);
			ed[x-1][y-1]=1;
		}
		if(jud_ed(k)) printf("YES\n");
		else if(bfs()) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

