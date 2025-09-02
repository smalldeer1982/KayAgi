# Wine Factory (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ c_i $ and $ z $ . You can make hacks only if both versions of the problem are solved.

There are three arrays $ a $ , $ b $ and $ c $ . $ a $ and $ b $ have length $ n $ and $ c $ has length $ n-1 $ . Let $ W(a,b,c) $ denote the liters of wine created from the following process.

Create $ n $ water towers. The $ i $ -th water tower initially has $ a_i $ liters of water and has a wizard with power $ b_i $ in front of it. Furthermore, for each $ 1 \le i \le n - 1 $ , there is a valve connecting water tower $ i $ to $ i + 1 $ with capacity $ c_i $ .

For each $ i $ from $ 1 $ to $ n $ in this order, the following happens:

1. The wizard in front of water tower $ i $ removes at most $ b_i $ liters of water from the tower and turns the removed water into wine.
2. If $ i \neq n $ , at most $ c_i $ liters of the remaining water left in water tower $ i $ flows through the valve into water tower $ i + 1 $ .

There are $ q $ updates. In each update, you will be given integers $ p $ , $ x $ , $ y $ and $ z $ and you will update $ a_p := x $ , $ b_p := y $ and $ c_p := z $ . After each update, find the value of $ W(a,b,c) $ . Note that previous updates to arrays $ a $ , $ b $ and $ c $ persist throughout future updates.

## 说明/提示

The first update does not make any modifications to the arrays.

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 5 $ liters of water in tower 2 and $ 4 $ liters of water is turned into wine. The remaining $ 1 $ liter of water flows into tower 3.
- When $ i = 3 $ , there are $ 4 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. The remaining $ 2 $ liters of water flows into tower 4.
- When $ i = 4 $ , there are $ 5 $ liters of water in tower 4. All $ 5 $ liters of water are turned into wine.

Hence, $ W(a,b,c)=1 + 4 + 2 + 5 = 12 $ after the first update.

The second update modifies the arrays to $ a = [3, 5, 3, 3] $ , $ b = [1, 1, 2, 8] $ , and $ c = [10^{18}, 10^{18}, 10^{18}] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 3.
- When $ i = 3 $ , there are $ 9 $ liters of water in tower 3 and $ 2 $ liters of water is turned into wine. The remaining $ 7 $ liters of water flow into tower 4.
- When $ i = 4 $ , there are $ 10 $ liters of water in tower 4. Only $ 8 $ liters of water is turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 2 + 8 = 12 $ after the second update.

The third update modifies the arrays to $ a = [3, 5, 0, 3] $ , $ b = [1, 1, 0, 8] $ , and $ c = [10^{18}, 10^{18}, 10^{18}] $ .

- When $ i = 1 $ , there are $ 3 $ liters of water in tower 1 and $ 1 $ liter of water is turned into wine. The remaining $ 2 $ liters of water flow into tower 2.
- When $ i = 2 $ , there are $ 7 $ liters of water in tower 2 and $ 1 $ liter of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 3.
- When $ i = 3 $ , there are $ 6 $ liters of water in tower 3 and $ 0 $ liters of water is turned into wine. The remaining $ 6 $ liters of water flow into tower 4.
- When $ i = 4 $ , there are $ 9 $ liters of water in tower 4. Only $ 8 $ liters of water is turned into wine.

Hence, $ W(a,b,c)=1 + 1 + 0 + 8 = 10 $ after the third update.

## 样例 #1

### 输入

```
4 3
3 3 3 3
1 4 2 8
1000000000000000000 1000000000000000000 1000000000000000000
4 3 8 1000000000000000000
2 5 1 1000000000000000000
3 0 0 1000000000000000000```

### 输出

```
12
12
10```

## 样例 #2

### 输入

```
5 5
10 3 8 9 2
3 4 10 8 1
1000000000000000000 1000000000000000000 1000000000000000000 1000000000000000000
5 4 9 1000000000000000000
1 1 1 1000000000000000000
2 7 4 1000000000000000000
4 1 1 1000000000000000000
1 8 3 1000000000000000000```

### 输出

```
34
25
29
21
27```

# 题解

## 作者：sunnygreen (赞：13)

注：**该题解做法仅适用于 Easy Version。**

设前 $i-1$ 个酒桶操作完成后第 $i$ 个酒桶有 $A_i$ 升酒，前 $i$ 个酒桶操作完成后产生了 $sum_i$ 升酒。令 $sum_0=0$，那么有：

$$A_i=\sum_{j=1}^{i}a_j-sum_{i-1}$$

$$
\begin{aligned}
sum_i
&=sum_{i-1}+\min(A_i,b_i)\\
&=sum_{i-1}+\min(\sum_{j=1}^{i}a_j-sum_{i-1},b_i)\\
&=\min(\sum_{j=1}^{i}a_j,b_i+sum_{i-1})\\
&=\min_{j=0}^{i}(\sum_{k=1}^{j}a_k+\sum_{k=j+1}^{n}b_k)\\
&=\min_{j=0}^{i}(\sum_{k=1}^{j}(a_k-b_k))+\sum_{j=1}^{n}b_j
\end{aligned}
$$

于是，只需要维护 $b$ 数组中元素的和以及 $a_i-b_i$  的前缀和最小值即可。前者可以 $O(1)$ 维护，后者可以用线段树 $O(\log n)$ 维护。具体地，每个节点维护区间和 $sum$ 以及最小前缀和 $ans$，合并信息时令当前节点为 $now$，其左右子节点分别为 $l,r$，那么有：

$$sum_{now}=sum_l+sum_r$$

$$ans_{now}=\min(ans_l,sum_l+ans_r)$$

时间复杂度 $O(n+q\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define fi first
#define se second
#define lhx make_pair
#define eb emplace_back
#define rep(i,l,r) for(int i=(l); i<=(r); ++i)
#define rep_(i,l,r) for(int i=(l); i>=(r); --i)
typedef long long lr;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
constexpr int N=500500,mod1=998244353,mod2=1e9+7;
constexpr db eps=1e-7;
constexpr int inf32=0x3f3f3f3f,Inf32=0xcfcfcfcf;
constexpr lr inf64=0x3f3f3f3f3f3f3f3f,Inf64=0xcfcfcfcfcfcfcfcf;
template<typename T>il T Max(T x,T y)
{
    return (x>y)? x:y;
}
template<typename T>il T Min(T x,T y)
{
    return (x<y)? x:y;
}
template<typename T>il T gcd(T x,T y)
{
    return (!y)? x:gcd(y,x%y);
}
template<typename T>il T Abs(T x)
{
    return (x>0)? x:(-x);
}
struct node
{
	lr sum,ans;
	il node operator +(const node &b)const
	{
		return (node){sum+b.sum,Min(ans,sum+b.ans)};
	}
}tr[N<<2];
int n,q,a[N],b[N];
lr sumb,c[N];
#define ls k<<1,l,mid
#define rs k<<1|1,mid+1,r
void Build(int k,int l,int r)
{
	if(l==r)
	{
		tr[k]=(node){a[l]-b[l],Min(a[l]-b[l],0)};
		return;
	}
	int mid=(l+r)>>1;
	Build(ls),Build(rs),tr[k]=tr[k<<1]+tr[k<<1|1];
}
void Modify(int k,int l,int r,int x,int v)
{
	if(l>x||r<x)
		return;
	if(l>=x&&r<=x)
	{
		tr[k]=(node){v,Min(v,0)};
		return;
	}
	int mid=(l+r)>>1;
	Modify(ls,x,v),Modify(rs,x,v),tr[k]=tr[k<<1]+tr[k<<1|1];
}
il void Solve()
{
	cin>>n>>q;
	rep(i,1,n)
		cin>>a[i];
	rep(i,1,n)
		cin>>b[i],sumb+=b[i];
	rep(i,1,n-1)
		cin>>c[i];
	Build(1,1,n);
	while(q--)
	{
		int p,x,y;
		lr z;
		cin>>p>>x>>y>>z,sumb+=y-b[p],b[p]=y,Modify(1,1,n,p,x-y),cout<<Min(0ll,tr[1].ans)+sumb<<'\n';
	}
}
int main()
{
#ifdef FILEIO
    string pre="hack",isuf="in",osuf="out";
    freopen((pre+"."+isuf).c_str(),"r",stdin);
    freopen((pre+"."+osuf).c_str(),"w",stdout);
#endif
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T=1;
    while(T--)
        Solve();
    return 0;
}
```

---

## 作者：LKY928261 (赞：7)

注：**该题解做法仅适用于 Easy Version**。

一道有趣的数据结构题。

首先注意到直接维护答案并不容易。而在 Easy Version 中所有剩下的水都能被运到下一个桶，所以酿出酒的体积等于初始所有酒桶里的水量总和减去最后第 $n$ 个桶中剩余的水的体积，即 $V_{\text{酒}}=V_{\text{原}}-V_{\text{剩}}$。于是只需维护经过前 $i$ 个桶后剩余的水量即可。

接下来考虑如何维护。

设经过第 $i$ 个桶前的水量为 $v$（初始为 $0$），则经过第 $i$ 个桶后，$v\gets \max(v+a_i-b_i,0)$。

考虑使用线段树维护，线段树上每个节点记录两个值 $x,y$，表示经过该节点对应区间后，$v\gets \max(v+x,y)$。

对于两个区间信息的合并，记左右两区间分别为 $l,r$，则有：

$$\begin{aligned}&\max(\max(v+x_l,y_l)+x_r,y_r)\\=&\max(\max(v+x_l+x_r,y_l+x_r),y_r)\\=&\max(v+(x_l+x_r),\max(y_l+x_r,y_r))\end{aligned}$$

即 $x\gets x_l+x_r,y\gets \max(y_l+x_r,y_r)$。

询问答案即为 $\sum{a_i}-\max(x_{root},y_{root})$，注意需要动态维护 $\sum{a_i}$。

当然，区间查询也是可以轻松做到的。

[完整赛时 AC 代码](https://codeforces.com/contest/1919/submission/240570980)。

---

## 作者：_ANIG_ (赞：6)

[传送门](https://www.luogu.com.cn/problem/CF1919F1)

可以发现，这些水要么浪费了，要么对答案产生贡献。

由于 $c_i=10^{18}$，所以只需要知道有多少水从 $n$ 流出去了即可。

设 $f_i$ 为有多少水从点 $i$ 流到点 $i+1$，则 $f_i=\max(f_{i-1}+a_i-b_i,0)$。

可以定义矩阵乘法：

$c_{i,j}=\max\{a_{i,k}+b_{k,j}\}$。

这个矩阵是满足结合律的。

而上面 $f$ 的转移就可以用这样的矩阵来刻画。

具体地，维护二元组 $(f_i,0)$，对于每个点 $i$，构造一个转移矩阵 $w$，使得 $(f_{i-1},0)\times w=(f_i,0)$。

则构造的 $w_i$ 为 $\begin{vmatrix}a_i-b_i&-inf\\0&0\end{vmatrix}$。

线段树维护矩阵乘积即可。
```cpp
    #include <bits/stdc++.h>
    using namespace std;
    #define int long long
    const int N=5e5+5,inf=1e18;
    struct jz{
    	int w[2][2],n,m;
    	friend jz operator*(jz a,jz b){
    		jz c;
    		c.n=a.n,c.m=b.m;
    		for(int i=0;i<a.n;i++){
    			for(int j=0;j<b.m;j++){
    				c.w[i][j]=-inf;
    				for(int k=0;k<a.m;k++){
    					c.w[i][j]=max(c.w[i][j],a.w[i][k]+b.w[k][j]);
    				}
    			}
    		}
    		return c;
    	}
    }w[N],cs;
    struct node{
    	int l,r;
    	jz sm; 
    }p[4*N];
    void upset(int x){
    	p[x].sm=p[x<<1].sm*p[x<<1|1].sm;
    }
    void reset(int x,int l,int r){
    	p[x].l=l,p[x].r=r;
    	if(l==r){
    		p[x].sm=w[l];
    		return;
    	}
    	int mid=l+r>>1;
    	reset(x<<1,l,mid);
    	reset(x<<1|1,mid+1,r);
    	upset(x);
    }
    void sets(int x,int d,jz sm){
    //	cout<<p[x].l<<" "<<p[x].r<<endl;
    	if(p[x].l==p[x].r){
    		p[x].sm=sm;
    		return;
    	}
    //	cout<<p[x].l<<" "<<p[x].r<<endl;
    	if(d<=(p[x].l+p[x].r>>1))sets(x<<1,d,sm);
    	else sets(x<<1|1,d,sm);
    	upset(x);
    }
    int n,m,a[N],b[N],c[N],al;
    jz gets(int x){
    	jz res;
    	res.n=res.m=2;
    	res.w[0][0]=a[x]-b[x];
    	res.w[1][0]=0;
    	res.w[0][1]=-inf;
    	res.w[1][1]=0;
    	return res;
    }
    //f[i]=max(f[i-1]+a[i]-b[i],0)
    signed main(){
    	cs.n=1,cs.m=2;
    	cs.w[0][0]=0;cs.w[0][1]=0;
    	cin>>n>>m;
    	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),al+=a[i];
    	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
    	for(int i=2;i<=n;i++)scanf("%lld",&c[i]);
    	jz cc;
    	cc.n=cc.m=2;
    	cc.w[0][0]=cc.w[1][1]=1;cc.w[1][0]=cc.w[0][1]=0;
    	for(int i=1;i<=n;i++)w[i]=gets(i);
    	reset(1,1,n);
    	while(m--){
    		int x,aa,bb,cc;
    		scanf("%lld%lld%lld%lld",&x,&aa,&bb,&cc);
    		al-=a[x];al+=aa;
    		a[x]=aa;b[x]=bb;c[x]=cc;
    		sets(1,x,gets(x));
    		printf("%lld\n",al-(cs*p[1].sm).w[0][0]);
    	}
    }


```


---

## 作者：dxbt (赞：5)

#### 注：该题解做法仅适用于 Easy Version。


本题有一个显然的结论：答案等于所有酿酒的法力总和减最大的前缀法力和与前缀水量和之差。

证明如下：

+ 我们首先让所有的酿酒师先酿自己酒桶的水，这是不劣的。我们令 $s_i=a_i-b_i$，表示酿酒师酿完酒后剩余的法力值或水量。

+ 由于水量可以无限量流入下一个水桶，我们考虑会浪费多少法力值，我们令 $sum$ 表示累加的 $s_i$，当 $sum<0$ 时，浪费为加上 $-sum$，并把 $sum$ 赋值为 $0$。

+ 我们去掉赋值操作，那么上面的流程就变成了找到这些浪费的点，答案就是它们差分数组的和，也就是最后一个浪费点的前缀 $sum$，即所有 $sum$ 的最小值。

+ 用线段树维护前缀 $s_i$ 的和，查询全局最大值即可。

```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l,i##end=r;i<=i##end;++i)
#define ll long long
using namespace std;
ll a[500009];
ll b[500009];
ll tr[500009*4];
ll tag[500009*4];
void pushdown(int o)
{
	tr[o<<1]+=tag[o];tr[o<<1|1]+=tag[o];
	tag[o<<1]+=tag[o];tag[o<<1|1]+=tag[o];
	tag[o]=0;
}
void add(int l,int r,int o,int A,int B,ll C)
{
	if(A<=l && r<=B)return tr[o]+=C,tag[o]+=C,void();
	int mid=l+r>>1;
	pushdown(o);
	if(A<=mid) add(l,mid,o<<1,A,B,C);
	if(B>mid) add(mid+1,r,o<<1|1,A,B,C);
	tr[o]=max(tr[o<<1],tr[o<<1|1]);
}
void solve()
{
	int n,q;cin>>n>>q;ll sum=0;
	F(i,1,4*n) tr[i]=tag[i]=0;
	F(i,1,n)cin>>a[i];
	F(i,1,n)cin>>b[i];
	ll sk=0;
	F(i,1,n-1)cin>>sk;
	F(i,1,n)add(1,n,1,i,n,b[i]-a[i]),sum+=b[i];
	F(i,1,q)
	{
		int p;ll ax,bx,cx;
		cin>>p>>ax>>bx>>cx;
		sum-=b[p]-bx;
		add(1,n,1,p,n,a[p]-b[p]+bx-ax);
		a[p]=ax;b[p]=bx;
		cout<<sum-max(tr[1],0ll)<<'\n';
	}
}
signed main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	solve();
	return 0;
}
```


---

## 作者：jr_zch (赞：3)

# Win Factory

题意已经很简明了，这里不加以阐述，注意到 $c_i,z=10^{18}$，但是 $n \leq 5 \times 10^5$，$a_i \leq 10^9$，也就是说，**所有桶里面装的水都不会超出桶容量或者管道容量**。

到这里，其实求解策略就很明显了，从第 $1$ 个水桶开始，只要巫师还有法力，就转化成酒，直到水用完或者法力用完，如果还有剩下的水，就流到下一个水桶去，和下一个水桶一起处理。

要是这题没有修改就已经贪心做完了，在有修改的情况下，数学功底比较好的人可以把答案用式子表示出来然后硬推，这里提供一种不同的思考方向。

考虑这样一个问题：假设水足够多，那么答案就是**巫师的法力总和**，但是在大多时候答案却小于这个值，少的那一部分去哪里了呢？也就是说**巫师的法力在什么情况下会浪费掉**？

显然，对于水桶 $i$ 如果 $a_i$ 加上前面水桶流过来的水小于 $b_i$ 就会导致法力的浪费，但是前面水桶流过来的水很难表示。发现第一个桶浪费的法力为 $b_i-a_i$，**当这个值为正时，表示浪费的法力；为负时，其绝对值表示盈余的水**。

如果对这个值做一遍前缀和是什么呢？令 $s_i=\sum_{j=1}^i b_j-a_j$，**如果这个值在上升，就说明 $b_i-a_i>0$，即法力的浪费，反之表示水的剩余**。那么它和答案的联系是啥呢？请仔细结合下面这幅表示 $s_i$ 变化的图象来理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/23giena3.png)

理解完过程后，再来看如何计算浪费值，图中**两段粉线相加**即为浪费值，显然，它们相加就是**最高点的高度**，即 $\max_{i=1}^n(s_i)$。需要注意的是，**浪费值不可能为负**，也就是说当最大值是负数时，把浪费值当做 $0$ 即可。

有了浪费值，答案就是法力总和减掉浪费值，即 $\sum_{i=1}^n b_i-\max_{i=1}^n(s_i)$，在修改过程中，前面的 $\sum$ 用一个变量维护，而后面相当于是求**全局最大值**，由于修改了一个值 $i$ 之后，前缀和 $s_i \sim s_n$ 都会改变，相当于是**区间修改，区间查询**，用线段树即可维护。

### Code：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=5e5+7;
int n,m,id,x,y,sum;
int a[maxn],b[maxn],s[maxn],dat[maxn<<2],laz[maxn<<2];

void pushdown(int rt){
	if(laz[rt]){
		dat[rt<<1]+=laz[rt];
		dat[rt<<1|1]+=laz[rt];
		laz[rt<<1]+=laz[rt];
		laz[rt<<1|1]+=laz[rt];
		laz[rt]=0;
	}
	return ;
}

void build(int rt,int l,int r){
	if(l==r){
		dat[rt]=s[l];
		return ;
	}
	int mid=l+r>>1;
	build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
	dat[rt]=max(dat[rt<<1],dat[rt<<1|1]);
	return ;
}

void update(int rt,int l,int r,int x,int y,int val){
	if(x<=l&&y>=r){
		dat[rt]+=val,laz[rt]+=val;
		return ;
	}
	int mid=l+r>>1;
	pushdown(rt);
	if(x<=mid) update(rt<<1,l,mid,x,y,val);
	if(y>mid) update(rt<<1|1,mid+1,r,x,y,val);
	dat[rt]=max(dat[rt<<1],dat[rt<<1|1]);
	return ;
}

signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]),sum+=b[i];
	for(int i=1;i<=n;i++) s[i]=s[i-1]+b[i]-a[i];
	for(int i=1;i<n;i++) scanf("%*lld");
	build(1,1,n);
	while(m--){
		scanf("%lld%lld%lld%*lld",&id,&x,&y),sum+=y-b[id];
		update(1,1,n,id,n,y-x-(b[id]-a[id]));
		a[id]=x,b[id]=y;
		printf("%lld\n",sum-max(dat[1],0ll));
	}
	return 0;
}
```

---

## 作者：Phartial (赞：2)

首先酿造和放水的顺序是不重要的。考虑水罐的最终状态：酿出了一些酒，在一段前缀中还可以将一些水酿成酒，在剩下的一段后缀中还剩下一些水。

考虑使用线段树对每个区间维护 $(p,q,s)$，表示该区间全部处理完后总共酿出了 $s$ 单位的酒，在一段前缀中还可以将 $p$ 单位的水酿成酒，在剩下的一段后缀中还剩下 $q$ 单位的水。

考虑合并 $(p_l,q_l,s_l)$ 和 $(p_r,q_r,s_r)$，$l$ 里剩下的水可以流到 $r$ 中酿成酒，于是合并后的状态为 $(p_l+p_r-v,q_l+q_r-v,s_l+s_r+v)$，其中 $v=\min(q_l,p_r)$。使用线段树维护即可。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 5e5 + 1;

struct E {
  LL p, q, s;
} e[kN << 2];
int n, q, a[kN], b[kN];

void Pu(int x) {
  LL v = min(e[x * 2].q, e[x * 2 + 1].p);
  e[x] = {e[x * 2].p + e[x * 2 + 1].p - v, e[x * 2].q + e[x * 2 + 1].q - v, e[x * 2].s + e[x * 2 + 1].s + v};
}
void B(int x, int l, int r) {
  if (l == r) {
    LL v = min(a[l], b[l]);
    e[x] = {b[l] - v, a[l] - v, v};
    return;
  }
  int m = l + r >> 1;
  B(x * 2, l, m), B(x * 2 + 1, m + 1, r);
  Pu(x);
}
void U(int x, int l, int r, int t) {
  if (l == r) {
    LL v = min(a[l], b[l]);
    e[x] = {b[l] - v, a[l] - v, v};
    return;
  }
  int m = l + r >> 1;
  if (t <= m) {
    U(x * 2, l, m, t);
  } else {
    U(x * 2 + 1, m + 1, r, t);
  }
  Pu(x);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  LL _;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }
  for (int i = 1; i < n; ++i) {
    cin >> _;
  }
  B(1, 1, n);
  for (int p, x, y; q--;) {
    cin >> p >> x >> y >> _;
    a[p] = x, b[p] = y;
    U(1, 1, n, p);
    cout << e[1].s << '\n';
  }
}
```

---

## 作者：yangshengyu0719 (赞：2)

**注：该题解做法仅适用于 Easy Version。**

经过思考我们可以发现：
这题可以用线段树维护每段信息，然后合并得到最终答案。

那么每个区间的答案就等于：**左区间的答案 $+$ 右区间的答案 $+\min$ ( 左区间剩下的水 ，有区间还能制造的酒 )。**

因此我们要维护三个信息：$suma$，$sumb$，$sum$。分别代表：区间内 $a_i$ 的总和，区间内 $b_i$ 的总和，区间内答案。

对于每一次向上传值的操作，只需要将 $T_k.sum \gets T_{ls}.sum + T_{rs}.sum + \min(T_{ls}.suma-T_{ls}.sum,T_{rs}.sumb-T_{rs}.sum)$。

## 代码
~~~cpp
#include <bits/stdc++.h>
#define int long long
#define ls k<<1
#define rs k<<1|1
using namespace std;
const int N=5e5+5;
int n,q,a[N],b[N];
struct node{
	int l,r;
	int suma,sumb,sum;
}T[N<<2];
void update(int k){
	T[k].suma=T[ls].suma+T[rs].suma;
	T[k].sumb=T[ls].sumb+T[rs].sumb;
	T[k].sum=T[ls].sum+T[rs].sum+min(T[ls].suma-T[ls].sum,T[rs].sumb-T[rs].sum);
}
void build(int k,int l,int r){
	T[k].l=l,T[k].r=r;
	if(l==r){
		T[k].suma=a[l],T[k].sumb=b[l];
		T[k].sum=min(a[l],b[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	update(k);
}
void modify(int k,int p,int x,int y){
	int l=T[k].l,r=T[k].r;
	if(l>p||r<p) return;
	if(l==r){
		T[k].suma=x,T[k].sumb=y;
		T[k].sum=min(x,y);
		return;
	}
	modify(ls,p,x,y);
	modify(rs,p,x,y);
	update(k);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int p,x,y,z;
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<n;i++) cin>>z;
	build(1,1,n);
	while(q--){
		cin>>p>>x>>y>>z;
		modify(1,p,x,y);
		cout<<T[1].sum<<'\n';
	}
	return 0;
}
~~~

---

## 作者：Mirasycle (赞：0)

由于本题管道容量无限，所以所有的水要么被酿成了酒，要么从最后一个酒桶中流走了。

于是考虑一个很暴力的做法就是每次递推整个过程，然后求出最后一个酒桶流出的水量，拿总的水量减去这个求出的值就是最后的答案了。

设 $dp_i$ 表示第 $i$ 个点流出水量。

那么就有 $dp_i=\max(dp_{i-1}+a_i-b_i,0)$。

每次都递推一遍是 $O(nq)$ 的。

观察到这个转移可以写成矩阵乘法的形式，由于是 $(\max,+)$ 具有结合律，于是可以用线段树维护。

矩阵转移是

$$\begin{bmatrix}
dp_{i-1}\\
0
\end{bmatrix}
\begin{bmatrix}
a_i-b_i&-\infty\\
0 &0
\end{bmatrix}
=\begin{bmatrix}
dp_i\\
0
\end{bmatrix}
$$

我们维护 $
\begin{bmatrix}
a_i-b_i&-\infty\\
0 &0
\end{bmatrix}
$ 的区间乘积，然后每次单点修改，全局求乘积即可。

时间复杂度 $O(n\log n)$。

---

## 作者：lfxxx (赞：0)

考场降智是这样的。

不难发现每次会把 $x$ 变成 $\max(0,x+a_i-b_i)$ 所以不妨令 $a_i - b_i$ 为 $k_i$，然后你发现所有水要么流到最后要么变成酒，所以算最后剩下多少水就行了。

令 $f_{k_i,down_i}(x) = \max(down_i,x+k_i)$。

有 $f_{k_i,down_i}(x) = \max(0,x+k_i-down_i) + down_i = f_{k_i,0}(x-down_i) + down_i$。

这说明 $f_{k_i,0}(x) = f_{0,-k_i}(x) + k_i$。

又有 $f_{k_1,0}(f_{k_2,0}(x)) = f_{0,-k_1}(f_{k_2,0}(x))+k_1 = f_{0,-k_1-k_2}(f_{0,-k_2}(x))+ k_1 + k_2$。

令 $pre_i = \sum_{j=1}^{i} k_j$。 

所以题目要求的东西即所有 $f_{k_i,0}(x)$ 复合起来就变成了 $f_{0,-pre_i}(x)$ 复合起来加上 $pre_n$。

不难发现前面的复合就是负的最小前缀和，直接丢到线段树上维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e5+114;
int pre[maxn<<2],mi[maxn<<2];
int sumA;
int a[maxn],b[maxn];
void pushup(int cur){
    mi[cur]=min(mi[cur<<1],pre[cur<<1]+mi[cur<<1|1]);
    pre[cur]=pre[cur<<1]+pre[cur<<1|1];
    return ;
}
void update(int cur,int lt,int rt,int pos,int k){
    if(pos<lt||pos>rt) return ;
    if(lt==rt){
        pre[cur]=k;
        mi[cur]=k;
        return ;
    }
    int mid=(lt+rt)>>1;
    update(cur<<1,lt,mid,pos,k);
    update(cur<<1|1,mid+1,rt,pos,k);
    pushup(cur);
    return ;
}
void build(int cur,int lt,int rt){
    if(lt==rt){
        pre[cur]=mi[cur]=a[lt]-b[lt];
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
    pushup(cur);
    return ;
}
int c;
int n,q;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i],sumA+=a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<n;i++) cin>>c;
    build(1,1,n);
    while(q--){
        int p;
        cin>>p;
        sumA-=a[p];
        cin>>a[p]>>b[p]>>c;
        sumA+=a[p];
        update(1,1,n,p,a[p]-b[p]);
        cout<<sumA-(pre[1]-min(0*1ll,mi[1]))<<'\n';
    }
    return 0;
}

```


---

