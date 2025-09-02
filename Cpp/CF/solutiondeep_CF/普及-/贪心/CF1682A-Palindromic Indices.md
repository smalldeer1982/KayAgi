# 题目信息

# Palindromic Indices

## 题目描述

给定一个回文字符串 $s$ ，它的长度为 $ n $ $ (2 \leq n \leq 10^5) $ ，问一共有多少种方式使它去掉一个字符后仍是回文字符串。

## 说明/提示

数据保证所有的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ 。

## 样例 #1

### 输入

```
3
3
aba
8
acaaaaca
2
dd```

### 输出

```
1
4
2```

# AI分析结果



# Palindromic Indices

## 题目描述

给定一个回文字符串 $s$ ，它的长度为 $ n $ $ (2 \leq n \leq 10^5) $ ，问有多少种方式使它去掉一个字符后仍是回文字符串。

## 说明/提示

数据保证所有的 $ n $ 之和不超过 $ 2 \cdot 10^5 $ 。

## 样例 #1

### 输入

```
3
3
aba
8
acaaaaca
2
dd
```

### 输出

```
1
4
2
```

---

### 题解综合分析

#### 关键思路总结
所有题解均围绕回文对称性展开，核心观察点：**可删除的位置必为中心对称的连续相同字符段**。最优解法通过以下步骤实现：
1. **确定中心位置**：奇数长度取中间字符，偶数长度取中间偏右位置
2. **双向扩展统计**：从中心向左右扩展统计连续相同字符数
3. **奇偶处理**：奇数长度需避免重复计数中心字符

#### 最优技巧提炼
1. **中心扩展法**：时间复杂度 O(n) 的线性遍历方式
2. **对称性利用**：仅需处理中心区域无需全串遍历
3. **奇偶统一处理**：通过整数除法特性统一处理不同长度类型

---

### 精选题解推荐

#### 1. 作者：_Ad_Astra_（★★★★★）
**核心亮点**：
- 代码简洁高效，利用字符串下标从0开始的特性统一处理奇偶
- 双向扩展逻辑清晰，仅需10行核心代码
```cpp
void solve() {
    cin >> n >> s;
    ans = 1;
    int id = n / 2; // 中心位置处理
    for(int i = id-1; i >= 0 && s[i] == s[id]; i--) ans++; // 左向扩展
    for(int i = id+1; i < n && s[i] == s[id]; i++) ans++;  // 右向扩展
    cout << ans << endl;
}
```

#### 2. 作者：Night_sea_64（★★★★☆）
**独特贡献**：
- 提出奇偶情况统一计算公式 `cnt*2 + n%2`
- 单侧遍历优化减少循环次数
```cpp
for(int i = n/2 + n%2; i < n && s[i] == s[i-1]; i++) cnt++;
cout << cnt*2 + n%2 << endl;
```

#### 3. 作者：accomplishment（★★★★☆）
**调试经验**：
- 发现双向扩展会重复统计中心字符，需减1修正
- 使用标准库函数优化字符比较
```cpp
char a = s[n/2];
int index = n/2;
while(s[index] == a) index++, cnt++; // 右向
index = n/2;
while(s[index] == a) index--, cnt++; // 左向
cout << cnt - 1 << endl; // 修正重复计数
```

---

### 拓展练习推荐
1. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217) - 回文数的生成与质数判断
2. [P1758 最长回文子串](https://www.luogu.com.cn/problem/P1758) - Manacher算法的经典应用
3. [P1435 回文字符串](https://www.luogu.com.cn/problem/P1435) - 动态规划解决回文构造问题

---

### 关键代码实现
最优解法的完整核心逻辑：
```cpp
void solve() {
    int n;
    string s;
    cin >> n >> s;
    int center = n / 2;      // 统一处理奇偶的中心位置
    int cnt = 0;
    char target = s[center];
    
    // 向左扩展
    int left = center;
    while(left >= 0 && s[left] == target) {
        cnt++;
        left--;
    }
    
    // 向右扩展（跳过已统计的中心）
    int right = center + 1;
    while(right < n && s[right] == target) {
        cnt++;
        right++;
    }
    
    cout << cnt << endl;
}
```

---
处理用时：43.72秒