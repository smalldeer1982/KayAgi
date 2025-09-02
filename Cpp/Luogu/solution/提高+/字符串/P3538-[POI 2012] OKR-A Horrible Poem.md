# [POI 2012] OKR-A Horrible Poem

## 题目描述

Bytie boy has to learn a fragment of a certain poem by heart.  The poem, following the best lines of modern art, is a long string    consisting of lowercase English alphabet letters only.  Obviously, it sounds horrible, but that is the least of Bytie's worries.

First and foremost, he completely forgot which fragment is he supposed to learn.  And they all look quite difficult to memorize...

There is hope, however: some parts of the poem exhibit certain regularity.  In particular, every now and then a fragment, say ![](http://main.edu.pl/images/OI19/okr-en-tex.1.png),    is but a multiple repetition of another fragment, say ![](http://main.edu.pl/images/OI19/okr-en-tex.2.png) (in other words, ![](http://main.edu.pl/images/OI19/okr-en-tex.3.png), i.e., ![](http://main.edu.pl/images/OI19/okr-en-tex.4.png), where ![](http://main.edu.pl/images/OI19/okr-en-tex.5.png) is    an integer).  In such case we say that ![](http://main.edu.pl/images/OI19/okr-en-tex.6.png) is a full period of ![](http://main.edu.pl/images/OI19/okr-en-tex.7.png) (in particular, every string is its own full period).

If a given fragment has a short full period, Bytie's task will be easy.  The question remains... which fragment was that?

Make a gift for Bytie - write a program that will read the whole poem as well as a list of fragments that Bytie suspects might be the    one he is supposed to memorize, and for each of them determines its shortest full period.

## 样例 #1

### 输入

```
8
aaabcabc
3
1 3
3 8
4 8```

### 输出

```
1
3
5```

# 题解

## 作者：RenaMoe (赞：55)

# 题解 P3538 【[POI2012]OKR-A Horrible Poem】

[题面](https://www.luogu.org/problem/P3538)

判断字符串循环节最方便的是$hash$

不会的请[出门左转P3370](https://www.luogu.org/problem/P3370)

我们先把字符串$hash$一遍

![](https://cdn.luogu.com.cn/upload/image_hosting/olzrdhcj.png)

如图，如果设循环节长度为$3$时，$s1$和$s2$的$hash$值是相等的

所以只需要找最小的$len$使得$hash(l+len,r)=hash(l,r-len)$

----

另外，**循环节的长度的循环次数都一定是总长的约数**

我的做法是把**总长除掉循环次数**

先把$len$分解质因数

（线性筛质数，并记录下每个数的最小质因子加速分解，~~这已经是常规操作了~~）

因为最小循环节的倍数也是循环节

所以从$len$开始试除每个质因子并判断（你可以理解为$len$的因子分为循环节的因子和循环次数的因子，要把循环次数的因子除掉）

具体的看代码吧。。。

----

### 代码

```cpp
#include <cstdio>
#include <cctype>
#include <vector>

using namespace std;

template<typename T> inline void read(T &x) {
	x = 0; T k = 1; char in = getchar();
	while (!isdigit(in)) { if (in == '-') k = -1; in = getchar(); }
	while (isdigit(in)) x = x * 10 + in - '0', in = getchar();
	x *= k;
}

typedef long long ll;

const ll MOD = 1e9 + 7;
const int N = 5e5 + 5;

int n, m;
ll g[N], hash[N], pow[N];// g记录最小质因子，pow存进制的整数次幂
char s[N];
bool vis[N];
vector<ll> pri;

// 线性筛
inline void euler() {
	for (ll i = 2; i <= n; ++i) {
		if (!vis[i])
			pri.push_back(i), g[i] = i;
		for (int j = 0; j < pri.size() && pri[j] * i <= n; ++j) {
			vis[pri[j]*i] = true, g[pri[j]*i] = pri[j];
			if (i % pri[j] == 0)
				break;
		}
	}
}

// 提取hash值
inline ll calc(int l, int r) {
	return ((hash[r] - hash[l-1] * pow[r-l+1]) % MOD + MOD) % MOD;
}

int main() {
	read(n);
	euler();
	scanf("%s", s+1);
    // hash
	for (int i = 1; i <= n; ++i)
		hash[i] = (hash[i-1] * 29 + s[i] - 'a' + 1) % MOD;
	
    // 预处理整数次幂
	pow[0] = 1;
	for (int i = 1; i <= n; ++i)
		pow[i] = (pow[i-1] * 29) % MOD;

	read(m);
	while (m--) {
		int l, r, len, ans;
		read(l), read(r), ans = len = r - l + 1;
        // 一点点常数优化
		if (calc(l+1, r) == calc(l, r-1)) {
			puts("1");
			continue;
		}
        // 重点
		while (len > 1) {
			if (calc(l+ans/g[len], r) == calc(l, r-ans/g[len]))// 判断
				ans /= g[len];// 除掉循环次数的因子
			len /= g[len];//分解
		}
		printf("%d\n", ans);
	}
    return 0;
}
```



---

## 作者：忆殇 (赞：34)

题目要求给出一个字符串和q次询问，并求出每次询问的区间内的最短循环节长度

首先有几个性质

    1、循环节一定是长度的约数
    2、如果n是一个循环节，那么k*n也必定是一个循环节（关键所在）
    3、n是[l,r]这一段的循环节  的充要条件是  [l,r-n]和[l+n,r]相同（利用这个性质我们在判断是否为循环节是可以做到O(1)）  
    所以我们可以在求出这个区间的长度之后，判断它的每个约数是否是循环节（应用性质3），并且因为性质1，它的约数是循环节，原串一定也是。

所以只要不断除以质因数（相当于从大到小枚举约数），缩小L的长度，最后就是最小的长度。

而一个重要的点在于，用上面方法来枚举约数是为了避免tle

在求它的质因数的时候，可以通过线性筛的过程求得，将时间法度由根号n 降为logn。

注意这里枚举到全长。

    void pri()
    {
        for(int i = 2;i<= maxn;i++)
        {
            if(used[i] == 0)
            {
                sushu[++k] = i;
                nxt[i] = i;//质数就返回自己（方便多次乘方的查找）。
            }
            for(int j = 1;j <= k && (long long)i*sushu[j]<= maxn;j++)
            {
                used[i*sushu[j]] = 1;
                nxt[i*sushu[j]] = sushu[j];（代表这个数是由这个质数将其表示为非质数，同时也是其质因数）。
                if(i%sushu[j] == 0)
                {
                    break;
                }
            }
        }
    }
这样通过nxt数组不断回跳，就可以找出所有质因数（多次乘方的也可以）

判定循环节的时候可以使用hash。

代码附上

    #include<cstdio>
    #include<cmath>
    #include<algorithm>
    #include<cstring>
    #define seed 13131
    #define maxn 500005
    using namespace std;
    typedef unsigned long long ull;
    char s[500005];
    ull s1[500005];
    ull ss[500005];
    int sushu[500005];
    int used[500005];
    int nxt[500005];
    int k;
    int ys[500005];
    void pri()
    {
        for(int i = 2;i<= maxn;i++)
        {
            if(used[i] == 0)
            {
                sushu[++k] = i;
                nxt[i] = i;
            }
            for(int j = 1;j <= k && (long long)i*sushu[j]<= maxn;j++)
            {
                used[i*sushu[j]] = 1;
                nxt[i*sushu[j]] = sushu[j];
                if(i%sushu[j] == 0)
                {
                    break;
                }
            }
        }
    }
    int check(int l1,int r1,int l2,int r2)
    {
        if(s1[r1]-ss[r1-l1+1]*s1[l1-1] == s1[r2]-ss[r2-l2+1]*s1[l2-1])
        {
            return 1;
        }
        return 0;
    }
    int main()
    {
        int n;
        scanf("%d", &n);
        scanf("%s",s+1);
        int q;
        scanf("%d", &q);
        for(int i = 1;i <= n;i++)
        {
            s1[i] = s1[i-1]*seed+s[i]-'a'+1;
        }
        ss[0] = 1;
        for(int i = 1;i <= n;i++)
        {
            ss[i] = ss[i-1]*seed; 
        }
        pri();
        for(int i = 1;i <= q;i++)
        {
            int l,r;
            scanf("%d%d", &l, &r);
            int len = r-l+1;
            int tt = 0;
            while(len != 1)
            {
                ys[++tt] = nxt[len];
                len = len/nxt[len];
            }
            len = r-l+1;
            for(int j = 1;j <= tt;j++)
            {
                int t = len/ys[j];
                if(check(l,r-t,l+t,r) == 1)
                {
                    len = t;
                }
            }
            printf("%d\n",len);
        }
        return 0;
    }

---

## 作者：BeyondStars (赞：16)

其实解决这道题的工具是哈希，但是精髓是线性筛素数。没错，这道题带有浓郁的数学味道。首先我们要明白一下几个东西(题解里告诉我的)
>1.如果$s$是$[l,r]$的循环节，那么$len_{[l,r]}$一定是$s$长度的倍数
2.如果$s$是$[l,r]$的循环节，那么[l,r-s]=[l+s,r]，正确性其实可以自己想一想，不难。
3.如果要使s的长度最小，我们可以枚举$len_{[l,r]}$的因数，从小到大枚举。
4.如果$s$是一个循环节，那么$ks k\in Z^*$也是一个循环节(前提是长度要小于区间长度)

那么怎么获得$len_{[l,r]}$的因数呢？这是一个问题，能想到这里，这道题就可以A了。首先，我们可以直接枚举，但是这样的复杂度是$O(\sqrt{n})$的，介于这道题死不要脸卡常(必须写快读，否则卡不过)，所以$O(\sqrt(n)$的复杂度过不了。那么我们看看算数基本定理，发现我们可以通过把长度拆分成若干质因数，然后通过不同质因数的组合，得到大小不同的质因数。
那么第一步，就是写出一个线筛：
```cpp
void prime(){
    for(int i = 2;i<=MAXN;i++){
        if(!not_prime[i]){
            prime_table[++prime_cnt] = i;
            min_prime_factor[i] = i;
        }
        for(int j = 1;j<=prime_cnt&&i*prime_table[j]<=MAXN;j++){
            not_prime[i*prime_table[j]] = true;
            min_prime_factor[i*prime_table[j]] = prime_table[j];
            if(!(i%prime_table[j]))break;
        }
    }
}
```
这里面我们用min_prime_factor[i]来表示i的最小质因数是多少，然后通过i/min_prime_factor[i]就可以表示另一个因数(可能是个合数)，然后又对另一个因数拆分，就可以得到i从大到小的不同因数啦(代码里面有说吗后面的一个储存i的质因数的数组factor为什么是递增的(不一定严格递增，但是不影响))。
接下来就是第二步啦！
第二步也很简单，就是判断$len_{[i,j]}$的每一个因数的长度是否可以构成一个循环节，如果可以，就把它分解了看看它的因数是不是可以，因为如果k是一个循环节，那么2k,3k也一定可以构成循环节。
一下就是我写的烂的不得了的代码咯，略略略！
```cpp

#include <cstring>
#include <cstdio>
using namespace std;
const int MAXN = 500010;
char str[MAXN];
int n;
unsigned long long Hash[MAXN];
const int base = 13131;
unsigned long long poww[MAXN];
int mod = 1e9+7;
int prime_table[MAXN];
bool not_prime[MAXN];
int min_prime_factor[MAXN];//min_prime_factor[i]表示i的最小质因子是多少
int factor[MAXN];
int factor_cnt;
int prime_cnt;
int read(){
    int x = 0,f = 1;
    static char c;
    c = getchar();
    while(c<'0'||c>'9'){ if(c=='-')f = -1;c= getchar();}
    while(c>='0'&&c<='9')x = x*10+c-'0',c = getchar();
    return x*f;
}
void prime(){
    for(int i = 2;i<=MAXN;i++){
        if(!not_prime[i]){
            prime_table[++prime_cnt] = i;
            min_prime_factor[i] = i;
        }
        for(int j = 1;j<=prime_cnt&&i*prime_table[j]<=MAXN;j++){
            not_prime[i*prime_table[j]] = true;
            min_prime_factor[i*prime_table[j]] = prime_table[j];
            if(!(i%prime_table[j]))break;
        }
    }
}
void calPow(){
    poww[0] = 1;
    for(int i = 1;i<=n;i++){
        poww[i] = poww[i-1]*base;
    }
}
void cal_hash(){
    for(int i = 1;i<=n;i++){
        Hash[i] = Hash[i-1]*base+str[i]-'a'+1;
    }
}
unsigned long long getHash(int l,int r){//返回以s开始，包括s的，长度为n的区间的哈希
    return Hash[r]-Hash[l-1]*poww[r-l+1];
}
bool judge(int l,int r,int len){
    return getHash(l,r-len)==getHash(l+len,r);
}
int main() {
    n = read();
    scanf("%s",str+1);
    prime();
    calPow();
    cal_hash();
    int q;
    q = read();
    int l,r;
    while(q--){
        l = read();
        r = read();
        int len = r-l+1;
        if(judge(l,r,1)){
            printf("%d\n",1);
        }else{
            factor_cnt = 0;
            while(len!=1){
                factor[++factor_cnt] = min_prime_factor[len];
                len = len / min_prime_factor[len];//可以保证factor里面因数是递减的，原因应该可以想明白
                //因为min_prime_factor[i]储存的是i的最小质因数，不断这样计算下去，facotr里面的数会越来越小。
            }
            len = r-l+1;
            for(int i = 1;i<=factor_cnt;i++){
                if(judge(l,r,len/factor[i])){
                    len /= factor[i];
                }
            }
            printf("%d\n",len);
        }
    }
    return 0;
}
```
给大家安利一波我的博客嘛。[蒟蒻的博客](http://denghaoyu.leanote.com/)欢迎各位dalao来~~调教~~指教
总结一下，这道题的关键就是想到如何分解l，不愧是紫题，思维难度还是比较大的！

---

## 作者：Leap_Frog (赞：14)

### P3538 [POI2012]OKR-A Horrible Poem 解题报告

这题还是挺有意思的。  

字符串Hash板子题。  

学到了三个小 tips：  

1. 判断一个字符串是否存在长度为 $len$ 的循环节不需要暴力枚举，复杂度为 $O(\frac{n}{len})$，可以直接判断 $[l,r-len]$ 是否等于 $[l+len,r]$ 复杂度 $O(1)$。
2. 如果一个字符串具有长度为 $x$ 的循环节，对任意的 $x\ |\ y$ 且 $y\ |\ (r-l+1)$ 肯定有 $y$ 也是循环节，所以可以直接枚举每个质因数是否除掉。
3. 对于多组询问值域 $\le10^6$ 分解质因数问题，我们不需要 $O(Q\sqrt{n})$ 地暴力，我们可以 $O(n)+O(\log n)$ 地用线性筛筛出一个数最大的质因子。  

就这样。

代码如下
```
//愿你和你重要的人能够再次重逢！
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<'0'||c>'9';c=getchar()) if(!(c^45)) f=1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	if(f) x=-x;
}
const int B=137;unsigned bas[500005],has[500005];
int n,Q,pc,p[500005],mx[500005],st[500005],tp;char v[500005],c[500005];
inline unsigned Hash(int l,int r) {return has[r]-bas[r-l+1]*has[l-1];}
int main()
{
	read(n),scanf("%s",c+1);
	for(int i=2;i<=n;i++)
	{
		if(!v[i]) p[++pc]=i,mx[i]=i;
		for(int j=1;j<=pc&&i*p[j]<=n;j++) {v[i*p[j]]=1,mx[i*p[j]]=p[j];if(!(i%p[j])) break;}
	}
	bas[0]=1;for(int i=1;i<=n;i++) bas[i]=bas[i-1]*B,has[i]=has[i-1]*B+c[i]-'a'+1;
	for(read(Q);Q--;)
	{
		int l,r,len;read(l),read(r),len=r-l+1,tp=0;
		while(len^1) st[++tp]=mx[len],len/=mx[len];
		len=r-l+1;for(int i=1,qwq;i<=tp;i++) {qwq=len/st[i];if(Hash(l,r-qwq)==Hash(l+qwq,r)) len/=st[i];}
		printf("%d\n",len);
	}
	return 0;
}
###### ```

---

## 作者：szr666 (赞：6)

我这里推荐一下[我的博客](https://www.luogu.org/blog/szr666--blog/)

在博客里观看更美观哦~

[题目](https://www.luogu.org/problemnew/show/P3538)
------------


------------

华丽的分割线
# 解析

### 判断循环节

设在$[x,y]$区间中循环节长度为$now$,如何判断是否成立？

如图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/y8k8pevi.png)

当两个串相错开$now$大小后,若$[x+now,y]$和$[x,y-now]$

两个子串完全相同,则结论成立,用$hash$预处理后可$O(1)$查询

### 数学

既然知道可以$O(1)$判断,那二分答案$O(logn)$怎么样？

不行,因为答案不满足单调性,而枚举又变为$O(n)$超时

我们可以有技巧的枚举,设区间长度$l=y-x+1$

那么$now$一定为$l$的因数,否则不满足循环节定义

这样可以用$O(\sqrt n)$质因数分解$l$,再枚举可分成几份

假设两份可以,那么$l/=2$继续看行不行,不行就换下一个因数

知道最后$l$即为最小循环节长度,其中$now=l/$份数

因为在满足循环节定义的前提下,尽可能多除以因数,故答案最小

但仍然超时,可以之前预处理$[1,n]$中素数,直接枚举素数即可

### 复杂度

由于之前预处理哈希值和素数,所以复杂度$O(n)$

共有$q$次询问,每次对$l$分解质因数,并试除因数

因为$l$最大为$n$,所以后者复杂度为$O(logn)$

前者需枚举$\sqrt n$以内素数,而$a$以内素数为$\pi(a)$

所以复杂度为$O(\pi(\sqrt n))$,因为$\pi(a)\approx \frac{n}{ln(n)}$

所以总复杂度为$O(n+q(logn+\frac{\sqrt n}{ln(\sqrt n)}))$

# 代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define ll long long
using namespace std;
const int N=600000;
void read(int &x)
{
	char c;
	c=getchar();
	int f;
	f=1;
	x=0;
	while((c<'0'||c>'9')&&c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x=x*f;
}
char a[N];
ll hash1[N],pow1[N];
ll p1=998244353;
ll check1(int x,int y)
{
	return ((hash1[y]-hash1[x-1]*pow1[y-x+1]%p1)+p1)%p1;
}
int prime[N],tot;
bool is_prime[N];
void getprime(int n)
{
	int i,j;
	is_prime[1]=1;
	for(i=2;i<=n;i++)
	{
		if(is_prime[i]==0)
		{
			tot++;
			prime[tot]=i;
		}
		for(j=1;j<=tot&&i*prime[j]<=n;j++)
		{
			is_prime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				break;
			}
		}
	}
}
int pr[N],ptot;
int main()
{
	int i,j,la,n,x,y,len,now;
	read(n);
	tot=0;
	getprime(n);
	scanf("%s",a+1);
	la=strlen(a+1);
	pow1[0]=1;
	for(i=1;i<=la;i++)
	{
		pow1[i]=pow1[i-1]*26%p1;
		hash1[i]=(hash1[i-1]*26+a[i]-'a')%p1;
	}
	read(n);
	for(i=1;i<=n;i++)
	{
		read(x);
		read(y);
		len=y-x+1;
		ptot=0;
		int up=sqrt(len);
		for(j=1;j<=tot&&prime[j]<=up;j++)
		{
			if(len%prime[j]==0)
			{
				ptot++;
				pr[ptot]=prime[j];
			}
			while(len%prime[j]==0)
			{
				len/=prime[j];
			}
		}
		if(len!=1)
		{
			ptot++;
			pr[ptot]=len;
		}
		len=y-x+1;
		for(j=1;j<=ptot;j++)
		{
			now=len/pr[j];
			while(check1(x,y-now)==check1(x+now,y))
			{
				len/=pr[j];
				if(len%pr[j]!=0)
				{
					break;
				}
				now=len/pr[j];
			}
		}
		printf("%d\n",len);
	}
}
```


---

## 作者：Sino_E (赞：6)

给一个稍微非正解的写法，洛谷上大概能拿90分的样子orz

考虑一个区间的循环节长度为$k$，每个循环节里每种字母出现$x_i$次，总共字母出现$X_i$次。

那么我们可以得到一个27元不定方程组，总共26个方程式，呈$x_ik=X_i$的模样。

考虑$gcd(x_i)k=gcd(X_i)$，有较大概率$gcd(x_i)=1$，或者一个较小的数。

这样我们可以得到$k=gcd(X_i)$或者再除上一个较小的数。

我们将这个较小的数从1到15列举出来。

然后对于每一次区间询问，根据上面的分析枚举$k$的大小，再用hash判断$k$是否满足一个最小循环节。

这样子能骗过不少分的样子（雾）

虽然做了各种玄学调试但AC还是失败了呢（

```cpp
// Code by ajcxsu
// Problem: poem

#include<bits/stdc++.h>
#define MOD (1000000009ll)
using namespace std;

typedef long long ll;
const int N=5e5+10;
int arr[N];
ll ha[N], p[N];
int pri[]={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int t[26][N];

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    string s;
    cin>>n>>s>>m;
    p[0]=1;
    for(int i=1;i<=n;i++) {
        for(int j=0;j<26;j++) t[j][i]=t[j][i-1];
        t[s[i-1]-'a'][i]++;
        ha[i]=(ha[i-1]*26+s[i-1])%MOD, p[i]=(p[i-1]*26)%MOD;
    }
    int l, r, g=-1, len, tt;
    for(int i=0;i<m;i++) {
        cin>>l>>r;
        tt=r-l>10?15:3;
        g=len=-1;
        for(int j=0;j<26;j++)
            if(t[j][r]-t[j][l-1]) {
                if(g==-1) g=t[j][r]-t[j][l-1];
                else g=__gcd(g, t[j][r]-t[j][l-1]);
            }
        if((r-l+1)%g) {cout<<r-l+1<<endl; continue;}
        for(int j=0;j<tt;j++)
            if(g%pri[j]==0) {
                len=r-l+1-(r-l+1)/g*pri[j];
                if(((ha[l+len-1]-ha[l-1]*p[len]%MOD)+MOD)%MOD == ((ha[r]-ha[r-len]*p[len]%MOD)+MOD)%MOD)
                    break;
                len=-1;
            }
        cout<<r-l+1-len<<endl;
    }
    return 0;
}
```

---

## 作者：raincity (赞：2)

## 分析
首先，我们要判断对于 $s_{l,l+1,...r}$ ，$len$ 是不是循环节。

有一个性质：$len$ 是 $s_{l,l+1,...r}$ 的循环节的充分必要条件是 $s_{l,l+1,...(r-len)} = s_{(l+len),(l+len+1),....r}$ 且 $len|(r-l+1)$。（显然）

所以我们需要快速判断两个子串是否相等。方法：字符串哈希。（如果这都不会就没必要做紫题了）

先上 `prework`（预处理哈希）、`Calc`（计算哈希值）、`check`（判断）放上来：

![](https://cdn.luogu.com.cn/upload/image_hosting/rzh65r2k.png)

接着看看怎么做。

因为要求 $len|(r-l+1)$，所以需要快速得到 $r-l+1$ 的质因数分解形式。用线性晒可以得到每一个数的最小质因子：

![](https://cdn.luogu.com.cn/upload/image_hosting/qbwakb1s.png)

接着我们就可以解决这一个问题了。

因为答案 $ans|(r-l+1)$，我们可以 **依次** 试除 $r-l+1$ 的每一个质因子。对于每一个质因子，我们检查 $\dfrac{ans}{p}$ 是不是循环节。如果是，就更新 $ans$。

得到 `calc` 函数：

![](https://cdn.luogu.com.cn/upload/image_hosting/vth6iafs.png)

然后做完了，~~顺便拿了最优解，我的常数怎么这么小~~

## 解决

上代码 ~~图片~~

~~该死，用了 0.5M 的高级空间~~

![](https://cdn.luogu.com.cn/upload/image_hosting/3h3kemvz.png)

#### THE END

---

## 作者：Zxsoul (赞：1)

# [[POI]2012 OKR-A Horrible Poem](https://www.luogu.com.cn/problem/P3538)

## 思路

​	看许多题解都是质因数分解，我来一个不一样的

- 首先暴力分是很好得滴，直接暴力枚举合法的答案即可，但是他跑死了---40分

- 换个方向，如果 $S$ 是 $l-r$ 的循环节的话，那么我们有 $hs[l,r-s] = hs[s+1,r]$ ，$O(1)$得到答案----60分!!!

- 可他还是会 $T$ ,我们再将其进行优化：

   有数学和规律发现：字串 $len$ 和每个字母个数的总**公约数**为循环节的个数
   显然公约数越大，循环节的数量也就越多，对应的答案区间也就越小
   得到公约数后，从头枚举公约数就好了，可是他还是会 $T$ ---------------------80分！！

   **正解** 从头到尾可能很长，我们不妨用两头跑的方法，枚举公约数的约数，在得到对应的约数的商，这样就可以两头枚举了，这样就**AC**了 --------------------100分！！！！

  

## 注意

- 如果还是 $T$ 那就是您做了无用的冗杂处理，这里列出作者的错误
  - 进制太大( $131$ 或 $3$ 即可)，最后被卡---$1.01s$ !!!!
  -  无用的 $strlen$ ！！！！

## 代码

````c
/*
    直接暴力枚举可能性即可，但是他跑死了。 
    27 ——> 47(洛谷60) —— >97(MLE)--->97(TLE,1.01S)---->100 
    区间长度len和每个字母个数的总公约数为循环节的个数
    显然公约数越大，循环节的数量也就越多，对应的答案区间也就越小
    得到公约数后，就可以从大到小枚举区间，然后检查区间是否符合条件，符合条件的就break;
    这里约数和区间的小技巧
    从小枚举最大公约数的约数，换句话说就是将区间从小的开始枚举，在比较的过程中，可以也记录下
    枚举的约数的区间是否满足条件（防止循环节就一个）；
    MLE:进制循环大于开的数组空间
    TLE：1.进制太大，进制为3,速度955ms,
         2.卡时间（1.01s)，删除(strlen),速度985； 
     
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
#define F(i,l,r) for(int i=l;i<=r;i++)
#define FK(x) memset(x,0,sizeof(0))
#define int unsigned long long

using namespace std;
/*-----------------------------*/
const int manx = 5e5 + 10;
//const int mod = 1e9+9;
const int base = 3;

inline int read(){
    char c = getchar();int x = 0,f = 1;
    for(;!isdigit(c);c = getchar())if(c == '-') f = -1;
    for(;isdigit(c);c = getchar()) x = x*10 + (c^48);
    return x * f;
}
int n, p[manx], m, sum[manx], num[500010][26], x, y;
char a[manx];
inline void prepare(){
    p[0] = 1;
    F(i,1,n) p[i] = p[i-1]*base;    
}
inline int apart(int l, int r){
    return (sum[r] - sum[l-1]*p[r-l+1] ) ;
}
inline bool check(int l, int lenth){
    int x1 = apart(x,y-l),x2 = apart(x+l,y);
    if(x1 == x2) return 1;
    return 0;
}
inline int gcd(int x,int y){
    return y ? gcd(y, x%y) : x;
}
signed main(){
   // freopen("d.in","r",stdin);
   // freopen("d.out","w",stdout);
    n = read();
    prepare();
    scanf("%s", a + 1);
    int s = strlen(a+1);
    m = read();
    F(i,1,s) sum[i] = (sum[i-1]*base + a[i]) ;
    F(i,1,s)
    F(j,1,26){
        num[i][j] = num[i-1][j] + (a[i]-'a'+1==j);
    }
    while(m--){
        x = read(), y = read();
        int ans = 0, l = 1, gcd_;
        int k = y - x + 1;
        gcd_ = k;
        F(i,1,26) gcd_= gcd(gcd_, num[y][i] - num[x-1][i]);
        for(int i = 1; i * i<= gcd_; i++){
            if(gcd_% i == 0){
                if(check(k/(gcd_/i), k)){ans = max(ans, gcd_/i);break;} 
                if(check(k/i, k)) ans = max(ans,i);
            }
        }
        printf("%d\n",k/ans);
    }
    return 0;
}
````



---

## 作者：Parabola (赞：1)

#### Part0.题外话

~~我*** 垃圾sb题~~

~~卡常数题没品德垃圾废物wdnmd~~

我真的对这题的卡常数感到佛了...

不过还是写写题解吧(毕竟咕值低了很多

~~SA赛高，hash全部死掉~~

#### Part1.思路

注意到当字符串$s$是$t$的循环节时，要满足两个条件

（记len1 = $|s|$ , len2 = $|t|$）

1. $len1$为$len2$的约数。

2. 然后$t$的$[1,len2 - len1 + 1]$ 与 $[1+len1,len2]$相等

如果你好奇为什么这两个相等，$s$就是$t$的循环节，你可以这样看看。

例如 $t = s1 + "xxx" + s2$

而$[1,len2-len1+1] = s1 + "xxx"$，$[1+len1,len2]="xxx"+s2$

“xxx”就是他们的重复部分啦（

因为 s1 + "xxx" = "xxx" + s2

所以 "xxx"前面的一段是$s1$

即 s1 + s1 + "yyy" = s1 + "yyy" + s2

其中"yyy"是"xxx"去掉从前面s1后的字符串

所以 s1 + "yyy" = "yyy" + s2

注意到他和一开始的s1 + "xxx" = "xxx" + s2很像

其实这就是像一个数学归纳法一样，可以证出来循环...

然后我们判相等其实就是看他们的lcp就好了，感性理解一下~

然后对于区间$[l,r]$，我们可以通过分解质因数枚举答案判断是否正确

至于直接分解会TLE，可以想到欧拉筛

欧拉筛的复杂度证明有一个“每一个数都被他的最小素因子筛掉”，我们记录下来最小素因子加快分解。

#### Part3.Code

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define rep(i , a , b) for(int i = (a) ; i <= (b) ; ++i)
#define irep(i , a , b) for(int i = (b) ; i >= (a) ; --i)
#define IO ios::sync_with_stdio(false)
#define ms(A) memset(A , 0 , sizeof A)
#define msinf(A) memset(A , 0x3f , sizeof A)
typedef long long ll;
typedef pair <int , int> pii;

const int inf = 0x3f3f3f3f;
const ll infLL = 0x3f3f3f3f3f3f3f3fLL;

const int N = 500000 + 5;
const int lg_N = 20 + 5;

char s[N];
int n , q , sz , nxt[N] , pri[N] , x[N] , c[N] , y[N] , sa[N] , h[N] , lg[N] , st[lg_N][N];
bool vis[N];

inline int read() {
    char ch;
    int x = 0;
    for(; !isdigit(ch) ; ch = getchar());
    for(; isdigit(ch) ; ch = getchar()) x = x * 10 + ch - '0';
    return x;
}

void Euler() {
    rep(i , 1 , n) vis[i] = 1;
    vis[0] = vis[1] = 0;
    rep(i , 2 , n) {
        if(vis[i]) pri[++sz] = nxt[i] = i;
        for(int j = 1 ; j <= sz && pri[j] * i <= n ; ++j) {
            vis[pri[j] * i] = 0;
            nxt[pri[j] * i] = pri[j];
            if(i % pri[j] == 0) break;
        }
    }
}

void SA() {
	int m = 0;
    rep(i , 1 , n) m = max(m , x[i] = s[i]);
    rep(i , 1 , n) ++c[x[i]];
    rep(i , 1 , m) c[i] += c[i - 1];
    irep(i , 1 , n) sa[c[x[i]]--] = i;
    for(int k = 1 ; k <= n ; k <<= 1) {
        int p = 0;
        rep(i , 1 , k) y[++p] = n - i + 1;
        rep(i , 1 , n) if(sa[i] > k) y[++p] = sa[i] - k;
        rep(i , 1 , m) c[i] = 0;
        rep(i , 1 , n) ++c[x[i]];
        rep(i , 1 , m) c[i] += c[i - 1];
        irep(i , 1 , n) sa[c[x[y[i]]]--] = y[i];
        rep(i , 1 , n) y[i] = x[i];
        x[sa[1]] = m = 1;
        rep(i , 2 , n) x[sa[i]] = m += !(y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]);
		if(n == m) break; 
    }
    int k = 0;
    rep(i , 1 , n) {
        if(x[i] == 1) continue;
        if(k) --k;
        int j = sa[x[i] - 1];
        while(s[j + k] == s[i + k]) ++k;
        h[x[i]] = k;
    }
    rep(i , 2 , n) lg[i] = lg[i >> 1] + 1;
    rep(i , 1 , n) st[0][i] = h[i];
    rep(j , 1 , lg[n] + 1) 
        rep(i , 1 , n - (1 << j) + 1) st[j][i] = min(st[j - 1][i] , st[j - 1][i + (1 << (j - 1))]); 
}

inline int lcp(int l , int r) {
	l = x[l]; r = x[r];
	if(l > r) swap(l , r);
	if(l == r) return inf;
	++l; int len = lg[r - l + 1];
    return min(st[len][l] , st[len][r - (1 << len) + 1]);
}

inline bool check(int l , int r , int len) {
    return (lcp(l , l + len) >= r - l + 1 - len);
} 

int main() {
    scanf("%d %s" , &n , s + 1); 
    SA();
	Euler();
    scanf("%d" , &q);
    while(q--) {
        int l , r;
        l = read(); r = read();
        int ans = r - l + 1;
        for(int i = r - l + 1 ; i > 1 ; i /= nxt[i]) 
        	if(check(l , r , ans / nxt[i])) ans /= nxt[i];
        printf("%d\n" , ans);
    }
    return 0;
}
```


---

## 作者：2016gdgzoi581 (赞：1)

~~（大力出奇迹）~~

对于每一次询问，答案肯定是这次询问长度的约数。

考虑一个子串$S[l...r]$，设其长度为$len$。如何确定它能不能再划分为更小的循环节？枚举$len$的质因数$p_i$，若对于每个$p_i$,长度为$len/p_i$的子串$S[l...len/p_i+1]$都不能作为$S$的循环节，则$S[l...r]$的最短循环节为它本身，否则递归处理。

如何判断$S[x...y]$是否为$S[l...r]$的循环节？$(l\le x\le y\le r)$

设$l_1=y-x+1,l_2=r-l+1$,首先判断$l2$是否整除$l1$

根据哈希的意义，一段子串的哈希值实际是这段子串在$base$进制下表示的数模$mod$的余数。所以，令$h1$为$S[x...y]$的哈希值，$h2$为$S[l...r]$的哈希值，若$S[x...y]$是为$S[l...r]$的循环节,则
$$h1×(base^0+base^{l1}+base^{2l_1}...base^{l2-l1})\equiv h2$$

可用等比数列求和公式~~（大力）~~计算。

注意先处理逆元和质因数。

```cpp
#pragma GCC optimize(3) 
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
#define ll long long
const ll m1=598669,m2=598657;
const ll base=233;
ll qp1[2300000/4],qp2[2333333/4],iv1[510000],iv2[510000];
ll h1[2333333/4],h2[2333333/4];
ll get1(ll l,ll r){
	return (h1[r]-h1[l-1]*qp1[r-l+1]%m1+m1)%m1; 
}
ll get2(ll l,ll r){
	return (h2[r]-h2[l-1]*qp2[r-l+1]%m2+m2)%m2; 
}
ll qpow(ll x,ll k,ll mod){
	ll s=1;
	while(k){
		if(k&1)s*=x,s%=mod;
		x*=x,x%=mod;
		k>>=1;
	}
	return s;
}
void extgcd(ll a,ll b,ll& d,ll& x,ll& y){
    if(!b){ d=a; x=1; y=0;}
    else{ extgcd(b,a%b,d,y,x); y-=x*(a/b); }
}
ll inv(ll a,ll n){
    ll d,x,y;
    extgcd(a,n,d,x,y);
    return d==1?(x+n)%n:-1;

}
int p[100100];
bool vis[500001];
vector<int> pfac[500010];
void init(){
	qp1[0]=qp2[0]=iv1[0]=iv2[0]=1;
	for(int i=1;i<=1000001/2;++i){
		qp1[i]=qp1[i-1]*base%m1;
		qp2[i]=qp2[i-1]*base%m2;
		iv1[i]=inv(qp1[i]-1,m1);
		iv2[i]=inv(qp2[i]-1,m2);
	}
	vis[1]=1;
	for(register int i=2;i<=500000;++i){
		pfac[i].push_back(i);
		if(!vis[i]){
			p[++p[0]]=i;
			for(register int j=2;j*i<=500000;++j){
				vis[i*j]=1;
				pfac[i*j].push_back(i);
			}
		}
	}
} 
//s[x..y]是否为s[l..r]的循环节 
inline bool check(int x,int y,int l,int r){
	int l1=y-x+1,l2=r-l+1;
	ll t1=(qp1[l2]-1)*iv1[l1]%m1;
	ll t2=(qp2[l2]-1)*iv2[l1]%m2;
	return get1(x,y)*t1%m1==get1(l,r)&&get2(x,y)*t2%m2==get2(l,r); 
}
inline int solve(int l,int r){
	if(r==l)return 1;
	int len=r-l+1;
	for(int i=0;i<pfac[len].size();++i){
		int l2=len/pfac[len][i];
		if(check(l,l+l2-1,l,r))return solve(l,l+l2-1);
	}
	return len;
}
int n,q;
char ch[2333333/4];
inline void read(int &x){
    char c=getchar();x=0;    
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
}
inline void write(int x){
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
signed main(){
//	freopen("true.in","r",stdin); 
	scanf("%d",&n);
//	scanf("%s",ch+1);
	getchar();
	for(int i=1;i<=n;++i)ch[i]=getchar();
	scanf("%d",&q);
	init();
	for(register int i=1;i<=n;++i)h1[i]=h1[i-1]*base%m1+ch[i]-'a',h2[i]=h2[i-1]*base%m2+ch[i]-'a';
	int l,r;
	while(q--){
		read(l);
		read(r);
		write(solve(l,r));
		putchar('\n'); 
	} 
}
```

---

## 作者：critnos (赞：0)

一个十分暴力的做法。

首先我们知道，如果 $[l,r-len]=[l+len,r]$ 相等，那么 $len$ 就是 $[l,r]$ 的循环节。

而 $len$ 又必须是 $r-l+1$ 的因数。

所以：

枚举 $r-l+1$ 的因数，每次验证第一个条件是否相等，即可解决本题。

然后，对于判断两个区间是否相等，可以使用哈希。

对于区间的哈希值，使用前缀和和直接自然溢出啥事没有维护即可。

详细些说：

前缀和数组 $p$ 应当用 `ull` 类型。因为他不仅范围大，而且对于小于 $0$ 也会溢出。即模数为 $2^{64}$。

构造出来，$p_i=a_i\times hash^i+p_{i-1}$，$hash$ 建议取一个较大的数，我用的是 $23333333333$。

这样子方便对比区间。设 $sum(l,r)$ 为区间 $[l,r]$ 的哈希值（$p_r-p_{l-1}$），对于验证条件 $1$，判断 $sum(l,r-len)\times hash^{len}$ 和 $sum(l+len,r)$ 是否相等。因为两个区间的哈希值事实上还差了一个 $hash^{len}$。

时间复杂度证明：

因数个数是 $\sqrt n$ 级别的，所以总时间复杂度应当是 $n+q\sqrt n$ 是过不去的。但是：

* 因数个数 $\sqrt n$ 是一个宽松的上界。事实上 $\le 5\times 10^5$ 的数中因数最多的有 $160$ 个。

* 不一定有要全部验证完。找到一个可行的就退出了。

当然上面的是最坏的时间复杂度，期望时间复杂度是：

$l,r$ 在区间 $[1,n]$ 内随机生成。所以 $r-l+1$ 也是 $n$ 级别的。在 $[1,k]$ 随机取一个数，它的因数个数期望是 $\log k$。所以，期望时间复杂度是 $n+q\log n$。

---

## 作者：MikukuOvO (赞：0)

考虑最裸的暴力，对于每一个区间做一遍$KMP$，复杂度$O(nm)$。

考虑使用哈希，枚举每一个区间长度的因数，可以证明只有$\sqrt n$个，然后判断$[l,r-d]$和$[l+d,r]$这两个字串是否相等即可，复杂度$O(m\sqrt n)$。

考虑到如果$d$是一个循环节，那么$d$的倍数也一定是，因此我们考虑对区间长度进行质因数分解，发现每个质因子之间互不干扰，这样我们从大到小枚举该因子取几个，直到不能取为止，这样复杂度是$O(mlogn)$的。

```cpp
const int N=5e5+5;
const int base=131;
const ll mod=998244353;

int n,m,cnt;
int pri[N],nxt[N],t[N];
char s[N];
ll h[N],f[N];
bool isp[N];

void init()
{
    f[0]=1;
    for(int i=1;i<=n;++i) h[i]=(h[i-1]*base%mod+s[i]-'a')%mod;
    for(int i=1;i<=n;++i) f[i]=f[i-1]*base%mod;
    for(int i=2;i<=n;++i)
    {
        if(!isp[i]) pri[++cnt]=i,nxt[i]=i;
        for(int j=1;j<=cnt&&i*pri[j]<=n;++j)
        {
            isp[i*pri[j]]=true,nxt[i*pri[j]]=pri[j];
            if(i%pri[j]==0) break;
        }
    }
}
bool check(int lx,int rx,int ly,int ry)
{
    ll a=(h[rx]-h[lx-1]*f[rx-lx+1]%mod+mod)%mod,b=(h[ry]-h[ly-1]*f[ry-ly+1]%mod+mod)%mod;
    return a==b;
}
int main()
{
    fio();
    gi(n);
    scanf("%s",s+1);
    init();
    gi(m);
    for(int i=1,l,r;i<=m;++i)
    {
        gi(l,r);
        int len=r-l+1,num=0;
        while(len!=1)
        {
            t[++num]=nxt[len];
            len/=nxt[len];
        }
        len=r-l+1;
        for(int j=1;j<=num;++j)
        {
            int d=len/t[j];
            if(check(l,r-d,l+d,r)) len=d;
        }
        print(len),pc(10);
    }
    end();
}
```

---

