# [USACO20DEC] Bovine Genetics G

## 题目描述

Farmer John 在对他的奶牛进行基因组测序之后，他现在要进行基因组编辑了！我们知道，基因组可以用一个由 A、C、G、T 组成的字符串来表示。Farmer John 考虑的基因组的最大长度为 $10^5$。

Farmer John 从一个基因组开始，通过下列步骤对其进行编辑：

 1. 在所有连续相同字符之间的位置将当前基因组切开。
 2. 反转所有得到的子串。
 3. 按原先的顺序将反转的子串进行联结。

例如，如果 FJ 从基因组 AGGCTTT 开始，他会执行下列步骤：

 1. 在连续的 G 和 T 之间切开，得到 AG | GCT | T | T。
 2. 反转每一子串，得到 GA | TCG | T | T。
 3. 将这些子串联结起来，得到 GATCGTT。

不幸的是，在对基因组进行编辑之后，Farmer John 的计算机崩溃了，他丢失了他开始时的基因组序列。此外，编辑后的基因组的部分位置遭到了破坏，这些位置用问号代替。

给定编辑后的基因组序列，请帮助 FJ 求出可能的开始时的基因组序列的数量，对 $10^9+7$ 取模。 

## 说明/提示

### 样例 2 解释：

除了在之前说明过的 AGGCTTT 之外，还有两种可能的开始时的基因组。

`AGGATTT -> AG | GAT | T | T -> GA | TAG | T | T -> GATAGTT`

`TAGGTTT -> TAG | GT | T | T -> GAT | TG | T | T -> GATTGTT`

### 测试点性质：


 - 测试点 1-4 中，基因组的长度不超过 $10$。
 - 测试点 5-11 中，基因组的长度不超过 $10^2$。
 - 测试点 12-20 没有额外限制。

供题：Benjamin Qi 

## 样例 #1

### 输入

```
?```

### 输出

```
4```

## 样例 #2

### 输入

```
GAT?GTT```

### 输出

```
3```

# 题解

## 作者：pmt2018 (赞：19)

**Observation:** 注意到一个非常重要的事实,由于我们是将所有连续相同字符之间的位置切开,因而对于一个串,它对应的结果串是唯一的。所以对于结果串而言,一种**合法**划分即对应一种合法初始串。

那么什么样的串是合法串呢？显然的有两个条件：
1. 每一段划分中间不能有连续相同字符，不然我们一定会在那个位置将其割开。
2. 对于划分中的连续两个子串$s,t$，$s$的首字符必须等于$t$的末字符，不然我们也不会去割那个位置。

不难证明这是一个充分必要条件。

由此可以得到一个朴素的DP想法，考虑$dp[i][ch]$表示已经把前i个字符割好了，且最后一个子串的首字母为ch，转移时从大往小枚举前一个划分位置$j$，判断$s[j+1\ldots i]$有无连续相同字符即可。这个东西的复杂度是$\Theta(n^2)$的，无法接受。

考虑优化。在这种划分问题中，有一个套路是考虑i时要么加入前一个划分，要么另起一段。这道题中也是同样的道理。令$dp[i][a][b][c]$表示最后一段最后一个字母为a，首字母为b，倒数第二段为c。

这样，对于$s[i+1]$来说，若$s[i+1]!=a$，那么自然可以添加进最后一段。若$a=c$，那么最后一段就可以结束，让$s[i+1]$自成一段。

这样复杂度即为$\Theta(n)$，转移时有一个$|\Sigma|^4$级别的常数，此题$|\Sigma|$为4，所以没有问题。

### Code

```cpp
#include<bits/stdc++.h>

#define y0 pmtx
#define y1 pmtxx
#define x0 pmtxxx
#define x1 pmtxxxx
#define pb push_back
#define mp make_pair
#define fi first 
#define se second
#define DEBUG printf("Passing Line %d in function [%s].\n",__LINE__,__FUNCTION__)

using namespace std;

typedef pair<int ,int > pii;
typedef vector<int > vi;
typedef long long ll;
typedef unsigned long long ull;

namespace FastIO{
    const int SIZE=(1<<20);
    char in[SIZE],*inS=in,*inT=in+SIZE;
    inline char Getchar(){
        if(inS==inT){inT=(inS=in)+fread(in,1,SIZE,stdin);if(inS==inT)return EOF;}
        return *inS++;
    }
    char out[SIZE],*outS=out,*outT=out+SIZE;
    inline void Flush(){fwrite(out,1,outS-out,stdout);outS=out;}
    inline void Putchar(char c){*outS++=c;if(outS==outT)Flush();}
    struct NTR{~NTR(){Flush();}}ztr;
}

#ifndef LOCAL
    #define getchar FastIO::Getchar
    #define putchar FastIO::Putchar 
#endif

template<typename T> inline void read(T &x){
    x=0;int f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    x*=f;
}

template<typename T>inline void write(T x){
    if(!x)putchar('0');
    if(x<0)x=-x,putchar('-');
    static int sta[40];int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
const int maxn=200007,INF=0x3f3f3f3f;
const ll MOD=1e9+7;
const ll LINF=0x3f3f3f3f3f3f3f3fll;
const ll P=19260817;

template<typename T>inline void ckmax(T &x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T &x,T y){x=(y<x?y:x);}
template<typename T>inline T my_abs(T x){if(x<0)x=-x;return x;}
inline int mod1(int x){return x<MOD?x:x-MOD;}
inline int mod2(int x){return x<0?x+MOD:x;}
inline void add(int &x,int y){x=mod1(x+y);}
inline void sub(int &x,int y){x=mod2(x-y);}

char s[maxn];
int n;
int dp[maxn][4][4][4];
const char to[]="AGCT";
int ans=0;
int main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(s[1]=='?'||s[1]==to[j])dp[1][j][j][i]=1;
		}
	}
	for(int i=2;i<=n;i++){
		for(int a=0;a<4;a++){
			if(s[i]!='?'&&s[i]!=to[a])continue;
			for(int b=0;b<4;b++){
				for(int c=0;c<4;c++){
					for(int la=0;la<4;la++){
						if(la!=a)add(dp[i][a][b][c],dp[i-1][la][b][c]);
						if(la==c)add(dp[i][a][a][b],dp[i-1][la][b][c]);
					}
				}
			}
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			add(ans,dp[n][i][j][i]);
		}
	}
	printf("%d",ans);
    return 0;
}

//things to remember
//1.long long
//2.array length
//3.freopen
//4 boarder case
```

### update on 2021.2.3:

鉴于评论区有很多人(确信)询问$n^2$的做法，我这里简单的描述一下，转移大概就是
$$ dp[i][a]=\sum_{j< i,s[i]=b,s[j+1]=a} dp[j][b](\forall k\in [j+1,i),s[k]!=s[k+1])$$
转移时从大往小枚举k即可。



---

## 作者：IamZZ (赞：4)

**G组练习总结#12**

stO **Benq** Orz

多练练动态规划吧……

### 题目大意

Farmer John 精通百般武艺，今天，他决定展示一手基因修改！

众所周知，DNA 的碱基有 4 种，奶牛也是哺乳动物，所以她们的基因是由 `A,C,T,G` 四种大写字母组成一个的一个长度为 $n(n\leq10^5)$ 字符串。

具体而言，FJ 将会遵循以下步骤修改基因：

首先，若 $i(i<n)$ 与 $i+1$ 位的字符相同，则将把左右的两段分成不同的子串；

然后，当他把整个串分成若干个子串后，将每个子串翻转，得到最终的基因串。

现在，不幸的是，FJ 比肩上帝的操作已经崩溃了他的电脑，使他只拥有**最终的**基因串而失去了**原始的**串。

再加上结果过于优美~~显卡飘香~~，有些位置的结果不能显示，我们不知道这个位置具体是什么数，用 `?` 代替。

现在 FJ 想要知道有多少种可能的原始串，结果对 $10^9+7$ 取模。

### 解题思路

既然给到我们的是最终串，那我们不妨分析一下它的性质：

首先，假若我们钦定 $[i,j],[j+1,k]$ 是两个相邻的子串，我们必须保证 $i,k$ 两位的字符相同（`?` 视为任意）；

其次，在一个子串内不能有两个相邻的字符，不然肯定会断开！

有了这两条性质，我们不妨往动态规划方面去想。

仔细一想，我们需要记的信息并不多，只需要计倒数第二个子串的开头字符，倒数第一个子串的开头字符（新建子串时会变成倒数第二），以及最后一个字符。

因为字符集大小就只有 4，这个信息量很小了。

转移有两种，一种是跟倒数第一串断开，倒数第一变成倒数第二，新建一个子串，这时需要满足倒数第一串的最后一个和倒数第二串的第一个相同。

第二种是将新加的字符放入倒数第一串，这时需要满足新加的字符和倒数第二个字符不相同（转移时的倒数第一嘛）。

那么，动态规划的转移已经显而易见了！

设 $dp_{i,j,k,l}(j,k,l\in \{A,C,T,G\})$ 表示当前处理到第 $i$ 个字符，倒数第二串的第一个字符是 $j$，倒数第一串的第一个和最后一个字符分别是 $k,l$。

转移的时候我们找到第 $i$ 位的字符 $c$，分别处理两种转移：

如果 $c\neq l$，则这个位置可以接在上一个之后，$dp_{i,j,k,c}+dp_{i-1,j,k,l}$。

如果 $l=j$，则可以断开新的子串，$dp_{i,k,c,c}+dp_{i-1,j,k,l}$。

最后，$ans=\sum_{i\in \{A,C,T,G\}}\sum_{j\in \{A,C,T,G\}} dp_{n,i,j,i}$。

记得取模，总复杂度 $\Theta(Tn),T=256$。

完结撒花(●'◡'●)！

### 参考代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,d=1e9+7;
int n,f[N][4][4][4],m;
char s[N],b[4]={'A','C','T','G'};//处理好字符集
int main()
{
	int i,j,k,l,o;
	scanf("%s",s+1);
	n=strlen(s+1);
	for(j=0;j<4;++j)
	{
		for(k=0;k<4;++k)
		{
			if(s[1]=='?'||s[1]==b[k])
			  f[1][j][k][k]=1;
		}
	}
	for(i=2;i<=n;++i)
	{
		for(j=0;j<4;++j)//找到s[i]
		{
			if(s[i]!='?'&&s[i]!=b[j])
			  continue;
			for(k=0;k<4;++k)//倒数第二串的开头
			{
				for(l=0;l<4;++l)//倒数第一串的开头
				{
					for(o=0;o<4;++o)//上一个最后
					{
						if(j!=o)
						  f[i][k][l][j]=(f[i][k][l][j]+f[i-1][k][l][o])%d;
						if(k==o)
						  f[i][l][j][j]=(f[i][l][j][j]+f[i-1][k][l][o])%d;
					}
				}
			}
		}
	}
	for(j=0;j<4;++j)
	{
		for(k=0;k<4;++k)
		  m=(m+f[n][j][k][j])%d;//统计答案
	}
	printf("%d",m);
	return 0;
}
```

---

## 作者：DYYqwq (赞：2)

有两个挺废话的性质：

- 两个连续段之间，前面段的开头字符必然等于后面段的结尾字符。
- 一个段中必然不能出现连续相等的字符。

设 $dp_{i,a,b,c}$ 表示最后一段最后字母为 $a$，第一个字母为 $b$，倒数第二段的第一个字母为 $c$。

方程有点难以理解，画个图说明一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/xnb8t43l.png)

发现如果 $d \ne a$ 那就是可以让他们两个拼在一起，$dp_{i,a,b,c}=\sum dp_{i-1,d,b,c}$。

如果 $c=d$ 那么就是上一段完全符合要求且已经完结撒花了，于是我们让 $a$ 字符自己新开一段，$dp_{i,a,a,b}=\sum dp_{i-1,d,b,c}$。

答案就是 $\sum dp_{n,i,j,i}$。

原因见图。

![](https://cdn.luogu.com.cn/upload/image_hosting/fvelid7n.png)

于是我们就愉快的做完啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int dp[100010][4][4][4] , ans;
string dna = "AGCT" , s;
int main()
{
	cin >> s;
	s = '_' + s;
	for(int i = 0 ; i < 4 ; i ++)
		for(int j = 0 ; j < 4 ; j ++) if(s[1] == '?' || s[1] == dna[j]) dp[1][j][j][i] = 1;
	for(int i = 2 ; i < s.size() ; i ++)
	{
		for(int a = 0 ; a < 4 ; a ++)
		{
			if(s[i] != '?' && s[i] != dna[a]) continue;
			for(int b = 0 ; b < 4 ; b ++)
			{
				for(int c = 0 ; c < 4 ; c ++)
				{
					for(int d = 0 ; d < 4 ; d ++)
					{
						if(d != a) dp[i][a][b][c] += dp[i - 1][d][b][c] , dp[i][a][b][c] %= mod;
						if(c == d) dp[i][a][a][b] += dp[i - 1][d][b][c] , dp[i][a][a][b] %= mod;
					}
				}
			}
		}
	}
	for(int i = 0 ; i < 4 ; i ++) for(int j = 0 ; j < 4 ; j ++) ans += dp[s.size() - 1][i][j][i] , ans %= mod;
	printf("%d" , ans);
    return 0;
}
```

---

## 作者：FReQuenter (赞：1)

考虑 dp。

令 $f_{i,j}$ 表示当前的位置和当前段的首字母。枚举分段点 $j$，判断 $\sum^{1}_{j=i-1}s_{j+1\cdots i}$ 是否有连续字符进行转移。

考虑优化。

我们需要简化判断 $\sum^{1}_{j=i-1}s_{j+1\cdots i}$ 是否有连续字符这个部分。可以通过记录倒数第二段的首字母和当前段的末尾字母以及之前的 $f$ 数组中记录的信息得知。

那么状态定义就变成了这样：

令 $f_{i,a,b,c}$ 表示当前的位置和当前段的尾字母、首字母、上一段的首字母。

转移分两种：

```cpp
if(b==c) f[i][d][d][a]+=f[i-1][a][b][c],f[i][d][d][a]%=mod;
if(b!=d) f[i][a][d][c]+=f[i-1][a][b][c],f[i][a][d][c]%=mod;
```

再根据 $s_i$ 是否为 $?$ 进行分类。

若 $s_i$ 为 $?$，则 $d$ 为四个字母对应的任意数字。

否则 $d$ 为 $s_i$。

转移的示意图：

```
(c...)(a...b) -> (a...)(d...d) (c==b)
(c...)(a...b) -> (c...)(a...d) (b!=d)
```

注意一下初始值和统计答案时用的 dp 状态。

```cpp
#include<bits/stdc++.h>
#define int long long

#define mod 1000000007

using namespace std;
string s;
int n,f[100005][4][4][4];
int get(char c){
	if(c=='A') return 0;
	if(c=='T') return 1;
	if(c=='G') return 2;
	if(c=='C') return 3; 
}
char c[4]={'A','T','G','C'};
/*
f {i,a,b,c} ->
i=pos
a=now's last
b=now's first
c=last's first
->
(c...)(a...b)
*/
signed main(){
	cin>>s;
	n=s.length();
	s='#'+s;
	for(int a=0;a<4;a++){
		for(int b=0;b<4;b++){
			if(s[1]=='?'){
				f[1][a][a][b]=1;
			}
			else{
				int d=get(s[1]);
				if(d==a) f[1][a][a][b]=1;
			}
		}
	}
	for(int i=2;i<=n;i++){
		for(int a=0;a<4;a++){
			for(int b=0;b<4;b++){
				for(int c=0;c<4;c++){
					//(c...)(a..b)
					if(s[i]=='?'){
						for(int d=0;d<4;d++){
							if(b==c) f[i][d][d][a]+=f[i-1][a][b][c],f[i][d][d][a]%=mod;
							//(c(b,b==c)...)(a...b) -> (a...)(d...d(b->d))
							if(b!=d) f[i][a][d][c]+=f[i-1][a][b][c],f[i][a][d][c]%=mod;
							//(c...)(a...b) -> (c...)(a...d(b->d))
						}
					}
					else{
						int d=get(s[i]);
						if(b==c) f[i][d][d][a]+=f[i-1][a][b][c],f[i][d][d][a]%=mod;
						if(b!=d) f[i][a][d][c]+=f[i-1][a][b][c],f[i][a][d][c]%=mod;
					}
				} 
			} 
		}
	}
	int ans=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			ans+=f[n][i][j][j],ans%=mod;
		}
	}
	cout<<ans;
}
```

---

## 作者：daniEl_lElE (赞：1)

首先，显然每种合法划分方式对应唯一原字符串。

考虑一种划分方式是合法的条件。假设有 $m$ 段，每一段开始结束分别为 $l_i,r_i$，那么我们显然需要 $s_{l_i}=s_{r_{i+1}}$，其中 $s_i$ 表示字符串第 $i$ 位。

同时，同一段内不能有连续字符。

充分性：考虑同一段内不能有连续字符，所以原串一定不会在段中间断开。同时相邻两段首位相同，故一定会在两段中间断开。

必要性：与充分性类似，反证一下即可。

于是设计 $dp_{i,j,k,l}$ 表示 $i$ 位置，$s_{l_{x-1}}$ 是哪个字符，$s_{l_x}$ 是哪个字符，$s_i$ 是哪个字符的划分方案数。转移的时候到这一段结束位置时，首先 $s_i=s_{l_{x-1}}$，其次下一位也会被钦定好，使用一个前缀和转移即可。总复杂度 $O(nV^4)$，其中 $V$ 为字符集大小。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int dp[100005][4],pre[100005][4][4][4];
char qval(char c){
	if(c=='A') return 0;
	if(c=='C') return 1;
	if(c=='G') return 2;
	if(c=='T') return 3;
}
signed main(){
	string s; cin>>s; int n=s.size(); s=" "+s+" ";
	if(s[1]=='?'){
		for(int i=0;i<4;i++) for(int j=0;j<4;j++) pre[1][i][j][j]=1;
	}
	else{
		for(int i=0;i<4;i++) pre[1][i][qval(s[1])][qval(s[1])]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				for(int p=0;p<4;p++){
					for(int q=0;q<4;q++){
						if(qval(s[i-1])==p||s[i-1]=='?'){
							if(qval(s[i])==q||s[i]=='?'){
								if(p!=q){ 
									(pre[i][j][k][q]+=pre[i-1][j][k][p])%=mod;
								}
							}
						}
					}
				}
			}
		}
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				if(qval(s[i])==j||s[i]=='?'){
					(dp[i][k]+=pre[i][j][k][j])%=mod;
				}
			}
		}
		for(int j=0;j<4;j++){
			if(s[i+1]=='?'){
				for(int k=0;k<4;k++) (pre[i+1][j][k][k]+=dp[i][j])%=mod;
			}
			else{
				(pre[i+1][j][qval(s[i+1])][qval(s[i+1])]+=dp[i][j])%=mod;
			}
		}
	}
	int ans=0;
	for(int j=0;j<4;j++) (ans+=dp[n][j])%=mod;
	cout<<ans;
	return 0;
}
```

---

