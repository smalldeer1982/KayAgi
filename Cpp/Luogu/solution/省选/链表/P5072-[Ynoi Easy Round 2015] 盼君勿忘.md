# [Ynoi Easy Round 2015] 盼君勿忘

## 题目背景

说起来，幸福本身就是因人而异的  
有些人认为只要能混口饭吃就行了  
有些人只要有书读就能满足  
![](https://cdn.luogu.com.cn/upload/pic/45571.png)  
有些人认为只有全力地生存才是最重要的  
有些人只要得到克服某种目标的瞬间就能满足  
有些人只要某个人得到幸福，自己就会跟着幸福  
也有些人则令人伤透脑筋地刚好相反  
![](https://cdn.luogu.com.cn/upload/pic/45572.png)
但是，大部分人都没有自觉  
他们不知道究竟什么能给自己带来幸福  
但是，他们会异口同声地表示想要获得幸福  
那样的人即使能察觉到幸福  
也没办法变得幸福  
最重要的是要敢于正视自己的内心  
![](https://cdn.luogu.com.cn/upload/pic/45573.png)  
【珂朵莉已经基本上不剩什么了】  
![](https://cdn.luogu.com.cn/upload/pic/45574.png)  
【心灵和身体，珂朵莉基本上快要全部失去了】  
![](https://cdn.luogu.com.cn/upload/pic/45575.png)  
【全部被我替换了】  
![](https://cdn.luogu.com.cn/upload/pic/45576.png)  
【幸好你在失去一切之前，回到了这里】  
【喜悦和悲伤】  
【还有喜欢某个人的情绪】  
【现在依旧还残存着一些吧？】  
嗯...  
确实还有那么一丝...  
【那就没问题了】  
【珂朵莉你，依旧是珂朵莉】  
![](https://cdn.luogu.com.cn/upload/pic/45578.png)  
![](https://cdn.luogu.com.cn/upload/pic/45579.png)  
威...廉...？   
![](https://cdn.luogu.com.cn/upload/pic/45580.png)  


## 题目描述

珂朵莉给了你一个序列，每次查询一个区间 $[l,r]$ 中所有子序列分别去重后的和 $\bmod\ p$。

## 说明/提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

对于 $100\%$ 的数据，$1\leq n,m,a_i \leq 10^5$，$1\leq p\leq 10^9$，$1\leq l\leq r\leq n$。

## 样例 #1

### 输入

```
5 5
1 2 2 3 4
1 2 233333
2 3 333333
1 5 5
3 5 15
2 4 8```

### 输出

```
6
6
1
6
0```

# 题解

## 作者：chenzida (赞：52)

>在太阳西斜的这个世界里，置身天上之森。等这场战争结束之后，不归之人与望眼欲穿的众人， 人人本着正义之名，长存不灭的过去、逐渐消逝的未来。我回来了，纵使日薄西山，即便看不到未来，此时此刻的光辉，**盼君勿忘**。————世界上最幸福的女孩

珂朵莉，要一直幸福哦。

第一道珂朵莉相关 $\text{Ynoi}$ 祭。

这题的难点首先在读题。。。去重是对于每一个子序列分别去重，比如 $1,2,4,2,2$ 去重之后是 $1,2,4$。而不是有两个子序列完全相同时去掉其中一个。

然后读完这个题之后我们发现，如果是有重复的就消去只剩一个，那么每个数在一个子序列中只会出现一次。假设在一个长度为 $t$ 的序列中，数字 $x$ 出现了 $k$ 次，那么它的贡献就是 $(2^t-2^{n-k})x$。

这个式子的证明就是容斥，整体减不合法。如果不选数 $x$ 的话就是剩下 $t-k$ 个随便选，也就是 $2^{t-k}$。

将这个式子推出来之后我就想直接莫队了，却忽略了一个最大难点，那就是随着区间的移动，我们的区间长度是在不断改变的，也就是 $t$ 其实是不确定的。

所以我们必须将所有贡献以一种形式存储下来，以便莫队移动区间后改变 $t$ 之后使用。

考虑一个在 $\text{Ynoi}$ 中常见的思路，根号分治。

当出现次数 $\leq \sqrt n$ 次的时候，我们出现记录次数，并且记录出现这个次数的数的和。由于乘法结合律，所以我们将这些数绑在一起乘是没有问题的。

当出现次数 $> \sqrt n$ 次的时候，我们记录数，并且直接用 $cnt$ 数组来查看次数。

大体思路明确了，剩下几个小问题

我们的时间复杂度是 $n\sqrt n$ 的，但是如果一不小心就会退化成 $n\sqrt n\log n$。

对于这个问题我们有两个东西要重点说一下。

1.维护出现次数 $> \sqrt n$ 的数，我们发现，在这若干种数中，只有不到 $\sqrt n$ 个数出现次数**有可能** $>\sqrt n$。所以我们考虑先预处理一下，将所有在整个序列中出现次数 $>\sqrt n$ 的数都处理出来。也就是说，我不管这个数实际出现几次，我只管它的“天赋”，也就是最多出现的次数会不会超过 $\sqrt n$。如果会的话，我就直接通过 $cnt$ 处理。时间复杂度还是 $n\sqrt n$。

2.快速查询 $2^t$ 的方法。这个方法很明显不能用快速幂，否则时间复杂度会退化。分析复杂度发现，我们可以容忍的最大复杂度是预处理 $O(\sqrt n)$，查询 $O(1)$。比起查询的 $O(1)$，我们发现预处理的时间较为宽裕，所以我们考虑光速幂，即预处理出来 $2^0,2^1...,2^{\sqrt n-1}$ 以及 $2^{\sqrt n},2^{2\sqrt n}...2^{\sqrt n\times \sqrt n}$。然后 $O(1)$ 组合相乘查询即可。

注意其中的 $\sqrt n$ 均表示 $n$ 的算术平方根下取整。

然后这题也没啥细节了，反正我是用了很短的时间一遍就过了。


---

## 作者：rui_er (赞：42)

**2020.1.4 更新：代码被人 hack 了，是光速幂只处理到 $\sqrt{n}$ 导致剩余部分未定义的错误，已经修改，求再次审核。**

---

给定一个序列，每次查询一个区间 $[l,r]$ 中所有子序列分别去重后的和  $s\bmod{p}$ 的结果。

---

乍一看好像不太可做，仔细分析发现有点规律：

**在一个长度为 $a$ 的序列中，一个数出现次数为 $b$。则有 $2^{a-b}$ 个子序列不包含该元素，它的贡献是 $2^a-2^{a-b}$。**

问题转化为如何快速求出每一个数的贡献值。

$10^5$、离线、维护数列，想到什么？莫队！

我们使用**莫队**记录**双向链表**（建议手写），维护每个数分别的出现次数，下标表示数，内容为出现次数。则这个链表的元素个数大致在 $\sqrt{n}$ 级别。在跳到当前区间后，枚举维护的链表，对于每个元素分别算出贡献值后相加即可。

还剩下最后一个问题：如何快速求出 $2^k$？普通的快速幂可能做不到，因为带一只 $\log$，容易被卡。果断选用**光速幂**。

光速幂是什么呢？就是一种 $\mathcal{O(\sqrt{n})}$ 预处理、$\mathcal{O(1)}$ 查询的，求特定底数的幂的快速方法。具体方案是：预处理 $2^1,2^2,\cdots,2^{\sqrt{n}}$ 和 $2^{\sqrt{n}},2^{2\times\sqrt{n}},\cdots,2^n$，然后根据商和余数即可 $\mathcal{O(1)}$ 求出结果。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e5+5;

ll n, m, a[N], SIZE, cnt[N], s[N], ans[N];
#define whichBlock(x) (\
	(x-1)/SIZE+1\
)
struct Query {
	ll l, r, p, id;
	Query(ll a=0, ll b=0, ll c=0, ll d=0) : l(a), r(b), p(c), id(d) {}
	~Query() {}
	friend bool operator < (const Query &a, const Query &b) {
		ll x = whichBlock(a.l), y = whichBlock(b.l);
		if(x == y) return a.r < b.r;
		return x < y;
	}
}q[N];
struct myList {
	struct Node {
		ll pre, nxt;
		Node(ll a=0, ll b=0) : pre(a), nxt(b) {}
		~Node() {}
	}nd[N];
	ll tot;
	myList(ll a=0) : tot(a) {}
	~myList() {}
	void insert(ll x) {
		nd[tot].nxt = x;
		nd[x].pre = tot;
		tot = x;
	}
	void erase(ll x) {
		if(x != tot) {
			nd[nd[x].pre].nxt = nd[x].nxt;
			nd[nd[x].nxt].pre = nd[x].pre;
		}
		else {
			nd[nd[x].pre].nxt = 0;
			tot = nd[x].pre;
		}
		nd[x] = Node();
	}
}lst;
namespace qpow {
	ll pow1[N], pow2[N];
	void initPow(ll mod) {
		pow1[0] = pow2[0] = 1;
		for(ll i=1;i<=SIZE+5;i++) pow1[i] = pow1[i-1] * 2 % mod;
		for(ll i=1;i<=SIZE+5;i++) pow2[i] = pow2[i-1] * pow1[SIZE] % mod;
	}
	ll calc(ll x, ll mod) {return pow1[x%SIZE]*pow2[x/SIZE]%mod;}
}
void upd(ll x, ll k) {
	if(!(s[cnt[a[x]]]-=a[x])) lst.erase(cnt[a[x]]);
	if(!s[cnt[a[x]]+=k]) lst.insert(cnt[a[x]]);
	s[cnt[a[x]]] += a[x];
}

int main() {
	scanf("%lld%lld", &n, &m);
	SIZE = sqrt(n);
	for(ll i=1;i<=n;i++) scanf("%lld", &a[i]);
	for(ll i=1;i<=m;i++) scanf("%lld%lld%lld", &q[i].l, &q[i].r, &q[i].p), q[i].id = i;
	sort(q+1, q+1+m);
	ll l = 1, r = 0;
	for(ll i=1;i<=m;i++) {
//		printf("QUERY #%d: id=%d l=%d r=%d p=%d\n", i, q[i].id, q[i].l, q[i].r, q[i].p);
		qpow::initPow(q[i].p);
		while(l > q[i].l) upd(--l, 1);
		while(r < q[i].r) upd(++r, 1);
		while(l < q[i].l) upd(l++, -1);
		while(r > q[i].r) upd(r--, -1);
		for(ll j=lst.nd[0].nxt;j;j=lst.nd[j].nxt) {
//			printf("LIST POSITION: %d\n", j);
			ll _1 = qpow::calc(r-l+1, q[i].p);
			ll _2 = qpow::calc(r-l+1-j, q[i].p);
			ll _3 = ((_1 - _2) * s[j] + q[i].p) % q[i].p;
			ans[q[i].id] = (ans[q[i].id] + _3 + q[i].p) % q[i].p;
		}
	}
	for(ll i=1;i<=m;i++) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：mrsrz (赞：25)

> 在太阳西斜的这个世界里，置身天上之森。等这场战争结束之后，不归之人与望眼欲穿的众人， 人人本着正义之名，长存不灭的过去、逐渐消逝的未来。我回来了，纵使日薄西山，即便看不到未来，此时此刻的光辉，盼君勿忘。————世界上最幸福的女孩

珂朵莉，要永远幸福哦。

---

我们考虑每个数的贡献。即该区间内含有这个数的子序列个数。用补集转化为不含这个数的子序列个数。

那么，假设这个数在$[l,r]$内出现了$k$次，则一共有$2^{r-l+1}-2^{r-l+1-k}$个子序列**包含**这个数。

所以，我们莫队，维护所有出现$k$次的不同数的和，然后包含这些数的子序列个数都相同，所以直接用和来计算贡献即可。

时间复杂度$O(nm)$~~，非常优秀~~。

考虑根号内分类讨论。

对于出现次数大于$\sqrt n$的数，这种数最多不到$\sqrt n$个。

所以我们莫队，统计出现次数小于等于$\sqrt n$的所有出现次数为$i$的和$s_i$，然后用一个东西来维护所有出现次数大于$\sqrt n$的数。

这样的话，每次询问的复杂度就是$O(\sqrt n)$了。

看上去好像没什么问题，实际上你会发现求2的幂次还有个$\log$，而且模数会改，不好预处理。

有一种分块$O(\sqrt n)$预处理，$O(1)$求幂次的方法，具体就是求出$2^0,2^1,2^2,\dots,2^{{\sqrt n}-1}$和$2^{\sqrt n},2^{2\sqrt n},\dots,2^n$（模意义），然后每个幂都分成两部分相乘即可。

每次询问重新计算一遍即可。

然后我们考虑用什么东西来维护出现次数大于$\sqrt n$的数。我用了unordered_set，理论上是线性的~~（当然这个理论有多可靠就不知道了）~~。

这样总时间复杂度$O((n+m)\sqrt n)$，空间复杂度$O(n)$。

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#include<vector>
#include<unordered_set>
#ifdef ONLINE_JUDGE
struct istream{
    char buf[23333333],*s;
    inline istream(){
        buf[fread(s=buf,1,23333330,stdin)]='\n';
        fclose(stdin);
    }
    inline istream&operator>>(int&d){
        d=0;
        for(;!isdigit(*s);++s);
        while(isdigit(*s))
        d=(d<<3)+(d<<1)+(*s++^'0');
        return*this;
    }
}cin;
struct ostream{
    char buf[8000005],*s;
    inline ostream(){s=buf;}
    inline ostream&operator<<(int d){
        if(!d){
            *s++='0';
        }else{
            static int w;
            for(w=1;w<=d;w*=10);
            for(;w/=10;d%=w)*s++=d/w^'0';
        }
        return*this;
    }
    inline ostream&operator<<(const char&c){*s++=c;return*this;}
    inline void flush(){
        fwrite(buf,1,s-buf,stdout);
        s=buf;
    }
    inline~ostream(){flush();}
}cout;
#else
#include<iostream>
using std::cin;
using std::cout;
#endif
#define siz 317
#define N 100005
int n,m,a[N],buc[N],_2[siz+2],__2[siz+2],out[N];
long long bvc[siz+2];
std::vector<int>lr;
std::unordered_set<int>s;
inline int pow2(int b,const int&md){
	int ret=1,a=2;
	for(;b;b>>=1,a=1LL*a*a%md)
	if(b&1)ret=1LL*ret*a%md;
	return ret;
}
inline int pw2(int m,const int&md){
	return 1LL*_2[m%siz]*__2[m/siz]%md;
}
struct que{
	int l,r,id,md;
	inline bool operator<(const que&rhs)const{
		return(l/siz!=rhs.l/siz)?(l<rhs.l):(r<rhs.r);
	}
}q[N];
inline void add(int pos){
	const int val=a[pos];
	if(buc[val]>siz)++buc[val];else
	if(buc[val]==siz)bvc[buc[val]++]-=lr[val],s.insert(val);else
	bvc[buc[val]]-=lr[val],bvc[++buc[val]]+=lr[val];
}
inline void del(int pos){
	const int val=a[pos];
	if(buc[val]>siz+1)--buc[val];else
	if(buc[val]==siz+1)s.erase(val),bvc[--buc[val]]+=lr[val];else
	bvc[buc[val]]-=lr[val],bvc[--buc[val]]+=lr[val];
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;lr.push_back(a[i++]))cin>>a[i];
	std::sort(lr.begin(),lr.end());
	for(int i=1;i<=n;++i)a[i]=lower_bound(lr.begin(),lr.end(),a[i])-lr.begin();
	for(int i=1;i<=m;++i)
	cin>>q[q[i].id=i].l>>q[i].r>>q[i].md;
	std::sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1;i<=n;++i)*bvc+=a[i];
	*_2=*__2=1;
	for(int i=1;i<=m;++i){
		while(r<q[i].r)add(++r);
		while(l>q[i].l)add(--l);
		while(r>q[i].r)del(r--);
		while(l<q[i].l)del(l++);
		const int md=q[i].md,len=r-l+1;
		for(int j=1;j<siz;++j)
		_2[j]=2LL*_2[j-1]%md;
		__2[1]=pow2(siz,md);
		for(int j=2;j<=siz;++j)
		__2[j]=__2[1]*1LL*__2[j-1]%md;
		int&ans=out[q[i].id];
		const int all=pw2(len,md);
		for(int j=1;j<=siz;++j)
		(ans+=1LL*(all-pw2(len-j,md)+md)*bvc[j]%md-md)+=ans>>31&md;
		for(int j:s){
			(ans+=1LL*(all-pw2(len-buc[j],md)+md)*lr[j]%md-md)+=ans>>31&md;
		}
	}
	for(int i=1;i<=m;++i)cout<<out[i]<<'\n';
	return 0;
}
```

---

## 作者：SIXIANG32 (赞：16)

> 在太阳西斜的这个世界里，置身天上之森。等这场战争结束之后，不归之人与望眼欲穿的众人， 人人本着正义之名，长存不灭的过去、逐渐消逝的未来。我回来了，纵使日薄西山，即便看不到未来，此时此刻的光辉，盼君勿忘。————世界上最幸福的女孩

珂朵莉最最最最最最最珂爱了！  
闲话少说，切入正题

---
第一道 Ynoi&400 题祭  
~~害怎么又暴露自己的菜鸡水平了~~  
显然，$1\le n,m,a_i \le 10^5$ 这样友好的数据，没有修改的良心操作和可以离线的痕迹，这很显然是个莫队。  
但是我们会发现“子序列”“去重”这些东东不好计算，我们转化成贡献。  

设 $[l,r]$ 这个区间内有一个 $x$，这个 $x$ 又出现了 $k$ 次，我们来计算 $x$ 对于 $[l,r]$ 的贡献。  
很显然，$[l,r]$ 有 $2^{r-l+1}$ 个子序列，因为每个元素只有两种状态：选或不选，那么不包含 $x$ 的子序列有多少个呢？显然就有 $2^{r-l+1-k}$ 个，由此，我们将两个相减就能得到包含 $x$ 的子序列个数：$2^{r-l+1}-2^{r-l+1-k}$ 就是包含 $x$ 的子序列个数。所以 $x$ 的贡献就是 $x\times (2^{r-l+1}-2^{r-l+1-k})$。   

---
设 $sum_i$ 为出现次数为 $i$ 的和，$cnt_i$ 为 $i$ 数出现的次数。  
然后我们需要一个 DS 来维护一串数量，这些数量为一个数出现的个数，需要支持快速遍历，插入和删除，显然可以用双向链表来维护。  
然后我们就可以用莫队来维护这个 $sum_i$，在插入删除时维护数量链表，最后遍历链表然后根据上面的贡献公式直接累加就好了~  

---
还有一个问题，就是该题中我们要多次计算二的次幂，然而鹅快速幂是 $\log_2 n$ 的，这该怎么办？  
黑科技光速幂出现了！  
光速幂是什么？就是预处理 $2^0$ 到 $2^{\sqrt n}$ 和 $2^{\sqrt n},2^{2\times {\sqrt{n}}},2^{3\times {\sqrt{n}}}...2^n$，每个幂次我们都把它看成两个部分相乘就可以 $O(1)$ 计算啦~

---
还有一个重要的事情：  
**能用 $a_i+a_i$，不用 $a_i\times2$**  
对于我这样并不怎么卡过常的蒟蒻来说这很重要，不然乘 2 试试就逝世/dk  

---
上代码！  
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#define MAXN 100010
#define int long long//这道题的常数不怎么卡，可以这样写
using namespace std;
int n,m,len;
struct node{//莫队输入
	int l,r,cl,ind,k;
}in[MAXN];
inline int read()//快读
{
    int ans=0;
    char ch=getchar();
    while (ch<'0' || ch>'9') ch=getchar();
    while (ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
    return ans;
}
inline void write(int x)
{
    char f[200];
    int tmp=x>0?x:-x,cnt=0;
    if(x==0)putchar('0'),putchar('\n');
    else{
    	if(x<0)putchar('-');
    	while(tmp>0)f[cnt++]=tmp%10+'0',tmp/=10;
    	while(cnt>0)putchar(f[--cnt]);
    	putchar('\n');
    }
}
struct list{//手写双向链表
	int pre[MAXN],nxt[MAXN],tot;
	void insert(int x){nxt[tot]=x,pre[x]=tot,tot=x;}
	void erase(int x)
	{
		if(x!=tot)nxt[pre[x]]=nxt[x],pre[nxt[x]]=pre[x];
		else nxt[pre[x]]=0,tot=pre[x];
		pre[x]=nxt[x]=0;
	}
}ML;
bool cmp(node &x,node &y)//莫堆排序
{
	return ((x.cl!=y.cl)?(x.l<y.l):((x.cl&1)?(x.r<y.r):(x.r>y.r)));
}
int sum[MAXN],cnt[MAXN],a[MAXN],p1[MAXN],p2[MAXN],ans[MAXN];
void get(int mod)//光速幂预处理
{
	p1[0]=p2[0]=1;
	for(int p=1;p<=len+7;p++)
		p1[p]=(p1[p-1]+p1[p-1])%mod;
	for(int p=1;p<=n/len+7;p++)
		p2[p]=p2[p-1]*p1[len]%mod; 
}
int Pow(int k,int mod){return p2[k/len]*p1[k%len]%mod;}//光速幂
void add(int qwq)//莫队插入
{
	sum[cnt[qwq]]-=qwq;
	if(!sum[cnt[qwq]])
		ML.erase(cnt[qwq]);
	cnt[qwq]++;
	if(!sum[cnt[qwq]])
		ML.insert(cnt[qwq]);
	sum[cnt[qwq]]+=qwq;
}
void del(int qwq)//莫队删除
{
	sum[cnt[qwq]]-=qwq;
	if(!sum[cnt[qwq]])
		ML.erase(cnt[qwq]);
	cnt[qwq]--;
	if(!sum[cnt[qwq]])
		ML.insert(cnt[qwq]);
	sum[cnt[qwq]]+=qwq;
}
signed main()
{
	n=read(),m=read(); 
	len=sqrt(n);
	for(int p=1;p<=n;p++)
		a[p]=read();
	for(int p=1;p<=m;p++)
	{
		in[p].l=read(),in[p].r=read(),in[p].k=read();
		in[p].ind=p,in[p].cl=(in[p].l-1)/len+1;
	}
	sort(in+1,in+m+1,cmp);
	int l=1,r=0;
	for(int p=1;p<=m;p++)
	{
		get(in[p].k);
		while(l<in[p].l)del(a[l++]);
		while(l>in[p].l)add(a[--l]);
		while(r<in[p].r)add(a[++r]);
		while(r>in[p].r)del(a[r--]); 
		for(int i=ML.nxt[0];i;i=ML.nxt[i])
			ans[in[p].ind]=(ans[in[p].ind]+((sum[i]*(Pow(in[p].r-in[p].l+1,in[p].k)-Pow(in[p].r-in[p].l+1-i,in[p].k)))%in[p].k+in[p].k)%in[p].k+in[p].k)%in[p].k;//然后是统计贡献，记得取模
	}
	for(int p=1;p<=m;p++)
		write(ans[p]);//输出
}
```
**PS：这份代码不能保证随时随地每时每刻都能 AC 这道题，因为最长的点跑了 3s，很可能评测姬任务一多然后就炸开花了**

---

## 作者：cirnovsky (赞：12)

# 题意简述

不看前面的废话就是题意简述。

# 题解

这是[数据结构一百题](https://www.luogu.com.cn/blog/161849/post-ji-lie-shuo-ju-jie-gou-yi-bai-ti)的第50题（一半了哦）的纪念题解。

无修改操作，基本确定大方向莫队。

考虑查询的问题，我们可以转化一下。即求区间内每个数出现的次数。

一个区间 $[l,r]$ 的子序列数量为：

$$\sum_{i=0}^{r-l+1}C^{i}_{r-l+1}=2^{r-l+1}$$

比如一个数在区间 $[l,r]$ 出现了 $k$ 次，那么一共有 $2^{r-l+1-k}$ 个子序列不包含这个数。这个很好理解，从组合数的意义可知。那么就有 $2^{r-l+1}-2^{r-l+1-k}$ 个子序列包含了这个数。

那么我们就可以用莫队维护**区间中出现了 $k$ 次的所有数的和**，然后乘上一个  $2^{r-l+1}-2^{r-l+1-k}$ 就是它的贡献了。

问题又来了：每次询问的模数是不确定的，我们需要每次都需要 $\Theta(n)$ 处理一遍2的幂。

有没有什么方法能把处理这个东西的复杂度降到 $\Theta(\sqrt{n})$ 或以下呢？

~~对此SyadouHayami表示我们可以打个高精。~~

方法是有的。

我们可以每次询问都处理出 $2^{1},2^{2},\cdots,2^{\sqrt{n}}$ ，以及 $2^{2\sqrt{n}},2^{3\sqrt{n}},\cdots,2^{n}$，都只需要 $\Theta(\sqrt{n})$。当然，都是在模 $p$ 的意义下的。我们分别记为`pow1`和`pow2`。

那么 $2^{x}\operatorname{mod}p=(pow1_{x\operatorname{mod}\sqrt{n}}\times pow2_{\lfloor x\div\sqrt{n}\rfloor})\operatorname{mod}p$。

于是就解决问题了。

我的代码遇到了一下两个玄学问题，贴出来给同样情况的人看看：

1. 链表部分的`prev`和`next`如果放在结构体里会T。

2. `pow1`,`pow2`,`sum`,`cnt`几个数组的定义如果放在最开头和`isa`以及`ans`两个数组一起会RE。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int Maxn = 1e5 + 10;
const int Size = 320;
int n, m, isa[ Maxn ], ans[ Maxn ];
struct Query_Node
{
	int l, r, p, id, pos;
} Q[ Maxn ];
struct Linked_List
{
	int tot, prev[ Maxn ], next[ Maxn ];
	Linked_List( ) { tot = 0; }

	void insert( int x )
	{
		next[ tot ] = x;
		prev[ x ] = tot;
		tot = x;
	}

	void erase( int x )
	{
		if( tot == x )	tot = prev[ x ];
		else
		{
			next[ prev[ x ] ] = next[ x ];
			prev[ next[ x ] ] = prev[ x ];
		}
		prev[ x ] = next[ x ] = 0;
	}
} llt;

bool cmp( Query_Node rhs, Query_Node shr )
{
	if( rhs.pos != shr.pos )	return rhs.l < shr.l;
	else	return rhs.r < shr.r;
}

int pow1[ Maxn ], pow2[ Maxn ];
void Pare_Two( int p )
{
	pow1[ 0 ] = pow2[ 0 ] = 1;
	for( int i = 1; i <= Size; ++ i ) 	pow1[ i ] = 1ll * 2 * pow1[ i - 1 ] % p;
	for( int i = 1; i <= Size; ++ i )	pow2[ i ] = 1ll * pow1[ Size ] * pow2[ i - 1 ] % p;
}

int Get_Two( int x, int p )
{
	return 1ll * pow1[ x % Size ] * pow2[ x / Size ] % p;
}

int sum[ Maxn ], cnt[ Maxn ];
void Make_Cont( int x, int f )
{
	int pos = isa[ x ];
	sum[ cnt[ pos ] ] -= pos;
	if ( ! sum[ cnt[ pos ] ] ) llt.erase( cnt[ pos ] );
	if( f == 1 ) ++cnt[ pos ];
	else --cnt[ pos ];
	if ( ! sum[ cnt[ pos ] ] ) llt.insert( cnt[ pos ] );
	sum[ cnt[ pos ] ] += pos;
}

void Contribute( )
{
	int l = 1, r = 0;
	for( int i = 1; i <= m; ++ i )
	{
		Pare_Two( Q[ i ].p );
		while( l > Q[ i ].l ) Make_Cont( --l, 1 );
		while( l < Q[ i ].l ) Make_Cont( l++, 0 );
		while( r > Q[ i ].r ) Make_Cont( r--, 0 );
		while( r < Q[ i ].r ) Make_Cont( ++r, 1 );
		for( int s = llt.next[ 0 ]; s; s = llt.next[ s ] )
		{
			int val = 1ll * sum[ s ] * ( Get_Two( r - l + 1, Q[ i ].p ) - Get_Two( r - l + 1 - s, Q[ i ].p ) + Q[ i ].p ) % Q[ i ].p;
			ans[ Q[ i ].id ] += val;
			ans[ Q[ i ].id ] %= Q[ i ].p;
		}
	}
}

signed main( )
{
	scanf( "%d %d", &n, &m );
	for( int i = 1; i <= n; ++ i )	scanf( "%d", &isa[ i ] );
	for( int i = 1; i <= m; ++ i )
	{
		int l, r, p;
		scanf( "%d %d %d", &l, &r, &p );
		Q[ i ].l = l, Q[ i ].r = r;
		Q[ i ].p = p, Q[ i ].id = i;
		Q[ i ].pos = l / Size;
	}
	sort( Q + 1, Q + 1 + m, cmp );
	Contribute( );
	for( int i = 1; i <= m; ++ i )
		printf( "%d\n", ans[ i ] );
	return 0;
}
```

---

## 作者：BFqwq (赞：8)

## [Ynoi2015]盼君勿忘

这是 Ynoi 中一道相对偏水的题目，非常简单的莫队。

首先很容易想到，对于一个长度为 $a$ 的序列，如果某个元素出现了 $b$ 次，

我们那么共有 $2^{a-b}$ 个子序列是不包含这一元素的，

而其他的子序列都包含这一元素。

换言之，这个元素的贡献次数是 $2^a-2^{a-b}$。

我们可以用一个链表来记录一下**区间贡献内出现次数相同的数的和**。

显然，这个链表内的元素个数最多是根号级别的。

对于 $2$ 的若干次幂，我们可以预处理出 $2^1,2^2\ldots 2^{\sqrt n}$ 与 $2^{2\times \sqrt n},2^{3\times \sqrt n} \ldots 2^n$。

然后我们就可以 $\operatorname{O}(1)$ 将其求出。

莫队的复杂度是 $\operatorname{O}(n\sqrt n)$，询问的复杂度为 $\operatorname{O}(m\sqrt n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(register int x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=100005;
const int blk=317; 
int n,m;
int a[maxn],cnt[maxn],bl[maxn];
int sum[maxn];
int res[maxn];
struct node{
    int l,r,id,p;
}q[maxn];
inline bool cmp(register node a,register node b){
	return bl[a.l]^bl[b.l]?a.l<b.l:bl[a.l]&1?a.r<b.r:a.r>b.r;
}
struct lian{
	int nxt,pre;
}e[maxn];int tl;
inline void _ins(register int x){
	e[tl].nxt=x;
	e[x].pre=tl;
	tl=x;
}
inline void _del(register int x){
	if(x^tl){
		e[e[x].pre].nxt=e[x].nxt;
		e[e[x].nxt].pre=e[x].pre;
	}
	else{
		tl=e[x].pre;
	}
	e[x].nxt=e[x].pre=0;
}
inline void add(register int x){
    if(cnt[x]){
        sum[cnt[x]]-=x;
        if(!sum[cnt[x]]){
        	_del(cnt[x]);
		}
    }
    cnt[x]++;
    if(!sum[cnt[x]]){
    	_ins(cnt[x]);
	}
    sum[cnt[x]]+=x;
}
inline void del(register int x){
    sum[cnt[x]]-=x;
    if(!sum[cnt[x]]){
    	_del(cnt[x]);
	}
    cnt[x]--;
    if(cnt[x]){
        if(!sum[cnt[x]]){
        	_ins(cnt[x]);
		}
        sum[cnt[x]]+=x;
    }
}
int p1[2233],p2[2233],p;
inline int pw(register int x){
    return (ll)p1[x%blk]*p2[x/blk]%p;
}
signed main() {
    n=read();m=read();
    int g=0,f=1;
    for(register int i=1;i<=n;i++){
    	a[i]=read();
		bl[i]=f;
		g++;if(g==blk){
    		f++;g=0;
		}
	}
    for(register int i=1;i<=m;i++){
    	q[i].l=read();q[i].r=read();q[i].p=read();q[i].id=i;
	}
    sort(q+1,q+m+1,cmp);
    for(register int i=1,l=1,r=0;i<=m;i++){
        while(r<q[i].r){
        	add(a[++r]);
		}
        while(l>q[i].l){
        	add(a[--l]);
		}
        while(r>q[i].r){
        	del(a[r--]);
		}
        while(l<q[i].l){
        	del(a[l++]);
		}
        p1[0]=p2[0]=1;
		p=q[i].p;
        for(register int j=1;j<=blk;j++){
        	p1[j]=(ll)p1[j-1]*2%p;
		}
        p2[1]=p1[blk];
        for(register int j=2;j<=blk;j++){
        	p2[j]=(ll)p2[j-1]*p2[1]%p;
		}
		register int o=q[i].id;
    	for(int j=e[0].nxt;j;j=e[j].nxt){
        	res[o]+=(ll)sum[j]*(pw(q[i].r-q[i].l+1)-pw(q[i].r-q[i].l+1-j))%p;
        	res[o]=(res[o]%p+p)%p;
    	}
    }
    for(register int i=1;i<=n;i++){
    	print(res[i]);
	}
}
```


---

## 作者：FourteenObsidian (赞：6)

考虑使用莫队。

考虑一个数 $x$ 在当前区间出现了 $y$ 次，假设区间长度为 $len$， 那么选取方案中包含它的方案数为 $2^{len-y}\times(2^y-1)$。（选不包含 $x$ 的方案数为 $2^{len-y}$，在 $y$ 个 $x$ 中选的方案数为 $2^y$， 但要减掉一个都不选的情况） 此时的贡献显然是 $x\times2^{len-y}\times(2^y-1)$。

用莫队统计当前区间出现次数为 $y$ 的数的总和，发现不同的 $y$ 值最多只有 $\sqrt n$ 个。我们可以用一个链表来记录这个值。

然后我们发现用快速幂复杂度较大，但底数始终为 $2$，所以可以用光速幂，对于每一个询问，先处理出 $2^1,2^2,\ldots,2^{\sqrt n}$ 和 $2^{\sqrt n},2^{2\sqrt n},\ldots,2^n$ 模 $p$ 意义下的值。对于一个幂次，拆成两个幂之积即可。

当然，还要卡常。计算每个值的贡献的式子可以化为 $x\times(2^{len}-2^{len-y})$，还有，取模很慢，必要时可以将它写成减去 $p$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10, sqN = 320;
int n, m, k, siz, answ, head, last;
int a[N], ans[N], mp[N], s1[sqN], s2[sqN], ton[N], num[N];
int mod;
struct Query
{
    int id, l, r, blo, mod;
}q[N];
struct List
{
	int from, nxt;
}lst[N];
inline int read()
{
    int x = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}
inline void write(int x)
{
	if(!x)
	{
		puts("0");
		return;
	}
	int top = 0, st[30];
	while(x)
	{
		st[++top] = x % 10;
		x /= 10;
	}
	while(top) putchar(st[top--] + '0');
	puts("");
	return;
}
bool cmp(Query a, Query b)
{
    return a.blo == b.blo ? ((a.blo & 1) ? a.r < b.r : a.r > b.r) : a.blo < b.blo;
}
inline void pre(int len)//光速幂预处理
{
    s1[0] = s2[0] = 1;
    k = sqrt(len);
    for(register int i = 1; i <= k; ++i)
	{
        s1[i] = (s1[i - 1] << 1ll);
		if(s1[i] >= mod) s1[i] -= mod;
	}
    for(register int i = 1; i <= len / k; ++i)
	{
		int s = (s2[i - 1] * s1[k]);
		if(s >= mod) s2[i] = s - (s / mod * mod);
		else s2[i] = s;
	}
    return;
}
inline void ins(int pos)//链表插入
{
	lst[pos].from = 0;
	lst[pos].nxt = head;
	lst[head].from = pos;
	head = pos;
	return;
}
inline void del(int pos)//链表删除
{
	if(head == pos) head = lst[pos].nxt;
	else
	{
		lst[lst[pos].from].nxt = lst[pos].nxt;
		lst[lst[pos].nxt].from = lst[pos].from;
	}
	return;
}
inline void move(int pos, int opt)//莫队移动
{
	if(mp[a[pos]])
	{
		ton[mp[a[pos]]] -= a[pos];
		if(!ton[mp[a[pos]]]) del(mp[a[pos]]);
	}
	mp[a[pos]] += opt;
	if(mp[a[pos]])
	{
		if(!ton[mp[a[pos]]]) ins(mp[a[pos]]);
		ton[mp[a[pos]]] += a[pos];
	}
}
inline int qpow(int x)//拆成两个幂次之积
{
	int s = s2[x / k] * s1[x % k];
	if(s < mod) return s;
	return s - (s / mod * mod);
}
signed main()
{
	n = read(), m = read();
    siz = sqrt(n);
    for(register int i = 1; i <= n; ++i)
        a[i] = read();
    for(register int i = 1; i <= m; ++i)
    {
		q[i].l = read(), q[i].r = read(), q[i].mod = read();
		q[i].id = i;
        q[i].blo = (q[i].l - 1) / siz + 1;
    }
    sort(q + 1, q + m + 1, cmp);
    int l = 1, r = 0;
    for(register int i = 1; i <= m; ++i)
    {
        answ = 0;
        int L = q[i].l, R = q[i].r, len = R - L + 1; mod = q[i].mod;
        pre(len);
        while(l > L) move(l - 1, 1), --l;
        while(r < R) move(r + 1, 1), ++r;
        while(l < L) move(l, -1), ++l;
        while(r > R) move(r, -1), --r;
		register int s = qpow(len);
		for(register int poi = head; poi; poi = lst[poi].nxt)
		{
			answ += (((ton[poi] % mod) * ((s % mod - qpow(len - poi) % mod + mod) % mod)) % mod);
			if(answ >= mod) answ -= mod;
		}
		ans[q[i].id] = answ;
    }
    for(register int i = 1; i <= m; ++i)
        write(ans[i]);
    return 0;
}
```


---

## 作者：ustze (赞：6)

这题有毒....反正我的写法常数巨大  
记$[l,r]$中出现次数为k的数的和为$s[k]$  
则答案显然为 $\sum{s[k]*(2^{r-l+1}-2^{r-l+1-k})}$  
因为值不为0的s[k]最多有$sqrt(n)$个，直接用hash表统计，莫队即可  
我的做法由于常数原因，得分在60~100左右  
代码：
```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define reg register
const int N=1e5+5;
typedef long long ll;
inline int read(){
    reg int s=0,f=1;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) s=s*10+ch-'0',ch=getchar();
    return s*f;
}
const int block=317;
int n,m;
int a[N],cnt[N],bel[N];
unordered_set<int> s2;
int s[N],ans[N];
struct ask{
    int l,r,id,mod;
}q[N];
inline int cmp(const ask & a,const ask & b){
    return bel[a.l]^bel[b.l] ? bel[a.l]<bel[b.l] : bel[a.l]&1 ? a.r<b.r : a.r>b.r;
}
inline void add(int x){
    if(cnt[x]) {
        s[cnt[x]]-=x;
        if(!s[cnt[x]]) s2.erase(cnt[x]);
    }
    cnt[x]++;
    if(!s[cnt[x]]) s2.insert(cnt[x]);
    s[cnt[x]]+=x;
}
inline void del(int x){
    s[cnt[x]]-=x;
    if(!s[cnt[x]]) s2.erase(cnt[x]);
    cnt[x]--;
    if(cnt[x]){
        if(!s[cnt[x]]) s2.insert(cnt[x]);
        s[cnt[x]]+=x;
    }
}
int pw1[N],pw2[N];
inline ll qpow(int x,int mod){
    return 1ll*pw1[x%block]*pw2[x/block]%mod;
}
inline int calc(int x){
    reg int ans=0;
    for(auto it:s2){
        ans=(ans+s[it]*(qpow(q[x].r-q[x].l+1,q[x].mod)-qpow(q[x].r-q[x].l+1-it,q[x].mod)+q[x].mod)%q[x].mod)%q[x].mod;
    }
    return ans;
}
int main(){
    n=read(),m=read();
    for(reg int i=1;i<=n;i++) a[i]=read();
    for(reg int i=1;i<=n;i++) bel[i]=(i-1)/block+1;
    for(reg int i=1;i<=m;i++) q[i].l=read(),q[i].r=read(),q[i].mod=read(),q[i].id=i;
    sort(q+1,q+m+1,cmp);
    reg int l=1,r=0;
    for(reg int i=1;i<=m;i++){
        for(;r<q[i].r;r++) add(a[r+1]);
        for(;r>q[i].r;r--) del(a[r]);
        for(;l<q[i].l;l++) del(a[l]);
        for(;l>q[i].l;l--) add(a[l-1]);
        pw1[0]=pw2[0]=1;
        for(reg int j=1;j<=block;j++) pw1[j]=1ll*pw1[j-1]*2%q[i].mod;
        pw2[1]=pw1[block];
        for(reg int j=2;j<=block;j++) pw2[j]=1ll*pw2[j-1]*pw2[1]%q[i].mod;
        ans[q[i].id]=calc(i);
    }
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
} 

```

---

## 作者：Stinger (赞：3)

# $\texttt{Description}$

> 只要不看珂普部分就是最简洁明了的desciption。

# $\texttt{Solution}$

这题大概是YnMO，不卡常不毒瘤代码短（（（

对于每个子序列分别求和已经无法优化。考虑一个在长度为 $l$，出现了 $x$ 次的数，它会队序列产生 $2^l-2^x$ 次贡献。式子的含义就是所有情况减去不包含这个数的情况。

然后观察题面，$10^5$ 的数据范围还不带修，大概率是莫队。

考虑用双向链表维护这些数，每个节点表示出现了该节点对应次数的数的总和。具体的，代码中声明一个`Node`类型的数组e，`e[x].s` 表示出现了 $x$ 次的数的和。

然后就可以正常莫队了。

啊不对，快速冥是 $O(logn)$ 的，怎么办？

$O(n\sqrt{n}logn)$ 跑 $10^5$ ，以快速冥的常数好像可以rush一波，但是算上双向链表的常数……还是老老实实优化吧（

这题可以耗费较多的时间队对每个模数的 $2$ 的 $x$ 次冥进行预处理，但是又不足以处理所有冥。再考虑快速冥，基于这样一个式子：$2^x=2^{x/2}\times 2^{x/2}$。这个时候两边的数只缩小了一倍。我们可不可以想传说中的vEB树那样以根号为跨度呢？式子变为 $2^x=2^{x/sqrt{x}}\times 2^{x\% sqrt{x}}$。**那么，预处理根号 $n$ 以内的冥，就可以 $O(1)$ 计算冥了！**


**还有一个非常玄学的地方：**

莫队更新的时候，`add,del` 的顺序至关重要，~~不然你会向我一样WA+TLE+RE~~

![](https://cdn.luogu.com.cn/upload/image_hosting/jcaiimnd.png)

时间复杂度 $O(n\sqrt{n})$（$n$ 与 $m$ 同阶）。

# $\texttt{Code}$

```cpp
#include <cstdio> 
#include <cmath>
#include <algorithm>

int a[100005], ans[100005], cnt[100005], p1[100005], p2[100005], S;
struct Node {
	int pre, nxt, s;
} e[100005];
struct Question {
	int l, r, p, id;
	inline bool operator < (const Question a) const {
		bool t((l - 1) / S + 1 == (a.l - 1) / S + 1);
		return t ? (r - 1) / S + 1 < (a.r - 1) / S + 1 : (l - 1) / S + 1 < (a.l - 1) / S + 1;
	}
} q[100005];

inline void insert1(const int x, const int s) {
	int n(e[x].nxt);
	e[n].pre = x + 1, e[x].nxt = x + 1, e[x + 1].s = s;
	e[x + 1].pre = x, e[x + 1].nxt = n;
}
inline void insert2(const int x, const int s) {
	int p(e[x].pre);
	e[p].nxt = x - 1, e[x].pre = x - 1, e[x - 1].s = s;
	e[x - 1].pre = p, e[x - 1].nxt = x;
}
inline void remove(const int x) {
	e[e[x].pre].nxt = e[x].nxt, e[e[x].nxt].pre = e[x].pre, e[x].nxt = e[x].pre = 0;
}
inline void add(const int x) {
	int c(cnt[x]);
	e[c].s -= x;
	if (e[c].nxt != c + 1) insert1(c, x);
	else e[c + 1].s += x; 
	if (!e[c].s) remove(c);
	++ cnt[x];
}
inline void del(const int x) {
	int c(cnt[x]);
	e[c].s -= x;
	if (e[c].pre != c - 1 && c > 1) insert2(c, x);
	else e[c - 1].s += x;
	if (!e[c].s) remove(c);
	-- cnt[x];
}
inline int qpow(const int x, const int p) {return 1LL * p2[x / S] * p1[x % S] % p;}

int main() {
	int n, m, l(1), r(0);
	scanf("%d%d", &n, &m);
	S = sqrt(n);
	for (int i(1); i <= n; ++ i) scanf("%d", a + i);
	for (int i(1); i <= m; ++ i) scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].p), q[i].id = i;
	std::sort(q + 1, q + m + 1);
	for (int i(1); i <= m; ++ i) {
		while (l > q[i].l) add(a[-- l]);
		while (r < q[i].r) add(a[++ r]);
		while (r > q[i].r) del(a[r --]);
		while (l < q[i].l) del(a[l ++]);
		p1[0] = p2[0] = 1;
		for (int j(1); j <= S; ++ j) p1[j] = 2LL * p1[j - 1] % q[i].p;
		for (int j(1); j <= S; ++ j) p2[j] = 1LL * p2[j - 1] * p1[S] % q[i].p;
		for (int j(e[0].nxt); j; j = e[j].nxt)
			ans[q[i].id] = (1LL * ans[q[i].id] + 1LL * e[j].s * (qpow(q[i].r - q[i].l + 1, q[i].p) - qpow(q[i].r - q[i].l + 1 - j, q[i].p)) % q[i].p) % q[i].p;
		ans[q[i].id] = (ans[q[i].id] + q[i].p) % q[i].p;
	}
	for (int i(1); i <= m; ++ i) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：devout (赞：2)

> 在太阳西斜的这个世界里，置身天上之森。
> 等这场战争结束后，不归之人与望眼欲穿的人们，人人本着正义之名。
> 长存不灭的过去，逐渐消逝的未来。
> 我回来了，纵使日薄西山，即便看不到未来，
> 此时此刻的光辉，**盼君勿忘**。
> ——世上最幸福的女孩


珂朵莉，要幸福哦。

****

主页AC 1k祭（

考虑一个数在区间里面会被算上多少次贡献

我们可以用全部区间减去包含这个数的区间，假设这个数在这段区间里出现了 $k$ 次，那么贡献就是

$2^{r-l+1}-2^{r-l+1-k}$

考虑一个~~经典~~的思想，对于 $\sqrt n$ 分类讨论

对于所有 $\leq \sqrt n$ 的数，我们可以记录出现了 $i$ 次的所有数的和，然后一起计算贡献

对于所有 $> \sqrt n$ 的数，这样的数不超过 $\sqrt n$ 个，所以我们可以把他们弄到一个链表里面暴力求。

在外面套一个莫队，就可以 $\mathcal O(n\sqrt n)$ 搞定了

但是注意有一个问题，就是每次的模数不一样，所以我们每次需要跑快速幂，会多出来一个 log，所以我们应该用光速幂来搞，这样可以保证复杂度不会炸

代码还是很好写的，注意不要炸 int，其他地方就没什么坑了（

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,m,sq;
int a[N],tim[N];
ll sum[N];
int pow1[N],pow2[N];
int head,tail,pre[N],nxt[N];
int out[N];
int pos[N];

struct texas{
	int id,l,r,p;	
}q[N];

bool cmp(texas x,texas y){
	if(pos[x.l]!=pos[y.l])return pos[x.l]<pos[y.l];
	if(pos[x.l]&1)return x.r<y.r;
	else return x.r>y.r;	
}

void init(int p){
	pow1[0]=1%p;
	Rep(i,1,sq)pow1[i]=1ll*pow1[i-1]*2%p;
	pow2[0]=pow1[0];
	Rep(i,1,sq)pow2[i]=1ll*pow2[i-1]*pow1[sq]%p;	
}

int getpow(int k,int p){
	if(k<=0)return 1;
	return 1ll*pow1[k%sq]*pow2[k/sq]%p;	
}

void insert(int x){
	nxt[x]=tail;
	pre[x]=pre[tail];
	nxt[pre[tail]]=x;
	pre[tail]=x;	
}

void dereto(int x){
	nxt[pre[x]]=nxt[x];
	pre[nxt[x]]=pre[x];
	nxt[x]=pre[x]=0;	
}

void add(int x){
	sum[tim[x]]-=x;
	tim[x]++;
	sum[tim[x]]+=x;
	if(tim[x]==sq+1)insert(x);
}

void del(int x){
	sum[tim[x]]-=x;
	tim[x]--;
	sum[tim[x]]+=x;
	if(tim[x]==sq)dereto(x);	
}

int main()
{
	read(n),read(m);
	Rep(i,1,n)read(a[i]);
	sq=sqrt(n)+1;
	Rep(i,1,n)pos[i]=(i-1)/sq+1;
	Rep(i,1,m)q[i].id=i,read(q[i].l),read(q[i].r),read(q[i].p);
	sort(q+1,q+m+1,cmp);
	head=n+1,tail=n+2;
	nxt[head]=tail;
	pre[tail]=head;
	Rep(i,1,n)sum[0]+=a[i];
	for(int i=1,l=1,r=0;i<=m;i++){
		while(l>q[i].l)add(a[--l]);
		while(r<q[i].r)add(a[++r]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);	
		init(q[i].p);
		int tot=getpow(q[i].r-q[i].l+1,q[i].p);
		Rep(j,1,sq){
			out[q[i].id]+=1ll*sum[j]%q[i].p*(tot-getpow(q[i].r-q[i].l+1-j,q[i].p)+q[i].p)%q[i].p;
			out[q[i].id]%=q[i].p;	
		}
		for(int it=nxt[head];it!=tail;it=nxt[it]){
			out[q[i].id]+=1ll*it*(tot-getpow(q[i].r-q[i].l+1-tim[it],q[i].p)+q[i].p)%q[i].p;
			out[q[i].id]%=q[i].p;	
		}
	}
	Rep(i,1,m)printf("%d\n",out[i]);
	return 0;
}
```


---

## 作者：Demoe (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/P5072)

~~第一道 Ynoi 纪念一下qwq~~

## 题意

- 给定一个序列，每次求一个区间 $[l,r]$ 中所有子序列分别去重后的和 $\bmod p$。

---

## Sol

观察题意，可以发现：

1. 可离线。

2. 每次模数不同。

3. 十有八九爆 $\text{int}$。

对于第 $1$ 点，容易想到用**莫队**解决问题。

那么时间复杂度已经到 $O(n \sqrt n)$ 了。（

---

我们考虑每一位对答案的贡献。

对于区间 $[l,r]$，考虑 $a_i$ 的贡献 。（$l \le i \le r$）

设 $a_i$ 在区间 $[l,r]$ 中出现 $cnt_{a_i}$ 次。

我们知道，一个元素总数为 $k$ 的集合的子集个数为 $2^k$ 个。

可由 $\sum\limits^k_{i=1}\dbinom{k}{i}=2^k$ 得出结论。

那么我们接下来算单个元素贡献有两种推导方法。

### Sol 1

我们直接从选入手。

那么可得贡献即为选的乘上不选的状态数。

即 $(2^{cnt_{a_i}}-1)\times 2^{r-l+1-cnt_{a_i}}$。

其中 $(2^{cnt_{a_i}}-1)$ 表示选的非空子集。

可化为 $2^{r-l+1}-2^{r-l+1-cnt_{a_i}}$。

### Sol 2

我们转换一下思路，一个子序列只有包含和不包含两种情况。

那么我们可以想到用总数减去不包含的状态数。

即直接可得 $2^{r-l+1}-2^{r-l+1-cnt_{a_i}}$。

---

我们考虑在莫队时保存出现次数相同元素的和。

需要快速插入，删除。

由于不需要保证有序，容易想到**双向链表**。（建议手写）

$O(1)$ 时间完成插入删除操作。

---

我们考虑模数不同，如何迅速求出 $2^k \bmod p$

我们考虑关于 $\sqrt n$ 分组。

$2^k=2^{\left\lfloor\frac{k}{\sqrt n}\right\rfloor \times \sqrt n+k \bmod \sqrt n}=2^{\left\lfloor\frac{k}{\sqrt n}\right\rfloor \times \sqrt n} \times 2^{k \bmod \sqrt n}$

那么我们可以预处理出 $2^1$，$2^2$，$2^3$...$2^{\sqrt n}$，$2^{2\sqrt n}$，$2^{3\sqrt n}$...$2^n$ 取模后的值。

并用上面的公式计算。

---

那么，似乎问题解决完了？qaq

为了卡常，我们全写 $\text{int}$，想着还有取模呢。qaq

交一发样例，过了。交一发，WAWAWA，抱灵了。（（（

这时候你需要在一些可能爆炸的地方强制类型转换成 $\text{long long}$。qwq

这样才可能不 WA。（

~~不要问我怎么知道 我调这个调了 $6$ 天才发现。~~

那么交一发 A 了qwq。

~~为啥加了火车头比不加慢啊qaq~~

给个刚好能过的代码主要在#9被卡。（

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
#define re register int
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,m,a[N],len,ans[N],cnt[N],sum[N],l=1,r=0,pw1[N],pw2[N];
struct Question{int l,r,p,id,pos;}q[N];
struct LINKED_LIST{
	struct Link{int pre,nxt;}lk[N];int cnt;
	LINKED_LIST(){cnt=0;}
	inline void Insert(int x){
		lk[cnt].nxt=x;
		lk[x].pre=cnt;
		cnt=x;
	}
	inline void Erase(int x){
		if(x^cnt){
			lk[lk[x].pre].nxt=lk[x].nxt;
			lk[lk[x].nxt].pre=lk[x].pre;
		}
		else cnt=lk[x].pre;
		lk[x].pre=lk[x].nxt=0;
	}
}qaq;
template <typename T> inline void rd(T &x){
	re fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(int x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
bool cmp(Question x,Question y){
	if(x.pos!=y.pos) return x.pos<y.pos;
	if(x.pos&1) return x.r<y.r;
	return x.r>y.r;
}
inline void init_pow(int p){
	pw1[0]=pw2[0]=1;
	for(re i=1;i<=len;i++) pw1[i]=((ll)1ll*pw1[i-1]*2)%p;
	for(re i=1;i<=len;i++) pw2[i]=((ll)1ll*pw2[i-1]*pw1[len])%p;
}
inline int get_pow(int x,int p){return ((ll)pw1[x%len]*pw2[x/len])%p;}
inline void upd(int x,int op){
	sum[cnt[a[x]]]-=a[x];
	if(!sum[cnt[a[x]]]) qaq.Erase(cnt[a[x]]);
	cnt[a[x]]+=op;
	if(!sum[cnt[a[x]]]) qaq.Insert(cnt[a[x]]);
	sum[cnt[a[x]]]+=a[x];
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(m);
	len=(int)sqrt(n);
	for(re i=1;i<=n;i++) rd(a[i]);
	for(re i=1;i<=m;i++) rd(q[i].l),rd(q[i].r),rd(q[i].p),q[i].id=i,q[i].pos=(q[i].l-1)/len+1;
	sort(q+1,q+m+1,cmp);
	for(re i=1;i<=m;i++){
		init_pow(q[i].p);
		while(l>q[i].l) --l,upd(l,1);
		while(r<q[i].r) ++r,upd(r,1);
		while(l<q[i].l) upd(l,-1),l++;
		while(r>q[i].r) upd(r,-1),r--;
		for(re j=qaq.lk[0].nxt;j;j=qaq.lk[j].nxt)
			ans[q[i].id]=((ans[q[i].id]+(ll)1ll*sum[j]*(get_pow(r-l+1,q[i].p)-get_pow(r-l+1-j,q[i].p))+q[i].p)%q[i].p+q[i].p)%q[i].p;
	}
	for(re i=1;i<=m;i++) wr(ans[i]),puts("");
	return 0;
}
```

---

## 作者：critnos (赞：2)

卡到了最优解QAQ：<https://www.luogu.com.cn/record/36863427>

此题应该通过计算贡献的方式求出答案。

对于一个数 $x$，如果他在区间 $[l,r]$ 中出现了 $k$ 次，则他对答案的贡献是 $x\times (2^{r-l+1}-2^{r-l+1-k})$。

可以合并所有出现次数为 $k$ 次的数，他们的贡献是 $s_k\times (2^{r-l+1}-2^{r-l+1-k})$，$s_k$ 表示所有出现次数为 $k$ 次的数的和。

先看 $s_k$ 怎么计算。

显然用莫队统计。然后遇到了一个问题就是怎么取出所有有意义的 $k$。可以使用一个支持插入，删除，遍历的数据结构，如哈希表或链表。莫队转移时动态的维护所有有意义的 $k$ 值。

再看后半部分：$2^{r-l+1}-2^{r-l+1-k}$。

这个重点在于求 $2^n \mod p$。可以使用光速幂，$O(\sqrt n)$ 预处理 $O(1)$ 求 $2^n \mod p$。

所以我们平衡了复杂度，总时间复杂度 $n\sqrt n$。

讲讲卡常方法：

* 最简单的优化：预编译指令，`fread`，`fwrite`（不过实测用处不大）

* 用手写链表，别用 `umap`

* 莫队奇偶排序

* 最重要的：取模优化。

众所周知取模的速度很慢，而此题无论是莫队求解还是光速幂预处理都要大量的取模。所以，我们考虑使用取模优化。具体见这里：<https://www.luogu.com.cn/problem/P6750>

以光速幂预处理为例：

```cpp
void init(int len)
{
	int i;
	bl=sqrt(len);
	ksm2[0]=ksm1[0]=1;
	for(i=1;i<=bl+5;i++)
		ksm1[i]=F.reduce(1ll*ksm1[i-1]*2);
	for(i=1;i<=bl+5;i++)
		ksm2[i]=F.reduce(1ll*ksm1[bl]*ksm2[i-1]);
}
```


最后，祝珂朵莉永远幸福鸭！

---

## 作者：FutaRimeWoawaSete (赞：1)

应该是 Ynoi 里面比较简单的一道。       

```Welcome home, Chtholly```        

首先需要注意一下这道题的意思，不是得所有的子序列去重，而是对子序列里面的元素进行去重然后求总和……在这里读错题浪费了 1h 。             

接着这道题就很简单了，很明显如果我们的子序列里面有一个元素 x 那么这个 x 会且只会对这个子序列产生一次它自己本身的贡献。            

有了这个条件我们就很好直接提出每个 x ，令 t 为它在查询区间里出现的次数，然后令区间长为 len ，x 的贡献就是 $x \times (2 ^ {len} - 2 ^ {len - t})$ ，$2 ^ {len}$ 是总的子序列个数，而 $2 ^ {len - t}$ 就是不包含 x 的子序列，简单排列组合。           

然后我们很明显又可以很 trick 的把出现次数提出来，因为我们发现我们这个式子在区间确定的情况下仅有两个变量，所以我们记 ```sum[x]``` 表示在这个区间里出现次数为 x 的元素之和，那么答案即可表示为 $\sum sum[x] \times (2 ^ {len} - 2 ^ {len - t})$ 。         

我们为何要把出现次数给提出来当变量？因为我们此时发现所有 ```sum[x]``` 中只有 ```sum[x]``` 不会 $0$ 才会造成贡献，而 ```sum[x]``` 不为 $0$ 的 x 个数最劣情况下即出现次数为 $1 , 2 , 3 , 4 ……$ 的情况全都出现过，最劣个数为 $\sqrt n$ ，所以我们只要记录一下所有的非零 x 然后就可以在 $O(\sqrt n)$ 的时间复杂度里面找出来，这里我写的是链表维护。                

之后我们要争取做到 $O(n \sqrt n)$ ，我们发现我们的求幂就只有求 $2$ 的幂并且指数大小严格控制在 $100000$ 以内，我们套一个光速幂解决即可。        

~~不会光速幂的同学可以参考一下其他题解毕竟这不是这道题的重点~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define int long long
const int Len = 1e5 + 5 , SIZE = 325;
long long n,m,p,a[Len],cnt,Point[Len],sum[Len],Cnt[Len];
long long qpow[SIZE],sqrtqpow[SIZE],Print[Len],head;
struct node
{
	int lst,to;
	node(int xx = 0,int yy = 0){lst = xx , to = yy;}
}edge[Len];
inline void add(int x)
{
	edge[x].lst = 0 , edge[head].lst = x;
	edge[x].to = head;
	head = x;
}
inline void del(int x)
{
	if(x == head)
	{
		int next = edge[head].to;
		edge[x].to = edge[x].lst = 0;
		edge[next].lst = 0;
		head = next;
	}
	else 
	{
		int next = edge[x].to , last = edge[x].lst;
		edge[last].to = next;
		edge[next].lst = last;
		edge[x].lst = edge[x].to = 0;
	}
}
struct Node
{
	int l,r,idx;
	int Mod;
}Sec[Len];
int block[Len],t;
bool cmp(Node x , Node y)
{
	if(block[x.l] ^ block[y.l]) return block[x.l] < block[y.l];
	return x.r < y.r;
}
void Add(int x)
{
	if(Cnt[a[x]]) sum[Cnt[a[x]]] -= a[x];
	if(!sum[Cnt[a[x]]] && Cnt[a[x]]) del(Cnt[a[x]]);
	Cnt[a[x]] ++;
	if(Cnt[a[x]]) sum[Cnt[a[x]]] += a[x];
	if(sum[Cnt[a[x]]] == a[x] && Cnt[a[x]]) add(Cnt[a[x]]);
}
void Sub(int x)
{
	if(Cnt[a[x]]) sum[Cnt[a[x]]] -= a[x];
	if(!sum[Cnt[a[x]]] && Cnt[a[x]]) del(Cnt[a[x]]);
	Cnt[a[x]] --;
	if(Cnt[a[x]]) sum[Cnt[a[x]]] += a[x];
	if(sum[Cnt[a[x]]] == a[x] && Cnt[a[x]]) add(Cnt[a[x]]);
}
signed main()
{
	scanf("%lld %lld",&n,&m);
	t = sqrt(n);
	for(int i = 1 ; i <= n ; i ++) block[i] = (i - 1) / t + 1;
	for(int i = 1 ; i <= n ; i ++) scanf("%lld",&a[i]);
	for(int i = 1 ; i <= m ; i ++) 
	{
		scanf("%lld %lld %lld",&Sec[i].l,&Sec[i].r,&Sec[i].Mod);
		Sec[i].idx = i;
	}
	sort(Sec + 1 , Sec + 1 + m , cmp);
	int l = 1 , r = 0;
	for(int i = 1 ; i <= m ; i ++)
	{
		while(l > Sec[i].l) Add(-- l);
		while(r < Sec[i].r) Add(++ r);
		while(l < Sec[i].l) Sub(l ++);
		while(r > Sec[i].r) Sub(r --);
		int len = r - l + 1 , T = sqrt(len);
		T ++;
		qpow[0] = 1;
		for(int j = 1 ; j <= T ; j ++) qpow[j] = qpow[j - 1] * 2LL % Sec[i].Mod;
		sqrtqpow[0] = 1;
		for(int j = 1 ; j <= T ; j ++) sqrtqpow[j] = sqrtqpow[j - 1] * qpow[T] % Sec[i].Mod;
		for(int e = head ; e ; e = edge[e].to)
			Print[Sec[i].idx] += sum[e] * (sqrtqpow[len / T] * qpow[len % T] % Sec[i].Mod - sqrtqpow[(len - e) / T] * qpow[(len - e) % T] % Sec[i].Mod + Sec[i].Mod) % Sec[i].Mod , Print[Sec[i].idx] %= Sec[i].Mod;
	}
	for(int i = 1 ; i <= m ; i ++) printf("%lld\n",Print[i]);
	return 0;
}
```

---

## 作者：AsunderSquall (赞：1)

这是我做的第一道Ynoi~  

## 题面

> 珂朵莉给了你一个序列，每次查询一个区间 $[l,r]$ 中所有子序列分别去重后的和  $mod\ p$

## 题解  


看上去这个“去重” “序列”非常不好处理，我们考虑转换成贡献  
如果数$x$在区间$[l,r]$中出现了$k$次  
那么不含$x$的数有$r-l+1-k$个，产生的子序列有$2^{r-l+1-k}$个  
所以$x$的贡献为$x \cdot (2^{r-l+1}-2^{r-l+1-k})$  
然后考虑怎么维护一个区间每个数出现的次数。  


我们把询问离线下来然后莫队。  
用一个数据结构存储出现次数相同的数的和  
这里我用了`unordered_set`用来储存  

加入一个数的时候，先找到这个数出现的次数$cnt$，然后将出现$cnt$次的数之和减去这个数。  
然后把这个数加入出现次数$cnt+1$的地方  
删除的时候类似，把这个数加入出现次数$cnt-1$的地方即可。  
值域只有$1e5$，找$cnt$可以直接开桶储存，不需要离散化。

```cpp
I void add(int x) 
{
    if (cnt[a[x]]) 
    { 
        sum[cnt[a[x]]]-=a[x];
        if (!sum[cnt[a[x]]]) sum2.erase(cnt[a[x]]);
    }
    cnt[a[x]]++;
    if (!sum[cnt[a[x]]]) sum2.insert(cnt[a[x]]);
    sum[cnt[a[x]]]+=a[x];
}
I void del(int x) 
{
	sum[cnt[a[x]]]-=a[x];
	if (!sum[cnt[a[x]]]) sum2.erase(cnt[a[x]]);
	cnt[a[x]]--;
	if (!cnt[a[x]])  return;
    	else 
    	{
		if (!sum[cnt[a[x]]]) sum2.insert(cnt[a[x]]);
		sum[cnt[a[x]]]+=a[x];
	}
}
```
~~不知道为什么代码会变成这个样子，本地挺正常的，或许是tab的问题~~  
这里`sum[i]`表示出现$i$次的数之和，`sum2`是一个`unordered_set`，用来存储所有出现过的次数。  
由于在长度为$L$的区间中不同种类的出现次数为$\sqrt n$以内，所以这样可以在时间内求出所有出现次数以及`sum`。  

然后我们再用快速幂算出答案。
然而这样是$O(m\sqrt n \log n)$的，会T掉。  
那么我们不用快速幂，用光速幂，就能快速得出答案了。  
```cpp
I void Init(int Mod) 
{
    pow1[0]=pow2[0]=1;
    for (R int i=1;i<=SIZE;i++) pow1[i]=1LL*pow1[i-1]*2%Mod;
    pow2[1]=pow1[SIZE];
    for (R int i=2;i<=SIZE;i++) pow2[i]=1LL*pow2[i-1]*pow2[1]%Mod;
}
I int gsm(int x,int Mod) {return pow1[x%SIZE]*pow2[x/SIZE]%Mod;}
```

完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read() 
#define wt(x) write(x)
#define R register
#define I inline
using namespace std;
const int N=1e5+5;
const int SIZE=317;
I int read() 
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0') {if (ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
I void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}
int n,m;
int a[N],cnt[N],block[N];
int pow1[N],pow2[N];
unordered_set<int> sum2;
int sum[N],ans[N];
struct Query
{
    int l,r,id,mod;
    bool operator<(const Query& o) const 
    {
        if (block[l]^block[o.l]) return l<o.l;
        else if (block[l]&1) return r<o.r;
        else return r>o.r;
    }//莫队排序
};
Query q[N];
I void add(int x) 
{
    if (cnt[a[x]]) 
    { 
        sum[cnt[a[x]]]-=a[x];
        if (!sum[cnt[a[x]]]) sum2.erase(cnt[a[x]]);
    }
    cnt[a[x]]++;
    if (!sum[cnt[a[x]]]) sum2.insert(cnt[a[x]]);
    sum[cnt[a[x]]]+=a[x];
}
I void del(int x) 
{
	sum[cnt[a[x]]]-=a[x];
	if (!sum[cnt[a[x]]]) sum2.erase(cnt[a[x]]);
	cnt[a[x]]--;
	if (!cnt[a[x]])  return;
    else 
    {
		if (!sum[cnt[a[x]]]) sum2.insert(cnt[a[x]]);
		sum[cnt[a[x]]]+=a[x];
	}
}
I void Init(int Mod) 
{
    pow1[0]=pow2[0]=1;
    for (R int i=1;i<=SIZE;i++) pow1[i]=1LL*pow1[i-1]*2%Mod;
    pow2[1]=pow1[SIZE];
    for (R int i=2;i<=SIZE;i++) pow2[i]=1LL*pow2[i-1]*pow2[1]%Mod;
}
I int gsm(int x,int Mod) {return pow1[x%SIZE]*pow2[x/SIZE]%Mod;}

I int get(int l,int r,int Mod) 
{
	int ans=0;
	int S=gsm(r-l+1,Mod);
	for (int it:sum2) ans=(ans+sum[it]*(S-gsm(r-l+1-it,Mod)+Mod)%Mod)%Mod;
	return ans%Mod;
}

signed main() 
{
    rd(n);rd(m);
    for (R int i=1;i<=n;i++) rd(a[i]);
    for (R int i=1;i<=n;i++) block[i]=(i-1)/SIZE+1;
    for (R int i=1;i<=m;i++) 
    {
        rd(q[i].l);
        rd(q[i].r);
        rd(q[i].mod);
        q[i].id=i;
    }
    sort(q+1,q+m+1);
    int l=q[1].l,r=l-1;
    for (R int i=1;i<=m;i++) 
    {
        while(l<q[i].l) del(l++);
        while(l>q[i].l) add(--l);
        while(r<q[i].r) add(++r);
        while(r>q[i].r) del(r--);
        Init(q[i].mod);
        ans[q[i].id]=get(q[i].l,q[i].r,q[i].mod);
    }
    for (R int i=1;i<=m;i++) {wt(ans[i]);putchar('\n');}
}
```


---

## 作者：Karry5307 (赞：1)

### 题意

给定一个长度为 $n$ 的序列 $a$ 和 $m$ 次询问，第 $i$ 次询问需要求出 $[l_i,r_i]$ 内所有子序列去重之后的和，对 $p_i$ 取模。

$\texttt{Data Range:}1\leq n,m,a_i\leq 10^5,1\leq p_i\leq 10^9$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13696282.html)

人生第一道 Ynoi，写篇题解祭之。

我们与其考虑某个子序列包含了哪些值，还不如看某个值能贡献到多少个子序列。

然而正着做不好做，因为一个子序列中某个值可能出现多次，所以考虑反过来看一个值不能贡献到多少个子序列，再用总的减去这个子序列就好了。

考虑某一个 $[l,r]$ 的询问，其中某个数出现了 $k$ 次，可以很容易由上面的分析知道这个数将会对 $2^{r-l+1}-2^{r-l+1-k}$ 个子序列产生贡献。

同时，注意到多个出现次数相同的数可以一起加起来贡献。所以我们可以考虑设 $b_k$ 为当前的区间内出现了 $k$ 次的所有数的和，那么我们可以得到答案为

$$\sum\limits_{k}b_k\left(2^{r-l+1}-2^{r-l+1-k}\right)$$

注意到 $b_k$ 可以使用莫队来维护，所以我们就得到了一个 $O(nm\log n)$ 的算法，但是无法通过。

考虑统计答案的时候我们会枚举很多等于 $0$ 的 $b_k$。所以我们在移动区间端点的时候可以同时用链表记录一下满足 $b_k\neq 0$ 的那些 $k$。

注意到链表中记录的 $k$ 是 $O(\sqrt{n})$ 的，所以时间复杂度就变为 $O(m\sqrt{n}\log n)$，还是会 TLE。

注意到这个 $\log$ 甚至都可以搞掉，考虑分块打表，对于每个询问都预处理一次，因为一次预处理是 $O(\sqrt{n})$ 的，所以复杂度为 $O(m\sqrt{n})$，加上一些基本的卡常技巧就可以过了。

### 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51; 
struct Query{
	ll l,r,p,id;
	inline bool operator <(const Query &rhs)const;
};
Query qry[MAXN];
ll n,qcnt,l,r,p,blockSize,ptrl,ptrr,len,hd;
li rres;
ll x[MAXN],res[MAXN],cntl[MAXN],sum[MAXN],prv[MAXN],nxt[MAXN];
ll blk[MAXN],pw[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline bool Query::operator <(const Query &rhs)const
{
	if(l/blockSize==rhs.l/blockSize)
	{
		return l/blockSize==1?r<rhs.r:r>rhs.r;
	}
	return l<rhs.l;
}
inline void insert(ll x)
{
	prv[x]=0,nxt[x]=hd,prv[hd]=x,hd=x;
}
inline void erase(ll x)
{
	if(x==hd)
	{
		return (void)(hd=nxt[x],prv[nxt[x]]=prv[x]=nxt[x]=0);
	}
	nxt[prv[x]]=nxt[x],prv[nxt[x]]=prv[x],prv[x]=nxt[x]=0;
}
inline void add(ll pos)
{
	if(!(cntl[x[pos]]++))
	{
		sum[1]+=x[pos];
	}
	else
	{
		sum[cntl[x[pos]]-1]-=x[pos],sum[cntl[x[pos]]]+=x[pos];
	}
	if(sum[cntl[x[pos]]]==x[pos])
	{
		insert(cntl[x[pos]]);
	}
	if(!sum[cntl[x[pos]]-1])
	{
		erase(cntl[x[pos]]-1);
	}
}
inline void del(ll pos)
{
	if(!(--cntl[x[pos]]))
	{
		sum[1]-=x[pos];
	}
	else
	{
		sum[cntl[x[pos]]+1]-=x[pos],sum[cntl[x[pos]]]+=x[pos];
	}
	if(sum[cntl[x[pos]]]==x[pos])
	{
		insert(cntl[x[pos]]);
	}
	if(!sum[cntl[x[pos]]+1])
	{
		erase(cntl[x[pos]]+1);
	}
}
inline void setup(ll md)
{
	pw[0]=blk[0]=1;
	for(register int i=1;i<=511;i++)
	{
		pw[i]=(pw[i-1]+pw[i-1])%md;
	}
	blk[1]=(pw[511]+pw[511])%md;
	for(register int i=1;i<=512;i++)
	{
		blk[i]=(li)blk[i-1]*blk[1]%md;
	}
}
inline ll query(ll x,ll md)
{
	return (li)blk[x>>9]*pw[x&511]%md;
}
int main()
{
	blockSize=sqrt(n=read()),qcnt=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=read();
	}
	for(register int i=1;i<=qcnt;i++)
	{
		l=read(),r=read(),p=read(),qry[i]=(Query){l,r,p,i};
	}
	sort(qry+1,qry+qcnt+1),ptrl=1;
	for(register int i=1;i<=qcnt;i++)
	{
		while(ptrr<qry[i].r)
		{
			add(++ptrr);
		}
		while(ptrr>qry[i].r)
		{
			del(ptrr--);
		}
		while(ptrl<qry[i].l)
		{
			del(ptrl++);
		}
		while(ptrl>qry[i].l)
		{
			add(--ptrl);
		}
		setup(p=qry[i].p),len=qry[i].r-qry[i].l+1,rres=0;
		for(register int j=hd;j;j=nxt[j])
		{
			rres+=(li)sum[j]*(query(len,p)-query(len-j,p));
		}
		res[qry[i].id]=(rres%p+p)%p;
	}
	for(register int i=1;i<=qcnt;i++)
	{
		printf("%d\n",res[i]);
	}
}
```

---

## 作者：Jμdge (赞：1)

人傻常数大，跑得超级慢，鬼知道为什么



# noteskey

发现这里可以用莫队做，对于一个数 x 来讲，如果它在块 $l$ ~ $r$ 内出现 k 次，那么贡献为 $2^{len}-2^{len-k} , len=r-l+1$，但是空间复杂度爆炸，我们需要再来个根号分别处理的优化

总之就是莫队离线处理，每个块内大于 $\sqrt n$ 和小于 $\sqrt n$ 的分别处理，然后 update 的时候注意转化就好了


对于 2 的幂次就是 $O(\sqrt n)$ 预处理 + $O(1)$ 查询


# code

总之比较...短(dl)吧

```cpp
//by Judge
#include<bits/stdc++.h>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define bl 317
#define ll long long
using namespace std;
const int M=1e5+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int CCF=-1,Z;
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(int x,char chr='\n'){
    if(CCF>1<<20)Ot();if(x<0)sr[++CCF]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
} int n,m,pw1[bl+3],pw2[bl+3]; arr a,buc,ans,pos;
ll bvc[bl+3]; vector<int> lr; unordered_set<int> s;
inline int qpow(int p,int mod){ // O 1 快速幂 
	return 1ll*pw1[p%bl]*pw2[p/bl]%mod;
}
struct que{ int l,r,id,md; }q[M];
inline bool cmp(que& a,que& b){  // 莫队 cmp  
	return pos[a.l]^pos[b.l]?a.l<b.l:((a.r>b.r)^(pos[a.l]&1));
}
inline void ADD(int x){ const int val=a[x];
	if(buc[val]>bl) ++buc[val];
	else if(buc[val]==bl) bvc[buc[val]++]-=lr[val],s.insert(val);
	else bvc[buc[val]]-=lr[val],bvc[++buc[val]]+=lr[val];
}
inline void DEL(int x){ const int val=a[x];
	if(buc[val]>bl+1) --buc[val];  //在 bl 之外转化的 
	else if(buc[val]==bl+1) s.erase(val),bvc[--buc[val]]+=lr[val]; //要从大于 bl 转为 bl 以内的 
	else bvc[buc[val]]-=lr[val],bvc[--buc[val]]+=lr[val]; //在 bl 之内转化的 
}
int main(){ n=read(),m=read(); fp(i,1,n) pos[i]=(i-1)/bl+1;
	fp(i,1,n) lr.push_back(a[i]=read()); sort(lr.begin(),lr.end());
	fp(i,1,n) a[i]=lower_bound(lr.begin(),lr.end(),a[i])-lr.begin();
	fp(i,1,m) q[i].l=read(),q[i].r=read(),q[i].md=read(),q[i].id=i;
	sort(q+1,q+1+m,cmp); int l=1,r=0; fp(i,1,n) *bvc+=a[i];
	*pw1=*pw2=1; fp(i,1,m){ //莫队主体 
		while(r<q[i].r) ADD(++r); while(l>q[i].l) ADD(--l);
		while(r>q[i].r) DEL(r--); while(l<q[i].l) DEL(l++);
		const int md=q[i].md,len=r-l+1; //计算当前块的答案 
		fp(j,1,bl-1) pw1[j]=pw1[j-1]*2ll%md;
		pw2[1]=pw1[bl-1]*2ll%md;
		fp(j,2,bl) pw2[j]=1ll*pw2[1]*pw2[j-1]%md;
		int& ANS=ans[q[i].id]; const int all=qpow(len,md);
		fp(j,1,bl) (ANS+=1ll*(all-qpow(len-j,md)+md)*bvc[j]%md-md)+=ANS>>31&md;
		for(Rg int j: s) (ANS+=1ll*(all-qpow(len-buc[j],md)+md)*lr[j]%md-md)+=ANS>>31&md;
	} fp(i,1,m) print(ans[i]); return Ot(),0;
}
```




---

## 作者：Conless (赞：0)

>【幸好你在失去一切之前，回到了这里】

>【喜悦和悲伤】

>【还有喜欢某个人的情绪】

>【现在依旧还残存着一些吧？】

这题是一道偏向思维的莫队题，最主要的问题是将传统莫队模板题中的“区间 $[l,r]$ 中不同的数之和”换为了“区间中每个子序列不同的数之和”，显然，我们不能对每个子序列分别处理，那么我们则考虑从整个区间对子序列的贡献方面着手

若整个区间中某个数 $x$ 出现了 $k$ 次，那么它产生的贡献为：

$\qquad ans=x\times$（子序列个数-不含该数的子序列数）

$\qquad \qquad = x\times(2^{len}-2^{len-k})$

如果对于每个不同的 $x$ 进行计算，那么时间复杂度至少是 $O(mn)$ 级别的，但如果对于不同的 $k$ 计算，即使在最坏情况下，即：$n=\frac{k(k-1)}{2}$，在使用双向链表的情况下，我们会发现每次查询的总时间复杂度约为 $O(m\sqrt{n})$，再套上莫队的 $O(n\sqrt{n})$，是可以接受 $10^5$ 的数据量的。

但是在具体代码实现的过程中，我们会发现由于对于每一次询问，$p$ 各不相同，所以无法一次预处理，而根号的复杂度说明即使再套上一个快速幂的 $O(logn)$ 也将无法接受，所以可以考虑使用~~我看题解才知道的~~**光速幂**，我们注意到：

$\qquad 2^k = 2^{\frac{k}{\sqrt{n}}\times \sqrt{n}}=2^{\lfloor \frac{k}{\sqrt{n}}\rfloor \times \sqrt{n}}\times 2^{k\ mod\sqrt{n}}$

因此，可以对每次询问预处理出两个数组 $pow1,pow2$，分别储存 $2^1,2^2,2^3,...,2^{\sqrt{n}}$ 与 $2^{\sqrt{n}}, 2^{2\sqrt{n}},...,2^n$，那么在枚举 $k$ 计算时可以做到 $O(1)$ 得到2的整数次幂取模结果

当然，最后还是要记得使用一些~~防毒瘤~~卡常 $trick$:
1.fread读入（其实并没有优化太多）
2.手写双向链表
3.各种位运算优化莫队
...

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 4e5 + 5;

class QuickRead
{

public:
    inline char gc()
    {
        static const int IN_LEN = 1 << 18 | 1;
        static char buf[IN_LEN], *s, *t;
        return (s == t) && (t = (s = buf) + fread(buf, 1, IN_LEN, stdin)), s == t ? -1 : *s++;
    }

    template <typename _Tp>
    inline QuickRead & operator >> (_Tp & num)
    {
        static char ch, sgn;
        ch = gc();
        while (!isdigit(ch))
        {
            if (ch == -1)
                return *this;
            sgn |= (ch == '-');
            ch = gc();
        }
        num = 0;
        while (isdigit(ch))
        {
            num = (num << 1) + (num << 3) + (ch ^ 48);
            ch = gc();
        }
        sgn && (num = -num);
        return *this;
    }
} qin;

class LinkList
{

public:
    struct Node {
        int pre, nxt;
    } node[MAXN];
    int las;

    LinkList() { las = 0; }
    inline void insert(int x)
    {
        node[las].nxt = x;
        node[x].pre = las;
        las = x;
    }

    inline void erase(int x)
    {
        if (x ^ las)
        {
            node[node[x].pre].nxt = node[x].nxt;
            node[node[x].nxt].pre = node[x].pre;
        }
        else las = node[x].pre;
        node[x].pre = node[x].nxt = 0;
    }
} lis;

struct Ask {
    int l, r, pos, num;
    ll p;
    bool operator < (const Ask & x) const
    {
        if (pos != x.pos)
            return pos < x.pos;
        else {
            if (pos & 1)
                return r < x.r;
            else return r > x.r;
        }
    }
} query[MAXN];

inline void inc(ll & x, ll y, ll p) { x = (x + y) % p; }

int n, q, len;
ll data[MAXN], ans[MAXN];
int a[MAXN], cnt[MAXN];
ll sum[MAXN];
pair<int, int> b[MAXN];

inline void add(int num)
{
    sum[cnt[num]] -= data[num];
    if (!sum[cnt[num]])
        lis.erase(cnt[num]);
    cnt[num]++;
    if (!sum[cnt[num]])
        lis.insert(cnt[num]);
    sum[cnt[num]] += data[num];
}
inline void erase(int num)
{
    sum[cnt[num]] -= data[num];
    if (!sum[cnt[num]])
        lis.erase(cnt[num]);
    cnt[num]--;
    if (!sum[cnt[num]])
        lis.insert(cnt[num]);
    sum[cnt[num]] += data[num];
}

ll pow1[MAXN], pow2[MAXN];
/*  pow1[i] refers to 2^i,
    pow2[i] refers to 2^(i*sqrt(x)),
    so that 2^k = 2^[(k/sqrt(x))*sqrt(x)]*2^(k mod sqrt(x))
*/
inline void pre_pow(ll p)
{
    pow1[0] = 1;
    for (int i = 1; i <= len; i++)
        pow1[i] = 1LL * pow1[i - 1] * 2 % p;
    pow2[0] = 1;
    for (int i = 1; i <= len; i++)
        pow2[i] = 1LL * pow2[i - 1] * pow1[len] % p;
}
inline ll get_pow(ll k, ll p) { return 1LL * pow2[k / len] * pow1[k % len] % p; }

int main()
{
    qin >> n >> q;
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        qin >> b[i].first;
        b[i].second = i;
    }
    sort(b + 1, b + n + 1);
    for (int i = 1, j = 0; i <= n; i++)
    {
        if (b[i].first != b[i - 1].first)
            j++;
        a[b[i].second] = j;
        data[j] = (ll)b[i].first;
    }
    for (int i = 1; i <= q; i++)
    {
        qin >> query[i].l >> query[i].r >> query[i].p;
        query[i].pos = query[i].l / len;
        query[i].num = i;
    }
    sort(query + 1, query + q + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= q; i++)
    {
        pre_pow(query[i].p);
        while (l < query[i].l)
            erase(a[l++]);
        while (l > query[i].l)
            add(a[--l]);
        while (r < query[i].r)
            add(a[++r]);
        while (r > query[i].r)
            erase(a[r--]);
        int siz = query[i].r - query[i].l + 1;
        ll MOD = query[i].p;
        for (int j = lis.node[0].nxt; j; j = lis.node[j].nxt)
            inc(ans[query[i].num], sum[j] * (get_pow(siz, MOD) - get_pow(siz - j, MOD) + MOD) % MOD, MOD);
    }
    for (int i = 1; i <= q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
```

---

## 作者：徐致远 (赞：0)


[本蒟蒻的blog](https://www.chnxuzhiyuan.cn/2019/11/12/%E3%80%8CYnoi2015%E3%80%8D%E7%9B%BC%E5%90%9B%E5%8B%BF%E5%BF%98-Solution/)

### 题解

首先这是一道Ynoi的题，并且数据范围非常友好，直接上莫队。

但是这题的模数并不固定，考虑如何处理。

首先考虑一个数$x$，如果他在区间$[L,R]$内出现了$k$次，那么就一共有$2^{R-L+1}-2^{R-L+1-K}$个子序列包含$x$。

不难发现，出现次数相同的数可以一起处理。

而且，不同的出现次数是$O(\sqrt{n})$级别的。设出现了$k$次的数的和为$sum$，那么这些出现次数为$k$的数对答案的贡献就是$sum\cdot(2^{R-L+1}-2^{R-L+1-K})$。

所以，我们可以通过莫队来维护每一种出现次数的数的和，并用一个类似链表的东西来维护当前存在的不同的出现次数。

考虑如何在每次的模数变化之后快速计算$2^k \mod p$。

可以用一个类似于BSGS的算法，先在$O(\sqrt n)$的复杂度内预处理出$2^1,2^2,\cdots,2^{\sqrt n} \mod p$以及$2^{\sqrt n},2^{2\sqrt n},\cdots 2^{n} \mod p$的值，然后每次就可以$O(1)$计算$2^k \mod p$了。

所以在莫队的过程中，对于每个询问先预处理$2$的幂，然后更新出现次数的信息，再遍历每种出现次数计算贡献即可。

时间复杂度$O(n\sqrt n)$。

### 代码

```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100005;
int n,m,a[maxn],Area[maxn],S,ans[maxn],nxt[maxn],pre[maxn],til,cnt[maxn],Pow[400][2];LL sum[maxn];
inline int read()
{
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
inline int QP(int a,int b,int TT)
{
	int ret=1,w=a;
	while(b)
	{
		if(b&1) ret=(LL)ret*w%TT;
		w=(LL)w*w%TT;b>>=1;
	}
	return ret;
}
struct Query
{
	int L,R,p,id;
	bool operator < (const Query& b)const{return Area[L]<Area[b.L]||(Area[L]==Area[b.L]&&((Area[L]&1)?R>b.R:R<b.R));}
}Q[maxn];
inline void Ins(int x){nxt[til]=x;pre[x]=til;til=x;}
inline void Del(int x){x==til?til=pre[x]:nxt[pre[x]]=nxt[x],pre[nxt[x]]=pre[x];nxt[x]=pre[x]=0;}
inline void upt(int x,int del){sum[cnt[x]]-=x;if(!sum[cnt[x]]) Del(cnt[x]);cnt[x]+=del;if(!sum[cnt[x]]) Ins(cnt[x]);sum[cnt[x]]+=x;}
inline void init(int TT)
{
	Pow[0][0]=Pow[0][1]=1;
	int ps=QP(2,320,TT);
	for(int i=1;i<=320;i++)
	{
		Pow[i][0]=(LL)Pow[i-1][0]*2%TT;
		Pow[i][1]=(LL)Pow[i-1][1]*ps%TT;
	}
}
inline int CP(int x,int TT){return (LL)Pow[x%320][0]*Pow[x/320][1]%TT;}
inline void Solve()
{
	int L=1,R=0;
	for(int i=1;i<=m;i++)
	{
		init(Q[i].p);
		while(R<Q[i].R) upt(a[++R],1);
		while(L>Q[i].L) upt(a[--L],1);
		while(R>Q[i].R) upt(a[R--],-1);
		while(L<Q[i].L) upt(a[L++],-1);
		int po=nxt[0];
		while(po)
		{
			ans[Q[i].id]=(ans[Q[i].id]+(LL)sum[po]*(CP(R-L+1,Q[i].p)-CP(R-L+1-po,Q[i].p)+Q[i].p)%Q[i].p)%Q[i].p;
			po=nxt[po];
		}
	}
}
int main()
{
	n=read();m=read();S=sqrt(n)+1e-10;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) Area[i]=(i-1)/S+1;
	for(int i=1;i<=m;i++){Q[i].L=read();Q[i].R=read();Q[i].p=read();Q[i].id=i;}
	sort(Q+1,Q+1+m);Solve();
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：Sol1 (赞：0)

> 在太阳西斜的这个世界里，置身天上之森。等这场战争结束之后，不归之人与望眼欲穿的众人， 人人本着正义之名，长存不灭的过去、逐渐消逝的未来。我回来了，纵使日薄西山，即便看不到未来，此时此刻的光辉，盼君勿忘。

> ————世界上最幸福的女孩

珂朵莉，加油。

---

这里介绍一种可以得到很快速度的做法，参考了最优解。

首先考虑子序列肯定是行不通的，因为子序列太多了；所以反向考虑每一个数对于答案的贡献。对于每一个数$x$，如果在区间$[l,r]$内出现了$y$次：

因为其他的数都可选可不选，而$x$必须选至少一个，所以贡献为$2^{r-l+1-y}\cdot(2^y-1)=2^{r-l+1}-2^{r-l+1-y}$。

但是膜数不一样怎么破？

注意到贡献分为$2^{r-l+1}$和$-2^{r-l+1-y}$。

此时第一部分可以利用$O(\sqrt N)$预处理$O(1)$查询的方式求定底数次幂。

又可以观察到一个性质：出现次数最多只有$O(\sqrt N)$种，因为$\sum\limits_{i=1}^{\sqrt N}i=O(N)$，所以问题转化为维护每一个数的出现次数。

这里就是要优化的部分了：其他大佬都使用unordered_set轻松地过掉了，而我只能卡到82分（人傻常数大）。

因为这个东西是无序的，且值域很小，所以可以使用权值上的双向链表来维护。这样可以完全抛弃STL拖后腿的巨大常数。

总复杂度$O(M \sqrt{N})$。

但是我的解法的速度较最优解仍是相差甚远，开满氧气的情况下最大点也需要2.88s。~~起码能过~~

```cpp
#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
//开满氧气（
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

//使用fread以获得更快的速度
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

const int S = 317;
struct Query {
	int l, r, i;
	long long mod;
};
int n, q, a[100005], cnt[100005], ans[100005], pow2[320], p2sqrt[320], esum[100005], plc[100005];
int prv[100005], nxt[100005], hd;
Query qry[100005];
//双向权值链表
inline void AddX(int x) {
	prv[x] = 0;
	nxt[x] = hd;
	prv[hd] = x;
	hd = x;
}

inline void DelX(int x) {
	if (x == hd) {
		prv[nxt[x]] = -1;
		hd = nxt[x];
	} else {
		nxt[prv[x]] = nxt[x];
		prv[nxt[x]] = prv[x];
	}
}

//最快莫队的比较方式
inline bool cmp(Query q1, Query q2) {
	return ((plc[q1.l] ^ plc[q2.l]) ? plc[q1.l] < plc[q2.l] : (plc[q1.l] & 1 ? q1.r < q2.r : q2.r < q1.r));
}

//快读
inline int qread() {
	register char c = getchar();
	register int x = 0;
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x;
}

inline void Read() {
	n = qread();
	q = qread();
	for (register int i = 1;i <= n;i++) a[i] = qread(), plc[i] = (i - 1) / S + 1;
	for (register int i = 1;i <= q;i++) {
		qry[qry[i].i = i].l = qread(); qry[i].r = qread(); qry[i].mod = qread();
	}
}
//向莫队中添加元素
inline void Add(int pos) {
	if (cnt[a[pos]]) {
		esum[cnt[a[pos]]] -= a[pos];
		if (!esum[cnt[a[pos]]]) DelX(cnt[a[pos]]);
	}
	cnt[a[pos]]++;
	if (!esum[cnt[a[pos]]]) AddX(cnt[a[pos]]);
	esum[cnt[a[pos]]] += a[pos];
}
//从莫队中删除元素
inline void Del(int pos) {
	esum[cnt[a[pos]]] -= a[pos];
	if (!esum[cnt[a[pos]]]) DelX(cnt[a[pos]]);
	cnt[a[pos]]--;
	if (cnt[a[pos]]) {
		if (!esum[cnt[a[pos]]]) AddX(cnt[a[pos]]);
		esum[cnt[a[pos]]] += a[pos];
	}
}
//求快速幂
inline long long Power2(int x, int mod) {
	return 1ll * p2sqrt[x / S] * pow2[x % S] % mod;
}

inline void Solve() {
	hd = 0;
	sort(qry + 1, qry + q + 1, cmp);
	register int l = qry[1].l, r = l - 1;
	for (register int i = 1;i <= q;i++) {
    		//预处理快速幂
		pow2[0] = 1;
		for (register int j = 1;j <= S;j++) pow2[j] = (1ll * pow2[j - 1] << 1) % qry[i].mod;
		p2sqrt[0] = 1;
		for (register int j = 1;j <= S;j++) p2sqrt[j] = 1ll * p2sqrt[j - 1] * pow2[S] % qry[i].mod;
        	//修改莫队
		while (r < qry[i].r) {
			Add(++r);
		}
		while (r > qry[i].r) {
			Del(r--);
		}
		while (l < qry[i].l) {
			Del(l++);
		}
		while (l > qry[i].l) {
			Add(--l);
		}
        	//求答案
		for (register int j = hd;j;j = nxt[j]) {
			ans[qry[i].i] = (ans[qry[i].i] + esum[j] * ((Power2(r - l + 1, qry[i].mod) 
				- Power2(r - l + 1 - j, qry[i].mod)) % qry[i].mod + qry[i].mod) % qry[i].mod) % qry[i].mod;
		}
	}
	for (register int i = 1;i <= q;i++) printf("%d\n", ans[i]);
}

int main() {
	Read();
	Solve();
	return 0;
}
```

---

