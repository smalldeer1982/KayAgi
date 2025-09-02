# 题目信息

# Restoring IPv6

## 题目描述

An IPv6-address is a 128-bit number. For convenience, this number is recorded in blocks of 16 bits in hexadecimal record, the blocks are separated by colons — 8 blocks in total, each block has four hexadecimal digits. Here is an example of the correct record of a IPv6 address: "0124:5678:90ab:cdef:0124:5678:90ab:cdef". We'll call such format of recording an IPv6-address full.

Besides the full record of an IPv6 address there is a short record format. The record of an IPv6 address can be shortened by removing one or more leading zeroes at the beginning of each block. However, each block should contain at least one digit in the short format. For example, the leading zeroes can be removed like that: "a56f:00d3:0000:0124:0001:f19a:1000:0000" $ → $ "a56f:d3:0:0124:01:f19a:1000:00". There are more ways to shorten zeroes in this IPv6 address.

Some IPv6 addresses contain long sequences of zeroes. Continuous sequences of 16-bit zero blocks can be shortened to "::". A sequence can consist of one or several consecutive blocks, with all 16 bits equal to 0.

You can see examples of zero block shortenings below:

- "a56f:00d3:0000:0124:0001:0000:0000:0000" $ → $ "a56f:00d3:0000:0124:0001::";
- "a56f:0000:0000:0124:0001:0000:1234:0ff0" $ → $ "a56f::0124:0001:0000:1234:0ff0";
- "a56f:0000:0000:0000:0001:0000:1234:0ff0" $ → $ "a56f:0000::0000:0001:0000:1234:0ff0";
- "a56f:00d3:0000:0124:0001:0000:0000:0000" $ → $ "a56f:00d3:0000:0124:0001::0000";
- "0000:0000:0000:0000:0000:0000:0000:0000" $ → $ "::".

It is not allowed to shorten zero blocks in the address more than once. This means that the short record can't contain the sequence of characters "::" more than once. Otherwise, it will sometimes be impossible to determine the number of zero blocks, each represented by a double colon.

The format of the record of the IPv6 address after removing the leading zeroes and shortening the zero blocks is called short.

You've got several short records of IPv6 addresses. Restore their full record.

## 样例 #1

### 输入

```
6
a56f:d3:0:0124:01:f19a:1000:00
a56f:00d3:0000:0124:0001::
a56f::0124:0001:0000:1234:0ff0
a56f:0000::0000:0001:0000:1234:0ff0
::
0ea::4d:f4:6:0
```

### 输出

```
a56f:00d3:0000:0124:0001:f19a:1000:0000
a56f:00d3:0000:0124:0001:0000:0000:0000
a56f:0000:0000:0124:0001:0000:1234:0ff0
a56f:0000:0000:0000:0001:0000:1234:0ff0
0000:0000:0000:0000:0000:0000:0000:0000
00ea:0000:0000:0000:004d:00f4:0006:0000
```

# AI分析结果



# 中文题目重写
## 题目描述

IPv6地址是一个128位的数字。为了方便，这个数字被记录为8个16位的十六进制块，用冒号分隔。例如"0124:5678:90ab:cdef:0124:5678:90ab:cdef"是完整格式。

压缩规则包括：
1. 移除每个块的前导零（至少保留一位）
2. 用"::"替换连续的一个或多个全零块（只能使用一次）

给定若干压缩后的IPv6地址，还原其完整形式。

## 输入输出样例
见原题

## 算法分类
字符串、模拟

---

# 题解分析与结论

### 解决思路共性
1. 处理双冒号：确定被压缩的零块数量（8 - 实际块数）
2. 补全前导零：每个块补至4位十六进制
3. 分段处理：将输入字符串拆分为若干块，处理特殊情况

### 最优题解亮点

#### 题解作者：0AND1STORY（★★★★☆）
**关键思路**：
- 将双冒号视为特殊标记0xfffff
- 使用vector存储各块数值
- 计算需要填充的零块数量（8 - 实际块数 +1）
- 用`printf("%04x")`自动补全前导零

**核心代码**：
```cpp
void work() {
    a.clear();
    input(); // 将双冒号转为0xfffff存入vector
    for (int i=0; i<a.size(); i++) {
        if (a[i] != 0xfffff) {
            printf("%04x:", a[i]); // 自动补零
        } else {
            int zero_blocks = 8 - a.size() + 1;
            while (zero_blocks--) printf("0000:");
        }
    }
    // 处理最后一个块（略）
}
```

#### 题解作者：joe_zxq（★★★★☆）
**关键思路**：
- 统计实际块数确定补零数量
- 使用vector存储非空块
- 遍历时遇到空块则填充计算出的零块

**核心代码**：
```cpp
void solve() {
    string s = "::1ed"; // 示例输入
    int cnt = 8 - 实际块数;
    for (int i=0; i<ss.size(); i++) {
        if (ss[i].empty()) {
            while (cnt--) cout << "0000:"; // 填充零块
        } else {
            ss[i] = string(4-ss[i].size(),'0') + ss[i]; // 补前导零
        }
    }
}
```

---

# 关键技巧总结
1. **双冒号处理**：通过`8 - 现有块数`确定零块数量
2. **格式化补零**：用`%04x`或手动补零保证4位长度
3. **分段策略**：将字符串拆分为块时，空块表示双冒号位置

---

# 拓展练习
1. [P2815 IPv6地址压缩](https://www.luogu.com.cn/problem/P2815)（逆过程）
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)（复杂字符串解析）
3. [P1179 数字分析](https://www.luogu.com.cn/problem/P1179)（字符串格式化处理）

---
处理用时：57.77秒