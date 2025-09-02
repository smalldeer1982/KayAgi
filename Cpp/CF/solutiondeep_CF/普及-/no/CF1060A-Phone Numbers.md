# 题目信息

# Phone Numbers

## 题目描述

Let's call a string a phone number if it has length 11 and fits the pattern "8xxxxxxxxxx", where each "x" is replaced by a digit.

For example, "80123456789" and "80000000000" are phone numbers, while "8012345678" and "79000000000" are not.

You have $ n $ cards with digits, and you want to use them to make as many phone numbers as possible. Each card must be used in at most one phone number, and you don't have to use all cards. The phone numbers do not necessarily have to be distinct.

## 说明/提示

In the first example, one phone number, "8000000000", can be made from these cards.

In the second example, you can make two phone numbers from the cards, for example, "80123456789" and "80123456789".

In the third example you can't make any phone number from the given cards.

## 样例 #1

### 输入

```
11
00000000008
```

### 输出

```
1
```

## 样例 #2

### 输入

```
22
0011223344556677889988
```

### 输出

```
2
```

## 样例 #3

### 输入

```
11
31415926535
```

### 输出

```
0
```

# AI分析结果



# Phone Numbers

## 题目描述

我们称一个字符串为电话号码，当且仅当它的长度为 11 且符合模式 "8xxxxxxxxxx"，其中每个 "x" 被替换为一个数字。

例如，"80123456789" 和 "80000000000" 是电话号码，而 "8012345678" 和 "79000000000" 不是。

你有 $n$ 张数字卡片，需要尽可能多地组成电话号码。每张卡片最多被用于一个电话号码，且不必用完所有卡片。电话号码不必互不相同。

## 说明/提示

- 第一个样例中，用卡片可以组成一个电话号码 "80000000000"。
- 第二个样例中，可以组成两个电话号码，例如 "80123456789" 和 "80123456789"。
- 第三个样例中无法组成任何电话号码。

---

**算法分类**：贪心

---

### 题解综合分析

题目核心是计算最多能组成多少个电话号码。每个电话号码需要 1 个 '8' 作为开头和 10 个其他数字。关键约束是总卡片数必须足够组成 k 个号码（每个 11 张卡片），且 '8' 的数量足够。最优解为以下两者的最小值：  
1. 总卡片数可组成的号码数：`n // 11`  
2. '8' 的数量：`count_8`

**关键技巧**：通过一次遍历统计 '8' 的出现次数，直接取最小值即可，时间复杂度 O(n)。

---

### 高星题解推荐

#### 题解作者：Fan_Tuan（4 星）
**亮点**：代码简洁，直接计算最小值，输入处理规范。  
**核心代码**：
```c
int main() {
    scanf("%d", &n);
    scanf("%s", s); 
    for (int i = 0; i < n; i++) 
        if (s[i] == '8') count++;
    cout << min(count, n/11);
}
```

#### 题解作者：kevin24（4 星）
**亮点**：逻辑清晰，逐字符读取避免数组越界。  
**核心代码**：
```cpp
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        if (a == '8') s++;
    }
    cout << min(n/11, s);
}
```

---

### 拓展与总结

**同类题目推荐**：
1. [P4995 跳跳！](https://www.luogu.com.cn/problem/P4995)（贪心策略）
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（贪心排序）
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（双指针贪心）

**个人心得**：  
- 注意题目隐含的总卡片数约束，避免漏判 `n < 11` 的情况（虽然 `n//11` 自动处理）。
- 直接遍历统计比复杂枚举更高效，体现了贪心思想的简洁性。

---
处理用时：158.43秒