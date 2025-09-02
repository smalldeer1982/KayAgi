# Aquarium decoration

## 题目描述

Arkady and Masha want to choose decorations for thier aquarium in Fishdom game. They have $ n $ decorations to choose from, each of them has some cost. To complete a task Arkady and Masha need to choose exactly $ m $ decorations from given, and they want to spend as little money as possible.

There is one difficulty: Masha likes some $ a $ of the given decorations, Arkady likes some $ b $ of the given decorations. Some decorations may be liked by both Arkady and Masha, or not be liked by both. The friends want to choose such decorations so that each of them likes at least $ k $ decorations among the chosen. Help Masha and Arkady find the minimum sum of money they need to spend.

## 说明/提示

In the first example the only possible variant to choose $ 3 $ decorations having all conditions satisfied is to choose decorations $ 1 $ , $ 2 $ , $ 3 $ .

In the second example friends can choose decoration $ 4 $ instead of decoration $ 3 $ , because this one is one coin cheaper.

In the third example it's not possible to choose $ 2 $ decorations in a way that both are liked by both Masha and Arkady.

## 样例 #1

### 输入

```
4 3 2
3 2 2 1
2
1 2
2
1 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 3 2
3 2 2 1
2
1 2
3
4 1 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
4 2 2
3 2 2 1
2
1 2
3
4 1 3
```

### 输出

```
-1
```

# 题解

## 作者：syk666 (赞：3)

考虑划分四个集合，记 $A$ 为仅被第一个人喜欢， $B$ 为仅被第二个人喜欢， $C$ 为同时被两个人喜欢， $D$ 为同时不被两个人喜欢。

预处理出以上四个集合，并排好序。

则考虑枚举 $C$选择的个数 $i$ ，则显然有 $A$ ，$B$ 至少需要选择 $k-i$ 个。并且显然取排序后的前 $k-i$ 个（对于 $ A $ 和 $   B$ ）。

考虑剩余的怎么取，前面我们提到是**至少**，则对于 $ k - i $后面的数字，这是我们**可能**选择的数，然后还有我们之前产生的答案还可能来自 $ D $ 。

那么现在，我们是不是就要动态的维护一下 $ A $ ，$ B $ 的后面一部分， $ D $的全部， 这些部分的前 $ x $ 小数吗？直接上**对顶堆**即可！

细节较多（

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=9e5+55;
int a[N],b[N],c[N],d[N];
long long suma[N],sumb[N],sumc[N],sumd[N];
int zz[10];
int cnt[10];
int tong[N];
int n,m,k;
long long v[N];
int A,B;
priority_queue<long long> q;
priority_queue<long long,vector<long long>,greater<long long> > p;
long long qsum=0;
long long minn=1e18;
void init(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        scanf("%lld",&v[i]);
    scanf("%d",&A);
    for(int i=1;i<=A;i++){
        int x;
        scanf("%d",&x);
        tong[x]++;
    }
    scanf("%d",&B);
    for(int i=1;i<=B;i++){
        int x;
        scanf("%d",&x);
        tong[x]+=2;
    }
//    a[++cnt[1]]=0;
//    b[++cnt[2]]=0;
//    c[++cnt[3]]=0;
//    d[++cnt[4]]=0;
    for(int i=1;i<=n;i++){
        if(tong[i]==0){
            cnt[4]++;
            d[cnt[4]]=v[i];
        }else if(tong[i]==1){
            cnt[1]++;
            a[cnt[1]]=v[i];
        }else if(tong[i]==2){
            cnt[2]++;
            b[cnt[2]]=v[i];
        }else if(tong[i]==3){
            cnt[3]++;
            c[cnt[3]]=v[i];
        }
    }
    sort(a+1,a+cnt[1]+1);
    sort(b+1,b+cnt[2]+1);
    sort(c+1,c+cnt[3]+1);
    sort(d+1,d+cnt[4]+1);
    for(int i=1;i<=cnt[1];i++)
        suma[i]=suma[i-1]+a[i];

    for(int i=1;i<=cnt[2];i++)
        sumb[i]=sumb[i-1]+b[i];

    for(int i=1;i<=cnt[3];i++)
        sumc[i]=sumc[i-1]+c[i];

    for(int i=1;i<=cnt[4];i++)
        sumd[i]=sumd[i-1]+d[i];
}
void PD(int x){
    int nd=max(0,k-x);
//    cout<<"**nd="<<nd<<endl;
    if(cnt[1]<nd||cnt[2]<nd) return ;
    int now=nd*2+x;
    int qk=m-now;
//    cout<<"qk="<<qk<<endl;
    for(int i=nd+1;i<=zz[1];i++){
        q.push(a[i]);
        qsum+=a[i];
    }
    for(int i=nd+1;i<=zz[2];i++){
        q.push(b[i]);
        qsum+=b[i];
    }
    zz[1]=nd;
    zz[2]=nd;
    while(1){
        if(!p.size()) break;
        if(!q.size()){
            q.push(p.top());
            qsum+=p.top();
            p.pop();
            continue;
        }
        long long ptop=p.top();
        long long qtop=q.top();
        if(ptop<qtop){
            p.pop();
            q.pop();
            p.push(qtop);
            q.push(ptop);
            qsum-=qtop;
            qsum+=ptop;
        }else{
            break;
        }
    }
    while(p.size()>0){
        if(!p.size()) break;
        if(q.size()>=qk) break;
        int ptop=p.top();
        p.pop();
        q.push(ptop);
        qsum+=ptop;
    }

    while(q.size()>=qk){
        if(!q.size()) break;
        if(q.size()==qk) break;
        int qtop=q.top();
        q.pop();
        p.push(qtop);
        qsum-=qtop;
    }
    if(q.size()!=qk) return ;
    long long NOW=sumc[x]+suma[nd]+sumb[nd];
    NOW+=qsum;
//    cout<<"nd="<<nd<<endl;
//    cout<<"NOW="<<NOW<<endl;
//    cout<<"qsum="<<qsum<<endl;
    minn=min(minn,NOW);
}
void doit(){
//    if(cnt[1]+cnt[3]<k||cnt[2]+cnt[3]<k){
//        cout<<-1<<endl;
//        exit(0);
//    }
    zz[1]=cnt[1];
    zz[2]=cnt[2];
    for(int i=1;i<=cnt[4];i++){
        q.push(d[i]);
        qsum+=d[i];
    }
    for(int i=0;i<=cnt[3];i++){
//        cout<<"i="<<i<<endl;
        PD(i);
    }
    if(minn==1e18) cout<<-1<<endl;
    else cout<<minn<<endl;
}
void ck(){
    cout<<"A--"<<endl;
    for(int i=1;i<=cnt[1];i++)
        cout<<a[i]<<" ";
    cout<<endl;

    cout<<"B--"<<endl;
    for(int i=1;i<=cnt[2];i++)
        cout<<b[i]<<" ";
    cout<<endl;

    cout<<"C--"<<endl;
    for(int i=1;i<=cnt[3];i++)
        cout<<c[i]<<" ";
    cout<<endl;

    cout<<"d--"<<endl;
    for(int i=1;i<=cnt[4];i++)
        cout<<d[i]<<" ";
    cout<<endl;
}
int main(){
//    freopen("b16.in","r",stdin);
//    freopen("b16.out","w",stdout);
    init();
//    ck();
    doit();
    return 0;
}
/*
10 8 5
3 6 8 5 6 14 16 8 20 17
6
2 9 5 1 8 4
6
7 6 4 9 8 2
*/

```







---

## 作者：MyukiyoMekya (赞：2)

一眼模拟费用流。

我们把 AB 都喜欢的称作 $ab$ ，只被 A 以及只被 B 喜欢的分别称作 $a$ 和 $b$ ，AB 都不喜欢的称作 $E$。

显然我们可以先贪心满足 $\ge k$ 这个限制，由于 A 和 B 都是要求 $\ge k$ 所以很好处理。

我们有两种选择：取一个 $a$ 和 $b$ ，或者取一个 $ab$，这里直接贪心取尽量小的。

然后发现取的物品个数不一定满足等于 $m$ 的限制，那么我们来调整一下。

如果物品取少了，我们可以在下列方案中贪心取最小的（每次使用方案后物品个数加 $1$）

1. 取 $1$ 个 $E$。
2. 取 $1$ 个 $a$。 
3. 取 $1$ 个 $b$。 
4. 取 $1$ 个 $ab$。
5. 用 $1$ 个 $a$ 和 $1$ 个 $b$ 换掉已经取的 $1$ 个 $ab$。

相当于我们要使得流量增加 $1$ ，且费用最小。可以通过最小费用最大流的算法过程来理解正确性。

如果物品取多了，我们可以在下列方案中贪心取最小的（每次使用方案后物品个数减 $1$）

1. 用已经取的 $1$ 个 $ab$  换掉 $1$ 个 $a$ 和 $1$ 个 $b$ 。

正确性同理。

实现起来就是对 $4$ 种物品分别开两个堆，然后按照上面的直接维护就行，时间复杂度 $\mathcal O(n\log n)$。

---

Upd：

经评论区老哥提醒，我发现好像没办法建立费用流模型（当然也可能是我太菜了建不出来）。

但是正确性还是可以保证的，大概考虑如果 $m$ 个物品的最优决策如果不是在 $m-1$ 的最优决策上进行上面的操作，那么说明 $m-1$ 的决策一定不是最优决策（大概毛估估一下应该是对的）。

如果有老哥能给出更严谨的证明请私信我 qwq。

```cpp
// This code wrote by relatorpunch
#include <bits/stdc++.h>
#define reg
#define int long long
#define ln putchar('\n')
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef std::pair<int,int> pii;
typedef std::vector<int> poly;
template <class t> inline void read(t &s){s=0;
signed f=1;char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();;s*=f;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
static int buf[50],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');}
template <class t>inline bool ckmin(t&x,t y){if(x>y){x=y;return 1;}return 0;}
const int MaxN=2e5+50;
struct PQLESS
{inline bool operator () (const int &x,const int &y) const{return y<x;}};
std::priority_queue<int,poly,PQLESS> a,b,ab,_;
std::priority_queue<int> A,B,AB,__;
int v[MaxN],x[MaxN],y[MaxN];
signed main(void)
{
	int n,m,K;read(n,m,K);
	for(int i=1;i<=n;++i)read(v[i]);
	{
		int u,v;read(u);
		while(u--)read(v),x[v]=1;
	}
	{
		int u,v;read(u);
		while(u--)read(v),y[v]=1;
	}
	for(int i=1;i<=n;++i)
		if(x[i]&&y[i])ab.push(v[i]);
		else if(x[i]&&!y[i])a.push(v[i]);
		else if(!x[i]&&y[i])b.push(v[i]);
		else _.push(v[i]);
	int love=0,cnt=0,ans=0;
	while(love<K)
	{
		int opt=0,mn=1e18;
		if(ab.size()&&ckmin(mn,ab.top()))opt=1;
		if(a.size()&&b.size()&&ckmin(mn,a.top()+b.top()))opt=2;
		if(!opt)break;
		++love,ans+=mn;
		if(opt==1)AB.push(ab.top()),ab.pop(),++cnt;
		else A.push(a.top()),B.push(b.top()),a.pop(),b.pop(),cnt+=2;
	}
	if(love!=K)return std::puts("-1"),0;
	while(cnt<m)
	{
		int opt=0,mn=1e18;
		if(_.size()&&ckmin(mn,_.top()))opt=1;
		if(a.size()&&ckmin(mn,a.top()))opt=2;
		if(b.size()&&ckmin(mn,b.top()))opt=3;
		if(AB.size()&&a.size()&&b.size()&&ckmin(mn,-AB.top()+a.top()+b.top()))
			opt=4;
		if(ab.size()&&ckmin(mn,ab.top()))opt=5;
		if(!opt)break;
		++cnt,ans+=mn;
		if(opt==1)__.push(_.top()),_.pop();
		else if(opt==2)A.push(a.top()),a.pop();
		else if(opt==3)B.push(b.top()),b.pop();
		else if(opt==4)ab.push(AB.top()),A.push(a.top()),B.push(b.top()),
			AB.pop(),a.pop(),b.pop();
		else AB.push(ab.top()),ab.pop();
	}
	while(cnt>m)
	{
		int opt=0,mn=1e18;
		if(__.size()&&ckmin(mn,-__.top()))opt=1;
		if(ab.size()&&A.size()&&B.size()&&ckmin(mn,ab.top()-A.top()-B.top()))
			opt=2;
		if(!opt)break;
		--cnt,ans+=mn;
		if(opt==1)_.push(__.top()),__.pop();
		else AB.push(ab.top()),a.push(A.top()),b.push(B.top()),
			ab.pop(),A.pop(),B.pop();
	}
	if(cnt!=m)return std::puts("-1"),0;
	write(ans),ln;
	return 0;
}
```



---

## 作者：Great_Influence (赞：2)

首先，可以先将物品分成四组:A喜欢的，B喜欢的，都喜欢的，都不喜欢的。设这些集合分别为$A,B,C,D$。

然后，我们枚举$C$集合选择多少个，并贪心地从其他集合中尽量选择权值小的点。

直接做是$O(n^2)$的。但是很显然得可以猜到，相邻之间的答案可以互相快速转移。因此，我们开三个队列，分别存储$A,B,D$三个集合。可以知道，当集合之间分别排完序后，选择的点一定是最靠前的几个物品。因此，我们使用$3$个指针来指示各个队列选择到了哪里。这样做就是$O(n)$的(然而前面有排序，时间复杂度为$O(n\log n)$)。

代码实现较简单，但是细节繁多，可以锻炼代码精度。

```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define pb push_back
#define mp make_pair
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
    const uint32 Buffsize=1<<15,Output=1<<23;
    static char Ch[Buffsize],*S=Ch,*T=Ch;
    inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
    static char Out[Output],*nowps=Out;
    
    inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

    template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

inline void file()
{
#ifndef ONLINE_JUDGE
	FILE*ASD=freopen("b.in","r",stdin);
	FILE*SACS=freopen("b.out","w",stdout);
#endif
}

const int MAXN=2e5+7;

static int n,m,k,w[MAXN];

static int A,B,C,D,a[MAXN],b[MAXN],c[MAXN],d[MAXN];

inline void init()
{
	read(n);read(m);read(k);
	if(k>m)puts("-1"),exit(0);
	Rep(i,1,n)read(w[i]);
	read(A);
	Rep(i,1,A)read(a[i]);
	read(B);
	Rep(i,1,B)read(b[i]);
}

static bool use[MAXN];

inline void solve()
{
	sort(a+1,a+A+1);sort(b+1,b+B+1);
	A=unique(a+1,a+A+1)-a-1;B=unique(b+1,b+B+1)-b-1;
	static int ps=1,np;
	Rep(i,1,A)
	{
		while(ps<=B&&b[ps]<a[i])++ps;
		if(b[ps]==a[i])c[++C]=a[i],++ps;
	}
	np=0;ps=1;
	Rep(i,1,A)
	{
		use[a[i]]=1;
		while(ps<=C&&c[ps]<a[i])++ps;
		if(a[i]!=c[ps])a[++np]=a[i];
	}A=np;
	np=0;ps=1;
	Rep(i,1,B)
	{
		use[b[i]]=1;
		while(ps<=C&&c[ps]<b[i])++ps;
		if(b[i]!=c[ps])b[++np]=b[i];
	}B=np;
	
	if(A+C<k||B+C<k||m<2*k-C)return(void)puts("-1");
	Rep(i,1,n)if(!use[i])d[++D]=w[i];
	Rep(i,1,A)a[i]=w[a[i]];
	Rep(i,1,B)b[i]=w[b[i]];
	Rep(i,1,C)c[i]=w[c[i]];
	sort(a+1,a+A+1);sort(b+1,b+B+1);sort(c+1,c+C+1);sort(d+1,d+D+1);
	ps=max(max(k-A,k-B),0);
	Chkmax(ps,2*k-m);
	Chkmax(ps,m-A-B-D);
	static ll ans,sm=0;
	Rep(i,1,k-ps)sm+=a[i]+b[i];
	Rep(i,1,ps)sm+=c[i];
	static int nA,nB,nD,lef;nA=max(k-ps,0),nB=max(k-ps,0),nD=0;
	a[A+1]=b[B+1]=d[D+1]=INT_MAX;
	
	lef=m-nA-nB-ps;
	while(lef-->0)
	{
		if(a[nA+1]<=b[nB+1]&&a[nA+1]<=d[nD+1])sm+=a[++nA];
		else if(b[nB+1]<=a[nA+1]&&b[nB+1]<=d[nD+1])sm+=b[++nB];
		else sm+=d[++nD];
	}
	ans=sm;++ps;
	while(ps<=C&&ps<=m)
	{
		sm+=c[ps];
		if(nA>=k-ps&&nB>=k-ps&&a[nA]+b[nB]-d[nD+1]>=max(max(a[nA],b[nB]),d[nD]))
			sm-=a[nA--]+b[nB--]-d[++nD];
		else
		{
			if(a[nA]>=b[nB]&&a[nA]>=d[nD])sm-=a[nA--];
			else if(b[nB]>=a[nA]&&b[nB]>=d[nD])sm-=b[nB--];
			else sm-=d[nD--];
		}

		Chkmin(ans,sm);
		++ps;
	}
	printf("%lld\n",ans);
}

int main()
{
    init();
    solve();
    return 0;
}
```

---

## 作者：zzw4257 (赞：1)

inf计划第二题,评分`2500`,思路**未**看题解，实现**看**了题解改的

> 给$n$个物品与价格$c_i$，$A,B$两人分别有一些喜欢的物品，求最小的花费使得购买的$m$件物品物品被$A$,$B$**分别**喜欢的数量都$\geqslant k$

贪心好像很简单的样子，有一类物品是取了会贡献两次所以这类点要单独考虑

考虑把物品分成没有贡献,贡献$A$,贡献$B$,贡献$AB$的四类假设分别为$S_0,S_1,S_2,S_3$

枚举$S_3$个数$i\in[1,\min\{m,|S_3|\}]$,然后$S_1/S_2$类分别取前$\min\{|S_1|,K-i\}/\min\{|S_2|,K-i\}$小的，最后在所有剩余物品中把$m$补满(判一下早超)

然后怎么做呢，感觉可以快速调整,也就是说可以用$4$个指针维护在每类数的位置

然后细节很少。。。~~但我错了很久~~

```cpp
for(i=0;i<=*p[3]&&i<=m;i++)if(K-i<=*p[1]&&K-i<=*p[2]){
    while(pos[3]<=i)res+=p[3][pos[3]++],++cnt;
    if(K-i+2==pos[1])res-=p[1][--pos[1]],--cnt;
    while(K-i>=pos[1])res+=p[1][pos[1]++],++cnt;
    if(K-i+2==pos[2])res-=p[2][--pos[2]],--cnt;
    while(K-i>=pos[2])res+=p[2][pos[2]++],++cnt;
    while(cnt<m){
        minn=0x3f3f3f3f;for(j=0;j<4;++j)if(pos[j]<=*p[j])minn=min(minn,p[j][pos[j]]);
        if(minn==INF)break;
        for(j=0;j<4;++j)if(p[j][pos[j]]==minn){res+=p[j][pos[j]++];break;}
        ++cnt;
    }
    if(cnt==m)ans=min(ans,res);
}
```





---

## 作者：ddxrS_loves_zxr (赞：0)

我们将物品分成 $4$ 个集合：

- 集合 $A$ 包含**只有** Arkady 喜欢的装饰。
- 集合 $B$ 包含**只有** Masha 喜欢的装饰。
- 集合 $C$ 包含二人都喜欢的装饰。
- 集合 $D$ 包含没人喜欢的装饰。

分别记这 $4$ 个集合的大小为 $a,b,c,d$。

我们可以先将这 $4$ 个集合分别按照花费从小到大来排序，并在后面按照这样的顺序来选择装饰。

不妨让我们来枚举我们从集合 $C$ 中选取了多少个装饰，假设选择了 $i$ 个。

那么我们至少要从集合 $A$ 和集合 $B$ 中分别选取 $j=k-i$ 个装饰。

那么对于确定的 $i$，这 $i+2j$ 个装饰是必选的，我们先将它们选上。此时还有一个限制没有满足，就是 $i+2j$ 可能不足 $m$。

此时，我们就需要从集合 $A$ 的剩下 $a-i$，集合 $B$ 的剩下 $b-j$，集合 $C$ 的剩下 $c-j$ 和集合 $D$ 的 $d$ 个装饰中选**花费最小的 $m-i-2j$** 个装饰。

考虑用一棵权值线段树来维护。我们将剩下的装饰以花费作为下标添加的线段树上，并维护区间的花费和以及拥有装饰的数量。

每次相当于在线段树上二分找到第一个满足装饰数量前缀和大于等于 $m-i-2j$ 的节点。

时间复杂度 $O(n\log V)$，可以通过离散化做到 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5, M = 1e9;
int n, m, qwq, K, c[N], a[N], b[N];
struct node {
    int t, id;
    bool operator <(const node &p) const {return t < p.t;}
} arr[N], brr[N], crr[N];
int cnta, cntb, cntc;
ll suma[N], sumb[N], sumc[N], ans = 0x3f3f3f3f3f3f3f3f;
int rot, siz[N << 5], lc[N << 5], rc[N << 5], cnt;;
ll tr[N << 5];
void change(int &p, int l, int r, ll x, int opt) {
    if(!p) p = ++cnt;
    int mid = l + r >> 1;
    if(l == r) return tr[p] += x * opt, siz[p] += opt, void();
    if(x <= mid) change(lc[p], l, mid, x, opt);
    else if(mid < x) change(rc[p], mid + 1, r, x, opt);
    tr[p] = tr[lc[p]] + tr[rc[p]], siz[p] = siz[lc[p]] + siz[rc[p]];
}
ll query(int p, int l, int r, int k) {
    int mid = l + r >> 1;
    if(l == r) return 1ll * k * l;
    if(siz[lc[p]] >= k) return query(lc[p], l, mid, k);
    else return tr[lc[p]] + query(rc[p], mid + 1, r, k - siz[lc[p]]);
}
int main() {
#ifdef ddxrS
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    cin>>n>>m>>K;
    for(int i = 1; i <= n; i++) cin>>c[i];
    cin>>qwq; for(int i = 1, p; i <= qwq; i++) cin>>p, a[p] = true;
    cin>>qwq; for(int i = 1, p; i <= qwq; i++) cin>>p, b[p] = true;
    for(int i = 1; i <= n; i++) {
        if(a[i] && b[i]) crr[++cntc] = {c[i], i};
        else if(a[i]) arr[++cnta] = {c[i], i};
        else if(b[i]) brr[++cntb] = {c[i], i};
        else change(rot, 1, M, c[i], 1);
    }
    sort(arr + 1, arr + cnta + 1), sort(brr + 1, brr + cntb + 1), sort(crr + 1, crr + cntc + 1);
    for(int i = 1; i <= cnta; i++) suma[i] = suma[i - 1] + arr[i].t;
    for(int i = 1; i <= cntb; i++) sumb[i] = sumb[i - 1] + brr[i].t;
    for(int i = 1; i <= cntc; i++) sumc[i] = sumc[i - 1] + crr[i].t;
    for(int i = K + 1; i <= cnta; i++) change(rot, 1, M, arr[i].t, 1);
    for(int i = K + 1; i <= cntb; i++) change(rot, 1, M, brr[i].t, 1);
    for(int i = 1; i <= cntc; i++) change(rot, 1, M, crr[i].t, 1);
    for(int i = 0, j = min(cnta, K), k = min(cntb, K); i <= cntc && i <= K; i++) {
        while(j >= 1 && j > K - i) change(rot, 1, M, arr[j].t, 1), j--;
        while(k >= 1 && k > K - i) change(rot, 1, M, brr[k].t, 1), k--;
        if(i >= 1) change(rot, 1, M, crr[i].t, -1);
        if(j >= K - i && k >= K - i && i + j + k <= m && siz[rot] >= m - i - j - k) ans = min(ans, suma[j] + sumb[k] + sumc[i] + query(rot, 1, M, m - i - j - k));
    }
    cout<<(ans < 0x3f3f3f3f3f3f3f3f ? ans : -1)<<'\n';
    cerr<<clock() * 1.0 / CLOCKS_PER_SEC<<'\n';
    return 0;
}
```

---

## 作者：SkyRainWind (赞：0)

考虑枚举都喜欢的个数 $s$ ，那么只有 A 喜欢的有 $k-s$ 个，B喜欢的 $k-s$ 个

然后我只需要找 所有的 $x$ 使得 $x$ 至多被 AB 一个人喜欢，而且没有被选的，找出前 $m - s - 2 \times (k-s)$ 大就可以了，可以用一个对顶堆维护（其实我之前还不知道这个东西，是自己脑补出来的2333）

细节超级多，代码里有详细注释（其实这种细节题关键的地方就在注释233）
```cpp
// by SkyRainWind
#include <cstdio>
#include <vector>
#include <cassert>
#include <queue>
#include <set>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mpr make_pair
#define debug() cerr<<"Yoshino\n"
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define pii pair<int,int>

using namespace std;

typedef long long LL;
#define int LL

const int inf = 1e9, INF = 0x3f3f3f3f, maxn = 2e5 + 5;

struct node{int val, id;}nd[maxn];
bool operator < (node a,node b){return a.val > b.val;}
node pq[maxn],pq2[maxn],pq3[maxn],pq4[maxn];
// pq 都不喜欢 pq2 A pq3 B pq4 AB 
int s2[maxn], s3[maxn], s4[maxn], s5[maxn];
// 前缀和 
int n,m,k,vis[maxn],pc1,pc2,pc3,pc4,pc5;
priority_queue<int>r1;
priority_queue<int,vector<int>,greater<int> >r2;	// 对顶堆 

void upd(int s,LL &res){	// 注意 res 是只包含单 A 单B AB都不喜欢 三种情况 
	// 去掉（不选）单 A 和单 B 的第(k-s)项，加入对顶堆中，因为实际上选的个数少了1，因此答案的堆（大根堆）中size需要+1 
	LL mx=-1;
	if(!r1.empty())mx = r1.top();
	node cur1 = pq2[k-s], cur2 = pq3[k-s];
	if(cur1.val > cur2.val)swap(cur1, cur2);
	if(r1.empty()){	// 特判一开始：如果AB都喜欢的s项和单A单B分别的(k-s)项加起来恰好是m的情况（此时答案堆size为0但是要更新了） 
		res -= cur1.val; res -= cur2.val;
		vector<int>tmp;
		tmp.push_back(cur1.val);
		tmp.push_back(cur2.val);
		if(!r2.empty())tmp.push_back(r2.top()), r2.pop();
		if(!r2.empty())tmp.push_back(r2.top()), r2.pop();
		sort(tmp.begin(), tmp.end());
		// 利用辅助堆（小根堆）中的2个元素（因为最坏情况是单A 单B 的第(k-s)项都比小根堆顶2个元素小 
		
		res += tmp[0];	// 因为 答案堆size 要加1，选最小的 
		r1.push(tmp[0]);r2.push(tmp[1]);r2.push(tmp[2]);r2.push(tmp[3]); 
		return ;
	}
	
	// 剩下的三种情况相对好考虑，注意答案堆和辅助堆每次都要size+1 
	// res 减是因为本来加上了的前缀和中含有当前第 (k-s) 项，但是现在要删去 
	if(cur2.val <= mx){	// delete mx
		r1.pop();r1.push(cur1.val);r1.push(cur2.val);r2.push(mx);
		res = res - mx;
	}else if(cur1.val <= mx){
		r1.push(cur1.val);r2.push(cur2.val);
		res = res - cur2.val;
	}else{
		int tp = r2.top();r2.pop();
		r2.push(cur1.val), r2.push(cur2.val);
		r1.push(tp);
		res = res + tp - cur1.val - cur2.val;
	}
}

signed main(){
//	freopen("CF799E.in","r",stdin);
//	freopen("CF799E-my.out","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)scanf("%lld",&nd[i].val), nd[i].id = i;
	sort(nd+1,nd+n+1);
	reverse(nd+1,nd+n+1);
	
	int tt;scanf("%lld",&tt);
	while(tt--){int v;scanf("%lld",&v);vis[v] ++;}
	scanf("%lld",&tt);
	while(tt--){int v;scanf("%lld",&v);vis[v] += 2;}
	for(int i=1;i<=n;i++){
		if(vis[nd[i].id] == 1){pq2[++pc2] = nd[i];s2[pc2] = s2[pc2-1] + nd[i].val;} 
		else if(vis[nd[i].id] == 2){pq3[++pc3] = nd[i];s3[pc3] = s3[pc3-1] + nd[i].val;}
		else if(vis[nd[i].id] == 3){pq4[++pc4] = nd[i];s4[pc4] = s4[pc4-1] + nd[i].val;}
		else pq[++pc1]=nd[i];
	}
		
	LL ans = 1e18, ff=0, res;
	for(int s=0;s<=min(pc4, k);s++){	// 枚举都喜欢的有几个 
		if(s + 2 * (k-s) > m)continue;	// 光满足喜欢>=k就已经超 m 了 
		if(n-(pc4-s) < m)continue;		// 因为钦定了剩下都喜欢的不选了（否则可以在那时候更新答案），而能选的不到 m个，也不行 
		if(k-s > pc2 || k-s > pc3)continue;
		
		int rest = m - s - 2*(k-s);
		if(++ ff == 1){	// 第一个暴力处理，之后每次更新答案 
			vector<int>tmp;
			for(int i=1;i<=pc1;i++)tmp.push_back(pq[i].val);
			for(int i=k-s+1;i<=pc2;i++)tmp.push_back(pq2[i].val);
			for(int i=k-s+1;i<=pc3;i++)tmp.push_back(pq3[i].val);
			sort(tmp.begin(),tmp.end());
			int rr = 0;
			LL sum = 0;
			for(int u : tmp){
				if(++rr <= rest)r1.push(u), sum += u;
				else r2.push(u);
			}
			res = s2[k-s] + s3[k-s] + sum;
			ans = min(ans, s4[s] + res);	// 因为都喜欢的是钦定的不改的，所以每次更新只需要维护 单A 单B 和AB 都不喜欢的答案 
			upd(s, res);
			continue;
		}
		
		ans = min(ans, res + s4[s]);
		upd(s, res);
	}
	
	// 特殊情况：AB都喜欢的数量 >= k，此时剩下的三种里面随便选，肯定取最小的 
	for(int i=1;i<=n;i++)
		if(vis[nd[i].id] <= 2){
			++pc5;
			s5[pc5] = s5[pc5-1] + nd[i].val;
		}
	for(int s=k;s<=min(pc4,m);s++){
		// s 个2个喜欢 剩下随便选
		if(m-s <= pc5){
			int tmp = s4[s];
			ans = min(ans, tmp + s5[m-s]); 
		}
	}
	printf("%lld\n",ans==(LL)1e18 ? -1 : ans);
//	cerr<<ans<<'\n';

	return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF799E)

# 题解

记总物品数为 $n$，只能买 $m$ 个使得两人喜欢的分别至少有 $k$ 个。

记 $sz1$ 为两人都喜欢的商品数，$sz2,sz3$ 分别为 $A,B$ 各自喜欢的商品数，首先我们可以预处理出来这仨东西：

```cpp
inline bool cmp(const int i,const int j){
    if(i==-1)return 0;
    if(j==-1)return 1;
    return c[i]<c[j];
}

int vis[MAXN+5];
inline void Solvetype(){
    rep(i,1,sz2)vis[a[i]]=1;
    rep(i,1,sz3)if(vis[b[i]]==1)
        vis[b[i]]=-1,both[++sz1]=b[i];
    rep(i,1,sz2)if(vis[a[i]]==-1)a[i]=-1;
    rep(i,1,sz3)if(vis[b[i]]==-1)b[i]=-1;
    sort(a+1,a+sz2+1,cmp),sort(b+1,b+sz3+1,cmp),sort(both+1,both+sz1+1,cmp);
    sz2-=sz1,sz3-=sz1;
}
```

考虑无解的情况：

1. $m<k$ 显然无解；
2. 即使两人买最少商品也超过 $m$，即 $m<sz1+2\times (k-sz1)$；
3. 两个人喜欢的商品数没有 $k$ 个，即 $sz1+sz2<k$ 或者 $sz1+sz3<k$；

然后，我们考虑枚举我们一共买了 $x$ 个两人都喜欢的商品，然后每个人一定还需买 $sz1-x,sz2-x$ 个各自喜欢的，贪心地，我们一定都是从小往大买

然后，我们在剩下没买的商品中选择前 $m-x-(sz1-x)-(sz2-x)$ 小的并将其买下，此处我们可以使用线段树（同机房有人用更巧妙的数组来做，但是时间复杂度依然要带 $\log$）维护全部商品中没选的的商品和，然后在线段树中找前 $m-x-(sz1-x)-(sz2-x)$ 小即可

总体来说题并不复杂，但是可以是因为我方法的原因，实现较为麻烦

总时间复杂度为 $\mathcal O(k\log n+n\log n)$

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13343188.html
```



---

