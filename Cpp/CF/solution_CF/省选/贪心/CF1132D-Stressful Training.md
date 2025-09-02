# Stressful Training

## 题目描述

今天，Berland SU 为学生们举办了又一次训练赛。共有 $n$ 名学生参加，每人都带来了自己的笔记本电脑。然而，大家都忘记带充电器了！

假设学生编号为 $1$ 到 $n$。第 $i$ 个学生的笔记本电脑在比赛开始时有 $a_i$ 的电量，每分钟消耗 $b_i$ 的电量（即如果某分钟开始时电量为 $c$，那么下一分钟开始时电量变为 $c-b_i$）。整场比赛持续 $k$ 分钟。

Polycarp（Berland SU 的教练）决定购买一个充电器，以便所有学生都能顺利完成比赛。他会在比赛开始的那一刻购买充电器。

Polycarp 可以选择购买任意非负整数功率的充电器。功率在购买前确定，之后不能更改。设所选功率为 $x$。在每一分钟的开始（从比赛开始到比赛结束的最后一分钟），他可以将充电器插到任意一台学生的笔记本电脑上，并使用若干整数分钟。如果某台笔记本电脑每分钟消耗 $b_i$ 的电量，那么在插上充电器时，其每分钟消耗变为 $b_i-x$。如果功率足够大，消耗可以为负，表示电量在增加。笔记本电脑的电量没有上限，可以无限大。充电器同一时刻最多只能给一台笔记本电脑充电。

如果某台笔记本电脑在任意一分钟开始时（从比赛开始到比赛结束的最后一分钟）电量从未低于零（允许为零），则该学生顺利完成比赛。比赛结束那一刻的电量不做要求。

请你帮助 Polycarp 计算，为了让所有学生都能顺利完成比赛，充电器的最小功率应为多少。如果不存在这样的充电器，请输出 $-1$。

## 说明/提示

让我们以第一个样例为例，假设充电器功率为 $5$：

1. 电量为 $[3, 2]$，将充电器插到第 1 台电脑；
2. 电量变为 $[3-4+5, 2-2] = [4, 0]$，将充电器插到第 2 台电脑；
3. 电量变为 $[4-4, 0-2+5] = [0, 3]$，将充电器插到第 1 台电脑；
4. 电量变为 $[0-4+5, 3-2] = [1, 1]$。

比赛在第 4 分钟结束。

但如果充电器功率为 $4$：

1. 电量为 $[3, 2]$，将充电器插到第 1 台电脑；
2. 电量变为 $[3-4+4, 2-2] = [3, 0]$，将充电器插到第 2 台电脑；
3. 电量变为 $[3-4, 0-2+4] = [-1, 2]$，第 1 台电脑电量为负，因此第 1 位学生无法完成比赛。

在第四个样例中，无论充电器功率多大，总有学生无法完成比赛。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 4
3 2
4 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 5
4
2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1 6
4
2
```

### 输出

```
2
```

## 样例 #4

### 输入

```
2 2
2 10
3 15
```

### 输出

```
-1
```

# 题解

## 作者：Super_Cube (赞：5)

# 思路：

因为答案具有单调性（简单来说就是如果某个 $x$ 能够满足电量在 $k$ 分钟内都不为负的情况下，那么大于 $x$ 的电量也能够满足），所以我们可以用**二分算法**来快速地求得最小的 $x$。

贪心地想，我们如何让所有电脑续航时间最长？当然是让最危急的（就是目前最快没电的）那台电脑接上充电器。

我们可以先预处理出如果不用充电器每台电脑最多能坚持的分钟数，循环 $k$ 次，每次找到时间最少的那台为其充电，然后把时间加上。如果某一次发现这台电脑从开始到现在能坚持的时间减去现在分钟数**小于 -1 了**，说明这个功率是**不合法**的（想想为什么）。

那我们如何知道哪台最快就要没电了呢？

STL 中的一个东西这个时候就体现出用处了——**优先队列**！这个东西说白了就是一个堆，~~用不着你手打~~，能够在 $O(logn)$ 的时间里插入元素，$O(1)$ 的时间取出按照某个方式排序后的第一个值。

关于优先队列的长相与用法：
```cpp
#include<queue>//头文件

priority_queue<类型>名称;//定义

q.push(x);//插入元素x
q.top();//取出堆顶元素
q.pop();//删除堆顶元素
```

那么这道题里，我们的优先队列肯定是以维持时间从小到大为排序方式。为了方便，把所有东西存入结构体，如下。

```cpp
struct node{
	int a,b;//初始电量，每分钟耗电量
	double d;//坚持分钟数，切记double!
}a[200005];//别开小了
```
我们如何使得一个自定义类型的优先队列使得其按照自己的需求进行排列呢？这个时候，就要用到重载运算符了，使用方法如下。

```cpp
struct node{
	int a,b;
	double d;
	friend bool operator<(node x,node y){
		return x.d>y.d;//按照d从小到大排序
		//注意:要记得反符号哦
	}
}a[200005];
```
也可以写成这样，如下。

```cpp
struct node{
	int a,b;
	double d;
	bool operator<(const node &x)const{
		return d>x.d;
	}
}a[200005];
```
还可以写在外面，如下。

```cpp
struct node{
	int a,b;
	double d;
}a[200005];
bool operator<(const node &x,const node &y){
	return x.d>y.d;
}
```
这三种写法都是一样的，看个人喜好，我用的第一种。~~（我才不会告诉你第2种最快）~~

好了，现在所有需要解决的知识点都解决了，可以开始写二分的判断函数了。

```cpp
bool check(int x){//充电器功率为x
	priority_queue<node>q;//定义优先队列
	for(i=1;i<=n;++i)q.push(a[i]);//把所有值扔进去
	for(i=1;i<=k;++i){
		node p=q.top();q.pop();//取出最危急的
		if(p.d-i<-1)return 0;//判断能否坚持到此刻
		p.d+=x*1.0/p.b;//给其充电
		q.push(p);//将其放回
	}return 1;
}
```

剩下就没什么难点了，自己实现吧。

# 注意：

1. ~~不开 long long 见祖宗。~~
2. 二分的边界，右边界别开小了，$2 \times 10^{12}$。
3. 找不到别忘了输出 -1。
4. ~~为了追求速度，别忘吸氧。~~

---

# Code：

```cpp
//已开启反作弊，(^_^)
#include<stdio.h>
#include<string.h>
#include<queue>
#define int long long
using namespace std;
struct node{
	int a,b;
	double d;
}a[200005];
bool operator<(const node &x,const node &y){
	return x.d>y.d;
}
int n,k,l,r=2e12,ans=-1,i;
bool check(int x){
	priority_queue<node>q;
	for(i=1;i<=n;++i)q.push(a[i]);
	for(i=1;i<=k;++i){
		node p=q.top();q.pop();
		if(p.d-i<-1)return 0;
		p.d+=x*1.0/p.b;q.push(p);
	}return 1;
}
int main(){
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;++i)scanf("%d",&a[i].a);
	for(i=1;i<=n;++i){
		scanf("%d",&a[i].b);
		a[i].d=a[i].a*1.0/a[i].b;
	}
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}printf("%d",ans);
	return 0;
}
```

---

## 作者：chenkaiwen (赞：3)

这是一道二分+贪心题，在洛谷上提交一直waiting，于是我直接去CF上提交了，通过记录如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/tif7ao2c.png)

### 题目大意

现在有 $n$ 台电脑，每台电脑 $i$ 的初始电量为 $a[i]$ ~~，因为电脑用的是神秘电池~~，电脑在**每分钟末**都会减少 $b[i]$ 个单位的电，为了在 $k$ 分中内不让电脑们断电，你搞了一个每分钟能且仅能给一台电脑充 $x$ 个单位电的充电器。**注意，你只有一个充电器，每分钟也只能给一台电脑充电，但每分钟可以给不同的电脑充电。** 现在让你求 $x$ 的最小值。

### 思路过程

看到这个题时，我们应该注意到一个非常关键的点让你求最小能满足条件的 $x$ 值，由此就能推断这是一道二分题。

为什么这是一道二分题？我们仔细分析一波，这个 $x$ 它其实有一个隐藏特性，当一个较大的 $x$ 能满足条件，那么比这个 $x$ 还要大的其他 $x$ 也一定能满足条件，也就是说，当我们发现一个 $x$ 它满足条件时，那么答案就一定不会是比这个值要大的其他值。这就是一个满足二分性质的东西，也就是**单调性**，在这一题中，单调性的体现就是：**一旦这个值满足，那么比这个值大的其他值也一定满足。**

现在我们知道了要用二分去寻找答案，但是我们该如何去判断一个答案的正确性呢？这里要用到贪心的思想，只要我们每分钟都去给马上就要断电的电脑充电，那么这就是最优解。注意，我们是给**马上就要断电的电脑**充电，而不是给**电量最少的电脑**充电，因为每个电脑耗电速度 $b[i]$ 不一定相同，所以电脑的存活时间不只和剩余电量有关，还和耗电速度有关，所以我们要考虑的是剩余电量和耗电速度的商，也就是剩余时间。

我们知道要每次取剩余时间最少的电脑充电，但我们该如何维护哪一台电脑是剩余电量最少的电脑呢？我们当然可以用   $O(n)$ 时间复杂度的遍历来维护这个需求，但这样太慢了，这里可以用一种数据结构来优化，我们用优先队列来维护寻找剩余电量最少的电脑这个需求。

总结一下，我们的思路是：二分一个答案，每一次贪心的给马上就要断电的电脑充电，用优先队列来查找哪个电脑马上就要断电。

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct as{
	long long cun,a,b,num;//十年OI一场空，不开long long 见祖宗，我在这里调了一个小时 
	bool operator <(const as &chongzhi)const{//记得重置运算符 
		if(cun==chongzhi.cun)return b>chongzhi.b;
		return cun>chongzhi.cun;
	} 
}q1,q2;
long long a[500101],b[500101];
long long n,k; 
void In(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
}
priority_queue<as>q;
void add(long long u,long long v,long long num){
	q1.cun=u/v;
	q1.a=u;
	q1.b=v;
	q1.num=num;
	if(q1.cun<k){
		q.push(q1)
	}
}
bool check(long long x){
	while(!q.empty())q.pop();
	for(int i=1;i<=n;i++){
		add(a[i],b[i],i);
	}
	for(int i=0;i<k&&(!q.empty());i++){
		q2=q.top(),q.pop();
		long long cun=q2.cun,u=q2.a,v=q2.b,num=q2.num;//取出我们要的电脑，这里也一定要long long 
		if(cun<i){
			return 0;
		}
		add(u+x,v,num);
	}
	return 1;
}
void Work(){
	long long l=0,r=1e13;//注意，可能出现不用充电也可以的情况，所以下界要为0
	//上界的情况应该是一台电脑一充电就再也不用充电，所以要为1e13 
	long long mid=(l+r)>>1;
	while(l<r){
		if(check(mid)){
			r=mid;
		}else{
			l=mid+1;
		}
		mid=(l+r)>>1;
	}
	if(l!=1e13)
		printf("%lld\n",l);
	else
		printf("-1\n");
}
int main(){
	In();
	Work();
	return 0;
}
/*
7 200000
1 100000 100000 100000 100000 100000 100000
100000 1 1 1 1 5 9
*/
```


---

## 作者：da32s1da (赞：3)

很明显考虑**二分**。

二分后，考虑怎么判合不合法。

我们开一个**priority_queue**，每次取出$\ \lfloor\frac{a}{b}\rfloor\ $最小的一个，然后充电。

注意充电加$a$即可，取出来后判断是否撑得过$k$分钟

```cpp
#include<cstdio>
#include<queue>
using namespace std;
typedef long long LL;
const int N=2e5+50;
const LL inf=2e12;
int n,k;
LL a[N],b[N],l,r,mid,Ans;
struct node{
	LL c,a;int b;
	node(LL C,int B,LL A):c(C),b(B),a(A){}
	bool operator <(const node &o)const{
		if(c!=o.c)return c>o.c;
		if(b!=o.b)return b<o.b;
		return a>o.a;
	}
}t(0,0,0);
priority_queue<node>s;
bool ok(LL u){
	while(!s.empty())s.pop();
	for(int i=1;i<=n;i++)
	if(a[i]/b[i]<k)s.push(node(a[i]/b[i],b[i],a[i]));
    // a/b>=k的没必要放进去
	if(s.empty())return true;
	for(LL i=0;i<k;i++){
		t=s.top();s.pop();
		if(t.c<i)return false;
		if((t.a+u)/t.b<k)s.push(node((t.a+u)/t.b,t.b,t.a+u));
		if(s.empty())return true;//同理
	}
	return true;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%I64d",&b[i]);
	l=0,r=inf;Ans=-1;
	while(l<=r){
		mid=(l+r)/2;
		if(ok(mid))Ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%I64d\n",Ans);
}
```

---

## 作者：0Io_oI0 (赞：2)

解题思路就是，如果确定 $p$ 判断是否存在方案，则每次贪心选择最早电量小于 $0$ 的电池 $u$ 充电总是最优的。否则考虑如果存在另一个充电方案 $T'$ 在当前时刻给 $u'\ne u$ 充电，那么假设 $T'$ 下一次给 $u$ 充电是 $t'$ 时刻，交换当前时刻和 $t'$ 时刻的充电操作总是合法的。

于是可以二分 $p$，每次按上述贪心判断是否存在方案。判断可以使用优先队列加速，时间复杂度为 $O(n\log ^2n)$。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int>pli;
namespace fastIO{char *p1,*p2,buf[100000];
	#define R register
	#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
	inline void read(ll&n){ll x=0,f=1;char ch=nc();while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=nc();}while(ch>=48&&ch<=57){x=(x<<3)+(x<<1)+(ch^48),ch=nc();}n=x*f;}inline void read(string&s){s="";char ch=nc();while(ch==' '||ch=='\n'){ch=nc();}while(ch!=' '&&ch!='\n'){s+=ch,ch=nc();}}inline void read(char&ch){ch=nc();while(ch==' '||ch=='\n'){ch=nc();}}inline void write(ll x){if(x<0){putchar('-'),x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');return;}inline void write(const string&s){for(R ll i=0;i<(int)s.size();i++){putchar(s[i]);}}inline void write(const char&c){putchar(c);}
}using namespace fastIO;
const ll INF=2e12,MAXN=2000010;
ll a[MAXN],b[MAXN],cnt[MAXN],last[MAXN],n,k;
bool check(ll x){
    priority_queue<pli,vector<pli>,greater<pli> >q;
    for(R ll i=0;i<n;i++){
        cnt[i]=0;
        if(a[i]>=b[i]*k)last[i]=-1;
		else{
            ll d=a[i]/b[i]+1;
            if(d<k) {
                last[i]=d;
                q.push({d,i});
            }
			else last[i]=-1;
        }
    }
    for(R ll j=0;j<k;j++){
        while(!q.empty()){
            pli top=q.top();
            ll d=top.first,i=top.second;
            if(d!=last[i]){
                q.pop();
                continue;
            }
            if(d<=j)return 0;
            break;
        }
        if(q.empty())break;
        pli top=q.top();
        q.pop();
        ll i=top.second;
        cnt[i]++;
        ll charge=a[i]+x*cnt[i]-b[i]*(j+1);
        if(charge<0)return 0;
        ll tot=a[i]+x*cnt[i],new_;
        if(tot>=b[i]*k)new_=k;
		else new_=(tot/b[i])+1;
        if(new_<k){
            last[i]=new_;
            q.push({new_,i});
        }
		else last[i]=-1;
    }
    return 1;
}
signed main(){
    read(n);
    read(k);
    for(ll i=0;i<n;i++)read(a[i]);
    for(ll i=0;i<n;i++)read(b[i]);
    ll l=0,r=INF;
    while(l<r){
        ll mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    if(l>=INF)puts("-1");
    else write(l);
    return 0;
}
```
![](https://discourse.xinyoudui.com/uploads/default/original/3X/4/d/4d84c82649a4e288dadd1eb335ddfdac7801484a.png)

亲测可过，请勿抄袭。

注：作者的代码好像常数有点大，所以加了快读快写，不加快读快写的话，后面几个点可能会被卡。

---

## 作者：Ryo_Yamada (赞：2)

显然，答案具有二分性。

对于两个答案 $x1,\,x2$，如果 $x1$ 是合法的答案，且 $x2 > x1$，那么保持相同的操作序列便可以证明 $x2$ 也是一个合法的答案。所以答案具有二分性。

对于每次给谁充电，当前所有电脑都有一个没电的时间节点 $t_i$。每次找到 $t_i$ 最小的并给其充电一定是最优的。如果有多个 $t_i$ 相同则找 $b_i$ 最大的。可以使用优先队列维护这个当前需要充电的电脑。时间复杂度为 $O(k \log n \log kb)$。

$2 \log$ 的算法可能会 TLE on 27，有几点可以优化：

- 如果当前电脑充完电之后再也不需要充电，可以不将其再次入队。
- 用一个变量记录每一个电脑还有多久断电，而不是每次都计算除法。

$\text{Code}$：

```cpp
#define mid (l + r >> 1)

def(N, int, 2e5 + 5)

int n, k;
ll a[N];
int b[N];

struct Node {
	int in; // 上次充电的时间
	ll a;
	int b;
	ll lst;
	
	bool operator > (const Node &oth) const {
		return (lst + in) == (oth.lst + oth.in) ? b > oth.b : (lst + in) > (oth.lst + oth.in);
	}
};

bool check(ll x) {
	priority_queue<Node, vector<Node>, greater<Node> > q;
	rep(i, 1, n) q.push((Node){1, a[i], b[i], a[i] / b[i]});
	for(int nw = 1; nw <= k && !q.empty(); ++nw) {
		Node u = q.top();
		q.pop();
		if(u.lst - nw + u.in < 0) return false;
		u.a -= u.b * (nw - u.in) - x;
		if(u.a / u.b + nw < k) {
			u.in = nw;
			u.lst = u.a / u.b;
			q.push(u);
		}
	}
	return true;
} 

int main() {
	qread(n, k);
	rep(i, 1, n) qread(a[i]);
	rep(i, 1, n) qread(b[i]);
	
	ll l = 0, r = 2e12, ans = -1;
	
	while(l <= r) {
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：lgnotus (赞：2)

考虑二分，二分充电器的功率。

如何进行$check$呢?

我们知道，如果对于当前电脑$i$,$\lfloor \frac {a_i}{b_i}\rfloor{}$最小，那么当前电脑一定是最早没电的，我们可以优先选择当前最先没电的电脑进行充电

因为每个电脑将会在$\lfloor \frac {a_i}{b_i}\rfloor+1$时没电，可以开一个$vector<int>cnt[N]$数组（队列也可以）$cnt[x]$存储的是在$x$时间点没电的电脑，我们创造两个指针$tot,Time$,前者遍历$cnt$数组（即当前电脑没电的时间），后者为当前时间

充电就相当于在$cnt[Time]$去掉一个电脑，在$cnt[tot+t]$加上这个电脑（$t=(Now[tmp]+mid)/b[tmp]$，$tmp$为这个电脑的编号，$Now[tmp]$为第$tmp$电脑不足以让他维持一个单位时间的剩余油量，很绕口蛤抱歉，看一下代码就能理解）

当前充电器不合法的条件就是电脑没电的时间小于当前时间

```cpp
#include<bits/stdc++.h>
#define N 200001
#define ll long long
using namespace std;

int n,k;
ll a[N],b[N],l,r,ans=-1;
vector<int>cnt[N];
ll Mymax(ll x,ll y){
    return x>y?x:y;
}


bool check(ll mid){
    for(int i=0;i<=k;i++)cnt[i].clear();
    ll Now[N];
    for(int i=1;i<=n;i++){
        if(a[i]/b[i]+1<k)cnt[a[i]/b[i]+1].push_back(i);
        Now[i]=a[i]%b[i];
    }
    int Time,tot;
    Time=tot=1;
    for(;Time<=k;Time++){//TOT
        while(tot<k&&cnt[tot].empty())tot++;
        if(tot<Time)return 0;
        if(tot==k)return 1;
        int tmp=cnt[tot].back();cnt[tot].pop_back();
        ll t=(Now[tmp]+mid)/b[tmp];
        Now[tmp]=(Now[tmp]+mid)%b[tmp];
        if(tot+t<k)cnt[tot+t].push_back(tmp);
    }
    return 1;
}

int main(){
    cin>>n>>k;
    ll maxn=LLONG_MIN;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        maxn=Mymax(maxn,b[i]);
    }
    l=0,r=k*maxn;
    while(l<=r){
        ll mid=(l+r)/2;
        if(check(mid))ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}

```









---

## 作者：anke2017 (赞：1)

### upd 2024.11.8 手欠撤销了题解，所以更改了一些地方，主要关于无解判断和部分卡常

省流：一个写了双 $\log$ 的人因为抢不到最优解，把复杂度优化到单 $\log$。

## 双 $\log$ 解法

[题目传送门](https://www.luogu.com.cn/problem/CF1132D)

容易发现，答案具有单调性，考虑**二分答案**。

这样，问题变为已知充电量，求出是否存在方案，使得前 $k$ 分钟都有电，并且单次复杂度要在 $O(n\log n)$ 级别或以下。

但是如果维护每分钟的剩余电量，每分钟都更改，由于每台电脑消耗的速度不相同，每分钟为 $O(n)$，显然会超时，单次复杂度至少是 $O(nk)$。

考虑不维护每分钟电量，只维护从开始时可使用时间（包括所有充电后的可使用时间）。

如果我们先给剩余时间少（很快就会没电）的人充电，与先给剩余时间多（晚些时候会没电）的人充电：

1. 如果我们给剩余时间多的人充电，导致剩余时间少的人没电了，那么显然得不偿失。

2. 否则，因为充电量一直不变，所以先充电，后充电对答案没有影响，即先给剩余时间少的人充电没有负面影响，结果不变。

从以上两点看，我们选择剩余时间更短的人充电一定更优。

如何选择剩余时间最短的人？

暴力求这个点是 $O(n)$ 的，考虑只有一个人被充电，而且一定是那个剩余时间最短的人，也就是只操作最值...这不是**堆优化**吗？

这样，对于每分钟，用堆维护所有人没电的时间，选择时间最短的，将其充电后重新放回堆里，时间复杂度为 $O(\log{n})$，单次检查复杂度为 $O(k\log{n})$。

总时间复杂度为 $O((k+n)\log{n}\log{val})$，$val$ 为二分上界。

对于充电头来说，当然是功率越大越强，但是到达对于每个人都是只需一次充电的程度之后（即充一次就可以用到比赛结束），没有区别，所以答案上界（有解时）为 $\max(b_i)\times k = 2 \times 10^{12}$，并可以证明实际上比这个还小。如果二分后超过此值，则判断无解。

堆采用 STL 实现。

### 一些小优化：（单个加速 0.1 秒左右）

1. 不需要再充电的就不用进堆了，反正再次充电也没用。
2. 有了上一点优化后，当堆为空时，直接返回 `true` 就好了。
3. 如果所有人的电池容量减去消耗速度都不够 $k$ 分钟花的，直接返回 `false`。
4. 每次 `check` 都新开一个堆，而不将原来的堆清空后使用。
5. 开 C++20 O2。
6. 快读。
7. 由于此做法的空间复杂度小，可以把快读的 `fread` 一次读入的字符数量增加。

### 一些较大的优化

1. 可以把初始堆记录下来，这样每次 `check` 时，建立 STL 堆的复杂度就从 $O(n\log{n})$ 变为 $O(n)$，总复杂度变为 $O(k\log{n}\log{val})$。
2. 不用开 `long long` 的用 `int` 就行了。
3. 将剩余的时间存起来，而不是单独计算，剩余时间用 `int` 而不是 `double` 存。
4. 事实上，无解的情况可以 $O(n+k)$ 判断，见下方代码。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

constexpr int maxn=2e5+100;

#define ll long long

ll a[maxn],b[maxn];
ll n,m;
ll totb;
ll tote;

char buf[50000001];

inline char nc()
{
    static char *p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,30000000,stdin),p1==p2)?EOF:*p1++;
}

ll read()
{
    static char a=nc();
    while(!isdigit(a)){a=nc();}
    ll n=0;
    while(isdigit(a))
    {
    	n=(n<<1)+(n<<3)+(a^48);
        a=nc();
    }
    return n;
}
//以上是快读

struct man
{
	ll a1,b1;int last;// a1 表示初始（包括充电后的）电量 ，b1 表示每分钟消耗电量
	//last表示从0时刻起可用时间
	//按整分钟算，14.01 分钟和 14.99 分钟一样，都是第 15 分钟没电（即可以忽略小数部分）
	bool operator <(const man tmp)const
	{
		return last>tmp.last;//注意 STL 是大根堆
	}
};
priority_queue<man> q;

bool check(ll x)
{
	if((totb-x)>tote/(double)(m-1))return false;//优化 3 
	priority_queue<man> q2=q;
	//大优化 1
	for(int i=0;i<m;i++)//第 i 到 i+1 分钟 
	{
		if(q2.empty())return true;//优化 2 
		man tmp=q2.top();
		//cout<<tmp.a1<<' '<<i<<'\n';
		q2.pop();
		if(tmp.last<i)return false;//已经有人电量为负了
		else if((tmp.a1+x)<tmp.b1*m)q2.push({tmp.a1+x,tmp.b1,(tmp.a1+x)/tmp.b1});
		//充电后重新入队，优化 1 
	}
	return true;// k 分钟后无事发生
}

int tmp_bucket[200001];

bool can_doit()
{
	for(int i=1;i<=n;i++)
	{
		if(a[i]<b[i]*m)tmp_bucket[a[i]/b[i]]++;
    //如果超过了 m 分钟，直接无视
	}
	for(int i=0;i<m;i++)
	{
		if(i)tmp_bucket[i]+=tmp_bucket[i-1];
        //防止越界
		if(tmp_bucket[i]>i+1)//这段时间内可以充电 i+1 次，如果有超过 i+1 个人要充电
			return false;//无解 
	}
	return true;
} 

signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		tote+=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		b[i]=read();
		totb+=b[i];
	}
    for(int i=1;i<=n;i++)if(a[i]<b[i]*m)q.push({a[i],b[i],a[i]/b[i]});
    if(!can_doit())//无解 
    {
    	cout<<-1;
    	return 0;
	}
//预处理 check 时的初始堆
	ll l=-1,r=2e12,mid;
//二分区间要开大，左区间需要为 -1
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(check(mid)){r=mid;}
		else l=mid;
	} 
	cout<<r;
	return 0;
}
```

## 走向单 $\log$

我们发现，有了上述优化后，在堆中的人一定是可使用时长小于 $k$ 的，且（从开始时）的可使用时长单调不减，而 $k$ 较小，所以考虑用**计数排序**的思想。

我们用一个一维数组套 `vector`，用第一维来表示可使用时间（从开始时计算，下同），用第二维来表示所有的，这个时间没电的人。  
每次从上一次的最小值开始，往后遍历 `vector`，找到最近一个有元素的 `vector` 并取出其的一个元素（实际使用时从后往前取以规避线性删除），判断合法性并将其充电后放到最新的位置，如果发现这次充电后不用再充电，则不做操作。

时间复杂度为 $O((n+k)\log{val})$。

如果跟双 $\log$ 做法类似的去存储初始状态并每次复原，时间复杂度变为 $O(k\log{val})$，但是因为本题 $n$ 和 $k$ 同级，所以并不用这样做。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

constexpr int maxn=2e5+100;

#define ll long long

ll a[maxn],b[maxn];
ll n,m;
ll totb;
ll tote;

inline char nc()
{
    static char buf[30000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,30000000,stdin),p1==p2)?EOF:*p1++;
}

ll read()
{
    static char a=nc();
    while(!isdigit(a)){a=nc();}
    static ll n;n=0;
    while(isdigit(a))
    {
    	n=(n<<1)+(n<<3);
        n+=(int)(a^48);
        a=nc();
    }
    return n;
}
//以上是快读

struct man
{
	ll a1,b1;int last;// a1 表示初始（包括充电后的）电量 ，b1 表示每分钟消耗电量
	//last表示从0时刻起可用时间
	//按整分钟算，14.01 分钟和 14.99 分钟一样，都是第 15 分钟没电（即可以忽略小数部分）
};
struct fm//find_max 的缩写
{
	vector<man> bucket[maxn];//桶 
	int now;//使用这个变量作为指针
	fm(){now=0;}
	void operator =(const fm tmp)
	{
		for(int i=tmp.now;i<=m;i++)
		{
			bucket[i]=tmp.bucket[i];
		}
		now=tmp.now;
	}
	inline bool empty()
	{
		while(!bucket[now].size()&&now<=m)now++;//跳过空桶
		return now==m+1;
	}
	inline man top()
	{
//由于每次调用前都会检查是否为空，所以不必再次清空
		return bucket[now].back();
	}
	inline void push(man tmp)
	{
		bucket[tmp.last].emplace_back(tmp);
	}
	inline void pop()
	{
		bucket[now].pop_back();
	}
}q,q2;

bool check(ll x)
{
	if((totb-x)>tote/(double)(m-1))return false;//优化 3 
	q2=q;
	for(int i=1;i<=m;i++)
	{
		if(q2.empty())return true;//优化 2 
		man tmp=q2.top();
		//cout<<tmp.a1<<' '<<i<<'\n';
		q2.pop();
		if(tmp.last<(i-1))return false;
		//已经有人电量为负了，注意这里是 i-1 ，是因为计算前 i-1 分钟而不是前 i 分钟 
		else if((tmp.a1+x)<tmp.b1*m)q2.push({tmp.a1+x,tmp.b1,(tmp.a1+x)/tmp.b1});
	}
	//充电后重新入队，优化 1 
	return true;// k 分钟后无事发生
}

signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		tote+=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		b[i]=read();
		totb+=b[i];
	}
    for(int i=1;i<=n;i++)if(a[i]<b[i]*m)q.push({a[i],b[i],a[i]/b[i]});
//预处理 check 时的初始桶
	if(q.empty()){cout<<0;return 0;}//其实不仅处理了不用充电，而且重置了指针 
	ll l=-1,r=2e12,mid;
//二分区间要开大，左区间需要为 -1
	while(l<r-1)
	{
		mid=(l+r)>>1;
		if(check(mid)){r=mid;}
		else l=mid;
		//cout<<"Success\n";
	} 
	if(r==2e12)cout<<-1;//无解
	else cout<<r;
	return 0;
} 
```

不知道是常数哪里过大了，时间反而是原来双 $\log$ 的 $1.5$ 倍，知道的可以私信。

附上错误指南：[WA，TLE集](https://www.luogu.com.cn/discuss/883828)

---

## 作者：Shadow_T (赞：1)

### $\texttt{Preface}$

[AC 记录](https://www.luogu.com.cn/record/147942532)

非常版的紫题。模拟赛 T4，因为看错一点题意加上 OI 赛制，只拿了 $70$ 分，差点 AC。

### $\texttt{Description}$

$n$ 个学生打一场 $k$ 分钟的比赛，每个学生刚开始电量为 $a_i$，**每分钟结束后**扣电 $b_i$ 点，如果有学生电量为负，则比赛失败。你还有一个充电器，每分钟可以选择一个学生充 $x$ 点电量，求满足所有学生可以完成比赛最小的充电值 $x$。

### $\texttt{Solution}$

首先很明显如果答案 $x$ 满足条件，$x+1$ 也满足条件，所以满足单调性。要求的是满足所有学生可以完成比赛最小的充电值，鉴定为：二分答案。

- 首先是打过无数遍的二分框架。

```cpp
int l=0,r=3e12;
while(l<r)
{
	int mid=(l+r)/2;
	if(check(mid)) r=mid;
	else l=mid+1;
}
```

如果答案满足条件，则缩小答案，否则扩大答案。这里有个坑点，$r$ 不能随心所欲设太大，如果直接开 $10^{18}$ 会完美爆 long long。

- 二分答案最重要的就是检验函数。

这里我们可以用贪心的思想。每次充电都充给最需要的学生，即还能撑的时间最短的学生，转化成数学公式就是先给 $a_i \div b_i$ 最小的学生。如果多个学生撑得时间一样且最短，选哪个都没有影响。

这里可以用优先队列来维护 $a_i \div b_i$，每次取出最小的，如果发现这个人已经比赛失败了，就返回失败，否则更新后再丢回队列。

```cpp
bool check(int x)
{
	priority_queue<st,vector<st>,greater<st> > q;
	for(int i=1;i<=n;i++)
	q.push({a[i],b[i],a[i]/b[i]});
	for(int i=1;i<=t;i++)
	{
		st t=q.top();
		if(t.a-t.b*(i-1)<0) return false;
		q.pop();
		t.a+=x;
		t.m=(double)(t.a)/(t.b);
		q.push(t);
	}
	return true;
}
```

复杂度化简后就是 $O(n\log n\log a_i)$。卡常数，可以发现我的 AC 记录第 $52$ 个点是 $2.99$ 秒，时限 $3$ 秒（

### $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int a[maxn],b[maxn];
int n,t;
struct st
{
	long long a,b;
	double m;
	bool operator <(const st &a)const
	{
		return m<a.m;
	}
	bool operator >(const st &a)const
	{
		return m>a.m;
	}
};
bool check(int x)
{
	priority_queue<st,vector<st>,greater<st> > q;
	for(int i=1;i<=n;i++)
	q.push({a[i],b[i],a[i]/b[i]});
	for(int i=1;i<=t;i++)
	{
		st t=q.top();
		if(t.a-t.b*(i-1)<0) return false;
		q.pop();
		t.a+=x;
		t.m=(double)(t.a)/(t.b);
		q.push(t);
	}
	return true;
}
signed main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	for(int i=1;i<=n;i++)
	cin>>b[i];
	int l=0,r=3e12;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	if(!check(l)) cout<<-1;
	else cout<<l;
}
```

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1132D)

## 思路

这是一道很简单的二分题，不懂双 $\log$ 是怎么搞出来的，我的做法思维复杂度，代码复杂度和时间复杂度都很低。

我们发现题意就相当于有 $n$ 个一次函数，$y_i=-(x-1) \times b_i+a_i\ (x \le k)$，这些函数有些会在取某些 $x$ 的时候值小于零，你在每个 $x$ 都可以抬高一个函数 $h$ 的高度，要求在满足任意时刻函数值都大于等于 $0$ 的情况下令 $h$ 最小。

很明显，答案具有可二分性，若在 $x=h$ 的时候满足条件，当 $x=h+1$ 时一定满足条件。

接下来考虑怎么 $\rm check$，显然地，我们可以算出每个函数需要抬几次，若总抬高次数已经大于了 $k$，则一定没有满足的方案。

现在我们考虑总抬高次数 $<k$ 的情况，可以直接把所有函数寄掉的点暴力求出来，然后排个序，对于排序后的某个数 $l_i$，若 $l_i<i$，则显然无法构造出满足条件的方案，直接退出即可。

如果直接排序，时间复杂度 $\mathcal O(k \log k\log \text{w})$，把排序的过程换成桶排，时间复杂度 $\mathcal O(k \log w)$，其中 $w$ 表示二分上界。

如此模拟即可，不加任何卡常跑了 $\rm 374\ ms$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
int const N=2e5+10;
int n,k,a[N],b[N],vis[N];
inline bool check(int x){
	memset(vis,0,sizeof(vis));
	int gg=0;
	for (int i=1;i<=n;++i){
		int res=a[i]-b[i]*(k-1);
		if (res>=0) continue;
		res=-res;gg+=(res+x-1)/x;
	}
	if (gg>k) return 0;//如果抬高次数已经大于 k 了，那么一定无解
	for (int i=1;i<=n;++i){
		int maxtime=a[i]/b[i]+1,res=a[i]%b[i];
		while (maxtime<k){
			++vis[maxtime];
			res+=x;maxtime+=(res/b[i]);
			res%=b[i];
		}//把所有函数寄掉的点都算出来
	}
	int l=1;
	for (int i=0;i<=k;++i)
		if (l+vis[i]-1>i) return 0;
		else l+=vis[i];//桶排
	return 1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;int flg=1;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=1;i<=n;++i) cin>>b[i];
	for (int i=1;i<=n;++i) if (a[i]<(k-1)*b[i]){flg=0;break;}
	if (flg){cout<<"0\n";return 0;}//特判不需要抬高的情况
	int l=1,r=1e14;
	while (l<r)
		if (check(mid)) r=mid;
		else l=mid+1;
	if (l==1e14) l=-1;
	cout<<l<<'\n';
	return 0;
}
```

---

## 作者：hanchengyi (赞：0)

# CF1132D Stressful Training题解

## 	思路

分析本题让我们求的 $x$，如果当前 $x$ 满足条件，那么根据题意，$x$ 更大一定也满足条件（因为充电时多充肯定优于少充）。这就满足了**单调性**，可以**二分 $x$ 这个答案**。

那么怎样判断当前 $x$ 合不合法呢？

这里是显然的**贪心策略**：每次充电选择最快要耗尽电的电脑充电，可以用优先队列进行维护这些电脑。如果在 $0 \le t \le k$ 的时间范围内出现了电要耗完的情况，那么当前二分的 $x$ 就不可行。

注意到 $1 \le a_i \le 10^{12}$，需把二分上界设置在 $10^{12}$ 以上。

## 代码

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define lld long long
using namespace std;
inline void read(lld &x){x=0;char c=getchar();bool p=1;
	for(;'0'>c||c>'9';c=getchar()) if(c=='-') p=0;
	for(;'0'<=c&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c^48);p?:x=-x;
}
const int N=2*1e5+9;
struct NODE{
	long long a,b;//初始电量ai和每分钟耗电量bi
	double v;//a/b，表示还有多久电耗完
	bool operator < (const NODE &y)const{
		return v>y.v;
	}
};
lld n,k;
NODE t[N];
bool check(lld x){
	priority_queue<NODE> p;
	for(int i=1;i<=n;i++){
		p.push(NODE{t[i].a,t[i].b,double(double(t[i].a)/double(t[i].b))});
	}//每次check前重置优先队列
	NODE tmp;
	for(int i=1;i<=k;i++){
		tmp=p.top();p.pop();
		if(tmp.v<i-1) return 0;
		//把当前剩余时间i-1和tmp这台电脑还可以坚持的时间比
		//如果不能坚持了，本次二分的x不行
		tmp.a+=x;//否则就充电
		tmp.v=double(tmp.a)/(double)(tmp.b);
		//重新计算还可以坚持的时间
		p.push(tmp);
	}
	return 1;
}
int main()
{
	read(n);read(k);
	for(int i=1;i<=n;i++)
		read(t[i].a);
	for(int i=1;i<=n;i++)
		read(t[i].b);
	lld l=0,r=1e13,mid,ans;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	if(l>=1e13||r>=1e13) l=-1;//注意无解的情况
	printf("%lld",l);
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1132D
## 题意
给定 $n$ 台电脑的初始电量和每分钟的耗电量以及使用的时间 $k$，以及一个只能给一台电脑每分钟增加 $x$ 个电量的充电宝，使得在 $k$ 分钟里，所有电脑的电量都不小于 $0$，如果可以，输出最小的 $x$，不可以，输出 $-1$。
## 思路
本题考虑使用二分答案，找最小的 $x$。那怎么判断答案的合法性呢？我们只要使用优先队列存每个电脑还能继续使用的时间，把时间少的排在前面，加上 $x$ 个电脑，计算剩余使用时间，再放入优先队列。如果剩余使用时间已经小于 $0$，那么就返回不可以，否则返回可以。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=2e5+10;
int n,t;
LL a[N],b[N];
struct node{
	LL x,y;
	double m;
	bool operator<(const node &a)const{
		return m>a.m;
	}
};
bool check(LL mid){
	priority_queue<node>q;
	for(int i=1;i<=n;i++){
		q.push(node{a[i],b[i],1.0*a[i]/b[i]});
	}
	for(int i=1;i<=t;i++){
		node now=q.top();
		q.pop();
		if(now.m-i<-1)return false;
		now.m+=1.0*mid/now.y;
		q.push(now);
	}
	return true;
}
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	LL l=0,r=2e12,ans=-1;
	while(l<=r){
		LL mid=l+(r-l)/2;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Harry_Hedwig (赞：0)

>**不开 `long long ` 见祖宗！！！**
# 0x00 思路
先看题。
>有 $n$ 个学生要打一场 $k$ 分钟的比赛（当然要用电脑）。

>每个学生的电脑有初始电量 $a_i$ 和**每分钟耗电量** $b_i$（电量在这一分钟的最后一刻结算，即**在下一分钟时才会减少，电量允许为负**）。

>这样肯定是无法打完比赛的，所以学生们买了一个充电器，功率为任意值，**每分钟可以使电量增加 $x$，结算规则与耗电量一样**，它可以在**任一分钟**给**任一学生**的电脑充电**任意时长**。

>问题：求**最小**的 $x$，使**所有学生的电脑**的电量在 $k$ 分钟内**都不为负**。

由于是求最小，所以如果这个功率的充电器是可行的，那么所有功率比它大的都一定可行。

所以这道题目答案有单调性，于是我们可以选择二分答案。

**注意：虽然题目说了电量可以为负，但是这个时候就打不了比赛了啊！**

由于常识，只要电量**大于等于** $0$，就可以继续用。~~什么鬼常识~~所以我们只需要找到充电器使得所有人电脑在任意时刻电量大于等于 $0$ 即可。

# 0x01 Check
由于我们先前已经二分了一个我们觉得有可能的答案（假设为 $c$），我们肯定需要去打一个模拟赛去模拟正式比赛时的真实情况。

那么这个时候我们就遇到了一个问题：每个人的电脑似乎都需要充电，到底充谁的好呢？

~~由于题目的标签是贪心 + 二分~~，因为我们要保证每个人的电脑都能撑到最后一刻，那么目前看来最危险的电脑就是 **当前电量能支撑的时间（不是电量！！！！）** 最少的那一台。所以为了帮助它渡过难关，当前分钟肯定会给其充电啦~

所以我们的贪心策略就出现了：找到当前能支撑的时间最少的一台电脑（这时可以用优先队列直接取队首）并在当前时间给其充电。

接着我们就可以写出代码了。

# code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct Mc
{
	long long now,elec;//电量,耗电率
	double times;//支撑时间
}a[200005],s,h;
bool operator<(Mc a,Mc b)
{
	return a.times>b.times;
}
int n,k;
bool check(long long c)
{
	priority_queue<Mc>q;
	int i;
	for(i=1;i<=n;i++)//入队
		q.push(a[i]);
	for(i=1;i<k;i++)
	{
		s=q.top();
		q.pop();
		if(s.times-i<-1)//这台电脑已经没电了
			return 0;
		s.times+=c*1.0/s.elec;//充电
		q.push(s);
	}
	return q.top().times-k>=-1;
}
long long ef(long long l,long long r)//二分模板,没什么好说的
{
	int i;
	if(l==r)
	{
		if(check(l))
			return l;
		return -1;
	}
	long long mid=(l+r)/2;	
	if(check(mid))
		return ef(l,mid);
	return ef(mid+1,r);
}
signed main()
{
	int i,j;
	scanf("%lld %lld",&n,&k);
	for(i=1;i<=n;i++)
		scanf("%lld",&a[i].now);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&a[i].elec);
		a[i].times=a[i].now*1.0/a[i].elec;//计算在最开始每台电脑能支撑的时间
	}
	printf("%lld",ef(0,2e12/*充电器最大功率*/));
	return 0;
}
```
对代码的解释：
```cpp
s=q.top();
q.pop();
if(s.times-i<-1)//这台电脑已经没电了
	return 0;
```
Q：为什么用队首来判断还能否坚持？

A：因为队首的电脑能支撑的时间最短，如果其可以支撑则其他的都可以，否则就说明已经没不行了。

---

## 作者：TulipeNoire (赞：0)

### 思路

这种题很容易想到二分。功率越大，就越能完成比赛。所以对功率进行二分。

然而，判断的函数似乎很难写——我怎么知道什么时候该给哪台电脑充电呢？不难发现，能坚持分钟数最小的同学最需要充电，因为如果不充电，他是最快没电的那个，所以优先给他充，不然给其他人充没有意义。那么用一个优先队列就可以实现最小值查询，删除与插入值的功能了。而判断某个功率不能支持完成比赛，就是某一时刻坚持分钟数第二少的同学已经坚持不了了。这样肯定就无能为力了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
struct P {
    long long t,d,m;
}a[200005];
bool operator <(P x,P y) {
    return x.m>y.m;
}
bool check(long long x) {
    priority_queue<P>q;
    for (int i=1;i<=n;i++) {
        q.push(a[i]);
    }
    for (int i=1;i<=k;i++) {
        P e=q.top();
        q.pop();
        e.t+=x;
        e.m=e.t/e.d;//更新坚持天数 
        if (e.m<i) return false;
        if (!q.empty())/*注意细节，若只有一个人，就必须判断，否则会RE*/ if (q.top().m<i) return false;
        q.push(e);
    }
    return true;
}
long long f(long long l,long long r) {
    if (l==r) return l;
    if (l==r-1) {
        if (check(l)) return l;
        return r;
    }
    long long mid=(l+r)/2;
    if (check(mid)) return f(l,mid);
    return f(mid+1,r);
}
int main() {
    scanf("%d %d",&n,&k);
    k--;
    for (int i=1;i<=n;i++) {
        scanf("%lld",&a[i].t);
    }
    for (int i=1;i<=n;i++) {
        scanf("%lld",&a[i].d);
        a[i].m=a[i].t/a[i].d;//坚持天数 
    }
    long long F=f(0,2e13);
    printf("%lld",(F==2e13?-1:F));
    return 0;
}
```

---

## 作者：smoothset (赞：0)

#### 思路
这种题，看到就会想到要二分这个$x$的值，那么接下来就考虑如何$check()$这个这个x值.
考虑使用一个优先队列，按照可以撑的时间排序，每次给可以撑的时间最少的点加上$x$的电，然后每当有可以超过$k$的，就直接移出队列，当队列为空时，便为成功，然后继续二分即可.
#### 代码
具体实现见代码部分（模板较长哈哈哈）
~~~cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
namespace OI
{
    #define pk putchar(' ')
    #define ph puts("")
    #define fi first
    #define se second
    template<class T>
    void rd(T &x)
    {
        x = 0;
        int f = 1;
        char c;
        while (!isdigit(c = getchar())) if (c == '-') f = -1;
        do
        {
            x = (x << 3) + (x << 1) + (c ^ 48);
        } while (isdigit(c = getchar()));
        x *= f;
    }
    template<class T>
    void pt(T x)
    {
        if (x < 0)
            putchar('-'), x = -x;
        if (x > 9)
            pt(x / 10);
        putchar(x % 10 ^ 48);
    }
}
using namespace OI;
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
const ll INF = 2e12;
int n, k;
ll a[N], l, r, ans, b[N];
struct node
{
	ll a, b, c;
	bool operator < (const node &x)const{
		if (c != x.c)
			return c > x.c;
		if (b != x.b)
			return b < x.b;
		return a > x.a;
	}
};
priority_queue<node> Que;
bool check(ll x)
{
	while (!Que.empty()) Que.pop();
	for (int i = 1; i <= n; i++)
		if (a[i] / b[i] < k)
			Que.push({a[i], b[i], a[i] / b[i]});
	if (Que.empty())
		return 1;
	for (int i = 0; i < k; i++)
	{
		node t = Que.top();
		Que.pop();
		if (t.c < i)
			return 0;
		if ((t.a + x) / t.b < k)
			Que.push({t.a + x, t.b, (t.a + x) / t.b});
		if (Que.empty())
			return 1;
	}
	return 1;
}
int main()
{
    rd(n), rd(k);
	for (int i = 1; i <= n; i++)
		rd(a[i]);
	for (int i = 1; i <= n; i++)
		rd(b[i]);
	l = 0, r = INF, ans = -1;
	while (l <= r)
	{
		ll mid = (l + r) >> 1;
		if (check(mid))
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	pt(ans);
    return 0;
}
~~~
#### 谢谢

---

