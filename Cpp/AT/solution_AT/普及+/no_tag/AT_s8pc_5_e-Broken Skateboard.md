# Broken Skateboard

## 题目描述

编码员 E869120 正在考虑去溜冰场，溜冰场的大小为 $H \times W$ 。左上角单元格为 $(1,1)$ ，右下角单元格为 $(H,W)$ 。  
溜冰场由 $1$ 个球门单元格、一些冰单元格和一些混凝土单元格组成。

溜冰场的特征如下：

- 滑冰者在冰格上移动时方向一致。
- 滑冰者只有在停止时才能改变方向。
- 如果滑冰者滑到了球门单元，他/她就完成了比赛。但是，如果滑冰者来到滑冰场外，则无法完成游戏。

此外，他的滑板坏了，因此移动速度会发生如下变化：

- 移动一个格子需要 $k$ 秒。最初， $k$ 为 $1$ 。
- 如果滑板滑到水泥格上， $k$ 将增加 $1$ 。
- 他只能向 4 个方向移动：上、下、左、右。

他想知道每个起始格完成游戏所需的最短时间。  
请写出代替 E869120 的程序。

## 说明/提示

- $1 \leq H \leq 777$ .
- $1 \leq W \leq 777$ .
- 具体单元的数量不超过 $7 \ 777$ 。
- 目标单元的数量正好是 $1$ 。

## 样例 #1

### 输入

```
6 6
......
.#....
......
......
......
...#.G```

### 输出

```
-1 -1 -1 9 -1 5
-1 -1 -1 8 -1 4
-1 -1 -1 7 -1 3
-1 -1 -1 6 -1 2
-1 -1 -1 5 -1 1
7 6 5 2 1 0```

## 样例 #2

### 输入

```
1 8
#####G##```

### 输出

```
15 10 6 3 1 0 1 3```

## 样例 #3

### 输入

```
9 9
....#..#.
#........
....#....
.#......#
...###...
##....#.#
....#...#
#....#...
.#.#..#.G```

### 输出

```
54 37 52 29 38 38 17 53 18
43 36 60 28 37 37 16 65 17
40 35 38 27 26 36 15 39 16
35 22 21 20 19 18 14 16 10
28 27 26 16 16 25 13 36 9
28 17 16 15 14 13 7 9 5
18 17 16 14 8 7 6 5 2
41 22 52 13 15 37 5 51 1
22 14 13 7 6 5 2 1 0```

# 题解

## 作者：COsm0s (赞：0)

最短路好题。

题目求所有点到终点的最短路，不妨转换成从终点开始拓展。但是这样有个小问题，就是水泥格的处理。

我们发现走到设为 $(i,j)$ 的水泥格后，$(i,j)\to (ex,ey)$ 的路径上，每条边加一。再次转化为每次走到一个水泥格对答案的贡献即为**从当前点到终点的边数**。

那只要在跑搜索的时候多记录一维当前点到终点的边数即可。

然后就是一个非常经典的记搜，也就是记录当前点坐标以及从哪个方向进入当前点，直接 BFS 即可。


```cpp
int dx[4] = {0, 1, -1, 0};
int dy[4] = {-1, 0, 0, 1};
struct State {
  int x, y, d;
  int c;
  int w;
};
string S[778];
int len[778][778][5];
void Solve() {
  int H, W;
  cin >> H >> W;
  int res = 0;
  int gx, gy;
  for (int i = 0; i < H; i++) {
    cin >> S[i];
    for (int j = 0; j < W; j++) {
      for (int k = 0; k < 4; k++) len[i][j][k] = (1ll << 60);
      if (S[i][j] == 'G') {
        gx = i;
        gy = j;
      }
    }
  }
  queue<State> qu;
  State cur;
  cur.x = gx;
  cur.y = gy;
  cur.c = 0;
  cur.w = 0;
  for (int k = 0; k < 4; k++) {
    cur.d = k;
    qu.push(cur);
  }
  State ne;
  while (qu.size()) {
    cur = qu.front();
    qu.pop();
    if (cur.x < 0 || cur.x >= H || cur.y < 0 || cur.y >= W) continue;
    if (len[cur.x][cur.y][cur.d] > cur.w) {
      len[cur.x][cur.y][cur.d] = cur.w;
      if (S[cur.x][cur.y] != '#') {
        ne.x = cur.x + dx[cur.d];
        ne.y = cur.y + dy[cur.d];
        ne.d = cur.d;
        ne.w = cur.w + 1;
        ne.c = cur.c + 1;
        qu.push(ne);
      } else {
        for (int k = 0; k < 4; k++)
          len[cur.x][cur.y][k] = min(len[cur.x][cur.y][k], cur.w);
        ne.w = cur.w + cur.c + 1;
        ne.c = cur.c + 1;
        for (int k = 0; k < 4; k++) {
          if ((k + cur.d != 3)) {
            ne.x = cur.x + dx[k];
            ne.y = cur.y + dy[k];
            ne.d = k;
            qu.push(ne);
          }
        }
      }
    }
  }
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      int mn = min(min(len[i][j][0], len[i][j][1]), min(len[i][j][2], len[i][j][3]));
      if (mn == (int)1ll << 60) mn = -1;
      cout << mn << ' ';
    }
    cout << '\n';
  }
}
```

---

## 作者：liuliucy (赞：0)

考虑从终点开始倒着搜，难点就在记录经过井号的时间。

发现经过井号 $k$ 只会加一，所以我们记录从终点到当前点的距离，每次经过井号将 $t+dist$，跑记忆化广搜即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001][1001];
int n,m;
struct xx{
	int len,dist,x,y,w;
};
const int dx[]={1,-1,0,0},
		  dy[]={0,0,1,-1};
queue<xx>q;
int f[4][1001][1001];
int stx,sty;
void bfs(){
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<4;i++)q.push({0,0,stx,sty,i}),f[i][stx][sty]=0;
	while(!q.empty()){
		auto [len,dist,x,y,w]=q.front();q.pop();
		for(int i=0;i<4;i++){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<1||nx>n||ny<0||ny>m)continue;
			if(a[x][y]==0&&w==i){
				if(f[w][nx][ny]>dist+len+1){
					f[w][nx][ny]=dist+len+1;
					q.push(xx{len+1,dist,nx,ny,w});
				}
			}
			else if(a[x][y]==1){
				if(f[i][nx][ny]>dist+2*len+1){
					f[i][nx][ny]=dist+2*len+1;
					q.push(xx{len+1,dist+len,nx,ny,i});
				}
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char s=getchar();
			while(s!='.'&&s!='#'&&s!='G')s=getchar();
			if(s=='G')a[i][j]=0,stx=i,sty=j;
			if(s=='#')a[i][j]=1;
		}
	}
	bfs();
	for(int i=1;i<=n;i++,putchar('\n')){
		for(int j=1;j<=m;j++){
			int ans=1e9;
			for(int k:{0,1,2,3})ans=min(ans,f[k][i][j]);
			printf("%d ",ans<1e9?ans:-1);
		}
	}

}
```

---

