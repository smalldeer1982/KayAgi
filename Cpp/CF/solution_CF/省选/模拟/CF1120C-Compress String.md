# Compress String

## 题目描述

给定一个长度为 $n$ 的字符串 $s$，由小写英文字母组成。你需要用最少的金币数对其进行压缩。

压缩字符串的方法是，将 $s$ 表示为若干个非空字符串的连接：$s = t_{1} t_{2} \ldots t_{k}$。对于第 $i$ 个字符串 $t_{i}$，有两种编码方式：

- 如果 $|t_{i}| = 1$，即当前字符串仅包含一个字符，则编码需要花费 $a$ 个金币；
- 如果 $t_{i}$ 是 $t_{1} t_{2} \ldots t_{i-1}$ 的子串，则编码需要花费 $b$ 个金币。

字符串 $x$ 是字符串 $y$ 的子串，表示 $x$ 可以通过删除 $y$ 开头和结尾的若干（可能为零或全部）字符得到。

你的任务是计算压缩给定字符串 $s$ 所需的最小金币数。

## 说明/提示

在第一个样例中，可以设 $t_{1} = $ 'a'，$t_{2} = $ 'b'，$t_{3} = $ 'a'，共需 $3 + 3 + 1 = 7$ 个金币，因为 $t_{3}$ 是 $t_{1}t_{2}$ 的子串。

在第二个样例中，只需将每个字符单独压缩即可。

在第三个样例中，可以设 $t_{1} = t_{2} = $ 'a'，$t_{3} = $ 'aa'，共需 $10 + 1 + 1 = 12$ 个金币，因为 $t_{2}$ 是 $t_{1}$ 的子串，$t_{3}$ 是 $t_{1}t_{2}$ 的子串。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3 1
aba
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 1 1
abcd
```

### 输出

```
4
```

## 样例 #3

### 输入

```
4 10 1
aaaa
```

### 输出

```
12
```

# 题解

## 作者：Heartlessly (赞：11)

## Description

给定一个长度为 $n$ 的字符串 $s$，现在有一个打字机，每次你可以花费 $a$ 的代价打出一个字符，或者花费 $b$ 的代价打出一个 已经打出的字符串 的子串，求打出 $s$ 的最小代价。$(1 \leq n,a,b \leq 5 \times 10^3)$

## Solution

很容易想到 $O(n^3)$ 的 **DP** 。

我们用 $f_i$ 表示打完前 $i$ 个字符所需要的最小代价，状态转移方程为

$$f_i = \min \left( f_{i - 1} + a,\min \{ f_{i - k}\} + b \right)$$

考虑第 $i$ 个字符是怎么打出来的。

可以先打出前 $i - 1$ 个字符，然后花费 $a$ 的代价打出第 $i$ 个字符。

设子串的末尾为第 $j$ 个字符，子串的长度为 $k$，则可以先打出前 $i - k$ 个字符，再花费 $b$ 的代价打出 $k$ 个字符。前提是 $s_{i-k + 1, i}$ 与 $s_{j - k + 1, j}$ 相等，可以用 $\rm hash$ 判断。

最后取上述两种情况的最小值即可。

如何优化？

不难发现，$f$ 数组的值其实是单调不减的。

换句话说，方程中 $k$ 的值要尽可能大。

而 $k$ 的最大值其实是 $s_{1,i}$ 与 $s_{1,j}$ 的 **最长公共后缀** 长度。

于是我们可以省去对 $k$ 的枚举，同样的状态，新转移方程为

$$f_i = \min \left( f_{i - 1} + a, \min \{f_{\max\left(i - LPS_{i,j}, j\right)} \} + b \right)$$

其中 $LPS_{i,j}$ 表示 $s_{1, i}$ 与 $s_{1,j}$ 的最长公共后缀长度。之所以要与 $j$ 取 $\max$，是因为已经假设子串末尾为第 $j$ 个字符，$i - LPS_{i,j}$ 的值肯定不能比 $j$ 小，否则就等于取了 还没打出来的字符串 的子串。

图示：

![EaEn0K.png](https://s2.ax1x.com/2019/05/04/EaEn0K.png)

$\rm LPS$ 可以用 $O(n^2)$ **DP** 预处理，考虑第 $s_i$ 和 $s_j$ 是否相等即可。

![EaQnB9.png](https://s2.ax1x.com/2019/05/04/EaQnB9.png)

当然这道题也可以用 $\rm SA$ 维护 **DP**，只不过写起来麻烦一点。

总时间复杂度为 $O(n^2)$ 。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

template <class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool f = 0;
    for (; !isdigit(c); c = getchar()) f ^= c == '-';
    for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
    x = f ? -x : x;
}

template <class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    T y = 1;
    int len = 1;
    for (; y <= x / 10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x / y + 48);
}

const int MAXN = 5e3;
int n, a, b, f[MAXN + 5], lps[MAXN + 5][MAXN + 5];
char s[MAXN + 5];

int main() {
    read(n), read(a), read(b);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            lps[i][j] = s[i] == s[j] ? lps[i - 1][j - 1] + 1 : 0;//预处理最长公共后缀
    memset(f, 0x3f, sizeof (f));
    f[0] = 0;//初始状态：不打字花费的代价为 0 
    for (int i = 1; i <= n; ++i) {
        f[i] = f[i - 1] + a;
        for (int j = 1; j < i; ++j)
            f[i] = min(f[i], f[max(i - lps[i][j], j)] + b);//转移 
    }
    write(f[n]);
    putchar('\n');
    return 0;
}
```



---

## 作者：Froggy (赞：3)


## 题解页面的 $\LaTeX{}$ 有锅，请到[我的blog中阅读](https://www.luogu.com.cn/blog/1445353309froggy/solution-cf1120c)！

---

众所周知，$\mathrm{SAM}$ 是在线算法。

所以这道题为什么不能用 $\mathrm{SAM}$ 暴搞呢？

---

首先很好想到一个 $\mathcal{O}(n^3)$ 的 $\mathrm{dp}$。

记 $dp_i$ 为写完 $1\sim i$ 的字母后的最小花费，显然答案是 $dp_n$。

然后有如下转移：

$$dp_i=\min
\begin{cases}
dp_{i-1}+a \\
dp_j+b \quad (1\leq j\leq i-1,S_{j+1\cdots i}\text{是}S_{1\cdots j}\text{的子串})
\end{cases}
$$

判断一个串是否是另一个串的子串显然可以用 $\mathrm{kmp}$ 算法优化到 $\mathcal{O}(n)$ ，但无法满足我们的要求。

---

考虑把下面那个转移优化到 $\mathcal{O}(1)$，这时候我们可以换个思路，用 $dp_j$ 来更新 $dp_i$ 即**第二种转移是用当前状态从前往后更新的**。

学过 $\mathrm{SAM}$ 应该都知道：

>如果一个串 $T$ 是串 $S$ 的子串，那么串 $S$ 的 $\mathrm{SAM}$ 上一定存在一条 $T$ 对应的从根出发的路径。

假设当前更新完毕的位置是 $i$，那么就把 $S_i$ 加到 $\mathrm{SAM}$ 里面，然后从 $i+1$ 开始，在 $\mathrm{SAM}$ 直接跑，直到不存在边为止，在此之前的位置的 $\mathrm{dp}$ 值都是需要更新的。

---

时间复杂度 $\mathcal{O}(n^2)$

其实此题用 $\mathrm{SAM}$ 是可以做到 $\mathcal{O}(n)$ 的，~~然鹅我太菜了不会~~。

---

***code:***

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 5050
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
int n,a,b;
int tot,las,dp[N];
char s[N];
struct SAM{
	int ch[26];
	int fa,len;
}t[N<<1];
void Insert(int c){       //建SAM
	int u=++tot;
	t[u].len=t[las].len+1;
	int p=las;
	while(p&&!t[p].ch[c]){
		t[p].ch[c]=u;
		p=t[p].fa;
	}
	if(!p){
		t[u].fa=1;
	} 
	else{
		int q=t[p].ch[c];
		if(t[q].len==t[p].len+1){
			t[u].fa=q;
		}
		else{
			int clone=++tot;
			t[clone]=t[q];
			t[clone].len=t[p].len+1;
			while(p&&t[p].ch[c]==q){
				t[p].ch[c]=clone;
				p=t[p].fa;
			}
			t[u].fa=t[q].fa=clone;
		}
	}
	las=u;
}
int main(){
	n=read(),a=read(),b=read();
	memset(dp,0x3f,sizeof(dp));
	scanf("%s",s+1);
	tot=las=1;
	dp[0]=0;
	for(int i=1;i<=n;++i){
		Insert(s[i]-'a');
		dp[i]=min(dp[i],dp[i-1]+a);   //第一种转移
		int u=1;
		for(int j=i+1;j<=n;++j){     //从前往后在SAM上跑
			int c=s[j]-'a';
			if(t[u].ch[c]){
				dp[j]=min(dp[j],dp[i]+b);  //存在边就更新
				u=t[u].ch[c];
			}
			else break;             //否则不存在到Sj的边就跳出循环
		}
	}
	printf("%d\n",dp[n]);
	return 呱;
}

```
[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!


---

## 作者：蒟酱 (赞：2)

简要题意：你需要打出一个长度为 $n$ 的字符串 $s$。
- 花费 $c_1$ 的代价，在末尾打出一个字符。
- 花费 $c_2$ 的代价，在末尾打出目前已打出字符串的某个子串。

问最少的操作代价，$n\le5\times10^3$。

不妨用 $f_i$ 表示操作前 $i$ 个数的最小代价。可以在枚举当前点 $i$ 时再枚举一个之前点 $j$。如果 $\exist\space1\le l\le r\le j,a[j+1\dots i]=a[l\dots r]$ 就进行一次转移。暴力去判断子串相等就是 $\mathcal O(n^3)$ 的复杂度。  
可以配合 $\text{hash}$，还要线段树维护 `set`。第 $i$ 个 `set` $s_i$ 储存 $\{x|x=a[p\dots i],1\le p\le i\}$ 的 $\text{hash}$ 值，查询相当于在一段前缀 `set` 中查询一个元素是否存在。不过这样又要用线段树又需要 `set`，复杂度 $\mathcal O(n^2\log^2n)$，就算使用 `unordered_set` 还得承受大常数 $\mathcal O(n^2\log n)$。  
发现不管怎么做，询问的东西都是一样的，先预处理出所有询问，按照每个询问的 $i$ 排序。这样每次询问都在一段前缀中进行。排序询问的复杂度是 $\mathcal O(n^2\log n)$，后续查询采用 `unordered_set`，复杂度 $\mathcal O(n^2)$。总复杂度为 $\mathcal O(n^2\log n)$。  
也可以维护原串的最长公共后缀，由于 $f$ 具有单调性（假如 $f_i>f_{i+1}$ 必然是操作 $2$ 使得这种情况发生，那我操作 $2$ 少粘贴一个字母就能使得 $f_i=f_{i+1}$，也就是说假设必然不成立，$f$ 具有单调性，$f_i\le f_{i+1}$），每次应该从最小的 $j$ 转移过来，这个最小的 $j$ 就是之前某个 $j$ 与 $i$ 的最大公共后缀。复杂度 $\mathcal O(n^2)$。  
在这个做法的基础上，在后缀自动机上跑双指针（$i$ 和 $j$），$a[j\dots i]$ 存在就转移，否则 $j$ 右移。复杂度 $\mathcal O(n)$。

---

## 作者：Purslane (赞：1)

# Solution

这竟然是紫题。我觉得应该评橙。

设 $dp_i$ 为字符串前缀 $S[1 \dots i]$ 的合法划分的最小代价。显然 $dp_i$ 是单调的。

所以在第二种转移的时候，我们希望找到 $S[1 \dots i]$ 的最长的一个后缀 $S[j \dots i]$，使得它是 $S[1 \dots j-1]$ 的子串。

那么我们 $O(n^2)$ 求出 $S$ 的两两 $\rm lcp$。对于每个 $j$，扫描他在 $S[1 \dots j-1]$ 中可能出现的位置，求出 $i$ 的最大值 $i_{\max}$，那么显然所有的 $j \le i \le i_{\max}$ 都可以让 $j$ 满足要求。

复杂度 $O(n^2)$，代码很短：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e3+10;
int n,a,b,dp[MAXN],lcp[MAXN][MAXN],mxlen[MAXN],lst[MAXN]; string S;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>a>>b>>S,S="&"+S; memset(lst,0x3f,sizeof(lst));
	roff(i,n,1) roff(j,n,1) if(S[i]==S[j]) lcp[i][j]=lcp[i+1][j+1]+1;
	ffor(i,2,n) ffor(j,1,i-1) mxlen[i]=max(mxlen[i],min(i-j,lcp[i][j]));	
	ffor(i,2,n) ffor(j,i,i+mxlen[i]-1) lst[j]=min(lst[j],i);
	dp[1]=a; ffor(i,2,n) {dp[i]=dp[i-1]+a;if(lst[i]<=n) dp[i]=min(dp[i],dp[lst[i]-1]+b);}
	cout<<dp[n];
	return 0;
}
```

---

## 作者：wucstdio (赞：1)

预知识：后缀数组。不会的请左转[这里](https://www.luogu.org/problemnew/show/P3809)

考虑DP。

我们设$f_i$表示将$s_{1,i}$划分的最小花费，则

$$f_{i+1}=min(f_{i+1},f_i+a)$$

$$f_{k}=min(f_{k},f_i+b)$$

其中$k$满足$s_{i+1,k}$是前面一部分的子串。

第一个方程很好实现。

对于第二个方程，我们可以枚举一下子串的起始位置，然后用SA求出最大的$k$（可以证明每次取最大的$k$一定最优）

丢一张图：

![](https://cdn.luogu.com.cn/upload/pic/55327.png)

时间复杂度$O(n^2)$。也许有更优秀的做法。

代码也就比较简单了：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char s[5005];
int n,a,b,x[5005],y[5005],c[5005],sa[5005],rnk[5005],height[5005];
int minl[15][5005],lg2[5005];
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	scanf("%s",s+1);
	int m=128;
	for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
	m=0;
	for(int k=1;m<n;k<<=1)
	{
		m=0;
		for(int i=n-k+1;i<=n;i++)y[++m]=i;
		for(int i=1;i<=n;i++)
		  if(sa[i]>k)y[++m]=sa[i]-k;
		for(int i=1;i<=m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i],y[i]=x[i];
		x[sa[1]]=m=1;
		for(int i=2;i<=n;i++)
		{
			if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])x[sa[i]]=m;
			else x[sa[i]]=++m;
		}
	}
	for(int i=1;i<=n;i++)rnk[sa[i]]=i;
	for(int i=1;i<=n;i++)
	{
		height[rnk[i]]=height[rnk[i-1]]-1;
		if(height[rnk[i]]<0)height[rnk[i]]=0;
		while(s[i+height[rnk[i]]]==s[sa[rnk[i]-1]+height[rnk[i]]])++height[rnk[i]];
	}//以上是后缀数组板子
	for(int i=2;i<=n;i++)
	  lg2[i]=lg2[i>>1]+1;
	for(int i=1;i<=n;i++)
	  minl[0][i]=height[i];
	for(int i=1;i<=lg2[n];i++)
	  for(int j=1;j<=n;j++)
	    minl[i][j]=min(minl[i-1][j],minl[i-1][j+(1<<(i-1))]);
	memset(x,0x3f,sizeof(x));//这里的x就是DP数组f
	x[0]=0;
	for(int i=0;i<n;i++)
	{
		x[i+1]=min(x[i+1],x[i]+a);
		int maxl=0;
		for(int j=1;j<=i;j++)
		{
			int x=rnk[j],y=rnk[i+1];
			if(x>y)swap(x,y);
			int d=lg2[y-x];
			maxl=max(maxl,min(min(minl[d][x+1],minl[d][y-(1<<d)+1]),i+1-j));
		}
		x[i+maxl]=min(x[i+maxl],x[i]+b);
	}
	printf("%d\n",x[n]);
	return 0;
}
```

---

## 作者：qiyue7 (赞：1)

此题为2015 ACM/ICPC Asia Regional Shanghai Online的字符串题Typewriter的二次削弱版  原题每次追加的字母带权，数据量120w  

一次削弱版为2019杭电多校第一场的Typewriter，题意和此题相同 题目数据为500w  

昨天打完就直接过来放个O(n)的AC代码吧   我的大致思路是离线预处理firstpos 然后利用区间单调性+单调队列优化转移即可做到O（n） 

具体细节看代码，代码应该还是很容易看明白的  （原题std是在线做法看不懂emmmmmm...~~**欺负离线党**~~）


代码中extend为sam的插入

O（n）离线AC主代码

```cpp
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s;
    long long n,a, b;
    cin >>n>> a >> b;
    while (cin >> s)
    {
        dp.fill(0);
        deque<pair<long long, long long> > que;
        int kk = s.size();
        last = 1, sam = 1;
        firstpos.fill(0);
        memset(trans, 0, sizeof(trans));
        par.fill(0), len.fill(0);
        for (auto &p : s)
            extend(p - 'a');
        dp[0] = a;
        que.push_back({ 0,a });
        int ff = 1, L = 0;
        ff = trans[ff][s[0] - 'a'];
        for (int i = 1; i < s.size(); ++i)
        {


            ff = trans[ff][s[i] - 'a'];
            while ((len[par[ff]] < i - L || firstpos[par[ff]] > L))
            {
                L++;
                if (i - L < len[par[ff]])
                    ff = par[ff];
            }


            while (!que.empty() && que.front().first < L)
                que.pop_front();
            if (!que.empty())
                dp[i] = min(dp[i - 1] + a, que.front().second + b);
            else
                dp[i] = dp[i - 1] + a;
            while (!que.empty() && que.back().second >= dp[i])
                que.pop_back();
            que.push_back({ i,dp[i] });
        }


        cout << dp[kk - 1] << '\n';
    }
    return 0;
}
```


---

## 作者：ifffer_2137 (赞：0)

逛了一圈没有同做法的，来补一发~
### 题意
给出 $n$，$a$，$b$ 和一个字符串 $s$，将一个串划分成若干段，每一段必须是单个字符或者是前面所有段连起来的连续子串，划分成一个字符需要 $a$ 元，划分成前面串的连续子串需要 $b$ 元，问最小花费是多少。
### 分析
看好多巨佬都用了 SA 之类的高级串串算法，其实没必要。

一个朴素的 DP，令 $f_i$ 表示前 $i$ 个字符的最小划分花费，那么显然，一种方法是：
$$f_i=f_{i-1}+a$$
还有一种方法是划分为前面一部分的子串，这个暴力转移不太可行，我们考虑单调性，发现 $f_i$ 单调不减，这个应该很显然吧，所以我们现在就要找出最靠前的合法转移位置。

还是考虑单调性，现在问题变成将一个串分为前后两部分，使后一部分为前一部分的子串，问后一部分最长能取多少。这个问题显然也是单调的，所以可二分，判断一个串是否是另一个串的子串只要哈希一下就可以做到 $\mathcal O(n)$ 了。

总时间复杂度就是 $\mathcal O(n^2\log_2n)$，~~喜提洛谷最劣解~~。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=5e3+5;
const int mod=1e9+7;
const int base=29;
int n,a,b;
int f[maxn];
string s;
int hs[maxn],pw[maxn];
int HASH(int l,int r){
	int res=hs[r]-hs[l-1]*pw[r-l+1]%mod+mod;
	if(res>mod) res-=mod;
	return res;
}
bool check(int l,int r,int x,int y){
	int p=HASH(x,y);
	for(int i=l;i<=r;i++){
		if(i+(y-x+1)-1>r) break;
		if(HASH(i,i+(y-x+1)-1)==p) return true;
	}
	return false;
}
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),a=read(),b=read();
	cin>>s;
	s=' '+s;
	pw[0]=1;
	for(int i=1;i<=n;i++){
		pw[i]=pw[i-1]*base%mod;
		hs[i]=hs[i-1]*base%mod+(s[i]-'a');
		if(hs[i]>mod) hs[i]-=mod;
		f[i]=f[i-1]+a;
		int l=1,r=i,pos=0;
		while(l<=r){
			int m=(l+r)/2;
			if(check(1,m,m+1,i)){
				pos=m;
				r=m-1;
			}else{
				l=m+1;
			}
		}
		if(!pos) continue;
		f[i]=min(f[i],f[pos]+b);
	}
	cout<<f[n]<<endl;
	return 0;
}
```

---

