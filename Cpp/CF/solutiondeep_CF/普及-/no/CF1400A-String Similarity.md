# 题目信息

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

# AI分析结果

### 题目内容
# 字符串相似度

## 题目描述
二进制字符串是指每个字符要么是0要么是1的字符串。两个长度相等的二进制字符串 $a$ 和 $b$ 是相似的，如果它们在某个位置上有相同的字符（存在一个整数 $i$ 使得 $a_i = b_i$ ）。例如：
 - 10010 和 01111 是相似的（它们在位置4上有相同的字符）；
 - 10010 和 11111 是相似的；
 - 111 和 111 是相似的；
 - 0110 和 1001 不相似。

给定一个整数 $n$ 和一个由 $2n - 1$ 个字符组成的二进制字符串 $s$ 。我们用 $s[l..r]$ 表示 $s$ 从第 $l$ 个字符开始到第 $r$ 个字符结束的连续子串（换句话说，$s[l..r] = s_l s_{l + 1} s_{l + 2} \dots s_r$ ）。

你必须构造一个长度为 $n$ 的二进制字符串 $w$ ，它与以下所有字符串都相似：$s[1..n]$ ，$s[2..n + 1]$ ，$s[3..n + 2]$ ，... ，$s[n..2n - 1]$ 。

## 说明/提示
样例情况的解释（相同位置上的相同字符加粗显示）：
 - 第一个测试用例：
    - $\mathbf{1}$ 与 $s[1..1] = \mathbf{1}$ 相似。
 - 第二个测试用例：
    - $\mathbf{000}$ 与 $s[1..3] =         \mathbf{000}$ 相似；
    - $\mathbf{000}$ 与 $s[2..4] =         \mathbf{000}$ 相似；
    - $\mathbf{000}$ 与 $s[3..5] =         \mathbf{000}$ 相似。
 - 第三个测试用例：
    - $\mathbf{1}0\mathbf{10}$ 与 $s[1..4] =         \mathbf{1}1\mathbf{10}$ 相似；
    - $\mathbf{1}01\mathbf{0}$ 与 $s[2..5] =         \mathbf{1}10\mathbf{0}$ 相似；
    - $\mathbf{10}1\mathbf{0}$ 与 $s[3..6] =         \mathbf{10}0\mathbf{0}$ 相似；
    - $1\mathbf{0}1\mathbf{0}$ 与 $s[4..7] =         0\mathbf{0}0\mathbf{0}$ 相似。
 - 第四个测试用例：
    - $0\mathbf{0}$ 与 $s[1..2] =         1\mathbf{0}$ 相似；
    - $\mathbf{0}0$ 与 $s[2..3] = \mathbf{0}1$ 相似。

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
101
```
### 输出
```
1
000
1010
00
```

### 算法分类
构造

### 综合分析与结论
这几道题解均围绕如何构造出符合要求的长度为 $n$ 的字符串展开。
 - **思路方面**：多数题解发现了构造字符串与原字符串特定位置字符的关系。如Error_Eric题解发现所有子串都包含 $s_n$ ，所以构造的字符串全为 $s_n$ ；STDquantum、引领天下、chenyuhe、luosw的正解思路类似，均是通过观察得出构造字符串的第 $i$ 位与原字符串第 $2i - 1$ 位相关；ZigZagKmp则是先初始化构造字符串与原字符串前 $n$ 位相同，再根据后续子串调整。
 - **算法要点**：主要是利用原字符串的子串与构造字符串的相似关系，找到对应位置字符的规律来进行构造。时间复杂度上，除luosw提到的乱搞做法外，其他均为 $O(n)$ 。
 - **解决难点**：难点在于发现构造字符串各位置字符与原字符串特定位置字符的对应规律，从而满足与所有子串相似的条件。

### 所选的题解
 - **作者：Error_Eric (5星)**
    - **关键亮点**：思路简洁清晰，通过观察子串都包含 $s_n$ 这一特点，直接得出构造的字符串由 $n$ 个 $s_n$ 组成，代码实现也极为简洁。
    - **重点代码**：
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
核心实现思想：读入数据后，循环 $n$ 次输出 $s$ 字符串的第 $n$ 个字符（数组下标为 $n - 1$ ）。
 - **作者：STDquantum (4星)**
    - **关键亮点**：通过具体示例展示匹配过程，思路较清晰，并且进一步发现每次匹配对应 $s$ 上的位数是奇数这一规律，优化了代码。
    - **重点代码**：
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
核心实现思想：读入数据后，遍历原字符串，若字符位置为奇数则输出。
 - **作者：引领天下 (4星)**
    - **关键亮点**：从构造第一个字符满足相似条件出发，逐步推导后续字符与原字符串的关系，规律总结清晰，代码简洁明了。
    - **重点代码**：
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
核心实现思想：读入数据后，利用字符串下标从0开始的特点，通过循环输出原字符串下标为偶数（即 $2i$ ）的字符。

### 最优关键思路或技巧
观察原字符串子串与构造字符串的相似关系，找到构造字符串各位置字符与原字符串特定位置字符的对应规律，这是解决本题的关键。如Error_Eric通过发现子串共有的字符位置，直接确定构造字符串；其他部分题解通过分析匹配过程，找到构造字符串位置与原字符串奇数位置字符的对应关系。

### 拓展
同类型题通常围绕字符串的特定相似性、匹配关系等条件，要求构造出新的字符串。类似算法套路是仔细分析给定字符串的子串特征，以及目标字符串需满足的条件，寻找两者之间字符位置或数值上的对应规律来进行构造。

### 洛谷推荐题目
 - [P1019 单词接龙](https://www.luogu.com.cn/problem/P1019)：通过寻找单词之间的接龙关系构造最长的单词链，考察字符串的拼接与构造。
 - [P1503 鬼子进村](https://www.luogu.com.cn/problem/P1503)：根据给定条件构造出符合要求的路径，涉及字符串的处理与构造思路。
 - [P1990 覆盖墙壁](https://www.luogu.com.cn/problem/P1990)：利用递推和构造的思想，用不同规格的瓷砖覆盖墙壁，与本题构造字符串思路有相通之处。 

---
处理用时：60.88秒