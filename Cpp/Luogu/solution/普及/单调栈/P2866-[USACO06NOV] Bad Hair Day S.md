# [USACO06NOV] Bad Hair Day S

## 题目描述


农夫约翰有 $N$ 头奶牛正在过乱头发节。

每一头牛都站在同一排面朝右，它们被从左到右依次编号为 $1, 2, \cdots, N$。编号为 $i$ 的牛身高为 $h_i$。第 $N$ 头牛在最前面，而第 $1$ 头牛在最后面。

对于第 $i$ 头牛**前面**的第 $j$ 头牛，如果 $h_i>h_{i+1}, h_i>h_{i+2}, \cdots, h_i>h_j$，那么认为第 $i$ 头牛可以看到第 $i+1$ 到第 $j$ 头牛。

定义 $C_i$ 为第 $i$ 头牛所能看到的牛的数量。请帮助农夫约翰求出 $C _ 1 + C _ 2 + \cdots + C _ N$。


## 说明/提示

### 数据规模与约定

对于 $100\%$ 的数据，保证 $1 \leq N \leq 8 \times 10 ^ 4$，$1 \leq h _ i \leq 10 ^ 9$。

## 样例 #1

### 输入

```
6
10
3
7
4
12
2```

### 输出

```
5```

# 题解

## 作者：Cripple_Abyss (赞：323)

[题目传送门](https://www.luogu.com.cn/problem/P2866)

本题考查对栈的应用

## 题目解法：
1. 每次输入一头牛的身高，找比这头牛矮的，出栈

1. 剩下的牛皆可以看到这只牛

1. ans值加等于栈中牛的个数

1. 这头牛入栈

# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
long long ans; //注意要开long long 
stack <int> a;
int main() {
	cin>>n;
	for (int i=1; i<=n; i++) {
		cin>>t;
		while (!a.empty()&&a.top()<=t)  
			a.pop();
		ans+=a.size();
		a.push(t);
	}
	cout<<ans;
	return 0;
}
```

都看到这了，点个赞呗QwQ

---

## 作者：huyufeifei (赞：40)

一看这道题，我先考虑的就是从后往前扫，然后发现有问题，考虑从前往后扫。

然后我发现只要维护没有被当前牛挡住的牛的个数就行了。

这显然就是个单调栈对吧，然后就会有以下代码：
```cpp
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    LL ans = 0;
    int t = 0;
    for(int i = 1; i <= n; i++) {
        while(t && a[i] >= p[t]) {
            t--;
        }
        ans += t;
        p[++t] = a[i];
    }
    printf("%lld", ans);

```
但是呢，人总是会有一些脑抽的时候对不对，就比如我。

所以我来给大家提供新思路了！

### 解法2：线段树！

#### 智商不够，数据结构来凑！

我的想法：可以把这些高度离散化一下。

然后从前往后扫描到第 ```i``` 头牛的时候，能够看见他的是所有在他前面比他高的牛，且没有被遮挡。

然后这头牛把不比他高的牛全部遮挡了。

抽象一下，然后我们要支持什么操作呢？

+ 区间求和
+ 单点修改
+ 区间赋值

好，一看就是线段树！
然后我就兴高采烈的打了个线段树，A了之后跑来看题解，WTF？？？为什么我打了一百多行的线段树，别人10行就A了？

然后深刻认识到了自己的脑残，于是发一篇题解博诸君一笑。

线段树：304ms时间  5.18M空间  2.22K代码

单调栈：48ms时间   2.2M空间   0.4K代码

可见单调栈的优越...你们千万不要学我。

线段树代码：
```cpp
#include <cstdio>
#include <algorithm>

typedef long long LL;

const int N = 80010;

bool tag[N << 2];
LL sum[N << 2], a[N], x[N];

inline void pushup(LL l, LL r, LL o) {
    if(l == r) {
        return;
    }
    sum[o] = sum[o << 1] + sum[o << 1 | 1];
    return;
}

inline void pushdown(LL l, LL r, LL o) {
    if(l == r || !tag[o]) {
        return;
    }
    tag[o << 1] = tag[o << 1 | 1] = 1;
    sum[o << 1] = sum[o << 1 | 1] = 0;
    tag[o] = 0;
    return;
}

void build(LL l, LL r, LL o) {
    if(l == r) {
        sum[o] = 0;
        return;
    }
    LL mid = (l + r) >> 1;
    build(l, mid, o << 1);
    build(mid + 1, r, o << 1 | 1);
    pushup(l, r, o);
    return;
}

LL ask(LL l, LL r, LL o, LL L, LL R) {
    if(L <= l && r <= R) {
        return sum[o];
    }
    if(r < L || R < l) {
        return 0;
    }
    pushdown(l, r, o);
    LL mid = (l + r) >> 1;
    return ask(l, mid, o << 1, L, R) + ask(mid + 1, r, o << 1 | 1, L, R);
}

void add(LL l, LL r, LL o, LL p) {
    if(l == r) {
        sum[o]++;
        tag[o] = 0; /// error : space
        return;
    }
    pushdown(l, r, o);
    LL mid = (l + r) >> 1;
    if(p <= mid) {
        add(l, mid, o << 1, p);
    }
    else {
        add(mid + 1, r, o << 1 | 1, p);
    }
    pushup(l, r, o);
    return;
}

void put(LL l, LL r, LL o, LL L, LL R) {
    if(tag[o]) {
        return;
    }
    if(L <= l && r <= R) {
        tag[o] = 1;
        sum[o] = 0;
        return;
    }
    pushdown(l, r, o);
    LL mid = (l + r) >> 1;
    if(L <= mid) {
        put(l, mid, o << 1, L, R);
    }
    if(mid < R) {
        put(mid + 1, r, o << 1 | 1, L, R);
    }
    pushup(l, r, o);
    return;
}
/**
6
10 3 7 4 12 2
*/
int main() {
    LL n;
    scanf("%lld", &n);
    for(LL i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        x[i] = a[i];
    }
    std::sort(x + 1, x + n + 1);
    LL t = std::unique(x + 1, x + n + 1) - (x + 1);
    for(LL i = 1; i <= n; i++) {
        LL p = std::lower_bound(x + 1, x + t + 1, a[i]) - x;
        a[i] = p;
    }
    build(1, n, 1);
    LL ans = 0;
    for(LL i = 1; i <= n; i++) {
        put(1, n, 1, 1, a[i]);
        ans += sum[1];
        //printf("%lld %lld\n", i, sum[1]);
        add(1, n, 1, a[i]);
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：Harry27182 (赞：34)

**思路：**

首先看到 $n\leq80000$ ，暴力肯定是不行的 ，我们考虑优化暴力 。显然，对于一个 $i$ ，如果 $j(j>i)$ 符合条件 ，那么所有的数 $x(i<x<j)$ 也符合条件 ，发现答案满足单调性后 ，我们可以考虑二分 。我们枚举左端点 $l$ ，二分右端点 $r$ ，最大化满足条件的右端点 $r$ ，现在问题就变成了如何判断区间 $[l,r]$ 是否满足条件 。

我们可以发现 ，只要 $l-1$ 比区间 $[l,r]$ 中的最大值大 ，那么这个区间就是符合条件的 ，所以现在只需要维护区间$[l,r]$ 中的最大值 ，这就是典型的 RMQ 问题 ，由于不需要修改 ，我们选择 ST 表来维护区间最值 ，问题就解决了 。

**代码：**

```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
int n,ans,a[80005],f[80005][30];
bool check(int l,int r)//ST表标准查询
{
	if(l>r)return 0;
	int k=log2(r-l+1);
	if(max(f[l][k],f[r-(1<<k)+1][k])<a[l-1])return 1;
	return 0;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		f[i][0]=a[i];
	} 
	for(int j=1;j<=20;j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]);
		}
	}//ST表预处理
	for(int i=1;i<=n;i++)
	{
		int l=i,r=n;
		while(l<r)
		{
			int mid=(l+r)/2;
			if((l+r)%2==1)mid++;//二分的时候要向上取整，否则会出现找不到最大的mid的情况
			if(check(i+1,mid))l=mid;//注意判断区间是[i+1,mid]，不是[i,mid]
			else r=mid-1;
		} 
		ans+=max((long long)0,l-i);
	}
	cout<<ans;
	return 0;
}
```

还有哪里不懂可以评论区问我，~~求顶......~~

---

## 作者：Hexarhy (赞：22)

本题适合刚学单调栈的同学练练手。

----------------

### 解题思路

题目说得挺清楚的。下面是思路。

让你维护一个严格递减的序列，显然是单调栈了。栈也是严格递减的。

与其求一头牛**能看见**几头牛，不如反过来，计算一头牛**能被**几头牛看见。由于是要求总数，因此不难想到，能看见的总数一定等于被看见的总数。

当然前者方法肯定也能做出来，这里不展开，或者看看[这里](https://www.luogu.com.cn/blog/Youngsc/solution-p2866)。

那么思路就很清晰了，稍稍讨论即可：

- 设栈顶元素高度为 $h$，新加进来第 $i$ 个元素高度为 $x$，$ans_i$ 为第 $i$ 头奶牛被看见的数目。

- 若 $h>x$，栈保持严格递减，直接入栈；

- 否则，即当 $h\le x$，为保持单调性，出栈，直到满足条件。

- 计算答案时，对于 $x$，栈内的所有元素都比它高，$ans_i$ 等于栈的元素个数，即`ans[i]=stack.size()`。

- 当然，上一步骤可简化为`ans+=stack.size()`。毕竟只要求总和。

------------------

### 实现细节

1. 请区分“单调递减”和“严格递减”！前者是包括等号的，而后者不包括等号。因此在判断时，$h\le x$ 都要出栈。

1. 养成好习惯，使用栈前一定要判断栈是否为空。

1. 栈内可以储存下标或高度。这对本题影响不大。下面代码储存下标。

1. 以后求和一个数组时，可以采用`std::accumulate()`，头文件为`<numeric>`。详细内容见文末。

1. 养成好习惯：请估算答案是否可能超过`int`。本题最多共有 $n=8\times 10^4$ 个，因此答案最大为 $\frac{n(n-1)}{2}\approx3\times10^9$。而`int`大约为 $2\times 10^9$，因此需要`long long`。

### 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <vector>
#include <numeric>//注意头文件
using namespace std;

int n;
stack <int> s;

int main()
{
	cin>>n;
	vector <long long> h(n+5),ans(n+5);//动态开数组，可学可不学。vector默认为0
	for(int i=1;i<=n;i++)
	 cin>>h[i];
	for(int i=1;i<=n;i++)
 	{
 		while(!s.empty() && h[s.top()]<=h[i])
 		 s.pop();//不满足要求的出栈
 		ans[i]=s.size();//第i头能被看见
 		s.push(i);
 	}
	cout<<accumulate(ans.begin(),ans.end(),0LL)<<endl;//推荐
	return 0;
}
```
-------------------

### 附加：关于`std::accumulate()`

首先，**不需要C++11**。记住头文件为`<numeric>`。

`std::accumulate(first,last,val,f)`：

其中前两个参数是迭代器，用法跟`std::sort()`一样。

函数意义为，返回一个数值，为区间 $[first,last)$ 中,若每个元素为 $x$，则 $f(x,val)$ 的和。

当函数中没有`f`时，默认为`[](type a,type b){return a+b;}`，即**加法运算**。

因此，语句`accumulate(ans.begin(),ans.end(),0LL)`表示`long long`类型的 $\sum ans$。

**函数的返回值类型取决于参数的类型。**

~~更多详细内容可以百度。~~

---

## 作者：YoungLove (赞：16)

[Youngsc](http://youngscc.github.io/)

大佬们都在统计一头牛能被几头牛看见，而蒟蒻在统计一头牛能看见几头牛。

我们可以倒着来扫，并同时维护一个单调栈，在每个元素入栈之前将身高小于它的全部出栈，然后如果栈里还有元素，那个这头牛一定是视野所及的最远的牛，也就是当视线的牛。因此栈顶的牛与当前的牛之间的牛均可被看见，累加进答案就好。如果栈里没有元素，那就说明一望无际，视线里的所有牛都能被看见，也将其累加进答案。


思路还是很好想的


## 代码在这里


```cpp
# include <algorithm>
# include <iostream>
# include <cstring>
# include <cstdio>
# include <queue>
# include <cmath>
# define R register
# define LL long long

using namespace std;

int n,h[100010],st[100010],top;
LL ans;

inline void in(R int &a){
    R char c = getchar();R int x=0,f=1;
    while(!isdigit(c)){if(c == '-') f=-1; c=getchar();}
    while(isdigit(c)) x = (x<<1)+(x<<3)+c-'0',c = getchar();
    a = x*f;
}

inline void maxx(R int &a,const int b){a>b? 0:a=b;}
inline void minn(R int &a,const int b){a<b? 0:a=b;}

inline int yg(){
    // freopen("maze1.in","r",stdin);
    // freopen("maze1.out","w",stdout);
    in(n);
    for(R int i=1; i<=n; ++i) in(h[i]);
    for(R int i=n; i>=1; --i)
    {
        while(top&&h[st[top]]<h[i]) top--;//将较小值都出栈。
        if(top) ans += st[top]-i-1;//站定挡住了视线，统计两个坐标之间
        else ans += n-i;//全能看见
        st[++top] = i;//入栈，此时进入的是坐标，以便接下来统计
    }
    printf("%lld",ans);
    return 0;
}

int youngsc = yg();
int main(){;}
```
（减少代码复制，共创美好洛谷）


---

## 作者：加勒比·史努比 (赞：8)

## Solve

1.单调队列。

2.既然是找比自己高度小的，就用单调递减。

3.每找到一个比自己高度小的，c[]加1，并加上其的c[];

## Tip

1.单调递减，所以不会找到比自己高度小的奶牛的高度更小的奶牛(向队首遍历)，从而解释了Slove中的步骤3.

2.不开long long 见祖宗。

## Code
```cpp
#include<iostream>
#include<cstdio>
#define N 80010
#define ll long long
using namespace std;  //标准开头
ll n,ans;  //n-奶牛数，ans-答案
ll q[N][3],h[N],c[N];  //q-队列 q[][1]表示奶牛的高度 q[][2]表示奶牛的序号，h-高度，c-同题中的c[]
ll head=1,tail=0;  //头指针，尾指针
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&h[i]);
	for(ll i=n;i>=1;i--){
		while(head<=tail&&h[i]>q[tail][1]){
			c[i]++;
			c[i]+=c[q[tail][2]];
			tail--;
		}
		tail++;
		q[tail][1]=h[i];
		q[tail][2]=i;
		ans+=c[i];
	}
	printf("%lld",ans);  //完美输出
	return 0;
}
```


---

## 作者：Randyhoads (赞：8)

和以前的用STL中的栈的神犇不一样，我是边读边处理的，所以写法有一些不一样，但思路都是一样的

我们要知道当有一只牛比他高时即使后面有更矮的他也看不到了，所以每读进一只牛时就把比他矮的牛都从栈中踢除

（栈可以理解成现在还看到牛的牛的序列），应为他们看不到其他牛了，而在这栈中越前面的身高越高，他也最不容易被踢出

符合先进后出

代码


```cpp
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;
inline int read()
{
    int f=1,x=0;
    char ch;
    do
    {
        ch=getchar();
        if(ch=='-') f=-1;
    }while(ch<'0'||ch>'9');
    do
    {
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }while(ch>='0'&&ch<='9');
    return f*x;
```
}//快读






    
```cpp
int n;
int h;
long long ans=0;
stack<int>st;//STL中的栈
int main()
{
    n=read();
    for(register int i=1;i<=n;i++)
    { 
        h=read();
        while(!st.empty()&&st.top()<=h)//找矮个
        {
            st.pop();
        }
        ans+=st.size();//当前剩下的牛都可以看见这头牛
        st.push(h);//把这头牛加入到可以看见的序列
    }
    printf("%lld",ans); 
}
```

---

## 作者：nothingness (赞：6)

这题貌似不用栈...

思路很简单，对于编号为 ${i}$ 的牛，只要有一头编号为 ${j}$ 的牛 ${(i<j)}$ 高于编号为 ${i}$ 的牛，就能得出 ${c[i]}$ 的值

但是，如果 ${~for(int~~k=i;k<=j;k++)}$ 的话，无疑会TLE ，这时候，就要用到一种类似 递推/链表(到底是啥我也不知道)的方法:

将序列倒着扫,记录比 ${a[i]}$ 大的第一个值的编号 ${next[i]=j}$ ，对于每一头牛，直接查它右边第一头牛的比它高的比它高的比它高的...(此处省略N字)牛，搜到比当前牛高的就停止，这样就可以大幅度节省时间



------------

## Code
```cpp
#include "bits/stdc++.h"
using namespace std;

int n,a[1000001],next[1000001],p;//我就想把数组开大，别拦我
long long ans;//ans>2147483647,我当时被卡了好久

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	a[n+1]=INT_MAX;//设第n+1头(不存在的)牛高2147483647作为终止节点
	for(int i=n;i>0;i--)
	{
		p=i+1;
		while(a[i]>a[p]&&p!=0)
			p=next[p];//通过链表(我也不知道是不是)快速查找第一个比它高的牛
		next[i]=p;//更新第一个比它高的牛
		ans+=p-i-1;//那么i到p之间的牛都比这头牛矮,计入答案
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Setsugesuka (赞：5)

事实上，我们可以运用 $ODT$ 来解决这个问题。

如果我们把这些牛按照高度离散化，当我们从前往后扫描到第 $i$ 只牛的时候，所有比他高且没被挡住的都可以看到他，然后他也加入到队伍里，把比他矮的挡住了。

不难发现把比他矮的挡住的这个过程就是一个朴素的区间推平，我们使用 $ODT$ 来维护这个操作。

值得注意的是
1. 题目有大量赋 $0$ 操作，也就是会形成大量值相等的连续区间，但他们不在同一个节点上。在每次 $assignval$ 操作后进行一次节点合并就能很好地提高复杂度。
2. 我们不需要每次都去从前往后遍历一遍 $set$ 来查找有多少牛比他矮，这个是可以动态维护的。

加入这些优化之后，在开启氧气的情况下，我们的程序可以以 $27ms$ 跑过最大的那个点。

```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline void write(T x)
{
    if(x>9)
    {
        write(x/10);
    }
    putchar(x%10+'0');
}

inline char nc()
{
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}

inline void read(int &sum)
{
    char ch=nc();
    int tf=0;
    sum=0;
    while((ch<'0'||ch>'9')&&(ch!='-')) ch=nc();
    tf=((ch=='-')&&(ch=nc()));
    while(ch>='0'&&ch<='9') sum=sum*10+(ch-48),ch=nc();
    (tf)&&(sum=-sum);
}

const int MAXN=1e6+10;

struct node
{
    int l,r;
    mutable int v;
    node() {}
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    bool operator <(const node &o) const
    {
        return l<o.l;
    }
};

set<node> s;
long long sum=0;

inline void merge(int l)
{
    set<node>::iterator it1,it2,it3;
    it2=s.lower_bound(l);
    if(it2==s.begin())
        return;
    it1=it2,it3=it2;
    it1--,++it3;
    bool pd3=(it3!=s.end());
    if(pd3&&it1->v==it2->v&&it2->v==it3->v&&it1->v==it3->v)
    {
        int l=it1->l,r=it3->r,v=it2->v;
        s.erase(it1,++it3);
        s.insert(node(l,r,v));
    }
    else if(it1->v==it2->v)
    {
        int l=it1->l,r=it2->r,v=it2->v;
        s.erase(it1,++it2);
        s.insert(node(l,r,v));
    }
    else if(pd3&&it2->v==it3->v)
    {
        int l=it2->l,r=it3->r,v=it2->v;
        s.erase(it2,++it3);
        s.insert(node(l,r,v));
    }
}

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos) return it;
    --it;
    int L=it->l,R=it->r,V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,int v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    long long tot=0;
    for(set<node>::iterator it=itl;it!=itr;++it)
        tot+=(it->r-it->l+1)*it->v;
    sum-=tot;
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

inline void add(int l,int r,int v)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    for(;itl!=itr;++itl)
        itl->v+=v;
    sum+=1;
}

int a[MAXN],b[MAXN];

int main()
{
    int n;
    read(n);
    for(int i=1;i<=n;i++)
        read(a[i]),b[i]=a[i];
    sort(b+1,b+n+1);
    int sz=unique(b+1,b+n+1)-(b+1);
    for(int i=1;i<=n;i++)
    {
        int cc=lower_bound(b+1,b+sz+1,a[i])-b;
        a[i]=cc;
    }
    s.insert(node(0,n+5,0));
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        assignval(1,a[i],0);
        merge(a[i]+1);
        ans+=sum;
        add(a[i],a[i],1);
    }
    write(ans);
    return 0;
}
```


---

## 作者：sycqwq (赞：4)

## 首先，来讲一下题意：

有n头牛，每头身高为$h^i$，他们都向右看，只要身高比自己低，就能看到，如果遇到比自己高的，那么，比自己高的牛的右边的牛自己也看不到，求n头牛向右看一共能看到多少头牛。

所以，这一题最主要就是求出 __右边第一个比自己高的牛的位置__ ，那么，这里可以维护一个单调递减栈，p[i]记录每头牛出栈时是第几头牛入栈，所以，第i头年能看到牛数就是p[i]-i-1,至于为什么要减1，是一个数学常识，请自行思考。

## 关于单调递减栈

	假设，数5 1 2 3 2 7一次入栈，如下。
    
   5入栈。
   
   栈内元素（从栈尾到栈顶）：5
    
   1和栈顶元素5作比较，1<5，满足递减性，入栈
   
   栈内元素：5 1
   
    
   3和栈顶元素1作比较，3>1,1出栈,在和5作比较，3<5,3入栈
    
   栈内元素：5 3


   2和3作比较，2<3，满足递减性，入栈
    
   栈内元素：5 3 2


   7和2作比较，7>2,2弹出，再和3作比较7>3,3弹出，再和5作比较，7>5，5弹出，此时栈为空，7入栈
    
   栈内元素：7
    

所以说，这个栈，为了维护递减性，可以不惜把栈顶元素弹出，直到满足递减性。
    


 ##  维护步骤：
    
   1：与栈顶元素比较，若大于栈顶元素（若栈为空转3），转2，否则，转3.
    
   2：栈顶元素弹出，转1.
   
   3：入栈，结束。
   
   好了，上代码：
    
```cpp
#include<bits/stdc++.h>
using namespace std;
int p[500005];
struct node{
	int id;//记录位置
	long long date;//记录身高（别问我为什么开long long
}a[80005];
stack<int> q; 
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].date;
		a[i].id=i;
		if(i==1)//如果i为1，说明还没有元素入栈，直接把位置入栈
			q.push(i);
		else//否则
		{
			while(!q.empty()&&a[q.top()].date/*这里记录的是编号，所以这样处理*/<=a[i].date)//如果栈不为空，并且入栈元素>栈顶元素，那么就把栈顶元素出栈，直到满足其1
			{
				p[q.top()]=i;//记录，这个数是在第i头牛入栈时被弹出的
				q.pop();
			}
			q.push(i);//此时，要么栈空了，要么入栈元素<栈顶元素，直接入栈
		}
	}
	unsigned long long s=0;
//	for(int i=1;i<=n;i++)
//	cout<<i<<' '<<p[i]<<endl;
	for(int i=1;i<n;i++)
	{
		if(p[i]==0)//特判一下，如果p[i]==0那么就说明右边没有比它再大的数了，直接加上它右边的数的个数
			s+=n-i;
		else
			s+=p[i]-i-1;
	}
	cout<<s;
}

```

---

## 作者：轩槿 (赞：2)

-233,楼下我同学，，，不对，，我同桌，，这是一个julao，建议你们参透他的。。

-思路跟楼下一样，，就是写的不一样。。。

```cpp
#include<algorithm>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include  <stdio.h>
#include   <math.h>
#include   <time.h>
#include   <vector>
#include   <bitset>
#include    <queue>
#include    <stack>
#include      <set>
#include      <map>
 using namespace std;
int n；
long long ans;//被这东西坑了5分钟，，害的我打了5分钟游戏
stack<int>q;
int a[80005];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    q.push(a[1]);
    for(int i=2;i<=n;i++){枚举第i头牛
        while(!q.empty()){
            if(a[i]>=q.top())q.pop();//如果此牛高于栈中第一头，就舍去
            else {q.push(a[i]);ans+=q.size()-1;break;}//如果不高于，就入栈，(ans+=q.size()-1)因为自己并不能算
        }
        if(q.empty())q.push(a[i]);//如果栈中没有比它高的，就入栈
    }
    printf("%d",ans);
return 0;
}
```

---

## 作者：peterwuyihong (赞：1)

# $Bad\ Hair\ Day$
## POJ3250
$C_i$为$i$号奶牛一直往前直到$j$号奶牛比它高，的$j-i-1$值，求$\sum_1^nC_i$

考虑维护一个单调递减的栈，如果当前牛的高度比栈中的元素高，那么这些元素肯定没有用了，看不到牛了。因为当前牛的坐标$i$一定大于栈中元素坐标$j$，而且$h_i$又高于或等于$h_j$，这表明牛$j$被挡住了，看不见后面的牛了，就把它弹出来（使牛原地起飞），那么剩下的牛就是满足$i>j$且$h_i<h_j$即单调递减，那么排除完没用的牛以后，栈中剩下的牛就能看到当前牛了
## Code
```cpp
#include<iostream>
#include<cstdio>
#define maxn 100010
using namespace std;
template<class T>void read(T &__x) {
	__x=0;
	short __f=1;
	char __ch=getchar();
	while(__ch<'0'||__ch>'9') {
		if(__ch=='-')__f=-1;
		__ch=getchar();
	}
	while(__ch>='0'&&__ch<='9') {
		__x=(__x<<1)+(__x<<3)+(__ch^48);
		__ch=getchar();
	}
	__x*=__f;
}
int n,x;
long long ans;
int s[maxn],top;
signed main() {
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	read(n);
	while(n--) {
		read(x);
		while(top&&s[top]<=x)top--;
		ans+=top;
		s[++top]=x;
	}
	cout<<ans;
}

```


---

## 作者：yezl (赞：1)

### 题意概述：

给定 $ n $ 头奶牛的身高，记为： $ h_1,h_2,h_3…h_n $ 若第 $ i $ 头奶牛比它前面的 $ j $ 头奶牛都要高的话，那么它就可以看到它们的头发（即 $ h_i>h_{i+1}>h_{i+2}>…>h_{j} $ ）  
评价：~~废话~~ 太细致了。

### 思路：

关于这道题我们~~还是先看标签~~，不对，这道题其实不看就可以知道是用单调栈啦......首先，它要求 $  {\textstyle \sum_{i=1}^{n}}C_i  $ ，那这个是什么意思呢？就是要你把从1到 $ n $ 所有奶牛可以看到的头发数加起来就是答案了，记住要开 $ \texttt{long\;long} $ 呀，不要像我一样浪费个10分钟。

根据题意，我们要维护一个单调递减栈，定义栈顶指针 $ tot $ ，然后就是进栈，记住，每个元素都要进栈且只能进栈一次，如果这个元素破坏了这个单调递减栈的单调性，那么就让栈内比它小的元素全部出栈（赶出去，也就是 $ tot $ - -），每次进栈时 $ ans $ 都要累加上 $ tot-1 $ 因为这就是这头奶牛可以看到的头发数呀（想一想，为什么），然后这个程序就完成啦。想要优化的同学可以加一个快读O，本题的数据量还是比较大的。

### 快读模板1（个人编写，不完善哈）：

```c
inline int read()
{
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+ch-'0';
		ch=getchar();
	}
	return num;
}
```

### 完整代码：

```c
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
const int N=100010;
int n,sta[N],tot,x;//sta 数组就是单调递减栈啦 
long long ans=0;//注意要 long long 呀 
inline int read()//快读函数 
{
	int num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+ch-'0';
		ch=getchar();
	}
	return num;
}
int main()
{
	n=read();//注意快读的读入方式o 
	for(int i=1;i<=n;i++)
	{
		x=read();
		while(tot>0 && x>=sta[tot])//如果当前栈不空并且要进栈的元素大于当前栈顶元素 
			tot--;//当前栈内元素出栈 
		sta[++tot]=x;//进栈 
		ans+=tot-1;//累加 
	}
	printf("%lld",ans);//输出 
	return 0;
}
```

希望可以帮到大家。

---

## 作者：S1gMa (赞：1)

```
每一头牛都站在同一排面朝东方，而且每一头牛的身高为h_i
```
 看到这句话，就可以知道是单调栈裸题
 
 单调栈 就是要维护单调性 --- 单调递减

这道题可以看成类似于这样的队形
```
|
|  |     |
|  |  |  |
|  |  |  |  |
|  |  |  |  |  |

```
很容易就可以找到关键点 只需要一直入栈 直到有一头牛比前一头高 则弹出栈中元素统计和直到大于此元素 继续维护单调性
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    long long high, ans;
    stack<long long> S;
    while ((scanf("%lld", &n)) != EOF)
    {
        ans = 0;
        cin >> high;
       S.push(high);
        for (int i = 1; i < n; i++)
        {
            cin >> high;
            while (!S.empty() && S.top() <= high)//如果栈非空 且遇到了前一个的身高 比 后一个的身高矮 则一直弹出 直到大于新入的元素
            {
                S.pop();
            }
            ans += S.size();//统计和
            S.push(high);
        }
        cout << ans << endl;//输出即可qwq
        while (!S.empty())
        {
            S.pop();
        }
    }
}

---

## 作者：Dawn_Sdy (赞：1)

这是一道很简单的题目。

可以发现，若牛i能从i+1一直看到牛j，则区间i~j一定是单调递减的。

所以我们只需要在每读入一个数时判断他是否满足单调递减即可。

很容易想到用单调栈来维护。

即每次读入i，依次判断栈的栈顶是否小于i，如果小于，就一直弹出。

直到栈顶元素不小于i，则现在栈中的元素个数，就可以累加到答案当中。

上AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n; 
int st[80005],top;
long long ans;
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++)	
		{
		int x;
		scanf("%d",&x);
		while (top && x>=st[top])
			  top--;
		ans+=top;
		st[++top]=x;
		}
	cout<<ans;
	return 0;
}

```

---

## 作者：STOcjyORZ (赞：1)

## 一份好理解的单调栈
翻了一下其他题解,用单调栈的其实方法大同小异,但不用那么麻烦.

------------
- 首先分析思路,牛只能向右看,所以仅需扫一遍单调栈即可.
- 接下来,由于牛只能看见他右侧比他低的牛,所以我们可以考虑使用单调递减的栈:
对于新元素,若高度小于栈顶元素就加进来,同时更新答案 **(** 这个新元素能被栈内原有的所有牛看见(因为他是递减的),所以答案要加上top-1的数量,将看见转换为被看见去理解 **)**.
若高度大于等于的话就一个一个弹栈直到小于即可;

------------
具体实现见~~简短~~的代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans=0;
ll a[100050]={0};
ll zhan[100050]={0};
int n,top=0;
int main()
{
cin>>n;
for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
for(int i=1;i<=n;i++)
{
	while(top&&a[i]>=zhan[top])//一定要加上等于号!题意是严格递减.
	{
	top--;//弹栈
	}
	zhan[++top]=a[i];
	ans+=(top-1);//核心!可以自己手画模拟一下	
}
cout<<ans;
return 0;
}
```



---

## 作者：Michael_Bryant (赞：1)

[先推一发我的博客](https://lfd2002.com/)

有个东西叫做单调栈
就是说对于一个栈 我们严格维护栈内元素单调性

每次新加入一个元素 我们从栈顶开始判断

只要不满足单调性就删除

然后发现这个性质刚好可以用在这道题上面

从后往前找 找到高度比自己大的停止

然后用一个后缀和（？的思想

只要我比你高 你能看到的我都能看到

这样就结束了 

要是说坑的话 大概就是ans需要用long long吧

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 800001
#define ll long long
int s[N],top,h[N],n,sum[N];
ll ans;
inline int read()
{
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++) h[i]=read();
    for(int i=n;i>=1;i--)
    {
        while(top&&h[i]>h[s[top]]) sum[i]+=sum[s[top--]]+1;
        s[++top]=i;
    }
    for(int i=1;i<=n;i++) ans+=sum[i];
    printf("%lld\n",ans);
}

```

---

