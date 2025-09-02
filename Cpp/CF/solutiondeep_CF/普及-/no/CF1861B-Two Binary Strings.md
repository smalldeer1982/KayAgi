# 题目信息

# Two Binary Strings

## 题目描述

You are given two strings $ a $ and $ b $ of equal length, consisting of only characters 0 and/or 1; both strings start with character 0 and end with character 1.

You can perform the following operation any number of times (possibly zero):

- choose one of the strings and two equal characters in it; then turn all characters between them into those characters.

Formally, you choose one of these two strings (let the chosen string be $ s $ ), then pick two integers $ l $ and $ r $ such that $ 1 \le l < r \le |s| $ and $ s_l = s_r $ , then replace every character $ s_i $ such that $ l < i < r $ with $ s_l $ .

For example, if the chosen string is 010101, you can transform it into one of the following strings by applying one operation:

- 000101 if you choose $ l = 1 $ and $ r = 3 $ ;
- 000001 if you choose $ l = 1 $ and $ r = 5 $ ;
- 010001 if you choose $ l = 3 $ and $ r = 5 $ ;
- 010111 if you choose $ l = 4 $ and $ r = 6 $ ;
- 011111 if you choose $ l = 2 $ and $ r = 6 $ ;
- 011101 if you choose $ l = 2 $ and $ r = 4 $ .

You have to determine if it's possible to make the given strings equal by applying this operation any number of times.

## 说明/提示

In the first test case, we can perform the following operations:

1. choose the string $ a $ , $ l = 2 $ , $ r = 4 $ ; after this operation, $ a $ is 01110001, $ b $ is 01110101;
2. choose the string $ b $ , $ l = 5 $ , $ r = 7 $ ; after this operation, $ a $ is 01110001, $ b $ is 01110001.

In the second test case, the strings are already equal.

In the third test case, we can perform the following operations:

1. choose the string $ a $ , $ l = 4 $ , $ r = 6 $ ; after this operation, $ a $ is 000111, $ b $ is 010111;
2. choose the string $ b $ , $ l = 1 $ , $ r = 3 $ ; after this operation, $ a $ is 000111, $ b $ is 000111;

In the fourth and fifth test cases, it's impossible to make the given strings equal.

## 样例 #1

### 输入

```
7
01010001
01110101
01001
01001
000101
010111
00001
01111
011
001
001001
011011
010001
011011```

### 输出

```
YES
YES
YES
NO
NO
NO
YES```

# AI分析结果

### 题目翻译
## 两个二进制字符串

### 题目描述
给定两个长度相等的字符串 $a$ 和 $b$，它们仅由字符 $0$ 和/或 $1$ 组成；两个字符串均以字符 $0$ 开头，以字符 $1$ 结尾。

你可以进行任意次数（可能为零次）以下操作：
- 选择其中一个字符串以及该字符串中的两个相同字符；然后将它们之间的所有字符都变为这些字符。

形式上，你选择这两个字符串中的一个（设所选字符串为 $s$），然后选取两个整数 $l$ 和 $r$，使得 $1 \leq l < r \leq |s|$ 且 $s_l = s_r$，接着将所有满足 $l < i < r$ 的字符 $s_i$ 替换为 $s_l$。

例如，如果所选字符串为 $010101$，通过一次操作可以将其转换为以下字符串之一：
- 若选择 $l = 1$ 且 $r = 3$，则变为 $000101$；
- 若选择 $l = 1$ 且 $r = 5$，则变为 $000001$；
- 若选择 $l = 3$ 且 $r = 5$，则变为 $010001$；
- 若选择 $l = 4$ 且 $r = 6$，则变为 $010111$；
- 若选择 $l = 2$ 且 $r = 6$，则变为 $011111$；
- 若选择 $l = 2$ 且 $r = 4$，则变为 $011101$。

你需要判断是否可以通过任意次此操作使给定的两个字符串相等。

### 说明/提示
在第一个测试用例中，我们可以执行以下操作：
1. 选择字符串 $a$，$l = 2$，$r = 4$；操作后，$a$ 为 $01110001$，$b$ 为 $01110101$；
2. 选择字符串 $b$，$l = 5$，$r = 7$；操作后，$a$ 为 $01110001$，$b$ 为 $01110001$。

在第二个测试用例中，两个字符串已经相等。

在第三个测试用例中，我们可以执行以下操作：
1. 选择字符串 $a$，$l = 4$，$r = 6$；操作后，$a$ 为 $000111$，$b$ 为 $010111$；
2. 选择字符串 $b$，$l = 1$，$r = 3$；操作后，$a$ 为 $000111$，$b$ 为 $000111$。

在第四个和第五个测试用例中，无法使给定的两个字符串相等。

### 样例 #1
#### 输入
```
7
01010001
01110101
01001
01001
000101
010111
00001
01111
011
001
001001
011011
010001
011011
```

#### 输出
```
YES
YES
YES
NO
NO
NO
YES
```

### 算法分类
枚举

### 综合分析与结论
这些题解主要围绕判断两个二进制字符串能否通过特定操作变得相等展开。大部分题解通过找规律，发现只要两个字符串中存在相同位置的相邻字符 “01”，就可以将两个字符串都转换为左边全是 “0”，右边全是 “1” 的形式，从而使它们相等。部分题解使用了动态规划的方法，但相对复杂。

### 所选题解
- **作者：kimidonatsu (4星)**
  - **关键亮点**：思路清晰，代码简洁，直接枚举字符串中相邻字符是否为 “01”，时间复杂度低。
  - **核心代码**：
```cpp
void solve() {
    int t;
    std::cin >> t;
    while (t--) {
        std::string a, b;
        std::cin >> a;
        std::cin >> b;
        
        bool flag = false;
        for (int i = 0; i + 1 < a.size(); i++) {
            if (a[i] == b[i] && a[i] == '0' && a[i + 1] == b[i + 1] && a[i + 1] == '1') {
                flag = true;
                break;
            }
        }
        
        if (flag) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
}
```
核心实现思想：遍历两个字符串，检查是否存在相同位置的相邻字符 “01”，若存在则标记为可以转换，输出 “YES”，否则输出 “NO”。

- **作者：_Haoomff_ (4星)**
  - **关键亮点**：思路明确，代码简洁，直接根据规律判断是否存在满足条件的位置。
  - **核心代码**：
```cpp
int t;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    for(string a,b;t--;){
        bool flag=false;
        cin>>a>>b;
        for(int i=0;i<a.size()-1;++i)
            if(a[i]=='0'&&a[i+1]=='1'&&b[i]=='0'&&b[i+1]=='1'){
                cout<<"YES\n";
                flag=true;
                break;
            }
        if(!flag)cout<<"NO\n";
    }
    return 0;
}
```
核心实现思想：对于每组输入的两个字符串，遍历字符串，检查是否存在相同位置的相邻字符 “01”，若存在则输出 “YES”，否则输出 “NO”。

- **作者：Crazyouth (4星)**
  - **关键亮点**：思路清晰，代码简洁，直接判断是否存在满足条件的相邻字符。
  - **核心代码**：
```cpp
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int flag=0;
        string a,b;
        cin>>a>>b;
        for(int i=1;i<a.size();i++)
        {
            if(a[i]=='1'&&b[i]=='1'&&a[i-1]=='0'&&b[i-1]=='0')
            {
                cout<<"YES"<<endl;
                flag=1;
                break;
            }
        }
        if(!flag) cout<<"NO"<<endl;
    }
}
```
核心实现思想：对于每组输入的两个字符串，遍历字符串，检查是否存在相同位置的相邻字符 “01”，若存在则输出 “YES”，否则输出 “NO”。

### 最优关键思路或技巧
通过观察和分析题目中的操作，发现可以将两个字符串都转换为左边全是 “0”，右边全是 “1” 的形式，而判断能否转换的关键在于是否存在相同位置的相邻字符 “01”，利用枚举的方法遍历字符串进行判断。

### 可拓展之处
同类型题目可能会改变操作规则或字符串的条件，例如操作次数有限制、字符串包含更多字符等。类似的算法套路可以应用于其他字符串处理问题，通过找规律和枚举的方法判断是否满足特定条件。

### 推荐题目
- [P1055 [NOIP2008 普及组] ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)
- [P1200 [USACO1.1] 你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)

### 个人心得摘录与总结
- **Xy_top**：没看到 $0$ 开始 $1$ 结尾的条件，写了个 DP 然后还过了，提醒我们做题时要仔细读题，注意题目中的条件限制。
- **One_JuRuo**：最近熬夜打 CF，视力下降，没看到题目里给的第一位和最后一位必定是 $0$ 和 $1$，导致想了半天，强调了读题的重要性，同时要保持良好的作息和状态。

---
处理用时：52.48秒