# 题目信息

# Vasya and Good Sequences

## 题目描述

Vasya has a sequence $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . Vasya may pefrom the following operation: choose some number from the sequence and swap any pair of bits in its binary representation. For example, Vasya can transform number $ 6 $ $ (\dots 00000000110_2) $ into $ 3 $ $ (\dots 00000000011_2) $ , $ 12 $ $ (\dots 000000001100_2) $ , $ 1026 $ $ (\dots 10000000010_2) $ and many others. Vasya can use this operation any (possibly zero) number of times on any number from the sequence.

Vasya names a sequence as good one, if, using operation mentioned above, he can obtain the sequence with [bitwise exclusive or](https://en.wikipedia.org/wiki/Exclusive_or) of all elements equal to $ 0 $ .

For the given sequence $ a_1, a_2, \ldots, a_n $ Vasya'd like to calculate number of integer pairs $ (l, r) $ such that $ 1 \le l \le r \le n $ and sequence $ a_l, a_{l + 1}, \dots, a_r $ is good.

## 说明/提示

In the first example pairs $ (2, 3) $ and $ (1, 3) $ are valid. Pair $ (2, 3) $ is valid since $ a_2 = 7 \rightarrow 11 $ , $ a_3 = 14 \rightarrow 11 $ and $ 11 \oplus 11 = 0 $ , where $ \oplus $ — bitwise exclusive or. Pair $ (1, 3) $ is valid since $ a_1 = 6 \rightarrow 3 $ , $ a_2 = 7 \rightarrow 13 $ , $ a_3 = 14 \rightarrow 14 $ and $ 3 \oplus 13 \oplus 14 = 0 $ .

In the second example pairs $ (1, 2) $ , $ (2, 3) $ , $ (3, 4) $ and $ (1, 4) $ are valid.

## 样例 #1

### 输入

```
3
6 7 14
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
1 2 1 16
```

### 输出

```
4
```

# AI分析结果



### 算法分类
前缀和 + 贪心优化

---

### 综合分析与结论
#### 核心思路与难点
1. **核心条件**：子数组满足两个条件：
   - 二进制 1 的总个数为偶数（异或抵消基础）
   - 最大单个数的 1 个数 ≤ 总和的一半（无法完全匹配则无法抵消）

2. **优化关键**：
   - **前缀和奇偶性**：快速统计所有总和为偶数的区间数（O(n)）
   - **有限回溯检查**：因二进制位数上限 64，只需检查前 64 个左端点即可排除非法情况（O(64n)）

3. **可视化设计**：
   - **颜色标记**：当前右端点（红色高亮）、检查区间（黄色框）、最大值变化（动态数字）
   - **动画流程**：
     1. 绘制前缀和奇偶性统计表（蓝绿交替）
     2. 右端点向右移动，每次计算时向左回溯 64 个位置
     3. 显示最大值更新过程（动态数值比较）
     4. 非法区间用闪烁红框标出，合法计数绿色增长

---

### 题解评分 (≥4星)
1. **蒟酱（5星）**  
   - 亮点：极简代码（40行）、逆向思维（先加总再减非法）、内置位计数函数优化  
   - 代码可读性高，直接体现核心逻辑  
   - 复杂度严格 O(60n) ，常数小

2. **开始新的记忆（4星）**  
   - 亮点：前缀和桶统计、显式维护最大值  
   - 代码逻辑清晰但稍显冗长  
   - 使用双重循环维护最大值，直观但效率略低

3. **Graphcity（4星）**  
   - 亮点：分治处理长短区间、显式证明匹配条件  
   - 代码简洁且包含详细注释  
   - 处理逻辑与主流解法一致，可读性较好

---

### 最优思路与代码实现
#### 关键代码（蒟酱题解）
```cpp
#include<iostream>
// ... 头文件省略 ...
constexpr int kN=3e5+1;
int n,a[kN],cnt[]={1,0},sum;
loli ans;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){loli x;cin>>x;a[i]=__builtin_popcountll(x);}
    for(int l=1;l<=n;l++){
        ans+=cnt[(sum+=a[l])&1]++;
        for(int r=l,max=0,num=0;r<=std::min(n,l+58);r++)
            max=std::max(max,a[r]),
            ans-=(num+=a[r])%2==0&&2*max>num;
    }
    cout<<ans;
}
```

#### 实现思想
1. **前缀和奇偶性桶**：`cnt[]` 记录前缀和奇偶性分布，快速统计合法区间数（O(1)）
2. **逆向检查非法区间**：对每个左端点 `l`，检查其后最多 58 个右端点 `r`，若总和为偶数但最大数超半则扣除

---

### 类似题目推荐
1. **P6569 [NOI Online #3 提高组] 魔法值**（位运算 + 矩阵快速幂）
2. **P1638 逛画展**（滑动窗口 + 统计条件）
3. **P3402 可持久化并查集**（前缀和思想 + 数据结构）

---

### 可视化设计（复古像素版）
#### 动画要素
- **像素网格**：每个数显示为 8x8 像素块，颜色深浅表示 1 的个数
- **音效触发**：
  - 合法区间：8-bit 上升音效（类似《超级玛丽》吃金币）
  - 非法区间：短促“哔”声
- **自动演示**：AI 按右端点顺序推进，回溯时显示红色扫描线

#### 代码片段（伪代码）
```javascript
// Canvas 绘制函数
function drawStep(r) {
  ctx.fillStyle = "#8B0000"; // 深红当前右端点
  ctx.fillRect(r*10, 0, 8, 8);
  for (let l = r; l >= Math.max(0, r-64); l--) {
    ctx.strokeStyle = "#FFD700"; // 金色扫描框
    ctx.strokeRect(l*10, 0, 8, 8);
    if (checkMax(l, r)) {
      playSound("error.wav"); // 非法音效
      ctx.fillStyle = "#FF0000"; 
    } else {
      playSound("coin.wav"); // 合法音效
    }
  }
}
```

---

### 个人心得摘录
> **蒟酱**：  
> “每个数的 1 个数最多 59，所以只需检查前 58 个位置，长区间自动合法”  
> —— 关键点在于利用数值上限压缩检查范围，避免暴力枚举  

> **开始新的记忆**：  
> 调试中发现未处理最大值更新的边界情况，修正后通过样例  
> —— 验证了核心条件缺一不可，需仔细检查逻辑分支

---
处理用时：72.14秒