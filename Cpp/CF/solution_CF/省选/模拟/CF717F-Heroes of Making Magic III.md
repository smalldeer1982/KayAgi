# Heroes of Making Magic III

## 题目描述

I’m strolling on sunshine, yeah-ah! And doesn’t it feel good! Well, it certainly feels good for our Heroes of Making Magic, who are casually walking on a one-directional road, fighting imps. Imps are weak and feeble creatures and they are not good at much. However, Heroes enjoy fighting them. For fun, if nothing else.

Our Hero, Ignatius, simply adores imps. He is observing a line of imps, represented as a zero-indexed array of integers $ a $ of length $ n $ , where $ a_{i} $ denotes the number of imps at the $ i $ -th position. Sometimes, imps can appear out of nowhere. When heroes fight imps, they select a segment of the line, start at one end of the segment, and finish on the other end, without ever exiting the segment. They can move exactly one cell left or right from their current position and when they do so, they defeat one imp on the cell that they moved to, so, the number of imps on that cell decreases by one. This also applies when heroes appear at one end of the segment, at the beginning of their walk.

Their goal is to defeat all imps on the segment, without ever moving to an empty cell in it (without imps), since they would get bored. Since Ignatius loves imps, he doesn’t really want to fight them, so no imps are harmed during the events of this task. However, he would like you to tell him whether it would be possible for him to clear a certain segment of imps in the above mentioned way if he wanted to.

You are given $ q $ queries, which have two types:

- $ 1 $ $ a $ $ b $ $ k $ — denotes that $ k $ imps appear at each cell from the interval $ [a,b] $
- $ 2 $ $ a $ $ b $ - asks whether Ignatius could defeat all imps on the interval $ [a,b] $ in the way described above

## 说明/提示

For the first query, one can easily check that it is indeed impossible to get from the first to the last cell while clearing everything. After we add 1 to the second position, we can clear the segment, for example by moving in the following way: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF717F/932daedb58f068e3465f1f1147c5a3d7bd7a6700.png).

## 样例 #1

### 输入

```
3
2 2 2
3
2 0 2
1 1 1 1
2 0 2
```

### 输出

```
0
1
```

# 题解

## 作者：getchar123 (赞：5)

~~看到还没有题解就来写一篇（雾~~。
## 题目分析

### 1.$O(n)$ 判断区间有解性
（这是暴力。。。已经会的可以直接跳过）。

很容易想到一个贪心方法：**从左端点出发，每次优先满足左边第一个不为 $0$ 的元素。只要满足完第 $r-1$ 个元素后，最后一个元素恰好为 $0$，并且在贪心过程中任何一个元素不小于 $0$，则为有解，否则无解。**

不需要考虑从右端点出发，证明略。

### 2.~~推柿子~~找规律
（建议一边看一边自己推，会更好理解）。

设最初的序列各数 $-1$ 后为 $a$。每次往返走都会将相邻两个元素 $-1$。灰色箭头为最开始原数列转 $a$ 数列时 $-1$ 时减掉的。红色箭头为往返跳。

![](https://cdn.luogu.com.cn/upload/image_hosting/7dhppx7m.png)

设 $b_i$ 为以第 $i$ 个元素为左端点的往返跳的个数，上图中 
$b=\{1,0,2,1,0,0,0\}$。
容易发现，$b_i=a_i-b_{i-1}$。

观察 $a$ 中一段区间 $+k$ 后 $b$ 序列的变化（$k=-1$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/0jlyny3b.png)

不够直观？自己手推吧。。。多推几位就看出来了 QAQ。

然后得出一个结论：**在被修改的区间内，与 $l$ 奇偶性相同的位置都 $+k$，奇偶性不同的位置都不变。在 $r$ 之后（也就是 $[r+1,n]$），如果被修改区间长度为偶数，则不变，否则与 $l$ 奇偶性相同的位置 $+k$，不同 $-k$。**

如何得出一段区间的 $b$？

![](https://cdn.luogu.com.cn/upload/image_hosting/fofrkv3g.png)

容易发现，**与 $l$ 奇偶性相同的位置 $i$ 只要用前缀的 $b_i-b_{l-1}$，不同则需要 $+b_{l-1}$。**

如何通过 $b$ 求出最终答案？根据之前的贪心，**其中如果有小于 $0$ 的数或是 $b_r$ 不为 $0$ 则无解，否则有解。**

### 3.线段树维护
通过上面的~~瞪眼法~~观察，应该很简单了吧～。

开两棵线段树，一棵维护偶数位置，一棵维护奇数位置的最小值就行啦～。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long ysl[200010],ysll[200010];
struct TREE{
	long long zhi,bj;
};
struct Tree{
	TREE tr[800010];
	void js(int p,int l,int r){
		if(l>r)return;
		if(l==r){
			tr[p].zhi=ysl[l];
			return;
		}
		int mid=(l+r)>>1,ls=p<<1,rs=(p<<1)+1;
		js(ls,l,mid);
		js(rs,mid+1,r);
		tr[p].zhi=min(tr[ls].zhi,tr[rs].zhi);
		return;
	}
	void bjxc(int p,int ls,int rs){
		tr[ls].zhi+=tr[p].bj;
		tr[ls].bj+=tr[p].bj;
		tr[rs].zhi+=tr[p].bj;
		tr[rs].bj+=tr[p].bj;
		tr[p].bj=0;
		return;
	}
	void xg(int p,int l,int r,int ll,int rr,long long val){
		if(ll<=0||ll>rr)return;
		if(ll<=l&&r<=rr){
			tr[p].zhi+=val;
			tr[p].bj+=val;
			return;
		}
		int mid=(l+r)>>1,ls=p<<1,rs=(p<<1)+1;
		bjxc(p,ls,rs);
		if(ll<=mid)xg(ls,l,mid,ll,rr,val);
		if(rr>mid)xg(rs,mid+1,r,ll,rr,val);
		tr[p].zhi=min(tr[ls].zhi,tr[rs].zhi);
		return;
	}
	long long cx(int p,int l,int r,int ll,int rr){
		if(ll<=0||ll>rr)return 0;
		if(ll<=l&&r<=rr){
			return tr[p].zhi;
		}
		int mid=(l+r)>>1,ls=p<<1,rs=(p<<1)+1;
		bjxc(p,ls,rs);
		long long jg=1e18;
		if(ll<=mid)jg=min(jg,cx(ls,l,mid,ll,rr));
		if(rr>mid)jg=min(jg,cx(rs,mid+1,r,ll,rr));
		return jg;
	}	
}tre[2];//0表示偶数，1表示奇数
int main(){
	scanf("%d",&n);
	int n0=n/2,n1=(n+1)/2;
	for(int i=1;i<=n;i++){
		scanf("%lld",&ysll[i]);
		ysll[i]--;
	}
	for(int i=2;i<=n;i++){
		ysll[i]-=ysll[i-1];
	}
	for(int i=2;i<=n;i+=2){
		ysl[i/2]=ysll[i];
	}tre[0].js(1,1,n0);//建树
	for(int i=1;i<=n;i+=2){
		ysl[(i+1)/2]=ysll[i];
	}tre[1].js(1,1,n1);//建树
	scanf("%d",&m);
	while(m--){
		int op,l,r;
		long long val;
		scanf("%d%d%d",&op,&l,&r);l++;r++;
		int l0=(l+1)/2,r0=r/2,l1=(l+2)/2,r1=(r+1)/2;;
		if(op==1){
			scanf("%lld",&val);
			if(l&1)tre[1].xg(1,1,n1,l1,r1,val);//修改区间内与l奇偶性相同的位置
			else tre[0].xg(1,1,n0,l0,r0,val);
			if((r-l+1)&1){//区间长度为奇数，修改r之后的区间
				if(l&1){
					tre[1].xg(1,1,n1,r1+1,n1,val);
					tre[0].xg(1,1,n0,r0+1,n0,-val);
				}
				else{
					tre[0].xg(1,1,n0,r0+1,n0,val);					
					tre[1].xg(1,1,n1,r1+1,n1,-val);					
				}
			}			
		}
		else{
			long long gf0,gf1;
			if(l&1){gf1=tre[0].cx(1,1,n0,l0-1,l0-1);gf0=-gf1;}
			else{gf0=tre[1].cx(1,1,n1,l1-1,l1-1);gf1=-gf0;}
			if(l0<=r0){
				long long gg=tre[0].cx(1,1,n0,l0,r0)+gf0;
				if(gg<0){//区间中有小于0的数
					puts("0");continue;
				}
			}
			if(l1<=r1){
				long long gg=tre[1].cx(1,1,n1,l1,r1)+gf1;
				if(gg<0){//区间中有小于0的数
					puts("0");continue;
				}
			}
			if(r&1){
				if(tre[1].cx(1,1,n1,r1,r1)+gf1!=0){//r不为0
					puts("0");continue;
				}
			}
			else{
				if(tre[0].cx(1,1,n0,r0,r0)+gf0!=0){//r不为0
					puts("0");continue;
				}				
			}
			puts("1");
		}
	}
	return 0;
}

```


---

## 作者：TernaryTree (赞：2)

大家好，我非常喜欢暴力，所以我使用暴力通过这道题。

我们考虑 $\Theta(n)$ 单次询问：先去掉最左边一开始算的一次，即 $a_l\gets a_l-1$；从左往右考虑，每次在最左边与次左边反复横跳，消掉最左边的数，如果次左边的小于 $0$ 就寄了。

发现如下事实：如果奇数位置和与偶数位置和的差绝对值 $\gt 1$ 就寄了。我们询问的时候加上这个剪枝，得到一个 $\Theta(n)$ 修改，$\Theta(n)$ 回答的做法。

修改没办法剪枝，我们想办法做掉它。直接上俩线段树维护即可，得到一个 $\Theta(\log n)$ 修改，$\Theta(n\log n)$ 回答的做法。看起来如果询问的答案全是 $1$ 复杂度就跑满了，就寄了。但是它过了。

[submission](https://codeforces.com/contest/717/submission/273981524)

---

## 作者：251Sec (赞：1)

显然 $l$ 到 $r$ 都必须至少走一次，然后我们还可以做来回横跳的操作，发现横跳多步的操作可以被横跳一步的操作刻画出来，于是我们把序列所有元素减一后得到如下问题：

> 维护一个序列，支持区间加，区间询问能否每次把相邻两个元素减一使得这个区间变成 $0$。

注意到存在唯一的贪心策略，就是每次找最左边两个数减去它们的 $\min$。并且你发现有解的话这个 $\min$ 必须取这两个数里左边的那个。于是模拟这个贪心，每次就是维护一个变量 $s \gets a_i-s$。然后要求 $s$ 一直 $\ge 0$ 且最后 $=0$。线段树分奇偶维护一下就好了。

---

## 作者：shinkuu (赞：0)

简单题……

这种要维护的东西，就先看怎么 $O(n)$ 做，再优化。

钦定从左走到右，发现最优策略一定是不断在最左边两个反复横跳，直到其中一个为 $0$，然后判断无解或变成 $n-1$ 的情况。并且 $\sum\limits_{i\bmod 2=1}a_i-\sum\limits_{i\bmod2=0}a_i=n\bmod 2$，否则会有剩的。无解就是 $\exists j,\sum\limits_{i\bmod 2=j\bmod 2\land i\le j}a_i-\sum\limits_{i\bmod 2\not=j\bmod 2\land i\le j}a_i<1-(j\bmod 2)$。上面的手玩一下就可以推出来。

然后再用一个线段树维护这个东西，要维护的值就是 $\sum\limits_{i\bmod 2=1}a_i-\sum\limits_{i\bmod2=0}a_i$。每次判断一个区间是否可行，就分奇偶性讨论，取出区间最小值，然后再加/减去 $l-1$ 位置的值，判断是否 $>$ 或 $\ge 0$，对于 $\sum\limits_{i\bmod 2=1}a_i-\sum\limits_{i\bmod2=0}a_i=n\bmod 2$ 这个条件，则也是类似的判断 $r$ 位置值减 $l-1$ 位置是否 $=0/1$ 即可。结合代码理解……

code：

```cpp
int n,m,a[N],s[N];
struct SGT{
	ll tr[N<<2][2],tag[N<<2][2];
	il void pushup(int o){
		tr[o][0]=min(tr[o<<1][0],tr[o<<1|1][0]);
		tr[o][1]=min(tr[o<<1][1],tr[o<<1|1][1]);
	}
	il void reset(int l,int r,int o,ll k,int op){
		if(l==r&&(l-op)&1)return;
		tr[o][op]+=k,tag[o][op]+=k;
	}
	il void pushdown(int l,int r,int o){
		int mid=(l+r)>>1;
		reset(l,mid,o<<1,tag[o][0],0),reset(mid+1,r,o<<1|1,tag[o][0],0),tag[o][0]=0;
		reset(l,mid,o<<1,tag[o][1],1),reset(mid+1,r,o<<1|1,tag[o][1],1),tag[o][1]=0;
	}
	void build(int l,int r,int o){
		if(l==r)return tr[o][l&1]=s[l]=a[l]-s[l-1],tr[o][(l-1)&1]=1ll*inf*inf,void();
		int mid=(l+r)>>1;
		build(l,mid,o<<1),build(mid+1,r,o<<1|1);
		pushup(o);
	}
	void update(int l,int r,int o,int x,int y,int k,int op){
		if(x>y)return;
		if(l>=x&&r<=y)return reset(l,r,o,k,op);
		pushdown(l,r,o);
		int mid=(l+r)>>1;
		if(x<=mid)update(l,mid,o<<1,x,y,k,op);
		if(y>mid)update(mid+1,r,o<<1|1,x,y,k,op);
		pushup(o);
	}
	ll query(int l,int r,int o,int x,int y,int op){
		if(r<x||l>y)return 1ll*inf*inf;
		if(l>=x&&r<=y)return tr[o][op];
		pushdown(l,r,o);
		int mid=(l+r)>>1;
		return min(query(l,mid,o<<1,x,y,op),query(mid+1,r,o<<1|1,x,y,op));
	}
}T;
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	T.build(1,n,1);
	scanf("%d",&m);
	while(m--){
		int op,x,y;ll k;scanf("%d%d%d",&op,&x,&y),x++,y++;
		if(op==1){
			scanf("%lld",&k);
			T.update(1,n,1,x,y,k,x&1);
			if((y-x+1)&1)T.update(1,n,1,y+1,n,k,x&1),T.update(1,n,1,y+1,n,-k,(x-1)&1);
		}else{
			k=x==1?0:T.query(1,n,1,x-1,x-1,(x-1)&1);
			if(T.query(1,n,1,y,y,y&1)-((y-x+1)&1?-k:k)!=((y-x+1)&1)||T.query(1,n,1,x,y,x&1)+k<=0||T.query(1,n,1,x,y,(x+1)&1)-k<0)puts("0");
			else puts("1");
		}
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

