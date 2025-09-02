# 「CROI · R2」在相思树下 II

## 题目背景

真的要继续吗？

真的不想放弃吗？

真的有用吗？

## 题目描述

狐妖们在涂山上举办了一场淘汰制比赛，现在已知第 $i$ 名参赛者实力为 $i$，每场比赛都会有两名选手决出胜负，胜者进入下一轮，为了尽量让实力较强和较弱的参赛选手均有获胜的可能，涂山雅雅设计了一种特殊的比赛规则。

具体而言，一共有 $2^n$ 位选手报名参加淘汰赛，每场比赛一定按照两种规则之一进行。

- 规则一：参加比赛的两名选手实力较强者胜出。
- 规则二：参加比赛的两名选手实力较弱者胜出。

现在涂山雅雅会对你进行 $m$ 次询问，对于一个每场比赛规则确定但选手分布未知的签表，每次询问第 $a$ 名选手能否闯入第 $b$ 轮比赛，若能则输出 `Yes`，否则输出 `No`。特殊地，若某位选手夺得了冠军，则我们称其闯入了第 $n+1$ 轮比赛。

下图展示了一张每场比赛规则确定，但选手分布未知的签表示例。其中，每场比赛下标注 $\max$ 表示该场比赛按照规则一进行，实力较强者胜出；标注 $\min$ 表示该场比赛按照规则二进行，实力较弱者胜出。

![](https://cdn.luogu.com.cn/upload/image_hosting/e727l3wf.png)

## 说明/提示

**【样例解释】**

样例中的签表与题目描述中的图示一致。

若要使第六位选手进入第二轮，或使第七位选手进入第三轮，均可按照如下顺序安排选手位置：$\{1,2,3,4,7,8,5,6\}$。具体比赛情况如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/v5sgk5ru.png)

显然不存在一种可能的情况使得第八位选手进入第四轮（即夺得冠军）。

**【数据范围】**

**本题采用捆绑测试**。

- Subtask 0（20 points）：$n \leq 3$，$m \leq 20$。
- Subtask 1（10 points）：对于所有询问，$b \leq 2$。
- Subtask 2（10 points）：保证每场比赛的规则均为规则一。
- Subtask 3（20 points）：保证第 $i$ 轮中的所有比赛比赛规则均相同。
- Subtask 4（40 points）：无特殊限制。

对于所有数据，$1\leq a\leq 2^n$，$1\leq b\leq n+1$，$1 \leq 2^n,m \leq 10^6$。

## 样例 #1

### 输入

```
3 3
2
2 1
2 1 2 1
6 2
7 3
8 4```

### 输出

```
Yes
Yes
No```

# 题解

## 作者：Ratio_Y (赞：21)

一道比 T2 简单的 T3。

## 思路
我们发现比赛流程图的形状是一棵完全二叉树，而题目所求的出每一轮次的进入范围限制也是从它的子比赛更新而来的，因此可以按类似线段树建图的方法直接处理出每一轮次的范围，最后 $O(1)$ 查询即可。

我们先设 $l_i$，$r_i$ 分别为第 $i$ 个节点中至少有 $l_i$ 个数比符合条件的值 $x$ 小，至少有 $r_i$ 个数比 $x$ 大。

放一张图形式化一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/00tgn06g.png)

~~（图丑，轻喷）~~

我们以一个按照规则二比赛的节点举例：假设胜者为 $x$，那么比赛后即拼凑后的范围块长右图那样。

更新时，首先已知有 $r_1$ 个数需要比 $x$ 大，有 $r_2$ 个数需要比 $y$ 大，同时要满足 $x<y$，所以最终这一节点的 $r_i$ 值应为 $r_1+r_2+1$；

同时需要至少有 $l_1$ 个数比 $x$ 小，$l_2$ 个数比 $y$ 小，由获胜者为 $x$ 我们可以推出 $l_1<l_2$，即 $x$ 能取到更小的值，所以在这个节点中的左边界就是 $x$ 子节点的左边界，但这是在假设 $x$ 获胜的情况，所以真正更新时的 $l_i$ 应等于 $\min(l_1,l_2)$。

按规则一比赛的节点同理，大家可以自己手动模拟下，最终转移式为：

$$l_i=l_{lson}+l_{rson}+1$$

$$r_i=\min(r_{lson}+r_{rson})$$

实现方面，由于二叉树的性质，我们根据节点长度 $len$ 可知该节点所在的层数为 $\log \,len$。题目中只需要进入某一层即可，所以整层的范围就是该层所有块的左右边界值分别的最小值。

## 细节处理
每节点左右边界初始为 $0$ 即无限制，每层左右边界初始为 $+\infty$ 以便赋值。

更新左右边界时要先递归到叶子结点再更新，因为每节点长度是从大到小的，而我们需要由小节点推大节点。

题目询问中为轮数，转化为层数需要在输入时减去 $1$。

## Code：
```
#include<bits/stdc++.h>

using namespace std;

const int Ratio=0;
const int N=1e6+5;
const int maxx=2e9;
int n,m;
int v[N<<1],sl[N<<1],sr[N<<1],L[25],R[25];

namespace Wisadel
{
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	#define mid ((l+r)>>1)
	void Wbuild(int rt,int l,int r)
	{
		if(l==r) return;
		int ceng=log2(r-l+1);// log2 自动向下取整 
		Wbuild(ls,l,mid),Wbuild(rs,mid+1,r);
		
		if(v[rt]==1) sl[rt]=sl[ls]+sl[rs]+1,sr[rt]=min(sr[ls],sr[rs]);
		else sl[rt]=min(sl[ls],sl[rs]),sr[rt]=sr[ls]+sr[rs]+1;
		// 判断节点类型并进行更新 
			
		L[ceng]=min(L[ceng],sl[rt]),R[ceng]=min(R[ceng],sr[rt]);
		// 更新每层范围 
	}
	short main()
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=(1<<n)-1;i++) scanf("%d",&v[i]);
		for(int i=1;i<=n;i++) L[i]=maxx,R[i]=maxx;
		Wbuild(1,1,(1<<n));
		
		for(int i=1;i<=m;i++)
		{
			int a,b;scanf("%d%d",&a,&b);b-=1;
			if(a>L[b]&&(1<<n)-a>=R[b]) printf("Yes\n");
			// 判断是否在范围内
			// (1<<n)-a>=R[b] 即为 (1<<n)-a+1>R[b] 
			else printf("No\n");
		}
		return Ratio;
	}
}
int main(){return Wisadel::main();}
```

---

## 作者：Kao_Potato (赞：9)

一道挺有趣的题目，也不算很难。

首先对于任意一个叶子结点，任意一个数都能够到达。

对于规则一（强者胜出），可以理解为要比某些数大才可以晋级。

对于规则二（弱者胜出），可以理解为要比某些数小才可以晋级。

那么可以考虑对于树中的每一个节点，维护达到当前节点需要比某些数大的数量和比某些数小的数量。父节点的这两个值可以通过两个子节点的值来合并得到。

对于取 $\max$ 操作，需要比父节点小的数的数量为需要比两儿子小的数的数量之和加一。加一是因为赢家一定比输家大，输家也会比父节点小。

$$smaller[fa]=smaller[son1]+smaller[son2]+1$$

而对于需要更大的数的数量，由于两儿子谁胜出都对结果无影响，故选择范围更大更优的那个。所以更大的数的数量越少越好，即需要更大的数的数量是两儿子中的较小值。

$$bigger[fa]=\min(bigger[son1],bigger[son2])$$

取 $\min$ 操作同理。

那么对于每一个询问，只需要查询目标数中是否在某一层任意一个节点的范围内即可。

预处理的时间复杂度为 $O(n \log n)$，$n$ 为选手数量，即叶子结点数量。理论上询问的时间复杂度较高，容易被卡，但实际跑起来还是很快的，想要更严谨可以对每一层开一个前缀和数组，用差分的方法将每一层的总区间范围合并到数组里，这样预处理时间仍为 $O(n \log n)$，查询就只需 $O(1)$ 了。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N=2000005;   //注意要开1e6两倍的空间，树非叶子节点还有这么多个 
int pn,qn;
struct Tree{
	int bn,sn,o;   //bn为需要的更大的数的数量，sn为需要的更小的数的数量，o为规则类型 
}t[N];
void yee(int now,int ceng){
	if(ceng>pn){
		return;   //最后一层bn和sn显然均为0，无需修改，直接返回 
	}
	yee(now*2,ceng+1);
	yee(now*2+1,ceng+1);
	if(t[now].o==2){   //规则二的合并 
		t[now].bn=t[now*2].bn+t[now*2+1].bn+1;
		t[now].sn=min(t[now*2].sn,t[now*2+1].sn);
	}else{   //规则一的合并 
		t[now].sn=t[now*2].sn+t[now*2+1].sn+1;
		t[now].bn=min(t[now*2].bn,t[now*2+1].bn);
	}
}
int main(){
	scanf("%d%d",&pn,&qn);
	for(int i=1;i<(1<<pn);i++){   //注意题目中给出规则类型的顺序与树编号的顺序相同 
		scanf("%d",&t[i].o);   //直接按顺序读入即可 
	}
	yee(1,1);
	for(;qn>0;qn--){
		int now,ceng,x=0;
		scanf("%d%d",&now,&ceng);
		for(int i=(1<<(pn-ceng+1));i<(1<<(pn-ceng+2));i++){   //注意位运算的优先级较低，不记得就都打上括号 
			if(now>t[i].sn && (1<<pn)-now>=t[i].bn){   //比当前数大和比当前数小的数的数量均符合要求
				//注意边界条件，是否有等号 
				x=1;
				break;
			}
		}
		if(x==1){
			printf("Yes\n");
		}else{
			printf("No\n");
		}
	}
	return 0;
}
```

---

## 作者：jr_linys (赞：9)

没打月赛，听到机房有人骂这题来看了下。  
想了好一会，感觉这题怎么样都得蓝起步吧。

维护一名选手从初始 $i$ 位置向上爬到高度 $d$ 的限制 $a/b_{i,d}$，表示要安排的实力比他小/大的选手的最少数量。

把操作搬到比赛（线段树）上，一个节点维护区间 $[l,r],mid=\frac{l+r}{2}$。  
若节点为 $\min$:  
- $a_{i,d}=a_{i,d-1}$
- $i\in[l,mid],b_{i,d}=b_{i,d-1}+1+\min\limits_{j=mid+1}^r b_j$
- $i\in(mid,r],b_{i,d}=b_{i,d-1}+1+\min\limits_{j=l}^{mid} b_j$

若节点为 $\max$:  
- $i\in[l,mid],a_{i,d}=a_{i,d-1}+1+\min\limits_{j=mid+1}^r a_j$
- $i\in(mid,r],a_{i,d}=a_{i,d-1}+1+\min\limits_{j=l}^{mid} a_j$
- $b_{i,d}=b_{i,d-1}$

考虑查询，要求 $a<x,x+b\le n$，则 $a<x\le n-b$。  
对比赛树上每一层开一个差分数组就好了。

比赛树有 $\log_2 n$ 层，每层 $O(n)$，时间复杂度 $O(n\log_2 n)$。  
~~然而没处理第一场比赛挂了好几发~~
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
template<class T>void Min(T &a,T b){if(a>b) a=b;}
template<class T>void Max(T &a,T b){if(a<b) a=b;}
const int N=1e6,L=__lg(N)+1;
int n,n2,m,op[N+5],f[L][N+5];
//         操作    差分数组
pii s[N+5];//限制a,b
pii dfs(int p,int l,int r,int d){
	if(l==r) return {0,0};
	int m=(l+r)>>1;
	pii L=dfs(p<<1,l,m,d-1),R=dfs(p<<1|1,m+1,r,d-1),ans={n2,n2};
	if(op[p]==1){
		for(int i=l;i<=m;++i)	s[i].first+=R.first+1;
		for(int i=m+1;i<=r;++i) s[i].first+=L.first+1;
	}else{
		for(int i=l;i<=m;++i)	s[i].second+=R.second+1;
		for(int i=m+1;i<=r;++i) s[i].second+=L.second+1;
	}
	for(int i=l;i<=r;++i){
		Min(ans.first,s[i].first),Min(ans.second,s[i].second);
		++f[d][s[i].first+1],--f[d][n2-s[i].second+1];
	}
	return ans;//返回区间的最优限制
}

int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m,n2=1<<n;
	for(int i=1;i<n2;++i) cin>>op[i];
	dfs(1,1,n2,n);
	f[0][0]=1;//记得处理第一场比赛啊
	for(int i=0;i<=n;++i) for(int j=1;j<=n2;++j) f[i][j]+=f[i][j-1];
	while(m--){
		int a,b;cin>>a>>b;
		cout<<(f[b-1][a]>0?"Yes\n":"No\n");
	}
}
```

---

## 作者：sail_with_pleasure (赞：5)

### Subtask 0

直接暴力模拟即可。

### Subtask 1

我们发现所有选手都能够进入第一轮。而对于第二轮，我们发现只有对于全部都是规则一或者全部都是规则二的情况略微特殊一些，剩下的情况也是所有选手都能进入第二轮。即全是规则一时只有一号选手无法进入第二轮，全是规则二时只有最后一位选手无法进入第二轮，特判一下就可以解决。

### Subtask 2

若均为规则一，显然每一轮比赛剩下的选手实力会越来越强，强的选手留在最后一定没有问题。这时我们将所有弱的分在相邻位置（$\{1,2,3...n\}$ 这样排布）会使闯进某一轮的最弱选手尽可能弱，可得到规律闯进第 $i$ 轮的选手最弱为 $2^{i-1}$ 号，所有比他强的选手也都可以进入这一轮。

### Subtask 3

与正解不同之处仅在于省略了同一轮比赛相互比较结果的过程，思路与正解相同，故参照下文即可。

### Subtask 4

正解采用类似于二分答案的思路，但与二分无关。

我们先考虑夺得冠军的选手可能编号的最大值。若编号最大值为 $x$，则所有编号小于 $x$ 的选手可视作编号 $0$，编号大于等于 $x$ 的选手可视作编号 $1$。问题转化为最少需要多少个编号 $1$ 使得编号 $1$ 能够夺得冠军。对于规则一，比赛双方只要有一方为编号 $1$ 即可;对于规则二，比赛双方编号必须全部为 $1$。从第一轮往上采用类似于树形 dp 的模式即可求出答案。可能夺得冠军的选手编号最小值也同理可求。

接下来证明可能夺得冠军的选手的编号为一段连续的区间。我们在求最大值时发现，所有编号大于等于 $x$ 的选手只要任意排布在 dp 所得的编号 $1$ 所在位置，最终夺得冠军的一定为 $x$ 号选手。最小值同理，而分别对最大值和最小值进行 dp 时，规则一和规则二恰好相反，所以一定存在签表上的一个位置使得夺得冠军的最小和最大编号选手在此位置均可能得到冠军。而所有大于最小编号小于最大编号的选手在此位置时，一定可以通过选手的调换使得其按照最小编号或最大编号一种情况靠拢，结论得证。

通过上述讨论可知，若想知道冠军的所有可能编号，将最小编号和最大编号通过树形 dp 求出即可。我们发现在树形 dp 的过程中我们也可以将每一轮中的各场比赛所有可能的参赛选手编号求出，故分别单独统计每一轮次的最小编号和最大编号即可预处理出所有的答案，在提问时直接回答便可解决本题。

代码如下：
```
#include<bits/stdc++.h>
using namespace std; 
const int N=4000000;
int n,m,f[N],l[N],r[N],a[N],ansl[N],ansr[N],aa,bb;  
void sc(int s,int c){
	if(c==n){
		if(a[s]==1)r[s]=1,l[s]=2;
		else l[s]=1,r[s]=2;
		ansl[n-c+2]=min(ansl[n-c+2],l[s]);
		ansr[n-c+2]=min(ansr[n-c+2],r[s]);
		return;
	}
	sc(s*2,c+1);
	sc(s*2+1,c+1);
	if(a[s]==1)r[s]=min(r[s*2],r[s*2+1]),l[s]=l[s*2]+l[s*2+1];
	else l[s]=min(l[s*2],l[s*2+1]),r[s]=r[s*2]+r[s*2+1];
	ansl[n-c+2]=min(ansl[n-c+2],l[s]);
	ansr[n-c+2]=min(ansr[n-c+2],r[s]);
	return;
}
int main(){
	//freopen("tree22.in","r",stdin);
	//freopen("tree22.out","w",stdout);
	cin>>n>>m;
	f[0]=1;
	for(int i=1;i<=n;i++){
		f[i]=f[i-1]*2;
		ansl[i]=1e9;
		ansr[i]=1e9; 
	}
	ansl[n+1]=1e9;
	ansr[n+1]=1e9;
	for(int i=1;i<=f[n]-1;i++){
		scanf("%d",&a[i]);
	}
	sc(1,1);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&aa,&bb);
		if(bb==1||(aa>=ansl[bb]&&aa<=f[n]-ansr[bb]+1))printf("Yes\n");
		else printf("No\n"); 
	}
	return 0;
}
```

---

## 作者：lsc72 (赞：4)

首先，我们定义该比赛为一颗二叉树，父节点为子节点的获胜结果（后面泛称为**胜利位**）子节点则称为**比赛位**。
    
 对于规则 1 ,实力较强者胜出，进入胜利位的选手的范围一定在两个比赛位的范围之间（比赛位的选手比赛后进入胜利位），而选手可以任意组合,两个比赛位可选选手的范围的最大值若在，一定可以进入胜利位，所以胜利位的选手范围的最大值就确定了，即 $ r_f=\max(r_l,r_r) $ 。
    
至于左边界，举个例子，两个范围为 $1$ 到 $2^n$ 的比赛位，在规则 1 的约束下，除了 $1$ 选手，所有选手都可以进入胜利位，所以胜利位的左边界为 $2$  。

那么再普通一点，这次我们忽略右边界，设一个比赛位的左边界为 $a$ ，另一个左边界为 $b$ ，且  $a<b$ 。  所以胜利位选手的范围一定是要大于 $a$ 的， $a$ 是最小值，也就是说要安排 $a-1$ 个实力小于 $a$ 的选手在先前和 $a$ 比赛才能让 $a$ 到达这个比赛位来让 $a$ 被 $b$ 击败，然而 $b$ 也要经过 $b-1$ 个实力小于它的才能到这个位置.然而他们的要击败的垫脚石却有重复，所以实际上要安排击败 $a+b-1$ 个选手才能让胜利位的选手实力最小，最小值就是 $a+b$ 。其实有 $a+b-1$ 个选手都在递归的左右比赛中被击败，所以总结来说就是 $ l_f=l_l+l_r $ 。
    
规则二也是同理。
    
至于具体的实现，先处理每个位置的选手范围，从叶节点（第一场比赛）开始逐层向上，时间复杂度为 $\mathcal{O}(n2^n)$ 。因为给出的是 $2^n$ 的范围，所以我们设 $k=2^n$ ， $k\leq10^6$ 所以时间复杂度就变为 $\mathcal{O}(klogk) $ ，可以接受，再统计每一层最大的可能的范围，对于每个询问 $\mathcal{O}(1)$ 回答即可。
    
作为蓝题似乎有点简单？如有问题或建议，欢迎指出，我会及时修改。
    
最后附上代码，里面还有较为详细的具体解释:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r,gui; //范围左边界，范围右边界，与比赛规则
};
vector<node> ceng[25];
int cmin[25],cmax[25];
int n,m,g,k;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); 
	cout.tie(NULL);
	for (int i=0;i<=24;i++) cmin[i]=1e8; //每一层允许的选手能力最小值
	for (int i=0;i<=24;i++) cmax[i]=0; //每一层允许的选手能力最大值
	cin>>n>>m;
	k=pow(2,n); //选手个数
	for (int j=1;j<=k;j++){
		node p;
		p.l=1; p.r=k; //最底层初始为最大范围
		ceng[n].push_back(p);
	}
	for (int i=0;i<n;i++){
		int y=pow(2,i);
		for (int j=1;j<=y;j++){
			node p;
			cin>>p.gui;
			ceng[i].push_back(p);
		}
	}
	for (int i=n-1;i>=0;i--){
		for (int j=0;j<ceng[i].size();j++){
			if (ceng[i][j].gui==1){
              			//规则1
				ceng[i][j].l=ceng[i+1][j*2].l+ceng[i+1][j*2+1].l;//左边界要求提升
				ceng[i][j].r=max(ceng[i+1][j*2].r,ceng[i+1][j*2+1].r);//右边界取最小
			}
			else{
              			//规则2
				ceng[i][j].l=min(ceng[i+1][j*2].l,ceng[i+1][j*2+1].l);//左边界取最小
				ceng[i][j].r=ceng[i+1][j*2].r+ceng[i+1][j*2+1].r-k-1;//右边界要求提升（值下降）
			}
			cmin[i]=min(cmin[i],ceng[i][j].l);
			cmax[i]=max(cmax[i],ceng[i][j].r);
          		//求每一层最大范围
		}
	}
	while (m--){
		int a,b;
		cin>>a>>b;
		if (b==1||a>=cmin[n-b+1]&&a<=cmax[n-b+1]) cout<<"Yes\n"; //判断
		else cout<<"No\n";
	}
	return 0; 
}
```

---

## 作者：封禁用户 (赞：4)

**不简单！！！不简单！！！**（好一道正常的蓝题~）  
我们需要知道，在某一轮中，你能够取得（在**这一轮**中获胜）的上界，下界是多少。  
在取 $\min$ 和取 $\max$ 状态下，**这一局**能够取得的上界下界是不同的。
$$\min:\\
[l,r] = [\min(l + l'),r + r' - 1]$$
$$\max:\\
[l,r] = [l + l',\max(r , r') + 2^{i - 1}]$$
而**整轮**的上下界就简单了：
$$[L,R] = [\min(L,l),\max(R,r)]$$
注意！判断时判断内容为：（请读者自证）
$$L[b] \le a \le R[b] + 2 ^ {n} - 2 ^ {b - 1}$$
**AC CODE（位运算版）**（无笔记）
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,l[1 << 20],r[1 << 20],v[1 << 19],L[21],R[21];
int main() {
    cin>>n>>m;
	for(int i = 1;i < (1 << n);i++){
	    cin >> v[i];
	}
	for(int i = (1 << n);i < (2 << n);i++){
	    l[i] = 1;
	    r[i] = 1;
	}
	L[1] = 1;
	R[1] = 1 << n;
	for(int i = 1;i <= n;i++){
		L[i + 1] = 1 << n;
		R[i + 1] = 1;
		for(int j = (1 << (n - i));j < (1 << (n + 1 - i));j++){
			if(v[j] == 1){
				l[j] = l[j << 1] + l[j << 1|1];
				r[j] = max(r[j << 1],r[j << 1|1])+(1<<(i-1));
			}else{
				l[j] = min(l[j << 1],l[j << 1|1]);
				r[j] = r[j << 1] + r[j << 1|1] - 1;
			}
			L[i + 1] = min(L[i + 1],l[j]);
			R[i + 1] = max(R[i + 1],r[j]);
		}
	}
	for(int i = 1;i <= m;i++){
		int a,b;
		cin >> a >> b;
		if(L[b] <= a && a <= R[b] + (1 << n) - (1 << b - 1)){
		    cout << "Yes" << endl;
		}else{
		    cout << "No" << endl;
		}
	}
    return 0;
}	
```
**AC CODE（正常版本）**~~（十分正常）~~（不一定能过，但能更好理解（详细笔记见此））
```cpp
#include <bits/stdc++.h>
using namespace std;
int maxn = 1e6 + 10;
int maxx = 1e7 + 10;
int n,m,l[maxx],r[maxx],v[maxn],L[30],R[30];//l表示这一个规则的赢取下界，r表示这一规则的赢取上界，L表示这一轮的赢取下界，R表示这一轮的赢取上界
int main() {
    cin>>n>>m;
	for(int i = 1;i < (pow(2,n));i++){
	    cin >> v[i];//第几轮的第几个规则
	}
	for(int i = (pow(2,n));i < (pow(2,n + 1));i++){
	    l[i] = 1;
	    r[i] = 1;//初始化 * 1
	}
	L[1] = 1;
	R[1] = 1 << n;//初始化 * 2
	for(int i = 1;i <= n;i++){
		L[i + 1] = 1 << n;
		R[i + 1] = 1;//初始化 * 3
		for(int j = (pow(2,n - i));j < (pow(n,n + 1 - i));j++){
			if(v[j] == 1){//取max的情况的边界
				l[j] = l[j * 2] + l[j * 2 + 1];
				r[j] = max(r[j * 2],r[j * 2 + 1])+(pow(2,i - 1));
			}else{//取min的情况的边界
				l[j] = min(l[j * 2],l[j * 2 + 1]);
				r[j] = r[j * 2] + r[j * 2 + 1] - 1;
			}
			L[i + 1] = min(L[i + 1],l[j]);//更新整轮的边界
			R[i + 1] = max(R[i + 1],r[j]);//记得+1！！
		}
	}
	for(int i = 1;i <= m;i++){
		int a,b;
		cin >> a >> b;
		if(L[b] <= a && a <= R[b] + (pow(2,n)) - (pow(2,b - 1))){//判断是否在此轮区间内
                /*(pow(2,n)) - (pow(2,b - 1)):一个类似前缀和的玩意*/
		    cout << "Yes" << endl;
		}else{
		    cout << "No" << endl;
		}
	}
    return 0;//好习惯
}	
```
（感谢[李子奕](https://www.luogu.com.cn/user/197616)大佬）

---

## 作者：TipherethB (赞：3)

# [洛谷P10767](https://www.luogu.com.cn/problem/P10767)
其他题解已经讲的很清楚了，这篇主要讲讲如何拼好分。
## Subtask 0
### 主要思想
$n$ 和 $m$ 都很小，考虑穷举法，然后模拟比赛过程。我用的随机化数组，当然也可以一个个枚举。

### 核心代码
```cpp
if (sub == 0) {
	for (int i = 1; i <= pow(2ll, n); i++) p[i] = i;
	for (int i = 1; i <= pow(2ll, n); i++) ans[i] = 1;//初始化
	for (int i = 1; i <= 150010; i++) {
		int l = pow(2ll, n);
		shuffle(p+1, p+1+l, rng);//随机化数组
		for (int i = 1; i <= pow(2ll, n); i++) sum[1][i] = p[i];
		for (int i = 2; i <= n + 1; i++) {
			for (int j = 1; j <= pow(2ll, (n + 1ll - i)); j++) {
				if (a[n-i+2][j] == 1) {
					sum[i][j] = max(sum[i-1][j*2-1], sum[i-1][j*2]);
					ans[sum[i][j]] = max(ans[sum[i][j]], i);
				}
				if (a[n-i+2][j] == 2) {
					sum[i][j] = min(sum[i-1][j*2-1], sum[i-1][j*2]);
					ans[sum[i][j]] = max(ans[sum[i][j]], i);
				}
			}
		}//模拟，如果按照规则能获胜就更新答案
	}
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		if (y > ans[x]) cout << "No\n";
		else cout << "Yes\n";//输出
	}
}
```
## Subtask 1
### 主要思想
$b \le 2$，明显可以推出一个性质：如果没有一场比赛为比谁更弱，则最弱的进不了第 $2$ 轮；如果没有一场比赛为比谁更强，则最强的进不了第 $2$ 轮；其余人两轮都能进，所以特判即可。

### 核心代码
```cpp
if (sub == 1) {
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		if (cnt == 0 && x == pow(2ll, n) && y == 2) cout << "No\n";
		if (cnt == pow(2ll, n)-1 && x == 1 && y == 2) cout << "No\n";
		//特判，cnt为规则1的数量
		else cout << "Yes\n";
	}
}
```
## Subtask 2
### 主要思想
比赛全都是比谁更强，所以实力弱的一定进不了后面的比赛。手算一下可以发现在第 $i$ 轮最弱的人至弱是所有人中第 $2^{y-1}$ 弱的，判断即可。

### 核心代码
```cpp
if (sub == 2) {
	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		if (pow(2ll, y-1) > x) cout << "No\n";
		else cout << "Yes\n";
	}
}
```
~~这测试点怎么一个比一个简单~~
## Subtask 3
和正解区别不大，直接看正解吧。
## 正解
用类似于线段树的东西维护每个选手在某一轮比他强和比他弱的选手的最小值。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1000010;
int n, m, x, y;

struct node{
	int l;
	int r;
	int op;
} g[N<<2];

void _work(int a, int b) {
	if (b > n) return;
	_work((a<<1), b+1);
	_work((a<<1)+1, b+1);
	if (g[a].op == 1) {
		g[a].l = g[(a<<1)].l + g[(a<<1)+1].l + 1;
		g[a].r = min(g[(a<<1)].r, g[(a<<1)+1].r);
	} else {
		g[a].r = g[(a<<1)].r + g[(a<<1)+1].r + 1;
		g[a].l = min(g[(a<<1)].l, g[(a<<1)+1].l);
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i < (1<<n); i++) cin >> g[i].op;
	_work(1, 1);
	while (m--) {
		int flag = 0;
		cin >> x >> y;
		for (int i = (1<<(n-y+1)); i < (1<<(n-y+2)); i++) {
			if (x > g[i].l && (1<<n) - x >= g[i].r) {
				flag = 1;
				break;
			}
		}
		if (flag) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
}
```

---

## 作者：Hisy (赞：0)

## 分析
首先，这一棵树是高度为 $n$ 的严格二叉树。

考虑设 $dpl$ 和 $dpr$ 这两个 dp 数组：
- $dpl_i$ 表示保守起见，在第 $i$ 层能够活下来的比 $x$ 较小的数量。
- $dpr_i$ 表示保守起见，在第 $i$ 层能够活下来的比 $x$ 较大的数量。

接下来又是分类讨论。

考虑取 $\max$：
- 根节点两个子节点一定较小，加上其中一个一定更小，则 $dpl_{i}=dpl_{lson(i)}+dpl_{rson(i)}+1$。
- 根节点两个子节点其中一定有一个更小，则 $dpr_{i}=\min(dpr_{lson(i)},dpr_{rson(i)})$。

考虑取 $\min$：
- 根节点两个子节点一定较大，加上其中一个一定更大，则 $dpr_{i}=dpr_{lson(i)}+dpr_{rson(i)}+1$。
- 根节点两个子节点其中一定有一个更大，则 $dpl_{i}=\min(dpl_{lson(i)},dpl_{lson(i)})$。

考虑如何确定 dp 顺序。很明显，只有 $lson$ 和 $rson$ 的答案出来了才能 dp，所以考虑 dfs。将其延伸到最深处然后依次向上递进。

对于每一个 $a$，有 $a-1$ 个比 $a$ 小的，要求 $dpl_{i}\le a-1$。有 $n-a$ 个比 $a$ 大的，要求 $dpr_{i}\ge n-a$。
## 细节
- 由于深度从 $0$ 开始，所以输入的 $b$ 要减一。
- 要开两倍空间。dfs 和线段树的 build 很相似，要开两倍空间。
- 不是所有的 $dpl$ 和 $dpr$ 都要赋为 $\infty$，不然叶子节点变成 $\infty$ 全 WA 哭都没地方哭。
## 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 1000001<<1
#define MAXM 26
using namespace std;
int n,m,v[MAXN],x[MAXN],y[MAXN],dpl[MAXM],dpr[MAXM];
void dfs(int root,int l,int r){
	if(l==r){
		return;
	}
	int k=log2(r-l+1);
	int mid=(l+r)>>1;
	dfs(root<<1,l,mid);
	dfs(root<<1|1,mid+1,r);
	if(v[root]==1){
		x[root]=x[root<<1]+x[root<<1|1]+1;
		y[root]=min(y[root<<1],y[root<<1|1]); 
	}else{
		y[root]=y[root<<1]+y[root<<1|1]+1;
		x[root]=min(x[root<<1],x[root<<1|1]);
	}
	dpl[k]=min(dpl[k],x[root]);
	dpr[k]=min(dpr[k],y[root]);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<(1<<n);++i){
		scanf("%d",&v[i]);
	}
	fill(dpl+1,dpl+n+1,INT_MAX);
	fill(dpr+1,dpr+n+1,INT_MAX);
	dfs(1,1,1<<n);
	while(m--){
		int a,b;
		scanf("%d %d",&a,&b);
		--b;
		if(dpl[b]<=a-1&&(1<<n)-a>=dpr[b]){
			puts("Yes");
		}else{
			puts("No");
		}
	}
	return 0;
}
```

---

