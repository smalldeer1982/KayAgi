# Adilbek and the Watering System

## 题目描述

Adilbek has to water his garden. He is going to do it with the help of a complex watering system: he only has to deliver water to it, and the mechanisms will do all the remaining job.

The watering system consumes one liter of water per minute (if there is no water, it is not working). It can hold no more than $ c $ liters. Adilbek has already poured $ c_0 $ liters of water into the system. He is going to start watering the garden right now and water it for $ m $ minutes, and the watering system should contain at least one liter of water at the beginning of the $ i $ -th minute (for every $ i $ from $ 0 $ to $ m - 1 $ ).

Now Adilbek wonders what he will do if the watering system runs out of water. He called $ n $ his friends and asked them if they are going to bring some water. The $ i $ -th friend answered that he can bring no more than $ a_i $ liters of water; he will arrive at the beginning of the $ t_i $ -th minute and pour all the water he has into the system (if the system cannot hold such amount of water, the excess water is poured out); and then he will ask Adilbek to pay $ b_i $ dollars for each liter of water he has brought. You may assume that if a friend arrives at the beginning of the $ t_i $ -th minute and the system runs out of water at the beginning of the same minute, the friend pours his water fast enough so that the system does not stop working.

Of course, Adilbek does not want to pay his friends, but he has to water the garden. So he has to tell his friends how much water should they bring. Formally, Adilbek wants to choose $ n $ integers $ k_1 $ , $ k_2 $ , ..., $ k_n $ in such a way that:

- if each friend $ i $ brings exactly $ k_i $ liters of water, then the watering system works during the whole time required to water the garden;
- the sum $ \sum\limits_{i = 1}^{n} k_i b_i $ is minimum possible.

Help Adilbek to determine the minimum amount he has to pay his friends or determine that Adilbek not able to water the garden for $ m $ minutes.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
4
1 5 4 2
2 4 2
0 4 5 4
2 5 3 1
1 2 4
3 1 3
2 3 5 1
2 1 1
1 4 3
```

### 输出

```
6
0
-1
4
```

# 题解

## 作者：Kelin (赞：3)

## 题意
一个容量为$c$升的浇水机器，一开始有$c0$升水，它每分钟会消耗$1$升水

有$n$个人，第$i$个人会在第$t_i$分钟至多带$a_i$升水过来并把他带的水一次性倒进机器，每升水卖$b_i$元

问要使得抽水机撑到第$m$分钟不断水（即剩余水量恒$\ge0$），最少的花费是多少；如果撑不到，输出$-1$

$0\le n\le5\times10^5,2\le m\le10^9,1\le c0\le c\le10^9$

---

## 题解
考虑贪心

先把所有人按照按照时间排序

对于第$i$个人，$\Delta t_i=t_i-t_{i-1}$，我们可以把机器里剩余的水按价格从低到高地用掉，并记录答案

对于每一个人我们把他带的水全部倒进去，直到满了为止，但是先不计费

如果机器里最贵的水价格$\gt b_i$，那么我们就可以把最贵的水倒出去一些，再把第$i$个人的水再倒进去一些（如果还有的话），就相当于那个人来的时候少带了一些水，而且这样也不会影响机器撑到$t_i$

可以发现这样的花费一定是最小的

具体实现可以设$map<int,int>q$，其中$q[a]$表示机器中剩余的价格为$a$的水有多少升

用水的时候每次取出最便宜的水（即$q.begin().second$）来更新答案，用完后就删除

加水的时候取出最贵的水（即$q.rbegin().first$）和当前的$b_i$比较，并计算要替换掉多少，完全替换了就删除

时间复杂度$O(n\log n)$

```cpp
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
	char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
	while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
const int N=5e5+5,M=N<<1;
typedef int arr[N];
typedef long long ll;
struct Water{
	int t,a,b;
	inline void in(){sd(t),sd(a),sd(b);}
	bool operator<(const Water&y)const{return t==y.t?(a==y.a?b<y.b:a<y.a):t<y.t;}
}a[N];
int n,m,c,res;map<int,int>q;
inline ll sol(){
	ll ans=0;
	sd(n),sd(m),sd(c),sd(res);
	fp(i,1,n)a[i].in();
	a[++n]=(Water){m,0,0};
	sort(a+1,a+n+1);
	q.clear();q[0]=res;
	fp(i,1,n){
		int DeltaT=a[i].t-a[i-1].t;
		if(DeltaT>c)return -1;
		while(!q.empty()&&DeltaT>0){
			int W=min(DeltaT,q.begin()->second);
			ans+=(ll)q.begin()->first*W;
			q.begin()->second-=W;DeltaT-=W;res-=W;
			if(!q.begin()->second)q.erase(q.begin());
		}
		if(DeltaT)return -1;
		int Cnt=a[i].a,Cost=a[i].b,add=min(c-res,Cnt);
		res+=add;
		while(!q.empty()&&add<Cnt&&Cost<q.rbegin()->first)
			if(Cnt-add>=q.rbegin()->second){
				add+=q.rbegin()->second;
				q.erase(--q.end());
			}else{
				q.rbegin()->second-=Cnt-add;
				add=Cnt;
			}
		q[Cost]+=add;
	}
	return ans;

}
int main(){
	#ifndef ONLINE_JUDGE
		file("s");
	#endif
	int q;sd(q);
	while(q--)printf("%lld\n",sol());
return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑到后面的人不能给前面的需求送水，我们从前往后考虑。

考虑先设计一个朴素贪心，我们就让每个人把水加满然后往后跑。

这个算法问题在于一个人加的水后面可能会被另一个价格更低的人加的水替换掉。

于是考虑反悔贪心，不妨维护一个水量与价格构成的集合，从前往后考虑，每考虑到一个人就把他的水全部加进去，假若水量和大于 $c$ 就去把价格贵的弹出，因为其没法留到后面且最劣，需要水的时候就从小往大取，因为先取小的不会让当前价格低的水浪费并且也能给后面的水腾出位置，这个过程可以使用 set 在 $O(n \log n)$ 的时间复杂度内维护出来。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;
const int inf = 1e9;
int n,m,c,c0;
multiset< pair<int,int> > S;
int sum;
int t[maxn],a[maxn],b[maxn];
int p[maxn];
bool cmp(int x,int y){
    return t[x]<t[y];
}
int ans;
bool cost(int cst){
    int x=cst;
    while(x>0){
        if(S.size()==0) return false;
        pair<int,int> tp=(*S.begin());
        S.erase(S.find(tp));
        sum-=tp.second;
        int flow=min(tp.second,x);
        tp.second-=flow,x-=flow;
        ans+=flow*tp.first;
        if(tp.second>0) S.insert(tp),sum+=tp.second;
    }
    return true;
}
void ins(int A,int B){
    S.insert(make_pair(B,A));
    sum+=A;
    while(sum>c){
        pair<int,int> tp=(*S.rbegin());
        sum-=tp.second;
        S.erase(S.find(tp));
        if(sum<c){
            tp.second=c-sum;
            sum+=tp.second;
            S.insert(tp);
        }
    }
}
set<int> T;
void work(){
    sum=0;
    ans=0;
    T.clear();
    T.insert(0);
    S.clear();
    cin>>n>>m>>c>>c0;
    for(int i=1;i<=n;i++){
        cin>>t[i]>>a[i]>>b[i];
        p[i]=i;
        T.insert(t[i]);
    }
    T.insert(m);
    sort(p+1,p+n+1,cmp);
    int now=0;
    ins(c0,0);
    for(int x:T){
        if(x==m) break;
        while(now<n&&t[p[now+1]]==x) now++,ins(a[p[now]],b[p[now]]);
        if(cost((*T.upper_bound(x))-x)==false){
            cout<<"-1\n";
            return ;
        }
    }
    cout<<ans<<'\n';
    return ;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
2 3 5 1
2 1 1
1 4 3
*/
```

---

## 作者：bruhify (赞：0)

题解都是反悔贪心，来一篇本质相同，但是推导过程支持卸载大脑的凸优化 dp。我们凸批是这样的！！

初始水量可以看作在 $0$ 时刻有一个水量为 $c_0$，单位代价为 $0$ 的人。从左到右考虑第 $i$ 个人以及他到下一个人之间的时间段，维护 $dp_j$ 表示当前系统里还有 $j$ 单位水的最小代价。那么考虑第 $i$ 个人，有 $dp_j+b_ik \rightarrow dp_{j+k}$，其中 $k \in [0,a_i], j+k \leq c$。再考虑这个人后面跟着的时间段，有一个整体平移 $dp_j \rightarrow dp_{j-(t_{i+1}-t_i)}$。

凸性证明如下：第二类操作执行了一个整体平移，再把 $x$ 坐标 $<0$ 的部分删掉，不会影响凸性，所以只考虑第一类操作。采用归纳法，初始 dp 点集为空集，显然是凸的。假设转移前，dp 点集是凸的，注意可以把这个操作转化成 $dp_j$ 和一个线段上的点集 $\{(x,b_ix)|x \in [0,a_i]\}$ 做闵可夫斯基和，再截取 $x$ 坐标 $\in [0,c]$ 的部分。线段显然是凸的，所以闵可夫斯基和也是凸的。证毕。

上述证明也提供了一个很好写的维护方法：用一个 set 维护当前 dp 的差分，再开一个 $dp_0$ 表示 $x=0$ 的实际 dp 值。由于值域太大，可以存成 $(b_i,a_i)$ 表示有 $a_i$ 个差分为 $b_i$ 的位置。考虑人的时候，只需要向 set 中插入一个 $(b_i,a_i)$，再删除最大斜率直到点集大小 $\leq c$。考虑时间段时，删除恰好 $t_{i+1}-t_i$ 个元素，将他们的斜率累计入 $dp_0$。最终答案就是 $dp_0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=0x3f3f3f3f;

int T,n;

ll lim;

struct Node {
	ll t,a,b;
	bool operator<(const Node &c) const {
		return t<c.t;
	}
}p[500005];

int read() {
	int s=0;
	char ch=getchar();
	while(ch<'0' || ch>'9') ch=getchar();
	while(ch>='0' && ch<='9') s=s*10+ch-'0',ch=getchar();
	return s;
}

multiset<pair<ll,ll> > st;

int main() {
	T=read();
	while(T--) {
		n=read(),p[n+1].t=read(),lim=read(),p[0].a=read();
		p[n+1].a=0,p[n+1].b=inf;
		for(int i=1;i<=n;i++) p[i].t=read(),p[i].a=read(),p[i].b=read();
		sort(p+1,p+n+1),st.clear();
		ll ans=0,siz=0;
		for(int i=0;i<=n;i++) {
			st.insert({p[i].b,p[i].a}),siz+=p[i].a;
			while(siz>lim) {
				auto x=*st.rbegin();
				st.erase(prev(st.end()));
				if(siz-x.second>=lim) siz-=x.second;
				else x.second-=(siz-lim),siz=lim,st.insert(x);
			}
			if(siz<p[i+1].t-p[i].t) {
				ans=-1;
				break;
			}
			ll rem=p[i+1].t-p[i].t;
			siz-=rem;
			while(rem) {
				auto x=*st.begin();
				st.erase(st.begin());
				if(x.second<=rem) ans+=x.first*x.second,rem-=x.second;
				else ans+=x.first*rem,x.second-=rem,rem=0,st.insert(x);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

---

## 作者：Exp10re (赞：0)

贪心好题。

CF 随机到这题的时候带了数据结构的标签，事实证明本题更侧重于贪心。

## 解题思路

考虑先将所有人按照时间排序，方便我们模拟浇水。

然后采用如下策略贪心：

- 轮到第 $i$ 个人的时候，距离上一个人已经过去了 $\Delta t=t_i-t_{i-1}$ 的时间，消耗了 $\Delta t$ 升水。
- 我们查看水库里面的水，优先消耗掉最便宜的水，然后计算这些水的价格之和。（水的价格取决于送水的人的定价，我们假定每一升水都标记了送水人定价的价格）
- 如果剩余水量不够 $\Delta t$，我们认为无解。
- 然后将第 $i$ 个人送的水全部加入水库中，这个时候很可能容量不够，那么我们就倒出里面比这个人的水贵的水，直到水库有足够空间使得第 $i$ 个人送的水能加进去，或者水库里面没有比这个人贵的水。

考虑正确性：

- 按照 $t$ 排序表明了在任意时间都有水的正确性。
- 第 $4$ 步的反悔操作可以视为在购买的时候就已经不要倒掉的水的钱了。
- 注意到操作本质上就是买下所有的水，然后贪心的倒掉多余的水，有解的正确性显然，反悔操作则保证了最优性。

具体实现上，用 map 存储价格为 $i$ 的水剩余量，用 multiset 维护价格的最大值和最小值以及插入删除操作。（当然如果您愿意可以用平衡树或者权值线段树）

再具体实现请参考代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=1010010;
map<long long,long long> res;
multiset<long long> val;
struct fri
{
	long long t,val,cnt;
};
fri f[MAXN];
bool cmp(fri ta,fri tb)
{
	return ta.t<tb.t;
}
long long n,m,C,r,ans,Res;
bool spent(long long x)
{
	long long t;
	while(x>0)
	{
		t=*val.begin();
		if(res[t]>x)
		{
			res[t]-=x;
			Res-=x;
			ans+=t*x;
			x=0;
		}
		else
		{
			x-=res[t];
			Res-=res[t];
			ans+=res[t]*t;
			res[t]=0;
			val.erase(val.begin());
		}
		if((val.empty()||Res<=0)&&x>=1)
		{
			return false;
		}
	}
	return true;
}
void add(long long i)
{
	long long c=f[i].cnt,v=f[i].val,t;
	val.insert(v);
	if(Res<C)
	{
		if(Res+c<=C)
		{
			res[v]+=c;
			Res+=c;
			return;
		}
		else
		{
			c-=C-Res;
			res[v]+=C-Res;
			Res=C;
		}
	}
	while(c>0)
	{
		t=*val.rbegin();
		if(t<=v)
		{
			break;
		}
		else
		{
			if(res[t]>c)
			{
				res[t]-=c;
				res[v]+=c;
				c=0;
			}
			else
			{
				c-=res[t];
				res[v]+=res[t];
				res[t]=0;
				val.erase(*val.rbegin());
			}
		}
	}
	if(res[v]==0)
	{
		val.erase(v);
	}
	return;
}
void work()
{
	ans=0;
	long long i,j,T=0;
	res.clear();
	val.clear();
	scanf("%lld%lld%lld%lld",&n,&m,&C,&r);
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&f[i].t,&f[i].cnt,&f[i].val);
	}
	sort(f+1,f+1+n,cmp);
	val.insert(0);
	res[0]+=r;
	Res=r;
	for(i=1;i<=n;i++)
	{
		if(!spent(f[i].t-T))
		{
			printf("-1\n");
			return;
		}
		else
		{
			add(i);
		}
		T=f[i].t;
	}
	if(!spent(m-T))
	{
		printf("-1\n");
		return;
	}
	else
	{
		printf("%lld\n",ans);
	}
	return;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

