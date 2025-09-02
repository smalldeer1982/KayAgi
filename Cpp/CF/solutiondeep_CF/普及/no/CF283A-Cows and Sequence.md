# 题目信息

# Cows and Sequence

## 题目描述

Bessie and the cows are playing with sequences and need your help. They start with a sequence, initially containing just the number 0, and perform $ n $ operations. Each operation is one of the following:

1. Add the integer $ x_{i} $ to the first $ a_{i} $ elements of the sequence.
2. Append an integer $ k_{i} $ to the end of the sequence. (And hence the size of the sequence increases by 1)
3. Remove the last element of the sequence. So, the size of the sequence decreases by one. Note, that this operation can only be done if there are at least two elements in the sequence.

After each operation, the cows would like to know the average of all the numbers in the sequence. Help them!

## 说明/提示

In the second sample, the sequence becomes ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF283A/56857d21d773e19700b8e6f134c0c7d8dc59ae9f.png)

## 样例 #1

### 输入

```
5
2 1
3
2 3
2 1
3
```

### 输出

```
0.500000
0.000000
1.500000
1.333333
1.500000
```

## 样例 #2

### 输入

```
6
2 1
1 2 20
2 2
1 2 -3
3
3
```

### 输出

```
0.500000
20.500000
14.333333
12.333333
17.500000
17.000000
```

# AI分析结果



# Cows and Sequence

## 题目描述

Bessie 和奶牛们在玩序列游戏，需要你的帮助。初始时序列只有一个数字 0，之后进行 $n$ 次操作，操作类型如下：

1. 将整数 $x_i$ 加到序列前 $a_i$ 个元素
2. 在序列末尾追加整数 $k_i$（序列长度 +1）
3. 删除序列最后一个元素（仅当序列元素 ≥2 时可用）

每次操作后输出序列所有数的平均值（保留十位小数）

## 输入输出样例

样例 #1 输入输出已省略，详见原题

## 算法分类
差分

---

## 题解综合分析

各题解均采用差分标记思想优化前缀操作，核心思路为：
1. 用标记数组记录前缀操作的影响
2. 删除元素时通过标记传递保持正确性
3. 维护总和与元素个数快速计算平均值

### 最优题解亮点

#### 1. [wmrqwq] ⭐⭐⭐⭐
**核心技巧**：双数组分离原始值与差分标记  
**代码亮点**：
```cpp
else if(opt==3)
    ans -= sz[gs] + pd[gs];  // 同时减去原始值与标记
    pd[gs-1] += pd[gs];      // 标记传递
    sz[gs] = pd[gs] = 0;     // 清空已删除元素
```
采用显式清空操作，避免残留数据干扰后续计算

#### 2. [RioFutaba] ⭐⭐⭐⭐
**思维亮点**：将标记数组解释为"未叠加的影响"  
**关键实现**：
```cpp
sum -= num[cnt] + s[cnt];    // 同时扣除数值与未应用的标记
s[cnt-1] += s[cnt];          // 向后传递未完成的操作
```
用变量名 `s` 直观表达待传播的增量

#### 3. [MattL] ⭐⭐⭐⭐
**代码优化**：switch 结构提升可读性  
**实现技巧**：
```cpp
case 3: // 三目运算处理删除
    sum -= num[cnt] + s[cnt];
    s[cnt-1] += s[cnt];
    num[cnt] = s[cnt--] = 0;
```
通过归零操作显式释放内存，减少潜在错误

---

## 关键代码实现

```cpp
// 基于 RioFutaba 题解的核心逻辑
int main() {
    int cnt = 1; // 初始包含元素0
    double sum = 0;
    vector<int> num(2e5+5), s(2e5+5);
    
    while(n--) {
        int op; cin >> op;
        if(op == 1) {
            int a, x; cin >> a >> x;
            s[a] += x;       // 记录前缀操作
            sum += a * x;    // 直接计算增量总和
        } else if(op == 2) {
            int k; cin >> k;
            num[++cnt] = k;  // 追加元素
            sum += k;
        } else if(cnt >= 2) {
            sum -= num[cnt] + s[cnt]; // 扣除末端值与未应用的标记
            s[cnt-1] += s[cnt];      // 标记前移
            s[cnt] = num[cnt] = 0;   // 清空已删除位置
            cnt--;
        }
        printf("%.10f\n", sum / cnt);
    }
}
```

---

## 拓展建议

1. **同类题型**：
   - 前缀操作优化：P3368（树状数组区间更新）
   - 动态维护平均值：P2827（滑动窗口维护）
   - 标记传播机制：P3372（线段树懒标记）

2. **举一反三**：
   当遇到以下特征时可考虑差分标记：
   - 操作仅影响前缀或后缀
   - 存在后进先出的元素变更（栈结构）
   - 需要将区间操作转换为单点操作

---

## 推荐练习
1. P2367 差分基础练习（难度：普及-）
2. P3368 树状数组区间修改（难度：普及/提高-）
3. P3373 线段树综合操作（难度：普及+/提高）

---
处理用时：64.54秒