# Bloxorz I

## 题目背景

小汤姆喜欢玩游戏。有一天，他下载了一个叫做“Bloxorz”的小电脑游戏，让他非常兴奋。

## 题目描述

这是一个关于将一个方块滚动到特定位置的游戏。准确地说，这个平面由几个单位单元格组成，是一个矩形形状的区域。而方块由两个完美对齐的单位立方体组成，可以躺下并占据两个相邻的单元格，也可以站立并占据一个单独的单元格。

你可以通过选择方块在地面上的四条边之一，并围绕该边旋转 90 度来移动方块，每次旋转算作一步。有三种类型的单元格，刚性单元格、易碎单元格和空单元格。

- 刚性单元格可以支撑方块的全部重量，因此可以是方块所占据的两个单元格中的任意一个，也可以是方块完全站立在上面的单元格。
- 易碎单元格只能支撑方块重量的一半，因此不能是方块完全站立在上面的唯一单元格。
- 空单元格无法支撑任何东西，因此方块不可能部分位于该单元格上。

游戏的目标是以最少的步数将站立的方块滚动到平面上唯一的目标单元格。

![](https://cdn.luogu.com.cn/upload/image_hosting/0byqnwkj.png)

方块站在单个单元格上。

![](https://cdn.luogu.com.cn/upload/image_hosting/q3gn2fd8.png)

方块横躺在两个相邻的单元格上。

![](https://cdn.luogu.com.cn/upload/image_hosting/9vtkwepc.png)

方块纵躺在两个相邻的单元格上。

在小汤姆通过游戏的几个阶段后，他发现比他预期的要难得多。因此，他求助于你的帮助。

## 说明/提示

### 数据范围

对于所有的数据：$3 ≤ R，C ≤ 500$。

### 翻译

翻译来自于：[ChatGPT](https://chatgpt.com/)。

## 样例 #1

### 输入

```
7 7
#######
#..X###
#..##O#
#....E#
#....E#
#.....#
#######
0 0```

### 输出

```
10```

# 题解

## 作者：carbon_monoxide (赞：7)

还没有看题目的可以戳[这里](https://www.luogu.com.cn/problem/P10485)。

这是一道模拟和 bfs 的好题，但是细节很多。

由于方块有三个状态，因此我们在写常规 bfs 时要多加一个量来表示方块的状态。我用 0 表示直立，1 表示横躺，2 表示竖躺。其中横躺时 $x,y$ 的坐标指向左边的方格，竖躺时 $x,y$ 的坐标指向上边的方格。

然后就是判断方块的违规操作。一共有两种情况，第一种是直立时站在方格 E 上，第二种是方块在方格 # 上（这里我们在地图的外面加一圈方格 #，就省得判断方块有没有越界了）。此外，方块走回头路也是违规的。

最后就是方块的移动。

我个人的代码是这样的：

```cpp
//zt表示状态，x与y是坐标，bs表示步数。
if(!zt){//直立时
    //q.push({x,y,zt,bs});
    q.push({x,y-2,1,bs+1});//向左
    q.push({x,y+1,1,bs+1});//向右
    q.push({x-2,y,2,bs+1});//向前
    q.push({x+1,y,2,bs+1});//向后
}else if(zt==1){//横躺时
    q.push({x,y-1,0,bs+1});//向左
    q.push({x,y+2,0,bs+1});//向右
    q.push({x-1,y,1,bs+1});//向前
    q.push({x+1,y,1,bs+1});//向后
}else{//竖躺时
    q.push({x,y-1,2,bs+1});//向左
    q.push({x,y+1,2,bs+1});//向右
    q.push({x-1,y,0,bs+1});//向前
    q.push({x+2,y,0,bs+1});//向后
}
```

知道这些坑点后，我们就可以愉快地写代码啦！

```cpp
//P10485
#include<bits/stdc++.h>
using namespace std;
int n,m,vis[510][510][3],ans=-1;
char a[510][510];
struct node{
	//坐标，状态，步数
    int x,y,zt,bs;
    /*
    zt=0 X

    zt=1 XX

    zt=2 X
         X
    */
}st,ed;//起点，终点
void bfs(){
	queue<node> q;
    q.push(st);
    while(!q.empty()){
        int x=q.front().x,y=q.front().y,zt=q.front().zt,bs=q.front().bs;
        //cout<<x<<" "<<y<<" "<<zt<<"\n";
        q.pop();
        if(x==ed.x&&y==ed.y&&zt==ed.zt){//到终点了
			ans=bs;
		    return;
		}
        if(a[x][y]=='E'&&!zt) continue;//直立在E格上
        if(a[x][y]=='#'||a[x][y+1]=='#'&&zt==1||a[x+1][y]=='#'&&zt==2) continue;//越界
        if(vis[x][y][zt]) continue;//同一状态下走过了
        vis[x][y][zt]=1;//标记走过了
        if(!zt){//直立时
            q.push({x,y-2,1,bs+1});
            q.push({x,y+1,1,bs+1});
            q.push({x-2,y,2,bs+1});
            q.push({x+1,y,2,bs+1});
        }else if(zt==1){//横躺时
            q.push({x,y-1,0,bs+1});
            q.push({x,y+2,0,bs+1});
            q.push({x-1,y,1,bs+1});
            q.push({x+1,y,1,bs+1});
        }else{//竖躺时
        	q.push({x,y-1,2,bs+1});
            q.push({x,y+1,2,bs+1});
            q.push({x-1,y,0,bs+1});
            q.push({x+2,y,0,bs+1});
        }
    }
}
int main(){
    while(cin>>n>>m&&n&&m){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                cin>>a[i][j];
		//手动加边界
        for(int i=1;i<=n;i++) a[i][0]='#',a[i][m+1]='#';
        for(int i=1;i<=m;i++) a[0][i]='#',a[n+1][i]='#';
        //找起点
        int f=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]=='X'){
                    if(a[i][j+1]=='X') st.zt=1;//起点是横躺状态
                    else if(a[i+1][j]=='X') st.zt=2;//起点是竖躺状态
                    else st.zt=0;//起点是直立状态
                    st.x=i,st.y=j;
					f=1;
					break;
                }
            }
            if(f) break;
        }
        //找终点
        f=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]=='O'){
                    if(a[i][j+1]=='O') ed.zt=1;//终点是横躺状态
                    else if(a[i+1][j]=='O') ed.zt=2;//终点是竖躺状态
                    else ed.zt=0;//终点是直立状态
                    ed.x=i,ed.y=j;
                    f=1;
					break;
                }
            }
            if(f) break;
        }
        bfs();//广搜
        if(ans==-1) cout<<"Impossible\n";//无解
        else cout<<ans<<"\n";//有解
        /*
        多测不清空
        爆零两行泪
        */
        memset(vis,0,sizeof(vis));
        ans=-1;
    }
    return 0;
}
```

---

## 作者：Misty_Post (赞：5)

看题感觉很难，实则不难。

显然用广搜，搜到一组答案直接退出就好。

但是为了解决时间问题，我们可以得出一个显然的优化，就是如果某个坐标的某个状态以前已经走过了，那现在走显然就不是最优了，就可以不用接着走下去了。

细节都在代码里，注释齐全，适合用来查错。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m;
ll stx,sty,szt,ans;
ll edx,edy;
ll vis[505][505][3];
//zt=1立着，zt=2,横着，记录左边，zt=3，竖着，记录上面 
char s[505][505];
struct KudaIzuna{//皮一下，可以去查一下是什么OvO 
	ll x,y,zt,st;
};
queue<KudaIzuna>q;
void bfs(){
	while(!q.empty()){
		KudaIzuna ls=q.front();
		ll x=ls.x,y=ls.y; 
		ll st=ls.st;
		if(!vis[x][y][ls.zt]){
			vis[x][y][ls.zt]=1;
			if(ls.zt==1){//立着 
				if(x==edx&&y==edy){//立起来到终点了 
					ans=st;
					return;
				}
				//竖着躺下来
				if(x-2>=1&&s[x-1][y]!='#'&&s[x-2][y]!='#'){//向上 
					q.push({x-2,y,3,st+1});
				} 
				if(x+2<=n&&s[x+1][y]!='#'&&s[x+2][y]!='#'){//向下 
					q.push({x+1,y,3,st+1});
				}
				//横着躺下来
				if(y-2>=1&&s[x][y-2]!='#'&&s[x][y-1]!='#'){
					q.push({x,y-2,2,st+1});
				} 
				if(y+2<=m&&s[x][y+2]!='#'&&s[x][y+1]!='#'){
					q.push({x,y+1,2,st+1});//左边坐标 
				}
			}
			if(ls.zt==2){//横着
				if(y-1>=1&&s[x][y-1]!='#'&&s[x][y-1]!='E'){//向左立起来 
					q.push({x,y-1,1,st+1});
				} 
				if(y+2<=m&&s[x][y+2]!='#'&&s[x][y+2]!='E'){//向右立起来 
					q.push({x,y+2,1,st+1});
				}
				if(x-1>=1&&s[x-1][y]!='#'&&s[x-1][y+1]!='#'){//向上翻滚 
					q.push({x-1,y,2,st+1});
				} 
				if(x+1<=n&&s[x+1][y]!='#'&&s[x+1][y+1]!='#'){//向下翻滚 
					q.push({x+1,y,2,st+1});
				} 
			} 
			if(ls.zt==3){//竖着 
				if(x-1>=1&&s[x-1][y]!='#'&&s[x-1][y]!='E'){//向上立起来 
					q.push({x-1,y,1,st+1});
				}
				if(x+2<=n&&s[x+2][y]!='#'&&s[x+2][y]!='E'){//向下立起来 
					q.push({x+2,y,1,st+1}); 
				}
				if(y-1>=1&&s[x][y-1]!='#'&&s[x+1][y-1]!='#'){//向左翻滚 
					q.push({x,y-1,3,st+1});
				}
				if(y+1<=m&&s[x][y+1]!='#'&&s[x+1][y+1]!='#'){//向左翻滚 
					q.push({x,y+1,3,st+1});
				}
			}
		}
		q.pop();
	}
}
int main(){
	while(cin>>n>>m){
		memset(vis,0,sizeof(vis));
		if(n==0){
			return 0;
		}
		while(!q.empty()){
			q.pop();
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>s[i][j];
				if(s[i][j]=='O'){
					edx=i,edy=j;
				}
			}
		}
		szt=-1;
		for(int i=1;i<=n;i++){
			if(szt!=-1){
				break;
			}
			for(int j=1;j<=m;j++){
				if(s[i][j]=='X'){
					if(s[i][j+1]=='X'){
						szt=2;stx=i,sty=j;
					}
					else if(s[i+1][j]=='X'){
						szt=3,stx=i,sty=j;
					}
					else{
						szt=1;stx=i,sty=j;
					}
				}
				if(szt!=-1){
					break;
				}
			}
		}
		ans=1e18;
		q.push({stx,sty,szt,0});
		bfs();
		if(ans==1e18){
			cout<<"Impossible"<<"\n";
		}
		else
			cout<<ans<<"\n";
	}
}
```

---

## 作者：xiaomo8125 (赞：3)

# P10485 Bloxorz I 题解
蓝书上的 BFS 例题，能够很好学习运用 BFS 和一些 BFS 处理细节。

这是一道典型的“走地图”类问题，也就是形如“给定一个矩形地图，控制一个物体在地图中按照要求移动，求最少步数”的问题。广度优先搜索算法很擅长解决这种问题——地图的整体形态是固定不变的，只有少数个体或特征随着每一步操作发生改变。我们只需要把这些变化的部分提取为状态，把起始状态加入队列，使用广度优先搜索算法不断取出队头状态，沿着分支扩展、入队即可。广度优先搜索是逐层遍历搜索树的算法。所有状态按照入队的先后顺序具有层次单调性（也就是步数单调性）。如果每一次扩展恰好对应一步，那么当一个状态第一次被访问（入队）时，就得到了从起始状态到达该状态的最少步数。

在这道题目中，不变的是整个地图，变化的部分有长方体的位置和放置形态。我们可以用一个三元组 $(x,y,lie)$ 代表一个状态（搜索树中的一个节点）然后执行广度优先搜索。

代码
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
struct rec{
	int x,y,lie;
};
char s[505][505];
rec st,ed;
int n,m,d[510][510][3];
queue<rec> q;
const int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};
bool valid1(int x,int y){
	return x>=1 && x<=n && y>=1 && y<=m;
}
void deal_st_ed(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='O'){
				ed={i,j,0};
				s[i][j]='.';
			}
			else if(s[i][j]=='X'){
				for(int k=0;k<4;k++){
					int x=i+dx[k],y=j+dy[k];
					if(valid1(x,y)&&s[x][y]=='X'){
						st={min(x,i),min(y,j),(k<2?1:2)};
						s[i][j]=s[x][y]='.';
						break;
					}
				}
				if(s[i][j]=='X')st={i,j,0};
			}
		}
	}
}
bool valid2(rec next){
	int nx=next.x,ny=next.y;
	if(!valid1(nx,ny)){
		return 0;
	}
	if(s[nx][ny]=='#'){
		return 0;
	}
	if(next.lie==0 && s[nx][ny]!='.'){
		return 0;
	}
	if(next.lie==1 && s[nx][ny+1]=='#'){
		return 0;
	}
	if(next.lie==2 && s[nx+1][ny]=='#'){
		return 0;
	}
	return 1;
}
const int n_x[3][4]={{0,0,-2,1},{0,0,-1,1},{0,0,-1,2}};
const int n_y[3][4]={{-2,1,0,0},{-1,2,0,0},{-1,1,0,0}};
const int n_l[3][4]={{1,1,2,2},{0,0,1,1},{2,2,0,0}};

int bfs(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<3;k++){
				d[i][j][k]=-1;
			}
		}		
	}
	while(!q.empty()){
		q.pop();
	}
	d[st.x][st.y][st.lie]=0;
	q.push(st);
	while(!q.empty()){
		rec now=q.front();
		q.pop();
		for(int i=0;i<4;i++){
			rec next;
			next.x=now.x+n_x[now.lie][i];
			next.y=now.y+n_y[now.lie][i];
			next.lie=n_l[now.lie][i];
			if(!valid2(next))continue;
			if(d[next.x][next.y][next.lie]==-1){
				d[next.x][next.y][next.lie]=d[now.x][now.y][now.lie]+1;
				q.push(next);
				if(next.x==ed.x && next.y==ed.y &&next.lie==ed.lie){
					return d[next.x][next.y][next.lie];
				}
			}
		}	
	}
	return -1;
}

int main(){
	int aa=0;
	while(cin>>n>>m && n){
		for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
		deal_st_ed();
		int ans=bfs();
		if(ans==-1)printf("Impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：atomic_int (赞：2)

### Analysis

BFS。

本题中方块比较特殊，有三种状态。我们分别用 $u=0,1,2$ 代表方块竖立着、方块竖躺着、方块横躺着。其中，当 $u=1$ 时，记坐标为下边一格，$u=2$ 时，记坐标为左边一格。那么移动函数为：
```cpp
std::tuple<int, int, int> move(int x, int y, int u, int dir) {
  // (x, y) 表示坐标，u 的含义见上文。返回的顺序也是这样，即坐标 + 状态。
  // dir = 0, 1, 2, 3 分别表示向上、下、左、右滚动。
  if (u == 0) {
    if (dir == 0) {
      return {x - 1, y, 1};
    } else if (dir == 1) {
      return {x + 2, y, 1};
    } else if (dir == 2) {
      return {x, y - 2, 2};
    } else {
      return {x, y + 1, 2};
    }
  }
  if (u == 1) {
    if (dir == 0) {
      return {x - 2, y, 0};
    } else if (dir == 1) {
      return {x + 1, y, 0};
    } else if (dir == 2) {
      return {x, y - 1, 1};
    } else {
      return {x, y + 1, 1};
    }
  }
  if (u == 2) {
    if (dir == 0) {
      return {x - 1, y, 2};
    } else if (dir == 1) {
      return {x + 1, y, 2};
    } else if (dir == 2) {
      return {x, y - 1, 0};
    } else {
      return {x, y + 2, 0};
    }
  }
}
```

剩下的就和普通的 BFS 无异了。时间复杂度为 $O(RC)$。

### Code

```cpp
#include <bits/stdc++.h>

const int N = 505;

int n, m, a[N][N], f[N][N][3];
std::tuple<int, int, int> st, ed;
bool vis[N][N][3];

bool exist(int x, int y) {
  return (x < 1 || x > n || y < 1 || y > m || a[x][y] == 2);
}

std::tuple<int, int, int> move(int x, int y, int u, int dir) {
  if (u == 0) {
    if (dir == 0) {
      return {x - 1, y, 1};
    } else if (dir == 1) {
      return {x + 2, y, 1};
    } else if (dir == 2) {
      return {x, y - 2, 2};
    } else {
      return {x, y + 1, 2};
    }
  }
  if (u == 1) {
    if (dir == 0) {
      return {x - 2, y, 0};
    } else if (dir == 1) {
      return {x + 1, y, 0};
    } else if (dir == 2) {
      return {x, y - 1, 1};
    } else {
      return {x, y + 1, 1};
    }
  }
  if (u == 2) {
    if (dir == 0) {
      return {x - 1, y, 2};
    } else if (dir == 1) {
      return {x + 1, y, 2};
    } else if (dir == 2) {
      return {x, y - 1, 0};
    } else {
      return {x, y + 2, 0};
    }
  }
}

void bfs() {
  std::queue<std::tuple<int, int, int>> q;
  q.push(st);
  vis[std::get<0>(st)][std::get<1>(st)][std::get<2>(st)] = true;
  while (!q.empty()) {
    auto [x, y, u] = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      auto [nx, ny, nu] = move(x, y, u, i);
      if (nu == 0 && (exist(nx, ny) || a[nx][ny] == 1)) {
        continue;
      }
      if (nu == 1 && (exist(nx, ny) || exist(nx - 1, ny))) {
        continue;
      }
      if (nu == 2 && (exist(nx, ny) || exist(nx, ny + 1))) {
        continue;
      }
      if (vis[nx][ny][nu]) {
        continue;
      }
      vis[nx][ny][nu] = true;
      f[nx][ny][nu] = f[x][y][u] + 1;
      q.push({nx, ny, nu});
    }
  }
  auto [x, y, u] = ed;
  if (!vis[x][y][u]) {
    std::cout << "Impossible" << '\n';
  } else {
    std::cout << f[x][y][u] << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  while (std::cin >> n >> m, n != 0 && m != 0) {
    st = ed = {0, 0, 0};
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        char c;
        std::cin >> c;
        if (c == 'E') {
          a[i][j] = 1;
        } else if (c == '#') {
          a[i][j] = 2;
        } else if (c == 'X') {
          if (std::get<0>(st) != 0) {
            auto [x, y, u] = st;
            if (x == i) {
              st = {x, y, 2};
            }
            if (y == j) {
              st = {i, j, 1};
            }
          } else {
            st = {i, j, 0};
          }
        } else if (c == 'O') {
          ed = {i, j, 0};
        }
      }
    }
    bfs();
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        a[i][j] = 0;
        for (int k = 0; k < 3; k++) {
          f[i][j][k] = 0;
          vis[i][j][k] = false;
        }
      }
    }
  }
  return 0;
}
```

---

## 作者：Nasaepa (赞：2)

这道题是一道 bfs 题目，但是细节比较多。

首先，这道题有多任务。我们可以用如下结构进行输入：

```cpp
while(scanf("%d%d",&n,&m),n|m)task();
```

我们可以在  `task()` 函数中进行操作，这样比较容易书写代码。`while` 循环中的表达式只会判断 `n|m` 的值是否为 $0$ ，其中 `|` 符号代表为**按位或**符号，`n|m` 的值为 $0$ 当且仅当 $n$ 与 $m$ 均为 $0$ 。

其次，这道题中，方块状态的储存是一大难点。我们可以定义三个变量 $stl,x,y$，其中 $stl$ 代表方块的状态（$stl = 0$ 代表**直立**，$stl = 1$ 代表方块**竖躺**，$stl = 2$ 代表方块**横躺**），$(x,y)$ 代表方块所在的位置，其中当 $stl = 0$ 时，$x,y$ 代表方块**底部**的位置， $stl = 1$ 时, $(x,y)$ 代表方块较**靠上**的格子的位置，$stl = 2$时，$(x,y)$ 代表方块较**靠左**的格子的位置。

因此，我们可以用结构体对方块进行储存，结构体如下：

```cpp
struct node{
    int x,y;
    int stl; // 状态。 0 为直立，1 为竖躺，2 为横躺
    int stp;// 步数
    node(const int &a = 0,const int &b = 0,const int &c = 0,const int &d = 0){
        x = a,y = b,stl = c,stp = d;
    }
};
```

知道了方块如何储存，我们就能顺理成章地求出方块的初始状态和终止状态。我们可以从上到下，从左到右遍历全图，寻找 `X` 字符，则第一个被遍历到的 `X` 字符一定所有 `X` 字符是较**靠左上**的一个（当然，全图可能只有一个 `X` 字符）。如果全地图有且仅有**一个** `X` 字符，则代表方块为**直立**状态。如果全地图有**两个** `X` 字符，则如果这两个字符在同一行，则方块的初始状态为**横躺**状态，否则为**竖躺**状态。判断方块的终止状态也可以使用相似的逻辑进行求出。对于方块的终止状态，我们实际上只需要知道其 $x,y$ 值，因为方块的终止状态的只有可能处于直立状态。我们可以利用相同的函数求出方块的初始和终止状态。

```cpp
inline node getstt(const char &ch){
    node to_ans;
    for(int i = 1;i<=n;++i){
        for(int j = 1;j<=m;++j){
            if(mp[i][j] != ch)continue;
            if(to_ans.x){// 表示横躺或者竖躺
                if(i == to_ans.x)to_ans.stl = 2;// 如果两个相同的字符在同一行，表示目前所求的状态是横躺状态
                else to_ans.stl = 1;
                return to_ans;// 如果已经知道了所求状态处于横躺或者竖躺，那么相当于已经完全知道了这个状态，可以直接返回
            }else to_ans.x = i,to_ans.y = j;
        }
    }
    return to_ans;
}
```

在知道方块的初始和终止状态后，我们便可以进行广搜。我们首先要考虑方块在什么情况是违规的。

首先，在**直立状态**下，如果方块踩空或者超出边界，则方块违规。除此以外，方块不能在标记为 `E`的方块上直立。判断代码如下：

```cpp
// 其中，mp 数组储存地图。
if(mp[x][y] == '#')continue ;
if(x <= 0 || x > n || y <= 0 || y > m)continue;
if(stl == 0 && mp[x][y] == 'E')continue ;
```

其次。在**横躺**或者**竖躺**状态下，我们需要判断方块的另一个位置是否违规。其代码如下：

```cpp
if(stl == 1 && mp[x+1][y] == '#')continue ;
if(stl == 2 && mp[x][y+1] == '#')continue ;
```

为了防止样例中，地图的边界部分不为 `#` ，我们可以手动进行设置：

```cpp
for(int i = 1;i<=n;++i)mp[i][0] = mp[i][m+1] = '#';
for(int i = 1;i<=m;++i)mp[0][i] = mp[n+1][i] = '#';
```

为了降低时间复杂度，防止方块走回头路，我们还要对方块的状态进行存储，防止方块进入**重复**状态。

```cpp
if(used[stl][x][y])continue ;
used[stl][x][y] = 1;
```

接着，我们还要考虑方块如何转移其状态。还是从最简单的**直立**状态开始考虑。当方块直立时，它可以向上下左右移动。如果以其将要到达的靠左上的点位置为 $(x_n,y_n)$，状态为 $stl_n$ 状态本别为：

1. 向上 $x_n = x - 2,y_n = y,stl_n = 1$
2. 向下 $x_n = x + 1,y_n = y,stl_n = 1$
3. 向左 $x_n = x,y _n = y-2,stl_n = 2$
4. 向右 $x_n = n,y_n = y+1,stl_n = 2$

如果为**竖躺**，则：

1. 向上 $x_n = x - 1,y_n = y,stl_n = 0$
2. 向下 $x_n = x + 2,y_n = y,stl_n = 0$
3. 向左 $x_n = x,y_n = y-1,stl_n = 1$
4. 向右 $x_n = n,y_n = y+1,stl_n = 1$

如果为**横躺**，则：

1. 向上 $x_n = x - 1,y_n = y,stl_n = 2$
2. 向下 $x_n = x + 1,y_n = y,stl_n = 2$
3. 向左 $x_n = x,y_n = y-1,stl_n = 0$
4. 向右 $x_n = n,y_n = y+2,stl_n = 0$

在知道这些后，我们就可以把整个代码写出来了。

```cpp
// #pragma GCC optimize(2) // 开启O2优化
#include<bits/stdc++.h>
using namespace std;
#define N 510 // 最大数据范围 = 1e6+10
#define INF 0x3f3f3f3f // 无穷大
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define x1 ytt87324bvt78234vb72384bv2342v4325vb2387623c
#define end qgri6ubv4678vrct6r2v3b768rtv2367r324v67rfc234v76vrf3467cv34657f3
int n,m,x,y,stl,stp;
char mp[N][N];
int dist[3][N][N];
bool used[3][N][N];

struct node{
    int x,y;
    int stl; // 状态。 0 为直立，1 为竖躺，2 为横躺
    int stp;// 步数
    node(const int &a = 0,const int &b = 0,const int &c = 0,const int &d = 0){
        x = a,y = b,stl = c,stp = d;
    }
};
node start,end;
// 根据某个字符得到状态
inline node getstt(const char &ch){
    node to_ans;
    for(int i = 1;i<=n;++i){
        for(int j = 1;j<=m;++j){
            if(mp[i][j] != ch)continue;
            if(to_ans.x){// 表示横躺或者竖躺
                if(i == to_ans.x)to_ans.stl = 2;
                else to_ans.stl = 1;
                return to_ans;
            }else to_ans.x = i,to_ans.y = j;
        }
    }
    return to_ans;
}

void bfs(){
    queue<node> q;
    q.push(start);
    while(q.size()){
        x = q.front().x;
        y = q.front().y;
        stl = q.front().stl;
        stp = q.front().stp;
        q.pop();
        if(used[stl][x][y])continue ;
        if(x <= 0 || x > n || y <= 0 || y > m)continue;
        // 判断在 E 上直立
        if(stl == 0 && mp[x][y] == 'E')continue ;
        // 判断一遍越界
        if(stl == 1 && mp[x+1][y] == '#')continue ;
        if(stl == 2 && mp[x][y+1] == '#')continue ;
        if(mp[x][y] == '#')continue ;
        dist[stl][x][y] = stp;
        used[stl][x][y] = 1;
        
        if(x == end.x && y == end.y && stl == end.stl)return ;
        // 找到下一个状态
        if(stl == 0){
            q.push(node(x,y-2,2,stp+1));
            q.push(node(x,y+1,2,stp+1));
            q.push(node(x-2,y,1,stp+1));
            q.push(node(x+1,y,1,stp+1));
        }else if(stl == 1){
            q.push(node(x-1,y,0,stp+1));
            q.push(node(x+2,y,0,stp+1));
            q.push(node(x,y-1,1,stp+1));
            q.push(node(x,y+1,1,stp+1));
        }else{
            q.push(node(x-1,y,2,stp+1));
            q.push(node(x+1,y,2,stp+1));
            q.push(node(x,y-1,0,stp+1));
            q.push(node(x,y+2,0,stp+1));
        }
    }
}

// 输入函数
void input(){
    for(int i = 1;i<=n;++i)scanf("%s",mp[i] + 1);
    memset(dist,0x3f,sizeof(dist));
    memset(used,0,sizeof(used));
    // 找出初始状态
    start = getstt('X');
    end = getstt('O');
    // 在外围设置 '#'
    for(int i = 1;i<=n;++i)mp[i][0] = mp[i][m+1] = '#';
    for(int i = 1;i<=m;++i)mp[0][i] = mp[n+1][i] = '#';
}

// 处理函数
void solve(){
    bfs();
}

// 输出函数
void output(){
    if(!used[end.stl][end.x][end.y])printf("Impossible\n");
    else printf("%d\n",dist[end.stl][end.x][end.y]);
}

// 多组测试样例
void task(){
    input();
    solve();
    output();
}

// 主函数
int main(int argc,char* argv[]){
    while(scanf("%d%d",&n,&m),n|m)task();
    system("pause");
    return 0;
}
```

---

## 作者：Helenty (赞：1)

### 前言

首先，推荐一个可以较难搜索的题单：[搜索强化 - 从入门到跳楼](https://www.luogu.com.cn/training/721855)。

然后说回本题：建议先玩一下 [Bloxorz](https://www.crazygames.com/game/bloxorz) 再做本题会跟好。

### 解题思路

前置知识：基本 BFS 模版和足够细心。

本题为一道有趣的 BFS 变形题，细节超多，做了我两个小时才 AC。

不难发现，这就是个升级版迷宫，加入了方块的多种状态，，我们只需升级一下方向数组就行了。

### 代码分析

本题相比其他的 BFS 题目，加入了方块的多种状态所以我们需要新建一个结构体，包含：坐标、状态和步数。随后我们建两个变量标记起点与终点。

然后就是 BFS 了。但是相比与普通的 BFS，本题的判断有在“易碎单元格”且是直立的、越界了、同一状态下走过了就需要 `continue` 掉。

最后是分直立时、横躺时、竖躺时三种情况本别存下来每种状态就可以了。

### 解题代码

具体内容详见 $112$ 行的代码，注释写的很详细了。

```cpp
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int N = 500; 

int n, m, vis[N + 5][N + 5][3], ans = -1;
char a[N + 5][N + 5];
// vis表示这个点有没有来过，a就是这个矩形
// ans设为 -1，最后如果无法达到目标单元格就输出 "Impossible" 

struct State
{
	int x, y, sta, ste;
	// x，y（坐标），state（状态），step（步数） 
	// sta 共3种情况：0：直立   1: 横躺   2: 竖躺
} st, ed; // 起点与终点 

void bfs()
{
	queue<State> q;
	q.push(st);
	while (!q.empty())
	{
		int x = q.front().x, y = q.front().y; // 记录坐标 
		int s = q.front().sta, step = q.front().ste; // 记录状态与当前步数 
		q.pop();
        if (x == ed.x && y == ed.y && s == ed.sta) // 到终点了 
		{
			ans = step;
		    return;
		}
		if (a[x][y] == 'E' && s == 0) continue; // 在“易碎单元格”且是直立的
		if (a[x][y] == '#' || a[x][y + 1] == '#' && s == 1) continue; //越界了
		if (a[x + 1][y] == '#' && s == 2) continue; //越界了 
		if (vis[x][y][s]) continue; //同一状态下走过了
		vis[x][y][s] = 1; //标记走过了
		if (s == 0) //直立时
		{
			q.push({x, y - 2, 1, step + 1});
			q.push({x, y + 1, 1, step + 1});
			q.push({x - 2, y, 2, step + 1});
			q.push({x + 1, y, 2, step + 1});
		}
		else if (s == 1) //横躺时
		{
			q.push({x, y - 1, 0, step + 1});
			q.push({x, y + 2, 0, step + 1});
			q.push({x - 1, y, 1, step + 1});
			q.push({x + 1, y, 1, step + 1});
		}
		else //竖躺时
		{
			q.push({x, y - 1, 2, step + 1});
			q.push({x, y + 1, 2, step + 1});
			q.push({x - 1, y, 0, step + 1});
			q.push({x + 2, y, 0, step + 1});
		}
	}
}

int main()
{
	while (cin >> n >> m && n && m)
	{
		for (int i = 1;i <= n;i++)
			for (int j = 1;j <= m;j++)
				cin >> a[i][j];
		bool flag = false;
		// 找起点 
		for (int i = 1;i <= n;i++)
		{
			for (int j = 1;j <= m;j++)
			{
				if (a[i][j] == 'X')
				{
					if (a[i][j + 1] == 'X') st.sta = 1; //起点是横躺状态
                    else if (a[i + 1][j] == 'X') st.sta = 2; //起点是竖躺状态
                    else st.sta = 0; //起点是直立状态
                    st.x = i, st.y = j;
					flag = true;
					break;
				} 
			}
			if (flag) break;
		 }
		flag = false;
		// 找终点 
		for (int i = 1;i <= n;i++)
		{
			for (int j = 1;j <= m;j++)
			{
				if (a[i][j] == 'O')
				{
					if (a[i][j + 1] == 'O') ed.sta = 1; //终点是横躺状态
                    else if (a[i + 1][j] =='O') ed.sta = 2; //终点是竖躺状态
                    else ed.sta = 0; //终点是直立状态
                    ed.x = i, ed.y = j;
					flag = true;
					break;
				} 
			}
			if (flag) break;
		 } 
		bfs();
		if (ans == -1) cout << "Impossible" << endl;
		else cout << ans << endl;
		memset(vis, 0, sizeof(vis));
		ans = -1;
	}
	return 0;
}
```

---

## 作者：linruichen (赞：1)

这题是一道广搜题，但是细节较多。

首先，模拟出长方形在不同的状态不同的移动方式，与移动完后，长方形移动后的状态，然后，预处理在该坐标，能否放下这个状态的长方形，剩余部分便是基础的广搜。（对于躺着的长方形，横着的我以右边的为头，竖着的我以上方的为头，状态就是只有立的，横的，竖的）。

然后就到了本题坑的地方，判能否可以以该位置为头，放该状态，如果该位为易碎单位，则不能放立的状态，如果该位不能放任何方块，则因将所有有方块在该位的所有状态标记。

看不懂代码有注释，看注释，理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
char b[520][520];
bool a[520][520][4];
int n,m,dx,dy,z,y,x;
struct w{
	int x,y,z,j;
}; 
void s(int x,int y,int z)
{
	queue<w>h;
	h.push((w){x,y,z,0});
	a[x][y][z]=false;
	while(h.size())
	{
		w b=h.front();
		h.pop();
		for(int i=1;i<=4;i++)
		{
			if(b.z==1)//立的状态，行动的方式，与行动后的状态与头。
			{
				int xx[5]={0,1,-2,0,0},yy[5]={0,0,0,1,-2},zz[5]={0,3,3,2,2};
				x=b.x+xx[i],y=b.y+yy[i],z=zz[i];
			}
			else
			if(b.z==2)//横的状态，行动的方式，与行动后的状态与头。
			{
				int xx[5]={0,-1,1,0,0},yy[5]={0,0,0,-1,2},zz[5]={0,2,2,1,1};
				x=b.x+xx[i],y=b.y+yy[i],z=zz[i];
			}
			else
			if(b.z==3)//竖的状态，行动的方式，与行动后的状态与头。
			{
				int xx[5]={0,-1,2,0,0},yy[5]={0,0,0,-1,1},zz[5]={0,1,1,3,3};
				x=b.x+xx[i],y=b.y+yy[i],z=zz[i];
			}
//以上结论皆为模拟得出，手推及可，看不懂的可多看几眼，或尝试自己手推推一遍，增加对代码的理解。
			if(a[x][y][z]&&x>0&&x<=n&&y>0&&y<=m)//基础的广搜。
			{
				a[x][y][z]=false; 
				h.push((w){x,y,z,b.j+1});
				if(x==dx&&y==dy&&z==1)
				{
					printf("%d\n",b.j+1);
					return;
				}
			}
		}
	} 
	printf("Impossible\n");
	return;
}
main(){
	while(scanf("%d%d",&n,&m)==2)
	{
		z=0;
		if(n==0&&m==0)
			return 0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>b[i][j];
		memset(a,true,sizeof(a));
//a数组用于存该位置，能否放下该状态，也就是预处理，判断的方式，也是模拟该状态，能否在该位置。
//手推及可，看不懂的可多看几眼，或尝试自己手推推一遍，增加对代码的理解。 
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				a[i][j][0]=a[i][j][1]=a[i][j][2]=a[i][j][3]=true;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				if(b[i][j]=='#')
					a[i][j][1]=a[i][j][2]=a[i][j][3]=a[i-1][j][3]=a[i][j-1][2]=false;
				else
				if(b[i][j]=='E')
					a[i][j][1]=false;
				else
				if(b[i][j]=='O')
					dx=i,dy=j;
				else
				if(b[i][j]=='X'&&!z)
				{
					if(b[i+1][j]=='X')
						x=i,y=j,z=3;
					else
					if(b[i][j+1]=='X')
						x=i,y=j,z=2;
					else
						x=i,y=j,z=1;					
				}	
			}
		for(int i=1;i<=m;i++)
			a[n][i][3]=false;
		for(int i=1;i<=n;i++)
			a[i][m][2]=false;
		s(x,y,z);
	}
}
```

---

## 作者：Tenil (赞：0)

# Solution

这里是博客：[Tenil](https://www.cnblogs.com/tenil)，有更好的看题体验哦~

## 题意

给定 $(R-2) \times (C-2)$ 棋盘（棋盘可能不全）和起点、终点，问能否将 $1 \times 1 \times 2$ 棋子从起点以特定方式移动到终点，若可以求最小步数。

移动方式：

棋子有直立、竖躺和横躺三种状态，初始为直立，要求到终点时也为直立。

移动时，进行滚动：

>直立：左右移动变横躺，上下移动变竖躺
>
>竖躺：左右移动不变，上下移动变直立
>
>横躺：左右移动变直立，上下移动不变

要求棋子必须完全在棋盘上，且不能在“易碎单元格”上直立。

## 分析 & 实现

求最少步数，典型 bfs 特征了，只是本题的状态比较麻烦。

将上述三状态分别记为：直立（0）、竖躺（1）和横躺（2）。竖躺时，位置记上方一格；横躺时记左侧一格。（这样设计可以让你在读入和特判时都只需将坐标加一，相对统一一点，不容易写错）

先写出转移数组(右、下为正方向)：


```cpp
//ort=0:立   1:竖躺(上面)   2:横躺（左边）     dest:0123 上下左右
const int dx[3][4]{{0,0,-2,1},{0,0,-1,1},{0,0,-1,2}};
const int dy[3][4]{{-2,1,0,0},{-1,2,0,0},{-1,1,0,0}};
const int nxtort[3][4]{{1,1,2,2},{0,0,1,1},{2,2,0,0}};
```

然后转移的时候注意每个朝向的特判：

```cpp
	bool ok=1;
	switch (nxt.o) {
		case 0://不能在“易碎单元格”上直立
			if(board[nxt.x][nxt.y]==2) ok=0;
			break;
		case 1://棋子必须完全在棋盘上
			if(!board[nxt.x][nxt.y+1]) ok=0;
			break;
		case 2:
			if(!board[nxt.x+1][nxt.y]) ok=0;
			break;
	}
	if(!ok) continue;
```

然后本题其实也就写完了（乐）。

## Code

读入可能有点抽象，还请见谅。

```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;

typedef long long ll;

ll fr() {
	ll x=0,f=1;char c=getchar();
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)) {
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}

const int maxn=501;
//ort=0:立   1:竖躺(上面)   2:横躺（左边）     dest:0123 上下左右
const int dx[3][4]{{0,0,-2,1},{0,0,-1,1},{0,0,-1,2}};
const int dy[3][4]{{-2,1,0,0},{-1,2,0,0},{-1,1,0,0}};
const int nxtort[3][4]{{1,1,2,2},{0,0,1,1},{2,2,0,0}};

int r,c,sx,sy,so,ex,ey;
int board[maxn][maxn];
//0空 1硬 2碎
bool vis[maxn][maxn][3];

struct att{
	int x,y,o,step=0;
};

int main() {
	r=fr();c=fr();
	while(r) {
		sx=sy=so=ex=ey=0;
		queue<att> q;
		memset(vis,0,sizeof(vis));
		memset(board,0,sizeof(board));//多测要清空！
		string str;getline(cin,str);//先吃一行#
		bool flag=0;
		for(int i = 1; i <= r-2; i++) {
			getchar();//行首#
			char cc;
			for(int j = 1; j <= c-2; j++) {
				cc=getchar();
				if(cc=='#') continue;
				if(cc=='.') board[j][i]=1;
				else if(cc=='E') board[j][i]=2;
				else if(cc=='X') {
					if(!sx) {
						sx=j,sy=i;
					}
					else {
						if(sx==j-1) so=2;
						if(sy==i-1) so=1;
					}
					board[j][i]=1;
				}
				else if(cc=='O') {
					ex=j,ey=i;board[j][i]=1;
				}
			}
			getchar();getchar();//行末#和换行符
		}
		getline(cin,str);
		q.push((att){sx,sy,so,0});
		while(!q.empty()) {
			att now=q.front();
			q.pop();
			if(now.x==ex&&now.y==ey&&now.o==0) {
				printf("%d\n",now.step);flag=1;
				break;
			}
			for(register int i = 0; i < 4; i++) {
				att nxt=(att){now.x,now.y,now.o,now.step+1};
				nxt.x+=dx[now.o][i];
				nxt.y+=dy[now.o][i];
				nxt.o=nxtort[now.o][i];
				if(nxt.x<1||nxt.x>c-2||nxt.y<1||nxt.y>r-2||!board[nxt.x][nxt.y]) continue;
				if(vis[nxt.x][nxt.y][nxt.o]) continue;
				bool ok=1;
				switch (nxt.o) {
					case 0:
						if(board[nxt.x][nxt.y]==2) ok=0;
						break;
					case 1:
						if(!board[nxt.x][nxt.y+1]) ok=0;
						break;
					case 2:
						if(!board[nxt.x+1][nxt.y]) ok=0;
						break;
				}
				if(!ok) continue;
				vis[nxt.x][nxt.y][nxt.o]=1;
				q.push(nxt);
			}
		}
		if(!flag) printf("Impossible\n");
		r=fr();c=fr();
	}
	return 0;
}
```

## 闲话

如果觉得有用，还请点个赞吧！

---

## 作者：ZinfI_Sh (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10485)

不同于其他题解的是，这里不使用 $3$ 种状态表示一个立方体，而是用~~复杂而冗余的~~ $4$ 种状态表示。

我们用一个四元组 $(x,y,dx,dy)$ 表示一个立方体，表示**源点为 $(x,y)$，$x$ 延展 $dx$ 步，$y$ 延展 $dy$ 步。**

为了方便讲解，我们将诸如“$x$ 延展 $dx$ 步，$y$ 延展 $dy$ 步”的话说成**往 $(dx,dy)$ 方向延展 / 走**。

比如如下两个立方体的状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/axh44z7j.png)

从左至右两个立方体状态分别是 $(5,1,0,0)$ 和 $(2,4,0,-1)$。

接下来考虑如何处理移动立方体。

分类讨论一下，总计 $11$ 种状态。我们先设我们要往 $(mx,my)$ 方向走，且为了方便把往 $y$ 的正和负方向走分别称为往上和往下走，把往 $x$ 的正和负方向走分别称为往左和往右走，

## 第一大类

当立方体为立着的（$dx=dy=0$）， 此时只要变成 $(x+mx,y+my,mx,my)$ 的状态就好了。

## 第二大类

当立方体为躺着的，而 $dx=0$ 且 $my=0$，或是 $dy=0$ 且 $mx=0$（上下延展并往左右走或左右延展并往上下走），此时 $(dx,dy)$ 状态不变，只要将 $x$ 和 $y$ 分别加上 $mx$ 和 $my$ 就好了。

## 第三大类

当立方体为躺着的，而 $dx=0$ 且 $mx=0$，或是 $dy=0$ 且 $my=0$（上下延展并往上下走或左右延展并往左右走），此时又要分两大类讨论。两种可能性为**源点偏移动方向**和**源点偏移动方向的对立方向**。

![](https://cdn.luogu.com.cn/upload/image_hosting/f3nao6lc.png)

上面的两个立方体都是往下走，两个分别将 $y$ 移动 $-1$ 和 $-2$ 步，$dx$ 和 $dy$ 设为 $0$ 就好了。

再讨论一下剩下 $6$ 种方向，剩下的套 bfs 板子就好了。

# AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define lowbit(x) (x & -x)
using namespace std;
const int DM[8][2] = {0, 1, 0, -1, 1, 0, -1, 0, 1, 1, 1, -1, -1, 1, -1, -1};
const int HASHMOD = 9223372036854775783;
const int HASHBASE = 131;
const int HASHITEM = 999997;
inline void read(int &res)
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    res = x * f;
}
struct Pos
{
    int x, y, dx, dy, t;
};
int n, m;
string g[501];
bool limit_pos(int x, int y)
{
    return (y >= 1 && y <= n && x >= 1 && x <= m);
}
bool check(int x, int y, int dx, int dy)
{
    if (!(limit_pos(x, y) && limit_pos(x + dx, y + dy)))
    {
        return 0;
    }
    if (dx == 0 && dy == 0)
    {
        if (g[y][x] != '#' && g[y][x] != 'E')
        {
            return 1;
        }
    }
    else
    {
        if (g[y][x] != '#' && g[y + dy][x + dx] != '#')
        {
            return 1;
        }
    }
    return 0;
}
const int FIX = 2;
bool vis[501][501][4][4];
queue<Pos> q;
int bfs(int sx, int sy, int sdx, int sdy)
{
    int ans = 1145141919810;
    memset(vis, 0, sizeof(vis));
    q.push({sx, sy, sdx, sdy, 0});
    vis[sy][sx][sdy + FIX][sdx + FIX] = 1;
    while (q.size())
    {
        Pos u = q.front();
        q.pop();
        // cout << u.x << ' ' << u.y << ' ' << u.dx << ' ' << u.dy << '\n';
        for (int i = 0; i <= 3; i++)
        {
            int dx = DM[i][0], dy = DM[i][1], tdx = u.dx, tdy = u.dy, tx = u.x, ty = u.y;
            if (u.dx == 0 && u.dy == 0)
            {
                tdx = dx;
                tdy = dy;
                tx += dx;
                ty += dy;
            }
            else
            {
                if (u.dx == 0 && dy == 0)
                {
                    tx += dx;
                }
                else if (u.dy == 0 && dx == 0)
                {
                    ty += dy;
                }
                else if ((u.dx == 0 && dx == 0) || (u.dy == 0 && dy == 0))
                {
                    tdx = tdy = 0;
                    if (u.dy == -1 && dy == -1)
                    {
                        ty -= 2;
                    }
                    else if (u.dy == 1 && dy == -1)
                    {
                        ty -= 1;
                    }
                    else if (u.dy == -1 && dy == 1)
                    {
                        ty += 1;
                    }
                    else if (u.dy == 1 && dy == 1)
                    {
                        ty += 2;
                    }
                    else if (u.dx == -1 && dx == -1)
                    {
                        tx -= 2;
                    }
                    else if (u.dx == 1 && dx == -1)
                    {
                        tx -= 1;
                    }
                    else if (u.dx == -1 && dx == 1)
                    {
                        tx += 1;
                    }
                    else if (u.dx == 1 && dx == 1)
                    {
                        tx += 2;
                    }
                }
            }
            if (!vis[ty][tx][tdy + FIX][tdx + FIX] && check(tx, ty, tdx, tdy))
            {
                // cout << "    " << tx << ' ' << ty << ' ' << tdx << ' ' << tdy << '\n';
                vis[ty][tx][tdy + FIX][tdx + FIX] = 1;
                q.push({tx, ty, tdx, tdy, u.t + 1});
                if (tdx == 0 && tdy == 0 && g[ty][tx] == 'O')
                {
                    ans = min(ans, u.t + 1);
                }
            }
        }
    }
    return ((ans == 1145141919810) ? -1 : ans);
}
signed main()
{
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0)
        {
            break;
        }
        int sx, sy, dx = 0, dy = 0;
        bool xsum = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> g[i];
            g[i] = ' ' + g[i];
            for (int j = 1; j <= m; j++)
            {
                if (g[i][j] == 'X')
                {
                    if (!xsum)
                    {
                        xsum = 1;
                        sx = j, sy = i;
                    }
                    else
                    {
                        dx = j - sx, dy = i - sy;
                    }
                }
            }
        }
        int tmp = bfs(sx, sy, dx, dy);
        if (tmp == -1)
        {
            cout << "Impossible\n";
        }
        else
        {
            cout << tmp << '\n';
        }
    }
    return 0;
}
```

---

