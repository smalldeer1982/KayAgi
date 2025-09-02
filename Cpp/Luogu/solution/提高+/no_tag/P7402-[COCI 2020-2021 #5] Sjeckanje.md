# [COCI 2020/2021 #5] Sjeckanje

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$。接着进行 $q$ 次修改，每次给定整数 $l,r,x$。表示将 $[l,r]$ 内的所有元素加上 $x$。

规定一个区间的权值为**该区间的最大值减去最小值**。现要将 $a$ 数组分为若干个连续的区间。规定一个已被分为若干个区间的数组的权值为**该数组所有区间的权值之和**。求数组 $a$ 在**每次修改**后的所有分法中，数组权值的最大值。

## 说明/提示

#### 样例 1 解释

|修改次数|本次修改后的数组|其中一种最优分法|数组权值|
| :----------: | :----------: | :----------: | :----------: |
|$1$|$[2,3,3,4]$|$[2,3,3,4]$|$2$|
|$2$|$[4,3,3,4]$|$[4,3],[3,4]$|$2$|
|$3$|$[4,4,4,4]$|$[4,4,4,4]$|$0$|

#### 数据规模与约定

**本题采用捆绑测试**。

|Subtask|分值|数据范围及约定|
| :----------: | :----------: | :----------: |
|$1$|$15$|$1 \le n,q \le 200$|
|$2$|$40$|$1 \le n,q \le 3000$|
|$3$|$55$|无|

对于 $100\%$ 的数据，$1 \le n,q \le 2 \times 10^5$，$-10^8 \le a_i,x \le 10^8$，$1 \le l \le r \le n$。

#### 说明

**本题分值按 COCI 原题设置，满分 $110$。**

**题目译自 [COCI2020-2021](https://hsin.hr/coci/) [CONTEST #5](https://hsin.hr/coci/contest5_tasks.pdf)  _T5 Sjeckanje_。**

## 样例 #1

### 输入

```
4 3
1 2 3 4
1 2 1
1 1 2
2 3 1```

### 输出

```
2
2
0```

## 样例 #2

### 输入

```
4 3
2 0 2 1
4 4 1
2 2 3
1 3 2```

### 输出

```
2
1
3```

# 题解

## 作者：lupengheyyds (赞：20)

[原题连接](https://www.luogu.com.cn/problem/P7402)

## 背景
其他的题解对这道题的做法已经有了大概的讲解，但是对于正解的思路与细节处理说得云里雾里，所以说我将对正解的思路及具体细节作诠释，不再赘述部分分数的解法。
## 分析

### 初步转化
看见区间加减，便不由得想到差分，于是建立一个差分数组 $d[i]=a[i]-a[i-1]$ ，这样每次就只需要在两处单点修改。

接着分析，一个区间真正能作出贡献的只有最大值与最小值，也就是说，当我们已经得到一段的极大值与极小值的时候，便应该直接划分，而非继续将其他的数纳入这个区间，最终使得整个划分出来的区间**单调不下降或单调不上升**。转化为数学语言就是：对于所有划分的区间 $[l,r]$ ，满足 $a[l]\le a[l+1]\le \cdots\le [r]$ 或者 $a[l]\ge a[l+1]\ge \cdots\ge a[r]$ ，接着将其转化为上文的**差分思路**也就是要满足 $d[l+1],d[l+2],\cdots,d[r]$同号（根据定义，$0$ 应该与任何数同号）。这样的话每个区间最后的值就应该是 $\sum\limits_{i=l+1}^r\left|d[i]\right|$ 。根据这个式子，我们可以发现，因为题目要求最大值，我们就应该尽量少的剔除差分值，非要减也要减去绝对值较小的差分值。

根据前面的分析，现在就需要我们单点修改，区间查询。那不就是线段树吗？于是我们可以尝试**从线段树的角度**考虑如何合并两个区间。

### 线段树分析

假设有这样一个区间（下面表示原数组，上面表示差分数组）：

![](https://s1.ax1x.com/2023/07/24/pCLICQI.png)

如果在差分线段树上的话，就会被分成这样两个区间：

![](https://s1.ax1x.com/2023/07/24/pCLIPyt.png)

那么对应反映在原数组上就是这样：

![](https://s1.ax1x.com/2023/07/24/pCLIAw8.png)

如果两个差分区间符合上述的“初步转换”中的条件的话就可以直接累加，合并成一个区间（过于简单，没有画出）。

但如果两个差分区间不符合条件也就是需要必须分开的时候，就会有一下两种情况：

- 分给左边

![](https://s1.ax1x.com/2023/07/24/pCLo1gA.png)

- 分给右边

![](https://s1.ax1x.com/2023/07/24/pCLIkef.png)

这是我们就会发现，对于差分区间，其左右两边的值可能选或不选，那么在处理线段树的时候，我们就应该对应存上左右两端选或不选的情况。

最后再输出整个区间，由于整个区间的左右两端选了的答案一定比不选优（多考虑了两个值），所以直接输出两端都选的情况就行，根本不用作比较。

对了，记得开 $\text{long long}$

如果还没有理解，就可以看代码。

## 代码

```
#include<bits/stdc++.h>
#define int long long//记得开long long 
using namespace std;
const int szl=8e5+5;
int sgt[szl][2][2];//第一维是线段树节点编号，第二位表示左端点状态，第三位表示由端点状态，0表示不选，1表示选 
int a[szl],d[szl],root=1;
void Updata(int p,int mid){
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			if(d[mid]*d[mid+1]>=0)sgt[p][i][j]=sgt[p<<1][i][1]+sgt[p<<1|1][1][j];//可以合并成一个区间 
			else sgt[p][i][j]=max(sgt[p<<1][i][0]+sgt[p<<1|1][1][j],sgt[p<<1][i][1]+sgt[p<<1|1][0][j]); //不能合并成一个区间 
	return;
}
void Add(int p,int l,int r,int pos){
	if(l==r){
		sgt[p][1][1]=abs(d[l]);
		return;
	}
	int mid=l+r>>1;
	if(pos<=mid)Add(p<<1,l,mid,pos);
	else Add(p<<1|1,mid+1,r,pos);
	Updata(p,mid);
	return;
}

signed main(){
	int n,q;cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		d[i]=a[i]-a[i-1];
		if(i==1)continue;
		Add(root,2,n,i);
		//也可以写在外面O(N)建树，但这样写慢却简单，少些一个函数，反正不会超时，减少错误率 
		//注意：差分数组从2到n的区间才有效 。 
	} 
	while(q--){
		int l,r,x;cin>>l>>r>>x;
		if(l>1){
			d[l]+=x;
			Add(root,2,n,l);
		}
		if(r<n){
			d[r+1]-=x;
			Add(root,2,n,r+1);
		}
		cout<<sgt[root][1][1]<<endl;//最后直接输出，不用比较左右端点不选的情况 
	}
	return 0;
}
```




---

## 作者：LittleYang0531 (赞：9)

### 题目描述:

给定一个长度为 $n$ 的序列 $a_i$。我们定义一个序列的划分是将一个序列划分为若干个区间，这 些区间依次连接起来就可以还原整个序列。例如：区间 [1 3]\[1 4][3 6] 就是序列 1 3 1 4 3 6 的一个 合法划分。我们定义一个区间的权值为**区间内的最大值减去区间内的最小值。定义在这个区间划分下，序列的权值为各个区间的权值的和。**

例如：在区间划分 [1 3]\[1 4][3 6] 的情况下，序列的权值为 $(3-1)+(4-1)+(6-3)=9$。 

你的任务是：求出序列 $a_i$ 权值最大的区间划分所对应的序列权值。 

需要支持 $q$ 次修改操作，修改操作形式如下:将下标区间 [ $l,r$ ] 中的 $a_i$ 加上 $x$ 。你需要在每一次修改操作之后，输出新的序列的权值最大的区间划分所对应的权值。

### 输入描述:

输入的第一行包括两个整数 $n$ 和 $q(1\leq n,q\leq 2\times10^5)$，分别表示序列的长度已经更新操作的次数。 第二行包含 $n$ 个整数 $a_i(-10^8\leq a_i\leq 10^8)$，表示序列的初值 $a_i$。 接下来的 $q$ 行，每行包括三个整数 $l,r(1\leq l\leq r\leq n)$ 和 $x(-10^8\leq x\leq 10^8)$，描述一个修改操作。

### 输出描述:

输出 $q$ 行，每行一个整数，表示每一次更新操作之后序列最大的可能的区间划分的权值。

### 分析:

#### 30pts:

令 $dp_i$ 为对于前 $i$ 个数据的区间能取到的最大权值，则 $dp_{i+j}=dp_i+a_{max}-a_{min}$。

而对于区间修改，for循环一个一个地加就行了，时间复杂度就只有 $O(qn)$。

总时间复杂度 $O(qn^2)$。

#### 60pts:	

最短路优化，将非单调区间拆分成若干个单调区间，使得最终答案一定不劣。

令 $d_i$ 为 $a_i$ 与 $a_{i-1}$ 的差值，则 $d_i=a_i-a_{i-1}\ \&\ d_1=0$。

若对于区间 $[l,r]$，使得 $d_{l+1},d_{l+2},...,d_r$ 的符号一定是一样的，则当前区间 $[l,r]$ 所能提供的对答案的贡献为 $\sum_{l+1}^r|d_i|$。

时间复杂度为 $O(qn)$。

#### 100pts:

引入线段树进行维护，记录线段树节点 $T[x][0/1][0/1]$，表示线段树节点为$x$所代表的区间能取到的区间最值。

后面的两个 0/1 分别表示左端点的 $d_i$ 取还是不取，以及右端点 $d_i$ 取还是不取。

修改时只需要修改所需要修改的区间的左端点以及右端点然后更新到线段树上即可。

时间复杂度为 $O(q\log_2n)$。

### 代码:

```C++
#include<bits/stdc++.h>
#define van long long
#define N 1000100
using namespace std;
van n,a[N],q,d[N];
van t[N*4][2][2];//线段树
void update(van p,van num)
{
	for (int i=0;i<2;i++) for (int j=0;j<2;j++)
	{
		t[p][i][j]=-1e18;
		for (int k=0;k<2;k++) for (int l=0;l<2;l++) if (l!=1||k!=1||d[num]*d[num+1]>=0) t[p][i][j]=max(t[p][i][j],t[p*2][i][k]+t[p*2+1][l][j]);
	}
}//更新线段树p节点上的值
void add(van p,van l,van r,van where)
{
	if (l==r)
	{
//		cout<<"add "<<l<<" "<<d[l]<<endl;
		t[p][1][1]=abs(d[l]);
		return;
	}
	van mid=l+r>>1;
	if (where<=mid) add(p*2,l,mid,where);
	if (where>mid) add(p*2+1,mid+1,r,where);
	update(p,mid);
}//更新线段树(单点修改)
van query(van x)
{
	return max(t[x][0][0],max(t[x][0][1],max(t[x][1][0],t[x][1][1])));
}//查询线段树上x节点的最大值
int main()
{
//	ifstream ywhin("sjeckanje.in");
//	ofstream ywhout("sjeckanje.out");
	#define ywhin cin
	#define ywhout cout
	ywhin>>n>>q;
	for (int i=1;i<=n;i++) ywhin>>a[i];
	for (int i=1;i<=n;i++) d[i]=i==1?0:a[i]-a[i-1],add(1,1,n,i);//差分并插入线段树上
	while (q--)
	{
		van l,r,k;
		ywhin>>l>>r>>k;
		if (l!=1)
		{
			d[l]+=k;
			add(1,1,n,l);
		}//添加左端点
		if (r!=n)
		{
			d[r+1]-=k;
			add(1,1,n,r+1);
		}//添加右端点
		cout<<query(1)<<endl;//查询[1,n]的区间最值
	}
	return 0;
}
```


---

## 作者：肖翔 (赞：6)

给一个无脑矩乘做法。

要求掌握“线段树维护矩阵”的前置知识。（动态 DP 弱化版）

参考 2022WC 的讲解，或可以看这篇 [blog](https://www.luogu.com.cn/blog/George-Plover/qian-tan-xian-xing-lan-biao-ji-wei-hu-ji-qiao-yi-xian-duan-shu-wei-li)



------------


（似乎朴素 DP 式子也和别人不一样。）

答案可以看做若干组区间中最大值与最小值的差。

这启示我们只要划分好了区间，就不需要关注最大值或最小值的位置，只要知道值。

首先考虑朴素 DP，记 $dp(i,0/1/2) $ 表示前 $ i $ 个数中，若干组最大值与最小两两匹配后，不剩任何值/剩一个最大值/剩一个最小值后得到的数值。

可以看做 $[1,i]$ 的区间断开成了 $ [1,j] $, $ [j+1,i] $ 两个区间，我们知道了 $ [1,j] $ 的匹配完后的答案，并知道了  $ [j+1,i] $ 的某个最值。

这就是上面“启示”的意义：我们不再需要记录和枚举 $ j $，可以快速转移并压掉一维。

于是，我们有

$$
dp(i,1)=\max\{dp(i-1,1),dp(i-1,0)+a_{i}\}
$$

$$
dp(i,2)=\max\{dp(i-1,2),dp(i-1,0)-a_{i}\}
$$

$$
dp(i,0)=\max\{dp(i-1,1)-a_{i },dp(i-1,2)+a_{i},dp(i-1,0)\}
$$

按照式子的定义去理解分析不难得出。

就是不选 $a_{i}$ 和选了 $a_{i}$ 的两种情况。

$dp(i,0)$ 在选了 $a_{i}$ 的基础上再分 $a_{i}$ 作最小值还是最大值。

于是每次修改完暴力跑 DP，可以得到 55 分代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
const int maxn=2e6+10;
int a[maxn];
int dp[maxn][3];
const int inf=pow(2,62);
inline void DP(){
	dp[0][1]=dp[0][2]=-inf;
	for(int i=1;i<=n;i++){
		dp[i][1]=max(dp[i-1][1],dp[i-1][0]+a[i]);
		dp[i][2]=max(dp[i-1][2],dp[i-1][0]-a[i]);
		dp[i][0]=max(max(dp[i-1][1]-a[i],dp[i-1][2]+a[i]),dp[i-1][0]);
	}
	return;
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	while(q--){
		int l,r,x;
		scanf("%lld%lld%lld",&l,&r,&x);
		for(int i=l;i<=r;i++)a[i]+=x;
		DP();
		printf("%lld\n",dp[n][0]);
	}
	return 0;
}
```



------------


考虑优化。

问题出在每次修改都要重新计算。

然而我们知道，肯定有很多是不必要的。

观察递推式的结构，发现他们都只与 $ i-1 $ 项有关。

有同学会想到滚掉一维，但这并不能实际优化时间复杂度。

对线性递推式，想到用矩阵转移，再结合有修改操作。

想到用线段树维护矩阵乘法的经典 trick。

（参考 2022WC 的讲解，或可以看这篇 [blog](https://www.luogu.com.cn/blog/George-Plover/qian-tan-xian-xing-lan-biao-ji-wei-hu-ji-qiao-yi-xian-duan-shu-wei-li)）

定义广义矩乘 $ (+,\max) $

用 $
 \begin{bmatrix}
   dp(i,0) & dp(i,1) & dp(i,2)
  \end{bmatrix}
$ 表示一个状态，则转移矩阵为：

$$
 \begin{bmatrix}
   0 & a_{i} & -a_{i} \\
   -a_{i} & 0 & -\infty \\
   a_{i} & -\infty & 0
  \end{bmatrix}
$$

顺便给出这题区间修改，整体加 $ k $ 的转移矩阵。（~~好人做到底~~）

但注意这个转移需要做的不是乘法，而是正常的矩阵加法。

$$
 \begin{bmatrix}
   0 & k & -k \\
   -k & 0 & -2k \\
   k & 2k & 0
  \end{bmatrix}
$$

可以暴力乘开矩阵或打表证明，经我个人检验都可行。

（考场上建议第二种，我也是考后才去乘开验证的。）

~~（因为 markdown 不好写所以证明不放了。）~~

然后就做完了。

还有注意开 long long，而且因为有时会有 inf 参与运算，代码实现时 inf 开太大会溢出导致答案错误，适量即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=pow(2,50);
const int maxn=4e5+10;
int a[maxn<<2],tag[maxn<<2];
struct Matrix {
	int a[3][3];
	Matrix(){
		memset(a,0,sizeof(a));
	}
	inline void build(){
		for(int i=0;i<3;i++)a[i][i]=1;
		return;
	}
};
Matrix operator*(Matrix x,Matrix y){
	Matrix z;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			z.a[i][j]=-inf;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
				z.a[i][j]=max(z.a[i][j],x.a[i][k]+y.a[k][j]);
	return z;
}
inline void change(Matrix& x,int a){
	x.a[0][1]+=a;x.a[0][2]-=a;
	x.a[1][0]-=a;x.a[2][0]+=a;
	x.a[2][1]+=2*a;x.a[1][2]-=2*a;
	return;
}
Matrix tr[maxn<<2];
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
inline void pushup(int x){
	tr[x]=tr[ls(x)]*tr[rs(x)];
	return;
}
inline void build(int x,int l,int r){
	if(l==r){
		change(tr[x],a[l]);
		tr[x].a[2][1]=tr[x].a[1][2]=-inf;
		return;
	}
	int mid=l+r>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	pushup(x);
	return;
}
inline void worktag(int x,int k){
	change(tr[x],k);
	tag[x]+=k;
	return;
}
inline void pushdown(int x){
	worktag(ls(x),tag[x]);
	worktag(rs(x),tag[x]);
	tag[x]=0;
	return;
}
inline void update(int x,int l,int r,int nl,int nr,int val){
	if(nl<=l&&r<=nr){
		worktag(x,val);
		return;
	}
	int mid=l+r>>1;pushdown(x);
	if(nl<=mid)update(ls(x),l,mid,nl,nr,val);
	if(mid<nr)update(rs(x),mid+1,r,nl,nr,val);
	pushup(x);
	return;
}
inline Matrix query(int x,int l,int r,int nl,int nr){
	if(nl<=l&&r<=nr){
		return tr[x];
	}
	int mid=l+r>>1;
	pushdown(x);
	if(nl<=mid&&mid<nr)return query(ls(x),l,mid,nl,nr)*query(rs(x),mid+1,r,nl,nr);
	else if(nl<=mid)return query(ls(x),l,mid,nl,nr);
	else return query(rs(x),mid+1,r,nl,nr);
}
int n,m;
inline int rd(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
signed main(){
	Matrix S;
	S.a[0][1]=S.a[0][2]=-inf;
	n=rd();m=rd();
	for(int i=1;i<=n;i++)a[i]=rd();
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int l,r,x;
		l=rd();r=rd();x=rd();
		update(1,1,n,l,r,x);
		Matrix tmp=S*query(1,1,n,1,n);
		printf("%lld\n",tmp.a[0][0]);
	}
	return 0;
}
```


---

## 作者：ln001 (赞：5)

## 题意
让[这道题](https://www.luogu.com.cn/problem/CF484D)支持区间加。

## 做法
从弱化版中得到性质，在最优的划分方案中，每个区间都是**单调**的。

在弱化版中，我们对前缀进行 dp 来计算答案，不可扩展。为了实现区间修改，改为对区间进行 dp。

---

不同寻常的，称 $0$ 与任何数都同号。

为了更好的支持区间加，首先进行一步转化。令差分数组为 $b$，区间 $[l, r]$ 单调当且仅当 $b_{l + 1}, b_{l + 2} \cdots b_r$ 均同号。

问题转化为，在序列 $b_2$ 到 $b_n$ 中，标记若干数，使得序列上的**极长被标记连续段**均同号，最大化每个**极长连续段的和的绝对值**的和。其中**未被标记的点**为**原题中**某个被划分出来的**区间的左端点**。

更简洁的，在序列 $b_2$ 到 $b_n$ 中，标记若干数，若相邻两数均被标记，需保证两数同号，最大化被标记的数的绝对值的和。

两个序列显然可以合并，同时又需要支持单点修改（差分后的区间修改），直接扔到线段树里，在节点上维护左端点和右端点不同的选择方案对应的答案。

[Code](https://vjudge.net/solution/56019973/0fXGs693KoWsuOq9xcWi)

---

## 作者：13402805827wuaiyang (赞：5)

提供一种（自认）较易理解的思路。

由题易得：最优方案中每一个区间都是单调的；合并两个单调区间时，所增加的总值固定为第二个区间最左端的值减去第一个区间最右端的值的绝对值，也就是说，合并时增加的值只与合并处的值之差有关，与其他信息无关。

因为所有操作都只与相邻的数之间的差有关，所以可以以差分数组来进行所有操作，并将区间修改变为单点修改。

根据上面的信息可得：合并时可以只需用到子区间的某种（或某几种）最值，转移时只需要判断两个区间是否可以合并，如果可以就加上合并处差值的绝对值即可。

注意两个区间原来最优的方案不一定能合并，所以我们还需要保留（尽可能）能合并的最优值，这个可以通过限制左端区间和右端区间递减还是递增实现。

最后注意排除单个元素组成既递增又递减的区间。（它本身合法，但会使由它得到的数据出现错误）

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,q,num[MAXN],cf[MAXN];
struct seg{
	int l,r;
	long long z[2][2];
	long long *operator [](const int x){
		return z[x];
	}
}tree[MAXN*4];
#define now tree[s]
#define lc tree[s<<1]
#define rc tree[s<<1|1]
void update(int s){
	int mid=(now.l+now.r)/2;
	for(register int i=0;i<=1;i++){
		for(register int j=0;j<=1;j++){
			now[i][j]=max(lc[i][0],lc[i][1])+max(rc[0][j],rc[1][j]);
			now[i][j]=max(now[i][j],lc[i][0]+rc[0][j]+(cf[mid+1]>=0)*cf[mid+1]);
			now[i][j]=max(now[i][j],lc[i][1]+rc[1][j]+(cf[mid+1]<=0)*(-cf[mid+1]));
		}
	}
}
void add(int s,int wz){
	if(now.l==now.r) return;
	int mid=(now.l+now.r)/2;
	if(wz<=mid) add(s<<1,wz);
	else add(s<<1|1,wz);
	update(s);
}
void build(int s,int l,int r){
	now.l=l,now.r=r;
	if(l==r){
		tree[s][0][1]=tree[s][1][0]=-0x3f3f3f3f3f3f3f3f;
		return;
	}
	int mid=(l+r)/2;
	build(s<<1,l,mid);
	build(s<<1|1,mid+1,r);
	update(s);
}
int lsl,lsr,lsk; 
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",&num[i]);
	for(int i=2;i<=n;i++) cf[i]=num[i]-num[i-1];
	build(1,1,n);
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&lsl,&lsr,&lsk);
		if(lsl!=1) cf[lsl]+=lsk,add(1,lsl);
		if(lsr!=n) cf[lsr+1]-=lsk,add(1,lsr+1);
		printf("%lld\n",max(max(tree[1][0][0],tree[1][0][1]),max(tree[1][1][0],tree[1][1][1])));
	}
	return 0;
}
```

---

## 作者：JackMerryYoung (赞：4)

# 前言

翻题单的时候突然发现忘记写这道题题解了。（不是

# 正文

纯暴力肯定不行，考虑优化。

我们发现一个性质：**最优划分一定能将原数组划分为若干个单调序列。**

于是我们就可以考虑一直分割。这样为什么不会裂开呢？

下面对一组样例进行解释：$[1, 3, 2, 4, 5, 7, 6]$

分割之后：$[1, 3] [2, 4, 5, 7] [6]$

则答案为 $2 + 5 + 0 = 7$.

我们发现，如果不是单调序列，那么有些部分的价值就被埋没了。

比如 $[1, 3, 2, 4, 5, 7]$, 如果你分成 $[1, 3, 2] [4, 5, 7]$, 那么显然 $2, 4$ 是单独可以创造价值的。

数学表示（~~随便瞎写的~~）：
$$
\forall 1 \le i < k < j \le N, s.t. \max_{x = i}^{k}{a_x} - \min_{x = i}^{k}{a_x} + \max_{x = k + 1}^{j}{a_x} - \min_{x = k + 1}^{j}{a_x} > \max_{x = i}^{j}{a_x} - \min_{x = i}^{j}{a_x}
$$
那么就知道策略了。我们使用差分。

令 $d_i = a_i - a_{i - 1}$, 若有区间 $[l, r]$, 使得 $d_l, d_{l + 1}, \cdots, d_{r - 1}, d_{r}$ 皆为同号（定义 $0$ 与任何实数同号），则这个序列一定单调。则它的贡献为：
$$
\sum_{i = l}^r{|d_i|}
$$
那么修改的时候只需维护差分数组 $d$ 即可。

然鹅发现复杂度是 $\mathcal{O}(QN)$, 还是过不了......

考虑线段树优化：设 $SegmentTree_{p, i_1, i_2} (i_1,i_2 \in S(0, 1))$ 表示编号为 $p$ 的节点所对应的区间 $[l, r]$ 的左右端点是否能取到时的 $\sum_{i = l}^r{|d_i|}$.

然后修改的时候只需要把左端点或者右端点的 $d_i$ 更新即可，复杂度 $\mathcal{O}(Q \log_2 N)$, 可以通过此题。

# 代码

半年之前的代码，有点丑。

~~你们最想要的..~~ 

Talk is$\color{white}\text{n't}$ cheap, $\color{white}\text{Don't}$ show me the code...

``` cpp
#include <bits/stdc++.h>
using namespace std;

int N, Q;
long long arr[200005];
long long seg[800005][2][2];
long long dis[200005];

void merge(int mid, int p);
void insert(int i, int now_l, int now_r, int p);
long long getans(int p);

int main()
{
	cin >> N >> Q;
	for(int i = 1; i <= N; ++ i)
		cin >> arr[i];
	
	for(int i = 1; i <= N; ++ i)
	{
		if(i != 1)
		{
			dis[i] = arr[i] - arr[i - 1];
			insert(i, 1, N, 1);
		}
	}
	
	for(int i = 1; i <= Q; ++ i)
	{
		int l, r, x;
		cin >> l >> r >> x;
		if(l != 1)
		{
			dis[l] += x;
			insert(l, 1, N, 1);
		}
	
		if(r != N)
		{
			dis[r + 1] -= x;
			insert(r + 1, 1, N, 1);
		}
	
		cout << getans(1) << endl;
	}
    
	return 0;
}

void merge(int mid, int p)
{
	for(int i1 = 0; i1 <= 1; ++ i1)
	{
		for(int i2 = 0; i2 <= 1; ++ i2)
		{
			seg[p][i1][i2] = -1919810;
			for(int i3 = 0; i3 <= 1; ++ i3)
			{
				for(int i4 = 0; i4 <= 1; ++ i4)
				{
					if(i3 != 1 || i4 != 1 || dis[mid] * dis[mid + 1] >= 0)
					{
						seg[p][i1][i2] = max(seg[p][i1][i2], seg[p << 1][i1][i3] + seg[(p << 1) | 1][i4][i2]);
					}
				}
			}
		}
	}
}

void insert(int i, int now_l, int now_r, int p)
{
	if(now_l == now_r)
	{
		seg[p][1][1] = abs(dis[i]);
		return;
	}
	
	int mid = (now_l + now_r) >> 1;
	if(i <= mid) 
		insert(i, now_l, mid, p << 1);
        
	if(i >= mid + 1) 
   		insert(i, mid + 1, now_r, (p << 1) | 1);
        
	merge(mid, p);
}

long long getans(int p)
{
	return max(max(seg[p][0][0], seg[p][0][1]), max(seg[p][1][0], seg[p][1][1]));
}
```
# 后言

作为线段树绿题，雀食有难度。

---

## 作者：2huk (赞：3)

结论是**每个划分的区间都单调**最优。

考虑差分。令 $b_i = a_i - a_{i-1}$。那么一个区间 $[l, r]$ 单调，等价于 $b_{l+1} \dots b_r$ 同号。此时对答案的贡献是 $\sum_{i=l+1}^r |b_i|$。

注意这里并没有把 $b_l$ 算进去。也就是说，如果一段区间 $[x,y]$ 被划分成了 $[x,m-1],[m,y]$，那么贡献是 $\sum_{i=x+1}^y |b_i| - |b_m|$。

于是得到了这样一个问题：

- 要求从 $b_2 \dots b_n$ 中选若干个数，使得相邻的两个数同号，并最大化选择的数的绝对值的和。

（这里一个数被选，等价于它不是划分的区间的左端点。）

（两个选择的数相邻就代表它们被划分到了同一个区间内。而同一个区间内的数应同号。）

别忘了还有 $q$ 次修改。因为是差分数组所以是单点修改。这启发我们往线段树上考虑。

我们尝试用线段树维护这个区间内选数的最大答案。发现合并（pushup）区间 $[l,mid],[mid+1,r]$ 时，我们需要知道 $mid,mid+1$ 是否**同时选择**。于是线段树的节点上维护四个值 $v_{0/1,0/1}$，表示左/右端点选/不选的最大答案。这样上传就能做了。


```cpp
// Problem: 
//     P7402 [COCI2020-2021#5] Sjeckanje
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7402
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #define tests
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10;

int n, q;
int a[N], b[N];

bool chk(int x, int y) {
	if (!x || !y) return true;
	return (x > 0) == (y > 0);
}

struct Tree {
	struct Node {
		int l, r;
		int v[2][2];
	}tr[N << 2];
	
	void pushup(int u) {
		for (int i : {0, 1}) for (int j : {0, 1})
			tr[u].v[i][j] = max({
				tr[u << 1].v[i][0] + tr[u << 1 | 1].v[0][j],
				tr[u << 1].v[i][0] + tr[u << 1 | 1].v[1][j],
				tr[u << 1].v[i][1] + tr[u << 1 | 1].v[0][j]
			});
		
		if (chk(b[tr[u << 1].r], b[tr[u << 1 | 1].l])) {
			for (int i : {0, 1}) for (int j : {0, 1})
				tr[u].v[i][j] = max(tr[u].v[i][j], tr[u << 1].v[i][1] + tr[u << 1 | 1].v[1][j]);
		}
	}
	
	void build(int u, int l, int r) {
		tr[u].l = l, tr[u].r = r;
		if (l == r) {
			tr[u].v[0][0] = 0;
			tr[u].v[1][1] = abs(b[l]);
			tr[u].v[0][1] = tr[u].v[1][0] = -2e9;
		} else {
			int mid = l + r >> 1;
			build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
			pushup(u);
		}
	}
	
	void modify(int u, int x) {
		if (tr[u].l == tr[u].r) {
			tr[u].v[1][1] = abs(b[x]);
		} else {
			int mid = tr[u].l + tr[u].r >> 1;
			if (x <= mid) modify(u << 1, x);
			else modify(u << 1 | 1, x);
			pushup(u);
		}
	}
}T;

void solve() {
	cin >> n >> q;
	
	for (int i = 1; i <= n; ++ i ) {
		cin >> a[i];
		b[i] = a[i] - a[i - 1];
	}
	
	if (n >= 2) T.build(1, 2, n);
	while (q -- ) {
		int l, r, x;
		cin >> l >> r >> x;
		b[l] += x, b[r + 1] -= x;
		if (l >= 2) T.modify(1, l);
		if (r + 1 <= n) T.modify(1, r + 1);
		cout << max({T.tr[1].v[0][0], T.tr[1].v[0][1], T.tr[1].v[1][0], T.tr[1].v[1][1]}) << '\n';
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int T = 1;
#ifdef tests
	cin >> T;
#endif
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：心灵震荡 (赞：2)

一个看起来和其他题解状态与转移都不同的 DDP 做法。

## Solution 1

先考虑一个朴素的 $O(n^2q)$ 做法。

对于区间加，我们就暴力在原数组上加一下。

对于查询，考虑 DP.

容易发现一个性质，每段的末尾一定是这一段中的最大/最小值，证明显然。

定义状态 $f_{i}$ 表示前 $i$ 个数中任意分段，$i$ 为最后一段末尾得到的权值的最大值。转移的时候枚举上一段的末尾 $j$，显然有转移 $f_{i} = \max\limits_{j<i} \{f_j + |a_{j+1}-a_i|\}$.

## Solution 2

考虑优化。常见的套路是通过分讨 $a_{j+1}$ 与 $a_i$ 的大小关系把绝对值去掉，有 $a_i - a_{j+1}$ 和 $a_{j+1} - a_i$ 两种情况。

- 若 $a_{j+1} < a_i$，则有 $f_i = \max\limits_{j<i, a_{j+1}<a_i} \{f_j + a_i - a_{j+1}\} = a_i + \max\limits_{j<i, a_{j+1}<a_i} \{f_j - a_{j+1}\}$；
- 若 $a_{j+1} > a_i$，则有 $f_i = \max\limits_{j<i, a_{j+1}>a_i} \{f_j - a_i + a_{j+1}\} = -a_i + \max\limits_{j<i, a_{j+1}>a_i} \{f_j + a_{j+1}\}$.

考虑在枚举转移的过程中动态维护 $f_j - a_{j + 1}$ 与 $f_j + a_{j + 1}$ 的前缀最大值，分别记为 $g_{j, 0}$ 和 $g_{j, 1}$.

有以下转移方程：

$$
\begin{aligned}
& f_i \gets f_{i - 1} + \max(g_{i - 1, 0} + a_i, g_{i - 1} - a_i).\\
& g_{i, 0} \gets \max(g_{i - 1, 0}, f_i - a_{i + 1}).\\
& g_{i, 1} \gets \max(g_{i - 1, 1}, f_i + a_{i + 1}).
\end{aligned}
$$

这样做是 $O(nq)$ 的。

## Solution 3

注意到转移式只有 $\max$ 和加法两种运算，并且转移的范围都很小，所以考虑矩乘优化。

> 普通的矩阵乘法无法处理 $\max$ 相关问题，考虑一个新定义的广义矩乘。
> 
> 定义 $A \otimes B = C$，则 $\displaystyle C_{i, j} = \min_{k = 1}^M (A_{i, k} + B_{k, j})$.
>
> 广义情况也**满足结合律**，故可以使用快速幂优化。
>
> 更进一步的扩展：对于两个符号 $\operatorname{op_1}, \operatorname{op_2}$，若 $\operatorname{op_2}$ 对 $\operatorname{op_1}$ 满足分配律，则都可以得到以 $\displaystyle C_{i, j} ={\operatorname{op_1}}_{k = 1}^M (A_{i, k} \operatorname{op_2} B_{k, j})$ 定义的扩展矩阵乘法。

$g$ 数组的转移是从同下标的 $f_i$ 而来，这样看起来不太好做，所以考虑将 $f_i$ 的转移式带入下面。

可以得到：

$$
\begin{aligned}
& g_{i, 0} \gets \max(g_{i - 1, 0}, \max(g_{i - 1, 0} + a_i - a_{i + 1}, g_{i - 1, 1} - a_i - a_{i + 1}).\\
& g_{i, 1} \gets \max(g_{i - 1, 1}, \max(g_{i - 1, 0} + a_i + a_{i + 1}, g_{i - 1, 1} - a_i + a_{i + 1}).
\end{aligned}
$$

整理得

$$
\begin{aligned}
& g_{i, 0} \gets \max(g_{i - 1, 0} + \max(0, a_i - a_{i + 1}), g_{i - 1, 1} - a_i - a_{i + 1}).\\
& g_{i, 1} \gets \max(g_{i - 1, 0} + a_i + a_{i + 1}, g_{i - 1, 1} + \max(0, -a_i + a_{i + 1})).
\end{aligned}
$$

这个东西就可以塞进矩阵乘法了。

对每个点维护一个广义矩阵 $F_i = \begin{bmatrix} f_i & g_{i, 0} & g_{i, 1} \end{bmatrix}$.

考虑根据转移式构造一个矩阵，

$$
G_i =
\begin{bmatrix}
-\infty & -\infty & -\infty \\
a_i & \max(0, a_i - a_{i + 1}) & a_i + a_{i + 1} \\
-a_i & -a_i - a_{i + 1} & \max(0, -a_i + a_{i + 1})
\end{bmatrix}
$$


有 $F_i = F_{i - 1} \otimes G_i$.

可以得到 $F_n = F_{n-1} \otimes G_n = \cdots = F_1 \otimes (G_2 \otimes G_3 \otimes \cdots \otimes G_n)$.

用线段树维护区间矩乘即可。

~~这时候就可以通过没有修改的情况~~，可以获得 $0$ 分。

其实本题最难的部分在于修改。

考虑单次区间加对矩阵造成的影响。

- 对 $i \in [l, r-1]$，形如相邻两项相减的部分不会发生变化（原因是这两项都会变化，差值不变），形如两项相加/相减的部分会变化 $\pm 2k$，只有一项的部分会变化 $\pm k$.
- 对 $i \in [1, l-1) \cap (r, n]$，不会造成任何影响。

后一部分不用管，前一部分可以直接维护一个区间加的 tag，每次遍历到一个区间就直接 pushdown 即可。

现在剩下的就只有 $l-1$ 和 $r$ 这两个位置。可以用树状数组维护所有 $a_i$，然后暴力更新 $F_{l-1}$ 与 $F_r$ 即可。

边界和细节比较多，可以参考代码仔细看一下。

## Code

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;
const int inf = 1e18;

int n, q, a[N], f[N], g[N][2], l, r, x;
int ct[N];

inline int lowbit(int x)
{
	return (x & (-x));
}

int qur(int x)
{
	if(x > n) return 0;
	int res = 0;
	while(x) res += ct[x], x -= lowbit(x);
	return res;
}

void add(int x, int k)
{
	while(x <= n)
	{
		ct[x] += k;
		x += lowbit(x);
	}
	return;
}

struct matrix
{
	int c[3][3];
	
	matrix operator * (const matrix &mt) const
	{
		matrix res;
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			res.c[i][j] = -inf;
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
		for(int k = 0; k < 3; k++)
			res.c[i][j] = max(res.c[i][j], c[i][k] + mt.c[k][j]);
		return res;
	}
};

inline matrix getmtr(int x)
{
	// 注意这里不能写成 a[x] 和 a[x + 1]，要在树状数组上查询以得到当前的值
	int ax = qur(x), ax1 = qur(x + 1);
	matrix res;
	// 按照式子构建矩阵
	res.c[0][0] = -inf;
	res.c[0][1] = -inf;
	res.c[0][2] = -inf;
	res.c[1][0] = ax;
	res.c[1][1] = max(0ll, ax - ax1);
	res.c[1][2] = ax + ax1;
	res.c[2][0] = -ax;
	res.c[2][1] = -ax - ax1;
	res.c[2][2] = max(0ll, -ax + ax1);
	return res;
}

struct node
{
	int l, r, tag;
	matrix mt;
} tree[N << 2];

void maketag(int x, int k) // 修改有影响的项
{
	tree[x].tag += k;
	tree[x].mt.c[1][0] += k;
	tree[x].mt.c[1][2] += 2 * k;
	tree[x].mt.c[2][0] -= k;
	tree[x].mt.c[2][1] -= 2 * k;
	return;
}

void pushdown(int x)
{
	maketag(x << 1, tree[x].tag);
	maketag(x << 1 | 1, tree[x].tag);
	tree[x].tag = 0;
}

void pushup(int x)
{
	tree[x].mt = tree[x << 1].mt * tree[x << 1 | 1].mt;
}

void build(int l, int r, int x)
{
	tree[x].l = l, tree[x].r = r;
	tree[x].tag = 0;
	if(l == r)
	{
		tree[x].mt = getmtr(l);
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, x << 1);
	build(mid + 1, r, x << 1 | 1);
	pushup(x);
	return;
}

void update(int l, int r, int k, int x) // 区间加
{
	if(l <= tree[x].l && tree[x].r <= r)
		return (void) (maketag(x, k));
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if(l <= mid) update(l, r, k, x << 1);
	if(mid < r) update(l, r, k, x << 1 | 1);
	pushup(x);
	return;
}

void modi(int p, int x) // 单点暴力修改
{
	if(p <= tree[x].l && tree[x].r <= p)
		{tree[x].mt = getmtr(p); return;}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if(p <= mid) modi(p, x << 1);
	if(mid < p) modi(p, x << 1 | 1);
	pushup(x);
	return;
}

matrix query(int l, int r, int x) // 查询 [l, r] 内的区间矩乘
{
	if(l <= tree[x].l && tree[x].r <= r)
		return tree[x].mt;
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	// 分讨左右区间的位置，乘的方向必须是左 -> 右，不能有误
	if(l <= mid && mid < r) return query(l, r, x << 1) * query(l, r, x << 1 | 1);
	else if(l <= mid) return query(l, r, x << 1);
	else if(mid < r) return query(l, r, x << 1 | 1);
}

signed main()
{
	ios :: sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++)
		cin >> a[i], add(i, a[i]), add(i + 1, -a[i]);
	build(1, n, 1);
	for(int c = 1; c <= q; c++)
	{
		cin >> l >> r >> x;
		add(l, x);
		add(r + 1, -x); // 用树状数组维护 a[i]（区间加转化为差分数祖上单点加）
		if(l <= r - 1) update(l, r - 1, x, 1); // 区间加
		// 暴力修改 l - 1 和 r 两个位置
		if(l > 0) modi(l - 1, 1);
		modi(r, 1);
		
		matrix st;
		for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			st.c[i][j] = -inf;
		f[1] = 0;
		g[1][0] = max(-qur(1), -qur(2));
		g[1][1] = max(qur(1), qur(2));
		st.c[0][0] = f[1];
		st.c[0][1] = g[1][0];
		st.c[0][2] = g[1][1]; // 提前处理 F[1]
		if(2 <= n)
		{
			matrix rt = st * query(2, n, 1);
			cout << rt.c[0][0] << '\n';
		}
		else cout << 0 << '\n';
	}
	return 0;
}
```

---

## 作者：wangyishan (赞：2)

线段树维护抽象矩阵乘法好题。

首先容易观察到一个性质：可以构造出一种最优方案，使得每个区间单调。

证明很简单，考虑一个单峰区间，你从峰上给它切开，答案一定不会更差。

令 $d_i=a_i-a_{i-1}$，则我们需要的区间划分就是使得 $[l,r]$ 中的 $d_{l+1},\dots,d_r$ 同号。

设 $f_{i,0/1}$ 表示以$i$ 结尾，最后一段是递增 or 递减段，已经考虑部分的最大权值和。转移很容易得出：

$$
f_{i,0}=\max(f_{i-1,0}+[d_i\ge 0]\cdot\left|d_i\right|,f_{i-1,1})\\
f_{i,1}=\max(f_{i-1,1}+[d_i\le 0]\cdot\left|d_i\right|,f_{i-1,0})\\
$$
然后就可以使用抽象矩阵乘法来维护了！具体的，维护一个 $(\max,+)$ 矩阵乘法：
$$
\begin{bmatrix}
f_{i,0}\\
f_{i,1}
\end{bmatrix}
=
\begin{bmatrix}
[d_i\ge 0]\cdot\left|d_i\right|&0\\
0& [d_i\le 0]\cdot\left|d_i\right|
\end{bmatrix}
\cdot
\begin{bmatrix}
f_{i-1,0}\\
f_{i-1,1}
\end{bmatrix}
$$
区间加变成两次单点修改，然后使用线段树维护抽象矩阵乘法就做完了。

细节见代码。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf=(1ll)<<50;
int n,q;
ll a[500050],d[500050];
struct martix{
    ll a[2][2];
    void clear(){memset(a,0,sizeof a);}
    void I(){for(int i=0;i<2;i++)a[i][i]=1;}
    martix(){clear();}
};
martix operator*(martix a,martix b){
    martix c;
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)c.a[i][j]=-inf;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)
                c.a[i][j]=max(c.a[i][j],a.a[i][k]+b.a[k][j]);
    return c;
}
#define ls p<<1
#define rs p<<1|1
martix s[500050<<2];
void pushup(int p){
    s[p]=s[ls]*s[rs];
}
void build(int p,int l,int r){
    if(l==r){
        s[p].a[0][0]=(d[l]>=0)*abs(d[l]),s[p].a[0][1]=0;
        s[p].a[1][0]=0,s[p].a[1][1]=(d[l]<=0)*abs(d[l]);
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
}
void change(int p,int l,int r,int k,ll v){
    if(l==r&&l==k){
        d[k]+=v;
        s[p].a[0][0]=(d[l]>=0)*abs(d[l]),s[p].a[0][1]=0;
        s[p].a[1][0]=0,s[p].a[1][1]=(d[l]<=0)*abs(d[l]);
        return;
    }
    int mid=(l+r)>>1;
    if(k<=mid)change(ls,l,mid,k,v);
    else change(rs,mid+1,r,k,v);
    pushup(p);
}
martix query(int p,int l,int r,int L,int R){
    if(L<=l&&r<=R)return s[p];
    int mid=(l+r)>>1;
    if(L>mid)return query(rs,mid+1,r,L,R);
    if(R<=mid)return query(ls,l,mid,L,R);
    return query(ls,l,mid,L,R)*query(rs,mid+1,r,L,R);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    martix S;
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<=n;i++)d[i]=a[i]-a[i-1];
    build(1,1,n);
    while(q--){
        int l,r,x;
        cin>>l>>r>>x;
        if(l>1)change(1,1,n,l,x);
        if(r<n)change(1,1,n,r+1,-x);
        S=query(1,1,n,1,n);
        cout<<max({S.a[0][0],S.a[0][1],S.a[1][0],S.a[1][1]})<<endl;
    }
    return 0;
}
```

---

## 作者：Le0Chan (赞：2)

本题中，除了 ddp 做法的题解，其他题解都或多或少有些问题，甚至出现了错误的证明。

做法一：

命题一：一定存在一种最优的划分方案，满足对于每一段 $[l,r]$，有 $\min(a_l,a_r)=\min\limits_{i\in [l,r]}a_i,\max(a_l,a_r)=\max\limits_{i\in [l,r]}a_i$。

证明：反证法，设 $a_p=\min\limits_{i\in [l,r]}a_i,a_q=\max\limits_{i\in [l,r]}a_i$，不失一般性地，假设 $p<q$。则当前贡献为 $a_q-a_p$，将区间拆为 $[l,p-1],[p,q],[q+1,r]$，则贡献为 $a_q-a_p+|a_r-a_{q+1}|+|a_{p-1}-a_l|$。

命题二：一定存在一种最优的划分方案，形如每一段的数内部单调不增或不降。

证明：首先长度为 $1$ 的区间不理会。还是反证，对于区间 $[l,r]$，假设 $a_l\le a_r$，存在 $p$ 满足 $a_l\le a_p>a_{p+1}\le a_r$。则将其拆成 $[l,p],[p+1,r]$ 一定不劣。

有了命题二后问题变得简单了许多。对于每一个区间 $[l,r]$，贡献形如 $|a_r-a_{l-1}|$，考虑拆贡献，在差分序列 $b_i=a_i-a_{i-1}$ 上考虑，贡献变为了 $\sum\limits_{i\in [l+1,r]}|b_i|$。观察哪些数在 $b$ 中产生了贡献，容易发现，对于任意极长连续段，$b$ 应当同号。这将问题转化为了另一形式：在序列里选出一些数，贡献为每个数的绝对值之和，要求不能存在两个相邻的异号的数都被选取。这启示我们进行分治，合并两个区间只需要关注交界处的符号，如果交界处异号，则这两个位置不能同时选，只需要处理出区间两个端点分别选或者不选四种情况即可。

区间修改在差分时变为了单点改。用线段树快速维护上述分治即可。

所以，部分题解中的区间一定是极长的单调区间就实属无稽之谈，忽略了长度为 $1$ 的区间的存在性。例如以下数据就能解决掉这个结论：

```1 4 -3 -4```

做法二：

划分区间难以快速计算，考虑从最小值和最大值出发，选取偶数个数，相邻的进行配对，贡献两数差的绝对值。容易得到一个递推：$f_{i,0/1/2}$ 为前 $i$ 个数，当前存在一个最小值/最大值未配对，或者什么没有需要配对的数。观察转移只与前一个数有关，且 $(\max,+)$ 有分配律和结合律，可以进行 ddp。但是本题较为特殊的地方是要支持区间加。$\prod (A_i+K)$ 与 $\prod A_i$ 在 $(\max,+)$ 运算下的差值是很好算的，但是这里的修改是给所有 $a_i$ 的位置加 $k$。一眼瞪不出来，可以打表找个规律，证明考虑展开证明。但是这种做法应当拓展性不强，因为与矩阵乘法的形式和转移矩阵有关。

给出两种做法的代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Le0{
#define LL long long
const int N=2e5+5;
int n,Q;
LL a[N],f[N][3];
// LL solve(){
//     memset(f,0xc0,sizeof(f));
//     f[0][0]=0;  
//     for(int i=1;i<=n;i++){
//         f[i][0]=max({f[i-1][0],f[i-1][1]+a[i],f[i-1][2]-a[i]});
//         f[i][1]=max({f[i-1][1],f[i-1][0]-a[i]});
//         f[i][2]=max({f[i-1][2],f[i-1][0]+a[i]});
//     }
//     return f[n][0];
// }
struct mat{
    LL a[3][3];
    mat(){memset(a,0xc0,sizeof(a));}
    LL* operator[](int x){return a[x];}
    void I(){memset(a,0,sizeof(a));}
    void prin(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                cout<<a[i][j]<<' ';
            }cout<<'\n';
        }cout<<"ed\n";
    }
}t[N<<2];
mat operator*(mat a,mat b){
    mat c;
    for(int i=0;i<3;i++)
        for(int k=0;k<3;k++)
            for(int j=0;j<3;j++)
                c[i][j]=max(c[i][j],a[i][k]+b[k][j]);
    return c;
}
mat operator+(mat a,mat b){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            a[i][j]+=b[i][j];
    return a;
}
struct seg{
    LL tg[N<<2];
    void pp(int p){t[p]=t[p<<1]*t[p<<1|1];}
    void build(int p,int l,int r){
        if(l==r){
            t[p][0][1]=t[p][2][0]=-a[l];
            t[p][0][2]=t[p][1][0]=a[l];
            t[p][0][0]=t[p][1][1]=t[p][2][2]=0;
            return;
        }int mid=l+r>>1;
        build(p<<1,l,mid);build(p<<1|1,mid+1,r);
        pp(p);
    }
    void add(int p,int l,int r,LL k){
        tg[p]+=k;
        mat c;c.I();
        c[0][1]=-k;c[0][2]=k;
        c[1][0]=k;c[1][2]=2ll*k;
        c[2][0]=-k;c[2][1]=-2ll*k;
        t[p]=t[p]+c;
    }
    void pd(int p,int l,int r){
        if(tg[p]){
            int mid=l+r>>1;
            add(p<<1,l,mid,tg[p]);
            add(p<<1|1,mid+1,r,tg[p]);
            tg[p]=0;
        }
    }
    void modify(int p,int l,int r,int ql,int qr,int x){
        if(l>=ql&&r<=qr){
            add(p,l,r,x);
            return;
        }int mid=l+r>>1;pd(p,l,r);
        if(ql<=mid) modify(p<<1,l,mid,ql,qr,x);
        if(qr>mid) modify(p<<1|1,mid+1,r,ql,qr,x);
        pp(p);
    }
}sg;
int main(){
    cin>>n>>Q;
    for(int i=1;i<=n;i++) cin>>a[i];
    sg.build(1,1,n);
    for(int i=1,l,r,x;i<=Q;i++){
        cin>>l>>r>>x;
        sg.modify(1,1,n,l,r,x);
        mat c;c[0][0]=0;
        cout<<(c*t[1])[0][0]<<'\n';
    }
    return 0;
}
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    return Le0::main();
}
```


```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Le0{
#define LL long long
const int N=2e5+5;
const LL inf=1e18;
int n,Q;
LL a[N],b[N];
struct node{
    LL v[2][2];int l,r;
    node(){v[0][0]=v[0][1]=v[1][0]=v[1][1]=-inf;}
    void prin(){
        cout<<l<<" "<<r<<"\n";
        cout<<v[0][0]<<" "<<v[0][1]<<" "<<v[1][0]<<" "<<v[1][1]<<'\n';
    }
}t[N<<2];
bool ck(LL x){return x>=0;}
node mg(node A,node B){
    node C;C.l=A.l;C.r=B.r;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int ii=0;ii<2;ii++){
                for(int jj=0;jj<2;jj++){
                    if(b[A.r]>0&&b[B.l]<0&&ii==1&&jj==1) continue;
                    if(b[A.r]<0&&b[B.l]>0&&ii==1&&jj==1) continue;
                    C.v[i][j]=max(C.v[i][j],A.v[i][ii]+B.v[jj][j]);
                }
            }
        }
    }
    return C;
}
struct seg{
    void build(int p,int l,int r){
        t[p].l=l;t[p].r=r;
        if(l==r){
            t[p].v[0][0]=0;t[p].v[1][1]=abs(b[l]);
            return;
        }int mid=l+r>>1;
        build(p<<1,l,mid);build(p<<1|1,mid+1,r);
        t[p]=mg(t[p<<1],t[p<<1|1]);
    }
    void modify(int p,int l,int r,int x){
        if(l==r){
            t[p].v[0][0]=0;t[p].v[1][1]=abs(b[l]);
            return;
        }int mid=l+r>>1;
        if(x<=mid) modify(p<<1,l,mid,x);
        else modify(p<<1|1,mid+1,r,x);
        t[p]=mg(t[p<<1],t[p<<1|1]);
    }
}sg;
int main(){
    cin>>n>>Q;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) b[i]=a[i]-a[i-1];
    sg.build(1,1,n);
    for(int i=1,l,r,x;i<=Q;i++){
        cin>>l>>r>>x;
        b[l]+=x; b[r+1]-=x; sg.modify(1,1,n,l);
        if(r<n) sg.modify(1,1,n,r+1);
        cout<<max(t[1].v[0][1],t[1].v[0][0])<<'\n';
    }
    return 0;
}
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    return Le0::main();
}
```

---

## 作者：Nygglatho (赞：2)

感觉关键就是找到贪心思路，不然复杂度就会被卡在 $O(n^3)$

可以发现，找 **极长的单调** 递增或递减序列，一定不会更劣。

证明：

- 对于一段单调递增（单调递减同理）的区间 $[l,r]$，满足 $a_l\le a_{l+1}\le\cdots\le a_r$，则这一段对答案贡献为 $a_r-a_l$。但是如果找到一个 $t(l\le t<r)$，分割为 $[l,t]$ 和 $[t+1,r]$，对答案贡献为 $(a_t-a_l)+(a_r-a_{t+1})$。显然，和不分割相比，答案减少了 $a_{t+1}-a_t$。因为单调递增，所以 $a_{t+1}-a_t\ge 0$，分割一定不会更优。
- 对于一段区间 $[l,r]$，其中满足存在一个 $p(l\le p<r)$，使得 $a_l\le a_{l+1}\le \cdots a_p> a_{p+1}\ge a_{p+2}\ge\cdots\ge a_r$，不分割，答案为 $\max(a_p-a_l,a_p-a_r)$，但是如果分割为 $[l,p]$ 和 $[p+1,r]$，答案则为 $(a_p-a_l)+(a_p-a_r)$，显然分割不会更劣。

考虑差分，令 $b_i=a_i-a_{i-1}$，那么单调递增区间 $[l,r]$ 则满足 $\forall l\le i\le r,b_i\ge 0$，单调递减同理为 $\le 0$，而由于差分，每个单调的区间 $[l,r]$ 答案即为 $\sum\limits_{i=l}^r |b_i|$。

考虑线段树，$[l,r]$ 区间维护 **差分数组区间为 $[l,r]$** 时最优方案，$[l,m]$ 和 $[m+1,r]$ 为子节点，分为两种情况：

- 如果 $b_m$ 和 $b_{m+1}$ 同号，那么可以直接合并，因为中间的区间可以合并到一起。
- 如果是异号，以 $m$ 位置为当前两段区间的谷为例，我们发现，差分之后按照刚才直接合并的方法，贡献相当于 $\max\limits_{i=l-1}^ma_l-a_m+\max\limits_{i=m}^ra_l-a_m$。注意到 $a_m$ 会重复计算，因此需要再额外线段树分别维护左右端点不选（以及全不选）的情况，并根据两种不同情况（$[l,m]$ 选右端点 $[m+1,r]$ 不选左端点，以及 $[l,m]$ 不选右端点 $[m+1,r]$ 选左端点）更新 $\max$ 的答案。

[Code](https://loj.ac/s/2157879)。

---

## 作者：Ooj_bai (赞：2)

介绍一个没那么精巧但（自认为）胜在好想的方法。
#### 部分分
  首先，对于静态的问题（即不带修改）我们可以使用 dp 解决。  
  显然，每个数对答案有三种可能：不贡献，作为区间最大值贡献正值，或作为区间最小值贡献负值。  
  我们定义一个贡献点是“已配对的”当且仅当存在一个与它贡献符号相反且中间不存在其他贡献点的未配对点。显然，对于一个全部已配对的贡献点集合，一定存在一个划分方式使得答案不劣于该集合的答案。    
  于是定义 $dp_{i,0/1/2}$ 表示前 $i$ 个数最后一个贡献点已配对或贡献正值或负值。有转移：
$$$
dp_{i,0}=\max(dp_{i-1,0},dp_{i-1,1}-a_i,dp_{i-1,2}+a_i)
$$$
$$$
				dp_{i,1}=\max(dp_{i-1,1},dp_{i-1,0}+a_i) 
$$$
$$$
				dp_{i,2}=\max(dp_{i-1,2},dp_{i-1,0}-a_i)
$$$
答案等于 $dp_{n,0}$。  
对于 $ 1 \le n,q \le 3000$ 的部分，暴力修改并每次重跑一遍 dp 即可。
#### 正解
线段树维护带信息的合并是常见套路，但为了合并信息，我们需要增设状态。定义 $t_{x,0/1/2,0/1/2}$ 表示对于 $x$ 所代表的区间最左边和最右边的贡献点已配对或贡献正或负值。定义 $ls(x)$ 为 x 的左子树（线段树上）,$rs(x)$ 为 x 右子树，有合并:
$$$
t_{x,0,0}=max({t_{ls(x),0,1}+t_{rs(x),2,0},t_{ls(x),0,2}+t_{rs(x),1,0},t_{ls(x),0,0}+t_{rs(x),0,0},t_{ls(x),0,0},t_{rs(x),0,0}})
$$$
$$$
t_{x,0,1}=\max({t_{ls(x),0,1}+t_{rs(x),2,1},t_{ls(x),0,2}+t_{rs(x),1,1},t_{ls(x),0,0}+t_{rs(x),0,1},t_{ls(x),0,1},t_{rs(x),0,1}})
$$$
$$$
t_{x,0,2}=\max({t_{ls(x),0,1}+t_{rs(x),2,2},t_{ls(x),0,2}+t_{rs(x),1,2},t_{ls(x),0,0}+t_{rs(x),0,2},t_{ls(x),0,2},t_{rs(x),0,2}})
$$$
$$$
t_{x,1,0}=\max({t_{ls(x),1,1}+t_{rs(x),2,0},t_{ls(x),1,2}+t_{rs(x),1,0},t_{ls(x),1,0}+t_{rs(x),0,0},t_{ls(x),1,0},t_{rs(x),1,0}})
$$$
$$$
t_{x,1,1}=\max({t_{ls(x),1,1}+t_{rs(x),2,1},t_{ls(x),1,2}+t_{rs(x),1,1},t_{ls(x),1,0}+t_{rs(x),0,1},t_{ls(x),1,1},t_{rs(x),1,1}})
$$$
$$$
t_{x,1,2}=\max({t_{ls(x),1,1}+t_{rs(x),2,2},t_{ls(x),1,2}+t_{rs(x),1,2},t_{ls(x),1,0}+t_{rs(x),0,2},t_{ls(x),1,2},t_{rs(x),1,2}})
$$$
$$$
t_{x,2,0}=\max({t_{ls(x),2,1}+t_{rs(x),2,0},t_{ls(x),2,2}+t_{rs(x),1,0},t_{ls(x),2,0}+t_{rs(x),0,0},t_{ls(x),2,0},t_{rs(x),2,0}})
$$$
$$$
t_{x,2,1}=\max({t_{ls(x),2,1}+t_{rs(x),2,1},t_{ls(x),2,2}+t_{rs(x),1,1},t_{ls(x),2,0}+t_{rs(x),0,1},t_{ls(x),2,1},t_{rs(x),2,1}})
$$$
$$$
t_{x,2,2}=\max({t_{ls(x),2,1}+t_{rs(x),2,2},t_{ls(x),2,2}+t_{rs(x),1,2},t_{ls(x),2,0}+t_{rs(x),0,2},t_{ls(x),2,2},t_{rs(x),2,2}})
$$$
考虑修改，对于整个区间的修改，已配对的贡献点不会有改变。只会使端点处贡献发生改变。
#### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define maxn 200005
using namespace std;
int n,q,a[maxn],dp[maxn][3];
struct xds{
	int lazy;
	int maxx[3][3];
	//0:已匹配 1:大 2:小 
}t[maxn*4];
void push_up(int x){
	t[x].maxx[0][0]=max({t[ls(x)].maxx[0][1]+t[rs(x)].maxx[2][0],t[ls(x)].maxx[0][2]+t[rs(x)].maxx[1][0],t[ls(x)].maxx[0][0]+t[rs(x)].maxx[0][0],t[ls(x)].maxx[0][0],t[rs(x)].maxx[0][0]});
	t[x].maxx[0][1]=max({t[ls(x)].maxx[0][1]+t[rs(x)].maxx[2][1],t[ls(x)].maxx[0][2]+t[rs(x)].maxx[1][1],t[ls(x)].maxx[0][0]+t[rs(x)].maxx[0][1],t[ls(x)].maxx[0][1],t[rs(x)].maxx[0][1]});
	t[x].maxx[0][2]=max({t[ls(x)].maxx[0][1]+t[rs(x)].maxx[2][2],t[ls(x)].maxx[0][2]+t[rs(x)].maxx[1][2],t[ls(x)].maxx[0][0]+t[rs(x)].maxx[0][2],t[ls(x)].maxx[0][2],t[rs(x)].maxx[0][2]});
	t[x].maxx[1][0]=max({t[ls(x)].maxx[1][1]+t[rs(x)].maxx[2][0],t[ls(x)].maxx[1][2]+t[rs(x)].maxx[1][0],t[ls(x)].maxx[1][0]+t[rs(x)].maxx[0][0],t[ls(x)].maxx[1][0],t[rs(x)].maxx[1][0]});
	t[x].maxx[1][1]=max({t[ls(x)].maxx[1][1]+t[rs(x)].maxx[2][1],t[ls(x)].maxx[1][2]+t[rs(x)].maxx[1][1],t[ls(x)].maxx[1][0]+t[rs(x)].maxx[0][1],t[ls(x)].maxx[1][1],t[rs(x)].maxx[1][1]});
	t[x].maxx[1][2]=max({t[ls(x)].maxx[1][1]+t[rs(x)].maxx[2][2],t[ls(x)].maxx[1][2]+t[rs(x)].maxx[1][2],t[ls(x)].maxx[1][0]+t[rs(x)].maxx[0][2],t[ls(x)].maxx[1][2],t[rs(x)].maxx[1][2]});
	t[x].maxx[2][0]=max({t[ls(x)].maxx[2][1]+t[rs(x)].maxx[2][0],t[ls(x)].maxx[2][2]+t[rs(x)].maxx[1][0],t[ls(x)].maxx[2][0]+t[rs(x)].maxx[0][0],t[ls(x)].maxx[2][0],t[rs(x)].maxx[2][0]});
	t[x].maxx[2][1]=max({t[ls(x)].maxx[2][1]+t[rs(x)].maxx[2][1],t[ls(x)].maxx[2][2]+t[rs(x)].maxx[1][1],t[ls(x)].maxx[2][0]+t[rs(x)].maxx[0][1],t[ls(x)].maxx[2][1],t[rs(x)].maxx[2][1]});
	t[x].maxx[2][2]=max({t[ls(x)].maxx[2][1]+t[rs(x)].maxx[2][2],t[ls(x)].maxx[2][2]+t[rs(x)].maxx[1][2],t[ls(x)].maxx[2][0]+t[rs(x)].maxx[0][2],t[ls(x)].maxx[2][2],t[rs(x)].maxx[2][2]});
}
void push_down(int x){
	if(t[x].lazy){
		for(int i=0;i<3;i++){
			t[ls(x)].maxx[1][i]+=t[x].lazy;t[rs(x)].maxx[1][i]+=t[x].lazy;
			t[ls(x)].maxx[i][1]+=t[x].lazy;t[rs(x)].maxx[i][1]+=t[x].lazy;
			t[ls(x)].maxx[2][i]-=t[x].lazy;t[rs(x)].maxx[2][i]-=t[x].lazy;
			t[ls(x)].maxx[i][2]-=t[x].lazy;t[rs(x)].maxx[i][2]-=t[x].lazy;
		}
		t[ls(x)].lazy+=t[x].lazy;
		t[rs(x)].lazy+=t[x].lazy; 
		t[x].lazy=0;
	}
	push_up(x);
}
void build(int l,int r,int x){
	if(l==r){
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				t[x].maxx[i][j]=-100000000000000ll;
		t[x].maxx[0][1]=t[x].maxx[1][0]=a[l];
		t[x].maxx[2][0]=t[x].maxx[0][2]=-a[l];
		return;
	}
	int mid=l+r>>1ll;
	build(l,mid,ls(x));
	build(mid+1,r,rs(x));
	push_up(x);
}
void update(int l,int r,int ex,int s,int e,int x){
	if(l<=s&&e<=r){
		t[x].lazy+=ex;
		for(int i=0;i<3;i++){
			t[x].maxx[1][i]+=ex;
			t[x].maxx[i][1]+=ex;
			t[x].maxx[2][i]-=ex;
			t[x].maxx[i][2]-=ex;
		}
		return;
	}
	push_down(x);
	int mid=s+e>>1ll;
	if(l<=mid)update(l,r,ex,s,mid,ls(x));
	if(mid<r)update(l,r,ex,mid+1,e,rs(x));
	push_up(x);
}
void dfs(int l,int r,int x){
	if(l==r)return;
	push_down(x);
	int mid=l+r>>1ll;
	dfs(l,mid,ls(x));
	dfs(mid+1,r,rs(x));
	push_up(x);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n<=3000&&q<=3000){
		while(q--){
			int l,r,x;
			cin>>l>>r>>x;
			for(int i=l;i<=r;i++)a[i]+=x;
			for(int i=0;i<=n;i++)
				dp[i][0]=dp[i][1]=dp[i][2]=0;
			dp[0][1]=dp[0][2]=-100000000000000ll;
			for(int i=1;i<=n;i++){
				dp[i][0]=max(dp[i-1][0],max(dp[i-1][1]-a[i],dp[i-1][2]+a[i]));
				dp[i][1]=max(dp[i-1][1],dp[i-1][0]+a[i]);
				dp[i][2]=max(dp[i-1][2],dp[i-1][0]-a[i]);
			}
			cout<<dp[n][0]<<'\n';
		}
	}else{
		build(1,n,1);
		while(q--){
			int l,r,x;
			cin>>l>>r>>x;
			update(l,r,x,1,n,1);
			cout<<t[1].maxx[0][0]<<'\n';
		}
	}
	return 0;
}
```
该做法无需观察性质，代价是比较难写。

---

## 作者：冷却心 (赞：0)

宝宝 ds。

若只考虑静态。性质：分段方案中每一段均单调。注意到如果一段分段不单调，那么把他按最值切割一定不劣。

那么有一个 naive 的 dp，记 $f_{i,0/1/2}$ 为处理完前 $i$ 个数，当前这一段单调递增且未结束，单调递减且未结束，结束于此的答案。转移 trivial。

观察到转移式中包含 $a_i$，不方便处理一段区间加法的贡献，所以考虑换一种方式转移：我们发现一段递增区间的贡献可以转化为，区间首位不贡献，其他位置贡献 $a_i-a_{i-1}$，递减同理，所以我们设 $f_{i,0/1}$ 为处理完前 $i$ 位，当前段递增或递减，转移也是简单的：

$$f_{i,0}=\max\{f_{i-1,0}+a_i-a_{i-1},f_{i-1,1}\},\\f_{i,1}=\max\{f_{i-1,1}+a_{i-1}-a_i,f_{i-1,0}\}.$$

会发现这样转移的贡献是一个差分状物，区间修改对一个区间内部的差分毫无影响，所以可以上线段树直接维护。对每个区间记录信息 $(l,r,g_{0/1,0/1})$，分别表示区间首尾元素，区间内部处理完，并且首位状态递增或递减，末位状态递增或递减的答案，合并类似上述转移，区间加法只对 $l,r$ 信息存在修改，然后做完了。时间复杂度 $O(q\log n)$，带个 $2^4$ 合并的常数，循环展开一下跑的飞快。

```cpp
#include <bits/stdc++.h>
#define uint unsigned int
#define ull unsigned long long
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const LL inf = 1e18;
int n, Q, A[N];

struct Node { LL l, r, res[2][2]; } tr[N << 2]; LL tag[N << 2];
const Node operator+(const Node& a, const Node& b) {
	Node c = {a.l, b.r, {{-inf, -inf}, {-inf, -inf}}};
	for (int j = 0; j < 2; j ++) for (int p = 0; p < 2; p ++) {
		LL w = max(0ll, (j == p ? (j ? b.l - a.r : a.r - b.l) : 0));
		c.res[0][0] = max(c.res[0][0], a.res[0][j] + b.res[p][0] + w);
		c.res[0][1] = max(c.res[0][1], a.res[0][j] + b.res[p][1] + w);
		c.res[1][0] = max(c.res[1][0], a.res[1][j] + b.res[p][0] + w);
		c.res[1][1] = max(c.res[1][1], a.res[1][j] + b.res[p][1] + w);
	} return c;
}
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
void build(int p, int l, int r) {
	if (l == r) {
		tr[p].l = tr[p].r = A[l]; tr[p].res[0][1] = tr[p].res[1][0] = -1e18; return ;
	} int mid = (l + r) >> 1;
	build(ls(p), l, mid); build(rs(p), mid + 1, r); tr[p] = tr[ls(p)] + tr[rs(p)];
	return ;
}
void f(int p, LL k) { tr[p].l += k; tr[p].r += k; tag[p] += k; }
void pushdown(int p) { if (tag[p]) f(ls(p), tag[p]), f(rs(p), tag[p]), tag[p] = 0; }
void update(int p, int l, int r, int x, int y, int k) {
	if (x > r || y < l) return ;
	if (x <= l && y >= r) { f(p, k); return ; }
	int mid = (l + r) >> 1; pushdown(p);
	update(ls(p), l, mid, x, y, k); update(rs(p), mid + 1, r, x, y, k);
	tr[p] = tr[ls(p)] + tr[rs(p)]; return ;
}

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> Q;
	for (int i = 1; i <= n; i ++) cin >> A[i];
	build(1, 1, n); int x, y, k;
	while (Q --) {
		cin >> x >> y >> k; update(1, 1, n, x, y, k);
		cout << max({tr[1].res[0][0], tr[1].res[0][1], tr[1].res[1][0], tr[1].res[1][1]}) << "\n";
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

首先考虑不带修怎么做，显然容易想到动态规划做法，定义 $dp_{i, 0/1/2}$ 表示前 $i$ 个数分段后：

- 啥也没剩。

- 剩一个最大值。

- 剩一个最小值。

得到的最大可能值。这样虽然可能有不是极差，但是由于不是极差，所以差比极差小，所以不影响。

于是有状态转移：

$$\begin{cases} dp_{i, 0} = \max(dp_{i - 1, 0}, dp_{i - 1, 1} - a_i, dp_{i - 1, 2} + a_i)  \\ dp_{i, 1} = \max(dp_{i - 1, 1}, dp_{i - 1, 0} + a_i) \\  dp_{i, 2} = \max(dp_{i - 1, 2}, dp_{i - 1, 0} - a_i )\end{cases}$$

朴素做是 $O(nq)$ 的考虑优化。

维护动态 dp，考虑矩阵，使用广义的 $(\max, +)$ 矩阵，容易验证其有结合律和分配律，令：

$$T_i = \begin{bmatrix} 0 & a_i & -a_i \\ -a_i & 0 & -\inf \\ a_i & -\inf & 0 \end{bmatrix}$$

于是：

$$\begin{bmatrix} dp_{i - 1, 0} & dp_{i - 1, 1} & dp_{i - 1, 2} \end{bmatrix} \cdot T_i = \begin{bmatrix} dp_{i, 0} & dp_{i, 1} & dp_{i, 2} \end{bmatrix}$$

区间加 $x$ 是一样的，即区间加这样的一个矩阵：

$$\begin{bmatrix} 0 & x & -x \\ -x & 0 & -2x \\ x & 2x & 0 \end{bmatrix}$$

使用线段树维护即可，时间复杂度为 $O(\omega^3 n \log n)$，这里 $\omega = 3$。

注意初始 $dp_{0, 0} = 0, dp_{0, 1} = dp_{0, 2} = -\inf$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10;
const ll inf = 3e13;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Mat{
	ll a[3][3];
	inline ll* operator[](int i){
		return a[i];
	}
	inline friend Mat operator*(Mat a, Mat b){
		Mat ans;
		for(int i = 0; i < 3; ++i){
			for(int j = 0; j < 3; ++j){
				ans[i][j] = -inf;
				for(int k = 0; k < 3; ++k)
				  ans[i][j] = max(ans[i][j], a[i][k] + b[k][j]);
			}
		}
		return ans;
	}
}now;
struct Node{
	int l, r;
	ll tag;
	Mat mul;
}X[N << 2];
int n, q, l, r, x;
int a[N];
inline void pushup(int k){
	X[k].mul = X[k << 1].mul * X[k << 1 | 1].mul;
}
inline void add(int k, ll v){
	X[k].tag += v;
	X[k].mul[0][1] += v, X[k].mul[2][0] += v, X[k].mul[2][1] += 2 * v;
	X[k].mul[0][2] -= v, X[k].mul[1][0] -= v, X[k].mul[1][2] -= 2 * v;
}
inline void push_down(int k){
	if(X[k].tag){
		add(k << 1, X[k].tag);
		add(k << 1 | 1, X[k].tag);
		X[k].tag = 0;
	}
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r){
		X[k].mul[0][0] = X[k].mul[1][1] = X[k].mul[2][2] = 0;
		X[k].mul[0][1] = X[k].mul[2][0] = a[l];
		X[k].mul[0][2] = X[k].mul[1][0] = -a[l];
		X[k].mul[1][2] = X[k].mul[2][1] = -inf;
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void update(int k, int l, int r, int v){
	if(X[k].l == l && r == X[k].r){
		add(k, v);
		return ;
	}
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  update(k << 1, l, r, v);
	else if(l > mid)
	  update(k << 1 | 1, l, r, v);
	else{
		update(k << 1, l, mid, v);
		update(k << 1 | 1, mid + 1, r, v);
	}
	pushup(k);
}
bool End;
int main(){
	<!-- freopen("lom.in", "r", stdin); -->
	<!-- freopen("lom.out", "w", stdout); -->
	now[0][1] = now[0][2] = -inf;
	n = read(), q = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	build(1, 1, n);
	while(q--){
		l = read(), r = read(), x = read();
		update(1, l, r, x);
		auto t = now * X[1].mul;
		write(t[0][0]);
		putchar('\n');
	}
	//cerr  << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：hnczy (赞：0)

有一点意思的题目，让我知道了 DDP 区间加的方法。

首先容易想到状态 $dp_{i,0/1/2}$ 表示到 $i$ 这个点，经过若干次分割，没有需要的，需要一个最小值，需要一个最大值。

很好写出转移：

- $dp_{i,0}=\max(dp_{i-1,1}-a_i,dp_{i-1,2}+a_i,dp_{i-1,0})$。

- $dp_{i,1} = \max(dp_{i-1,1},dp_{i-1,0}+a_i)$。

- $dp_{i,2}=\max(dp_{i-1,2},dp_{i-1,0}-a_i)$。

可以写出 $O(nq)$ 算法，可以得到一定部分分。

既然是动态修改的，考虑 ddp 。容易写出转移矩阵。

$$
\begin{vmatrix}
0 & -a_i & a_i& \\
a_i & 0& -\inf\\
-a_i & -\inf & 0
\end{vmatrix}
$$

然而这里是一个区间修改，一般的 ddp 都是单点修改，比较好写，那我们如何写呢？

这里需要用一个矩阵转移，这个矩阵需要自己构造，这里直接列出：

$$
\begin{vmatrix}
0 &−x&x \\
 
x&0&2x\\
 
−x&−2x&0\\
\end{vmatrix}
$$

区间加上这一个矩阵，用一个懒惰标记即可。注意这里是矩阵加法，而不是矩阵乘法。

时间复杂度 $O(k^3n\log n)(k=3)$

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2E5+5,inf=1e16;
int n,m,a[N];
struct Mat{
	int c[3][3];
	Mat(){
		memset(c,0,sizeof c);
	}
	Mat operator * (const Mat &a){
		Mat res;
		memset(res.c,-0x3f,sizeof res.c);
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					res.c[i][j]=max(c[i][k]+a.c [k][j],res.c[i][j]);
		return res;
	}
	Mat operator +(const Mat &a){
		Mat res;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				res.c[i][j]=c[i][j]+a.c[i][j];
		return res; 
	} 
	void clear(){
		memset(c,0,sizeof c);
	}
	void operator = (const int &a){
		c[0][1]=a,c[0][2]=-a;
		c[1][0]=-a,c[1][2]=-inf;
		c[2][0]=a,c[2][1]=-inf;
	}
};
Mat mul;
struct SEG{
	#define ls (p<<1)
	#define rs (p<<1|1)
	#define mid (l+r>>1)
	Mat c[N<<2],tag[N<<2];
	void pushup(int p){
		c[p]=c[ls]*c[rs];
	} 
	void pushdown(int p){
		c[ls]=c[ls]+tag[p];
		c[rs]=c[rs]+tag[p];
		tag[ls]=tag[ls]+tag[p];
		tag[rs]=tag[rs]+tag[p];
		tag[p].clear() ;
	} 
	void change(int p,int l,int r,int L,int R){
		if(L<=l &&r<=R){
			c[p]=c[p]+mul;
			tag[p]=tag[p]+mul;
			return ; 
		}
		pushdown(p);
		if(L<=mid)change(ls,l,mid,L,R);
		if(R> mid)change(rs,mid+1,r,L,R);
		pushup(p);
	}
	void build(int p,int l,int r){
		if(l==r)return c[p]=a[l],void();
		build(ls,l,mid),build(rs,mid+1,r);
		pushup(p);
	}
}seg;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",a+i);
	Mat tmp;
	tmp.c[0][1]=tmp.c[0][2]=-inf;
	seg.build(1,1,n);
	//cout<<(tmp*seg.c[1]).c[0][0]<<endl;
	for(int i=1,l,r,x;i<=m;i++){
		scanf("%lld%lld%lld",&l,&r,&x);
		mul.clear() ;
		mul.c[0][1]=x;
		mul.c[0][2]=-x;
		mul.c[1][0]=-x;
		mul.c[1][2]=-2*x;
		mul.c[2][0]=x;
		mul.c[2][1]=2*x;
		seg.change(1,1,n,l,r);
		Mat ans = tmp*seg.c[1];
		printf("%lld\n",ans.c[0][0]);
	}
	return 0;
}

```

---

## 作者：_anll_ (赞：0)

感觉挺高质一题，当然也有可能是阿凉菜菜。

写篇题解当作攒 rp 了，s 组一定要一等啊啊！

## 思路
如果没有修改，$O(n)$ 的 dp 是十分显然的。具体地，如果要将一个数加入当前区间，当其对 $minn$ 或 $maxn$ 有贡献时才应当扩展区间，否则从 $r+1$ 起另开一区间一定不劣。进一步推断会发现，当区间形成单调递增或递减时为最优解。

我们发现，如果两个区间需要合并，那么一定要符合单调性，其实只与差值有关。于是我们可以将原数组转成差分数组即可，注意此时的差分数组只有下标 $2\sim n$ 有效（默认从 $1$ 开始）。于是问题变成了单点修改差分数组，区间查询整个数组的结果。你发现这个问题很线段树，而线段树的时间复杂度通过本题绰绰有余。

我们考虑如何维护合并。这里可以粗略分为两个大类讨论：两个区间合并后形成一个大合法区间，那么我们只需要将左区间末和右区间初的差值加上即可；对于两个区间无法合并成大合法区间的情况，我们考虑将其拆开，但这就要涉及到边界值选或不选的情况，如果不理解这里的可以手玩一下。发现状态至多四个，不妨直接枚举。具体地，我们设 $maxn[0/1][0/1]$ 为不选/选左端点且不选/选右端点的情况下的最大值，合并时只需要比较一下怎么划分值大即可。

特别地，对于 $2\sim n$ 这个区间，选择左端点与右端点一定不劣，因此我们输出时不需要判断。

## 代码
大体思路就是这样，有不清楚的地方可以结合注释理解。
```cpp
#include<cmath>
#include<iostream>
#define lc p<<1
#define rc p<<1|1
#define int long long
#define mid (tr[p].l+tr[p].r)/2
using namespace std;
const int N=2e5+5;
struct Tr{
	int l,r,maxn[2][2];
}tr[N<<2];
int n,q,num[N],dis[N];
void pushup(int p){
	for(int i=0;i<=1;i++){
		for(int j=0;j<=1;j++){
			if(dis[tr[lc].r]*dis[tr[rc].l]<0)
				tr[p].maxn[i][j]=max(tr[lc].maxn[i][0]+tr[rc].maxn[1][j],//讨论中间点归左/右区间谁更优 
									 tr[lc].maxn[i][1]+tr[rc].maxn[0][j]);
			else tr[p].maxn[i][j]=tr[lc].maxn[i][1]+tr[rc].maxn[1][j];
		}
	}
}
void build(int l,int r,int p){
	tr[p]={l,r};
								//注意这里要使用绝对值 
	if(l==r) return void(tr[p].maxn[1][1]=abs(dis[l]));
	build(l,mid,lc);build(mid+1,r,rc);
	pushup(p);
}
void update(int a,int p){
	if(tr[p].l==tr[p].r) return void(tr[p].maxn[1][1]=abs(dis[tr[p].l]));
	if(a<=mid) update(a,lc);
	else update(a,rc);
	pushup(p);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>q;int l,r,x;
	for(int i=1;i<=n;i++) cin>>num[i];
	for(int i=2;i<=n;i++) dis[i]=num[i]-num[i-1];
	if(n>1) build(2,n,1);//差分数组下标从2开始 
	while(q--){
		cin>>l>>r>>x;
		if(l>1) dis[l]+=x,update(l,1);
		if(r<n) dis[r+1]-=x,update(r+1,1);
		cout<<tr[1].maxn[1][1]<<endl; 
	}
	return 0;
}
```

---

## 作者：LCat90 (赞：0)

我们可以选取一段单调的序列。那么这个序列一定不能通过划分，使得权值优于直接选这个序列而不分的权值。

于是我们把整个序列分成若干段单调的序列，并且每个子序列最长。要证明这样可行，只需要再证明两个不同的单调序列进行合并更劣。显然地，如果一个元素加入了另一个单调序列，因为不满足单调性，那么它一定会使最大值更小或使最小值更大。不满足。

问题就转化成了求所有单调序列中最大值减最小值的差的和。但是这样来看查询和修改都比较麻烦。

想到差分，设 $d_i=a_i-a_{i-1}$，则区间修改就可以变为单点修改，即将 $d_{l-1}$ 加上 $x$，将 $d_r$ 减去 $x$。

然后是查询。我们注意差分的性质。如果 $d_i$ 为正数，即 $a_i-a_{i-1}> 0$，那么可以说明 $a_i>a_{i-1}$。根据不等式的传递性，我们得知一段连续的为正数的 $d$ 一定说明 $a$ 的这一段具有单调递增性。负数同理。

再者，有 $ans=|a_r-a_l|=\sum _ {i=l+1}^r |d_i|$，所以查询就变成了区间求和，可以使用线段树维护。对于 ``pushup``，我们需要分类讨论。因为同一个 $i$ 不能存在于 $2$ 个子序列中，而一个 $i$ 会关联上 $d_{i-1}$ 和 $d_{i+1}$，二者如果要合并就表示将两个序列合并在了一起，所以还要判断是否有单调性。

讲一讲 ``pushup`` 方面的实现，我们维护 $T_{x,0/1,0/1}$ 表示当前线段树的 $x$ 节点选与不选左右的 $d_i$ 的情况。对于其子树 $ls$ 和 $rs$，首先当它们没有相交后重复时都可以选。而如果重复了，即 $ls$ 的右边和 $rs$ 的左边都选了，我们就需要判断是否这个 $d_i$ 对应的两个 $a_j$ 是否同号，只有这样才能满足连续单调性，合并才是正确的。

其余细节可以参考清纯代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m, q, a[N];
struct node {
	int l, r, x;
} T[N << 2][2][2];
void pushup(int p) {
	for(int a1 = 0;a1 <= 1; ++a1) 
	for(int a4 = 0;a4 <= 1; ++a4) {
		T[p][a1][a4].x = -1e9;
		for(int a2 = 0;a2 <= 1; ++a2)
		for(int a3 = 0;a3 <= 1; ++a3) {
			if(a2 != 1 or a3 != 1 or (a[T[p << 1][0][0].r] * a[T[p << 1 | 1][0][0].l] >= 0))
				T[p][a1][a4].x = max(T[p][a1][a4].x, T[p << 1][a1][a2].x + T[p << 1 | 1][a3][a4].x);
		}
	}
}
void build(int p, int l, int r) {
	for(int a1 = 0;a1 <= 1; ++a1)
	for(int a2 = 0;a2 <= 1; ++a2) T[p][a1][a2].l = l, T[p][a1][a2].r = r;
	if(l == r) {
		T[p][1][1].x = abs(a[l]); 
		return ; 
	}
	int mid = l + r >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	pushup(p);
}
void update(int p, int k, int x) {
	if(T[p][0][0].l == T[p][0][0].r) {
		T[p][1][1].x = abs(a[k] += x);
		return ;
	}
	int mid = T[p][0][0].l + T[p][0][0].r >> 1;
	if(mid >= k) update(p << 1, k, x); 
	else update(p << 1 | 1, k, x);
	pushup(p);
}
signed main() {
	cin >> n >> q;
	for(int i = 1, x, lst = 0;i <= n; ++i) {
		scanf("%lld", &x);
		if(i != 1) a[i - 1] = x - lst;
		lst = x;
	}
	build(1, 1, n - 1);
	while(q--) {
		int l, r, x;
		scanf("%lld %lld %lld", &l, &r, &x);
		if(l - 1 >= 1) update(1, l - 1, x);
		if(r < n) update(1, r, -x);
		printf("%lld\n", T[1][1][1].x);
	}
	return 0;	
}
```

---

