# 「WyOJ Round 1」归 · 星穗垂野

## 题目背景

>神龟虽寿，犹有竟时；腾蛇乘雾，终为土灰。老骥伏枥，志在千里；烈士暮年，壮心不已。
>
>——曹操《龟虽寿》

## 题目描述

给定长度为 $n$ 的序列 $(a_1,a_2,\dots,a_n)$，定义函数 $w(l,r)$ 为：

$$
w(l,r)= \gcd(a_l,a_{l+1},\dots,a_{r})\times \sum_{i=l}^r b_i
$$

定义序列选择**互不相交**的 $m$ 段（$m>0$）区间 $[l_1,r_1],[l_2,r_2],\dots,[l_{m},r_{m}]$（即 $\forall i\in [1,m), r_{i}<l_{i+1}$）的代价为：

$$
\sum_{i=1}^{m} w(l_{i},r_{i})
$$

定义**好的选择**为 $\forall i\in [1,m], r_{i}-l_{i}+1\ge \gcd(a_{l_i},a_{l_i+1},\dots,a_{r_i})\ge r_{i-1}-l_{i-1}+1$。其中，$l_0=r_0=0$。

选择 $m$ 段的**额外**代价是 $mC$，其中 $C$ 为给定的常数。

试求 $a$ 序列的**好的选择**的最小代价。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^5$，$1\le a_i\le 10^5$，$0\le b_i\le 10^5$，$-10^9\le C\le 10^9$。保证至少能够选择一段。

| 测试点 | $T$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $10^3$ | $n\le 10$ |
| $2$ | $5$ | $C\ge 0$ |
| $3,4$ | $5$ | $n\le 300$ |
| $5$ | $5$ | $n\le 1000$ |
| $6\sim 10$ | $5$ | $n\le 10^5$ |

## 样例 #1

### 输入

```
1
6 -7
1 1 4 5 1 4
1 9 1 9 8 10```

### 输出

```
-6```

# 题解

## 作者：harmis_yz (赞：3)

思维难度：没有。

代码难度：绿。

建议评级：蓝。

## 分析

考虑 DP。

定义状态函数 $f_{i,j}$ 表示前 $i$ 个数划分，最后一个区间长度为 $j$ 时候的最小值。

注意到这题给了很多个 $\gcd$，那有个典的东西就是对于同一个 $r$，关于 $l$ 不同的 $\gcd$ 值只有 $O(\log V)$ 个。因为 $l \to l-1$，$\gcd$ 要么不变，要么至少变成原来的 $\frac{1}{2}$（删至少一个质因子）。我们枚举 $r$，枚举 $\gcd$ 的值（记为 $x$）。那么可以得到一个合法的 $l$ 区间 $[L,R]$（$r-l+1\ge x \land \gcd(a_l,a_{l+1},\dots,a_r)=x$）。对于这里面的任意一个 $l$，都有转移方程：$f_{r,r-l+1}=\min(f_{r-1,r-l+1},\min\limits_{k=0}^{x}f_{l-1,k}+(x \sum\limits_{i=l}^{r}b_i +C))$。

乍一看很难维护，再一看就可以维护了。为什么呢，简单。我们有：$f_{i,j} \le f_{i-1,j}$。所以 $\min\limits_{k=0}^{x}f_{l-1,k}+(x \sum\limits_{i=l}^{r}b_i +C)$ 一定不小于 $\min\limits_{k=0}^{x}f_{l-2,k}+(x \sum\limits_{i=l-1}^{r}b_i +C)$，因为 $b_{l-1}\ge 0$ 且 $f_{l-2,k}\ge f_{l-1,k}$。同时呢，我们 $f_{i,j}$ 能用来转移 $f_{k,w}$ 时，$f_{i,j-1}$ 也一定能用来转移 $f_{k,w}$（$f_{r,r-l+1}$ 的限制比 $f_{r,r-l+2}$ 松）。所以 $l$ 在 $r$ 和 $x$ 都是定值的时候取 $R$ 就行了。

也就是说，转移方程变成：$f_{r,r-R+1}=\min(f_{r-1,r-R+1},\min\limits_{k=0}^{x}f_{R-1,k}+(x \sum\limits_{i=R}^{r}b_i +C))$。线段树维护即可，时间复杂度 $O(n\log^2n)$。

## 代码

```cpp
const int N=1e5+10,inf=1e18;
int n,C;
int a[N],b[N],s[N];
int __[N],Gcd[N][20];
struct Tree{
	int l,r,mi;
}tr[N<<2];
struct node{
	int i,j,delta,k;
};
struct node_{
	int j,k;
};
vector<node_> vec_[N];
vector<node> vec[N];

il void up(int u){
	tr[u].mi=min(tr[ls(u)].mi,tr[rs(u)].mi);
	return ;
}
il void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r,tr[u].mi=inf;
	if(l==r) return ;
	int mid=l+r>>1;
	build(ls(u),l,mid),build(rs(u),mid+1,r);
	return ;
}
il void modify(int u,int x,int y){
	if(tr[u].l==tr[u].r) return tr[u].mi=min(tr[u].mi,y),void(0);
	int mid=tr[u].l+tr[u].r>>1;
	if(x<=mid) modify(ls(u),x,y);
	else modify(rs(u),x,y);
	return up(u),void(0);
}
il int query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r) return tr[u].mi;
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid&&mid< r) return min(query(ls(u),l,r),query(rs(u),l,r));
	if(l<=mid) return query(ls(u),l,r);
	return query(rs(u),l,r);
}
il int get_gcd(int l,int r){
	int k=__[r-l+1];
	return gcd(Gcd[l][k],Gcd[r-(1ll<<k)+1][k]);
}

il void solve(){
	n=rd,C=rd;
	for(re int i=0;i<=n;++i) __[i]=log2(i),vec[i].clear(),vec_[i].clear();
	for(re int i=1;i<=n;++i) a[i]=rd,Gcd[i][0]=a[i];
	for(re int i=1;i<=n;++i) b[i]=rd,s[i]=s[i-1]+b[i];
	for(re int j=1;j<20;++j)
	for(re int i=1;i+(1ll<<j)-1<=n;++i) Gcd[i][j]=gcd(Gcd[i][j-1],Gcd[i+(1ll<<(j-1))][j-1]);
	for(re int r=1;r<=n;++r){
		int u=r;
		while(u>=1){
			int gcdd=get_gcd(u,r);
			int le=1,ri=u,w=-1;
			while(le<=ri){
				int mid=le+ri>>1;
				if(get_gcd(mid,r)>=gcdd) w=mid,ri=mid-1;
				else le=mid+1;
			}
			int x=w,y=u;
			//r+1-gcdd>=l
			int l=r+1-gcdd;
			l=min(l,y);
			if(l<x){
				u=x-1;
				continue;
			}
			vec[l-1].push_back({r,r-l+1,gcdd*s[r]-gcdd*s[l-1]+C,gcdd});
			u=x-1;
		}
	}
	build(1,0,N-1);
	vec_[0].push_back({0,0});
	for(re int r=0;r<=n;++r){
		for(auto x:vec_[r]){
			int j=x.j,k=x.k;
			modify(1,x.j,x.k);
		}
		for(auto x:vec[r]){
			int i=x.i,j=x.j,delta=x.delta,k=x.k;
			int Min=query(1,0,k);
			vec_[i].push_back({j,delta+Min});
		}
	}
	printf("%lld\n",query(1,1,N-1));
    return ;
}
```

---

