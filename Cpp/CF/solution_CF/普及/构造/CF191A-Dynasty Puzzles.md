# Dynasty Puzzles

## 题目描述

The ancient Berlanders believed that the longer the name, the more important its bearer is. Thus, Berland kings were famous for their long names. But long names are somewhat inconvenient, so the Berlanders started to abbreviate the names of their kings. They called every king by the first letters of its name. Thus, the king, whose name was Victorious Vasily Pupkin, was always called by the berlanders VVP.

In Berland over its long history many dynasties of kings replaced each other, but they were all united by common traditions. Thus, according to one Berland traditions, to maintain stability in the country, the first name of the heir should be the same as the last name his predecessor (hence, the first letter of the abbreviated name of the heir coincides with the last letter of the abbreviated name of the predecessor). Berlanders appreciate stability, so this tradition has never been broken. Also Berlanders like perfection, so another tradition requires that the first name of the first king in the dynasty coincides with the last name of the last king in this dynasty (hence, the first letter of the abbreviated name of the first king coincides with the last letter of the abbreviated name of the last king). This tradition, of course, has also been always observed.

The name of a dynasty is formed by very simple rules: we take all the short names of the kings in the order in which they ruled, and write them in one line. Thus, a dynasty of kings "ab" and "ba" is called "abba", and the dynasty, which had only the king "abca", is called "abca".

Vasya, a historian, has recently found a list of abbreviated names of all Berland kings and their relatives. Help Vasya to find the maximally long name of the dynasty that could have existed in Berland.

Note that in his list all the names are ordered by the time, that is, if name $ A $ is earlier in the list than $ B $ , then if $ A $ and $ B $ were kings, then king $ A $ ruled before king $ B $ .

## 说明/提示

In the first sample two dynasties can exist: the one called "abcca" (with the first and second kings) and the one called "abccba" (with the first and third kings).

In the second sample there aren't acceptable dynasties.

The only dynasty in the third sample consists of one king, his name is "c".

## 样例 #1

### 输入

```
3
abc
ca
cba
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
vvp
vvp
dam
vvp
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
ab
c
def
```

### 输出

```
1
```

# 题解

## 作者：珅肐 (赞：14)

题目描述不是很清楚

大意是：给你$n$个字符串，将这些字符串拼接，求一个最长的序列，使这个其中每个串的最后一个字母与第一个字母相同（最后一个串的最后一个字母与第一个串的第一个字母相同），而且后面的串只能接在前面的串的后边。

举个例子：$auj$ $jhg$ $ $ $gfert$ $tyuhj$ $jbgva$

考虑$dp$:

我们用$f[l][r]$表示从字母$l$到字母$r$所能走过的最长长度。

对于一个字符串$s$来讲，至少有：

$$f[s[0]][s[len-1]]=len$$

状态转移方程为：

$$dp[i][r]=max(dp[i][r],dp[i][l]+len) ,i={'a','b',…'z'}$$

代码就好写了

但是要注意：

递推时一定要保证，转移前的状态是合法的

我们如果只有两个串$ab$和$de$，并不能有$f[a][e]=f[a][b]+f[b][d]+f[d][e]$

因为这时$f[b][d]$虽然是$0$但是并没有此状态的存在，写的时候要么特判，要么赋极小值。

#### 代码奉上：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<cstring>
using namespace std;
inline int read(){//这个题没什么用的快读
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
char c[10];
int f[27][27];
int main(){
	int n=read(),ans=0;
	for(int i=1;i<=n;++i){
		scanf("%s",c);//开一个数组就够了，为保证后面的串接在前面，边读边做
		int len=strlen(c),l=c[0]-'a',r=c[len-1]-'a';//如上所述
		for(int j=0;j<26;++j)
			if(f[j][l])f[j][r]=max(f[j][r],f[j][l]+len);
		f[l][r]=max(f[l][r],len);
	}
	for(int i=0;i<26;++i)ans=max(f[i][i],ans);//统计答案
	printf("%d\n",ans);//输出
	return 0;//好习惯
}

```


---

## 作者：きりと (赞：6)

## 题目大意

选出一些字符串拼接，若首位字符相同即为合法，求最长合法字符串。

## 解题思路

一看数据范围有 $5e5$ ，显然得跑 $dp$ 了，状态设计方面，较大的 $n$ 的范围使得我们的选择并不多。很容易可以想到：因为答案只与两头的字符有关系，所以我们不妨设 $f[i][j]$ 为左端字符编码为 $i$ ，右端为 $j$ 的拼接后字符串的最大长度。

接下来考虑转移：

对于每一个子字符串 $s$ ，显然至少会有 $f[s[1]][s[s.size()]]≥s.size()$

然后如果此时有一个字符，编码为 $j$  ，且已知有一段开头为此字符，结尾为 $s[1]$ 的拼接字符串，则 $f[j][s[s.size()]]$ 可更新为 $f[j][s[1]]+s.size()$ 。

答案就是 $max(f[1][1],f[2][2],...,f[26][26])$ 辣！

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[27][27];
signed main()
{
    int n;
    string s;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        int l=s.size();
        int x=s[0]-'a'+1,y=s[l-1]-'a'+1;
        for(int j=1;j<=26;j++)
        {
            if(f[j][x]>0)
            {
                f[j][y]=max(f[j][y],f[j][x]+l);
            }
        }
        f[x][y]=max(f[x][y],l);
    }
    int maxn=0;
    for(int i=1;i<=26;i++)
    {
        maxn=max(maxn,f[i][i]);
    }
    cout<<maxn<<endl;
    return 0;
}
```



---

## 作者：complete_binary_tree (赞：3)

[原题传送门](https://www.luogu.com.cn/problem/CF191A)

我发现一些 dalao 们没有详细的讲 dp，所以我在此展示蒟蒻的思路：

# 题目大意

给定 $n$ 个字符串，要求**按给出的顺序拼接**，并且前一个单词的尾部和后一个单词的头部相同。

例如：

```
aaa
abg
aca
```

其中，```aaa-abg``` 是合法的拼接，而 ```aaa-aca-abg``` 不是合法的拼接（没有按照给定的顺序）。

现在，我们要求满足头尾相等的最长合法序列。

如上，最长的拼接应该是 ```aaa-aca```，长度为 $6$。

# 题目做法

考虑线性 dp。

我们可以用三维的 $dp_{i,j,k}$，表示用前 $i$ 个字符串可以拼接成头为 $j$，尾为 $k$ 的最长字符串。

那么容易发现：（设 $start$ 为第 $i$ 个字符串的首字母，$last$ 为第 $i$ 个字符串的尾字母，$l$ 为第 $i$ 个字符串的长度）

- $dp_{i,j,last}=\max(dp_{i-1,j,last},dp_{i-1,j,start}+l)(\text{'a'} \le j \le \text{'z'})$（要么不选，要么选）
- $dp_{i,start,last}=\max(dp_{i-1,start,last},l)$（要么继承上一个，要么单独成新字符串）
- $dp_{i,j,k}=dp_{i-1,j,k}(k \ne last)$（其它情况，直接转移

最后取 $dp_{n,i,i}(1 \le i \le n)$ 最大值即可。

如果这时，你高高兴兴地打代码，上交，会发现它 $\text{MLE}$ 了。为什么呢？

## 优化空间复杂度

我们发现，这种做法的 $dp$ 至少要开 $5\times10^5\times26\times26$ 的数组，即大约 $1.26\text{GB}$。

显然，我们要压缩至少一维，把它从 $\text{MLE}$ 的深渊中解救。

然后，我们看到刚刚的 dp 方程式，发现每一个第 $i$ 层的 dp 都是由第 $i-1$ 层的 dp 转移过来的。

所以，我们可以把 $dp$ 的 $i$ 维给压掉，直接从原有的 $dp_{i,j,k}$ 转移过来。

这样，我们就解决了 $\text{MLE}$ 的问题。

（详细内容与注意事项见代码注释）

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n, maxn;
string s;

int f[127][127]; //把字母与 26 个数字对应较为麻烦，索性开 127，正好可以容下 char 的范围，更方便。

int main(){
	scanf("%d", &n);

	for(int i = 1; i <= n; ++i){
		cin >> s;
		for(char start = 'a'; start <= 'z'; ++start)//在线处理，枚举所有可能的开头
		    if(f[start][s[0]]) //必须有串与 s 拼接才能更新，否则会导致拼接后开头与 start 不一致
				f[start][s[s.length() - 1]] = max(f[start][s[s.length() - 1]], int(f[start][s[0]] + s.length())); //第一个 dp 式子

		f[s[0]][s[s.length() - 1]] = max(f[s[0]][s[s.length() - 1]], (int)s.length()); //第二个 dp 式子，由于前面我们 有串与 s 拼接才能更新 的特判，所以这行是不能省略的。
        //第三个 dp 式子由于压维直接保留，不用更新。
	}

	for(int i = 'a'; i <= 'z'; ++i)
		maxn = max(maxn, f[i][i]); //统计首尾相同的最长字符串

	printf("%d", maxn);

	return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/136916392) $\text{(1.75s/72KB)}$

蒟蒻写题解不易，喜欢就点个赞吧~

---

## 作者：lalaji2010 (赞：2)

# CF191A

## 分析

注意题目中 $3$ 个性质。

1. 字符串**顺序给出**，后给出的字符串只能拼在先给出的字符串后面。
2. 拼接时后一个字符串的首字母与前一个字符串的尾字母相同。
3. 最后拼接好的字符串的首尾字母相同。

举个例子，给定八个字符串 `llj jc zm cpp phy yhb bct bl`，最后应该拼成 `llj jc cpp phy yhb bl`，`zm` 和 `bct` 不能要了。

### 设置状态

注意到性质一其实是规定了拼接的无后效性，考虑 dp。

性质二和性质三告诉我们这道题的状态只与首尾字母有关，并且这道题求的是最长拼接长度，再结合本题只有 $26$ 个字母，顺理成章地设出状态 $dp[i][j]$ 表示以字母 $i$ 开头以字母 $j$ 结尾的最长拼接长度。显然，初始值都为 $0$。

考虑该如何进行状态转移。

### 状态转移

由性质一可得，一定是在顺序遍历的过程中进行转移。

不妨令当前遍历到字符串 $s$，其首字母为 $head$，尾字母为 $tail$，长度为 $len$。

$s$ 可以与一个以任意字母 $k$ 开头，以 $head$ 结尾的字符串进行拼接，状态转移为 $dp[k][tail]=\max(dp[k][tail],dp[k][h]+len)$。当然，在前面拼接成过以 $k$ 开头以 $head$ 结尾的字符串才行。

同时，$s$ 本身就可以是一种以 $head$ 开头，以 $tail$ 结尾的字符串的方案，所以也有 $dp[head][tail]=\max(dp[head][tail],len)$。

当然，其实在输入的时候就可以完成状态转移。并且为了节省空间，我们将小写字母从小到大依次重新编码成 $0$ 到 $25$ 的整数。

### 统计答案

题目要求首尾字母相同，那么只要计算 $0 \leq i \leq 25$ 时 $dp[i][i]$ 的最大值就好啦。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
long long dp[35][35];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		int len=s.size();
		int h=s[0]-'a',t=s[len-1]-'a';
		for(int j=0;j<26;j++){
			if(!dp[j][h]) continue;
			dp[j][t]=max(dp[j][t],dp[j][h]+(long long)(len));	
		}
		dp[h][t]=max(dp[h][t],(long long)(len));
	}
	long long res=0;
	for(int i=0;i<26;i++){
		res=max(res,dp[i][i]);
	}
	cout<<res<<"\n";
	return 0;
}
```

---

## 作者：luogu_gza (赞：2)

其实可以发现，整一个转移只和三个要素有关：首字母，末尾字母，长度。

我们记录这三个要素为 $l_i,r_i,len_i$。

我们定义 $f_{i,j}$ 表示从 $i$ 开始，到 $j$ 结束的最大长度。

明显的，每一次更新就是 $f_{j,r_i}=\max(f_{j,r_i},f_{j,l_i}+len_i))$。

时间复杂度：$\mathcal O(n)$。

[code](https://codeforces.com/contest/191/submission/215309829)

---

## 作者：baiABC (赞：2)

对每一个输入的字符串，可以给开头和末尾的字符间连一条边，权值为字符串长度。

求一个有向图最长的环的长度（经过的边不重复）应该是 NPC 的。

但是题目中有这样一句话：
> Note that in his list all the names are ordered by the time, that is, if name $A$ is earlier in the list than $B$, then if $A$ and $B$ were kings, then king $A$ ruled before king $B$.

这样满足了 DP 的无后效性，就可以直接考虑 DP 了：

设 $d(cl, cr)$ 表示从开头为字符 $cl$，末尾为 $cr$ 的能拼接成的最长字符串长度（暂不考虑第一个字母和最后一个字母相同的条件），则对于每个输入的字符串，可以实时更新以该单词为结尾的答案。

状态转移方程见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int d[26][26], n;
int main()
{
   ios::sync_with_stdio(0);
   cin >> n;
   for(int i = 0; i < n; ++i)
   {
      string s; cin >> s;
      int j = s[0]-'a', k = s.back()-'a';
      for(int l = 0; l < 26; ++l)
         if(d[l][j]) // d[i][j] != 0 表示状态合法
            d[l][k] = max(d[l][k], d[l][j]+(int)s.size());
      d[j][k] = max(d[j][k], (int)s.size());
   }
   int ans = 0;
   for(int i = 0; i < 26; ++i) ans = max(ans, d[i][i]);
   cout << ans << '\n';
   return 0;
}
```

---

## 作者：naroto2022 (赞：1)

# CF191A 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF191A)

### 题意

给定 $n$ 个字符串，将其中一些字符串取出来并拼接在一起，满足拼接的前面一个字符串的结尾与拼接的后面一个字符串的开头相同，且拼接成的字符串的收尾相同。

例子：$\text{asc cdlaks sloa}$。

（无特殊意义，随便举的例子。）

### 思路

一看到这题就想到了 DP。

于是，设了一个二维数组 $f$，$f_{l,r}$ 表示字母 $l$ 到字母 $r$ 的最大长度。（就是以字符 $l$ 开头，字符 $r$ 结尾的字符串的最大长度）其中，字母均用数字表示。

所以对于一个字符数组 $s$，$len$ 为它的长度，有：

$f[s[1]][s[len-1]]=len$。

接下来要考虑转移的式子：

对于一个字符串（从 $1$ 开始输入），设 $l=s[1]-97+1,r=s[len]-97+1$（因为 $a$ 的 ASCLL 码为 $97$），枚举所有可能的开头 $i(i\in[1,26])$，有两种情况：

1. 不将这个字符串接入：则 $f[i][r]=f[i][r]$；
2. 将这个字符串接入：则 $f[i][r]=f[i][l]+len$。

两者取最大值即可，所以有：

$f[i][r]=\max(f[i][r],f[i][l]+len)$。

枚举完以后，咱们还要在权衡利弊一下，如果 $f[l][r]<len$，那还不如直接就只要这个字符串，所以枚举完后还要有：

$f[l][r]=\max(f[l][r],len)$。

于是，这题就可以 AC 啦。

### 总结

1. 用数字表示字母。
2. 线性 DP。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
long long n,f[35][35],ans,len,l,r;
//f[l][r] 表示字母 l 到字母 r 的最大长度 
char s[15];
int main(){
	scanf("%lld",&n);
	for(int i=1; i<=n; i++){
		scanf("%s",s+1);
		len=strlen(s+1);
		l=s[1]-'a'+1,r=s[len]-'a'+1;
		for(int j=1; j<=26; j++)
			if(f[j][l]) 
				f[j][r]=max(f[j][r],f[j][l]+len);
		f[l][r]=max(f[l][r],len);
	} 
	for(int i=1; i<=26; i++) ans=max(ans,f[i][i]);
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：abensyl (赞：1)

原题：[CF191A Dynasty Puzzles](https://www.luogu.com.cn/problem/CF191A)。

这是一道动态规划的好题。

## 思路

我们假设 $f$ 数组为 dp 数组。

那么将状态设置为 $f[k][i][j]$ 表示前 $k$ 个单词中，从字符 $i$ 开头，到字符 $j$ 结尾的首尾相接的字符串长度。

假设第 $k$ 个单词以 $l$ 开头，$r$ 结尾，长度为 $len$。

我们循环 $i$ 枚举开头字符并由 $l$ 和 $r$ 进行更新，由于朝代相邻国王之间的更替原则，$f[k][i][r] = \max(f[k-1][i][l]+len, f[k][i][r])$。

最终输出的答案为所有 $f[k][i][i]$ 中的最大值。

观察可发现，可以通过降维将 $k$ 的一维删去，变为二维 dp 数组，节省空间。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int mod = 998244353, N = 500005, INF = 1 << 30;

int f[26][26];
string s[N];

void solve() {
	int n;
	cin>>n;
	for(int i=1;i<=n;++i) cin>>s[i];
	for(int i=1;i<=n;++i) {
		string zc=s[i];
		int st=zc[0]-'a',ed=zc[zc.size()-1]-'a';
		int sz=zc.size();
		for(int j=0;j<26;++j) {
			if(j!=st&&f[j][st]==0) continue;
			f[j][ed]=max(f[j][ed],f[j][st]+sz);
		}
	} int res=0;
	for(int i=0;i<26;++i) res=max(res,f[i][i]);
	cout<<res<<'\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  // cin>>t;
  while (t--) solve();
  return 0;
}
```

我的 [AC 记录](https://codeforces.com/contest/191/submission/203114870)。

---

## 作者：nynkqh_yzp (赞：1)

一眼 DP 设状态为 $f_{i,j,k}$ 表示用了前 $i$ 个名字，首字母为 $j$，尾字母为 $k$ 所能得到的最长的长度。

转移：设第 $i$ 个名字的首字母为 $h_i$，尾字母为 $t_i$，长度为 $l_i$，$f_{i,j,k}=f_{i-1,j,k}$。

如果 $h_i=j$，那么 $f_{i,j,k}=\max(f_{i,j,k},f_{i-1,t_i,k}+l_i)$。

如果 $t_i=k$，那么 $f_{i,j,k}=\max(f_{i,j,k},f_{i-1,j,h_i}+l_i)$。

答案为 $\max\{f_{i,j,j}\}$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[2][27][27],l[500001],ans;
char a[500001][11];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",a[i]);
		l[i]=strlen(a[i]);
	}
	for(int x=1;x<27;x++)
		for(int y=1;y<=27;y++)
			f[0][x][y]=-0x3f3f3f3f;
	int an=0;
	for(int i=1;i<=n;i++){
		an=!an;
		for(int x=1;x<27;x++)
			for(int y=1;y<=27;y++){
				f[an][x][y]=f[!an][x][y];
				if(a[i][l[i]-1]-'a'+1==y)
					f[an][x][y]=max(f[an][x][y],f[!an][x][a[i][0]-'a'+1]+l[i]);
				if(a[i][0]-'a'+1==x&&a[i][l[i]-1]-'a'+1==y)
					f[an][x][y]=max(f[an][x][y],l[i]);
			}
	}
	for(int x=1;x<27;x++)
		ans=max(ans,f[n%2][x][x]);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：heyx0201 (赞：0)

# 题意
给出 $n$ 个字符串，要求把一些字符串拼在一起，假设由 $k$ 个字符串组成，则第 $2 \lt i \le k$ 个字符串的首字母要和第 $i - 1$ 个字符串的尾字母相同，又要求第 $1$ 个字符串的首字母和第 $k$ 个字符串的尾字母相同。求 $\max_k$。
# 思路
评蓝有点逆天了。

CF 1500 的动规题我都不会，我还是太菜了。

看到字符串，你想到了什么？

观察到，因为总共只有 $26$ 个字母 `ABC...Z`，而我们的题目其实只跟首尾字母有关系，于是可以想到把状态设计为 $dp_{x, y}$ 表示拼接出的字符串 $S$ 的首尾字母分别为 $x, y$ 时的 $\max_{|S|}$。

好了，状态好了，接下来就是转移方程了。

总共只有 $26$ 个字母，~~这不就乱转移吗~~可以对每个状态枚举上一步的首字母 $c$，如果 $c$ 能和当前首字母 $l$ 组成合法串，那么 $c$ 和当前尾字母 $r$ 也能够组成合法串，也就是 $dp_{i, r} = dp_{i, l} + len, i \in \{$`ABC.....Z`$\}$，$len$ 为当前字符串的长度。

考虑到类似于下面这种数据上述的算法可能会出现问题：
```
5
af
bg
ch
di
ej
正确输出：2
错误输出：0
```
问题出自于有可能无法构成符合题目要求的串，所以对每个给出的 $n$ 个串中的 $l_i, r_i \ (1 \le i \le n)$  的答案都至少为 $len_i$。
# 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll n, dp[30][30];

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		ll len = s.size();
		ll l = s[0] - 'a', r = s[len - 1] - 'a';
		for (int j = 0; j < 26; j++) {
			if (dp[j][l]) {
				dp[j][r] = max(dp[j][r], dp[j][l] + len);
			}
		}
		dp[l][r] = max(dp[l][r], len);
	}
	ll ans = 0;
	for (int i = 0; i < 26; i++) {
		ans = max(ans, dp[i][i]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：A1C3 (赞：0)

# CF191A Dynasty Puzzles

观察本题，容易想到 dp 做法。

设 $f_{i, j}$ 表示以 $i$ 开头，以 $j$ 结尾的最长单词长度，其中 $0 \le i, j < 26$。对于每个读入的字符串 $s$，设其长度为 $l$，开头为 $l$，结尾为 $r$，然后依次遍历 $i (0 \le i < 26)$，若 $f_{i, l} \neq 0$，则说明存在以 $i$ 开头、以 $l$ 结尾的合法拼接，此时说明可以将 $s$ 拼接在后面，更新 $f_{i, r} = \max(f_{i, r}, f_{i, l} + l)$。循环结束后，更新以 $l$ 开头、以 $r$ 结尾的答案为 $f_{l, r} = \max(f_{l, r}, l)$。最后的答案即为 $f_{i, i} (0 \le i < 26)$ 的 $\max$。

## AC Code

```cpp
#include <iostream>
#include <cstring>
using namespace std;
char s[17];
int f[30][30];
int main() {
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", s);
		int len = strlen(s), l = s[0]-'a', r = s[len-1]-'a';
		for (int i = 0; i < 26; ++i)
			if (f[i][l]) f[i][r] = max(f[i][l]+len, f[i][r]);
		f[l][r] = max(f[l][r], len);
	}
	int ans = 0;
	for (int i = 0; i < 26; ++i)
		ans = max(ans, f[i][i]);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：LHLeisus (赞：0)

[cnblogs](https://www.cnblogs.com/LHLeisus/p/18244682)|[洛谷](https://www.luogu.com.cn/problem/CF191A)|[codeforces](http://codeforces.com/problemset/problem/191/A)

首先感受一下 $2s$ 的时限还是很宽裕的，复杂度大概是 $n$ 乘上一个什么东西。

于是 dp 状态肯定也不只有 $n$。大胆设 $f_{i,a,b}$ 表示结尾是第 $i$ 个串，并且首尾两个字符分别是 $a$ 和 $b$ 时的最长长度。

转移枚举 $i$，再枚举 $a$，注意到此时 $b$ 一定为 $s_i$ 的末位字符，不用枚举了。大体的转移方程：

$$
f_{i,a,b}=\max f_{j,a,st_{i}}+ln_i
$$

其中 $st_i$ 是指 $s_i$ 的第一个字符，$ln_i$ 是串长。

显然时空都爆炸了，考虑优化：

转移的时候额外记录一个 $mx_{a,b}$ 表示 $\max\limits_{j<i} f_{j,a,b}$ 可以实现 $\mathcal{O}(1)$ 转移。

但是这样空间还是爆炸的。其实 $f$ 的第一维没有必要记录，每次转移时我们只关心 $mx$ 里的值，而 $mx$ 里的值一定来自 $1\sim i-1$。于是第一维就愉快地滚掉了。


转移的时候有几种情况：

1. $mx_{a,st_i}\neq 0$，意味着接在前面某个串后面，直接转移；
2. $mx_{a,st_i}=0$，也就是当前串是第一个。这有两种情况：
	1. $a=st_i$，$mx_{a,b}=ln_i$；
   2. $a\neq st_i$，什么也不用做。

最后答案就是 $\max\limits_{i=1}^n mx_{st_i,st_i}$。时间复杂度 $\mathcal{O}(26n)$。

```cpp
int n,m,k;
char s[N];
int st[N],ed[N],ln[N];
int f[30][30];
int mx[30][30];
int main()
{
	n=read();
	FOR(i,1,n){
		scanf("%s",s+1);
		ln[i]=strlen(s+1);
		st[i]=s[1]-'a'+1;ed[i]=s[ln[i]]-'a'+1;
	}
	FOR(i,1,n){
		FOR(a,1,26){
			int fst=st[i],lst=ed[i];
			if(mx[a][fst]>0)f[a][lst]=mx[a][fst]+ln[i];
			else f[a][lst]=mx[0][0];
			mx[a][lst]=max(mx[a][lst],f[a][lst]);
			if(a==fst&&mx[a][fst]==0)f[fst][lst]=mx[fst][lst]=max(mx[fst][lst],ln[i]);
		}
	}
	int ans=0;
	FOR(i,1,n) ans=max(mx[st[i]][st[i]],ans);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑设 $f_{i,j,k}$ 表示当前是第 $i$ 个，并且字符串开头是 $j$，结尾是 $k$ 的最长长度。

然后 $f_{i,j,k}=\max \{f_{id,j,k'}\} + sz(s_i)$，其中 $s_i$ 表示第 $i$ 个字符串，$sz()$ 表示字符串长度，$k'$ 是$s_i$ 开头的字母。

然后直接将 $i$ 删掉，改为在 $i$ 之前所有的最大的值是多少。

然后每次枚举转移即可。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
int n;
string s[500010];
int a[30][30];
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
	memset(a, -0x3f, sizeof(a));
 
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> s[i];
 
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 26; ++j) {
			if (a[j][s[i][0] - 'a'] != -0x3f3f3f3f)
				a[j][s[i].back() - 'a'] = max(a[j][s[i].back() - 'a'], a[j][s[i][0] - 'a'] + (int)s[i].size());
		}
		a[s[i][0] - 'a'][s[i].back() - 'a'] = max(a[s[i][0] - 'a'][s[i].back() - 'a'], (int)s[i].size());
	}
 
	int ans = 0;
	for (int i = 0; i < 26; ++i) ans = max(ans, a[i][i]);
 
	printf("%d\n", ans);
 
	return 0;
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

有 $n$ 个字符串 $a_i$，按顺序选择一些字符串拼接成一个字符串 $s$，满足一个字符串的开头与前一个字符串的末尾相等，$s$ 的开头与末尾相等。求最长 $s$ 的长度。

## 思路

考虑 dp。

$dp_{i,j}$ 表示 $s$ 以 $i$ 开头，以 $j$ 结尾时的最大长度。

状态转移方程为 $dp_{i, r} = \max(dp_{i, r}, dp_{i,l} + m), 1 \le i \le 26$，这里 $l$ 指 $a_i$ 的开头，$r$ 指 $a_i$ 的结尾。转移时一定要保证 $dp_{i,r}$ 是合法的。

最终答案就是 $\max\limits_{i=1}^{26} dp_{i,i}$。

## 代码

```cpp
int dp[30][30];

int main() {
	int n = rd(), ans = 0;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s; s = " " + s;
		int m = s.size() - 1, l = s[1] - 96, r = s[m] - 96;
		for(int j = 1; j <= 26; j++) 
			if(dp[j][l]) dp[j][r] = max(dp[j][r], dp[j][l] + m);
		dp[l][r] = max(dp[l][r], m);
	}
	for(int i = 1; i <= 26; i++) ans = max(ans, dp[i][i]);
	cout << ans;
    return 0;
}
```

---

## 作者：Union_Find (赞：0)

# First 题意

这道题题意不是很清楚，是说有 $n$ 个单词，要选出若干个让他们首尾相连，而且最后一个字符必须和第一个一样，求最大字符数。

# Second 暴力 dp

这个需要一点思维。令 $f[i][j]$ 为以第 $i$ 个单词开头，第 $j$ 个单词结尾的最长字符数。转移方程就是 $f[i][j]=f[i][k]+f[k][j](k \in [i+1,j-1])$ 且可以连接。简单粗暴 $O(n^3)$。

# Third 暴力 dp 优化

其实只需要在每次输入完之后，枚举前 $i-1$ 个单词是否可以和第 $i$ 个连接，直接求解，时间复杂度 $O(n^2)$。

# Fourth 正解

我们可以发现，对于一个单词，我们只在乎他的开头和结尾，以及他的长度。那就可以令 $f_[i][j]$ 表示以字母 $i$ 开头，字母 $j$ 结尾的最长字符数。那么转移方程就是 $f[i][r]=f[i][l]+size$，其中 $l,r,size$ 表示该单词的开头和结尾，以及长度。那么我们就可以 $O(n)$ 求解了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, f[131][131], ans, sz, l, r;
char ch[15];
int main(){
	scanf ("%lld", &n);
	while(n--){ 
		scanf ("%s", ch), sz = strlen(ch), l = ch[0] - 'a', r = ch[sz - 1] - 'a';
		for (int i = 0; i <= 25; i++)
			if (f[i][l])
				f[i][r] = max(f[i][r], f[i][l] + sz);
		f[l][r] = max(f[l][r], sz);
	} 	
	for (int i = 0; i <= 25; i++) ans = max(ans, f[i][i]);
	printf ("%lld", ans);
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

首先定义 $dp_{i,j}$ 表示最终拼凑出的字符串，起始和末尾元素分别为 $i,j$ 的答案。

由题目描述得出如下转移（令 $S_{1},S_{len}$ 分别为 $a,b$）：

$$
dp_{a,b} = \max(len)
$$

其次，得出状态转移方程：

$$
dp_{i,b} = \max(dp_{i,a} + len)
$$

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 35,inf = 0x3f3f3f3f;
int n,ans;
int dp[N][N];
string s;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	memset(dp,-inf,sizeof(dp));
	cin >> n;
	for (re int i = 1;i <= n;i++){
		cin >> s;
		int len = s.length();
		s = ' ' + s;
		int a = s[1] - 'a';
		int b = s[len] - 'a';
		for (re int j = 0;j < 26;j++) dp[j][b] = max(dp[j][b],dp[j][a] + len);
		dp[a][b] = max(dp[a][b],len);
	}
	for (re int i = 0;i < 26;i++) ans = max(ans,dp[i][i]);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：dyc2022 (赞：0)

大淼的 dp 题目。

## 0. 链接区

luogu：[Link](https://www.luogu.com.cn/problem/CF191A)

codeforces：[Link](http://codeforces.com/problemset/problem/191/A)

AC 记录，放心食用：[Link](https://www.luogu.com.cn/record/98160926)

## 1. 状态

设 $dp_{i,j}$ 表示以字符 $i$ 开头，且以 $j$ 结尾的字符串的最大长度。

## 2. 状态转移

首先，我们要判断某个字符串 $s$ 可不可以接到任意一个别的字符串 $t$ 后面。需要满足 $s$ 的第一个字符要等于 $t$ 的最后一个字符。而 $t$ 的第一个字符可以通过枚举得到。设 $t$ 以 $c_0$ 开头，以 $c_1$ 结尾；$s$ 以 $c_1$ 开头，以 $c_2$ 结尾，长度为 $len$，**且 $t$ 不是空串**，则：

$$dp_{c_0 , c_2} = \max(dp_{c_0 , c_2},dp_{c_0,c_1} + len)$$

我们还可以让这个字符串什么都不接，独立成串。因此：

$$dp_{c_1,c_2}=\max(dp_{c_1,c_2},len)$$

## 3. 输出结果

由于要求结果串的首字符和末字符相等，因此结果是 $dp_{c,c}$，$c$ 是 `a` 到 `z` 范围间的任一字符。

## 4. AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[130][130];
int n,ans;
string str;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>str;
		int len=str.length();
		for(char i='a';i<='z';i++)
			if(dp[i][str[0]]!=0)dp[i][str[len-1]]=max(dp[i][str[len-1]],dp[i][str[0]]+len);
		dp[str[0]][str[len-1]]=max(len,dp[str[0]][str[len-1]]);
	}
	for(char i='a';i<='z';i++)ans=max(ans,dp[i][i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：erok (赞：0)

## 写在前面
~~博客出bug了，连交几遍不更新，我人都改麻了，过一个吧。~~

这题是在教练出的模拟赛中做的，当时想了一会儿就出了思路。赛后同学在问，我看了几篇题解，总觉得写的不够详细，遂决定自己上手写一篇。

## 题目大意
给你 $ n $ 个字符串，若两个字符串其中一个字符串的第一个字母与另一个字符串的最后一个字母相同，则可以将它们首尾相接成为一个新的字符串。

求第一个字母与最后一个字母的字符串相同的最长字符串长度。

如 $\texttt{abc}$ 与 $\texttt{cbab}$ 可拼接为 $\texttt{abcbab}$，长度为 6。

## 解题思路

数据范围 5e5 考虑 dp。

首先观察样例可以发现：我们对于每个字符串，只关注它的 开头字母 $\texttt{x}$ ，结尾字母 $\texttt{y}$，与它的长度 $ len $。其中 $\texttt{x,y}$ 影响两个字符串是否能够拼接，而 $ len $ 则是我们要求的答案，那么状态的定义显而易见。

**用 $ dp_{i,j} $ 表示以字母 $ i $ 开头 ，$ j $ 结尾的字符串的最大长度。**

那么状态已经推出，我们看看如何转移。

再回头看看之前的例子： $\texttt{abc}$ 与 $\texttt{cbab}$ 。它们拼接成为一个以 $\texttt{a}$ 开头，$\texttt{b}$ 结尾的字符串 $\texttt{abcbab}$，长度为 $6$。 则对于 $ dp_{a,b} $ 此处由 $dp_{a,c}$ 与 $ dp_{c,b} $ 转移得来。很容易推广：

**对于 $ dp_{i,j} $ ，它由 $ \sum_{k=1}^{26} $ $dp_{i,k}+ dp_{k,j}$ 转移而来**。

则对于每个新的字符串 $S$，我们枚举转移$\sum_{i=1}^{26}$

若 $dp_{i,x}$ 有值，则 $dp_{i,y}=\max(dp_{i,y},dp_{i,x}+len)$ 

$dp_{x,y}=\max(dp_{x,y},len)$。

那么最后 $ans$ 为 $\sum_{i=1}^{26} $$\max (dp_{i,i},ans)$。


## Code
~~代码已作防抄袭处理~~
```cpp
#include<bits/stdc++.h>
#define int long long
#define in(x) scanf("%lld"，&x)
#define o() printf(" ")
#define O() puts("")
#define out(x) printf("%lld"，x)
const int maxn=1e2+10;
const int maxm=26+10;
using namespace std;
int n;
int x，y;
int ans;
int len;
char s[maxm];
int dp[maxm][maxm];
signed main() {
	in(n);
	for(int j=1; j<=n; j++) {
		cin>>s;
		len=strlen(s);
		int x=s[0]-'a'+1，y=s[len-1]-'a'+1;//变量意义同上文。
		for(int i=1; i<=26; i++)
			if(dp[i][x])
				dp[i][y]=max(dp[i][y]，dp[i][x]+len);
		dp[x][y]=max(dp[x][y]，len);//注意这个转移
	}
	for(int i=1; i<=26; i++)
		ans=max(dp[i][i]，ans);//取最大值
	out(ans);
	return 0;
}
```

---

## 作者：QianianXY (赞：0)

## 题目描述

给定 $n$ 个字符串，若首尾相接可合并，求结果串最大值。结果串自身首尾需相同。

## 题目分析

值得积累的 dp 模型。

设 $f(i,j)$ 表示首尾字母 ASCII 码分别为 $i,j$ 的串的最大长度

初始化：输入串 $S$，长度为 $len$，则 $f(S_1,S_{len}) = len$。

转移方程：$f(i,S_{len})=\max(f(i,S_1)+len) ('a'\le i\le'z')$

答案：由于结果串首尾相同，所以取 $f(i,i) ('a'\le i\le'z')$ 最大值即可。

## code


```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 1000
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, f[N][N], ans; char c[N];

int main()
{
	read(n);
	while (n--)
	{
		scanf("%s", c + 1); int len = strlen(c + 1);
		for (rei i = 'a'; i <= 'z'; i++) if (f[i][c[1]]) f[i][c[len]] = max(f[i][c[len]], f[i][c[1]] + len);
		f[c[1]][c[len]] = max(len, f[c[1]][c[len]]);
	}
	for (rei i = 'a'; i <= 'z'; i++) ans = max(f[i][i], ans);
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Tyyyyyy (赞：0)

# 题目大意
给出$n$个字符串，要求你输出它们可拼接的最大长度。

两个字符串可拼接，当且仅当字符串$1$的最后一个字符与字符串$2$的第一个字符相同，且字符串$1$的第一个字符与字符串$2$的最后一个字符相同。

一个字符串只能使用一次。
# 思路分析
数据范围很大，搜索当然是不行的，容易想到$dp$来解决这个问题。

定义$dp[i][j]$为从字符$i$到字符$j$可拼接的最大长度。

由于要求所有字符串可拼接的最大长度，因此依次输入字符串，对于每个字符串，判断是否可以拼接，如果可以，更新$dp$值。

定义$l$为当前字符串的第一个字符对应的$ASCII$编码，$r$为当前字符串的最后一个字符的$ASCII$编码，$len$为当前字符串的长度。

容易得到转移方程：
$dp[j][r]=max(dp[j][r],dp[j][l]+len)(dp[j][i]!=0)$（$j$为循环变量）

对于一般情况：$dp[l][r]=max(dp[l][r],len)$

AC代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
char name[15];
int dp[30][30];
int n,maxl,l,r,len;
int main()
{
	scanf("%d",&n);
	memset(dp,-63,sizeof(dp));
	for(int i=1;i<=n;i++)
	{
		scanf("%s",name);
		len=strlen(name);
		l=name[0]-'a';
		r=name[len-1]-'a';
		for(int j=0;j<26;j++)
		{
			if(dp[j][l])dp[j][r]=max(dp[j][r],dp[j][l]+len);
		}
		dp[l][r]=max(dp[l][r],len);
	}
	for(int i=0;i<26;i++)maxl=max(maxl,dp[i][i]);
	printf("%d",maxl);
	return 0;
}
```

---

