# K-Dominant Character

## 题目描述

您将得到一个全部由小写拉丁字母组成的字符串s，当且仅当对于每个长度不小于k的s的子串都含有字符c（c指某个小写拉丁字母），那么我们称c为k-主导字符。
您需要给出一个最小的k，使得对于给定的s至少存在一个k-主导字符。

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
2
```

## 样例 #2

### 输入

```
zzzzz
```

### 输出

```
1
```

## 样例 #3

### 输入

```
abcde
```

### 输出

```
3
```

# 题解

## 作者：yzx72424 (赞：4)

[题意](https://blog.csdn.net/gtuif/article/details/79382381)

思路：简单模拟

对字符串s中每个字符都算出k，取其中的最小值

```
#include<bits/stdc++.h>
using namespace std;
int l[27],r[27],t=0x3f3f3f3f;
char s[1000005]; 
int main(){
    scanf("%s",s+1);
    int c=strlen(s+1); 
    for(int i=1;i<=c;i++){
        int id=s[i]-97;
        l[id]=max(l[id],i-r[id]);
        r[id]=i;
    }
    for(int i=0;i<26;i++) l[i]= l[i]==0?0:max(l[i],c+1-r[i]); 
    for(int i=0;i<26;i++)t=l[i]==0?t:min(t,l[i]); 
    cout<<t;
}
```

---

## 作者：王熙文 (赞：4)

### 题目描述：

有一个包含小写字母的字符串 $s$，当且仅当对于所有长度不小于 $k$ 的 $s$ 子串都含有某个小写字母 $c$，那么我们成 $c$ 为 k- 主导字符。你需要找出一个最小的 $k$，使得对于 $s$ 至少存在一个 k- 主导字符。

### 解题思路：

考虑先枚举 k- 主导字符，从 `a` 到 `z`。

那么假设主导字符为 $c$，那么最少的长度就是两个相邻 $c$ 字符中最长的距离。

如这样：`c*****c`，那么 $k$ 就至少为 $6$，因为如果 $k$ 为 $5$，中间的 $5$ 个星中没有 $c$。

对于边界呢，若字符串的长度为 $l$，字符为 $1 \sim l$，那么把 $s_0$ 和 $s_{l+1}$ 变成 $c$ 就可以了。



### 参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int Max=1e9;

char s[100010];

int main()
{
	scanf("%s",s+1);
	int l=strlen(s+1),minzm=Max;
	for(char i='a'; i<='z'; ++i) // 枚举主导字符
	{
		s[0]=i;
		s[l+1]=i;
        // 将 s[0] 和 s[l+1] 都赋成主导字符，方便统计边界情况
		int j=1 /* 枚举字符串中下一个主导字符 */ ,last=0 /* 上一个主导字符的位置，默认为 0 */ ,maxqj=0 /* 最大的间隔 */ ;
		while(j<=l+1)
		{
			while(s[j]!=i) ++j; // 找到下一个主导字符
			maxqj=max(maxqj,j-last); // 更新最长间隔
			last=j++; // 更新上一个主导字符，并且 j 要加一
		}
		minzm=min(minzm,maxqj); // 更新答案最小值
	}
	printf("%d",minzm);
	return 0;
}
```

---

## 作者：sto__Liyhzh__orz (赞：3)

[这名字挺吉利的，（滑稽）](https://www.luogu.com.cn/problem/CF888C)

一道简单模拟，对于每个出现过的字母 $c$，我们只需依次算出它们的 $k_c$，再取最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=100000+5;

int l[30],r[30];
string s;

int main()
{
    cin>>s;
    int len=s.size();
    for(int i=0;i<len;i++)
    {
        int id=s[i]-97;
        l[id]=max(l[id],i+1-r[id]);
        r[id]=i+1;
    }
    for(int i=0;i<26;i++) 
    {
        if(l[i]!=0) l[i]=max(l[i],len+1-r[i]); 
    }
    int ans=1e9;
    for(int i=0;i<26;i++)
    {
        if(l[i]!=0) ans=min(ans,l[i]);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：_ZML_ (赞：2)

# 思路
不难想到用二分来做，我们二分 $k$。

判断方法很简单，把长度为 $k$ 的子串扫一遍，看一下有没有主导字符就行了。
# 部分代码
```cpp
//check函数部分
bool check(int mid) {
	for(int i=1;i<=26;i++) b[i]=0x3f3f3f3f;
	for(int j=mid;j<=len;j++){
		int i=j-mid+1;
		for(int k=1;k<=26;k++) a[k]=sum[j][k]-sum[i-1][k];
		for(int k=1;k<=26;k++) b[k]=min(b[k],a[k]);
	}
	for(int i=1;i<=26;i++) if (b[i]!=0) return true ;
	return false;
}
```


---

## 作者：__Hacheylight__ (赞：1)

楼上的$O(n)$题解太强了，本菜鸡来说一说其他做法

这个题目看到的第一感觉就是二分答案，因为又是要求最小值且答案有单调性

设$n=|S|$,二分最小的$k$，然后$O(n)$的扫出每个字串，把每个字串的字符信息保存，然后判断每一个字串是否有公共字符。

我们发现这样做有一些浪费时间，因为每个字串的字符信息是不会变的，于是我们可以把它前缀和记录一下

$sum[i][j]$表示前i个字符字符j出现的次数，然后枚举字串起点$l$和终点$r$，每个字符出现的次数就是$sum[r][j]-sum[l-1][j]$就好了

优化完的时间复杂度为$O(nlogn)$

$wow!$

$n$才$10^5$这。。。二分也能过,出题人tql

```cpp
#include <map>
#include <set>
#include <ctime>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std ;
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define per(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define enter cout << endl
#define siz(x) ((int)x.size())
typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 100010 ;
const int M = 30 ;
const int INF = 0x3f3f3f3f ;
const int iinf = 1 << 30 ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

int a[M], b[M] ;
int sum[N][M] ;
char s[N] ;
int n ;

bool check(int x) {
    for (int i = 1; i <= 26; i++) b[i] = iinf ;
    for (int r = x; r <= n; r++) {
        int l = r - x + 1 ;
        for (int i = 1; i <= 26; i++) a[i] = sum[r][i] - sum[l - 1][i] ;
        for (int i = 1; i <= 26; i++) b[i] = min(b[i], a[i]) ;
    }
    for (int i = 1; i <= 26; i++) if (b[i]) return true ;
    return false ;
}

signed main(){
    scanf("%s", s + 1) ; n = strlen(s + 1) ;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 26; j++) sum[i][j] = sum[i - 1][j] ;
        sum[i][s[i] - 'a' + 1]++ ;
    }
    int l = 0, r = n + 1 ;
    while (l + 1 < r) {
        int mid = (l + r) >> 1 ;
        if (check(mid)) r = mid ;
        else l = mid ;
    }
    printf("%d\n", r) ;
    return 0 ;
}

```

---

## 作者：RioFutaba (赞：0)

8！8！8！
## 思路

二分很容易，枚举 $k$ 和 $c$ 然后枚举所有长度为 $k$ 的字串直接判断即可。复杂度是 $O(n \log n)$。

或者可以算出每个字符在 $s$ 中最大的间隔，如 ```a``` 在 ```abcdeaba``` 中的最大间隔是 ```abcdea``` 的 $5$。一个 $c$ 在 $s$ 中的最大间隔就是 $c$ 所对应的最小的 $k$。复杂度为 $O(n)$。

最小的最大间隔就是答案。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

string s;
int last[256],a[256];
int ans;
int main(){
	cin >> s;
	ans=s.length();
	s=" "+s;
	for(int i=1;i<s.length();i++){
		a[s[i]]=max(a[s[i]],i-last[s[i]]);
		last[s[i]]=i;
	}
	for(int c='a';c<='z';c++)
		if(a[c]) ans=min(ans,max(a[c],(int)s.length()-last[c]));
	cout << ans << "\n";
	return 0;
} 
```

---

## 作者：liuzhongrui (赞：0)

~~做这题的人一定会发的！~~

## 思路

首先，我们可以遍历字符串，将每个字符及其下标存储在一个 `map` 中。这里 `map` 的键是字符，值是一个包含该字符所有出现位置的列表。

接下来我们需要计算 $ k $ 的值，对于每个字符，我们需要计算它在字符串中能支持的最大子串长度 $ k $。也就是说，对于字符 $ c $，我们可以取得它在字符串中所有出现的下标，并计算相邻两个下标之间的距离，最大距离的补充将直接与我们希望的 $ k $ 值相关。

最后，我们遍历完所有字符之后，取所有字符计算得到的 $ k $ 的最小值，这个 $ k $ 就是我们要的东西。

## 代码



```cpp

#include <bits/stdc++.h>
using namespace std;
string str;
map<char, vector<int> > mp;
int main() {
	getline(cin >> ws, str);
	int n = str.length();
	for (int i = 0; i < n; i++)
		mp[str[i]].push_back(i);
	int ans = n / 2 + 1;
	for (auto i : mp) {
		if (i.second.size() >= 2) {
			int res = i.second[0] + 1;
			for (int j = 1; j < i.second.size(); j++){
				res = max(i.second[j] - i.second[j - 1], res);
			}
			res = max((int)(n - i.second.back()), res);
			ans = min(ans, res);
		}
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：GJX_Algorithm (赞：0)

# CF888C 题解

## 题目描述
- 给定一个只由小写字母组成的字符串 $s$。
- 当每个长度至少为 $k$ 的 $s$ 的子串都包含字符 
$c$ 时，称字符 $c$ 为 k-主导字符。
- 输出一个最小的 $k$，且 $s$ 中至少有一个 k-主导字符。

## 解题思路
### 二分做法
- 第一遍看完题，不难发现题中的 $k$ 是具有单调性的，再看一眼范围 $10^5$，直接尝试二分答案。
- 二分 $k$，检查是否每个长度为 $k$ 的子串都包含同一个字符。
- 但，暴力枚举每一个子串，然后又统计出现次数肯定会超时，所以还得用前缀和维护每个字母出现的次数，注意维护前缀和时要**把每个字母都赋值**，而**不是**：
  ```cpp
  pre[i][s[i] - 'a'] = pre[i - 1][s[i] - 'a'] + 1;
  ```
- 时间复杂度 $O(n \log n)$。
- 前缀和维护部分：
  ```cpp
  s = "#" + s;
  for (int i = 1; i < s.size(); i++)
  {
      for (int c = 0; c < 26; c++) pre[i][c] = pre[i - 1][c];
      pre[i][s[i] - 'a']++;
  }
  ```
- $\texttt{check}$ 部分：
  ```cpp
  bool check(int x)
  {
      int flag[30] = {0};
      for (int i = 1; i + x - 1 < s.size(); i++)
      {
          int j = i + x - 1;
          for (int c = 0; c < 26; c++)
              if (pre[j][c] - pre[i - 1][c] == 0)
                  flag[c] = 1;
      }
      for (int c = 0; c < 26; c++)
          if (flag[c] == 0)
              return 1;
      return 0;
  }
  ```

### 模拟做法
- 二分 AC 之后再看一眼题，发现似乎可以 $O(n)$ 过……所以读者看完题后一定要思考一下，~~不然会像笔者一样~~。
- 我们假设一个字符串的子串长这样：$\texttt{adrba}$，如果 $a$ 为主导字符，$k < 4$的话，$\texttt{drb}$ 不包含 $a$，所以一定有 $k \ge 4$。
- 对于边界的处理，我们发现，$last$ 初始值为 0，左边界可以不用考虑，右边界只需在循环完后虚拟一个点再取一边最大值即可。
- 接下来只要枚举主导字符，计算最长间隔，然后取最小值即可。
- 代码
  ```cpp
  s = "#" + s;
  int n = s.size();
  for (int c = 0; c < 26; c++)
  {
      int last = 0, len = 0;
      for (int i = 1; i < n; i++)
          if (s[i] - 'a' == c)
          {
              len = max(len, i - last);
              last = i;
          }
      len = max(len, n - last);
      ans = min(ans, len);
  }
  ```

---

## 作者：Undefined_Shawn (赞：0)

本题是个简单的模拟，思维量不高。

### 解题思路

枚举 $26$ 个字母，对于每个字母找出它的 $k$。
那怎么找出每个字母的 $k$ 呢？
分析一下：

如果是这种情况（ X 为当前的字母）
```
X···X
```
那么长度最小为 $4$，因为如果长度小于 $4$，那么中间的其他字符就不符合条件了，所以长度最小为 $4$。

知道这点后就简单多了，直接开写！
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7;

char s[N];      // 输入的字符串

int main() {
    scanf("%s", s + 1);
    int len = strlen(s + 1), ans = len;    // len长度，ans初始化为长度，因为ans最长也就能取到长度
    for (char c = 'a'; c <= 'z'; c++) {   // 枚举26个字母
        int cnt = 0, tmp = 0;    // cnt计算当前的长度（临时），tmp计算k-主导字符是c的长度（k）
        // 计算从c到后一个c的长度
        for (int i = 1; i <= len; i++) {
            cnt++;
            if (s[i] == c) {   
                tmp = max(tmp, cnt);
                cnt = 0;
            }
    	}
        tmp = max(tmp, cnt + 1);      // 别忘了最后一段！！蒟蒻在这里调了半天
        ans = min(ans, tmp);    //  统计答案
    }
    cout << ans;   // 华丽结束QAQ
    return 0;
}
```

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给出一个字符串 $s(1\le |s|\le 10^5)$。你要找到一个最小的 $k$，使得存在一个字符 $c$，在每个长度为 $k$ 的子串中都出现。

## 思路1

我们很容易想到可以直接二分 $k$，然后判定 $k$ 是否可行，判定方法很简单，只需要把每一个长度为 $k$ 的子串全部检查一遍，看看是否有字母都存在于这些子串中。这种方法的时间复杂度为 $O(n\log n)$。

## 代码1

接下来放上二分代码（主要部分）。

```cpp
#define REP(I, N) for (int I = 0; I < (N); ++I)
#define FORS(I, S) for (int I = 0; S[I]; ++I)
const int SIZE = 1e6+10;
char s[SIZE];
int main(){
    RS(s);
    int ll=1,rr=LEN(s);
    while(ll<rr){
        int mm=(ll+rr)/2;
        int cnt[26]={};
        bool fail[26]={};
        FORS(i,s){
            cnt[s[i]-'a']++;
            if(i>=mm-1){
                REP(j,26)if(!cnt[j])fail[j]=1;
                cnt[s[i-mm+1]-'a']--;
            }
        }
        bool suc=0;
        REP(i,26)
            if(!fail[i])suc=1;
        if(suc)rr=mm;
        else ll=mm+1;
    }
    W(ll);
    return 0;
}
```

## 思路2

我们也可以对于 26 个字符全部计算出最小的 $k$，然后取其中最小的一个 $k$ 即可。这种方法的时间复杂度为 $O(n)$。

对于字符 $c$，先找出它在字符串中出现的所有位置，$k$ 就是它们之间所有间隔的最大值再加一。

## 代码2

接下来放上思路 2 的代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int c[50],lx[50],ans=1e9;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>s;
    int n=s.size();
    for(int i=0;i<26;i++)lx[i]=-1;
    for(int i=0;i<n;i++){
	c[s[i]-'a']=max(c[s[i]-'a'],i-lx[s[i]-'a']);
	lx[s[i]-'a']=i;
    }
    for(int i=0;i<26;i++)ans=min(ans,max(c[i],n-lx[i]));
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：yeshubo_qwq (赞：0)

思路：

对于每一个字母，算出它最小的 $k$，再在所有字母最小的 $k$ 里取最小。

如何求出对应字母最小的 $k$？

如果有这样一段（`c` 为对应字母）`c###c`，中间一段长度为 $3$，那么最小的 $k$ 至少为 $4$。因为最小的 $k$ 如果为 $3$，中间的 $3$ 个字母中没有对应字母。

注意处理边界时要 $+1$。如 `c##`，长度为 $2$，但因为边界没有对应字母，所以要 $+1$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,cnt,k,ans;
char c,s[100005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s+1;ans=n=strlen(s+1);
	for (c='a';c<='z';c++){
		for (i=1;i<=n;i++){
			cnt++;
			if (s[i]==c) k=max(k,cnt),cnt=0;
		}
		k=max(k,cnt+1),cnt=0;
		ans=min(ans,k),k=0;
	}
	return cout<<ans,0;
}
```


---

## 作者：codeLJH114514 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF888C)

# $\textbf{Problem}$

给定一个字符串，定义一个字符 $c$ 是 **$k$ 主导字符** 当且仅当每一个长度**不小于 $k$ 的子串**都包含 $c$。
 
请问，已知 $k$ 满足至少有一个 $k$ 主导字符，那么 $k$ 的最小值是多少？

$1 \le N \le 10^5$，其中 $N$ 是给定字符串的长度。

# $\textbf{Analysis}$

首先，我们可以把 $k$ 主导字符的条件转换成：当且仅当每一个长度**等于 $k$ 的子串**都包含 $c$。因为，每一个长度大于 $k$ 的子串肯定包含一个长度等于 $k$ 的子串，所以有：所有长度等于 $k$ 的子串包含 $c \to $ 所有长度大于 $k$ 的子串一定包含 $c$。

然后，我们枚举 $c$，对于每一个 $c$ 都算出来 $c$ 是 $k$ 主导字符中的 $k$ 的最小值。

最后，直接把所有 $k$ 取最小值即可。

关于时间复杂度：因为 $N$ 最大值十万，所以我们对于每一个 $c$ 都需要保证算的时间复杂度为 $\mathcal{O}(N)$。

我们这样算：对于每一个在字符串中的 $c$ 和第 $0$ 个和第 $N + 1$ 个，我们给相邻的它们之间的距离（距离就是相隔的字符数） $+1$ 取 `max`。

为什么这样算对的呢？因为比算出来的 $k$ 小的一定在最远的两个距离里面没有 $c$，我们这样又能保证 $c$ 一定是 $k$ 主导字符，所以这样就是对的。

举个例子：`aaaabaaababaaaaaaaabaaaaaaaaaa`，$c = b$，所有的距离为 $\{4,3,1,8,10\}$，这个算法给出的是 $11$。如果再取小一点？比如 $10$，那么就会在最后一段挂掉，$10$ 都不行那更小的绝对不行，然后你又找不到不含 $b$ 的长度为 $11$ 的子串，所以 $11$ 就是答案。

说了这么多，上代码吧：

代码一共只有 $18$ 行。

```cpp
#include <iostream>
std::string s;
int Answered;
int main() {
    std::cin >> s;
    Answered = s.size() / 2 + 1;
    for (int i = 0; i < 26; i++) {
        char ch = i + 'a';
        int Last = -1, k = 0xACACACAC;
        for (int j = 0; j < s.size(); j++) 
            if (s[j] == ch) 
                k = std::max(k, j - Last),
                Last = j;
        Answered = std::min(std::max(k, (int)s.size() - Last), Answered);
    }
    std::cout << Answered << "\n";
    return 0;
}
```

总结：这是一道思维含量一般，代码量也一般的题目。

---

