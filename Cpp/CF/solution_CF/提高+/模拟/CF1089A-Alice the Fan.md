# Alice the Fan

## 题目描述

爱丽丝是排球的忠实粉丝，特别是非常强大的“A队”。

排球比赛最多由五局组成。 在每局比赛中，球队每赢一球得`1`分。 在前四局比赛中，一旦一支球队得分至少为`25`分，本局比赛结束。而第五局比赛，一旦一支球队得分至少达到`15`分，则本局比赛结束。 此外，如果其中一支球队得分为`25`（或第五局为`15`分），而另一支球队得分为`24`（或第五局为`14`），则该局将继续下去，直到球队得分之间的绝对差异变为`2`。 当其中一支球队赢得三局时，比赛结束。比赛得分是每支球队赢得的局数。

爱丽丝找到了一本书，其中包含“A队”所有比赛的所有结果。这本书很旧，书的某些部分变得难以理解。 爱丽丝无法阅读有关每支球队赢了多少局的信息，她无法阅读每局中每支球队得分多少的信息，她甚至不知道某一场比赛中的打了多少局。 她拥有的唯一信息是在一场比赛中每支球队在所有局比赛中得分的总数。

Alice想知道“A队”在每场比赛中可以取得的最佳比赛得分是多少。 “A队”赢得的局数与对手之间的差异越大，比赛得分越高。 找到最佳比赛分数或者得出结论：没有比赛可能会得到这样结果。 

如果有多种可能方案，输出任何一种方案即可。

## 样例 #1

### 输入

```
6
75 0
90 90
20 0
0 75
78 50
80 100
```

### 输出

```
3:0
25:0 25:0 25:0
3:1
25:22 25:22 15:25 25:21
Impossible
0:3
0:25 0:25 0:25
3:0
25:11 28:26 25:13
3:2
25:17 0:25 25:22 15:25 15:11
```

# 题解

## 作者：Panda_hu (赞：4)

# 题解

仔细观察一下数据范围，发现$a,b≤200$，有点像一个$O(n^3)$的预处理暴力dp。

设$dp[A][B][x][y]$为`A队`得分总和为$A$,`B队`得分总和为$B$,现在的比分是$x:y$时是否有解。
再开一个vector $ans[A][B][x][y]$保存答案。

然后转移就很好写了:
[设$winscore$为正常情况下能够获胜的分数]
1.该局有一个队伍得分在$winscore+1$分及以上，此时两组分数相差2:
$$dp[A+val][B+val-2][x+1][y]=dp[A][B][x][y]$$
$$dp[A+val-2][B+val][x][y+1]=dp[A][B][x][y]$$
2.该局有一个队伍得分在$winscore-1$分以下，此时有一组分数为为$winscore$，另外一组的得分任意：
$$dp[A+winscore][B+val][x+1][y]=dp[A][B][x][y]$$
$$dp[A+val][B+winscore][x][y+1]=dp[A][B][x][y]$$

时间复杂度:$O(9n^3)$
# 实现
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
#include<vector>
using namespace std;
#define MAXN 200
#define LL long long
#define INF 10000
#define MOD 1000000000
#define PB push_back
#define MP make_pair
#define FR first
#define SE second
int dp[MAXN+5][MAXN+5][4][4];
vector< pair<int,int> > ans[MAXN+5][MAXN+5][4][4];
int T;
int vx[]={3,3,3,2,1,0},vy[]={0,1,2,3,3,3};
int main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	dp[0][0][0][0]=1;
	for(int A=0;A<=200;A++)
		for(int B=0;B<=200;B++)
			for(int x=0;x<=2;x++)
				for(int y=0;y<=2;y++)
				{
					int maxs=25;
					if(x+y==4)maxs=15;
					if(!dp[A][B][x][y])continue;
					for(int val=maxs+1;val<=200;val++){
						if(A+val<=200&&B+val-2<=200&&!dp[A+val][B+val-2][x+1][y]){
							dp[A+val][B+val-2][x+1][y]=1;
							ans[A+val][B+val-2][x+1][y]=ans[A][B][x][y];
							ans[A+val][B+val-2][x+1][y].PB(MP(val,val-2));
						}
						if(A+val-2<=200&&B+val<=200&&!dp[A+val-2][B+val][x][y+1]){
							dp[A+val-2][B+val][x][y+1]=1;
							ans[A+val-2][B+val][x][y+1]=ans[A][B][x][y];
							ans[A+val-2][B+val][x][y+1].PB(MP(val-2,val));
						}
					}
					for(int val=0;val<maxs-1;val++){
						if(A+maxs<=200&&B+val<=200&&!dp[A+maxs][B+val][x+1][y]){
							dp[A+maxs][B+val][x+1][y]=1;
							ans[A+maxs][B+val][x+1][y]=ans[A][B][x][y];
							ans[A+maxs][B+val][x+1][y].PB(MP(maxs,val));
						}
						if(A+val<=200&&B+maxs<=200&&!dp[A+val][B+maxs][x][y+1]){
							dp[A+val][B+maxs][x][y+1]=1;
							ans[A+val][B+maxs][x][y+1]=ans[A][B][x][y];
							ans[A+val][B+maxs][x][y+1].PB(MP(val,maxs));
						}
					}
				}
	scanf("%d",&T);
	while(T--)
	{
		int A,B,x=-1,y;
		scanf("%d%d",&A,&B);
		for(int v=0;v<6;v++)
		if(dp[A][B][vx[v]][vy[v]])
		{
			x=vx[v],y=vy[v];
			break;
		}
		if(x==-1){printf("Impossible\n");continue;}
		printf("%d:%d\n",x,y);
		for(int i=0;i<ans[A][B][x][y].size();i++)
		printf("%d:%d ",ans[A][B][x][y][i].FR,ans[A][B][x][y][i].SE);
		printf("\n");
	}
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路

发现 $0 \le a,b \le 200$，于是考虑 DP。

设 $dp_{i,j,x,y}$ 表示 A 队赢了 $i$ 分、B 队赢了 $j$ 分、A 队赢了 $x$ 场、B 队赢了 $y$ 场的情况是否合法。等于一表示合法，等于零表示不合法。

转移比较麻烦，按照题目描述一步步来。

首先考虑 $x+y = 5$ 的情况。此时是第五场，赢得本场需要 $15$ 分。枚举哪个队伍赢得本场的胜利，还要枚举输的队伍赢了多少分。所以转移：

$$dp_{i,j,x,y} = \max
\begin{cases} 
dp_{i-15,j-k,x-1,y} (0 \le k \le \min(j,13),x \ge 1,y \not = 3) \\
dp_{i-k,j-15,x,y-1} (0 \le k \le \min(i,13),y \ge 1,x \not = 3) \\
\end{cases}$$

需要注意，转移的那个状态要满足 $x \not = 3,y \not = 3$，不然比赛就直接结束了。

然后考虑加时赛。

还是枚举哪个队伍取得胜利，同时枚举比赛结束时双方得了多少分。

$$dp_{i,j,x,y} = \max
\begin{cases} 
dp_{i-k,j-k+2,x-1,y} (16 \le k \le \min(i,j)+2,x \ge 1,y \not = 3) \\
dp_{i-k+2,j-k,x,y-1} (16 \le k \le \min(i,j)+2,y \ge 1,x \not = 3) \\
\end{cases}$$

接着就是前 $1 \sim 4$ 场的情况。这跟上面是一样的。把 $15$ 改为 $25$ 即可。

最后记录当前状态是从哪里转移过来的，倒序输出即可。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m;
int dp[220][220][10][10];
struct node{
	int aa,bb,cc,dd;
};
node ans[220][220][10][10];
bool operator==(node x,node y){
	return x.aa == y.aa && x.bb == y.bb && x.cc == y.cc && x.dd == y.dd;
}
bool operator!=(node x,node y){
	return !(x == y);
}
void go_work(){
	dp[0][0][0][0] = 1;
	for(int i = 0; i <= 200; i++){
		for(int j = 0; j <= 200; j++){
			for(int x = 0; x <= 3; x++){
				for(int y = 0; y <= 3; y++){
					if(x+y == 5){
						if(i >= 15 && x >= 1 && y != 3){
							for(int q = 0; q <= min(13,j); q++){
								if(dp[i-15][j-q][x-1][y]){
									dp[i][j][x][y] = 1;
									ans[i][j][x][y] = {i-15,j-q,x-1,y};
								}
							}
						}
						if(j >= 15 && y >= 1 && x != 3){
							for(int q = 0; q <= min(13,i); q++){
								if(dp[i-q][j-15][x][y-1]){
									dp[i][j][x][y] = 1;
									ans[i][j][x][y] = {i-q,j-15,x,y-1};
								}
							}
						}
						for(int q = 16; q <= min(i,j)+2; q++){
							if(i >= q && j >= q-2 && x >= 1 && y != 3){
								if(dp[i-q][j-q+2][x-1][y]){
									dp[i][j][x][y] = 1;
									ans[i][j][x][y] = {i-q,j-q+2,x-1,y};
								}
							}
							if(i >= q-2 && j >= q && y >= 1 && x != 3){
								if(dp[i-q+2][j-q][x][y-1]){
									dp[i][j][x][y] = 1;
									ans[i][j][x][y] = {i-q+2,j-q,x,y-1};
								}
							}
						}
					}else{
						if(i >= 25 && x >= 1 && y != 3){
							for(int q = 0; q <= min(23,j); q++){
								if(dp[i-25][j-q][x-1][y]){
									dp[i][j][x][y] = 1;
									ans[i][j][x][y] = {i-25,j-q,x-1,y};
								}
							}
						}
						if(j >= 25 && y >= 1 && x != 3){
							for(int q = 0; q <= min(23,i); q++){
								if(dp[i-q][j-25][x][y-1]){
									dp[i][j][x][y] = 1;
									ans[i][j][x][y] = {i-q,j-25,x,y-1};
								}
							}
						}
						for(int q = 26; q <= min(i,j)+2; q++){
							if(i >= q && j >= q-2 && x >= 1 && y != 3){
								if(dp[i-q][j-q+2][x-1][y]){
									dp[i][j][x][y] = 1;
									ans[i][j][x][y] = {i-q,j-q+2,x-1,y};
								}
							}
							if(i >= q-2 && j >= q && y >= 1 && x != 3){
								if(dp[i-q+2][j-q][x][y-1]){
									dp[i][j][x][y] = 1;
									ans[i][j][x][y] = {i-q+2,j-q,x,y-1};
								}//l
							}//u
						}//f
					}//i
				}//t
			}//u
		}//a
	}//e
}//b
stack<pair<int,int>> prt;
int main(){
	go_work();
	scanf("%d",&t);
	while(t--){
		static node tp,now;
		scanf("%d%d",&n,&m);
		while(prt.size()){
			prt.pop();
		}
		if(dp[n][m][3][0]){
			puts("3:0");
			now = (node){n,m,3,0};
			tp = ans[n][m][3][0];
			while(now != (node){0,0,0,0}){
				prt.push({now.aa-tp.aa,now.bb-tp.bb});
				now = tp;
				tp = ans[tp.aa][tp.bb][tp.cc][tp.dd];
			}
			while(prt.size()){
				printf("%d:%d ",prt.top().first,prt.top().second);
				prt.pop();
			}
			puts("");
		}else if(dp[n][m][3][1]){
			puts("3:1");
			now = (node){n,m,3,1};
			tp = ans[n][m][3][1];
			while(now != (node){0,0,0,0}){
				prt.push({now.aa-tp.aa,now.bb-tp.bb});
				now = tp;
				tp = ans[tp.aa][tp.bb][tp.cc][tp.dd];
			}
			while(prt.size()){
				printf("%d:%d ",prt.top().first,prt.top().second);
				prt.pop();
			}
			puts("");
		}else if(dp[n][m][3][2]){
			puts("3:2");
			now = (node){n,m,3,2};
			tp = ans[n][m][3][2];
			while(now != (node){0,0,0,0}){
				prt.push({now.aa-tp.aa,now.bb-tp.bb});
				now = tp;
				tp = ans[tp.aa][tp.bb][tp.cc][tp.dd];
			}
			while(prt.size()){
				printf("%d:%d ",prt.top().first,prt.top().second);
				prt.pop();
			}
			puts("");
		}else if(dp[n][m][2][3]){
			puts("2:3");
			now = (node){n,m,2,3};
			tp = ans[n][m][2][3];
			while(now != (node){0,0,0,0}){
				prt.push({now.aa-tp.aa,now.bb-tp.bb});
				now = tp;
				tp = ans[tp.aa][tp.bb][tp.cc][tp.dd];
			}
			while(prt.size()){
				printf("%d:%d ",prt.top().first,prt.top().second);
				prt.pop();
			}
			puts("");
		}else if(dp[n][m][1][3]){
			puts("1:3");
			now = (node){n,m,1,3};
			tp = ans[n][m][1][3];
			while(now != (node){0,0,0,0}){
				prt.push({now.aa-tp.aa,now.bb-tp.bb});
				now = tp;
				tp = ans[tp.aa][tp.bb][tp.cc][tp.dd];
			}
			while(prt.size()){
				printf("%d:%d ",prt.top().first,prt.top().second);
				prt.pop();
			}
			puts("");
		}else if(dp[n][m][0][3]){
			puts("0:3");
			now = (node){n,m,0,3};
			tp = ans[n][m][0][3];
			while(now != (node){0,0,0,0}){
				prt.push({now.aa-tp.aa,now.bb-tp.bb});
				now = tp;
				tp = ans[tp.aa][tp.bb][tp.cc][tp.dd];
			}
			while(prt.size()){
				printf("%d:%d ",prt.top().first,prt.top().second);
				prt.pop();
			}
			puts("");
		}else{
			puts("Impossible");
		}
	}
	return 0;
}
```

~~说这是 DP 谁信啊，分明就是 TMD 大模拟~~。

---

## 作者：xuyifei0302 (赞：0)

因为有 $a \le 200$ 和 $b \le 200$，所以我们考虑把每一种比分和总得分的情况提前预处理出来。

我们开一个数组 $mark_{i,j,k,k1}$，表示比分为 $i ： k$，总得分分别为 $j$ 和 $k1$。对于前 $4$ 局，最大为 $25$ 分，我们考虑一下四种情况：

- 本局是以 $25$ 分结束，我们就可以从 $0$ 到 $23$ 枚举另一个队的得分，假设为 $point$。若本队获胜，则向 $mark_{i + 1,j + 25,k,k1 + point}$，反之则向 $mark_{i ,j + point,k + 1,k1 + 25}$ 转移。
- 本局是以 $15$ 分结束，我们就可以从 $0$ 到 $13$ 枚举另一个队的得分，假设为 $point$。若本队获胜，则向 $mark_{i + 1,j + 15,k,k1 + point}$，反之则向 $mark_{i ,j + point,k + 1,k1 + 15}$ 转移。

而答案只需在转移过程中记录即可。

所以总状态为 $4 \times 200 \times 4 \times 200 = 640000$。转移枚举量为 $200$。总计算量为 $128000000$，不会超时。

因为我们是要找出最好的比分，所以应从本队胜利，比分为 $3:0$ 开始枚举。

下面是代码环节：

```cpp
#include<bits/stdc++.h>
struct Node {
	int pointa, pointb;
} x[7][205][7][205][5];
using namespace std;
int m, a, b, len[7][205][7][205];
bool mark[7][205][7][205];
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	mark[0][0][0][0] = true;
	for (int i = 0; i <= 2; i ++) {
		for (int j = 0; j <= 200; j ++) {
			for (int k = 0; k <= 2; k ++) {
				for (int k1 = 0; k1 <= 200; k1 ++) {
					if (!mark[i][j][k][k1]) {
						continue;
					}
					if (i + k <= 3) {
						for (int point = 0; point <= 23; point ++) {
							if (j + 25 <= 200 && k1 + point <= 200 && !mark[i + 1][j + 25][k][k1 + point]) {
								mark[i + 1][j + 25][k][k1 + point] = mark[i][j][k][k1];
								len[i + 1][j + 25][k][k1 + point] = len[i][j][k][k1] + 1;
								for (int k2 = 1; k2 <= len[i][j][k][k1]; k2 ++) {
									x[i + 1][j + 25][k][k1 + point][k2] = x[i][j][k][k1][k2];
								}
								x[i + 1][j + 25][k][k1 + point][len[i + 1][j + 25][k][k1 + point]].pointa = 25;
								x[i + 1][j + 25][k][k1 + point][len[i + 1][j + 25][k][k1 + point]].pointb = point;
							}
							if (j + point <= 200 && k1 + 25 <= 200 && !mark[i][j + point][k + 1][k1 + 25]) {
								mark[i][j + point][k + 1][k1 + 25] = mark[i][j][k][k1];
								len[i][j + point][k + 1][k1 + 25] = len[i][j][k][k1] + 1;
								for (int k2 = 1; k2 <= len[i][j][k][k1]; k2 ++) {
									x[i][j + point][k + 1][k1 + 25][k2] = x[i][j][k][k1][k2];
								}
								x[i][j + point][k + 1][k1 + 25][len[i][j + point][k + 1][k1 + 25]].pointa = point;
								x[i][j + point][k + 1][k1 + 25][len[i][j + point][k + 1][k1 + 25]].pointb = 25;
							}
						}
						for (int point = 26; point <= 200; point ++) {
							if (j + point <= 200 && k1 + point - 2 <= 200 && !mark[i + 1][j + point][k][k1 + point - 2]) {
								mark[i + 1][j + point][k][k1 + point - 2] = mark[i][j][k][k1];
								len[i + 1][j + point][k][k1 + point - 2] = len[i][j][k][k1] + 1;
								for (int k2 = 1; k2 <= len[i][j][k][k1]; k2 ++) {
									x[i + 1][j + point][k][k1 + point - 2][k2] = x[i][j][k][k1][k2];
								}
								x[i + 1][j + point][k][k1 + point - 2][len[i + 1][j + point][k][k1 + point - 2]].pointa = point;
								x[i + 1][j + point][k][k1 + point - 2][len[i + 1][j + point][k][k1 + point - 2]].pointb = point - 2;
							}
							if (j + point - 2 <= 200 && k1 + point <= 200 && !mark[i][j + point - 2][k + 1][k1 + point]) {
								mark[i][j + point - 2][k + 1][k1 + point] = mark[i][j][k][k1];
								len[i][j + point - 2][k + 1][k1 + point] = len[i][j][k][k1] + 1;
								for (int k2 = 1; k2 <= len[i][j][k][k1]; k2 ++) {
									x[i][j + point - 2][k + 1][k1 + point][k2] = x[i][j][k][k1][k2];
								}
								x[i][j + point - 2][k + 1][k1 + point][len[i][j + point - 2][k + 1][k1 + point]].pointa = point - 2;
								x[i][j + point - 2][k + 1][k1 + point][len[i][j + point - 2][k + 1][k1 + point]].pointb = point;
							}
						}
					} else {
						for (int point = 0; point <= 13; point ++) {
							if (j + 15 <= 200 && k1 + point <= 200 && !mark[i + 1][j + 15][k][k1 + point]) {
								mark[i + 1][j + 15][k][k1 + point] = mark[i][j][k][k1];
								len[i + 1][j + 15][k][k1 + point] = len[i][j][k][k1] + 1;
								for (int k2 = 1; k2 <= len[i][j][k][k1]; k2 ++) {
									x[i + 1][j + 15][k][k1 + point][k2] = x[i][j][k][k1][k2];
								}
								x[i + 1][j + 15][k][k1 + point][len[i + 1][j + 15][k][k1 + point]].pointa = 15;
								x[i + 1][j + 15][k][k1 + point][len[i + 1][j + 15][k][k1 + point]].pointb = point;
							}
							if (j + point <= 200 && k1 + 15 <= 200 && !mark[i][j + point][k + 1][k1 + 15]) {
								mark[i][j + point][k + 1][k1 + 15] = mark[i][j][k][k1];
								len[i][j + point][k + 1][k1 + 15] = len[i][j][k][k1] + 1;
								for (int k2 = 1; k2 <= len[i][j][k][k1]; k2 ++) {
									x[i][j + point][k + 1][k1 + 15][k2] = x[i][j][k][k1][k2];
								}
								x[i][j + point][k + 1][k1 + 15][len[i][j + point][k + 1][k1 + 15]].pointa = point;
								x[i][j + point][k + 1][k1 + 15][len[i][j + point][k + 1][k1 + 15]].pointb = 15;
							}
						}
						for (int point = 16; point <= 200; point ++) {
							if (j + point <= 200 && k1 + point - 2 <= 200 && !mark[i + 1][j + point][k][k1 + point - 2]) {
								mark[i + 1][j + point][k][k1 + point - 2] = mark[i][j][k][k1];
								len[i + 1][j + point][k][k1 + point - 2] = len[i][j][k][k1] + 1;
								for (int k2 = 1; k2 <= len[i][j][k][k1]; k2 ++) {
									x[i + 1][j + point][k][k1 + point - 2][k2] = x[i][j][k][k1][k2];
								}
								x[i + 1][j + point][k][k1 + point - 2][len[i + 1][j + point][k][k1 + point - 2]].pointa = point;
								x[i + 1][j + point][k][k1 + point - 2][len[i + 1][j + point][k][k1 + point - 2]].pointb = point - 2;
							}
							if (j + point - 2 <= 200 && k1 + point <= 200 && !mark[i][j + point - 2][k + 1][k1 + point]) {
								mark[i][j + point - 2][k + 1][k1 + point] = mark[i][j][k][k1];
								len[i][j + point - 2][k + 1][k1 + point] = len[i][j][k][k1] + 1;
								for (int k2 = 1; k2 <= len[i][j][k][k1]; k2 ++) {
									x[i][j + point - 2][k + 1][k1 + point][k2] = x[i][j][k][k1][k2];
								}
								x[i][j + point - 2][k + 1][k1 + point][len[i][j + point - 2][k + 1][k1 + point]].pointa = point - 2;
								x[i][j + point - 2][k + 1][k1 + point][len[i][j + point - 2][k + 1][k1 + point]].pointb = point;
							}
						}
					}
				}
			}
		}
	}
	cin >> m;
	while (m --) {
		cin >> a >> b;
		if (mark[3][a][0][b]) {
			cout << "3:0\n";
			for (int i = 1; i <= len[3][a][0][b]; i ++) {
				cout << x[3][a][0][b][i].pointa << ":" << x[3][a][0][b][i].pointb << " ";
			}
			cout << "\n";
		} else if (mark[3][a][1][b]) {
			cout << "3:1\n";
			for (int i = 1; i <= len[3][a][1][b]; i ++) {
				cout << x[3][a][1][b][i].pointa << ":" << x[3][a][1][b][i].pointb << " ";
			}
			cout << "\n";
		} else if (mark[3][a][2][b]) {
			cout << "3:2\n";
			for (int i = 1; i <= len[3][a][2][b]; i ++) {
				cout << x[3][a][2][b][i].pointa << ":" << x[3][a][2][b][i].pointb << " ";
			}
			cout << "\n";
		} else if (mark[2][a][3][b]) {
			cout << "2:3\n";
			for (int i = 1; i <= len[2][a][3][b]; i ++) {
				cout << x[2][a][3][b][i].pointa << ":" << x[2][a][3][b][i].pointb << " ";
			}
			cout << "\n";
		} else if (mark[1][a][3][b]) {
			cout << "1:3\n";
			for (int i = 1; i <= len[1][a][3][b]; i ++) {
				cout << x[1][a][3][b][i].pointa << ":" << x[1][a][3][b][i].pointb << " ";
			}
			cout << "\n";
		} else if (mark[0][a][3][b]) {
			cout << "0:3\n";
			for (int i = 1; i <= len[0][a][3][b]; i ++) {
				cout << x[0][a][3][b][i].pointa << ":" << x[0][a][3][b][i].pointb << " ";
			}
			cout << "\n";
		} else {
			cout << "Impossible\n";
		}
	}
	return 0;
}
```

---

## 作者：daiarineko (赞：0)

## 题意简述

一场大分为 FT3、小分为 FT25+2（Tiebreaker 为 FT15+2）的比赛中 A 和 B 分别获得了 a 和 b 个小分，请构造每小局中两方的得分情况使得两方总小分等于对应值或报告无解，在此基础上最大化 A 的大分 - B 的大分，多（$5 \times 10^4$）次询问。

## 思路

首先我们可能会想到找规律或者贪心。不过注意到 $a, b \leq 200$，可以考虑 dp。

设 $dp_{r, w, a, b}$ 为比赛进行了 $r$ 轮，A 赢了 $w$ 轮，总小分分别为 $a$ 和 $b$ 时，两方大分之差的最大值。

考虑每次枚举比分，这看起来复杂度很高，但我们只需要枚举一方 $25$ 分的情况和两方进入加赛的情况，即 `0-25 1-25 ... 23-25 24-26 25-27 ... , 25-0 25-1 ... 25-23 26-24 27-25 ...` 这 $O(n)$ 个情况，总的复杂度是 $O(n^3m)$，带一个较大的常数。

然后考虑如何能够把 $m$ 消去。发现询问除了 $a, b$ 没有额外变量，意味着我们可以预处理进行 DP，这样复杂度就变成了 $O(n^3 + m)$。

找路径的方法就是套路，考虑记录每个 DP 状态的转移来源即可，这里的转移来源则为最后一局两方的小分，使用 `std::pair<int, int>` 存储。

细节还是不少的，比如一方 3 大分之后不能继续比赛这种。

## 代码

```cpp
#include <bits/stdc++.h>
using ll = long long;

int m, a, b;
int dp[6][6][205][205];
std::pair<int, int> from[6][6][205][205];
std::vector<std::pair<int, int>> tmp;
void trans(int r, int w, int a, int b, int a0, int b0) {
  if (a0 > a || b0 > b || (a0 > b0 && !w)) return;
  if (w == 3 && !(a0 > b0)) return;
  if (w == r - 3 && !(a0 < b0)) return;
  int res = dp[r - 1][w - (a0 > b0)][a - a0][b - b0];
  if (a0 > b0) ++res;
  else --res;
  if (dp[r][w][a][b] < res) {
    dp[r][w][a][b] = res;
    from[r][w][a][b] = {a0, b0};
  }
}
int main() {
  std::memset(dp, -0x3f, sizeof dp);
  dp[0][0][0][0] = 0;
  for (int r = 1; r <= 5; ++r) {
    for (int w = 0; w <= r && w <= 3; ++w) {
      int mx = (r == 5) ? 15 : 25;
      for (int a = 0; a <= 200; ++a) {
        for (int b = 0; b <= 200; ++b) {
          from[r][w][a][b] = {-1, -1};
          for (int i = 0; i <= mx - 2; ++i) {
            trans(r, w, a, b, mx, i);
            trans(r, w, a, b, i, mx);
          }
          for (int i = mx + 1; i <= 200; ++i) {
            trans(r, w, a, b, i, i - 2);
            trans(r, w, a, b, i - 2, i);
          }
        }
      }
    }
  }
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cin >> m;
  while (m--) {
    std::cin >> a >> b;
    int ans = -0x3f3f3f3f, ansid = 0, answa = 0;
    for (int r = 3; r <= 5; ++r) {
      int w = 3;
      if (dp[r][w][a][b] > ans) ans = dp[r][w][a][b], ansid = r, answa = w;
      w = r - 3;
      if (dp[r][w][a][b] > ans) ans = dp[r][w][a][b], ansid = r, answa = w;
    }
    int r = ansid, sa = 0, sb = 0, w = answa;
    tmp.clear();
    while (r) {
      auto [a0, b0] = from[r][w][a][b];
      tmp.emplace_back(a0, b0);
      --r;
      a -= a0;
      b -= b0;
      if (a0 == -1) {
        a = 1;
        break;
      }
      if (a0 > b0) ++sa, --w;
      else ++sb;
    }
    if (a || b) std::cout << "Impossible\n";
    else {
      std::cout << sa << ':' << sb << '\n';
      for (auto i = tmp.rbegin(); i != tmp.rend(); ++i) {
        std::cout << i->first << ':' << i->second << ' ';
      }
      std::cout << '\n';
    }
  }
  std::cout.flush();
  return 0;
}
```

## 后记

简单看了一下之前的那篇题解，这两个做法应该是类似但不完全相同的（）我的常数会大一些。以及我认为我的码风比较好看（逃）

---

