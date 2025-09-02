# Robots on Ice

## 题目描述

受哈尔滨冰雕的启发，来自北极机器人与自动机大学的参赛队员决定程序竞赛结束后在校园内举办自己的冰雪节。他们打算在冬天结冰的时候，从学校附近的一个湖里获取冰块。为了便于监测湖中冰层的厚度，他们先将湖面网格化，然后安置一个轻巧的机器人逐个方格测量冰层的厚度。在网格中有三个特殊方格被指定为“检查点”，对应着机器人在检查过程中经过整个行程的四分之一、二分之一、四分之三的位置，机器人在这三个特殊“检查点”会发送相应的进度报告。为了避免对冰面造成不必要的磨损和划痕而影响后续的使用，机器人需要从网格左下角坐标为 $(0，0)$ 的方格出发，经过所有方格仅且一次，然后返回位于坐标为 $(0，1)$ 的方格。如果有多种路线符合要求，则机器人每天会使用一条不同的路线。机器人只能沿北、南、东、西四个方向每次移动一个方格。  
给定网格的大小和三个检查点的位置，编写程序确定有多少种不同的检查路线。例如，湖面被划分为 $3 \times 6$ 的网格，三个检查点按访问的顺序分别为 $(2，1)，(2，4)$ 和 $(0，4)$，机器人必须从 $(0，0)$ 方格开始，路经 $18$ 个方格，最后终止于 $(0，1)$ 方格。机器人必须在第 $4（＝\left\lfloor\dfrac{18}{4}\right\rfloor）$ 步的时候经过 $(2，1)$ 方格，在第 $9（＝\left\lfloor\dfrac{18}{2}\right\rfloor）$ 步的时候经过 $(2，4)$ 方格，第 $13（＝\left\lfloor\dfrac{3 \times 18}{4}\right\rfloor）$ 步的时候经过 $(0，4)$ 方格，只有两种路线符合要求，如下图所示。  
![UVA1098 Robots on Ice](https://cdn.luogu.com.cn/upload/image_hosting/vy6tphyl.png)  
需要注意：（1）当网格的大小不是 $4$ 的倍数时，在计算步数时使用整除；（2）某些情况下可能不存在符合要求的路线，例如给定一个 $4 \times 3$的网格，三个检查点分别为 $(2，0)，(3，2)$ 和 $(0，2)$，那么将不存在从 $(0，0)$ 方格出发，结束于 $(0，1)$ 方格且满足要求的路线。

# 题解

## 作者：Lemon_zqp (赞：2)

### 预处理
首先，把 $vis$ 数组，从 $(1,1)$ 到 $(n,m)$ 设为 $0$，把周围设为 $1$。这样在后面判断的时候就不用再判断出界了，直接看 $vis$ 数组即可。
### 思路
简单深搜题目，只不过在检查函数里加上几个剪枝。如果到了时间没到点，就不用继续判断了，到了点没到时间同理，需要重复计算的可以考虑用一个变量存下来，注意有一个坑，如果你到了终点，但是没走完，也就是步数不等于 $n \times m$，就不能计入答案。
### 复杂度
每组数据的时间复杂度是 $O(nm + 4^{nm})$，加上一堆剪枝，可以通过此题。
### 代码
```
#include <bits/stdc++.h>
using namespace std;

int dx[5] = {0, 0, -1, 1};
int dy[5] = {-1, 1, 0, 0};
int vis[100][100], ans = 0;
int n, m, x1, yy1, x2, y2, x3, y3, t1, t2, t3;

bool check(int x, int y, int time, int i){//剪枝 
	if(vis[x][y]) return false;//走过了或越界 
	if(x == 1 && y == 2 && time != (n * m)) return false;//到了重点，但是没走完 
	if(time == t1 && (x != x1 || y != yy1)) return false;//到了时间，没到点 
	if((x == x1 && y == yy1) && time != t1) return false;//到了点，没到时间
	if(time == t2 && (x != x2 || y != y2)) return false;
	if((x == x2 && y == y2) && time != t2) return false; 
	if(time == t3 && (x != x3 || y != y3)) return false;
	if((x == x3 && y == y3) && time != t3) return false;
	//如果走的路形成了一个圈也不行(即如果按当前方向往前走不行，但是往左右可以走，说明绕圈了)
    if(vis[x + dx[i]][y + dy[i]] && !vis[x + dy[i]][y + dx[i]] && !vis[x - dy[i]][y - dx[i]]) return false;
	return true;
}

void dfs(int x, int y, int step){
	if(x == 1 && y == 2){//到了终点，答案加一 
        ans++;
		return;
	}
	for(int i = 0; i < 4; i++){//普通dfs 
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(check(nx, ny, step + 1, i)){
			vis[nx][ny] = true;
			dfs(nx, ny, step + 1);
			vis[nx][ny] = false;
		}
    }
    return;
}

int main(){
	int t = 1;
	while(cin >> n >> m){
		if(n == 0 && m == 0){ 
			return 0;
		}
		t1 = n * m / 4;//把每个时间点存下来，避免重复计算导致的超时 
		t2 = n * m / 2;
		t3 = n * m * 3 / 4;
		for(int i = 1; i <= n; i++) {//预处理 
			vis[i][0] = true; vis[i][m + 1] = true;
			for(int j = 1; j <= m; j++) {
				vis[i][j] = false;
				vis[0][j] = true;
				vis[n+1][j] = true;
			}
		}
		cin >> x1 >> yy1 >> x2 >> y2 >> x3 >> y3; 
		x1++;//把数组向右下拉一格，这样起点就会成为 (1,1)，我个人认为这样会好处理一点 
		x2++;
		x3++;
		yy1++;
		y2++;
		y3++;
		ans = 0;
		vis[1][1] = true;//起点已经走过了 
		dfs(1, 1, 1);
		cout << "Case " << t << ": " << ans << '\n';
		t++;
	}
    return 0;
}
```

---

## 作者：Zhanghaoxiang930 (赞：0)

### 思路

看到题目中的 $m$ 和 $n$ 的数据范围 $2 \leq m,n \leq 8$，可以选择用深搜加剪枝来做，在深搜函数中，对于每个位置最多会尝试 $4$ 个方向进行递归，所以对于每一组数据的复杂度为 $O(4^{nm})$。在深搜函数里面，每要走一个点就判断一次，以避免走多余的路，实现优化。注意特判如果前后不能走，而左右可以走的话直接结束，因为这说明绕圈了。此复杂度，深搜加剪枝可以过本题。
### 初始化
由于从 $(0,0)$ 点开始走不方便我们判断，所以我们可以将所有涉及坐标加一，从 $(1,1)$ 开始走，终点为 $(1,2)$。同时，定义 $v$ 数组，来记录每个点是否走过。

### 代码

```cpp
#include<bits/stdc++.h>
#define maxn 200
using namespace std;
int t,n,m,sum,cnt;
bool b[maxn][maxn];
int v[maxn][maxn],s[10000],dx[maxn],dy[maxn];
int ax[5] = {0,-1,1,0,0};  //坐标数组 
int ay[5] = {0,0,0,-1,1};
bool check(int x, int y, int t, int d){ //判断剪枝 
	if(v[x][y]){
		return false;
	}
	if(x==1&&y==2&&t!=(n*m)){ //到终点但没走完
		return false;
	}
	if(v[x+ax[d]][y+ay[d]]&&!v[x+ay[d]][y+ax[d]]&&!v[x-ay[d]][y-ax[d]]){ //如果走的路形成了一个圈：绕圈了
		return false;
	} //判断特殊点 
	for(int i=1;i<=3;i++){
		if(t>s[i]&&!v[dx[i]][dy[i]]){  //超过时间还没到过特殊点 
			return false;	
		}   
		if((x==dx[i]&&y==dy[i]&&t!=s[i])||(t==s[i]&&!(x==dx[i]&&y==dy[i]))){  //不在规定时间内到达特殊点 
			return false;
		}
	}
	return true;
}void dfs(int x,int y,int t){
	if(x==1&&y==2){
		sum++;
		return ;
	}
	for(int i=1;i<=4;i++){
		int nx=x+ax[i];
		int ny=y+ay[i];
		if(check(nx,ny,t+1,i)){
			v[nx][ny]=1; //标记 
			dfs(nx,ny,t+1); 
			v[nx][ny]=0; //回溯 
		}
	}
}void init(){ //初始化：把地图包起来 
	sum=0; 
	for(int i=1;i<=n;i++){
		v[i][0]=1;v[i][m+1]=1;
		for(int j=1;j<=m;j++){
			v[i][j]=0,v[0][j]=1,v[n+1][j]=1;
		}
	}
}
int main(){
	while(cin>>n>>m){
		if(n==0&&m==0){
			break;
		}
		init();
		for(int i=1;i<=3;i++){
			cin>>dx[i]>>dy[i]; //存储特殊点坐标 
			dx[i]++; //+1更方便剪枝 
			dy[i]++;
		}
		s[1]=n*m/4;  //记录每个特殊点要经过的时间 
		s[2]=n*m/2;
		s[3]=n*m*3/4;
		v[1][1]=1;
		cnt++; 
		dfs(1,1,1);  //从（1,1）开始走 
		cout<<"Case "<<cnt<<": "<<sum<<endl;
	}
}
```

---

