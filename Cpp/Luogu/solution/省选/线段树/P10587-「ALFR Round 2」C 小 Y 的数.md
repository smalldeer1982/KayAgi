# 「ALFR Round 2」C 小 Y 的数

## 题目描述

小 Y 非常喜欢 $42$ 这个数，于是他也喜欢以 $42$ 为初始数，然后往后面依次拼接 $4,2$ 的数，如 $42,424,4242,\cdots$。小 Y 给了你一个大小为 $n$ 的整数序列 $a$，小 Y 有 $m$ 次操作，操作有四种：

- `1 l r x` 将 $l\sim r$ 中的数加上 $x$。

- `2 l r x` 将 $l\sim r$ 中的数乘上 $x$。

- `3 l r x` 将 $l\sim r$ 中的数修改为 $x$。

- `4 l r` 询问 $l\sim r$ 中有多少个小 Y 喜欢的数。

## 说明/提示

### 样例解释

第 $1$ 次操作为询问区间 $1\sim8$ 中有多少个小 Y 喜欢的数，共 $1$ 个，为 $a_2$。

第 $2$ 次操作为将区间 $1\sim8$ 中的数加上 $377$，数列 $a$ 变为 $418,419,420,421,422,423,424,424$。

第 $3$ 次操作为询问区间 $1\sim8$ 中有多少个小 Y 喜欢的数，共 $2$ 个，为 $a_7,a_8$。

第 $4$ 次操作为将区间 $1\sim1$ 中的数乘上 $100$，数列 $a$ 变为 $41800,419,420,421,422,423,424,424$。

第 $5$ 次操作为将区间 $1\sim8$ 中的数加上 $624$，数列 $a$ 变为 $42424,1043,1044,1045,1046,1047,1048,1048$。

第 $6$ 次操作为询问区间 $1\sim7$ 中有多少个小 Y 喜欢的数，共 $1$ 个，为 $a_1$。

第 $7$ 次操作为将区间 $1\sim8$ 中的数修改为 $424242$，数列 $a$ 变为 $424242,424242,424242,424242,424242,424242,424242,424242$。

第 $8$ 次操作为询问区间 $1\sim5$ 中有多少个小 Y 喜欢的数，共 $5$ 个，为 $a_1,a_2,a_3,a_4,a_5$。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $20$ | $n,m\le10^4$ |
| $1$ | $80$ | - |

对于 $100\%$ 的数据，$1\le n,m,a_i,x\le5\times10^5$，$1\le l,r\le n$。

保证每次操作后 $1\le a_i\le5\times10^5$。

## 样例 #1

### 输入

```
8 8
41 42 43 44 45 46 47 47
4 1 8
1 1 8 377
4 1 8
2 1 1 100
1 1 8 624
4 1 7
3 1 8 424242
4 1 5```

### 输出

```
1
2
1
5```

# 题解

## 作者：_Yonder_ (赞：8)

考虑势能线段树，要维护的有：区间最大值（$Max$），区间最小值（$Min$），区间内每个数字与第一个比它大的小 Y 喜欢的数字的差的最小值（$Mix$）。

对于一操作，判断 $Mix$ 是否小于等于 $x$，若是则用加标记，否则直接暴力修改，每个数字最多只会被暴力修改 5 次。

对于二操作，直接暴力乘即可，每个数顶多会被乘 19 次。

对于三操作就是普通的区间覆盖，但是它很明显会影响一、二操作的时间复杂度，但只要我们在进行一、二操作的暴力修改前判断一下 $Max$ 是不是等于 $Min$ 即可。

四操作就判断 $Mix$ 是否为零即可，若是就输出 $Mix$ 为零的数的个数。
# Code
```cpp
#include<bits/stdc++.h>
#ifdef ONLINE_JUDGE
static char buf[4500000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,4500000,stdin),p1==p2)?EOF:*p1++
#endif
using namespace std;
inline int read(){
    int x=0;char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9') x=x*10+(c^48),c=getchar();
    return x;
}inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
const int N=5e5+5;
int n,m,a[N],x=42,f[N],nex[N],op,l,r,c;
int add[N<<2],Max[N<<2],Min[N<<2],Mix[N<<2],cnt[N<<2],tag[N<<2],Q[N<<2];
inline void push_up(int p){
    register int ls=p<<1,rs=p<<1|1;
	Max[p]=Max[Max[ls]>Max[rs]?ls:rs];
	Min[p]=Min[Min[ls]<Min[rs]?ls:rs];
	Mix[p]=Mix[Mix[ls]<Mix[rs]?ls:rs];
	if(Mix[ls]==Mix[rs]) cnt[p]=cnt[ls]+cnt[rs];
	else cnt[p]=cnt[Mix[ls]<Mix[rs]?ls:rs];
}
inline void fc(int p,int c){add[p]=0,tag[p]=c,cnt[p]=Q[p],Mix[p]=nex[c]-c,Max[p]=Min[p]=c;}
inline void fa(int p,int c){add[p]+=c;Min[p]+=c;Max[p]+=c;Mix[p]-=c;}
inline void push_down(int p){
	if(tag[p]){
	    if(add[p]) tag[p]+=add[p],add[p]=0;
	    fc(p<<1,tag[p]),fc(p<<1|1,tag[p]),tag[p]=0;
	    return;
	}
	if(add[p]) fa(p<<1,add[p]),fa(p<<1|1,add[p]),add[p]=0;
}
inline void Build(int p=1,int pl=1,int pr=n){
	Q[p]=pr-pl+1;
	if(pl==pr){Max[p]=Min[p]=a[pl],cnt[p]=1,Mix[p]=nex[a[pl]]-a[pl];return;}
	int mid=pl+pr>>1;Build(p<<1,pl,mid);Build(p<<1|1,mid+1,pr);push_up(p);
}
inline void ca(int p,int ind){if(tag[p]) a[ind]=tag[p];a[ind]+=add[p];tag[p]=add[p]=0;}
inline void update1(int l,int r,int x,int p=1,int pl=1,int pr=n){
	if(l<=pl&&pr<=r){
		if(Mix[p]>=x){fa(p,x);return;}
		if(Max[p]==Min[p]){fc(p,Max[p]+x);return;}
	}int mid=pl+pr>>1;push_down(p);
	if(l<=mid) update1(l,r,x,p<<1,pl,mid);
	if(r>mid) update1(l,r,x,p<<1|1,mid+1,pr);
	push_up(p);
}
inline void update2(int l,int r,int x,int p=1,int pl=1,int pr=n){
	if(pl==pr){ca(p,pl);a[pl]*=x;fc(p,a[pl]);return;}
	if(l<=pl&&pr<=r&&Max[p]==Min[p]){fc(p,Max[p]*x);return;}
	int mid=pl+pr>>1;push_down(p);
	if(l<=mid) update2(l,r,x,p<<1,pl,mid);
	if(r>mid) update2(l,r,x,p<<1|1,mid+1,pr);
	push_up(p);
}
inline void update3(int l,int r,int x,int p=1,int pl=1,int pr=n){
	if(l<=pl&&pr<=r){fc(p,x);return;}
	int mid=pl+pr>>1;push_down(p);
	if(l<=mid) update3(l,r,x,p<<1,pl,mid);
	if(r>mid) update3(l,r,x,p<<1|1,mid+1,pr);
	push_up(p);
}
inline int ask(int l,int r,int p=1,int pl=1,int pr=n){
	if(l<=pl&&pr<=r) return !Mix[p]*cnt[p];
	push_down(p);int mid=pl+pr>>1;
	return (l<=mid?ask(l,r,p<<1,pl,mid):0)+(r>mid?ask(l,r,p<<1|1,mid+1,pr):0);
}
int main(){
	f[42]=f[424]=f[4242]=f[42424]=f[424242]=1;
	x=1e9;for(register int i=N-1;i;i--){if(f[i]) x=i;nex[i]=x;}
	n=read(),m=read();for(register int i=1;i<=n;i++) a[i]=read();
	Build();
	while(m--){
		op=read(),l=read(),r=read(),c=op<4?read():0;
		if(op==1) update1(l,r,c);
		else if(op==2){if(c^1) update2(l,r,c);}
		else if(op==3) update3(l,r,c);
		else write(ask(l,r)),putchar('\n');
	}
    return 0;
}
```

---

## 作者：harmis_yz (赞：3)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/3yyu431w)。

## 分析

考虑势能线段树。

不难发现，当 $V=5\times 10^5$ 时，小Y 喜欢的数只有 $5$ 个。这里使用两种势能，第一种表示 $x$ 这个数可能成为小Y 喜欢的数的势能，第二种表示 $x$ 这个数达到 $V$ 的势能。

对于区间加法操作。我们令 $nxt_i$ 表示 $i$ 与第一个比 $i$ 大且是小Y 喜欢的数的差。对于每个节点，维护 $mit$ 表示该节点维护的区间中 $nxt_x$ 最小的值。进行分类讨论：

1. $mit > x$。此时势能无影响，且对答案无影响。直接做区间加法即可。
2. $mit \le x$。此时区间总势能至少减 $len$。下传继续维护区间加法。

对于区间乘法操作。每个数的初始势能不大于 $\log V$，一个区间的总势能至少减 $len$。下传继续维护区间乘法。

对于区间覆盖操作。该操作将会使一个区间的两种势能统一，且恢复原来的势能需要 $O(n)$ 的代价。直接进行区间覆盖即可。在这里，对于一个区间所有数都相同的时候，加法操作和乘法操作均能够将该区间视做单点，所以无需下传维护。

对于区间询问。我们因为 $mit \ge 0$，我们记录每个点维护的区间中 $nxt_x=mit$ 的数量，记为 $cnt$。当该点的 $mit=0$ 时，答案即为 $cnt$。否则为 $0$。

根据势能分析，该算法的时间复杂度为 $O(n\log V)$。

## 代码

```cpp
il void up(int u){
	tr[u].mx=max(tr[ls(u)].mx,tr[rs(u)].mx);
	tr[u].mi=min(tr[ls(u)].mi,tr[rs(u)].mi);
	tr[u].mit=min(tr[ls(u)].mit,tr[rs(u)].mit);
	tr[u].cnt=(tr[u].mit==tr[ls(u)].mit)*tr[ls(u)].cnt+(tr[u].mit==tr[rs(u)].mit)*tr[rs(u)].cnt;
	return ;
}
il void down(int u){
	if(tr[u].tag_cov){
		tr[ls(u)].mx=tr[ls(u)].mi=tr[u].tag_cov;
		tr[ls(u)].mit=nxt[tr[u].tag_cov];
		tr[ls(u)].cnt=(tr[ls(u)].r-tr[ls(u)].l+1);
		tr[ls(u)].tag_cov=tr[u].tag_cov;
		tr[ls(u)].tag_add=0;
		
		tr[rs(u)].mx=tr[rs(u)].mi=tr[u].tag_cov;
		tr[rs(u)].mit=nxt[tr[u].tag_cov];
		tr[rs(u)].cnt=(tr[rs(u)].r-tr[rs(u)].l+1);
		tr[rs(u)].tag_cov=tr[u].tag_cov;
		tr[rs(u)].tag_add=0;		
		tr[u].tag_cov=0;
	}
	if(tr[u].tag_add){
		tr[ls(u)].mx+=tr[u].tag_add,tr[ls(u)].mi+=tr[u].tag_add;
		tr[ls(u)].mit-=tr[u].tag_add;
		tr[ls(u)].tag_add+=tr[u].tag_add;
		
		tr[rs(u)].mx+=tr[u].tag_add,tr[rs(u)].mi+=tr[u].tag_add;
		tr[rs(u)].mit-=tr[u].tag_add;
		tr[rs(u)].tag_add+=tr[u].tag_add;	
		tr[u].tag_add=0;	
	}
	return ;
}
il void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	if(l==r){
		tr[u].mx=tr[u].mi=a[l];
		tr[u].mit=nxt[a[l]];
		tr[u].cnt=1;
		tr[u].tag_cov=tr[u].tag_add=0;
		return ;
	}
	int mid=l+r>>1;
	build(ls(u),l,mid),build(rs(u),mid+1,r);
	up(u);
	return ;
}
il void modify_add(int u,int l,int r,int x){
	if(tr[u].l>=l&&tr[u].r<=r){
		if(tr[u].mit>x){
			tr[u].mit-=x;
			tr[u].tag_add+=x;
			tr[u].mi+=x,tr[u].mx+=x;
			return ;
		}
		if(tr[u].mi==tr[u].mx){
			tr[u].mi+=x,tr[u].mx+=x;
			tr[u].tag_cov=tr[u].mi;
			tr[u].tag_add=0;
			tr[u].mit=nxt[tr[u].tag_cov];
			tr[u].cnt=(tr[u].r-tr[u].l+1);
			return ;
		}
	}
	if(tr[u].l==tr[u].r){
		if(tr[u].mit>x){
			tr[u].mit-=x,
			tr[u].tag_add+=x;
			tr[u].mi+=x,tr[u].mx+=x;
			return ;
		}
		tr[u].mi+=x,tr[u].mx+=x;
		tr[u].tag_cov=tr[u].mi;
		tr[u].tag_add=0;
		tr[u].mit=nxt[tr[u].tag_cov];
		tr[u].cnt=(tr[u].r-tr[u].l+1);	
		return ;	
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify_add(ls(u),l,r,x);
	if(mid< r) modify_add(rs(u),l,r,x);
	up(u);
	return ;
}
il void modify_mul(int u,int l,int r,int x){
	if(x==1) return ;
	if(tr[u].l>=l&&tr[u].r<=r){
		if(tr[u].mi==tr[u].mx){
			tr[u].mi*=x,tr[u].mx*=x;
			tr[u].tag_cov=tr[u].mi;
			tr[u].tag_add=0;
			tr[u].mit=nxt[tr[u].tag_cov];
			tr[u].cnt=(tr[u].r-tr[u].l+1);
			return ;			
		}
	}
	if(tr[u].l==tr[u].r){
		tr[u].mi*=x,tr[u].mx*=x;
		tr[u].tag_cov=tr[u].mi;
		tr[u].tag_add=0;
		tr[u].mit=nxt[tr[u].tag_cov];
		tr[u].cnt=(tr[u].r-tr[u].l+1);
		return ;			
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify_mul(ls(u),l,r,x);
	if(mid< r) modify_mul(rs(u),l,r,x);
	up(u);
	return ;
}
il void modify_cov(int u,int l,int r,int x){
	if(tr[u].l>=l&&tr[u].r<=r){
		tr[u].tag_cov=x;
		tr[u].tag_add=0;
		tr[u].mi=tr[u].mx=x;
		tr[u].mit=nxt[x];
		tr[u].cnt=(tr[u].r-tr[u].l+1);
		return ;
	}
	down(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify_cov(ls(u),l,r,x);
	if(mid< r) modify_cov(rs(u),l,r,x);
	up(u);
	return ;
}
il int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r) return tr[u].cnt*(tr[u].mit==0);
	down(u);
	int mid=tr[u].l+tr[u].r>>1,sum=0;
	if(l<=mid) sum+=query(ls(u),l,r);
	if(mid< r) sum+=query(rs(u),l,r);
	up(u);
	return sum;
}
```

---

