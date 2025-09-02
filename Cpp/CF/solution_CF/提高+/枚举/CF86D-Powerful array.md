# Powerful array

## 题目描述

An array of positive integers $ a_{1},a_{2},...,a_{n} $ is given. Let us consider its arbitrary subarray $ a_{l},a_{l+1}...,a_{r} $ , where $ 1<=l<=r<=n $ . For every positive integer $ s $ denote by $ K_{s} $ the number of occurrences of $ s $ into the subarray. We call the power of the subarray the sum of products $ K_{s}·K_{s}·s $ for every positive integer $ s $ . The sum contains only finite number of nonzero summands as the number of different values in the array is indeed finite.

You should calculate the power of $ t $ given subarrays.

## 说明/提示

Consider the following array (see the second sample) and its \[2, 7\] subarray (elements of the subarray are colored):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86D/5e3c36b108711f9f95c3c3519472e9f583328f8b.png) Then $ K_{1}=3 $ , $ K_{2}=2 $ , $ K_{3}=1 $ , so the power is equal to $ 3^{2}·1+2^{2}·2+1^{2}·3=20 $ .

## 样例 #1

### 输入

```
3 2
1 2 1
1 2
1 3
```

### 输出

```
3
6
```

## 样例 #2

### 输入

```
8 3
1 1 2 2 1 3 1 1
2 7
1 6
2 7
```

### 输出

```
20
20
20
```

# 题解

## 作者：ykuouzf (赞：11)

### 分块做法

虽说该题的正解应该是莫队，但在多数情况下，莫队能解决的问题分块也都能解决（当然指的是在时间足够宽裕的情况下

先用$O(n \sqrt n)$的时间预处理出每个块内各个数出现的次数及答案（具体代码中用前缀和维护），用 $s[i][j]$ 表示第 $i$ 块内 $j$ 数出现的次数，$pre[i][j]$ 表示从第 $i$ 块到第 $j$ 块这一区间的答案

处理询问时，如果 $i$ 和 $j$ 在同一块内，直接暴力统计答案，否则就先记答案为中间整块的答案，对两端的散块造成的影响暴力统计

统计时，考虑到当 $tot[a[i]]$ 变为 $ tot[a[i]] + 1$ 时:

$ans = a[i] * (tot_{a[i]} + 1) ^ 2 - tot_{a[i]} ^ 2 $
$ = a[i] * (2 * tot_{a[i]} + 1) $

时间： $O(n \sqrt n)$ , 空间： $\sqrt n * \sum Max_{a[i]}$

你以为到这就结束了？？？

实际写时，这样的代码是会MLE的，开不下那么大的空间

故此我加了一个离散化：

```
for (int i = 1; i <= n; i++) {
	if (!v[a[i]]) {
		c[++m] = a[i]; b[a[i]] = m;
		v[a[i]] = 1;
	} a[i] = b[a[i]];
}
```
优化后的空间： $n\sqrt n $

这样是勉强不会MLE了，但可惜的是，它T了

然后~~玄学调了一波块长~~，在MLE和TLE之间反复横跳了几次才过$qwqwq$

时间限制：5.00s

最大用时：4.93s

空间限制：250.00MB

所用空间：243.49MB

~~大家千万不要学我啊还是老实写莫队吧~~

## Code：
```
#include <bits/stdc++.h>
#define ll long long

int read() {
	int j; char c;
	for (c = getchar(); !isdigit(c); c = getchar());
	for (j = 0; isdigit(c); j = j * 10 + c - 48, c = getchar());
	return j;
}

void write(ll x) {
	char c[20]; int l = 0;
	do { c[++l] = x % 10 + 48; x /= 10; } while (x);
	do { putchar(c[l--]); } while (l);
	putchar('\n');
}

const int N = 2e5 + 10;
const int block = 670; //这里开到650以下会MLE，开到700以上会TLE（开到700时最大一个点耗时4.99s 
const int A = 1e6 + 10; 

int n, m, q, cnt;
int a[N], b[A], c[N], pos[N], l[N], r[N], tot[N], v[A];
int s[300][N];
ll pre[500][500];

signed main() {
	n = read(); q = read();
	cnt = n / block + (n % block != 0);
	for (int i = 1; i <= n; i++) {
		a[i] = read(); pos[i] = (i - 1) / block + 1;
	}
	for (int i = 1; i <= n; i++) {
		if (!v[a[i]]) {
			c[++m] = a[i]; b[a[i]] = m;
			v[a[i]] = 1;
		} a[i] = b[a[i]];
	}
	for (int i = 1; i <= cnt; i++) {
		l[i] = r[i - 1] + 1;
		r[i] = r[i - 1] + block;
	} r[cnt] = n;
	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= N - 10; j++) { s[i][j] = s[i - 1][j]; }
		for (int j = l[i]; j <= r[i]; j++) { s[i][a[j]]++; }
	}
	for (int i = 1; i <= cnt; i++) {
		memset(tot, 0, sizeof tot);
		for (int j = i; j <= cnt; j++) {
			pre[i][j] = pre[i][j - 1];
			for (int k = l[j]; k <= r[j]; k++) {
				pre[i][j] += 1ll * c[a[k]] * (2 * tot[a[k]] + 1);
				tot[a[k]]++;
			}
		}
	}
	while (q --> 0) {
		int L = read(), R = read();
		ll ans;
		if (pos[L] == pos[R]) { ans = 0;
			for (int i = L; i <= R; i++) { tot[a[i]] = 0; }
			for (int i = L; i <= R; i++) { ans += 1ll * c[a[i]] * (2 * tot[a[i]]++ + 1); }
		} else {
			ans = pre[pos[L] + 1][pos[R] - 1];
			for (int i = L; i <= r[pos[L]]; i++) { tot[a[i]] = 0; }
			for (int i = l[pos[R]]; i <= R; i++) { tot[a[i]] = 0; }
			for (int i = L; i <= r[pos[L]]; i++) {
				ans += 1ll * c[a[i]] * (2 * (s[pos[R] - 1][a[i]] - s[pos[L]][a[i]] + tot[a[i]]++) + 1);
			}
			for (int i = l[pos[R]]; i <= R; i++) {
				ans += 1ll * c[a[i]] * (2 * (s[pos[R] - 1][a[i]] - s[pos[L]][a[i]] + tot[a[i]]++) + 1);
			}
		}
		write(ans);
	}
	return 0;
}
```



---

## 作者：cyffff (赞：11)

# CF86D Powerful array
#### [_传送门_](https://www.luogu.com.cn/problem/CF86D)
蒟蒻刚学莫队，找题做，~~结果被块长卡了一个中午$RE$#$55$~~，~~顺便拿了个最优解~~
## 思路
给出 $n,q,a_{1,2,...,n}$,每次询问给出$l$、$r$，$cnt_i$ 为 $l$、$r$ 区间中 $i$ 出现的次数，求 $\sum_icnt_i\times i$。

区间询问，考虑莫队维护。

莫队就是维护 $L,R$ ，对于每次询问跳到正确的区间处理的~~暴力~~算法，如果还不会右转[P3901](https://www.luogu.com.cn/problem/P3901)。

此题与 $P3901$ 类似，也是拿一个 $cnt$ 数组存当前 $L,R$ 区间中 $i$ 的出现次数，考虑插入 $i$，由平方差公式得

$$ans={(cnt_i+1)}^2\times i-{cnt_i}^2\times i+ans=((cnt_i+cnt_i+1)\times (cnt_i-cnt_i+1))\times i+ans=(2\times cnt_i+1)\times i+ans$$

删除同理，转换符号即可。

接下来就是莫队基本操作了，$sz$ 作为块长取 $\frac{n}{\sqrt{\frac{3}{2}m}}+1$（因为#$55$中 $n<\sqrt{\frac{3}{2}m}$，导致出现 $sz$ 为 $0$ 的情况，得$+1$）最快。按照 $sz$ 进行奇偶排序，然后暴力跳 $L,R$ 就行了，具体见下代码内容。

$AC\;Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//IO优化
	int len=0;
	char ibuf[(1<<20)+1],*iS,*iT,out[(1<<25)+1];
	#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
//  #define gh() getchar()
	#define reg register
	inline int read(){
		reg char ch=gh();
		reg int x=0;
		while(ch<'0'||ch>'9') ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return x;
	}
	inline void write(ll x){
		if(x>9)write(x/10);
		out[len++]=x%10+48;
	}
}using namespace IO;
int n,m,k,curL=1,curR,sz,cnt[1000001],a[200001];//具体意义见上
ll g[200001],ans;//g_i表示第i次询问的答案
struct que{
	int id,l,r;
	friend bool operator<(const que &a,const que &b){
		return a.l/sz^b.l/sz?a.l<b.l:a.l/sz&1?a.r<b.r:a.r>b.r;//奇偶排序
	}
}ask[200001];//询问
inline void add(int p){//加
	cnt[a[p]]++,ans+=(2*cnt[a[p]]-1)*a[p];
}
inline void del(int p){//删
	cnt[a[p]]--,ans-=(2*cnt[a[p]]+1)*a[p];
}
int main(){
	n=read();
	m=read();
	sz=n/sqrt(m*2/3)+1;//块长
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<=m;i++){
		int l=read(),r=read();
		ask[i]={i,l,r};
	}
	sort(ask+1,ask+m+1);//离散化
	for(int i=1;i<=m;i++){
		int L=ask[i].l,R=ask[i].r;
		while(curL>L) add(--curL);
        while(curR<R) add(++curR);
		while(curL<L) del(curL++);
        while(curR>R) del(curR--);
        g[ask[i].id]=ans;
	}
	for(int i=1;i<=m;i++){
		write(g[i]);
		out[len++]='\n';
	}
	fwrite(out,1,len,stdout);
    return 0;
}
/*
Time:18.14s
Memory:41.48MB
*/
```
那这就再见了 $qwq$~

---

## 作者：maowuyou (赞：5)

# 又将是一道经典的莫队
~~感谢莫涛大队长的算法(不该乱奶)~~
## 话不多说，我们进入正题

 [题目传送器](https://www.luogu.org/problem/CF86D)

~~题目翻译给得很有良心，概括得很全面~~

由于没有修改，可以离线，很容易想到莫队

我们考虑如何左右移动指针 l 和 r 

考虑我们现在已经得出了一个当前 l 、 r 的答案——sum

在该区间中 ，值为 x 的数 出现的个数 被 c[x] 统计

假设我们现在要加入一个数 a[i] 

很明显 我们需要统计 c[a[i]] 在得到 a[i] 后 对答案的贡献 

我介绍两种方法 

          1.运用完全平方公式 (a+b)^2 = a^2 + 2ab + b^2
        
   	      对于 a[i] 出现的次数 c[a[i]] 
          
          它原本对答案的贡献为 c[a[i]]^2
          
          现在它增加为 c[a[i]]+1
          
          他对答案的贡献改为 (c[a[i]]+1)^2
          
          展开得 c[a[i]]^2 + 2*c[a[i]] + 1
          
          由于我们现在只统计了 c[a[i]]^2 
          
          所以 还要加上 2*c[a[[i]] + 1 就行了
          
        2.既然原来的 c[a[i]] 已经过时了 
        
          那么就直接将他的贡献减去 
        
          加入 c[a[i]]+1 对答案的贡献

两种方法都是 O(1) ，可以采用  ，个人认为第二种更好理解

剩下的就是一些普遍的东西了 

先读入 ， 再奇偶性排序 ， 然后跑莫队
        
代码也不长 1.1KB 左右 
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#define MAXN 1000005
#define LL long long 
using namespace std;
LL sum,a[MAXN],ans[MAXN],c[MAXN];
int n,m,L,R,pos[MAXN];
struct ques
{
	int l,r;
	int id;
}f[MAXN];
bool cmp(const ques k,const ques t)
{
	if (pos[k.l]==pos[t.l]) return k.r<t.r;
	return k.l<t.l; 
}
void add(int x)
{
    sum-=c[a[x]]*c[a[x]]*a[x];
    c[a[x]]++;
    sum+=c[a[x]]*c[a[x]]*a[x];
}
void del(int x)
{
    sum-=c[a[x]]*c[a[x]]*a[x];
    c[a[x]]--;
    sum+=c[a[x]]*c[a[x]]*a[x];
}
void que(int l,int r)
{
	while (L<l) del(L++);
	while (L>l) add(--L);
	while (R<r) add(++R);
	while (R>r) del(R--);
	return;
}
int main()
{
	scanf("%d %d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	int len=sqrt(n);
	for (int i=1;i<=n;i++) pos[i]=(i-1)/len+1; 
	for (int i=1;i<=m;i++)
	{
		scanf("%d %d",&f[i].l,&f[i].r);
		f[i].id=i;
	}
	sort(f+1,f+m+1,cmp);
	L=1;
	R=0;
	sum=0;
	for (int i=1;i<=m;i++)
	{
		que(f[i].l,f[i].r);
		ans[f[i].id]=sum;
	}
	for (int i=1;i<=m;i++) printf("%lld\n",ans[i]);
	return 0;
} 
```
这是一道很基础的序列莫队 

建议接下去可以做一做 [小Z的袜子](https://www.luogu.org/problem/P1494)（序列莫队） 或 [数颜色 / 维护队列](https://www.luogu.org/problem/P1903)（待修莫队）

---

## 作者：Presentation_Emitter (赞：3)

这是莫队算法的裸题。关于莫队的介绍见[这篇blog](https://www.cnblogs.com/WAMonster/p/10118934.html)。

一般可用莫队做的题满足以下条件：

1. 离线。（其实是有在线莫队的，见洛谷日报 183 期）
2. 将已处理的区间由 $[l,r]$ 转移为 $[l \pm 1,r]$ 或 $[l,r \pm 1]$ 是 $\Theta(1)$ 的。

本题要求求出出现次数的平方乘以其出现的值。这和[P2709 小B的询问](https://www.luogu.com.cn/problem/P2709)很像。在转移时，我们可以用平方差公式。

设左指针为 $lp$，右指针为 $rp$，$k$ 在 $[lp,rp]$ 中出现 $cnt_k$ 次。具体操作如下：

1. 左端点向左移，$lp \leftarrow lp-1$，$cnt_{a_{lp}} \leftarrow cnt_{a_{lp}}+1$，$res \leftarrow res+(2 \times cnt_{a_{lp}} -1) \times a_{lp}$
2. 右端点向右移，$rp \leftarrow rp+1$，$cnt_{a_{rp}} \leftarrow cnt_{a_{rp}}+1$，$res \leftarrow res+(2 \times cnt_{a_{rp}} -1) \times a_{rp}$
3. 左端点向左移，$res \leftarrow res+(2 \times cnt_{a_{lp}} -1) \times a_{lp}$，$cnt_{a_{lp}} \leftarrow nt_{a_{lp}}-1$，$lp \leftarrow lp+1$
4. 右端点向右移，$res \leftarrow res+(2 \times cnt_{a_{rp}} -1) \times a_{rp}$，$cnt_{a_{rp}} \leftarrow cnt_{a_{rp}}-1$，$rp \leftarrow rp-1$
5. ~~`while(1)rp++;`~~

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define uint unsigned int
#define neinf 0xc0c0c0c0
#define inf 0x3f3f3f3f
#define ll long long
#define reg register
#define db double
#define il inline
#define gc getchar
#define pc putchar
#define HgS 1000000007
il int rd()
{
	reg int res=0,lab=1;
	reg char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')lab=-lab;ch=getchar();}
	while(ch>='0'&&ch<='9')
		res=(res<<3)+(res<<1)+(ch&15),ch=getchar();
	return res*lab;
}
il void prt(ll x,char t)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)prt(x/10,0),x%=10;
	putchar(x|48);
	if(t)putchar(t);
}
#define ar 1000000
#define len 200000
#define siz 444
#define cp(x) ((x-1)/siz+1)
int n,a[len+5],q,tm[ar+5];
ll ans[len+5];
struct query
{
	int l,r,id;
	query(){l=r=id=0;}
	query(int _l,int _r,int _id){l=_l;r=_r;id=_id;}
}qr[len+5];
#define lq(i) ((qr+(i))->l)
#define rq(i) ((qr+(i))->r)
bool cmp(query x,query y)
{
	return cp(x.l)<cp(y.l)||(cp(x.l)==cp(y.l)&&
		((cp(x.l)&1)?x.r<y.r:x.r>y.r));
}
int main()
{
	n=rd();q=rd();
	for(int i=1;i<=n;++i)a[i]=rd();
	for(int i=1;i<=q;++i)
	{
		int tl=rd(),tr=rd();
		qr[i]=query(tl,tr,i);
	}
	sort(qr+1,qr+1+q,cmp);
	reg int lt=1,rt=0;
	reg ll res=0;
	for(int i=1;i<=q;++i)
	{
		while(lt>lq(i))
			res+=(((++tm[a[--lt]])<<1)-1)*a[lt];
		while(rt<rq(i))
			res+=(((++tm[a[++rt]])<<1)-1)*a[rt];
		while(lt<lq(i))
			res-=a[lt]*(((tm[a[lt++]]--)<<1)-1);
		while(rt>rq(i))
			res-=a[rt]*(((tm[a[rt--]]--)<<1)-1);
		ans[qr[i].id]=res;
	}
	for(int i=1;i<=q;++i)prt(ans[i],'\n');
	return 0;
}
```

---

## 作者：Vocanda (赞：2)

# 题目
[题目链接](https://www.luogu.com.cn/problem/CF86D)

# 分析
莫队板子题，稍微分析一下区间跳转时的转移就好了。

我们要求的答案就是每段区间内的 $\sum_i cnt_i^2\times i$ ，单独乘以一个 $i$ 我们暂时先不考虑。主要就是按套路区间跳转的时候 $cnt_i^2$ 的变化量。

按照莫队的做法，每一次区间大小是只会变化 $1$ 的，所以我们的答案也只会有一个进行变化，那么就会好维护许多。把 $cnt_i^2$ 拆开看一下，如果当前 $i$ 的个数多了 $1$ ，那么 $cnt_i$ 肯定就多了 $1$ 。那么我们根据完全平方 

$$(cnt_i+1)^2 = cnt_i^2 + 2\times cnt_i+1$$ 
$$(cnt_i-1)^2 = cnt_i^2 - 2\times cnt_i+1$$

这样我们就得到了每一次修改的变化量，即：

$$2\times cnt_i + 1$$ 
和

$$-2\times cnt_i + 1$$

最后不要忘记乘以一个 $i$ 。

然后在区间跳转的时候按照这个式子转化计算答案即可。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e6+10;
int bel[maxn],a[maxn],block;
ll cnt[maxn],ans[maxn],sum;
struct Node{
	int l,r,id;
	friend bool operator < (const Node& a,const Node& b){//重载运算符
		return bel[a.l] == bel[b.l] ? a.r < b.r : bel[a.l] < bel[b.l];
	}
}q[maxn];
inline void Del(int x){//计算减去的贡献。
	sum -= cnt[a[x]] * 2 * a[x] - a[x];
	cnt[a[x]]--;
}
inline void Add(int x){//计算加上的贡献。
	sum += cnt[a[x]] * 2 * a[x] + a[x];
	cnt[a[x]]++;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	block = sqrt(n);//计算块大小。
	for(int i = 1;i <= n;++i){
		scanf("%d",&a[i]);
		bel[i] = (i - 1) / block + 1;//计算每个点属于哪块。
	}
	for(int i = 1;i <= m;++i){//把询问离线
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id = i;
	}
	sort(q+1,q+m+1);//按照块进行排序
	int l = 1,r = 0;
	for(int i = 1;i <= m;++i){
		int ql = q[i].l,qr = q[i].r;
		while(l < ql)Del(l++);//注意自加自减运算符的顺序
		while(l > ql)Add(--l);
		while(r < qr)Add(++r);
		while(r > qr)Del(r--);
		ans[q[i].id] = sum;
	}
	for(int i = 1;i <= m;++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：Gu_Pigeon (赞：2)

# 又双叒叕一道莫队裸题（特大雾）

~~希望更容易看懂本题解？学习[莫队算法](https://www.luogu.org/blog/codesonic/Mosalgorithm)~~

最普通的莫队，把 `inc`（把指针所指的指加入队列）和 `dec`（把指针所指的指移出队列）写好，~~其他都可以复制了~~。

那么考虑如何在 $\text O(1)$ 时间内完成转移。。。

对于一个数的加入/移除，造成的影响有：

```cpp
sum = sum - cnt[a[x]] * cnt[a[x]] * a[x];
cnt[a[x]]++; // or cnt[a[x]]--;
sum = sum + cnt[a[x]] * cnt[a[x]] * a[x];
```

上面的代码中，`a[i]` 表示序列中第 `i` 个数的值，`cnt[x]` 表示**队列中**值为 `x` 的数有多少个，`sum` 表示当前队列的答案。

Emmm… 就这样好了？

没错好了……

| | $ \tiny\textsf{ya} $ | $ \tiny\textsf{hang} $ |
|-|:-:|:-:|
| 不过上面的写法有点麻烦，可以考虑 | 化 | 简 |

其实，过程中 `sum` 的变化无非是因为 `cnt` 的值发生了变化，因此化简为下面的柿子（以 `inc` 为例）：

```cpp
sum += (cnt[a[x]] + 1) * (cnt[a[x]] + 1) * a[x] - cnt[a[x]] * cnt[a[x]] * a[x];
// and cnt[a[x]]++;
```

进一步拆括号，就是：

```cpp
sum += cnt[a[x]] * cnt[a[x]] * a[x] + 2 * cnt[a[x]] * a[x] + a[x] - cnt[a[x]] * cnt[a[x]] * a[x];
// and cnt[a[x]]++;
```

这不就可以消掉了吗！！！

```cpp
sum += 2 * cnt[a[x]]++ * a[x] + a[x];
```

| | $ \tiny\textsf{zhuang} $ | $ \tiny\textsf B $ |
|-|:-:|:-:|
| 加上位运算，方便 | 卡 | 常 |

```cpp
sum += (cnt[a[x]]++ << 1 | 1) * a[x];
```

Perfect!

$\Large\textit{Code Below}$

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

#define N 200019
#define int long long
int n, t, sz, a[N], ans[N], sum, cnt[1000086];

struct data
{
	int l, r, id;
} q[N];

void inc(int x)
{
	sum += (cnt[a[x]]++ << 1 | 1) * a[x];
}

void dec(int x)
{
	sum -= (--cnt[a[x]] << 1 | 1) * a[x];
}

signed main() 
{
	scanf("%lld%lld", &n, &t); sz = pow(n, 0.5);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (int i = 1; i <= t; i++) scanf("%lld%lld", &q[i].l, &q[i].r), q[i].id = i;
	sort(q + 1, q + t + 1, [](data a, data b){return (a.l / sz) ^ (b.l / sz) ? a.l < b.l : a.r < b.r;});
	int lp = 1, rp = 0;
	for (int i = 1; i <= t; i++) 
	{
		while (rp < q[i].r) inc(++rp);
		while (rp > q[i].r) dec(rp--);
		while (lp < q[i].l) dec(lp++);
		while (lp > q[i].l) inc(--lp);
		ans[q[i].id] = sum;
	}
	for (int i = 1; i <= t; i++) printf("%lld\n", *(ans + i));
}
```


---

## 作者：谦谦君子 (赞：1)

## 本题标签：分块！！！


哎发现大佬们人均会莫队，但是蒟蒻不会莫队，于是我只好用分块来献丑了qaq~

希望能够给大家多一个思路&让一些人了解一下分块（虽然我觉得会莫队的应该没有不会分块的）

鉴于这是一个比较基础的分块题，在此之前先介绍一下分块


其实分块的思想非常简单
## 大体思想：
分块就是把一段数分成几块来做

分块的操作一般是维护和查询，一个对于$[l，r]$的操作，对于在该区间内的**完整的块**，我们**直接**维护整个块的信息；对于**两侧不完整**的部分，我们**暴力修改**每个点的信息。写分块的关键就是想好如何维护和查询。

**一般情况下，当$S=\sqrt{N}$时，时空复杂度最优。**

## 解决问题：
分块可以处理很多区间问题，虽然复杂度要比树状数组和线段树要高，但是代码比较简短、思想直观形象，所以很多题不会求解可以考虑分块一下

## 具体实现
分块分块，首先自然需要分，在这里给出一个小栗子：这里是通过分块来维护区间最大值

```cpp
void build()
{
	dis=sqrt(n);                    //每个块的长度
	num=n/dis;                      //共有多少个块
	for (int i=1;i<=num;i++)        //给每一个块标记左右范围
	{
		l[i]=dis*(i-1)+1;
		r[i]=dis*i;
	}
	r[num]=n;                       //最后一个r dis*i有可能大于n故要改回n
	for (int i=1;i<=num;i++)
	{
		int ans=0;
		for (int j=l[i];j<=r[i];j++)
		{
			ans=max(ans,a[j]);      //具体题目具体分析，此题中要求维护区间最大值故记录区间最大值
			block[j]=i;             //记录没一个点属于哪一个块
		}
		maxx[i]=ans;
	}
}
}
```
相信通过这个大家能对分块的思想有一个基本的了解，接下来我们回到这一题~

## 题目大意：
给出一个$n$个数组成的数列$a_1...a_n$，有$t$次询问，每次询问为一个$[l,r]$的区间，求区间内每种数字出现次数的平方$×$数字的值的和。

## 思路：
发现这是一个标准的纯查询的问题，我们考虑用分块做

我们可以这样做：
- 对这$n$个数进行分块，将其分成$\sqrt n$块，算出每一块的长度并且将查询的左端点的所在的块数求出
- 对每一次的询问进行排序，按照左端点所在块号&右端点从小到大进行排序，注意前者优先级大于后者，原因：这让每一次往后的暴力都确保是往右的
- 算出第一次询问每次跟上次的询问区间比较，把多出来的减掉，把少的加上去

但是我们应该加什么呢？对于一个已经出现了$x$次的数$a_i$,$x^2\cdot a_i$变成了$(x+1)^2\cdot a_i$

而根据**完全平方公式**可知

$(x+1)^2=x^2+2\cdot x+1$

所以只需加上$(2\cdot x+1)\cdot a_i$即可，于是这就变成了一个比较暴力的问题

ok,如果大家对这个代码是否能过表示怀疑的话我们不妨来算一下复杂度，$t$次询问

具体代码不再展示，希望对你能够有帮助

---

## 作者：Cripple_Abyss (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF86D)

这是一道很好的莫队模板题！

言归正传，我们先来了解一下莫队：

## STEP 1 分块：
其实就是一个暴力的过程。
```cpp
int size = sqrt(n);
for (int i = 1; i <= n; i++)
{
    scanf("%d", &a[i]);
    pos[i] = i/ size;
}
```

## STEP 2 输入询问：
因为莫队是离线的数据结构，我们要对询问的数据稍加处理。

```cpp
for (int i = 1; i <= m; i++)
{
    scanf("%d%d", &q[i].l, &q[i].r);
    q[i].k = i;
}
sort(q + 1, q + m + 1, cmp);
```

$cmp$ 函数比较内容：

- 先按左端点分的块进行排序。

- 然后再按右端点进行排序。

代码如下：
```cpp
bool cmp(node a, node b)
{
    if (pos[a.l] != pos[b.l])
        return pos[a.l] < pos[b.l];
    return a.r < b.r;
}
```

## STEP 3 计算结果
代码模板如下：
```cpp
int l = 1, r = 0;
for (int i = 1; i <= m; i++)
{
    while (l < q[i].l)
        Del(l++);
    while (l > q[i].l)
        Add(--l);
    while (r < q[i].r)
        Add(++r);
    while (r > q[i].r)
        Del(r--);
    ans[q[i].k] = s;
}
```
个人觉得比较清晰，不做解释，可看其他题解分析。 QwQ

而莫队的核心代码就是 $Add$ 和 $Del$ 两个函数。


## 本题 Code
```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
const int MAXN = 2e6 + 5;
struct node
{
    int l, r, k;
} q[MAXN];
int a[MAXN], pos[MAXN], cnt[MAXN];
long long s, ans[MAXN]; 
int n, m;
int l = 1, r;
bool cmp(node a, node b)
{
    if (pos[a.l] != pos[b.l])
        return pos[a.l] < pos[b.l];
    return a.r < b.r;
}
inline void Add(int x)
{
    s += cnt[a[x]] * a[x] * 2 + a[x];
    cnt[a[x]]++;
}
inline void Del(int x)
{
    s -= cnt[a[x]] * a[x] * 2 - a[x];
    cnt[a[x]]--;
}
int main()
{
    scanf("%d%d", &n, &m);
    int size = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        pos[i] = i / size;
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].k = i;
    }
    sort(q + 1, q + m + 1, cmp);
    for (int i = 1; i <= m; i++)
    {
        while (l < q[i].l)
            Del(l++);
        while (l > q[i].l)
            Add(--l);
        while (r < q[i].r)
            Add(++r);
        while (r > q[i].r)
            Del(r--);
        ans[q[i].k] = s;
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
```

## 智障推荐
[P2709 小B的询问](https://www.luogu.com.cn/problem/P2709) 
与本题挺相似的。

都看到这里了，点个赞再走呗 QwQ

## 彩蛋
### 祝大家 CSP2020 J/S RP++ ！！！

---

## 作者：Su_Zipei (赞：0)

比较简单的莫队题目，莫队算法一般用来离线解决区间问题，并且要求左右端点移动的时间复杂度不能过高，~~$O(n)$移动一次就还不如暴力~~。

这一道题为什么可以用莫队呢，因为从$cnt->cnt+1$的移动很好移动，减一同理，所以就能够使用莫队解决这个问题。

如果莫队写的比较熟练，往往可以把一个$Add$函数通过运算符优先级压缩成一句话，据说这样会快，而且如果掌握熟练的话写起来也很方便，不熟练的话就算了。

```cpp
/*
8 3
1 1 2 2 1 3 1 1
2 7
1 6
2 7
*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+10;
typedef long long ll;
int sqr;
struct Ask{
	int id,l,r;
	bool operator < (const Ask&A)const{
		int cl=(l-1)/sqr+1,cr=(A.l-1)/sqr+1;
		return cl==cr?cl&1?r<A.r:r>A.r:cl<cr;
	}
}p[N];
int a[N],cnt[N];
ll ans[N];
int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=q;i++)
		scanf("%d%d",&p[i].l,&p[i].r),p[i].id=i;
	sqr=sqrt(q);
	sort(p+1,p+q+1);
	ll res=0;
	for(int i=1,cl=1,cr=0;i<=q;i++){
		while(cr<p[i].r)res+=(cnt[a[++cr]]++*2+1)*a[cr];
		while(cl>p[i].l)res+=(cnt[a[--cl]]++*2+1)*a[cl];
		while(cr>p[i].r)res-=a[cr]*(cnt[a[cr--]]--*2-1);
		while(cl<p[i].l)res-=a[cl]*(cnt[a[cl++]]--*2-1);
		ans[p[i].id]=res;
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
	return 0;
}

```


---

## 作者：1saunoya (赞：0)

莫队裸题

~~没想到外国人都知道莫涛队长.jpg~~

莫队的博客 -> [$\text{这儿}$](https://www.cnblogs.com/qf-breeze/p/11380502.html)

莫队主要是排完序之后 左右指针移动 每次移动都是 O1 的

移动次数不会超过 $m log n$ 所以对于这题是足够了。
跑的慢死
我搞了个离散化 因为我刚开始以为 $a_i<=10^9$
然后打好之后发现 $a_i<=10^6$ 数组也可以开下...

```cpp
#include <bits/stdc++.h>
#define int long long
#define gc c=getchar()
inline int read() {
    register int x = 0 ;
    register char c ;
    while(isspace(gc)) ;
    while(x = (x << 1) + (x << 3) + (c ^ 48) , isdigit(gc)) ;
    return x ;
}
using namespace std ;
const int N = 2e5 + 10 ;
int n , m ;
int block , tmp = 0 ;
int val[N] ;
int cnt[N] ;
int tot = 0 ;
int b[N] ;
int ans[N] ;
struct node {
    int l , r , id ;
    int d ;
} a[N] ;
inline void Delete(int x) {
    tmp -= (cnt[val[x]]) * (cnt[val[x]]) * b[val[x]] ;
    cnt[val[x]] -- ;
    tmp += (cnt[val[x]]) * (cnt[val[x]]) * b[val[x]] ;
}
inline void Insert(int x) {
    tmp -= (cnt[val[x]]) * (cnt[val[x]]) * b[val[x]] ;
    cnt[val[x]] ++ ;
    tmp += (cnt[val[x]]) * (cnt[val[x]]) * b[val[x]] ;
}
inline bool cmp(node x , node y) {
    return x.id == y.id ? x.r < y.r : x.id < y.id ;
}
signed main() {
    n = read() ;
    m = read() ;
    int block = sqrt(n) ;
    for(register int i=1; i<=n; i++) {
        val[i] = read() ;
        b[i] = val[i] ;
    }
    sort(b + 1 , b + n + 1) ;
    tot = unique(b + 1 , b + n + 1) - b - 1 ;
    for(register int i = 1 ; i <= n ; i ++) val[i] = lower_bound(b + 1 , b + tot + 1 , val[i]) - b ;
    for(register int i=1; i<=m; i++) a[i].l = read() , a[i].r = read() ;
    for(register int i=1; i<=m; i++) {
        a[i].id = (a[i].l + block - 1) / block ;
        a[i].d = i ;
    }
    sort(a + 1 , a + m + 1 , cmp) ;
    int l , r ;
    l = r = a[1].l ;
    -- r ;
    for(register int i=1; i<=m; i++) {
        while(l < a[i].l) Delete(l ++) ;
        while(l > a[i].l) Insert(-- l) ;
        while(r > a[i].r) Delete(r --) ;
        while(r < a[i].r) Insert(++ r) ;
        ans[a[i].d] = tmp ;
    }
    for(register int i=1; i<=m; i++) cout << ans[i] << endl ;
    return 0 ;
}
```

---

## 作者：eee_hoho (赞：0)

题意：$t$次询问区间$[l,r]$中$\sum_x a_x\times cnt[a_x]^2$，$cnt$为出现次数

裸的莫队题，用$cnt[x]$表示$x$出现的次数，根据平方的性质，我们得出加减操作

- 加：$ans+=a_x\times 2cnt[a_x]+1,cnt[a_x]++$
- 减：$ans-=a_x\times 2cnt[a_x]-1,cnt[a_x]--$

先加减再更新$ans$也是一样的

然后考虑一下莫队的卡常——奇偶性排序

我们对左端点在同一个块里的询问，若其块的编号是奇数，那么按右端点升序排序；若编号是偶数，则按右端点降序排序。不在同一个块里的就按左端点升序排序

这样子为什么会快呢？

如果我们处理完的这个区间是奇数号区间，那么右指针是指向比较靠后的点的，而下次到偶数号区间，正好是按右端点降序排序，移动右指针的距离就少了很多。这样子复杂度理论可以快一倍

然而莫队终究是个分块暴力，所以复杂度仍然是$O(n\sqrt n)$，对于这个题而言时间已经足够了

**Code**
``` cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define N 2000000
using namespace std;
struct node
{
    int l,r,b,id;
}q[N+5];
int n,m,a[N+5],blo;
long long ans[N+5],tmp,cnt[N+5];
int cmp(node x,node y)     //奇偶性排序
{
    return (x.b==y.b)?(x.b%2==1?x.r<y.r:x.r>y.r):x.l<y.l;
}
void add(int x)
{
    tmp+=(long long)a[x]*1LL*(cnt[a[x]]*2+1);
    cnt[a[x]]++;
}
void del(int x)
{
    tmp-=(long long)a[x]*1LL*(cnt[a[x]]*2-1);
    cnt[a[x]]--;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    blo=(sqrt(m*2/3))?n/sqrt(m*2/3):sqrt(n);  //块大小
    if (!blo)blo=sqrt(n);
    for (int i=1;i<=m;i++)
    {
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].b=q[i].l/blo;
        q[i].id=i;
    }
    sort(q+1,q+m+1,cmp);
    for (int i=1,l=1,r=0;i<=m;i++)    //莫队
    {
        while (l>q[i].l)add(--l);
        while (r<q[i].r)add(++r);
        while (l<q[i].l)del(l++);
        while (r>q[i].r)del(r--);
        ans[q[i].id]=tmp;
    }
    for (int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：hovny (赞：0)

## [题面](https://www.luogu.org/problemnew/show/CF86D)

给出一个$n$个数组成的数列$a$，有$t$次询问，每次询问为一个$[l,r]$的区间，求区间内**每种数字出现次数的平方×数字的值** 的和

## 思路：


### 直接上莫队咯      ~~`然后就T了`~~

没学过莫队？！~~我也没办法~~

这道题的数据范围在$2e5$的级别，有人会问莫队肯定要炸啊 捏~

### 时限5000ms，那就可以乱搞了

但是！还是要加一些优化

### 如何优化？

1.对于算法本身的优化

由于莫队可以说是一个块状暴力的算法，就是把区间划分为$\sqrt n$块然后在块内暴力~~（到头还是暴力）~~

我们可以把要查询的区间当做点表示在平面直角坐标系上，RT：

![](https://www.cnblogs.com/images/cnblogs_com/hovny/1364959/o_%e8%8e%ab%e9%98%9f1.png)

就像这样把询问放在平面直角坐标系上，**$\large x$轴为询问该区间的顺序，$\large y$轴表示该区间的右端点**，如果我们忽略区间的$L$值的影响，不难看出，虽然我们已经把区间划分在一个块里了，但是还是有很多冗余的操作，如果要是这些冗余的操作少一点就好了，这当然可以啦！

我们可以让**块内的区间按$\large R$ 递增**，这样能省很多时间，但是在区间过渡的时候，我们还是会做很多多余的操作，因为区间都是递增的，这样改变块的时候就可能有一个很大的落差，就掉了下去，可以自己想象一下

![](https://www.cnblogs.com/images/cnblogs_com/hovny/1364959/o_%e8%8e%ab%e9%98%9f2.png)

为了避免上述的现象，我们可以让区间像一个波浪一样，这样就很高效了，这样的划分方式叫做`奇偶划分`~~应该是这么叫的吧，还有一个是奇偶性剪枝~~

```cpp
inline bool cmp(node a,node b){//代码是关键，讲了啥不重要(手动划线)
	return (pos[a.l]==pos[b.l])?(pos[a.l]&1)?a.r<b.r:a.r>b.r : a.l<b.l;
}//千万不要写if，会T！
```

接着就是块的大小，同样影响速度，一般普通的块的大小应该是$\large \sqrt n$，但是，根据某奆佬研究，大小为$\large n^{0.54}$时更快，Orz

2.对于程序本身优化，~~说人话就是卡卡常~~

比如：

> 加点`register`
>
> 非递归函数前加个`inline`
>
> 不用快读用`fread`
>
> 还有！乘法变加法……

然后就把最大时间卡到了`622ms`

~~啊哈哈哈哈哈~~

Code：

```cpp
#include<bits/stdc++.h>
#define getchar() *(p++)//在快读基础上改一点就行了
#define Re register//卡常必备
#define ll long long
#define M 1000010
#define N 200010
using namespace std;
struct node{
	int l,r,i;
}b[N];//sum是数的多少，pos表示在哪块
int a[N],pos[N],n,m,sum[M],l,r,block;
ll Ans[N],ans;
char bf[1<<25],*p;
int read(){
	Re int s=0;
	Re char c=getchar();
	while(!isdigit(c))
		c=getchar();
	while(isdigit(c))
	{
		s=(s<<1)+(s<<3)+c-'0';
		c=getchar();
	}
	return s;
}
inline bool cmp(node a,node b){//奇偶划分
	return (pos[a.l]==pos[b.l])?(pos[a.l]&1)?a.r<b.r:a.r>b.r : a.l<b.l;
}//注意，这里不要写if语句，会T
inline void Add(Re ll x)
{
	sum[x]++;//有些人写在前面，那样的话就应该是+1
	ans+=(sum[x]+sum[x]-1)*x;//就是由原来的乘变成了加，手算一小部分也没有关系啦
}
inline void Del(Re ll x)
{
	ans-=(sum[x]+sum[x]-1)*x;//这里和上面也是一样的
	sum[x]--;//为什么我感觉上面-1会更慢呢~
}
int main()
{
	Re int i;
	bf[fread(bf,1,1<<25,stdin)]='\0';p=bf;//fread大法
	n=read();m=read();block=pow(n,0.54);//神奇的块的大小
	for(i=1;i<=n;i++)
		a[i]=read(),pos[i]=i/block;
	for(i=1;i<=m;i++)
		b[i].l=read(),b[i].r=read(),b[i].i=i;
	sort(b+1,b+1+m,cmp);l=1;
	for(i=1;i<=m;i++)//然后上莫队
	{
		while(r<b[i].r)
			Add(a[++r]);
		while(r>b[i].r)
			Del(a[r--]);
		while(l<b[i].l)
			Del(a[l++]);
		while(l>b[i].l)
			Add(a[--l]);
		Ans[b[i].i]=ans;
	}
	for(i=1;i<=m;i++)
		printf("%lld\n",Ans[i]);
	return 0;
}
```
### ~~再说一遍~~
### 最后注意，sort的时候，如果数组本来就有序了，sort会很慢，所以千万不要在里面加if了，容易T


---

## 作者：yzhang (赞：0)

### [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/10009499.html)

### [原题传送门](https://www.luogu.org/problemnew/show/CF86D)

### 裸的莫队啊，[我博客里有对莫队较详细的介绍](https://www.cnblogs.com/yzhang-rp-inf/p/9991671.html)

这道题很简单，可以说是裸的模板

但是如何在已有的值上进行操作？

小学生应该都知道$x^2+x+x+1=(x+1)^2$

那么转移就超级简单了qaq

```cpp
inline void add(register int c)
{
	sum+=(num[c]+num[c]+1)*c;
	++num[c];
}
inline void del(register int c)
{
	--num[c];
	sum-=(num[c]+num[c]+1)*c;
}
```

## 要开long long~~（虽说我没试过int，但我觉得会炸int）~~

```cpp
#include <bits/stdc++.h>
#define N 200005
using namespace std;
inline int read()
{
	register int x=0,f=1;register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
inline void write(register long long x)
{
	if(!x)putchar('0');if(x<0)x=-x,putchar('-');
	static int sta[25];int tot=0;
	while(x)sta[tot++]=x%10,x/=10;
	while(tot)putchar(sta[--tot]+48);
}
struct query{
	int l,r,id,bl;
}q[N];
int a[N],blocksize=0,num[1000005];
long long ans[N],sum=0;
inline void add(register int c)
{
	sum+=(num[c]+num[c]+1)*c;
	++num[c];
}
inline void del(register int c)
{
	--num[c];
	sum-=(num[c]+num[c]+1)*c;
}
inline bool cmp(register query a,register query b)
{
	return a.bl!=b.bl?a.l<b.l:(a.bl&1?a.r<b.r:a.r>b.r);
}
int main()
{
	int n=read(),m=read();
	blocksize=sqrt(n);
	for(register int i=1;i<=n;++i)
		a[i]=read();
	for(register int i=1;i<=m;++i)
	{
		int l=read(),r=read();
		q[i]=(query){l,r,i,(l-1)/blocksize+1};
	}
	sort(q+1,q+1+m,cmp);
	int l=1,r=0;
	for(register int i=1;i<=m;++i)
	{
		int ll=q[i].l,rr=q[i].r;
		while(ll<l)
			add(a[--l]);
		while(ll>l)
			del(a[l++]);
		while(rr>r)
			add(a[++r]);
		while(rr<r)
			del(a[r--]);
		ans[q[i].id]=sum;
	}
	for(register int i=1;i<=m;++i)
		write(ans[i]),printf("\n");
	return 0;
 } 
```

---

## 作者：Fheiwn (赞：0)

关于此题，暴力是能过5组左右，让暴力优美一点的莫队是很不错的选择，  
但此题可谓是丧心病狂，若使用cin,cout会在三十多组时T掉，  
并且记数数组要开int才能过，否则就在四十组左右徘徊（也可能是人傻常数大）  
除此之外，就没什么，用莫队就能过了  

```cpp
#include<iostream> 
#include<cstdio>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<bitset>
#include<vector>
#include<cstdlib>
#define QAQ int
#define TAT long long
#define OwO bool
#define ORZ double
#define Ug unsigned
#define F(i,j,n) for(QAQ i=j;i<=n;++i)
#define E(i,j,n) for(QAQ i=j;i>=n;--i)
#define MES(i,j) memset(i,j,sizeof(i))
#define MEC(i,j) memcpy(i,j,sizeof(j))

using namespace std;
const QAQ N=200005;

QAQ n,m;
QAQ bel[N],block;
struct Ask{
	QAQ l,r,id;
	
	friend OwO operator < (Ask a,Ask b){
		return bel[a.l]==bel[b.l] ? a.r<b.r : bel[a.l]<bel[b.l];
	}
}q[N];
QAQ L,R;
TAT ans[N],sum;
QAQ t[1000005],a[N];

QAQ read(){  
    QAQ p=0;char x=getchar();  
    while (x<'0' || x>'9') x=getchar();  
    while (x>='0' && x<='9') p=p*10+x-'0',x=getchar();  
    return p;  
}  

void Less(TAT x){
	sum-=1ll*t[x]*t[x]*x;
	t[x]--;
	sum+=1ll*t[x]*t[x]*x;
}

void add(TAT x){
	sum-=1ll*t[x]*t[x]*x;
	t[x]++;
	sum+=1ll*t[x]*t[x]*x;
}

QAQ main(){
	n=read();m=read();
	block=sqrt(1.0*n);
	F(i,1,n) a[i]=read(),bel[i]=(i-1)/block+1;
	F(i,1,m) q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1);
	L=1;R=0;
	F(i,1,m) {
		QAQ l=q[i].l,r=q[i].r;
		while(L<l) Less(a[L]),L++;
		while(L>l) L--,add(a[L]);
		while(R<r) R++,add(a[R]);
		while(R>r) Less(a[R]),R--;
		ans[q[i].id]=sum;
	}
	F(i,1,m) printf("%lld\n",ans[i]);
	return 0;
}

```

---

