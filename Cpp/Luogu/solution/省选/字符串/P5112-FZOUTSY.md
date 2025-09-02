# FZOUTSY

## 题目描述

### 原始题意

cdm1020 是一名废宅，他平时最喜欢的事情就是水（复）群（读）。

他截取了他最近水的群的聊天记录，并且通过某种奥妙重重的压缩算法将这些聊天记录压缩成了一个长度为 $n$ 的字符串，因为他是一个中二社厨，所以这个字符串当中仅仅含有 $\mathtt{f,z,o,u,t,s,y}$ 这 $7$ 种字符，出于对后缀数据结构的狂热，他只对这个字符串的后缀感兴趣，他定义一个后缀的编号为 $i$，当且仅当它代表的字符串的区间为 $[i,n]$。

cdm1020 定义一对后缀 $(i,j)$ 是"$k$级复读的"当且仅当 $i$ 和 $j$ 的最长公共前缀的长度大于等于 $k$，换句话说一对$k$级复读的后缀也是 $k-1,k-2,k-3,\cdots,1,0$ 级复读的。

现在他想问你对于编号在 $(l,r)$ 中的后缀，有多少对后缀是 $k$ 级复读的。

### 一句话题意

给定一个长度为 $n$ 并且字符集为 $\mathtt{f,z,o,u,t,s,y}$ 的字符串和一个询问参数 $k$，多组询问 $(l,r)$ 求编号在 $(l,r)$ 间的后缀中，有多少对后缀的 LCP（最长公共前缀）长度大于等于 $k$。

定义一个后缀的编号为 $i$ 当且仅当这个后缀代表的是 $(i,n)$ 这段区间的字符。

## 说明/提示

### 数据范围及约定

对于全部数据，$1\leq l\leq r\leq n \leq 3×10^6$，$1\leq k \leq n \leq 3×10^6$，$1\leq m \leq 10^5$，$1 \leq n^2m \leq 10^{15}$。

保证输入的字符串中仅含 $\mathtt{f,z,o,u,t,s,y}$ 这 $7$ 种小写字母。

## 样例 #1

### 输入

```
20 15 3
oouuoouuoouuoouuoouu
10 16
2 15
4 13
6 7
4 12
12 14
12 13
7 19
1 5
6 13
1 15
9 15
11 15
1 19
15 18```

### 输出

```
3
18
8
0
6
0
0
12
1
4
21
3
1
32
0```

# 题解

## 作者：mrsrz (赞：3)

显然只要考虑以每个位置开头的$k$个字符就可以了。

现在就要把每个位置$i$按照其之后的$k$个字符分类。

不难想到一个好写、方便且效率高的算法：哈希。

我们对每个位置$i$开始的连续$k$个字符的哈希值处理出来（可以通过每个位置的后缀哈希值处理出来，处理后缀哈希值显然$O(n)$扫一遍即可），然后用map对其进行离散。

接下来的问题就是：给定一个序列$a_i$，每次询问一个区间内有多少对数相等。

~~小Z的袜子~~

莫队一下即可。

等等复杂度不对啊，$O(n\sqrt n)$的啊！

~~没错$O(n\sqrt n)$就是能跑3e6~~

正确的做法是把块长设为$\frac n {\sqrt m}$，此时时间复杂度为$O(n\sqrt m)$，由于条件$n^2m\leqslant 10^{15}$，所以是正确的。

~~然鹅块长$\sqrt n$确实过了，应该是出题人没卡~~

---

注意事项：

由于字符集比较小，字符比较多，取模的单哈希容易被卡（我就被卡了好几次），双哈希会TLE。但是出题人貌似没有特意卡哈希，所以自然溢出就过了。

## Code：
```cpp
#include<cstdio>
#include<cctype>
#include<cmath>
#include<algorithm>
#include<unordered_map>
const int base=233;
typedef long long LL;
#define N 3000005
std::unordered_map<LL,int>X;
inline int readint(){
    int c=getchar(),d=0;
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar())
    d=d*10+(c^'0');
    return d;
}
int n,m,k,id[N],fp=0,buc[N];
LL ans[N],hx[N],H[N],pw[N];
int siz;
char s[N];
struct que{
    int l,r,id;
    inline bool operator<(const que&rhs)const{
        return(l/siz!=rhs.l/siz)?l<rhs.l:r<rhs.r;
    }
}q[100005];
int main(){
    n=readint(),m=readint(),k=readint();
    for(int i=*pw=1;i<=n;++i)pw[i]=1LL*pw[i-1]*base;
    scanf("%s",s+1);
    for(int i=n;i;--i)hx[i]=(hx[i+1]*base+s[i]-'a');
    for(int i=1;i<=n-k+1;++i){
        H[i]=hx[i]-hx[i+k]*pw[k];
        if(!X.count(H[i]))X[H[i]]=++fp;
        id[i]=X[H[i]];
    }
    for(int i=1;i<=m;++i){
        q[i].l=readint(),q[i].r=readint();q[i].id=i;
        if(q[i].r>n-k+1)q[i].r=n-k+1;
        if(q[i].l>q[i].r)q[i].l=1,q[i].r=0;
    }
    siz=n/sqrt(m);
    std::sort(q+1,q+m+1);
    LL now=0;
    for(int l=1,r=0,i=1;i<=m;++i){
        while(r<q[i].r)now+=buc[id[++r]]++;
        while(l>q[i].l)now+=buc[id[--l]]++;
        while(l<q[i].l)now-=--buc[id[l++]];
        while(r>q[i].r)now-=--buc[id[r--]];
        ans[q[i].id]=now;
    }
    for(int i=1;i<=m;++i)printf("%lld\n",ans[i]);
    return 0;
}

```

---

## 作者：ZnHF (赞：2)

# 题意简述

给定一个长度为 $n$ 的，由特定 $7$ 种字符构成的字符串，有 $m$ 次询问，每次询问需要求出编号在 $[l,r]$ 内的后缀中，有多少对后缀的最长公共前缀长度大于等于 $k$。

# 题目分析

注意到在所有询问中，$k$ 的值是一样的，所以我们可以考虑求出给定字符串中以第 $i$ 个位置为开头，第 $i+k-1$ 个位置为结尾的区间的哈希值，随后，问题便转化为求在给定的区间内，有多少对数字相等。可以使用莫队解决。

## 代码

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
inline int read(){register int t1=0,t2=0;register char x=getchar();while(x<'0' ||x>'9'){if(x=='-') t2|=1;x=getchar();}while(x>='0' && x<='9'){t1=(t1<<1)+(t1<<3)+(x^48),x=getchar();}return t2?-t1:t1;}
inline void write(int x){register int sta[105],top=0;if(x<0) putchar('-'),x=-x;do{sta[top++]=x%10,x/=10;}while(x);while(top) putchar(sta[--top]+48);}
const int base=131;
int n,m,k,f[3000005],p[3000005],a[3000005],tot,t[3000005],ans[3000005],l=1,r,now,cnt[3000005],temp;
char c[3000005];
struct que{
    int l,r,id;
}q[100005];
bool cmp(que x,que y){
    if(x.l/temp!=y.l/temp) return x.l<y.l;
    if((x.l/temp)&1) return x.r<y.r;
    return x.r>y.r;
}
inline void add(int x){
    now-=cnt[x]*cnt[x];
    cnt[x]++;
    now+=cnt[x]*cnt[x];
}
inline void del(int x){
    now-=cnt[x]*cnt[x];
    cnt[x]--;
    now+=cnt[x]*cnt[x];
}
signed main(){
    #ifdef cxy
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    ios::sync_with_stdio(0);
    cin>>n>>m>>k;
    p[0]=1;
    for(int i=1;i<=n;i++){
        cin>>c[i];
        f[i]=f[i-1]*base+(c[i]-'a'+1);
        p[i]=p[i-1]*base;
    }
    for(int i=1;i+k-1<=n;i++){
        a[i]=f[i+k-1]-f[i-1]*p[i+k-1-i+1];
        t[i]=a[i];
        tot++;
    }
    sort(t+1,t+1+tot);
    temp=unique(t+1,t+1+tot)-t-1;
    for(int i=1;i<=tot;i++) a[i]=lower_bound(t+1,t+1+temp,a[i])-t;
    for(int i=1;i<=m;i++){
        cin>>q[i].l>>q[i].r;
        q[i].id=i;
        q[i].r=min(q[i].r,n-k+1);
        if(q[i].l>q[i].r){
            q[i].l=1;
            q[i].r=0;
        }
    }
    temp=sqrt(m);
    sort(q+1,q+1+m,cmp);
    for(int i=1;i<=m;i++){
        while(l>q[i].l) add(a[--l]);
        while(r<q[i].r) add(a[++r]);
        while(l<q[i].l) del(a[l++]);
        while(r>q[i].r) del(a[r--]);
        ans[q[i].id]=now-(q[i].r-q[i].l+1)>>1;
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：ustze (赞：2)

这应该是比赛中最简单的一题吧，我想（虽然我没打  
对每个长度为k的子串做一个hash，之后就等于小z的袜子了...  
维护区间每个颜色（姑且这么叫吧，即hash值）个数的平方和，然后就是一个莫队模板题了...  
另外，这题很dl的卡hash，我用了好几个模数都过不了，最后自然溢出过了...  
具体见代码吧
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int N=3e6+5,base=131;
int n,m,k;
int block;
int belong[N];
ll a[N];int cnt[N];
ll f[N],mul[N],b[N];ll anss[N];
char s[N];
struct ask{
    int l,r,id;
}q[N];
inline int read(){
    int s=0;char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) s=s*10+ch-48,ch=getchar();
    return s;
}
inline bool cmp(const ask &a,const ask &b){
    return belong[a.l]^belong[b.l]?belong[a.l]<belong[b.l]:belong[a.l]&1?a.r<b.r:a.r>b.r;
}
ll ans=0;
inline void add(int x){cnt[a[x]]++,ans+=cnt[a[x]]*2-1;}
inline void del(int x){ans-=cnt[a[x]]*2-1,cnt[a[x]]--;}
int main(){
    n=read(),m=read(),k=read();
    if(m<=1) block=1;
    else block=(n-k+1)/sqrt(m*2/3);
    if(block<1) block=1;
    scanf("%s",s+1);
    mul[0]=1;
    for(int i=1;i<=n;i++) f[i]=((ll)f[i-1]*base+s[i]),mul[i]=(mul[i-1]*base);
    n=n-k+1;
    for(int i=1;i<=n;i++) {
        a[i]=((f[i+k-1]-(f[i-1]*mul[k])));
        b[i]=a[i];belong[i]=(i-1)/block+1;
    }
    sort(b+1,b+n+1);int t=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++) 
        a[i]=lower_bound(b+1,b+t+1,a[i])-b;
    //以上为前置操作，即预处理
    int l,r,num=0;
    for(int i=1;i<=m;i++){
        l=read(),r=read();
        if(l<=n){
            if(r>n) r=n;
            num++;q[num].l=l,q[num].r=r,q[num].id=i;
        }
    }
    sort(q+1,q+num+1,cmp);
    l=1,r=0;
    //以下为莫队
    for(int i=1;i<=num;i++){
        for (;r<q[i].r;r++) add(r+1);
        for (;r>q[i].r;r--) del(r);
        for (;l<q[i].l;l++) del(l);
        for (;l>q[i].l;l--) add(l-1);
        anss[q[i].id]=(ans-(q[i].r-q[i].l+1))/2;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",anss[i]);
    return 0;
}
```

---

## 作者：_ctz (赞：1)

[$My\ blog$](https://ctz45562.github.io/2019/05/11/洛谷-P5112-FZOUTSY)

[传送门](https://www.luogu.org/problemnew/show/P5112)

不知道是莫队写假了还是人丑常数大，随便一交就是最劣解$QwQ$。

首先来看数据范围：$n^2m\le 10^{15}$

开个方：$n\sqrt{m}\le 3\times 10^7$

这不莫队吗？考虑怎么$O(1)$添加、删除一个后缀的影响。

把串翻转一下就是前缀的最长公共后缀，也就是$SAM$里$parent\ tree$的$LCA$的$len$。

而且某个点子孙的$len$一定大于它自己的$len$。

这样找到所有最高的$len\ge k$的节点，它子树中任意两个节点都能产生$1$贡献。

染个色计数跑一遍莫队就完了。

代码：

``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define maxn 6000005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
#define son(x,y) son[x][y]
struct Query{
	int l,r,be,num;
	bool operator < (const Query &x)const{
		if(x.be!=be)return be<x.be;
		if(be&1)return r<x.r;
		return r>x.r;
	}
}q[100005];
struct edge{
	int pre,to;
}e[maxn];
int trans[150],son[maxn][7],fa[maxn],len[maxn],c[maxn],top[maxn],h[maxn],w[maxn]={1},num,cnt=1,last=1,k;
long long ans[100005],all;
char s[maxn];
inline void add(int from,int to){
	e[++num].pre=h[from],h[from]=num,e[num].to=to;
}
void dfs(int node=1,int tp=0){
	if(!tp&&len[node]>=k)tp=node;
	top[node]=tp;
	for(register int i=h[node];i;i=e[i].pre)dfs(e[i].to,tp);
}
void insert(int c){
	int p=last,ne=last=++cnt;
	len[ne]=len[p]+1;
	while(p&&!son(p,c))son(p,c)=ne,p=fa[p];
	if(!p)fa[ne]=1;
	else {
		int q=son(p,c);
		if(len[q]==len[p]+1)fa[ne]=q;
		else {
			int sp=++cnt;
			memcpy(son[sp],son[q],sizeof son[q]);
			len[sp]=len[p]+1,fa[sp]=fa[q],fa[q]=fa[ne]=sp;
			while(p&&son(p,c)==q)son(p,c)=sp,p=fa[p];
		}
	}
}
inline void up(int x){
	if(!x)return;
	all+=(c[x]++);
}
inline void down(int x){
	if(!x)return;
	all-=(--c[x]);
}
int main(){
	trans['z']=1,trans['o']=2,trans['u']=3,trans['t']=4,trans['s']=5,trans['y']=6;
	int n=read(),m=read(),sq=n/sqrt(m),l,r;k=read();
	scanf("%s",s+1);
	for(register int i=1;i<=n>>1;++i)swap(s[i]=trans[s[i]],s[n-i+1]=trans[s[n-i+1]]);
	for(register int i=1;i<=n;++i)insert(s[i]);
	for(register int i=1;i<=n;++i)w[i]=son(w[i-1],s[i]);
	for(register int i=2;i<=cnt;++i)add(fa[i],i);
	dfs();
	for(register int i=1;i<=n;++i)w[i]=top[w[i]];
	for(register int i=1;i<=m;++i)l=read(),r=read(),q[i].l=n-r+1,q[i].r=n-l+1,q[i].num=i,q[i].be=l/sq+1;//原串翻转了，询问区间也要翻转
	sort(q+1,q+1+m);
	l=1,r=0;
	for(register int i=1;i<=m;++i){
		while(l<q[i].l)down(w[l++]);
		while(l>q[i].l)up(w[--l]);
		while(r>q[i].r)down(w[r--]);
		while(r<q[i].r)up(w[++r]);
		ans[q[i].num]=all;
	}
	for(register int i=1;i<=m;++i)printf("%lld\n",ans[i]);
}

```

$P.S$：欢迎$dalao$提出蒟蒻哪里写假了，~~虽然当最劣解也挺好的~~



---

## 作者：Thinking (赞：1)

## ~~模板：后缀数组毒瘤~~

看见题面上的“后缀”、“$lcp$”等字样，dalao们大概马上想到后缀数组了。但是这道题能不能不用后缀数组呢？~~（其实是我不会后缀数组）~~

不难想到，$lcp\ge k$意味着两个字符串的前$k$个字符是相同的，于是大力字符串哈希，用$$(a_{1}x^{k-1}+a_{2}x^{k-2}+...+a_{k})*k-a_{1}x^{k}+a_{k+1}=a_{2}x^{k-1}+a_{3}x^{k-2}+...+a_{k+1}$$不难$O(n)$算出各个长度为$k$的子串的哈希值，接下来就是统计方案了。可以参考[小Z的袜子](https://www.luogu.org/problemnew/show/P1494)，用莫队解决问题。

但是，$O(n\sqrt{n})$的莫队会被卡，所以要用快大小为$\frac{n}{\sqrt{m}}$的莫队，复杂度为$O(n\sqrt{m})$，对于$n^{2}m\le 10^{15}$，即$n\sqrt{m}\le 3.2*10^{7}$的数据，可以通过。

另外，模数太小的字符串哈希也会被卡，最好直接用unsigned long long，相当于模$2^{64}$，再对$n$个值离散化。

$code:$

```cpp
#include<cstdio>
#include<cctype>
#include<cmath>
#include<algorithm>
#define PC(A) putchar(A)
using namespace std;
typedef unsigned long long ll;
const int N=3000050;
const int M=100050;
const int P=3000017;
const int x=233;  //233
char BB[1<<21],*S,*T;
inline char gc(){return S==T&&(T=(S=BB)+fread(BB,1,1<<20,stdin),S==T)?EOF:*S++;}
inline short rdc(){
    char c=gc();
    while(!islower(c))c=gc();
    return c-'a';
}
inline int rdi(){
    char c=gc();
    while(!isdigit(c))c=gc();
    int x=c&15;
    for(c=gc();isdigit(c);c=gc())x=(x<<3)+(x<<1)+(c&15);
    return x;
}
short buf[25];
inline void wt(ll x){
    short l=-1;
    while(x>9){
        buf[++l]=x%10;
        x/=10;
    }
    PC(x|48);
    while(l>=0)PC(buf[l--]|48);
    PC('\n');
}
short a[N];
int h[P],nxt[N],p[N],cnt[N],l[M],r[M],t[M],n,k,sz,o=1;
ll v[N],s[M];
inline void add(ll w){
    int t=w%P;
    v[o]=w;
    nxt[o]=h[t];
    h[t]=o;
}
inline int find(ll w){
    int t=w%P,i;
    for(i=h[t];i;i=nxt[i])if(v[i]==w)return i;
    return 0;
}  //用哈希表实现离散化
inline ll fp(int p){  //快速幂
    ll a=x,s=1;
    while(p){
        if(p&1)s=s*a;
        a=a*a;
        p>>=1;
    }
    return s;
}
inline void work(){
    int i,t;
    ll tmp=fp(k),res=0;
    for(i=1;i<=k;i++)res=res*x+a[i];
    add(res);
    p[1]=1;
    for(i=k+1;i<=n;i++){
        res=res*x-a[i-k]*tmp+a[i];  //前文的式子
        if(t=find(res))p[i-k+1]=t;
        else{
            p[i-k+1]=++o;
            add(res);
        }
    }
}
int cmp(int a,int b){return (l[a]-1)/sz==(l[b]-1)/sz?r[a]<r[b]:l[a]<l[b];}
int main(){
    int m,i,x,y;
    ll ans=0;
    n=rdi();m=rdi();k=rdi();
    sz=n/sqrt(m);
    for(i=1;i<=n;i++)a[i]=rdc();
    work();
    for(i=0;i<m;i++){
        l[i]=rdi();r[i]=rdi();
        if(r[i]+k-1>n)r[i]=n-k+1;
        if(l[i]>r[i])l[i]=r[i];  //坑，小心这两种问题
        t[i]=i;
    }
    sort(t,t+m,cmp);
    x=l[t[0]];y=r[t[0]];
    for(i=x;i<=y;i++){
        ans+=cnt[p[i]];
        cnt[p[i]]++;
    }
    s[t[0]]=ans;
    for(i=1;i<m;i++){
        if(l[t[i]]<x)do{
            x--;
            ans+=cnt[p[x]];
            cnt[p[x]]++;
        }while(x>l[t[i]]);
        else for(;x<l[t[i]];x++){
            cnt[p[x]]--;
            ans-=cnt[p[x]];
        }
        if(r[t[i]]>y)do{
            y++;
            ans+=cnt[p[y]];
            cnt[p[y]]++;
        }while(y<r[t[i]]);
        else for(;y>r[t[i]];y--){
            cnt[p[y]]--;
            ans-=cnt[p[y]];
        }
        s[t[i]]=ans;
    }  //莫队
    for(i=0;i<m;i++)wt(s[i]);
    return 0;
}
```

---

## 作者：happybob (赞：0)

由于 $k$ 固定，考虑处理 $h_i$ 为以 $i$ 开头的后缀的前 $k$ 个字符的哈希值。

两个后缀的最长公共前缀 $\geq k$ 等价于这两个后缀前 $k$ 个字符相同，于是可以转化为 $h_i=h_j$。

于是变成了经典的类似区间数颜色的问题，使用莫队，块长为 $\frac{n}{\sqrt{m}}$，就可以做到 $O(n \sqrt{m})$ 的复杂度了。

有点卡哈希模数，但 `unsigned long long` 自然溢出过了。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
using ull = unsigned long long;

const int N = 3e6 + 5, M = 1e5 + 5;

int n, m, k;
char s[N];
int len, bel[N], cnt[N];
long long res, ans[M];

ull hashing[N];
ull ec[N];
int nec[N];
vector<ull> v;

struct Query
{
	int l, r, id;
	Query(int _l, int _r, int _i) : l(_l), r(_r), id(_i) {}
	Query() {}
	bool operator<(const Query& g) const
	{
		return (bel[l] ^ bel[g.l]) ? bel[l] < bel[g.l] : (bel[l] & 1) ? r < g.r : r > g.r;
	}
}p[M];

ull qpow(ull a, ull b)
{
	ull res = 1, base = a;
	while (b)
	{
		if (b & 1)
		{
			res = res * base;
		}
		base *= base;
		b >>= 1LL;
	}
	return res;
}

struct FastIO {
	static const int S = 1e7;
	int wpos;
	char wbuf[S];
	FastIO() : wpos(0) {}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if (pos == len)
			pos = 0, len = fread(buf, 1, S, stdin);
		if (pos == len) exit(0);
		return buf[pos++];
	}
	inline int xuint() {
		int c = xchar(), x = 0;
		while (c <= 32) c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x;
	}
	inline int xint()
	{
		int c = xchar(), x = 0;
		while (c <= 32) c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x;
	}
	inline void xstring(char* s)
	{
		int c = xchar();
		while (c <= 32) c = xchar();
		for (; c > 32; c = xchar()) *s++ = c;
		*s = 0;
	}
	inline void wchar(int x)
	{
		if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wint(long long x)
	{
		char s[24];
		int n = 0;
		while (x || !n) s[n++] = '0' + x % 10, x /= 10;
		while (n--) wchar(s[n]);
		wchar('\n');
	}
	inline void wstring(const char* s)
	{
		while (*s) wchar(*s++);
	}
	~FastIO()
	{
		if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
} io;

int main()
{
	n = io.xint(), m = io.xint(), k = io.xint();
	io.xstring(s);
	len = max(1, (int)(n / sqrt(m)));
	for (int i = 1; i <= n; i++)
	{
		hashing[i] = hashing[i - 1] * 27 + (s[i - 1] - 'a');
	}
	ull pp = qpow(27, k);
	for (int i = 1; i + k - 1 <= n; i++)
	{
		ull subseq_hash = (hashing[i + k - 1] - hashing[i - 1] * pp);
		ec[i] = subseq_hash;
		v.emplace_back(ec[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 1; i + k - 1 <= n; i++)
	{
		nec[i] = lower_bound(v.begin(), v.end(), ec[i]) - v.begin() + 1;
	}
	for (int i = 1; i <= m; i++)
	{
		int l, r;
		l = io.xint(), r = io.xint();
		r = min(r, n - k + 1);
		p[i] = Query(l, r, i);
	}
	sort(p + 1, p + m + 1);
	int nl(1), nr(0);
	for (int i = 1; i <= m; i++)
	{
		if (p[i].l > p[i].r || p[i].l > n - k + 1)
		{
			ans[p[i].id] = 0;
			continue;
		}
		int l = p[i].l, r = p[i].r;
		while (nr < r) res += cnt[nec[++nr]]++;
		while (nl > l) res += cnt[nec[--nl]]++;
		while (nl < l) res -= --cnt[nec[nl++]];
		while (nr > r) res -= --cnt[nec[nr--]];
		ans[p[i].id] = res;
	}
	for (int i = 1; i <= m; i++) io.wint(ans[i]);
	return 0;
}
```


---

## 作者：Pwtking (赞：0)

[传送门](https://www.luogu.com.cn/problem/P5112)

区间的非强制在线操作，首先可以想到莫队，并且貌似区间之间的答案也可以相互转化，考虑莫队。

接下来就是如何转化为莫队了。

观察到 $k$ 是不变的，意味着我们可以预处理**以每个字符为起点之后 $k$ 个字符所组成的字符串的哈希值**和**以每个字符为起点的后缀的哈希值**以便去重。

接下来就转化为[小z的袜子](https://www.luogu.com.cn/problem/P1494)了，正常莫队即可。


---

## 作者：bmatrix (赞：0)

大家好我后缀数组学魔怔了，所以我来写一发用到后缀数组的题解。

首先求出字符串 $s$ 的 $sa$，$rk$ 和 $ht$ 三个数组，用 $i$ 代表 $s$ 以 $i$ 开头的后缀。

根据 $\operatorname{lcp}(i, j) = \min\limits_{p=rk_i + 1}^{rk_j} ht_p$，问题转化为区间内有多少个点对满足 $\min\limits_{p=rk_i + 1}^{rk_j} ht_p\ge k$，换句话说就是在 $(rk_i,rk_j]$ 这个区间里每个数都 $\ge k$。

由于每个数都 $\ge k$，所以 $<k$ 的 $ht$ 就将原 $ht$ 数组分成了若干块，$rk$ 值在同一块里的点对有贡献，否则没贡献。设 $c_i$ 为第 $i$ 个块中的元素个数，问题转化为对于每个询问求 $\sum \dfrac{c_i*(c_i - 1)}2$。

发现这个东西可以莫队，时间复杂度 $O(n\log n + n\sqrt m)$，可过。

代码：
```cpp
constexpr int N = 3e6 + 5;
int n, m, k, cnt[N], sa[N], id[N], __rk[2][N], *rk = __rk[0], *ork = __rk[1], ht[N];
char s[N];
void get_sa() {
    int m = 128, p = 0;
    rep(i, 1, n) ++cnt[rk[i] = s[i]];
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    per(i, n, 1) sa[cnt[rk[i]]--] = i;
    for(int w = 1; ; m = p, p = 0, w <<= 1) {
        rep(i, n - w + 1, n) id[++p] = i;
        rep(i, 1, n) if(sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, 4 * (m + 1));
        rep(i, 1, n) ++cnt[rk[i]];
        rep(i, 1, m) cnt[i] += cnt[i - 1];
        per(i, n, 1) sa[cnt[rk[id[i]]]--] = id[i];
        swap(rk, ork);
        p = 0;
        rep(i, 1, n) rk[sa[i]] = ork[sa[i]] == ork[sa[i - 1]] && ork[sa[i] + w] == ork[sa[i - 1] + w] ? p : ++p;
        if(p == n) break;
    }
}
void get_ht() {
    int k = 0;
    rep(i, 1, n) {
        if(k) --k;
        while(s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        ht[rk[i]] = k;
    }
}
int B, b[N], tot, bel[N], cc[N];
ll ans[N], res;
void get_b() {
    rep(i, 1, n) if(ht[i] < k) b[++tot] = i;
    b[tot + 1] = n + 1;
    rep(i, 1, tot) rep(j, b[i], b[i + 1] - 1) bel[sa[j]] = i;
}
struct query {
    int l, r, id;
    bool operator<(const query& b) const {
        return l / B != b.l / B ? l / B < b.l / B : (l / B & 1) ? r < b.r : r > b.r;
    }
} q[N];
inline void add(int i) { res += cc[i]++; }
inline void del(int i) { res -= --cc[i]; }
void solve() {
    int l = 1, r = 0;
    rep(i, 1, m) {
        while(l > q[i].l) add(bel[--l]);
        while(r < q[i].r) add(bel[++r]);
        while(l < q[i].l) del(bel[l++]);
        while(r > q[i].r) del(bel[r--]);
        // rep(i, 1, tot) cout << cc[i] << ' '; cout << endl;
        ans[q[i].id] = res;
    }
}
signed main() {
    cin >> n >> m >> k;
    cin >> (s + 1);
    get_sa();
    get_ht();
    get_b();
    // rep(i, 1, n) cout << sa[i] << ' '; cout << endl;
    // rep(i, 1, n) cout << rk[i] << ' '; cout << endl;
    // rep(i, 1, n) cout << ht[i] << ' '; cout << endl;
    // rep(i, 1, tot) cout << b[i] << ' '; cout << endl;
    // rep(i, 1, n) cout << bel[i] << ' '; cout << endl;
    rep(i, 1, m) cin >> q[i].l >> q[i].r, q[i].id = i;
    B = n / sqrt(m);
    sort(q + 1, q + m + 1);
    solve();
    rep(i, 1, m) cout << ans[i] << endl;
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

$\operatorname{LCP}(a,b)\ge k\Leftrightarrow$ $\forall i\le k,a_i=b_i$。

维护出每个后缀 $s_i$ 长度为 $k$ 的前缀 $a_i$。

然后就是数区间 $a_i$ 相同对数，莫队维护。

$\sqrt{n^2m}=n\sqrt m\le\sqrt{10^{15}}$，可以过掉。

```cpp
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
struct Q{int l, r, i;}q[3000050];
int n, m, k, z, t[3000050], c[3000050];char f[3000050];
unsigned long long g = 1, a[3000050], v[3000050], h[3000050];long long p, s[3000050];
void I(int x) {p += c[a[x]]++;}void D(int x) {p -= --c[a[x]];}
bool B(Q x, Q y) {return t[x.l] == t[y.l] ? t[x.l] & 1 ? x.r < y.r : x.r > y.r : x.l < y.l;}
int main()
{
	scanf("%d%d%d%s", &n, &m, &k, f + 1);
	for(int i = 1;i <= k;++i) g *= 233;
	for(int i = 1, k = n / sqrt(m) + 1;i <= n;++i)
		h[i] = h[i - 1] * 233 + f[i], t[i] = (i - 1) / k + 1;
	for(int i = 1;i <= n - k + 1;++i) v[z++] = a[i] = h[i + k - 1] - h[i - 1] * g;
	sort(v, v + z);z = unique(v, v + z) - v;
	for(int i = 1;i <= n - k + 1;++i) a[i] = lower_bound(v, v + z, a[i]) - v + 1;
	for(int i = 0;i < m;++i)
		scanf("%d%d", &q[i].l, &q[i].r), q[i].r = min(q[i].r, n - k + 1),
		q[i].l = min(q[i].l, q[i].r + 1), q[i].i = i;
	sort(q, q + m, B);for(int i = 0, l = 1, r = 0;i < m;++i)
	{
		while(l > q[i].l) I(--l);while(r < q[i].r) I(++r);
		while(l < q[i].l) D(l++);while(r > q[i].r) D(r--);
		s[q[i].i] = p;
	}
	for(int i = 0;i < m;++i) printf("%lld\n", s[i]);return 0;
}
```


---

## 作者：404Not_Found (赞：0)

好像挺简单的。

因为我不会什么后缀数组和后缀自动机，考虑字符串哈希，$\mathcal{O}(n)$ 算出每个长度为 $k$ 的子串的哈希值，不难发现就是要求 $[l,r]$ 之间有多少对哈希值相等。莫队搞一下，就做完了。

这题数据比较水，开始块长设的 $\sqrt n$，$\mathcal{O}(n \sqrt n)$ 冲过了 $3 \times 10^6$。事实上应该把块长设为 $\dfrac{n}{\sqrt m}$，时间复杂度是 $\mathcal{O}(n \sqrt{m})$ 的。又因为保证了 $n^2m \le 10^{15}$，所以复杂度是正确的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e6+5;
int n,m,k;
char s[N];
int bel[N],blk;
struct Query{
	int id,l,r;
	bool operator<(const Query& rhs) const
	{
		if(bel[l]==bel[rhs.l]) return bel[l]&1?r<rhs.r:r>rhs.r;
		return bel[l]<bel[rhs.l];
	}
} q[N];
#define ull unsigned long long
ull Hash[N],pw[N],t[N],val[N],tot;
const ull base = 131;
void Hash_init()
{
	pw[0]=1;
	for(int i=1;i<=n;i++)
	{
		pw[i]=pw[i-1]*base;
		Hash[i]=Hash[i-1]*base+s[i];
	}
	for(int i=0;i<=n-k;i++) val[i+1]=Hash[i+k]-Hash[i]*pw[k],t[++tot]=val[i+1];
	sort(t+1,t+tot+1);
	tot=unique(t+1,t+n+1)-t-1;
	for(int i=1;i<=n;i++) val[i]=lower_bound(t+1,t+tot+1,val[i])-t;
}
long long cnt[N],ans[N],now;
void add(int x){now+=cnt[val[x]]; cnt[val[x]]++;}
void del(int x){cnt[val[x]]--; now-=cnt[val[x]];}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	scanf("%s",s+1); Hash_init();
	int blk=pow(n,0.5);
	for(int i=1;i<=n;i++) bel[i]=(i-1)/blk+1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&q[i].l,&q[i].r); q[i].id=i;
		if(q[i].r>n-k+1) q[i].r=n-k+1;
		if(q[i].l>q[i].r) q[i].l=1,q[i].r=0;
	}
	sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(r<q[i].r) add(++r);
		while(r>q[i].r) del(r--);
		while(l<q[i].l) del(l++);
		while(l>q[i].l) add(--l);
		ans[q[i].id]=now;
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<"\n";
	return 0;
}
```

---

## 作者：Jμdge (赞：0)

这道题居然这么水...个屁啊...


# noteskey

其实这里我们用个 HASH 自然溢出求出每个后缀的 HASH 值就行了

但由于这里要求的只是 K 级复读，那么我们只需要记录每个后缀前 K 个字符的 HASH 值就好了，至于询问区间就是离线下来用莫队处理了...

# faster

然后关键的就是卡常技巧了 Q.Q

首先是上面说过的自然溢出

其次就是 unordered_map 了，因为 map 比较慢啊...怎么说，一个跑不过去用另一个就对了 ~(￣▽￣)~

还有莫队的时候 compare 函数的优化，具体看代码

# code

短倒是挺短的...

```cpp
//by Judge
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include<unordered_map>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define ll unsigned long long
using namespace std;
const int base=131;
const int M=3e6+3;
typedef int arr[M];
typedef ll ARR[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} inline void reads(string& s){ char c=getchar();
	for(;!isalpha(c);c=getchar()); s=" ";
	for(;isalpha(c);c=getchar()) s+=c;
} char sr[1<<21],z[20];int CCF=-1,Z;
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(ll x,char chr='\n'){
    if(CCF>1<<20)Ot(); while(z[++Z]=x%10+48,x/=10);
    while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
} int n,m,k,bl,tim; string s;
unordered_map<ll,int> X;
arr id,num;  ARR ans,hx,H,pw;
struct que{ int l,r,id; }q[100005];
inline bool cmp(const que& a,const que& b){
	return (a.l/bl!=b.l/bl)?a.l<b.l:(a.l/bl&1)?a.r<b.r:a.r>b.r;
}
int main(){ n=read(),m=read(),k=read(),*pw=1;
	fp(i,1,n) pw[i]=pw[i-1]*base; reads(s);
	fd(i,n,1) hx[i]=hx[i+1]*base+s[i]-'a';
	fp(i,1,n-k+1){ H[i]=hx[i]-hx[i+k]*pw[k];
		if(!X.count(H[i])) X[H[i]]=++tim; id[i]=X[H[i]];
	}
	fp(i,1,m){
		q[i].l=read(),q[i].r=read(),q[i].id=i;
		if(q[i].r>n-k+1) q[i].r=n-k+1;
		if(q[i].l>q[i].r) q[i].l=1,q[i].r=0;
	}
	bl=n/sqrt(m)+1,sort(q+1,q+1+m,cmp);
	ll now=0; int l=1,r=0;
	for(int i=1;i<=m;ans[q[i].id]=now,++i){
		while(r<q[i].r) now+=num[id[++r]]++;
		while(l>q[i].l) now+=num[id[--l]]++;
		while(l<q[i].l) now-=--num[id[l++]];
		while(r>q[i].r) now-=--num[id[r--]];
	} fp(i,1,m) print(ans[i]); return Ot(),0;
}
```

# UPD：

代码好像被 HACK 了？

但其实思路没毛病...只不过莫队分块的时候块的大小调一下（+1）就好了

```cpp
	bl=n/sqrt(m); // before update
	bl=n/sqrt(m)+1;  // after update
```



---

## 作者：Owen_codeisking (赞：0)

发布一篇搞笑的题解………

我前段时间自己yy出了这道题结果翻一翻以前公开赛有这题而且比我造的数据要强……

看一看自己的程序简直sb……

错解：

下面是作死过程……

首先我们做一遍后缀数组，然后对于每个数在 $rnk$ 上二分/倍增到区间 $[L,R]$。想到莫队，对于一个 $[l,r]$ 转换为 $[l,r+1]$ 的时候看看 $[L_{r+1},R_{r+1}]$ 中间多少 $l\leq sa\leq r$

然后我们用后缀数组+莫队+树状数组打出了 $O(n\sqrt{n}\log n)$ 的版本……

现在我们想去掉这个 $\log$……

我想到二次离线莫队！时间复杂度 $O(n\sqrt{n})$

但是没用……这道题 $n\leq 3\times 10^6$……

正解：哈希

对于区间 $[i,i+k-1](1\leq i\leq n-k+1)$ 做一遍哈希，把问题转换为小 $Z$ 的袜子。

但是我们需要玄学调一调块长…… $siz=\frac {n}{\sqrt{m}}$ 就行了。

我也不知道 $shadowice1984$ 为什么没卡掉自然溢出……

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxn=3000000+10;
const int base=233;
int n,m,k,blo,cnt[maxn],tot;ull f[maxn],pw[maxn],val[maxn],mp[maxn],ans[maxn],now;
char s[maxn];

struct Query{
    int l,r,id;
}q[maxn];

inline bool cmp(const Query &a,const Query &b){
    if((a.l-1)/blo!=(b.l-1)/blo) return (a.l-1)/blo<(b.l-1)/blo;
    return a.r<b.r;
}

inline int read(){
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();};
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}

inline void add(int x){now+=cnt[val[x]]++;}
inline void del(int x){now-=--cnt[val[x]];}

int main()
{
    n=read(),m=read(),k=read();blo=n/(int)sqrt(m)+1;
    scanf("%s",s+1);
    pw[0]=1;
    for(int i=1;i<=n;i++){
        f[i]=f[i-1]*base+s[i];
        pw[i]=pw[i-1]*base;
    }
    for(int i=0;i<=n-k;i++) val[i+1]=mp[++tot]=f[i+k]-f[i]*pw[k];
    sort(mp+1,mp+tot+1);
    tot=unique(mp+1,mp+tot+1)-mp-1;
    for(int i=1;i<=n;i++) val[i]=lower_bound(mp+1,mp+tot+1,val[i])-mp;
    for(int i=1;i<=m;i++){
        q[i].l=read(),q[i].r=read(),q[i].id=i;
        if(q[i].r>n-k+1) q[i].r=n-k+1;
        if(q[i].l>q[i].r) q[i].l=1,q[i].r=0;
    }
    sort(q+1,q+m+1,cmp);
    int L=1,R=0;
    for(int i=1;i<=m;i++){
        while(R<q[i].r) add(++R);
        while(R>q[i].r) del(R--);
        while(L<q[i].l) del(L++);
        while(L>q[i].l) add(--L);
        ans[q[i].id]=now;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
    return 0;
}
```

---

