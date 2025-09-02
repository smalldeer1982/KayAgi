# Palisection

## 题目描述

给定一个长度为n的小写字母串。问你有多少对相交的回文子 串（包含也算相交） 。

## 样例 #1

### 输入

```
4
babb
```

### 输出

```
6
```

## 样例 #2

### 输入

```
2
aa
```

### 输出

```
2
```

# 题解

## 作者：xixike (赞：15)

[博客食用更佳](https://www.cnblogs.com/xixike/p/15514978.html)

# Description

> [Luogu传送门](https://www.luogu.com.cn/problem/CF17E)

# Solution

非常有意思的一道题。

看到**回文子串**，首先想到的 manacher 算法。emm……但是写了 manacher 之后怎么做呢？

我们发现，求相交的回文子串非常麻烦，所以直接一波正难则反，用总的回文子串数减去不相交的。

接下来考虑如何求不相交的回文子串。

我们开两个数组 $f_i$，$g_i$。$f_i$ 表示以 $i$ 为开头的回文串有多少个，$g_i$ 表示以 $i$ 为结尾的回文串有多少个。

看到标签里的$\color{blue}{前缀和}$，我们给 $g_i$ 做个前缀和存到 $sum_i$ 里，那么 $sum_i$ 就表示结尾是 $i$ 及以前的点的回文子串有多少个， 我们发现不相交的回文子串个数就是:

 $$res = \sum\limits_{i = 1}^{n}{sum_i \times f_{i + 1}}$$

用总数减去即可。

那么 $f_i$ 和 $g_i$ 怎么求呢？

我们发现标签里的 $\color{blue}{差分}$ 还没有用到~~标签真是好用~~。考虑用差分。

我们已经使用 manacher 算法求出了每个点作为回文串的中心时最长的回文半径是多少，设为 $p_i$（$p_i$ 是原字符串扩展后的新串的回文半径，长度就是原串的回文串的长度，如果不懂的话可以去学一下 manacher，这里不再赘述）。

我们发现，一个半径 $p_i$ 会形成许多回文串，分别是：

$$i - p_i + 1\ \ \ \  \sim\ \ \ \  i\ \ \ \  \sim\ \ \ \  i + p_i - 1$$

$$i - p_i + 2\ \ \ \  \sim\ \ \ \  i\ \ \ \  \sim\ \ \ \  i + p_i - 2$$

$$i - p_i + 3\ \ \ \  \sim\ \ \ \  i\ \ \ \  \sim\ \ \ \  i + p_i - 3$$
$$·$$
$$·$$
$$i - 1\ \ \ \ \sim\ \ \ \ i\ \ \ \ \sim\ \ \ \ i + 1$$
$$i$$

也就是说，我们要对 $f_{i - p_i + 1} \sim f_i$ 都 +1，同样的，对$g_i \sim g_{i + p_i - 1}$ 也都 +1。

这时我们就可以用差分来解决了，即 $f_{i - p_i + 1}++$，$f_{i + 1}--$，同时对 $g_{i}++$，$g_{i + p_i}--$。

最后循环一遍统计答案就可以啦，需要注意的是，现在我们已经把原本的字符串扩展过了，所以循环的增幅为 2。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long

using namespace std;

const ll N = 4e6 + 10;
const ll mod = 51123987;
ll n, ans, tot, sum;
char s[N], a[N];
ll f[N], g[N], p[N];

inline void manacher(){
    s[0] = '*', s[(n << 1) + 1] = '#';
    for(ll i = 1; i <= n; ++i)
        s[(i << 1) - 1] = '#', s[i << 1] = a[i];
    n = (n << 1) + 1;
    ll mx = 0, id = 0;
    for(ll i = 1; i <= n; ++i){
        if(i < mx) p[i] = min(mx - i, p[(id << 1) - i]);
        else p[i] = 1;
        while(i - p[i] >= 1 && i + p[i] <= n && s[i - p[i]] == s[i + p[i]]) p[i]++;
        if(i + p[i] > mx) mx = i + p[i], id = i;
        tot = (tot + (p[i] >> 1)) % mod;
    }
}

signed main(){
    scanf("%lld%s", &n, a + 1);
    manacher();
    for(ll i = 1; i <= n; ++i){
        f[i - p[i] + 1]++, f[i + 1]--;
        g[i]++, g[i + p[i]]--;
    }
    for(ll i = 1; i <= n; ++i)
        f[i] += f[i - 1], g[i] += g[i - 1];
    ans = tot * (tot - 1) / 2 % mod;
    for(ll i = 2; i <= n - 2; i += 2){
        sum = (sum + g[i]) % mod;
        ans = (ans - sum * f[i + 2] % mod + mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}
```



# End

---

## 作者：Kelin (赞：11)

### 题意

求一个字符串的所有有交集的回文子串有多少对

---
### 题解

直接做貌似是做不了的,考虑到正难则反

我们设用回文串的总数是$sum$ $\Rightarrow ans={sum\choose 2}-$没有交集的回文串对数

考虑怎么算没有交集的回文串对数

我们考虑答案可以是$\sum_i$以$i$结尾的回文串个数$\times i$后面的回文串个数

以$i$结尾的回文串个数就是$i$这个点在$fail$树上的深度

$i$后面的回文串个数$=\sum_{j>i}$以$j$开头的回文串个数

考虑把串反过来,再用后缀和优化一下就可以了

因为$n\le 2*10^6$,所以这题要用邻接链表来存$fail$树

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
const int N=2e6+5,P=51123987;
typedef int arr[N];
typedef long long ll;
int n,sum,ans;arr suf,dep;char s[N];
struct eg{int nx,to,w;};
struct node{int fail,len,cnt;};
inline int pls(int a,int b){return a+=b,a>=P?a-P:a;}
inline int sub(int a,int b){return a-=b,a<0?a+P:a;}
struct PAM{
    int n,tot,las,ce;arr fi,s;node a[N];eg e[N];
    inline void add(int u,int v,int w){e[++ce]={fi[u],v,w},fi[u]=ce;}
    inline void init(){s[0]=-1,tot=1,ce=n=las=0;a[0].fail=1,a[1].len=-1;}
    inline int gf(int x){while(s[n-a[x].len-1]^s[n])x=a[x].fail;return x;}
    inline int get(int u,int w){go(u)if(e[i].w==w)return v;return 0;}
    inline int ins(int v){
        int&u=tot;s[++n]=v;las=gf(las);
        if(!get(las,v)){
            a[++u]={get(gf(a[las].fail),v),a[las].len+2,0};
			add(las,u,v);dep[u]=dep[a[u].fail]+1;
        }++a[las=get(las,v)].cnt;return dep[las];
    }
    inline int calc(){
        int tp=0;
        fd(i,tot,2)tp=pls(tp,a[i].cnt),
        	a[a[i].fail].cnt+=a[i].cnt;
        return tp;
    }
}p;
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    scanf("%d%s",&n,s+1);
    p.init();fd(i,n,1)suf[i]=pls(suf[i+1],p.ins(s[i]-'a'));
    memset(p.fi,0,4*(p.tot+1));
    p.init();fp(i,1,n)ans=pls(ans,1ll*p.ins(s[i]-'a')*suf[i+1]%P);
    sum=p.calc();sum=1ll*sum*(sum-1)/2%P;printf("%d",sub(sum,ans));
return 0;
}
```

---

## 作者：唐一文 (赞：10)

## Description

[传送门](https://www.luogu.com.cn/problem/CF17E)

## Solution

~~看到字符串就想到哈希~~

直接求相交的回文子串的数量显然不太好求

那么可以算出所有回文子串的数量再减去不相交的回文子串的数量

设所有回文子串的个数为 $num$，以下标 $i$ 开头的回文子串个数为 $L_i$，以下标 $i$ 结尾的回文子串个数为 $R_i$

那么所有回文子串对数的数量为 $\dbinom{num}{2}$

对于每个 $i$，与以 $i$ 结尾的回文子串不相交的且在 $i$ 右边的回文子串的个数为 $\sum_{j=i+1}^nL_j$

那么所有不相交的回文子串的数量为 $\sum_{i=1}^nR_i\sum_{j=i+1}^nL_j$

相交的回文子串的数量即为 $\dbinom{num}{2}-\sum_{i=1}^nR_i\sum_{j=i+1}^nL_j$

接下来考虑怎么计算 $num$

发现一个长度大于 $1$ 的回文串，把它两边的字母去掉，仍是一个回文串

所以我们可以对每个位置进行二分，寻找以 $i$ 为中心的最长回文串的长度，记为 $len_{i,0}$ 和 $len_{i,1}$，分长度为奇数和长度为偶数的情况

那么 $num=\sum_{i=1}^n\left\lceil\dfrac{len_{i,0}}{2}\right\rceil+\sum_{i=1}^n\dfrac{len_{i,1}}{2}$

但是求 $len$ 时直接暴力判断回文时间复杂度是 $\mathcal O(n^2\log{n})$，可以用哈希优化变成 $\mathcal O(n\log{n})$

再来考虑求 $L$ 和 $R$

对于 $len_{i,0}$，可以将区间 $\left[i-\left\lfloor\dfrac{len_{i,0}}{2}\right\rfloor,i\right]$ 的 $L$ 和区间 $\left[i,i+\left\lfloor\dfrac{len_{i,0}}{2}\right\rfloor\right]$ 的 $R$ 都 $+1$

$len_{i,1}$ 同理

如果直接暴力的话时间复杂度是 $\mathcal O(n^2)$，可以用树状数组或线段树维护，变成 $\mathcal O(n\log{n})$

那么这题就做完了，时间复杂度 $\mathcal O(n\log{n})$

## Tips

- 这个做法比较屑，时空都需要卡常

- 哈希可以用 `int` 自然溢出减少时空消耗（这道题没有卡 `int` 自然溢出）

- $L,R$ 用线段树维护会爆空间，常数也很大，过不去，要用树状数组

- $L$ 是区间修改和区间查询，用两个树状数组维护（具体的可以看[这题](https://www.luogu.com.cn/problem/P3372)的题解），$R$ 是区间修改和单点查询，只需要用一个树状数组维护

## Code

~~最裂解代码~~
```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
#define ll long long
using namespace std;
#define MAXN 2000005
#define mod 51123987
#define lowbit(x) ((x)&(~(x)+1))
#define MOD(x) ((x)<mod?(x):(x)-=mod)
#define fMOD(x) ((x)>-mod?(x):(x)+=mod)
#define GetFro(l,r)fro[(r)]-fro[(l)-1]*mul[(r)-(l)+1]//求s[l,r]的哈希值
#define GetBac(l,r)bac[(l)]-bac[(r)+1]*mul[(r)-(l)+1]//求s[r,l]的哈希值
int n;
ll ans;
char s[MAXN];
int mul[MAXN]={1},fro[MAXN],bac[MAXN];
struct SMT{//维护L
  int sum[MAXN][2];
  il void Add(int x,int k,int id){for(;x<=n;sum[x][id]+=k,MOD(sum[x][id]),fMOD(sum[x][id]),x+=lowbit(x));}
  il void Update(int l,int r){Add(l,1,0),Add(r+1,-1,0),Add(l,l-1,1),Add(r+1,~r+1,1);}
  il int Qry(int x,int id){int ans=0;for(;x;ans+=sum[x][id],MOD(ans),x-=lowbit(x));return ans;}
  il int Query(int l,int r){int ans=(1ll*r*Qry(r,0)-1ll*(l-1)*Qry(l-1,0)-1ll*Qry(r,1)+1ll*Qry(l-1,1))%mod;return fMOD(ans);}
}L;
struct BIT{//维护R
  int sum[MAXN];
  il void Add(int x,int k){for(;x<=n;sum[x]+=k,MOD(sum[x]),fMOD(sum[x]),x+=lowbit(x));}
  il void Update(int l,int r){Add(l,1),Add(r+1,-1);}
  il int Qry(int x){int ans=0;for(;x;ans+=sum[x],MOD(ans),x-=lowbit(x));return ans;}
}R;
main(){
  scanf("%d%s",&n,s+1);
  for(re int i=1;i<=n;++i)mul[i]=mul[i-1]*131;
  for(re int i=n;i;--i)bac[i]=bac[i+1]*131+s[i];//倒过来哈希一遍
  for(re int i=1;i<=n;++i)fro[i]=fro[i-1]*131+s[i];//正着哈希一遍
  for(re int i=1,l,r,mid;i<=n;++i){
    for(l=0,r=min(i-1,n-i+1)+1;l+1<r;mid=l+r>>1,GetFro(i-mid,i-1)==GetBac(i,i+mid-1)?l=mid:r=mid);//二分长度为偶数的回文串（这里枚举的是往左右拓展的长度）
    if(l)ans+=l,L.Update(i-l,i-1),R.Update(i,i+l-1);//注意要判断是否有长度为偶数的回文串
    for(l=0,r=min(i-1,n-i+1)+1;l+1<r;mid=l+r>>1,GetFro(i-mid,i-1)==GetBac(i+1,i+mid)?l=mid:r=mid);//二分长度为奇数的回文串
    ans+=l,L.Update(i-l,i),R.Update(i,i+l);
  }
  ans+=n,ans%=mod,ans=(1ll*ans*(ans-1)>>1)%mod;
  for(re int i=1;i<n;++i)ans-=1ll*R.Qry(i)*L.Query(i+1,n)%mod;
  printf("%d",(ans%mod+mod)%mod);
}
```

---

## 作者：Karry5307 (赞：7)

### 题意

给定一个长度为 $n$ 的字符串 $S$，求有多少种方案从 $S$ 中选出两个相交的回文串。

$\texttt{Data Range:}1\leq n\leq 2\times 10^6$

### 题解

不敢想象，我居然没看题解写出了 *2900 的字符串题？（~~以前做字符串基本上都得看题解~~）

很明显直接做不是很好做，于是考虑用总的方案数减去不相交的方案数。

设 $f_i$ 表示以 $i$ 为前缀的回文串个数，$g_i$ 表示以 $i$ 为后缀的回文串个数，则答案为

$$\sum\limits_{i=1}^{n}f_i\sum\limits_{j=1}^{i-1}g_j$$

然后记录一个 $g$ 的前缀和这部分可以 $O(n)$，考虑求 $f$ 和 $g$。

先对这个串做 Manacher 求出以位置 $i$ 的字符为中心的最长回文半径 $r_i$，然后以这个串为中心，拓展到不超过 $r_i$ 的所有串都是回文串。

注意到这些串的左端点是连续的，也即这个回文中心对 $f$ 的贡献是一段区间加 $1$ 的形式，差分即可搞定，对于 $g$ 也是类似的求法，时间复杂度 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=4e6+51,MOD=51123987,INV2=25561994;
ll n,mxr,mid,c,res,lx,rx;
ll rad[MAXN],f[MAXN],g[MAXN];
char s[MAXN],ch[MAXN];
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
int main()
{
	n=read(),scanf("%s",s+1),ch[0]='~',ch[n*2+1]='|';
	for(register int i=1;i<=n;i++)
	{
		ch[i*2-1]='|',ch[i*2]=s[i];
	}
	for(register int i=1;i<=2*n+1;i++)
	{
		rad[i]=i<mxr?min(rad[(mid<<1)-i],rad[mid]+mid-i):1;
		while(ch[i+rad[i]]==ch[i-rad[i]])
		{
			rad[i]++;
		}
		rad[i]+i>mxr?mxr=rad[i]+i,mid=i:1;
	}
	for(register int i=1;i<=2*n+1;i++)
	{
		lx=i-rad[i]+1,rx=i+rad[i]-1,lx+=lx&1,rx-=rx&1;
		if(lx<=rx)
		{
			lx>>=1,rx>>=1,f[lx]++,f[(i>>1)+1]--,g[(i+1)>>1]++,g[rx+1]--;
			c=(c+(i>>1)-lx+1)%MOD;
		}
	}
	for(register int i=1;i<=n;i++)
	{
		f[i]+=f[i-1],g[i]+=g[i-1];
	}
	for(register int i=1;i<=n;i++)
	{
		g[i]=(g[i]+g[i-1])%MOD,res=(res+(li)f[i]*g[i-1]%MOD)%MOD;
	}
	printf("%d\n",((li)c*(c-1)%MOD*INV2%MOD-res+MOD)%MOD);
}
```

---

## 作者：hyfhaha (赞：4)

卡空间PAM，2010没有PAM，所以都是马拉车

众所周知，PAM拥有十分优秀的时间复杂度，但空间复杂度lj得不行

但这题卡空间，所以得用到**邻接链表PAM** 

先讲思路

题目要求相交的回文子串对，这很难做

于是我们求补集，求不相交的回文子串对，再用总数减即可

求法和上文的**最长双回文子串** 类似

正反建一次PAM，存该位置结尾的回文子串个数，然后加法改乘法

自己领悟一下，挺简单的。

现在讲一下**邻接链表PAM** 

#### 注意：**邻接链表PAM**不是使空间变小了，而是用时间换空间

我们记边结构体$line$

存$3$个信息：$nx,to,w$ 分别表示上一条边，这条边通向的节点编号，这条边是代表哪个字符

数组$fir[i]$表示$i$伸出的最后一条边的编号（头插式

当我们要寻找$u$的$v$儿子

我们就像邻接链表一样找，直到有一条边的$w==v$为止

找不到记得指根

```cpp
int getson(int u,int v){
	for(int i=u;i!=-1;i=l[i].nx)
		if(l[i].w==v)return l[i].to;
	return -1;
}
```

建点的时候把边建上

```cpp
void insert(int u,int i){
	int Fail=getfail(pre,i),ls=getfail(fail[Fail],i);
	if(getson(fir[Fail],u)==-1){
		if(getson(fir[ls],u)==-1)fail[++tot]=0;		//找不到指根
		else fail[++tot]=getson(fir[ls],u);	//找到了
		l[++cnt]=(line){fir[Fail],tot,u};fir[Fail]=cnt;		//加边
		len[tot]=len[Fail]+2;
		ans[tot]=ans[fail[tot]]+1;		//结尾回文子串个数
		pre=tot;
	}else 
	pre=getson(fir[Fail],u);
}
```

然鹅事实上你仍然过不了，你还要继续压空间，省掉一堆数组就可以过啦！

总代码：

```cpp
#include<bits/stdc++.h>
#define maxn 2000005
#define mod 51123987
using namespace std;
char s[maxn];
int slen,b[maxn];
long long res;
int fail[maxn],len[maxn],ans[maxn],fir[maxn];
struct line{int nx,to,w;}l[maxn];
int tot,pre,cnt;
void init(){
	memset(fir,-1,sizeof(fir));cnt=0;
	fail[0]=1;len[1]=-1;tot=1;pre=0;
}
int getfail(int x,int i){
	while(i-len[x]-1<0||s[i-len[x]-1]!=s[i])x=fail[x];
	return x;
}
int getson(int u,int v){
	for(int i=u;i!=-1;i=l[i].nx)
		if(l[i].w==v)return l[i].to;
	return -1;
}
void insert(int u,int i){
	int Fail=getfail(pre,i),ls=getfail(fail[Fail],i);
	if(getson(fir[Fail],u)==-1){
		if(getson(fir[ls],u)==-1)fail[++tot]=0;
		else fail[++tot]=getson(fir[ls],u);
		l[++cnt]=(line){fir[Fail],tot,u};fir[Fail]=cnt;
		len[tot]=len[Fail]+2;
		ans[tot]=ans[fail[tot]]+1;
		pre=tot;
	}else 
	pre=getson(fir[Fail],u);
}
int main(){
	int n;
	scanf("%d",&n);
	scanf("%s",s);slen=strlen(s);init();
	reverse(s,s+slen);
	for(int i=0;i<slen;i++)insert(s[i]-'a',i),b[slen-i-1]=ans[pre];
	for(int i=slen-1;i>=0;i--)b[i]+=b[i+1],b[i]%=mod;
	reverse(s,s+slen);init();
	for(int i=0;i<slen-1;i++){
		insert(s[i]-'a',i);int x=ans[pre];
		res+=(1ll*x*b[i+1])%mod,res%=mod;
	}
	printf("%lld\n",((1ll*b[0]*(b[0]-1)/2ll)%mod-res+mod)%mod);
	return 0;
}
```



---

## 作者：荣一鸣 (赞：4)

## 回文串处理从马拉车开始

马拉车是啥？走这里（这是同学的blog） [传送门->hash & manacher & ......](https://blog.csdn.net/qq_42037034/article/details/80975874)

首先，我们从这道题讲起，我们看到要找回文串，再求回文串的左边界和右边界，然后再比较是否相交。

我在第一遍写的时候，直接打暴力，连马拉车都没打。。。

果断爆，多少分我也不知道，但还是能有分的，代码已删，不出了。

那么我们马拉车之后就得到了对于每个对称点i来说的最长的半径f[i]。然后我们开始差分。

差分是个神奇的东西[不会走这里](https://blog.csdn.net/dingming001/article/details/73732102)

我们定义两个数组l[ ],r[ ]，用l[i]来存以i为开头的回文串的数量，r[i]来存以i为结尾的回文串的数量，我们可以发现，当i<j时，r[i] * l[j]得到的就是不满足的一部分数量，我们用差分和前缀和来做

```
for(int i=1;i<=M;i++){
	l[i-f[i]+1]++;
    l[i+1]--;
    r[i]++;
    r[i+f[i]]--;
    (ans+=f[i]/2)%=P;//此时ans为回文串总数 
	ans=1ll*ans*(ans-1)/2%P;//假设都能相交ans就是相交的总数
	for(int i=1,s=0;i<=M;i++){
		l[i]+=l[i-1],r[i]+=r[i-1];//这里前缀和利用差分取得l,r到底是多少
		if(i%2==0) //manacher后的字符位
        	(ans-=1ll*s*l[i]%P)%=P,(s+=r[i])%=P;//s是在i之前已经结束的回文串数，s*l[i]就代表在i时减掉的数量
	}
}
```
强，无敌，放一波压缩的22行的神仙代码

```
#include<bits/stdc++.h>
#define P 51123987
#define maxn 4000005
using namespace std;
int N,M=1,f[maxn],l[maxn],r[maxn],ans;
char a[maxn],b[maxn];
int main(){
	scanf("%d%s",&N,a),b[0]=1;
	for(int i=0;i<N;i++,M++) b[++M]=a[i];//manacher时要放入的代码用' '代替
	for(int i=1,p=0,q=0;i<=M;i++){//manacher
		f[i]=q>i? min(f[2*p-i],q-i):1; //f[i]为半径 ，i为中心 
		while(b[i+f[i]]==b[i-f[i]]) f[i]++;
		if(i+f[i]>q) p=i,q=i+f[i];
	}
	for(int i=1;i<=M;i++) l[i-f[i]+1]++,l[i+1]--,r[i]++,r[i+f[i]]--,(ans+=f[i]/2)%=P;//此时ans为回文串总数 
	ans=1ll*ans*(ans-1)/2%P;//假设都能相交 
	for(int i=1,s=0;i<=M;i++){
		l[i]+=l[i-1],r[i]+=r[i-1];
		if(i%2==0) (ans-=1ll*s*l[i]%P)%=P,(s+=r[i])%=P;
	}
	printf("%d\n",(ans+P)%P);
}
```

---

## 作者：crashed (赞：3)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/CF17E)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到回文串，先上马拉车。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;马拉车跑完一遍之后，我们就可以推出这个字符串里面有多少个回文串。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;有了总的回文串数量，我们也就可以得到总的回文串两两配对的数量。然后我们就只需要考虑不相交的回文串对的数量，然后减掉就可以了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$l_i$为以$i$为左端点的回文串的数量，$r_i$为以$i$为右端点的回文串的数量，那么不难发现答案就是：  
$$\sum_{i=1}^{|S|}r_i\sum_{j=i+1}^{|S|}l_j$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;设$ls(i)=\sum_{j=i}^{|S|}l_j$，然后答案就是$\sum_{i=1}^{|S|}r_ils(i+1)$。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;而用差分可以在马拉车之后$O(n)$求出$l$和$r$，于是这道题就被$O(n)$解决了。差分部分具体看代码。  
# 代码
```cpp
#include <cstdio>

const int mod = 51123987, inv2 = 25561994;
const int MAXN = 2e6 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + s - '0', s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int lef[MAXN], rig[MAXN];
int len[MAXN << 1], l[MAXN << 1], r[MAXN << 1];
char S[MAXN << 1];
int N, length;

void manacher()
{
	int mid = 0, mxr = 0;
	for( int i = 1 ; i <= length ; i ++ )
	{
		if( i <= mxr ) len[i] = MIN( len[( mid << 1 ) - i], mid + len[mid] - i );
		while( i - len[i] > 0 && i + len[i] <= length && S[i - len[i]] == S[i + len[i]] ) len[i] ++;
		if( i + len[i] > mxr ) mxr = i + len[i], mid = i;
	}
}

int fix( const int a )  { return ( a % mod + mod ) % mod; }

int main()
{
	read( N );
	S[++ length] = '$';
	for( int i = 1 ; i <= N ; i ++ )
		S[++ length] = getchar(), S[++ length] = '$';
	manacher();
	for( int i = 1 ; i <= length ; i ++ )
		l[i - len[i] + 1] ++, l[i + 1] --,
		r[i] ++, r[i + len[i]] --;
        //做差分，(i-len[i],i]都可以成为左端点，而[i,i+len[i])都可以成为右端点
	int res = 0;
	for( int i = 1 ; i <= length ; i ++ )
	{
		( res += len[i] >> 1 ) %= mod, ( l[i] += l[i - 1] ) %= mod, ( r[i] += r[i - 1] ) %= mod;
		if( S[i] ^ '$' ) lef[i >> 1] = l[i], rig[i >> 1] = r[i];
        //把扩展的串上的l和r转到原串上面
	}
	for( int i = 1 ; i <= N ; i ++ ) ( lef[N - i + 1] += lef[N - i + 2] ) %= mod;
	res = 1ll * res * fix( res - 1 ) % mod * inv2 % mod;
	for( int i = 1 ; i <= N ; i ++ )
		res = fix( res - 1ll * rig[i] * lef[i + 1] % mod );
	write( res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：myEnd (赞：2)

题目大意：让你求一个字符串的所有有交集的回文子串有多少对。

## 解题思路

先用 Manacher 算法求出回文串个数 $n$ 。之后进行排除，所以答案就是

由于 Manacher 算法求出回文串比较模板，接下来讨论需要排除的情况：考虑在线性时间内求出没有交集的回文子串数。

容易发现，如果有两个回文子串没有交集，那么一定存在一个点使得他左边的回文子串和他右边的回文子串必然没有交集。

也就是说我们对于一个点，要计算有多少回文子串的右端点不超过这个点，同时要统计有多少个回文子串的左端点不超过他。

但是这样会有大量的重复，接下来讨论优化：

为了像筛法的进步一样避免重复，最好每种情况只枚举一遍，于是得到了下面这种方法：

分别用 $\text{结尾在该点的回文子串数量}\times\text{起点在该点右侧的回文串的数量}$ , 这样能做到不重不漏了。

我们开两个数组 $\text{head}$​​ 、 $\text{tail}$​​ 分别代表头和尾。$\text{head}_i$​​ 表示以 $i$​​ 号节点开头的回文子串， $\text{tail}_i$​​ 表示以 $i$​​ 号节点结尾的回文子串。

接下来讨论如何求得 $\text{head}$ 与 $\text{tail}$ 数组：

Manacher 算法只能求得每个点的回文半径。进一步推敲：

对于 $i$ 号点位回文串中心时，可以发现产生了许多的回文串：

| $i - r[i] + 1$     | $i$        | $i + r[i] - 1$     |
| ------------------ | ---------- | ------------------ |
| **$i - r[i] + 2$** | **$i$**    | **$i + r[i] - 2$​​** |
| **$i - r[i] + 3$** | **$i$**    | **$i + r[i] - 3$​** |
| **......**         | **......** | **......**         |

 注意到回文半径的定义： $i - r[i]$ 与 $i + r[i]$ 是不同字符，不被包含。

那么 $\text{head}$​ 被从 $i - r[i] + 1$​ 到 $i$​ 区间 $+1$， $\text{tail}$​ 被从 $i$ 到 $i + r[i] - 1$ 区间 $+1$ 即可。

于是易得：多次区间修改，最后询问一次。可以分析出可以使用“差分+前缀和”。

注意到：现在求出的 $\text{head}$ 与 $\text{tail}$ 都是被扩展过的字符串的。

最后枚举时只枚举字符位即可。因为以字符开头/结尾的回文子串一定也会在字符为终止，而原字符串上的回文子串一定也能对应到扩展后的字符串上，占位符不影响。

## 参考代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

typedef long long ll;
const ll mod=51123987, MAXN = 2200000;
ll sum, maxn, i0, all, r[MAXN<<1], head[MAXN<<1], tail[MAXN<<1], len,ans, num;
char a[MAXN], s[MAXN<<1];

//占位符放置
inline void init_Manacher(void)
{
    s[0]='^';
    s[1]='$';
    for(int i=0;i<=len-1;i++)  s[2*i+2]=a[i], s[2*i+3]='$';
    s[2*len+2]='%';
    r[1]=i0=1, maxn=2;
}

//Manacher
inline void Manacher(void)
{
    for(int i=2;i<=2*len+1;i++)
    {
        r[i]=maxn>i?min(maxn-i,r[2*i0-i]):1;
        while(s[i-r[i]]==s[i+r[i]])r[i]++;
        if(i+r[i]>maxn)maxn=i+r[i],i0=i;
        num=r[i]/2;
        all=(all+num)%mod;
    }
}

int main()
{
    scanf("%lld %s",&len,a);

    init_Manacher();
    Manacher();

    for(int i=1;i<=2*len+1;i++)  head[i-r[i]+1]++, head[i+1]--;
    for(int i=1;i<=2*len+1;i++)  tail[i]++, tail[i+r[i]]--;
    for(int i=1;i<=2*len+1;i++)  head[i]+=head[i-1], tail[i]+=tail[i-1];

    ans=(all-1)*all/2%mod;//C(n, 2)

    for(int i=2;i<=2*len-2;i=i+2)
    {
        sum=(sum+tail[i])%mod; 
        ans=(ans-sum*head[i+2]%mod)%mod;
    }

    printf("%I64d\n", (ans%mod+mod)%mod);
    return 0;

}
```

---

## 作者：lzyqwq (赞：1)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/p/17828736.html)**

改进了一下 @[$\bf{ \color{black}\text{唐}\color{red} \text{一文}}$](https://www.luogu.com.cn/user/150843) 大佬的做法。

tags：

- $\text{strings}$

- $\color{red}*2900$

**[洛谷](https://www.luogu.com.cn/problem/CF17E) [CF](https://codeforces.com/problemset/problem/17/E)**

> - 给出一个字符串 $s$，求 $s$ 有多少对相交的回文子串（不考虑顺序）。
>
> - $|s|\le 2\times 10^6$。
>
> - $2.00\,\text{s}\,/\,125.00\,\text{MB}$。

考虑容斥，用回文子串对数减去不相交的。记 $tot$ 表示回文子串个数，$L_i$ 表示以 $i$ 开头的回文子串个数，$R_i$ 表示以 $i$ 结尾的回文子串个数，则答案为：

$$\dfrac{tot\cdot (tot-1)}{2}-\sum\limits_{i=1}^{|s|} \left(R_i\cdot \sum\limits_{j=i+1}^{|s|} L_j\right)$$

简单解释一下，就是枚举左边回文子串的结尾位置，那么所有开头位置大于这个位置的回文子串与其不相交。

考虑如何求出 $tot$，枚举中心 $i$，分奇数、偶数长度讨论，可以发现若一个子串是回文串，那把它两端的字符去掉其仍然是回文串，即答案有单调性。

维护正反串哈希值，考虑二分 + 哈希求出出最长的奇数 / 偶数分别是**第几个**。记为 $f0,f1$，那么它带来了 $f0+f1$ 个回文子串。

而且可以发现，以奇数为例，对于 $[i-f0+1,i]$ 这些位置又可以作为当前回文串的左端点，相当于 $L$ 区间 $+1$；$[i,i+f0-1]$ 这些位置可以作为右端点，相当于 $R$ 区间 $+1$。

由于只有一次查询，而且还是在最后，考虑维护差分数组并前缀和，就可以求出 $L_i,R_i$。

最后枚举 $i$，维护一下 $L$ 的后缀和直接算即可。

时间复杂度为 $\mathcal{O}(|s|\log |s|)$，空间复杂度为 $\mathcal{O}(|s|)$。

**[提交记录（$\color{limegreen}\bf Accepted$ $\bold{590\,{ms}\,/\,52008\,{KB}}$，含代码）](https://codeforces.com/contest/17/submission/232569780)**


---

## 作者：Argon_Cube (赞：1)

因为作者太菜了，所以有一个不用正难则反的做法。但是很显然非常复杂被其它题解爆杀。

还有这玩意真有 ${}^* 2900$ 吗。

---

先跑 Manacher，对每一个位置统计以它为左端点与以它为右端点的回文串个数。

然后两个字符串相交，当且仅当一个的左端点小于另一个的右端点且一个的右端点大于等于另一个的左端点。做一遍前缀和就能统计出对于每一个回文串与它相交的有多少个，加起来就好了。

接着我们可以发现一个回文串我们会算成与自己相交，减去即可；一对不同的相交回文串会被算两次，除以二就行了。

感谢题目给的模数是个奇数。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <array>

using namespace std;

array<long long,4000003> manacher,presuml,presumr;
array<char,4000003> str;
const int moder=51123987;

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cnt;
    long long answer=0;
    cin>>cnt;
    str[0]='A',str[1]='_';
    for(int i=1;i<=cnt;i++)
        cin>>str[i<<1],str[i<<1|1]='_';
    str[cnt+1<<1]='C';
    for(int i=1,pos=0;i<cnt+1<<1;i++)
    {
        if(pos+manacher[pos]>=i)
            manacher[i]=min(manacher[pos*2-i],pos+manacher[pos]-i);
        while(str[i+manacher[i]+1]==str[i-manacher[i]-1])
            ++manacher[i];
        if(i+manacher[i]>pos+manacher[pos])
            pos=i;
        answer-=manacher[i]+1>>1;
    }
    for(int i=1;i<cnt+1<<1;i++)
        ++presuml[i-manacher[i]],--presuml[i+1],++presumr[i],--presumr[i+manacher[i]];
    for(int i=1;i<cnt+1<<1;i++)
        (presuml[i]+=presuml[i-1])%=moder,(presumr[i]+=presumr[i-1])%=moder;
    int suml=0,sumr=0;
    for(int i=2;i<cnt+1<<1;i+=2)
        suml=(suml+presuml[i])%moder,answer=(answer+presumr[i]*suml-presuml[i]*sumr)%moder+moder,sumr=(sumr+presumr[i])%moder;
    cout<<answer%moder*(moder+1)/2%moder;
    return 0;
}
```

---

## 作者：功在不舍 (赞：1)

一道挺奇妙的字符串题目，要你求一个字符串的所有有交集的回文子串有多少对。

统计回文子串的重复情况好像没法在线性时间内做到。

我们可以先用manacher求出回文串个数n。

则答案就是$ C_n^2-$没有交集的回文子串对数。

现在来想想怎么在线性时间内求出没有交集的回文子串对数


可以发现，如果两个回文子串没有交集，那么他们俩一定有一个分割点。

对于一个分割点，他左边的回文子串和右边的回文子串必然都没有交集。

也就是我们对于一个点，要统计有多少回文子串的右端点不超过他，

也要统计有多少回文子串的左端点不超过他。

但是这就够了吗？ 不，我们可以发现上面那种计算方式有大量重复。

为了避免重复，我们只能枚举一遍，分别用结尾在该点的回文子串数量乘以在起点在
该点右侧的回文串的数量，这样就没有重复了，而且能统计到所有无交集回文子串对。

我们设$tou[i]$为以i号点为开头的回文子串数量，$wei[i]$为以i号点结尾的回文子串数量。

现在怎么求tou和wei呢？我们的manacher只能求出每个点的回文半径。

对于i号点为回文串中心时，可以发现产生了很多个回文串

               i-r[i]+1   i    i+r[i]-1
               
               i-r[i]+2   i    i+r[i]-2
               
               i-r[i]+3   i    i+r[i]-3
               
               . . . . . .
               
注意回文半径的定义$i-r[i]$和$i+r[i]$是不同的字符哦。

tou 被从$i-r[i]+1$到$i$ 区间+1 wei 被从$i$到$i+r[i]-1$区间+1

多次区间修改，最后询问一次，这不就是差分+前缀和吗？

注意，现在我们求出来的wei和tou都是被扩展过的字符串的。

最后枚举的时候我们只枚举字符位就好了。因为以字符为开头/结尾的回文子串一定

也会在字符位终止，而原串上的回文子串一定也能对应到扩展串上，占位符不影响。
               
               

用样例举个例子

              0   1   2   3   4   5   6   7   8   9   10

              ^   &   b   &   a   &   b   &   b   &   % 
    
回文半径 r[i]
                     
              \   1   2   1   4   1   2   3   2   1   \
       
以i号点开头的回文串数量tou[i] 差分/前缀和
           
              \   3  -1   0  -1   2  -1   0  -1   0   \
 
              \   3   2   2   1   3   2   2   1   1   \

以i号点结尾的回文串数量wei[i] 差分/前缀和

              \   1   0   1  -1   1   0   1  -1   1   \ 

              \   1   1   2   1   2   2   3   2   3   \


只统计偶数字符位

manacher求出共有6个回文子串

1.分割点在3号 $ wei[2]*tou[4]=1*1=1 $

2.分割点在5号 $ (wei[2]+wei[4])*tou[6]=(1+1)*2=4 $

3.分割点在7号 $ (wei[2]+wei[4]+wei[6])*tou[8]=(1+1+2)*1=4 $

答案为$ C_6^2-(1+4+4)=15-9=6$

大家都懂了吗？下面是代码

```cpp

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char a[2200000],s[4400000];
typedef long long ll;
ll p=51123987,sum,maxn,i0,all,r[4400000],tou[4400000],wei[4400000],len,ans,num;
int main()
{
	scanf("%lld %s",&len,a);
	s[0]='^';s[1]='$';
	for(int i=0;i<=len-1;i++)
	    s[2*i+2]=a[i],s[2*i+3]='$';
	s[2*len+2]='%';r[1]=i0=1,maxn=2;
	for(int i=2;i<=2*len+1;i++)
	{
	   r[i]=maxn>i?min(maxn-i,r[2*i0-i]):1;
	   while(s[i-r[i]]==s[i+r[i]])r[i]++;
	   if(i+r[i]>maxn)maxn=i+r[i],i0=i;
	   num=r[i]/2;all=(all+num)%p;
    }//正常manacher 
    for(int i=1;i<=2*len+1;i++)tou[i-r[i]+1]++,tou[i+1]--;
    for(int i=1;i<=2*len+1;i++)wei[i]++,wei[i+r[i]]--;
	for(int i=1;i<=2*len+1;i++)tou[i]+=tou[i-1],wei[i]+=wei[i-1];
//差分与前缀和 
	ans=(all-1)*all/2%p;
	for(int i=2;i<=2*len-2;i=i+2)
	{//注意上面的模拟过程，wei是要记录前缀和的 
		sum=(sum+wei[i])%p; 
		ans=(ans-sum*tou[i+2]%p)%p;
	}
    cout<<(ans%p+p)%p<<endl;
	return 0;
}


```
       
补充：突然想起来，其实我们要求得$tou[i]$和$wei[i]$可以用回文自动机在$O(n)$时间内解出来，具体代码就是回文自动机的模板题目，求的是$wei[i]$。你只要把串倒置一遍就可以求出$tou[i]$了，这样做的好处是省去了差分过程，也不用在原串上加入‘#’占位符,这里就不放代码了，因为思路已经很明确了。
      



---

## 作者：Jorisy (赞：0)

显然 P1872 加强版。

首先设 $t$ 为回文子串总个数，则本题可以转化为求 $C_t^2-k$，其中 $k$ 是不相交的回文子串对数，也就是总的对数去掉不相交对数，也就变成了 P1872 的线性做法。

记 $l_i$ 为 $s_{1\sim i}$ 的回文子串个数，$r_i$ 为 $s_{i\sim n}$ 的回文子串个数，那么乘法原理可得 $k=\sum\limits_{i=2}^n\left(\sum\limits_{j=1}^{i-1}l_i\right)r_i$。那么就转化成，我们做 Manacher 时，对 $l,r$ 进行区间加一，这一操作显然可以通过差分优化处理。而计算 $k$ 时，我们也可以用前缀和优化一下。

另外注意负数取模。

AC Code：
```cpp
#include<bits/stdc++.h>
#define mod 51123987
#define int long long
using namespace std;

int n,p[4000005],l[4000005],r[4000005],ans,t;
string s; 

void manacher()
{
	int mr=0,mid=0;
	for(int i=1;i<s.size();i++)
	{
		p[i]=i<=mr?min(p[mid*2-i],mr-i+1):1;
		while(s[i+p[i]]==s[i-p[i]]) p[i]++;
		if(i+p[i]>mr) mr=i+p[i]-1,mid=i;
		ans=(ans+p[i]/2)%mod;
		l[i+1>>1]++;
		l[i+p[i]>>1]--;
		r[(i-p[i])/2+1]++;
		r[i/2+1]--;//差分
		//将下标 0~2n 变成 1~n，这个稍微推一下就能出来
	}
}

signed main()
{
	cin>>n;
	s="~#";
	for(int i=1;i<=n;i++)
	{
		char c;
		cin>>c;
		s+=c;
		s+="#";
	}
	manacher();
	ans=1ll*ans*(ans-1)/2%mod;//也就是 C(k,2)
	for(int i=1;i<=n;i++) l[i]+=l[i-1],r[i]+=r[i-1];//前缀和转换成原数组
	for(int i=1;i<=n;i++) l[i]=(l[i]+l[i-1])%mod;//前缀和优化
	for(int i=2;i<=n;i++) ans=(ans-l[i-1]*r[i]%mod+mod)%mod;//计算答案
	cout<<ans;
 	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

远古 $2900$。不难。

先 manacher 一遍。计算出有每个位置是多少回文串的结尾，即对于以 $mid$ 为中心的最长回文串 $[l,r]$，将 $c_{[mid, r]}$ 加 $1$。区间加可以使用差分再前缀和实现。

容斥。设 $tot$ 为回文子串个数，则答案为 $\dbinom{tot}{2}$ 减去不相交的回文子串对数。

还是从 $mid$ 扩展的 $[l,r]$ 考虑，我们要求 $\sum\limits_{i=l}^{mid}\sum\limits_{j=1}^{i-1}c_j$。后面那项做一遍前缀和。然后发现求前面一项还是前缀和。

也就是总共做三次前缀和。

复杂度线性。

[Code](https://www.luogu.com.cn/paste/fed28gqo)

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2900}$
---
### 解题思路：

正难则反，考虑计算出所有的不相交的串的个数并用任选两个串的数量去减。

然后考虑具体如何计算，对于每一个位置，计算出这个位置之前的所有的完整的回文，并用这个值乘上以当前位置为起始端点的回文数量即可。

这两个值的计算是类似的，考虑计算以某一个点为起始的回文的个数。对于任意一个位置 $i$，如果以这个位置为中心点的最长回文是单向拓展长度为 $l$，则任意的 $[i-l,i]$ 都可以作为起始点。也就是一个区间加。

由于只需要最后查询一次，差分一下就好了。

---

实现的时候可以采取跳过奇数位的方法来避免添加的数造成的影响。

----
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=4000005,MOD=51123987;
int n,cnt,f[MAXN],mr,mid,pre[MAXN],suf[MAXN],l,r,tot,sum,ans;
char s[MAXN];
signed main(){
	scanf("%lld",&n);
	s[0]='@';s[++cnt]='#';
	for(int i=1;i<=n;i++){
		s[++cnt]=getchar();
		while(s[cnt]=='\n'||s[cnt]=='\r')s[cnt]=getchar();
		s[++cnt]='#';
	}
	for(int i=1;i<=cnt;i++){
		if(i<mr)f[i]=min(f[(mid*2)-i],f[mid]+mid-i);
		else f[i]=1;
		while(s[i-f[i]]==s[i+f[i]])f[i]++;
		if(i+f[i]>mr){mr=i+f[i];mid=i;}
		tot=(tot+f[i]/2)%MOD;
	}
	for(int i=1;i<=cnt;i++)pre[i-f[i]+1]++,pre[i+1]--,suf[i]++,suf[i+f[i]]--;
	for(int i=1;i<=cnt;i++) 
	pre[i]+=pre[i-1],suf[i]+=suf[i-1];
	
	ans=(tot*(tot-1)/2)%MOD;
	for(int i=2;i<=cnt-2;i+=2){
		sum=(sum+suf[i])%MOD;
		ans=(ans+MOD-sum*pre[i+2]%MOD)%MOD;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：SunsetSamsara (赞：0)

## 前置知识
manacher 算法，差分
## 分析
题目让我们求出 **相交的回文字串个数**，那我们可以先求出 **不相交的回文子串个数** 再用 **所有两两搭配的回文子串个数** 减去它。

所有两两搭配的回文子串个数就是 $C^2_{n}$，$n$ 为所有回文子串个数。

为了求出不相交的回文子串个数，令 $L_i$ 表示以 i 为起点的回文子串个数，$R_i$ 表示以 $i$ 为中点的回文子串个数。

怎么求出 $L_i$ 与 $R_i$ 呢？

对于每个下标 $i$，就需要让 $L_{i-r_i}$ 至 $L_{i}$ 自增 $1$，$R_{i}$ 至 $R_{i+r_i}$ 自增 $1$

接下来就可以利用差分快速解决。

下面就可以求出不相交的回文子串个数了。

不相交的回文子串个数就是：
$$\sum \limits_{i=1}^{len(str)}(L[i]\times\sum\limits_{j=1}^i R_j)$$

相减后得到答案。

## 代码
```cpp#include<cstdio>
using namespace std;
#define lld long long
#define min(a,b) ((a<b)?(a):(b))
const int mod=51123987;
char str1[30000001];
char str2[30000001];
int rd[30000001];
lld l[30000001];
lld r[30000001];
int len;
lld ans;
int main(){
	scanf("%*d%s",str1);
	str2[0]='@';
	str2[++len]='#';
	for(int i=0;str1[i];++i){
		str2[++len]=str1[i];
		str2[++len]='#';
	}
	int mx=0,id=0;
	for(int i=1;i<=len;++i){
		if(i<mx)rd[i]=min(rd[id*2-i],mx-i);
		else rd[i]=1;
		while(str2[i-rd[i]]==str2[i+rd[i]])++rd[i];
		if(mx<i+rd[i]){
			id=i;
			mx=i+rd[i];
		}
	}
	// Manacher
	lld t=0;
	for(int i=1;i<=len;++i){
		++l[i-rd[i]+1];//差分 
		--l[i+1];
		++r[i];
		--r[i+rd[i]];
		t=(t+(rd[i]>>1))%mod;//回文子串个数 
	}
	ans=(t*(t-1)>>1)%mod;//所有两两搭配的回文子串个数
	for(int i=1;i<=len;++i){
		l[i]+=l[i-1];
		r[i]+=r[i-1];
	}//L[i]与R[i] 
	t=0;
	for(int i=1;i<=len;++i)
		if(!(i&1)){//有意义的下标 
			ans=(ans-t*l[i])%mod;
			t=(t+r[i])%mod;
		}
	printf("%lld\n",(ans+mod)%mod);
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF17E)

给定一个长度为 $n$ 的小写字母串.问你有多少对相交的回文子 串(包含也算相交)。.

**输入格式**

第一行是字符串长度 $n(1\le n\le 2*10^6)$，第二行字符串.

**输出格式**

相交的回文子串个数 $\bmod 51123987$.

# 题解

首先，如果我们正向求解有多少个回文串相交有些困难，因为相交的长度不固定，甚至还有可能是包含关系，考虑正~~男(♂)~~难则反——反向求解有多少回文串没有交，这样我们只需要枚举分界点，计算在左边和在右边的回文串数量即可.

那么，这个题的问题就是在对于位置 $i$，我们如何求出在它 左/右 边的回文串数量，这里主要介绍使用 $\tt PAM$ 的解决方案.

我们考虑在加入一个字符 $\tt s[i]$ 之后，结尾**刚好在** $i$ 的回文串的数量，这里给出性质:

> 以一个点结尾的回文串个数就是它所代表的点在 $fail$ 树上的深度.

证明：$\mathcal Obviously$.

对于在其右边的，我们倒着做一遍就可以了.

```cpp
https://www.cnblogs.com/Arextre/p/14269229.html
```

# 本题关键

1. 考虑问题，正难则反；
2. 回文自动机特性：以一个点结尾的回文串个数就是它所代表的点在 $fail$ 树上的深度；

另外，这个题卡空间，建议使用邻接表构建自动机 ~~坑死我了~~.

---

## 作者：chihik (赞：0)


答案为所有的回文串组合-不相交的回文串组合。

记 $cnt$ 为回文串个数 ， 可以通过计算每个节点的回文串数量求得。

不相交的回文组合也比较好求，先算出以 $i$ 为左端点和右端点的回文串数量 $L[i]$ , $R[i]$。

不相交的回文组合个数为：

$$\sum_{i=1}^{len-1}R[i]\sum_{j=i+1}^{len}L[j]$$

将 $L$ 数组做一遍后缀和即可解决问题 ， 注意中间的取模。

空间只有 $\text{128MB}$ , 用朴素的数组存图要炸掉。

~~这道题除了卡空间，就没有什么难点了。~~

实现时用邻接表代替，为了方便打了一个函数找边，常数大了几十倍。

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
#define Mod 51123987

const int MAXN = 2000000;
#pragma GCC pack(1)
struct Palindrome_Automaton {
    int Size , Last , Root0 , Root1 , Link[ MAXN + 5 ];
    int n; char Str[ MAXN + 5 ];
    int Len[ MAXN + 5 ] , Cnt[ MAXN + 5 ] , End[ MAXN + 5 ];
    int Ans , L[ MAXN + 5 ] , R[ MAXN + 5 ];
    vector< pair< char , int > > Trans[ MAXN + 5 ];

    void Init( ) {
        Size = 0; n = 0;
        for( int i = 0 ; i <= MAXN ; i ++ ) Trans[ i ].clear( );
        memset( Link , 0 , sizeof( Link ) );
        memset( Len , 0 , sizeof( Len ) );

        Root0 = Size ++ , Root1 = Size ++; Last = Root1;
        Len[ Root0 ] = 0  , Link[ Root0 ] = Root1;
        Len[ Root1 ] = -1 , Link[ Root1 ] = Root1;
    }

    int chk( long long x ) {
        if( x >= Mod ) x %= Mod;
        return x;
    }
    
    int Finde( int u , char ch ) {
        for( int i = 0 ; i < Trans[ u ].size( ) ; i ++ )
            if( Trans[ u ][ i ].first == ch ) return Trans[ u ][ i ].second;
        return 0;
    }
    int Extend( char ch ) {
        int u = Last; Str[ ++ n ] = ch;
        for( ; Str[ n ] != Str[ n - Len[ u ] - 1 ] ; u = Link[ u ] );
        if( !Finde( u , ch ) ) {
            int Newnode = ++ Size , v = Link[ u ];
            Len[ Newnode ] = Len[ u ] + 2;
            for( ; Str[ n ] != Str[ n - Len[ v ] - 1 ] ; v = Link[ v ] );
            Link[ Newnode ] = Finde( v , ch ); Trans[ u ].push_back( { ch , Newnode } );

            End[ Newnode ] = End[ Link[ Newnode ] ] + 1;
        }
        Cnt[ Last = Finde( u , ch ) ] ++;
        return End[ Last ];
    }
    void Build1( char *str ) {
        Init( );
        int len = strlen( str );
        for( int i = 0 ; i < len ; i ++ )
            R[ i ] = Extend( str[ i ] );
        
        for( int i = Size ; i >= 2 ; i -- )
            Cnt[ Link[ i ] ] = chk( Cnt[ Link[ i ] ] + Cnt[ i ] ) , Ans = chk( Ans + Cnt[ i ] );
        Ans = chk( chk( 1ll * Ans * chk( Ans - 1 + Mod ) ) * 25561994ll );
    }
    void Build2( char *str ) {
        Init( );
        int len = strlen( str );
        for( int i = len - 1 ; i >= 0 ; i -- )
            L[ i ] = Extend( str[ i ] );
    }

    int Calc( ) {
        n --;
        for( int i = n - 1 ; i >= 0 ; i -- )
            L[ i ] = ( L[ i ] + L[ i + 1 ] ) % Mod;
        for( int i = 0 ; i < n ; i ++ )
            Ans = chk( Ans - chk( 1ll * R[ i ] * L[ i + 1 ] ) + Mod );
        return Ans;
    }
}PAM;

int n;
char str[ MAXN + 5 ];
int main() {
    scanf("%d\n%s", &n , str );
    PAM.Build1( str );
    PAM.Build2( str );
    printf("%d", PAM.Calc( ) );
    return 0;
}
```


---

