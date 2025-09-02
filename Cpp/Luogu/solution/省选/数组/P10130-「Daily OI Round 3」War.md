# 「Daily OI Round 3」War

## 题目背景

《赤壁之战》是一款开放世界冒险游戏，这意味着从你踏入提瓦特的第一刻起，只要合理规划自己的体力，不论翻山越岭、还是横渡江河，总有办法见到新的风景。

## 题目描述

有 $n$ 条船，船编号为 $1$ 至 $n$。每条船上有 $m$ 个士兵，士兵编号为 $1$ 至 $m$。

开始时，有若干组船由铁索相连。具体的关系给出如下：

给出 $s$ 组关系，形如 $l_1,r_1,l_2,r_2$，表示 $\forall k \in [0,r_1-l_1]$，第 $l_1+k$ 条船与第 $l_2+k$ 条船相连，保证 $r_1-l_1+1=r_2-l_2+1$ 且 $l_1 < l_2$。

保证 $\forall p \in [1,n]$，最多存在一组关系使得 $l_2 \le p \le r_2$。

然后有 $q$ 个操作，操作如下（操作按照时间先后顺序编号为 $1 \sim q$）：

操作 $1$：向编号为 $p$ 的船的 $[L,R]$ 区间的士兵发射一支火箭。这样操作之后，这个区间的所有士兵都会着火。由于铁锁连环的缘故，所有与 $p$ 直接相连或间接相连的船的 $[L,R]$ 区间的士兵都会着火。注意，士兵可能着火多次。

操作 $2$：撤回编号为 $p$ 的操作，保证这个操作必定是操作 $1$。**保证不会多次撤回同一个操作，并且以后的询问都不考虑已经撤销的操作所带来的影响。**

操作 $3$：询问船 $p$ 上区间为 $[L,R]$ 的士兵是否全部着火。如果全部着火请输出 `Yes`，否则输出 `No`。

## 说明/提示

#### 【样例解释 #1】

首先给出了两条关系式，第一条表示了 $1$ 与 $2$，$2$ 与 $3$，$3$ 与 $4$，$4$ 与 $5$，$5$ 与 $6$ 的船是相连的。第二条表示了 $7$ 与 $8$，$8$ 与 $9$，$9$ 与 $10$ 的船是相连的。

第一个操作向第 $4$ 条船的 $1$ 到 $5$ 号士兵发射火箭，因为 $1$ 到 $6$ 号船是相连的，所以 $1$ 到 $6$ 号船上的 $1$ 到 $5$ 号士兵都着火了。

第二个操作询问第一条船的 $2$ 到 $3$ 号是否着火。显然着火了，所以输出 `Yes`。

第三个操作撤回了第一个操作，所以所有士兵操作后都没有着火。

第四个操作询问第一条船的 $2$ 到 $3$ 号是否着火。显然没有着，所以输出 `No`。

第五个操作将十号船的 $[2,7]$ 士兵着火，第六个操作将九号船的 $[3,6]$ 着火。然后第七个操作撤回了第六个操作。注意：目前，第七到十号船的 $[2,7]$ 的士兵是着火的。

第八号操作将七号船的 $[8,13]$ 着火，第九个操作询问是否 $[2,12]$ 全部着火。显然此时已经全部着火了。

#### 【数据范围】

对于全部数据保证：$1 \le n\leq 10^9$，$1 \le m\leq 5\times 10^5$，$0 \le q\leq 10^5$，$0 \le s\leq 200$。

## 样例 #1

### 输入

```
10 20 2 9
1 5 2 6
7 9 8 10
1 4 1 5
3 6 2 3
2 1
3 6 2 3
1 10 2 7
1 9 3 6
2 6
1 7 8 13
3 8 2 12```

### 输出

```
Yes
No
Yes```

## 样例 #2

### 输入

```
10 10 2 10
1 1 2 2
1 1 8 8
1 2 1 8
1 6 7 8
1 8 7 8
1 9 6 7
3 8 3 3
2 4
1 5 7 8
3 3 3 3
3 6 3 3
2 3```

### 输出

```
Yes
No
No```

# 题解

## 作者：xs_siqi (赞：3)

考虑把这个问题转化为线段树区间加+区间询问最小值。如果最小值为 $0$ 那就肯定有人没着火，如果大于 $0$ 了那肯定都着火了。




把原来的线段树重复利用一下。这样就变成了一个 区间加+区间覆盖+区间最小值线段树。

我们注意到一个性质：对于每组 $l_2,r_2$ 不相交。也就是说，一个点往前直接相连的边有且仅有一条。

然后我们发现这个东西其实是一个树形结构，所以我们在每次操作和询问的时候只要在根节点打标记与询问就可以了。

暴力找根是 $O(n)$ 的复杂度。总复杂度就是 $O(nq)$ 了。

然后接下来会有一个部分分的想法：对于每个船我完全可以直接大力并查集维护它们是不是在同一个连通块内。因为 $n$ 只有 $10^5$ 所以我最多并查集十万个点对吧。然后我可以对连通块进行一个标记和询问。


然后，我们发现找根完全可以优化成 $m$ 级别的。

对于区间重复的情况，我可以直接跳过这个重复的区间，直接跳到不重复的区间里。这个东西可以推一个数学式子表示我要往前跳多少。然后由于这棵树深度最多只有 $m$，所以我最多肯定只跳 $m$ 次。

但是这样因为询问 $q$ 个点，理论上我最多可能找到 $q$ 个根节点，那这样空间稳稳爆炸。

所以，我们可以把操作全部离线下来，然后把每个相同根节点的操作按顺序排序往下做，当这个根节点的所有操作做完之后，重复利用这个线段树即可。

这题其实暑假就出完了，只能说 Daily OI 挺能鸽的，隔壁出题组一周四个题直接交审核了。

```cpp

#include<bits/stdc++.h>
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
const int maxn=5e5+5;
int n,m,s,q,tot,x[maxn],y[maxn],cs,l1[maxn],op[maxn],k[maxn],ans[maxn];
struct edge{int l1,r1,l2,r2;}a[maxn];
struct node{int L,R,p,op,id;}Q[maxn];
struct tree{
	int t[maxn*4],lz[maxn*4],lz2[maxn*4];
	void pu(int rt)<%t[rt]=min(t[ls],t[rs]);%>
	void pd(int rt){
		if(lz2[rt])
			t[ls]=t[rs]=lz[ls]=lz[rs]=0,
			lz2[ls]=lz2[rs]=1,lz2[rt]=0;
		if(lz[rt]!=0)
			t[ls]+=lz[rt],t[rs]+=lz[rt],
			lz[ls]+=lz[rt],lz[rs]+=lz[rt],
			lz[rt]=0;
	}
	void modify1(int rt,int l,int r,int ql,int qr,int p){
		if(ql<=l&&r<=qr)<%t[rt]+=p,lz[rt]+=p;return ;%>
		pd(rt);
		int mid=l+r>>1;
		if(ql<=mid)modify1(ls,l,mid,ql,qr,p);
		if(qr>mid)modify1(rs,mid+1,r,ql,qr,p);
		pu(rt);
	}
	void modify2(int rt,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)<%t[rt]=0,lz[rt]=0,lz2[rt]=1;return ;%>
		pd(rt);
		int mid=l+r>>1;
		if(ql<=mid)modify2(ls,l,mid,ql,qr);
		if(qr>mid)modify2(rs,mid+1,r,ql,qr);
		pu(rt);
	}
	int query(int rt,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return t[rt];
		pd(rt);
		int mid=l+r>>1,res=1e9;
		if(ql<=mid)res=query(ls,l,mid,ql,qr);
		if(qr>mid)res=min(res,query(rs,mid+1,r,ql,qr));
		return res;
	}
}vis;
bool cmp1(node x,node y){
	return x.p==y.p?x.id<y.id:x.p<y.p;
}
bool cmp2(edge x,edge y){
	return x.l2<y.l2;
}
int jump(int x){
	for(int i=s;i>=1;i--)
		if(a[i].l2<=x&&a[i].r2>=x){
			if(a[i].l2-a[i].l1>=a[i].r2-a[i].l2+1)x=a[i].l1+(x-a[i].l2);
			else x-=(x-a[i].l2)/(a[i].l2-a[i].l1)*(a[i].l2-a[i].l1);
			if(x>=a[i].l2)x-=(a[i].l2-a[i].l1);
		}
		else if(a[i].l2<x)return x;
	return x;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&q);
	for(int i=1;i<=s;i++)
		scanf("%d%d%d%d",&a[i].l1,&a[i].r1,&a[i].l2,&a[i].r2);
	sort(a+1,a+s+1,cmp2);
	for(int i=1;i<=q;i++){
		Q[i].id=i;
		scanf("%d%d",&Q[i].op,&Q[i].p);
		if(Q[i].op==1)
			scanf("%d%d",&Q[i].L,&Q[i].R),
			Q[i].p=jump(Q[i].p);
		if(Q[i].op==2)
			Q[i]=Q[Q[i].p],Q[i].id=i,Q[i].op=2;
		if(Q[i].op==3)
			scanf("%d%d",&Q[i].L,&Q[i].R),
			Q[i].p=jump(Q[i].p);
	}
	sort(Q+1,Q+q+1,cmp1);
	for(int i=1;i<=q;i++){
		if(Q[i].p!=Q[i-1].p)vis.modify2(1,1,m,1,m);
		if(Q[i].op==1)vis.modify1(1,1,m,Q[i].L,Q[i].R,1);
		if(Q[i].op==2)vis.modify1(1,1,m,Q[i].L,Q[i].R,-1);
		if(Q[i].op==3)ans[Q[i].id]=(vis.query(1,1,m,Q[i].L,Q[i].R)>0?2:1);
	}
	for(int i=1;i<=q;i++)
		if(ans[i])printf(ans[i]==2?"Yes\n":"No\n");
	return 0;
}
/*
10 20 2 9
1 5 2 6
7 9 8 10
1 4 1 5
3 6 2 3
2 1
3 6 2 3
1 10 2 7
1 9 3 6
2 6
1 7 8 13
3 8 2 12
*/
```

---

