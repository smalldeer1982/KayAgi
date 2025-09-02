# Rooks Defenders

## 题目描述

You have a square chessboard of size $ n \times n $ . Rows are numbered from top to bottom with numbers from $ 1 $ to $ n $ , and columns — from left to right with numbers from $ 1 $ to $ n $ . So, each cell is denoted with pair of integers $ (x, y) $ ( $ 1 \le x, y \le n $ ), where $ x $ is a row number and $ y $ is a column number.

You have to perform $ q $ queries of three types:

- Put a new rook in cell $ (x, y) $ .
- Remove a rook from cell $ (x, y) $ . It's guaranteed that the rook was put in this cell before.
- Check if each cell of subrectangle $ (x_1, y_1) - (x_2, y_2) $ of the board is attacked by at least one rook.

Subrectangle is a set of cells $ (x, y) $ such that for each cell two conditions are satisfied: $ x_1 \le x \le x_2 $ and $ y_1 \le y \le y_2 $ .

Recall that cell $ (a, b) $ is attacked by a rook placed in cell $ (c, d) $ if either $ a = c $ or $ b = d $ . In particular, the cell containing a rook is attacked by this rook.

## 说明/提示

Consider example. After the first two queries the board will look like the following picture (the letter $ R $ denotes cells in which rooks are located, the subrectangle of the query of the third type is highlighted in green):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/ed156665629e711ee2ed4626477b94d3794c1b66.png)Chessboard after performing the third and the fourth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/287c91194903b3f438014966a1c3ab50aa3053b1.png)Chessboard after performing the fifth and the sixth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/2450d8ada954d98a57be494097290cacc9d47393.png)Chessboard after performing the seventh and the eighth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/860ee139e8d85a9e953e6218af254f9a2b04a395.png)Chessboard after performing the last two queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/fa48f4457088559fa8b50c796cacdd0ae0609075.png)

## 样例 #1

### 输入

```
8 10
1 2 4
3 6 2 7 2
1 3 2
3 6 2 7 2
1 4 3
3 2 6 4 8
2 4 3
3 2 6 4 8
1 4 8
3 2 6 4 8```

### 输出

```
No
Yes
Yes
No
Yes```

# 题解

## 作者：panyanppyy (赞：4)

## Problem
给出一个 $n\times m,1\le n,m\le 10^5$ 的棋盘，有 $q\le 2\times 10^5$ 次操作，操作分为三种：

1. 读入 ```1 x y``` 表示在点 $(x,y)$ 放置一枚車。

2. 读入 ```2 x y``` 表示移除 $(x,y)$ 的車，保证原先有車存在。

3. 读入 ```3 x y X Y``` 询问 $(x\sim X,y\sim Y)$ 中有多少个可以被車攻击到的点。
## Solution

看到修改和询问操作以及 $10^5$ 的数据范围，马上能想到数据结构。

考虑区间修改和查询直接用树状数组或者线段树维护即可。

* 方案 1：

	对行和列分别开一颗树状数组。
    
	添加操作可以对没有标记过的点加入树状数组中，标记 $+1$。

   删除操作时如果当前行/列只剩这个了，就从树状数组中删除，标记 $-1$。

	如果 $x\sim X$ 一共有 $X-x+1$ 个点就说明这个矩形的行都可以被攻击到，列同理。

* 方案 2：
	对行和列分别开一颗线段树。

   修改直接单点加即可。

   维护区间的最小值，如果区间值为零就有不能被攻击到的点。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) x.begin(),x.end()
using namespace std;
const int N=1e5+1;
int n,m,fx[N],fy[N];
inline int low(int x){return-x&x;}
struct qjc{
	int t[N];
	inline void update(int x,int k){for(;x<=n;x+=low(x))t[x]+=k;}
	inline int query(int x){int res=0;for(;x;x-=low(x))res+=t[x];return res;}
	inline Q(int x,int y){return query(y)-query(x-1);}
}_x,_y;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,op,x,y,X,Y;i<=m;i++){
		scanf("%d%d%d",&op,&x,&y);
		switch(op){
			case 1:
				fx[x]++,fy[y]++;
				if(fx[x]==1)_x.update(x,1);
				if(fy[y]==1)_y.update(y,1);
				break;
			case 2:
				fx[x]--,fy[y]--;
				if(!fx[x])_x.update(x,-1);
				if(!fy[y])_y.update(y,-1);
				break;
			case 3:
				scanf("%d%d",&X,&Y);
				if(_x.Q(x,X)==X-x+1||_y.Q(y,Y)==Y-y+1)puts("YES");
				else puts("NO");
				break;
		}
	}
	return 0;
}
```

---

## 作者：Anguei (赞：1)

## 题意

有一个大小为 $n\times n$ 的棋盘，有三种操作：

- 在第 $x$ 行第 $y$ 列的位置，放置一个 Rook 棋子
- 移除在第 $x$ 行第 $y$ 列的位置已有的 Rook 棋子
- 判断在 $(x1, y1)$ 到 $(x2, y2)$ 范围内所有的位置，是否全部可以被 Rook 棋子攻击？

注：Rook 棋子的攻击范围是，同一行 / 同一列的全部格子。

$n \leq 2 \times 10^5$。

## 分析

考虑什么时候，一个子矩阵内所有位置都被攻击？

如图，子矩阵（绿色区域）的第一行、第二行被攻击，是因为左侧有两个 Rook 棋子。而第三行被攻击，是因为右下角还有一个棋子。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/fa48f4457088559fa8b50c796cacdd0ae0609075.png)

如果移除左边两颗棋子，则第一行和第二行无法被**完整攻击**（前两行的第三列仍可被右下角棋子攻击）。

如果移除右下角的棋子，则第三行无法被攻击。

设子矩阵有 $r$ 行 $c$ 列，若前 $r-1$ 行上都已有棋子，此时最后一行还未被攻击。要么把最后一行也放上棋子，要么再放至多 $c$ 个棋子，把最后一行的每一列都攻击掉…

由此可见，若想让一个子矩阵范围内所有位置都可以被攻击，即**完整攻击**，当且仅当子矩阵的**每一行或每一列**都能被攻击。

于是可以使用两个树状数组维护。一个维护每一行是否被攻击，一个维护每一列是否被攻击。

```cpp
struct Fenwick {
  int n;
  std::vector<int> v;
  Fenwick(int n) : n(n), v(n + 1) {}
  int lowbit(int x) { return x & -x; }
  void add(int x, int y) {
    for (; x <= n; x += lowbit(x)) v[x] += y;
  }
  int sum(int x) {
    int res = 0;
    for (; x; x -= lowbit(x)) res += v[x];
    return res;
  }
  int rangeSum(int l, int r) { return sum(r) - sum(l - 1); }
};

void solution() {
  int n, q;
  read(n, q);
  std::vector<int> row(n + 1, 0), col(n + 1, 0);
  Fenwick bitRow(n), bitCol(n);
  while (q--) {
    int opt;
    read(opt);
    if (opt == 1) {
      int x, y;
      read(x, y);
      // a[x][y] = true;
      ++row[x];
      ++col[y];
      if (row[x] == 1) bitRow.add(x, 1);
      if (col[y] == 1) bitCol.add(y, 1);
    } else if (opt == 2) {
      int x, y;
      read(x, y);
      // a[x][y] = false;
      --row[x];
      --col[y];
      if (row[x] == 0) bitRow.add(x, -1);
      if (col[y] == 0) bitCol.add(y, -1);
    } else {
      int x1, y1, x2, y2;
      read(x1, y1, x2, y2);
      int rowLen = x2 - x1 + 1, colLen = y2 - y1 + 1;
      bool ok = false;
      if (bitRow.rangeSum(x1, x2) == rowLen) ok = true;
      if (bitCol.rangeSum(y1, y2) == colLen) ok = true;
      std::cout << (ok ? "YES" : "NO") << "\n";
    }
  }
}
```

---

## 作者：Rnfmabj (赞：1)

树状数组裸题。

~~在 CF 这种拼手速的场合谁会打线段树啦~~


------------
## 题意

给定一个 $n × n$ 的正方形棋盘，支持如下操作：

1. 在 $(x,y)$ 格放入一个棋子“车”。

2. 移除 $(x,y)$ 格的“车”。

3. 给定一个子矩形，其左上角格为 $(x_1,y_1)$，右下角格为 $(x_2,y_2)$，查询该子矩形是否被棋盘上所有“车”的攻击范围覆盖。

保证操作合法。


------------


## 思路

单点修改 + 区间查询 + CF 特有的手速要求（码量要小）= 树状数组。

维护两个树状数组，分别对应行和列。

查询时只需要查询子矩形对应的行区间和列区间有多少行 / 列被覆盖即可。

只要行和列中至少有一个区间被完全覆盖，那么就是满足要求的，反之一定不满足。

插入的时候不能想当然，要判断当前行 / 列是否已经有棋子，如果有的话就不能插入。因为一行 / 列上的多个棋子只能覆盖一行 / 列。

删除同理，要判断移除当前棋子后本行 / 列是否无棋子，如果当前棋子是本行 / 列的最后一个，那么就需要删除，反之不需要。

这个判断只要额外开两个数组就可以了。

时间复杂度 $O(nlogn)$ ，空间复杂度 $O(n)$ 。


------------


## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define R read()
#define file(a) freopen(#a".in","r",stdin),freopen(#a".out","w",stdout)
using namespace std;
inline ll read() {
	ll s=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')f*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*f;
}
inline void write(ll x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10),x%=10;
	putchar('0'+x);
}//Don't use it for CF.
inline void wk(ll x){write(x);putchar(' ');}
inline void we(ll x){write(x);putchar('\n');}
const ll maxn=1e5+5;
ll t1[maxn],t2[maxn];
ll n,m;
ll lb(ll x){
	return x&-x;
}//lowbit
void add_1(ll p,ll x){
	while(p<=n){
		t1[p]+=x;
		p+=lb(p); 
	}
}
void add_2(ll p,ll x){
	while(p<=n){
		t2[p]+=x;
		p+=lb(p); 
	}
}//两个插入/删除函数
ll sum_1(ll x){
	ll res=0;
	while(x>0){
		res+=t1[x];
		x-=lb(x);
	}
	return res;
}
ll sum_2(ll x){
	ll res=0;
	while(x>0){
		res+=t2[x];
		x-=lb(x);
	}
	return res;
}//两个查询
ll cnt_1[maxn],cnt_2[maxn];//两个记录数组，用来记录当前行/列棋子数
signed main(){
	n=R,m=R;
	for(ll i=1;i<=m;i++){
		ll opt=R;
		if(opt==1){
			ll x=R,y=R;
			if(!cnt_1[x])add_1(x,1);
			if(!cnt_2[y])add_2(y,1);//坑点：只有当本行/列之前不存在棋子时才需要插入
			cnt_1[x]++,cnt_2[y]++;
		}
		if(opt==2){
			ll x=R,y=R;
			if(cnt_1[x]==1)add_1(x,-1);
			if(cnt_2[y]==1)add_2(y,-1);//同上
			cnt_1[x]--,cnt_2[y]--;
		}
		if(opt==3){
			ll ans=0,flag=0,fl=0;
			ll x=R,y=R,l=R,r=R;
			ans=sum_1(l)-sum_1(x-1);//查询行
			if(ans<l-x+1)flag=1;
			ans=sum_2(r)-sum_2(y-1);//查询列
			if(ans<r-y+1)fl=1;
			if(flag==1&&fl==1)cout<<"NO"<<endl;//只有行列都没能完全覆盖时才不满足要求
			else cout<<"YES"<<endl;//反之满足要求
		}
	}
	return 0;
}
```


---

## 作者：小木虫 (赞：1)

### Preface  
一道和 B 题一样板的带点结论的线段树题。  
### Problem  
给你一个 $n×n$ 棋盘，三种操作：  
1.在棋盘上 $(x,y)$ 处放一个车。  
2.移除 $(x,y)$ 的车。  
3.给你一个子矩阵，问你其中所有节点是否可以都被车走到。（车可以走若干步，但不可以拐弯）  
### Solution  
一个很显然的结论，一个子矩阵所有的点能被车走到，当且仅当其左右的车能覆盖其或上下的车能覆盖。  
维护俩线段树，分别代表竖轴和横轴的车覆盖情况，做完了。  
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,t,x,y;
const int N=2e5+10;
int lu,ld,ru,rd;
struct TREE{
	int tree[N<<4];int tot[N<<4];
	void pushup(int rt){
		tree[rt]=tree[rt*2]+tree[rt*2+1];
	}	
	void update(int rt,int left,int right,int x,int y){
		if(left==right){
			tot[rt]+=y;
			if(tot[rt]==1&&y==1)tree[rt]+=1;
			if(tot[rt]==0&&y==-1)tree[rt]-=1;
			return;
		}
		int mid=(left+right)/2;
		if(x<=mid)update(rt*2,left,mid,x,y);
		else update(rt*2+1,mid+1,right,x,y);
		pushup(rt);
	}
	int query(int rt,int left,int right,int L,int R){
		if(left>=L&&right<=R){
			return tree[rt];
		}
		int mid=(left+right)/2;
		int res=0;
		if(L<=mid)res+=query(rt*2,left,mid,L,R);
		if(R>=mid+1)res+=query(rt*2+1,mid+1,right,L,R);
		return res;
	}
}T[2];
void init(){
	
}
void solve(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=q;i++){
		cin>>t;
		if(t==1){
			cin>>x>>y;
			T[0].update(1,1,n,x,1);
			T[1].update(1,1,n,y,1);
		}
		if(t==2){
			cin>>x>>y;
			T[0].update(1,1,n,x,-1);
			T[1].update(1,1,n,y,-1);
		}
		if(t==3){
			cin>>lu>>ru>>ld>>rd;
			if((T[0].query(1,1,n,lu,ld)==(ld-lu+1))||(T[1].query(1,1,n,ru,rd)==(rd-ru+1))){
				cout<<"YES"<<endl;
			}else{
				cout<<"NO"<<endl;
			}
		}
	}
}
int main(){
	solve();
	return 0;
}
```


---

## 作者：a1co0av5ce5az1cz0ap_ (赞：1)

这个线段树硬是卡了我 1h……
## 一、题意
在一个 $n\times n$ 的棋盘上，每次有 $q$ 个操作：

1. 在 $(x,y)$ 位置放置一个车（jū）
2. 移除 $(x,y)$ 位置的车（保证那里还有）
3. 问从 $(x_1,y_1)$ 到 $(x_2,y_2)$ 这个区间内是不是每个点都可能被车攻击，如果都是就输出 `Yes`，否则输出 `No`。
## 二、思路
在国际象棋里面，车能攻击的范围是同一行同一列。

因此，第三个操作相当于问是不是第 $x_1\sim x_2$ 行都有车或者第 $y_1\sim y_2$ 列都有车。

我们可以分别拿两个线段树存 $x$ 和 $y$，不过问是不是都有车，所以我们就初始每个节点的默认值都是 $1$，$\text{pushup}$ 就是取 $\max$。

之后就很简单了。

对于第一种操作，就是两个线段树都在对应位置 $-1$。

对于第二种操作，两个线段树都在对应位置 $+1$。

对于第三种操作，只要有一个线段树查询的结果是 $0$ 就输出 `Yes`，否则输出 `No`。
## 三、代码
```cpp
#include<bits/stdc++.h>
using namespace std;
//线段树
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mid ((a[p].l+a[p].r)>>1)
struct node{
	int l,r,t;
};
struct segmentTree{
	node a[400005];
	inline void pushup(int p){
		a[p].t=max(a[ls(p)].t,a[rs(p)].t);
	}
	void build(int l,int r,int p){
		a[p].l=l,a[p].r=r;
		if(l==r){
			a[p].t=1;//初始为1
			return;
		}
		build(l,mid,ls(p));
		build(mid+1,r,rs(p));
		pushup(p);
	}
	void add(int v,int p,int u){//在v的位置增加u，根为p
		if(a[p].l==a[p].r){
			a[p].t+=u;
			return;
		}
		if(v<=mid) add(v,ls(p),u);
		if(v>mid) add(v,rs(p),u);
		pushup(p);
	}
	int query(int l,int r,int p){//查询l到r，根为p
		if(l<=a[p].l&&a[p].r<=r) return a[p].t;
		if(a[p].l>r||a[p].r<l) return 0;
		return max(query(l,r,ls(p)),query(l,r,rs(p)));//记得取max
	}
}tx,ty;
int main(){
	ios::sync_with_stdio(0);//这两行一定要加，不然会tle
	cin.tie(0);cout.tie(0);
	int n,m;
	cin>>n>>m;
	tx.build(1,n,1);ty.build(1,n,1);//都要build
	int op,x,y,x2,y2;
	for(int i=1;i<=m;i++){
		cin>>op>>x>>y;
		if(op==1){
			tx.add(x,1,-1);//分别-1
			ty.add(y,1,-1);
		}else if(op==2){
			tx.add(x,1,1);//分别+1
			ty.add(y,1,1);
		}else{
			cin>>x2>>y2;
			//只要一个是0，就是Yes
			if(!(tx.query(x,x2,1)&&ty.query(y,y2,1))) cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1679C](https://www.luogu.com.cn/problem/CF1679C)

* **【解题思路】**

本题等价于：

给定 $x_1,y_1,x_2,y_2$，问以下两个条件是否至少有一个被满足：

* 第 $x_1\sim x_2$ 行是否每行至少有一个棋子。

* 第 $y_1\sim y_2$ 列是否每列至少有一个棋子。

我们可以动态维护某行或某列有没有棋子，于是我们可以通过算前缀和的方式来判断上面两个条件是否被满足。

于是直接树状数组即可。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

array<int,100001> tree_row,tree_line,cnt_row,cnt_line;

int update(int idx,int val,int lim,array<int,100001>& tree_arr)
{
	while(idx<=lim)
        tree_arr[idx]+=val,idx+=idx&-idx;
}

int presum(int idx,array<int,100001>& tree_arr)
{
	int result=0;
    while(idx)
        result+=tree_arr[idx],idx-=idx&-idx;
    return result;
}

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt,cntquery;
	cin>>cnt>>cntquery;
	while(cntquery--)
	{
		int optype,x,y,a,b;
		cin>>optype;
		switch(optype)
		{
			case 1:
				cin>>x>>y;
				if(cnt_line[x]++==0)
					update(x,1,cnt,tree_line);
				if(cnt_row[y]++==0)
					update(y,1,cnt,tree_row);
				break;
			case 2:
				cin>>x>>y;
				if(--cnt_line[x]==0)
					update(x,-1,cnt,tree_line);
				if(--cnt_row[y]==0)
					update(y,-1,cnt,tree_row);
				break;
			case 3:
				cin>>x>>y>>a>>b;
				cout<<(presum(a,tree_line)-presum(x-1,tree_line)==a-x+1||presum(b,tree_row)-presum(y-1,tree_row)==b-y+1?"Yes":"No")<<'\n';
				break;
		}
	}
	return 0;
}
 
```

---

## 作者：3a51_ (赞：0)

首先需要发现一个性质，一个矩形 $(x1,y1,x2,y2)$ 要全部被攻击，需要满足至少有 $x2-x1+1$ 行被攻击或者 $y2-y1+1$ 列被攻击。

证明：

假设 $p_1=x2-x1+1$，$p_2=y2-y1+1$，假设只攻击到了 $p_1-1$ 行，那么还有一行 $p_2$ 个格子没被攻击到，这 $p_2$ 个格子都在不同的列，所以一定还需要 $p_2$ 次。

所以其实只用考虑一个区间的行、列是否全部被攻击即可，那么可以把原问题抽象成 $2$ 个线段，分别是行、列，不难发现需要在线段上执行的就是单点更新、区间查询，所以可以开两颗线段树维护。另外，因为没有区间更新，懒标记都省了，多方便！

关键部分代码：

```cpp
//单点更新
void secupd(int t,int L,int v,int l,int r,int k){//t是第几颗线段树，L是更新位置，v代表值（1表示放置车，0表示删除车），其他不用说。
	if(l==r){
		Q[t][k]=v;
	}
	else{
		int mid=(l+r)>>1;
		if(L<=mid) secupd(t,L,v,l,mid,k<<1);
		else secupd(t,L,v,mid+1,r,k<<1|1);
		Q[t][k]=Q[t][k<<1]+Q[t][k<<1|1];
	}
}

//区间查询
int Query(int t,int L,int R,int l,int r,int k){
	if(L<=l && r<=R) return Q[t][k];
	else{
		int sum=0;
		int mid=(l+r)>>1;
		if(L<=mid) sum+=Query(t,L,R,l,mid,k<<1);
		if(R>mid) sum+=Query(t,L,R,mid+1,r,k<<1|1);
		return sum;
	}
}

//主函数
signed main()
{
	ios::sync_with_stdio(false);//读入优化
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int op,x,y,x1,x2,y1,y2;
		cin>>op;
		if(op==1){
			cin>>x>>y;
			cnt1[x]++;
			if(cnt1[x]==1){//坑点，记住判断两次同行、同列
				secupd(0,x,1,1,n,1);
			}
			cnt2[y]++;
			if(cnt2[y]==1){//坑点，记住判断两次同行、同列
				secupd(1,y,1,1,n,1);
			}
		}
		if(op==2){
			cin>>x>>y;
			cnt1[x]--;
			if(cnt1[x]==0){//坑点，记住判断两次同行、同列
				secupd(0,x,0,1,n,1);
			}
			cnt2[y]--;
			if(cnt2[y]==0){//坑点，记住判断两次同行、同列
				secupd(1,y,0,1,n,1);
			}
		}
		if(op==3){
			cin>>x1>>y1>>x2>>y2;
			int p1=Query(0,x1,x2,1,n,1),p2=Query(1,y1,y2,1,n,1);
			if(p1==x2-x1+1 || p2==y2-y1+1){//如果满足全部行被攻击或全部列被攻击
				cout<<"Yes"<<endl;
			}else{
				cout<<"No"<<endl;
			}
		}
	}
	return 0;
}

//题外话：赛时结束前6s把这题过了（
```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1679C)

题意：给定一个 $n \times n$ 棋盘，有三种操作：1、在 $(x,y)$ 增加一个车（保证该点没有车）；2、删除在 $(x,y)$ 的车（保证该点有车）；3、给定一个矩形，查询这个矩形的每一个单元格是否都被至少一个车攻击。（车的攻击范围是该车所在的行与列的所有格子）

一个矩形所有格子都被攻击当且仅当该矩形的每一行都有车或每一列都有车。然后自然想到增加操作就相当于标记某一行和某一列能被攻击到，记为 $1$；删除则是将 $1$ 变为 $0$。然后查询相当于查询区间内是否都为 $1$，即查询区间和是否等于区间长度。

那这个就相当于单点修改和询问区间和，直接开两个树状数组维护行和列即可。

但是可能会出现不合法的情况，即某一行（列）被标记了两次或以上，从而区间和会得到错误结果。因此可以开两个数组，记录某一行（列）实际被攻击的次数，当实际次数为 $0$ 或 $1$ 时再对树状数组进行修改，否则直接在记录数组上修改即可。

时间复杂度 $O(q \log n)$。

---

## 作者：I_am_Accepted (赞：0)

### Analysis

* * * 

**结论：** 若一个子矩阵中的格子均可以被攻击到，则子矩阵中的格子均可以被横向攻击到，或者均可以被纵向攻击到。

**证明：** 反证法，假设有位置 $(x_1,y_1)$ 只能被横向攻击到，位置 $(x_2,y_2)$ 只能被纵向攻击到。

则 $y_1$ 这一列全部是没有被纵向攻击的，$x_2$ 这一行全部是没有被横向攻击的，所以 $(x_2,y_1)$（必然在子矩阵内）没有被任何攻击到。

矛盾，原命题成立。

* * *

所以，我们对于行（列同理）记录「这一行是（$1$）否（$0$）被横向攻击」。

接下来就等价于区间询问是否全为 $1$，这就是树状数组 / 线段树模板了。

### Code

本人用的树状数组。

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 100010
#define low (x&(-x))
int a[N],b[N],c[N],d[N],n;
void add(int x,int y){
	while(x<=n){
		c[x]+=y;
		x+=low;
	}
}
void Add(int x,int y){
	while(x<=n){
		d[x]+=y;
		x+=low;
	}
}
int que(int x){
	int res=0;
	while(x){
		res+=c[x];
		x-=low;
	}
	return res;
}
int Que(int x){
	int res=0;
	while(x){
		res+=d[x];
		x-=low;
	}
	return res;
}
signed main(){IOS;
int q;
	cin>>n>>q;
	int opt,x,y,xx,yy;
	while(q--){
		cin>>opt>>x>>y;
		if(opt==1){
			if(!a[x]) add(x,1);
			if(!b[y]) Add(y,1);
			a[x]++;
			b[y]++;
		}else if(opt==2){
			a[x]--;
			b[y]--;
			if(!a[x]) add(x,-1);
			if(!b[y]) Add(y,-1);
		}else{
			cin>>xx>>yy;
			if(que(xx)-que(x-1)==xx-x+1 || Que(yy)-Que(y-1)==yy-y+1) cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		}
	}
return 0;}
```

---

## 作者：Cocoly1990 (赞：0)

题意：给定一个棋盘，支持下车和拿走车，以及查询一个区间是否每个格子都至少被一个车攻击到。

容易想到分行和列维护，考虑转化题意，本质上要求维护一个序列，支持单点加一减一，查询区间是否全为正整数。

简单数据结构题。直接树状数组维护区间和必然是寄的，虽然我尝试过把区间查询的加和逻辑修改再维护，但并没有调出来，我们不妨修改就直接在原先的序列上修改，树状数组维护区间正整数的个数，如果每次在序列上修改使得 $a_i\leftarrow 1$，那么树状数组该位 $+1$，如果 $a_i\leftarrow 0$，那么该位 $-1$，其他情况不需要管。

核心代码：

```
		if(opt == 1){
			gi(x);gi(y);
			fff[x][0] += 1;
			fff[y][1] += 1;
			if(fff[x][0] == 1) add(x, 1, 0);
			if(fff[y][1] == 1) add(y, 1, 1);
		}
		else if(opt == 2){
			gi(x);gi(y);
			fff[x][0] -= 1;
			fff[y][1] -= 1;
			if(fff[x][0] == 0) add(x, -1, 0);
			if(fff[y][1] == 0) add(y, -1, 1);
		}
```

查询啥的直接原来怎么查现在就怎么查。

[Submission](https://codeforces.com/contest/1679/submission/157169048)

---

## 作者：Shunpower (赞：0)

## 题目大意

目前有一个棋盘，大小为 $n\times n$，你要处理以下三种操作或询问：
- `1 x y` 表示在 $(x,y)$ 处放置一个车，这辆车的势力范围将为整个 $x$ 行，整个 $y$ 列。
- `2 x y` 表示移除 $(x,y)$ 处的**一个**车，保证这个地方至少有一辆车。
- `3 x1 y1 x2 y2` 表示查询对于所有 $x1\leqslant x\leqslant x2$ 且 $y1\leqslant y\leqslant y2$ 的 $(x,y)$ 是否全部都能被车的势力范围覆盖。如果是，输出 `Yes`，否则输出 `No`。

共有 $q$ 次操作或询问。

数据范围：$1\leqslant n\leqslant 10^5,1\leqslant q\leqslant 2\cdot 10^5$。

## 思路

首先我们来试着转换询问，发现其实就是查一个矩形。而如果矩形要想全部被车的势力范围掉，那么只有两种可能：

- 这个矩形中任意一行都是车的势力范围
- 这个矩形中任意一列都是车的势力范围

显然不会出现两种相结合的情况。

考虑到车只有行和列，而这里的询问也之和行、列有关了，所以我们考虑维护行和列上的车。

一个最为纯粹的瞎想告诉我们可以试试二维线段树，但是我们其实可以给它换一下，我们考虑维护行一棵线段树，维护列再搞一棵。**似乎**我们需要实现两种操作：
- 布尔的单点加法，给这个行或列加车或者删车
- 区间查询，看看车的数量是否等于矩阵需要的行数或列数

但是这显然是错的，如果你这样写会 WA #3。

我们发现如果用布尔的单点加法，这个地方如果有一堆车的话每次移动只拿一个就实现不了了，那么我们换成正常单点加会怎样呢？

还是不行，这样做之后，你就不能靠车的个数来看是不是能把矩形覆盖完了，你得知道是不是每行或者每列都有车。那么我们可以考虑如果一行有车就是 $1$，没车就是 $0$，然后搞区间并。

于是我们需要实现两种操作：
- 单点加法
- 区间查并

注意，由于单点修改没法直接改并，所以你还是要维护单点值，如果单点值变为 $0$ 就去改并为 $0$，不是 $0$ 的时候就把并改为 $1$。不过你就不需要区间求和了。

千万不能拿单点值去并，必须像上面那样做，因为按位并可能把非零值并出 $0$ 来，比如 $1$ 和 $2$。

## 代码

我的代码写得很丑，赛时比较赶时间没有删区间求和的部分。代码在下面的提交记录中可见：

[赛时 AC](https://codeforces.com/contest/1679/submission/157193782)

若您要看区间并的部分，请自行忽略 $sum$ 相关变量。

---

## 作者：Hooch (赞：0)

### 题目大意

有一个 $n\times n$ 的棋盘，现在有 $q$ 个操作，每个操作如下：

+ 操作 $1$，在格子 $(x,y)$ 上放置一个车。
+ 操作 $2$，在格子 $(x,y)$ 上删除一个车。（一个格子上最多只有一个车，并且删除时保证该格子上有车）
+ 操作 $3$，查询矩阵 $(x1,y1)$ 到 $(x2,y2)$ 上是否每一个格子都会被车攻击。

**提示**：_车是指国际象棋中的车，在 $(x,y)$上的车可以攻击第 $x$ 行上的任意一格，也能攻击第 $y$ 列的任意一格，第 $(x,y)$ 同样也属该车的攻击范围。_

### 基本思路

我们可以看到数据范围 $n\le 10^5$ 就知道不可能真的构造出一个棋盘来做。

于是我们可以从车的攻击模式下手，一个车只攻击一行一列，并且一个矩阵也必须每一行都被攻击或者每一列都被攻击才回答 `Yes`。我们可以维护两个数列，分别维护行被攻击的情况和列被攻击的情况。

在一个序列中，我们要同时维护两个数值，一个是这一行 / 列上已没有车，另一个代表这一行 / 列的车数量，因为如果直接维护这一行有没有车，那么删除的时候你就不知道这一行 /  列的车有没有被删完，所以才维护两个值。

于是我们可以把问题转化为对两个序列进行单点修改和查询区间和，这可以用树状数组和线段树来做，而我用的线段树。

代码如下：

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (register int i(l); i <= r; ++i)
#define rep2(i, l, r) for (register int i(l); i >= r; --i)
using namespace std;
const int Buffer_Size = 1 << 10;
namespace {
    char buffer[Buffer_Size], *ihead = buffer + Buffer_Size, *itail = ihead;
    inline char Next_Char() {
        if (ihead == itail) fread(buffer, 1, Buffer_Size, stdin), ihead = buffer;
        return *ihead++;
    }
    template <typename T>
    inline void read(T &x) {
        x = 0; char ch = Next_Char(); T f = 1;
        while (!isdigit(ch)) f -= (ch == '-') << 1, ch = Next_Char();
        while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = Next_Char();
        x *= f;
    }
    template <typename T, typename ...L> inline void read(T &x, L &...y) {read(x), read(y...);}
    inline void readstr(string &s) {
        s = ""; char ch = Next_Char();
        while (ch == ' ' || ch == '\n') ch = Next_Char();
        while (ch ^ ' ' && ch ^ '\n') s += ch, ch = Next_Char();
    }
}
const int N = 1e5 + 5;
struct SegMentTree {
    struct node {int l, r, sum, shit;} t[N << 2];
    inline int lson(int x) {return x << 1;}
    inline int rson(int x) {return x << 1 | 1;}
    inline void pushup(int x) {t[x].sum = t[lson(x)].sum + t[rson(x)].sum; t[x].shit = t[lson(x)].shit + t[rson(x)].shit;}
    inline void buildtree(int x, int l, int r) {
        t[x].l = l; t[x].r = r;
        if (l == r) {
            t[x].sum = 0;
            t[x].shit = 0;
            return ;
        } int mid = l + r >> 1;
        buildtree(lson(x), l, mid);
        buildtree(rson(x), mid + 1, r);
        pushup(x);
    }
    inline void update(int x, int pos, int val) {
        if (t[x].l == t[x].r) {
            t[x].sum += val;
            if (t[x].sum >= 1) t[x].shit = 1;
            else t[x].shit = 0;
            return ;
        } int mid = t[x].l + t[x].r >> 1; 
        if (pos <= mid) update(lson(x), pos, val);
        else update(rson(x), pos, val);
        pushup(x);
    }
    inline int query(int x, int L, int R) {
        if (t[x].l >= L && t[x].r <= R) return t[x].shit;
        int mid = t[x].l + t[x].r >> 1, res = 0; 
        if (L <= mid) res += query(lson(x), L, R);
        if (R > mid) res += query(rson(x), L, R);
        return res;
    }
} t1, t2;
int n, q;
signed main(void) {
    read(n, q); t1.buildtree(1, 1, n);
    t2.buildtree(1, 1, n);
    while (q--) {
        int op, x, y, X, Y; read(op);
        if (op == 1) { read(x, y);
                      t1.update(1, x, 1);
                      t2.update(1, y, 1);
                     } else if (op == 2) { read(x, y);
                                          t1.update(1, x, -1);
                                          t2.update(1, y, -1);
                                         } else {
            read(x, y, X, Y);
            if (X - x + 1 == t1.query(1, x, X) || Y - y + 1 == t2.query(1, y, Y)) puts("YES");
            else puts("NO");
        }
    }
}
```



---

