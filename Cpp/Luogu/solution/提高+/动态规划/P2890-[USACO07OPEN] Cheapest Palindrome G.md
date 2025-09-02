# [USACO07OPEN] Cheapest Palindrome G

## 题目描述

给定一个由 $n$ 个不同的小写字母构成的长 $m$ 的字符串 $s$。可以通过**在 $\bm{s}$ 的任意位置**增减字母将 $s$ 改为回文串。增减字母的花费不同，求最小花费。

## 说明/提示

对于 $100\%$ 的数据，$1\le m\le2\times10^3,1\le n\le 26,0\le x,y\le 10^4$。

$\mathrm{by\ @}$[$\mathrm{Fish\_Know\_Forever}$](/user/663215)

## 样例 #1

### 输入

```
3 4
abcb
a 1000 1100
b 350 700
c 200 800
```

### 输出

```
900
```

# 题解

## 作者：zhenglier (赞：23)

[更好的阅读体验](https://www.cnblogs.com/zhenglier/p/11157574.html)

## 区间DP

设$f[i][j]$为从$i$到$j$这段区间被修正为回文串的最小花费，$c[ch][0]$为添加字符$ch$的花费，$c[ch][1]$为删去字符$ch$的花费，$s$为题目给出的串。为可以用如下几个转移：

- 用$[i+1,j]$区间转移：这种转移相当于在$[i+1,j]$区间的左边加入一个字符，让$[i,j]$变为回文的方法为在左边删去该字符或在右边加上该字符，有转移方程：

$$f[i][j]=min(f[i][j],f[i+1][j]+min(c[s[i]][0],c[s[i]][1]))$$

- 用$[i,j-1]$区间转移：这种转移相当于在$[i,j-1]$区间的右边加入一个字符，方法同上：

$$f[i][j]=min(f[i][j],f[i][j-1]+min(c[s[j]][0],c[s[j]][1]))$$

- 当前区间$[i,j]$满足$s[i]==s[j]$，直接用$[i+1,j-1]$转移:

$$f[i][j]=min(f[i][j],f[i+1][j-1])$$

然后就可以愉快地写代码了：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2010;
int n,m;
char s[N];
int c[255][2];
int f[N][N];
int main(){
    cin>>m>>n;
    scanf("%s",s+1);
    for(int i=1;i<=m;++i){
        char op[2];
        int a,b;
        scanf("%s %d %d",op,&a,&b);
        c[op[0]][0]=a;
        c[op[0]][1]=b;
	}
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;++i)f[i][i]=0;
	for(int i=0;i<=n+1;++i){
	    for(int j=0;j<i;++j)f[i][j]=0;
	}
	for(int k=1;k<=n;++k){
	    for(int i=1;k+i<=n;++i){
	    	int j=k+i;
	        f[i][j]=min(f[i+1][j]+min(c[s[i]][0],c[s[i]][1]),
			            f[i][j-1]+min(c[s[j]][0],c[s[j]][1]));
			if(s[i]==s[j]){
				if(j-i==1)f[i][j]=0;
			    else f[i][j]=min(f[i][j],f[i+1][j-1]);
			}
		}
	}
	cout<<f[1][n]<<endl;
}
```

---

## 作者：ldxcaicai (赞：18)

# Solution
此题有玄学的状态转移方程；

设字符串为 $s[1,m]$,删除某字符的价格为 $val[k-'a']$；

最关键的一点在于,如果 $s[i+1,j]$ 已经是回文，那么删除掉 $s[i]$ 与在 $s[j,j+1]$ 中间插入 $s[i]$ 两个操作是等价的，即 $val[k-'a']=\min \{insert[k],delete[k]\}$;

并定义状态f[i,j]表示将s[i,j]变成回文字符串的最小代价

#则不难发现：f[i,i]=0;

#若s[i]==s[i+1],那么有f[i,j]=0;

#对于已经求出值的f[i,j]

- 如果s[i-1]==s[j+1]，那么显然有f[i-1][j+1]=min(f[i-1][j+1],f[i][j]);

- dp[i-1][j]=min(dp[i-1][j],dp[i][j]+val[s[i-1]-'a']);

- dp[i][j+1]=min(dp[i][j+1],dp[i][j]+val[s[j+1]-'a']);

#下面给出代码

```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
char s[2010];
int n,m,dp[3010][3010],val[3010];
int main(){
    scanf("%d %d %s",&n,&m,s+1);
    int a,b;
    char k[3];f
    for(int i=1;i<=n;++i){
        scanf("%s%d%d",k,&a,&b);
        val[k[0]-'a']=min(a,b);
    }
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=m;++i){
        dp[i][i]=0;
        if(s[i]==s[i+1])dp[i][i+1]=0;
    }
    for(int l=0;l<=m;++l)
        for(int i=1;i<=m;++i){
            int j=i+l;
            a=s[i-1]-'a';
            b=s[j+1]-'a';
            if(a==b)dp[i-1][j+1]=min(dp[i-1][j+1],dp[i][j]);    //玄学 
            dp[i-1][j]=min(dp[i-1][j],dp[i][j]+val[s[i-1]-'a']);//D P 
            dp[i][j+1]=min(dp[i][j+1],dp[i][j]+val[s[j+1]-'a']);//方程 
        }
    printf("%d",dp[1][m]);
    return 0;
}
```

---

## 作者：zhaoyp (赞：15)

首先我们可以发现，如果把一个字符串构成回文串的话，对于某一个单独出现的字符，我们既可以将其删除，也可以在另一侧添加上一个同样的字符，于是可以得到以下性质：

**添加和删除字符其实是等价的**。

于是修改某个字符的费用就是添加和删除费用的较小值。

------------

由于是为了实现字符串从左往右与从右往左读是一样的，我们不妨先将原字符串翻转。求出它们最大公共子序列的费用和，原字符串费用和与其之差即为答案。

------------

## DP状态设计及转移
 
设 $dp_{i,j}$ 为原字符串前 $i$ 位与翻转后字符串前 $j$ 位的最大公共子序列的费用和，那么则有：

$dp_{i,j} = \max\{dp_{i,j - 1},dp_{i - 1,j}\}$

若原字符串第 $i$ 位与翻转后字符串第 $j$ 位相等则有：

$dp_{i,j} = \max\{dp_{i,j},dp_{i - 1,j - 1} + a_{str_{i  - 1}}\}$

其中 $a_i$ 代表修改 ASCLL 值为 $i$ 的字符的费用，由于字符串下标由 $0$ 开始，所以转移中为 $a_{str_{i  - 1}}$ 。

------------

## code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define min(x,y) x < y?x:y
#define max(x,y) x > y?x:y
int m,n,x,y,ans,a[150],dp[2005][2005];
char ch;
string str,strr;
void input()
{
	cin >> n >> m >> str;
	for(int i = 1;i <= n;i++)
		cin >> ch >> x >> y,a[ch] = min(x,y); 
	for(int i = m - 1;i >= 0;i--)
		strr = strr + str[i];
} 
void DP()
{
	for(int i = 1;i <= m;i++)
		for(int j = 1;j <= m;j++)
		{
			dp[i][j] = max(dp[i][j - 1],dp[i - 1][j]);
			if(strr[j - 1] == str[i - 1])
				dp[i][j] = max(dp[i][j],dp[i - 1][j - 1] + a[str[i - 1]]);
		}
}
void output()
{
	for(int i = 0;i < m;i++)
		ans += a[str[i]];
	ans -= dp[m][m];
	printf("%d",ans);
}
int main()
{
	input();
	DP();
	output(); 
	return 0 ;
}
```


---

## 作者：BackSlashDelta (赞：8)

## [❮Luogu P2890❯](https://www.luogu.com.cn/problem/P2890)

### ➤ 闲言

被这个在两端操作的区间 DP 卡了挺久。题解中不少大佬讲的不错，但是我卡在了某些莫名其妙的地方。所以写篇题解加深印象，顺便帮助他人理解。

### ➤ 题面

给定一个长度为 $m$ 的包含 $n$ 个小写字母的字符串。你可以任意的：（一）在两个字符之间插入一个小写字母并付出相应的代价（二）删去任意一个字符并付出相应的代价。给定字符串中每一个小写字母插入和删除的代价。求将原串变为回文串的最小代价。

### ➤ 题解

#### ❖ 转化

对于任意一个回文的子串，一定是由它包含的原子串通过插入和删除操作得到的。那我们假定任何回文子串都是由被它包含的子串通过操作而来的。由此可以得到：当前的回文串只可能有五种来源：

- （下划线标记子串，红色表示删除，绿色表示添加）
- 当前串已经是回文串了。$\color{black}{\text{x}\underline{\text{abba}}\text{x}}$
- 添加一个当前串最右端的字符。$\color{green}{\text{x}}\color{black}{\text{a}\underline{\text{bba}}\text{x}}$
- 删去当前串最右端的一个字符。$\color{black}{\text{a}\underline{\text{bba}}}\color{red}{\text{x}}$
- 删去当前串最左端的一个字符。$\color{red}{\text{x}}\color{black}{\underline{\text{abb}}\text{a}}$
- 添加一个当前串最左端的字符。$\color{black}{\text{x}\underline{\text{abb}}\text{a}}\color{green}{\text{x}}$

于是问题转化成了区间问题：在上一个区间在两端进行操作，使得得到的新的区间满足题目要求。

于是，我们考虑使用区间 DP 求解。

#### ❖ 转移

像普通的区间 DP 一样，我们使用 ``dp[begin][end]`` 表示以 ``begin`` 为开始到 ``end`` 终止的字符串中通过操作得到回文串所需要的最小代价。若串本身回文，则代价为 ``0`` 。

因为 ``dp[][]`` 中存储的是使它对应的串回文所需要的串的代价，所以在转移时我们可以默认它的子串已经回文（转移使用的是 ``dp[][]`` 数组）。那我们转移只要分两种情况：当前串的左右两端相同；当前串的左右两端不同。

**注意：** 仔细读题，我们插入与删除的代价仅仅与对应的**字符**有关，与位置无关。

- 对于当前串两端相同的情况，直接由它的子状态转移过来即可：

```cpp
// 串已经回文，不必消耗额外代价
dp[begin][end] <={ dp[begin + 1][end - 1] }
```

- 对于当前串两端不同的情况，分类讨论：

```cpp
// 在 s[begin] 与 s[begin+1] 之间添加一个字符。
// 可以认为新添加的字符处于 s[begin+0.5] 的位置。
// （因为它不属于原串）
dp[begin][end] <={ dp[begin + 1][end] + insert[s[begin]] }
```
```cpp
// 删去 s[begin] 。可以认为将 s[begin] 挖空，并
// 不移动原串，即令其他字符坐标不变（像 x_abbax 这
// 样，下划线处被挖空了，但它是回文的"xabbax"）
dp[begin][end] <={ dp[begin + 1][end] + delete[s[begin]] }
```
```cpp
// 在 s[end-1] 与 s[end] 之间添加一个字符
dp[begin][end] <={ dp[begin][end - 1] + insert[s[end]]   }
```
```cpp
// 删去 s[end] 。
dp[begin][end] <={ dp[begin][end - 1] + delete[s[end]]   }
```

所以转移已经出来了：

```cpp
// 这里默认 dp[][] 中的初始值都为 0，
// 并且 begin != end 。也就是说，若
// dp[][] == 0 ，则它没有被更新过，
// 那么必须用上一步的值来更新它。不然
// 依照 min() 的比较方式，它将无法更新
if (s[begin] == s[end]) {
  dp[begin][end] = min(dp[begin + 1][end - 1],
                       dp[begin][end] ? dp[begin][end]:
                                        0x7fffffff)
} else {
  dp[begin][end] = min(min(min(dp[begin + 1][end] + ins[s[begin]],
                               dp[begin + 1][end] + del[s[begin]]),
                           min(dp[begin][end - 1] + ins[s[end]]  ,
                               dp[begin][end - 1] + del[s[end]]  )),
                               dp[begin][end] ? dp[begin][end] :
                                                0x7fffffff);
}
```

#### ❖ 简化

不觉得很臃肿吗？那简化一下。  
观察到转移式中删去 ``s[begin]`` 与插入 ``s[begin]`` 的式子很像，考虑合并。  
同样，对于 ``s[end]`` 的操作也合并。

```cpp
dp[begin][end] = min(min(dp[begin + 1][end] + min(ins[s[begin]],
                                                  del[s[begin]]),
                         dp[begin][end - 1] + min(ins[s[end]]  ,
                                                  del[s[end]]  )),
                         dp[begin][end] ? dp[begin][end] :
                                          0x7fffffff);
```

发现每次我们操作字符 ``s[begin]`` 和 ``s[end]`` 时，都是取的代价消耗最小值。考虑继续简化。

```cpp
// cost[x] = min(ins[x], del[x])
dp[begin][end] = min(min(dp[begin + 1][end] + cost[s[begin]],
                         dp[begin][end - 1] + cost[s[end]  ]),
                         dp[begin][end] ? dp[begin][end] :
                                          0x7fffffff);
```

虽然仍然不怎么好看，但已经简化很多了。

### ➤ 代码

```cpp
// 读入部分，ReadNum(); 为快读函数，返回一个整型数。
// ReadLtr(); 会返回遇到的第一个的字母。例如在：
// 123abc 的数据中，ReadLtr(); 会返回 'a'
inline void ReadIn() {
  n = ReadNum();
  m = ReadNum();
  for (int i = 1; i <= m; i++) {
    s[i] = ReadLtr() - 'a';
  }
  for (int i = 1, id; i <= n; i++) {
    id = ReadLtr() - 'a';
    cost[id] = min(ReadNum(), ReadNum());
  }
}
// DP 部分
int dp[MAXM][MAXM];  // [left][right] = cost
inline void DP() {
  for (int len = 2; len <= m; len++) {
    for (int begin = 1, end = begin + len - 1; end <= m; begin++, end++) {
      if (s[begin] == s[end]) {
        dp[begin][end] = min(dp[begin + 1][end - 1], 
                             dp[begin][end] ? dp[begin][end] :
                                              0x7fffffff);
      } else {
        dp[begin][end] = min(min(dp[begin + 1][end] + cost[s[begin]],
                                 dp[begin][end - 1] + cost[s[end]  ]),
                                 dp[begin][end] ? dp[begin][end] :
                                                  0x7fffffff);
      }
    }
  }
}
// 输出部分。比较显然，不解释。
inline void PrintAns() {
  printf("%d\n", dp[1][m]);
}
```



---

## 作者：Talaodi (赞：4)

一道很水的区间DP。

设 $dp_{i,j}$ 为将名字中第 $i$ 个字符到第 $j$ 个字符修改为回文串的最小花费。

当 $s_i=s_j$ 时，只需要让 $i+1$ 到 $j-1$ 是回文串即可。

当 $s_i\ne s_j$ 时，可以让 $i + 1$ 到 $j$ 是回文串，删除开头或在末尾添加一个 $s_i$；也可以让 $i$ 到 $j - 1$ 是回文串，删除末尾或在开头添加一个 $s_j$。

由此推得转移方程：

$$dp_{i,j}=dp_{i+1,j-1}(s_i=s_j)$$

$$dp_{i,j}=\min\{dp_{i+1,j}+add_{s_i},dp_{i+1,j}+del_{s_i},dp_{i,j-1}+add_{s_j},dp_{i,j-1}+del_{s_j}\}(s_i\ne s_j)$$

时间复杂度：$O(m^2)$

[代码（C++，$94ms$）：](https://www.luogu.com.cn/record/41294917)
```
#include <iostream>
#include <limits>

int const INF = std::numeric_limits<int>::max();

int dp[2001][2001];
char name[2001];
int add[301];
int del[301];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        std::cin >> name[i];
    }

    for (int i = 1; i <= n; i++) {
        char c;
        std::cin >> c;
        std::cin >> add[c] >> del[c];
    }

    for (int l = 2; l <= m; l++) {
        for (int i = 1; i + l - 1 <= m; i++) {
            int j = i + l - 1;
            dp[i][j] = INF;

            if (name[i] == name[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            }
            else {
                dp[i][j] = std::min(
                    std::min(dp[i + 1][j] + add[name[i]], dp[i][j - 1] + add[name[j]]),
                    std::min(dp[i + 1][j] + del[name[i]], dp[i][j - 1] + del[name[j]])
                );
            }
        }
    }

    std::cout << dp[1][m];

    return 0;
}
```

---

## 作者：rui_er (赞：4)

小清新 dp 题喜加一。

题意：我们有一个字符串 $s$，长度为 $m$。我们可以在任意位置添加或删除一个字母，共有 $n$ 个字母可供选择，添加或删除不同字母所需花费不同，求使这个字符串为回文串的最少花费。

---

显然区间 dp，设计状态 $dp_{i,j}$ 表示使 $s_i\sim s_j$ 为回文串所需的最少花费。

下面考虑状态转移：

我们枚举区间长度 $l\in\left[0,m\right)$，然后枚举左端点 $i$，得到右端点 $j$。

对于一个回文字符串，在它的左侧加一个字符后要想保持回文性，有两种方法：在右侧添加一个同样的字符，或者将左侧字符删去。可以看出，对于一个字符而言，插入和删除的权值没有区别，可以只存最小值。

考虑这个字符串，我们可以看做它是由回文串在左侧添加一个字符得到的，也可以看做它是在右侧添加一个字符得到的。我们选择这两者的更小的那个即可：（$mp$ 表示对于一个字符，插入和删除的权值中小的那个）

$$dp_{i,j}=\min(dp_{i+1,j}+mp_{s_i},dp_{i,j-1}+mp_{s_j})$$

当然，有一种情况较为特殊：$s_i=s_j$，此时我们需要特判。如果 $l\le 1$，则该串本身回文， $dp_{i,j}=0$。否则，$dp_{i,j}=\min(dp_{i,j},dp_{i+1,j-1})$。

于是，我们便得到了本题的三个方程。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;
const int M = 2005;

int n, m;
string s;
map<char, int> mp;
int dp[M][M];

int main() {
	scanf("%d%d", &n, &m);
	cin>>s;
	memset(dp, 0x3f, sizeof(dp));
	for(int i=0;i<m;i++) {
		for(int j=0;j<=i;j++) dp[i][j] = 0;
	}
	for(int i=1;i<=n;i++) {
		char c = getchar();
		for(;c==' '||c=='\n';c=getchar());
		int a, b;
		scanf("%d%d", &a, &b);
		mp[c] = min(a, b);
	}
	for(int l=0;l<m;l++) {
		for(int i=0,j=l;j<m;i++,j++) {
			dp[i][j] = min(dp[i+1][j]+mp[s[i]], dp[i][j-1]+mp[s[j]]);
			if(s[i] == s[j]) dp[i][j] = min(dp[i][j], (l <= 1 ? 0 : dp[i+1][j-1]));
		}
	}
	printf("%d\n", dp[0][m-1]);
	return 0;
}
```

---

## 作者：wuzhoupei (赞：3)

这个题的题解比较少；

首先，这个题我一上来就想到了一道白皮上的DP；

那道题的转移方程是

if(a[i]==b[j]) f[i][j]=f[i-1][j-1];

else f[i][j]=min(f[i-1][j],f[i][j-1])+1;

大概就是当前a串字母和b串字母相同时，等价于前一个位置相同；

否则就改变其中的一个，求最小值；

----------

那这道题可以说是有相同之处；

如果s[i]==s[j]，f[i][j]=f[i+1][j-1]；

就是说如果i，j这两个位置相同，那没必要去增加或删减；

最小值为之前i-1，j-1为回文串的最小值；

否则
我们明确f[i-1][j]和f[i][j-1]已经是回文串的最小值了；

那么只需要看看收尾两个字母是增加某一个还是删减某一个更优；

所以转移方程也就有了；(详见代码)；

枚举顺序也要注意是左端点倒着枚举；

我的博客：http://blog.csdn.net/pretend\_fal


cpp
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define II int
#define C char
#define R register
#define I 2050
using namespace std;


II n,m;

II add[I], del[I], f[I][I];

string s;


int main()
{
//    freopen("1.in","r",stdin);
    
    scanf("%d%d",&n,&m);
    cin>>s;
    for(R II i=1;i<=n;i++)
    {
        R C a;    
        while (scanf("%c",&a)!=EOF&&(a==' '||a=='\n'));
        scanf("%d%d",&add[a],&del[a]);
    }
    for(R II r=1;r<m;r++)
    {
        for(R II l=r-1;l>=0;l--)
        {
            if(s[l]==s[r]) f[l][r]=f[l+1][r-1];
              else {
                    R II a1=f[l][r-1]+min(del[s[r]],add[s[r]]);
                    R II a2=f[l+1][r]+min(del[s[l]],add[s[l]]);
                    f[l][r]=min(a1,a2);
              }
              // 因为l+1，所以要求f[l][r]时，f[l+1][r]已经求出来了;
              // 所以l倒着枚举； 
        }
    }
    
    printf("%d\n",f[0][m-1]);
    exit(0);
}
```

---

## 作者：Corsair (赞：3)

#### 注意一下这题，插入和删除都能在任意位置且花费都不同，不是只能在开头和结尾。

分析题目，有2种做法  (~~我只会2种~~)
1. 记忆化搜索 
1. 递推 

下面讲一下记忆化搜索。

#### 设原字符串为 s

#### 问题实际上就是求 s[i],s[i+1],s[i]......s[j]转换成回文串的最小代价。



------------

样例字符串： abcb

### 1. 在字符串尾添加si 
		形成 abcba
        等同于 s[i],s[i+1]......s[j],s[i]
### 2. 在字符串首添加sj
		形成 babcb
        等同于 s[j],s[i]......s[j]
### 3. 删除字符串首si 
		形成 bcb
        等同于 s[i+1]......s[j-1],s[j]
### 4. 删除字符串尾sj 
		形成 abc
        等同于 s[i],s[i+1]......s[j-1]
        
###  如果s[i]等于s[j] 可直接跳过，等同于求 s[i+1] , s[i+2]......s[j-2] , s[j-1]

# 设f[i][j] 表示从s[i]到s[j]的最少花费
(不要认为是DP)

通过上述，可以简化成求

1. 在字符串尾添加s[i]    
### f[i+1][j]

1. 在字符串首添加sj
### 	f[i][j-1]
1. 删除字符串首si 
### 		f[i+1][j]

1. 删除字符串尾sj 
### 		f[i][j-1]

## 注意：都是化简过的(因为添加之后首尾相同，所以是求f[i+1][j-1],但是只在单独一边增加或删除了，就是求f[i+1][j]或f[i][j-1])



------------
这样我们可以发现有重叠子问题。该怎么优化呢？

#### 因为只有增加和删除的花费不同，题目要求的是最小花费，所以求出min(增加字母x的花费，删除字母x的花费)  再加上就OK了。



------------

下面贴代码
```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,ans;
int a[100000];
//增加字母x的花费 
int b[100000];
//删除字母x的花费 
int f[3000][3000];
char s[100000];
//原字符串 


//记搜 
int work(int i,int j)
{
	if(i>=j) return 0;
	//长度小于等于0，无花费。 
	if(f[i][j]!=-1) return f[i][j];
	f[i][j]=0;
	
	if(s[i]==s[j]) return f[i][j]=work(i+1,j-1);
	//首尾相同，直接跳过。 
	
	//核心代码 
	f[i][j]=min(work(i,j-1)+min(a[s[j]-'a'+1],b[s[j]-'a'+1]),work(i+1,j)+min(a[s[i]-'a'+1],b[s[i]-'a'+1]));
	// min(a[s[j]-'a'+1],b[s[j]-'a'+1]) 表示 增加s[j]的花费 和 删除s[j]的花费 的最小花费 
	// min(a[s[i]-'a'+1],b[s[i]-'a'+1]) 以此类推。 
	return f[i][j];
}


int main()
{
	char x;
	memset(f,-1,sizeof(f));
	scanf("%d%d\n",&n,&m);
	for(int i=1;i<=m;i++)
		cin>>s[i];
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		scanf("%d%d",&a[x-'a'+1],&b[x-'a'+1]);
		//存入花费 
	}
	ans=work(1,m);
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Plus_Ultra (赞：1)

一. 题目大意：

- 给你长度为n的字符串，其中有m种字符.

- 每种字符都有两个值，分别是插入这个字符的代价，删除这个字符的代价.

- 让你求将原先给出的那串字符变成一个回文串的最小代价.

二. 具体解法：

-  dp[ i ][ j ] 代表区间i到区间j成为回文串的最小代价，那么对于dp[i][j]有三种情况：


		1. dp[i + 1][j] 表示区间 i 到区间 j 已经是回文串了的最小代价，那么对于 s[i] 这个字母，我们有两种操作，删除与添加，对应有两种代价，dp[i + 1][j] + ins[s[i]] 或 dp[i + 1][j] + del[s[i]] ，取这两种代价的最小值.
        
        2. dp[i][j - 1] 表示区间 i 到区间 j - 1 已经是回文串了的最小代价，那么对于 s[j] 这个字母，同样有两种操作，dp[i][j - 1] + ins[s[j]] 或 dp[i][j - 1] + del[s[j]] ，取最小值.
        
        3. 若是 s[i] == s[j] ，dp[i + 1][j - 1] 表示区间i+1到区间 j - 1 已经是回文串的最小代价，那么对于这种情况，我们考虑 dp[i][j] 与 dp[i + 1][j - 1] 的大小.
        
- 三种情况取min即可.

下面上代码（其实我知道各位大佬也不需要代码）：

```
#include<iostream>
#include<cstring>

#define N 2019

using namespace std;

int n,m,dp[N][N],del[N],ins[N];
char s[N],c;

int main()
{
	cin>>m>>n>>s+1;
	for(int i=1;i<=m;i++)
	{
		cin>>c;
		cin>>ins[c]>>del[c];
		//不能cin>>c>>ins[c]>>del[c];
	}
			
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++)  dp[i][i]=0;//自己到自己当然没有花费

	for(int len=1;len<=n;len++)//普通序列DP模板
	  	for(int i=1;i+len<=n;i++)
		{
			int j=i+len;
			if(s[i]==s[j])//相等
			{
				if(j-i==1)  dp[i][j]=0;//特判情况
				else  dp[i][j]=dp[i+1][j-1];
			}  
			dp[i][j]=min(dp[i][j],dp[i+1[j]+min(del[s[i]],ins[s[i]]));
			dp[i][j]=min(dp[i][j],dp[i][j-1]+min(del[s[j]],ins[s[j]]));
		}
		
	cout<<dp[1][n]<<endl;
	
	return 0;
}

```

去掉空行30来行，也是比较短了.

###  _[Plus Ultra!](https://www.luogu.org/blog/OnePunchManGO/)_ 




---

## 作者：楠枫 (赞：0)

## 区间$DP$
[题目](https://www.luogu.com.cn/problem/P2890)  

汉化版[传送门](https://www.luogu.com.cn/blog/nanfengzjy/p2890-usaco07opencheapest-palindrome-g-han-hua-ban)

这道题转移数组 $f$ 是表示的是 $f[i][j]$ 为修正字符串中 $i,j$ 区间为回文串的最小代价。

则有转移方程 ：
$$
f[i][j]=\min(f[i+1][j]+\min(a1,a2),f[i][j-1]+\min(b1,b2));
$$
$a1,a2$ 分别为添加，删掉第 $i$ 个字符所需的费用， $b1,b2$ 同理。所已此转移方程意思就是说 $f[i+1][j]$ $f[i][j-1]$ 是回文串，所以若要从此两种状态转移到 $f[i][j]$ 那么就要删除或插入第 $i$ 个字符， $OR$ 删除或插入第 $j$ 个字符。最后再取它们的最小值。


如果第 $i$ 个字符等于第 $j$ 个字符，那么又有一种新的状态转移。
$$
f[i][j]=\min(f[i+1][j-1],f[i][j])
$$
$AC\kern 0.5em CODE$:
```cpp
#include<bits/stdc++.h>
using namespace std;
int cost[2001][2];
char ch[30];
int f[2001][2001];
char s[2001];
int n,m;
int main() {
    scanf("%d%d%s",&n,&m,s+1);
    for (int i=1;i<=n;i++) {
        int a,b;//输入
        cin >> ch[i];//此处不建议使用scanf("%c"),会将空格一块输入
        scanf("%d%d",&a,&b);
        cost[ch[i]-'a'][0]=a;//记录此字符删除，加入的费用
        cost[ch[i]-'a'][1]=b;
    }
    memset(f,0x4f,sizeof(f));//求最小值，要先初始化为最大值
    for (int i=1;i<=m;i++) {
        f[i][i]=0;//一个字符也是回文串，费用是0
        for (int j=1;j<i;j++) {
            f[i][j]=0;//将反区间也记为0
        }
    }
    for (int l=1;l<=m;l++) {
         for (int i=1;i<=m-l;i++) {//妥妥的区间DP
              int j=i+l;
              f[i][j]=min(f[i+1][j]+min(cost[s[i]-'a'][0],cost[s[i]-'a'][1]),f[i][j-1]+min(cost[s[j]-'a'][0],cost[s[j]-'a'][1]));
              if (s[i]==s[j]) {
              	  f[i][j]=min(f[i+1][j-1],f[i][j]);//状态转移
              }
          }
     }
     printf("%d\n",f[1][m]);//输出，第1位到最后一位变成回文串的费用
     return 0;
}
```
此解有 $m^2$ 个状态，有两种决策，所以时间复杂度应为 $O(4m^2)$ 。

---

## 作者：WanderingTrader (赞：0)

这是一道 **区间dp** 题
### 题目分析
区间dp，顾名思义，就是根据区间来设计状态，那我们也来试一下吧。  
1. 设计状态：设 $dp_{i,j}$ 为将 $[i,j]$ 这个区间内的字符串修改为回文串的最小花费；
2. 转移方程：这个嘛……好像不太好想，那我们先放一放；
3. 边界条件：分三种  
（1） $i=j$，此时 $dp_{i,j}=0$  
（2）$i+1=j$ 此时 $dp_{i,j}=\min\ \{ins[str[i]],del[str[i]],ins[str[i+1]],del[str[i+1]]\}$，也就是插入或删除两个字符中的任意一个，都可以构成回文串，在四种方案中取最小花费。  
（3）暂且设成 $\infty$  

那么状态转移方程究竟是什么呢？  
确实是一个很毒瘤的方程。  
以样例为例：  
`abcb`  
1. 如果要算 $dp_{1,4}$，我们可以先算出 $dp_{1,3}$，然后将最后一个字符`b`删除或插入在字符串开头，在两种方案中取最小，即：  
$dp_{i,j}=dp_{i,j-1}+\min\{del[str[j]],ins[str[j]\}$  
2. 同样，我们也可以算出 $dp_{2,4}$，然后将第一个字符`a`插入字符串末尾，或者直接删除，在原有基础上再取最小，即：  
$dp_{i,j}=\min\{dp_{i,j},dp_{i+1,j}+\min\{del[str[i]],ins[str[i]\}\}$  
还有没有别的情况呢？答案是肯定的  
3. 如果 $str[i]=str[j]$，那么  
$dp_{i,j}=\min\{dp_{i,j},dp_{i+1,j-1}\}$   
否则，只有将两个字符都删除这一种情况：  
$dp_{i,j}=\min\{dp_{i,j},dp_{i+1,j-1}+del[str[i]]+del[str[j]]\}$   

至此，转移方程结束。  
如果硬要合并成一个方程，将会非常长，这里就不这样做了。
### 代码
首先我们读入数据并初始化（这里对str做了一个移位处理）：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200
#define M 2005
#define INF 1e16
#define ll long long
ll ins[N],del[N];
ll dp[M][M];
int main()
{
	int n,m;
	string str;
	scanf("%d%d",&n,&m);
	cin >> str;
	str = "0"+str;
	for(int i=1;i<=n;++i)
	{
		char ch;
		cin >> ch;
		scanf("%lld%lld",&ins[ch],&del[ch]);
	}
	return 0;
}
```
然后对 $dp_{i,i},dp_{i,i+1}$ 做初始化：
```cpp
for(int i=1;i<=m;++i)
	for(int j=1;j<=m;++j) if(i!=j)
		dp[i][j] = INF; 
for(int i=1;i<m;++i)
{
	if(str[i]==str[i+1])
		dp[i][i+1] = 0;
	else 
		dp[i][i+1] = min(min(ins[str[i]],del[str[i]]),min(ins[str[i+1]],del[str[i+1]]));
}
```
最后是主体转移方程  
有两个易错点：
1. 这里 $dp_{i,j}$ 有依赖于 $dp_{i+1,j}$ ，所以i要倒着枚举
2. 区间的长度不可以小于3，即赋初值时 $i=m-2,j=i+2$ ，否则初始化的部分会被覆盖掉。

代码：
```cpp
for(int i=m-2;i;--i)
		for(int j=i+2;j<=m;++j)
		{
			ll ans=dp[i+1][j]+min(ins[str[i]],del[str[i]]);
			ans=min(ans,dp[i][j-1]+min(ins[str[j]],del[str[j]]));
			ans=min(ans,dp[i+1][j-1]+(str[i]!=str[j])*(del[str[i]]+del[str[j]]));
			dp[i][j] = ans;
		}
```
这里我们借助了一个 **布尔值在整数中的值为0或1，将判断条件转成具体数值**，简化了转移方程3的写作。如果 $str[i]=str[j]$，那么`(str[i]!=str[j])`会返回0，将后面的算式答案直接抹去了。  

最后输出 $dp_{1,m}$ 即可
```cpp
printf("%lld\n",dp[1][m]);
```

全部代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200
#define M 2005
#define INF 1e16
#define ll long long
ll ins[N],del[N];
ll dp[M][M];
int main()
{
	int n,m;
	string str;
	scanf("%d%d",&n,&m);
	cin >> str;
	str = "0"+str;
	for(int i=1;i<=n;++i)
	{
		char ch;
		cin >> ch;
		scanf("%lld%lld",&ins[ch],&del[ch]);
	}
	for(int i=1;i<=m;++i)
		for(int j=1;j<=m;++j) if(i!=j)
			dp[i][j] = INF; 
	for(int i=1;i<m;++i)
	{
		if(str[i]==str[i+1])
			dp[i][i+1] = 0;
		else 
			dp[i][i+1] = min(min(ins[str[i]],del[str[i]]),min(ins[str[i+1]],del[str[i+1]]));
	}
	for(int i=m-2;i;--i)
		for(int j=i+2;j<=m;++j)
		{
			ll ans=dp[i+1][j]+min(ins[str[i]],del[str[i]]);
			ans=min(ans,dp[i][j-1]+min(ins[str[j]],del[str[j]]));
			ans=min(ans,dp[i+1][j-1]+(str[i]!=str[j])*(del[str[i]]+del[str[j]]));
			dp[i][j] = ans;
		}
	printf("%lld\n",dp[1][m]);
	return 0;
}
```
顺利完成了。  
区间dp的调试方法也很简单，算完以后加上这几行（注释去掉）就行了，对于较小的数据，完全可以手算对比：
```cpp
//	for(int i=1;i<=m;++i)
//		for(int j=i;j<=m;++j)
//			printf("%d %d %lld\n",i,j,dp[i][j]);
```
建议大家做完此题 ~~挑战~~ 直接切掉 [P2758 编辑距离](/problem/P2758)，和此题的想法十分类似。  

$$\texttt{The End.}$$

---

## 作者：Illusory_dimes (赞：0)

一开始，按照一个insert数组，一个delete数组，卡了一个小时
# 我太难了
接着，后知后觉地发现，这是一道好题(差点没发现是区间dp)
# 我太蒻了
然后，我开始分析，两个数组不是办法。

先用个f二维数组表示使s(i,j)成为回文的最小花费

其次，蒻蒻的我发现了

当s(i+1,j)已经是回文时，删第i个与在j+1处加一个s[i]是一样的，所以加一个val数组表示处理这个字母的较小值

去掉两个数组，违背了我的初衷...(幸好初衷是错的)
# 真香
接着，看代码吧
```cpp
#include<bits/stdc++.h>
#define min(a,b) a<b?a:b
using namespace std;
int n,m,val[2020],f[2020][2020];
char s[2020];//f(i,j)为把s(i,j)变回文的价钱 
int main()
{
	scanf("%d%d%s",&n,&m,s+1);
	char a[3];int dlt,ist;
	for(int i=1;i<=n;i++)
	{
		scanf("%s%d%d",a,&dlt,&ist);
		//abcb=>bcb 回文cost dlt
		//abcb=>abcba 回文cost ist
		//所以,此时,删与加等价,就取较小值
		val[a[0]-'a'+1]=min(dlt,ist);
	}
	memset(f,127,sizeof(f));
	for(int i=1;i<=m;i++)
	{
		f[i][i]=0;
		if(s[i]==s[i+1])
		f[i][i+1]=0;
	}
	for(int l=0;l<=m;l++)
	for(int i=1;i<=m;i++)
	{
		int j=i+l;
		int p=s[i-1]-'a'+1;
		int q=s[j+1]-'a'+1;
		if(p==q)f[i-1][j+1]=min(f[i][j],f[i-1][j+1]);
		//i-1与j+1可以构成回文(玄学一号)
		f[i-1][j]=min(f[i][j]+val[p],f[i-1][j]);
		//塞i-1的点(玄学二号)
		f[i][j+1]=min(f[i][j]+val[q],f[i][j+1]);
		//塞j+1的点(玄学三号)
	}
	printf("%d",f[1][m]);
	return 0;
}
```
竟然一次就过了，玄学nb!!!

注：l是长度...

写得不好，大佬勿喷

但
# 若有帮助，那将是我莫大的荣幸
容我再唠叨一句
# 真香

---

## 作者：ljcljc (赞：0)

### 1.题目概述
  对于一个长$M$并且由$N$个小写字母构成的字符串$S$。通过增、删字母将其变成回文串（增删特定字母的花费不同），求最小花费。
  

------------

### 2.解题思路
区间$DP$

其中$f[i][j]$表示 使字符串$S$中的第$i$到第$j$这段区间的字符变为回文串 的 最小花费

则 动态转移方程 为：

①若$s[i]$ == $s[i+l]$ 则$f[i][i+l]$ = $f[i+1][i+l-1]$

②$f[i][i+l]=min(min(v1,v2),min(v3,v4));$

其中：$v1=f[i][i+l-1] + $增加该字母代价；

$v2=f[i][i+l-1] + $删除该字母代价；

$v3=f[i+1][i+l] + $增加该字母代价；

$v4=f[i+1][i+l] +$ 删除该字母代价；




------------


### 3.AC代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 255;
const int MAXM = 2010;
struct pt {
	int x, y;
} a[MAXN];
int n, m, f[MAXM][MAXM];
char s[MAXM];

int main() {
	cin >> m >> n >> s+1;
	for(int i=1; i<=m; i++) {
		char c;
		cin >> c;
		cin >> a[(int)(c)].x >> a[(int)(c)].y;
	}
	memset(f,63, sizeof(f));
	for(int i=1; i<=n; i++) {
		f[i][i]=0;
	}
    for(int i=0; i<=n+1; i++) {
        for(int j=0; j<i; j++) {
        	f[i][j]=0;
        }
    }
	for(int k=1; k<=n; k++) {
		for(int i=1; i+k<=n; i++) {
			int j=k+i;
			f[i][j] = min(f[i+1][j]+min(a[(int)s[i]].x, a[(int)s[i]].y), f[i][j-1]+min(a[(int)s[j]].x, a[(int)s[j]].y));
			if(s[i]==s[j]) {
				if(j-i==1) f[i][j]=0;
				else f[i][j] = min(f[i][j], f[i+1][j-1]);
			}
		}
	}
	cout << f[1][n];
	return 0;
}
```


---

## 作者：Dream_It_Possible (赞：0)

我们设f[i][j]表示从字符从i到j的最小花费。

然后用区间dp的思想，先算小的状态，用小的状态合并，算出大的状态，最终得到答案。

状态转移方程：
```cpp
f[i][j]=min(f[i+1][j]+a[c[i]],min(f[i][j-1]+a[c[j]],min(f[i+1][j]+b[c[i]],f[i][j-1]+b[c[j]])));
	if (c[i]==c[j])
	f[i][j]=f[i+1][j-1];
```

初始化只能将一半置位INF，不然会WA。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int a[2005],b[2005];
char c[2005];
int f[2005][2005];
int main()
{
	int n,m,l,i,j;
	char A;
	int B,C;
	cin>>n>>m;
	cin>>(c+1);
	for (i=1;i<=n;i++)
	{
		cin>>A>>B>>C;
		a[A]=B;
		b[A]=C;
	}
	for (i=0;i<2005;i++)
	{
		for (j=i;j<2005;j++)
		f[i][j]=2147483647;//初始化
	}
	for (i=0;i<2005;i++)
	f[i][i]=0;//初始化
	for (l=1;l<=m;l++)
	{
		for (i=1;i<=m;i++)
		{
			j=i+l;
			if (j>m)
			break;
			f[i][j]=min(f[i+1][j]+a[c[i]],min(f[i][j-1]+a[c[j]],min(f[i+1][j]+b[c[i]],f[i][j-1]+b[c[j]])));//取四种状态中最小
			if (c[i]==c[j])//两边字符相等，不用花费
			f[i][j]=f[i+1][j-1];
		}
	}
	cout<<f[1][m];
	return 0;	
} 
```

---

## 作者：aakennes (赞：0)

# 【区间DP】低价回文


# 【思路】

对于一块新区间，要想保证区间中的元素是回文词，其实就可以转化成保证首元素和尾元素相同，这样就转化成了一个递归的子问题，显然可以用区间DP来搞。

如果相同，那么$f[i][j]$就能直接从$f[i-1][j-1]$转移过来，而且不用代价。

如果不同，我们可以只处理首元素和尾元素中的一个。

*	处理首元素，我们可以从$f[i+1][j]$转移过来，然后要么删除首元素，要么在尾端插入一个首元素。
*	处理尾元素，我们可以从$f[i][j-1]$转移过来，同前。

# 【代码】

```
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=2e5+5,INF=0x3f3f3f3f,maxe=2e3+5;
int n,m,f[maxe][maxe],low[maxn],ans,del[maxn],add[maxn];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main(){
	m=read(),n=read();
	char a[maxn];
	cin>>a+1;
	for(int i=1;i<=m;i++){
		char x;
		cin>>x;
		cin>>add[x]>>del[x];
	}
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n+1;i++)f[i][i]=0;//初始化
	for(int d=2;d<=n;d++){
		for(int i=1,j;(j=i+d-1)<=n;i++){
			if(a[i]==a[j]){//相等
				if(i==j-1)f[i][j]=0;//亲测必须加
				f[i][j]=min(f[i][j],f[i+1][j-1]);
			}
			else f[i][j]=min(f[i+1][j]+min(del[a[i]],add[a[i]]),f[i][j-1]+min(del[a[j]],add[a[j]]));//不相等，要么在对a[i]删除或插入，要么对a[j]删除或插入
		}
	}
	cout<<f[1][n];
	return 0;
}
```


---

