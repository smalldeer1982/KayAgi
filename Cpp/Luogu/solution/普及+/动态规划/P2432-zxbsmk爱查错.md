# zxbsmk爱查错

## 题目背景

zxbsmk 在暑假回了一趟老家，见到了自己的外婆。然而他遇到了一个问题。

## 题目描述

外婆很喜欢给别人写信，然而因为年纪大了，信里面充斥着各种错误。所以 zxbsmk 打算帮外婆修正每个错误的句子。

因为外婆的文化水平很高，所以她写的句子都是英文句子，并且句子内的字母都是小写字母。然而 zxbsmk 的英语水平非常低，所以他买来了一本英语词典，词典里一共有 $W (1 \leq W \leq 600)$ 个单词，每个单词的长度都不超过 $25$ 个字母，而且都是由小写字母组成的。

那么再来看一下外婆的句子都有什么错误。例如，外婆写的一个句子是 `catotail`，这并没有什么意义，因为一个多余的字母 `o` 出现了，所以正确的句子应该是 `cattail`。

已知外婆的句子是由 $L (2 \leq L \leq 300)$ 个字母组成的。其中有一些字母是多余的。现在，请你借助 zxbsmk 的词典，帮助他修正外婆的句子。而且你必须尽量少地去除多余的字母，使剩余的字母是一个合法的句子。

## 说明/提示

`catotail` $\to$ `cattail`

## 样例 #1

### 输入

```
2 8
catotail
cat
tail```

### 输出

```
1```

# 题解

## 作者：lsroi (赞：9)

**题目大意：** 给你一个主串以及若干个子串，求最少需要删除几个字母，使得主串能由一些子串组成。

**思路：** 求最值问题，我们可以联想到用dp求解，最直接的状态就是，设**dp[i]表示主串的前i位最少需要删除几个字母。**

- 方程显然：**dp[i]=min{dp[i-1]+1,dp[k]+(i-k-len[j])};**

- （其中，k表示从主串[k+1...i]的区间中删掉一些字符能得到子串j的最大左端点-1，此时(显然此时的代价就为 **区间长度-子串j的长度** )）

**代码如下：**

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=605;
string s;	//主串
string s1[maxn];//子串
int len,len1[maxn],f[maxn];
int main()
{
    memset(f,0x3f,sizeof(f));	//初始化
    int n,t,i,j,k,l;
    cin>>n>>t;
    cin>>s;  len=s.size();
    for(i=1;i<=n;i++)cin>>s1[i],len1[i]=s1[i].size();
    f[0]=0;	//边界条件
    for(i=0;i<len;i++)
    {
      if(!i)f[i+1]=1;		//特殊情况（也是相当于边界
      else f[i+1]=f[i]+1;	//最劣情况
      for(j=1;j<=n;j++)	//枚举子串
      {
        int l=i,l1=len1[j]-1;	//用两个指针来寻找最短区间且包含子串j
        while(l>=0&&l1>=0)
        {
          if(s[l]==s1[j][l1])l--,l1--;
          else l--;
        }
        if(l1<0)f[i+1]=min(f[i+1],f[l+1]+(i-l-len1[j]));
      }
    }
    cout<<f[len]<<endl;
    return 0;
}
```


---

## 作者：rsdbk_husky (赞：8)

## 零. 安利：

[安利一下我的博客。](https://rsdbkhusky.github.io/)

## 一. 审题：

#### 1.已知&输入：

- 给出一个长度为 $L$ 的文本串。
- 给出 $W$ 个单词串。

#### 2.目标&输出：

- 在文本串中删除尽量少的字母使得文本串只有由词串构成，输出这个最少删除的字母数。

## 二. 思路

#### 1. 思考解法

- 文本串后面的内容不会影响文本串前半部分的最优解，**符合无后效性**。
- 若把文本串右端位置作为状态，文本串右端位置较靠右的状态需要通过文本串右端位置较靠左的状态得到（如 $d_i$ 需要通过 $d_0 \dots d_{i-1}$ 的其中之一得到），**符合子问题重叠性**。

所以考虑DP。

#### 2. 确定状态转移方程

$d_i$：前 $i$ 个子母的文本串中最少删除的字母数。

$txtidx$：用该第 $j$ 个单词串匹配前 $i$ 个子母的文本串，匹配完时文本串的下标。（**3.** 中有详解）

$delcnt$：用该第 $j$ 个单词串匹配前 $i$ 个子母的文本串，匹配过程中失配的次数。（**3.** 中有详解）

$seccessmatch$：用该第 $j$ 个单词串匹配前 $i$ 个子母的文本串，是否匹配成功。（**3.** 中有详解）

**综上所述，状转方程**：$d_i=\min_{j=1}^{W}\begin{cases}d_{i-1}+1~~~~~~~~~~~~~~~~~(seccessmatch=false)\\d_{txtidx}+delcnt~~~~~(seccessmatch=true)\end{cases}$

#### 3.细节&详解

~~反正跟字符串有关题的题解，没图我是看不懂。~~

比如文本串是 **cabbcxyz** ，我们现在正在求 $d_5$ （$i=5$） 用其中一个单词串 **abc** 匹配，用某个单词匹配时不用管其他单词。

初始时把 $txtidx$ 设为 $i$ （也就是 $5$），$wordidx$ 设为单词长度， $delcnt$ 设为 $0$ 。（注意 $delnum$ 不是整个文本串删去的字母个数，而是当前情况下匹配过部分的文本串的删去字母个数。**3.** 中有详解）

初始时：

![初始时](https://cdn.luogu.com.cn/upload/image_hosting/hj73llvb.png)

第一次匹配后：

![第一次匹配后](https://cdn.luogu.com.cn/upload/image_hosting/ceegje0t.png)

第二次匹配后：

![第二次匹配后](https://cdn.luogu.com.cn/upload/image_hosting/46jxowqa.png)

第三次匹配后：

![第三次匹配后](https://cdn.luogu.com.cn/upload/image_hosting/heq6srqt.png)

第四次匹配后：

![第四次匹配后](https://cdn.luogu.com.cn/upload/image_hosting/4up8t7by.png)

## 三. 代码

代码中有比较详细的注释。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXwordcnt = 600;//单词数量最大值 
const int MAXwordlen = 25;//单词长度最大值 
const int MAXtxtlen = 300;//文本长度最大值 

int wordcnt/*单词数量*/, txtlen/*文本长度*/;
char word[MAXwordcnt + 10][MAXwordlen + 10]/*单词*/, txt[MAXtxtlen + 10]/*文本*/;

int d[MAXtxtlen];//DP数组 

int main() {
	scanf("%d %d", &wordcnt, &txtlen);
	scanf("%s", txt + 1);
	for (int i = 1; i <= wordcnt; ++i) {
		scanf("%s", word[i] + 1);
	}
	d[0] = 0;
	for (int i = 1; i <= txtlen; ++i) {
		d[i] = d[i - 1] + 1;//如果没有单次得以再次位置匹配，需要删除的单词数++ 
		for (int j = 1; j <= wordcnt; ++j) {
			int wordidx = strlen(word[j] + 1);//此时单词串的下标
			int txtidx;//此时文本串的下标
			int delcnt = 0;//当前情况下匹配过部分的文本串的删去字母个数
			bool seccessmatch = 0;//是否匹配成功
			for (txtidx = i; txtidx >= 1; --txtidx) {
				if (wordidx == 0) {//wordidx == 0代表单词已经匹配完了 
					seccessmatch = 1;
					break;
				}
				if (txt[txtidx] == word[j][wordidx]) {//如果单词串与文本串在该位置相同... 
					--wordidx;						  //那么匹配下一位 
				} else {							  //否则...
					++delcnt;						  //需要删的个数++ 
				}
			}
			if (wordidx == 0) {//wordidx == 0代表单词已经匹配完了 
				seccessmatch = 1;
			}
			if (seccessmatch) {						 //如果成功匹配... 
				d[i] = min(d[i], d[txtidx] + delcnt);//转移状态
			}
		} 
	}
	printf("%d", d[txtlen]);
}
```





---

## 作者：quarmer (赞：5)

### 简化题意
给出一个长度为 $L$ 的字符串， 再给出 $W$ 个单词，问至少从 $L$ 中去掉多少字符才能由若干个单词拼成，单词使用可以重复。

### 思路

这种题一看就是 DP，考虑 $f_{i}$ 为在 $L$ 中前 $i$ 个字符最少需要删除多少个字符。显然的， $f_{i}$ 可以由 $f_{i - 1} + 1$ 得到。假设删除后拼成这句话的所有单词中最后一个单词为 $W_{j}$，那么方程显然 

$f_{i} = \min(f_{i - 1} +1, f_{i - len} + (len - |W_{j}|)$

其中，$len$ 表示 $L$ 中从第 $i$ 个字符往前数 $len$ 个字符，使子串 $L_{i - len +1} - L_{i}$ 可以通过删除单词拼成 $W_{j}$ 的 $len$ 的最小值。此时的 $f_{j}$ 就可以等于前 $i - len$ 个字符要删除字符的最小值与 $i + len - 1 $ 之后要拼成 $W_{j}$ 要删除字符的最小值之和。

至于求 $len$ 可以从 $L$ 的第 $i$ 个字符与 $W_{j}$ 的最后一个字符向前一一匹配，具体实现见代码。

### 代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;
#define int long long
int f[305] ;
int n, m ;
string s ;
string d[605] ;
signed main() {
	cin >> n >> m ;
	cin >> s ;
	for(int i = 1 ; i <= n ; i++) cin >> d[i] ;
	memset(f, 0x3f, sizeof(f)) ; //要求最小值，初始化成INF
	f[0] = 0 ; //边界 f[0] = 0 
	for(int i = 1 ; i <= m ; i++) {
		f[i] = f[i - 1] + 1 ;
		for(int j = 1 ; j <= n ; j++) {
			int r1 = i, r2 = d[j].size() ;//指针的思想
			int flag = 1 ;//记录是否可以匹配成功
			while(r1 && r2) {
				if(d[j][r2 - 1] == s[r1 - 1]) r1--, r2-- ; //若匹配成功，各向前移一位
				else r1-- ; // 不然 把母串指针前移一位
				if(!r2) flag = 0 ; //匹配成功
			}
			if(!flag) f[i] = min(f[r1] + i - r1 - (int)d[j].size(), f[i]) ; // 若匹配成功，转移
		}
	}
	cout << f[m] ;
	return 0 ;
}

```

---

## 作者：木木！ (赞：5)

提供一个不一样的做法。

考虑每一个单词对于答案的影响。很显然，对于每一个起始位置，我们尽快拼出那个单词，找出结尾的位置。那么，只要我们到达了结尾的那个位置，就可以通过一定的代价转换到开头那个位置。这就很像最短路。

于是做法就很显然了，建一个最短路图，对于字符串的每一位建一个点，然后对于每一个单词分别连边，最后再连 `i->i-1` 长度为 1 的一组边来表示直接删。

有一些小优化，比如如果某一个起始位置不是待处理单词的第一个字母，那么这个起始位置可以忽略。

最后建出的是一个 DAG，并且拓扑序已知，直接 DP 求最短路就好。

设单词平均长度为 $L_W$，时间复杂度为 $\Theta(WLL_W)$。可以预处理每一个字符在单词中的位置，期望时间复杂度可以降为 $\Theta(\dfrac{WLL_W}{|S|})$，其中 $|S|$ 为字符集大小，最坏时间复杂度仍是 $\Theta(WLL_W)$。

附 AC 代码：

```cpp
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

void chkmin(int& a,int b)
{
    if(b<a) a=b;
}

int beg[305];
int ed[183005];
int nxt[183005];
int li[183005];
int top;

void addedge(int a,int b,int c)
{
	++top;
	ed[top] = b;
	li[top] = c;
	nxt[top] = beg[a];
	beg[a] = top;
}

int dn;
int dist[305];

void dp()
{
    for(int i=0; i<dn; ++i)
    {
        dist[i] = 0x7f7f7f7f;
    }
    
    for(int i=dn; i; --i)
    {
        for(int p=beg[i]; p; p=nxt[p])
        {
            chkmin(dist[ed[p]],dist[i]+li[p]);
        }
    }
}

int lisi[35];
int listill[35];
int lisnxt[305];
int lisval[305];
int listop;

void clearlis()
{
	memset(lisi,0,sizeof(lisi));
	memset(listill,0,sizeof(listill));
	listop = 0;
}

void addlis(int k)
{
	++listop;
	lisval[listop] = k;
	lisnxt[listop] = lisi[1];
	lisi[1] = listop;
	if(!listill[1]) listill[1]=listop;
}

void levup(int x)
{
	if(!lisi[x]) return;
	lisnxt[listill[x]] = lisi[x+1];
	lisi[x+1] = lisi[x];
	if(!listill[x+1]) listill[x+1]=listill[x];
	lisi[x] = listill[x] = 0;
}

char stri[305];
char word[35];

int main()
{
	int w,l;
	scanf("%d%d",&w,&l);
	scanf("%s",stri+1);

	for(int i=1; i<=w; ++i)
	{
		scanf("%s",word+1);
		clearlis();

		const int wl = strlen(word+1);
		for(int j=1; j<=l; ++j)
		{
			for(int h=min(j,wl); h>1; --h)
				if(stri[j]==word[h])
					levup(h-1);

			if(stri[j]==word[1])
				addlis(j);

			for(int p=lisi[wl]; p; p=lisnxt[p])
				addedge(j,lisval[p]-1,j-lisval[p]+1-wl);
			levup(wl);
		}
	}

	for(int i=1; i<=l; ++i)
		addedge(i,i-1,1);

	dn = l;
	dp();

	printf("%d\n",dist[0]);
}
```

---

## 作者：SUNCHAOYI (赞：3)

考虑动态规划的作法，设 $dp[i]$ 表示原字符串的前 $i$ 位最少需要删除的字符的数量，显然最后的答案是 $dp[L]$。

对于初始值，因为求最小值，所以先把 $dp[i]$ 均设置为 $+\infty$，同时由转移方程的含义可知 $dp[0] = 0$。然后就是处理单词与文章是否能匹配的核心思路了，设 $dx$ 表示当前匹配到的位置 $i$，$dy$ 表示第 $j$ 个单词的长度 $len[j]$。从 $i$ 与单词的末尾开始，若成功匹配，则 $dx,dy$ 均减一，否则 $dx$ 减一。如果 $dy$ 的值先变为 $0$ 或者 $dx,dy$ 同时变为 $0$，这说明该单词能够在原字符串中匹配；但是如果不能匹配，显然原字符串的第 $i$ 个位置需要被删除。

所以有状态转移方程 $dp[i] = min (dp[i - 1] + 1,dp[dx] + (i - dx - len[j])$，显然此时的 $dx$ 表示在匹配之后 $dx$ 的值，而不是初始的 $dx = i$。

讲了这么多，再看着代码理解一下叭！

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,INF,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 605;
const int MOD = 1e9 + 7;
inline int read ();
int n,m,dlen[MAX],dp[MAX];
char str[MAX >> 1],cor[MAX][30];	
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();m = read ();
	scanf ("%s",str + 1);
	for (int i = 1;i <= n;++i)
	{
		scanf ("%s",cor[i] + 1);
		dlen[i] = strlen (cor[i] + 1);//单词的长度
	}
	init (dp);//初始化
	dp[0] = 0;
	for (int i = 1;i <= m;++i)
	{
		dp[i] = dp[i - 1] + 1;
		for (int j = 1;j <= n;++j)//共有 n 个单词，一一匹配
		{
			int dx = i,dy = dlen[j];
			while (dx && dy)//边界条件
			{
				if (str[dx] == cor[j][dy]) --dx,--dy;
				else --dx;
			}
			if (!dy) dp[i] = min (dp[i],dp[dx] + (i - dx - dlen[j]));//成功匹配才能进行状态转移
		}
	}
	printf ("%d\n",dp[m]);//此处为 m 而不是 n 哦！
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

