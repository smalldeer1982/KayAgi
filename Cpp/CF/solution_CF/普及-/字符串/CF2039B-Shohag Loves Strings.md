# Shohag Loves Strings

## 题目描述

# Shohag Loves Strings

## 问题描述

给定一个字符串 $s$，定义 $f(p)$ 为字符串 $p$ 的所有不同的非空子字符串的数量。从字符串 $s$ 中找到一个非空子字符串 $p$，使得 $f(p)$ 为偶数。如果找不到这样的子字符串，则输出 $-1$。

## 样例 #1

### 输入

```
5
dcabaac
a
youknowwho
codeforces
bangladesh```

### 输出

```
abaa
-1
youknowwho
eforce
bang```

# 题解

## 作者：___define___ (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF2039B)

[原题传送门](https://codeforces.com/problemset/problem/2039/B)

## 思路

不要被题目的样例吓到了，其实这题并不是很难。

题目中给出的数据范围较大，所以我们优先找长度小的子串。

容易发现，若一个子串长度为二且子串里的字符相同，那么这个子串就是符合题目要求的。例如 `aa`，可以拆分为 `a` 和 `aa`。

若一个子串长度为三且子串里的字符两两不同，那么这个子串也是符合题目要求的。例如 `abc`，可以拆分为 `a`、`b`、`c`、`ab`、`bc` 和 `abc`。

若一个子串长度为三，中间的字符与其它两个字符不同且其他两个字符相同，那么这个子串不符合题目要求。例如 `aba`，可以拆分为 `a`、`b`、`ab`、`ba` 和 `aba`。

如果一个子串长度为一，那么这个子串显然不符合题目要求。

由于一个字符串都是由上述四种子串类型组成的，所以我们只需找符合题目要求的两种类型的子串，找到了就输出，找不到输出 `-1` 就行了。

[AC 代码](https://codeforces.com/contest/2039/submission/294125039)

---

## 作者：wangyizhi (赞：2)

题目传送门 ： [洛谷](https://www.luogu.com.cn/problem/CF2039B) | [CodeForces](https://codeforces.com/problemset/problem/2039/B)

## 题目大意

给一个字符串，求出其中一个**子串（必须连续！）**，使这个字串中的非空子串构成的集合（即要去重）的大小为偶数并输出。若无输出`-1`。

## 题目分析

~~显然找规律~~

我们肯定要找几种较短的、满足条件的字符串，然后再在原串中找类似的。

对于一个形如`a`的字符串，显然不行。考虑两个字符时的情况：

+ 对于形如`aa`的字符串，其中不同的非空字串的个数为 $2$，满足；
+ 对于形如`ab`的字符串，其中不同的非空字串的个数为 $3$，不满足。

因此我们首先可以找连续的两个相同的字符，那如果没有呢？

那我们再来看三个字符的情况：

+ 对于形如`abc`的字符串，其中不同的非空字串的个数为 $6$，满足；
+ 对于形如`aba`的字符串，其中不同的非空字串的个数为 $5$，不满足；

因此，然后我们可以找连续的互不相同的三个字符。

那如果都没有呢？满足这个条件的字符串只有这种：`abababab...`，对于长为 $n$ 的这样的一个字符串，可以算出其中不同的非空字串的个数为 $2n-1$，一定为奇数。

因此我们只要求其中形如`aa`或`abc`的串就行辣！

## AC Code

```cpp
// by wangyizhi(571247)
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		int n=s.length();
		if(n==1) // n=1 显然无解
			cout<<-1<<endl;
		else
		{
			bool flag=0;
			for(int i=1;i<n;i++)
			{
				if(s[i]==s[i-1]) // aa 有解
				{
					flag=1;
					cout<<s[i]<<s[i]<<endl;
					break;
				}
			}
			if(flag) continue;
			for(int i=2;i<n;i++)
			{
				if(s[i]!=s[i-1]&&s[i-1]!=s[i-2]&&s[i]!=s[i-2]) // abc 有解
				{
					flag=1;
					cout<<s[i-2]<<s[i-1]<<s[i]<<endl;
					break;
				}
			}
			if(flag) continue;
			else cout<<-1<<endl; // 否则无解
		}
	}
	return 0;
}
```

###### 蒟蒻的第一篇题解，管理大大求过！！！

---

## 作者：lunjiahao (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF2039B)

[CF 题目传送门](http://codeforces.com/problemset/problem/2039/B)

[博客园](https://www.cnblogs.com/lunjiahao/p/18573081)**可能**食用更佳

### 题目大意：
对于一个字符串 $p$ ，钦定 $\operatorname{f}(p)$ 表示 $p$ 的非空子串 $^\dag$ 的个数。

多组数据，每次给定一个字符串 $s$，求能否找出一个非空字符串 $p$，使得 $p$ 是 $s$ 的子串，并且满足 $\operatorname{f}(p)$ 为偶数，存在输出任意一个满足条件的字符串 $p$，无解输出 `-1`。

数据范围：$1 \leq \lvert s \rvert \leq 10^5,\sum \lvert s \rvert \leq 3 \times 10^5$。

$^\dag$ 如果字符串 $a$ 能由字符串 $b$ 删除开头和结尾的若干个字符（可以是 $0$ 个）得到，那么就称 $a$ 是 $b$ 的子串。

### 题目分析：

显然是不能枚举 $s$ 的每一个子串，考虑减少枚举子串长度的范围。

钦定 $t$ 为 $s$ 的子串，字符串从下标 $0$ 开始，分类讨论：

- $\lvert t \rvert = 1$ 时，

  此时 $\operatorname{f}(t)$ 恒为 $1$，不满足题意，故不考虑枚举。

- $\lvert t \rvert = 2$ 时，

  分类讨论：

  1. 若 $t_0 \neq t_1$，则 $\operatorname{f}(t)=3$，不满足题意；
  2. 若 $t_0 = t_1$，则 $\operatorname{f}(t)=2$，满足题意。

- $\lvert t \rvert = 3$ 时，

  分类讨论：

  1. 若 $t_0 \neq t_1 \neq t_2$，则 $\operatorname{f}(t)=6$，满足题意；
  2. 若 $t_0 = t_1 \neq t_2$，则 $\operatorname{f}(t)=5$，不满足题意，其余几种包含两个字符相同的情况一致，故不再赘述；
  3. 若 $t_0 = t_1 = t_2$，则 $\operatorname{f}(t)=2$，满足题意，但这种情况已在 $\lvert t \rvert = 2,t_0=t_1$ 时枚举了，故不考虑枚举。

- $\lvert t \lvert \geq 4$ 时，不难发现前面已验证过其非空真子串，故不用再进行枚举了。

综上所得，枚举每一个长度为 $2$ 和长度为 $3$ 的子串即可检验是否存在解。

### Code:

注意代码中的字符串下标从 $1$ 开始，与上文并非一致

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
char st[N];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",st+1);
		int n=strlen(st+1);
		if(n==1)
		{
			puts("-1");
			continue;
		}
		bool flag=false;
		for(int i=1;i+2<=n;i++)
			if(st[i]!=st[i+1]&&st[i]!=st[i+2]&&st[i+1]!=st[i+2])
			{
				printf("%c%c%c\n",st[i],st[i+1],st[i+2]);
				flag=true;
				break;
			}
		if(flag) continue;
		for(int i=1;i+1<=n;i++)
			if(st[i]==st[i+1])
			{
				printf("%c%c\n",st[i],st[i+1]);
				flag=true;
				break;
			}
		if(!flag) puts("-1");
	}
	return 0;
}
```

---

## 作者：_lmh_ (赞：1)

手玩一下发现形如 `AA` 或是 `ABC` 这样的字符串都恰有偶数个本质不同子串，如果存在这样的子串直接输出即可。

否则，相邻的字符都不相等，但又不存在三个相邻的字符两两不同，所以间距为 $2$ 的字符都相等，字符串形如 `ABABABAB...A` 或 `ABABABAB...AB`。

这个东西的任意一个子串也都是这两种类型，设其长度为 $n$，容易发现这个子串的形态只和它的开头字符和长度有关，则它长度为 $n$ 的子串有 $1$ 个，其余长度的子串都有两个（开头可以为 `A` 也可以为 `B`），总字串个数为奇数，无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007;
ll T,n,lst[26];
char s[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>(s+1);n=strlen(s+1);
		memset(lst,-1,sizeof(lst));
		bool fl=1;
		for (int i=1;i<n;++i) if (s[i]==s[i+1]){
			cout<<s[i]<<s[i+1];fl=0;break;
		}
		if (fl){
			for (int i=2;i<n;++i) if (s[i-1]!=s[i+1]){
				cout<<s[i-1]<<s[i]<<s[i+1];fl=0;break;
			}
		}
		if (fl) cout<<"-1";cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Chenyanxi0829 (赞：1)

考虑长度是一的子串其 $f$ 值为 $1$，不满足。接着考虑长度是二的子串，如果两个字符相同则 $f$ 值为 $2$，满足，直接输出。否则 $f$ 值为 $3$，不满足。如果长度为二的合法子串不存在，则说明相邻两个字符不相同。再考虑长度是三的子串，如果这三个字符都不相同，则 $f$ 值为 $6$，满足要求。如果还没有这种子串，那么这个串就形如 $c_1c_2c_1c_2\dots$，这样所有子串的 $f$ 值都是 $2len-1$，因为长度小于 $len$ 的子串有两种，长度为 $len$ 的子串有一种，于是就证明了这种串不存在合法子串。

### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 100, mod = 998244353;

int t;
string s;

void S() {
  for (int i = 0; i + 1 < s.size(); i++) {
    if (s[i] == s[i + 1]) {
      cout << s[i] << s[i + 1] << '\n';
      return;
    }
  }
  for (int i = 0; i + 2 < s.size(); i++) {
    if (s[i] != s[i + 2]) {
      cout << s[i] << s[i + 1] << s[i + 2] << '\n';
      return;
    }
  }
  cout << "-1\n";
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> s, S();
  }
  return 0;
}
```

---

## 作者：GeYang (赞：0)

# 题意

给你一个字符串，求一个非空子串使得其所有不同的非空子字符串的数量为偶数。

# 思路

数据较大，不能穷举。

考虑化繁为简，找“基本”的子串。所谓“基本”子串，就是尽可能短的符合要求的子串。

## 过程

### 长度较短的子串

当长度为 $1$ 时，没有符合要求的子串。

当长度为 $2$ 时，若两元素相同，则共 $2$ 种，符合要求；若两元素不相同，则共有 $3$ 种，不符合条件。

当长度为 $3$ 时，只有相邻两元素不相同的子串满足条件。

当长度为 $4$ 时，拆成两个长度为 $2$ 的子串分析。

当长度为 $5$ 时，拆成一个长度为 $2$ 的子串和一个长度为 $3$ 的子串。

我们似乎可以发现什么。

### 长度较长的子串

当子串长度为 $n$ 且 $n>3$ 时，设长度为 $2$ 的子串有 $x$ 个，长度为 $3$ 的子串有 $y$ 个，两种子串的个数都是整数且可以为零。

构造方法不唯一，有多种证法，下面给出其中一种。

当 $n$ 为奇数时，满足 $x=\frac{n-3}{2}$ 且 $y=1$。

当 $n$ 为偶数时，满足 $x=\frac{n}{2}$ 且 $y=0$。

因此当子串长度大于三时，都可以用长度为 $2$ 的子串和长度为 $3$ 的子串拼接而成，结论与长度较短的子串相同。

## 结论

以下所有子串都满足要求，直接查找即可。

- 长度为 $2$ 且两元素相同的。

- 长度为 $3$ 且相邻两元素互不相同的（首尾可以相同）。

---

## 作者：HYdroKomide (赞：0)

### 题意：

给定一个字符串，问其是否包含一个非空子串，使该子串本质不同的非空子串数量是偶数。

### 思路：

发现如果字符串很长，本质非空子串的数量不好处理。不妨直接从最短的一些子串考虑，手搓一些性质。

1. 子串长度为 $1$：本质不同的子串个数必然为 $1$，不符合；
2. 子串长度为 $2$：如果两个字符相同（如 `aa`），本质不同子串个数是 $2$，符合条件；如果两个字符不同（如 `ab`），本质不同的子串个数是 $3$，不符合；
3. 子串长度为 $3$：如果存在两个相邻相同的字符，则必然符合 $2$ 中的情况，符合条件。于是我们只剩下 `aba`、`abc` 的两种情况。前者不符合条件，后者符合；

由上述情况继续推算，不难发现，只有原字串是类似 `abababababab` 这样 `ab` 交替的字符串，才不存在符合条件的子串，输出 `-1`，其它字符串都一定存在子串符合条件。

### 程序如下：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=1e5+5;
int T;
char ch[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s",ch+1);
		int n=strlen(ch+1);
		bool flag=false;
		for(int i=1;i<n;i++){
			if(ch[i]==ch[i+1]){
				printf("%c%c\n",ch[i],ch[i+1]);
				flag=true;
				break;
			}
			if(ch[i]!=ch[i+1]&&ch[i+1]!=ch[i+2]&&ch[i]!=ch[i+2]&&i+2<=n){
				printf("%c%c%c\n",ch[i],ch[i+1],ch[i+2]);
				flag=true;
				break;
			}
		}
		if(!flag)printf("-1\n");
	}
	return 0;
} 
```
### THE END

---

## 作者：Vct14 (赞：0)

下文中“子串”均指非空子串。

两个相邻字符相同，如 `aa`，子串数为 $2$（`a`，`aa`），为偶数；三个相邻字符两两不同，如 `abc`，子串数为 $6$（`a`，`b`，`c`，`ab`，`bc`，`abc`），为偶数。若都不含有，则这个字符串一定为 `abab...` 的形式，子串数为 $2s-1$（其中 $s$ 为字符串长度），为奇数，无解。直接判断是否含有以上两种子串即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		string s;cin>>s;
		int l=s.length();
		if(l==1){
			puts("-1");
			continue;
		}bool ok=false;
		for(int i=1; i<l; i++){
			if(s[i]==s[i-1]){
				cout<<s[i-1]<<s[i]<<"\n";
				ok=1;
				break;
			}
			if(i>=2 && s[i]!=s[i-2] &&  s[i]!=s[i-1] && s[i-1]!=s[i-2]){
				cout<<s[i-2]<<s[i-1]<<s[i]<<"\n";
				ok=1;
				break;
			}
		} 
		if(!ok) puts("-1");
	} 
	return 0;
}

```

---

## 作者：YuYuanPQ (赞：0)

VP 的时候没有马上想出来，后面改了一下思考方向就想到了。

像这种题，我们优先考虑找出合法的，那么分类讨论一下：

- 对于长度为 $1$ 的子串，显然不合法；
- 对于长度为 $2$ 的子串，如果 $2$ 个字符都相等，经过计算得出其函数值为 $2$，那么这是合法的；
- 对于长度为 $3$ 的子串，如果 $3$ 个字符互不相等，经过计算得出其函数值为 $6$，那么这也是合法的；
- 其他情况同理，可视作上 $2$ 种情况的大规模版，不必考虑。

然后就做完了。

## Code
[Link](https://codeforces.com/contest/2039/submission/293830491)

---

## 作者：queenbee (赞：0)

# CF2039B Shohag Loves Strings 题解

## 思路
[题目传送门](https://www.luogu.com.cn/problem/CF2039B)，按照字符串长度枚举一下符合 $f(p)$ 为偶数的字符串。

当长度为 $1$ 时，字符串只有一个非空子串，所以所有长为 $1$ 的子串均不符合条件。

当长度为 $2$ 时，$aa$ 类型的字符串有两个不同的非空子串，$ab$ 类型的字符串有三个不同的非空子串，仅有 $aa$ 类型的符合条件。

当长度为 $3$ 时，$abc$ 类型的字符串有六个不同的非空子串，$aba$ 类型的字符串有五个不同的非空子串，$aaa$、$aab$、$baa$ 等类型中包含 $aa$ 类型的字符串，所以除 $aba$ 类型外均符合条件。

当长度大于 $3$ 时，该字符串一定包含长度为 $2$ 和 $3$ 的子串，只要字符串包含 $aa$ 类型或 $abc$ 类型子串，则该子串为满足条件的子串，可得仅有形如 $abababa…$ 的字符串无满足条件的子串。

形如 $abababa…$ 的字符串不满足的证明。该字符串所有子串均形如 $abababa…$ 。其长度为 $1$ 的不同子串有 $a$ 和 $b$，长度为 $2$ 的不同子串有 $ab$ 和 $ba$。依此类推，所有子串数量均为 $2$，仅有与本身相同的不同子串有 $1$ 个，所以不同子串共有奇数个，不满足条件。

## 程序
```cpp
#include<bits/stdc++.h>	//我爱万能头 
using namespace std;
#define int long long
int t;
int n,flag;
string s; 
signed main(){
	cin>>t;
	while(t--){
		flag=0;
		cin>>s;
		n=s.length();
		s=' '+s;
		for(int i=1;i<=n;i++){
			if(s[i]==s[i-1]){	//形如aa的子串 
				cout<<s[i-1]<<s[i]<<endl;
				flag=1;
				break;
			}
			if(i>2&&s[i]!=s[i-1]&&s[i]!=s[i-2]&&s[i-1]!=s[i-2]){	//形如abc的子串 
				cout<<s[i-2]<<s[i-1]<<s[i]<<endl;
				flag=1;
				break;
			}
		}
		if(!flag){
			puts("-1");
		}
	}
	return 0;	//完结撒花
}
```

---

## 作者：xingshuyan000 (赞：0)

[题目传送门（洛谷入口）：CF2039B](https://www.luogu.com.cn/problem/CF2039B)

[题目传送门（Codeforces 入口）：2039B](https://codeforces.com/problemset/problem/2039/B)

# 题目大意

定义 $f(p)$ 表示的是字符串 $p$ **不同**的非空子串的数量。现在给定你一个字符串 $s$，请你找到 $s$ 的一个子串 $p$，使得 $f(p)$ 是偶数。如果不存在这样的字符串 $p$，请输出 $-1$。

如果存在多个符合条件的字符串 $p$，输出任意一个即可。

# 题目分析

 _首先声明，这篇题解中所有用来举例子的字符串都是我随机想到的，没有针对任何人。_ 

首先，为了方便表述，我们令 $n=|s|$，$|s|$ 就是字符串 $s$ 的长度。

我们很容易就能发现，当 $n = 1$ 时，一定是没有符合题意的字符串的，因为当 $n=1$ 时，字符串的唯一非空子串 $p$ 就是他本身，此时的字符串 $p$ 的非空子串数量只有一个，所以直接输出 $-1$ 就好啦。

对于 $n \ge 2$ 情况，我们怎么处理呢？

根据数学上的一种思想，从特殊到一般，我们可以先找几个特殊情况来看看。

对于 $n=2$ 的情况，我们找几个例子：

- 如果 $p=\texttt{xx}$，$f(p)=2$，符合题意；
- 如果 $p=\texttt{ac}$，$f(p)=3$，不符合题意。

通过上面的例子，我们会发现，当 $n=2$ 时，如果 $p$ 的两个字符是同样的，那么这个字符串的 $f(p)$ 就是符合题意的。其实再去找几个类似的例子也是酱紫的。通过数学归纳法可以证明该结论。

接下来，我们可以再找几个 $n=3$ 的例子：

- 如果 $p=\texttt{tot}$，$f(p)=5$，显然不符合题意；
- 如果 $p=\texttt{sin}$，$f(p)=6$，这是符合题意的；
- 如果 $p=\texttt{ppt}$，$f(p)=5$，不符合题意；
- 如果 $p=\texttt{ooo}$，$f(p)=3$，不符合题意。

好了，我们可以发现，当 $n=3$ 时，如果 $p$ 中的三个字符都不相同，$f(p)$ 是偶数，符合题意；否则，如果只要有任意两个是相同的，$f(p)$ 就是奇数，不符合题意；当然，如果三个字符都相同，同样 $f(p)$ 是奇数，不符合题意。同样可以用数学归纳法来证明。

如果 $n$ 的值继续增大，我们会发现，他其实就是 $n=2$ 或 $n=3$ 这两种情况的扩展，我们总可以把字符串通过切割，化归为 $n=2$ 或 $n=3$ 的情况。

你以为这道题的分析到这里就结束了吗？NO！其实还有一种情况我们没有分析呢。这是一种什么情况呢？请继续往下看。~~（其实我也是看了官方题解才知道还有这种情况的（手动捂脸））~~

如果字符串 $s$ 是形如 $s=\texttt{stststststst}\cdots$ 的字符串，就是你既可以看成是 $2$ 个字符一循环，也可以看成是 $3$ 个字符一循环的这种循环字符串，怎么判断呢？

我们先来拆解这个字符串：

- 对于长度为 $1$ 的子串，一共有两个：`s` 和 `t`；
- 对于长度为 $2$ 的子串，一共有两个：`st` 和 `ts`；
- 对于长度为 $3$ 的子串，一共有两个：`sts` 和 `tst`。

我们观察一下，这一共 $6$ 个不同的子串，没有一个是符合我们前面说的符合题意的子串，所以对于这类的字符串，是没有符合题意的子串的，所以输出 $-1$ 即可。

到这里，这道题的分析才算结束。至于代码吧，应该就不难写了。~~（要不我就不贴代码了吧？嘿嘿）~~

算了，还是给你们贴上吧。

# CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
	string s;
	cin >> s;
	int n = s.length();
	if(n == 1){
		cout << -1 << endl;
		return;
	}
	s = " " + s;
	for(int i = 1; i <= n - 1; i ++)
	{
		if(s[i] == s[i + 1])
		{
			string t = s.substr(i, 2);
			cout << t << endl;
			return;
		}
	}
	for(int i = 1; i <= n - 2; i ++)
	{
		if(s[i] != s[i + 1] && s[i] != s[i + 2] && s[i + 1] != s[i + 2])
		{
			string t = s.substr(i, 3);
			cout << t << endl;
			return;
		}
	}
	cout << -1 << endl;
	return;
}
int main()
{
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Binah_cyc (赞：0)

看见这类题一般的做法一般是手玩一些小样例。

考虑长度为 $2$ 的子串，容易发现只有形如 $\texttt{aa}$ 的字符串符合条件。因此如果这个字符串包含两个相同且相邻的字符，可以直接截取并输出。再考虑长度为 $3$ 的字串，同样枚举所有情况并手玩可以发现只有 $\texttt{abc}$ 的子串符合条件。

然后考虑什么时候无解。发现只有形如 $\texttt{ababab}\dots$ 的不知道答案。

经过简单手玩后，可以发现它本质不同的子串有 $2n-1$ 个，即除原串之外任何长度都有两种，原串有 $1$ 种。这个显然不合法。

然后就做完了，存在合法方案当且仅当存在形如 $\texttt{aa}$ 或 $\texttt{abc}$ 的子串。

```c
// Problem: B. Shohag Loves Strings
// Contest: Codeforces - CodeTON Round 9 (Div. 1 + Div. 2, Rated, Prizes!)
// URL: https://codeforces.com/contest/2039/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
int _;
string s;
bool solve()
{
	for(int i=1;i<s.length();i++) if(s[i]==s[i-1]) return cout<<s[i-1]<<s[i]<<'\n',1;//aa型
	for(int x=0;x+3-1<s.length();x++)
		if(s[x]!=s[x+1]&&s[x]!=s[x+2]&&s[x+1]!=s[x+2])
			return cout<<s[x]<<s[x+1]<<s[x+2]<<'\n',1;//abc型
	return 0;
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>_;
	while(_--)
	{
		cin>>s;
		if(!solve()) cout<<-1<<'\n';
	}
	return 0;
}
```

---

