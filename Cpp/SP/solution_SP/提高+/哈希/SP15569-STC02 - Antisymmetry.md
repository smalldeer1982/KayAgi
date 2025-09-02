# STC02 - Antisymmetry

## 题目描述

对于一个 01 字符串，如果将这个字符串 0 和 1 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串。比如 00001111 和 010101 就是反对称的，而 1001 就不是。 现在给出一个长度为 n 的 01 字符串，求它有多少个子串是反对称的，注意这里相同的子串出现在不同的位置会被重复计算。

# 题解

## 作者：Poncirus (赞：10)

看完题过后，第一反应是字符串哈希。

我们先把这个计数问题转换为判定问题：若已知字符串 $S$，如何判断其是否反对称？

令 $S'$ 表示 $S$ “按位取反” 后再翻转整个串得到的结果，那么明显，当 $S$ 的哈希值与 $S'$ 的哈希值相等时，$S$ 反对称（原文定义）。

这个过程是 $\mathcal O(1)$ 的。那么我们可以枚举每个串 $(i,j)$，逐个判断，可以 $\mathcal O(n^2)$ 的时间复杂度内完成。

时间主要浪费在了枚举 $(i,j)$ 上。注意到关键词 “对称”，也就是说一个反对称的字符串应该类似于轴对称，将一个反对称串的开头字符和末尾字符同时去掉，该串依然满足反对称。

我们发现，既然长字符串反对称，短字符串也一定反对称，那么这个过程就是具有单调性的，可以考虑二分。

我们枚举每一个“对称轴” $i$，二分 $i$ 两边的字符数量 $l$，$\mathcal O(1)$ 判断 $(i-l,i+l)$ 是否反对称。总时间复杂度 $\mathcal O(\log n)$。

```cpp
#include<cstdio>
#include<cstring>
#define int unsigned long long
namespace XSC062{
	const int maxn=1e6+5;
	const int mod=1504831;  // 114514th prime number
	char s[maxn];
	int n,l,r,mid,res,ans;
    int h[2][maxn],p[maxn];
	inline void init(){
		p[0]=1;
		for(int i=1;i<=n;++i){
			h[0][i]=h[0][i-1]*mod+s[i];
			p[i]=p[i-1]*mod;
		}
		for(int i=n;i;--i)
			h[1][i]=h[1][i+1]*mod+(s[i]=='1'?'0':'1');
		return;
	}
    inline int min(int x,int y){ return x<y?x:y; }
	inline int get0(int l,int r){
		return h[0][r]-h[0][l-1]*p[r-l+1];
	}
	inline int get1(int l,int r){
		return h[1][l]-h[1][r+1]*p[r-l+1];
	}
    inline bool check(int l,int r){
        return get0(l-r+1,l)==get1(l+1,l+r);
    }
	signed main(){
		scanf("%llu%s",&n,s+1); init();
        for(int i=1;i<=n;++i){
            l=1; r=min(i,n-i); res=0;
            while(l<=r){
                mid=l+r>>1;
                if(check(i,mid))
                    res=mid, l=mid+1;
                else r=mid-1;
            }
            ans+=res;
        }
        printf("%llu",ans);
		return 0;
	}
}
signed main(){ XSC062::main(); return 0; }
```

---

## 作者：袁宇轩 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/SP15569)

居然没有一篇用 $hash$ 的题解，那我就来水一篇。

在此感谢[巨佬](https://www.luogu.com.cn/user/88004)的思路点拨。

$n^2$ 的 $hash$ 应该都会，就不讲了。

但不过 $n^2$ 注定会超时，那么我们考虑优化一下。

首先有一个显然的结论：**反对称字串**的长度一定为偶数，否则中间的数取反后一定不相等，那么**反对称字串的对称轴一定在两个字符中间**。

经过思考，我们会发现一个**单调性**：如果一个字串是**反对称字串**，假设对称轴位于第 $i$ 个字符右边，且半径为 $R$ ，那么一定存在字串 $S_{i-r+1}$~$S_{i+r}$（$r$<$R$）是**反对称字串**。

----
就那样例打比方 : 11001011

$S_4$~$S_7$ 为 0101；将其取反、翻转之后得到 0101；

所以 0101 是反对称字串。

那我们在看 $S_5$~$S_6$ : 10；将其取反、翻转之后得到 10；

所以 10 也是反对称字串

-----
看到这里那大家应该都有点想法了，这不是直接二分+$hash$。

我们可以枚举对称轴，二分求出最大的半径，那么答案就是所有求出的半径之和，时间复杂度 $O(nlogn)$ 。

注： $S_l$~$S_r$ 翻转之后的位置为 $S_{n-r+1}$~$S_{n-l+1}$ 。

$Code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define For(i,j,k) for(int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
inline ll read(){
	ll x=0;char ch=getchar();bool f=0;
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=1;
	for(;isdigit(ch);ch=getchar()) x=x*10+ch-'0';
	return f?-x:x;
}
void write(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);putchar(x%10+'0');
}
void writeln(ll x){write(x);puts("");}
void writep(ll x){write(x);putchar(' ');}

int const N=5e5+3;
int const P=131;
ull power[N],Hash1[N],Hash2[N];
int n;
ll ans;
char s[N];

ull find1(int l,int r){
	return Hash1[r]-Hash1[l-1]*power[r-l+1];
}
ull find2(int l,int r){
	return Hash2[r]-Hash2[l-1]*power[r-l+1];
}
int main(){
	n=read();
	scanf("%s",s+1);
	power[0]=1;
	for (int i=1;i<=n;i++){
		power[i]=power[i-1]*P;
		Hash1[i]=Hash1[i-1]*P+s[i]-'0';//原字符串
		Hash2[i]=Hash2[i-1]*P+((s[n-i+1]-'0')^1);//取反、翻转之后的字符串
	}
	for (int i=1;i<n;i++){//枚举对称轴
		int l=0,r=min(i,n-i);
		while (l<r){//二分求最大半径
			int mid=l+r+1>>1;
			if (find1(i-mid+1,i+mid)==find2(n-i-mid+1,n-i+mid)) l=mid;
			else r=mid-1;
		}
		ans+=l;
	}
	writeln(ans);
	return 0;
}
```


---

## 作者：blackjack (赞：4)

# Analysis

理解题目后很容易发现，所谓反对称串需要满足两个条件:

1.串长度为偶数.

2.假设串为s，串长为len，则s[i]=!s[len-i-1]

然后很容易想到一个暴力的思路：由于长度是偶数，可以枚举 中间空挡，向两边拓展，一个一个依次判断对应位置上的数字是否不同，这是一个十分类似找回文串的操作，很容易发现可以用Manacher算法实现,时间复杂度O(n)，由于我并不会，所以我们可以套用另一个速度较快的检查回文串的方法：枚举中间空位，然后二分答案。注意二分程序的开闭关系。时间复杂度O(nlogn)。 具体看代码。

# Code

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef unsigned int ui;
typedef long long ll;
ll ans=0;
int n,l,r,mid;
const int p=13;
char s[500010];
ui preh[500010],sufh[500010],bin[500010];

void build(){
    bin[0]=1;
    for (int i=1;i<=500000;++i)
        bin[i]=bin[i-1]*p;
    for (int i=1;i<=n;++i)
        preh[i]=preh[i-1]*p+s[i]-'0';
    for (int i=n;i;--i)
        sufh[i]=sufh[i+1]*p-(s[i]-'0')+1;
}

inline bool check(int la,int ra,int lb,int rb){
    if (preh[ra]-preh[la-1]*bin[ra-la+1]==sufh[lb]-sufh[rb+1]*bin[rb-lb+1])
        return true;
    return false;
}

int main(){
    freopen("ant.in","r",stdin);
    freopen("ant.out","w",stdout);
    cin>>n;
    scanf("%s",s+1);
    build();
    for (int i=1;i<n;++i){
        if (s[i]==s[i+1])
            continue;
        l=1;
        if (i<n-i)
            r=i;
        else
            r=n-i;
        while (r>=l){
            mid=(l+r)/2;
            if (check(i-mid+1,i,i+1,i+mid))
                l=mid+1;
            else
                r=mid-1;
        }
        ans+=r;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Shawk (赞：3)

希丰展，看[博客](https://www.cnblogs.com/Z8875/p/13401684.html)
## 题目大意
* 求出反对称子串的数量，常说的回文是说从中间开始，两边的字符都相同，反对称就是不相同

## 解题思路
* 这道题要求反对称子串，自然想到 $O(n)$ 求回文字串的 mancher 算法，因为反对称和回文的定义很相像。
```cpp
void Manacher() {//Manacher板子
	    s[0] = '~';//首位插入特殊字符
	    for (int i = 1; i <= n; ++i)
	        s[i*2-1] = '#', s[i<<1] =a[i];//隔空插入特殊字符，判奇回文串
	    s[n*2+1] = '#';
	    for (int i = 1, c = 0, r = 0; i <= n << 1; ++i) {
	        f[i] = i <= r ? min(f[c*2-i], r - i + 1) : 1;
	        while (s[i-f[i]] == s[i+f[i]]) ++f[i];//f[i]*2-1就是以i为中心最长回文子串的长度
	        if (i + f[i] - 1 > r) r = i + f[i] - 1, c = i;
	    }
}
```
* mancher 算法求的是奇回文串，本题要求的都是偶数长度的反对称子串，我们可以变化一下，从每两个字符的中间位置出发进行更新，这样就不需要插入特殊字符了。
* 接下来说一些代码实现的细节，因为这道题并不是裸的板子，需要一些小小的变形，自己画画图有助于理解。
  * 在初始赋值的时候，到右边界最长的字符数应为 r-i，注意这里的 i 是第 i 个空隙。
  * 扩展的时候，左边界是 i-f[i]，右边界是 i+f[i]+1，这里需要注意的是我这种写法不能通过在字符串首位放入特殊字符来自行判断边界，需要判断一下，还有这里求的就是不相同`!=`的字符，而不是板子里的`==`了。
  * 更新最长右边界的时候，此时的右边界是 i+f[i]。
  * 计算答案的时候，f[i] 存的是向一边扩展的最大长度，f[i]*2 是以第 i 个间隔为中心的最长反对称子串长度，而这个间隔的反对称子串数量其实就是长度的一半，也就是 f[i]。
* 最后提醒一点，n 为 5e5 的01串的字串数量是 1e10 级别的，要开long long。
```cpp
#include <cstdio>
#include <algorithm>
#define int long long//记得开long long!!
using namespace std;
const int N = 5e5 + 5;
int n, f[N], ans;
char a[N];
signed main() {
	    scanf("%lld%s", &n, a + 1);//读入总长及01串
	    for (int i = 1, c = 0, r = 0; i < n; ++i) {
	    //i是第i个间隔，r是最远右边界，c是其中心的位置
	        if (i < r) f[i] = min(f[c*2-i], r - i);
	        //进行初始化，不满足i<r的初始值就是0
	        while (i - f[i] > 0 && i + f[i] + 1 <= n && a[i-f[i]] != a[i+f[i]+1]) f[i]++;//要判边界
	        if (i + f[i] > r) r = i + f[i], c = i;//更新最远右边界及其中心
	        ans += f[i];//统计答案
	    }
	    printf("%lld\n", ans);
	    return 0;
}
```

---

## 作者：royzhu (赞：3)

刚学（~~深度~~）字符串

其实这是一道马拉车题

## 思路：
马拉车是找回文的，而题意是求相反的，只要改判断就可以了

### 介绍变量
![](https://cdn.luogu.com.cn/upload/pic/69494.png)
 
### 在跑的时候只会出现3种情况
![](https://cdn.luogu.com.cn/upload/pic/69495.png)
![](https://cdn.luogu.com.cn/upload/pic/69496.png)
![](https://cdn.luogu.com.cn/upload/pic/69497.png)
#### ac代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define M 500010
int R[M];
char s[M];
long long ans=0;
int main()
{
	int n;scanf("%d %s",&n,s+1);
	int mid=0;
	R[0]=0;
	for(int i=1;i<n;i++)
	{
		if(i<mid+R[mid])R[i]=min(R[(mid<<1)-i],mid+R[mid]-i);
		else R[i]=0;
		int l=i-R[i],r=i+R[i]+1;
		while(l>=1&&r<=n&&s[l]!=s[r])l--,r++;
		l++;r--;
		R[i]=(r-l+1)>>1;
		if(r>mid+R[mid])mid=i;
		ans+=R[i];
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：Withers (赞：2)

### 题目大意

给你一个01字符串，让你求有多少个取反后翻转和原串相同的字符串


------------

### 思路
看到这道题，显然会想起回文串和用来求回文串的 manacher 算法 ，但是这里要取反，考虑到串长必定为偶数，（否则中间的字符取反之后必然不是他自己），于是可以发现每次匹配的都是一个奇数位和偶数位，把所有的奇数位取反之后匹配即可


------------
### Code

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define Withers using
#define AK namespace
#define IOI std;
#define ACM __gnu_pbds 
Withers AK IOI;
Withers AK ACM;
typedef long long ll;
typedef pair<int,int> pii;
ll n,m,u,v,w,x,y,z,l,r,minn=INT_MAX,maxx=INT_MIN,len,res,pos,id,as,k;
char t[2400010],s[2400010];
ll p[2400010];
#define infll 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define endl '\n'
#define rd read
#define Y cout<<"YES"<<endl
#define N cout<<"NO"<<endl
#define deb(x) cout<<#x<<"="<<x<<" ";
int main()
{
	scanf("%lld",&n);
	scanf("%s",t+1);
	//n=strlen(t+1);
	for(int i=2;i<=n;i+=2) t[i]=(t[i]=='1')?'0':'1';//预处理字符串，更好的用manacher匹配
	s[1]='#',s[0]='~';
	for(int i=1;i<=n;i++)
	{
		s[i*2]=t[i];
		s[i*2+1]='#';
	}
	n=n*2+1;
	ll ans=0,mid=0,r=0;
	for(ll i=1;i<=n;i++)
	{
		if(i<=r) p[i]=min(p[(mid<<1)-i],r-i+1ll);
		 while(s[i-p[i]]==s[i+p[i]]) ++p[i];
		if(p[i]+i>r) r=p[i]+i-1,mid=i;
	}
	//manacher板子
	for(int i=3;i<=n;i+=2) ans+=p[i]/2;//因为如果已一个原串的地方为中点，他自己取反肯定不是自己，不符合题意
	cout<<ans;
}
// POWERED BY WITHERS
// THINK ONCE, CODE TWICE
```


---

## 作者：wyc_qwq (赞：1)

# 题目意思
对于一个 01 字符串，如果将这个字符串 0 和 1 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串。比如 00001111 和 010101 就是反对称的，而 1001 就不是。 现在给出一个长度为 n 的 01 字符串，求它有多少个子串是反对称的，注意这里相同的子串出现在不同的位置会被重复计算。

# 题目做法
看完题过后，第一反应是字符串哈希。
显然，若一个字符串长度为奇数，则不可能合法。因为中间的字符会进行比较，但取反后不会相等。
那么，我们肯定是要处理一个长度为偶数的字符串。
我们把它分成两段。
假设 i 和 i+1 分别为左半边的结尾与右半边的开始，对两边进行比较。
这个过程可以通过枚举长度和哈希解决。
然后就完美的 TLE 了~。
因此我们要进行改进。
我们可以发现，若一个字符串是合法的，那么从中间向两边散开，且不超过两个端点的字符串也是合法的。
因为，若是这个字符串合法，相当于把右半边取反，从中点折叠会与左半边完全重合。
所以，我们就只要枚举中点，二分长度就好了。

# 那废话不多说，上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long p=1e9+7;
string s;
unsigned long long int base[1000005],h1[1000005],h2[1000005],sum=0;
int n;
bool check(int x,int d)
{
	int l=x-d+1,r=x+d;
	if(h1[r]-h1[l-1]*base[r-l+1]==h2[l]-h2[r+1]*base[r-l+1])
	{
		return true;
	}
	return false;
}
int main()
{
	cin>>n;
	cin>>s;	
	s=' '+s;
	for(int i=1;i<=n;i++)
	{
		h1[i]=h1[i-1]*p+(s[i]=='1');
	}
	for(int i=n;i>=1;i--)
	{
		h2[i]=h2[i+1]*p+(s[i]=='0');
	}
	base[0]=1;
	for(int i=1;i<=n;i++)
	{
		base[i]=base[i-1]*p;
	}
	for(int i=1;i<n;i++)
	{
		int l=0,r=min(i,n-i),mid,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(i,mid))
			{
				ans=mid,l=mid+1;
			}
			else
			{
				r=mid-1;
			}
		}
		sum+=ans;
	}
	cout<<sum;
	return 0;
}
```
# 最后，求管理员大大通过！( •̀ ω •́ )y

---

## 作者：Engulf (赞：0)

按照原文定义，若一个串 $s_1s_2s_3\cdots s_k$ 是好的，那么它和 $(s_k\oplus 1)(s_{k-1}\oplus 1)\cdots(s_1\oplus 1)$ 相等，也就是说 $s_i = s_{k - i + 1} \oplus 1$，即 $s_i \oplus s_{k - i + 1} = 1$，这与回文串的定义类似，所以我们直接上 manacher，仅仅在两端拓展时用我们重新定义的方式来判断能否拓展即可。

最后的答案为 $\sum \left\lfloor \dfrac{p_i}{2} \right\rfloor$，$p_i$ 为以 $i$ 为回文中心的最长回文半径，因为每个最长回文串去掉首位相等数量的字母仍是回文串。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 1e6 + 5;

int n;

char str[N];

int p[N];

void build(char *str) {
    static char ch[N];
    cin >> ch + 1;
    int len = 0;
    str[0] = '~';
    str[++len] = '|';
    for (int i = 1; ch[i]; i++) str[++len] = ch[i], str[++len] = '|';
}

bool equal(char a, char b) {
    if (a == '~') return b == '~';
    if (a == '|') return b == '|';
    if (a == '0') return b == '1';
    return b == '0';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    build(str);
    ll ans = 0;
    for (int i = 1, r = 0, mid = 0; str[i]; i++) {
        if (i <= r) p[i] = min(p[2 * mid - i], r - i + 1);
        while (equal(str[i - p[i]], str[i + p[i]])) p[i]++;
        if (i + p[i] - 1 > r) r = i + p[i] - 1, mid = i;
        ans += p[i] / 2;
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：koobee (赞：0)

先预处理。

预处理两个东西，第一个是原字符串的哈希值，第二个是原字符串的反对称串的哈希值。

然后二分答案。（答案一定是偶数哦）

检验函数：对于区间 $(l,r)$ 而言，分成两半，设长度为 $2×len$，两半为 $l,l+len-1$ 和 $l+len,r$，他们反对称后对应的子串为 $n-r+1,n-l-len+1$ 和 $n-l-len+2,n-l+1$，判断 $l,l+len-1$ 与 $n-r+1,n-l-len+1$ 的哈希值是否相等以及 $l+len,r$ 与 $n-l-len+2,n-l+1$ 的哈希值是否相等即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
typedef unsigned long long ull;
ull n, l, r, h1[N], p[N], h2[N], ans;
string s, t;
ull Hash(int l, int r, bool f){
	if(!f) return h1[r] - h1[l-1] * p[r-l+1];
	else return h2[r] - h2[l-1] * p[r-l+1];
}
bool check(int l, int r){
	int len = r - l + 1;
	int md = l + len / 2 - 1;
	int fll = n - l + 1, flr = n - md + 1, frl = n - md, frr = n + 1 - r;
	if(Hash(flr, fll, 1)==Hash(md+1, r, 0) && Hash(frr, frl, 1)==Hash(l, md, 0)) return 1;
	return 0;
}
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n>>s;
	t = s;
	for(int i = 0; i < n; i++) t[i] = '0' + '1' - t[i];
	for(int i = 0; i * 2 < n; i++) swap(t[i], t[n-i-1]);
	for(int i = 1; i <= n; i++) h2[i] = h2[i-1] * 3 + t[i-1] - '0' + 1;
	p[0] = 1;
	for(int i = 1; i <= n; i++) h1[i] = h1[i-1] * 3 + s[i-1] - '0' + 1, p[i] = p[i-1] * 3;
	for(int i = 1; i < n; i++){
		if(s[i-1] == s[i]) continue;
		int l = 1, r = min(i, int(n-i));
		while(l < r){
			int mid = (l + r + 1) / 2;
			if(check(i-mid+1, i+mid)) l = mid;
			else r = mid - 1;
		}
		ans += l;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：zhzkiller (赞：0)

## 题目描述
这道题要求我们对一个 `01` 串进行处理，找出取反并倒写后仍与原来相同的子串个数。

## 解题思路
首先考虑暴力做法。用 $O(n^2)$ 的时间找到子串端点，并用 $O(n)$ 的时间判断子串是否取反倒序相等。总体时间复杂度 $O(n^3)$。

那么我们怎么优化呢？我们对字符串判等有一个相当优秀的算法——字符串哈希。我们只需要分别对原串进行正向哈希和对反串进行反向哈希就能在 $O(1)$ 的时间内判断子串是否相等。总体时间复杂度 $O(n^2)$。

然而要通过本题，这个时间复杂度我们还是不能接受。仔细思考本题，发现我们不需要一一枚举子串，因为符合答案的子串长度一定为偶数。我们完全可以直接枚举中间分割线的位置（两个数之间的位置），向两边进行拓展。同时这个操作具有单调性——哈希值相等的子串可能拓展，而哈希值不相等的子串一定不能拓展。于是我们可以二分拓展距离，每次查询复杂度为 $O(\log n)$。总体时间复杂度 $O(n \log n)$。

总结：本题需要 **字符串哈希 + 二分答案**。

完结撒花~

献上蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=500010;
const int mod=131;

int n;
long long ans;
char a1[N],a2[N];
unsigned long long f1[N],f2[N],p[N];

long long erfen(int l,int r,int now)
{
	int L=l,R=r;
	while(L<R)
	{
		int mid=(L+R+1)>>1;
		int L1=now-mid+1,R1=now+mid;
		if(L1>=1&&R1<=n&&f1[R1]-f1[L1-1]*p[R1-L1+1]==f2[L1]-f2[R1+1]*p[R1-L1+1]) L=mid;
		else R=mid-1;
	}
	return L;
}

int main()
{
	scanf("%d",&n);p[0]=1;
	for(int i=1;i<=n;i++)
	{
		cin>>a1[i];
		a2[i]=(a1[i]=='1'?'0':'1');
	}
	for(int i=1;i<=n;i++)
	{
		p[i]=p[i-1]*mod;
		f1[i]=f1[i-1]*mod+(a1[i]-'0');
	}
	for(int i=n;i;i--) f2[i]=f2[i+1]*mod+(a2[i]-'0');
	
	for(int i=1;i<=n;i++) ans+=erfen(0,i,i);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Harry_Hedwig (赞：0)

建议先阅读[P3498的题解](https://www.luogu.com.cn/blog/465692/solution-p3498)。
# 0x00 思路
先看题。
>对于一个 $01$ 字符串，如果将**这个字符串 $0$ 和 $1$ 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串**。比如 $00001111$ 和 $010101$ 就是反对称的，而 $1001$ 就不是。 现在给出一个长度为 $n$ 的 $01$ 字符串，求它有**多少个子串**是反对称的，注意这里**相同**的子串出现在**不同**的位置**会被重复计算**。

emmm……这题……和 [P3498 [POI2010]KOR-Beads](https://www.luogu.com.cn/problem/P3498) 有什么本质上的区别吗？都是运用字符哈希将一个序列正着存一遍再反着存一遍，只不过这道题需要取反而已，然后枚举所有子串即可。

# 0x01 优化
QAQ
![](https://cdn.luogu.com.cn/upload/image_hosting/2qwkr5ua.png)

接着你会发现它 TLE 了。

那么就说明如果我们使用完全暴力的方法是不可行的。这个时候我们就需要一点点的数学分析。

首先，我们发现一个 $01$ 串如果是回文的，那么它的左右两边各减去 $i$ 个字母（$0\le i \le \left \lfloor  \dfrac{len}{2} \right \rfloor$）也都是回文的。那么我们就可以找到以某一个位置作为对称轴的最远的一个符合反对称条件的字符串，接着我们就可以找到一此位置作为对称轴的反对称子串的个数。

那么有人可能会想：是否需要分奇偶数的情况？

其实是不用的。

为什么？

因为长度为奇数的字符串肯定不是反对称的。因为取反过后 $0$ 的个数一定和去反前 $0$ 的个数不同，所以不可能重叠。

接着，我们根据上面推论的东西可以发现子串是单调的。所以我们可以使用二分进行优化。那么致辞，这道题也就被我们轻轻松松地 A 了。

# code
**不开 `long long ` 见祖宗！！！**

```cpp
#include<map>
#include<cstdio>
#include<string>
#include<cmath>
#include<cstring>
char space[500005],space2[500005];//原数组，取反后数组
long long ans;
unsigned long long Hash[500005],p[500005],Hash2[500005];//原哈希，，取反后反过来哈希
const int clac=27796511;//乘数
int l,r;
inline void qr(int &ret){int x=0,f=0;char ch;ch=getchar();while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();ret=f?-x:x;return;}
//快读,别翻了

unsigned long long getnum(int l,int r)//原哈希函数
{
	return Hash[r]-Hash[l-1]*p[r-l+1];
}
unsigned long long getnum2(int l,int r)//现函数
{
	return Hash2[l]-Hash2[r+1]*p[r-l+1];
}
int main()
{
	int i,n,q,tot,j;
	p[0]=1;
	for(i=1;i<=500000;i++)
		p[i]=p[i-1]*clac;
	qr(n);
	scanf("%s",space);//当做字符串处理
	for(i=1;i<=n;i++)
	{
		Hash[i]=Hash[i-1]*clac+space[i-1];
		space2[i-1]=!(space[i-1]-'0')+'0'; 
	}
	for(i=n;i;--i)
		Hash2[i]=Hash2[i+1]*clac+space2[i-1];
	for(i=1;i<n;i++)//对称轴（即中心）在哪
	{
		int l=0,r=std::min(i,n-i);//防止越界
		while(l<r)//二分
		{
			unsigned long long sum=getnum(i-r+1,i+r),sumx=getnum2(i-r+1,i+r);//该子串哈希值
			if(l+1==r)
			{
				if(sum==sumx)
					l=r;
				break;
			}
			int mid=(l+r)/2;
			sum=getnum(i-mid+1,i+mid),sumx=getnum2(i-mid+1,i+mid);
			if(sum==sumx)
				l=mid;
			else
				r=mid-1;
		}
		ans+=l;//子串个数
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：零殇 (赞：0)

#### 题意
有一个 $ n $ 个字符的 ` 01 ` 串。对于一个 ` 01 ` 串，若它全部取反并反转后等于原串，则合法。求这个字符串有多少个子串合法。

#### 思路
显然，若一个字符串长度为奇数，则不可能合法。因为中间的字符会进行比较，但取反后不会相等。

那么，我们肯定是要处理一个长度为偶数的字符串。

我们把它分成两段。

假设 $ i $ 和 $ i+1 $ 分别为左半边的结尾与右半边的开始，对两边进行比较。

这个过程可以通过枚举长度和哈希解决。

然后就完美的 TLE 了~。

因此我们要进行改进。

我们可以发现，若一个字符串是合法的，那么从中间向两边散开，且不超过两个端点的字符串也是合法的。

因为，若是这个字符串合法，相当于把右半边取反，从中点折叠会与左半边完全重合。

所以，我们就只要枚举中点，二分长度就好了。

双倍经验 [P3501 [POI2010]ANT-Antisymmetry](https://www.luogu.com.cn/problem/P3501)

上代码：

```
#include<bits/stdc++.h>
const long long base=1e9+7;
using namespace std;
int n;
long long ans;
char s[600000];
unsigned long long sum[600000],hash1[600000],hash2[600000];
unsigned long long check(int l,int r) {
	return hash1[r]-(hash1[l-1]*sum[r-l+1]);
}
unsigned long long check2(int l,int r) {
	return hash2[r]-(hash2[l-1]*sum[r-l+1]);
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    	cin>>s[i];
    sum[0]=1;
    for(int i=1;i<=n;i++) {
    	sum[i]=sum[i-1]*base;
    	hash1[i]=hash1[i-1]*base+(s[i]-'0');
    	hash2[i]=hash2[i-1]*base+((s[n-i+1]-'0')^1);
	}
	for(int i=1;i<n;i++) {
		int l=0,r=min(i,n-i),flag=0;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(check(i-mid+1,i+mid)==check2(n-i-mid+1,n-i+mid)) {
				flag=mid;
				l=mid+1; 
			}
			else
				r=mid-1;
		}
		ans+=(long long)flag;
	}
	printf("%lld",ans);
	return 0;
}
```

完结撒花~

---

## 作者：KEBrantily (赞：0)

好久没写题解了……

------------
## Description

对于一个 $0/1$ 串，如果取反后再将整个串反过来和原串一样，就称作「反对称」字符串

给出一个长度为 $n$ 的 $0/1$ 串，求它有多少个反对称子串

------------
## Solution

哈希题

不难想到，预先处理出正向原串哈希值与反向取反串的哈希值

常规做法，暴力枚举区间判定，哈希值相等则加一

但是数据范围 $1\le n\le 500\ 000$ 显然会超时

于是考虑二分

二分枚举每个区间的对称轴，每次对答案的贡献就是其半径

------------
## Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define maxn 1000100
#define LL long long
#define uLL unsigned long long

using namespace std;

int n;
LL ans;
char s[maxn];
uLL b=1e9+7,Get[maxn],val[maxn],V[maxn];

inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
	return s*w;
}

inline int gethash2(int l,int r){return V[l]-V[r+1]*Get[r-l+1];}
inline int gethash1(int l,int r){return val[r]-val[l-1]*Get[r-l+1];}
inline bool check(int l,int r) {return gethash1(l,r)==gethash2(l,r);}

inline int erfen(int i){
	int l=0,r=min(i,n-i),Ans=0;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(i-mid+1,i+mid)){l=mid+1;Ans=mid;} 
		else r=mid-1;
	}
	return Ans;
}

int main(){
	n=read();scanf("%s",s+1);
	int len=strlen(s+1);Get[0]=1;
	for(register int i=1;i<=n;i++){
		val[i]=val[i-1]*b+(uLL)s[i];	
		Get[i]=Get[i-1]*b;
	}
	for(register int i=n;i>=1;i--){
	    if(s[i]=='1') V[i]=V[i+1]*b+(uLL)'0';
		else V[i]=V[i+1]*b+(uLL)'1';
	}
//	for(register int i=1;i<n;i++) 
//	    for(register int j=i+1;j<=n;j++)
//	    		if(gethash1(i,j)==gethash2(i,j)) ans++;
    for(register int i=1;i<=n;i++) ans+=erfen(i);
	printf("%lld",ans);
	return 0;
}
```

------------


---

