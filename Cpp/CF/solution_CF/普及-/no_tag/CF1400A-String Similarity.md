# String Similarity

## 题目描述

A binary string is a string where each character is either 0 or 1. Two binary strings $ a $ and $ b $ of equal length are similar, if they have the same character in some position (there exists an integer $ i $ such that $ a_i = b_i $ ). For example:

- 10010 and 01111 are similar (they have the same character in position $ 4 $ );
- 10010 and 11111 are similar;
- 111 and 111 are similar;
- 0110 and 1001 are not similar.

You are given an integer $ n $ and a binary string $ s $ consisting of $ 2n-1 $ characters. Let's denote $ s[l..r] $ as the contiguous substring of $ s $ starting with $ l $ -th character and ending with $ r $ -th character (in other words, $ s[l..r] = s_l s_{l + 1} s_{l + 2} \dots s_r $ ).

You have to construct a binary string $ w $ of length $ n $ which is similar to all of the following strings: $ s[1..n] $ , $ s[2..n+1] $ , $ s[3..n+2] $ , ..., $ s[n..2n-1] $ .

## 说明/提示

The explanation of the sample case (equal characters in equal positions are bold):

The first test case:

- $ \mathbf{1} $ is similar to $ s[1..1] = \mathbf{1} $ .

The second test case:

- $ \mathbf{000} $ is similar to $ s[1..3] =         \mathbf{000} $ ;
- $ \mathbf{000} $ is similar to $ s[2..4] =         \mathbf{000} $ ;
- $ \mathbf{000} $ is similar to $ s[3..5] =         \mathbf{000} $ .

The third test case:

- $ \mathbf{1}0\mathbf{10} $ is similar to $ s[1..4] =         \mathbf{1}1\mathbf{10} $ ;
- $ \mathbf{1}01\mathbf{0} $ is similar to $ s[2..5] =         \mathbf{1}10\mathbf{0} $ ;
- $ \mathbf{10}1\mathbf{0} $ is similar to $ s[3..6] =         \mathbf{10}0\mathbf{0} $ ;
- $ 1\mathbf{0}1\mathbf{0} $ is similar to $ s[4..7] =         0\mathbf{0}0\mathbf{0} $ .

The fourth test case:

- $ 0\mathbf{0} $ is similar to $ s[1..2] =         1\mathbf{0} $ ;
- $ \mathbf{0}0 $ is similar to $ s[2..3] = \mathbf{0}1 $ .

## 样例 #1

### 输入

```
4
1
1
3
00000
4
1110000
2
101```

### 输出

```
1
000
1010
00```

# 题解

## 作者：Error_Eric (赞：3)

### 思路

题目大意：对于字符串 $a$ 和 $b$，如果字符串 $|a|=|b|$ 并且存在 $i$ 使得 $a_i=b_i$ 那么这两个字符串相似。($a\sim b$)

对于一个字符串 $S$ ,$S[l...r]$ 表示由 $S_l,S_{l+1},...,S_{r-1},S_r$ 构成的字符串。

现在给定一个长度为 $2\times n-1$ 的01串$s$，求一个长度为 $n$ 的字符串满足 $n\sim s[1...n],n\sim s[2...n+1],n\sim s[3...n+2]...,n\sim s[n...2n-1]$

---

显然输出的长度必须为x。

显然$s[1...n],s[2...n+1],s[3...n+2]...,s[n...2n-1]$中都包括 $s_n$。

而 $s_n$ 在$s[1...n],s[2...n+1],s[3...n+2]...,s[n...2n-1]$
中的位置分别是$n,n-1,n-2,...,1$。

所以只要输出 $n$ 个 $s_n$ 即可。


### code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int t,n;string s;
int main(){
	scanf("%d",&t);
	while(t--){
		cin>>n>>s;
		for(int i=1;i<=n;i++)putchar(s[n-1]);
		putchar(10);
	}
} 
```

---

## 作者：STDquantum (赞：2)

可以发现，小串 $s^\prime$ 一共匹配了 $n$ 次，而 $s^\prime$ 长度刚好为 $n$。

也就是说，我们可以让每次匹配相似的时候都匹配 $s^\prime$ 的不同位（因为只需匹配一位，也就是其他位根本不用管，单独考虑就行）。

比如当 $n=5,s=\mathbf{101011010}$ 时，如下面形式匹配：

第一次匹配，不去考虑其他位，在 $s^\prime$ 第一位填上 $s$ 的第一位，这时已经可以保证 $s^\prime$ 和 $s$ 的第一个子串相似了。

| $s^\prime$ | 1    |      |      |      |      |      |      |      |      |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $s$        | 1    | 0    | 1    | 0    | 1    | 1    | 0    | 1    | 0    |

第二次匹配：这时 $s^\prime$ 的第一位已经没有用了（因为只需匹配一位），我们将它向右移动一位匹配第二个 $s$ 的子串，并将 $s^\prime$ 的第二位填上对应的 $s$ 的这一位。

| $s^\prime$ |      | 1    | 1    |      |      |      |      |      |      |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $s$        | 1    | 0    | 1    | 0    | 1    | 1    | 0    | 1    | 0    |

第三、四、五次匹配同理，向右移动一位，再填上一位。

| $s^\prime$ |      |      | 1    | 1    | 1    |      |      |      |      |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $s$        | 1    | 0    | 1    | 0    | 1    | 1    | 0    | 1    | 0    |

| $s^\prime$ |      |      |      | 1    | 1    | 1    | 0    |      |      |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $s$        | 1    | 0    | 1    | 0    | 1    | 1    | 0    | 1    | 0    |

| $s^\prime$ |      |      |      |      | 1    | 1    | 1    | 0    | 0    |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $s$        | 1    | 0    | 1    | 0    | 1    | 1    | 0    | 1    | 0    |

这时就已经移动到了最后， 我们也得到了 $s^\prime=\mathbf{11100}$。

可以检验一下，这么填出来的答案能保证和 $s$ 的每个长度为 $n$ 的子串相似。

这样就已经可以做出答案了，但是我们还可以做得更快。

可以发现每次填上对应位的时候，对应的那个 $s$ 上的位数一定是奇数（从 $1$ 开始计算），所以直接在读入时输出奇数位或者读入完输出奇数位即可。

主要部分（`ch`是 $s$ 串）：

```cpp
scanf("%d", &t);
for (int i = 1; i <= t; ++i) {
    scanf("%d%s", &n, ch + 1);
    for (int j = 1; j <= 2 * n - 1; ++j) {
        if (j % 2 == 1) cout << ch[j]; // 奇数位就输出
    }
    puts(""); // 换行
}
```



---

## 作者：ZigZagKmp (赞：2)

本文同步发表于[我的cnblog](https://www.cnblogs.com/ZigZagKmp/p/13563143.html)

本场题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1400-edu-94-solution)

## 题意简述
定义两个字符串$a,b$是相似的，当且仅当这两个字符串长度相同，且存在$i\in [1,|a|]$，使得$a_i=b_i$。

给定一个长度为$2n-1$的01字符串$S$，你需要构造出一个长度为$n$的字符串，使得它与$S$的每一个长度为$n$的子串都是相似的。

题目保证有解。

多测，$1\le n\le 50$。
### 算法考察
构造
## 算法分析
因为题目保证有解，因此我们可以如下构造。

构造$a_1,a_2,\cdots,a_n$=$s_1,s_2,\cdots,s_n$。

然后向后枚举$s$的每一个长度为$n$的子串，如果对应位置$a_i\neq s_j$，则$a_i$任意。

因为保证有解，所以不会出现最后所有的$a$都任意的情况。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
int s[105],a[105];
signed main(){
	int CasT;
	read(CasT);
	while(CasT--){
		read(n);
		for(int i=1;i<2*n;i++)scanf("%1d",&s[i]);
		for(int i=1;i<=n;i++)a[i]=s[i];//初始化
		for(int i=2;i<=n;i++){
			for(int j=i;j<=n+i-1;j++){
				if(a[j-i+1]!=s[j])a[j-i+1]=-1;//任意标记
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i]==-1)a[i]=0;//任意取
		}
		for(int i=1;i<=n;i++)printf("%d",a[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：引领天下 (赞：0)

考虑构造。

首先使 $w_1=s_1$，则已经满足了 $s[1,n]$ 与 $w$ 相似。

那么如何使 $s[2,n+1]$ 与 $w$ 相似呢？

使 $w_2=s_3$ 即可。

$s[3,n+2]$ 呢？

$w_3=s_5$。

至此，我们已经发现了一个规律：

**$w$ 串中每增加一个位置，$s$ 串中都会对应地增加两个位置。**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    register int t,n;
    string s;
    cin>>t;
    while(t--){
        cin>>n>>s;
        for(int i=0;i<n;i++)cout<<s[i<<1];//由于string是0下标，所以可以直接*2输出。
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：chenyuhe (赞：0)

对于每组数据，只需输出一个相似字符串即可。

每组数据共有$n$个按题目要求的子串，我们要输出的字符串，只需满足第一位和第一个子串的第一位，第二位和第二个子串的第二位，$...$第$n$位和第$n$个子串的第$n$位相同即可，而且能确保做到（$n$位对$n$个）

下面只需观察第$i$个子串的第$i$位，容易发现，那位正好是原字符串的第$2i-1$位，所以只需输出原字符串的第$1,3,5,...2n-1$位即可

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
string a;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		cin>>a;
		for(int i=0;i<a.size();i=i+2)cout<<a[i];
		puts("");
	}
	return 0;
}
```


---

## 作者：luosw (赞：0)

### 题意简述

- 定义两个长度都为 $w$ 的二进制串 $m,n$ **相似**的条件为 $\exists i\in [1,w]$ 使得 $m_i=n_i$ 。这里「相似」记作 $\sim$。

- 现在给定一个 $n\in \mathbb{Z}$ 于一个长度为 $2n-1$ 的二进制串 $s$，求出一个长度为 $n$ 的二进制串 $ans$，使得对于 $s$ 中长度为 $n$ 的所有连接字串构成的集合 $A$ 中，$\forall A_i \sim ans$。如果有多个答案，输出其中一个。

### 题目分析


#### 正解：$O(n)$

这道题有很多的乱搞做法。我们现在先来分析一下正解。

要使 $ans$ 满足 $\forall A_i \sim ans$，不难发现最简单的方法是将 $s$ 中的 $\dfrac{1}{2}$ 的元素存入 $ans$，这样能确保结果成立。

重要代码：

```cpp
for (int i = 0; i < int(S.size()); i += 2)
        ans += S[i];
```

这个算法的时间复杂度为 $O(n)$，由于 $n$ 取值范围小，所以这应该是这道题的正解。并且这道题不会有 $O(1)$ 算法。

下面给出一些其他方法。

#### 更容易理解的 $O(n^2)$ 算法

要使$ans$ 满足 $\forall A_i \sim ans$，我们可以对于 $A_i$，将它的第 $i$ 项存入 $ans$ 中。则首先需要循环求出 $A$，还需要循环依次存入 $ans$ 串中，每次就输出 $ans_i$ 即可。

重要代码：

```cpp
 for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n; j++) {
                temp += a[i + j];
            }
            putchar(temp[i]);
            temp = "";
        }
        putchar('\n');
```

整体时间复杂度 $O(n^2)$。

#### 最乱搞的做法

直接获得一个随机的二进制串 $q$，然后反复验证其相似性。验证相似性需要的时间复杂度为 $O(n^2)$，而随机生成的二进制串 $q$ 不满足条件的概率是 $\dfrac{1}{2^n}$，设重试 $cnt$ 次，故最终的时间复杂度为 $O(cnt\times n^2)$ 由于 $cnt,n$ 都很小，所以该解法仍然可以通过此题。

重要代码：

```cpp
 while (true) {
        for (int i = 0; i < N; i++)
            ans[i] = char('0' + rng() % 2);
 
        bool valid = true;
 
        for (int start = 0; start < N; start++) {
            bool match = false;
 
            for (int i = 0; i < N; i++)
                match = match || ans[i] == S[start + i];
 
            valid = valid && match;
        }
 
        if (valid)
            break;
    }
 
    cout << ans << '\n';
}
```

### 总结

这道题作为 A 题还是挺有思维难度的。

---

