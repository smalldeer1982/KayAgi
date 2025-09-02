# Cow Tennis Tournament

## 题目描述

Farmer John is hosting a tennis tournament with his $ n $ cows. Each cow has a skill level $ s_{i} $ , and no two cows having the same skill level. Every cow plays every other cow exactly once in the tournament, and each cow beats every cow with skill level lower than its own.

However, Farmer John thinks the tournament will be demoralizing for the weakest cows who lose most or all of their matches, so he wants to flip some of the results. In particular, at $ k $ different instances, he will take two integers $ a_{i},b_{i} $ $ (a_{i}<b_{i}) $ and flip all the results between cows with skill level between $ a_{i} $ and $ b_{i} $ inclusive. That is, for any pair $ x,y $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283E/7acc269d103239529ceb47c1b525554954b93d55.png) he will change the result of the match on the final scoreboard (so if $ x $ won the match, the scoreboard will now display that $ y $ won the match, and vice versa). It is possible that Farmer John will change the result of a match multiple times. It is not guaranteed that $ a_{i} $ and $ b_{i} $ are equal to some cow's skill level.

Farmer John wants to determine how balanced he made the tournament results look. In particular, he wants to count the number of triples of cows $ (p,q,r) $ for which the final leaderboard shows that cow $ p $ beats cow $ q $ , cow $ q $ beats cow $ r $ , and cow $ r $ beats cow $ p $ . Help him determine this number.

Note that two triples are considered different if they do not contain the same set of cows (i.e. if there is a cow in one triple that is not in the other).

## 说明/提示

In the first sample, cow 3 > cow 1, cow 3 > cow 2, and cow 2 > cow 1. However, the results between cows 1 and 2 and cows 2 and 3 are flipped, so now FJ's results show that cow 1 > cow 2, cow 2 > cow 3, and cow 3 > cow 1, so cows 1, 2, and 3 form a balanced triple.

## 样例 #1

### 输入

```
3 2
1 2 3
1 2
2 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 3
5 9 4 1 7
1 7
2 8
3 9
```

### 输出

```
3
```

# 题解

## 作者：李至擎 (赞：8)

正难则反，考虑求不合法的三元组的数量。

对于一个不合法的三元组，可以发现条件等价于三元组中有一个点出度为 2。记 $m$ 次操作后每个点出度为 $d_i$，答案就是 $\dbinom{n}{3}-\sum\limits_{i=1}^n\dbinom{d_i}{2}$。

那么怎么统计？回忆 $\mathcal{O}(nm)$ 的做法，数组 $a_{i,j}$ 表示 $i,j$ 间边的方向。假设当次修改影响的区间是 $[l,r]$，那么这个修改就是 $\forall i,j\in[l,r]$，$a_{i,j}\gets a_{i,j}\oplus 1$。显然可以对 $j$ 这一维差分。

更进一步的，我们可以对操作应用差分的思想。更具体的，我们枚举 $i$，用线段树维护 $a$ 数组，每个修改 $[l,r]$ 就是在 $i$ 为 $l$ 或 $r+1$ 的时候区间异或一下。时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mk make_pair
#define fi first
#define se second
using namespace std;
typedef pair<int,int>pii;
const int inf=1e18; 
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
struct segtree{
	#define ls p<<1
	#define rs p<<1|1
	#define lson l,mid,ls
	#define rson mid+1,r,rs
	struct Node{
		int s[2],tag;
	}c[400005];
	void pushup(int p){
		for(int i=0;i<2;i++)c[p].s[i]=c[ls].s[i]+c[rs].s[i];
	}
	void pushdown(int l,int r,int p){
		if(!c[p].tag)return;
		int siz=r-l+1,ln=siz-(siz>>1),rn=siz>>1;
		swap(c[ls].s[0],c[ls].s[1]);
		swap(c[rs].s[0],c[rs].s[1]);
		c[ls].tag^=c[p].tag,c[rs].tag^=c[p].tag;
		c[p].tag=0;  
	}
	void build(int l,int r,int p){
		c[p].tag=0;
		if(l==r){
			c[p].s[0]=1,c[p].s[1]=0;
			return;
		}
		int mid=(l+r)>>1;
		build(lson),build(rson);
		pushup(p);
	}
	void update(int l,int r,int p,int L,int R){
		if(L<=l&&r<=R){
			swap(c[p].s[0],c[p].s[1]);
			c[p].tag^=1;
			return;
		}
		int mid=(l+r)>>1;pushdown(l,r,p);
		if(L<=mid)update(lson,L,R);
		if(R>mid)update(rson,L,R);
		pushup(p);
	}
	int query(int l,int r,int p,int L,int R,int o){
		if(L<=l&&r<=R)return c[p].s[o];
		int mid=(l+r)>>1,res=0;pushdown(l,r,p);
		if(L<=mid)res+=query(lson,L,R,o);
		if(R>mid)res+=query(rson,L,R,o);
		return res;
	}
	#undef ls
	#undef rs
	#undef lson
	#undef rson
}Tr;
int h[100005];vector<pii>v[100005];
signed main(){
	int n=read(),m=read(),ans=n*(n-1)*(n-2)/6;
	for(int i=1;i<=n;i++)h[i]=read();
	sort(h+1,h+n+1);h[0]=-inf,h[n+1]=inf;
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		if(l>h[n]||r<h[1])continue;
		l=lower_bound(h,h+n+1+1,l)-h;
		r=upper_bound(h,h+n+1+1,r)-h-1;
		v[l].push_back(mk(l,r));
		v[r+1].push_back(mk(l,r));
	}
	Tr.build(1,n,1);
	for(int i=1;i<=n;i++){
		for(auto x:v[i])Tr.update(1,n,1,x.fi,x.se);
		Tr.update(1,n,1,1,i);
		int cnt=Tr.query(1,n,1,1,n,1)-Tr.query(1,n,1,i,i,1);
		ans-=cnt*(cnt-1)/2;
		Tr.update(1,n,1,1,i);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Freopen (赞：8)

考虑数不满足条件的三元组个数。

那么三元组中必有且仅有一个出度为2

对于每个点若出度为$x$则贡献了$\frac {x(x-1)}{2}$。

从小到大扫一遍用线段树维护当前点和哪些点的连边被反转奇数次。

注意这道题的线段树是只需要区间翻转，全局求和的。

$Code$
```cpp
#include<bits/stdc++.h>
#define maxn 100005
#define LL long long
#define lc u<<1
#define rc lc|1
using namespace std;

int n,K,s[maxn];
int sm[maxn<<2],len[maxn<<2],tg[maxn<<2],cs;
vector<int>pL[maxn],pR[maxn];

void Build(int u,int l,int r){
	sm[u] = len[u] = r-l+1;
	if(l==r) return;
	int m=l+r>>1;
	Build(lc,l,m),Build(rc,m+1,r);
}
void dtp(int u){ sm[u] = len[u] - sm[u] , tg[u] ^= 1; }
void dt(int u){ if(tg[u]) dtp(lc),dtp(rc),tg[u]=0; }
void ins(int u,int l,int r,int ql,int qr){
	if(ql>r||l>qr) return;
	if(ql<=l&&r<=qr) return (void)(dtp(u));
	int m=l+r>>1;dt(u);
	ins(lc,l,m,ql,qr),ins(rc,m+1,r,ql,qr);
	sm[u] = sm[lc] + sm[rc];
}

int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++) scanf("%d",&s[i]);
	sort(s+1,s+1+n);
	for(int x,y;K--;){
		scanf("%d%d",&x,&y);
		x = lower_bound(s+1,s+1+n,x)-s;
		y = upper_bound(s+1,s+1+n,y)-s-1;
		pR[x].push_back(y);
		pL[y+1].push_back(x);
	}
	LL ans = n * (n-1ll) * (n-2ll) / 6;
	Build(1,1,n);
	for(int i=1;i<=n;i++){
		ins(1,1,n,i,i);
		for(int j=0;j<pL[i].size();j++)
			ins(1,1,n,pL[i][j],i-1),cs^=1;
		for(int j=0;j<pR[i].size();j++)
			ins(1,1,n,i,pR[i][j]),cs^=1;
		int t = sm[1]-cs;
		ans -= 1ll * t * (t-1) / 2;
	}
	printf("%lld\n",ans);
}
```


---

## 作者：wyd_forever (赞：2)

## [题目大意](https://www.luogu.org/problem/CF283E):
**给出n个正整数，由大小确定数与数之间的指向关系（大的指向小的），其中大小处在某一区间的数指向关系全部取反，问n个数之间的三元环个数**  
  
正在做学长推荐的数据结构题，莫名看到了这道数学（蒟蒻感觉对这种有数学成分的题相当无力啊），于是本蒟蒻想（kan ti jie）了好久好久，终于受到学长数学+数据结构的真传切了这题（先orz切题的大佬一波）  
# 具体思路
### first
  不管怎样，$s_i$数值范围很大，而区间取反也是从数值入手，既然如此，不管三七二十一，先把数值离散化一波，用数值大小的排名代替数值，将数值范围化为$1-n$，然后把要取反的区间两端做同样的操作。又因为反正是数值区间上的取反，干脆把所有数再排下序,这样基本操作就完成了。
### second  
  三元环不好直接求，，终于发现可以 **容斥** 一波，先求出所有方案：  
$$C_n^3$$  
    然后是不符合题意的方案数，本蒟蒻觉得分为两种：  
1.  一群牛之间互相都不可以击败对方（即一堆相等的正整数），这样的一堆数之间没有指向性。这样的话，我们可以用一个数组$cnt_x$，来记录数x出现的个数，而明显看得出来，只要在每堆这些相等的数中任意取2个，则方案不合理。综上，该情况的不合理方案为(式子里的$s_i$为离散化处理过的$s_i$数组)：  
$$\sum_{i=s_1}^{s_n}{C_{cnt_{i}}^2}$$  
2.  一头牛很勇，可以搞其他很多头牛（即一个数很nb，可以指（cha）向其他的很多个数）。而一个数x能指向的数有且仅有两种情况（~~又是两种……~~）  ：a.一个数y比x小且未被经过x的区间经过奇数次（即未被经过x的区间给d掉）；b.一个数z比x大且被经过x的区间经过奇数次（即被经过x的区间给d掉）。设第一种情况存在可能的y有$res_1$种，第二种情况存在可能的z有$res_2$种，那么显然，在$res_1$和$res_2$中取出任两个和x搭配都会导致方案不合理。设$res=res_1+res_2$，则不合理方案数为：  $C_{res}^2$。而总的不合理方案书如下：
$$\sum_{i=s_1}^{s_n}{C_{res_i}^2}$$  
  
### third  
由上总结后，求解答案的思路清晰很多了呢（没有的话别喷蒟蒻）。但看看上面我们要求的两个东西，$C_{cnt_i}^2$很好求，但那个很勇的牛的情况就有点%￥&……  
  
关键是经过x的区间要算、而没经过的不能算进去这个不好处理，莫非一个个数值暴力枚举？？这样肯定超时，怎么办呢？？  
  
本蒟蒻脑子转得慢，搞不懂怎么处理，去问学长，学长说要用扫描线，我说我不会，于是学长耐心地跟我讲了扫描线，我认真滴听，然后……没听懂。  
    
关于学长讲的扫描线，我只记得好像是先按区间左界$sort$一波，再操作一波，再按右界$sort$一波，再操作一波，然后就有答案了……  

但我不会操作啊！！  
    
算了，按照学长的左界$sort$先yy一波，灵光一闪！从$s_1$开始遍历到$s_n$，每循环到一个点$i$就把左界小于$i$的还未取反的区间给进行取反，    
  
然后把区间左界$l$压入以右界$r$为关键词的一个动态数组（$vector$）$e[r]$，然后再把$e[i-1]$里的左界一一取出，再进行一次取反（两次取反便为还原，就相当于把区间给排除了）。
  
### forth  
    
具体的区间取反使用线段树实现，这样我们就很愉快地切题了  
    
时间复杂度$O(L+klogL)$，$L$为s中不同数值的个数， 感觉应该比$O(n+klogn)$的期望要好些  
  
### fifth  
祝大家切题愉快  
  
### sixth
  
    
附上代码     
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define in read()
#define fur(i,a,b) for(int i=a;i<=b;i++)
#define xx 110000
#define int long long
#define ll long long
inline int read()
{
    int x=0,f=1;char ch=getchar();
    for(;!isalnum(ch);ch=getchar()) if(ch=='-') f=-1;
    for(;isalnum(ch);ch=getchar()) x=x*10+ch-'0';
    return x*f;
}
int s2[xx],s1[xx],s[xx],cnt[xx];    //s存战斗力，s2存排序后的，s1存s2去重后的，再将s1里的排名赋到s上
int n,c[4][xx],all=0;  //c存组合数（当然也可以在线算），all记录s2长度
struct prom{int a,b;}t[xx];  //存储区间
struct linetree{int l,r,tot,sum;bool tag;}lt[xx<<2];  //tot存储总数，sum存储被取反数
inline bool cmp(prom x,prom y){return x.a<y.a;}
vector<int>e[xx];
inline int look2(int x)  //取出s1中第一个小于等于x的数的下标，即排名
{
    int head=1,tail=all,ans=1;
    while(head<=tail)
    {
        int mid=(head+tail)>>1;
        if(s1[mid]<=x) ans=mid,head=mid+1;
        else tail=mid-1;
    }
    return ans;
}
inline int look1(int x)  //取出s1中第一个大于等于x的数
{
    int head=1,tail=all,ans=all;
    while(head<=tail)
    {
        int mid=(head+tail)>>1;
        if(s1[mid]>=x) ans=mid,tail=mid-1;
        else head=mid+1;
    }
    return ans;
}

//------------

//线段树
inline void up(int k)
{
    int q=k<<1;
    lt[k].sum=lt[q].sum+lt[q+1].sum;
    lt[k].tot=lt[q].tot+lt[q+1].tot;
}
inline void down(int k)
{
    if(lt[k].tag)
    {
        int q=k<<1;
        lt[q].sum=lt[q].tot-lt[q].sum;
        lt[q+1].sum=lt[q+1].tot-lt[q+1].sum;
        lt[q].tag^=1;
        lt[q+1].tag^=1;
        lt[k].tag^=1;
    }
}
inline void build(int k,int i,int j)
{
    lt[k].l=i;
    lt[k].r=j;
    if(i==j)
    {
        lt[k].tot=cnt[i];
        return;
    }
    int q=k<<1,mid=(i+j)>>1;
    build(q,i,mid);
    build(q+1,mid+1,j);
    up(k);
}
inline void change(int k,int i,int j)
{
    if(i<=lt[k].l&&j>=lt[k].r)
    {
        lt[k].sum=lt[k].tot-lt[k].sum;
        lt[k].tag^=1;
        return;
    }
    down(k);
    int q=k<<1,mid=lt[q].r;
    if(i<=mid) change(q,i,j);
    if(j>mid) change(q+1,i,j);
    up(k);
}
inline int askus(int k,int i,int j) //访问区间中没有被取反的数的个数
{
	if(i>j) return 0;
    if(i<=lt[k].l&&j>=lt[k].r) return lt[k].tot-lt[k].sum;
    down(k);
    int q=k<<1,mid=lt[q].r,res=0;
    if(i<=mid) res+=askus(q,i,j);
    if(j>mid) res+=askus(q+1,i,j);
    return res;
}
inline int askrs(int k,int i,int j) //访问区间中被取反的数的个数
{
	if(i>j) return 0;
    if(i<=lt[k].l&&j>=lt[k].r) return lt[k].sum;
    down(k);
    int q=k<<1,mid=lt[q].r,res=0;
    if(i<=mid) res+=askrs(q,i,j);
    if(j>mid) res+=askrs(q+1,i,j);
    return res;
}
//线段树

//------------

signed main()
{
    n=in;
    fur(i,1,n)
    {
        c[0][i]=1;c[1][i]=i;
        fur(j,2,min(i,3ll)) c[j][i]=c[j-1][i-1]+c[j][i-1];
    }
    int k=in;
    fur(i,1,n) s2[i]=s1[i]=s[i]=in;
    sort(s2+1,s2+n+1);
    fur(i,1,n)
    {
        while(s2[i]==s2[i+1]) i++;
        s1[++all]=s2[i];
    }
    fur(i,1,n) s[i]=look1(s[i]),cnt[s[i]]++;
    sort(s+1,s+n+1);
    build(1,1,s[n]);
    fur(i,1,k) t[i].a=in,t[i].b=in;
    fur(i,1,k) t[i].a=look1(t[i].a),t[i].b=look2(t[i].b);
    sort(t+1,t+k+1,cmp);
    int ans=c[3][n],tnt=1;
    fur(i,1,s[n])
    {
        while(t[tnt].a<=i&&tnt<=k)  //先算区间左界小于等于当前i的
        {
            change(1,t[tnt].a,t[tnt].b);
            e[t[tnt].b].push_back(t[tnt].a);
            tnt++;
        }
        fur(j,0,(int)e[i-1].size()-1) change(1,e[i-1][j],i-1ll);  //再删区间右界小于当前i的
        int res=0;
        res+=askus(1,1,i-1);
        res+=askrs(1,i+1,s[n]);
        ans-=cnt[i]*c[2][res];
		ans-=c[2][cnt[i]];
	}
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：Cobalt (赞：2)

可以发现，如果三头牛无法形成一个合法的三元组，那么一定有一头牛可以打败其他两头牛。

所以，假设第i头牛可以打败 $d_i$ 头牛，那么问题可以转化成：
#### 所有的组合-不合法的组合
### $=\binom{n}{3}-\sum\limits_{i=1}^{n}{\binom{d_i}{2}}$

#### 1. 离散化，按照能力强度排序
#### 2. 对修改区间分别按照$l$和$r$分别排序

#### 3. 双指针 + 线段树处理出其他牛与它的胜负是否取反
这需要处理所有覆盖了该牛的操作

从$i$移动到$i+1$时，考虑包含了当前牛的区间如何变化。

首先，有一些旧的右端点为$S_i$的的区间不再覆盖当前牛，同时也有一些新的左端点为$S_{i-1}$的区间覆盖了它，这两个信息用两个指针分别维护。

加入和删除一个区间等同于对区间内异或一次，详见[P2574](https://www.luogu.org/problemnew/show/P2574)

#### 4. 线段树区间询问获取$d_i$
战斗力小于它的牛中，它能战胜个数的为：

$(i-1)-Sum(1,i-1)$

战斗力大于它的牛中，为：

$Sum(i+1,n)$

#### 一些细节：
- 对于操作$[l,r]$有可能$l$会小于最小的战斗力
可以特判掉或者把线段树范围开到$[0,n]$
- 答案要开 long long

### AC代码:
```cpp
#include<iostream>
#include<algorithm>
#define N 110000
using namespace std;
struct D{
    int l,r;
}a[N],b[N];
int L[N*4],R[N*4],len[N*4],tag[N*4],val[N*4],s[N];
int n,m;
long long ans;
inline void swap(int &a,int &b){
    int t=a;
    a=b;
    b=t;
}
void build(int x,int l,int r){
    len[x]=r-l+1;
    L[x]=l,R[x]=r;
    if(l>=r)
        return;
    int mid=(l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
}
void pushdown(int x){
    if(!tag[x])
        return;
    tag[x<<1]^=1;
    val[x<<1]=len[x<<1]-val[x<<1];
    tag[x<<1|1]^=1;
    val[x<<1|1]=len[x<<1|1]-val[x<<1|1];
    tag[x]=0;
}
void modify(int x,int l,int r){
    if(L[x]>=l&&R[x]<=r){
        val[x]=len[x]-val[x];
        tag[x]^=1;
        return;
    }
    pushdown(x);
    int mid=(L[x]+R[x])>>1;
    if(l<=mid)
        modify(x<<1,l,r);
    if(r>mid)
        modify(x<<1|1,l,r);
    val[x]=val[x<<1]+val[x<<1|1];
}
int query(int x,int l,int r){
    if(L[x]>=l&&R[x]<=r)
        return val[x];
    pushdown(x);
    int res=0;
    int mid=(L[x]+R[x])>>1;
    if(l<=mid)
        res+=query(x<<1,l,r);
    if(r>mid)
        res+=query(x<<1|1,l,r);
    return res;
}
bool cmp(D x,D y){
    return x.l<y.l;
}
bool cmp2(D x,D y){
    return x.r<y.r;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    ans=1LL*n*(n-1)*(n-2)/6;
    build(1,0,n);
    for(int i=1;i<=n;i++)
    	cin>>s[i];
    sort(s+1,s+n+1);
    for(int i=1;i<=m;i++){
    	int x,y;
    	cin>>x>>y;
    	x=lower_bound(s+1,s+n+1,x)-s;
    	y=upper_bound(s+1,s+n+1,y)-s-1;
    	a[i].l=b[i].l=x;
    	a[i].r=b[i].r=y;
    }
    sort(a+1,a+m+1,cmp);
    sort(b+1,b+m+1,cmp2);
    int p=0,q=0;
    for(int i=1;i<=n;i++){
        long long d=0;
        while(p<m&&a[p+1].l<=i){
            p++;
            modify(1,a[p].l,a[p].r);
        }
        while(q<m&&b[q+1].r<i){
            q++;
            modify(1,b[q].l,b[q].r);
        }
        if(i>1)
            d+=(i-1)-query(1,1,i-1);
        if(i<n)
            d+=query(1,i+1,n);
        ans-=(d*(d-1))/2;
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：daniEl_lElE (赞：1)

三元环性质：有且仅有一个点出度为 $2$。

然后就好做了，用线段树计算出每个点往前，往后的出度分别是多少，然后所有点出度中选择两个的方案的和即可。

具体地，先离散化，然后从右往左加入反转区间的开头结尾，相当于对一段后缀进行 $0,1$ 反转，然后线段树求区间和即可。

总复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int tol[100005],tor[100005];
struct sgt{
	int f[2000005],siz[2000005],tag[2000005];
	void pushdown(int i){
		if(tag[i]){
			f[i*2]=siz[i*2]-f[i*2];
			f[i*2+1]=siz[i*2+1]-f[i*2+1];
			tag[i*2]^=1;
			tag[i*2+1]^=1;
			tag[i]=0; 
		}
	}
	void build(int i,int l,int r){
		tag[i]=0;
		if(l==r){
			f[i]=0,siz[i]=1;
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=f[i*2]+f[i*2+1];
		siz[i]=siz[i*2]+siz[i*2+1];
	}
	void flip(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr){
			f[i]=siz[i]-f[i];
			tag[i]^=1;
			return ;
		}
		pushdown(i);
		if(ql<=mid) flip(i*2,l,mid,ql,qr);
		if(qr>mid) flip(i*2+1,mid+1,r,ql,qr);
		f[i]=f[i*2]+f[i*2+1];
	}
	int qry(int i,int l,int r,int ql,int qr){
		if(ql>qr) return 0;
		if(ql<=l&&r<=qr) return f[i];
		if(ql>r||qr<l) return 0;
		pushdown(i);
		return qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr);
	}
}tree;
int s[100005],l[100005],r[100005],tag1[100005],tag2[100005];
vector<int> v1[100005];
vector<int> v2[100005];
signed main(){
	int n,k; cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>s[i];
	sort(s+1,s+n+1);
//	for(int i=1;i<=n;i++) cout<<s[i]<<" ";
	for(int i=1;i<=k;i++){
		cin>>l[i]>>r[i];
		l[i]=lower_bound(s+1,s+n+1,l[i])-s;
		r[i]=lower_bound(s+1,s+n+1,r[i]+1)-s-1;
		if(l[i]>r[i]) continue;
		v1[l[i]].push_back(r[i]);
		v2[r[i]].push_back(l[i]);
//		cout<<l[i]<<" "<<r[i]<<"\n";
	}
	{
		tree.build(1,1,n);
		tree.flip(1,1,n,1,n);
		for(int i=1;i<=n;i++){
			for(auto v:v1[i]){
				tree.flip(1,1,n,i,v);
			}
			tol[i]=tree.qry(1,1,n,1,i-1);
			for(auto v:v2[i]){
				tree.flip(1,1,n,v,i);
			}
		}
	}
	{
		tree.build(1,1,n);
		for(int i=n;i>=1;i--){
			for(auto v:v2[i]){
				tree.flip(1,1,n,v,i);
			}
			tor[i]=tree.qry(1,1,n,i+1,n);
			for(auto v:v1[i]){
				tree.flip(1,1,n,i,v);
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
//		cout<<tol[i]<<" "<<tor[i]<<"\n";
		(ans+=(tol[i]+tor[i])*(tol[i]+tor[i]-1)/2);
	}
//	cout<<ans<<" ";
	cout<<n*(n-1)*(n-2)/6-ans;
	return 0;
} 
```

---

## 作者：moonbowqwq (赞：1)

[题目链接](https://codeforces.com/problemset/problem/283/E)

Thanks to hjy dalao.

## 题意简述

有 $n$ 个点，对于任意两个点 $u, v$，若满足 $u > v$，则存在一条从 $u$ 到 $v$ 的有向边。

有 $k$ 次操作，每次操作会给出两个参数 $a$ 和 $b$，满足 $a < b$，表示将所有边号在 $a, b$ 之间的点之间的边的方向变为原来方向的反方向。

在所有操作结束以后，请你求出图中三元环的个数。

## 解题思路

直接统计三元环是困难的，不妨考虑一下不合法的情况。可以发现所有非三元环都形如以下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/o31unkwn.png)

那么我们只需要在类似于上图 $1$ 处统计不合法的答案数量，再用 $C_{n}^{3}$ 减去不合法的答案数量即可。

那么问题就来到了如何统计每个点的出度。尝试用邻接矩阵存图，假设 $n = 3$，初始情况如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/5mhw3ap0.png)

而当我们进行一个 $a = 2, b = 3$ 的操作后，就变成了这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/adblcxjn.png)

可以发现，每一次操作，都相当于对从 $(a, a)$ 到 $(b, b)$ 这一个正方形内的元素进行一次异或 $1$ 的操作。所以，我们可以用类似于差分的方法实现区间异或，然后用扫描线依次统计每个点的出度即可，时间复杂度 $O((n + k) \log n)$。

## 代码实现

```
#include<bits/stdc++.h>

using namespace std;

namespace my_code{
  #define ll long long
  const int N = 1e5;
  
  int n, k, s[N + 5];
  vector<pair<int, int>> have[N + 5];

  struct segment_tree{
    struct tree_node{
      int sum, len;
      bool lz;
    }tn[N + 5 << 2];
    
    void update(int x){
      tn[x].sum = tn[x].len - tn[x].sum;
      tn[x].lz ^= 1;
      return;
    }

    void push_down(int x){
      if(tn[x].lz){
        update(x << 1);
        update(x << 1 | 1);
        tn[x].lz = false;
      }
      return;
    }

    void push_up(int x){
      tn[x].sum = tn[x << 1].sum + tn[x << 1 | 1].sum;
      return;
    }
    
    void build(int x = 1, int l = 1, int r = n){
      tn[x].sum = 0;
      tn[x].len = r - l + 1;
      tn[x].lz = false;
      if(l == r)
        return;
      build(x << 1, l, l + r >> 1);
      build(x << 1 | 1, l + r + 2 >> 1, r);
      return;
    }

    void reversal(int tl, int tr, int x = 1, int l = 1, int r = n){
      if(r < tl || l > tr)
        return;
      if(l >= tl && r <= tr){
        update(x);
        return;
      }
      push_down(x);
      reversal(tl, tr, x << 1, l, l + r >> 1);
      reversal(tl, tr, x << 1 | 1, l + r + 2 >> 1 ,r);
      push_up(x);
      return;
    }

    int qsum(int tl, int tr, int x = 1, int l = 1, int r = n){
      if(r < tl || l > tr)
        return 0;
      if(l >= tl && r <= tr)
        return tn[x].sum;
      push_down(x);
      return qsum(tl, tr, x << 1, l, l + r >> 1) + qsum(tl, tr, x << 1 | 1, l + r + 2 >> 1 ,r);
    }
  }seg;

  void my_main(){
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i)
      scanf("%d", &s[i]);

    sort(s + 1, s + 1 + n);

    for(int i = 1, a, b; i <= k; ++i){
      scanf("%d%d", &a, &b);
      a = lower_bound(s + 1, s + 1 + n, a) - s;
      b = upper_bound(s + 1, s + 1 + n, b) - s - 1;
      if(a > b)
        continue;
      have[a].push_back(make_pair(a, b));
      have[b + 1].push_back(make_pair(a, b));
    }
    seg.build();

    ll ans = (ll)n * (n - 1) * (n - 2) / 6;
    for(int i = 1; i <= n; ++i){
      for(auto rv : have[i])
        seg.reversal(rv.first, rv.second);
      int num = seg.qsum(1, n) - seg.qsum(i, i);
      ans -= (ll)num * (num - 1) >> 1;
      seg.reversal(i, i);
    }
    printf("%lld", ans);
    return;
  }
}

int main(){
  my_code::my_main();
  fflush(stdout);
  return 0;
}
```

---

## 作者：Erotate (赞：0)

对于一个不合法的三元环，它有且只有一个点的出度为 $2$。设节点 $i$ 的出度为 $d_i$，那么根据容斥原理，答案就是

$$\binom{3}{n} - \sum_{i = 1}^{n} \binom{2}{d_i}$$

然后我们考虑怎么来维护翻转操作。如果用邻接矩阵存图的话，对一段区间 $[a, b]$，翻转一次就相当于对 $(a,a)$ 到 $(b,b)$ 的矩阵与 $1$ 进行了一次区间异或。那么我们就可以用线段树来维护这个异或操作，先统计前缀和，然后差分来做即可。


```cpp
const int N = 1e5 + 5;
int n, k, a[N];
vector<PII > G[N];
struct Segment{
	#define ls k << 1
	#define rs k << 1 | 1
	struct Node{
		int sum, len, tag;
	}tr[N << 2];
	void push_down(int k){
		if(!tr[k].tag) return ;
		tr[ls].sum = tr[ls].len - tr[ls].sum;
		tr[ls].tag ^= 1;
		tr[rs].sum = tr[rs].len - tr[rs].sum;
		tr[rs].tag ^= 1;
		tr[k].tag = 0;
	}
	void push_up(int k){
		tr[k].sum = tr[ls].sum + tr[rs].sum;
	}
	void build(int k, int l, int r){
		tr[k] = {0, r - l + 1, 0};
		if(l == r) return ;
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
	}
	void rev(int k, int l, int r, int L, int R){
		if(L <= l && r <= R){
			tr[k].sum = tr[k].len - tr[k].sum;
			tr[k].tag ^= 1;
			return ; 
		}
		push_down(k);
		int mid = l + r >> 1;
		if(L <= mid) rev(ls, l, mid, L, R);
		if(R > mid) rev(rs, mid + 1, r, L, R);
		push_up(k);
	}
	int qry(int k, int l, int r, int L, int R){
		if(L <= l && r <= R) return tr[k].sum;
		push_down(k);
		int mid = l + r >> 1, res = 0;
		if(L <= mid) res += qry(ls, l, mid, L, R);
		if(R > mid) res += qry(rs, mid + 1, r, L, R);
		return res;
	}
}T;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> k;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1);
	for(int i = 1, l, r; i <= k; ++i){
		cin >> l >> r;
		l = lower_bound(a + 1, a + n + 1, l) - a, r = upper_bound(a + 1, a + n + 1, r) - a - 1;
		if(l > r) continue;
		G[l].push_back(make_pair(l, r)), G[r + 1].push_back(make_pair(l, r));
	}
	T.build(1, 1, n);
	LL ans = 1ll * n * (n - 1) * (n - 2) / 6;
	for(int i = 1; i <= n; ++i){
		for(auto v : G[i]) T.rev(1, 1, n, v.fi, v.se);
		int t = T.qry(1, 1, n, 1, n) - T.qry(1, 1, n, i, i);
		ans -= 1ll * t * (t - 1) / 2;
		T.rev(1, 1, n, i, i);
	}
	cout << ans << endl;
    return 0;
}
```

---

## 作者：Saka_Noa (赞：0)

题目要我们求三元组的数量。根据经验，我们处理一下。发现不合法的三元组只有一种情况：即一个三元组中，一个点的出度为 $2$。记 $d_i$ 为一个点的出度，所以总的答案是 $\binom{3}{n} - \sum \binom{2}{d_i}$。问题转化为如何快速求出每个点的 $d_i$。观察发现，对于一个点，只有经过它的区间才会对它的 $d_i$ 产生影响，显然我们可以利用差分的思想，在每个操作的两个端点进行修改。具体的，把一个 $l \sim r$ 的修改在 $l$ 和 $r + 1$ 分别进行一次区间翻转，我们从小到大按枚举每个点，统计答案。  
再说一个代码实现的细节，我们记一个标记 $cs$ 表示当前这个点以前区间翻转操作次数，当 $cs$ 为奇数次时，说明当前这个点被覆盖了，否则覆盖相互抵消或者没被覆盖。

```cpp
#include<bits/stdc++.h>

using namespace std;
#define lc k << 1
#define rc lc | 1
#define lcon lc, l, mid
#define rcon rc, mid + 1, r
#define Mid int mid = l + r >> 1

typedef long long ll;
const int N = 1e5 + 500;

int n, k;
int sum[N << 2], tag[N << 2], len[N << 2], cs;

void dk(int k) {tag[k] ^= 1, sum[k] = len[k] - sum[k];} 
void pd(int k) {if(tag[k]) dk(lc), dk(rc), tag[k] = 0;} 
void build(int k ,int l, int r) {
	len[k] = r - l + 1; if(l == r) return;
	Mid; build(lcon), build(rcon);
}
void modify(int k, int l, int r, int x, int y) { 
	if(y < l || x > r) return ;if(x <= l && r <= y) return (void)dk(k);
	pd(k); Mid; if(x <= mid) modify(lcon, x, y);
	if(y > mid) modify(rcon, x, y); sum[k] = sum[lc] + sum[rc];
}

int s[N];
vector<int> L[N];
vector<int> R[N];
int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", s + i); 
	sort(s + 1, s + n + 1);
	while(k--) {
		int x, y; scanf("%d %d", &x, &y);
		x = lower_bound(s + 1, s + n + 1, x) - s;
		y = upper_bound(s + 1, s + n + 1, y) - s - 1;
		R[x].push_back(y), L[y + 1].push_back(x);
	} 
	build(1, 1, n);
	ll ans = (ll) n * (n - 1) * (n - 2) / 6; 
	for(int i = 1;i <= n; ++i) {
		for(auto P : L[i]) modify(1, 1, n, P, i - 1), cs ^= 1;
		for(auto P : R[i]) modify(1, 1, n, i, P), cs ^= 1;
		int t = sum[1] - cs; 
		ans -= (ll) t * (t - 1) / 2;
		modify(1, 1, n, i, i);
	}
	printf("%lld" ,ans);
	return 0;
}
```

---

## 作者：Aiopr_2378 (赞：0)

Solution of CF283E Cow Tennis Tournament

## 一、题目大意

有 $n$ 个点，每个点有一个点权 $s_i$，一开始，每个点向比其点权小的点连边。接下来 $k$ 个操作，每个操作给定 $l,r$，将 $s_x,s_y\in [l,r]$ 的点对 $(x,y)$ 的边翻转方向。

问最后有多少对三元组 $(x,y,z)$ 满足 $x\rightarrow y,y\rightarrow z,z\rightarrow x$。（箭头表示连边方向）两个三元组不同当且仅当有一个点在其中一个三元组中而不在另一个三元组中。

## 二、解题思路

考虑到正面思考好像很难，正难则反，考虑有多少组三元组不符合这个条件。

不难发现，对于不满足条件的三元组 $(x,y,z)$，其中肯定有一个点的出度（在这三个点构成的图中）为 $2$。我们就考虑能否求出每个点在最后有多少个出度，进而求出答案。

因为一段区间翻转，只会对这个区间内的点对 $(x,y)$ 产生变化，不妨按照扫描线的思路，按照点权大小排序后，对离散化的点权建立线段树，表示每个点是否对当前点 $x$ 的连边有翻转（即区间翻转操作是奇数次还是偶数次）。我们把每个操作拆分为两个：

- 左端标记在区间 $[l,r]$ 翻转；
- 右端标记在区间 $[l,r]$ 撤销翻转，即再进行一次翻转即可。

我们按照离散化的点集，按照权值从小到大扫描。再每一个点记录当前点的出度：

- 对于比当前点 $x$ 点权小的点 $y$，当前点连向这个点，当且仅当区间 $[y,x)$ 的翻转次数为偶数次；
- 对于比当前点 $x$ 点权大的点 $y$，当前点连向这个点，当且仅当区间 $(x,y]$ 的翻转次数为奇数次。

这样，我们进行区间修改，区间查询，就可以在 $O(\log n)$ 的时间内求出一个点的出度。根据组合公式，可以得到不合法的种类数为 $C_{num}^2$，其中 $num$ 为出度。

所以最后答案就是

$$
C_n^3-\sum\limits_{i=1}^nC_{num_i}^2
$$

## 三、参考代码

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define MAXN 100005
#define mid ((tree[p].l+tree[p].r)>>1)
#define ls (p<<1)
#define rs (p<<1|1)
typedef long long ll;
int n,k,s[MAXN];
ll ans;
vector<int> add[MAXN],del[MAXN];
struct node{
    int l,r,sum[2];
    bool tag;
}tree[MAXN<<2];
void update(int p){
    tree[p].sum[0]=tree[ls].sum[0]+tree[rs].sum[0];
    tree[p].sum[1]=tree[ls].sum[1]+tree[rs].sum[1];
}
void build(int l,int r,int p){
    tree[p].l=l,tree[p].r=r;
    if(l==r){
        tree[p].sum[0]=1;
        return;
    }
    build(l,mid,ls);
    build(mid+1,r,rs);
    update(p);
}
void pushdown(int p){
    if(!tree[p].tag) return;
    swap(tree[ls].sum[0],tree[ls].sum[1]);
    swap(tree[rs].sum[0],tree[rs].sum[1]);
    tree[ls].tag^=1;
    tree[rs].tag^=1;
    tree[p].tag=0;
}
void modify(int l,int r,int p){
    if(l<=tree[p].l&&r>=tree[p].r){
        swap(tree[p].sum[0],tree[p].sum[1]);
        tree[p].tag^=1;
        return;
    }
    pushdown(p);
    if(l<=mid) modify(l,r,ls);
    if(r>mid) modify(l,r,rs);
    update(p);
}
int query(int l,int r,int op,int p){
    if(l>r) return 0;
    if(l<=tree[p].l&&r>=tree[p].r) return tree[p].sum[op];
    pushdown(p);
    int sum=0;
    if(l<=mid) sum+=query(l,r,op,ls);
    if(r>mid) sum+=query(l,r,op,rs);
    return sum;
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>s[i];
    sort(s+1,s+1+n);//按照点权排序
    for(int x,y,i=1;i<=k;i++){
        cin>>x>>y;
        x=lower_bound(s+1,s+1+n,x)-s;//求出离散化后的操作范围
        y=upper_bound(s+1,s+1+n,y)-s-1;
        if(y<x) y=x;
        add[x].push_back(y);//建立类扫描线
        del[y].push_back(x);
    }
    build(1,n,1);
    for(int i=1;i<=n;i++){
        for(auto v:add[i]) modify(i,v,1);
        int cnt1=query(1,i-1,0,1);//比当前点点权小的点所带来的出度
        int cnt2=query(i+1,n,1,1);//比当前点点权大的点所带来的出度
        if(cnt1+cnt2>=2) ans+=1ll*(cnt1+cnt2)*(cnt1+cnt2-1)/2;//组合答案
        for(auto v:del[i]) modify(v,i,1);
    }
    ans=1ll*n*(n-1)*(n-2)/6-ans;
    cout<<ans;
    return 0;
}
```

---

## 作者：MatrixGroup (赞：0)

## 前言

Kevin 搬的模拟赛都是小清新思维题！就是我被创死了！非常好题目，爱来自瓷器。

## 题意

给定一个 $n$ 点的竞赛图，初始边全为 $i\to j$ 当且仅当 $a_i<a_j$（$a$ 两两不同），$k$ 次操作，每次操作形如将所有 $a_i,a_j\in [l,r]$ 的边反向。求最终的图的三元环个数。

$n,k\le10^5$。

## 题解

三元环个数一看就不可维护。考虑用 $\dbinom{n}{3}$ 减去三元非环个数。考虑枚举初始点，个数即为 $\sum\limits_{i=1}^n \binom{d_i}{2}$，其中 $d_i$ 为结点 $i$ 的出度。

显然可以将 $a$ 排序。那么转化成初始形如 $i\to j(i<j)$，结点编号在一定区间内的边反向。考虑对每个结点 $i$ 分别考虑 $d_i$。

显然一开始的出度形如 $[0,0,0,\cdots,0,/,1,\cdots,1,1,1]$，其中 $/$ 表示点 $i$，不纳入计算。操作形如如果 $i\in [l,r]$ 则区间反转（指的是 $0\to1$，$1\to0$），容易用线段树维护。

考虑 $i$ 到 $i+1$ 的变化。只有那些 $i$ 不在 $i+1$ 在或 $i$ 在 $i+1$ 不在的区间和 $i,i+1$ 这两点会带来变化。前者只在端点出变化，因此总变化次数是 $O(n+k)$ 的。这样维护 $d_i$，本题可以在 $O((n+k)\log n)$ 的时间复杂度内完成。

---

## 作者：陌路的花 (赞：0)

首先根据题目可知这是一个完全图.

如果不考虑边的方向，那任取三个点都能构成一个环.

现在题目给了这些边一个方向，所以一个环不合法，当且仅当其上有一个点出度为 $2$ .

于是我们的答案就是 $\binom{n}{3}-\sum\binom{d_i}{2}$ ，这里的 $d$ 表示出度.

记 $0$ 为初始连边状态， $1$ 为反转连边状态， $p_x$ 为 $x$ 和现在这个点**当前的**连边状态 .

于是题目的操作就可以转化成区间反转区间查询了，使用线段树即可.

---

