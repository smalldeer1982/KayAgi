# Two Strings

## 题目描述

字符串 $s = s_1 s_2 \dots s_{|s|}$（其中 $|s|$ 表示字符串 $s$ 的长度）的一个长度为 $|x|$ 的子序列是一个字符串 $x = s_{k_1} s_{k_2} \dots s_{k_{|x|}}$，其中 $1 \leq k_1 < k_2 < \dots < k_{|x|} \leq |s|$。

给定两个字符串 $s$ 和 $t$。考虑所有与字符串 $t$ 相同的 $s$ 的子序列。是否满足字符串 $s$ 的每一个字符都至少出现在其中一个这样的子序列中？换句话说，对于所有 $i$（$1 \leq i \leq |s|$），是否存在 $s$ 的子序列 $x = s_{k_1} s_{k_2} \dots s_{k_{|x|}}$，使得 $x = t$ 且对于某个 $j$（$1 \leq j \leq |x|$），有 $k_j = i$？


## 说明/提示

在第一个样例中，字符串 $t$ 可以作为子序列以三种方式出现在字符串 $s$ 中：abab、abab 和 abab。在这些出现方式中，$s$ 的每个字符至少出现一次。

在第二个样例中，字符串 $s$ 的第 4 个字符没有出现在任何 $t$ 的出现中。

在第三个样例中，字符串 $t$ 并未出现在字符串 $s$ 中。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
abab
ab
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
abacaba
aba
```

### 输出

```
No
```

## 样例 #3

### 输入

```
abc
ba
```

### 输出

```
No
```

# 题解

## 作者：water_tomato (赞：12)


[题目链接](https://www.luogu.com.cn/problem/CF223B) [博客版本](https://code.watertomato.com/cf223b-two-strings-%e9%a2%98%e8%a7%a3/)
### 题意

询问是否：对于 $s$ 中每一个 $s_i$，都找的到一个包含它的 $s$ 的**子序列**（不是子串）与 $t$ 相同。

### 解析

首先我们考虑，必须要按顺序找到第一个子序列，否则一定是 `No`。

例如，若 $t=abcd$，$s$ 的前几项可以为 $aabbbcdd$，但是不能为 $acbcd$，因为第一个 $c$ 一定不满足。

找到之后，我们记录每一个字母在 $t$ 中出现的最后一个位置。为什么是最后一个？因为我们后续找到字符，将他作为子序列中的后面那个位置一定比前面那个位置更容易配对。

例如：若 $t=aba$，我们后续在 $s$ 中找到了一个 $a$，那么记录最后一个位置，相当于将它接到最后去，这个子序列就已经满足了，如果将它作为第一个位置，还需要找到一个 $b$，显然是划不来的。

然后再使用一个指针 $l$，在便历 $s$ 的过程中，用 $l$ 记录下一个需要找的数在 $t$ 中是哪个位置，如果最终 $ l \le length_t$ 的话就说明一定存在某些字母没有配对成功。

如果仍然无法理解，可以结合代码，配有注释。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
char s[N],t[N];
int sn,tn,l=1,cnt=1;
int f[50];
int main(){
	scanf("%s%s",s+1,t+1);
	sn=strlen(s+1);tn=strlen(t+1);
	for(int i=1;i<=sn;i++){
		if(s[i]==t[cnt]) f[s[i]-'a']=++cnt;//记录 t 中每一个字母的位置 
		if(s[i]==t[l]) l++;//如果能接下去，那就接下去 
		if(f[s[i]-'a']<l) l=f[s[i]-'a'];//发现了一个更前的需要加入子序列的字母
		//只能将 l 往前移到这个字母的后面重新准备接下去 
		if(l<=1){ //如果发现了 t 中不存在的字母，或者第一个子序列接不成功 
			printf("No\n");//这两种情况中的任意一种都必然是 No 
			return 0;
		}
	}
	if(l<=tn) printf("No\n");//如果最后边接不上，也是 No 
	else printf("Yes\n");
	return 0;
}
```



---

## 作者：littlejuruo (赞：5)

## 写在前面

[可能更好的阅读体验](https://www.cnblogs.com/zhu-chen/p/14029183.html)

麻烦审核的管理员注意一下,把这题错误的翻译改掉,已经不少人被翻译坑了.

提供一下自己的翻译

>给你两个字符串$s,t$,判断是否满足对于每一个$s_i$,都存在$s$的子序列$x$,使$s_i \in x$且$x=t$
>
>Translated by [littlejuruo](https://www.luogu.com.cn/user/86815)

---
# Solution

对于每个位置,我们记录$l_i$表示$s_{1...i}$的所有子序列所能匹配$t$的最长前缀,$r_i$表示$s_{i...|s|}$的所有子序列所能匹配$t$的最长后缀.

那么易得当且仅当$r_i \le l_i$,我们能找到一个符合要求的子序列包含$s_i$

那么如何求出$l,r$呢?

以求$l$为例,我们用$pos_c$记录字符$c$目前的最长前缀,$k$表示前一个位置匹配的最长前缀,显然$k$不减,因此我们只需要考虑$s_i$和$t_k$是否相等,如果相等,就更新$pos$和$k$

$l_i$就等于$pos_{s_i}$

$r$也可以用同样的方式求出来,只不过把顺序和初值改一下就行了

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10,INF=0x3f3f3f3f;
void file(string s){freopen((s+".in").c_str(),"r",stdin),freopen((s+".out").c_str(),"w",stdout);}
int read(){
	int f=1,a=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		a=a*10+ch-'0';
		ch=getchar();
	}
	return a*f;
}

string s,t;
int l[MAXN],r[MAXN],pos[35];

void makel(){
	int k=0;
	memset(pos,-1,sizeof(pos));
	for(int i=0;i<s.length();++i){
		if(k<t.length()&&s[i]==t[k]){
			l[i]=k,pos[s[i]-'a']=k++;
		}else{
			l[i]=pos[s[i]-'a'];
		}
	}
}

void maker(){
	int k=t.length()-1;
	memset(pos,INF,sizeof(pos));
	for(int i=s.length()-1;i>=0;--i){
		if(k>=0&&s[i]==t[k]){
			r[i]=k,pos[s[i]-'a']=k--;
		}else{
			r[i]=pos[s[i]-'a'];
		}
	}
}

signed main(){
//  file("");
	cin>>s>>t;
	makel();
	maker();
	for(int i=0;i<s.length();++i){
		if(l[i]<r[i]){
			puts("No");
			return 0;	
		}
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：jasonliujiahua (赞：2)

# CF223B
[题目传送门](https://www.luogu.com.cn/problem/CF223B)
## 1. 题意简述
考虑 $s$ 的所有与 $t$ 相同的子序列，询问是否 $s$ 中每一个字母都属于这样的一个子序列中。
## 2. 转化
考虑 $s$ 中的一个字符 $s_i$，若 $s_i$ 满足条件，则有一个 $s$ 的子序列包含 $s_i$ 且等于 $t$，这就等价于存在 $s_1 \cdots s_i$ 的包含 $s_i$ 的子序列为 $t$ 的前缀，$s_i \cdots s_n$ 的包含 $s_i$ 的子序列为 $t$ 的后缀，两者可以拼出 $t$。

因此，不妨设 $f_i$ 表示 $s_1 \cdots s_i$ 的包含 $s_i$ 且为 $t$ 的前缀的最长子序列到 $t$ 中的位置，$g_i$ 同理。因此如果符合条件就等价于：
$$\forall i,f_i\ge g_i$$

## 3. DP
接下来考虑如何求出 $f$ 和 $g$。不少题解给出如下方法：
以求 $l_i$ 为例。$pos_i$ 表示当前包含字母 $i$ 的最大匹配长度，设一个指针 $k$ 表示之前的最大匹配匹配到了 $t$ 的前 $k-1$ 位。

如果 $s_j=t_k$，则 $l_j\gets k,pos[s_l]\gets k,k \gets k+1$。

否则 $l_j\gets pos[s_l]$。


接下来给出此方法的证明。
设 $x$ 表示 $s_i$ 这个字符。考虑 $t$ 中的情形：
![](https://cdn.luogu.com.cn/upload/image_hosting/6ce4hz92.png)
设 $x$ 上一次的位置在 $j$。
- 若将 $s_i$ 插入位置①，则与 $j$ 为上一次的定义矛盾，显然不行。
- 若将 $s_i$ 插入位置③，不如选②。

综上，$s_i$ 只可能插在 $k$ 或 $j$。而前者的条件是 $s_j=t_k$，因此若满足就更新 $k$ 和 $f_i$，否则继承上一位（注意这里 $j$ 其实就等于准备更新 $s_i$ 时的 $pos_x$）。



## 4. 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
char s[maxn],t[maxn];
int n,m,f[maxn],g[maxn],h1[maxn],h2[maxn];
void init()
{
    cin>>s+1;
    cin>>t+1;
    n=strlen(s+1);
    m=strlen(t+1);
}
void DP()
{
    int k=1;
    for(int i=1;i<=n;i++)
    {
        if(t[k]==s[i]) f[i]=h1[s[i]]=k++;
        else f[i]=h1[s[i]];
    }
    for(int i=1;i<=n+1;i++) g[i]=h2[s[i]]=m+1;
    k=m;
    for(int i=n;i;i--)
    {
        if(t[k]==s[i]) g[i]=h2[s[i]]=k--;
        else g[i]=h2[s[i]];
    }
}
void work()
{
    for(int i=1;i<=n;i++)
    {
        if(f[i]<g[i])
        {
            printf("No");
            return;
        }
    }
    printf("Yes");
}
int main()
{
    init();
    DP();
    work();
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

細節怪，思維怪。

$t$ 中的每個字母，做與 $s$ 的唯一的對應，指向最後出現的位置。

維護指針，作用為指向下一個需要匹配的對象在 $s$ 中的位置。它的維護借助上文的對應。具體的，遍歷 $s$，更新為現在的字母最後一個位置（借助上文的對應），如果原本指針更加後說明該字母已經被匹配。

總體來看，這個算法是多進度的。維護了每個字母對 $s$ 的映射，``指向最後`` 過濾掉了前部分重復字母，因為後面若能組成合法子序列，他們是肯定可行的。

但是這個算法可能有些不充分，在算法執行時刻，出現位置可能還沒有被覆蓋進子序列，那麽，指針就應該移到該位置。

那麽觀察已有算法，執行過程中的特殊情況要考慮。在 $s$ 中可能有 $t$ 中不存在字符，很顯然指針會一直叠代到原有的地方。

還有一種是尾部不能拼接，指針沒有指到最後。

核心代碼：

```cpp
for(int i = 1,j = 1;i<=len_s;i++) {
	if(s[i] == t[j]) j++,lst[s[i]] = j;
	if(s[i] == t[point]) ++point;
	if(lst[s[i]] <= point) point = lst[s[i]];
	if(point < 2) NO; 
}
```


---

## 作者：spire001 (赞：1)

## CF223B题解

### 题意
给你两个字符串 $s,t$。
问你是否 $s$ 中的每个字符，都可以在 $s$ 中的一个等于字符串 $t$ 的字符子序列（可以不连续）中找到。

### 分析
首先最开始我将题目读错了，以为 `KMP` 加差分秒了！
然而是子序列而不是子串，所以需要另想办法。

发现了一个优化 dp 解决此题目的办法。

首先一个字符如果满足题意的话，可能在这个字符前面有 $t$ 的一段，后面也有一段。

那么我们设置 $dp$ 数组，表示从前后最长能够拓展到几个字母，就可以通过从前拓展的距离加上从后拓展的距离是否大于 $|t|$ 来判断是否合法。

在程序中可以用下标代替长度，最后判断从前是否小于从后的长度即可。。。

用 $dp_{0,i}$ 表示从前往后最长拓展距离，$dp_{1,i}$ 反之。

那么我们可以打出这段暴力代码：
```cpp
for (int i = 1; i <= n; i++)
  for (int j = 0; j != i; j++)
    if (a[i] == b[dp[0][j] + 1])
      dp[0][i] = max(dp[0][i], dp[0][j] + 1);
for (int i = 1; i <= n; i++)
  for (int j = n + 1; j > i; j--)
    if (a[i] == b[dp[1][j] - 1])
      dp[1][i] = min(dp[1][i], dp[1][j] - 1);
```

那么很显然，这个 dp 是可以优化的，根据字符下标即可优化。
从 $O(|s|\times|t|)$ 优化到 $O(|s|)$。

### 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <map>

using namespace std;

constexpr int N = 200010;
typedef long long LL;

int n, m;
string a, b;
int flag[N];

map<char, int> mp;

int dp[2][N]; // dp[0][i] / dp[1][i] 表示 从左到右 / 从右到左 最远拓展到...
int f[512]; // 优化 dp 的数组

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> a >> b; 
  n = a.length(); m = b.length();
  a.insert(a.begin(), '#'); a.push_back('#'); // 避免 0 下标, 数组越界
  b.insert(b.begin(), '#'); b.push_back('#'); // 避免 0 下标, 数组越界

  if (a[1] != b[1] || a[n] != b[m])
    return cout << "No" << endl, 0; // 必要条件
  
  memset(f, -1, sizeof f); // 初始化为 -1 
  f[static_cast<int>(b[1])] = 1;

  for (int i = 1; i <= n; i++)
  {
    int k = static_cast<int>(a[i]); // 强制类型转换，防止弹警告
    dp[0][i] = f[k];
    int k1 = static_cast<int>(b[dp[0][i] + 1]);
    f[k1] = max(f[k1], dp[0][i] + 1);
  }
      
  fill(f, f + 512, m + 1);
  f[static_cast<int>(b[m])] = m;

  for (int i = n; i >= 1; i--)
  {
    int k = static_cast<int>(a[i]);
    dp[1][i] = f[k];
    int k1 = static_cast<int>(b[dp[1][i] - 1]);
    f[k1] = min(f[k1], dp[1][i] - 1);
  }

  for (int i = 1; i <= n; i++)
    if (dp[0][i] < dp[1][i]) // 判断每个字符是否合法
      return cout << "No" << endl, 0;
  
  cout << "Yes" << endl;

  return 0;
}
```

---

## 作者：eastcloud (赞：1)

[更好的阅读体验+广告](https://www.cnblogs.com/eastcloud/p/17056286.html)

## 题目分析

题目很短，只有两句话，可分析的不多，似乎难以入手，我们不妨换一个思路转化一下题意，改为：是否对于 $s$ 中的每一个字符，总有一个等于 $t$ 的 $s$ 的子序列**覆盖**它。

因此，我们可以考虑对于每一个字符，通过**前后拼接**的方式覆盖它，但是前后满足条件的子序列有很多，我们必须缩小范围。

考虑一下子序列的性质可以发现，总有一个等于 $t$ 的子序列（如果 $s$ 中有等于 $t$ 的子序列），它的每一个元素在 $s$ 中的下标都不晚于其他子序列的下标，这个结论很好证明，如果有一个不符合的那他肯定就不是这个最早的子序列。

知道了这个性质，来考虑前后拼接，我们对于 $s$ 的每一个字符 $s_i$，求出当 $s$ 的子序列 $u$ 以 $s_i$ 为结尾时，它最长能匹配到的 $t$ 的位置，前后都求一遍，记为 $j$ 和 $k$，因为具有前面提到的子序列的性质，这个位置一定是在 $t$ 中最后面或者最前面的，所以如果 $j<k$ 或者两个里有任意一个无法匹配，就无解，否则有解。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector> 
#define ll long long
using namespace std;
int pos[30];
int l[1000001],r[1000001];
int main(){
	string s,t;
	cin>>s>>t;
	int cnt=0,n=s.length(),m=t.length();
	memset(r,0x3f,sizeof(r));
	for(int i=0;i<n;i++){
		if(cnt!=m && s[i]==t[cnt]){
			l[i]=cnt+1;
			pos[s[i]-'a'+1]=cnt+1;
			cnt++;
		}
		else l[i]=pos[s[i]-'a'+1];
	}
	memset(pos,0,sizeof(pos));
	cnt=m-1;
	for(int i=n-1;i>=0;i--){
		if(cnt!=-1 && s[i]==t[cnt]){
			r[i]=cnt+1;
			pos[s[i]-'a'+1]=cnt+1;
			cnt--;
		}
		else r[i]=pos[s[i]-'a'+1];
	}
	for(int i=0;i<n;i++){
		if(l[i]<r[i] || (l[i]==0 || r[i]==0)){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
	return 0;
}

```



---

## 作者：vеctorwyx (赞：1)

看题直观感觉好像很简单，一做发现细节不少，有点复杂，做完又会觉得简单。。。

----------------


首先读题，~~注意问的是子序列不是字串~~。

最直接的想法是弄一个类似于双指针的东西扫一遍，看看 $s$ 串能不能整一个子序列跟 $t$ 串一样，然后再拿一个数组看看 $s$ 串中每一种元素是否都在 $t$ 串种出现。

然后就错了。。。

hack 数据是这样的：

```

babbbbbaba
ab

```
这样子最后一个 ``a`` 是没有 ``b`` 与它凑一个子序列的。

~~那是不是说倒着再跑一边就对了?~~

别急，这样子还是只有最前面和最后面一小部分是保证一定能凑出子序列的，其他位置还是不能确定。

定义某个位置的**前匹配长度**为以这个位置为结尾的子序列可以与 $t$ 的前缀匹配的长度，记为 $pr_i$。

同时定义**最大前匹配长度**为以这个位置为结尾的子序列可以与 $t$ 的前缀匹配的最大长度，记为 $mpr_i$。

那么同时可以记一个后匹配长度去维护后缀匹配，分别记为 $su_i$，$msu_i$。

回到双指针的地方，观察 $s$ 串：

1. 如果可以直接跟 $t$ 串匹配，则当前位置的最大匹配长度为 $t$ 串的当前匹配长度；

2. 如果不能直接匹配，则当前位置的最大匹配长度为上一个出现的这个字符的最大匹配长度。

关于匹配长度有个性质：

如果一个位置 $i$ 存在 $pr_i+su_i=len_t$，则这个位置一定可以被包含某个合法子序列中。

那么对于一个位置 $i$，满足 $mpr_i + msu_i \ge len _ t$， 则这个为是可以被包含某个合法子序列中。

显然 $mpr$ 和 $msu$ 可以在两次双指针扫的时候维护。

-------------

然后就有了一种做法：

用双指针正反各扫一遍，维护 $mpr$ 和 $msu$。对于 $s$ 串中每一个位置 $i$， 都要满足 $mpr_i + msu_i \ge len_t + 1$（加 $1$ 是因为位置 $i$ 会被算两边）

code:

```
#include<bits/stdc++.h>
using namespace std;
int n, m, len;
char s1[200010], s2[200010];
int pr[200010], su[200010];
int vis[233];
signed main(){
	scanf("%s", s1 + 1);
	n = strlen(s1 + 1);
	scanf("%s", s2 + 1);
	m = strlen(s2 + 1);
	int l1 = n, l2 = m;
	while(l1 >= 1 && l2 >= 1){
		while(s1[l1] != s2[l2] && l1 >= 1){
			pr[l1] = vis[s1[l1]];
			l1--;
		}
		if(s1[l1] == s2[l2]){
			vis[s1[l1]] = m - l2 + 1;
			pr[l1] = vis[s1[l1]];
			l1--, l2--;
		}
	}
	while(l1 >= 1){
		pr[l1] = vis[s1[l1]];
		l1--;
	}
	memset(vis, 0, sizeof(vis));
	l1 = 1, l2 = 1;
	while(l1 <= n && l2 <= m){
		while(s1[l1] != s2[l2] && l1 <= n){
			su[l1] = vis[s1[l1]];
			l1++;
		}
		if(s1[l1] == s2[l2]){
			vis[s1[l1]] = l2;
			su[l1] = vis[s1[l1]];
			l1++, l2++;
		}
	}
	while(l1 <= n){
		su[l1] = vis[s1[l1]];
		l1++;
	}	
	for(int i = 1; i <= n; i++)
		if(pr[i] + su[i] <= m){
			puts("No");
			return 0;
		}
	puts("Yes");
	return 0;
}
```

---

## 作者：Resurgammm (赞：1)

$upd:$ 修改了表述错误。 

> 给定两个字符串 $s$ 和 $t$，回答是否有：$t$ 串作为 $s$ 串的子序列把 $s$ 串的所有元素覆盖。

手玩一下可以发现，必须找到满足要求的第一个子序列，否则一定是无解的。

设 $l_i$ 为 $s_{1\dots i}$ 的所有子序列能匹配 $t$ 的最长前缀，$r_i$ 为 $s_{i\dots |S|} $ 的所有子序列能匹配 $t$ 的最长后缀。

如果在 $s$ 中任意一个位置时有 $l_i<r_i$ 那么都是无解的。

考虑如何求出 $l,r$ 数组。

设 $pos_i$ 为字母 $i$ 在 $t$ 中出现的最后一个位置，因为这样一定比它前面出现的位置更加容易进行配对。

以求出 $l$ 为例，设 $k$ 为前一个位置和 $t$ 所匹配的最长前缀，显然它是单增的。

那么只需判断 $s_i$ 和 $t_k$ 是否相等，如果相等则有 $l_i\gets k,pos_{s_i}\gets k,k\gets k+1$。

否则有 $l_i\gets pos_{s_i}$

求 $r$ 数组同理。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout);
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(y,x,sizeof(x))
	
	const int maxn=2e5+5;
	
	int n,m;
	char s[maxn],t[maxn];
	int l[maxn],r[maxn],pos[36];
	inline void getl(){
		int k=1; fill(pos,-1);
		for(int i=1;i<=n;i++){
			if(k<=m && s[i]==t[k]) l[i]=k,pos[s[i]-'a']=k++;
			else l[i]=pos[s[i]-'a'];
		}
	}
	inline void getr(){
		int k=m; fill(pos,0x3f3f3f3f);
		for(int i=n;i>=1;i--){
			if(k>=1 && s[i]==t[k]) r[i]=k,pos[s[i]-'a']=k--;
			else r[i]=pos[s[i]-'a'];
		}
	}
	
	inline int main(){
		scanf("%s",s+1); n=strlen(s+1);
		scanf("%s",t+1); m=strlen(t+1);
		getl(); getr(); 
		for(int i=1;i<=n;i++)
			if(l[i]<r[i]){puts("No"); exit(0);}
		puts("Yes");
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：Uuuuuur_ (赞：0)

先朴素地想，我们考虑 $S_i$ 能否接在字符 $S_j$ 后面，但是，$S_j$ 有很多种匹配 $T$ 的方法，我们无法确定到底能不能接。

这时候就有一个很贪心的思想，对于 $S_j$，只用知道它能匹配的最远距离（设为 $f_j$），因为 $S_j$ 匹配近距离的情况已经包含在内了。所以，我们只要把 $S_j,S_i$ 拼起来，在 $T$ 中找 $pos \le f_j$ 的 $S_iS_j$ 组合。

但是有两个问题：查找耗时；计算 $f_i$ 耗时。

先看计算 $f_i$，对于 $i$，不需要枚举所有之前的位置，只要枚举能接的字符是什么，对于同一种字符，肯定越接后面的越好，所有只要维护当前每种字符最大的 $f$，然后枚举字符，再在 $T$ 中找。

查找也能优化，二分查找就好，对于 $T$ 中每一种连续字符二元组 $(A,B)$，记录其所在所有位置，查找时直接二分。


现在我们得到了什么，一个 $f_i$， 它代表能匹配的最远距离。我们发现这个题目是有后效性的，对于 $S_i$，不仅前面要能接，后面也要能接。所以我们反着做一遍同样的**动态规划**，得到从后往前匹配能得到最远距离 $revf_i$，如果 $f_i + revf_i - 1 \ge m$，肯定是存在一个匹配子序列的。反之就不存在。

总复杂度 $O(kn \log n )$，$k$ 是字符集大小，在这里是 $26$，$2$ 秒时限还是比较轻松的。

二分时很多细节，比如加一减一问题，这里建议自己模拟一遍。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define num(A, B) (int((A) * 31 + (B)))
using namespace std;
const int N = 2e5 + 5;
int f[N], revf[N];
string a, b;
int n, m;
vector<int> fir[N];
int maxx[205];
int max(int x, int y) {
    return x > y ? x : y;
}
int main() {    
    cin >> a >> b;
    n = a.size(), m = b.size();
    for (int i = 1; i < m; i++) {
        fir[num(b[i - 1], b[i])].push_back(i - 1);
        sec[num(b[i - 1], b[i])].push_back(i);
    }
    
    for (int i = 0; i < n; i++) {
        if (a[i] == b[0]) f[i] = 1;
        for (char pre = 'a'; pre <= 'z'; pre++) {
            int now = num(pre, a[i]);
            if (!fir[now].empty()) {
                auto p = upper_bound(fir[now].begin(), fir[now].end(), maxx[pre] - 1);
                if (p != fir[now].begin()) {
                    p--;
                    f[i] = max(f[i], *p + 2);
                }
            }
        }
        maxx[a[i]] = f[i];
    }

    memset(maxx, 0, sizeof maxx);
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == b[m - 1]) revf[i] = 1;
        for (char nex = 'a'; nex <= 'z'; nex++) {
            int now = num(a[i], nex);
            if (!sec[now].empty()) {
                auto p = lower_bound(fir[now].begin(), fir[now].end(), m - maxx[nex] - 1);
               
                if (p != fir[now].end()) {
                    revf[i] = max(revf[i], m - *p);
                }
            }
        }
        maxx[a[i]] = revf[i];
    }

    for (int i = 0; i < n; i++) {

        if (f[i] + revf[i] - 1 < m) {
            cout << "No";
            return 0;
        }
    }
    cout <<"Yes";
    return 0;
}
```


---

## 作者：masterhuang (赞：0)

littlejuruo 和 火羽白日生 两位大佬的表述可能有些问题，如果我错了可以纠正。

下面说说我的理解。

----
发现如果包含第 $i$ 位的一个子序列 $a$ 满足 $a=t$。设原来第 $i$ 位在 $a$ 中是第 $j$ 位。

我们可以把 $a$ 分成 $a_1,a_2,...,a_j$ ，$a_j,a_{j+1},...,a_{|t|}$ 两个部分（注意这里第二个 $a_j$ 不是笔误）。

则 $a_1,a_2,...,a_j$ 匹配 $t$ 的前 $j$ 位，$a_j,a_{j+1},...,a_{|t|}$ 匹配 $t$ 的后面部分。

设 $l_i$ 表示： $s$ 的前 $i$ 位中，**包含第 $i$ 位**的所有子序列中，最大匹配了 $t$ 的前 $l_i$ 位。

同理：$r_i$ 表示： $s$ 的从最后一位到 $i$ 位中，**包含第 $i$ 位**的所有子序列中，最大匹配了 $t$ 的最后一位到第 $r_i$ 位。

举个例子：
```
s=abacaba
t=aba
则：
  1 2 3 4  5 6 7
l 1 2 3 无 3 2 3
r 1 2 1 无 1 2 3
```
比如这里 $l_5$。第一个的 $a$，第二个的 $b$，和**第五个**的 $a$ 组成的 $aba$ 和 $t$ 的前三位成功匹配。故 $l_5=3$ 。大家自行理解一下。

----
求法：以求 $l_i$ 为例（求 $r_i$ 同理，不明白可以看代码）。 $pos_i$ 表示当前包含字母 $i$ 的最大匹配长度。设已经处理了前 $j-1$ 位。令设一个指针 $k$ 表示之前的最大匹配匹配到了 $t$ 的前 $k-1$ 位。

如果 $s_j=t_k$，则 $l_j\gets k,pos[s_l]\gets k,k\gets k+1$。

否则 $l_j\gets pos[s_l] $。

通过 $l$ 的定义容易证明。于是就可以求出 $l,r$ 了。

求 $l$ 时初始 $pos$ 值都为 $0$ ，求 $r$ 时初始 $pos$ 值都为 $\infty$ 。为了满足下面的性质。$pos$ 在实际操作时要把字符 $s$ 减 $'a'$ 得到 $0-25$ 的数字。

-----
思考一下发现：第 $i$ 位时有解等价于 $l_i\ge r_i$。

于是判断一下输出即可。实现时和描述上一些名字有出入。

code:
```cpp
//落谷 CF223B
//https://www.luogu.com.cn/problem/CF223B
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=2e5+5;
int n,m,f[N],g[N],h[35];
char a[N],b[N];
int main()
{
	scanf("%s%s",a+1,b+1);n=strlen(a+1);m=strlen(b+1);
	for(int i=1,j=1;i<=n;i++)
	{
		if(a[i]==b[j]) f[i]=j,h[a[i]-'a']=j++;
		else f[i]=h[a[i]-'a'];//实现的时候字符-'a'转换为数字
	}
//求出上面说的l
	memset(h,0x3f,sizeof(h));
	for(int i=n,j=m;i;i--)
	{
		if(a[i]==b[j]) g[i]=j,h[a[i]-'a']=j--;
		else g[i]=h[a[i]-'a'];
	}
//求出上面说的r
	for(int i=1;i<=n;i++) if(f[i]<g[i]) return 0*puts("No");
	puts("Yes");
	return 0;
}
```

---

