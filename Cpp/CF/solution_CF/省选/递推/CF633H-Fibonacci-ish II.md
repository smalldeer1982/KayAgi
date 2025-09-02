# Fibonacci-ish II

## 题目描述

Yash is finally tired of computing the length of the longest Fibonacci-ish sequence. He now plays around with more complex things such as Fibonacci-ish potentials.

Fibonacci-ish potential of an array $ a_{i} $ is computed as follows:

1. Remove all elements $ j $ if there exists $ i&lt;j $ such that $ a_{i}=a_{j} $ .
2. Sort the remaining elements in ascending order, i.e. $ a_{1}&lt;a_{2}&lt;...&lt;a_{n} $ .
3. Compute the potential as $ P(a)=a_{1}·F_{1}+a_{2}·F_{2}+...+a_{n}·F_{n} $ , where $ F_{i} $ is the $ i $ -th Fibonacci number (see notes for clarification).

You are given an array $ a_{i} $ of length $ n $ and $ q $ ranges from $ l_{j} $ to $ r_{j} $ . For each range $ j $ you have to compute the Fibonacci-ish potential of the array $ b_{i} $ , composed using all elements of $ a_{i} $ from $ l_{j} $ to $ r_{j} $ inclusive. Find these potentials modulo $ m $ .

## 说明/提示

For the purpose of this problem define Fibonacci numbers as follows:

1. $ F_{1}=F_{2}=1 $ .
2. $ F_{n}=F_{n-1}+F_{n-2} $ for each $ n&gt;2 $ .

In the first query, the subarray \[1,2,1\] can be formed using the minimal set {1,2}. Thus, the potential of this subarray is 1\*1+2\*1=3.

## 样例 #1

### 输入

```
5 10
2 1 2 1 2
2
2 4
4 5
```

### 输出

```
3
3
```

# 题解

## 作者：da32s1da (赞：20)

总有出题人喜欢出一些。。奇奇怪怪复杂度的东西。

正解是**莫队+线段树**，但是。。暴力也能过去。

模拟操作就好了嘛。

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=3e4+50;
int n,m,q,x;
struct node{
    int val,id;
    bool operator <(const node &o)const{return val<o.val;}
}a[N];
int Fib[N],l[N],r[N],Max[N],Now[N];
long long Ans[N];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i].val);
        a[i].id=i;
    }
    sort(a+1,a+n+1);
    //先按照大小 从小到大排序
	//这样对于每个区间就不用排序啦
	Fib[1]=Fib[2]=1;
    for(int i=3;i<=n;++i)Fib[i]=(Fib[i-1]+Fib[i-2])%m;
    //预处理Fib数列
    scanf("%d",&q);
    for(int i=1;i<=q;++i){
    	scanf("%d%d",&l[i],&r[i]);
    	Max[i]=-1;
	}
    //初始化每个区间的最大值
    //因为题目中有要求：删除重复数字
    for(int i=1;i<=n;++i){
    	x=a[i].val%m;
        //提前取模
        //这个优化十分重要！
        //下面如果是1ll*Fib[++Now[j]]*a[i].val，就会TLE
        //加上这个会在3500ms通过最大点
    	for(int j=1;j<=q;++j)
	    if(a[i].id>=l[j]&&a[i].id<=r[j]&&a[i].val!=Max[j]){
        	//在区间内，且不等于最大数字(即不重复)
	        Max[j]=a[i].val;
            //更新最大值
	        Ans[j]+=Fib[++Now[j]]*x;
            //加上答案
            //Now[j]表示第j个区间计算到Fib第几项
	    }
	}
    for(int i=1;i<=q;i++)printf("%lld\n",Ans[i]%m);
    //最后统一取模
}
```

---

## 作者：Honor誉 (赞：10)


我们这题先离散化并去重，然后我们考虑莫队。

考虑新加入一个数和删除一个数对答案产生的影响。

#### 加入一个数
我们如果这个数在序列中不是第一次出现，不用管他。

如果是第一次出现，权值线段树求的他的值和在排序去重后的斐波那契数列里的项的乘积。

我们要便于修改，所以我们要记录上一次和这一次的答案值，

比如说$(b,a+b)$,我们保存了$(a,b)$,我们就可以算出$(b,a+b)$,所以我们用一个$pre$和一个$now$,来保存上一个的乘积和这一个的乘积。然后答案就是$now[1]$。

删除一个数也是这样。
```cpp
void work(int hao,int l,int r,int x)
{
	if(l==r)
	{
		pre[hao]=now[hao]=0;
		return;
	}
	if(tag[hao])
	{
		down(hao);
	}
	int mid=(l+r)/2;
	if(x<=mid)
	{
		work(hao<<1,l,mid,x);
		make_tag(hao<<1|1,-1);//左边会对右边的排名产生影响
	}else{
		work(hao<<1|1,mid+1,r,x);
	}
	up(hao);
}
```

#### 删除一个数
我们如果这个数在序列中不是最后一次出现，不用管他。

我们像插入一样在权值线段树中修改即可。

#### 记得懒标记

```cpp
#include<bits/stdc++.h>
#define N 30010
using namespace std;
struct data
{
	int l,r,id1,id;
}q[N];
int b[N],a[N],pre[N<<2],now[N<<2],tag[N<<2],maxn,f[N*3],mod,n,id[N],cnt[N],num[N],p,ans[N];
bool cmp(int x,int y)
{
	return a[x]<a[y];
}
bool cmp1(data a,data b)
{
	if(a.id!=b.id)
	{
		return a.l<b.l;
	}
	return a.r<b.r;
}
void make_tag(int hao,int x)
{
	int xx=(1ll*pre[hao]*f[maxn+x-1]+1ll*now[hao]*f[maxn+x])%mod;//f[i-1]*f[c-1]+f[i]*f[c]=f[i+c]
	int yy=(1ll*pre[hao]*f[maxn+x]+1ll*now[hao]*f[maxn+x+1])%mod;
	tag[hao]+=x;
	pre[hao]=xx;
	now[hao]=yy;
}
void down(int hao)
{
	make_tag(hao<<1,tag[hao]);
	make_tag(hao<<1|1,tag[hao]);
	tag[hao]=0;
}
void up(int hao)
{
	pre[hao]=(pre[hao<<1]+pre[hao<<1|1])%mod;
	now[hao]=(now[hao<<1]+now[hao<<1|1])%mod;
}
void work(int hao,int l,int r,int x)
{
	if(l==r)
	{
		pre[hao]=now[hao]=0;
		return;
	}
	if(tag[hao])
	{
		down(hao);
	}
	int mid=(l+r)/2;
	if(x<=mid)
	{
		work(hao<<1,l,mid,x);
		make_tag(hao<<1|1,-1);//权值线段树左边会对右边产生影响，所以要懒标记记录 
	}else{
		work(hao<<1|1,mid+1,r,x);//而右边对于左边则不会 
	}
	up(hao);
}
void work1(int hao,int l,int r,int x)
{
	if(l==r)
	{
		pre[hao]=(1ll*id[x]*f[maxn+tag[hao]])%mod;
		now[hao]=(1ll*id[x]*f[maxn+tag[hao]+1])%mod;
		return;
	}
	if(tag[hao])
	{
		down(hao);
	}
	int mid=(l+r)/2;
	if(x<=mid)
	{
		work1(hao<<1,l,mid,x);
		make_tag(hao<<1|1,1);
	}else{
		work1(hao<<1|1,mid+1,r,x);
	}
	up(hao);
}
void del(int x)
{
	cnt[x]--;
	if(cnt[x]==0)//不是最后一个不理 
	{
		work(1,1,maxn,x);
	}
}
void sum(int x)
{
	cnt[x]++;
	if(cnt[x]==1)//不是第一个不理 
	{
		work1(1,1,maxn,x);
	}
}
int main()
{
	scanf("%d%d",&n,&mod);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=i;
	}
	sort(b+1,b+n+1,cmp);
	num[b[1]]=++maxn;//离散化 
	id[maxn]=a[b[1]];
	for(int i=2;i<=n;i++)
	{
		if(a[b[i]]!=a[b[i-1]])
		{
			maxn++;
		}
		num[b[i]]=maxn;
		id[maxn]=a[b[i]];
	}
	f[maxn+1]=f[maxn+2]=1;//预处理斐波那契 
	for(int i=maxn+3;i<=maxn*2;i++)
	{
		f[i]=f[i-1]+f[i-2]>=mod?f[i-1]+f[i-2]-mod:f[i-1]+f[i-2];
	}
	for(int i=maxn;i>=0;i--)
	{
		f[i]=f[i+2]-f[i+1]<0?f[i+2]-f[i+1]+mod:f[i+2]-f[i+1];
	}
	int kkk=sqrt(n);
	scanf("%d",&p);
	for(int i=1;i<=p;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=(q[i].l-1)/kkk;
		q[i].id1=i;
	}
	sort(q+1,q+p+1,cmp1);
	int ll=q[1].l,rr=q[1].l-1;
	for(int i=1;i<=p;i++)//莫队 
	{
		while(ll<q[i].l)
		{
			del(num[ll]);
			ll++;
		}
		while(rr<q[i].r)
		{
			rr++;
			sum(num[rr]);
		}
		while(ll>q[i].l)
		{
			ll--;
			sum(num[ll]);
		}
		while(rr>q[i].r)
		{
			del(num[rr]);
			rr--;
		}
		ans[q[i].id1]=now[1];
		while(ans[q[i].id1]<0)
		{
			ans[q[i].id1]+=mod;
		}
	}
	for(int i=1;i<=p;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}
```



---

## 作者：Implicit (赞：4)

### 如何纯正根号（详细揭秘）

令 $c_i$ 是 $i$ 的出现次数，$B$ 是阈值。

考虑把值域划分成若干段，使得每段 $[l,r]$ 满足下列两个条件之一：
- $l=r$ 且 $c_l>B$，这样的段最多 $O(n/B)$ 个。
- $\sum_{i=l}^rc_i\le 2B$，这样的段也可以划分到最多 $O(n/B)$ 个。

由于 $f_{x+y}=f_{x+1}f_y+f_xf_{y-1}$，那么假设某段中的数分别为 $a_{1\dots m}$，只需要算出 $\sum_jf_ja_j$ 和 $\sum_j f_ja_{j+1}$ 以及 $m$ 即可 $O(n/B)$ 拼出一个询问的答案。

对于第一种段只需要知道段里唯一的数在询问区间的存在性，莫队即可。

对于第二种段，由于总出现次数是 $O(B)$ 的，所以不同的贡献数是 $O(B^2)$ 的。维护只考虑值域 $[l,r]$ 时每种询问区间的答案，每次把值域分成两半递归进入，时间复杂度 $T(n)=2T(n/2)+O(n^2)=O(n^2)$。从而这部分的时间复杂度是 $O(B^2)$ 的。

总复杂度 $O(n\sqrt q)$。

---

## 作者：Genius_Z (赞：4)

莫队+线段树维护矩乘，复杂度$\Theta(T^3n\sqrt nlogn)$，也可以二次离线达到$\Theta(n\sqrt n)$的复杂度。

挺不错的题，除了卡常和放了暴力过去之外都挺好的，看到没有正解的题解，我就来发一发。

我们考虑加入一个数造成的影响，后面的数的矩阵都全部要乘以一个斐波那契递推的矩阵，我们考虑在权值线段树上维护，然后打上标记维护即可，细节挺多的，然后删除一个数就是后面的数乘一个逆矩阵即可。

因为本题卡常，所以离散化后立即取模，避免用$long long$，减少不必要的取模，尽量精简函数。

```cpp
#pragma region revive
#include <cstdio>
#include <iostream>
#include <algorithm>
#define inl inline
#define re register int
#define fa(x) fa[x]
#define son(x, y) t[x].child[y]
#define ls(x) child[x][0]
#define rs(x) child[x][1]
#define ll long long
const int inf = 0x3f3f3f3f;
const ll Linf = 0x3f3f3f3f3f3f3f3fLL;
#define lowbit(x) ((x) & (-x))
using namespace std;
#ifndef _DEBUG
#define getchar() (*(IOB.in.p++))
#define putchar(c) (*(IOB.out.p++) = (c))
#define io_eof() (IOB.in.p >= IOB.in.pend)
struct IOBUF {
	struct {
		char buff[1 << 27], *p, *pend;
	} in;
	struct {
		char buff[1 << 27], *p;
	} out;
	IOBUF() {
		in.p = in.buff;
		out.p = out.buff;
		in.pend = in.buff + fread(in.buff, 1, 1 << 27, stdin);
	}
	~IOBUF() { fwrite(out.buff, 1, out.p - out.buff, stdout); }
} IOB;
#endif
template <typename IO>
inl void write(IO x) {
	if (x == 0) return (void)putchar('0');
	if (x < 0) putchar('-'), x = -x;
	static char buf[30];
	char *p = buf;
	while (x) {
		*(p++) = x % 10 + '0';
		x /= 10;
	}
	while (p > buf)
		putchar(*(--p));
}
inl void writestr(const char *s) {
	while (*s != 0)
		putchar(*(s++));
}
template <typename IO>
inl void writeln(IO x) { write(x), putchar('\n'); }
template <typename IO>
inl void writesp(IO x) { write(x), putchar(' '); }
inl int readstr(char *s) {
	char *begin = s, c = getchar();
	while (c < 33 || c > 127) {
		c = getchar();
	}
	while (c >= 33 && c <= 127) {
		*(s++) = c;
		c = getchar();
	}
	*s = 0;
	return s - begin;
}
template <typename IO>
inl IO read() {
	IO x = 0;
	register bool w = 0;
	register char c = getchar();
	while (c > '9' || c < '0') {
		if (c == '-') w = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return w ? -x : x;
}
#pragma endregion
int s[30001], n, p, siz, mp[30001], a[30001], b[30001], cnt[30001];
ll ans[30001];
struct quiz {
	int l, r, id;
	bool operator<(const quiz& a)const {
		return s[l] == s[a.l] ? s[l] & 1 ? r<a.r : r>a.r : s[l] < s[a.l];
	}
}q[30001];
struct matrix {
	int a[2][2];
	matrix() { a[0][0] = 1, a[1][0] = a[0][1] = 0, a[1][1] = 1; }
	matrix(int x) {
		if (x == 1)a[0][0] = 1, a[1][0] = 1, a[0][1] = 1, a[1][1] = 0;
		else if (!x)a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;
		else a[0][0] = 0, a[0][1] = 1, a[1][0] = 1, a[1][1] = -1;
	}
	inl int* operator[](int x) { return a[x]; }
	inl const int* operator[](int x) const { return a[x]; }
	friend matrix operator*(const matrix &a, const matrix &b) {
		matrix c = matrix(0);
		for (re i = 0; i < 2; i++) {
			for (re j = 0; j < 2; j++) {
				for (re k = 0; k < 2; k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		for (re i = 0; i < 2; i++) {
			for (re j = 0; j < 2; j++) {
				c[i][j] %= p;
			}
		}
		return c;
	}
	friend matrix operator+(const matrix &a, const matrix &b) {
		matrix c = matrix(0);
		for (re i = 0; i < 2; i++) {
			for (re j = 0; j < 2; j++) {
				c[i][j] += a[i][j] + b[i][j];
			}
		}
		for (re i = 0; i < 2; i++) {
			for (re j = 0; j < 2; j++) {
				c[i][j] %= p;
			}
		}
		return c;
	}
	matrix operator*(int x) {
		for (re i = 0; i < 2; i++) {
			for (re j = 0; j < 2; j++) {
				a[i][j] = a[i][j] * x;
			}
		}
		for (re i = 0; i < 2; i++) {
			for (re j = 0; j < 2; j++) {
				a[i][j] %= p;
			}
		}
		return *this;
	}
	friend bool operator==(const matrix &a, const matrix &b) {
		for (re i = 0; i < 2; i++) {
			for (re j = 0; j < 2; j++) {
				if (a[i][j] != b[i][j])return 0;
			}
		}
		return 1;
	}
	friend bool operator!=(const matrix &a, const matrix &b) {
		return !(a == b);
	}
}E = matrix(), G = matrix(1), R = matrix(-1);
struct node {
	int w;
	matrix tag, ans;
}t[120001];
inl void upd(int k) {
	matrix a = t[k << 1].ans, b = t[k << 1 | 1].ans;
	if (t[k << 1].w != 1)a = a * t[k << 1].w;
	if (t[k << 1 | 1].w != 1)b = b * t[k << 1 | 1].w;
	t[k].ans = a + b;
}
inl void build(int k, int l, int r) {
	t[k].w = l != r;
	if (l == r)return (void)(t[k].ans = G);
	re mid = l + r >> 1;
	build(k << 1, l, mid), build(k << 1 | 1, mid + 1, r);
	upd(k);
}
inl void mul(int k, matrix w) {
	t[k].ans = t[k].ans*w, t[k].tag = t[k].tag*w;
}
inl void pushdown(int k) {
	if (t[k].tag != E) {
		mul(k << 1, t[k].tag), mul(k << 1 | 1, t[k].tag);
		t[k].tag = E;
	}
}
inl void insert(int k, int l, int r, int p) {
	if (l == r) return (void)(t[k].w = mp[p]);
	pushdown(k);
	re mid = l + r >> 1;
	if (p <= mid)insert(k << 1, l, mid, p), mul(k << 1 | 1, G);
	else insert(k << 1 | 1, mid + 1, r, p);
	upd(k);
}
inl void erase(int k, int l, int r, int p) {
	if (l == r) return (void)(t[k].w = 0);
	pushdown(k);
	re mid = l + r >> 1;
	if (p <= mid)erase(k << 1, l, mid, p), mul(k << 1 | 1, R);
	else erase(k << 1 | 1, mid + 1, r, p);
	upd(k);
}
inl void add(int x) {
	if (!cnt[x]++) insert(1, 1, siz, x);
}
inl void del(int x) {
	if (!--cnt[x]) erase(1, 1, siz, x);
}
signed main() {
	n = read<int>(), p = read<int>();
	for (re i = 1; i <= n; i++)a[i] = b[i] = read<int>();
	sort(b + 1, b + 1 + n);
	siz = unique(b + 1, b + 1 + n) - b - 1;
	re m = read<int>(), num = sqrt(n);
	for (re i = 1; i <= n; i++) {
		re k = a[i];
		mp[a[i] = lower_bound(b + 1, b + 1 + siz, a[i]) - b] = k % p;
	}
	for (re i = 1; i <= 30000; i++)s[i] = (i - 1) / num + 1;
	for (re i = 1; i <= m; i++) q[i].l = read<int>(), q[i].r = read<int>(), q[i].id = i;
	sort(q + 1, q + 1 + m);
	build(1, 1, siz);
	re l = 1, r = 0;
	for (re i = 1; i <= m; i++) {
		while (l > q[i].l)add(a[--l]);
		while (r < q[i].r)add(a[++r]);
		while (l < q[i].l)del(a[l++]);
		while (r > q[i].r)del(a[r--]);
		ans[q[i].id] = t[1].ans[0][1]%p;
	}
	for (re i = 1; i <= m; i++)writeln((ans[i] % p + p) % p);
}
```



---

## 作者：SilverLi (赞：2)

> [Fibonacci-ish II の 传送门](https://www.luogu.com.cn/problem/CF633H)
>
> [按一按](https://www.cnblogs.com/Silver-Wolf/p/18714622/CF633H)

多个区间和去重交给莫队。

用线段树维护 $\begin{bmatrix}
  fib_{i-1} \times val, fib_i \times val
\end{bmatrix}$。

~~具体和线段树的区间和差不多~~，上传时左右儿子矩阵相加，下传时左右儿子矩阵都乘上懒标记。

斐波那契数列下一项的矩阵是 $\begin{bmatrix}
  0 & 1 \\
  1 & 1
\end{bmatrix}$，插入新数时区间乘这个矩阵就行。

区间除要用刚才矩阵的逆矩阵 $\begin{bmatrix}
  -1 & 1 \\
  1 & 0
\end{bmatrix}$，现在就变成乘法了。

卡常小技巧：

用 `unsigned short`，矩阵乘法展开，离散化。

```cpp
#include <bits/stdc++.h>
#define int unsigned short
#define ls p << 1
#define rs p << 1 | 1
#define Ad tr[p].ad
#define mid (l + r >> 1)
using namespace std;
inline signed read()
{
    signed f = 0, ans = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return f ? -ans : ans;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
const signed N = 3e4 + 5, M = N << 2;
signed a[N], b[N];
int n, m, sq, si, mod;
int fib[N], res[N], mp[N], id[N];
struct que
{
    int l, r, id;
    bool operator<(const que &x) const
    {
        if (l / sq != x.l / sq)
            return l < x.l;
        return l / sq & 1 ? r < x.r : r > x.r;
    }
} q[N];
template <typename T>
inline T Mod(T &&x) { return x >= mod ? x -= mod : x; }
struct Matrix
{
    int h, w, a[2][2];
    Matrix() : Matrix(1, 2) {}
    Matrix(int H, int W) : h(H), w(W)
    {
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j)
                a[i][j] = 0;
    }
    Matrix(short id)
    {
        if (id == 0)
            assert(0);
        else
        {
            h = w = 2;
            if (id > 0)
                a[0][1] = a[1][0] = a[1][1] = 1, a[0][0] = 0;
            else
                a[1][0] = a[0][1] = 1, a[0][0] = mod - 1, a[1][1] = 0;
        }
    }
    Matrix operator+(const Matrix &rhs) const
    {
        Matrix ans(*this);
        Mod(ans.a[0][0] += rhs.a[0][0]);
        Mod(ans.a[0][1] += rhs.a[0][1]);
        return ans;
    }
    Matrix operator*(const Matrix &rhs) const
    {
        Matrix ans(h, rhs.w);
        if (h == 1 && w == 2)
        {
            ans.a[0][0] = Mod(1 * a[0][0] * rhs.a[0][0] % mod + 1 * a[0][1] * rhs.a[1][0] % mod);
            ans.a[0][1] = Mod(1 * a[0][0] * rhs.a[0][1] % mod + 1 * a[0][1] * rhs.a[1][1] % mod);
        }
        else
        {
            ans.a[0][0] = Mod(1 * a[0][0] * rhs.a[0][0] % mod + 1 * a[0][1] * rhs.a[1][0] % mod);
            ans.a[0][1] = Mod(1 * a[0][0] * rhs.a[0][1] % mod + 1 * a[0][1] * rhs.a[1][1] % mod);
            ans.a[1][0] = Mod(1 * a[1][0] * rhs.a[0][0] % mod + 1 * a[1][1] * rhs.a[1][0] % mod);
            ans.a[1][1] = Mod(1 * a[1][0] * rhs.a[0][1] % mod + 1 * a[1][1] * rhs.a[1][1] % mod);
        }
        return ans;
    }
} u[N], ru[N];
struct Tree
{
    struct tree
    {
        Matrix v;
        int sum;
        short ad;
    } tr[M];
    void down(signed p)
    {
        if (Ad > 0)
        {
            tr[ls].v = tr[ls].v * u[Ad], tr[ls].ad += Ad;
            tr[rs].v = tr[rs].v * u[Ad], tr[rs].ad += Ad;
            Ad = 0;
        }
        else if (Ad < 0)
        {
            tr[ls].v = tr[ls].v * ru[-Ad], tr[ls].ad += Ad;
            tr[rs].v = tr[rs].v * ru[-Ad], tr[rs].ad += Ad;
            Ad = 0;
        }
    }
    void update(int p) { tr[p].v = tr[ls].v + tr[rs].v; }
    void insert(int l, int r, int x, signed p, int rk)
    {
        ++tr[p].sum;
        if (l == r)
        {
            tr[p].v = Matrix(1, 2);
            tr[p].v.a[0][0] = 1 * fib[rk - 1] * b[x] % mod;
            tr[p].v.a[0][1] = 1 * fib[rk] * b[x] % mod;
            return;
        }
        down(p);
        if (mid >= x)
            insert(l, mid, x, ls, rk);
        else
            insert(mid + 1, r, x, rs, rk);
        update(p);
    }
    void insert(int x, int rk) { insert(1, si, x, 1, rk); }
    void remove(int l, int r, int x, signed p)
    {
        --tr[p].sum;
        if (l == r)
        {
            tr[p].v = Matrix();
            return;
        }
        down(p);
        if (mid >= x)
            remove(l, mid, x, ls);
        else
            remove(mid + 1, r, x, rs);
        update(p);
    }
    void remove(int x) { remove(1, si, x, 1); }
    void multiply(int l, int r, int s, int t, signed p, Matrix &v, short w)
    {
        if (l >= s && r <= t)
        {
            tr[p].v = tr[p].v * v, tr[p].ad += w;
            return;
        }
        down(p);
        if (mid >= s)
            multiply(l, mid, s, t, ls, v, w);
        if (mid < t)
            multiply(mid + 1, r, s, t, rs, v, w);
        update(p);
    }
    void multiply(int s, int t, Matrix &v, short w) { multiply(1, si, s, t, 1, v, w); }
    int ask_ans() { return tr[1].v.a[0][1]; }
    int rank(int l, int r, int s, int t, signed p)
    {
        if (l >= s && r <= t)
            return tr[p].sum;
        down(p);
        int ans = 0;
        if (mid >= s)
            ans = rank(l, mid, s, t, ls);
        if (mid < t)
            ans += rank(mid + 1, r, s, t, rs);
        return ans;
    }
    int rank(int x) { return rank(1, si, 1, x, 1); }
} tr;
inline void insert(int i)
{
    if (++mp[id[i]] == 1)
    {
        tr.insert(id[i], tr.rank(id[i]) + 1);
        tr.multiply(id[i] + 1, n, u[1], 1);
    }
}
inline void remove(int i)
{
    if (--mp[id[i]] == 0)
    {
        tr.remove(id[i]);
        tr.multiply(id[i] + 1, n, ru[1], -1);
    }
}
signed main()
{
    // freopen("chk.in", "r", stdin);
    // freopen("chk.out", "w", stdout);
    n = read(), sq = sqrt(n);
    mod = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    copy(a + 1, a + n + 1, b + 1);
    sort(b + 1, b + n + 1);
    si = unique(b + 1, b + n + 1) - b;
    for (int i = 1; i <= n; ++i)
        id[i] = lower_bound(b + 1, b + si, a[i]) - b;
    for (int i = 1; i <= n; ++i)
        b[i] = b[i] % mod;
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= n; ++i)
        fib[i] = Mod(fib[i - 1] + fib[i - 2]);
    u[1] = Matrix(1), ru[1] = Matrix(-1);
    for (int i = 2; i <= n; ++i)
        u[i] = u[i - 1] * u[1], ru[i] = ru[i - 1] * ru[1];
    m = read();
    for (int i = 1; i <= m; ++i)
        q[i].l = read(), q[i].r = read(), q[i].id = i;
    sort(q + 1, q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i)
    {
        while (l > q[i].l)
            insert(--l);
        while (r < q[i].r)
            insert(++r);
        while (l < q[i].l)
            remove(l++);
        while (r > q[i].r)
            remove(r--);
        res[q[i].id] = tr.ask_ans();
    }
    for (int i = 1; i <= m; ++i)
        write(res[i]), putchar('\n');
    return 0;
}
```

---

## 作者：bellmanford (赞：2)

这里提供一个显然的分块做法。

显然值域分块，对于每个块暴力搞出所有块内的二元组的形成的区间的值，区间只考虑块内元素的贡献。

由于贡献是按斐波那契数列计算的，可以把贡献转化为矩阵，每次回答时枚举从小到大枚举每个块，假设这个块之前的统计过的个数为 $cnt$ ，每个块对于区间 $[l,r]$ 的贡献是这个块在这个区间内的元素中最靠两边的元素形成的二元组的贡献矩阵乘上斐波那契矩阵的 $cnt$ 次方。

假设询问次数和和 $n$ 同阶，设块长为 $T$ ，预处理复杂度为 $\mathcal{O(Tn\log n)}$ ，需要使用值域线段树来维护，查询复杂度为 $\mathcal{O(n^2/T)}$ ， $T$ 取到 $n/\sqrt{n\log n}$ 时总复杂度为 $\mathcal{O(n\sqrt{n\log n})}$ 。

有一点细节，就是查询时要去重，所以值相同的要在同一块，如果存在某一个值的个数大于块长，可以单独成块，由于值都一样，贡献就不用预处理了，可以特判。

---

## 作者：ty_mxzhn (赞：1)

类似题：[来着不拒，去者不追](https://www.luogu.com.cn/problem/P5501)。

既然看到了这道题，我们就知道这道题应该是 $\Omega(n\sqrt{n})$ 的。结合数据范围我们猜测正解复杂度应该是 $O(n\sqrt{n}\log n)$ 左右。

莫队，维护一个值域线段树，如果这个数没有出现过那么就把后缀乘上一个矩阵，这个位置本身可以存在一个对角矩阵用来乘上自己的数。

莫队不需要回滚，因为斐波那契乘上的矩阵存在逆矩阵 $
\begin{pmatrix}
  0 & 1 \\
  1 & -1
\end{pmatrix}$。

需要离散化。记得取模，可能写的丑需要卡常。

---

## 作者：Lu_xZ (赞：1)

### [Fibonacci-ish II ](https://www.luogu.com.cn/problem/CF633H)
题意：给定一个长度最大为 $30000$ 的序列，和最多 $30000$ 个询问，每个询问问某区间 $[L,R]$ 里的数，去掉重复然后排序之后，依次乘上斐波那契数列然后求和，结果对 $m$ 取余的值。

转化一下题意，也就是在值域数轴上求 $\sum a_i \cdot b_i$。

$a_i$ 是当前位置的值，如果在询问区间中存在就为 $val$，否则为 $0$。

$b_i$ 是该位置乘的哪个斐波那契数。

考虑在 $p$ 位置加入一个数，会产生什么变化。
+ $a_p = val$
+ $[p + 1, inf]$ 的所有 $b$ 变为其下一项。

斐波那契有良好的性质。

$$\left[ \begin{matrix}
   1 & 1\\
   1 & 0 \\
  \end{matrix}
  \right]^n = 
\left[
 \begin{matrix}
    Fib_{n + 1} & Fib_n\\
   Fib_n & Fib_{n - 1}
  \end{matrix}
  \right]
 $$

所以操作二转化为 $[p + 1, inf]$ 所有 $b$ 乘上 $\left[ \begin{matrix}   1 & 1\\   1 & 0 \\  \end{matrix}  \right]$，用线段树维护。

每个节点的懒标记可以用矩阵维护，但常数太大。

只记录每个懒标记的次数，预处理 $Fib[i]$ 和 $invFiv[i]$ 来分别表示 $\left[ \begin{matrix}   1 & 1\\   1 & 0 \\  \end{matrix}  \right]^i$ 和其逆 $\left[ \begin{matrix}   0 & 1\\   1 & -1 \\  \end{matrix}  \right]^i$。

为了减小常数，这里我用一维数组来实现矩阵。
```cpp
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
#define pb emplace_back
#define All(X) X.begin(), X.end()
using namespace std;
using ll = long long;
constexpr int N = 3e4 + 5, B = 175;

int n, m, P, Fib[N][4] = {1, 0, 0, 1}, invFib[N][4] = {1, 0, 0, 1};
int M[4] = {1, 1, 1, 0};
int invM[4] = {0, 1, 1, -1};

int c[4];

inline void mul(int a[4], int b[4]) {
	c[0] = (a[0] * b[0] + a[1] * b[2]) % P;
	c[1] = (a[0] * b[1] + a[1] * b[3]) % P;
	c[2] = (a[2] * b[0] + a[3] * b[2]) % P;
	c[3] = (a[3] * b[3] + a[2] * b[1]) % P;
	memcpy(a, c, 16);
}

int a[N], b[N], tot;
int t[N << 2][4], val[N << 2], tag[N << 2];

#define ls x << 1
#define rs ls | 1

inline void pushup(int x) {
	t[x][0] = (t[ls][0] * val[ls] + t[rs][0] * val[rs]) % P;
	t[x][1] = (t[ls][1] * val[ls] + t[rs][1] * val[rs]) % P;
	t[x][2] = (t[ls][2] * val[ls] + t[rs][2] * val[rs]) % P;
	t[x][3] = (t[ls][3] * val[ls] + t[rs][3] * val[rs]) % P;
}
/*
由于 val 可能为 0，直接在叶子节点上操作有可能会丢失信息
因此把乘 val 的操作放在 pushup 中完成
*/

inline void pushdown(int x) {
	if(tag[x]) {
		if(tag[x] > 0) {
			mul(t[ls], Fib[tag[x]]);
			mul(t[rs], Fib[tag[x]]);
		}
		if(tag[x] < 0) {
			mul(t[ls], invFib[-tag[x]]);
			mul(t[rs], invFib[-tag[x]]);
		}
		tag[ls] += tag[x];
		tag[rs] += tag[x];
		tag[x] = 0;
	}
}

void build(int x = 1, int l = 1, int r = tot) {
	val[x] = l != r;  //非叶子节点的 val 为 1
	if(l == r) {
		memcpy(t[x], M, 16);
		return;
	}
	int mid = l + r >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
}

inline void insert(int p, int x = 1, int l = 1, int r = tot) {
	if(l == r) return val[x] = b[p], void();
	pushdown(x);
	int mid = l + r >> 1;
	if(p <= mid) {
		insert(p, ls, l, mid);
		mul(t[rs], M);
		++ tag[rs];
	}
	else insert(p, rs, mid + 1, r);
	pushup(x);
}

inline void erase(int p, int x = 1, int l = 1, int r = tot) {
	if(l == r) return val[x] = 0, void();
	pushdown(x);
	int mid = l + r >> 1;
	if(p <= mid) {
		erase(p, ls, l, mid);
		mul(t[rs], invM);
		-- tag[rs];
	}
	else erase(p, rs, mid + 1, r);
	pushup(x);
}

int cnt[N], ans[N];

inline void add(int x) {
	if(++ cnt[x] == 1) insert(x);
}

inline void del(int x) {
	if(-- cnt[x] == 0) erase(x);
}

#define c(x) ((x) / B) 

struct qry {
	int l, r, id;
	bool operator < (const qry &x) {
		if(c(l) != c(x.l)) return c(l) < c(x.l);
		if(c(l) & 1) return c(r) < c(x.r);
		return c(r) > c(x.r);
	}
} q[N];

void init_Fib() {
	rep(i, 1, n) {
		memcpy(Fib[i], Fib[i - 1], 16);
		memcpy(invFib[i], invFib[i - 1], 16);
		mul(Fib[i], M);
		mul(invFib[i], invM);
	}
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> P;
	invM[3] = P - 1;
	init_Fib();
	rep(i, 1, n) {
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	tot = unique(b + 1, b + n + 1) - b - 1;
	rep(i, 1, n) {
		a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
	}
	rep(i, 1, tot) {
		b[i] = (b[i] % P + P) % P;
	}
	cin >> m;
	rep(i, 1, m) {
		cin >> q[i].l >> q[i].r;
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);
	build();
	int l = 1, r = 0;
	rep(i, 1, m) {
		auto[L, R, id] = q[i];
		while(l < L) del(a[l ++]);
		while(l > L) add(a[-- l]);
		while(r < R) add(a[++ r]);
		while(r > R) del(a[r --]);
		ans[id] = t[1][2] % P;
	}
	rep(i, 1, m) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

莫队，考虑加入、删除的贡献。

需要维护若干二元组 $(a_i,b_i)$，支持 $a_i$ 单点修改，$b_i$ 区间加减 $1$，求全局 $\sum a_if_{b_i}$，其中 $f$ 是斐波那契数列，

维护 $B_i=\begin{bmatrix}f_{b_i}&f_{b_i-1}\end{bmatrix}$，则问题变为 $a_i$ 单点修改，$B_i$ 区间乘除 $\begin{bmatrix}1&1\\1&0\end{bmatrix}$，求全局 $\sum a_iB_i$，

线段树维护之。卡一卡常。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define K 200
using namespace std;
struct Q
{
    int l, r, i;
} q[30050];
int n, m, z, M, a[30050], _a[30050], b[30050], c[30050], v[30050], Z[30050];
bool O(Q x, Q y) { return b[x.l] == b[y.l] ? b[x.l] & 1 ? x.r < y.r : x.r > y.r : x.l < y.l; }
struct S
{
    int a[2][2];
    S() { memset(a, 0, sizeof a); }
    S operator+(S b)
    {
        S c;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                c.a[i][j] = (a[i][j] + b.a[i][j]) % M;
        return c;
    }
    S operator*(S b)
    {
        S c;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
            {
                int q = 0;
                for (int k = 0; k < 2; ++k)
                    q += a[i][k] * b.a[k][j];
                c.a[i][j] = q % M;
            }
        return c;
    }
    S operator*(long long k)
    {
        S c;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                c.a[i][j] = a[i][j] * k % M;
        return c;
    }
} B, F, _F, G[30050], _G[30050];
struct T
{
    S q;
    int s, z;
} R[30050 << 2];
void u(int p) { R[p].q = R[p << 1].q + R[p << 1 | 1].q; }
void f(int p, int s, int t, int x)
{
    if (x >= 0)
        R[p].q = R[p].q * G[x];
    else
        R[p].q = R[p].q * _G[-x];
    R[p].z += x;
    R[p].s += x;
}
void d(int p, int s, int t)
{
    int m = s + t >> 1;
    if (R[p].z)
        f(p << 1, s, m, R[p].z), f(p << 1 | 1, m + 1, t, R[p].z), R[p].z = 0;
}
void T(int l, int r, int x, int s, int t, int p)
{
    if (l <= s && t <= r)
        return f(p, s, t, x);
    d(p, s, t);
    int m = s + t >> 1;
    if (l <= m)
        T(l, r, x, s, m, p << 1);
    if (r > m)
        T(l, r, x, m + 1, t, p << 1 | 1);
    u(p);
}
void C(int l, int x, int s, int t, int p)
{
    if (s == t)
    {
        R[p].q = B * G[R[p].s] * x;
        return;
    }
    d(p, s, t);
    int m = s + t >> 1;
    if (l <= m)
        C(l, x, s, m, p << 1);
    else
        C(l, x, m + 1, t, p << 1 | 1);
    u(p);
}
void I(int x, int u)
{
    if (!c[u]++)
    {
        C(u, x, 1, z, 1);
        if (u != z)
            T(u + 1, z, 1, 1, z, 1);
    }
}
void D(int x, int u)
{
    if (!--c[u])
    {
        C(u, 0, 1, z, 1);
        if (u != z)
            T(u + 1, z, -1, 1, z, 1);
    }
}
int main()
{
    F.a[0][0] = F.a[0][1] = F.a[1][0] = _F.a[0][1] = _F.a[1][0] = B.a[0][0] = G[0].a[0][0] = G[0].a[1][1] = 1;
    _G[0] = G[0];
    scanf("%d%d", &n, &M);
    _F.a[1][1] = M - 1;
    for (int i = 1; i <= 3e4; ++i)
        G[i] = G[i - 1] * F, _G[i] = _G[i - 1] * _F;
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i), b[i] = (i - 1) / K + 1, v[z++] = a[i];
    sort(v, v + z);
    z = unique(v, v + z) - v;
    for (int i = 1; i <= n; ++i)
        _a[i] = lower_bound(v, v + z, a[i]) - v + 1;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
        scanf("%d%d", &q[i].l, &q[i].r), q[i].i = i;
    sort(q, q + m, O);
    for (int i = 0, l = 1, r = 0; i < m; ++i)
    {
        while (l > q[i].l)
            --l, I(a[l], _a[l]);
        while (r < q[i].r)
            ++r, I(a[r], _a[r]);
        while (l < q[i].l)
            D(a[l], _a[l]), ++l;
        while (r > q[i].r)
            D(a[r], _a[r]), --r;
        Z[q[i].i] = R[1].q.a[0][0];
    }
    for (int i = 0; i < m; ++i)
        printf("%d\n", Z[i]);
    return 0;
}
```


---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF633H)

# 前置知识

[普通莫队算法](https://oi-wiki.org/misc/mo-algo/) | [线段树](https://oi-wiki.org/ds/seg/) | [矩阵](https://oi-wiki.org/math/linear-algebra/matrix/)

# 解法

考虑莫队，先对原序列进行离散化。 

考虑新加入一个数时在权值线段树将后面的数的斐波那契矩阵都乘上一个转移矩阵的系数来表示斐波那契下标加一，删除时将后面的数的斐波那契矩阵都除上一个转移矩阵的系数来表示斐波那契下标减一。

对于常见写法 $\begin{bmatrix} Fib_{n} & Fib_{n+1} \\ 0 & 0 \end{bmatrix}=\begin{bmatrix} 0 & 1 \\ 0 & 0 \end{bmatrix} \times \begin{bmatrix} 0 & 1 \\ 1 & 1 \end{bmatrix}^{n}$，我们发现 $\begin{bmatrix} 0 & 1 \\ 0 & 0 \end{bmatrix}$ 没有逆矩阵，只能另行他法尝试删去其中的 $0$。

另一种写法是 $\begin{bmatrix} Fib_{n+1} & Fib_{n} \\ Fib_{n} & Fib_{n-1} \end{bmatrix}=\begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix} \times \begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}^{n}$，而 $\begin{bmatrix} 1 & 0 \\ 0 & 1 \end{bmatrix}$ 的逆矩阵是它本身，$\begin{bmatrix} 1 & 1 \\ 1 & 0 \end{bmatrix}$ 的逆矩阵是 $\begin{bmatrix} 0 & 1 \\ 1 &-1 \end{bmatrix}$。这样就解决了乘/除一个系数的问题。

略带卡常。需要取模优化和预处理斐波那契及其逆矩阵。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
int a[30010],b[30010],c[30010],pos[30010],L[30010],R[30010],ans[30010],cnt[30010],klen,ksum,p;
struct ask
{
	int l,r,id;
}q[30010];
bool q_cmp(ask a,ask b)
{
	return (pos[a.l]==pos[b.l])?((pos[a.l]%2==1)?(a.r<b.r):(a.r>b.r)):(a.l<b.l);
}
struct Matrix
{
	int ma[4];
	Matrix()
	{
		memset(ma,0,sizeof(ma));
	}
	Matrix operator + (const Matrix &another)
	{
		Matrix ans;
		ans.ma[0]=(ma[0]+another.ma[0])%p;
		ans.ma[1]=(ma[1]+another.ma[1])%p;
		ans.ma[2]=(ma[2]+another.ma[2])%p;
		ans.ma[3]=(ma[3]+another.ma[3])%p;
		return ans;
	}
	Matrix operator * (const Matrix &another)
	{
		Matrix ans;
		ans.ma[0]=(ma[0]*another.ma[0]+ma[1]*another.ma[2])%p;
		ans.ma[1]=(ma[0]*another.ma[1]+ma[1]*another.ma[3])%p;
		ans.ma[2]=(ma[2]*another.ma[0]+ma[3]*another.ma[2])%p;
		ans.ma[3]=(ma[2]*another.ma[1]+ma[3]*another.ma[3])%p;
		return ans;
	}
	Matrix operator * (const int &another)
	{
		Matrix ans;
		ans.ma[0]=ma[0]*another;
		ans.ma[1]=ma[1]*another;
		ans.ma[2]=ma[2]*another;
		ans.ma[3]=ma[3]*another;
		return ans;
	}
}Base,invBase,Fib[30010],invFib[30010];
struct SMT
{
	struct SegmentTree
	{
		int val,lazy;
		Matrix sum;
	}tree[120010];
	#define lson(rt) (rt<<1)
	#define rson(rt) (rt<<1|1)
	void pushup(int rt)
	{
		tree[rt].sum=(tree[lson(rt)].sum*tree[lson(rt)].val)+(tree[rson(rt)].sum*tree[rson(rt)].val);
	}
	void build(int rt,int l,int r)
	{
		if(l==r)
		{
			tree[rt].val=0;
			tree[rt].sum=Base;
			return;
		}
		tree[rt].val=1;
		int mid=(l+r)>>1;
		build(lson(rt),l,mid);
		build(rson(rt),mid+1,r);
	}
	void pushdown(int rt)
	{
		if(tree[rt].lazy!=0)
		{
			if(tree[rt].lazy>0)
			{
				tree[lson(rt)].sum=tree[lson(rt)].sum*Fib[tree[rt].lazy];
				tree[rson(rt)].sum=tree[rson(rt)].sum*Fib[tree[rt].lazy];
			}
			else
			{
				tree[lson(rt)].sum=tree[lson(rt)].sum*invFib[-tree[rt].lazy];
				tree[rson(rt)].sum=tree[rson(rt)].sum*invFib[-tree[rt].lazy];
			}
			tree[lson(rt)].lazy+=tree[rt].lazy;
			tree[rson(rt)].lazy+=tree[rt].lazy;
			tree[rt].lazy=0;
		}
	}
	void update1(int rt,int l,int r,int pos,int val)
	{
		if(l==r)
		{
			tree[rt].val=val;
			return;
		}
		pushdown(rt);
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			update1(lson(rt),l,mid,pos,val);
			tree[rson(rt)].sum=tree[rson(rt)].sum*Base;
			tree[rson(rt)].lazy++;
		}
		else
		{
			update1(rson(rt),mid+1,r,pos,val);
		}
		pushup(rt);
	}
	void update2(int rt,int l,int r,int pos,int val)
	{
		if(l==r)
		{
			tree[rt].val=val;
			return;
		}
		pushdown(rt);
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			update2(lson(rt),l,mid,pos,val);
			tree[rson(rt)].sum=tree[rson(rt)].sum*invBase;
			tree[rson(rt)].lazy--;
		}
		else
		{
			update2(rson(rt),mid+1,r,pos,val);
		}
		pushup(rt);
	}
}T;
void init(int n,int m)
{
	klen=n/sqrt(m)+1;
	ksum=n/klen;
	for(int i=1;i<=ksum;i++)
	{
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+klen;
	}
	if(R[ksum]<n)
	{
		ksum++;
		L[ksum]=R[ksum-1]+1;
		R[ksum]=n;
	}
	for(int i=1;i<=ksum;i++)
	{
		for(int j=L[i];j<=R[i];j++)
		{
			pos[j]=i;
		}
	}
	Base.ma[0]=1;     Base.ma[1]=1;     Base.ma[2]=1;     Base.ma[3]=0;
	invBase.ma[0]=0;  invBase.ma[1]=1;  invBase.ma[2]=1;  invBase.ma[3]=p-1;
	Fib[0].ma[0]=1;   Fib[0].ma[1]=0;   Fib[0].ma[2]=0;   Fib[0].ma[3]=1;
	invFib[0].ma[0]=1;invFib[0].ma[1]=0;invFib[0].ma[2]=0;invFib[0].ma[3]=1;
	for(int i=1;i<=n;i++)
	{
		Fib[i]=Fib[i-1]*Base;
		invFib[i]=invFib[i-1]*invBase;
	}
	T.build(1,1,b[0]);
}
void add(int x)
{
	cnt[a[x]]++;
	if(cnt[a[x]]==1)
	{
		T.update1(1,1,b[0],a[x],c[x]);
	}
}
void del(int x)
{
	cnt[a[x]]--;
	if(cnt[a[x]]==0)
	{
		T.update2(1,1,b[0],a[x],0);
	}
}
int main()
{
	int n,m,l,r,i;
	scanf("%d%d",&n,&p);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
		c[i]=a[i]%p;
	}
	sort(b+1,b+1+n);
	b[0]=unique(b+1,b+1+n)-(b+1);
	for(i=1;i<=n;i++)
	{
		a[i]=lower_bound(b+1,b+1+b[0],a[i])-b;
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	init(n,m);
	sort(q+1,q+1+m,q_cmp);
	for(i=1,l=1,r=0;i<=m;i++)
	{
		while(l>q[i].l)
		{
			l--;
			add(l);
		}
		while(r<q[i].r)
		{
			r++;
			add(r);
		}
		while(l<q[i].l)
		{
			del(l);
			l++;
		}
		while(r>q[i].r)
		{
			del(r);
			r--;
		}
		ans[q[i].id]=T.tree[1].sum.ma[1];
	}
	for(int i=1;i<=m;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

