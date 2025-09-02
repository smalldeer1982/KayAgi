# Carrots for Rabbits

## 题目描述

There are some rabbits in Singapore Zoo. To feed them, Zookeeper bought $ n $ carrots with lengths $ a_1, a_2, a_3, \ldots, a_n $ . However, rabbits are very fertile and multiply very quickly. Zookeeper now has $ k $ rabbits and does not have enough carrots to feed all of them. To solve this problem, Zookeeper decided to cut the carrots into $ k $ pieces. For some reason, all resulting carrot lengths must be positive integers.

Big carrots are very difficult for rabbits to handle and eat, so the time needed to eat a carrot of size $ x $ is $ x^2 $ .

Help Zookeeper split his carrots while minimizing the sum of time taken for rabbits to eat the carrots.

## 说明/提示

For the first test, the optimal sizes of carrots are $ \{1,1,1,2,2,2\} $ . The time taken is $ 1^2+1^2+1^2+2^2+2^2+2^2=15 $

For the second test, the optimal sizes of carrots are $ \{4,5,5,5\} $ . The time taken is $ 4^2+5^2+5^2+5^2=91 $ .

## 样例 #1

### 输入

```
3 6
5 3 1```

### 输出

```
15```

## 样例 #2

### 输入

```
1 4
19```

### 输出

```
91```

# 题解

## 作者：Qiaoqia (赞：10)

这题的其它题解都没有去证明保证贪心正确性的关键性质 $f(l, p) - f(l, p-1) \le f(l, p+1) - f(l, p)$，而如果没有这个性质，直接取最大的贪心无疑是错误的，所以我来补充一下证明。

首先最小的 $f(l, p)$ 肯定要求将 $l$ 分配成若干段不超过 $1$ 的，即尽可能平均分配，因为若存在两段 $x > y + 1$ 那么把 $x$ 变成 $x-1$，$y$ 变成 $y+1$ 肯定更优，这样不断调整即可使最后剩下的段极差不超过 $1$。

然后对式子进行移项，$f(l, p) - f(l, p-1) \le f(l, p+1) - f(l, p) \Rightarrow f(l, p+1) + f(l, p-1) \ge 2f(l, p)$，其中的 $2f(l, p) = f(2l, 2r)$ 因为把两边一样的已经不超过 $1$ 的合并起来肯定极差还是不会超过 $1$，但是如果合并 $f(l, p-1)$ 和 $f(l, p+1)$ 就不一定了，可能会出现极差为 $2$ 的，因此证毕。

有了这个结论意味着不可能出现一行前面很小突然就变得很大的情况（因为只会更小），于是贪心就对了。

```cpp
std::priority_queue<std::array<long long, 3>> q;
void main() {
	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	auto sqr = [](long long x) { return x * x; };
	auto f = [&](long long l, long long p) { 
        l = a[l];
        return sqr(l/p)*(p-l%p) + (l%p)*sqr(l/p+1);
    };
	for (int i = 1; i <= n; i++) 
	    q.push({f(i, 1)-f(i, 2), i, 2}), ans += f(i, 1);
	for (int i = 1; i <= k - n; i++) {
	    auto c = q.top(); q.pop();
	    ans -= c[0];
	    if (c[2] < a[c[1]])
	        q.push({f(c[1], c[2])-f(c[1], c[2]+1), c[1], c[2]+1});
	}
	std::cout << ans;
}
```

---

## 作者：tommymio (赞：8)

比赛的时候想了两种假做法：

- 二分

- 弄一个堆，暴力砍两段，再扔进去。

这两种做法直接写都非常假，直接二分会导致多余步数不好处理，而第二种做法不满足均值不等式显然是错的，这是一个假贪心。

但第二种做法启发我们，每次取一种能够对答案减少量最大的方案显然是可行的。并且样例 $2$ 提醒了我们对于一个给定长度 $x$，切割段数 $y$，是可以在 $O(1)$ 时间复杂度内计算出它的最小代价的，不妨设这个最小代价为 $f(x,y)$。

这个贪心的正确性基于 $f(x,y)-f(x,y+1)$ 单调不增。

那么问题就简单了很多，使用贪心反悔的思想，初始时将所有 $a_i$ 扔进去，并将切割段数设为 $1$。以后每次取出切割段数 $+1$ 能够取到答案最大减少量的 $a_i$，试图扩展并统计贡献即可。

```cpp
#include<cstdio>
#include<cmath>
#include<queue>
#include<functional>
#define pr std::pair<ll,int> 
#define pr2 std::pair<ll,pr>
#define mk_pr(x,y) std::make_pair(x,y)
typedef long long ll;
int a[1000005];
std::priority_queue<pr2> Q;
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
ll f(int x,int y) {return (ll)(x/y)*(ll)(x/y)*(y-x%y)+(x%y)*(ll)(1+x/y)*(ll)(1+x/y);}
int main() {
	int n=read(),k=read(); ll ans=0;//m=k-n;
	for(register int i=1,x;i<=n;++i) {x=read(); ans+=(ll)x*(ll)x; Q.push(mk_pr(f(x,1)-f(x,2),mk_pr(x,2)));}
	for(register int i=1;i<=k-n;++i) {
		pr2 now=Q.top(); Q.pop();
		ans-=now.first; int x=now.second.first,y=now.second.second;
		Q.push(mk_pr(f(x,y)-f(x,y+1),mk_pr(x,y+1)));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：gyh20 (赞：3)

堆贪心。

首先，假如只有一个数，要分成 $k$ 段，那么尽量平均一定优。

先把原题转化为：执行 $k-n$ 次操作。

对于每一个数，初始视为执行一次操作，每多进行一次操作相当于让一个数多执行一次操作，由于互不影响，每次堆贪心找出让代价变化最大的即可。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,k,t,a[200002],b[200002],ans,sum[200002],s;
inline int calc(re int x,re int y){
	if(y>=x)return x;
	re int xx=((x-1)/y),num=x-xx*y,num1=y-num;
	return num*(xx+1)*(xx+1)+num1*xx*xx;
}
struct node{
	int val,tim;
	bool operator <(const node &x)const{
		return calc(val,tim)-calc(val,tim+1)<calc(x.val,x.tim)-calc(x.val,x.tim+1);
	}
};
priority_queue<node>q;
signed main(){
	n=read(),k=read();k-=n;
	for(re int i=1;i<=n;++i)a[i]=read(),q.push((node){a[i],1}),ans+=a[i]*a[i];
	for(re int i=1;i<=k;++i){
		node x=q.top();q.pop();
		ans-=calc(x.val,x.tim)-calc(x.val,x.tim+1);
		q.push((node){x.val,x.tim+1});
	}
	printf("%lld",ans);
}
```


---

## 作者：EricQian (赞：1)

[CF1428E Carrots for Rabbits](https://www.luogu.com.cn/problem/CF1428E)

### 题意：

有 $n$ 个萝卜，每个萝卜的初始大小为 $a_i$ 。现在要把这些萝卜切为为 $k$ 个。吃每一个萝卜的时间为这个萝卜的大小的平方，求吃完所有萝卜的最小时间，即 $\sum_{i=1}^{k}{a_i^2}$ 最小 。求出最小值 。

### 题解：

+ 二分是错的 。

+ 贪心切两段是错的 。

**正解：**

令 $f(i,cnt)$ 为把第 $i$ 个萝卜分为 $cnt$ 个后吃完的最少时间，则初始答案为 $\sum_{i=1}^{n}{f(i,1)}$ 。

维护一个小根堆，存的值为 $f(i,cnt)-f(i,cnt+1)$ ，每一次取出堆顶，将堆顶的萝卜再切一段下来，并塞回堆中 。

在这一次操作中，答案减小了 $f(i,cnt)-f(i,cnt+1)$ ，且这个值在这一次切割操作中是最优的，所以答案是正确的。

以上操作进行 $k-n$ 次 。

最终的答案为初始答案减去每一次取出堆顶后对答案减小的值。

大致代码：

```cpp
int n,k,a[Maxn];
ll ans;
ll f(ll sum,ll cnt)
{
	 return (sum%cnt)*(sum/cnt+1ll)*(sum/cnt+1ll)+(cnt-(sum%cnt))*(sum/cnt)*(sum/cnt);
}
struct Data
{
	 ll sum,cnt;
	 bool friend operator < (Data x,Data y)
	 {
	 	 return (f(x.sum,x.cnt)-f(x.sum,x.cnt+1ll))<(f(y.sum,y.cnt)-f(y.sum,y.cnt+1ll));
	 }
};
priority_queue<Data> q;
// main
n=rd(),k=rd();
for(int i=1;i<=n;i++) a[i]=rd(),q.push((Data){1ll*a[i],1ll}),ans+=1ll*a[i]*a[i];
for(int i=1;i<=k-n;i++)
{
	 Data cur=q.top(); q.pop();
	 ans-=(f(cur.sum,cur.cnt)-f(cur.sum,cur.cnt+1ll)),cur.cnt+=1ll;
	 q.push(cur);
}
printf("%lld\n",ans);
```

---

## 作者：vectorwyx (赞：1)

纪念一下第一道E题，~~尽管是赛后A的~~


------------
令 $f(x,y)$ 表示把数 $x$ 分成 $y$ 份所能得到的最小平方和。根据均值不等式，$f(x,y)=(\frac{n}{k})^{2}(k-(n\mod k))+(n\mod k)(\frac{n}{k}+1)^{2}$

有一个比较暴力的想法就是算出所有的 $f(x,y)(y \le k)$ 然后直接背包。但显然过不了。

考虑优化，由于每切一道相当于多分裂出一份，因此我们可以把切一次作为物品的代价，前后平方和的差值作为价值，也就是令 $f(a_{x},y)-f(a_{x},y+1)$ 作为物品 $(x,y)$ 的价值（$x\le n,y \le k$）。这样问题就转化为了物品的代价均为1，选 $n-k$ 个物品使得价值最大。

但 $x$ 相同的物品之间是有依赖关系的：如果我们要选物品 $(x,y)$，我们必须先把物品 $(x,z),z<y$ 都选上。又因为同一行的物品的价值不上升，因此我们可以使用贪心策略来解决这个问题。每一次都选择能选的物品中价值最大的那个，然后把它的后继物品加入能选择的物品中，这个过程可以用堆来维护。时间复杂度为 $O(n\log n)$。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

ll S(int n,int k){//把数n分成k份的最小平方和 
	int x=n/k,y=n%k;
	return 1ll*x*x*(k-y)+1ll*y*(x+1)*(x+1);//通过均值不等式推出来的式子 
}

struct Node{
	ll val,sum;//val是再砍一刀的价值，sum是目前的平方和 
	int num,cut;//num是原数，cut是切了多少刀 
	Node(){}
	Node(int x){//初始化 
		cut=0;
		num=x;
		sum=1ll*x*x;
		val=sum-S(x,2);
	}
	void change(){//求它的后继物品 
		sum=sum-val;
		cut++;
		val=sum-S(num,cut+2); 
	} 
	bool operator<(const Node &x) const{
		return val<x.val;
	}
};
priority_queue<Node> q;
const int maxn=1e5+5;
int a[maxn];

int main(){
	int n=read(),k=read();
	ll ans=0;
	fo(i,1,n) a[i]=read(),ans+=1ll*a[i]*a[i];
	fo(i,1,n) q.push(Node(a[i])); 
	int cnt=n;
	while(cnt<k){
		Node t=q.top();q.pop();
		++cnt;
		ans-=t.val;
		t.change();
		q.push(t);//将它的后继物品放到堆中 
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：_ZHONGZIJIE0608_ (赞：0)

有 $N$ 根棒子，第 $i$ 根棒子长度为 $A_i$。现在要把这些棒子砍成 $M$ 根短棒，短棒的长度要求为正整数。砍棒子是要花钱的。你如果砍出一根长度为 $L$ 的棒子，需要支付 $L^2$ 元。问你砍 $M$ 根棒子所需要的最小费用。

>钱给少了是砍不出 $M$ 根棒子的，而钱给多了就可以砍出。所以这里可以二分答案。
>
>接下来计算砍 $M$ 根棒子的最省钱的方案。
* * *
等等，好像不能二分?

发现可行性不好维护。多余步数不好处理。

这不像是能 DP 的复杂度，考虑挖掘性质搞贪心。

令 $f(l,k)$ 为把长 $l$ 的棒子砍成 $k$ 段的最少的费用。

读一读样例，加上小学数学知识，我们发现砍完之后最好有两种不同长度的段数 $k_1,k_2$ 与一个长度 $w$，且 $k_1+k_2=k,k_1w+k_2(w+1)=l$。要求最小化 $k_1 w^2+k_2(w+1)^2$。

显然有 $w=\left\lfloor \frac{l}{k} \right \rfloor,k_2=l \bmod k$。于是我们 $O(1)$ 计算 $f(l,k)$。

考虑如下的贪心算法。首先考虑没有削减。然后一段一段地砍。当我们增加额外的段数时优先队列维护哪根棒子能使成本降低最大。对于长度为 $l$ 的棒子，额外切一次降低成本为 $f(l,k)-f(l,k+1)$。

可以证明（当然也能感性理解），$f(l,k-1)-f(l,k)\ge f(l,k)-f(l,k+1)$。所以切得越多降低成本越少。那么方案就没有后效性了，因为后面的不优。

那么只要用优先队列维护哪一根棒子成本降低最大，在它上面维护成本。

具体来讲，首先只有 $M-N$ 个棒子是砍完后新增的（之前的棒子又不会消失）。所以初始答案是 $\sum_{i=1}^N A_{i}^2$，只执行 $M-N$ 次操作。按照多砍一刀能减少的成本从大到小排序（优先队列）。队列里记录每个棒子的长度和当前砍的段数。取出队头后直接减少成本。

由于每次有且仅有一根新增棒子，最终答案就是 $M$ 根棒子的答案。

还是要注意“新增棒子数”的性质，不要写一堆乱七八糟的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,K,a[N],ans=0;
int f(int l,int k){
	int k2=l%k;int k1=k-k2;int w=l/k;
	return  k1*w*w+k2*(w+1)*(w+1);
}
struct node{
	int l,k;
	bool operator <(const node &o)const{
		return f(l,k)-f(l,k+1)<f(o.l,o.k)-f(o.l,o.k+1);
	}
};
priority_queue<node>q;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>K;K-=n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i)q.push({a[i],1}),ans+=a[i]*a[i];
	for(int i=1;i<=K;++i){
		node u=q.top();q.pop();
		int l=u.l,k=u.k;
		ans-=f(l,k)-f(l,k+1);
		q.push({l,k+1});
	}cout<<ans;
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

对于一个胡萝卜，假若切成 $x$ 根那么一定是平均的切最优，不妨记 $val_i(x)$ 表示第 $i$ 根胡萝卜切成 $x$ 根带来的代价，再定义 $g_i(x) = val_i(x-1) - val_i(x)$，我们发现 $g_i(x)$ 是单调的且增长越来越缓慢，也即是凸的，而答案是 $\max_{\sum x_i = k} \sum g_i(x_i)$，也就是所有 $g_i(x)$ 的闵可夫斯基和的第 $k$ 项，直接用堆维护一下闵可夫斯基和即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
int val(int x,int y){
	int d=x/y;
	int f=x%y;
	int g=y-f;
	return d*d*g+(d+1)*(d+1)*f;
}
int a[maxn],vis[maxn],n,k,sum;
multiset< pair<int,int> > S;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i]*a[i],vis[i]=1;
	k-=n;
	for(int i=1;i<=n;i++) S.insert(make_pair(val(a[i],vis[i])-val(a[i],vis[i]+1),i));
	for(int i=1;i<=k;i++){
		pair<int,int> tp=(*S.rbegin());
		S.erase(S.find(tp));
		sum-=tp.first;
		int u=tp.second;
		vis[u]++;
		S.insert(make_pair(val(a[u],vis[u])-val(a[u],vis[u]+1),u));
	}
	cout<<sum<<"\n";
	return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

令 $\operatorname{f}(x,y)$ 为将长度为 $x$ 的胡萝卜切成 $y$ 份最小平方和。

对于只有一根胡萝卜的情况，很明显需要平均分，这样一定最优。根据均值不等式，很容易得出 $\operatorname{f}$ 函数的算法，可以参考代码。

考虑贪心，在每根胡萝卜中，哪一根胡萝卜在我们多切一刀时能使我们的成本减少最多。如果长度为 $x$ 的胡萝卜目前有 $y$ 块，那么多切一刀所减少的成本为 $\operatorname{f}(x,y)-\operatorname{f}(x,y-1)$。注意到它是一个减函数，那么保证了价值是单调不减的，换句话说，萝卜切的越多块，总价值越低。因此可以用单调队列求解。

重载运算符时，只需要比较 $\operatorname{f}(a,b)-\operatorname{f}(a,b+1)$ 与 $\operatorname{f}(a',b')-\operatorname{f}(a,b'+1)$ 即可。

仔细观察数据范围，发现需要开 `long long`，不然会爆掉。更多细节可以看代码。

```cpp
#define int long long
int n,k;
int ans;
int sum(int x,int y)
{
	return (x/y)*(x/y)*(y-x%y)+(x%y)*(x/y+1)*(x/y+1);
}
struct node
{
	int x,y;
	bool operator <(const node &a) const
	{
		return sum(x,y)-sum(x,y+1)<sum(a.x,a.y)-sum(a.x,a.y+1);
	}
};
priority_queue<node> pq;
void solve()
{
	cin>>n>>k;
	int i;
	for(i=1;i<=n;i++)
	{
		int a;
		cin>>a;
		ans += a*a;
		pq.push({a,1});
	}
	for(i=1;i<=k-n;i++)
	{
		node u = pq.top();
		pq.pop();
		ans -= sum(u.x,u.y)-sum(u.x,u.y+1);
		pq.push({u.x,u.y+1});
	}
	cout<<ans<<endl;
    return;
}
```

---

## 作者：tder (赞：0)

什么唐诗出题人 NOIP 模拟赛 T1 放蓝题。

---

我们不妨定义 $f(i,j)$ 表示将一根长度为 $i$ 的萝卜切成 $j$ 段的最小答案，即对于所有满足 $\displaystyle\left(\sum_{k=1}^ja_k\right)=i$ 的序列 $\{a_j\}$，取 $f(i,j)=\displaystyle\min\left\{\sum_{k=1}^ja_k^2\right\}$。

那么，有显然的贪心结论：

> 当序列 $\{a_j\}$ 中有 $j-(i\bmod j)$ 个 $\left\lfloor\dfrac ij\right\rfloor$ 和 $i\bmod j$ 个 $\left\lfloor\dfrac ij\right\rfloor+1$ 时，此时 $f(i,j)$ 取到最小值，为：
> $$
>   f(i,j)=\left(j-(i\bmod j)\right)\times\left\lfloor\dfrac ij\right\rfloor^2+(i\bmod j)\left(\left\lfloor\dfrac ij\right\rfloor+1\right)^2
> $$

这个很好证明，类似「和一定差小积大」的思考方式即可。

我们不妨先计算出 $\text{ans}_0=\sum f(a_i,1)$，即一刀不切时的答案。

接下来，考虑试图缩小这个答案。显然的，对于长分别为 $x,y$ 的两个萝卜，若 $\Delta x=f(x,p)-f(x,p+1)>\Delta y=f(y,q)-f(y,q+1)$，即把 $x$ 多切一刀的贡献比把 $y$ 多切一刀更大，则切 $x$ 更优。此处感性理解一下，我们需要最终的 $\text{ans}=\text{ans}_0-\sum\Delta$ 尽可能小，即减少的 $\Delta$ 尽可能大，因此我们优先选择贡献较大的切。

因此可以用优先队列维护，再记录一下每个萝卜当且被切了几刀，在代码中是 $\{d_n\}$ 序列。记 $n,k$ 同阶，时间复杂度 $O(n\log n)$。

---

代码中的取模可以全部删去，模拟赛的题是带取模的，懒得删了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e6 + 5, M = 1e18;
int n, m, c[N], cnt, d[N], ans;
priority_queue<pair<int, int>> q;
int f(int i, int j) {
	return (i / j) * (i / j) * (j - i % j) + (i / j + 1) * (i / j + 1) * (i % j);
}
signed main() {
	cin>>n>>m;
	for(int i = 1; i <= n; i++) cin>>c[i], cnt += (bool)c[i];
	if(cnt > m) {
		cout<<-1<<endl;
		return 0;
	}
	m -= cnt;
	for(int i = 1; i <= n; i++) if(c[i]) {
		ans += f(c[i], 1) % M, ans %= M; d[i] = 1;
		q.push({f(c[i], 1) - f(c[i], 2), i});
	}
	while(m-- && !q.empty()) {
		auto t = q.top(); q.pop(); 
		int i = t.first, j = t.second;
        ans -= i % M, ans += M, ans %= M;
		d[j]++;
        q.push({f(c[j], d[j]) - f(c[j], d[j] + 1), j});
    }
	cout<<ans<<endl;
}
```

---

## 作者：Little09 (赞：0)

想象下面的情景：现在你面前有 $n$ 台可以升级的机器，每台机器都是第 $1$ 级别。第 $i$ 台机器从第 $j$ 级升级到第 $j+1$ 级的代价为 $c(i,j)$（代价当然大于 $0$），是一个可以在 $O(1)$ 时间内计算的常数。你需要升级 $k$ 次，请问你所需的最小代价。

贪心地想，每次找到一个所需代价最小的机器升级即可。此处只需要用一个优先队列维护即可。但是需要注意，如果是最大代价，贪心就是显然不对的了。

再回到这道题上，$n$ 个胡萝卜就是 $n$ 个机器，对每个萝卜的升级就是把它从切 $x$ 块变成切 $x+1$ 块。我们设计一个函数 $f(x,y)$ 表示把长度 $x$ 的萝卜切成 $y$ 份的代价，那么升级的代价就是 $f(x,y)-f(x,y+1)$。于是就与开头的机器升级问题一样了。

至于 $f$ 函数很显然是可以 $O(1)$ 算出来的，只要尽量平均地切即可。

代码实现不难。

---

## 作者：MVP_Harry (赞：0)

挺有意思的一道题，比赛时一直在考虑如何优化dp，没想到直接贪心的做法。

首先，对于一个长度为$l$的萝卜，分成$x$段，很明显想到均值不等式，容易在$O(1)$时间内求出。其次，可以证明对于一个固定的萝卜，将其切成$x$段带来的收益（及减少的量）是大于等于将其再继续切成$x + 1$段的。

因此，利用这两个性质，不难得出一个贪心的策略：对每一次切的时候，考虑如何能减去最大值，而这很好用```priority_queue```维护。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, m, n) for (int i = m; i <= n; i++)

const int maxn = 1e5 + 5;
ll a[maxn]; 
ll cost = 0; 
priority_queue< pair<ll, pair<ll, ll> > > q; 

ll val(ll len, ll nums) {
	ll unit = len / nums;
	ll extra = len - unit * nums;
	return (nums - extra) * unit * unit + extra * (unit + 1) * (unit + 1); 
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0); 
    int N, K;
    cin >> N >> K;
    rep(i, 1, N) {
    	cin >> a[i];
    	cost += (ll) a[i] * a[i];
    	q.push(mp(val(a[i], 1) - val(a[i], 2), mp(a[i], 2))); 
    }
    int cuts = K - N;
    rep(i, 1, cuts) {
    	cost -= q.top().first; 
    	ll a = q.top().second.first, b = q.top().second.second;
    	q.pop();
    	q.push(mp(val(a, b) - val(a, b + 1), mp(a, b + 1)));
    }
    cout << cost << "\n"; 
	return 0; 
}
```

---

