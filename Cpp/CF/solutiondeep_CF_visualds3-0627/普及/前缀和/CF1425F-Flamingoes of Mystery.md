# 题目信息

# Flamingoes of Mystery

## 题目描述

This is an interactive problem. You have to use a flush operation right after printing each line. For example, in C++ you should use the function fflush(stdout), in Java — System.out.flush(), in Pascal — flush(output) and in Python — sys.stdout.flush().

Mr. Chanek wants to buy a flamingo to accompany his chickens on his farm. Before going to the pet shop, Mr. Chanek stops at an animal festival to have fun. It turns out there is a carnival game with a flamingo as the prize.

There are $ N $ mysterious cages, which are numbered from $ 1 $ to $ N $ . Cage $ i $ has $ A_i $ $ (0 \le A_i \le 10^3) $ flamingoes inside $ (1 \le i \le N) $ . However, the game master keeps the number of flamingoes inside a secret. To win the flamingo, Mr. Chanek must guess the number of flamingoes in each cage.

Coincidentally, Mr. Chanek has $ N $ coins. Each coin can be used to ask once, what is the total number of flamingoes inside cages numbered $ L $ to $ R $ inclusive? With $ L < R $ .

## 说明/提示

In the sample input, the correct flamingoes amount is $ [1, 4, 4, 6, 7, 8] $ .

## 样例 #1

### 输入

```
6
 
5
 
15
 
10
 ```

### 输出

```
 
? 1 2
 
? 5 6
 
? 3 4
 
! 1 4 4 6 7 8```

# AI分析结果



## 算法分类
前缀和与差分

---

## 题解思路与核心难点

### 核心思路
所有题解均基于前缀和与差分思想。通过构造前缀和数组，利用相邻询问的差值推导出大部分元素，最后通过一次额外询问解出前两个元素。核心步骤如下：
1. **前缀和构建**：询问 `1-i` 的区间和（i从2到n），得到前缀和数组。
2. **差分求值**：通过相邻前缀和的差值得出a3到an的值。
3. **前两个元素求解**：通过额外询问 `2-n` 或 `2-3` 的区间和，结合已知前缀和反推a1和a2。

### 解决难点
- **交互次数限制**：必须严格使用n次询问，需巧妙设计询问区间。
- **边界处理**：前两个元素无法直接通过差分得出，需通过整体和与部分和的差值推导。
- **缓冲区管理**：交互题需在每次输出后立即刷新缓冲区，否则会导致死锁。

---

## 题解评分（≥4星）

### 1. RioFutaba（4.5星）
- **亮点**：代码结构清晰，变量命名合理，通过一次询问 `2-n` 的和直接解出a1，逻辑简洁。
- **核心代码**：
  ```cpp
  for(int i=2;i<=n;i++){ 
      cout << "? 1 " << i << endl;
      cin >> res[i];
      a[i] = res[i] - res[i-1];
  }
  cout << "? 2 " << n << endl;
  cin >> x;
  a[1] = res[n] - x; 
  a[2] = res[2] - a[1];
  ```

### 2. ZQIN_P（4星）
- **亮点**：使用 `2-3` 的询问推导a2，更直观展示差分思想。
- **核心代码**：
  ```cpp
  cout<<"? 1 2"<<endl;
  cin>>num1;
  for(int i=3;i<=n;i++){
      cout<<"? 1 "<<i<<endl;
      cin>>num2;
      a[i] = num2 - num1;
      num1 = num2;
  }
  cout<<"? 2 3"<<endl;
  cin>>num2;
  a[2] = num2 - a[3];
  a[1] = num - a[2];
  ```

### 3. hzoi_Shadow（4星）
- **亮点**：代码注释完整，强调缓冲区管理，适合新手学习。
- **核心代码**：
  ```cpp
  cout<<"? 1 2"<<endl;
  fflush(stdout);
  cin>>sum[2];
  for(i=3;i<=n;i++){
      cout<<"? 1 "<<i<<endl;
      fflush(stdout);
      cin>>sum[i];
      a[i]=sum[i]-sum[i-1];
  }
  ```

---

## 最优技巧提炼
1. **前缀和链式推导**：通过 `1-i` 的连续询问构造前缀和链，利用相邻差值直接求出a3到an。
2. **整体和反推法**：通过最后一次询问部分区间的和，结合总和反推前两个元素，例如 `a1 = total_sum - sum(2-n)`。
3. **交互题缓冲技巧**：在C++中使用 `endl` 自动刷新缓冲区，避免手动调用 `fflush`。

---

## 相似题目推荐
1. **洛谷P1115**：最大子段和（前缀和极值问题）。
2. **CF1772B**：矩阵旋转判断（交互式推理）。
3. **洛谷P3131**：子序列模7问题（前缀和与模运算结合）。

---

## 可视化算法设计

### 动画方案
1. **网格展示**：用Canvas绘制一排笼子，初始为问号。每次询问后，根据回答填充对应区间的和。
2. **差分高亮**：当计算a3到an时，用颜色标记相邻前缀和的差值区域。
3. **前两元素推导**：用闪烁效果突出最后一次询问的区间，并用箭头标注总和与部分和的关系。

### 复古像素风格
- **颜色方案**：8位色调色板，笼子用绿色像素块，已求解元素用黄色，当前操作区用红色边框。
- **音效设计**：
  - **询问时**：播放短促的"哔"声。
  - **求解成功**：播放经典马里奥过关音效。
- **自动演示**：按固定间隔逐步执行询问和计算，右侧面板显示当前推导公式。

---

## 核心代码实现（RioFutaba版本）
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e3+5;
int n, a[maxn], res[maxn], x;
int main() {
    cin >> n;
    for (int i=2; i<=n; i++) { 
        cout << "? 1 " << i << endl;
        cin >> res[i];
        a[i] = res[i] - res[i-1];
    }
    cout << "? 2 " << n << endl;
    cin >> x;
    a[1] = res[n] - x;
    a[2] = res[2] - a[1];
    cout << "!";
    for (int i=1; i<=n; i++) cout << " " << a[i];
    cout << endl;
    return 0;
}
```

---
处理用时：222.72秒