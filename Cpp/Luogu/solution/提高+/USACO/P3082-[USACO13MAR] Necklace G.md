# [USACO13MAR] Necklace G

## 题目描述

Bessie the cow has arranged a string of N rocks, each containing a single letter of the alphabet, that she wants to build into a fashionable necklace.

Being protective of her belongings, Bessie does not want to share her necklace with the other cow currently living on her side of the barn.  The other cow has a name that is a string of M characters, and Bessie wants to be sure that this length-M string does not occur as a contiguous substring anywhere within the string representing her necklace (otherwise, the other cow might mistakenly think the necklace is for her).  Bessie decides to remove some of the rocks in her necklace so that the other cow's name does not appear as a substring.  Please help Bessie determine the minimum number of rocks she must remove.

贝西收集了N颗石头，每颗石头上都有一个字母，贝西想把这些石头做成项链。

贝西的身边有另一只奶牛，这只奶牛的名字是一个长度为M的字符串，贝西不希望这只牛的名字出现在她的项链上(项链的子串)，她想知道，最少删掉几颗石头就可以避免这种情况发生。


## 说明/提示

```cpp
For at least 20% of test cases, N <= 20. 
For at least 60% of test cases, N <= 1000, M <= 100. 
For all test cases, N <= 10000, M <= 1000. 
For all test cases, M <= N. 
```
The modified necklace should be "abbaa".

---

$\text{upd 2022.7.29}$：新增加一组 Hack 数据。

## 样例 #1

### 输入

```
ababaa 
aba 
```

### 输出

```
1 
```

# 题解

## 作者：¶凉笙 (赞：11)

## [题解] [USACO13MAR]Necklace G

> [传送门](https://www.luogu.com.cn/problem/P3082)

### 前置知识

- AC 自动机。

如果你不会，可以看看 [这篇文章](https://www.luogu.com.cn/blog/AG-Liangsheng/post-mu-ban-ac-zi-dong-ji)（我不会告诉你我是来推销博客的。

请确保您已经学会 AC 自动机。

### 解题报告

对于题中的两个字符串，显然奶牛的名字是模式串，我们先把它插入到 AC 自动机中。

没有什么正确的贪心做法，因此考虑 DP。

设题目中项链的字符串为 $S$，奶牛的名字为 $S'$， $f[i,j]$ 表示已经考虑了 $S$ 的前 $i$ 个字符，在 AC 自动机上对应的第 $j$ 个结点的最大保留长度。

- 设 $nxt$ 为上一个结点 $j$ 的 $i$ 指针，如果指向的不是 $S'$ 结束的位置，那么 $f[i,nxt]=max(f[i,nxt],f[i-1][j]+1)$ 。

- 同样地，如果当前位置不是 $S'$ 的结束位置，那么 $f[i,j]=max(f[i,j],f[i-1][j])$。

最后答案取个 max，用总长度减去就好了。

```c++
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
template <typename T>
inline T read(){
	T x=0;char ch=getchar();bool fl=false;
	while(!isdigit(ch)){if(ch=='-')fl=true;ch=getchar();}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);ch=getchar();
	}
	return fl?-x:x;
}
#include <queue>
const int maxn = 1000 + 10;
int f[maxn*10][maxn];
namespace AC{
int t[maxn][26],fail[maxn],end[maxn],cnt=0;
void insert(char *s){
	int u=0;
	for(int i=1;s[i];i++){
		if(!t[u][s[i]-'a'])t[u][s[i]-'a']=++cnt;
		u=t[u][s[i]-'a'];
	}
	end[u]=1;
}
queue<int> q;
void build(){
	for(int i=0;i<26;i++)if(t[0][i])q.push(t[0][i]);
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(t[u][i])fail[t[u][i]]=t[fail[u]][i],q.push(t[u][i]);
			else t[u][i]=t[fail[u]][i];
		}
	}
}
}
using namespace AC;
char s[maxn],T[maxn*10];
int main(){
	cin>>T+1>>s+1;
	insert(s);build();
	int len=strlen(T+1);
	for(int i=1;i<=len;i++){
		for(int j=0;j<=cnt;j++){
			if(!end[t[j][T[i]-'a']])
				f[i][t[j][T[i]-'a']]=max(f[i][t[j][T[i]-'a']],f[i-1][j]+1);
			if(!end[j])
				f[i][j]=max(f[i][j],f[i-1][j]);
		}
	}
	int ans=0;
	for(int i=0;i<=cnt;i++)ans=max(ans,f[len][i]);
	printf("%d\n",len-ans);
	return 0;
}
```
--------------------
### 小结

个人认为 AC 自动机只是简化了 DP 的过程，并且便于理解。

本质上和其它题解的线性 DP 还是一样的。

---

## 作者：zhaoyp (赞：8)

# Solution
正难则反，将问题转化成留下一个长度最长的 $a$ 的子串，使得 $b$ 不在其中出现过。

设 $f_{i,j}$ 表示 $a$ 串前 $i$ 个字符，**正好**匹配到 $b$ 串第 $j$ 个字符，最多可保留的位数。
 
考虑从 $f_i$ 转移到 $f_{i + 1}$，转移方程为: 

$$f_{i+1,k} = \max\{f_{i+1,k},f_{i,j} + 1\}$$

其中 $k$ 表示添加了字符 $a_{i + 1}$ 之后，**正好**匹配到 $b$ 串的位置。

之后问题的难点就在于如何快速的求出每一个 $f_{i,j}$ 对应的 $k$。

记 $g_{i,j}$ 表示已经正好匹配到 $b$ 串第 $i$ 个字符，再添上字符 $j$ 所匹配到的位置，也就是上文的 $k$。

先对 $b$ 串跑一边 $\text{KMP}$，预处理出 $next$ 数组，考虑 $g$
的转移。

$$g_{i,j} = \begin{cases} i + 1 &b_{i + 1} = j\\g_{next_i,j} & otherwise \end{cases}$$

综上有：
$$f_{i+1,g_{j,a_{i + 1}}} = \max\{f_{i+1,g_{j,a_{i + 1}}},f_{i,j} + 1\}$$
初值：
$$f_{i,j} = f_{i - 1,j}$$

时间复杂度 $O(nm)$。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 5;
const int maxm = 1e3 + 5;
int n,m,f[maxn][maxm],ans,g[maxm][30],kmp[maxm];
char a[maxn],b[maxm];
void input()
{
	scanf("%s%s",a + 1,b + 1);
	n = strlen(a + 1),m = strlen(b + 1);
}
void prefix()
{
	int j = 0;
	for(int i = 2;i <= m;i++)
	{
		while(j&&b[i] != b[j + 1])
			j = kmp[j];
		kmp[i] = b[i] == b[j + 1] ? ++j : 0;
	}
	for(int i = 0;i < m;i++)
		for(int j = 1;j <= 26;j++)
			g[i][j] = (b[i + 1] == j + 'a' - 1) ? i + 1 : g[kmp[i]][j];
}
void DP()
{
	for(int i = 0;i < n;i++)
	{
		if(i)
			for(int j = 0;j < m;j++)
				f[i][j] = max(f[i][j],f[i - 1][j]);
		for(int j = 0;j < m;j++)
				f[i + 1][g[j][a[i + 1] - 'a' + 1]] = max(f[i + 1][g[j][a[i + 1] - 'a' + 1]],f[i][j] + 1);
	}
}
void output()
{
	for(int i = 0;i < m;i++)
		ans = max(ans,f[n][i]);
	printf("%d",n - ans);
}
int main()
{
	input();
	prefix();
	DP();
	output();
	return 0 ;
}
```

---

## 作者：foreverlasting (赞：5)

首先先放一波官方题解：

由于在计算满足某些准则的子序列个数时常常是这样的，所以这个问题的解决方案使用动态规划。假设代表Bessie项链的初始字符串是S，而另一个奶牛的名字是T。对于每一个i，我们想计算S[1..i]的子序列的数目。一种可能是记住我们所选择的子序列的最后一个|T|-1个字母，这是我们在添加一个字母时能够更新的东西，它也允许我们确定是否包含T作为子串。



不幸的是，所提出的方法中的状态数在|T|中是指数的，因此对于我们的需求来说太大了。也许我们不在乎最后的|T|-1字母到底是什么？事实上，这就足以知道它们是如何“相似”的。在这里，相似性的正确度量是这些字母的最长后缀，也就是T的一些前缀。这也是我们在状态转换时可以保持的信息，并且它还允许我们确定所选的序列包含T作为子串。



为了加速状态转换，在匹配T[1..j]和添加任何字母C之后预先计算包含的T的前缀可能是有用的。这给了我们一个A*|T|状态转换，其中A＝26是字母表的大小。

我们的解的总复杂度是O(A*|T|*|T|+|S|*|T|)，如果我们只是预先计算过渡。虽然这是足够快的，它实际上是一样容易预先计算与DP的过渡，减少复杂度到O(A*|T|+|T|*|S|)。

然后是自我理解：

根本就是一道DP好吧。于是就好了

code：
```
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define res register int
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read() {
    res s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(res x) {
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int N=1e4+10;
string S,s;
int n,m;
int next[N][30],dp[N],f[N];
int main() {
    cin>>S>>s;
    n=S.size(),m=s.size();
    for(res i=0; i<n; i++)S[i]-='a';
    for(res i=0; i<m; i++)s[i]-='a';
    for(res i=1; i<m; i++) {
        res prev=next[i-1][s[i-1]];
        next[i-1][s[i-1]]=i;
        for(res j=0; j<26; j++)next[i][j]=next[prev][j];
    }
    next[m-1][s[m-1]]=m;
    for(res i=0;i<m;i++){
        for(res j=0;j<26;j++)printf("%d ",next[i][j]);
        puts("");
    }
    dp[0]=0;
    for(res i=0; i<n; i++) {
        for(res j=0; j<m; j++) {
            res cur=next[j][S[i]];
            f[cur]=max(f[cur],dp[j]+1);
        }
        memcpy(dp,f,sizeof(dp));
    }
    res result=0;
    for(res i=0; i<m; i++)result=max(result, dp[i]);
    write(n-result);
    return 0;
}
```



---

## 作者：船酱魔王 (赞：2)

# P3082 [USACO13MAR] Necklace G 题解

## 题意回顾

给定长度为 $ n $ 的字符串 $ S $ 和长度为 $ m $ 的字符串 $ T $，在 $ S $ 中删除最少数量的字符使 $ T $ 不在 $ S $ 中作为一个子串出现，输出这个最少数量。

$ n \le 10^4 $，$ m \le 10^3 $。

## 分析

一道典型的 KMP 题。

建立数组 $ pre $，$ pre_{i,j} $ 表示 $ T $ 的前 $ i $ 个字符加上字符 $ j $ 后同时是 $ T $ 的前缀的最长后缀。用 KMP 算法易求。

设计动态规划状态，$ dp_{i,j} $ 表示 $ S $ 的前 $ i $ 个字符在若干次删除操作后的最长等于 $ T $ 的前缀的后缀长度为 $ j $ 时最少删除的字符数。

使用主动转移，$ dp_{i,j}+1 $ 转移到 $ dp_{i+1,j} $ 表示删去第 $ i+1 $ 个字符。$ dp_{i,j} $ 转移到 $ dp_{i+1,pre_{j,s_{i+1}}} $，表示不删去第 $ i+1 $ 个字符。

$ \min\{dp_{n,j}\}(0\le j < m) $ 即为答案。

注意可以将寻找最长相等前后缀封装成一个函数 ```findnxt(i,j)``` 表示寻找在 $ T $ 的前 $ i $ 个字符后面接上字符 $ j $ 后的最长匹配。

注意不能转移到 $ dp_{i,m} $，因为已经完整的匹配了字符串 $ T $，是不合法情况。

## AC 代码

```
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e4 + 5;
const int M = 1e3 + 5;
const int inf = 1e9 + 5;
string s, t;
int n, m;
int d[M];
int pre[M][32];
int dp[N][M];
int findnxt(int ps, char ch) {
	int j1 = ps;
	while(j1 > 0 && t[j1 + 1] != ch) {
		j1 = d[j1];
	}
	if(t[j1 + 1] == ch) {
		return j1 + 1;
	}
	return 0;
}
int main() {
	cin >> s >> t;
	n = s.size();
	m = t.size();
	s = " " + s;
	t = " " + t;
	d[0] = 0;
	d[1] = 0;
	for(int i = 2; i <= m; i++) {
		d[i] = findnxt(d[i - 1], t[i]);
	}
	for(int i = 0; i < m; i++) {
		for(int j = 'a'; j <= 'z'; j++) {
			pre[i][j - 'a'] = findnxt(i, j);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < m; j++) {
			dp[i][j] = inf;
		}
	}
	dp[1][pre[0][s[1] - 'a']] = 0;
	dp[1][0] = min(dp[1][0], 1);
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < m; j++) {
			//cout << i << " " << j << " " << dp[i][j] << " " << pre[j][s[i + 1] - 'a'] << endl; 
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
			dp[i + 1][pre[j][s[i + 1] - 'a']] = min(dp[i + 1][pre[j][s[i + 1] - 'a']], dp[i][j]);
		}
	}
	int ans = inf;
	for(int j = 0; j < m; j++) {
		ans = min(ans, dp[n][j]);
	}
	cout << ans << endl;
	return 0;
} 
```

## 总结与评价

校内省选练习赛的第一题，感觉是一个较为基础的 KMP 练习题。

---

## 作者：lyhqwq (赞：2)

# Solution
为了方便，在下文中我们规定：石头上的字母叫做 $a$，奶牛的名字叫做 $b$。

我们要删除一个字符串，当且仅当存在一个字符串和模式串匹配。所以我们要让文本串中没有与模式串匹配的子串。这样问题就转变为了一个字符串匹配问题。

我们令 $f_{i,j}$ 表示当前考虑到了 $a$ 的第 $i$ 位，匹配了 $b$ 的前 $j$ 位，要删除的最少的字符数量。

我们考虑 $f_{i,j}$ 可以转移到哪里。

若 $a_{i+1}$ 不删，那么可以转移到 $f_{i+1,to_{j,a_{i+1}}}$。

其中 $to_{j,k}$ 表示已经匹配到了模式串的第 $j$ 位，新的字符为 $k$，之后可以匹配到模式串的第几位。

若 $a_{i+1}$ 删，那么可以转移到 $f_{i+1,j}$。

对于 $to_{j,k}$ 的求解过程，可以先通过 kmp 算法计算出 $next$ 数组（在我的代码中叫做 $pi$ 数组），之后通过 $next$ 数组来计算。

因为文本串中不能出现模式串，故最后答案为 $\min_{i=0}^{m-1}f_{n,i}$。

总的时间复杂度 $O(nm)$，可以通过本题。

upd on 2023.7.20 修改了一个小笔误

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10005;
const int M=1005;
int n,m;
char a[N],b[M];
int pi[N]; 
int f[N][M],to[M][30];
void getPi(){
	pi[0]=pi[1]=0;
	for(int i=2;i<=m;i++){
		int j=pi[i-1];
		while(j&&b[j+1]!=b[i]) j=pi[j];
		pi[i]=(b[i]==b[j+1]?j+1:0);
	}
}
int getTo(int i,char j){
	if(b[i+1]==j) return i+1;
	if(!i) return 0;
	else return getTo(pi[i],j);
}
int main(){
	scanf("%s%s",a+1,b+1);
	n=strlen(a+1),m=strlen(b+1); 
	getPi();
	for(int i=0;i<m;i++){
		for(int j=0;j<26;j++){
			to[i][j]=getTo(i,'a'+j);
		}
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(to[j][a[i+1]-'a']!=m) f[i+1][to[j][a[i+1]-'a']]=min(f[i+1][to[j][a[i+1]-'a']],f[i][j]);
			f[i+1][j]=min(f[i+1][j],f[i][j]+1);
		}
	}
	int ans=0x3f3f3f3f;
	for(int i=0;i<m;i++){
		ans=min(ans,f[n][i]);
	}
	printf("%d\n",ans);
	return 0;
} 


```


---

## 作者：Parsley_ (赞：1)

暑期集训老师留了这道题，自己怎么也做不明白，看题解也一知半解，后来好歹是琢磨会了，发一篇题解，尽量写的详细些，帮助更多不明白的朋友，希望大家能看得懂。

记 $S$ 为项链原串（长度为 $n$），$T$ 为奶牛名字（长度为 $m$）。

---

首先，用 kmp 每次枚举是不现实的，虽然删除只能删除匹配到的串中的字符，但是并不可以确定删除哪个字符更优，就是有后效性，贪心不行。那就得 dp 了。

首先就得设计状态，通常设计状态都有一维是 **前 $i$ 个数** 这样的类型，比较好理解，毕竟这里的 $i$ 代表了每一个阶段。第二维就不是很好想了。题解里说：

![](https://cdn.luogu.com.cn/upload/image_hosting/endve97z.png)

话有点难懂，我翻译一下，就是：**$S$ 字符串的前 $i$ 个字符组成的前缀子串的后缀** 能和 **$T$ 字符串的前缀** 最大匹配长度为 $j$ 需要删除的最小字符个数。换句话说，就是要使 $S$ 的前 $i$ 个字符的后缀能与 $T$ 的前缀匹配长度为 $j$ 所需的最小删除字符个数。这个从 KMP 算法的角度可以更好理解。画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/pt2lxlni.png)

就是要达到这个状态的最小删除字符数。

我试着反复推敲了一下怎么想到这个维度：从前 $i$ 个数向后转移，可能会造成影响，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vw569adp.png)

当前位于 $i$ 位置，前面的橘色是某一段和 $T$ 字符串的前缀相同的后缀，那么接上蓝色段有可能凑出一个 $T$，这样就出问题了，我们要解决的就是这样的问题，肯定就要把状态往这个方向设计，于是就有这个维度了（也许不是这么想的 qwq）。

第二步就是转移了。题解里大多用的是刷表法，就是从 $i$ 向 $i+1$ 转移，也称为主动转移，确实更好理解些。

现在在 $i$ 位置（也就是考虑前 $i$ 个字符），考虑向第 $i+1$ 状态转移，

$f_{i+1,j}=\min(f_{i+1,j},f_{i,j} + 1)$ 这是删除掉第 $i+1$ 个字符的最小删除个数，显然从 $f_{i,j}$ 转移过来，删掉 $i+1$ 字符，所以 $+1$。

这个比较好想到，但是如果不删除第 $i+1$ 字符，从哪里转移呢？

首先第一维应该还是尝试从 $i$ 转移过来。但是前 $i$ 个字符的匹配长度和加上第 $i+1$ 字符之后的匹配长度没有太多关系。（这里的匹配长度还是和 $T$ 字符串的前后缀匹配长度）

我们考虑设计另一个数组 $g_{i,j}$ 表示 $T$ 中前 $i$ 个字符加上 字符 $j$（$j$ 表示 ASCLL 码）之后的字符串（长度为 $i+1$）的后缀能与 $T$ 的前缀去匹配的最大匹配长度（自匹配）。那么 $g$ 数组就可以辅助我们转移 $f$ 数组，它解决的是“跳到哪” 的问题。

$f_{i+1,g_{j, s_{i+1}}}=\min(f_{i+1,g_{j, s_{i+1}}}, f_{i,j})$ 这个就是不删除 $i+1$ 字符的最小删除字符数，直接转移。

继续考虑 $g$ 数组怎么求，这个就比较好办，可以用 KMP 的 $next$ 数组辅助求出来（我习惯叫 $next$ 为 $pmt$）

先把 $T$ 字符串的 $pmt$ 求出来，然后如下操作：

（1）如果 $T_{i+1}=(char)j$，那么 $g_{i,j}=i+1$；
（2）否则，$g_{i,j}=g_{pmt_i, j}$.

画一个图就好说了：

![](https://cdn.luogu.com.cn/upload/image_hosting/rlx7lgbz.png)

前 $i$ 个字符的相等前后缀（两条红线），那个红圈的意思是加上 $j$ 字符；失配就往前跳，类似 KMP 算法。

最后还有一大问题，就是这样会算错。转移时，可能会转移到 $f_{i+1,m}$，通过枚举 $j$ 时不枚举到 $m$，转移之后的状态时，不会有来自 $f_{i+1}{m}$ 的贡献（全局考虑，不会有问题）。最后答案来自 $\min f_{n,j}(j\in[0, m)\ )$

至此，问题圆满解决。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
const int N = 10005;
const int M = 1005;
const int inf = 1e9 + 5;
using namespace std;

char S[N], T[M];
int n, m ;
int f[N][M];
int g[M][32];

int pmt[N];


int main()
{
    cin >> S + 1 >> T + 1;
    n = strlen(S + 1), m = strlen(T + 1);

    for (int i = 2, j = 0; i <= m; i++) {
        while (j && T[j + 1] != T[i]) j = pmt[j];
        if (T[j + 1] == T[i]) j++;
        pmt[i] = j;
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 26; j++)
            if (T[i + 1] == (char)(j + 'a'))
                g[i][j] = i + 1;
            else
                g[i][j] = g[pmt[i]][j];
    
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++) // caution m!
            f[i][j] = inf;
    
    f[1][g[0][S[1] - 'a']] = 0;
    f[1][0] = min(f[1][0], 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) { // ! caution
            f[i + 1][j] = min(f[i + 1][j], f[i][j] + 1);
            f[i + 1][g[j][S[i + 1] - 'a']] = min(f[i + 1][g[j][S[i + 1] - 'a']], f[i][j]);
        }
    }
    int ans = inf;
    for (int j = 0; j < m; j++)
        ans = min(ans, f[n][j]);
    cout << ans << endl;
    return 0;
}
```

第一维或许可以滚动掉，但不想试了。

这题真是 KMP 的精髓，看来 KMP 常考的并不是模式串匹配，而是 $pmt$ 也就是 $next$ 数组的活用。

我的表达能力有限，再怎么说有些思路也表达不清楚，还需要大家多多思考下，欢迎提问。

---

## 作者：SolIII (赞：1)

## 前言

[更好的阅读体验](https://www.luogu.com.cn/article/0ngjfq9b)

KMP 与 DP。

## 题目分析

### 简化题意

给定字符串 `S` 和 `T`，求在 `S` 中最少删几个字符才能使 `S` 中不出现 `T`。

### 思路

看到字符串匹配类型的题目，第一时间想到 KMP 算法。考虑暴力，枚举 `S` 中的每一个字符删或不删，后使用 KMP 算法匹配。

看一眼数据规模 ，发现 `For all test cases, N <= 10000, M <= 1000.` 显然刚才的暴力不能满足题目的时限要求。


考虑优化，设动态规划状态为 $f_{i, j}$，表示在 `S` 的 $1$ 到 $i$ 位中删掉一些字符后末尾最多能与 `T` 的 $1$ 到 $j$ 位进行配对的最少字符删减数量。

对于动态规划的转移方程，我们可以从两种情况来考虑（对于此处的状态，我们可以发现主动转移比被动转移的代码与思路都容易许多，所以使用主动转移）：

1. 在转移中保留 $S_{i + 1}$: 对于这种情况，我们希望找到 一个数 $k$ 使 $S_{1 \cdots i + 1}$ 与 $T_{1 \cdots k}$ 配对。在寻找 $k$ 的过程中，我们可以使用类似于 KMP 算法的 `while` 循环来寻找（即利用 `Bonder` 的性质，让已经匹配的部分尽量长）。在这种情况下，$f_{i + 1, k} = f_{i, j}$（注意当 $k$ 为 $0$ 时也需要转移）。

2.  在转移中删除 $S_{i + 1}$: 这种情况下匹配的长度与转移前相同，即 $f_{i + 1, j} = f_{i, j} + 1$。

## 参考代码

```cpp
#include<bits/stdc++.h>    //万能头
using namespace std;
const int NR = 1e4;
const int MR = 1e3;
const int KR = 2e2;
char s[NR + 10];
char t[MR + 10];
int p[MR + 10];
int dp[NR + 10][MR + 10];     //dp 数组
int f[NR + 10][KR + 10];      //记忆化
void KMP(char x[], int len){    //预处理 t 的前缀最大 Bonder 长
	p[0] = 0;
	p[1] = 0;
	for(int i = 2;i <= len;i++){
		int j = p[i - 1];
		while(j != 0 && x[j + 1] != x[i]){
			j = p[j];
		}
		p[i] = (x[j + 1] == x[i]  ? j + 1 : 0);
	}
	return ;
}
int cal(int j, char c){   //记忆化优化计算 k 
	if(f[j][c] != -1) return f[j][c];  //已经计算过则返回
	int k = j;      //否则计算
	while(k != 0 && c != t[k + 1]){  //利用 Bonder 的性质，让已经匹配的部分尽量长
		k = p[k];
	}
	return f[j][c] = k;  //计算完毕，返回
}

int main(){
   //初始化
	memset(dp, 0x3f3f3f3f, sizeof(dp));
	memset(f, -1, sizeof(f));
	dp[0][0] = 0;
   //读入
	scanf("%s%s", s + 1, t + 1);
	int n = strlen(s + 1), m = strlen(t + 1);
   //预处理
	KMP(t, m);
   //动态规划
	for(int i = 0;i < n;i++){
		for(int j = 0;j < m;j++){
			int k = cal(j, s[i + 1]);  //计算 k
        // 转移 1
			if(s[i + 1] == t[k + 1] && k + 1 != m){
				dp[i + 1][k + 1] = min(dp[i + 1][k + 1], dp[i][j]);  
			}
			else if(k + 1 != m) dp[i + 1][0] = min(dp[i + 1][0], dp[i][j]);   //注意当 $k$ 为 $0$ 时也需要转移
			dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);   //转移 2
		}
	}
   //统计答案
	int Min = INT_MAX;
	for(int i = 0;i < m;i++){
		Min = min(Min, dp[n][i]);
	}
	printf("%d\n", Min);  //输出
	return 0;
}
```

---

## 作者：cccgift (赞：0)

## 看到其它题解讲得不太清楚，这里给出一种易懂的算法。

题意：给两个字符串$a,b$，求最少需要删除$a$的几个字符，使得$b$不是$a$的子串。

乍一眼看过去，需要用到字符串匹配，应该是$KMP$的题目……

但是，题目中要求的是删除几个字符，$KMP$完全做不了。

那么，我们可以把题目转化一下，变成最多留下$a$的几个字符，使得$b$不是它的子串。

题目看上去可做多了，我们设$f[i][j]$表示$a$的前$i$个字符，若要匹配$b$的前$j$个字符，最多留下来的字符个数。

那么，方程如下：

$f[i+1][k]=max(f[i+1][k],f[i][j]+1)$

其中$k$表示加入第$i+1$个字符后，最多能匹配$b$的字符个数。

暴力转移是$O(nm^2)$的，考虑如何进行快速匹配，这不就是$KMP$吗？

先预处理出$b$的$next$数组，然后每一次转移时直接从$j$开始匹配，即可做到$O(1)$找出$k$，时间复杂度是$O(nm)$。

然而，直接跳$next$数组貌似不是严格$O(1)$，导致这份代码在洛谷上跑了$949ms$，在我们学校的$OJ$上直接$TLE$了……

代码如下：

```cpp
#include<cstdio>
#include<cstring>
#include<cctype>
#include<utility>
#include<algorithm>
#include<cmath>
using namespace std;
#define res register int
#define ll long long
//#define cccgift
//#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21],*p1=buf,*p2=buf;
namespace wode{
    template<typename T>
    inline void read(T &x)
    {
        static char ch;bool f=1;
        for(x=0,ch=getchar();!isdigit(ch);ch=getchar()) if(ch=='-') f=0;
        for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());x=f?x:-x;
    }
    template<typename T>
    void print(T x)
    {
        if (x<0) putchar('-'),x=-x;
        if (x>=10) print(x/10);
        putchar(x%10+'0');
    }
    template<typename T>
    inline void print(T x,char ap) {print(x);if (ap) putchar(ap);}
    template<typename T>
    inline T max(T x,T y) {return x<y?y:x;}
    template<typename T>
    inline T min(T x,T y) {return x<y?x:y;}
    template<typename T>
    inline void chkmax(T &x,T y) {x=x<y?y:x;}
    template<typename T>
    inline void chkmin(T &x,T y) {x=x<y?x:y;}
}
using wode::read;using wode::chkmin;using wode::print;
#define chkmax(x,y) x=x>y?x:y
int nxt[1010],f[2][1010],n,m,maxx,s,t; //用滚动数组优化空间
char a[10010],b[1010];
int main()
{
	scanf("%s%s",a+1,b+1),n=strlen(a+1),m=strlen(b+1);
	for(res i=2,j=0;i<=m;++i) { //预处理next
		while(j&&b[i]!=b[j+1]) j=nxt[j];
		if(b[i]==b[j+1]) ++j;
		nxt[i]=j;
	}
	memset(f[0],255,sizeof(f[0])),f[0][0]=0;
	for(res i=1;i<=n;++i) {
		t=s,s^=1;
		memcpy(f[s],f[t],sizeof(f[t]));
		for(res j=0;j<m;++j) if(~f[t][j]) { //如果不可能出现这样的匹配方式就不用再进行转移了
			int l=j;
			while(l&&a[i]!=b[l+1]) l=nxt[l];
			if(a[i]==b[l+1]) ++l;
			chkmax(f[s][l],f[t][j]+1);
		}
	}
	for(res i=0;i<m;++i) chkmax(maxx,f[n&1][i]); //看看哪种情况（匹配数达不到b的长度）最优
	print(n-maxx,'\n'); //最后的答案就是a的长度减去留下来的字符个数
	return 0;
}
```

---

