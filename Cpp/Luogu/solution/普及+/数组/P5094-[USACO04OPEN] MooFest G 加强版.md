# [USACO04OPEN] MooFest G 加强版

## 题目描述

每一年，约翰的 $ N $ 只奶牛参加奶牛狂欢节。这是一个全世界奶牛都参加的大联欢。狂欢节包括很多有趣的活动，比如干草堆叠大赛、跳牛栏大赛，奶牛之间有时还相互扎屁股取乐。当然，她们会排成一列嚎叫，来欢庆她们的节日。奶牛们的叫声实在刺耳，以致于每只奶牛的听力都受到不同程度的损伤。现在告诉你奶牛 $ i $ 的听力为 $ v_i $ ，这表示如果奶牛 $ j $ 想说点什么让她听到，必须用高于 $ v_i \times dis(i,j) $ 的音量。因此，如果奶牛 $ i $ 和 $ j $ 想相互交谈，她们的音量必须不小于 $ \max (v_i,v_j) \times dis(i,j) $。其中 $ dis(i,j) $ 表示她们间的距离。

现在 $ N $ 只奶牛都站在一条直线上了，每只奶牛还有一个坐标 $ x_i $。如果每对奶牛都在交谈，并且使用最小音量，那所有 $ N(N-1)/2 $ 对奶牛间谈话的音量之和为多少？

## 说明/提示

### 数据范围

因为原数据下 $O(N^2)$ 算法可以通过，所以新添加了一些增强数据。

原数据作为子任务 $1$，新添加的数据作为子任务 $2$。

- 子任务 $1$（$1$ 分）：$1 \leq N,V_i,x_i \leq 2 \times 10^4$。
- 子任务 $2$（$99$ 分）：$1 \leq N,V_i,x_i \leq 5 \times 10^4$。

## 样例 #1

### 输入

```
4
3 1
2 5
2 6
4 3```

### 输出

```
57```

# 题解

## 作者：一只书虫仔 (赞：42)

#### Description

> 给定两个长度为 $n$ 的序列 $v_i,x_i$，定义一个点对 $(i,j)$（$i \ne j$）的价值 $f(i,j)$ 为 $\max(v_i,v_j) \times |x_i-x_j|$，求：
> $$\sum\limits_{i=1}^n \sum\limits_{j=1}^n f(i,j)[i \ne j]$$

#### Solution

很难想象这只是一个绿题，可能拿树状数组做会舒服一点吧，这里介绍分治做法。

我们把 $\displaystyle \sum\limits_{i=1}^n \sum\limits_{j=1}^n f(i,j)[i \ne j]$ 先拆成 $\displaystyle \sum\limits_{i=1}^n\sum\limits_{j=1}^n \max(v_i,v_j)[i \ne j]$ 和 $\displaystyle \sum\limits_{i=1}^n \sum\limits_{j=1}^n |x_i-x_j|[i \ne j]$，看看分别怎么计算：

- $\displaystyle \sum\limits_{i=1}^n\sum\limits_{j=1}^n \max(v_i,v_j)[i \ne j]$ 我们把 $v_i$ 升序排列一下，那么第 $i$ 个数的贡献即为前 $i-1$ 个数。
- $\displaystyle \sum\limits_{i=1}^n \sum\limits_{j=1}^n |x_i-x_j|[i \ne j]$ 我们把 $x_i$ 升序排列一下，那么定 $j$ 为右端点，下面这一段就可以如下化简：

$$\begin{aligned}\sum\limits_{i=1}^{j-1}|x_i-x_j|&=\sum\limits_{i=1}^{j-1}x_j-x_i\\&=\sum\limits_{i=1}^{j-1}x_j -\sum\limits_{i=1}^{j-1}x_i\\&=x_j \times (j-1)-sum_{j-1}\end{aligned}$$

其中 $sum_i$ 为前缀和。

那把这两个融合起来怎么搞呢？我们可以用结构体输入这两个序列，以 $v$ 为第一关键字先把序列进行排序。

现在对于区间 $[l,r]$ 计算他的贡献，这一段区间的 $v$ 是已经排好序的，所以考虑分治，将区间分为两半 $[l,mid]$ 和 $[mid+1,r]$，可以通过递归算出贡献在 $[l,mid]$ 的和贡献在 $[mid+1,r]$ 的，接下来要算的就是有贡献的跨越这两个区间的。

我们在 $[mid+1,r]$ 中枚举 $j$ 作为贡献的右界，算 $[l,j]$ 的贡献，并将其加起来作为跨区间的贡献和。将其分拆为 $v$ 和 $x$ 两部分计算：

- $v$，既然排过序了那么全部都是 $v_j$。
- $x$，其中 $[l,j]$ 的贡献会有一个位置 $i$ 使得 $i$ 是最后一个 $a_i(x) \le a_j(x)$ 的，那么区间 $[l,j]$ 的贡献就可以如下计算（$sumx_{[l,r]}$ 为 $a_{[l,r]}(x)$ 的和）：

$$\begin{aligned}x_j-x_l+x_j-x_{l+1}+\cdots+x_j-x_i+x_{i+1}-x_j+\cdots+x_{mid}-x_j&=\sum\limits_{k=l}^i x_j-x_k+\sum\limits_{k=i+1}^{mid} x_k-x_j\\&=\sum\limits_{k=l}^i x_j-\sum\limits_{k=l}^i x_k+\sum\limits_{k=i+1}^{mid} x_k-\sum\limits_{k=i+1}^{mid} x_j\\&=x_j \times (i-l+1)-sumx_{[l,i]}+sumx_{[i+1,mid]}-x_j \times (mid -i)\end{aligned}$$

通过预处理前缀和这个是可以 $\mathcal O(1)$ 求的，也就是对于一个 $j$，他对答案的贡献为：

$$v_j \times (x_j \times (i-l+1)-sumx_{[l,i]}+sumx_{[i+1,mid]}-x_j \times (mid -i))$$

但注意，能将其如上计算的前提是 $[l,mid]$ 和 $[mid+1,r]$ 分别按照 $x$ 进行排序。

我们都知道有归并排序，所以可以处理完上面这些之后再将 $[l,r]$ 以 $x$ 为关键字排一下序。我们不用在处理答案前排序的原因应该很简单，因为有递归函数帮我们处理 $[l,mid]$ 和 $[mid+1,r]$ 的顺序问题，只需要为 $[l,r]$ 外面的区间服务即可。

代码放的是处理贡献的部分。

#### Code

```cpp
int mid = (l + r) / 2;
solve(l, mid);
solve(mid + 1, r);
memset(sum, 0, sizeof(sum));
for (int i = l; i <= r; i++) sum[i] = sum[i - 1] + a[i].x;
int i = l - 1;
for (int j = mid + 1; j <= r; j++) {
	while (a[i + 1].x <= a[j].x && i < mid)
		i++;
	ans += a[j].v * ((i - l + 1) * a[j].x - sum[i] + sum[mid] - sum[i] - (mid - i) * a[j].x);
}
```

---

## 作者：Laser_Crystal (赞：30)

$emmm……$貌似没有题解是在$StudyingFather$增加$Subtask2$之后发的……

~~毒瘤StudyingFather，还我的n方过百万~~

最近scw妹子在补习数据结构，看到学妹的题单里正好有数据结构的题目，于是水几题发篇题解qwq

**总体思路：**

1. 对奶牛们的音量进行排序
2. 维护两个树状数组，分别表示第 i 头奶牛前坐标是小于$x_i$的数量和坐标之和。**树状数组的长度是整个坐标系的长度。**
3. 推式子，$\Delta ans_i=i\text{之前所有的相对于}x_i\text{的距离的绝对值}*v_i$（想一想，为什么可以这么做？）
4. 计算出3
5. 输出完事了

如何推导出3的式子是个难点，具体看代码吧：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct cow{ll v,pos;}a[50004];
ll n;
inline bool cmp(cow x,cow y){return x.v<y.v;}
ll Cnt[50004],Sum[50004];
inline ll lowbit(ll x){return x&(-x);}
inline void add_cnt(ll p,ll x){for(ll i=p; i<50004; i+=lowbit(i)) Cnt[i]+=x;}
inline void add_sum(ll p,ll x){for(ll i=p; i<50004; i+=lowbit(i)) Sum[i]+=x;}
inline ll count_cnt(ll p){ll total=0;for(ll i=p; i>0; i-=lowbit(i)) total+=Cnt[i];return total;}
inline ll count_sum(ll p){ll total=0;for(ll i=p; i>0; i-=lowbit(i)) total+=Sum[i];return total;}
//真的没有过度压行啊啊啊
//cnt数组表示前i头奶牛坐标小于当前奶牛坐标的数量，sum数组表示当前奶牛前i头奶牛坐标小于当前奶牛坐标之和
//有点点绕qwq
int main()
{
    cin>>n;
    for(register ll i=1; i<=n; i++) cin>>a[i].v>>a[i].pos;
    sort(a+1,a+n+1,cmp);
    ll ans=0,z=0;
    for(register ll i=1; i<=n; i++)
    {
        ll cnt=count_cnt(a[i].pos),sum=count_sum(a[i].pos);
        ans+=(cnt*a[i].pos-sum)*a[i].v;//坐标小于i的和
        ans+=((z-sum)-(i-1-cnt)*a[i].pos)*a[i].v;//坐标大于i的和，z是当前坐标总和
        //ans+=((cnt*a[i].pos-sum)+((z-sum)-(i-1-cnt)*a[i].pos))*a[i].v;--->这里是合并后的大公式，但是难理解
        add_cnt(a[i].pos,1);add_sum(a[i].pos,a[i].pos);
        z+=a[i].pos;
    }
    cout<<ans<<endl;
    return 0;
}
```
嗯……就是这样子辣，scw妹子很菜的，希望大家能指出她的错误qwq

---

## 作者：EDqwq (赞：20)

#### 非常可爱的树状数组题

***

### 思路：

第一眼看去，这个柿子里面比较难解决的是$max$，如何解决它呢？

类似一月月赛T2的思想，对它的$v$值进行一次从小到大的排序，对于计算一个位置前面的值，只需要取当前位置的$v$值即可。

接下来是处理$dis(i,j)$，这个东西麻烦在带一个绝对值，如何去掉这个绝对值呢？

我们可以分两种情况计算：$x_i > x_j$， $x_i < x_j$。

对于$x_i > x_j$我们需要统计$i$前面的所有数$j$满足$x_i > x_j$的$x_j$的和，然后用满足条件的$j$的个数乘$x_i$减去这个和就是答案了。

所以我们要维护两个树状数组，一个维护在这个$x_i$前面，有多少小于它的$x_j$。另一个维护在$x_i$前面，小于它的$x_j$的和。

对于我们到达的一个$i$，只需要对这两个树状数组的$x_i$位置，一个加1（个数），一个加$x_i$（求和）即可。

那对于$x_i < x_j$怎么处理呢？

我们已经知道了在$x_i$前面，坐标小于它的坐标和，那我们维护一个前缀和，即可知道大于它的坐标和。

同理，我们也已经知道了在$x_i$前面，坐标小于它的坐标的个数，那我们当然也可以知道坐标大于它的个数。用在$x_i$前面，坐标大于$x_i$的坐标和，减去坐标大于它的个数乘以$x_i$就是答案了。

最后记得统计完答案要乘以$v_i$。

***

### 代码

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x) memset(x,0,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

struct node{
	int v;
	int x;
}a[1000010];

int n;
int tree1[1000010];
int tree2[1000010];
int ans;
int summ;
const int nn = 50000;

bool cmp(node x,node y){
	return x.v < y.v;
}

int lowbit(int x){
	return x & -x;
}

void update1(int i,int x){
	for(;i <= nn;i += lowbit(i))tree1[i] += x;
}

int query1(int x){
	int s = 0;
	for(;x;x -= lowbit(x))s += tree1[x];
	return s;
}

void update2(int i,int x){
	for(;i <= nn;i += lowbit(i))tree2[i] += x;
}

int query2(int x){
	int s = 0;
	for(;x;x -= lowbit(x))s += tree2[x];
	return s;
}

signed main(){
	cin>>n;
	for(int i = 1;i <= n;i ++)a[i].v = read(),a[i].x = read();
	sort(a + 1,a + n + 1,cmp);
	for(int i = 1;i <= n;i ++){
		int num = query1(a[i].x);
		int sum = query2(a[i].x);
		ans += (num * a[i].x - sum) * a[i].v;//小于它
		ans += ((summ - sum) - (i - num - 1) * a[i].x) * a[i].v;//大于它
		update1(a[i].x,1);//更新
		update2(a[i].x,a[i].x);
		summ += a[i].x;//前缀和
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Martini (赞：8)

那啥......这里是刚碰信息2个月的萌新！！！
但是看到题解里只有暴力和树状数组两种思路///
那就给大家看一种二分的思路吧www
虽然常数大了点（？ 而且代码也烦了点emm
但我就是不想开两个BIT！！！



------------
思路就是很简单的二分吧
先按照x从小到大排序（直接stl快排就完事了
然后用归并排序按照v从大到小排 一边排一边可以计算答案了。
因为每次合并两个区间的时候左区间的x都比右区间的x要小的 所以每次合并的时候 找到两边第一个（也就是最大的）元素中更大的一个，计算它此时对答案的贡献的时候只需要考虑另一个区间剩余元素的和就行了 也就不用像BIT里那样考虑哪些x比它小哪些x比它大 就比较舒服~
剩下就不多说了吧 由于是真的萌新所以代码习惯并不好......直接上代码吧///
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ans=0;
int n;
const int maxn=5e5+5;
int v[maxn],x[maxn];
int y[maxn],id[maxn];

bool cmpx(int i,int j){return x[i]<x[j];}

ll msort(int l,int r){
	int la=l;
	if (l==r) return x[id[l]];
	int mid=(l+r)>>1;
	ll lsm = msort(l,mid);
	ll rsm = msort(mid+1,r);
	ll lm = lsm,rm = rsm;
	int midd=mid;
	int tot = l;
	while (l<=midd && mid+1<=r){
		if (v[id[l]] >= v[id[mid+1]]){
			ans += v[id[l]]*(rm-x[id[l]]*(r-mid)); 
			lm -= x[id[l]];
			y[tot++]=id[l++];	
		}
		else {
			ans += v[id[mid+1]]*(x[id[mid+1]]*(midd-l+1)-lm);
			rm -= x[id[mid+1]];
			y[tot++]=id[++mid];
		}
	}
	if (l<=midd)
		for (int i=l;i<=midd;i++)
			y[tot++]=id[i];
	else for (int i=mid+1;i<=r;i++) y[tot++]=id[i];
	for (int i=la;i<=r;i++){
		id[i]=y[i];	
	}
	return lsm+rsm;
}
 
int main(){
	cin >> n;
	for (int i=1;i<=n;i++){
		id[i]=i;
		cin >> v[i] >> x[i];
	}
	sort(id+1,id+n+1,cmpx);
	ll sm=msort(1,n);
	cout << ans;
	return 0;
}
```
有什么好一点的修改方法也求大佬指教吧///

---

## 作者：genshy (赞：6)



看到大部分题解里都是用树状数组写的，所以今天我就水一发线段树的题解。

其实也挺好写的，不用建树，只需要一个单点修改和区间查询。

时间复杂度 $O(nlogn)$ ，但是不知道为什么会比 树状数组慢 $30ms$ .

可能是树状数组常数比较小吧。

**sloution**：

我们要求的是 $\displaystyle\sum_{i=1}^{n}\sum_{j=i+1}^{n} max(v_i,v_j) \times dis(i,j)$

考虑到有最大值和距离不好同时处理，我们可以枚举一下最大值。

也就是说我们按听力从小到大排一下序，处理前面的点和他的贡献。

我们开一个权值线段树维护每个坐标出现的次数以及每个坐标的和。

然后统计 $x$ 的答案的时候，就在线段树上统计出比 $x$ 的坐标小的数个数 $num1$，以及坐标和 $sum1$。

在统计出比 $x$ 坐标大的数的个数 $num2$ 以及坐标和 $sum2$。

这个点对答案的贡献就是 $num1 \times v[x] - sum1 + sum2 - num2 \times v[x]$

在依次计算出每个点的贡献就可以。

**线段树版**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 50010;
int n;
long long ans;
struct node
{
	int x,v;
}e[50010];
struct Tree
{
	int sum,tag;
}tr[N<<2];
#define sum(o) tr[o].sum
#define tag(o) tr[o].tag
inline int read()
{
	int s = 0,w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
	return s * w;
}
bool comp(node a,node b){ return a.v < b.v;}
void up(int o)
{
	sum(o) = sum(o<<1) + sum(o<<1|1);
	tag(o) = tag(o<<1) + tag(o<<1|1);
}
void chenge(int o,int l,int r,int x,int val)
{
	if(l == r)
	{
		tag(o)++;
		sum(o) += val;
		return;
	}
	int mid = (l + r)>>1;
	if(x <= mid) chenge(o<<1,l,mid,x,val);
	if(x > mid) chenge(o<<1|1,mid+1,r,x,val);
	up(o);
}
pair<int,int> query(int o,int l,int r,int L,int R)
{
	int sum = 0, num = 0;
	if(L <= l && R >= r) return make_pair(sum(o),tag(o));
	int mid = (l + r)>>1;
	if(L <= mid)
	{
		pair<int,int> kk = query(o<<1,l,mid,L,R);
		sum += kk.first;
		num += kk.second;
	}
	if(R > mid)
	{
		pair<int,int> kk = query(o<<1|1,mid+1,r,L,R);
		sum += kk.first;
		num += kk.second;
	}
	return make_pair(sum,num);
}
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		e[i].v = read();
		e[i].x = read();
	}
	sort(e+1,e+n+1,comp);
	for(int i = 1; i <= n; i++)
	{
		pair<int,int> kk = query(1,1,N-5,1,e[i].x);
		ans += 1LL * e[i].v * (kk.second * e[i].x - kk.first);
		kk = query(1,1,N-5,e[i].x+1,N-5);
		ans += 1LL * e[i].v * (kk.first - kk.second * e[i].x);
		chenge(1,1,N-5,e[i].x,e[i].x);
	}
	printf("%lld\n",ans);
	return 0;
}
```

**树状数组版**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 50010;
int n,t1[N],t2[N];
long long ans;
struct node
{
	int x,v;
}e[50010];
inline int read()
{
	int s = 0,w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + ch - '0'; ch = getchar();}
	return s * w;
}
bool comp(node a,node b){ return a.v < b.v;}
int lowbit(int x){ return x & -x; }
void chenge(int x,int val)
{
	for(; x <= N-5; x += lowbit(x)) t1[x] += val;
}
void modify(int x,int val)
{
	for(; x <= N-5; x += lowbit(x)) t2[x] += val;
}
int query_num(int x)
{
	int res = 0;
	for(; x; x -= lowbit(x)) res += t1[x];
	return res;
}
int query_sum(int x)
{
	int sum = 0;
	for(; x; x -= lowbit(x)) sum += t2[x];
	return sum;
}
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
	{
		e[i].v = read();
		e[i].x = read();
	}
	sort(e+1,e+n+1,comp);
	for(int i = 1; i <= n; i++)
	{
		int num = query_num(e[i].x);
		int sum = query_sum(e[i].x);
		ans += 1LL * e[i].v * (num * e[i].x - sum);
		num = query_num(N-5) - query_num(e[i].x);
		sum = query_sum(N-5) - query_sum(e[i].x);
		ans += 1LL * e[i].v * (sum - num * e[i].x);
		chenge(e[i].x,1);
		modify(e[i].x,e[i].x);
	}
	printf("%lld\n",ans);
	return 0;
}
```





---

## 作者：白いバラの夜 (赞：6)

题目大意：n只奶牛，第i只听力为vi，坐标为xi，两只奶牛聊天时音量是max(vi,vj)∗abs(xi−xj)。求n(n−1)/2对奶牛的音量和题目大意：n只奶牛，第i只听力为vi，坐标为xi，两只奶牛聊天时音量是max(vi,vj)∗abs(xi−xj)。求n(n−1)/2对奶牛的音量和

表示很想问黑题是什么鬼。

思路：经验告诉我们，有比较的题就先排序…… 
按照x轴从大到小排序，这样用树状数组维护坐标就行了 
对于绝对值，可以拆成正负分别计算，因此还需要维护一个区间数量

我的收获：排序大法吼，比较先排序

代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long int ll;
const int MAX_N=20000;
struct node {
	int v,x;
} a[MAX_N+5];
ll n,num[MAX_N+5],cnt,sum[MAX_N+5],ans,tot;
inline ll read() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') {
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
bool cmp(node x,node y) {
	return x.v>y.v;
}
void add(ll x,ll v,ll k) {
	for(ll i=x; i<=MAX_N; i+=i&(-i)) {
		sum[i]+=v;
		num[i]+=k;
	}
}
void query(ll x) {
	for(ll i=x; i>0; i-=i&(-i)) {
		tot+=sum[i];
		cnt+=num[i];
	}
}
int main() {
	n=read();
	for(ll i=1; i<=n; i++) {
		a[i].v=read(),a[i].x=read();
	}
	sort(a+1,a+n+1,cmp);
	for(ll i=1; i<=n; i++) {
		add(a[i].x,a[i].x,1);
	}
	for(ll i=1; i<=n; i++) {
		tot=cnt=0;
		query(a[i].x);
		ans+=a[i].v*(cnt*a[i].x-tot);
		cnt=-cnt,tot=-tot;
		query(MAX_N);
		ans+=a[i].v*(tot-cnt*a[i].x);
		add(a[i].x,-a[i].x,-1);
	}
	printf("%lld",ans);
	return 0;
}
/*
4
3 1
2 5
2 6
4 3

57
*/
```

---

## 作者：06ray (赞：5)

### 难度:普及-

### 直接n方暴力就能水过。

#### 先按奶牛的听力值从小到大排序，然后在暴力枚举每个奶牛排序后之前的奶牛，累加它们坐标的绝对值之差乘这个奶牛的听力值，就是最终的答案。

#### 话不多说，上代码

```
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
struct node{
	int x,y;
}a[50100];//用结构体存入每个奶牛的坐标和听力值，方便排序
bool cmp(node a,node b)
{
	return a.x<b.x;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);//以奶牛的听力值从小到大排序
	long long ans=0;
	for(int i=2; i<=n; i++)
	{
		for(int j=1; j<i; j++)
		{
			ans+=a[i].x*abs(a[i].y-a[j].y);//累加
		}
	}
	cout<<ans;
	return 0;
}
```

~~话说是谁把它评到黑色的~~

---

## 作者：Fairicle (赞：4)

对于这种题容易想到用树状数组去维护。（以下将简写**树状数组**为 **BIT**）

我们发现这个 $max$ 不好处理，如果枚举只能 $O(N^2)$ 做。那么我们考虑排序，从大到小进行贡献的统计。

具体操作为：

建立两个 BIT，一个为 $c_0$ 维护元素个数，一个为 $c_1$ 维护位置和。那么我们统计到排序后的 $i$ 号奶牛时，贡献就是

$$v_i*(backsum-backnum*x_i+prenum*x_i-presum)$$

$backnum,backnum$ 分别代表位置在 $i$ 号奶牛后面的奶牛数和后面奶牛的位置和。$prenum,presum$ 同理。这些可以通过前面的两个 BIT 维护。

计算完贡献后，为避免重复计算，将 $i$ 从两个 BIT 中删除即可。

code：
```cpp
#define ll long long
#define ri register int
ll n,c[N][2],maxn=50000,ans;
inline int lowbit(int x){return x&(-x);}
inline void add(int x,int v,int op){
	for(ri i=x;i<=maxn;i+=lowbit(i)) c[i][op]+=v;
}
inline ll query(int x,int op){
	ll ans=0;
	for(ri i=x;i>0;i-=lowbit(i)) ans+=c[i][op];return ans;
}
struct node{
	ll v,x;
}a[N];
inline bool cmp(node a,node b){return a.v>b.v;}
int main(){
	n=rd();
	for(ri i=1;i<=n;++i) a[i].v=rd(),a[i].x=rd(),add(a[i].x,1,0),add(a[i].x,a[i].x,1);
	sort(a+1,a+1+n,cmp);
	for(ri i=1;i<=n;++i){
		ll pre_num=query(a[i].x-1,0),back_num=query(maxn,0)-query(a[i].x,0),pre_sum=query(a[i].x-1,1),back_sum=query(maxn,1)-query(a[i].x,1);
		ans+=a[i].v*(back_sum-back_num*a[i].x+pre_num*a[i].x-pre_sum);
		add(a[i].x,-1,0),add(a[i].x,-a[i].x,1);
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：船医 (赞：4)

一个树状数组题，有一定思维量。

树状数组c1用来维护听力为i的牛对应的位置和的前缀和,c2则用来维护听力为i的牛数目的前缀和。


把原数列正反都做一次，这样每次只需要统计比自己听力低的牛的结果就行。


代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=50005;
struct cow{
	long long v,p;
	bool operator<(const cow& c) const{
		return p<c.p;
	}
}a[N];
long long n,m,lb[N],c1[N],c2[N],caozuo,p,q,u,ans;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}//快读，其实没有必要，导致TLE的是下面一个地方的死循环
void add1(long long x,long long y)
{
	while(x<=N)//是N，因为树状数组长度并不是n，下面同理
	{
        c1[x]+=y;
        x+=lb[x];
	}
}
void add2(long long x,long long y)
{
    while(x<=N)
	{
        c2[x]+=y;
        x+=lb[x];
	}
}
long long sum1(long long x){
	long long res=0;
	if (x==0)
	{
		return 0;
	}
	for (;x>0;x-=lb[x])
	{
		res+=c1[x];
	}
	return res;
}
long long sum2(long long x){
	long long res=0;
	if (x==0)
	{
		return 0;
	}
	for (;x>0;x-=lb[x])
	{
		res+=c2[x];
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=N;i++)//注意这里要是N，不然会在add里加0导致死循环TLE
   {
      lb[i]=i&(-i);
   }
	for(long long i=1;i<=n;i++)
	{
		a[i].v=read();
		a[i].p=read();
	}
	sort(a+1,a+n+1);//先按位置sort一遍。sort结构体在上面重载了运算符
	for (long long i=1;i<=n;i++){
		long long der=a[i].p*sum2(a[i].v)-sum1(a[i].v);
		ans+=der*a[i].v;
		add1(a[i].v,a[i].p);
		add2(a[i].v,1);//c2每次++
	}
	for(long long i=1;i<=N;i++)
	{
		c1[i]=0;
		c2[i]=0;
	}
	for (long long i=n;i>=1;i--){
		long long der=sum1(a[i].v-1)-a[i].p*sum2(a[i].v-1);
		ans+=der*a[i].v;
		add1(a[i].v,a[i].p);
		add2(a[i].v,1);
	}
	cout<<ans;
	return 0;
}
```

![](https://cdn.luogu.com.cn/upload/pic/62225.png)![](https://cdn.luogu.com.cn/upload/pic/62225.png)祝大家熟练运用树状数组！

---

## 作者：STPGUY (赞：4)

# [MooFest](https://www.luogu.com.cn/problem/P5094)
## 题目大意：
求：

$$
\sum_{i=1}^n\sum_{j=1}^n\max(v_i,v_j)dis(i,j)
$$

## 分析

其实我们发现这个$\max$十分不好维护

就是说，如果已经保证了$v_i\ge v_j$，那么原式可以写为

$$
\sum_{i=1}^nv_i\sum_{j=1}^ndis(i,j)
$$

这个按照$v_i$从大到小就可以了吧

那么就是$\sum_{j=i+1}^ndis(i,j)$的问题了

这个看看数据，这个大概是需要一个$\log$的复杂度

那么发现像什么线段树，树状数组之类的~~高级~~数据结构就可以维护

就分成两种情况，一种是$x_p>x_i$的，一种是$x_p < x_i$的

那就分别求和，那么就可以写成这样$sum\{x_p[x_p>x_i]\}-cnt\{[x_p>x_i]\}*x_i+cnt\{[x_p<x_i]\}*x_i-sum\{x_p[x_p<x_i]\}$

## 细节
这个用了一个十分易懂的方式来维护

那就是先按照$x_i$从小到大排序

用树状数组一个点一个点插入，记录一下每头牛的$x_i$的排序，方便下文的删除操作

然后再按$v_i$从大到小排序

然后每次就查询完了就从树状数组中把这头牛删掉

然后重载了一下运算符，操作可能会方便一些吧

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 1e5 + 10;
const int p = 1e9 + 7;

int n;
ll ans(0);
struct node{int v, x, p;}c[maxn];

inline bool cmpx(node x, node y)
{
    return x.x < y.x;
}

inline bool cmpv(node x, node y)
{
    return x.v > y.v;
}

#define lowbit(x) (x & -x)
int tree[maxn], cnt[maxn];
inline void add(int x, int v, int p)
{
    while (x <= n) {
        tree[x] += v;
        cnt[x] += p;
        x += lowbit(x);
    }
}

inline pair<int, int> query(int x)
{
    int ans(0), cur(0);
    while (x) {
        ans += tree[x];
        cur += cnt[x];
        x -= lowbit(x);
    }
    return make_pair(ans, cur);
}

#define sum first
#define num second

pair <int, int> operator - (pair <int, int> a, pair<int, int> b)
{
    return make_pair (a.sum - b.sum, a.num - b.num);
}

inline pair<int, int> query(int l, int r)
{
    return query(r) - query(l);
}

int main()
{  
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++i) scanf ("%d %d", &c[i].v, &c[i].x);
    sort (c + 1, c + n + 1, cmpx);
    for (int i = 1; i <= n; ++i) add(i, c[i].x, 1), c[i].p = i;
    sort (c + 1, c + n + 1, cmpv);
    for (int i = 1; i <= n; ++i) {
        pair <int, int> r = query(c[i].p, n), l = query(c[i].p - 1);
        ans += 1ll * c[i].v * (r.sum - r.num * c[i].x + l.num * c[i].x - l.sum);
        add(c[i].p, -c[i].x, -1);
    }
    printf ("%lld\n", ans);
}
```

---

## 作者：ez_lcw (赞：4)

# 史上最短代码题解

~~到底是怎么评到紫题的？？？~~

看到数据范围和经过真实实验后，我们发现：

可以直接枚举$i,j$，然后按题意暴力加上$ans$就可以了。

因为题目中提到"**如果奶牛$i$和$j$想相互交谈，她们的音量必须不小于$\max(v_i,v_j)\times dis(i,j)$。其中$dis(i,j)$表示她们间的距离。**"

代码如下：

```cpp
#include<bits/stdc++.h>
 
#define N 20010
 
using namespace std;
 
int n,v[N],x[N];
long long ans;
 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d",&v[i],&x[i]);
    for(int i=1;i<=n;i++)
    	for(int j=1;j<i;j++)
        	ans+=abs(x[i]-x[j])*max(v[i],v[j]);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：durbin中将 (赞：2)

大水题,纯模拟.
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,v[20001],x[20001],ans=0;
inline long long read()//快读
{
    long long res=0;
    long long fl=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') fl=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=res*10+ch-'0';
        ch=getchar();
    }
    return fl*res;
} 
int main(){
	n=read();
	for(register int i=1;i<=n;i++)
		v[i]=read(),x[i]=read();
	for(register int i=1;i<=n;i++){
		for(register int j=i+1;j<=n;j++){//逐个向后递进
			ans+=max(v[i],v[j])*(abs(x[i]-x[j]));//按题意累加即可
		}
	}
	printf("%lld\n",ans);//输出
	return 0;
}
```

---

## 作者：cryozwq (赞：1)

### 一些闲话
建议管理员撤下所有 $O(n^2)$ 的题解，这是错误的。~~说的像我自己的程序常数不大一样~~。看到这题题解都是双树状数组，这里来发**三**树状数组。当然这个程序常数很大，**而且非常需要吸氧。**

不吸氧：[T飞](https://www.luogu.com.cn/record/36203604)。

吸氧：[跑的挺快](https://www.luogu.com.cn/record/36203615)。

下面是正文

## 分析
这道题题意非常简洁，不做解释。

首先很容易打出 $O(n^2)$ 的算法，枚举每两头牛之间的音量，然后你就 T 飞了。

所以我们需要一个更快的算法。

首先排序，为什么排序呢？因为我们看下这个式子：

$\max(v_i,v_j) \times dis(i,j)$

你看这个 $\max$ 肯定不是好东西，我们要把它干掉。所以我们按照 $v_i$ 的大小排序，然后按顺序枚举，为了节约时间，我们每次都只把这个 $i$ 和前面的加和。

那么我们现在就解决了 $\max(v_i,v_j)$ 的问题。来看下 $dis(i,j)$。

显然有 $dis(i,j) = \left| \ x_i-x_j\right|$ 。

又出现了绝对值，我们也不想要这种东西，考虑 $x_i$ 之前有 $m$ 个小于它的，编号为 $x_{k_1},x_{k_2}......x_{k_m}$，

那么对于每一个 $x_i$ 和前面的 $x$ 的距离之和为 $\displaystyle\sum_{j=1}^{i-1}x_j-\displaystyle\sum_{u=1}^{m}x_{{k_u}}\times2+2\times m\times x_i$

对于上面的式子的两个求和，因为都是动态的，我们使用树状数组维护。当然了，我们还需要一个树状数组维护 $m$，可以看成是逆序对数量。维护的细节就不讲了，~~要是不会维护就去把蓝书翻个十遍~~。
## 代码
```cpp
#include<bits/stdc++.h>
#define lowbit(i) i&(-i)
using namespace std;
map<int,int>A;
map<int,int>C,C2,C3;//为了节约空间开的map 
int n,n2;
struct cow{
	int v,x;
}c[400005];
bool cmp(cow a,cow b){
	return a.v<b.v;
}
void add(int x,int y){
	while(x<=n){
		C[x]+=y;
		x+=lowbit(x);
	}
}
int sum(int x){
	int ans=0;
	while(x){
		ans+=C[x];
		x-=lowbit(x);
	}
	return ans;
}
void add2(int x,int y){
	while(x<=n2){
		C2[x]+=y;
		x+=lowbit(x);
	}
}
int sum2(int x){
	int ans=0;
	while(x){
		ans+=C2[x];
		x-=lowbit(x);
	}
	return ans;
}
void add3(int x,int y){
	while(x<=n2){
		C3[x]+=y;
		x+=lowbit(x);
	}
}
int sum3(int x){
	int ans=0;
	while(x){
		ans+=C3[x];
		x-=lowbit(x);
	}
	return ans;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i].v>>c[i].x;
		n2=max(n2,c[i].x);
	}
	sort(c+1,c+n+1,cmp);
	long long ans=0;	
	for(int i=1;i<=n;i++){
		add(i,c[i].x);  
		add2(c[i].x,-2*c[i].x);//跟维护逆序对差不多的思想 
		add3(c[i].x,1);//维护逆序对数量 
		long long t=sum(i-1)-c[i].x*(i-1)+sum2(c[i].x-1)+sum3(c[i].x-1)*c[i].x*2;//这里就是计算距离之和 
		t*=c[i].v;
		ans+=t;
	}
	cout<<ans<<endl;
	return 0;
} 
```
复杂度为 $O(n \log n)$，可以通过本题。

---

