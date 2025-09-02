# [USACO25OPEN] OohMoo Milk G

## 题目描述

农夫约翰正在生产他世界闻名的 OohMoo 牛奶以获取利润。他有 $N$ 个（$1 \leq N \leq 10^5$）瓶子需要装牛奶，每个瓶子初始含有 $m_i$（$0 \leq m_i \leq 10^9$）单位的牛奶。每天，他会选择 $A$ 个（$1 \leq A \leq N$）瓶子，每个被选中的瓶子增加 $1$ 单位牛奶。

不幸的是，他的竞争对手农夫 Nhoj 知道这个生产过程并计划破坏。每天在农夫约翰添加牛奶后，农夫 Nhoj 会偷偷从 $B$ 个（$0 \leq B < A$）不同的非空瓶子中各偷走 $1$ 单位牛奶。为了不被发现，农夫 Nhoj 确保 $B$ 严格小于 $A$。

经过 $D$ 天（$1 \leq D \leq 10^9$）后，农夫约翰将出售他的牛奶。如果一个瓶子含有 $M$ 单位牛奶，它将卖出 $M^2$ moonies 的价钱。

设 $P$ 为唯一确定的利润值，使得无论农夫 Nhoj 如何操作，农夫约翰都能保证至少获得 $P$ 利润；同时无论农夫约翰如何操作，农夫 Nhoj 都能确保农夫约翰最多获得 $P$ 利润。请输出 $P$ 对 $10^9+7$ 取模的结果。


## 说明/提示

样例一解释：经过 $4$ 天后，可能的牛奶量为 $[4,11,11,12,12]$，总利润为 $4^2+11^2+11^2+12^2+12^2=546$。

- 测试点 $4\sim6$：$N,D \leq 1000$。
- 测试点 $7\sim10$：$D \leq 10^6$。
- 测试点 $11\sim20$：无额外限制。

## 样例 #1

### 输入

```
5 4
4 2
4 10 8 10 10```

### 输出

```
546```

## 样例 #2

### 输入

```
10 5
5 1
1 2 3 4 5 6 7 8 9 10```

### 输出

```
777
```

## 样例 #3

### 输入

```
5 1000000000
3 1
0 1 2 3 4```

### 输出

```
10```

# 题解

## 作者：dengchengyu (赞：5)

显然当 $m$ 越大时，使 $m$ 加一或减一造成的变化量越大。

于是约翰的操作就是把最大 $A$ 个加一，Nhoj 的操作就是把最大 $B$ 个减一，然而直接动态维护这个过程是不好做的。

显然有一个结论，由于 $B\le A$，无论怎么操作最大的 $A$ 个数还是那些数，于是排序后只考虑前 $A$ 个数。那么约翰每次都会把这些数加一，于是考虑先把所有数加 $D$，然后接下来 Nhoj 可以做 $D\times B$ 次操作，每次选择一个数使它减一，并且要满足一个数不能减超过 $D$ 次，上述过程与原题意是等价的。

接下来我们二分一个数 $mid$，要使所有大于 $mid$ 的数减到 $mid$ 或是减完 $D$ 次。如果还没完成这个过程次数就用完了，说明这个 $mid$ 不合法，要找更大的 $mid$。否则如果还有剩余次数，那么**亲**自指**定**这些数最小减到 $mid-1$，然后统计答案并尝试寻找更小的 $mid$。

显然时间复杂度为 $O(n\log V)$。

```cpp
const int N=1e5+5,mod=1e9+7;
int n,D,A,B,a[N];
signed main(){
	read(n,D,A,B);
	fo(i,1,n) read(a[i]);
	sort(a+1,a+1+n,greater<>());
	fo(i,1,A) a[i]+=D;
	int l=0,r=2e9,ans=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		int cnt=0;
		ll sum=0,res=0;
		fo(i,1,A) {
			if(a[i]>=mid) {
				int del=min(D,a[i]-mid);
				sum+=del;
				if(del<D) ++cnt;
				else res=(res+(ll)(a[i]-D)*(a[i]-D))%mod;
			}
			else res=(res+(ll)a[i]*a[i])%mod;
		}
		if(sum>(ll)D*B) {l=mid+1; continue;}
		fo(i,A+1,n) res=(res+(ll)a[i]*a[i])%mod;
		ll t=min((ll)cnt,(ll)D*B-sum);
		if(mid==0) t=0;
		res=(res+(ll)mid*mid%mod*(cnt-t))%mod;
		res=(res+(ll)(mid-1)*(mid-1)%mod*t)%mod;
		ans=res,r=mid-1;
	}
	write(ans);
	return 0;
}
```

---

## 作者：HD0X (赞：4)

题意略。

首先发现 John 一定选最大的 $A$ 瓶，Nhoj 一定选最大的 $B$ 瓶（因为它们增长量最大）。所以选定的 $A$ 瓶是固定的，但 $B$ 瓶会变的，难以维护，所以考虑换一种方式。

我们先将 $A$ 瓶牛奶从大到小排序，加上 $d$，再对每个瓶子去减不超过 $d$ 次，总共减 $B \times d$ 次，使得值最小。

这个过程可以用线段树维护，具体来说，对于一段牛奶数相同的区间，有 $\text{3}$ 种情况会使它停止减少：可以与下一段合并，$B \times d$ 用完了，最左边的减少次数达到 $d$（因为它一定是该区间减的次数最多的）。

而一个数最多被合并一次，最多达到减少 $d$ 次一次，$B \times d$ 最多用光一次，所以整体时间复杂度为 $O(n \log n)$。

upd：对于线段树上的操作，实际上可以用一个双端队列维护，对于每个位置记录时间戳，大于 $d$ 就弹出。这样子再与下一段合并，只要记录最后退出时队列中的元素应是多少，这样瓶颈就在于排序了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7,MAXN=1e5+10;
int n,A,B,a[MAXN],ans;
long long d;
struct Segment{
	struct tree{
		int val,add;
	}t[MAXN<<2];
	void build1(int l,int r,int rt)
	{
		t[rt].add=0;
		if(l==r)
		{
			t[rt].val=a[l];
			return;
		}
		int m=(l+r)>>1;
		build1(l,m,rt<<1);
		build1(m+1,r,rt<<1|1);
		t[rt].val=min(t[rt<<1].val,t[rt<<1|1].val);
	}
	void build2(int l,int r,int rt)
	{
		t[rt]={d,0};
		if(l==r) return;
		int m=(l+r)>>1;
		build2(l,m,rt<<1);
		build2(m+1,r,rt<<1|1);
	}
	void Pointupdate(int rt,int res)
	{
		t[rt].add+=res;
		t[rt].val-=res;
	}
	void pushdown(int rt)
	{
		if(t[rt].add)
		{
			Pointupdate(rt<<1,t[rt].add);
			Pointupdate(rt<<1|1,t[rt].add);
			t[rt].add=0;
		}
	}
	void update(int l,int r,int L,int R,int res,int rt)
	{
		if(L<=l && r<=R) return Pointupdate(rt,res);
		pushdown(rt);
		int m=(l+r)>>1;
		if(L<=m) update(l,m,L,R,res,rt<<1);
		if(m<R) update(m+1,r,L,R,res,rt<<1|1);
		t[rt].val=min(t[rt<<1].val,t[rt<<1|1].val);
	}
	int query(int l,int r,int L,int R,int rt)
	{
		if(L<=l && r<=R) return t[rt].val;
		pushdown(rt);
		int m=(l+r)>>1,ans=2e9;
		if(L<=m) ans=query(l,m,L,R,rt<<1);
		if(m<R) ans=min(ans,query(m+1,r,L,R,rt<<1|1));
		return ans;
	}
}T1,T2;

int main()
{
	cin>>n>>d>>A>>B;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1,greater<int>());
	for(int i=A+1;i<=n;i++) ans=(ans+1ll*a[i]*a[i]%mod)%mod;
	n=A;
	for(int i=1;i<=n;i++) a[i]+=d;
	T1.build1(1,n,1),T2.build2(1,n,1);
	d=d*B;
	int r,l=1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]==a[1]) r=i;
		else break;
	}
	while(d)
	{
		long long x=min(1ll*T1.query(1,n,l,r,1)-a[r+1],min(d/(r-l+1),1ll*T2.query(1,n,l,l,1)));
		d-=(r-l+1)*x;
		T2.update(1,n,l,r,x,1);
		T1.update(1,n,l,r,x,1);
		if(T1.query(1,n,l,r,1)!=a[r+1] && T2.query(1,n,l,l,1)>0)
		{
			if(d) T1.update(1,n,l,l+d-1,1,1);
			break;
		}
		else if(T1.query(1,n,l,r,1)!=a[r+1])
		{
			while(T2.query(1,n,l,l,1)==0 && l<=r) ++l;
			if(l>r)
			{
				r=l;
				for(int i=r+1;i<=n;i++)
				{
					if(a[i]==a[r]) ++r;
					else break;
				}
			}
		}
		else
		{
			r++;
			for(int i=r+1;i<=n;i++)
			{
				if(a[i]==a[r]) ++r;
				else break;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		int x=T1.query(1,n,i,i,1);
		ans=(ans+1ll*x*x%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：WWW_bilibili_com (赞：3)

题意略。

首先发现 John 一定选最大的 $A$ 瓶，Nhoj 一定选最大的 $B$ 瓶（因为它们增长量最大）。所以最后会发生变化的奶瓶只有前 $A$ 瓶（因为每次选取完后只有最大的 $A$ 瓶之中的 $A-B$ 瓶会增加一，所以这 $A$ 瓶一定还是最大的）。

由于Nhoj一定选最大的 $B$ 瓶，所以最终结果一定在可行范围内最接近与平均。所以我们可以视为前 $A$ 瓶的牛奶增加了 $D\times (A-B)$ 瓶，且最终数列前 $A$ 项接近于平均值。

考虑从大往小排序。从第 $A$ 瓶向第一瓶遍历，对于第 $i$ 项，如果剩余可分配点数大于 $(m_{i-1}-m_i)\times (A-i+1)$，则说明后面全部都改为 $m_{i-1}$ （这里先不修改），否则把剩下的点数平均分配给后面的奶瓶。

然后我们发现这个做法有一个漏洞，就是对于第 $i$ 个奶瓶，它里面最多装 $m_i+D$ 的奶，所以我们在遍历时进行特判，假如这一次最后一个瓶子即将增加的奶量超过了它的最大奶量，则直接将最后一个瓶子的奶量增加到最大值，然后把最后一个瓶子的标记向前移动一位，然后就做完了。

时间复杂度 $O(n)$，排序 $O(n\log n)$。

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read(){
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57){
        if(ch=='-')
            f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57)
        x=x*10+ch-48,ch=nc();
   	return x*f;
}
long long s[100001];
bool ff(const long long a,const long long b){
	return a>b;
}
int main(){
	int a,b,c,d,e;
	long long f,g;
	a=read();
	b=read();
	c=read();
	d=read();
	for(int v=1;v<=a;++v){
		s[v]=read();
	}
	sort(s+1,s+a+1,ff);
	f=(long long)(c-d)*b;
	s[0]=1145141919810;
	for(int v=c;v;--v){
		if((__int128)(s[v-1]-s[v])*(c-v+1)<=f){
			while(s[c]+b<s[v-1]){
				f=f-s[c]-b+s[v];
				s[c]=s[c]+b;
				--c;
			}
			f=f-(s[v-1]-s[v])*(c-v+1);
		}
		else{
			g=f/(c-v+1);
			if(s[v]+g>=s[c]+b){
				f=f-s[c]-b+s[v];
				s[c]=s[c]+b;
				--c;
				++v;
				continue;
			}
			f=f%(c-v+1);
			for(int var=v+1;var<=c;++var){
				s[var]=s[v]+g;
			}
			s[v]=s[v]+g;
			for(int var=v;f;++var,--f){
				++s[var];
			}
			break;
		}
	}
	f=0;
	for(int v=1;v<=a;++v){
		s[v]=s[v]%1000000007;
		f=(f+s[v]*s[v])%1000000007;
	}
	cout<<f;
	return 0;
}
```

---

## 作者：zhuweiqi (赞：3)

首先注意到每天添加牛奶的时候肯定选择现有奶量最多的 $A$ 瓶牛奶，同理可得偷牛奶也是偷奶量最多的 $B$ 瓶牛奶，而由于 $A>B$，所以注意到每天添加的牛奶瓶其实是同一批，也就是初始最多的 $A$ 瓶，然后发现偷牛奶的操作不太方便每天依次处理，所以直接转化成另一个问题：我先把这 $A$ 瓶牛奶加上 $D$（天数），然后一共可以偷 $B\times D$ 次，但每瓶不能偷超过 $D$ 次，这样我们就可以二分一个值，表示把所有奶量大于这个值的奶瓶要么偷到和这个值相等，要么偷 $D$ 次，显然最终取到的这个值（设为 $l$）的偷的次数应该刚好大于等于我需要偷的次数 $B\times D$，然后把多偷的奶量（设为 $c$）再加回去，即把恰好 $c$ 瓶原本被偷到 $l$ 的奶瓶的奶量加到 $l+1$，最后统计答案即可。

Code：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,d,A,B,tot,cnt;
int a[100002];
bool check(int ch){
	cnt=0;
	for(int i=1;i<=A;i++){
		if(a[i]-d>=ch) cnt+=d;
		else if(a[i]>=ch) cnt+=a[i]-ch;
	}
	return cnt>=tot;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>d>>A>>B;tot=d*B;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n,greater<int>());
	for(int i=1;i<=A;i++) a[i]+=d;
	int l=0,r=a[1]+d,mid;
	while(l<r){
		mid=l+r+1>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	check(l);
	int c=cnt-tot,ans=0;
	for(int i=1;i<=A;i++){
		if(a[i]-d>l) ans+=(a[i]-d)*(a[i]-d);
		else if(c) ans+=(l+1)*(l+1),c--;
		else ans+=min(l,a[i])*min(l,a[i]);
		ans%=mod;
	}
	for(int i=A+1;i<=n;i++) ans+=a[i]*a[i],ans%=mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

下称农夫约翰为 AA，农夫 Nhoj 为 BB。牛奶量被看作数。

首先每次 AA 和 BB 分别会对最大的若干个数操作，因为 $x^2-(x-1)^2=2x-1$ 是单调递增的。

不难发现 AA 操作的 $A$ 个数是不变的，BB 操作的 $B$ 个数是会变的，但也一定在这 $A$ 个数中。

先给每个数加上 $D$，只需求出每个数被 BB 操作的次数，相当于一共可以减 $BD$ 次且每个数至多被减 $D$ 次。

把 $2x-1$ 看作价值，因为是单调的所以不需要一个个选，只需求出前 $BD$ 大的价值和。

二分优化即可，时间复杂度 $O(n\log V)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef __int128 BI;
const BI inf=1e18;
const int N=1e5+5;
BI fr(){
	BI n=0;
	char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))n=n*10+c-48,c=getchar();
	return n;
}
int n,A,B;
BI D,a[N],ans;
bool check(BI x){
	BI cnt=0;
	rep(i,1,A){
		if(!a[i])continue;
		BI l=(max(a[i]-D,(BI)0)+1)*2-1,r=a[i]*2-1;
		if(x<=l)cnt+=D;
		else if(l<x&&x<=r)cnt+=(r-x)/2+1;
	}
	return cnt<=D*B;
}
BI cal(BI x){
	BI cnt=0;
	rep(i,1,A){
		if(!a[i])continue;
		BI l=(max(a[i]-D,(BI)0)+1)*2-1,r=a[i]*2-1;
		if(x<=l)cnt+=D;
		else if(l<x&&x<=r)cnt+=(r-x)/2+1;
	}
	cnt=D*B-cnt;
	BI res=0;
	rep(i,1,A){
		if(!a[i])continue;
		BI l=(max(a[i]-D,(BI)0)+1)*2-1,r=a[i]*2-1;
		if(x<=l)res+=(l+r)*D/2;
		else if(l<x&&x<=r){
			res+=(x+r)*((r-x)/2+1)/2;
			if(cnt)cnt--,res+=x-2;
		}
	}
	return res;
}
void slv(){
	n=fr(),D=fr(),A=fr(),B=fr();
	rep(i,1,n)a[i]=fr();
	sort(a+1,a+1+n,greater<BI>());
	rep(i,1,A)a[i]+=D;
	rep(i,1,n)ans+=a[i]*a[i];
	BI l=0,r=inf,mid,res=inf;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid*2+1))res=mid*2+1,r=mid-1;
		else l=mid+1;
	}
	ans-=cal(res);
	printf("%lld\n",(ll)(ans%(1000000007)));
}
void main(){
	int T=1;
//	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

首先 FJ 一定会给容量最大的 $A$ 个瓶子增加牛奶，JF 一定从容量最大的 $B$ 个瓶子中取牛奶。

发现最小的 $n-A$ 个元素的大小固定，这部分直接计算即可，后面不考虑这些元素。

现在的操作就是全局加 $1$ 和对前 $B$ 大的数减 $1$，即对最小的 $A-B$ 个数加 $1$。

这可以用类似合并连续段的方法做。

设我们要维护的段是 $[l,r]$。

首先，先从小到大排序，钦定第 $A-B+1$ 个元素为初始连续段（即 $[l,r]=[A-B+1,A-B+1]$）。

我们要求 $[l,r]$ 包含 $A-B+1$，且极差不大于 $1$。同时，如果极差为 $1$，则要求 $[l,r]$ 与 $[1,A-B]$ 有交。

考虑 $[l,r]$ 什么时候与左边/右边合并。

记 $v$ 为 $[l,r]$ 内的最小值，$m$ 为 $[l,r]$ 内有多少大于 $v$ 的数，$w$ 为与 $[1,A-B]$ 的交，$t$ 为当前经过了多长时间，$len$ 表示 $r-l+1$。

如果 $lt$ 天后可以往左合并，则 $lt$ 是最小的满足 $a_{l-1}+t+lt=\lfloor\dfrac{v\times len+m+w\times lt}{len}\rfloor$ 的 $lt$。变形得：

$$(len-w)lt+(a_{l-1}+t)len-v\times len-m\in[1-len,0]$$

$$\min lt=\lceil\dfrac{v\times len+m-(a_{l-1}+t)len+(1-len)}{len-w}\rceil$$

如果 $rt$ 天后可以往右合并，先判掉 $w=0$，此时 $rt$ 是最小的满足 $a_{r+1}=\lceil\dfrac{v\times len+m+w\times rt}{len}\rceil$ 的 $rt$。变形得：

$$w\times rt-a_{r+1}\times len+v\times len+m\in[1-len,0]$$

$$\min rt=\lceil\dfrac{a_{r+1}\times len-v\times len-m+(1-len)}{w}\rceil$$

然后模拟 $\min(lt,rt,d-t)$ 天（即更新上文的量），更新 $[l,r]$ 即可。

因为 $[l,r]$ 的移动的量级是 $O(n)$，因此上文复杂度正确。

最后分 $[1,l-1]$，$[l,r]$，$[r+1,n]$ 三种情况考虑即可。

时间复杂度 $O(n\log n)$，瓶颈在排序。

代码（可能会有细节问题，但现在可以 AC）：

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ldb long double 
#define bi __int128_t
using namespace std;
const int N=2e5+10;
const int mod=1e9+7;
int n,d,A,B;
int a[N],ans=0;
void Add(int &a,int b){
    a+=b;if(a>=mod) a-=mod;
}
void Sub(int &a,int b){
    a-=b;if(a<0) a+=mod;
}
int main(){
    //freopen("3.in","w",stdout);
    //cout<<"1000 100000"<<endl;
    //cout<<"555 222"<<endl;
    //for(int i=1;i<=1000;i++) cout<<rand()%1000000<<' ';
    //cout<<endl;
    //return 0;
    //freopen("3.in","r",stdin);
    //freopen("3.out","w",stdout);
    cin>>n>>d;cin>>A>>B;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n-A;i++) Add(ans,1ll*a[i]*a[i]%mod);
    for(int i=n-A+1;i<=n;i++){
        a[i-(n-A)]=a[i];
    }
    int cnt=A-B;n=A;
    int l=cnt+1,r=cnt+1;
    ll m=0,v=a[l],tag=0;
    while(d!=0){
        //if(clock()*1.0/CLOCKS_PER_SEC>1.0) break; 
        ll lt=1e18+10,rt=1e18+10;
        int av=cnt+1-l,len=r-l+1;
        if(l!=1){
            lt=((v-(a[l-1]+tag))*len+m-(len-1)+(len-av-1))/(len-av);
        }
        if(r!=n){
            if(av==0){
                if(m!=0&&v+1==a[r+1]) rt=0;
            }else{
                rt=((a[r+1]-v)*len-len+1-m+av-1)/av;
            }
        }
        //cout<<l<<' '<<r<<' '<<lt<<' '<<rt<<' '<<v<<' '<<a[l-1]+tag<<' '<<m<<endl;
        ll tim=min(lt,rt);
        if(d<tim){
            tag+=d;m+=1ll*d*av;
            v+=m/len;m%=len;
            d=0;
        }else{
            tag+=tim;m+=1ll*tim*av;
            v+=m/len;m%=len;
            d-=tim;
        }
        ll mn=v+m/len,mx=v+(m+len-1)/len;
        //cout<<mn<<' '<<mx<<' '<<m<<endl;
        while(l!=1&&a[l-1]+tag==mn){
            l--;
        }while(r!=n&&a[r+1]==mx){
            r++;if(mx!=mn) m++;
        }
    }
    for(int i=1;i<=n;i++){
        if(i<l){
            Add(ans,1ll*(a[i]+tag)*(a[i]+tag)%mod);
        }else if(i<=r){
            int o=0;
            if(m>0) m--,o=1;
            Add(ans,1ll*(v+o)*(v+o)%mod);
        }else{
            Add(ans,1ll*a[i]*a[i]%mod);
        }
    }cout<<ans<<endl;
	return 0;
}
```
（$w=0$ 貌似出了点问题，但好像不影响结果）

---

## 作者：gcx12012 (赞：0)

### 前言
有点牛的题，想了一中午才会。
### Solution
将序列 $a$ 排序好，对于 John 来说，最优策略是选择前 $A$ 大 $+1$；对于 Nhoj 来说，最优策略是选择前 $B$ 大 $-1$。因此我们可以将一次操作看作对一个单调不递减序列 $a$ 区间 $[N-A+1,N-B]$ 进行 $+1$ 操作。

$O(D\log N)$ 的做法是显然的，考虑一下如何推到正解。

首先我们考虑一种特殊情况：$A=N,B<A$ 且 $\forall 1\le i \le n,a_i=x$。

这时我们可以看作依次循环从 $N$ 到 $1$ 将每个数 $+1$，一次操作就相当于可以加 $A-B$ 个数。我们设具有这样区间加规律的区间为 $[L,R]$。

然后对一般情况进行打表观察，这里假定 $a$ 是一直单调不递减的。我们发现：对于 $\forall 1\le i \le N-A$ 的 $a_i$ 一直保持不变，且满足规律的最长 $[L,R]$ 区间满足：$0\le a_R-a_L\le 1$。然后我们发现，初始 $L=R=N-B$ 时，左右端点会时不时往外扩散，直到 $L=N-A+1,R=N$ 时或操作次数用完时才停止。当 $a_R-a_L=1$ 时左端点会移动，当 $a_{R+1}=a_R$ 时右端点会移动。

因此我们直接考虑移动一次端点所需的操作次数对整个操作序列的影响，直接维护这个过程即可，移动一次端点所需的操作次数可以通过二分解决，然后拿个树状数组维护当前的 $a_i$ 即可。

这样的时间复杂度是 $O(N\log^2 N)$ 的，完全可以通过。但是细节多，写的时候保持脑子清醒。
```
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 200010
#define For(i,a,b) for(int i=a;i<=b;++i)
#define Rof(i,a,b) for(int i=a;i>=b;--i)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r 
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int >
#define fi first
#define se second

using namespace std;
const ll mod=1e9+7;
ll a[N];
ll n,q,A,B;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
ll c[N];
void add(int x,ll k){
	while(x<=n){
		c[x]+=k;
		x+=(x&(-x));
	}
}
ll qry(int x){
	ll p=0;
	while(x){
		p+=c[x];
		x-=(x&(-x));
	}
	return p;
}

int main()
{
	n=read(),q=read(),A=read(),B=read();
	For(i,1,n) a[i]=read();
	sort(a+1,a+n+1);
	For(i,1,n) add(i,a[i]),add(i+1,-a[i]);
	ll L=n-B,R=n-B,lst=0,len=1,gai=0;
	while(lst<q){
		ll nowadd=(n-B)-L+1;
		ll tiao1=1e15,tiao2=1e15;
		if(R<n){
			ll l=0,r=1e13;
			while(l<=r){
				ll mid=(l+r)/2;
				if(qry(R)+(gai==0?mid*nowadd+len-1:mid*nowadd+gai-1)/len>=a[R+1]) tiao1=mid,r=mid-1;
				else l=mid+1;
			}
		}
		if(L>n-A+1){
			ll l=0,r=1e13;
			while(l<=r){
				ll mid=(l+r)/2;
				if(qry(L-1)+mid>=qry(R)+(gai==0?mid*nowadd+len-1:mid*nowadd+gai-1)/len-1 && len!=1) tiao2=mid,r=mid-1;
				else l=mid+1;
			}
		}
		ll tim;
		if(lst+min(tiao1,tiao2)>=q) tim=q-lst;
		else tim=min(tiao1,tiao2);
		add(n-A+1,tim);
		add(L,-tim);
		ll chu=tim*nowadd/len,yu=tim*nowadd%len;
		add(L,chu),add(R+1,-chu);
		add(max(L,R-gai-yu+1),1),add(R-gai+1,-1);
		if(len-gai-yu<0) add(R-(yu-(len-gai))+1,1),add(R+1,-1);
		gai=(gai+tim*nowadd)%len;
		lst+=tim;
		if(lst==q) break;
		if(tiao1<=tiao2) R++,len++,gai=(gai==0?0:gai+1);
		else{
			L--;
			if(!gai){
				if(qry(L)==qry(L+1)) gai=0;
				else gai=len;
			}
			len++;
		}
		/*
		For(i,1,n) cout<<qry(i)<<' ';
		cout<<endl;
		cout<<lst<<endl;
		cout<<tiao1<<' '<<tiao2<<endl;
		cout<<L<<' '<<R<<endl;
		cout<<gai<<endl;
		*/
	}
	ll ans=0;
	For(i,1,n){
		ll now=qry(i)%mod;
		ans=(ans+now*now%mod)%mod;
	}
	cout<<ans;
	return 0; 
}
/*
7 100 5 2
1 3 10 29 38 60 70
51421

4 100 3 1
2 3 10 45
22192
*/
```

---

## 作者：Yao_yx (赞：0)

对于一个正整数，若其越大其平方增长速度就越快，所以 John 每次肯定选择最大的 $A$ 个加一，又因为每操作两轮，每个数相对于上一次是单调不减的，所以最大的 $A$ 个是固定的。

考虑 Nhoj ，同理每次选择最大的 $B$ 个减一，但是动态维护前 $B$ 大值很难维护，所以考虑先将刚开始最大的 $A$ 个都加 $D$，然后再减 $D$ 次，每次减 $B$ 个。而这也就相当于每次减一个，减 $B\times D$ 次，每个最多减 $D$ 次。

考虑每次将最大值推平为次大值，次大值再推平为第三大值，以此类推。使用优先队列维护该操作。队列外记录当前推平到的数即其个数（因为有许多相同元素）。队列中每个元素记录两个值 $x$ 和 $t$ ，其中 $x$ 为当前推平到的数，$t$ 为 $0$ 表示加入一个数，为 $1$ 表是删除一个数（因为每个数最多减 $D$ 次）。按 $x$ 为第一关键字， $t$ 为第二关键字从大到小排序（因为从大往下推平）。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5 + 10;
const int mod = 1e9 + 7;

int n, d, A, B, a[MAXN];

struct node{ int x, t; };
bool operator < (node p, node q){ return p.x == q.x ? p.t < q.t : p.x < q.x; }
priority_queue<node> q;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> d >> A >> B; for(int i = 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a + n + 1); for(int i = n - A + 1; i <= n; ++i) a[i] += d, q.push({a[i] - d, 1}), q.push({a[i], 0});
	int cnt = 1, val = a[n], pos = n, tmp = B * d; q.pop();
	while(!q.empty()){
		int x = q.top().x, t = q.top().t; q.pop();
		if(cnt * (val - x) >= tmp){
			int z = tmp / cnt; tmp %= cnt;
			val -= z; break;
		}
		tmp -= cnt * (val - x), val = x;
		(t ? cnt-- : (cnt++, pos--));
	}
	int ans = 0; for(int i = 1; i < pos; ++i) (ans += a[i] * a[i] % mod) %= mod;
	(ans += (val - 1) * (val - 1) % mod * tmp % mod) %= mod;
	(ans += val * val % mod * (cnt - tmp) % mod) %= mod;
	for(int i = pos + cnt; i <= n; ++i) (ans += (a[i] - d) * (a[i] - d) % mod) %= mod; cout << ans;
	
	return 0;
}
```

---

