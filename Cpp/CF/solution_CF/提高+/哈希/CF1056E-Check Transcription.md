# Check Transcription

## 题目描述

One of Arkady's friends works at a huge radio telescope. A few decades ago the telescope has sent a signal $ s $ towards a faraway galaxy. Recently they've received a response $ t $ which they believe to be a response from aliens! The scientists now want to check if the signal $ t $ is similar to $ s $ .

The original signal $ s $ was a sequence of zeros and ones (everyone knows that binary code is the universe-wide language). The returned signal $ t $ , however, does not look as easy as $ s $ , but the scientists don't give up! They represented $ t $ as a sequence of English letters and say that $ t $ is similar to $ s $ if you can replace all zeros in $ s $ with some string $ r_0 $ and all ones in $ s $ with some other string $ r_1 $ and obtain $ t $ . The strings $ r_0 $ and $ r_1 $ must be different and non-empty.

Please help Arkady's friend and find the number of possible replacements for zeros and ones (the number of pairs of strings $ r_0 $ and $ r_1 $ ) that transform $ s $ to $ t $ .

## 说明/提示

In the first example, the possible pairs $ (r_0, r_1) $ are as follows:

- "a", "aaaaa"
- "aa", "aaaa"
- "aaaa", "aa"
- "aaaaa", "a"

The pair "aaa", "aaa" is not allowed, since $ r_0 $ and $ r_1 $ must be different.

In the second example, the following pairs are possible:

- "ko", "kokotlin"
- "koko", "tlin"

## 样例 #1

### 输入

```
01
aaaaaa
```

### 输出

```
4
```

## 样例 #2

### 输入

```
001
kokokokotlin
```

### 输出

```
2
```

# 题解

## 作者：brealid (赞：13)

说一个关于 Hash 的复杂度证明（下文中 $S_{01}$ 表示 $01$ 串，$S_{abc}$ 表示字母串）![/fad](https://cdn.luogu.com.cn/upload/pic/62250.png)

---

> 通常这道题的 Hash 做法流程是这样的（记 $cnt_0$ 为 $01$ 串中的 $0$ 个数，$cnt_1$ 为 $01$ 串中的 $1$ 个）
> 1. 枚举 $r_0$ 的长度 $len_0$
> 2. 如果根据枚举到的长度 $len_0$ 可以找到一个正整数 $len_1$，满足 $cnt_0 * len_0 + cnt_1 * len_1 = |S_{abc}|$，那么进行第 $3$ 步，否则枚举下一个 $len_0$
> 3. 扫一遍 $S_{01}$，同时维护一个指针 $p$ 指向 $S_{abc}$ 中的字符（初始为 $1$）。如果遇到 $0$，则将 $^{\mathbf{Hash}}r_{0}$ 与 $Hash(p, p + len_0 - 1)$ 比较（若当前枚举到的 $0$ 是 $S_{01}$ 的第一个 $0$，则将 $^{\mathbf{Hash}}r_{0}$ 设为 $\mathbf{Hash}(p, p + len_0 - 1)$），同时将指针加上 $len_0$。遇到 $1$ 同理。

对于这样一个过程，枚举 $len_0$ 的复杂度是 $\Theta(\frac{|S_{abc}|}{cnt_0})$

考虑对于多少种情况，存在满足 $cnt_0 * len_0 + cnt_1 * len_1 = |S_{abc}|$ 的 $len_1$

由 $\mathbf{exgcd}$ 的知识，可知两组满足条件的 $\begin{cases}len_0\\len_1\end{cases}$ 之间，$len_0$ 相差 $\frac{cnt_0}{\mathbf{gcd}(cnt_0, cnt_1)}$

因此最多需要扫 
$$\frac{\Theta(\frac{|S_{abc}|}{cnt_0})}{\frac{cnt_0}{\mathbf{gcd}(cnt_0, cnt_1)}}=\Theta(\frac{\mathbf{gcd}(cnt_0, cnt_1)*|S_{abc}|}{cnt_0^2})$$
遍的 $S_{01}$，每次 $\Theta(|S_{01}|)$

总时间复杂度 
$$\Theta(\frac{\mathbf{gcd}(cnt_0, cnt_1)*|S_{abc}|*|S_{01}|}{cnt_0^2})$$

其中，  
$\max\{\mathbf{gcd}(cnt_0, cnt_1)\}≈\frac{|S_{01}|}{2}$  
$\min\{cnt_0^2\}≈\frac{|S_{01}|^2}{4}$（
 $cnt_0$ 显然可以通过倒置 $0,1$ （$0$ 变 $1$，$1$ 变 $0$）变成 $\max\{cnt_0, cnt_1\}$）

$$\therefore\Theta(\frac{\mathbf{gcd}(cnt_0, cnt_1)*|S_{abc}|*|S_{01}|}{cnt_0^2}) = \Theta(\frac{|S_{01}|*|S_{abc}|*|S_{01}|}{|S_{01}|^2})=\Theta(|S_{abc}|)$$

---

时间复杂度是优于 $\mathbf{SA}$ 的。

但由于自动溢出 $2^{32}$ 被卡了（$2^{64}$ 尚不清楚），所以需要 ``long long`` + ``% P``(P 是质数)，因此有一个较大的常数。

不过还是比 $\mathbf{SA}$ 快 ![/cy](https://cdn.luogu.com.cn/upload/pic/62225.png)![/xyx](https://cdn.luogu.com.cn/upload/pic/62230.png)

代码可以见 [gitee 仓库](https://gitee.com/hkxa/mycode/blob/master/luogu/CF1056E.cpp)


---

## 作者：include13_fAKe (赞：8)

## 前言
本人第一篇蓝题题解，也是 $2024$ 年的第一篇题解。（以前总是想写但没时间）
## 题意

给定一个 $01$ 串 $t$ 和一个字母串 $s$，求有多少对字符串 $(r_0, r_1)$ 满足 $r_0 \neq r_1$ 且将 $t$ 中的 $0$ 都换成 $r_0$，$1$ 都换成 $r_1$ 后，得到的字符串与 $s$ 相同。

$2 \leq |t| \leq 10^5$，$1 \leq |s| \leq 10^6$，$t$ 中至少存在一个 $0$ 和一个 $1$。

## 思路

暴力哈希。

直接枚举字符串 $r_0$ 和 $r_1$ 的长度，然后用**哈希以后的字符串**验证其是否正确。

## 具体代码实现

双哈希~~（在 CF 上是不是五哈希都要被卡）~~。

首先，输入两个字符串。

为了写哈希方便，**如果你是用的是 string 类型，最好在最前面加一个空格，使它的下标从 $1$ 开始**。

**记得要先取 size 后加空格。**

```cpp
	cin>>s;
	int str_s=s.size();
	s=' '+s;
```

接下来，计算**字母串**的哈希值，**可同时计算 pow 数组（这样的复杂度应该是最低的**）。**记得取模**。

紧接着，考虑计算出 $01$ 串中 $0$ 和 $1$ 的数量，用两个变量 $a_0$ 和 $a_1$ 储存。

$\text{接下来才是正事}$。

暴力枚举 $0$ 对应的字符串的长度（从 $1$ 到字母串的长度），用 $b_0$ 存储。

然后算出 $1$ 对应的字符串的长度。用 $b_1$ 存储。**如果它不是正整数，一定要舍弃。**

**但是枚举肯定是可以提前结束的**。该结束就结束。

接下来就逐位比较即可。

**注意哈希值的正确求法。**

设其起始位为 $i$，结束位为 $j$，哈希值为

$$(hash_j-hash_{i-1}\times pow_{j-i+1}\operatorname{mod}p+p)\operatorname{mod}p$$

其中 $p$ 为模数。

**第一次出现的要储存下来。**

**任何时候发现字符串（和储存的不同）有问题都可以立刻结束**，但循环到字符串最后仍没有发现问题就正确了。

**注意特判 $r_0=r_1$**。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod1=999999937;
const int mod2=998244353;
string t;
string s;
int hash1[1000*2018];
int hash2[1000*2018];
int pow1[1000*2018];
int pow2[1000*2018];
int a0,a1;//串的次数 
int b0,b1;//串的长度 
int c0,c1;//hash1
int d0,d1;//hash2
signed main(){
	cin>>t;
	cin>>s;
	int str_s=s.size();
	s=' '+s;
	pow1[0]=1;
	pow2[0]=1;
	for(int i=1;i<=str_s;i++){
		hash1[i]=hash1[i-1]*669+s[i];
		hash1[i]%=mod1;
		pow1[i]=pow1[i-1]*669%mod1;
		hash2[i]=hash2[i-1]*874+s[i];
		hash2[i]%=mod2;
		pow2[i]=pow2[i-1]*874%mod2;
	}
	
	int str_t=t.size();
	t=' '+t;
	for(int i=1;i<=str_t;i++){
		if(t[i]=='0')	a0++;
		else	a1++;
	}
	int ans=0;
	for(int i=1;i<=str_s;i++){
		b0=i;
		int c=str_s-a0*b0;
		if(c<a1)	break;
		if(c%a1==0){
			b1=c/a1;
		}
		else	continue;
//		cout<<b0<<' '<<b1<<endl;
		int now=0;
		c0=c1=d0=d1=-1;
		for(int j=1;j<=str_t;j++){
			if(t[j]=='0'){
				if(c0==-1){
					c0=(hash1[now+b0]-hash1[now]*pow1[b0]%mod1+mod1)%mod1;
					d0=(hash2[now+b0]-hash2[now]*pow2[b0]%mod2+mod2)%mod2;
//					cout<<c0<<' '<<d0<<endl;
				}
				else{
					int c2=(hash1[now+b0]-hash1[now]*pow1[b0]%mod1+mod1)%mod1;
					int d2=(hash2[now+b0]-hash2[now]*pow2[b0]%mod2+mod2)%mod2;
//					cout<<c2<<' '<<d2<<endl;
//					cout<<now<<endl;
					if(c2!=c0||d2!=d0)	break;
				}
				now+=b0;
			}
			else{
				if(c1==-1){
					c1=(hash1[now+b1]-hash1[now]*pow1[b1]%mod1+mod1)%mod1;
					d1=(hash2[now+b1]-hash2[now]*pow2[b1]%mod2+mod2)%mod2;
//					cout<<c1<<' '<<d1<<endl;
				}
				else{
					int c2=(hash1[now+b1]-hash1[now]*pow1[b1]%mod1+mod1)%mod1;
					int d2=(hash2[now+b1]-hash2[now]*pow2[b1]%mod2+mod2)%mod2;
//					cout<<c2<<' '<<d2<<endl;
//					cout<<now<<endl;
					if(c2!=c1||d2!=d1)	break;
				}
				now+=b1;
			}
//			cout<<now<<endl;
			if(c0==c1&&d0==d1)	break;
			if(now==str_s)	ans++;
		}
//		cout<<endl;
	}
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：KevinYu (赞：7)

一道很有意思的题目。     
鉴于这道题是英文题面，我们来把题面的重点翻译一下。         
```
我们有一个由0，1组成的数字串a，还有一个字符串b。
我们令a中的每一个0都对应一个串s1，令a中每一个1都对应另一个串s2，s1与s2不能完全相同。
问有多少组不同的串对(s1,s2)，使得a被s1，s2替换后后与b完全相同。
```
看到这种字符串题，无非就几个算法:AC自动机，hash，marachar...      
这一题就要用到hash         
友情提示：请不要用能被hash killer干掉的模数，CF可是一个可以互相hack的网站，这一题里面可能有一堆毒瘤数据。        
我们来过一遍算法流程。      
1.初始化:   
我们先读入串a和串b，并处理出a中'0'和'1'的数目。
```cpp
int main()
{
	scanf("%s%s",&a[0],&b[0]);
	int lena=strlen(a);
	int lenb=strlen(b);
	for(int i=0;i<lena;i++)
	{
		if(a[i]=='0')nowa++;
		else nowb++;
	}
```
2.预处理：     
然后我们开两个数组  
用```up[i]```来存储pow(base,i)       
用```hb[i]```来存储b的hash值 
```cpp
	up[0]=1;
	for(int i=1;i<=lenb;i++)up[i]=(up[i-1]*base)%mod;
	for(int i=1;i<=lenb;i++)hb[i]=(hb[i-1]*base+b[i-1]-'a'+1)%mod;
```
3.算法主要过程:       
让我们逐步分析算法主要过程:     
1.我们枚举'0'子串的长度，从i一直枚举到lenb。        
在此过程中，若子串长度与子串个数的乘积大于lenb，就直接结束算法。     
```cpp
	for(int i=1;i<=lenb;i++)
	{
		if(!(nowa*i<=lenb))break;
```
2.一些定义:
我们分别定义hs0，hs1为'0'，'1'代表的子串的hash值。      
定义p为'1'子串的长度。    
定义l，r为当前位置。     
定义flg为当前循环过程是否失败。     
```cpp
		ll hs0=0,hs1=0;
		int p=lenb-nowa*i;
		if(p%nowb!=0||p<nowb)continue;
		p/=nowb;
		int l,r=0;
		int flg=0;
```
3.判断能够匹配的状态:        
我们直接枚举每一个可能状态，找到了就打上flg   
子函数定义:
```cpp
ll f(int l,int r)
{
	ll val=(hb[r]-hb[l-1]*up[r-l+1])%mod;
	return (val+mod)%mod;
}
void judge(ll* xi,int* flg,int* klg,int* l,int *r)
{
	if(*xi==0)*xi=f(*l,*r);
	else if(*xi!=f(*l,*r)){*klg=1;*flg=1;}
}
```
判断代码:
```cpp
		for(int j=0;j<lena;j++)
		{
			int klg(0);
			l=r+1;
			if(a[j]=='0'){r+=i;judge(&hs0,&flg,&klg,&l,&r);if(klg)break;}
			if(a[j]=='1'){r+=p;judge(&hs1,&flg,&klg,&l,&r);if(klg)break;}
		}
```
4.判断a，b是否是相同的串,并更新答案:
```cpp
		if(hs0==hs1){flg=1;continue;}
		if(!flg)ans++;
	}
```
主过程代码:    
```cpp
	for(int i=1;i<=lenb;i++)
	{
		if(!(nowa*i<=lenb))break;
		ll hs0=0,hs1=0;
		int p=lenb-nowa*i;
		if(p%nowb!=0||p<nowb)continue;
		p/=nowb;
		int l,r=0;
		int flg=0;
		for(int j=0;j<lena;j++)
		{
			int klg(0);
			l=r+1;
			if(a[j]=='0'){r+=i;judge(&hs0,&flg,&klg,&l,&r);if(klg)break;}
			if(a[j]=='1'){r+=p;judge(&hs1,&flg,&klg,&l,&r);if(klg)break;}
		}
		if(hs0==hs1){flg=1;continue;}
		if(!flg)ans++;
	}
```
4.输出答案:     
```cpp
		if(hs0==hs1){flg=1;continue;}
		if(!flg)ans++;
	}
```
算法过程这样就结束了。
完整代码：         
```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<climits>
#include<ctime>
#include<algorithm>
#include<complex>
#include<iostream>
#include<map>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
#define ll long long
#define base 39
#define mod 1000000007
using namespace std;
int ans;
int nowa,nowb;
char b[1000010];
char a[100010];
ll hb[1000010];
ll up[1000010];
ll f(int l,int r)
{
	ll val=(hb[r]-hb[l-1]*up[r-l+1])%mod;
	return (val+mod)%mod;
}
void judge(ll* xi,int* flg,int* klg,int* l,int *r)
{
	if(*xi==0)*xi=f(*l,*r);
	else if(*xi!=f(*l,*r)){*klg=1;*flg=1;}
}
int main()
{
	scanf("%s%s",&a[0],&b[0]);
	int lena=strlen(a);
	int lenb=strlen(b);
	for(int i=0;i<lena;i++)
	{
		if(a[i]=='0')nowa++;
		else nowb++;
	}
	up[0]=1;
	for(int i=1;i<=lenb;i++)up[i]=(up[i-1]*base)%mod;
	for(int i=1;i<=lenb;i++)hb[i]=(hb[i-1]*base+b[i-1]-'a'+1)%mod;
	for(int i=1;i<=lenb;i++)
	{
		if(!(nowa*i<=lenb))break;
		ll hs0=0,hs1=0;
		int p=lenb-nowa*i;
		if(p%nowb!=0||p<nowb)continue;
		p/=nowb;
		int l,r=0;
		int flg=0;
		for(int j=0;j<lena;j++)
		{
			int klg(0);
			l=r+1;
			if(a[j]=='0'){r+=i;judge(&hs0,&flg,&klg,&l,&r);if(klg)break;}
			if(a[j]=='1'){r+=p;judge(&hs1,&flg,&klg,&l,&r);if(klg)break;}
		}
		if(hs0==hs1){flg=1;continue;}
		if(!flg)ans++;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：一扶苏一 (赞：5)

## 【SA】【CF1056E】 Check Transcription

### Description

给定一个 $01$ 串 $t$ 和一个字母串 $s$，求有多少对字符串 $(r_0, r_1)$ 满足将 $r_0 \neq r_1$ 且将 $t$ 中的 $0$ 都换成 $r_0$，$1$ 都换成 $r_1$ 后，得到的字符串与 $s$ 相同。

$2 \leq |t| \leq 10^5$，$1 \leq |s| \leq 10^6$，$t$ 中至少存在一个 $0$ 和一个 $1$。

### Solution

不妨设 $t_0 = 0$，否则将 $t$ 中字符取反，答案不变。

显然 $r_0$ 应该是 $s$ 的一个前缀，考虑枚举 $r_0$ 的长度 $\operatorname{len}_0$，不难发现由于 $t$ 是确定的，所以 $r_1$ 也被唯一确定了，即 $\operatorname{len}_1 = \frac{|s| - \operatorname{len_0} \times \operatorname{cnt}_0}{\operatorname{cnt}_1}$，其中 $\operatorname{cnt_i}$ 为字符 $i$ 出现的次数。

首先如果 $\operatorname{len}_1$ 不是正整数则显然该长度不合法，对于 $\operatorname{len}_1$ 是整数的情况，考虑直接暴力遍历 $t$，对于 $t$ 中每个字符 $c$ 所对应的 $s$ 的子串，都比较一下这段子串和 $t$ 中第一个等于 $c$ 的字符对应的 $s$ 的子串是否相等即可。

对于比较两个子串是否相等，可以后缀排序后预处理出 $s$ 的 $\operatorname{height}$ 数组，用 ST 即可做到 $O(1)$ 查询。

考虑时间复杂度：设 $|t| = m$，$|s| = n$。预处理 ST 的时间复杂度为 $O(n \log n)$，对于枚举长度，设 $\min(\operatorname{len}_0, \operatorname{len}_1) = k$，则一次枚举的复杂度为 $O(\frac{m}{k})$，同时注意到m所有的 $\operatorname{len_0}$ 互不相同，$\operatorname{len}_1$ 互不相同，也即每个 $k$ 都只出现 $O(1)$ 次（至多两次），而 $k_{\max} = m$，这是一个调和级数，所以这部分的时间复杂度为 $O(m \log m)$。因此总时间复杂度 $O(n \log n) - O(m \log m)$。

最后别忘了特判 $r_0 = r_1$ ，这种情况不能累加答案。

### Code

```cpp
const int maxt = 21;
const int maxn = 2000006;

void SA();
void Calc();
void Init();
void Height();

int main() {
  freopen("1.in", "r", stdin);
  Init();
  SA();
  Height();
  Calc();
  return 0;
}

int m, n;
char s[maxn], t[maxn];
void Init() {
  m = qrs(t + 1); n = qrs(s + 1);
  if (t[1] == '1') {
    for (int i = 1; i <= m; ++i) if (t[i] == '1') {
      t[i] = '0';
    } else {
      t[i] = '1';
    }
  }
}

int mp;
int sa[maxn], rnk[maxn], height[maxn], tax[maxn], tp[maxn];
void RadixSort() {
  memset(tax + 1, 0, mp * sizeof (int));
  for (int i = 1; i <= n; ++i) ++tax[rnk[i]];
  for (int i = 2; i <= mp; ++i) tax[i] += tax[i - 1];
  for (int i = n; i; --i) sa[tax[rnk[tp[i]]]--] = tp[i];
}

void SA() {
  for (int i = 1; i <= n; ++i) {
    mp = std::max(mp, rnk[i] = s[i]);
    tp[i] = i;
  }
  RadixSort();
  for (int len = 1, p = 0; (mp = p) != n; len <<= 1) {
    p = 0;
    for (int i = 1; i <= len; ++i) tp[++p] = n - len + i;
    for (int i = 1; i <= n; ++i) if (sa[i] > len) tp[++p] = sa[i] - len;
    RadixSort();
    std::swap(tp, rnk);
    rnk[sa[1]] = p = 1;
    for (int i = 2, di = i - 1; i <= n; di = i++) {
      int x = sa[i], y = sa[di];
      rnk[sa[i]] = ((tp[x] == tp[y]) && (tp[x + len] == tp[y + len])) ? p : ++p;
    }
  }
}

int ST[maxt][maxn];
void Height() {
  int p = 0;
  for (int i = 1, j = sa[rnk[i] - 1]; i <= n; j = sa[rnk[++i] - 1]) {
    if (p) --p;
    while (s[i + p] == s[j + p]) ++p;
    ST[0][rnk[i]] = height[rnk[i]] = p;
  }
  for (int i = 0, di = i + 1, len = (1 << i); i < maxt; len = 1 << (i = di++)) {
    for (int l = 1, m = l + len; m <= n; m = ++l + len) {
      ST[di][l] = std::min(ST[i][l], ST[i][m]);
    }
  }
}

int query(int x, int y) {
  if (x == y) return n;
  if (x > y) std::swap(x, y);
  int len = y - x, t = log2(len);
  return std::min(ST[t][x + 1], ST[t][y - (1 << t) + 1]);
}

int c0, c1, f1;
void Calc() {
  int ans = 0;
  for (int i = 1; i <= m; ++i) if (t[i] == '0') {
    ++c0;
  } else {
    ++c1;
    if (f1 == 0) f1 = i - 1;
  }
  for (int len = 1; len <= n; ++len) {
    bool flag = true;
    ll t0 = 1ll * c0 * len;
    if (t0 >= n) break;
    if (((n - t0) % c1) != 0) continue;
    int p1 = f1 * len + 1, len1 = (n - t0) / c1;
    for (int i = 1, p = 1; i <= n; ++p) if (t[p] == '0') {
      if (query(rnk[1], rnk[i]) < len) {
        flag = false;
        break;
      }
      i += len;
    } else {
      if (query(rnk[p1], rnk[i]) < len1) {
        flag = false;
        break;
      }
      i += len1;
    }
    if (flag) {
      if ((len != len1) || (query(rnk[1], rnk[p1]) < len)) ++ans;
    }
  }
  qw(ans, '\n');
}
```



---

## 作者：DPair (赞：3)

提供一种实现简单的 $\mathcal{O}(|s|)$ 做法（这个 $|s|$ 是翻译中那个 $10^6$ 范围的东西）。

## 思路
首先我们不难发现， $t$ 串的开头那个字符一定对应的是 $s$ 串的一个前缀。因此我们只需要枚举这个字符对应串的长度就可以唯一确定它对应的串。

然后我们注意到 $t$ 串中 $0/1$ 的出现次数我们都可以知道，我们又知道了某个字符的长度，那么另一个字符对应串的长度我们也能确定。

考虑我们扫一遍 $t$ 串，由于每一个字符对应的字符串长度我们都已知，因此若我们 $\mathcal{O}(|t|)$ 扫一遍 $t$ 串，就可以求出每一个字符在 $s$ 串中对应的 **起始位置**。

再加上我们确定的长度，每一个字符在 $s$ 中对应的串我们可以通过哈希 $\mathcal{O}(1)$ 求得，因此我们得到了一个 $\mathcal{O}(|t|)$ 判断一组长度是否合法的算法。

但是这样看起来还是 $\mathcal{O}(|s||t|)$ 的，不过注意到在 $t$ 串中，出现次数更多的那一个字符的出现次数一定 $\ge \frac{|t|}{2}$。

因此我们枚举这一个字符，显然另一个字符的长度还是可以 $\mathcal{O}(1)$ 求，而且我们枚举的上界只需要达到 $\mathcal{O}(\frac{|s|}{|t|})$。

因此最终复杂度分析出来是 $\mathcal{O}(\frac{|s|}{|t|})\times\mathcal{O}(|t|)=\mathcal{O}(|s|)$ 的。

## 代码
只放关键部分
```cpp
const int MAXN = 1e6 + 5;
char t[MAXN], s[MAXN];
int m, n;

int h[MAXN][2], b[MAXN][2];
const int MOD[2] = {114, 1919};
const int base[2] = {514, 810};

inline void init() {    
    b[0][0] = b[0][1] = 1; rep(i, 1, n) {
        b[i][0] = 1ll * b[i - 1][0] * base[0] % MOD[0];
        b[i][1] = 1ll * b[i - 1][1] * base[1] % MOD[1];
        
        h[i][0] = (1ll * h[i - 1][0] * base[0] + s[i]) % MOD[0];
        h[i][1] = (1ll * h[i - 1][1] * base[1] + s[i]) % MOD[1];
    }
}

int f[2][2], len[2];
bool vis[2];

inline void get_hash(int &x, int &y, int l, int r) {
    const int o = (r - l + 1);
    x = (((1ll * h[r][0] - 1ll * h[l - 1][0] * b[o][0]) % MOD[0]) + MOD[0]) % MOD[0];
    y = (((1ll * h[r][1] - 1ll * h[l - 1][1] * b[o][1]) % MOD[1]) + MOD[1]) % MOD[1];
}

inline int judge() {
    vis[0] = vis[1] = 0; memset(f, 0, sizeof(f));
    int it = 1; rep(i, 1, m) {
        const bool x = t[i] ^ 48; int u, v; get_hash(u, v, it, it + len[x] - 1);
        if(!vis[x]) { vis[x] = 1; f[x][0] = u; f[x][1] = v; }
        else if(u != f[x][0] || v != f[x][1]) return 0;
        it += len[x];
    }
    return !(f[0][0] == f[1][0] && f[0][1] == f[1][1]);
}

signed main() {
    read(t + 1); read(s + 1); m = strlen(t + 1); n = strlen(s + 1);
    init(); int c[2] = {0, 0}; rep(i, 1, m) ++ c[t[i] ^ 48];
    if(c[0] < c[1]) { std::swap(c[0], c[1]); rep(i, 1, m) t[i] ^= 1; }
    int ans = 0; rep(k, 1, n / c[0]) {
        len[0] = k; if((n - k * c[0]) % c[1]) continue;
        if(!(len[1] = (n - k * c[0]) / c[1])) continue;
        ans += judge();
    }
    print(ans);
}
```

---

## 作者：万弘 (赞：3)

~~这个彩笔不会证时间复杂度,看了扶苏的题解才会证.~~

考虑枚举$|r_0|=i$.先统计0的个数$cnt_0$,则$|r_1|=\frac{|s|-cnt_0\times i}{|t|-cnt_0}$

实际上知道了$|r_0|,|r_1|$就能知道$r_0,r_1$因为0对应的第一次出现的串(假设起始位置是$pos$)就是$r_0$($s[pos,pos+i-1]=r_0$),$r_1$同理.  
然后就是检查,每个0对应的串必须相等,每个1对应的串必须相等$(r_0\ne r_1)$.前者等价于每个0对应的串$=r_0$,后者等价于每个1对应的串$=r_1$．这就是一个求子串LCP的问题,SA预处理出height之后建ST表即可．

最后证一下时间复杂度,SA预处理是$\mathcal O(n\log n)\ (n=max(|s|,|t|))$,后面每次枚举要$|t|$的代价,但这样不好证,但因为有$|t|\le \frac{n}{i}$.最坏情况下是$\sum_{i=1}^n\frac{n}{i}=\mathcal O(n\log n)$
```cpp
/**********/
#define MAXN 1000001
ll sa[MAXN],rk[MAXN],tp[MAXN],c[MAXN];
char s[MAXN],t[MAXN];
void radix_sort(ll n,ll m)
{
    for(ll i=1;i<=m;++i)c[i]=0;
    for(ll i=1;i<=n;++i)++c[rk[i]];
    for(ll i=1;i<=m;++i)c[i]+=c[i-1];
    for(ll i=n;i;--i)sa[c[rk[tp[i]]]--]=tp[i];
}
void make_SA(ll n,ll m=128)
{
    for(ll i=1;i<=n;++i)rk[i]=s[i],tp[i]=i;
    radix_sort(n,m);
    for(ll k=1;k<=n;k<<=1)
    {
        ll cur=0;
        for(ll i=n-k+1;i<=n;++i)tp[++cur]=i;
        for(ll i=1;i<=n;++i)
            if(sa[i]>k)tp[++cur]=sa[i]-k;
        radix_sort(n,m);
        std::swap(rk,tp);
        cur=1,rk[sa[1]]=1;
        for(ll i=2;i<=n;++i)
        {
            if(tp[sa[i]]!=tp[sa[i-1]]||tp[sa[i]+k]!=tp[sa[i-1]+k])++cur;
            rk[sa[i]]=cur;
        }
        if(cur>=n)break;
        m=cur;
    }
}
ll height[MAXN];
void make_height(ll n)
{
    ll k=0;
    for(ll i=1;i<=n;++i)
    {
        if(k>0)--k;
        ll j=sa[rk[i]-1];
        while(s[i+k]==s[j+k])++k;
        height[rk[i]]=k;
    }
}
struct ST
{
    ll t[21][MAXN],lg[MAXN];
    void build(ll* arr,ll n)
    {
        lg[1]=0;
        for(ll i=2;i<=n;++i)lg[i]=lg[i>>1]+1;
        for(ll i=1;i<=n;++i)t[0][i]=arr[i];
        for(ll i=1;i<=lg[n];++i)
            for(ll j=1;j+(1<<i)-1<=n;++j)
                t[i][j]=min(t[i-1][j],t[i-1][j+(1<<(i-1))]);
    }
    ll Qmin(ll l,ll r)
    {
    	if(l>r)std::swap(l,r);
    	++l;
        ll k=lg[r-l];
        return min(t[k][l],t[k][r-(1<<k)+1]);
    }
}st;
int main()
{
    scanf("%s%s",t+1,s+1);
    ll lent=strlen(t+1),lens=strlen(s+1),cnt0=0;
    make_SA(lens),make_height(lens);
    st.build(height,lens);
    for(ll i=1;i<=lent;++i)cnt0+=(t[i]=='0');
    ll ans=0;
    if(cnt0==lent)
    {
    	if(lens%cnt0==0)
    	{
    		ll i=lens/cnt0,pos=i+1,flag=1;
    		for(ll j=2;j<=lent;pos+=i,++j)
    			if(st.Qmin(rk[1],rk[pos])<i)flag=0;
    		if(flag)++ans;
		}
		printf("%d",ans);
		return 0;
	}
    else if(cnt0==0)
    {
    	if(lens%(lent-cnt0)==0)
    	{
    		ll i=lens/(lent-cnt0),pos=i+1,flag=1;
    		for(ll j=2;j<=lent;pos+=i,++j)
    			if(st.Qmin(rk[1],rk[pos])<i)flag=0;
    		if(flag)++ans;
		}
		printf("%d",ans);
		return 0;
	}
    for(ll i=1;i*cnt0<=lens;++i)
    {
        if((lens-i*cnt0)%(lent-cnt0))continue;
        ll start0=0,start1=0,pos=1,flag=1;
        ll k=(lens-i*cnt0)/(lent-cnt0);
        for(ll j=1;j<=lent;++j)
        {
            if(t[j]=='0')
            {
                if(!start0)start0=pos;
                else if(st.Qmin(rk[start0],rk[pos])<i)flag=0;
                pos+=i;
            }
            else
            {
                if(!start1)start1=pos;
                else if(st.Qmin(rk[start1],rk[pos])<k)flag=0;
                if(!k)flag=0;
                pos+=k;
            }
        }
        if(flag&&(i!=k||st.Qmin(rk[start0],rk[start1])<i))++ans;
    }
    printf("%d",ans);
    return 0;
}

```

---

## 作者：This_Rrhar (赞：2)

记 01 串为 $a$，字符串为 $b$。

首先设 $a$ 中有 $sx$ 个 $0$ 和 $sy$ 个 $1$。考虑枚举 $|x|$ 和 $|y|$，此时有 $sx\times|x|+sy\times|y|=|b|$，那么只需要枚举 $|x|,|y|$ 中的一个，即可得到另一个。对于每个 $|x|$ 和 $|y|$，可以通过 $b$ 得到对应的 $x$ 和 $y$，此时再用哈希验证 $(x,y)$ 是否合法解即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

#define N 1000001

string a,b;

#define base 1301
#define MOD 998244353
ll qpow(ll x,ll y,ll p=MOD)
{
	ll s=1;
	x%=p;
	while(y)
	{
		if(y&1)(s*=x)%=p;
		(x*=x)%=p,y>>=1;
	}
	return s;
}
ll h[N];
void init()
{
	h[0]=b[0];
	for(size_t i=1;i<b.size();i++)h[i]=(h[i-1]*base+b[i])%MOD;
}
ll sub(ll l,ll r)
{
	if(l==0)return h[r];
	return (h[r]-h[l-1]*qpow(base,r-l+1)%MOD+MOD)%MOD;
}

ll sx,sy;

ll ans;

int main()
{
	ios::sync_with_stdio(false);
	cin>>a>>b,init();
	for(char c:a)sx+=(c=='0'),sy+=(c=='1');
	for(int i=1;sx*i+sy<=b.size();i++)
		if((b.size()-sx*i)%sy==0)
		{
			ll j=(b.size()-sx*i)/sy,hx=0,hy=0;
			bool f=true;
			size_t l=0,r;
			for(char c:a)
			{
				if(c=='0')
				{
					r=l+i-1;
					if(r>=b.size())
					{
						f=false;
						break;
					}
					if(!hx)hx=sub(l,r);
					else if(hx!=sub(l,r))
					{
						f=false;
						break;
					}
				}
				else
				{
					r=l+j-1;
					if(r>=b.size())
					{
						f=false;
						break;
					}
					if(!hy)hy=sub(l,r);
					else if(hy!=sub(l,r))
					{
						f=false;
						break;
					}
				}
				l=r+1;
			}
			if(hx==hy)f=false;
			ans+=f;
		}
	cout<<ans;
}
```

---

## 作者：liruixiong0101 (赞：0)

首先我们可以枚举 0 字符串的长度 和 1 字符串的长度，其实就是 $ax+by=|s|$ 的解的个数（其中 $a,b$ 分别为 $t$ 中 $0$ 的个数和 $1$ 的个数），然后用哈希暴力判断，每次判断复杂度 $O(|t|)$，解的个数最多 $O(|s|)$，那么这么做的时间复杂度就是 $O(|s||t|)$。

真的是这样的吗？

我们进一步思考，当 $|t|$ 比较小的时候肯定可以通过，当 $|t|$ 比较大的时候解的个数很少也可以通过，这让我们思考暴力的时间复杂度是不是正确的？

我们需要更精确的估计 $ax+by=|s|$ 的解的个数。首先发现 $a+b=|t|$，这说明了 $0\le a,b\le |t|$，显然我们又有 $x,y\ge 0$，那么就有 $x=\dfrac{|s|-by}{a}\le \dfrac{|s|}{a}$，同理 $y\le\dfrac{|s|}{b}$，那么解的个数最多是 $O(\min(\dfrac{|s|}{a},\dfrac{|s|}{b}))=O(\dfrac{|s|}{\max(a,b)})$，因为 $0\le a,b\le |t|$，所以有 $\dfrac{|t|}{2}\le \max(a,b)\le |t|$，那么解的个数就是 $O(\dfrac{|s|}{|t|})$ 级别的，此时总时间复杂度为 $O(\dfrac{|s|}{|t|}\cdot|t|)=O(|s|)$，复杂度正确。

代码很简单，就不给了。

本题的难点在于想到暴力复杂度正确。

---

## 作者：封禁用户 (赞：0)

题解：CF1056E Check Transcription
-----
题目大意：给定一个 $01$ 串 $t$ 和一个字母串 $s$，求有多少对字符串 $(r_0, r_1)$ 满足 $r_0 \neq r_1$ 且将 $t$ 中的 $0$ 都换成 $r_0$，$1$ 都换成 $r_1$ 后，得到的字符串与 $s$ 相同。$2 \leq |t| \leq 10^5$，$1 \leq |s| \leq 10^6$，$t$ 中至少存在一个 $0$ 和一个 $1$。注意翻译中的 $s, t$ 与英文题面中的相反。

思路：哈希。

首先，我们要看数据范围，$\left | t \right | \le10^5$，$\left | s \right | \le10^6$，暴力很好写，但是会炸，于是我们考虑一种时间复杂度为 $\mathcal O(\left|s\right|)$ 的做法。可以先枚举 01 串的长度，用字符串哈希匹配求解，将符合条件答案累加即可，此时复杂度为：

$$\mathcal O(\dfrac {\left |s\right |}{\left |t\right |}) \times \mathcal O(\left |t\right |)=\mathcal O{\left |s\right |}$$

核心代码：


```cpp
typedef long long ll;
ll query(int l,int r) { return ((hsh[r] - hsh[l - 1] * p[r - l + 1]) % mod + mod) % mod; }
void solve(){
    cin >> a >> b;
    n = a.size();
    m = b.size();
    a = ' ' + a;
    b = ' ' + b;
    p[0] = 1;
    rep1(i,1,m){
        hsh[i] = (hsh[i - 1] * base + b[i] - 'a' + 1) % mod;
        p[i] = (p[i - 1] * base) % mod;
    }
    rep1(i,1,n)
        if (a[i] == '0') cnt0++;
        else cnt1++; 
    rep1(r0,1,m){
        if (m - r0 * cnt0 < cnt1)
            break;
        if ((m - r0 * cnt0) % cnt1 > 0)
            continue;
        int r1 = (m - r0 * cnt0) / cnt1;
        int hash0 = -1;
        int hash1 = -1;
        int p = 1;
        bool flag = true;
        rep1(i,1,n){
            if (a[i] == '0'){
                int val = query(p,p + r0 - 1);
                if (hash0 == -1)hash0 = val;
                else if (hash0 != val){
                    flag = false;
                    break;
                }
                p += r0;
            }
            else{
                int val = query(p,p + r1 - 1);
                if (hash1 == -1)hash1 = val;
                else if (hash1 != val){
                    flag = false;
                    break;
                }
                p += r1;
            }
        }
        if (flag && hash0 != hash1)
            ans++;
    }
    cout << ans;
    
}
```

---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/blog/523641/CF1056E) $|$ 
[题目传送门](/problem/CF1056E) 

---
${\large\color{#00CD00}\text{前置知识}}$

众所周知，字符串哈希可以实现快速且便捷的字符串匹配。若 $h_i$ 表示 $s_{[1,i]}$ 的哈希值，则有：$h_i=h_{i-1}\times Base+s_i$（存储时常利用 `unsigned long long` 自然溢出或进行取模）。可以发现，这相当于把字符串当成一个 $Base$ 进制数，再将其转成十进制。由此不难得出，$s_{[l,r]}$ 的哈希值为 $h_r-h_{l-1}\times Base^{r-l+1}$。

而要判断两个字符串相同，只需要判断其在同一 $Base$ 值下的哈希值相同即可。

------------
${\large\color{#00CD00}\text{思路}}$

设 $c_0,c_1$ 分别为 $t$ 中 $0/1$ 的数量。显然，满足条件的 $r_0,r_1$ 首先需要满足 $|r_0|\cdot c_0+|r_1|\cdot c_1=|s|$。那么我们可以枚举所有满足条件的正整数 $|r_0|,|r_1|$，然后利用字符串哈希暴力匹配即可。

暴力匹配的算法流程如下（设当前在 $s$ 中匹配到的位置为 $p$，$r_0$ 的哈希值为 $h_0$，$r_1$ 的哈希值为 $h_1$）：
- 遍历 $t$ 中的每一个字符
- 如果当前的字符为 $0$：求出 $s_{[p,p+r_0-1]}$ 的哈希值，记为 $tmp$，然后 $p\gets p+r_0$。
  - 如果 $h_0$ 为空，则 $h_0\gets tmp$。
  - 比较 $tmp$ 与 $h_0$，如果 $tmp\ne h_0$ 则说明不合法，停止匹配。
- 如果当前的字符为 $1$：与 $0$ 的情况同理。
- 成功匹配完成后，如果 $h_0\ne h_1$（题目要求 $r_0\ne r_1$），则增加答案。

此外，本题使用 `unsigned long long` 自然溢出存储哈希值会被 hack，因此需要对 $10^9+7$ 取模。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,Base=2233,Mod=1e9+7;
int n,m,c0,c1,ans;
int h[N],b[N]={1};
char t[N],s[N];
int get_hash(int l,int r){ //求 s[l...r] 的哈希值
	return (h[r]-h[l-1]*b[r-l+1]%Mod+Mod)%Mod;
}
signed main()
{
	cin>>t+1>>s+1;
	n=strlen(t+1),m=strlen(s+1);
	for(int i=1;i<=n;i++) t[i]=='0'?c0++:c1++;
	for(int i=1;i<=m;i++)
	{
		b[i]=b[i-1]*Base%Mod;
		h[i]=(h[i-1]*Base+s[i])%Mod;
		//预处理：b[i]=Base^i, h[i]=s[1...i] 的哈希值
	}
	for(int x=1;x<m/c0;x++)
	{
		if((m-x*c0)%c1>0)continue;
		int y=(m-x*c0)/c1;
		//x=|r0|,y=|r1|
		int h0=-1,h1=-1,p=1;
		for(int i=1;i<=n;i++) //遍历 t
		{
			if(t[i]=='0'){
				int tmp=get_hash(p,p+x-1); //求出哈希值
				if(h0==-1)h0=tmp;
				else if(tmp!=h0)goto err; //不合法
				p+=x;
			}
			else{
				int tmp=get_hash(p,p+y-1);
				if(h1==-1)h1=tmp;
				else if(tmp!=h1)goto err;
				p+=y;
			}
		}
		if(h0!=h1)ans++;
		err:;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：kinglf (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1056E)
## 题目分析：
先看范围，$|t|\le 10^5$，$|s|\le 10^6$，直接暴力肯定过不了，考虑复杂度为 $O(n)$ 的算法。
## 思路讲解：
可以先枚举 01 字符串的长度，运用字符串哈希匹配求解，符合条件答案累加。
## 代码 code :
```cpp
//时间复杂度：O(n/(n/2)*n)=O(2n) 
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=1e6+10,mod=1e9+7;
char s1[N],s2[N];
ll cnt0,cnt1,i0,i1,cnt,len0,len1,res,f0,f1;
unsigned ll hsh[N],base=131,p[N],h,h0,h1;//base和mod慎重选择（#17卡unsigned long long 自动溢出） 
int main(){
	p[0]=1;
	for (ll i=1;i<=N;i++)
		p[i]=(p[i-1]*base)%mod;//base的i次方倍 
	cin>>s1+1>>s2+1;
	ll l1=strlen(s1+1);
	ll l2=strlen(s2+1);
	for (ll i=1;i<=l1;i++)
		if (s1[i]=='0') {
			cnt0++;//累计0的个数 
			if (!f0) i0=i-1,f0=1;//记录第一次出现0的位置 
		}
		else {
			cnt1++;//累计1的个数 
			if (!f1) i1=i-1,f1=1;//记录第一次出现1的位置 
		}
	cnt=max(cnt0,cnt1);//选大的枚举 
	for (ll i=1;i<=l2;i++)
		hsh[i]=(hsh[i-1]*base+s2[i]-'a'+1)%mod;//处理s数组的哈希值 
	for (ll i=1;i<=l2;i++){
		h=0;
		ll fl=0,sum=0;
		if (cnt1==cnt){
			len1=i;
			if ((l2-cnt1*i)%cnt0!=0) continue;
			len0=(l2-cnt1*i)/cnt0;
		}
		else{
			len0=i;
			if ((l2-cnt0*i)%cnt1!=0) continue;
			len1=(l2-cnt0*i)/cnt1;//计算01串分别的长度 
		}
		if (len0<0||len1<0) break;//越界退出 
		h0=(hsh[i0*len1+len0]-hsh[i0*len1]*p[len0]%mod+mod)%mod;//计算哈希值 
		h1=(hsh[i1*len0+len1]-hsh[i1*len0]*p[len1]%mod+mod)%mod;
		for (ll j=1;j<=l1;j++){//O(n)逐一匹配 
			if (s1[j]=='1') {
				h=(h*p[len1]+h1)%mod;
				if (hsh[sum+len1]!=h){
					fl=1;
					break;
				}
				sum+=len1;
			}
			else {
				h=(h*p[len0]+h0)%mod;
				if (hsh[sum+len0]!=h){
					fl=1;
					break;
				}
				sum+=len0;
			}
		}
		if (len1==0||len0==0||h0==h1||hsh[l2]!=h||fl) continue;//不符合条件即打断 
		res++;//答案++ 
	}
	printf ("%lld",res);


	return 0;
}
```


---

## 作者：CQWDX (赞：0)

关键词：字符串哈希，暴力匹配。

---

容易发现当 $|r_0|$ 与 $|r_1|$ 一定时，就可以确定 $r_0$ 与 $r_1$ 的值。

考虑枚举 $|r_0|$，$|r_1|$ 后在 $s$ 上按照 $t$ 的顺序进行匹配。

记 $|t|=n,|s|=m,|r_0|=l_0,|r_1|=l_1$，$cnt_0$ 为 $t$ 中 $0$ 的数量，$cnt_1$ 为 $t$ 中 $1$ 的数量。

当 $l_0$ 一定，且 $cnt_1\mid(m-l_0\times cnt_0)$ 时，$l_1=\frac{m-l_0\times cnt_0}{cnt_1}$。

枚举 $l_0,l_1$，对于每个 $r_0,r_1$ 进行匹配。

```cpp
for(int i = 1; i <= n; i++) cnt0 += t[i] == '0', cnt1 += t[i] == '1';
for(int len0 = 1; len0 * cnt0 < m; len0++) {
	if((m - len0 * cnt0) % cnt1 != 0) continue;
	int len1 = (m - len0 * cnt0) / cnt1;
	int res = check(len0, len1);
	ans += res;
}
```


考虑用指针法进行匹配。

将 $s$ 中的第一个 $r_0$，$r_1$ 记录下来。

对于指针 $p$，若有 $t_i=0$，则将 $[s_p,s_{p+l_0-1}]$ 与 $r_0$ 进行匹配；若 $t_i=1$，则将 $[s_p,s_{p+l_1-1}]$ 与 $r_1$ 进行匹配；同时指针跳到下一个 $r_0$ 或 $r_1$ 的位置。

注：题目要求 $r_0\neq r_1$，需要特判。

匹配时间复杂度均摊 $O(\log n)$。

```cpp
int check(int len0, int len1) {
	int now = 1, bl0 = 0, br0 = 0, bl1 = 0, br1 = 0;
	for(int i = 1; i <= n; i++) {
		if(t[i] == '0') {
			if(bl0 == 0) bl0 = now, br0 = now + len0 - 1;
			else if(!cmp(bl0, br0, now, now + len0 - 1)) return 0;
			now += len0;
		} else if(t[i] == '1') {
			if(bl1 == 0) bl1 = now, br1 = now + len1 - 1;
			else if(!cmp(bl1, br1, now, now + len1 - 1)) return 0;
			now += len1;
		}
	}
	if(bl0 != 0 && bl1 != 0 && cmp(bl0, br0, bl1, br1)) return 0;
	return 1;
}
```
但是发现若对于两个字符串暴力匹配，时间复杂度 $O(n^2)$，会超时。

可以使用哈希。

令 $H_i$ 为字符串 $s$ 的前缀哈希值。

在 $w$ 进制下，有区间哈希公式 

$$hash(l,r)=H_r-w^{r-l+1}\times H_{l-1}$$

$O(n)$ 预处理后可以 $O(1)$ 求取区间哈希值。

~~按照 Codeforces 的尿性，不建议使用单哈希。ull 自然溢出会在 #17 被卡。别问我怎么知道的。~~

```cpp
ull getHash(int op, int l, int r) {
	return ((hash[op][r] - hash[op][l - 1] * pw[op][r - l + 1] % mod) + mod) % mod;
}
bool cmp(int l1, int r1, int l2, int r2) {
	for(int i = 1; i <= SIZE; i++)
		if(getHash(i, l1, r1) != getHash(i, l2, r2))
			return 0;
	return 1;
}
```

时间复杂度近似 $O(n\log n)$。能过。

完整代码就不放了。（逃

---

