# 母音を数える (Counting Vowels)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joi2020yo1a/tasks/joi2020_yo1a_b

長さ $ N $ の英小文字からなる文字列 $ S $ が与えられる．$ S $ のうち母音字の個数，つまり `a`，`i`，`u`，`e`，`o` の個数の総和を求めよ．

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 50 $.
- $ S $ は長さ $ N $ の文字列である．
- $ S $ の各文字は英小文字である．

### Sample Explanation 1

母音字は `\_oi\_o\_e\_` の $ 4 $ 個である．

### Sample Explanation 2

母音字は `\_i\_a\_o` の $ 3 $ 個である．

## 样例 #1

### 输入

```
8
joiyosen```

### 输出

```
4```

## 样例 #2

### 输入

```
6
bitaro```

### 输出

```
3```

# 题解

## 作者：Donnyliu01 (赞：2)

## Part 1 题意简述

本题只需要从输入的字符串 `str` 中判断有多少个字符 $\in [a,e,i,o,u]$。

## Part 2 思路分析

我们可以考虑使用 `char` 数组以便于输入~~（也没方便到哪去）~~，然后遍历整个字符数组，如果是元音字母就把答案加上 $1$。

## Part 3 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[105];
int n, ans = 0;
int main() {
    cin >> n >> s;
    for(int i = 0; i < n; i++)  
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') ans++;
    cout << ans << endl;  
    return 0;
}
```

---

## 作者：InversionShadow (赞：0)

## AT_joi2020_yo1a_b 母音を数える (Counting Vowels) 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_joi2020_yo1a_b)

### 题意：

给定一个长度为 $n\ (1 \leq n \leq 100)$ 的字符串，请你求出字符串中有多少个 ```a```，	```e```，```i```，```o```，```u```。

### 思路：

遍历字符串，如果该字符为 ```a```，```e```，```i```，```o```，```u``` 中的一个，就将答案加 $1$。

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

string s;
int n, sum;

int main() {
  cin >> n >> s;
  for (int i = 0; i < n; i++) {    // 遍历字符串
    sum += (s[i] == 'a' || s[i] == 'i' || s[i] == 'u' || s[i] == 'e' || s[i] == 'o' ? 1 : 0);  // 三目运算符，等价于 if 语句，不过容易出错，个人感觉 if 语句更好用
  }
  cout << sum << endl;  // 一定要换行！！！
  return 0;
}

```


---

## 作者：ivyjiao (赞：0)

题意：输入一个正整数 $N$，接着输入一个字符串 $S$，判断 $S$ 中有多少个 `a e i o u`。

思路：$N$ 根本没用，$S$ 只用字符读入就行。

代码实现：

```cpp
#include<iostream>
using namespace std;
char p;
int x;
int main(){
    while(cin>>p) if(p=='a'||p=='e'||p=='i'||p=='o'||p=='u') x++;
    cout<<x<<endl;
}
```


---

## 作者：tbdsh (赞：0)

# 题意
[题目传送门](https://www.luogu.com.cn/problem/AT_joi2020_yo1a_b)

输入一个正整数 $N(1\le N\le50)$，接着输入一个长度为 $N$ 的字符串 $S$。输出这个字符串中 `a`,`e`,`i`,`o`,`u` 的出现总次数。

# 分析
直接输入字符串 $S$，挨个枚举 $S$ 的每一个字符，看是否为 `a`,`e`,`i`,`o`,`u`，是就将答案 $+1$。最后输出即可。**最后需要换行。**

时间复杂度：$O(N)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
string s;
int ans; 
int main(){
  cin >> s >> s;//直接输入两次 s，后一次输入的会覆盖前一次输入的长度 n，这十分的节省空间(bushi)。
  int len = s.size();
  for (int i = 0; i < len; i++){//挨个枚举
    ans += s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'; //运用逻辑表达式的特性，直接判断即可。
  }
  cout << ans << "\n";//输出答案并换行。
  return 0;
}
```

---

