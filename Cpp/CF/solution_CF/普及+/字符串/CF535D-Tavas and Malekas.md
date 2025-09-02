# Tavas and Malekas

## 题目描述

Tavas is a strange creature. Usually "zzz" comes out of people's mouth while sleeping, but string $ s $ of length $ n $ comes out from Tavas' mouth instead.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535D/edec2eae8d180d77009c457fa18d1007b3d9ea05.png)Today Tavas fell asleep in Malekas' place. While he was sleeping, Malekas did a little process on $ s $ . Malekas has a favorite string $ p $ . He determined all positions $ x_{1}&lt;x_{2}&lt;...&lt;x_{k} $ where $ p $ matches $ s $ . More formally, for each $ x_{i} $ ( $ 1<=i<=k $ ) he condition $ s_{xi}s_{xi}+1...\ s_{xi}+|p|-1=p $ is fullfilled.

Then Malekas wrote down one of subsequences of $ x_{1},x_{2},...\ x_{k} $ (possibly, he didn't write anything) on a piece of paper. Here a sequence $ b $ is a subsequence of sequence $ a $ if and only if we can turn $ a $ into $ b $ by removing some of its elements (maybe no one of them or all).

After Tavas woke up, Malekas told him everything. He couldn't remember string $ s $ , but he knew that both $ p $ and $ s $ only contains lowercase English letters and also he had the subsequence he had written on that piece of paper.

Tavas wonders, what is the number of possible values of $ s $ ? He asked SaDDas, but he wasn't smart enough to solve this. So, Tavas asked you to calculate this number for him.

Answer can be very large, so Tavas wants you to print the answer modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample test all strings of form "ioioi?" where the question mark replaces arbitrary English letter satisfy.

Here $ |x| $ denotes the length of string x.

Please note that it's possible that there is no such string (answer is 0).

## 样例 #1

### 输入

```
6 2
ioi
1 3
```

### 输出

```
26
```

## 样例 #2

### 输入

```
5 2
ioi
1 2
```

### 输出

```
0
```

# 题解

## 作者：tuzhewen (赞：9)

那么这题看见各位都是用kmp做的，那么本蒟蒻再此提供一种$Z$函数的做法

首先我们把模式串$p$的$Z$数组计算好。

然后对于我们每次读进来的一个位置，我们要判断它是否可行，有两种情况：1.它没有雨前面任何一个位置发生冲突，那么这个位置一定是合法的。2.如果它于前面的位置有冲突了，但是重合的位置是一样的（比如第一个样例），那么也是可行的。

像第一种情况,因为题目给的位置是递增的，那么直接判断`x+len_p<=y`即珂，其中`len_p`是字符串（模式串）的长度。

那么第二种情况就是要看$Z$数组的用法了。可以发现，如果说这个模式串的前缀与后缀的$LCP(Longest Common Prefix)$大于等于了重合的长度，那么我们就可以放。举个栗子：

对于样例$1$而言：第一个`ioi`与第二个`ioi`的重合长度为$1$，并且第二个`ioi`的前缀与第一个`ioi`的后缀是完全重合的，即重合长度可以大于等于$1$，那么就可以放。

再来举一个，如果说要串$ooppo$放在$1$、$3$的位置上，那么就会发生冲突，因为这个串的前缀与后缀最大的重合长度只有$1$，但是重合长度是$3$，那么一定会发生冲突，所以不可取。

最后就是快速幂算一下的事情了，上代码！

$ACcode:$
```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
using namespace std;
const int N=1e6+5,mod=1e9+7;
inline int qpow(int a,int b) {
	int res=1,tp=a;
	while(b) {
		if(b&1)res=1ll*res*tp%mod;
		tp=1ll*tp*tp%mod;
		b>>=1;
	}
	return res;
}
int lenp,n,m;
char p[N];
int z[N],pos[N];
void get_z(char *s1,int n) {
	int L=0,R=0;
	F(i,1,n-1) {
		if(i>R) {
			L=i,R=i;
			while(R<n&&s1[R-L]==s1[R])R++;
			z[i]=--R-L+1;
		}
		else {
			int k=i-L;
			if(z[k]<R-i+1)z[i]=z[k];
			else {
				L=i;
				while(R<n&&s1[R-L]==s1[R]) R++;
				z[i]=--R-L+1;
			}
		}
	}
}
int ans,sum[N],ls;
bool check(int x,int y) {
	if(y-x>=lenp) return true;
	return z[y-x]>=x+lenp-y;
}
int main() {
	scanf("%d%d",&n,&m);
	if(!m) return printf("%d\n",qpow(26,n)),0;
	scanf("%s",p);
	lenp=strlen(p);
	get_z(p,lenp);
	F(i,1,m) scanf("%d",&pos[i]),pos[i]--,sum[pos[i]]++,sum[pos[i]+lenp]--;
	F(i,2,m) {
		if(!check(pos[i-1],pos[i])) return puts("0"),0;
	}
	F(i,0,n-1) {
		sum[i]+=sum[i-1];
		if(!sum[i]) ans++;
	}
	return printf("%d\n",qpow(26,ans)),0;
}
```

~~求反手留赞~~

---

## 作者：Computer1828 (赞：2)

首先我们发现假如有可能，那么答案就是 $26^c$，其中 $c$ 表示空白（即没有填字符）位置数。

然后我们发现，只需要比较相邻两个放入的串是否合法就行。如下图，若 A、B 合法，B、C 合法，则 A、C 一定合法。这可以这么理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/70wrg1je.png)

因为 A 与 B 合法，B 与 C 合法，那么两条红线之间的部分是相同的，两条蓝线之间的部分也是相同的。绿线是 A 和 B 的公共部分，同时也是 B 和 C 的公共部分，所以 A、B 合法与 B、C 合法是可以同时存在的，所以只需比较相邻串即可。

也就是比较前一个的后缀和后一个的前缀，这可以哈希。

代码：

```cpp
#define N 1000005
#define ll long long
#define mod 1000000007
#define mm 998244333

int n,m,a[N];char p[N];
ll pre[N],suf[N],pw[N];
bool vis[N];
int main(){
	scanf("%d%d",&n,&m);
	if(m == 0) return printf("%lld",qpow(26,n)),0;
	scanf("%s",p+1);int len = strlen(p+1);
	pw[0] = 1;
	for(int i = 1;i<=len;++i) pre[i] = (pre[i-1]*26+(p[i]-'a'))%mm,pw[i] = pw[i-1]*26%mm;
	for(int i = len;i>=1;--i) suf[i] = (suf[i+1]+1ll*(p[i]-'a')*pw[len-i])%mm;
	scanf("%d",&a[1]);
	for(int i = 0;i<len;++i) vis[a[1]+i] = true;
	for(int i = 2;i<=m;++i){
		scanf("%d",a+i);
		if(a[i-1]+len-1 >= a[i]){
			if(suf[a[i]-a[i-1]+1] != pre[a[i-1]+len-a[i]]) return printf("0"),0;
			else for(int j = a[i-1]+len;j<=a[i]+len-1;++j) vis[j] = true;
		}else for(int j = a[i];j<=a[i]+len-1;++j) vis[j] = true;
	}
	ll ans = 0;
	for(int i = 1;i<=n;++i) if(!vis[i]) ans++;
	printf("%lld",qpow(26,ans));
	return 0;
}
```

---

## 作者：fighter (赞：2)



~~阅读理解题~~

## 题意解释

给定文本串的长度$n$和一个模式串$s$，并且已知模式串在文本串中某些出现位置（不一定仅在这些位置出现），求可能的文本串的数量。

## 分析

首先输入有可能出现方案为0的情况（即不合法），于是我们先考虑不合法的判断。

显而易见的是当$s$出现的结尾位置大于$n$时，直接可以判定为不合法。

然后就是当两个模式串出现位置有重叠时，假如重叠部分匹配不上，那么显然无解。（具体判定方式下文会将）

如果有解，那么我们只要统计文本串内有多少位置没有被模式串覆盖，记为$cnt$，那么答案就是$26^{cnt}$。

---

具体来考虑如何判断重叠部分是否匹配。显然重叠部分是模式串的一个后缀和前缀的重叠，于是我们只要判断当前位置的后缀和前缀是否匹配。而这个判断可以用两种方式实现：$KMP$和字符串哈希。

### KMP

我们发现问题和$KMP$算法中的$next$数组定义类似，于是我们可以想到：以模式串末尾为起始位置，一直跳$next$指针，途中经过的位置的前缀一定和后缀相等（可以想想$next$数组的意义）。那么我们只要把这些位置标记出来，只有在这些位置上重叠，前缀和后缀才有可能相等。

### 字符串哈希

涉及到字符串的比较，那么肯定可以想到字符串哈希。我们可以先预处理模式串的哈希值，然后在重叠的时候判断前缀和后缀是否相等即可。

## 代码

数据有坑，要特判$m=0$的情况。

### KMP

```cpp
#include <bits/stdc++.h>
#define ll long long
#define P 1000000007
#define MAX 1000005
using namespace std;

ll qpow(ll a, ll n){
    ll res = 1;
    while(n){
        if(n&1) res = res*a % P;
        a = a*a%P;
        n >>= 1;
    }
    return res;
}

char s[MAX];
int n, m, len, Next[MAX], mark[MAX], p[MAX];

void init(){
    int j = 0;
    len = strlen(s+1);
    for(int i = 2; i <= len; i++){
        while(j && s[j+1] != s[i]){
            j = Next[j];
        }
        if(s[j+1] == s[i]) j++;
        Next[i] = j;
    }
    for(int i = len; i; i = Next[i]){
        mark[i] = 1;
    }
}

int main()
{
    cin >> n >> m;
    scanf("%s", s+1);
    init();
    for(int i = 1; i <= m; i++){
        scanf("%d", &p[i]);
    }
    if(!m){
        cout << qpow(26, n) << endl;
        return 0;
    }
    for(int i = 1; i <= m; i++){
        if(p[i]+len-1 > n){
            puts("0");
            return 0;
        }
        if(i > 1 && p[i-1]+len > p[i]){
            int x = p[i-1]+len-p[i];
            if(!mark[x]){
                puts("0");
                return 0;
            }
        }
    }
    int cnt = p[1]-1;
    for(int i = 1; i < m; i++){
        if(p[i]+len < p[i+1]){
            cnt += p[i+1]-p[i]-len;
        }
    }
    cnt += n-p[m]-len+1;
    cout << qpow(26, cnt) << endl;
    
    return 0;
}
```

### 字符串哈希

```cpp
#include <bits/stdc++.h>
#define ll long long
#define P 1000000007
#define MAX 1000005
using namespace std;

ll qpow(ll a, ll n){
    ll res = 1;
    while(n){
        if(n&1) res = res*a % P;
        a = a*a%P;
        n >>= 1;
    }
    return res;
}

const ll b1 = 99979, b2 = 100007;
const ll p = 1e9+7, q = 1e9+9;
ll p1[MAX], sum1[MAX], p2[MAX], sum2[MAX];
char s[MAX];
int n, m, len, a[MAX];

void init(){
    len = strlen(s+1);
    p1[0] = 1;
    for(int i = 1; i <= len; i++){
    	p1[i] = p1[i-1]*b1%p;
    }
    p2[0] = 1;
    for(int i = 1; i <= len; i++){
    	p2[i] = p2[i-1]*b2%q;
    }
    sum1[0] = 0;
    for(int i = 1; i <= len; i++){
        sum1[i] = (sum1[i-1]*b1%p+s[i]-'a')%p;
    }
    sum2[0] = 0;
    for(int i = 1; i <= len; i++){
        sum2[i] = (sum2[i-1]*b2%q+s[i]-'a')%q;
    }
}

int main()
{
    cin >> n >> m;
    scanf("%s", s+1);
    init();
    for(int i = 1; i <= m; i++){
        scanf("%d", &a[i]);
    }
    if(!m){
        cout << qpow(26, n) << endl;
        return 0;
    }
    for(int i = 1; i <= m; i++){
        if(a[i]+len-1 > n){
            puts("0");
            return 0;
        }
        if(i > 1 && a[i-1]+len > a[i]){
            int x = a[i-1]+len-a[i];
            if(sum1[x]!=(sum1[len]%p-sum1[len-x]*p1[x]%p+p)%p || sum2[x]!=(sum2[len]-sum2[len-x]*p2[x]%q+q)%q){
                puts("0");
                return 0;
            }
        }
    }
    
    int cnt = a[1]-1;
    for(int i = 1; i < m; i++){
        if(a[i]+len < a[i+1]){
            cnt += a[i+1]-a[i]-len;
        }
    }
    cnt += n-a[m]-len+1;
    cout << qpow(26, cnt) << endl;
    
    return 0;
}
```



---

## 作者：Endt (赞：1)

# Tavas and Malekas-题解
先判断是否和法，合法答案则为 $26^x$，$x$ 为剩余可填的位置数。

可以使用 $Z$ 函数来判断是否合法，具体做法见代码。

[$Z$ 函数板子](https://www.luogu.com.cn/problem/P5410)
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,p=1000000007;
char b[1000555];
int lenb,z[1000555];//Z函数
bool a[1000555];//记录是否有以当前位置开头的字符串

void funz(){//Z函数
	int maxi=0;
	for(int i=2;i<=lenb;++i){
		if(maxi+z[maxi]>i)z[i]=min(z[maxi]+maxi-i,z[i-maxi+1]);
		while(b[z[i]+1]==b[z[i]+i]&&z[i]+i<=lenb)++z[i];
		if(i+z[i]>maxi+z[maxi])maxi=i;
	}
	z[1]=lenb;
}

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",b+1);
	lenb=strlen(b+1);
	funz();
	long long x,y;//x为上一个字符串剩余长度
	while(m--){
		scanf("%d",&x);
		a[x]=true;
	}
	x=y=0;
	for(int i=1;i<=n;++i){
		if(x){
			if(a[i]){
				if(z[lenb-x+1]>=x)x=lenb;
				else{
					printf("0");
					return 0;
				}
			}
		}else{
			if(a[i]){
				x=lenb;
			}else{
				++y;
			}
		}
		if(x)--x;
	}
	x=1;
	while(y--){//慢速幂
		x=(x*26)%p;
	}
	printf("%lld",x);
	return 0;
}
```

---

## 作者：CaiXY06 (赞：1)

我们要计算的就是除去模式串所占的位置数，显然答案为 $26^{n}$，$n$ 为位置数。

在计算模式串的贡献时，我们会遇到一个问题，就是如果两个模式串有重叠，我们就得减去重叠部分贡献，以免计算两次。同时，我们还需要判断一波这尾端和头端的两端串是否相同，这显然就是一个字符串匹配的问题。

所以我们考虑一波 **Hash**，判断字符串是否相等，问题就迎刃而解了。

当然 **Hash** 是可以被卡的，比如作者就因自然溢出被卡挂在最后一个点![/dk](https://cdn.luogu.com.cn/upload/pic/62228.png)，所以大家也需要选择合适的模数，甚至双哈希三哈希避免被卡。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int res=1,n,m,T;
char s[1000010];
unsigned long long H[1000010],fac[1000010],base=23333;
inline bool check(int p){
	return (H[m]-H[m-p]*fac[p]%mod+mod)%mod!=H[p]; //判断俩截字符串是否相同
}
signed main(){
	scanf("%lld%lld%s",&n,&T,s+1);
	m=strlen(s+1);
	fac[0]=1;
	for(int i=1;i<=m;i++){//计算Hash值
		fac[i]=fac[i-1]*base%mod;
		H[i]=(H[i-1]*base%mod+s[i]-'a'+1)%mod; 
	}
	for(int i=1,x,p=-1;i<=T;i++){
		scanf("%d",&x);
		if(x-p>=m||p==-1)n-=m;
		else if(check(m-(x-p)))return puts("0"),0;
		else n-=x-p;//减去贡献
		p=x;//记录上个位置
	}
	while(n--)res=res*26%mod;//懒得写快速幂
	printf("%lld",res);
	return 0;
} 
```


---

## 作者：ran_qwq (赞：0)

前置知识：[KMP](https://oi-wiki.org/string/kmp/)。

如果有解，设没被 $m$ 个模式串覆盖的位置有 $x$ 个，答案为 $26^x$。

本题的难点就在于怎么判无解。

最朴素的做法是把每个模式串都粘到文本串上，判断是否有矛盾的位置。但这是 $O(pm)$ 的，无法通过。

先把模式串的所有 border 求出来，那么如果两个模式串有交，就必须满足相交的部分是一个 border，对模式串两两判断是 $O(m^2)$ 的。

不难观察发现这等价于相邻两个模式串满足条件，感性证明就是若 $a=b,b=c$ 则 $a=c$。只用对相邻两个模式串判断即可。时间复杂度 $O(n)$。

```cpp
int n,m,k,as=1,ne[N],a[N],b[N],c[N]; string s;
void QwQ() {
	n=rd(),k=rd(),cin>>s,m=s.size(),s=" "+s;
	for(int i=1;i<=k;i++) a[i]=rd();
	for(int i=2,j=0;i<=m;i++) {
		for(;j&&s[i]!=s[j+1];j=ne[j]);
		if(s[i]==s[j+1]) j++; ne[i]=j;
	}
	for(int i=m;i;i=ne[i]) b[i]=1;
	for(int i=1;i<k;i++) if(a[i+1]-a[i]<m&&!b[m-a[i+1]+a[i]]) return wr(0,"\n");
	for(int i=1;i<=k;i++) c[a[i]]=m;
	for(int i=1;i<=n;i++) {
		cmax(c[i],c[i-1]-1);
		if(!c[i]) cmul(as,26);
	}
	wr(as,"\n");
}
```

---

## 作者：I_will_AKIOI (赞：0)

我们先把这 $m$ 个字符串放进去，相邻的字符串会出现两种情况，要么相交，要么不相交。不相交的情况比较简单，没有被占用的格子可以随便填字母，记没有被占用的格子的长度为 $n$，根据乘法原理，答案会被乘上 $26^n$。

相交的情况，如果两个字符串相交的部分不相等，那么无解。设相交的长度为 $n$，那么需要满足前一个字符串后面的 $n$ 的字符和后一个字符串前 $n$ 个字符相等，否则无解。这不就是 border 吗？我们先用 KMP 预处理出文本串的所有 border，然后相交的部分是不是文本串的 border。

注意第一个字符串前和最后一个字符串后会空一些格子，这些格子也可以随便填字母。还要特判 $m=0$ 的情况。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
#define N 1000005
using namespace std;
int n,m,k,now,ans=1;
int a[N],nxt[N],vis[N];
string s;
int Pow(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>k>>s;
	m=s.size();
	for(int i=1;i<=k;i++) cin>>a[i];
	for(int i=1,j=0;i<m;i++)
	{
		while(j>0&&s[i]!=s[j]) j=nxt[j-1];
		if(s[i]==s[j]) j++;
		nxt[i]=j;
	}
	now=nxt[m-1];
	do
	{
		vis[now]=1;
		now=nxt[now-1];
	}
	while(now);//处理border，vis[i]表示i是否是s的border
	for(int i=1;i<k;i++)
	{
		if(a[i]+m<=a[i+1]) ans=ans*Pow(26,a[i+1]-a[i]-m)%mod;//不相交
		else if(vis[m-a[i+1]+a[i]]==0)//相交且不是border
		{
			cout<<0;
			return 0;
		}
	}
	if(k!=0)
	{
		if(a[1]!=1) ans=ans*Pow(26,a[1]-1)%mod;
		if(a[k]+m-1<=n)//特判开头和结尾
		{
			ans=ans*Pow(26,n+1-a[k]-m)%mod;
			cout<<ans;
		}
		else cout<<0;
	}
	else cout<<Pow(26,n);
	return 0;
}
```

---

## 作者：Engulf (赞：0)

记模式串长 $s$。

若模式串在 $x$ 和 $y$ 处出现且 $x$ 和 $y$ 之间没有模式串出现，分两种情况讨论：

1. 若 $x + s - 1 < y$，两处无交点，合法。
2. 否则存在交点，如果此时交的那两部分不相等的话，就不存在这样的文本串了，答案就是 $0$。

判断字符串相等，字符串哈希即可。

若合法，简单统计一下有多少个位置是没有字符限制的，记其为 $c$，答案即为 $26^n$。

**注意，本题卡自然溢出哈希。**

实现很简洁。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e6 + 5;
const int mod1 = 1e9 + 7, mod2 = 998244353;
const int base1 = 1097, base2 = 9901;

int n, m;

int len;

char str[N];

int hs1[N], hs2[N];

int pw1[N], pw2[N];

inline int geths(int l, int r, int *hs, int *pw, int mod) {return (hs[r] - 1ll * hs[l - 1] * pw[r - l + 1] % mod + mod) % mod;}

inline bool equ(int l1, int r1, int l2, int r2) {return geths(l1, r1, hs1, pw1, mod1) == geths(l2, r2, hs1, pw1, mod1) && geths(l1, r1, hs2, pw2, mod2) == geths(l2, r2, hs2, pw2, mod2);}

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod1;
        a = 1ll * a * a % mod1;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> str + 1, len = strlen(str + 1);
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i <= len; i++) pw1[i] = 1ll * pw1[i - 1] * base1 % mod1;
    for (int i = 1; i <= len; i++) pw2[i] = 1ll * pw2[i - 1] * base2 % mod2;
    for (int i = 1; i <= len; i++) hs1[i] = (1ll * hs1[i - 1] * base1 % mod1 + str[i]) % mod1;
    for (int i = 1; i <= len; i++) hs2[i] = (1ll * hs2[i - 1] * base2 % mod2 + str[i]) % mod2;
    bool valid = true;
    int fil = 0;
    for (int i = 1, last = 0; i <= m; i++) {
        int x;
        cin >> x;
        if (i == 1) fil += len;
        else {
            if (last + len - 1 >= x && !equ(x - last + 1, len, 1, last + len - x)) {
                valid = false;
                break;
            }
            fil += len - max(0, last + len - x);
        }
        last = x;
    }
    if (!valid) cout << 0 << "\n";
    else cout << qpow(26, n - fil) << "\n";
    return 0;
}
```

---

## 作者：fjy666 (赞：0)

前置知识：exKMP。  
本题为一道很好的 $z$ 函数练习题。  
发现题目的本质在于 match 一个模式串的前缀和后缀，看看能不能匹配。  
此时可以想到普通的 KMP，在 $\mathcal{O}(n)$ 的时间内求出 border。  
但是这样是不行的，考虑反例 `abababab`，border 为 $6$，但是长为 $3$ 的前后缀不能匹配。  
所以考虑 exkmp，求出 $z$ 函数后用于前后缀匹配。  
这样就做完了，时间复杂度 $\mathcal{O}(n)$。  
```cpp
#include <bits/stdc++.h>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int in(void) { int x; scanf("%d",&x); return x; }
ll inl(void) { ll x; scanf("%lld",&x); return x; }
using namespace std;
const int kN = 1000005,P = 1000000007;
char s[kN]; int border[kN];
//void prefix_function(char *s,int n) {
//	border[1] = 0;
//	_rep(i,2,n) {
//		int j = border[i - 1];
//		while(j && s[j + 1] != s[i]) j = border[j];
//		if(s[j + 1] == s[i]) ++j;
//		border[i] = j;
//	}
//} 
int z[kN];
void Z_function(char *s,int n) {
	z[1] = n;
	for(int i = 2,l = 0,r = 0; i <= n;++i) {
		if(i <= r) z[i] = min(z[i - l + 1],r - i + 1);
		while(i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) ++z[i];
		if(i + z[i] - 1 > r) l = i,r = i + z[i] - 1;  
	}
}
int match[kN];
int main() {
	int n = in(),m = in();
	scanf("%s",s + 1);
	int k = strlen(s + 1); 
	Z_function(s,k);
	_rep(i,1,m) match[i] = in();
	sort(match + 1,match + 1 + m);
	if(match[m] + k - 1 > n) {
		puts("0");
		return 0;
	}
//	printf("%d\n",border[k]);
	int cnt = m ? k : 0;
	_rep(i,2,m) {
		if(match[i - 1] + k - 1 >= match[i]) {
			int duplicated = match[i - 1] + k - match[i];
			if(z[k - duplicated + 1] < duplicated) {
				puts("0");
				return 0;
			} 
			cnt += k - duplicated;
		}
		else cnt += k;
	}
	ll ans = 1;
	_rep(i,1,n - cnt) ans = (ans * 26) % P;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：kouylan (赞：0)

我们先分两种情况考虑。

1. 前后两个子串没有重合

![](https://cdn.luogu.com.cn/upload/image_hosting/ego8nt94.png)

此时，答案就是中间段随便填字母。设子串长为 $len$，上一个子串的右端点为 $r$，中间段可任意填的长度为 $a_i-r-1$。

2. 前后两个子串有重合

![](https://cdn.luogu.com.cn/upload/image_hosting/v5q5smbv.png)

可知当且仅当中间重合部分对应的串相等时，才合法，否则无解。

观察图形可以发现，重合的部分就是原串的前缀和后缀。所以我们自然的想到了 Z 函数，判断 LCP 是否到串的末尾即可。

最后，答案就是每个可以任意填的位置做 $26$ 字母的乘法原理。

下面是 AC 代码。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int M = 1e9+7ll;

int n,m,len,a[1000005],z[1000005],ans;
char str[1000005];

void getz(int n,char *str)
{
	z[1] = n;
	int l=0,r=0;
	for(int i=2;i<=n;i++)
	{
		if(i>r)
		{
			while(i+z[i]<=n && str[i+z[i]]==str[1+z[i]])
				z[i]++;
			l = i, r = i+z[i]-1;
		}
		else if(z[i-l+1]<r-i+1)
			z[i] = z[i-l+1];
		else
		{
			z[i] = r-i;
			while(i+z[i]<=n && str[i+z[i]]==str[1+z[i]])
				z[i]++;
			l = i, r = i+z[i]-1;
		}
	}
}

int ksm(int x,int w)
{
	int s=1;
	while(w)
	{
		if(w&1)
			s = s*x%M;
		x = x*x%M;
		w >>= 1;
	}
	return s;
}

signed main()
{
	scanf("%lld%lld%s",&n,&m,str+1);
	len = strlen(str+1);
	for(int i=1;i<=m;scanf("%lld",a+i),i++);
	getz(len,str);
	int r=0;
	for(int i=1;i<=m;i++)
	{
		if(r<a[i])
		{
			ans += a[i]-r-1;
			r = a[i]+len-1;
			continue;
		}
		int p=a[i]-a[i-1]+1;
		if(z[p]>=len-p+1)
			r = a[i]+len-1;
		else
			return puts("0"), 0;
	}
	ans += n-r;
	cout<<ksm(26,ans)<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：Acc_Robin (赞：0)

# CF535D Tavas and Malekas 题解

> 不要看它1900就以为这是一道水题

[题目链接](http://codeforces.com/problemset/problem/535/D)

## 题意

　　给定文本串的长度$n$和一个模式串$S$， 并且已知模式串在文本串中某些出现位置（不一定仅在这些位置出现）， 求可能的文本串的数量。

## 思路

　　看似数数题，但事实上只需要考虑有哪些位置是“自由”（即可以是`a`到`z`中任意一个字母）的，记为$cnt$，那么答案就是$26^{cnt}$.本题的难点在于判无解的情况，即相邻两个模式串可能会冲突.

## 解决方案

　　这题用KMP做更合适，但为了练习Z函数，故此处使用Z函数.（事实上，KMP和Z函数没有什么区别）.

　　我们预处理出模式串的Z函数.

　　记相邻的两个模式串为$a,b$，不妨设$a$在$b$的前面.

　　很显然，相邻两个模式串会冲突当且仅当下面两个条件同时满足

　　1.这两个模式串有交集

　　2.交集部分不是$a$的后缀或不是$b$的前缀.

　　那么由Z函数的定义可知，上面两个条件形式化的表达就是

$$
a_i-a_{i-1}<len ~ \land  z[a_i-a_{i-1}]<len-(a_i-a_{i-1})
$$

　　其中$a_i$表示第$i$个模式串首位出现的位置，$len$表示模式串的长度.

　　只需要逐一比较即可.

## 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
namespace Acc{
	const int N = 1e6+10;
	const int mod = 1e9+7;
	char s[N];
	int n,m,a[N],z[N],i,l,r,len,ans,sum[N];
	int qpow(int a,int b){
		int res=1;
		for(;b;a=1ll*a*a%mod,b>>=1)if(b&1)res=1ll*res*a%mod;
		return res;
	}
	void work(){
		for(scanf("%d%d%s",&n,&m,s),i=1;i<=m;i++)scanf("%d",&a[i]);
		for(len=strlen(s),i=1,l=0,r=0;i<len;i++){
			if(i<=r&&z[i-l]<r-i+1) z[i]=z[i-l];
			else for(z[i]=max(0,r-i+1);i+z[i]<n&&s[z[i]]==s[i+z[i]];)z[i]++;
			if(i+z[i]-1>r) l=i,r=i+z[i]-1;
		}
		for(sort(a+1,a+m+1),i=2;i<=m;i++)if(a[i]-a[i-1]<len&&z[a[i]-a[i-1]]<len-a[i]+a[i-1])return (void)(printf("0"));
		for(i=1;i<=m;i++)sum[a[i]]++,sum[a[i]+len]--;
		for(int i=1;sum[i]+=sum[i-1],i<=n;i++)if(!sum[i])ans++;
		printf("%d",qpow(26,ans));
	}
}
int main(){
	return Acc::work(),0;
}		
```

---

## 作者：ycyaw (赞：0)

[传送门](https://www.luogu.org/problemnew/show/CF535D)

发现楼上$($或许会变楼下？$)$ $paulzrm$ 的题解是错的，$hack$数据给在其题解的讨论区。也不知道$cf$什么时候数据这么水了？

给出正解：

首先很容易发现答案就是$26$的“空位个数”次方。空位的个数很显然能够通过~~极其方便的~~差分处理出来，我们要处理的仅仅只有判断是否无解。

分两种情况：

第一种，两个串不相交，显然什么关系都没有。

第二种，两个串相交，我们要判断相交部分是不是相同。发现相交的是第一个字符串的后缀，和第二个字符串的前缀，判断这两段是否相同，那么最容易想到的就是$Hash$了。$Hash$在$cf$上极其危险，有人会对着你卡。所以尽量写个双$Hash$即可。

观察到要判断前缀和后缀的关系，那么显然$KMP$也是可以的。$KMP$的$next$数组就是判断以每一位结尾的字符串前缀和后缀有多少位相等的。那么我们就可以用$KMP$算出，哪些长度的重叠部分是满足条件的。举个栗子，串$abababab$，$next[8]=6$，那么重叠部分长度为$6$就是符合条件的，然后再算$next[6]=4$，$next[4]=2$ $\cdots$，所以重叠部分长度为$4,2$都是符合条件的。

代码：
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
#define mo 1000000007
using namespace std;
int n,m,p[1000005],len,a[1000005],sum[1000005],vis[1000005];
char s[1000005];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+(ch^48);ch=getchar();}
    return ret*ff;
}
inline ll ksm(ll x,ll y){
    ll res=1;
    while(y){
        if(y&1) res=res*x%mo;
        y>>=1;
        x=x*x%mo;
    }
    return res;
}
signed main(){
    n=read(),m=read();
    scanf("%s",s+1);
    len=strlen(s+1);
    int j=0;
    p[1]=0;
    for(int i=2;i<=len;i++){//kmp
        while(j>0&&s[i]!=s[j+1]) j=p[j];
        if(s[i]==s[j+1]) j++;
        p[i]=j;
    }
    for(int i=len;i;i=p[i]) vis[i]=1;//哪些长度的重叠符合条件
    for(int i=1;i<=m;i++) a[i]=read(),sum[a[i]]++,sum[a[i]+len]--;
    for(int i=2;i<=m;i++){
        if(a[i]-a[i-1]<len){
            if(!vis[a[i-1]+len-a[i]]){//a[i-1]+len-a[i]即重叠长度，很容易手玩得出
                printf("0");
                return 0;
            }
        }
    }
    int cnt=0,s=0;
    for(int i=1;i<=n;i++){
        s+=sum[i];
        if(s==0) cnt++;
    }
    printf("%lld",ksm(26,cnt));
    return 0;
}
```


---

## 作者：米奇 (赞：0)

## 算法：hash

## 题解：
这题数据有点毒瘤，需要特判m=0的情况。否则就wa第55个点

我们发现如果是满足条件的，那么答案就是$26^{(\text{空白位置个数})}$

然后难点就在于判断是否满足条件。

我用的是hash，直接比较相邻的两个串的重叠部分是否相同。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int base=20040409;
const int N=1e6+5;
int n,m,len,p[N],h[N],l[N],r[N];
char s[N];
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}*/
#define gc getchar
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
int kuai(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b%2==1)res=res*a%mod;
		a=a*a%mod;
		b=b/2;
	}
	return res;
}
int find(int l,int r)
{
	return (h[r]-h[l-1]*p[r-l+1]%mod+mod)%mod;
}
bool pd(int x,int y)
{
	if(r[x]<l[y])return true;
	int xu=r[x]-l[y]+1;
	if(find(len-xu+1,len)==find(1,xu))return true;
	return false;
}
signed main()
{
	n=read();m=read();
	if(!m){cout<<kuai(26,n);return 0;}
	scanf("%s",s+1);
	len=strlen(s+1);
	p[0]=1;
	for(int i=1;i<=len;i++)p[i]=p[i-1]*base%mod;
	for(int i=1;i<=len;i++)h[i]=(h[i-1]*base+s[i])%mod;
	for(int i=1;i<=m;i++)l[i]=read();
	sort(l+1,l+m+1);
	for(int i=1;i<=m;i++)r[i]=l[i]+len-1;
	for(int i=2;i<=m;i++)
		if(!pd(i-1,i)){puts("0");return 0;}
	int ans=l[1]-1;
	int R=r[1];
	for(int i=2;i<=m;i++)
	{
		if(l[i]>R)ans+=l[i]-R-1;
		R=max(R,r[i]);
	}
	ans+=n-R;
	cout<<kuai(26,ans);
	return 0;
}
```

---

## 作者：世末OIer (赞：0)

听说正解是哈希?本蒟蒻不管那么多了。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
string s;
int a[1000005];
int tj[10000005];
const int md=1000000007;
inline ll qp(ll a,ll b){                                   //快速幂(算出是26的多少次方)
	if(a==0) return 1;
	if(a==1) return b;
	ll t=qp(a/2,b);
	t*=t,t%=md;
	if(a&1){t*=b;t%=md;}
	return t;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>s;
	int i,j;
	for(i=0;i<m;++i) cin>>a[i],++tj[a[i]],--tj[a[i]+s.size()];
	for(i=1;i<n;++i){                      //由于是按照从小到大给的，所以就不用排序了
		if(a[i]-a[i-1]<s.size()){
			if(s[0]!=s[a[i]-a[i-1]]){      //一个位置两种字母?不可能
				cout<<0<<endl;
				return 0;
			}
		}
	}
	int sum=0,gs=0;
	for(i=1;i<=n;++i){                     //统计0的个数
		sum+=tj[i];
		if(!sum) ++gs;
	}
	cout<<qp(gs,26)<<endl;
	return 0;
}
```

---

