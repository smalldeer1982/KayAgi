# GukiZ and GukiZiana

## 题目描述

Professor GukiZ was playing with arrays again and accidentally discovered new function, which he called $ GukiZiana $ . For given array $ a $ , indexed with integers from $ 1 $ to $ n $ , and number $ y $ , $ GukiZiana(a,y) $ represents maximum value of $ j-i $ , such that $ a_{j}=a_{i}=y $ . If there is no $ y $ as an element in $ a $ , then $ GukiZiana(a,y) $ is equal to $ -1 $ . GukiZ also prepared a problem for you. This time, you have two types of queries:

1. First type has form $ 1 $ $ l $ $ r $ $ x $ and asks you to increase values of all $ a_{i} $ such that $ l<=i<=r $ by the non-negative integer $ x $ .
2. Second type has form $ 2 $ $ y $ and asks you to find value of $ GukiZiana(a,y) $ .

For each query of type $ 2 $ , print the answer and make GukiZ happy!

## 样例 #1

### 输入

```
4 3
1 2 3 4
1 1 2 1
1 1 1 1
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 3
1 2
1 2 2 1
2 3
2 4
```

### 输出

```
0
-1
```

# 题解

## 作者：shao0320 (赞：4)

### CF551E GukiZ and GukiZiana

一道思维比较水但是考察卡 $\text{STL}$ 常数的数据结构题

首先看到这个 $10s$ 的时限和 $n\leq5\times10^5$ 的数据范围就感觉并不是很友好。

这个东西实际上就是把每个点抽出来求第一个和最后一个的距离，$1$ 操作显然分块之后打标记维护整块的 $\text{tag}$ 即可。

考虑暴力 $2$ 操作就是从两边枚举到第一个值为 $y$ 的点的位置之差，那么只需要用一个数据结构来支持快速找出来一个块内是否有数字 $y$ 即可。

平衡树等数据结构都是可以的，我用的是 $\text{multiset}$，但是被卡那个 $\log$ 了，因此用了 $\text{unordered multiset}$ 就过去了。

时间复杂度 $n\sqrt n$

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<unordered_set>
#define N 505005
#define int long long
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,q,a[N],col[N],tag[N],L[N],R[N],blo;
unordered_multiset<int>S[805];
void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+48); 
}
signed main()
{
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	blo=700;
	for(int i=1;i<=n;i+=blo)
	{
		for(int j=i;j<i+blo;j++)col[j]=(i-1)/blo+1;
		L[(i-1)/blo+1]=i;R[(i-1)/blo+1]=min(n,i+blo-1);
	}
	for(int i=1;i<=n;i++)S[col[i]].insert(a[i]);
	while(q--)
	{
		int opt=read();
		if(opt==1)
		{
			int l=read(),r=read(),x=read();
			for(int i=l;i<=min(R[col[l]],r);i++)a[i]+=x;
			S[col[l]].clear();
			for(int i=L[col[l]];i<=R[col[l]];i++)S[col[l]].insert(a[i]);
			if(col[l]==col[r])continue;
			for(int i=L[col[r]];i<=r;i++)a[i]+=x;
			S[col[r]].clear();
			for(int i=L[col[r]];i<=R[col[r]];i++)S[col[r]].insert(a[i]);
			for(int i=col[l]+1;i<=col[r]-1;i++)tag[i]+=x;
		}
		if(opt==2)
		{
			int le=0,ri=0,Y=read();
			for(int i=col[n];i>=1;i--)
			{
				if(S[i].find(Y-tag[i])==S[i].end())continue;
				else{for(int j=R[i];j>=L[i];j--)if(a[j]+tag[i]==Y){ri=j;break;};break;}
			}
			for(int i=1;i<=col[n];i++)
			{
				if(S[i].find(Y-tag[i])==S[i].end())continue;
				else{for(int j=L[i];j<=R[i];j++)if(a[j]+tag[i]==Y){le=j;break;};break;}
			}
			if(le==0)puts("-1");
			else write(ri-le),puts("");
		}
	}
}
```

---

## 作者：lyt_awa (赞：2)

### [< 题目传送门 >](https://www.luogu.com.cn/problem/CF551E)
一看到区间操作于是我们就：分块大法吼啊！！！

对于区间加法想必大家都比较熟悉了，这里不再赘述。
### 暴力
对于询问我们可以发现每一次都是对整个区间进行询问。很显然暴力的解法就是从前往后扫找到最前面的等于 $y$ 的数的下标 $l$，再从后往前扫找到最前面的等于 $y$ 的数的下标 $r$，$r-l$ 即为所求（若找不到则为 $-1$）。
### 优化
我们可以在每一块里用 unordered_map 来记录是否有 $y$ 这个数，这样在找的时候，遇到有 $y$ 的块直接 for 找到最边上的 $y$ 的位置就好了。
## 时间复杂度
由于我们找 $l$ 的时候是从左往右，找 $r$ 的时候是从右往左，所以只会暴力扫块两次，则询问的复杂度为 $O(\sqrt{n})$。操作也为 $O(\sqrt{n})$。所以总的时间复杂度为 $O(q\sqrt{n})$（~~应该是最快的吧~~）。
## $code$
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 5e5 + 5;

inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int n, q, T, pos[N], L[709], R[709];
ll a[N], add[709];
unordered_map<ll, bool> ji[709];

inline void iinit(int i) {
	for (int j = L[i]; j <= R[i]; ++j) pos[j] = i, ji[i][a[j]] = 1;
	for (int j = R[i]; j >= L[i]; --j) ji[i][a[j]] = 1;
}

inline void init(int geshu) {
	T = geshu;
	for (int i = 1; i <= T; ++i) L[i] = (i - 1) * (n / geshu) + 1, R[i] = i * (n / geshu), iinit(i);
	if (R[T] < n) ++T, L[T] = R[T - 1] + 1, R[T] = n, iinit(T);
}

inline void change(int l, int r, ll x) {
	int p = pos[l], q = pos[r];
	if (p == q) {
		for (int i = L[p]; i <= R[p]; ++i) ji[p].erase(a[i]);
		for (int i = l; i <= r; ++i) a[i] += x;
		for (int i = L[p]; i <= R[p]; ++i) ji[p][a[i]] = 1;
		return;
	}
	for (int i = p + 1; i <= q - 1; ++i) add[i] += x;
	for (int i = L[p]; i <= R[p]; ++i) ji[p].erase(a[i]);
	for (int i = l; i <= R[p]; ++i) a[i] += x;
	for (int i = L[p]; i <= R[p]; ++i) ji[p][a[i]] = 1;
	for (int i = L[q]; i <= R[q]; ++i) ji[q].erase(a[i]);
	for (int i = L[q]; i <= r; ++i) a[i] += x;
	for (int i = L[q]; i <= R[q]; ++i) ji[q][a[i]] = 1;
	return;
}

inline int ask(ll y) {
	int l = -1;
	for (int i = 1; i <= T; ++i) {
		if (ji[i][y - add[i]]) {
			for (int j = L[i]; j <= R[i]; ++j)
				if (a[j] == y - add[i]) {
					l = j;
					break;
				}
			break;
		}
		else ji[i].erase(y - add[i]);
	}
	if (l == -1) return -1;
	int r = -1;
	for (int i = T; i >= 1; --i) {
		if (ji[i][y - add[i]]) {
			for (int j = R[i]; j >= L[i]; --j)
				if (a[j] == y - add[i]) {
					r = j;
					break;
				}
			break;
		}
		else ji[i].erase(y - add[i]);
	}
	return r - l;
}

int main() {
	n = read(); q = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	init(sqrt(n));
	while (q--) {
		int opt = read();
		if (opt == 1) {
			int l = read(), r = read();
			ll x = read();
			change(l, r, x);
		}
		else {
			ll y = read();
			printf("%d\n", ask(y));
		}
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：2)

分块出奇迹！~~打表过样例！~~

我们发现。操作一就是非常经典的区间加问题。操作二其实就是求最靠左和最靠右的值为 $x$ 的位置。

我们考虑分块。对于每一块建一个 $multiset$，维护块中的数的集合。对于操作 $1$，直接边角块暴力，中间块打一个标记。对于操作二，直接从左到右（从右到左）循环每一块，如果在这一块中的数中存在 $x$，就循环一遍这一块中的数，碰到 $x$ 就直接退出。

注意点：不要break掉内层循环忘了break外层。

```cpp
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define int long long
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
int n=read(),m=read(),a[500005];
int l[5005],r[5005],blk,bel[500005],tag[5005];
multiset<int> pos[5005];
const int BLOCK_SZ=700;
signed main(){
	fz(i,1,n)	a[i]=read();
	blk=(n-1)/BLOCK_SZ+1;
	fz(i,1,blk){
		l[i]=(i-1)*BLOCK_SZ+1;
		r[i]=min(i*BLOCK_SZ,n);
		fz(j,l[i],r[i])	bel[j]=i;
//		cout<<l[i]<<" "<<r[i]<<endl;
	}
	fz(i,1,blk){
		fz(j,l[i],r[i])
			pos[i].insert(a[j]);
	}
	while(m--){
		int opt=read();
		if(opt==1){
			int L=read(),R=read(),x=read();
			int l0=bel[L],r0=bel[R];
//			cout<<l0<<" "<<r0<<endl;
			if(l0==r0){
				pos[l0].clear();
				fz(i,L,R){
					a[i]+=x;
				}
				fz(i,l[l0],r[l0])	pos[l0].insert(a[i]);
			}
			else{
				for(int i=l0+1;i<r0;i++)	tag[i]+=x;
				pos[l0].clear();
				fz(i,L,r[l0]){
					a[i]+=x;
				}
				fz(i,l[l0],r[l0])	pos[l0].insert(a[i]);
				pos[r0].clear();
				fz(i,l[r0],R){
					a[i]+=x;
				}
				fz(i,l[r0],r[r0])	pos[r0].insert(a[i]);
			}
		}
		else{
			int x=read();
			int L=0,R=0;
			fz(i,1,blk){
				if(pos[i].find(x-tag[i])!=pos[i].end()){
					bool flag=0;
					fz(j,l[i],r[i]){
//						cout<<a[j]<<endl;
//						cout<<a[j]+tag[i]<<" "<<x<<endl;
						if((a[j]+tag[i])==x){
							L=j;
							flag=1;
							break;
						}
					}
					if(flag)	break;
				}
			}
			fd(i,blk,1){
				if(pos[i].find(x-tag[i])!=pos[i].end()){
					bool flag=0;
					fd(j,r[i],l[i]){
						if(a[j]+tag[i]==x){
							R=j;
							flag=1;
							break;
						}
					}
					if(flag)	break;
				}
			}
			if(L==0||R==0)	puts("-1");
			else			cout<<R-L<<endl;
		}
	}
	return 0;
}
```

---

## 作者：free_fall (赞：1)

# 题目大意
给定一个数列 $a_1,a_2,\dots,a_n$，有两个操作：

1.  给定 $l,r,x$，令 $a_l,a_{l+1},\dots,a_r$ 都加上 $x$。
2.  给定 $y$,求一个最大的 $j-i$，满足 $a_i=a_j=y$，输出最大的 $j-i$，无解输出 $-1$。
# 思路
题目可以简单理解为做一个区间加法以及查询最左端和最右端数值为 $y$ 的数。

很容易可以想到怎么写暴力，直接暴力循环修改区间，再循环两次查找左端点和右端点。而正解也是在这种暴力写法的基础上加一些优化得来的。

首先我们很容易地发现暴力修改区间效率太低了，所以可以使用**分块**的写法进行优化，将区间查询的时间复杂度由 $O(n)$ 降到 $O(\sqrt n)$，~~我们教练说分块就是优美的暴力~~。
```
void Add(int l,int r,int c){
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;i++){
			a[i]+=c;
		}
		copy(bel[l]);
		return;
	}
	for(int i=l;i<=R[bel[l]];i++){
		a[i]+=c;
	}
	copy(bel[l]);
	for(int i=L[bel[r]];i<=r;i++){
		a[i]+=c;
	}
	copy(bel[r]);
	for(int i=bel[l]+1;i<=bel[r]-1;i++){
		add[i]+=c;
	}
	return;
}
```
~~然后就有一个残酷的现实摆在面前~~，如果无法将查询左右端点的时间复杂度降下来，我们前面写的关于**分块**的优化就和学校的眼保健操一样毫无意义。既然前面已经写好了**分块**，不如继续利用这种写法。

我们可以用 ```pair<int,int> b``` 来记录排好序的每一个块，$b_{first}$ 记录数值，$b_{second}$ 记录在原数组中的下标，然后暴力枚举每一个块，使用**二分**来查找左右端点。这样查询的时间复杂度也由 $O(n)$ 降到了 $O(\sqrt n\log n)$，整体的时间复杂度为 $O(n\sqrt n\log n)$，已经可以过掉这道题了。

注意判掉 $y$ 不存在的情况，此时应该输出 $-1$。
# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,q,a[N],bel[N],L[N],R[N],C,add[N];
pair<int,int> b[N];
void copy(int now){
	for(int i=L[now];i<=R[now];i++){
		b[i].first=a[i];
		b[i].second=i;
	}
	sort(b+L[now],b+R[now]+1);
	return;
}
void init(){
	C=sqrt(n);
	for(int i=1;i<=(n-1)/C+1;i++){
		L[i]=(i-1)*C+1;
		R[i]=i*C;
	}
	R[(n-1)/C+1]=n;
	for(int i=1;i<=n;i++){
		bel[i]=(i-1)/C+1;
	}
	for(int i=1;i<=(n-1)/C+1;i++){
		copy(i);
	}
	return;
}
void Add(int l,int r,int c){
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;i++){
			a[i]+=c;
		}
		copy(bel[l]);
		return;
	}
	for(int i=l;i<=R[bel[l]];i++){
		a[i]+=c;
	}
	copy(bel[l]);
	for(int i=L[bel[r]];i<=r;i++){
		a[i]+=c;
	}
	copy(bel[r]);
	for(int i=bel[l]+1;i<=bel[r]-1;i++){
		add[i]+=c;
	}
	return;
}
int query(int c){
	int ans1=0x7f7f7f7f,ans2=-0x7f7f7f7f;
	for(int i=1;i<=(n-1)/C+1;i++){
		int l=L[i],r=R[i],ans=-1;
		while(l<=r){
			int mid=(l+r)/2;
			if(b[mid].first+add[i]>=c){
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		if(ans>=L[i]&&ans<=R[i]&&b[ans].first+add[i]==c)ans1=min(ans1,b[ans].second);
	}
	for(int i=1;i<=(n-1)/C+1;i++){
		int l=L[i],r=R[i],ans=-1;
		while(l<=r){
			int mid=(l+r)/2;
			if(b[mid].first+add[i]<=c){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		if(ans>=L[i]&&ans<=R[i]&&b[ans].first+add[i]==c)ans2=max(ans2,b[ans].second);
	}
	if(ans1==0x7f7f7f7f||ans2==-0x7f7f7f7f)return -1;
	return ans2-ans1;
}
signed main(){
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	init();
	while(q--){
		int op,l,r,x,y;
		scanf("%lld",&op);
		if(op==1){
			scanf("%lld%lld%lld",&l,&r,&x);
			Add(l,r,x);
		}
		if(op==2){
			scanf("%lld",&y);
			printf("%lld\n",query(y));
		}
	}
	return 0;
}
```

---

## 作者：Memory_of_winter (赞：1)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10135735.html)

**题目大意：**一个长度为$n(n\leqslant5\times10^5)$的数组，有两个操作：

1. $1\;l\;r\;x：$把区间$[l,r]$加上$x$
2. $2\;x：$询问$x$第一次出现和最后一次出现之间的距离，若没出现输出$-1$

**题解：**分块，把每个块排个序（可以把数值为第一关键字，位置为第二关键字），整块的加就块上打$tag$，非整块的就暴力重构，查询就在每个块内求这个数出现位置，直接二分查找就行了。设块大小为$S$，修改复杂度$O(\dfrac n S+2S)$，查询复杂度$O(\dfrac n S\log_2 S)$，$S$略大于$\sqrt n$最好。




**C++ Code：**

```cpp
#include <algorithm>
#include <cstdio>
#include <cctype>
namespace IO {
	struct istream {
#define M (1 << 24 | 3)
		char buf[M], *ch = buf - 1;
		inline istream() {
#ifndef ONLINE_JUDGE
			freopen("input.txt", "r", stdin);
#endif
			fread(buf, 1, M, stdin);
		}
		inline istream& operator >> (int &x) {
			while (isspace(*++ch));
			for (x = *ch & 15; isdigit(*++ch); ) x = x * 10 + (*ch & 15);
			return *this;
		}
		inline istream& operator >> (long long &x) {
			while (isspace(*++ch));
			for (x = *ch & 15; isdigit(*++ch); ) x = x * 10 + (*ch & 15);
			return *this;
		}
#undef M
	} cin;
	struct ostream {
#define M (1 << 24 | 3)
		char buf[M], *ch = buf - 1;
		int w;
		inline ostream& operator << (int x) {
			if (!x) {
				*++ch = '0';
				return *this;
			}
			if (x < 0) *++ch = '-', x = -x;
			for (w = 1; w <= x; w *= 10);
			for (w /= 10; w; w /= 10) *++ch = (x / w) ^ 48, x %= w;
			return *this;
		}
		inline ostream& operator << (const char x) {*++ch = x; return *this;}
		inline ~ostream() {
#ifndef ONLINE_JUDGE
			freopen("output.txt", "w", stdout);
#endif
			fwrite(buf, 1, ch - buf + 1, stdout);
		}
#undef M
	} cout;
}

#define maxn 500010
const int BSZ = 1 << 10, BNUM = maxn / BSZ + 10;

int bel[maxn];
int L[BNUM], R[BNUM];
long long tg[BNUM];
struct node {
	long long s;
	int id;
	inline node() {}
	inline node(long long __s, int __id) : s(__s), id(__id) {}
	inline node(int __s, int __id) {s = __s, id = __id;}
	inline friend bool operator < (const node &lhs, const node &rhs) {
		return lhs.s == rhs.s ? lhs.id < rhs.id : lhs.s < rhs.s;
	}
} s[maxn];

int n, m, Bnum;

int query(const int x) {
	int max = 0, min = 0;
	for (int i = 1; i <= Bnum; i++) if (tg[i] <= x) {
		const int y = x - tg[i];
		int l = std::lower_bound(s + L[i], s + R[i], node(y, 0)) - s;
		if (l != R[i] && s[l].s == y) {
			int r = std::lower_bound(s + L[i], s + R[i], node(y + 1, 0)) - s - 1;
			if (!min) min = s[l].id;
			max = s[r].id;
		}
	}
	if (!min) return -1;
	return max - min;
}
int main() {
	IO::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		IO::cin >> s[i].s; s[i].id = i;
		bel[i] = (i - 1 >> 10) + 1;
	}

	Bnum = bel[n];
	for (int i = 1; i <= Bnum; i++) {
		L[i] = i - 1 << 10, R[i] = L[i] + BSZ;
	}
	L[1] = 1, R[Bnum] = n + 1;
	for (int i = 1; i <= Bnum; i++) {
		std::sort(s + L[i], s + R[i]);
	}

	while (m --> 0) {
		int op, l, r, x;
		IO::cin >> op >> l;
		if (op == 1) {
			IO::cin >> r >> x;
			const int lb = bel[l], rb = bel[r];
			if (lb == rb) {
				for (register node *now = s + L[lb]; now != s + R[lb]; ++now) if (l <= now -> id && now -> id <= r) now -> s += x;
				std::sort(s + L[lb], s + R[lb]);
			} else {
				for (register node *now = s + L[lb]; now != s + R[lb]; ++now) if (l <= now -> id) now -> s += x;
				std::sort(s + L[lb], s + R[lb]);
				for (int i = lb + 1; i < rb; i++) tg[i] += x;
				for (register node *now = s + L[rb]; now != s + R[rb]; ++now) if (now -> id <= r) now -> s += x;
				std::sort(s + L[rb], s + R[rb]);
			}
		} else {
			IO::cout << query(l) << '\n';
		}
	}
	return 0;
}

```



---

## 作者：critnos (赞：1)

相信大家看了别的神仙的题解都知道怎么用分块做了

接下来讲几个细节

为了查找一个块里用有没有一个数，可以用暴力排序+二分查找，set，uset 等方法实现。

其中前两种方法都是 $\sqrt n \log n$ 的，用 uset 实现是 $\sqrt n$ 的，所以用 uset 更好。

吗？

事实证明 uset 的常数大到飞天！

这是 [uset](https://www.luogu.com.cn/record/35833841)

这是 [暴力排序+二分](https://www.luogu.com.cn/record/35834321)

答案显然。

然后相信大家看到这题就显然联想到由乃打扑克。

但是要注意，这题要用 `long long`。

最后是一个剪枝的方法。

在块内二分/倍增的时候

先判断块内最大/最小值是否小于/大于 $y$，如果是就直接返回 $0$。

[加了剪枝后](https://www.luogu.com.cn/record/35831656) 快了一倍。

---

## 作者：intel_core (赞：0)

首先发现这个题询问操作要求只和一个值有关，于是我们只需要把每个值单独维护就可以了。

一般的 $\text{poly log}$ 数据结构都不能很好地支持操作2，于是我们直接分块维护每个块内每个数具体的值，询问的时候只需要询问当前值在块内第一次和最后一次出现的地方就可以。

具体来说，我们对序列分块：

* 如果修改的是整块，直接打懒标记；如果修改的是不满一块的数，暴力改然后重构这个快。

* 询问的时候依次扫一遍即可。

可以用 `STL::unordered_map` 和 `STL::unordered_set` 做到总复杂度 $O(n \sqrt{n})$，手动 $O_2$ 后可以跑进 $2s$ 。

---

