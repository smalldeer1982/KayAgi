# 题目信息

# Center Alignment

## 题目描述

几乎每一个文本编辑器都有文字居中对齐的功能，因此Berland的著名文本编辑器Textpad的开发者们希望在产品的第四次更新中加入此功能。

您的任务是尽快编写一个文本居中对齐的原型程序，祝您好运!

## 样例 #1

### 输入

```
This  is

Codeforces
Beta
Round
5
```

### 输出

```
************
* This  is *
*          *
*Codeforces*
*   Beta   *
*  Round   *
*     5    *
************
```

## 样例 #2

### 输入

```
welcome to the
Codeforces
Beta
Round 5

and
good luck
```

### 输出

```
****************
*welcome to the*
*  Codeforces  *
*     Beta     *
*   Round 5    *
*              *
*      and     *
*  good luck   *
****************
```

# AI分析结果

### 题目内容重写
几乎每一个文本编辑器都有文字居中对齐的功能，因此Berland的著名文本编辑器Textpad的开发者们希望在产品的第四次更新中加入此功能。

您的任务是尽快编写一个文本居中对齐的原型程序，祝您好运!

### 样例 #1

#### 输入
```
This  is

Codeforces
Beta
Round
5
```

#### 输出
```
************
* This  is *
*          *
*Codeforces*
*   Beta   *
*  Round   *
*     5    *
************
```

### 样例 #2

#### 输入
```
welcome to the
Codeforces
Beta
Round 5

and
good luck
```

#### 输出
```
****************
*welcome to the*
*  Codeforces  *
*     Beta     *
*   Round 5    *
*              *
*      and     *
*  good luck   *
****************
```

---

### 题解综合分析与结论

本题的核心难点在于处理文本居中对齐时的微调问题，特别是当文本长度与最大长度差为奇数时，需要交替进行左偏和右偏。各题解大多采用模拟的方法，通过计算每行文本的左右空格数来实现居中对齐。以下是几条较为优秀的题解：

---

### 所选题解

#### 题解1：作者：耶耶小朋友 (赞：7)
- **星级**：★★★★☆
- **关键亮点**：代码结构清晰，处理空行和微调逻辑明确，使用了`string`类的构造函数生成边框和空格，代码可读性高。
- **核心实现思想**：通过`gets`读取每行文本，计算最大长度，使用`string`生成边框和空格，处理微调时通过布尔变量`bt`控制左右偏。
- **代码片段**：
```cpp
string a(mx+2,'*');
cout << a << endl;
bool bt = false;
for (int i = 0;i <= cnt;i++) {
    cout << '*';
    if (len[i] == 0) {
        for (int j = 1;j <= mx;j++) cout << " ";
    } else {
        int mid;
        if ((mx - len[i]) % 2 == 1) {
            if (bt == false) {
                mid = (mx - len[i] - 1) / 2;
                for (int j = 1;j <= mid;j++)  cout << " ";
                cout << str[i];
                for (int j = 1;j <= mid+1;j++)  cout << " ";
                bt = true;
            } else {
                mid = (mx - len[i] + 1) / 2;
                for (int j = 1;j <= mid;j++) cout << " ";
                cout << str[i];
                for (int j = 1;j <= mid-1;j++) cout << " ";
                bt = false;
            }
        } else {
            mid = (mx - len[i]) / 2;
            for (int j = 1;j <= mid;j++) cout << " ";
            cout << str[i];
            for (int j = 1;j <= mid;j++) cout << " ";
        }
    }
    cout << "*\n";
}
cout << a << endl;
```

#### 题解2：作者：SIXIANG32 (赞：4)
- **星级**：★★★★☆
- **关键亮点**：使用`getline`读取文本，处理空行和微调逻辑清晰，代码简洁，易于理解。
- **核心实现思想**：通过`getline`读取每行文本，计算最大长度，处理微调时通过`cnt`变量控制左右偏。
- **代码片段**：
```cpp
string ud(maxn+2,'*');
cout << ud << endl;
for (int p = 1; p <= tot; p++) {
    if (str[p].size() == 0) {
        string s(maxn, ' ');
        cout << "*" << s << "*" << endl;
    } else if ((maxn - str[p].size()) % 2 == 0) {
        string s((maxn - str[p].size()) / 2, ' ');
        cout << "*" << s << str[p] << s << "*" << endl;
    } else {
        string s((maxn - str[p].size()) / 2, ' ');
        cnt++;
        if (cnt % 2)
            cout << "*" << s << str[p] << s << " *" << endl;
        else
            cout << "* " << s << str[p] << s << "*" << endl;
    }
}
cout << ud << endl;
```

#### 题解3：作者：outis_crypt (赞：4)
- **星级**：★★★★☆
- **关键亮点**：使用`string`构造函数生成边框和空格，处理微调时通过`left`和`right`变量控制左右偏，代码逻辑清晰。
- **核心实现思想**：通过`getline`读取每行文本，计算最大长度，处理微调时通过`left`和`right`变量控制左右偏。
- **代码片段**：
```cpp
string e(max_length + 2, '*');
cout << e << endl;
int right = 0, left = 1;
for (int j = 0; j < i; j++) {
    if (s[j].length() == 0) {
        string back(max_length, ' ');
        cout << '*' << back << '*' << endl;
    } else if (s[j].length() < max_length && s[j].length()) {
        int t = max_length - s[j].length();
        if (t % 2 == 0) {
            string back(t / 2, ' ');
            cout << '*' << back << s[j] << back << '*' << endl;
        } else {
            if (left) {
                string back((t - 1) / 2, ' ');
                left = 0, right = 1;
                cout << "*" << back << s[j] << back << " *" << endl;
            } else if (right) {
                string back((t - 1) / 2, ' ');
                right = 0; left = 1;
                cout << "* " << back << s[j] << back << "*" << endl;
            }
        }
    } else if (s[j].length() == max_length) {
        cout << "*" << s[j] << "*" << endl;
    }
}
cout << e << endl;
```

---

### 最优关键思路或技巧
1. **使用`string`构造函数生成边框和空格**：通过`string(length, char)`可以快速生成指定长度的字符串，简化了代码。
2. **微调逻辑控制**：通过布尔变量或计数器控制左右偏，确保微调逻辑的交替执行。
3. **处理空行**：在读取和处理文本时，需要特别处理空行，避免程序出错。

---

### 可拓展之处
1. **文本对齐的其他形式**：可以拓展到左对齐、右对齐等其他对齐方式。
2. **多语言支持**：处理不同语言的文本对齐问题，特别是涉及字符宽度的情况。
3. **图形界面实现**：将文本对齐功能集成到图形界面编辑器中，提升用户体验。

---

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 考察模拟和边界处理。
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042) - 考察字符串处理和模拟。
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056) - 考察模拟和优化策略。

---

### 个人心得摘录
- **调试经历**：在处理空行时，容易忽略空行的处理，导致程序出错。通过增加空行特判，解决了这一问题。
- **踩坑教训**：在计算左右空格数时，容易忽略奇偶性判断，导致微调逻辑出错。通过增加奇偶性判断，解决了这一问题。
- **顿悟感想**：使用`string`构造函数生成边框和空格，大大简化了代码，提高了代码的可读性和可维护性。

---
处理用时：51.30秒