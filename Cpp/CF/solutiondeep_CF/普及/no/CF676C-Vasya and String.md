# 题目信息

# Vasya and String

## 题目描述

High school student Vasya got a string of length $ n $ as a birthday present. This string consists of letters 'a' and 'b' only. Vasya denotes beauty of the string as the maximum length of a substring (consecutive subsequence) consisting of equal letters.

Vasya can change no more than $ k $ characters of the original string. What is the maximum beauty of the string he can achieve?

## 说明/提示

In the first sample, Vasya can obtain both strings "aaaa" and "bbbb".

In the second sample, the optimal answer is obtained with the string "aaaaabaa" or with the string "aabaaaaa".

## 样例 #1

### 输入

```
4 2
abba
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 1
aabaabaa
```

### 输出

```
5
```

# AI分析结果



# Vasya and String

## 题目描述

高中生Vasya得到一个长度为$n$的生日礼物字符串，仅由字母'a'和'b'组成。定义字符串的美丽值为最长连续相同字符子串的长度。Vasya最多可以改变$k$个字符，求他能得到的最大美丽值。

## 算法分类
滑动窗口（双指针法）

## 题解综合分析

### 核心思路对比
各题解主要采用两种方法：
1. **滑动窗口法**：维护可变窗口，统计窗口内非目标字符数量，通过左右指针动态调整窗口大小
2. **二分法**：预处理字符位置数组，通过二分查找确定最长可用区间

滑动窗口法时间复杂度O(n)更优，二分法O(nlogn)在本题数据规模下也可行但实现较复杂。所有题解中，滑动窗口法实现更简洁高效。

### 最优题解推荐

#### 1. wuyixiang（5星）
**亮点**：  
- 两次独立滑动窗口处理a/b两种情况
- 代码结构清晰易读
- 严格维护修改次数约束条件

**核心代码**：
```cpp
int main() {
    // 处理a的最大长度
    for(int r = 1; r <= n; r++) {
        if(a[r] == 'a') sum++;
        while(sum > k && l < r) {
            if(a[l] == 'a') sum--;
            l++;
        }
        ans = max(ans, r - l);
    }
    // 处理b的最大长度（结构同上）
}
```

#### 2. xiongyuhan（4星）
**亮点**：
- 统一处理逻辑封装为函数
- 变量命名清晰直观

**代码片段**：
```cpp
while(r < n) { // 处理a转b
    if(s[r] == 'a') sum++;
    while(sum > k) {
        if(s[l] == 'a') sum--;
        l++;
    }
    ans = max(ans, r++ - l + 1);
}
```

#### 3. pomelo_nene（4星）
**亮点**：
- 单次遍历同时处理两种字符
- 空间复杂度优化至O(1)

**实现思路**：
```cpp
while(r < n) {
    // 统计当前字符数
    if(a <= k || b <= k) 扩展窗口
    else 滑动左边界
}
```

## 关键技巧总结
1. **双指针维护有效窗口**：左指针仅在超过修改次数时移动，保证窗口始终合法
2. **分情况独立处理**：分别计算全a和全b的最优解后取最大值
3. **即时更新最大值**：每次窗口移动后立即更新结果，避免二次遍历

## 同类题目推荐
1. [P0383 滑动窗口](https://www.luogu.com.cn/problem/P1886) - 滑动窗口最值问题
2. [P0219 尽可能使字符串相等](https://leetcode-cn.com/problems/get-equal-substrings-within-budget/)（同类思想）
3. [P1493 最大连续1的个数 III](https://leetcode-cn.com/problems/max-consecutive-ones-iii/)（相同模板题）

## 调试经验摘录
1. **边界处理**：需单独处理k=0的情况（作者gxxjqqiang通过特判解决）
2. **初始化重置**：处理第二种字符前必须重置计数变量（wuyixiang代码中的`l = 0, sum = 0`）
3. **索引偏移**：多位作者通过添加前缀空格(`a = " " + a`)简化索引计算

---
处理用时：55.28秒