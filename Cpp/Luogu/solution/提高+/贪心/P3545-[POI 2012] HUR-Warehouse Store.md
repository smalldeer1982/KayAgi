# [POI 2012] HUR-Warehouse Store

## 题目描述

现在有 $n$ 天。第 $i$ 天上午会进货 $A_i$ 件商品，中午的时候会有顾客需要购买 $B_i$ 件商品，可以选择满足顾客的要求，或是无视掉他。

如果要满足顾客的需求，就必须要有足够的库存。问最多能够满足多少个顾客的需求。

## 说明/提示

对于 $100\%$ 的数据，$1\leqslant n\leqslant 2.5\times 10^5$，$0\leqslant a_i,b_i \leqslant 10^9$。

## 样例 #1

### 输入

```
6
2 2 1 2 1 0
1 2 2 3 4 4```

### 输出

```
3
1 2 4```

# 题解

## 作者：小手冰凉 (赞：30)

这题的做法是贪心



很明显可以发现，当能卖时就卖是一个十分好的贪心策略


但是会有一种情况例外，就是前面有一个很大的人要买，以至于后面的一群人都不能买了


所以可以用堆维护一下在之前买的人最大是多少，如果当前的人买不了，而堆中最大比当前大就把那个人换成现在这个，如果现在的最大比之前还大显然换了更加不优。




```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=250005;
int n;
int a[N],b[N];
struct xxx{
    int k,t;
}heap[N];
bool com(xxx a,xxx b)
{
    return a.t<b.t;
}
bool comm(xxx a,xxx b)
{
    return a.k<b.k;
}
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&b[i]);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    int t=0;
    int k=0;
    memset(heap,0,sizeof(heap));
    make_heap(heap+1,heap+t+1,com);
    for(int i=1;i<=n;i++){
//        cout<<heap[1].t<<' '<<heap[1].k<<endl;
        k+=b[i];
        if(a[i]<=k){//贪心
            k-=a[i];
            t++;
            heap[t].t=a[i];
            heap[t].k=i;
            push_heap(heap+1,heap+t+1,com);
        }
        else if(heap[1].t>=a[i]){//用堆维护，将之前的解改的更优
            k+=heap[1].t;
            k-=a[i];
            pop_heap(heap+1,heap+t+1,com);
            heap[t].t=a[i];
            heap[t].k=i;
            push_heap(heap+1,heap+t+1,com);
        }
    }
    sort(heap+1,heap+t+1,comm);
    printf("%d\n",t);
    for(int i=1;i<=t;i++){
        printf("%d ",heap[i].k);
    }
    return 0;
}
```

---

## 作者：Macesuted (赞：24)

[题面](https://www.luogu.com.cn/problem/P3545)

## 题意

题目中给出两个数组 $A[]$ 和 $B[]$ ，你拥有一个存货数量，在第 $i$ 天的上午会加上 $A_i$ ，下午你可以选择减少 $B_i$ 的存货来满足一个顾客的要求。问 $n$ 天内你最多能满足多少顾客。

## 做法

我们先尽可能满足所有我们遇到的顾客，并且使用一个大根堆存放所有你当前满足过的顾客的信息。当我们遇到一个我们无法直接满足的顾客，如果大根堆的堆顶的 $B_i$ 小于当前的 $B_i$ ，我们尝试取出大根堆的堆顶，将它删除并且将它的 $B_i$ 加入你的存货数量中，然后你继续满足这一位顾客。

## 算法正确性证明

由于我们前提条件中有“大根堆堆顶的 $B_i$ 大于当前的 $B_i$ ”，如果我们不满足大根堆堆顶的顾客（即当前方案下所有我们满足的顾客中 $B_i$ 最大的），我们一定是能够用取消堆顶的顾客所拿来的库存来满足当前顾客的，所以我们满足的顾客数量不降，并且你手头上的存货数量还有可能上升，也对答案有正面影响。所以不满足堆顶，满足当前项在这样的情况下是满足贪心的局部最优的。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=250005;

typedef pair<long long,int> pii;

long long a[maxn],b[maxn];
bool vis[maxn];//记录是否满足每一位顾客

priority_queue<pii,vector<pii>,less<pii> > que;

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	for(int i=1;i<=n;i++) scanf("%lld",b+i);
	long long tot=0,cnt=0;
	for(int i=1;i<=n;i++)
	{
		tot+=a[i];
		if(tot<b[i]&&!que.empty()&&que.top().first>b[i])
		{//若无法满足当前顾客并且堆顶更贵的情况
			vis[que.top().second]=false;
			tot+=que.top().first;//删除堆顶
			que.pop();
			cnt--;
		}
		if(tot>=b[i])
		{
			tot-=b[i];
			que.push((pii){b[i],i});
			vis[i]=true;//加入当前点
			cnt++;
		}
	}
	printf("%lld\n",cnt);
	for(int i=1;i<=n;i++)
		if(vis[i]) printf("%d ",i);
	puts("");
	return 0;
}
```

---

## 作者：John_yangliwu (赞：10)

## 思路
贪心反悔+优先队列。

直接贪心显然是不行的。 如果我们每一天能卖就卖，反之不卖，就能被以下数据卡掉：

```cpp
10
9 0 0 0 0 0 0 0 0 0
9 1 1 1 1 1 1 1 1 1
```
按以上算法， 第一天就会卖掉 $9$ 件商品，本来可以放弃第一天获取更大的收益，结果却目光短浅地把所有库存卖给了需求最高的客户。所以我们需要设计一种正确的贪心方法：

首先开一个 $vis$ 数组，$vis_i=true$ 表示满足了客户 $i$，反之没有满足。
用 $sum$ 表示现有的库存，初始为 $0$，第 $i$ 天 $sum$ 加上 $a_i$。

1. 跟错误算法一样，对于客户 $i$，首先能卖就卖，且把 $vis_i$ 置为 $true$；反之不卖（**贪心**）。
2. 若今天的客户 $i$ 满足不了，即 $sum<b_i$，那就找到满足过的，即 $vis_j=true$，且 $b_j$ 最大的客户 $j\ (1\le j<i)$，若 $b_j>b_i$，那么，就用卖给客户 $j$ 的商品去满足客户 $i$，即把 $vis_j$ 置为 $false$，$vis_i$ 置为 $true$，$sum$ 加上 $b_j-b_i$。显然，放弃满足 $b_j$ 较高的客户 $j$，去满足 $b_i$ 较低的客户 $i$，能获得更大的收益（**反悔**）。

那么，如何高效地实现找出在客户 $i$ 之前满足过的 $b_j$ 最大的客户 $j$ 呢？

我们发现，**优先队列**可以胜任。对于每个满足过的客户 $j\ (1\le j<i)$，维护客户的需求 $b_j$ 以及来的时间 $j$，就可以用 $O(1)$ 的复杂度查找 $\max\limits_{1\le j<i}{b_j}$，以及用 $O(\log n)$ 的复杂度删除，其中 $i$ 为天数。

## Tips
$0\le a_i, b_i \le 10^9$，随便加一加就溢出，所以开 long long。

## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 250005;
ll a[MAXN], b[MAXN];
int n;

struct node {//客户的结构体，来的时间与需求
	int id;
	ll v;
	bool operator < (const node& x) const {
		return v < x.v;
	}
	bool operator > (const node& x) const {
		return v > x.v;
	}

};

priority_queue<node, vector<node>, less<node> > q;
bool vis[MAXN];//客户满足情况
int ans;

int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) cin >> b[i];
	ll sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += a[i];
		if(sum >= b[i]) {//能满足，直接卖
			sum -= b[i];
			vis[i] = 1;
			q.push(node{i, b[i]});
			++ans;
		}
		else {
			if(!q.empty() && q.top().v > b[i]) {//满足不了，但是满足过需求更高的客户，把卖出去的退回来！
				vis[q.top().id] = 0;
				vis[i] = 1;
				sum += q.top().v - b[i];
				q.pop();
				q.push(node{i, b[i]});
			}
		}
	}
	
	cout << ans << endl;
	for(int i = 1; i <= n; i++) {
		if(vis[i]) cout << i << ' ';
	}
	
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/45740332)

---
$\large\text{THE\ \ END}$

---

## 作者：UhhhQQQU (赞：8)

###### 我的第一篇紫题题解~~~

好了，回归正题

当我们一看到这个题目的时候，我们会先想到什么呢？

本蒟蒻就想到了~~我擦！这是紫题！~~用暴力每一天能否完成订单来解决这个问题。但当以下数据出现时···

```
6
5 0 0 0 0 0
5 1 1 1 1 1
```
显然，面对这种数据时暴力肯定是错的。

然后本蒟蒻又想到了~~看一下题解吧！就看一下！~~dfs解决。但数据范围极大，会T掉（$2^{250000}$）。

so，我们只有重看题目，找一找关键词了。

然后眼瞎的我才发现
>最多能满足几天中顾客的需求

>↑ ↑

这不是贪心吗QAQ（请原谅我的视力）

所以根据~~脑洞~~贪心的思想，我们有以下思路：

1、将当前所拥有的商品件数统计出来，枚举每天的订单是否能完成（听我说完！这不是暴力！QAQ）
	
   i、如果能，将当前所拥有的商品减去顾客所要的商品。然后把这个订单放进~~垃圾桶~~里。
    
   ii、如果不能，则在~~垃圾桶~~中找到以前订单之中**所需**的商品件数最大的一个订单，然后与当前的这个订单比较，如果当前订单**所需**的商品件数，比找出来的订单的**所需**商品件数要少，则~~把刚翻出来的订单扔出机房窗外，刚接到的订单放在垃圾桶里~~（贪心思想）。
   
这里可能又有julao在问了：

>为什么可以处理的订单不扔出窗外，而是放在垃圾桶里呢？

本蒟蒻答：

>其实后面有一个在垃圾桶中找订单的操作，而是要找所需商品件数最大的，所以显然这个垃圾桶应该是一个二叉堆，优化一下程序。（机房的垃圾桶都这么高级？QAQ）

思路梳理：贪心思想+二叉堆优化。

上代码~~~↓

```
#include<cstdio>
#include<queue>
using namespace std;
struct shangpin{
	long long a,b;
}day[250010];
priority_queue<shangpin> ans2;
long long n,zongshu,ansl;
bool operator <(const shangpin &x,const shangpin &y)
{
	return x.a<y.a;
}
inline void read(long long &x)
{
	char ch;
	for(ch=getchar(),x=0;ch<'0'||ch>'9';ch=getchar());
	for(;ch>='0'&&ch<='9';x=(x<<3)+(x<<1)+(ch^48),ch=getchar());
}
inline void write(int x)
{
	if(x>=10)write(x/10);
	putchar(x%10+48);
}
int main()
{
	read(n);
	for(register long long i=1;i<=n;i++)read(day[i].a);
	for(register long long i=1;i<=n;i++)
	{
		read(day[i].b);
		zongshu+=day[i].a;
		if(day[i].b<=zongshu)
		{
			zongshu-=day[i].b;
			++ans1;
			shangpin tmp={day[i].b,i};
			ans2.push(tmp);
		}
		else if(!ans2.empty()&&ans2.top().a>day[i].b)
		{
			zongshu+=ans2.top().a-day[i].b;
			ans2.pop();
			shangpin tmp={day[i].b,i};
			ans2.push(tmp);
		}
	}
	write(ans1),putchar('\n');
    while(!ans2.empty())write(ans2.top().b),putchar(' '),ans2.pop();
}
```
（请不要抄蒟蒻的代码QAQ，这里是有防伪哒~~~）

---

## 作者：genshy (赞：7)

# 这是一道很经典的贪心题

### 贪心策略：当能满足当前所有人时满足当前所有人。

但当不能满足时，就会出现错误。

那我们怎么保证贪心的正确行呢？

当我们不能满足时，我们可以看看前面的人，看看满足这个人是不是更优。

假如，当前这个人要比前面买的最多的人都要多，那我们可以不买给

这个人，以此来留下更多的商品，满足剩下的人。

如果比前面买的最多的人都要少，说明满足这个人要更优，

因为他可以剩下更多的商品，来满足剩下的人。

那我们就可以考虑维护一个大跟堆，每次把人的序号和他买的商品数

加入堆中，然后按照上述方法维护就行了。

### 几个注意的点

1. 在删除大根堆堆顶时，一定要判断这个堆是否为空。否则就会疯狂RE

1. 一定要开 long long（~~不开long long见祖宗~~）

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define LL long long
using namespace std;
LL n,ans;
LL a[300010],b[300010];
bool vis[300010];
priority_queue<pair<LL,int>, vector< pair<LL,int> > >q;//维护一个大根堆
int main()
{
	scanf("%lld",&n); LL rest = 0;
	for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
	for(int i = 1; i <= n; i++) scanf("%lld",&b[i]);
	for(int i = 1; i <= n; i++)
	{
		rest += a[i];
		if(b[i] <= rest)//剩下的商品数，要比这个人买的要多，则可以满足
		{
			ans++;
			q.push(make_pair(b[i],i));
			rest -= b[i];//rest存剩下的商品数
			vis[i] = 1;
		}
		else if(!q.empty() && b[i] < q.top().first)//一定要判堆是否为空
		{
            int t = q.top().second; q.pop();//去掉不优的堆顶
            rest += b[t]; rest -= b[i];
            vis[t] = 0, vis[i] = 1;//对要买的商品打标急
            q.push(make_pair(b[i],i));
		}
	}
	printf("%lld\n",ans);
	for(int i = 1; i <= n; i++) if(vis[i]) printf("%d ",i);
	return 0;
}
```
###  ENDING


---

## 作者：Tarsal (赞：2)

以下题解为本人拿到题目的思维过程，可以仔细阅读，如果只想看正解的可以从第三段开始阅读。

[P3545 [POI2012]HUR-Warehouse Store](https://www.luogu.com.cn/problem/P3545)

---

首先，我们看到题目先会想到 $01$ 背包。是个正确的作法，但是肯定过不了。

然后，我们考虑到这一定是个贪心/推式子的题目。

但是推式子的题目一般的特性在这里显然不符合(推式子的题目一般不会让你选择)

那接下来考虑怎么去贪心。

第一想法是我们选最小的肯定是最优的，因为就算选了这个最小的而导致其他的不可以选，那也最多只能导致一个不可以选。

因为如果可以导致多个不可以选的话，选了次小的哪一个也会导致更多的不可以选。

所以选择最小的策略是对的，$sort$ 一般的复杂度我们也可以接受，但是问题来了，我们那些数可以取？

取完当前最小的，那么它前面的一些数说不定不可以再去。

那么处理这些的复杂度就不稳定了，可以构造数据卡掉。

---

接下来我们想每天上午进的货物会对什么有影响。

这个很显然，它可以对他后面的所有数产生影响，因为到货了就可以卖给别人了。

那是不是可以这么考虑，从后往前去跑，每次去当前可以取的最小的。

因为从后完全就去除了它的后效性，所有正确性也是对的。

但是新增一个数 $A_i$ 可能很大，一次可以处理多个数。

那你就必须保证后面整个序列是有序的，而且还要维护一个后缀和。

我们考虑维护这个有序数列的复杂度最优，那就是往前加一个数，就把这个数加入到数列里面去。

这样的复杂度最劣是 $O(n^2)$ 的，还是会炸。

---

那我们是不是无法从一些顺序上去找到优化的空间。

我们就可以考虑去莽，然后支持撤销，这样也可以保证正确性。

具体的话是这样实现的：

从前往后读入，每次可以取就取，并且把这些取过的记录在单调队列中。

如果当前这个放不下，我们就把他和队列首的元素做比较，不断更新即可。

根据我们的第二个想法，每个前面取过的如果弹出来，因为他的后效性，肯定是可以服务后面的。

那么就结束了。

### $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 250010;
int n, sum, ans, book[maxn];
priority_queue<pair<int, int>, vector<pair<int, int> > > Q;
struct node {
    int a, b, id;
} e[maxn];
int cmp(node x, node y) {
    return x.b < y.b;
}
signed main() {
    scanf("%lld", &n);
    for(int i = 1; i <= n; ++ i) {
        scanf("%lld", &e[i].a);
        e[i].id = i;
    }
    for(int i = 1; i <= n; ++ i) {
        scanf("%lld", &e[i].b);
    }
    for(int i = 1; i <= n; ++ i) {
        sum += e[i].a;
        if(e[i].b < sum) {
            Q.push(make_pair(e[i].b, e[i].id));
            ++ ans;
            book[i] = 1;
            sum -= e[i].b;
        }
        else if(! Q.empty() && Q.top().first > e[i].b) {
            book[Q.top().second] = 0;
            book[i] = 1;
            sum += e[Q.top().second].b - e[i].b;
            Q.pop(); Q.push(make_pair(e[i].b, e[i].id));
        }
    }
    printf("%lld\n", ans);
    for(int i = 1; i <= n; ++ i) {
        if(book[i]) {
            printf("%d ", i);
        }
    }
    return 0;
}
```

Ps:本人知道题解前不应该放错误作法，但是觉得这些错误作法也是一些解题的思路，这里用不上，其他地方可能用到上，望批准。

---

## 作者：7KByte (赞：2)

还没有线段树的题解，我来发一篇。


根据套路，考虑贪心。


显然我们应该优先选择买的数量少的客户，因为所有客户对答案的贡献都是$1$，数量少的客户可以以更小的代价对答案产生贡献。


**定义**$:\operatorname{Sum_i}=\sum\limits_{j=1}^ia_j$

考虑到货物可以囤积，显然只要$\mathrm{Sum_{i}}\ge b_i$即可搞定第$i$个人。


搞定第$i$个人会对消耗掉$b_i$个货物，这将使$\operatorname{Sum_i}\cdots\operatorname{Sum_n}$减少$b_i$。

但同时考虑到$Sum_i$非负，所以选第$i$个人之前要查询$\operatorname{Sum_i}\cdots\operatorname{Sum_n}$是否都大于$b_i$。

所以我们只用维护一个支持区间修改和区间查询最小值的线段树即可。


$Code:\mathrm{O(N\ log\ N)}$
```cpp
#include<bits/stdc++.h>
#define int long long 
#define N 250005
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
struct node{
	int l,r,val,add;
}a[N<<2];
#define ls (x<<1)
#define rs (ls|1)
#define A a[x].add
#define L a[x].l
#define R a[x].r
#define S a[x].val
struct point{
	int val,day;
	bool operator<(const point o)const{
		if(val^o.val)return val<o.val;
		return day<o.day;
	}
}b[N];
int s[N],n;
void updata(int x){
	S=min(a[ls].val,a[rs].val)+A;
}
void build(int x,int l,int r){
	L=l;R=r;A=0;
	if(l==r){
		S=s[l];return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	updata(x);
}
void pushup(int x,int val){
	S+=val;A+=val;
}
void down(int x){
	if(!A)return;
	pushup(ls,A);pushup(rs,A);A=0;
}
void change(int x,int l,int r,int val){
	if(L>=l&&R<=r)pushup(x,val);
	else{
		down(x);
		int mid=(L+R)>>1;
		if(mid>=l)change(ls,l,r,val);
		if(mid<r)change(rs,l,r,val);
		updata(x);
	}
}
int ask(int x,int l,int r){
	if(L>=l&&R<=r)return S;
	down(x);
	int mid=(L+R)>>1,mn=0x7fffffffffffffff;
	if(mid>=l)mn=min(mn,ask(ls,l,r));
	if(mid<r)mn=min(mn,ask(rs,l,r));
	return mn;
}
int ans;
vector<int>ed;
//Program by Inf_Voltage
signed main(){
	scanf("%lld",&n);
	rep(i,1,n)scanf("%lld",&s[i]),s[i]+=s[i-1];
	build(1,1,n);
	rep(i,1,n)scanf("%lld",&b[i].val),b[i].day=i;
	sort(b+1,b+n+1);
	rep(i,1,n){
		int x=b[i].val,y=b[i].day;
		if(ask(1,y,n)>=x){
			ans++;ed.push_back(y);
			change(1,y,n,-x);
		}
	}
	printf("%lld\n",ans);
	sort(ed.begin(),ed.end());
	for(int i=0;i<ed.size();i++)printf("%lld ",ed[i]);
	putchar('\n');
	return 0;
}
```

---

## 作者：123hh2 (赞：1)

--->[传送门](https://www.luogu.com.cn/problem/P3545)

---

### 题目大意

在 $n(1 \le n \le 250000)$ 天中，给你每天商品的进货量和每天可能的出货量，求出最多能满足多少天的可能的出货量和对应的时间，商品可以累积

---

### 思路

一眼贪心

先建一个大根堆用来存可能的商品出货量和对应的时间，正序枚举天数。

对于第 $i$ 天，首先先考虑当前货物是否能满足当前可能的出货量的需求：如果满足就可以直接进堆，不满足的话就将当前可能的出货量与堆顶作比较，贪心的将较小的可能的出货量加入堆，再将大的踢出来，以便以后能更好的满足其他天数的出货量

代码中有详细的注释

---

### 代码

```cpp
#include<bits/stdc++.h>
#define in inline
#define ri register
#define int long long int 
#define _123hh2 0
using namespace std;
in int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
in void write(int x)
{
    if(x<0) {x=-x;putchar('-');}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int maxn=250001;
int awa[maxn];//用来存每天的进货量
bool vis[maxn];//标记能满足哪天的出货量
priority_queue<pair<int,int> > q;//大根堆，用 pair 存第 i 天的出货量
signed main()
{
    cin.tie(NULL);cout.tie(NULL);
    int n=read(),sum=0;
    for(ri int i=1;i<=n;i++) awa[i]=read();
    for(ri int i=1;i<=n;i++)
    {
        sum+=awa[i];//当前库存的货物
        int x=read();
        if(sum>=x) q.push(make_pair(x,i)),vis[i]=1,sum-=x;//如果满足就可以直接进堆
        else
        {
            if(q.empty()) continue;//这里得判断一下，可能当前库存比要求出货量小，并且堆为空，这时直接弃掉当天的选择
            if(q.top().first>x)//堆顶比第 i 天出货量大，让小的进堆，大的出堆
            {
                vis[q.top().second]=0;//之前的商品不出了，标成0
                vis[i]=1;//出当前的商品，标为1
                sum+=q.top().first,sum-=x;//别忘了更新一下当前的库存商品
                q.pop();q.push(make_pair(x,i));
            }
        }
    }
    write(q.size()),puts("");//现在堆的大小就是能出商品的最大天数
    for(ri int i=1;i<=n;i++) if(vis[i]) cout<<i<<" ";//依次将标记的天数输出出来
    return _123hh2;
}
```


---

## 作者：Tgotp (赞：1)

题解清一色的优先队列...

我用了并查集+树状数组...

看到题就容易想到最小的肯定最先选.

同时要满足当前剩余的前ｉ个必须至少剩下这么多

树状数组维护即可.

c++代码如下：
```
#include<bits/stdc++.h>
#define rep(i,x,y) for(register int i = x;i <= y; ++ i)
#define repd(i,x,y) for(register int i = x;i >= y; -- i)
typedef long long ll;
using namespace std;
template<typename T>inline void read(T&x)
{
	char c;int sign = 1;x = 0;
	do { c = getchar(); if(c =='-') sign = -1; }while(!isdigit(c));
	do { x = x * 10 + c - '0'; c = getchar(); }while(isdigit(c));
	x *= sign;
}

const int N = 3e5 + 50;
int id[N],a[N],n;
ll t[N];
const bool cmp(int x,int y) { return a[x] < a[y]; }
#define lowbit(x) (x & -x)
inline void add(int x,int w)
{
	if(!x) return;
	for(register int i = x;i <= n; i += lowbit(i))
		t[i] += w;
}
inline ll find(int x)
{
	ll ans = 0;
	for(register int i = x; i ; i -= lowbit(i))
		ans += t[i];
	return ans;
}

int p[N];
int get_fa(int x) { return p[x] == x ? x : p[x]=get_fa(p[x]); }
int ans[N],num;

int main()
{
	freopen("6.in","r",stdin);
	read(n);
	rep(i,1,n)
	{
		int x;
		read(x);
		add(i,x);
	}
	rep(i,1,n)
	{
		read(a[i]);
		id[i] = i; p[i] = i;
	}
	sort(id+1,id+1+n,cmp);
	rep(i,1,n)
		if(find(id[i]) >= a[id[i]])
		{
			ans[++num] = id[i];
			int j = id[i],w = a[id[i]];
			while(w)
			{
				j = get_fa(j);	
				int k = find(j)-find(j-1);
				add(j,max(-w,-k));
				if(w >= k) p[j] = j-1;
				w = max(0,w-k);
			}
		}
	printf("%d\n",num);
	sort(ans+1,ans+1+num);
	rep(i,1,num) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：小塘空明 (赞：1)

   一开始我看到这题时，下意识反应。哇，水题，能取就取不就行了。
  
   但很明显，当前面存在一个很大的数时，可能让后面许多不能买。
  
   但我们不必更换贪心策略 ~~否则你怎么贪心~~ 考虑动态维护前面已经选择买了的物品的集合。
   
   我们依旧选择能买就买，假设你不能买了，你考虑当前物品的价格是否低于已经买了的物品的最高价格，如果低于则替换，对余额进行更新。
   
   合法性我也不会很严谨的证明。但显然在最优选择下我们无法同时买下这两件商品，而选择买下便宜的会让我们有更多的余额买剩下的商品。
   
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
typedef long long ll;
const ll size=3e5+10;
struct node{ll a,b;}c[size];
priority_queue<node> q;
ll n,ans,res;
bool operator<(const node&a,const node&b){return a.a<b.a;}
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(ll i=1;i<=n;i++) c[i].a=read();
	for(ll i=1;i<=n;i++) c[i].b=read();
	for(ll i=1;i<=n;i++){
		res+=c[i].a;
		if(res>=c[i].b){
			node now;res-=c[i].b;ans++;
			now.a=c[i].b;now.b=i;q.push(now);
		}
		else{
			if(q.size()&&q.top().a>c[i].b){
				res+=q.top().a-c[i].b;
				node now;q.pop();
				now.a=c[i].b;now.b=i;q.push(now);
			}
		}
	}
	printf("%lld\n",ans);
	while(q.size()){
		printf("%lld ",q.top().b);q.pop();
	}
	return 0;
}
```


---

## 作者：Yajnun (赞：0)

贪心

第i天进的货只能给第i天及以后的人

反着跑一遍，每天都把尽可能多的货给后面尽可能多的人
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#define maxn 2000005
#define ll long long
#define for(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

struct node{int v,id;
bool operator <(const node y)const
	{return v>y.v;}};
ll a[maxn],b[maxn],ans[maxn],n,m; 
priority_queue<node>q;
void pre()
{
	scanf("%d",&n);
	for(i,1,n)scanf("%d",&a[n-i+1]);
	for(i,1,n)scanf("%d",&b[n-i+1]);
}

int main()
{
	pre();
	int len=0;ll sum=0;
	for(i,1,n)
	{
	q.push((node){b[i],n-i+1});
		while(!q.empty()&&a[i]>=q.top().v)
		{	
		    a[i]-=q.top().v;
		    ans[++len]=q.top().id;
			q.pop() ;
		 }
		if(!q.empty()){node t;t.v=q.top().v-a[i];t.id=q.top().id;q.pop();q.push(t);}
	}
	printf("%d\n",len);
	sort(ans+1,ans+len+1);
	for(i,1,len)printf("%d ",ans[i]);
	return 0;
}




---

