# Bits And Pieces

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$。

你需要在所有满足 $i < j < k$ 的三元组 $(i, j, k)$ 中，找到表达式 $a_{i} | (a_{j} \& a_{k})$ 的最大值。

其中 $\&$ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)，$|$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。

## 说明/提示

在第一个样例中，唯一可能的三元组是 $(1, 2, 3)$，因此答案为 $2 | (4 \& 6) = 6$。

在第二个样例中，共有 $4$ 个可能的三元组：

1. $(1, 2, 3)$，其值为 $2|(8\&4) = 2$。
2. $(1, 2, 4)$，其值为 $2|(8\&7) = 2$。
3. $(1, 3, 4)$，其值为 $2|(4\&7) = 6$。
4. $(2, 3, 4)$，其值为 $8|(4\&7) = 12$。

因此最大值为 $12$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 4 6
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
2 8 4 7
```

### 输出

```
12
```

# 题解

## 作者：juju527 (赞：17)

### 前置知识

[sosdp](https://codeforces.com/blog/entry/45223)

即求子集和与超集和

原理为高维前缀和

### $\texttt{Solution}$

由于有三个变量，考虑枚举一个较特殊的i

补集转化一波，问题变为 $\max\{ \overline{a_i}\And a_j\And a_k+a_i\}$,$\overline{a_i}$为 $a_i$ 补集

考虑按位贪心

我们只需要求某个集合的超集中是否有至少两个下标大于i的元素

满足这次贪心就成立

故我们做一遍sosdp，记录超集的最大元素位置和次大元素位置即可

时间复杂度 $O(nlogw)$

代码简单易懂

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int a[maxn];
int read(){
    int x=0,y=1;
    char ch=getchar();
    while(ch<48||ch>57){if(ch==45)y=-1;ch=getchar();}
    while(ch>=48&&ch<=57)x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*y;
}
int mx[(1<<21)],cx[(1<<21)];
inline void update(int k,int x){
	if(mx[k]<x){cx[k]=mx[k];mx[k]=x;}
	else if(mx[k]==x)cx[k]=x;
	else cx[k]=max(cx[k],x);
	return ;
}
void sos(int len){
	for(int i=0;i<21;i++)
		for(int j=0;j<len;j++)
			if(!(j&(1<<i))){
				update(j,mx[j^(1<<i)]);
				update(j,cx[j^(1<<i)]);
			}
	return ;
}
int main(){
    freopen("CF1208F.in","r",stdin);
    freopen("CF1208F.out","w",stdout);
   	int n;
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		update(a[i],i);
	}
	sos(1<<21);
//	for(int i=1;i<(1<<21);i++)cout<<i<<" "<<mx[i]<<" "<<cx[i]<<endl;
	int S=(1<<21)-1,ans=0;
	for(int i=1;i<=n-2;i++){
		int c=S^a[i];
		int s=0;
		for(int j=21;j>=0;j--){
			if(!((c>>j)&1))continue;
			s+=(1<<j);
			if(cx[s]<=i)s-=(1<<j);
		}
		ans=max(ans,a[i]+s);
	}
	printf("%d\n",ans);
    return 0;
}

```

---

## 作者：tzc_wk (赞：13)

[题面传送门](https://codeforces.ml/contest/1208/problem/F)

题意：求 $\max\limits_{i<j<k}a_i|(a_j\&a_k)$。

$1\leq n \leq 10^6,1\leq a_i\leq 2\times 10^6$

u1s1 这题算高维前缀和里不那么 sb 的题，虽然代码也很简单。

很容易想到一个贪心，从高到低枚举每一位，能填 $1$ 就填 $1$，不能填 $1$ 就填 $0$。

于是本题转化为一个问题：是否存在某个 $i,j,k$ 使得 $x$ 为 $a_i|(a_j\&a_k)$ 的子集。枚举 $a_i$ 包含 $x$ 中的哪些位，以及 $a_j\&a_k$ 中包含 $x$ 哪些位，然后贪心地取下标最小的 $i$，以及下标最大的 $j,k$，判断 $i<j$ 即可。

至于怎样求下标最小的 $i$ 和下标最大的 $j,k$。记 $mn_x$ 为下标最小的包含 $x$ 的 $a_i$，$mx_x$ 为下标最大的两个包含 $x$ 的 $a_i$。高位前缀和随便一搞就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1e6;
const int LOG_N=21;
const int LIM=(1<<LOG_N)-1;
int n,a[MAXN+5],tmp[4],mn[LIM+5];
pii mx[LIM+5];
pii merge(pii x,pii y){
	tmp[0]=x.fi,tmp[1]=x.se,tmp[2]=y.fi,tmp[3]=y.se;
	sort(tmp,tmp+4);reverse(tmp,tmp+4);return mp(tmp[0],tmp[1]);
}
bool check(int x){
	for(int i=x;i;i=(i-1)&x) if(mn[x^i]<mx[i].se) return 1;
	return (mn[x]<mx[0].se);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	memset(mn,63,sizeof(mn));
	for(int i=1;i<=n;i++) mn[a[i]]=min(mn[a[i]],i);
	for(int i=1;i<=n;i++) mx[a[i]]=merge(mx[a[i]],mp(i,0));
	for(int i=0;i<LOG_N;i++) for(int j=LIM;~j;j--) if(!(j>>i&1)){
		mn[j]=min(mn[j],mn[j^(1<<i)]);mx[j]=merge(mx[j],mx[j^(1<<i)]);
	}
	int cur=0;for(int i=LOG_N;~i;i--) if(check(cur|(1<<i))) cur|=(1<<i);
	printf("%d\n",cur);
	return 0;
}
```

上帝不要惩罚我刷水题（

---

## 作者：封禁用户 (赞：10)

~~题意:略~~

可以看出，这题可以从后往前进行处理，

统计各子集出现个数，

注意计算时**高位优先**！ 

具体见代码(有注释):
```cpp
#include <bits/stdc++.h>
using namespace std;
int sum[2000010],a[1000010],vis[2000010],n,ans = 0;
void add(int x,int y)//添加子集个数 x数字 y当前标记 
{
	if(sum[x] > 1||vis[x] == y) return;//个数超过一个(没有意义)或者已被访问
	++sum[x];//统计 
	vis[x] = y;//标记 
	for(int i = 0;(1 << i-1) < x;++i) 
		if(x & (1 << i))
			add(x ^ (1 << i),y);//枚举子集		 
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;++i) scanf("%d",&a[i]);//输入 
	add(a[n],n);
	add(a[n-1],n-1);//添加后两个 
	for(int i = n-2;i >= 1;--i)
	{
		int k = 0;
		for(int j = 20;j >= 0;--j)//高位优先 
			if(!(a[i] & (1 << j))&&sum[k ^ (1 << j)] > 1) 
				k ^= 1 << j;
		ans = max(ans,a[i]|k);//统计答案 
		add(a[i],i);//添加 
	}
	printf("%d",ans);//输出 
	return 0;	
}
```


---

## 作者：GavinZheng (赞：8)

# CF1208F Bits And Pieces

[传送门](https://codeforces.com/contest/1208/problem/F)

## 思路

这里要运用SOS-DP的思路（$\text{Sum over Subsets}$）。我在另外一篇博客里介绍过。[SOS_DP](https://www.cnblogs.com/GavinZheng/p/11533990.html)

SOS-DP是记录每个$mask$所有子集的信息，而这道题只需要记录每个$mask$所有超集的信息即可。$dp[mask]$记录的是能满足$mask$是其的子集的所有数中坐标最大的两个。我们枚举$a_i$，然后贪心的按位取就可以了。具体细节可以看代码。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn (int)(5194304)
using namespace std;
int n,a[maxn],mi=0;
struct gg{
	int key1,key2;
	gg(int k1=0,int k2=0){key1=k1,key2=k2;}
}dp[maxn];
void insert(int num,int val){
	if(val>dp[num].key1){
		dp[num].key2=dp[num].key1;
		dp[num].key1=val;
	}
	else if(val>dp[num].key2){
		dp[num].key2=val;
	}
	return;
}
void init(){
	for(int i=1;i<=n;i++)insert(a[i],i);
	for(int i=0;i<=22;i++){
		for(int j=0;j<=2e6;j++){
			if((1<<i)&j){
				insert((1<<i)^j,dp[j].key1);
				insert((1<<i)^j,dp[j].key2);
			}
		}
	}
}
bool test(int mask,int num){
	if(dp[mask].key2>=num)return 1;
	return 0;	
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	init();
	for(int i=1;i<=n-2;i++){
		int check=0;
		for(int j=21;j>=0;j--){
			if((1<<j)&a[i])continue;
			if(test(check^(1<<j),i))check^=(1<<j);
		}
		mi=max(mi,check|a[i]);
	}
	printf("%d",mi);
	return 0;
}

```



## 参考资料

[CodeForces -1208F Bits And Pieces](https://blog.csdn.net/Ratina/article/details/100100711)

---

## 作者：foreverlasting (赞：6)

[推销博客](https://foreverlasting1202.github.io/2019/08/27/CF1208%E9%A2%98%E8%A7%A3/)

### F Bits And Pieces

题意：有一个长度为$n$的序列$a_i$，现要求找出一组数对$(i,j,k)$，满足$i<j<k$且$a_i\  or\ (a_j\ and\ a_k)$最大。$1\leq n,a_i\leq 2\ast 10^6$。

做法：考虑枚举一个$i$，按高位贪心枚举$1$，然后需要的是快速判断当前状态是否合法。为了判断是否合法，我们记一个三元组$(x,y,S)$表示当前的数为$S$，满足$S\in a_x\ and\ a_y$的最右边的$x$和$y$。这个东西的转移，你就枚举$S$，然后枚举一位变为$0$，由$S$转移到这个数，预处理好即可。复杂度$O(a_iloga_i+nloga_i)$。

code:
```cpp
//2019.8.27 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f
#define unl __int128
#define eps 5.6e-8
#define RG register
#define db double
#define pc(x) __builtin_popcount(x)
//#define pc(x) __builtin_popcountll(x)
typedef pair<int,int> Pair;
#define mp make_pair
#define fi first
#define se second
#define pi acos(-1.0)
#define pb push_back
#define ull unsigned LL
#define gc getchar
//inline char gc() {
//    static char buf[100000],*p1,*p2;
//    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
//}
//inline int read() {
//    res s=0,ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
inline int read() {
    res s=0,ch=gc(),w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
    return s*w;
}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc();
//    while(ch<'0'||ch>'9')ch=gc();
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s;
//}
//inline LL Read() {
//    RG LL s=0;
//    res ch=gc(),w=1;
//    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=gc();}
//    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=gc();
//    return s*w;
//}
//inline void write(RG unl x){
//    if(x>10)write(x/10);
//    putchar(int(x%10)+'0');
//}
inline void swap(res &x,res &y) {
    x^=y^=x^=y;
}
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//clock_t start=clock();
//inline void ck(){
//    if(1.0*(clock()-start)/CLOCKS_PER_SEC>0.1)exit(0);
//}
const int N=1e6+10;
const int M=(1<<21)+10;
namespace MAIN{
    int n;
    int a[N];
    Pair dp[M];
    inline Pair operator + (const RG Pair &x,const res &y){
        if(!y)return x;
        int tmp[3]={x.fi,x.se,y};
        sort(tmp,tmp+3);
        return mp(tmp[1],tmp[2]);
    }
    inline Pair operator + (RG Pair x,const RG Pair &y){
        x=x+y.fi+y.se;
        return x;
    }
    int ans;
    inline bool ck(const RG Pair &x,const res &I){
        return x.se&&x.fi>I;
    }
    int lg,end;
    inline void MAIN(){
        n=read();
        for(res i=1;i<=n;i++)a[i]=read(),dp[a[i]]=dp[a[i]]+i,lg=max(int(log2(a[i])),lg);
        end=(1<<(lg+1))-1;
        for(res i=0;i<=lg;i++)
            for(res S=0;S<=end;S++)
                if(S&(1<<i))dp[S^(1<<i)]=dp[S^(1<<i)]+dp[S];
        for(res i=1;i<=n;i++){
            res cnt=end-a[i],nS=0;
            for(res j=lg;~j;j--)if(cnt&(1<<j)&&ck(dp[nS|(1<<j)],i))nS|=1<<j;
            if(ck(dp[nS],i))ans=max(ans,nS|a[i]);
        }
        printf("%d\n",ans);
    }
}
int main(){
//    srand(19260817);
//    freopen("signin.in","r",stdin);
//    freopen("signin.out","w",stdout);
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：MSqwq (赞：5)

看了一下题解貌似没有这样的做法（？    
考虑枚举 $d_i$，式子等价于最大化 $d_i | (\complement_{d_i}\& d_j\&d_k)$，然后问题就变成最大化 $\complement_{d_i}\& d_j\&d_k$ 了。  
枚举每一位，强制性的限制是 $a_i$ 为 $1$ 的位，一定不能填 $1$，软限制是 $i  < j < k$，那就很好做了，先去做一遍高维前缀和求出每个数被组成的最大下标和次大下标，因为在没有上界限制的情况下，越大越好。求出来这个之后就可以一位一位去填了，因为要最大化，所以从高位开始填，能填就填，限制是前面说到的 $a_i$ 为 $1$ 的位只能填 $0$，剩下的如果次大下标都大于 $i$ 就一定可以填。  
代码：  
```
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
using namespace std;
const int mod=998244353;
const int INF=0x3f3f3f3f;

inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

inline void wr(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x/10)wr(x/10);putchar(x%10+'0');
}

const int N=3e6+10;
int a[N];pii dp[N];

pii yqy(pii x,pii y)
{
    pii res;
    if(x.first>y.first)res.first=x.first,res.second=max(x.second,y.first);
    else res.first=y.first,res.second=max(x.first,y.second);
    return res;
}

int main()
{
    int n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)dp[a[i]]=yqy(dp[a[i]],{i,0});
    for(int i=0;i<=20;i++)
    {
        for(int j=0;j<(1<<21);j++)
        {
            if(j&(1<<i))continue;
            dp[j]=yqy(dp[j],dp[j|(1<<i)]);  
        }
    }
    int ans=0;
    for(int i=1;i<=n-2;i++)
    {
        int x=0;
        for(int j=21;j>=0;j--)
        {
            if(a[i]&(1<<j))continue;
            if(dp[x|(1<<j)].second>i)x|=(1<<j);
        }
        ans=max(ans,a[i]|x);
    }
    wr(ans),puts("");
	return 0;
}
```


---

## 作者：chenxia25 (赞：5)

首先在线性结构上搞是没有前途的，因为这些位运算不满足某些例如与 $\min/\max$ 的分配律等的好性质。于是我们换个角度，考虑枚举答案，看它们都可行不可行。

容易想到，可以枚举 $a_i$ 的部分看是否有 $i<j<k$ 使得 $a_j\operatorname{and}a_k$ 和 $a_i$ 或起来能包含当前答案。那么我们显然可以求出对于每个值，$a_i$ 部分包含它的最小 $i$ 和 $a_j\operatorname{and}a_k$ 包含它的最大 $j$，如果 $i<j$ 就可行。后面这个显然更强，但也是不难的，只需要看包含当前值的次大下标即可，这个高维前缀和即可轻松求出。

但是如果向上面这样枚举的话，最快也只能做到枚举子集的 $\mathrm O\!\left(3^d\right)$。但是我们注意到要求的是最大的符合要求的值，于是可以按照套路字典序贪心，从高到低位决定（这是本题的关键，也是我看了题解之后发现的东西）。因为容易发现若 $i$ 包含 $j$，则 $ok(i)\to ok(j)$。于是这样只需要判断 $\mathrm O(d)$ 个值是否可行，复杂度 $\mathrm O\!\left(2^dd\right)$。

然后发现这个字典序贪心的写法跟普通的倍增代替二分是一样的，尽管它并不满足普遍意义上的单调性。

**_[code](https://www.luogu.com.cn/paste/4ewnwzp0)_**

---

## 作者：喵仔牛奶 (赞：3)

考虑一个贪心，从高到第枚举位数，如果这位为 $1$ 可以的话就为 $1$，否则为 $0$。

如何判断？枚举当前状态那几位由 $d_i$ 贡献，哪几位由 $d_j\&d_k$ 贡献，设 $d_i$ 贡献的子集为 $b$， $d_j\&d_k$ 贡献的子集为 $c$，求出最小满足 $b\subseteq a_i$ 的 $i$，次大满足 $c\subseteq a_j$ 的 $j$，如果 $i<j$，说明当前状态合法。

可以证明不会漏掉最优解：
1. 设 $A$ 为最优状态，$B$ 为当前状态，由上文做法可知 $B$ 为 $A$ 最后几位 $1$ 变为 $0$ 的数。
1. 最优解和当前状态肯定合法（废话），设 $A$ 枚举时判断合法的 $d_i$ 贡献的子集和 $d_j\&d_k$ 贡献的子集分别为 $b_A,c_A$（相当于上文的 $b,c$），$B$ 的分别为 $b_B,c_B$。
1. 由 1 可知 $b_B\subseteq b_A,c_B\subseteq c_A$，而存在 $i,j$ 使得 $b_A\subseteq a_i,c_A\subseteq a_j$，等量代换可知存在 $i,j$ 使得 $b_B\subseteq a_i,c_B\subseteq a_j$。

求最小满足 $b\subseteq a_i$ 的 $i$，次大满足 $c\subseteq a_j$ 的 $j$ 可以用[高维前缀和](https://oi-wiki.org/basic/prefix-sum/)。

具体地，设 $sum_{i}$ 为满足 $i\subseteq a_j$ 的最小 $j$，$f_{i,j}$ 为同 $j$ 低 $(21-i)$ 位相同的数对 $sum_j$ 的贡献（$21$ 是 $a_i$ 的最高位数）。可知 $sum_i=f_{21,i}$。

其转移方程为：$f_{i,j}=\min\{f_{i-1,j},f_{i,j'}\}$。其中 $j'$ 为将 $j$ 的第 $i$ 位变为 $1$ 的数，如果 $j$ 第 $i$ 位本就为 $1$，则 $f_{i,j'}=\infty$。

求次大值同理，改变 $sum,f$ 的定义及修改转移方程中的取 $\min$ 操作即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 22;
struct node {
	int max, sec;
	node(int x, int y) : max(x), sec(y) {}
	node() {}
	node operator + (const node& x) const {
		int qwq = max, qaq = x.max;
		if (qaq > qwq) swap(qwq, qaq);
		return node(qwq, std::max({qaq, sec, x.sec}));
	}
} mx[1 << N]; // 求次大值的结构体
int n, m, w, ans, mn[1 << N]; // mn 为最小值
int main() {
	memset(mn, 0x3f, sizeof mn);
	cin >> n;
	for (int i = 1; i <= n; i ++)
		cin >> w, mx[w] = mx[w] + node(i, 0), mn[w] = min(mn[w], i);
	for (int i = 0; i < 21; i ++)
		for (int j = (1 << 21) - 1; j >= 0; j --)
			if (!(j & 1 << i)) mx[j] = mx[j] + mx[j ^ 1 << i], mn[j] = min(mn[j], mn[j ^ 1 << i]); // 动态规划+滚动数组，记得倒序枚举啊 QAQ
	for (int i = 21; i >= 0; i --) {
		int now = ans | 1 << i, success = 0;
		for (int j = now; ; j = (j - 1) & now) { // 枚举子集
			if (mn[j] < mx[now ^ j].sec) success = 1;
			if (success || !j) break; // 别忘了 j = 0 的情况 QAQ
		}
		if (success) ans = now;
	}
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：ListenSnow (赞：3)

## 题意

给定 $n$ 个数的数组 $d$，找到 $i < j < k$ 的 $i,j,k$，使得 $d_i|(d_j \& d_k)$ 最大。

#### 数据范围

$3 \leq  n \leq 10^6,0 \leq d_i \leq 2 \times 10^6$。

### 思路

>思路来源于同机房的[城阙](https://www.luogu.com.cn/user/115857)巨佬。

注意到或运算的性质，只要两个数之间有一个数的第 $i$ 位为 $1$，那么得到的结果中的第 $i$ 位就为 $1$。于是就可以考虑枚举 $d_i$。而对于 $d_j \& d_k$，我们只关心 $d_i$ 在二进制下为 $0$ 的位数 $d_j \& d_k$ 得到的结果是否为 $1$。更一般的，根据贪心的性质，位数越高的为 $1$ 得到的答案也就越大。而 $d_i$ 本身就为 $1$ 的位数就并不关心。

于是就可以考虑用一个数组统计 $+\infty$ 的所有子集的出现次数，如果一个子集出现了两次，那么就必然存在 $d_j$ 和 $d_k$ 使得它们 $\&$ 得到的集合中包含这个集合。

考虑如何更新子集出现的次数，我们只需要一个集合出现两次，再多也就没有意义了，但直接循环枚举，单次更新的复杂度达到了 $O(2^{23})$ （$2 \times 10^6$ 在二进制下连第 $0$ 位一共有 $23$ 位）。于是可以考虑 DFS 更新，如果 $d_i$ 的一个子集已经被更新了两次，那么它的所有子集也必定都被更新了两次，此时直接返回就可以。但是需要注意一个数被更新两次的情况（如从 $111$ 搜索到 $110$ 和 $101$，它们又会各自枚举一次 $100$），于是每一次更新的时候要开一个数组记录一下每个子集是否已经被枚举过。

而对于每一个 $d_i$，从高到低枚举每一位（因为 $100000>011111$），同时用一个变量 $now$ 记录当前要求的 $d_j\&d_k$ 的集合的子集。如果当前位为 $1$，那就直接更新 $d_i$ 得到的答案的最大值，如果为 $0$，那么就判断将 $now$ 当前位上更新成 $1$ 后的集合后，是否在 $d_j\&d_k$ 里出现了两次。最终取所有 $d_i$ 的最大值即可。

### code：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=3e6+10;
bool vis[N];int a[N],n,cnt[N],st[N],top,ans;
void update(int val)
{
	if(cnt[val]>=2||vis[val]) return ;cnt[val]++;st[++top]=val;vis[val]=true;
	for(int i=22;i>=0;i--) if(val>>i&1) update(val^(1<<i));
}
int query(int val)
{
	int res=0,now=0;
	for(int i=22;i>=0;i--)
	{
		if(val>>i&1) res|=1<<i;
		else if(cnt[now|(1<<i)]>=2) res|=1<<i,now|=1<<i;
	}
	return res;
}
void clear(){while(top) vis[st[top--]]=false;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);update(a[n]);clear();
	for(int i=n-1;i>=2;i--)
	{
		update(a[i]);clear();
		ans=max(ans,query(a[i-1]));
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：1)

这道题很高。

对于每一个值 $x$，我们求出 $a_j\ \text{and}\ a_k\ (j<k)$ 包含 $x$ 的最大 $j$，设为 $p_x$。

这个是正常的高维前缀和维护了一个不寻常的东西（位置的最大值和次大值），具体看代码。

然后我们枚举每一个 $i$，通过二分搜索（在 trie 的视角的话就是每次往一个儿子走）找到 $x\ \text{or}\ a_i$ 最大的 $x$，满足 $p_x>i$。

最后求一个 $\max$ 即可。

复杂度 $O(c(n+2^c))$，$c$ 为二进制位数。

[Link](https://codeforces.com/contest/1208/submission/175250312)

---

## 作者：cirnovsky (赞：1)

考虑把原问题写成一个在 $\left(\log_2 \max v \right) \times n$ 的矩阵里选出三列，我们首先预处理出 $j \cap q$。具体，我们需要对于每一个权值 $v$ 求出一个最大的下标 $p$（$1 \leqslant p \leqslant n$）满足存在极大的 $q < p$ 且 $v \cap a_p \cap a_q = v$，即 $v \subseteq \left(a_p \cap a_q\right)$，这个可以做一个二元组 dp，即设 $f_v$ 为对于 $v$ 而言的答案，注意到 $p$ 和 $q$ 的实际意义是「满足左右两边存在有一个位置做并操作后是 $v$ 的超集的位置下标」的最大值和次大值，所以更新答案是容易的。

考虑如何转移。对于一个左闭右开区间 $[0, 2^n)$，我们分治求出 $[0, 2^{n-1})$ 和 $[2^{n-1}, 2^n)$ 的 dp，当然左边区间的 dp 值不会对右边区间产生影响，所以我们考虑右边区间对左边区间的影响。$\forall i \in [l, m)$，我们需要从 $i$ 的超集转移到 $i$，因为在 dp 时我们实际上是把所有贡献放到一个点上，又注意到 $i-l+m$ 和 $i$ 的关系就是二进制意义下多了一个最高位的 $1$，所以只需要从 $i-l+m$ 转移到 $i$ 即可（有点谜语，但就这样吧）。

然后就贪心取最高位，挨个取 max 就行了。

```cpp
int n, a[1000100], qwq;
pii dp[3000100];
pii upd(const pii& x, const pii& y) {
  if (x.first > y.first) {
    return pii(x.first, max(y.first, x.second));
  }
  else {
    return pii(y.first, max(x.first, y.second));
  }
}
void sos_dp(int l, int r) {
  if (r-l == 1) {
    return;
  }
  int mid = (l+r)/2;
  sos_dp(l, mid), sos_dp(mid, r);
  for (int i=l; i<mid; ++i) {
    dp[i] = upd(dp[i], dp[i-l+mid]);
  }
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i=1; i<=n; ++i) {
    cin >> a[i];
    dp[a[i]] = upd(dp[a[i]], pii(i, 0));
  }
  qwq = 1;
  for (int up=*max_element(a+1, a+n+1); (1<<qwq) <= up;) {
    qwq++;
  }
  sos_dp(0, 1<<qwq);
  int ans = 0;
  for (int i=1; i<=n; ++i) {
    int offset = 0;
    bool f = 0;
    for (int j=qwq; j>=0; --j) {
      if (~(a[i]>>j)&1 && dp[offset|(1<<j)].second > i) {
        offset |= 1<<j, f = 1;
      }
    }
    if (dp[offset].second > i) {
      f = 1;
    }
    if (f) {
      cmax(ans, a[i]|offset);
    }
  }
  cout << ans << "\n";
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

这玩意儿好像是叫 SOS_DP 来着……不过也倒没什么特殊的性质，其实就可以看作状压 DP 的一种。                  

我们考虑使用 DP 维护。                  

令 $DP_x$ 表示两个数与起来得到的数且 $x$ 属于这个数的子集的最远的两个下标。               

初始化时直接把每个 $a_i$ 对应的 $i$ 初始进 $a_i$ 就好了，然后每次暴力把它其中的一个 $1$ 变成 $0$ ，接着向这个状态转移，并且转移时数从大到小枚举。                  

这么做的正确性在于每次转移的所有状态的子集并起来加上原来这个数本身就是原来这个数的子集了，所以可以保证在转移中每个数的子集都被计算到。                  

我们可以在 $O(\max a_i \log a_i)$ 的时间复杂度完成这个 DP 。                    

接着对于每个数我们考虑以它作为或的第一个数时的答案。           

我们从高到低贪心处理。对于一个位如果当前位为 $1$ 的话我们就不管它，否则我们开一个数 $w$ 表示当前需要后面两个数与起来得到一个数并且 $w$ 是这个数的子集，然后我们直接用得到的 DP 数组去检测一下就好了，时间复杂度 $O(n \log a_i)$ 。                

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e6 + 5;
int maxa,n,a[Len],ans;
struct node
{
	int fir,sec;
	node(){fir = 0 , sec = 0;}
	node(int FIR,int SEC){fir = FIR , sec = SEC;}
}dp[Len];
inline void Get(int x,int pos)
{
	if(!pos) return; 
	if(dp[x].fir < pos)
	{
		dp[x].sec = dp[x].fir;
		dp[x].fir = pos;
	}
	else if(dp[x].sec < pos && dp[x].fir != pos) dp[x].sec = pos;
}
void Init()
{
	for(int i = maxa ; i >= 0 ; i --)
	{
		for(int j = 0 ; j <= 20 ; j ++) 
		{
			if((i >> j) & 1) 
			{
				Get(i ^ (1 << j) , dp[i].fir);
				Get(i ^ (1 << j) , dp[i].sec);
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&a[i]);
		Get(a[i] , i);
		maxa = max(maxa , a[i]);
	}
	Init();
//	for(int i = 1 ; i <= maxa ; i ++) printf("%d %d %d\n",i,dp[i].fir,dp[i].sec);
	for(int i = 1 ; i <= n - 2 ; i ++) 
	{
		int w = 0;
		for(int j = 20 ; j >= 0 ; j --)
		{
			if((a[i] >> j) & 1) continue;
			if(dp[w | (1 << j)].sec > i) w |= (1 << j);
		}
		ans = max(ans , a[i] | w);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

$\text{Difficulty: }\color{red}\text{2600}$。

高维前缀和+字典树。

令 $x_i$ 为存在 $i\in d_j$（以下 $\in$ 表示二进位属于）的最小 $j$，$y_i$ 为存在 $i\in d_j\& d_k$，$j<k$ 的最大 $j$。

问题转化为最大的 $i|j$ 使得 $x_i<y_j$，使用 01-Trie 按序插入查询即可。复杂度 $O(\max a_i\log\max a_i)$，可能需要一定卡常。

[提交记录](https://codeforces.com/contest/1208/submission/201807216)。

---

