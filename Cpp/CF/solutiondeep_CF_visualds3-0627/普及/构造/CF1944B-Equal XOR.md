# 题目信息

# Equal XOR

## 题目描述

You are given an array $ a $ of length $ 2n $ , consisting of each integer from $ 1 $ to $ n $ exactly twice.

You are also given an integer $ k $ ( $ 1 \leq k \leq \lfloor \frac{n}{2} \rfloor  $ ).

You need to find two arrays $ l $ and $ r $ each of length $ \mathbf{2k} $ such that:

- $ l $ is a subset $ ^\dagger $ of $ [a_1, a_2, \ldots a_n] $
- $ r $ is a subset of $ [a_{n+1}, a_{n+2}, \ldots a_{2n}] $
- [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of elements of $ l $ is equal to the bitwise XOR of elements of $ r $ ; in other words, $ l_1 \oplus l_2 \oplus \ldots \oplus l_{2k} = r_1 \oplus r_2 \oplus \ldots \oplus r_{2k} $

It can be proved that at least one pair of $ l $ and $ r $ always exists. If there are multiple solutions, you may output any one of them.

 $ ^\dagger $ A sequence $ x $ is a subset of a sequence $ y $ if $ x $ can be obtained by deleting several (possibly none or all) elements of $ y $ and rearranging the elements in any order. For example, $ [3,1,2,1] $ , $ [1, 2, 3] $ , $ [1, 1] $ and $ [3, 2] $ are subsets of $ [1, 1, 2, 3] $ but $ [4] $ and $ [2, 2] $ are not subsets of $ [1, 1, 2, 3] $ .

## 说明/提示

In the first test case, we choose $ l=[2,1] $ and $ r=[2,1] $ . $ [2, 1] $ is a subset of $ [a_1, a_2] $ and $ [2, 1] $ is a subset of $ [a_3, a_4] $ , and $ 2 \oplus 1 = 2 \oplus 1 = 3 $ .

In the second test case, $ 6 \oplus 4 = 1 \oplus 3 = 2 $ .

## 样例 #1

### 输入

```
4
2 1
1 2 2 1
6 1
6 4 2 1 2 3 1 6 3 5 5 4
4 1
1 2 3 4 1 2 3 4
6 2
5 1 3 3 5 1 2 6 4 6 4 2```

### 输出

```
2 1
2 1
6 4
1 3
1 2
1 2
5 1 3 3
6 4 2 4```

# AI分析结果



---

### 算法分类
**构造**

---

### 核心思路与难点分析
**题目核心**：利用异或性质构造两个等长子数组，使异或和相等。  
**关键思路**：
1. **两次出现的数**：每个数出现两次的成对选入，异或贡献为0。
2. **一次出现的数**：成对选入两边，保证异或和同步变化。

**解决难点**：
- 发现两次出现的数对异或无影响，优先填充此类数。
- 剩余位置用一次出现的数对填充，确保两边异或同步变化。

---

### 题解评分（≥4星）

1. **jiangchen1234（5星）**  
   - 思路清晰，分步骤处理两次和一次出现的数。
   - 代码结构简洁，变量命名合理。
   - 直接利用哈希表统计频次，逻辑严谨。

2. **Blikewsr（4星）**  
   - 使用分类统计优化代码，但变量命名稍显混乱。
   - 核心逻辑明确，分两次填充与补充填充。

3. **Shadow_T（4星）**  
   - 提出分频次处理，但代码可读性略低。
   - 核心思路一致，但实现细节不够直观。

---

### 最优思路提炼
1. **成对填充**：优先选择两次出现的数，成对加入两数组，异或和为0。
2. **对称补充**：剩余位置用一次出现的数对填充，保证两边异或同步变化。
3. **频次对称性**：前半段和后半段两次出现的数的数量相等，确保构造可行性。

---

### 同类型题与算法套路
- **通用套路**：  
  利用数学性质（如异或、奇偶性）构造解，常见于构造类题目。
- **相似题目**：  
  - CF1594B（利用二进制构造特定数值）
  - CF1385D（分治构造满足条件字符串）
  - 洛谷 P1631（序列合并构造）

---

### 推荐洛谷题目
1. **P1469** - 找筷子（异或性质应用）
2. **P1631** - 序列合并（构造有序序列）
3. **P3919** - 可持久化数组（分块构造）

---

### 核心代码实现（jiangchen1234）
```cpp
void solve() {
    mp1.clear(); mp2.clear();
    int n = read(), k = read();
    // 统计前半部分频次
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        ++mp1[a[i]];
    }
    // 统计后半部分频次
    for (int i = 1; i <= n; ++i) {
        b[i] = read();
        ++mp2[b[i]];
    }
    // 处理两次出现的数
    for (int i = 1; i <= n; ++i) {
        if (mp1[a[i]] == 2 && len1 <= 2 * k - 2) {
            ans1[len1++] = a[i];
            ans1[len1++] = a[i];
            mp1[a[i]] = 0;
        }
    }
    // 对称处理后半部分
    for (int i = 1; i <= n; ++i) {
        if (mp2[b[i]] == 2 && len2 <= 2 * k - 2) {
            ans2[len2++] = b[i];
            ans2[len2++] = b[i];
            mp2[b[i]] = 0;
        }
    }
    // 填充一次出现的数对
    for (int i = 1; i <= n; ++i) {
        if (len1 < 2 * k && mp1[a[i]] == 1) {
            ans1[len1++] = a[i];
            ans2[len2++] = a[i];
        }
    }
    // 输出结果
    for (int i = 0; i < 2*k; ++i) cout << ans1[i] << " ";
    cout << endl;
    for (int i = 0; i < 2*k; ++i) cout << ans2[i] << " ";
    cout << endl;
}
```

---

### 可视化设计
**动画方案**：
1. **分块显示**：用两个矩形区域表示前半和后半数组，元素按出现频次着色（两次为绿色，一次为黄色）。
2. **成对填充**：绿色元素自动成对跳转到答案区，播放“滴”音效。
3. **对称补充**：黄色元素成对跳转，播放“嗒”音效，高亮同步填充过程。
4. **异或和跟踪**：实时显示当前异或值，填充完成后显示“✔”动画。

**复古风格**：
- **8位像素UI**：使用16色调色板，元素用8x8像素块表示。
- **音效设计**：  
  - 成对填充：8-bit“确认”音效（短促高频）。
  - 完成构造：经典FC过关音乐片段。
- **自动演示**：按步骤自动执行，支持暂停/步进观察填充逻辑。

**交互示例**：  
[查看在线演示](https://example.com/xor-visualizer)（伪链接，需实际部署）

---
处理用时：84.89秒