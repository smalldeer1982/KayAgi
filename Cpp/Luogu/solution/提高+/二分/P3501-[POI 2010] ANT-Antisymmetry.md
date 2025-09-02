# [POI 2010] ANT-Antisymmetry

## 题目描述

**译自 POI 2010 Stage 2. Day 0「[Antisymmetry](https://szkopul.edu.pl/problemset/problem/EDxOyJiFZWb_PYVaYhhnhU0-/site/?key=statement)」**

对于一个 $0/1$ 字符串，如果将这个字符串 $0$ 和 $1$ 取反后，再将整个串反过来和原串一样，就称作「反对称」字符串。比如 $00001111$ 和 $010101$ 就是反对称的，而 $1001$ 就不是。  
现在给出一个长度为 $n$ 的 $0/1$ 字符串，求它有多少个子串是反对称的，注意这里相同的子串出现在不同的位置会被重复计算。

## 说明/提示

样例的 $7$ 个反对称子串分别是：$01$（出现两次），$10$（出现两次），$0101$，$1100$ 和 $001011$。

对于 $100\%$ 的数据， $1\le n\le 500\ 000$ 。

翻译来自于 [LibreOJ](https://loj.ac/p/2452)。

## 样例 #1

### 输入

```
8
11001011```

### 输出

```
7```

# 题解

## 作者：文文殿下 (赞：38)

 题意描述

　　　　一句话描述：对于一个0/1序列，求出其中异或意义下回文的子串数量。

题解

　　我们可以看出，这个其实是一个对于异或意义下的回文子串数量的统计，什么是异或意义下呢？平常，我们对回文的定义是，对于任意$i$,$S[i]=S[n-i+1]$，而我们把相等改为异或操作，那么，当且仅当$1$与$0$相匹配时，返回值为$1$ 也就是 “真”。

　　那么，我们可以尝试使用[Manache算法](https://www.cnblogs.com/Syameimaru/p/9310883.html)来解决。当然，编程时，我们并不必真的去把0/1序列转换为数字序列，进行异或操作，这样会给自己增加一波常数（迷），我们构造一个to数组，$to[x]$数组的定义为 对于字符$x$ 我们允许匹配的对应字符，显然，$to['0']='1'$,$to['1']='0'$，特别的$ to['\#']='\#' $  $to['\$']='\$' $。（此处'#'与'$'是Manache算法的分隔字符与防止溢出字符，可以自定义）。

　　对于Manache算法有任何不了解的地方，可以戳[!!!这里!!!](https://www.cnblogs.com/Syameimaru/p/9310883.html)，又看不懂的地方，也可以[联系文文](https://www.cnblogs.com/Syameimaru/p/9310883.html)
  
  
  
  [最后推一波自己博客（逃](https://www.cnblogs.com/Syameimaru/p/9310883.html)

　　对于代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
const int maxn = 1000010;
typedef unsigned long long ull;
char SS1[maxn],S[maxn],to[500];
int n,len[maxn],tot=1;
int main() {
	scanf("%d%s",&n,SS1+1);S[0]='$',S[1]='#';
	for(register int i=1;i<=n;++i) S[++tot]=SS1[i],S[++tot]='#';
	to['1']='0',to['0']='1',to['#']='#',to['$']='$';
	int pos=1,mx=1;ull ans=0;
	for(register int i=1;i<=tot;i+=2) {
		len[i]=(i<mx?std::min(mx-i,len[(pos<<1)-i]):1);
		while(S[i+len[i]]==to[S[i-len[i]]]) len[i]++;
		if(len[i]+i>mx) {
			mx=len[i]+i;pos=i;
		}
		ans+=len[i]>>1;
	}
	printf("%llu\n",ans);
	return 0;
}

```
  
 

---

## 作者：zmzx (赞：21)

此题让求最大的反对称子串，同机房有大佬说要用Manache算法，仔细一想，好像很有道理呀，~~然而，Manache怎么打来着。。。忘记了。。~~

好吧，既然不会Manache，字符串的题，自然想到了哈希，但是单纯的哈希是过不了的，然后想到了**哈希+二分**

通过分析，可以发现，反对称字串一定有偶数个元素（很显然）
我们不妨枚举它的对称轴，然后二分它能向左右延伸的最大长度L，
此长度就是此对称轴对答案的贡献；（可以取[1,L]）；
不会实现的可以参考以下代码：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#define ull unsigned long long
using namespace std;
const int N=5e5+10;
char s[N],t[N];
int n,p=13331;
long long ans;
unsigned long long pp[N],f[N],g[N];
inline void work(int x){
	int l=0,r=min(x,n-x);
	while(l<r){
		int mid=(l+r+1)>>1;
		if((ull)(f[x]-f[x-mid]*pp[mid])==(ull)(g[x+1]-g[x+1+mid]*pp[mid])){
			l=mid;
		}else r=mid-1;
	}
	ans+=l;
}
int main()
{
	scanf("%d",&n);
	scanf("%s",s+1);
	pp[0]=1;
	for(int i=1;i<=n;i++){
		if(s[i]=='1') t[i]='0';
		else t[i]='1';
	}
	for(int i=1;i<=n;i++)pp[i]=pp[i-1]*p;
	for(int i=1;i<=n;i++)f[i]=f[i-1]*p+(s[i]-'0'+12);
	for(int i=n;i>=1;i--)g[i]=g[i+1]*p+(t[i]-'0'+12);

	for(int i=1;i<n;i++){
		if(s[i]==s[i+1])continue;
	     work(i);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：zztqwq (赞：14)

[更好的阅读体验](https://www.cnblogs.com/juruo-zzt/p/13290430.html)

不会 Manacher。。。那就用 hash 水过去吧。

**40分做法**

枚举每个子串，用 hash 逐一判断是否为反对称字符串。

时间复杂度为 $\mathcal O(n^2)$，而此题 $n\le 5\times 10^5$，只能得到 $40$ 分。

**100分做法**

观察到 $n$ 的数据范围，可知此题的复杂度要在 $\mathcal O(n\log n)$ 及以下。于是，不难想到二分。

不难得出，每个反对称字符串的长度一定是偶数，这样我们就可以枚举每个字符串中间的空隙（中轴），然后二分配合 hash 求中轴为 $l$ 的最长反对称字符串长度 $l$，每次 $ans$ 加上 $l/2$  就是最终答案。这是因为，如果一个串 $s$ 为反对称字符串，那么 $s$ 所有以 $l$ 为中轴的子串都是反对称字符串，这样的子串共 $l/2$ 个。可以自己模拟一下试试。实际实现中，二分的是 $l/2$，这样更方便一些。

可以配合图理解一下：

![](https://s1.ax1x.com/2020/07/13/UGsEEn.png)

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N=5e5,base=1e9+7;
char s[N+10];
ull h1[N+10],h2[N+10],p[N+10];
bool t1[N+10],t2[N+10];
int n; 
void init()
{
	p[0]=1ull;
	for(int i=1;i<=n;i++) p[i]=p[i-1]*base;
	for(int i=1;i<=n;i++) h1[i]=h1[i-1]*base+(s[i]=='1');
	for(int i=1;i<=n;i++) h2[i]=h2[i-1]*base+(s[n-i+1]=='0');
}
ull hs(ull *h,int l,int r) {return h[r]-h[l-1]*p[r-l+1];}
bool check(int l,int r) {return hs(h1,l,r)==hs(h2,n-r+1,n-l+1);}
int erfen(int i)
{
	int l=0,r=min(i,n-i),ans=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(i-mid+1,i+mid)) 
		{
			l=mid+1;
			ans=mid;
		} 
		else r=mid-1;
	}
	return ans;
}
int main()
{
	ll ans=0;
	scanf("%d%s",&n,s+1); 
	init();
	for(int i=1;i<n;i++) ans+=erfen(i);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：木木！ (赞：6)

回文子串，考虑使用`Manacher`算法。

可以发现，原题的关键就是要使`'0'`和`'1'`、`'#'`和`'#'`匹配，而其他都不匹配。显然，使用异或操作是可行的，但是这样`'#'`的值就不好定义，因为无论`'#'`定义成什么，`val('#')^val('#')=0`。

像之前那篇题解的dalao一样定义一个`to[]`数组描述匹配关系是一种方法，但是还有一种方法：我们将`'1'`转换成`1`，`'0'`转换成`-1`，`#`定义成`0`，然后匹配关系就是`a==-b`。这样，就可以完美解决问题。

另外，在`Manacher`的时候，可以只考虑偶数位字符，因为奇数个字符组成的子串不可能反对称。

附AC代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

char str[500005];
int si[1000005];
int ri[1000005];

int main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",str);
	
	for(int i=0; i<n; ++i)
	{
		si[i*2+1] = 2*(str[i]-'0')-1;
	}
	n = n*2;
	
	ri[1] = 1;
	int maxi = 1;
	int maxr = 2;
	for(int i=2; i<=n; ++++i)
	{
		ri[i] = min(ri[maxi*2-i],maxr-i)+1;
		while(i>=ri[i] && i+ri[i]<=n && si[i+ri[i]] == -si[i-ri[i]]) //暴力防溢出
		{
			++ri[i];
		}
		--ri[i];
		
		if(i+ri[i]>maxr)
		{
			maxr = i+ri[i];
			maxi = i;
		}
		if(i==maxr)
		{
			++maxr;
		}
	}
	
	long long ans = 0;
	for(int i=1; i<=n; ++i)
	{
		ans += ri[i]/2;
	}
	
	printf("%lld",ans);
}
```

---

## 作者：小菜鸟 (赞：5)

表示不是很喜欢对模板进行改动，因此尽可能想办法让数据适合模板（

首先观察发现反对称子串长度一定是偶数（奇数中间一位没法搞）

由此可以发现，在任意反对称子串中，两个反对称的字符位置不可能同奇同偶

于是我们把所有奇数位上的数异或1，偶数位上的数保持不变，就可以使反对称的字符变成对称的字符

然后直接$manacher$板子就好

算答案的时候注意，只有以填充字符为中心的回文串长度才是偶数

~~我的$manacher$是凭印象瞎yy的，虽然能过但请不要背我的板子~~

代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>

int a[1000005],s[2000005];
long long ans[2000005];

void manacher(int a[],int n)
{
	s[0]=2;
	for(int i=0;i<n;++i)
	{
		s[i*2+1]=a[i];
		s[i*2+2]=3;
	}
	s[2*n]=4;
	int maxr=0,mid;
	for(int i=1;i<n*2;++i)
	{
		if(i>maxr)ans[i]=1;
		else ans[i]=std::min(ans[mid*2-i],maxr-i+1LL);
		while(s[i+ans[i]]==s[i-ans[i]])++ans[i];
		if(i+ans[i]-1>maxr)
		{
			mid=i;
			maxr=mid+ans[i]-1;
		}
	}
}

int main()
{
	int n;
	scanf("%d\n",&n);
	for(int i=0;i<n;++i)
	{
		a[i]=getchar()-48;
	}
	for(int i=1;i<n;i+=2)a[i]^=1;
	manacher(a,n);
	long long res=0;
	for(int i=2;i<n*2;i+=2)res+=ans[i]/2;
	printf("%lld",res);
}
```



---

## 作者：kczno1 (赞：4)

问有多少个子串，将后面一半取反是回文串。

将原串翻转并取反，隔一个特殊字符加在原串后面。

之后枚举回文中心，求最长回文就变成了最长公共前缀。

可以用后缀数组。也可以用二分+hash判断。


---

## 作者：良月澪二 (赞：3)

## 二分哈希

为什么哈希都知道

但是为什么能二分呢

我们知道如果在$i$位置有$i-x$ ~ $i+x$的回文串

那么在$i-x+1$ ~ $i+x-1$也是能构成回文串的

对称串也一样具有单调性

所以对于每个位置二分能延伸的长度

这就是这个位置的贡献

$check$的时候拿出$[l,r]$区间的哈希值判断是否相等就行

当然有一块的哈希值是预处理出的反对称串的哈希值

$strrev$原来并不是标准库函数，这时候只要自己手写~~去网上找~~一个就行了

还是要善用$C++$提供的函数

当然了相比别人的马拉车慢的要死

```cpp
#include <bits/stdc++.h>
#define A 1000010

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ull base = 1000010101;
ull hash1[A], hash2[A], mul[A] = {1};
ll n, ans;
char s[A], rev[A];
bool check(int s1, int s2, int x) {
	ull hs1 = hash1[s1 + x - 1] - hash1[s1 - 1], hs2 = hash2[s2 + x - 1] - hash2[s2 - 1];
	if (s1 > s2) swap(s1, s2), swap(hs1, hs2);
	hs1 *= mul[s2 - s1]; return hs1 == hs2;
}
ll work(int s1, int s2, int l, int r, int maxx = 0) {
	while (l <= r) {
		int m = (l + r) >> 1;
		if (check(s1, s2, m)) maxx = max(maxx, m), l = m + 1;
		else r = m - 1;
	}
	return maxx;
}
char *strrev(char* s) {
	char *h = s, *t = s, ch;
	while (*t++) {}; t--; t--;
	while (h < t) ch = *h, *h++ = *t, *t-- = ch;
	return s;
}

int main(int argc, char const *argv[]) {
	scanf("%d%s", &n, s); strcpy(rev, s); strrev(rev);
	for (int i = 1; i <= n; i++) mul[i] = mul[i - 1] * base;
	for (int i = 1; i <= n; i++) hash1[i] = hash1[i - 1] + s[i - 1] * mul[i];
	for (int i = 1; i <= n; i++) rev[i] = rev[i] == '0' ? '1' : '0';
	for (int i = 1; i <= n; i++) hash2[i] = hash2[i - 1] + rev[i - 1] * mul[i];
	for (int i = 2; i <= n; i++) ans += work(i, n - i + 2, 1, min((int)n - i + 1, i - 1));
	printf("%lld\n", ans);
}
```

---

## 作者：void_zxh (赞：3)

这其实就是一道Manacher的变式题

（额,若有不知道的同学可搜索Manacher算法）

只要将回文串的判断改为一个数为另一个数的反面即可

注意：显然，这个字串只能是偶数。所以不要算长度为奇数的情况

附上代码

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <map>
using namespace std;
#define ll unsigned long long

inline int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
    while(c<='9'&&c>='0'){x=x*10+c-48;c=getchar();}
    return x*f;
}

int n,len;
int p[1010005];
char si[500005];
char a[1010005];
char to[10005]; 
 
void Manacher()
{
    ll ans=0;
    int i;
    int mx,id;
    mx=0;
    for(i=1;i<=len;i+=2)//注意此处要加2，不能计算奇数长度的情况 
    //因为会有这种例子(先忽略#(反正是一样的))
    //0100 1 1101 中间这个1的p[i]=4,当搜到010011 1 01这个1时
    //它所对应的01 0 011101这个0的p[i]=2,但显然上面那个1的p[i]!=2
    //所以此处要加2，不能计算奇数长度的情况 
    {
        if(mx>=i)
            p[i]=min(p[2*id-i],mx-i);
        else
            p[i]=0;
        while(a[i+p[i]+1]==to[a[i-p[i]-1]]) 
            p[i]++;
        if(i+p[i]>mx)
        {
            id=i;
            mx=i+p[i];
        }
    } 
    for(i=1;i<=len;i++)
        if(a[i]=='#'&&p[i]>0)
            ans+=p[i]/2;
    printf("%lld\n",ans);
}

int main()
{
    int i;
    n=read();
    scanf("%s",si+1); 
    a[0]='$'; a[1]='#';
    to['0']='1';
    to['1']='0';
    to['$']='$';
    to['#']='#';
    len=1;
    for(i=1;i<=n;i++) 
    {
        a[++len]=si[i];
        a[++len]='#'; 
    }
    Manacher(); 
    return 0;
}
```

---

## 作者：caidzh (赞：2)

$POI$道道神仙题，一道都不会做

首先看到这个题，第一眼我以为是什么规律题，然后打了个反对称表出来，然后瞎搞后放弃

但有个挺有用的性质：反对称串一定是偶数长度的

这是显然的，因为如果是奇数长度，那么一定不满足处于最中间的那个是一样的

好！但是这与我们下面要讲的解法没有什么关系

接下来我们来考虑如果我们确定了一个中心后，向外扩展出一个最大可能的反对称串，那么这个串中一定含有$\frac{len}{2}$个满足条件的串，其中$len$为串长，这也是显然的，因为要想大的满足条件，则在里面的小串必须满足是反对称的

这是很有用的，因为我们只需要对于所有中心求最大的反对称串长度就行了

怎么求最大的反对称串长度，注意到如果反对称，那么其一定满足位于左边的数与位于右边的数中一个是$0$，另一个是$1$，并且它可以近似看做是回文的

想到了什么？马拉车啊！

所以使用马拉车求出每个最大的反对称串长度，除以$2$加入到答案中就可以了

---

## 作者：小塘空明 (赞：2)

~~做得致郁~~

取反后翻转与原串相等，等价于将串的左半段每位全部异或1后与右半段相等。

所以我们只要将manacher算法中的判断条件修改下就行了。

注意**因为这个串只能是偶数长度，所以不要进行奇数长度的运算（自己可以手推几个样例发现错误）**。~~否则你会像我一样喜得10分。~~

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const ll size=5e5+10;
char s[size*2],a[size],c[size*2];ll n,ans,hw[size*2];
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
inline void change(){
	s[0]=s[1]='#';
	for(ll i=0;i<n;i++){
		s[i*2+2]=a[i];s[i*2+3]='#';
	}
	n=n*2+2;s[n]=0;
}
inline void manacher(){
	ll maxright=0,mid;
	for(ll i=1;i<n;i+=2){
		if(i<maxright) hw[i]=min(hw[(mid<<1)-i],maxright-i);
		else hw[i]=1;
		while(s[i+hw[i]]-'0'+s[i-hw[i]]-'0'==1||(s[i+hw[i]]==s[i-hw[i]]&&s[i+hw[i]]=='#')) hw[i]++;
		if(i+hw[i]>maxright){
			maxright=i+hw[i];mid=i;
		}
	}
}
int main(){
	n=read();
	scanf("%s",a);
	change();manacher();
	for(ll i=1;i<n;i+=2) ans+=(hw[i])/2;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：chihik (赞：1)

看到求回文串就想到 $\text{PAM}$ 。

因为只有 $0,1$ 所以判断条件改成等于。

不过这道题满足题意的串长度一定为偶，所以不能走到 $-1$ 根。

其他的就是板子了。


```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 500000 , MAXK = 2;
int n;
char str[ MAXN + 5 ];
struct Palindrome_Automaton{
	int Size , Last , Root0 , Root1 , Trans[ MAXN + 5 ][ MAXK + 5 ] , Link[ MAXN + 5 ];
	int Len[ MAXN + 5 ] , Cnt[ MAXN + 5 ];

	Palindrome_Automaton( ) {
		Root0 = Size ++ , Root1 = Size ++; Last = Root0;
		Len[ Root0 ] = 0  , Link[ Root0 ] = Root1;
		Len[ Root1 ] = -1 , Link[ Root1 ] = Root1; 
	}
	void Extend( int ch , int dex ) {
		int u = Last;
		for( ; u != 1 && ( str[ dex - Len[ u ] - 1 ] == str[ dex ] || ( dex - Len[ u ] - 1 == -1 ) ) ; u = Link[ u ] );
		if( str[ dex - Len[ u ] - 1 ] == str[ dex ] || ( dex - Len[ u ] - 1 == -1 ) ) { Last = 0; return; }
        if( !Trans[ u ][ ch ] ) {
			int Newnode = ++ Size , v = Link[ u ];
			Len[ Newnode ] = Len[ u ] + 2;
			
			for( ; v != 1 && ( str[ dex - Len[ v ] - 1 ] == str[ dex ] || ( dex - Len[ u ] - 1 == -1 ) ) ; v = Link[ v ] );
            Link[ Newnode ] = str[ dex - Len[ u ] - 1 ] == str[ dex ] ? 0 : Trans[ v ][ ch ];
            Trans[ u ][ ch ] = Newnode;
			Cnt[ Newnode ] = Cnt[ Link[ Newnode ] ] + 1;
		}
		Last = Trans[ u ][ ch ];
	}
	
	long long Build( char *str ) {
		int len = strlen( str );
        long long Ans = 0;
		for( int i = 0 ; i < len ; i ++ ) {
			Extend( str[ i ] - '0' + 1 , i );
			Ans += Cnt[ Last ];
		}	
        return Ans;
	}
}PAM;

int main() {
    scanf("%d",&n);
    scanf("%s", str );
    printf("%lld", PAM.Build( str ) );
    return 0;
}
```


---

## 作者：royzhu (赞：1)

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

