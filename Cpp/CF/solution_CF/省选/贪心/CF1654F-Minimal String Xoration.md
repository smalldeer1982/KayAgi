# Minimal String Xoration

## 题目描述

You are given an integer $ n $ and a string $ s $ consisting of $ 2^n $ lowercase letters of the English alphabet. The characters of the string $ s $ are $ s_0s_1s_2\cdots s_{2^n-1} $ .

A string $ t $ of length $ 2^n $ (whose characters are denoted by $ t_0t_1t_2\cdots t_{2^n-1} $ ) is a xoration of $ s $ if there exists an integer $ j $ ( $ 0\le j \leq 2^n-1 $ ) such that, for each $ 0 \leq i \leq 2^n-1 $ , $ t_i = s_{i \oplus j} $ (where $ \oplus $ denotes the operation [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

Find the lexicographically minimal xoration of $ s $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test, the lexicographically minimal xoration $ t $ of $ s = $ "acba" is "abca". It's a xoration because, for $ j = 3 $ ,

- $ t_0 = s_{0 \oplus j} = s_3 = $ "a";
- $ t_1 = s_{1 \oplus j} = s_2 = $ "b";
- $ t_2 = s_{2 \oplus j} = s_1 = $ "c";
- $ t_3 = s_{3 \oplus j} = s_0 = $ "a".

 There isn't any xoration of $ s $ lexicographically smaller than "abca".In the second test, the minimal string xoration corresponds to choosing $ j = 4 $ in the definition of xoration.

In the third test, the minimal string xoration corresponds to choosing $ j = 11 $ in the definition of xoration.

In the fourth test, the minimal string xoration corresponds to choosing $ j = 10 $ in the definition of xoration.

In the fifth test, the minimal string xoration corresponds to choosing either $ j = 0 $ or $ j = 1 $ in the definition of xoration.

## 样例 #1

### 输入

```
2
acba```

### 输出

```
abca```

## 样例 #2

### 输入

```
3
bcbaaabb```

### 输出

```
aabbbcba```

## 样例 #3

### 输入

```
4
bdbcbccdbdbaaccd```

### 输出

```
abdbdccacbdbdccb```

## 样例 #4

### 输入

```
5
ccfcffccccccffcfcfccfffffcccccff```

### 输出

```
cccccffffcccccffccfcffcccccfffff```

## 样例 #5

### 输入

```
1
zz```

### 输出

```
zz```

# 题解

## 作者：Little09 (赞：20)

难点：这题让你求找到一个 $x$ 使得字符串字典序最小，但是事实上是可以求出第 $k$ 小的。

令 $f(x,k)$ 表示取 $x$ 作为 xor 的值，得到字符串的前 $2^k$ 个字符的子串。那么有一个很重要的性质：

$$f(x,k)=f(x,k-1)+f(x\text{ xor } 2^{k-1},k-1)$$

加号表示字符串的拼接。证明比较简单，对于前 $2^{k-1}$ 位的 $i$，满足 $i\text{ xor }x=(i+2^{k-1})\text{ xor }(x \text{ xor } 2^{k-1})$，所以拼接是可行的。

所以我们倍增地做。枚举 $k$，每次对所有 $x$ 按字符串的字典序排序。拼接时先考虑前面的字符串，再考虑后面的就行了。

复杂度是 $O(n^2\times 2^n)$。两个 $n$ 其中一个是枚举 $k$，另一个是对 $2^n$ 个数排序的 $\log$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
char s[N];
int a[N],v[N];
int t[N],n,m;
int l;
bool cmp(int x,int y)
{
	if (v[x]==v[y]) return v[x^l]<v[y^l];
	return v[x]<v[y];
}

int main()
{
	scanf("%d",&n);
	scanf("%s",&s);
	m=(1<<n);
	for (int i=0;i<m;i++) a[i]=i;
	for (int i=0;i<m;i++) v[i]=s[i]-'a';
	sort(a,a+m,cmp);
	for (int i=1;i<=n;i++)
	{
		l=(1<<(i-1));
		sort(a,a+m,cmp);
		int cnt=0;
		for (int j=0;j<m;j++)
		{
			if (j==0||cmp(a[j-1],a[j])) t[a[j]]=++cnt;
			else t[a[j]]=cnt;
		}
		for (int j=0;j<m;j++) v[j]=t[j];
	}
	int ans=a[0];
	for (int i=0;i<m;i++) printf("%c",s[i^ans]);
	return 0;
}

```


---

## 作者：周子衡 (赞：15)

其他题解大部分采用了类似后缀排序中倍增的思路。笔者赛时的思路略为不同：考虑如何比较两个异或串 $T_i,T_j$ 的大小关系。这一点可以利用二分找到其第一个不同位置来实现。找位置的时候可以利用哈希确定两个子串是否完全相同。预处理时间复杂度 $O(n2^n)$，总共需要进行 $O(2^n)$ 次比较，单次比较时间复杂度 $O(n2^n)$。总时间复杂度 $O(n2^n)$。这个做法实现起来比较简单。

下面的代码为了提高正确率采用了双哈希。

```cpp
#include<cstdio>

using namespace std;

typedef unsigned long long ull;

const ull C[2]={998244353,1000000007};

int n;
char S[1<<20];

ull HASH[2][20][1<<20];
ull pw[2][1<<20];

int cmp(int x,int y)
// -1: x < y
// 0: x = y
// 1: x > y
{
	if(HASH[0][n][x]==HASH[0][n][y]&&HASH[1][n][x]==HASH[1][n][y])return 0;
	for(int j=n-1;j>=0;j--)
	{
		if(HASH[0][j][x]==HASH[0][j][y]&&HASH[1][j][x]==HASH[1][j][y])x^=(1<<j),y^=(1<<j);
	}
	return S[x]<S[y]?-1:1;
}

int main()
{
	
	scanf("%d%s",&n,S);
	pw[0][0]=pw[1][0]=1;for(int j=0;j<2;j++)for(int i=1;i<(1<<n);i++)pw[j][i]=pw[j][i-1]*C[j];
	for(int i=0;i<(1<<n);i++)HASH[0][0][i]=HASH[1][0][i]=S[i]*S[i];
	
	for(int k=0;k<2;k++)
	for(int j=1;j<=n;j++)
	{
		for(int i=0;i<(1<<n);i++)
		{
			HASH[k][j][i]=HASH[k][j-1][i]+HASH[k][j-1][i^(1<<(j-1))]*pw[k][1<<(j-1)];
		}
	}
	int ans=0;
	for(int i=1;i<(1<<n);i++)
	{
		if(cmp(ans,i)>0)ans=i;
	}
	for(int i=0;i<(1<<n);i++)putchar(S[ans^i]);
}
```

---

## 作者：Sharpsmile (赞：3)

大家好，我来带大家见证一下生物的多样性。

因为我比较愚钝，所以我只会很傻的分块做法。

首先我们暴力枚举 $j$ 的最后 $B$ 位（默认下取整，后面也一样），并尝试求出，满足最后 $B$ 是 $x$ 的所有 $j$ 中最小的串是哪个。

不难发现，确定最后 $B$ 位后，原串被剖分成了 $T=2^{n-B}$ 个串，我们需要考虑前 $n-B$ 位来最小化这个重排之后的串。

那我们对这 $T$ 个串全部对应成其排名，那么我们现在要解决的其实h和原来是一样的。不难发现我们可以在 $O(2^n\log (???))$ 的复杂度内做到为分出的串排序这件事情（串长的和是 $2^n$，字符集也认为是 $O(2^n)$。不管是直接排序还是字典树都可以）。

下面把 $n$ 和 $\log$ 当作同阶。

正常人都知道如果我们取 $B=1$，则 复杂度是 $T(n)=O(n2^n)+2T(n-1)=O(n^22^n)$。

会发现本质就是枚举 $j$，每确定一位就把对应的两个字符合并起来。

但是我 VP 的时候完全没有想到后面可以继续用同样的方法递归下去做啊，因为字符集比较小所以可以用字典树做到 $O(2^n)$ 得到对应排名。然后后面 $2^{2(n-B)}$ 跑暴力。复杂度是 $O(2^B(2^n+2^{2(n-B)}))=O(2^{B+n}+2^{2n-B})$，取 $B=\frac{n}{2}$ 即可得到 $O(2^{\frac{3n}{2})}$ 的超绝复杂度。理论上 $2^{27}$ 大约是 $10^8$，感觉能过。

然而现实比较悲伤，字典树访问不连续（也有可能是我写的太烂了）常数爆炸，跑不动。

我们把字典树换成直接排序，内存访问相对连续，复杂度是 $O(2^{\frac{3n}{2}}(n-B))$。随机数据下跑的飞快，本地测只需要 $300ms$。最慢的情况应该是所有字符都一样（这样字符串比较会跑满），本地测也只要 $350ms$。

交上去过了，$1000ms$。

---

## 作者：daniEl_lElE (赞：3)

考虑 $dp_{i,j}$ 表示 $s_{j\oplus0},s_{j\oplus1},s_{j\oplus2},\dots,s_{j\oplus i}$ 在所有 $j=0\sim2^n-1$ 中的字典序排名。考虑转移，不难发现 $dp_{i,j}$ 所表示的字符串由 $dp_{i-1,j}$ 和 $dp_{i-1,j\oplus2^i}$ 拼接而成。故可以用 `pair` 存储直接 `sort` 即可。最后只需要找 $dp_{n,j}$ 最小的 $j$ 作为答案。复杂度为 $O(2^nn^2)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int rk[1000005];
pair<pair<int,int>,int> pr[1000005];
signed main(){
	int n; cin>>n;
	string s; cin>>s;
	for(int i=0;i<(1<<n);i++){
		rk[i]=s[i]-'a';
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<(1<<n);j++) pr[j].first.first=rk[j],pr[j].first.second=rk[j^(1<<i)],pr[j].second=j;
		sort(pr,pr+(1<<n));
		rk[pr[0].second]=0;
		for(int j=1;j<(1<<n);j++) rk[pr[j].second]=((pr[j].first.first!=pr[j-1].first.first)||(pr[j].first.second!=pr[j-1].first.second))+rk[pr[j-1].second];
	}
	int minp=0;
	for(int i=0;i<(1<<n);i++){
		if(rk[i]==0) minp=i;
	}
	for(int i=0;i<(1<<n);i++) cout<<s[i^minp];
	return 0;
}
```

---

## 作者：WeLikeStudying (赞：3)

- 纸上得来终觉浅。
- 我曾经苦思许久，但却不如一个样例的手推来得轻松简单。

**题意**
- [链接](https://www.luogu.com.cn/problem/CF1654F)。
- 给定一个长度为 $2^n$ 的串 $a$，定义该串的“$j$ 变换”为新串 $c$ 满足 $c(i)=a(i\operatorname{xor} j)$，求该串字典序最小的“$j$ 变换”。
- $n\le 18$。

**分析**
- 我们给出原题没有给的样例解释：
$$n=3,a=\texttt{bcbaaabb}$$
$$j=1,c=\texttt{cbabaabb}$$
$$j=2,c=\texttt{babcbbaa}$$
$$\cdots$$
$$j=4,c=\texttt{aabbbcba}$$
$$\cdots$$
- 发现了什么？当 $j=2^i$ 的时候，相当于大小为 $2^i$ 的段在奇偶块交换！
- 怎么利用这个性质，考虑 $j$ 的最高位是否有 $1$，也就是将原字符串拆成两段考虑，求出一个 $j$ 优先使得前面的字典序最小，然后再求出一个 $j$ 优先使得后面的字典序最小……
- 这好吗，这不好。因为子问题相关！我们可以先求出一个最小的 $j$，然后在这个基础上让整个串最小化，但是这样复杂度会很不对劲。
- 我的天哪，这个性质是不是没用了。
- 不要慌张，这个性质还是挺好的，只不过我们的延伸太垃圾了，我们想想一般的情况，如何构造 $j$ 变换，然后我们发现是 $j$ 变换的 $2^{n-1}$ 前缀与 $j\oplus 2^{n-1}$ 变换的 $2^{n-1}$ 前缀拼接而成的，所以我们就可以用[后缀排序](https://www.luogu.com.cn/problem/P3809)的方法来倍增求，代码实现大概就是抄一遍后缀排序的模板，时间复杂度可以是 $O(n\log^2n)$ 到 $O(n\log n)$ 但并不清楚线性的后缀排序方法是否也可以应用在这里。
- 很有趣的是，这个方法可以将所有的变换在相同的复杂度内排序，就像我们找最小循环移位所发生的事情那样。
- [代码实现](https://www.luogu.com.cn/paste/37rt7bik)。

---

## 作者：Take_A_Single_6 (赞：2)

首先看到这题上来给了一个 $2^n$ ，所以我们考虑能否倍增地做这道题。  
集中注意力，我们可以设计 $s(x,l)$ 表示前 $2^l$ 个字符下标异或 $x$ 组成的字符串，那么  
$$s(x,l+1) = s(x,l) + s(x \oplus 2^l,l)$$  
理解一下，前 $2^l$ 个字符可以直接得到，而 $2^l + 1$ 至 $2^{l+1}$ 个字符需要由前 $2^l$ 个字符下标异或别的值得到。因为这些下标肯定小于 $2^l$ ，所以由异或运算的结合律可以得到
$$(i + 2^l) \oplus x = (i \oplus 2^l) \oplus x = i \oplus (2^l \oplus x)$$  
然后我们就可以按照后缀数组的方法排序，双 $\log$ 可以过掉，用快排就好。
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX% 10 + '0');
}
int n,m,rk[maxn],ls[maxn],id[maxn],len;//rk表示异或i的排名，ls作为备份，id表示排名为i的异或值
char ss[maxn];
bool cmp(int x,int y)
{
	if(rk[x]==rk[y])return rk[x^len]<rk[y^len];//前一半一样比后一半，注意如果相等会返回false，后面会用
	else return rk[x]<rk[y];
}
signed main()
{
	n=read(),m=(1<<n);
	cin>>ss;
	for(int i=0;i<m;i++)id[i]=i,rk[i]=ss[i];
	sort(id,id+m,cmp);
	for(int i=0,p;i<n;i++)
	{
		len=(1<<i),sort(id,id+m,cmp),ls[id[0]]=p=0;
		for(int j=1;j<m;j++)ls[id[j]]=(cmp(id[j-1],id[j])?++p:p);//p表示不同字符串的个数
		for(int j=0;j<m;j++)rk[j]=ls[j];
	}
	for(int i=0;i<m;i++)putchar(ss[i^id[0]]);
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：2)

诈骗题，这个题放前面不知道能多少人切（

考虑问题与字符串的字典序相关，且字符串的长度是 $2$ 的次幂，不难联想到后缀排序，这个能解决字符串排序并且**与倍增长度相关**的算法。

~~刚开始给龙鱼说有规律龙鱼还不信。~~

出于乱搞选手的直觉，先打个表，找规律，我们以 $n = 2 ^ 3 = 8$ 打一个表，看当 $j = 0,1,......7$ 时的下标都长啥样。

```
8
#0
0 1 2 3 4 5 6 7
#1
1 0 3 2 5 4 7 6
#2
2 3 0 1 6 7 4 5
#3
3 2 1 0 7 6 5 4
#4
4 5 6 7 0 1 2 3
#5
5 4 7 6 1 0 3 2
#6
6 7 4 5 2 3 0 1
#7
7 6 5 4 3 2 1 0
```

通过观察，我们发现假设当前排好的是每个字符串的前 $2 ^ i$ 个字符，那么在将 $s[0 , 2 ^ i - 1]$ 与 $s[2 ^ i , 2 ^ {i + 1} - 1]$ 两部分拼起来的时候，对于每个 $j$ 的 $s[2 ^ i , 2 ^ {i + 1} - 1]$ 部分，它总是**另一个 $j$ 的 $s[0 , 2 ^ i - 1]$ 部分**。

进一步观察，假设当前是对前 $2 ^ i$ 的字符排序，那么相当于对所有 $j$ 以 $2 ^ i$ 大小分组，每组内相邻 $2 ^ {i - 1}$ 距离的两个 $j$ **它们的前缀信息是彼此的后缀信息**。

然后这道题就做完了，写 $O(n \log ^ 2 n)$ 就可以通过，写 $O(n \log n)$ 写挂了就得不偿失了。

```cpp
/*
月亮静静地诉说着
用谁也无法听到的声音
潮起潮落
失去的记忆光景
群星悄悄地记录着
用谁也无法解读的文字
无限的言语形成漩涡
孕育出千亿册书
对我而言 天空一望无垠
时间转瞬即逝
一无所知的空虚
语言的集合
只能在土中腐朽而去
即便如此 我也要呐喊
不明所以地呼喊
也要让喊声响彻天际
太阳终将升起吧
卑屈的黑暗回答道
没有人能预见未来
我将手伸向天空
抓住冷冽的风
将绝望吹散吧
梦想也好 苦恼也罢 将所有带向过去
在沉睡于地上的黎明之中
我将会继续前进
向着还未见到的明天
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
int ht[Len],n,m,id[Len],rk[Len],sa[Len],cnt[Len],px[Len],odrk[Len],p;
char s[Len];
struct Node
{
	int x,y,id;
	Node(){x = y = id = 0;}
	Node(int X,int Y,int ID){x = X , y = Y , id = ID;}
}sk[Len];
bool cmp(Node x,Node y)
{
	if(x.x == y.x) return x.y < y.y;
	return x.x < y.x;
}
int main()
{
	scanf("%d",&n);
	n = 1 << n;
	scanf("%s",s);
	m = max(300 , n);
	for(int i = 0 ; i < n ; i ++) ++ cnt[rk[i] = s[i ^ 0]];
	for(int i = 1 ; i <= m ; i ++) cnt[i] += cnt[i - 1];
	for(int i = 0 ; i < n ; i ++) rk[i] = cnt[s[i ^ 0] - 1] + 1;
	for(int w = 1 ; w < n ; w <<= 1)//对于 2w 长度的串排序 
	{
	 	//相当于 2w 组内交换分配 
	 	for(int i = 0 ; i < n ; i ++) sk[i].x = sk[i].y = 0 , sk[i].id = i;
	 	for(int i = 0 ; i < n ; i += (w + w)) 
		{
			int di = i;
			for(int j = i ; j < i + w + w ; j ++) 
			{
				int now = j - di;
				if(now < w) sk[j].y = rk[j + w];
				else sk[j].y = rk[j - w];
				sk[j].x = rk[j];
			}
		}
		sort(sk , sk + n , cmp);
		int rkk = 1;
		rk[sk[0].id] = rkk;
		for(int i = 1 ; i < n ; i ++) 
		{
			if(sk[i].x == sk[i - 1].x && sk[i].y == sk[i - 1].y);
			else rkk ++;
			rk[sk[i].id] = rkk;
		}
	}
	//for(int i = 0 ; i < n ; i ++) printf("%d %d\n",i,rk[i]);
	for(int i = 0 ; i < n ; i ++) 
	{
		if(rk[i] == 1)
		{
			//printf("%d\n",i);
			for(int j = 0 ; j < n ; j ++) putchar(s[i ^ j]);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：juicyyou (赞：2)

相当诈骗，不过挺有意思的。

考虑按位确定最优的 $x$，我们首先有一个最显然的暴力，按顺序确定每一位，如果这一位确定为 1，那么就按照 $\operatorname{xor}$ 的运算把当前序列进行一个变换。复杂度是 $O(4^n)$，很显然过不去。

但是我们考虑从低位到高位考虑，我们发现，在确定第 $t$ 位时，前面 $t - 1$ 位已经确定，那么实际上序列可以被划分成一些长度为 $2^{t - 1}$ 的段，这些段内部的顺序在之后的过程中不会被改变。

于是我们直接把这些段按照字典序顺序排序，然后用一个段的 $\operatorname{Rank}$ 来替代这一段接着往下做。注意到该过程类似于 SA 的排序，所以使用基数排序即可。那么每次长度减半，那么复杂度就是 $T(k) = 2T(k - 1) + O(2^k)$，就有 $T(n) = O(n2^n)$，可以通过。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = (1 << 18) + 5;
int n; char s[maxn]; int N = 0;
int cnt[maxn]; int tmp[maxn], id[maxn];
int rk[maxn];
int tid[maxn];
typedef pair<int, int> pii;
#define fi first
#define sc second 
#define mkp make_pair
void psort(vector<pii> p){
    int len = p.size(); int maxv = (len << 1);
    for(int i = 0;i < maxv;i++) cnt[i] = 0;
    for(int i = 0;i < len;i++) cnt[p[i].sc]++;
    for(int i = 1;i < maxv;i++) cnt[i] += cnt[i - 1];
    for(int i = len - 1;i >= 0;i--) tmp[--cnt[p[i].sc]] = i;
    for(int i = 0;i < maxv;i++) cnt[i] = 0;
    for(int i = 0;i < len;i++) cnt[p[tmp[i]].fi]++;
    for(int i = 1;i < maxv;i++) cnt[i] += cnt[i - 1];
    for(int i = len - 1;i >= 0;i--) id[--cnt[p[tmp[i]].fi]] = tmp[i];
    int M = 0; rk[id[0]] = 0; tid[0] = id[0];
    for(int i = 1;i < len;i++){
        rk[id[i]] = (p[id[i - 1]] == p[id[i]]) ? M : ++M;
        tid[rk[id[i]]] = id[i];
        // cout << rk[id[i]] << " " << id[i] << endl;
    }
    return ;
}
vector<int> solve(vector<int> &p){
    int len = p.size(); int plen = (len >> 1);
    if(len == 1){
        return p;
    }
    vector<pii> lw;
    for(int i = 0;i < len;i += 2){
        lw.emplace_back(p[i], p[i + 1]);
    }
    psort(lw); vector<int> ls, lv;
    for(int i = 0;i < plen;i++){
        ls.push_back(rk[i]); lv.push_back(tid[i]);
    }
    vector<int> resl = solve(ls);
    vector<pii> rw;
    for(int i = 0;i < len;i += 2){
        rw.emplace_back(p[i + 1], p[i]);
    }
    psort(rw); vector<int> rs, rv;
    for(int i = 0;i < plen;i++){
        rs.push_back(rk[i]); rv.push_back(tid[i]);
    }
    vector<int> resr = solve(rs); vector<int> ansl, ansr;
    for(int i = 0;i < plen;i++){
        ansl.push_back(p[lv[resl[i]] << 1]); ansl.push_back(p[lv[resl[i]] << 1 | 1]);
        ansr.push_back(p[rv[resr[i]] << 1 | 1]); ansr.push_back(p[rv[resr[i]] << 1]);
    }
    // cout << len << endl; cout << tid[0] << endl;
    return min(ansl, ansr);
}
bool vis[maxn]; int ch[maxn];
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> s; N = (1 << n); 
    for(int i = 0;i < N;i++){
        vis[s[i] - 'a'] = 1;
    }
    int M = 0;
    for(int i = 0;i < 26;i++){
        if(vis[i]){
            rk[i] = M++; ch[rk[i]] = i;
        }
    }
    vector<int> nd;
    for(int i = 0;i < N;i++){
        nd.push_back(rk[s[i] - 'a']);
    }
    vector<int> ans = solve(nd);
    for(int i = 0;i < N;i++){
        cout << (char)(ch[ans[i]] + 'a');
    }
    cout << endl; return 0;
}

```

---

## 作者：Erica_N_Contina (赞：1)

我们仿造后缀数组的写法。当然，如果你没学过后缀数组，也可以看本篇题解。



我们定义数组 $sa_{i,j}$ 表示：考虑了前 $2^i$ 个字符时，选 $sa_{i,j}$ 作为异或值（就是拿来异或下标的那个数）时字符串 $t$（即 $t$ 的前 $2^i$ 个字符）在所有异或值的情况中字典序排名为 $j$。

我们从 $1$ 到 $n$ 枚举 $i$。因为我们不需要在不同的 $i$ 之间转移，所以可以去掉 $sa$ 的第一维。

这里我们还需要一个数组 $ord$，$ord_j$ 代表的是选 $j$ 为异或值时，$t$ 中长度为 $2^i$ 的前缀，在所有异或值选取情况中，$t$ 长度为 $2^i$ 的前缀里的排名。这里一样是省略了第一维。



现在我们就可以开始实现 `cmp` 函数，来对我们的 $sa$ 数组进行排序了。我们倍增地合并前缀，直到求出最后的结果。

我们要合并两个子串 $A,B$（$A$ 在先），并且比较是将 $a$ 作为异或值的 $A+B$ 字典序小，还是将 $b$ 作为异或值的 $A+B$ 字典序小。

这里给出一个递推式：

$f(x,k)$ 表示以 $x$ 为异或值，长度为 $2^k$ 的前缀，有：

$f(x,k)=f(x,k−1)~ \text{connect} ~f(x ~\text{xor}~ 2 ^{k−1} ,k−1)$

此处不再证明。

此处假设我们比较 $a,b$ 哪个作为异或值更加优秀（`cmp` 函数总要传入两个数比较咯，这里的 $a,b$ 具体来说是 $sa_a,sa_b$，$a,b$ 是任意下标）。

先比较两种情况的 $A$ 的大小，若相等，再比较 $B$。这里我们使用 $ord$ 数组比较即可。

根据 $ord$ 数组，$ord_a$ 就是 $A$ 的排名。由 $f$ 递推式得：$ord_{a~\text{xor}~2^{i}}$可以代表 $B$ 的排名。

（注意不能用 `char s[]` 替代 `int ord[]`，因为存不下）



最后我们来考虑如何处理出 $ord$ 数组。假设我们要将状态长度为 $2^{i-1}$ 的前缀转移到长度为 $2^{i}$ 的前缀，那么我们在对 $sa$ 排序后就得到了长度为 $2^{i-1}$ 的前缀状态下的 $sa$ 的排序了。

此时我们从前往后扫一遍 $sa$ 数组，然后记录以下排名即可。之所以只需要考虑相邻两项，是因为之前已经排序了，所以要么相等，要么后面比前面大。



```C++
/*                                                                                
                      Keyblinds Guide
     				###################
      @Ntsc 2024

      - Ctrl+Alt+G then P : Enter luogu problem details
      - Ctrl+Alt+B : Run all cases in CPH
      - ctrl+D : choose this and dump to the next
      - ctrl+Shift+L : choose all like this
      - ctrl+K then ctrl+W: close all
      - Alt+la/ra : move mouse to pre/nxt pos'
	  
*/

string s,ori;
int sa[N];
int t[N];
int ord[N];
int cur;

bool cmp(int a,int b){
    //我们要合并两个子串i,j
    //f(x,k)表示以x为异或值，长度为2^k的前缀
    //f(x,k)=f(x,k−1) connect f(x xor 2 ^{k−1} ,k−1)
    //此处我们比较a,b那个作为异或值更加优秀
    //先比较i，相等再比较j
    //注意的是我们这里的ord_a代表的是选a为异或值时，长度为2^i的前缀，在所有长度为2^i的前缀里的排名
    //参考cnt代码
    //由f递推式得：ord[a^(1<<cur)]可以代表j
    //注意不能用char *s[]替代ord[]，因为存不下
    if(ord[a]==ord[b])return ord[a^(1<<cur)]<ord[b^(1<<cur)];
    return ord[a]<ord[b];
}


signed main(){
    int n=rd;
    cin>>s;
    itn m=1<<n;

    ori=s;

    //下标从0开始
    for(int j=0;j<m;j++){
        sa[j]=j;
        ord[j]=s[j]-'a';
        //sa_j代表：考虑了前2^i个字符时（i见下），选sa_j作为异或值时字符串排名为i
    }
    sort(sa,sa+m,cmp);


    for(int i=0;i<n;i++){
        cur=i;
        sort(sa,sa+m,cmp);

        itn cnt=0;

        //开始对于每一个候选异或值，处理出拼接后的前缀的排序
        for(int j=0;j<m;j++){
            if(!j||cmp(sa[j-1],sa[j]))t[sa[j]]=++cnt;
            //之所以只需要考虑相邻两项，是因为之前已经排序了，所以要么相等，要么后面比前面大。
            else t[sa[j]]=cnt;
        }

        for(int j=0;j<m;j++){
            ord[j]=t[j];
        }
    }


    for(int i=0;i<m;i++){
        putchar(ori[i^sa[0]]);
    }

}
```

---

## 作者：lfxxx (赞：0)

字符串趣题。

比较字符串大小的常见方法是二分出最长公共前缀，但在本题中不太可做，所以我们转而考虑另一种比较方法——类似于 SA 求法的倍增法。

具体而言，不妨设计 $rk_{i,j}$ 表示异或上的数是 $i$ 时字符串的前 $2^{j}$ 位在所有可能的字符串的前 $2^j$ 位中的排名，然后你发现你要比较 $rk_{i,j},rk_{k,j}$ 的大小就是比较 $S\{i \oplus 0,...,i \oplus 2^j-1\},S\{k \oplus 0,...,k \oplus 2^j-1\}$，考虑将当前的字符串拆解为两个已经处理出的小字符串，你发现 $S\{i \oplus 0,...,i \oplus 2^j-1\} = S\{i \oplus 0,...,i \oplus 2^{j-1}-1\} + S\{i \oplus 2^{j-1},...,i \oplus 2^j-1\}$，注意力集中一下，你发现异或 $i \oplus 2^{j-1}$ 的前 $2^{j-1}$ 个字符刚好也是 $S\{i \oplus 2^{j-1},...,i \oplus 2^j-1\}$，所以比较 $rk_{i,j},rk_{k,j}$ 就是比较二元组 $(rk_{i,j-1},rk_{i \oplus 2^{j-1},j-1}),(rk_{k,j-1},rk_{k \oplus 2^{j-1},j-1})$，所以一层一层的排序即可做到 $O(n^2 \times 2^n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = (1<<18);
int n;
string S;
int rk[maxn];
pair< pair<int,int>,int > a[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	cin>>S;
	for(int i=0;i<(1<<n);i++) a[i]=make_pair(make_pair((int)S[i],(int)S[i]),i);
	sort(a,a+(1<<n));
	rk[a[0].second]=0;
	for(int i=1;i<(1<<n);i++) rk[a[i].second]=(a[i].first==a[i-1].first?rk[a[i-1].second]:rk[a[i-1].second]+1);
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<n);j++) a[j]=make_pair(make_pair(rk[j],rk[j^(1<<(i-1))]),j);
		sort(a,a+(1<<n));
		rk[a[0].second]=0;
		for(int j=1;j<(1<<n);j++) rk[a[j].second]=(a[j].first==a[j-1].first?rk[a[j-1].second]:rk[a[j-1].second]+1);
	}
	int x=a[0].second;
	for(int i=0;i<(1<<n);i++) cout<<S[i^x];
	return 0;
}
```

---

## 作者：不知名用户 (赞：0)

题意：给定长度为 $2^n$ 的序列 $a$，找出 $0\le x<2^n$ 使得序列 $a_{0\oplus x},a_{1\oplus x},\cdots a_{(2^n-1)\oplus x}$ 的字典序最小。

考虑像后缀排序一样不断倍增长度。用 $f(x,i)(0\le x<2^i)$ 表示 $a_{0\oplus x},a_{1\oplus x},\cdots,a_{2^i\oplus x}$。考虑由 $f(*,i-1)\to f(x,i)$ 的转移。

前 $2^{x-1}$ 位是 $f(x,i-1)$。考虑后 $2^{i-1}$ 位的某个数 $j$，$x\oplus j=x\oplus((j-2^{i-1})\oplus 2^{i-1})=(x\oplus 2^{i-1})\oplus(j-2^{i-1})$，$j-2^{i-1}$ 表示 $j$ 往左边推了 $2^{i-1}$ 个位置。所以 $f(x,i)=f(x,i-1)+f(x\oplus2^{i-1},i-1)$，加号表示拼接。

归纳一下。归纳我们已经得到了 $f(x,i-1)$ 的顺序，那么 $f(x,i)$ 的顺序就是以 $f(x,i-1)$ 为第一关键字，$f(x\oplus2^{i-1},i-1)$ 为第二关键字排序后的顺序。和 SA 唯一的不同是 $f(x+2^{i-1})$ 变成了 $f(x\oplus2^{i-1})$。

输出就用最小的 $f(x,n)$ 作为 $x$。

因为 $x\oplus2^{i-1}<2^n$，代码比 SA 好写很多倍。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1<<19], v[1<<19], vv[1<<19], p[1<<19], cur, l;
bool cmp(int x, int y)
{
	if(v[x]!=v[y]) return v[x] < v[y];
	return v[x^l] < v[y^l];
}

int main()
{
	int n, i, j;
	scanf("%d", &n);getchar();
	for(i=0;i<(1<<n);i++) scanf("%c", &a[i]), v[i] = a[i], p[i] = i;
	stable_sort(&p[0],&p[(1<<n)-1]+1,cmp);
	for(l=1;l<(1<<n);l<<=1)
	{
		stable_sort(&p[0],&p[(1<<n)-1]+1,cmp);
		vv[p[0]] = cur = 0;
		for(j=1;j<(1<<n);j++) if(cmp(p[j-1],p[j])) vv[p[j]] = ++cur;else vv[p[j]] = cur;
		for(j=0;j<(1<<n);j++) v[j] = vv[j];
	}
	for(i=0;i<(1<<n);i++) printf("%c", a[i^p[0]]);
	return 0;
}
```

---

