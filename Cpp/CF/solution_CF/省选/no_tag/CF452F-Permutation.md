# Permutation

## 题目描述

给你一个1到n的排列，你需要判断该排列内部是否存在一个3个元素的子序列(可以不连续)，使得这个子序列是等差序列。

## 样例 #1

### 输入

```
4
1 3 4 2
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5
1 5 2 4 3
```

### 输出

```
YES
```

# 题解

## 作者：破忆 (赞：11)

## 【题目大意】
给定n的一个排列，判断是否存在
$i<j<k,a[j]-a[i]=a[k]-a[j]$
## 【分析】
将题目转化

对于每个$a[i]$判断是否存在$k$,使得$a[i]-k$与$a[i]+k$序列上的位置在$i$的异侧

记录下每个数的状态，记$i$左边出现过的数状态为1，未出现过的数状态为0

若有解，则必定存在$k$,使得$a[i]-k$与$a[i]+k$状态不同，即这两个数序列上的位置在$i$的异侧

反之，若无解，对于任意$k$,都要满足$a[i]-k$与$a[i]+k$状态一致，即在总体状态上形成了以$a[i]$为中心的回文串

这样，只需判断以$i$为中心的状态串是否是回文串即可

可以用**线段树**+**哈希**解决
## 【算法】
线段树+哈希
## 【代码】
```cpp
#include<bits/stdc++.h>
#define ls (k<<1)
#define rs (k<<1|1)
#define mid (l+r>>1)
#define LL long long
using namespace std;
const int maxn=3e5+5,maxt=maxn<<2;
const int TT=1e9+7,bas=23;
int n;
int a[maxn];
LL pw[maxn];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
struct tree{
	LL val;
	int len;
	tree (const LL v=0,const int l=0){val=v,len=l;}
}ta[maxt],tb[maxt];//ta正向，tb反向
tree merge(tree l,tree r){
	tree ret;
	ret.val=(l.val*pw[r.len]%TT+r.val)%TT;
	ret.len=l.len+r.len;
	return ret;
}
void pushup(int k){
	ta[k]=merge(ta[ls],ta[rs]);
	tb[k]=merge(tb[rs],tb[ls]);
}
void update(int k,int l,int r,int x){
	if(l==r){
		ta[k]=tb[k]=tree(1,1);
		return;
	}
	if(x<=mid) update(ls,l,mid,x);
	else update(rs,mid+1,r,x);
	pushup(k);
}
tree query1(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y) return ta[k];
	if(y<=mid) return query1(ls,l,mid,x,y);
	if(mid<x) return query1(rs,mid+1,r,x,y);
	return merge(query1(ls,l,mid,x,mid),query1(rs,mid+1,r,mid+1,y));
}//这里tb与ta询问时遍历顺序相反，左右颠倒
tree query2(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y) return tb[k];
	if(y<=mid) return query2(ls,l,mid,x,y);
	if(mid<x) return query2(rs,mid+1,r,x,y);
	return merge(query2(rs,mid+1,r,mid+1,y),query2(ls,l,mid,x,mid));
}
void build(int k,int l,int r){
	if(l==r){
		ta[k]=tb[k]=tree(0,1);
		return;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
int main(){
	freopen("CF452F.in","r",stdin);
	freopen("CF452F.out","w",stdout);
	n=read();
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*bas%TT;
	build(1,1,n);
	for(int i=1;i<=n;i++){
		int x=read();
		update(1,1,n,x);
		int k=min(x-1,n-x);
		if(k<=0) continue;
		if(query1(1,1,n,x-k,x-1).val!=query2(1,1,n,x+1,x+k).val){
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
```

------------
感谢$ZZK$大佬的指导

---

## 作者：Aaron_Romeo (赞：8)

# 题意

给定 $n$ 的一个排列，判断是否存在 $i<j<k$， $a_j-a_i=a_k-a_j$ 的三元组。

其中 $n \le 3 \times 10 ^ 5$。

# 分析

我们现在称输出 yes 的序列为好序列，输出 no 的为坏序列。

考虑序列是坏的条件。

很容易想到，对任意 $1$ ~ $n$ 的数 $i$ 来说，$i - k$ 和 $i + k$ 是必须在 $i$ 的同一侧的。这其实就是一个坏序列的充要条件，但直接判是 $O(n ^ 2)$ 的，考虑发现一些更强的性质来优化。

~~不难发现~~，$i ± 1$ 与 $i ± 3$ 也都得在 $i$ 的同一侧。证明如下：

> 假设不在同一侧，不妨设 $i ± 1$ 在左，$i ± 3$ 在右。

> 若 $i - 1$ 在 $i + 1$ 前，则 $i - 1$，$i + 1$，$i + 3$ 构成三元组，则原序列是好的，矛盾。

> 若 $i + 1$ 在 $i - 1$ 前，则 $i + 1$，$i - 1$，$i - 3$ 构成三元组，则原序列是好的，矛盾。

同理我们可以推出，$i ± 1$，$i ± 3$，$i ± 5$ 也是在同一侧的：

> 假设不在同一侧，$i ± 5$ 在右，其余在左。

> 若要使得原序列是坏的，则需要满足：

> $i - 3$ 在 $i - 1$ 前，$i - 1$ 在 $i + 3$ 前，$i + 3$ 在 $i + 1$ 前，$i + 1$ 在 $i - 3$ 前。(这里省去步骤)

> 则推出 $i - 3$ 在 $i - 3$ 前，矛盾。

因此我们可以推出一个结论：$i ± k$ $(k$ 为奇数且 $1 \le i ± k \le n)$ 都是在 $i$ 的同一侧的。完整证明如下：

> 先使用归纳法，假设当前已经证明 $i ± 1$，$i ± 3$，$...$，$i ± (k - 2)$ 在同一侧。现在证明 $i ± k$ 也在同一侧。

> 再次假设不在同一侧，$i ± k$ 在右，其余在左。

> 对于在左的 $i ± x$：

> 对于 $i - x$ 与 $i - k$ 来说，$i - x$ 应在 $2(i - x) - (i - k)$ 之前，否则会形成三元组。

> 对于 $i + x$ 与 $i + k$ 来说，$i - x$ 应在 $2(i - x) - (i - k)$ 之前，否则会形成三元组。

> 若把这些条件连成边，则每个左边的点都会引出一条出边，且终点也在这个范围内。即这是一个基环树，则因为有环，所以矛盾。

> 证毕。

类似地，我们可以推出，对于固定的 $i$ 和 $a$，$i ± 2 ^ a \times k$ $(k$ 为奇数且 $1 \le i ± 2 ^ a \times k \le n)$ 都在同一侧。

现在我们来证明他是推出坏序列的充分必要条件：

> 首先他肯定是必要的，因为这是我们推出来的条件。

> 其次他显然是充分的，因为经过这些条件排除后，对于每一个 $i$，任何 $i ± k$ ( $1 \le i ± k \le n)$ 都不会出现在 $i$ 的两侧。

> 所以他是充分且必要的。

这个结论有什么用呢？

我们发现，$k$ 是一步一步往外扩展的，

![](https://cdn.luogu.com.cn/upload/image_hosting/1juffu2d.png)

所以他应该是一个前缀或后缀的形式。

![](https://cdn.luogu.com.cn/upload/image_hosting/mafz6tuk.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/nox0253g.png)

而我们要判断的相当于是，对于每个 $i$ 和 $a$，是否这些前缀或后缀上的数的下标是否 **都大于** 或 **都小于** $i$ 的下标，并且这些数都是 $\bmod \ 2 ^ {a + 1}$ 的同余类。

所以我们枚举 $a$，接着处理这些前缀与后缀上的数的 **下标的最大值和最小值**，然后进行判定即可。时间复杂度 $O(n\log n)$。

# Code

```cpp
#include <iostream>
const int N = 1e5;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1 ++ )
bool is_num(char ch) {return '0' <= ch && ch <= '9';}
char buf[1000000], *p1 = buf, *p2 = buf;
int read() {
	char ch;
	int f = 1;
	int x = 0;
	while (!is_num(ch = gc())) if (ch == '-') f = -1;
	do x = (x << 1) + (x << 3) + ch - '0'; while (is_num(ch = gc()));
	return f * x;
}
int pos[N + 5];
int mnpre[N + 5], mxpre[N + 5]; // 前缀下标最小与最大
int mnsuf[N + 5], mxsuf[N + 5]; // 后缀下标最小与最大
int main()
{
	int n = read();
	for (int i = 1; i <= n; i ++ ) pos[read()] = i; //每个数的下标
	for (int k = 2; k <= n; k *= 2) //枚举 2 ^ (a + 1)
	{
		for (int i = 1; i <= n; i ++ ) // 处理每个同余类的前缀的下标最小最大 
		{
			mnpre[i] = i <= k ? pos[i] : min(mnpre[i - k], pos[i]);
			mxpre[i] = i <= k ? pos[i] : max(mxpre[i - k], pos[i]);
		}
		for (int i = n; i >= 1; i -- ) // 处理每个同余类的后缀的下标最小最大
		{
			mnsuf[i] = i + k > n ? pos[i] : min(mnsuf[i + k], pos[i]);
			mxsuf[i] = i + k > n ? pos[i] : max(mxsuf[i + k], pos[i]);
		}
		for (int i = 1 + k / 2; i <= n - k / 2; i ++ ) // 枚举有贡献的 i 
		{
			int l = (i - k / 2 - 1) / k, r = (n - i - k / 2) / k; // 计算 k 往左和往右分别能扩展多少步 
			int max, min;
			if (l <= r) min = mnpre[i + k / 2 + k * l], max = mxpre[i + k / 2 + k * l]; // 如果 l <= r, 则是前缀
			else min = mnsuf[i - k / 2 - k * r], max = mxsuf[i - k / 2 - k * r]; // 否则是后缀
			if (min < pos[i] && pos[i] < max) {puts("yes"); return 0;} // 如果 i 被夹在这些数中间, 即这些数不在 i 的同一侧, 则原序列是好的 
		}
	}
	puts("no");
	return 0;
}
```

---

## 作者：SmileMask (赞：4)

## 0.前置芝士

- 线段树

- 哈希

## 1.题解

可能大家一开始看这道题有点蒙，不知道从哪里下手。

我们可以转化成这个问题：设 $x$ 为公差，那么我们就是求 $a_i-x$ 和 $a_i+x$ 是否在异侧。（即一数在左，一数在右）

我们考虑如何解决这个问题。

我们可以维护一个序列 $s$，每次把 $a_i$ 这个位置修改为 $1$。

然后判断 $s[a_i-x,a_i+x]$ 是否为回文串就行了，为什么呢？

因为设中心为 $a_i$，$a_i-x$ 为 $0$，$a_i+x$ 为 $1$ 的话，这样就形成不了一个回文串，而且 $a_i+x$ 出现过，$a_i-x$ 没出现过，这样就相当于 $a_i+x$ 在 $a_i$ 的左边，$a_i-x$ 在 $a_i$ 的右边，这样就形成了一个长度为 $3$ 的等差子序列。

单点修改，区间查询，你想到了什么？

**线段树**。

那么我们就可以用线段树维护这段区间的正反哈希值。
至于线段树如何写，代码里有。

## Code

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline int rd(){
	int num=0,sign=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') sign=-1; ch=getchar();}
	while (ch>='0'&&ch<='9') num=(num<<3)+(num<<1)+(ch^48),ch=getchar();
	return num*sign;
}
const int B=3;
const int mod=1e9+7;
const int N=3e5+7;
int n,f[N],b[N];
struct node{
	int l,r,h1,h2,len;
	node friend operator + (const node &a,const node &b){
		node ans;
		ans.l=a.l;ans.r=b.r;
		ans.len=ans.r-ans.l+1;
		ans.h1=(a.h1*f[b.len]%mod+b.h1)%mod;
		ans.h2=(b.h2*f[a.len]%mod+a.h2)%mod;
		return ans;
	}
}a[N<<2];
void build(int l,int r,int id){
	a[id].l=l;a[id].r=r;
	a[id].len=r-l+1;
	a[id].h1=a[id].h2=0;
	if(l==r) return ;
	int mid=(l+r)>>1;
	build(l,mid,id<<1);build(mid+1,r,id<<1|1);
}
void change(int pos,int id){
	if(a[id].l==a[id].r) return a[id].h1=a[id].h2=1,void();
	int mid=(a[id].l+a[id].r)>>1;
	if(pos<=mid) change(pos,id<<1);
	else change(pos,id<<1|1);
	a[id]=a[id<<1]+a[id<<1|1];
}
node query(int l,int r,int id){
	if(l<=a[id].l&&a[id].r<=r) return a[id];
	if(a[id<<1].r>=r) return query(l,r,id<<1);
	if(a[id<<1|1].l<=l) return query(l,r,id<<1|1);
	return query(l,r,id<<1)+query(l,r,id<<1|1);
}
signed main(){
	f[0]=1;
	for(int i=1;i<=N-7;i++) f[i]=f[i-1]*B%mod;
	n=rd();
	build(1,n,1);
	for(int i=1;i<=n;i++) b[i]=rd();
	for(int i=1;i<=n;i++){
		change(b[i],1);
		int x=min(b[i]-1,n-b[i]);
		if(query(b[i]-x,b[i],1).h1!=query(b[i],b[i]+x,1).h2&&i>=3){
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}

```


---

## 作者：Dilute (赞：4)

[$$\huge\texttt{在本人blog食用更佳}$$](http://dilute.xyz/2019/02/26/Solutions/Solution-CF452F/)

## 又双叒叕是题外话

今天模拟考是原题大战。

$T1$是这题。

$T2$是某次$CF\ Div1\ E$题。

$T3$反正是某道神仙题。

~~像我这样的菜鸡只能来做做**相对**可做的T1~~

~~虽然只是相对可做但是还是被全场切穿了啊喂~~

~~内心OS：这个不订正的理由真的nice~~

## 思路

我们看到题面要求求的三元组，然后瞎变形一下
$$a_j - a_i = a_k - a_i$$
$$a_i + a_k = 2 a_j $$
$$a_k = 2a_j - a_i$$
这样子，我们开始试图枚举$j$，之后我们就有一个美妙的性质

> 在$j$确定的情况下，对于一个$a_i$有对应的$a_j$可以组成三元组当且仅当
>
> - $2a_j - a_i$存在（废话）
> - $2a_j - a_i$与$a_j$在$a_i$的不同侧

（如果第二点看不懂可以直接看下面的进一步推导）

我们用$s_i$表示$i$这个数在$j$左边的位置有没有出现过

那么我们可以把上面的两点东西给弄出来，那么就是

$\forall\ 1 \leq 2a_j - a_i \leq n, s_{a_i} \neq s_{2a_j - a_i}$ 

变换一下，变成不能组成三元组的条件，那就是

$\forall\ 1 \leq 2a_j - a_i \leq n, s_{a_i} = s_{2a_j - a_i}$ 

表示在图上，那就可以画成这样↓

![](http://dilute.xyz/images/1.png)

（就是红色部分和绿色部分是对称的）
（反正这个意思感性理解一下）

好，然后我们接下来可以愉快地对$s$进行哈希了。

我们接下来考虑如何动态地维护$s$的哈希数组

现在的目标就是：资瓷单点修改和区间查询（正反都要）

实际上一个线段树就可以解决了

每个节点维护正反两个哈希值

就可以轻松写意地切掉此题。

这是我在模拟考时候写的代码，丑的一批。


## 代码实现

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647
#define mod 998244353
#define lc(a) (a << 1)
#define rc(a) (a << 1 | 1)
#define add(a, b) ((a) + (b) >= mod ? (a) + (b) - mod : (a) + (b))
#define minus(a, b) ((a) < (b) ? (a) - (b) + mod : (a) - (b))
#define mul(a, b) ((a) * (ll)(b) % mod)

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}
int a[300010];
int s[300010];
int powmod[300010];
struct SEG{
    int l;
    int r;
    int sum;
    int rev;

    SEG operator + (const SEG &b) const { // 为了方便查询的时候我把push_up给直接写成这种形式了
        if(l == -1)  // (SEG){-1, -1, -1, -1}  代表空的一段
            return b;
        if(b.l == -1)
            return (SEG){l, r, sum, rev};
        return (SEG){l, b.r, add(mul(sum, powmod[b.r - b.l + 1]), b.sum), add(mul(b.rev, powmod[r - l + 1]), rev)};
    }
};
struct SEG_Tree{
    SEG t[2400000];

    void push_up(int cur){
        t[cur] = t[lc(cur)] + t[rc(cur)];
    }

    void build(int cur, int l, int r){
        t[cur].l = l;
        t[cur].r = r;
        t[cur].sum = t[cur].rev = 0;
        if(l == r){
            t[cur].sum = t[cur].rev = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        build(lc(cur), l, mid);
        build(rc(cur), mid + 1, r);
        push_up(cur);
    }

    void modify(int cur, int pos, int c){
        if(t[cur].l == t[cur].r){
            t[cur].sum = t[cur].rev = c;
            return ;
        }
        if(pos <= t[lc(cur)].r)
            modify(lc(cur), pos, c);
        else
            modify(rc(cur), pos, c);
        push_up(cur);
    }

    SEG query(int cur, int l, int r){
        if(t[cur].l > r || t[cur].r < l)
            return (SEG){-1, -1, -1, -1};
        // printf("[%d, %d], query(%d, %d), {%d, %d}\n", t[cur].l, t[cur].r, l, r, t[cur].sum, t[cur].rev);
        if(t[cur].l >= l && t[cur].r <= r)
            return t[cur];
        return query(lc(cur), l, r) + query(rc(cur), l, r);
    }
}t;

int main(){
    int n = inp();
    for(int i = 1; i <= n; i++)
        a[i] = inp();
    powmod[0] = 1;
    for(int i = 1; i <= n; i++)
        powmod[i] = (powmod[i - 1] << 1) % mod;
    t.build(1, 1, n);
    bool flg = false;
    for(int i = 1; i <= n; i++){
        t.modify(1, a[i], 1);
        // printf("--------------------\na[i] = %d\n", a[i]);
        if((a[i] << 1) - 1 <= n){
            if(a[i] > 1 && t.query(1, 1, a[i] - 1).sum != t.query(1, a[i] + 1, (a[i] << 1) - 1).rev){
                flg = true;
                break;
            }
        } else {
            if(a[i] < n && t.query(1, a[i] + 1, n).rev != t.query(1, (a[i] << 1) - n, a[i] - 1).sum){
                flg = true;
                break;
            }
        }
    }
    if(flg){
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}
```



---

## 作者：peterwuyihong (赞：3)

题意：给一个排列，询问里面有没有三元连续子序列使得这个子序列是等差数列。

你看这个问题很油腻，于是你转化问题到值域上搞。

顺着扫，扫到一个数就记这个数的状态为 $1$，如果当前数是等差数列的中间项，由于是排列，那么旁边两项如果状态不同，那么他们的位置就在两侧，否则就在同侧。

如果发现了在两侧就直接输出 Yes 并进行一个路的跑，否则就继续下去，可以发现不符合当且仅当两边是回文的，选取一个牛逼的模数，用线段树维护哈希即可。

现在是 $14:06$，我看我什么时候写完。

现在是 $14:30$，我写完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<' '<<x<<endl
/* --------------- fast io --------------- */ // begin
namespace Fread {
const int SIZE = 1 << 26;
char buf[SIZE], *S, *T;
inline char getchar() {
	if (S == T) {
		T = (S = buf) + fread(buf, 1, SIZE, stdin);
		if (S == T) return '\n';
	}
	return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 26;
char buf[SIZE], *S = buf, *T = buf + SIZE;
inline void flush() {
	fwrite(buf, 1, S - buf, stdout);
	S = buf;
}
inline void putchar(char c) {
	*S++ = c;
	if (S == T) flush();
}
struct NTR {
	~ NTR() { flush(); }
} ztr;
} // namespace Fwrite
#ifdef ONLINE_JUDGE
	#define getchar Fread :: getchar
	#define putchar Fwrite :: putchar
#endif
namespace Fastio {
struct Reader {
	template<typename T>
	Reader& operator >> (T& x) {
		char c = getchar();
		T f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		x = 0;
		while (c >= '0' && c <= '9') {
			x = (x * 10 + (c - '0'));
			c = getchar();
		}
		x *= f;
		return *this;
	}
	Reader& operator >> (char& c) {
		c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		return *this;
	}
	Reader& operator >> (char* str) {
		int len = 0;
		char c = getchar();
		while (c == '\n' || c == ' ') c = getchar();
		while (c != '\n' && c != ' ') {
			str[len++] = c;
			c = getchar();
		}
		str[len] = '\0';
		return *this;
	}
	Reader(){}
} cin;
const char endl = '\n';
struct Writer {
	template<typename T>
	Writer& operator << (T x) {
		if (x == 0) { putchar('0'); return *this; }
		if (x < 0) { putchar('-'); x = -x; }
		static int sta[45];
		int top = 0;
		while (x) { sta[++top] = x % 10; x /= 10; }
		while (top) { putchar(sta[top] + '0'); --top; }
		return *this;
	}
	Writer& operator << (char c) {
		putchar(c);
		return *this;
	}
	Writer& operator << (char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer& operator << (const char* str) {
		int cur = 0;
		while (str[cur]) putchar(str[cur++]);
		return *this;
	}
	Writer(){}
} cout;
} // namespace Fastio
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl
/* --------------- fast io --------------- */ // end

#define maxn 300010
typedef unsigned long long ull;
int n;
ull pw[maxn];
struct prpr{
	int len;
	ull s;
	prpr(int ll=0,int ss=0):len(ll),s(ss){}
}t1[maxn<<2],t2[maxn<<2];
prpr operator+(prpr a,prpr b){
	return prpr(a.len+b.len,pw[b.len]*a.s+b.s);
}
void build(int l,int r,int x=1){
	t1[x].len=t2[x].len=r-l+1;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(l,mid,x<<1),build(mid+1,r,x<<1|1);
	t1[x]=t1[x<<1]+t1[x<<1|1];
	t2[x]=t2[x<<1|1]+t2[x<<1];
}
void change(int pos,int l=1,int r=n,int x=1){
	if(l==r){
		t1[x].s=t2[x].s=1;
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)change(pos,l,mid,x<<1);
	else change(pos,mid+1,r,x<<1|1);
	t1[x]=t1[x<<1]+t1[x<<1|1];
	t2[x]=t2[x<<1|1]+t2[x<<1];
}
prpr ask1(int x,int y,int l=1,int r=n,int o=1){
	if(x<=l&&r<=y)return t1[o];
	int mid=(l+r)>>1;
	prpr ans;
	if(x<=mid)ans=ask1(x,y,l,mid,o<<1);
	if(y>mid)ans=ans+ask1(x,y,mid+1,r,o<<1|1);
	return ans;
}
prpr ask2(int x,int y,int l=1,int r=n,int o=1){
	if(x<=l&&r<=y)return t2[o];
	int mid=(l+r)>>1;
	prpr ans;
	if(y>mid)ans=ask2(x,y,mid+1,r,o<<1|1);
	if(x<=mid)ans=ans+ask2(x,y,l,mid,o<<1);
	return ans;
}
int x,len;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n;pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*131;
	build(1,n);
	for(int i=1;i<=n;i++){
		cin>>x;
		change(x);
		len=min(x-1,n-x);
		if(len==0)continue;
		if(ask1(x-len,x-1).s!=ask2(x+1,x+len).s){
			cout<<"Yes";
			return 0;
		}
	}
	cout<<"No";
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}

```
我之前写的[Ynoi2011遥远的过去](https://www.luogu.com.cn/problem/P5310)上面的平衡树维护哈希不知道比它高到哪里去了，对于这些困难，还是小的很。

[P2757 [国家集训队]等差子序列](https://www.luogu.com.cn/problem/P2757)，一样的题。

[LOJ6287](https://loj.ac/p/6287)，一样的题。


---

## 作者：神光qwq (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF452F)

[双倍经验](https://www.luogu.com.cn/problem/P2757)

## 思维历程

首先考虑枚举中间数 $mid$ 和差值 $d$，但是复杂度一下就到平方级别，需要优化。

由于题目中给出的是 $1$ 到 $n$ 的排列，保证对于每个 $mid$ 和 $d$ 必然存在 $mid+d$ 和 $mid-d$，考虑一个转换，即判断二者是在 $mid$ 同侧或者异侧，进一步的用 $0$ 表示未出现，用 $1$ 表示已出现，若存在一组 $mid$ 和 $d$ 满足等差序列要求，其充要条件便是这个 $01$ 串不是一个回文串。

其他大佬想到 hash 而我这个蒟蒻只想到了二进制。

考虑线段树维护，对于每个数叶子就是维护出现与否，每个节点都是维护它叶子所组成的二进制值，上传操作时（此处表示正二进制值）左子树的值左移右子树 $01$ 串长度再加上右子树值。

对于回文串的判断直接采取正反二进制值表示的数值是否相等，此时（此处表示正二进制值）就是左子树的值左移右子树**访问的**相应 $01$ 串长度（不一定访问该子树内所有节点）。

**三个小坑点。**

- 左移应当先预处理为 $base$ 数组然后在后面直接相乘。
- 对于 $a[i]=1$ 或 $a[i]=n$ 应当直接跳过。
- 开 long long。

~~本人拙见，如有差错，请赐教。~~
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define void inline void
#define ls rt<<1
#define rs rt<<1|1
#define L t[rt].tl
#define R t[rt].tr
using namespace std;
const ll N=5e5+10,mod=1e9+7;
ll n,flag,maxn,minn,a[N],base[N+10];
struct node{
	ll tl,tr,sum[2],depth;
}t[N<<2];
inline ll read(){
	char ch=getchar();ll res=0,f=1;
	while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}
void init(){
	base[0]=1;
	for(ll i=1;i<=N;i++)
		base[i]=base[i-1]*2ll%mod;
}
void pushup(ll rt){
	t[rt].sum[0]=((t[ls].sum[0]*base[t[rs].depth])+t[rs].sum[0])%mod;
	t[rt].sum[1]=((t[rs].sum[1]*base[t[ls].depth])+t[ls].sum[1])%mod;
}
void build(ll rt,ll l,ll r){
	t[rt].tl=l,t[rt].tr=r;
	if(l==r){t[rt].depth=1,t[rt].sum[0]=t[rt].sum[1]=0;return ;}
	ll mid=(l+r)>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	t[rt].depth=t[ls].depth+t[rs].depth;
	t[rt].sum[0]=t[rt].sum[1]=0;
}
void modify(ll rt,ll x){
	if(L==R){t[rt].sum[0]=t[rt].sum[1]=1;return ;}
	ll mid=(L+R)>>1;
	if(x<=mid) modify(ls,x);
	else modify(rs,x);
	pushup(rt);
}
inline ll query(ll rt,ll l,ll r,ll k){
	if(l<=L&&R<=r) return t[rt].sum[k];
	ll mid=(L+R)>>1,dr=max(mid-max(l,L)+1,0ll),dl=max(min(r,R)-mid,0ll),res=0;
	if(!k){
		if(l<=mid) res+=(query(ls,l,r,k)*base[dl])%mod;
		if(mid<r) res+=query(rs,l,r,k)%mod;
	}
	else{
		if(l<=mid) res+=query(ls,l,r,k)%mod;
		if(mid<r) res+=(query(rs,l,r,k)*base[dr])%mod;
	}
	return res%mod;
}
int main(){
	init();n=read(),flag=0;build(1,1,n);
	for(ll i=1;i<=n;i++) a[i]=read();
	for(ll i=2;i<n;i++){
		modify(1,a[i-1]);
		if(a[i]==1||a[i]==n) continue;
		ll len=min(a[i]-1+1,n-a[i]+1);//防止非法访问
		if(query(1,a[i]-len+1,a[i]-1,0)!=query(1,a[i]+1,a[i]+len-1,1)){
			printf("YES\n"),flag=1;
			break;
		}
	}
	if(flag==0) printf("NO\n");
	return 0;
}

```


---

## 作者：louhao088 (赞：2)

树状数组 $+$ HASH


------------

首先，我们很容易得到一个 $O(n^2)$ 的做法，枚举前 2 个数，然后判断后面有没有存在第 3 个数。


------------

考虑怎么对其进行优化。考虑枚举中间的一个数，如果前后存在一个与其差相同的数，那么则有解。

这个东西怎么快速判断是否存在呢？这个不是很好判断，我们考虑判断什么时候没有解。如果我们建出关于某个数之前数的权值线段树的话，那么其应是关于这个数对称的。

具体的，我们可以用 树状数组 $+$ HASH 的方法判断是否对称。具体的，建两个树状数组，一个记录从前往后的 Hash， 另一个记录从后往前的，每枚举一个数，就往树状数组中加值。


------------

复杂度 $O(n \log n)$。





------------
代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define lowbit(x) (x&-x)
const int maxn=5e5+5,M=34005,mod=1e9+7,mod2=998244353;
inline int read(){
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x){
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,a[maxn];
struct Hash{
	int x,y;
	Hash(int a=0,int b=0){x=a,y=b;}
	Hash operator + (const Hash &a)const{return Hash((x+a.x)%mod,(y+a.y)%mod2);}
	Hash operator - (const Hash &a)const{return Hash((x-a.x+mod)%mod,(y-a.y+mod2)%mod2);}
	Hash operator * (const Hash &a)const{return Hash(1ll*x*a.x%mod,1ll*y*a.y%mod2);}
	bool operator ==(const Hash &a)const{return x==a.x&&y==a.y;}
}base,fac[maxn];
struct BIT{
	Hash c[maxn];
	void add(int x,Hash num){for(int i=x;i<=n;i+=lowbit(i))c[i]=c[i]+num;}
	Hash query(int x){Hash res;for(int i=x;i;i-=lowbit(i))res=res+c[i];return res;}
}T1,T2;
bool check(int l,int r,int l2){
	Hash a=T1.query(r)-T1.query(l-1);
	Hash b=T2.query(l2)-T2.query(r-1);
	b=b*fac[r];a=a*fac[n-r+1];
	if(a==b)return 0;return 1;
}
signed main(){
	n=read();fac[0]=Hash(1,1);base=Hash(197,233);
	for(int i=1;i<=n;i++)a[i]=read(),fac[i]=fac[i-1]*base;
	for(int i=1;i<=n;i++){
		T1.add(a[i],fac[a[i]-1]);T2.add(a[i],fac[n-a[i]]);
		int z=min(a[i]-1,n-a[i]);
		if(check(a[i]-z,a[i],a[i]+z)){puts("YES");exit(0);}
	}puts("NO");
 	return 0;
}


```



---

## 作者：Martian148 (赞：2)

# Link
[CF452F Permutation](https://www.luogu.com.cn/problem/CF452F)

# Solve

先转化一下题意，对于一个$a[i]$我们判断如果存在一个$a[i]+k$和$a[i]-k$在$a[i]$的异侧，那么就存在一个解，输出$yes$，如果对于每个$a[i]$都不存在，就输出$no$。

如何判断是否存在$a[i]+k$和$a[i]-k$的位置，我们想到了回文，处理每个$a[i]$时，我们把$a[i]$这个位置打上$1$，如果此时的序列不是以$a[i]$为中心的回文，那么肯定有一个对应的$a[i]+k$或者$a[i]-k$在$a[i]$后面，就存在解了，如果是回文，那么对于这个$a[i]$每一个k，$a[i]+k$和$a[i]-k$都在$a[i]$同侧了。

如何维护回文，很容易的想到**线段树+哈希**，一个回文串，正着哈希和反过来哈希的结果是一样的，我们就建两棵线段树，一棵表示正着哈希，一棵表示反着哈希，反着哈希的树统计时就把左儿子和右儿子交换就好了，相当于把线段树做了一次对称(这么说也不够严谨，感性理解一下就好了)。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5,TT=1e9+7,bas=27;
typedef long long LL;
int N,a[maxn];
LL pw[maxn];
struct node{
	LL val;
	int len;
	node(const LL v=0,const int l=0){val=v;len=1;}
}ta[maxn<<2],tb[maxn<<2];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
node merge(node l,node r){
	node ret;
	ret.val=(l.val*pw[r.len]%TT+r.val)%TT;
	ret.len=l.len+r.len;
	return ret;
}

void pushup(int k){
	ta[k]=merge(ta[k<<1],ta[k<<1|1]);
	tb[k]=merge(tb[k<<1|1],tb[k<<1]);
}

void update(int k,int l,int r,int x){
	if(l==r){
		ta[k]=tb[k]=node(1,1);
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid)update(k<<1,l,mid,x);
	else update(k<<1|1,mid+1,r,x);
	pushup(k);
}

node query1(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y)return ta[k];
	int mid=r+l>>1;
	if(y<=mid)return query1(k<<1,l,mid,x,y);
	if(mid<x)return query1(k<<1|1,mid+1,r,x,y);
	return merge(query1(k<<1,l,mid,x,mid),query1(k<<1|1,mid+1,r,mid+1,y));
}

node query2(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y)return tb[k];
	int mid=r+l>>1;
	if(y<=mid)return query2(k<<1,l,mid,x,y);
	if(mid<x)return query2(k<<1|1,mid+1,r,x,y);
	return merge(query2(k<<1|1,mid+1,r,mid+1,y),query2(k<<1,l,mid,x,mid));
}

void build(int k,int l,int r){
	if(l==r){
		ta[k]=tb[k]=node(0,1);
		return ;
	}
	int mid=r+l>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	pushup(k);
}

int main(){
	freopen("CF452F.in","r",stdin);
	freopen("CF452F.out","w",stdout);
	N=read();
	pw[0]=1;
	for(int i=1;i<=N;i++)pw[i]=pw[i-1]*bas%TT;
	build(1,1,N);
	for(int i=1;i<=N;i++){
		int x=read();
		update(1,1,N,x);
		int k=min(x-1,N-x);
		if(k<=0) continue;
		if(query1(1,1,N,x-k,x-1).val!=
		query2(1,1,N,x+1,x+k).val){
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
```

---

## 作者：水库中的水库 (赞：2)

推荐一下[我的博客](http://ljf-cnyali.cn/2019/09/08/CF452F-%E7%BA%BF%E6%AE%B5%E6%A0%91-Hash/)

这道题有一道一样的题[LuoguP2757](https://www.luogu.org/problem/P2757)，但那道题可以 $O(n^2)$ 水过去

首先提一个 $Hash$ 的技巧，假设有

$$\begin{aligned}&Hash_1=p\times a_1\\&Hash_2=Hash_1+p^2\times a_2\\&\dots\end{aligned}$$

假设我们要求 $a_x\dots a_y$ 的 $Hash$ 的值，可以用上面的 $Hash_i$ 的到

即值为 $Hash_y-Hash_x\times p^{y-x}$

再接着考虑这道题，首先保证了这个序列是 $1\rightarrow n$ 的排列，所以每一个数当且仅当出现一次

假设当前考虑到第 $i$ 个数字，值为 $a_i$ ，那么如果 $a_i$ 作为一个等差数列的中间值的话，应满足 $a_j<a_i$ 且 $a_j$ 已经在 $i$ 之前出现过， $2a_i-a_j$ 还未出现

可以使用一个 $bool$ 数组转化一下这个要求，设 $b_i$ 表示 $i$ 这个值是否出现过

那么如果 $a_i$ 不可能作出贡献当且仅当从以 $i$ 为中心的 $b$ 串是一个回文串，即任意 $x$ 都满足 $b_{a_i-x}=b_{a_i+x}$

那么就使用之前提到的 $Hash$ 来判断是否为回文串，因为要动态更新，用线段树或树状数组维护一下即可

```c++
/***************************************************************
	File name: CF452F.cpp
	Author: ljfcnyali
	Create time: 2019年09月08日 星期日 15时14分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 300010;
const int Mod = 103;

int n, a[maxn], p[maxn];
struct node
{
    int val;
} Tree[maxn << 2][2];

inline int Query(int root, int l, int r, int L, int R, int k)
{
    if ( L <= l && r <= R ) return Tree[root][k].val;
    int Mid = l + r >> 1, sum = 0;
    if ( L <= Mid ) sum += Query(lson, l, Mid, L, R, k);
    if ( Mid < R ) sum += Query(rson, Mid + 1, r, L, R, k);
    return sum;
}

inline void PushUp(int root, int k)
{
    Tree[root][k].val = Tree[lson][k].val + Tree[rson][k].val;
}

inline void Modify(int root, int l, int r, int pos, int val, int k)
{
    if ( l == r ) { Tree[root][k].val = val; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val, k);
    else Modify(rson, Mid + 1, r, pos, val, k);
    PushUp(root, k);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    p[0] = 1; REP(i, 1, n) p[i] = p[i - 1] * Mod;
    REP(i, 1, n)
    {
        int len = min(a[i] - 1, n - a[i]);
        int s1 = a[i] - len, s2 = n - a[i] - len + 1;
        int x = Query(1, 1, n, s1, a[i], 0);
        int y = Query(1, 1, n, s2, n - a[i] + 1, 1);
        if ( s1 > s2 ) y = y * p[s1 - s2];
        else x = x * p[s2 - s1];
        // printf("%lld %lld\n", x, y);
        if ( x != y ) { puts("YES"); return 0; }
        Modify(1, 1, n, a[i], p[a[i]], 0);
        // printf("%lld %lld %lld %lld\n", a[i], p[a[i]], n - a[i] + 2, p[n - a[i] + 1]);
        Modify(1, 1, n, n - a[i] + 1, p[n - a[i] + 1], 1);
    }
    puts("NO");
    return 0;
}
```



---

## 作者：sgl654321 (赞：1)

### 题目大意
给定一个长度为 $n$ 的排列 $a$，请问 $a$ 中是否存在一个长度为 $3$ 的等差数列。

### 解题思路

首先，对于一个长度为 $3$ 的等差数列，显然有 $2b_2=b_1+b_3$。

容易想到枚举中间的 $b_2$，考虑是否存在 $b_1$ 与 $b_3$，满足它们的平均值为 $b_2$，并且在 $b_2$ 的两侧。

建立一个权值数组 $c$。从左往右扫描 $a$ 排列，扫到的元素 $a_x=b_2$。如果 $a_x=1$ 或者 $a_x=n$，那么显然不存在以 $a_x$ 为中项的等差数列了。

其余情况，我们把 $c_{a_i}(i\in[1,x-1])$ 都设置为 $1$，把 $c_{a_j}(j\in[x,n])$ 都设为 $0$。如果有一个以 $c_{a_x}$ 为中心的**非回文串**，那么就存在一个等差数列。这是因为左右两边的 $c_i$ 不相等，它们一定位于 $a_x$ 的两侧。


这样说起来比较绕，我们举一个例子：

例：$a=\{1,4,3,2\}$

- $x=1,a_x=1$，直接跳过。
- $x=2,a_x=4$，直接跳过。
- $x=3,a_x=3$。此时 $c=\{1,0,0,1\}$。以 $c_3$ 为中心的有一个 $\{c_2,c_3,c_4\}$，即 $\{0,0,1\}$。它不是回文串。因此，$2,3,4$ 三个数就在原排列中构成了一个等差数列。
- $x=4,a_x=2$。此时 $c=\{1,0,1,1\}$。以 $c_4$ 为中心的有一个 $\{c_1,c_2,c_3\}$，即 $\{1,0,1\}$。它是回文串。所以不存在以 $2$ 为中项的等差数列。


现在，我们就需要实现以下功能即可：

1. 把 $c_{a_x}$ 单点修改，从 $0$ 变成 $1$。
2. 判断是否存在以 $c_{a_x}$ 为中心的**非回文串**。

对于操作 $2$，我们直接判断 $c_{a_x}$ 为中心的最长的串就行了。因为如果串 $S$ 不是回文串，那么串 $ch_1+S+ch_2$ 也一定不是回文串。

如何快速判断一个串是否回文？哈希！我们正着求一遍哈希函数，反着求一边哈希函数，如果相等就是回文的。

而哈希函数是满足区间加法的。具体的，设一个字符串 $S$ 的 hash 值为 $H(S)$。若 $(S,len)=(S_1,len_1)+(S_2,len_2)$。那么有 $H(S)=H(S_1)\times base^{len_2}+H(S_2)$。大家可以想象成十进制数尝试一下。

所以总结起来，我们要实现的就是：单点修改，区间查询。线段树就呼之欲出了。

总结一下做法：

1. 从左到右扫描 $a_x$。
2. 找到以 $a_x$ 为中心的最长串 $S$。
3. 通过线段树的区间求和，求出 $S$ 正着和反着的 hash 值。如果不相等，那么存在等差数列，直接输出 ```YES```，然后退出。
4. 单点修改 $c_{a_x}$，将它从 $0$ 变成 $1$。

### 参考代码
我用 $t_1$ 维护正着的线段树，用 $t_2$ 维护倒着的线段树。

```cpp
#include<bits/stdc++.h>
#define base 2
#define mod 1145141919
typedef long long ll;
using namespace std;
struct node{
	long long l,r,sum;
}t[2][1200010];
long long tt,n,a[300010];
long long ps[2][300010],md,l1,r1,l2,r2,len,ans,num1,num2;
long long bas[300010];
bool flag;
void build(long long i,long long l,long long r,bool ff){
	t[ff][i].l=l;t[ff][i].r=r;
	t[ff][i].sum=0;
	if(l==r){
		ps[ff][l]=i;
		t[ff][i].sum=0;
		return;
	}	
	long long mid=(l+r)>>1;
	build(i*2,l,mid,ff);
	build(i*2+1,mid+1,r,ff);
}
void chaxun(ll i,ll l,ll r,ll ff){
	if(l<=t[ff][i].r&&r>=t[ff][i].l){
		if(l<=t[ff][i].l&&r>=t[ff][i].r){
			ans=(ans+t[ff][i].sum*bas[r-t[ff][i].r])%mod;
			return; 
		}
		chaxun(i*2,l,r,ff);
		chaxun(i*2+1,l,r,ff);
	}	
}
void xiugai(ll x,ll ff){
	ll now=ps[ff][x];
	t[ff][now].sum=1;
	while(now/2!=0){
		now/=2;
		t[ff][now].sum=(t[ff][now*2].sum*bas[t[ff][now*2+1].r-t[ff][now*2+1].l+1]
		+t[ff][now*2+1].sum)%mod;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	bas[0]=1;
	for(int i=1;i<=300005;++i)bas[i]=bas[i-1]*base%mod;
	cin>>n;
	flag=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n,0);
	build(1,1,n,1);
	for(int i=1;i<=n;i++){
		md=a[i];	
		len=min(a[i]-1,n-a[i]);
		l1=a[i]-len;r1=a[i]+len;
		len=2*len+1;//只要这个不是回文串就行了 [l,r]
		ans=0;chaxun(1,l1,r1,0);num1=ans;
		r2=n+1-l1;l2=n+1-r1;
		ans=0;chaxun(1,l2,r2,1);num2=ans;
		if(num1!=num2){
			flag=1;//非回文串 
			break;
		}
		xiugai(md,0);
		xiugai(n-md+1,1);
	}
	if(flag)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```

---

## 作者：OldDriverTree (赞：1)

线段树维护字符串哈希好题。

[双倍经验](https://www.luogu.com.cn/problem/P2757)

# 思路
如果一个长度为 $3$ 的等差序列的第二项为 $x$，公差为 $d$，那么第一项为 $x-d$，第二项为 $x+d$。

那么考虑维护一个 $01$ 序列：$a$，$a_i$ 表示在当前 $i$ 这个数在前面是否出现过，出现过为 $1$，否则为 $0$。

暴力做法就是先扫一遍 $a$ 序列，然后考虑等差序列的第二项 $x$ 为 $a_i$。再枚举公差 $d$，如果 $x-d$ 和 $x+d$ 中只有一个在前面出现过，那么 $x-d$ 和 $x+d$ 就在 $x$ 的两侧，返回存在等差序列。枚举完 $d$ 后记得再更新 $a$ 序列。

时间复杂度为 $O(n^2)$，显然会超时，考虑优化。

可以发现其实枚举 $d$ 并判断的过程就是比较 $a$ 序列的两个子段是否相等，显然可以用哈希优化。

再维护一个 正哈希值和反哈希值，扫 $a$ 序列时就判断前一段的正哈希值和后一段的反哈希值是否相等，如果不相等就返回存在等差序列。

由于还要再进行单点修改的操作，那么就可以用线段树来维护哈希值。

# Code
```cpp
#include<bits/stdc++.h>
#define L rt<<1
#define R rt<<1|1
using namespace std;
const int mod=1e9+7;
const int base=3;
const int N=4e5;
int n,power[N];

struct node //线段树
{
	int l,r,h1,h2; //h1：正哈希值，h2：反哈希值
	int mid() { return l+r>>1; }
	int len() { return r-l+1; }
	
	friend node operator +(node x,node y)
	{
		node z; z.l=x.l,z.r=y.r;
		z.h1=(1ll*x.h1*power[y.len()]%mod+y.h1)%mod;
		z.h2=(1ll*y.h2*power[x.len()]%mod+x.h2)%mod;
		return z;
	}
}T[N<<2];

void build(int rt,int l,int r) {
	T[rt].l=l,T[rt].r=r,T[rt].h1=T[rt].h2=0;
	if (l!=r) build(L,l,T[rt].mid()),build(R,T[rt].mid()+1,r);
}
void update(int rt,int pos) {
	if (T[rt].l==T[rt].r) T[rt].h1=T[rt].h2=1;
	else update(pos<=T[rt].mid()?L:R,pos),T[rt]=T[L]+T[R];
}
node query(int rt,int l,int r)
{
	if (l<=T[rt].l&&T[rt].r<=r) return T[rt];
	if (r<=T[rt].mid()) return query(L,l,r);
	if (T[rt].mid()<l) return query(R,l,r);
	return query(L,l,r)+query(R,l,r);
}
bool judge()
{
	for (int i=2,x,l;i<=n;i++) {
		scanf("%d",&x); l=min(x-1,n-x); // l 为公差最大的合法值
		if (l&&query(1,x-l,x-1).h1!=query(1,x+1,x+l).h2) return true;
		update(1,x); //更新 a 序列
	}
	return false;
}
int main()
{
	scanf("%d",&n); build(1,1,n); power[0]=1;
	for (int i=1;i<N;i++) power[i]=1ll*power[i-1]*base%mod;
	puts(judge()?"YES":"NO");
	return 0;
}
```

---

## 作者：Chthologist7507 (赞：1)

双倍经验：P2757 [国家集训队]等差子序列

**线段树+哈希**

~~我菜死了调了好久然后搞了半天才 AC，~~ 所以在代码中会提到一些坑点


## 分析

对于三元等差数列，有一个常见技巧就是枚举中值 $b=a_i$，然后找 $b-k,b+k$ 是否在同侧，如果在同侧就寄了，不在就赢了

如果暴力枚举 $b,k$ 那就是平方级别了，妥妥 TLE

考虑优化，对于枚举 $b$，无法优化，只能考虑优化 $k$ 的寻找

动态维护存在性 01 串，表示每一个数是否在左边出现，在右边是否出现，如果是回文串，那就寄了，因为一大一小全部集中在左侧或右侧，否则就赢了

如何快速判断回文？字符串哈希，如果正着的哈希等于反着的哈希，那么就回文

那么就是搞一个 $\log$ 级的动态维护哈希值的数据结构，考虑使用线段树，每个节点记录长度和正反哈希值

没了，思路就这么简单

## 代码

如果没有深入理解的话坑点会比较多，所以结合注释食用

```cpp
#include <bits/stdc++.h>
#define ll unsigned long long
#define inl inline
#define rep(i,a,b) for(int i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
const int N=5e5+10,mod=1e9+7,B=27;
struct Node{
	ll h1,h2;int l1,l2;
	Node(const ll v=0,const int l=0){h1=h2=v;l1=l2=1;}
}t[N<<2];//这里用了一个大结构体，h1,h2 是正反哈希值，l1,l2表示长度
int n,a[N],T;
ll p[N];
bool flag;
Node comp(Node x,Node y){
	Node tmp;
	tmp.h1=(x.h1*p[y.l1]%mod+y.h1)%mod;
	tmp.h2=(y.h2*p[x.l2]%mod+x.h2)%mod;//请注意 h2 表示反哈希，所以要相对于正哈希反着操作，要不然就 WA 16 pts
	tmp.l1=x.l1+y.l1;tmp.l2=x.l2+y.l2;
	return tmp;
}//合并操作，用于上传
namespace Tree{
	#define ls k<<1
	#define rs k<<1|1
	#define mid (l+r>>1)
	#define pushup(k) t[k]=comp(t[ls],t[rs])
	inl void update(int k,int l,int r,int x){
		if(x<l||x>r)return ;
		if(l==r){
			Node tmp;tmp.h1=tmp.h2=1;tmp.l1=tmp.l2=1;
			t[k]=tmp;
			return ;
		}
		update(ls,l,mid,x);update(rs,mid+1,r,x);pushup(k);
	}
	inl void build(int k,int l,int r){
		if(l==r){
			Node tmp;tmp.h1=tmp.h2=0;tmp.l1=tmp.l2=1;
			t[k]=tmp;
			return ;
		}
		build(ls,l,mid);build(rs,mid+1,r);pushup(k);
	}
	Node query(int k,int l,int r,int x,int y){
		if(x<=l&&y>=r)return t[k];
		if(y<=mid)return query(ls,l,mid,x,y);
		if(mid<x)return query(rs,mid+1,r,x,y);
		return comp(query(ls,l,mid,x,mid),query(rs,mid+1,r,mid+1,y));
	}
}
using namespace Tree;
signed main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T=1;//从 P2757 来的，其实跟 T 没关系（
	while(T--){
		// rep(i,1,N<<2)t[i].h1=t[i].h2=t[i].l1=t[i].l2=0;
		p[0]=1;flag=0;
		cin>>n;
		rep(i,1,n)p[i]=p[i-1]*B%mod;
		build(1,1,n);
		rep(i,1,n){
			int x;cin>>x;//不论是否找到了三元等差数列，都要读完（一上来因为这个寄了一发）
			if(flag)continue;
			update(1,1,n,x);
			int len=min(x-1,n-x);
			if(len<=0)continue;//不合法特判
			if(query(1,1,n,x-len,x-1).h1!=query(1,1,n,x+1,x+len).h2){//如果正哈希不等于反哈希，找到了
				cout<<"Y\n";flag=1;
			}
		}
		if(!flag)cout<<"N\n";
	}
}
```

完结撒花！

---

## 作者：QZJ666 (赞：0)

## 题意：

给定长度为 $n$ 的排列 $a$，判断其中是否存在长度为 $3$ 的等差数列。

## 做法：

对于这种 $3$ 个数的问题，我们考虑枚举中间的那个数，设我们枚举位置为 $i$，设公差为 $v$，只要我们可以在 $1$ 到 $i-1$ 中找到 $a_i-v$，在 $i+1$ 到 $n$ 中找到 $a_i+v$（或者反过来）就满足条件。

直接思考不是很好想，考虑将过程转化成 $01$ 序列，在我们枚举到第 $i$ 个点时，已经出现的数为 $1$，没有出现过的数为 $0$，相当于在序列的第 $a_i$ 个位置，若 $a_i-v$ 出现过且 $a_i+v$ 也出现过，或者都没有出现过时，因为 $a$ 是一个排列，所以 $a_i-v$ 和 $a_i+v$ 一定在 $i$ 的同侧，对于选的这一个 $v$ 无解。那么如果这个对于任意一个 $v$ 都无解的话，这个序列一定是以 $a_i$ 为中心对称的，也就是左边从左往右的序列和右边从右往左的序列相等。

判断序列相等？hash！

于是我们只需要维护从左往右和从右往左的哈希值，还要支持修改，于是用一个线段树来维护。时间复杂度$\mathcal{O}(n\log n)$


## 代码

```cpp
#include<bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;
const ull seed=233;
int n;
char a[300005];
ull ksm[300005];
struct node{
	int l,r;
	ull vl,vr;
}Tree[1200005];
void ztree(int p,int l,int r){
	Tree[p].l=l,Tree[p].r=r;
	if(l==r){
		Tree[p].vl=Tree[p].vr=(unsigned long long)a[l];
		return;
	}
	int mid=l+r>>1;
	ztree(p*2,l,mid);
	ztree(p*2+1,mid+1,r);
	Tree[p].vl=Tree[p*2].vl*ksm[r-mid]+Tree[p*2+1].vl;
	Tree[p].vr=Tree[p*2+1].vr*ksm[mid-l+1]+Tree[p*2].vr;
}
ull Getl(int p,int l,int r){
	if(l<=Tree[p].l&&Tree[p].r<=r)return Tree[p].vl;
	int mid=Tree[p].l+Tree[p].r>>1;
	ull vl=0,vr=0;
	if(l<=mid)vl=Getl(p*2,l,r);
	if(r>mid)vr=Getl(p*2+1,l,r);
	if(!vl)return vr;
	if(!vr)return vl;
	return vl*ksm[min(Tree[p*2+1].r,r)-mid]+vr;
}
ull Getr(int p,int l,int r){
	if(l<=Tree[p].l&&Tree[p].r<=r)return Tree[p].vr;
	int mid=Tree[p].l+Tree[p].r>>1;
	ull vl=0,vr=0;
	if(l<=mid)vl=Getr(p*2,l,r);
	if(r>mid)vr=Getr(p*2+1,l,r);
	if(!vl)return vr;
	if(!vr)return vl;
	return vr*ksm[mid+1-max(Tree[p*2].l,l)]+vl;
}
void update(int p,int l){
	if(Tree[p].l==Tree[p].r){
		Tree[p].vl=Tree[p].vr=(unsigned long long)a[l];
		return;
	}
	int mid=Tree[p].l+Tree[p].r>>1;
	if(l<=mid)update(p*2,l);
	else update(p*2+1,l);
	Tree[p].vl=Tree[p*2].vl*ksm[Tree[p].r-mid]+Tree[p*2+1].vl;
	Tree[p].vr=Tree[p*2+1].vr*ksm[mid-Tree[p].l+1]+Tree[p*2].vr;
}
int main(){
	scanf("%d",&n);
	ksm[0]=1;
	for(int i=1;i<=n;i++)a[i]='0',ksm[i]=ksm[i-1]*seed;
	ztree(1,1,n);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		if(x==1||x==n){
			a[x]='1';
			update(1,x);
			continue;
		}
		int lenl=x-1,lenr=n-x;
		if(lenl<lenr)lenr=lenl;
		else lenl=lenr;
		ull vl=Getl(1,x-lenl,x-1);
		ull vr=Getr(1,x+1,x+lenr);
		a[x]='1';
		update(1,x);
		if(vl!=vr){
			puts("yes");
			return 0;
		}
	}
	puts("no");
	return 0;
}
```

---

## 作者：Purslane (赞：0)

## Solution

这题出的很有想法啊 .

考虑枚举中间项 . 一个显然的想法是 , 挨个枚举左边的数 , 看右边有没有数能和中间数 , 左边数构成等差数列 . 可惜这是平方的 , 过不了 .

考虑优化 . 由于这是排列 , 右边出现等价于左边没有出现 .

所以扫描一下数组 , 每次判断是不是有可能与当前数构成等差数列的数都在左边出现了或都在右边出现了 . 

这又等价于 , 如果把桶 (权值线段树) 看做 $01$ 串 , 以当前这个数为中心对称 . 

哈希经典运用 . 注意开 `long long` .

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid (l+r>>1)
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10,MOD=1e9+7;
int n,a[MAXN],p[MAXN],val1[MAXN<<2],val2[MAXN<<2];
void update(int k,int l,int r,int pos) {
	if(l==r) return val1[k]=val2[k]=1,void();
	if(pos<=mid) update(k<<1,l,mid,pos); else update(k<<1|1,mid+1,r,pos);
	val1[k]=(val1[k<<1]*p[r-mid]%MOD+val1[k<<1|1])%MOD,val2[k]=(val2[k<<1|1]*p[mid-l+1]%MOD+val2[k<<1])%MOD;
	return ;
}
int query(int k,int l,int r,int x,int y,int op) {
	if(x<=l&&r<=y) return (op==1)?val1[k]:val2[k];
	if(y<=mid) return query(k<<1,l,mid,x,y,op); if(x>mid) return query(k<<1|1,mid+1,r,x,y,op);
	if(op==1) return (query(k<<1,l,mid,x,mid,op)*p[y-mid]%MOD+query(k<<1|1,mid+1,r,mid+1,y,op))%MOD;
	return (query(k<<1|1,mid+1,r,mid+1,y,op)*p[mid-x+1]%MOD+query(k<<1,l,mid,x,mid,op))%MOD;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;ffor(i,1,n) cin>>a[i];
	p[0]=1;ffor(i,1,n) p[i]=p[i-1]*2%MOD;
	ffor(i,1,n) {
		update(1,1,n,a[i]);
		int l=max(1ll,2*a[i]-n),r=min(n,2*a[i]-1);
		if(query(1,1,n,l,r,1)!=query(1,1,n,l,r,2)) return printf("YES"),0;
	}
	return printf("NO"),0;
}
```

---

