# [ARC162C] Mex Game on Tree

## 题目描述

给定一棵有 $N$ 个顶点的有根树，顶点编号为 $1$ 到 $N$。顶点 $1$ 是根，对于每个 $i\ (2\leq i \leq N)$，顶点 $i$ 的父节点为 $P_i$。

树上的部分顶点上写有 $0$ 到 $N$ 之间的整数。这些信息由数列 $A=(A_1,A_2,\ldots,A_N)$ 给出，若 $A_i\neq -1$，则表示顶点 $i$ 上写有整数 $A_i$；若 $A_i=-1$，则表示顶点 $i$ 上没有写整数。

Alice 和 Bob 进行游戏。Alice 先手，双方轮流操作，直到所有顶点都被写上整数。每次操作可以选择一个尚未写整数的顶点，并在其上写一个 $0$ 到 $N$ 之间的整数。

操作结束后，对于每个顶点 $v$，定义 $f(v)$ 为“在顶点 $v$ 的子树中（包括 $v$ 本身），没有被写下的最小非负整数”。

若存在某个顶点 $v$ 满足 $f(v)=K$，则 Alice 获胜，否则 Bob 获胜。请判断在双方都采取最优策略的情况下，谁会获胜。

有 $T$ 组测试数据，请分别作答。

## 说明/提示

## 限制

- $1\leq T\leq 10^3$
- $2\leq N\leq 10^3$
- $0\leq K\leq N$
- $1\leq P_i < i\ (2\leq i\leq N)$
- $-1\leq A_i\leq N\ (1\leq i\leq N)$
- 所有输入的数均为整数
- 所有测试数据中 $N$ 的总和不超过 $2\times 10^3$

## 样例解释 1

对于第 $1$ 组测试数据，Alice 可以在顶点 $2$ 上写 $0$，无论 Bob 如何操作，都有 $f(2)=2$，因此 Alice 获胜。对于第 $2$ 组测试数据，Bob 可以通过合理选择写入的整数，使得不存在 $f(v)=4$ 的顶点，因此 Bob 获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
4 2
1 1 2
-1 -1 3 1
6 4
1 2 2 1 3
-1 -1 -1 -1 -1 -1```

### 输出

```
Alice
Bob```

# 题解

## 作者：_•́へ•́╬_ (赞：7)

## 思路

如果存在一个子树已经被填满，且 $\operatorname{mex}$ 已经是 $K$，那么 Alice 胜。

如果存在一个子树只剩一个空位，且存在一个数，填了之后 $\operatorname{mex}$ 为 $K$，那么 Alice 胜。

其他情况都是 Bob 胜。

如果你不能理解上面的判定为啥是对的，我可以再给你一个结论：Bob 填的所有数都一定恰好为 $K$。这样可以对【$\operatorname{mex}$ 为 $K$】这个判定条件进行最大程度的破坏。

所以，如果有两个空位，那就肯定破坏掉了。

## code

```cpp
#include<stdio.h>
#include<bitset>
#define N 1009
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	bool t=0;char c=nc();for(;c<'0'||'9'<c;t|=c=='-',c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());if(t)x=-x;
}
int t,n,m,f[N],x[N],cnt[N];bitset<N>a[N];
struct __readt__{inline __readt__(){read(t);}}_readt___;
main()
{
	read(n);read(m);for(int i=1;i<n;++i)read(f[i]),--f[i];
	for(int i=0;i<n;read(x[i++]));
	for(int i=0;i<n;cnt[i]=0,a[i++].set());
	for(int i=n-1;i>=0;--i)
	{
		if(~x[i])a[i][x[i]]=0;
		else++cnt[i];
		if(!cnt[i])if(a[i]._Find_first()==m){printf("Alice\n");goto nxt;}
		if(cnt[i]==1)if(a[i]._Find_first()==m||
			a[i]._Find_next(a[i]._Find_first())==m){printf("Alice\n");goto nxt;}
		if(i)a[f[i]]&=a[i],cnt[f[i]]+=cnt[i];
	}
	printf("Bob\n");
	nxt:if(--t)main();
}
```



---

## 作者：Lucky_Xiang (赞：3)

# 题目

[ARC162C](https://www.luogu.com.cn/problem/AT_arc162_c)

# 思路

我们考虑 Alice 会在哪一个子树上获胜。 获胜子树必须满足以下条件：

1. 子树中的数字没有 $k$。
2. 子树中空结点的数量不少于缺少的数字的数量。
3. 在 Alice 填完所有空结点之前，Bob 不会来捣乱。

定义“可能的获胜子树”为满足 1、2 号条件的子树。

只要 Bob 在一个节点填入 $k$，从这个节点到根的所有节点都不能成为获胜子树的根节点。这样他可以同时破坏多个可能的获胜子树，我们考虑把这种情况化简。

假如 $u$ 和 $v$ 所代表的子树都是可能的获胜子树，而 $v$ 在 $u$ 的子树中。那么，只要 Bob 破坏了 $v$ 就能破坏 $u$，因此 Alice 肯定会放弃 $u$ 而保住 $v$。这样就缩小了可能的获胜子树的范围，使他们的子树互不相交。

因此，原问题被转化为了以下问题：给定若干个非负整数，Alice 可以把一个数字减一，Bob 可以删除一个数，两人轮流操作，Alice 先手，只要任何一个数变成了 $0$ 则 Alice 获胜，否则 Bob 获胜。

其中，每个“数”对应每个可能的获胜子树中空结点的个数。

可以分情况讨论：

- 若所有数中存在 $0$ 或 $1$，则 Alice 获胜。
- 若所有数中不存在 $0$ 或 $1$，只要 Alice 减小哪个数，Bob 就删除哪个数，因此 Bob 获胜。

因此，我们只需判断是否存在可能的获胜子树只有不超过一个空结点即可。因为 $N$ 只有 $10^3$，我们可以暴力枚举每个子树的信息，复杂度 $O(N^2)$。如果这题升级为 $N\le10^5$，那就可以考虑用 dsu on tree 维护，复杂度 $O(N \log N)$。

# 代码

[Code](https://atcoder.jp/contests/arc162/submissions/42837792)

---

## 作者：SafariMo (赞：1)

[Luogu Link](https://www.luogu.com.cn/problem/AT_arc162_c)

考虑 Bob 的最优策略。

先说结论：Bob 一定会不断填 $k$。

证明：

- 如果 Bob 填的数字 $<k$ 则对 Alice 填的数没有影响甚至更优。
- 如果 Bob 填的数字 $>k$ 则对 Alice 填的数没有影响。
- 如果 Bob 填的数字 $=k$ 则 Alice 填任何数也无法将该树的父节点的 $\operatorname{mex}$ 值设为 $k$。

证毕。

问题转化成了这样：

Alice 必须在 $\le 1$ 次操作后完成否则会被 Bob 破坏。

实现过程很简单。

如果一个节点的子树 $\operatorname{mex}$ 为 $k$ 或操作一次可以使 $\operatorname{mex}$ 为 $k$，则 Alice 必胜。

[Code](https://netcut.cn/p/0f9f6108e4d4d392)

---

## 作者：wangshulin (赞：0)

# 前言
一道诈骗题。
# 思路
首先不难发现，Bob 的最优策略一定是填上颜色 $k$，因为一个点的子树中有 $k$ 之后，它的 $\operatorname{mex}$ 一定不为 $k$，进而可以知道，在一个点的子树中，如果只有一个空位，那么 Alice 还可能一击必胜，但是如果有大于等于两个空位，那么 Bob 必定能占领其中的一个使得 Alice 无法得逞，所以就按照以上方法判断即可。
# 代码

```cpp
#include<stdio.h>
#include<algorithm>
#include<string.h>
const int N=1005;
struct node{
	int x,y,nxt;
}p[2*N];
int Q,n,k,x,y,cnt,cdfn,h[N],col[N],ccol[N],dfn[N],rnk[N],bot[N];
bool f;
void in(int x,int y){
	p[++cnt].x=x,p[cnt].y=y;
	p[cnt].nxt=h[x],h[x]=cnt;
}
void dfs(int x){
	dfn[x]=++cdfn,rnk[cdfn]=x;//dfn 为 dfs 序，rnk 为 dfn 转编号
	for(int k=h[x];k;k=p[k].nxt){
		int y=p[k].y;
		dfs(y);
	}
	bot[x]=cdfn;//子树中 dfn 最大的
}
int main(){
	scanf("%d",&Q);
	while(Q--){
		memset(h,cnt=cdfn=0,sizeof(h));
		scanf("%d%d",&n,&k);
		for(int i=2;i<=n;i++){
			scanf("%d",&x);
			in(x,i);
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&col[i]);
			if(col[i]==-1) col[i]=n+1;
		}
		dfs(1);
		f=false;//false 为 Bob 胜利
		for(int i=1;i<=n;i++){
			memset(ccol,0,sizeof(ccol));
			for(int j=dfn[i];j<=bot[i];j++){//小技巧，通过 dfs 序来遍历子树
				ccol[col[rnk[j]]]++;
			}
			if(ccol[k]||ccol[n+1]>1) continue;//空位大于一个或者已经有 k
			int s=0;
			for(int i=0;i<k;i++){//让 k 成为 mex 的阻碍是 0->k-1 的颜色有一些没有
				if(!ccol[i]) s++;
			}
			if(ccol[n+1]==1){//一个空位 
				if(s<=1) f=true;//一个空位且再填上一个原来没有的颜色就可以让 mex 变成 k
			}else{//没有空位
				if(!s) f=true;//如果没有空位且本来 mex 就为 k
			}
		}
		if(f) printf("Alice\n");
		else printf("Bob\n");
	}
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

可以发现若 Bob 在某个节点填了值 $K$，那么会直接导致其根链上的所有节点均不可能满足要求。

因此若某个节点的子树内有不小于两个空位，那么 Alice 一定无法使该子树满足要求。

若某节点子树内有一个空位且可以通过填上这一空位使其合法，那么 Alice 可以在第一次操作中操作该节点进而胜利。

若某节点子树内不存在空位且 mex 值合法，那么 Alice 胜利。

反之若 Alice 操作某个空位，Bob 只需要找到与这个空位的根链交集最多的空位并填写 $K$ 即可。可以发现 Bob 选择的节点一定可以覆盖当前状态下 Alice 选择的节点的根链上所有子树内有空位的节点，进而 Bob 必胜。

---

