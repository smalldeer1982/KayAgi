# [ABC381C] 11/22 Substring

## 题目描述

在本题中，11/22 字符串的定义与 A 问题和 E 问题相同。

当字符串 $T$ 满足以下所有条件时，称 $T$ 为 **11/22 字符串**。

- $|T|$ 是奇数。这里 $|T|$ 表示 $T$ 的长度。
- 第 $1$ 个字符到第 $\frac{|T|+1}{2}-1$ 个字符都是 `1`。
- 第 $\frac{|T|+1}{2}$ 个字符是 `/`。
- 第 $\frac{|T|+1}{2}+1$ 个字符到第 $|T|$ 个字符都是 `2`。

例如，`11/22`、`111/222`、`/` 是 11/22 字符串，但 `1122`、`1/22`、`11/2222`、`22/11`、`//2/2/211` 不是。

给定一个由 `1`、`2`、`/` 组成、长度为 $N$ 的字符串 $S$。$S$ 至少包含一个 `/`。  
请你求出 $S$ 的所有（连续的）子串中，作为 11/22 字符串的最大长度。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2 \times 10^5$
- $S$ 是由 `1`、`2`、`/` 组成的长度为 $N$ 的字符串
- $S$ 至少包含一个 `/`

## 样例解释 1

$S$ 的第 $2$ 个字符到第 $6$ 个字符组成的子串为 `11/22`，这是一个 11/22 字符串。在 $S$ 的所有子串中，这是最长的 11/22 字符串。因此答案为 $5$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8
211/2212```

### 输出

```
5```

## 样例 #2

### 输入

```
5
22/11```

### 输出

```
1```

## 样例 #3

### 输入

```
22
/1211/2///2111/2222/11```

### 输出

```
7```

# 题解

## 作者：FlowerAccepted (赞：5)

## 思路
可以发现，一个 `11/22` 字符串的正中间是 `/`，左边全是 `1` ，右边全是 `2`，并且 `1` 和 `2` 的个数相等。

一个想法是多指针，用 $i$ 维护 `11/22` 字符串的中间位置，$j$ 维护 `11/22` 字符串的开头，$k$ 维护 `11/22` 字符串的结尾。

让 $i$ 遍历 $T$ 的每个字符，如果 $T_i$ 是 `/`，则从 $i$ 开始向两边拓展 $j$，$k$，如果符合条件，则继续拓展，否则将得到的 $j - k$ 与当前的最大值 $MAX$ 取大值，作为新的 $MAX$。

$i$ 遍历完后输出 $MAX$ 即可。

## 代码
```cpp
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main() {
    int MAX = 1, n;
    string T, s;
    cin >> n >> T;
    for (int i = 0, j = 0, k = 0; i < n; i ++, j = i - 1, k = i + 1) {
        if (T[i] != '/') {
            continue;
        }
        while (j >= 0 && k < n && T[j] == '1' && T[k] == '2') {
            j --;
            k ++;
        }
        MAX = max(MAX, k - j - 1);
    }
    cout << MAX;
    return 0;
}

```

---

## 作者：include13_fAKe (赞：3)

直接从每一个 `/` 同时往左右暴力扩展即可。

因为暴力扩展不能跨过任何斜杠，所以任何数字只会被它两边相邻的斜杠暴力扩展到。

时间复杂度 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int len;
int include13=0;
signed main(){
	cin>>len;
	cin>>s;
//	len=s.size();
	s=' '+s;
	s[0]='#',s[len+1]='&';
	for(int i=1;i<=len;i++){
		int j=0;
		if(s[i]=='/'){
			while(s[i-j-1]=='1'&&s[i+j+1]=='2')	j++;
			include13=max(include13,j*2+1);
		}
	}
	cout<<include13<<endl;
	return 0; 
} //ABC381C 
```

---

## 作者：__Allen_123__ (赞：1)

> 定义一个 “$11/22$ 字符串”为一个长度为奇数，前一半为 $\texttt1$，最中间为 $\texttt/$，后一半为 $\texttt2
$ 的字符串，求 $S$ 中最长的为 $11/22$ 字符串的子串长度。

我们仍然考虑使用一个 `vector` 或数组存储每一个极长相同字符连续段的字符及其出现次数，可以发现，当其中有连续 $3$ 项满足第一项为连续 $x$ 个 $\texttt1$，第二项为单独一个 $\texttt/$，第三项为连续 $y$ 个 $\texttt2$ 时，可以形成一个长度为 $2\times\min\{x,y\}+1$ 的 $11/22$ 字符串。据此求解即可。

[AC 记录](https://atcoder.jp/contests/abc381/submissions/60044224)。

---

## 作者：Hughpig (赞：0)

观察发现，每个 $11/22$ 字符串都可以看作一个 $\texttt{/}$ 字符，前面跟着若干个 $1$，后面跟着若干个 $2$ 构成。为了最大化答案，前后的 $1$ 和 $2$ 的个数要尽可能多，可以取到前面 $1$ 个数和后面 $2$ 个数的较小值。

先预处理出两个数组 $a,b$。$a_i$ 表示以 $s_i$ 结尾最多有多少个 $\texttt{1}$，$b_i$ 表示以 $s_i$ 开头最多有多少个 $\texttt{2}$。

根据数组 $a$ 的定义显然，如果 $s_i$ 为 $1$，那么 $a_i=a_{i-1}+1$，否则 $a_i=0$。可以通过扫一遍 $s$ 预处理出 $a$ 数组。$b$ 数组同理。

然后对于每个 $s_i$，如果 $s_i=\texttt{/}$，根据上文的分析，以 $s_i$ 作为中间的 $11/22$ 字符串最长长度可以取到 $2\times \min(a_{i-1},b_{i+1})+1$，更新答案即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(int i=(l);(i)<=(r);++i)

constexpr int N=2e5+9;

int n;string s;
int a[N],b[N],ans;

int main()
{
	cin>>n>>s;
	up(0,n-1,i){
		if(s[i]=='1')a[i]=a[i-1]+1;
		else a[i]=0;
	}
	for(int i=n-1;~i;--i){
		if(s[i]=='2')b[i]=b[i+1]+1;
		else b[i]=0;
	}
	up(0,n-1,i){
		if(s[i]=='/'){
			ans=max(ans,min(a[i-1],b[i+1])*2+1);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Hacker_Cracker (赞：0)

## [ABC381C] 11/22 Substring 题解
### Solution
循环遍历，每次找到 `/` 暴力扩展判断即可。

这里说一下为什么这样的时间复杂度不是 $O(N^2)$。

这道题寻找的子串是具有非常明显特征的。不同于最长回文子串，它要求 `/` 左侧必须是 `1`，右侧必须是 `2`。那么一个合法的 11/22 串的右边必然不可能是另一个合法 11/22 串的左半部分；同理，一个合法 11/22 串的左半部分也不会成为另一个合法 11/22 串的右半部分。故时间复杂度只能是 $O(N)$。

文字说明可能不好理解。举个例子，字符串 `11/2222/221/22`，在第一个 `/` 处，只会扩展位置为 $1$ 到 $5$ 的字符串；在第二个 `/` 处，会扩展位置为 $8$ 的字符串；在第三个 `/` 处，会扩展位置为 $11$ 到 $13$ 的字符串。

### [AC](https://www.luogu.com.cn/record/190472156) Code
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
	int n;
	string s;
	cin>>n>>s;
	s=" "+s;
	int ans=1;
	for(int i=1;i<=n;i++){
		if(s[i]=='/'){
			int cnt=0,l=i-1,r=i+1;
			while(l>=1&&l<=n&&r>=1&&r<=n&&s[l]=='1'&&s[r]=='2'){
				l--,r++;
			}
			l++,r--;
			ans=max(ans,r-l+1);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：无名之雾 (赞：0)

场上想到了一个智慧做法，但是因为先开的 E 所以直接用 E 的代码过了。

## 思路

我们考虑这个 `11/22` 序列中一定需要存在 `/` 这个字符。

所以一个显然的思路就是从每个 `/` 开始向两边扩展判断现在的序列是否为合法的 `11/22` 序列。

### 复杂度证明

我们假定这个序列里一共有 $x$ 个 `/`，则在最劣情况下对于每个 `/` 我们都会一直向外扩展直到检查到另一个 `/` 的出现。也就是最多只会 $\dfrac{n}{x}$ 次。

所以这个做法的复杂度就是 $O(x\times \dfrac{n}{x})$ 也就是 $O(n)$ 的。

[submission](https://atcoder.jp/contests/abc381/submissions/60104221)

---

## 作者：Cosine_Func (赞：0)

先考虑只有一个 `/` 的做法。很显然，可以向两端延伸端点得到答案。再看本题，可以对每一个 `/` 分开处理。核心代码：
```cpp
int n,l,r,ans;
string s;
vector<int> pos;
inline void Solve(){
	cin>>n>>s;
	s=" "+s;
	s=s+" ";
	for(int i=1;i<=n;i++)
		if(s[i]=='/')
			pos.pb(i);
	for(int p:pos){
		l=r=p;
		while(1<=l and r<=n){
			if(s[l-1]=='1' and s[r+1]=='2')l--,r++;
			else break;
		}
		ans=max(ans,r-l+1);
	}
	cout<<ans;
}
```
尝试分析复杂度。容易得出，该算法的时间复杂度上界为 $O(N^2)$。但这是该算法的真实复杂度吗？显然不是。该算法在 4ms 内 AC 了本题。考虑进一步分析。当存在 $K$ 个 `/` 时，平均时间复杂度 $O(N+K\times\frac{N}{K})=O(N)$。

[参考代码](https://atcoder.jp/contests/abc381/submissions/60047550)

---

## 作者：4041nofoundGeoge (赞：0)

应该很~~毒瘤~~简单吧。

## 思路

题目中描述让我们在字符串中寻找 `11/22`。我们就可以以 `/` 为中心，分别创建两个指针（左指针和右指针），步骤如下：

- 最初，我们定义变量 $\text{ans}=0$。

- 对于每一个 $i=1,2,3,\dots N$ 执行一下操作：

  - 如果 $S[i]\not=$ `/`，愣着干啥，不用执行直接跳过这层循环。
  - 如果 $S[i]=$ `/`，执行一下过程（设 $d$ 为单向延伸长度，设左指针 $l=i-(d+1)$ 右指针 $r=i+(d+1)$）:
    - 如果 $l<1$ 或 $l>N$ 退出循环。
    - $r$ 同理违反跳出循环。
    - 如果 $S[l]\not=1$ 退出循环。
    - $S[r]$ 同理，跳出循环。
  - 打擂台，$\text{ans}=\max(\text{ans},1+2d)$。

- 最后输出 $\text{ans}$ 即可。

这个程序的时间复杂度为 $O(N)$。

代码就非常好写了。

## 代码

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
  int N;
  string S;
  cin >> N >> S;

  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] != '/') continue;
    int d = 0;
    while (true) {
      int j = i - (d + 1);
      int k = i + (d + 1);
      if (!(0 <= j and j < N)) break;
      if (!(0 <= k and k < N)) break;
      if (S[j] != '1') break;
      if (S[k] != '2') break;
      d++;
    }
    ans = max(ans, 1 + d * 2);
  }
  cout << ans << "\n";
}
```

完工于 $2024$ 年 $11$ 月 $23$ 日。

---

## 作者：linjinkun (赞：0)

先说一下暴力做法，就是每找到一个左斜线，就同时往左边和右边同事扩散，设左边的下标变量为 $l$，右边的下标变量为 $r$，那么他必须保证 $l \ge 1$ 并且 $r \le n$，这是边界条件，同时还要满足 $a_l = 1$ 和 $a_r = 2$，此时已经保证了我们的串长度为奇数了，然后取长度最大值就是答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
char a[N];
signed main()
{
	int n;
	scanf("%d",&n);
	scanf("%s",a+1);
	int num = 0;
	for(int i = 1;i<=n;i++)
	{
		if(a[i] == '/')//找到一个'/'
		{
			int ans = 0;
			int l = i-1,r = i+1;//同时往两个方向找
			while(l>=1&&r<=n&&a[l] == '1'&&a[r] == '2')//左边必须都是1，右边必须都是2
			{
				ans++;//这里只算一边的长度，另一边是一样的
				l--;//更新
				r++;//更新
			}
			num = max(num,(ans<<1)+1);//<<1指的是我们只算了一边，还有一样的另一边，+1指的是'/'
		}
	}
	printf("%d",num);
	return 0;
}
```
其实这题就是暴力做，主要在于如何证明暴力时间复杂度为 $O(n)$ 呢？

证明如下：

接下来说说复杂度证明，因为对于一个左斜线的位置，如果这个位置可以扩散（也就是有满足题目要求的字符串），那么这个位置的右边肯定有一串连续的 $2$，那么这些位置就不可能成为后面的左斜线的左边扩散的位置，那么这么一来，每个位置就只会被遍历 $1$ 次，那么时间复杂度为 $O(n)$，证毕。

---

