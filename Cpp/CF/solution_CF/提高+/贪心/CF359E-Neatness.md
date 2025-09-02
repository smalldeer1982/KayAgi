# Neatness

## 题目描述

Simon loves neatness. So before he goes to bed, Simon wants to complete all chores in the house.

Simon's house looks like a rectangular table consisting of $ n $ rows and $ n $ columns from above. All rows of the table are numbered from $ 1 $ to $ n $ from top to bottom. All columns of the table are numbered from $ 1 $ to $ n $ from left to right. Each cell of the table is a room. Pair $ (x,y) $ denotes the room, located at the intersection of the $ x $ -th row and the $ y $ -th column. For each room we know if the light is on or not there.

Initially Simon is in room $ (x_{0},y_{0}) $ . He wants to turn off the lights in all the rooms in the house, and then return to room $ (x_{0},y_{0}) $ . Suppose that at the current moment Simon is in the room $ (x,y) $ . To reach the desired result, he can perform the following steps:

1. The format of the action is "1". The action is to turn on the light in room $ (x,y) $ . Simon cannot do it if the room already has light on.
2. The format of the action is "2". The action is to turn off the light in room $ (x,y) $ . Simon cannot do it if the room already has light off.
3. The format of the action is "dir" ( $ dir $ is a character). The action is to move to a side-adjacent room in direction $ dir $ . The direction can be left, right, up or down (the corresponding dir is L, R, U or D). Additionally, Simon can move only if he see a light in the direction $ dir $ . More formally, if we represent the room, Simon wants to go, as $ (nx,ny) $ , there shold be an integer $ k $ $ (k&gt;0) $ , that room $ (x+(nx-x)k,y+(ny-y)k) $ has a light. Of course, Simon cannot move out of his house.

Help Simon, find the sequence of actions that lets him achieve the desired result.

## 样例 #1

### 输入

```
3 1 1
1 0 0
0 1 0
1 0 0
```

### 输出

```
YES
D1R2L2D2UU2
```

## 样例 #2

### 输入

```
3 1 1
1 0 0
0 1 0
0 0 1
```

### 输出

```
NO
```

# 题解

## 作者：Alex_Wei (赞：1)

### [CF359E Neatness](https://www.luogu.com.cn/problem/CF359E)

挺趣味的一道题。

注意到如果我们一路走一路开，就可以在已经走过的地方自由移动。

这启发我们从 $(x_0, y_0)$ 开始 DFS，每到一个位置就将它的灯打开，保证可以回到已经经过的位置。一边回溯一边关灯，回溯时上一层的灯还是亮着的，所以合法。

有解当且仅当每个原来有灯的位置都被 DFS 到了，即 DFS 结束后整张图没有亮灯。

正确性证明：称一个点合法当且仅当它被 DFS 到。只需证明每个可达的位置均合法。如果一个局面可以继续扩展，那么第一个被扩展的位置上下（或左右）均有合法点。假设存在可达的位置不合法，那么存在一个上下（或左右）均有合法点的非法点。不妨设其上方的合法点较后被 DFS 到，那么该合法点的下方是非法点。但可以从该合法点向下 DFS，与其下方是非法点矛盾。

时间复杂度 $\mathcal{O}(n ^ 3)$。[代码](https://codeforces.com/contest/359/submission/210720468)。

---

## 作者：water_three (赞：1)

[CSDN链接](https://blog.csdn.net/heruimiao123456/article/details/123968353)

[题目链接](https://www.luogu.com.cn/problem/CF359E)

### 性质：
一个很显然的性质，对于一个灯，如果没有任何灯**依赖**这个灯才能关，那么就可以关掉这个灯。
### 思路：
从卧室开始搜索，设当前到的房间为 $\left(x,y\right)$。若此时任意一个方向上有灯，那就往那个方向搜索。如果都没有，**说明从这个房间到不了其他任何房间**，那么这个灯没有用，可以直接关了。

**注意事项：当到一个房间后，如果这个房间灯没有开，可以直接打开，然后走的时候再关**。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[501][501],now,a[501][501],n,x,y,cao[10000000],tot;
int dfs(int x,int y){
	if(vis[x][y]||x<1||x>n||y<1||y>n)return 0;//判断是否走过 
	if(!a[x][y]){
		now++;
		cao[++tot]=1;//先开灯 
	}
	vis[x][y]=1;
	int pan=0;
	for(int i=x-1;i>=1;i--){//往上搜
		if(a[i][y]&&vis[i][y]==0){
			pan=1;
			break;
		}
	}
	if(pan){
		cao[++tot]=3;
		dfs(x-1,y),pan=0;
		cao[++tot]=4;
	}
	for(int i=x+1;i<=n;i++){//往下搜
		if(a[i][y]&&vis[i][y]==0){
			pan=1;
			break;
		}
	}
	if(pan){
		cao[++tot]=4;
		dfs(x+1,y),pan=0;
		cao[++tot]=3;
	}
	for(int j=y+1;j<=n;j++){//往右搜
		if(a[x][j]&&vis[x][j]==0){
			pan=1;
			break;
		}
	}
	if(pan){
		cao[++tot]=6;
		dfs(x,y+1),pan=0;
		cao[++tot]=5;
	}
	for(int j=y-1;j>=1;j--){//往左搜
		if(a[x][j]&&vis[x][j]==0){
			pan=1;
			break;
		}
	}
	if(pan){
		cao[++tot]=5;
		dfs(x,y-1),pan=0;
		cao[++tot]=6;
	}//分别从四个方向上搜索 
	cao[++tot]=2;//关灯离开 
	now--;
	return 0;
} 
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
			now+=a[i][j];
		}
	}
	dfs(x,y);
	if(now){
		printf("NO");
		return 0;
	}
	else{
		printf("YES\n");
		for(int i=1;i<=tot;i++){
			switch(cao[i]){
				case 1:printf("1");break;
				case 2:printf("2");break;
				case 3:printf("U");break;
				case 4:printf("D");break;
				case 5:printf("L");break;
				case 6:printf("R");break;
			}
		}
	}
} 
```


---

## 作者：bobo2007 (赞：0)

## CF359E Neatness 题解

### 解法

如果卧室是黑的，先点亮卧室。

然后从卧室出发进行 `dfs`，每次走能走的且没被走过的路，然后走过去。

递归时如果当前点不是亮的，就点亮当前点。

回溯时熄灭当前点。

正确性的话一个原本亮着的点如果能被到达，那么一定正好到达一次，回退一次，最后如果有解的话正好能把所有灯熄灭。

维护方面每次搜路时可以直接 $O(n)$ 枚举当前方向有无亮着的灯，总复杂度 $O(n^3)$。

也可以像我~~大冤种~~和群友 VP 时用树状数组看前方亮着的灯，总复杂度 $O(n^2\log n)$，然后比群友慢两分钟打完输掉。

### code

```C++
#include<bits/stdc++.h>
using namespace std;
int n,xx,yy,a[510][510],vis[510][510],tr1[510][510],tr2[510][510],d[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
char c[4]={'L','R','U','D'};
string s;
void add1(int i,int x,int y) {while(x<=n) tr1[i][x]+=y,x+=x&(-x);}
void add2(int i,int x,int y) {while(x<=n) tr2[x][i]+=y,x+=x&(-x);}
int qry1(int i,int x) {int ans=0;while(x) ans+=tr1[i][x],x-=x&(-x);return ans;}
int qry2(int i,int x) {int ans=0;while(x) ans+=tr2[x][i],x-=x&(-x);return ans;}
int qq1(int i,int l,int r) {return qry1(i,r)-qry1(i,l-1);}
int qq2(int i,int l,int r) {return qry2(i,r)-qry2(i,l-1);}
void dfs(int x,int y)
{
	int i,j;vis[x][y]=1;
	if(a[x][y]) add1(x,y,-1),add2(y,x,-1),a[x][y]=0;
	else s.push_back('1');
	for(i=0;i<4;i++)
	{
		int o=0;
		if(vis[x+d[i][0]][y+d[i][1]]) continue;
		if(i==0) o=qq1(x,1,y);
		else if(i==1) o=qq1(x,y,n);
		else if(i==2) o=qq2(y,1,x);
		else o=qq2(y,x,n);
		if(o>0)
		{
			s.push_back(c[i]);
			dfs(x+d[i][0],y+d[i][1]);
			s.push_back(c[i^1]);
		}
	}
	s.push_back('2');
}
int main()
{
	scanf("%d%d%d",&n,&xx,&yy);
	int i,j,op=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) scanf("%d",&a[i][j]);
	if(!a[xx][yy]) s.push_back('1'),a[xx][yy]=1;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) if(a[i][j]) add1(i,j,1),add2(j,i,1);
	dfs(xx,yy);
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) if(a[i][j]) {printf("NO");return 0;}
	printf("YES\n");
	cout<<s;
	return 0;
}
```

---

