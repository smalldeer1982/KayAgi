# Chemistry Experiment

## 题目描述

One day two students, Grisha and Diana, found themselves in the university chemistry lab. In the lab the students found $ n $ test tubes with mercury numbered from $ 1 $ to $ n $ and decided to conduct an experiment.

The experiment consists of $ q $ steps. On each step, one of the following actions occurs:

1. Diana pours all the contents from tube number $ p_{i} $ and then pours there exactly $ x_{i} $ liters of mercury.
2. Let's consider all the ways to add $ v_{i} $ liters of water into the tubes; for each way let's count the volume of liquid (water and mercury) in the tube with water with maximum amount of liquid; finally let's find the minimum among counted maximums. That is the number the students want to count. At that, the students don't actually pour the mercury. They perform calculations without changing the contents of the tubes.

Unfortunately, the calculations proved to be too complex and the students asked you to help them. Help them conduct the described experiment.

## 样例 #1

### 输入

```
3 3
1 2 0
2 2
1 2 1
2 3
```

### 输出

```
1.50000
1.66667
```

## 样例 #2

### 输入

```
4 5
1 3 0 1
2 3
2 1
1 3 2
2 3
2 4
```

### 输出

```
1.66667
1.00000
2.33333
2.66667
```

# 题解

## 作者：GuuGuu (赞：14)

# 题目

[CF431E Chemistry Experiment](https://www.luogu.com.cn/problem/CF431E)

# 分析

线段树上二分，二分答案，线段树。

没人写 $1\log$ 的线段树上二分做法，这里提供一个。

首先，我们的目的是要求出尽可能小的最大体积，这显然是可以二分后直接判断的。

但是这样是 $2\log$ 的，我们可以直接考虑线段树上二分。

可是这样就需要实数的线段树上二分了吗？并不是。

我们考虑求答案的过程：先把要选的试管全部调整到同一个体积，再同时给所有的试管平均倒水。

显然，因为我们的修改操作只会出现整数的体积，所以这个调整到的体积一定是一个整数！

所以我们可以考虑并不直接线段树上二分出答案，而是二分出这个调整到的高度！

二分过程如下，每次先重置 $SIZE,SUM=0$ ：

> 其中 $sum$ 表示**值域区间**内水的体积和，$siz$ 表示**值域区间**内试管的个数。
>
> $SUM$ 表示左侧总的水的体积和，$SIZE$ 表示左侧总的试管个数

```cpp
ll SIZE,SUM;
ll Query(int x,int l,int r,ll lim){
	if(!x) return l;
	if(l==r) return SIZE+=siz(x),SUM+=sum(x),l;
	int mid=l+r>>1,MID=mid+1;//注意MID
	ll res=1ll*(siz(ls(x))+SIZE)*mid-(sum(ls(x))+SUM);
	if(res>=lim) return Query(ls(x),l,mid,lim);
	else return SIZE+=siz(ls(x)),SUM+=sum(ls(x)),Query(rs(x),mid+1,r,lim); 
}
```

接下来就是同时往上调整：

```cpp
else{
	read(l);//l是要分配的体积
    SIZE=SUM=0;
	int height=Query(Root,0,1e9,l);
	l=l-(SIZE*height-SUM);//现在l是多余的拿来分配的体积
	double Ans=(double)height+1.0*(double)l/(double)(SIZE);//加上多增加的高度
	printf("%.5lf\n",Ans);
}
```

那么就结束了，这里我们通过调整二分的对象规避了实数的线段树上二分。

时间复杂度 $O(n\log n)$ 。

#  代码

跑得比较快。


```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;bool f=false;char ch=getchar();
	while(!isdigit(ch)){f|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template<typename T>
inline void write(T x){
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
#define ll long long
#define ull unsigned long long
#define inc(x,y,mod) (((x)+(y))>=(mod)?(x)+(y)-(mod):(x)+(y))
#define dec(x,y,mod) ((x)-(y)<0?(x)-(y)+(mod):(x)-(y))
#define rep(i,x,y) for(register int i=(x);i<=(y);i++)
#define dep(i,y,x) for(register int i=(y);i>=(x);i--)
const int N=1e5+5,M=2e5+5,MOD=1e9+7;
int n,m,h[N],cur;
struct SGT{
	int siz,ls,rs;
	ll sum;
	#define ls(x) t[x].ls
	#define rs(x) t[x].rs
	#define sum(x) t[x].sum
	#define siz(x) t[x].siz
}t[N<<6];
void Modify(int &x,int l,int r,int pos,int v){
	if(!x) x=++cur;
	siz(x)+=v,sum(x)+=v*pos;
	if(l==r) return ;
	int mid=l+r>>1;
	if(pos<=mid) Modify(ls(x),l,mid,pos,v);
	else Modify(rs(x),mid+1,r,pos,v);
	return ;
}
ll SIZE,SUM;
ll Query(int x,int l,int r,ll lim){
	if(!x) return l;
	if(l==r) return SIZE+=siz(x),SUM+=sum(x),l;
	int mid=l+r>>1,MID=mid+1;
	ll res=1ll*(siz(ls(x))+SIZE)*MID-(sum(ls(x))+SUM);
	if(res>=lim) return Query(ls(x),l,mid,lim);
	else return SIZE+=siz(ls(x)),SUM+=sum(ls(x)),Query(rs(x),mid+1,r,lim); 
}
int Root;
signed main(){
	read(n);read(m);
	rep(i,1,n) read(h[i]),Modify(Root,0,1e9,h[i],1);
	while(m--){
		ll op,l,r;
		read(op);
		if(op==1) read(l),read(r),Modify(Root,0,1e9,h[l],-1),Modify(Root,0,1e9,(h[l]=r),1);
		else{
			read(l);SIZE=SUM=0;
			int height=Query(Root,0,1e9,l);
			l=l-(SIZE*height-SUM);
			double Ans=(double)height+1.0*(double)l/(double)(SIZE);
			printf("%.5lf\n",Ans);
		}
	}
	
	return 0;
}
```


---

## 作者：Mobius127 (赞：8)

提供一种简单而又好理解的思路。

[题目传送门](https://www.luogu.com.cn/problem/CF431E)

操作一直接跳过，单点修改太逊了。

看操作二：这玩意什么鬼？

仔细分析一下，一个结论明显得出：


- 最后有水的试管水面高度都是相同的。

这个显然，因为题目要求最高的水平水面尽量矮，所以若有水面高度差，我们直接拿高的往低的里面灌就能减小答案。

同时，我们发现，答案具有单调性。也就是说，我们如果强制所有水面到达 $x$ 高度这个方案可行，那么所有 $\ge x$ 的方案均可。

果断二分答案。

二分 $mid$ 之后，思考如何判断这个答案可不可行。

因为只能往小于等于 $mid$ 的试管里面灌，也就是说我们要统计出所有高度小于等于 $mid$ 的试管的数量 $num$，同时也要统计这些试管里面水银的体积 $sum$。如果 $num \times mid - sum \ge v$ 这个 $mid$ 就是可行的（自行画图体会）。

又由于没有区间限制，而且 mid 值不确定，果断上权值线段树 + 动态开点。

然后。。。就写完了？？

时间复杂度 $O(mlog^2S)$。不是很需要卡常。

注意动态开点不要使用 vector，内存尽量卡大一点即可

### Code

```cpp
    #include <stdio.h>
    #include <algorithm>
    #include <cmath>
    #include <vector>
    #define int long long
    #define N 100005
    using namespace std;
    typedef long long ll;
    typedef double ld;
    const int INF=1e10;
    const ld exep=1e-5;
    int root, cnt;
    struct node{int num, lc, rc;ll sum;}null;
    node operator + (node a, node b){
    	node c;c.sum=a.sum+b.sum, c.num=a.num+b.num;
    	return c;
    }
    struct Segment_Tree{
    	#define mid (l+r>>1)
    	node V[N*30];
    	void pre(){
    		null.sum=0, null.num=0;
    		null.lc=null.rc=0;
    	}
    	void pushup(int k){
    		V[k].sum=V[k].num=0;
    		if(V[k].lc){
    			V[k].sum+=V[V[k].lc].sum;
    			V[k].num+=V[V[k].lc].num;
    		}
    		if(V[k].rc){
    			V[k].sum+=V[V[k].rc].sum;
    			V[k].num+=V[V[k].rc].num;
    		}
    	}
    	void add(int &k, int l, int r, int x, int v){
    		if(!k) k=++cnt, V[k]=null;
    //		printf("%d %d %d %d %d\n", k, l, r, mid, x);
    //		system("pause");
    		if(l==r){
    			V[k].num+=v;V[k].sum=V[k].num*x;
    			return ;
    		}
    		if(x<=mid) add(V[k].lc, l, mid, x, v);//printf("goleft\n"), 
    		else add(V[k].rc, mid+1, r, x, v);//printf("goright\n"), 
    		return pushup(k);
    	}
    	node query(int &k, int l, int r, int x, int y){
    		if(!k) return null;
    		if(x<=l&&r<=y) return V[k];
    		node ret=null;
    		if(x<=mid) ret=ret+query(V[k].lc, l, mid, x, y);
    		if(mid<y) ret=ret+query(V[k].rc, mid+1, r, x, y);
    		return ret;
    	}
    	#undef mid
    }chtholly;
    int n, m;
    int turn(ld x){
    	ll f=ceil(x);
    	return f>INF?INF:f;
    }
    bool check(ld mid, ld sum){
    	node ans=chtholly.query(root, 0, INF, 0, turn((ll)mid));
    //	printf("%lf %d %lld\n", mid, ans.num, ans.sum);
    	ld gt=(ld)1ll*ans.num*mid-(ld)ans.sum;
    	if(gt>=sum) return 1;
    	return 0;
    }
    int a[N];
    signed main(){
    	chtholly.pre();
    	scanf("%lld%lld", &n, &m);
    	for(int i=1; i<=n; i++){
    		scanf("%lld", &a[i]);
    		chtholly.add(root, 0, INF, a[i], 1);
    	}
    	for(int i=1; i<=m; i++){
    		int opt;scanf("%lld", &opt);
    		if(opt&1){
    			int x, v;scanf("%lld%lld", &x, &v);
    			chtholly.add(root, 0, INF, a[x], -1);
    			a[x]=v;
    			chtholly.add(root, 0, INF, v, 1);
    		}
    		else{
    			ll v;scanf("%lld", &v);
    			ld l=0, r=1e15, ans;
    			while(l+exep<r){
    				ld mid=(l+r)/2.0;
    				if(check(mid, (ld)v)) ans=mid, r=mid;
    				else l=mid;
    			}
    			printf("%.5lf\n", ans);
    		}
    	}
    	return 0;
    }
```


---

## 作者：Alex_Eon (赞：6)

#### [$\color{red}博客内食用效果更佳（点我）$](https://www.luogu.com.cn/blog/Ksy/solution-cf431e)

### 题外话
又被 long long 卡半天，为了警示自己，写一篇题解。
### 思路：（动态开点权值线段树）线段树+二分
### 复杂度：$O(m\log^2(n))$
### 主体思路
首先很显著从水银少的试管向水银多的试管依次取，并且最终倒完水后所有试管里的液面相平。

考虑将倒水分为两部分，先用水将所选的试管都填到同一高度（所选的试管水银高度中的最大值），然后如果有剩余则平均填到每一个试管中。先考虑暴力从前向后枚举选前 $i$ 个水银最少的试管。如果 $i-1$ 倒完水后的液面高于 $i$，那么将 $i$ 选中显著是更优的，否则更劣。

排序后暴力枚举的话显然不支持修改，考虑权值线段树维护，因为空间限制需要动态开点。

如果选中前 $i$ 个水银最少的试管劣于选 $i-1$ 个，那么再向后选都不会更优，考虑直接二分选择前多少个试管，尝试找到最大的 $i$ 使得选前 $i$ 为更优的策略。

#### 具体实现
线段树节点需要维护：
- 区间内试管个数。
- 区间内试管水银总和。

线段树需要支持：
- 查询前 $rk$ 名试管水银总和。
- 查询第 $rk$ 名试管水银高度。

对于 $mid$：设 $pos$ 为第 $mid$ 个试管的水银高度，$q$ 为前 $mid$ 个试管水银的和，$x$ 为查询的值。
- 若 $pos\times mid-q>x$ 即无法填平所选试管，则选前 $mid$ 个试管一定为劣解，否则为优解。

### 代码实现需要注意的地方：

- 要开 **long long**。
- 注意二分边界、条件设置。

### 参考代码：
参考代码中变量名与题解中均一致，详见注释。
```cpp
#define LL long long
#define UN unsigned
#include<bits/stdc++.h>
using namespace std;
//--------------------//
const int N=1e5+5;

int n,m;
LL a[N];
//--------------------//
const int TN=N<<6;
struct Seg_Tree
{
	struct Seg_Tree_Node
	{
		int ls,rs;
		int cnt;
		LL val;
	}t[TN];
	int tot,root;

	void push_up(int rt){t[rt].cnt=t[t[rt].ls].cnt+t[t[rt].rs].cnt,t[rt].val=t[t[rt].ls].val+t[t[rt].rs].val;}

	void change(int &rt,int L,int R,int pos,int val)
	{
		if(!rt)
			rt=++tot;
		if(L==R)
		{
			t[rt].cnt+=val;
			t[rt].val+=1LL*val*L;
			return;
		}
		int mid=L+R>>1;
		if(pos<=mid)
			change(t[rt].ls,L,mid,pos,val);
		else
			change(t[rt].rs,mid+1,R,pos,val);
		push_up(rt);
		return;
	}

	LL query(int &rt,int L,int R,int rk)//查询前 rk 个的和
	{
		if(!rt)
			return 0;
		if(rk==t[rt].cnt)
			return t[rt].val;
		if(L==R)
			return L*rk;
		int mid=L+R>>1;
		LL res=0;
		res=query(t[rt].ls,L,mid,min(rk,t[t[rt].ls].cnt));//查左区间
		if(rk>t[t[rt].ls].cnt)//若排名超过左侧区间的元素个数，查右区间
			res+=query(t[rt].rs,mid+1,R,rk-t[t[rt].ls].cnt);
		return res;
	}

	int queryrk(int &rt,int L,int R,int rk)//查询第 rk 个的高度
	{
		if(!rt)
			return 0;
		if(L==R)
			return L;
		int mid=L+R>>1;
		if(t[t[rt].ls].cnt>=rk)//在左区间
			return queryrk(t[rt].ls,L,mid,rk);
		return queryrk(t[rt].rs,mid+1,R,rk-t[t[rt].ls].cnt);//在右区间
	}
}T;
//--------------------//
double mim(LL x)//二分
{
	int l=1,r=n,res=0;
	while(l<=r)
	{
		int mid=l+r>>1,pos=T.queryrk(T.root,0,1e9,mid);
		LL q=T.query(T.root,0,1e9,mid);
		if(1LL*pos*mid-q>x)//若为劣解
			r=mid-1;
		else//否则为优解
			l=mid+1,res=mid;
	}
	if(!res)
		res=1;
	LL q=T.query(T.root,0,1e9,res);
	return 1.0*(q+x)/res;//液体总量除以试管个数为答案
}
//--------------------//	
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),T.change(T.root,0,1e9,a[i],1);
	LL x;
	for(int op,i=1;i<=m;i++)
	{
		scanf("%d%lld",&op,&x);
		if(op==1)
		{
			T.change(T.root,0,1e9,a[x],-1);
			scanf("%lld",&a[x]);
			T.change(T.root,0,1e9,a[x],1);
		}
		else
			printf("%.5lf\n",mim(x));
	}
 	return 0;
}
```


---

## 作者：Islauso (赞：4)

[更好的阅读体验](https://www.azusemisa.top/posts/128296706.html)

## 题目大意

给出一个长度为 $n$ 的序列，要求支持两种操作：1、单点修改。2、**如果**从 $n$ 个数中选出一些数，给他们一共加上 $k$，求加完后这些数中最大值的最小值（只是假设，并不是真的要加上）。

## 思路

第一种操作很简单，我们重点考虑一下第二种。

什么情况下最优呢？显然，应该是选出来的这些数在加完之后值一样的时候，而且我们应该尽量多选一些数，这样平均下来才会尽量小。

也就是说，假设最后选出来的这些数在一共加上 $k$ 之后的值都为 $b$，那我们要选的数就是所有小于等于 $b$ 的，但这样会很麻烦，因为随着选数方案的改变，$b$ 也会随之而变，所以我们可以换种思路。

我们随便选一个数 $t$ 出来，以它作为标准，把所有小于等于它的数都选出来，然后先把小于它的数累加到等于它，然后再一起累加。

相当于是这样。

![](https://cdn.jsdelivr.net/gh/xiao-lin52/image-upload/20210119195614.png)

以第四个数为标准，先把其他小于它的数加到和它一样。

![](https://cdn.jsdelivr.net/gh/xiao-lin52/image-upload/20210119195655.png)

然后再一起累加。

![](https://cdn.jsdelivr.net/gh/xiao-lin52/image-upload/20210119195715.png)

这样，选出来的作为标准的这个数 $t$ 就很关键了，显然它不能太大，不然其他的数还没有加到和它一样就已经把 $k$ 用完了，但它也不能太小，因为有可能存在一个数 $x$，一开始的时候，$x$ 是大于 $t$ 的，但在最后一起累加的时候，它又小于累加后得到的数了，这样就会存在浪费，那我们要怎么找出这个不大不小刚刚好的 $t$ 呢？

不难发现，$t$ 是可以二分的，具体来说，我们按照刚刚那个办法，先随便找一个数作为 $t$，如果其他小于它的数没法全部累加到和它一样，就说明这个数太大了，反之，如果可以，就说明这个数也许是正确答案，我们就可以继续往大的去找。

那么问题又来了，显然要求出所有小于等于它的数能否累加到和它一样，我们就需要知道这些数的数量和总和，显然如果暴力查找单次询问是 $O(n\log n)$ 的，所以有没有一种数据结构之类的东西能快速维护这两个值呢？

平衡树啊！

我们可以直接把二分的过程放到平衡树上去，显然平衡树是可以很好的维护我们需要的这两个值的，这样单次询问复杂度就降到了 $O(\log n)$，轻松过掉 $10^5$。

啊对了，这里有一个坑点，由于我们需要知道的是所有小于等于 $t$ 的数的总和和数量，所以光统计这个点的左儿子是不够的，还要考虑到它祖先的左儿子，不过这个可以在递归的过程中累加，如果是往右儿子走，我们就把当前这个点及它左儿子这颗子树中的信息累加到一个变量里，在计算时，把这个变量的值也塞到一块进行计算就行了。

## 参考代码

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = (l), i##end = (r); i <= i##end; i++)
#define per(i, r, l) for(int i = (r), i##end = (l); i >= i##end; i--)
#define debug(x) cerr<<#x<<" = "<<x
#define pii pair<int, int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int N = 1e5+10, mod = 20060209;
const double inf = 1e16;
int n, m, rt, sed, tot, son[N<<1][2], siz[N<<1], num[N<<1], rnd[N<<1];
ll a[N], val[N<<1], sum[N<<1];//这里采用常数小码量也小的 Treap
inline int rd()
{
	return sed = 114514ll*sed%mod*1919810%mod;
}
inline void push_up(int p)
{
	siz[p] = siz[son[p][0]]+siz[son[p][1]]+num[p];
	sum[p] = sum[son[p][0]]+sum[son[p][1]]+val[p]*num[p];
}
inline void spin(int &p, int s)//板子
{
	int t = son[p][s];
	son[p][s] = son[t][s^1];
	son[t][s^1] = p;
	push_up(p);
	push_up(t);
	p = t;
}
void ins(int &p, ll k)//板子
{
	if(!p)
	{
		p = ++tot;
		rnd[p] = rd();
		siz[p] = num[p] = 1;
		val[p] = sum[p] = k;
		return;
	}
	if(val[p] == k)
	{
		num[p]++;
		siz[p]++;
		sum[p] += k;
		return;
	}
	int t = (val[p] < k);
	ins(son[p][t], k);
	if(rnd[son[p][t]] > rnd[p])
		spin(p, t);
	push_up(p);
}
void del(int &p, ll k)//板子
{
	if(!p)
		return;
	if(val[p] == k)
	{
		if(num[p] > 1)
		{
			num[p]--;
			siz[p]--;
			sum[p] -= k;
			return;
		}
		if(!son[p][0] && !son[p][1])
			p = 0;
		else if(son[p][0] && !son[p][1])
		{
			spin(p, 0);
			del(son[p][1], k);
		}
		else if(!son[p][0] && son[p][1])
		{
			spin(p, 1);
			del(son[p][0], k);
		}
		else
		{
			int t = (rnd[son[p][0]] < rnd[son[p][1]]);
			spin(p, t);
			del(son[p][t^1], k);
		}
		push_up(p);
		return;
	}
	int t = (val[p] < k);
	del(son[p][t], k);
	if(rnd[son[p][t]] > rnd[p])
		spin(p, t);
	push_up(p);
}
double query(int p, ll k, ll s1, int s2)//s1 和 s2 记录祖先的左子树的信息
{
	if(!p)
		return inf;
	double t = (s1+sum[p]-sum[son[p][1]]+k)*1.0/(s2+siz[p]-siz[son[p][1]]);//计算给所有小于等于当前数一共加上 k 以后最小的值，也就是上面的图三的结果
	if(t > val[p])//往右儿子递归
		return min(query(son[p][1], k, s1+sum[p]-sum[son[p][1]], s2+siz[p]-siz[son[p][1]]), t);
	else
		return query(son[p][0], k, s1, s2);
}
int main()
{
	sed = time(0)%mod;
	scanf("%d%d", &n, &m);
	rep(i, 1, n)
		scanf("%d", &a[i]), ins(rt, a[i]);
	rep(i, 1, m)
	{
		int op, p;
		ll v;
		scanf("%d", &op);
		if(op == 1)
		{
			scanf("%d%lld", &p, &v);
			del(rt, a[p]);
			ins(rt, v);
			a[p] = v;
		}
		else
		{
			scanf("%lld", &v);
			printf("%.5lf\n", query(rt, v, 0, 0));
		}
	}
	return 0;
}
```

---

## 作者：275307894a (赞：4)

[题面传送门](https://www.luogu.com.cn/problem/CF431E)

题解里居然没有写线段树上二分的，来交一发。

维护一颗权值线段树，以$h_i$为下标，主要维护两个值，是元素个数和元素和。
那么当前点$m$可以判断左边的节点数$\times m-$左边的元素和是否大于当前的水量来考虑走左边还是右边。走到最后一个节点时计算剩下的水量，然后均摊给每一个试管。

时间复杂度$O(nloga)$，一点不卡常。

代码实现:
```cpp
#include<cstdio>
#define l(x) f[x].l
#define r(x) f[x].r
using namespace std;
int n,m,k,y,x,tot,pus,root,cnt,sx,a[100039];
long long z;
struct tree{int l,r,siz;long long f;}f[10000039];
inline void get(long long x,int y,long long l,long long r,int &now){
	if(!now) now=++cnt;
	if(l==r) {f[now].f+=x*y;f[now].siz+=y;return ;}
	double m=(l+r)/2;
	if(x<=m) get(x,y,l,m,l(now));
	else get(x,y,m+1,r,r(now));
	f[now].f=f[l(now)].f+f[r(now)].f;
	f[now].siz=f[l(now)].siz+f[r(now)].siz;
}
inline double find(long long x,long long l,long long r,int now){
	long long siz=0;long long fs=0;
	while(l!=r){
		double m=(l+r)/2;
		if(x>=m*(siz+f[l(now)].siz)-fs-f[l(now)].f)l=m+1,fs+=f[l(now)].f,siz+=f[l(now)].siz,now=r(now);
		else r=m,now=l(now);
	}
	return l+(x-(l*(siz+f[l(now)].siz)-fs-f[l(now)].f))*1.0/siz;
}
inline void read(int &x){
	char s=getchar();x=0;
	while(s<'0'||s>'9') s=getchar();
	while(s>='0'&&s<='9') x=(x<<3)+(x<<1)+(s^48),s=getchar();
}
int main(){
//	freopen("1.in","r",stdin);
	register int i;
	read(n);read(m);
	for(i=1;i<=n;i++) read(a[i]),get(a[i],1,0,1e13,root);
	for(i=1;i<=m;i++){
		read(sx);
		if(sx==1) read(x),read(y),get(a[x],-1,0,1e13,root),a[x]=y,get(a[x],1,0,1e13,root);
		else scanf("%lld",&z),printf("%.5lf\n",find(z,0,1e13,root));
	}
}
```

---

## 作者：FxorG (赞：2)

## $\text{Description}$

你要将v分给一些数字，使得这些数字的最大值最小。

~~然而我看成了使得全局最大值最小。~~

## $\text{Solution}$

感觉这题很水啊，不知道怎么评黑的。

先考虑询问，发现最大值最小，不难想到二分答案。

考虑其单调性，假如体积为 $ans$ 时可以分配成功，那么 $ans+1$ 也必定可以。

之后，我们不难想到，应该是所有 $\le mid$ 的数都得分配的。

所以我们只需要考虑

$$ \sum h_i \ (h_i \le mid) $$

这东西无脑权值线段树顺便一手动态开点，二分精度开 $1e-4$ 就好。

## $\text{Code}$
```cpp
#include <bits/stdc++.h>

#define N (int)(1e5+5) 
#define db double
#define inf (int)(1e9)
#define int long long

using namespace std;

struct node {
	int ls,rs,sum,cnt;
}t[N*50];

int a[N];
int tot,rt,n,m;

void update(int &cur,int l,int r,int x,int v,int vc) {
	if(!cur) cur=++tot;
	if(l==r) {
		t[cur].sum+=v; t[cur].cnt+=vc;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(t[cur].ls,l,mid,x,v,vc);
	else update(t[cur].rs,mid+1,r,x,v,vc);
	t[cur].sum=t[t[cur].ls].sum+t[t[cur].rs].sum;
	t[cur].cnt=t[t[cur].ls].cnt+t[t[cur].rs].cnt;
}

int query(int cur,int l,int r,int cl,int cr,bool fl) {
	if(!cur) return 0;
	if(r==inf&&cr>r) cr=inf;
	if(cl<=l&&r<=cr) return fl?t[cur].sum:t[cur].cnt;
	int mid=(l+r)>>1,res=0;
	if(cl<=mid) res=query(t[cur].ls,l,mid,cl,cr,fl);
	if(cr>mid) res+=query(t[cur].rs,mid+1,r,cl,cr,fl);
	return res;
}

db solve(int x) {
	db l=0.0,r=1e15,res=0.0;
	while(l<r-(1e-4)) {
		db mid=(l+r)/2.0;
	//	cout<<(int)mid<<' '<<query(rt,0,inf,0,mid,1)+x<<" "<<query(rt,0,inf,0,mid,0)*mid<<endl;
		if((query(rt,0,inf,0,mid,1)+x)<=query(rt,0,inf,0,mid,0)*mid) res=r=mid;
		else l=mid;
	}
	return res;
}

int rd() {
	int f=1,sum=0; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}


signed main() {
	int op,x,y;
	n=rd(); m=rd();
	for(int i=1;i<=n;i++) a[i]=rd(),update(rt,0,inf,a[i],a[i],1);
	while(m--) {
		op=rd();
		if(op==1) {
			x=rd(); y=rd();
			update(rt,0,inf,a[x],-a[x],-1);
			update(rt,0,inf,y,a[x]=y,1);
		} else {
			x=rd();
			printf("%.4lf\n",solve(x));
		}
	}
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：1)

题目翻译有点难绷。

浮点数直接计算比较困难，考虑二分答案转化为可行性判断。即求出不大于某个体积最多能放多少水再比较即可。

然后问题就是如何求不大于某个容积最多能放多少水。

已知体积二分到 $K$，那么水银体积所有不大于 $K$ 的都可以产生贡献。我们可以用总体积减水银体积来计算，所以问题转化为求有多少瓶水银体积不大于 $K$ 和这些水银的总体积。

考虑把询问离线下来，把所有水银体积离散化，然后把体积映射到值域上，开值域线段树即可解决问题。

对于满足要求的瓶子个数，每个瓶子的体积对应的位置加一；对于满足要求的总体积，每个瓶子的体积对应的位置加上体积即可。

最后的查询可以用线段树二分也可以先二分出位置再查询，整个二分过程也可以直接在线段树上二分，但我没写。

下述代码的时间复杂度为 $O(n \log n (\log V+\log \frac{1}{\varepsilon}))$。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<bitset>
#include<ctime>
#define int long long
#define ls (p<<1)
#define rs (p<<1|1)
#define mid ((l+r)>>1)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
const double eps=1e-5;
struct Que{
	int opt,x,y;
}q[N];
int n,m,k,a[N];
int b[N],c[N],d[N],to[N],cnt;
map<int,int>vis;
struct Tree{
	int sum[N<<2],id;
	inline void pushup(int p){
		sum[p]=sum[ls]+sum[rs];
	}
	void build(int p,int l,int r){
		if(l==r){
			if(id==1)
				sum[p]=c[l];
			else sum[p]=d[l];
		//	sum[p]=id==1?c[l]:1;
			return;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(p);
	}
	void update(int x,int p,int l,int r,int k){
		if(l==x&&x==r){
			sum[p]+=k;
			return;
		}
		if(x<=mid)update(x,ls,l,mid,k);
		if(x>mid) update(x,rs,mid+1,r,k);
		pushup(p);
	}
	inline int query(int L,int R,int p,int l,int r){
		if(L>R)
			return 0;
		if(L<=l&&r<=R)
			return sum[p];
		int res=0;
		if(L<=mid)res+=query(L,R,ls,l,mid);
		if(R>mid) res+=query(L,R,rs,mid+1,r);
		return res;
	}
}T1,T2;
int get(double x){
	int l=1,r=k,ans=0;
	while(l<=r){
		if(to[mid]<=x){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return ans;
}
int check(double x,int y){
	int p=get(x);
	int s1=T1.query(1,p,1,1,k),s2=T2.query(1,p,1,1,k);
	double res=s2*x-s1;
	if(res>=y)
		return 1;
	return 0;
}
signed main()
{
	//freopen("t1.in","r",stdin);
	//freopen("t1.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[++cnt]=a[i];
	}
	for(int i=1;i<=m;i++){
		q[i].opt=read();
		if(q[i].opt==1){
			q[i].x=read(),q[i].y=read();
			b[++cnt]=q[i].y;
		}
		else q[i].x=read();
	}
	sort(b+1,b+cnt+1);
	k=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=k;i++){
		vis[b[i]]=i;
		to[i]=b[i];
	}
	for(int i=1;i<=n;i++){
		c[vis[a[i]]]+=a[i];
		d[vis[a[i]]]++;
	}
	T1.id=1,T2.id=2;
	T1.build(1,1,k);
	T2.build(1,1,k);
	for(int i=1;i<=m;i++){
		int opt=q[i].opt,x=q[i].x,y=q[i].y;
		if(opt==1){
			int w=vis[y],p=vis[a[x]];
			T1.update(p,1,1,k,-a[x]);
			T2.update(p,1,1,k,-1);
			a[x]=y;
			T1.update(w,1,1,k,a[x]);
			T2.update(w,1,1,k,1);
		}
		if(opt==2){
			double l=0,r=1e15,ans=l;
			while(r-l>eps){
				double midd=(l+r)/2;
				if(check(midd,q[i].x)){
					r=midd;
					ans=midd;
				}
				else l=midd;
			}
			printf("%.5lf",ans);
			putchar('\n');
		}
	}
	return 0;
}


```

---

## 作者：5k_sync_closer (赞：1)

权值线段树。

>finally let's find the minimum among counted maximums.

最大值最小。二分。设当前二分中点为 $k$。

容易发现 $h_i\le k$ 的试管才会造成贡献，若 $\sum\limits_{h_i\le k}k-h_i\ge v$ 则 $k$ 合法。

$\sum\limits_{h_i\le k}k-h_i=\sum\limits_{h_i\le k}k-\sum\limits_{h_i\le k}h_i$。分别用权值线段树维护即可。

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
struct T
{
	T *l = 0, *r = 0;
	int c = 0;long long s = 0;
	void u()
	{
		c = s = 0;
		if(l) c += l->c, s += l->s;
		if(r) c += r->c, s += r->s;
	}
}*r;
void M(int l, int x, int y, int s, int t, T *&p)
{
	if(!p) p = new T;if(s == t) return (void)(p->c += x, p->s += y);int m = s + t
	>> 1;if(l <= m) M(l, x, y, s, m, p->l);else M(l, x, y, m + 1, t, p->r);p->u();
}
int X(int l, int r, int s, int t, T *p)
{
	if(!p) return 0;if(l <= s && t <= r) return p->c;int m = s + t >> 1, q = 0;if(l
	<= m) q += X(l, r, s, m, p->l);if(r > m) q += X(l, r, m + 1, t, p->r);return q;
}
long long Y(int l, int r, int s, int t, T *p)
{
	if(!p) return 0;if(l <= s && t <= r) return p->s;int m = s + t >> 1;long long q = 0;
	if(l <= m) q += Y(l, r, s, m, p->l);if(r > m) q += Y(l, r, m + 1, t, p->r);return q;
}
int n, m, a[100050];long long x;double L, R, K;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;++i)
		scanf("%d", a + i), M(a[i], 1, a[i], 0, 1e9, r);
	for(int i = 0, o;i < m;++i)
	{
		scanf("%d%lld", &o, &x);
		if(o & 1) M(a[x], -1, -a[x], 0, 1e9, r), scanf("%d", a + x), M(a[x], 1, a[x], 0, 1e9, r);
		else
		{
			L = 0;R = 1e11;while(fabs(L - R) > 1e-5){K = (L + R) / 2;
			if(K * X(0, min(K, 1e9), 0, 1e9, r) - Y(0, min(K, 1e9), 0, 1e9, r) >= x)
			R = K;else L = K;}printf("%.5lf\n", L);
		}
	}
}
```


---

## 作者：Purslane (赞：0)

## Solution

为方便理解 , 把水银改为汞 .

首先 , 我们应分析出结论 : 水一定是集中在汞最少的几个试管里 , 而且水面一样平 . 

> 这很好理解 , 如果把水放在汞多的试管里面 , 那么把水转移到汞少的肯定不劣 . 

> 同样 , 如果水面不一样平 , 把水面高的中多余的水转到水面低的也不劣 .

所以我们要支持部动态删减 , 维护有序的数组 , 平衡树是个不错的选择 .

最后答案肯定是把前 $k$ 个试管都补的和试管 $k$ 中的汞一样高 , 试着二分出 $k$ . 

由于平衡树是平衡的 , 所以遍历它 , 复杂度 $O(\text{m log n})$ . 具体做法是 , 记录子树内的节点数以及权值和 . 

二分的时候 , 记录子树外已经有多少节点数和权值和 , 计算补平需要多少 . 

如果足够 , 就走向右子树 , 否则走向左子树 . 

实现的话 , 参考二分答案是怎么实现的 .

[code](https://codeforces.com/contest/431/submission/150026290) .

452 ms , 所以 FHQ 的常数也没有那么可怕 ?

---

