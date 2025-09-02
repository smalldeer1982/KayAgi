# [ABC344D] String Bags

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc344/tasks/abc344_d

あなたは最初、空文字列 $ S $ を持っています。  
 さらに、文字列がいくつか入った袋 $ 1,2,\dots,N $ があります。  
 袋 $ i $ には $ A_i $ 個の文字列 $ S_{i,1},S_{i,2},\dots,S_{i,A_i} $ が入っています。

これから、以下の手順を $ i=1,2,\dots,N $ について繰り返します。

- 以下のふたつの行動のうち、どちらかを選択して行う。
  - $ 1 $ 円を支払い、袋 $ i $ からちょうどひとつの文字列を選択して $ S $ の末尾に連結する。
  - 何もしない。
 
文字列 $ T $ が与えられるとき、最終的に $ S $ と $ T $ を一致させるために必要な最小の金額を求めてください。  
 但し、どのようにしても最終的な $ S $ を $ T $ に一致させることができない場合、 `-1` と出力してください。

## 说明/提示

### 制約

- $ T $ は長さ $ 1 $ 以上 $ 100 $ 以下の英小文字からなる文字列
- $ N $ は $ 1 $ 以上 $ 100 $ 以下の整数
- $ A_i $ は $ 1 $ 以上 $ 10 $ 以下の整数
- $ S_{i,j} $ は長さ $ 1 $ 以上 $ 10 $ 以下の英小文字からなる文字列
 
### Sample Explanation 1

例えば、以下のようにすると $ 2 $ 円で最終的な $ S $ と $ T $ を一致させることができ、これが必要な金額の最低値であることが示せます。 - $ i=1 $ について、袋 $ 1 $ から `abc` を選択し $ S $ の末尾に連結する。 $ S= $ `abc` となる。 - $ i=2 $ について、何もしない。 - $ i=3 $ について、袋 $ 3 $ から `de` を選択し $ S $ の末尾に連結する。 $ S= $ `abcde` となる。

### Sample Explanation 2

どのようにしても最終的な $ S $ と $ T $ を一致させることができないので、 `-1` と出力してください。

## 样例 #1

### 输入

```
abcde
3
3 ab abc abcd
4 f c cd bcde
2 e de```

### 输出

```
2```

## 样例 #2

### 输入

```
abcde
3
2 ab abc
3 f c bcde
1 e```

### 输出

```
-1```

## 样例 #3

### 输入

```
aaabbbbcccc
6
2 aa aaa
2 dd ddd
2 ab aabb
4 bbaa bbbc bbb bbcc
2 cc bcc
3 ccc cccc ccccc```

### 输出

```
4```

# 题解

## 作者：CodingOIer (赞：8)

## [ABC344D] String Bags 题解

### 思路分析

显然是 dp 题。

我们设 $dp_{i, j}$ 的定义是：$i$ 为当前选择第 $i$ 组字符串，$j$ 表示当前总长度，储存最少的代价。

则可以写出 dp 代码：

```cpp
for (int i = 1; i <= n; i++)
{
    for (int j = 1; j <= l; j++)
    {
        dp[i][j] = dp[i - 1][j];
        for (auto &k : p[i])
        {
            if (k.size() > j || !check(j, k))
            {
                continue;
            }
            dp[i][j] = std::min(dp[i][j], dp[i - 1][j - k.size()] + 1);
        }
    }
}
```

其中 `bool check(int w, std::string k)` 返回 $s$ 的后 $w$ 位字符是否与 $k$ 相匹配。

### 代码实现

算比较基础的 dp 了。

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
constexpr int MaxN = 1e2 + 5;
int n, l;
int dp[MaxN][MaxN];
char s[MaxN];
char t[MaxN];
std::vector<std::string> p[MaxN];
bool check(int w, std::string k)
{
    for (int i = w; i >= w - k.size() + 1; i--)
    {
        if (s[i] != k[k.size() - (w - i + 1)])
        {
            return false;
        }
    }
    return true;
}
int main()
{
    scanf("%s", s + 1);
    scanf("%d", &n);
    l = strlen(s + 1);
    for (int i = 1; i <= n; i++)
    {
        int m;
        scanf("%d", &m);
        for (int j = 1; j <= m; j++)
        {
            scanf("%s", t);
            p[i].push_back(t);
        }
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= l; j++)
        {
            dp[i][j] = 0x3f3f3f3f;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= l; j++)
        {
            dp[i][j] = dp[i - 1][j];
            for (auto &k : p[i])
            {
                if (k.size() > j || !check(j, k))
                {
                    continue;
                }
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j - k.size()] + 1);
            }
        }
    }
    printf("%d\n", dp[n][l] == 0x3f3f3f3f ? -1 : dp[n][l]);
    return 0;
}
```

---

## 作者：coderJerry (赞：7)

### 题目描述：[传送门](https://www.luogu.com.cn/problem/AT_abc344_d)
### 题目分析
分组背包板子。题目分析跟着代码一起看更好哦！

我们用 ```dp[x]``` 表示长度为 $x$ 时最少要给多少钱，如果当前字符串是 $t$ 的子串，且当前（也就是代码中的 ```dp[j]```）为 ```-1```（没被更新过） 或者比加入这个字符串前的最小价值（也就是代码中的 ```dp[j-k]```） 要大时，就更新 ```dp[j]```。最后的 ```dp[len]```（```len``` 是 $t$ 的长度） 就是答案。
### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,dp[110];
string t,s[110];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    for(int i=1;i<=100;i++) dp[i]=-1;
    dp[0]=0;
    cin>>t>>n;
    int len=t.size();
    for(int i=1;i<=n;i++){
        cin>>a;
        for(int h=1;h<=a;h++) cin>>s[h];
        for(int j=len;j>=1;j--){
            for(int u=1;u<=a;u++){
                int k=s[u].size();
                if (j-k>=0&&t.substr(j-k,k)==s[u]&&dp[j-k]!=-1){
                    int tmp=dp[j-k]+1;
                    if(dp[j]==-1||dp[j]>tmp) dp[j]=tmp;
                }
            }
        }
    }
    cout<<dp[len]<<endl;
    return 0;
}
```

---

## 作者：FBW2010 (赞：7)

# 题意简述

[传送门](https://www.luogu.com.cn/problem/AT_abc344_d)

有 $n$ 个背包，每个背包中有 $a_i$ 个字符串。现在从 $1$ 到 $n$ 号背包中每个依次选 $0$ 或 $1$ 个字符串使他们连起来为字符串 $T$，求最少选多少个。

# 思路

看到许多大佬用 dp 做出了这道题，蒟蒻不才，献上一篇搜索的题解。

我们根据背包编号进行搜索，每次从当前背包中的字符串选择一个，或者不选。最后看能不能组成 $T$，如果能就更新答案。

但如果只是这样，复杂度极高，肯定会 TLE。这时我们需要~~使用 dp~~ 引入几个剪枝：

+ 每次选择时，只有当前字符串连上所选字符串能组成 $T$ 的前面一部分才选择。

+ 如果当前所选字符串大于等于目前的 $ans$，就没必要继续了。

现在这个搜索看起来很 OK 了，但交上去还会超时 $5$ 个点。这时我们加入一个最为重要的剪枝：

+ 定义 $f_{i,j}$ 为搜索到第 $i$ 个背包，字符串长度为 $j$ 的最少选择数，如果当前次数大于等于它，就直接退出，否则更新最小值。~~咋这么像 dp 呢。~~

此时，我们就可以快乐的 AC 了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=2e9,a[105],f[105][1005];
string t,s[105][15];
void DFS(int x,int sum/*已选择的字符串个数*/,string k/*当前组成的字符串*/){
	//更新答案 
	if(x>n){
		if(k==t)ans=min(ans,sum); 
		return;
	}
	
	//剪枝 
	if(sum>=ans||sum>=f[x][k.size()])return; 
	f[x][k.size()]=sum;
	
	//枚举选哪个 
	for(int i=1;i<=a[x];i++){
		string p=k+s[x][i];
		if(p.size()<=t.size()&&p==t.substr(0,p.size())){
			DFS(x+1,sum+1,p);
		}
	}
	
	//不选 
	DFS(x+1,sum,k);
}
int main(){
	cin>>t>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=1;j<=a[i];j++){
			cin>>s[i][j];
		}
		for(int j=0;j<=1000;j++){
			f[i][j]=2e9; //初始化 f 数组 
		}
	}
	DFS(1,0,"");
	if(ans==2e9)printf("-1");
	else cout<<ans;
	return 0;
}
```

---

## 作者：Vocaloid世末歌者 (赞：4)

本文同步发表于 [cnblogs](https://www.cnblogs.com/cppom/p/-/ABC344D-tijie)。

赌狗天天输的一集。

### 大意

你最开始有一个空字符串 $S$。

你还有编号为 $1, 2, \dots, N$ 的袋子，每个袋子都包含一些字符串。

袋子 $i$ 包含 $A_i$ 个字符串 $S_{i,1}, S_{i,2}, \dots, S_{i,A_i}$。

对 $i = 1, 2, \dots, N$ 重复以下步骤**仅一次**（这里原题没有讲清楚）：

- 执行以下两个操作之一：
  - 支付 $1$ 日元，从袋子 $i$ 中选择一个字符串，并将其接到 $S$ 的末尾。
  - 睡觉（啥都不干）。

给定一个字符串 $T$，求使最后 $S$ 等于 $T$ 所需的最小金额。

如果无法使最后的 $S$ 等于 $T$，则打印 `-1`。

### 思路

我最开始打了个爆搜，众所周知寄了。

然后疯狂推 DP，一阵木大木大后我开窍了：

用 $dp_{i,j}$ 表示处理到了第 $i$ 个袋子，现在这个字符串已经有 $j$ 位（而且与 $t$ 匹配）了。

初始化所有位置为无穷大（比如说我取的一千多，够了）。

首先枚举每个袋子。

然后肯定是要 `dp[i][j]=dp[i-1][j]` 的（万一你这组没出息你要保留实力）

然后你枚举一下袋子里的哪个字符串，再枚举一下 $k$（加上这个字符串之前的长度）。

如果加上这个字符串后能与 $t$ 匹配，`dp[i][k+s[i][j].size()-1]=min(dp[i][k+s[i][j].size()-1],dp[i-1][k-1]+1);`。注意我的代码是从 $1$ 开始的。

最后看一下 `dp[n][t.size()]`，如果不是无穷大，就输出它，否则就输出 `-1`。

----------------------

Posted on [cnblogs](https://www.cnblogs.com/cppom/p/-/ABC344D-tijie) too. But I didn't write English solution there.

I'm a big fool.

### Solution

I used DFS at first, and got TLE.

Then I started to think about DP:

$dp_{i,j}$ means we handled to the $i$th bag, and already matched $j$ letters with $t$.

Initialization the whole $dp$ array to infinity.

Then enumerate the bags.

Remember to `dp[i][j]=dp[i-1][j]` at first.

And then enumerate the strings in this bag, then $k$（$k$ means the lenth of the string before adding this string）.

If after adding this string the whole string can match with $t$, `dp[i][k+s[i][j].size()-1]=min(dp[i][k+s[i][j].size()-1],dp[i-1][k-1]+1);` to update.

Print `dp[n][t.size()]` at last. Of course, if `dp[n][t.size()]` equals to infinity, printf $-1$ instead.

### 代码/code

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define N 1000010
#define MOD 998244353
#define esp 1e-8
#define INF 999999999999999999
#define LL long long
#define rep(i,a,b,g) for(LL i=a;i<=b;i+=g)
#define rem(i,a,b,g) for(LL i=a;i>=b;i-=g)
#define repn(i,a,b,g) for(LL i=a;i<b;i+=g)
#define remn(i,a,b,g) for(LL i=a;i>b;i-=g)
#define pll pair<LL,LL>
#define mkp(x,y) make_pair(x,y)
#define i128 LL
#define lowbit(x) ((x)&(-(x)))
#define lc (u<<1)
#define rc (u<<1|1)
using namespace std;
void read(i128 &x)
{
	i128 f=1;
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
void write(i128 x)
{
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
LL n,a[110],dp[110][110];
string t,s[110][20];
int main()
{
	cin>>t>>n;
	rep(i,0,n,1)rep(j,1,t.size(),1)dp[i][j]=1029;
	rep(i,1,n,1)
	{
		cin>>a[i];
		rep(j,1,a[i],1)cin>>s[i][j];
	}
	rep(i,1,n,1)
	{
		rep(j,0,t.size(),1)dp[i][j]=dp[i-1][j];
		rep(j,1,a[i],1)
		{
			for(LL k=1;k+s[i][j].size()-1<=t.size();k++)
			{
				bool f=1;
				rep(l,1,s[i][j].size(),1)
				{
					if(s[i][j][l-1]!=t[k+l-2])
					{
						f=0;
						break;
					}
				}
				if(f)
				{
					dp[i][k+s[i][j].size()-1]=min(dp[i][k+s[i][j].size()-1],dp[i-1][k-1]+1);
				}
			}
		}
	}
	if(dp[n][t.size()]==1029)cout<<-1<<endl;
	else cout<<dp[n][t.size()]<<endl;
	return 0;
}
```

---

## 作者：liangbob (赞：2)

## $\mathtt{Pre\ Explanation}$

口胡出奇迹！STL 出奇迹！

本题解中 $|s|$ 表示字符串 $s$ 的长度。

## $\mathtt{Solution}$

作为一位合格的 OIer，你第一眼看到本题的想法是：暴力或者贪心。暴力在 Atcoder 赛制中显然不可取，于是你考虑贪心。

你在想：贪心的策略应该是每组选择最长的那个？可是不行啊，万一你选了最长的，后面接不上了怎么办？很有可能选个短的，后面再选个短的就可以接上？

既然贪心不行，那么你就开始思考 DP。你参考 LIS 的定义方法，决定定义 $f_i$ 为凑出 $T$ 的前 $i$ 位的最小代价。这个时候你又发现你需要保证每个组只能选一个，为了不重复选择，你想起了做 01 背包时的状态定义，选择增加一维，于是你把定义改成了 $f(i,j)$ 代表用前 $i$ 组的字符串凑出 $T$ 的前 $i$ 位的最小代价。

有了状态定义，你开始考虑转移。对于第 $i$ 组，你发现可以啥也不做，于是你写下了 $f(i,j)=f(i-1,j)$。但是第 $i$ 组还可以选择一个字符串转移，每个字符串都有转移的可能，于是你选择枚举这个组的所有字符串 $s_k$（$1 \le k \le c_i$）。显然，当一个字符串是 $T$ 的后缀时可以转移。抛去这个后缀，前面的部分，也就是 $T$ 的前 $j-|s_k|$ 位，就由前 $i - 1$ 组负责组成，这样才可以保证不重复，组成的代价就是 $f(i-1,j-|s_k|)$，而接上这个后缀本身还有 $1$ 点代价。于是你写下了下面这条式子：

$$f(i,j)=\min\{f(i,j),f(i-1,j-|s_k|) + 1\}$$

当然，你知道这个转移只有在 $s_k$ 是 $T$ 的后缀时才可以进行。而你又考虑到 $f(i,j)=f(i-1,j)$ 对于每个 $j$ 都成立，因此你决定在转移前先复制一下 $f(i-1)$ 到 $f(i)$，这样子就只用考虑第二种转移了。

现在你苦于怎么判断后缀，这个时候你突然想起了 substr，你只需要通过它取出最后 $|s_k|$ 位，然后再来看看是否与 $s_k$ 一样就可以了。

你开始敲代码，敲的时候发现如果 $|s_k|>j$，那么显然转移不了，直接跳过即可，还有就是要初始化数组全部为无穷大，这样会方便求最小。当然，你也记得在初始化完后，将 $f(0,0)$ 设置为 $0$，这样就可以正确地转移了。

最后，你成功地通过了此题。

## $\mathtt{Code}$

```cpp
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
//#define endl '\n'
#define IL inline
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

IL int read()
{
	int x = 0,f = 1;
	char c = getchar();
	while(c <'0'|| c >'9'){if(c == '-') f = -1;c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = getchar();
	return x * f;
}

void write(int x)
{
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, f[105][105], c[105];
string t, s[105][105];

int main()
{
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	// cout.tie(0);
	cin >> t;
	cin >> n;
	int m = t.size();
	for(int i = 1;i <= n;i++)
	{
		cin >> c[i];
		for(int j = 1;j <= c[i];j++)
		{
			cin >> s[i][j];
		}
	}
	memset(f, 0x7f, sizeof(f));
	f[0][0] = 0;
	for(int i = 1;i <= n;i++)
	{
		memcpy(f[i], f[i - 1], sizeof(f[i - 1]));
		for(int j = 1;j <= m;j++)
		{
			for(int k = 1;k <= c[i];k++)
			{
				int gft = s[i][k].size();
				if(gft > j) continue;
				if(t.substr(0, j).substr(j - gft) == s[i][k]) f[i][j] = min(f[i][j], f[i - 1][j - gft] + 1);
			}
		}
	}
	cout << (f[n][m] == 0x7f7f7f7f ? -1 : f[n][m]) << endl;
	return 0;
}
```

---

## 作者：tyr_04 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc344_d)

## 题目大意

给你一个字符串，并给你 $n$ 个字符串集，每个字符串集中又有 $a_i$ 个字符串，每个字符串集中**最多只能选择一个字符串**或**不选择任何字符串**。

问在最好情况下至少要用多少个字符集中的字符串构成原来的字符串（必须从前往后依次构成），如果无解则输出 $-1$。

## 题解

看一看数据范围，如果用搜索的话很有可能会超时。于是必须有一个更为优秀的算法，于是就想到了用 dp 来做。

如何 dp 呢？首先明确 dp 的定义，定义 $dp_i$ 表示当前构成前 $i$ 个字符时字符串集内字符串的最小使用次数。

那么我们只用枚举下一次状态转移的起始位置，再将现有的字符串与目前构成的字符串的结尾比较一下，看看是否符合条件就可以了（前提是前面的字符串集中的字符串可以构成目前状态下的字符串）。

当符合条件时，状态转移方程为：$dp[k+s.size()-1]=min(dp[k-1]+1,dp[k+s.size()-1])$

其中，$k$ 代表目前状态下字符串转移的起始位置，$s$ 代表现有的字符串。

当然，别忘记了初始化。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110],n,sum,ans=INT_MAX,dp[110];
string s[110][110];
char t[110];
int main()
{
	string p;
	cin>>p;
	sum=p.size()-1;
	for(int i=0;i<=sum;i++)
	{
		t[i+1]=p[i];
	}
	sum++;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		for(int j=1;j<=a[i];j++)
		{
			cin>>s[i][j];
		}
	}
	for(int i=0;i<=101;i++)
	{
		dp[i]=INT_MAX;
	}
	dp[0]=0;
	for(int i=1;i<=n;i++)//枚举字符串集数 
	{
		for(int k=sum;k>=1;k--)//枚举要转移的字符串的起始位置 
		{
			for(int j=1;j<=a[i];j++)//枚举字符串集内的字符串 
			{
				if(dp[k-1]!=INT_MAX&&k+s[i][j].size()-1<=sum)
				{
					bool z=0;
					int o=0;
					for(int l=k;l<k+s[i][j].size();l++)
					{
						if(t[l]!=s[i][j][o])
						{
							z=1;
							break;
						}
						o++;
					}
					if(z==1)
					{
						continue;
					}
					else
					{
						dp[k+s[i][j].size()-1]=min(dp[k-1]+1,dp[k+s[i][j].size()-1]);
					}
				}
			}
		}
	}
	if(dp[sum]==INT_MAX)
	{
		cout<<-1;
	}
	else
	{
		cout<<dp[sum];
	}
	return 0;
}
```

---

## 作者：kevinZ99 (赞：2)

这是一篇不用 $dp$ 的题解

## 题意
给你一个字符串 $S$，给你 $n$ 个包，每个包里有一些字符串，让你从第 $1$ 个包选择到第 $n$ 个。

对于每一个包你有两种操作

1、什么也不做。

2、选择其中的一个字符串将其接在你已经组成的字符串 $T$ 后面，这个操作消耗 $1$ 人民币。

如何利用最少的人民币将 $T$ 变为 $S$？

## 思路
第一眼：暴力搜索，但是超时。

所以需要优化，这是我从我大脑中突然想到了某一个奇奇怪怪的优化！

先初始化出一个数组 ```have```。

```have[i][j]```：从 $S$ 的第 $i$ 开始可以匹配到第 ```have[i][j]``` 个字符。

然后进行广搜。

状态：现在匹配到了字符串的 $S$ 的第 $x$ 个字符，用到了第 $y$ 个包，花费了 $z$ 人民币。

然后就可以快快乐乐的搜索啦！！！

## 代码
```cpp
/*
  Author:Kevin Z K Y
  t_limit:
  m_limit:
*/
//mod 998244353 \ 1e9+7 \ 1e9+9 \ 19260817 \ 104857601
#include <bits/stdc++.h>
#define putendl putchar('\n')
#define putspace putchar(' ')
#define rep(f,a) for(auto (f):(a))
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
using namespace std;
using vi = vector<int> ;
using ll = long long ;
using hint = __int128 ;
using PII = pair<int,int> ;
using PLL = pair<ll,ll> ;
const double eps=1e-6;
namespace IO{//快读没用
	#define gc() getchar()
    ll max(ll x,ll y){return x>=y?x:y;}
    ll min(ll x,ll y){return x<=y?x:y;}
    ll abs(ll x){return x<=0?-x:x;}
	double fabs(double x){return x<-eps?-x:x;}
	hint readh(){char ch;hint x=0,y=1;while(ch=gc(),(ch<48||ch>57)&&ch!=-1)if(ch==45)y=-1;x=ch-48;while(ch=gc(),47<ch&&ch<58)x=x*10+(ch-48);return x*y;}
	ll readl(){char ch;ll x=0,y=1;while(ch=gc(),(ch<48||ch>57)&&ch!=-1)if(ch==45)y=-1;x=ch-48;while(ch=gc(),47<ch&&ch<58)x=x*10+(ch-48);return x*y;}
	int readi(){char ch;int x=0,y=1;while(ch=gc(),(ch<48||ch>57)&&ch!=-1)if(ch==45)y=-1;x=ch-48;while(ch=gc(),47<ch&&ch<58)x=x*10+(ch-48);return x*y;}
	template<typename T>
	void writei(T x){if(x<0)putchar('-'),x=-x;int index_output=0;char s[40];do{s[index_output++]=x%10+48,x/=10;}while(x);while(index_output)putchar(s[--index_output]);}
	template<typename T>
	void writeis(T x,char c){writei(x);putchar(c);}
	void writess(string &s,int start){int index_output=start;while(s[index_output]!='\0')putchar(s[index_output++]);}
	void writesse(string &s,int start,int end){int index_output=start;while(s[index_output]!='\0'&&index_output<end+1)putchar(s[index_output++]);}
}
using namespace IO;
namespace my{
	void IOS(){ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);}
	string ot;
	string f;
	int n;
	int fl;
	bitset<105> vis[105];
	vector<string>t[105];
	int len[105];
	vector<PII>have[105];
	bool end=false;
	void init(){
		up(i,1,n){
			up(j,0,len[i]-1){
				int tl=t[i][j].length();
				up(k,0,fl-tl+1){
					bool flag=false;
					up(l,0,tl-1)
						if(f[k+l]!=t[i][j][l]){
							flag=true;
							break;
						}
					if(!flag)have[k].push_back({k+tl-1,i});
					if(k+tl-1==fl-1)end=true;
				}
			}
		}
		if(!end){
			cout<<"-1"<<'\n';
			exit(0);
		}
	}
	void bfs(){
		#define fst first
		#define sed second
		queue<pair<int,PII>>q;
		for(PII v:have[0])q.push({v.fst,{v.sed,1}}),vis[v.fst][v.sed]=1;
		while(!q.empty()){
			pair<int,PII> k=q.front();q.pop();
			if(k.fst==fl-1){
				cout<<k.sed.sed<<'\n';
				exit(0);
			}
			if(k.sed.fst==n&&k.fst!=fl-1)continue;
			for(PII v:have[k.fst+1]){
				if(v.sed<=k.sed.fst)continue;
				if(vis[v.fst][v.sed])continue;
				if(v.sed==n&&v.fst!=fl-1)break;
				q.push({v.fst,{v.sed,k.sed.sed+1}});
				vis[v.fst][v.sed]=true;
			}
		}
		#undef fst
		#undef sed
	}
	void solve(){
		IOS();
		cin>>f;
		fl=f.length();
		cin>>n;
		up(i,1,n){
			cin>>len[i];
			up(j,1,len[i]){
				string s;
				cin>>s;
				t[i].push_back(s);
			}
		}
		init();
		bfs();
		cout<<"-1"<<'\n';
	}
}
int main(){
//  	freopen("abc344d.txt","r",stdin);
//  	freopen("","w",stdout);
	int _=1;
	while(_--)my::solve();
	return 0;
}
```
然后在我的乱搞下成功的在4ms之内跑过了！！！

[提交记录](https://atcoder.jp/contests/abc344/submissions/51109361)

---

## 作者：Leo2011 (赞：1)

明显是 DP。

然后就开始分析：

状态：$dp_{ij} =$ 有 $i$ 个袋子且匹配 $T$ 的前缀的长度为 $j$ 时所需的最少钱数。

匹配 $T$ 的前缀的长度为 $j$ 就是前 $j$  个字符与 $T$ 的前 $j$ 个字符相同。

相对简单。

---
然后看转移。为了方便，咱不妨令 $|S|$ 为字符串 $S$ 的长度，其它的同理。

假设是要将第 $i$ 个袋子里的字符串 $L$ 接到 $S$ 的末尾，那么就只有 $S_{|S|+1}$ 与 $S_{|S|+|L|)}$ 依次对应时才能从 $dp_{(i-1)|S|}$ 转移到 $dp_{i|L|}$。

为啥呢？

不对应那你接哪儿去了？不是说好接到末尾吗？那你问啥呢，浪费表情:-(

那我不选呢？

不选你 $j$ 不变不就得了？

所以，转移部分就是：

```cpp
for (int i = 0; i < n; i++) {
		for (int j = 0; j < 110; j++) dp[i + 1][j] = dp[i][j];  // 同步过去
		int m;
		cin >> m;
		while (m--) {
			...判断是否满足上面的条件
				if (满足) dp[i + 1][j + sl] = min(dp[i + 1][j + sl], dp[i][j] + 1);
			}
		}
	}
```

上面`dp[i + 1][j + sl]`就是不选，`dp[i][j] + 1`就是选。

---

最后看一下时间复杂度。

$\Theta(NM|S|\cdot|T|)$。$M$ 为袋中字符串数量。

为啥？

你看我们上面的代码，不就是先遍历了一遍 $N$ 个袋子，再遍历字符串数量 $M$，每次判断相等挨个比较不就是 $|S|\cdot|T|$嘛。

结束~

---

ACCode：

```cpp
// Problem: D - String Bags
// Contest: AtCoder - 	Toyota Programming Contest 2024#3（AtCoder Beginner Contest 344）
// URL: https://atcoder.jp/contests/abc344/tasks/abc344_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)
/*Code by Leo2011*/
#include <bits/stdc++.h>

#define log printf
#define EPS 1e-8
#define INF 0x3f3f3f3f
#define FOR(i, l, r) for (int(i) = (l); (i) <= (r); ++(i))
#define IOS                      \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);            \
	cout.tie(nullptr);

using namespace std;

typedef __int128 i128;
typedef long long ll;
typedef pair<int, int> PII;

const int N = 110;
int dp[N][N];  // dp[i][j] = 前 i 个袋子中匹配 T 的前缀长度为 j 时所需的最少钱数。      
string t;

template <typename T>

inline T read() {
	T sum = 0, fl = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T>

inline void write(T x) {
	if (x < 0) putchar('-'), write<T>(-x);
	static T sta[35];
	int top = 0;
	do { sta[top++] = x % 10, x /= 10; } while (x);
	while (top) putchar(sta[--top] + 48);
}

int main() {
	IOS memset(dp, INF, sizeof(dp));
	dp[0][0] = 0;
	cin >> t;
	int tl = t.size(), n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 110; j++) dp[i + 1][j] = dp[i][j];
		int m;
		cin >> m;
		while (m--) {
			string s;
			cin >> s;
			int sl = s.size();  // 比较
			for (int j = 0; j + sl <= tl; j++) {
				bool flag = true;
				for (int k = 0; k < sl; k++)
					if (t[j + k] != s[k]) {
						flag = false;
						break;
					}
				if (flag) dp[i + 1][j + sl] = min(dp[i + 1][j + sl], dp[i][j] + 1);  // 状态转移方程
			}
		}
	}
	if (dp[n][tl] > 5e8) dp[n][tl] = -1;  // 过大就是祭了
	cout << dp[n][tl] << "\n";
	return 0;
}
```

[AC记录~](https://www.luogu.com.cn/record/150332762)

理解万岁！

---

## 作者：Otue (赞：1)

考虑 dp。定义 $dp_{i,j}$ 表示前 $i$ 个组拼成所给字符串前 $j$ 个字符的最小花费。

对第 $i$ 个组进行扫描，看这一个字符串能不能拼上去。

比赛时没有精细实现，所以代码看看就好了：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;

char a[N];
int m, cnt[105], dp[205][205]; 
string s[105][105]; 

signed main() {
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	cin >> (a + 1);
	int n = strlen(a + 1); 
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> cnt[i];
		for (int j = 1; j <= cnt[i]; j++) cin >> s[i][j];
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= cnt[i]; j++) {
			int len = s[i][j].size();
			for (int k = 0; k <= n; k++) {
				if (k + len > n) continue;
				string tmp = "";
				for (int w = k + 1; w <= k + len; w++) tmp += a[w];
				for (int w = 0; w <= m; w++) {
					if (tmp == s[i][j] && i > w) dp[k + len][i] = min(dp[k + len][i], dp[k][w] + 1);
				}
			}
		}
	}
	int res = 2e9;
	for (int i = 1; i <= m; i++) res = min(res, dp[n][i]);
	if (res == 2e9) puts("-1");
	else cout << res << endl;
}
```

---

## 作者：Ivan422 (赞：1)

# AT_abc344_d

题目大意：有 $n$ 次选择，每次 $a_i$ 个可以选择的字符串，选一个字符串的代价是 $1$，问组成字符串 $T$ 需要的最小代价。

思路：可以把这题看做一个背包动态规划，我们可以将状态设计为第 $i$ 次选择中，拼接到 $T_j$ 时的最小代价。

动态规划初始化：求最小值自然是全部赋值为极大值，而第 $0$ 时刻没有拼接时，代价为 $0$，即 $f_{0,0}=0$。

动态规划状态转移：先处理什么也不拿的情况，每个长度都能为上一次选择时的答案，即 $f_{i,j}=f_{i-1,j}$。而在每次选择时在 $T$ 里找 $s_{i,j}$，下标记为 $pos$，$s_{i,j}$ 长度记为 $sz$。自然可以由上一时刻拼接到 $pos$ 时转移过来，即 $f_{i,pos+sz}$ 是由 $f_{i-1,pos}$ 转移而来。

最后，根据上述的动态规划，可以写出如下代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=205;
int f[N][N],n,a[N],pos; // 前i次拼接处长度为j最小代价
string t,s;
signed main(){
	memset(f,0x3f,sizeof(f));
	cin>>t>>n;
	f[0][0]=0; // dp 初始化
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=0;j<=200;j++)f[i][j]=f[i-1][j]; // 不拼接的情况
		for(int j=1;j<=a[i];j++){
			cin>>s;
			pos=0;
			while(t.find(s,pos)!=t.npos){ // 查找可拼接位置
				pos=t.find(s,pos);
				if(pos==t.npos)break; // 查找失败
				f[i][pos+s.size()]=min(f[i][pos+s.size()],f[i-1][pos]+1); // 状态转移
				pos++; // 接着查询
			}
		}
	}
	if(f[n][t.size()]>n)cout<<-1; // 无解
	else cout<<f[n][t.size()]; // 答案
	return 0;
}
```

---

## 作者：Floating_Trees (赞：0)

upd: 24.3.11，感谢 @[compaq](37275) 指出错误。

### 题意
有 $n$ 个袋子，每个袋子里有 $a_i$ 个字符串，你刚开始有一个空字符串，有 $n$ 次操作，第 $i$ 次操作可以从第 $i$ 个袋子里不拿或只拿一个字符串。现在给你一个字符串 $t$，问最少要从袋子里拿多少个字符串，才能使得最终的字符串变成 $t$，若不能输出 $-1$。
### 思路
DP。令 $dp_{i,j}$ 表示已经已经用了 $i$ 个口袋，达成 $t $ 的前 $j$ 个字符最小花费。那么就可以从 $dp_{i-1,j-|s|}$ 转移到 $dp_{i,j}$。时间复杂度 $O(nm|t||s|)$

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 110;
char s[N],t[N];
int n,m,dp[110][110];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	
	memset(dp,0x3f3f3f3f,sizeof(dp)); // 初始化最大值 
	dp[0][0] = 0;// 初始化 
	
	cin >> t + 1; int tl = strlen(t + 1);
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 0;j <= tl;j++)
			dp[i][j] = dp[i-1][j]; // 如果不从当前口袋选 
		cin >> m;
		while (m--)
		{
			cin >> s + 1; int sl = strlen(s + 1);
			for (int j = sl;j <= tl;j++)
			{
				bool f = true;
				int c = 1;
				for (int k = j - sl + 1;k <= j;k++)
					if (t[k] != s[c++])
						f = false;
				// 判断当前这个字符串是不是t的其中一段 
				if (f)
					dp[i][j] = min(dp[i][j],dp[i-1][j-sl] + 1); // 转移 
			}
		}
	}
	
	int ans = 0x3f3f3f3f;
	for (int i = 0;i <= n;i++)
		ans = min(ans,dp[i][tl]); // 求答案 
	cout << (ans == 0x3f3f3f3f ? -1 : ans) << "\n";
	
	
	return 0;
}
```

---

## 作者：Addicted_Game (赞：0)

# [传送门](https://www.luogu.com.cn/problem/AT_abc344_d)

###  题目大意
给定目标字符串与 $n$ 组字符串，要在这些字符串中依次每组选择一个或不选，求最少选几个可以组成目标字符串。

### 思路
看到这道题的第一反应一定是搜索，但是会超时。既然搜索不行，那就想 **dp**。

很明显是一道分组背包，在每组都只能最多选一个。那么需要判断的就是可不可以选这个字符串。而可以选择的就是在目标串某个位置的往后的 $size_{i,j}$ 位是否与 $s_{i,j}$ 相同即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string t;
int n;
int num[105];
string s[105][105];
int dp[105];
int main(){
	cin>>t;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&num[i]);
		for(int j=1;j<=num[i];j++){
			cin>>s[i][j];
		}
	}
	memset(dp,0x3f,sizeof dp);
	dp[0]=0;
	int len=t.size();
	for(int i=1;i<=n;i++){	
		for(int j=len;j>=1;j--){
			for(int k=1;k<=num[i];k++){
				int si=s[i][k].size();
				if(j-si>=0&&t.substr(j-si,si)==s[i][k]){//判断加上后的末尾这一段是否匹配 
					dp[j]=min(dp[j],dp[j-si]+1);
				}
			}//注意j和k不能换位置 
		}
	}
	if(dp[len]<=5e8) printf("%d",dp[len]);//因为转移中会减少，所以要放松一点 
	else printf("-1");
	return 0;
}
```

---

## 作者：_AyachiNene (赞：0)

# 思路：
设 $dp_{i,j,k}$ 表示匹配到了 $T$ 的第 $i$ 位，当前选到第 $j$ 组，花的钱是 $k$ 的可能性。转移很好转移，如果当前选到字符串是当前选出 $T$ 的前缀的后缀，那么就可以直接从 $dp_{i-siz_{s},j-1,k-1}$ 转移过来，或不选它，从 $dp_{i,j-1,k}$ 转移过来。赛时唐了，状态设计是有冗余的，可以不用设花的钱的数量，直接求就行了。
# Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
	if(x<0){x=-x;putchar('-');}
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int len[1145][1145];
int dp[105][105][105];
string t;
int n,a[114514];
string s[1145][1145];
int check(string str,int pos)
{
	for(int i=1;i<str.size();i++)
		if(str[i]!=t[pos+i])
			return 0;
	return 1;
}
int main()
{
	cin>>t;
	t=' '+t;
	len[0][0]=t.size()-1;
	n=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		for(int j=1;j<=a[i];j++)
			cin>>s[i][j],len[i][j]=s[i][j].size(),s[i][j]=' '+s[i][j];
	}
	for(int i=0;i<=n;i++)
		dp[0][i][0]=1;
	for(int i=1;i<=len[0][0];i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=a[j];k++)	
				for(int w=1;w<=n;w++)
				{
					dp[i][j][w]|=dp[i][j-1][w];
					if(i>=len[j][k]&&check(s[j][k],i-len[j][k]))
						dp[i][j][w]|=dp[i-len[j][k]][j-1][w-1];
				}
	for(int i=1;i<=100;i++)
		for(int j=1;j<=n;j++)
			if(dp[len[0][0]][j][i]) 
			{
				write(i);
				return 0;
			}
	puts("-1");
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑动态规划算法，定义 $dp_{i,j}$ 表示用前 $i$ 个袋子拼出 $T$ 的前 $j$ 个字符的最小价钱，则状态转移方程为：

$$dp_{i,j} = \max_{k=1}^{a_i} [S_{i,k} = T(j-l_{i,k}+1,j)] dp_{i-1,j-l_{i,k}}+1$$

其中 $T(l,r)$ 表示字符串 $T$ 中 $[l,r]$ 范围内的字符组成的字符串。

时间复杂度为 $O(NM^3)$。

**代码写法和上述解法略微不同，采用的是用 $dp_{i-1,j}$ 对 $dp_{i,j+l_{i,k}}$ 的更新。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=105,M=15,INF=1e9;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,ans=INF;
ll a[N];
ll L[N][M];
string T;
string S[N][M];
ll dp[N][N]; // 表示前 i 个地方拼完 1~j 的最小数量 
int main(){
	cin>>T;
	m=T.size();
	T=" "+T;
	n=read();
	for(int i=0;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    dp[i][j]=INF;
	for(int i=1;i<=n;i++){
		a[i]=read();
		for(int j=1;j<=a[i];j++){
			cin>>S[i][j];
			L[i][j]=S[i][j].size();
			S[i][j]=" "+S[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			if(dp[i-1][j]==INF)
			  continue;
			ll l=j+1;
			for(int k=1;k<=a[i];k++){
				bool f=1;
				ll r=j+L[i][k];
				for(int t=l;t<=r;t++){
				    if(T[t]!=S[i][k][t-l+1]){
				    	f=0;
				    	break;
					}
				}
				if(f)
				  dp[i][r]=min(dp[i][r],dp[i-1][j]+1);
			}
		}
		for(int j=1;j<=m;j++)
		  dp[i][j]=min(dp[i][j],dp[i-1][j]);
		ans=min(ans,dp[i][m]);
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=m;j++){
//			write(dp[i][j]==INF?-1:dp[i][j]);
//			putchar(' ');
//		}
//		putchar('\n');
//	}
	write(ans==INF?-1:ans);
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

### 一些鲜花
考场上因为把 dfs 复杂度错认为是 $10000 \times 10000$ 的，~~于是吃完两发罚时才想起不对这是 dp。~~

### sol
简单 dp。

设 $dp_{i,j}$ 表示前 $i$ 个 $A_i$ 中全对前 $j$ 个的最小代价，于是口胡出状态转移方程。

$dp_{i,j} = \min\{dp_{i-1,j},dp_{i-1,j-S_{i}}+1(S_i==T_{(j-S_i) \sim j})\}$

于是枚举一堆东西转移就完了。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,f[101][10001],jl,ans1,cnt,ans=INT_MAX,val,x,y,q;
int b[201],c[201],k;
string s,a[101][11],wssb;
map<int,int>mp;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>s;
	int len=s.size();
	s=s;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		for(int j=1;j<=b[i];j++){
			cin>>a[i][j];
		}
	}
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=len;j++){
			f[i][j]=f[i-1][j];
			for(int k=1;k<=b[i];k++){
				if(a[i][k].size()<=j){
					bool ff=0;
					for(int l=j-a[i][k].size();l<j;l++){
						if(s[l]!=a[i][k][l-j+a[i][k].size()]){ff=1;break;}
					}
					if(!ff) f[i][j]=min(f[i][j],f[i-1][j-a[i][k].size()]+1); 
				}
			}
		}
	}
	if(f[n][len]==0x3f3f3f3f3f3f3f3f)cout<<-1<<endl;
	else cout<<f[n][len]<<endl;
	return 0;
}
//life is hard , dp is fun
```

---

## 作者：Albatross_LC (赞：0)

### 思路：

考虑 DP。

设 $dp_{i, j} = $ 所需的最少金钱。其中 $i$ 指已处理的背包数量，$j$ 指匹配的 $T$ 前缀长度。

考虑将字符串 $X$ 在第 $(i + 1)$ 个背包中添加到 $S$ 的末尾。那么，从 $dp_{i,|S|}$ 到 $dp_{i + 1, |S| + |X|}$ 的转换只有在 $(|S| + 1)$ 到 $(|S| + |X|)$ 的字符与 $X$ 匹配时才可能发生。

在这个问题的约束下，我们可以直接检查这个条件。

同时，不选择一个字符串对应于从 $dp_{i, j}$ 到 $dp_{i + 1, j}$ 的转换。

通过实现这个 DP，问题可以在大约 $O(NM|S||T|)$ 时间内解决（其中 $M$ 是背包中字符串的数量）。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[105][105];
int main(){
  for(int i=0;i<105;i++)
    for(int j=0;j<105;j++)
      dp[i][j]=1e9;
  dp[0][0]=0;
  string t;
  cin >> t;
  int tl=t.size();
  int n;
  cin >> n;
  for(int i=0;i<n;i++){
    for(int j=0;j<105;j++){dp[i+1][j]=dp[i][j];}
    int m;
    cin >> m;
    while(m>0){
      m--;
      string s;
      cin >> s;
      int sl=s.size();
      for(int j=0;j+sl<=tl;j++){
        bool ok=true;
        for(int k=0;k<sl;k++){
          if(t[j+k]!=s[k]){ok=false;break;}
        }
        if(ok)dp[i+1][j+sl]=min(dp[i+1][j+sl],dp[i][j]+1);
      }
    }
  }
  if(dp[n][tl]>5e8)dp[n][tl]=-1;
  cout << dp[n][tl] << "\n";
}
```

---

## 作者：LittleDrinks (赞：0)

## [\[ABC344D\] String Bag](https://www.luogu.com.cn/problem/AT_abc344_d)

记 $S[i:j]$ 表示字符串 $S$ 第 $i$ 到第 $j$ 位构成的子串。

设 $c_x$ 表示连接 $S[1:x]$ 所需的最小花费，不能连接时记为 $-1$。如果此时袋中的字符串 $s_{i,j}$ 与 $S[x:y]$ 重合，并且 $S[1:x-1]$ 能够找到一种方式完成连接（即 $c_{x-1}\neq -1$），那么 $c_y\leftarrow \min\{c_y,c_{x-1}+1\}$。

注意每个口袋中只能选出一个字符串，因此考虑袋中的字符串时，都需要在上一轮的 $c$ 的基础上操作，将更新的数值存入 $tc$ 数组，并在这一轮结束时统一更新。（忘记这个会 `WA` 一个点）

[AC 代码提交记录](https://www.luogu.com.cn/record/150183473)

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXT=105, MAXN=105, MAXA=15;
string t, s[MAXN][MAXA];
int len, n, a[MAXN], c[MAXT], tc[MAXT];

int main()
{
//	freopen("3.in", "r", stdin);
	cin >> t;
	len = t.length();
	t = " " + t;
	
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		for (int j = 1; j <= a[i]; ++j) {
			cin >> s[i][j];
		}
	}
	
	c[0] = 0;
	for (int i = 1; i <= len; ++i) { c[i] = -1; }
	for (int i = 1; i <= n; ++i) {
		
		for (int x = 1; x <= len; ++x) { tc[x] = c[x]; }

		for (int j = 1; j <= a[i]; ++j) {
			int sl = s[i][j].length();
			for (int k = 1; k+sl-1 <= len; ++k) {

				if (t.substr(k, s[i][j].length()) == s[i][j]) {
					if (c[k-1] != -1) {
						if (tc[k+sl-1] == -1) {
							tc[k+sl-1] = c[k-1] + 1;
						} else {
							tc[k+sl-1] = min(tc[k+sl-1], c[k-1]+1);
						}
					}
				}
				
			}
		}
		
		for (int x = 1; x <= len; ++x) { c[x] = tc[x]; }
	}
	
	cout << c[len] << endl;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc344_d)

## 思路

不会用 dp，怎么办呢？看到最少步数当然可以想到搜索啦。

很明显，如果不进行剪枝，时间复杂度为 $\mathcal{O}(n!)$ 左右。所以我们进行几个剪枝：

1. 如果当前字符串长度已经大于目标串长度了，那么肯定匹配不到答案，直接弹出；

2. 如果当前字符串不是目标串的一部分，那么肯定匹配不到答案，直接弹出，可以用 STL 中的 ``substr()`` 函数快捷匹配；

3. 如果之前在当前位置找到过这个串，并且所用步数比当前步数小，直接弹出。这里可以用 map 记录。

经过这一番玄学剪枝，我们成功 AC 了这道题。
- 可选优化：手写一个 pair 类型的 unordered_map。

## AC 代码

广度优先搜索 bfs：

```cpp
#include<bits/stdc++.h>
#define rep(k,l,r) for(register int (k)=(l);k<=(r);++k)
using namespace std;
inline ll read(){//快读优化。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
struct pair_hash{//手写 pair 比较函数。
    template<class T1,class T2>
    size_t operator()(const pair<T1,T2>&pair)const{
        return hash<T1>()(pair.first)^hash<T2>()(pair.second);
    }
};unordered_map<pair<string,int>,int,pair_hash>vis;
const int N=110;
int n,a[N],len;
string t,s[N][N];
struct node{
	int step,x;//当前步数 当前位置。
	string str;//当前匹配到的字符串。
};queue<node>q;
int main(){
	cin>>t>>n;
	len=t.size();
	rep(i,1,n){
		a[i]=read();
		rep(j,1,a[i])cin>>s[i][j];
	}
	q.push({0,0,""});
	while(q.size()){
		node now=q.front();
		q.pop();
		if(now.str==t){//匹配到了即为最少步数，直接输出后结束程序。
			cout<<now.step;
			return 0;
		}
		rep(i,now.x+1,n){
			rep(j,1,a[i]){
				string str=now.str+s[i][j];
				int nowl=str.size();
				if(nowl>len||t.substr(0,nowl)!=str)continue;//剪枝 1. 和剪枝 2.
				if(vis[{str,i}]&&vis[{str,i}]<=now.step+1)continue;//剪枝 3.
				vis[{str,i}]=now.step+1;
				q.push({now.step+1,i,str});
			}
		}
	}
	cout<<-1;//找不到输出 -1。
	return 0;
}
```

---

深度优先搜索 dfs：

```cpp
#include<bits/stdc++.h>
#define rep(k,l,r) for(register int (k)=(l);k<=(r);++k)
using namespace std;
inline ll read(){//快读优化。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
const int N=110;
int n,a[N],ans=1e9,len,cnt,ma[N],p[N];
string en,s[N][N];
struct pair_hash{//手写 pair 比较函数。
    template<class T1,class T2>
    size_t operator()(const pair<T1,T2>&pair)const{
        return hash<T1>()(pair.first)^hash<T2>()(pair.second);
    }
};unordered_map<pair<string,int>,int,pair_hash>vis;
void dfs(int now,string str,int dep){
	int nowl=str.size();
    /*
    剪枝解析：
    1. 当前长度比目标串长；
    2. 当前步骤比最短步骤多；
    3. 后面的长度过短，无论如何都不能拼成目标串长度；
    4. 当前部分和目标串前面不一样；
    5. 已经搜索过当前串且用的步骤比现在短。
    */
	if(nowl>len||dep>=ans||nowl+p[now]<len||en.substr(0,nowl)!=str||vis[{str,now}]&&vis[{str,now}]<=dep)return ;
	vis[{str,now}]=dep;
	if(now==n+1){
		if(str==en)ans=min(ans,dep);//拼成目标串，取最小值。
		return ;
	}
	rep(i,1,a[now])dfs(now+1,str+s[now][i],dep+1);
	dfs(now+1,str,dep);
	return ;
}
int main(){
	cin>>en>>n;
	len=en.size();
	rep(i,1,n){
		a[i]=read();
		rep(j,1,a[i]){
			cin>>s[i][j];
			ma[i]=max(ma[i],(int)s[i][j].size());
		}
	}
	for(int i=n;i>=1;--i)p[i]=p[i+1]+ma[i];//记录后缀剪枝。
	dfs(1,"",0);
	if(ans==1e9)ans=-1;//拼不成输出 -1。
	cout<<ans;
	return 0;
}
```

[广搜 AC 记录](https://atcoder.jp/contests/abc344/submissions/51110567)

[深搜 AC 记录](https://atcoder.jp/contests/abc344/submissions/51110937)

---

## 作者：CQ_Bob (赞：0)

## 分析

这把开挂了。

考虑 DP。定义状态函数 $f_{i,j}$ 表示在前 $i$ 个序列中选若干个拼起来，使得 $T$ 的前 $j$ 个字符已经拼好的最小代价。

然后去枚举当前序列中的所有字符串，暴力看是否能够拼起来即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=105;
char t[N];
int n,a[N];
char s[N][N][N];
int len[N][N];
int f[N][N];

il bool check(int S,int I,int J){
	for(re int i=S,j=1;j<=len[I][J];++i,++j)
		if(t[i]!=s[I][J][j]) return 0;
	return 1;
}
il void solve(){
	scanf("%s",t+1);
	int m=strlen(t+1);
	n=rd;
	for(re int i=1;i<=n;++i){
		a[i]=rd;
		for(re int j=1;j<=a[i];++j){
			scanf("%s",s[i][j]+1);
			len[i][j]=strlen(s[i][j]+1);
		}
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(re int i=1;i<=n;++i)
		for(re int j=0;j<=m;++j){
			f[i][j]=f[i-1][j];
			for(re int k=1;k<=a[i];++k)
				if(j-len[i][k]+1>=1&&check(j-len[i][k]+1,i,k))
					f[i][j]=min(f[i][j],f[i-1][j-len[i][k]]+1);	
		}
	if(f[n][m]>n+100) cout<<"-1";
	else cout<<f[n][m];
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}

```

---

