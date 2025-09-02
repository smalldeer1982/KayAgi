# 题目信息

# yyy2015c01 的 IDE 之 Call Stack

## 题目背景

在 2020 年的某一天，我们的 yyy2015c01 同学想要开发一套 IDE。


## 题目描述

作为他开发团队中的一员，你不幸地 yyy2015c01 被选入了 Debugger 的开发组。

yyy2015c01 设想的 Debugger 由几部分组成，其中的一个小组件就是 Call Stack——中文称之为 “调用栈”。

由于 IDE 目前还是内测版，开发组需要先编一个能识别参数表的 Call Stack 来看看效果如何。这个任务交由你来完成。

开发组假想的 Call Stack 能实现识别 `int` 和 `char` 参数表，以辨别出不同的函数，规则是：

```
int fac1(int n);
```

和

```
int fac1(char n);
```

是两个不同的函数；但

```
int Fac1(int n,int m);
```

和

```
int FAC1(int x,int y);
```

被认为是相同的函数。也就是说，这个 Call Stack 认的不是参数名，而是其类型和忽略大小写的函数名。

注意：`int main()` 可能会出现，也可能不出现；无论它有没有出现，都不能将其算入函数中。

请你编写一个 Call Stack，并在所有函数调用完后输出这个程序一共有多少个不完全相同的函数（保证程序中的每个函数至少调用一次）。


## 说明/提示

每个函数的参数最多有 $10$ 个，每行的输入数据长度均不超过 $255$。

向本题主人公 yyy2015c01 同学致敬！


## 样例 #1

### 输入

```
2
FAC1 (N=233, M=65 'A', A=0)
main ()
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
fac1 (N=250)
FAC1 (a=987)
```

### 输出

```
1
```

# AI分析结果

### 综合分析与结论

本题的核心任务是统计不同函数的数量，函数的不同性由函数名（忽略大小写）和参数类型决定。题解主要集中在如何高效地处理输入、判断函数是否重复、以及如何存储和比较函数信息。大多数题解采用了结构体或`map`、`set`等数据结构来存储函数信息，并通过遍历或哈希表来判断重复。

### 所选高星题解

#### 1. 作者：Alex_Wei (5星)
**关键亮点**：
- 使用结构体`fact`存储函数名和参数类型，结构清晰。
- 通过`vector<fact>`存储所有函数，并通过遍历去重，逻辑简单明了。
- 单独编写`getpara()`函数处理参数，提高了代码的可读性和复用性。

**核心代码**：
```cpp
struct fact{
    string na;
    vector<int> para;
};

vector<int> getpara() {
    string p;
    int pc = 0;
    vector<int> para;
    getline(cin, p);
    for(int x = 0; x < p.size(); x++) {
        if(p[x] == ',' || p[x] == ')') para.pb(pc), pc = 0;
        if(p[x] == 39) pc = 1;
    }
    return para;
}
```

#### 2. 作者：OoXiao_QioO (4星)
**关键亮点**：
- 使用`map<string, int>`存储函数名和参数类型的组合，简化了去重逻辑。
- 通过字符串拼接函数名和参数类型，避免了复杂的比较操作。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码**：
```cpp
map<string, int> M;
string x;
char s[100001], s1[100001];

int main() {
    int n, i, l, cnt = 0, f;
    cin >> n;
    while(n--) {
        scanf("%s", s);
        l = strlen(s);
        if(strcmp(s, "main") == 0) continue;
        for(i = 0; i < l; i++) if(isupper(s[i])) s[i] += 32;
        x = s;
        getchar();
        gets(s1);
        l = strlen(s1);
        for(i = 0; i < l; i++) {
            f = 1;
            if(s1[i] == '=') {
                while(s1[i] != ',' && i < l) {
                    i++;
                    if(s1[i] == '\'') { f = 0; break; }
                }
            }
            if(f) x += '1'; else x += '0';
        }
        if(M[x] == 0) cnt++;
        M[x] = 1;
    }
    cout << cnt << endl;
    return 0;
}
```

#### 3. 作者：ZXXS (4星)
**关键亮点**：
- 使用`set<pair<string, string>>`存储函数名和参数类型，利用`set`自动去重的特性。
- 通过`getline`读取参数，处理了参数中的空格问题。
- 代码结构清晰，逻辑简单，适合快速实现。

**核心代码**：
```cpp
set<pair<string, string>> se;
int m; 
string s, a;

int main() {
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        cin >> s;
        if(s == "main") { getline(cin, s); continue; }
        for(int i = 0; i < s.size(); ++i) if(s[i] >= 'a' && s[i] <= 'z') s[i] += 'A' - 'a';
        a = s;
        getline(cin, s);
        s[s.size() - 2] = ',';
        if(s == "()") { se.insert(make_pair("", a)); }
        string p = "";
        for(int i = 0; i < s.size(); ++i) if(s[i] == ',') p += (s[i - 1] == 39 && s[i + 1] != 39 ? '1' : '0');
        se.insert(make_pair(p, a));
    }
    printf("%d\n", se.size());
    return 0;
}
```

### 最优关键思路与技巧
1. **数据结构选择**：使用`vector`、`map`或`set`存储函数信息，简化了去重逻辑。
2. **参数处理**：通过判断单引号的存在来确定参数类型，简化了参数类型的判断。
3. **函数名处理**：将函数名统一转换为小写，避免了大小写敏感的问题。

### 拓展与举一反三
- **类似题目**：可以尝试处理更复杂的函数签名，如带有默认参数、模板参数等。
- **算法套路**：类似的问题可以通过字符串处理和哈希表来解决，适用于需要快速查找和去重的场景。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

### 个人心得总结
- **调试经历**：在处理参数时，容易忽略空格和逗号的影响，建议使用`getline`读取整行数据。
- **踩坑教训**：函数名的大小写处理容易被忽略，建议统一转换为小写或大写后再进行比较。
- **顿悟感想**：使用`set`或`map`可以大大简化去重逻辑，适合处理需要快速查找和去重的问题。

---
处理用时：39.84秒