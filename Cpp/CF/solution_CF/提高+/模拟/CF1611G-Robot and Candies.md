# Robot and Candies

## 题目描述

Polycarp has a rectangular field of $ n \times m $ cells (the size of the $ n \cdot m $ field does not exceed $ 10^6 $ cells, $ m \ge 2 $ ), in each cell of which there can be candy. There are $ n $ rows and $ m $ columns in the field.

Let's denote a cell with coordinates $ x $ vertically and $ y $ horizontally by $ (x, y) $ . Then the top-left cell will be denoted as $ (1, 1) $ , and the bottom-right cell will be denoted as $ (n, m) $ .

If there is candy in the cell, then the cell is marked with the symbol '1', otherwise — with the symbol '0'.

Polycarp made a Robot that can collect candy. The Robot can move from $ (x, y) $ either to $ (x+1, y+1) $ , or to $ (x+1, y-1) $ . If the Robot is in a cell that contains candy, it takes it.

While there is at least one candy on the field, the following procedure is executed:

- Polycarp puts the Robot in an arbitrary cell on the topmost row of the field. He himself chooses in which cell to place the Robot. It is allowed to put the Robot in the same cell multiple times.
- The Robot moves across the field and collects candies. He controls the Robot.
- When the Robot leaves the field, Polycarp takes it. If there are still candies left, Polycarp repeats the procedure.

Find the minimum number of times Polycarp needs to put the Robot on the topmost row of the field in order to collect all the candies. It is guaranteed that Polycarp can always collect all the candies.

## 说明/提示

In the first set Polycarp may not put the Robot on the field at all, so the answer "0"

In the second set, Polycarp will need to place the robot on the field twice. The Robot can collect candies like this: for the first time Polycarp puts the Robot in the cell $ (1, 1) $ and collects candies at the positions $ (1, 1) $ and $ (3, 3) $ . The second time Polycarp can again put the Robot in $ (1, 1) $ , and then the Robot will move first to $ (2,2) $ , then to $ (3, 1) $ and collect the last candy.

In the fourth set, you can show that the Robot cannot collect all the candies in three passes.

## 样例 #1

### 输入

```
4

2 2
00
00

3 3
100
000
101

4 5
01000
00001
00010
10000

3 3
111
111
111```

### 输出

```
0
2
2
4```

# 题解

## 作者：CDFLS_mao_zx (赞：17)

## CF1611G

### 题意简述：

给定一张 $n \times m$  的 $01$ 网格图，每次选一个点 $(1,x)$ 出发，可以从 $(x,y)$ 到  $(x+1,y+1)$ 或者 $(x+1,y-1)$，问至少出发多少次才能经过每个 $1$ 至少一次。

$n  \times m \leq 10^6$

### 赛场上的一些想法（错解）：

1.考虑相邻两行，猜想其答案为每相邻两行答案的最大值，显然错误。

2.考虑转化成数字问题，发现 $x+y$ 要么增加 $2$ 要么不变，考虑按奇数偶数分类，分别处理，这个可以有，然后发现仍然不会做。

### 思路

赛场上问题的转化出现了一些问题，没有让问题变简单，所以考虑原问题。不妨先不考虑边界，如果走出了边界，直接对称回去。

我们通过观察发现不会从同一个点出发两次。考虑从左到右加入路径，如果一个点 $(1,y)$ 加入了两次，找到两次路径第一个不同的位置，找不到就说明第二条完全重复，可以删去，选择不同位置中靠右的一个，发现它一定可以通过 $(1,y+2)$  得到， $(1,y+2)$ 得到它时可以覆盖更多未覆盖的点。



然后是路径不会穿插，如果路径穿插了，那么找到第一个公共点，交换后面的部分，这样是等价的。



答案的上界是 $\lceil{\dfrac{m}{2}}\rceil \times 2$，可以构造一种方案覆盖所有点。



有了这几条性质，就可以开始贪心了。我们从 $(1,1)$ 到 $(1,n+m)$ 分别考虑加入一条路径。什么时候加入路径暂且不提，我们考虑加入的路径应该怎么走。设当前点为 $(x_0,y_0)$，如果当前对角线上 （$x+y = x_0+y_0$ 的点），存在 $(x_1,y_1)$ 满足 $x_1>x_0$ ，那么就一定走 $(x+1,y-1)$，因为现在这条路径必须覆盖掉这条对角线上剩下的点（因为路径不会穿插，后面的路径不会与当前路径相交），否则一定走 $(x+1,y+1)$，这样可以让后面能选的路径更多。



然后是什么时候应该从 $(1,i)$ 加入一条新路径，结论是当且仅当有点满足 $x+y=1+i$ 并且没被覆盖时。必要性显然。充分性，如果使用了 $(1,i)$，并且对角线没有点，那么它最开始一定是走了一段无用的 $(x+1,y+1)$，使用更后面的点替代即可。



于是用一些 `set` 维护所有满足 $x+y=i$ 的黑点，模拟刚刚的方案即可。

### 代码（目前 CF 最短)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int i,j,n,t,m,ans;
string str[N];
set<int> st[N];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m;ans=0;
		for(i=1;i<=n;i++)
		{
			cin>>str[i];
			for(j=1;j<=m;j++)
			if(str[i][j-1]=='1')st[i+j].insert(i);
		}
		for(i=1;i<=n+m;i++)
		{
			if(st[i+1].size()==0)continue;
			int pos=i;ans++;
			for(j=1;j<=n;j++)
			{
				st[j+pos].erase(j);
				if(st[j+pos].rbegin()!=st[j+pos].rend()&&*st[j+pos].rbegin()>j)pos--;
				else pos++;
			}
		}
		cout<<ans<<endl;
	}
}

```

 











---

## 作者：_Cheems (赞：2)

观察、转化，然后贪心。

显然，假如将原网格黑白染色，那么不同颜色互不影响。

考虑相同颜色，那么机器人实际上是在对角线上移动。对于一条从左上到右下的对角线，可以发现线上的点 $x+y$ 是固定的。同理，对于另一类对角线，$x-y$ 是固定的。

所以可以用数值描述一条对角线。记 $a,b$ 分别表示为经过该点的两条对角线，有 $a=x+y,b=x-y$。

容易发现，一个点可以到达的点构成一个以它为顶点的正三角。进一步观察得知，$(a,b)$ 可以到达 $(p,q)$，当且仅当 $a\le p$ 且 $b\le q$。

所以原问题转化为序列问题。首先对第一维排序，考虑第二维。那么就是求至少几个上升子序列可以将原序列覆盖。

直接贪心即可，具体的，维护当前上升子序列的末尾元素集合 $S$，假如新增一个元素 $x$，我们肯定要让 $S$ 的下界尽量小，也就是选取最大的 $p\in S$，满足 $p\le x$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int T, n, m, na, nb, ans;
char c[N];
struct node{int x, y;} A[N], B[N];

inline bool cmp(node A, node B) {return A.x == B.x ? A.y < B.y : A.x < B.x;}
inline void solve(node A[], int n){
	set<int> s;
	sort(A + 1, A + 1 + n, cmp);
	for(int i = 1; i <= n; ++i){
		if(s.empty()) s.insert(A[i].y), ++ans;
		else{
			if(*s.begin() > A[i].y) s.insert(A[i].y), ++ans;
			else{
				auto lsy = s.upper_bound(A[i].y); --lsy;
				s.erase(*lsy), s.insert(A[i].y);
			}
		}
	}
}
signed main(){
	cin >> T;
	while(T--){
		scanf("%d%d", &n, &m), ans = na = nb = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%s", c + 1);
			for(int j = 1; j <= m; ++j){
				if(c[j] == '1') 
					if((i + j) & 1) A[++na] = {i + j, i - j};
					else B[++nb] = {i + j, i - j};
			}
		}
		solve(A, na), solve(B, nb);	
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：lzyzs (赞：1)

# CF1611G Robot and Candies
## 题意
给定一张 $n×m$ 的 $01$ 网格图，每次选一个点 $(1,x)$ 出发。可以从 $(x,y)$ 到 $(x+1,y+1)$ 或者 $(x+1,y−1)$，至少出发多少次才能经过每个 $1$ 至少一次。

$(n⋅m≤1000000)$

## 思路

思考：显而易见这个图需要分奇偶。那么先只考虑一个图。

采用局部最优到整体最优的思路。

将棋盘分为 $\max(n, m)$ 条斜率为 $-1$ 的斜线 $($ 从右上角开始向左下角 $)$。

显然对于每一条斜线将会覆盖糖果或空，将每一条斜线 $line_i$ 将会覆盖的糖果储存下来。

对于什么都没有覆盖的斜线显然没有用，可以不存储。

对于覆盖了糖果的斜线一定存在**最后一颗被覆盖的糖果**显然覆盖了这个糖果以后机器人所走的路径没有贡献，可能有更大的贡献。考虑转折去覆盖其它糖果。

一个结论：若一个机器人可以覆盖一个糖果，那么这个机器人一定可以覆盖这个糖果所在直线的最后一颗糖果。

证明：因为同一条斜线上，所以一直走一定可以覆盖。

所以从左斜线到右斜线枚举每一个斜线 $line_i$ 的末尾，判断其可否到达的斜线 $line_j$ $(i < j)$ 的末尾，若可以则从 $line_j$ 的末尾向上枚举糖果 $k$，若 $k$ 可以从 $line_i$ 的末尾抵达，则在 $line_j$ 中删除 $k$，枚举完成之后, 将 $line_i$ 的末尾改为 $line_j$ 的末尾将 $line_j$ 的末尾删除，如果 $line_j$ 被删完，那么就不需要机器人去覆盖这个斜线了。将 $line_j$ 删除。$j$ 继续向下枚举。

答案为最终剩下的 $line$ 的数量。

### 剪枝
枚举过程中若一定无法达到 $line_j$ 则直接结束。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
bool cmp (pair<int, int> a, pair<int, int> b) {
	if (a.first + a.second == b.first + b.second) return a.first < b.first;
	return a.first + a.second < b.first + b.second;
}
inline bool can (pair<int, int> a, pair<int, int> b) {
	return (b.first - a.first) >= fabs(a.second - b.second) ;
}
int n, m;
vector<pair<int, int> > NG[N];
int getans(vector<pair<int, int> > G1) {
	vector<int> Z;
	sort(G1.begin(), G1.end(), cmp);
	int top = 0;
	Z.push_back(0);
	for (int i = 0; i < G1.size(); i++) {
		int u = G1[i].first + G1[i].second;
		top++;
		Z.push_back(u);
		NG[top].resize(0);
		NG[top].push_back(G1[i]);
		int j = i + 1;
		for (; j < G1.size() && G1[j].first + G1[j].second == u; j++) 
			NG[top].push_back(G1[j]);
		i = j - 1;
	}
	int ans = top;
	for (int i = 1; i < top; i++) {
		if (NG[i].size() == 0) continue;
		pair<int, int> now = NG[i][NG[i].size() - 1];
		int u = i + 1, nt = Z[i];
		while (u <= top) {
			if ((n - now.first) * 2 < Z[u] - nt) break;
			if (NG[u].size() != 0) {
				if (can(now, NG[u][NG[u].size() - 1])) {
					int j = NG[u].size() - 2;
					for (; j >= 0 && can(now, NG[u][j]); j--) ;
					now = NG[u][NG[u].size() - 1];
					nt = Z[u];
					if (j < 0) {
						ans --;
						NG[u].resize(0);
					} else {
						int nd = NG[u].size() - j - 1;
						while (nd--) NG[u].pop_back();
					}
				} 
			}
			u++;
		}
	}
	return ans;
}
void solve() {
	vector<pair<int, int> > G[2];
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		string str;
		cin >> str;
		str = " " + str;
		for (int j = 1; j <= m; j++) {
			if (((i + j) & 1) && str[j] == '1') G[0].push_back(pair<int, int>{i, j});
			if ((!((i + j) & 1)) && str[j] == '1') G[1].push_back(pair<int, int>{i, j});
		}
	}
	printf("%d\n", getans(G[0]) + getans(G[1]));
}

signed main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
	return 0;
}

```

---

