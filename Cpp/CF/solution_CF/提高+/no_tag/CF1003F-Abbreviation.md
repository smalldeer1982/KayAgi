# Abbreviation

## 题目描述

有 $n$ 个单词（$w_i$），它们通过空格拼接成了一个字符串 $s$。

例如有 $3$ 个单词 `hello`, `oi`和 `world`，它们拼成了字符串`hello oi world`。

定义区间相等 $s[a..b] =s[c..d]$ 当且仅当由 $w_i,a\le i \le b$ 拼接成的字符串与 $w_j, c\le j \le d$ 拼接成的字符串相等。

你可以将相等的若干个区间（至少两个）进行**缩写**操作，具体地，用该区间内所有单词的大写首字母替代单词及空格。例如，`abc a abc a abc` 中，有 3 段相等的 `abc`，可以**缩写**成 `A a A a A`。也有 2 段相等的 `a abc`，可以**缩写**成 `abc AA AA`。

问至多进行 1 次**缩写**操作后，字符串 $s$ 的长度最小是多少？

## 样例 #1

### 输入

```
6
to be or not to be
```

### 输出

```
12
```

## 样例 #2

### 输入

```
10
a ab a a b ab a a b c
```

### 输出

```
13
```

## 样例 #3

### 输入

```
6
aa bb aa aa bb bb
```

### 输出

```
11
```

# 题解

## 作者：zjwwjhy (赞：5)

题目翻译：给你一段文本，你可以将两段以上的相同的子段分别缩成只由子段内单词首字母构成的一个单词，求最后字符串总长度的大小

（比如 **to be or not to be** 能缩为 **TB or not TB**）

（**jjj a jjj b jjj** 能缩为 **J a J b J** ）

由于单词总长度很长，但单词数很少，所以我们可以用map把不同的单词用不同的数字表示，然后用KMP（ $n^2$ 枚举模式串， $n$ 的KMP，总复杂度 $O(n^3)$ ）

最后计算就很直接了

## $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define gc getchar
inline ll read(){
	ll x = 0; char ch = gc(); bool positive = 1;
	for (; !isdigit(ch); ch = gc())	if (ch == '-')	positive = 0;
	for (; isdigit(ch); ch = gc())	x = x * 10 + ch - '0';
	return positive ? x : -x;
}
inline void write(ll a){
    if(a<0){
    	a=-a; putchar('-');
	}
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writeln(ll a){write(a); puts("");}
inline void wri(ll a){write(a); putchar(' ');}
int n;
int s[1010];
int val[1010];
int kmp[1010];
int km[1010];
int cnt;
map<string,int> mp;
string nl;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>nl;
		val[i]=nl.size();
		val[i]+=val[i-1];
		if(mp[nl]==0) mp[nl]=(++cnt);
		s[i]=mp[nl];
	}
	int Ans=val[n]+n-1;
	for(int k=1;k<=n;k++){
		for(int l=k;l<=n;l++){
			int n1=0;
			int j=k-1;
			kmp[k]=k-1;
			for(int i=k+1;i<=l;i++){
				while(j!=k-1 && s[i]!=s[j+1]) j=kmp[j];
				if(s[i]==s[j+1]) j++;
				kmp[i]=j;
			}
			j=k-1;
			for(int i=1;i<=n;i++){
				while(j!=k-1 && s[i]!=s[j+1]) j=kmp[j];
				if(s[i]==s[j+1]) j++;
				if(j==l){
					n1++;
					j=k-1;
				}
			}
			if(n1>=2) Ans=min(Ans,val[n]+n-1-n1*(val[l]-val[k-1]-(l-k+1)+l-k));
		}
	}
	cout<<Ans<<endl;
	return 0;
}
```


---

## 作者：灵茶山艾府 (赞：1)

由于操作的对象是单词，通过一个 map 把每个单词转换成数字 ID，这样题目就变成统计子区间出现次数了。由于 $n$ 很小，可以暴力枚举子区间，查询其在序列中的出现次数，这一操作可以用 KMP 或 Rabin-Karp 来实现。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	var n int
	Fscan(in, &n)
	text := make([]int, n)  // 单词编号数组
	sum := make([]int, n+1) // 单词长度前缀和
	allSum := n - 1         // 总长度
	id := map[string]int{}
	for i := range text {
		var s string
		Fscan(in, &s)
		if _, has := id[s]; !has {
			id[s] = len(id)
		}
		text[i] = id[s]
		sum[i+1] = sum[i] + len(s)
		allSum += len(s)
	}

	// KMP: s 在 text 中的不相交出现次数
	count := func(s []int) (cnt int) {
		n := len(s)
		f := make([]int, n)
		c := 0
		for i := 1; i < n; i++ {
			b := s[i]
			for c > 0 && s[c] != b {
				c = f[c-1]
			}
			if s[c] == b {
				c++
			}
			f[i] = c
		}
		c = 0
		for _, b := range text {
			for c > 0 && s[c] != b {
				c = f[c-1]
			}
			if s[c] == b {
				c++
			}
			if c == n {
				cnt++
				c = 0
			}
		}
		return
	}

	ans := allSum
	for r := 1; r <= n; r++ {
		for l := 0; l < r; l++ {
			if c := count(text[l:r]); c > 1 {
				if v := allSum - c*(sum[r]-sum[l]-1); v < ans {
					ans = v
				}
			}
		}
	}
	Print(ans)
}
```

由于 Golang 的 `strings.Count` 内置 Rabin-Karp，所以也可以这样写：


```go
package main

import (
	"bufio"
	. "fmt"
	"os"
	"strings"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	var n int
	Fscan(in, &n)
	a := make([]rune, n)
	sum := make([]int, n+1)
	allSum := n - 1
	id := map[string]int{}
	for i := range a {
		var s string
		Fscan(in, &s)
		if _, ok := id[s]; !ok {
			id[s] = len(id)
		}
		a[i] = rune(id[s])
		sum[i+1] = sum[i] + len(s)
		allSum += len(s)
	}

	ans := allSum
	text := string(a)
	for r := 1; r <= n; r++ {
		for l := 0; l < r; l++ {
			if c := strings.Count(text, string(a[l:r])); c > 1 {
				if v := allSum - c*(sum[r]-sum[l]-1); v < ans {
					ans = v
				}
			}
		}
	}
	Print(ans)
}
```



---

