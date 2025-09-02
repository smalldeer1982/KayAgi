# [CEOI 2017] Palindromic Partitions

## 题目描述

给出一个只包含小写字母字符串，要求你将它划分成尽可能多的小块，使得这些小块构成回文串。

例如：对于字符串 ``abcab``，将他分成 ``ab`` ``c`` ``ab`` 或者 ``abcab`` 就是构成回文串的划分方法，``abc`` ``ab`` 则不是。

## 说明/提示

对于 $100\%$ 的数据，有 $1\le T\le 10$。设 $L$ 为单个字符串的长度，则 $1\le L\le 10^6$​​。

## 样例 #1

### 输入

```
4
bonobo
deleted
racecar
racecars```

### 输出

```
3
5
7
1```

# 题解

## 作者：小粉兔 (赞：14)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/10356919.html ](https://www.cnblogs.com/PinkRabbit/p/10356919.html )

菜菜只能靠写简单字符串哈希维持生活。

### 题意简述：

题面讲得很清楚了。

### 题解：

很显然从两边往中间推，能选的就选上这个贪心策略是对的。

如何判断能不能选上，直接字符串哈希吧。

有一个小细节：中间那块要不要选，即ans要不要加1？判一下串长即可。

```cpp
#include <cstdio>
#include <cstring>

typedef unsigned long long UL;
const int B = 79;

int T, N;
char str[1000005];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s", str); N = strlen(str);
		UL s1 = 0, s2 = 0, b = 1;
		int ans = 0;
		for (int i = 0; i < N / 2; ++i) {
			s1 = s1 * B + str[i];
			s2 = s2 + str[N - i - 1] * b;
			b = b * B;
			if (s1 == s2) {
				ans += 2;
				s1 = s2 = 0, b = 1;
			}
		}
		if (N % 2 || s1) ++ans;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：the_same_prayers (赞：10)

看到还没有人写题解我就先来~~水一篇~~

题意有些令人迷惑（为什么叫“这些小块构成回文‘**串**’ ”），我反正看了十分钟，所以重新解释一遍：

**给你一个字符串，让你把它拆成x个小块，并且这些小块构成回文块。回文块：将每个小块看作一个整体（类似于回文串里的字符），以某个块或两个小块之间的间隙为对称轴，则对称轴两边的块应该一一对应且相同。两小块当且仅当两者长度和字符完全一样时相同。**

整体思路：
- 
- ~~开始想过malacher~~后来发现要malacher必须hash，还不好划块。（既然hash了，为什么不暴力匹配一下呢？）

- 先想过枚举两个匹配的字符串的首尾长度，但是，仔细观察会发现 **如果首尾块无法匹配，中间块匹配答案也不会增加**。

- 所以，~~经过蒟蒻浅显的思考后，~~我们应该从首端枚举首端块的结尾位置（或者说枚举长度），与后端同样长度块的hash值做比较；若匹配，ans+=2，首端和后端指针分别后/前移len个长度单位，继续比较。

做法与细节
- 
-  先hash出字符串前缀，用公式

**hash=((hash[r]−hash[l−1]∗p(r−l+1))%MOD+MOD)%MOD**

求子块hash值（后者比对时在线求）。
- 三个指针：首端未匹配的第一个字符（lik1），末端未匹配的第一个字符（lik2），正在搜索的字符（i）。
- 使用快速幂求Pow（p，len），p即用于离散化的小质数。
- 在线求pow很可能因为重复求而超时，所以预处理一下，用一个数组存值
- 若最后lik1>lik2，即所有都匹配，直接输出ans，否则有中间块不匹配，则输出ans+1

代码如下（有些丑陋请见谅qwq）：
```cpp
#pragma GCC optimize(3,"Ofast","inline")//o3臭氧是个好东西
#include<stdio.h>
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
char l[N];
long long ahash[N],r[N],mod=2000000033;
long long mm[N];
int n,m,p=233,ans,lik1,lik2;
long long Pow(int p,int i)
{
	if(i==1)return p;
	if(i==0)return 1;
	long long int m=Pow(p,i/2);
	if(i%2==1)return m%mod*m%mod*p%mod;
	else return m*m%mod;
}
void work()
{
	lik1=1,lik2=m;
	for(int i=1;i<=(m+1)/2&&lik1<lik2;i++)
	{
		int len=i-lik1+1;
		if(l[i-1]==l[lik2-1])
		{
			if(((ahash[i]-ahash[lik1-1]*mm[len])%mod+mod)%mod==((ahash[lik2]-ahash[lik2-len]*mm[len])%mod+mod)%mod)
			ans+=2,lik1+=len,lik2-=len;
			
		}
	}
		if(lik1>lik2)printf("%d\n",ans);
		else printf("%d\n",ans+1);
}
int main()
{
	cin>>n;
	for(int i=0;i<=N/2;i++)mm[i]=Pow(p,i);//预处理Pow，否则重复求而且长度很大易超时
	while(n--)
	{
		memset(ahash,0,sizeof(ahash));ans=0;
		scanf("%s",l);
		m=strlen(l);
		for(int i=1;i<=m;i++)//我的存储方式可能有些不舒服，hash[i]对应的是第i个字符（从1开始）前缀（包括自己）的hash值
		{
			ahash[i]=(ahash[i-1]*p+l[i-1]-'a'+1)%mod;
		}
		work();
	}
}

```
看在蒟蒻写了这么久的份上，给个赞吧~

欢迎大家来踩博客：[qwq](https://www.luogu.com.cn/user/224346)


---

## 作者：cqbzlym (赞：10)

其实题读懂了就很好做了。

因为要使最后分得的串数量最多，所以就要让每一段的长度尽量小。所以，我们的原则是：能分就分。两边同时减去最短的回文前 / 后缀，直到串空为止。

现在我们面临着一个问题：假设某串（称为串 $A$）被我们以 “能选就选” 的方法选中，但有另一串（称为串 $B$）必须与串 $A$ 组合才能组成回文，此时应该怎么办？

但是，稍微思考一下就能发现，对于串 $ABBA$，两边同时减去一个 $A$，$BB$ 依然回文，若以上述情况不存在。

以字符串哈希为工具，可以得出代码：

```cpp
#include<cstdio>
#include<cstring>
#define int unsigned long long
namespace XSC062{
	const int maxn=1e6+5;
	const int mod=1504831;  // 114514th prime number
	char s[maxn];
	int T,l,r,n,cnt;
	int h[maxn],p[maxn];
	inline void init(){
		p[0]=1;
		for(int i=1;i<=n;++i){
			h[i]=h[i-1]*mod+s[i];
			p[i]=p[i-1]*mod;
		}
		return;
	}
	inline int get(int l,int r){
		return h[r]-h[l-1]*p[r-l+1];
	}
	signed main(){
		scanf("%llu",&T);
		while(T--){
			scanf("%s",s+1);
			n=strlen(s+1);
			init(); l=1; r=n; cnt=0;
			for(int i=l;i<=r;++i){
				if(get(l,i)==get(r-(i-l+1)+1,r))
					cnt+=(i==r)?1:2, r-=i-l+1, l=i+1;
			}
			printf("%llu\n",cnt);
		}
		return 0;
	}
}
signed main(){ XSC062::main(); return 0; }
```

---

## 作者：Suki_Megumi (赞：6)

把字符串Hash，取到区间Hash值，然后再从两边往中间贪心，Hash值相等的就是两块可以构成回文串的答案，ans+=2
```cpp
#include <bits/stdc++.h>

typedef unsigned long long ull;
const int maxn = 1e6 + 7;
const int inf = 0x3f3f3f3f;
const int base = 31;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
    return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int T;
char s[maxn];
ull h[maxn], p[maxn];

inline void Hash(const int &len) {
    p[0] = 1, h[1] = 1;
    for(int i = 1; i <= len; ++i) {
        p[i] = p[i - 1] * base;
        h[i] = h[i - 1] * base + s[i];
    }
}

inline ull get_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    T = read();
    while(T--) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        Hash(len);
        int last = 0, ans = 0;
        for(int i = 1; i <= len / 2; ++i) {
            if(get_hash(last + 1, i) == get_hash(len - i + 1, len - last)) {
                last = i;
                ans += 2;
            }
        }
        if(last * 2 < len) ans++;
        print(ans); puts("");
    }
    return 0;
}
```
~~顺便宣传[个人博客](https://lgakki.cn)~~

---

## 作者：Hoks (赞：2)

## 前言
[题目链接](https://www.luogu.com.cn/problem/P4656#submit)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-p4656)内食用也许会更佳吧。

先膜一发楼上兔队的题解，模拟赛的题，感觉挺水的。
## 思路分析
这题要求的是最多的回文块，易得我们把一个大的回文块拆成两个小的回文块能增加个数，所以果断食用哈希。

对于一个字符串顺序哈希一遍，再反向哈希一遍，如果有两个值一样那就是有相同的回文块，直接清空哈希值累加答案，最后特判一下分成奇数块的时候就行了。

P:S:哈希使用自然溢出大法很舒服，而且模数推荐 $1145141$。有时能够创造奇迹。
## 代码
```cpp
#include<bits/stdc++.h>
#define ing long long
using namespace std;
int t,n;
char s[1000010];
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x;
}
signed main()
{
	freopen("palindromic.in","r",stdin);
	freopen("palindromic.out","w",stdout);
	t=read();
	while(t--)
	{
		scanf("%s",s);n=strlen(s);
		unsigned long long hash1=0,hash2=0,op=1;
		int ans=0;
		for(int i=0;i<n/2;i++)
		{
			hash1=hash1*1145141+s[i];
			hash2=hash2+s[n-i-1]*op;
			op=op*1145141;
			if(hash1==hash2) ans+=2,hash1=hash2=0,op=1;
		}
		if(n%2||hash1) ans++;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：VioletIsMyLove (赞：2)

对于这道题，笨蛋的想法就是左边的字符串每次的右边界往右推一个单位，右边的字符串每次左边界往左推一个单位，一但左边从串和右边的串相等时就把长度清 $0$。但每次判断两个串的时效太慢，对于每个串它要出结果时效近似 $L^2$，所以我们想到字符串 $hash$，这样每次判断 $O(1)$ 就没问题，这题就做下来了，但是奇偶要特判一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int TT[2]={1000007,100007};//hash尽量模大的质数，这里开2个也是怕撞车
int t;
int s[2][1000005],S[2][1000005];
char a[1000005];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
	return ret*f;
}
int main(){
	t=read();S[0][0]=S[1][0]=1;
	while(t--){
		scanf("%s",a+1);int lena=strlen(a+1),st=0,len=1,ed=lena/2,ans=1;
		for(int i=1;i<=lena;i++)S[0][i]=S[0][i-1]*TT[0],s[0][i]=s[0][i-1]+a[i]*S[0][i],S[1][i]=S[1][i-1]*TT[1],s[1][i]=s[1][i-1]+a[i]*S[1][i];
		for(int i=1;i<=ed;i++){
			if((s[0][st+len]-s[0][st])*S[0][lena-st-len-st]==s[0][lena-st]-s[0][lena-st-len]&&(s[1][st+len]-s[1][st])*S[1][lena-st-len-st]==s[1][lena-st]-s[1][lena-st-len]){
				if(st+len<ed+lena%2)ans+=2;else ans++;len=0;st=i;
			}
			len++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：一只书虫仔 (赞：1)

#### Description

> 给定一个字符串 $S$，求将其分为 $k$ 个部分 $s_1,s_2,\cdots,s_k$ 使得 $s_i=s_{k-i+1}$，使得 $k$ 最大，输出最大的 $k$。

#### Solution

注意，并不是判断回文哦（第一次以为是判断回文，导致看样例没看懂（）。

首先，先抛出结论，我们的程序可以这么做：程序可以定两个指针，这两个指针是对称的，第一个指针 $i \in [1,mid]$，第二个指针 $j =|S|-i+1$，再定两个左右端点指针 $L,R$，初始 $L=1$，$R=|S|$，然后判断 $S_{[L,i]}$ 是否等于 $S_{[j,R]}$，如果等于了，那么答案就加 $2$，并调整左右界，$L=i+1$，$R=|S|-i$，也就是往里一个，相当于把 $[L,i],[j,R]$ 切掉。

具体 $mid$ 和操作要根据 $|S|$ 的奇偶性进行具体判断，判断等于使用字符串哈希。

为什么可以这么做呢？我们来做一个小证明。

假设有两段 $[1,i]$ 与 $[1,j]$，其中 $i<j$ 都是与相应的区间对称的，那么 $[i+1,j]$ 中肯定也有至少一个子区间与相应的区间对称的。假设 $[1,i]=\texttt{ab}$，$[1,j]=\texttt{abcab}$，那么原字符串就可以表示为 $S=\texttt{abcab}\cdots\texttt{abcab}$，$[i+1,j]$ 中可以分为 2 个子区间，$\texttt c$ 与 $\texttt{ab}$ 可以与相应子区间对称。所以，我们就可以贪心，从左往右能切就切。

还有一些细节可以直接看代码（代码写的很丑）。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const unsigned long long P = 23;
unsigned long long a[1000100];

unsigned long long binpow (unsigned long long b, unsigned long long p) {
	unsigned long long res = 1;
	while (p > 0) {
		if (p & 1)
			res = res * b;
		b = b * b;
		p >>= 1;
	}
	return res;
}

unsigned long long getHash (int l, int r) {
	unsigned long long hash1tol = a[l - 1] * binpow(P, r - l + 1);
	return a[r] - hash1tol;
}

int main () {
	int t;
	scanf("%d", &t);
	while (t--) {
		string s;
		cin >> s;
		int str = s.size();
		s = ' ' + s;
		int cnt = 0;
		for (int i = 1; i <= str; i++)
			a[i] = a[i - 1] * P + s[i];
		if (str % 2 != 0) {
			int L = 1, R = str;
			for (int i = 1; i <= (str + 1) / 2 - 1; i++) {
//				printf("OUT %d %d\n", L, R);
				if (getHash(L, i) == getHash(str - i + 1, R)) {
					cnt += 2;
					L = i + 1;
					R = str - i;
//					printf("IN %d %d\n", L, R); 
				}
			}
			cnt++;
		} else {
			int L = 1, R = str;
			for (int i = 1; i <= str / 2; i++) {
//				printf("OUT %d %d\n", L, R);
				if (getHash(L, i) == getHash(str - i + 1, R)) {
					cnt += 2;
					L = i + 1;
					R = str - i;
//					printf("IN %d %d\n", L, R);
				}
			}
			if (L < R) cnt++;
		}
		printf("%d\n", cnt);
 	}
	return 0;
}
```

---

## 作者：Lappland_Texas (赞：1)

# 题意简述:

大概就是给你一个字符串，然后让你划分成最大块数然后构成回文串（相同的子串可以看成同一个字符）。

下面讲一下思路。

## 1.  $30$ 分思路（初步）

想的是从两头往中间搜，因为如果目前的两头已经不匹配的话显然是无法构成回文串的,匹配用哈希维护就好了。

于是遇到不同的就把搜的长度加一,如果找到相同的就将搜索长度置为 $0$ ，从下位继续枚举。

但是用长度来做是非常不好判断边界,还会写非常多的判断语句,比如偶数和奇数个时的终止循环条件需要分开写，答案统计也需要分别另写，还特别容易出锅（令人不齿）。

~~某蒟蒻在考试的时候就是这么做的，然后只得了 $30$ 分。~~

## 2. 经过加工后的想法

写两个左指针 $l$，$l1$ 和两个右指针 $r$，$r1$ 来枚举，遇到不相等的字符就 ```l++,r--``` 如果正在匹配的字符串哈希值相等，就在向前跳后把左串的左指针 $l1$ 置为当前位置，右串的右指针 $r1$ 置为当前位置（可看作长度归零）。

终止条件即 $l<r$ 。

注意，在跳出循环后需要进行特判最后的一块，如果 $l1$ 不等于  $r1+1$ 说明中间那一坨需要直接分成一块,则```ans++```。


下面是代码

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define N 1000005
#define ll long long
int has[N],cf[N],sah[N];
const int p = 233333;
const int mod = 20041103;

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    cin>>n;
    cf[0]=1;
    for(int i=1;i<=N;i++)cf[i]=(cf[i-1]*p);//预处理p的次方 
    for(int i=1;i<=n;i++)
    {
        string a;
        cin>>a;
        len=a.size();
        int ans=0;
        for(int j=0;j<len;j++)has[j]=(has[j-1]*p+a[j]);//用哈希来匹配字符串 
        int l=0,r=len-1;
        int l1=0,r1=len-1;
        while(l<r)
        {
            if((has[l]-has[l1-1]*cf[l-l1+1])==(has[r1]-has[r-1]*cf[r1-r+1]))
            {
                l++,r--;
                l1=l,r1=r;
                ans+=2;
            }
            else
            {
                l++,r--;
            }
        }
        if(l1!=r1+1)ans++;
        cout<<ans<<endl;
        memset(has,0,sizeof has);       
    }
    return 0;
}
```

不取模也无伤大雅嘛。

---

## 作者：Neil_Qian (赞：0)

# P4656 [CEOI2017] Palindromic Partitions
## 题面描述
[https://www.luogu.com.cn/problem/P4656](https://www.luogu.com.cn/problem/P4656)   
意思是把原字符串划分成尽量多个部分，将每个部分看作一个字母，使得这些部分回文。  
另一种说法：  
将原字符串 $L(n=L.size())$ 划分成 $x[1],x[2],x[3],\dots,x[k]$ ,使得 $x[i]=x[k-i-1],i\in[0,n/2]$ ，最大化这个 $k$ ,并输出 $k$ 。
## 题解
### 哈希
#### 用途
哈希是一种字符串算法，设一个字符串的长度为 $n$ ，则它只需要 $O(n)$ 的时间做预处理，之后就能在 $O(1)$ 的时间内判断两个字串是否相同。
#### 实现
我们可以将整个字符串看成一个 $base$ 进制的数，每一位是该字符的 ASCII ，用数组 $h[i]$ 表示该字符串从 $1\to i$ 的数值。  
然后可以利用前缀和的思想，可以得出如下结论：  
$l\to r$ 的哈希值 = $h[r]-h[l]\times p[r-l+1]$ ， 其中 $p[i]=p^i$ 。  
那么问题来了：应该用多少进制呢？需要高精吗？  
先回答第二个问题。由于高精太复杂，还会提升时间复杂度，因此采用 long long 或 unsigned long long 即可，也不用取模，可以让它自然溢出。至于第一个问题，有人研究过，使用 131 进制最好，因为不容易冲突。当然，其它数也几乎不可能冲突。  
#### 例题
[acwing.com/problem/content/140/](acwing.com/problem/content/140/)
#### 模板代码
```cpp
//代码时间较长，比较拉跨，请见谅
#include<iostream>
#include<cstdio>
#include<string>
#define ll long long
using namespace std;
const ll base=131;
ll h[1000002],p[1000002];
ll n,m;
string temp,x=" ";
ll l1,r1,l2,r2;
ll get(ll l,ll r){//求取哈希值
	return h[r]-h[l-1]*p[r-l+1];
}
int main(){
	p[0]=1;
	cin>>temp;n=temp.size();x+=temp;//加一个空格，好从 1 开始
	for(int i=1;i<=n;i++){
		p[i]=p[i-1]*base;//计算进制，以免超时
		h[i]=h[i-1]*base+x[i];//哈希值的前缀和
	}
	scanf("%lld",&m);
	while(m--){
		scanf("%lld%lld%lld%lld",&l1,&r1,&l2,&r2);
		if(get(l1,r1)==get(l2,r2)){//哈希值相等，字符串相同
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}
	}
	return 0;
}
```
### 哈希的应用
其实本题有一些贪心的思想。  
先想一个问题：想要分成尽量多的部分，每个部分应该怎么样？当然越短越好啊对不对？于是，我们采用两个变量 $s1,s2$ ，分别从两端出发，开始往中间一个字符一个字符地往中间走，每走到一个字符就把字符加到 $s1,s2$ 里，具体操作如下：  
```cpp
s1=s1*base+str[i],s2=s2+str[n-i-1]*b,b*=base;//base代表进制
```
### 注意事项
在任何一道题中，要么用 scanf ，要么用 cin 。  
只要用了 cin ，就必须加上一句话：
```cpp
ios::sync_with_stdio(false),cin.tie(0);
```
因为 cin 是很慢的，加了以后会快一些。
### 代码
只有 15 行，但请仔细看。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int base=131;
string str;ll n,s1,s2,b;int ans;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);int T;cin>>T;
	while(T--){//这里不用哈希模板的方式
		cin>>str,n=str.size();s1=str[0],s2=str[n-1],b=base,ans=0;
		for(int i=0;i<n/2;i++,s1=s1*base+str[i],s2=s2+str[n-i-1]*b,b*=base)//这里使用了哈希的思想，把字符变成数加在了 s1,s2 中
			if(s1==s2)ans+=2,s1=s2=0,b=1;
		printf("%d\n",ans+((s1-str[n/2])/base||n%2));//特判
	}
	return 0;
}
```

---

## 作者：lyxeason (赞：0)

~~这题大概是 CEOI2017 里最水的吧~~

首先题目中说要分成尽可能多的小块，也就是说每一块要尽量短。

所以可以用一种递归的方式求解。设 $f(l,r)$ 为字符串 $a$ 中 $a_l\cdots a_r$ 最多能分成多少小块。那么每次枚举 $i\in[1,r-l+1]$，表示块长。然后判断 $a_l\cdots a_{l+i-1}$ 能否与 $a_{r-i+1}\cdots a_r$ 匹配，如果能且 $[l,l+i-1]$ 与 $[r-i+1,r]$ 没有重合，那么令答案加二，递归到 $f(l+i,r-i)$ 继续求解。否则令答案加一（不能再分就把它算作中间的一段）并返回。但要注意在 $l>r$ 时及时退出。

由于要处理的长度不断递减，所以时间复杂度最多 $O(n)$。

其中的匹配可以用字符串哈希 $O(1)$ 实现。具体见代码。

------------
### 代码
###### 代码里有注释
```cpp


#include <cstdio>
#include <cstring>
#define ull unsigned long long

using namespace std;

const ull P = 131;
int T;
char S[1000009];
int N;
ull s[1000009]; //用 unsigned long long 是因为无符号位整数就相当于对2的64次方求余
ull p[1000009];
int res;

int Get_Str (int l, int r) { //字符串哈希，求S[l]-S[r]的哈希值
    return s[r] - s[l - 1] * p[r - l + 1];
}

void Get_Res (int l, int r) { //即前面的f
    int i;

    if (l > r) return;
    for (i = 1; i <= r - l + 1; i++)
        if (Get_Str(l, l + i - 1) == Get_Str(r - i + 1, r)) break;
    if (l + i - 1 >= r - i + 1) { res++; return; }
    else {
        res += 2;
        Get_Res(l + i, r - i);
    }
}

int main () {
    p[0] = 1;
    for (int i = 1; i <= 1000000; i++) p[i] = p[i - 1] * P;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", S + 1);
        N = strlen(S + 1);
        for (int i = 1; i <= N; i++) s[i] = s[i - 1] * P + S[i] - 'a' + 1;
        res = 0;
        Get_Res(1, N);
        printf("%d\n", res);
    }

    return 0;
}
```

---

## 作者：bwartist (赞：0)

先考虑暴力的思路：分割，判断每两个对应的段是否相等。

判断字符串相等很容易想到哈希。而“分割”这一步骤也可以用哈希来实现，可以转换成求每一段（相当于子串）的哈希值。

>具体来说，若 $l$ 表示子串左端点， $r$ 表示子串右端点，f(l,r)表示子串的哈希值，就有： 
$$f(l,r)=f(1,r)-f(1,l)*p^{r-l+1}$$
>$f(1,l)$ 很好求，在第一遍算整体的字符串哈希值时就可以求出。 $f(1,r)$ 同理。 $p$ 表示计算整体哈希值时每一位字符乘的“进制”。

所以最终的步骤就可以简化成：从左右两端向中间推进，如果左右两边的子串的哈希值相等，就从这里分割一次。
另外，不要忘记可能最后一段不能被分割，答案要加一。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
string a;
int T;
const int Maxx = 1000000;
ll H[Maxx+5], p[Maxx + 5];
ll f (int l, int r) {
	return H[r] - H[l - 1] * p[r - l + 1]; 
}
int main () {
	p[0] = 1;
	for (int i = 1; i <= Maxx; i++)	p[i] = p[i - 1] * 31;
	scanf ("%d\n", &T);
	while (T--) {
		cin>>a;
		ll sum = 0, ans = 0, L = 1, R = a.size(), x = 1, y = a.size();
		for (int i = 0; i < a.size(); i++) {
			sum = sum * 31 + a[i];
			H[i + 1] = sum;
		}
		while (x < y) {
			if (f(L, x) == f(y, R))	ans += 2, L = x + 1, R = y - 1;
			x++, y--;
		}
		if (L <= R)	ans++;
		printf ("%d\n", ans);
	}
	return 0;
}
```



---

## 作者：Unnamed114514 (赞：0)

### 前置知识
[哈希](https://baike.baidu.com/item/Hash/390310?fromtitle=%E5%93%88%E5%B8%8C&fromid=24086145&fr=aladdin)，本人认为它是一个密码加密技术，就是加密一个密码所用的东西。在算法中，我们使用它可以减少空间，虽然有可能引起冲突，所以说我们就可以用一些方法来减少冲突的可能。虽然它的部分问题可以用 KMP 解决，但本题还是推荐使用哈希。
### 算法思路
首先，我们使用单哈希，具体方法只需要用到初始化和查询子串的值，具体方法如下，设常数 $k=37$，那么 $Hash_i\gets Hash_{i-1}+s_i+1$，有没有想到什么？对，前缀和！查询子串的方法可以这样：子串 $[l,r]$ 的值为 $Hash_r-Hash_l \times Hash_{r-l+1}\times k^{r-l+1}$，有了这个方法，我们可以 $O(1)$ 地匹配了。最后贪心的从右侧寻找与左边的相同的数，相同就可以了，不相同就继续查找。
### 复杂度分析
空间复杂度 $O(maxl)$，即 Hash 数组，时间复杂度 $O(n)$，因为每个字母只便利并且删除一次，可以过。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int k=37,maxl=1e6+5;
int t,Hash[maxl],power[maxl];
inline int getans(int l,int r){
 	return Hash[r]-Hash[l-1]*power[r-l+1];
}//查询子串的值
signed main(){
	scanf("%llu",&t);
	power[0]=1;
	for(int i=1;i<=maxl;++i)
		power[i]=power[i-1]*k;//初始化次方表
	for(int i=1;i<=t;++i){
		char s[maxl];
		scanf("%s",s+1);
		int len=strlen(s+1);
		int l=1,r=len,ans=0;
		for(int i=1;i<=len;i++)
			Hash[i]=Hash[i-1]*k+s[i]-+1;//初始化
		while(l<r){
			long long f=-1;
			for(int i=1;i<=len;++i){
				int ll=l+i-1,rr=r-i+1;
				if(ll>rr)
					break;
				if(getans(l,ll)==getans(rr,r)){
					f=i;
					break;
				}
			}
			if(f==-1){
				ans++;
				break;
			}
			ans+=2,l+=f,r-=f;
		}
		if(l==r)
			ans++;
		printf("%llu\n",ans);
	}	
	return 0;
} 
```

---

## 作者：BotYoung (赞：0)

## P4656题解

**前置知识: 字符串哈希（或 KMP）**

首先观察题面，其意思是让我们将一个字符串分割成尽可能多的子串，使得这些字串构成的集合是回文的。所以我们知道，需要使用一个合理的、快速的方法判断字符串中的两个子串是否相等。所以我们需要使用 **KMP** 或 **字符串哈希**。

由于 **KMP** 过于深奥，我这小小的蒟蒻讲不明白，所以给出 **字符串哈希** 的做法。

因为我们要让字串尽可能的多，意思是我们要让每个子串的长度尽可能小，并且题目限制了我们的时间复杂度在 $O(n)$，所以考虑贪心的做法（线性 DP 复杂度过高）。

不妨从字符串的第一个位置开始枚举，如果从第一个没有被判断过的位置，到当前位置的字串（即：$S[last..i]$）与其关于字符串中间位置对称的字符（即：$S[n-i+1..last+1]$）这两个字符串相等，那么我一定要将这两个字符串分割出去，因为这样可以使所选集合中的字符串的长度最短，从而达到字串数量最多的目的。

下面给出代码和详细解释：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P = 13331;
int T, n, ans, last;
char s[1000005];
unsigned long long f[1000005], p[1000005];
void H(){//采用自然溢出法，保存一个字符串及其字串的哈希值
	for (int i = 1; i <= n; i++)
		f[i] = f[i - 1] * P + s[i] - 'a' + 1;
}
bool judge(int l1, int r1, int l2, int r2){
	//根据哈希值判断两个字串是否相等
	//判断方法的正确性证明略 
	return f[r1] - f[l1 - 1] * p[r1 - l1 + 1] == f[r2] - f[l2 - 1] * p[r2 - l2 + 1];
}
int main(){
	scanf("%d", &T);
	p[0] = 1;
	for (int i = 1; i <= 1000000; i++)
		p[i] = p[i - 1] * P;
	//p[i]存储 p^i%(2^64-1) 的值，用于判断字符串是否相等 
	while(T--){
		scanf("\n%s", s + 1);
		n = strlen(s + 1);
		//输入 
		H();//初始化Hash数组（代码中的f数组） 
		ans = 0, last = 1;//last 
		for (int i = 1; i <= n; i++)
			if (judge(last, i, n - i + 1, n - last + 1))
				last = i + 1, ans++;//如果两个字符串已经相等，则一定要选出 
			//原因见上方 
		printf("%d\n", ans); 
		//输出答案 
	}
	return 0;
}
```

---

## 作者：Light_in_Dark (赞：0)

## P4656 [CEOI2017]Palindromic Partitions 题解
> 第一眼看到题目，感觉他应该是个暴力搜索，但看一眼数据范围，顿时傻了 $\texttt{---}$ 他不能暴力！！！于是只能用第二个思路。

> 首先这里有个贪心思想，就是只要我能划分我就必须划！按照这个思路我们就可以清晰的用哈希来解决。

## 代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
int read() { //快读
	int x = 0;
	char ch;
	while((ch = getchar()) < '0' || ch > '9');
	while(ch >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return x;
}
void write(int x) { //快写 
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
const int inf = 1e6, p = 137;
ull Hash[inf + 5], Pow[inf + 5];
int T, ans, n, l, r;
char s[inf + 5];
ull ask(int l, int r) {	return Hash[r] - Hash[l - 1] * Pow[r - l + 1]; } //查询从 l 到 r 的哈希值 
int main() {
	T = read();
	Pow[0] = 1;
	for (int i = 1; i <= inf; ++i) Pow[i] = Pow[i - 1] * p; //预处理出 p 的幂次 
	while (T--) {
		memset(Hash, 0, sizeof(Hash)); //初始化 
		scanf("%s", s + 1);
		n = strlen(s + 1), l = 1, r = n, ans = 0;
		for (int i = 1; i <= n; ++i) Hash[i] = Hash[i - 1] * p + s[i]; //计算 hash 值 
		while (l < r) {
			bool flag = 0;
			for (int i = 1; i <= r - l; ++i) {
				if (ask(l, l + i - 1) == ask(r - i + 1, r)) { //判断是否合法，如果合法，就跳出循环 
					l += i, r -= i, ans += 2, flag = 1;
					break;
				}
			}
			if (!flag) //如果找不到，说明这是一个不能回文的数，就退出循环 
				break;
		}
		ans += l <= r; //判断 l,r 之间有没有一个值，如果有，答案增加 
		write(ans), putchar('\n');
	}
	return 0;
}
```

---

## 作者：cqbzjyh (赞：0)

**思路：**

用两个指针 $L$ 和 $R$ ，分别指向字符串首尾。从两端同时枚举找到相同的字符串，  $s_{1 \sim  L}$ 和 $s_{R \sim n}$, 然后下次再从 $L$ 和 $R$ 出发，继续找到相同的字符串，如果最后找到字符串的长度不足 $n$ 就将答案加 $1$。

例如：$\verb!bonobo!$

先找到 $s_{1\sim2} = s_{5\sim6}$= $\verb!bo!$，已匹配字符串长度 $:4$

然后我们就会发现剩下的字符无法匹配，而且我们发现已匹配字符串长度不足 $n$。所以剩下的 $\verb!no!$ 只能单独为一部分。

故最后答案为 $3$

对于匹配字符串，我们可以用 hash 来维护，两个字符串 hash 值相等，则两个字符串可以匹配。

**code**

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int maxn = 1e6 + 5; 
const int base = 31;
int Hash[maxn], Pow[maxn];
char s[maxn];
int gethash() {
	int len = strlen(s + 1);
	for (int i = 1; i <= len; i++) {
		Hash[i] = Hash[i - 1] * base + s[i];
	}
}
int get(int L, int R) {
	return Hash[R] - Hash[L - 1] * Pow[R - L + 1];
}
int ans;
signed main() {
	Pow[1] = base;
	for (int i = 2; i <= maxn; i++) Pow[i] = Pow[i - 1] * base;
	int t;
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--) {
		cin >> s + 1;
		gethash();
		ans = 0;
		int len = strlen(s + 1), st = 0;
		int LL = 1, L = 1, RR = len, R = len;
		while (L < R) {
			if (get(LL, L) == get(R, RR)) {
				ans += 2;
				st += 2 * (L - LL + 1);
				L++;
				R--;
				LL = L;
				RR = R;
			} else {
				L++;
				R--;
			}
		}
		if (st < len) ans++;
		cout << ans << endl;
	}
	return 0;
}
```

宣传博客:https://www.cnblogs.com/cqbzjyh/p/15560890.html

---

## 作者：Liynw (赞：0)

贪心 + Hash

因为要划分为尽量多的部分，所以我们从两边开始找，设两个指针分别指着从左往右数和从右往左数第 $i$ 个字符。只要找到两个字符串一样，就把它们分离出来。

两个字符串是否一样可以通过 Hash 判断，但是有个问题：我们是从两边往中间枚举的，右边那个字符串是倒着枚举的，怎么判断呢？

这个很简单，我们只需要判断一下当前右边遍历到的字符是字符串的第几个，假设它是第 $k$ 个，那么就加上它乘以 $base^k$ 即可。

最后有个细节：如果字符串的长度是奇数，或者还剩下一些字符，那么需要把这些字符作为一个区间，答案要加一。

```cpp
#include <cstdio>
#include <cstring>
#define ull unsigned long long

const int maxn = (int) 1e6 + 5, p = 97, base = 10;

int T, n;
char s[maxn];

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		ull hash1 = 0ull, hash2 = 0ull, pow = 1;
		int ans = 0;
		for(int i = 1; i <= n / 2; i++) {
			hash1 = hash1 * p + s[i];
			hash2 = hash2 + s[n - i + 1] * pow;
			pow *= p;
			if(hash1 == hash2) {
				ans += 2;
				hash1 = hash2 = 0ull;
				pow = 1;
			}
		}
		if((n & 1) || hash1)
			++ans;
		printf("%d\n", ans);
	}
	return 0;
} 
```

---

## 作者：CaoXian (赞：0)

## P4656 题解

首先，这道题有一个很明显的贪心策略，就是能划分出来一个前缀和后缀相同的字串时，那么就一定要划分出来，因为是求的最多的小块。

暴力思路很明显，直接用 `STL` 的 `string` 从两边开始暴力判断。

在这个过程中， `string` 的比较时间非常大，为了节约时间，我们可以将 `string` 改为哈希，这样可以大大减少时间。

最后，在中间的最后一块需要判断一下，即防止多算或少算。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
//快读快输略
typedef unsigned long long ull;
const ull mul = 1e9 + 7;
ull t, m, len, a, b, ans;
char s[1000005];
int main() {
	scanf("%llu\n", &t);
	while(t--) {
		a = b = ans = 0, m = 1;
		fgets(s + 1, 1000002, stdin);
		len = strlen(s + 1) - 1;
		fu(i, 1, (len + 1) / 2) {
			a = a * mul + s[i], b = s[len - i + 1] * m + b, m *= mul;//Hash
			if(a == b) ans += (i == (len + 1) / 2 && len & 1 ? 1 : 2)/*特判*/, a = b = 0, m = 1;
		}
		if(a != b) ++ans;//防止少算
		write(ans, '\n');
	}
	return 0;
}
```


---

