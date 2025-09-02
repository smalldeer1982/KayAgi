# [ABC242G] Range Pairing Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc242/tasks/abc242_g

$ 1,2,\dots,N $ と番号付けられた人が並んでおり、人 $ i $ は色 $ A_i $ の服を着ています。

以下の形式で表される $ Q $ 個のクエリに答えてください。

- 整数 $ l,r $ が与えられる。 人 $ l,l+1,\dots,r $ だけに着目したとき、同じ色の服を着た $ 2 $ 人からなるペアは最大何組作れるか答えよ。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 10^5 $
- $ 1\ \le\ Q\ \le\ 10^6 $
- $ 1\ \le\ A_i\ \le\ N $
- 各クエリについて、 $ 1\ \le\ l\ \le\ r\ \le\ N $

### Sample Explanation 1

$ A=(1,2,3,2,3,1,3,1,2,3) $ です。この入力には $ 6 $ 個のクエリが含まれます。 $ 1 $ 個目のクエリは $ (l,\ r)\ =\ (6,\ 10) $ です。人 $ 6 $ と人 $ 8 $ 、人 $ 7 $ と人 $ 10 $ を組にすることで、同じ色の服を着たペアを $ 2 $ 組作ることができます。 $ 2 $ 個目のクエリは $ (l,\ r)\ =\ (5,\ 8) $ です。人 $ 5 $ と人 $ 7 $ 、人 $ 6 $ と人 $ 8 $ を組にすることで、同じ色の服を着たペアを $ 2 $ 組作ることができます。 $ l=r $ であるようなクエリも与えられます。

## 样例 #1

### 输入

```
10
1 2 3 2 3 1 3 1 2 3
6
6 10
5 8
3 6
4 4
1 6
1 10```

### 输出

```
2
2
1
0
3
4```

# 题解

## 作者：Fireworks_Rise (赞：3)

# 分析题目

一道莫队的板子题 ~~（第一次发莫队的题解）~~。

分析题目，就是求出询问区间中所有相同颜色可以匹配出的对数之和，学过莫队的都知道，把每种颜色所出现的个数 $cnt_i\div 2$ 并相加即可。

比较板，浅浅贴上蒟蒻代码...

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,m,a[N],ans[N];
struct Question {
	int l,r;
	int id;
} q[N];
int cnt[N],res;
int blo[N],block;
bool cmp(Question x,Question y) {
	if(blo[x.l]!=blo[y.l]) return x.l<y.l;
	if(blo[x.l]&1) return x.r<y.r;
	return x.r>y.r;
}
inline void del(int x) {
	res-=cnt[a[x]]/2;
	--cnt[a[x]];
	res+=cnt[a[x]]/2;
}
inline void add(int x) {
	res-=cnt[a[x]]/2;
	++cnt[a[x]];
	res+=cnt[a[x]]/2;
}
signed main() {
	scanf("%lld",&n);
	block=sqrt(n);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		blo[i]=(i-1)/block+1;
	}
	scanf("%lld",&m);
	for(int i=1;i<=m;i++) {
		scanf("%lld%lld",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++) {
		int ql=q[i].l,qr=q[i].r;
		while(l>ql) add(--l);
		while(l<ql) del(l++);
		while(r>qr) del(r--);
		while(r<qr) add(++r);
		ans[q[i].id]=res;
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：_sh1kong_ (赞：1)

[In Luogu](https://www.luogu.com.cn/problem/AT_abc242_g)

### 做法
一道挺板子的莫队。

所谓莫队算法，其实就是暴力算法的优化。暴力算法是按询问的左右端点排序，然后暴力得到答案的，而莫队是把询问左右端点所属的块进行排序，再与暴力一样得到答案。优化后，时间复杂度变成了 $\mathcal{O(n \sqrt n)}$。

再回到这道题。我们将询问离线，分块，接着按左右端点属于的块进行排序，最后暴力得到答案。

code:

```cpp
#include <bits/stdc++.h>
#define int long long

const int N = 5e5 + 5, M = 1e6 + 5, MOD = 1000007;

using namespace std;

inline int read(){
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
} 

int n, m, len, res;

int f[N], cnt[N], ans[M];

struct query

{
	int l, r, id;
}q[M];

bool cmp (query x, query y)

{
	return (x.r / len) == (y.r / len) ? x.l < y.l : x.r < y.r;
}

void del(int k)

{
	res -= (cnt[f[k]] / 2);
	cnt[f[k]] --;
	res += (cnt[f[k]] / 2);
}

void add(int k)

{
	res -= (cnt[f[k]] / 2);
	cnt[f[k]] ++;
	res += (cnt[f[k]] / 2);
}

signed main()

{
	n = read();
	for (int i = 1; i <= n; i ++ ) f[i] = read();
	m = read();
	for (int i = 1, x, y; i <= m; i ++ ) 
	{
		x = read(), y = read();
		q[i] = {x, y, i};
	}
	len = n / (sqrt((m * 2 / 3)));
	sort(q + 1, q + m + 1, cmp);
	int l = 0, r = 0;
	for (int i = 1; i <= m; i ++ )
	{
		int ql = q[i].l, qr = q[i].r;
		while (l < ql) del(l ++);
		while (r > qr) del(r --);
		while (l > ql) add(-- l);
		while (r < qr) add(++ r);
		ans[q[i].id] = res;
	}
	for (int i = 1; i <= m; i ++ ) cout << ans[i] << '\n';
}
```

---

## 作者：lovely_hyzhuo (赞：0)

莫队板子？

首先，你需要了解 [莫队](https://oi-wiki.org/misc/mo-algo-intro/)。

然后，定义 $cnt_i$ 表示颜色 $i$ 的出现次数。

那么，最后的总数就是所有颜色的出现次数除以 $2$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int l,r;
	int id;
	int ans1,ans2;
}a[1000010];
int n,m;
int cnt[1000010];
int pos[1000010];
int sum;
int t;
int c[1000010];
void add(int col)
{
	sum-=cnt[col]/2;
	cnt[col]++;
	sum+=cnt[col]/2;
}
void cel(int col)
{
	sum-=cnt[col]/2;
	cnt[col]--;
	sum+=cnt[col]/2;
}
bool cmp1(node a,node b)
{
	return ((a.l-1)/t+1)==((b.l-1)/t+1)?a.r>b.r:((a.l-1)/t+1)<((b.l-1)/t+1);
}
int ans[1000010];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>c[i];
	t=sqrt(n);
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].l>>a[i].r;
		a[i].id=i;
	}
	sort(a+1,a+m+1,cmp1);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l>a[i].l)add(c[--l]);
		while(r<a[i].r)add(c[++r]);
		while(l<a[i].l)cel(c[l++]);
		while(r>a[i].r)cel(c[r--]);
		ans[a[i].id]=sum;
	}
	for(int i=1;i<=m;i++)
		cout<<ans[i]<<endl;
		
	return 0;
}
```


---

## 作者：WaterSun (赞：0)

# 思路

题目中有一个坑点，就是对于每一件衣服不能重复使用。

那么，对于每一个颜色为 $i$ 的衣服，所能得到的价值就是 $\lfloor \frac{cnt_i}{2} \rfloor$。（其中 $cnt_i$ 表示颜色 $i$ 的衣服的数量）

那么最终的答案就是 $\sum_{i = 1}^{+\infty}\lfloor \frac{cnt_i}{2} \rfloor$。

用普通莫队维护一下即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define pl(x) (x / mq.len)

using namespace std;

const int N = 1e5 + 10,M = 1e6 + 10;
int n,q;
int arr[N],ans[M];

struct array{
	int l;
	int r;
	int id;
}Q[M];

struct mqueue{
	int len,sum;
	int cnt[N];
	
	inline void add(int x){
		sum -= cnt[x] / 2;
		cnt[x]++;
		sum += cnt[x] / 2;
	}
	
	inline void del(int x){
		sum -= cnt[x] / 2;
		cnt[x]--;
		sum += cnt[x] / 2;
	}
	
	inline void f(){
		int l = 1,r = 0;
		for (re int i = 1;i <= q;i++){
			int ql = Q[i].l;
			int qr = Q[i].r;
			while (l > ql) add(arr[--l]);
			while (r < qr) add(arr[++r]);
			while (l < ql) del(arr[l++]);
			while (r > qr) del(arr[r--]);
			ans[Q[i].id] = sum;
		}
	}
}mq;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	mq.len = sqrt(n);
	for (re int i = 1;i <= n;i++) arr[i] = read();
	q = read();
	for (re int i = 1;i <= q;i++){
		Q[i].l = read();
		Q[i].r = read();
		Q[i].id = i;
	}
	sort(Q + 1,Q + q + 1,[](auto const &a,auto const &b){
		if (pl(a.l) != pl(b.l)) return pl(a.l) < pl(b.l);
		if (pl(a.l) & 1) return a.r < b.r;
		return a.r > b.r;
	});
	mq.f();
	for (re int i = 1;i <= q;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：highkj (赞：0)

# 思路
一眼就是莫队呀！那么我们就要用一个数组为 $cnt_i$ 以及一个 $l,r$ 为当前的区间左端点和右端点，那么 $cnt_i$ 就表示在 $l\sim r$ 区间中 $i$ 出现的次数，那么我们每次在区间扩大和区间缩小时就可以先将原来的减掉在加上改之后的总贡献，其实能配的对数就是 $cnt_i\div 2$，然后我们就用一个数组存下答案再输出即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define rep(ix,yy,y) for(int ix=yy;ix<=y;ix++)
#define int long long
using namespace std ;
const int N=2e6+10;
int a[N],aa[N],cnt[N];
struct node {
	int l,r,id;
} s[N];
int len,n,m,res;
bool cmp(node a,node b) {
	if(a.l/len!=b.l/len) return a.l<b.l;
	return a.l/len&1?a.r<b.r:a.r>b.r;
}
void add(int i) {
	res-=cnt[a[i]]/2;
	res+=(++cnt[a[i]])/2;
}
void del(int i) {
	res-=cnt[a[i]]/2;
	res+=(--cnt[a[i]])/2;
}
signed main() {
	cin>>n;
	rep(i,1,n) cin>>a[i];
	cin>>m;
	len=sqrt(n); //块长 
	rep(i,1,m) {
		cin>>s[i].l>>s[i].r;
		s[i].id=i;
	}
	sort(s+1,s+1+m,cmp); 
	int l=1,r=0;
	rep(i,1,m) {
		while(l>s[i].l) add(--l); //区间扩大 
		while(r<s[i].r) add(++r);
		while(l<s[i].l) del(l++);//区间缩小 
		while(r>s[i].r) del(r--);
		aa[s[i].id]=res;
	}
	rep(i,1,m) cout<<aa[i]<<endl;
	return false;
}
```

---

## 作者：CQ_Bab (赞：0)

# 思路
~~莫队裸题一道呀~~ ，我们可以用一个数组为 $cnt_i$ 记录 $i$ 在当前区间内出现的次数，然后我们就还是要定义一个 $l$ 和 $r$ 代表当时的区间的左右端点，然后我们还是用暴力转移就是我们可以处理出来 $l$ 和当前左端点的相对位置然后移动，$r$ 也同理。然后我们在移动时可以用两个函数来更新答案，就是将原来的减去加上新的即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define rep(ix,yy,y) for(int ix=yy;ix<=y;ix++)
#define int long long
using namespace std ;
const int N=1e6+10;
int a[N],ans[N],cnt[N];
struct node{
	int l,r,id;
}s[N];
int len,n,m,res;
bool cmp(node a,node b) {
	if(a.l/len!=b.l/len) return a.l<b.l;
	return a.r<b.r;
}
void add(int i) { //加入
	res-=cnt[i]/2;
	cnt[i]++;
	res+=(cnt[i])/2;
}
void del(int i) { //删除
	res-=cnt[i]/2;
	cnt[i]--;
	res+=(cnt[i])/2;
}
signed main() {
	cin>>n;
	rep(i,1,n) cin>>a[i]	;
	cin>>m;
	len=sqrt(n);
	rep(i,1,m) {
		cin>>s[i].l>>s[i].r;
		s[i].id=i;
	}
	sort(s+1,s+1+m,cmp); //排序
	int l=1,r=0;
	rep(i,1,m) {
		while(l>s[i].l) add(a[--l]);
		while(r<s[i].r) add(a[++r]);
		while(l<s[i].l) del(a[l++]); //相对位置
		while(r>s[i].r) del(a[r--]);
		ans[s[i].id]=res;
	}
	rep(i,1,m) cout<<ans[i]<<endl;
	return false;
}
/*
10
1 2 3 2 3 1 3 1 2 3
6
6 10
5 8
3 6
4 4
1 6
1 10
*/
```

---

## 作者：CQ_Bob (赞：0)

## 分析

莫队模板。

我们定义 $\mathit{cnt}_{i}$ 表示在当前区间内数字 $i$ 出现的个数。因为是两两匹配，所以对于某个 $i$，其在当前区间内能组成的最大组数就是 $\left\lfloor\dfrac{\mathit{cnt}_{i}}{2}\right\rfloor$，之后的套模板就行啦。

注：在更新 $\mathit{cnt}_{i}$ 的时候，如果不对式子加以优化（像我一样），那么就需要先删除旧的价值，在更新新的价值哦。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+10;
int ans;
int n,m;
struct node1{
	int l,r,id;
}q[N];
int c[N],cnt[N];
int b[N];
bool cmp(node1 a,node1 b){
	int len=sqrt(n);//最优块长 s=sqrt(n) 
	if(a.l/len!=b.l/len){
		return a.l<b.l;
	}
	else{
		return a.r<b.r;
	}
}
void add(int x){
	if(cnt[x]>=2){//除旧 
		ans-=cnt[x]/2;
	}
	cnt[x]++;
	if(cnt[x]>=2){//迎新 
		ans+=cnt[x]/2;	
	}
}
void del(int x){
	if(cnt[x]>=2){
		ans-=cnt[x]/2;
	}
	cnt[x]--;
	if(cnt[x]>=2){
		ans+=cnt[x]/2;	
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		int l,r;cin>>l>>r;
		q[i].id=i,q[i].l=l,q[i].r=r;
	}
	sort(q+1,q+m+1,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l>q[i].l) add(c[--l]);//顺序可以改变的，但是有些不行 
		while(r<q[i].r) add(c[++r]);
		while(l<q[i].l) del(c[l++]);
		while(r>q[i].r) del(c[r--]);
		b[q[i].id]=ans;//记录答案 
	}
	for(int i=1;i<=m;i++){
		cout<<b[i]<<"\n";
	}
	return 0; 
}
```


---

## 作者：happybob (赞：0)

莫队板子。若 $i$ 出现 $c_i$ 次，我们能要求的是 $\sum \limits_{i \in \mathbb{N}} \lfloor \frac{c_i}{2} \rfloor$。

简单莫队维护即可，复杂度 $O(q \sqrt n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int bel[N], ans[N];

struct Query
{
	int id, l, r;
	bool operator<(const Query& g) const
	{
		return (bel[l] ^ bel[g.l] ? bel[l] < bel[g.l] : (bel[l] & 1 ? r < g.r : r > g.r));
	}
}p[N];

int n, q, a[N], cnt[N], res;

inline void add(int x)
{
	res -= cnt[a[x]] / 2;
	cnt[a[x]]++;
	res += cnt[a[x]] / 2;
}

inline void del(int x)
{
	res -= cnt[a[x]] / 2;
	cnt[a[x]]--;
	res += cnt[a[x]] / 2;
}

int main()
{
	scanf("%d", &n);
	int s = (int)sqrt(n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), bel[i] = i / s;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		p[i] = { i, l, r };
	}
	sort(p + 1, p + q + 1);
	int nl(1), nr(0);
	for (int i = 1; i <= q; i++)
	{
		int l = p[i].l, r = p[i].r;
		while (nl > l) add(--nl);
		while (nr < r) add(++nr);
		while (nl < l) del(nl++);
		while (nr > r) del(nr--); 
		ans[p[i].id] = res;
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0; 
}
```


---

## 作者：AlicX (赞：0)

### 前言

我的第一篇莫队题解。

翻译差评，我把题目意思理解为了颜色相同的最多的个数，然后又理解成了选出两人组。~~好吧或许是我太菜了。~~

## Solution

题目其实是要我们求出在一段区间内的每种颜色除以二的和，发现一个显然的性质：当我们知道了一个点的答案，我们可以将答案扩散到与它相邻的区间，于是考虑莫队做，维护一个 $sum$ 表示区间答案，每次移动端点时进行更新。

值得注意的是莫队的循环顺序，需要保证 $l \leq r$，否则会出现一个数被添加负数次的情况。

还有一个莫队小优化：当我们进行左端点排序后，一般都是直接将右端点从小到大排，但是这样在跨区间时右端点的移动会达到 $O(n)$，所以我们进行奇偶排序：当处于奇数段的右端点从小往大，偶数段的从大往小，这样就会形成波浪形，达到最优，大概优化了 30% 左右。 

### AC Code

```cpp
// Celestial Cyan 
// Luogu uid : 706523 
// Luogu : https://www.luogu.com.cn/problem/AT_abc242_g
// CF : 
// AT : https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc242_g	
// FTOJ : 
// Contest : AtCoder Beginner Contest 242
// Cnblogs : 
// Memory Limit: 1 GB 
// Time Limit: 5000 ms 
// 2023/6/17     

#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
#define il inline 
#define db double
#define low(x) x&-x
#define ls(x) x<<1
#define rs(x) x<<1|1 
#define pb(x) push_back(x)
#define gcd(x,y) __gcd(x,y) 
#define lcm(x,y) x*y/gcd(x,y) 
#define debug puts("-------")  
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> PII; 
const int N=1e6+10,INF=1e9+7;  
int n,m;
int ans[N]; 
int sum=0,len; 
int a[N],cnt[N],mp[N]; 
struct Mind{ 
	int l,r,id; 
	il bool operator<(Mind &Cyan)const{
		if(l/len!=Cyan.l/len) return l<Cyan.l;
		return (l/len)&1?r<Cyan.r:r>Cyan.r; 
	} 
}q[N];  
il int read(){ 
	int x=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){ if(c=='-') f=-1; c=getchar(); }
	while(c>='0'&&c<='9'){ x=(x<<3)+(x<<1)+c-48; c=getchar(); }
	return x*f;
} 
il void add(int x){ 
	sum-=cnt[x]/2;
	cnt[x]++; sum+=cnt[x]/2;    
} 
il void del(int x){ 
	sum-=cnt[x]/2;
	cnt[x]--; sum+=cnt[x]/2; 
}
signed main(){ 
	n=read(); len=sqrt(n);
	for(int i=1;i<=n;i++) a[i]=read(); m=read(); 
	for(int i=1;i<=m;i++) q[i].l=read(),q[i].r=read(),q[i].id=i; 
	sort(q+1,q+m+1); int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(l>q[i].l) add(a[--l]);
		while(r<q[i].r) add(a[++r]);
		while(l<q[i].l) del(a[l++]);
		while(r>q[i].r) del(a[r--]);
		ans[q[i].id]=sum; 
	} for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);  
	return 0;
} /* */
```


---

