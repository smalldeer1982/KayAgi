# 题目信息

# Mark the Photographer

## 题目描述

Mark is asked to take a group photo of $ 2n $ people. The $ i $ -th person has height $ h_i $ units.

To do so, he ordered these people into two rows, the front row and the back row, each consisting of $ n $ people. However, to ensure that everyone is seen properly, the $ j $ -th person of the back row must be at least $ x $ units taller than the $ j $ -th person of the front row for each $ j $ between $ 1 $ and $ n $ , inclusive.

Help Mark determine if this is possible.

## 说明/提示

In the first test case, one possible order is to have the third, fifth, and sixth person on the back row and the second, first, and fourth on the front row. The heights of the people will look like this.

 Back $ 9 $  $ 12 $  $ 16 $ Front $ 3 $  $ 1 $  $ 10 $ It works because

- $ h_3-h_2 = 9-3 \geq 6 $ ,
- $ h_5-h_1 = 12-1\geq 6 $ , and
- $ h_6-h_4 = 16-10\geq 6 $ .

In the second test case, it can be shown there is no way to order people in a way that satisfies the condition.

In the third test case, the only way to arrange people to satisfy the condition is to have the first person on the back row and the second person on the front row.

## 样例 #1

### 输入

```
3
3 6
1 3 9 10 12 16
3 1
2 5 2 2 2 5
1 2
8 6```

### 输出

```
YES
NO
YES```

# AI分析结果



# Mark the Photographer 的中文题目

## 题目描述

Mark 需要为 $2n$ 个人拍摄集体照。第 $i$ 个人的身高为 $h_i$ 单位。

他需要将这些人排成两排：前排和后排，每排各 $n$ 人。为了保证每个人都能被清晰看到，后排的第 $j$ 个人必须比前排的第 $j$ 个人至少高 $x$ 单位（对每个 $1 \le j \le n$ 成立）。

请帮助 Mark 判断是否存在这样的排列方式。

## 说明/提示

第一个测试案例中，可行的排列方式是将第三、五、六人放在后排，第二、一、四人放在前排。具体身高差验证如下：
- 后排第一人 9 与前排第一人 3 的差为 6
- 后排第二人 12 与前排第二人 1 的差为 11
- 后排第三人 16 与前排第三人 10 的差为 6

第二个测试案例证明无法找到满足条件的排列。

第三个测试案例唯一可行的排列是将第一人放在后排，第二人放在前排。

---

## 题解分析与结论

### 关键思路
所有题解均采用排序+贪心策略，核心步骤为：
1. 将 $2n$ 人按身高升序排序
2. 检查前 $n$ 人分别与后 $n$ 人的对应位置差值是否满足 $h_{i+n}-h_i \ge x$

正确性证明要点：
- **鸽巢原理**：对于任意前 $i+n$ 个元素，若存在不满足条件的位置，则必然存在无法配对的列
- **贪心最优性**：按序匹配能确保最小差值最大化

### 精选题解（评分≥4星）

#### 1. FFTotoro（★★★★★）
**亮点**：引用鸽巢原理严格证明，代码简洁高效
```cpp
sort(a.begin(),a.end());
bool flag=true;
for(int i=0;i<n;i++)
    if(a[i+n]-a[i]<k) flag=false;
```

#### 2. MH_SLC（★★★★☆）
**亮点**：详细解释贪心选择策略，包含调试经验
```cpp
sort(a + 1, a + 2 * n + 1);
for(int i = 1; i <= n; i++)
    if(a[n + i] - a[i] < x) flag = 1;
```

#### 3. sunkuangzheng（★★★★☆）
**亮点**：给出归并排序实现，强调证明过程
```cpp
msort(1,2*n); // 手写归并排序
for(int i=1;i<=n;i++)
    if(a[i+n]-a[i]<x) { ... }
```

---

## 核心实现代码
```cpp
// 通用实现框架
sort(h.begin(), h.end());
bool valid = true;
for(int i=0; i<n; ++i) {
    if(h[i+n] - h[i] < x) {
        valid = false;
        break;
    }
}
cout << (valid ? "YES" : "NO");
```

---

## 举一反三

### 类似题目推荐
1. P1094 [NOIP2007 普及组] 纪念品分组 - 贪心+双指针
2. P1106 删数问题 - 贪心选择数字排列
3. P1233 木棍加工 - 二维排序贪心

### 调试经验总结
- **边界检查**：循环范围需严格覆盖n个比较对（如从0或1开始需统一）
- **排序范围**：确保排序整个2n数组（某题解曾因此出错）
- **提前退出**：发现不满足条件立即break提升效率

### 关键技巧
当遇到**两两配对**且存在**差值约束**的问题时：
1. 排序往往是突破口
2. 相邻/对称位置的配对能保证最优性
3. 数学证明（鸽巢原理、反证法）能有效验证策略正确性

---
处理用时：46.48秒