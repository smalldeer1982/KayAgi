# Little Elephant and Array

## 题目描述

小象喜欢和数组玩。现在有一个数组  $a$，含有  $n$ 个正整数，记第  $i$ 个数为  $a_i$。

现在有  $m$ 个询问，每个询问包含两个正整数  $l_j$ 和  $r_j \;(1\leqslant l_j\leqslant r_j\leqslant n)$，小象想知道在  $A_{l_j}$ 到  $A_{r_j}$ 之中有多少个数  $x$，其出现次数也为  $x$。

## 样例 #1

### 输入

```
7 2
3 1 2 2 3 3 7
1 7
3 4
```

### 输出

```
3
1
```

# 题解

## 作者：Kewth (赞：30)

~~刷淼题~~

这题莫队不够优秀，需要离线还稍微难写点。

注意到一个数 x 可能对一个询问产生贡献的必要条件的是其出现过至少 x 次，这样的数不超过 $O(\sqrt{n})$ 个，对于每个这样的数记出现次数的前缀和，对于询问暴力枚举所有这样的数并通过前缀和查询该数的出现次数即可。

复杂度 $O((n+q)\sqrt{n})$ ，代码十分简单：

```cpp
#include <cstdio>

struct { inline operator int () { int x; return scanf("%d", &x), x; } } read;

const int maxn = 100005, maxb = 500;
int a[maxn], tot[maxn];
int t[maxb][maxn], val[maxb];

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++)
		if ((a[i] = read) <= n)
			++ tot[a[i]];
	int p = 0;
	for (int x = 1; x <= n; x ++)
		if (tot[x] >= x) {
			val[++ p] = x;
			for (int i = 1; i <= n; i ++)
				t[p][i] = t[p][i - 1] + (a[i] == x);
		}
	while (q --) {
		int l = read, r = read, ans = 0;
		for (int i = 1; i <= p; i ++)
			if (t[i][r] - t[i][l - 1] == val[i])
				++ ans;
		printf("%d\n", ans);
	}
}
```

---

## 作者：Warriors_Cat (赞：8)

似乎莫队的思路更好想一些？

---

### $Solution:$

首先，$a_i> n$ 的 $a_i$ 肯定没有贡献，因为一共就只有 $n$ 个数。所以 $a_i > n$ 的都可以直接舍掉，这样子值域就也是 $10^5$ 了，无需离散化。

由于在此题是要恰好为 $a_i$ 次，所以 `Insert` 和 `Delete` 也要注意，一旦不是 $a_i$ 就要把贡献 $-1$。

比如说，在 `Insert` 的时候，当 `cnt[a[x]] == a[x] + 1` 时，贡献要减回来。`Delete` 也同理。

后面就是莫队基础操作了，时间复杂度为 $O(m\log m+n\sqrt{n})$。

---

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;
#define ll long long
#define fi first
#define se second
#define x1 x_csyakioi_1
#define x2 x_csyakioi_2
#define y1 y_csyakioi_1
#define y2 y_csyakioi_2
#define y0 y_csyakioi_0
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 100010;
int n, m, k, a[N], pos[N], cnt[N], ans[N], res;
struct ask{
	int l, r, idx;
	bool operator < (const ask&rhs)const{
		return pos[l] ^ pos[rhs.l] ? l < rhs.l : pos[l] & 1 ? r < rhs.r : r > rhs.r;
	}
}q[N];
inline void Insert(int x){
	if(a[x] > n) return;
	++cnt[a[x]];
	if(cnt[a[x]] == a[x]) ++res;
	if(cnt[a[x]] == a[x] + 1) --res;
}
inline void Delete(int x){
	if(a[x] > n) return;
	if(cnt[a[x]] == a[x] + 1) ++res;
	if(cnt[a[x]] == a[x]) --res;
	--cnt[a[x]];
}
int main(){
	n = read(); m = read(); k = sqrt(n);
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) pos[i] = (i - 1) / k + 1;
	for(int i = 1; i <= m; ++i) q[i].l = read(), q[i].r = read(), q[i].idx = i;
	sort(q + 1, q + m + 1); int L = 1, R = 0;
	for(int i = 1; i <= m; ++i){
		int x = q[i].l, y = q[i].r, idx = q[i].idx;
		while(R < y) Insert(++R);
		while(L > x) Insert(--L);
		while(R > y) Delete(R--);
		while(L < x) Delete(L++);
		ans[idx] = res;
	}
	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：marTixx (赞：7)

提供一种不一样的 $\mathcal{O(nlog_n)}$ 解法

# 题意

离线询问在区间 $[ l,r ]$ 中有多少个数$x$，其出现次数也为$x$

# Sol


## 思路

一看到这题马上会联想到 [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972)

建议先做 P1972，本题可以借鉴 P1972 的想法完成

先把询问离线下来，

我们考虑区间内一个数 $x$ 是否能造成贡献，我们先看区间内最右的那个 $x$，如果这个 $x$ 的第往左 $x - 1$ 个 $x$ 在区间内，且这个 $x$ 的第往左 $x$ 个 $x$ 不在区间内，我们就可以给答案加 $1$。

所以我们把区间按左端点排序，用树状数组或者线段树维护一下。

具体维护什么呢？

下面可能有一点点难理解，可以拿小数据模拟一下下面的过程好好想想。

考虑当前的数为 $x$，

- 若 $x$ 往左第 $ x - 1$ 个数存在，且它的位置为 $p_1$，那我们就给数据结构上位置 $p_1$ 的贡献由 $ 0 $ 改为  $ 1$；

- 若 $x$ 往左第 $x$ 个数存在，且它的位置为 $p_2$，我们在处理上一个 $x$ 时就把它的贡献改为 $1$ 了，但此时它已经不符合条件（因为算上它的区间就会包含 $x + 1$ 个 $x$ 了），所以把它的贡献由 $1$ 改为为 $-1$，为什么是 $-1$ 而不是 $ 0 $呢，因为这里其实是一个差分，仔细模拟一下就能理解
- 若 $x$ 往左第 $x + 1$ 个数存在，且它的位置为 $p_3$，你会发现我们在上一个 $x$ 处把它改成了 $-1$，但是此时我们已经把 $p_2$ 位置改成了 $-1$，所以它的差分贡献已经不是 $-1$ 了，而是 $0$ ，所以把 $p_3$ 位置由 $-1$ 改成 $0$。

## 细节

1. $a_i$ 最大有 $1e9$，需离散化一下，
2. 每个 $x$ 的位置我们可以用 vector 来记录。

## 代码

~~我习惯线段树所以这里提供的是线段树的代码~~

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 1e5 + 30;

std::vector < int > v[N];


int n, m;
int a[N], ans[N], pos[N], s[N], b[N];

struct NODE
{
    int l, r, id;
}q[N];
struct SEGMENTTREE
{
    int l, r, s;
}t[N << 2];

int read()
{
    int s = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
    return s;
}

int cmp(NODE x, NODE y)
{
    return x.r < y.r;
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if (t[p].l == t[p].r) return ;
    int mid = l + r >> 1;
    build(p << 1, l, mid), build(p << 1 | 1, mid + 1, r);
}

void change(int p, int pos, int val)
{
    if (t[p].l == t[p].r) {t[p].s = val; return ; }
    int mid = t[p].l + t[p].r >> 1;
    if (pos <= mid) change(p << 1, pos, val);
    else change(p << 1 | 1, pos, val);
    t[p].s = t[p << 1].s + t[p << 1 | 1].s;
}

int ask(int p, int l, int r)
{
    if (t[p].l >= l && t[p].r <= r) return t[p].s;
    int mid = t[p].l + t[p].r >> 1, tot = 0;
    if (l <= mid) tot += ask(p << 1, l, r);
    if (mid < r) tot += ask(p << 1 | 1, l, r);
    return tot;
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++ i) s[i] = read(), b[i] = s[i];
    std::sort(s + 1, s + n + 1); int len = std::unique(s + 1, s + n + 1) - s - 1;
    for (int i = 1; i <= n; ++ i) a[i] = std::lower_bound(s + 1, s + len + 1, b[i]) - s;
    for (int i = 1; i <= n; ++ i) v[a[i]].push_back(i), pos[i] = v[a[i]].size() - 1;
    for (int i = 1; i <= m; ++ i) q[i].l = read(), q[i].r = read(), q[i].id = i;
    std::sort(q + 1, q + m + 1, cmp); build(1, 1, n);
    for (int i = 1; i <= m; ++ i)
    {
        int last = q[i - 1].r + 1;
        for (int j = last; j <= q[i].r; ++ j)
        {
            if (pos[j] - b[j] + 1 >= 0)
            {
                if (pos[j] - b[j] >= 0) change(1, v[a[j]][pos[j] - b[j]], -1);
                if (pos[j] - b[j] - 1 >= 0) change(1, v[a[j]][pos[j] - b[j] - 1], 0);
                change(1, v[a[j]][pos[j] - b[j] + 1], 1);
            }
        }
        ans[q[i].id] = ask(1, q[i].l, q[i].r);
    }
    for (int i = 1; i <= m; ++ i) printf ("%d\n", ans[i]);
    return 0;
}
```



---

## 作者：Shirο (赞：6)

第一次手切的紫题

观察题目，值域是$1e9$,可是$n$只有$1e6$

说明大于n的数全部对答案没有贡献

假若1有1个，2有两个，以此类推，约500个才到$1e5$上限

固记录同一数字出现的位置，对于l，r二分

复杂度$O(500 nlogn)$

```cpp
#include<bits/stdc++.h>
#define dbg(x) cout<<#x "=" <<x<<endl;
using namespace std;
const int maxn=1e6+5;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
#define __ read()//快读
vector<int> g[maxn];//用于存储某一数字的出现位置
vector<int> pending;//有可能符合条件的数字
int q,n,m,bloc[maxn];
int main()
{
	n=__,q=__;
	for(int i=1;i<=n;++i)
	{
		bloc[i]=__;
		if(bloc[i]<=n)
			g[bloc[i]].push_back(i);
	}
	for(int i=1;i<=n;++i)
	{
		if(g[i].size()>=i)
			pending.push_back(i);//如果符合条件
	}
	while(q--)
	{
		int l=__,r=__,ans=0;
		for(auto block:pending)
		{
			int cur=block;
			int ll=lower_bound(g[cur].begin(),g[cur].end(),l)-g[cur].begin();//二分左边界
			int rr=upper_bound(g[cur].begin(),g[cur].end(),r)-g[cur].begin();//二分右边界
			if(rr-ll==cur)++ans;
		} 
		cout<<ans<<endl;
	}
}
```


---

## 作者：suyue1098765432 (赞：2)

这道题有一个复杂度为$O(nlogn)$的做法，就是离线+线段树。

这个做法，需要把所有的询问以右端点写一个链表存储起来，然后考虑每个右端点来回答询问。

注意到对于一个右端点，对于一个数$x$使得，出现次数也为$x$的左端点只会在一个区间里，并且这个区间是从一个值为$x$点的下一个点，到下一个值为$x$的点。

这样可以先求出一个数组$Next[i]$表示跟$s[i]$相同的下一个元素下标，然后令数组$Rid[i]$表示这段区间的右端点，$Lid[i]+1$表示这段区间左端点，这样在这两个数组更新的时候$Lid[i]$就等于上一个$Rid[i]$，特别的，初始时候这个$Rid[i]$表示第一个区间的右端点。

这样就从左到右扫描右端点，当扫描到$i$的时候，若从$1$到$i$中$s[i]$出现次数等于$s[i]$，那么就跳到$s[i]$的第一个区间，若出现次数大于$s[i]$，那个就跳到下一个区间，这样对于左端点，就是查询这个左端点被多少个区间包含，这可以用线段树来维护。

特别的，如果一个元素$x$大于$n$，那么一共$n$个数，一定不会出现$x$次，那么就可以直接忽略掉他，这里可以将它改为$n+1$，这样既不会对统计过程造成影响，也不会数组越界。

code:

```c
#include<stdio.h>
#include<string.h>
struct node{
	long long s,Flag;
}a[4000010];//线段树 
struct node2{
	int y,Next,s;
}b[2000010];int Lenb,Sta[1000010];//链表 
int Sl[1000010];//存储数列 
int Js[1000010];//i的出现次数 
long long Anss[1000010];//询问的答案 
int n,m;
int Last[1000010];
int Next[1000010];//下一个值为s[i]的下标 
int Rid[1000010],Lid[1000010];//区间左右端点 
int Read(){//快读 
	int res=0,zf=1;char ch;
	while((ch=getchar())<48||ch>57)if(ch=='-')zf=!zf;res=(ch^48);
	while((ch=getchar())>=48&&ch<=57)res=(res<<3)+(res<<1)+(ch^48);
	return zf?res:(-res);
}
int Merge(int x,int y,int s){//链表插入元素 
	b[++Lenb].y=y;
	b[Lenb].Next=Sta[x];
	Sta[x]=Lenb;
	b[Lenb].s=s;
	return 0;
}
int Add(int k,int l,int r,int x,int y,long long s){//线段树区间加s
	if(x>y||x>r||y<l)return 0;
	if(x<=l&&y>=r){
		a[k].s+=(r-l+1)*s;
		a[k].Flag+=s;
		return 0;
	}
	int Mid=(l+r)>>1;
	if(a[k].Flag){
		Add(k<<1,l,Mid,l,Mid,a[k].Flag);
		Add(k<<1|1,Mid+1,r,Mid+1,r,a[k].Flag);
		a[k].Flag=0;
	}
	Add(k<<1,l,Mid,x,y,s);
	Add(k<<1|1,Mid+1,r,x,y,s);
	a[k].s=a[k<<1].s+a[k<<1|1].s;
	return 0;
}
long long Find(int k,int l,int r,int x,int y){//线段树查询区间和 
	if(x>y||x>r||y<l)return 0ll;
	if(x<=l&&y>=r)return a[k].s;
	int Mid=(l+r)>>1;
	if(a[k].Flag){
		Add(k<<1,l,Mid,l,Mid,a[k].Flag);
		Add(k<<1|1,Mid+1,r,Mid+1,r,a[k].Flag);
		a[k].Flag=0;
		a[k].s=a[k<<1].s+a[k<<1|1].s;
	}
	return Find(k<<1,l,Mid,x,y)+Find(k<<1|1,Mid+1,r,x,y);
}

int main(){
	n=Read();m=Read();
	for(int i=1;i<=n;i++){
		Sl[i]=Read();
		if(Sl[i]>n)Sl[i]=n+1;
	}
	for(int i=n;i>=1;i--){//预处理Next,和第一个区间的Rid 
		Next[i]=Last[Sl[i]];
		Last[Sl[i]]=i;
		Rid[Sl[i]]=i;
	}
	for(int i=1;i<=m;i++){
		int x=Read();int y=Read();
		Merge(y,x,i);
	}
	for(int i=1;i<=n;i++){
		Js[Sl[i]]++;
		if(Js[Sl[i]]==Sl[i]){//将区间加入 
			Add(1,1,n,1,Rid[Sl[i]],1);
		}else if(Js[Sl[i]]>Sl[i]){//区间跳到下一个 
			Add(1,1,n,Lid[Sl[i]]+1,Rid[Sl[i]],-1);//先删除现有区间 
			Lid[Sl[i]]=Rid[Sl[i]];
			Rid[Sl[i]]=Next[Rid[Sl[i]]];
			Add(1,1,n,Lid[Sl[i]]+1,Rid[Sl[i]],1);//再加入新区间 
		}
		for(int j=Sta[i];j;j=b[j].Next){
			Anss[b[j].s]=Find(1,1,n,b[j].y,b[j].y);//询问 
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",Anss[i]);//输出结果 
	return 0;
}
```






---

## 作者：My_666 (赞：2)

## 莫队

莫队的板子题。

但是 $ 1 <= ai <= 10^9 $，所以将 $ai$ 作为下标显然是不行的，常规办法就是离散化，但是本人~~懒得写~~离散化……

然而我们可以发现本题统计的信息为有多少个数 $x$，其出现次数也为 $x$，并且$ 1 <= n <= 10^5 $，显然一个数最多出现 $x$ 次，所以 $if(ai > n) $ $return;$ 就行了。

其他详见代码注释——

## 代码如下：


```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

#define ms(a) memset(a, 0, sizeof(a))

template<class T> void read(T &x) {
	x = 0; ll f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {f |= (ch == '-'); ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	x = f ? -x : x;
	return;
}

ll n, m, siz, a[N], pos[N];

struct query {ll l, r, num;} q[N];

bool cmp(query a, query b) {
	return pos[a.l] == pos[b.l] ? a.r < b.r : pos[a.l] < pos[b.l];
}

ll ans[N], now, cnt[N];//ans[]统计答案，cnt[]统计次数，now计数器

void add(ll x) {
	if (a[x] > n) return; //直接return，防止数组越界
	if(cnt[a[x]] == a[x]) now--; //如果加入这个数之前符合条件，那么加入后绝对不符合，直接减去
 	cnt[a[x]]++;//次数++
	if (cnt[a[x]] == a[x]) now++;//如果加入后符合条件，计数器++；
}

void del(ll x) {
	if (a[x] > n) return; //同上
	if(cnt[a[x]] == a[x]) now--;
	cnt[a[x]] --;
	if(cnt[a[x]] == a[x])
	now++;
}

int main() {
	read(n), read(m);
	//分块，减少时间复杂度。
	siz = sqrt(n);
	for (ll i = 1; i <= n; i++) {
		read(a[i]);
		pos[i] = i / siz;
	}
	for (ll i = 1; i <= m; i++) {
		read(q[i].l), read(q[i].r);
		q[i].num = i;
	}
	sort(q + 1, q + 1 + m, cmp);
	//莫队板子
	ll l = 1, r = 0;
	for (ll i = 1; i <= m; i++) {
		while (q[i].l < l) add(--l);
		while (q[i].r > r) add(++r);
		while (q[i].l > l) del(l++);
		while (q[i].r < r) del(r--);
		ans[q[i].num] = now;
	}
	for (ll i = 1; i <= m; i++) cout << ans[i] << "\n";
	return 0;
}
```

### 感谢阅读！


---

## 作者：Godのfather (赞：2)

## （〇）写在前面的话

~~感谢公开赛让我发现了一道这么好的题。~~

## （一）考场思路

第一眼看到题：好难呀，怎么做？

第二眼看到题：貌似离线下来可以莫队水过？

第三眼看到题：$10^6$的数据范围莫队直接暴毙（指算法）。

先讲一下莫队的思路。首先按照套路，将所有询问离线下来，分块。然后就是莫队的模板题了，左右指针各种移动，对答案加加减减即可。

理论时间复杂度$\Theta(N\sqrt N)$

给出代码（成功卡过了$10^6$的数据）：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int w = 0, f = 1; char ch = getchar();
	while(ch < '0' or ch > '9') {if(ch == '-') f = -f; ch = getchar();}
	while(ch >= '0' and ch <= '9') w = w*10 + ch - '0', ch = getchar();
	return w*f;
}
const int maxn = 1e6 + 5;
int N, M, a[maxn], belong[maxn], ans[maxn], sum, cnt[maxn];
struct Question{
	int l, r, id;
}q[maxn];
bool cmp(Question x, Question y){
	return (belong[x.l]^belong[y.l])?belong[x.l]<belong[y.l]:(belong[x.l]%2?x.r<y.r:x.r>y.r);
}
inline void add(int x){
	if(x > N) return ;
	if(!(cnt[x]^x)) sum --;
	cnt[x] ++;
	if(!(cnt[x]^x)) sum ++;
}
inline void del(int x){
	if(x > N) return ;
	if(!(cnt[x]^x)) sum --;
	cnt[x] --;
	if(!(cnt[x]^x)) sum ++;
}
int main(){
	N = read(), M = read();
	for(int i=1; i<=N; i++) a[i] = read();
	for(int i=1; i<=M; i++){
		int l = read(), r = read();
		q[i] = (Question){l, r, i};
	}
	int len = 1620, bnum = ceil((double)N/len);
	for(int i=1; i<=bnum; i++) for(int j=(i-1)*len+1; j<=min(i*len, N); j++) belong[j] = i;
	sort(q+1, q+M+1, cmp);
	int l = 1, r = 0;
	for(int i=1; i<=M; i++){
		int ql = q[i].l, qr = q[i].r;
		while(l > ql) add(a[--l]);
		while(l < ql) del(a[l++]);
		while(r > qr) del(a[r--]);
		while(r < qr) add(a[++r]);
		ans[q[i].id] = sum;
	}
	for(int i=1; i<=M; i++) printf("%d\n", ans[i]);
	return 0;
}
```

其实在考场上并没有写莫队，理智告诉我，$10^6$莫队是不可能卡过去的。于是开始想$\Theta(N\log N)$的算法。

然后。。。T2就被爆破了。。。我的莫队!!!

## （二）爆破后思路

即使被爆破了，题还是要做的。于是开始用各种$\log $数据结构yy。

先将询问离线，按照左端点排序，固定左端点，考虑如何计算右端点造成的贡献。

如果左端点固定了，那么区间内某个数的数量只与右端点的位置有关。只需要判断右端点之前有多少个合法的数就行了。

如何统计有多少个合法的数呢？考虑一个合法的数对右端点造成的贡献。

假设$x$出现的位置分别为$d_1,d_2,...,d_n$，那么如果固定了左端点在$(d_{l-1},d_l]$，那么，$x$可以对在$[d_{l+x-1},d_{l+x})$的右端点造成贡献。所以用一个数据结构对$[d_{l+x-1},d_{l+x})$执行区间加操作即可。

同样的，当左端点移动的时候，只需要删除$[d_{l+x-1},d_{l+x})$的贡献，然后在增加新的贡献即可。

实际上，上述操作跟扫描线有相似的地方。

用树状数组维护即可。时间复杂度$\Theta(N\log N)$

代码（轻松跑过$10^6$）：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int w = 0, f = 1; char ch = getchar();
	while(ch < '0' or ch > '9') {if(ch == '-') f = -f; ch = getchar();}
	while(ch >= '0' and ch <= '9') w = w*10 + ch - '0', ch = getchar();
	return w*f;
}
const int maxn = 1e6 + 5;
struct Question{
	int l, r, id;
}q[maxn];
int N, a[maxn], c[maxn], Q;
bool cmp(Question x, Question y){
	return x.l < y.l;
}
void add(int x, int y){
	for(; x<=N+1; x += x&-x) c[x] += y;
}
int ask(int x){
	int ans = 0;
	for(; x; x -= x&-x) ans += c[x];
	return ans;
}
int ans[maxn], pointer[maxn], sum[maxn];
vector<int> head[maxn];
int main(){
	N = read(), Q = read();
	for(int i=1; i<=N; i++){
		a[i] = read();
		if(a[i] > N) continue;
		sum[a[i]] ++;
		if(sum[a[i]] == a[i]) add(i, 1), head[a[i]].push_back(i);
		else if(sum[a[i]] == a[i] + 1) add(i, -1), head[a[i]].push_back(i);
		else if(sum[a[i]] > a[i]) head[a[i]].push_back(i);
	}
	
	for(int i=1; i<=Q; i++){
		int l = read(), r = read(), id = i;
		q[i] = (Question){l, r, id};
	}
	sort(q+1, q+Q+1, cmp);
	int j = 1, tmp = 0;
	for(int i=1; i<=Q; i++){
		for(; j<q[i].l; j++){
			if(a[j] > N) continue;
			if(pointer[a[j]] < head[a[j]].size()){
				add(head[a[j]][pointer[a[j]] ++], -1);
				if(pointer[a[j]] < head[a[j]].size()) add(head[a[j]][pointer[a[j]]], 1);
			}
			if(pointer[a[j]] < head[a[j]].size()){
				add(head[a[j]][pointer[a[j]]], 1);
				if(pointer[a[j]]+1 < head[a[j]].size()) add(head[a[j]][pointer[a[j]]+1], -1);
			}
		}
		ans[q[i].id] = ask(q[i].r);
	}
	for(int i=1; i<=Q; i++) printf("%d\n", ans[i]);
	return 0;
}
```

## （三）总结

再次感谢良心出题人给了一道这么好的题。

---

## 作者：MuYC (赞：1)

#### 前言

表示这道题目，大家都没有利用好那256MB的空间 ~~(只是我的做法比较辣鸡，需要很多空间)~~

#### 思路

这道题未必需要什么**莫队**,**树状数组**,**线段树**,**分块**。

(用今天比赛的时候YY出来的题目的性质过的，貌似跟Kewth是一个思路欸，多了些解释，求过)

直接观察题目性质并且利用好256MB空间，然后用前缀和用 O($(q+n)\sqrt{2 * n}$)的时间 莽过去就行了。

这道题目有一个优秀的性质：

虽然给定的数的大小可能为 $10 ^ 9$。但是，并非所有数都是有用的，更加确切的说，实际上有用的数不超过 $\sqrt{2 * n}$  种。

此话怎讲（看起来我在搞玄学）？听我细细道来。

首先，如果一种数，（在整个区间中）其出现次数小于等于自己的大小，那么这个数铁定“没用”了，其无论如何也无法在答案中做出贡献，这样子的数，是肯定可以删掉的。

什么情况下被留下来的数最多？ 不难发现，当每个数的大小尽量小的时候才能留下来的数最多，倘若想留下尽可能多的数，其中的最优情况就是留下了$1$ ， $2$ ， $3$ , ... , $k$ ，根据等差数列求和公式，那么 $\frac{k*(k + 1)}{2} <= n$

这样子，留下来的 $k$ 个数最大就只能是 $\sqrt{2 * n}$  种了。这也是本人用的算法的最坏情况。

仔细计算，发现 $\sqrt{2 * n}$ 最大不会超过 $450$ ， 然后 $450$ * $10 ^ 5$ 的空间消耗大概是 $170MB$ 。 于是我浪得飞起，直接开上 $500 * 10^5$ 的前缀和数组。对于每一次查询，只需要枚举有多少种数被包含在这个区间内的数量**恰好**等于其大小即可。

于是我们就用空间复杂度: O($n\sqrt{2 * n}$) 时间复杂度: O($(q+n)\sqrt{2 * n}$) 的 ~~优秀~~ 乱搞做法过了这一题。

人菜话多，写得很长。就啰嗦到这里了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int sum[505][100005];//暴力开数组
const int MAXN = 100005;
int n,q;
int a[MAXN];
map <int ,int > book,vis;//这里是记录信息用的两个map
int New[MAXN],tot = 0;

inline int read()//这里是快读
{
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar());
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}

signed main()
{
    n = read(), q = read();
    for(int i = 1 ; i <= n;  i ++) 
    a[i] = read(),book[a[i]] ++,vis[a[i]] = 1;//这里是在统计信息
    
    for(int i = 1 ; i <= n ; i ++)
        if(book[a[i]] < a[i])
        vis[a[i]] = 0,a[i] = 0;//这里是在删去无用的数
 
    for(int i = 1 ; i <= n ; i ++)
        if(vis[a[i]] == 1) 
        tot ++ , New[tot] = a[i] , vis[a[i]] ++;//这里是在统计有用的数
        
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1 ; j <= tot ; j ++){
            sum[j][i] = sum[j][i - 1] ;
            if(New[j] == a[i])sum[j][i] ++;//统计前缀和
        }

    for(int i = 1 ; i <= q ; i ++){
        int l = read() , r = read();
        int Ans = 0;
        for(int j = 1 ; j <= tot ; j ++)
            if(sum[j][r] - sum[j][l - 1] == New[j])Ans ++;//暴力统计答案
        printf("%d\n",Ans);
    }
    return 0;
}
```

### 后话

我得承认我的做法比较劣(过不了今天的比赛题，比赛的时候还是老老实实写了莫队)，但是貌似这个题目是可以观察性质简单的过掉的，代码比较短。

还有一个性质，不知道怎么用。对于一个区间的询问，其答案小于等于$\sqrt{2 * len}$的，这个东西我不大知道怎么用，但是相信聪明的你某天路过看到的时候，说不定就能用上这个性质了。

(代码修正了一下，求管理通过)

---

## 作者：Durancer (赞：1)

#### 前言

- 这道题是打比赛的时候的一道题目，因为题目重了只好含泪切掉这道题。（有几个坑点QWQ）

#### 题目描述

- 给定一个长度为$n$的序列$a$

- 有$q$次询问，每一次询问这其中符合条件的数字种类有多少（就是没有重着的数字）

- 条件为:区间内$a_i$这个数出现的次数正好等于$a_i$自身的值

#### 思路分析

- 奇奇怪怪的思路

-  首先，我们进行离线操作，先把询问的区间给记录下来，然后根据左区间的序号按照升序排列（以下全为排好序后的区间）

- 其次，我们先处理好第一个区间内的值，将这个作为初始值进行处理

- 然后，我们就开始对$2-n$个区间开始操作

- 每次处理是，都是从前一个区间向着当前区间靠拢，然后在这个处理的过程中，直接判断是否当前的数符合条件，最后区间转移完，答案也就出来了

#### 正确性

- 那么这个方法如何证明正确性呢，我们想象一下，首先我们进行在一个区间内进行操作（为了方便选择第一个区间来做说明OVO）

![](https://cdn.luogu.com.cn/upload/image_hosting/lpvftgp5.png)

- 来看这个序列，模拟一下过程。

- 首先在这个序列中，在第$1$位的时候，$1$的个数被记录下来了，当前的数量符合条件，那么现在的$ans=1$，再看走到第$3$位的时候，这个情况就是$2$的个数正好符合条件了，那么把它给记录下来，此时的$ans=2$,然后最细节的地方就是到了$4$的位置的时候，就可以发现，这个时候$2$的数量超了，并且这个数的答案记录过，那么就在减去，并且把标记删除即可。

#### 坑点分析

- 第一个坑点就是如果你不看题目的话，你开了一个$1e6$的数组，那么你就会炸掉了，因为最大为$1e9$，因为长度最大就是一百万，那么我们在处理的过程中就把所有的大于一百万的数都给赋值成0即可，这样就避免了RE的情况

- 第二个坑点就是我这个算法的坑点，当进行一个区间移动的时候，也就是当右区间比原来区间大的时候，最后两个值合并的时候要记得特判一下，不然也会挂掉QWQ

#### 代码实现

```
#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<map>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1e6+9;
struct node{
	int l;
	int r;
	int num;//编号 
}q[N];
int lal=0,lar=0;//表示上次的区间长度
int Q;//询问 
int n;//序列长度 
int ans[N];//答案 
int vis[N];//标记 
int cnt[N];//计数 
int a[N];
int read()
{
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') w = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + ch - '0', ch = getchar();
	return s * w;
}
bool cmp(node a,node b)
{
	if(a.l!=b.l)
	return a.l<b.l;
	else return a.r<b.r;
}
void work(int x)
{
	//cout<<" No."<<x<<" l= "<<lal<<" r= "<<lar<<endl; 
	int l=q[x].l;
	int r=q[x].r;
	while(lal<l)//将原先左边的区间全部转移到现在的位置 
	{
		cnt[a[lal]]--;//把之前的全部减掉
		if(cnt[a[lal]]==a[lal])
		{
			if(vis[a[lal]]==0)
			{
				ans[q[x].num]++;
				vis[a[lal]]=1;//在线查找，如果有相同的，那么就直接加上 
			}
		}
		else if(cnt[a[lal]]!=a[lal])
		{
			if(vis[a[lal]]==1)//如果这个以前已经加上过了贡献，
			//但是现在他的答案已经不符合条件了，那么就直接扔掉 
			{
				ans[q[x].num]--;
				vis[a[lal]]=0;
			}
		}
		lal++;//不需要减去最后一个，这个没问题 
	}
	if(lar>r)
	while(lar>r)//如果上个区间的右端点比当前的要大，那么就缩小 
	{
		cnt[a[lar]]--;//把之前的全部减掉
		if(cnt[a[lar]]==a[lar])
		{
			if(vis[a[lar]]==0)
			{
				ans[q[x].num]++;
				vis[a[lar]]=1;//在线查找，如果有相同的，那么就直接加上 
			}
		}
		else if(cnt[a[lar]]!=a[lar])
		{
			if(vis[a[lar]]==1)//如果这个以前已经加上过了贡献，
			//但是现在他的答案已经不符合条件了，那么就直接扔掉 
			{
				ans[q[x].num]--;
				vis[a[lar]]=0;
			}
		}
		lar--;//最后一个不需要减去 
	}
	if(lar<r)//如果原先的右区间比现在的要小 
	{
		lar++;//转移到右边一点，因为原先的r点已经记录过了 
		while(lar<r)
		{
			cnt[a[lar]]++;//把现在的全部加上 
			if(cnt[a[lar]]==a[lar])
			{
				if(vis[a[lar]]==0)
				{
					ans[q[x].num]++;
					vis[a[lar]]=1;//在线查找，如果有相同的，那么就直接加上 
				}
			}
			else if(cnt[a[lar]]!=a[lar])
			{
				if(vis[a[lar]]==1)//如果这个以前已经加上过了贡献，
				//但是现在他的答案已经不符合条件了，那么就直接扔掉 
				{
					ans[q[x].num]--;
					vis[a[lar]]=0;
				}
			}
			lar++;
		}
		cnt[a[lar]]++;//把现在的全部加上 
		if(cnt[a[lar]]==a[lar])
		{
			if(vis[a[lar]]==0)
			{
				ans[q[x].num]++;
				vis[a[lar]]=1;//在线查找，如果有相同的，那么就直接加上 
			}
		}
		else if(cnt[a[lar]]!=a[lar])
		{
			if(vis[a[lar]]==1)//如果这个以前已经加上过了贡献，
			//但是现在他的答案已经不符合条件了，那么就直接扔掉 
			{
				ans[q[x].num]--;
				vis[a[lar]]=0;
			}
		}
	}
} 
int main()
{
	n=read();
	Q=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		if(a[i]>100000)
		a[i]=0;
	}
	for(int i=1;i<=Q;i++)
	{
		q[i].l=read();
		q[i].r=read();
		q[i].num=i;
	}
	sort(q+1,q+1+Q,cmp); 
//	for(int i=1;i<=n;i++)
//	{
//		cout<<"l= "<<q[i].l<<" r= "<<q[i].r<<" num= "<<q[i].num<<endl;
//	}
	for(int i=q[1].l;i<=q[1].r;i++)
	{
		cnt[a[i]]++; 
		if(cnt[a[i]]==a[i])//说明当前已经满足条件了
		{
			if(vis[a[i]]==0)//如果这个答案还没有统计过那么久记录下来 
			{
				ans[q[1].num]++;
				vis[a[i]]=1;//在线查找，如果有相同的，那么就直接加上 
			}
		}
		else if(cnt[a[i]]!=a[i])
		{
			if(vis[a[i]]==1)//如果这个以前已经加上过了贡献，
			//但是现在他的答案已经不符合条件了，那么就直接扔掉 
			{
				ans[q[1].num]--;
				vis[a[i]]=0;
			}
		} 
	}
	lal=q[1].l;
	lar=q[1].r;
	for(int i=2;i<=Q;i++) 
	{
		ans[q[i].num]=ans[q[i-1].num];//转换一下 
		work(i); 
	}	
	for(int i=1;i<=Q;i++)
	cout<<ans[i]<<endl;
	return 0;
}
```


---

## 作者：dsaykc233 (赞：1)

 来一发莫队QWQ 
 
 [题目戳我](https://www.luogu.com.cn/problem/CF220B)
 
 本题思路如下
1. 长度为n的序列分成sqrt(n)+1块，
1. 把所有询问[l,r]读入，然后以左端点l的块号从小到大排序
1. 同一块内的询问按照右端点r从小到大排序具体做的时候，第一个查询时暴力查询，得到答案t
1. 然后l在同块内的查询r只增不减,l的变化最多sqrt(n)，所以同块内的查询时间复杂度基本上为O(n)。

1. 查询到下一块时,r才可能减小，然后同块内又只增不减，l变化最多sqrt(n)。 则整体时间复杂度为O((n+m)sqrt(n))

别的话便不多说了，AC代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=100005;
int n,m,sz,a[M],cnt[M],t,ans[M];
struct node
{
    int le,ri,b,id;
}p[M];
bool cmp(node u,node v)
{
    if(u.b!=v.b) return u.b<v.b;
    return u.ri<v.ri;
}
void add(int x)
{
    if(a[x]>n)
    	return; //值大于n的不可能是答案，忽略
    if(cnt[a[x]]==a[x]) 
    	t--; //加入a[x]时a[x]已经是答案，加入a[x]后a[x]就不可能是答案了
    cnt[a[x]]++; //加入a[x]
    if(cnt[a[x]]==a[x]) 
    	t++; //加入a[x]后判断a[x]的次数cnt[a[x]]是否等于a[x]
}
void del(int x)
{
    if(a[x]>n) 
    	return; //值大于n的不可能是答案，忽略
    if(cnt[a[x]]==a[x]) 
    	t--;
    cnt[a[x]]--;
    if(cnt[a[x]]==a[x]) 
    	t++;
}
int main()
{
    scanf("%d%d",&n,&m);
    sz=int(sqrt(n)); //分块大小
    for(int i=1; i<=n; i++) 
    	scanf("%d",&a[i]);
    for(int i=1; i<=m; i++)
    {
        scanf("%d%d",&p[i].le,&p[i].ri);
        p[i].b=p[i].le/sz; //分块编号,左端点在块内暴力查找
        p[i].id=i;
    }
    sort(p+1,p+1+m,cmp);
    int l=0, r=0;
    for(int i=1; i<=m; i++)//调整l,r，使得l到p[i].le-1,r到p[i].ri
    { 
        while(r<p[i].ri) add(++r); //添加a[r+1]
        while(r>p[i].ri) del(r--); //去掉a[r]
        while(l>p[i].le-1) add(l--); //添加a[l]
        while(l<p[i].le-1) del(++l); //去掉a[l+1]
        ans[p[i].id]=t;
    }
    for(int i=1; i<=m; i++) 
    	printf("%d\n",ans[i]);
    return 0;
}
```


---

## 作者：YingLi (赞：0)

一种奇怪的暴力，复杂度近似$O(n\sqrt n)$？n=1e6可以碾过去的那种。

首先a[i]只有小于等于n的时候才可能有贡献。其次，a[i]越大，越难做出贡献，也就是说假如我离线询问，枚举右端点r，那么从1~r其实没多少a[i]是有可能给出贡献的。所以——维护到当前位置有哪些a[i]可能做出贡献，维护到当前位置有a[i]个a[i]的区间的左右端点，对每个询问判断是否刚好卡着a[i]的这个区间即可。

关于复杂度的话，假如打满从1开始的值能给出贡献，那么最多放$\sqrt n$个。加上如果数据随机的话，大的a[i]就会比较多，不产生贡献的a[i]也就相应多。

上代码——

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
#define maxn 1000006
using namespace std;
typedef long long ll;
int read() {
	int x = 0, f = 1, ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
	return x * f;
}

int n, Q, a[maxn], cnt[maxn], ans[maxn], st[maxn], tot = 0, nxt[maxn], lst[maxn], pre[maxn], lim[maxn], fst[maxn];
struct node {int l, id;};
vector<node> q[maxn];
signed main() {
	n = read(), Q = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1, l, r; i <= Q; i++) l = read(), r = read(), q[r].push_back({l, i});
	for(int i = 1; i <= n; i++) {
		if(a[i] <= n) {//过滤掉一部分
			if(!cnt[a[i]]) fst[a[i]] = i;
			nxt[lst[a[i]]] = i; pre[i] = lst[a[i]]; lst[a[i]] = i; cnt[a[i]]++;
			if(cnt[a[i]] == a[i]) st[++tot] = a[i], lim[a[i]] = fst[a[i]];
			else lim[a[i]] = nxt[lim[a[i]]];
		}//pre和nxt是前后指针，lim是左端点，st放合法的a[i]
		for(int j = 0; j < q[i].size(); j++) {
			register int l = q[i][j].l, id = q[i][j].id, res = 0;
			for(int k = 1; k <= tot; k++) if(lim[st[k]] >= l && pre[lim[st[k]]] < l) res++;
			ans[id] = res;
		}
	}
	for(int i = 1; i <= Q; i++) printf("%d\n", ans[i]);
	return 0;
}

```


---

## 作者：infinities (赞：0)

区间问题，加上可以用 $O(1)$ 统计答案方法，而且 $n,m\le 10^5$，就可以愉快使用莫队了。

$a_i\le 10^9$，可以发现只有 $a_i\le n$ 的 $a_i$ 才对答案有贡献。所以直接莫队。

每次添加/减少一个数的时候直接判断原先这个数是不是答案里的，和之后可不可以对答案产生贡献即可。

裸的莫队复杂度 $O(n\sqrt{n})$。

code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define rint regester int
const int maxn = 1e5 + 10;
const int INF = 1e9;
using namespace std;
int read(){int x = 0,f = 1; char ch = getchar(); while(ch < '0' || ch > '9'){if(ch == '-')f = -1; ch = getchar();}while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();} return x * f;}
int cnt[maxn], n, m, belongs[maxn], now, l = 1, r, num[maxn], bnum, len, ans[maxn];
struct node{int l, r, id;}q[maxn];
int cmp(node a, node b){return (belongs[a.l] ^ belongs[b.l]) ? belongs[a.l] < belongs[b.l] : a.r < b.r;}
void add(int x){
    if(num[x] > n)return;
	if(cnt[num[x]]++ == num[x])--now;
	if(cnt[num[x]] == num[x])++now;
}//添加时修改答案
void del(int x){
    if(num[x] > n)return;
	if(cnt[num[x]]-- == num[x])--now;
	if(cnt[num[x]] == num[x])++now;
}//删除时修改答案
signed main(){//朴素莫队
	n = read(), m = read();
	for(int i = 1; i <= n; i++)num[i] = read();
	for(int i = 1; i <= m; i++)q[i].l = read(), q[i].r = read(), q[i].id = i;
	len = sqrt(n);
	bnum = (int)((double)n / len + 0.5);
	for(int i = 1; i <= bnum; i++)for(int j = (i - 1) * len + 1; j <= i * len; j++)belongs[j] = i;
	sort(q + 1, q + 1 + m, cmp);
	for(int i = 1; i <= m; i++){
		int ql = q[i].l, qr = q[i].r;
		while(l > ql)add(--l);
		while(l < ql)del(l++);
		while(r < qr)add(++r);
		while(r > qr)del(r--);
		ans[q[i].id] = now;
	}
	for(int i = 1; i <= m; i++)cout << ans[i] << "\n";
}
```

---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/08/05/%E3%80%8E%E9%A2%98%E8%A7%A3%E3%80%8FCodeforces220B%20Little%20Elephant%20and%20Array)

### Solution

我们先看题目，发现只有查询，没有修改，所以可以用普通的莫队解决。

题目中的$a_i$的范围是$\in [1, 10^9]$，而数的总数的范围是$\in [1, 10^5]$，所以当这个数大于$10^5$了，这个数就不可能为所求的$x$忽略这个数后就不用进行离散化了。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN = 100005;
int n, m, nowans, a[MAXN], bl[MAXN], ans[MAXN], cnt[MAXN];
struct node {
    int l, r, id;
    bool operator < (const node &x) const {//排序的规则
        return bl[l] == bl[x.l] ? r < x.r : bl[l] < bl[x.l];
    }
} info[MAXN];
inline void add(int x) {
    if (a[x] > n) return ;//如果数值超了n的范围就退出
    if (cnt[a[x]] == a[x]) nowans--;
    cnt[a[x]]++;
    if (cnt[a[x]] == a[x]) nowans++;
}
inline void dec(int x) {
    if (a[x] > n) return ;
    if (cnt[a[x]] == a[x]) nowans--;
    cnt[a[x]]--;
    if (cnt[a[x]] == a[x]) nowans++;
}
int main() {
    scanf("%d%d", &n, &m);
    int block = (int)sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        bl[i] = i / block;
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &info[i].l, &info[i].r);//莫队是离线算法，需要记录询问的左右端点
        info[i].id = i;//记录每个询问的编号
    }
    sort(info + 1, info + m + 1);
    memset(cnt, 0, sizeof(cnt));
    int    l = 1, r = 0;
    for (int i = 1; i <= m; i++) {//莫队
        while (l < info[i].l) dec(l++);
        while (l > info[i].l) add(--l);
        while (r < info[i].r) add(++r);
        while (r > info[i].r) dec(r--);
        ans[info[i].id] = nowans;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：Seanq (赞：0)

**CF220B Little Elephant and Array**      
~~小小莫队~~    
`        
题目描述    
小象喜欢和数组玩。现在有一个数组a，含有n个正整数，记第i个数为ai      
现在有m个询问，每个询问包含两个正整数lj和rj(1<=lj<=rj<=n)，小象想知道在Alj到Arj之中有多少个数x，其出现次数也为x     
输入格式    
第一行n和m，n表示数组大小，m表示询问个数，下一行为数组的值，再下m行，每行两个数lj和rj，描述如题面    
输出格式     
共m行，每行一个数，表示答案    
`    
easy or not?        
其实很简单        
对于add操作，如果原本它是符合的，那么ans--；如果现在符合了，那么ans++     
对于del操作，如果原本它是符合的，那么ans--；如果现在符合了，那么ans++     
然后就是普通的莫队     
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
struct node{
    int l,r;
    int Rk;
}s[N];
int n,m;
int col[N];
int happen[N];
int b[N];
int l,r;
int u;
int ans=0;
int anw[N];
bool cmp(node x,node y){
    if(b[x.l]==b[y.l]) return x.r<y.r;
    return x.l<y.l;
}
int main(){
    while(~scanf("%d%d",&n,&m)){
        memset(anw,0,sizeof(anw));
        memset(happen,0,sizeof(happen));
        ans=0;
        u=sqrt(n);
        for(int i=1;i<=n;i++) b[i]=(i/u)+1;
        for(int i=1;i<=n;i++){
            scanf("%d",&col[i]);
            if(col[i]>n) col[i]=-1;//如果大于n了就肯定不能成为答案 
        }
        for(int i=1;i<=m;i++){
            scanf("%d%d",&s[i].l,&s[i].r);
            s[i].Rk=i;
        }
        sort(s+1,s+m+1,cmp);
        for(int i=1;i<=m;i++){
            if(i==1){
                for(int j=s[i].l;j<=s[i].r;j++){
                    happen[col[j]]++;
                    if(happen[col[j]]==col[j]) ans++;
                    if(happen[col[j]]==col[j]+1) ans--;
                }
                l=s[i].l;
                r=s[i].r;
            }
            else{
                while(l<s[i].l){
                    l++;
                    happen[col[l-1]]--;
                    if(happen[col[l-1]]==col[l-1]) ans++;
                    if(happen[col[l-1]]==col[l-1]-1) ans--;
                }
                while(l>s[i].l){
                    l--;
                    happen[col[l]]++;
                    if(happen[col[l]]==col[l]) ans++;
                    if(happen[col[l]]==col[l]+1) ans--;
                }
                while(r<s[i].r){
                    r++;
                    happen[col[r]]++;
                    if(happen[col[r]]==col[r]) ans++;
                    if(happen[col[r]]==col[r]+1) ans--;
                }
                while(r>s[i].r){
                    r--;
                    happen[col[r+1]]--;
                    if(happen[col[r+1]]==col[r+1]) ans++;
                    if(happen[col[r+1]]==col[r+1]-1) ans--;
                }
            }
            anw[s[i].Rk]=ans;
        }
        for(int i=1;i<=m;i++){
            printf("%d\n",anw[i]);
        }
    }
    return 0;
} 
```






---

