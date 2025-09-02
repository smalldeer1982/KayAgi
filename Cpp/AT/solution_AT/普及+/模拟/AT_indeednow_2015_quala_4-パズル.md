# パズル

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-quala/tasks/indeednow_2015_quala_4

あなたには、以下のような縦 $ H $マス、横 $ W $ マスのスライドパズルの盤面が与えられます(図1)。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_indeednow_2015_quala_4/27c449b69b0c35720b6d1bee41096f7623a661f9.png)  
図1. スライドパズル盤面

   
各マスには、相異なる $ 1 $ から $ H×W-1 $ までの番号が割り振られており、さらにある $ 1 $ つのマスは空きマスとなっています。

このスライドパズルでは、空白マスを左右上下のマスのいずれかと入れ替える操作が許されています。 ただし、入れ替えたい方向にマスが存在しない場合は入れ替えることができません。

この盤面に入れ替え操作を任意の回数行い、完成の状態にしたいと思っています。 ここで、完成の状態とは、左上のマスから順番に番号付けされており右下が空白マスであるような状態にしたいと思っています(図2)。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_indeednow_2015_quala_4/0618fe48636154c76d651eb5484bdec3557384e5.png)  
図2. 完成盤面

   
つまり、完成盤面とは、

- 番号 $ i\ (1≦i≦H×W-1) $ のマスは $ (1+[(i-1)÷W],1+(i-1)%W) $ にある
- さらに、空きマスが $ (H,W) $ にある

という状態を指します。$ [a÷b] $ は $ a $ を $ b $ で割った値の小数点以下を切り捨てたもの、$ a%b $ は $ a $ を $ b $ で割った余りを指します。

最小操作数が $ 24 $ 回以内ということが保障されているとき、パズルを解くのに必要な最小操作数を出力しなさい。

## 说明/提示

### Sample Explanation 1

最初、空きマスは $ (1,2) $ にあります。この空きマスを「右→下→下」と動かすことで完成の状態にすることができ、そのとき最小操作回数を達成します。

### Sample Explanation 4

パズルが元から完成している場合もあります。

### Sample Explanation 5

出力する答えが最大となるケースです。

## 样例 #1

### 输入

```
3 3
1 0 2
4 5 3
7 8 6```

### 输出

```
3```

## 样例 #2

### 输入

```
3 5
6 1 2 8 5
7 0 4 3 10
11 12 13 9 14```

### 输出

```
12```

## 样例 #3

### 输入

```
2 2
1 2
3 0```

### 输出

```
0```

## 样例 #4

### 输入

```
4 4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 0```

### 输出

```
0```

## 样例 #5

### 输入

```
6 6
1 2 3 4 5 6
14 15 10 16 11 12
8 9 19 17 0 18
7 13 20 22 23 24
25 26 21 28 29 30
31 32 27 33 34 35```

### 输出

```
24```

# 题解

## 作者：zzhbpyy (赞：2)

### [传送门](https://atcoder.jp/contests/indeednow-quala/tasks/indeednow_2015_quala_4)

A* 板子题，也是 [P1379](https://www.luogu.com.cn/problem/P1379) 的经验。不知道 A* 的同学可以看这里：[A* - OI Wiki](https://oi-wiki.org/search/astar/)。

此题以现在状态和终态不同的格数作为估价函数，我们将估价函数与走都这一状态花的步数相加塞入小根堆中，每次取出最小的枚举即可。

## 完整代码

```c++
#include<bits/stdc++.h>
using namespace std;
struct Node{
	int a[8][8];
}t;
int n,m,ans[8][8],di[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
map<Node,int>mp;
map<Node,bool>vis;
inline bool operator<(Node a,Node b){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a.a[i][j]!=b.a[i][j])return a.a[i][j]<b.a[i][j];
		}
	return false;
}
inline int gujia(Node a){
	int res=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			res+=(a.a[i][j]!=ans[i][j]);
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>m;int ooo=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)cin>>t.a[i][j],ans[i][j]=++ooo;
	}
	ans[n][m]=0;//构造终态
	priority_queue<pair<int,Node>,vector<pair<int,Node>>,greater<pair<int,Node>>>q;
	q.push({0,t});
	while(!q.empty()){
		auto g=q.top().second;q.pop();
		int gg=gujia(g);
		if(!gg)cout<<mp[g]<<'\n',exit(0);
		int _=0,__=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)if(g.a[i][j]==0){_=i,__=j;goto UU;}//找到0的位置
		UU:;
		for(int i=0;i<=3;i++){
			int s=_+di[i][0],t=__+di[i][1];//枚举向每个方向交换
			if(s<=0||s>n||t>m||t<=0)continue;
			auto h=g;
			swap(h.a[_][__],h.a[s][t]);
			if(mp[h]&&mp[g]+1>mp[h])continue;//若有更少步数到达这一状态的方法则不塞入堆中
			mp[h]=mp[g]+1;
			q.push({gujia(h)+mp[h],h});
		}
	}
}
```

---

## 作者：Li_Yichen (赞：0)

迭代加深搜索板题。目标矩阵需要根据输入预处理，首先定义期望步数为与目标不同点的数量，然后每次当前步数加期望步数超过最大步骤的直接剪枝，注意每次需要回溯恢复现场。每次到达最大步数时，期望步数为零时为完成，直接返回即可，注意答案要加换行。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int to[10][10];
int a[10][10];
int dx[] = {0,1,-1,0};
int dy[] = {1,0,0,-1};
int ans;
int flag;
int sx,sy;
void init(){
    int cnt = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i == n && j == m) to[i][j] = 0;
            else to[i][j] = ++ cnt;
        }
    }
}
int value(){
    int val = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j] != to[i][j]) val ++;
        }
    }
    return val;
}
void dfs(int x,int y,int exstep,int step){
    if(step == ans){
        if(!exstep) flag = 1;
        return ; 
    }
    for(int i=0;i<4;i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
        swap(a[nx][ny],a[x][y]);
        int now = value();
        if(now + step <= ans){
            dfs(nx,ny,now,step+1);
            if(flag) return ;
        }
        swap(a[nx][ny],a[x][y]);
    }
}
int main(){
    cin >> n >> m;
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> a[i][j];
            if(!a[i][j]){
                sx = i;
                sy = j;
            }
        }
    }
    while(1){
        dfs(sx,sy,value(),0);
        if(flag){
            cout << ans;
            return 0;
        }
        ans ++;
    }
    return 0;
}
```

---

