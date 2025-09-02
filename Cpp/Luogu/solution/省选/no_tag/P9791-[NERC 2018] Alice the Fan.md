# [NERC 2018] Alice the Fan

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) A 题。

## 题目描述

Alice 喜欢看排球比赛，她尤其喜欢看 A 队打球，排球比赛的规则如下：

- 一场比赛最多有 $5$ 局。

- 前面 $4$ 均需获得至少 $25$ 分方可获胜，第 $5$ 局仅需获得 $15$ 分。

- 如果单局内其中一方满足获胜条件**但是**双方比分之差不满 $2$，不算获胜。

- 有一方比分达到 $3$ 即为获胜，此时立刻结束比赛。

现在分别给你 A 队和 B 队赢球的个数，请你帮忙确定 A 队最好的比分是多少，或者确定这场球赛还没有结束。

（注：本题定义最好的比分为，如果 A 队可以赢，要使得它们两队的比分差尽可能大，反之尽可能小。）

## 说明/提示

测试数据保证 $1 \leq m \leq 50000$，$1 \leq a,b \leq 200$。

注：由于技术原因，SPJ 在评测时出现 UKE 是因为您的代码存在谬误，造成了 SPJ 读取字符时多/少读取到了，后面便无法正常评测。

## 样例 #1

### 输入

```
6
75 0
90 90
20 0
0 75
78 50
80 100```

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
25:17 0:25 25:22 15:25 15:11```

# 题解

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

