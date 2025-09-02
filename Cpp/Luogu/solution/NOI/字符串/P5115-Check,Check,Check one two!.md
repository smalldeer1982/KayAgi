# Check,Check,Check one two!

## 题目背景

您正在听くらげP的チェチェ・チェック・ワンツー!，突然教导主任推门进来了，于是您只好假装自己在写字符串题

~~(结果教导主任一眼秒了这水题，您因没事刷水题被批判了一番)~~

## 题目描述

给定一个字符串

我们定义$lcp(i,j)$表示从字符串第$i$个位置开始的后缀和从第$j$个位置开始的后缀的最长公共前缀长度

我们定义$lcs(i,j)$表示在字符串第$i$个位置结束的前缀和在第$j$个位置结束的前缀的最长公共后缀长度

现在给定一个长度为$n$的字符串，希望您求出

$$\sum_{1\leq i < j \leq n}lcp(i,j)lcs(i,j)[lcp(i,j)\leq k1][lcs(i,j) \leq k2]$$

模$2^{64}$的值(也就是unsigned long long自然溢出即可)

$[lcs(i,j) \leq k]$表示如果$lcs(i,j) \leq k$这个命题为真那么这个式子的值是1否则是0,另外一个方括号也是同理



## 说明/提示

设n表示字符串的长度

测试点10的分值为1,这个测试点的$n \leq 1000$

对于所有的测试点

$$1 \leq n \leq 10^5,1\leq k1 , k2 \leq n$$

## 样例 #1

### 输入

```
aabccbbbcbbcbccacbcb
8 20```

### 输出

```
140```

## 样例 #2

### 输入

```
checkcheckcheckonetwo
7 11```

### 输出

```
216```

# 题解

## 作者：Alex_Wei (赞：14)

[P5115 Check, Check, Check one two!](https://www.luogu.com.cn/problem/P5115)

看到题目，我首先想到建出正反串 SA 及其 $ht$ 的笛卡尔树，并在一棵树上启发式合并，另一棵树上用 P4211 LCA 套路做，掐指一算发现时间复杂度是 $\mathcal{O}(n\log ^ 3 n)$，虽然离线（枚举 LCA，考虑较小子树对较大子树的贡献，将询问离线扫描线）后三个 $\log$ 分别是启发式合并，BIT 和树剖，显然卡不满，但是依然非常难写。

稍微观察一下 $\mathrm{lcp}(i, j)$ 和 $\mathrm{lcs}(i, j)$，它们拼接起来形成长为 $\mathrm{lcp}(i, j) + \mathrm{lcs}(i, j) - 1$ 的相等子串，联想到优秀的拆分，这启发我们在 $(i - \mathrm{lcs}(i, j) + 1, j - \mathrm{lcs}(i, j) + 1)$ 处统计贡献。因为相等子串的要求 **极长**，否则 $\mathrm{lcp}(i, j)$ 或 $\mathrm{lcs}(i, j)$ 可以更大，所以枚举 $i, j$，若 $s_{i - 1} \neq s_{j - 1}$，则 $s[i, i + \mathrm{lcp}(i, j) - 1]$ 产生贡献。进一步地，我们发现贡献和 $i, j$ 具体无关，仅和 $L = \mathrm{lcp}(i, j)$ 相关，为 $f(L) = \sum\limits_{p = 1} ^ L p(L - p + 1) [p\leq k_1][L - p + 1 \leq k_2]$。$f$ 可以 $\mathcal{O}(n)$ 预处理。

对于 $s_{i - 1} \neq s_{j - 1}$ 的要求，直接容斥。问题转化为求与任意两个 $(i, j)(i < j)$ 的 $\mathrm{lcp}(i, j)$ 相关的式子。经典套路，直接对 $ht$ 做扫描单调栈，对于当前 $i$ 实时维护 $\sum\limits_{1\leq j < i} f(\min_{p = j + 1} ^ i ht_p)$ 即可。时间复杂度 $\mathcal{O}(n(\log n + |\Sigma|))$。

理论可以做到关于长度加字符集线性（线性 SA，线性区间 RMQ），但不实用。

听说官方题解是 $\log ^ 2 n$ 的边分树，应该是对题解一开始的 $\log ^ 3 n$ 思路应用更多套路。对比两种做法，直接硬做没有用到拼接成相等子串的性质，而扫描单调栈巧妙运用了该性质。对于前者，可以扩展至无法拼接的问题而后者不能，如给定排列 $p$，将原问题 $\mathrm{lcp}(i, j)$ 换成 $\mathrm{lcp}(p_i, p_j)$。对于后者，可以扩展至任意容易快速计算 $f$ 的情形，如 $(\mathrm{lcp}(i, j) \mathrm{lcs}(i, j)) ^ k$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
constexpr int N = 1e5 + 5;
ull f[N], ans;
int n, k1, k2;
char s[N];
ull S1(ull x) {return x * (x + 1) / 2;}
ull S2(ull x) {return x * (x + 1) * (x + x + 1) / 6;}
int sa[N], rk[N], ork[N], buc[N], id[N], ht[N];
bool cmp(int a, int b, int w) {return ork[a] == ork[b] && ork[a + w] == ork[b + w];}
void build() {
  int m = 1 << 7, p = 0;
  for(int i = 1; i <= n; i++) buc[rk[i] = s[i]]++;
  for(int i = 1; i <= m; i++) buc[i] += buc[i - 1];
  for(int i = n; i; i--) sa[buc[rk[i]]--] = i;
  for(int w = 1; ; w <<= 1, m = p, p = 0) {
    for(int i = n - w + 1; i <= n; i++) id[++p] = i;
    for(int i = 1; i <= n; i++) if(sa[i] > w) id[++p] = sa[i] - w;
    memset(buc, 0, sizeof(buc));
    memcpy(ork, rk, sizeof(rk)), p = 0;
    for(int i = 1; i <= n; i++) buc[rk[i]]++;
    for(int i = 1; i <= m; i++) buc[i] += buc[i - 1];
    for(int i = n; i; i--) sa[buc[rk[id[i]]]--] = id[i];
    for(int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i - 1], sa[i], w) ? p : ++p;
    if(p == n) break;
  }
  for(int i = 1, k = 0; i <= n; i++) {
    if(k) k--;
    while(s[i + k] == s[sa[rk[i] - 1] + k]) k++;
    ht[rk[i]] = k;
  }
}
ull calc(char lim) {
  static int stc[N], w[N], top;
  ull cur = 0, ans = top = 0;
  for(int i = 2; i <= n; i++) {
    int wid = lim ? s[sa[i - 1] - 1] == lim : 1;
    while(top && stc[top] >= ht[i]) cur -= w[top] * f[stc[top]], wid += w[top--];
    stc[++top] = ht[i], w[top] = wid, cur += wid * f[ht[i]];
    if(lim ? s[sa[i] - 1] == lim : 1) ans += cur;
  }
  return ans;
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  cin >> s + 1 >> k1 >> k2, n = strlen(s + 1);
  for(int L = 1; L <= n; L++) {
    int l = max(1, L - k2 + 1), r = min(L, k1);
    if(l > r) break;
    f[L] = (S1(r) - S1(l - 1)) * (L + 1) - (S2(r) - S2(l - 1));
  }
  build(), ans += calc(0);
  for(int i = 0; i < 26; i++) ans -= calc('a' + i);
  cout << ans << "\n";
  return 0;
}
```

---

## 作者：Deep_Kevin (赞：8)

首先我们考虑对于一个点对$(i,j)$来说，要找到前面极长的匹配$a$，后面极长的匹配$b$，贡献是两者长度的乘积$(a+1)*(b+1)$，我们考虑在SAM上$(i+p,j+p),p\in[0,b]$两个$endpos$合并时统计$(i,j)$的贡献。

由于后缀自动机上两个$endpos$的$LCA$的$maxlen$就是对应两个前缀的最长公共后缀，所以我们可以肯定的是，当$(i+p,j+p)$合并时，设对应点的$maxlen$为$c$，$(i+p-c+1,j+p-c+1)=(i-a,j-a)$

$(i,j)$会被$b+1$种点对统计到，我们只需要在每一次被统计到时给答案加上$a+1$就可以了。在$SAM$节点上，贡献和相当于每次加一个等差数列。
这时候没有$k1,k2$限制的答案已经出来了。
考虑上$k2$的限制，我们发现只要限制一下每次加的等差数列的末项不大于$k2$就可以了。

$k1$的限制怎么办，对于一个$SAM$上的节点，我们看是否存在被**恰好**计算第$k1+1$次的节点，如果存在，那么减去其产生的所有贡献。同时，这个还限制了等差数列的首项不小于$maxlen_i-k1+1$。具体可以看看代码怎么写。

好像我的做法与其他题解不大相同，同时也以$90ms$的运行时间成为了**题解提交时间为止**的最优解。

代码十分简洁明了，个人在处理$SAM$上$fail$树合并问题时钟爱对长度基数排序。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=200010;
int fail[N],ch[N][26],mx[N],n,k1,k2,las,rig[N],sum[N],a[N],tot;
unsigned long long op[N],ans;
char s[N];

void insert(int c){
	int x=++tot,p=las;las=x;mx[x]=mx[p]+1;rig[x]=1;
	for(;p!=-1 && !ch[p][c];p=fail[p]) ch[p][c]=x;
	if(p==-1) fail[x]=0;
	else if(mx[ch[p][c]]==mx[p]+1) fail[x]=ch[p][c];
	else{
		int q=++tot,tmp=ch[p][c];mx[q]=mx[p]+1;
		fail[q]=fail[tmp];fail[x]=fail[tmp]=q;
		for(int i=0;i<26;i++) ch[q][i]=ch[tmp][i];
		for(;p!=-1 && ch[p][c]==tmp;p=fail[p]) ch[p][c]=q;
	}
}

unsigned long long gs(int x,int y){
	if(x>y) return 0;
	return 1ull*(x+y)*(y-x+1)/2;
}

int main(){
	scanf("%s",s+1);n=strlen(s+1);
	scanf("%d %d",&k1,&k2);fail[0]=-1;
	for(int i=1;i<=n;i++) insert(s[i]-'a');
	for(int i=1;i<=tot;i++) sum[mx[i]]++;
	for(int i=n;i>=1;i--) sum[i]+=sum[i+1];
	for(int i=1;i<=tot;i++) a[sum[mx[i]]--]=i;
	for(int i=1;i<=tot;i++){
		int x=a[i];
		op[fail[x]]+=1ull*rig[x]*rig[fail[x]];
		rig[fail[x]]+=rig[x];
		ans+=op[x]*gs(max(1,mx[x]-k1+1),min(k2,mx[x]));
		if(mx[x]>k1 && mx[x]-k1<=k2) ans-=1ull*op[x]*(mx[x]-k1)*k1;
	}
	printf("%llu\n",ans);
}
```


---

## 作者：qwaszx (赞：7)

时代...变了啊...

orz _rqy shadowice1984

-----

一开始胡出来一个想想就巨大长的俩log的dsu做法，看看题解发现有精巧做法

对于 $(i,j)$ ，我们发现 $S[i-lcs(i,j)+1,i+lcp(i,j)-1]$ 和 $S[j-lcs(i,j)+1,j+lcp(i,j)-1]$ 是完全相同的，于是我们可以枚举所有这样的子串来计算贡献，对于一个子串 $T$，考虑它的两个出现位置，如果这两次出现都是**极长**的（即向左向右扩展都会使得这两个串不同），那么 $T$ 中的每一个位置都会造成贡献. 具体地，这个贡献是

$$
\sum_{i=1}^{|T|}[i\leq k2,|T|-i+1\leq k1]i(|T|-i+1)
$$

即枚举 $lcs$ 的长度 $i$. 上式容易 $O(1)$ 计算. 那么我们考虑在SAM的parent tree上计算，每次合并上来一个子树计算答案，显然我们应该只计算该节点的最长串的贡献，容易知道新合并上来的节点的左端一定是极长的，只需要限制右边极长，那么我们用总的减去右边非极长的，这个只需要对每个节点维护一个 $cnt[u][c]$ 表示其所有endpos中下一位为 $c$ 的方案数即可. 

复杂度 $O(26n)$，非常好写.

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=2e5+5000;
struct Node{int len,fa,ch[26];}a[N];
unsigned long long f[N];
int size[N],cnt[N][26],K1,K2,n,precnt[N],cur,node_cnt,id[N];
char st[N];
unsigned long long calc1(int n){return 1ull*n*(n+1)>>1;}
unsigned long long calc2(int n){return 1ull*n*(n-1)*(n+1)/3;}
void prework()
{
    for(int i=1;i<=n;i++)//预处理f[i]表示|T|=i的贡献
    {
        int l=max(1,i-K2+1),r=min(i,K1);
        if(l<=r)f[i]=i*(calc1(r)-calc1(l-1))-(calc2(r)-calc2(l-1));
    }
}
void ins(int ch,int pos)
{
    int u=cur;cur=++node_cnt;a[cur].len=a[u].len+1;
    size[cur]=1;if(pos!=n)cnt[cur][st[pos+1]-97]=1;
    for(;u&&!a[u].ch[ch];u=a[u].fa)a[u].ch[ch]=cur;
    if(!u){a[cur].fa=1;return;}
    int v=a[u].ch[ch];if(a[v].len==a[u].len+1){a[cur].fa=v;return;}
    int t=++node_cnt;a[t]=a[v];a[t].len=a[u].len+1;
    a[cur].fa=a[v].fa=t;
    for(;u&&a[u].ch[ch]==v;u=a[u].fa)a[u].ch[ch]=t;
}
void merge(int u,int v)
{
    size[u]+=size[v];
    for(int i=0;i<26;i++)cnt[u][i]+=cnt[v][i];
}
unsigned long long calc(int u,int v)
{
    unsigned long long ans=1ull*size[u]*size[v];//总的
    for(int i=0;i<26;i++)ans-=1ull*cnt[u][i]*cnt[v][i];//非极长的
    return ans;
}
int main()
{
    scanf("%s",st+1);n=strlen(st+1);node_cnt=cur=1;
    for(int i=1;i<=n;i++)ins(st[i]-97,i);
    scanf("%d%d",&K1,&K2);
    prework();
    for(int i=1;i<=node_cnt;i++)precnt[a[i].len]++;
    for(int i=1;i<=n;i++)precnt[i]+=precnt[i-1];
    for(int i=1;i<=node_cnt;i++)id[precnt[a[i].len]--]=i;
    unsigned long long ans=0;
    for(int i=node_cnt;i>=2;i--)
    {
        int u=id[i],fa=a[u].fa;
        ans+=f[a[fa].len]*calc(fa,u);merge(fa,u);//贡献系数相同，只需要算方案数
    }
    cout<<ans<<endl;
}
```

---

## 作者：Durant_Lee (赞：7)

[欢迎来我的blog逛逛](https://blog.csdn.net/Dream_Lolita/article/details/85318555)

这个做法是在问了rqy巨佬以后才会的，一时觉得自己十分菜，rqy赛高！

我们要求的是这个东西：
$$\sum_{1\leq i<j\leq n}lcp(i,j)lcs(i,j)[lcp(i,j)\leq k_1][lcs(i,j)\leq k_2]$$
其中$lcp(i,j)$表示第$i$个后缀和第$j$个后缀的$lcp$，$lcs(i,j)$表示第$i$个前缀和第$j$个前缀的$lcs$。

由于题目中定义的$lcp$和$lcs$是以一个点为中心往两边计算的，我们不妨将它们拼在一起。

具体来说，假设我们知道$lcp(i,j)$和$lcs(i,j)$，那么我们不难得到：$$S[i-lcp(i,j)+1\dots i+lcs(i,j)-1]=S[j-lcp(i,j)+1\dots j+lcs(i,j)-1]$$
且$$S[i-lcp(i,j)]\neq S[j-lcp(i,j)],S[i+lcs(i,j)]\neq S[j+lcs(i,j)]$$

那么现在我们相当于得到一个长度为$len=lcp(i,j)+lcs(i,j)-1$的串，这个串的每个位置都可以作为中间点来计算贡献。这个贡献我们是可以快速计算出来的，具体来说我们有：
$$\sum_{i=1}^{k_1}i(len-i+1)-\sum_{i=1}^{len-k_2}(len-i+1)$$
这里的上下标可能需要取个$\text{max}$或$\text{min}$，具体可以看代码或者手推一波。

于是我们对$S$建出后缀数组，那么我们要考虑的就是每两个后缀之间的贡献。显然两个后缀$i,j$有贡献当且仅当它们的$lcp$不为$0$且$S[i-1]\neq S[j-1]$。

这样做法就比较显然了：每个后缀$i$要记录$S[i-1]$是什么字符，按$\text{height}$从大到小拆隔板进行启发式合并，考虑有多少对贡献的时候直接容斥一下，然后乘上长度为当前$\text{height}$的贡献即可。

时间复杂度是$O(n\log n)$的，写起来简单易懂。

由于一些奇怪的原因我的后缀数组板子并不太对，在建出来以后需要一些“调整”，大家大可以忽略下面的代码。

```cpp
#include<bits/stdc++.h>
#define mkp make_pair
#define fi first
#define se second
using namespace std;

typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e5+10;
int n,k1,k2;
int a[N],lp[N],rp[N],siz[N],bl[N],cnt[N][28];
char s[N];
pii h[N];
ull ans,f[N];

namespace SA
{
	int rk[N],hi[N];
	int wa[N],wb[N],wx[N],wy[N],sa[N];
	bool cmp(int *r,int a,int b,int l){return r[a]==r[b] && r[a+l]==r[b+l];}
	void getsa(int *r,int n,int m)
	{
		int *x=wa,*y=wb,*t,i,j,p;
		for(i=0;i<m;++i) wx[i]=0;
		for(i=0;i<n;++i) wx[x[i]=r[i]]++;
		for(i=1;i<m;++i) wx[i]+=wx[i-1];
		for(i=n-1;~i;--i) sa[--wx[x[i]]]=i;
		for(j=1,p=0;p<n;j<<=1,m=p)
		{
			for(p=0,i=n-j;i<n;++i) y[p++]=i;
			for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
			for(i=0;i<m;++i) wx[i]=0;
			for(i=0;i<n;++i) wx[wy[i]=x[y[i]]]++;
			for(i=1;i<m;++i) wx[i]+=wx[i-1];
			for(i=n-1;~i;--i) sa[--wx[wy[i]]]=y[i];
			for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i) 
				x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
		}
	}
	void getheight(int *r)
	{
		int i,j,k=0;
		for(i=1;i<=n;++i) rk[sa[i]]=i;
		for(i=0;i<n;hi[rk[i++]]=k)
			for(k?k--:0,j=sa[rk[i]-1];r[i+k]==r[j+k];++k);
	}
	void adjust()
	{
		for(int i=1;i<=n;++i) sa[i]++;
		for(int i=n;i;--i) rk[i]=rk[i-1];
		sa[0]=rk[0]=0;
	}
}
using namespace SA;

ull sq(int x){return (ull)(x+1)*x/2;}
ull sq2(int x){return (ull)x*(2*x+1)*(x+1)/6;}
ull getf(int x)
{
	if(x>=k1+k2)return 0;
	ull s1=(ull)sq(min(x,k1))*(x+1)-sq2(min(x,k1));
	ull s2=(ull)sq(max(0,x-k2))*(x+1)-sq2(max(0,x-k2));
	return (ull)s1-s2;
}

void init()
{
	scanf("%s%d%d",s,&k1,&k2);n=strlen(s);
	k1=min(k1,n);k2=min(k2,n);
	for(int i=1;i<=n;++i) f[i]=getf(i);
	for(int i=0;i<n;++i) a[i]=s[i]-'a'+1;
	getsa(a,n+1,30);getheight(a);adjust();
	for(int i=n;i;--i) a[i]=a[i-1]; a[0]=0;
	for(int i=1;i<=n;++i) lp[i]=rp[i]=bl[i]=i,siz[i]=1,cnt[i][a[sa[i]-1]]++;
	for(int i=2;i<=n;++i) h[i-1]=mkp(-hi[i],i);
	sort(h+1,h+n);
}

ull calc(int x,int y)
{
	ull res=(ull)siz[x]*siz[y];
	for(int i=1;i<=26;++i) res-=(ull)cnt[x][i]*cnt[y][i];
	return res; 
}

void merge(int x,int y)
{
	for(int i=1;i<=26;++i) cnt[y][i]+=cnt[x][i];
	for(int i=lp[x];i<=rp[x];++i) bl[i]=y;
	lp[y]=min(lp[y],lp[x]);rp[y]=max(rp[y],rp[x]);siz[y]+=siz[x];
}

void solve()
{
	for(int i=1;i<n;++i) 
	{
		int len=-h[i].fi,x=bl[h[i].se],y=bl[h[i].se-1];
		if(siz[x]>siz[y]) swap(x,y);
		ans+=(ull)f[len]*calc(x,y);merge(x,y);
	}
	printf("%llu",ans);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("LGP5115.in","r",stdin);
	freopen("LGP5115.out","w",stdout);
#endif
	init();solve();
	return 0;
}
```




---

## 作者：phigy (赞：5)

个人认为是最简单且最优的方法。

---

预处理：

$$F(x)=\sum_{i=1}^{x}i(x-i+1)[i\leq k_1][x-i+1\leq k_2]$$

拆 $\text {LCS}$：



$$=\sum_{1\leq i < j \leq n}[S_{i-1}\neq S_{j-1}]F(lcp(rk_i,rk_j))$$



拆贡献：

$$=\sum_{1\leq k\leq n}F(k)\sum_{1\leq i < j \leq n}[lcp(rk_i,rk_j)=k,S_{i-1}\neq S_{j-1}]$$

$$=\sum_{1\leq k\leq n}F(k)\sum_{1\leq i < j \leq n}[lcp(i,j)=k,S_{sa_i-1}\neq S_{sa_j-1}]$$

这个东西我们预处理每种 $S_{sa_i-1}$ 的前缀和，然后在 $\text{SA}$ 的 $\text{Height}$ 数组上跑单调栈统计。

单调栈使用方法参考 [P3804 【模板】后缀自动机（SAM）](https://www.luogu.com.cn/problem/P3804) 中的 $\text{SA}$ 解法。

理论上使用 $\text{SA-IS}$ 算法是可以达到 $\text{O(n)}$ 的优秀复杂度的。

```cpp
#include <iostream>
#include <cstring> 

#define int long long

using namespace std;

const int N=100000;
int m=127;
unsigned int l[N+5];
int h[N+5];
int n,k1,k2;
char s[N+5];
int rk[N+5];
int sa[N+5];
int id[N+5];
int cnt[N+5];
int oldrk[N+5];
int st[N+5],tot;
unsigned int ans;
unsigned int f[N+5];
unsigned int sum[N+5][28];

int calc1(int x)///1,2,3
{
	return x*(x+1)/2;	
} 
int calc2(int x)///1*2,2*3,3*4
{
	return  x*(x+1)*(x-1)/3;
}

signed main()
{
	int i,j,k;
	cin>>s+1;
	n=strlen(s+1);
	cin>>k1>>k2;
	for(i=1;i<=n;i++)
	{
		int l=max(i-k1+1,(int)1);
		int r=min(k2,i);
		if(l<=r)
		{
			f[i]=i*(calc1(r)-calc1(l-1))-(calc2(r)-calc2(l-1));
		} 
	}
	for(i=1;i<=n;i++)
    {
        rk[i]=s[i];
        cnt[rk[i]]++;
    }
    for(i=1;i<=m;i++)
    {
        cnt[i]+=cnt[i-1];
    }
    for(i=1;i<=n;i++)
    {
        sa[cnt[rk[i]]]=i;
        cnt[rk[i]]--;
    }
    for(int w=1,p;p!=n;w*=2,m=p)
    {
        for(p=0,i=n-w+1;i<=n;i++)
        {
            p++;
            id[p]=i;
        }
        for(i=1;i<=n;i++)
        {
            if(sa[i]>w)
            {
                p++;
                id[p]=sa[i]-w;
            }
        }
        memset(cnt,0,sizeof(cnt));
        for(i=1;i<=n;i++)
        {
            cnt[rk[i]]++;
        }
        for(i=1;i<=m;i++)
        {
            cnt[i]+=cnt[i-1];
        }
        for(i=n;i>=1;i--)
        {
            sa[cnt[rk[id[i]]]]=id[i];
            cnt[rk[id[i]]]--;
        }
        memcpy(oldrk+1,rk+1,n*sizeof(int));
        for(p=0,i=1;i<=n;i++)
        {
            if(oldrk[sa[i]]!=oldrk[sa[i-1]]||oldrk[sa[i]+w]!=oldrk[sa[i-1]+w])
            {
                p++;
            }
            rk[sa[i]]=p;
        }
    }
    for(i=1,j=0;i<=n;i++)
    {
        if(j)j--;
        while(s[i+j]==s[sa[rk[i]-1]+j])
        {
            j++;
        }
        h[rk[i]]=j;
	}
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=25;j++)
		{
			sum[i][j]+=sum[i-1][j];
		}
		if(sa[i]!=1)sum[i][s[sa[i]-1]-'a']++;
	}
	for(i=1;i<=n;i++)
	{
		while(tot&&h[i]<h[st[tot]])
		{
			unsigned int res=0;
			for(j=0;j<=25;j++)
			{
				res+=(sum[st[tot]-1][j]-sum[st[tot]-l[st[tot]]-1][j])*(sum[st[tot]+l[i]][j]-sum[st[tot]-1][j]);
			}
			ans+=f[h[st[tot]]]*((l[st[tot]])*(l[i]+1)-res); 
			l[i]+=l[st[tot]];
			tot--;
		}
		tot++;
		st[tot]=i;
		l[i]++;
	}
	while(tot)
	{
		unsigned int res=0;
		for(j=0;j<=25;j++)
		{
			res+=(sum[st[tot]-1][j]-sum[st[tot]-l[st[tot]]-1][j])*(sum[st[tot]+l[n+1]][j]-sum[st[tot]-1][j]);
		}
		ans+=f[h[st[tot]]]*((l[st[tot]])*(l[n+1]+1)-res); 
		l[n+1]+=l[st[tot]];
		tot--;
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：凯特琳 (赞：2)

[博客链接](https://blog.csdn.net/calabash_boy/article/details/102559568)
# 题意
给出串$S$，$K1,K2$，求
$$\sum_{1 \le i < j \le n}{LCP(i,j) \cdot LCS(i,j) \cdot [LCP(i,j) \le K1] \cdot [LCS(i,j) \le K2]}$$

# 题解
不是很懂边分树怎么维护信息的。。。只会边分。
首先对原串$S$和反串$S'$建立SAM，然后取出两棵$parent$树，然后在$S$的SAM中找到每个前缀点，以及$S'$的SAM中的每个后缀点，分别标号为$1..i$。
则求的东西就是
$$
\sum_{1 \le i < j \le n}{len[LCA(i,j)] \cdot len'[LCA'(i,j)] \cdot [len[LCA(i,j)] \le K2] \cdot [len'[LCA'(i,j)]\le K1]}
$$
目前为止看起来还是很烦，我们继续处理一下，将$parent$树看成一个有根有边权（可以负）的树，将每个点的$len$($len'$)视作是他到根的距离。然后将$S$的$parent$树中$len > K2$点的$len$置为0，同理将$S'$的$parent$树中$len > K1$点的$len'$置为0。**之后便可以认为是一棵有边权的树，根据$dep$来确定每条边的长度**。

则求的就是所有点对 **在两个数中的LCA的深度之积** 的和。即
$$
\sum_{1 \le i < j \le n}{dep[LCA(i,j)]\cdot dep'[LCA'(i,j)]}
$$

到这里就是边分的套路了，可以$O(nlogn)$或者$O(nlog^2n)$求解。
具体做法是：
先将某一个LCA化简掉，这里化简掉第一个LCA，即原式等价于
$$
\sum_{1 \le i < j \le n}{\frac{1}{2}\cdot (dep[i] + dep[j] - dis(i,j)) \cdot dep'[LCA'(i,j)]}
$$

先对第一棵树加一些点改造（为了保证边分治的正确复杂度），进行边分治。
在分治到某条边$<u,v>$，边权是w时，我们要求在第一棵树中，$dis$经过了$<u,v>$这条边的点对$(i,j)$对答案的贡献。设$u$这一侧的点集是$L$，$v$那一侧的点集是$R$。则原式继续等价于
$$
\frac{1}{2} \cdot\sum_{(i\in L,j\in R)}{(dep[i] + dep[j] - dis(i,u) - dis(j,v) - w) \cdot dep'[LCA'(i,j)]}
$$

观察到$dep$,$dis$都是定值，设$A[i]=\left\{\begin{array}{rcl}dep[i] - dis(i,u) & & {i \in L}\\dep[i] - dis(i,v) & & {i\in R}\end{array} \right.$则化简为
$$
\frac{1}{2} \cdot \sum_{i \in L, j \in R}{(A[i] + A[j] - w)\cdot dep'[LCA'(i,j)]}
$$

到这里成功的把第一棵树彻底扔掉了，于是这个东西很显然在第二棵树搞个虚树，做个01DP就行了。
第二棵树的LCA用RMQ去求,排序用基数排序就可以做到整体复杂度$O(nlogn)$。否则复杂度$O(nlog^2n)$。

这代码怎么这么长。。。

```cpp
// Created by calabash_boy on 2019/10/15.
// Luogu 5115.SAM + 边分 + 虚树DP: Given S, calculate
// \sum_{i<j and LCP(i,j)<=K1 and LCS(i,j)<=K2}{LCS(i,j) * LCP(i,j)}
// 最大度数有限制（例如parent树27度），则不需要三度化。
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
char s[maxn],t[maxn];int n,K1,K2;
struct Suffix_Automaton{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){add(*s-'a');s++;}
    }
    void add(int c){
        int p = last, np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    void extract(vector<int> * E,char *s,int n,int *id,int *dep,int K){
        int temp = 1;
        for (int i=0;i<n;i++){
            temp = nxt[temp][s[i] - 'a'];
            id[temp] = i + 1;
        }
        for (int i=2;i<=cnt;i++)E[fa[i]].push_back(i);
        for (int i=1;i<=cnt;i++){
            if (l[i] <= K)dep[i] = l[i];
            else dep[i] = 0;
        }
    }
}sam1,sam2;
vector<int> EE1[maxn * 2],E2[maxn*2];
vector<tuple<int,int,int> > E1[maxn*4];
int idd1[maxn * 2],id1[maxn*4];
int depp1[maxn * 2],dep1[maxn*4];
int id2[maxn* 2],dep2[maxn*2];
bool can_use[maxn*4];
int edge_cnt = 0;
int cnt, st[maxn * 2][20], depth[maxn * 2];
int pos2[maxn*2],pos1[maxn*4];
int dfs_clock,l[maxn*2],r[maxn*2];
void dfs2(int u,int fa){
    l[u] = ++dfs_clock;
    st[u][0] = fa;
    depth[u] = depth[fa] + 1;
    for (int i=1;i<20 && st[u][i-1];i++){
        st[u][i] = st[st[u][i-1]][i-1];
    }
    for (auto v : E2[u]){
        if (v == fa)continue;
        dfs2(v,u);
    }
    r[u] = dfs_clock;
}
int get_lca(int u,int v){
    if (depth[u] < depth[v])swap(u,v);
    for (int i=19;i>=0;i--){
        if (depth[st[u][i]] >= depth[v])u = st[u][i];
    }
    if (u == v)return u;
    for (int i=19;i>=0;i--){
        if (st[u][i] != st[v][i]){
            u = st[u][i];v = st[v][i];
        }
    }
    assert(st[u][0] == st[v][0]);
    return st[u][0];
}
//三度化
int dfs(int u,int fa){
    int now = ++cnt;
    id1[now] = idd1[u];dep1[now] = depp1[u];
    pos1[id1[now]] = now;
    int pre = now;
    for (auto v : EE1[u]){
        if (v == fa)continue;
        int temp = ++cnt;
        id1[temp] = 0;dep1[temp] = depp1[u];
        edge_cnt ++;
        E1[pre].push_back(make_tuple(temp,dep1[temp] - dep1[pre],edge_cnt));
        E1[temp].push_back(make_tuple(pre,dep1[temp] - dep1[pre],edge_cnt));
        int vid = dfs(v,u);
        edge_cnt ++;
        E1[temp].push_back(make_tuple(vid,dep1[vid] - dep1[temp],edge_cnt));
        E1[vid].push_back(make_tuple(temp,dep1[vid] - dep1[temp],edge_cnt));
        pre = temp;
    }
    return now;
}
long long ans = 0;
int sz[maxn*4];
int dis[maxn* 4];
void dfs_dis(int u,int fa,int len){
    dis[u] = len;
    for (auto e : E1[u]){
        int v,lll,edge_id;tie(v,lll,edge_id) = e;
        if (v == fa || !can_use[edge_id])continue;
        dfs_dis(v,u,len + lll);
    }
}
void dfs_sz(int u,int fa){
    sz[u] = 1;
    for (auto e : E1[u]){
        int v,len,edge_id;tie(v,len,edge_id) = e;
        if (v == fa || !can_use[edge_id])continue;
        dfs_sz(v,u);
        sz[u] += sz[v];
    }
}
void dfs_edge(int u,int fa,int &e_id,int &uu,int &vv,int &ww,int &max_sz,int tot_node){
    for (auto e : E1[u]){
        int v,len,edge_id;tie(v,len,edge_id) = e;
        if (v == fa || !can_use[edge_id])continue;
        int max_sz_t = max(sz[v],tot_node - sz[v]);
        if (max_sz_t < max_sz){
            max_sz = max_sz_t;
            uu = u;vv = v;ww = len;e_id = edge_id;
        }
        dfs_edge(v,u,e_id,uu,vv,ww,max_sz,tot_node);
    }
}
void dfs_node(int u,int fa,vector<int> &nodes){
    if (id1[u])nodes.push_back(id1[u]);
    for (auto e : E1[u]){
        int v,len,edge_id;tie(v,len,edge_id) = e;
        if (v == fa || !can_use[edge_id])continue;
        dfs_node(v,u,nodes);
    }
}
int color[maxn * 2];
int vis[maxn];
long long dp[maxn * 2];
long long dp_cnt[maxn*2][2];
long long dp_sum[maxn*2][2];
int stk[maxn*2];
int fa[maxn*2];
inline void clear(int x,int type){
    dp[x] = 0;vis[x] = type;
    for (int c = 0; c < 2;c ++)dp_cnt[x][c] = dp_sum[x][c] = 0;
}
void DP(vector<int> & nodes_,int ww){
    vector<int> nodes(0);
    for (int x : nodes_){
        nodes.push_back(pos2[x]);
    }
    for (int x : nodes)clear(x,1);
    sort(nodes.begin(),nodes.end(),[](int x,int y){
        return l[x] < l[y];
    });
    int SZ = nodes.size();
    for (int i=1;i<SZ;i ++){
        int temp = get_lca(nodes[i-1],nodes[i]);
        if (!vis[temp]){
            nodes.push_back(temp);
            clear(temp,2);
        }
    }
    if (!vis[1]){
        nodes.push_back(1);
        clear(1,2);
    }
    sort(nodes.begin(),nodes.end(),[](int x,int y){
        return l[x] < l[y];
    });
    int top = 1;
    stk[0] = nodes[0];
    for (int i=1;i<nodes.size();i++){
        while (l[nodes[i]] > r[stk[top-1]]) top --;
        fa[nodes[i]] = stk[top-1];
        stk[top++] = nodes[i];
    }
    long long anss = 0;
    for (int i= nodes.size() - 1;i >=0 ;i --){
        int u = nodes[i], c = vis[u] == 1? color[id2[u]] - 1: -1;
        if (c != -1){
            long long A = dep1[pos1[id2[u]]] - dis[pos1[id2[u]]];
            dp[u] += A * dp_cnt[u][!c] + dp_sum[u][!c];
            dp[u] -= dp_cnt[u][!c] * ww;
            dp_cnt[u][c] ++;
            dp_sum[u][c] += A;
        }
        long long temp_ans = dp[u] * dep2[u];
        assert(temp_ans %2 == 0);
        anss += temp_ans/2;
        dp[fa[u]] += dp_cnt[fa[u]][0] * dp_sum[u][1] + dp_cnt[u][0] * dp_sum[fa[u]][1];
        dp[fa[u]] += dp_cnt[fa[u]][1] * dp_sum[u][0] + dp_cnt[u][1] * dp_sum[fa[u]][0];
        dp[fa[u]] -= (dp_cnt[fa[u]][1] * dp_cnt[u][0] + dp_cnt[fa[u]][0] * dp_cnt[u][1]) * ww;
        for (int c = 0;c < 2;c ++){
            dp_cnt[fa[u]][c] += dp_cnt[u][c];
            dp_sum[fa[u]][c] += dp_sum[u][c];
        }
    }
    ans += anss;
    for (int x : nodes)vis[x] = 0;
}
void calc(int uu,int vv,int ww){
    vector<int> L(0),R(0),nodes(0);
    dfs_node(uu,0,L);dfs_node(vv,0,R);
    for (int x : L){color[x] = 1;nodes.push_back(x);}
    for (int x : R){color[x] = 2;nodes.push_back(x);}
    DP(nodes,ww);
}
void dfs(int root){
    dfs_sz(root,0);
    int tot_node = sz[root];
    if (tot_node == 1)return;
    int edge_id,uu,vv,ww,max_sz = tot_node + 1;
    dfs_edge(root,0,edge_id,uu,vv,ww,max_sz,tot_node);
    can_use[edge_id] = false;
    dfs_dis(uu,0,0);dfs_dis(vv,0,0);
    calc(uu,vv,ww);dfs(uu);dfs(vv);
}
int main(){
    scanf("%s%d%d",s,&K1,&K2);
    n = strlen(s);
    memcpy(t,s,sizeof s);reverse(t,t + n);
    sam1.init(s);sam2.init(t);
    sam1.extract(EE1,s,n,idd1,depp1,K2);
    sam2.extract(E2,t,n,id2,dep2,K1);
    for (int i=1;i<= sam2.cnt; i ++){
        if (id2[i]){
            id2[i] = n + 1 - id2[i];
            pos2[id2[i]] = i;
        }
    }
    int root1 = dfs(1,0);int root2 = 1;
    dfs2(root2,0);
    memset(can_use,true,sizeof can_use);
    dfs(root1);
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：szh_AK_all (赞：1)

[摘自本文](https://www.luogu.com.cn/article/7d7bk882)。

### P5115 Check,Check,Check one two!

记 $f_x=\sum_{l=1}^{k_1} \sum_{r=1}^{k_2}[l+r-1=x]\times l\times r$，则我们要求的式子可以转化成 $\sum_{i=1}^n \sum_{j=i+1}^n [s_{i-1}\ne s_{j-1}]\times f_{lcp(rk_i,rk_j)}$，转而枚举 lcp，即 $\sum_{i=1}^n f_i\times \sum_{i=1}^n \sum_{j=i+1}^n [lcp(rk_i,rk_j)=k]\times [s_{i-1}\ne s_{j-1}]$，也就是 $\sum_{i=1}^n f_i\times \sum_{i=1}^n \sum_{j=i+1}^n[lcp(i,j)=k]\times [s_{sa_i-1}\ne s_{sa_j-1}]$。

那么可以考虑枚举每个 lcp 计算其对答案的贡献。

我们仍然可以对 height 数组建出笛卡尔树，对于当前点 $x$，从它的左右区间所涵盖的后缀范围内各任选一个后缀，则他们的 lcp 为 $h_x$。但是我们从左右子树选出节点 $i,j$ 后，还需满足 $s_{sa_i-1}\ne s_{sa_j-1}$，显然某个 $s_k$ 只有 $26$ 种取值，于是可以设 $g_{i,j}$ 表示在节点 $i$ 的子树中满足 $sa_{sa_y-1}=j$ 的 $y$ 的个数。转移有 $g_{x,i}=g_{lson,i}+g_{rson,i}$，对答案的贡献为 $\sum_{i\ne j} g_{lson,i}\times g_{rson,j}$，这个是好算的。

考虑计算 $f_x$。

$f_x=\sum_{l=1}^{k_1} \sum_{r=1}^{k_2}[l+r-1=x]=\sum_{l=1}^{k_1} [x-l+1\le k_2]\times l\times (x-l+1)$，于是对于每个 $x$，我们可以确定 $l$ 的范围，也就是 $\sum_{l=x+1-k_2}^{k_1} l\times (x-l+1)$，这个可以转换成前缀和的形式，也就是我们要算出 $\sum_{l=1}^y l\times (x-l+1)$，很显然 $\sum_{l=1}^y l\times (x-l+1)=\sum_{l=1}^y l\times (x+1)-\sum_{l=1}^y l^2=(x+1)\times \frac{l\times (l+1)}{2}-\frac{l\times(l+1)\times(2\times l+1)}{6}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
const int N = 100005;
int a[N], b[N], sa[N], h[N], rk[N], t[N], q[N];
string s;
int n, m;

void getsa() {
	memset(t, 0, sizeof(t));
	memset(sa, 0, sizeof(sa));
	for (int i = 1; i <= n; i++) {
		a[i] = s[i];
		++t[a[i]];
	}
	for (int i = 2; i <= 128; i++)
		t[i] += t[i - 1];
	for (int i = n; i >= 1; i--)
		sa[t[a[i]]--] = i;
	int now = 128;
	for (int k = 1; k <= n; k *= 2) {
		int cnt = 0;
		for (int i = n - k + 1; i <= n; i++)
			b[++cnt] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k)
				b[++cnt] = sa[i] - k;
		memset(t, 0, sizeof(t));
		for (int i = 1; i <= n; i++)
			t[a[i]]++;
		for (int i = 2; i <= now; i++)
			t[i] += t[i - 1];
		for (int i = n; i >= 1; i--)
			sa[t[a[b[i]]]--] = b[i], b[i] = 0;
		swap(a, b);
		int tot = 1;
		a[sa[1]] = 1;
		for (int i = 2; i <= n; i++) {
			if (b[sa[i]] == b[sa[i - 1]] && b[sa[i] + k] == b[sa[i - 1] + k])
				a[sa[i]] = tot;
			else
				a[sa[i]] = ++tot;
		}
		if (tot == n)
			break;
		now = tot;
	}
}

void gethi() {
	memset(rk, 0, sizeof(rk));
	memset(h, 0, sizeof(h));
	for (int i = 1; i <= n; i++)
		rk[sa[i]] = i;
	int now = 0;
	for (int i = 1; i <= n; i++) {
		if (rk[i] == 1)
			continue;
		if (now)
			now--;
		int j = sa[rk[i] - 1];
		while (i + now <= n && j + now <= n && s[i + now] == s[j + now])
			now++;
		h[rk[i]] = now;
	}
	for (int i = 1; i <= n; i++)
		h[i] = h[i + 1];
}
ull cnt[N];

struct node {
	int l, r, hi;
	ull f[30];
	int ql, qr;
} p[N];

void bu(int d, int l, int r) {
	if (!d)
		return;
	p[d].ql = l, p[d].qr = r;
	bu(p[d].l, l, d);
	bu(p[d].r, d + 1, r);
}
int qq[N];

void dikaer() {
	int top = 0;
	h[n] = -1;
	for (int i = 1; i <= n; i++) {
		int now = 0;
		while (top && h[i] <= h[qq[top]]) {
			p[qq[top]].r = now;
			now = qq[top];
			top--;
		}
		p[i].l = now;
		qq[++top] = i;
	}
}

void dfs(int x) {
	if (p[x].l)
		dfs(p[x].l);
	if (p[x].r)
		dfs(p[x].r);
	node zuo, you;
	if (!p[x].l) {
		zuo.ql = zuo.qr = p[x].ql;
		for (int i = 0; i <= 28; i++)
			zuo.f[i] = 0;
		zuo.f[s[sa[p[x].ql] - 1] - 'a' + 1] = 1;
	} else
		zuo = p[p[x].l];
	if (!p[x].r) {
		you.ql = you.qr = p[x].qr;
		for (int i = 0; i <= 28; i++)
			you.f[i] = 0;
		you.f[s[sa[p[x].qr] - 1] - 'a' + 1] = 1;
	} else
		you = p[p[x].r];
	ull ans = 0;
	for (int i = 0; i <= 28; i++)
		ans += zuo.f[i];
	ull tmp = 0;
	for (int i = 0; i <= 28; i++)
		tmp += you.f[i];
	ull da = 0;
	for (int i = 0; i <= 28; i++)
		da += zuo.f[i] * you.f[i];
	cnt[h[x]] += ans * tmp - da;
	for (int i = 0; i <= 28; i++)
		p[x].f[i] = zuo.f[i] + you.f[i];
}

int Sum(int l, int i) {
	if (l <= 0)
		return 0;
	int ans = (i + 1) * (1 + l) * l / 2;
	int tmp = l * (l + 1) * (2 * l + 1) / 6;
	ans -= tmp;
	return ans;
}
int k1, k2;

void work() {
	dfs(p[n].l);
	ull ans = 0;
	for (int i = 1; i <= n; i++) {
		int k = 0;
		if (k1 + k2 >= i)
			k = Sum(min(k1, i),  i) - Sum(i + 1 - k2 - 1, i);
		ans += 1uLL * k * cnt[i];
	}
	cout << ans;
}

signed main() {
	cin >> s >> k1 >> k2;
	n = s.size();
	s = " " + s;
	s[0] = 'a' - 1;
	getsa();
	gethi();
	dikaer();
	bu(p[n].l, 1, n);
	work();
}
```

---

## 作者：Richard_Whr (赞：1)

给出一种纯数据结构做法：

注意到这个 $ \operatorname{Lcp}(i,j) \le k$ 不好，我们知道的是 $\operatorname{Lcp}(i,j) \ge k$ 的部分形成若干个不交的区间。

进一步的，在 SA 的克鲁斯卡尔重构树上，形成若干个不交的子树。

我们可以用不带限制的减去 $>k$ 的部分即可，这部分是区间，较为好算。

对于 Lcs 同理，发现变成了两颗树间点对问题。

套用暴力写挂的做法：在第一颗树上边分治，抠出第二颗树的虚树做 01dp。

套用的条件是：第一棵树上用距离刻画，第二棵树上用 LCA 刻画，三度化。

发现重构树本来就是按 LCA 刻画的，因为两点的 LCP 等于两者 LCA 的点权。

如何用距离刻画呢？先把点权做差分，套用“暴力写挂”的做法：$d_{\operatorname{Lca}}(u,v)=\frac{d_u+d_v-dis(u,v)}{2}$。

最后还差一个三度化，注意到重构树本来就是二叉树，不用管了。

然后做完了。

点分更好写，我写的点分。

5.5k 你根本不需要实现。

一点细节是最后求的是 $ans \times 2$ 的值，除二不好搞，先用 __int128 存着。

复杂度 $O(n log n)$，一个是点分治，一个是虚树的排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,M=20;
typedef pair<int,int> PII;
typedef unsigned long long ULL;
const ULL Mod=(1<<32)-1;
typedef __int128 Int;
int n,m,k1,k2;
char str[N];
bool st[N];
Int res;
struct Tree
{
	vector<PII> e[N];
	int dfn[N],sz[N],seq[N],ts,fa[N];
	int d[N];
	int Min[N][M];
	void dfs(int u,int p)
	{
		dfn[u]=++ts,sz[u]=1,seq[ts]=u;
		Min[ts][0]=fa[u]=p;
		for(auto [v,w]:e[u])
		{
			if(v==p) continue;
			d[v]=d[u]+w;
			dfs(v,u);
			sz[u]+=sz[v];
		}
	}
	int get(int x,int y){return dfn[x]<dfn[y]?x:y;}
	void init()
	{
		dfs(m,0);
		for(int j=1;j<M;j++)
			for(int i=1;i+(1<<j)-1<=m;i++)
				Min[i][j]=get(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);
	}
	int lca(int x,int y)
	{
		if(x==y) return x;
		if(dfn[x]>dfn[y]) swap(x,y);
		x=dfn[x]+1,y=dfn[y];
		int j=log2(y-x+1);
		return get(Min[x][j],Min[y-(1<<j)+1][j]);
	}
}T[2];
struct SA
{
	struct E
	{
		int a,b,c;
		bool operator<(const E &B)const{return c>B.c;}
	};
	vector<E> vec;
	char s[N];
	int y[N],c[N],x[N];
	int sa[N],rk[N],height[N];
	int val[N];
	int p[N];
	int find(int x)
	{
		if(p[x]!=x) return p[x]=find(p[x]);
		return p[x];
	} 
	void add(int t,int a,int b,int c)
	{
		T[t].e[a].push_back({b,c});
		T[t].e[b].push_back({a,c});
	}
	void build_T(int t)
	{
		for(int i=1;i<=n*2;i++) p[i]=i;
		sort(vec.begin(),vec.end());
		int tot=n;
		for(int i=1;i<=n;i++) val[i]=n-i+1;
		for(auto E:vec)
		{
			int a=E.a,b=E.b,c=E.c;
			a=find(a),b=find(b);
			val[++tot]=c;
			add(t,tot,a,val[a]-val[tot]);
			add(t,tot,b,val[b]-val[tot]);
			p[a]=tot,p[b]=tot;
		}
		T[t].d[tot]=val[tot];
	}

	void init(int t)
	{
		memcpy(s,str,sizeof str);
		int m=122;
	    for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	    for(int i=1;i<=m;i++) c[i]+=c[i-1];
	    for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	    
	    for(int k=1;k<=n;k<<=1)
	    {
	        int num=0;
	        for(int i=n-k+1;i<=n;i++) y[++num]=i;
	        for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
	        for(int i=1;i<=m;i++) c[i]=0;
	        for(int i=1;i<=n;i++) c[x[y[i]]]++;
	        for(int i=1;i<=m;i++) c[i]+=c[i-1];
	        for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
	        swap(x,y);
	        x[sa[1]]=num=1;
	        for(int i=2;i<=n;i++) 
	            x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
	        m=num;
	        if(m==n) break;
	    }
		for(int i=1;i<=n;i++) rk[sa[i]]=i;
		for(int i=1,k=0;i<=n;i++)
		{
		    if(rk[i]==1) continue;
		    int j=sa[rk[i]-1];
		    if(k) k--;
		    while(i+k<=n && j+k<=n && s[i+k]==s[j+k]) k++;
		    height[rk[i]]=k;
		    vec.push_back({i,j,k});
		}
		
		build_T(t);
	}
}Ds[2];
Int g[N],s[N][2],c[N][2];
vector<int> vc[3];
vector<int> E[N];

int get_sz(int u,int fa)
{
	if(st[u]) return 0;
	int sz=1;
	for(auto [v,w]:T[0].e[u])
	{
		if(v==fa) continue;
		sz+=get_sz(v,u);
	}
	return sz;
}

int get_wc(int u,int fa,int tot,int &wc)
{
	if(st[u]) return 0;
	int sz=1,mx=0;
	for(auto [v,w]:T[0].e[u])
	{
		if(v==fa) continue;
		int t=get_wc(v,u,tot,wc);
		mx=max(mx,t),sz+=t;
	}
	mx=max(mx,tot-sz);
	if(mx*2<=tot) wc=u;
	return sz;
}

void get_dist(int u,int fa,int dis,int k)
{
	if(st[u]) return;
	if(u<=n) g[u]=T[0].d[u]-dis,vc[k].push_back(u);
	for(auto [v,w]:T[0].e[u]) if(v!=fa) get_dist(v,u,dis+w,k);
}

bool cmp(int x,int y){return T[1].dfn[x]<T[1].dfn[y];}

int VT(vector<int> &vec)
{
	vector<int> Ver;
	sort(vec.begin(),vec.end(),cmp);
	for(int i=1;i<vec.size();i++)
	{
		int x=vec[i-1],y=vec[i];
		Ver.push_back(x),Ver.push_back(T[1].lca(x,y));
	}
	Ver.push_back(vec.back());
	sort(Ver.begin(),Ver.end(),cmp);
	Ver.erase(unique(Ver.begin(),Ver.end()),Ver.end());
	vec=Ver;
	for(int i=1;i<vec.size();i++)
	{
		int x=vec[i-1],y=vec[i],p=T[1].lca(x,y);
		E[p].push_back(y);
	}
	return vec[0];
}

Int Dp(int u)
{
	Int sum=0,val=T[1].d[u];
	for(auto v:E[u])
	{
		sum+=Dp(v);
		if(val<=k2) for(int x=0;x<2;x++) sum+=(Int)s[u][x]*c[v][x^1]*val+s[v][x]*c[u][x^1]*val;
		for(int x=0;x<2;x++) s[u][x]+=s[v][x],c[u][x]+=c[v][x];
	}
	return sum;
}

Int calc(int i,int j)
{
	if(!vc[i].size() || !vc[j].size()) return 0;
	vector<int> vec;
	for(auto u:vc[i]) 
	{
		int v=n-u+1;
		s[v][0]=g[u],s[v][1]=0,vec.push_back(v);
		c[v][0]=1,c[v][1]=0;
	}
	for(auto u:vc[j]) 
	{
		int v=n-u+1;
		s[v][1]=g[u],s[v][0]=0,vec.push_back(v);
		c[v][1]=1,c[v][0]=0;
	}
	int rt=VT(vec);
	Int res=Dp(rt);
	for(auto u:vec) s[u][0]=s[u][1]=c[u][0]=c[u][1]=0,E[u].clear();
	return res;
}

Int calc(int u)
{
	get_wc(u,-1,get_sz(u,-1),u);
	if(st[u]) return 0;
	int k=0;
	for(auto [v,w]:T[0].e[u])
	{
		get_dist(v,u,w,k++);
	}	
	Int sum=0;
	for(int i=0;i<k;i++)
		for(int j=i+1;j<k;j++)
			sum+=calc(i,j);
	for(int i=0;i<k;i++) vc[i].clear();
	st[u]=true;
	for(auto [v,w]:T[0].e[u]) sum+=calc(v);
	return sum;
}

void Dfs(int u,int p)
{
	if(T[0].d[u]>k1) 
	{
		for(int i=T[0].dfn[u];i<T[0].dfn[u]+T[0].sz[u];i++) st[T[0].seq[i]]=false;
		res-=calc(u);
		return;
	}
	for(auto [v,w]:T[0].e[u]) if(v!=p) Dfs(v,u);
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	
	cin>>(str+1);
	cin>>k1>>k2;
	n=strlen(str+1);
	Ds[0].init(0);
	reverse(str+1,str+1+n);
	Ds[1].init(1);
	m=n*2-1;
	T[0].init(),T[1].init();
	
	res=calc(m);
	Dfs(m,0);
	ULL ans=(res>>1)&Mod;
	cout<<ans<<"\n";
	
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

来个字符串重工业做法。

首先对正串反串分别建 SAM，然后两个下标的 LCP 和 LCS 长度就对应着它们在两棵树上对应结点的 LCA 代表的串长。

首先思考第二棵树。对于这种贡献为 $len_{LCA}[len_{LCA}\le k_1]$ 的计算，一种常见方式就是拆分两个点的作用，变成链加和链查。

我们设 $val_i=len_i[len_i\le k_1]-len_{fa_i}[len_{fa_i}\le k_1]$，这个贡献类似于差分，两个点到根结点的链的重合部分权值之和就是答案。

这个链加和链查跟平常的维护不太一样，一次加法操作相当于这个结点加上它对应的权值，用树剖 + 线段树可以方便维护。

接下来考虑第一棵树。枚举 LCA，那么两个端点分别就在两棵不同的子树内。考虑用 dsu on tree 优化它，先将重儿子的子树提前做好链加，剩下的子树就可以暴力做链加链查操作了。

总时间复杂度 $O(n\log^3 n)$，过不去。考虑优化，发现树剖 + 线段树这个操作就有两个 $\log$，需要一个更加优秀的数据结构来维护。

这个数据结构就是 **全局平衡二叉树**。

对于全局平衡二叉树的每个结点维护五个值 $(a,s_a,b,s_b,tag)$。$a,s_a$ 相当于结点的 $val$ 和子树的 $val$ 之和。$b,s_b$ 相当于这个结点的贡献和整个子树的贡献之和。$tag$ 则需要记录这个结点需要的加法操作次数。

每次修改时，如果上一个点为当前点的右儿子 / 轻儿子，或者没有上一个点，就修改当前点和它的右子树。查询时先将祖先链的所有标记下传再进行求和。

时间复杂度 $O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5+5;

int n,m,rt,k1,k2; ull ans; char str[Maxn+5];

struct SegTree
{
    ull t[Maxn+5],val[Maxn+5],sum[Maxn+5],num[Maxn+5]; int tag[Maxn+5];
    int anc[Maxn+5],ch[Maxn+5][2],st[Maxn+5],top;
    #define ls(x) ch[x][0]
    #define rs(x) ch[x][1]
    inline void push_up(int p) {t[p]=t[ls(p)]+val[p]+t[rs(p)];}
    inline void f(int p,int k) {if(p) val[p]+=k*num[p],t[p]+=k*sum[p],tag[p]+=k;}
    inline void push_down(int p) {if(ls(p)) f(ls(p),tag[p]); if(rs(p)) f(rs(p),tag[p]); tag[p]=0;}
    inline int isRoot(int x) {return (x!=ls(anc[x]) && x!=rs(anc[x]));}
    inline void Update(int x,int k)
    {
        top=0; for(int i=x;i;i=anc[i]) st[++top]=i;
        Rof(i,top,1) push_down(st[i]);
        for(int i=x,p=0;i;p=i,i=anc[i])
        {
            if(isRoot(p)) p=0;
            if(!p || p==rs(i))
            {
                val[i]+=k*num[i],t[i]+=k*num[i];
                if(ls(i)) f(ls(i),k);
            }
            push_up(i);
        }
    }
    inline ull Count(int x)
    {
        ull res=0;
        top=0; for(int i=x;i;i=anc[i]) st[++top]=i;
        Rof(i,top,1) push_down(st[i]);
        for(int i=x,p=0;i;p=i,i=anc[i])
        {
            if(isRoot(p)) p=0;
            if(!p || p==rs(i)) res+=val[i]+t[ls(i)];
        }
        return res;
    }
} T;

inline void Update(int x,int op);
inline ull Query(int x);

struct SAM
{
    int lst,tot,k,fa[Maxn+5],pos[Maxn+5],idx[Maxn+5]; ull val[Maxn+5];
    int len[Maxn+5],dep[Maxn+5],t[Maxn+5][26],chk[Maxn+5];
    int siz[Maxn+5],son[Maxn+5],top[Maxn+5],st[Maxn+5],cur;
    vector<int> v[Maxn+5];
    inline SAM() {lst=tot=1;}
    inline void Insert(int x,int id)
    {
        int p=lst,k=++tot;
        len[k]=len[p]+1,pos[id]=k,idx[k]=id,lst=k;
        while(p && !t[p][x]) t[p][x]=k,p=fa[p];
        if(!p) fa[k]=1;
        else
        {
            int q=t[p][x];
            if(len[q]==len[p]+1) fa[k]=q;
            else
            {
                fa[++tot]=fa[q],memcpy(t[tot],t[q],sizeof(t[q]));
                len[tot]=len[p]+1,fa[k]=fa[q]=tot;
                while(p && t[p][x]==q) t[p][x]=tot,p=fa[p];
            }
        }
    }
    inline void dfs(int x)
    {
        chk[x]=(len[x]<=k),dep[x]=dep[fa[x]]+1,siz[x]=1;
        if(chk[x]) val[x]=len[x]-len[fa[x]];
        else if(chk[fa[x]]) val[x]=0ull-len[fa[x]];
        for(auto y:v[x])
        {
            dfs(y),siz[x]+=siz[y];
            son[x]=(siz[y]>siz[son[x]]?y:son[x]);
        }
    }
    inline void Count(int x,ull val)
    {
        if(!val) return;
        if(idx[x]) ans+=val*Query(idx[x]);
        for(auto y:v[x]) Count(y,val);
    }
    inline void Add(int x,int op)
    {
        if(idx[x]) Update(idx[x],op);
        for(auto y:v[x]) Add(y,op);
    }
    inline void dfs1(int x,int op)
    {
        for(auto y:v[x]) if(y!=son[x]) dfs1(y,0);
        if(son[x]) dfs1(son[x],1);
        for(auto y:v[x]) if(y!=son[x]) Count(y,len[x]*chk[x]),Add(y,1);
        if(idx[x])
        {
            if(chk[x]) ans+=1ull*Query(idx[x])*len[x];
            Update(idx[x],1);
        }
        if(!op) Add(x,-1);
    }
    inline void dfs2(int x,int t)
    {
        top[x]=t;
        if(son[x]) dfs2(son[x],t);
        for(auto y:v[x]) if(y!=son[x]) dfs2(y,y);
    }
    inline int BuildChain(int l,int r)
    {
        if(l>r) return 0;
        int sum=0,now=0;
        For(i,l,r) sum+=(siz[st[i]]-siz[son[st[i]]]);
        For(i,l,r)
        {
            now+=(siz[st[i]]-siz[son[st[i]]]);
            if(now*2>=sum)
            {
                int x=st[i]; T.num[x]=val[x];
                T.ch[x][0]=BuildChain(l,i-1),T.ch[x][1]=BuildChain(i+1,r);
                T.anc[T.ch[x][0]]=T.anc[T.ch[x][1]]=x;
                T.sum[x]=val[x]+T.sum[T.ch[x][0]]+T.sum[T.ch[x][1]];
                T.push_up(x); return x;
            }
        }
        return 0;
    }
    inline int BuildTree(int x)
    {
        for(int i=x;i;i=son[i]) for(auto y:v[i])
            if(y!=fa[i] && y!=son[i]) T.anc[BuildTree(y)]=i;
        cur=0; for(int i=x;i;i=son[i]) st[++cur]=i,top[i]=x;
        return BuildChain(1,cur);
    }
    inline void Build()
    {
        For(i,2,tot) v[fa[i]].push_back(i);
        dfs(1),dfs2(1,1);
    }
} S1,S2;

inline void Update(int x,int op) {x=S2.pos[x]; T.Update(x,op);}
inline ull Query(int x) {x=S2.pos[x]; return T.Count(x);}

int main()
{
    scanf("%s%d%d",str+1,&k2,&k1),n=strlen(str+1);
    For(i,1,n) S1.Insert(str[i]-'a',i),S2.Insert(str[n-i+1]-'a',n-i+1);
    S1.k=k1,S2.k=k2,S1.Build(),S2.Build();
    rt=S2.BuildTree(1),S1.dfs1(1,0);
    printf("%llu\n",ans);
    return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

首先我们对 $S$ 正反建一个 SAM，那么：
- $\operatorname{lcp}(i,j)$ 的意义就是 $i,j$ 代表的节点在反串上 LCA 的 $len$；
- $\operatorname{lcs}(i,j)$ 的意义就是 $i,j$ 代表的节点在正串上 LCA 的 $len$。

我们考虑把后面那个长度限制压进去，也就是如果一个节点长度 $>k_i$ 就让其为 $0$。原问题相当于两棵树 $T_1,T_2$（树的大小**大于等于** $n$），每个节点有一个权值 $v_{i,u}$。求：

$$\sum_{1\leq i<j\leq n} v_{1,\text{LCA}_1(i,j)}\times v_{2,\text{LCA}_2(i,j)}$$

首先枚举 $u=\text{LCA}_1(i,j)$，那么相当于给若干点集，求不同点集的点 $i,j$ 中 $v_{2,\text{LCA}_2(i,j)}$ 的和。根据 LCA 的套路我们拆成到 $1$ 的路径加，查询到 $1$ 的路径和。使用树剖加上树上启发式合并可以做到 $\mathcal O(n\log^3 n)$。线段树一脸过不去。

我们再琢磨一下我们线段树需要维护什么，我们需要维护一个初始为 $0$ 的序列 $x_{1,2,\dots,n}$ 还有一些给定的初值 $a_i$，每次会：

- 给区间加 $d\times a_i$。
- 问区间和。

我们通过差分把两种询问都转成前缀和，你会发现这种东西很可树状数组，我们换上树状数组就过了。跑得挺快的。就是码力惊人！

时间复杂度：$\mathcal O(n\log^3 n)$。瓶颈处是 BIT，树剖，常数很小。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN=1e5+5;
bool Mbe;
int n,t,k1,k2,tot;string s;ll ans=0;
ll p[MAXN<<1];
int fa[MAXN<<1],in[MAXN<<1],top[MAXN<<1],siz[MAXN<<1],mson[MAXN<<1];
vector<int> son[MAXN<<1];
struct SAM{ 
int nxt[MAXN<<1][26],fail[MAXN<<1],len[MAXN<<1],ed[MAXN<<1],rep[MAXN<<1];
vector<int> son[MAXN<<1];
int lst=1,tot=1;
void insert(int ch,int t){
	int cur=++tot,p=lst;
	len[cur]=len[lst]+1;ed[t]=cur,rep[cur]=t;
	while(p&&!nxt[p][ch]) nxt[p][ch]=cur,p=fail[p];
	int q=nxt[p][ch];
	if(!p) fail[cur]=1;
	else if(len[q]==len[p]+1) fail[cur]=q;
	else{
		int cl=++tot;
		memcpy(nxt[cl],nxt[q],sizeof(nxt[q]));
		fail[cl]=fail[q];len[cl]=len[p]+1;
		while(p&&nxt[p][ch]==q) nxt[p][ch]=cl,p=fail[p];
		fail[cur]=fail[q]=cl;
	}
	lst=cur;
	return;
}
void build(){
	for(int i=2;i<=tot;i++) son[fail[i]].push_back(i);
}
}pre,suf; 
struct BIT{// 维护区间 xi += d*pi，求区间和 
ll a[MAXN<<1];
void add(int x,ll d){while(x<=t){a[x]+=d;x+=(x&-x);}}
ll ask(ll x){ll r=0;while(x){r+=a[x];x-=(x&-x);}return r;} 
}T1,T2;
bool Med;
void Add(int l,int r,ll d){
	if(l>1){
		T1.add(l-1,-d*p[l-1]);
		T2.add(l-1,-d);
	} 
	T1.add(r,d*p[r]);
	T2.add(r,d);
}
ll Ask(int l,int r){
	return (T1.ask(r)+p[r]*(T2.ask(t)-T2.ask(r)))-
	(T1.ask(l-1)+p[l-1]*(T2.ask(t)-T2.ask(l-1)));
}
void dfs(int u){
	siz[u]=1;fa[u]=suf.fail[u];
	for(int v:suf.son[u]){
		dfs(v);
		if(siz[v]>siz[mson[u]]) mson[u]=v;
		siz[u]+=siz[v];
	}
	return;
}
void dfs1(int u){
	in[u]=++tot;p[tot]=(suf.len[u]-suf.len[fa[u]]);
	if(mson[u]){
		top[mson[u]]=top[u];dfs1(mson[u]);
	}
	for(int v:suf.son[u]) if(v!=mson[u]){
		top[v]=v;dfs1(v);
	}
} 
void add(int u,int d){// 单点加 
//	cout<<"Add "<<u<<' '<<d<<endl;
	while(u){
		Add(in[top[u]],in[u],d);
		u=fa[top[u]];
	}
}
ll ask(int u){// 单点查 
//	cout<<"Ask "<<u<<endl;
	ll r=0;
	while(u){
		r+=Ask(in[top[u]],in[u]);
		u=fa[top[u]];
	} 
//	cout<<"Get "<<r<<endl;
	return r;
}
void get_sz(int u){
	siz[u]=1;
	for(int v:son[u]){
		get_sz(v);
		siz[u]+=siz[v];
		if(siz[v]>siz[mson[u]]) mson[u]=v;
	}
}
void sol(int u,ll d){
	if(pre.rep[u]) add(suf.ed[pre.rep[u]],d);
	for(int v:son[u]) sol(v,d);
}
void cal(int u,ll d){
	if(pre.rep[u]) ans+=ask(suf.ed[pre.rep[u]])*d;
	for(int v:son[u]) cal(v,d);
}
void dfs2(int u){
//	cout<<"DFS at "<<u<<' '<<pre.rep[u]<<endl;
	siz[u]=1;
	for(int v:son[u]) if(v!=mson[u]){
		dfs2(v);sol(v,-1);
	}
	if(mson[u]) dfs2(mson[u]);
//	cout<<"DFS At "<<u<<' '<<ans<<endl;
	if(pre.rep[u]){
		ans+=ask(suf.ed[pre.rep[u]])*pre.len[u];
		add(suf.ed[pre.rep[u]],1);
	}
	for(int v:son[u]) if(v!=mson[u]){
		cal(v,pre.len[u]);sol(v,1);
	}
//	cout<<"End At "<<ans<<endl;
	return;
}
int main(){
	ios::sync_with_stdio(false);
//	freopen("jellyfish.in","r",stdin);
	cerr<<"Memory: "<<(&Mbe-&Med)*1.0/1024/1024<<endl; 
	cin>>s>>k1>>k2;n=s.length();s=" "+s;
	for(int i=1;i<=n;i++) suf.insert(s[i]-'a',i);
	for(int i=n;i>=1;i--) pre.insert(s[i]-'a',i);
	suf.build(),pre.build();
	for(int i=1;i<=suf.tot;i++) if(suf.len[i]>k2) suf.len[i]=0;
	for(int i=1;i<=pre.tot;i++) if(pre.len[i]>k1) pre.len[i]=0;
	t=suf.tot;
	for(int i=1;i<=pre.tot;i++) son[i]=pre.son[i];
	dfs(1);top[1]=1;dfs1(1);// 对 suf 进行树剖 
//	for(int i=1;i<=n;i++) cout<<pre.ed[i]<<' '<<suf.ed[i]<<endl;//cout<<endl; 
//	for(int i=1;i<=suf.tot;i++) cout<<suf.fail[i]<<' ';cout<<endl;
	for(int i=1;i<=t;i++) p[i]+=p[i-1];
	memset(siz,0,sizeof(siz));memset(mson,0,sizeof(mson));
	get_sz(1);dfs2(1);
	cout<<ans<<endl;
}
```

---

