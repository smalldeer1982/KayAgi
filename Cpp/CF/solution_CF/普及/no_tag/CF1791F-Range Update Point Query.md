# Range Update Point Query

## 题目描述

## 题意描述

给定一个数列 $ a_1, a_2, \cdots, a_n $，你需要对这个序列进行如下的两种操作：

- $ 1 $ $ l $ $ r $ — 对于任意的 $ l \le i \le r$，将 $ a_i $ 修改为 $ a_i $ 的数位之和。
- $ 2 $ $ x $ — 输出 $ a_x $ .

## 说明/提示

第一组测试数据的操作过程如下：

- 开始时，$ a = [1, 420, 69, 1434, 2023] $。
- 对 $ l=2 $，$ r=3 $ 执行操作, 完成后 $ a $ 变为 $ [1, \textcolor{red}{6}, \textcolor{red}{15}, 1434, 2023] $。
- 询问 $ x=2 $ , $ x=3 $ 以及 $ x=4 $，输出 $ 6 $，$ 15 $ 以及 $ 1434 $。
- 对 $ l=2 $ , $ r=5 $ 执行操作，完成后 $ a $ 变为 $ [1, \textcolor{red}{6}, \textcolor{red}{6}, \textcolor{red}{12}, \textcolor{red}{7}] $。
- 询问 $ x=1 $，$ x=3 $ 以及 $ x=5 $，输出 $ 1 $，$ 6 $ 以及 $ 7 $。

## 样例 #1

### 输入

```
3
5 8
1 420 69 1434 2023
1 2 3
2 2
2 3
2 4
1 2 5
2 1
2 3
2 5
2 3
9999 1000
1 1 2
2 1
2 2
1 1
1
2 1```

### 输出

```
6
15
1434
1
6
7
36
1
1```

# 题解

## 作者：Sincerin (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/CF1791F)

[更好的阅读体验](https://www.luogu.com.cn/blog/sincerin520/solution-CF1791F)

#### Update: 2023.2.6 14:11

#### 修改了解法一的时间复杂度，看错题了。

$$\  $$

# 题意

给定一个整数 $t$ 表示有 $t$ 组数据。

每组数据第一行给定两个整数 $n$ 和 $m$ 分别表示一共有 $n$ 个数和 $m$ 次查询，接下来一行 $n$ 个整数 $a_1 ,a_2 \ ... \ a_n$。

接下来 $m$ 行每行给定一个 $opt\in[1,2]$ 表示操作种类。
- $1 \ \ l \ \ r$ 对于每个 $a[i]\ (i \in [l,r])$ 修改为其各个位上数相加的和。

- $2 \ \ x  \ $ 查询 $a_x$ 的值。


$1\leq t\leq 1000 \ , \ 1 \le a_i \le 10^9 .$

$1 \le n,m\le 2 \times 10^5 .$

# 解析

首先这个区间修改单点查询一眼数据结构题。但是这个区间修改 $\dots$ 怎么这么怪捏？首先这个东西是可以用线段树维护的。但是每个元素的值修改完都是不同的，所以无法对一个区间进行操作，只能 $\Theta(n)$ 地遍历整棵子树进行修改操作。

- 注：下文用 $\operatorname{popcount_{10}}(x)$ 来表示 $x$ 在十进制下各个位上数的和。

## $\ \ \ \ $做法1

首先是常规做法。在这里我维护了一个区间赋值 $\operatorname{tag}$ 以及区间最大值最小值，并进行了一个小小的优化：

- 当区间最大值为个位数时，很显然整个区间都没有必要再修改，其左右子树也不必修改。

- 当区间所有数都相等（最大值与最小值相等）时，可以直接给该区间赋值为 $\operatorname{popcount_{10}}(x)$。
 
分析一下势能，对于 $x \le 10^9 $ 的最大的 $\operatorname{popcount_{10}}(x)$ 只有 $81$，这就意味着最多只会开 $2$ 次就会变成一位数。这份代码可以跑到 $\Theta(n \log n)$ 级别左右。 


反正我实测这个玩意跑的飞快，大概严格单 $\log$ 的速度。


## $\ \ \ \ $AC Code

```cpp
//373ms C++14(GCC 9)-O2 32.12MB 2.06KB 

#include<iostream>
#include<cstdio>  
#include<algorithm> 
using namespace std;  
const int N=200005;
#define int long long  
int T,n,m,l,r,x,y,z,op;
#define lson(p) p<<1
#define rson(p) p<<1|1
struct SegmentTree{
    int l,r; 
    int maxn,minn;
	int tag;
    #define l(i) t[i].l
    #define r(i) t[i].r  
    #define maxn(i) t[i].maxn
    #define minn(i) t[i].minn
    #define tag(i) t[i].tag
}t[N<<2];
int a[N];
inline void pushup(int p)
{	
	maxn(p)=max(maxn(lson(p)),maxn(rson(p)));
	minn(p)=min(minn(lson(p)),minn(rson(p)));
}
inline void build(int p,int l,int r)
{
    l(p)=l;  r(p)=r; tag(p)=INT_MAX;
    if(l==r) 
    {
        maxn(p)=minn(p)=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(lson(p),l,mid); 
	build(rson(p),mid+1,r);
    pushup(p);
}
inline void spread(int p)
{   
    if(tag(p)!=INT_MAX)
    {
		tag(lson(p))=tag(p);  maxn(lson(p))=tag(p);  minn(lson(p))=tag(p);
		tag(rson(p))=tag(p);  maxn(rson(p))=tag(p);  minn(rson(p))=tag(p);
    	tag(p)=INT_MAX;
	}
}
inline int query(int p,int x)
{
	if(l(p)==r(p)) return maxn(p);
	spread(p);
	int mid=(l(p)+r(p))>>1; 
	if(x<=mid) return query(lson(p),x);
    else return query(rson(p),x); 
}
inline int popcount(int val)
{
	register int temp=0;
	for(;val;val/=10) temp+=val%10;
	return temp;
}
inline void change(int p,int l,int r)
{
    if(maxn(p)<=9) return; 
    if(l<=l(p)&&r>=r(p)) 
	{
		if(minn(p)==maxn(p))
	    {
			register int d=popcount(maxn(p));
	        tag(p)=d; maxn(p)=d; minn(p)=d; return;
		}
	} 
	spread(p);  
    register int mid=(l(p)+r(p))>>1;
    if(l<=mid) change(lson(p),l,r); 
	if(r>mid) change(rson(p),l,r);
    pushup(p);
}
signed main(void)
{  
	freopen("CF1791F.in","r",stdin);
	scanf("%lld",&T);	
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		for(register int i=1;i<=n;++i) scanf("%lld",&a[i]);
		build(1,1,n);
		for(register int i=1;i<=m;++i)
		{
			scanf("%lld",&op);
			if(op==1)
			{
				scanf("%lld%lld",&l,&r);
				change(1,l,r);
			}
			else
			{
				scanf("%lld",&x);
				printf("%lld\n",query(1,x)); 
			}
		}
	}
    return 0;
}  
```

[AC Record](https://www.luogu.com.cn/record/101522977)


## $\ \ \ \ $做法2

首先我们知道只需要支持单点查询，所以珂以记录每个点的修改次数 $x$，查询时暴力执行这 $x$ 次操作来模拟即可。

这样的最坏时间复杂度在 $\Theta(c \log n \ + q \ (\log n + c))$。

- $c$ 指的是修改次数，$q$ 为查询次数。

当然你完全可以把它看做 $\Theta(n \log n)$。

至于优化 $\dots$ 可以在每次模拟后更新 $a_x$ 的值并将原来这个节点加上的操作数清零。虽然这样清除是 $\Theta(\log n)$ 的并且这样跑的更慢了。~~不过数据大点就好使了。~~

## $\ \ \ \ $ AC Code

```cpp
//389ms C++14(GCC 9)-O2 26.00MB 2.42KB 

#include<iostream>
#include<cstdio>   
using namespace std;
#define int long long   
const int N=200005; 
#define lson(p) p<<1
#define rson(p) p<<1|1
struct SegmentTree{
    int l,r; 
    int dat;
    int add;
    #define l(i) t[i].l
    #define r(i) t[i].r 
    #define dat(i) t[i].dat
    #define add(i) t[i].add
}t[N<<2];
int T,n,m,l,r,op,x,a[N];
inline void pushup(int p){dat(p)=dat(lson(p))+dat(rson(p));}//个人习惯
inline void build(int p,int l,int r)//建树 
{
    l(p)=l;  r(p)=r; add(p)=0;
    if(l==r) {dat(p)=0;return;};
    register int mid=(l+r)>>1;
    build(lson(p),l,mid);
	build(rson(p),mid+1,r);
    pushup(p);
}
inline void spread(int p)//pushdown函数下传懒标记 
{ 
    if(add(p)) 
    {
    	dat(lson(p))+=add(p)*(r(lson(p))-l(lson(p))+1); 
		dat(rson(p))+=add(p)*(r(rson(p))-l(rson(p))+1); 
        add(lson(p))+=add(p); add(rson(p))+=add(p); 
		add(p)=0;//清标记 
    }
}
inline void change(int p,int l,int r)//区间加 
{
    if(l<=l(p)&&r>=r(p))
    {
        ++add(p); dat(p)+=(r(p)-l(p)+1);
        return;
    }
    spread(p);
    register int mid=(l(p)+r(p))>>1;
    if(l<=mid) change(lson(p),l,r);
    if(r>mid) change(rson(p),l,r);
    pushup(p);
}
inline void Delete(int p,int x)//查询完更新值并删除之前加的。 
{
    if(l(p)==r(p)) 
    {
    	dat(p)=0;
    	return; 
	} 
    spread(p);
	register int mid=(l(p)+r(p))>>1;  
    if(x<=mid) Delete(lson(p),x);
    else Delete(rson(p),x);
} 
inline int query(int p,int x)//单点查询 
{
    if(l(p)==r(p)) return dat(p);
    spread(p);
    register int mid=(l(p)+r(p))>>1;  
    if(x<=mid) return query(lson(p),x);
    else return query(rson(p),x);
} 
inline int popcount(int x)//求一个数各个位上数的和 
{
	register int val=a[x],cnt=query(1,x);
	register int temp=0;//temporary
	for(register int i=1;i<=cnt;++i)
	{ 
		if(val<=9) return val; //注意这里 
		temp=0;for(;val;val/=10) temp+=val%10;
		val=temp;
	}
	return val;
}
signed main(void)
{
	freopen("CF1791F.in","r",stdin);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		build(1,1,n);
		for(register int i=1;i<=n;++i) scanf("%lld",&a[i]);
		for(register int i=1;i<=m;++i)
		{
			scanf("%lld",&op);
			if(op==1)
			{
				scanf("%lld%lld",&l,&r);
				change(1,l,r);
			}
			else
			{
				scanf("%lld",&x);
				int ans=popcount(x);
				a[x]=ans;//更新a[x] 
				Delete(1,x);//把a[x]之前的操作次数删掉 
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}

```
[AC Record](https://www.luogu.com.cn/record/101524650)

线段树常数大的一言难尽。总之我爱线段树！我也爱给我我点赞的你们![](//图.tk/2)！



---

## 作者：Ycyofmine (赞：7)

# 翻译
有一个长度为 $n$ 的数组，有 $q$ 次询问。

有以下两种操作：

1.给定 $l$，$r$ 使得连续区间 $[l,r]$ 内的 $a_i$ 变成其本身的所有数位之和。

2.给定 $x$，输出 $a_x$。
## 并查集解法
由于多次将 $a_i$ 变成本身的各数位之和，$a_i$ 小于 10 后就不会再改变。

故使用并查集**维护序列连通性**，即跳过这些无法改变的 $a_i$。
```cpp
for (int i = find(fa[l]); i <= r; i = fa[find(i + 1)]) {
	a[i] = f(a[i]);
	if (a[i] < 10)
		fa[i] = fa[i + 1];
}
```
### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
constexpr int N = 2e5 + 5;

int fa[N], a[N];

int find(int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int f(int x) {
	int sum = 0;
	while (x) {
		sum += x % 10;
		x /= 10;
	}
	return sum;
}

void ac() {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> a[i];
	iota(fa, fa + n + 5, 0);
	while (q--) {
		int o; cin >> o;
		if (o == 1) {
			int l, r;
			cin >> l >> r;
			for (int i = find(fa[l]); i <= r; i = fa[find(i + 1)]) {
				a[i] = f(a[i]);
				if (a[i] < 10)
					fa[i] = fa[i + 1];
			}
		} else {
			int x; cin >> x;
			cout << a[x] << '\n';
		}
	}
}

signed main() {	
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	int tt = 1;
	cin >> tt;
	while (tt--) ac();
	return 0;
}
```


---

## 作者：Flanksy (赞：6)

### 线段树

------------

很容易看出单个数字的操作次数存在上界，保证数组中数位为 $1$ 的元素不被重复更新就可以维持时间复杂度。

使用线段树维护序列，每次对区间暴力操作，对于全部元素数位为 $1$ 的区间标记死亡并在操作时跳过。每个数至多被操作三次，视为常数。由于 $n$，$q$ 同阶，时间复杂度 $O(n\log n)$。

```cpp
#include<algorithm>
#include<iostream>
using namespace std;
struct Segment{int l,r,w;bool d;}s[800001];
int T,n,q;
void build(int u,int l,int r){
	s[u].l=l,s[u].r=r,s[u].w=0;
	if(l==r){cin>>s[u].w,s[u].d=s[u].w<10;return;}
	build(u*2,l,(l+r)/2);build(u*2+1,(l+r)/2+1,r);
	s[u].d=s[u*2].d&&s[u*2+1].d;
}
void change(int u){
	int now=0;
	while(s[u].w) now+=s[u].w%10,s[u].w/=10;
	s[u].w=now,s[u].d=s[u].w<10;
}
void update(int u,int l,int r){
	if(s[u].l>r||s[u].r<l||s[u].d) return;
	if(s[u].l==s[u].r) change(u);
	else{
		update(u*2,l,r),update(u*2+1,l,r);
		s[u].d=s[u*2].d&&s[u*2+1].d;
	}
}
int query(int u,int p){
	if(s[u].l>p||s[u].r<p) return 0;
	if(s[u].l==s[u].r) return s[u].w;
	return max(query(u*2,p),query(u*2+1,p));
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	for(cin>>T;T;T--){
		cin>>n>>q,build(1,1,n);
		while(q--){
			static int l,r,opt;
			cin>>opt;
			if(opt==1) cin>>l>>r,update(1,l,r);
			else cin>>l,cout<<query(1,l)<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：aCssen (赞：4)

数据结构学傻了。
### Solution
一种显然正确的做法：维护每个数被操作的次数，询问时再模拟操作。

所以我们只需要一个数据结构，支持区间加 $1$，单点查询，可以使用常数小的树状数组，详见[此题](https://www.luogu.com.cn/problem/P3368)。

但是一个数的操作次数级别是 $O(q)$ 的，仍然无法通过。但我们知道，对一个 $<10$ 的数进行操作，该数的值没有变化，而对于任意一个 $ \le10^9$ 的数，最多进行三次操作就会 $<10$，所以我们在模拟操作时，如果现在的数 $<10$ 就可以 `break`。

综上，我们得到了以下做法：
+ 对于修改操作，在树状数组中执行 `add(l,1)` 和 `add(r+1,-1)`。
+ 对于查询操作，查询 $1$ 到 $x$ 的前缀和，即是 $x$ 的操作次数，对 $a_x$ 模拟每个操作，如果 $a_x<10$ 就直接 `break`。

时间复杂度 $\mathcal{O}(n+q\log n)$。
### 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<vector>
#include<queue>
#define lowbit(x) x&(-x)
using namespace std;
typedef long long ll;
const int MOD=1e9+7;
const int mod=998244353;
const int maxn=5e5+5;
const int maxm=3005;
int t[maxn],a[maxn],n,q;
void add(int x,int k){
    for(;x<=n;x+=lowbit(x)) t[x]+=k;
}
int query(int x){
    int ans=0;
    for(;x;x-=lowbit(x)) ans+=t[x];
    return ans;
}
void solve(){
    cin>>n>>q;
    for(int i=1;i<=n+1;i++) t[i]=0;
    for(int i=1;i<=n;i++) cin>>a[i];
    while(q--){
        int opt,l,r;
        cin>>opt;
        if(opt&1){
            cin>>l>>r;
            add(l,1);
            add(r+1,-1);
        }
        else
        {
            cin>>l;
            int k=query(l),v=a[l];
            for(int i=1;i<=k;i++){
                if(v<10) break;
                int p=0;
                while(v){
                    p+=(v%10);
                    v/=10;
                }
                v=p;
            }
            cout<<v<<'\n';
        }
    }
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：zhicheng (赞：3)

### 思路

因为是区间修改，单点查询，考虑线段树。但是因为每一个要改的元素都不知道要改多少，所以先考虑一个点一个点地改。但是我们发现如果 $a_i$ 是一位数，那么无论改多少次它都不会变。因此我们考虑增加一个 `tag`，表示此区间内的数是否都为一位数。如果修改到了这一个区间且 `tag` 被标记，那么就根本不用继续往下修改。查询就按最原始的查就行了。

### Code

注意上文中的 `tag` 在代码中是 `p` 数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[800010],p[800010];
void build(int l,int r,int rt){
	int mid;
	if(l==r){
		scanf("%d",&a[rt]);
		if(a[rt]/10==0){  //建树时就可以标记了
			p[rt]=1;
		}
		return;
	}
	mid=(l+r)>>1;
	build(l,mid,rt<<1);
	build(mid+1,r,rt<<1|1);
	p[rt]=p[rt<<1]&p[rt<<1|1];  //pushup
}
void modify(int x){  //单点修改
	int u=a[x],ans=0;
	while(u){
		ans+=u%10;
		u/=10;
	}
	a[x]=ans;
}
void update(int x,int y,int l,int r,int rt){
	int mid;
	if(x<=l&&y>=r&&p[rt]){  //标记过了就可以不改了
		return;
	}
	if(l==r){
		modify(rt);
		if(a[rt]/10==0){  //标记
			p[rt]=1;
		}
		return;
	}
	mid=(l+r)>>1;
	if(x<=mid){
		update(x,y,l,mid,rt<<1);
	}
	if(y>=mid+1){
		update(x,y,mid+1,r,rt<<1|1);
	}
	p[rt]=p[rt<<1]&p[rt<<1|1];
}
int query(int x,int l,int r,int rt){
	int mid;
	if(l==r){
		return a[rt];
	}
	mid=(l+r)>>1;
	if(x<=mid){
		return query(x,l,mid,rt<<1);
	}
	else{
		return query(x,mid+1,r,rt<<1|1);
	}
}
int main(){
	int t,n,q,op,x,y;
	scanf("%d",&t);
	while(t--){
		memset(a,0,sizeof(a));
		memset(p,0,sizeof(p));  //注意清空
		scanf("%d%d",&n,&q);
		build(1,n,1);
		while(q--){
			scanf("%d%d",&op,&x);
			if(op==1){
				scanf("%d",&y);
				update(x,y,1,n,1);
			}
			else{
				printf("%d\n",query(x,1,n,1));
			}
		}
	}
}
```

### 后话

[P4145](https://www.luogu.com.cn/problem/P4145) 和这道题很像，稍微改改就能过。

---

## 作者：loser_seele (赞：3)

简单题。

我们实际上可以暴力更新答案，注意到如果一个位置上的数 $ \leq 9 $ 那么更新实际上没用，于是维护一个 $ \geq 10 $ 的数的列表，每次只更新区间内列表的数即可。

看上去是暴力，但是因为 $ a_i \leq 10^9 $，于是设 $ f(x) $ 为 $ x $ 的数位和，则有 $ f(a_i) \leq 81,f(f(a_i)) \leq 18,f(f(f(a_i))) \leq 9 $，于是每个位置最多被更新 $ 3 $ 次，复杂度正确。

维护列表可以用 set 实现，时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
signed main()
{
int T;
cin>>T;
while(T--)
{
    int n,q;
    cin >> n >> q;
    set<int> S;
    for(int i=1;i<=n;i++) 
    cin >> a[i], S.insert(i);
    while (q --) 
    {
        int op;
        cin >> op;
        if (op == 2) 
        {
            int x;
            cin >> x;
            cout << a[x] << "\n";
        } 
        else 
        {
            int l,r;
            cin >> l >> r;
            auto it = S.lower_bound(l);
            vector<int> rm;
            while (it != S.end() and *it <= r) 
            {
                int pos = *it;
                int x = a[pos];
                int y = 0;
                while (x > 0) 
                y+=x%10,x/=10;
                a[pos] = y;
                if (y < 10) 
                rm.push_back(pos);
                it ++;
            }
            for (auto x:rm) 
            S.erase(x);
        }
    }
}
}
```


---

## 作者：5k_sync_closer (赞：2)

怎么全是线段树啊，来点 DSU。

维护 $f_i$ 表示 $i$ 后第一个 $\ge 10$ 的位置（需要操作的位置），初始 $f_i=i$。

区间修改 $[l,r]$ 时，初始 $i=\operatorname{find}(l)$，修改 $a_i$ 后，若 $a_i<10$，令 $f_i=i+1$。

然后令 $i=\operatorname{find}(i+1)$（跳到下一个需要操作的位置）。
```cpp
#include <cstdio>
int T, n, m, a[200050], f[200050];
int F(int x) { return x == f[x] ? x : f[x] = F(f[x]); }
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i), f[i] = i;
        f[n + 1] = n + 1;
        for (int i = 0, o, x, y; i < m; ++i)
        {
            scanf("%d%d", &o, &x);
            if (o & 1)
            {
                scanf("%d", &y);
                for (int j = F(x); j <= y; j = F(j + 1))
                {
                    o = a[j];
                    a[j] = 0;
                    while (o)
                        a[j] += o % 10, o /= 10;
                    if (a[j] < 10)
                        f[j] = j + 1;
                }
            }
            else
                printf("%d\n", a[x]);
        }
    }
    return 0;
}
```



---

## 作者：OldDriverTree (赞：1)

# 前言
我的一个学长在一次考试中出了这道题，~~于是我用 $10 \min$ 把这道题切了~~。

和这题思路类似的题：
1. [P4145](https://www.luogu.com.cn/problem/P4145)
2. [P8618](https://www.luogu.com.cn/problem/P8618)
3. [SP2713](https://www.luogu.com.cn/problem/SP2713)
4. [CF483D](https://www.luogu.com.cn/problem/CF438D)

# 思路
由于每次修改操作时每个数最多操作 $3$ 次后再操作就不会发生变化了。

所以我们考虑用一棵线段树维护区间最大值。

区间修改时，如果当前区间的最大值小于 $10$，那么后就操作后整个区间都不会发生变化，那么就直接 `return`（整个区间内的数都为个位数时，每个数操作后还是他本身，所以不会发生变化），搜到单点时，就把当前节点的值变成他的每个数位上的数字和。

那么每个单点一共最多就会进行 $3n$ 次操作。

# Code
```cpp
#include<bits/stdc++.h>
#define mid (l+r>>1)
#define ls rt<<1,l,mid
#define rs rt<<1|1,mid+1,r
#define push_up(rt) val[rt]=max(val[rt<<1],val[rt<<1|1])
using namespace std;
int val[900000];

int read() {
	int x=0; char ch=0;
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x;
}
int f(int x) 
{
	int y=0;
	while (x) {
		y+=x%10;
		x/=10;
	}
	return y;
}
void build(int rt,int l,int r) {
	if (l==r) val[rt]=read();
	else build(ls),build(rs),push_up(rt);
}
void modify(int rt,int l,int r,int L,int R) {
	if (val[rt]<10) return;
	if (l==r) return val[rt]=f(val[rt]),void();
	if (L<=mid) modify(ls,L,R);
	if (mid<R) modify(rs,L,R);
	push_up(rt);
}
int query(int rt,int l,int r,int pos) {
	if (l==r) return val[rt];
	if (pos<=mid) return query(ls,pos);
	else return query(rs,pos);
}
int main()
{
	int T=read();
	while (T--) 
	{
		int n=read(),m=read();
		build(1,1,n);
		while (m--) {
			int op=read(),x=read();
			if (op==1) modify(1,1,n,x,read());
			else printf("%d\n",query(1,1,n,x));
		}
	}
	return 0;
}
```

---

## 作者：arrow_king (赞：1)

~~没错我数据结构学傻了，看见区间操作就线段树~~

## 思路

在线操作，思路类似 [上帝造题的七分钟2](https://www.luogu.com.cn/problem/P4145)。

考虑，一个 $10^9$ 内的正整数操作的次数是很有限的，最大的数，比如说 $999999999$，操作数量也只是 $3$ 而已。

所以就可以不追求单次操作的复杂度，转而去限制均摊复杂度。

开一颗线段树，其中维护 $4$ 个值：

- $l$：区间左端点；
- $r$：区间右端点；
- $num$：若是叶子节点，则表示对应点的值；否则为 $0$；
- $need$：是否需要继续递归操作的标记。

`push_up` 函数也很好理解，$l,r,num$ 不用管，$need$ 的话，或一下就可以了。（两个子节点有一个需要更新这个节点就需要更新）

每次修改时，如果当前节点 $need$ 为 $0$，直接 `return`；若不是，递归左右两个节点修改。如果到了叶子节点，直接暴力修改就可以了，如果修改值没变化，$need$ 赋值为 $0$。最后一路 `push_up` 回去。

`query` 就直接单点查询可以了。

时间复杂度 $\mathcal O(n\log n)$ ~~以及计算数位和和每个数递归 $3$ 次的“常数”~~。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define lc(x) x<<1
#define rc(x) (x<<1)|1
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
struct node {
	int l,r;
	int num,need;
};
node tr[200005*4];
int t,n,q;
int a[200005];
il int disum(int x) {
	int ans=0;
	while(x) {
		ans+=x%10;
		x/=10;
	}
	return ans;
}
il void push_up(int now) {
	tr[now].need=tr[lc(now)].need||tr[rc(now)].need;
}
il void build(int now,int l,int r) {
	tr[now].l=l,tr[now].r=r;
	if(l==r) {
		tr[now].num=a[l];
		if(a[l]!=disum(a[l])) tr[now].need=1;
		return;
	}
	int mid=(l+r)>>1;
	build(lc(now),l,mid);
	build(rc(now),mid+1,r);
	push_up(now);
}
il void update(int nl,int nr,int l,int r,int now) {
	if(l==r) {
		int x=disum(tr[now].num),y=disum(x);
		tr[now].num=x;
		if(x==y) tr[now].need=0;
		return;
	}
	int mid=(l+r)>>1;
	if(nl<=mid&&tr[lc(now)].need==1) update(nl,nr,l,mid,lc(now));
	if(mid<nr&&tr[rc(now)].need==1) update(nl,nr,mid+1,r,rc(now));
	push_up(now);
}
il int query(int p,int l,int r,int now) {
	if(l==r) return tr[now].num;
	int mid=(l+r)>>1;
	if(p<=mid) return query(p,l,mid,lc(now));
	else return query(p,mid+1,r,rc(now));
}
int main() {
	t=read();
	while(t--) {
		n=read(),q=read();
		for(int i=1;i<=n;i++) a[i]=read();
		build(1,1,n);
		int opt,l,r;
		for(int i=1;i<=q;i++) {
			opt=read(),l=read();
			if(opt==1) {
				r=read();
				update(l,r,1,n,1);
			}
			else printf("%d\n",query(l,1,n,1));
		}
	}
	return 0;
}
```

---

## 作者：Keroshi (赞：0)

# 解题思路
首先，题目需要两个操作，区间修改和单点查询。     
不难想到使用线段树来维护，但是区间修改是将每个数改成其数位之和，    
用 lazytag 很难实现，所以只能暴力修改。    
但是题目中的操作有一个奇妙的性质，就是每个数经过三次操作后就会小于十，    
然后就不会发生改变。   
通过这一性质，可以用线段树来维护区间最大值，当暴力修改时，   
检查当前节点的最大值，如果最大值小于十，那么就停止继续操作。  
将线段树板子改一改就行了。  
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T;
int n,q,a[N];
int p(int x){ // 数位之和
    int res=0;
    for(;x;x/=10) res += x % 10;
    return res;
}
struct SegmentTee{ // 线段树板子
    int f[N*4],le[N*4],ri[N*4],tag[N*4];
    void pushup(int u) { // 维护区间最大值
        f[u] = max(f[u << 1] , f[u << 1 | 1]);
    }
    void build(int u,int l,int r){ // 建树
        if(l == r){
            f[u] = a[l];
            le[u] = l; ri[u] = r; tag[u] = 0;
            return;
        }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        le[u] = l; ri[u] = r; tag[u] = 0;
        pushup(u);
    }
    void modify(int u,int l,int r) { // 暴力区间修改
        if(f[u] <= 9) return; // 小于十就不用修改了
        if(le[u] == ri[u]){ // 到叶子节点了
            f[u] = p(f[u]);  // 修改
            return;
        }
        int mid = le[u] + ri[u] >> 1;
        if(l <= mid) modify(u << 1, l, r);
        if(mid < r) modify(u << 1 | 1, l, r);
        pushup(u);
    }
    int query(int u,int x) { // 单点查询
        if(le[u] == ri[u]) return f[u];
        int mid = le[u] + ri[u] >> 1;
        if(x <= mid) return query(u << 1, x);
        else return query(u << 1 | 1, x);
    }
}t;
void solve(){ // 多测好习惯，开个函数
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    t.build(1,1,n);
    for(int i=1;i<=q;i++) {
        int opt;
        cin >> opt;
        if(opt == 1){
            int l,r;
            cin >> l >> r;
            t.modify(1,l,r);
        }
        if(opt == 2){
            int x;
            cin >> x;
            cout << t.query(1,x) << endl;
        }
    }
}
int main(){
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：yeshubo_qwq (赞：0)

## Solution1

[伪·双倍经验](https://www.luogu.com.cn/problem/P4145)

跟 P4145 类似，容易发现，一个数至多进行 $3$ 次更新就不会变了（$\le 9$），使用线段树维护区间最大值，区间和即可。

修改可以直接暴力修改，当区间最大值 $\le 9$ 时直接中止。

直接把 P4145 代码改改就过了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct tree{
    int l,r,x,mx;
};
tree tr[800005];
int n,m,i,a[200005],b,x,y,z;
void build(int pos,int l,int r){
    tr[pos].l=l;tr[pos].r=r;
    if (l==r){
        tr[pos].mx=tr[pos].x=a[r];
        return;
    }
    int mid=(l+r)>>1;
    build(pos<<1,l,mid);
    build(pos<<1|1,mid+1,r);
    tr[pos].x=tr[pos<<1].x+tr[pos<<1|1].x;
    tr[pos].mx=max(tr[pos<<1].mx,tr[pos<<1|1].mx);
}
int change(int x){
	int res=0;
	while (x>0) res+=(x%10),x/=10;
	return res;
}
void inc(int pos,int l,int r){
	if (tr[pos].mx<=9) return ;
	if (tr[pos].l==tr[pos].r){
		tr[pos].mx=tr[pos].x=change(tr[pos].x);
		return ;
	}
    int mid=(tr[pos].l+tr[pos].r)>>1;
    if (l<=mid) inc(pos<<1,l,r);
    if (r>mid)  inc(pos<<1|1,l,r);
    tr[pos].x=tr[pos<<1].x+tr[pos<<1|1].x;
    tr[pos].mx=max(tr[pos<<1].mx,tr[pos<<1|1].mx);
}
int inq(int pos,int l,int r){
    if (l<=tr[pos].l&&tr[pos].r<=r) return tr[pos].x;
    int mid=(tr[pos].l+tr[pos].r)>>1;
    int ans=0;
    if (l<=mid) ans+=inq(pos<<1,l,r);
    if (r>mid)  ans+=inq(pos<<1|1,l,r);
    return ans;
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while (T--){
    	cin>>n>>m;
	    for (i=1;i<=n;i++) cin>>a[i];
	    build(1,1,n);
	    for (i=1;i<=m;i++){
	        cin>>b>>x;
	        if (b==1) cin>>y,inc(1,x,y);
	        else cout<<inq(1,x,x)<<'\n';
	    }
	}
    return 0;
}
```
Solution2：

注意到只需实现单点求和，线段树有点大材小用。

用树状数组维护每个位置进行了几次更新，至多做 $3$ 次，每次询问暴力求值即可。

没有代码。

Solution3：

似乎用并查集也可以搞，有空再写。

---

## 作者：LincW (赞：0)

本文将 $x$ 的数位和记为 $\mathrm{f}(x)$。

线段树。

在每个节点上维护操作 $1$ 进行的次数（带懒标记）。

在叶子节点上维护值（即 $a_x$）。

每次 `push_down` 到叶子节点时，进行 $\mathrm{lazy\_tag}$ 次 $a_x \gets \mathrm{f}(a_x)$。

这样仍然会 TLE。

注意到 $\forall x<10,x=\mathrm{f}(x)$，所以进行以下特判：

- 如果叶子节点进行 $\mathrm{lazy\_tag}$ 次 $a_x \gets \mathrm{f}(a_x)$ 时 $a_x<10$，停止该操作。

- 如果叶子节点存的值小于 $10$，那么该叶子节点 `push_down` 时什么都不做。

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

typedef long long ll;

const ll N=200000;

struct node
{
	ll val;
	ll lazy_tag;
	ll l,r;
};

int digit_sum(ll x,ll bx)
{
	int res=0;
	while(x>0)
	{
		res+=(x%bx);
		x/=bx;
	}
	return res;
}

class Tree
{
	private:
		node data[4*N+5];
		void _push_down(int nod)
		{
			if(data[nod].l==data[nod].r)
			{
				for(int i=0;i<data[nod].lazy_tag && data[nod].val>=10;++i)
				{
					data[nod].val=digit_sum(data[nod].val,10);
				}
				data[nod].lazy_tag=0;
				return;
			}
			if(data[nod].lazy_tag!=0)
			{
				data[nod*2+1].lazy_tag+=data[nod].lazy_tag;
				data[nod*2+2].lazy_tag+=data[nod].lazy_tag;
				data[nod].lazy_tag=0;
			}
		}
		void _edit(ll l,ll r,ll nod)
		{
			_push_down(nod);
			if(data[nod].l==l && data[nod].r==r)
			{
			    data[nod].lazy_tag+=1;
				return;
			}
			if(data[nod*2+1].r>=l)
			{
				if(data[nod*2+1].r>=r)
				{
					_edit(l,r,nod*2+1);
				}
				else
				{
					_edit(l,data[nod*2+1].r,nod*2+1);
					_edit(data[nod*2+1].r+1,r,nod*2+2);
				}
			}
			else
			{
				_edit(l,r,nod*2+2);
			}
			return;
		}
		ll _query(ll idx,ll nod)
		{
			_push_down(nod);
			if(data[nod].l==idx && data[nod].r==idx)
			{
				return data[nod].val;
			}
			ll sum=0;
			if(data[nod*2+1].r>=idx)
			{
				sum=_query(idx,nod*2+1);
			}
			else
			{
				sum=_query(idx,nod*2+2);
			}
			return sum;
		}
		void _construct(ll arr[],ll nod)
		{
			if(data[nod].l==data[nod].r)
			{
				data[nod].val=arr[data[nod].l];
				return;
			}
			
			ll mid=(data[nod].l+data[nod].r)/2;
			
			data[nod*2+1].l=data[nod].l;
			data[nod*2+1].r=mid;
			
			data[nod*2+2].l=mid+1;
			data[nod*2+2].r=data[nod].r;
			
			_construct(arr,nod*2+1);	
			_construct(arr,nod*2+2);
		}
	public:
		void construct(ll arr[],ll num)
		{
			for(ll i=0;i<4*num+4;++i)
			{
				data[i].val=0;
				data[i].l=-1;
				data[i].r=-1;
				data[i].lazy_tag=0;
			}
			data[0].l=0;
			data[0].r=num-1;
			_construct(arr,0);
		}
		
		void edit(ll l,ll r)
		{
			_edit(l,r,0); 
		} 
		
		ll query(ll idx)
		{
			return _query(idx,0);
		}
};

ll n,m;
ll a[N+5];

Tree tree;

ll read()
{
	ll res=0;
	int flag=1;
	char c=0;
	while((c>'9' || c<'0') && c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		flag=-1;
		c=getchar();
	}
	while(c<='9' && c>='0')
	{
		res*=10;
		res+=(ll)(c-'0');
		c=getchar();
	}
	return res*flag;
}

int main()
{
	int t;
	t=read();
	while(t--)
	{
		n=read();
		m=read();
		
		for(ll i=0;i<n;++i)
		{
			a[i]=read();
		}
		
		tree.construct(a,n);
		
		while(m--)
		{
			ll typ,x,y;
			typ=read();
			x=read();
			
			if(typ==1)
			{
				y=read();
				tree.edit(x-1,y-1);
			}
			else
			{
				printf("%d\n",(int)tree.query(x-1));
			}
		}
	}
}
```


---

## 作者：ttq012 (赞：0)

~~这不是GSS4吗？~~ ~~是不是就我一个人写了线段树？~~

容易发现，一个 $10^9$ 的数，执行 $3$ 次操作之后，这个数就会 $<10$。

对于一个 $<10$ 的数，不管执行多少次操作，这个数都不会变。

那么可以维护一个“区间的数是否都 $<10$” 的信息，修改的时候暴力修改，如果发现区间所有的数都 $<10$，那么不维护即可。

跑的有点慢。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int a[N];
struct Node
{
  int l,r,one,sum;
  Node(){
    l=r=one=sum=0;
  }
  void init(int p){
    l=r=p;
    sum=a[p];
    one=0;
  }
}z[N<<2];
int gcc(int x){
  int cnt=0;
  while(x){
    cnt+=x%10;
    x/=10;
  }return cnt;
}
Node operator+(const Node&lhs, const Node&rhs){
  Node res;
  res.l=lhs.l;
  res.r=rhs.r;
  res.sum=lhs.sum+rhs.sum;
  if(lhs.one&&rhs.one)
    res.one=1;
  else res.one=0;
  return res;
}
void build(int l, int r,int rt){
  if(l==r)z[rt].init(l);
  else{
    int mid=l+r>>1;
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    z[rt]=z[rt<<1]+z[rt<<1|1];
  }
}
void modify(int l,int r,int rt,int nowl, int nowr){
  if(z[rt].one)return;
  if(l==r){
    z[rt].sum=gcc(z[rt].sum);
    if(z[rt].sum<10)z[rt].one=1;
    return;
  }
  int mid=l+r>>1;
  if(nowl<=mid)modify(l,mid,rt<<1,nowl,nowr);
  if(mid<nowr)modify(mid+1,r,rt<<1|1,nowl,nowr);
  z[rt]=z[rt<<1]+z[rt<<1|1];
}
int query(int l,int r,int rt,int p){
  if(l==r)return z[rt].sum;
  int mid=l+r>>1;
  if(p<=mid)return query(l,mid,rt<<1,p);
  else return query(mid+1,r,rt<<1|1,p);
}
signed main(){
  int T;
  cin>>T;
  while(T--){
    int n,q;
    cin>>n>>q;
    for(int i=0;i<=n*4+10;i++)z[i]=Node();
    for(int i=1;i<=n;i++)cin>>a[i];
    build(1,n,1);
    while(q--){
      int o;
      cin>>o;
      if(o==1){
        int l,r;
        cin>>l>>r;
        modify(1,n,1,l,r);
      }
      else{
        int p;
        cin>>p;
        cout<<query(1,n,1,p)<<'\n';
      }
    }
  }
  return 0;
}
```



---

