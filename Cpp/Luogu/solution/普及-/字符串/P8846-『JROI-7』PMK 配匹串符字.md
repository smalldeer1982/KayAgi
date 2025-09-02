# 『JROI-7』PMK 配匹串符字

## 题目背景

> 限制很宽泛，构造也就很憨批。

——command_block 《考前小贴士》

## 题目描述

对于一个字符串 $S$，记 $|S|$ 表示 $S$ 的长度，记 $S_i$ 表示 $S$ 的第 $i$ 个字符，记 $S_{l,r}$ 表示 $S_l,S_{l+1},...,S_r$ 组成的字符串。定义两个字符串相等，当且仅当他们长度相等，且每个位置的字符相同。

对于一个字符串 $S$ 和一个正整数 $i\le |S|$，若 $k$ 是满足 $k<i$ 且 $S_{1,k}=S_{i-k+1,i}$ 的最大的正整数，则 $next_i=k$。特别的，若不存在 $k$ 满足条件，则 $next_i=0$。

请你构造一个由小写字母组成的字符串 $S$，满足 $|S|=n$，且对于所有正整数 $i\le |S|$，$next_i$ 之和最小。

## 说明/提示

### 数据规模
本题采用捆绑测试。

对于 $50\%$ 的数据，$n\le 26$。

对于 $100\%$ 的数据，$1\le n\le 10^5$。

## 样例 #1

### 输入

```
5```

### 输出

```
abcde```

# 题解

## 作者：2021sunzishan (赞：10)

## 题目大意：
构造一个长度为 $n$ 的，从第二项起，每一项都与第一项不同的字符串。

### 没啥好说的，上代码！

代码：
```c
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    cin>>n;
    cout<<'a';
    for(int i=2;i<=n;i++)
        cout<<'b';
    return 0;
}
```
完结~

---

## 作者：pxb0801 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P8846)

--------------

## 1.分析：

这是一道很明显的构造题，无需任何算法。

题目说了，如果 $next_i$ 不为 $0$，那么就必须有 $S_{1,k}=S_{i-k+1,i}$，也就是说至少 $S_1=S_{i-k+1}$。所以只要满足 $S_1$ 与其它所有字符都不相同就可以使得 $next_i$ 之和最小，等于 $0$。

---------------
## 2.AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	cin>>n;
	printf("a");//第一个输出与其它所有字符都不相同
	for(int i=2;i<=n;i++){
		printf("b");
	}
	return 0;
}
```

---

## 作者：_Spectator_ (赞：2)


[可能更好的食用体验](/blog/523641/P8846) $|$ 
[题目传送门](/problem/P8846) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{主要思路}}$

根据题意不难发现，$S_{1,k}$ 总是包含第一个字符，而 $S_{i-k+1,i}$ 总是不包含第一个字符。因此，只要使 $S$ 的第一个字符在后面都不会再次出现，就能使 $next_i$ 永远为 $0$，和自然就是最小的。 

一种构造方法：第一个字符为 `a` ，其余字符均为 `b`。

------------

${\large\color{#00CD00}\text{完整代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main()
{
	cin>>n;
	cout<<'a';
	for(int i=1;i<n;i++)cout<<'b';
	return 0;
}
```

---

---

## 作者：Neflibata_xy (赞：1)

## 题意简述
构造一个由小写字母组成的字符串 $S$,使得
- $|S|=n$
- $S_{1,k}=S_{k,2k-1}\ (2k-1\le n)$的情况尽可能少，最小为$\ 0$

## 题目分析
显然，只要使$S$的第一个字母与其后的字母都不相同，$next_i\ $就始终为$\ 0$，即$\ abbbbbbbbb...$（答案不唯一）
### $\mathtt{Code:}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    scanf("%d", &n);
    printf("a");
    for (int i = 1; i < n; i++)
        printf("b");//“构造也就很憨批”（误
    return 0;
}
```
###### （第一篇题解，求过）

---

