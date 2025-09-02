# K Smallest Sums

## 题目描述

有一个 $k \times k$ 的矩阵，在每行任取一个位置，把这些位置的元素相加的到一个值，求前 $k$ 小的值。

## 说明/提示

对于 $100\%$ 的数据，$2 \leq k \leq 750$。

## 样例 #1

### 输入

```
3
1 8 5
9 2 5
10 7 6
2
1 1
1 2```

### 输出

```
9 10 12
2 2```

# 题解

## 作者：一扶苏一 (赞：12)

### 显然可以一行一行做。

同时如果S+now[j]最小，需要S最小。即我们只需要记录前i行的最小的k个ans，分别与当前行的k个相加，从k^2个ans中选择前k个小的记录。显然前k小的可以开一个大根堆维护。即如果size>k则pop。这样一共有k次转移，每次转移有k^2个状态，维护k的堆的复杂度为Logk，这样总复杂度为O(k^3logk)。

因为易于通过数学归纳证明取第i行的最小的只需要与前i-1行最小的k个ans相加得到。这样我们不妨用数组ans记录前i行最小的k个ans，现在我们考虑我们有两个数组a,b，需要取k个ans最小。不妨设a和b都是有序的，我们显然有如下关系：

```
	a1+b1≤a1+b2≤a1+b3≤a1+b4≤……≤a1+bk

　　a2+b1≤a2+b2≤a2+b3≤a2+b4≤……≤a2+bk

　　……

　　ak+b1≤ak+b2≤ak+b3≤ak+b4≤……≤ak+bk
```

这样显然ai+bj**可能**成为前k小的ans当且仅当ai+bj-1是前k小的ans。

我们维护一个**可能**成为ans的序列，每次取这个序列中最小，显然最小值可以成为合法的ans。同时不妨设这个值为ai+bj，那么我们将ai+bj+1压入序列，因为它可能成为合法的ans。

初始化上，因为ai+b1可能成为合法的ans，我们将这k个全部压入队列中。

### Code
```
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
#ifdef ONLINE_JUDGE
#define putchar(o) \
puts("I am a cheater!")
#endif
#define maxn 1010

inline void qr(int &x) {
	char ch=getchar(),lst=NULL;
	while(ch>'9'||ch<'0') lst=ch,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(lst=='-') x=-x;
}

template <typename T>
inline T mmax(const T &a,const T &b) {if(a>b) return a;return b;}
template <typename T>
inline T mmin(const T &a,const T &b) {if(a<b) return a;return b;}
template <typename T>
inline T mabs(const T &a) {if(a>=0) return a;return -a;}

template <typename T>
inline void mswap(T &a,T &b) {T temp=a;a=b;b=temp;}

————————————————以上是头文件——————————————

int k,MU[maxn],ans[maxn];

struct Zay {
	int v,s;
	Zay(int a=0,int b=0) {v=a;s=b;}
	inline bool operator <(const Zay &others) const{return this->v>others.v;}
};

std::priority_queue<Zay>Q;
void clear();

int main() {
	while(~scanf("%d",&k)) {
		clear();
		for(int i=1;i<=k;++i) qr(ans[i]);
		for(int i=2;i<=k;++i) {
			memset(MU,0,sizeof MU);
			for(int j=1;j<=k;++j) {
				qr(MU[j]);
			}
			std::sort(MU+1,MU+1+k);
			while(!Q.empty()) Q.pop();
			for(int j=1;j<=k;++j) {
				Q.push(Zay(ans[j]+MU[1],1));
			}
			for(int j=1;j<=k;++j) {
				Zay temp=Q.top();Q.pop();
				ans[j]=temp.v;
				if(temp.s<k) Q.push(Zay(temp.v-MU[temp.s]+MU[temp.s+1],temp.s+1));
			}
		}
		for(int i=1;i<k;++i) printf("%d ",ans[i]);printf("%d\n",ans[k]);
	}
	return 0;
}

void clear() {
	memset(ans,0,sizeof ans);
}
```

## Summary
在堆的应用中，维护一坨可能合法的解进行操作，是一种常用的思路。比如本题和dijkstra算法都是这个思路。这一坨合法的解一般满足下面两个条件：

第一，这坨解中最大/小的解一定是合法的解。比如本题中，序列中最小的一定是合法的解，dijkstra算法中，堆中权值和最小的解一定是到该点的最短路等等

第二，通过寻找合法解，可以获得其他可能解。比如在本题中，ai+bj合法时，ai+bj+1是可能解。在dijkstra算法中，找到到一个点的最短路可以更新和它相邻的点的可能最短路压入堆中。

---

## 作者：MY_Lee (赞：8)

$\mathrm{Update\ on\ 2020/4/20}$：哦买噶 $\LaTeX$ 居然炸了赶紧修啊。

$\mathrm{Update\ on \ 2022/5/6}$：修正了一个笔误。
#### 闲聊

> 我不知道那么长的题面想说什么$\cdots\cdots$

---
### 思路

如果我们把所有和都求出来再排序，复杂度为 $\mathcal{O(n^n+n^n\log n^n)}$。~~想都不用想 T 飞飞~~。

---
我们先把矩阵的每行升序排序。

然后考虑把矩阵的前两行进行求和，得到如下表格：

| |$x_1$|$x_2$|$\cdots$|$x_k$|
|:-----:|:-----:|:-----:|:-----:|:-----:|
|$y_1$|$x_1+y_1$|$x_2+y_1$|$\cdots$|$x_k+y_1$|
|$y_2$|$x_1+y_2$|$x_2+y_2$|$\cdots$|$x_k+y_2$|
|$\cdots$|$\cdots$|$\cdots$|$\cdots$|$\cdots$|
|$y_k$|$x_1+y_k$|$x_2+y_k$|$\cdots$|$x_k+y_k$|

然后我们试着找一找规律：

- $\because x_1\le x_2\le x_3\le\cdots\le x_k$
- $\therefore x_1+y_1\le x_2+y_1\le x_3+y_1\le\cdots\le x_k+y_1$

我们发现:

$x_1+y_i\le x_2+y_i\le x_3+y_i\le\cdots\le x_k+y_i(1\le i\le k)$

所以我们就有了一种思路。

开一个堆，预处理将堆中放入 $x_1+y_1,x_2+y_1,\cdots,x_k+y_1$

然后每次我们都取出堆顶，设它为 $x_i+y_j$，那么我们记录一下它，然后压入 $x_{i+1}+y_j$ 即可。循环 $k$ 次，就得到了两行求和的前 $k$ 小。

---
那么我们怎么做 $k$ 行求和呢？

~~这不是很简单的吗？~~ $k$ 行求和就相当于先做 $1,2$ 行，得到的 $k$ 小重新放入 $1$ 里，再做 $1,3$ 行 $\cdots$ 即可。

---
#### 代码

我用 $a$ 数组表示上述思路中的 $1$ 行，用 $b$ 数组表示上述思路中的 $2,3,\cdots,k$ 行。节省空间。

好了好了，赶紧上代码吧！

```cpp
#include<queue>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct Node{
	int number,sum;
	inline bool operator <(const Node &x)const{
		return sum>x.sum;
	}//将和升序排序
};
priority_queue<Node>sumque;
int n,a[755],tomerge[755],now[755];//now 用来记录当前是 x[?]+y[j] 中的 ?。
inline void merge(){
	while(sumque.empty()==false){
		sumque.pop();
	}//很重要！要先把堆中元素清空！
	Node tmp;
	for(register int i=1;i<=n;i++){
		tmp.number=i;tmp.sum=a[i]+tomerge[1];
		now[i]=1;//从 x[1] 开始
		sumque.push(tmp);//入堆
	}
	for(register int i=1;i<=n;i++){
		Node nowsum=sumque.top();
		sumque.pop();//取出
		a[i]=nowsum.sum;//更新
		if(now[nowsum.number]>=n){
			continue;
		}//如果已经取完 k 个了，就不用继续入堆了
		now[nowsum.number]++;//否则当前的 now[]++。
		nowsum.sum-=tomerge[now[nowsum.number]-1];
		nowsum.sum+=tomerge[now[nowsum.number]];//更新和
		sumque.push(nowsum);//入堆
	}
}
int main(){
	while(1==scanf("%d",&n)){
		for(register int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		sort(a+1,a+n+1);//预处理
		for(register int i=2;i<=n;i++){
			for(register int j=1;j<=n;j++){
				scanf("%d",&tomerge[j]);
			}
			sort(tomerge+1,tomerge+n+1);//预处理
			merge();
		}
		printf("%d",a[1]);
		for(register int i=2;i<=n;i++){
			printf(" %d",a[i]);
		}
		printf("\n");//最后答案即为 a 数组
	}
	return 0;
}
```
---
#### 番外

看在[良心出题人](https://moon-snow.blog.luogu.org/)疯狂打 $\LaTeX$ 的份上，点个大拇指再走嘛！

---

## 作者：_gcl (赞：6)

放一下题面链接：[题面](https://www.luogu.com.cn/problem/UVA11997)

蒟蒻第一篇真正意义上的题解，求过（www）


~~话说做了这个题我才明白学好英语的重要性~~

这里的中文翻译题面和原题面有所不同，没有直译，没太看懂emmm。直接看的英文，大体意思就是：

- 给定K个数组，且每个数组有K个数，然后我们从每个数组取一个和其他几个数组相加。这样的话，我们可以得到K^K个加和 （由计数原理可知）。要求输出的是些加出来的和中最小的k个值

题面不算很好理解，这里可以给举个例子


比如现在给定一个K=2，两个数组的值分别是

| 3 |5  |
| -----------: | -----------: |
| 4  | 6 |


------------


那么我们可以得出的值分别有


------------

| 3+4 |3+6  |
| -----------: | -----------: |
| 5+6 | 5+6 |

然后取K个最小的，也就是这四个里的前两个，结果便是 7,9；

本能就是打出加和后的表，然后暴力枚举前K个数，输出即可（显然TLE）

对于这种多个值取前K个最小值的问题，本能想到的便是priority_queue嘛
因为priority便可以维护处前K个小的数来

那么这个题怎么做呢？

首先先考虑两个数组合并的情况

|A1  |A2  |A3  |A4  |
| -----------: | -----------: | -----------: | -----------: |
|B1  |B2  |B3  |B4  |

如果A数组与B数组是排好序的 ， 显然我们可以得出这样一个不等关系

| A1+B1<=A1+B2<=A1+B3<=A1+B4|
| -----------: |
|A2+B1<=A2+B2<=A2+B3<=A2+B4 |
|An+B1<=An+B2<=An+B3<=An+B4  |
（偷个懒少写几个）

所以我们知道了对于加和出来的每行的最小值。但知道这个显然是不够的，这些每行的最小值显然不一定是最终的答案。比如A2+B1不一定就严格大于A1+B2

虽然没法直接知道答案，但我们可以用这些数来更新嘛。毕竟这些数是它本行最优的

那么如何更新呢？

首先
```cpp
	priority_queue<node> q;
	for(int i=0;i<n;i++)
	{
		q.push(node(A[i]+B[0],0));
	}
```
其中A是第一个数组，B是第二个数组，这样就把每行的最优情况给弄出来了

然后想，如果你这一行最优的都没法被更新，那后面的点也没有必要来更新了。如果当前这个点可以被更新，那么就添加他本行的下一个点，放入优先队列中，再取优先队列中的最小的数进行更新。显然，因为要求K个最小值，那么肯定是更新K个点的。每次进来一个点，那么答案数组就记录一个，然后优先队列再pop（）掉。因此复杂度为O（K log2（K））代码如下：

```
	for(int i=0;i<n;i++)
	{
		node cur=q.top();
		q.pop();
		C[i]=cur.s;
		if(cur.b<n-1)
		{
			q.push(node(cur.s+B[cur.b+1]-B[cur.b],cur.b+1));
		}
	}
```

有人可能会问cur.s+B[cur.b+1]-B[cur.b]是什么东西啊，这个东西其实就是当前这个数的下一个点的值。（为什么？）

关于结构体的定义如下

```cpp
struct node
{
	int s,b;//s为当前的加和的值，b为当前的这一行的第b个
	node(int s,int b):s(s),b(b){};
	bool operator < (const node & k) const
	{
		return s>k.s;//重载小于号，让小的放前面
	}
};
```
这里的s，便是当前的的值。b为当前行的第b个。为什么不用存a（记录当前行）呢？这个问题对于前面的思路已经比较显然了。因为我们最开始维护的便是每一行的最优值，所以更新只考虑当前行的问题（别的行的数他也没法更新啊）。所以此时不用存具体是多少行了，自然也就不用存a的值了。


此题不是两个表，而是k个表。那么边两两合并，合并出的最后的结果一定是最优的（为什么？）

比较显然，因为两次合并出的最小值一定是最优的，那么那这些最小值再进行合并的时候也是最优的，所以最后的答案一定是对的。放完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int s,b;
	node(int s,int b):s(s),b(b){};
	bool operator < (const node & k) const
	{
		return s>k.s;
	}
};
inline int read()
{
	int sum=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	return sum*f;
}
int n;
int A[1000][1000];
void union_(int *A,int *B,int *C)
{
	priority_queue<node> q;
	for(int i=0;i<n;i++)
	{
		q.push(node(A[i]+B[0],0));
	}
	for(int i=0;i<n;i++)
	{
		node cur=q.top();
		q.pop();
		C[i]=cur.s;
		if(cur.b<n-1)
		{
			q.push(node(cur.s+B[cur.b+1]-B[cur.b],cur.b+1));
		}
	}
}
int main()
{
	while(scanf("%d",&n)==1)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
			A[i][j]=read();
			}
			sort(A[i],A[i]+n);
		}
		for(int i=1;i<n;i++)
		{
			union_(A[0],A[i],A[0]);
		}
		printf("%d",A[0][0]);//关于输出的锅.....
		for(int i=1;i<n;i++)printf(" %d",A[0][i]);
		printf("\n");
	}
	return 0;
}
```


时间复杂度为（k^2log2（k）），稳AC






---

## 作者：Wi_Fi (赞：1)

如果直接一口气算完的话，第一是状态太多，第二是不好维护，所以考虑两两合并最后递推出结果。

因为是求加和的前 $k$ 小值，如果用数组维护排序太耗时，因此考虑用堆来维护，可以直接用 ```priority_queue```。每次存入三个值，分别是两个下标与加和。每一轮结束时更新即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=755;
struct pai
{
	int x,y,sum;
	bool operator<(const pai &a)const{
		return sum>a.sum;
	}
}t;
int i,j,n,a[N][N],b[N];
priority_queue<pai>q;
int main()
{
	while(cin>>n)
	{
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)cin>>a[i][j];
			sort(a[i]+1,a[i]+n+1);
		}
		for(i=1;i<n;i++)
		{
			while(!q.empty())q.pop();
			for(j=1;j<=n;j++)q.push({j,1,a[i][j]+a[i+1][1]});
			for(j=1;j<=n;j++)
			{
				t=q.top(),q.pop();
				b[j]=t.sum,q.push({t.x,t.y+1,a[i][t.x]+a[i+1][t.y+1]});
			}
			for(j=1;j<=n;j++)a[i+1][j]=b[j];
		}
		for(i=1;i<n;i++)cout<<b[i]<<' ';
		cout<<b[n]<<"\n";
	}
	return 0;
}
```

---

## 作者：Wiueh_Plus (赞：1)

[K Smallest Sums](https://www.luogu.com.cn/problem/UVA11997)

## Problem
在一个 $k\times k$ 的矩阵中，每行任取一个数，将取出的数加在一起，求所有可能中前 $k$ 小的值。

## Solution
先考虑每两行之间应该怎么做。这就是 [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)。

假设有两个序列 $A$ 和 $B$，长度都为 $k$。我们现将这两个序列从小到大排序。显然会有：
$$A_1+B_1\leq A_1+B_2\leq \dots A_1+B_n$$
$$A_2+B_1\leq A_2+B_2\leq \dots A_2+B_n$$
$$\dots$$
$$A_n+B_1\leq A_n+B_2\leq \dots A_n+B_n$$

显然，我们将所有式子的第一项，也就是 $A_i+B_1$ 放入一个小根堆的优先队列。自此操作开始。

每次取出优先队列中第一个元素，这个元素一定是所有结果中最小的。假设取出的元素是 $A_i+B_j$，那么我们接下来就将 $A_i+B_{j+1}$ 放入优先队列，因为 $A_i+B_{j+1}$ 也一定是在没有被选的元素中是最小的。

重复 $k$ 次操作，就可以取出所有结果中前 $k$ 小的结果。

易得时间复杂度为 $O(k\log k)$。

------------

我们仿照上面的思路，转换到多行的问题。很显然我们可以将 $k$ 行的矩阵，每次按照上面的操作合并前 $2$ 行，直到最后只剩 $1$ 行，那么最后这一行就是最终答案。

易得时间复杂度为 $O(k^2\log k)$。

## Code
```cpp
struct node{
	int id_a,id_b,val;
	friend bool operator < (node a,node b){
		return a.val > b.val;
	}
};
priority_queue<node> q;
int k,a[N],b[N],res[N];
void clear(){
	while (!q.empty()){
		q.pop();
	}
}
signed main(){
	while (~scanf("%lld",&k)){
		for (int i = 1;i <= k;i++){
			a[i] = read();
		}
		for (int cnt = 2;cnt <= k;cnt++){
			for (int i = 1;i <= k;i++){
				b[i] = read();
			}
			sort(a + 1,a + k + 1);
			sort(b + 1,b + k + 1);
			clear();
			for (int i = 1;i <= k;i++){
				q.push({i,1,a[i] + b[1]});
			}
			for (int i = 1;i <= k;i++){
				node tmp = q.top();
				q.pop();
				res[i] = tmp.val;
				q.push({tmp.id_a,tmp.id_b + 1,a[tmp.id_a] + b[tmp.id_b + 1]});
			}
			for (int i = 1;i <= k;i++){
				a[i] = res[i];
			}
		}
		for (int i = 1;i <= k - 1;i++){
			printf("%lld ",res[i]);
		}
		printf("%lld\n",res[k]);
	}
	return 0;
}
```

---

## 作者：TLE_AK (赞：1)

### 前言
看了眼题解，发现没有手写堆的代码，于是便补一个手写堆的吧（
## 思路
很明显可以看出是 [P1631 序列合并](https://www.luogu.com.cn/problem/P1631) 的加强版（没做过建议先做此题）。

首先对于有序数列 $A$ 与 $B$,第一个答案一定为 $A_1 + B_1$ 而第二个答案一定为 $\min(A_2 + B_1,A_1 + B_2)$，若 $A_2 + B_1 > A_1 + B_2$，则第三个答案为 $\min(A_2 + B_2,A_3 + B_1,A_1 + B_2)$ 也就是说，我们每一次可以从堆中取出最小值，将这个值所代表的的 $i,j$ 各自加 $1$ 插入堆中就行了。	

对于 $k$ 个序列，可以看成 $k - 1$ 列的结果加上这一列，所以每两列往一个方向遍历就行了（因为之前的结果已被固定了）。

## 代码
```
#include<bits/stdc++.h>


using namespace std;

namespace acac
{
	struct node
	{
		int v,w,i,j;//分别表值，位置，对应的i,j
	}sreap[800];
	int cnt;
	int A[760],B[760],C[760],bj[760][760];
	void up(int now) //ins更新堆
	{
		while(now>1)
		{
			int f=(now>>1);
			if(sreap[now].v<sreap[f].v)
			{
				swap(sreap[now].v,sreap[f].v);
				swap(sreap[now].w,sreap[f].w);
				swap(sreap[now].i,sreap[f].i);
				swap(sreap[now].j,sreap[f].j);
				now>>=1;
			}
			else break;
		}
	} 
	void down(int now)//del更新堆
	{
		while((now<<1)<=cnt)
		{
			int tmp;
			if((now<<1)==cnt)tmp=(now<<1);
			else if(sreap[(now<<1)].v<sreap[(now<<1)+1].v)tmp=(now<<1);
			else tmp=(now<<1)+1;
			if(sreap[now].v>sreap[tmp].v)
			{
				swap(sreap[now].v,sreap[tmp].v);
				swap(sreap[now].w,sreap[tmp].w);
				swap(sreap[now].i,sreap[tmp].i);
				swap(sreap[now].j,sreap[tmp].j);
				now=tmp;
			}
			else break;
		}
	}
	void ins(int num,int i,int j)//插入
	{
		cnt++;
		sreap[cnt].v=num;
		sreap[cnt].i=i;
		sreap[cnt].j=j;
		sreap[cnt].w=cnt;
		up(cnt);
	}
	void del()//删除
	{
		swap(sreap[1].v,sreap[cnt].v);
		swap(sreap[1].w,sreap[cnt].w);
		swap(sreap[1].i,sreap[cnt].i);
		swap(sreap[1].j,sreap[cnt].j);
		cnt--;
		if(!cnt)return ;
		down(1); 
	}
	int main()
	{
		int k;
		while(scanf("%d",&k)!=EOF)//多测
		{
			
			
			for(int i=1;i<=k;i++)
			{
				scanf("%lld",&A[i]);
			}
			sort(A+1,A+1+k);//输入时不有序
			//cout<<"A";
			for(int i=1;i<=k-1;i++)
			{
				for(int j=1;j<=k;j++)
				{
					scanf("%lld",&B[j]);
				}
				sort(B+1,B+1+k);//同上
				cnt=0;
				memset(sreap,0,sizeof(sreap));
				memset(bj,0,sizeof(bj));//重置堆
				ins(A[1]+B[1],1,1);
				
				bj[1][1]=1;
				for(int j=1;j<=k;j++)
				{
					
					C[j]=sreap[1].v;
              //取出元素
					int nx=sreap[1].i,ny=sreap[1].j;
					
					if(!bj[nx+1][ny])
					{
						ins(A[nx+1]+B[ny],nx+1,ny);
						bj[nx+1][ny]=1;
					}
					if(!bj[nx][ny+1])
					{
						ins(A[nx]+B[ny+1],nx,ny+1);
						bj[nx][ny+1]=1;
					}
					//左右加堆
			/*		for(int j=1;j<=cnt;j++)
					{
						cout<<j<<" "<<sreap[j].v<<" "<<sreap[j].i<<" "<<sreap[j].j<<"\n";
					}
					cout<<'\n';*/
              //测试代码
					del(); 
				
				}
				for(int j=1;j<=k;j++)
				{
					A[j]=C[j];
				}//结果放到A中（保持有序）
			
			} 
			for(int i=1;i<k;i++)
			{
				cout<<C[i]<<" ";
			}
			cout<<C[k]<<'\n';//注意输出
		}
		
		return 0;
	}
}

int main()
{
	acac::main();
	return 0;
}

```

---

## 作者：Happy_mouse (赞：0)

# [UVA11997 K Smallest Sums](https://www.luogu.com.cn/problem/UVA11997) 题解
[AC 证明](https://www.luogu.com.cn/record/183953570)
## 更新日志

24/10/22：添加 AC 证明，修改代码及注释。

## 题目分析


拿之前的前 $K$ 小 $a_1,a_2,\dots a_n$，和下一行的 $K$ 个数 $b_1,b_2,\dots b_n$ 组合出 $K^2$ 个数，取前 $K$ 小即为直到此行的前 $K$ 小。

***

**正确性证明（反证）：**

假设之前的第 $K+1$ 小与下一行的一个数 $b_i$ 组成了当前的前 $K$ 小，则 $b_i$ 与之间的前 $K$ 小的和皆小于这个和，所以这个和至少是当前第 $K+1$ 小。矛盾，得证。

***

但是，一共 $K$ 行，每行两层循环，共 $O(K^3)$ ，数据范围根本过不了。

怎么优化呢？

我们发现，只要 $b_i+a_j$ 是前 $K$ 小，都有 $b_i+a_{j-1}$ 是前 $K$ 小（$j>0$）。

所以我们可以对于每一排：

### step1
建一个数对小根堆，第一个数存值，第二个数组存下标，依次将每一个 $b_i$ 与 $a_1$ 组合，放入优先队列，用 $f$ 数组存 $b_i$ 所匹配的 $a_j$，初始值为 $1$；

### step2
将队列中最小值取出（设 $b_i$ 与 $a_{f_i}$ 组合）后，将 $b_i$ 与 $a_{f_i+1}$ 组合，重新放入优先队列，将该最小值存入 $c$ 数组；

### step3

更新 $f_i$（匹配下一个，即 $f_i$ 加 $1$）；

### step4
回到 `step2`，重复 $K$ 次（即前 $K$ 小）；

### step5
清空优先队列，将 $c$ 赋值给 $a$，$c$ 数组可清可不清，反正下一次操作会覆盖掉。
***
P.S. 在开始时，由于 $a$ 数组还没有值，直接将第一排赋值给 $a$ 数组并排序（否则可能不按顺序）。

## 举个栗子

以样例第一组数据第一排到第二排为例（~~字儿真多~~）：
***
初态

进行 `step1`。

|数组\下标|$1$|$2$|$3$|
|:-:|:-:|:-:|:-:|
|$a$|$1$|$5$|$8$|
|$b$|$9$|$2$|$5$|
|$c$|$0$|$0$|$0$|
|$f$|$1$|$1$|$1$|
|优先队列|$3,2$|$6,3$|$10,1$|
***
第一次

取出堆顶 $(3,2)$，进行 `step2` 到 `step4`。

|数组\下标|$1$|$2$|$3$|
|:-:|:-:|:-:|:-:|
|$a$|$1$|$5$|$8$|
|$b$|$9$|$2$|$5$|
|$c$|$3$|$0$|$0$|
|$f$|$1$|$2$|$1$|
|优先队列|$6,3$|$7,2$|$10,1$|
***
第二次

取出堆顶 $(6,3)$，进行 `step2` 到 `step4`。

|数组\下标|$1$|$2$|$3$|
|:-:|:-:|:-:|:-:|
|$a$|$1$|$5$|$8$|
|$b$|$9$|$2$|$5$|
|$c$|$3$|$6$|$0$|
|$f$|$1$|$2$|$2$|
|优先队列|$7,2$|$10,1$|$10,3$|
***
第三次

取出堆顶 $(7,2)$，进行 `step2` 到 `step4`。

|数组\下标|$1$|$2$|$3$|
|:-:|:-:|:-:|:-:|
|$a$|$1$|$5$|$8$|
|$b$|$9$|$2$|$5$|
|$c$|$3$|$6$|$7$|
|$f$|$1$|$3$|$2$|
|优先队列|$10,1$|$10,2$|$10,3$|
***
末态

进行 `step5`。

|数组\下标|$1$|$2$|$3$|
|:-:|:-:|:-:|:-:|
|$a$|$3$|$6$|$7$|
|$b$|$9$|$2$|$5$|
|$c$|$0$|$0$|$0$|
|$f$|$1$|$3$|$2$|
|优先队列|\\|\\|\\|
## 代码
```cpp
//码风不好，不太喜欢写函数，循环老是一层一层套，见谅
	
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[755],b[755],c[755],f[755];
//数组与上文定义相同
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >q;//建堆，两个参数，以第一个为标准排序
signed main(){
	int n;
	while(scanf("%lld",&n)!=EOF){
		//读入第一排
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		sort(a+1,a+n+1);//排序
		//从第二排开始操作
		for(int j=2;j<=n;j++){
			//读入第 j 排
			for(int i=1;i<=n;i++) scanf("%lld",&b[i]),f[i]=1,q.push(pair<int,int>(a[1]+b[i],i));//每次将当前一排，与之前最小情况加起来放入堆
			for(int i=1;i<=n;i++){
				c[i]=q.top().first;//取当前最小情况并存储
				f[q.top().second]++;//组合大一点的情况
				q.push(pair<int,int>(a[f[q.top().second]]+b[q.top().second],q.top().second));//放入新组合
				q.pop();//删除最小
			}
			//存最小情况
			for(int i=1;i<=n;i++) a[i]=c[i];
			//清空
			while(!q.empty()) q.pop();
		}
		//输出，温馨小提示：这题不吃行末空格！！！
		for(int i=1;i<n;i++) printf("%lld ",a[i]);
        printf("%lld\n",a[n]);
	}
	return 0;
}
```

---

## 作者：Swirl (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA11997)

# 思路简述

首先，如果将问题弱化，将 $k\times k$ 的矩阵转化为 $a$ 和 $b$ 两个数组，则就转化成了 [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)。

这里我就不写 P1631 的题解了，因为跟本题也差不了多少。

**进入正题：**

本题是要求前 $k$ 小的值，比较容易想到堆。

在这里我懒，懒得写手写堆，我使用了 C++ 的系统数据结构：`priority_queue`。

**细化思路：**

不难想到，我们可以一行一行地更新答案，这样问题就近似成了 P1631。

设原矩阵为：

$$
\begin{bmatrix}
A_{1,1},A_{1,2},\dots,A_{1,k}\\
A_{2,1},A_{2,3},\dots,A_{2,k}\\
\dots\\
A_{k,1},A_{k,2},\dots,A_{k,k}
\end{bmatrix}
$$

假设堆里初始有 $A_{1,1},A_{1,2},\dots,A_{1,k}$ 这 $k$ 个元素。

我们只需要依次更新堆，每一次再拿前 $t$ 次更新得到的答案 $ans$ 数组与 $A_{t+1}$ 数组进行更新即可。

不过在此之前需要将 $A_1,A_2,\dots,A_k$ 数组进行排序。

**思路部分完结**。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0)
// #pragma GCC optimize(2)
#define int long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define il inline
using namespace std;

int n;
struct Node {
    int NumA, NumB, Val;
    friend bool operator<(Node a, Node b) { 
		return a.Val > b.Val; 
	}
};

priority_queue<Node> pq;

int a[755][755];
int b[755];
int ans[755];

signed main() {
    ios;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
            	cin >> a[i][j];
			}
        }
        for (int s = 2; s <= n; s++) {
            while (pq.size())
                pq.pop();
            sort(a[s - 1] + 1, a[s - 1] + n + 1);
            sort(a[s] + 1, a[s] + n + 1);
            for (int i = 1; i <= n; i++) {
                pq.push({i, 1, a[s - 1][i] + a[s][1]});
            }
            for (int i = 1; i <= n; i++) {
                Node tmp = pq.top();
                pq.pop();
                ans[i] = tmp.Val;
                pq.push({tmp.NumA, tmp.NumB + 1, a[s - 1][tmp.NumA] + a[s][tmp.NumB + 1]});
            }
            for (int i = 1; i <= n; i++) {
                a[s][i] = ans[i];
            }
        }
        for (int i = 1; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << ans[n] << endl;
    }
    return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

多组数据。每组数据给出一个 $k\times k$ 的矩阵 $a_{i,j}$。

你需要对于每一行，选出一个数，显然有 $k^{k}$ 种方案。

你需要输出和最小的前 $k$ 组方案。

$1 \leq k \leq 750$，注意本题评测时不忽略行末多余空格。

## 思路

套路地，我们考虑对于一个长度为 $n$ 的序列 $a$ 和一个序列 $b$，分别从中选出一个数，求出和的前 $n$ 小。

首先如果我们需要找到最小的一个解，则可以对 $a,b$ 从小到大排序后输出 $a_1+b_1$。

然后考虑我们取出一个 $a_1+b_1$ 之后，第 $2$ 大可能是什么呢？可能是 $a_{2}+b_1$ 或 $a_1+b_2$。但 $a_{2}+b_{2}$ 之后就有多种可能（$a_{2}+b_3,a_3+b_1,a_3+b_2$ 等等）。

我们可以换一个思路。钦定我们固定 $a_i$ 选 $b_j$，则找到 $a_i+b_j$ 后就可以转移到 $a_i+b_{j+1}$。所以我们可以将 $a_i+b_1$ 插入一个堆中，每次直接堆顶转移即可。

我们称这样的操作为合并。

对于本题，我们只需要一行一行合并。时间复杂度 $O(Tk^2\log k)$ 可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 755;
int k,a[N][N],s[N],t[N],bk[N];
typedef pair<int,int> pii;

struct ytxyakioi{
    bool operator()(const pii &x, const pii &y){
        return (s[x.first] + t[x.second]) > (s[y.first] + t[y.second]);
    }
};

void merge(){
    sort(s+1, s+k+1);sort(t+1, t+k+1);
    priority_queue<pii,vector<pii>,ytxyakioi> q;
    for(int i=1;i<=k;i++) q.push({i,1ll});
    for(int i=1;i<=k;i++){
        auto z = q.top();
        q.pop();
        q.push({z.first, z.second + 1});
        bk[i] = s[z.first] + t[z.second];
    }
}

void solve(){
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++) cin>>a[i][j];
    }
    for(int i=1;i<=k;i++) s[i]=a[1][i];
    for(int i=1;i<=k;i++) t[i]=a[2][i];
    merge();
    for(int i=3;i<=k;i++){
        for(int j=1;j<=k;j++) s[j] = bk[j];
        for(int j=1;j<=k;j++) t[j] = a[i][j];
        merge();
    }
    for(int i=1;i<k;i++) cout<<bk[i]<<' ';
    cout<<bk[k]<<'\n';
    return;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    while(cin>>k) solve();
    return 0;
}
```

---

## 作者：Eleveslaine (赞：0)

先将每一行非递增排序。  
考虑合并两行，将 $a_i,b_i(0\le i<n)$ 前 $n$ 小组成一个新有序数列 $c_i$。  
这就是 [P1631](https://www.luogu.com.cn/problem/P1631)，用堆维护即可。具体地，若当前最小值为 $a_i+b_j$，则可能的次小值为 $a_{i+1}+b_j,a_i+b_{j+1}$。这样由一对数 $(i,j)$ 可以推到 $(i+1,j)$ 和 $(i,j+1)$。特别地，需要去重（例如 $(1,1)$ 可能会被扩展两次），方法是仅在 $j=0$ 时扩展 $(i+1,j)$。初始时把 $a_0+b_0$ 入堆，每次出堆一个数，共出堆 $n$ 次即可。

这样扩展的大致过程图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/6qylgev7.png)

于是我们得到合并两行的代码实现：

```cpp
struct thair
{
    int i,j,sum;
    inline bool operator <(const thair &x) const
    {
        return sum>x.sum; // 大根堆变小根堆
    }
};
priority_queue <thair> q;

vector <int> combine(const vector <int> &a,const vector <int> &b)
{
    vector <int> ans;
    while(!q.empty()) q.pop();
    q.push({0,0,a[0]+b[0]});
    for(int t=0;t<n;++t)
    {
        thair u=q.top(); q.pop();
        ans.push_back(u.sum);
        if(u.j==0) // 去重
            q.push({u.i+1,u.j,a[u.i+1]+b[u.j]});
        q.push({u.i,u.j+1,a[u.i]+b[u.j+1]});
    }
    return ans;
}
```

这样合并 $(n-1)$ 次，最后剩下的那一行就是答案。  
输出时注意过滤行末空格。

---

## 作者：Comentropy (赞：0)

### 前言
这道题有简化版，要是做不出来这道题可以先去思考这道题：[P1631 序列合并](https://www.luogu.com.cn/problem/P1631)。相当于将 $n$ 维变成了二维。

## 分析
对于这道题，可以参考简化版的思路，可以先缩小（简化）使得这道题变得清晰。

简化：对于升序排列过的两个序列 $a_1$，$a_2$，$\ldots$，$a_n$ 和 $b_1$，$b_2$，$\ldots$，$b_n$，取两个序列中的元素相加，求前 $n$ 小的和。

对于上述序列，很明显有 $a_1+b_1 \leq a_1+b_i$ 和 $a_1+b_1\leq a_i+b_1$ 。也就有下列大小关系：

$a_1+b_1 \leq a_1+b_2 \leq \ldots \leq a_1+b_n $。

$a_2+b_1 \leq a_2+b_2 \leq \ldots \leq a_2+b_n $。

$\ldots$。

$a_n+b_1 \leq a_n+b_2 \leq \ldots \leq a_n+b_n $。

即 $a_i + b_j \leq a_i+b_k (j\leq k)$，并且有 $a_i+ b_j \leq a_k+b_j(i\leq k)$。则可以根据贪心思想，一直将当前最小值对应的数 $b_j$ 的下一个和当前对应的 $a_i$ 相加，直到该数，即 $a_i+b_{j+1}$ 不为最小值了即可。这种方法需要使用 **堆或优先队列** 实现，因为这样迭代插进去的和具有后效性。

考虑方式如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/38gfz50j.png)

这么简化的原因很简单，每次只需要找到局部最优解，进行 $n-1$ 次迭代就可以得到答案。也就是，将每次解决问题得到的最小和赋值到 $a$，在对下一个 $b$ 进行操作，时间复杂度 $\Theta(k^2 \log k)$，复杂度瓶颈在于排序和优先队列维护。每次迭代常数约为 $3$，复杂度 $\Theta(k\log k)$。

## 注意
这道题需要删掉行末空格，否则会 ```presentation error``` 导致 ```WA```。

## Code 

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int N=1050;
typedef pair<int,int> PII;
priority_queue< PII, vector<PII>, greater<PII> > q;
priority_queue< int, vector<int>, greater<int> > ans;
int a[N],b[N],cnt[N];
int n;
void solve(){
    for(int i=1;i<=n;i++){
        q.push(make_pair(a[i]+b[1],i));
        cnt[i]=1;
    }
    int i=0;
    while(i<n){
        int val=q.top().first,j=q.top().second;
        ans.push(val);  // 保存这些最小和。
        q.pop();
        q.push(make_pair(a[j]+b[++cnt[j]],j));  // 只需要观察当前最小值对应的下一个数组中的数。
        i++;
    }
    for(int i=1;i<=n;i++){
        a[i]=ans.top(); // 迭代。
        ans.pop();
    }
    q={};
    ans={};
    return ;
}
int main(){
    while(~scanf("%d",&n)){
        q={};
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+1+n);    // 这种处理一定要注意单调。
        for(int i=2;i<=n;i++){
            for(int j=1;j<=n;j++)
                scanf("%d",&b[j]);
            sort(b+1,b+1+n);
            solve();    
        }
        for(int i=1;i<n;i++) 
            printf("%d ",a[i]); // 每次得到的最小答案都在a中。
        printf("%d\n",a[n]);
    }
    return 0;
}
// P1631 -> UVA11997;
// 根据 P1631的思路即可，每次只需更新a数组即可
// 常数约为 3 ， 复杂度 k^2 log k
```


---

## 作者：Coros_Trusds (赞：0)

# 题目大意

有一个 $n \times n$ 的矩阵，在每行任取一个位置，把这些位置的元素相加的到一个值，求前 $n$ 小的值。

# 题目分析

对每行升序排列。

抽象问题，先来考虑前两行 $a,b$。因为 $a_1\le a_2\le a_3\le\cdots\le a_n$ 且 $b_1\le b_2\le\cdots\le b_n$，所以 $a_1+b_1\le a_2+b_1\le a_3+b_1\le \cdots\le a_n+b_1$。

亦即：$a_1+b_j\le a_2+b_j\le \cdots\le a_n+b_j$。

所以我们先把 $a_1+b_1, a_2+b_1, a_3+b_1, \cdots, a_n+b_1$ 存在堆中。然后每次取出最小值记为 $a_i+b_j$，然后压入 $a_{i}+b_{j+1}$，如此循环 $n$ 次即可更新出前 $n$ 小。

# 代码

这是单次询问的代码。

```cpp
//2022/5/3
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <queue>
#include <utility>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : (-x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if (x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
typedef std::pair<int,int> PII;

const int N = 755;
int a[N],b[N],id[N];
int n;
std::priority_queue<PII,std::vector<PII>,std::greater<PII> >q;
inline void merge() {
	while (!q.empty()) q.pop();
	for (register int i = 1;i <= n; ++ i) {
		id[i] = 1;
		q.push(std::make_pair(a[i] + b[1],i));
	}
	for (register int i = 1;i <= n; ++ i) {
		PII u = q.top();q.pop();
		a[i] = u.first;
		if (id[u.second] < n) {
			q.push(std::make_pair(u.first - b[id[u.second]] + b[id[u.second] + 1],u.second));
			id[u.second] ++;
		}
	}
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	scanf("%d",&n);
	for (register int i = 1;i <= n; ++ i) scanf("%d",a + i);
	std::sort(a + 1,a + n + 1);
	for (register int i = 2;i <= n; ++ i) {
		for (register int j = 1;j <= n; ++ j) {
			b[j] = read();
		}
		std::sort(b + 1,b + n + 1);
		merge();
	}
	for (register int i = 1;i <= n; ++ i) printf("%d ",a[i]);
	puts("");
	
	return 0;
}
```

---

## 作者：Ouaoan (赞：0)

题目：[K Smallest Sums](https://www.luogu.org/problemnew/show/UVA11997)

---

[更好阅读体验？](https://blog.csdn.net/rabbit_ZAR/article/details/78767823)

---

思路：

如果假设在前i行中，已经求出了k个最小的和，那么，也可以求出加上第i+1行数后的k个最小值（及第i+1行中的结果只和前i行的结果有关）。

所以，如果把前第i行得到的k个数看成一行，这题可以拆分成k-1个小问题，即：在两行数中找出k个最小的值。

然后，对于其中的每一个小问题，可以运用归并排序的思想，只是要用到优先队列。每一次将和最小的弹出，把下面一行移动一个就可以了。

---


代码：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <cstring>
#include <map>
using namespace std;
 
struct A{
	int x,y;
	A(){}
	A(int xx,int yy){
		x=xx,y=yy;
	}
	bool operator < (const A& other) const{
		if(x>other.x||(x==other.x&&y>other.y)) return true;
		return false;
	}
};
 
int n;
int a[1000][1000];
int f[1000];
 
void Do(int a[]){
	priority_queue<A> que;
	for(int i=1;i<=n;i++){
		que.push(A(f[i]+a[1],1));
	}
	for(int i=1;i<=n;i++){
		A x=que.top();
		que.pop();
		f[i]=x.x;
		int y=x.y;
		if(y+1<=n){
			A z=A(f[i]-a[y]+a[y+1],y+1);
			que.push(z);
		}
	}
}
 
int main() {
	
	while(~scanf("%d",&n)){
		
		memset(a,0,sizeof(a));
		memset(f,0,sizeof(f));
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&a[i][j]);
			}
		}
		
		for(int i=1;i<=n;i++){
			sort(a[i]+1,a[i]+n+1);
		}
		for(int i=1;i<=n;i++){
			f[i]=a[1][i];
		}
		for(int k=2;k<=n;k++){
			Do(a[k]);
		}
		
		for(int i=1;i<n;i++){
			printf("%d ",f[i]);
		}
		printf("%d\n",f[n]);
	}
	
	return 0;
}
```

---

