# [USACO5.1] 乐曲主题Musical Themes

## 题目描述

我们用 $N$（$1 \le N \le 5000$）个音符的序列来表示一首乐曲，每个音符都是 $1 \sim 88$ 范围内的整数，每个数表示钢琴上的一个键。很不幸这种表示旋律的方法忽略了音符的时值，但这项编程任务是关于音高的，与时值无关。

许多作曲家围绕一个重复出现的“主题”来构建乐曲。在我们的乐曲表示法中，“主题”是整个音符序列的一个子串，它需要满足如下条件：

1. 长度至少为 $5$ 个音符。
2. 在乐曲中重复出现（可能经过转调，见下）。
3. 重复出现的同一主题不能有公共部分。

“转调”的意思是主题序列中每个音符都被加上或减去了同一个整数值。给定一段乐曲，计算其中最长主题的长度（即音符数）。

本题时限为 $1$ 秒钟！

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 5.1


## 样例 #1

### 输入

```
30
25 27 30 34 39 45 52 60 69 79 69 60 52 45 39 34 30 26 22 18
82 78 74 70 66 67 64 60 65 80```

### 输出

```
5```

# 题解

## 作者：niiick (赞：16)

楼教主男人八题 AND 2009年集训队论文的例题之一，在POJ上n的范围是20000，dp和hash什么的应该都会被卡，所以后缀数组才是真正的正解

先不考虑转调，马上想到可以**二分**判断长度为mid是否可行

先求出字符串的height数组，然后在height上分组

每组是height上**连续的一段**，且其中**除第一个以外**所有height值都**不小于mid**（无法满足的就自己单独一个组）

满足这两点的情况下**使一组尽量长**，
比如这样(图片也出自论文)
![在这里插入图片描述](https://i.loli.net/2018/12/06/5c08efd719dc9.png)

我们只需要检查是否存在一组，
满足其中**最大的sa-最小的sa>mid**，若满足即可行

因为按这样分组，**组内任意两个后缀的lcp长度都不会小于mid**

现在考虑转调，其实也很简单

我们只需要在原音乐序列的**差分数组**上求height即可

因为若原序列有两个子段的差分序列一样，那么他们一定可以通过加/减同一个数得到

(再次注意转调**不是**最大的sa-最小的sa+1>mid，因为我们要在原序列的**差分数组**上求height)


***********

```cpp
//niiick
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
typedef long long lt;

int read()
{
    int x=0,f=1;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return x*f;
} 

const int maxn=40010;
int n,m;
int a[maxn];
int rak[maxn],sa[maxn],tp[maxn],tax[maxn];
int height[maxn];

void rsort()
{
    for(int i=0;i<=m;++i) tax[i]=0;
    for(int i=1;i<=n;++i) tax[rak[i]]++;
    for(int i=1;i<=m;++i) tax[i]+=tax[i-1];
    for(int i=n;i>=1;--i) sa[tax[rak[tp[i]]]--]=tp[i];
}

void ssort()
{
    m=210;
    for(int i=1;i<=n;++i)
    rak[i]=a[i],tp[i]=i;
    
    rsort();
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(int i=n-k+1;i<=n;++i) tp[++p]=i;
        for(int i=1;i<=n;++i) if(sa[i]>k) tp[++p]=sa[i]-k;
        
        rsort();
        swap(rak,tp);
        rak[sa[1]]=p=1;
        for(int i=2;i<=n;++i)
        rak[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+k]==tp[sa[i-1]+k])?p:++p;
        if(p>=n) break;
        m=p;
    }
}

void getH()
{
    int k=0;
    for(int i=1;i<=n;++i)
    {
        if(k) k--;
        int j=sa[rak[i]-1];
        while(a[i+k]==a[j+k]) k++;
        height[rak[i]]=k;
    }
}

int check(int x)
{
    int mx=sa[1],mi=sa[1];
    for(int i=2;i<=n;i++)
    {
        if(height[i]<x) mx=mi=sa[i];
        else
        {
            if(sa[i]<mi) mi=sa[i];
            if(sa[i]>mx) mx=sa[i];
            if(mx-mi>x) return 1;
        }
    }
    return 0;
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
    	if(n==0) break;
    	for(int i=1;i<=n;++i) a[i]=read();
    	for(int i=1;i<n;++i) a[i]=a[i+1]-a[i]+90;
    	n--;//差分数组长度少1
    	
    	ssort(); getH();
    	
    	int ans=0;
        int L=0,R=n,mid;
        while(L<R)
        {
            mid=L+R>>1;
            if(check(mid)) ans=mid,L=mid+1;
            else R=mid;
        }
        if(ans<4) printf("0\n");
        else printf("%d\n",ans+1);
    }
    return 0;
}
```


---

## 作者：「QQ红包」 (赞：9)

一道比较简单的dp题

f[i][j]表示以 第一个部分以第i个字符为结尾，第二个部分以第j个字符为结尾，主题的长度。

dp转移方程f[i][j]=f[i-1][j-1]+1（a[i]-a[i-1]==a[j]-a[j-1]）

                  f[i][j]=1(a[i]-a[i-1]!=a[j]-a[j-1])

然而不能有重叠部分，我们可以发现，f[i][j]最大为j-i，所以要加个限制f[i-1][j-1]+1<=j-i

然后开5k\*5k的数组会炸（在usaco上），所以用滚动数组（多棒）

```cpp
/*
ID: ylx14271
PROG: theme 
LANG: C++     
*/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int a[5010];
int i,j,k,n;
int f[2][5010]; 
int ans;
int main()
{
    freopen("theme.in","r",stdin);
    freopen("theme.out","w",stdout);
    scanf("%d",&n);
    for (i=1;i<=n;i++) scanf("%d",&a[i]);//读入
    for (i=1;i<n-4;i++)//因为长度最大为5，所以只搞到n-4
        for (j=i+1;j<=n;j++)//不能重叠，所以i+1开始
        {
            if (a[i]-a[i-1]==a[j]-a[j-1]&&f[(i-1)%2][j-1]+1<=j-i)
            f[i%2][j]=f[(i-1)%2][j-1]+1; else f[i%2][j]=1;
            ans=max(ans,f[i%2][j]);
        }
    if (ans<5) ans=0;
    printf("%d\n",ans);//输出
    return 0;
}
```

---

## 作者：CTime_Pup_314 (赞：6)

更好的阅读体验

[CTime_Pup_314的博客](https://ctp314.github.io/)

# [P2743 [USACO5.1]乐曲主题Musical Themes](https://www.luogu.org/problemnew/show/P2743)

>**求不重叠的最长重复子串**，其中两个字符串相等的条件变为相同位置两字符差值一定


首先，我们需要解决被重新定义的匹配的问题，相同位置字符差值一定，那么同一个字符串相邻差值与另一个位置的差值相等

例如：1 2 3 5 与 3 4 5 2 两个字符串转成查分后变为 1 1 2 与 1 1 -3  那么 1 2 3 与 3 4 5 相等， 就可以又 1 1 与 1 1 相等得出

即问题变为在差分数组下求原定义的相等的不重叠最大子串，需注意的是差分数组的子串长度+1才是原子串

其次，我们要知道，最大重复子串即为height数组里的最大值，这不难证明，因为重复子串必定是任意两后缀的LCP，而LCP就对应的是height数组一段连续区间的最小值，必定小于等于height的最大值

而现在题目要求不重叠，对长度k进行二分，将问题变为判定长为k的不重叠重复子串的存在问题

所以我们把height值大于等于k的归在一组，只有这样才存在至少长为k的不重叠子串，该组内sa的最大值与最小值的差若小于等于k，就存在

按height分组是常见方法，如图

![按height分组](https://ctp314.github.io/2019/02/21/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E5%8D%81%E4%B8%89%E9%A2%98/SA_1.png)

实现格式较固定

```cpp
for(int i = 1; i <= n; ++i)
{        
    if(height[i] < k) maxv = -INF, minv = INF;// 重新更新 
    // 每一组内维护的信息
    // 判断是否合法
}

```

因此第一道题就解决了

差分转化

```cpp
n = read();
for(int i = 1; i <= n; ++i) a[i] = read();
for(int i = 1; i <= n; ++i) s[i] = a[i]-a[i-1]+100; // 防止负数
```

判断二分答案合法

```cpp
bool valid(int k)
{
    int maxv = -INF, minv = INF;
    for(int i = 1; i <= n; ++i)
    {        
        if(height[i] < k) maxv = -INF, minv = INF;        
        maxv = max(sa[i], maxv);
        minv = min(sa[i], minv);
        if(maxv-minv > k) return true; //注意为小于k，因为这是差分数组
    }
    return false;
}
```

二分答案

```cpp
int l = 0, r = n;
while(l <= r)
{
    int mid = (l+r)>>1;
    if(valid(mid)) l = mid+1, ans = mid;
    else r = mid-1;
}
++ans;
if(ans < 5) ans = 0; // 按题意判断
printf("%d\n", ans);
```

---

## 作者：Danny_boodman (赞：5)

## 哈希大法吼！

这道题不需要用后缀数组这些~~花里胡哨~~的，用纯noip内容的hash+二分是可以~~水~~过的。

首先我们发现我们需要寻找最长的一种没有公共部分的重复出现的子串，使这个串中数字之间的差不变。那我们将这n个数前后做差，得到另一个长度是n-1的序列。问题转化为求出这个序列的最长重复子串，且这些子串不能重叠。

我们发现这种串的长度满足单调性，所以考虑二分串的长度，至于如何判断重复的子串，就用hash处理整个串，使我们的hash满足前缀和的性质，到时候相减进行判断就行了。

让我们看看如何~~乱搞~~构造一个好的hash

1.首先，你需要一个unsigned long long来防止hash值策马奔腾而爆掉

2.然后，开始乱搞，越乱越好，把想要卡你hash的数据秀晕

3.之后取个模，装入链表或vector以便于查找

我的hash是这样的：

假设有一串数1,2,3,4,5

先随便设一个几千的值x（比如你的生日？）

| hash(1)     | hash(2)     | hash(3)     | hash(4)     | hash(5)     |
| :---- | :---- | :---- | :---- | :---- |
| hash(2)+1 |       |       |       |       |
| | hash(3)*x+2 |       |       |       |
| | | hash(2)*x+3 |       |       |
| |  |  | hash(4)*x+4 |       |
| |  |  |  | 5 |

其实也就是这个

$hash(5)=5*x^0$

$hash(4)=5*x^1+4*x^0$

$hash(3)=5*x^2+4*x^1+3*x^0;$

$hash(2)=5*x^3+4*x^2+3*x^1+2*x^0$

$hash(1)=5*x^4+4*x^3+3*x^2+2*x^1+1*x^0;$


总通式:$H(i)=s[n]x^{n-i}+s[n-1]x^{x-i-1}+......+s[i+1]x+s[i]$

因为$hash$值只与$s[i]~s[i+L-1]$和$L$有关，所以就可以为所欲为了

最后送一句话

>Hash的精髓在于乱搞——叶某富

```
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;
typedef unsigned long long ull;
const int N=200010;
const int mod=2007;
const ull Rand=5201;
struct ss{
    ull zhi;int pos;
    ss(ull a,int b)
    {
        zhi=a;pos=b;
    }
};
vector<ss> G[mod];
int n,tlen,ans;
ull Hash[N],base[N];
int data[N],tmp[N];
void Init()
{
    base[0]=1;
    for(int i=1;i<n;i++)
    tmp[i]=data[i+1]-data[i];
    tlen=n-1;
    for(int i=1;i<n;i++)
    {
        Hash[i]=Hash[i-1]*Rand+tmp[i];
        base[i]=base[i-1]*Rand;
    }
}
int query(ull v,int wei,int l)
{
    int x=v%mod;
    G[x].push_back(ss(v,wei));
    for(int i=0;i<G[x].size();i++)
    if(G[x][i].zhi==v&&wei-G[x][i].pos>=l+1)
    return 1;
    return 0;
}
int check(int l)
{
    l--;
    for(int i=0;i<mod;i++)
    G[i].clear();
    int flag=0;
    for(int i=1;i<=tlen-l+1;i++)
    {
        ull v=Hash[i+l-1]-Hash[i-1]*base[l];
        if(query(v,i,l))
        {
            flag=1;return 1;
        }
    }
    return 0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    scanf("%d",&data[i]);
    Init();
    int l=5,r=n;
    while(l<r)
    {
        int mid=(l+r)/2;
        if(check(mid))
        {
            ans=mid;
            l=mid+1;
        }
        else
        r=mid;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：3)

$SAM$ 好题。

考虑把源序列进行差分，设原序列为 $A_1, A_2, \dots, A_N$，那么差分后就是 $A'_i=A_{i+1}-A_i$。

如果存在一段 $[l,r]$ 满足存在一段 $[l',r']$ 使得 $r+1 < l'$ 并且 $A'_l=A'_{l'}\ \wedge\ A'_{l+1}=A'_{l'+1}\ \wedge\dots\wedge\ 
A'_r=A'_{r'}$，那么在原序列的区间 $[l-1,r]$（和 $[l'-1,r]$）形成一个主题。

注意需要 $r+1 < l'$，而不是 $r < l'$，应为如果 $r+1=l'$ 那么两个区间在原序列对应的区间会重叠。

把 $A'$ 当成一个字符串然后用 SAM 维护子串的最小 $r$，最大 $r$，然后输出判断最大合法子串 $+1$ 是否大于等于 $5$ 就好了。

（感觉应该出一个加强版，$N\le 2\cdot10^5$。。。）

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

// begin fast read template by CYJian (source: https://www.luogu.com.cn/paste/i11c3ppx)

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

// end fast read template by CYJian

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
//const int MOD = 1000000007;

namespace SAM {
	constexpr int MAXN = 5005;
	constexpr int MAXT = 177;
	struct state {
		int len, lnk, fpo;
		int nxt[MAXT];
	} st[MAXN*2];
	int sz, last;
	int mknode(int fro = -1) {
		int nd = sz++;
		if(fro == -1) memset(st[nd].nxt, -1, sizeof st[nd].nxt);
		else {
			memcpy(st[nd].nxt, st[fro].nxt, sizeof st[nd].nxt);
			st[nd].lnk = st[fro].lnk;
			st[nd].fpo = st[fro].fpo;
		}
		return nd;
	}
	void init() {
		sz = last = 0;
		mknode(); st[0].len = 0, st[0].lnk = -1;
	}
	void ext(int c) {
		int cur = mknode();
		st[cur].len = st[last].len+1;
		st[cur].fpo = st[cur].len-1;
		int p = last;
		while(p != -1 && st[p].nxt[c] == -1) st[p].nxt[c] = cur, p = st[p].lnk;
		if(p == -1) st[cur].lnk = 0;
		else {
			int q = st[p].nxt[c];
			if(st[p].len + 1 == st[q].len) st[cur].lnk = q;
			else {
				int cl = mknode(q); 
				st[cl].len = st[p].len + 1; st[cur].lnk = st[q].lnk = cl;
				while(p != -1 && st[p].nxt[c] == q) st[p].nxt[c] = cl, p = st[p].lnk;
			}
		}
		last = cur;
	}
	vector<int> revlnk[MAXN*2];
	int lpo[MAXN*2], ans;
	int dfs(int p) {
		lpo[p] = st[p].fpo;
		for(int& v:revlnk[p]) lpo[p] = max(lpo[p], dfs(v));
		if(((st[p].lnk==-1)?0:(st[st[p].lnk].len+1))<=min(st[p].len,min(lpo[p]-st[p].fpo-1, st[p].fpo+1)))
			ans = max(ans,min(st[p].len,min(lpo[p]-st[p].fpo-1,st[p].fpo+1)));
		return lpo[p];
	}
	int makelpo() {
		rep1(i, sz-1) revlnk[st[i].lnk].pb(i);
		ans = 0;
		dfs(0);
		return ans;
	}
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; gi(n);
	int prev = -1;
	SAM::init();
	rep(i, n) {
		int v; gi(v);
		if(i) SAM::ext(v - prev + 87);
		prev = v;
	}
	int v = SAM::makelpo()+1;
	print((v<5)?0:v);
}

```

---

## 作者：Celebrate (赞：2)

这一道题暴力肯定是不行的（我也不会打暴力）

我一看到只要是重复出现的就可以了，就灵机一动，想到了

DP（也可以说是递推），f[i][j]表示以i开头和j开头的最大值
```cpp
#include<bits/stdc++.h>
#define MAXN 5100
using namespace std;
int n,a[MAXN];
int f[MAXN][MAXN];
int maxx;
int main()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;++i) scanf("%d",&a[i]);//输入 
	for(i=1;i<=n-5;++i)//枚举两个顶点 
	{
		for(j=i+5;j<=n;++j)//最小有5个 
		{
			if(a[i]-a[i-1]==a[j]-a[j-1])//如果变化幅度相同 
			{
				f[i][j]=min(j-i-1,f[i-1][j-1]+1);//这里不用f[i][j]是因为f[i][[j]开始肯定是0，还有就是这个值在怎么大也不能重复 
				maxx=max(maxx,f[i][j]);//记录最大值 
			}
		}
	}
	if(maxx>=4) printf("%d\n",maxx+1);//输出 
	else		printf("0\n");//记得这里没有记录头，只记录了后面，所以要+1 
	return 0;
}
```

---

## 作者：void_zxh (赞：2)

来一发后缀数组的题解。。

后缀数组是啥，请见国家集训队论文。。。。其实我只是个弱鸡。。。。。（逃~~~~）

··




    


    

        
```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int _rank[20005],wb[20005],wv[20005],wss[20005];
int n;
int height[20005],sa[20005];
inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c<'0' || c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0' && c<='9')
    {
        x=x*10+c-48;
        c=getchar();
    }
    return x*f;
}
bool cmp(int *r,int a,int b,int l)  
{  
    return r[a]==r[b] && r[a+l]==r[b+l];  
}  
void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=_rank,*y=wb,*t;
    for(i=0;i<m;i++) wss[i]=0;
    for(i=0;i<n;i++) wss[x[i]=r[i]]++;
    for(i=1;i<m;i++) wss[i]+=wss[i-1];
    for(i=n-1;i>=0;i--)
        sa[--wss[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<m;i++) wss[i]=0;
        for(i=0;i<n;i++) wss[wv[i]]++;
        for(i=1;i<m;i++) wss[i]+=wss[i-1];
        for(i=n-1;i>=0;i--) sa[--wss[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
        x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}
void calheight(int *r,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++)    _rank[sa[i]]=i;
    for(i=0;i<n;height[_rank[i++]]=k)
        for(k?k--:0,j=sa[_rank[i]-1];r[i+k]==r[j+k];k++); 
}
bool judge(int k,int n)
{
    int i,mx,mi;
    mx=mi=sa[1];
    for(i=2;i<=n;i++)
    {
        if(height[i]>=k&&i<=n)
        {
            mi=min(mi,sa[i]);
            mx=max(mx,sa[i]);
            if(mx-mi>k)    return 1;
            continue;
        }
            mx=mi=sa[i];
    }
    return 0;
}
int main()
{
    int s[20005],r1[20005];
    int l,i;
    scanf("%d",&l);
        for(i=0;i<l;i++)
            scanf("%d",&s[i]); 
        for(i=0;i<l-1;i++)    s[i]=s[i+1]-s[i]+100;
        for(i=0;i<l;i++)    r1[i]=s[i];
        r1[--l]=0;
        da(r1,sa,l+1,200);
        calheight(r1,l);
```
/\*
不可重叠最长重复子串

    
二分一个答案k，然后对height进行分组。。。

有希望成为最长公共前缀不小于k的两个后缀一定在同一组。

然后对于每组后缀，

只须判断每个后缀的sa值的最大值和最小值之差是否不小于k。

如果有一组满足，则说明存在，否则不存在。

时间复杂度为O(nlogn)。

\*/

        
```cpp
    /*for(i=0; i<l; i++)  // _rank[i] : suffix(i)排第几  
        printf("_rank[%d] =  %d\n",i,_rank[i]);  
    printf("\n");  
    for(i=1; i<=l; i++)   // sa[i] : 排在第i个的是谁  
        printf("sa[%d] =  %d\n",i,sa[i]);
    printf("\n");
    for(i=1; i<=l; i++)   // height[i]：suffix(sa[i-1])和suffix(sa[i])的最长公共前缀，也就是排名相邻的两个后缀的最长公共前缀
        printf("height[%d] =  %d\n",i,height[i]); */
        int li=4,ri=l/2,mid;
        int ans=0;
        while(li<=ri)
         {
              mid=(li+ri)/2;
                if(judge(mid,l))
            {
                ans=mid;
                    li=mid+1;
            }
            else    
                ri=mid-1;
        }
        ans++;
        printf("%d\n",ans<5?0:ans);
    return 0;
}
··
```

---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2743)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先，很容易看出，转调这个东西可以用差分来消除影响。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后问题就变成了求原串中最长的相同子串。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;不难看出可以用后缀数组+高度数组求解。先把这两个东西预处理出来，然后来一个$O(n^2)$的枚举，枚举的是两个串的起点。然后$RMQ$查询$LCP$的重复长度，然后注意特判一下重复长度$\ge5$和相交与否，~~然后幸好数据小不然就会T~~，然后就过了。  
# 代码
```cpp
#include <cmath>
#include <cstdio>

const int MAXN = 5005, MAXSIZ = 5005, MAXLOG = 25;
//不知为何MAXSIZ开小了一直RE，所以才开得和N一样大

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int RMQ[MAXN][MAXLOG];
int cnt[MAXSIZ], rnk[MAXN * 4], tmp[MAXN * 4], sa[MAXN], height[MAXN];
int a[MAXN], dif[MAXN];
int N, lg2;

bool equal( const int x, const int y, const int s )
{
	return rnk[x] == rnk[y] && rnk[x + s] == rnk[y + s];
}

void init()
{
	for( int j = 1 ; j <= lg2 ; j ++ )
	{
		for( int i = 1 ; i + ( 1 << ( j - 1 ) ) <= N ; i ++ )
		{
			RMQ[i][j] = MIN( RMQ[i][j - 1], RMQ[i + ( 1 << ( j - 1 ) )][j - 1] );
		}
	}
}

int LCP( const int l, const int r )
{
	if( l == r ) return N - l + 1;
	int x = rnk[l], y = rnk[r];
	if( x > y ) x ^= y, y ^= x, x ^= y;
	x ++;
	int k = log2 ( y - x + 1 );
	return MIN( RMQ[x][k], RMQ[y - ( 1 << k ) + 1][k] );
}

int main()
{
	int upper = 0;
	read( N );
	lg2 = log2( N );
	for( int i = 1 ; i <= N ; i ++ )
	{
		read( a[i] );
		dif[i] = a[i] - a[i - 1] + 100;
        //避免出现负数下标
		upper = MAX( upper, dif[i] );
	}
	for( int i = 1 ; i <= N ; i ++ )
	{
		cnt[dif[i]] = 1;
	}
	for( int i = 1 ; i <= upper ; i ++ )
	{
		cnt[i] += cnt[i - 1];
	}
	for( int i = 1 ; i <= N ; i ++ )
	{
		rnk[i] = cnt[dif[i]];
	}
	int las = cnt[upper], p = 0;
	for( int k = 1 ; k < N ; k <<= 1 )
	{
		for( int i = 1 ; i <= las ; i ++ ) cnt[i] = 0;
		for( int i = 1 ; i <= N ; i ++ ) cnt[rnk[i + k]] ++;
		for( int i = 1 ; i <= las ; i ++ ) cnt[i] += cnt[i - 1];
		for( int i = N ; i >= 1 ; i -- ) tmp[cnt[rnk[i + k]] --] = i;
		for( int i = 1 ; i <= las ; i ++ ) cnt[i] = 0;
		for( int i = 1 ; i <= N ; i ++ ) cnt[rnk[tmp[i]]] ++;
		for( int i = 1 ; i <= las ; i ++ ) cnt[i] += cnt[i - 1];
		for( int i = N ; i >= 1 ; i -- ) sa[cnt[rnk[tmp[i]]] --] = tmp[i];
		las = 0;
		for( int i = 1 ; i <= N ; i ++ ) 
		{
			if( ! equal( sa[i], sa[i - 1], k ) ) las ++;
			tmp[sa[i]] = las;
		}
		for( int i = 1 ; i <= N ; i ++ ) rnk[i] = tmp[i];
	}
	p = 0;
	for( int i = 1, j ; i <= N ; i ++ )
	{
		if( rnk[i] == 1 ) continue;
		if( p ) p --;
		j = sa[rnk[i] - 1];
		while( i + p <= N && j + p <= N && dif[i + p] == dif[j + p] ) p ++;
		height[rnk[i]] = p;
	}
	for( int i = 1 ; i <= N ; i ++ )
	{
		RMQ[i][0] = height[i];
	}
	init();
	int res = 0, t;
	for( int i = 1 ; i <= N ; i ++ )
	{
		for( int j = i + 1 ; j <= N ; j ++ )
		{
			if( ( t = LCP( i, j ) ) >= 4 && i + t - 1 < j - 1 )
            //注意差分数组转换成对应的原序列长度时得加一，所以是>=4；
			{
				res = MAX( res, t + 1 );
			}
		}
	}
    //枚举两个起点
	write( res ), putchar( '\n' );
	return 0;
}
```

---

## 作者：drophell (赞：1)

最近在学SAM，拿sam也可以做。

题意就是让你求不可重叠最长重复子串，只不过这个字串被加加渐渐了一通，所以不能直接套模板

~~结合物理~~就像势能一样，势能大小可以随意定，但是势能差恒定，所以我们转化一下，

要 5个连续音符主题 等价于 有连续4次的重复变化
所以做差

然后考虑Right集合定义:

1、满足“不可重叠”这一条件就需要|Right|>=2，每一个叶子所代表的Right是不相交的。

2、得出每个结点的right集合，就能得到这些串的出现位置，right集合就是在PARENT树中 子树内结束结点的并集，我们不需要并集，只需要满足条件的串的区间长度

3、可以dp出right集合中的最大值/最小值，差值和maxlen取较小值就是到该结点串符合题意的最长长度。

然后就做出来了

~~着实感觉需要特别明白那些晦涩的定义才能灵活应用。~~



```cpp
#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define ll unsigned long long
#define mem(a,b) memset(a,b,sizeof(a))
#define mec(a,b) memcpy(a,b,sizeof(b))
using namespace std;
const int  MAXN=50000+50;
int n;
int str[MAXN];
ll ans;
struct SAM
{
    int tot,last,cur;
    int fa[MAXN*2],ts[MAXN*2][180];
    int ln[MAXN*2],sz[MAXN*2],c[MAXN],q[MAXN*2];
    int l[MAXN*2],r[MAXN*2];
    void init(){fa[tot=last=1]=0;mem(l,0x3f);}
    //
    //
    inline void extend(int x,int id)
    {
        int p,q,tmq;
        cur=++tot;ln[cur]=ln[last]+1;sz[cur]=1;l[cur]=r[cur]=id;
        for(p=last;p&&!ts[p][x];p=fa[p])
            ts[p][x]=cur;
        if(p==0)fa[cur]=1;
        else 
        {
            if(ln[p]+1==ln[q=ts[p][x]])fa[cur]=q;
            else 
            {
                tmq=++tot;
                ln[tmq]=ln[p]+1;
                fa[tmq]=fa[q];
                fa[cur]=fa[q]=tmq;
                mec(ts[tmq],ts[q]);
                for(;ts[p][x]==q;p=fa[p])ts[p][x]=tmq;
            }
        }
        last=cur;
    }
    void sort()
    {
        for(int i=0;i<=n;i++)c[i]=0;
        for(int i=1;i<=tot;i++)c[ln[i]]++;
        for(int i=1;i<=n;i++)c[i]+=c[i-1];
        for(int i=tot;i>=1;i--)q[c[ln[i]]--]=i;
    }
    void solve()
    {
    	int ans=0;
    	for(int i=tot,u=q[i],f=fa[u],t;i>=1;u=q[--i],f=fa[u])
    	{
    		sz[f]+=sz[u];
    		l[f]=min(l[f],l[u]),r[f]=max(r[f],r[u]);
    		if(sz[u]>=2&&(t=min(ln[u],r[u]-l[u]-1))>=4)
    			ans=max(ans,t);
    		if(ln[u]<4)break;
    	}
    	printf("%d",ans<4?0:ans+1);
    }
    
}sam;
int main()
{
    
    scanf("%d",&n);
    sam.init();
    int past;scanf("%d",&past);n--;
    for(int i=1,x;i<=n;i++)
    {
    	scanf("%d",&x);str[i]=x-past+88;past=x;
    	//printf("%3d",str[i]);
    	sam.extend(str[i],i);
    }
    sam.sort();sam.solve();
    
    return 0;
        
}
```

---

## 作者：L_M_ (赞：0)

提供一个也许能过n <= 20000的哈希做法

常规套路，我们求出原串哈希值，然后二分答案mid，依次枚举每个位置起始，长为mid的串是否出现过，然后用map维护串的上一次的开始位置，复杂度O(nlog^2n)

对于转调，处理原数组的差分数组即可

然后这里有一个问题，哈希值容易重复。根据某（其实是我忘了叫啥的概率模型）：值域在[0,mod]的哈希值，对于[0,20000]次的询问，冲突的概率其实很大，只是因为luogu上数据小，所以能过

解决这一问题的方法是双哈希。选择两个模数作为哈希，开两个map分别维护两个哈希值，map里维护<ll,pair>，pair里存位置和这个点的另一个哈希值。然后在算某个位置的哈希值的时候呢，你将两个哈希值都算出来，哪个能够和两个都匹配上，哪个就是正确的

这样的出错概率就很小了

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath> 
#include<iostream>
#include<map>
using namespace std;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << "  ";
#define B cout << "breakpoint" << endl;
#define pii pair<ll,int>
#define mp make_pair
typedef double db;
typedef long long ll;
inline int read()
{
    int ans = 0,op = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') op = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        (ans *= 10) += ch - '0';
        ch  = getchar();
    }
    return ans * op;
}
const int maxn = 5005;
const ll b = 5505;
const ll mod0 = 998244353;
const ll mod1 = 19260817;
ll hash[maxn][2],base[maxn][2];
int a[maxn],val[maxn];
int n;
bool check(int l)
{
    l--;
    map<ll,pii> m0,m1;
    for(int i = 1;i <= n - l;i++)
    {
        ll tp0 = (hash[i + l - 1][0] - hash[i - 1][0] * base[l][0] % mod0 + mod0) % mod0;
        ll tp1 = (hash[i + l - 1][1] - hash[i - 1][1] * base[l][1] % mod1 + mod1) % mod1;
        if(m0[tp0].second)
        {
        	pii u0 = m0[tp0];
        	ll val0 = u0.first,lt = u0.second;
        	if(val0 == tp1 && i - lt >= l + 1) return 1;
        }
        if(m1[tp1].second)
        {
        	pii u1 = m1[tp1];
        	ll val1 = u1.first,lt = u1.second;
        	if(val1 == tp0 && i - lt >= l + 1) return 1;
        }
        if(!m1[tp1].second && !m0[tp0].second) 
        {
        	m0[tp0] = mp(tp1,i);
        	m1[tp1] = mp(tp0,i);
        }
    }
    return 0;
}
int main()
{
    n = read();
    base[0][0] = base[0][1] = 1;
    for(int i = 1;i <= n;i++)
        val[i] = read();
    for(int i = 1;i < n;i++)
    {
        a[i] = val[i + 1] - val[i] + 88;
        base[i][0] = (base[i - 1][0] * b) % mod0;
        hash[i][0] = (hash[i - 1][0] * b % mod0 + (ll)a[i]) % mod0;
        base[i][1] = (base[i - 1][1] * b) % mod1;
        hash[i][1] = (hash[i - 1][1] * b % mod1 + (ll)a[i]) % mod1;
    }
    int l = 5,r = n;
    int ans = 0;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid))
            l = mid + 1,ans = max(ans,mid);
        else r = mid;
    }
    printf("%d",ans);
}
        

```




---

## 作者：Drinkwater (赞：0)

我只能说我的方法非常特别，打完一个O(n^3)的暴力以后发现有79分，好神奇，然后我开始想怎么优化暴力，然后发现了一个巧妙的性质我们用一个数组dp[i][j]代表以i开头和以j开头的子串的最大主题长度，我们会发现，如果你要求dp[i][j]的值，可以从上一次dp[i-1][j-1]推过来，什么意思呢？就是你从i-1，j-1开始,发现有dp[i-1][j-1]这么长的重复长度，那我们就没必要从i，j开始算，直接从i+dp[i-1][j-1]-1,j+dp[i-1][j-1]-1开始算就可以了，这样省去了很多没必要的比较，有点类似KMP的思想，这样应该可以达到近似O（n^2），速度也不慢。

/*************************************************************************

    > File Name: 乐曲主题.cpp
    > Author: Drinkwater-cnyali
    > Created Time: 2017/5/7 23:00:41
************************************************************************/







```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define mem(a, b) memset((a), b, sizeof(a))
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int maxn = 5010;
int n;
int a[maxn],ans;
int dp[maxn][maxn];
int main()
{
    n = read();
    REP(i,1,n)a[i] = read();
    for(int i=1;i<=n-5;++i)
    {
        for(int j=i+5;j<=n;j++)
        {
            int c = a[i] - a[j];
            int sum = max(dp[i-1][j-1]-1,0);
            int len = max(dp[i-1][j-1]-1,0);
            for(int l=i+len,r=j+len;
                    l<=min(j-1,n)&&r<=n;++l,++r)
            {
                if(a[l] != a[r] + c)break;
                if(a[l] == a[r] + c)sum++;
                ans = max(ans,sum);
            }
            dp[i][j] = sum;
        }
    }
    if(ans < 5)puts("0");
    else printf("%d",ans);
    return 0;
}

```

---

## 作者：Vin_1999 (赞：0)

我去我居然一开始用二分答案做，没看出来这是最长公共子串dp的变体。（请关爱弱智儿童）





```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<climits>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
const int maxn=5010;
```
static int dp[maxn][maxn],cha[maxn],a[maxn],n,



```cpp
                      ans;
inline void init()
{
    scanf("%d",&n);
    rep(i,1,n) scanf("%d",&a[i]);
    rep(i,1,n-1) rep(j,i+1,n) dp[i][j]=dp[j][i]=1;
    rep(i,2,n) cha[i]=a[i]-a[i-1];
}
int main()
{
  freopen("e:/in.txt","r",stdin);
     init();
     rep(i,2,n)
       rep(j,i+1,n)
       if(cha[i]==cha[j]&&j-i>dp[i-1][j-1])
    {
        dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
        ans=max(dp[i][j],ans);
        }
  printf("%d",ans>4 ? ans:0);
  return 0;
}//by lyyz-ljy
```

---

## 作者：GoldenPotato137 (赞：0)

[戳我获得更好的阅读体验qwq](https://www.goldenpotato.cn/%E5%AD%97%E7%AC%A6%E4%B8%B2/luogu-p2743-usaco5-1%E4%B9%90%E6%9B%B2%E4%B8%BB%E9%A2%98musical-themes/)

---
# Solution
这题可以用哈希做，也可以用SA做。下面我们分别讲一下两种做法。

### 哈希
首先，我们把转掉的问题处理掉。我们考虑把原串做差分数组，即用后面那一个减去前面那一个。这样子，我们直接在新的串上找完全相同的两个不可重叠子串即可。

这个，我们考虑先在外面二分一个答案的长度，然后暴力做，从后往前扫，把所有子串都丢到哈希表里面，插入一个新的串之前，就检查一下之前是否有这个串，如果有的话，就检查一下是否满足相隔长度是否大于mid即可。

时间复杂度$O(nlogn)$


### 后缀数组
这题的后缀数组做法就比较妙了。

首先，我们还是要做差分数组的。
然后，我们还是要求出SA及height的(不会SA的小伙伴可以看[这里](https://www.goldenpotato.cn/字符串/后缀数组sa学习笔记/))
然后，我们仍然是在外面二分答案，然后考虑怎么检查。

因为每个串不可重复，我们可以考虑把height数组分组，我们希望一个组尽可能长，并且组内所有元素的$height>=mid$，这样子，如果这个组里面有两个原数的sa相隔超过mid，则说明这个结果是正确的。

时间复杂度$O(nlogn)$

---
# Code
sa做法纯属yy，如果讲爆了还请各位dalao指出qwq

我写的双模hash，而且没有使用哈希表，用的是set，总复杂度$O(nlog^2n)$
```cpp
#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
const int N=20000+100;
const int E=233;
const int P2=2333333333;
int n;
unsigned long long POW[N];
long long POW2[N],c[N];
void Init()
{
    POW2[0]=POW[0]=1;
    for(int i=1;i<=n;i++)
        POW[i]=POW[i-1]*E,
        POW2[i]=(POW2[i-1]*E)%P2;
}
struct rec
{
    unsigned long long hash;
    long long hash2;
    int t;
    friend bool operator < (rec a,rec b)
    {
        if(a.hash==b.hash)
            return a.hash2<b.hash2;
        return a.hash<b.hash;
    }
};
set <rec> record;
bool Check(int ans)
{
    record.clear();
    unsigned long long hash=0;
    long long hash2=0;
    for(int i=1;i<=ans;i++)
    {
        hash=hash+c[i]*POW[ans-i+1];
        hash2=(hash2+c[i]*POW2[ans-i+1])%P2;	
    }
    record.insert((rec){hash,hash2,ans});
    for(register int i=ans+1;i<n;i++)
    {
        hash=(hash-c[i-ans]*POW[ans])*E+c[i]*E;
        hash2=((((hash2-c[i-ans]*POW2[ans])*E+c[i]*E)%P2)+P2)%P2;
        set <rec> :: iterator p=record.lower_bound((rec){hash,hash2,0});
        if((*p).hash==hash and (*p).hash2==hash2)
        {
            if(i-(*p).t>=ans)
                return true;
        }
        else
            record.insert((rec){hash,hash2,i});
    }		
    return false;
}
int main()
{
    scanf("%d",&n);
    for(register int i=1;i<=n;i++)
        scanf("%lld",&c[i]);
    for(register int i=1;i<n;i++)
        c[i]=c[i+1]-c[i];
    Init();
    
    int L=4,R=n,mid,ans=0;
    while(L<=R)
    {
        mid=(L+R)>>1;
        if(Check(mid)==true)
            ans=mid+1,L=mid+1;
        else
            R=mid-1;
    }
    
    if(ans==6) ans++;
    printf("%d",ans);
    return 0;
}

```






---

