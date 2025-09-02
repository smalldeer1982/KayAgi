# [CERC2016] 舞动的盘子 Dancing Disks

## 题目描述

Luka 非常擅长解决汉诺塔问题，他发明了一种类似汉诺塔的使用盘子和柱子的游戏。这个游戏有 $n$ 个不同大小的盘子以及 $36$ 根柱子。盘子按照大小从小到大依次被编号为 $1$ 到 $n$。柱子形成了 $6$ 行 $6$ 列的矩阵，从上到下每行依次被编号为 $1$ 到 $6$，从左到右每列依次被编号为1到 $6$。



 ![](https://cdn.luogu.com.cn/upload/pic/4686.png) 

游戏一开始，$n$ 个盘子都被堆叠在左上角坐标为 $(1,1)$ 的柱子上。对于每一次操作，玩家可以选择一个柱子，取出最顶上若干个盘子，然后选择右边或者下面的某个柱子，将取出的盘子全部堆叠在其顶上（不会翻转顺序）。游戏的目标是把所有盘子都移动到 $(6,6)$ ，且自底向上大小依次递减。


给定游戏的初始局面，请找到任意一组玩通关的方法。数据保证解必定存在。

## 样例 #1

### 输入

```
6
1 6 5 4 3 2```

### 输出

```
1 1 D 6
2 1 D 6
3 1 D 6
4 1 D 6
5 1 D 6
6 1 R 6
6 2 R 6
6 3 R 6
6 4 R 6
6 5 R 5
6 5 R 1```

# 题解

## 作者：封禁用户 (赞：4)

##$x y R/D w$表示从$(x,y)$顶部取w个棋子想右/下移动
一到机房就被$Manchery$安利了这题…… 
考虑$n$路归并，可以从$(1..x,1..y)$的格子归并到$(x,y)$


------------
##$(1,1)$因为没有移动，所以只能保证顶部第一个棋子是有序的，$(2,1)(1,2)$可以通过比较$(1,1)$的顶部两个棋子来做到两个棋子的升序，$(2,2)$可以归并$(1,1)(2,1)(1,2)$做到5个有序……其他的格子可以从它之前的格子中n路归并得到序列。递归处理就可以了。 
大概$(6,6)$刚好可以做到$40000$ 
要做到从底向上升序的话，之前的格子得从底向上降序，反之亦然

粗略算了下复杂度……大概$O(66+36nlog36)$？？ 反正跑得过……
```c
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#define X first
#define Y second

using namespace std;

typedef pair<int,int> pari;
typedef pair<int,pari> par;

int n;
int C[10][10];
stack<int> A[10][10],B[10][10];
priority_queue<par,vector<par>,less<par> > Q1;
priority_queue<par,vector<par>,greater<par> > Q2;

inline void move(int i,int j,int x,int y){
    for(;i<x;i++) printf("%d %d D 1\n",i,j);
    for(;j<y;j++) printf("%d %d R 1\n",i,j);
}

inline void Sort1(int x,int y){
    for(int i=1;i<=x;i++)
        for(int j=1;j<=y;j++)
            if((i!=x||j!=y)&&!A[i][j].empty()) Q1.push(par(A[i][j].top(),pari(i,j)));
    while(!Q1.empty()){
        A[x][y].push(Q1.top().X);
        int i=Q1.top().Y.X,j=Q1.top().Y.Y; Q1.pop();
        move(i,j,x,y); A[i][j].pop();
        if(!A[i][j].empty()) Q1.push(par(A[i][j].top(),pari(i,j)));
    }
}

inline void Sort2(int x,int y){
    for(int i=1;i<=x;i++)
        for(int j=1;j<=y;j++)
            if((i!=x||j!=y)&&!A[i][j].empty()) Q2.push(par(A[i][j].top(),pari(i,j)));
    while(!Q2.empty()){
        A[x][y].push(Q2.top().X);
        int i=Q2.top().Y.X,j=Q2.top().Y.Y; Q2.pop();
        move(i,j,x,y); A[i][j].pop();
        if(!A[i][j].empty()) Q2.push(par(A[i][j].top(),pari(i,j)));
    }
}

void solve(int x,int y,int wh){
    if(x==1&&y==1){
        if(!B[x][y].empty()) A[x][y].push(B[x][y].top()),B[x][y].pop();
        return ;
    }
    if((x==1&&y==2)||(x==2&&y==1)){
        if(B[1][1].empty()) return ;
        int i=B[1][1].top(); B[1][1].pop();
        if(B[1][1].empty()){ A[x][y].push(i); move(1,1,x,y); return ; }
        int j=B[1][1].top(); B[1][1].pop();
        if((i>j)^wh) printf("%d %d %c 2\n",1,1,x==1?'R':'D');
        else printf("%d %d %c 1\n%d %d %c 1\n",1,1,x==1?'R':'D',1,1,x==1?'R':'D');
        if(wh) A[x][y].push(max(i,j)),A[x][y].push(min(i,j));
        else A[x][y].push(min(i,j)),A[x][y].push(max(i,j));
        return ;
    }
    for(int i=x;i;i--)
        for(int j=y;j;j--)
            if(i!=x||j!=y) solve(i,j,wh^1);
    if(wh) Sort1(x,y);
    else Sort2(x,y);
}

int main(){
    //freopen("disks.in","r",stdin);
    //freopen("disks.out","w",stdout);
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++){
        scanf("%d",&x); B[1][1].push(x);
    }
    solve(6,6,1);
}
```

---

## 作者：Phartial (赞：1)

# P3681 [CERC2016] 舞动的盘子 Dancing Disks 题解

如果除 $(6,6)$ 外的其他格子上的盘子自底向上递增，那么我们就可以使用类似选择排序的方式（先找到 $n$，将其移到 $(6,6)$，然后找到 $n-1$，将其移到 $(6,6)$，以此类推）将其全部移到 $(6,6)$，并使 $(6,6)$ 上的盘子自底向上递减。

进一步的，如果所有满足 $i\le x,j\le y,(i,j)\ne(x,y)$ 的格子 $(i,j)$ 的顶部有 $c_{i,j}$ 个盘子自底向上递增/递减，那么我们可以使用类似选择排序的方式（先将最大/小值移至 $(x,y)$，然后是次大/小值，依次类推）将这些盘子移到 $(x,y)$ 上，同时使得这些盘子自底向上递减/递增。

设 $f_{x,y}$ 为格子 $(x,y)$ 中最多能排序的盘子个数，显然 $f_{1,1}=1$，同时有转移方程：

$$
f_{x,y}=\sum_{i\le x,j\le y,(i,j)\ne(x,y)} f_{i,j}
$$

此时 $f_{6,6}=26928$，但 $n\le 40000$，考虑优化。

发现在此转移方程中 $f_{1,2}=f_{2,1}=1$，但我们实际上可以将其优化到 $2$：考察 $(1,1)$ 顶端的两个盘子，如果它的顺序就是我们想要的顺序的话就直接一起移到 $(1,2)$ 或 $(2,1)$，否则分成两步移到 $(1,2)$ 或 $(2,1)$。

那么我们就将 $f_{1,2}$ 和 $f_{2,1}$ 优化到了 $2$，此时 $f_{6,6}=42960$，可以通过此题。

```cpp
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

const int kV = 4e4 + 1, kN = 7;

struct Q {
  int v, x, y;
  bool operator<(const Q &o) const { return v < o.v; }
};
int n;
vector<int> a[kN][kN];

void M(int i, int j, int x, int y, int c = 1) {
  for (; i < x; ++i) {
    cout << i << ' ' << j << " D " << c << '\n';
  }
  for (; j < y; ++j) {
    cout << i << ' ' << j << " R " << c << '\n';
  }
}
int S(int x, int y, bool d) {  // d=0 自底向上递增，d=1 自底向上递减
  if (x == 1 && y == 1) {
    return !a[1][1].empty();
  }
  if (x + y == 3) {
    if (a[1][1].empty()) {
      return 0;
    }
    if (a[1][1].size() == 1) {
      M(1, 1, x, y);
      a[x][y].push_back(a[1][1].back()), a[1][1].pop_back();
      return 1;
    }
    int v1 = a[1][1].back();
    a[1][1].pop_back();
    int v2 = a[1][1].back();
    a[1][1].pop_back();
    if (d ^ (v2 < v1)) {
      M(1, 1, x, y, 2);
      a[x][y].push_back(v2), a[x][y].push_back(v1);
    } else {
      M(1, 1, x, y), M(1, 1, x, y);
      a[x][y].push_back(v1), a[x][y].push_back(v2);
    }
    return 2;
  }
  int s = 0;
  priority_queue<Q> q;
  for (int i = x; i >= 1; --i) {
    for (int j = y; j >= 1; --j) {
      if (i != x || j != y) {
        int c = S(i, j, !d);
        s += c;
        for (; c--; a[i][j].pop_back()) {
          q.push({(d ? 1 : -1) * a[i][j].back(), i, j});
        }
      }
    }
  }
  for (; !q.empty(); q.pop()) {
    Q v = q.top();
    M(v.x, v.y, x, y);
    a[x][y].push_back(abs(v.v));
  }
  return s;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  a[1][1].resize(n);
  for (int &i : a[1][1]) {
    cin >> i;
  }
  S(6, 6, 1);
  return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# P3681 题解

[Problem Link](https://www.luogu.com.cn/problem/P3681)

**题目大意**

> 给 $6\times 6$ 的一个网格，初始 $1\sim n$ 共 $n$ 个盘子乱序排列在 $(1,1)$ 上，每次操作你可以选定一个 $(i,j)$ 格子，把格子最顶端的任意个盘子移动到 $(i+1,j)/(i,j+1)$ 上。
>
> 请把 $1\sim n$ 移动到 $(6,6)$ 使得从下到上盘子标号递减。
>
> 数据范围：$n\le 4\times 10^4$。

**思路分析**

考虑 $f_{i,j}$ 表示 $i\times j$ 网格的最多能排序几个盘子，考虑归并，先盘子移动到其他所有格子 $(x,y)$，将 $f_{x,y}$ 个盘子升序排列，然后从其他所格子中归并，每次取最大值移动到 $(x,y)$ 上即可。

此时 $f(i,j)=\sum_{x=1}^i\sum_{y=1}^j[(x,y)\ne(i,j)]f_{x,y}$，但此时 $f_{6,6}\approx 2\times 10^4$。

注意到对于 $f_{1,2}/f_{2,1}$，我们可以通过整体移动 / 分开移动排序，因此 $f_{1,2}=f_{2,1}=2$，这样就能得到 $f_{6,6}\ge 4\times 10^4$。

输出方案就按归并的过程模拟即可。

总操作次数不超过 $10n$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> a[7][7];
int dp[7][7];
inline void R(int x,int y,int c) {
	printf("%d %d R %d\n",x,y,c);
	a[x][y+1].insert(a[x][y+1].end(),a[x][y].end()-c,a[x][y].end());
	a[x][y].erase(a[x][y].end()-c,a[x][y].end());
}
inline void D(int x,int y,int c) {
	printf("%d %d D %d\n",x,y,c);
	a[x+1][y].insert(a[x+1][y].end(),a[x][y].end()-c,a[x][y].end());
	a[x][y].erase(a[x][y].end()-c,a[x][y].end());
}
inline void opr(int sx,int sy,int tx,int ty,int c=1) {
	while(sx<tx) D(sx++,sy,c); while(sy<ty) R(sx,sy++,c);
}
inline void solve(int x,int y,int n,bool op) { //0:less, 1:greater
	auto cmp=[&](int x,int y) { return op?x<y:x>y; };
	if(n==1) return opr(1,1,x,y);
	if(n==2) {
		if(cmp(*prev(a[1][1].end(),2),*prev(a[1][1].end(),1))) opr(1,1,x,y),opr(1,1,x,y);
		else opr(1,1,x,y,2);
		return ;
	}
	auto chk=[&](auto i,auto j) { return cmp(a[i[0]][i[1]].back(),a[j[0]][j[1]].back()); };
	priority_queue <array<int,3>,vector<array<int,3>>,decltype(chk)> Q(chk); 
	int N=n;
	for(int i=1;i<=x;++i) {
		for(int j=1;j<=y;++j) if((i<x||j<y)&&(i>1||j>1)) {
			solve(i,j,min(dp[i][j],n),op^1);
			Q.push({i,j,min(dp[i][j],n)});
			if((n-=dp[i][j])<=0) goto Mg;
		}
	}
	Q.push({1,1,1});
	Mg:
	while(!Q.empty()) {
		auto u=Q.top(); Q.pop();
		opr(u[0],u[1],x,y);
		if(--u[2]) Q.push(u);
	}
}
signed main() {
	dp[1][1]=1,dp[1][2]=2,dp[2][1]=2;
	for(int i=1;i<=6;++i) for(int j=1;j<=6;++j) if(i+j>3) {
		for(int x=1;x<=i;++x) for(int y=1;y<=j;++y) if(x<i||y<j) dp[i][j]+=dp[x][y];
	}
	int n;
	scanf("%d",&n);
	a[1][1].resize(n);
	for(int &i:a[1][1]) scanf("%d",&i);
	solve(6,6,n,1);
	return 0;
}
```

---

## 作者：EXODUS (赞：0)

# Part 1：前言

非常好题目，爱来自中国。





# Part 2：正文

首先考虑我们怎么样才能把一些盘子在某个柱子上排序。不妨设当前我们要把一些盘子在第 $(i,j)$ 个位置顺序排序，一个简单的想法是，我们让这些盘子在 $\{(x,y)\mid 1\leq x\leq i\land 1\leq y\leq j\land(x,y)\neq(i,j)\}$ 上倒序排序，然后每次在这些格子中找到编号最大的盘子，将其移到 $(i,j)$，反复直到所有盘子都被移到 $(i,j)$ 上为止。不难发现将这些盘子在 $(x,y)$ 上倒序排序是一个子问题，因此我们可以考虑设 $f(i,j,0/1)$ 表示在 $(i,j)$ 上最多能将多少盘子正序或倒序排序。显然有边界 $f(1,1,0)=f(1,1,1)=1$，转移为 $f(i,j,k)=\sum\limits_{x=1}^i\sum\limits_{y=1}^j[x\neq i\lor y\neq j]f(x,y,k\oplus 1)$。

经过计算，$f(6,6,0)=26928$。但是这样还不够，考虑进行一些优化。注意到我们实际上能将 $(1,2)$ 这个格子对两个盘子排序。具体而言，假设我们要正序排两个，考虑在 $(1,1)$ 的最上面两个盘子，如果当前第一个大于第二个，我们就一个一个移，否则一次移两个，倒序也可以类似出来。这样 $f(1,2,*)=f(2,1,*)=2$，此时 $f(6,6,0)=42960$，可以通过本题。

代码实现上，我们并不需要处理出来 $f$ 数组。我们可以视为在 $(1,1)$ 中可以冒出一些卡片，在特殊处理 $(1,1),(1,2),(2,1)$ 的前提下，在处理一个格子 $(i,j)$ 的时候，我们只需要以相反状态递归填满其左上角的格子，然后模拟移到其上即可。


# Part 3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
const int N=7;
int n,cnt;
vector<int>stk;
vector<int>card[N][N];
vector<tuple<int,int,int,int>>ans;
void arrive(int x,int y,int tx,int ty){while(x<tx)ans.eb(x,y,0,1),x++;while(y<ty)ans.eb(x,y,1,1),y++;}
void solve(int x,int y,int tp){
	if(x<=0||y<=0)return;
	// printf("%d %d %d\n",x,y,tp);
	// Sleep(100);
	if(x==1&&y==1){if(!stk.empty())card[1][1].eb(stk.back()),stk.pop_back();return;}
	if(x==1&&y==2){
		if(stk.empty())return;
		else if((int)stk.size()==1)ans.eb(1,1,1,1),card[x][y].eb(stk.back()),stk.pop_back();
		else{
			if(tp==0){
				int u=stk.back();stk.pop_back();
				int v=stk.back();stk.pop_back();
				if(u<v)ans.eb(1,1,1,2);
				else ans.eb(1,1,1,1),ans.eb(1,1,1,1);
				card[x][y].eb(max(u,v)),card[x][y].eb(min(u,v));
			}else{
				int u=stk.back();stk.pop_back();
				int v=stk.back();stk.pop_back();
				if(u<v)ans.eb(1,1,1,1),ans.eb(1,1,1,1);
				else ans.eb(1,1,1,2);
				card[x][y].eb(min(u,v)),card[x][y].eb(max(u,v));
			}
		}
		return;
	}
	if(x==2&&y==1){
		if(stk.empty())return;
		else if((int)stk.size()==1)ans.eb(1,1,0,1),card[x][y].eb(stk.back()),stk.pop_back();
		else{
			if(tp==0){
				int u=stk.back();stk.pop_back();
				int v=stk.back();stk.pop_back();
				if(u<v)ans.eb(1,1,0,2);
				else ans.eb(1,1,0,1),ans.eb(1,1,0,1);
				card[x][y].eb(max(u,v)),card[x][y].eb(min(u,v));
			}else{
				int u=stk.back();stk.pop_back();
				int v=stk.back();stk.pop_back();
				if(u<v)ans.eb(1,1,0,1),ans.eb(1,1,0,1);
				else ans.eb(1,1,0,2);
				card[x][y].eb(min(u,v)),card[x][y].eb(max(u,v));
			}
		}
		return;
	}
	for(int i=x;i>=1;i--)for(int j=y;j>=1;j--)if(i!=x||j!=y)solve(i,j,tp^1);
	if(tp==0){
		while(1){
			int px=0,py=0,val=0;
			for(int i=1;i<=x;i++)for(int j=1;j<=y;j++)if(i!=x||j!=y)
				if(!card[i][j].empty()&&(px==0||py==0||card[i][j].back()>val))
					val=card[i][j].back(),px=i,py=j;
			if(!px)break;
			card[px][py].pop_back(),card[x][y].eb(val),arrive(px,py,x,y);
		}
	}else{
		while(1){
			int px=0,py=0,val=0;
			for(int i=1;i<=x;i++)for(int j=1;j<=y;j++)if(i!=x||j!=y)
				if(!card[i][j].empty()&&(px==0||py==0||card[i][j].back()<val))
					val=card[i][j].back(),px=i,py=j;
			if(!px)break;
			card[px][py].pop_back(),card[x][y].eb(val),arrive(px,py,x,y);
		}
	}
	// Debug("%d %d %d\n",x,y,(int)card[x][y].size());
}
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)scanf("%d",&x),stk.eb(x);
	const int X=6,Y=6;
	solve(X,Y,0);
	assert((int)card[X][Y].size()==n);
	for(auto [x,y,d,l]:ans)printf("%d %d %c %d\n",x,y,d==0?'D':'R',l);
	// for(auto x:card[6][6])printf("%d ",x);printf("\n");
	return 0;
}
```



---

