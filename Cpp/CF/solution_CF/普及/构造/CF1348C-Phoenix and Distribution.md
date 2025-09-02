# Phoenix and Distribution

## 题目描述

Phoenix has a string $ s $ consisting of lowercase Latin letters. He wants to distribute all the letters of his string into $ k $ non-empty strings $ a_1, a_2, \dots, a_k $ such that every letter of $ s $ goes to exactly one of the strings $ a_i $ . The strings $ a_i $ do not need to be substrings of $ s $ . Phoenix can distribute letters of $ s $ and rearrange the letters within each string $ a_i $ however he wants.

For example, if $ s =  $ baba and $ k=2 $ , Phoenix may distribute the letters of his string in many ways, such as:

- ba and ba
- a and abb
- ab and ab
- aa and bb

But these ways are invalid:

- baa and ba
- b and ba
- baba and empty string ( $ a_i $ should be non-empty)

Phoenix wants to distribute the letters of his string $ s $ into $ k $ strings $ a_1, a_2, \dots, a_k $ to minimize the lexicographically maximum string among them, i. e. minimize $ max(a_1, a_2, \dots,       a_k) $ . Help him find the optimal distribution and print the minimal possible value of $ max(a_1, a_2, \dots, a_k) $ .

String $ x $ is lexicographically less than string $ y $ if either $ x $ is a prefix of $ y $ and $ x \ne y $ , or there exists an index $ i $ ( $ 1 \le i \le min(|x|, |y|)) $ such that $ x_i $ &lt; $ y_i $ and for every $ j $ $ (1 \le j       < i) $ $ x_j = y_j $ . Here $ |x| $ denotes the length of the string $ x $ .

## 说明/提示

In the first test case, one optimal solution is to distribute baba into ab and ab.

In the second test case, one optimal solution is to distribute baacb into abbc and a.

In the third test case, one optimal solution is to distribute baacb into ac, ab, and b.

In the fourth test case, one optimal solution is to distribute aaaaa into aa, aa, and a.

In the fifth test case, one optimal solution is to distribute aaxxzz into az, az, x, and x.

In the sixth test case, one optimal solution is to distribute phoenix into ehinopx.

## 样例 #1

### 输入

```
6
4 2
baba
5 2
baacb
5 3
baacb
5 3
aaaaa
6 4
aaxxzz
7 1
phoenix```

### 输出

```
ab
abbc
b
aa
x
ehinopx```

# 题解

## 作者：WYXkk (赞：12)

只要你想到了桶排，这题就变难了 $1145141919810$ 倍。

首先我们应该拿最小的 $k$ 个字符来当每个字符串的开头，这个是没有问题的。

如果已经出现了至少 $2$ 种字符，我们把剩下的部分全部接到某个较小的字符的后面，答案即为第 $k$ 大的字符。

否则，前 $k$ 大字符相同，如果剩下的全部相同，显然我们应该平均分配；

再否则，剩下的不全相同，把它们全部接到某个后面显然最优。

如果你用桶排的话可能要写几十行，但用 sort 几行就写完了。

$\texttt{code:}$

```cpp
rd(n);rd(k);
scanf("%s",s+1);
sort(s+1,s+n+1);
if(s[k]!=s[1]) printf("%c\n",s[k]);
else if(s[n]!=s[k+1]) printf("%c%s\n",s[1],s+k+1);
else {putchar(s[1]);F(i,1,(n-1)/k) putchar(s[k+1]);puts("");}
```

---

## 作者：wsyhb (赞：5)

## 题意简述

给定大小为 $n$ 的字符集合 $s$，字符可能重复，要求将其分成 $k$ 个字符串，使得**字典序最大的字符串字典序最小**，输出这个字典序最大的字符串。

**数据范围**：$1 \le k \le n \le 10^5$

## 分析

先看样例（这个样例是真的良心，包含了所有情况）：

``` cpp
Input
6
4 2
aabb
5 2
aabbc
5 3
aabbc
5 3
aaaaa
6 4
aaxxzz
7 1
ehinopx

Output
ab
abbc
b
aa
x
ehinopx
```

PS：**由于 $s$ 为字符集合（即可以按任意顺序选取），样例中输入的字符串 $s$ 均已按从小到大顺序排列，方便读者阅读。**

第一组数据，采用了“**平均分配**”的策略——每次从字符串开头取出 $k$ 个字符，依次放在 $k$ 个字符串的末尾，直到取空为止。

第二组数据，采用了“**一次性分配**”的策略——一开始从字符串开头取出 $k$ 个字符，作为 $k$ 个字符串的开头，然后将剩余字符依次放在开头字母最小的字符串末尾。

第三组数据，其实同样采用了“**一次性分配**”的策略，但开头字母 `b` 比 `a` 字典序大，最终答案仍为什么都没有添加的 `b`。

第四组数据，采用了“**平均分配**”的策略。

第五组数据，情况类似于第三组数据，略。

第六组数据，$k=1$，没有任何策略。（也可以认为可以使用任何策略）

## 题解

首先，我们可以将前 $k$ 个字符依次作为 $k$ 个字符串的开头，显然这是最优的。

先考虑“**一次性分配**”策略如何实现——

将剩余字符全部放在第 $1$ 个字符串的开头，取第 $1$ 个字符串和第 $k$ 个字符串的 $\max$ 作为当前答案。（亦可分类讨论——若开头字母均相同，选第 $1$ 个字符串；否则选第 $k$ 个字符串）

然后考虑“**平均分配**”策略如何实现——

每次从字符串开头取出 $k$ 个字符，依次放在 $k$ 个字符串的末尾，直到取空为止，用第 $k$ 个字符串更新答案。

**注意：每次读入字符串时，一定要先排序，再处理。**

## 代码

下列代码完全遵循上述题解实现。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
char s[max_n];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,k;
		scanf("%d%d%s",&n,&k,s+1);
		sort(s+1,s+n+1);
		string ans="";
		if(s[1]==s[k])
		{
			ans+=s[1];
			for(int i=k+1;i<=n;++i)
				ans+=s[i];
		}
		else
			ans+=s[k];
		string Max="";
		for(int i=1;i<=k;++i)
		{
			string now="";
			for(int j=i;j<=n;j+=k)
				now+=s[j];
			Max=max(Max,now);
		}
		ans=min(ans,Max);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：huayucaiji (赞：4)

我们先来看题目中的一个条件

>**$a_i$ should be non-empty**

所以无论如何我们都要先把第一位填上。在填数值前要排序就不说了。  
我们把第一位填完后，就要开始像，如何保证最大的最小呢？有的人可能会想到“斗地主发牌”的方式，一个一个发，十分快乐，但是第二组样例就把你的想法击得粉碎了。

```plain
5 2
baacb
```

这组的答案是 $abbc$ 但是“斗地主发牌”算出来的是 $abc$。相差甚远。所以我们要想为什么。

因为说我们要让最大的最小，所以我们尽可能让低位上的字符最小，所以我们要把“斗地主发牌”里放到其他串里的捞回来，放到一个串里，使得这一串使我们最后的答案。因此我们发现这时候“一条龙”的方法最好。

可惜了，第一组样例就把你的 AC 梦击碎。

```plain
4 2
baba
```

答案是 $ab$，可是一条龙算出来的是 $abb$。真是悲剧。那么什么时候要“一条龙”，什么时候要“斗地主发牌”呢？我们~~不难~~发现如果第一位上的字符填完了后面的没填的字符里只有一种字符了，那么我们一条龙时的长度太大，也不行，这时候为了让长度最短，我们还是要“斗地主发牌”。

所以现在两种情况非常分明了。我们也通过了样例，但是很可惜：

![C](http://image.qingtengbc.com/2020/05/02/710b0b8151195.png)

当时我也很崩溃，但是随便造了一组数据，就查出问题所在了。

```plain
6 3
aabbbb
```

答案是 $b$，但是我们输出了 $bb$。因为我们采取了“斗地主发牌”。那为什么这里有是采用“一条龙”呢？因为我们发现如果第一位上已经不相同了，那么后面无论是“斗地主”还是“一条龙”都没有关系了。所以我们让他长度最短，这个程序就没有问题了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10;

int n,k;
string a[maxn];
char s[maxn];

signed main() {
	int t=read();
	while(t--) {
		for(int i=1;i<=k;i++ ) {
			a[i]="";
		}
		n=read();k=read();
		for(int i=1;i<=n;i++) {
			cin>>s[i];
		}
		sort(s,s+n+1);
		int now=1;
		for(int i=1;i<=k;i++) {
			a[i]+=s[now++];
		}
		int sum[30]={};
		int q=0;
		for(int i=now;i<=n;i++) {
			if(!sum[s[i]-'a']) {
				q++;
			}
			sum[s[i]-'a']++;
		}
		if(s[1]!=s[k]) {
			cout<<s[k]<<endl;
		}
	    else {
			if(q==1) {
				int t=1;
				for(;now<=n;now++) {
					a[t]+=s[now];
					t++;
					if(t==k+1) {
						t=1;
					}
				}
			}
			else {
				for(;now<=n;now++) {
					a[1]+=s[now];
				}
			}
			string ans=a[1];
			for(int i=2;i<=k;i++) {
				if(a[i]>ans) {
					ans=a[i];
				}
			}
			cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：2)

考虑最小的字母的个数所带来的不同情况的答案，为了简化，设 最小的字母的个数为 $cnt$：

情况一: 如果 $cnt<k$ ，因为我们要把最小的字母都平均分到每个字符串里，则 $a_k$ 的第一个字符一定和最小的字母不相等，则我们要想尽可能让 $a_k$ 的字母最小，则 $a_k$ 为第 $k$ 小的字母，其余的任意累加到其他字符串即可。则最大的字符串为第 $k$ 小的字母。

如果 $cnt>k$，又分两种情况:

情况二: 如果选了 $k$ 个最小的字母，满足 $a$ 都是非空的，如果剩下 $n-k$ 个字母都是相同的，则我们平均分配这些字母到 $a$。

情况三：剩下的 $n-k$ 个字母不是相同的，则我们把这 $n-k$ 个字母全累加到同一个 $a$ 即可，显然这样子可以使最大的字符串尽量的小。

### [$\mathcal{Code}$](https://codeforces.com/contest/1348/submission/78773297)

---

## 作者：Isshiki_Hugh (赞：1)

题目意思是把一个字符串里的各个字符分配成k组有序字符串，使 k 组有序字符串中字典序最大的一个最小的策略。

于是很显然有这样一个思路，字典序小的字符要尽可能在前面。

很自然的得到，我们的 k 个字符串，必须分别以排序后的字符串中前 k 个字符开头。并且很容易得到这样一个策略，当前 k 个字符不全都一样的时候，只要输出第 k 个字符就行了。因为以 a 开头的字符字典序必然比 b 开头的小。我们只需要把剩下的所有字符都放到 a 后面。

当前 k 个都一样呢？

那我们考虑 k+1 ~ n的字符，如果 k+1 上的和 n 上的都一样，即之后的字符全都一样，显然我们需要均摊这些字符。

如果 k+1 和 n 上的不一样，我们就把剩下的字符按照字典序都塞到 ``ch[k]`` 的后面，因为我们需要让字典序相对大的字符往后靠。仔细思考就会发现这种策略在这种情况下是最优的。
```markdown

# a c c c d
# a
# a

必然比

# a c d
# a c
# a c

优
```

代码：


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#include<set>
#include<vector>
#include<queue>
#include<cstdlib>//rand()
#define rep(i,a,b) for(register long long i = (a);i <= (b);++i)
#define per(i,a,b) for(register long long i = (a);i >= (b);--i)
typedef long long ll;
typedef unsigned long long ull;
using std::string;using std::cin;using std::cout;

int n,k;
char ch[100001];

int main(){
    //std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("in.in", "r", stdin);

    int T;
    cin >> T;
    while(T--){
        cin >> n >> k;
        rep(i,1,n) cin >> ch[i];
        std::sort(ch+1,ch+n+1);
        if(ch[1] != ch[k]) cout << ch[k] << "\n";
        else {
            if(ch[k + 1] == ch[n]){
                cout << ch[k];
                rep(i,1,(n - k) / k + ((n - k) % k == 0 ? 0 : 1)) cout << ch[i+k];
                cout << "\n";
            } else {
                rep(i,k,n) cout << ch[i];
                cout << "\n";
            }
        }

    }   

    return 0;
}

```

---

## 作者：氧少Kevin (赞：0)

# CF1348C - Phoenix and Distribution
- https://www.luogu.com.cn/problem/CF1348C
- 字典序构造

## 题意
给出一个长为 $n$ 的字符串 $s$，和一个正整数 $k$。

现需要把该字符串分为 $k$ 个非空的部分，每个部分的字符也可以以任意的顺序排列。

例如：$k=2$ 时，字符串 “$\tt abbac$” 可以被分成 “$\tt acb$” 和 “$\tt ab$”。

现在，需要让这 $k$ 个字符串中，字典序最大的那个字符串的字典序尽可能小。

求这个字符串。

## 思路

不妨先对 $s$ 升序排序。

题目要求这 $k$ 个字符串非空，不妨先取出 $s$ 的前 $k$ 个字符，依次填入这 $k$ 个字符串。

### 案例 1
例如：$k=3,s=\tt aabbbccc$，有：

|序号|内容|
|--|--|
|1|$\tt a$|
|2|$\tt a$|
|3|$\tt b$|

接下来，剩余的字符串应该全部接到 $1$ 号字符串或者 $2$ 号字符串后面，

|序号|内容|
|--|--|
|1|$\tt abbccc$|
|2|$\tt a$|
|3|$\tt b$|

平均分配给 $1$ 号字符串和 $2$ 号字符串是不优的。因为靠前的字符摆放得越多，字典序越小，此时更优。

### 案例 2
例如：$k=3,s=\tt aaabbbbbb$，有：

|序号|内容|
|--|--|
|1|$\tt a$|
|2|$\tt a$|
|3|$\tt a$|

接下来，剩余的字符串应该平均分配给这三个字符串。

|序号|内容|
|--|--|
|1|$\tt abb$|
|2|$\tt abb$|
|3|$\tt abb$|

全部接到 $1$ 号字符串后面是不优的。因为字符一样，越短的字典序越小。

### 案例 3
例如：$k=3,s=\tt aabccccc$，有：

|序号|内容|
|--|--|
|1|$\tt a$|
|2|$\tt a$|
|3|$\tt b$|

接下来，剩余的字符串应该平均分配给这三个字符串。

|序号|内容|
|--|--|
|1|$\tt accccc$|
|2|$\tt a$|
|3|$\tt b$|

平均分配是不优的。因为首字符不同，首字符靠后的注定字典序较大，所以剩下的字符必须放在最小的字符后面。

### 案例 4
例如：$k=3,s=\tt aaabbbbbb\textcolor{red}{c}$，有：

|序号|内容|
|--|--|
|1|$\tt a$|
|2|$\tt a$|
|3|$\tt a$|

#### 剩余的字符串平均分配给这三个字符串
|序号|内容|
|--|--|
|1|$\tt abb\textcolor{red}{c}$|
|2|$\tt abb$|
|3|$\tt abb$|

#### 剩余的字符串全部接到 $1$ 号字符串后
|序号|内容|
|--|--|
|1|$\tt abbbbbb\textcolor{red}{c}$|
|2|$\tt a$|
|3|$\tt a$|

能看出，平均分配是不优的。因为字符不同，靠前的字符摆放得越多，字典序越小，此时更优。

### 总结

具体实现时，不妨将 “平均分配取最小” 和 “全部接在最小的字符后” 两种方法的结果取字典序较小的输出。

---

## 作者：Blancа (赞：0)

### 题意：
将一个序列分成k份，让字典序最大的那个序列的字典序最小

### 思路：
首先这k个序列一定不为空，所以为了保证字典序最小我们一定是将前k小的字母放在第一位  
考虑后面的怎么放，从样例可以看出来：  
#### 如果前k个相同
那么后面的如果都相同就没有什么字典序大小之分，如果后面的有一个不相同，那么我们尽量让字典序大的靠后，所以不妨将所有的都堆在一起，用样例举个例子：  
5 2  
baacb  
都堆在一起：  
a   
abbc  
如果分开  
ab  
abc  
显然，abbc要比abc小  
#### 如果前k个有不同的
那么将k个以后都堆到第一个字母字典序最小的那个上面就是最优的

##### 代码实现：
```c++
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read () {
	int x = 0, f = 1; char ch = getchar();
	for (;!isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	return x * f;
}
const int maxn = 1e5 + 50;
int t;
int n, k;
char S[maxn];
int a[maxn];
int ans[maxn];
int main () {
	t = read();
	while (t--) {
		n = read(), k = read();
		scanf ("%s", S + 1);
		for (int i = 1; i <= n; i++) a[i] = S[i];
		sort (a + 1, a + 1 + n);
		int top = 0;
		bool judge1 = false;
		for (int i = 1; i < k; i++) {
			if (a[i] != a[i + 1]) judge1 = true;
		}
		if (judge1 == true) {//第二种情况
			ans[++top] = a[k];
		} else {//第一种情况
			bool judge2 = true;
			for (int i = k + 1; i < n; i++) {
				if (a[i] != a[i + 1]) judge2 = false;
			}
			if (judge2 == true) {
				ans [++top] = a[k];
				if (n % k == 0) for (int i = 1; i < n / k; i++) ans[++top] = a[i + k];
				else for (int i = 1; i < n / k + 1; i++) ans[++top] = a[i + k];
			} else {
				for (int i = k; i <= n; i++) ans[++top] = a[i];
			}
		}
		for (int i = 1; i <= top; i++) printf ("%c", (char)ans[i]);
		puts("");
	}
	return 0;
}
```

---

