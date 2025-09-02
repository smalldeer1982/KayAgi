# Santa Claus and a Palindrome

## 题目描述

Santa Claus likes palindromes very much. There was his birthday recently. $ k $ of his friends came to him to congratulate him, and each of them presented to him a string $ s_{i} $ having the same length $ n $ . We denote the beauty of the $ i $ -th string by $ a_{i} $ . It can happen that $ a_{i} $ is negative — that means that Santa doesn't find this string beautiful at all.

Santa Claus is crazy about palindromes. He is thinking about the following question: what is the maximum possible total beauty of a palindrome which can be obtained by concatenating some (possibly all) of the strings he has? Each present can be used at most once. Note that all strings have the same length $ n $ .

Recall that a palindrome is a string that doesn't change after one reverses it.

Since the empty string is a palindrome too, the answer can't be negative. Even if all $ a_{i} $ 's are negative, Santa can obtain the empty string.

## 说明/提示

In the first example Santa can obtain abbaaaxyxaaabba by concatenating strings $ 5 $ , $ 2 $ , $ 7 $ , $ 6 $ and $ 3 $ (in this order).

## 样例 #1

### 输入

```
7 3
abb 2
aaa -3
bba -1
zyz -4
abb 5
aaa 7
xyx 4
```

### 输出

```
12
```

## 样例 #2

### 输入

```
3 1
a 1
a 2
a 3
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2 5
abcde 10000
abcde 10000
```

### 输出

```
0
```

# 题解

## 作者：ifffer_2137 (赞：0)

### 题意
给定 $k$ 个长度均为 $n$ 的字符串，每个字符串有权值 $a_i$（可能为负），要求从中选取若干个拼接为一个回文串，使总权值最大。
### 分析
因为是回文，先按照选取字符串个数的奇偶性分讨。

如果是奇数，那么中间那个串必然回文，然后剩下两边就变成偶数的情况。对于偶数，回文对应位置的两个串应当是互为反串的。所以我们把正串和反串归为一种，一起考虑。

有一个朴素的想法是对于同一种串优先选取最大的，只要贡献为正就一直加，正确性显然。

于是我们单独拿出所有已经回文的串，每一个开个大根堆，简单算一下贡献。因为奇数个的只能有一种串，所以先累计偶数个的答案，再加上偶数变为奇数增量最大的那一个。

对于不回文的串，直接对正串反串各开一个大根堆，一对一对往后选正的即可，直接累加。

然后就做完了，时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e5+5;
int n,m,tot,ans,mx;
string s,ss;
int c[maxn];
map<string,int> id;
priority_queue<int,vector<int>,less<int> >v[maxn][2];
vector<int> tmp;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		cin>>s;ss=s;reverse(ss.begin(),ss.end());
		int x=read();
		if(s==ss){
			if(!id[s]) id[s]=++tot;
			c[id[s]]=0;
			v[id[s]][0].push(x);
		}else{
			int op=0;
			if(ss<s) swap(s,ss),op=1;
			if(!id[s]) id[s]=++tot;
			c[id[s]]=1;
			v[id[s]][op].push(x);
		}
	}
	for(int i=1;i<=tot;i++){
		if(!c[i]){
			int k0=0,k1=0;
			tmp.clear();
			while(!v[i][0].empty()){
				tmp.eb(v[i][0].top());
				v[i][0].pop();
			}
			for(int j=0;j<tmp.size()-1;j+=2){
				if(tmp[j]+tmp[j+1]>0) k0+=tmp[j]+tmp[j+1];
				else break;
			}
			if(tmp[0]>0) k1+=tmp[0];
			for(int j=1;j<tmp.size()-1;j+=2){
				if(tmp[j]+tmp[j+1]>0) k1+=tmp[j]+tmp[j+1];
				else break;
			}
			ans+=k0;
			mx=max(mx,k1-k0);
		}else{
			while(!v[i][0].empty()&&!v[i][1].empty()){
				int x=v[i][0].top(),y=v[i][1].top();
				v[i][0].pop(),v[i][1].pop();
				if(x+y>0) ans+=x+y;
				else break;
			}
		}
	}
	cout<<ans+mx<<"\n";
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：0)

思路：贪心。

将字符串分为回文和非回文两类。

记拼接后的字符串为 $S$。对于非回文的字符串 $s$，应取 $s$ 与其翻转串 $\textit{rev}(s)$，拼接在 $S$ 的左右两侧；对于回文串应放置于 $S$ 的中间。

例如 $S=\texttt{abc}+\texttt{xyx}+\texttt{cba}$

在读入时将字符串对应的美丽值按回文和非回文分到两个哈希表中，然后按如下贪心策略计算答案：

对于非回文的字符串 $s$，应取 $s$ 与其翻转串 $\textit{rev}(s)$ 对应的美丽值数组，排序后，每次取两个数组的最大值累加入答案，直至其中一个数组为空或两个最大值之和不为正。

对于回文的字符串类似，取其美丽值数组，排序后，每次取数组的两个最大值累加入答案，直至数组少于两个元素或两个最大值之和不为正。

最后还有一步：我们可以往 $S$ 的正中间插入一个美丽值为正的回文串，或者删除一个美丽值为负的回文串，这可以在遍历时统计出来，取能插入的最大值或者能删除的最小值，然后更新答案。

AC 代码（Golang）:

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
	"sort"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	var k, n, v, mx, ans int
	var s string
	np := map[string][]int{} // 非回文
	p := map[string][]int{}  // 回文
o:
	for Fscan(in, &k, &n); k > 0; k-- {
		Fscan(in, &s, &v)
		for i := 0; i < n/2; i++ {
			if s[i] != s[n-1-i] {
				np[s] = append(np[s], -v) // 方便排序统计
				continue o
			}
		}
		p[s] = append(p[s], v)
	}

	for s, a := range np {
		t := []byte(s)
		for i := 0; i < n/2; i++ {
			t[i], t[n-1-i] = t[n-1-i], t[i]
		}
		rev := string(t)
		b := np[rev]
		sort.Ints(a)
		sort.Ints(b)
		for i := 0; i < len(a) && i < len(b) && a[i]+b[i] < 0; i++ {
			ans -= a[i] + b[i]
		}
		delete(np, rev)
	}
	for _, a := range p {
		sort.Ints(a)
		i := len(a) - 1
		for ; i > 0 && a[i]+a[i-1] > 0; i -= 2 {
			ans += a[i] + a[i-1]
			if -a[i-1] > mx {
				mx = -a[i-1]
			}
		}
		if i >= 0 && a[i] > mx {
			mx = a[i]
		}
	}
	Print(ans + mx)
}
```


---

