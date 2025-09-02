# 题目信息

# Personalized Cup

## 题目描述

At many competitions that have a word «cup» in its official name the winner is presented with an actual cup. This time the organizers of one unusual programming competition have decided to please the winner even more and to add a nameplate to the cup with the handle of the winner.

The nameplate is to be rectangular and the text on it will be printed as a table of several rows and columns. Having some measurements done, the organizers have found out that the number $ a $ of rows cannot be greater than $ 5 $ while the number $ b $ of columns cannot exceed $ 20 $ . Every cell of the table will contain either an asterisk («\*») or a letter of user's handle.

Furthermore, the organizers want the rows of the table to be uniform, which means that the number of asterisks used in different rows should differ by at most one (i.e. you can't have two asterisks in the first row and none in the second). The main goal, however, is to obtain the winner's handle precisely when reading the table from top to bottom and from left to right in every row (skipping asterisks).

The organizers want for the nameplate to have as few rows as possible and among all valid tables with the minimum number of rows they want to choose the one that has the minimum number of columns.

The winner is not yet determined so your task is to write a program that, given a certain handle, generates the necessary table.

## 样例 #1

### 输入

```
tourist
```

### 输出

```
1 7
tourist
```

## 样例 #2

### 输入

```
MyNameIsLifeIAmForeverByYourSideMyNameIsLife
```

### 输出

```
3 15
MyNameIsLifeIAm
ForeverByYourSi
deMyNameIsL*ife
```

# AI分析结果



# 题目中文翻译

# Personalized Cup

## 题目描述

在许多名称包含"杯"的竞赛中，获胜者会被授予真实的奖杯。这次，某次特殊编程竞赛的主办方决定为奖杯加装名牌，并刻上获胜者的昵称。

名牌需要呈现为若干行若干列的矩形表格，每行最多5行，每列最多20列。表格中的每个单元格可以是星号（*）或用户昵称的字符。要求不同行的星号数量相差不超过1，且按行优先顺序读取非星号字符时，必须得到完整的昵称。

需要找到行数最少（行数相同时列数最少）的合法表格方案。

## 样例 #1

### 输入

```
tourist
```

### 输出

```
1 7
tourist
```

## 样例 #2

### 输入

```
MyNameIsLifeIAmForeverByYourSideMyNameIsLife
```

### 输出

```
3 15
MyNameIsLifeIAm
ForeverByYourSi
deMyNameIsL*ife
```

**算法分类**：构造

---

# 题解分析与结论

## 关键思路总结

1. **行数计算**：最小行数由 `a = min(ceil(len/20), 5)` 确定，确保每列不超过20
2. **列数计算**：`b = ceil(len/a)` 确保足够容纳字符
3. **星号分配**：需要补 `t = a*b - len` 个星号，均匀分配到前t行，每行补1个
4. **输出策略**：前t行每行输出b-1个字符+1个星号，剩余行输出完整b个字符

## 推荐题解

### 题解作者：Drind（4星）
**核心亮点**：
- 数学推导行数和列数
- 清晰划分带星号行与普通行
- 代码简洁高效（时间复杂度O(n)）
```cpp
int main() {
    string s; cin >> s;
    int n = s.size();
    int l = (n-1)/20 + 1; // 计算最小行数
    int k = n/l + (n%l != 0); // 列数
    int t = l - n%l; // 需要补星号的行数
    
    cout << l << " " << k << endl;
    int now = 0;
    // 输出带星号的行
    for(int i=0; i<t; i++) {
        cout << s.substr(now, k-1) << "*\n";
        now += k-1;
    }
    // 输出普通行
    for(int i=t; i<l; i++) {
        cout << s.substr(now, k) << "\n";
        now += k;
    }
}
```

### 题解作者：sqrt404（4星）
**核心亮点**：
- 动态计算星号数量
- 使用循环统一处理输出
- 包含模运算优化逻辑
```cpp
int main() {
    string s; cin >> s;
    int len = s.size();
    int line = len/20 + bool(len%20);
    int weight = (len + line - 1)/line; // 列数计算
    
    int star = line*weight - len;
    int cnt = 0;
    cout << line << " " << weight << endl;
    for(int i=0; i<line; i++) {
        int output = weight - (star>0 ? 1 : 0);
        cout << s.substr(cnt, output);
        cnt += output;
        if(star-- > 0) cout << "*";
        cout << endl;
    }
}
```

---

# 拓展与练习

**同类题目推荐**：
1. [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098) - 字符串构造与格式化输出
2. [P1498 南蛮图腾](https://www.luogu.com.cn/problem/P1498) - 分形图案构造
3. [P1321 单词覆盖还原](https://www.luogu.com.cn/problem/P1321) - 字符串模式匹配与构造

**调试心得**：
- 注意边界情况：当长度刚好是20的倍数时，行数计算容易出错
- 星号分配必须均匀，测试案例需覆盖各种余数情况
- 字符串截取时索引计算容易越界，建议使用substr函数

---
处理用时：108.82秒