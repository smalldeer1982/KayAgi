# [USACO09HOL] Holiday Painting G

## 题目描述

To show their spirit for the holidays, the cows would like to paint a picture! Their picture will be represented as an R x C (1 <= R <= 50,000; 1 <= C <= 15) grid of unit squares, each of which is either 0 or 1. The grid rows are conveniently numbered 1..R; the columns are numbered 1..C.

Being pressed for time, the cows have asked their neighbors north of the border for help. Under the very helpful supervision of Canmuu the moose, they constructed a machine to throw paint at the picture in entire buckets! Beginning with all 0's in the picture grid, the machine splashes a certain paint color (either 0 or 1) over a

rectangle in the grid. In particular, Canmuu suggested that they perform Q (1 <= Q <= 10,000) operations; operation i consists of five integers R1\_i, R2\_i, C1\_i, C2\_i, and X\_i (1 <= R1\_i <= R2\_i <= R; 1 <= C1\_i <= C2\_i <= C; 0 <= X\_i <= 1), meaning that the cows will paint each unit square with a row index between R1\_i and R2\_i, inclusive, and a column index between C1\_i and C2\_i, inclusive, with color X\_i.

However, painting a picture like this is quite prone to mistakes. So Canmuu has enlisted you to determine, after each operation, the number of unit squares in the grid which are the correct color.

MEMORY LIMIT: 64 MB

TIME LIMIT: 1.5 seconds

为了表达假日的激情，奶牛们要画一幅巨大的画。

画布可以分成$R\times C$个方格，从上到下编为 $1$ 到 $R$ 行，从左到右编为 $1$ 到 $C$ 列。作画的颜色有两种，白色（用 $0$ 表示）或者黑色（用 $1$ 表示）。

由于时间紧迫，奶牛们不得不请教北面的邻居，卡门。卡门送给它们一台机器，一次操作只输入5个参数 $R1_i,R2_i,C1_i,C2_i,X_i$ $(1 \le R1_i \le R2_i \le R;1 \le C1_i \le C2_i \le C;0 \le X_i \le 1)$，把 $R1_i$ 行到 $R2_i$ 行，$C1_i$ 列到 $C2_i$ 列的一个大长方形涂成 $X_i$ 色。在所有操作还未进行的时候，画布是白色的。

奶牛们一共要进行 $Q$ 次操作。

因为这样的画法总要出些差错，所以奶牛们想请你算算，每一次操作过后，一共有多少个方格与它们的目标画里对应的方格是同色的。

## 说明/提示

The cows want to paint a picture of a holiday tree


After the first operation, the picture grid looks as follows:

000000000000000

000000000000000

000000000000000

000000000000000

011111111111110

011111111111110

011111111111110

011111111111110

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

000000000000000

There are 113 unit squares which match the corresponding square in the tree image; they are denoted below by an 'x' (the other bits are shown as they appear after the first paint splash):

0000000x0000000

000000xxx000000

00000xxxxx00000

0000xxxxxxx0000

0xx111111111xx0

0xxx1111111xxx0

0xx111111111xx0

0x11111111111x0

000xxxxxxxxx000

00xxxxxxxxxxx00

0xxxxxxxxxxxxx0

00xxxxxxxxxxx00

0xxxxxxxxxxxxx0

xxxxxxxxxxxxxxx

000000xxx000000

000000xxx000000

000000xxx000000


## 样例 #1

### 输入

```
17 15 10 
111111101111111 
111111000111111 
111110000011111 
111100000001111 
111000000000111 
111100000001111 
111000000000111 
110000000000011 
111000000000111 
110000000000011 
100000000000001 
110000000000011 
100000000000001 
000000000000000 
111111000111111 
111111000111111 
111111000111111 
5 8 2 14 1 
8 17 3 7 1 
4 5 10 15 0 
7 16 12 14 1 
2 17 13 14 0 
2 6 2 3 1 
13 14 4 8 1 
3 6 6 7 1 
1 16 10 11 0 
7 16 10 10 0 
```

### 输出

```
113 
94 
95 
91 
87 
93 
91 
87 
93 
93 
```

# 题解

## 作者：颓_废_人 (赞：3)

## 线段树？ 不用吧
还是要分成C个序列来处理\
我的思路是将每个序列分成k个颜色相同的块，然后每个块都算一下有几个满足要求就行了。\
具体就是用队列，存三个变量l,r,g,分别表示这个块的左端点，右端点和颜色，每次询问就过一遍，将要加入的一段颜色加入，再分类讨论原有块和加入块的位置关系保证一个点不出现在两个块里就行了。\
ps：为了提升运算的速度，要将队列中相邻的颜色一样的块合并。\
时间复杂度：俺也不知道，反正过了。\
代码略长（反正分类讨论写了一种情况就可以复制粘贴了）
```cpp
#include<bits/stdc++.h>
using namespace std;
int R,C,q,sum[16][50010],que[16][2][50010][3],len[16];
int main()
{
	scanf("%d%d%d",&R,&C,&q);
	for(int i=1;i<=R;i++)
	{
		getchar();
		for(int j=1;j<=C;j++)
		{
			bool tmp=getchar()-'0';
			sum[j][i]=sum[j][i-1]+tmp;
		}
	}
	for(int i=1;i<=C;i++)
	{
		que[i][0][1][0]=1;
		que[i][0][1][1]=R;
		que[i][0][1][2]=0;
		len[i]=1;
	}//一开始只有一个块
	for(int i=1;i<=q;i++)
	{
		bool nw=i%2;
		int x1,x2,y1,y2,kd;
		scanf("%d%d%d%d%d",&x1,&x2,&y1,&y2,&kd);
		for(int j=1;j<y1;j++)
		{
			for(int e=1;e<=len[j];e++)
			{
				que[j][nw][e][0]=que[j][!nw][e][0];
				que[j][nw][e][1]=que[j][!nw][e][1];
				que[j][nw][e][2]=que[j][!nw][e][2];
			}
		}
		for(int j=y2+1;j<=C;j++)
		{
			for(int e=1;e<=len[j];e++)
			{
				que[j][nw][e][0]=que[j][!nw][e][0];
				que[j][nw][e][1]=que[j][!nw][e][1];
				que[j][nw][e][2]=que[j][!nw][e][2];
			}
		}
		for(int j=y1;j<=y2;j++)
		{
			int tmp=0;
			for(int e=1;e<=len[j];e++)
			{
				bool hv=0;
				int l=que[j][!nw][e][0],r=que[j][!nw][e][1];
				if(l>=x1&&r<=x2) hv=1;//被要加入的块压住了就可以不管了
				if(x1==l)
				{
					hv=1;
					if(tmp!=0&&que[j][nw][tmp][2]==kd) que[j][nw][tmp][1]=x2;
					else
					{
						que[j][nw][++tmp][2]=kd;
						que[j][nw][tmp][1]=x2;
						que[j][nw][tmp][0]=x1;
					}
				}
				if(que[j][!nw][e][1]>=x1&&que[j][!nw][e][0]<x1)
				{
					hv=1;
					que[j][nw][++tmp][0]=que[j][!nw][e][0];
					que[j][nw][tmp][1]=x1-1;
					que[j][nw][tmp][2]=que[j][!nw][e][2];
					if(tmp!=0&&que[j][nw][tmp][2]==kd) que[j][nw][tmp][1]=x2;
					else
					{
						que[j][nw][++tmp][2]=kd;
						que[j][nw][tmp][1]=x2;
						que[j][nw][tmp][0]=x1;
					}
				}
				if(que[j][!nw][e][1]>x2&&que[j][!nw][e][0]<=x2)
				{
					if(tmp!=0&&que[j][nw][tmp][2]==que[j][!nw][e][2])
					{
						que[j][nw][tmp][1]=r;
						continue;
					}
					que[j][nw][++tmp][0]=x2+1;
					que[j][nw][tmp][1]=r;
					que[j][nw][tmp][2]=que[j][!nw][e][2];
					continue;
				}
				if(hv) continue;//以上是分类讨论
				if(tmp!=0&&que[j][!nw][e][2]==que[j][nw][tmp][2]) que[j][nw][tmp][1]=r;
				else
				{
					que[j][nw][++tmp][0]=l;
					que[j][nw][tmp][1]=r;
					que[j][nw][tmp][2]=que[j][!nw][e][2];
				}
			}
			len[j]=tmp;
		}
		int ans=0;
		for(int j=1;j<=C;j++)
		{
			for(int e=1;e<=len[j];e++)
			{
				int tmp=sum[j][que[j][nw][e][1]]-sum[j][que[j][nw][e][0]-1];
				if(que[j][nw][e][2]) ans+=tmp;
				else ans+=(que[j][nw][e][1]-que[j][nw][e][0]+1-tmp);
			}
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：中国飞鱼 (赞：2)

 _写了一晚上的题~~_ 

观察到列数只有15,可以想到对于每一列维护一颗线段树

**sum表示该区间与目标矩阵中该区间相同元素个数**

**lazy表示该区间应被修改成什么颜色**

**g即目标矩阵中该区间白色格子的个数**

显然一个区间的sum=区间长度-g(修改为0时) 或 g(修改为1时)

```
#define RG register
#include<cstdio>
using namespace std;
const int N=50005;
int n,m,q,X,Ans;
int a[N][16];
inline int read()
{
	RG int x=0,w=1;RG char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*w;
}
struct segment{
	int sum[N<<2],lazy[N<<2],g[N<<2];
	inline void Pushup(int rt){sum[rt]=sum[rt<<1]+sum[rt<<1|1];}
	void Build(int rt,int l,int r,int k){
		if(l==r)
		{
			sum[rt]=a[l][k]^1;
			g[rt]=a[l][k];
			return;
		}
		int mid=(l+r)>>1;
		Build(rt<<1,l,mid,k);
		Build(rt<<1|1,mid+1,r,k);
		Pushup(rt);
		g[rt]=g[rt<<1]+g[rt<<1|1];
	}
	inline void Pushdown(int rt,int s){//s即区间长度
		int t=lazy[rt];
		if(t==-1)return;
		if(!t)
		{
			sum[rt<<1]=(s-(s>>1))-g[rt<<1];
			sum[rt<<1|1]=(s>>1)-g[rt<<1|1];
		}
		else
		{
			sum[rt<<1]=g[rt<<1];
			sum[rt<<1|1]=g[rt<<1|1];
		}
		lazy[rt<<1]=lazy[rt<<1|1]=t;
		lazy[rt]=-1;
	}
	void Modify(int rt,int l,int r,int ll,int rr){
		if(ll<=l&&r<=rr)
		{
			if(X)sum[rt]=g[rt];
			else sum[rt]=r-l+1-g[rt];
			lazy[rt]=X;
			return;
		}
		Pushdown(rt,r-l+1);
		int mid=(l+r)>>1;
		if(ll<=mid)Modify(rt<<1,l,mid,ll,rr);
		if(rr>mid)Modify(rt<<1|1,mid+1,r,ll,rr);
		Pushup(rt);
	}
}T[16];
int main()
{
	n=read();
	m=read();
	q=read();
	RG char c;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			c=getchar();
			while(c!='0'&&c!='1')c=getchar();
			a[i][j]=c-'0';
		}
	for(int i=1;i<=m;i++)T[i].Build(1,1,n,i);
	RG int x1,x2,y1,y2;
	while(q--)
	{
		x1=read();
		x2=read();
		y1=read();
		y2=read();
		X=read();
		for(int i=y1;i<=y2;i++)T[i].Modify(1,1,n,x1,x2);
		Ans=0;
		for(int i=1;i<=m;i++)Ans+=T[i].sum[1];
		printf("%d\n",Ans);
	}
	return 0;
}
```

---

## 作者：Chtholly__Nota (赞：1)

## 题目:P2930 [USACO09HOL] Holiday Painting G
传送门 [P2930 [USACO09HOL] Holiday Painting G](https://www.luogu.com.cn/problem/P2930)

 蒟蒻的第一篇题解，求过 QAQ 感谢 @[critnos](https://www.luogu.com.cn/user/203623 "critnos")大佬的帮助。
## 正题 
 当我第一次看到这题的时候想到了维护 $15$ 个线段树，但是由于我比较懒，且时间不够，所以就打了一个暴力算法拿了 $49$ 分。
 
 思想就是对于每一次的修改如果上色后和原来相同那么就将贡献加一，反之亦然。统计目标图中 ``0`` 的个数为初始的相同值，每一次修改加上贡献并输出。
#### 代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;

int r,c,q;
int r1,r2,c1,c2,x;
int ans,cs;
int a[50005][20],b[50005][20];

int main() {
	cin>>r>>c>>q;
	for(int i=1; i<=r; i++) {
		string s;
		cin>>s;
		for(int j=1; j<=c; j++) {
			a[i][j]=s[j-1]-'0';
			if(a[i][j]==0) cs++;
		}
	}
	for(int i=1; i<=q; i++) {
		ans=0;
		scanf("%d%d%d%d%d",&r1,&r2,&c1,&c2,&x);
		for(int i=r1; i<=r2; i++) {
			for(int j=c1; j<=c2; j++) {
				int t=b[i][j];
				b[i][j]=x;
				if(a[i][j]==b[i][j] && b[i][j]!=t) ans++;
				if(a[i][j]!=b[i][j] && b[i][j]!=t) ans--;
			}
		}
		if(ans+cs<=0) {
			printf("%d\n",0);
			cs=0;
		} else {
			printf("%d\n",ans+cs);
			cs=ans+cs;
		}
	}
	return 0;
}
```
 但是由于代码中每一次输入都要进行 $(R2_i-R1_i) \times (C2_i-C1_i)$ 次操作，肯定是会 TLE 的，但是由于我不想写线段树，那该怎么办呢，灵光一闪，区间修改？~~我想起了珂朵莉~~，那就用珂朵莉树来写吧。
 
### 珂树思路：
图一开始全部为 ``0`` ，直接开 $C$ 个珂朵莉树维护每一行，将染色操作用珂朵莉树的推平操作实现，维护相同颜色数量。
 
每一行的操作都是一样的，所以在这里就假设只有一行，那么对于一行，假设其目标为 ``001101011`` ,先统计其 ``0`` 的个数为 $4$ ,次询问，第一次从 $1$ 到 $5$ 染成 ``1`` ，第二次从 $3$ 到 $8$ 染成 ``0`` ，第三次从 $4$ 到 $6$ 染成 ``1`` ，第四次从 $2$ 到 $5$ 染成 ``0`` 。

很显然可以看出当不进行操作的时候,相同的个数就是目标中 ``0`` 的个数。那么对于每一次操作。
 
假如是染成 ``1`` ，发现贡献应该是在当前图的这一操作段中为 ``0`` 且目标图中为 ``1`` 的个数 $-$ 当前图的这一操作段中为 ``0`` 且目标图中为 ``0`` 的个数。
 
假如是染成``1``，和上面相反，发现贡献应该是在当前图的这一操作段中为 ``1`` 且目标图中为 ``0`` 的个数 $-$ 当前图的这一操作段中为 ``1`` 且目标图中为 ``1``的个数。
 
那么对于当前操作段中 ``0`` 或 ``1`` 的个数可以在推平的时候统计，那么对于目标图中 ``0`` 或 ``1`` 的数量怎么办呢。
 
假设每一次都遍历，那么可能会超时（~~没试过~~ ，那么该怎么办呢。
 
仔细读题目，发现图中只可能又 ``1``或 ``0``，那么可以用前缀和来维护一段区间内 ``1``的个数 ，``1`` 的个数知道了 , ``0`` 还不好求吗？区间长度减去区间中 ``1`` 的个数就是区间中 ``0`` 的个数。

对于每一次操作将贡献加入答案中，答案初始为目标图中 ``0`` 的个数，输出。
 
现在，我们了解了思路，就可以轻松打出用珂朵莉树来解决这个题目的代码了。
 
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 定义节点结构体
struct node {
	int l, r;
	mutable int v;
	friend bool operator <(node a, node b) {
		return a.l < b.l;
	}
};

// 定义集合数组
set<node> s[16];
int mpp[50005][20], scc[50005][20], qz[20][50005];

// 分割函数，将区间[l, r]分割成[l, x-1]和[x, r]
auto split(int x, int bh) {
	auto it = s[bh].lower_bound({x, 0, 0});
	if (it != s[bh].end() && it->l == x)
		return it;
	it--;
	if (it->r < x)
		return s[bh].end();
	int l = it->l, r = it->r, v = it->v;
	s[bh].erase(it);
	s[bh].insert({l, x - 1, v});
	return s[bh].insert({x, r, v}).first;
}

// 分配函数，将区间[l, r]赋值为v并分别统计上一次是0，目标为1的个数，上一次是1，目标为0的个数，上一次是1，目标为1的个数，上一次是0，目标为0的个数
pair<pair<int,int>,pair<int,int> > assign(int l, int r, int v, int bh) {
	auto itr = split(r + 1, bh), itl = split(l, bh);
    int slyy=0,syyl=0,syyy=0,slyl=0;
	for(auto it=itl;it!=itr;it++){
        if(it->v==0){
            slyy+=qz[bh][it->r]-qz[bh][it->l-1];
			slyl+=it->r-it->l+1-qz[bh][it->r]+qz[bh][it->l-1];
        }
        if(it->v==1){
            syyl+=it->r-it->l+1-qz[bh][it->r]+qz[bh][it->l-1];
			syyy+=qz[bh][it->r]-qz[bh][it->l-1];
        }
	}
	s[bh].erase(itl, itr);
	s[bh].insert({l, r, v});
    return {{slyy,syyl},{syyy,slyl}};
}
int r, c, q;
int main() {
    int gl=0;
	scanf("%d%d%d", &r, &c, &q);
	for (int i = 1; i <= r; i++) {
		string st;
		cin >> st;
		for (int j = 0; j < c; j++) {
			mpp[i][j + 1] = st[j] - '0';//这里要注意，如果直接cin那么会读入错误，当时调了半天才发现，要一个一个读入或者用字符串读入，然后转成数字
            if(mpp[i][j+1]==0) gl++;
		}
	}
	for (int i = 1; i <= c; i++) {//前缀和
		for (int j = 1; j <= r; j++) {
			qz[i][j] = mpp[j][i] + qz[i][j-1];
		}
	}
	for (int i = 1; i <= c; i++) {//初始化
		s[i].insert({1, r, 0});
	}
	int c1, c2, r1, r2, x;
	long long ans;
	while (q--) {
		ans = 0;
		scanf("%d%d%d%d%d", &r1, &r2, &c1, &c2, &x);
		for (int i = c1; i <= c2; i++) {
			pair<pair<int,int>,pair<int,int> > tt=assign(r1,r2,x,i);
			if(x==1){
				ans+=tt.first.first-tt.second.second;//这一操作段中为0且目标图中为1的个数−当前图的这一操作段中为0且目标图中为0的个数
			}
			else{
				ans+=tt.first.second-tt.second.first;//这一操作段中为1且目标图中为0的个数−当前图的这一操作段中为1且目标图中为1的个数

			}
		}
		cout << ans+gl << "\n";
		gl=ans+gl;//将答案更新
	}
    return 0;
}
```

---

## 作者：houmy (赞：1)

## 题意简述
给定一个 $R \times C$ 的矩阵，初始为 $0$。$Q$ 次询问，每次将其中一个矩形改为 $0$ 或 $1$。求每次询问后和目标矩阵相同的元素个数。 

## 题解

前置知识：线段树

我们首先注意到，$C$ 非常小，只有 $15$，而 $R$ 很大。于是我们自然想到开 $C$ 棵独立的线段树，分别维护矩阵的 $C$ 列。

线段树的节点要维护这几个数值：

1. 这一个区间和目标矩阵吻合的元素的个数（`sgtree`）

2. 这一个区间目标矩阵 $0$（或 $1$，本题解中以 $0$ 为例）的个数（`num`）
3. 上一次赋值操作留下的 `lazytag`（`tag`）

接下来我会细说线段树的维护方法。（具体可以参考我的代码）

### 建树 build

注意到前文中的 `sgtree` 和 `num` 都是区间加和的操作，于是我们用类似线段树 1 这道题的方法维护。在每个叶子节点判断该节点对应的矩阵中的元素是否和目标矩阵的元素对应，如果对应将前文提到的 `sgtree` 和 `num` 都设为 $1$，否则都设为 $0$。注意我们还没有赋值操作，所以先将 `tag` 设为 $-1$。

另：建树之后 `num` 都不再改动，`num` 是静态的。

### 懒标记下传 pushdown

首先要特判一下对应节点的 `tag` 是不是 $-1$。如果是 $-1$，那么就不用管这个节点。

如果对应的 `tag` 是 $0$（即将区间设为 $0$）的操作，那么直接让子节点的 `sgtree` 等于 `num`，对应都是 $0$ 的情况，并下传 `tag`。否则就是设为 $1$ 的操作，将子节点的 `sgtree` 设为 `(r-l+1)-num`，也就是目标矩阵里不是 $0$ 的个数。

最后一定要记得把当前节点的 `tag` 设为 $-1$。

### 修改 update

向下递归修改。如果目前节点对应的区间在目标区间内，那么就用类似 `pushdown` 的方法更新目前节点的 `sgtree` 和 `tag`，否则就递归之后更新当前节点的 `sgtree`。**注意不要更新 `num`。**

### 查询 query

和查询区间加和的模板一样，当前区间在目标区间内直接返回当前节点的 `sgtree`，否则就向下递归查询。

注意 `query` 和 `update` 在向下查找的时候一定要先 `pushdown`。

### 一个小 trick

手打 $15$ 棵线段树实在非常困难，~~Ctrl+C/V 也同样困难~~。一个 trick 是，在所有的函数的参数里面加一个 `id`，来说明时在哪一棵树里面操作。

这样说可能有一点抽象，建议对照（但不要“借鉴”）代码理解。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,q;
int sgtree[20][200010],tag[20][200010],num[20][200010];
char tgt[50010][20];
void build(int id,int x,int l,int r){
    if(l==r){
        sgtree[id][x]=(tgt[l][id]=='0');
        tag[id][x]=-1;
        num[id][x]=(tgt[l][id]=='0');
        return;
    }
    int mid=(l+r)>>1;
    build(id,x<<1,l,mid);
    build(id,x<<1|1,mid+1,r);
    sgtree[id][x]=sgtree[id][x<<1]+sgtree[id][x<<1|1];
    num[id][x]=num[id][x<<1]+num[id][x<<1|1];
    tag[id][x]=-1;
}
void pushdown(int id,int x,int l,int r){
    if(tag[id][x]!=-1){
        int mid=(l+r)>>1;
        tag[id][x<<1]=tag[id][x<<1|1]=tag[id][x];
        if(tag[id][x]==0){
            sgtree[id][x<<1]=num[id][x<<1];
            sgtree[id][x<<1|1]=num[id][x<<1|1];
        }else{
            sgtree[id][x<<1]=(mid-l+1)-num[id][x<<1];
            sgtree[id][x<<1|1]=(r-mid)-num[id][x<<1|1];
        }
        tag[id][x]=-1;
    }
}
void update(int id,int x,int l,int r,int l2,int r2,int color){
    if(l2<=l&&r<=r2){
        if(color==0){
            sgtree[id][x]=num[id][x];
        }else{
            sgtree[id][x]=(r-l+1)-num[id][x];
        }
        tag[id][x]=color;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(id,x,l,r);
    if(l2<=mid)update(id,x<<1,l,mid,l2,r2,color);
    if(r2>mid)update(id,x<<1|1,mid+1,r,l2,r2,color);
    sgtree[id][x]=sgtree[id][x<<1]+sgtree[id][x<<1|1];
}
int query(int id,int x,int l,int r,int l2,int r2){
    if(l2<=l&&r<=r2){
        return sgtree[id][x];
    }
    int mid=(l+r)>>1;
    pushdown(id,x,l,r);
    int ans=0;
    if(l2<=mid)ans+=query(id,x<<1,l,mid,l2,r2);
    if(r2>mid)ans+=query(id,x<<1|1,mid+1,r,l2,r2);
    return ans;
}
int main(){
    cin>>r>>c>>q;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cin>>tgt[i][j];
        }
    }
    for(int j=1;j<=c;j++)build(j,1,1,r);
    // for(int i=1;i<=r;i++){
    //     for(int j=1;j<=c;j++){
    //         if(query(j,1,1,r,i,i))cerr<<tgt[i][j];
    //         else cerr<<char(tgt[i][j]^1);
    //     }
    //     cerr<<endl;
    // }
    // cerr<<endl;
    while(q--){
        int r1,r2,c1,c2,color;
        cin>>r1>>r2>>c1>>c2>>color;
        for(int i=c1;i<=c2;i++){
            update(i,1,1,r,r1,r2,color);
        }
        int ans=0;
        for(int i=1;i<=c;i++){
            ans+=query(i,1,1,r,1,r);
        }
        // for(int i=1;i<=r;i++){
        //     for(int j=1;j<=c;j++){
        //         if(query(j,1,1,r,i,i))cerr<<tgt[i][j];
        //         else cerr<<char(tgt[i][j]^1);
        //     }
        //     cerr<<endl;
        // }
        // cerr<<endl;
        cout<<ans<<endl;
    }
}
```

## 写在最后

最后我想说一说一个很大的坑（我第一次因为这个喜提没过样例加上 WA+RE 32 分）。按照我的思路，线段树维护的是每一列的若干行，而我的 `tgt` 数组（记录目标矩阵）记录的是每一行的若干列，在一开始导致：

1. `build` 的时候树实际上是建的有问题的，和 `update` 以及 `query` 的方向不一致

2. 我的 `tgt` 数组两个维度开反了，喜提 `RE`。

3. 在修复了前两个 BUG 后，我的 `build` 函数里面的逻辑有一点绕。

如果我有机会重构代码，下一次我会把 `tgt` 数组读入的时候就翻转一下（`cin>>tgt[j][i]`）,这样代码会美观一点。

感谢阅读！

---

## 作者：critnos (赞：1)

显然是每次操作后统计贡献。

看到 $C\le 15$ 果断选择维护 $C$ 个同一类数据结构支持这个操作。

然后就变成了序列上的操作。

用珂朵莉树做相当简单。对于一个连续段，统计其与“目标画”的不同的数的数量。若此连续段为 $1$ 则为目标这段区间中 $0$ 的个数，反之亦然。

维护目标的前缀和即可。

每次推平的时候减去区间中连续段的贡献，再加上推平后的贡献即可。

复杂度是对的。每次 split 增加了常数个元素，每次遍历后删除此元素，所以每个元素最多被访问一次。总访问复杂度 $\log q$。

总复杂度 $RC+qC\log q$，跑得挺快的。

---

## 作者：fy0123 (赞：1)

来一发题解~

其实是一道比较水的线段树（虽然本人一开始炸了好几次。。。

我们需要维护的是某个区间内符合要求的格子个数，首先需要一个前缀和的数组，s[i][j][0/1]表示的是第i列前j行，0的个数/1的个数。

然后对于每个区间由于我们是把区间覆盖成全0或全1，因此就可以用s数组来维护这个线段树，维护一下区间和就好了，要加懒标记。

详见代码：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#define mid (l+r)/2
#define lc o<<1
#define rc o<<1|1
using namespace std;

inline int read()
{
    char ch = getchar(); int x = 0, flag = 0;
    while (!isdigit(ch)){ if (ch == '-') flag = 1; ch = getchar(); }
    while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
    return flag ? -x : x;
}

inline void write(int a){ if (a >= 10) write(a/10); putchar('0'+a%10); }
inline void writeln(int a){ write(a); puts(""); }

const int N = 50010, M = 20;
int n, m, q, ans = 0;
char a[N][M];
int s[M][N][2];

struct Tree{
    int c[N<<2], lazy[N<<2];
}T[M];

inline void build(int id, int o, int l, int r)
{
    if (l == r){
        T[id].c[o] = s[id][l][0]-s[id][l-1][0];
        return;
    }
    build(id, lc, l, mid);
    build(id, rc, mid+1, r);
    T[id].c[o] = T[id].c[lc] + T[id].c[rc];
}

inline void pushdown(int id, int o, int l, int r)
{
    int t = T[id].lazy[o];
    T[id].c[lc] = s[id][mid][t] - s[id][l-1][t];
    T[id].c[rc] = s[id][r][t] - s[id][mid][t];
    T[id].lazy[lc] = t;
    T[id].lazy[rc] = t;
    T[id].lazy[o] = -1;
}

inline void update(int id, int o, int l, int r, int x, int y, int v)
{
    if (x <= l && y >= r){
        T[id].c[o] = s[id][r][v] - s[id][l-1][v];
        T[id].lazy[o] = v;
        return;
    }
    if (T[id].lazy[o] != -1) pushdown(id, o, l, r);
    if (x <= mid) update(id, lc, l, mid, x, y, v);
    if (y > mid) update(id, rc, mid+1, r, x, y, v);
    T[id].c[o] = T[id].c[lc] + T[id].c[rc];
}

int main()
{
    n = read(), m = read(), q = read();
    for (int i = 1; i <= n; i ++) scanf("%s", a[i]+1);
    for (int i = 1; i <= m; i ++)
        for (int j = 1; j <= n; j ++){
            s[i][j][0] = s[i][j-1][0] + (a[j][i] == '0');
            s[i][j][1] = s[i][j-1][1] + (a[j][i] == '1');
        }
    for (int i = 1; i < M; i ++)
        for (int j = 1; j < N<<2; j ++) T[i].lazy[j] = -1;
    for (int i = 1; i <= m; i ++) build(i, 1, 1, n);
    while (q --){
        int r1, r2, c1, c2, x;
        r1 = read(), r2 = read(), c1 = read(), c2 = read(), x = read();
        for (int i = c1; i <= c2; i ++) update(i, 1, 1, n, r1, r2, x);
        ans = 0;
        for (int i = 1; i <= m; i ++) ans += T[i].c[1];
        writeln(ans);
    }
    return 0;
}
```

---

## 作者：Hate_and_Love (赞：0)

一开始没注意数据范围~

可以发现列最大只有 15。

并且我们修改的是一个矩形。

那么就是一列列修改并且统计答案。

这里就可以用线段树，对每列建树，然后更新统计答案。

具体怎么统计，就是因为每次都是将一个区间内的数改成 1 或 0 ，那么我们先统计出每个区间的标准 1 和 0 个数。

那么改成哪个就是哪个为相同的答案。

然后注意一些细节就行了


```cpp
// Author: levil
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N = 5e4+5;
const int M = 1e6+5;
const LL Mod = 1e9+7;
#define rg register
#define pi acos(-1)
#define INF 1e9
#define CT0 cin.tie(0),cout.tie(0)
#define IO ios::sync_with_stdio(false)
#define dbg(ax) cout << "now this num is " << ax << endl;
namespace FASTIO{
    inline LL read(){
        LL x = 0,f = 1;char c = getchar();
        while(c < '0' || c > '9'){if(c == '-') f = -1;c = getchar();}
        while(c >= '0' && c <= '9'){x = (x<<1)+(x<<3)+(c^48);c = getchar();}
        return x*f;
    }
    void print(int x){
        if(x < 0){x = -x;putchar('-');}
        if(x > 9) print(x/10);
        putchar(x%10+'0');
    }
}
using namespace FASTIO;
void FRE(){/*freopen("data1.in","r",stdin);
freopen("data1.out","w",stdout);*/}

int n,m,q;
string a[N];
struct Node{int L,r,sum1,sum0,val,tag;}node[20][N<<2];
void Pushup(int id,int idx)
{
    node[id][idx].val = node[id][idx<<1].val + node[id][idx<<1|1].val;
}
void Pushdown(int id,int idx)
{
    if(node[id][idx].tag != -1)
    {
        int tag = node[id][idx].tag;
        if(tag == 0)
        {
            node[id][idx<<1].val = node[id][idx<<1].sum0;
            node[id][idx<<1|1].val = node[id][idx<<1|1].sum0;
        }
        else
        {
            node[id][idx<<1].val = node[id][idx<<1].sum1;
            node[id][idx<<1|1].val = node[id][idx<<1|1].sum1;
        }
        node[id][idx<<1].tag = node[id][idx<<1|1].tag = tag;
        node[id][idx].tag = -1;
    }
}
void build(int L,int r,int id,int idx)
{
    node[id][idx].L = L,node[id][idx].r = r;
    node[id][idx].tag = -1;
    if(L == r)
    {
        if(a[L-1][id-1] == '0') node[id][idx].sum0++,node[id][idx].val = 1;
        else node[id][idx].sum1++;
        return ;
    }      
    int mid = (L+r)>>1;
    build(L,mid,id,idx<<1);
    build(mid+1,r,id,idx<<1|1);
    node[id][idx].sum0 = node[id][idx<<1].sum0 + node[id][idx<<1|1].sum0;//上限
    node[id][idx].sum1 = node[id][idx<<1].sum1 + node[id][idx<<1|1].sum1;
    Pushup(id,idx);
}
void update(int L,int r,int id,int idx,int val)
{
    if(node[id][idx].L >= L && node[id][idx].r <= r)
    {
        if(val == 0) node[id][idx].val = node[id][idx].sum0;
        else node[id][idx].val = node[id][idx].sum1;
        node[id][idx].tag = val;
        return ;
    }
    int mid = (node[id][idx].L + node[id][idx].r)>>1;
    Pushdown(id,idx);
    if(mid >= L) update(L,r,id,idx<<1,val);
    if(mid < r) update(L,r,id,idx<<1|1,val);
    Pushup(id,idx);
}
int main()
{
    IO;CT0;
    cin >> n >> m >> q;
    for(rg int i = 0;i < n;++i) cin >> a[i];
    for(rg int j = 0;j < m;++j) build(1,n,j+1,1);
    while(q--)
    {
        int r1,r2,c1,c2,z;
        cin >> r1 >> r2 >> c1 >> c2 >> z;
        for(rg int i = c1;i <= c2;++i) update(r1,r2,i,1,z);
        int ans = 0;
        for(rg int i = 1;i <= m;++i) ans += node[i][1].val;
        cout << ans << endl;
    }
    system("pause");    
}
```

---

