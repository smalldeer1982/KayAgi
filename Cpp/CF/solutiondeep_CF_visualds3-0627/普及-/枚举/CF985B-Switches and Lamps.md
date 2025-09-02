# 题目信息

# Switches and Lamps

## 题目描述

You are given $ n $ switches and $ m $ lamps. The $ i $ -th switch turns on some subset of the lamps. This information is given as the matrix $ a $ consisting of $ n $ rows and $ m $ columns where $ a_{i,j}=1 $ if the $ i $ -th switch turns on the $ j $ -th lamp and $ a_{i,j}=0 $ if the $ i $ -th switch is not connected to the $ j $ -th lamp.

Initially all $ m $ lamps are turned off.

Switches change state only from "off" to "on". It means that if you press two or more switches connected to the same lamp then the lamp will be turned on after any of this switches is pressed and will remain its state even if any switch connected to this lamp is pressed afterwards.

It is guaranteed that if you push all $ n $ switches then all $ m $ lamps will be turned on.

Your think that you have too many switches and you would like to ignore one of them.

Your task is to say if there exists such a switch that if you will ignore (not use) it but press all the other $ n-1 $ switches then all the $ m $ lamps will be turned on.

## 样例 #1

### 输入

```
4 5
10101
01000
00111
10000
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 5
10100
01000
00110
00101
```

### 输出

```
NO
```

# AI分析结果



---

# Switches and Lamps 题解分析

## 算法分类
**模拟**

---

## 题解思路与核心难点

### 核心思路
1. **统计每个灯被多少开关控制**  
   使用数组 `cnt[j]` 记录第 `j` 盏灯被多少个开关连接。若 `cnt[j] = 1`，则该灯只能被唯一一个开关控制。
2. **枚举每个开关并检查是否冗余**  
   对每个开关 `i`，检查其控制的每盏灯 `j`。若存在某个 `j` 使得 `cnt[j] = 1` 且开关 `i` 控制 `j`，则开关 `i` 不可被忽略。否则，开关 `i` 可被移除。

### 解决难点
- **高效判断冗余开关**：通过预处理 `cnt` 数组，将判断时间复杂度从 O(n^3) 优化到 O(nm)。
- **关键数据结构**：仅需一个长度为 `m` 的数组存储每盏灯的控制次数。

---

## 题解评分 (≥4星)

### 1. AutumnKite（★★★★☆）
- **亮点**：思路清晰，代码简洁，时间复杂度 O(nm)。
- **代码可读性**：变量命名规范，逻辑明确。
- **优化程度**：直接利用预处理数组，无需动态修改和恢复。

### 2. Zq_water（★★★★☆）
- **亮点**：代码极简，变量命名合理（如 `cnt` 和 `mp`）。
- **实践性**：直接遍历开关和灯，无冗余操作。

### 3. xvl_（★★★★☆）
- **亮点**：注释明确，逻辑分段清晰，适合教学。
- **思维角度**：明确指出“开关能被去掉的条件是其控制的灯均有替代开关”。

---

## 最优思路提炼

### 关键步骤
1. **预处理统计**：遍历矩阵，统计每盏灯的控制次数。
2. **开关检查**：对每个开关，检查其控制的灯是否均有其他开关可替代。

### 代码片段
```cpp
int cnt[m]; // 统计每盏灯的控制次数
for (int i = 0; i < n; i++) {
    bool can_remove = true;
    for (int j = 0; j < m; j++) {
        if (a[i][j] == '1' && cnt[j] == 1) {
            can_remove = false;
            break;
        }
    }
    if (can_remove) return "YES";
}
return "NO";
```

---

## 类似题目与算法套路

### 相似算法套路
- **依赖统计**：通过预处理统计依赖关系，再通过枚举验证条件。
- **冗余判断**：判断某元素是否冗余（如开关、边、节点等）。

### 推荐题目
1. **洛谷 P1119**：灾后重建（依赖时间窗口的连通性判断）。
2. **洛谷 P1347**：排序（拓扑排序中的冗余边判断）。
3. **洛谷 P2921**：Trick or Treat on the Farm（图的依赖关系分析）。

---

## 个人心得摘录
- **AutumnKite** 提到“优化时间复杂度时，发现预处理 `cnt` 是关键”。
- **chenyanbing2023** 尝试动态修改和恢复 `cnt`，但最终发现静态预处理更高效。
- **望月Asta** 使用 `bitset` 优化按位或操作，但实际数据量下传统方法更优。

---

## 可视化与算法演示

### 动画方案
1. **初始化阶段**  
   - 绘制 `n` 个开关和 `m` 盏灯，用网格表示矩阵。
   - 动态统计 `cnt[j]`，每统计一次，对应灯的颜色加深（如浅蓝→深蓝）。

2. **开关检查阶段**  
   - 高亮当前检查的开关（如红色边框）。
   - 遍历该开关控制的灯，若某个灯的 `cnt[j] = 1`，则将其标记为红色。
   - 若所有灯均未标红，触发“成功”动画（如绿色闪光）。

### 复古像素风格设计
- **颜色方案**：8-bit 调色板（红、蓝、绿、黄），开关为方块，灯为圆形像素。
- **音效**：  
  - 正确操作：8-bit 上升音调（类似《超级马里奥》吃金币音效）。  
  - 错误操作：短促“哔”声。
- **自动演示**：AI 按顺序遍历开关，用户可暂停观察 `cnt` 值变化。

---

## 最终代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, m, cnt[N];
char a[N][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == '1') cnt[j]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        bool can_remove = true;
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '1' && cnt[j] == 1) {
                can_remove = false;
                break;
            }
        }
        if (can_remove) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
```

---
处理用时：93.74秒