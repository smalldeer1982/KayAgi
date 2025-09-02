# Weather Forecast

## 题目描述

你是风之神。

通过移动一朵大云，你可以决定天气：云下必定下雨，其他地方阳光普照。

但你是一个仁慈的神：你的目标是给乡间的每个田地带来足够的雨水，给市场和节日带来阳光。小人类用他们贫乏的词汇，只能将这称为“天气预报”。

你负责管理一个名为 Paccimc 的小国家。这个国家由 $4 \times 4$ 的方块区域组成，用它们的编号表示。

![](https://cdn.luogu.com.cn/upload/image_hosting/tuq65kcj.png)

你的云的大小为 $2 \times 2$，不得越过国家的边界。

给出了一段时间内每个区域的市场和节日的安排。

在该时段的第一天，无论安排如何，在中心区域（6-7-10-11）都会下雨。

在接下来的每一天，你可以将你的云向四个基本方向之一（北、西、南和东）移动 $1$ 或 $2$ 个方格，也可以将其保持在原位。不允许对角线移动。所有移动均发生在一天开始时。

你不应该让一个区域连续一周没有雨水（也就是说，你允许最多连续 $6$ 天没有雨）。你不必在你获得的时间段之外的日子里考虑雨水：也就是说，你可以假设在时间段之前的整个国家都下雨，在它结束后的一天也是如此。

## 样例 #1

### 输入

```
1 
0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 
7
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 1 0 0 0 0 1 1 0 0 1 
0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 1 
0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 
0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 
1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 
0 0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 
7 
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 1 0 0 0 0 0 1 0 0 
0 0 0 1 0 0 0 0 0 0 1 0 1 0 0 0 
0 1 0 0 0 0 0 1 0 0 0 0 1 0 0 0 
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 1 1 0 1 0 0 0 0 1 
0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0
15 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 1 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 1 1 0 1 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 
0 0 1 1 0 0 0 0 0 1 0 0 0 0 0 0 
1 1 0 0 0 0 0 0 0 0 1 0 0 1 0 0 
0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0  
0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 
1 0 0 1 1 0 0 0 0 1 0 1 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 
0 0 0 0 0 1 0 1 0 1 0 0 0 0 0 0  
0```

### 输出

```
0
1
0
1```

# 题解

## 作者：Ashford (赞：5)

# **P10492 Weather Forecast**
这个问题可以通过记忆化搜索结合状态压缩来解决。核心思路是只跟踪**四个角落**的干燥天数，并利用 DFS 遍历所有可能的云移动路径。通过剪枝（检查云是否覆盖活动区域、角落干燥天数是否超限）优化。状态转移时枚举所有合法移动方向并更新角落的干燥天数，最终判断是否存在合法路径满足所有约束条件。时间复杂度为 $O (N)$，空间复杂度为 $O (N×3×3×7⁴)$，其中 $N$ 为天数。

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 370;
int n,a[MAXN][5][5],f[5][5][MAXN][8][8][8][8];
bool check(int day, int x, int y) {
	for(int i=x; i<=x+1; i++) {
		for(int j=y; j<=y+1; j++) {
			if(a[day][i][j] == 1) return false;
		}
	}
	return true;
}
int dfs(int x, int y, int day, int zs, int zx, int ys, int yx) {
	if(f[x][y][day][zs][zx][ys][yx] != -1) return f[x][y][day][zs][zx][ys][yx];
	if(!check(day, x, y)) return 0;
	if(zs >= 7 || zx >= 7 || ys >= 7 || yx >= 7) return 0;
	if(day == n) return 1;
	int dx[] = {-1, 0, -2, 0, 2, 0, 1, 0, 0},dy[] = {0, -1, 0, -2, 0, 2, 0, 1, 0},ans = 0;
	for(int i = 0; i < 9; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if(1 <= nx && nx <= 3 && 1 <= ny && ny <= 3) {
			int new_zs = (nx == 1 && ny == 1) ? 0 : zs + 1;
			int new_zx = (nx == 3 && ny == 1) ? 0 : zx + 1;
			int new_ys = (nx == 1 && ny == 3) ? 0 : ys + 1;
			int new_yx = (nx == 3 && ny == 3) ? 0 : yx + 1;
			ans |= dfs(nx, ny, day + 1, new_zs, new_zx, new_ys, new_yx);
		}
	}
	f[x][y][day][zs][zx][ys][yx] = ans;
	return ans;
}
int main() {
	while(1) {
		memset(f, -1, sizeof(f));
		cin>>n;
		if(n == 0) break;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= 4; j++) {
				for(int k = 1; k <= 4; k++) {
					cin>>a[i][j][k];
				}
			}
		}
		cout << dfs(2, 2, 1, 1, 1, 1, 1) << "\n";
	}
	return 0;
}
```

---

## 作者：Montpelier (赞：4)

## P10492 Weather Forecast （记忆化搜索+剪枝）

---

### 题目大意

有一个 $4\times4$ 大小的城镇，让你控制一块 $2\times2$ 的云彩，你每天可以有 $9$ 种走的方法：上下左右或者不动，走的时候可以走 $1$ 或者 $2$ 步。云彩所在的地方肯定会下雨。另外，给你最多 $365$ 天的安排，要求某些日子的某些城镇不能下雨。此外，任何地方都不能有连续超过 $6$ 天不下雨。


### 解决方法

首先，这道题爆搜的思路是很好想的，也很好实现。显然，会 TLE。

我们不妨用云朵左上方那个点来代表云朵，那么这个点就处于 $(1,1)$ 到 $(3,3)$ 之间了。（设地图左上角为 $(1,1)$）

注意到，只需要考虑 $(1,1)$ $(1,3)$ $(3,1)$ $(3,3)$ 这四个点不会 $\ge7$ 天淋不到雨就可以了，因为这是云朵在四个角落的情况，最没可能淋到雨。

我们考虑 TLE 的理由，也就是如何剪枝。爆搜的问题往往是花费大量计算了**不可能成为结果的情况** or **已经计算过了的情况**。这道题中属于后者。具体来说（建议手写一遍爆搜然后看看访问顺序），是因为计算了大量**天数相同，云朵位置相同，四个角落上面未下雨的天数也相同** 的问题。因此，引入 `bool vst[t][s][8][8][8][8]` 数组，表示“第 $t$ 天，云朵在 $s$ 位置（状压，一共就 $9$ 个可能位置），$(1,1)$、$(1,3)$、$(3,1)$、$(3,3)$ 四个位置分别有多少天未下雨”这种情况有没有被访问过，如果被访问过就不用再次计算了。因为一共才 $4\times4$ 宫格，所以有极高的概率重复，这种剪枝也就效率很高。



code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=369;
const int dx[9]={0,0,0,1,-1,0,0,2,-2};
const int dy[9]={0,1,-1,0,0,2,-2,0,0};
const int plt[12]={0,1,2,3,0,4,5,6,0,7,8,9}; //用于映射
int T,day[N];
bool vst[N][10][8][8][8][8]; //记忆化搜索用于剪枝
bool ans;
bool ok(int t,int x,int y,int a[]) {
	int p[4]={(x-1)*4+y,x*4+y,(x-1)*4+y+1,x*4+y+1};
	if (x<1||x>3||y<1||y>3) return 0;
	for (int k=1;k<=4;++k)
		if (a[k]>=7) return 0;
	for (int k=0;k<4;++k)
		if ((1<<p[k])&day[t]) return 0;
	if (vst[t][plt[p[0]]][a[1]][a[2]][a[3]][a[4]])
		return 0;
	return 1;
}
void dfs(int t,int x,int y,int a[]) {
	if (ans) return;
	if (t==T) {ans=1;return;} //完成任务
	int b[5];
	memset(b,0,sizeof b);
	for (int k=0;k<9;++k) {
		int nx=x+dx[k],ny=y+dy[k];
		if ((!t)&&k) break; //t=0，即第一天只能原地不动
		for (int j=1;j<=4;++j) b[j]=a[j]+1;
		if (nx==1&&ny==1) b[1]=0; //区域1下过雨了
		if (nx==1&&ny==3) b[2]=0; //同理
		if (nx==3&&ny==1) b[3]=0;
		if (nx==3&&ny==3) b[4]=0;
		if (ok(t+1,nx,ny,b)) {
			vst[t+1][plt[(nx-1)*4+ny]][b[1]][b[2]][b[3]][b[4]]=1;
			dfs(t+1,nx,ny,b);
		}
	}
}
int a[5];
int main() {
	while (1) {
		memset(day,0,sizeof day);
		cin>>T;
		if (!T) break;
		for (int i=1;i<=T;++i) {
			int x;
			for (int j=1;j<=16;++j) {
				cin>>x;
				day[i]=day[i]|(x<<j); //状压
			}
		}
		memset(vst,0,sizeof vst);
		memset(a,0,sizeof a);
		ans=0;
		dfs(0,2,2,a); //初始在(2,2)
		cout<<ans<<endl;
	}
	return 0;
}
```


[AC链接](https://www.luogu.com.cn/record/170418116)


求赞赞~

---

## 作者：Allan_Xu (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/P10492)
### 记忆化搜索+剪枝

**两个剪枝**：

1. 如果雨落到有活动的地方，不合法，直接剪掉。
2. 如果四个角没有下雨超过 $7$ 天，不合法，因为四个角地方被覆盖的情况是最少的，~~没听懂？~~（换个说法，如果四个角的其他地方超过 $7$ 天没下雨，那么一定四个角有一个角也 $7$ 天没下雨了）。

再采用一下记忆化搜索，不然会 TLE。

另外，多提一嘴，数组最好抵着数据范围开，因为虽然数据范围很小，但维数挺多的，不然也是 TLE ~~（你猜我怎么知道的）~~。

_code_

```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read(){//快读
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int n;
int a[370][5][5];
int f[5][5][370][8][8][8][8];
int dx[]={-1,0,-2,0,2,0,1,0,0};
int dy[]={0,-1,0,-2,0,2,0,1,0};
int dfs(int x,int y,int day,int zs,int zx,int ys,int yx){
	if(f[x][y][day][zs][zx][ys][yx]!=-1)return f[x][y][day][zs][zx][ys][yx];
	for(int i=x;i<=x+1;i++){
		for(int j=y;j<=y+1;j++){
			if(a[day][i][j]==1)return 0;
		}
	}
	if(zs>=7||zx>=7||ys>=7||yx>=7)return 0;
	int ans=0;
	if(day==n) return 1;
	for(int i=0;i<9;i++){
		int nx=x+dx[i],ny=y+dy[i];
		if(1<=nx&&nx<=3&&1<=ny&&ny<=3){
			ans=ans|dfs(nx,ny,day+1,((nx==1&&ny==1)?0:zs+1),((nx==3&&ny==1)?0:zx+1),((nx==1&&ny==3)?0:ys+1),((nx==3&&ny==3)?0:yx+1));
		}
	}
	if(f[x][y][day][zs][zx][ys][yx]==-1) f[x][y][day][zs][zx][ys][yx]=ans;
	return ans;
}
signed main(){
while(1){
	memset(f,-1,sizeof(f));
	n=read();
	if(n==0)break;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=4;j++){
			for(int k=1;k<=4;k++){
				a[i][j][k]=read();
			}
		}
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=4;j++){
//			for(int k=1;k<=4;k++){
//				cout << a[i][k][j]<< " ";
//			}
//			cout << "\n";
//		}
//		cout << "\n";
//	}
	cout << dfs(2,2,1,1,1,1,1) << "\n";
}
	
	return 0;
}

```

---

## 作者：ThomasNO1 (赞：1)

## Problem
[题目传送门](https://www.luogu.com.cn/problem/P10492)

## Solution
  1：不要给有节日和市场的地方下雨。
  
  这个很简单，用一个前缀和数组 $s_{D,i,j}$，表示第 $D$ 天 $(1,1)$ 到 $(i,j)$ 有多少个市场和节日，搜索时直接判断 $s_{x + 1,y + 1}-s_{x - 1,y + 1}-s_{x + 1,y - 1}+s_{x - 1,y - 1}$ 是否大于 $0$，如果大于就返回。

  2：不让一个区域连续一周没有雨水。

  其实只要判断四个角有没有下雨就行了，因为只要有一个地方 $7$ 天没下雨，那么包含它的任何一个 $2 \times 2$ 矩阵都也没下雨，也就是说，四个角中至少有一个角没下雨。

  如果只判断是否满足两个条件的话肯定会超时，所以我们可以用一个七维数组 $dp_{x,y,Day,A,B,C,D}$ 来存答案，防止重复搜索就行了。（$A,B,C,D$ 分别表示四个角连续多少天没下雨）

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s[377][6][6],dp[377][6][6][8][8][8][8];
bool flag = false;
int dx[] = {1,0,-1,0,2,0,-2,0,0};
int dy[] = {0,1,0,-1,0,2,0,-2,0};
bool dfs(int Day,int x,int y,int A,int B,int C,int D){
	bool ans = 0;
	if(s[Day][x + 1][y + 1] - s[Day][x - 1][y + 1] - s[Day][x + 1][y - 1] + s[Day][x - 1][y - 1] > 0 ||
	A >= 7 || B >= 7 || C >= 7 || D >= 7) return 0;
	if(dp[Day][x][y][A][B][C][D] != -1) return dp[Day][x][y][A][B][C][D];
	if(Day == n) return 1;
	for(int i = 0;i < 9;i++){
		int nx = x + dx[i],ny = y + dy[i];
		if(nx < 1 || nx > 3 || ny < 1 || ny > 3) continue;
		if(s[Day + 1][nx + 1][ny + 1] - s[Day + 1][nx - 1][ny + 1] - s[Day + 1][nx + 1][ny - 1] + 
		s[Day + 1][nx - 1][ny - 1] > 0) continue;
		ans |= dfs(Day + 1,nx,ny,(nx == 1 && ny == 1 ? 0 : A + 1),(nx == 1 && ny == 3 ? 
		0 : B + 1),(nx == 3 && ny == 1 ? 0 : C + 1),(nx == 3 && ny == 3 ? 0 : D + 1));
	}
	return dp[Day][x][y][A][B][C][D] = ans;
}
void solve(){
	memset(s,0,sizeof s);
	memset(dp,-1,sizeof dp);
	flag = 0;
	for(int D = 1;D <= n;D++)
		for(int i = 1;i <= 4;i++)
			for(int j = 1;j <= 4;j++)
				scanf("%d",&s[D][i][j]),s[D][i][j] += s[D][i - 1][j] + s[D][i][j - 1] -
				s[D][i - 1][j - 1];
	printf("%d\n",dfs(1,2,2,1,1,1,1));
}
int main(){
	while(cin >> n && n)
		solve();
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：1)

## 题面
[P10492 Weather Forecast](https://www.luogu.com.cn/problem/P10492)
## 分析
记忆化搜索。

注意对于干旱，只用看图中四个角落是否干旱就行了。

于是乎记忆化的状态就是 $7$ 维，第 $1$ 维是第 $i$ 天，第 $2$ 维和第 $3$ 维是云朵左上角的坐标 $x,y$。
第 $4 \to 7$ 维则是图中四个角的干旱程度。

注意云朵位置完全可以用一个坐标表示，并不需要存储四个点。

于是，可以用记忆化记录每一天的每一个状态是否搜索过了。

宽搜暴力枚举每一天的每一个状态是否合法就可以了。

时间复杂度为 $O(n \times 9 \times 7^4)$。
## Code

```cpp

#include<bits/stdc++.h>
using namespace std;
struct node {
	int day,x,y,id1,id2,id3,id4;
};
int dp[400][5][5][7][7][7][7];
int mp[400][10][10];
int n;
queue<node>q;
int nxt[5][2]= {{0,1},{1,0},{0,-1},{-1,0},{0,0}};
int nex[4][2]= {{0,0},{0,1},{1,0},{1,1}};
int bfs() {
	memset(dp,0,sizeof(dp));
	if(mp[1][1][1]||mp[1][1][2]||mp[1][2][2]||mp[1][2][1])return 0;
	while(!q.empty())q.pop();
	dp[1][1][1][1][1][1][1]=1;
	q.push((node) {
		1,1,1,1,1,1,1
	});
	while(!q.empty()) {
		node tmp=q.front();
		q.pop();
		int x=tmp.x;
		int y=tmp.y;
		int day=tmp.day;
		if(day==n)return 1;
		int hys1=tmp.id1;
		int hys2=tmp.id2;
		int hys3=tmp.id3;
		int hys4=tmp.id4;
		for(int i=0; i<5; i++) {
			for(int j=1; j<=2; j++) {
				int xgd1=hys1;
				int xgd2=hys2;
				int xgd3=hys3;
				int xgd4=hys4;
				int tx=x+nxt[i][0]*j;
				int ty=y+nxt[i][1]*j;
				if(tx<0||tx>2)continue;
				if(ty<0||ty>2)continue;
				int flag=0;
				for(int k=0; k<4; k++) {
					int fx=tx+nex[k][0];
					int fy=ty+nex[k][1];
					if(mp[day+1][fx][fy]) {
						flag=1;
						break;
					}
				}
				if(flag)continue;
				if(tx==0&&ty==0) {
					xgd1=-1;
				}
				if(xgd1+1==7)continue;
				if(tx==0&&ty==2) {
					xgd2=-1;
				}
				if(xgd2+1==7)continue;
				if(tx==2&&ty==0) {
					xgd3=-1;
				}
				if(xgd3+1==7)continue;
				if(tx==2&&ty==2) {
					xgd4=-1;
				}
				if(xgd4+1==7)continue;
				xgd1++;
				xgd2++;
				xgd3++;
				xgd4++;
				if(dp[day+1][tx][ty][xgd1][xgd2][xgd3][xgd4])continue;
				dp[day+1][tx][ty][xgd1][xgd2][xgd3][xgd4]=1;
				q.push((node) {
					day+1,tx,ty,xgd1,xgd2,xgd3,xgd4
				});
			}
		}
	}
	return 0;
}
int main() {
	while(1) {
		scanf("%d",&n);
		if(n==0)return 0;
		for(int i=1; i<=n; i++) {
			for(int j=0; j<4; j++) {
				for(int k=0; k<4; k++) {
					scanf("%d",&mp[i][j][k]);
				}
			}
		}
		printf("%d\n",bfs());
	}
	return 0;
}
```

---

