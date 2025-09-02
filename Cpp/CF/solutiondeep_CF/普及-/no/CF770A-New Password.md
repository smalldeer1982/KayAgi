# 题目信息

# New Password

## 题目描述

Innokentiy decides to change the password in the social net "Contact!", but he is too lazy to invent a new password by himself. That is why he needs your help.

Innokentiy decides that new password should satisfy the following conditions:

- the length of the password must be equal to $ n $ ,
- the password should consist only of lowercase Latin letters,
- the number of distinct symbols in the password must be equal to $ k $ ,
- any two consecutive symbols in the password must be distinct.

Your task is to help Innokentiy and to invent a new password which will satisfy all given conditions.

## 说明/提示

In the first test there is one of the appropriate new passwords — java, because its length is equal to $ 4 $ and $ 3 $ distinct lowercase letters a, j and v are used in it.

In the second test there is one of the appropriate new passwords — python, because its length is equal to $ 6 $ and it consists of $ 6 $ distinct lowercase letters.

In the third test there is one of the appropriate new passwords — phphp, because its length is equal to $ 5 $ and $ 2 $ distinct lowercase letters p and h are used in it.

Pay attention the condition that no two identical symbols are consecutive is correct for all appropriate passwords in tests.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
java
```

## 样例 #2

### 输入

```
6 6
```

### 输出

```
python
```

## 样例 #3

### 输入

```
5 2
```

### 输出

```
phphp
```

# AI分析结果

### 题目翻译
# 新密码

## 题目描述
伊诺肯季决定更改社交网络“联系人！”中的密码，但他懒得自己想一个新密码。这就是他需要你帮助的原因。

伊诺肯季决定新密码应满足以下条件：
- 密码的长度必须等于 $n$。
- 密码只能由小写拉丁字母组成。
- 密码中不同符号的数量必须等于 $k$。
- 密码中任意两个连续的符号必须不同。

你的任务是帮助伊诺肯季，发明一个满足所有给定条件的新密码。

## 说明/提示
在第一个测试中，“java” 是合适的新密码之一，因为它的长度等于 $4$，并且使用了 $3$ 个不同的小写字母 $a$、$j$ 和 $v$。

在第二个测试中，“python” 是合适的新密码之一，因为它的长度等于 $6$，并且由 $6$ 个不同的小写字母组成。

在第三个测试中，“phphp” 是合适的新密码之一，因为它的长度等于 $5$，并且使用了 $2$ 个不同的小写字母 $p$ 和 $h$。

请注意，对于测试中的所有合适密码，没有两个相同符号连续的条件都是正确的。

## 样例 #1
### 输入
```
4 3
```
### 输出
```
java
```

## 样例 #2
### 输入
```
6 6
```
### 输出
```
python
```

## 样例 #3
### 输入
```
5 2
```
### 输出
```
phphp
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路基本一致，都是通过构造的方法生成满足条件的密码。要点在于利用循环和取模运算，以保证生成的密码长度为 $n$，包含 $k$ 个不同的小写字母，且相邻字符不同。不同题解的差异主要在于实现方式，有的打表存储 26 个字母，有的直接利用 ASCII 码特性。难点在于理解如何通过取模运算来满足不同字符和相邻字符不同的条件。

### 所选题解
- **作者：Aw顿顿 (赞：2)，4星**
  - **关键亮点**：思路清晰，详细阐述了如何根据题目要求构造密码，代码简洁，且强调了测样例不过但提交能过的原因（有 Special Judge）。
  - **个人心得**：强调此题有 Special Judge，测样例不过没事，提交可以过，并给出了提交通过的记录链接。
- **作者：锦瑟，华年 (赞：1)，4星**
  - **关键亮点**：对题目条件进行了详细总结，并清晰说明了如何满足不同字符和相邻字符不同的条件，代码简单易懂。
- **作者：Sora1336 (赞：1)，4星**
  - **关键亮点**：指出此解法可能是最快解法，使用 `putchar` 优化输出速度，核心代码简洁明了。

### 重点代码
```cpp
// Aw顿顿
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main(){
    cin>>n>>k;
    while(n--){
        cout<<(char)('a'+n%k);
    }
    cout<<endl;
    return 0;
}

// 锦瑟，华年
#include<stdio.h>
using namespace std;
int main(){
    int n,k,i;
    scanf("%d%d",&n,&k);
    for(i=0;i<n;i++)printf("%c",'a'+i%k);
    return 0;
}

// Sora1336
#include <iostream>
using namespace std;
int main(){
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++) putchar('a'+i%k);
} 
```
**核心实现思想**：通过循环 $n$ 次，每次输出字符 `'a'` 加上当前循环次数对 $k$ 取模的结果，利用取模运算保证有 $k$ 个不同的字符，且相邻字符不同。

### 关键思路或技巧
利用取模运算和 ASCII 码特性，通过循环生成满足条件的密码，代码实现简单高效。

### 拓展思路
同类型题可能会有更多复杂的条件限制，如增加字符范围、对字符出现次数有要求等，但基本思路都是通过构造的方法满足条件。类似算法套路可用于解决一些字符串构造、序列构造的问题。

### 推荐题目
- [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)
- [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)

---
处理用时：29.52秒