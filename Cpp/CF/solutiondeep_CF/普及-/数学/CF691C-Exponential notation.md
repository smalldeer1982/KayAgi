# 题目信息

# Exponential notation

## 题目描述

You are given a positive decimal number $ x $ .

Your task is to convert it to the "simple exponential notation".

Let $ x=a·10^{b} $ , where $ 1<=a&lt;10 $ , then in general case the "simple exponential notation" looks like "aEb". If $ b $ equals to zero, the part "Eb" should be skipped. If $ a $ is an integer, it should be written without decimal point. Also there should not be extra zeroes in $ a $ and $ b $ .

## 样例 #1

### 输入

```
16
```

### 输出

```
1.6E1
```

## 样例 #2

### 输入

```
01.23400
```

### 输出

```
1.234
```

## 样例 #3

### 输入

```
.100
```

### 输出

```
1E-1
```

## 样例 #4

### 输入

```
100.
```

### 输出

```
1E2
```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个正十进制数 \( x \)。

你的任务是将它转换为“简单指数表示法”。

设 \( x = a \cdot 10^{b} \)，其中 \( 1 \leq a < 10 \)，那么在一般情况下，“简单指数表示法”看起来像 "aEb"。如果 \( b \) 等于零，则 "Eb" 部分应被省略。如果 \( a \) 是整数，则应省略小数点。此外，\( a \) 和 \( b \) 中不应有多余的零。

#### 样例 #1

##### 输入

```
16
```

##### 输出

```
1.6E1
```

#### 样例 #2

##### 输入

```
01.23400
```

##### 输出

```
1.234
```

#### 样例 #3

##### 输入

```
.100
```

##### 输出

```
1E-1
```

#### 样例 #4

##### 输入

```
100.
```

##### 输出

```
1E2
```

---

### 题解分析与结论

#### 综合分析与结论

本题的核心是将一个十进制数转换为科学计数法表示，主要难点在于处理前导零、后导零、小数点的位置以及指数的计算。大多数题解都采用了字符串处理的方式，通过遍历字符串找到有效数字的起始和结束位置，然后根据小数点的位置计算指数。

#### 最优关键思路或技巧

1. **字符串处理**：通过遍历字符串去除前导零和后导零，找到有效数字的起始和结束位置。
2. **小数点的处理**：找到小数点的位置，并根据其位置计算指数。
3. **指数计算**：根据小数点的位置和有效数字的起始位置计算指数，注意正负号的处理。
4. **输出格式控制**：根据题目要求，控制输出格式，如省略小数点、指数为零时省略 "E0" 等。

#### 可拓展之处

1. **处理负数**：如果题目扩展到负数，可以在处理前导零时增加对负号的处理。
2. **处理科学计数法输入**：如果输入已经是科学计数法形式，可以进一步优化处理逻辑。

#### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

---

### 高星题解精选

#### 题解1：作者：2023gdgz01 (赞：5)

##### 星级：★★★★★

##### 关键亮点

- **清晰的逻辑**：通过四个步骤明确处理字符串，逻辑清晰。
- **代码简洁**：代码结构清晰，易于理解。
- **优化程度高**：通过一次遍历找到关键位置，减少了不必要的计算。

##### 核心代码

```cpp
int l, r, x, n;
string s;

int main() {
    cin >> s;
    n = s.size();
    l = -1;
    for (register int i = 0; i < n; ++i) {
        if (s[i] != '0' && s[i] != '.') {
            l = i;
            break;
        }
    }
    for (register int i = n - 1; i >= 0; --i) {
        if (s[i] != '0' && s[i] != '.') {
            r = i;
            break;
        }
    }
    x = s.find('.');
    if (x == -1) x = n; //防止 s 为整数。
    if (l == -1) cout << "0";
    else {
        cout << s[l];
        if (l != r) {
            cout << ".";
            for (register int i = l + 1; i <= r; ++i)
                if (s[i] != '.') //防止重复输出小数点。
                    cout << s[i];
        }
        if (l + 1 != x)
            cout << "E" << x - l - (l < x);
    }
    cout << "\n";
    return 0;
}
```

##### 个人心得

- **调试经历**：在处理小数点位置时，最初忽略了整数情况，导致错误，后来通过增加判断条件修复。

---

#### 题解2：作者：Juanzhang (赞：4)

##### 星级：★★★★☆

##### 关键亮点

- **分步处理**：将处理过程分为前缀零、后缀零和小数点的处理，逻辑清晰。
- **代码可读性高**：通过自定义函数 `find` 提高代码可读性。
- **优化程度较高**：通过一次遍历处理前缀和后缀零，减少了不必要的计算。

##### 核心代码

```cpp
int l = 1, r;
char str[maxn];

int find(char ch) {
    for (int i = l; i <= r; i++) {
        if (str[i] == ch) {
            return i;
        }
    }
    return EOF;
}

int main() {
    gets(str + 1);
    r = strlen(str + 1);
    int point = find('.');
    for (; str[l] == 48; l++);
    for (; (~point) && str[r] == 48; r--);
    if (str[r] == '.') {
        r--;
    }
    if (str[l] == '.') {
        int e = -1, pos = l + 1;
        for (; str[pos] == '0'; pos ++, e--);
        putchar(str[pos]);
        if (pos != r) {
            putchar('.');
            for (int i = pos + 1; i <= r; i++)
                putchar(str[i]);
        }
        printf("E%d", e);
        return 0;
    }
    int e = ((~point) ? point - 1 : r) - l;
    int _ = r;
    for (; _ > l && str[_] == 48; _--);
    putchar(str[l]);
    if (e && _ > l) {
        putchar('.');
    }
    for (int i = l + 1; i <= _; i++) {
        if (str[i] != '.' || !e) {
            putchar(str[i]);
        }
    }
    if (e) {
        printf("E%d", e);
    }
    return 0;
}
```

##### 个人心得

- **踩坑教训**：在处理后缀零时，最初没有考虑小数点后的零，导致输出错误，后来通过增加判断条件修复。

---

#### 题解3：作者：__qkj__ (赞：2)

##### 星级：★★★★☆

##### 关键亮点

- **简洁的逻辑**：通过去前导零、后导零和小数点的处理，逻辑简洁。
- **代码简洁**：代码结构清晰，易于理解。
- **优化程度较高**：通过一次遍历处理前缀和后缀零，减少了不必要的计算。

##### 核心代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin>>s;
    int l=0,r=s.size()-1;
    while(s[l]=='0'||s[l]=='.')l++;  //去前导零
    while(s[r]=='0'||s[r]=='.')r--;  //去后导零
    int d=s.find(".");  //找小数点
    if(d==string::npos)d=s.size();
    /*输出 E 以前的部分*/
    cout<<s[l];
    if(l!=r)cout<<'.';
    for(int i=l+1;i<=r;i++)
        if(s[i]!='.')
            cout<<s[i];
    /*输出 E 以后的部分*/
    int now=d-l;
    if(l<d)now--;
    if(now)cout<<'E'<<now;
    return 0;
}
```

##### 个人心得

- **顿悟感想**：在处理小数点位置时，最初忽略了整数情况，导致错误，后来通过增加判断条件修复。

---
处理用时：59.90秒