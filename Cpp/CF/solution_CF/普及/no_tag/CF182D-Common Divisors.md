# Common Divisors

## 题目描述

Vasya has recently learned at school what a number's divisor is and decided to determine a string's divisor. Here is what he came up with.

String $ a $ is the divisor of string $ b $ if and only if there exists a positive integer $ x $ such that if we write out string $ a $ consecutively $ x $ times, we get string $ b $ . For example, string "abab" has two divisors — "ab" and "abab".

Now Vasya wants to write a program that calculates the number of common divisors of two strings. Please help him.

## 说明/提示

In first sample the common divisors are strings "abcd" and "abcdabcd".

In the second sample the common divisor is a single string "a". String "aa" isn't included in the answer as it isn't a divisor of string "aaa".

## 样例 #1

### 输入

```
abcdabcd
abcdabcdabcdabcd
```

### 输出

```
2
```

## 样例 #2

### 输入

```
aaa
aa
```

### 输出

```
1
```

# 题解

## 作者：OldVagrant (赞：5)

## 题意
给定两个字符串 $S_1,S_2$，求有多少个字符串 $x$ ，满足 $x$ 在复制若干次拼接起来后既可以得到 $S_1$，又可以得到 $S_2$。
## Solution
题解里似乎还没有普通 ```KMP``` 的做法，那我就来补充一个。   
首先，要知道一个结论，令一个字符串 $S$ 的最小循环元为 $L$，那么 $S$ 的任意循环元 $L'$，必定是由若干个 $L$ 复制若干次拼接起来的。   
然后由于 $x$ 既是 $S_1$ 的循环元，又是 $S_2$ 的循环元，那么 $x$ 存在的前提条件就是 $S_1$ 和 $S_2$ 的最小循环元完全相同，否则无法同时满足 $x$ 是 $S_1$ 和 $S_2$ 的循环元（由上面的那个结论可以推出来）。  
那么，不妨先把 $S_1,S_2$ 的最小循环元 $L$ 用 ```KMP``` 分别求出来，把 $S_1$ 表示为 $a$ 个 $L$ 拼接而成，把 $S_2$ 表示为 $b$ 个 $L$ 拼接而成，把 $x$ 表示为 $c$ 个 $L$ 拼接而成，可得 $c|a$ 且 $c|b$ ，即 $c$ 是 $a,b$ 的公约数。然后暴力枚举 $a,b$ 的约数即可。
## Code
```
#include <bits/stdc++.h>
#define gc getchar
using namespace std;
int neA[100001],neB[100001],fac[100001];//两个ne数组都是用来求最小循环元L的，fac用于存储某个因数是否出现过
char a[100001],b[100001];
signed main(){
	int n=0,m=0;
	char ch=gc();
	while(ch<'a'||ch>'z') ch=gc();
	while(ch>='a'&&ch<='z') a[++n]=ch,ch=gc();
	while(ch<'a'||ch>'z') ch=gc();
	while(ch>='a'&&ch<='z') b[++m]=ch,ch=gc();//a,b只含小写字母，用getchar加上特判读入
	for(int i=2,j=0;i<=n;neA[i]=j,i++){//下面是普通的KMP算法部分
		while(j&&a[i]!=a[j+1]) j=neA[j];
		if(a[i]==a[j+1]) j++;
	}for(int i=2,j=0;i<=m;neB[i]=j,i++){
		while(j&&b[i]!=b[j+1]) j=neB[j];
		if(b[i]==b[j+1]) j++;
	}int minA=neA[n],minB=neB[m],p,q,ans=0;
   //只有当n是循环元长度(n-minA)的倍数时，a[1]~a[n-minA]才是a的最小循环元，b同理
	while(n%(n-minA)) minA=neA[minA];
	while(m%(m-minB)) minB=neB[minB];
	p=n-minA,q=m-minB;
	if(p!=q) cout<<0,exit(0);
	for(int i=1;i<=p;i++) if(a[i]!=b[i]) cout<<0,exit(0);//如果两字符串的最小循环元不完全相同，则不可能存在合法的x
	for(int i=1,j=n/p;i<=j;i++) if(j%i==0) fac[i]=1;//标记每个约数是否出现过
	for(int i=1,j=m/q;i<=j;i++) if(j%i==0) ans+=fac[i];//累加到答案里
	cout<<ans;
	return 0;
}
```

---

## 作者：Allanljx (赞：4)

## 思路
首先，将两个字符串分别哈希，然后枚举两个字符串的公因数（同时也是公共因子串的长度）。然后对于每个子串用哈希检查一下。
## 代码
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
char s1[100005],s2[100005];
int h1[100005];
int h2[100005];
int db[100005];
int ans;
signed main()
{
	db[0]=1;
	for(int i=1;i<=100000;i++) db[i]=db[i-1]*27;
	cin>>(s1+1)>>(s2+1);
	int l1=strlen(s1+1),l2=strlen(s2+1);
	for(int i=1;i<=l1;i++)//哈希
	{
		h1[i]=h1[i-1]*27+s1[i]-'a';
	}
	for(int i=1;i<=l2;i++)//哈希
	{
		h2[i]=h2[i-1]*27+s2[i]-'a';
	}
	for(int i=1;i<=min(l1,l2);i++)//枚举公因数
	{
		if(l1%i||l2%i) continue;
		int f1=0,f2=0;
		for(int j=i;j<=l1;j+=i)//检查哈希值
		{
			if(h1[j]-h1[j-i]*db[i]!=h1[i])
			{
				f1=1;
			}
		}
		for(int j=i;j<=l2;j+=i)//检查哈希值
		{
			if(h2[j]-h2[j-i]*db[i]!=h2[i])
			{
				f2=1;
			}
		}
		if(!f1&&!f2&&h1[i]==h2[i]) ans++;
	}
	cout<<ans<<endl;
}
```


---

## 作者：山田リョウ (赞：3)

题解区里好像都是 $O(\sigma(n))$ 的哈希的做法，我来发一篇线性的扩展 kmp 的做法吧。

**本文中字符串下标从 $0$ 开始，$s[i]$ 表示字符串 $s$ 从第 $i$ 个字符开始的后缀。**

容易注意到，如果一个长度为 $n$ 的字符串 $s$ 有长度为 $i$ 的循环节，则 $i|n$ 且 $\operatorname{lcp}\left(s,s[i]\right)+i=n$。

可以发现上面那个 $\operatorname{lcp}\left(s,s[i]\right)$ 显然就是 $\operatorname{z}$ 函数，所以跑一遍 exKMP 就能得到。

所以我们对两个字符串各跑一遍 exKMP，求出 $\operatorname{z}$ 函数后，枚举循环节长度 $i$，判断是否有长度为 $i$ 的循环节，而且如果两个字符串的长度为 $i$ 的前缀（因为如果前缀都不相等了，即使都有长度为 $i$ 的循环节，循环节也不可能相等）不相等了，就跳出循环。

$\green{\text{AC code}}$:

```cpp
// Problem: CF182D Common Divisors
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF182D
// Memory Limit: 250 MB
// Time Limit: 2000 ms

#include<stdio.h>
#include<string.h>
void exkmp(char*s,int*z,int n){
	for(int i=1,j=0,k=z[0]=0;i<n;++i){
		if(i<=k&&z[i-j]<=k-i)z[i]=z[i-j];
		else for(z[i]=(k+1>i?k+1-i:0);i+z[i]<n&&s[z[i]]==s[i+z[i]];++z[i]);
		if(z[i]+i-1>k)k=z[i]+i-1,j=i;
	}
}
char s1[200001],s2[200001];
int z1[200001],z2[200001];
inline int min(int a,int b){return a<b?a:b;}
int main(){
	int n,m,cnt=0;
	scanf(" %s",s1),n=strlen(s1);
	scanf(" %s",s2),m=strlen(s2);
	exkmp(s1,z1,n),exkmp(s2,z2,m);
	for(int i=1;s1[i-1]==s2[i-1]&&i<=n&&i<=m;++i)
		if(!(n%i)&&!(m%i)&&z1[i]+i==n&&z2[i]+i==m)
			++cnt;
	printf("%d",cnt);
	return 0;
}
```

---

## 作者：MostlyHarmless (赞：2)

~~这题居然没题解？没事，我来水一发~~
## 思路
本题主要考察字符串哈希。字串哈希是指用一个数代表一串字母（对于本题，哈希出来的数字至少是$26$进制，原因相信大家也知道），~~当然，由于取模操作它有一定的错误概率。~~ 

~~教练告诉我们~~根据题目可以归纳出公因子串的几个性质
1. 其长度必然为$s_1$,$s_2$的公因数
2. 对于长度为$i$的因子串，将 $s_1$ 切分为长度为 $i$ 的若干段，每一段必须与 $s_1$ 中长度为 $i$ 的前缀相同
3. 同理，对于长度为$i$的因子串，将 $s_2$ 切分为长度为 $i$ 的若干段，每一段必须与 $s_2$ 中长度为 $i$ 的前缀相同

知道这些之后大致就可以开始码代码了。不过有些细节时要注意的，具体见下。
## 代码
码风奇丑，大佬勿喷。
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 100005;
const int mod = 1000000007;
string s1,s2;
long long h1[maxn],h2[maxn],p26[maxn];
bool ch(int p) {
	//怎么理解判断呢
	//举个例子，对于字串abcdabcdabcdabcd，p = 3，即要判断的因子串为abcd
	//那第一次循环i就直接=7，即拿到的哈希数h1[8]代表abcdabcd
	//这时我们需要判断的的只有****abcd是不是==abcd，因为之前的肯定判断过了，并且是一个或多个abcd堆叠起来的
	//所以我们要干的事情就明朗了，具体操作见下
	for (int i = p*2+1; i < s1.size(); i = i+p+1) {
		//可以自己试着推一下~~实际上和状压dp的二进制位操作有点类似~~
		long long cur = (h1[i+1] - h1[i-p] * p26[p+1] % mod + mod)%mod;
		if (cur != h1[p+1]) {
			return false;
		}
	}
	for (int i = p*2+1; i < s2.size(); i = i+p+1) {
		long long cur = (h2[i+1] - h2[i-p] * p26[p+1] % mod + mod)%mod;
		if (cur != h1[p+1]) {
			return false;
		}
	}
	return true;
}
int main() {
	cin >> s1 >> s2;
	//预处理26的次方
	p26[0] = 1LL;
	for (int i = 1; i < maxn; i++) {
		p26[i] = p26[i-1]*26LL%mod;
	}
	//由于事先没考虑好，用了string，必须从0开始为下标，麻烦无比。改用字符数组下标从1开始会舒服很多。
	for (int i = 0; i < s1.size(); i++) {
		h1[i+1] = h1[i]*26LL+(s1[i]-'a');
		h1[i+1] %= mod;
	}
	for (int i = 0; i < s2.size(); i++) {
		h2[i+1] = h2[i]*26LL+(s2[i]-'a');
		h2[i+1] %= mod;
	}
	int ans = 0;
	for (int i = 0; i < min(s1.size(),s2.size()); i++) {
		//前两个判断：字串长度是公因数
		if (s1.size()%(i+1) == 0 && s2.size()%(i+1) == 0 && h1[i+1] == h2[i+1]) {
			if (ch(i)) ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
```
完结撒花

---

## 作者：IkunTeddy (赞：1)

# 题目分析
看到楼上大佬都在用 hash，我什么前缀函数 PMT 的忠实拥护者必须上一波新思路。

我们只需先用 PMT 求出 border 那么周期自然而然就求出来了，只需一一对比两字符串的周期是否相同答案就求出来了。

# Code
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int maxn=1e5+10;
char s1[maxn],s2[maxn];
int pi1[maxn],pi2[maxn];
int per1[maxn],per2[maxn];
int l1,l2;
void PMT(char s[],int pi[]){
	int l=strlen(s+1);
	for(int i=2;i<=l;i++){
		int j=pi[i-1];
		while(j&&s[j+1]!=s[i])j=pi[j];
		if(s[j+1]==s[i])j++;
		pi[i]=j;
	}
}
int cnt1,cnt2;
void get(int per[],int pi[],int l,int &cnt){
	int x=l;
	while(x){
		per[++cnt]=l-x;
		x=pi[x];
	}
	per[++cnt]=l;
}
ull h1[maxn],h2[maxn],Base[maxn],base=2936349;
ull Hash(int l,int r,ull h[]){
	return h[r]-h[l-1]*Base[r-l+1];
   	//我不会告诉你，我也偷偷用了hash比较周期(●´∀｀●)
}
int ans=0;
int main(){
	scanf("%s%s",s1+1,s2+1);
	l1=strlen(s1+1),l2=strlen(s2+1);
	Base[0]=1;
	for(int i=1;i<=max(l1,l2);i++)Base[i]=Base[i-1]*base;
	PMT(s1,pi1);
	PMT(s2,pi2);
	get(per1,pi1,l1,cnt1);
	get(per2,pi2,l2,cnt2);
	for(int i=1;i<=l1;i++)h1[i]=h1[i-1]*base+s1[i];
	for(int i=1;i<=l2;i++)h2[i]=h2[i-1]*base+s2[i];
	int p1=2,p2=2;
	while(p1<=cnt1&&p2<=cnt2){
		while(p1<=cnt1&&per1[p1]<per2[p2])p1++;
		while(p2<=cnt2&&per2[p2]<per1[p1])p2++;
		if(Hash(1,per1[p1],h1)==Hash(1,per2[p2],h2)&&l1%per1[p1]==0&&l2%per2[p2]==0)ans++;
		p1++,p2++;
	}
	cout<<ans<<endl;
	
	return 0;
}

```

---

## 作者：I_will_AKIOI (赞：0)

由于因子串需要一个一个拼起来，所以我们枚举字符串的前缀，就可以枚举到因子串。假设两个字符串为 $s$ 和 $t$，长度分别为 $n,m$。接着把这个因子串一个个拼起来，最后哈希判断是否和两个字符串相等。设当前枚举到了 $i$，那么需要拼接 $\displaystyle\frac{n}{i}+\frac{m}{i}$ 次。容易发现复杂度是调和级数级别的。

```cpp
#include<bits/stdc++.h>
#define N 100005
#define int unsigned long long
#define BASE 100
using namespace std;
string s,t;
int n,m,ans,h1,h2,h,p[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>s>>t;
	n=s.size(),m=t.size();
	for(int i=0;i<n;i++) h1=h1*BASE+s[i]-'a';
	for(int i=0;i<m;i++) h2=h2*BASE+t[i]-'a';
	p[0]=1;
	for(int i=1;i<=100000;i++) p[i]=p[i-1]*BASE;
	for(int i=1;i<=n;i++)
	{
		h=h*BASE+s[i-1]-'a';
		if(n%i==0&&m%i==0)
		{
			int h3=h,f1=0,f2=0;
			for(int j=i;j<=n;j+=i)
			{
				if(h3==h1)
				{
					f1=1;
					break;
				}
				h3=h3*p[i]+h;
			}
			h3=h;
			for(int j=i;j<=m;j+=i)
			{
				if(h3==h2)
				{
					f2=1;
					break;
				}
				h3=h3*p[i]+h;
			}
			if(f1&&f2) ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：eb0ycn (赞：0)

# CF182D Common Divisors 题解

## 思路

假设有两个字符串 $t$ 和 $s$，它们的长度分别为 $k$ 和 $n$。

我们可以发现：只有 $k$ 是 $n$ 的因子时，$t$ 才**有可能**是 $s$ 的“因子串”。并且对于一个固定的 $s$，不可能有两个“因子串”长度相同。

所以，我们只需要对两个字符串进行哈希，再枚举每个可行的长度 $i$，以较短字符串的前 $i$ 个元素的哈希值 $tot$ 为标准，看剩余部分是否可以分为若干个哈希值为 $tot$ 的子串。具体见代码。

## 代码



```cpp
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
char a[100001],b[100001];
ull chash[2][100001][2],poww[100001][2],tot1,tot2,cm1,cm2;
int n,m,k,flag,ans;
inline ull rh1(int i,int l,int r)//O(1) 获取一段区间的哈希值。
{
	return chash[i][r][0]-chash[i][l-1][0]*poww[r-l+1][0];
}
inline ull rh2(int i,int l,int r)
{
	return chash[i][r][1]-chash[i][l-1][1]*poww[r-l+1][1];
}
int main()
{
	poww[0][0]=poww[0][1]=1;
	for(int i=1;i<=100000;++i)poww[i][0]=poww[i-1][0]*13,poww[i][1]=poww[i-1][1]*17;
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1),m=strlen(b+1);
	if(n>m)swap(a,b),swap(n,m);
	for(int i=1;i<=n;++i)
	{
		chash[0][i][0]=chash[0][i-1][0]*13+a[i];//为了防止出事，
		chash[0][i][1]=chash[0][i-1][1]*17+a[i];//我用了双哈希。
	}
	for(int i=1;i<=m;++i)
	{
		chash[1][i][0]=chash[1][i-1][0]*13+b[i];
		chash[1][i][1]=chash[1][i-1][1]*17+b[i];
	}
	for(int i=1;i<=n;++i)//枚举“因子串”的长度。 
	{
		if(n%i||m%i)continue;//首先，“因子串”的长度得是元字符串长度的因子。
		flag=1;
		tot1=rh1(0,1,i);//如果符合要求，
		tot2=rh2(0,1,i);//每一段应该都是这两个哈希值。
		for(int j=i+1;j<=n-i+1;j+=i)//枚举较短字符串的每一段的起始位置。 
		{
			cm1=rh1(0,j,j+i-1);
			cm2=rh2(0,j,j+i-1);
			if(cm1!=tot1||cm2!=tot2)
			{
				flag=0;
				break;
			}
		}
		if(!flag)continue;
		for(int j=1;j<=m-i+1;j+=i)//枚举较长字符串的起始位置。（注意这里要从头开始）
		{
			cm1=rh1(1,j,j+i-1);
			cm2=rh2(1,j,j+i-1);
			if(cm1!=tot1||cm2!=tot2)
			{
				flag=0;
				break;
			}
		}
		if(flag)++ans;
	}
	printf("%d",ans);
	return 0;
}
```



------------


## 关于时间复杂度

虽然此代码看上去有两重循环，但随着 $i$ 的增大，内层的循环次数在不断减小。所以理论上，时间复杂度应该是一个类似[调和级数](https://baike.baidu.com/item/%E8%B0%83%E5%92%8C%E7%BA%A7%E6%95%B0/8019971?fr=ge_ala)的东西。


$$O\large(\sum_{i=1}^n \frac{n}{i} )$$

大概就是 $O(n \log n)$。

由于 $i$ 要被 $n$ 和 $m$ 整除，所以实际的时间复杂度肯定比它更低。

---

## 作者：Shadow_T (赞：0)

### 题目大意

给定两个字符串 $a,b$，求有多少个字符串 $s$，多次拼接后可以组成 $a$ 和 $b$。

$1\leq |a|,|b| \leq 10^5$。

### 解题思路

考虑哈希，先求出 $a,b$ 的哈希值 $h_1,h_2$。

然后以 $1$ 为头往后找子串 $s$。如果此子串的长度为 $|a|$ 和 $|b|$ 的公因数，那么算出 $s$ 衔接 $\frac{|a|}{i}$ 的哈希 $H_1$ 和 衔接 $\frac{|b|}{i}$ 次的哈希 $H_2$。如果 $H_1=h_1$ 且 $H_2=h_2$ 哈希相等，就可以统计一次。

有亿点点小卡常，第一次用双哈希在第 $44$ 个点炸了。在衔接多次字符串时加了个速，选用了能乘 $2$ 的加速。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int hash_a=157;
const int mod=1e18+7;
int get_hash(string s)
{
	int n=s.size();
	int res=0;
	for(int i=0;i<n;i++)
	{
		res*=hash_a;
		res%=mod;
		res+=(s[i]-'a');
	}
	return res%mod;
}
string calc(string s,int c)
{
	string s1=s;
	int cs=s.size();
	int len=cs;
	int mb=c*cs;
	while(cs<mb)
	{
		if(cs*2<mb) cs*=2,s=s+s;
		else cs+=len,s+=s1;
	}
	return s;
}
signed main()
{
	string a,b;
	cin>>a>>b;
	string s="";
	int n=min(b.size(),a.size());
	int lena=a.size(),lenb=b.size();
	int hasha1=get_hash(a);
	int hashb1=get_hash(b);
	int ans=0;
	for(int i=0;i<n;i++)
	{
		s+=b[i];
		if(lena%(i+1)==0&&lenb%(i+1)==0)
		{
			string s1=calc(s,lena/(i+1)),s2=calc(s,lenb/(i+1));
			int hash1=get_hash(s1),hash2=get_hash(s2);
			if(hash1!=hasha1||hash2!=hashb1) continue;
			else ans++;
		}
	}
	cout<<ans;
}
```

---

## 作者：_edge_ (赞：0)

感觉这道题目还是挺简单的。

首先，我们看到这个东西，显然，只有答案的字符串长度为 s1 长度，s2 长度的公共约数，才能够合法。

然后就可以直接找出 s1 长度，s2 长度的公共约数，这个东西是 $d(10^5)$，不会超过 $50$。

然后我们再去对他进行枚举，那么考虑长度已经确定了，怎么确定答案字符串呢。

试想一下，如果合法，那么再第一个字符串里面去一节都是可以的！不妨取第一节。

然后我们取出之后，大力进行枚举判断。

然而这个暴力实现复杂度是 $O(n^2 \times d(10^5))$ 的。

显然是过不了这道题目的。

总结一下，我们发现复杂度大部分消耗在取出字符串和判断字符串是否相等。

容易想到，这种操作可以用 hash 比较迅速的维护。

本质上来说，hash 就是一个多进制的数，因此取出选定的一节字符串的值是比较好做的。

当然，这里如果模数选的不好，可能会被奇怪的 hack 掉。

这里推荐双模数 $10^9+7$，$998244353$。

但是我比较懒，所以只用了 $10^9+7$ 但也过掉了。

时间复杂度 $O(n \times d(10^5))$。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define int long long 
#define pb push_back
using namespace std;
const int INF=1e5+5;
const int Mod=1e9+7;
const int base=233;
const int Mod1=998244353;
const int base1=191;
string s1,s2;
vector <int> v;
int hash1[INF],hash2[INF],ba[INF];
int query1(int l,int r) {
	int len=ba[r-l+1];
	return (hash1[r]-hash1[l-1]*len%Mod+Mod)%Mod;
}
int query2(int l,int r) {
	int len=ba[r-l+1];
	return (hash2[r]-hash2[l-1]*len%Mod+Mod)%Mod;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s1>>s2;
	int len1=s1.size(),len2=s2.size();
	s1=" "+s1;s2=" "+s2;
	for (int i=1;i*i<=len1;i++) {
		if (len1%i==0) {
			int kk=i;
			if (len2%kk==0) 
				v.pb(kk);
			kk=len1/i;
			if (kk==i) continue;
			if (len2%kk==0)
				v.pb(kk);
		}
	}
	ba[0]=1;
	int len=max(len1,len2);
	for (int i=1;i<=len;i++)
		ba[i]=(ba[i-1]*base)%Mod;
	for (int i=1;i<=len1;i++)
		hash1[i]=(hash1[i-1]*base%Mod+s1[i]-'a'+5)%Mod;
	for (int i=1;i<=len2;i++)
		hash2[i]=(hash2[i-1]*base%Mod+s2[i]-'a'+5)%Mod;
	
	int vlen=v.size();
	int ans=0;
	for (int i=0;i<vlen;i++) {
		int kk=query1(1,v[i]);
		int fl=1;
		for (int j=1;j<=len1;j+=v[i])
			if (kk!=query1(j,j+v[i]-1)) fl=0;
		for (int j=1;j<=len2;j+=v[i])
			if (kk!=query2(j,j+v[i]-1)) fl=0;
		ans+=fl;
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

