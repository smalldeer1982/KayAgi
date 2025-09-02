# 题目信息

# Sum of Digits

## 题目描述

Having watched the last Harry Potter film, little Gerald also decided to practice magic. He found in his father's magical book a spell that turns any number in the sum of its digits. At the moment Gerald learned that, he came across a number $ n $ . How many times can Gerald put a spell on it until the number becomes one-digit?

## 说明/提示

In the first sample the number already is one-digit — Herald can't cast a spell.

The second test contains number $ 10 $ . After one casting of a spell it becomes $ 1 $ , and here the process is completed. Thus, Gerald can only cast the spell once.

The third test contains number $ 991 $ . As one casts a spell the following transformations take place: $ 991→19→10→1 $ . After three transformations the number becomes one-digit.

## 样例 #1

### 输入

```
0
```

### 输出

```
0
```

## 样例 #2

### 输入

```
10
```

### 输出

```
1
```

## 样例 #3

### 输入

```
991
```

### 输出

```
3
```

# AI分析结果



### 中文重述题目
# 数位和

## 题目描述

小Gerald看完《哈利波特》后决定练习魔法。他在父亲的魔法书中发现了一个咒语，能将任意数变为其各位数字之和。当他学会这个咒语时，遇到了一个数$n$。Gerald可以施放多少次咒语直到该数变为个位数？

## 说明/提示

第一个样例中的数本身就是一位数，无法施法。

第二个样例中的数是10，施法一次后变为1，过程结束。因此可以施放1次。

第三个样例中的数是991，经过三次变换：991→19→10→1，最终变为个位数。

### 输入输出样例见原题

---

### 算法分类
**模拟**

---

### 题解综合分析

各题解核心思路一致：
1. **字符串处理大数**：由于输入可达$10^{10^5}$，首次转换必须用字符串处理各位求和。
2. **数值类型后续处理**：第一次转换后数值最大为$9 \times 10^5$，可用`int`或`long long`继续处理。
3. **特判边界**：输入长度=1时直接输出0次。
4. **循环累加次数**：首次转换计为1次，后续每次转换直至结果<10。

**共同难点**：  
多数题解未正确处理全零输入（如"000"），此时数值为0但字符串长度>1，正确结果应为0次。仅AB_IN的Python题解通过`int(s)`隐式处理了前导零。

---

### 高星题解推荐

#### 1. AB_IN（Python） - ⭐⭐⭐⭐
**亮点**：  
- 直接利用Python的`int()`处理字符串转数值，自动消除前导零。
- 简洁清晰的循环结构，正确处理全零情况。
**代码核心**：
```python
def f(x):
    cnt = 0
    for i in x: cnt += int(i)
    return str(cnt)

s = input().strip()
num = 0
while int(s) >= 10:
    s = f(s)
    num += 1
print(num)
```

#### 2. wpj20241021005（C++） - ⭐⭐⭐⭐
**亮点**：  
- 清晰的字符串处理与数值转换分离逻辑。
- 特判输入长度为1的情况，代码可读性强。  
**改进点**：需增加全零输入的判断。  
**核心代码**：
```cpp
string n;
unsigned long long cnt = 0, ans = 1;
for (int i = 0; i < n.size(); i++) 
    cnt += n[i] - '0';
while (cnt >= 10) {
    ans++;
    cnt = change(cnt); // 数位和函数
}
cout << ans;
```

---

### 关键思路总结
- **大数处理**：用字符串处理初始输入，避免数值溢出。
- **转换优化**：首次转换后转为数值类型，减少后续计算开销。
- **边界特判**：注意长度为1或全零的特殊情况。
- **隐式转换**（Python优势）：利用语言特性简化前导零处理。

---

### 同类题目推荐
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   - 考察：模拟与分治思想
2. [P1307 数字反转](https://www.luogu.com.cn/problem/P1307)  
   - 考察：字符串/数值处理
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)  
   - 考察：字符串排序与组合

---
处理用时：242.45秒