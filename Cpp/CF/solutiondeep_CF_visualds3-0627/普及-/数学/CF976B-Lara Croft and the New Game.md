# 题目信息

# Lara Croft and the New Game

## 题目描述

You might have heard about the next game in Lara Croft series coming out this year. You also might have watched its trailer. Though you definitely missed the main idea about its plot, so let me lift the veil of secrecy.

Lara is going to explore yet another dangerous dungeon. Game designers decided to use good old 2D environment. The dungeon can be represented as a rectangle matrix of $ n $ rows and $ m $ columns. Cell $ (x,y) $ is the cell in the $ x $ -th row in the $ y $ -th column. Lara can move between the neighbouring by side cells in all four directions.

Moreover, she has even chosen the path for herself to avoid all the traps. She enters the dungeon in cell $ (1,1) $ , that is top left corner of the matrix. Then she goes down all the way to cell $ (n,1) $ — the bottom left corner. Then she starts moving in the snake fashion — all the way to the right, one cell up, then to the left to the cell in $ 2 $ -nd column, one cell up. She moves until she runs out of non-visited cells. $ n $ and $ m $ given are such that she always end up in cell $ (1,2) $ .

Lara has already moved to a neighbouring cell $ k $ times. Can you determine her current position?

## 说明/提示

Here is her path on matrix $ 4 $ by $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1

### 输入

```
4 3 0
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
4 3 11
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
4 3 7
```

### 输出

```
3 2
```

# AI分析结果



## 唯一算法分类
组合数学

## 综合分析与结论
题目要求计算Lara在特定蛇形路径下移动k次后的坐标。核心思路是将路径分为两部分处理，通过数学推导直接计算位置，避免模拟。

### 核心思路
1. **第一部分**：垂直向下移动至(n,1)。当k <n时，坐标可直接得出。
2. **第二部分**：蛇形移动。计算剩余步数k1，通过商和余数确定行数和列方向：
   - 行数 = n - (k1/(m-1))，每行消耗(m-1)步。
   - 商的奇偶性决定列方向：偶数向右，奇数向左。

### 关键公式
- 行数：`x = n - (k1/(m-1))`
- 列方向：
  - 商为偶数：`y = 余数 + 2`
  - 商为奇数：`y = m - 余数`

### 可视化设计
- **动画方案**：用不同颜色区分移动方向，高亮当前计算的行和余数。
- **复古像素风格**：8-bit网格显示路径，Lara移动时播放音效。
- **控制面板**：支持步进、速度调节，实时显示商和余数的计算过程。

---

## 题解清单（评分≥4星）
### 1. wwwidk1234（5星）
- **亮点**：思路清晰，代码简洁，数学推导完整。
- **关键代码**：
  ```cpp
  if((k1/(m-1))%2==1) 
    cout<<n-k1/(m-1)<<" "<<m-k1%(m-1);
  else 
    cout<<n-k1/(m-1)<<" "<<k1%(m-1)+2;
  ```

### 2. GordonLu（4星）
- **亮点**：代码极简，直接利用商的奇偶性判断列方向。
- **代码片段**：
  ```cpp
  if ((n-l)%2==0) 
    cout << k+2;
  else 
    cout << m-k;
  ```

### 3. felixshu（4星）
- **亮点**：变量命名明确，分奇偶情况处理列方向。
- **核心逻辑**：
  ```cpp
  if(k/(m-1) %2==1) y = m -余数;
  else y = 余数 +2;
  ```

---

## 最优思路提炼
- **分阶段处理**：将路径拆分为垂直和蛇形阶段。
- **商与余数的应用**：用整除运算确定行数，余数定位列。
- **奇偶性判断方向**：避免模拟的关键，直接推导列位置。

---

## 同类型题目推荐
1. **P1003 铺地毯**：通过数学计算覆盖点的最后地毯。
2. **P3612 [USACO17JAN] Secret Cow Code S**：分形结构的数学规律分析。
3. **P1255 数楼梯**：模式观察与递推优化。

---

## 个人心得摘录
- **数据范围**：必须使用`long long`避免溢出。
- **边界处理**：k=0和k刚好完成第一部分的情况需特判。
- **方向推导**：商的奇偶性与行列方向的关系是解题关键。

---

## 代码实现（核心数学逻辑）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    long long n, m, k;
    cin >> n >> m >> k;
    if (k < n) {
        cout << k+1 << " 1";
        return 0;
    }
    long long k1 = k - n;
    long long row = n - k1/(m-1);
    long long rem = k1 % (m-1);
    if ((k1/(m-1)) % 2 == 1) 
        cout << row << " " << m - rem;
    else 
        cout << row << " " << rem + 2;
}
```

---

## 可视化与复古动画设计
- **Canvas绘制**：网格动态生成，移动路径用像素块标记。
- **音效触发**：步进时播放"beep"声，方向变化时音调不同。
- **自动推导模式**：模拟AI自动计算商和余数，分步高亮。

---
处理用时：277.88秒