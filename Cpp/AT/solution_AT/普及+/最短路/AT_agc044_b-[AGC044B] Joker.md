# [AGC044B] Joker

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc044/tasks/agc044_b

映画「ジョーカー」が今夜放映されるとあり、あなたの行きつけの劇場はすでに満席です。この劇場には $ N $ 席の座席からなる列が $ N $ 列あり、これらの席が $ N\times\ N $ の正方形型に並んでいます。最前列の観客に左から $ 1,\ 2,\dots,\ N $ の番号を、前から $ 2 $ 列目の観客に左から $ N+1,\ \dots,\ 2N $ の番号を付け、以降の観客にも同様に番号を付けます。最後列の観客の番号は、左から $ N^2-N+1,\dots,\ N^2 $ となります。

上映が終わると、観客は決まった順に劇場を出ます。$ i $ 番目に劇場を出るのは、番号 $ P_i $ の観客です。番号 $ P_{i+1} $ の観客は、番号 $ P_{i} $ の観客が劇場を出るまで待ってから移動します。劇場を出るには、席から席への移動を繰り返し、席からなる正方形型のエリアの外に出なければなりません (四辺のどこからでも出ることができます)。席から席への移動では、前後左右の $ 4 $ 方向への移動が可能です。

番号 $ x $ の観客が、劇場を出る際に番号 $ y $ の別の観客が **まだ座っている** 席を通り抜けてしまうと、番号 $ x $ の観客は番号 $ y $ の観客に永遠に嫌われます。各観客は、自分を永遠に嫌う観客の数が最小となるように移動方法を選びます。

番号 $ x $ の観客が番号 $ y $ の観客に永遠に嫌われるような組 $ (x,\ y) $ の個数を求めてください。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 500 $
- 列 $ P_1,\ P_2,\ \dots,\ P_{N^2} $ は $ \{1,\ 2,\ \dots,\ N^2\} $ の順列である。

### Sample Explanation 1

上映が終わる前の劇場内の観客の配置は以下の通りです。 ``` 1 2 3 4 5 6 7 8 9 ``` 劇場を出る最初の $ 4 $ 人 (番号 $ 1 $, $ 3 $, $ 7 $, $ 9 $ の観客) は席を通り抜けることなく劇場を出られるので、誰にも嫌われません。 その後、番号 $ 5 $ の観客は、劇場を出る際に番号 $ 2 $, $ 4 $, $ 6 $, $ 8 $ の観客が座る席のうちいずれかを通り抜けなければなりません。よって、番号 $ 5 $ の観客は上記の観客のうち少なくとも一人に嫌われます。 最後に残った $ 4 $ 人 (順に番号 $ 4 $, $ 8 $, $ 6 $, $ 2 $ の観客) は、人が座っている席を通り抜けずに劇場を出られます (そもそも、席を通り抜ける必要がありません)。

## 样例 #1

### 输入

```
3
1 3 7 9 5 4 8 6 2```

### 输出

```
1```

## 样例 #2

### 输入

```
4
6 7 1 4 13 16 10 9 5 11 12 14 15 2 3 8```

### 输出

```
3```

## 样例 #3

### 输入

```
6
11 21 35 22 7 36 27 34 8 20 15 13 16 1 24 3 2 17 26 9 18 32 31 23 19 14 4 25 10 29 28 33 12 6 5 30```

### 输出

```
11```

# 题解

## 作者：Free_Duck (赞：3)

## 题目大意

电影院里有 $n$ 排，$n$ 列的座位，组成一个 $n\times n$ 的正方形。所有的座位都坐满了人。

电影结束时，观众按一定顺序依次离场。观众只有达到座位广场边界才算离场完毕。观众可以从一个座位移动到其 $4$ 个相邻座位中的一个。

在离场时，某位观众 $x$ 可能会经过观众 $y$ 目前的座位；在这种情况下，观众 $y$ 将永远讨厌观众 $x$。

求出最小的使 $y$ 永远讨厌 $x$ 的观众对数 $(x, y)$。

## 解法说明

设 $dis[x][y]$ 表示第 $x$ 行，第 $y$ 列的观众当前的最少受人讨厌次数。初始时，显然 $dis[x][y]=\min\{x-1,y-1,n-x,n-y\}$ 。

然后，每次有观众离场后都暴力更新所有节点的最短路。时间复杂度貌似是 $O(n^4)$，但是初始的 $\sum_{i=1}^n \sum_{j=1}^n dis[i][j] \le n^3$，所以最多更新不超过 $n^3$ 次，时间复杂度为 $O(n^3)$。


```cpp
#include<bits/stdc++.h>
using namespace std;

int n,p,nx,ny,ans,dis[505][505],dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
bool vis[114][514];

void dfs(int x,int y){
	for(int i=0;i<4;i++){
		nx=x+dx[i],ny=y+dy[i];
		if(nx&&nx<=n&&ny&&ny<=n&&dis[nx][ny]>dis[x][y]+vis[x][y]){
			dis[nx][ny]=dis[x][y]+vis[x][y];
			dfs(nx,ny);
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[i][j]=min(min(i-1,j-1),min(n-i,n-j));
		}
	}
	memset(vis,1,sizeof(vis));
	for(int i=1;i<=n*n;i++){
		cin>>p;
		nx=(p-1)/n+1,ny=(p-1)%n+1;
		ans+=dis[nx][ny],vis[nx][ny]=0;
		dfs(nx,ny);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：licn (赞：3)

先初始化 $dis$ 数组，记录每个人最开始出去的最小不方便度。
每一次有一个人离开后，如果他的邻居也能被更新，就更新他邻居的邻居一直到不能再更新。时间复杂度看起来像 $n^4$ 的，但是每个点初始的 $dis$ 最大不超过 $n$，每一次更新最少减 $1$，那么每个点最多被更新 $n$ 次。总共有 $n^2$ 个点，时间复杂度是 $O(n^3)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3;
int n,num,head[N*N],tot,dis[N*N],ans,v[N*N];
struct node{
	int to,next;
}edge[N*N*6];
void read(int x1,int y1,int x2,int y2){
	int u=(x1-1)*n+y1;
	int v=(x2-1)*n+y2;
	tot++;
	edge[tot].to=u;
	edge[tot].next=head[v];
	head[v]=tot;
	tot++;
	edge[tot].to=v;
	edge[tot].next=head[u];
	head[u]=tot;
}
void bfs(int x){
	queue<int>q;
	q.push(x);
	while(q.size()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=edge[i].next){
			int y=edge[i].to;
			if(dis[y]>dis[x]+1-v[x]){
				dis[y]=dis[x]+1-v[x];
				q.push(y);
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			dis[(i-1)*n+j]=min(min(i-1,j-1),min(n-i,n-j));
			if(i>1)read(i,j,i-1,j);
			if(j>1)read(i,j,i,j-1);
			if(i<n)read(i,j,i+1,j);
			if(j<n)read(i,j,i,j+1);
		}
	}
	for(int i=1;i<=n*n;i++){
		int x;
		scanf("%d",&x);
		ans+=dis[x];
		v[x]=1;
		bfs(x);
	}
	printf("%d",ans);
	return 0;
}

---

