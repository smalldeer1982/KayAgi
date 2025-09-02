# Tufurama

## 题目描述

One day Polycarp decided to rewatch his absolute favourite episode of well-known TV series "Tufurama". He was pretty surprised when he got results only for season 7 episode 3 with his search query of "Watch Tufurama season 3 episode 7 online full hd free". This got Polycarp confused — what if he decides to rewatch the entire series someday and won't be able to find the right episodes to watch? Polycarp now wants to count the number of times he will be forced to search for an episode using some different method.

TV series have $ n $ seasons (numbered $ 1 $ through $ n $ ), the $ i $ -th season has $ a_{i} $ episodes (numbered $ 1 $ through $ a_{i} $ ). Polycarp thinks that if for some pair of integers $ x $ and $ y $ ( $ x<y $ ) exist both season $ x $ episode $ y $ and season $ y $ episode $ x $ then one of these search queries will include the wrong results. Help Polycarp to calculate the number of such pairs!

## 说明/提示

Possible pairs in the second example:

1. $ x=1 $ , $ y=2 $ (season 1 episode 2 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 2 episode 1);
2. $ x=2 $ , $ y=3 $ (season 2 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 2);
3. $ x=1 $ , $ y=3 $ (season 1 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 1).

In the third example:

1. $ x=1 $ , $ y=2 $ (season 1 episode 2 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 2 episode 1);
2. $ x=1 $ , $ y=3 $ (season 1 episode 3 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF961E/6ef98cfc3df1e68639bb147759e3ed8244b80174.png) season 3 episode 1).

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3
8 12 7
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
3 2 1
```

### 输出

```
2
```

# 题解

## 作者：YellowBean_Elsa (赞：10)

### 写一篇分析较详细的树状数组题解

首先简化题意:

- 对于 $[1,n]$ 中的每个数 $i$，告诉你 $a_i$

- 请求出有多少有序数对 $(i,j)$ 满足:

$$ j \le a_i$$
$$ i \leq a_j$$
$$ i<j$$

对于这种多维题目，常见思路是根据单调性质维护几维，再用数据结构维护几维

所以我们可以把每个数先都插入树状数组，再通过扫描，利用单调性质及时排除无效点

流程如下：

1. 建立两个数组 $u$，$v$，分别按 $i$，$a_i$ 排序

1. 按 $u$ 从 $1$ 扫到 $n$ ，每扫到一个数就把它从树状数组中删除，维护条件3

2. 每扫到一个数 $i$，就把 $v$ 中前面不满足 $i \leq a_j$ 的点从树状数组中删除，维护条件2

1. 对于每个点，它的答案就是在树状数组中查询 $a_i$ 的结果，维护条件1

上代码

```cpp
//coder: FeliksYB, an AKer of IMO
#include<bits/stdc++.h>
#define ll long long//小心见祖宗qwq 
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')f=-1,ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return f*x;
}const int N=2e5+15;
int n,a[N];
struct point{//按a顺序储存每个点 
	int x,a;
	bool operator < (const point &A)const{
		return a<A.a;
	}
}p[N];
ll c[N];//树状数组 
inline ll lowbit(ll x){
	return x&-x;
}inline ll query(ll x){
	ll res=0;
	for(;x;x-=lowbit(x))res+=c[x];
	return res;
}inline void add(ll x,int k){
	for(;x<=n;x+=lowbit(x))c[x]+=k;
}ll ans;
bool out[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		p[i].a=read();
		p[i].x=i;
		p[i].a=min(p[i].a,n);//优化，请根据Sample2自行理解 
		add(i,1);//把点插入树状数组 
		a[i]=p[i].a;
	}
	sort(p+1,p+n+1);//按a排序 
	//对于每个点i计算有几个点与之可以匹配 
	for(int i=1,now=1;i<=n;i++){
		//排除无效点j (because j <= i) 
		if(!out[i])add(i,-1),out[i]=1;
		//排除无效点j (because a[j] < i) 
		while(now<=n && p[now].a<i){
			if(!out[p[now].x])add(p[now].x,-1),out[p[now].x]=1;
			++now;
		} 
		ans+=query(a[i]);//查询a[i]之前，确保a[i]>=j 
	}
	printf("%lld\n",ans);
	return 0;
}/*一组易错data：
5
4 5 2 4 3
output 6
*/
```


---

## 作者：SunnyYuan (赞：9)

1. 我们维护一个存储下标数据的树状数组，先将 $1\sim n$ 插入树状数组。

2. 用 $a$ 表示原数组，$b$ 表示按照 $a_i$ 排序后的数组。

3. 我们从 $1$ 开始统计，直到 $n$，统计时：

   - 将 $i$ 删除，不能把自己算进去。

   - 为了排除 $a_j < i$ 的部分，可以从前往后扫描 $b$，一直删，直到 $b_{\text{cur}} \geq i$，

     因为 $b$ 单调不下降，所以 $i$ 都用不着了， $i + 1$ 也用不着了。

   - 调查 $a_i \geq j$ 的部分，调用 $\text{query}(a_i)$ 即可。

   - 注意：排除的时候用 $b$，这样就不用遍历整个 $a$ 数组来排除 $a_j < i$ 的部分；

     而询问的时候要用 $a$，因为询问的是 $a_i \geq j$ 的部分。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using i64 = long long;

const int N = 200010;

int tr[N];

void add(int x, int v) {
	for (; x < N; x += x & -x) tr[x] += v;
}

int ask(int x) {
	int res = 0;
	for (; x; x -= x & -x) res += tr[x];
	return res; 
}

int n;
int a[N];

struct Node {
	int id;
	int v;
}b[N];

bool del[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i].id = i;
		b[i].v = a[i];
	}
	for (int i = 1; i <= n; i++) add(i, 1);
	sort(b + 1, b + n + 1, [](const Node& a, const Node& b) { return a.v < b.v; });
	int cur = 1;
	i64 ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!del[i]) del[i] ^= 1, add(i, -1);
		while (b[cur].v < i && cur <= n) {
			if (!del[b[cur].id]) del[b[cur].id] ^= 1, add(b[cur].id, -1);
			cur++;
		}
		ans += ask(min(n, a[i]));
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Tari (赞：6)

另一种树状数组。

题意：

$$ans=\sum_{i=1}^{n}\sum_{j=i+1}^{a[i]} [a[j]\geq i]$$

对于每一个 $i$ ：

$$\sum_{j=i+1}^{a[i]} [a[j]\geq i]=\sum_{j=i+1}^{n} [a[j]\geq i]-\sum_{j=a[i]+1}^n [a[j]\geq i]$$

对于每一个 $i$ 答案即为两个后缀和的差；所以我们可以把每一天倒着插入，然后分别求出两部分的答案，后缀和可以用树状数组维护。

详见代码：
```cpp
#include<bits/stdc++.h>
#define R register int
#define ll long long
using namespace std;
namespace Luitaryi {
inline int g() { R x=0,f=1;
	register char s; while(!isdigit(s=getchar())) f=s=='-'?-1:f;
	do x=x*10+(s^48); while(isdigit(s=getchar())); return x*f;
} const int N=200010;
int n,L,a[N],c[N],ans[N]; ll anss;
vector <int> s[N];
inline void add(int x) {for(;x<=L;x+=x&-x) ++c[x];}
inline int query(int x) { R ret=0;
	for(;x;x-=x&-x) ret+=c[x]; return ret;
}
inline void main() {
	n=g(),L=n+1; for(R i=1;i<=n;++i) {
		a[i]=g(),a[i]=a[i]>n?n+1:a[i];
		if(a[i]>i) s[a[i]].push_back(i);
	}
	for(R i=n;i;--i) {
		for(R j=0,lim=s[i].size();j<lim;++j) 
			ans[s[i][j]]-=n-i-query(s[i][j]-1);
		if(a[i]>i) ans[i]+=n-i-query(i-1);
		add(a[i]);
	} for(R i=1;i<=n;++i) anss+=ans[i];
	printf("%lld\n",anss);
}
} signed main() {Luitaryi::main(); return 0;}
```

2019.11.08

---

## 作者：antiquality (赞：6)

看见唯一篇题解写的是主席树……

这固然不失为一种不错的方法，但是也有不用高级数据结构的做法

比如，树状数组。

实际上呢，真实题意用数学语言表达就是上一篇列出的公式；我这里用更加形象的语言描述一下真实题意：

> 有一部电视剧有n季，每一季有ai集。定义二元组(i,j)：存在第i季有第j集。求(i,j)与(j,i)同时合法(i<j)的对数。

> 简洁一些就是：求<i,j>对数，使得a[i]≥j，a[j]≥i并且(i<j)

这样子看上去就好理解多了吧……

更加具体的分析我列在[博客](http://www.cnblogs.com/antiquality/p/8746718.html)里了，这里贴出代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;
int n,now,a[200035];
struct node
{
    int a,i;
    bool operator < (node &xx) const
    {
        return a < xx.a;
    }
}p[200035];
int f[200035];
int read()
{
    char ch = getchar();int num = 0;
    for (; !isdigit(ch); ch = getchar());
    for (; isdigit(ch); ch = getchar())
        num = (num<<3)+(num<<1)+ch-48;
    return num;
}
int lowbit(int x){return x&-x;}
void add(int x, int c){for (; x<=n+1; x+=lowbit(x))f[x]+=c;}
int query(int x)
{
    int ret = 0;
    for (; x; x-=lowbit(x))
        ret += f[x];
    return ret;
}
int main()
{
    n = read();now = 1;
    for (int i=1; i<=n; i++)
        a[i] = min(read(), n+1), p[i].a = a[i], p[i].i = i, add(i, 1);
    sort(p+1, p+n+1);
    for (int i=1; i<=n; i++)
    {
        while (now<=n && p[now].a < i)add(p[now++].i, -1);
        ans += query(a[i]);
        if (a[i] >= i)ans--;
    }
    cout << ans / 2 << endl;
    return 0;
}
```

~~看上去挺简洁的对吧~~

---

## 作者：Tx_Lcy (赞：2)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16856957.html)

[题目传送门](https://www.luogu.com.cn/problem/CF961E)

## 思路

个人觉得主席树比较好想，而且代码非常简单，仅需 $37$ 行。

我们不妨枚举 $j$，这样 $i$ 的范围就被确定在了 $1$ 至 $\min(j-1,a_j)$，也就是说我们需要查询的内容就是所有 $1 \le i \le \min(j-1,a_j)$ 且 $a_i \ge j$ 的 $i$ 的个数。

于是主席树维护即可，时空复杂度 $\mathcal O(n \log n)$。

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int const N=2e5+10;
int n,cnt=1,a[N],c[N*50],root[N*50],lc[N*50],rc[N*50];
#define ls (lc[x])
#define rs (rc[x])
#define mid ((l+r)>>1)
inline int clone(int x){lc[++cnt]=lc[x];rc[cnt]=rc[x];c[cnt]=c[x];return cnt;}
inline int update(int la,int l,int r,int p){
	int x=clone(la);
	if (l==r){++c[x];return x;}
	if (p<=mid) ls=update(lc[la],l,mid,p);
	else rs=update(rc[la],mid+1,r,p);
	c[x]=c[ls]+c[rs];
	return x;
}
inline int query(int x,int l,int r,int p){
	if (!x) return 0;
	if (l==r) return c[x];
	if (p<=mid) return query(ls,l,mid,p)+c[rs];
	else return query(rs,mid+1,r,p);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;root[0]=1;
	long long ans=0;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=1;i<=n;++i)
		root[i]=update(root[i-1],1,1e9,a[i]);	
	for (int i=2;i<=n;++i){
		int lim=min(a[i],i-1);
		ans+=query(root[lim],1,1e9,i);
	}
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：dalao_see_me (赞：2)

居然没人写分块题解？来一发！

[题目传送门](https://www.luogu.com.cn/problem/CF961E)
## 题目大意
设二元组 $(x,y)$，满足 $x<y$，$y\le a_x$，$x\le a_y$。求二元组个数。
## 做法
显而易见的一点是，$1\le x,y\le n$。

接下来，我们考虑从 $1$ 到 $n$ 枚举 $x$。

此时 $y$ 的取值范围是 $x+1\le y\le a_x$。

那么，我们还需要满足 $x\le a_y$ 这个条件。

把整个 $y$ 的范围一起看，问题转化成了“区间查询大于等于 $k$ 的数的个数（不带修）”。

这就可以用分块解决了。

对于每一个块，可以用 `vector` 维护该块内的元素（有序）。

在查询时，对于完整的块，二分求出大于等于 $k$ 的数的个数；

对于不完整的块，暴力求出大于等于 $k$ 的数的个数。

不会的可以左转[这里](https://loj.ac/p/6278)，和这题还是很像的。

时间复杂度是 $O(n\sqrt n\log\sqrt n)=O($ 跑得过 $)$。

然后就到了快乐的代码时间。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5, M = 455;
vector <int> v[M];
int bel[N], a[N], l[M], r[M];
int n, block, ans;
inline int read() {
	int x = 0, f = 1; char c = getchar();
	while (c < '0' || c > '9') {if (c == '-') f = -f; c = getchar();}
	while (c >= '0' && c <= '9') {x = x * 10 + (c ^ 48); c = getchar();}
	return x * f;
}
inline int query(int p, int q, int val) {
	if (p > q) return 0;
	int res = 0;
	if (bel[p] == bel[q]) {
		for (int i = p; i <= q; i++) if (a[i] >= val) res++;
		return res;
	}
	for (int i = bel[p] + 1; i < bel[q]; i++) res += r[i] - l[i] + 1 - (lower_bound(v[i].begin(), v[i].end(), val) - v[i].begin());
	for (int i = p; i <= r[bel[p]]; i++) res += a[i] >= val ? 1 : 0;
	for (int i = l[bel[q]]; i <= q; i++) res += a[i] >= val ? 1 : 0;
	return res;
}
signed main() {
	n = read();
	for (int i = 1; i <= n; i++) a[i] = min(read(), n);
	block = sqrt(n);
	for (int i = 1; i <= block; i++) {
		l[i] = r[i - 1] + 1;
		r[i] = i * block;
		for (int j = l[i]; j <= r[i]; j++) bel[j] = i, v[i].push_back(a[j]);
		sort(v[i].begin(), v[i].end());
	}
	if (r[block] < n) {
		block++;
		l[block] = r[block - 1] + 1;
		r[block] = n;
		for (int j = l[block]; j <= r[block]; j++) bel[j] = block, v[block].push_back(a[j]);
		sort(v[block].begin(), v[block].end());
	}
	for (int i = 1; i <= n; i++) ans += query(i + 1, a[i], i);
	printf("%lld", ans);
	return 0;
}
```
$46$ 行结束，简洁明了。

---

## 作者：Bosun (赞：2)

## 全真主席树做法，你值得拥有
(震惊！此题使用主席树，仅需59行即可搞定！)

 简化题意，我们可以发现题目要求的是Ai≥j且i≤Aj(1<=i,j<=n)的对数，这是一个二维的东西。
 
 那么，我们要写一个又臭又长的线段树套线段树。喂喂喂，别走啊，我刚刚开van笑的呢！众所周知，主席树也可以维护二维信息，我们就可以利用下标的有序性将题目转化成:在i时间将Ai插入主席树中，最后对于每个i求在Ai时间时主席树中比i小的个数。这样就可以完美解决了。
 
 还有一些细节要注意：我们不需要离散化Ai,因为当Ai≥n与Ai==n实质是相同的。当然，如果Ai≥i ，会将自己统计一次，所以在一开始减掉，最后除以2就行了。
 
 code:
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int N=200005;
int cnt,a[N],rt[N];
typedef long long ll;
ll ans;
struct node{
	int ls,rs,s;
	node(){
		ls=0,rs=0,s=0;
	}
};
node t[N*40];
struct fuck_wxw{
	int build(int l,int r){
		int now=++cnt;
		if(l<r){
			int mid=l+r>>1;
			t[now].ls=build(l,mid);
			t[now].rs=build(mid+1,r);
		}
		return now;
	}
	int update(int k,int l,int r,int v){
		int now=++cnt;
		t[now]=t[k],t[now].s=t[k].s+1;
		if(l<r){
			int mid=l+r>>1;
			if(v<=mid)t[now].ls=update(t[k].ls,l,mid,v);
			else t[now].rs=update(t[k].rs,mid+1,r,v);	
		}
		return now;
	}
	int query(int k,int l,int r,int v){
		if(l==r)return t[k].s;
		int mid=l+r>>1;
		if(v<=mid){
			return t[t[k].rs].s+query(t[k].ls,l,mid,v);
		}else{
			return query(t[k].rs,mid+1,r,v);
		}
	}
}T;
int main(){
	int i;
	cin>>n;
	ll tot=0;
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]=min(a[i],n);
		if(a[i]>=i)ans--;
	}
	rt[0]=T.build(1,n);
	for(i=1;i<=n;i++)rt[i]=T.update(rt[i-1],1,n,a[i]);
	for(i=1;i<=n;i++)ans+=1ll*T.query(rt[a[i]],1,n,i);
	cout<<ans/2<<endl;
	return 0;
} 
```


---

## 作者：jch123 (赞：1)

## 解题思路：

$i<j$ 与 $a_j\ge i$ 可以转化为 $i \le \min(j-1,a_j)$ 这样的话就能用树状数组查询后缀和就行。

查询时的时候只需查 $\min(i-1,a_i)$ 的后缀来满足 $a_i \ge j$ 即可。一个小技巧是插入 $\max(n,a_i)$ 就行，这样不会影响答案。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N],c[N];
vector<int> v[N]; 
int n;
int lowbit(int x){return x&(-x);}
void add(int p,int x)
{
	while(p<=n)
	{
		c[p]+=x;
		p+=lowbit(p);
	}
}
int ask(int p)
{
	int res=0;
	while(p)
	{
		res+=c[p];
		p-=lowbit(p);
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],v[min(i-1,a[i])].push_back(i);
	long long ans=0;
	int p=1;
	for(int i=1;i<=n;i++)
	{
		add(min(n,a[i]),1);
		for(int x:v[i]) ans+=ask(n)-ask(x-1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：GJX_Algorithm (赞：1)

# CF961E 题解
## 题目描述
- 给定一个长度为 $n$ 的序列 $a$。

- 定义二元组 $(i,j)$ 满足 $1 \le i < j \le n ∧ a_i \ge j ∧ a_j \ge i$。

- 求序列 $a$ 中二元组的个数。

## 解题思路
- 如果读者在做这一题之前做过 [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)，就能发现这两题非常像。

- 我们发现，逆序对这题只有两个条件，但此题给出了三个条件，根据这个区别继续挖掘就会发现 $1 \le i < j \le n ∧ a_j \ge i$ 可以转化为 $i \le \min(j - 1,a_j)$，接下来就可以树状数组了。

- 我们可以对每个 $i$ 在下标 $\min(i - 1,a_i)$ 的地方插入询问，显然此时已经满足 $i \le \min(j - 1,a_j)$ 这个条件，另外一个条件树状数组就能帮我们解决啦！！！！！

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x & -x
using namespace std;
const int N = 2e5 + 5, INF = 1e9;
int n, a[N], ans;
vector<int> vt[N];
map<int, int> tree;
int query(int x)
{
    int sum = 0;
    while (x < INF)
    {
        sum += tree[x];
        x += lowbit(x);
    }
    return sum;
}
void update(int x)
{ 
    while (x > 0)
    {
        tree[x]++;
        x -= lowbit(x);
    }
    return ;
}
signed main()
{
  	cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) vt[min(i - 1, a[i])].push_back(i);
    for (int i = 1; i <= n; i++)
    {
        update(a[i]);
        for (int x : vt[i]) ans += query(x);
    }
	cout << ans;
	return 0;
}
```

---

## 作者：mango2011 (赞：1)

提供一种不一样的分块思路。

首先，我们发现这道题有一个好性质（都不需要离散化了这），就是令 $a_i=\min(a_i,n)$ 一定不影响答案。这样，我们就成功的把值域控制在 $n$ 以内。

像逆序对一样，我们先枚举右端点 $j$，这时我们考虑什么样的 $i$ 满足条件：

+ $1\le i\le \min(j-1,a_j)$，这是因为 $a_j\ge i$ 且 $i<j$。

+ $a_i\ge j$，这是因为 $a_i\ge j$（显然）。

那么我们就可以开始维护了，对于每一个 $j$，令 $p_j=\min(j-1,a_j)$，则我们需要维护 $[1,p_j]$ 中使得 $a_i\ge j$ 的 $i$ 的个数，由于值域很小，所以：

考虑分块，记 $ton_{i,j}$ 为第 $i$ 个块中使得 $a_k\ge j$ 的 $k$ 的个数，$O(n\sqrt n)$ 预处理。询问时从左到右扫描每一个块，对多余的部分单独计算，统计贡献即可。

每一次“询问”都是 $O(\sqrt n)$，总复杂度为 $O(n\sqrt n)$。

一个温馨提示：由于内存限制比较紧张，所以可以令块长 $len=1000$。

综上，我们就解决了这个问题。

---

## 作者：_acat_ (赞：1)

## 题目大意

给一个长度为 $n$ 的序列 $A$。
问有多少个有序对 $(x,y)$ 满足:
1. $x<y$
2. $A_x \ge y$
3. $A_y \ge x$

$n \le 2e5$。

## 思路

先分析下条件，可以合并前 $2$ 个得到：

数对满足 $x<y \le A_x$ 且 $A_y \ge x$。

像这种有坐标有值的一般都类似于二维数点问题。我们可以用扫描线思想，通过对一维排序按顺序处理来满足这一维的要求，另一维就可以用数据结构来维护。

本题枚举 $x$ 这一维方便，（只需要把 $\ge x$ 的 $A_y$ 加进来，否则如果枚举 $y$，$x$ 有 $2$ 种情况。）

因此我们从大到小枚举 $x$。

然后把 $A_y \ge x$ 的 $y$ 记录下来。

然后查询在区间 $\left(x,A_x\right]$ 的 $y$ 的个数即可。

显然用树状数组就可以做到，时间复杂度 $O(n \log n)$。

本题维护 $A_i$ 的值时需要离散化，我们可以这样处理来避免离散化:

如果 $A_i>n$，那么可以把 $A_i$ 改为 $n$。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200010
using namespace std;
int n,a[N], sum[N],b[N];
int lowbit(int x){
    return x&(-x);
}
void change(int x,int v){
    while(x<=n){
        sum[x]+=v;
        x+=lowbit(x);
    }
}
int query(int x){
    int ret=0;
    while(x){
        ret+=sum[x];
        x-=lowbit(x);
    }
    return ret;
}
int cmp(int x,int y){
    return a[x]>a[y];
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        a[i]=min(a[i],n);
        b[i]=i;
    }
    sort(b+1, b+n+1, cmp);
    int j=0;
    ll ans=0;
    for(int i=n;i>=1;i--){
        while(j+1<=n&a[b[j+1]]>=i){
            change(b[j+1],1);
            j++;
        }
            if(i<=a[i]){
                ans+=query(a[i])-query(i);
            }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：hegm (赞：1)

### [Tufurama](https://www.luogu.com.cn/problem/CF961E)

对于可持久化来说，就是一简单题。

观察题面，发现我们要求的是下标和权值的关系。

那么我们可持久化序列下标，也就是以下标为版本。

由于有关值域，所以我们选择权值线段树。

对于点 $i$，我们需要查询版本 $1\sim \min(n,a_i)$，权值范围在 $i\sim \infty$ 的区间点的数量。

注意到这样会对于 $a_i\ge i$ 的点多算，所以我们要减去所有 $a_i\ge i$ 的点。

然后对于一个点对，我们会分别在 $i,j$ 的位置算两遍，所以最终答案要除 $2$。

### $\text{CODE}$
```cpp
#include<bits/stdc++.h>
#define N 200005
#define int long long
#define lc tr[to].ls
#define rc tr[to].rs
#define inf 1000000000
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,a[N],rt[N];
struct tree
{
	int ls,rs,siz;
}tr[N*40];int tot;
int news(int now)
{
	tr[++tot]=tr[now];
	return tot;
}
void up(int to){tr[to].siz=tr[lc].siz+tr[rc].siz;}
int add(int now,int l,int r,int x)
{
	int to=news(now);
	if(l==r)
	{
		tr[to].siz++;
		return to;
	}
	int mid=(l+r)>>1;
	if(mid>=x)lc=add(tr[now].ls,l,mid,x);
	else rc=add(tr[now].rs,mid+1,r,x);
	up(to);
	return to;
}
int que(int nl,int nr,int l,int r,int ql,int qr)
{
	if(l>=ql&&r<=qr)return tr[nr].siz-tr[nl].siz;
	int mid=(l+r)>>1,cnt=0;
	if(mid>=ql)cnt+=que(tr[nl].ls,tr[nr].ls,l,mid,ql,qr);
	if(mid<qr)cnt+=que(tr[nl].rs,tr[nr].rs,mid+1,r,ql,qr);
	return cnt;
}
int ans=0;
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)rt[i]=add(rt[i-1],1,inf,a[i]);
	for(int i=1;i<=n;i++)ans+=que(rt[0],rt[min(a[i],n)],1,inf,i,inf);
	for(int i=1;i<=n;i++)if(a[i]>=i)ans--; 
	cout<<ans/2<<"\n";
	return 0;
}
```

---

## 作者：FiraCode (赞：1)

## 题意
给你一个数组，求 $i,j$ 满足：

*	$1 \le x < y \le n$
*	$y \le a_x$
*	$x \le a_y$

## 题解思路
读入的时候，因为 $j \le n$ 所以当 $a_i > n$ 时，我们把 $a_i$ 变成 $n$ 就可以了。

然后我们可以用一个 `vector` 来维护 $(1)$ 和 $(3)$ 的最大可能值。

那么我们设 $v_i$ 表示最大可能为 $i$ 的数的下标是多少。

那么最大可能值就是 $i - 1$ 与 $a_i$ 取个最小值就行了。

因为 $x \le a_y$ 所以一种最大的可能就是 $x=a_y$，另一种就是 $i - 1$，因为 $x < y$ 所以 $x$ 的最大值就是 $y - 1$。

然后就枚举 $i$，然后对于每个 $i$ 枚举对应的 $v_i$，然后答案就加上 $i - \sum_{a_i < v_j}$。

## AC CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000010;
int &read(int &r){//快读
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
int n;
int a[N];
vector<int> v[N];//表示i最大的x是多少
template<class T>
struct BIT {//树状数组模板
	T c[N];
	void modify(int x, T d) {
		if (x <= 0) return;
		for (; x <= n; x += (x & -x))
			c[x] += d;
	}
	T query(int x) {
		T res = 0;
		for (; x; x -= (x & -x))
			res += c[x];
		return res;
	}
};
BIT<ll> c;
int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		a[i] = min(a[i], n);
		v[min(i - 1, a[i])].push_back(i);
		//因为要满足i>j那么i最大就是j-1,且i<=a[j]，所以还要与a[j]取个最小值
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		c.modify(a[i], 1);
		for (auto t : v[i]) {
			ans += i - c.query(t - 1);//答案加上总数- x<a[x]的数的个数
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑树状数组。

对于条件 $a_j \ge i \land a_i \ge j \land i <j$，可以转化为：$a_i \ge j \land i \le \min(j-1,a_j)$。

对于每个 $j$，在下标 $\min(j-1,a_j)$ 插入一个询问。然后枚举 $i$ 和这个下标上的询问。此时显然所有 $i \le \min(j-1,a_j)$ 的值都已经有了，直接树状数组求不小于 $j$ 的数量即可。复杂度 $O(n \log V)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=2e5+10,inf=1e9+1;
int n,a[N],ans;
vector<int> in[N];
unordered_map<int,int> tr;

il void add(int x){
	while(x) ++tr[x],x-=x&(-x);
}
il int query(int x){
	int ans=0;
	while(x<inf) ans+=tr[x],x+=x&(-x);
	return ans;
}

il void solve(){
	n=rd;
	for(re int i=1;i<=n;++i) a[i]=rd;
	for(re int i=1;i<=n;++i) in[min(i-1,a[i])].push_back(i);
	for(re int i=1;i<=n;++i){
		add(a[i]);
		for(auto j:in[i]) ans+=query(j);
	}
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}

```

---

## 作者：2021sunzishan (赞：0)

这是一篇主席树题解，应该比较详细了。

## 思路：
首先看题目给的几个式子：

$1\le i<j\le n$

$j\le a_i$

$i\le a_j$

那么为了查找方便我们先把 $i$ 和 $j$ 调换一下位置:

$1\le j<i\le n$

$i\le a_j$

$j\le a_i$

然后合并第 $1$ 和第 $3$ 个式子，就得出了 $j$ 的范围：

$j\le i-1$ 且 $j\le a_i$

所以我们要求的就是 $a_k$ （$k$ 在 $1$ 到 $\min(i-1,a_i)$ 这个区间里面）小于等于 $i$ 的数有多少个，就是与 $i$ 相匹配的答案。

我们开一个可持久化权值线段树（如果不会就上网看一眼，跟普通线段树差不多，非常简单,就是桶）。第 $k$ 棵树里面存的就是 $1$ 到 $k$ 的信息，直接查询第 $k$ 棵树即可。

以上就是本题的思路了，如果还不懂，那就看看代码吧。

**切勿抄袭！！！**

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//偷个懒(要开long long)
#define N 5000005//nlog(n)
int root[N],a[N];
struct node{
	int lson,rson,s;
}tr[N];
int cnt=0,n;
int build(int l,int r){//建第一棵空树
	int u=++cnt;
	if(l==r)
		return u;
	int mid=(l+r)/2;
	tr[u].lson=build(l,mid);
	tr[u].rson=build(mid+1,r);
	return u;
}
void push(int u){//上传信息
	int lson=tr[u].lson,rson=tr[u].rson;
	tr[u].s=tr[lson].s+tr[rson].s;
}
int sig(int u,int l,int r,int k){//建一棵新的log(n)的树，及可持久化
	tr[++cnt]=tr[u];
	int v=cnt;
	if(l==r){
		tr[v].s++;//桶
		return v;
	}
	int mid=(l+r)/2;
	if(k<=mid)
		tr[v].lson=sig(tr[u].lson,l,mid,k);
	if(mid<k)
		tr[v].rson=sig(tr[u].rson,mid+1,r,k);
	push(v);
	return v;
}
int ask(int u,int l,int r,int k){//查询以u为根的子树的信息
	if(u==0)return 0;
	if(l==r)return tr[u].s;
	int mid=(l+r)/2,ans=0;
	if(k<=mid)
		ans+=ask(tr[u].lson,l,mid,k)+tr[tr[u].rson].s;
  //在左边，先加上右边的值
	if(mid<k)
		ans+=ask(tr[u].rson,mid+1,r,k);
	return ans;
}
inline int read(){
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+c-'0';
		c=getchar();
	}
	return a*f;
}
main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	root[0]=build(1,n);
	for(int i=1;i<=n;i++){
		a[i]=min(read(),n);
		root[i]=sig(root[i-1],1,n,a[i]);//把a[i]放入桶
	}
	int ans=0;
	for(int i=2;i<=n;i++){//为什么不从i=1开始?因为i=1没有值
		int k=min(i-1,a[i]);
		ans+=ask(root[k],1,n,i);
	}
	printf("%lld\n",ans);
	return 0;
}

```
完结撒花~

---

## 作者：Milthm (赞：0)

有一些像这题这样的题，需要枚举两维，但可以把一维扔到数据结构里去，从而减少复杂度。

你考虑一个这样的算法：枚举 $i$，把 $i$ 自己和满足 $a_j\lt i$ 的 $j$ 全都删掉。这样只需要去满足 $a_i\ge j$，所以没被删除的数中下标小于等于 $a_i$ 的就是答案。

但是这是 $O(n^2)$ 做法，想想怎么去优化它。

枚举 $i$ 大概率优化不掉。这个“满足 $a_j\lt i$ 的 $j$ 全都删掉”每次都要重新找一遍答案，很废时间。考虑开一个新的数组，把 $a$ 排序之后的结果存进去。因为 $i$ 枚举是单调的，所以每次就不用找之前找过的了。

然后这个统计答案也要重新扫一遍，考虑开一个树状数组，每次删除就是把删除元素对应的位置的 $1$ 变成 $0$，查询直接查询前缀和即可。

最后有一点小技巧，发现元素可能很大，不过如果大于 $n$ 那么就比任何下标都大了，所以它的实际值再大也没有意义，直接改成 $n$ 就行。

时间复杂度 $O(n\log n)$。

### AC code

```cpp
#include<bits/stdc++.h>
#define int long long 
#define N 200005
using namespace std;
int n,a[N],c[N],now=1,vis[N],ans;
struct node{
	int x,id;
}b[N];
int cmp(node a,node b){
	return a.x<b.x; 
}
int read(){
	char c=getchar();int ans=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))ans=ans*10+c-'0',c=getchar();
	return ans;
}
void add(int x,int k){
	while(x<=n){
		c[x]+=k;x+=x&-x;
	}
}
int query(int x){
	int ans=0;
	while(x){
		ans+=c[x];x-=x&-x;
	}
	return ans;
}
signed main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=min(n,read()),b[i]={a[i],i},add(i,1);
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;++i){
		if(!vis[i])add(i,-1),vis[i]=1;
		while(now<=n&&b[now].x<i){
			if(!vis[b[now].id])add(b[now].id,-1),vis[b[now].id]=1;++now;
		}
		ans+=query(a[i]);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：ldj2006 (赞：0)

# CF961E Tufurama 题解

## 二维数点做法

## 题意

&emsp;&emsp;给定长度为 $n$ 的序列 $a$，统计二元组 $(i,j)$ 的个数，使得该二元组满足 $1 \leq i < j \leq n, a_i \geq j, a_j \geq i$。$n$ 在 $2 \times 10^{5}$ 级别，$a_i$ 在 $1 \times 10^{9}$ 级别。

## 思路分析

&emsp;&emsp;我们考虑把序列中 $n$ 个元素看成 $(i,a_i)$ 坐标的点，至于平面直角坐标系中。我们先忽略“$1 \leq i < j \leq n$”的条件。可以发现，对于某一个 $i$，我们要统计的是所有的 $j$ 中满足 $j \leq a_i, a_j \geq i$ 的点的个数，也就是横坐标小于等于当前点、纵坐标大于等于当前点的点的个数。画出图就是下面的样子：

![图片1](https://cdn.luogu.com.cn/upload/image_hosting/bfuknb52.png)

&emsp;&emsp;至于具体怎么处理数点过程，我们按照先横坐标再纵坐标的方式对于点排序。然后我们可以把每个询问 $(a_i,i)$ 做排序，代表查询横坐标小于等于 $a_i$，纵坐标大于等于 $i$ 的点的个数。我们横坐标从小到大一列一列地统计点（即一根扫描线在 x 轴上从小往大扫），用树状数组维护纵坐标上离散化过后的每个位置的已统计点的点数前缀和，统计纵坐标大于等于 $i$ 的区间内的点数，就可以知道对应的答案了。

&emsp;&emsp;那么我们怎么处理 $1 \leq i < j \leq n$ 的条件呢？首先我们考虑在的统计中，出现的 $i = j$ 的情况，可以发现，如果这样的情况被统计到了，（代入条件可得）就会满足 $a_i \geq i, a_i \geq i$，于是我们直接在序列上遍历统计 $a_i \geq i$ 的个数，在总统计答案中减掉就行。

&emsp;&emsp;然后就是 $i < j$ 的条件如何处理，我们发现 $a_i \geq j, a_j \geq i$ 和 $a_j \geq i, a_i \geq j$(即交换 $i,j$ 后)是等效的，也就是说每一个满足条件的点对被统计了两遍。于是我们在刚刚的基础上，把统计答案除以二，就得到了正确结果。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 5e5 + 5;
const int M = 5e5 + 5;

int n,m;
int a[N];
int ycnt;

int qcnt;
int yrk[N];

struct quest
{
	int x,y;
}que[N*2];

int ans[N];

bool cmp1(quest xx,quest yy)
{
	return xx.x < yy.x;
}

int t[N];

int lowbit(int xx)
{
	return xx & (-xx);
}

void add(int pos,int k)
{
	for(int i = pos;i <= ycnt;i += lowbit(i))
		t[i] += k;
}

int ask(int pos)
{
	int ans = 0;
	for(int i = pos;i >= 1;i -= lowbit(i))
		ans += t[i];
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	LL samecnt = 0;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
		if(a[i] >= i)
			samecnt++;
		yrk[i] = a[i];
		que[++qcnt] = {a[i],i};
	}
	sort(que+1,que+1+n,cmp1);
	sort(yrk+1,yrk+1+n);
	ycnt = unique(yrk+1,yrk+1+n)-1-yrk;
	int idx = 1;
	LL ans = 0;
	for(int i = 1;i <= n;i++)
	{
		while(idx <= que[i].x && idx <= n)
		{
			int tmpidx = lower_bound(yrk+1,yrk+1+ycnt,a[idx])-yrk;
			add(tmpidx,+1);
			idx++;
		}
		int tmpfd = lower_bound(yrk+1,yrk+1+ycnt,que[i].y)-yrk-1;
		ans += (LL)(ask(ycnt)-ask(tmpfd));
	}
	ans -= samecnt;
	ans /= 2;
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：david0911 (赞：0)

## 题意

给定长度为 $n$ 的序列 $a$，求有多少个有序对 $(i,j)$ 满足以下条件：

* $1 \le i <j \le n$

* $a_i \ge j$

* $i \le a_j$

## 做法

首先注意到 $i$ 应满足 $1 \le i \le \min (j-1,a_j)$，于是问题转化为求 $1$ 到 $\min (j-1,a_j)$ 之间有多少个数比 $j$ 大，显然可以使用主席树维护这个值。

## 细节

我们发现 $a_i$ 值域较大，由于统计时涉及值与下标的大小比较，离散化可能会改变统计结果，所以这里选择一种常用技巧：一边读入一边建树。

建树代码具体如下：

```cpp
for(int i=1;i<=n;++i){
	scanf("%d",&a[i]);
	rt[i]=update(rt[i-1],1,1e9,a[i]);
}
```

查询时可以枚举 $j$，算出 $i$ 的右边界，查询即可。由于 $1 \le i < j$，枚举时可以从 $2$ 开始。

查询代码具体如下：

```cpp
for(int i=2;i<=n;++i){
	int lim=min(i-1,a[i]); 
	ans+=1ll*query(rt[lim],1,1e9,i);
}
```

剩余部分便是主席树板子，此处不作讲解。

**AC Code**

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn=2e5+5;
int n,tp=0,a[maxn],rt[maxn];
long long ans=0;
struct TREE{
	int l,r,s;
}t[maxn<<5];

int clone(int p){
	int k=++tp;
	t[k]=t[p];
	t[k].s++;
	return k;
}

int update(int k,int l,int r,int v){
	k=clone(k);
	if(l==r){
		return k;
	}
	int mid=(l+r)>>1;
	if(v<=mid) t[k].l=update(t[k].l,l,mid,v);
	else t[k].r=update(t[k].r,mid+1,r,v);
	return k;
}

int query(int k,int l,int r,int v){
	if(!k) return 0;
	if(l==r) return t[k].s;
	int mid=(l+r)>>1;
	if(v<=mid) return t[t[k].r].s+query(t[k].l,l,mid,v);
	else return query(t[k].r,mid+1,r,v);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		rt[i]=update(rt[i-1],1,1e9,a[i]);
	}
	for(int i=2;i<=n;++i){
		int r=min(i-1,a[i]); 
		ans+=1ll*query(rt[r],1,1e9,i);
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：Gaode_Sean (赞：0)

对于这此类数列上的统计问题，显然可以用树状数组来解决。

按照常规思路，我们从 $1$ 到 $n$ 枚举 $j$，并对于每一个 $j$，排除满足 $a_i +1 \leq j$ 的 $i$（$1 \leq i-1 \leq j-2$）。

算法的具体流程是：

首先，建立起一个优先队列，队列中的元素为数列中的元素。

其次，按元素的输入顺序逐一扫描数列中的元素，设其为 $x$，并对优先队列中小于 $x$ 的元素执行 add 操作。

最后，对该元素进行 add 操作，并更新答案。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
typedef long long ll;
map<int,int> mp;
int n;
ll ans,c[N];
priority_queue< pair<int,int> > q;
ll ask(int x)
{
	ll res=0;
	for(;x;x-=x&(-x)) res+=c[x];
	return res;
}
void add(int x,ll y){for(;x<=n;x+=x&-x) c[x]+=y;}

int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		while(!q.empty()&&-q.top().first<i) add(q.top().second,-1),q.pop();
		ans+=ask(min(n,x)),add(i,1),q.push(make_pair(-x,i));
	}
	printf("%lld",ans);
	return 0;
}
```

---

