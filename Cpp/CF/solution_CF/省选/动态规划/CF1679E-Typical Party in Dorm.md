# Typical Party in Dorm

## 题目描述

Today is a holiday in the residence hall — Oleh arrived, in honor of which the girls gave him a string. Oleh liked the gift a lot, so he immediately thought up and offered you, his best friend, the following problem.

You are given a string $ s $ of length $ n $ , which consists of the first $ 17 $ lowercase Latin letters { $ a $ , $ b $ , $ c $ , $ \ldots $ , $ p $ , $ q $ } and question marks. And $ q $ queries. Each query is defined by a set of pairwise distinct lowercase first $ 17 $ letters of the Latin alphabet, which can be used to replace the question marks in the string $ s $ .

The answer to the query is the sum of the number of distinct substrings that are palindromes over all strings that can be obtained from the original string $ s $ by replacing question marks with available characters. The answer must be calculated modulo $ 998\,244\,353 $ .

Pay attention! Two substrings are different when their start and end positions in the string are different. So, the number of different substrings that are palindromes for the string aba will be $ 4 $ : a, b, a, aba.

Consider examples of replacing question marks with letters. For example, from the string aba??ee when querying { $ a $ , $ b $ } you can get the strings ababaee or abaaaee but you cannot get the strings pizza,  abaee, abacaba, aba?fee, aba47ee, or abatree.

Recall that a palindrome is a string that reads the same from left to right as from right to left.

## 说明/提示

Consider the first example and the first query in it. We can get only one string as a result of replacing the question marks — abaaaba. It has the following palindrome substrings:

1. a — substring \[ $ 1 $ ; $ 1 $ \].
2. b — substring \[ $ 2 $ ; $ 2 $ \].
3. a — substring \[ $ 3 $ ; $ 3 $ \].
4. a — substring \[ $ 4 $ ; $ 4 $ \].
5. a — substring \[ $ 5 $ ; $ 5 $ \].
6. b — substring \[ $ 6 $ ; $ 6 $ \].
7. a — substring \[ $ 7 $ ; $ 7 $ \].
8. aa — substring \[ $ 3 $ ; $ 4 $ \].
9. aa — substring \[ $ 4 $ ; $ 5 $ \].
10. aba — substring \[ $ 1 $ ; $ 3 $ \].
11. aaa — substring \[ $ 3 $ ; $ 5 $ \].
12. aba — substring \[ $ 5 $ ; $ 7 $ \].
13. baaab — substring \[ $ 2 $ ; $ 6 $ \].
14. abaaaba — substring \[ $ 1 $ ; $ 7 $ \].

In the third request, we get 4 lines: abaaaba, abababa, abbaaba, abbbaba.

## 样例 #1

### 输入

```
7
ab??aba
8
a
b
ab
abc
abcd
abcde
abcdef
abcdefg```

### 输出

```
14
13
55
105
171
253
351
465```

## 样例 #2

### 输入

```
11
???????????
6
abcdefghijklmnopq
ecpnkhbmlidgfjao
olehfan
codef
glhf
q```

### 输出

```
900057460
712815817
839861037
756843750
70840320
66```

# 题解

## 作者：MatrixGroup (赞：4)

- 题目大意

给定一个长度为 $n$ 的字符串 $s$，字符集为 $\alpha\cup\{\texttt{?}\}$。

有 $q$ 次询问，给出一个字符集 $t$，问，将 $s$ 中的**所有** $\texttt{?}$ 替换成 $t$ 中的**任意**一个字符的所有方案，$s$ 包含的所有**可以本质相同**的回文字串的个数的和。模 $998244353$。

$n\le10^3,q\le2\times10^5,|\alpha|=17,t\subseteq\alpha$。

- 解法

既然给我们了这个字符串，那么显然是要预处理的。同时这个数据范围很像一个 $O(n^2)$。

考虑预处理每个子串的贡献。对于每一对对应的字符 $c_1,c_2$：

- 如果都是 $\texttt{?}$，贡献是乘上 $|t|$。
- 如果一个是 $\texttt{?}$（不妨是 $c_1$），贡献是乘上 $[c_2\in t]$。
- 如果都不是 $\texttt{?}$ 且相等，贡献是乘上 $1$。
- 如果都不是 $\texttt{?}$ 且不等，贡献是乘上 $0$。

然后还要乘上所有不在子串内的 $\texttt{?}$ 的贡献。

发现一段区间的贡献都可以表达成 $0$ 或 $|t|^{u}\times[v\subseteq t]$。用区间 dp 的思想预处理即可。

发现 $[v\subseteq t]$ 可以用高维前缀和做。同时发现 $|\alpha|$ 不大，可以预处理对于每个 $|t|$ 的答案。

时间复杂度是 $O(|\alpha|n^2+|\alpha|^22^{|\alpha|}+q|\alpha|)$。

（对于每个 $|t|$ 的复杂度是预处理 $O(n^2)$ 的加入和高维前缀和 $O(|\alpha|2^{|\alpha|})$，后面的是读入）

- 代码

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod1=998244353;
int n,q;
string s,t;
int mask;
ll val[133333][18];//做高维前缀和
bool zero[1005][1005];//是否为0
int cont[1005][1005];//需要包含
int pwer[1005][1005];//|t|的次方
ll pw[18][1005];
int ss[1005];
int main()
{
	ios_base::sync_with_stdio(false);
	cin>>n>>s;
	ss[0]=0;
	for(int i=1;i<=n;++i)
	{
		ss[i]=ss[i-1]+(s[i-1]=='?');//前缀和用于计算其他的问号个数
	}
	for(int i=1;i<=17;++i)
	{
		pw[i][0]=1;
		for(int j=1;j<=n;++j)
		{
			pw[i][j]=pw[i][j-1]*i%mod1;//预处理次方
		}
	}
	for(int l=1;l<=n;++l)
	for(int i=0,j=l-1;j<n;++i,++j)
	{
		if(l==1)//不要预处理 2，因为长度为0是0,0,0符合。
		{
			if(s[i]=='?')
			pwer[i][j]=1;
		}
		else
		{
			if(zero[i+1][j-1])//0->0
			{
				zero[i][j]=1;
			}
			else
			{
				if(s[i]=='?'&&s[j]=='?')
				{
					cont[i][j]=cont[i+1][j-1];
					pwer[i][j]=pwer[i+1][j-1]+1;
				}
				else if(s[i]=='?')
				{
					cont[i][j]=cont[i+1][j-1]|(1<<(s[j]-'a'));
					pwer[i][j]=pwer[i+1][j-1];
				}
				else if(s[j]=='?')
				{
					cont[i][j]=cont[i+1][j-1]|(1<<(s[i]-'a'));
					pwer[i][j]=pwer[i+1][j-1];
				}
				else if(s[i]==s[j])
				{
					cont[i][j]=cont[i+1][j-1];
					pwer[i][j]=pwer[i+1][j-1];
				}
				else
				{
					zero[i][j]=1;
				}
			}
		}
		if(!zero[i][j])
		{
			for(int k=1;k<=17;++k)//这里登记就要 O(|a|n^2)
			{
				(val[cont[i][j]][k]+=pw[k][pwer[i][j]+ss[n]-(ss[j+1]-ss[i])])%=mod1;
			}
		}
	}
	for(int i=0;i<17;++i)//高维前缀和
	{
		for(int j=0;j<(1<<17);++j)
		{
			if((j>>i)&1)
			{
				for(int k=1;k<=17;++k)
				{
					(val[j][k]+=val[j^(1<<i)][k])%=mod1;
				}
			}
		}
	}
	cin>>q;
	while(q--)
	{
		cin>>t;
		mask=0;
		for(int i=0;i<t.size();++i)
		mask|=1<<(t[i]-'a');
		cout<<val[mask][t.size()]<<endl;
	}
	return 0;
}
```

---

## 作者：Masterwei (赞：4)

挺好想的。

发现字符串长度只有 $1000$，所以我们可以枚举一个回文串的中间，从中间向两边拓展。

设 $cnt$ 表示当前所有的 `?` 个数， $S$ 表示当前至少需要的字符集。

对于一对对应的字母对，有以下三种情况：


如果两个都是问号，那么 $cnt$ 减 $1$；

如果只有一个问号，那么 $cnt$ 减 $1$，$S$ 加上两个中不是问号的字母。

如果都没有，则都不改。

如此操作，我们便可得到使得这个字串是一个回文串至少要的字母，以及剩下可以随便选的位置数。

所以，我们设 $f_s$ 表示选 $s$ 这个状态的字串数量，那么当 $S\subseteq s$ 时，$f_s+=\operatorname{popcount}^{cnt}$，其中 $\operatorname{popcount}$ 表示状态 $s$ 下 $1$ 的个数。

但是这样明显会似，高维前缀和即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=2005,mod=998244353;
int n,len;
char tmp[Maxn],a[Maxn];
int f[1<<17][20];
inline int popcount(int x){
	int res=0;
	for(int i=0;i<17;i++)res+=(x>>i)&1;
	return res;
}
int pw[20][Maxn];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	scanf("%s",tmp+1);
	int tot=0;
	pw[0][0]=1;
	for(int i=1;i<=19;i++){
		pw[i][0]=1;
		for(int j=1;j<=n;j++)pw[i][j]=pw[i][j-1]*i%mod;
	}
	for(int i=1;i<=n;i++){
		a[++len]=tmp[i];a[++len]='/';
		tot+=(tmp[i]=='?');
	}
	for(int i=1;i<=len;i++){
		int cnt=tot,s=0;
		for(int j=1;i+j-1<=len&&i-j+1>=1;j++){
			int pd=(a[i+j-1]=='?')+(a[i-j+1]=='?');
			if(a[i+j-1]!=a[i-j+1]&&!pd)break;
			if(a[i+j-1]=='/'&&a[i-j+1]=='/')continue;
			if(j==1)pd=(a[i]=='?')*114;
			if(pd==1){
				cnt--;
				if(a[i+j-1]!='?')s|=(1<<(a[i+j-1]-'a'));
				else s|=(1<<(a[i-j+1]-'a'));
			}if(pd==2)cnt--;
			for(int i=popcount(s);i<=17;i++)
				f[s][i]+=pw[i][cnt],f[s][i]%=mod;
//			for(int k=i-j+1;k<=i+j-1;k++)if(a[k]!='/')printf("%c",a[k]);
//			printf(":%d %d %d\n",s,cnt,pd);
		}
	}
	for(int j=0;j<=17;j++)
		for(int i=0;i<17;i++)
			for(int s=1;s<(1<<17);s++)
				if(s&(1<<i))f[s][j]+=f[s^(1<<i)][j],f[s][j]%=mod;
	int q=read();
	while(q--){
		scanf("%s",a+1);
		n=strlen(a+1);
		int s=0;
		for(int i=1;i<=n;i++)s|=(1<<(a[i]-'a'));
		printf("%lld\n",f[s][popcount(s)]);
	}
	return 0;
}
/*
7
ab??aba
1
ab


7
ab??aba
9
a
b
ab
abc
abcd
abcde
abcdef
abcdefg
abcdefgh
*/
```

---

## 作者：ifffer_2137 (赞：1)

### 题意
给定一个长度为 $n$，仅由前 $17$ 个英文小写字母和问号组成的字符串 $s$。多次询问，每次给出一个由前 $17$ 个英文小写字母组成的字符集 $A$，你可以将 $s$ 中的问号任意替换成 $A$ 中的字母，求所有替换方案中 $s$ 的回文子串数之和。
### 分析
计数题一般算贡献。

注意到 $O(n^2)$ 级别的枚举子串是可接受的，所以先把所有子串拿出来，看一下它能对那些字符集产生多少的贡献。由于要求是回文，所以枚举回文中心，再向两边扩展。对于当前回文中心，左右对应的两个位置有若干情况：

1. 两个都是问号。这种情况不会对获得贡献的字符集产生要求，并且会提供一个可以随意填的位置，即最终产生的贡献会乘上一个字符集大小。

2. 只有一个是问号。由于回文，所以这种情况下，这个问号的填法是确定的，于是会对获得贡献的字符集产生要求，必须要含有跟这个问号对应的字符，而对产生的贡献大小没有影响。

3. 没有问号。这种情况直接判一下两个字符是否相等即可，如果不相等就直接退出循环不用往外扩展了，如果相等就无效果。

注意在这个子串以外的部分也可能有问号，这些问号也是随便填的。

现在你预处理出所有子串产生贡献的条件和大小，再看一下怎么作用到一个字符集上。不难发现，对于一个字符集 $\text{S}$，只有它包含一个子串所要求的集合 $\text{T}_i$，才能获取贡献。具体地：
$$\text{ans}_{\text{S}}=\sum_{\text{T}_i\in\text{S}}|\text{S}|^{\text{cnt}_i}$$
其中 $\text{cnt}_i$ 表示钦定子串 $i$ 回文时，可以随意填的位置的数量，刚刚已经预处理过。

这个式子是子集向超集转移，显然可以跑 SOSDP。但是因为子集对超集的贡献与超集的大小有关，所以是无法直接高维前缀和的。既然集合大小不同无法转移，那我们不妨直接钦定被转移的集合大小，设 $\text{dp}_{i,\text{S}}$ 表示字符集 $\text{S}$ 对一个大小为 $i$ 的超集所产生的贡献，外层枚举 $i$，内层暴力 SOSDP，即可朴素转移。

最后回答询问时暴力获取一下字符集，直接输出 $\text{dp}_{|\text{S}|,\text{S}}$ 即可。时间复杂度 $O(n^2|\Sigma|+|\Sigma|^22^{|\Sigma|}+q|\Sigma|)$。
### 代码
为了不让头显得太冗长，就只给主函数了。
```cpp
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read();cin>>s;s=' '+s;
	for(int i=1;i<=n;i++) if(s[i]=='?') m++;
	for(int i=1;i<=18;i++){
		pw[i][0]=1;
		for(int j=1;j<=n;j++) pw[i][j]=pw[i][j-1]*i%mod;
	}
	for(int i=1;i<=n;i++){
		int tot=(s[i]=='?'),cnt=(s[i]=='?'),msk=0;
		for(int j=1;j<=18;j++) dp[j][msk]=(dp[j][msk]+pw[j][m])%mod;
		int l=i-1,r=i+1;
		while(l>=1&&r<=n){
			if(s[l]!='?'&&s[r]!='?'&&s[l]!=s[r]) break;
			else if(s[l]=='?'&&s[r]=='?') tot+=2,cnt++;
			else if(s[l]=='?'||s[r]=='?'){
				if(s[l]!='?') msk|=(1<<(s[l]-'a'));
				else msk|=(1<<(s[r]-'a'));
				tot++;
			}
			for(int j=1;j<=18;j++) dp[j][msk]=(dp[j][msk]+pw[j][m-tot+cnt])%mod;
			l--,r++;
		}
	}
	for(int i=1;i<n;i++){
		int tot=0,cnt=0,msk=0;
		int l=i,r=i+1;
		while(l>=1&&r<=n){
			if(s[l]!='?'&&s[r]!='?'&&s[l]!=s[r]) break;
			else if(s[l]=='?'&&s[r]=='?') tot+=2,cnt++;
			else if(s[l]=='?'||s[r]=='?'){
				if(s[l]!='?') msk|=(1<<(s[l]-'a'));
				else msk|=(1<<(s[r]-'a'));
				tot++;
			}
			for(int j=1;j<=18;j++) dp[j][msk]=(dp[j][msk]+pw[j][m-tot+cnt])%mod;
			l--,r++;
		}
	}
	for(int siz=1;siz<=18;siz++){
		for(int i=0;i<18;i++){
			for(int msk=0;msk<(1<<18)-1;msk++){
				if(msk&(1<<i)){
					dp[siz][msk]=(dp[siz][msk]+dp[siz][msk^(1<<i)])%mod;
				}
			}
		}
	}
	q=read();
	while(q--){
		string t;cin>>t;int l=t.size(),msk=0; 
		for(int i=0;i<l;i++) msk|=(1<<(t[i]-'a'));
		cout<<dp[l][msk]<<"\n";
	}
	return 0;
}
```

---

## 作者：Hanx16Kira (赞：1)

# Typical Party in Dorm

[Luogu CF1679E](https://www.luogu.com.cn/problem/CF1679E)

## Solution

注意到字符集大小 $|\Sigma|$ 是 $17$，很特殊，因此考虑预处理一个字符集所有的答案。

暴力枚举串的回文中心，这里仅讨论长度为奇数的情况，偶数同理。

不难发现，当确定了一个区间过后，字符集中需要含有的字符状态是确定的，所以只需要关心不在这个区间内的问号会对答案产生什么贡献。

设总共的问号个数为 $\operatorname{tot}$，当前的区间内的确定的问号个数为 $\operatorname{cnt}$，当前区间确定必须加入字符集的元素为 $S$，那么考虑扩展左右边界：

- 两侧均不为问号，且两个字符不同。此时直接退出即可。
- 两侧均为问号，此时只需要确定一个问号另一个问号也随之确定，因此只需要 $\operatorname{cnt}$ 加 $1$。
- 一侧为问号，一侧为字符，此时问号确定，将 $\operatorname{cnt}$ 加 $1$，并将这个字符加入到 $S$ 中。

考虑如何统计贡献。显然确定的问号不会对答案产生贡献，而未确定的问号每个都会对答案产生 $|\Sigma|$ 的贡献。发现最后答案与 $|\Sigma|$ 相关，因此设 $f(S,i)$ 表示当前确定的字符集为 $S$，最后的字符集大小为 $i$。那么每次扩展边界都会对 $f(S,k\in[1,|\Sigma|])$ 带来 $k^{\operatorname{tot}-\operatorname{cnt}}$ 的贡献。

注意到 $f(S,k)$ 会对所有 $S\subseteq T$ 的 $f(T,k)$ 产生贡献，因此最后对每个 $f(S,k)$ 做一个子集卷积即可。

时间复杂度 $\mathcal O(n^2|\Sigma|+|\Sigma|^22^{|\Sigma|})$。

```cpp
int N;
char str[_N];
mint f[_M][20];
void init() {
    int tot = 0;
    For(i, 1, N) tot += str[i] == '?';
    For(i, 1, N) {
        auto solve = [&tot](int l, int r) -> void {
            int cnt = tot, sta = 0;
            while (l >= 1 && r <= N) {
                if (str[l] != '?' && str[r] != '?' && str[l] != str[r]) break;
                if (str[l] != '?' && str[r] == '?') sta |= 1 << (str[l] - 'a');
                if (str[l] == '?' && str[r] != '?') sta |= 1 << (str[r] - 'a');
                if (l != r && (str[l] == '?' || str[r] == '?')) --cnt;
                For(j, 1, 17) f[sta][j] += mint(j).pow(cnt);
                --l, ++r;
            }
        };
        solve(i, i), solve(i, i + 1);
    }
    int lim = 1 << 17;
    For(t, 1, 17) {
        for (int i = 1; i < lim; i <<= 1)
            for (int j = 0; j < lim; j += i << 1)
                For(k, 0, i - 1) f[j+k+i][t] += f[j+k][t];
    }
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    For(i, 1, N) cin >> str[i];
    init();
    int Q; cin >> Q;
    while (Q--) {
        string s; cin >> s;
        int sta = 0;
        for (char c: s) sta |= 1 << (c - 'a');
        cout << f[sta][s.length()] << '\n';
    }
}
```

---

## 作者：Exber (赞：1)

观察到字符集很小，所以考虑预处理出每个字符集的答案，询问的时候快速回答。

设 $dp_{i,j}$ 表示字符集为 $i$（$i$ 的二进制位表示对应字符有/没有），字符集大小为 $j$ 的答案，$all$ 为整个字符串中 `?` 的个数。

这里新增一维存储字符集大小是因为转移的时候 $dp_i$ 会统计上 $j\in i$ 的 $dp_j$，而在统计答案的时候会用到字符集大小的乘方，无法化简。

不难发现，可以枚举回文中心，然后不停往两边拓展，扩展途中记录下当前子串内部的 `?` 个数 $cnt$：

- 若遇到两个不为 `?` 且不同的字符或者超出字符串边界，那么停止拓展；
- 若遇到一边为 `?` 另一边不为 `?`，那么字符集 $sta$ 加上不为 `?` 的那个字符且让 $cnt\to cnt+1$；
- 若遇到两边都为 `?`，那么让 $cnt\to cnt+1$；
- 初始子串为空串，每拓展一次，就把 $dp_{sta,j}$ 加上 $j^{all-cnt}$。

处理完所有子串之后，需要让 $dp_i$ 统计上所有 $j\in i$ 的 $dp_j$，那么仿照 [CF449D Jzzhu and Numbers](https://www.luogu.com.cn/blog/251130/cf449d-jzzhu-and-numbers-zuo-ti-ji-lu) 的思路，转移的时候先按位枚举，再枚举那一位为 $1$ 的 $i$ 来转移 $dp_i$，这样就可以避免算重。

```cpp
int n,q;
char s[S],str[S];
int dp[1<<17][25];

inline int qpow(int x,int y)
{
	int res=1;
	for(;y>0;y>>=1,x=1ll*x*x%p) res=(y&1)?1ll*res*x%p:res;
	return res;
}

inline void slove()
{
	cin>>n;
	cin>>(s+1);
	int all=0;
	for(int i=1;i<=n;i++) all+=s[i]=='?';
	for(int i=1;i<=n;i++)
	{
		int l=i+1,r=i-1;
		int sta=0,cnt=0;
		while(l>1&&r<n&&(s[l-1]==s[r+1]||s[l-1]=='?'||s[r+1]=='?'))
		{
			l--,r++;
			if(s[l]=='?'&&s[r]!='?') sta|=1<<s[r]-'a';
			if(s[l]!='?'&&s[r]=='?') sta|=1<<s[l]-'a';
			if(l!=r&&(s[l]=='?'||s[r]=='?')) cnt++;
			for(int j=1;j<=17;j++) dp[sta][j]=(dp[sta][j]+qpow(j,all-cnt))%p;
		}
		l=i+1,r=i;
		sta=0,cnt=0;
		while(l>1&&r<n&&(s[l-1]==s[r+1]||s[l-1]=='?'||s[r+1]=='?'))
		{
			l--,r++;
			if(s[l]=='?'&&s[r]!='?') sta|=1<<s[r]-'a';
			if(s[l]!='?'&&s[r]=='?') sta|=1<<s[l]-'a';
			if(s[l]=='?'||s[r]=='?') cnt++;
			for(int j=1;j<=17;j++) dp[sta][j]=(dp[sta][j]+qpow(j,all-cnt))%p;
		}
	}
	for(int j=0;j<=16;j++)
		for(int i=0;i<=(1<<17)-1;i++)
			if((i>>j)&1)
				for(int k=1;k<=17;k++) dp[i][k]=(dp[i][k]+dp[i^(1<<j)][k])%p;
	cin>>q;
	while(q-->0)
	{
		cin>>(str+1);
		int len=strlen(str+1),sta=0;
		for(int i=1;i<=len;i++) sta|=1<<str[i]-'a';
		cin<<dp[sta][len]<<endl;
	}
}
```



---

## 作者：yshpdyt (赞：0)

## 题意
给定一个长为 $n\le 1000$ 由前 $17$ 个小写字母和问号组成的字符串 $s$。

$q\le2\times10^5$ 询问，每次给定由前 $17$ 个英文小写字母组成的字符集，将 $s$ 中的问号任意替换成字符集中的字母，求所有替换方案中 $s$ 的回文子串数之和。

## Sol
记 $S$ 为询问字符集，${|S|}$ 为一次询问的字符集大小，由于 ${|S|}\le 17$ 所以可以考虑状压用二进制数。

$n$ 的范围可以直接枚举回文中心和长度计算出所有可能回文子串区间，考虑应该区间可能成为一个回文串，其需要满足对应的两个位置 $i,j$ 满足以下条件其中之一，考虑这三种情况对答案的影响：

- $s_i=s_j\neq ?$：已经确定位置无需考虑。
- $s_i\neq s_j= ?$：此时 $j$ 必须填 $s_i$ 该回文串才会有贡献，于是询问的字符集中必须有 $s_i$，记所有必须出现的字符形成的集合为 $T$。
- $s_i=s_j= ?$：保证两个位置相同的基础上可以在字符集随便选，记有 $t$ 对这样的位置。

注意到我们要求所有替换方案的回文子串，区间外的问号填法也会影响答案，记 $c$ 为区间外的问号数，则对答案的影响为：

$$[T\subseteq S]\times{|S|}^{c+t}$$

记 $f(T,x)$ 表示所有要求字符集合为 $T$，$c+t=x$ 的合法区间数，$g(S)$ 为询问集合为 $S$ 的答案。

$$g(S)=\sum_{x=0}^n {|S|}^x\sum\limits_{T\subseteq S} f(T,x)$$

直接做会超时，这个式子的瓶颈在于枚举 $x$，而对于一个 $T$ 由于不知道 $S$ 所以前面的 $|S|^x$ 无法塞到后面计算。

既然对于固定 $S$ 去枚举 $x$ 会超时，我们可以考虑对固定 $T$ 去枚举 $|S|$ 统计贡献。

改变 $f(T,x)$ 的定义为所有要求字符集合为 $T$ 的合法区间，对 $|S|=x$ 的所有 $S$ 的贡献方案，我们依次对 $|T|\le k\le |S|$，令 $f(T,k)\leftarrow k^{c+t}$，于是我们的转移式子就变成了：

$$g(S)=\sum\limits_{T\subseteq S} f(T,|S|)$$

记 $m=|S|$，枚举子集时间复杂度为 $O(mn^2+3^m+qm)$，用高维前缀和可以做到 $O(mn^2+m2^m+qm)$。


## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 140005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=998244353;
const ll inf=1e18;
const double eps=1e-6;
ll f[N][20];
ll g[N];
ll n,m;
string s;
ll fpow(ll x,ll y){
    ll res=1;
    while(y){
        if(y&1)res=res*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return res;
}
ll cnt=0;
void sol(ll l,ll r){
    ll c=cnt,t=0,T=0;
    while(l>=1&&r<=n){
        if(s[l]=='?'&&s[r]=='?')t++,c=c-2+(l==r);
        else if(s[l]=='?'&&s[r]!='?')T|=(1ll<<(s[r]-'a')),c--;
        else if(s[r]=='?'&&s[l]!='?')T|=(1ll<<(s[l]-'a')),c--;
        else if(s[l]!=s[r]) break;
        ll x=__builtin_popcount(T);
        while(x<=17){ 
            f[T][x]=(f[T][x]+fpow(x,c+t))%mod;
            x++;
        }
        l--,r++;
    }
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>s;
    s=" "+s;
    for(int i=1;i<=n;i++)cnt+=(s[i]=='?');
    for(int i=1;i<=n;i++){
        ll l=i,r=i;//奇回文串
        sol(l,r);
        l=i,r=i+1;//偶回文串
        sol(l,r);
    }
    for(ll S=0;S<(1ll<<17);S++){
        ll x=__builtin_popcount(S);

        for(ll T=S;T;T=(T-1)&S)g[S]=(g[S]+f[T][x])%mod;
        g[S]=(g[S]+f[0][x])%mod;//空集也要计算
    }
    cin>>m;
    while(m--){
        cin>>s;
        ll S=0;
        for(auto y:s)S|=(1ll<<(y-'a'));
        cout<<g[S]<<endl;
    }
    return 0;
}
```

---

## 作者：DerrickLo (赞：0)

我们考虑预处理出 $f_{i,j}$ 表示如果要使得子串 $s_i\sim s_j$ 为回文子串，整个串可以自由填的 $\texttt{?}$ 的个数，$g_{i,j}$ 表示如果要使得子串 $s_i\sim s_j$ 为回文子串，最小的字符集是什么。显然 $f_{i,j}$ 和 $g_{i,j}$ 可以由 $f_{i+1,j-1}$ 和 $g_{i+1,j-1}$ 得到。

那么对于一个字符集 $S$ 的答案就是 $\displaystyle{\sum_{g_{i,j}\in S}|S|^{f_{i,j}}}$，直接对于每个字符集大小分别做一次高维前缀和即可。

时间复杂度 $\mathcal O(2^{|\Sigma|}|\Sigma|^2+q|\Sigma|)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int n,q,m,f1[1005][1005],f2[1005][1005],g[20][1000005],sum[1005];
string s,t;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>s,s=" "+s;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(s[i]=='?');
	for(int len=1;len<=n;len++)for(int i=1;i+len-1<=n;i++){
		int j=i+len-1;
		if(s[i]!='?'&&s[j]!='?'&&s[i]!=s[j]){
			f1[i][j]=-1;
			continue;
		}
		if(f1[i+1][j-1]==-1){
			f1[i][j]=-1;
			continue;
		}
		f1[i][j]=f1[i+1][j-1];
		if(s[i]!='?'&&s[j]!='?'&&s[i]==s[j])f2[i][j]=f2[i+1][j-1];
		else if(s[i]=='?'&&s[j]!='?')f2[i][j]=f2[i+1][j-1]|(1<<(s[j]-'a'));
		else if(s[i]!='?'&&s[j]=='?')f2[i][j]=f2[i+1][j-1]|(1<<(s[i]-'a'));
		else f2[i][j]=f2[i+1][j-1],f1[i][j]++;
		for(int k=1;k<=17;k++)g[k][f2[i][j]]+=ksm(k,f1[i][j]+sum[i-1]+sum[n]-sum[j]),g[k][f2[i][j]]%=mod;
	}
	for(int k=1;k<=17;k++)for(int i=1;i<=17;i++)for(int j=0;j<(1<<17);j++)if(j&(1<<i-1))g[k][j]+=g[k][j^(1<<i-1)],g[k][j]%=mod;
	cin>>q;
	while(q--){
		cin>>t,m=t.size(),t=" "+t;
		int now=0;
		for(int i=1;i<=m;i++)now+=(1<<(t[i]-'a'));
		cout<<g[__builtin_popcount(now)][now]<<"\n";
	}
}
```

---

## 作者：happybob (赞：0)

考虑枚举所有可能成为回文段的 $[l,r]$ 以及所有关于 $mid$ 对应的数对 $(i,j)$，容易通过分类讨论求出这一对的贡献，进一步地，每一个回文段的贡献都可以转化为形如对所有 $S$ 的超集 $T$ 的一个关于 $\left| T \right|$ 的式子。先枚举回文段中点可以在 $O(n^2)$ 的复杂度内求出回文段贡献。

然后问题就简单了。考虑枚举 $\left| T \right|$，对于所有 $S$ 求出贡献后进行高维前缀和即可。总复杂度 $O(n^2+\left|\Sigma\right|^2 2^{\left|\Sigma\right|}+q)$，可以通过。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1005, M = 17;
const ll MOD = 998244353ll;

int n, q;
string s;
array<ll, 1 << M> ans;

array<vector<pair<int, int>>, 1 << M> st;

inline void add(int S, int x, int c)
{
	st[S].emplace_back(x, c);
}

inline ll qpow(ll a, ll b)
{
	ll res = 1ll, base = a;
	while (b)
	{
		if (b & 1ll) res = res * base % MOD;
		base = base * base % MOD;
		b >>= 1ll;
	}
	return res;
}

array<ll, 1 << M> val;

inline void fwt(int l, int r)
{
	if (l >= r) return;
	int mid = l + r >> 1;
	fwt(l, mid);
	fwt(mid + 1, r);
	int j = l;
	for (int i = mid + 1; i <= r; i++)
	{
		val[i] = (val[i] + val[j++]) % MOD;
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> s;
	int tw = 0;
	s = " " + s;
	for (auto &j : s) tw += (j == '?');
	for (int i = 1; i <= n; i++)
	{
		int cnt = 0;
		int S = 0;
		int j = i - 1, k = i + 1, cw = 0;
		if (s[i] == '?') add(0, 1, 1), cnt = 1, cw = 1;
		else add(0, 0, 0);
		while (j >= 1 && k <= n)
		{
			cw += (s[j] == '?') + (s[k] == '?');
			if (s[j] != s[k])
			{
				if (s[j] != '?' && s[k] != '?') break;
				else if (s[j] == '?') S |= (1 << (s[k] - 'a'));
				else S |= (1 << (s[j] - 'a'));
			}
			else
			{
				if (s[j] == '?') cnt++;
			}
			add(S, cnt, cw);
			j--, k++;
		}
	}
	for (int i = 1; i < n; i++)
	{
		int j = i, k = i + 1, S = 0, cnt = 0, cw = 0;
		while (j >= 1 && k <= n)
		{
			cw += (s[j] == '?') + (s[k] == '?');
			if (s[j] != s[k])
			{
				if (s[j] != '?' && s[k] != '?') break;
				else if (s[j] == '?') S |= (1 << (s[k] - 'a'));
				else S |= (1 << (s[j] - 'a'));
			}
			else
			{
				if (s[j] == '?') cnt++;
			}
			add(S, cnt, cw);
			j--, k++;
		}
	}
	for (int c = 1; c <= 17; c++)
	{
		for (int S = 0; S < (1 << 17); S++)
		{
			val[S] = 0;
			for (auto &j : st[S])
			{
				val[S] = (val[S] + 1ll * qpow(c, j.first) * qpow(c, tw - j.second) % MOD) % MOD;
			}
		}
		fwt(0, (1 << 17) - 1); 
		for (int S = 0; S < (1 << 17); S++)
		{
			if (__builtin_popcount(S) == c) ans[S] = val[S];
		}
	}
	cin >> q;
	while (q--)
	{
		string t;
		cin >> t;
		int st = 0;
		for (auto &j : t) st |= (1 << (j - 'a'));
		cout << ans[st] << "\n";
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

考虑枚举 $[l,r]$，计算贡献。我们可以通过枚举中间点然后往外扩展的方式得到 $[l,r]$ 这个区间产生贡献必须存在的字符集 $s$ 和可以选择的空位数量 $cnt$，那么对于 $s\subseteq S$ 的询问 $S$，这个区间的贡献就是 $|S|^{cnt}$。

考虑到 $|S|\le 17$，于是可以对于 $[l,r]$ 预处理出每一个 $|S|$ 的贡献，这个贡献就可以从 $[l,r]$ 放到对应的必须字母集合 $s$ 里。

因为 $n^2<2^{|\sum|}$，不妨预处理答案。

对于一个 $S$，贡献就是子集的贡献总和。

这样复杂度就是子集的数量，$3^{|\sum|}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1005, mod = 998244353;
int n, q, tmp, cnt, f[1 << 17][18], tot, qp[20][N], g[1 << 17], sum[1 << 17], m;
char s[N], c[N];
inline void init(){
	for(int i = 1; i <= 17; i++){
		qp[i][0] = 1ll;
		for(int j = 1; j <= n; j++) qp[i][j] = qp[i][j - 1] * i % mod;
	}
}
inline void add(int &x, int y){
	x += y;
	if(x >= mod) x -= mod;
}
signed main(){
//	freopen("data.in", "r", stdin);
	scanf("%lld%s", &n, s + 1);
	for(int i = 1; i <= n; i++){
		if(s[i] == '?') tot++;
	}
	init();
	for(int L = 1, R = 1; R <= n; (L == R ? R++ : L++)){
		tmp = 0, cnt = tot;
		for(int l = L, r = R; l >= 1 && r <= n; l--, r++){
			if(s[l] != s[r]){
				if(s[l] == '?') tmp |= 1 << s[r] - 'a', cnt--;
				else if(s[r] == '?') tmp |= 1 << s[l] - 'a', cnt--;
				else break ;
			}
			else{
				if(s[l] == '?' && l != r){
					cnt--;
				}
			}
//			printf("%lld %lld %lld %lld\n", l, r, cnt, tmp);
			for(int j = 1; j <= 17; j++){
				add(f[tmp][j], qp[j][cnt]);
			}
		}
	}
	for(int S = 1; S < 1 << 17; S++){
		sum[S] = sum[S ^ (S & -S)] + 1;
		for(int s = S; ; s = (s - 1) & S){
			add(g[S], f[s][sum[S]]);
			if(s == 0) break ;
		}
	}
	scanf("%lld", &q);
	while(q--){
		scanf("%s", c + 1);
		tmp = 0;
		m = strlen(c + 1);
		for(int i = 1; i <= m; i++){
			tmp |= 1 << c[i] - 'a';
		}
		printf("%lld\n", g[tmp]);
	}
	return 0;
}
```

---

