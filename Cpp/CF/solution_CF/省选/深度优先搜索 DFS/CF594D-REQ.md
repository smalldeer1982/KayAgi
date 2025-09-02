# REQ

## 题目描述

Today on a math lesson the teacher told Vovochka that the Euler function of a positive integer $ φ(n) $ is an arithmetic function that counts the positive integers less than or equal to n that are relatively prime to n. The number $ 1 $ is coprime to all the positive integers and $ φ(1)=1 $ .

Now the teacher gave Vovochka an array of $ n $ positive integers $ a_{1},a_{2},...,a_{n} $ and a task to process $ q $ queries $ l_{i} $ $ r_{i} $ — to calculate and print ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF594D/1bd06985c605f4dcc1229ea18fcf81458cbdb3b0.png) modulo $ 10^{9}+7 $ . As it is too hard for a second grade school student, you've decided to help Vovochka.

## 说明/提示

In the second sample the values are calculated like that:

- $ φ(13·52·6)=φ(4056)=1248 $
- $ φ(52·6·10·1)=φ(3120)=768 $
- $ φ(24·63·13·52·6·10·1)=φ(61326720)=12939264 $
- $ φ(63·13·52)=φ(42588)=11232 $
- $ φ(13·52·6·10)=φ(40560)=9984 $
- $ φ(63·13·52·6·10)=φ(2555280)=539136 $

## 样例 #1

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
7
1 1
3 8
5 6
4 8
8 10
7 9
7 10
```

### 输出

```
1
4608
8
1536
192
144
1152
```

## 样例 #2

### 输入

```
7
24 63 13 52 6 10 1
6
3 5
4 7
1 7
2 4
3 6
2 6
```

### 输出

```
1248
768
12939264
11232
9984
539136
```

# 题解

## 作者：feicheng (赞：11)

考完期末复活一下， 感谢 Acc_Robin 给我讲了这道题。

## Description

给定长度为 $n$ 的序列 $a$， $q$ 次询问，每次询问包含两个参数 $l,r$，求
  $$
  \varphi\left(\prod_{i=l}^r a_i\right)  
  $$
  答案对 $10^9+7$ 取模。
  
**限制**：$1\le n\le 2\times 10^5$，$1\le a_i\le 10^6$。

## Solution

首先需要知道 $\varphi(p^k)=(p-1)p^{k-1}$，设
  $$
  a_i=\prod_{j}p_j^{m_{i,j}}  
  $$

  则有 
  $$
  \varphi\left(\prod_{i=l}^r a_i\right)=\varphi\left(\prod_{i=l}^r \prod_{j}p_j^{m_{i,j}}\right)=\varphi\left(\prod_{j}p_j^{\sum\limits_{l\le i\le r}m_{i,j}}\right)  
  =\prod_j(p_j-1)p_j^{\sum\limits_{l\le i\le r}m_{i,j}-1}
  $$
  于是考虑对 $a_i$ 进行质因数分解，对每个 $p_j$ 考虑其贡献： 若 $p_j$ 第一次出现，则其贡献为 $(p_j-1)p_j^{m_{i,j}-1}$。
  
  反之，需要找到 $p_j$ 的前驱，在这个位置乘上 $\dfrac{p_j}{p_j-1}$ 以消除其贡献，再在 $i$ 的位置乘上 $(p_j-1)p_j^{m_{i,j}-1}$。
  
发现是一个单点修改区间求乘积的问题，线段树解决即可。

  时间复杂度:$\mathcal O(n\log\log a_i\log n+q\log n)$。

---

## 作者：Siyuan (赞：11)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-Codeforces-594D-REQ/)

---

## Description

> 题目链接：[Codeforces 594D](https://codeforces.com/contest/594/problem/D/)

今天的数学课上，老师告诉 Vovochka 正整数的欧拉函数 $\varphi(n)$ 是计算小于等于 $n$ 且与 $n$ 互质的正整数的函数，$1$ 和任意正整数互质所以 $\varphi(1)=1$。

现在老师给了 Vovochka 一个数列 $a_1,a_2,\dots,a_n$，要求回答 $q$ 个询问 $l_i,r_i$，计算 $\varphi\left(\prod_{i=l}^r a_i\right)$ 的值，答案对 $10^9 + 7$ 取模。这个问题对二年级学生来说太难了，所以你决定帮助 Vovochka。

数据范围：$1\le n,q\le 2\times 10^5$，$1\le a_i\le 10^6$

------

## Solution

由于只有询问操作，因此我们首先想到**离线**后用莫队解决。但是莫队的复杂度为 $O(q\sqrt n\log a_i)$（其中 $\log a_i$ 指每个数的本质不同的质因子个数），显然无法通过本题（我卡了半个小时常数还是 $\text{TLE}$ ~~出题人毒瘤~~）。

还是考虑离线，我们将询问**按照右端点排序**，维护一个右指针，将每个 $a_i$ 逐个加入。用**树状数组**维护每个位置对答案的贡献。

我们考虑 $a_i$ 的其中一个质因子 $p$（其他的质因子同理）。由于我们把询问按照右端点排序了，而每个质因子只能对答案有**一次贡献**，那么我们把 $p$ 的贡献放到区间 $[1,i]$ 的**最右边**，即进行操作 $add(i,p-1)$ 和 $add(i,p^{-1})$。如果 $p$ 已经出现过了，那么我们需要**防止区间左端点左侧产生贡献**，维护一个 $lst[i]$ 表示 $i$ 这个质因子**上次出现的位置**，将 $lst[p]$ 位置的贡献消去即可。

对于如何快速分解每个数的质因子，我们可以根据线性筛的本质：每个数只会被其**最小质因子**筛去，在筛的过程中直接记录每个数的最小质因子即可！

**时间复杂度**：$O((n+q)\log n\log a_i)$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>

const int N=2e5+5,M=1e6+5;
const int mod=1e9+7;
int n,m,tot,a[N],b[N],p[M/10],f[M],pre[N],lst[M],ans[N];
bool flg[M];

struct Data {
	int l,r,id;
	bool operator < (const Data &rhs) const {
		return r<rhs.r;
	}
} q[N];

void sieve(int n) {
	for(int i=2;i<=n;++i) {
		if(!flg[i]) p[++tot]=i,f[i]=i;
		for(int j=1;j<=tot&&i*p[j]<=n;++j) {
			flg[i*p[j]]=1,f[i*p[j]]=p[j];
			if(i%p[j]==0) break;
		}
	}
}
int pow(int x,int p) {
	int ret=1;
	for(;p;p>>=1,x=1LL*x*x%mod) if(p&1) ret=1LL*ret*x%mod;
	return ret;
}
int inv(int x) {
	return pow(x,mod-2);
}
void add(int x,int val) {
	for(;x<=n;x+=x&-x) b[x]=1LL*b[x]*val%mod;
}
int query(int x) {
	int ret=1;
	for(;x;x^=x&-x) ret=1LL*ret*b[x]%mod;
	return ret;
}
void update(int i) {
	for(int x=a[i],p=f[x];x>1;p=f[x]) {
		add(i,p-1),add(i,inv(p));
		if(lst[p]) add(lst[p],inv(p-1)),add(lst[p],p);
		lst[p]=i;
		while(x%p==0) x/=p;
	}
}
int main() {
	sieve(M-5);
	scanf("%d",&n);
	pre[0]=1;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),pre[i]=1LL*pre[i-1]*a[i]%mod;
	scanf("%d",&m);
	for(int i=1;i<=m;++i) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	std::sort(q+1,q+m+1);
	for(int i=0;i<=n;++i) b[i]=1;
	for(int i=1,j=0;i<=m;++i) {
		int x=q[i].l,y=q[i].r;
		while(j<y) update(++j);
		ans[q[i].id]=1LL*pre[y]*inv(pre[x-1])%mod*query(y)%mod*inv(query(x-1))%mod;
	}
	for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：Acc_Robin (赞：7)

提供一个在线做法。

这个问题的本质是二维数点，所以对于离线做法也存在一个可持久化线段树的做法。

考虑使用可持久化线段树维护，内层的区间乘积就是该点的答案 $\varphi$。

令指针 $i$ 从 $1$ 向 $n$ 扫，每次对于一个 $a_i$，考虑它会哪些区间的 $\varphi$ 值造成什么样的贡献。

我们将 $a_i$ 分解质因数，对每一个质因数 $p$，令 $las_p$ 表示上一次出现 $p$ 的位置。

- 若 $las_p$ 不存在，则直接在当前这颗线段树的位置 $i$ 乘上 $(p-1)p^{v_p(a_i)-1}$。

- 若 $las_p$ 存在，那么要消除掉 $las_p$ 处的贡献，就给这颗线段树的 $las_p$ 处乘上 $\frac{p}{p-1}$，然后再给 $i$ 接着乘上 $(p-1)p^{v_p(a_i)-1}$。

对于询问 $[l,r]$，我们只要在第 $r$ 棵线段树上询问 $[l,r]$ 这个区间的乘积即可。

预处理复杂度 $O(n\log a_i\log n)$，询问复杂度 $O(\log n)$，空间复杂度 $O(n\log a_i\log n)$。

相较于离线做法，是用空间换的在线。

---

## 作者：ywy_c_asm (赞：5)

这题其实拿莫队是能过的……就是这相当于是要询问区间内每种质因子的乘积与$p-1$的乘积，然后这和区间数颜色差不多就直接拿莫队做就行了……

当然要过掉这题你还需要一些技巧，首先你要用$a^{-1}=-\frac p a(p\%a)^{-1}\space O(n)$求逆元，然后你要把所有用到log求逆元的地方都改成用这个或者逆元的乘积，这样虽然不是复杂度瓶颈，但是毕竟是$O(\log P)$的，加了这个之后跑的还挺快，然后因为我们在莫队的时候要$O(\log a_i)$枚举质因子，这个log虽然比较虚但是还是会对时间带来不小的影响，莫队的时候要把块大小开的大一点，这个我在本地上~~手动三分~~发现1220左右最快。加了上面两个优化最慢的一个点才2s左右……

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ll long long
#define p 1000000007
#define blo 1220
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	ll inv[1000001];
	void print(int num) {
	    if (num >= 10)
	        print(num / 10);
	    putchar(num % 10 + '0');
	}
	ll qzj[200001];
	int ints[200001], mindiv[1000001], prime[1000001];
	unsigned char bv[1000001];
	inline void prim(int n) {
	    int ptr = 0;
	    for (register int i = 2; i <= n; i++) {
	        if (!bv[i]) {
	            prime[ptr] = i;
	            ptr++;
	            mindiv[i] = i;
	        }
	        for (register int j = 0; j < ptr; j++) {
	            int cjr = prime[j] * i;
	            if (cjr > n)
	                break;
	            bv[cjr] = 1;
	            mindiv[cjr] = prime[j];
	            if (i % prime[j] == 0)
	                break;
	        }
	    }
	    inv[0] = inv[1] = 1;
	    for (register int i = 2; i <= n; i++) {
	        inv[i] = (inv[p % i] * (p - (p / i))) % p;
	    }
	}
	vector<int> vec[200001];
	inline ll mi(int a, int b) {
	    ll ans = 1, tmp = a;
	    while (b) {
	        if (b & 1)
	            ans = (ans * tmp) % p;
	        tmp = (tmp * tmp) % p;
	        b >>= 1;
	    }
	    return (ans);
	}
	int cnt[1000001];
	typedef struct _n {
	    int l;
	    int r;
	    int id;
	    friend bool operator<(const _n &a, const _n &b) {
	        if (a.l / blo == b.l / blo)
	            return (a.r < b.r);
	        return (a.l / blo < b.l / blo);
	    }
	} node;
	node memchi[200001];
	ll ans1[200001], ans2[200001], ji[200001], jiny[200001];
	void ywymain() {
	    int n = get();
	    int mx = 0;
	    for (register int i = 1; i <= n; i++) mx = max(mx, ints[i] = get());
	    prim(mx);
	    qzj[0] = jiny[0] = 1;
	    for (register int i = 1; i <= n; i++) {
	        int tmp = ints[i];
	        while (tmp != 1) {
	            int d = mindiv[tmp];
	            vec[i].push_back(d);
	            while (mindiv[tmp] == d) tmp /= d;
	        }
	        qzj[i] = (qzj[i - 1] * ints[i]) % p;
	        jiny[i] = (jiny[i - 1] * inv[ints[i]]) % p;
	    }
	    int m = get();
	    for (register int i = 1; i <= m; i++) {
	        int l = get(), r = get();
	        ji[i] = (qzj[r] * jiny[l - 1]) % p;
	        memchi[i].l = l;
	        memchi[i].r = r;
	        memchi[i].id = i;
	    }
	    sort(memchi + 1, memchi + 1 + m);
	    ll jp = 1, jp1 = 1;
	    int l = memchi[1].l, r = memchi[1].r;
	    for (register int i = l; i <= r; i++) {
	        for (register int j = 0; j < vec[i].size(); j++) {
	            if (!cnt[vec[i][j]])
	                jp = (jp * inv[vec[i][j]]) % p, jp1 = (jp1 * (vec[i][j] - 1)) % p;
	            cnt[vec[i][j]]++;
	        }
	    }
	    ans1[memchi[1].id] = jp;
	    ans2[memchi[1].id] = jp1;
	    for (register int i = 2; i <= m; i++) {
	        while (l > memchi[i].l) {
	            l--;
	            for (register int j = 0; j < vec[l].size(); j++) {
	                if (!cnt[vec[l][j]])
	                    jp = (jp * inv[vec[l][j]]) % p, jp1 = (jp1 * (vec[l][j] - 1)) % p;
	                cnt[vec[l][j]]++;
	            }
	        }
	        while (r < memchi[i].r) {
	            r++;
	            for (register int j = 0; j < vec[r].size(); j++) {
	                if (!cnt[vec[r][j]])
	                    jp = (jp * inv[vec[r][j]]) % p, jp1 = (jp1 * (vec[r][j] - 1)) % p;
	                cnt[vec[r][j]]++;
	            }
	        }
	        while (l < memchi[i].l) {
	            for (register int j = 0; j < vec[l].size(); j++) {
	                cnt[vec[l][j]]--;
	                if (!cnt[vec[l][j]])
	                    jp = (jp * vec[l][j]) % p, jp1 = (jp1 * inv[vec[l][j] - 1]) % p;
	            }
	            l++;
	        }
	        while (r > memchi[i].r) {
	            for (register int j = 0; j < vec[r].size(); j++) {
	                cnt[vec[r][j]]--;
	                if (!cnt[vec[r][j]])
	                    jp = (jp * vec[r][j]) % p, jp1 = (jp1 * inv[vec[r][j] - 1]) % p;
	            }
	            r--;
	        }
	        ans1[memchi[i].id] = jp;
	        ans2[memchi[i].id] = jp1;
	    }
	    for (register int i = 1; i <= m; i++) {
	        ll cjr = ji[i];
	        cjr *= ans1[i];
	        cjr %= p;
	        cjr *= ans2[i];
	        cjr %= p;
	        print(cjr);
	        putchar('\n');
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：_Yonder_ (赞：3)

先令 $s=\prod\limits_{i=l}^{r}{a_i}$，则有：$φ(s)=s\prod\limits_{i=1}^{cnt}{\frac{p_i-1}{p_i}}$

$s$ 并不难求（前缀积加逆元），后面的 $\prod\limits_{i=1}^{cnt}{\frac{p_i-1}{p_i}}$ 类似数颜色，将每个询问按 $r$ 排序，然后树状数组即可，时间复杂度 $O(q\log n\log a_i)$。
# Code
```
#include<bits/stdc++.h>
#define S std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define rep(i,l,r) for(register int i=l;i<=r;i++)
#define per(i,l,r) for(register int i=l;i>=r;i--)
using namespace std;
template<typename P>inline void read(P&x){bool f=0;x=0;char c=getchar();while(!isdigit(c)) f|=c=='-',c=getchar();while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();x=f?~(x-1):x;}
template<typename P>inline void write(P x){if(x<0) putchar('-'),x=-x;if(x>9) write(x/10);putchar((x%10)^48);}
const int N=2e5+5,mod=1e9+7,M=1e6+5;
struct IN{int l,r,i;}in[N];
int n,m,a[N],to[M],tr[N],t[M],out[N],sum[N];
inline int quickpow(int a,int b,int c){
    register int ans=1;
    while(b){if(b&1) ans=(ans*1ll*a)%c;b>>=1;a=a*1ll*a%c;}
    return ans;
}inline void Prime(){
    bool f[M]={};int p[N],len=0;
    for(register int i=2;i<M;i++){
        if(!f[i]) p[++len]=i,to[i]=i;
        for(register int j=1;j<=len&&i*p[j]<M;j++)
            {f[i*p[j]]=true,to[i*p[j]]=p[j];if(!(i%p[j])) break;}
    }
}inline int inv(int x){return quickpow(x,mod-2,mod);}
inline int ask(int x){int ans=1;while(x) ans=(ans*1ll*tr[x])%mod,x^=x&-x;return ans;}
inline void add(int x,int d){while(x<N) tr[x]=(tr[x]*1ll*d)%mod,x+=x&-x;}
inline void modify(int x){
    for(register int i=a[x],p=to[i];i>1;p=to[i]){
        add(x,p-1),add(x,inv(p));
        if(t[p]) add(t[p],inv(p-1)),add(t[p],p);
        t[p]=x;while(i%p==0) i/=p;
    }
}
int main(){
    S;cin>>n;sum[0]=1;rep(i,1,n) cin>>a[i],sum[i]=sum[i-1]*1ll*a[i]%mod;
    cin>>m;Prime();rep(i,1,m) cin>>in[i].l>>in[i].r,in[i].i=i;
    sort(in+1,in+1+m,[](IN x,IN y){return x.r<y.r;});
    rep(i,0,n) tr[i]=1;
    for(register int i=1,j=1;i<=m;i++){
        while(j<=in[i].r) modify(j++);
        out[in[i].i]=sum[in[i].r]*1ll*inv(sum[in[i].l-1])%mod*ask(in[i].r)%mod*inv(ask(in[i].l-1))%mod;
    }for(register int i=1;i<=m;i++) write(out[i]),putchar('\n');
	return 0;
}
```

---

## 作者：dd_d (赞：3)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16504705.html)  
### Sol  
挺套路的一个题。  
首先 $\phi(n) = n \times \prod (1-\frac{1}{p_i})$。  
那么一次询问就变成了区间积乘上区间质因数并集的贡献。  
前者直接前缀积维护即可。考虑后者怎么维护。  
离线，把询问按右端点排序。依次加入 $a_i$。  
记 $p$ 表示 $a_i$ 的质因数。将 $p$ 的贡献放在 $i$ 这个位置上，若之前出现过 $p$ 那么记个 $last_p$ 表示上一次 $p$ 出现的位置并删掉贡献。树状数组维护即可。  
时间复杂度 $O(n \log n \log a_i)$。
### Code
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=1e6+10,mod=1e9+7;
struct node
{
	int l,r,id;
}q[N];
int n,s[N],a[N],c[N],last[N],p[N],ans[N],tot,vis[N],m;
inline int quickpower(int a,int b)
{
	int res=1;
	while (b)
	{
		if (b&1) (res*=a)%=mod;
		b>>=1; (a*=a)%=mod;
	}
	return res;
}
void init()
{
	for (int i=0;i<N;i++)
		c[i]=1;
	for (int i=2;i<N;i++)
	{
		if (!vis[i]) p[++tot]=i;
		for (int j=1;j<=tot&&i*p[j]<N;j++)
		{
			vis[i*p[j]]=1;
			if (i%p[j]==0) break;
		}
	}
}
inline void add(int x,int y)
{
	for (;x<N;x+=lowbit(x))
		c[x]=c[x]*y%mod;
}
inline int query(int x)
{
	int res=1;
	for (;x;x-=lowbit(x))
		res=res*c[x]%mod;
	return res;
}
void update(int x)
{
	int now=a[x];
	for (int i=1;p[i]*p[i]<=now;i++)
		if (now%p[i]==0)
		{
			assert(now%p[i]==0);
			add(x,(p[i]-1)*quickpower(p[i],mod-2)%mod);
			if (last[p[i]]) add(last[p[i]],p[i]*quickpower(p[i]-1,mod-2)%mod);
			last[p[i]]=x;
			while (now%p[i]==0) now/=p[i];
		}
	if (now!=1)
	{
		add(x,(now-1)*quickpower(now,mod-2)%mod);
		if (last[now]) add(last[now],now*quickpower(now-1,mod-2)%mod);
		last[now]=x;
	}
}
signed main()
{
	n=read(); s[0]=1; init();
	for (int i=1;i<=n;i++)
		a[i]=read(),s[i]=s[i-1]*a[i]%mod;
	m=read();
	for (int i=1;i<=m;i++)
		q[i]={read(),read(),i};
	sort(q+1,q+m+1,[](node x,node y)
	{
		return x.r<y.r;
	});
	int now=0;
	for (int i=1;i<=m;i++)
	{
		while (now<q[i].r) update(++now);
		// cout<<q[i].id<<' '<<s[q[i].r]*quickpower(s[q[i].l-1],mod-2)%mod<<' '<<query(q[i].r)*quickpower(query(q[i].l-1),mod-2)%mod<<'\n';
		ans[q[i].id]=s[q[i].r]*quickpower(s[q[i].l-1],mod-2)%mod*query(q[i].r)%mod*quickpower(query(q[i].l-1),mod-2)%mod;
	}
	for (int i=1;i<=m;i++)
		writeln(ans[i]);
}





```

---

## 作者：Owen_codeisking (赞：3)

发一个莫队稳定 $O(n\sqrt{n})$ 的题解

可能我人傻常数大所以跑得特别慢。。。

一道相似的题目：[[Ynoi2015]此时此刻的光辉](https://www.luogu.org/problemnew/show/P5071)

首先想到计算每一个质因子的贡献，$\varphi(p^k)=(p-1)\times p^{k-1}$

然后我们发现每一个数 $a_i$，大于 $\sqrt{a_i}$ 的质因子只有一个。那么我们可以把小于 $\sqrt{a_i}$ 的质因子弄出来。因为 $a_i\leq 10^6$，我们只用弄小于 $1000$ 的质数，数一数一共只有 $168$ 个。我们维护 $168$ 个关于质因子的前缀积，然后在莫队后查询。

时间复杂度 $O(n\sqrt{n}+n\times \frac {\sqrt{a_i}}{\log \sqrt{a_i}})$

还有一些技巧，比如我们可以维护分子和分母，然后最后再快速幂，这样逆元的 $\log$ 就省掉了。

当然，莫队怎么打得过 $O(n\log^2 n)$ 解法呢。。。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=200000+10;
const int mod=1e9+7;
int n,m,lim,blo,a[maxn],b[maxn],cnt[maxn*5],sum[maxn][200],ans1[maxn],ans2[maxn],now1=1,now2=1,pri[1010],tot;bool vis[1010];

struct Query{
    int l,r,id;
}q[maxn];

inline bool cmp(const Query &a,const Query &b){
    if((a.l-1)/blo!=(b.l-1)/blo) return (a.l-1)/blo<(b.l-1)/blo;
    return a.r<b.r;
}

inline int read(){
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}

inline int fpow(int a,int b){
    int ret=1;
    for(;b;b>>=1,a=1ll*a*a%mod)
        if(b&1) ret=1ll*ret*a%mod;
    return ret;
}

inline void sieve(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]) pri[++tot]=i;
        for(int j=1;j<=tot&&i*pri[j]<=n;j++){
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) break;
        }
    }
}

inline void solve(int x,int n){
    int val;
    for(int i=1;i<=tot&&pri[i]<=n;i++)
        if(n%pri[i]==0){
            val=1;
            while(n%pri[i]==0) n/=pri[i],val*=pri[i];
            sum[x][i]=val;
        }
    if(n>1) b[x]=n;
}

inline void add(int x){
    if(!b[x]) return ;
    if(++cnt[b[x]]==1) now1=1ll*now1*(b[x]-1)%mod;
    else now1=1ll*now1*b[x]%mod;
}

inline void del(int x){
    if(!b[x]) return ;
    if(--cnt[b[x]]==0) now2=1ll*now2*(b[x]-1)%mod;
    else now2=1ll*now2*b[x]%mod;
}

int main()
{
    n=read();blo=sqrt(n)+1;
    for(int i=1;i<=n;i++) a[i]=read(),lim=max(lim,a[i]);
    sieve((int)sqrt(lim));
    for(int i=1;i<=n;i++) solve(i,a[i]);
    for(int j=1;j<=tot;j++){
        sum[0][j]=1;
        for(int i=1;i<=n;i++){
            if(!sum[i][j]) sum[i][j]=sum[i-1][j];
            else sum[i][j]=1ll*sum[i][j]*sum[i-1][j]%mod;
        }
    }
    m=read();
    for(int i=1;i<=m;i++) q[i].l=read(),q[i].r=read(),q[i].id=i;
    sort(q+1,q+m+1,cmp);
    int L=1,R=0;
    for(int i=1;i<=m;i++){
        while(R<q[i].r) add(++R);
        while(R>q[i].r) del(R--);
        while(L<q[i].l) del(L++);
        while(L>q[i].l) add(--L);
        ans1[q[i].id]=now1;ans2[q[i].id]=now2;
        for(int j=1;j<=tot;j++){
            if(sum[q[i].r][j]==sum[q[i].l-1][j]) continue;
            ans1[q[i].id]=1ll*ans1[q[i].id]*sum[q[i].r][j]%mod*(pri[j]-1)%mod;
            ans2[q[i].id]=1ll*ans2[q[i].id]*sum[q[i].l-1][j]%mod*pri[j]%mod;
        }
    }
    for(int i=1;i<=m;i++) printf("%d\n",1ll*ans1[i]*fpow(ans2[i],mod-2)%mod);
    return 0;
}
```

---

## 作者：Prean (赞：2)

我不会数据结构/kk

我想题意应该十分清楚了。

我们知道 $ \varphi(p^k)=p^{k-1}(p-1) $，那么我们考虑将一个询问下放到右端点，然后往右移动右端点并更新每个左端点到右端点的答案。

这就变得很容易了。最开始所有位置的答案都是 $ 1 $。

加入一个数 $ a $ 的时候，因为积性函数可以拆成质数幂处的积性函数之积，所以我们这里也考虑拆成质数幂。

然后记录每一个质因子上一次出现的位置，假设为 $ x $，现在的右端点为 $ i $，那么我们令 $ (x,i] $ 乘上 $ p-1 $，$ [1,x] $ 乘上 $ p $，剩下的位置乘上 $ p^{k-1} $。

可以知道复杂度是 $ O(n\log n\frac {\log V}{\log\log V}) $ 的。~~这个复杂度不知道是在哪儿看到的，反正 1e6 以内绝对不会超过 7。~~

这个拿线段树做就好了。

然后我们发现是单点查询，所以对标记可持久化。然后使用 zkw 线段树加上快读你就可以拿到 lg 最优解。

甚至能在 CF 上面卡进第一页。。。

实际上还有更为厉害的方法。。。

考虑每个位置的初始值都是 $ a_i $，每次往右扫时将 $ p $ 变为 $ p-1 $，线段树的操作次数是我的三分之一。。。

而且这个玩意儿是可以使用树状数组的。。。

不管怎样先把我的代码挂在这里了：
```cpp
#include<iostream>
#include<cctype>
#include<vector>
typedef unsigned ui;
const ui M=2e5+5,mod=1e9+7;
ui n,m,G,a[M],l[M],r[M],ans[M],prod[M<<2];ui top,pri[M*5],pos[M*5],lst[M*5];std::vector<ui>id[M];
char _input[1<<25|1],_output[1<<25|1],*_p1=_input,*_p2=_output;
inline ui read(){
	ui n(0);char s;while(!isdigit(s=*_p1++));while(n=n*10+(s&15),isdigit(s=*_p1++));return n;
}
inline void write(ui&n){
	static char s[10];ui top(0);while(s[++top]=n%10^48,n/=10);while(*_p2++=s[top],--top);
}
inline void sieve(const ui&M){
	ui i,j,x;
	for(i=2;i<=M;++i){
		if(!pos[i])pri[pos[i]=++top]=i;
		for(j=1;j<=pos[i]&&(x=i*pri[j])<=M;++j)pos[x]=j;
	}
}
void Modify(ui l,ui r,const ui&V){
	for(l+=G-1,r+=G+1;l^r^1;l>>=1,r>>=1){
		if(~l&1)prod[l^1]=1ull*prod[l^1]*V%mod;
		if(r&1)prod[r^1]=1ull*prod[r^1]*V%mod;
	}
}
inline ui Query(ui x){
	ui ans(1);x+=G;while(x)ans=1ull*ans*prod[x]%mod,x>>=1;return ans;
}
signed main(){
	std::cin.read(_input,sizeof _input);
	ui i,x(0),y,t;n=read();for(G=1;G<=n+1;G<<=1);for(i=1;i<=n+G;++i)prod[i]=1;
	for(i=1;i<=n;++i)(a[i]=read())>x&&(x=a[i]);Build(1);sieve(x);m=read();
	for(i=1;i<=m;++i)l[i]=read(),r[i]=read(),id[r[i]].push_back(i);
	for(i=1;i<=n;++i){
		for(x=a[i];x^1;){
			if(pos[x]^1)Modify(lst[pos[x]]+1,i,pri[pos[x]]-1);if(lst[pos[x]])Modify(1,lst[pos[x]],pri[pos[x]]);
			lst[y=pos[x]]=i;t=1;while(pos[x/pri[y]]==pos[x])t*=pri[y],x/=pri[y];x/=pri[y];if(t^1)Modify(1,i,t);
		}
		for(ui&ID:id[i])ans[ID]=Query(l[ID]);
	}
	for(i=1;i<=m;++i)write(ans[i]),*_p2++=10;std::cout.write(_output,_p2-_output);
}
```

---

## 作者：mygr (赞：2)

[Link](https://www.luogu.com.cn/problem/CF594D)

题目大意不用我翻译了吧


首先看到区间查询，尝试着往数据结构方向考虑

先简化一下问题：如何求一个十分大的数的欧拉函数？

我们联想到线性筛求欧拉函数的方法，即枚举这个数的每个质因数，然后就有

$$\varphi(n) = \Pi_{p^k \in pri_n} (p-1)\times p^{k-1}$$

很容易想到对于这个数 n ，它的答案其实就是所有数的乘积再乘上所有质因子减一除以质因子，即

$$\varphi(n) = n \times \Pi_{p \in pri_n} \frac{p-1}{p}$$

所以说事实上我们可以直接用线段树维护一个区间的和，然后寻找这个区间中所有的质因子即可但是线段树天生来不适合解决区间查询的集合并/交问题，所以我们从另一个角度思考，我们是不是可以选择一个数，把他的一个质因子由 $p$ 变为 $p-1$，这样子每次查询的时候就可以方便统计了。

当然这个点不是乱取的，我们要确保每次取到这个质因子时一定会取到这个点，并且这个改变的质因子只出现一次。

我们可以这样考虑，我们固定查询的右端点，我们把从此点出发，向左找到的第一个质因子改变，此时我们查询时如果向左寻找，则遇到的第一个此质因子一定是被更改过的那个点，就保证了“必定选中”和“只有一个”的条件。

我们发现状态是可以继承的，并且区间是静态的，所以可以用主席树优化，每次进行质因数分解更新向前节点即可。

注：但是这题卡空间，所以没法直接用主席树，可以把询问离线下来，然后直接在原树上修改即可（结果还是要离线啊

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int Max=2e5+5,Mod=1e9+7,nmax=1.1e6+5;
struct tree{
	int l,r;
	int mul;
	tree()
	{
		mul=1;
		l=r=0;
	}
}p[Max*50];
int cnt=0;
void pushup(int now)
{
	p[now].mul=(ll)p[p[now].l].mul*p[p[now].r].mul%Mod;
}
void update(int now,int loc,int l,int r,int x,int y)
{
	if(l==r)
	{
		p[now].mul=(ll)p[now].mul*x/y;
		return ;
	}
	int mid=(l+r)>>1;
	if(loc<=mid)
	{
		if(!p[now].l)
			p[now].l=++cnt;
		update(p[now].l,loc,l,mid,x,y);
	}
	else
	{
		if(!p[now].r)
			p[now].r=++cnt;
		update(p[now].r,loc,mid+1,r,x,y);
	}
	pushup(now);
}
ll query(int now,int l,int r,int nl,int nr)
{
	if(l<=nl and nr<=r)
		return p[now].mul;
	int mid=(nl+nr)>>1;
	ll ans=1;
	if(l<=mid)
		ans=(ll)ans*query(p[now].l,l,r,nl,mid)%Mod;
	if(mid<r)
		ans=(ll)ans*query(p[now].r,l,r,mid+1,nr)%Mod;
	return ans;
}
int pre[nmax],pri[nmax],tot=0,from[nmax];
bool is[nmax];
void init()
{
	for(int i=2;i<=nmax-5;i++)
	{
		if(!is[i])
		{
			from[i]=1;
			pri[++tot]=i;
		}
		for(int j=1;j<=tot and i*pri[j]<=nmax-5;j++)
		{
			is[i*pri[j]]=true;
			from[i*pri[j]]=i;
			if(i%pri[j]==0)
				break;
		}
	}
}
int n,q;
int a[Max],root[Max];

struct mode{
	int l,r,rank,ans;
}m[Max];
bool cmp(mode a,mode b)
{
	return a.r<b.r;
}
bool cmp2(mode a,mode b)
{
	return a.rank<b.rank;
}
int main()
{
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	init();
	root[0]=++cnt;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&m[i].l,&m[i].r);
		m[i].rank=i;
	}
	sort(m+1,m+1+q,cmp);
	int now=1;
	for(int i=1;i<=n;i++)
	{
		int ans=1,nu=a[i],pr;
		while(nu>1)
		{
			pr=nu/from[nu];
			nu=from[nu];
			if(pre[pr]!=i)
			{
				if(pre[pr])
					update(root[0],pre[pr],1,n,pr,pr-1);
				pre[pr]=i;
				ans*=pr-1;
			}
			else
				ans*=pr;
		}
		update(root[0],i,1,n,ans,1);
		
		while(m[now].r==i and now<=q)
		{
			m[now].ans=query(root[0],m[now].l,m[now].r,1,n);
			now++;
		}
	}
	sort(m+1,m+1+q,cmp2);
	for(int i=1;i<=q;i++)
		printf("%d\n",m[i].ans);
}
/*
10
1 2 3 4 5 6 7 8 9 10
7
1 1
3 8
5 6
4 8
8 10
7 9
7 10

1
4608
8
1536
192
144
1152
*/
```




---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF594D)。


## 思路

考虑将询问离线后扫描线，用线段树维护当前右端点为 $i$ 时每个左端点的答案。

对于新增的元素 $x$，现在的位置为 $i$，考虑将其分解质因数 $x=\prod_{k}p_k$，类似 [HH的项链](https://www.luogu.com.cn/problem/P1972)，对于每个质因子，记录它上一次出现的位置 $lst_p$，根据 $\varphi(p)=p-1,\varphi(p^k)=p^{k-1}(p-1)$，对于当前的质因子 $p$，在线段树上将区间 $[1,lst_p]$ 整体乘上 $p$，对区间 $[lst_p+1,i]$ 乘上 $p-1$，操作完记得更新 $lst_p$。

时间复杂度 $\mathcal{O}(Q\omega(v)\log n)$，其中 $v$ 是值域，$\omega(v)$ 表示 $[1,v]$ 中数的最大质因子个数，在本题范围内不会超过 $8$。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=3e5+6,V=1e6;
const int Mod=1e9+7;
int n,Q;
int a[Maxn];

int lst[V+5];
int ans[Maxn];
int lm[V+5];
vector<pair<int,int> >q[Maxn];

struct TREE{
    int l,r;
    ll val,tag;
}tree[Maxn<<2];

inline void pushup(int node){
    tree[node].val=tree[node<<1].val*tree[node<<1|1].val%Mod;
}
void buildtree(int node,int l,int r){
    tree[node].l=l;
    tree[node].r=r;
    tree[node].tag=1;
    if(l==r){
        tree[node].val=1;
        return ;
    }
    int mid=tree[node].l+tree[node].r>>1;
    buildtree(node<<1,l,mid);
    buildtree(node<<1|1,mid+1,r);
    pushup(node);
}

inline void spread(int node,int x){
    tree[node].val=tree[node].val*x%Mod;
    tree[node].tag=tree[node].tag*x%Mod;
}
inline void pushdown(int node){
    if(tree[node].tag==1) return ;
    spread(node<<1,tree[node].tag);
    spread(node<<1|1,tree[node].tag);
    tree[node].tag=1;
}
void modify(int node,int l,int r,int x){
    if(tree[node].l>=l and tree[node].r<=r){
        spread(node,x);
        return ;
    }
    pushdown(node);
    int mid=tree[node].l+tree[node].r>>1;
    if(l<=mid) modify(node<<1,l,r,x);
    if(r>mid) modify(node<<1|1,l,r,x);
    pushup(node);
}
ll query(int node,int x){
    if(tree[node].l==tree[node].r) return tree[node].val;
    int mid=tree[node].l+tree[node].r>>1;
    pushdown(node);
    if(x<=mid) return query(node<<1,x);
    else return query(node<<1|1,x);
}

bitset<V+5>isp;

int main(){
    for(int i=2;i<=V;i++){
        if(!isp.test(i)){
            lm[i]=i;
            for(int j=i+i;j<=V;j+=i){
                isp.set(j);
                if(!lm[j]) lm[j]=i;
            }
        }
    }

    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    buildtree(1,1,n);

    scanf("%d",&Q);
    for(int i=1;i<=Q;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        q[r].emplace_back(l,i);
    }
    
    for(int i=1;i<=n;i++){
        int num=a[i];
        
        while(num>1){
            int j=lm[num];
            modify(1,lst[j]+1,i,j-1);
            if(lst[j])modify(1,1,lst[j],j);
            lst[j]=i;
            num/=j;
        }
        for(auto [j,id]:q[i]) ans[id]=query(1,j);
    }
    for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Tenshi (赞：1)

使用莫队跑了 1499ms，应该是这题莫队的实现里前列的吧（心虚。

[提交记录](https://codeforces.com/contest/594/submission/259820687)

这里简单讲一下做法：

- 对于每一次查询，可以发现答案为 $\prod_{i\in[l, r]} a_i \times \prod_{p\in S(l, r)} (1-\frac{1}{p})$，其中 $S(l, r)$ 代表区间 $[l, r]$ 内所有 $a$ 值的质因子组成的集合。
- $\prod_{i\in[l, r]} a_i$ 很简单，直接在查询时用前缀积维护即可。
- 剩下的问题用一个桶在莫队过程中维护各种质因子的个数，$res$ 代表 $\prod_{p} (1-\frac{1}{p})$，然后当桶质因子种类数出现变更的时候就从 $res$ 中分别乘除 $(1-\frac{1}{p})$ 。
- 最后的工作就是考虑预处理，使用线性筛筛出每个数的最小质因子然后计算出数组 $a$ 每个值的质因数分解结果即可。

然而有个巨坑的细节，让我在 TLE30 了很多次：我在**值域**上开了存储质因数分解结果的 `vector`（相当于固定开 $10^6$ 个），后来发现改成开用**下标**维护的 `vector`（相当于固定开 $2\times10^5$ 个）后快了很多。

完整代码见上面提交记录，下面是带注释的主要代码：

```cpp
const int N=2e5+5, M=1e6+5, mod=1e9+7;

int n, m, w[N];
int p[N];

struct Query{
	int id, l, r, k;
	bool operator < (const Query &o)const{
		return k==o.k? ((k&1)? r<o.r: r>o.r): k<o.k;
	}
}q[N];

int b[M]; // 桶
vector<int> f[N]; // 这里就是上面说的细节所在数组
int pp[M], ipp[M]; // 预处理出 (1-1/p) 以及 1/(1-1/p)

int fpow(int x, int p){
	int res=1;
	for(; p; p>>=1, x=1LL*x*x%mod) if(p&1) res=1LL*res*x%mod;
	return res%mod;
}

int inv(int x){
	return fpow(x, mod-2);
}

int mul(int x, int y){
	return 1LL*x*y%mod;
}

vector<int> pr; // 维护质数
bool isc[M]; // 是否为合数 
int minf[M]; // minf[x] 为 x 的最小质因数

void init(){
	rep(i, 2, M-1){
		if(!isc[i]){
			pp[i]=1-inv(i)+mod;
			ipp[i]=inv(pp[i]);
			pr.pb(i);
			minf[i]=i;
		}
		for(int j=0; pr[j]*i<M; j++){
			isc[pr[j]*i]=true;
			minf[pr[j]*i]=pr[j];
			if(i%pr[j]==0) break;
		}
	}
}

int res=1;
int ans[N];

void add(int i){
	auto &fac=f[i];
	for(auto &e: fac){
		++b[e];
		if(b[e]==1) res=mul(res, pp[e]);
	}
}

void del(int i){
	auto &fac=f[i];
	for(auto &e: fac){
		--b[e];
		if(!b[e]) res=mul(res, ipp[e]);
	}
}

signed main(){
	init();
	p[0]=1;
	cin>>n;
	rep(i, 1, n) read(w[i]), p[i]=mul(p[i-1], w[i]);
	rep(i, 1, n){
		int val=w[i];
		while(val>1){
			int mf=minf[val];
			while(val%mf==0) val/=mf;
			f[i].pb(mf);
		}
	}
	
	cin>>m;
	const int len=n*1.5/sqrt(m);
	// const int len=870;
	debug(len);
	rep(i, 1, m){
		int l, r; read(l), read(r);
		q[i]={i, l, r, l/len};
	}
	
	sort(q+1, q+1+m);
	
	for(int i=0, j=1, k=1; k<=m; k++){
		auto [id, l, r, _]=q[k];
		while(j>l) add(--j);
		while(i<r) add(++i);
		while(j<l) del(j++);
		while(i>r) del(i--);

		ans[id]=mul(res, mul(p[r], inv(p[l-1])));
	}
	rep(i, 1, m) printf("%d\n", ans[i]);
	
	return 0;
}
```

---

## 作者：1saunoya (赞：1)

设 
$$x = \prod_{i=1}^{cnt} p_i^{k_i} [p_i\in prime]$$

那么显然
$$\varphi(x) = x*\frac{1}
{\prod_{i=1}^{cnt}p_i}$$


因为每个质数只会出现一次，所以当成数颜色，同 [HH的项链]，这题就没了


```cpp
// powered by c++11
// by Isaunoya
#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)
using namespace std;
using db = double;
using ll = long long;
using uint = unsigned int;
#define int long long
using pii = pair<int, int>;
#define ve vector
#define Tp template
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back
#define fir first
#define sec second
// the cmin && cmax
Tp<class T> void cmax(T& x, const T& y) {
  if (x < y) x = y;
}
Tp<class T> void cmin(T& x, const T& y) {
  if (x > y) x = y;
}
// sort , unique , reverse
Tp<class T> void sort(ve<T>& v) { sort(all(v)); }
Tp<class T> void unique(ve<T>& v) {
  sort(all(v));
  v.erase(unique(all(v)), v.end());
}
Tp<class T> void reverse(ve<T>& v) { reverse(all(v)); }
const int SZ = 0x191981;
struct FILEIN {
  ~FILEIN() {}
  char qwq[SZ], *S = qwq, *T = qwq, ch;
  char GETC() { return (S == T) && (T = (S = qwq) + fread(qwq, 1, SZ, stdin), S == T) ? EOF : *S++; }
  FILEIN& operator>>(char& c) {
    while (isspace(c = GETC()))
      ;
    return *this;
  }
  FILEIN& operator>>(string& s) {
    while (isspace(ch = GETC()))
      ;
    s = ch;
    while (!isspace(ch = GETC())) s += ch;
    return *this;
  }
  Tp<class T> void read(T& x) {
    bool sign = 1;
    while ((ch = GETC()) < 0x30)
      if (ch == 0x2d) sign = 0;
    x = (ch ^ 0x30);
    while ((ch = GETC()) > 0x2f) x = x * 0xa + (ch ^ 0x30);
    x = sign ? x : -x;
  }
  FILEIN& operator>>(int& x) { return read(x), *this; }
  FILEIN& operator>>(signed& x) { return read(x), *this; }
  FILEIN& operator>>(unsigned& x) { return read(x), *this; }
} in;
struct FILEOUT {
  const static int LIMIT = 0x114514;
  char quq[SZ], ST[0x114];
  signed sz, O;
  ~FILEOUT() { flush(); }
  void flush() {
    fwrite(quq, 1, O, stdout);
    fflush(stdout);
    O = 0;
  }
  FILEOUT& operator<<(char c) { return quq[O++] = c, *this; }
  FILEOUT& operator<<(string str) {
    if (O > LIMIT) flush();
    for (char c : str) quq[O++] = c;
    return *this;
  }
  Tp<class T> void write(T x) {
    if (O > LIMIT) flush();
    if (x < 0) {
      quq[O++] = 0x2d;
      x = -x;
    }
    do {
      ST[++sz] = x % 0xa ^ 0x30;
      x /= 0xa;
    } while (x);
    while (sz) quq[O++] = ST[sz--];
    return;
  }
  FILEOUT& operator<<(int x) { return write(x), *this; }
  FILEOUT& operator<<(signed x) { return write(x), *this; }
  FILEOUT& operator<<(unsigned x) { return write(x), *this; }
} out;

int n, q;
const int maxn = 2e5 + 52;
const int maxp = 1e6 + 61;
const int mod = 1e9 + 7;
int a[maxn], las[maxp];
inline int qpow(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = x * x % mod)
    if (y & 1) res = res * x % mod;
  return res;
}
inline int inv(int x) { return qpow(x, mod - 2); }
struct BIT {
  int c[maxn];
  inline int low(int x) { return x & -x; }
  inline void upd(int x, int y) {
    for (; x <= n; x += low(x)) c[x] = c[x] * y % mod;
  }
  inline int qry(int x) {
    int ans = 1;
    for (; x; x ^= low(x)) ans = ans * c[x] % mod;
    return ans;
  }
} bit;
vector<int> prime[maxp];
vector<pii> v[maxn];
void add(int pos) {
  for (auto x : prime[a[pos]]) {
    if (las[x]) bit.upd(las[x], x), bit.upd(las[x], inv(x - 1));
    bit.upd(pos, inv(x)), bit.upd(pos, x - 1);
    las[x] = pos;
  }
}
int pre[maxn];
int ans[maxn];
signed main() {
#ifdef _WIN64
  freopen("testdata.in", "r", stdin);
#else
  ios_base ::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
#endif
  // code begin.
  in >> n;
  int mx = 0;
  rep(i, 1, n) in >> a[i], cmax(mx, a[i]);
  pre[0] = 1;
  rep(i, 1, n) pre[i] = pre[i - 1] * a[i] % mod;
  vector<bool> vis(mx + 1, 0);
  rep(i, 2, mx) if (!vis[i]) {
    prime[i].push_back(i);
    for (int j = (i << 1); j <= mx; j += i) prime[j].push_back(i), vis[j] = 1;
  }
  in >> q;
  rep(i, 1, q) {
    int l, r;
    in >> l >> r;
    v[r].push_back({ l, i });
  }
  rep(i, 0, n) bit.c[i] = 1;
  rep(i, 1, n) {
    add(i);
    for (auto x : v[i])
      ans[x.second] =
          pre[i] * inv(pre[x.first - 1]) % mod * bit.qry(i) % mod * inv(bit.qry(x.first - 1)) % mod;
  }
  rep(i, 1, q) out << ans[i] << '\n';
  return 0;
  // code end.
}
```

---

## 作者：liuyidu (赞：0)

欧拉函数+树状数组

首先看看[欧拉函数](https://blog.csdn.net/TheWayForDream/article/details/113811341)吧。

现在讲讲怎么处理，首先离线，之后我们可以想到每个质因子对单个位置只有一次贡献，那么我们可以开一个数组，记录每个质因子上次产生贡献的位置，并在离线处理的过程中，不断更新就好了。细节比较多，可以在代码里看看，主要就是结合上面的结论，进行操作。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,M=1e6+10,MOD=1e9+7;
int prime[M],tot,f[M],ans[N],pre[N];//f存每个点最小的质因子 
int lst[M];//lst 存每个数组是否出现过，出现在哪个位置 
bool isprime[M];
void sieve(int n){//欧拉筛 
	for(int i=2;i<=n;++i){
		if(!isprime[i])prime[++tot]=i,f[i]=i;
		for(int j=1;j<=tot&&i*prime[j]<=n;++j){
			isprime[i*prime[j]]=1;
			f[i*prime[j]]=prime[j];
			if(i%prime[j]==0)break;
		}
	}
}
int n,q,a[N];
struct node{
	int l,r,id;
	bool operator <(const node &a)const{
		if(r==a.r)return l<a.l;
		return r<a.r;
	}
}que[N];
inline int lowbit(int x){
	return x&-x;
}
inline int qpow(int x,int p) {
	int ret=1;
	for(;p;p>>=1,x=1ll*x*x%MOD) if(p&1) ret=1ll*ret*x%MOD;
	return ret;
}
inline int inv(int x) {//逆元 
	return qpow(x,MOD-2);
}
int tr[N];
void add(int i,int x){
	for(;i<=n;i+=i&-i)tr[i]=1ll*tr[i]*x%MOD;
}
int query(int i){
	int sum=1;
	for(;i;i-=i&-i)sum=1ll*sum*tr[i]%MOD;
	return sum;
}
void update(int i){
	for(int x=a[i],p=f[x];x>1;p=f[x]){//通过 f[x] 我们可以得到 a[i] 的所有质因子，优化空间 
		add(i,p-1);
		add(i,inv(p));
		if(lst[p])add(lst[p],inv(p-1)),add(lst[p],p);
		lst[p]=i;
		while(x%p==0)x/=p;
	}
}
int main(){
	sieve(M-10);
	scanf("%d",&n);
	pre[0]=1;
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),pre[i]=1ll*pre[i-1]*a[i]%MOD,tr[i]=1;
	scanf("%d",&q);
	for(int i=1;i<=q;++i)scanf("%d%d",&que[i].l,&que[i].r),que[i].id=i;
	sort(que+1,que+q+1);
	int j=0;
	for(int i=1;i<=q;++i){
		int x=que[i].l,y=que[i].r;
		while(j<y)update(++j);//类似hh的项链，不断后移 
		int now=1;
		ans[que[i].id]=1ll*pre[y]*inv(pre[x-1])%MOD*query(y)%MOD*inv(query(x-1))%MOD;
	}
	for(int i=1;i<=q;++i){
		cout<<ans[i]<<endl;
	}
}
```

---

## 作者：Transfixion_ (赞：0)

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/CF594D)

## $\textbf{Description}$

给定长为 $n$ 的序列 $a$，$m$ 组询问，每次询问给出 $l,r$，求：

$$\varphi\left(\prod_{i=l}^r a_i\right)$$

答案对 $(10^9+7)$ 取模。

$n,m\le 2\times 10^5,V\le 10^6$。其中 $V=\max a_i$。

## $\textbf{Solution}$

记号说明：推导过程中 $p$ 均表示质数。

首先 $\varphi$ 有一个计算公式：

$$\varphi(n)=n\prod_{p|n} \frac{p-1}{p}$$

从而原式可以做以下变形：

$$\varphi\left(\prod_{i=l}^r a_i\right)=\left(\prod_{i=l}^ra_i\right)\left( \prod_{\exists l\le i\le r,p|a_i}\frac{p-1}{p}\right)$$

前面那个 $\prod$ 可以前缀积搞定。

考虑后面那个 $\prod$。相同的 $p$ 产生的贡献只算一次，这与区间数颜色是极为相似的，莫队维护后面那个 $\prod$ 即可。

当然直接维护你会 T 得很惨。

---

新的记号说明：

- 与上文的含义不同，下文的 $p$ 表示模数 $(10^9+7)$。

- 称莫队的时间复杂度为 $\mathcal O(f(n))-\mathcal O(g(n))$ 表示莫队指针移动的复杂度为 $\mathcal O(f(n))$，求当前区间的答案的时间复杂度为 $\mathcal O(g(n))$。

- $\omega(n)$ 表示 $n$ 的不同质因子个数。

随便写写的话时间复杂度 $\mathcal O(m\sqrt n\log p\cdot \omega(V))$。

$5\times 10^{10}$ 过不了一点。

---

虽然这个 $\log p$ 看起来很虚，但还是有点影响的。

预处理一下就可以把 $\log$ 去掉，比如：

类埃氏筛地，预处理出 $10^6$ 以内所有数的质因子集合，顺便线性求逆元，$\mathcal O(V\log V)$。

>注：
>
>这看上去是个优化，不过其实做了很多无用功，是不必要的，理由如下。
>
>线性求出的逆元只能给 $a$ 用，因为只有 $a$ 的值域是 $[1,V]$，其他地方如前缀积的值域是 $[0,p)$ 而非 $[1,V]$。
>
>然而 $a$ 是静态的，$n$ 和 $V$ 相差一个数量级，还不如一个一个地求，这样是 $\mathcal O(n\log V)$ 的（@xhgua 的写法）。

至于处理所有前缀积与前缀积逆元，写不写都无所谓，放在莫队里求也可以。

因为前面已经处理掉了逆元，从而莫队中移动指正的复杂度由 $\mathcal O(\log n\cdot \omega(V))$ 变为 $\mathcal O(\omega(V))$。

总时间复杂度 $\mathcal O(m\sqrt n\cdot\omega(V))$，成功地去掉了 $\log$。

同时实现了 $5\times 10^{10}\to3\times 10^9$ 的飞跃。

不过以上的这种预处理方式很烂很慢，具体来说：

我作为机房公认的小常选手使用了上述写法，调了六七次次块长都稳定在 test #30 T 掉。
 
公认的大常选手 @xhgua 复杂度与我相同，但在预处理上和我有一定差异，最开始一样是 T，但是他调了一下块长就通过了此题。

说明这部分的实现和对块长的分析是很重要的！虽然我不会！

---

莫队的话 $\mathcal O(m\sqrt n)$ 的复杂度摆在这里了，只能想办法把 $\omega(V)$ 去掉。

回忆静态区间 $k\text{th}$，若使用普通平衡树维护当前区间，则莫队的复杂度是 $\mathcal O(\log n)-\mathcal O(\log n)$，总复杂度为 $\mathcal O(m\sqrt n\log n)$；若使用值域分块，则莫队的复杂度变为 $\mathcal O(1)-\mathcal O(\sqrt n)$，总复杂度变为 $\mathcal O(m\sqrt n+m\sqrt V)$，优于原本的写法。

对于本道题目，刚才讲述的方法中，莫队的复杂度为 $\mathcal O(\omega(V))-\mathcal O(1)$，而我们需要的是 $\mathcal O(1)-\mathcal O(\le \frac{3\times 10^8}{m})$，我知道这不标准，但就是这个意思：牺牲求当前区间答案的复杂度来换取移动指针的 $\mathcal O(1)$。

注意到正整数 $n$ 至多只有一个质因子 $\ge\sqrt n$，也就是说剩下 $\omega(n)-1$ 个质因子都 $< \sqrt n$，这让我们联想到根号分治。

设阈值 $T=\sqrt V$，对于所有 $\le T$ 的质因子，暴力处理并前缀和优化；对于 $>T$ 的质因子，我们选择在指针移动的时候维护。

不难发现每次指针移动只需要考虑至多一个质因子的影响，从而该莫队的复杂度变为 $\mathcal O(1)-\mathcal O(\sqrt V)$。

总时间复杂度为 $\mathcal O(m\sqrt n+m\sqrt V)$。

块长取 $\frac n{\sqrt m}$ 最优。瞎调块长之后差不多跑了 2.1s，被吊打。

以及事实上离线 BIT 非常好写。

## $\textbf{AC Code}$

```cpp
#include <bits/stdc++.h>
#define rep(i, st, ed) for(int i = (st); i <= (ed); i++)
#define per(i, st, ed) for(int i = (st); i >= (ed); i--)
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 20], *p1 = buf, *p2 = buf;
template <typename _Tp> inline void read(_Tp& x) {
	char c = gc(); x = 0; bool f = 0;
	for(; !std::isdigit(c); c = gc()) f |= c == '-';
	for(; std::isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c ^ 48);
	f ? x = ~x + 1 : 1;
}
inline void read(std::string& x) {
	x.clear(); char c = gc(); for(; !std::isgraph(c); c = gc());
	for(; std::isgraph(c); c = gc()) x.push_back(c);
}
template <typename _Tp, typename ...Args>
inline void read(_Tp& x, Args& ...args) {
	read(x), read(args...);
}

typedef long long i64;
constexpr int N = 2e5 + 5;
constexpr int V = 1e6;
constexpr int B = 800;
constexpr int T = 170;
constexpr int mod = 1e9 + 7;
int n, m, a[N], prd[N], iprd[N], inv[V + 5];
int pr[V + 5], tot, maxd[V + 5], sum[T + 5][N], val[V + 5], ival[V + 5];
std::bitset<V + 5> vis;

int cnt[V + 5], cur = 1;
inline void add(int x) {
	const int i = maxd[x];
	if(i > T) {
		if(cnt[i]++) return ;
		cur = 1ll * cur * val[pr[i]] % mod;
	}
}

inline void del(int x) {
	const int i = maxd[x];
	if(i > T) {
		if(--cnt[i]) return ;
		cur = 1ll * cur * ival[pr[i]] % mod;
	}
}

struct Query {
	int l, r, id, bel;
} q[N];
int ans[N];

inline int qry(int l, int r) {
	int res = 1ll * prd[r] * iprd[l - 1] % mod * cur % mod;
	rep(i, 1, T) if(sum[i][r] - sum[i][l - 1]) res = 1ll * res * val[pr[i]] % mod;
	return res;
}

signed main() {
	read(n); rep(i, 1, n) read(a[i]);
	read(m); rep(i, 1, m) read(q[i].l, q[i].r), q[i].id = i;
	inv[0] = inv[1] = 1;
	rep(i, 2, V) {
		inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
		val[i] = 1ll * (i - 1) * inv[i] % mod;
		ival[i] = 1ll * inv[i - 1] * i % mod;
		if(vis[i]) continue; pr[++tot] = i;
		for(int j = i; j <= V; j += i) {
			vis[j] = 1, maxd[j] = tot;
		}
	}
	prd[0] = 1, iprd[0] = 1;
	rep(i, 1, n) prd[i] = 1ll * prd[i - 1] * a[i] % mod;
	rep(i, 1, n) iprd[i] = 1ll * iprd[i - 1] * inv[a[i]] % mod;
	rep(i, 1, n) {
		rep(x, 1, T) sum[x][i] = sum[x][i - 1];
		for(int x = a[i]; x > 1; x /= pr[maxd[x]]) {
			if(maxd[x] <= T) sum[maxd[x]][i]++;
		}
	}
	rep(i, 1, m) q[i].bel = (q[i].l - 1) / B;
	auto cmp = [&](const Query lhs, const Query rhs) {
		if(lhs.bel ^ rhs.bel) return lhs.l < rhs.l;
		if(lhs.bel & 1) return lhs.r > rhs.r;
		return lhs.r < rhs.r;
	};
	std::sort(q + 1, q + m + 1, cmp);
	for(int i = 1, l = 1, r = 0; i <= m; i++) {
		int ql = q[i].l, qr = q[i].r;
		while(l > ql) add(a[--l]);
		while(r < qr) add(a[++r]);
		while(l < ql) del(a[l++]);
		while(r > qr) del(a[r--]);
		ans[q[i].id] = qry(ql, qr);
	}
	rep(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：wcyQwQ (赞：0)

首先考虑欧拉函数的计算式 $\varphi(n) = n\prod_{p | n} \dfrac{p - 1}{p}$，所以我们考虑对每一个 $a_i$ 进行因式分解，然后计算每个质因子的贡献。

不难发现我们考虑一下重复质因子的贡献就做完了，这玩意在线不太好做，所以我们考虑离线。将询问按右端点排序，然后考虑一个一个加入，假设我们现在要在第 $i$ 个位置加入一个质因子 $p$，我们用 $last_p$ 表示 $p$ 上次出现的位置，然后我们在 $last_p$ 上乘一个 $\dfrac{p}{p - 1}$，再在 $i$ 上乘一个 $\dfrac{p - 1}{p}$ 即可，注意更新 $last_p$ 的值。

开个树状数组维护区间乘积就做完了，时间复杂度 $O(n\log n\log V)$。[Code](https://codeforces.com/contest/594/submission/207056887)

---

## 作者：Epoch_L (赞：0)

## Solution
挺好一道数论题。

考虑到欧拉函数的一个计算方法：

$$
\varphi(n)=n\prod_{i=1}^s\frac {p_i-1}{p_i}
$$

那么我们就可以把答案写成：

$$
\varphi(\prod_{i=l}^ra_i)=\prod_{i=l}^ra_i\times \prod_i(\frac{p_i-1}{p_i})
$$

其中 $p_i$ 代表 $[l,r]$ 中所有数质因子的并集。简单点来说，就是区间乘积乘上所有 $\Large\frac {p_i-1}{p_i}$。

注意到 $p_i$ 是不能重复贡献的，这就好比种类，于是我们想到了 [P1972](https://www.luogu.com.cn/problem/P1972)，这题就是求区间种类数。所以按照同样的方法，把询问离线并按照右端点排序，依次加入 $a_i$，用树状数组维护即可。

具体地，对于 $a_i$ 的一个质因子 $p_i$，先在 $i$ 位置上乘 $\Large\frac {p_i-1}{p_i}$，再记录 $p_i$ 出现的前一个位置（若没有则不需操作），将其除以 $\Large\frac {p_i-1}{p_i}$，保证不重复。

其实会 P1972 这题就做完了，做法十分相似。

最后关于常数的问题，不能直接 $O(\sqrt{n})$ 求质因数，可以先做一遍线筛，把每个数的最小质因子记为 $f_i$，然后一直 $p=f_{p}$ 即可。还可以把快速幂换成线性求逆元。

---

## 作者：orz_z (赞：0)

根据 $\varphi$ 的规律，设 $n=\prod\limits_{i}{p_i^{a_i}}$，则有 $\varphi(n)=n\times\prod\limits_{i}{\frac{p_i-1}{p_i}}$。

故区间 $\varphi$ 可先前缀积算前面那个，后面那么直接看区间出现哪些质数即可。

考虑离线，我们将询问按照右端点排序，维护一个右指针，将 $a_i$ 逐个加入，用树状数组维护每个位置对答案的贡献。

预处理所有质数，$\log V$ 枚举找质因子，对于重复出现的质因子，维护 $lst_i$ 表示质因子 $i$ 上次出现的位置，将上次的贡献消去即可。

时间复杂度 $\mathcal O((n+q)\log n\log V)$（其中 $V$ 表示值域 $[1,n]$）。

---

## 作者：hwk0518 (赞：0)

容易发现，$\phi(\prod_{i=l \to r}a_i)$

$=\prod_{i=l \to r}a_i*\prod_{i=1 \to 10^6}f(i)*[i|\prod_{j=l \to r}a_j]$

其中$f(i)=\frac{i-1}{i}$.

前半部分可以预处理前缀和后查询。

如果将每个数分解质因数，开$n$个$vector$，将$a_i$所有质因数插入$i$号$vector$，后半部分即询问一个区间内不同数的乘积。发现题目允许离线。所以将所有询问按右端点排序，用一个指针从头扫到尾，扫到$i$时回答右端点为$i$的所有询问。将质因数插入树状数组上它最后出现的位置，询问即为查询$l$到$r$所有数的乘积。例如：

$5,35,216,4$

$5,7$应插在$2$号位，$3$应插在$3$号位，$2$应插在$4$号位。

时间复杂度$O(n*\sqrt{\max_{i=1 \to n}a_i}+n*10*log \max_{i=1 \to n}a_i)$.

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
#include<vector>
using namespace std;

const int N=2e5+5;
const int M=1e6+5;
const int mod=1e9+7;
int n,q,a[N],s[N],lat[M];
vector<int> v[N];
struct node
{
	int l,r,id,ans;
};
node que[N];

int F_p(int x,int y)
{
	int bas=x,ret=1;
	while(y)
	{
		if(y&1) ret=1LL*ret*bas%mod;
		bas=1LL*bas*bas%mod;
		y>>=1;
	}
	return ret;
}

struct Tree_Array
{
	int c[M];
	int lowbit(int x)
	{
		return x&(-x);
	}
	
	void build()
	{
		int i;
		for(i=1;i<=n;++i) c[i]=1;
	}
	
	void update(int pos,int x)
	{
		while(pos<=M)
		{
			c[pos]=1LL*c[pos]*x%mod;
			pos+=lowbit(pos);
		}
	}
	
	int query(int pos)
	{
		int ret=1;
		while(pos)
		{
			ret=1LL*ret*c[pos]%mod;
			pos-=lowbit(pos);
		}
		return ret;
	}
	int query(int l,int r)
	{
		return 1LL*query(r)*F_p(query(l-1),mod-2)%mod;
	}
};
Tree_Array SS;

bool cmp(node x,node y)
{
	return x.r<y.r;
}
bool id_cmp(node x,node y)
{
	return x.id<y.id;
}

void init()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;++i) scanf("%d",&a[i]);
	s[0]=1;for(i=1;i<=n;++i) s[i]=1LL*s[i-1]*a[i]%mod;
	SS.build();
}

void prework()
{
	int i,j;
	for(i=1;i<=n;++i)
	{
		for(j=2;j*j<=a[i];++j)
			if(a[i]%j==0)
			{
				while(a[i]%j==0) a[i]/=j;
				v[i].push_back(j);
			}
		if(a[i]>1) v[i].push_back(a[i]);
	}
}

int cal(int x)
{
	return 1LL*(x-1)*F_p(x,mod-2)%mod;
}
void calc(int x)
{
	int i,sz=v[x].size();
	for(i=0;i<sz;++i)
	{
		if(lat[v[x][i]])
			SS.update(lat[v[x][i]],F_p(cal(v[x][i]),mod-2));
		SS.update(x,cal(v[x][i]));
		lat[v[x][i]]=x;
	}
}

void work()
{
	int i,j;
	scanf("%d",&q);
	for(i=1;i<=q;++i)
	{
		scanf("%d%d",&que[i].l,&que[i].r);
		que[i].id=i;
	}
	
	sort(que+1,que+q+1,cmp);
	int las=0;
	for(i=1;i<=q;++i)
	{
		for(j=las+1;j<=que[i].r;++j) calc(j);
		las=que[i].r;
		que[i].ans=SS.query(que[i].l,que[i].r);
	}
	sort(que+1,que+q+1,id_cmp);
	
	for(i=1;i<=q;++i)
		printf("%d\n",1LL*que[i].ans*s[que[i].r]%mod*F_p(s[que[i].l-1],mod-2)%mod);
}

int main()
{
	init();prework();work();
	return 0;
}

```

---

