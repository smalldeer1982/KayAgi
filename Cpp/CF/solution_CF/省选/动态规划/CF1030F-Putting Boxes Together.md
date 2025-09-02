# Putting Boxes Together

## 题目描述

有一条无限长的直线，由若干格子组成。在这条直线的某些格子上放有 $n$ 个箱子。第 $i$ 个箱子位于格子 $a_i$ 上，重量为 $w_i$。所有 $a_i$ 互不相同，并且对于所有合法的 $i$，都有 $a_{i-1} < a_i$。

你希望将一些箱子聚集在一起。将编号在区间 $[l, r]$ 的箱子聚集在一起，意味着你需要移动它们，使得它们的位置变为某个连续区间 $[x, x + (r - l)]$。

每一步你可以将任意一个箱子移动到相邻的格子上，只要该格子没有其他箱子（即你可以选择 $i$ 并将 $a_i$ 加 $1$ 或减 $1$，所有位置始终保持互不相同）。将第 $i$ 个箱子移动一格需要消耗 $w_i$ 单位能量。你可以以任意顺序、任意次数移动任意箱子。

有时某些箱子的重量会发生变化，因此有两种类型的操作：

1. $id$ $nw$ ——将编号为 $id$ 的箱子的重量 $w_{id}$ 变为 $nw$。
2. $l$ $r$ ——你需要计算将编号在 $[l, r]$ 区间内的箱子聚集在一起所需的最小总能量。由于答案可能很大，请输出其对 $1000\,000\,007 = 10^9 + 7$ 取模的结果。注意，箱子在查询过程中不会实际移动，你只需计算答案。

注意，你需要最小化原始答案，而不是其对 $10^9 + 7$ 取模的结果。所以如果有两个可能的答案 $2 \cdot 10^9 + 13$ 和 $2 \cdot 10^9 + 14$，你应该选择第一个并输出 $10^9 + 6$，即使第二个答案取模后为 $0$。

## 说明/提示

让我们逐步分析样例中的操作：

1. $1\ 1$ —— 只有一个箱子，无需移动，能量消耗为 $0$。
2. $1\ 5$ —— 可以将箱子移动到区间 $[4, 8]$：$1 \cdot |1 - 4| + 1 \cdot |2 - 5| + 1 \cdot |6 - 6| + 1 \cdot |7 - 7| + 2 \cdot |10 - 8| = 10$。
3. $1\ 3$ —— 可以将箱子移动到区间 $[1, 3]$。
4. $3\ 5$ —— 可以将箱子移动到区间 $[7, 9]$。
5. $-3\ 5$ —— 将 $w_3$ 从 $1$ 改为 $5$。
6. $-1\ 10$ —— 将 $w_1$ 从 $1$ 改为 $10$。此时权值为 $w = [10, 1, 5, 1, 2]$。
7. $1\ 4$ —— 可以将箱子移动到区间 $[1, 4]$。
8. $2\ 5$ —— 可以将箱子移动到区间 $[5, 8]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 8
1 2 6 7 10
1 1 1 1 2
1 1
1 5
1 3
3 5
-3 5
-1 10
1 4
2 5
```

### 输出

```
0
10
3
4
18
7
```

# 题解

## 作者：Tjqq (赞：8)

提供一个**无脑**做法：

对于一个区间 $[l,r]$ 的询问，如果选择将箱子移动到 $[L,R]$ 的区间内，答案显然就是 

$$f(L,R)=\sum_{i=l,j=L}^n w_i\times|a_i-j|$$ 

然后通过~~打表~~证明可以发现当 $L\in [a_l,a_r]$ 时，得到的答案是一个单峰函数。然后我们可以通过三分/二分找到它的峰顶，因为这题两只 $\log$ 时间比较紧，所以用 $\log_{2}n$ 的二分。

然后就是考虑快速求出 $f(L,R)$。因为这题只有对于 $w$ 的单点修改，所以使用树状数组维护。原序列 $a$ 是单调递增的，因此可以二分出一个位置 $p$，使得 $\forall i \in [l,pos]\ a_i\le L+i-1 , \forall i \in [pos+1,r]\ a_i\ge L+i-1$ 然后式子就变成了

$$\sum_{i=l,j=L}^p w_i\times j - \sum_{i=l,j=L}^p w_i\times a_i + \sum_{i=p+1,j=p+1+L-l}^r w_i\times j - \sum_{i=p+1,j=p+1+L-l}^r w_i\times a_i$$

所以用三个树状数组，分别维护 $w_x$，$x \times w_x$，$a_x \times w_x$。 

然后就做完了。

## 代码

```cpp
/*
town
*/
#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
#define ll __int128
#define pb emplace_back
#define inf 0x3f3f3f3f
char Ch;
int ff;
inline void rd(int &x) {
	x=0,ff=1,Ch=getchar();
	while((Ch<'0'||Ch>'9')&&Ch!='-') Ch=getchar();
	if(Ch=='-')Ch=getchar(),ff=-1;
	while(Ch>='0'&&Ch<='9') {
		x=(x<<1)+(x<<3)+Ch-'0';
		Ch=getchar();
	}
	x*=ff;
}
using namespace std;
const int N=2e5+5,mod=1e9+7;
int n,Q;
int a[N],w[N];
struct node {
	ll t[3][N];
	inline void upd(int f,int x,ll y) {
		for(; x<=n; x+=x&-x) t[f][x]+=y;
	}
	inline ll ask(int x,int y) {
		ll res=0;
		for(; x>0; x-=x&-x) {
			res+=t[0][x];
			res-=t[1][x];
			res+=y*t[2][x];
		}
		return res;
	}
	inline ll query(int x,int y,int z) {
		return ask(y,z)-ask(x-1,z);
	}
} T;
inline int Find(int l1,int r1,int l2,int r2) {
	int l=l2,r=r2,ans=0,mid;
	while(l<=r) {
		mid=l+r>>1;
		if(a[mid]<=mid-l2+l1)
			ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
inline ll Get(int L,int R,int l,int r) {
	int cyx=L-l;
	int pos=Find(L,R,l,r);
//	printf("cyx %d %d %d %d %d\n",L,R,l,r,pos);
	 ll res=T.query(l,pos,cyx);
//	printf("FFF %d !=%d\n",cyx,res);
	if(pos<r) res-=T.query(pos+1,r,cyx);
//	printf("alskalsks %d %d\n",-T1.query(pos+1,r)-cyx*T3.query(pos+1,r),T2.query(pos+1,r));
//	printf("move (%d %d) to (%d %d) = %d\n",L,R,l,r,res);
	return res;
}
inline int solve(int L,int R) {
	int sz=R-L+1,l=a[L],r=a[R]-sz+2,ans=L;
//	printf("Get %d %d %d %d %d\n",L,R,l,l+sz-1,Get(l,l+sz-1,L,R));
	while(l<=r) {
		int mid=l+r>>1;
		if(Get(mid,mid+sz-1,L,R)<=Get(mid+1,mid+1+sz-1,L,R))
			ans=mid,r=mid-1;
		else l=mid+1;
	}
	return Get(ans,ans+sz-1,L,R)%mod;
}
signed main() {
//	srand(time(0));
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n),rd(Q);
	for(int i=1; i<=n; i++)
		rd(a[i]);
	for(int i=1; i<=n; i++) {
		rd(w[i]);
		T.upd(0,i,1ll*i*w[i]);
		T.upd(1,i,1ll*a[i]*w[i]);
		T.upd(2,i,1ll*w[i]);
	}		
//	printf("LT %d %d %d\n",T1.query(1,n),T2.query(1,n),T2.query(1,n));
	int x,y;
	while(Q--) {
		rd(x),rd(y);
		if(x<0) {
			x=-x;
			T.upd(0,x,-1ll*x*w[x]);
			T.upd(1,x,-1ll*a[x]*w[x]);
			T.upd(2,x,-1ll*w[x]);
			w[x]=y;
			T.upd(0,x,1ll*x*w[x]);
			T.upd(1,x,1ll*a[x]*w[x]);
			T.upd(2,x,1ll*w[x]);
		}
		else
			printf("%d\n",solve(x,y));
	}
	return 0;
}
/*
sum{|ai-j|*wi} (i=l~r,j=L~R)
p2=p1-l+L 
-> sum{j*wi}{j=L~L+p2}-sum{ai*wi}{i=l~p1}
*/
```

---

## 作者：Natori (赞：2)

>[CF1030F Putting Boxes Together](https://www.luogu.com.cn/problem/CF1030F)

下设一次询问的下标区间为 $[l,r]$。

定义 **聚合目标** 为一个箱子或空地，其他箱子都向它移动。显然聚合目标一定在询问区间内，否则就有箱子会移动大于区间长度的距离，这显然是不优的。

在编号区间中其他箱子聚合之前，先将它们向各自一侧最接近聚合目标的箱子聚合，显然这一步并不会影响答案。这样就把聚合目标两侧的箱子先聚合成了两个 **整体**。

一个结论是：最优的聚合目标一定是箱子。

~~感性~~ 证明一下：

设聚合目标为箱子 $i$（不一定最优），设 $w_i$ 为 $c_i$，设左边 **箱子整体** 的 $\sum w$ 为 $c_1$，最右端箱子要移动 $s_1$ 步才能与 $i$ 相邻。右边 **箱子整体** 同理，设为 $c_3,s_3$。

不妨设 $i$ 左右两边均为空地。若不为空地，则可以将 $i$ 所在箱子整体视作一个箱子。

按照上面的方案，聚合的代价为 $c_1s_1+c_3s_3$。

如果聚合目标变为 $i$ 右边的空地，那么代价就变成 

$$c_1(s_1+1)+c_i+c_3(s_3-1)$$

上式等于 $c_1s_1+c_3s_3+c_1+c_i-c_3$。

如果 $c_1+c_i \geq c_3$，那么以箱子为聚合目标就比空地更优。转化一下，即 $\sum_{j=l}^i{w_j} \geq \sum_{j=i+1}^r{w_j}$ 时箱子更优。

同理，如果聚合目标变为 $i$ 左边的空地，那么箱子比空地优的条件就是 $\sum_{j=l}^{i-1}{w_j} \leq \sum_{j=i}^r{w_j}$。

因此，比两边空地更优的箱子 $i$ 应当是最小的 $pos$，使得：

$$\sum\limits_{j=l}^{pos}{w_j} \geq \sum\limits_{j=pos+1}^r{w_j}$$

显然这样的 $i$ 存在。

由之前的假设，$i$ 两边均为空地，因此 $i$ 两边的箱子整体必须移动 $\geq 1$ 的距离才能与 $i$ 相邻。如果聚合目标变成 $i$ 以外的其他箱子，就相当于把上面的不等式 **两边同时乘上一个 $\geq 1$ 的系数**，不等式仍然成立。

因此，所有箱子中最优的 $i$，也应该是最小的 $pos$，满足 $\sum_{j=1}^{pos}{w_j} \geq \sum_{j=pos+1}^n{w_j}$

这样不仅证明了之前的结论，还得到了 $i$ 最优的条件。

最优的聚合目标可以通过维护 $w$ 的前缀和，并在区间内二分得到。

------------
下设询问区间内最优的聚合目标为 $pos$。

考虑枚举 $i \in [l,r]$，表示向 $pos$ 聚合的箱子。将每一个 $i$ 的答案算出来，加在一起就是区间的答案。

对于每个 $i$，它需要移动 $|a_i-a_{pos}|-|i-pos|$ 步才能结束移动。其中，$|a_i-a_{pos}|$ 为 $i$ 与 $pos$ 之间的距离，$|i-pos|$ 为移动结束后 $i$ 和 $pos$ 必须间隔的距离，因为 $i,pos$ 之间可能还有箱子。

（比较抽象，建议在纸上画一个数轴）

那么 $i$ 的贡献就应该是 $w_i \times (|a_i-a_{pos}|-|i-pos|)$，求和即可得到答案。

------------

~~喜闻乐见的推柿子时间！~~

遇到绝对值一般都要拆掉才能优化。



写出区间 $[l,r]$ 的答案：

$$\sum\limits_{i=l}^{r}w_i \times (|a_i-a_{pos}|-|i-pos|)$$

根据 $i$ 与 $pos$ 的大小关系拆掉绝对值，得到

$$\sum\limits_{i=l}^{pos}w_i \times (a_{pos}-a_i-pos+i)+\sum\limits_{i=pos+1}^{r}w_i \times (a_{i}-a_{pos}-i+pos)$$

使用乘法分配律，得到

$$\sum\limits_{i=l}^{pos}(w_i \times (a_{pos}-pos)-w_i \times (a_i-i))+\sum\limits_{i=pos+1}^{r}(w_i \times (a_{i}-i)-w_i \times (a_{pos}-pos))$$

把两个求和号分别拆开，答案为

$$(a_{pos}-pos) \times (\sum\limits_{i=l}^{pos}w_i) -\sum\limits_{i=l}^{pos}(w_i \times (a_i-i))+\sum\limits_{i=pos+1}^{r}(w_i \times (a_i-i))-(a_{pos}-pos) \times (\sum\limits_{i=pos+1}^{r}w_i)$$

维护区间 $\sum w_i,\sum w_i \times (a_i-i)$ 即可，需要支持单点修改。使用线段树，总复杂度 $\mathcal{O}(n \log^2 n)$，因为还要二分区间最优聚合目标。

代码别的题解都有，这里就不贴了。

~~好像推复杂了（？）~~

---

## 作者：Xttttr (赞：1)

## CF1030F 题解

[传送门](https://www.luogu.com.cn/problem/CF1030F)  [更好的阅读体验](https://www.cnblogs.com/Xttttr/p/17615939.html)

简化题意：有 $n$ 个小球，每个小球在位置 $a_i$，移动一格的代价是 $w_i$，有两种操作，一种是将 $w_x$ 改成 $y$，一种是查询 $\min\limits_{x=1}^n\{\sum\limits_{i=l}^rw_i\times (|a_x-a_i|+|x-i|)\}$。

### 思路

很好的线段树二分练手题。

对于每个询问，首先肯定要找到使得答案最小的 $x$。我们考虑当前的 $x$ 变成 $x+1$ 时答案的改变量，发现就是 $(a_{x+1}-a_x)\times(\sum\limits_{i=l}^xw_i-\sum\limits_{i=x+1}^rw_i)$，因此 $x$ 取到 $[l,r]$ 的带权中位数时最优，即最小的满足 $\sum\limits_{i=l}^x w_i\geqslant\sum\limits_{i=x+1}^rw_i$ 的 $x$。

于是就可以直接二分+线段树来找这个 $x$，这也是其他题解的做法，单次复杂度是 $O(\log^2n)$ 的。如果直接用线段树二分的话就是 $O(\log n)$ 的，感觉还是比较板的。

接下来计算答案比较简单，就不再赘述了。

贴一下线段树二分的代码。

```
struct Seg{
    ll t[N<<2];
    inline void upd(int rt){t[rt]=t[ls]+t[rs];}
    inline void modify(int rt,int l,int r,int x,int k){
        if(l==r){
            t[rt]=k;
            return;
        }
        if(x<=mid)modify(ls,l,mid,x,k);
        else modify(rs,mid+1,r,x,k);
        upd(rt);
    }
    inline ll query(int rt,int l,int r,int L,int R){
        if(L>R)return 0;
        if(L<=l&&r<=R)return t[rt];
        ll ans=0;
        if(L<=mid)ans=query(ls,l,mid,L,R);
        if(mid<R)ans+=query(rs,mid+1,r,L,R);
        return ans;
    }
    inline int query(int rt,int l,int r,int L,int R,ll sum,ll &cur){
        if(l==r){
            if(2ll*(t[rt]+cur)<sum){
                cur+=t[rt];
                return -1;
            }
            return l;
        }
        if(L<=l&&r<=R){
            if(2ll*(t[rt]+cur)<sum){
                cur+=t[rt];
                return -1;
            }
            if(2ll*(t[ls]+cur)>=sum)return query(ls,l,mid,L,R,sum,cur);
            cur+=t[ls];
            return query(rs,mid+1,r,L,R,sum,cur);
        }
        int ans=-1;
        if(L<=mid)ans=query(ls,l,mid,L,R,sum,cur);
        if(~ans)return ans;
        return query(rs,mid+1,r,L,R,sum,cur);
    }
}T;
```

---

## 作者：DNWy (赞：1)

~~学习了楼上，楼上讲的很好了，不过我更喜欢线段树搭树状数组，用线段树和树状数组写了一遍，给有需要的同学准备的。~~

# Problem
给定数列 $\{a\}$ $\{w\}$，表示第 $i$ 的点的位置 $a_i$，权值 $w_i$，实现两种操作：

- 给出 $i$，$x$，单点修改 $w_i=x$。
- 给出 $l$，$r$，查询 $min_{x=1}^n\{\sum_{i=l}^rw_i*(|a_x-a_i|+|x-i|)\}$。

# Solution
### 转化题意
看到使后面的 $\sum_{i=l}^rw_i*(|a_x-a_i|+...)$ 最小，于是想到是求 $l$ 到 $r$ 的[**带权中位数**](https://baike.baidu.com/item/%E5%B8%A6%E6%9D%83%E4%B8%AD%E4%BD%8D%E6%95%B0/8517609)，并支持修改(省略的部分很好维护)。

结合带权中位数的相关知识（即恰好满足 $\sum_{i=1}^xw_i\ge\sum_{i=x+1}^nw_i$ 的数 $x$），我们可以通过二分查找 $O(\log n)$ 得到。

### 考虑如何维护求和

观察到，去掉绝对值可以拆分为
$$\sum_{i=l}^x(w_i*(a_x-x)-w_i*(a_i-i))+\sum_{i=x+1}^r(w_i*(a_i-i)-w_i*(a_x-x))$$
进一步，左边：
$$(\sum_{i=l}^xw_i)* \sum_{i=l}^x(a_x-x)-\sum_{i=l}^xw_i*(a_i-i)$$
右边：
$$\sum_{i=x+1}^rw_i*(a_i-i)-(\sum_{i=x+1}^rw_i)* \sum_{i=x+1}^r(a_x-x)$$
二者之和即是答案。

很容易地，我们可用**线段树/树状数组**维护出 $\sum w_i$ 和 $\sum(a_i-i)$，快乐 A 掉此题。

### 实现细节
查询带权中位数时，我们不能对 $\sum w_i$ 取模，此时也不会爆掉 long long；

但在求和时，我们需要对查询到的 $\sum w_i$ 取模，因为其还会乘上一个足以爆掉 long long 的数。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define mp make_pair
using namespace std;
const int SIZE = 2e5+10;
const int MOD = 1e9+7;

int n,q,a[SIZE],w[SIZE];
struct BIT{//树状数组实现,区间查询w_i
    int t[SIZE];
    void add(int x,int y){
        for(;x<=n;x+=x&-x) t[x]+=y;
    }
    int ask(int x){
        int tmpans=0;
        for(;x;x-=x&-x) tmpans+=t[x];
        return tmpans;
    }
    int qsum(int l,int r){
        return ask(r)-ask(l-1);
    }
}tr;
struct ST{//线段树实现,区间
    int t[4*SIZE];//w_i*a_i的和
    void build(int p=1,int l=1,int r=n){
        if(l==r){t[p]=w[l]*(a[l]-l);return ;}
        int mid=(l+r)>>1;
        build(p<<1,l,mid),build(p<<1|1,mid+1,r);
        t[p]=(t[p<<1]+t[p<<1|1])%MOD;
    }
    void add(int cp,int val,int p=1,int l=1,int r=n){//单点修改
        if(l==r){t[p]=val*(a[l]-l);return ;}
        int mid=(l+r)>>1;
        if(cp<=mid) add(cp,val,p<<1,l,mid);
        else add(cp,val,p<<1|1,mid+1,r);
        t[p]=(t[p<<1]+t[p<<1|1])%MOD;
    }
    int qsum(int cl,int cr,int p=1,int l=1,int r=n){//查询sum2区间和
        if(cl<=l&&cr>=r) return t[p];
        int mid=(l+r)>>1,tmpans;
        if(cl<=mid) tmpans=qsum(cl,cr,p<<1,l,mid);
        else tmpans=0;
        if(cr>mid) tmpans=(tmpans+qsum(cl,cr,p<<1|1,mid+1,r))%MOD;
        return tmpans;
    }
}t;

int Binary_search(int l,int r,int ll,int rr){//二分查找 带权中位数
    int tmpans;
    while(l<=r){
        int mid=(l+r)>>1;
        if(tr.qsum(ll,mid)>=tr.qsum(mid+1,rr)) r=mid-1,tmpans=mid;
        else l=mid+1;
    }
    return tmpans;
}

void query(int l,int r){
    int pos=Binary_search(l,r,l,r),tmpans=0;
    tmpans=(tr.qsum(l,pos)%MOD*(a[pos]-pos)-t.qsum(l,pos))%MOD;//套用推出来的公式即可
    tmpans=((tmpans+t.qsum(pos+1,r)-tr.qsum(pos+1,r)%MOD*(a[pos]-pos))%MOD+MOD)%MOD;
    cout<<tmpans<<"\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>q;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<=n;++i){cin>>w[i];tr.add(i,w[i]);}
    t.build();
    while(q--){
        int x,y;cin>>x>>y;
        if(x<0){
            t.add(-x,y);
            int tmp=tr.qsum(-x,-x);//树状数组实现单点修改
            tr.add(-x,-tmp),tr.add(-x,y);
        }
        else query(x,y);
    }
    return 0;
}
```

---

## 作者：bztMinamoto (赞：1)

学习了->[这里](https://www.cnblogs.com/CzxingcHen/p/9694955.html#4085514)

先来考虑一下货仓选址问题，就是一堆不带权值的数，选出一个点使得所有点到他的距离之和最小，那么肯定是选中位数最优

然后加上权值限制，这玩意儿有个学名叫做带权中位数

带权中位数为满足$\sum_{i=1}^x w_i\geq \sum_{i=x+1}^n w_i$的最大的$x$

简单证（kou）明（hu）一下为什么是对的，假设将区间内的所有数移到$x+1$的位置，那么$[1,x]$内的数全都要多走$dis[x,x+1]$的路程，而$[x+1,n]$内的数可以少走这么多路程，那么总权值的变化量就为$dis[x,x+1]*(sum_{i=1}^x w_i-\sum_{i=x+1}^n w_i)$，可以发现若上面那个不等式不成立则往右移总权值变小，也就是说答案会更优，所以只有当上面那个等式成立时才不会往右移更优。又因为这玩意儿是从左边移过来的，所以左边的都比他劣。那么它一定是最优的。

于是这个东西我们可以二分

然后我们来考虑一下原问题，发现所有的移动方案都可以等价于固定一个点不动，其他的点向它靠。那么我们设$pos$为最优的点，然后用和上面的方法一样考虑可以发现当$pos$为带权中位数时答案最优。所以我们可以直接二分出$pos$

现在的问题就是如何快速计算总代价了，即$\sum_{i=l}^{pos-1}w_i*(a_{pos}-a_i-(pos-i))+\sum_{i=pos+1}^{r}w_i*(a_{i}-a_{pos}-(i-pos))$

考虑左边这一坨（右边同理），化一下式子可得它等于$$\sum_{i=l}^{pos-1}w_i*(a_{pos}-pos-(a_i-i))$$

然后右边也是差不多的形式，于是只要维护$\sum w_i$和$\sum w_i*(a_i-i)$就能快速算出答案了

于是用树状数组维护这两个玩意儿，然后二分找出带权中位数，每一次快速计算答案即可
```
//minamoto
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=2e5+5;const ll P=1e9+7;
int n,q;ll a[N],w[N];
namespace SUM{
    ll c[N];
    inline void add(int x,ll y){
        for(;x<=n;x+=x&-x) c[x]+=y;
    }
    inline ll que(int x){
        ll res=0;
        for(;x;x-=x&-x) res+=c[x];
        return res;
    }
    inline ll query(int l,int r){
        if(r<l) return 0;
        return que(r)-que(l-1);
    }
}
namespace MUL{
    ll c[N];
    inline void add(int x,ll y){
        y%=P;
        for(;x<=n;x+=x&-x)
        (c[x]+=y+P)%=P;
    }
    inline ll que(int x){
        ll res=0;
        for(;x;x-=x&-x) (res+=c[x])%=P;
        return res;
    }
    inline ll query(int l,int r){
        if(r<l) return 0;
        return (que(r)-que(l-1)+P)%P;
    }
}
inline int getpos(int ql,int qr){
    int l=ql,r=qr,mid,res;
    while(l<=r){
        mid=(l+r)>>1;
        if(SUM::query(ql,mid)>=SUM::query(mid+1,qr)) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}
void solve(int l,int r){
    if(l==r) return (void)(print(0));
    int pos=getpos(l,r);ll res=0;
    res=(-MUL::query(l,pos)+(SUM::query(l,pos) % P)*(a[pos] - pos)%P+P)%P;
    res=(res+MUL::query(pos,r)-SUM::query(pos,r)%P*(a[pos]-pos)%P+P)%P;
    print(res);
}
int main(){
//    freopen("testdata.in","r",stdin);
    n=read(),q=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=n;++i){
        w[i]=read(),SUM::add(i,w[i]),MUL::add(i,w[i]*(a[i]-i));
    }
    while(q--){
        int x=read(),y=read();
        if(x<0){
            x=-x,SUM::add(x,-w[x]),MUL::add(x,-w[x]*(a[x]-x));
            w[x]=y,SUM::add(x,y),MUL::add(x,y*(a[x]-x));
        }else solve(x,y);
    }
    Ot();
    return 0;
}
```

---

## 作者：Patrickpwq (赞：1)

学习了楼上，楼上讲的很好了，不过我更喜欢线段树，用线段树写了一遍，给有需要的同学准备的
```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
const int N=2e5+5;
const int mod=1000000007;
using namespace std;
template<class T>
inline void read(T &x)
{
    x=0; int f=1;
    static char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
    while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    x*=f;
}
inline void write(ll x)
{
    if(x<0) {x=-x; putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+'0'); 
}
int n,Q;
ll a[N],w[N],b[N];
struct Tree
{
    int l,r;
    ll sum,s;
}tree[4*N];
inline void pushup(int now)
{
    tree[now].sum=tree[now<<1].sum+tree[now<<1|1].sum;
    tree[now].s=(tree[now<<1].s+tree[now<<1|1].s)%mod;
}
inline void build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r;
    if(l==r)
    {
        tree[now].sum=w[l];
        tree[now].s=b[l]*w[l]%mod;
        return;
    }
    int m=(l+r)>>1;
    build(now<<1,l,m);
    build(now<<1|1,m+1,r);
    pushup(now);
}
inline ll query(int now,int l,int r)
{
    if(l<=tree[now].l&&tree[now].r<=r) return tree[now].sum;
    int m=(tree[now].l+tree[now].r)>>1; ll ans=0;
    if(l<=m) ans+=query(now<<1,l,r);
    if(r>m) ans+=query(now<<1|1,l,r);
    return ans;
}
inline void update(int now,int pos,int x)
{
    if(tree[now].l==tree[now].r)
    {
        tree[now].sum=x;
        tree[now].s=b[pos]*x%mod;
        return;
    }
    int m=(tree[now].l+tree[now].r)>>1;
    if(pos<=m) update(now<<1,pos,x);
    else update(now<<1|1,pos,x);
    pushup(now);
}
inline ll ask(int now,int l,int r)
{
    if(l<=tree[now].l&&tree[now].r<=r)	return tree[now].s;
    int m=(tree[now].l+tree[now].r)>>1; ll ans=0;
    if(l<=m) ans=(ans+ask(now<<1,l,r))%mod;
    if(r>m) ans=(ans+ask(now<<1|1,l,r))%mod;
    return ans;	
}
inline void Solve(int l,int r)
{
    int L=l,R=r,ans=l;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        ll QL=query(1,l,mid),QR=query(1,mid+1,r);
        if(QL>=QR) ans=mid,R=mid-1;
        else L=mid+1;
    }
    ll t1=(query(1,l,ans-1)%mod*(a[ans]-ans)%mod-ask(1,l,ans-1)+mod)%mod;
    ll t2=(query(1,ans+1,r)%mod*(ans-a[ans]+mod)%mod+ask(1,ans+1,r)%mod)%mod;
	write((t1+t2)%mod);
	putchar('\n');
} 
int main()
{
    read(n),read(Q);
    for(int i=1;i<=n;i++) read(a[i]),b[i]=a[i]-i;
    for(int i=1;i<=n;i++) read(w[i]);
    build(1,1,n);
    int l,r;
    while(Q--)
    {
        read(l),read(r);
        if(l<0) update(1,-l,r);
        if(l>0)	Solve(l,r);
    }
    return 0;
} 

```

---

## 作者：tribool4_in (赞：0)

首先容易发现每次“聚合”必然存在一个箱子不动，令其为 $p$。考虑反证，若所有箱子均移动，则存在一段前缀的箱子右移，一段后缀的箱子左移，设前缀的 $w$ 的和为 $Sl$，后缀的 $w$ 的和为 $Sr$，此时将相遇点向较小侧移动一定不劣，移动一步可以减小 $\max(Sl,Sr)-\min(Sl,Sr)$。

考虑对于某个 $p$ 如何求出答案，对于 $p$ 左右分开计算，得到 $\displaystyle\sum_{i=l}^{p-1}w_i(a_p-a_i-(p-i))+\sum_{i=p+1}^{r}w_i(a_i-a_p-(i-p))$，拆开可以发现关于 $i$ 的项有 $w_i$、$iw_i$、$a_iw_i$，用树状数组对三者分别维护即可。

考虑如何求出 $p$。考虑另一个结论：对于询问区间 $[l,r]$，$p$ 为满足 $S_{l,p}\ge\dfrac{S_{l,r}}{2}\ (1)$ 的最小值，即有 $S_{l,p-1}<\dfrac{S_{l,r}}{2}\ (2)$。证明与上面同理，若不满足 $(1)$ 式则可向右移，若不满足 $(2)$ 式则可向左移。于是容易用线段树二分（或直接二分）找出 $p$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
int n, q;
int a[N], w[N];
struct BIT {
#define lowbit(x) ((x) & (-(x)))
    bool ismod;
    BIT(bool ismod) : ismod(ismod) {}
    int b[N];
    int query(int x) {
        int s = 0;
        for (; x > 0; x -= lowbit(x)) s += b[x], (s >= mod && ismod) && (s -= mod);
        return s;
    }
    void update(int x, int v) {
        for (; x <= n; x += lowbit(x)) b[x] += v, (b[x] >= mod && ismod) && (b[x] -= mod);
    }
    int query(int x, int y) { return ismod ? (query(y) - query(x - 1) + mod) % mod : (query(y) - query(x - 1)); }
#undef lowbit
} bw(0), bwa(1), bwi(1);
int getrp(int lp, int rp, int s) {
    int l = lp, r = rp, ans = lp;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (bw.query(lp, mid) * 2 >= s) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> w[i], bw.update(i, w[i]), bwa.update(i, w[i] * a[i] % mod), bwi.update(i, w[i] * i % mod);
    for (int i = 1, x, y; i <= q; i++) {
        cin >> x >> y;
        if (x > 0) {
            int p = getrp(x, y, bw.query(x, y));
            int la = ((a[p] - p) * (bw.query(x, p - 1) % mod) % mod - bwa.query(x, p - 1) + bwi.query(x, p - 1) + mod) % mod;
            int ra = (bwa.query(p + 1, y) - (a[p] - p) * (bw.query(p + 1, y) % mod) % mod - bwi.query(p + 1, y) + mod) % mod;
            cout << ((la + ra) % mod + mod) % mod << '\n';
        } else {
            x = -x;
            bw.update(x, y - w[x]);
            bwa.update(x, (y - w[x] + mod) * a[x] % mod);
            bwi.update(x, (y - w[x] + mod) * x % mod);
            w[x] = y;
        }
    }
    return 0;
}

```

---

