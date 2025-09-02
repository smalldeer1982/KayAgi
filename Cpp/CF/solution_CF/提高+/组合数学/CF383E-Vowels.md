# Vowels

## 题目描述

Iahubina is tired of so many complicated languages, so she decided to invent a new, simple language. She already made a dictionary consisting of $ n $ 3-words. A 3-word is a sequence of exactly $ 3 $ lowercase letters of the first 24 letters of the English alphabet ( $ a $ to $ x $ ). She decided that some of the letters are vowels, and all the others are consonants. The whole language is based on a simple rule: any word that contains at least one vowel is correct.

Iahubina forgot which letters are the vowels, and wants to find some possible correct sets of vowels. She asks Iahub questions. In each question, she will give Iahub a set of letters considered vowels (in this question). For each question she wants to know how many words of the dictionary are correct, considering the given set of vowels.

Iahubina wants to know the $ xor $ of the squared answers to all the possible questions. There are $ 2^{24} $ different questions, they are all subsets of the set of the first 24 letters of the English alphabet. Help Iahub find that number.

## 样例 #1

### 输入

```
5
abc
aaa
ada
bcd
def
```

### 输出

```
0
```

# 题解

## 作者：E_huan (赞：8)

### 高维前缀和（或者叫做 sosdp）
本来要求的是和元音字母集合有交集的集合个数，但是这很难求，转化成被元音字母补集包含的个数。


元音字母是 `a`-`x` 的所有子集，其补集也是。


求其所有子集的个数之和，就是高维前缀和问题。
感性理解就是 $19$ 维空间，每一位是 $1$ 的就包含是 $1$ 和是 $0$ 的（这些空间里的点就是读入进来的字符串转化成的二进制表示），二进制下是 $1$ 的位理解成这个维度坐标是 $1$，是 $0$ 的理解成坐标是 $0$。

枚举每个维度做高维前缀和，`if((1<<i)&j)`的意思可以理解成：

$1$.这一位是 $0$ 的前缀和就是从 $0$ 加到 $0$，就是自己，不用再加。

$2$.这一位是 $1$ 的就要从 $0$ 加到 $1$，也就是`dp[j]+=dp[j^(1<<i)];`
把这一位是 $0$ 的 `dp[j^(1<<i)]` 加到这一位是 $1$ 的 `dp[j]` 上。

#### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read()
{
    int res=0;
    char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) res=res*10+(ch^'0'),ch=getchar();
    return res;
}
inline int lowbit(int x){return x&(-x);}
inline int sq(int x) {return x*x;}
int n;
int dp[(1<<24)+5];
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        char a[5]; scanf("%s",a);
        int u=0;
        for(int j=0;j<=2;j++) 
            if(a[j]<='x') 
                u|=(1<<(a[j]-'a'));
        dp[u]++;
    }
    for(int i=0;i<24;i++)
        for(int j=0;j<(1<<24);j++)
            if((1<<i)&j)
                dp[j]+=dp[j^(1<<i)];
    ll ans=0;
    for(int i=0;i<(1<<24);i++) ans^=(n-dp[i])*(n-dp[i]);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Little09 (赞：8)

依次枚举每一个元音字符集。对于每个字符集，考虑到一个单词是正确的当且仅当其包含至少一个元音字母，于是考虑不正确的单词：不包含任何一个元音字母，也就是属于这个元音字母集合的补集。

于是对于每个补集，考虑有多少个单词属于它，就是不正确的单词数。这一步可以通过高维前缀和完成。

```cpp
	n=read();
	for (int i=1;i<=n;i++)
	{
		int u=0;
		for (int j=1;j<=3;j++)
		{
			char x=readchar();
			if (x>='y') continue;
			u|=(1<<(x-'a'));
		}
		dp[u]++;
	}
	for (int i=0;i<24;i++)
	{
		for (int j=0;j<(1<<24);j++)
		{
			if (j&(1<<i)) dp[j]+=dp[j^(1<<i)];
		}
	}
	for (int i=0;i<(1<<24);i++) ans=ans^((n-dp[i])*(n-dp[i]));
	cout << ans;
```


---

## 作者：chenxia25 (赞：6)

不是我说，这不是一个有手就行的高维前缀和板子题？不知为啥 2700 & 一堆复杂的还要容斥的题解？（装起来了装起来了）

考虑对于某个元音字母集合的答案是多少。考虑求反面，不包含元音字母的单词个数，这个就非常简单了。显然就是字符集合包含于当前元音字母集合的补集的单词个数。那就处理出所有单词的字符集，然后高维前缀和一下就可以了。

这样子复杂度是 $\mathrm O\!\left(2^dd\right)$ 的。以 CF 机子是可以跑过的。但是这个集合们的大小最多为 $3$，感觉一脸可以把 $d$ 去掉的样子？但是逛了一圈发现没有。

---

## 作者：米奇 (赞：5)

## 题意：
对于24个字母，选出若干字母当“元音”，一个字符串是好的，至少有一个字符是“元音”。
答案是所以情况的好字符串个数的平方的异或和。

## 做法：
最简单的想法，枚举元音的状态，计算有多少个字符串是好的。
考虑如何快速求出F[S]，表示元音状态为S，的好字符串个数。发现需要容斥，1个字符-2个字符+......。这样就能用子集DP来解决了


## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define next Next
#define gc getchar
#define int long long
const int N=(1<<24)+5;
int n,ans,F[N];
char s[15];
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}*/
inline int read()
{
    int ret=0,f=0;char c=gc();
    while(!isdigit(c)){if(c=='-')f=1;c=gc();}
    while(isdigit(c)){ret=ret*10+c-48;c=gc();}
    if(f)return -ret;return ret;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		int t=0;
		for(int i=1;i<=3;i++)
			t|=(1<<(s[i]-'a'));
		for(int i=t;i>0;i=(i-1)&t)
			if(__builtin_popcount(i)%2==1)F[i]++;
			else F[i]--;
	}
	for(int i=0;i<24;i++)
		for(int j=0;j<(1<<24);j++)
			if(j&(1<<i))F[j]+=F[j^(1<<i)];
	for(int i=0;i<(1<<24);i++)
		ans=ans^(F[i]*F[i]);
	cout<<ans;
}
```

---

## 作者：人间温柔 (赞：4)

数学里有一句话：正难则反。

当统计合法单词数量十分困难时，我们可以统计非法单词的数量。

假设辅音字母所构成的集合为 $s$，那么非法单词就等价于这个单词的所有字母都在 $s$ 内。

然后利用 $sos-dp$ 就可以解决了。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
long long ans;
int f[1<<24];

int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		char x,y,z;
		cin>>x>>y>>z;
		x-='a';
		y-='a';
		z-='a';
		int mask=(1<<x) | (1<<y) | (1<<z);
		f[mask]++;
	}
	int mask=(1<<24)-1;
	for(int i=0;i<24;i++){
		int bit=1<<i;
		for(int x=0;x<=mask;x++){
			if(x&bit){
				f[x]+=f[x-bit];
			}
		}
	}
	for(int x=0;x<=mask;x++){
		ans^=(n-f[x])*(n-f[x]);
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：喵仔牛奶 (赞：3)

平方的异或和不太能维护，考虑暴力枚举子集计算答案。

包含至少一个元音字母的单词很难统计，但是全部由辅音字母组成的单词可以统计。枚举辅音字母集，求有多少单词是它的子集。可以用[高维前缀和](https://oi-wiki.org/basic/prefix-sum/)实现。

时间复杂度 $\mathcal{O}(n+2^{|S|}\times|S|)$，$|S|$ 为字符集，本题为 $24$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 24;
int n, ans, sum[1 << N];
char ch;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i ++) {
		int res = 0;
		for (int j = 1; j <= 3; j ++)
			cin >> ch, res = res | 1 << (ch - 'a');
		sum[res] ++;
	}
	for (int i = 0; i < 24; i ++)
		for (int j = 0; j < 1 << 24; j ++)
			if (j & 1 << i) sum[j] += sum[j ^ 1 << i];
	for (int i = 0; i < 1 << 24; i ++)
		ans ^= (n - sum[i]) * (n - sum[i]);
	cout << ans << '\n';
	return 0;
}
```


---

## 作者：uibn (赞：2)

当前最劣解，写篇题解庆祝一下。（

非常复杂而且跑得特别慢的容斥，把一个单词的三个字母排序并去重，留下的字母称作第一大、第二大、第三大的字母。

有很多数组需要预处理。

动态规划，用 $ans[i]$ 表示元音集合为 $i$ 时的包含至少一个元音的单词个数，设 $k$ 为 $i$ 中最大的元音，则考虑 $ans[i]$ 由 $ans[i-2^k]$ 转移过来。此时增加的答案有三种情况：

一. 第一大字母为 $k$ ，此时第二、第三大的字母肯定不在 $i$ 中，可以直接贡献答案（预处理这样的单词数）。

二. 第二大字母为 $k$ ，此时第一大的字母要求不在 $i$ 中，可以枚举第一大的字母计算有多少个单词（预处理这样的单词数），这里时间复杂度是 $2^d * d$ ，d为元音个数。

三. 第三大字母为 $k$ ，此时需要另求一个数组 $f$ ，定义 $f[i]$ 为满足第三大字母为 元音集合 $i$ 中最大的字母，并且第一大、第二大字母不在 $i$ 中的单词数。

$i$ 中只有一个元音时，直接预处理得到，否则
设 $j$ 为 $i$ 中最小的元音， $f[i]$ 由 $f[i-2^j]$ 转移，此时减少的答案有 1. 第二大字母为 $j$ 的情况 （预处理这样的单词数），或者2. 第一大字母为 $j$ 的情况，第二大字母不在 $i$ 中。

令 $a[j][k]$ 表示第一大字母为 $j$ ，第三大字母为 $k$ 的单词个数。

对于2. $f[i]$ 减去 $a[j][k]$ ， 假设 $i$ 中最小的元音为 $j$ ，最大的元音为 $k$， 则枚举 $i$ 中其他的元音 $p$ ，$f[i]$ 再加上第一大为 $j$ ，第三大字母为 $k$ ，并且第二大字母为 $p$ 的单词个数（预处理这样的单词数）。

最后 $ans[i]$ 加上 $f[i]$ ，就求完了。

我把这些放在同一遍循环中求，cf上每一个点稳定2.4秒。

```
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<bitset>
using namespace std;
const int INF=(1<<24)-1;
int n;
int a[26][26],b[26][26],c[26],r[26],g[26][26],l[26][26][26];
int f[INF+2],ans[INF+2];
int main()
{
	scanf("%d",&n);
	char ch[5];
	int tem[5];
	for (int i=1;i<=n;i++)
	{
		scanf("%s",ch);
		tem[1]=ch[0]-'a';
		tem[2]=ch[1]-'a';
		tem[3]=ch[2]-'a';
		sort(tem+1,tem+3+1);
		if (tem[3]>23) tem[3]=tem[2];
		if (tem[2]>23) tem[3]=tem[2]=tem[1];
		r[tem[1]]++;
		if (tem[1]==tem[2]&&tem[2]==tem[3])
		{
			if (tem[1]<=23) ans[1<<tem[1]]++;
		}
		else if (tem[1]==tem[2]||tem[2]==tem[3])
		{
			g[tem[3]][tem[1]]++;
			if (tem[1]<=23) ans[1<<tem[1]]++;
			if (tem[3]<=23) ans[1<<tem[3]]++;
		}
		else
		{
			a[tem[1]][tem[3]]++;
			b[tem[2]][tem[3]]++;
			c[tem[3]]++;
			l[tem[1]][tem[2]][tem[3]]++;
			g[tem[2]][tem[1]]++;
			if (tem[1]<=23) ans[1<<tem[1]]++;
			if (tem[2]<=23) ans[1<<tem[2]]++;
			if (tem[3]<=23) ans[1<<tem[3]]++;
		}
	}
	for (int i=1;i<=INF;i++)
	{
		int cnt=0,j=0,k=0;
		for (int p=0;p<=23;p++)
		{
			if (i&(1<<p))
			{
				cnt++;
				if (cnt==1) j=p;
				k=p;
			}
		}
		if (cnt==1)
		{
			f[i]=c[j]; continue;
		}
		if (cnt==2) f[i]=f[i^(1<<j)]-a[j][k]-b[j][k];
		else
		{
			f[i]=f[i^(1<<j)]-a[j][k]-b[j][k];
			for (int p=j+1;p<=k-1;p++)
			{
				if (i&(1<<p)) f[i]+=l[j][p][k];
			}
		}
		if (cnt>=2)
		{
			ans[i]=ans[i^(1<<k)]+r[k]+f[i];
			for (int p=0;p<k;p++)
			{
				if (!(i&(1<<p)))
				{
					ans[i]+=g[k][p];
				}
			}
		}
	}
	long long ret=0ll;
	for (int i=0;i<=INF;i++) ret^=1ll*ans[i]*ans[i];
	printf("%lld",ret);
	return 0;
}
```

---

## 作者：ZhongYuLin (赞：1)

我们只在乎字符串中有哪些字符，所以先将每一个字符串压成一个数字。

考虑枚举每一个元音集合，设其为 $S$，结合高中知识，有：

$$S \cap A=\varnothing \Leftrightarrow  A\subseteq\complement_US $$

SOSdp 求出不合法的即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1<<24;
string s;
int f[N];
int ans,n;
int main(){
    ios::sync_with_stdio(cin.tie(cout.tie(0)));
    cin>>n;for(int i=1;i<=n;++i)cin>>s,
    //一个状态可能对应多个字符串，例如aab与aba都对应011，acc与caa都对应101
    ++f[(1<<s[0]-'a')|(1<<s[1]-'a')|(1<<s[2]-'a')];
    for(int i=0;i<24;++i)
        for(int j=(1<<24)-1;~j;--j)
            if(j&(1<<i))f[j]+=f[j^(1<<i)];
    for(int i=0;i<1<<24;++i)ans^=(n-f[i])*(n-f[i]);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Mooncrying (赞：1)

# CF383E Vowels 题解

### 题目大意

- 给出 $n$ 个长度为 $3$ 的单词（每个字母都为 $a$ 到 $x$ 中的任意一个），我们说该单词是正确的，当且仅当该单词中含有至少一个元音。元音可以是范围内的任意字母。

- 对于所有 $ 2 ^ {24}$ 种元音集合，求出所有情况下正确单词个数的平方的异或和。

- $1 \le n \le 10 ^{4}$。

### 题意分析

- 因为字母的数量很少，只有 $24$ 个，所有我们考虑把单词压缩成状态，用类似**状压 dp** 的方法做出这道题。

- 我们知道，每一个元音集合都对应着一个正确单词的集合。但这个正确单词的集合我们似乎不太好求。

- 数学中有一种思想叫做**正难则反**，这里我们可以借鉴该思想，把问题转化成求出每个元音集合对应的不正确的单词集合，最后用单词总个数 $n$ 减去不正确的单词个数，也能得到我们想要的答案。

- 接下来我们考虑如何求出不正确的单词集合。

	我们首先要知道，一个单词不正确，即一个单词中不含任何元音。
    
   我们用符号来表示一下：
   
   设当前枚举到的元音集合为 $A_{i}$，某一个单词中包含的字母集合为 $B_{j}$，则容易得到关系 $A_{i} \cap B_{j} = \varnothing$，由此我们可以得到以下关系式：
   
   设元音集合状态压缩之后的二进制状态为 $a_{i}$，单词状态压缩之后的二进制状态为 $b_{j}$，则有：$ a_{i} \& b_{j} = 0$。
   
   于是我们可以接着往下推。不难想到，对 $a_{i}$ 取反，得到的数一定满足上述关系式。然后我们不难发现，取反之后的数在二进制表示下，任何一位或几位的 $1$ 变成 $0$，所得出的数仍满足上述关系式。
    
    举个例子：
    
    一个数 $a$ 为 $(010010101) _ {2}$，该数取反后变为 $(101101010) _ {2}$，我们设其为 $b$，易证得 $a \& b = 0$。同样地，易证出 $(101101000) _ {2}$，$(001101010) _ {2}$，$(100001010) _ {2}$ 等数都满足 $\& a = 0$（可以在草稿纸上写写）。
    
- 这样我们实际上就找到了每个元音集合所对应的所有不正确的单词集合了。

	怎样求出该集合的元素个数呢？
    
    这里我们要用到**高维前缀和**来维护。
    
    不太明白高维前缀和的同学[戳这里](https://www.luogu.com.cn/blog/wwwjy4612code/gao-wei-qian-zhui-hu)。
    
    这玩意这么写：
    
    ```cpp
	for(int i = 0; i < 24; ++ i)
		for(int j = 0; j < M; ++ j)
			if(j & (1 << i) ) f[j] += f[j ^ (1 << i)];//高维前缀和
	```
    
    于是对于每个元音集合的二进制状态 $a_{i}$，其取反后得到的数 $b_{i}$ 所对应的 $f_{b_{i}}$ 的值就是该状态下不正确的单词数目。
    
- 接下来就简单了，该平方平方，该异或异或，按题目输出即可。

- 时间复杂度为 $O(n + 24 \cdot 2 ^ {24})$。

下面是 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M = 1 << 24;
int f[M + 10], n, ans;
char s[5];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i)
	{
			scanf("%s", s);
			int sta = 0;
			for(int j = 0; j < 3; ++ j)
			sta |= (1 << (s[j] - 'a') );
			++ f[sta];
	}
	for(int i = 0; i < 24; ++ i)
		for(int j = 0; j < M; ++ j)
			if(j & (1 << i) ) f[j] += f[j ^ (1 << i)];//高维前缀和
	for(int i = 0; i < M; ++ i)
		ans ^= (n - f[i]) * (n - f[i]);
        //这里的 f[i] 其实是每个 i 取反之后的那个状态对应的元音集合所对应的不正确的单词个数。因为每种情况都会被枚举到，因此不用取反也是可以的。
	printf("%d\n", ans);
	return 0;//高维前缀和
}
```



---

## 作者：zac2010 (赞：1)

拿到这题，看到求答案的方式：“平方的异或和”。这是就能想到可能有两种方式统计答案：
* 直接按照他所说的去算。

	算出每一种情况下的数量平方再取个异或和。
* 拆贡献

	既然是平方，就无异于点对数，故而可以两两之间统计贡献。

但是这道题拆贡献很难做（或许是没法做），故而考虑直接去算。

我们发现直接统计合法数量很难，故而我们统计不合法数量。我们发现不合法数量必须要求是当前集合补集的子集。我们采用高维前缀和求和即可。

时间复杂度 $O(2^c \times c)$，其中 $c=24$，表示字母数量。

[代码](https://codeforces.com/contest/383/submission/203856873)。

---

## 作者：Aiopr_2378 (赞：0)

solution of CF383E Vowels

## 解题思路

记一个元音字母集合为 $A$，记集合 $K=\{s|s_i\in A,i\in[0,2]\}$，其中 $s$ 为一个长为 $3$ 的字符串。换句话说，$K$ 是所有对集合 $A$ 正确的字符串组成的集合。

对于一个字符串 $s\in K$ 的条件是 $\exist s_i\in A$。这个条件不容易不重不漏地维护，考虑转化。

记集合 $L=U-K$，其中 $U$ 为全集。也就是 $L$ 是集合 $K$ 的补集。字符串 $s\in L$ 的条件是 $\forall s_i\not \in A$。这个条件比较好维护。

具体地，记 $f_C$ 为：对于元音字母集合 $A$ 的补集 $C$，字符串 $s\in L$ 的数量，集合字母定义见上。则 $f_C$ 可以使用高维前缀和维护。最后在使用 $U-C$ 得到 $A$，则元音字母集合 $A$ 的答案即为 $n-f_C$。

关于高维前缀和：令 $g_{p,i}$ 表示在前 $p$ 个二进制位上，满足 $j\equiv i\pmod {2^p}$ 的 $f_j$ 的总和。也就是前 $p$ 个二进制位相等的下标的元素值和。

则有转移如下：

$$
g_{p,j}=
\begin{cases}
g_{p-1,j} & j_{(p)}=0\\
g_{p-1,j}+g_{p-1,j-2^p} & j_{(p)}=1
\end{cases}
$$

其中 $j_{(p)}$ 表示 $j$ 的二进制第 $p$ 位。

时间复杂度 $O(p2^{p}),p=24$。

## 参考代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 16777220
#define N (1<<24)
int n,f[MAXN];
string s;
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        int p=(1<<(s[0]-'a'))|(1<<(s[1]-'a'))|(1<<(s[2]-'a'));
        f[p]++;
    }
    for(int i=0;i<24;i++){
        for(int j=0;j<N;j++){
            if((j>>i)&1) f[j]+=f[j-(1<<i)];
        }
    }
    int ans=0;
    for(int i=0;i<N;i++) ans^=(n-f[i])*(n-f[i]);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Moyou (赞：0)

# \[CF383E] Vowels 题解

## 思路

要求的这个东西一看就没什么性质，考虑枚举所有元音子集。

如果我们能够求出 $f_s$ 表示 $s$ 集合作为元音时有多少个单词至少包含一个元音。

难求，正难则反，考虑 $f_s$ 表示 $s$ 集合作为元音时有多少个单词全都由非元音字母组成，由于对称性，我们只需要求出 $s$ 集合作为非元音时有多少个单词全都由非元音字母组成，这个就是权值为 01 的子集和，SOSDP 即可。

时间复杂度：$O(2^{\Sigma}\Sigma)$。

```cpp
// Problem: Vowels
// Author: Moyou
// Copyright (c) 2024 Moyou All rights reserved.
// Date: 2024-02-04 16:29:01

#include <iostream>
#define int long long
using namespace std;
const int N = 1e4 + 10, M = 24;

int n, f[(1 << M)];
string s;

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 1, x; i <= n; i ++) {
        cin >> s, x = 0;
        for(auto c : s) x |= (1 << (c - 'a'));
        f[x] ++;
    }
    for(int j = 0; j < 24; j ++)
        for(int i = 1; i < (1 << 24); i ++)
            if(i >> j & 1) f[i] += f[i ^ (1 << j)];
    int ans = 0;
    for(int i = 0; i < (1 << 24); i ++)
        ans ^= (n - f[i]) * (n - f[i]);
    cout << ans << '\n';

    return 0;
}

```


---

## 作者：封禁用户 (赞：0)

# 思路
这道题可以依次枚举每一个元音字符集，可以直接把不合法的单词看成元音单词的补集，直接用高维前缀和维护即可，复杂度 $O(d2^d)$。

具体细节见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=(1<<24)+100;
int n,f[N];
string s;
inline int readint(){//快读
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
signed main(){
	n=readint();
	for(int i=1;i<=n;i++){
		cin>>s;
		int tmp=0;
		for(int j=0;j<=23;j++){//计算补集
			char x=j+'a';
			bool flag=true;
			for(int k=0;k<s.size();k++){
				if(x==s[k]){
					flag=false;
					break;
				}
			}
			if(flag)tmp|=(1<<j);//预处理
		}
		f[tmp]++;
	}
	for(int i=1;i<=24;i++){
		for(int j=0;j<=(1<<24)-1;j++){
			if((j>>(i-1))&1){//高维前缀和
				f[j-(1<<(i-1))]+=f[j];
			}
		} 
	}
	int ans=0;
	for(int i=0;i<(1<<24);i++){
		ans^=((n-f[i])*(n-f[i]));//求答案
	}
	cout<<ans<<endl;
	return 0; 
}
```


---

