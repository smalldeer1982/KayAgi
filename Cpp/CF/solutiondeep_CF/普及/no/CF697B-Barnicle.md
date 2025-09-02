# 题目信息

# Barnicle

## 题目描述

Barney is standing in a bar and starring at a pretty girl. He wants to shoot her with his heart arrow but he needs to know the distance between him and the girl to make his shot accurate.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF697B/5aebaf3f991f80d87e0ec849d0a3847086ffdfb5.png)Barney asked the bar tender Carl about this distance value, but Carl was so busy talking to the customers so he wrote the distance value (it's a real number) on a napkin. The problem is that he wrote it in scientific notation. The scientific notation of some real number $ x $ is the notation of form $ AeB $ , where $ A $ is a real number and $ B $ is an integer and $ x=A×10^{B} $ is true. In our case $ A $ is between $ 0 $ and $ 9 $ and $ B $ is non-negative.

Barney doesn't know anything about scientific notation (as well as anything scientific at all). So he asked you to tell him the distance value in usual decimal representation with minimal number of digits after the decimal point (and no decimal point if it is an integer). See the output format for better understanding.

## 样例 #1

### 输入

```
8.549e2
```

### 输出

```
854.9
```

## 样例 #2

### 输入

```
8.549e3
```

### 输出

```
8549
```

## 样例 #3

### 输入

```
0.33e0
```

### 输出

```
0.33
```

# AI分析结果



# Barnicle

## 题目描述

Barney 站在酒吧里凝视着一个漂亮女孩。他想用心形箭射她，但需要知道他与女孩之间的距离以确保射击准确。

Barney 向酒保 Carl 询问这个距离值，但 Carl 正忙于与顾客交谈，于是将距离值（一个实数）写在餐巾纸上。问题是这个值是用科学计数法书写的。某个实数 $x$ 的科学计数法表示为 $AeB$，其中 $A$ 是实数，$B$ 是整数，满足 $x = A × 10^B$。在本问题中，$A$ 的取值在 $0$ 到 $9$ 之间，$B$ 是非负整数。

Barney 对科学计数法一窍不通，请求你告诉他该距离值的常规十进制表示，要求小数点后的数字尽可能少（如果是整数则不保留小数点）。具体输出格式参考样例。

## 样例 #1

### 输入
```
8.549e2
```

### 输出
```
854.9
```

## 样例 #2

### 输入
```
8.549e3
```

### 输出
```
8549
```

## 样例 #3

### 输入
```
0.33e0
```

### 输出
```
0.33
```

---

**算法分类**：字符串、模拟

---

### 题解分析与结论

#### 核心思路
1. **输入解析**：将科学计数法拆分为有效数字部分（A）和指数部分（B）。
2. **小数点移动**：根据指数 B 的数值，将 A 的小数点向右移动 B 位。
3. **边界处理**：处理补零、去除前导/后缀零、整数无小数点等特殊情况。

#### 关键技巧
- **格式化输入**：使用 `scanf` 的高级特性直接提取各部分（如 `%[^e]` 读取到 e 前的内容）。
- **字符串操作**：通过字符串分割、拼接和插入操作模拟小数点移动。
- **特判优化**：针对 `1.0e0` 等特殊情况进行单独处理，避免冗余计算。

---

### 精选题解

#### 题解1：Miller2019（★★★★☆）
**亮点**：
- 利用 `scanf` 高级格式拆分输入，代码简洁高效。
- 分类讨论指数与小数位数的三种情况，逻辑清晰。
- 实测最优解（497ms/3.54MB）。

**核心代码**：
```cpp
scanf("%d.",&i);
scanf("%[^e]%ne%d",d,&digit,&k);
if (k >= digit) {
    printf("%d%s%.*d",i,d,k-digit,0);
} else {
    printf("%d%.*s.%s",i,k,d,d+k);
}
```

#### 题解2：LOVE_Ynoi（★★★★☆）
**亮点**：
- 使用 `string` 的 `find` 和 `substr` 分割输入，代码直观。
- 特判 `1.0e0` 类特殊情况，避免错误输出。

**核心代码**：
```cpp
pos = x.find('e');
string f = x.substr(0, pos);
int n = stoi(d);
f.erase(1 + f.begin());
if (f.size() - 1 > n) 
    f.insert(1 + n, ".");
else 
    f.append(n - f.size() + 1, '0');
```

#### 题解3：zsh_haha（★★★★☆）
**亮点**：
- 分情况处理整数/小数部分，逻辑完备。
- 动态处理前导零和后缀零，鲁棒性强。

**关键实现**：
```cpp
for (int i = cnt; i >= 0; i--) { // 处理后缀零
    if (flag && b[i] == '0') cnt--;
    else break;
}
```

---

### 拓展练习
1. [P1022 计算器的改良](https://www.luogu.com.cn/problem/P1022) - 字符串解析与方程求解。
2. [P1061 Booklet Printing](https://www.luogu.com.cn/problem/P1061) - 分页模拟与边界处理。
3. [P1553 数字反转（升级版）](https://www.luogu.com.cn/problem/P1553) - 字符串操作与特殊符号处理。

---
处理用时：61.52秒