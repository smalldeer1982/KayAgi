# [ABC351F] Double Sum

## 题目描述

给定一个整数序列 $A = (A_1, A_2, \dots, A_N)$。  
请计算下式的值：

$$
\sum_{i=1}^N \sum_{j=i+1}^N \max(A_j - A_i, 0)
$$

在给定的约束条件下，保证答案小于 $2^{63}$。

## 说明/提示

## 约束

- $2 \leq N \leq 4 \times 10^5$
- $0 \leq A_i \leq 10^8$
- 输入的所有值均为整数

## 样例解释 1

当 $(i, j) = (1, 2)$ 时，$\max(A_j - A_i, 0) = \max(3, 0) = 3$。  
当 $(i, j) = (1, 3)$ 时，$\max(A_j - A_i, 0) = \max(1, 0) = 1$。  
当 $(i, j) = (2, 3)$ 时，$\max(A_j - A_i, 0) = \max(-2, 0) = 0$。  
将这些值相加，$3 + 1 + 0 = 4$，即为答案。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 5 3```

### 输出

```
4```

## 样例 #2

### 输入

```
10
5 9 3 0 4 8 7 5 4 0```

### 输出

```
58```

# 题解

## 作者：xxgirlxx (赞：86)

## 题目大意

还用说吗？就是求下面这个式子的值啊！

$$\sum_{i=1}^{N}\sum_{j=i+1}^{N}\max(A_j-A_i,0)$$

## 题目思路

首先，把式子转化一下：因为 $0$ 可以转化为 $A_j-A_j$ 所以式子转化为：

$$\sum_{i=1}^{N}\sum_{j=i+1}^{N}\max(A_j-A_i,A_j-A_j)$$

然后提一个 $A_j$ 出来，就是：

$$\sum_{i=1}^{N}\sum_{j=i+1}^{N}A_j+\max(-A_i,-A_j)$$

再将负数转化为正数，也就是将 $\max$ 内的 $-A_i$ 和 $-A_j$ 变为 $A_i$ 和 $A_j$。因为从负数化成了正数，所以前面的符号也要变，不是加了，是减。因为负数的时候取的是 $\max$，也就是去掉负号后更小的那个数。所以将负号去掉后就不是取 $\max$ 了，而是取 $\min$。式子为：

$$\sum_{i=1}^{N}\sum_{j=i+1}^{N}A_j-\min(A_i,A_j)$$

最后我们再来考虑计算的问题。

先考虑 $A_j$。因为第 $j$ 个数，会跟前面的 $j-1$ 个数都匹配一遍，所以第 $j$ 个数会贡献出 $A_j \times (j-1)$。

再考虑 $-\min(A_i,A_j)$。因为每两个数之间一定会匹配一次，所以第 $i$ 小的数会贡献出 $-A_i \times (n-i)$。

所以我们只需要先计算一遍所有 $A_j$ 的贡献，再排一遍序，在计算一下所有第 $i$ 小的贡献就可以通过这道题啦！

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,a[400010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],ans+=a[i]*(i-1);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)ans-=a[i]*(n-i);
	cout<<ans;
	return 0;
}
```

---

## 作者：Ace_FutureDream (赞：7)

为什么大家都要用树状数组、线段树，甚至于平衡树？这里为一些不想写数据结构的人提供一种十分简便的做法，代码也就十几行。

首先分析题意，让你求：

$\displaystyle\sum_{i=1}^N\sum_{j=i+1}^N\max(A_j-A_i,\ 0) $

一个很明显的做法，离散化之后用枚举 $i$，然后利用树状数组，求出每一个 $j<i$，且 $A_j<A_i$ 的和，即可求得答案。
其实这么做的本质是不考虑 $A_j-A_i$ 为负的情况，但我们是否可以换一种思路呢？

我们稍微思考即可发现另一种思路：先不考虑 $\max$，先把

$\displaystyle\sum_{i=1}^N\sum_{j=i+1}^NA_j-A_i$

求出来，之后再加上 $A_j-A_i$ 为负数的情况，因为产生负数是无序的，所以可以排序做，然后就做完了。

实在不理解的可以举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/pvgwievg.png)

将 $F_1$ 设为 $2-5$ ，$F_2$ 设为 $5-3$，$F_3$ 设为 $2-3$ 。

那么我们不考虑 $\max$ 的 $ans=F_1+F_2+F_3$，

然后我们排序后的数列为 $2$，$3$，$5$，

此时 $F_1'=5-2$，$F_2'=5-3$，$F_3'=3-2$，

我们可以发现 $F_1'=|F_1|$，$F_2'=|F_2|$，$F_3'=|F_3|$。

那么，若 $F_i<0$，则 $F_i'+F_i=0$，恰好抵消。

若 $F_i\ge 0$，则 $F_i'+F_i=2F_i$。

所以，$ans= \dfrac{\sum_{i=1}^NF_i'+F_i}{2}$。

而 $F$ 可以在输入时预处理出来，$F'$ 可以排序后处理出来。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[400010],s,ans,n;
signed main(){
   	cin>>n;
   	for(int i=1;i<=n;i++)cin>>a[i],ans+=(i-1)*a[i]-s,s+=a[i];
	sort(a+1,a+n+1);
	for(int i=n;i>=2;i--)s-=a[i],ans+=(i-1)*a[i]-s;
	cout<<ans/2<<'\n';
   	return 0;
}
```
## code 清晰版：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[400010];
signed main(){
   	int n;
   	cin>>n;
   	int s=0,ans=0;
   	for(int i=1;i<=n;i++){
   		cin>>a[i];
   		ans+=(i-1)*a[i]-s;
   		s+=a[i];
	}
	sort(a+1,a+n+1);
	for(int i=n;i>=2;i--){
		s-=a[i];
		ans+=(i-1)*a[i]-s;
	}
	cout<<ans/2<<'\n';
   	return 0;
}
```

---

## 作者：Day_Tao (赞：6)

~~讲个笑话：F < D（）~~

### 题目大意

给定整数列 A，求 $\sum \limits _ {i=1}^N\sum \limits _ {j=i+1}^N \max(A_j-A_i,0)$。数据范围 $2\le N \le 4\times 10^5$，$0\le A_i\le 10^8$。

### Sol

考虑到 $\forall i<j$，只有 $A_i\le A_j$ 才会产生贡献。所以可以维护对于每一个 $A_i$ 能产生贡献的 $A_j$。这时可以相当排序，并记录后缀和。但是排完序之后怎么处理$A_i\le A_j$，但是 $j<i$ 的情况呢？这时可以考虑开两个后缀和，$sum1$ 记录后面的总贡献，$sum2$ 记录后面能产生贡献的数的个数。记此时的数为 $A_i$，那么这部分的贡献就是 $sum1-sum2\times A_i$。

再让我们考虑如何维护后缀和。由于一次次更新会是 $O(n^2)$ 的复杂度，所以可以用树状数组维护后缀和。~~不会用树状数组的请移步 [P3374 【模板】树状数组 1
](https://www.luogu.com.cn/problem/P3374?contestId=160746)。~~

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)
#define pqg priority_queue<int, vector<int>, greater<int>>
#define pql priority_queue<int, vector<int>, less<int>>
#define ls root << 1
#define rs root << 1 | 1
#define scnaf scanf
#define int long long
#define rt register int
const int MAX = 4e5 + 5;
const int INF = 0x7fffffff;
const int mod = 998244353;
int n, j, p[MAX], cnt[MAX];
int tree[MAX], ans;
struct Day_Tao
{
    int w, id;
} a[MAX];
inline int lowbit(int x)
{
    return x & -x;
}
inline void build()
{
    for (int i = 1; i <= n; i++) // 一次建两个树状数组
    {
        j = i + lowbit(i);
        tree[i] += a[i].w, ++cnt[i];
        if (j <= n)
            tree[j] += tree[i], cnt[j] += cnt[i];
    }
}
inline int query(int x, int y)
{
    int sum1 = 0, sum2 = 0; // sum1 代表后缀和，sum2 代表后缀元素个数
    for (; y; y -= lowbit(y))
        sum1 += tree[y], sum2 += cnt[y];
    for (int i = x; i; i -= lowbit(i))
        sum1 -= tree[i], sum2 -= cnt[i];
    return sum1 - sum2 * a[x].w;
}
inline void update(int x, int y)
{
    for (; x <= n; x += lowbit(x))
        tree[x] -= y, cnt[x]--; // 减去对后面没有贡献的数
}
inline bool cmp(Day_Tao x, Day_Tao y)
{
    return x.w < y.w;
}
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i].w), a[i].id = i;
    sort(a + 1, a + n + 1, cmp);
    build();
    for (int i = 1; i <= n; i++)
        p[a[i].id] = i; // 记录对应 a 的位置
    for (int i = 1; i <= n; i++)
    {
        ans += query(p[i], n);
        update(p[i], a[p[i]].w);
    }
    printf("%lld\n", ans);
    system("pause");
    return 0;
}
```

---
### END

---

## 作者：__ryp__ (赞：6)

题意明显：对每个 $i$，求 $\sum\limits_{j=i+1}^n \max (A_j - A_i, 0)$。求每个 $i$ 的答案总和。

实际上就是找使得 $A_j \gt A_i$ 且 $j \gt i$ 的所有 $A_j$ 的和。我们从后往前加入 $A_i$，那么就消掉了第二维。于是只需要统计当前所有大于 $A_i$ 的数的和以及数量即可。

可以用离散化 + 树状数组，也可以平衡树。我写的后者。

[submission](https://atcoder.jp/contests/abc351/submissions/52873980)

upd 2024.05.02 [加了一个树状数组写法](https://atcoder.jp/contests/abc351/submissions/53023731)

---

## 作者：_determination_ (赞：4)

看到式子：

$$ \displaystyle\ \sum_{i=1}^N\ \sum_{j=i+1}^N\ \max(A_j\ -\ A_i,\ 0) $$

考虑化简。

$$ \left ( \displaystyle\ \sum_{i=1}^N\ \sum_{j=i+1}^N\ A_j\ -\ A_i  \right ) -\ \left ( \displaystyle\ \sum_{i=1}^N\ \sum_{j=i+1,a_j<a_i}^N\ A_j\ -\ A_i \right )   $$

发现左边的东西随便算，右面的东西是一个类似逆序对的东西，可以类似逆序对进行处理。

这坨式子：

$$ \displaystyle\ \sum_{i=1}^N\ \sum_{j=i+1,a_j<a_i}^N\ A_j\ -\ A_i $$

可以开两个树状数组，一个存权值，一个存数量。倒序扫描，每次查询树状数组中比 $a_i$ 小的部分并更新即可。

小细节：
1. 中间过程会爆 `long long`，记得开 `int128`。
1. 记得离散化。

具体实现看代码。

```cpp
#include<bits/stdc++.h>
#define int __int128
#define inf (int)1e18
using namespace std;
int a[400010];
int n,ans;
int t1[400010],t2[400010];
int b[400010],c[400010];
int lowbit(int x){return x&(-x);}
void upd(int t[],int x,int v)
{
	while(x<=400000)
	{
		t[x]+=v;
		x+=lowbit(x);
	}
}
int calc(int t[],int x)
{
	int ans=0;
	while(x)
	{
		ans+=t[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	long long read;
	cin >> read;
	n=read;
	for ( int i = 1 ; i <= n ; i++ )
	{
		cin >> read;
		read++;
		ans+=read*(i-1);
		ans-=read*(n-i);
		a[i]=read;
	}
//	read=ans;
//	cout << read << endl;
	for ( int i = 1 ; i <= n ; i++ )
	{
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	int m=unique(b+1,b+1+n)-b-1;
	for ( int i = n ; i >= 1 ; i-- )
	{
		c[i]=lower_bound(b+1,b+1+m,a[i])-b;
		ans+=calc(t2,c[i])*a[i];
		ans-=calc(t1,c[i]);
		upd(t2,c[i],1);
		upd(t1,c[i],a[i]);
	}
	read=ans;
	cout << read;
	return 0;
}
```

---

## 作者：2huk (赞：3)

- 给定一个长度为 $n$ 的序列 $a$，求 $\sum_{1 \le i < j \le n} \max(a_j - a_i, 0)$。
- $n \le 4 \times 10^5$，$0 \le a_i \le 10^8$。

枚举 $j$。我们需要计算 $\sum_{1 \le i < j} \max(a_j - a_i, 0)$。

可以发现只有在 $a_j \ge a_i$ 时，后面那坨才会有贡献。所以我们可以将式子改为 $\sum_{1 \le i < j,a_j \ge a_i} (a_j - a_i)$。

这个式子的计算是极易的。令 $t = \sum_{1 \le i < j,a_j \ge a_i} 1$，那么我们可以将原式中的 $a_j$ 提出来，即 $t \times a_j - \sum_{1 \le i < j,a_j \ge a_i} a_i$。

所以我们需要计算的就是 $\sum_{1 \le i < j,a_j \ge a_i} 1$ 和 $\sum_{1 \le i < j,a_j \ge a_i} a_i$。用树状数组实现即可。

注意到 $a_i$ 可能很大，所以解决方法可以是离散化或用 map。

---

## 作者：rhn7 (赞：2)

史前最简单 F，可惜这场比赛我有事没打。

把 $a$ 数组排序，从前往后枚举 $a_i$，设 $id_i$ 为 $a_i$ 在原序列的编号，这样前面枚举过的数一定 $\le a_i$，只用看 $id$ 就行了。设 $k$ 为 $id_j<id_i \land j<i$ 的 $j$ 个数，$s$ 为满足上面条件的 $a_j$ 之和，对于所有满足上面条件的 $j$，都会产生 $a_i-a_j$ 的贡献，总贡献就是 $ka_i-s$，$k$ 和 $s$ 用树状数组维护。

其实不排序也行，方法差不多，只不过数值会很大，要用动态开点线段树维护，比较难写。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=4e5+5;
ll n,c[N][2],ans;
struct T{ll x,id;}a[N];
void add(ll x,ll p,ll k){for(;x<=n;x+=x&-x) c[x][p]+=k;}
ll sum(ll x,ll p){ll res=0;for(;x;x-=x&-x) res+=c[x][p];return res;}
int main(){
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i].x),a[i].id=i;
	sort(a+1,a+n+1,[](T a,T b){return a.x<b.x;});
	for(ll i=1;i<=n;i++){
		ans+=a[i].x*sum(a[i].id,0)-sum(a[i].id,1);
		add(a[i].id,0,1);add(a[i].id,1,a[i].x);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：whx2009 (赞：1)

## 本题思路：
这道题其实并不复杂，我们可以直接按照权值去建一棵线段树，再扫到当前这一个数的时候我们可以先把他的值从主席树中删除，把比他大的数字和拎出来减去总共这样的数的个数与当前值的权值即可。

在这里的线段数需要动态开点，不然空间复杂度就会爆掉。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(p) tr[p].ls
#define rs(p) tr[p].rs
#define mid (tr[p].l+tr[p].r)/2
using namespace std;
int cnt;
struct f{
	int ls,rs,l,r,sum,siz;
}tr[4000001*4];
int a[400001];
void wei(int p){
	tr[p].sum=tr[ls(p)].sum+tr[rs(p)].sum;
	tr[p].siz=tr[ls(p)].siz+tr[rs(p)].siz;
}
void gai(int p,int l,int k,int f){
	if(tr[p].l==tr[p].r){
		if(f)tr[p].siz++;
		else tr[p].siz--;
		tr[p].sum+=k;return;
	}
	if(!ls(p)){tr[++cnt].l=tr[p].l,tr[cnt].r=mid,ls(p)=cnt;}
	if(!rs(p)){rs(p)=++cnt,tr[cnt].l=mid+1,tr[cnt].r=tr[p].r;}
	if(l<=mid) gai(ls(p),l,k,f);
	else gai(rs(p),l,k,f);
	wei(p);
}
int chasi(int p,int l){
	if(tr[p].l>=l) return tr[p].siz;
	int ret=0;
	if(l<=mid) ret+=chasi(ls(p),l)+chasi(rs(p),l);
	if(l>mid) ret+=chasi(rs(p),l);
	return ret;
}
int chasu(int p,int l){
	if(!p) return 0;
	if(tr[p].l>=l) return tr[p].sum;
	int ret=0;
	if(l<=mid) ret+=chasu(ls(p),l)+chasu(rs(p),l);
	if(l>mid) ret+=chasu(rs(p),l);
	return ret;
}
signed main()
{
	int n,ans=0;
	cin>>n;
	tr[++cnt].l=0,tr[cnt].r=100000000;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		gai(1,a[i],a[i],1);
	}
	for(int i=1;i<=n;i++){
		gai(1,a[i],-a[i],0);
		int sum1=chasu(1,a[i]),siz1=chasi(1,a[i]);
		ans+=sum1-siz1*a[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：HasNoName (赞：1)

### 题目大意

$N$ 个数，统计每一对 $i$ 和 $j$ 如果 $j>i$ 且 $a_j>a_i$ 则答案加上 $a_j-a_i$，问答案是多少。

### 思路

对于每一个 $a_i$ 答案相当于加上了 $a_i$ 前面比 $a_i$ 小的数的个数乘 $a_i$，并减去 $a_i$ 后面比 $a_i$ 大的数的个数乘 $a_i$。

考虑使用树状数组。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
unordered_map<ll,int>d;
const int N=400005;
ll a[N],c[N],n,b[N];
int lowbit(int x)//树状数组
{
    return x&(-x);
}
void add(int k)
{
    if(k>n)return;
    c[k]++;
    add(k+lowbit(k));
}
int get(int k)
{
    if(k==0)return 0;
    return c[k]+get(k-lowbit(k));
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        b[i]=a[i];
    }
    sort(b+1,b+n+1);//离散化
    int k=0;
    b[0]=-1;
    for(int i=1;i<=n;i++)
    {
        if(b[i]!=b[i-1])d[b[i]]=++k;
    }
    __int128 ans=0;//可能会超过 long long
    for(int i=n;i>=1;i--)//倒序得到后面比一个数大的数的个数
    {
        add(d[a[i]]);
        ans-=(get(n)-get(d[a[i]]))*a[i];//后面比一个数大的数的个数乘这个数
    }
    memset(c,0,sizeof(c));//清空数组
    for(int i=1;i<=n;i++)
    {
        add(d[a[i]]);
        ans+=get(d[a[i]]-1)*a[i];
    }
    ll ans_=ans;
    cout<<ans_<<'\n';
    return 0;
}

```

---

## 作者：UniGravity (赞：1)

感觉比 E 简单。

看到 $\max(A_j-A_i,0)$，可以想到将其在**树状数组**上考虑。

$i$ 从 $N$ 到 $1$ 枚举，按顺序往里面加即可。

对于每一次查询，只需要知道大于 $A_i$ 的数**和及数量**。这可以在**权值树状数组上查询区间**解决。

小细节是，要对 $A$ 进行**离散化**。

```cpp
#include <bits/stdc++.h>
#define int long long
#define il inline
#define fr il friend
#define reg register
#define rnt reg int
#define forto(i, a, b) for (rnt i = (a); i <= (b); ++i)
using namespace std;
il int read() {
    rnt x = 0, f = 1; reg char c = getchar();
    while (c < '0' || '9' < c) {if (c == '-') f = -1; c = getchar();}
    while ('0' <= c && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
    return x * f;
}

int n, a[400005], old[400005], rk[400005], c[400005], c2[400005];

il int lowbit(rnt x) {return x & -x;}
il void update(rnt p, rnt k) {
    for (rnt i = p; i <= n; i += lowbit(i)) c[i] += k;
}
il int query(rnt p) {
    rnt ans = 0;
    for (rnt i = p; i > 0; i -= lowbit(i)) ans += c[i];
    return ans;
}
il void update2(rnt p, rnt k) {
    for (rnt i = p; i <= n; i += lowbit(i)) c2[i] += k;
}
il int query2(rnt p) {
    rnt ans = 0;
    for (rnt i = p; i > 0; i -= lowbit(i)) ans += c2[i];
    return ans;
}

signed main() {
    n = read();
    forto(i, 1, n) old[i] = a[i] = read();
    sort(old + 1, old + 1 + n);
    rnt len = unique(old + 1, old + n + 1) - old - 1;
    forto(i, 1, n) {
        rk[i] = lower_bound(old + 1, old + len + 1, a[i]) - old;
        //printf("%lld ", rk[i]);
    }
    //printf("\n");
    int ans = 0, sum = 0;
    for (rnt i = n; i >= 1; i--) {
        ans += (query(n) - query(rk[i])) - (query2(n) - query2(rk[i])) * a[i];
        update(rk[i], a[i]); update2(rk[i], 1);
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：Liyunze123 (赞：1)

~~第一次场切F，写个题解庆祝一下~~
# 1.题目大意
对于所有的 $1 \le i < j \le n$，求 $\max(a_j-a_i,0)$ 之和。
# 2.解题思路
如果求 $a_j-a_i$，很容易做出来。容易发现求的比正确答案少。只要补上少的即可。可以在归并排序时把少的补出来。

归并排序时，如果发现逆序对 $(i,j)$，把答案加上 $f_m-f_{i-1}-(m-i+1) \times a_j$，$m$ 就是归并排序时的 $mid$，$f_i=  a_l+a_{l+1}+……+a_i$。

证明：对于 $(i,j)$，对于 $a_j$，$a_i$ 到 $a_m$ 都应该是 $0$，但现在是负的，就要加上 $a_i-a_j+a_{i+1}-a_j+……+a_m-a_j$，合并为 $a_i+a_{i+1}+……+a_m-(m-i+1) \times a_j$，运用前缀和就等于 $f_m - f_{i-1} - (m-i+1) \times a_j$。
# 3.代码展示
```
#include<bits/stdc++.h>
using namespace std;
int n;
long long s,ans,f[400010],a[400010],b[400010];
void S(int l,int r){
	if(l>=r){f[l]=a[l];return;}
	int m=(l+r)/2,i=l,j=m+1,t=0;
	long long s=0;
	S(l,m),S(m+1,r);
	while(i<=m&&j<=r)
		if(a[i]<=a[j])b[++t]=a[i++];
		else ans+=f[m]-((i!=l)?f[i-1]:0)-(m-i+1)*a[j],b[++t]=a[j++];
	while(i<=m)b[++t]=a[i++];
	while(j<=r)b[++t]=a[j++];
	for(int w=1,x=l;w<=t;w++,x++)a[x]=b[w],f[x]=s+a[x],s+=a[x];
}
int main(){
	scanf("%d",&n);
	for(int w=1;w<=n;w++)scanf("%lld",&a[w]),ans+=a[w]*(w-1)-s,s+=a[w];
	S(1,n),printf("%lld",ans);
    return 0;
}
```

---

## 作者：incra (赞：1)

### Solution
水题，提供一个平衡树解法。

转换一下题意，对于每一个 $i$，我们要求的东西就是 $a_i\times cnt-sum$，其中 $cnt$ 和 $sum$ 分别表示在 $1\sim i - 1$ 中，不大于 $a_i$ 的数的个数与总和。

那么我们要维护的就是小于等于某一数的数的数量和总和，这玩意显然可以用平衡树解决。这里我选了 FHQ-treap。

于是这题就差不多了，以 $a_i$ 为 $key$，再另外维护一个数 $sum$，在 $a_i$ 以权值分裂后左边那棵树的 $size$ 和 $sum$ 即为所求。
### Code
[Link](https://atcoder.jp/contests/abc351/submissions/52872339)。

---

## 作者：Engulf (赞：0)

倒序做，对于每个 $i$，假设我们已经处理好 $i+1$
 到 $n$ 的所有贡献，式子 $\max(a_j - a_i, 0)$ 相当于求 $i+1$ 到 $n$ 中，$\ge a_i$ 的数的和（记为 $S$）减去 $\ge a_i$ 的数的个数（记为 $C$）乘 $a_i$，即
 
 $$S-Ca_i$$
 
考虑直接使用动态开点权值线段树维护值域，问题迎刃而解。

每处理完一个 $i$ 就把 $a_i$ 放入线段树中，处理 $i-1$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 4e5 + 5;

int n;
int a[N];

int ls[N * 50], rs[N * 50];
int cnt[N * 50];
ll sum[N * 50];
int idx;

void modify(int &p, int l, int r, int x) {
    if (!p) p = ++idx;
    if (l == r) {cnt[p]++, sum[p] += x; return;}
    int mid = l + r >> 1;
    x <= mid ? modify(ls[p], l, mid, x) : modify(rs[p], mid + 1, r, x);
    sum[p] = sum[ls[p]] + sum[rs[p]];
    cnt[p] = cnt[ls[p]] + cnt[rs[p]];
}

ll querySum(int p, int l, int r, int L, int R) {
    if (l > R || r < L) return 0;
    if (L <= l && r <= R) return sum[p];
    int mid = l + r >> 1;
    return querySum(ls[p], l, mid, L, R) + querySum(rs[p], mid + 1, r, L, R);
}

int queryCnt(int p, int l, int r, int L, int R) {
    if (l > R || r < L) return 0;
    if (L <= l && r <= R) return cnt[p];
    int mid = l + r >> 1;
    return queryCnt(ls[p], l, mid, L, R) + queryCnt(rs[p], mid + 1, r, L, R);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int root = 0;
    ll ans = 0;
    for (int i = n; i; i--) {
        ans += querySum(root, 0, 1e8, a[i], 1e8) - 1ll * queryCnt(root, 0, 1e8, a[i], 1e8) * a[i];
        modify(root, 0, 1e8, a[i]);
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：WorldMachine (赞：0)

树状数组入门题。

类似逆序对的做法，从后往前扫，用树状数组维护所有 $>x$ 的数的个数 $\text{cnt}$ 和元素和 $\text{sum}$，则 $x$ 对答案的贡献为 $\text{sum}-\text{cnt}\cdot x$。

记得离散化。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 400005;
int n, a[N], b[N], d[N];
ll ans;
struct BIT {
	ll c[N];
	void update(int x, int d) { while (x <= n) c[x] += d, x += x & -x; }
	ll query(int x) { ll ans = 0; while (x) ans += c[x], x -= x & -x; return ans; }
} t1, t2;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = d[i] = a[i];
	sort(b + 1, b + 1 + n);
	int len = unique(b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= n; i++) d[i] = lower_bound(b + 1, b + 1 + len, d[i]) - b;
	for (int i = n; i >= 1; i--) {
		ll tmp1 = t1.query(len) - t1.query(d[i]);
		ll tmp2 = t2.query(len) - t2.query(d[i]);
		ans += tmp2 - tmp1 * a[i];
		t1.update(d[i], 1);
		t2.update(d[i], a[i]);
	}
	printf("%lld", ans);
}
```

---

## 作者：_WRYYY_ (赞：0)

[在我的博客观看。](https://www.cnblogs.com/wryyy-233/p/18162643)

实际上很板。

考虑在 $i$ 后小于 $val_i$ 的数都对答案没贡献，所以我们只需要知道在 $i$ 后且大于 $val_i$ 的数的和以及有多少个这样的数就可以了。

知道了我们要求什么，就可以一眼权值线段树。

从后往前扫不断加入数，然后访问对应区间即可，当然因为值域比较大，所以还要离散化。

时间复杂度 $O(n\log_2n)$。

因为赛时写的比较急，所以比较丑。

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define N 400010
using namespace std;
using namespace __gnu_pbds;
ll tr[N << 2], val[N], a[N],tc[N<<2];
map<ll, ll> ma;
void tr_p(int k, int l, int r, int x, ll c)
{
	if (l > x || r < x)
		return;
	if (l == r && l == x)
	{
		tr[k] += c;
		++tc[k];
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid)
		tr_p(k << 1, l, mid, x, c);
	else
		tr_p(k << 1 | 1, mid + 1, r, x, c);
	tr[k] = tr[k << 1] + tr[k << 1 | 1];
	tc[k] = tc[k << 1] + tc[k << 1 | 1];
	return;
}
ll tr_a(int k, int l, int r, int x, int y)
{
	if (l > y || r < x)
		return 0;
	if (l >= x && r <= y)
		return tr[k];
	int mid = l + r >> 1;
	ll ans = 0;
	if (x <= mid)
		ans += tr_a(k << 1, l, mid, x, y);
	if (y > mid)
		ans += tr_a(k << 1 | 1, mid + 1, r, x, y);
	return ans;
}
ll tr_a1(int k, int l, int r, int x, int y)
{
	if (l > y || r < x)
		return 0;
	if (l >= x && r <= y)
		return tc[k];
	int mid = l + r >> 1;
	ll ans = 0;
	if (x <= mid)
		ans += tr_a1(k << 1, l, mid, x, y);
	if (y > mid)
		ans += tr_a1(k << 1 | 1, mid + 1, r, x, y);
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, rn, id;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> val[i];
		a[i] = val[i];
	}
	sort(a + 1, a + 1 + n);
	rn = unique(a + 1, a + 1 + n) - a - 1;
	// cerr << rn;
	id = 0;
	for (int i = 1; i <= rn; i++)
	{
		++id;
		ma[a[i]] = id;
	}
	ll ans = 0;
	for (int i = n; i; i--)
	{
		ans += tr_a(1, 1, rn, ma[val[i]], rn) - val[i] * tr_a1(1, 1, rn, ma[val[i]], rn);
		tr_p(1, 1, rn, ma[val[i]], val[i]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：_qhbd_ (赞：0)

# 题意
给定有 $N$ 个元素的序列 $A$，求 $\sum_{i=1}^{N}\sum_{j=i+1}^N\max(0,A_j-A_i)$。
# 思路
$\sum_{i=1}^{N}\sum_{j=i+1}^N\max(0,A_j-A_i)$ 可等同于 $\sum_{i=1}^{N}\sum_{j=1}^{i-1}[A_i>A_j]\times(A_i-A_j)$。

对于变换后式子，如果用暴力处理的思路，每次查找之前小于当前枚举数的数，然后用计当前数减去小于当前数的总差值。

然后，不难发现，我们可以用两个树状数组存储数的个数和数的和。虽然 $0\le A_i\le10^8$，但是 $2\le N\le 4\times10^5$，所以，可以先离散各数，然后遍历 $A$，每次将当前数依离散值存入树状数组，同时求出小于当前数的数的数量和它们的和，然后用当前数乘以小于当前数的数量减去它们的和。
# 代码
```cpp
#include<bits/stdc++.h>

#define ll long long
#define lb(x) (-x&x)

using namespace std;

const int N=4e5+5;

int n;
int ID;
int a[N];

map<int,int> id;

ll rt[N];
ll tr[N];
ll ans;

inline void update(int i,int x){

    for(;i<=n;i+=lb(i)){

        tr[i]+=x;
        rt[i]++;
    }
}

inline ll querynum(int i){

    ll res=0;

    for(;i>0;i-=lb(i))
        res+=rt[i];

    return res;
}

inline ll queryval(int i){

    ll res=0;

    for(;i>0;i-=lb(i))
        res+=tr[i];

    return res;
}

int main(){

    scanf("%d",&n);

    for(int i=1;i<=n;i++){

        scanf("%d",&a[i]);

        id[a[i]]=0;
    }

    for(auto t:id)
        id[t.first]=++ID;
    
    for(int i=1;i<=n;i++){

        int x=id[a[i]];

        ans+=querynum(x)*a[i]-queryval(x);

        update(x,a[i]);
    }

    printf("%lld",ans);

    return 0;
}
```

---

## 作者：__Floze3__ (赞：0)

## 思路简介

~~AT 不会出题可以不出，又放个板子什么意思？~~

我们想到，对于一个数 $A_i$，记在它之前的数有 $cnt$ 个，这些数的和为 $sum$，那么这个数所产生的贡献即为 $A_i \times cnt - sum$。考虑扫描线算法，用两个树状数组分别统计小于等于某个数的个数以及这些数的和，一边统计答案，一边把当前的数插入树状数组中。注意到值域为 $10^8$，因此我们需要离散化。

## 代码

由于头文件过于冗长，这里只放实际有效的代码。

```cpp
const int N = 4e5 + 5;
const int mod = 1e9 + 7;
const ll inf = 1e18;

int n, tot;
ll a[N], tree1[N], b[N], ans, tree2[N];

il void add(ll tree[], int p, ll val) {
    for (; p <= tot; p += lowbit(p)) tree[p] += val;
    return ;
}

il ll ask(ll tree[], int p) {
    ll res = 0;
    for (; p; p -= lowbit(p)) res += tree[p];
    return res;
}

signed main() {
    #ifdef FLOZE_TOT
    file("");
    #endif
    read >> n;
    _FOR(i, 1, n) {
        read >> a[i];
        b[i] = a[i];
    }
    std::sort(b + 1, b + 1 + n);
    tot = std::unique(b + 1, b + 1 + n) - b - 1;
    _FOR(i, 1, n) {
        int t = std::lower_bound(b + 1, b + 1 + tot, a[i]) - b;
        ans += ask(tree2, t) * a[i] - ask(tree1, t);
        add(tree1, t, a[i]), add(tree2, t, 1ll);
    }
    write << ans;
    Avada_Kedavra;
}
```

---

## 作者：Redshift_Shine (赞：0)

# AT_abc351_f [Double Sum](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc351_f)

## 题面简述

对于长度为 $n$ 的数列 $a$ 求

$$
\sum_{i=1}^n\sum_{j=i+1}^n \max(a_j-a_i,0)
$$

## 省流

树状数组 + 离散化。

没有 E 难。

## 思路

首先，尽管内存限制为 1024MiB ，我们仍然不能使用未经离散化的树状数组，因为会空间超限。

按照顺序遍历 $a$ 中的元素 $a_k$ ，则题面中 $j=k$ 时对答案做的贡献就是

$$
\sum_{i=1}^{j-1} (a_j-a_i) [a_j>a_i]
$$

将其展开得

$$
a_j\times\sum_{i=1}^{j-1} [a_j>a_i]-\sum_{i=1}^{j-1} a_i[a_j>a_i]
$$

显然可以使用树状数组维护。

时间复杂度为 $O(n\log n)$ 。

## 代码

```c++
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 4e5 + 10;
using ll = long long;
int n, m;
ll tr1[N], tr2[N], ret, x[N], y[N], tmp;
void update(ll *tr, int x, int y)
{
    while (x < N)
        tr[x] += y, x += (x & -x);
}
ll query(ll *tr, int x)
{
    ll res = 0;
    while (x)
    {
        res += tr[x];
        x -= (x & -x);
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", x + i);
        y[i] = x[i];
        // ret += x * query(tr2, x) - query(tr1, x);
        // update(tr1, x + 1, x);
    }
    sort(y + 1, y + n + 1);
    m = unique(y + 1, y + n + 1) - y - 1;
    for (int i = 1; i <= n; i++)
    {
        tmp = x[i];
        x[i] = lower_bound(y + 1, y + m + 1, x[i]) - y;
        ret += tmp * query(tr2, x[i]) - query(tr1, x[i]);
        update(tr1, x[i] + 1, tmp);
        update(tr2, x[i] + 1, 1);
    }
    printf("%lld\n", ret);
}
```

---

