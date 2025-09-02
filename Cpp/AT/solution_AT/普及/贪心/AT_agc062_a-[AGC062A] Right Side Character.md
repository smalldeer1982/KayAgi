# [AGC062A] Right Side Character

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc062/tasks/agc062_a

`A`,`B` のみからなる長さ $ n\ (2\leq\ n) $ の文字列 $ T=T_1T_2\dots\ T_n $ に対し、長さ $ n-1 $ の文字列 $ f(T) $ を以下のように定めます。

- $ T_i={} $`A` が成り立つ $ i\ (1\leq\ i\ \leq\ n-1) $ 全体を $ a_1\ <\ a_2\ <\ \dots\ <\ a_{m} $ とし、 $ T_i={} $`B` が成り立つ $ i\ (1\leq\ i\ \leq\ n-1) $ 全体を $ b_1\ <\ b_2\ <\ \dots\ <\ b_k $ とする。このとき、 $ f(T)=T_{a_1+1}T_{a_2+1}\dots\ T_{a_m+1}T_{b_1+1}T_{b_2+1}\dots\ T_{b_k+1} $ と定める。
 
例えば文字列 $ T={} $`ABBABA` について、$ T_i={} $`A` が成り立つ $ i\ (1\leq\ i\ \leq\ 5) $ 全体は $ i=1,4 $ , $ T_i={} $`B` が成り立つ $ i\ (1\leq\ i\ \leq\ 5) $ 全体は $ i=2,3,5 $ であるため、$ f(T) $ は $ T_{1+1}T_{4+1}T_{2+1}T_{3+1}T_{5+1}={} $`BBBAA` になります。

`A`,`B` のみからなる長さ $ N $ の文字列 $ S $ が与えられます。

$ S $ を $ f(S) $ で置き換えることを $ N-1 $ 回行った後の $ S $ を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10^5 $
- $ 2\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ S $ は `A`,`B` のみからなる長さ $ N $ の文字列
- 入力される数値はすべて整数
- $ 1 $ つの入力に含まれるテストケースについて、 $ N $ の総和は $ 3\ \times\ 10^5 $ 以下
 
### Sample Explanation 1

$ 1 $ つ目のテストケースについて、$ S $ は `AB`$ {}\rightarrow\ {} $`B` と変化します。 $ 2 $ つ目のテストケースについて、$ S $ は `AAA`$ {}\ \rightarrow\ {} $`AA`$ {}\ \rightarrow\ {} $`A` と変化します。 $ 3 $ つ目のテストケースについて、$ S $ は `ABAB`$ {}\rightarrow\ {} $`BBA`$ {}\ \rightarrow\ {} $`BA`$ {}\ \rightarrow\ {} $`A` と変化します。

## 样例 #1

### 输入

```
3
2
AB
3
AAA
4
ABAB```

### 输出

```
B
A
A```

# 题解

## 作者：yllcm (赞：1)

汗流浃背了。

你硬做了 40min，发现没一点前途。打个表可以发现如果末尾是 A 的话答案一定是 A，证明不难：

* 考虑最后一个 B 的位置：如果不存在，那么答案显然是 A，否则，操作后最后一个字符是最后一个 B 后面的字符，显然为 A，归纳得证。

猜想答案是 B 当且仅当一个前缀是 A 而一个后缀是 B（即不存在相邻两个字符为 BA），证明：

* 充分性：随手模拟一下。
* 必要性：假设不成立，那么考虑操作后的结果。假设串中不存在相邻两个字符为 AB，那么 A 在末尾，答案不会是 B。否则，一定可以找到相邻两个字符分别为 AB 和 BA 的两个位置，此时操作后前者的 B 一定在后者的 A 前，也就是说一定存在 BA 子串，归纳得证。

所以只需要判一下是否存在相邻两个字符为 BA 的情况即可。

感觉我不打表完全想不到这个方向啊。

---

## 作者：MurataHimeko (赞：1)

每次位于开头的字母都会被删掉，最后只会剩下末尾的字符。

不妨对末尾字符的种类讨论一下。

1. 末尾字符是 $A$

那么答案一定是 $A$。

如果序列已经没有 $B$，答案显然为 $A$。

如果序列中还有字母 $B$，因为 $B$ 不在末尾，所以最后一个 $B$ 一定会在新序列的末尾加入一个 $A$。所以末尾始终是 $A$。

2. 末尾字符是 $B$

考虑找到序列最后一个 $A$ 的位置，如果这个 $A$ 之前还有 $B$，那么这个 $A$ 在新序列里一定会出现。同时这个 $A$ 又会加入自己之后的 $B$，这个 $B$ 在新序列里一定会在某个 $A$ 之前。这就使得永远存在一个 $A$ 不会被删除，那么最后答案就是 $A$。反之答案为 $B$。



代码：

```cpp
int main () {
    scanf("%d", &T);
    while(T--) {
        scanf("%d %s", &n, s + 1);
        if(s[n] == 'A') {
            puts("A");
            continue;
        }
        pe(i, n) {
            if(s[i] == 'A') {
                bool flag = 0;
                re(j, i) {
                    if(s[j] != 'A') {
                        flag = 1;
                    }
                }
                if(!flag) puts("B");
                else puts("A");
                break;
            }
            if(i == 1) {
                puts("B");
            }
        }
    }
}
```


---

## 作者：lixianyuan (赞：0)

# 题意
[传送门](https://www.luogu.com.cn/problem/AT_agc062_a)\
给出 $T$ 组数据，每组数据给出字符串长度 $n$ 和字符串 $S$。求反复执行 $S\to f(S)$ 直到 $S$ 的长度为 1，求剩下的是什么字符。\
定义 $f(S)$ 为 $S$ 中从左到右所有 `A` 右边的第一个字符组成的字符串加上 $S$ 中从左到右所有 `B` 右边的第一个字符组成的字符串。
# 分析
**答案是 `A`：**\
情况一：如果字符串最后一位为字符 `A`，或者字符串全部由字符 `A` 组成，那么答案一定是字符 `A`。\
证明：如果最后一位是字符 `A`，那么在它的前面必然有一个字符 `B`，字符 `B` 的最末尾就是字符串 $f(s)$ 的最末尾，无论如何答案只能是 `A`，这里可以自行推导。\
如果整个字符串都是字符 `A`，那么答案显然只能是字符 `A`。\
\
情况二：如果以字符 `B` 结尾且字符 `B` 出现在了字符 `A` 的前面，答案一定是字符 `A`。\
证明：因为 $f(s)$ 是字符 `A` 右边的数加字符 `B` 右边的数，所以只要是在字符 `A` 右侧的字符都会被慢慢挪到左边，而因为字符 `A` 在字符 `B` 右边，所以会一直保留到最后，故答案为字符 `A`。\
\
**答案是 `B`**：\
只要答案不是 `A`，那一定是 `B` ~~（别问我为什么）~~，可以自行证明或模拟验证。
# Code
其实代码很简单，主要靠思维。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define endl "\n"
#define F(i,x,y) for(int i=x;i<y;++i)
using namespace std;
const int N=2e5+10;
void work(){
	int n;cin>>n;
	string s;cin>>s;
	if(s[n-1]=='A'){	//如果最后一位是字符'A' 
		cout<<'A';
		return ;
	}
	bool b=1;
	F(i,0,n-1){
		if((s[i]=='B'||s[i+1]=='B')&&b){	//判断是否有字符'B' 
			b=0;
		}
		if(s[i]=='B'&&s[i+1]=='A'){			//判断字符'B'是否出现在了字符'A'左侧 
			cout<<'A';
			return ;
		}
	}
	if(b){
		cout<<'A';
		return ;
	}
	cout<<'B';
}
int main(){
    int _;cin>>_;
    while(_--){			//T组数据 
		work();
		cout<<endl;
	}
    return 0;
}
```

---

## 作者：National_Studying (赞：0)

分为三种情况：

1. 以字母 `A` 结尾：因为最后一个 `B` 不管出现在哪里一定会在 `A` 前面，所以无论怎么删除 `A` 都一定会留在最后。

2. 以字母 `B` 结尾 (非 `A`)： 因为需要保留 `A`，所以要确保 `B` 后面含有 `A` (出现 `BA` ) 来将 `A` 保留到最后，如果出现 `BB` 的情况也不用管，因为 `BB` 在删除后也只剩下一个 `B`，所以后续也会被删除。
 
3. 剩余情况剩余皆为 `B`。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int intt;
#define int long long

intt main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		string s;
		cin >> n >> s;
		if (s[n - 1] == 'A')cout << "A\n";
		else {
			int flag = 0;
			for (int i = 0; i < n; i++) {
				if (s[i] == 'B' && s[i + 1] == 'A') {
					cout << "A\n";
					flag = 1;
					break;
				}
			}
			if (flag == 0)cout << "B\n";
		}
	}
	return 0;
}
```

---

## 作者：fede (赞：0)

# 正文

## 分析

题目要我们判断最后留下的是 `A` 还是 `B`，**而每一次操作过后第一位都会被删除**。

> `A` 是 Alice，`B` 是 Bob，因为男士要让着女士，所以 `A` 更容易活到最后。

我们可以分开讨论。

### A

如果字符串中没有 `B`，答案显然是 `A`。

如果 `A` 在字符串最后一位，因为`B` 不在最后一位，所以排在最后的一个 `B` 的后一位就一定是 `A`，所以根据题意 `A` 仍然在最后一位，答案是 `A`。

如果 `A` 在 `B` 的前面，根据题意这个 `B` 就会把这个 `A` 放到后面，而这个 `A` 就会把后一位放在前面，所以答案是 `A`。

### B

因为答案不是 `A`，那么就是 `B`（好直白）。

## 思路

我们只需要判断 `A` 是不是留到最后的字符。

我们可以用 $O(n)$ 的时间复杂度查找有没有 `B`；   
再用 $O(1)$ 的时间复杂度判断字符串最后一位是不是 `A`；   
最后用 $O(n)$ 的时间复杂度查找有没有 `B` 后一位是 `A` 的情况。

## 代码

时间复杂度 $O(n)$，轻松通过此题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1e6+10;
int n; 
string s;
void solve(){
	cin>>n;
	cin>>s;
	s=' '+s;
	if(s.find('B')==s.npos){
		cout<<'A'<<endl;
		return ;
	}
	if(s[n]=='A'){
		cout<<'A'<<endl;
		return ;
	}
	for(int i=1;i<n;i++){
		if(s[i]=='B'&&s[i+1]=='A'){
			cout<<'A'<<endl;
			return ;
		}
	}
	cout<<'B'<<endl;
	return ;
}
int T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/AT_agc062_a)
## 题意：
给你一个长为 $n \ge 2$ 的只由 ```A``` 和 ```B``` 组成的字符串 $S[1 \cdots n]$，定义 $f(S)$ 是 $S$ 中从左到右所有 ```A``` 右边的第一个字符组成的字符串加上 $S$ 中从左到右所有 ```B``` 右边的第一个字符组成的字符串。由于 $S$ 中除了最右边的字符之外右边都有字符，所以 $f(S)$ 的长度为 $n-1$。

$T$ 组数据，给出 $S$，将 $S$ 反复执行 $S \to f(S)$ 直到 $S$ 长度为 $1$，问你最后的这个字符是 ```A``` 还是 ```B```。
## 思路：
应针对字符串 $S[1 \cdots n]$ 的最后一个字母进行讨论：

1.当 $S_n$ 为 ```A``` 时:

(1) $S$ 中没有 ```B```。答案一定是 ```A```。

(2) $S$ 中有 $B$。我们假设 $B$ 最后一次出现是 $S_i(i<n)$。那么 $S[i+1 \cdots n]$ 全部都是 $A$。又因为 $f(S)$ 的最后一个字符就是这个 $B$ 的右边第一个字符，所以 $f(S)$ 的最后一个字符也是 $A$。

于是当 $S_n$ 为 $A$ 时反复操作到最后，剩下的字符一定是 $A$。

2.当 $S_n$ 为 $B$ 时:

(1) $S$ 中没有 $A$。答案一定是 $B$。

(2) $S$ 中有 $A$。然后考虑 $S_n$ 是 $B$ 时 $f(S)$ 的最后一位是否 $A$ 的情况。

不难发现必要条件是存在 $i$ 使 $S_i = B$ 并且 $S_{i+1} = A$。这是因为，如果不存在 $i$ 使 $S_i = B$ 并且 $S_{i+1} = A$，那么由于有 $A$，所以一定是一段 $A$ 加上一段 $B$。容易知道每次操作后都是一段 $A$ 加上一段 $B$，最后一次操作后一定只剩下 $B$。

然后如果存在 $i$ 使 $S_i = B$ 并且 $S_{i+1} = A$，那么 $S$ 一定是形如 $AAA \cdots BBB \cdots AAA \cdots BBB \cdots B$ 的结构，即从后往前看，是一段 $B$，加上一段 $A$，前面再跟着一段 $B$。然后我们知道，这样的话，$f(S)$ 每操作一次末尾连续的 $B$ 的个数都会减少 $1$。所以在它在长度变为 $1$ 之前一定会转换成一个结尾是 $A$ 的字符串。最后一次操作后一定只剩下 $A$。

所以当 $S_n$ 为 $B$ 时判断是否有 $i$ 符合 $S_i = B$ 并且 $S_{i+1} = A$，如果符合则输出 $A$，否则输出 $B$
## Code:
```cpp
//非洛谷题_AtCoder_AT_agc062_a_[AGC062A] Right Side Character 
#include<bits/stdc++.h>
#pragma GCC/*G++*/ optimize(1)//O1
#pragma GCC/*G++*/ optimize(2)//O2
#pragma GCC/*G++*/ optimize(3)//O3
using namespace std;
long long t=0,n=0;
string s;
bool flag=0;//用于判断有没有一个i符合s[i]='A'和s[i+1]='B' 
int main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);//cin加速
    cin>>t;
    while(t--){
    	cin>>n>>s;
    	flag=0;
    	if(s[n-1]=='A'){//注意字符串开始下标为0 
    		cout<<"A\n";//如果s[n]为'A',答案为'A' 
		}else{//否则判断有没有一个i符合s[i]='B'和s[i+1]='A' 
			for(int i=0;i<=n-2;i++){
				if(s[i]=='B'&&s[i+1]=='A'){
					flag=1;
				}
			}
			if(flag==0){
				cout<<"B\n";
			}else{
				cout<<"A\n";
			}
		}
	}
    return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

记 $n=|s|$，观察到以下两个性质：

若 $s_n=A$，则 $f(s)_{n-1}=A$，进而答案为 $A$。

若 $s_n=B$ 且 $\exists i\in [2,n],s_{i-1}s_{i}=BA$，则 $\exists i\in [2,n],f(s)_{i-1}f(s)_{i}=BA$。

由于最终必然不存在，中间即存在某步使得 $f(s)_{n-1}=A$。

综上，答案为 $B$ 的必要条件 $s_n=B$ 且 $\forall i\in [2,n],s_{i-1}s_{i}\ne BA$。

简单判定即可，时间复杂度为 $O(n)$。

### 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int T;
    cin >> T;
    while (T--) {
    	int N;
		string S;
    	cin >> N >> S;
    	int X = 0;
    	bool check = true;
    	if (S[N - 1] == 'A') 
		  check = false;
    	for (int i =0; i < N - 1; i++)
		  if (S[i] != S[i + 1]) 
		    X++;
        if (X >= 2) 
		  check = false;
    	cout << (check ? 'B' : 'A') << endl;
	}
	return 0;
}
```


---

## 作者：0xyz (赞：0)

#### 一、题目大意

对于一个长为 $n\ge 2$ 的只由 `A` 和 `B` 组成的字符串 $S[1…n]$，定义 $f(S)$ 是 $S$ 中从左到右所有 `A` 右边的第一个字符组成的字符串加上 $S$ 中从左到右所有 `B` 右边的第一个字符组成的字符串。由于 $S$ 中除了最右边的字符之外右边都有字符，所以 $f(S)$ 的长度为 $n-1$。

$T$ 组数据，给出 $S$，将 $S$ 反复执行 $S\to f(S)$ 直到 $S$ 长度为 $1$，问你最后的这个字符是 `A` 还是 `B`。

- $\sum n\le 3\times 10^5$

#### 二、做法

神仙思维题。

首先暴力模拟显然是 $O(n^2)$ 的。

然后下面是正解。
我们针对字符串 $S[1…n]$ 的最后一个字母进行讨论：

$(1)$ 如果 $S_n$ 是 `A`。

1. $S$ 中没有 `B`。答案一定是 `A`。

2. $S$ 中有 `B`。我们假设 `B` 最后一次出现是 $S_i(i<n)$。那么我们就有 $S[i+1…n]$ 全部都是 `A`。又因为 $f(S)$ 的最后一个字符就是这个 `B` 的右边第一个字符，所以 $f(S)$ 的最后一个字符也是 `A`。

于是反复操作到最后，剩下的字符一定是 `A`。

$(2)$ 如果 $S_n$ 是 `B`。

1. $S$ 中没有 `A`。答案一定是 `B`。

2. $S$ 中有 `A`。然后考虑 $S_n$ 是 `B` 时 $f(S)$ 的最后一位是 `A` 的情况。

	不难发现必要条件是存在 $i$ 使 $S_i=$`B` 并且 $S_{i+1}=$`A`。这是因为，如果不存在 $i$ 使 $S_i=$`B` 并且 $S_{i+1}=$`A`，那么由于有 `A`，所以一定是一段 `A` 加上一段 `B`。容易知道每次操作后都是一段 `A` 加上一段 `B`，最后一次操作后一定只剩下 `B`。

   然后如果存在 $i$ 使 $S_i=$`B` 并且 $S_{i+1}=$`A`，那么 $S$ 一定是形如 `…BA…AB…B` 的结构，即从后往前看，是一段 `B`，加上一段 `A`，前面再跟着一个 `B`。然后我们知道，这样的话，$f(S)$ 是 `…AB…B`。并且每操作一次末尾连续的 `B` 的个数都会减少 $1$。所以在它在长度变为 $1$ 之前一定会转换成一个结尾是 `A` 的字符串。最后一次操作后一定只剩下 `A`。
   
然后我们依照这些讨论写出代码即可。

#### 三、代码

注意代码里的 $S$ 下标从 0 开始。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
ll t,n,fl;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>s;fl=0;
		for(ll i=1;i<n;i++)
			if(s[i-1]=='B'&&s[i]=='A')fl=1;
		cout<<(fl?'A':s[n-1])<<'\n';
	}
	return 0;
}
```

---

