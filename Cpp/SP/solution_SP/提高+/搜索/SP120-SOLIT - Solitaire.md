# SOLIT - Solitaire

## 题目描述

Solitaire是一款在8x8棋盘上玩的游戏。棋盘的行和列分别为1到8，从顶部到底部以及从左到右依次编号。
棋盘上有4个相同的棋子。在每一次移动中，一个棋子可以：
- 移动一格到一个相邻的空格（向上、向下、向左或向右）
- 跳过另一个相邻的棋子到与之相邻一个空格（向上、向下、向左或向右）

## 样例 #1

### 输入

```
1
4 4 4 5 5 4 6 5
2 4 3 3 3 6 4 6```

### 输出

```
YES```

# 题解

## 作者：2c_s (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/SP120)

## 思路

其实这题不用双向广搜也能过，看似时间复杂度很大，会超时，实际上有很多不能走的情况，所以时间复杂度远小于它，可以在 $1.5\mathrm{s}$ 内跑过。这题时间限制是不准的，比 $896\mathrm{ms}$ 要大。

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
    int T=read();
	while(T--){
		memset(vis,0,sizeof vis);
		memset(mp,0,sizeof mp);
		a.step=0;//当前步数也清零。
		for(int i=1;i<=4;++i)a.x[i]=read(),a.y[i]=read();
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

遍历当前每个棋子位置，如果有一个棋子没在其中任何一个目标位置，那么肯定没走完。

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
    int T=read();
	while(T--){
		memset(vis,0,sizeof vis);
		memset(mp,0,sizeof mp);
		a.step=0;
		for(int i=1;i<=4;++i)a.x[i]=read(),a.y[i]=read();
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

[AC 记录](https://www.luogu.com.cn/record/166283984)

---

## 作者：meifan666 (赞：1)

先分享一下本题的[双倍经验](https://www.luogu.com.cn/problem/UVA1724)。
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
int T;
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
	cin>>T; 
	while(T--){
		memset(vis,0,sizeof(vis));
		memset(aaa,-1,sizeof(aaa));
		memset(bbb,-1,sizeof(bbb));
		ok=0;
		for(int i=1;i<=4;i++){
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

## 作者：封禁用户 (赞：1)

本题是 UVA1724 的双倍经验。

如果直接 bfs，就会有 $16^8$（走 $8$ 步，每步有 $16$ 种选择）种状态，会 TLE。所以考虑采用更高效的双向广搜。

那怎么双向广搜呢？我们可以从起点和终点交替搜索，标记棋子走过的位置。如果发现重复了，就说明起点出发的这条路径就能和终点接上。如果超过 $8$ 步还没接上就是无解了。

---

## 作者：rainbow_cat (赞：0)

数据范围很小，考虑直接直接搜素，枚举量为 $(4 \times 4)^8$，超时。   
这里使用双向搜索，从起始状态和终止状态分别搜索 $4$ 步，状态可以用哈希记录，如果状态有重合则有解。   
因此枚举量为 $2 \times (4 \times 4)^4$，即 $2^{17}$。  
代码过于丑陋，这里就不展示了。

---

## 作者：qinmingze (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/SP120)

### 思路

#### 1. 方法

这是一道搜索题。

首先我们考虑爆搜，根据题目，我们有 $4$ 颗棋子，每个棋子总共有 $4$ 种走法，总步数要在 $8$ 步之内，那么程序最多就会运算 $16^8$，理论上是会超时的。

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

注意：在新的状态入队后，我们需要对我们刚刚改变了值的数组进行**还原操作**。

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
	cin >> T;
	while(T--){ 
		for(int i = 1; i <= 4; i++) cin >> a[i].fi >> a[i].se;
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

