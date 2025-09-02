# [JOIST 2025] 救护车 / Ambulance

## 题目背景

由于评测机性能差距，本题增加 1 秒时限。

## 题目描述


IOI 王国被表示为一个 $L$ 行 $L$ 列的方形网格。行从上到下编号为 $1, 2, \dots, L$，列从左到右编号为 $1, 2, \dots, L$。

位于第 $i$ 行（$1 \leq i \leq L$）和第 $j$ 列（$1 \leq j \leq L$）的单元格记为 $(i, j)$。

由于近期疫情扩散，国王比太郎决定在网格的四个角落（单元格 $(1, 1)$、$(1, L)$、$(L, 1)$ 和 $(L, L)$）各建造一所医院，每所医院配备一辆救护车。救护车运输规则如下：

- 救护车可在时间 $0$ 或之后开始移动。
- 救护车会重复以下步骤（可能 $0$ 次）：  
  - 从所属医院出发 $\to$ 移动到患者位置 $\to$ 接载患者 $\to$ 返回医院并放下患者。
- 每辆救护车一次**最多**运送 $1$ 名患者。
- 救护车只能将患者送回其初始所属医院，**不可在其他位置放下患者**。
- 救护车每次移动到四连通单元格（上下左右）耗时 $1$ 单位时间。接载和放下患者的耗时忽略。
- 不同医院的救护车可同时占据同一单元格。

已知第 $k$ 名患者位于 $(X_k, Y_k)$，判断是否所有患者都能在时间 $T$ 内被运送到任意医院。


## 说明/提示


### 样例解释

#### 样例 $1$ 解释

- 将第 $1$ 和第 $2$ 个病人送往位于 $(1, 1)$ 的医院；
- 将第 $3$ 个病人送往位于 $(1, 6)$ 的医院；
- 将第 $4$ 个病人送往位于 $(6, 6)$ 的医院。

这样，所有病人都可以在第 $8$ 个时间点被送往医院，因此输出 $\texttt{Yes}$。

例如，如果停靠在 $(1, 1)$ 医院的救护车按照以下顺序移动，它可以在第 $8$ 个时间点之前将第 $1$ 和第 $2$ 个病人都送到医院。

| 时间 | 救护车状态                                      |
|:---:|------------------------------------------------|
| $0$    | 从单元格 $(1, 1)$ 出发                           |
| $1$    | 到达单元格 $(2, 1)$                              |
| $2$    | 到达单元格 $(2, 2)$，接上第 2 个病人，出发       |
| $3$    | 到达单元格 $(1, 2)$                              |
| $4$    | 到达单元格 $(1, 1)$，放下第 2 个病人，出发       |
| $5$    | 到达单元格 $(1, 2)$                              |
| $6$    | 到达单元格 $(1, 3)$，接上第 1 个病人，出发       |
| $7$    | 到达单元格 $(1, 2)$                              |
| $8$    | 到达单元格 $(1, 1)$，放下第 1 个病人             |

该样例满足子任务 $1\sim 4,6,7$ 的限制。

#### 样例 $2$ 解释

可以证明不可能做到，所以输出 $\texttt{No}$。

该样例满足所有子任务的限制。

#### 样例 $3$ 解释

该样例满足子任务 $1\sim 4,6,7$ 的限制。


#### 样例 $4$ 解释

该样例满足子任务 $4,6,7$ 的限制。







### 数据范围

- $3 \leq L \leq 10\,000$；
- $1 \leq N \leq 160$；
- $1 \leq T \leq 20\,000$；
- $1 \leq X_k, Y_k \leq L$；
- $(X_k, Y_k)$ 不与 $(1, 1), (1, L), (L, 1), (L, L)$ 的任意一个相等；
- 所有输入值为整数。


### 子任务

| 子任务 | 分数 | 特殊性质 |
|:--:| :-:| - |
| $1$      | $4 $   | $T \leq 50$ |
| $2$      | $8 $   | $T \leq 160$ |
| $3$      | $5 $   | $N \leq 10$ |
| $4$      | $18$   | $N \leq 20$ |
| $5$      | $15$   | $N \leq 45$，$L$ 为奇数，且所有患者满足 $Y_k = \frac{L+1}{2}$ |
| $6$      | $31$   | $N \leq 45$ |
| $7$      | $19$   | / |


## 样例 #1

### 输入

```
6 4 8
1 3
2 2
3 4
5 5```

### 输出

```
Yes```

## 样例 #2

### 输入

```
9 5 19
5 5
5 5
7 5
2 5
9 5```

### 输出

```
No```

## 样例 #3

### 输入

```
7 7 16
6 1
2 4
4 5
5 5
3 4
6 4
5 1```

### 输出

```
Yes```

## 样例 #4

### 输入

```
200 15 800
126 45
196 40
43 58
96 13
28 33
44 55
60 22
58 156
135 183
44 29
92 182
157 138
30 132
175 87
166 57```

### 输出

```
No```

# 题解

## 作者：BYR_KKK (赞：4)

很有意思！

四个点还是太多了，考虑进一步减少限制。若只有 $(1,1)$ 和 $(L,L)$ 两个点应该怎么办？让 $C_i$ 代表 $i$ 到 $(1,1)$ 的成本，$D_i$ 代表 $i$ 到 $(L,L)$ 的成本，此时有 $C_i+D_i$ 为一个常数。因此我们按照 $C_i$ 排序后取一个前缀到 $(1,1)$，其余点到 $(L,L)$ 即可。

这样我们有一个 $O(2^n)$ 的做法。考虑将所有点分别按照 $cost(1,1)$ 和 $cost(1,L)$ 排序，这样对于每种分组方案而言，存在两个数 $b_0$ 和 $b_1$，使得只有当 $i$ 按照第一种排序方式后位置 $\le b_0$ 才能选择 $(1,1)$（否则不能选择 $(1,1)$，可以选择 $(L,L)$），按照第二种排序方式后位置 $\le b_1$ 才能选择 $(1,L)$（否则不能选择 $(1,L)$，可以选择 $(L,1)$）。这样如果我们确定了 $b_0$ 和 $b_1$，那么所有点会被分成四组，每组存在两个选择。

接下来对于每组分别 dp。$f_i$ 代表当该组的第一个选择耗时 $i$ 时第二个选择的最小耗时。这个 dp 的总时间复杂度时 $O(nT)$ 的。对于四组的 dp 全都做完以后，考虑在第一组（两个选择分别为 $(1,1)$ 和 $(1,L)$）钦定 $(1,1)$ 的耗时，这样能得到 $(1,L)$ 的剩余时间，接着在剩下三组中贪心即可。由于需要枚举 $b_0$ 和 $b_1$，时间复杂度为 $O(n^3T)$。无法通过。

实际上我们移动 $b_0$ 和 $b_1$ 的增量只有 $1$，这意味着每次移动只会带来 $O(1)$ 个点更换组别，我们维护前缀 dp 值和后缀 dp 值可以简单做到 $O(n^2T)$。

---

## 作者：Mirasycle (赞：3)

四个医院还是太复杂了，于是先弱化一下问题，将 $4$ 个医院变成 $2$ 个，且两个医院处于对角线。

设第 $i$ 个人到医院 $(1,1)$ 的代价为 $a_i$，到医院 $(L,L)$ 的代价为 $b_i$。可以发现 $a_i+b_i$ 为一个定值，于是就是一个经典贪心，直接按照 $a_i$ 排序后，前缀分配给医院 $1$，后缀分配给医院 $2$。

扩展到四个医院，还是按照刚刚的对角线划分。我们这次引入两个对角线序列，$(1,1)$ 和 $(L,L)$ 一组，$(L,1)$ 和 $(1,L)$ 一组。对于第一组按照到 $(1,1)$ 的距离排序，对于第二组按照到 $(1,L)$ 的距离排序。

枚举两个序列中的前后缀分界点，可以将所有点分成四组，每一组中的点可以前往两个地点。于是我们直接设计一个 dp，设 $dp_{i,t}$ 表示考虑了这一组的中的前 $i$ 个元素，第一个医院用时为 $t$ 的时候，第二个医院的最小用时。对于四组分别 dp 之后，枚举 $(1,1)$ 的用时，然后利用第一组和第二组的 dp 信息可以得到到 $(1,L)$ 和到 $(L,1)$ 的最小用时，利用第三组的 dp 信息可以得到 $(L,L)$ 的最小用时，再利用第四组的 dp 信息判定 $(L,L)$ 和 $(L,1)$ 当前的用时是否合法即可。

单次 dp 是 $O(nT)$ 的，如果直接枚举分界点就是 $O(n^3T)$ 的。可以对于第一个分界点扫描线，维护下标为第二个分界点的前后缀 dp 值，这样子就可以做到 $O(n^2T)$ 了。

洛谷有点卡常，你开局就特判一下肯定无解的情况可以冲过去。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=170;
const int inf=1e9;
const int maxt=2e4+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
struct node{ int x,y; }a[maxn]; int to[maxn];
int L,n,T,p[maxn],q[maxn],dp[4][maxn][maxt];
int c1(int id){ return a[id].x+a[id].y-2; }
int c2(int id){ return a[id].x-1+L-a[id].y; }
int c3(int id){ return L-a[id].x+a[id].y-1; }
int c4(int id){ return L-a[id].x+L-a[id].y; }
bool cmp(int x,int y){ return c1(x)<c1(y); }
bool cmp2(int x,int y){ return c2(x)<c2(y); }
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>L>>n>>T; T/=2; bool flag=1; int co=T;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		cmin(co,c1(i)); cmin(co,c2(i));
		cmin(co,c3(i)); cmin(co,c4(i));
		flag&=(a[i].x==a[1].x&&a[i].y==a[1].y);
	}
	if(n/4*co>T){ cout<<"No"; return 0; }
	for(int i=1;i<=n;i++) p[i]=i,q[i]=i,to[i]=4; 
	sort(p+1,p+1+n,cmp); sort(q+1,q+1+n,cmp2);
	for(int i=0;i<=n;i++){//[1,i]->1  [i+1,n]->4
		//[1,j]->2 [j+1,n]->3
		for(int j=1;j<=n;j++){
			int u=q[j];
			for(int t=0;t<=T;t++){
				if(to[u]==1){
					dp[2][j][t]=dp[2][j-1][t];
					dp[0][j][t]=dp[0][j-1][t]+c2(u);
					if(c1(u)<=t) cmin(dp[0][j][t],dp[0][j-1][t-c1(u)]);
					if(t) cmin(dp[0][j][t],dp[0][j][t-1]);
				}else{
					dp[0][j][t]=dp[0][j-1][t];
					dp[2][j][t]=dp[2][j-1][t]+c2(u);
					if(c4(u)<=t) cmin(dp[2][j][t],dp[2][j-1][t-c4(u)]);
					if(t) cmin(dp[2][j][t],dp[2][j][t-1]);
				}
			}
		}
		for(int j=n-1;j>=0;j--){
			int u=q[j+1];
			for(int t=0;t<=T;t++){
				if(to[u]==1){
					dp[3][j][t]=dp[3][j+1][t];
					dp[1][j][t]=dp[1][j+1][t]+c3(u);
					if(c1(u)<=t) cmin(dp[1][j][t],dp[1][j+1][t-c1(u)]);
					if(t) cmin(dp[1][j][t],dp[1][j][t-1]);
				}else{
					dp[1][j][t]=dp[1][j+1][t];
					dp[3][j][t]=dp[3][j+1][t]+c3(u);
					if(c4(u)<=t) cmin(dp[3][j][t],dp[3][j+1][t-c4(u)]);
					if(t) cmin(dp[3][j][t],dp[3][j][t-1]);
				}
			}
		}
		for(int j=0;j<=n;j++){
			int z=T;
			for(int t1=0;t1<=T;t1++){//枚举 (1,1) 
				int t2=dp[0][j][t1],t3=dp[1][j][T-t1];
				if(max(t2,t3)>T) continue;
				t2=T-t2; t3=T-t3;
				if(dp[2][j][z]>t2) continue;
				while(z&&dp[2][j][z-1]<=t2) z--;
				if(dp[3][j][T-z]<=t3){ cout<<"Yes"; return 0; }
			}
		}
		to[p[i+1]]=1;
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：cwfxlh (赞：2)

## [P11986](https://www.luogu.com.cn/problem/P11986)    

不算特别难的黑。    

首先将时间 $T$ 除以二下取整，变成算距离和。令连到 $(1,1)$ 的为一类点，连接到 $(1,L)$ 的为二类点，连接到 $(L,1)$ 的为三类点，连接到 $(L,L)$ 的为四类点。  

考虑只有 $(1,1)$ 和 $(L,L)$ 怎么做，那么两个代价分别是 $x+y-2$ 和 $(L-x)+(L-y)$，于是按照 $x+y$ 排序，一类点是一段前缀，四类点是一段后缀。      

尝试枚举这段前缀的长度，于是情况变为在前缀里能选一二三类点，后缀能选二三四类点。对于二三类点而言，将 $x-y$ 排序后，二类点是一段前缀，三类点是一段后缀。   

于是对于这两段前后缀，将其分别再按 $x-y$ 排序，然后再一次枚举前后缀的分段点，在前缀后缀分别做背包，要记录的分别是二类点代价和为 $i$ 时一类点代价和的最小值，以及三类点代价和为 $i$ 时一类点代价和的最小值，然后求出这一整段内，在保证一类点代价不超过限制时，对于固定的二类点代价，三类点代价的最小值。    

每次需要求一个前后缀的背包，求 $O(n)$ 段，所以总复杂度是 $O(n^2T)$ 的。    

代码：   

```cpp
#include<bits/stdc++.h>
#define inf 10000000
using namespace std;
int L,n,lmt,dp[20003],pre[163][20003],suf[163][20003],g[163][20003];
pair<int,int>p[163];
pair<int,int>p2[163];
bool comp(pair<int,int> xx,pair<int,int> yy){return (xx.first+xx.second)<(yy.first+yy.second);}
bool comp2(pair<int,int> xx,pair<int,int> yy){return (xx.first-xx.second)<(yy.first-yy.second);}
void cln(){
	for(int j=0;j<20003;j++)dp[j]=inf;
	return;
}
void calc(int lft,int rgt,int tp){
	for(int i=lft-1;i<=rgt+1;i++){
		for(int j=0;j<=lmt;j++)g[i][j]=inf;
	}
	cln();
	dp[0]=0;
	for(int i=lft;i<=rgt;i++){
		int v1=p2[i].first+p2[i].second-2,v2=p2[i].first-1+(L-p2[i].second);
		if(tp)v1=(2*L-2)-v1;
		for(int j=lmt;j>=0;j--){
			if(dp[j]>lmt)continue;
			g[i-1][dp[j]]=min(g[i-1][dp[j]],j);
			if(j+v2<=lmt)dp[j+v2]=min(dp[j+v2],dp[j]);
			dp[j]+=v1;
		}
	}
	for(int i=0;i<=lmt;i++)if(dp[i]<=lmt)g[rgt][dp[i]]=min(g[rgt][dp[i]],i);
	for(int i=lft-1;i<=rgt;i++){
		for(int j=1;j<=lmt;j++)g[i][j]=min(g[i][j],g[i][j-1]);
	}
	cln();
	dp[0]=0;
	for(int i=rgt;i>=lft;i--){
		int v1=p2[i].first+p2[i].second-2,v2=(L-p2[i].first)+p2[i].second-1;
		if(tp)v1=(2*L-2)-v1;
		for(int j=lmt;j>=0;j--){
			if(dp[j]>lmt)continue;
			if(!tp)pre[rgt][j]=min(pre[rgt][j],g[i][lmt-dp[j]]);
			else suf[lft][j]=min(suf[lft][j],g[i][lmt-dp[j]]);
			if(j+v2<=lmt)dp[j+v2]=min(dp[j+v2],dp[j]);
			dp[j]+=v1;
		}
	}
	for(int j=lmt;j>=0;j--){
		if(dp[j]>lmt)continue;
		if(!tp)pre[rgt][j]=min(pre[rgt][j],g[lft-1][lmt-dp[j]]);
		else suf[lft][j]=min(suf[lft][j],g[lft-1][lmt-dp[j]]);
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>L>>n>>lmt;
	lmt/=2;
	for(int i=1;i<=n;i++)cin>>p[i].first>>p[i].second;
	sort(p+1,p+n+1,comp);
	for(int i=0;i<163;i++){
		for(int j=0;j<20003;j++)pre[i][j]=suf[i][j]=inf;
	}
	cln();
	pre[0][0]=suf[n+1][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)p2[j]=p[j];
		sort(p2+1,p2+i+1,comp2);
		calc(1,i,0);
		for(int j=i;j<=n;j++)p2[j]=p[j];
		sort(p2+i,p2+n+1,comp2);
		calc(i,n,1);
	}
	for(int i=0;i<=n;i++){
		for(int j=1;j<=lmt;j++){
			pre[i][j]=min(pre[i][j],pre[i][j-1]);
			suf[i][j]=min(suf[i][j],suf[i][j-1]);
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=lmt;j++){
			if(pre[i][j]+suf[i+1][lmt-j]<=lmt){cout<<"Yes";return 0;}
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：XZhuRen (赞：0)

真正的好题。

正方形平面上给你 $n$ 个点，要求每个点选定一个角到达，花费是相应的曼哈顿距离，要求四角的总时间最大值不超过 $T$，问是否存在分配方案。

设读入坐标为 $x_1,y_1$，先转切比雪夫距离，即 $x=x_1+y_1-2,y=x_1-y_1$，并将 $L-1$，则花费转化为到四边的距离：$x,L+y,2L-x,L-y$。

则现在容易画出一个十字，每个十字内的点向被划分的两个对边分配。

设 $f1$ 为第一部分到 $1$ 花费 $T$，到 $2$ 的最小花费，类比设置 $f2,f3,f4$，取前缀 $\min$ 后可以做到 $\mathcal{O}(1)$ 判定答案。

四部分划分可以扫描线，钦定一维后扫描第二维，处理前缀后缀即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=165,M=1e4+5;
const int inf=1e9+7;
int n,T,L;
void chkmn(int &x,int y){x=min(x,y);}
//规划每个患者到哪一个医院
struct Node{
	int x,y,idy;
	bool operator <(const Node&o)const{return x<o.x;}
	bool operator >(const Node&o)const{return y<o.y;}
}a[N];
int id[N];
void init(){
	scanf("%d%d%d",&L,&n,&T),T=T>>1;
	L--;
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y),x--,y--;
		a[i].x=x+y,a[i].y=x-y;
	}
	sort(a+1,a+1+n,greater<Node>());
	for(int i=1;i<=n;i++)a[i].idy=i;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)id[a[i].idy]=i;
}
int f1[N][M],f2[N][M];
int f3[N][M],f4[N][M];
void work(){
	for(int dx=0;dx<=n;dx++){
		f1[0][0]=f2[0][0]=0;
		for(int dy=1;dy<=n;dy++){
			int i=id[dy];
			for(int t=T;t>=0;t--){
				if(i<=dx){
					f2[dy][t]=f2[dy-1][t];
					f1[dy][t]=f1[dy-1][t]+(L+a[i].y);
					if(t>=a[i].x)chkmn(f1[dy][t],f1[dy-1][t-a[i].x]);
				}else{
					f1[dy][t]=f1[dy-1][t];
					f2[dy][t]=f2[dy-1][t]+(2*L-a[i].x);
					if(t>=L+a[i].y)chkmn(f2[dy][t],f2[dy-1][t-(L+a[i].y)]);
				}
			}
		}
		f3[n][0]=f4[n][0]=0;
		for(int dy=n-1;dy>=0;dy--){
			int i=id[dy+1];
			for(int t=T;t>=0;t--){
				if(i>dx){
					f4[dy][t]=f4[dy+1][t];
					f3[dy][t]=f3[dy+1][t]+(L-a[i].y);
					if(t>=(2*L-a[i].x))chkmn(f3[dy][t],f3[dy+1][t-(2*L-a[i].x)]);
				}else{
					f3[dy][t]=f3[dy+1][t];
					f4[dy][t]=f4[dy+1][t]+a[i].x;
					if(t>=(L-a[i].y))chkmn(f4[dy][t],f4[dy+1][t-(L-a[i].y)]);
				}
			}
		}
		for(int dy=0;dy<=n;dy++){
			for(int t=1;t<=T;t++)chkmn(f1[dy][t],f1[dy][t-1]),chkmn(f2[dy][t],f2[dy][t-1]);
			for(int t=1;t<=T;t++)chkmn(f3[dy][t],f3[dy][t-1]),chkmn(f4[dy][t],f4[dy][t-1]);
		}
		for(int dy=0;dy<=n;dy++){
			for(int t=0;t<=T;t++){
				int tmp=f1[dy][t];if(tmp>T)continue;
				tmp=f2[dy][T-tmp];if(tmp>T)continue;
				tmp=f3[dy][T-tmp];if(tmp>T)continue;
				tmp=f4[dy][T-tmp];if(tmp+t>T)continue;
				printf("Yes\n");
				return;
			}
		}
	}
	printf("No\n");
}
int main(){
	init();
	work();
	return 0;
}
```

---

