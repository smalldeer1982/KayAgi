# [USACO18DEC] The Bucket List B

## 题目描述

Farmer John 正在考虑改变他给奶牛挤奶的时候分配牛奶桶的方式。他认为这最终能使得他使用数量更少的桶，然而他不清楚具体是多少。请帮助他！

Farmer John 有 $N$ 头奶牛（$1\le N\le 100$），方便起见编号为 $1\dots N$。 第 $i$ 头奶牛需要从时间 $s_i$ 到时间 $t_i$ 之间挤奶，并且挤奶过程中需要用到 $b_i$ 个桶。于是多头奶牛可能在同一时刻都在挤奶；如果这样，他们不能使用相同的桶。也就是说，一个在第 $i$ 头奶牛挤奶时用的桶不可以被任何在时间 $s_i$ 到时间 $t_i$ 之间挤奶的其他奶牛使用。当然，这个桶在这段时间之外可以被其他奶牛所使用。为了简化他的工作，FJ 保证在任一时刻，至多只有一头奶牛开始或是结束挤奶（也就是说，所有的 $s_i$ 和 $t_i$ 各不相同）。

FJ 有一个储藏室，里面有依次编号为 $1$、$2$、$3$、……的桶。在他的挤奶策略中，当某一头奶牛（比如说，奶牛 $i$）开始挤奶（在时间 $s_i$），FJ 就跑到储藏室取出编号最小的 $b_i$ 个桶分配给第i头奶牛用来挤奶。

请求出 FJ 需要在储藏室中存放多少个桶才能使得他能够顺利地给所有奶牛挤奶。


## 说明/提示

在这个例子中，FJ 需要 $4$ 个桶：他用桶 $1$ 和桶 $2$ 来给奶牛 $3$ 挤奶（从时间 $2$ 开始）。他用桶 $3$ 给奶牛 $1$ 挤奶（从时间 $4$ 开始）。当奶牛 $2$ 在时间 $8$ 开始挤奶时，桶 $1$ 和桶 $2$ 可以再次利用，然而桶 $3$ 不可以，所以他会使用桶 $1$、桶 $2$ 和桶 $4$。

## 样例 #1

### 输入

```
3
4 10 1
8 13 3
2 6 2```

### 输出

```
4```

# 题解

## 作者：_Qer (赞：19)

裸差分吧，~~虽然数据水暴力随便锤~~

对于每个$s,t,b$，标记从$s$到$t$间需要的桶数量加上$b$，用差分来搞，一个$p$数组，$p_i$表示$i+1$时刻比$i$时刻需要的桶数多$p_i$，那么对于每头牛，$p_{s-1}$就要加$b$，$p_t$就减$b$，最后求前缀和再取个$max$就完事了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, s, t, b, p[1010];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &s, &t, &b);
		p[s - 1] += b, p[t] -= b;
	}
	int ans = 0, h = 0;//h即前缀和
	for (int i = 0; i <= 1001; ++i) {
		ans = max(ans, h);
		h += p[i];
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：damage (赞：6)

### 题解

```USACO 2018.12月赛 铜组 第二题```

其实这题只要动动脑筋（大佬：动什么脑筋！）就很简单了，其实就是离散化的思想（雾）

因为挤奶的时间范围很小，而又没有重复，所以只要用```used[]```数组表示当前所需要的桶的数量。

对于每个开始时间让```used[s]=b```，即需要用桶，对于每个结束时间则让```used[t]=-b```，即挤完奶桶在这个时间换回去了，桶的需求量减少了$b$（因为有加才有减，所以根本不需要考虑负数的情况）

最后再从最早时间（方便来说就是$1$）枚举到最晚时间（方便来说就是$1000$），寻找```used[]```的最大值即可。

---

### 代码

```cpp
#include<stdio.h>
int n,s,t,b,used[1010],now,res;
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d%d",&s,&t,&b);
        used[s]=b; //需要用桶
        used[t]=-b; //可以换桶了
    }
    for(register int i=1;i<=1000;++i)
    {
        now+=used[i]; //累加用的桶的数量
        if(now>res) res=now; //找出最大值
    }
    printf("%d\n",res);
    return 0;
}
```

---

## 作者：yubing_lml (赞：4)

NO.6蒟蒻表示还没有看过差分，就用简单的模拟做了一下，非常好理解~

把奶牛的开始挤奶时间和结束时间还有需要的桶数用结构体存储，用结构体数组a[i]保存每只奶牛的情况；用mark数组标记奶牛是否取完奶，available表示当前可用的桶数，ans存储答案，二者均初始化为0。

起初先用sort()函数对奶牛按开始挤奶时间排个序，方便以后的遍历。

之后，对每只奶牛i，都判断它前面的i-1只奶牛是否取完奶，如果奶牛k取完奶并且mark[k]==false（表示是在这只奶牛来之后才挤完奶，之前没有挤完奶），则available=available+a[k].bucket。

对前面的奶牛遍历完后，判断available的值是否大于当前奶牛i需要的桶数，若大于等于，直接available减去这个桶数；否则ans+=a[i]-available,同时将available置为0，表示当前没有可用的桶了。

挤奶到这里就告一段落了，希望我的题解可以扩展大家的思维(*^▽^*)，有问题欢迎交流~


```cpp
#include <iostream>
#include<cstring>
#include<algorithm>
using namespace std;

int n, ans = 0, available;  
bool mark[107];

struct cow
{
	int start, end;
	int bucket;

	bool operator <(const cow&b)const
	{
		return start < b.start;
	}
}a[107];

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i].start >> a[i].end >> a[i].bucket;
	sort(a + 1, a + 1 + n);
	memset(mark, false, sizeof(mark));
	available = 0;
	for (int i = 1; i <= n; i++)
	{
		for(int j=1;j<i;j++)
			if (a[j].end < a[i].start&&mark[j] == false) //该奶牛已经挤完奶，标记
			{
				mark[j] = true;
				available += a[j].bucket;
			}
		if (available >= a[i].bucket)
			available -= a[i].bucket;
		else
		{
			ans += a[i].bucket - available;
			available = 0;
		}
	}
	cout << ans;
	cin >> n;
	return 0;
}
```


---

## 作者：jacktang233 (赞：2)

Cu的第二题       
好像也没啥难度        
我们把样例手抄一下    
不难发现是一个区间覆盖的问题   
简单来说就是区间修改区间查询最大值       
那么对于Cu组的同学们来说怎么做呢      
~~教练我会线段树~~         
emmmm          
logn数据结构太高级了      
~~教练我会分块~~          
其实没必要       
直接暴力即可            


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n;
int l,r;
int w;
int tm[2000]={0};
int main() 
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		cin>>l;cin>>r;cin>>w;
		for(int j=l;j<=r;j++)
			tm[j] += w;
		
	}
	int maxx = -1;
	for(int i=1;i<=1000;i++)
		if(maxx < tm[i])
			maxx = tm[i];
			
	cout<<maxx<<endl;
	return 0;
	
}
```




---

## 作者：monstersqwq (赞：1)

这题一看就是~~暴力~~差分+前缀和啊（不懂差分的参考我[这篇题解](https://www.luogu.com.cn/blog/yansihenghuhu/solution-sp10500) [这道题](https://www.luogu.com.cn/problem/SP10500)，和这道题几乎没有区别）

定义一个 $p$ 数组，$p_i \gets a_i-a_{i-1}$ 每次输入 $s,t,b$，$p_{s} \gets p_s+b,p_{t+1} \gets p_{t+1}-b$。然后求一遍 $p$ 数组的前缀和，输出最大的前缀和。

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>//可爱的头文件 
using namespace std;
int p[1005],s,t,b,ans=-1,sum=0,n;//ans是答案，sum是p的前缀和，每次更新再更新答案，不需要建立数组 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s>>t>>b;
		p[s]+=b;
		p[t+1]-=b;
	}
	for(int i=1;i<=1000;i++)//懒得求时间的最大值了，就循环到最大值好了 
	{
		sum+=p[i];
		ans=max(ans,sum);
	}
	cout<<ans<<endl; 
	return 0;
}
```


---

## 作者：lytqwq (赞：1)

题目链接：[https://www.luogu.org/problemnew/show/P5117](https://www.luogu.org/problemnew/show/P5117)

1.
把挤奶开始的时间看做拿桶

把挤奶结束的时间看做放桶

储存在结构体中

```cpp
#define N 201
int n;
struct d{
	int time,cost;
}qwq[N];
```


2.
输入时对应的量存在结构体数组里

```cpp
cin>>n;
for(int i=1;i<=n;i++)
{
	int s,t,b;
	cin>>s>>t>>b;

	qwq[i*2-1].time=s;
	qwq[i*2-1].cost=b;
	qwq[i*2].time=t;
	qwq[i*2].cost=-b;
}
```

3.

按时间先后排序

在结构体中加这个：

```cpp
bool operator < (const d x) const
{
	return time < x.time;
}
```
在主程序里sort一下就行了

4.
按排序后的顺序遍历，模拟维护拿杯的数量，ans取max

```cpp
	int now=0,ans=0;
	for(int i=1;i<=2*n;i++)
	{
		now+=qwq[i].cost;
		
		ans=max(ans,now);
	}
```



完整程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 201
int n;
struct d{
	int time,cost;
	bool operator < (const d x) const
	{
		return time < x.time;
	}
}qwq[N];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int s,t,b;
		cin>>s>>t>>b;
		
		qwq[i*2-1].time=s;
		qwq[i*2-1].cost=b;
		qwq[i*2].time=t;
		qwq[i*2].cost=-b;
	}
	sort(qwq+1,qwq+2*n+1);
	int now=0,ans=0;
	for(int i=1;i<=2*n;i++)
	{
		now+=qwq[i].cost;
		
		ans=max(ans,now);
	}
	cout<<ans;
}
```


---

## 作者：__Hacheylight__ (赞：0)

T2 The Bucket List

【题意】

有n只奶牛，每头奶牛$i$会在$s[i]$时刻索要$b[i]$个桶，然后在$t[i]$时归还，请问要准备几个同才能满足要求。

【分析】

水题一道

搞个$struct(tim,op,sum)$,表示在$tim$时刻发生的时间，$op$表示属性，0为索要，1为归还，$sum$表示数量。这样会有$2n$个$struct$

把$struct$按$tim$排个序，然后$for$一遍处理一下就可以了。

【代码】

```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 110 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD = 1000000007 ;

inline int read(){
    int X = 0, w = 0 ;
    char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
    cout << x << endl ;
    exit(0) ;
}

void PRINT(string x) {
    cout << x << endl ;
    exit(0) ;
}

void douout(double x){
     printf("%lf\n", x + 0.0000000001) ;
}

int n, ans, res, cnt ;

struct events {
	int tim, ch, sum ;
} a[N << 1] ;

bool cmp(events a, events b) {
	return a.tim < b.tim ;
}

int main() {
	scanf("%d", &n) ;
	for (int i = 1, s, t, b; i <= n; i++) {
		scanf("%d%d%d", &s, &t, &b) ;
		a[++cnt] = (events) {s, 0, b} ;
		a[++cnt] = (events) {t, 1, b} ;
	}
	sort(a + 1, a + cnt + 1, cmp) ;
	for (int i = 1; i <= cnt; i++) {
		events tmp = a[i] ;
		if (tmp.ch == 0) ans += tmp.sum ;	
		else ans -= tmp.sum ;
		res = max(res, ans) ; 
	}
	printf("%d\n", res) ;
}
```

---

## 作者：封禁用户 (赞：0)

题面很简单，有$N$条线段，让你求被覆盖最多的一个点被覆盖的次数。

数据范围，一看傻了，$N\leq100$？？？

所以可以用很多种方法，差分，树状数组，纯暴力，线段树，都行。

下面是我的线段树代码，~~不愿写了抄的我之前的线段树板子~~。
```cpp
#include <cstdio>
#include <iostream>
#include <stack>
#include <utility>
#include <algorithm>
#include <set>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#define rep(i,a,b) for(int i=(a);i<=(b);++i) 
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define gc() getchar()
#define endll putchar('\n')
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double ld;
inline ll read(){
    char ch=gc();
    ll x=0,f=1;
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=gc();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=gc();
    }
    return x*f;
}
inline void print(ll k){
    if(k<0) k=-k,putchar('-');
    if(k>9) print(k/10);
    putchar(k%10+48);
}
inline void println(ll k){
    print(k);
    endll;
}
inline void printsp(ll k){
    print(k);
    putchar(' ');
}
const int maxn=101000;
ll seg[maxn<<2],tag[maxn<<2],n;
inline int lson(int p){
    return p<<1;
}
inline int rson(int p){
    return p<<1|1;
}
inline void push_up(int p){
    seg[p]=max(seg[lson(p)],seg[rson(p)]);
}
inline void f(int p,int l,int r,ll k){
    tag[p]=tag[p]+k;
    seg[p]=seg[p]+k;
}
inline void push_down(int p,int l,int r){
    int mid=(l+r)>>1;
    f(lson(p),l,mid,tag[p]);
    f(rson(p),mid+1,r,tag[p]);
    tag[p]=0;
}
inline void update(int dl,int dr,int l,int r,int p,ll k){
    if(dl<=l&&r<=dr){
        seg[p]+=k;
        tag[p]+=k;
        return;
    }
    push_down(p,l,r);
    int mid=(l+r)>>1;
    if(dl<=mid) update(dl,dr,l,mid,lson(p),k);
    if(dr>mid) update(dl,dr,mid+1,r,rson(p),k);
    push_up(p);
}
inline ll query(int dl,int dr,int l,int r,int p){
    ll res=-0x3f3f3f3f;
    if(dl<=l&&r<=dr) return seg[p];
    int mid=(l+r)>>1;
    push_down(p,l,r);
    if(dl<=mid) res=max(query(dl,dr,l,mid,lson(p)),res);
    if(dr>mid) res=max(res,query(dl,dr,mid+1,r,rson(p)));
    return res;
}
int main(){
    //freopen("blist.in","r",stdin);
    //freopen("blist.out","w",stdout);
    n=read();
    rep(i,1,n){
        int x=read(),y=read(),k=read();
        update(x,y,1,2000,1,k);
    }
    println(query(1,2000,1,2000,1));
    return 0;
}
```


---

## 作者：djh123 (赞：0)

简单题意：

每次在 $l - r$ 区间内加上一个数，求最大值。

由于$n, l, r$ 都在 1000 的范围内，所以对于每次加操作，可以直接 for 一遍加上。

最后求最大值即可。

```cpp

#include <cstdio>
#include <iostream>
using namespace std;
int f[10500];
int main() {
    int n, l, r, x; scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d %d %d", &l, &r, &x);
        for(int j = l ; j <= r ; ++ j) f[j] += x;
    }
    int ans = 0;
    for(int i = 1 ; i <= 1000 ; ++ i) ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}

```

复杂度 $O(n^2)$

这道题也有复杂度更优秀的做法，差分。

对于每一次操作，可以在 $l$ 处 加 x，在 $r + 1$ 处 减x

那么对于差分后的数组，求一遍前缀和就是原数组了

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int f[10500];
int main() {
    int n, l, r, x; scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%d %d %d", &l, &r, &x);
		f[l] += x;
		f[r + 1] -= x;//要注意差分数组的边界情况
    }
    int ans = 0, now = 0;
    for(int i = 1 ; i <= 1000 ; ++ i) now += f[i], ans = max(ans, now);
    printf("%d\n", ans);
    return 0;
}
```

复杂度$O(n)$

---

