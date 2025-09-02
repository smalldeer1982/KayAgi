# [ABC284F] ABCBAC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc284/tasks/abc284_f

長さ $ N $ の文字列 $ S $ および整数 $ i\ (0\leq\ i\leq\ N) $ に対して、$ f_i(S) $ を、

- $ S $ の先頭 $ i $ 文字
- $ S $ を反転した文字列
- $ S $ の末尾 $ N-i $ 文字

をこの順に連結した文字列と定義します。 例えば、$ S= $ `abc`、$ i=2 $ のとき、$ f_i(S)= $ `abcbac` です。

長さ $ 2N $ の文字列 $ T $ が与えられます。 $ f_i(S)=T $ を満たす長さ $ N $ の文字列 $ S $ と整数 $ i\ (0\leq\ i\leq\ N) $ の組を $ 1 $ つ見つけてください。 そのような $ S,i $ の組が存在しない場合は、それを報告してください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 10^6 $
- $ N $ は整数
- $ T $ は英小文字からなる長さ $ 2N $ の文字列

### Sample Explanation 1

問題文中に書いた通り、$ S= $ `abc`、$ i=2 $ とすると $ f_i(S)= $ `abcbac` となって $ T $ に一致するため、`abc` と $ 2 $ を出力します。

### Sample Explanation 2

$ S= $ `abab`、$ i=3 $ としても条件を満たします。

### Sample Explanation 3

$ S= $ `agc`、$ i=3 $ としても条件を満たします。

### Sample Explanation 4

条件を満たす $ S,i $ の組が存在しない場合は `-1` を出力してください。

## 样例 #1

### 输入

```
3
abcbac```

### 输出

```
abc
2```

## 样例 #2

### 输入

```
4
abababab```

### 输出

```
abab
1```

## 样例 #3

### 输入

```
3
agccga```

### 输出

```
cga
0```

## 样例 #4

### 输入

```
4
atcodeer```

### 输出

```
-1```

# 题解

## 作者：Kreado (赞：28)

[题目传送门](https://atcoder.jp/contests/abc284/tasks/abc284_f)。

#### 思路

对于一个 $f(S)$，我们可以将它化成三个部分。

也就是 $[0,i-1],[i,i+n-1],[i+n,2n]$。

我们可以不断枚举中断点 $i$，判断中间子串是否是原字符串的回文串，时间复杂度 $O(n^2)$。

我们不得不寻找一种更好的方法，对此我们可以把它切成四部分。

即 $[0,i-1],[i,n],[n+1,i+n-1],[i+n,2n]$。

仅当 $T$ 是合法的字符串，有 $i$ 满足 $[0,i-1]$ 和 $[n+1,i+n-1]$，$[i,n]$ 和 $[i+n,2n]$ 互为回文数。

为了运算方便，我们可以把 $[n+1,2n]$ 翻转过来。

显然的，$[0,n]$ 绝对是 $[n+1,2n]$ 右移复制后的子串。

我们只要找到 $[0,n]$ 在 $[n+1,2n][n+1,2n]$ 串中的位置，逆推之后，我们就能确定 $i$ 的位置，这道题就做完了。

时间复杂度 $O(n)$，代码非常简洁，当然这道题做法还有 `Z函数，KMP，字符串Hash` 等。

事实上，除了 ex 题其他题都很水。

#### Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn=3e6+7;
char s[Maxn],a[Maxn],b[Maxn]; 
ll n,t;
int main(){
	scanf("%lld",&n);cin>>s;
	for(ll i=0;i<n;++i){
		a[i]=s[i];
		b[i]=b[i+n]=s[n*2-i-1];
	}
	//cout<<s<<" "<<a<<endl;
	ll i=strstr(b,a)-b;
	if(i<0){puts("-1");return 0;}i=n-i;
	for(ll j=0;j<i;++j) printf("%c",s[j]);
	for(ll j=n+i;j<(n<<1);++j) printf("%c",s[j]);
	printf("\n%d",i);
	return 0;
}
```


---

## 作者：expnoi (赞：10)

我提供两种解法，着重讲解后者。

第一种是哈希。

我们枚举 $i$，哈希判断其是否合法即可。

这是代码：

```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=(s<<3)+(s<<1)+(c^48);
		c=getchar();
	}
	return s*w;
}
inline void print(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
		print(x/10);
	putchar(x%10+'0');
	return;
}
int h[2000010],p[2000010],H[2000010];
const int mod=1e14+7;
int n;
string s;
inline int calc1(int l,int r)
{
	return (h[r]-h[l-1]*p[r-l+1]%mod+mod)%mod;
}
inline int calc2(int l,int r)
{
	return (H[l]-H[r+1]*p[r-l+1]%mod+mod)%mod;
}
signed main()
{
	n=read();
	cin>>s;
	s=" "+s;
	p[0]=1;
	for(int i=1;i<=(n<<1);i++)
	{
		p[i]=p[i-1]*131;
		h[i]=h[i-1]*131+s[i];
		p[i]%=mod;
		h[i]%=mod;
	}
	for(int i=(n<<1);i>=0;--i)H[i]=H[i+1]*131+s[i],H[i]%=mod;
	for(int i=0;i<=n;i++){//注意从0开始
		int x=(h[i]*p[n-i]%mod+calc1(n+i+1,n*2)+mod)%mod;
		int y=calc2(i+1,i+n);
		if(x==y)
		{
			cout<<s.substr(1,i)<<s.substr(n+i+1,n-i);
			puts("");
			print(i);
			return 0;
		}
	}
	puts("-1");
}
```

后者比较巧妙，有一些巧妙的转换。

我们设输入字符串的前 $i$ 个字符为 $a$，$a$ 的倒序为 $f(a)$，后 $n-i$ 个字符为 $b$， 其倒序为 $f(b)$。

根据题目的定义，输入字符串即为 $a+f(b)+f(a)+b$。

显然 $a+f(b)=b+f(a)$。

因为字符串长度是偶数，那么我们将字符串的后半段倒序，倒序后字符串就是 $a+f(b)+f(b)+a$。

显然我们发现了美妙的性质。

我们将可能成为 $a$ 的字符串都枚举出来，因为他们两个串分别为前缀和后缀，我们可以用 $KMP$ 求出可能成为答案的公共前后缀 $a$。

不过这还没完，我们还需要判断除掉枚举出的 $a$ 以后的以折半线隔开的两个字符串是否相同，如果相同，$f(b)=f(b)$ 为对应这个 $a$ 的答案。如果没有，那么这个枚举出来的 $a$ 没有机会成为答案。

其实不用直接判断中间两个串是否相同而求答案，有两种方法，一种方法是哈希判断两个串是否相同，不过这是不完美算法，我更倾向于后者。

我们考虑再将字符串 $a+f(b)+f(b)+a$ 的两个半段分别倒序，那么就得到了    $b+f(a)+f(a)+b$。

没错，我们再用 $KMP$ 求一次公共前后缀，就可以求出可能成为答案的所有 $b$。

那么转念一想，我们两次 $KMP$ 分别求出可能成为答案的 $a$ 和 $b$，那么显然 $a$ 对应的另一个串的长度是否为 $n-lena$，我们只要判断在 $KMP$ 求出的所有可能的串中有无这个长度来对应这个 $a$ 即可。

那么可以用桶标记求出的 $a$ 和 $b$ 的长度，再循环枚举答案即可。

代码：

```cpp
#include<bits/stdc++.h>
//Orz
using namespace std;
inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=(s<<3)+(s<<1)+(c^48);
		c=getchar();
	}
	return s*w;
}
inline void print(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
		print(x/10);
	putchar(x%10+'0');
	return;
}
int n,nxt[2000010],p[2000010],cnt1[2000010],cnt2[2000010];
string s,t;
int main()
{
	n=read();
	cin>>s;
	s=" "+s;
	t=s;
  	cnt1[0]=cnt2[0]=1;
	for(int i=n+1;i<=n+(n>>1);i++)swap(s[i],s[n*3-i+1]);
	nxt[1]=0;
	int j=0;
	for(int i=2;i<=n*2;i++){
		while(j&&s[j+1]!=s[i])j=nxt[j];
		if(s[j+1]==s[i])++j;
		nxt[i]=j;
	}
	for(int i=n+1;i<=n+(n>>1);i++)swap(s[i],s[n*3-i+1]);
	for(int i=1;i<=n/2;i++)swap(s[i],s[n-i+1]);
	for(int i=n*2;i;i=nxt[i])cnt1[i]=1;
	j=0;
	memset(nxt,0,sizeof(nxt));
	for(int i=2;i<=n*2;i++){
		while(j&&s[j+1]!=s[i])j=nxt[j];
		if(s[j+1]==s[i])++j;
		nxt[i]=j;
	}
	for(int i=n*2;i;i=nxt[i])cnt2[i]=1;
	for(int i=0;i<=n;i++)//注意从0开始
	{
		if(cnt1[i]&&cnt2[n-i])
		{
			cout<<t.substr(1,i)<<t.substr(n+i+1,n-i);
			puts("");
			print(i);
			return 0;
		}
	}
	puts("-1");
}
```

---

## 作者：Pengzt (赞：8)

[ABC284F](https://www.luogu.com.cn/problem/AT_abc284_f)

这题的正解好像是 $Z$ 函数。

如果 $str = T + T$ 的话，若可以找到连续的分别长为 $n$ 的两段，且这两段可通过 $1$ 次翻转变为相同的字符串，那么便一定有解，否则无解。

暴力判断是 $\mathcal{O}(n)$ 的，时间复杂度直接上天。

可以用哈希 $\mathcal{O}(1)$ 地判断出两个字符串是否相等。

但这题卡了自然溢出的哈希，所以要自己设定一个模数。

我用的是双哈希。

时间复杂度：$\mathcal{O}(n)$

[评测记录](https://atcoder.jp/contests/abc284/submissions/37866284)

---

## 作者：_Imaginary_ (赞：5)

# 使用 KMP

注意不是 Z 函数，是普通的 KMP。

大部分的做法都是字符串哈希，也有部分使用 Z 函数，但是我不知为什么 wa 个不停。于是搬用了在比赛时想了一半的 KMP 做法。

## Solution

在本篇文章中，大小写字母不区分，只是为了更明显地表示字母的对应关系。

我们给定了一个串 $S=\texttt{abcde}$，以及它经过处理后的一个串 $T=\texttt{abcEDCBAde}$，你需要通过 $T$ 还原出 $S$。

直接说思路吧，我们把前 $n$ 个字符和后 $n$ 个字符断开，分别存到两个串中，再把后面半段串翻转一下。

$$
A=\texttt{abcED}\\
B=\texttt{edABC}
$$

这里 $B$ 是由 $\texttt{CBAde}$ 翻转得到的。

我们发现，$A$ 的一个前缀就是 $B$ 的一个后缀， $B$ 的一个前缀也是 $A$ 的一个后缀。

这样我们就可以联想到 KMP。

具体的做法是，把 $B$ 延长一倍，变成：

$$
A=\color{red}\texttt{abcED}\\
\color{black}B=\texttt{ed}\color{red}\texttt{ABCed}\color{black}\texttt{ABC}
$$

这不就是字符串匹配？

（具体为什么这样匹配后就能得到 $S$，读者自证不难）

我们基本上结束了，最后还有一点。如第二个样例：

```
4
aBABAbab
```

大写的部分表示 $S$ 被断开的位置。

这个时候，同样套用之前的方法。

$$
A=\texttt{aBAB}\\
B=\texttt{babAbabA}
$$

我们就可以发现和 $\texttt{aBAB}$ 匹配的是 $\texttt{Abab}$，而不是 $\texttt{abAb}$。

因此，我们要求的就是**最靠后的成功匹配的串**，即 $\texttt{Abab}$。

接下来，求出来了这个，怎么求答案呢？

以最开始的：

$$
A=\color{red}\texttt{abcED}\\
\color{black}B=\texttt{ed}\color{red}\texttt{ABCed}\color{black}\texttt{ABC}
$$

为例。在原串中，我们要求的是 $\texttt{c}$ 的位置，而这个位置是小写字母 $\texttt{c}$ 和大写字母 $\texttt{E}$ 的交叉点。

对于大写字母，我们在 $B$ 中匹配出了 $\texttt{ABCed}$ 后，就知道了前面 $\texttt{ed}$ 的位置，从而知道了原来的 $S$ 串被分成的一部分是 $\texttt{de}$，那另一部分就是 $\texttt{abc}$ 了，我们也就求出原串断开的位置是 $\texttt{c}$。具体可以自行手算几个例子试一试。

还有一些小细节，上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2000005;
int n;
char t[N],s[N];
int nxt[N];
void get_nxt(char *b,int m)
{
	nxt[0]=0;
	int pl=0;
	int i=1;
	while(i<m)
	{
		if(b[pl+1]==b[i+1])
		{
			pl++;
			i++;
			nxt[i]=pl;
		}
		else
		{
			if(pl==0) 
			{
				i++;
				nxt[i]=0;
			}
			else pl=nxt[pl];
		}
	}
}
int kmp(char *a,int n,char *b,int m)
{
	int ret=-1;
	int i=0,j=0;
	while(i<n)
	{
		if(a[i+1]==b[j+1])
		{
			i++;
			j++;
		}
		else if(j>0) j=nxt[j];
		else i++;
		if(j==m)//已匹配到一个，但是要找最靠后的
		{
			j=nxt[j];
			ret=i;
		}
	}
	return ret;
}
int main()
{
	scanf("%d",&n);
	scanf("%s",t+1);
	for(int i=2*n;i>=n+1;i--) s[2*n-i+1]=t[i];
	for(int i=1;i<=n;i++) s[i+n]=s[i];
	get_nxt(t,n);
	int tmp=kmp(s,2*n,t,n);
	if(tmp==-1)
	{
		printf("-1");
		return 0;
	}
	
	for(int i=tmp+1;i<=2*n;i++) printf("%c",s[i]);
	for(int i=tmp;i>=n+1;i--) printf("%c",s[i]);
	printf("\n%d",2*n-tmp);
	return 0;
}
```

### 后记

一千五左右的难度差不多是绿题，KMP 板子是黄的，所以难度应该差不多。（Z 函数是紫板子呢）

在调出来 hash 后，我稍微做了个比对。

```
hash: 1016 Byte, 96 ms, 68272 KB
KMP:  1028 Byte, 41 ms, 11648 KB
```

效率没有本质的差别。

---

## 作者：yeshubo_qwq (赞：3)

## Solution

不难想到枚举 $i$，然后判断。

将原来的字符串分成四份：$\left[1,i\right],\left[i+1,n\right],\left[n+1,n+i\right],\left[i+n+1,n+n\right]$。

$\left[1,i\right]$ 对应 $\left[n+1,n+i\right]$，$\left[i+1,n\right]$ 对应 $\left[i+n+1,n+n\right]$，判断两者是否都相等即可。

判断可以使用哈希，但注意中间插入的原串经过反转，所以要正、反各做一遍哈希，$\left[n+1,n+i\right]$ 和 $\left[i+1,n\right]$ 用反着做的值，另外两者用正着做的值。

別忘记输出无解，记得**数组要开双倍空间**。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=99989397,base=233;
int B[N<<1],res[N<<1],B1[N<<1],res1[N<<1],n,m,i;
string S;
void pre(){
	B[0]=1,B1[n+1]=1;
	for (int i=1;i<=m;i++) res[i]=(res[i-1]*base%mod+S[i])%mod,B[i]=(B[i-1]*base)%mod;
	for (int i=m;i>=1;i--) res1[i]=(res1[i+1]*base%mod+S[i])%mod,B1[i]=(B1[i+1]*base)%mod;
}
int query(int l,int r){return (l>r?0:(res[r]-res[l-1]*B[r-l+1]%mod+mod)%mod);}
int query1(int l,int r){return (l>r?0:(res1[l]-res1[r+1]*B[r-l+1]%mod+mod)%mod);}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>S,m=(n<<1),S=" "+S,pre();
	for (i=0;i<=n;i++)
		if (query(1,i)==query1(n+1,n+i) && query1(i+1,n)==query(i+n+1,n*2))
			return cout<<S.substr(1,i)<<S.substr(i+n+1,n-i)<<'\n'<<i,0;
	return cout<<-1,0;
}
```


---

## 作者：Disjoint_cat (赞：2)

题目传送门：[LG](https://www.luogu.com.cn/problem/AT_abc284_f)，[AT](https://atcoder.jp/contests/abc284/tasks/abc284_f)

## ABC284F ABCBAC

### 前言

写篇题解真不容易啊！

本人蒟蒻，赛时想了 1h 才 AC。

看了看题解区，没人用 KMP 做的，来写一发 KMP 的题解。

**声明：对于字符串 $S$，如果 $j<i$，令 $S_{i\dots j}$ 为空串。**

### 题意

- 对于长为 $n$ 的字符串 $S$ 与 $i(0\le i\le n)$，定义 $f(S,i)$ 为：

$$S_{1\dots i}+\operatorname{reverse}(S)+S_{i+1\dots n}$$

- 现在给出长度为 $2n$ 字符串 $T$，你需要找到一个长为 $n$ 的字符串 $S$ 与 $i(0\le i\le n)$，满足 $f(S,i)=T$。多解输出任意，无解输出 $-1$。

- $1\le n\le10^6$，$T$ 只包含小写字母。

### Solution

光用文字说很抽象，这里会用图像辅助理解。

假设我们已经找到了 $S$ 与 $i$。

对于字符串 $X$，如果 $X_i=S_j$，则令 $x(i)=j$。然后可以将其连成（可能不连续）线段。（这里讲的不清楚，可以根据下文意会）

首先，我们把 $S$ 表示成一条直线。

![](https://cdn.luogu.com.cn/upload/image_hosting/2dutrveb.png)

很容易理解，因为根据定义，$S_i=S_i$，恒成立。

接下来是 $T$ 的：

![](https://cdn.luogu.com.cn/upload/image_hosting/mi99h4ou.png)

可以发现，中间几乎没有确定的东西，除了……中间的 $n$。

这个 $n$ 是怎么来的呢？可以证明，在 $T_{1\dots n}$ 中，$S_1\sim S_n$ 各出现了一次，所以成立。

那构造一个新串试试？

考虑将 $T$ 的后半部分反转。令 $T'=T_{1\dots n}+\operatorname{reverse}(T_{n+1\dots2n})$，再画出 $T'$ 的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/yz7tkslk.png)

诶？发现 $T'_{1\dots i}=T'_{2n-i+1\dots 2n}$！

于是可以对 $T'$ 做 KMP，取 $i=nxt_{2n}$……

等等，还有个问题！这里我们完全假设了已经找到了 $S$，可它不一定真的满足条件！

这里我们只保证了 $T'_{1\dots i}=T'_{2n-i+1\dots 2n}$，却没有保证中间部分也相同。

![](https://cdn.luogu.com.cn/upload/image_hosting/x7h7qu3z.png)

但是我们还是可以得到一个算法：

令 $i=nxt_{2n}$，检查中间部分是否相等。相等则输出，如不相等，再令 $i=nxt_i$。如果 $i=0$，则无解。

但是“检查中间部分是否相等”还是只能暴力比较（如果直接 KMP，最坏要做 $O(n)$ 次，还不如暴力），最坏时间复杂度还是 $O(n^2)$，还是会 [TLE](https://atcoder.jp/contests/abc284/submissions/37838140)。（~~但是就 T 了一个点，或许可以卡常过去~~）

怎么办？能不能只做一次 KMP，就能完成快速判断？

$T'$ 是 $T$ **后半部分**反转，那如果让 $T$ 的**前半部分**翻转呢？

令 $T''=\operatorname{reverse}(T_{1\dots n})+T_{i+1\dots 2n}$：

![](https://cdn.luogu.com.cn/upload/image_hosting/9rafgicb.png)

哇！（~~你不觉得吗~~）做完了！！！

对 $T''$ 再做一次 KMP，可以得到让 $T''_{1\dots n-i}=T''_{n+i+1\dots2n}$ 的所有的 $i$。

综上，我们得到了如下算法：

- 构造 $T'$ 和 $T''$；

- 对 $T'$ 和 $T''$ 各做一次 KMP，结果分别为 $nxt1[]$ 和 $nxt2[]$；

- 令 $i=nxt1_{2n}$。记录 $cnt1_{i}=1$，然后再令 $i=nxt1_i$，直到 $i=0$（**注意 $i=0$ 时也要记录**）；

- 对 $nxt2$ 做类似的操作，结果存在 $cnt2[]$ 中；

- 遍历所有的 $0\le i\le n$，如果 $cnt1_i$ 与 $cnt2_{n-i}$ 均为 $1$，则这个 $i$ 是一个解，输出；

- 遍历完后也未找到解，则无解。~~这不是废话吗~~

时间复杂度：$O(n)$。

### [Code](https://atcoder.jp/contests/abc284/submissions/37843272)

```cpp
#include<bits/stdc++.h>
#define ll long long
#define YJL_DRC_LCH_WJY_WQY_ZZH using
#define AK namespace
#define IOI std
YJL_DRC_LCH_WJY_WQY_ZZH AK IOI;
void Init()
{

}
const int N=1000005;
int nxt[N<<1],nxt2[N<<1],n,t;
string s,s1="$",s2="$";
bool cnt[N][2];
void Solve()
{
	cin>>n>>s;s="$"+s;
	for(int i=1;i<=n;i++)s1+=s[i];
	for(int i=n<<1;i>n;i--)s1+=s[i];
	for(int i=2;i<=n<<1;i++)
	{
		while(t&&s1[i]!=s1[t+1])t=nxt[t];
		if(s1[i]==s1[t+1])t++;
		nxt[i]=t;
	}
	for(int i=n;i;i--)s2+=s[i];
	for(int i=n+1;i<=n<<1;i++)s2+=s[i];
	t=0;
	for(int i=2;i<=n<<1;i++)
	{
		while(t&&s2[i]!=s2[t+1])t=nxt2[t];
		if(s2[i]==s2[t+1])t++;
		nxt2[i]=t;
	}
	int v=nxt[n<<1];
	while(v)
	{
		if(v<=n)cnt[v][0]=1;
		v=nxt[v];
	}
	v=nxt2[n<<1];
	while(v)
	{
		if(v<=n)cnt[v][1]=1;
		v=nxt2[v];
	}
	cnt[0][0]=cnt[0][1]=1;
	for(int i=0;i<=n;i++)
		if(cnt[i][0]&&cnt[n-i][1])
		{
			for(int j=1;j<=i;j++)cout<<s[j];
			for(int j=n;j>i;j--)cout<<s[j];
			cout<<endl<<i;
			return;
		}
	puts("-1");
}
void QingKong()
{

}
int main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int T=1;
	//cin>>T;
	Init();
	while(T--)
	//while(cin>>n&&n)
	//while(cin>>n)
	{
		Solve();
		QingKong();//多测不清空，抱灵两行泪
	}
	return 0;
}
```

完结撒花~

---

## 作者：FReQuenter (赞：2)

## 思路

不难发现，给定 $s$ 和一个分段点 $x$，可以生成出 $t$。类似地，给定 $t$ 和一个分段点 $x$，也可以生成出 $s$。

那么我们可以枚举分段点，希望可以 $O(1)$ 判断当前分段点是否可行。

显然，$O(n)$ 判断是可以做到的：只要对 $t$ 进行一堆子串截取即可。我们不需要对截取出来的子串进行修改，只要拼接和比较是否相等即可。

那么，字符串哈希是一个很好的选择。题目中给定的 $t$ 有一段是 $s$ 的首尾翻转而来，所以可以正着做一遍哈希值，反着再来一遍。[字符串哈希入门](https://blog.csdn.net/errors_F/article/details/123241715)。

难得地，这题数据并不水。它卡了自然溢出，会 WA\*5。

## 代码

```cpp
#include<bits/stdc++.h>
#define p 131
#define mod 100000927
#define int unsigned long long
using namespace std;
int h1[2000005],h2[2000005],base[2000005];
int hash1(int l,int r){
	return (h1[r]+mod-h1[l-1]*base[r-l+1]%mod)%mod;
}
int hash2(int l,int r){
	return (h2[l]+mod-h2[r+1]*base[r-l+1]%mod)%mod;
}
signed main(){
    int n;
    cin>>n;
    string t;
    cin>>t;
    t='#'+t;
    base[0]=1;
    for(int i=1;i<=n*2;i++) base[i]=base[i-1]*p,base[i]%=mod;
    for(int i=1;i<=n*2;i++) h1[i]=h1[i-1]*p+t[i]-48,h1[i]+=mod,h1[i]%=mod;
    for(int i=n*2;i;i--) h2[i]=h2[i+1]*p+t[i]-48,h2[i]+=mod,h2[i]%=mod;
    for(int i=0;i<=n;i++){
        int hs=hash2(i+1,i+n);
        if((hash1(1,i)*base[n-i]%mod+hash1(i+n+1,n+n))%mod==hs){
            string tmp=t.substr(i+1,n);
            reverse(tmp.begin(),tmp.end());
            cout<<tmp<<'\n'<<i;
            return 0;
        }
    }
    cout<<-1;
    return 0;
}
```

---

## 作者：Jasper08 (赞：2)

由于 $1\le N\le 10^6$，我们需要考虑 $O(N)$ 的做法。不难发现题目其实是让我们判断字符串 $\overline{S_1S_2\cdots S_iS_{i+N+1}\cdots S_{2N}} $ 和 $\overline{S_{i+N}S_{i+N-1}\cdots S_{i+1}} $ 是否完全相等。判断字符串相等，可以很自然地想到字符串哈希。

字符串哈希的实现方式通常是将原字符串字符串视作一个 $p$ 进制数，将其转换为十进制后对 $q$ 取模。这里取 $p=13331$，$q=2^{64}$（可直接通过 `unsigned long long` 的溢出取模）。

我们可以先计算 $S$ 中所有前缀和后缀字符串的的哈希值。定义 $pre_i$ 表示 $S_1\sim S_i$ 的字符的哈希值。显然 $pre_0=0$，那么 $pre_i=pre_{i-1}\times p+S_i$。同理，定义 $suf_i$ 表示 $S_{2n}\sim S_i$ 的字符的哈希值，则 $suf_{2N+1}=0,suf_{i}=suf_{i+1}\times p+S_i$。

接下来，我们可以通过 $pre,suf$ 求出每个子串的哈希值。对于字符串 $\overline{S_lS_{l+1}\cdots S_r}\;(l\le r)$，显然其哈希值为 $pre_r-pre_{l-1}\times p^{r-l+1}$；而对于字符串 $\overline{S_rS_{r-1}\cdots S_l}$，其哈希值则为 $suf_l-suf_{r+1}\times p^{r-l+1}$。其中 $p$ 的幂次可以预处理出来。

那么我们枚举 $i=0,1,2,\cdots ,N$，用哈希判断字符串 $\overline{S_1S_2\cdots S_iS_{i+N+1}\cdots S_{2N}} $ 和 $\overline{S_{i+N}S_{i+N-1}\cdots S_{i+1}} $ 是否完全相等即可。注意哈希验证后还要根据题意模拟验证一遍。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
 
using namespace std;
 
typedef unsigned long long ull;
 
const int N = 2e6+10;
const int P = 13331;
 
int n;
char t[N];
ull pre[N], suf[N], p[N];
 
ull prehash(int l, int r) {
    return (pre[r] - pre[l-1] * p[r-l+1]);
}
 
ull sufhash(int l, int r) {
    return (suf[l] - suf[r+1] * p[r-l+1]);
}
 
bool check(int i) {
	string s1, s2;
  	int j = 1;
  	for ( ; j <= i; ++j) s1 += t[j];
  	for ( ; j <= i+n/2; ++j) s2 += t[j];
  	for ( ; j <= n; ++j) s1 += t[j];
  	reverse(s2.begin(), s2.end());
  	if (s1 == s2) return 1;
 	return 0;
}
 
int main() {
    cin >> n >> t+1;
 
    p[0] = 1, n *= 2;
    for (int i = 1; i <= n; ++i) p[i] = p[i-1] * P;
    for (int i = 1; i <= n; ++i) pre[i] = pre[i-1] * P + (t[i]-'a');
    for (int i = n; i >= 1; --i) suf[i] = suf[i+1] * P + (t[i]-'a');
 
    for (int i = 1; i <= n/2; ++i) {
        ull pr = prehash(1, i), rev = sufhash(i+1, i+n/2), sf = prehash(i+n/2+1, n);
      	ull tt = pr * p[n/2-i] + sf;
        if (tt == rev && check(i)) {
            for (int j = i+n/2; j > i; --j) putchar(t[j]);
          	cout << endl << i << endl;
            system("pause");
            return 0;
        }
    }
    puts("-1");
    system("pause");
    return 0;
}
```

---

## 作者：Light_Star_RPmax_AFO (赞：2)

## 前言


长沙市一中 8 机房 0726 模拟测 4

[更好的阅读体验](https://www.luogu.com.cn/blog/JJL0610666/solution-at-abc284-f)

# 思路

**hash**：

hash 的作用之一就是可以 $O(1)$ 匹配字符串。

分析一下，由于字符串是由正，反两个字符串组成的如样例一：

`"abc" = "ab" + "c"` 再在中间加上翻转的 `"cba"` 就组成了 `"abcbac"`。

所以我们只需要判断去掉中间这一段之后是否去除的和留下的相等，就可以判断。

## 坑点

此题卡掉了 `unsigned long long`，我们考试的的时候甚至连 $998244353$ 也被卡掉了，所以这里我们需要使用 $1000000007$ 来取模。

# AC Code

```cpp
#include<bits/stdc++.h>
#define ull long long
#define Fup(i,j,k) for(int i = j;i <= k;++i)
#define Fdn(i,j,k) for(int i = j;i >= k;--i)
using namespace std;
 
inline int read()
{
    int x = 0,f = 1;char ch = getchar();
    while (ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - 48;ch = getchar();}
    return x * f;
}
 
void write(int x)
{
    if(x < 0)
       putchar('-'),x =- x;
    if(x > 9)
       write(x / 10);
    putchar(x % 10 + '0');
    return;
}
 
int n;
string s;
ull Hashf[10000010],pos[10000010],Hashb[10000010];
const ull base = 29,mod = 1000000007;
 
ull sumf(int l,int r){
    if(l > r)return 0;
    return ((Hashf[r] - (1ll * Hashf[l - 1] * pos[r - l + 1]) % mod) + mod) % mod;
}
 
ull sumb(int l,int r){
    if(l > r)return 0;
    return ((Hashb[r] - (1ll * Hashb[l - 1] * pos[r - l + 1]) % mod) + mod) % mod;
}
 
int main(){
    n = read();
    cin>>s;
    s = " " + s;
    pos[0] = 1;
    for(int i = 1;i <= 2 * n;i++){
        pos[i] = pos[i - 1] * base % mod;
        Hashf[i] = (Hashf[i - 1] * base % mod + (s[i] - 'a')) % mod;
        Hashb[i] = (Hashb[i - 1] * base % mod + (s[2 * n - i + 1] - 'a')) % mod;
    }
    
    for(int i = 0;i <= n;i++){
        if((i == 0 || sumf(1,i) == sumb(n - i + 1,n)) && (i == n || sumf(i + n + 1,2 * n) == sumb(n + 1,n * 2 - i)))
		{
			cout<<s.substr(1,i)+s.substr(i + n + 1,n - i)<<endl<<i;
			return 0;
		}
    }
    cout<<-1;
    return 0;
}
```

---

## 作者：tZEROちゃん (赞：2)

Z 函数（扩展 KMP）

### Pre-knowledge


这个东西外国好像叫 Z Algorithm，但是中国好像叫扩展 KMP 的多一点。

为了方便起见，下文的字符串从 $0$ 开始计数，就是说第一个字符是 $S_0$。

以及在下文出现的一些定义：
- $S[l:r]$：表示 $S$ 的第 $l$ 到第 $r-1$ 个字符构成的子字符串，若 $l=r$ 则是空串，若没有写 $r$ 表示从第 $l$ 个字符开始的后缀。
- ${\rm{rev}}(S)$：表示字符串 $S$ 的倒序，比如 $S= \tt abcd$，那么 ${\rm{rev}}(S) = \tt dcba$。
- $|S|$ 表示字符串 $S$ 的长度。

首先我们来明确一下扩展 KMP 能解决什么问题。

- 给定字符串 $S$，对于 $1\le i\le |S|$，找到 $S$ 和 $S[i:]$ 的 LCP（longest common prefix，最长公共前缀）。

扩展 KMP 可以在 ${\mathcal O}(|S|)$ 的复杂度解决这个问题，提供一些可供学习的资料。

- [【OI-Wiki】Z 函数（扩展 KMP）
](https://oi-wiki.org/string/z-func/)。
- [【洛谷 P5410 模板】扩展 KMP / Z 函数](https://www.luogu.com.cn/problem/P5410)。

当然，这道题作为 AtCoder 里的试题，我们可以考虑直接使用 [AtCoder Library 的 Z 函数](https://github.com/atcoder/ac-library/blob/master/atcoder/string.hpp)。

那么，在下文中，我们约定：

- $Z(S)[i]$ 表示 $S$ 与 $S[i:]$ 的 LCP 长度。特别的，$Z(S)[|S|]=0$。

### Solution

考虑转化题目条件：

- 存在字符串 $S$ 和 $i(0\le i\le N)$，使得 $f_i(S)=T$。
- 存在 $i(0\le i\le N)$ 使得 $T[0:i] = {\rm{rev}}(T[N:N+i])$，$T[N+i:2N]={\rm rev}(T[i:N])$。
- 令 $A = T[0:N], B = {\rm{rev}}(T[N:N+i])$，那么存在 $i(0\le i\le N)$ 使得 $A[0:i] = B[N-i:N]$，$A[i:N] = B[0:N-i]$。
- 令 $X=A+B,Y=B+A$（此处的加号表示字符串拼接），那么存在 $i(0\le i\le N)$ 使得 $Z(X)[2N-i]=i$，$Z(Y)[N+i]=N-i$。

最后一个条件可以先预处理 $Z(X), Z(Y)$，然后在 ${\mathcal{O}}(1)$ 的复杂度内判断。最后，可以在 ${\mathcal{O}}(N)$ 的时间复杂度内解决。

```cpp
#include<bits/stdc++.h>
#include<atcoder/string>
using namespace std;
using namespace atcoder;
int main() {
   int n;
   cin >> n;
   string t;
   cin >> t;
   string a, b;
   for (int i = 0; i < n; ++i) a += t[i];
   for (int i = 2 * n - 1; i >= n; --i) b += t[i];
   string x = a + b, y = b + a;
   vector<int> za_x = z_algorithm(x);
   vector<int> za_y = z_algorithm(y);
   za_x.push_back(0);
   za_y.push_back(0);
   for (int i = 0; i <= n; ++i) {
      if (za_x[2 * n - i] == i && za_y[n + i] == n - i) {
         for (int j = 0; j < i; ++j) cout << t[j];
         for (int j = n + i; j < 2 * n; ++j) cout << t[j];
         cout << '\n' << i << '\n';
         return 0;
      }
   }
   puts("-1");
}
```

---

## 作者：CarroT1212 (赞：1)

#### 题目大意

对于一个长度为 $N$ 的字符串 $S$ 和 $i(0 \le i \le N)$，定义 $f_i(S)$ 为 $S$ 的前 $i$ 个字符、$S$ 的反串、$S$ 的后 $(N-i)$ 个字符依次拼接得到的字符串。现给定长度为 $2N$ 的字符串，试求出 $i$ 与 $S$。

数据范围：$1 \le N \le 10^6$，$S$ 仅含小写字母。

#### 解法分析

哈希爆算。

暴力做法肯定是拆出字符串直接进行比较，也肯定是过不了的。如果用哈希的话，我们枚举 $i$，计算 $f_i(S)$ 中从第 $(i+1)$ 位开始的长度为 $N$ 的字符串的哈希值，并和 $f_i(S)$ 的前 $i$ 个字符和后 $(N-i)$ 个字符拼接所得字符串的哈希值作比较，如果相等就说明找到了，输出即可。

但是这个蒟蒻赛时由于对哈希的理解极度贫乏并没有想到全部前缀预处理后 $O(1)$ 求哈希，而是只预处理了两头连续字符串的哈希值，中间的反串只算一次，后面都是根据前一次结果直接计算转移的，贼丑，代码凑合着看吧，大体思路还是一样的。

注意开 `long long`，记得检查有没有漏取模，赛时因为这俩挂了一发。

另外据说这题卡单模数，我可能是因为运气比较好或者写法过于奇怪没有受害，如果是双模数我这种转移写法可能就寄了，所以代码参考一下就好。

#### 代码

很丑。

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pll pair<ll,ll>
using namespace std;
const int N=2e6+7,MOD=1e9+7,B=129;
int n;
ll f[N],b[N];
char str[N];
ll qpow(ll x,ll y) { return y?(y&1?x:1)*qpow(x*x%MOD,y>>1)%MOD:1; }
int main() {
	scanf("%d%s",&n,str+1);
	for (int i=1;i<=n;i++) f[i]=(f[i-1]+(ll)str[i]*qpow(B,i-1)%MOD)%MOD; // 两头字符串的哈希值
	for (int i=n*2;i>n;i--) b[i]=(b[i+1]*B%MOD+(ll)str[i])%MOD;
	ll cnt=0;
	for (int i=1;i<=n;i++) cnt=(cnt*B%MOD+(ll)str[i])%MOD;
	for (ll i=n+1;i<=n*2;i++) {
		if (cnt==(f[i-n-1]+b[i]*qpow(B,i-n-1)%MOD)%MOD) { // 相等了
			for (int j=1;j<=i-n-1;j++) printf("%c",str[j]);
			for (int j=i;j<=n*2;j++) printf("%c",str[j]);
			return printf("\n%d",i-n-1),0;
		}
		cnt=((cnt-str[i-n]*qpow(B,n-1)%MOD+MOD)%MOD*B%MOD+str[i])%MOD; // 因为每次算的中间的字符串都只相对于上一次的偏移了一位，所以可以通过计算直接转移过去
	}
	printf("-1");
	return 0;
}
```

---

## 作者：Hell0_W0rld (赞：1)

## F
+ [link](https://atcoder.jp/contests/abc284/tasks/abc284_f) 
+ *1575。
+ 难度：绿。
+ 官方标答：`Z algorithm`。
+ 我的解法：`HASH` + 枚举。

注意到 $f_i(S)=S[1:i]+rev(S[i+1:n])+rev(S[1:i])+S[i+1:n]$，即 $t[n\to 1]$ 和 $t[n+1\to 2n]$ 分别为 $a+b$ 和 $b+a$，其中 $a=S[i\to 1],b=S[i+1\to n]$。所以我们只需要找到 $a$ 即可，也就是 $i$，$S$ 就自然出现了。

于是对 $t$ 的前 $n$ 位和后 $n$ 位分别做前缀哈希，再枚举 $i$。只要满足上述性质，那么输出前 $i$ 位和后 $n-i$ 位拼起来。

附录：本题不能用单模数。因为本蒟蒻不会双模，只能写双底数，即 HASH 的进制数。

[坎坷的提交后，最终 AC 了](https://atcoder.jp/contests/abc284/submissions?f.Task=abc284_f&f.LanguageName=&f.Status=&f.User=brianxi)

Code：
```cpp
const ll N=3e6+9;
ll n;
ull p[N]={1};
ull p2[N]={1};
ull h[N][2];
ull h2[N][2]; 
const ll BASE=1145141,BASE2=99824;
ull pre(ll r,ll k){return h[r][k];}
ull suf(ll l,ll k){return h[n][k]-h[n-l][k]*p[l];}
ll pre2(ll r,ll k){return h2[r][k];}
ll suf2(ll l,ll k){return h2[n][k]-h2[n-l][k]*p2[l];}
int main(){
	string t;
	cin>>n>>t;
	string a=t.substr(0,n);
	string b=t.substr(n);
	reverse(a.begin(),a.end());
	for(ll i=1;i<=n;i++)p[i]=p[i-1]*BASE;
	for(ll i=1;i<=n;i++)p2[i]=p2[i-1]*BASE2;
	for(ll i=1;i<=n;i++)h[i][0]=h[i-1][0]*BASE+a[i-1];
	for(ll i=1;i<=n;i++)h[i][1]=h[i-1][1]*BASE+b[i-1];
	for(ll i=1;i<=n;i++)h2[i][0]=(h2[i-1][0]*BASE2+a[i-1]);
	for(ll i=1;i<=n;i++)h2[i][1]=(h2[i-1][1]*BASE2+b[i-1]);
	rep(x,0,n){
		ll y=n-x;
		if(suf(x,0)==pre(x,1) && pre(y,0)==suf(y,1) && suf2(x,0)==pre2(x,1) && pre2(y,0)==suf2(y,1)){
			cout<<t.substr(0,x)<<t.substr(n+x)<<endl<<x<<endl;
			return 0;
		}
	} 
	cout<<-1<<endl;
	return 0;
}
```

---

## 作者：DengDuck (赞：0)

简单字符串哈希题，我们考虑枚举 $i$，然后求出前 $i$ 个字符与后 $n-i$ 个字符拼成的字符串的哈希，和中间的 $[i+1,i+n]$ 这一部分翻转之后的哈希值，然后判断即可。

简单讲讲怎么拼出两段字符串拼接之后的哈希值，首先你需要求出两段自己的哈希值，求法如下：

首先你可以处理出一个字符串所有前缀的哈希值，记作 $pre_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/c362mjij.png)

显然求 $[l,r]$ 的哈希值，只需要对于 $pre_r$ 去除 $pre_{l-1}$ 的贡献，显然 $pre_{l-1}$ 的部分到此已经成你的进制乘了 $r-l+1$ 次，所以区间哈希值为：

$$
pre_r-pre_{l-1}\times T^{r-l+1}
$$

拼接的方法也是同理，只需要对于后面的段算上前面的段的贡献即可。

设后面的段长度为 $N$，前面的段哈希值为 $A_1$，后面的段哈希值为 $A_2$，则拼接哈希值为：

$$
A_1\times T^N+A_2
$$

对于字符串倒过来的哈希值，你可以直接弄一份倒过来字符串的前缀哈希值就行了。

然后这题就比较简单了，直接判断即可。

数据比较强大，我用我心爱的 $\text{DeepSeaSpray}$ 生日死活过不去，所以假了个双哈希就过了，考虑 $998244353$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=4e6;
//const LL M;
const LL mod=998244353;
const LL mod2=20090327;
//const LF eps;
const LL P=13331;
const LL P2=1331;
LL n,pre[N],suf[N],pre2[N],suf2[N],pw[N],pw2[N];
char c[N+5];
int main()
{
	scanf("%lld%s",&n,c+1);
	n*=2;
	pw[0]=1,pw2[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*P%mod;
	for(int i=1;i<=n;i++)pw2[i]=pw2[i-1]*P2%mod2;
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]*P%mod+c[i]-'a';
	for(int i=n;i>=1;i--)suf[i]=suf[i+1]*P%mod+c[i]-'a';
	for(int i=1;i<=n;i++)pre2[i]=pre2[i-1]*P2%mod2+c[i]-'a';
	for(int i=n;i>=1;i--)suf2[i]=suf2[i+1]*P2%mod2+c[i]-'a';
	for(int i=0;i<=n/2;i++)
	{
		LL t1=(-suf[i+n/2+1]*pw[n/2]%mod+suf[i+1]+mod)%mod;
		LL t2=(pre[n]-pre[n-(n/2-i)]*pw[n/2-i]%mod+pre[i]*pw[n/2-i]%mod+mod)%mod;
		LL tt1=(-suf2[i+n/2+1]*pw2[n/2]%mod2+suf2[i+1]+mod2)%mod2;
		LL tt2=(pre2[n]-pre2[n-(n/2-i)]*pw2[n/2-i]%mod2+pre2[i]*pw2[n/2-i]%mod2+mod2)%mod2;
		//	cout<<t1<<' '<<t2<<endl;
		if(t1==t2)
		{
			for(int j=1;j<=i;j++)putchar(c[j]);
			for(int j=n-(n/2-i)+1;j<=n;j++)putchar(c[j]);
			putchar('\n');
			printf("%d\n",i);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
//RP++
```



---

## 作者：hjqhs (赞：0)

题目中的 $f$ 函数本质就是在原本字符串中的某一位把倒序字符串塞进去。所以可以枚举中间删去的字符串，判断剩下字符串是否相等。用 hash 可以做到 $O(n)$。  
模拟赛题，写了一个小时结果卡了自然溢出，差评。
```cpp
// Problem: F - ABCBAC
// Contest: AtCoder - AtCoder Beginner Contest 284
// URL: https://atcoder.jp/contests/abc284/tasks/abc284_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Created Time: 2023-11-22 17:54:20
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

#define int long long
#define rep(i, a, b) for (int i = a; i <= b; ++ i)
#define per(i, a, b) for (int i = a; i >= b; -- i)

using namespace std;

const int N = 2000005;
const int INF = 0x3f3f3f3f;
const int B = 131;
const int MOD = 1000000007;

int n, nn, base[N] = { 1 }, ordh[N], revh[N];
string s;

void init_hash () {
	rep (i, 1, nn) base[i] = base[i - 1] * B % MOD;
	
	rep (i, 1, nn) ordh[i] = ( ordh[i - 1] * B % MOD + (s[i] ^ 48) ) % MOD;
	per (i, nn, 1) revh[i] = ( revh[i + 1] * B % MOD + (s[i] ^ 48) ) % MOD;
}

int qord (int l, int r) {
	if (l > r) return 0;
	return (ordh[r] - ordh[l - 1] * base[r - l + 1] % MOD + MOD) % MOD;
}

int qrev (int l, int r) {
	if (l > r) return 0;
	return (revh[l] - revh[r + 1] * base[r - l + 1] % MOD + MOD) % MOD;
}

void solve () {
	cin >> n >> s;
	s = ' ' + s, nn = n << 1;
	
	init_hash ();
	
	rep (i, 0, n) {
		int dat1 = qord (1, i) * base[n - i] % MOD;
		int dat2 = qord (i + n + 1, nn) % MOD;
		int dat3 = qrev (i + 1, i + n) % MOD;
		if ( (dat1 + dat2) % MOD == dat3 ) {
			string ans = s.substr (i + 1, n);
			reverse (ans.begin(), ans.end());
			
			return cout << ans << '\n' << i, void ();
		} 
	}
	
	return cout << -1, void ();
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	solve();
	
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

### 小技巧：`strstr()` 函数

- `strstr()` 函数搜索一个字符串在另一个字符串中的第一次出现。
- 找到所搜索的字符串，则该函数返回第一次匹配的字符串的地址；
- 如果未找到所搜索的字符串，则返回 NULL。

以下代码会返回 $a$ 中第一次出现子串 $b$ 的位置（下标）

```C++
char a[N],b[N];
	scanf("%s %s",a,b);
	int i=strstr(a,b)-a;
	cout<<i;
```


运行实例

```Plain Text
in: asdfghjk fgh
out: 3
```



### **非正解思路**

当我们拿到一个字符串 $ S=abc$，我们，我们要知道 $fi(S)$ 是怎么得到的。整理一下题目的意思可以知道，我们就是在原字符串 $S$ 的第 $i$ 个位置后插入字符串 $S$ 的倒序串。那么现在我们既然知道题目给出的串中包含了两个答案串 $S$，我们首先想到的就是枚举 $i$ 的位置。但很显然，这种做法的时间复杂度达到了 $O(n^2)$ 我们过不去。

我们假设字符串 $S=1\sim n$，假设 $T$ 是 $fi(S)$ 得到的，那么 $T$ 一定是 $1\sim k +n\sim 1 +(k+1)\sim n$（此处 $+$ 表示连接字符串）。我们考虑以下操作：截取 $T$ 的前一半作为字符串 $A$，那么 $A=1\sim k+n\sim (k+1)$，从后往前截取 $T$ 的后一半并重复一次作为字符串 $B$，那么 $B=n\sim(k+1)+1\sim k +n\sim(k+1)+1\sim k $。

我们可以发现在 $B$ 中一定存在 $A$ 这个子串。

但是如果 $T$ 不是 $fi(S)$ 得到的，那么很显然 $B$ 中就没有 $A$ 这个子串了。所以根据这个方法，我们可以判断 $T$ 是否是某个 $fi(S)$ 得到的。

最后如果 $B$ 在有 $A$ 子串，那么我们就找到这个子串的开头的位置，就知道了 $i$ 是多少了，使用 `strstr()` 函数可以快速得到。

### Code

```C++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=3e6+7;
char s[N],a[N],b[N]; 
ll n,t;
int main(){
	scanf("%lld",&n);cin>>s;//eg.s=abcbac
	for(ll i=0;i<n;++i){
		a[i]=s[i];//截取S的前一半 eg.a=abc
		b[i]=b[i+n]=s[n*2-i-1];//从后往前截取s的后一半并重复一次eg.b=cabcab
	}
	ll i=strstr(b,a)-b;//寻找b中的a子串
	
	if(i<0){
		puts("-1");
		return 0;
	}
	i=n-i;
	for(ll j=0;j<i;++j) printf("%c",s[j]);
	for(ll j=n+i;j<(n<<1);++j) printf("%c",s[j]);
	printf("\n%d",i);
	return 0;
}
```




---

## 作者：快乐的大童 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc284_f)
## 题意简述
一个长为 $2n$ 的字符串，在其中选择一个长度为 $n$ 的子串 $t$，使得字符串剩下的部分拼接起来组成的字符串等于 $s$ 反转后的字符串。输出任意一组方案。
## 思路
看到“两个字符串相等”，考虑哈希。

将原字符串反转，方便我们取 $t$。

记录数组 $a_i$ 表示每个反转字符串的自 $i$ 起的长度为 $n$ 的子串的哈希值。

记录数组 $b_i$ 表示原字符串去掉自 $i$ 起的长度为 $n$ 的子串，剩下的部分组成的字符串的哈希值。

那么这个字符串有解当且仅当存在一个 $i$ 使得 $a_i=b_{n-i+2}$。


------------

附注：此题数据极为恶心，本人写的双模哈希换了两次模数和底数才过，~~在此之前一直 `AC*59,WA*1`~~。

所以该代码的模数和底数都是乱打的。
## 代码
已去掉火车头和快读快输。

```cpp
/*R()为快读函数，write()为快输函数*/
#define int long long
#define rep(a,b,c) for(int a=b;a<=c;a++)
const int maxn=2e6+5,base=42;
const int mod[2]={1145191559,6666655777};
int n;
char s1[maxn],s2[maxn]; 
int a[maxn][2],b[maxn][2];
int ksm(int x,int y,int p){
	int res=1;
	while(y){
		if(y&1) res=(res*x)%p;
		x=(x*x)%p;
		y>>=1;
	}
	return res;
}
void hash1(){
	rep(i,1,n){
		a[1][0]=(a[1][0]*base+(s2[i]-'a'))%mod[0];
		a[1][1]=(a[1][1]*base+(s2[i]-'a'))%mod[1];
	}
	rep(i,2,n+1){
		a[i][0]=(((a[i-1][0]-((s2[i-1]-'a')*ksm(base,n-1,mod[0]))%mod[0]+mod[0])%mod[0]*base)%mod[0]+(s2[i+n-1]-'a'))%mod[0];
		a[i][1]=(((a[i-1][1]-((s2[i-1]-'a')*ksm(base,n-1,mod[1]))%mod[1]+mod[1])%mod[1]*base)%mod[1]+(s2[i+n-1]-'a'))%mod[1];
	}
}//其实哈希式子自己小推一下就好
void hash2(){
	rep(i,1,n){
		b[n+1][0]=(b[n+1][0]*base+(s1[i]-'a'))%mod[0];
		b[n+1][1]=(b[n+1][1]*base+(s1[i]-'a'))%mod[1];
	}
	per(i,n,1){
		int k1=ksm(base,n-i,mod[0]),k2=ksm(base,n-i,mod[1]);
		b[i][0]=((b[i+1][0]-(s1[i]-'a')*k1+mod[0])%mod[0]+(s1[i+n]-'a')*k1)%mod[0];
		b[i][1]=((b[i+1][1]-(s1[i]-'a')*k2+mod[1])%mod[1]+(s1[i+n]-'a')*k2)%mod[1];
	}
}
signed main(){
	n=R();
	scanf("%s",s1+1);
	rep(i,1,2*n) s2[i]=s1[2*n-i+1];
	hash1();hash2();
	rep(i,1,n+1){
		if(a[i][0]==b[n-i+2][0]&&a[i][1]==b[n-i+2][1]){
			rep(j,i,i+n-1) putchar(s2[j]);puts("");
			write(n-i+1);
			return 0;
		}
	}
	puts("-1");
}
```


---

## 作者：迟暮天复明 (赞：0)

题意：对于一个字符串 $S$，你可以将其分成两个字符串 $A$ 与 $B$。将 $A$，$S$ 的逆序字符串，$B$ 三个串拼接，得到字符串 $T$。现在给你 $T$，求 $S$ 与任意一种可行的拼接方案。

先上图。
![](https://cdn.luogu.com.cn/upload/image_hosting/rnyim7pp.png)

我们如果把 $S$ 分成字符串 $L$ 和 $R$，那么同时 $S$ 的逆序字符串也可以视为 $L$ 的逆序字符串与 $R$ 的逆序字符串拼接成的字符串。

那这样这个题就很简单了。我们可以枚举字符串 $L$ 的长度，然后就能算出另外三个字符串在 $T$ 中的位置。接下来我们只需要判断是否成立即可。判断两个字符串相等，最先想到的肯定是字符串哈希。我们做出 $T$ 的正序哈希值与逆序哈希值，然后就可以很方便地判断了。总时间复杂度 $O(|T|)$。

注意这个题卡了自然溢出哈希。单哈希好像有一些模数被卡了。但是双哈希肯定能过。

赛时代码：
```cpp
#include<bits/stdc++.h>
using ll = long long;
using namespace std;

long long hshl[2000010],hshr[2000010];
const ll mod = 1e9+7;
const ll base = 37;
void gethash(string s, int n) {
  ll sum=0;
  for(int i=0;i<n*2;++i) {
    sum=sum*base+s[i]-'a'+1;
    sum%=mod;
    hshl[i+1]=sum;
  }
  sum=0;
  for(int i=n*2-1;i>=0;--i){
    sum=sum*base+s[i]-'a'+1;
    sum%=mod;
    hshr[i+1]=sum;
  }
}
ll qpow(int a){
  ll ans=1,b=base;
  while(a){
    if(a&1)ans=ans*b%mod;
    b=b*b%mod;
    a>>=1;
  }return ans;
}ll getlhash(int l, int r) {
  return ((hshl[r] - hshl[l - 1] * qpow(r - l + 1)) % mod + mod) % mod;
}
ll getrhash(int l, int r) {
  return ((hshr[l] - hshr[r + 1] * qpow(r - l + 1)) % mod + mod) % mod;
}
int main(){
  ios::sync_with_stdio(0);
  int n;cin>>n;string s;cin>>s;gethash(s,n);
  for(int i=0;i<=n;++i){
    int l=i,r=i+n,mid=n;
    int a=getlhash(1,l),b=getrhash(mid+1,r),c=getlhash(r+1,2*n),d=getrhash(l+1,mid);
    if(a!=b)continue;
    if(c!=d)continue;
    for(int j=0;j<i;++j)cout<<s[j];
    for(int j=i+n;j<2*n;++j)cout<<s[j];
    cout<<endl<<l;
    return 0;
  }cout<<"-1";
  return 0;
}
```

---

## 作者：lfxxx (赞：0)

这题是字符串哈希题。

我们可以枚举 $i$ 并判断合法。

也就是说，判断前 $i$ 为字符串和后 $N-i$ 为字符串拼接起来后是否是中间那一段字符串的翻转。

那该如何判断合法呢？

字符串哈希预处理前缀后缀哈希和，然后用快速幂处理逆元以来拼接两个字符串的哈希值，中间翻转的字符串的哈希值用后缀哈希和处理，再 $O(1)$ 比对即可。因为用到快速幂，所以总复杂度 $O(n 
\log n)$ 。

特别注意，现在针对 `unsigned long long` 已经有了卡发，所以尽量写大质数作为模数。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9+7;
const int maxn=2e6+100;
int pre[maxn];
int suf[maxn];
int n;
int qpow(int a,int b){
	if(b==0) return 1;
	if(b==1) return a;
	int res=qpow(a,b/2);
	res*=res;
	res%=mod;
	if(b%2==1) res*=a,res%=mod;
	return res;
}
char s[maxn];
int getHash(int l,int r,int type){
	if(l>r) return 0;
	if(type==1) //前缀 
		return (((pre[r]-pre[l-1]+mod)%mod)*qpow(qpow(37,l-1),mod-2))%mod;
	else
		return (((suf[l]-suf[r+1]+mod)%mod)*qpow(qpow(37,2*n-r),mod-2))%mod;
} 

signed main(){
	cin>>n;
	for(int i=1;i<=2*n;i++){
		cin>>s[i];
	}
	for(int i=1;i<=2*n;i++){
		pre[i]=(pre[i-1]+(s[i]-'a'+1)*qpow(37,i))%mod;
	}
	for(int i=2*n;i>=1;i--){
		suf[i]=(suf[i+1]+(s[i]-'a'+1)*qpow(37,2*n-i+1))%mod;
	}
	for(int i=0;i<=n;i++){
		if((getHash(1,i,1)+(getHash(n+i+1,2*n,1)*qpow(37,i))%mod)%mod==getHash(i+1,n+i,0)){
			for(int j=n+i;j>=i+1;j--){
				cout<<s[j];
			}
			cout<<'\n'<<i;
			return 0;
		}
	}
	cout<<-1;
}
```


---

