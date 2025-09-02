# DQUERY - D-query

## 题目描述

[English](/problems/DQUERY/en/) [Vietnamese](/problems/DQUERY/vn/)Given a sequence of n numbers a $ _{1} $ , a $ _{2} $ , ..., a $ _{n} $ and a number of d-queries. A d-query is a pair (i, j) (1 ≤ i ≤ j ≤ n). For each d-query (i, j), you have to return the number of distinct elements in the subsequence a $ _{i} $ , a $ _{i+1} $ , ..., a $ _{j} $ .

## 样例 #1

### 输入

```
5
1 1 2 1 3
3
1 5
2 4
3 5```

### 输出

```
3
2
3```

# 题解

## 作者：Tarsal (赞：30)

今天机房讲了莫队。

但是蒟蒻我并没有听懂，所以晚上回家恶补，才弄明白莫队。

莫队是莫涛大神发明的，它的作用就是用优秀的复杂度求解于一些区间之间的操作，莫队其实就是一个优雅的暴力，它的复杂度是O(n sqrt(n))；

以此[题](https://www.luogu.org/problemnew/show/SP3267)为例，其实这题和[这题](https://www.luogu.org/problemnew/show/P1972)是一样的，不过P1972会卡莫队。

回到此题：

题意很直白，我就不多赘述；

思路1：

暴力，这题最朴素的作法无非就是从l到r扫一遍，用数组记下出现的数，然后求值：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100010
bool flag[maxn];
int n, m, a[maxn], sum, ans, l, r, x, y;
int main()
{
	//freopen("count.in","r",stdin);
	//freopen("count.out","w",stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++ i)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; ++ i)
	{
		scanf("%d%d%d%d", &l, &r, &x, &y);
		memset(flag, 0, sizeof(flag));
		sum = ans = 0;
		for(int j = l; j <= r; ++ j)
			if(a[j] >= x && a[j] <= y)
			{
				++ sum;
				if(flag[a[j]] == 0)
				{
					flag[a[j]] = 1;
					++ ans;
				}
			}
		printf("%d %d\n", sum, ans);
	}
	return 0;
}
```
ans即为所求；

但是这种作法的复杂度是O(n*n)的，肯定过不了；

那么就需要一些优化：

我们用两个指针不断的移动到相应的区间；
```cpp
int l = 0, r = 1;
```
然后在移动的时候，我们就不停的add，del；

如果要想右，就add；

否则，就del；
```cpp
void add(int x)
{
	if(cnt[a[x]] == 0)
		++ now;
	++ cnt[a[x]];
}
```
```cpp
void del(int x)
{
	-- cnt[a[x]];
	if(cnt[a[x]] == 0)
		-- now;
}
```

```cpp
while(l < q[i].l)
	del(l ++);
while(l > q[i].l)
	add(-- l);
while(r < q[i].r)
	add(++ r);
while(r > q[i].r)
	del(r --);

```
就是上面这样，

这就是莫队？

不，还有一个地方，

我们来假设要查询的区间为[1, 10000000]呢？

那不一样还是没有优化。

所以莫队还要一个很重要的地方，就是排序；

该如何排序？

如果按左端点排序，那么右端点就会不好表示；

如果按右端点排序，那么左端点就会不好表示；

这个时候，分块大法万岁；

把长度为n的序列，分成sqrt(n)个块；

把查询区间按照左端点所在块的序号排个序，如果左端点所在块相同，再按右端点排序。

其实，蒟蒻我也不明白这为什么会快200多ms，但它就是会；

整个程序的复杂度为O(n * sqrt(n));

代码时间：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 1000010
int n, m, a[maxn], cnt[maxn], ans[maxn], bein[maxn], l = 1, r, now;

struct node
{
	int l, r, id;
}q[maxn];

bool cmp(node a, node b)
{
	return bein[a.l] == bein[b.l] ? a.r < b.r : bein[a.l] < bein[b.l];
}

void add(int x)//加入操作 （右移 
{
	if(cnt[a[x]] == 0)
		++ now;
	++ cnt[a[x]];
}

void del(int x)//删除（左移 
{
	-- cnt[a[x]];
	if(cnt[a[x]] == 0)
		-- now;
}

void print(int x)//要从后往前输出，所以来递归输出 
{
	if(x / 10)
		print(x / 10);
	//printf("%d", x % 10);
	putchar(x % 10 + '0');
	//printf("K"); 
}

int main()
{
    scanf("%d", &n);//输入 
	for(int i = 1; i <= ceil((double) n / sqrt(n)); ++ i)
		for(int j = (i - 1) * sqrt(n) + 1; j <= i * sqrt(n); ++ j)
			bein[j] = i;//这是分的块 
	for(int i = 1; i <= n; ++ i)
		scanf("%d", &a[i]);//还是输入 
	scanf("%d", &m);//继续输入 
	for(int i = 1; i <= m; ++ i)
	{
		scanf("%d%d", &q[i].l, &q[i].r);//还要输入 
		q[i].id = i;//记录下序号，cmp中要用 
	}
    sort(q + 1, q + m + 1, cmp);//排序 
    /*这种作法就不需要add和del 
    for(int i = 1; i <= m; ++i) {
        int ql = q[i].l, qr = q[i].r;
        while(l < ql) now -= !--cnt[aa[l++]];
        while(l > ql) now += !cnt[aa[--l]]++;
        while(r < qr) now += !cnt[aa[++r]]++;
        while(r > qr) now -= !--cnt[aa[r--]];
        ans[q[i].id] = now;
    }
	*/
	for(int i = 1; i <= m; ++ i)
	{
		while(l < q[i].l)//l右移 
			del(l ++);
		while(l > q[i].l)//l左移 
			add(-- l);
		while(r < q[i].r)//r右移 
			add(++ r);
		while(r > q[i].r)//r左移 
			del(r --);
		ans[q[i].id] = now;
	}
    for(int i = 1; i <= m; ++ i)
	{
		print(ans[i]);//输出 
		printf("\n");//记得换行 
	}
	return 0;
}
```
因为在本蒟蒻最开始学的时候没有懂，所以有拜读了[WAMonster](https://www.cnblogs.com/WAMonster/p/10118934.html)大佬的文章，可能在思路上会有部分相同，而且我也强力推荐这位大佬的博客，写的特别好。

---

## 作者：hongzy (赞：17)

放一个主席树的在线做法

记一个$last[i]$表示$a[i]$上一次出现的位置，那么问题转换为求一个区间$[l,r]$里$last\leq l-1$的个数，可以用主席树维护$last$值，为了方便，把$last+1$，主席树值域就为$[1,n]$了

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 3e4 + 10;
const int M = 1e6 + 10;

int n, q, a[N], pre[M], la[N]; //pre[i] : i上一次出现的位置
int T[N << 5], s[N << 5], L[N << 5], R[N << 5], id;

void build(int &rt, int l, int r) {
	rt = ++ id; s[rt] = 0;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	build(L[rt], l, mid);
	build(R[rt], mid + 1, r);
}

void update(int pre, int &rt, int l, int r, int x) {
	rt = ++ id; s[rt] = s[pre] + 1;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(x <= mid) R[rt] = R[pre], update(L[pre], L[rt], l, mid, x);
	else L[rt] = L[pre], update(R[pre], R[rt], mid + 1, r, x);
}

int query(int rt1, int rt2, int l, int r, int ql, int qr) {
	if(ql <= l && r <= qr) return s[rt2] - s[rt1];
	int mid = (l + r) >> 1, ans = 0;
	if(ql <= mid) ans += query(L[rt1], L[rt2], l, mid, ql, qr);
	if(mid < qr) ans += query(R[rt1], R[rt2], mid + 1, r, ql, qr);
	return ans;
}

int main() {
	scanf("%d", &n); build(T[0], 1, n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d", a + i);
		la[i] = pre[a[i]] + 1; pre[a[i]] = i;
		update(T[i - 1], T[i], 1, n, la[i]);
	}
	scanf("%d", &q);
	for(int l, r, i = 1; i <= q; i ++) {
		scanf("%d%d", &l, &r);
		printf("%d\n", query(T[l - 1], T[r], 1, n, 1, l));
	}
	return 0;
}
```

---

## 作者：灼眼的夏娜 (赞：9)

### 如何水过一道紫题

你突然发现它和P1972 一毛一样

。。。。。。

看看算法标签，嗯！没有树状数组？

你很生气，于是决定写一个二维树状数组水过它

离线操作，将询问区间右端点升序排列，从左往右扫，之前没有出现过

的元素加到树状数组上，出现过的减去，做个前缀和的差即可

原封不动的代码交了上去，发现A了。。。

## code
```cpp
#include<bits/stdc++.h>
#define R register
#define LL k<<1
#define RR k<<1|1

using namespace std;
const int N = 1e6+5;
int n,m;
int tr[N],ap[N];
int flag[N],ans[N];
struct seq{
	int l,r,id;
}q[N];

inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x = x*10+c-'0';c = getchar();}
    return x*f;
}

inline bool cmp(const seq &a,const seq &b) {return a.r < b.r;}

inline int lowbit(int x) {return x & (-x);}

inline void add(int x,int v)
{
	while(x <= n){
		tr[x] += v;
		x += lowbit(x);
	}
}

inline int query(int x)
{
	int res = 0;
	while(x > 0){
		res += tr[x];
		x -= lowbit(x);
	}
	return res;
}

int main()
{
	n = read();
	for(R int i = 1;i <= n;++ i) ap[i] = read();
	m = read();
	for(R int i = 1;i <= m;++ i){
		q[i].l = read();
		q[i].r = read();
		q[i].id = i;
	}
	sort(q+1,q+m+1,cmp);
	int nxt = 1;
	for(R int i = 1;i <= m;++ i){
		for(R int j = nxt;j <= q[i].r;++ j){
			if(flag[ap[j]]) add(flag[ap[j]],-1);
			flag[ap[j]] = j;
			add(j,1);
		}
		nxt = q[i].r + 1;
		ans[q[i].id] = query(q[i].r) - query(q[i].l-1);
	}
	for(R int i = 1;i <= m;++ i) printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：zhaotiensn (赞：7)

本来是想写主席树的在线写法的，练一练主席树，然后听说这题卡莫队，不信邪，写了一写，然后就过了，就懒得写主席树了。发现竟然没有人写题解，写一发莫队题解。

莫队复杂度O(q sqrt n)，SPOJ时限卡的比较紧，然而莫队还是能过（摊手）。

没有什么好讲的，就是莫队的模板，排序过后暴力跳和修改，记录当前区间内每种颜色的个数和一共的颜色种数。当一种颜色个数修改为0时总数减一，当一种为0的颜色个数修改为1时总数加一。

不过记录颜色个数好像不能用map，我一开始用map超时了，后来改成离散后开数组存就过了。

AC代码：
```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read(){
    int x=0;char ch=gc();bool positive=1;
    for(;!isdigit(ch);ch=gc())if(ch=='-')positive=0;
    for(;isdigit(ch);ch=gc())x=x*10+ch-'0';
    return positive?x:-x;
}

inline void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}

inline void writeln(int x){
    write(x);puts("");
}//以上为快读快输

struct Query{
    int l,r,id,ans;//l,r表示查询的区间,id表示第几个询问,ans表示答案
}q[200005];

struct Node{
    int id,num;
    inline bool operator<(const Node&x)const{
        return num<x.num;
    }//num表示颜色种类
}a[30005];

int n,m,l,r,len,sum,vis[30005],b[30005],id[200005];
//vis[i]表示颜色i在当前区间内一共出现了vis[i]次,id就是莫队排序用的
inline bool cmp1(Query x,Query y){
    if(id[x.l]==id[y.l]){
        if(id[x.l]&1){
            return x.r<y.r;
        }else{
            return x.r>y.r;
        }
    }else{
        return id[x.l]<id[y.l];
    }
}//莫队预处理询问的比较函数

inline bool cmp2(Query x,Query y){
    return x.id<y.id;
}//返回最初的询问顺序

inline void inc(int x){
    if(!vis[x])sum++;//修改总和
    vis[x]++;//增加颜色x的出现次数
}

inline void del(int x){
    vis[x]--;//减少颜色x的出现次数
    if(!vis[x])sum--;//同上
}

int main(){
    n=read();len=sqrt(n);
    for(int i=1;i<=n;i++){
        a[i].id=i;
        a[i].num=read();
        id[i]=(i-1)/len+1;
    }
    sort(a+1,a+n+1);//预处理询问
    b[a[1].id]=1;
    for(int i=2;i<=n;i++){
        if(a[i].num==a[i-1].num){
            b[a[i].id]=b[a[i-1].id];
        }else{
            b[a[i].id]=i;
        }
    }//离散颜色的种类
    m=read();
    for(int i=1;i<=m;i++){
        q[i].l=read();q[i].r=read();
        q[i].id=i;
    }
    sort(q+1,q+m+1,cmp1);
    for(int i=q[1].l;i<=q[1].r;i++)inc(b[i]);
    l=q[1].l;r=q[1].r;
    q[1].ans=sum;
    for(int i=2;i<=m;i++){//莫队
        while(l<q[i].l)del(b[l++]);
        while(l>q[i].l)inc(b[--l]);
        while(r<q[i].r)inc(b[++r]);
        while(r>q[i].r)del(b[r--]);
        q[i].ans=sum;
    }
    sort(q+1,q+m+1,cmp2);//输出答案
    for(int i=1;i<=m;i++)writeln(q[i].ans);
    return 0;
}
```

---

## 作者：2018chenyu (赞：6)

**[别人家的好博客](https://www.cnblogs.com/WAMonster/p/10118934.html)**  
**[别人家的好日报](https://www.luogu.org/blog/codesonic/Mosalgorithm)**  
------------
**你需要先了解一些[分块的知识](https://www.luogu.com.cn/blog/rocket-master/you-ya-di-pu-li-shang-fen-kuai)**  
### Opening words
经常听见别人说“莫队是优雅的暴力”，勾起了我的~~性欲~~学习欲望，而莫队也没有辜负我~~数十年如一日的追求~~的期望。  
### Introduction
莫队是由莫涛大神提出的，一种~~玄学毒瘤暴力骗分~~区间操作算法，它以简短的框架、简单易记的板子和优秀的复杂度闻名于世，是不可多得的、时间复杂度一般仅$O(n\sqrt{n})$的优秀离线暴力算法。  
莫队算法一般分为两类，一是莫队维护区间答案，二是维护区间内的数据结构。  

------------
### Example
上例题：  
[SP3267 DQUERY - D-query](https://www.luogu.org/problem/SP3267)  
即[[SDOI2009]HH的项链](https://www.luogu.org/problem/P1972)数据弱化版,~~毒瘤~~强大数据卡莫队（泪奔~）  
在本题中，莫队算法用于维护区间答案。  
#### Analyse
先思考朴素的暴力做法，每次操作从左往右扫，$O(nm)$十分快乐~~卡的又不是我~~。  
接着想到不用修改那么预处理好了，但是有个问题，每个操作有L、R两个关键字，所以分块，L接近的（在一个块中）就排R好了，上CMP：
```cpp
inline bool cmp(node a,node b) {return (belong[a.l]^belong[b.l])?belong[a.l]<belong[b.l]:a.r<b.r;}
```
然后搞L、R两个指针表示当前统计的区域，针对每个操作的L、R移动两个指针（由于已经预处理过，所以每次指针移动的幅度不大），一边移动一边维护-->每一步都是$O(1)$，看代码：
```cpp
inline void add(int x)
{
	if(!cnt[a[x]]) ans++;
	cnt[a[x]]++;
}
inline void del(int x)
{
	cnt[a[x]]--;
	if(!cnt[a[x]]) ans--;
}

while(l<Q[i].l) del(l++);
while(l>Q[i].l) add(--l);
while(r>Q[i].r) del(r--);
while(r<Q[i].r) add(++r);
```
不得不说，预处理的离线做法很快。以下是完整代码
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+10;
inline int read()
{
	int x=0;bool f=false;
	char ch=getchar();
	while(ch<'0' || ch>'9') f|=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
struct node{int l,r,id,ans;}Q[N];
int ans,a[N],belong[N],cnt[N];
inline bool cmp(node a,node b) {return (belong[a.l]^belong[b.l])?belong[a.l]<belong[b.l]:a.r<b.r;}
inline void add(int x)
{
	if(!cnt[a[x]]) ans++;
	cnt[a[x]]++;
}
inline void del(int x)
{
	cnt[a[x]]--;
	if(!cnt[a[x]]) ans--;
}
int main()
{
	int n=read();for(int i=1;i<=n;i++) a[i]=read();
	int m=read();for(int i=1;i<=m;i++) Q[i].l=read(),Q[i].r=read(),Q[i].id=i;//读入操作 
	int block=sqrt(n+1);for(int i=1;i<=n;i++) belong[i]=(i-1)/block+1;//分块 
	sort(Q+1,Q+m+1,cmp);//进行预处理 
	int l=1,r=0;ans=0;
	for(int i=1;i<=m;i++)
	{
		while(l<Q[i].l) del(l++);
		while(l>Q[i].l) add(--l);
		while(r>Q[i].r) del(r--);
		while(r<Q[i].r) add(++r);
		Q[Q[i].id].ans=ans;
	}
	for(int i=1;i<=m;i++) printf("%d\n",Q[i].ans);
	return 0;
}
```
#### Analyse*2  
如何进行~~毒瘤~~有效的优化呢？（卡常技巧篇）  

**1、#pragma GCC optimize(2)**  
可以用实践证明，开了O2的莫队简直跑得飞快，连1e6都能无压力跑过，甚至可以比不开O2的版本快上4~5倍乃至更多。然而~~大~~部分OI比赛中O2是禁止的，如果不禁O2的话，那还是开着吧qwq  
~~实在不行，就optimize(3)（逃~~  

**2、快读快写**  

**3、玄学奇偶性排序**  
我们正常的排序方式是这样的：  
```cpp
inline bool cmp(node a,node b) {return (belong[a.l]^belong[b.l])?belong[a.l]<belong[b.l]:a.r<b.r;}
```
然而，我们可以对左端点在同一奇数块的区间，右端点按升序排列，反之降序。这个东西看着没卵用，但实际效果显著。  
```cpp
bool cmp(node a,node b) {return (pos[a.l]^pos[b.l])?pos[a.l]<pos[b.l]:(pos[a.l]&1?a.r<b.r:a.r>b.r);}
```
实在是太**长**了，~~吓得我把inline删了~~belong改成pos。  
![](https://cdn.luogu.com.cn/upload/image_hosting/n1viz9g4.png)  
它的主要原理便是右指针跳完奇数块往回跳时在同一个方向能顺路把偶数块跳完，然后跳完这个偶数块又能顺带把下一个奇数块跳完。理论上主算法运行时间减半，实际情况有所偏差。（不过能优化得很爽就对了）  

**4、移动指针的常数压缩**  
把这一坨  
```cpp
inline void add(int x)
{
	if(!cnt[a[x]]) ans++;
	cnt[a[x]]++;
}
inline void del(int x)
{
	cnt[a[x]]--;
	if(!cnt[a[x]]) ans--;
}

while(l<Q[i].l) del(l++);
while(l>Q[i].l) add(--l);
while(r>Q[i].r) del(r--);
while(r<Q[i].r) add(++r);
```
压成
```cpp
while(l<Q[i].l) now-=!--cnt[a[l++]];
while(l>Q[i].l) now+=!cnt[a[--l]]++;
while(r<Q[i].r) now+=!cnt[a[++r]]++;
while(r>Q[i].r) now-=!--cnt[a[r--]];
```
不过会变得难以调试，初学者~~肾~~慎用  
**完结撒花！！**

---

## 作者：LCGUO (赞：3)

这题我是用莫队过的；  
众所周知，莫队是一个~~暴力毒瘤玄学~~很方便的算法（不套其他的数据结构），可以乱搞很多的区间问题。

p.s.我是通过这篇[博客](https://www.cnblogs.com/WAMonster/p/10118934.html)来自学的，如果有理解不对的地方，还望 dalao 指正

---
进入正题：  
莫队算法将询问排序后，通过移动左右端点来更改答案，从而保证它优秀的复杂度。

在排序询问时，我们要用到分块的思想：  
我们将整个区间分成 $\sqrt{n}$ 个块。

在排序的时候，如果左端点在同一个块，就将右端点按从大到小排序；否则，按左端点的块从大到小排序。

这样保证了每个端点一次最多移动 $\sqrt{n}$ 格，从而保证了复杂度。

```cpp
friend bool operator < (qus a,qus b){
    return k[a.l]==k[b.l]?a.r<b.r:k[a.l]<k[b.l];
}
```

然后在排序的时候可以将普通的排序，换成按块的奇偶分类排序，可以让你的代码玄学咕咕咕的加快。

```cpp
friend bool operator < (qus a,qus b){
    return k[a.l]^k[b.l]?k[a.l]<k[b.l]:(k[a.l]&1?a.r<b.r:a.r>b.r);
}
```

之后便是 `Add` 和 `Del` 函数，用来在移动的同时更新答案。

用 num 来记录目前的区间 $[l,r]$ 的数字种类，$cnt_x$ 来记录 x 出现的次数；

在加入第 pos 个数时，如果该数在这个区间第一次出现，则将总数加一：

```cpp
void Add(int pos){
    if(!cnt[a[pos]]) ++num;
    ++cnt[a[pos]];
}
```

在删除第 pos 个数时，如果删除后这个数在区间内不在出现，则将总数减一：

```cpp
void Del(int pos){
    --cnt[a[pos]];
    if(!cnt[a[pos]]) --num;
}
```

然后是转移左右端点。

如果当前的左端点，小于答案的左端点，则将该点删除，并将左端点向右移；  
如果当前的左端点，大于答案的左端点，则将左端点左移，并且将该点加入；  
如果当前的右端点，大于答案的右端点，则将该点删除，并将右端点向左移；  
如果当前的右端点，小于答案的右端点，这将右端点右移，并且将该点加入。  
（这不是绕口令）

```cpp
    while(L<q[i].l) Del(L++);
    while(L>q[i].l) Add(--L);
    while(R<q[i].r) Add(++R);
    while(R>q[i].r) Del(R--);
```

最后在统计答案的时候，按照原先输入的顺序输出就好了。

---

代码如下（码风有点丑）：

```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
inline int read(){
    int s=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=0;c=getchar();}
    while(c>='0'&&c<='9') s=(s<<1)+(s<<3)+(c^48),c=getchar();
    return f?s:-s;
}
int n,a[30010],cnt[1000010],num=0,Q;
int k[1010],ks,ans[200010];
struct qus{
    int l,r,id;
    friend bool operator < (qus a,qus b){
        return k[a.l]^k[b.l]?k[a.l]<k[b.l]:(k[a.l]&1?a.r<b.r:a.r>b.r);
    }
}q[200010];
void Del(int pos){
    --cnt[a[pos]];
    if(!cnt[a[pos]]) --num;
}
void Add(int pos){
    if(!cnt[a[pos]]) ++num;
    ++cnt[a[pos]];
}
int main(){
    n=read(); ks=sqrt(n);
    for(rint i=1;i<=n;++i) a[i]=read();
    for(rint i=1;i<=n;++i) k[i]=(i-1)/ks+1;
    Q=read();
    for(rint i=1;i<=Q;++i){
    	q[i].l=read();
        q[i].r=read();
        q[i].id=i;
    }
    sort(q+1,q+1+Q);
    int L=1,R=0;
    for(rint i=1;i<=Q;++i){
        while(L<q[i].l) Del(L++);
        while(L>q[i].l) Add(--L);
        while(R<q[i].r) Add(++R);
        while(R>q[i].r) Del(R--);
        ans[q[i].id]=num;
    }
    for(rint i=1;i<=Q;++i)
    	printf("%d\n",ans[i]);
    return 0;
}
```

咕咕咕~

---

## 作者：Carbon (赞：2)

没错，我又来写线段树的题解了。


首先，题意依旧不用说了；这道题要我们求的是区间有多少个不同的数字。我们发现，假设数组pos[i]表示的是：这个位置是不是数字i所出现的最后一个位置（目前），说以我们只需将输入的询问的数组按照右端点从小到大排序，每当我们遇到一个点时，我们只需将他的pos更新为last即可。这样我们只需用线段树维护pos数组即可。

Talk is cheap,show you the code

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N=2e5+5;
const int M=1e6+5;
int letter[N];//读入数组 
int L[N],R[N];//线段树的左右端点 
int ans[N];//保存答案 
int sum[N];//线段树 
int pos[M];//记录数上一次出现的位置 
int n,m;

struct node
{
	int x,y;//左右端点 
	int cnt;//读入的顺序 
	bool operator < (const node &b)const
	{
		return y<b.y;
	}
} a[N];


//线段树高清无码模板 
void build(const int &l,const int &r,const int &now)
{
	L[now]=l;
	R[now]=r;
	sum[now]=0;
	if (l==r)
	{
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,now<<1);
	build(mid+1,r,now<<1|1);
}

void update(const int &x,const int &now,const int &d)
{
	if (L[now]==R[now])
	{
		sum[now]+=d;
		return;
	}
	int mid=(L[now]+R[now])>>1;
	if (x<=mid)update(x,now<<1,d);
	else update(x,now<<1|1,d);
	sum[now]=sum[now<<1]+sum[now<<1|1];
}

int query(const int &l,const int &r,const int &now)
{
	if (L[now]==l&&R[now]==r)return sum[now];
	int mid=(L[now]+R[now])>>1;
	if (r<=mid)return query(l,r,now<<1);
	else if (l>mid)return query(l,r,now<<1|1);
	else return query(l,mid,now<<1)+query(mid+1,r,now<<1|1);
	sum[now]=sum[now<<1]+sum[now<<1|1];
}

int main()
{
	scanf("%d",&n);
	build(1,n,1);
	for (int i=1; i<=n; i++)
		scanf("%d",&letter[i]);
	scanf("%d",&m);
	for (int i=1; i<=m; i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].cnt=i;//小trick 
	}
	sort(a+1,a+1+m);
	int last=0;
	for (int i=1; i<=m; i++)
	{
		while (last<a[i].y)
		{
			last++;
			update(last,1,1);
			if (pos[letter[last]])
				update(pos[letter[last]],1,-1);
			pos[letter[last]]=last;
		}
		ans[a[i].cnt]=query(a[i].x,a[i].y,1);
	}
	for (int i=1; i<=m; i++)
		printf("%d\n",ans[i]);
	return 0;
}

```

---

## 作者：FourteenObsidian (赞：1)

强制在线数据结构题做多了，于是用分块写的。

没想到一遍过了。

首先离散化，

接着令 $num[i][j]$ 表示前 $i$ 块中 $j$ 的出现次数 

$col[i][j]$ 表示第 $i$ 块到第 $j$ 块间有多少不同的数

预处理后直接算就好了。

总复杂度： $O(n\sqrt{n})$

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100100,sqN = 1010;
int n,m,a[N],bl[N],st[N],ed[N],num[sqN][N],col[sqN][sqN],numb[N],cnt[sqN];//numb是用来储存当前块内i数的个数的
int a1[N],len;
int ans = 0,sum;
inline void build()
{
    sum = sqrt(n);
    for(register int i = 1; i <= sum; ++i)
        st[i] = (n / sum) * (i - 1) + 1,ed[i] = (n / sum) * i;
    ed[sum] = n;
    for(register int i = 1; i <= sum; ++i)
	{
        for(register int j = st[i]; j <= ed[i]; ++j)
            bl[j] = i,++num[i][a[j]];
    	for(register int j = 1; j <= len; ++j)//以块为单位求前缀和算出num数组
    		num[i][j] += num[i - 1][j];
    }
    for(register int i = 1; i <= sum; ++i)
	{
    	for(register int j = i; j <= sum; ++j)
		{
    		col[i][j] = col[i][j - 1];
			for(register int k = st[j];k <= ed[j];++k)
			{
				if(!(num[j - 1][a[k]] - num[i - 1][a[k]]) && (!numb[a[k]]))
				++col[i][j],++numb[a[k]];//如果第i块到第j - 1块间没有出现过，且在此块内第一次出现，就加上
			}
			for(register int k = st[j]; k <= ed[j]; ++k) numb[a[k]] = 0;//清空	
		}
	}
    return;     
}
inline int ask(int l,int r)
{
	int res = 0;
	if(bl[l] == bl[r])//在同一块内暴力计算
	{
        for(register int i = l; i <= r; ++i)
        	if(!numb[a[i]]++) ++res;
		for(register int i = l; i <= r; ++i) numb[a[i]]=0;
		return res;
    }
	res = col[bl[l] + 1][bl[r] - 1];//将答案先加上中间一段的数的个数
    for(register int i = l; i <= ed[bl[l]]; ++i)
    	if((!numb[a[i]]++) && !(num[bl[r] - 1][a[i]] - num[bl[l]][a[i]])) ++res;//如果在边角块中第一次出现且中间一段没出现，就累加
	for(register int i=st[bl[r]];i<=r;++i)
		if((!numb[a[i]]++) && !(num[bl[r] - 1][a[i]] - num[bl[l]][a[i]])) ++res;//同上
	for(register int i = l; i <= ed[bl[l]]; ++i) numb[a[i]] = 0;
	for(register int i = st[bl[r]]; i <= r; ++i) numb[a[i]] = 0;//清空
	return res;
}
int main()
{
	scanf("%d",&n);
	for(register int i = 1; i <= n; ++i)
		scanf("%d",&a[i]);
	memcpy(a1,a,sizeof(a));
	sort(a1 + 1, a1 + n + 1);
	len = unique(a1 + 1,a1 + n + 1) - a1 - 1;
	for(register int i = 1; i <= n; ++i)
        a[i] = lower_bound(a1 + 1,a1 + len + 1,a[i]) - a1;\\离散化
	build();
	int p,q,x = 0;
	scanf("%d",&m); 
	for(register int i = 1; i <= m; ++i)
	{
		scanf("%d%d",&p,&q);
		x = ask(p,q);// 在线题写多了（划掉）
		printf("%d\n",x);
	}
	return 0;
}
```


---

## 作者：nth_element (赞：1)

想要更丰富的展示，请点击[我的博客](https://www.cnblogs.com/nth-element/p/11785032.html)

***

若想要深入学习主席树，[传送门]( https://www.cnblogs.com/nth-element/p/11755820.html )。

***

**Description**:

给定数列 $\{a_n\}$ ,求闭区间 $[l,r]$ 的互异的个数。

**Method**:

扫描序列建立可持续化线段树，若此元素是第一次出现，就将对应的线段树中的位置加1；反之，就将上一个出现的元素对应的线段树中的位置减1，将此元素对应的线段树中的位置加1。

对于查询的 $[l,r]$ ，在第 $r$ 个版本的线段树上查询位置 $l$ ,对经过的区间中的和累加一下即可。

**Code**:

```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 30010
using namespace std;
inline void read(int &x)
{
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int n,q;
int a[Maxn]; 
int tot=0;
struct Segtree
{
    int ls,rs,sum;
}tree[Maxn<<5];
int rt[Maxn];
inline void Init(){tot=0;}
inline void pushup(int rt)
{
   tree[rt].sum=tree[tree[rt].ls].sum+tree[tree[rt].rs].sum;
}
inline int build(int l,int r)
{
    int rt=++tot;
    if(l==r) 
    {
        tree[rt].sum=0;
        return rt;
    }
    int mid=(l+r)/2;
    tree[rt].ls=build(l,mid);
    tree[rt].rs=build(mid+1,r);
    pushup(rt);
    return rt;
}
int update(int k,int l,int r,int root,int val)
{
    int rt=++tot;
    tree[rt]=tree[root];
    if(l==k&&r==k)
    {
        tree[rt].sum+=val;
        return rt;
    }
    int mid=(l+r)/2;
    if(k<=mid) tree[rt].ls=update(k,l,mid,tree[rt].ls,val);
    else tree[rt].rs=update(k,mid+1,r,tree[rt].rs,val);
    pushup(rt);
    return rt;
}
int query(int l,int r,int rt,int pos)
{
    if(l==r) return tree[rt].sum;
    int mid=(l+r)/2;
    if(pos<=mid) return tree[tree[rt].rs].sum+query(l,mid,tree[rt].ls,pos);
    else return query(mid+1,r,tree[rt].rs,pos);
}
map<int,int>mp;
signed main()
{
    Init();
    read(n);
    for(int i=1;i<=n;i++)
    {
        read(a[i]);
    }
    rt[0]=build(1,n);
    for(int i=1;i<=n;i++)
    {
        if(mp.find(a[i])==mp.end())
        {
            mp[a[i]]=i;
            rt[i]=update(i,1,n,rt[i-1],1);	
        }else
        {
            int tmprt=update(mp[a[i]],1,n,rt[i-1],-1);
            rt[i]=update(i,1,n,tmprt,1);
        }
        mp[a[i]]=i;
    }
    read(q);
    while(q--)
    {
        int l,r;
        read(l),read(r);
        int ans=query(1,n,rt[r],l);
        printf("%lld\n",ans);
    } 
    return 0;
}
```

---

## 作者：Jesselrj (赞：1)

### $Solution 1$ 暴力
根据每次询问的$[L, R]$区间， 每一次都用for循环循环一遍，用一个数组$cnt$记录有没有出现过这个数。

**时间复杂度** $O(m(n+s))$ ～ $O(n^2)$
这个时间复杂度肯定是会`TLE`到怀疑人生的。

### $Solution 2$ 暴力的基础上加点优化

#### 优化一

每次新增加数，枚举到一个值$num$,可以判断一下$cnt_{num}$是否为$0$，如果为$0$，那么代表这个数是一个新出现的数字，$ans$自然就要$+1$。

```cpp
void insert(int p) {
	if (!cnt[a[p]]) ++sum;
	++cnt[a[p]];
}
```


反之，如果是删除一个值$num$时，就应该在删去后判断$cnt_{num}$是否为$0$，如果为$0$，那么代表这个数已经不存在于这一区间里了，那么，$ans$自然就要$-1$。
 
```cpp
void remove(int p) {
	--cnt[a[p]];
	if (!cnt[a[p]]) --sum;
}
```



#### 优化二

用两个指针$l, r$来维护每次询问的边界，这样就不需要每次询问都直接枚举，而是通过不断移动$l, r$，直到&l, r&与$[L, R]$重合，然后运用优化一来统计答案。

```cpp
void work() {
	int l = 1, r = 0;
	for (int i = 1; i <= m; i++) {
		int ql = q[i].l, qr = q[i].r;
		while (l < ql) remove(l++);
		while (l > ql) insert(--l);
		while (r < qr) insert(++r);
		while (r > qr) remove(r--);
		ans[q[i].id] = sum;
	}
}

```

优化后的暴力，在普通的情况下表现还不错，但是遇到下图这种极端数据的情况，那么时间复杂度就会退化回$O(nm)$

![](https://img2018.cnblogs.com/blog/1539583/201812/1539583-20181214145508773-749403260.jpg)

图片转自[WAMonster dalao的莫队blog](https://www.cnblogs.com/WAMonster/p/10118934.html)

### $Solution 3$ 莫队

莫队的核心在于分块与排序，分完块之后进行一个对每个询问的$l$边界所在的块进行排序，如果两个询问所在的块相同，那么就按每个询问的$r$边界进行排序。

排序函数：
```cpp
bool cmp(Node a, Node b) {
	return a.seg == b.seg ? a.r < b. r : a.seg < b.seg;
}
```

当然，还有更快的~~玄学~~奇偶排序：
```cpp
bool cmp(Node a, Node b) {
	return (a.seg ^ b.seg) ? (a.seg < b.seg) : ((a.seg & 1) ? a.r < b.r : a.r > b.r);
}
```

而且，根据运算符优先级，我们可以把$Solution 2$中的部分改成：

```cpp
void work() {
	int l = 1, r = 0, sum = 0;
	for (int i = 1; i <= m; i++) {
		int ql = q[i].l, qr = q[i].r;
		while (l < ql) sum -= !--cnt[a[l++]];
		while (l > ql) sum += !cnt[a[--l]]++;
		while (r < qr) sum += !cnt[a[++r]]++;
		while (r > qr) sum -= !--cnt[a[r--]];
		ans[q[i].id] = sum;
	}
}
```

所以这道题的代码就是：
```cpp
#include <bits/stdc++.h>
#define Maxn 500100
using namespace std;

int a[Maxn], cnt[Maxn], num[Maxn], ans[Maxn];
int n, m, knum;
struct Node {
	int l, r, id, seg;
} q[Maxn];

bool cmp(Node a, Node b) {
	return (a.seg ^ b.seg) ? (a.seg < b.seg) : ((a.seg & 1) ? a.r < b.r : a.r > b.r);
}

void work() {
	int l = 1, r = 0, sum = 0;
	for (int i = 1; i <= m; i++) {
		int ql = q[i].l, qr = q[i].r;
		while (l < ql) sum -= !--cnt[a[l++]];
		while (l > ql) sum += !cnt[a[--l]]++;
		while (r < qr) sum += !cnt[a[++r]]++;
		while (r > qr) sum -= !--cnt[a[r--]];
		ans[q[i].id] = sum;
	}
}

int main() {
	scanf("%d", &n);
	knum = sqrt(n) * 1.5;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].id = i;
		q[i].seg = q[i].l / knum;
	}
	sort(q + 1, q + m + 1, cmp);
	work();
	for (int i = 1; i <= m; i++) 
		printf("%d\n", ans[i]);
	return 0;
} 
```

---

## 作者：crh1272336175 (赞：0)

今天本蒟蒻学了一下午，总算有一点搞懂莫队了，自然要发个题解庆祝一下

首先，感谢[这位大佬的blog](https://www.cnblogs.com/WAMonster/p/10118934.html)让我看懂了莫队

莫队是一个离线做法，思路的重点是要对询问进行排序，我们可以记录2个指针le和ri，每次完成一个询问开始下一个的时候，我们只要较少移动指针，就可以大大降低复杂度了

更巧妙的是，排序有2种

1. 朴素排序：
  若在同一段，按ri排序，否则按le排序
  
2.高级排序
  对于左端点在同一奇数块的区间，右端点按升序排列，反之降序
  
主要的难点就是这些了，看AC代码：

  ```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e6+5;
int n,m,t,ans;
int a[M],cnt[M],L[M],R[M],pos[M],Ans[M];
struct node
{
	int le,ri,id;
}q[M];
/*bool cmp(node x,node y)//普通的排序 
{
 	if(pos[x.l]!=pos[y.l]) return pos[x.l]<pos[y.l];
 	return pos[x.r]<pos[y.r];
}*/
bool cmp(node a, node b)//高级的排序 
{
	if(pos[a.le]^pos[b.le]) return pos[a.le]<pos[b.le];
	else if(pos[a.le]&1) return a.ri<b.ri;
	else return a.ri>b.ri;
}
inline int read()
{
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d",&q[i].le,&q[i].ri);
		q[i].id=i;
	}
}
inline void init()
{
	t=sqrt(n);
	for(int i=1; i<=t; i++)
	{
		L[i]=(i-1)*t+1;
		R[i]=i*t;
	}
	if(R[t]<n) 
	{
		L[t+1]=R[t]+1;
		R[++t]=n;
	}
	for(int i=1; i<=t; i++)
	    for(int j=L[i]; j<=R[i]; j++)
	        pos[j]=i;//pos表示某个数字属于哪个段 
}
inline void add(int x)
{
	if(!cnt[a[x]]) ans++;
	cnt[a[x]]++;
}
inline void del(int x)
{
	cnt[a[x]]--;
	if(!cnt[a[x]]) ans--;
}
int main()
{
	read();
	init();
	sort(q+1,q+1+m,cmp);
	int le=1,ri=0;
	for(int i=1; i<=m; i++)
	{
		int ql=q[i].le,qr=q[i].ri;
		while(le<ql) del(le++);
		while(le>ql) add(--le);
		while(ri<qr) add(++ri);
		while(ri>qr) del(ri--);
		Ans[q[i].id]=ans; 
	}
	for(int i=1; i<=m; i++)
	    printf("%d\n",Ans[i]);
	return 0; 
}
```


---

## 作者：盧鋅 (赞：0)

## **莫队!!!!**


------------
先说下基本思想吧,就是用l,r两个指针来回扫描,然后在O(1)的时间内完成有一次移动,顺便统计下ins(插入)或者del(删除)的值对区间有无贡献即可.

用 ans 记录总贡献,用 cnt 记录是否重复及重复数量,若重复则无贡献

则[l,r]与询问重合的时候ans即为答案.

但是很明显当询问区间不规律的时候,l和r两个指针就会"左右横跳",然后时间复杂度就会变大.

所以我们要对询问进行排序(分块),顺便加入玄虚优化,做法是块内按照块的奇偶性进行r随缘排序,块外按照l排序.

块的大小取n的1/4次方到3/4次方为好.通过分块的操作,我们可以是时间复杂度降为O(n的3/2次方).


对询问分块(手动滑稽)
```
struct query{
	int l,r,in,id;
	inline bool operator < (const query &a)const{
	if(!(in^a.in)){
		return (in&1)?r<a.r:r>a.r; 
	}
	return in<a.in;
	}
}q[maxn];
```
ins和del操作

```
inline void ins(int x){
	if(!cnt[a[x]]++)ans++;
}
inline void del(int x){
	if(!--cnt[a[x]])ans--;
}
```

------------
朴素的莫队之间的区别就是ins和del还有ans与cnt了

##### AC代码如下
```
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#include<cmath> 
#define maxn 1001000
using namespace std;
int ans,num[maxn],cnt[maxn],a[maxn];
int n,m,k,len;
#define re register
inline int read(){
	re int x=0;re bool y=0;re char ch;
	while(!isdigit(ch=getchar()))if(ch=='-')y=1;
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return y?-x:x; 
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
}
struct query{
	int l,r,in,id;
	inline bool operator < (const query &a)const{
	if(!(in^a.in)){
		return (in&1)?r<a.r:r>a.r; 
	}
	return in<a.in;
	}
}q[maxn];
inline void ins(int x){
	if(!cnt[a[x]]++)ans++;
}
inline void del(int x){
	if(!--cnt[a[x]])ans--;
}
int main(){
    n=read();
//    m=read();
//    k=read();
    len=sqrt(n);
    for(register int i=1;i<=n;++i){
        a[i]=read();
    }
    m=read();
    int x,y;
    for(register int i=1;i<=m;++i){
        x=read();
        y=read();
        q[i].l=x;
        q[i].r=y;
        q[i].in=(x-1)/len+1;
        q[i].id=i;
    }
    sort(q+1,q+1+m);
    int l=1,r=0;
    for(register int i=1;i<=m;++i){
        x=q[i].l;
        y=q[i].r;
        while(l<x)del(l++);
        while(l>x)ins(--l);
        while(r<y)ins(++r);
        while(r>y)del(r--);
        num[q[i].id]=ans;
    }
    for(register int i=1;i<=m;++i){
        write(num[i]);
        printf("\n");
    }
    return 0;
}
```
另附三倍AC

[P3901 数列找不同](https://www.luogu.org/problem/P3901)

[P2709 小B的询问](https://www.luogu.org/problem/P2709)


---

## 作者：Trimsteanima (赞：0)

## SP3267 DQUERY - D-query

[题目](https://www.spoj.com/problems/DQUERY/)

### $\mathcal{Description}$

给出一个长度为 $n$ 的数列，有 $q$ 个询问，需要求出在 $(l, r)$ 区间内有多少不同的数

### $\mathcal{Solution}$

这题就是 [[SDOI2009]HH的项链](https://www.luogu.org/problem/P1972) 的数据弱化版，可以把他当做莫队的模板题。

考虑最简单的做法，也就是暴力，用一个 $cnt$ 数组记录 $(l, r)$ 区间内（暴力扫一遍）每个数出现的次数，再扫一遍 $cnt$ 数组统计不为 $0$ 的个数，输出答案。

很容易想出第一步优化，在记录 $cnt$ 数组的同时，在加之前判断下是否为 $0$，也就是之前有没有出现过这个数，如果为 $0$ 那么$ans++$。

再考虑下优化，我们可以弄两个指针 $l$ 、$r$ ，每次询问移动 $l$、$r$ 到询问的区间，统计 $ans$ 时只需在两个指针处加减 $cnt$。

当然如果他需要查找的区间是这样的

![](https://i.loli.net/2019/09/28/Gtg6MfC4OE2YABQ.jpg)

所以我们还需将查询区间的左端点进行排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e4 + 10, M = 2e6 + 10;
int n, m, now, be[M], a[M], cnt[M], ans[M];
struct Node {
	int l, r, id;
} q[M];
inline int read() {
	int x = 0, k = 1; char c = getchar();
	for (; c < 48 || c > 57; c = getchar()) k ^= (c == '-');
	for (; c >= 48 && c <= 57; c = getchar()) x = x * 10 + (c ^ 48);
	return k ? x : -x;
}
inline bool cmp(Node a, Node b) {  // 奇偶性排序
	return (be[a.l] ^ be[b.l]) ? be[a.l] < be[b.l] : ((be[a.l] & 1) ? a.r < b.r : a.r > b.r);
} 
int main() {
	n = read();
	int sz = sqrt(n), n1 = ceil((double)n / sz);
	for (int i = 1; i <= n1; i++)   // 分块
		for (int j = (i - 1) * sz + 1; j <= i * sz; j++)
			be[j] = i;
	for (int i = 1; i <= n; i++)
		a[i] = read();
	m = read();
	for (int i = 1; i <= m; i++)
		q[i].l = read(), q[i].r = read(), q[i].id = i;
	std::sort(q + 1, q + 1 + m, cmp);
	int L = 1, R = 0;
	for (int i = 1; i <= m; i++) {
		int l = q[i].l, r = q[i].r;
		while (L < l)
			now -= !--cnt[a[L++]];
		while (L > l)
			now += !cnt[a[--L]]++;
		while (R < r)
			now += !cnt[a[++R]]++;
		while (R > r)
			now -= !--cnt[a[R--]];
		ans[q[i].id] = now;
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：苏幕寒 (赞：0)

莫队的版子题，先对问题进行分块，然后块内排序，然后回答问题就可以了；

不会莫队的可以看一下这个博客
[莫队](https://www.cnblogs.com/WAMonster/p/10118934.html)

代码简单易懂：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,a[N],ans[N],be[N],ks,sum,b[N];
struct md{
	int l,r,num;
}q[N];
bool cmp(md x,md y){
	return be[x.l]==be[y.l]?x.r<y.r:x.l<y.l;
}
void add(int x)
{
	b[x]++;
	if(b[x]==1) sum++;
}
void aee(int x)
{
	b[x]--;
	if(b[x]==0) sum--;
}
int main()
{
	scanf("%d",&n);ks=sqrt(n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].num=i;be[i]=i/ks+1;
	}
	sort(q+1,q+1+m,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l<q[i].l) aee(a[l]),l++;
		while(l>q[i].l) l--,add(a[l]);
		while(r>q[i].r) aee(a[r]),r--;
		while(r<q[i].r) r++,add(a[r]);
		ans[q[i].num]=sum;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
```
完结撒花



---

## 作者：yzhang (赞：0)

### [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/10004083.html)

### [原题传送门](https://www.luogu.org/problemnew/show/SP3267)

### 这题和[Luogu P1972 [SDOI2009]HH的项链](https://www.luogu.org/problemnew/show/P1972)很像，只是数据大小有些差别，[题解](https://www.cnblogs.com/yzhang-rp-inf/p/10004039.html)

### [我博客里对莫队的介绍](https://www.cnblogs.com/yzhang-rp-inf/p/9991671.html)

我们在排序询问时，普通是这样qaq

```cpp
inline bool cmp(register query a,register query b)
{
    return a.bl==b.bl?a.r<b.r:a.bl<b.bl;
}
```

我加了一个奇偶优化：按奇偶块排序。如果区间左端点所在块不同，那么就直接按左端点从小到大排；如果相同，奇块按右端点从小到大排，偶块按右端点从大到小排。

```cpp
inline bool cmp(register query a,register query b)
{
    return a.bl!=b.bl?a.l<b.l:((a.bl&1)?a.r<b.r:a.r>b.r);
}
```

剩下我们就按照莫队的板子模拟就行啦qaq

完整代码：

```cpp
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define N 500005
using namespace std;
inline int read()
{
	register int x=0,f=1;register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
inline void write(register int x)
{
	if(!x)putchar('0');if(x<0)x=-x,putchar('-');
	static int sta[25];int tot=0;
	while(x)sta[tot++]=x%10,x/=10;
	while(tot)putchar(sta[--tot]+48);
}
struct query{
	int l,r,id,bl;
}q[N];
int num[1000001],blocksize=0,a[N],ans[N];
inline bool cmp(register query a,register query b)
{
	return a.bl!=b.bl?a.l<b.l:((a.bl&1)?a.r<b.r:a.r>b.r);
}
int main()
{
	int n=read();
	blocksize=sqrt(n);
	for(register int i=1;i<=n;++i)
		a[i]=read();
	int m=read();
	for(register int i=1;i<=m;++i)
	{
		int l=read(),r=read();
		q[i]=(query){l,r,i,l/blocksize};
	}
	sort(q+1,q+1+m,cmp);
	int l=1,r=0,sum=0;
	for(register int i=1;i<=m;++i)
	{
		int ll=q[i].l,rr=q[i].r;
		while(ll<l)
			sum+=!num[a[--l]]++;
		while(ll>l)
			sum-=!--num[a[l++]];
		while(rr>r)
			sum+=!num[a[++r]]++;
		while(rr<r)
			sum-=!--num[a[r--]];
		ans[q[i].id]=sum;
	}
	for(register int i=1;i<=m;++i)
		write(ans[i]),printf("\n");
	return 0;
}
```

---

## 作者：meisr (赞：0)

感兴趣的可以了解一下p1972，题目格式相同，但是数据范围大得多。

这是一道罕见的使用离散化加线段树的noip（雾）而不是莫队和主席树的算法。

以下是思路：


------------
我们先考虑没有重合元素的序列，求它在不同区间内的元素种类数。

很明显，这就是一道简单的无修改，区间求和的题目。

但题目中出现了重合元素。此时我们需要考虑重合元素对不同序列的影响。

在只考虑某一个区间的情况下，我们可以发现，如果一个点的位置小于我们当前考虑的区间的左端点，那么这个点是显然对答案是没有任何贡献的；而对于同种元素的所有点而言，它们中有可能贡献答案的那一部分（以下称为可贡献点）对答案的贡献，和所有可贡献点中离着区间左端点最近的那**一个**可贡献点对答案的贡献是必然相同的。而证明显然。

于是考虑离散化，按照所有询问区间的左端点排序。对于第i个点而言，我们记录在它后面、离它最近且与它元素相同的点nxt[i]，同时将所有元素的第一个点在线段树中计数。同时维护一个变量（可以理解为一个指针），表示上一个区间的左端点。当前区间的左端点若大于上一个区间的左端点，那么变量就会变化相应的位置；变量每变化一个位置，如从i变化为i+1时，i这个点将不会在未来的询问中做出任何贡献。而为了在接下来的询问中统计贡献，我们需要在nxt[i]的位置+1而清空i位置的贡献。

以下为代码：
```
#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)>>1)
#define lson rt<<1,l,mid
#define rson rt<<1|1,mid+1,r
#define update() nod[rt]=nod[rt<<1]+nod[rt<<1|1]
const int N=2e6+10;
int n,m,a[N],nxt[N],nod[N<<2],head[N];
struct Query{int l,r,id,ans;}q[N];
inline void modify(int rt,int l,int r,int pos,int goal){
	if(l==pos&&r==pos){
		nod[rt]=goal;
		return;
	}
	if(l>pos||r<pos) return;
	modify(lson,pos,goal);
	modify(rson,pos,goal);
	update();
}
inline int query(int rt,int l,int r,int L,int R){
	if(L<=l&&r<=R) return nod[rt];
	if(l>R||L>r) return 0;
	return query(lson,L,R)+query(rson,L,R);
}
inline bool cmp(Query x,Query y){return x.l<y.l;}
inline bool comp(Query x,Query y){return x.id<y.id;}
inline int read(){
	int a=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
	return a*f;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n;i;i--) if(!head[a[i]]) modify(1,1,n,i,1),head[a[i]]=i; else nxt[i]=head[a[i]],head[a[i]]=i,modify(1,1,n,i,1),modify(1,1,n,nxt[i],0);
	cin>>m;
	for(int i=1;i<=m;i++) q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	int nowl=1;
	for(int i=1;i<=m;i++){
		while(nowl<q[i].l){
			modify(1,1,n,nowl,0);
			modify(1,1,n,nxt[nowl],1);
			nowl++;
		}
		q[i].ans=query(1,1,n,q[i].l,q[i].r);
	}
	sort(q+1,q+m+1,comp);
	for(int i=1;i<=m;i++) cout<<q[i].ans<<"\n";
} 
```


---

## 作者：孑彧 (赞：0)

# SP3267 DQUERY 解题报告

### 题目描述

给出一个长度为n 的数列，$a_{1} ,a_{2},...,a_{n} $，有q 个询问，每个询问给出数对(i,j),需要你给出$a_{i},a_{i+1} ,...,a_{j}$ 这一段中有多少不同的数字

### 思路

很明显的是，这道题和[这道题](https://www.luogu.org/problem/P1972)是完全一样的，但是！！！这个题不会卡莫队

~~嘿嘿嘿~~

然后我就把被P1972卡掉的莫队放到这里，然后就过了

[P1972题解链接](https://hybjzzq.blog.luogu.org/p1927-hh-di-xiang-lian-xie-ti-bao-gao)

说句闲话，~~莫队真好用~~

### 代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define maxn 1100000
using namespace std;
int c[maxn],col[maxn],ans;
int n,m,len;
int num[maxn];
inline int read(){
	register int x=0,t=1;
      register char ch=getchar();
      while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
      if(ch=='-'){t=-1;ch=getchar();}
      while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
      return x*t;
}
struct Query{
	int l,r,in,id;
	inline bool operator < (const Query &a)const{
		if(!(in^a.in)){
			return (in&1)?r<a.r:r>a.r;
		}
		return in<a.in;
	}
}q[maxn];
inline void change(int x,int k){
	col[c[x]]+=k;
	if(col[c[x]]==0&&k==-1)--ans;
	if(col[c[x]]==1&&k==+1)++ans;
}
int main(){
	n=read();
	len=sqrt(n);
	for(register int i=1;i<=n;i++){
		c[i]=read();
	}
	m=read();
	for(register int i=1;i<=m;i++){
		q[i].l=read();
		q[i].r=read();
		q[i].in=(q[i].l-1)/len+1;
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	int l=1,r=0;
	for(register int i=1;i<=m;i++){
		while(l<q[i].l)change(l,-1),l++;
		while(l>q[i].l)change(l-1,1),l--;
		while(r<q[i].r)change(r+1,1),r++;
		while(r>q[i].r)change(r,-1),r--;
		num[q[i].id]=ans;
	}
	for(register int i=1;i<=m;i++){
		printf("%d\n",num[i]);
	}
	return 0;
}
```



---

## 作者：Skeleton (赞：0)

其实这道题和HH项链几乎就是一道题，这里我用树状数组A掉的。

直接上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e6+1;
int n,m,k=1;
int las[Maxn];//记录
int rec[Maxn];
int res[Maxn];
int sum[Maxn];
struct Skeleton
{
    int l,r,pos;
}ask[Maxn];//离线操作所用的结构体

bool cmp(Skeleton x,Skeleton y)
{
    return x.r<y.r;
}
int lowbit(int x)//板子
{
    return x&(-x);
}
void update(int rt,int v)//板子
{
    while(rt<=n)
    {
        sum[rt]+=v;
        rt+=lowbit(rt);
    }
}
int asksum(int rt)//板子
{
    int res=0;
    while(rt>0)
    {
        res+=sum[rt];
        rt-=lowbit(rt);
    }
    return res;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int num;
        scanf("%d",&num);
        las[i]=rec[num]?rec[num]:Maxn+1;//las[i]表示对于i这个位置，上一次出现数字num的位置。
        rec[num]=i;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d",&ask[i].l,&ask[i].r);//对于询问的区间进行离线操作
        ask[i].pos=i;//记录询问位置，便于排序后输出
    }
    sort(ask+1,ask+m+1,cmp);//按r的升序排序
    for(int i=1;i<=m;i++)
    {
        while(k<=ask[i].r)
        {
            update(las[k],-1);//因为只考虑右端最后出现的数，所以把之前的全部清零
            update(k,1);
            k++;
        }
        res[ask[i].pos]=asksum(ask[i].r)-asksum(ask[i].l-1);//区间查询
    }
    for(int i=1;i<=m;i++)//离线输出
    {
        printf("%d\n",res[i]);
    }
    return 0;
}
```

---

