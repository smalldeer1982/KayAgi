# [USACO09OPEN] Work Scheduling G

## 题目描述

农夫约翰有很多工作要做！为了高效地经营农场，他必须从他所做的每一项工作中赚取利润，每项工作只需要一个时间单位。

他的工作日从时间 $0$ 开始，总共有 $1,000,000,000$ 个时间单位。他目前可以从 N ($1 \leq N \leq 100,000$) 项工作中选择要做的工作，这些工作被方便地编号为 $1$ 到 $N$。

虽然理论上他有可能完成所有 $N$ 项工作，但实际上这是极不可能的，因为他在任何一个时间单位内只能完成一项工作，而截止日期通常会导致他无法完成所有任务。

第 $i$ 项工作的截止时间为 $D_i$ ($1 \leq D_i \leq 1,000,000,000$)。如果他在截止时间前完成第 $i$ 项工作，他将获得 $P_i$ ($1 \leq P_i \leq 1,000,000,000$) 的利润。

给定一系列工作和截止日期，FJ 能够获得的最大总利润是多少？答案可能无法容纳在 32 位整数中。

## 说明/提示

在时间 1 完成工作 3 (1,7)，在时间 2 完成工作 1 (2,10) 以最大化收益 (7 + 10 -> 17)。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3 
2 10 
1 5 
1 7 
```

### 输出

```
17 
```

# 题解

## 作者：Taduro (赞：77)

这题是一道带反悔的贪心，第一次遇到这种思路的题赶紧发个题解纪念一下。
首先思路就是先按时间排序（不是那个1e8啊，是截止日期），然后如果一个工作有时间去做，就先做了它（听起来有点怪），然后把它的价值压入一个小根堆。当我们找到一个没法做却价值比当前堆顶高的工作时，我们就放弃那个最小的工作，用做它的时间去做这个价值更高的工作。

另外，这题似乎不能用一般的单调队列做？（求不打脸）因为维护队列单调性的时候要删去一些元素，这样就无法支持题目所要求的修改。（或者用dp+单调队列？）

```
#include<queue>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	int tim,mny;
}w[100001];
int n,i;
long long ans;
priority_queue<int,vector<int>,greater<int> > q;
bool cmp(node a,node b){
	return a.tim<b.tim;
}
int main(){
	scanf("%d",&n);
	for (i=1; i<=n; i++)
		scanf("%d%d",&w[i].tim,&w[i].mny);
	sort(w+1,w+n+1,cmp);
	for (i=1; i<=n; i++){
		if (w[i].tim<=q.size()){
			if (w[i].mny>q.top()){
				ans-=q.top();
				q.pop(); q.push(w[i].mny);
				ans+=w[i].mny;
			}
		}
		else{
			q.push(w[i].mny);
			ans+=w[i].mny;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Ace_Heart (赞：39)

蒟蒻第一次写题解

表示瑟瑟发抖……

看着题解太冷清了……

~~而上一篇又有点点简略~~

主要也是为了梳理梳理自己思路，就献丑写一篇题解啦~

首先

这是一道很明显的贪心题

看到题的第一步肯定是想排序截止时间

正常人当然是想优先完成紧急的工作啦~

在紧急的工作里自然是优先完成报酬高的工作啦~

如果你想到这样贪心的话

枚举1~n项已经排好序的工作

每做一项工作就day++

然后符合条件就做

就可以拿到40分

其实错误的原因很简单

到后期万一都是高报酬的工作（但由于超时做不了了）

你会不会后悔前期做了哪些低报酬的工作呢？

就像这个例子

n=4

(a) 1 2

(b) 1 1

(c) 2 8

(d) 2 5

显然如果第一天做了a或b任何一个工作

到第二天都会后悔

于是我们就想

要是我第一天做的是当前的工作就好的（报酬更高）

于是我们想改变过去

减去第一天的工作的报酬（不做了）

在第一天做我们当前的工作（当前超时的工作）

那么依次类推

枚举到第i项工作时如果工作超时了

那么就穿越回过去在之前做过的工作中挑一个报酬最低的

然后在那一项工作那天做第i项的工作（前提是第i项工作报酬要高于过去最低报酬的那天的工作，不然没有收益）

那么如何快速找到最低报酬的那项做过的工作呢？

于是我们就自然而然的想到用一个小根堆（优先队列）来维护

保证队首为最小的

符合条件的就入队即可

代码如下

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#define ll long long
#define N 1001003
#define inf 0x7fffffff
using namespace std;
ll read()
{
	int flag=1;
	ll ret=0;
	char ch=getchar();
	while( (ch>'9' || ch<'0') && ch!='-')
	ch=getchar();
	if(ch=='-')
	flag=-1,ch=getchar();
	while(ch>='0' && ch<='9')
	ret=ret*10+ch-'0',ch=getchar();
	return ret*flag;
}
struct work
{
	ll d;
	ll p;
};
work a[N];
bool cmp(work x,work y)
{
	if(x.d==y.d)
	return x.p>y.p;
	return x.d<y.d;
}
ll day=0;
ll d[N];
void Add(ll x)
{
	day++;
	int son=day;
	int father=son/2;
	while(x<d[father] && father)
	{
		d[son]=d[father];
		son=father;
		father=son/2;
	}
	d[son]=x;
}
ll Del()//输出并删除堆顶元素 
{
	ll ret=d[1];
	int father=1;
	int son=father*2;
	if(son+1<day && d[son+1]<d[son])
	{
		son++;
	}
	while(son<day && d[son]<d[day])
	{
		d[father]=d[son];
		father=son;
		son=father*2;
		if(son+1<day && d[son+1]<d[son])
		son++;
	}
	d[father]=d[day];
	day--;
	return ret;
}
int main()
{
	ll n;
	n=read();
	for(ll i=1;i<=n;i++)
	{
		a[i].d=read();
		a[i].p=read();
	}
	sort(a+1,a+1+n,cmp);
	ll money=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i].d>day)//由于day实际为当前队列长度（做的工作数），故应该大于 
		{
			Add(a[i].p);//不超时直接入队 
			money+=a[i].p;
		}
		else
		{
			if(a[i].p>d[1])//超时则与队首比较大小 
			{
				Add(a[i].p);
				money+=a[i].p-Del();//前面已保证收益为正 
			}
		}
	}
	cout<<money;
	return 0;
}
```









---

## 作者：Imakf (赞：24)

~~似乎没有看到跟我一样的做法？~~

首先这个题对于每一个物品有两个参数 $(end,val)$，我们期望选出的   $val$ 和尽可能大。通常情况下我们贪心都是时间从小到大排序，但我们可以考虑**反着做**。

### Hint

设最大的 $end$ 为 $R$ ,次大的为 $R'$。所有 $end = R$ 的物品，能在时间 $(0,R]$ 处被选。所有 $end = R'$ 的物品能在时间 $(0.R']$ 处被选，以此类推。

### 算法流程

得到这个事实后，我们可以维护一个大根堆，初始为空，我们按照时间 $t$ **从大到小扫到** $1$。对于每一个 $t$ ，如果存在 $end=t$ 的就先把，所有的 $end = t$ 的 $val$ 放入堆。然后每一秒都取走最大值即可。

这么做，复杂度是跟 $\max\{end\}$ 有关的，我们发现中间有大段的时间都是不需要插入操作的，于是我们可以简化这一部分的流程。详见代码。

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>

#define rg register
#define MX (100000 + 5)
#define ll long long
#define int long long

std::priority_queue<int> q;

int read(){//快速读入}

struct WORK{
	int pos ,val;
	bool operator <(const WORK &B)const{return pos == B.pos ? val > B.val : pos > B.pos;}
}P[MX];

signed main(){
	int n = read();
	for(rg int i = 1 ,p ,v ; i <= n ; ++i){
		p = read(); v = read();
		P[i] = (WORK){p ,v};
	}
	std::sort(P + 1 ,P + 1 + n);
	P[n + 1] = (WORK){0 ,0};	// 终止条件
	ll Ans = 0;
	for(rg int i = 1 ; i <= n ; ){	// 此处的 i 枚举的是 n 个插入操作
		while(true){	// 同一秒的操作都一次性完成
			q.push(P[i++].val);
			if(P[i].pos != P[i - 1].pos)	break;	
            	// 下一个要插入的不是同一秒的就 break 掉
		}
		int cnt = P[i - 1].pos - P[i].pos;
        	// 找到两组插入之间的时间差，节约了枚举时间的复杂度
		while(!q.empty() && cnt--){	// 注意堆要非空
			Ans += q.top();	// 每秒都选最大值
			q.pop();
		}
	}
	printf("%lld\n" ,Ans);
	return 0;
}
```

---

## 作者：子谦。 (赞：20)

读完题，我们会发现有一个很重要的信息，每件物品代价相同，但价值不同。那么我们很容易想到，在满足限制的情况下，我们肯定会选择价值尽可能大的物品。

我们可否用背包来实现呢，答案是否定的，或者说我不会QwQ

那么，我们来看看贪心

由于物品的代价相同，那么当物品之间冲突时，我们留下价值大者，必定最优。因为每件物品代价都是1，那么不可能出现因为放入一件物品，而挤掉了两件物品的可能，所以一定是单点比较，没有什么求和之类的

对于价值一件物品被放入的越晚，影响也就越小，那么我们就要尽可能晚的放入物品

我们用0表示这一秒有任务，1表示没有。那么我们按照价值排序，寻找$1$~$d[i]$中最靠右的0，将他变成1，答案加上当前物品的价值即可

详见代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc getchar
#define maxn 1000005
using namespace std;

inline ll read(){
    ll a=0;int f=0;char p=gc();
    while(!isdigit(p)){f|=p=='-';p=gc();}
    while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
    return f?-a:a;
}

struct ahaha{
    int w,b;
    inline bool friend operator<(const ahaha &x,const ahaha &y){
        if(x.w!=y.w)return x.w>y.w;
        return x.b<y.b;
    }
}q[maxn];

int n,cnt,b[maxn];
ll ans;
int tree[maxn];   //利用树状数组修改及查询前缀和
#define lowbit(x) x&-x
inline void add(int a,int k){
    while(k<=n){
        tree[k]+=a;
        k+=lowbit(k);
    }
}
int query(int k){
    int sum=0;
    while(k){
        sum+=tree[k];
        k-=lowbit(k);
    }return sum;
}

inline void solve(int i){
    int sum=query(q[i].b);    //在当前物品截止时间前，放入了多少物品
    if(sum==b[q[i].b])return;  //如果已经放满，则返回
    int l=1,r=q[i].b;
    while(l<r){    //二分查找最靠右的0
        int m=l+r>>1;
        int ss=query(m);
        if(sum-ss==b[r]-b[m]){
            r=m;sum=ss;
        }
        else
            l=m+1;
    }ans+=q[i].w;add(1,l);
}

int main(){
    n=read();
    for(int i=1;i<=n;++i)
        b[++cnt]=q[i].b=read(),q[i].w=read();
    sort(b+1,b+cnt+1);cnt=unique(b+1,b+cnt+1)-b-1;
    for(int i=1;i<=n;++i)    //先将截止时间离散化，我们把总的时间分为若干时间段，每段时间只有一个时间点为截止时间
        q[i].b=lower_bound(b+1,b+cnt+1,q[i].b)-b;
    sort(q+1,q+n+1);    //按照权值排序
    for(int i=1;i<=n;++i)
        solve(i);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Parabola (赞：19)

都是堆与树状数组？

有没有考虑过贪心部分线性呢？

其实也算不到线性，因为这样搞还要考虑天数...

所以时间复杂度是$O(Nlog_2N + α(1e9) * N)$

贪心思路：对于每一个利润最大的工作，我们尽量选。

很快能想出暴力

设$c_i$代表第$i$天是否安排了工作，那么对于每一个工作，我们尝试把它放在它的截止日期上（这样才能让其他的工作有更多的空位安排）。

但如果它的截止日期已经放置了呢？那就截止日期前一天，如果前一天还可以呢？再前一天...

所以暴力代码很快能写出来

```
//按照获得利润值排序

//考虑第i个工作
for(int i = 1 ; i <= n ; ++i) {
	int k = END(i); //第i个工作的截止日期
    while(c[k]) --k; //找到第一个可以放置这个工作的天
	if(k == 0) continue; //如果不存在这个天，那这个工作就没办法选了
    //那现在就是可以选了
    ans += P(i) , c[k] = true;
    //得到这个点的价值，并且把这一天标记为已放置
}
```

肯定TLE啊...

看到那个最慢的循环了嘛


```cpp
while(c[k]) --k;
```

拿个并查集让这个循环变成一次`find`操作，各位应该明白我意思。

然后就又因为天数最大到了`1e9`，所以随便离散化一下就过了，但是我偷懒直接`C++11-unordered_map`乱搞了，要更快可能得手写hash表。

------------


## Code

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;
const int MAXN=100000+5;
struct stu
{
    int e;
    long long p;
}a[MAXN];
unordered_map <int , bool> c;
unordered_map <int , int> f;
unordered_set <int> cx;
int n,m;
inline bool cmp(stu a,stu b)
{
    return a.p>b.p;
}
int find(int x) {
    if(!cx.count(x)) f[x] = x , cx.insert(x);
    return f[x]==x ? x : f[x]=find(f[x]);
}
void merge(int x,int y)
{
    int t1=find(x),t2=find(y);
    if(t1!=t2)
        f[t1]=t2;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(register int i=1;i<=n;i++)
        cin>>a[i].e>>a[i].p;
    long long ans=0;
    sort(a+1,a+n+1,cmp);
    for(register int i=1;i<=n;i++)
    {
        int k=find(a[i].e);
        if(k==0)    continue;
        c[k]=true;
        ans+=a[i].p;
        merge(k,k-1);
    }
    cout<<ans;
}
```

---

## 作者：witliu (赞：17)

贪心思想：先假设每一项工作都做，将各项工作按截止时间排序后入队，在判断第i项工作做与不做时，若其截至时间符合条件，则将其与队中报酬最小的元素比较，若第i项工作报酬较高，则ans+=a[i].p-q.top()。用优先队列（小根堆）来维护队首元素最小。

    
    
```cpp
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
struct yw{
long long d,p;
}a[100005];
priority_queue <yw> q;
bool cmp(const yw&a,const yw&b)
{
  return a.d<b.d;
}
bool operator < (yw a,yw b)
{
     return a.p>b.p;
}
int main()
{    
    long long n,ans=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) 
    scanf("%lld%lld",&a[i].d,&a[i].p);
    sort(a+1,a+1+n,cmp);  // 按照截止时间排序 
    for(int i=1;i<=n;i++)
        if (a[i].d<=q.size())
        {
          if (q.top().p<a[i].p) 
            ans+=a[i].p-q.top().p,q.pop(),q.push(a[i]);//修改队中元素 
        }
        else 
        q.push(a[i]),ans+=a[i].p;
    printf("%lld",ans);
}
```

---

## 作者：llzzxx712 (赞：14)

# P2949
[（可能）更好的阅读体验](https://www.luogu.com.cn/blog/llzzxx712/solution-p2949)

[传送门](https://www.luogu.com.cn/problem/P2949)
## 题目描述
- 给你N个任务，每个任务 $i$ 都有截止日期  $d_{i}$ 和报酬$p_{i}$。
- 完成每个任务时间相同，都为一个单位。
- 你需要使所得报酬最大并输出。
- $1<=p_{i},d_{i},n<=10^9$
## 题目分析
这是一道**贪心**题是肯定的，但我没有想到用标签中的单调队列怎么做，我使用了**二叉堆/优先队列**来解决。

**那具体怎么贪心呢？**

先是一个**错误的贪心思路**(注意是错的）——在每个时间点都选择当前报酬最高的任务进行完成。

这很容易举出反例，比如这里有两个工作，一个报酬为5，截止日期为3 。另一个报酬为4，截止日期为1 。按照此贪心思路我们先选第一个工作得到5点报酬然后第二个工作因截止而放弃。但很显然我们应该先选第二个工作再做第一个，这样可以获得9点报酬。

那么我们修改我们的思路——把任务按照时间排序，按照时间选择任务。

但仍可以举出反例，这里有三个任务，第一个任务截止时间为1，报酬为1，后两个任务截止时间都为2，报酬分别为8和9，按照此思路我们会先选择任务1，但很显然我们应该选择任务2、3而不选1.

这需要我们进一步改进，我们注意到每个任务完成的时间都为1，这意味着我们在一个时间可以做任意一个任务。当我们遇到一个报酬更大的任务且时间不够时，我们应该放弃前面选择的报酬最小（且比当前任务报酬小）的任务进行替换——这就是贪心中的**退流思想**。我们可以建立一个小根堆，将每次选择的任务报酬放入堆中，每次时间不够时取出堆顶，与当前任务进行比较。

## 思路总结
1. 读入每个工作并用结构体储存，按时间从小到大排序。
1. 建立小根堆与每次任务比较，保证结果最优。

## 易错点
- 结果可以很大，记得开 long long。
- 替换任务时不需要增加时间

## 代码（带注释）

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#define N 100002
#define ll long long 
using namespace std;
void read(int &x){//快读 
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	x*=f;
}
struct cow{
	int g,d;//g为奶，d为截止时间 
}a[N];
int cmp(cow aa,cow bb){
	return aa.d<bb.d;//按照时间排序 
}
priority_queue < int > q;
int n,t;
ll ans;//只有结果需要开long long 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		read(a[i].d),read(a[i].g);//读入 
	}
	sort(a+1,a+1+n,cmp);//排序 
	for(int i=1,t=1;i<=n;i++){//i表示现在扫描到第几个任务，t表示当前花费了多少时间 
		if(a[i].d<t){//时间不够了 
			int x=-q.top();//取负存入、取出（使它为小根堆） 
			if(x<a[i].g){//如果取出的任务报酬比当前小，替换 
				q.pop();q.push(-a[i].g);
				ans+=a[i].g-x; 
			}
		}
		if(a[i].d>=t){//时间充足，将当前任务放入 
			q.push(-a[i].g); 
			ans+=a[i].g;t++;
		}
	}
	cout<<ans;
}

```

**最后**：令人喜爱的双倍经验

[p3093 双倍经验](https://www.luogu.com.cn/problem/P3093)

**写题解不易，给个赞呗**

---

## 作者：KSToki (赞：14)

看到题解里清一色的堆维护的反悔贪心，我来提供一个**树状数组优化暴力**。

仍然是贪心，以价值为关键字从大到小排序，如果 $1\sim t[i]$ 没有塞满，那就尽量咕到最后一个空位做。正确性显然，直接暴力是 $O(n^2)$ 的。

发现找空位的过程可以优化，加入树状数组，二分位置判断即可，时间复杂度 $O(nlog^2n)$ 可以通过。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int n;
struct work
{
	int w;
	int t;
	bool operator <(work x2)
	{
		return w>x2.w;
	}
}x[100001];
int c[100001];
ll ans;
inline int lowbit(int a)
{
	return a&(-a);
}
inline void update(int pos,int v)
{
	while(pos<=n)
	{
		c[pos]+=v;
		pos+=lowbit(pos);
	}	
}
inline int sum(int pos)
{
	int res=0;
	while(pos)
	{
		res+=c[pos];
		pos-=lowbit(pos);
	}
	return res;
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i)
	{
		x[i].t=min(read(),(int)1e5);
		x[i].w=read();
	}
	sort(x+1,x+n+1);
	for(int i=1;i<=n;++i)
		if(sum(x[i].t)!=x[i].t)
		{
			int l=1,r=x[i].t,mid,res;
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(sum(x[i].t)-sum(mid-1)!=x[i].t-mid+1)
				{
					res=mid;
					l=mid+1;
				}
				else
					r=mid-1;
			}
			update(res,1);
			ans+=x[i].w;
		}
	printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：John_Nash (赞：10)

这题可以用逆向思维，假设时间倒流，那么工作的截止日期就变成工作的开始日期，这样就变成一个很简单的贪心，只要每天做利润最大的工作即可（因为工作在时间到0之前永远不会消失）。
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

const int Max_n=100005;

struct Node{
    int d,p;
}job[Max_n];

priority_queue<int> q;

bool cmp(Node a,Node b){
    return a.d>b.d;
}

int main(){
    int n,t,p;
    long long ans;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&job[i].d,&job[i].p);
    sort(job+1,job+n+1,cmp); //工作截止时间降序，即时光倒流的情况下开始时间升序
    p=1; ans=0ll;
    while(p<=n){ //循环直到所有工作都已经开始
        if(q.empty()) t=job[p].d; //如果当前没有工作，将时间直接前进到下一个工作的开始时间
        while(p<=n&&job[p].d==t) //把此时开始的工作加到队列中
            q.push(job[p++].p);
        ans+=q.top(); //做利润最大的工作
        q.pop(); t--; //时间“前进”一天
    }
    while(t&&!q.empty()){ //只要时间没结束且还有工作可做，就继续做
        ans+=q.top();
        q.pop(); t--;
    }
    cout<<ans<<endl;
    return 0;
}

```
虽然代码长度差不多，但更好理解。

---

## 作者：Vanyun (赞：6)

## 题意

现在有$n$个工作，每个工作对应一个到期的时限$D_i$和一个完成工作可获得的报酬$P_i$。

每完成一个工作需要耗费$1$的单位时间。

现在你需要考虑如何安排工作才可以使获得的报酬最大。并输出最大的报酬。

## 思路

这是一道带需要可以反悔的贪心题。

首先我们尽量完成多的任务。这样价值可能会比较大。

所以我们按照时间来排序。

用一个小根堆来维护我们已完成的工作中的可获得的报酬的最小值。

如果我们当前枚举到的工作时限已经过了，我们跟最小值比较一下。如果目前工作可获得的收益大的话说明我们完成这个工作可获得的效益更高。这个就是反悔的过程。

否则直接累加即可。

证明的话因为花费的时间都是一样的，那么我们把价值大留下来肯定更优。

这样枚举到到最后一定是最大值。

因为每完成一个工作需要的时间都是$1$，所以小根堆中节点的数量就是已经花费的时间。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int maxn = 1e5+10;

int n, ans;
pair<int,int> a[maxn];

signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i ++) scanf("%lld%lld", &a[i].first, &a[i].second);
	sort(a+1, a+n+1);
	priority_queue<int, vector<int>, greater<int> > q;
	for(int i = 1; i <= n; i ++){
		if(a[i].first <= q.size()){
			if(a[i].second > q.top()){
				ans -= q.top();
				ans += a[i].second;
				q.pop();
				q.push(a[i].second);
			}
		}else q.push(a[i].second), ans += a[i].second;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：0nullptr (赞：3)

题目链接 ：[P2949](https://www.luogu.org/problem/P2949)

这道题目是一道很明显的**贪心**问题。可以发现每个工作代价（占用时间）均为一，而相应的价值（工作利润）不同。此时我们可以想到一个很显然的贪心策略，即
```
1.当工作的利润不同时，优先进行利润更大的工作
2.当工作的利润相同时，优先进行截止时间更晚的工作
```
根据以上贪心策略，对于工作，可以定义以下结构体
```cpp
struct job{
    int end_time;//截止时间
    int value;//工作利润
	
    bool operator< (const job &J)const {//重载小于号
        if (value != J.value) return value > J.value;
        return end_time > J.end_time;
    }
}j[100005];
```
接下来考虑如何处理工作时间冲突的情况。由于排序后，数组前面的元素利润更大，显然，当为了使利润更高，应该将排序后数组中靠后的工作在截止时间之前进行。由于有$10^9$的单位时间，显然是开不下一个这么长的数组用来判断每个时间是否进行工作。考虑到工作数量$N\leq10^6$,我们使用一个$set$对每个时间是否进行工作进行存储。代码如下：
```cpp
set<int> pr;//用于判断每个时间是否进行了工作
int main(){
    int n;
    cin>>n;
    for (int i = 1; i <= n; i++){
        cin>>j[i].end_time>>j[i].value;
    }
    sort(j + 1, j + n + 1);//对工作数组j进行排序
    long long ans = 0;//注意此处必须开long long，不然会爆掉
    for (int i = 1; i <= n; i++){
        while ( pr.count( j[i].end_time )  && j[i].end_time > 0) {
            j[i].end_time--;
        }//判断当前截止时间是否进行了工作，如果有工作在进行，那么将截止时间前移
        if ( j[i].end_time ){//如果当前工作在0时刻之前可以进行
            ans += j[i].value;//加上该工作的利润
            pr.insert( j[i].end_time );//记录当前时间
        }
    }
    cout<<ans<<endl;//输出
    return 0;
}
```
把这段代码提交评测，居然**T**了四个点？考虑对代码进行优化。不难发现，在将当前工作时间前移的**while循环**中浪费了大量的时间。当大量工作截止时间相同时，会进行大量重复计算。因此可以用一个类似于并查集的结构进行优化，记录下每个时间之前最晚**可能**没有进行工作的时间。使用**map**进行存储该结构与每个时间是否进行工作后，改写的**while循环**如下：
```cpp
map<int, int> time_table;//用于存储每个时间之前最晚可能没有进行工作的时间

int now_time = j[i].end_time;
while ( pr[ j[i].end_time ] && j[i].end_time > 0) {
    if(time_table[ j[i].end_time ])//如果当前时间前有一段时间已经进行了工作 
        j[i].end_time = time_table[ j[i].end_time ]--;//向前跳跃一段时间
    else j[i].end_time--;//否则只向前进行一步
}
time_table[now_time] = j[i].end_time;//更新
```
这样，虽然循环中仍有部分重复计算，代码运行效率已经降低到可以接受的范围，完整的优化留作后续思考~~其实是我不想写QAQ~~。下面给出基于$pbds$的完整代码实现
```cpp
// luogu-judger-enable-o2
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
using namespace __gnu_pbds;

inline int read() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ 48);
        c = getchar();
    }
    return x;
}

struct job {
    int end_time;
    int value;
} j[100005];

struct cmp{
    inline bool operator() (const job& J1, const job& J2){
        if (J1.value != J2.value) return J1.value > J2.value;
        return J1.end_time > J2.end_time;
    }
};

gp_hash_table<int, int> pr;
gp_hash_table<int, int> time_table;
int main() {
    int n = read();
    for (register int i = 1; i <= n; ++i) {
        j[i].end_time = read();
        j[i].value = read();
    }
    sort(j + 1, j + n + 1, cmp());
    long long ans = 0;
    for (register int i = 1; i <= n; ++i) {
        int now_time = j[i].end_time;
        while ( pr[ j[i].end_time ] && j[i].end_time > 0) {
            if(time_table[ j[i].end_time ])
                j[i].end_time = time_table[ j[i].end_time ]--;
            else j[i].end_time--;
        }
        time_table[now_time] = j[i].end_time;
        if ( j[i].end_time ) {
            ans += j[i].value;
            pr[ j[i].end_time ] = 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：SBofGaySchool (赞：2)

大佬们思路都说的非常清楚路，我来贡献一个相同思路使用 $set$ 进行实现的极简做法。（前面的题解中，有一个大佬提及了 $set$，但是思路貌似和我的有一定差异，而且他最后 $T$ 了……）

### 1. 贪心思想总结

这道题目的贪心思想很明确：

- 单位时间只能做一件工作，所以应该先考虑利润高的；
- 对于每件工作，应该尽量把它往后拖，这样剩下比较靠前的时间可以安排别的工作。

总结一下，我们只需要根据利润从高到低给工作排序，然后对于每件工作，我们尽量把它往后安排，即安排到 **最靠后** 并且 **不晚于其截止时间** 的时刻。

### 2. 实现方法

可以注意到，如果一个工作的截止时间大于 $N$，那么它 **一定可以被安排上**，所以我们只需要关心截止时间小于等于 $N$ 的工作即可。

我们可以使用一个 $set$ 存储当前所有的空闲时间，一开始，$1$ 时刻到 $N$ 时刻都是空闲的，即这个 $set$ 中存储了 $1$ 到 $N$ 中的所有数。

对于每个截止时间小于等于 $N$ 的工作，我们从这个 $set$ 中找到 **最大的** 且 **不晚于其截止时间** 的空闲时刻。如果存在，就意味着这个工作可以被安排上，我们从 $set$ 中删除这个时刻，并把这个工作的利润累加到答案中。

我们需要对所有工作排序。对每个工作，都可能涉及从 $set$ 中查找并删除元素的操作，所以这样做的时间复杂度为 $O(N \log N)$，可以轻松通过本题。

### 3. 代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define MAXN 100005
long long n;
// 工作，first为利润，second为截止时间
pair<long long, long long> k[MAXN];
long long ans;
// 用于存储空闲时刻的set
set<long long> s;
int main() {
    scanf("%lld", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &k[i].second, &k[i].first);
    }
    // 根据利润进行排序
    sort(k, k + n);
    // 初始化set，加入1~N，因为开始时这些时刻都是空闲的
    for (long long i = 1; i <= n; i++) {
        s.insert(i);
    }
    // 按照价值从高到低考虑每件工作
    for (long long i = n - 1; i >= 0; i--) {
        // 对于截止时间小于等于n的工作，我们才需要考虑其是否能安排上
        if (k[i].second <= n) {
            // 从set中找到第一个【晚于】其截止时间的时刻
            // 这一时刻【之前】的那个时刻，就应该是我们安排这个工作的时刻
            auto it = s.upper_bound(k[i].second); 
            // 如果不存在（剩余时刻中的第一个时刻都晚于其截至时间了），就只能放弃
            if (it == s.begin()) {
                continue;
            }
            // 否则，安排上这个工作，并移除其占用的时刻
            s.erase(--it);
        }
        // 累加答案
        ans += k[i].first;
        
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：peterwuyihong (赞：2)

# $Work\ Scheduling$
## 贪心算法中的后悔算法

假设宁是贪心算法计算机花$Q$，后悔算法流程大致如下

花$Q$：小孩子才做选择，我全都要！（假设全做，按时间排序）

花$Q$：咦，做这个工作（智这个障）有时间耶，做！

花$Q$：草，来不及了来不及了。哇！这个工作比之前那个工作赚的钱多耶！砸瓦鲁多！（之前的工作不做了，换成了这个工作）

那么如何维护这个“之前的工作”呢？大根堆维护即可
```cpp
#include<bits/stdc++.h>
#define debug(x) cerr<<#x<<' '<<x<<endl
using namespace std;
template<class T>void read(T &__x){
	__x=0;short __f=1;char __ch=getchar();
	while(__ch<'0'||__ch>'9'){if(__ch=='-')__f=-1;__ch=getchar();}
	while(__ch>='0'&&__ch<='9'){__x=(__x<<1)+(__x<<3)+(__ch^48);__ch=getchar();}
	__x*=__f;
}
template<class T>void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+48);
}
#define maxn 100010
#define int long long
int n;
struct point{
	int t,w;
	bool operator<(point x)const{
		return t<x.t;
	}
}s[maxn];
priority_queue<int,vector<int>,greater<int> >q;
int ans;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	read(n);
	for(int i=1;i<=n;i++)read(s[i].t),read(s[i].w);
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++)
	if(s[i].t<=q.size()){//没时间了，要反悔了
		if(q.top()<s[i].w){
			ans+=s[i].w-q.top();
			q.pop();
			q.push(s[i].w);
		}
	}else{
		ans+=s[i].w;
		q.push(s[i].w);
	}
	write(ans);
}
```
同样思路的题目[OHHHHH](https://www.luogu.com.cn/problem/P4053)

---

## 作者：EarthGiao (赞：2)

## 【思路】
优先队列 + 贪心    
~~这道题告诉我以后不要相信洛谷标签~~ ……     
标签是单调队列，我硬生生用单调队列写了半个多小时    
终于放弃了单调队列选择了我的条件反射     
优先队列    
然后改了几下就A掉了……   
可能是我太蒻了，不会怎么写单调队列吧     

### 【为什么要用贪心】
~~还好贪心这个标签是正确的~~    
这道题的贪心很显然      
就是在每一个时间点都选择在这个时间点能够做的获得利润最大的策略    
这样就可以由局部最优得到全局最优了    

### 【最终思路】  
那怎么好好的利用贪心呢？    
可以按照时间顺序排一下序    
然后如果优先队列中的元素数量    
小于这个点的时间    
那就直接放入优先队列     
（    
因为这个点的时间之前的每一个时间单位    
都是可以完成一个工作的   
所以如果元素数量小于这个时间   
那就是时间还绰绰有余   
不需要考虑优不优的    
放进去就行    
反正多放一定比少放更优    
）    
反之，    
则想一下    
这一个利润如果比前面某一个时间单位做的工作得到的利润更大    
那如果在那个时间单位做这个工作就会变得更优   
有点反悔的意思      
这个时候队首就是一个最好的被替换的对象    
这很显然就不赘述了    
然后处理完成之后将优先队列里面全部的值加起来就是了      
### 【注意】
优先队列是小根堆的哦    
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int Max = 1000006;
struct node
{
	int t;
	int v;
}a[Max];

bool cmp(const node x,const node y)
{
	return x.t < y.t;
}
priority_queue<int,vector<int>,greater<int> >q;
signed main()
{
//	freopen("work.in","r",stdin);
	int n;	
	cin >> n;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i].t >> a[i].v;
	sort(a + 1,a + 1 + n,cmp);
	int ans = 0;
	for(register int i = 1;i <= n;++ i)
	{
		if(a[i].t > q.size())
		{
			q.push(a[i].v);
			ans += a[i].v;
		}
		else
		{
			if(a[i].v > q.top())
			{
				ans -= q.top();
				q.pop();
				q.push(a[i].v);
				ans += a[i].v;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：kikuss (赞：2)

# Solution
很容易想到按时间从小到大排序,因为它的截止时间越长,我们就可以了把前面的时间去留给其他物品,然后贪心的去选,但是这样会WA,为什么?

看一下这种情况,我们在前面选了价值较小的工作,但是当前有一个价值比它大得多的工作我们却没法选,这个时候就会后悔,所以这是一道可以反悔的贪心题

那么怎么反悔呢?我们用一个小根堆去维护,每次选的工作,我们把它的价值丢进小根堆,如果碰到一个选不了的工作,我们就拿它和堆顶比较,如果比它大,那么堆顶其实没必要选的,所以把它弹出去

具体情况是什么样子的呢?(以下我们用$t$表示工作的截止时间)

因为一个单位时间只能做一个工作,所以堆的元素个数表示至少已经过了$size$个单位时间
```
1. 当前工作的t小于堆的元素个数,说明当前工作已经截止了,不用管
2. 当前工作的t大于堆内元素个数,直接插入
3. 当前工作的t等于堆内元素个数,与堆顶比较,看谁更优
```
欢迎踩博客[real_l](https://www.cnblogs.com/real-l/p/9911297.html)
# Code
```cpp
#include<bits/stdc++.h>
#define in(i) (i=read())
#define il extern inline
#define rg register
#define Min(a,b) ((a)<(b)?(a):(b))
#define Max(a,b) ((a)>(b)?(a):(b))
#define lol long long
using namespace std;

const lol N=1e6+10;

lol read() {
    lol ans=0, f=1; char i=getchar();
    while (i<'0' || i>'9') {if(i=='-') f=-1; i=getchar();}
    while (i>='0' && i<='9') ans=(ans<<1)+(ans<<3)+(i^48), i=getchar();
    return ans*f;
}

struct Node {
    lol day,v;
    bool operator < (const Node &a) const {return day<a.day;}
}t[N];

priority_queue<lol,vector<lol>,greater<lol> >q;

int main()
{
    lol n,ans=0; in(n);
    for (lol i=1;i<=n;i++)
        in(t[i].day), in(t[i].v);
    sort(t+1,t+1+n);
    for (lol i=1;i<=n;i++) {
        if(t[i].day<q.size()) continue;
        else if(t[i].day==q.size()) {
            if(t[i].v>q.top()) {
                ans-=q.top(); q.pop();
                q.push(t[i].v); ans+=t[i].v;
            }
        }else ans+=t[i].v,q.push(t[i].v);
    }cout<<ans<<endl;
}
```

---

## 作者：lijyya (赞：2)

这题考的是**带反悔的贪心**

由贪心的策略得：

先按照时间先后顺序给工作排序

接着从前往后更新答案

当遇到一个时间允许的工作时，答案加上这个工作的价值，把这个工作加入小根堆

当遇到一个时间不允许的工作时，在小根堆中找到一个价值最小的工作，如果小于当前工作的价值，就不做之前的这个工作，然后答案减去这个工作的价值，转而做现在这个工作，答案加上这个工作的价值

对于时间的排序和小根堆的排序关键字，我们可以用友元函数重载运算符：

对于 $sort$，重载 $<$ 运算符，使其按时间从小到大排序

对于 $greater$，重载 $>$ 运算符，使其按价值从大到小排序

代码实现：

```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>

#define LL long long

const int maxn = 1e6 + 10;

struct Node {
	int d, p;
	friend bool operator < (Node x, Node y) {
		return x.d < y.d;
	}
	friend bool operator > (Node x, Node y) {
		return x.p > y.p;
	}
} a[maxn];

using std::priority_queue;
using std::vector;

priority_queue <Node, vector <Node>, std::greater<Node> > q;

int n;
LL ans;

int main() {
	scanf("%d", &n);
	
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].d, &a[i].p);
	}
	
	std::sort(a + 1, a + 1 + n);
	
	for (int i = 1; i <= n; ++i) {
		if (a[i].d > (int)q.size()) {
			ans += a[i].p;
			q.push(a[i]); 
		}
		else {
			if (a[i].p > q.top().p) {
				ans += a[i].p - q.top().p;
				q.pop();
				q.push(a[i]); 
			}
		}
	}
	
	printf("%lld\n", ans);
}
```

---

## 作者：丧黑福造 (赞：2)

$\text{2020.10.28 UPD}$：修改了$markdown$&&润色了语言，使能更清晰的理解思路

------------------------------
## 感谢我的神仙同桌[星棋居](https://www.luogu.com.cn/user/237821)

思路：贪心

与题解里的反悔贪心不同，这里介绍一种不同的贪心。我们先将$D_i$**从大到小**排序。接着我们来想一想，显然，在最理想的状态下，**我们每个工作都可以完成**（$D_i\leqslant 10^5$）。继续分析，将所有$D_i$相同的$P_i$放进$priority$_$queue$里。若$D_{i+1}\ne D_i$，在不考虑$D_i$与$D_{i+1}$的$P_i$大小的前提下，做相同的$D_i$中$P_i$最大的$D_i - D_{i+1}$个工作（剩余的$D_i$的工作一定会与后面的工作发生时间冲突）所以将剩余$D_i$工作的$P_i$先保留在优先队列中，与后面工作的$P_j$比大小，取较大值$\text{ans+=max(P[i],P[j])}$,依次类推。

---------------------
$code$: 
```cpp
#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
struct work {int t, v;} a[100005];//结构体,t表示单位时间；v表示利润
long long ans;//不开long long 见祖宗
priority_queue <int, vector<int> > q;//定义一个小根堆来维护最大v[i]
inline bool cmp(work a, work b) {return a.t > b.t;}//将单位时间从大到小排序

main() {
	int n; scanf ("%d", &n);
	for (register int i = 1; i <= n; i ++) scanf ("%d %d", &a[i].t, &a[i].v);//读入
	sort (a + 1, a + n + 1, cmp); a[n + 1].t = a[n + 1].v = 0;//边界，虽然默认是0，但是要知道
	for (register int i = 1; i <= n; i ++) {
		q.push(a[i].v);
		int c = a[i].t - a[i + 1].t;
		while (!q.empty() && c --) {ans += q.top(); q.pop();}//当优先队列不为空且a[i].t != a[i+1].t时，ans累加
	}
	printf ("%lld\n", ans); return 0;//end
}
```

$Q:$
为什么$ans$累加到$c=0$时优先队列不需要清空？

$A:$
因为需要与后面的$P_j$比较大小，取利润大的

---

## 作者：XL4453 (赞：1)

题目分析：

考虑贪心，不一样的是这个贪心可以反悔。

首先将所有的任务按照时间排序，如果发现在当前任务完成时间前还有空余时间，那就先把这个任务完成了。

如果没有，那就考虑将前面的某一个任务顶替掉，删除那个任务的影响，然后完成当前任务，也就是反悔。

删除那个任务后，由于那个任务的时效已经过了，而且也不可能在顶替掉任何一个任务，所以一定不可能再次考虑，直接删掉就行了。

------------

实现上，用一个优先队列保存已经选了的任务，然后按照上述贪心思路模拟即可。

注意 STL 的优先队列是从大到小的，可以取负数放入或者将其改为从小到大使用。

------------
~~要是我也能反悔就好了。~~

------------
```cpp
#include<algorithm>
#include<cstdio>
#include<queue>
using namespace std;
priority_queue<long long,vector<long long>,greater<long long> > q;
struct node{
	long long d,p;
}num[100005];
bool cmd(node a,node b){
	return a.d<b.d;
}
long long n,now,u;
long long ans;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&num[i].d,&num[i].p);
	sort(num+1,num+n+1,cmd);
	for(int i=1;i<=n;i++){
		if(num[i].d>now)u+=num[i].d-now,now=num[i].d;
		if(u>0){
			u--;
			ans+=num[i].p;
			q.push(num[i].p);
		}
		else{
			if(q.top()<num[i].p){
				ans-=q.top();
				q.pop();
				ans+=num[i].p;
				q.push(num[i].p);
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：nth_element (赞：1)

想要更丰富的展示，请移步[我的Blog](https://www.cnblogs.com/nth-element/p/11785043.html)

***

若想要深入学习反悔贪心，[传送门]( https://www.cnblogs.com/nth-element/p/11768155.html )。

***

**Description**:

有 $n$ 项工作，每 $i$ 项工作有一个截止时间 $D_i$ ，完成每项工作可以得到利润 $P_i$ ，求最大可以得到多少利润。

**Method**:

做这道题的时候并没有想到反悔贪心，只是想到一个错误的贪心算法。按照截止时间为第一关键字，利润为第二关键字排序，统计一遍即可。

显然上面的贪心算法刻印被Hack掉。可以先不选择当前截止时间的利润，等一下选择下一个更大的利润，这样可以得到更大的最优解。

但我们发现这个贪心策略错误的原因是当前的最优解可能不是全局最优解，显然符合反悔贪心的思想。于是我们用一个反悔堆维护最优解。

假如满足题设条件（即没有超出截止时间）就分成两种情况：若当前的最优解比原来的最优解（堆顶）更优秀，我们就更新全局最优解，把原来的最优解丢出去，再把当前的最优解放进去（即反悔策略）；反之，就不管了。假如不满足特设条件，就把当前的最优解丢进堆里，更新全局最优解即可。

**Code**:

```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 100010
inline void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
using namespace std;
int n;
struct node
{
    int D,P;
    bool operator <(const node &x)const
    {
        return D<x.D;
    }
}job[Maxn];
priority_queue<int,vector<int>,greater<int> >qu;
signed main()
{
    //	freopen("Job.in","r",stdin);
    //	freopen("Job.out","w",stdout);
    read(n);
    for(int i=1;i<=n;i++)
    {
        read(job[i].D),read(job[i].P);
    }
    sort(job+1,job+n+1);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(qu.size()>=job[i].D)//符合条件
        {
            if(qu.top()<job[i].P)//当前的最优解比原来的最优解（堆顶）更优秀
            {
                ans-=qu.top();//更新全局最优解
                qu.pop();//把原来的最优解丢出去
                qu.push(job[i].P);//把当前的最优解放进去
                ans+=job[i].P;//更新全局最优解
            }
        }else//不符合条件
        {
            qu.push(job[i].P);//把当前的最优解丢进堆里
            ans+=job[i].P;//更新全局最优解
        }
    }
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：D愚者 (赞：1)

- 前言：

	今天校内oj的比赛题目；
	
    这题是贪心+优先队列；
------------
- 思路：
	
    先用截止日期为关键字排序
	
    枚举1到n，分两种情况讨论：用cnt记录选了几个工作；
    ```cpp
	1.当cnt小于当前枚举到的数（用i表示）的截止日期时：
		将i的价值加到ans里，并把当前价值入队（要转为小根堆）
		if(cnt!=e[i].d){
			cnt++;
			q.push(-e[i].p);//转为小根堆
			ans+=e[i].p;
		}
   	2.当cnt等于当前枚举到的数（用i表示）的截止日期时：
    	如果i的价值比队首大，那么就替换掉队首，这也是为什么要转成小根堆的原因
      	else{
			int k=-q.top();//小根堆，堆顶
			if(k<e[i].p){
				q.pop();
				ans+=e[i].p-k;//替换
				q.push(-e[i].p);//入队
			}
		}  
	```

------------
- 代码：
    ```cpp
    #include<cstdio>
    #include<queue>
    #include<algorithm>
    using namespace std;
    int n;
    long long ans,cnt;
    priority_queue<int> q;
    struct node{
        int d,p;
    }e[100010];
    bool cmp(node a,node b){
        return a.d<b.d;
    }
    int main(){
    //	freopen("study.in","r",stdin);
    //	freopen("study.out","w",stdout);
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d %d",&e[i].d,&e[i].p);
        sort(e+1,e+1+n,cmp);
        for(int i=1;i<=n;i++){
            if(cnt!=e[i].d){
                cnt++;
                q.push(-e[i].p);
                ans+=e[i].p;
            }
            else{
                int k=-q.top();
                if(k<e[i].p){
                    q.pop();
                    ans+=e[i].p-k;
                    q.push(-e[i].p);
                }
            }
        }
        printf("%lld",ans);
        return 0;
    }
    ```


------------
- 提醒：注意储存时转为小根堆（~~惨痛的教训~~）

---

## 作者：WaKing (赞：1)

算法：贪心加二叉树

贪心策略：在一个工作不超过截止日期前，尽量晚做，对于每个时间t，保证不超出截至时间的前提下，尽量做利润前t高的。综上所述，我们可以依次扫描每个工作，动态维护满足上性质的计划。

具体思路：

建立一个初始为空的小空堆（节点权值为工作利润）， 把工作按截止时间排序，开始扫描；

1.若当前工作的截止时间t等于当前堆中的节点（第n个节点代表第n个单位时间做的工作的利润）个数，则说明此方案下，前t个单位时间已经安排了t个工作。此时，若此工作利润大于堆顶权值（当前计划的最低利润），那么将当前工作替换掉堆顶。

2.若当前工作的截止时间大于堆中的计划工作个数，直接把其插入堆。

代码如下：
```cpp
#include <bits/stdc++.h>
#define SIZE 1000005
#define int long long
using namespace std;
inline int read(){int k = 0, d = 1; char ch = getchar();
	while(ch != '-' && (ch > '9' || ch < '0')) ch = getchar();
	if(ch == '-') d = -1, ch = getchar();
	while(ch >= '0' && ch <= '9') k = k * 10 + ch - '0', ch = getchar(); return k * d;}
void write(int x){
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');}
struct N{int di, pi;}work[SIZE];
bool cmp(N a, N b){return a.di < b.di;}
int n = read(), heap[SIZE], p, ans;
void up(int p){
	while(p > 1){
		if(heap[p] < heap[p >> 1]){
			swap(heap[p], heap[p >> 1]);
			p >>= 1;}
		else break;}}
void Insert(int val){
	heap[++ p] = val;
	up(p);}
int GetTop(){return heap[1];}
void down(int w){
	int s = w << 1;
	while(s <= p){
		if(s < p && heap[s] > heap[s + 1]) s ++;
		if(heap[s] < heap[w]){
			swap(heap[s], heap[w]);
			w = s; s <<= 1;
		}
		else break;
	}
}
void Extract(){
	heap[1] = heap[p --];
	down(1);
}
int del(){
	int ret = heap[1], father = 1, son = father << 1;
    if(son + 1 < p && heap[son + 1] < heap[son]) son ++;
    while(son < p && heap[son] < heap[p])
    {
        heap[father] = heap[son];
        father = son;
        son = father << 1;
        if(son + 1 < p && heap[son + 1] < heap[son])
        son++;}
    heap[father] = heap[p];
    p --;
    return ret;}
signed main(){
	for(int w = 0; w < n; ++ w){work[w].di = read(), work[w].pi = read();}
	sort(work, work + n, cmp);
	for(int w = 0; w < n; ++ w){
		if(p < work[w].di){Insert(work[w].pi); ans += work[w].pi;}
		else{
			if(work[w].pi > heap[1]){Insert(work[w].pi); ans += work[w].pi - del();}}}
	write(ans);
}

```

---

## 作者：_lfxxx_ (赞：1)

**题目传送门：[P2949 [USACO09OPEN]Work Scheduling G](https://www.luogu.com.cn/problem/P2949)**
### 题意：
有 $N$ 个工作。对于第 $i$ 个工作，如果你在截止时间 $D_i$ 前做完，你可以获利 $P_i$ ，问你最多能获利多少。
### 思路：
仔细一看，唉，跟[P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)，[UVA1316 Supermarket](https://www.luogu.com.cn/problem/UVA1316)和[P3093 [USACO13DEC]Milk Scheduling S](https://www.luogu.com.cn/problem/P3093)很像~~四倍经验~~。

其实已经有很多大佬讲过小根堆的思路了，这里我在具体讲一下。

先假设所有工作都能做即利润都能拿到，然后将工作按时间升序排序。

然后开始遍历工作。如果还有时间做，就将该工作放进堆，否则，将该工作与堆中最小利润的工作比（这也是为什么要用小跟堆的原因）。

如果利润大一些，将该工作放进堆，那个利润低的拿出来，同时将拿出来的工作的利润扣除。

否则，就不入堆，再将该工作的利润扣除。
### 注意事项：
定义堆时注意不要定义成 `priority_queue<int,vector<int>,greater<int>>q;` 这样，否则最后的两个大于号会被认为是位运算。

正确的写法：
`priority_queue<int,vector<int>,greater<int> >q;` .

~~不开~~**`long long`**~~见祖宗~~
### 代码：
```cpp
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
priority_queue<int,vector<int>,greater<int> >q;
struct thing{int s,t;}a[100005];//不要问我为什么是s和t
inline bool cmp(thing a,thing b){
	return a.t<b.t;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n;
	long long m=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].t>>a[i].s;
		m+=a[i].s;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
	    if(a[i].t>q.size())//这里读者可以好好想想为什么这样写就是有时间做
			q.push(a[i].s);
	    else if(q.top()<a[i].s){
			m-=q.top();
	    	q.pop();
	    	q.push(a[i].s);
		}
	    else
            m-=a[i].s;
	}
	cout<<m<<endl;
	return 0;
}
```
时间复杂度： $O(NlogN)$ ，足以通过 $10^5$ 的数据。

~~赶紧去拿四倍经验吧~~
### 更新：
`2021-05-31`：更正了两处错别字。

---

## 作者：Otomachi_Una_ (赞：0)

本题为可反悔的贪心。

首先最多有 $10^5$ 个任务，而时间上限达到 $10^9$，我们可近似认为时间为无限。

按截止时间的先后进行排序，如果时间足够就先做截止时间短的，后将其价格压入一个小根堆内，如果时间不够看看堆顶的价格若比其小，则放弃堆顶所代表的工作，去做价值更高的工作。

## Code
```
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=1e5+5;
int n;
int z=0,ans=0;//现工作时间
struct work{
	int t,p;
}a[MAXN];
bool cmp(work u,work v){
	return u.t<v.t;
}
priority_queue<int> Q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].t>>a[i].p;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].t>z){
			Q.push(-a[i].p);
			ans+=a[i].p;
			z++;
		}
		else if(!Q.empty()&&-Q.top()<a[i].p){
			int k=-Q.top();
			ans+=(a[i].p-k);
			Q.pop();
			Q.push(-a[i].p);
		}
	}
	cout<<ans;
}
```


---

## 作者：Mars_Dingdang (赞：0)

本题是一道经典的贪心，用决策包容性求解，方法多样。

## 题目大意
有 $n$ 个商品，每个商品有利润 $p_i$ 和过期时间 $d_i$，每天只能卖一个商品，过期商品不能卖， 求如何安排每天卖的商品，使得利润最大。

## 大体思路
先来看一道弱化版：[UVA1316](https://www.luogu.com.cn/problem/UVA1316)。此题中 $1\le n,p_i,d_i\le 10^4$。一种显而易见的贪心策略是将利润从大到小排序，对于每个商品，在其过期之前尽可能晚地卖出。这样，该商品对其他商品具有“决策包容性”。

换句话说，对于利润为 $p$ 的商品，将其尽可能晚卖出。若其在 $d$ 时刻卖出，则 $d$ 时刻卖出其他商品利润显然小于 $p$，而该商品在 $d$ 时刻卖出对全局造成的影响最小，因此尽可能晚。

于是，我们用并查集维护时刻，起初每一天构成一个集合。对于每个商品，若其在 $d_i$ 天后过期，则查询 $r=root(d_i)$，如果 $r>0$ 则在第 $r$ 天卖出，并合并 $r$ 与 $r-1$，即令 $father(r)\leftarrow r-1$。

其本质是用并查集维护数组中位置的占用情况，时间复杂度 $O(n\log n+n\alpha(n))$，空间复杂度 $O(d)$。

__________

然而，对于本题 $p,d\le 10^9$，$O(d)$ 的空间复杂度显然不可行，因此考虑另一种贪心方法：按时间从小到大排序，并保证前 $d$ 天在不卖出过期商品的前提下卖出价值前 $d$ 大的商品。

具体地，将商品按 $d$ 从小到大排序，然后以商品价值为权值建立一个初始为空的小根堆。对于排序后第 $i$ 个商品，若 $d_i$ 比堆内元素数量大，即该商品能够在前 $d_i$ 天被售出，因此答案累加 $p_i$ 并将其入堆。否则，将 $p_i$ 与 $top$ 进行比较，若 $p_i$ 大则将 $top$ 弹出，并压入 $p_i$，更新答案。

最终，堆内商品价值之和即为答案。时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

## 代码
```cpp
typedef pair<int, int> PII;
PII p[maxn];
int n; ll ans;
priority_queue <int, vector<int>, greater<int> > q; //小根堆
int main () {
	read(n);
	rep(i, 1, n){
		read(p[i].first);
		read(p[i].second);
	}
	sort(p + 1, p + n + 1);//输入+排序
	rep(i, 1, n) {
		int d = p[i].first, w = p[i].second;
		if(d > q.size()) q.push(w), ans += w;
        //若有空位直接入堆
		else {
			int v = q.top();//否则与堆顶比较
			if(v < w) {
				q.pop(); ans -= v;
				q.push(w); ans += w;
			}
		}
	}
	writeln(ans);
	return 0;
}
```

---

## 作者：Doqin07 (赞：0)

## 一道反悔类贪心

 1. 先按照截至时间排序
 2. 我们接下来需要思考第 $i$ 项工作做还是不做，首先一个前提若其截止时间符合条件，就与队中最小元素（用优先队列维护）比较，若第 $i$ 项工作较高，那么就反悔，选择去做当前的工作。

#### Code:

```cpp
/*Coder:DongYinuo*/
#include <bits/stdc++.h>
using namespace std;
namespace I_Love_{
    typedef long long ll;
    const int maxn=100005;
    const int N=1005;
    const int mod=1e9+7;
    #define F(i,l,r) for (int i=l;i<=r;++i)
    #define REP(i,r,l) for (int i=r;i>=l;--i)
    #define mem(a,b) memset(a,b,sizeof(a));
    #define MP make_pair
    #define PB push_back
    #define PII pair<int,int>
    #define PLL pair<ll,ll>
    #define all(a) a.begin(),a.end()
    #define sz(a) a.size()
    #define lson ind*2 
    #define rson ind*2+1
    int I(){char c;int x=0,f=1;while(c=getchar()){if(c=='-')f=-1;if(isdigit(c))break;}while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();return x*f;}
    template <typename T>void Rd(T& arg){arg=I();}
    template <typename T,typename...Types>void Rd(T& arg,Types&...args){arg=I();Rd(args...);}
    priority_queue<ll,vector<ll>,greater<ll>> q;
    struct Info{
        ll dead,val;
    };
    Info a[maxn];
    bool cmp(Info x,Info y){
        return x.dead<y.dead;
    }
    ll n,ans;
    void run(){
        scanf("%lld",&n);
        F(i,1,n){
            scanf("%lld%lld",&a[i].dead,&a[i].val);
        }
        sort(a+1,a+1+n,cmp);
        F(i,1,n){
            if(a[i].dead<=q.size()){
                if(q.top()<a[i].val){
                    ans+=a[i].val-q.top();
                    q.pop();
                    q.push(a[i].val);
                }
            }else{
                ans+=a[i].val;
                q.push(a[i].val);
            }
        }
        printf("%lld\n",ans);
    }
    void OI(){
        run();
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif
    I_Love_::OI();
    return 0;
}
```



---

## 作者：KGV7 (赞：0)

好像我跟前面大佬的“后悔法”长得有点像但又不一样，于是发一波供大家参考（//▽//）

按时间倒着排序，DDL大的放前面，然后每一轮把DDL的相同的扔进优先队列里（权值大的在队首），之后从后往前枚举时间点进行贪心。

考虑到每从优先队列取出一个元素就需要将DDL相同的元素的DDL减一（同一个时间点只能干一项工作），这个可能可以用数据结构操作...吧◔ ‸◔？。但是可以想一个偷懒的方法--记录当前考虑到的时间cur，没取出一个元素就cur--，减到跟下一轮DDL为止（因为再取出的话就要考虑下一轮DDL的元素）。

大概就是这样......
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1e6+4;
int n;
ll sum;
struct Node {
	int v,t;
	friend bool operator <(const Node x,const Node y) {
		return x.v<y.v;
	}
}a[N];
priority_queue<Node> q;
bool cmp(const Node x,const Node y) {
	return x.t>y.t||(x.t==y.t&&x.v>y.v);
}
inline int read() {
	int x=0;char c=getchar();
	while (c<'0'||c>'9') c=getchar();
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x; 
}
int main() {
//	freopen("in.txt","r",stdin);
	n=read();
	for (register int i=1;i<=n;++i)
		a[i].t=read(),a[i].v=read();
	sort(a+1,a+n+1,cmp);
	int cur=a[1].t,i=1;
	while (1) {
		while (a[i].t==cur)
			q.push(a[i]),++i;
		while (!q.empty()&&a[i].t<cur) {
			sum+=q.top().v;
			q.pop();
			--cur;
		}
		if (i>n) break;
		cur=min(a[i].t,cur);
	}
	printf("%lld\n",sum);
	return 0;
}
```


---

## 作者：wsk_1202 (赞：0)

算法：贪心。

把截止时间从小到大排序，对我们选择完成的工作的利润维护一个小根堆。

从 $1$ 到 $n$ 扫，能完成当前工作就完成，并将该工作的利润插入小根堆中；

如果不能完成，判断该工作的利润是否大于我们选择完成的工作的最小利润（小根堆堆顶）。

如果大于则替换掉原最小利润工作，否则无操作（也就是不选它）。

代码实现如下。

```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;//利润可能会爆int
inline ll rd()//读入优化
{
	ll x=0,p=1;
	char a=getchar();
	while((a<48||a>57)&&a!='-')a=getchar();
	if(a=='-')p=-p,a=getchar();
	while(a>47&&a<58)
	{
		x=(x<<1)+(x<<3)+(a&15);
		a=getchar();
	}
	return x*p;
}
struct node//用结构体存储每一项工作，并重载小于号运算符，方便排序
{
	ll t,p;
	bool operator < (const node &y)const
	{
		return t<y.t;//按截止时间从小到大排
	}
}a[100002];
ll n,time,ans;
priority_queue <ll,vector<ll>,greater<ll> > q;//小根堆，使用优先队列实现
int main()
{
	n=rd();
	for(int i=1;i<=n;i++)
	{
		a[i].t=rd();a[i].p=rd();
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(time<a[i].t)//如果可以完成，暂时认为完成它会得到最大利润，并将它插入堆
		{
			time++;
			ans+=a[i].p;
			q.push(a[i].p);
		}
		else if(a[i].p>q.top())//若不能完成，则把它与堆顶元素比较；如果完成这个工作的利润较大，就将原来的替换
		{
			ans-=q.top();ans+=a[i].p;
			q.pop();q.push(a[i].p);
		}
	}
	printf("%lld\n",ans);//输出答案
	return 0;
}
```

---

## 作者：Randolph、 (赞：0)

[P2949 [USACO09OPEN]工作调度Work Scheduling](https://www.luogu.org/problemnew/show/P2949)

~~题目标签是单调队列+dp，萌新太弱不会~~

明显的一道贪心题，考虑排序先做截止时间早的，但我们发现后面可能会出现价值更高却没有时间做的情况

**我们需要反悔的操作**

于是我们想到用堆，如果当前放不下且当前价值高于已做工作中的最小价值，则删去它加入当前值

**类似用堆实现反悔的贪心的经典题目：[P1484 种树](https://www.luogu.org/problemnew/show/P1484)**


```cpp
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
struct thing {
    int t,v;
    bool operator <(const thing &b)const {
        return v>b.v;//小根堆
    }
} a[100005];
inline bool cmp(thing a,thing b) {
    return a.t<b.t;
}
int n;
long long ans;
priority_queue<thing> q;
int main() {
    scanf("%d",&n);
    for (int i=1; i<=n; i++) scanf("%d%d",&a[i].t,&a[i].v);
    sort(a+1,a+n+1,cmp);
    for (int i=1; i<=n; i++)
        if (a[i].t<=q.size()) {
            if (q.top().v<a[i].v) ans+=a[i].v-q.top().v,q.pop(),q.push(a[i]);
        } else q.push(a[i]),ans+=a[i].v;
    printf("%lld",ans);
}
```


---

