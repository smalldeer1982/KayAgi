# Drink Bar

## 题目描述

[problemUrl]: https://atcoder.jp/contests/snuke21/tasks/snuke21_j



# 题解

## 作者：封禁用户 (赞：9)

是模拟赛的题目，有部分分提示的话会比较好想。~~然而并不意味着我考试时做出来了。~~  

### 题意

给定 $n$ 个三元组 $(a_i,b_i,c_i)$，对于下标的一个非空子集定义其特征值为 $(\max\limits_{i\in S}a_i,\max\limits_{i\in S}b_i,\max\limits_{i\in S}c_i)$。

问有多少不同的特征值三元组。

数据范围：$n\leq 10^5$。

### 暴力的分析

首先考虑一个暴力的 $\mathcal{O}(n^3)$ 做法，即枚举 $(i,j,k)$ 下标表示 $(a_i,b_j,c_k)$ 能否是一组特征值。  

显然，选的三元组越多越不容易满足 $a_i,b_j,c_k$ 为最大值，所以我们只会选择 $(i,j,k)$ 三个三元组。  

这样只需要判断是否 $a_i\gt\max(a_j,a_k)$ 且 $b_j\gt\max(a_i,a_k)$ 且 $c_k\gt\max(c_i,c_j)$。   

### 正解的分析  

$\mathcal{O}(n^3)$ 的暴力告诉我们只需要看 $(i,j,k)$ 这样的对是否是 $(a,b,c)$ 的最大值即可。

而这意味着我们只需要那些三个三元组满足，不妨分情况讨论。

#### 若 $i=j=k$。

即只有一个三元组，那肯定合法，这样的三元组个数为 $n$。

#### 若 $i,j,k$ 有两个相等。

也就是选两个三元组，总方案数显然是 $\binom{n}{2}$ 的。

然而我们很快发现这样会计算重复，即出现 $a_i\gt a_j,b_i\gt b_j,c_i\gt c_j$ 那就和只选一个没有区别了，我们要去掉这样的三元组。

尝试计算出 $P_i$ 表示被 $i$ 三元组形成这样 '三维偏序' 的个数，则我们需要减去 $\sum P_i$。

计算 $P_i$ 显然是用 cdq 分治，这里并不展开。

#### 若 $i,j,k$ 均不相等。

即你要选三个三元组，总方案显然是 $\binom{n}{3}$。

明显有不合法的情况，仔细思考后分为两种：

- 有一个位置同时占领了两个特征值的最大。
 
- 有一个位置占领了所有特征值。
 
先考虑第一种：

- 我们显然研究占领了两个特征值的最大的哪个位置（因为它限制多）。
 
- 发现它需要满足 $a_i\gt a_j,a_i\gt a_k$ 且 $b_i\gt b_j,b_i\gt b_k$ 我们称这样为关于 ab 的二维偏序。同样还有 ac 的二维偏序，bc 的二维偏序。
 
- 二维偏序是可以简单计算的，令它们为 $A_i,B_i,C_i$。
 
- 我们发现造成这种不合法是因为 $i$ 选择了两个被它二维偏序的点，这种方案是 $\binom{A_i}{2}+\binom{B_i}{2}+\binom{C_i}{2}$ 的。
 
- 可是你发现它计重了，对于被三维偏序的点,它在三个里边被减了三次，不过我们先不着急加上，因为还有一个情况没分析。

再考虑第二种：

- 有了刚才的经验，不合法的状况显然是当选了两个被 $i$ 三维偏序的点，即 $\binom{P_i}{2}$。
 
- 那么我们相当于要加上两次 $\binom{P_i}{2}$。

如此，本题便优雅的结束了。用到了一种类似容斥的思想。

考虑题目的难点在哪里，额，似乎只要想到考虑 $(i,j,k)$ 的关系后面是很顺的。

~~那为什么我没想到勒。~~

### 代码实现

一直以来，我都觉得我写代码是比较好看的，然而这个题写的确实比较丑，凑合看看就好。

注释就不给了，算法流程还是很明确的。

```cpp
//Shirosaki Hana kawaii
#include<bits/stdc++.h>
const int QWQ=2e5+5;
using namespace std;
#define id(i) t[i].id
#define a(i) t[i].a
#define b(i) t[i].b
#define c(i) t[i].c
using LL=long long;
inline int read(){
	int x=0,f=1; char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar())
		if (ch=='-') f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())
		x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
struct unit{ int a,b,c,id; } t[QWQ];
int T,n,s[QWQ]; LL p3[QWQ],p2[3];
inline LL C(int x){ return (LL)x*(x-1)/2; }
inline bool cmp(unit x,unit y){ return x.a<y.a; }
inline bool cnp(unit x,unit y){ return x.b<y.b; }
inline void add(int x,int v){ for (;x<=n;x+=(x&-x)) s[x]+=v; }
inline int ask(int x,int r=0){ for (;x;x-=(x&-x)) r+=s[x]; return r; }
#define mid (l+r>>1)
void solve(int l,int r){
	if (l==r) return ;
	solve(l,mid),solve(mid+1,r);
	sort(t+l,t+mid+1,cnp);
	sort(t+mid+1,t+r+1,cnp);
	int j=l;
	for (int i=mid+1;i<=r;i++){
		for (;j<=mid&&b(j)<b(i);add(c(j++),1));
		p3[id(i)]+=ask(c(i));
	}
	for (;j>l;add(c(--j),-1));
}
signed main(){
	n=read();
	for (int i=1;i<=n;i++)
		a(i)=read(),b(i)=read(),c(i)=read();
	for (int i=1;i<=n;i++) id(i)=i;
	sort(t+1,t+n+1,cmp);
	solve(1,n);
	sort(t+1,t+n+1,cmp);
	for (int i=1;i<=n;i++)
		p2[0]+=C(ask(b(i))),add(b(i),1);
	fill(s+1,s+n+1,0);
	for (int i=1;i<=n;i++)
		p2[1]+=C(ask(c(i))),add(c(i),1);
	fill(s+1,s+n+1,0);
	sort(t+1,t+n+1,cnp);
	for (int i=1;i<=n;i++)
		p2[2]+=C(ask(c(i))),add(c(i),1);
	fill(s+1,s+n+1,0);
	LL ret=(LL)n*(n-1)*(n-2)/6+C(n)+n;
	ret=ret-p2[0]-p2[1]-p2[2];
	for (int i=1;i<=n;i++) ret-=p3[i]-2ll*C(p3[i]);
	printf("%lld",ret);
	return 0;
} 
```

---

## 作者：do_it_tomorrow (赞：6)

[更好的阅读体验](https://www.doittomorrow.xyz/post/at-snuke21-j-drink-bar-de-ti-jie/)

NOIp 模拟赛考了，遂记之。

容易发现 $\nexists(A,B,C)$ 使 $\forall S$ 满足 $\lvert S \rvert>3$，因为 $(A,B,C)$ 中只有 $3$ 个元素，多了就放不进去了。

考虑分 $3$ 中情况讨论。

**对于第 $1$ 中情况，$\lvert S \rvert=1$。**

因为 $a,b,c$ 都是排列所以一定不存在重复的 $(A,B,C)$，自然答案就是 $n$。

**对于第 $2$ 种情况，$\lvert S \rvert=2$。**

考虑使用容斥，显然总方案为 $n\choose 2$，考虑怎么计算不合法的方案。

在这个情况下，不合法的方案显然就是 $(A,B,C)$ 全部来自一个位置。

换而言之，不合法的数量就是 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n [(a_i<a_j)\wedge (b_i< b_j)\wedge (c_i<c_j)]$。

发现是三维偏序，直接用 CDQ 分治就可以求解。

**对于第 $3$ 种情况，$\lvert S\rvert=3$。**

继续使用容斥，显然总方案为 $n\choose 3$，还是考虑怎么计算不合法方案。

不合法的方案就是一个位置取超过 $2$ 个三元组中的元素，考虑分别考虑 $AB,AC,BC$。

确定了对象之后直接二位偏序处理，但是需要把多减的三个元素选都是一个位置的情况加回来。

[Submission #58377417 - Snuke's Birthday Contest](https://atcoder.jp/contests/snuke21/submissions/58377417)

---

## 作者：Zaunese (赞：2)

抛开数点做法。考虑最根本的目的：可以选 $2^n$ 个子集，然后对于三元组相同的方案只留一个。

规定：选的个数越少的越“本原”，越不应该被去除。

容易证明只要选最多 $3$ 个。证明：由于给定的是排列，最多就只有 $3$ 个下标能分别取一个最大值，其他的再选都是多余的。

接下来，任务是，从 $N+\binom N2+\binom N3$ 中扣除掉重复方案。

选一个的，由上定义，一定不重。

选两个的只能跟选一个的重了，形态一定是，选了 $i$ 和 $j$，$a_i<a_j$，$b_i<b_j$，$c_i<c_j$，与只选 $j$ 的方案重复。三维编序即可。

选三个的，若是跟选两个的重了，⼀定有⼀个下标取到了 $2$ 个最大值；若是跟选一个的重了，就是取了 $3$ 个最大值。

若是跟选两个的重了，枚举这个下标 $p$，若 $a,b$ 取了最大值，那么另外 $2$ 个下标 $i,j$ 就需要满足 $a_i<a_p$，$a_j<a_p$，$b_i<b_p$，$b_j<b_p$。（对 $b,c$ 和 $a,c$ 同理。）直接二维偏序。

需要注意的是，如果 $i,j$ 在 $a,b,c$ 都被 $p$ 偏序的话会被减掉三次，这是跟选一个的重了，于是应该补回来两次。这里直接用上刚才三维偏序算的答案。

时间复杂度在三维偏序的 $O(n\log^2 n)$。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

#define fi first
#define se second
#define mkp std::make_pair
using ll=long long;

const int NV=1e5;
ll C3(ll n){
    return n*(n-1)*(n-2)/6;
}ll C2(ll n){
    return n*(n-1)/2;
}

int N;

namespace bit{
    int tr[NV+5];
    void add(int i,int z){
        for(;i<=N;i+=i&-i) tr[i]+=z;
    }int que(int i){
        int ans=0;
        for(;i;i-=i&-i) ans+=tr[i];
        return ans;
    }
}

namespace xm{
    ll sumabc[NV+5],sumab[NV+5],sumbc[NV+5],sumac[NV+5];
    int a[NV+5],b[NV+5],c[NV+5],p[NV+5];
    void cdq(int l,int r){
        if(l==r) return;
        int mid=l+r>>1;
        cdq(l,mid);
        cdq(mid+1,r);
        int i=mid+1,j=l;
        for(;i<=r;++i){
            for(;j<=mid&&b[p[j]]<b[p[i]];++j)
                bit::add(c[p[j]],1);
            sumabc[p[i]]+=bit::que(c[p[i]]);
        }
        for(--j;j>=l;--j) bit::add(c[p[j]],-1);
        std::inplace_merge(p+l,p+mid+1,p+r+1,[&](int x,int y){
                return b[x]<b[y];});
    }void _(){
        scanf("%d",&N);
        for(int i=1;i<=N;++i) scanf("%d%d%d",a+i,b+i,c+i);

        for(int i=1;i<=N;++i) p[i]=i;
        std::sort(p+1,p+N+1,[&](int x,int y){
                return a[x]<a[y];});

        memset(bit::tr,0,sizeof bit::tr);
        memset(sumabc,0,sizeof sumabc);
        cdq(1,N);
        for(int i=1;i<=N;++i){
            sumab[p[i]]=bit::que(a[p[i]]);
            bit::add(a[p[i]],1);
        }
        memset(bit::tr+1,0,sizeof*bit::tr*N);
        for(int i=1;i<=N;++i){
            sumbc[p[i]]=bit::que(c[p[i]]);
            bit::add(c[p[i]],1);
        }
        memset(bit::tr+1,0,sizeof*bit::tr*N);
        std::sort(p+1,p+N+1,[&](int x,int y){
                return a[x]<a[y];});
        for(int i=1;i<=N;++i){
            sumac[p[i]]=bit::que(c[p[i]]);
            bit::add(c[p[i]],1);
        }
        ll ans=N+C2(N)+C3(N);
        for(int i=1;i<=N;++i)
            ans=ans-sumabc[i]-C2(sumab[i])-C2(sumbc[i])-C2(sumac[i])
                +2*C2(sumabc[i]);
        printf("%lld\n",ans);
    }
}

int main(){
    int t;
    //freopen("max.in","r",stdin);
    //freopen("max.out","w",stdout);
    t=1;
    while(t--) xm::_();
    return 0;
}
```

---

## 作者：鲤鱼江 (赞：1)

是紫题的样子，不知道为啥没有场切。

首先发现一个性质：每个点都是一个三元组，而最后求的是每个元素的 $\max$，这就说明最多只会选 $3$ 个数，否则没有意义。

所以分三类讨论：

## 选 $1$ 个

此时不会有重复，为 $n$。

## 选 $2$ 个

不考虑重复时，方案为 ${n\choose 2}$。

此时，若选的 $i$ 和 $j$ 满足：其中一个将另外一个三维偏序，则与只选一个数重复，故减去。

三维偏序采用 CDQ 分治进行，$O(n\log^2n)$。

## 选 $3$ 个

不考虑重复时，为 ${n\choose 3}$。

此时，不合法分两种情况：

1.有一个数占据了两个最大值。

2.一个数占据三个最大值。

不难发现第一种可以枚举具体是哪两维被占据了，将贡献减去。

此时第二种情况被第一种情况包含，且被算了 $3$ 遍，所以要加回来 $2$ 倍的情况 $2$ 的方案数，此时可以用之前处理出来的三维偏序算。

总时间：做了三次二维偏序和一次三维偏序，$O(n\log^2 n)$。

很好写的代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+10;
struct node{int x,y,z,id;}a[N];
int T,n,d[N],A[N],B[N],C[N];ll ans;

bool cmpa(node x,node t){return x.x<t.x;}
bool cmpb(node x,node t){return x.y<t.y;}

struct TreeArray{
	int tr[N];
	inline int lowbit(const int &x){return x&(-x);}
	inline void add(int i,const int x){for(;i<=n;i+=lowbit(i)) tr[i]+=x;}
	inline int ask(int i){int res=0;for(;i;i-=lowbit(i)) res+=tr[i];return res;}
}t;

void CDQ(int l,int r){
	if(l==r) return ;
	int mid=(l+r)>>1;CDQ(l,mid);CDQ(mid+1,r);sort(a+l,a+1+r,cmpb);
	for(int i=l;i<=r;++i) (a[i].id<=mid)?(t.add(a[i].z,1),0):(d[a[i].id]+=t.ask(a[i].z));
	for(int i=l;i<=r;++i) if(a[i].id<=mid) t.add(a[i].z,-1);
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i].x>>a[i].y>>a[i].z;
	sort(a+1,a+1+n,cmpa);for(int i=1;i<=n;++i) a[i].id=i;
	CDQ(1,n);sort(a+1,a+1+n,cmpa);
	for(int i=1;i<=n;++i){A[i]=t.ask(a[i].y);t.add(a[i].y,1);}
	for(int i=1;i<=n;++i) t.tr[i]=0;
	for(int i=1;i<=n;++i){B[i]=t.ask(a[i].z);t.add(a[i].z,1);}
	for(int i=1;i<=n;++i) t.tr[i]=0;
	sort(a+1,a+1+n,cmpb);
	for(int i=1;i<=n;++i){C[a[i].id]=t.ask(a[i].z);t.add(a[i].z,1);}
	sort(a+1,a+1+n,cmpa);
	ans+=n+1ll*n*(n-1)/2+1ll*n*(n-1)*(n-2)/6;
	for(int i=1;i<=n;++i) ans-=d[i]+1ll*A[i]*(A[i]-1)/2+1ll*B[i]*(B[i]-1)/2+1ll*C[i]*(C[i]-1)/2-1ll*d[i]*(d[i]-1);
	cout<<ans<<endl;
	return 0;
}
/*
	绘梨衣保佑！！！
*/
```

---

## 作者：Deyu (赞：1)

对于所有子集，其中 $a,b,c$ 的最大值有三种情况：全部出自同一个三元组、出自两个不同的三元组以及出自三个不同的三元组。因此我们可以分类讨论三种情况：

### 全部出自同一个三元组
显然有 $n$ 种方案。

### 出自两个不同的三元组
一共有 $\dfrac{n(n-1)}{2}$ 种方案。

设这两个三元组分别是 $i,j$ ，那么不合法的方案满足 $a_i<a_j\land b_i<b_j\land c_i<c_j$ 。可以用 cdq 分治处理。

### 出自三个不同的三元组
一共有 $\dfrac{n(n-1)(n-2)}{6}$ 种方案。

不合法的方案应当满足其中一个三元组同时包含两个或三个值的最大值。

例如，某一个三元组 $i$ 中 $a,b$ 都是最大值，那么记 $f(a,b)$ 为与它配对后是不合法方案的三元组数。这些三元组满足 $a_i>a_j\land b_i>b_j$ ，因此可以用二位偏序计算出 $f(a,b)$ 。

从 $f(a,b)$ 中选出两个不同的方案的方案数 $g(a,b)=\dfrac{f^2(a,b)-f(a,b)}{2}$ 。

此外还有 $(b,c),(a,c),(a,b,c)$ 为最大值的情况。运用容斥原理可得不合法方案数为 $g(a,b)+g(b,c)+g(a,c)-2\times g(a,b,c)$ 。其中 $g(a,b,c)$ 即为三维偏序的计算结果。

```
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define int long long
int n,c[N],f[N];
void add(int x,int y){
	for(;x<=n;x+=(x&(-x))){
		c[x]+=y;
	}
}
int ask(int x){
	int ans=0;
	for(;x;x-=(x&(-x))){
		ans+=c[x];
	}return ans;
}
struct node{
	int a,b,c,id;
}e[N];
bool cmpa(node x,node y){
	return x.a<y.a;
}
bool cmpb(node x,node y){
	return x.b<y.b;
}
void cdq(int l,int r){//cdq分治计算三维偏序 
	if(l>=r) return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	int i=l,j=mid+1;
	while(i<=mid&&j<=r){
		if(e[i].b<e[j].b){
			add(e[i].c,1);
			i++;
		}else{
			f[e[j].id]+=ask(e[j].c);
			j++;
		}
	}
	while(j<=r){
		f[e[j].id]+=ask(e[j].c);j++;
	}
	while(i>l){
		i--;add(e[i].c,-1);
	}
	sort(e+l,e+r+1,cmpb);
}
void clear(){
	for(int i=1;i<=n;i++) c[i]=0;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	for(int i=1;i<=n;i++) f[i]=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>e[i].a>>e[i].b>>e[i].c;
		e[i].id=i;
	}
	clear();
	sort(e+1,e+n+1,cmpa);
	cdq(1,n);
	int cut=0; 
	clear();
	sort(e+1,e+n+1,cmpa);
	for(int i=1;i<=n;i++){
		int tmp=ask(e[i].b);
		cut+=tmp*(tmp-1)/2;//计算a,b同为最大时的二维偏序 
		add(e[i].b,1);
	}
	clear();
	sort(e+1,e+n+1,cmpa);
	for(int i=1;i<=n;i++){
		int tmp=ask(e[i].c);
		cut+=tmp*(tmp-1)/2;//计算a,c同为最大时的二维偏序 
		add(e[i].c,1);
	}
	clear();
	sort(e+1,e+n+1,cmpb);
	for(int i=1;i<=n;i++){
		int tmp=ask(e[i].c);
		cut+=tmp*(tmp-1)/2;//计算b,c同为最大时的二维偏序 
		add(e[i].c,1);
	}
	for(int i=1;i<=n;i++){
		cut+=f[i];
	}
	int ans=n+n*(n-1)/2+n*(n-1)*(n-2)/6-cut;
	for(int i=1;i<=n;i++){
		ans+=f[i]*(f[i]-1);
	}
	//容斥原理统计答案 
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：Wu_Qi_Tengteng (赞：0)

考场 70point。

可以发现总共可能对答案有贡献的就三种选法，选一个、选两个、选三个。

超过三个所选的方案就一定与之前重复了。

所以我们对他们分开计算贡献，选一个的答案就是 $n$。

选两个的答案就是 $\binom{n}{2}$。但是发现，如果一个数被另一个数三维偏序，他就会与第一个重复，否则一定不会重复（因为是排列）。这个可以用 [CDQ分治](https://oi-wiki.org/misc/cdq-divide/) 求出。

接着是选三个。原本的答案是 $\binom{n}{3}$。这个时候算重的，肯定就是其中一个数的下标出现在最大值中的个数 $\ge 2$ 次。

然后我们分类讨论一下 ab 类，ac 类和 bc 类。

所谓 ab 类就是对于一个 $p$，去找  $a_i<a_p,b_i<b_p$ 的个数。假设数量为 $cnt_p$，那么关于 $p$ 的 ab 类型的算重的个数就是 $\binom{cnt_p}{2}$。ac 类和 bc 类同理。这个用二位偏序就可以了。

但是需要注意的是，如果 $i$ 被 $p$ 三位偏序，他就会被减掉 $3$ 次。所以我们还要保留统计选两个时的答案然后给加上。（这个就类似于容斥。）

时间复杂度 $\mathcal{O}(n\log^2n)$。瓶颈在于 CDQ。

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
const int N=2e5+5;
int C(int n,int m){
	if(n<0||m<0||n<m)return 0;
	int res=1;
	for(int i=n-m+1;i<=n;i++)res*=i;
	for(int i=1;i<=m;i++)res/=i;
	return res;
}
int T,n;
struct node{
	int a,b,c;
	int abc,ab,ac,bc;
}cz[N];
struct Ta{
	int s[N];
	void add(int x,int v){for(;x<=n;x+=(x&(-x)))s[x]+=v;}
	int sum(int x){int res=0;for(;x;x-=(x&(-x)))res+=s[x];return res;}
}ta;
void solve1(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1,j=l;
	solve1(l,mid);solve1(mid+1,r);
	sort(cz+l,cz+mid+1,[&](node x,node y){return x.b<y.b;});
	sort(cz+mid+1,cz+r+1,[&](node x,node y){return x.b<y.b;});
	for(int i=mid+1;i<=r;i++){
		while(cz[j].b<cz[i].b&&j<=mid)ta.add(cz[j].c,1),j++;
		cz[i].abc+=ta.sum(cz[i].c);
	}
	while(j>l)ta.add(cz[--j].c,-1);
}
void solve(){
	n=read();
	for(int i=1;i<=n;i++){
		cz[i].a=read(),cz[i].b=read(),cz[i].c=read();
		cz[i].abc=cz[i].ab=cz[i].bc=cz[i].ac=0;
	}
	int ans=n+C(n,2)+C(n,3);
	sort(cz+1,cz+n+1,[](node x,node y){return x.a<y.a;});
	solve1(1,n);

	sort(cz+1,cz+n+1,[](node x,node y){return x.a<y.a;});
	for(int i=1;i<=n;i++)cz[i].ab=ta.sum(cz[i].b),ta.add(cz[i].b,1);//ab
	for(int i=1;i<=n;i++)ta.add(cz[i].b,-1);
	
	for(int i=1;i<=n;i++)cz[i].ac=ta.sum(cz[i].c),ta.add(cz[i].c,1);//ac
	for(int i=1;i<=n;i++)ta.add(cz[i].c,-1);

	sort(cz+1,cz+n+1,[](node x,node y){return x.b<y.b;});//bc
	for(int i=1;i<=n;i++)cz[i].bc=ta.sum(cz[i].c),ta.add(cz[i].c,1);
	for(int i=1;i<=n;i++)ta.add(cz[i].c,-1);

	for(int i=1;i<=n;i++)ans+=-cz[i].abc-C(cz[i].ab,2)-C(cz[i].ac,2)-C(cz[i].bc,2)+2*C(cz[i].abc,2);
	printf("%lld\n",ans);
}
signed main(){
	T=read();
	while(T--)solve();
	return 0;
} 
```

---

