# Arpa and a list of numbers

## 题目描述

Arpa has found a list containing $ n $ numbers. He calls a list bad if and only if it is not empty and gcd (see notes section for more information) of numbers in the list is $ 1 $ .

Arpa can perform two types of operations:

- Choose a number and delete it with cost $ x $ .
- Choose a number and increase it by $ 1 $ with cost $ y $ .

Arpa can apply these operations to as many numbers as he wishes, and he is allowed to apply the second operation arbitrarily many times on the same number.

Help Arpa to find the minimum possible cost to make the list good.

## 说明/提示

In example, number $ 1 $ must be deleted (with cost $ 23 $ ) and number $ 16 $ must increased by $ 1 $ (with cost $ 17 $ ).

A gcd (greatest common divisor) of a set of numbers is the maximum integer that divides all integers in the set. Read more about gcd [here](https://en.wikipedia.org/wiki/Greatest_common_divisor).

## 样例 #1

### 输入

```
4 23 17
1 17 17 16
```

### 输出

```
40
```

## 样例 #2

### 输入

```
10 6 2
100 49 71 73 66 96 8 60 41 63
```

### 输出

```
10
```

# 题解

## 作者：囧仙 (赞：2)

## 题解

考虑枚举最终所有数字的一个公因子是多少。不妨设为 $d$。那么对于一个数字 $a$，我们要使得它成为 $d$ 的倍数只有两种途径：把它删除，或者加上 $(d-a\bmod d)\bmod d$ 个 $1$。这是由于给 $a$ 加上若干个 $1$ 后再删除显然是比直接删除更劣的。设 $f(a_i)=(d-a\bmod d)\bmod d$，也就是如果使用操作 $2$，需要多少下可以让 $a_i$ 成为 $d$ 的倍数。

观察到 $a_i\in[1,10^6]$，因此考虑用个桶存下所有的 $a_i$。接着按照 $f(a_i)$ 的值进行分类。如果 $f(a_i)=0$，那么显然不用操作这类 $a_i$，否则，如果 $f(a_i)\cdot y\le x$，那么增加这些 $a_i$ 会比删除这些 $a_i$ 更优。反之亦然。

但因为我太菜了，我是按照 $[l=d\times k,r=d\times k+d-1]\quad k=0,1,2,\cdots$ 来将值域分块的（一共会被分为 $\left\lceil\frac{10^6}{d}\right\rceil$ 块）。每块内的值的 $f(a_i)$ 为 $0,d-1,d-2,\cdots ,0$。这么做容易统计两种操作产生的价值。预处理出桶里面数字的前缀和、前缀数量：

$$
\begin{aligned}
P_i&=\sum_{j=1}^n [a_j\le i]\cdot a_j \cr
Q_i&=\sum_{j=1}^n [a_j\le i]\cdot 1 \cr
\end{aligned}
$$

为了方便，设 $\operatorname{sum}_P(l,r)=P_r-P_{l+1}$ 和 $\operatorname{sum}_Q(l,r)=Q_r-Q_{l-1}$。由于先前已经讨论过了，$f(a_i)\cdot y\le x$ 时增加更优，否则删除更优，因此可以求出一个界值 $p=\max\{l,r-\left\lfloor\frac{y}{x}\right\rfloor\}$，对于 $[l+1,p]$ 内的数字都是删除更优，对于 $[p+1,r]$ 内的数字都是增加更优。容易统计这一块的总花费：

$$x\cdot\operatorname{sum}_Q(l+1,p)+y\cdot\left(\operatorname{sum}_Q(p+1,r)\cdot d\cdot (k+1)-\operatorname{sum}_P(p+1,r)\right)$$

那么统计每一块的花费和，就能求出在这样的 $d$ 下的总花费了。

考虑时间复杂度。设 $m=10^6$。对于每个 $d$ 都会分出 $\left\lceil\frac{m}{d}\right\rceil$ 块，每块内的处理都是 $\mathcal O(1)$ 的。因此，总复杂度为：

$$\mathcal O\left(n+\sum \left\lceil\frac{m}{d}\right\rceil\right)=\mathcal O(n+m\log m)$$

然后可以发现如果 $d$ 是一个合数，那么它的一个质因数肯定比它更优（并且必然在它之前就枚举过了）。因此只用枚举素数即可。时间复杂度和埃氏筛法相同，为 $\mathcal O(m\log\log m)$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e6+3;
int n,m=1e6,x,y; i64 ans=1e18,P[MAXN*2],Q[MAXN*2];
i64 sum(int l,int r,i64 *W){return W[r]-W[l-1];}
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
int main(){
    n=qread(),x=qread(),y=qread();
    up(1,n,i){int t=qread(); P[t]+=t,Q[t]++;}
    up(1,2*m,i) P[i]+=P[i-1],Q[i]+=Q[i-1];
    up(2,m,i){
        i64 c=0; int p=0,l,r;
        for(int j=0;i*j+1<=m;++j){
            l=i*j+1,r=i*j+i-1,p=max(l-1,r-x/y);
            c+=1ll*x*sum(l,p,Q);
            c+=1ll*y*(1ll*i*(j+1)*sum(p+1,r,Q)-sum(p+1,r,P));
            if(c>1e18) c=1e18;
        }
        ans=min(ans,c);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：弹星者 (赞：2)

我们从1到max(ai)枚举最后都变成的gcd是多少，假设为g，那么所有数都必须变成一个比g大的最小的g的倍数k·g。   
枚举k，然后在一个区间[(k-1)*g+1,k*g]里，一定存在一个分界点f，使得小于等于f的数全都删去，因为删除的代价小于把它们都变成kg的代价；大于f的数全都变成kg。因为x<=(kg-ai)*y，所以显然这个分界点是kg-ceil(x/y)。不过分界点不一定落在区间里，要讨论一下。  
要预处理前缀和cnt(i)表示小于等于i的数的个数，sum(i)表示小于等于i的数的和。 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int cnt[2000005],n,x,y,a[2000005],maxn;
ll sum[2000005],ans=9000000000000000000ll,nowans;
int main(){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		++cnt[a[i]];
		sum[a[i]]+=(ll)a[i];
	}
	maxn=*max_element(a+1,a+n+1);
	if(maxn==1){
		printf("%lld\n",(ll)n*(ll)min(x,y));
		return 0;
	}
	for(int i=2;i<=maxn*2;i++){
		cnt[i]+=cnt[i-1];
		sum[i]+=sum[i-1];
	}
	for(int i=2;i<=maxn;i++){
		nowans=0;
		for(int j=i;j<=maxn+i;j+=i){
			int r=j;
			int l=r-i+1;
			int upd=r-(int)(ceil((double)x/(double)y)+0.5);
			if(upd>=l)
				nowans+=(ll)x*(ll)(cnt[upd]-cnt[l-1]);
			else upd=l-1;
			nowans+=(ll)y*((ll)(cnt[r]-cnt[upd])*(ll)r-(sum[r]-sum[upd]));
		}
		ans=min(ans,nowans);
	}
	printf("%lld\n",ans);
	return 0;
}
```

特殊情况：一开始全是1。

---

## 作者：斗神_君莫笑 (赞：1)

当我们知道了这个gcd时，对于每个数就分为了删除或者加到k\*gcd（gcd的倍数）  
那么显然一个数只能加x/y次，否则还不如直接删除  
我们可以在外面预处理出这个值为max_increase

然后便是枚举gcd了  
但是我们发现，如果直接暴力的话复杂度是n^2  
（虽然可以卡过去  
想起我们需要的数在每个被gcd划分的区间中具有相似性  
也就是说对于每一段由gcd划分出的区间，都可以由一个数值划分出加和删两种选择  
而这个数值不就是r-max_increase嘛   
这时候就应该想到前缀和了  
预处理出<=某个值的数 的个数和他们的和  
那么我们就可以O1求出代价  

关于复杂度：   
对于每一个gcd，都能把区间分为n/gcd段  
易证这个调和级数会收敛在nlogn（别问，问就是背）  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[500010],sum[2000010],cnt[2000010];
signed main(){
	int n,x,y;
	scanf("%lld%lld%lld",&n,&x,&y);
	int s=0;
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		s=max(s,a[i]);
		++cnt[a[i]];
		sum[a[i]]+=a[i];
		//先对于每个值处理
		//由于值分散的特性需要最后统一求前缀和 
	}
	if(s==1){ 
		printf("%lld",n*min(x,y));
		return 0;
	}
	for(int i=1;i<=s*2;++i){//考虑到最大值可能需要加,因此往后处理 
		sum[i]+=sum[i-1];
		cnt[i]+=cnt[i-1];
	}
	int max_increase=ceil((double)(x/y)+0.5),ans=0x7ffffffffffffff;
	for(int i=2;i<=s;++i){
		int now_ans=0;
		for(int j=i;j<=s+i;j+=i){
			int l=j-i+1,r=j;
			int k=r-max_increase;
			if(k>=l)//删除 
				now_ans+=x*(cnt[k]-cnt[l-1]);
			else k=l-1;//全部增加 
			now_ans+=y*(r*(cnt[r]-cnt[k])-(sum[r]-sum[k]));
		}
		ans=min(ans,now_ans);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：ZLCT (赞：0)

# CF850B Arpa and a list of numbers
## 题目翻译
给定一个正整数序列 $a$，我们可以花费 $x$ 的代价删除一个数或花费 $y$ 的代价将一个数 $+1$，其中操作次数不限。问最少花费多少代价才能使得序列的最大公约数不为 $1$。（空序列最大公约数不为 $1$）。\
$n\le 5\times 10^5,A\le 10^6。$（$A$ 表示值域）
## solution
这个题是一个很有意思的好题，下面我将一步步地还原本题的思考过程。
### NO.1 暴力
题目既然使所有数的 $\gcd$ 不为 $1$，那就说明最后所有数都会具有一个相同的因数，那根据唯一分解定理我们可知这也等价于所有数最后都会具有一个相同的质因数。\
那我们就考虑去枚举这个质因数 $p$，那对于每一个 $a_i$，我们有两种选择，第一种可以将其删除，第二种可以将其增加一些使得其是 $p$ 的倍数。\
由于我们肯定是想要选择尽可能少的代价，于是我们只会将它增加到最靠近它的 $d$ 的倍数，也就是只会增加 $d-(a_i\bmod p)$。\
于是对于每一个 $a_i$，它最优的代价就是 $\min(x,y\times(d-(a_i\bmod p)))$。\
这样需要枚举每一个质因数，每次需要枚举这 $n$ 个数，总复杂度是 $O(\pi(A)n)\approx O(\frac{A}{\ln{A}}n)\approx 4\times 10^{10}$。\
此时会有两种思考，一种觉得这个复杂度也不是很高，稍微优化一下或许能过去，一种是觉得这种卡法过不去，另寻出路。\
我们先来看第一种思考。
### NO.2 暴力优化
在第一次读到这个题时，敏锐的数学直觉就告诉我们有一个质因子非常特殊：$2$。\
这是因为对于 $2$ 而言，$+1$ 和删除的贡献是一样的，所以只需要知道有多少个是 $2$ 的倍数，剩下的那些都一定会选择 $\min(x,y)$ 的代价。\
那这似乎没什么用，但是我们继续思考，这也就意味着一个数如果从不是 $p$ 的倍数变成是 $p$ 的倍数，那它的代价一定不小于其变成 $2$ 的倍数的代价。\
于是这也就是说设 $cnt_d$ 表示在序列中质数 $d$ 的倍数的个数，我们只需要考虑 $cnt_d>cnt_2$ 的数以及 $2$ 时的代价即可。\
这有什么用处呢，这样就可以过了。\
我们先算一次 $p=2$ 时的代价，然后我们只要每次随机一个质数 $d$，若该质数没有被考虑过并且 $cnt_d>cnt_2$ 我们就考虑它，最终答案就是所有情况的最小值。\
可能十分疑惑，感觉这稍微一卡就不行了，当然我也觉得很假，那我们来分析一下这个算法。\
我们感性理解一下，如果序列中的质因数比较少，那我们就一定可以全部考虑到，此时正确性没什么问题。\
那如果序列中的质因数比较多，并且最终答案的因子不是 $2$ 时，的确会 被卡，所以如果你运气不好的话会在第 $115$ 个点被卡，但是我们思考一下此时既然全是奇数，那 $3$ 作为因子就比较优秀了，因为奇数中 $3$ 的倍数一定是最多的。\
当然这也很不严谨，所以我们也可以把 $[2,100]$ 内所有质数都先算一遍，然后你会发现即使运气不好也可以轻松跑过去。\
具体严谨证明十分困难，等想出来再补上，但是可以证明的是由于最高次数就才是一开始算的 $4\times 10^{10}$，所以加一点剪枝以后复杂度只要降 $100$ 的常数就够了。
### NO.3 正经做法
这道题的正经做法还是需要比较强大的数学经验的。\
我们注意到对于当前枚举的质数 $p$，值域在 $[1,p]$ 区间与值域在 $[p+1,2p]$ 之间的数其实贡献是类似的，因为所有的 $kp+1$ 的代价计算都是 $\min(y\times(p-1),x)$，因此我们可以从头开始依次地去枚举每一个长度为 $p$ 的段。\
至于为什么想到去这么枚举，这是因为如果我们能 $O(1)$ 算出每一段的代价，根据调和级数我们只需要枚举 $O(A\ln{A})$ 段，这个复杂度是完全可以接受的。\
那我们考虑如何去计算每一段的代价。\
首先根据 $x,y$ 的大小关系我们可以算出在什么时候删除更优什么时候不断加一更优，具体地，我们设当前区间是 $[z-p+1,z]$，要求当值 $q$ 为何时时选择删除更优，那么有以下式子：
```math
\begin{equation*}
\begin{cases}
q\ge z-p+1\\
(z-q)\times y\le x
\end{cases}
\end{equation*}
```
解得：
```math
\begin{equation*}
\begin{cases}
q\ge z-p+1\\
q\ge z-\frac{x}{y}
\end{cases}
\end{equation*}
```
于是 $q=\max(z-p+1,z-\lfloor{\frac{x}{y}}\rfloor)$。\
那我们开一个桶 $t_x$ 表示 $x$ 的出现次数，再开两个前缀和数组：
```math
\begin{aligned}
pre1_x=\sum\limits_{i=1}^{x}t_i\\
pre2_x=\sum_{i=1}^{x}t_i\times i
\end{aligned}
```
对于 $j<q$ 的部分我们选择删除，代价就是 $x\times(pre1_{x-1}-pre1_{z-p})$，对于 $j\ge q$ 的部分我们选择加到 $z$，总共要加的代价就是 $y\times(z\times(pre1_{z-1}-pre1_{q-1})-(pre2_{z-1}-pre2_{q-1}))$。\
可以直接这么做，复杂度是 $O(A\ln A)$ 也可以接受，但是我们前面说了，只需要去枚举质数即可，那只枚举质数我们需要枚举的次数就是
```math
\displaystyle\sum\limits_{d\in\mathbb{P}}^{A}\lfloor\frac{A}{d}\rfloor
```
那我们知道这个函数与调和级数十分相似，可以看作是调和级数部分点所组成的，那由于质数的分布大致比较均匀，所以我们可以认为其与调和函数的计算规则一致，因此可以认为复杂度为 $O(\frac{A}{\ln{A}}\ln{A})$，但是由于值域比较小，所以不能将两个 $\ln{A}$ 抵消，只能算是近线性。
## code
### 法1
```cpp
#include<bits/stdc++.h>
#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define int long long
using namespace std;
const int N=1e6+8888;
const int maxn=1e6;
mt19937 rng(time(0));
int prime[N>>3],cnt,vx,vy,n,a[N],ans=1e18+7,t[N],mind[N];
bool notprime[N],vis[N>>3];
int can[N>>3],len;
void init(){
    notprime[1]=1;mind[1]=1;
    for(int i=2;i<=maxn;++i){
        if(!notprime[i]){
            prime[++cnt]=i;
            mind[i]=i;
        }
        for(int j=1;j<=cnt&&prime[j]<=maxn/i;++j){
            notprime[i*prime[j]]=1;
            mind[i*prime[j]]=prime[j];
            if(i%prime[j]==0)break;
        }
    }
}
void make(int x){
    while(x!=1){
        t[mind[x]]++;
        int dd=mind[x];
        while(x%dd==0)x/=dd;
    }
}
void check(int d){
    int res=0;
    for(int i=1;i<=n;++i){
        if(!(a[i]%d))continue;
        res+=min(vx,vy*(d-a[i]%d));
        if(res>=ans)return;
    }
    ans=res;
    return;
}
bool OK(double x){
    return x*1000.0/CLOCKS_PER_SEC<1500.0;
}
signed main(){
    clock_t st=clock();
    init();
    scanf("%lld%lld%lld",&n,&vx,&vy);
    for(int i=1;i<=n;++i){
        scanf("%lld",&a[i]);
        make(a[i]);
    }
    for(int i=3;i<=cnt;++i){
        if(t[prime[i]]>t[2])can[++len]=prime[i];
    }
    check(2);
    check(3);
    for(int i=1;i<=len&&can[i]<=100;++i){
        vis[i]=1;
        check(can[i]);
    }
    if(!len){
        printf("%lld\n",ans);
        return 0;
    }
    while(OK(clock()-st)){
        int d=rng()%len+1;
        if(vis[d])continue;
        vis[d]=1;
        check(can[d]);
    }
    printf("%lld\n",ans);
    return 0;
}
```
### 法2
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+8888;
const int maxn=1e6+666;
int prime[N>>3],cnt,vx,vy,n,a[N],ans=1e18+7,pre1[N<<1],pre2[N<<1];
bool notprime[N];
void init(){
    notprime[1]=1;
    for(int i=2;i<=maxn;++i){
        if(!notprime[i]){
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&prime[j]<=maxn/i;++j){
            notprime[i*prime[j]]=1;
            if(i%prime[j]==0)break;
        }
    }
}
signed main(){
    init();
    cin>>n>>vx>>vy;
    for(int i=1;i<=n;++i){
        int x;cin>>x;
        pre1[x]++;
        pre2[x]+=x;
    }
    for(int i=1;i<=2ll*maxn;++i){
        pre1[i]+=pre1[i-1];
        pre2[i]+=pre2[i-1];
    }
    for(int id=1;id<=cnt;++id){
        int d=prime[id],nans=0;
        for(int j=d;j<=2ll*maxn;j+=d){
            int x=max((j*vy-vx+vy-1)/vy,j-d+1);
            nans+=(pre1[x-1]-pre1[j-d])*vx+(j*(pre1[j-1]-pre1[x-1])-(pre2[j-1]-pre2[x-1]))*vy;
            if(nans>=ans)break;
        }
        ans=min(ans,nans);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：cike_bilibili (赞：0)

注意到值域在 $10^6$ 范围内，可以枚举 gcd，设当前枚举到了 $g$，那么序列中每一个数要么一直加一到最近的 $kg$，要么直接删去，对于每一段值域区间 $[(k-1)g+1,kg]$，一定存在一个分界点 $pos$ 使得 $[pos,kg]$ 中的元素一直加一，$[(k-1)g+1,pos-1]$ 中的元素直接删去，$pos$ 可以由 $x$ 和 $y$ 推出，答案用树状数组维护即可，时间复杂度 $O(N\log N + V \ln V \log N)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
const int V=1000000;
int n,x,y;
int a[2000005];
struct BIT{
	ll tree[2000005];
	int lowbit(int i){
		return i&-i;
	}
	void add(int pos,int val){
		for(int i=pos;i<=2*V;i+=lowbit(i))tree[i]+=val;
	}
	ll ask(int l,int r){
		if(l>r)return 0;
		ll ans=0;
		for(int i=r;i;i-=lowbit(i))ans+=tree[i];
		for(int i=l-1;i;i-=lowbit(i))ans-=tree[i];
		return ans;
	}
}T1,T2;
ll ans=1e18;
int main(){
	n=read(),x=read(),y=read();
	int len=x/y;
	for(int i=1;i<=n;i++)a[i]=read(),T1.add(a[i],1),T2.add(a[i],a[i]);
	for(int i=2;i<=V;i++){//枚举gcd 
		ll sum=0;
		int j=0;
		do{
			j+=i;
			int l=j-i+1,r=j;
			sum+=1ll*y*(1ll*j*T1.ask(max(r-len,l),r)-T2.ask(max(r-len,l),r))+1ll*x*T1.ask(l,r-len-1);
//			cout<<l<<' '<<r<<' '<<len<<' '<<sum<<' '<<T1.ask(max(r-len,l),r)<<'\n';
		}while(j<=V);
		ans=min(ans,sum);
	}
	cout<<ans;
}
```

---

## 作者：猪小屁 (赞：0)

这道题枚举公约数就好了，枚举倍数还要判断一下，会枚举到无用的数，增加复杂度。

然后枚举区间，区间的右端点为枚举的倍数（因为要让最后的gcd都为那个数）。

再找到每个区间的临界值，临界值右边的数都要加，才能使代价最小，左边都要删除。然后就可以列不等式去找这个临界值了。

开了两个数组，cnt[i]记录原数组中有多少个数在i之前

sum[i]记录第i个数之前所有的原数组的前缀和

比如原数组为5 18 27 29
cnt[20]=2 cnt[30]=4 sum[6]=5 sum[20]=5+18=23

**特殊情况：全为1，就必须全删除或全加1**

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
int cnt[2000005],n,x,y,a[500005],N;
ll sum[2000005],ans=9000000000000000000ll,nowans;
int main(){
    //freopen("a.in","r",stdin);
    scanf("%d%d%d",&n,&x,&y);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);
        ++cnt[a[i]];
        sum[a[i]]+=(ll)a[i];
    }
    N=*max_element(a+1,a+n+1);
    if(N==1){
        printf("%I64d\n",(ll)n*(ll)min(x,y));
        return 0;
    }
    for(int i=2;i<=N*2;++i){
        cnt[i]+=cnt[i-1];
        sum[i]+=sum[i-1];//预处理
    }
    for(int i=2;i<=N;++i){
        nowans=0;
        for(int j=i;j<=N+i;j+=i){
            int R=j;
            int L=R-i+1;
            int upd=R-(int)(ceil((double)x/(double)y)+0.5);//向上取整
            if(upd>=L){
                nowans+=(ll)x*(ll)(cnt[upd]-cnt[L-1]);//处理删除的代价
            }//若这个点在区间内
            else{
                upd=L-1;
            }//不在的话，这个区间都该加
            nowans+=(ll)y*((ll)(cnt[R]-cnt[upd])*(ll)R-(sum[R]-sum[upd]));//处理加的代价
        }
        ans=min(ans,nowans);
    }
    printf("%I64d\n",ans);
    return 0;
}
```



---

## 作者：xiaoming_king (赞：0)

没啥好说的 
注意特殊值 开头全部为1
分界点也许不在区间里
从1开始枚举 到max（ai）最后所算出的gcd
```cpp
 #include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
int cnt[2000005],n,x,y,a[500005],N;
ll sum[2000005],ans=9000000000000000000ll,nowans;
int main(){
    //freopen("a.in","r",stdin);
    scanf("%d%d%d",&n,&x,&y);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);
        ++cnt[a[i]];
        sum[a[i]]+=(ll)a[i];
    }
    N=*max_element(a+1,a+n+1);
    if(N==1){
        printf("%I64d\n",(ll)n*(ll)min(x,y));
        return 0;
    }
    for(int i=2;i<=N*2;++i){
        cnt[i]+=cnt[i-1];
        sum[i]+=sum[i-1];
    }
    for(int i=2;i<=N;++i){
        nowans=0;
        for(int j=i;j<=N+i;j+=i){
            int R=j;
            int L=R-i+1; 
            int upd=R-(int)(ceil((double)x/(double)y)+0.5);
            if(upd>=L){
                nowans+=(ll)x*(ll)(cnt[upd]-cnt[L-1]);
            } 
            else{
                upd=L-1;
            }
            nowans+=(ll)y*((ll)(cnt[R]-cnt[upd])*(ll)R-(sum[R]-sum[upd]));
        }
        ans=min(ans,nowans);
    }
    printf("%I64d\n",ans);
    return 0;
}
```


---

