# [AGC031A] Colorful Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc031/tasks/agc031_a

長さ $ N $ の文字列 $ S $ が与えられます。 $ S $ の部分列であって、すべて異なる文字からなるものの数を $ 10^9+7 $ で割った余りを答えてください。文字列として同一でも、異なる位置から取り出された部分列は区別して数えることとします。

ただし、文字列の部分列とは、文字列から文字をいくつか **正の個数** 取り出し、もとの文字列から順序を変えずにつなげたものを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100000 $
- $ S $ は英小文字からなる
- $ |S|=N $

### Sample Explanation 1

$ S $ 自体がすべて異なる文字からなるので、すべての部分列が条件を満たします。

### Sample Explanation 2

`b`, `a` ($ 2 $ 通り), `ba` ($ 2 $ 通り) の合計 $ 5 $ 通りが答えとなります。`baa` などは`a`が $ 2 $ 回現れるため当てはまらないことに注意してください。

## 样例 #1

### 输入

```
4
abcd```

### 输出

```
15```

## 样例 #2

### 输入

```
3
baa```

### 输出

```
5```

## 样例 #3

### 输入

```
5
abcab```

### 输出

```
17```

# 题解

## 作者：FFTotoro (赞：3)

此题的大致思路：根据加法原理，若这个字符出现 $x$ 次，那么有 $x+1$ 种选择方案（不选或者选第 $1$ 个、第 $2$ 个……第 $x$ 个）；又根据乘法原理，将每个字符的选择方案乘起来就是最终答案。

此题解与其他题解的不同之处在于，还运用了 STL 里的 `std::count` 函数；在这里给大家介绍一下此函数的用法。

这个函数和 sort 函数类似，原型如下：

```count (_InputIterator __first, _InputIterator __last, const _Tp& __value)```

具体意思就是，第一个参数给出要查找的容器的开始的迭代器，第二个参数给出要查找的容器的结束的迭代器，第三个参数给出要统计的值。例如，我们要统计一个 `std::vector` $a$ 中 $720$ 出现的个数，并赋值给变量 $c$，就可以这么写：

```int c=count(a.begin(),a.end(),720);```

放代码：

```cpp
#include<iostream>
#include<algorithm> // count 函数存于 algorithm 头文件中
#define int long long // 本题数据要开 long long
using namespace std;
const int mod=1e9+7;
main(){
  int n,c=1; string s; cin>>n>>s;
  for(char i='a';i<='z';i++)
    (c*=count(s.begin(),s.end(),i)+1)%=mod; // 乘起来并取模
  cout<<c-1<<endl; // 减 1 是为了去掉空串
  return 0;
}
```

---

## 作者：Yukinoshita_Yukino (赞：1)

一句话题意：给定一个长度为 $n$ 的字符串，求其中不含相同字母子串的个数。

答案子串的长度是一定小于等于原字符串中字符种类数的。

先看一眼样例字符串:	```abcd```

我们可以画一个图感受一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/cthevrgr.png)

上图四个方格代表可以放字符的地方（也可以不放）。方格下面的数代表此方格的情况数。在这个样例中有两种情况，放或者不放，所以情况数是2。

更普遍的，如果有 $n$ 个相同字母，则有 $n+1$ 个情况数。根据小学学过的乘法原理，把以上数连乘起来就好。

PS:**十年OI一场空，不开longlong见祖宗**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int t[30];
char str[100010];
const int mod=1e9+7;
signed main()
{
	cin>>n;
	cin>>str;
	for(int i=0;i<26;i++) 
		t[i]=1;
	for(int i=0;i<n;i++) 
		t[str[i]-'a']++;
	int ans=1;
	for(int i=0;i<26;i++) 
	{
		ans*=t[i];
		ans%=mod;
	}
	cout<<ans-1;
	return 0;
}


```

---

## 作者：TLEWA (赞：0)

一个标准的加法定理和乘法定理的题。

根据加法原理，一个字符出现 $n$ 次，那么有 $n+1$ 中选这个字符的方法，根据乘法原理，将每个字符的选择方案乘起来就得到了答案。

代码如下：
```cpp
#include<iostream>
using namespace std;

long long mod=1000000007,n,ans=1; //要开ll捏 
string s;
int arr[300];

int main() {
	cin >> n >> s;
	for(auto c:s) ++arr[c];
	for(int c='a';c<='z';++c) ans=(ans*(arr[c]+1))%mod;
	cout << (ans+1000000006)%mod << endl;
	return 0;
} 
```

解释一下 `(ans+1000000006)%mod`，如果 $1000000007$ 不是质数，那么有可能直接 $-1$ 就会变成 $-1$，显然不对。


---

## 作者：icefake (赞：0)

# AT4691 [AGC031A] Colorful Subsequence


虽然这道题是 $AGC$ 中的，但作为$A$题其实和 $ABC$ 的 $B$ 题难度没区别。。。

### 关于题意
~~什么时候我的英语水平才能超越二年级 $QAQ$~~

**英语真的很重要！！！**

简单的说，就是——
给定字符串 $S$，求其无重复字符子序列个数

注：不同位置上的同种字符不算同一个字符

> 比如：在字符串 $abbc$ 中，其无重复字符子序列有 $a$, $b$, $b$, $c$, $ab$, $ab$, $ac$, $bc$, $bc$, $abc$ 和 $abc$，共11个，所以 $ans$ 为11

### 分析
由题意得。。。/xk
我们只需要先统计一下 $a$ ~ $z$ 每个字符的出现次数
然后将这些次数全部加上1，最后求积就行了

至于为什么。。。
相信大家用小学二年级学过的组合知识就能想出来啦

还有一件事——
貌似空集不算在 $ans$ 里面。。。
别问我为啥，反正样例里面没有算/kk

### 展示一下我的代码
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 310;//众所周知，ASCII应该不会大于310 
const int mod = 1e9 + 7;
int n, tem, ans = 1;
int cnt[maxn] = {0};
string s;

signed main()
{
	cin>>n;
	cin>>s;
	for(int i = 0; i < s.length(); i ++) {
		tem = s[i];
		cnt[tem] ++;
	}
	for(int i = 'a'; i <= 'z'; i ++) {
		ans *= cnt[i] + 1;
		ans %= mod;
	}
	cout<<ans - 1;//减去空集 
	return 0;
}
```






---

