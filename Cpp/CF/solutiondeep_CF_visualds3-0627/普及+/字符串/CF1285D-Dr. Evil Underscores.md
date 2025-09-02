# 题目信息

# Dr. Evil Underscores

## 题目描述

Today, as a friendship gift, Bakry gave Badawy $ n $ integers $ a_1, a_2, \dots, a_n $ and challenged him to choose an integer $ X $ such that the value $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ is minimum possible, where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

As always, Badawy is too lazy, so you decided to help him and find the minimum possible value of $ \underset{1 \leq i \leq n}{\max} (a_i \oplus X) $ .

## 说明/提示

In the first sample, we can choose $ X = 3 $ .

In the second sample, we can choose $ X = 5 $ .

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2
1 5```

### 输出

```
4```

# AI分析结果



## 唯一算法分类
**分治（隐式Trie）**

---

## 综合分析与结论
### 核心思路与难点
题目要求找到使所有数异或X后的最大值最小。核心思路是**按位分治**：
1. **从高位到低位处理**，高位的选择权对结果影响更大
2. 将当前位为0/1的数分成两组：
   - 若仅存一组，该位可归零，递归处理低位
   - 若两组共存，该位必为1，取两组递归结果的最小值+当前位值
3. 递归终止条件为处理完所有位或数组为空

### 算法可视化设计
- **动态分组展示**：用不同颜色高亮当前处理的位数，动画展示数组分裂为0/1两组的过程
- **贡献值标记**：当必须加上当前位值时，用闪动特效显示2^k的累加
- **递归层级树**：用缩进或层级连线展示递归调用结构
- **复古像素风格**：用8-bit风格的色块表示数组元素，位处理过程类似俄罗斯方块下落，音效在分组时触发经典FC音效

---

## 题解评分（≥4星）
1. **基地A_I（5星）**
   - **亮点**：代码最简洁，递归逻辑清晰，无需显式建树
   - **核心代码**：
     ```cpp
     int Solve(vector<int> p,int K) {
         if(p.empty() || K<0) return 0;
         vector<int> p1,p2;
         for(int x:p) (x&(1<<K)) ? p1.push_back(x) : p2.push_back(x);
         if(p1.empty()) return Solve(p2,K-1);
         if(p2.empty()) return Solve(p1,K-1);
         return (1<<K) + min(Solve(p1,K-1), Solve(p2,K-1));
     }
     ```

2. **EternalHeart1314（4星）**
   - **亮点**：函数式分治实现，通过vector传递分组
   - **关键逻辑**：
     ```cpp
     int dfs(VI a, int bit) {
         if(!bit) return 0;
         VI b,c; --bit;
         for(int x:a) (x>>bit&1)?b.pb(x):c.pb(x);
         if(b.empty()) return dfs(c,bit);
         if(c.empty()) return dfs(b,bit);
         return (1<<bit) + min(dfs(b,bit), dfs(c,bit));
     }
     ```

3. **little_sun（4星）**
   - **亮点**：显式Trie实现，树形DP思路清晰
   - **树形DP核心**：
     ```cpp
     int query(int x, int k) {
         if (!num[x]) return 0;
         int ans = 1e9;
         if (ch[x][0]) ans = min(ans, query(ch[x][0], k>>1));
         if (ch[x][1]) ans = min(ans, query(ch[x][1], k>>1));
         return (num[x]==1 ? ans : ans + k);
     }
     ```

---

## 核心代码实现
**基地A_I的分治解法完整代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int Solve(vector<int> p, int K) {
    if(p.empty() || K<0) return 0;
    vector<int> p1,p2;
    for(int x:p) (x&(1<<K)) ? p1.push_back(x) : p2.push_back(x);
    if(p1.empty()) return Solve(p2,K-1);
    if(p2.empty()) return Solve(p1,K-1);
    return (1<<K) + min(Solve(p1,K-1), Solve(p2,K-1));
}

int main() {
    scanf("%d",&n);
    a.resize(n);
    for(int i=0;i<n;++i) scanf("%d",&a[i]);
    printf("%d\n", Solve(a,30));
    return 0;
}
```

---

## 相似题目推荐
1. [CF1849D - XOR Construction](https://www.luogu.com.cn/problem/CF1849D)
2. [ABC281F - XOR World](https://www.luogu.com.cn/problem/AT_abc281_f)
3. [P4592 [TJOI2018] 异或](https://www.luogu.com.cn/problem/P4592)

---

## 可视化算法演示
**8-bit风格动画设计**：
1. **初始化**：30x30像素网格，每行表示一个二进制位（高位在上）
2. **分组动画**：当前处理位高亮黄色，0组左移（蓝色块），1组右移（红色块）
3. **贡献标记**：当分组冲突时，该行闪烁红色，右侧显示+2^k
4. **音效设计**：
   - 分组成功：8-bit "coin"音效
   - 位冲突：短促警报声
   - 递归返回：不同音阶的电子音表示层级

**交互控制**：
- 空格键：暂停/继续
- 方向键：单步前进/后退
- F1：切换自动演示模式（AI自动解谜）

---

## 个人心得摘录
> "分治时传递vector会复制数据，改为传递下标优化后效率提升10倍" —— ix35  
> "突然意识到当某位必须为1时，后续只需关注较小的一半，类似启发式合并" —— been_apart

**调试经验**：递归边界处理不当会导致栈溢出，需确保空集及时返回0。分治解法中位运算的优先级容易出错，建议多用括号。

---
处理用时：84.27秒