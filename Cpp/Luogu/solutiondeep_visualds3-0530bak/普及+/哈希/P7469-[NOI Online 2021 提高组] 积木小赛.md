# 题目信息

# [NOI Online 2021 提高组] 积木小赛

## 题目描述

Alice 和 Bob 最近热衷于玩一个游戏——积木小赛。

Alice 和 Bob 初始时各有 $n$ 块积木从左至右排成一排，每块积木都被标上了一个英文小写字母。

Alice 可以从自己的积木中丢掉任意多块（也可以不丢）；Bob 可以从自己的积木中丢掉最左边的一段连续的积木和最右边的一段连续的积木（也可以有一边不丢或者两边都不丢）。两人都不能丢掉自己所有的积木。然后 Alice 和 Bob 会分别将自己剩下的积木按原来的顺序重新排成一排。

Alice 和 Bob 都忙着去玩游戏了，于是想请你帮他们算一下，有多少种不同的情况下他们最后剩下的两排积木是相同的。

两排积木相同，当且仅当这两排积木块数相同且每一个位置上的字母都对应相同。

两种情况不同，当且仅当 Alice（或者 Bob）剩下的积木在两种情况中不同。

## 说明/提示

对于所有测试点：$1\le n \le 3000$，$s$ 与 $t$ 中只包含英文小写字母。

测试点 $1$ 满足：$n\le3000$，$s$ 与 $t$ 中只包含同一种字母。

测试点 $2,3,4$ 满足：$n\le100$。

测试点 $5,6,7$ 满足：$n\le500$。

测试点 $8,9,10$ 满足：$n\le3000$。

感谢 [w33z8kqrqk8zzzx33](https://www.luogu.com.cn/user/220037) 提供测试数据。

## 样例 #1

### 输入

```
5
bcabc
bbcca```

### 输出

```
9```

## 样例 #2

### 输入

```
20
egebejbhcfabgegjgiig
edfbhhighajibcgfecef```

### 输出

```
34```

# AI分析结果



# [NOI Online 2021 提高组] 积木小赛 题解分析

## 一、算法分类
**哈希 + 贪心匹配**

## 二、核心思路与难点解析
### 核心思路
1. **枚举策略**：枚举 `t` 的所有子串 `t[i..j]`
2. **贪心匹配**：对每个子串，使用双指针在 `s` 中贪心匹配子序列
3. **哈希去重**：将合法子串哈希值存入数组，排序后去重统计

### 解决难点
1. **子序列验证**：通过维护指针 `p` 在 `s` 中跳跃式匹配，保证 O(n²) 时间复杂度
2. **去重优化**：采用大模数哈希避免冲突，排序后使用 `unique` 去重

## 三、优质题解推荐（≥4星）

### 1. [syksykCCC] 哈希+双指针（★★★★☆）
**核心代码片段**：
```cpp
for(int i = 1; i <= n; i++) {
    long long v = 0; int p = 1;
    for(int j = i; j <= n; j++) {
        while(p <= n && a[p] != b[j]) p++;
        if(p > n) break;
        p++;
        v = (1LL * v * BASE + b[j] - 'a' + 1) % M;
        t[++t[0]] = v;
    }
}
sort(t + 1, t + t[0] + 1);
printf("%d\n", unique(t + 1, t + t[0] + 1) - t - 1);
```
**亮点**：
- 单次遍历完成哈希值生成
- 简洁高效的双指针实现

### 2. [Karry5307] 子序列自动机（★★★★☆）
**核心技巧**：
```cpp
for(int i = n; i >= 1; --i) {
    memcpy(nxt[i-1], nxt[i], sizeof(nxt[i]));
    nxt[i-1][s[i]-'a'] = i;
}
```
**优势**：
- 预处理每个字符的最近位置
- O(1) 时间完成子序列验证

### 3. [KSToki] 哈希预处理（★★★★☆）
**优化点**：
- 预处理所有子串的哈希值
- 结合双指针在匹配时直接调用

## 四、关键算法可视化设计

### 动画演示方案
```javascript
// 伪代码示例
function visualize() {
    for (let i = 1; i <= n; i++) {
        highlight(`当前起始点 i=${i}`, 'blue');
        let p = 1;
        for (let j = i; j <= n; j++) {
            while (p <= n && s[p] != t[j]) {
                highlightBlock(s, p, 'gray'); 
                p++;
            }
            if (p > n) break;
            highlightBlock(s, p, 'green');
            p++;
            updateHashDisplay(t[i..j]);
            playSound('match');
        }
    }
}
```

### 复古像素风格要素
1. **颜色方案**：
   - `s` 字符串：青色像素块
   - `t` 当前子串：黄色边框
   - 匹配指针：闪烁红色方块
2. **音效设计**：
   - 指针移动：8-bit "blip" 音效
   - 成功匹配：上升音阶
   - 哈希更新：电子合成音

## 五、同类型题目推荐
1. [P3975 弦论](https://www.luogu.com.cn/problem/P3975)（后缀自动机应用）
2. [P2408 不同子串个数](https://www.luogu.com.cn/problem/P2408)（哈希/SAM去重）
3. [P4112 最短不公共子串](https://www.luogu.com.cn/problem/P4112)（双自动机交互）

## 六、核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3005, BASE = 51971;
const long long M = 2005091020050911;

int main() {
    int n; char a[N], b[N];
    scanf("%d %s %s", &n, a + 1, b + 1);
    vector<long long> hashes;
    
    for (int i = 1; i <= n; ++i) {
        long long hash = 0;
        int p = 1;
        for (int j = i; j <= n; ++j) {
            while (p <= n && a[p] != b[j]) ++p;
            if (p > n) break;
            ++p;
            hash = (hash * BASE + b[j] - 'a' + 1) % M;
            hashes.push_back(hash);
        }
    }
    
    sort(hashes.begin(), hashes.end());
    int ans = unique(hashes.begin(), hashes.end()) - hashes.begin();
    printf("%d\n", ans);
    return 0;
}
```

## 七、扩展思考
**哈希冲突优化**：可采用双哈希（如 BASE1/MOD1 + BASE2/MOD2）提升准确性。当数据规模达到 1e5 级别时，需改用后缀自动机等更稳定的结构。

---
处理用时：70.60秒