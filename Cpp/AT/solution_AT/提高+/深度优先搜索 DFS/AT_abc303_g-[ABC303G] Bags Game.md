# [ABC303G] Bags Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc303/tasks/abc303_g

$ N $ 個の袋が左右一列に並んでいて、左から $ i $ 番目の袋には $ x_i $ 円が入っています。

十分多くのお金を持っている高橋君と青木君が、高橋君を先手として交互に次の操作をします。

- 以下の $ 3 $ 種類の操作のうち $ 1 $ つを選んで行う。
  - 右端または左端の袋を $ 1 $ 個選んで取る。
  - $ A $ 円をすぬけ君に支払う。そして、「右端または左端の袋を $ 1 $ 個選んで取る」という操作を $ \min(B,n) $ ($ n $ は残っている袋の個数) 回繰り返す。
  - $ C $ 円をすぬけ君に支払う。そして、「右端または左端の袋を $ 1 $ 個選んで取る」という操作を $ \min(D,n) $ ($ n $ は残っている袋の個数) 回繰り返す。

残っている袋が無くなった時点での高橋君の利得を「(高橋君が取った袋に入っている金額の総和) $ - $ (高橋君がすぬけ君に支払った金額の総和)」とし、これを $ X $ 円とします。また、青木君の利得についても同様に定め、$ Y $ 円とします。

高橋君が $ X-Y $ を最大化、青木君が $ X-Y $ を最小化することを目的に最適な操作をしたときの $ X-Y $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3000 $
- $ 1\ \leq\ x_i\ \leq\ 10^9 $
- $ 1\ \leq\ A,C\ \leq\ 10^9 $
- $ 1\ \leq\ B,D\ \leq\ N $
- 入力はすべて整数

### Sample Explanation 1

高橋君と青木君が最適な操作をしたとき、$ X=92,\ Y=2 $ となります。

## 样例 #1

### 输入

```
5 10 2 1000000000 1
1 100 1 1 1```

### 输出

```
90```

## 样例 #2

### 输入

```
10 45 3 55 4
5 10 15 20 25 30 35 40 45 50```

### 输出

```
85```

## 样例 #3

### 输入

```
15 796265 10 165794055 1
18804175 185937909 1934689 18341 68370722 1653 1 2514380 31381214 905 754483 11 5877098 232 31600```

### 输出

```
302361955```

# 题解

## 作者：rzh01014 (赞：3)

# [abc303_g](https://www.luogu.com.cn/problem/AT_abc303_g)
### 前言
一道单调队列优化的~~练习题~~好题。   
NOIP 前的最后一篇题解。
### 题目描述
Takahashi（先手）和 Aoki（后手）在玩游戏。他们有无限的钱，从左到右一共有 $N$ 个物品，第 $i$ 个价
值为 $x_i$。   
两个人轮流操作，每次轮到的一个人可以做 $3$ 种操作之一（假设还剩下 $n$ 个物品）。    
- 拿走最左边或者最右边的物品。   
- 付给 Snuke $A$ 块钱，然后重复以下操作 $\min(B,n)$ 次：拿走最左边或者最右边的物品。
- 付给 Snuke $C$ 块钱，然后重复以下操作 $\min(D,n)$ 次：拿走最左边或者最右边的物品。    

定义一个人的最大收益是拿到的所有东西的价值之和减去付给 Snuke 的钱数。    
请问如果 $2$ 个人都使用最优策略，使得自身的收益减去对方的收益尽量的大，那么最终 Takahashi 的收益减去 Aoki 的收益会是多少？
### 做法
先打一个暴力，定义 $f_{i,j}$ 为区间 $[i,j]$ 可以获得的最大收益（自己的收益减去对方的收益）。    
对于题目中的操作，我们可以分成 $4$ 种情况进行转移。   
- #### 操作一：
    我们选最左边的数，可以有以下的转移：
    $$
    \begin{aligned}
      f_{i,j}=x_i-f_{i+1,j}
    \end{aligned}
    $$
    当前区间为 $[i,j]$,拿完最左的剩下的区间为 $[i+1,j]$。   
    由于双方都是最优策略，故在拿完后对方的收益必是区间最大收益。在当前一步获得的收益为 $x_i$，下一步对方的收益为 $f_{i+1,j}$，因此选左的收益为 $x_i-f_{i+1,j}$。
- #### 操作二：
    我们选最右边的数，可以有以下的转移：
    $$
    \begin{aligned}
      f_{i,j}=x_j-f_{i,j-1}
    \end{aligned}
    $$
    同操作一。    
    当前区间为 $[i,j]$,拿完最右的剩下的区间为 $[i,j-1]$。   
    由于双方都是最优策略，故在拿完后对方的收益必是区间最大收益。在当前一步获得的收益为 $x_j$，下一步对方的收益为 $f_{i,j-1}$，因此选右的收益为 $x_j-f_{i,j-1}$。
- #### 操作三：
  花费 $A$ 的代价操作 $\min(B,n)$，每次拿走最左端的数或最右端的物品。不难发现每次操作完时取掉的都是最左端开始连续的一段与最右端开始连续的一段，那么中间会剩下连续的一段。   
  我们可以进行反向思考，枚举留下中间的一段是什么。此时可以使用一个前缀和，记 $sum_i=\sum\limits_{j=1}^{i}x_j$。枚举起始点为 $k$，令区间长度 $len=j-i+1$，应保留的区间长度 $lenn=j-i+1-\min(B,j-i+1)=\max(0,len-B)$，那么留下的区间为 $[k,\min(k+lenn-1,j)]$。    
  此时取出的收益为 $sum_j-sum_{i-1}-(sum_{\min(k+lenn-1,j)}-sum_k)$，即区间总收益减去留下的总收益，最后还要减去对手下一步的收益 $f_{k,\min(k+lenn-1,j)}$ 与代价 $A$，所以当前的收益为 $sum_j-sum_{i-1}-(sum_{\min(k+lenn-1,j)}-sum_k)-f_{k,\min(k+lenn-1,j)}-A$。  
  故可以给出如下的转移方程：
  $$
    lenn=j-i+1-\min(B,j-i+1)=\max(0,j-i+1-B)=\max(0,len-B)\\
    f_{i,j}=\max\{ sum_j-sum_{i-1}-(sum_{\min(k+lenn-1,j)}-sum_k)-f_{k,\min(k+lenn-1,j)}-A \}
  $$
- #### 操作四：
  如操作三,只是把代价 $A$ 改成 $C$，操作次数从 $B$ 改成 $D$。    
  可以给出相似的转移方程：
  $$
    lenn=j-i+1-\min(D,j-i+1)=\max(0,j-i+1-D)=\max(0,len-D)\\
    f_{i,j}=\max\{ sum_j-sum_{i-1}-(sum_{\min(k+lenn-1,j)}-sum_k)-f_{k,\min(k+lenn-1,j)}-C \}
  $$
在有了这四个转移方程之后，就能打出正确的 DP。    
这就有了一发正确的~~代码~~暴力：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e3+5;
int f[N][N],sum[N];
int n,a,b,c,d,x[N];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>a>>b>>c>>d;
	for(int i=1; i<=n; i++) cin>>x[i],sum[i]=sum[i-1]+x[i];
	for(int len=1; len<=n; len++) {
		for(int i=1; i+len-1<=n; i++) {
			int j=i+len-1;
			f[i][j]=max(x[j]-f[i][j-1],x[i]-f[i+1][j]);
			int lenn=max(0ll,(j-i+1)-b);
			if(lenn==0) f[i][j]=max(f[i][j],sum[j]-sum[i-1]-a);
			else for(int k=i; k+lenn-1<=j; k++)
					f[i][j]=max(f[i][j],sum[j]-sum[i-1]-(sum[k+lenn-1]-sum[k-1])-f[k][k+lenn-1]-a);
			lenn=max(0ll,(j-i+1)-d);
			if(lenn==0) f[i][j]=max(f[i][j],sum[j]-sum[i-1]-c);
			else for(int k=i; k+lenn-1<=j; k++)
					f[i][j]=max(f[i][j],sum[j]-sum[i-1]-(sum[k+lenn-1]-sum[k-1])-f[k][k+lenn-1]-c);
		}
	}
	cout<<f[1][n]<<"\n";
	return 0;
}
```
交上去会发现超时，再去看一眼数据范围，发现 $N$ 很大并不支持 $O(n^3)$ 的区间 DP。    
此时就要考虑优化，那么怎么优化呢？     
### 优化
我们继续观察 DP 的转移过程，发现在枚举 $k$ 的时候不同的 $i$、$j$ 所需枚举的一部分 $k$ 是相同的。    
换而言之，有一些对答案无影响的转移会被枚举、执行多次。     
每次枚举区间 $[i,j]$ 留下的长度是相同的，所以考虑 $O(n)$ 的复杂度遍历整个数组，在之后的查询中进行区间转移。    
有很多种操作可以进行优化。
- #### 单调队列：
  题目中的转移过程是寻找区间最值，可以将转移方程进一步转化：
  $$
    \begin{aligned}
    f_{i,j}=\max\{ sum_j-sum_{i-1}-(sum_{\min(k+lenn-1,j)}-sum_k)-f_{k,\min(k+lenn-1,j)}-A \}\\
    =sum_j-sum_{i-1}-A-\min\{ (sum_{\min(k+lenn-1,j)}-sum_k)-f_{k,\min(k+lenn-1,j)} \}\\
    f_{i,j}=\max\{ sum_j-sum_{i-1}-(sum_{\min(k+lenn-1,j)}-sum_k)-f_{k,\min(k+lenn-1,j)}-C \}\\
  =sum_j-sum_{i-1}-C-\min\{ (sum_{\min(k+lenn-1,j)}-sum_k)-f_{k,\min(k+lenn-1,j)} \}\\
    \end{aligned}
  $$
  转移 $f_{i,j}$ 的过程就变成了寻找能被包含在区间 $[i,j]$ 中，长度为 $lenn$ 的小区间带来代价的最小值。   
  我们会发现这个过程很像[滑动窗口](https://www.luogu.com.cn/problem/P1886)，即在维护长度为 $len$ 的区间中的最值，可以拿单调队列来维护。    
  现在的区别为滑动窗口里的值变为了一个小区间中的代价，但同样可以维护区间中的最小值。   
  那么该怎么转移呢？    
  不难发现在滑动窗口对答案有效时，仅当窗口的左端点在当前区间内，因此在窗口滑出区间的前一步进行对区间 $[i,j]$ 的转移就行。    
  由于单调队列的队头是区间最小值，因此该转移是区间的最优情况。     
  拿单调队列维护 DP 转移的复杂度为 $O(n^2)$。
    ``` cpp
  #include <bits/stdc++.h>
	#define int long long
	using namespace std;
	const int N=3e3+5;
	int f[N][N],sum[N];
	int n,a,b,c,d,x[N];
	inline int get(int now,int lenn){return sum[now+lenn-1]-sum[now-1]+f[now][now+lenn-1];}
	struct node{/* 手写单调队列 */
		int q[N];
		int head,tail;
		void init(){head=1,tail=0;}
		bool empty(){return head>tail;}
		int size(){return tail-head+1;}
		int front(){return q[head];}
		int end(){return q[tail];}
		void pop(){tail--;}
		void push(int x){q[++tail]=x;}
		void pop_front(){++head;}
	}q;
	signed main() {
		ios::sync_with_stdio(0);cin.tie(0);
		cin>>n>>a>>b>>c>>d;
		for(int i=1;i<=n;i++) cin>>x[i],sum[i]=sum[i-1]+x[i];
		for(int len=1;len<=n;len++){
			for(int i=1;i+len-1<=n;i++){
				int j=i+len-1;
				f[i][j]=max(x[j]-f[i][j-1],x[i]-f[i+1][j]);	
			}
			int lenn=max(0ll,len-b);
			if(lenn==0){
				for(int i=1;i+len-1<=n;i++){
					int j=i+len-1;
					f[i][j]=max(f[i][j],sum[j]-sum[i-1]-a);
				}
			}
			else{
				q.init();
				for(int now=1;now+lenn-1<=n;now++){
					while(!q.empty()&&get(now,lenn)<=get(q.end(),lenn)) q.pop();
					q.push(now);
					if(!q.empty()&&q.front()<now+lenn-len) q.pop_front();
					int i=now+lenn-len,j=now+lenn-1;
					if(i>0&&j<=n) f[i][j]=max(f[i][j],sum[j]-sum[i-1]-get(q.front(),lenn)-a);
				}
			}
			lenn=max(0ll,len-d);
			if(lenn==0){
				for(int i=1;i+len-1<=n;i++){
					int j=i+len-1;
					f[i][j]=max(f[i][j],sum[j]-sum[i-1]-c);
				}
			}
			else{
				q.init();
				for(int now=1;now+lenn-1<=n;now++){
					while(!q.empty()&&get(now,lenn)<=get(q.end(),lenn)) q.pop();
					q.push(now);
					if(!q.empty()&&q.front()<now+lenn-len) q.pop_front();
					int i=now+lenn-len,j=now+lenn-1;
					if(i>0&&j<=n) f[i][j]=max(f[i][j],sum[j]-sum[i-1]-get(q.front(),lenn)-c);
				}
			}
		}
		cout<<f[1][n];
		return 0;
	}
  ```
- #### 线段树、ST 表
  线段树也是一样的，拿线段树维护区间的最小值，转移方法与单调队列一样。   
  只不过线段树的复杂度为 $O(n\log n)$，常数也比较大，但也足以通过此题。使用线段树优化 DP 的复杂度为 $O(n^2\log n)$。
    ```cpp
  #include <bits/stdc++.h>
  #define p2 p<<1
	#define p3 p<<1|1
	#define j i+len-1
	#define int long long
	using namespace std;
	const int N=3e3+5,inf=1e18;
	int f[N][N],sum[N],tr[N<<2];
	int n,a,b,c,d,x[N];
	inline int get(int now,int lenn) {return sum[now+lenn-1]-sum[now-1]+f[now][now+lenn-1];}
	void build(int l,int r,int p,int lenn){
		if(l==r) return (void)(tr[p]=get(l,lenn));
		int mid=(l+r)>>1;
		build(l,mid,p2,lenn),build(mid+1,r,p3,lenn);
		tr[p]=min(tr[p2],tr[p3]);
	}
	int query(int l,int r,int ll,int rr,int p){
		if(l>=ll&&r<=rr) return tr[p];
		int ret=inf,mid=(l+r)>>1;
		if(ll<=mid) ret=min(ret,query(l,mid,ll,rr,p2));
		if(mid+1<=rr) ret=min(ret,query(mid+1,r,ll,rr,p3));
		return ret;
	}
	signed main() {
		ios::sync_with_stdio(0);cin.tie(0);
		cin>>n>>a>>b>>c>>d;
		for(int i=1; i<=n; i++) cin>>x[i],sum[i]=sum[i-1]+x[i];
		for(int len=1; len<=n; len++) {
			for(int i=1; i+len-1<=n; i++) f[i][j]=max(x[j]-f[i][j-1],x[i]-f[i+1][j]);
			int lenn=max(0ll,len-b);
			if(lenn==0) for(int i=1; i+len-1<=n; i++) f[i][j]=max(f[i][j],sum[j]-sum[i-1]-a); 
			else {
				build(1,n-lenn+1,1,lenn);
				for(int i=1;i+len-1<=n;i++) f[i][j]=max(f[i][j],sum[j]-sum[i-1]-query(1,n-lenn+1,i,j-lenn+1,1)-a);
			}
			lenn=max(0ll,len-d);
			if(lenn==0) for(int i=1; i+len-1<=n; i++) f[i][j]=max(f[i][j],sum[j]-sum[i-1]-c); 
			else {
				build(1,n-lenn+1,1,lenn);
				for(int i=1;i+len-1<=n;i++) f[i][j]=max(f[i][j],sum[j]-sum[i-1]-query(1,n-lenn+1,i,j-lenn+1,1)-c);
			}
		}
		cout<<f[1][n];
		return 0;
	}
  ```
  同理使用 ST 表也可以维护与线段树一样的相同查询，复杂度为 $O(n\log n)$，但 ST 表的常数更小，会更快一些，实测使用 ST 表的时间约为 $250ms$。   
  使用 ST 表维护 DP 的复杂度为 $O(n^2\log n)$。   
    ```cpp
  	#include <bits/stdc++.h>
	#define int long long
	using namespace std;
	const int N=3e3+5;
	int f[N][N],sum[N],st[N][20];
	int n,a,b,c,d,x[N];
	inline int get(int now,int lenn) {
		return sum[now+lenn-1]-sum[now-1]+f[now][now+lenn-1];
	}
	void build(int len,int lenn) {
		for(int i=1; i<=len; i++) st[i][0]=get(i,lenn);
		for(int j=1; j<=__lg(len); j++) {
			for(int i=1; i<=len-(1<<j)+1; i++) st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
	inline int query(int l,int r) {
		int k=__lg(r-l+1);
		return min(st[l][k],st[r-(1<<k)+1][k]);
	}
	signed main() {
		ios::sync_with_stdio(0);
		cin.tie(0);
		cin>>n>>a>>b>>c>>d;
		for(int i=1; i<=n; i++) cin>>x[i],sum[i]=sum[i-1]+x[i];
		for(int len=1; len<=n; len++) {
			for(int i=1; i+len-1<=n; i++){
				int j=i+len-1;
				f[i][j]=max(x[j]-f[i][j-1],x[i]-f[i+1][j]);
			}
			int lenn=max(0ll,len-b);
			if(lenn==0) {
				for(int i=1; i+len-1<=n; i++) {
					int j=i+len-1;
					f[i][j]=max(f[i][j],sum[j]-sum[i-1]-a);
				}
			} else {
				build(n-lenn+1,lenn);
				for(int i=1; i+len-1<=n; i++) {
					int j=i+len-1;
					f[i][j]=max(f[i][j],sum[j]-sum[i-1]-query(i,j-lenn+1)-a);
				}
			}
			lenn=max(0ll,len-d);
			if(lenn==0) {
				for(int i=1; i+len-1<=n; i++) {
					int j=i+len-1;
					f[i][j]=max(f[i][j],sum[j]-sum[i-1]-c);
				}
			} else {
				build(n-lenn+1,lenn);
				for(int i=1; i+len-1<=n; i++){
					int j=i+len-1;
					f[i][j]=max(f[i][j],sum[j]-sum[i-1]-query(i,j-lenn+1)-c);
				}
			}
		}
		cout<<f[1][n];
		return 0;
	}
  ```
### 小结
此题的方法很多，但总体差不多，都是优化转移的过程。    
看到题目可以去想方程的转移过程中是否有重复的枚举或可以避免掉不优的情况，借此来进行优化可以从而想出正解。

---

## 作者：Southern_Dynasty (赞：2)

区间 DP。

设 $f_{l,r}$ 表示只考虑 $[l,r]$，先手得分减后手得分的最大值（并不关心谁是先手谁是后手），区间长度 $len=r-l+1$。

然后对三种情况分别讨论：

- 使用操作一，此时取掉左/右端点的部分先手后手互换，对答案的贡献为 $\max(a_l-f_{l+1,r},a_r-f_{l,r-1})$。

- 使用操作二，继续分讨：

   - $len\le B$：直接全部取走，贡献为 $(\sum_{i=l}^{r}a_i)-A$。
   - $len>B$：考虑将 $B$ 的长度分配给前缀和后缀，贡献为 $\max_{i=0}^{B}(\sum_{i=l}^{l+i-1}a_i)+(\sum_{i=r-(B-i)+1}^{r}a_i)-A-f_{l+i,r-(B-i)}$。

- 操作三同理：

	- $len\le D$：直接全部取走，贡献为 $(\sum_{i=l}^{r}a_i)-C$。
   - $len>D$：考虑将 $D$ 的长度分配给前缀和后缀，贡献为 $\max_{i=0}^{D}(\sum_{i=l}^{l+i-1}a_i)+(\sum_{i=r-(D-i)+1}^{r}a_i)-C-f_{l+i,r-(D-i)}$。
   
然后对上述贡献取 $\max$ 就是 $f_{l,r}$ 的值。
   
用前缀和维护一下即可做到 $O(n^3)$。

[Code](https://atcoder.jp/contests/abc303/submissions/41865962)

考虑优化。容易发现，此时操作一、操作二和操作三的第一种情况复杂度都是对的。只有操作二、操作三的第二种情况需要枚举长度，时间复杂度 $O(n)$。

考虑对 $len$ 相同的区间同时处理：记 $j=B-i$（$i$ 就是操作二转移方程里的，操作三同理），$s(l,r)$ 表示 $[l,r]$ 的区间和。转化一下转移方程：

$$
\max_{i=0}^{B}s(l,l+i-1)+s(r-j+1,r)-A-f_{l+i,r-j}
$$

$$
=\max_{i=0}^{B}s(l,r)-s(l+i,r-j)-A-f_{l+i,r-j}
$$

这个时候我们发现 $s(l,r)$ 和 $A$ 是定值。提出来，就变成了：

$$
s(l,r)-A-\min_{i=0}^{B}s(l+i,r-j)+f_{l+i,r-j}
$$

现在考虑维护后面这坨东西。

容易发现，$[l+i,r-j]$ 这个区间的长度是不变的，都为 $len-B$。令 $g_i=f_{i,i+len-B-1}+s(i,i+len-B-1)$。此时发现方程就是

$$
s(l,r)-A-\min_{i=l}^{l+B}g_i
$$

然后直接用 ST 表维护 $\min g_i$ 即可。对于不同的 $len$ 直接重构即可。时间复杂度 $O(n^2\log n)$，可以通过此题。

[Code](https://atcoder.jp/contests/abc303/submissions/41866561)

---

## 作者：0xyz (赞：2)

### 一、题目大意

Takahashi（先手）和 Aoki（后手）在玩游戏。他们有无限的钱，从左到右一共有 $N$ 个物品，第 $i$ 个价值 $x_i$，两个人轮流操作，每次轮到的一个人可以做 $3$ 种操作之一（假设还剩下 $n$ 个物品）。

- 拿走最左边或者最右边的物品。
- 付给 Snuke $A$ 块钱，然后拿走最左边和最右边的共 $\min(B,n)$ 个物品。
- 付给 Snuke $C$ 块钱，然后拿走最左边和最右边的共 $\min(D,n)$ 个物品。

定义一个人的最大收益是拿到的所有东西的价值之和减去付给 Snuke 的钱数。

请问如果 $2$ 个人都使用最优策略，使得自身的收益减去对方的收益尽量的大，那么最终 Takahashi 的收益减去 Aoki 的收益会是多少？

- $1\le B,D\le N\le 3000,A,C\le 10^9$

### 二、做法

部分来自官方题解。

#### 1. 确定算法

面对这种双方轮流从一个序列两端取走物品并且要最大化自己的收益减去对方的收益的策略游戏，我们一般直接选择区间 dp。

#### 2. 状态设计

令 $f_{i,j}$ 表示序列里还有从第 $j$ 个开始的 $i$ 个物品（之所以不令 $f_{i,j}$ 代表区间 $[i,j]$ 是因为这样方便优化），要求此时双方都使用最优策略，最终先手减去后手的收益。我们要求的就是 $f_{n,1}$。

#### 3. 状态转移

依据题意直接写。

$(1)$ 拿走最左边或者最右边的物品。

$f_{i,j}=\max(x_j-f_{i-1,j+1},x_{i+j-1}-f_{i-1,j})$


$(2)$ 付给 Snuke $Z$ 块钱，然后拿走最左边和最右边的物品直到剩下 $k$ 个物品。

枚举剩下 $k$ 个物品从第几个开始，这里用 $l$ 表示。方便起见，我们用 $S(i,j)$ 代表从第 $j$ 个开始的 $i$ 个物品的价值和，可以用前缀和计算。

$f_{i,j}=\max\limits_{j\le l\le j+i-k}\{S(i,j)-S(k,l)-f_{k,l}-Z\}$

总时间复杂度 $O(n^3)$，超时。

#### 4. 优化转移

我们可以将 $(2)$ 的式子变成：

$f_{i,j}=S(i,j)-Z-\min\limits_{j\le l\le j+i-k}\{S(k,l)+f_{k,l}\}$

我们发现，对于固定的 $(i,k)$ 这样的 $[j,j+i-k]$ 长度是固定的。并且对于任意的 $i$，只有 $2$ 种 $k$。所以使用单调队列，维护 $S(k,l)+f_{k,l}$ 的最小值即可。时间复杂度 $O(n^2)$。

当然还有 $O(n^2\log n)$ 的线段树、ST 表做法，以及 $O(n^2)$ 的 $O(n)$ RMQ 做法。

### 三、代码

```cpp
#include<bits/stdc++.h>
#define S(p,q) s[p+q-1]-s[q-1]
#define V(p,q) (S(p,q)+f[p][q])
using namespace std;
typedef long long ll;
ll f[3010][3010],n,A,B,C,D,s[3010],x[3010],q[3010];
inline void cal(ll k,ll i,ll Z){
	for(ll j=1,h=1,t=0;j<=n+1-k;j++){
		while(h<=t&&V(k,q[t])>=V(k,j))t--;
		q[++t]=j;
		while(h<t&&q[h]<j+k-i)h++;
		if(j+k>i)f[i][j+k-i]=max(f[i][j+k-i],S(i,j+k-i)-Z-V(k,q[h]));
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>A>>B>>C>>D;
	for(ll i=1;i<=n;i++)cin>>x[i],s[i]=s[i-1]+x[i];
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n+1-i;j++)f[i][j]=max(x[j]-f[i-1][j+1],x[i+j-1]-f[i-1][j]);
		cal(i-min(i,B),i,A);cal(i-min(i,D),i,C);
	}
	cout<<f[n][1]<<'\n';
	return 0;
}
```

---

## 作者：DE_aemmprty (赞：1)

### 1 题目大意

**1.1 题目翻译**

有两个人轮流取物品。总共有 $n$ 个物品，第 $i$ 个物品的价值为 $w_i$。

他们按照下面的其中一种方式取物品：

* 取出这一排物品最前面的或者最后面的。这一步没有代价。

* 设还剩下 $m$ 个物品，那么重复取出 $\min(B, m)$ 个物品，每次取出最前面的或者最后面的。这一步的代价为 $A$。

* 设还剩下 $m$ 个物品，那么重复取出 $\min(D, m)$ 个物品，每次取出最前面的或者最后面的。这一步的代价为 $C$。

最后一个人取出物品的价值为所有他取出物品价值之和减去他所花费的代价。问当两人均以最优策略取物品时，先手取出物品的价值减去后手取出物品的价值为多少。

**1.2 数据范围**

对于 $100\%$ 的数据：

* $1 \leq B, D \leq n \leq 3000$

* $A, C \leq 10 ^ 9$

### 2 解法分析

**2.1 初见此题**

首先，一看这道题，我们就会发现：不管怎么取物品，任何时刻的序列一定是原序列的一段连续子区间。所以，我们不难想到区间 DP。

**2.2 暴力 DP**

设 $f_{i, j}$ 表示当前序列为原序列从第 $i$ 个到第 $j$ 个元素时，答案的最大值。那么，会有 $3$ 种情况：

* 操作 1。此时，$f_{i,j} = \max(w_i - f_{i + 1, j}, w_j - f_{i, j - 1})$

* 操作 2。设 $l = j - i + 1$，则：

    * 当 $B \geq l$ 时：
    $$f_{i, j} = (\sum_{i \leq k \leq j}w_k) - A$$
    
    * 当 $B < l$ 时：
    $$f_{i, j} = \max_{0 \leq k \leq B}\{(\sum_{i \leq p \leq i + k - 1} w_p) + (\sum_{j - B + k + 1 \leq p \leq j}w_p) - A - f_{i + k, j - B + k}\}$$
    
* 操作 3。大致与操作 2 相同，这里就不过多叙述。

至此，我们完成了暴力 DP，时间复杂度为 $\mathcal{O}(n^3)$，显然过不了。

所以，接下来，我们就要考虑优化。

暴力代码如下：

```cpp
int getsum(int l, int r){
	return sum[r] - sum[l - 1];
}

void update(int A, int B, int i, int j, int &x){
	if (B >= j - i + 1)
		x = max(x, getsum(i, j) - A);
	else 
		f (k, 0, B)
			x = max(x, getsum(i, j) - getsum(i + k, j - B + k) - A - dp[i + k][j - B + k]);
}

signed main() {
	cin >> n >> A >> B >> C >> D;
	f (i, 1, n) {
		scanf("%lld", &w[i]);
		sum[i] = sum[i - 1] + w[i];
	}
	g (i, n, 1)
		f (j, i, n){
			dp[i][j] = max(w[i] - dp[i + 1][j], w[j] - dp[i][j - 1]);
			update(A, B, i, j, dp[i][j]);
			update(C, D, i, j, dp[i][j]);
		}
	printf("%lld\n", dp[1][n]);
	return 0;
}
```

**2.3 DP 优化**

观察 DP 方程。我们发现，极限复杂度只出现在了操作 2 当 $B < l$ 的情况。所以，我们把这个式子的 $\max$ 去掉，得：

$$
(\sum_{i \leq p \leq i + k - 1} w_p) + (\sum_{j - B + k + 1 \leq p \leq j}w_p) - A - f_{i + k, j - B + k}
$$

我们发现，$(\sum_{i \leq p \leq i + k - 1} w_p) + (\sum_{j - B + k + 1 \leq p \leq j}w_p)$ 可以前缀和 $\mathcal{O}(1)$ 计算。设 $s_{l, r}$ 为 $l$ 到 $r$ 的物品价值之和，于是得：

$$
- s_{i + k, j - B + k} - f_{i + k, j - B + k} - A + s_{i, j}
$$

观察这个方程。我们把 $k$ 视为未知数，$i, j$ 视为常数，则 $s_{i,j} - A$ 为常数，可以提到 $\max$ 外面。所以，我们需要维护的只有：

$$
s_{i + k, j - B + k} + f_{i + k, j - B + k}
$$

发现这两个区间的长度都是 $(j - B + k) - (i + k) = j - i - B + 1$，那么相当于只需要维护长度为 $x$ 的 $f_{i, i + x - 1} + s_{i, i + x - 1}$ 中最小的一个即可。

这有许多维护方法，比如优先队列，线段树，ST 表。

至此，这道题就完成了。时间复杂度为 $\mathcal{O}(n^2)$ 或者 $\mathcal{O}(n^2\log{n})$

这里我使用了 ST 表，代码如下：

```cpp
int getsum(int l, int r){
	return sum[r] - sum[l - 1];
}

void init(){
	f (i, 2, n)
		lg[i] = lg[i / 2] + 1;
}

int query(int l, int r){
	int p = lg[r - l + 1];
	return min(st[l][p], st[r - (1ll << p) + 1][p]);
}

void update(int A, int B, int i, int j, int &x){
	if (B >= j - i + 1)
		x = max(x, getsum(i, j) - A);
	else 
		x = max(x, getsum(i, j) - A - query(i, i + B));
}

void build(int len){
	f (i, 1, n - len + 1)
		st[i][0] = dp[i][i + len - 1] + getsum(i, i + len - 1);
	f (j, 1, 15)
		f (i, 1, n - len + 2 - (1ll << j))
			st[i][j] = min(st[i][j - 1], st[i + (1ll << (j - 1))][j - 1]);
}

signed main() {
	cin >> n >> A >> B >> C >> D;
	f (i, 1, n) {
		scanf("%lld", &w[i]);
		sum[i] = sum[i - 1] + w[i];
	}
	init();
	f (len, 1, n) {
		f (i, 1, n - len + 1){
			int j = i + len - 1;
			dp[i][j] = max(w[i] - dp[i + 1][j], w[j] - dp[i][j - 1]);
		}
		if (len > B)
			build(len - B);
		f (i, 1, n - len + 1)
			update(A, B, i, i + len - 1, dp[i][i + len - 1]);
		if (len > D)
			build(len - D);
		f (i, 1, n - len + 1) {
			update(C, D, i, i + len - 1, dp[i][i + len - 1]);
		}
	}
	printf("%lld\n", dp[1][n]);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：1)

经典题，考虑区间 dp，$f_{l,r}$ 表示只考虑 $[l, r]$ 区间，先手得分减后手得分最大值。

对于第一种操作直接 $f_{l,r} \gets \max(a_l - f_{l+1,r}, a_r - f_{l,r-1})$，第二种操作，考虑枚举 $[l,r]$ 长为 $r - l + 1 - B$ 的子段，即可转移。第三种操作同理。

那么我们得到了[一个 $O(n^3)$ 的做法](https://atcoder.jp/contests/abc303/submissions/41798440)。考虑优化。发现瓶颈在于枚举子段。发现因为子段长度固定，所以可以直接查固定区间长度的形似 $f_{p,p+k-1}$ 的最大值。考虑使用 ST 表，按区间长度从小到大计算每个 $f_{l,r}$，当一个长度的区间都计算完了，就把它们扔给 ST 表预处理。

时空复杂度均为 $O(n^2 \log n)$。

[code](https://atcoder.jp/contests/abc303/submissions/41798797)

---

## 作者：Claire0918 (赞：0)

我们注意到两侧都可以取出物品，所以两侧都是可以转移的，考虑区间 dp。

设 $f_{l, r, p}$ 表示在原序列中位于 $[l, r]$ 中物品在 $p \in \{0, 1\}$ 的人首先选的答案。

我们只讨论 $f_{l, r, 0}$ 的转移，$f_{l, r, 1}$ 可以对称得出。

首先，根据第一条有 $f_{l, r, 0} \gets \max\{f_{l + 1, r, 1} + x_l, f_{l, r - 1, 1} + x_r\}$。

对于第二条，我们在 $[l, r]$ 中取出一个长度为 $\max\{0, |[l, r]| - B\}$ 的子序列 $[l', r']$，有转移 $\displaystyle f_{l, r, 0} \gets \max_{[l', r']} \{f_{l', r'} + \sum_{i = l}^{l' - 1} x_i + \sum_{i = r' + 1}^{r} x_i - A\}$。我们记 $\displaystyle s_i = \sum_{k = 1}^{i} x_i$，则有 $\displaystyle f_{l, r, 0} \gets \max_{[l', r']} \{f_{l', r'} + s_{l' - 1} - s_{l - 1} + s_{r} - s_{r'} - A\} = \max_{[l', r']} \{f_{l', r'} + s_{l' - 1} - s_{r'}\} + s_{r} - s_{l - 1} - A$。

暴力转移的复杂度将会达到 $\mathcal{O}(n^3)$，我们考虑优化。

事实上，$r'$ 是与 $l'$ 线性相关的。所以在大括号中的东西是仅随 $l'$ 而变化的，而大括号外的是不变的。我们考虑使用数据结构维护 $f_{l', r'} + s_{l' - 1} - s_{r'}$，可以做到 $\mathcal{O}(1)$ 或者 $\mathcal{O}(\log n)$ 转移。

一种简单的实现是使用 st 表，对于 $\mathcal{O}(n^2)$ 个 $[l, r]$，使用 $\mathcal{O}(n\log n)$ 的复杂度预处理 st 表，单次 $\mathcal{O}(1)$ 的复杂度进行转移。

总时间复杂度是 $\mathcal{O}(n^2\log n)$，可以通过。

对于 $p = 1$ 的一切情况和 $p = 0$ 的第三条转移，读者可以通过上述的内容对称地推出，故在此不再细致说明了。

特别需要注意 $p = 1$ 时转移是取最小值，与 $p = 0$ 相反。读者需要对于不同的需求进行细致地初始化。

特别指出，存在一种使用单调队列以代替数据结构优化转移的做法可以做到 $\mathcal{O}(n^2)$ 的优秀复杂度，此处不给出实现。

除此之外，给出实现的 st 表做法存在优化空间。我们注意到区间长度为 $0$ 的 st 表是可能需要多次的，故可以直接将其存下。这样的复杂度并不会有改变，但对于较大的数据优化显著。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 3000 + 10, maxlog = 12;
const long long INF_MAX = 1e18, INF_MIN = -1e18;

int n, a, b, c, d;
long long x[maxn], pre[maxn], f[maxn][maxn][2], st1[maxn][maxlog + 10], st2[maxn][maxlog + 10];

inline void build1(int len){
    for (int i = 1; i <= n; i++){
        st1[i][0] = f[i][i + len - 1][1] + pre[i - 1] - pre[i + len - 1];
    }
    for (int j = 1; j <= maxlog; j++){
        for (int i = 1; i + (1 << j) - 1 <= n; i++){
            st1[i][j] = max(st1[i][j - 1], st1[i + (1 << j - 1)][j - 1]);
        }
    }
}

inline long long query1(int l, int r){
    const int k = __lg(r - l + 1);
    return max(st1[l][k], st1[r - (1 << k) + 1][k]);
}

inline void build2(int len){
    for (int i = 1; i <= n; i++){
        st2[i][0] = f[i][i + len - 1][0] - pre[i - 1] + pre[i + len - 1];
    }
    for (int j = 1; j <= maxlog; j++){
        for (int i = 1; i + (1 << j) - 1 <= n; i++){
            st2[i][j] = min(st2[i][j - 1], st2[i + (1 << j - 1)][j - 1]);
        }
    }
}

inline long long query2(int l, int r){
    const int k = __lg(r - l + 1);
    return min(st2[l][k], st2[r - (1 << k) + 1][k]);
}

int main(){
    scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
    for (int i = 1; i <= n; i++){
        scanf("%lld", &x[i]);
        pre[i] = pre[i - 1] + x[i];
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            f[i][j][0] = INF_MIN;
            f[i][j][1] = INF_MAX;
        }
    }
    for (int i = 1; i <= n; i++){
        f[i + 1][i][0] = f[i + 1][i][1] = 0;
    }
    for (int len = 1; len <= n; len++){
        for (int l = 1; l + len - 1 <= n; l++){
            const int r = l + len - 1;
            f[l][r][0] = max({f[l][r][0], f[l + 1][r][1] + x[l], f[l][r - 1][1] + x[r]});
        }
        int lst = max(0, len - b);
        build1(lst);
        for (int l = 1; l + len - 1 <= n; l++){
            const int r = l + len - 1;
            // p \in S s.t. l + p + lst - 1 <= r
            f[l][r][0] = max(f[l][r][0], query1(l, r - lst + 1) - pre[l - 1] + pre[r] - a);
        }
        lst = max(0, len - d);
        build1(lst);
        for (int l = 1; l + len - 1 <= n; l++){
            const int r = l + len - 1;
            // p \in S s.t. l + p + lst - 1 <= r
            f[l][r][0] = max(f[l][r][0], query1(l, r - lst + 1) - pre[l - 1] + pre[r] - c);
        }
        
        for (int l = 1; l + len - 1 <= n; l++){
            const int r = l + len - 1;
            f[l][r][1] = min({f[l][r][1], f[l + 1][r][0] - x[l], f[l][r - 1][0] - x[r]});
        }
        lst = max(0, len - b);
        build2(lst);
        for (int l = 1; l + len - 1 <= n; l++){
            const int r = l + len - 1;
            // p \in S s.t. l + p + lst - 1 <= r
            f[l][r][1] = min(f[l][r][1], query2(l, r - lst + 1) + pre[l - 1] - pre[r] + a);
        }
        lst = max(0, len - d);
        build2(lst);
        for (int l = 1; l + len - 1 <= n; l++){
            const int r = l + len - 1;
            // p \in S s.t. l + p + lst - 1 <= r
            f[l][r][1] = min(f[l][r][1], query2(l, r - lst + 1) + pre[l - 1] - pre[r] + c);
        }
    }
    printf("%lld", f[1][n][0]);

return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

有 $n$ 个物品，第 $i$ 个物品价值为 $x_i$。

Alice 和 Bob 在玩游戏。Alice 先手，每次可以进行下列操作中的一种：

- 拿走最左边的物品。
- 拿走最右边的物品。
- 支付 $A$ 元钱，拿走最多 $B$ 个物品。
- 支付 $C$ 元钱，拿走最多 $D$ 个物品。

当没有物品时，游戏结束。此时 Alice 可以赚得 $X-Y$ 元钱，其中 $X$ 为 Alice 拿走的物品总价值，$B$ 为 Bob 拿走的物品总价值。

Alice 希望最大化赚得的钱数，Bob 希望最小化 Alice 赚得的钱数。你需要求出假如两人都绝顶聪明，Alice 可以赚得的钱数。

$1\leq B,D\leq n\leq 3000,1\leq A,C,x_i\leq 10^9$。

## 思路

首先对于类似双端队列的最优化 / 计数 / 博弈问题，我们有一种非常经典的方法是区间 dp。

下面记 $P(i)=\sum_{k=1}^{i}x_k$。

设 $f(i,j)$ 表示考虑到区间 $[i,j]$ 的最大收益。我们依次考虑每一种操作：

* 拿走左边的物品 $f(i,j)\leftarrow x_i-f(i+1,j)$。
* 拿走右边的物品 $f(i,j)\leftarrow x_j-f(i-1,j)$。
* 支付 $A$ 元钱拿走两端最多 $B$ 个物品。这需要分两种情况讨论：

  * $j-i+1\leq B$，则 $f(i,j)\leftarrow -A+P(j)-P(i-1)$。
  * $j-i+1>B$。这时拿完后会剩下一段长度为 $j-i+1-B$ 的区间的所有物品。我们可以枚举这一段区间：

    $$
    f(i,j)\leftarrow -A+P(j)-P(i-1)-\min_{k=i}^{B+i} P(k+j-i-B) - P(k-1)+f(k, k+j-i-B)
    $$
* 支付 $C$ 元钱拿走两段最多 $D$ 个物品。和上面的操作类似，不再赘述。

暴力转移，时间复杂度 $O(n^3)$ 难以承受。主要问题集中在考虑 $j-i+1>B$ 时的转移。

我们观察这个式子：

$$
\min_{k=i}^{B+i} P(k+j-i-B) - P(k-1)+f(k, k+j-i-B)
$$

令 $F(i,j)=P(j)-P(i-1)+f(i,j)$，可以得到：

$$
\min_{k=i}^{B+i} F(k,k+j-i-B)
$$

可以看成一个（形式较为简单的）求最小值的问题。

考虑这个东西怎么求。令 $G(i,j)=\min_{k=i}^{B+i}F(k,k+j-1)$，则上述求最小值的式子就是 $G(i,j-i+1-B)$。

那 $G$ 怎么求呢？观察这个形式，我们发现固定 $F(i,j)$ 中的 $j-i+1$ 不变化，可以看成一个滑动窗口（静态定长区间 RMQ 查询）的问题。

而滑动窗口是可以用单调队列单次 $O(n)$ 求的。于是整个 dp 过程也就被优化到了 $O(n^2)$。可以通过本题。

实现的时候注意是长度为 $B+1$ 和 $D+1$ 的窗口，且注意各种数组越界问题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3005;
int n, A, B, C, D, a[N], f[N][N], g[N][N][2];
int q[N], head, tail;

void sliding(int len, int siz, bool tag){
    head = 1; tail = 0;
    auto get = [&](int i){ return f[i][i + len - 1] + (a[i + len - 1] - a[i - 1]); };
    for(int i=1;i<=min(siz - 1, n - len + 1);i++){
        while(head <= tail && get(q[tail]) >= get(i)) tail--;
        q[++tail] = i;
    }
    for(int i=siz;i<=(n - len + 1);i++){
        while(head <= tail && get(q[tail]) >= get(i)) tail--;
        q[++tail] = i;
        while(head <= tail && q[head] <= (i - siz)) head++;
        g[len][i - siz + 1][tag] = get(q[head]);
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> A >> B >> C >> D;
    for(int i=1;i<=n;i++) cin >> a[i], a[i] += a[i - 1];
    for(int i=1;i<=n;i++) f[i][i] = a[i] - a[i - 1];
    sliding(1, B + 1, 0); sliding(1, D + 1, 1);
    for(int len=2;len<=n;len++){
        for(int l=1,r=len;r<=n;l++,r++){
            f[l][r] = (a[l] - a[l - 1]) - f[l + 1][r];
            f[l][r] = max(f[l][r], (a[r] - a[r - 1]) - f[l][r - 1]);
            if(len <= B) f[l][r] = max(f[l][r], a[r] - a[l - 1] - A);
            else f[l][r] = max(f[l][r], a[r] - a[l - 1] - A - g[len - B][l][0]);
            if(len <= D) f[l][r] = max(f[l][r], a[r] - a[l - 1] - C);
            else f[l][r] = max(f[l][r], a[r] - a[l - 1] - C - g[len - D][l][1]);
        }
        sliding(len, B + 1, 0); sliding(len, D + 1, 1);
    }
    cout << f[1][n] << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

