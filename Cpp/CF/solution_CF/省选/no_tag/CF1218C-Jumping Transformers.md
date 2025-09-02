# Jumping Transformers

## 题目描述

你，强大的 Blackout，正站在 $N \times M$ 矩阵的左上角 $(0,0)$。你每秒可以向右或向下移动一格。

矩阵中有 $K$ 个变形金刚在跳跃。每个变形金刚从位置 $(x, y)$、在时间 $t$ 开始跳跃，每秒跳到下一个位置。$x$ 轴向下增长，$y$ 轴向右增长。跳跃的顺序为 $ \{(x, y), (x+d, y-d), (x+d, y), (x, y+d)\} $，并且循环往复。在时间 $t$ 之前，变形金刚不会出现在矩阵中。

你需要到达右下角 $(N-1, M-1)$，途中如果遇到变形金刚（可能有多个），你必须全部击杀，并损失击杀每个变形金刚所需的能量之和。

被击杀的变形金刚会立刻消失，不再跳跃。请输出 Blackout 到达右下角所需消耗的最小能量。

## 说明/提示

如果 Blackout 选择从 $(0, 0)$ 走到 $(2, 0)$，再从 $(2, 0)$ 走到 $(2, 2)$，他需要击杀第一个和第三个变形金刚，总能量消耗为 9。不存在能量消耗更少的路径。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3 5
0 1 1 0 7
1 1 1 0 10
1 1 1 1 2
1 1 1 2 2
0 1 1 2 3
```

### 输出

```
9```

# 题解

## 作者：daniEl_lElE (赞：0)

考虑 $dp_{i,j,k,0/1}$ 表示目前走到 $i,j$ 位置，连续 $k$ 步从上一步的方向走来，上一步的方向为右/下。

考虑对于每个障碍物，在其经过且会碰到人的点打上其花费的 $val_{i,j}$。同时注意到在一些情况下，到达 $(x,y+d)$ 或 $(x+d,y)$ 时已经经过 $(x,y)$ 或 $(x-d,y+d)$ 并消除了这个障碍，于是在这些位置打上一个至少连续向右/下走多少步才可以免掉其价值花费的 $tmp_{i,j}$。

dp 转移是单次 $O(1)$ 的，总复杂度 $O(n^3)$，可以通过。注意需要使用滚动数组。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[2][505][505][2];
int val[505][505];
vector<pair<pair<int,int>,int>> vc1[505];
vector<pair<pair<int,int>,int>> vc2[505];
int tmp1[505][505],tmp2[505][505];
signed main(){
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		int x,y,d,t,e; cin>>x>>y>>d>>t>>e;
		if(((x+y)%4==t%4)&&(x+y>=t)){
			val[x][y]+=e;
			if(d%4==3){
				vc1[x].push_back(make_pair(make_pair(d,y+d),-e));
			}
			if(d%4==2){
				vc2[x+d].push_back(make_pair(make_pair(d,y),-e));
			}
		}
		if(((x+y)%4==(t+1)%4)&&(x+y>=t+1)){
			val[x+d][y-d]+=e;
			if(d%4==1){
				vc1[x+d].push_back(make_pair(make_pair(d,y),-e));
			}
		}
		if(((x+y+d)%4==(t+2)%4)&&(x+y+d>=t+2)){
			val[x+d][y]+=e;
		}
		if(((x+y+d)%4==(t+3)%4)&&(x+y+d>=t+3)){
			val[x][y+d]+=e;
		}
	}
	memset(dp,1,sizeof(dp));
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) for(int l=0;l<=j;l++) tmp1[j][l]=0;
		for(int j=0;j<m;j++) for(int l=0;l<=i;l++) tmp2[j][l]=0;
		for(auto v:vc1[i]) tmp1[v.first.second][v.first.first]+=v.second;
		for(int j=0;j<m;j++) for(int l=1;l<=j;l++) tmp1[j][l]+=tmp1[j][l-1];
		for(auto v:vc2[i]) tmp2[v.first.second][v.first.first]+=v.second;
		for(int j=0;j<m;j++) for(int l=1;l<=i;l++) tmp2[j][l]+=tmp2[j][l-1];
		int p=(i&1),q=(i&1)^1;
		memset(dp[p],1,sizeof(dp[p]));
		if(i==0){
			dp[0][0][0][0]=val[0][0]; 
		}
		else{
			for(int j=0;j<m;j++){
				for(int k=0;k<i;k++) dp[p][j][k+1][0]=min(dp[p][j][k+1][0],dp[q][j][k][0]+val[i][j]+tmp2[j][k+1]);
				for(int k=0;k<=j;k++) dp[p][j][1][0]=min(dp[p][j][1][0],dp[q][j][k][1]+val[i][j]+tmp2[j][1]); 
			}
		}
		for(int j=1;j<m;j++){
			for(int k=0;k<=i;k++) dp[p][j][1][1]=min(dp[p][j][1][1],dp[p][j-1][k][0]+val[i][j]+tmp1[j][1]);
			for(int k=0;k<j;k++) dp[p][j][k+1][1]=min(dp[p][j][k+1][1],dp[p][j-1][k][1]+val[i][j]+tmp1[j][k+1]);
		}
	}
	int p=(n-1)&1,ans=1e18;
	for(int k=0;k<n;k++) ans=min(ans,dp[p][m-1][k][0]);
	for(int k=0;k<m;k++) ans=min(ans,dp[p][m-1][k][1]);
	cout<<ans;
	return 0;
}
```

---

