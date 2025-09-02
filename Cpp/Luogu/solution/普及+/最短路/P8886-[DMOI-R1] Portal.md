# [DMOI-R1] Portal

## 题目背景

出题人正在玩一款叫 Portal 的游戏。但由于他太菜了，于是找来了你，让你帮他过几个他过不去的关卡。

什么？你说你不会玩？

玩家需要通过传送门枪到达出口。利用传送门枪射击可开出两种门，分别是橙色门和蓝色门，两面都可作入口及出口。在创造门的时候，另一道同样颜色的门会消失，即是说同时间不可能存在两道同色的门，最多只可同时存在一道蓝色及一道橙色的门。

两道传送门在三维空间之中的两个地点创造出视觉上及物理上的连系，传送门的立点只限于平面，玩家从门出来时会自动配合地心吸力调整身体水平。

出题人把所有希望都寄托于你身上了哟。哦，对了，因为出题人是个白嫖党，因此他拥有的是盗版 Portal。

## 题目描述

在一个 $n \times n$ 的二维平面图上，用 $(x,y)$ 表示地图第 $x$ 行第 $y$ 列。每个点都是墙、虚空和地面中的一种，分别用 `#`，`*`，`.` 表示。玩家只能站在地面上。**地图之外都是墙。**

你手里有一个传送门枪，可以发射蓝色和橙色的传送门，只能朝上下左右四个方向使用。

在选定一个方向和颜色后，将会在该方向上第一个碰到的墙的墙面上建造选定颜色的传送门，并摧毁之前建造的这种颜色的传送门。两种颜色的传送门不能被建立在同一墙面。

玩家可以朝上下左右四个方向的空地移动。玩家还可以在不同色传送门之间穿梭。假如玩家朝一堵墙移动并且墙面上有传送门，并且当前已经建立了两个传送门，那么会从另一个传送门出来（必须保证出来也站在陆地上）。

出来的时候，玩家会站在另一个门外的空地上，**四个方向都可以。**

一开始玩家站在 $(1,1)$，目的地是 $(n,n)$。求最少使用多少次传送门枪才能到达目的地。

**注意哦，这里的使用指的是穿过多少面传送门。**

## 说明/提示

### 样例1解释

我们用白色格子表示空地，黑色格子表示墙，蓝色格子表示蓝色传送门，橙色格子表示橙色传送门，可以画出第一局的如下地图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s16tq3vq.png)

走到橙色传送门处，从橙色传送门进入，蓝色传送门出即可。

而第二局地图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/v7q0izdk.png)


走到蓝色传送门处，从蓝色传送门进入，橙色传送门出即可。

### 数据范围

对于 $20\%$ 的数据，$n \le 10$。

对于 $60\%$ 的数据，$n \le 100$。

对于另外 $10\%$ 的数据，$T=1$ 且不存在虚空。

对于 $100\%$ 的数据，$2 \le n \le 500$，$1 \le T \le 10$。

## 样例 #1

### 输入

```
2
5
..###
#.#.#
#..##
...#.
.###.
5
..#..
##..#
#.#..
..#..
.#...```

### 输出

```
2
2```

## 样例 #2

### 输入

```
4
5
...*.
*##*.
#..*.
#*###
.....
5
.#*..
.**.#
###.*
***.*
**...
5
.**..
***.#
###.*
***.*
*****
5
.**..
***.#
###..
***.*
***..```

### 输出

```
4
2
```

## 样例 #3

### 输入

```
见下发文件portal1.in```

### 输出

```
见下发文件portal1.ans```

## 样例 #4

### 输入

```
见下发文件portal2.in```

### 输出

```
见下发文件portal2.ans```

# 题解

## 作者：andychen_2012 (赞：6)

# 【DMOI 官方题解】

## 解题思路

### 部分分

额，出题人想着第一档部分分应该是乱做吧？暴力 dfs 就行了。而第二档部分分，也就是 $60\%$ 的，应该就是 dfs 加上一些剪枝，或者 01bfs 没有实现好的同学吧。

### 正解

我们要求的是传送门枪最少使用次数，因此我们不用管走路。所以我们可以将每个连通的空地视为一个连通块。

那么我们就是要看如果要从起点所在的连通块走到终点所在的连通块至少要经过多少连通块。

我们可以发现，如果我们想要从一个连通块抵达另一个连通块，这两个连通块之间必须存在一个地方仅存在一个墙壁,如 `..#..` 左右两个连通块可互相抵达，但 `..##..` 左右两个连通块就不可互相抵达。

不过我们要思考下面这么一个情况：

```
.***.
*.#..
****#
*..#.
****.
```

我们用数字表示不同的连通块，一个连通块的空地用同一个数字表示。

```
1***2
*3#22
****#
*44#5
****5
```

但我们别忘了地图外面也都是墙，因此我们的真正的地图如下：

```
#######
#1***2#
#*3#22#
#****##
#*44#5#
#****5#
#######
```

我们可以发现有如下连通块到达关系，其中 $i \to j$ 表示连通块 $i$ 可以到达连通块 $j$：

```
1 -> 2
2 -> 1
2 -> 3
2 -> 4
2 -> 5
4 -> 2
4 -> 3
5 -> 2
5 -> 4
```

我们发现连通块 2 和 3 之间存在一个地方只有一个墙间隔，但是 3 不能到 2 ， 2 可以到 3 ，因为 3 旁边除了一堵墙以外都是虚空，无法建立两个不同颜色的传送门，但 2 可以。

还是上面那个例子，注意连通块 4 可以抵达连通块 2 和 3，因为传送门是可以穿过虚空的，但是 4 不可以抵达连通块 5，因为不能在虚空中走路。

还要注意，不能在一堵墙上建两面传送门。

想清楚了以上情况后，我们就有一个清晰的思路，可以建立出来一个有向图，$i \to j$ 表示连通块 $i$ 可以抵达连通块 $j$，每条边的边权都为 $1$，要求的就是起点所在连通块到终点所在连通块的最短距离，就如上图，我们选择 $1 \to 2,2 \to 5$ 两条边即可到达终点所在连通块。

当然，你也可以采用 01bfs 的方式，不建图跑，但这样的话可能需要进行一定的剪枝，不过如果实现得比较好的话，不剪枝也可以过。

不过代码实现上要考虑到的还是挺多的。

## 解题代码

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
inline int read(){
	int x=0;
	int ch=getchar(),f=0;
	while(ch<48||ch>57) f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return f?-x:x;
}
inline void write(int x,char end='\n'){
	if(x==0){
		putchar('0');
		putchar(end);
		return;
	}
	if(x<0) putchar('-'),x=-x;
	int st[70],sr=0;
	while(x){
		st[sr++]=x%10;
		x/=10;
	}
	while(sr--) putchar(st[sr]+48);
	putchar(end);
	return;
}
const int N=2005,INF=2e9;
const int M=2500005,M2=5000005;
const int dx[4]={0,1,-1,0},dy[4]={1,0,0,-1};
int n;
char s[N][N];
int dis[N];
int col[N][N];
int head,tail;
struct node{
    int x,y;
};
struct edge{
	int to,nxt;
}e[M2];
int hd[M2],ecnt;
inline void add(int u,int v){
	e[++ecnt].to=v;
	e[ecnt].nxt=hd[u];
	hd[u]=ecnt;
}
node q[M2];
int cango[10],only[M2][2];
#define mp make_pair
map<pair<int,int>,bool> mps;
inline void bfs(){
	int cnt=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(s[i][j]=='.'&&!col[i][j]){
				head=1,tail=0;
				++cnt;
				q[++tail]=(node{i,j});
				while(head<=tail){
					node h=q[head++];
					int x=h.x,y=h.y;
					col[x][y]=cnt;
					for(int i=0;i<4;++i){
						int tx=x+dx[i],ty=y+dy[i];
						if(s[tx][ty]!='.') continue;
						if(!col[tx][ty]){
							col[tx][ty]=cnt;
							q[++tail]=(node{tx,ty});
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=cnt;++i) only[i][0]=only[i][1]=-1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(col[i][j]){
				int g=col[i][j];
				if(s[i-1][j]=='#'){
					if(only[g][0]==-1){
						only[g][0]=i-1;
						only[g][1]=j;
					}
					else
						only[g][0]=only[g][1]=-2;
				}
				if(s[i+1][j]=='#'){
					if(only[g][0]==-1){
						only[g][0]=i+1;
						only[g][1]=j;
					}
					else
						only[g][0]=only[g][1]=-2;
				}
				if(s[i][j-1]=='#'){
					if(only[g][0]==-1){
						only[g][0]=i;
						only[g][1]=j-1;
					}
					else
						only[g][0]=only[g][1]=-2;
				}
				if(s[i][j+1]=='#'){
					if(only[g][0]==-1){
						only[g][0]=i;
						only[g][1]=j+1;
					}
					else
						only[g][0]=only[g][1]=-2;
				}
			}
		}
	}
	for(int i=0;i<=n+1;++i){
		for(int j=0;j<=n+1;++j){
			if(s[i][j]=='#'){
//				printf("now judging:%d %d\n",i,j);
				for(int k=1;k<=4;++k) cango[k]=-1;
				bool nowflag=0;
				if(i<n&&col[i+1][j]) cango[1]=col[i+1][j],nowflag=1;
				if(i>1&&col[i-1][j]) cango[2]=col[i-1][j],nowflag=1;
				if(j<n&&col[i][j+1]) cango[3]=col[i][j+1],nowflag=1;
				if(j>1&&col[i][j-1]) cango[4]=col[i][j-1],nowflag=1;
				if(!nowflag) continue;
				for(int k=j-1;k>=1&&s[i][k]!='#';--k){
					int c=col[i][k];
					if(c){
						for(int l=1;l<=4;++l){
							if(cango[l]==-1) continue;
							if(c==cango[l]) continue;
							if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
							if(only[c][0]==-1) continue;
							if(k==j-1){
								if(only[cango[l]][0]==-2){
									if(!mps[mp(cango[l],c)]){
										mps[mp(cango[l],c)]=1;
										add(cango[l],c);
//										printf("%d %d\n",cango[l],c);
									}
								}
								continue;
							}
							if(only[c][0]==i&&only[c][1]==j) continue;
							if(mps[mp(c,cango[l])]) continue;
							mps[mp(c,cango[l])]=1;
							add(c,cango[l]);
//							printf("%d %d\n",c,cango[l]);
						}
					}
				}
				for(int k=j+1;k<=n&&s[i][k]!='#';++k){
					int c=col[i][k];
					if(c){
						for(int l=1;l<=4;++l){
							if(cango[l]==-1) continue;
							if(c==cango[l]) continue;
							if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
							if(only[c][0]==-1) continue;
							if(k==j+1){
								if(only[cango[l]][0]==-2){
									if(!mps[mp(cango[l],c)]){
										mps[mp(cango[l],c)]=1;
										add(cango[l],c);
//										printf("%d %d\n",cango[l],c);
									}
								}
								continue;
							}
							if(only[c][0]==i&&only[c][1]==j) continue;
							if(mps[mp(c,cango[l])]) continue;
							mps[mp(c,cango[l])]=1;
							add(c,cango[l]);
//							printf("%d %d\n",c,cango[l]);
						}
					}
				}
				for(int k=i-1;k>=1&&s[k][j]!='#';--k){
					int c=col[k][j];
					if(c){
						for(int l=1;l<=4;++l){
							if(cango[l]==-1) continue;
							if(c==cango[l]) continue;
							if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
							if(only[c][0]==-1) continue;
							if(k==i-1){
								if(only[cango[l]][0]==-2){
									if(!mps[mp(cango[l],c)]){
										mps[mp(cango[l],c)]=1;
										add(cango[l],c);
//										printf("%d %d\n",cango[l],c);
									}
								}
								continue;
							}
							if(only[c][0]==i&&only[c][1]==j) continue;
							if(mps[mp(c,cango[l])]) continue;
							mps[mp(c,cango[l])]=1;
							add(c,cango[l]);
//							printf("%d %d\n",c,cango[l]);
						}
					}
				}
				for(int k=i+1;k<=n&&s[k][j]!='#';++k){
					int c=col[k][j];
					if(c){
						for(int l=1;l<=4;++l){
							if(cango[l]==-1) continue;
							if(c==cango[l]) continue;
							if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
							if(only[c][0]==-1) continue;
							if(k==i+1){
								if(only[cango[l]][0]==-2){
									if(!mps[mp(cango[l],c)]){
										mps[mp(cango[l],c)]=1;
										add(cango[l],c);
//										printf("%d %d\n",cango[l],c);
									}
								}
								continue;
							}
							if(only[c][0]==i&&only[c][1]==j) continue;
							if(mps[mp(c,cango[l])]) continue;
							mps[mp(c,cango[l])]=1;
							add(c,cango[l]);
//							printf("%d %d\n",c,cango[l]);
						}
					}
				}
			}
		}
	}
	dis[1]=0;
	for(int i=2;i<=cnt;++i) dis[i]=INF;
	priority_queue<pair<int,int> > q2;
	q2.push(mp(0,1));
	while(!q2.empty()){
		int u=q2.top().second;
		q2.pop();
		for(int i=hd[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q2.push(mp(-dis[v],v));
			}
		}
	}
	mps.clear();
	for(int i=1;i<=ecnt;++i) e[i]=edge{0,0};
	ecnt=0;
	for(int i=1;i<=cnt;++i) hd[i]=0;
	cnt=0;
}
int main(){
    int T=read();
    while(T--){
    	n=read();
        for(int i=1;i<=n;i++)
            scanf("%s",s[i]+1);
        if(s[1][1]!='.'||s[n][n]!='.')
            return 0;
        for(int i=0;i<=n+1;++i)
        	for(int j=0;j<=n+1;++j)
        		col[i][j]=0;
        for(int i=0;i<=n+1;++i) s[i][0]=s[i][n+1]='#';
        for(int i=0;i<=n+1;++i) s[0][i]=s[n+1][i]='#';
		bfs();
//        for(int i=0;i<=n+1;++i){
//        	for(int j=0;j<=n+1;++j){
//        		printf("%d ",col[i][j]);
//			}
//			puts("");
//		}
        if(dis[col[n][n]]==INF) puts("-1");
        else printf("%d\n",dis[col[n][n]]*2);
    }
    return 0;
}
```

### 后记

其实一开始出题人 std 挂掉了，漏考虑了一次判断，结果新造的数竟然卡不掉错误的 std，在写题解时才发现自己手造的数据使得原来的 std 挂了。

在经过许多次对拍后发现卡不掉这种错法，只好作罢，把原 std 贴出来，希望各位能够把它给 hack 掉：

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
inline int read(){
	int x=0;
	int ch=getchar(),f=0;
	while(ch<48||ch>57) f=(ch=='-'),ch=getchar();
	while(ch>47&&ch<58) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return f?-x:x;
}
inline void write(int x,char end='\n'){
	if(x==0){
		putchar('0');
		putchar(end);
		return;
	}
	if(x<0) putchar('-'),x=-x;
	int st[70],sr=0;
	while(x){
		st[sr++]=x%10;
		x/=10;
	}
	while(sr--) putchar(st[sr]+48);
	putchar(end);
	return;
}
const int N=2005,INF=2e9;
const int M=2500005,M2=5000005;
const int dx[4]={0,1,-1,0},dy[4]={1,0,0,-1};
int n;
char s[N][N];
int dis[N];
int col[N][N];
int head,tail;
struct node{
    int x,y;
};
struct edge{
	int to,nxt;
}e[M2];
int hd[M2],ecnt;
inline void add(int u,int v){
	e[++ecnt].to=v;
	e[ecnt].nxt=hd[u];
	hd[u]=ecnt;
}
node q[M2];
int cango[10],only[M2][2];
#define mp make_pair
map<pair<int,int>,bool> mps;
inline void bfs(){
	int cnt=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(s[i][j]=='.'&&!col[i][j]){
				head=1,tail=0;
				++cnt;
				q[++tail]=(node{i,j});
				while(head<=tail){
					node h=q[head++];
					int x=h.x,y=h.y;
					col[x][y]=cnt;
					for(int i=0;i<4;++i){
						int tx=x+dx[i],ty=y+dy[i];
						if(s[tx][ty]!='.') continue;
						if(!col[tx][ty]){
							col[tx][ty]=cnt;
							q[++tail]=(node{tx,ty});
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=cnt;++i) only[i][0]=only[i][1]=-1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(col[i][j]){
				int g=col[i][j];
				if(s[i-1][j]=='#'){
					if(only[g][0]==-1){
						only[g][0]=i-1;
						only[g][1]=j;
					}
					else
						only[g][0]=only[g][1]=-2;
				}
				if(s[i+1][j]=='#'){
					if(only[g][0]==-1){
						only[g][0]=i+1;
						only[g][1]=j;
					}
					else
						only[g][0]=only[g][1]=-2;
				}
				if(s[i][j-1]=='#'){
					if(only[g][0]==-1){
						only[g][0]=i;
						only[g][1]=j-1;
					}
					else
						only[g][0]=only[g][1]=-2;
				}
				if(s[i][j+1]=='#'){
					if(only[g][0]==-1){
						only[g][0]=i;
						only[g][1]=j+1;
					}
					else
						only[g][0]=only[g][1]=-2;
				}
			}
		}
	}
	for(int i=0;i<=n+1;++i){
		for(int j=0;j<=n+1;++j){
			if(s[i][j]=='#'){
//				printf("now judging:%d %d\n",i,j);
				for(int k=1;k<=4;++k) cango[k]=-1;
				if(i<n&&col[i+1][j]) cango[1]=col[i+1][j];
				if(i>1&&col[i-1][j]) cango[2]=col[i-1][j];
				if(j<n&&col[i][j+1]) cango[3]=col[i][j+1];
				if(j>1&&col[i][j-1]) cango[4]=col[i][j-1];
				for(int k=j-1;k>=1&&s[i][k]!='#';--k){
					int c=col[i][k];
					if(c){
						for(int l=1;l<=4;++l){
							if(cango[l]==-1) continue;
							if(c==cango[l]) continue;
							if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
							if(only[c][0]==-1) continue;
							if(k==j-1){
								if(only[cango[l]][0]==-2){
									if(!mps[mp(cango[l],c)]){
										mps[mp(cango[l],c)]=1;
										add(cango[l],c);
									}
								}
								continue;
							}
							if(mps[mp(c,cango[l])]) continue;
							mps[mp(c,cango[l])]=1;
							add(c,cango[l]);
//							printf("%d %d\n",c,cango[l]);
						}
					}
				}
				for(int k=j+1;k<=n&&s[i][k]!='#';++k){
					int c=col[i][k];
					if(c){
						for(int l=1;l<=4;++l){
							if(cango[l]==-1) continue;
							if(c==cango[l]) continue;
							if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
							if(only[c][0]==-1) continue;
							if(k==j+1){
								if(only[cango[l]][0]==-2){
									if(!mps[mp(cango[l],c)]){
										mps[mp(cango[l],c)]=1;
										add(cango[l],c);
									}
								}
								continue;
							}
							if(mps[mp(c,cango[l])]) continue;
							mps[mp(c,cango[l])]=1;
							add(c,cango[l]);
//							printf("%d %d\n",c,cango[l]);
						}
					}
				}
				for(int k=i-1;k>=1&&s[k][j]!='#';--k){
					int c=col[k][j];
					if(c){
						for(int l=1;l<=4;++l){
							if(cango[l]==-1) continue;
							if(c==cango[l]) continue;
							if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
							if(only[c][0]==-1) continue;
							if(k==i-1){
								if(only[cango[l]][0]==-2){
									if(!mps[mp(cango[l],c)]){
										mps[mp(cango[l],c)]=1;
										add(cango[l],c);
									}
								}
								continue;
							}
							if(mps[mp(c,cango[l])]) continue;
							mps[mp(c,cango[l])]=1;
							add(c,cango[l]);
//							printf("%d %d\n",c,cango[l]);
						}
					}
				}
				for(int k=i+1;k<=n&&s[k][j]!='#';++k){
					int c=col[k][j];
					if(c){
						for(int l=1;l<=4;++l){
							if(cango[l]==-1) continue;
							if(c==cango[l]) continue;
							if(mps[mp(c,cango[l])]&&mps[mp(cango[l],c)]) continue;
							if(only[c][0]==-1) continue;
							if(k==i+1){
								if(only[cango[l]][0]==-2){
									if(!mps[mp(cango[l],c)]){
										mps[mp(cango[l],c)]=1;
										add(cango[l],c);
									}
								}
								continue;
							}
							if(mps[mp(c,cango[l])]) continue;
							mps[mp(c,cango[l])]=1;
							add(c,cango[l]);
//							printf("%d %d\n",c,cango[l]);
						}
					}
				}
			}
		}
	}
	dis[1]=0;
	for(int i=2;i<=cnt;++i) dis[i]=INF;
	priority_queue<pair<int,int> > q2;
	q2.push(mp(0,1));
	while(!q2.empty()){
		int u=q2.top().second;
		q2.pop();
		for(int i=hd[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q2.push(mp(-dis[v],v));
			}
		}
	}
	mps.clear();
	for(int i=1;i<=ecnt;++i) e[i]=edge{0,0};
	ecnt=0;
	for(int i=1;i<=cnt;++i) hd[i]=0;
	cnt=0;
}
int main(){
	freopen("portal.in","r",stdin);
	freopen("std2.out","w",stdout);
    int T=read();
    while(T--){
    	n=read();
        for(int i=1;i<=n;i++)
            scanf("%s",s[i]+1);
        if(s[1][1]!='.'||s[n][n]!='.')
            return 0;
        for(int i=0;i<=n+1;++i)
        	for(int j=0;j<=n+1;++j)
        		col[i][j]=0;
        for(int i=0;i<=n+1;++i) s[i][0]=s[i][n+1]='#';
        for(int i=0;i<=n+1;++i) s[0][i]=s[n+1][i]='#';
		bfs();
//        for(int i=0;i<=n+1;++i){
//        	for(int j=0;j<=n+1;++j){
//        		printf("%d ",col[i][j]);
//			}
//			puts("");
//		}
        if(dis[col[n][n]]==INF) puts("-1");
        else printf("%d\n",dis[col[n][n]]*2);
    }
    return 0;
}
```

---

## 作者：SteveHans (赞：1)

# 传送门题解
## 题意解释
题目稍微有些复杂，这里就说几个重要的点：

（注：连通块指由 `.` 四方向连通组成的区域）

### 1

**地图之外都是墙**，这里就有一个推论，在有解的地图中，玩家能到的连通块周围一定有墙。

证明，使用反证法，假设存在一个连通块周围无墙，并且玩家可以到达。首先此连通块**必定不与** $(1, 1)$ **这个格子联通**，因为 $(1, 1)$ 在边界，$(0, 1)$ 和 $(1, 0)$ 是墙。然后又因为传送门只能在墙上，所以此连通块也必定不是通过传送门让玩家到达。又因为到达一个连通块的方式只有通过传送门和直接走过来，所以此连通块不存在。

### 2

**四个方向都可以**，这决定了能不能使**仅隔墙的**连通块之间相互沟通。如样例地图：*（数字表示连通块编号）*

```
11###
#1#3#
#11##
111#2
1###2
```

如果有规定必须为传送枪发射方向，那么 $(4,4)$ 这个格子就只能到达 $(4, 3)$ 这个格子，也就无法使得连通块 $1$ 和连通块 $2$ 相通。

### 3

**传送枪的使用指的是穿过多少面传送门**，那么就不难想到，我们可以在每一个能建传送门的空地上建一条**边权为** $1$ 的**指向墙的**有向边，然后再每个墙周围的空地上建一条**边权为** $1$ 的**指向空地**的有向边。也就是把此题穿过门的描述抽象成了边权。

## 解题思路

承接上面的 $2$ 号和 $3$ 号解释，我们可以把每一个从 $(1, 1)$ 到 $(n, n)$ 的所有格子都抽象成点，空地与空地之间有**双向的**且**边权为** $0$ 的边，墙与周围空地之间有指向空地的边权为 $1$ 的边，同时空地与它发射传送枪可射到的墙之间也有指向墙的边权为 $1$ 的边。这样就只需要**求最短路**就好了。

但是当我尝试这样做时，我才注意到刚才的 $1$ 号解释，所以应该要把**所有边界看成墙**，建边也要建到边界上来。

再最后讨论一个问题，需不需要询问此时是否有**钥匙**，即是否需要确定每一个连通块一定可以通过接壤（接壤边界或 `#`）得到至少一个墙。其实我们已经证明了，就在 $1$ 号解释中。

因为此题边权只用 $0$ 和 $1$，所以可以使用双端队列广搜，我~~因为太懒~~使用的是 STL 里的 deque。

时间复杂度为 $O(n^3)$，瓶颈在建图的 build 函数。

示例代码：（建议大家把数组开大一点）

```
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

#define x first
#define y second

const int N = 1010, M = N * N, E = 2e6 + 10;
char s[N][N];
int g[N][N];
int h[M], e[E], ne[E], w[E], idx; //邻接表存储图
int n;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
bool st[M];
int d[M];

void add(int a, int b, int c)
{
    e[++ idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx;
}

void build() //建立模型
{
    //直接枚举每个空地
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= n; j ++)
            if (s[i][j] == '.')
            {
                for (int u = 0; u < 4; u ++)
                {
                    int x = i + dx[u], y = j + dy[u];
                    if (!x || x > n || !y || y > n)
                    {
                        add(g[x][y], g[i][j], 1);
                    }
                    int a = g[i][j], b = g[x][y]; //得到(i,j)和(x,y)的对应数
                    if (s[x][y] == '.') add(a, b, 0);
                    else if (s[x][y] == '#') add(b, a, 1); //反过来建边
                }

                //直接枚举此点第一个碰到的墙，建立边
                int t = j + 1;
                while (t <= n && s[i][t] != '#') t ++;
                add(g[i][j], g[i][t], 1);
                t = j - 1;
                while (t > 0 && s[i][t] != '#') t --;
                add(g[i][j], g[i][t], 1);
                t = i + 1;
                while (t <= n && s[t][j] != '#') t ++;
                add(g[i][j], g[t][j], 1); 
                t = i - 1;
                while (t > 0 && s[t][j] != '#') t --;
                add(g[i][j], g[t][j], 1); 
            }
}

int bfs() //双端队列广搜求最短路
{
    memset(d, 0x3f, sizeof d);
    memset(st, 0, sizeof st);
    d[g[1][1]] = 0;

    deque<int> q;
    q.push_back(g[1][1]);

    while (q.size())
    {
        int t = q.front(); q.pop_front();
        
        if (st[t]) continue;
        st[t] = true;

        if (t == g[n][n]) return d[t];

        for (int i = h[t]; i; i = ne[i])
        {
            int j = e[i];
            if (d[j] > d[t] + w[i])
            {
                d[j] = d[t] + w[i];
                if (w[i]) q.push_back(j);//双端队列广搜经典
                else q.push_front(j);
            }
        }
    }

    return -1;
}

int main()
{
	int T;
    cin >> T;

    while (T --)
    {
        memset(h, 0, sizeof h); //别忘了初始化
        idx = 0;

        scanf("%d", &n);
        for (int i = 1; i <= n; i ++) //因为要考虑边界上的墙，所以从1开始
            scanf("%s", s[i] + 1);

        if (s[1][1] != '.' || s[n][n] != '.') return 0;

        //把(x,y)坐标对应到一个数，方便邻接表建图
        for (int i = 0, t = 1; i <= n + 1; i ++) //考虑边界上的墙所以从0枚举到n+1
            for (int j = 0; j <= n + 1; j ++)
                g[i][j] = t ++;

        build();

        printf("%d\n", bfs()); //直接输出
    }
	
	return 0;
}
```

---

