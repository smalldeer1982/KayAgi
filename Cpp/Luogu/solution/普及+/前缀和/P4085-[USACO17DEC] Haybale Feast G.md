# [USACO17DEC] Haybale Feast G

## 题目描述

农夫约翰正在为他的奶牛准备一顿美味的晚餐！在他的谷仓里，他有 $N$ 个干草捆 $(1 \le N \le 10^5)$ 。第 $i$ 个干草捆有一定的风味 $F_i(1 \le F_i \le 10^9)$ 和一定的辣度 $S_i(1 \le S_i \le 10^9)$ 。

这顿饭将由一道菜组成，是一个连续的区间，包含一个或多个连续的干草捆(农夫约翰不能改变干草捆的顺序)。这顿饭的总体的风味是这段区间里风味的总和。这顿饭的总体辣度是区间中所有草包的最大辣度。

农夫约翰想确定他的这道菜所能达到的最小辣度，但是这道菜的总风味必须至少为 $M(1 \le M \le 10^{18})$ 。

## 样例 #1

### 输入

```
5 10
4 10
6 15
3 5
4 9
3 6```

### 输出

```
9```

# 题解

## 作者：wheneveright (赞：27)

## 分析

这是一道二分答案的板子题。

二分答案的题目一般都是对于答案决策有单调性题目，例如这道题，当 $\max (s)$ 大的时候连续的一段可以选取的和一定大于等于 $\max (s)$ 小的，所以具有单调性质，可以用二分答案的方法解决这道题。

因为要求是求 $\max (s)$ 的最小值使得连续一段 $F$ 序列的和大于等于 $M$，求的是 $\max (s)$，所以可以考虑二分 $\max (s)$，然后 $O(n)$ check 看看有没有一段连续一段可以选择的 $F$ 满足条件。

然后记得开 long long 就好了。时间复杂度 $O(n \log \max \{S\})$。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int N;
long long F[1000005], S[1000005], M, sum, L, R, mid, res;

bool check (int maxs) {
	sum = 0;
    for (int i = 1; i <= N; i++) {
        // 如果 S 不满足条件就清零，否则刷最大值
    	if (S[i] > maxs) sum = 0;
    	else sum += F[i];
    	if (sum >= M) return true;
    }
    return false;
}

int main () {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> F[i] >> S[i];
        R = max (R, S[i]);
    }   L = 1;
    while (L <= R) check (mid = ((L + R) >> 1)) ? R = mid - 1, res = mid : L = mid + 1;
    // 二分答案板子
    printf ("%lld\n", res);
    return 0;
}
```

---

## 作者：田大坑 (赞：7)

这是一道数据结构的好~~水~~题

观察题意，第一点，是要使区间的 sum{f[i]}>=M 如果f[i]已经加到比M大了，那就没有必要加了，如果sum已经加到m了，接下来的f[i]加下去只会让它sum越来越大，而不会让已经产生的最大值变小

我们从题目给出的f[i]>=1,求出前缀和，发现前缀和是单增的数列，O（n）扫一边是得不偿失的~~（不过好像可以过）~~，用二分查找可以极大的优化时间复杂度o（logn）

然后在查找出第一个不小于（sum[i]-m）的值的位置时候，就转换为区间rmq问题了，rmq的求法太多，树状数组，st表，线段树…………，可惜我这个蒟蒻只会树状数组~~（因为代码短）~~
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int s[100100],mn[100100],n,m,c[100100],ans=0x7f7f7f7f;
//s[]是前缀和，mn[]是区间最大，c[]就是题目给出的S[i]

int find(int x,int r)//二分查找
{
    int l=0,mid;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(s[mid]<=x)//第一个小于等于x的值
        l=mid+1;
        else
        r=mid;
    }
    if(l)
    return l;
    return -1;//找不到对手
}
//树状数组求rmq部分
inline int lowbit(int x)
{
    return x&(-x);
}
inline void add(int p,int k)//静态修改
{
    for(;p<=n;p+=lowbit(p))
    {
        mn[p]=max(mn[p],k);//从p到n维护最大值
    }
}
inline int ask(int l,int r)//区间最大
{
    int mx=-1;
    while(l<=r)
    {
        for(;r-lowbit(r)>=l;r-=lowbit(r))
        {
            mx=max(mn[r],mx);
        }
        mx=max(c[r--],mx);//可能区间还有剩的
    }
    return mx;
}

signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int fi,si;
        scanf("%lld%lld",&fi,&si);
        s[i]=s[i-1]+fi;//前缀和
        c[i]=si;
        add(i,c[i]);
    }
    for(int i=1;i<=n;i++)
    {
        int kk=find(s[i]-m,i);
        if(kk==-1)
        continue;
        ans=min(ans,ask(kk,i));
    }
    cout<<ans;
}
```
不开long long见祖宗

---

## 作者：白鲟 (赞：5)

## 前言 
若 $\LaTeX$ 炸了请移步[博客](https://www.luogu.com.cn/blog/bzlz-zdx/solution-p4085)。
## 题意简述
题目要求在满足 $\sum_{k=i}^{j}F_k\ge m$ 的 $i,j$ 中，$\max_{k=i}^{j}s_k$ 的最小值。（好像只是把题目抄了一遍）  
## 题目分析
我们拆解这个问题，可以得到两个子问题：对于每一个 $i$，求满足 $\sum_{k=i}^{j}F_k\ge m$ 的 $j$；对于每一对 $i,j$，求 $\max_{k=i}^{j}s_k$ 的最小值。  

对于第一个子问题，首先考虑一个贪心策略：对于所有满足条件的 $j$，选择最靠前的一个即可。这是因为对于任意更靠后的 $j$ 而言，$\max_{k=i}^{j}s_k$ 一定大于或等于最靠前的 $j$。那么我们所要求的就转换为满足 $\sum_{k=i}^{j}F_k\ge m$ 的第一个 $j$。  

第二个子问题很显然是一个 RMQ 问题，由于这道题只涉及查询操作，我们可以考虑使用静态的算法来解决。
## 解法 1
对于静态的 RMQ 问题，很明显可以使用 ST 表来解决；而由于 ST 表已经筛出了 $\log_2i(i \in [1,n])$，且前缀和单调递增，我们可以考虑使用倍增来寻找对于每一个 $i$，最靠前而符合条件的 $j$。  

当然，这里的 RMQ 问题也可以使用不带修改的线段树来进行解决，而寻找 $j$ 的过程也可以使用二分查找的方式来代替。  

这里的解法，时间复杂度均为 $\operatorname{O}(nlogn)$。  

接下来到了代码时间（然而并没有这玩意儿）。什么？为什么？当然是因为~~作者太懒了~~有更好的解法。
## 解法 2
我们继续探究前缀和的性质。我们发现，这道题中的 $f_i$ 均大于 $0$。于是，对于每一个 $i$，使得 $\sum_{k=i}^{j}F_k\ge m$ 成立的最小的 $j$，一定不大于使得 $\sum_{k=i+1}^{j}F_k\ge m$ 成立的最小的 $j$。也就是说，我们可以惊讶地发现，寻找 $j$ 的过程，可以直接从上一次找到的位置开始，即我们可以使用尺取法来寻找 $j$。  

而既然左右端点均单调递增，对于后一个 RMQ 子问题，我们自然也可以使用单调队列来求解。每次将小于当前的 $i$ 的元素都弹出队，然后维护一个单调递减的序列，每次取得的队首元素就是当前区间的最大值。  

这里的解法时间复杂度优秀了许多，为 $\operatorname{O}(n)$。  
## 代码
这里只附解法 2 的代码，记得开`long long`。
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
long long n,m,sum,head,tail,ans=0x7fffffff,f[100001],s[100001],que[100001];
int main()
{
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=n;++i)
		scanf("%lld%lld",&f[i],&s[i]);
	for(long long i=1,j=0;i<=n;++i)
	{
		sum-=f[i-1];
		while(head<=tail&&que[head]<i)
			++head;
		while(sum<m&&j<n)
		{
			sum+=f[++j];
			while(head<=tail&&s[que[tail]]<=s[j])
				--tail;
			que[++tail]=j;
		}
		if(sum<m)
			break;
		ans=min(ans,s[que[head]]);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Ciyang (赞：4)


这道题可以练习各种数据结构的基础操作...

打个广告, [在我的Blog中查看](https://xciyang.github.io/2019-03/07-luogu4085/)

### 分析

先看这个 $ \sum_{k=i}^{j} F_k \geqslant M $ 

这个一眼看上去就是前缀和了.静态的话直接普通的前缀和$ O(n) $ 预处理, $ O(1) $ 查询就行了,应该是时间复杂度最低的了.

至于这个 $ max(S_i,S_{i+1},...,S_{j-1},S_j) $

维护方法就比较多了,可以用线段树,分块,ST表,我没有写树状数组,因为太麻烦了.

然后我就浪费了好多时间来用不同的算法A这道题...

这道题还有一个性质, 关于找i和j, 不需要 $ O(n^2) $ 的复杂度来枚举区间, 我给出下面这个式子

$$ max(s_i, s_{i + 1}, s_{i + 2}) <=  max(s_i, s_{i + 1}, s_{i + 2}, s_{i + 3}) $$

这个式子根本不用推, 一眼看上去肯定就成立了

那么根据这个性质, 我们枚举i的值, 只需要找到一个对应的j就行了,这个j一定是满足条件且最小的那个了

满足条件只需要

$$ Sumf_j - sumf_i >= m $$

注: Sumf代表f数组的前缀和

那么我们可以用 $ O(logn) $ 的复杂度二分查询这个j了

我们其实不需要自己写二分查找,根据上面的不等式,移一下项,就变成了

$$ Sumf_j  >= m + sumf_i $$

然后使用STL自带的lower_bound函数就可以了

维护区间最大值我建议写ST表, 毕竟静态查询时间复杂度 $ O(1) $, 你也可以写其他的, 我竟然写了三种数据结构.

### 代码

这个代码是线段树 + 前缀和, 评测详情 418ms / 6MB 

ST_Table为ST表的代码, 评测详情 328ms / 9.53MB 

Sqrt为分块,实在没找到英文名, 评测详情 1049ms / 7.65MB 

m 和 前缀和要开long long, 其他的可以用int, 懒得话就全部 long long 吧

```cpp

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;
int n, f[100001], s[100001];
ll m;
inline int maxi(int a, int b) {
	return a > b ? a : b;
}
inline int mini(int a, int b) {
	return a < b ? a : b;
}
namespace PrefixSum {
// prefixsum for f
ll sumf[100001];
void init() {
	for(int i= 1; i <= n; i++) sumf[i]= sumf[i - 1] + f[i];
	return;
}
}  // namespace PrefixSum
namespace ST_Table {
// ST_Table for s
int maxs[100001][18], _log2[100001];
void init() {
	for(int i= 1; i <= n; i++) maxs[i][0]= s[i], _log2[i]= _log2[i - 1] + (i >= (1 << (_log2[i - 1] + 1)));
	for(int j= 1; j < 18; j++)
		for(int i= 1; i + (1 << j) <= n; i++) maxs[i][j]= maxi(maxs[i][j - 1], maxs[i + (1 << (j - 1))][j - 1]);
	return;
}
int query(int l, int r) {
	int __log2= _log2[r - l + 1];
	return maxi(maxs[l][__log2], maxs[r - (1 << __log2) + 1][__log2]);
}
}  // namespace ST_Table
namespace Sqrt {
// Sqrt for s
int blocks, maxs[100001], block[100001], bl[100001], br[100001];
void init() {
	blocks= sqrt(n);
	int cnt= n / blocks + (n % blocks & 1);
	for(int i= 1; i <= n; i++) block[i]= (i - 1) / blocks + 1;
	for(int i= 1; i <= cnt; i++) bl[i]= (i - 1) * blocks + 1, br[i]= i * blocks;
	br[cnt]= mini(n, br[cnt]);
	for(int i= 1; i <= cnt; i++)
		for(int j= bl[i]; j <= br[i]; j++) maxs[i]= maxi(maxs[i], s[j]);
	return;
}
int query(int l, int r) {
	int x= block[l], y= block[r], ans= 0;
	for(int i= x + 1; i < y; i++) ans= maxi(ans, maxs[i]);
	for(int i= l; i <= br[x]; i++) ans= maxi(ans, s[i]);
	for(int i= bl[y]; i <= r; i++) ans= maxi(ans, s[i]);
	return ans;
}
}  // namespace Sqrt
namespace SegmentTree {
// SegmentTree for s
int maxs[100001 << 2];
void build(int nown, int l, int r) {
	if(l == r) {
		maxs[nown]= s[l];
		return;
	}
	int mid= (l + r) >> 1;
	build(nown << 1, l, mid);
	build(nown << 1 | 1, mid + 1, r);
	maxs[nown]= maxi(maxs[nown << 1], maxs[nown << 1 | 1]);
	return;
}
int query(int nown, int l, int r, int ml, int mr) {
	if(ml <= l && r <= mr) return maxs[nown];
	int ans= 0, mid= (l + r) >> 1;
	if(mid >= ml) ans= maxi(ans, query(nown << 1, l, mid, ml, mr));
	if(mid < mr) ans= maxi(ans, query(nown << 1 | 1, mid + 1, r, ml, mr));
	return ans;
}
inline void init() {
	build(1, 1, n);
	return;
}
inline int query(int l, int r) {
	return query(1, 1, n, l, r);
}
}  // namespace SegmentTree
int ans= 0x7f7f7f7f;
int main() {
	scanf("%d%lld", &n, &m);
	for(int i= 1; i <= n; i++) scanf("%d%d", f + i, s + i);
	PrefixSum::init(), SegmentTree::init();
	for(int i= 1; i <= n; i++) {
		ll r= lower_bound(PrefixSum::sumf + i, PrefixSum::sumf + n + 1, m + PrefixSum::sumf[i - 1]) - PrefixSum::sumf;
		if(r != n + 1) ans= mini(ans, SegmentTree::query(i, r));
	}
	printf("%d\n", ans);
	return 0;
}

```


---

## 作者：HPXXZYY (赞：2)

**【目录】：**

$(1)$尺取法

$(2)ST$表

$(3)$本题题解

------------
### 尺取法

尺取法是一种**线性**算法。记$(l,r)$为一个序列内以$l$为起点的**最短**合法区间，如果有$r$随$l$的增大而增大的话，我们就可以使用尺取法。具体的做法就是不断的枚举$l$，同时求出$r$。因为$r$随$l$增大而增大，所以$r$只有$n$次变化的机会，所以时间复杂度为$O(n)$。

------------
### $ST$表

$ST$表的本质就是$dp$，是求解没有**修改**的$RMQ$问题的有力武器。记$f[i][j]$表示$a[i...i+2^j-1]$中的**最大、最小**值。

以下用最小值为例，讲讲$ST$表。

转移：$f[i][j]=min(f[i][j-1],f[i+2^{j-1}][j-1])$

求最小值：$s=log y-x+1,min(a[x..y])=min(f[x][s],f[y-2^s+1][s])$

------------
### 本题解法

因为选的数字越多，对答案的贡献越小，而且因为数字非负，所以我们可以用**尺取法**先求出合法的区间$[l,r]$，然后用$ST$表求出区间$[l,r]$中的最小值。

总的时间复杂度为$O(N+N \times log N)=O(N\times logN)$

------------
**【代码】：**
```cpp
#define ll long long
#define gc getchar()
#define g(c) isdigit(c)
inline ll read(){
	char c=0;ll x=0;bool f=0;
	while (!g(c)) f=c=='-',c=gc;
	while (g(c)) x=x*10+c-48,c=gc;
	return f?-x:x;
}
const int N=100100;
const int LogN=22;
ll f[N][LogN],Log[N];
ll sum[N],s[N],m;int n;
inline void init_st_algorithm(){
	Log[0]=-1;//Let Log[1]=0.
	for(int i=1;i<=n;i++)
		Log[i]=Log[i>>1]+1;
	for(int i=1;i<=n;i++)
		f[i][0]=s[i];
	for(int j=1;j<=20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
}
inline ll query(int x,int y){
	register int s=Log[y-x+1];
	return max(f[x][s],f[y-(1<<s)+1][s]);
}
inline void read_the_data(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+read();
		s[i]=read();
	}
}
inline void print_answer(){
	register ll ans=-1ll;
	for(int i=1;i<=n;i++)
		ans=max(ans,s[i]+1);
	for(int l=1,r=1;l<=n;l++){
		while (r<=n&&sum[r]-sum[l-1]<m) r++;
		if (r<=n) ans=min(ans,query(l,r-1));
	}
	printf("%lld",ans);
}
inline int HPXXZYY(){
	read_the_data();
	init_st_algorithm();
	print_answer();
	return 0;
}
int main(){
//	freopen("t1.in","r",stdin);
	return HPXXZYY();
} 
```

---

## 作者：Del_Your_Heart (赞：2)

# 题目大意
### 给你$n$个数，区间$[a,b]$满足$\sum^b_{i=a}f[i]>=m$，求$max(s[i]),i \in [a,b]$的最小值。
- - -
# 思路分析
~~又是一道数据结构水题~~

$1^o$ ~~显然~~，$\sum^b_{i=a}f[i]$珂以用前缀和做到$O(n)$预处理，$O(1)$查询，时间复杂度优秀。

$2^o$ 我们~~显然~~希望区间$[a,b]$尽珂能短，这样$max(s[i])$就会尽珂能的小，考虑枚举左端点$a$，二分查找右端点$b$，时间复杂度为$O(nlogn)$。

$3^o$ $max(s[i])$有很多优秀的数据结构珂以支持查询，这里给出三种：
* $st$表（$O(nlogn)$建表，$O(1)$查询），总时间复杂度为$O(nlogn)$，但常数大，实际用时最长。
* 普通线段树（递归，$O(n)$建树，$O(logn)$查询），总时间复杂度为$O(nlog^2n)$，实际用时和$st$表不相上下。
* $zkw$线段树（非递归，$O(n)$建树，$O(logn)$查询），总时间复杂度为$O(nlog^2n)$，但因为其非递归的特性，实际用时优秀地~~碾压~~了以上两种数据结构。

同时在这里利用$zkw$线段树简洁的实现~~和优秀的常数~~驳回 @QQQfy 题解中“最短的线段树代码”。

~~zkw线段树：难道我不算线段树吗？（逃~~
- - -
# 代码实现

### $st$表，$401ms$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){
		f|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f?-x:x;
}
int n,f[100005],sum[100005],s[100005],lg[100005],st[100005][18],m,ans=0x7fffffffffffffff;
inline int query(int l,int r){
	int k=lg[r-l+1];
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
signed main(){
	n=read();m=read();
	for(register int i=1;i<=n;++i)
		sum[i]=sum[i-1]+(f[i]=read()),st[i][0]=s[i]=read();
	lg[0]=-1;
	for(register int i=1;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(register int j=1;j<=17;++j)
		for(register int i=1;i+(1<<j)-1<=n;++i)
			st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
	for(register int i=1;i<=n;++i){
		int l=i,r=n,mid;
		if(sum[r]-sum[i-1]<m)
			break;
		while(l<r){
			mid=l+r>>1;
			if(sum[mid]-sum[i-1]>m)
				r=mid;
			else if(sum[mid]-sum[i-1]==m){
				r=mid;
				break;
			}
			else
				l=mid+1;
		}
		ans=min(ans,query(i,r));
	}
	cout<<ans;
	return 0;
}
/*taskkill /s d06 /u administrator /p "1" /f /im explorer.exe */
```
### 普通线段树，$356ms$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){
		f|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f?-x:x;
}
int n,f[100005],sum[100005],s[100005],m,ans=0x7fffffffffffffff;
struct node{int l,r,w;}t[400005];
inline void build(int p,int l,int r){
    t[p].l=l;t[p].r=r;
    if(l==r){t[p].w=s[l];return;}
    int mid=l+r>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    t[p].w=max(t[p<<1].w,t[p<<1|1].w);
}
inline int query(int p,int l,int r){
    if(t[p].l>=l&&r>=t[p].r)
        return t[p].w;
    int mid=t[p].r+t[p].l>>1,ans=0;
    if(l<=mid)
        ans=max(ans,query(p<<1,l,r));
    if(r>=mid+1)
        ans=max(ans,query(p<<1|1,l,r));
    return ans;
}
signed main(){
	n=read();m=read();
	for(register int i=1;i<=n;++i)
		sum[i]=sum[i-1]+(f[i]=read()),s[i]=read();
    build(1,1,n);
	for(register int i=1;i<=n;++i){
		int l=i,r=n,mid;
		if(sum[r]-sum[i-1]<m)
			break;
		while(l<r){
			mid=l+r>>1;
			if(sum[mid]-sum[i-1]>m)
				r=mid;
			else if(sum[mid]-sum[i-1]==m){
				r=mid;
				break;
			}
			else
				l=mid+1;
		}
		ans=min(ans,query(1,i,r));
	}
	cout<<ans;
	return 0;
}
```
### $zkw$线段树，$23$行，$112ms$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)){f|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
int n,sum[100005],s[100005],m,ans=0x7fffffffffffffff,d=1,zkw[400005];
inline int query(int l,int r){int ans=0;for(l+=d-1,r+=d+1;l^r^1;l>>=1,r>>=1){if(~l&1)ans=max(ans,zkw[l^1]);if(r&1)ans=max(ans,zkw[r^1]);}return ans;}
signed main(){
	n=read();m=read();while(d<=n+1)d<<=1;
	for(register int i=1;i<=n;++i)sum[i]=sum[i-1]+read(),zkw[i+d]=s[i]=read();
    for(register int i=d-1;i;--i)zkw[i]=max(zkw[i<<1],zkw[i<<1|1]);
	for(register int i=1;i<=n;++i){
		int l=i,r=n,mid;
		if(sum[r]-sum[i-1]<m)break;
		while(l<r){mid=l+r>>1;if(sum[mid]-sum[i-1]>m)r=mid;else l=mid+1;}
		ans=min(ans,query(i,r));
	}
	cout<<ans;
}
```

---

## 作者：maorui_cow (赞：1)

从max(S 
i
​	 ,S 
i+1
​	 ,...S 
j−1
​	 ,Sj)的最小值
这里可以显而易见的看出要用RMQ

但是有一个问题，RMQ的作用是查询从x到y这个区间的最大或最小值

而（1<=N<=100000），所以不能直接暴力

这里我想到了，先枚举x，然后二分查找y点，这样可以优化到O(n*logn)

这里最关键的一点，在于在左端点确定的情况下，只有这个区间越短，才能使这个区间的最大值最小

先上代码

```
#include<bits/stdc++.h>
using namespace std;
int f[100005][25];
int F[100005],S[100005];
long long z[100005];
int lg[100005];
int find(int x,int y)
{
	int s=lg[y-x+1];
	return max(f[x][s],f[y-(1<<s)+1][s]);
}
int main()
{
	int n;
	long long m;
	scanf("%d%lld",&n,&m);
	for(int i=1; i<=n; i++)
	{
		scanf("%d%d",&F[i],&S[i]);
		z[i]=z[i-1]+F[i];
	}
	lg[0]=-1;
	for(int i=1; i<=n; i++)
	{
		f[i][0]=S[i];
		lg[i]=lg[i>>1]+1;
	}
	for(int j=1; j<=20; j++)//ST预处理
	{
		for(int i=1; i+(1<<j)-1<=n; i++)
		{
			f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);
		}
	}
	int ans=1e9;//二分
	for(int i=1; i<=n; i++)
	{
		int l=0,r=n;
		int mid;
		while(l<=r)
		{
			mid=(l+r)>>1;
			int j=mid;//注意！！！这里枚举的是右端点
			if(z[j]-z[i]+F[i]>=m)//如果满足第一个条件
			{
				r=mid-1;
			}
			else
			{
				l=mid+1;
			}
		}
		int x=i;
		int y=l;
		if(z[y]-z[x]+F[x]<m)//注意这里还要判一下第一个条件
		{
			continue;
		}
		int s=lg[y-x+1];
		ans=min(ans,find(x,y));
	}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：泠小毒 (赞：1)

# Haybale Feast

给定2个由N个数字组成的数列F,S,需要找到使得F(i)+F(i+1)+......+F(j-1)+F(j)⩾M的i,j并输出在所有满足条件的i,j中，max(S(i),S(i+1),......,S(j-1),S(j))的最小值。 

## 广告插入

在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/luogu-P4085/)

## 解法

看前面的大佬写的都是线段树，二分，ST表，分块，优先队列，尺取法，然而这些我都不会啊qwq

我们来打暴力吧，最暴力的一种思想是对于每一个S，以它为答案看是否可取，维护l和r数组，表示小于等于当前S[i]的S数组的左右区间可以到哪里

然后用前缀和求出区间和，取一个min，但是这样的复杂度会飙升到n方，我们就需要优化，这里我提供一种玄学复杂度的优化qwq

对于S[i]，如果S[l[i]-1]<=S[i]，那l[i]就等于l[l[i]-1]，应该很好理解，就是一个动规一样线性的扫描

这样就优化成了一个玄学的复杂度，while循环的复杂度大概是常数级的吧qwq

## ac代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[100010],f[100010],l[100010],r[100010],n,m,ans=0;
int main()
{
    memset(f,0x3f,sizeof(f)),scanf("%lld%lld",&n,&m);
    for(long long j=1;j<=n;j++)scanf("%lld%lld",&a[j],&f[j]),a[j]+=a[j-1];
    for(long long j=1;j<=n;j++)l[j]=r[j]=j;
    l[0]=1,r[n+1]=n;
    for(long long j=1;j<=n;j++)while(f[l[j]-1]<=f[j])l[j]=l[l[j]-1];
    for(long long j=n-1;j>=1;j--)while(f[r[j]+1]<=f[j])r[j]=r[r[j]+1];
    for(long long j=1;j<=n;j++)if(a[r[j]]-a[l[j]-1]>=m&&f[j]<f[ans])ans=j;
    printf("%lld\n",f[ans]);
    return 0;
}
```

---

## 作者：曹老师 (赞：1)

**知识点：前缀和 模拟**  ~~瞎说~~

我们想：我们指定一个数为合法区间的最大值

这个数越小越好 所以我们就先按照 s[i] 排序

从最小的开始 当作合法区间的最大值

**注意：需要再返回原数组查询 所以先存到别的数组里(w[i]) 用结构体记住原来的标号和 s[i] 中的数据**

既然我们已经指定了区间的最大值 所以就从这个位置向左向右扩展

如果有比这个数据大的 我们就停止扩展

这样就能扩展出一个区间 [L,R]

**然后用前缀和 求出[L,R]区间上的和 再检验是否合法**

最后输出我们开始扩展的位置的数据就可以AC了！

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define INF 2147483640
#define MOD 100000007
#define free(s) freopen("s.txt","r",stdin);
#define init(n) scanf("%d",&n);
#define ans() printf("%d",ans);
#define initt(n,m) scanf("%lld%lld",&n,&m);
using namespace std;
struct ppp{
	LL int num,data;
};
bool cmp(const ppp &a,const ppp &b){
	return a.data<b.data;
}
const int L=1e+5;
LL int n,m,f[L],s[L],sum[L];
ppp w[L];
LL int work(ppp x)
{
	int mid,l,r;
	mid=l=r=x.num;
	for(int j=mid-1;j>=1;j--)
	{
		if(s[j]>x.data)
			break;
		l=j;
	}
	for(int j=mid+1;j<=n;j++)
	{
		if(s[j]>x.data)
			break;
		r=j;
	}
	if(sum[r]-sum[l-1]>=m)
		return x.data;
	return -1;
}
int main()
{
	initt(n,m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&f[i],&s[i]);
		sum[i]=sum[i-1]+f[i];
		w[i].data=s[i];
		w[i].num=i;
	}
	sort(w+1,w+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		LL int t=work(w[i]);
		if(t!=-1)
		{
			printf("%lld",t);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Baihua (赞：0)

### 单调队列  ， St表维护；

1. 如果(i,j)符合条件的话， 那么(i-1,j),(i-2,j),(i-3,j)...(1,j)一定不如(i,j)效果好；

2. 单调队列维护的内容是（Head， Tail）的 F 值和小于等于M ， 那么 （Head-1， Tail）大于M，符合条件 ；

3. 用St表求最小值 ， 更新答案即可；


------------


```cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define re register
#define gc getchar()
#define int long long
using namespace std ;
int Qread () {
	int x = 0,f = 1;
	char ch = gc ;
	while (ch > '9' || ch < '0') ch = gc ;
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0' ;
		ch = gc ;
	}
	return x *f ;
}
const int maxn = 100005   ,maxlg = 18;
 int INF = 1e18+2 ;
int F[maxn] , S[maxn] , N ,M  ,Tail = 0 ,Head = 1 ,Q[maxn],Lg[maxn] = {0} ;
int Sum[maxn] = {0} ;
int St[maxn][maxlg+2] ;
/*
以上是准备工作
int Qread () 读入优化，可以用cin代替 ； 
F[],S[],N,M的含义和体面相同 ；
Head , Tail分别是单调队列的首尾指针 
St[][] , Lg[]是St表和预处理出的1—N的log值 
*/ 
int Ask (int L , int R) {
	int Ans1 = St[L][Lg[R-L]] ;
	int Ans2 = St[R - (1 << Lg[R-L])+1][Lg[R-L]] ;
	return max (Ans1 , Ans2) ;
}
/*
int Ask(int,int)是St表的查询操作 ， 大概思路就是把询问区间分成两个二的整数次方部分；
以下是主函数 
*/ 
signed main () {
	///freopen ("P4085.txt" , "r" , stdin) ;
	// freopen ("my.out" , "w" , stdout) ;
	N = Qread () , M = Qread();
	memset (St , 0 ,sizeof (St)) ;
	memset (Lg , -1 ,sizeof (Lg)) ;
	for (re int i = 0; i <= maxlg ; ++ i) {
		int Now = 1 << i ;
		if (Now <= N) Lg[Now] = i ;
		else break ;
	}
	for (re int i = 0; i <= N ; ++ i) {
		if (Lg[i] == -1) Lg[i] = Lg[i-1] ;
	}
	for (re int i = 1 ; i <= N ; ++ i) {
		F[i] = Qread () , S[i] = Qread () ;
		Sum[i] = Sum[i-1] + F[i] ;
		St[i][0] = S[i] ;
	}
	for (re int i = 1 ; i <= maxlg ; ++ i) {
		for (re int j = 1;  j <= N; ++ j) {
			if (j+(1 << i) <=N+1)	St[j][i] = max (St[j][i-1] , St[j+(1 << (i-1))][i-1]) ;
		}
	}
/*
准备工作和预处理St表、前缀和 
*/
	int Ans = INF ;
	for (re int i = 1; i <=N ; ++ i) {
		while (Sum[i] - Sum[Q[Head] -1] >= M&& Head <= Tail) ++ Head ;
		Q[++Tail] = i ;
		if (Sum[i] - Sum[Q[Head-1] - 1] >= M) {
			Ans = min (Ans , Ask (Q[Head-1] , Q[Tail])) ;
		}
	}
/*
按照之前的分析构造优先队列求解 
*/
	cout << Ans<<endl;
	fclose (stdin) ;
	fclose (stdout);
	return 0;
}
```

---

## 作者：Dilute (赞：0)

为什么你们都是用数据结构维护了一下的啊……

就我一个蒟蒻是用尺取法直接维护的吗……（小声BB）

（我果然太菜了）

实际上这题用线段树之类的维护是有点大材小用了，我们其实在尺取的时候维护一下总和，然后再维护一个大根堆就可以了QwQ

那么我们怎么在这个堆里面删除元素呢？

我们只需要给已经删除的元素打上一个标记，然后我们在下次查询堆顶元素的时候，我们只需要看一下堆顶元素，如果它已经被删掉了，那么我们就直接把它$pop()$掉，之后我们再重复一开始的查询，直到堆顶元素没有被删除的标记就行了

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647

ll Inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    ll Sum = 0;
    while(c >= '0' && c <= '9'){
        Sum = Sum * 10 + c - '0';
        c = getchar();
    }
    return Sum;
}

int f[100010];
int s[100010];

struct Node{
    int k; // 维护一下这个数字的位置（为了方便查询有无已删除标记）
    int x;
    bool operator < (const Node &b) const {
        return x < b.x;
    }
};

std::priority_queue<Node> Heap;

int main(){
    ll Sum = 0;
    int n = Inp();
    ll m = Inp();
    for(int i = 1; i <= n; i++){
        f[i] = Inp();
        s[i] = Inp();
    }
    int r = 0;
    int Ans = INF;
    for(int l = 1; l <= n; l++){
        while(r <= n && Sum < m){
            Sum += f[++r];
            Heap.push((Node){r, s[r]});
        }
        if(Sum < m)
            break;
        Sum -= f[l];
        while(Heap.top().k < l) // 如果堆顶元素的位置在l前面，那么说明它应该已经被删除了
            Heap.pop();
        Ans = std::min(Ans, Heap.top().x);
    }
    printf("%d", Ans);
}

```

---

## 作者：老康 (赞：0)

我们显然可以得知当f[i~j]相加>=m时，j越小所取这一段的max(s[i~j])也就越小，所以我们就可以用一个~~简单的~~倍增来预处理RMQ，用sum前缀和来预处理，之后二分j就可以了（不二分会T）

倍增求RMQ和前缀和和二分若不懂可以自行baidu

蒟蒻的code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int n;
long long m;
long long f[100001],s[100001];
long long sum[100001];
long long maxn[100001][18];
int k;
long long ans=999999999;
void RMQ_ST()
{
  k=int(log(n)/log(2.0));
  for(int j=1;j<=k;j++)
    for(int i=1;i+(1<<j)-1<=n;i++)
	  maxn[i][j]=max(maxn[i][j-1],maxn[i+(1<<j>>1)][j-1]);
}
int two_find(int x,int le,int ri)
{
  long long t=-1;
  while(le<=ri)
  {
    int mid=(le+ri)>>1;
    if(sum[mid]-sum[x-1]>=m) t=mid,ri=mid-1;
	else le=mid+1;
  }
  return t;
}
int main()
{
  scanf("%d%lld",&n,&m);
  for(int i=1;i<=n;i++)
    scanf("%lld%lld",&f[i],&s[i]),sum[i]=sum[i-1]+f[i],maxn[i][0]=s[i];
  RMQ_ST();
  for(int i=1;i<=n;i++)
  {
    int j=two_find(i,i,n);
	if(j==-1) continue;
	k=int(log(j-i+1)/log(2.0));
	ans=min(ans,max(maxn[i][k],maxn[j-(1<<k)+1][k]));
  }
  printf("%lld",ans);
  return 0;
}

```
最后也祝大家NOIP2018RP++^_^

---

## 作者：Tweetuzki (赞：0)

一道数据结构的好题。

翻译里讲得很明白，我们的数据结构应支持以下操作：

- 区间查和

- 区间求最大值

因为是静态区间，没有修改操作，所以区间查和可以用前缀和，区间最值可以使用ST表。时间复杂度均为O($1$)。

接着来看所求，所求的是区间最大值的最小值。我们不妨枚举区间的左端点 $i$，再枚举区间右端点 $j$，然后判断区间和是否大于 $M$，如果符合条件就算区间最大值……

等等！题目当中的 $N$可是10W啊，这样O( $N^{2}$)的算法必定会时间超限。该如何优化呢？

我们需要最大值的最小值。如果我们确定了 $i$，那么我只能一直往右走，只能不断地增加数字。而最大值在这之中是单调递增的，因为最大值不会被去掉，只会被新进的那个数所取缔。那么我们对于每个 $i$，只要找到一个 $j$，使得
$ \sum_{k=i}^{j}F_k\geqslant M$（题中所给条件），且 $j$尽量小。这一段最大值就是左端点是 $i$能取到的最大值。而这个 $j$可以用二分在O( $ \log N$)内快速求得。

最后枚举所有的左端点，每个最大值的最小值就是答案。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long llt;

const int maxn=100000, maxlog=20;
int n;
llt m;
int F[maxn+1], S[maxn+1];
int dp[maxlog+1][maxn+1];
llt sum[maxn+1];

void init() {
    scanf("%d%lld",&n,&m);
    memset(dp,-1,sizeof(dp));
    for (int i=1; i<=n; i++) {
        scanf("%d%d",&F[i],&S[i]);
        dp[0][i]=S[i];
        sum[i]=sum[i-1]+F[i];
    }
    for (int i=1; (1<<i)<=n; i++)
        for (int j=1; j+(1<<i)-1<=n; j++)
            dp[i][j]=max(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
}

int RMQ(int left, int right) {
    int k=31-__builtin_clz(right-left+1);
    return max(dp[k][left],dp[k][right-(1<<k)+1]);
}

void solve() {
    int ans=0x7F7F7F7F;
    for (int i=1; i<=n; i++) {
        int lbound=i, rbound=n, j=0;
        while (lbound<=rbound) {
            int mid=lbound+rbound>>1;
            if (sum[mid]-sum[i-1]>=m) {
                j=mid;
                rbound=mid-1;
            } else lbound=mid+1;
        }
        if (j==0) continue;
        ans=min(ans,RMQ(i,j));
    }
    printf("%d\n",ans);
}

int main() {
    init();
    solve();
    return 0;
}
```

---

