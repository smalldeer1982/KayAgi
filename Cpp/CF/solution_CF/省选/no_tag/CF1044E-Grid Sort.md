# Grid Sort

## 题目描述

给你一个 $n \times m$ 的网格。网格的每个单元格内填充了从 $1$ 到 $nm$ 的唯一整数，每个整数只出现一次。

每次操作，你可以选择网格中的任意一个环，然后让这个环上的所有整数顺时针移动一个位置。一个“环”需要满足以下条件：

- 至少包含四个方格；
- 每个方格在环中至多出现一次；
- 每对相邻方格（包括第一个和最后一个方格）必须共享一个边。

例如，看下面的网格：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044E/ddc1310958686d8165141874c4116974e680c504.png)

我们可以选择一个这样的环：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044E/7e671f37a2d95c9ff29f9b01e59e68feea0624a5.png)

执行操作后得到的新网格是：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1044E/0080a8fe7414955dbaf5a00f8b4368121f12f705.png)

在此例中，所选择的环可以表示为序列 $[1, 2, 3, 6, 5, 8, 7, 4]$，数字按所希望的旋转方向排列。

请找到一系列操作，将网格有序化，使得从上到下连接每一行后形成的数组是排序好的（参见上面的第一张图）。

注意，不必追求最小化操作次数或环的总长度。惟一的要求是：所有环的长度总和不能超过 $10^5$。在当前约束条件下，可以保证总有解。你只需输出一个有效的步骤序列来实现网格的排序。

## 样例 #1

### 输入

```
3 3
4 1 2
7 6 3
8 5 9
```

### 输出

```
1
8 1 4 7 8 5 6 3 2```

## 样例 #2

### 输入

```
3 5
1 2 3 5 10
11 6 4 14 9
12 7 8 13 15
```

### 输出

```
3
4 4 14 13 8
4 5 10 9 4
4 12 7 6 11
```

# 题解

## 作者：xtx1092515503 (赞：3)

一定不是最优，但可能是最清晰的解法。

------

首先，我们觉得旋转太奇怪的环没有意义。不妨考虑只旋转 $2\times2$ 矩形，这样来构造方案。

然后考虑用只旋转 $2\times2$ 矩形的策略来处理 $3\times3$ 矩阵的排序。

排序的单位操作是交换两个位置的值而不改变其它位置的值。于是我们考虑用 $2\times2$ 矩形实现上述交换操作。

那就搜吧。搜完发现交换 $3\times3$ 矩阵中任意两个位置而不改变其它位置的值最多只需要旋转 $5$ 次 $2\times2$ 的正方形。

只要能做到交换 $3\times3$ 中两个位置的值，那就一定能处理 $n\times m$ 的情形，也即只旋转 $2\times2$ 矩形的策略是可行的。

现在考虑正解。我们可以想到从上到下、从左往右依次把每个位置填入它应该填的数。

假如每次交换都采取 $3\times3$ 矩阵中的方法的话，总次数是 $20\times20\times40\times5\times4=320000$ 的。超出太多了，我们需要贪污一些。

假设我们现在考虑到了位置 $(x,y)$，且应该填入此位置的元素位于 $(X,Y)$。则应有（$X>x$）或（$X=x$ 但 $Y>y$），因为 $(x,y)$ 前的位置都已经归位了。

我们发现，这一路上大部分位置都是没有必要使用 $3\times3$ 矩阵的，直接转 $2\times2$ 即可。但这需要保证该 $2\times2$ 矩阵所有元素都不在已经排好序的位置内，不然会打乱已经排好的位置。

我们考虑首先将 $Y$ 移到 $y$。

显然，若 $X$ 不在最后一行，我们一定可以通过旋转 $\begin{bmatrix}(X,Y)&(X,Y+1)\\(X+1,Y)&(X+1,Y+1)\end{bmatrix}$ 子矩阵做到 $Y$ 右移一位。$Y$ 左移类似。

若 $X$ 在最后一行，但 $x$ 不在最后或倒数第二行，我们可以先将 $(X,Y)$ 向上移动一格，然后也类似地左移右移即可。

若上述条件都不满足，即 $X$ 在最后一行且 $x$ 在最后或倒数第二行，我们可以直接用最上面搜出来的”交换 $3\times3$ 矩阵中任意两个位置而不改变其它位置的值“的策略来进行移动。

重复执行上述策略，显然最后 $Y$ 一定会被移到 $y$。

然后考虑将 $X$ 移到 $x$。也可以类似得到——这里是分 $Y$ 是否在最后一列，如果是则采取 $3\times3$ 矩阵的方法，不是则转 $\begin{bmatrix}(X,Y-1)&(X,Y)\\(X+1,Y-1)&(X+1,Y)\end{bmatrix}$。

显然这么操作过后，一定移到了其目标位置。

下面考虑分析次数。显然，对于大部分位置，最多只需要常规旋转 $40$ 次（横向 $20$ 次，纵向 $20$ 次）即可到达目标位置。$20\times20\times40\times4=64000$，绰绰有余。

对于最后一行和最后一列的位置，其可能需要调用 $3\times3$ 矩阵，每次 $5$ 次旋转。但是这种位置不会超过 $40$ 个，$40\times5\times40\times 4=32000$。

二者加起来 $96000$。刚好满足 $10^5$ 的限制，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define all(x) x.begin(),x.end()
int dis[362880];
int rex[8][4]={
{0,0,1,1},
{0,0,1,1},
{1,1,2,2},
{1,1,2,2},
{0,1,1,0},
{0,1,1,0},
{1,2,2,1},
{1,2,2,1}
},rey[8][4]={
{0,1,1,0},
{1,2,2,1},
{0,1,1,0},
{1,2,2,1},
{0,0,1,1},
{1,1,2,2},
{0,0,1,1},
{1,1,2,2},
};
int appr[362880],las[362880];
vector<int>trans[3][3][3][3];
int code(int*a){
	int ret=0;
	for(int i=0;i<9;i++){
		ret=1ll*ret*(9-i);
		for(int j=i+1;j<9;j++)ret+=(a[i]>a[j]);
	}
	return ret;
}
void deco(int val,int*a){
	static bool cho[9];
	for(int i=8;i>=0;i--)a[i]=val%(9-i),val/=9-i,cho[i]=false;
	for(int i=0;i<9;i++)for(int j=0;j<9;j++)if(!cho[j]&&!a[i]--){a[i]=j,cho[j]=true;break;}
}
void print(int*a){for(int i=0;i<3;i++){for(int j=0;j<3;j++)printf("%d",a[i*3+j]);puts("");}puts("");}
void mo(int*a,int id){
	int tmp=a[rex[id][3]*3+rey[id][3]];
	for(int i=2;i>=0;i--)a[rex[id][i+1]*3+rey[id][i+1]]=a[rex[id][i]*3+rey[id][i]];
	a[rex[id][0]*3+rey[id][0]]=tmp;
}
int a[9];
queue<int>q;
void bfs(){
	memset(dis,-1,sizeof(dis)),dis[0]=0,q.push(0);
//	for(int i=0;i<8;i++){for(int j=0;j<4;j++)printf("(%d,%d)",rex[i][j],rey[i][j]);puts("");}
	while(!q.empty()){
		int x=q.front(),y;q.pop();
//		printf("%d\n",x);
		deco(x,a);
//		print(a);
		for(int i=0;i<8;i++){
			mo(a,i);
			y=code(a);
			if(dis[y]==-1)dis[y]=dis[x]+1,las[y]=x,appr[y]=i,q.push(y);
			mo(a,i^4);
		}
	}
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int I=0;I<3;I++)for(int J=0;J<3;J++){
		if(i==I&&j==J)continue;
		for(int k=0;k<9;k++)a[k]=k;
		swap(a[i*3+j],a[I*3+J]);
		int x=code(a);
		while(x)trans[i][j][I][J].push_back(appr[x]),x=las[x];
		reverse(all(trans[i][j][I][J]));
//		printf("(%d,%d)->(%d,%d)",i,j,I,J);for(auto k:trans[i][j][I][J])printf("%d ",k);puts("");
	}
}
int n,m,b[1000];
vector<vector<int> >v;
void MOVE(vector<int>x,vector<int>y){
	vector<int>u;
	for(int i=0;i<4;i++)u.push_back(b[x[i]*m+y[i]]);
	v.push_back(u);
	int tmp=b[x[3]*m+y[3]];
	for(int i=2;i>=0;i--)b[x[i+1]*m+y[i+1]]=b[x[i]*m+y[i]];
	b[x[0]*m+y[0]]=tmp;
}
void MOVE(int x,int y,int id){
	vector<int>X(4),Y(4);
	for(int i=0;i<4;i++)X[i]=rex[id][i]+x,Y[i]=rey[id][i]+y;
	MOVE(X,Y);
}
void MOVE(int x,int y,int X,int Y){
	int xx=max(0,max(x,X)-2);
	int yy=max(0,max(y,Y)-2);
	x-=xx,y-=yy,X-=xx,Y-=yy;
	for(auto i:trans[x][y][X][Y])MOVE(xx,yy,i); 
}
void Rightward(int&x,int&y){
	if(x==n-1)MOVE(x,y,x,y+1);
	else MOVE({x,x,x+1,x+1},{y,y+1,y+1,y});
	y++;
}
void Leftward(int&x,int&y){
	if(x==n-1)MOVE(x,y,x,y-1);
	else MOVE({x,x,x+1,x+1},{y,y-1,y-1,y});
	y--;
}
void Upward(int&x,int&y){
	if(y==m-1)MOVE(x,y,x-1,y);
	else MOVE({x-1,x-1,x,x},{y,y+1,y+1,y});
	x--;
}
int main(){
	bfs();
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)scanf("%d",&b[i*m+j]);
	for(int i=0;i<n*m;i++){
		int x=i/m,y=i%m,X,Y;
		for(int j=i;j<n*m;j++)if(b[j]==i+1)X=j/m,Y=j%m;
		if(x==X&&y==Y)continue;
		if(X==n-1&&x<n-2)Upward(X,Y);
		while(Y<y)Rightward(X,Y);
		while(Y>y)Leftward(X,Y);
		while(X>x)Upward(X,Y);
//		for(int i=0;i<n;i++){for(int j=0;j<m;j++)printf("%d ",b[i*m+j]);puts("");}
	}
	printf("%d\n",v.size()); 
	for(auto i:v){printf("%d ",i.size());for(auto j:i)printf("%d ",j);puts("");}
	return 0;
}
```



---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/1044/problem/E) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1044E)

114514 年前某培训机构讲的题。最近终于抽着星期天的空补掉了（

首先碰到这类题目我们可以套路化地想到**归纳构造**，具体来说我们考虑逐步将一行 / 一列上的元素归位，方便起见如果 $n>m$ 就将最后一行复原成 $(n-1)m+1,(n-1)m+2,\cdots,nm$，否则将最后一列复原成 $m,2m,3m,\cdots,nm$。

如何复原一行呢？我们很明显可以想到这样的策略**先两个数配对两两复原，如果 $m$ 是奇数那就最后三个批量复原**，即，我们先将 $(n-1)m+1$ 放到 $(1,1)$ 的位置，再将 $(n-1)m+2$ 放到 $(2,1)$ 的位置，然后绕一个大圈将它们绕到 $(n,1)$ 和 $(n,2)$，然后再对 $(n-1)m+3$ 和 $(n-1)m+4$ 做同样的操作即可。绕圈圈这一部分最无脑的办法是将包含 $(1,1),(2,1),(n,1),(n,2)$ 的四个格子的最小环找到然后不断绕直到 $(n,1),(n,2)$ 的位置，但这样 $\sum |S|$ 是四方的。更优的办法是只绕 $2\times 2$ 的环，这样 $\sum |S|$ 就变成三方了，不加卡常通过此题的限制无压力。

注意到我们上面的归纳对于 $n\le 3,m\le 3$ 是行不通的，而此题 $n,m$ 下界刚好是 $3$，因此我们还需要解决 $n=3,m=3$ 的问题，这种情况想怎么做就怎么做，感觉上 DFS/BFS 都是可以的，时间复杂度 $9!·9^2$，但是不知道为什么我的 DFS 要 4w 多步所以就写了 BFS。

跑得巨慢且写得巨垃圾的代码，真心不建议看：

```cpp
const int MAXN = 20;
vector<vector<int> > ans;
int n, m, a[MAXN + 2][MAXN + 2], ought[MAXN + 2][MAXN + 2];
void rotate() {
	static int tmp_a[MAXN + 2][MAXN + 2], tmp_ought[MAXN + 2][MAXN + 2];
	memset(tmp_a, 0, sizeof(tmp_a)); memset(tmp_ought, 0, sizeof(tmp_ought));
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		tmp_a[j][i] = a[i][j], tmp_ought[j][i] = ought[i][j];
	swap(n, m);
	memset(a, 0, sizeof(a)); memset(ought, 0, sizeof(ought));
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		a[i][j] = tmp_a[i][j], ought[i][j] = tmp_ought[i][j];
}
void opt(vector<pii> vec) {
	vector<int> A; for (pii p : vec) A.pb(a[p.fi][p.se]); ans.pb(A);
	static int b[MAXN + 2][MAXN + 2];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) b[i][j] = a[i][j];
	for (int i = 0; i < vec.size(); i++) b[vec[(i + 1) % vec.size()].fi][vec[(i + 1) % vec.size()].se] = a[vec[i].fi][vec[i].se];
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] = b[i][j];
}
void work(int v, int x, int y) {
	int nx = 0, ny = 0;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (a[i][j] == v) nx = i, ny = j;
	while (nx > x) {
		if (ny != m) opt(vector<pii>{mp(nx, ny), mp(nx - 1, ny), mp(nx - 1, ny + 1), mp(nx, ny + 1)});
		else opt(vector<pii>{mp(nx, ny), mp(nx - 1, ny), mp(nx - 1, ny - 1), mp(nx, ny - 1)});
		nx--;
	}
	while (nx < x) {
		if (ny != m) opt(vector<pii>{mp(nx, ny), mp(nx + 1, ny), mp(nx + 1, ny + 1), mp(nx, ny + 1)});
		else opt(vector<pii>{mp(nx, ny), mp(nx + 1, ny), mp(nx + 1, ny - 1), mp(nx, ny - 1)});
		nx++;
	}
	while (ny > y) opt(vector<pii>{mp(nx, ny), mp(nx, ny - 1), mp(nx + 1, ny - 1), mp(nx + 1, ny)}), ny--;
}
namespace Three_Times_Three {
	const int MAXC = 362880;
	vector<int> CYC[12] = {
	vector<int>{0, 1, 4, 3},
	vector<int>{3, 4, 7, 6},
	vector<int>{1, 2, 5, 4},
	vector<int>{4, 5, 8, 7},
	vector<int>{0, 1, 4, 7, 6, 3},
	vector<int>{1, 2, 5, 8, 7, 4},
	vector<int>{0, 1, 2, 5, 4, 3},
	vector<int>{3, 4, 5, 8, 7, 6},
	vector<int>{0, 1, 4, 5, 8, 7, 6, 3},
	vector<int>{0, 1, 2, 5, 8, 7, 4, 3},
	vector<int>{0, 1, 2, 5, 4, 7, 6, 3},
	vector<int>{1, 2, 5, 8, 7, 6, 3, 4}
	};
	bool vis[MAXC + 5];
	vector<vector<int> > pth[MAXC + 5];
	int calc(vector<int> vec) {
		int prd = 1, res = 0;
		for (int i = 8; ~i; i--) {
			int sum = 0;
			for (int j = i + 1; j < 9; j++) sum += vec[j] < vec[i];
			res += sum * prd; prd *= (9 - i);
		}
		return res;
	}
	void solve33() {
		queue<vector<int> > q; vector<int> st, ed;
		for (int i = 1; i <= 3; i++) for (int j = 1; j <= 3; j++) st.pb(a[i][j]), ed.pb(ought[i][j]);
		q.push(st);
		while (!q.empty()) {
			vector<int> vec = q.front(); q.pop(); int ID = calc(vec);
			if (vec == ed) {for (auto v : pth[ID]) ans.pb(v); break;}
			for (int i = 0; i < 12; i++) {
				vector<int> tmp = vec;
				for (int j = 0; j < CYC[i].size(); j++) tmp[CYC[i][(j + 1) % CYC[i].size()]] = vec[CYC[i][j]];
				int nID = calc(tmp);
				if (!vis[nID]) {
					pth[nID] = pth[ID]; vector<int> trs;
					for (int x : CYC[i]) trs.pb(vec[x]);
					pth[nID].pb(trs); vis[nID] = 1;
					q.push(tmp);
				}
			}
		}
	}
} using namespace Three_Times_Three;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		scanf("%d", &a[i][j]), ought[i][j] = (i - 1) * m + j;
	while (n > 3 || m > 3) {
		if (n < m) rotate();
		auto deal2 = [&](int id) {
			work(ought[n][id + 1], 1, 1); work(ought[n][id], 2, 1);
			for (int i = 1; i <= n - 3; i++) opt(vector<pii>{mp(i, 1), mp(i + 1, 1), mp(i + 2, 1), mp(i + 2, 2), mp(i + 1, 2), mp(i, 2)});
			opt(vector<pii>{mp(n - 2, 1), mp(n - 1, 1), mp(n - 1, 2), mp(n - 2, 2)});
			for (int i = 1; i < id; i++) opt(vector<pii>{mp(n - 1, i), mp(n - 1, i + 1), mp(n - 1, i + 2), mp(n - 2, i + 2), mp(n - 2, i + 1), mp(n - 2, i)});
			opt(vector<pii>{mp(n - 1, id), mp(n - 1, id + 1), mp(n, id + 1), mp(n, id)});
			opt(vector<pii>{mp(n - 1, id), mp(n - 1, id + 1), mp(n, id + 1), mp(n, id)});
		};
		auto deal3 = [&](int id) {
			work(ought[n][id + 2], 1, 1); work(ought[n][id + 1], 2, 1); work(ought[n][id], 3, 1);
			for (int i = 1; i <= n - 4; i++) opt(vector<pii>{mp(i, 1), mp(i + 1, 1), mp(i + 2, 1), mp(i + 3, 1), mp(i + 3, 2), mp(i + 2, 2), mp(i + 1, 2), mp(i, 2)});
			opt(vector<pii>{mp(n - 3, 1), mp(n - 2, 1), mp(n - 1, 1), mp(n - 1, 2), mp(n - 2, 2), mp(n - 3, 2)});
			opt(vector<pii>{mp(n - 2, 1), mp(n - 1, 1), mp(n - 1, 2), mp(n - 1, 3), mp(n - 2, 3), mp(n - 2, 2)});
			for (int i = 1; i < id; i++) opt(vector<pii>{mp(n - 1, i), mp(n - 1, i + 1), mp(n - 1, i + 2), mp(n - 1, i + 3), mp(n - 2, i + 3), mp(n - 2, i + 2), mp(n - 2, i + 1), mp(n - 2, i)});
			opt(vector<pii>{mp(n - 1, id), mp(n - 1, id + 1), mp(n - 1, id + 2), mp(n, id + 2), mp(n, id + 1), mp(n, id)});
			opt(vector<pii>{mp(n - 1, id), mp(n - 1, id + 1), mp(n - 1, id + 2), mp(n, id + 2), mp(n, id + 1), mp(n, id)});
			opt(vector<pii>{mp(n - 1, id), mp(n - 1, id + 1), mp(n - 1, id + 2), mp(n, id + 2), mp(n, id + 1), mp(n, id)});
		};
		if (m % 2 == 0) {
			for (int i = 1; i <= m; i += 2) deal2(i);
		} else {
			for (int i = 1; i <= m - 3; i += 2) deal2(i);
			deal3(m - 2);
		}
		n--;
	}
	solve33();
	printf("%d\n", (int)ans.size());
	for (auto v : ans) {
		printf("%d", (int)v.size());
		for (int x : v) printf(" %d", x);
		printf("\n");
	}
	return 0;
}
/*
4 4
9 5 8 11
2 13 7 4
15 1 3 6
10 16 12 14
*/
```



---

