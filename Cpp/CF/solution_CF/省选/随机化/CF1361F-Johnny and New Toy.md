# Johnny and New Toy

## 题目描述

Johnny 有一个新玩具。你可能已经猜到，这个玩具有点特别。玩具是一个长度为 $n$ 的排列 $P$，由 $1$ 到 $n$ 的数字组成，依次排列在一行上。

对于每个 $i$（$1 \leq i \leq n-1$），在 $P_i$ 和 $P_{i+1}$ 之间写有一个权值 $W_i$，这些权值构成了 $1$ 到 $n-1$ 的一个排列。此外，还有额外的权值 $W_0 = W_n = 0$。

规则定义了一个子区间 $[L, R]$ 是“好”的，当且仅当对于任意 $i \in \{L, L+1, \ldots, R-1\}$，都有 $W_{L-1} < W_i$ 且 $W_R < W_i$。对于这样的子区间，还定义 $W_M$ 为集合 $\{W_L, W_{L+1}, \ldots, W_{R-1}\}$ 的最小值。

现在游戏开始了。在一次操作中，玩家可以选择一个“好”的子区间，将其切分为 $[L, M]$ 和 $[M+1, R]$ 两部分，并交换这两部分。更具体地说，操作前该子区间的结构为：
$$
W_{L-1}, P_L, W_L, \ldots, W_{M-1}, P_M, W_M, P_{M+1}, W_{M+1}, \ldots, W_{R-1}, P_R, W_R
$$
操作后变为：
$$
W_{L-1}, P_{M+1}, W_{M+1}, \ldots, W_{R-1}, P_R, W_M, P_L, W_L, \ldots, W_{M-1}, P_M, W_R
$$
这样的操作可以执行多次（也可以不执行），目标是让排列 $P$ 的逆序对数量最小。

Johnny 的妹妹 Megan 觉得规则太复杂了，于是她想考考哥哥。她会选择一对下标 $X$ 和 $Y$，并交换 $P_X$ 和 $P_Y$（$X$ 可能等于 $Y$）。每次妹妹交换后，Johnny 都想知道，从当前的 $P$ 出发，经过若干次合法操作后，能得到的最小逆序对数是多少。

你可以假设输入是随机生成的。$P$ 和 $W$ 是独立且等概率的全排列，Megan 的每次询问也是独立且等概率地选择下标对。

## 说明/提示

考虑第一个样例。第一次询问后，$P$ 已经有序，因此逆序对数为 $0$。

第二次询问后，$P$ 变为 $[1, 3, 2]$，有一个逆序对，可以证明无法通过操作得到 $0$ 逆序对。

最后，$P$ 变为 $[2, 3, 1]$；我们可以对整个排列进行一次操作（整个区间本身是一个好子区间），结果为 $[1, 2, 3]$，逆序对数为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3 2 1
2 1
3
1 3
3 2
3 1```

### 输出

```
0
1
0```

## 样例 #2

### 输入

```
5
4 3 2 5 1
3 2 1 4
7
5 4
5 2
1 5
2 4
2 4
4 3
3 3```

### 输出

```
3
1
2
1
2
3
3```

# 题解

## 作者：jerry3128 (赞：1)

### 题目大意
- 给定由排列随机生成的分治树，分治树可以上每个节点可以交换左右儿子。
- 在随机交换两个值得情况下，求分治树先序遍历叶子节点的最小逆序对个数。

### solution
- 整体交换左右儿子发现对答案的影响只有跨越当前分治树节点的逆序对有影响，不会影响父亲节点、儿子节点的答案贡献。
- 所以对于每个分分治节点直接贪心考虑，如果交换后答案减小就直接交换。
- 即维护 $lval$、$rval$ 分别表示先走左左儿子、右儿子的答案，这个可以通过在每个节点开一颗动态开点线段树完成。
- 那么算法大体框架就出来了：
	- 对于分治树上每个节点开线段树维护 $lval$、$rval$，贪心选择交换儿子。
   - 交换两个值得时候就在分治树上暴力跳父亲，在线段树上插入删除，同时计算 $lval$、$rval$，如果 $rval > lval$ 直接交换左右儿子及信息即可。
- 考虑复杂度，首先是线段树有一只 $\log$。考虑分治树，题目当中明确表示：分治树基于一个随机排列生成、并且所有修改随机生成。
- 那么我们可以认为每一次询问的节点到达分治树根的距离期望为 $\log$。
- 那么我们算法复杂度为期望 $\mathcal O(n\log^{2}n)$，基于数据随机。

```
//ayanami保佑，夸哥保佑，狗妈保佑，MDR保佑，锉刀怪保佑，M99保佑，克爹保佑
#include<bits/stdc++.h>
using namespace std;
int p1=1000000,p2=0;
char buf[1000005],wb[1000005];
int gc() {
	if(p1>=1000000)fread(buf,1,1000000,stdin),p1=0;
	return buf[p1++];
}
#define gc getchar
#define Loli true
#define Kon xor true
long long getint() {
	long long ret=0,flag=1;
	char c=gc();
	while(c<'0'||c>'9') {
		if(c=='-')flag=-1;
		c=gc();
	}
	while(c<='9'&&c>='0') {
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=gc();
	}
	return ret*flag;
}
void pc(char x) {
	if(p2>=1000000)fwrite(wb,1,1000000,stdout),p2=0;
	wb[p2++]=x;
}
void wrt(long long x) {
	if(x<0)pc('-'),x=-x;
	int c[24]= {0};
	if(!x)return pc('0'),void();
	while(x)c[++c[0]]=x%10,x/=10;
	while(c[0])pc(c[c[0]--]+'0');
}
long long ans;
int n,m,w[200005],p[200005],wp[200005];
namespace Seg{
	struct node{int l,r,val;}v[800005];
	void build(int rt,int l,int r){
		v[rt].l=l,v[rt].r=r;
		if(l==r)return v[rt].val=w[l],void();
		int mid=(l+r)>>1;build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
		v[rt].val=min(v[rt<<1].val,v[rt<<1|1].val);
	}
	int ask(int rt,int l,int r){
		if(l<=v[rt].l&&v[rt].r<=r)return v[rt].val;
		int mid=v[rt<<1].r,res=0x3f3f3f3f;
		if(l<=mid)res=min(res,ask(rt<<1,l,r));
		if(mid<r)res=min(res,ask(rt<<1|1,l,r));
		return res;
	}
}
namespace S{
	int tot;
	struct node{int ls,rs,val;}v[80000005];
	void ins(int &rt,int p,int val,int L=1,int R=n){
		if(!rt)rt=++tot;
		v[rt].val+=val;
		if(L==R)return;
		int mid=(L+R)>>1;
		if(p<=mid)ins(v[rt].ls,p,val,L,mid);
		else ins(v[rt].rs,p,val,mid+1,R);
	}
	int ask(int rt,int l,int r,int L=1,int R=n){
		if(!rt||l<=L&&R<=r)return v[rt].val;
		int mid=(L+R)>>1,res=0;
		if(l<=mid)res+=ask(v[rt].ls,l,r,L,mid);
		if(mid<r)res+=ask(v[rt].rs,l,r,mid+1,R);
		return res;
	}
}
struct node{int ls,rs,lrt,rrt,fa;long long lval,rval;}v[200005];
int fa[200005];
int build(int l,int r,int prt){
	if(l>r)return 0;
	if(l==r)return fa[l]=fa[l+1]=l,v[l].fa=prt,v[l].ls=l,v[l].rs=l+1,l;
	int rt=wp[Seg::ask(1,l,r)];
	v[rt].fa=prt;
	v[rt].ls=l<rt?build(l,rt-1,rt):(fa[l]=rt,l);
	v[rt].rs=rt<r?build(rt+1,r,rt):(fa[rt+1]=rt,rt+1);
	return rt;
}
void REV(int x){swap(v[x].ls,v[x].rs),swap(v[x].lrt,v[x].rrt),swap(v[x].lval,v[x].rval);}
void INS(int pl,int val){
	ans-=v[fa[pl]].lval;
	if(pl==v[fa[pl]].ls)S::ins(v[fa[pl]].lrt,val,1),v[fa[pl]].lval+=S::ask(v[fa[pl]].rrt,1,val),v[fa[pl]].rval+=S::ask(v[fa[pl]].rrt,val,n);
	else                S::ins(v[fa[pl]].rrt,val,1),v[fa[pl]].rval+=S::ask(v[fa[pl]].lrt,1,val),v[fa[pl]].lval+=S::ask(v[fa[pl]].lrt,val,n);
	if(v[fa[pl]].lval>v[fa[pl]].rval)REV(fa[pl]);
	ans+=v[fa[pl]].lval,pl=fa[pl];
	while(v[pl].fa){
		ans-=v[v[pl].fa].lval;
		if(pl==v[v[pl].fa].ls)S::ins(v[v[pl].fa].lrt,val,1),v[v[pl].fa].lval+=S::ask(v[v[pl].fa].rrt,1,val),v[v[pl].fa].rval+=S::ask(v[v[pl].fa].rrt,val,n);
		else                  S::ins(v[v[pl].fa].rrt,val,1),v[v[pl].fa].rval+=S::ask(v[v[pl].fa].lrt,1,val),v[v[pl].fa].lval+=S::ask(v[v[pl].fa].lrt,val,n);
		if(v[v[pl].fa].lval>v[v[pl].fa].rval)REV(v[pl].fa);
		ans+=v[v[pl].fa].lval,pl=v[pl].fa;
	}
}
void DEL(int pl,int val){
	ans-=v[fa[pl]].lval;
	if(pl==v[fa[pl]].ls)S::ins(v[fa[pl]].lrt,val,-1),v[fa[pl]].lval-=S::ask(v[fa[pl]].rrt,1,val),v[fa[pl]].rval-=S::ask(v[fa[pl]].rrt,val,n);
	else                S::ins(v[fa[pl]].rrt,val,-1),v[fa[pl]].rval-=S::ask(v[fa[pl]].lrt,1,val),v[fa[pl]].lval-=S::ask(v[fa[pl]].lrt,val,n);
	if(v[fa[pl]].lval>v[fa[pl]].rval)REV(fa[pl]);
	ans+=v[fa[pl]].lval,pl=fa[pl];
	while(v[pl].fa){
		ans-=v[v[pl].fa].lval;
		if(pl==v[v[pl].fa].ls)S::ins(v[v[pl].fa].lrt,val,-1),v[v[pl].fa].lval-=S::ask(v[v[pl].fa].rrt,1,val),v[v[pl].fa].rval-=S::ask(v[v[pl].fa].rrt,val,n);
		else                  S::ins(v[v[pl].fa].rrt,val,-1),v[v[pl].fa].rval-=S::ask(v[v[pl].fa].lrt,1,val),v[v[pl].fa].lval-=S::ask(v[v[pl].fa].lrt,val,n);
		if(v[v[pl].fa].lval>v[v[pl].fa].rval)REV(v[pl].fa);
		ans+=v[v[pl].fa].lval,pl=v[pl].fa;
	}
}
int main() {
	n=getint();
	for(int i=1;i<=n;i++)p[i]=getint();
	for(int i=1;i<n;i++)wp[w[i]=getint()]=i;
	Seg::build(1,1,n-1),build(1,n-1,0);
	for(int i=1;i<=n;i++)INS(i,p[i]);
	m=getint();
	for(int i=1;i<=m;i++){
		int l=getint(),r=getint();
		DEL(l,p[l]),DEL(r,p[r]),swap(p[l],p[r]),INS(l,p[l]),INS(r,p[r]);
		wrt(ans),pc('\n');
	}
	fwrite(wb,1,p2,stdout);
	return Loli Kon;
}
```

---

## 作者：约瑟夫用脑玩 (赞：0)

没咋写过线段树合并，于是来写写这道水题。

首先观察 $W$ 的交换定义，显然的发现就是笛卡尔树可以交换左右子树进行逆序对贡献。

假设交换点 $x$ 的左右子树 $ls_x,rs_x$，那么 $ls_x,rs_x$ 子树内部的贡献不变，因为段整体交换。

同时 $x$ 子树以外的贡献不变，分别看 $x$ 子树左边和右边就会发现都没变。

所以边的贡献就只有 $ls_x,rs_x$ 互相的贡献，也就是本来的逆序对变成了正序对。

那么我们统计逆序对的个数，正序对就是所有对数减去逆序对数，贪心取两个中最小的即可。

两个子树互相的逆序对数直接上线段树合并，我们就会做没有修改的问题了。

~~由于我只想练习写线段树合并而不想练习线段树合并统计贡献，于是我使用了启发式统计贡献。~~

复杂度为 $O(n\log n)$，如果是启发式合并/统计贡献也可以做，复杂度是 $O(n\log^2n)$ 的。

空间复杂度由于后面要可持久化所以是 $O(n\log n)$ 的，启发式合并的话会是 $O(n\log^2 n)$，启发式统计贡献没有空间复杂度。

考虑修改，首先由于 $W$ 是随的，所以笛卡尔树树高是 $\log n$ 的。

直接对每个点的贡献都进行修改，发现就是看改的那个值有几个逆序对加上或减去即可，我们之前线段树合并的时候可持久化一下这里就可以直接用了。

由于询问不独立，于是每次还要修改，如果直接可持久化修改我就爆空间了，所以再开一棵动态开点线段树来维护询问的影响。

反正线段树部分都是 $O(\log n)$ 的，然后乘上修改的点数 $\log n$，询问复杂度 $O(q\log^2n)$。

~~空间复杂度也是 $O(q\log^2n)$ 的，我也不知道为什么动态开点线段树就没被卡空间了（~~

还有笛卡尔树随便建就行了，总复杂度 $O(n\log n+q\log^2n)$，我启发式所以是 $n\log^2n$ 的，但 CF 机子快也就过了。

[代码](https://www.luogu.com.cn/paste/l0rk8ahi)还是放一下。

---

