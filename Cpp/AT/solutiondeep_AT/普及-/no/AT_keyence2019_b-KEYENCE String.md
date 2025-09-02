# 题目信息

# KEYENCE String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/keyence2019/tasks/keyence2019_b

連続した部分文字列 (空でも良い) を $ 1 $ 度だけ取り除くことで `keyence` に変換することができる文字列をキーエンス型文字列と呼ぶことにします．

英小文字のみから成る文字列 $ S $ が与えられるので，$ S $ がキーエンス型文字列かどうか判定してください．

## 说明/提示

### 制約

- $ S $ の長さは $ 7 $ 以上 $ 100 $ 以下
- $ S $ は英小文字のみから成る

### Sample Explanation 1

`keyence` とは `key of science` の略です．

## 样例 #1

### 输入

```
keyofscience```

### 输出

```
YES```

## 样例 #2

### 输入

```
mpyszsbznf```

### 输出

```
NO```

## 样例 #3

### 输入

```
ashlfyha```

### 输出

```
NO```

## 样例 #4

### 输入

```
keyence```

### 输出

```
YES```

# AI分析结果

### 题目内容重写

#### 题目描述

通过一次移除一个连续的子字符串（可以是空字符串）后，可以将字符串转换为 `keyence` 的字符串称为 **キーエンス型字符串**。

给定一个仅由小写字母组成的字符串 $ S $，请判断 $ S $ 是否为 **キーエンス型字符串**。

#### 说明/提示

##### 约束

- $ S $ 的长度在 $ 7 $ 到 $ 100 $ 之间。
- $ S $ 仅由小写字母组成。

##### 样例解释 1

`keyence` 是 `key of science` 的缩写。

##### 样例 #1

###### 输入

```
keyofscience
```

###### 输出

```
YES
```

##### 样例 #2

###### 输入

```
mpyszsbznf
```

###### 输出

```
NO
```

##### 样例 #3

###### 输入

```
ashlfyha
```

###### 输出

```
NO
```

##### 样例 #4

###### 输入

```
keyence
```

###### 输出

```
YES
```

### 算法分类

**字符串**

### 综合分析与结论

本题的核心在于判断字符串 $ S $ 是否可以通过移除一个连续的子字符串（包括空字符串）后变为 `keyence`。由于 `keyence` 的长度为 7，且 $ S $ 的长度至少为 7，因此我们可以通过遍历 $ S $ 的所有可能的子字符串移除方式，来检查是否能够得到 `keyence`。

### 通用建议与扩展思路

1. **遍历所有可能的子字符串移除方式**：由于 $ S $ 的长度在 7 到 100 之间，直接遍历所有可能的子字符串移除方式是可行的。我们可以通过双重循环来实现这一点：外层循环遍历子字符串的起始位置，内层循环遍历子字符串的结束位置。

2. **字符串匹配**：在每次移除子字符串后，检查剩余的字符串是否与 `keyence` 完全匹配。如果匹配，则返回 `YES`，否则继续遍历。

3. **优化思路**：由于 `keyence` 的长度固定为 7，我们可以通过计算 $ S $ 的长度与 `keyence` 的长度差来优化遍历范围，减少不必要的计算。

### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
3. [P3371 【模板】AC自动机](https://www.luogu.com.cn/problem/P3371)

### 关键代码实现

```cpp
#include <iostream>
#include <string>
using namespace std;

bool isKeyenceString(const string& s) {
    string target = "keyence";
    int n = s.length();
    int m = target.length();
    for (int i = 0; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            string temp = s.substr(0, i) + s.substr(j);
            if (temp == target) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    string s;
    cin >> s;
    if (isKeyenceString(s)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
```

### 核心实现思想

1. **双重循环遍历所有可能的子字符串移除方式**：外层循环遍历子字符串的起始位置，内层循环遍历子字符串的结束位置。
2. **字符串拼接与匹配**：在每次移除子字符串后，通过 `substr` 函数拼接剩余的字符串，并与 `keyence` 进行比较。
3. **返回结果**：如果找到匹配的字符串，则返回 `YES`，否则返回 `NO`。

---
处理用时：25.68秒