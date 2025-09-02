# 题目信息

# [USACO2.1] 顺序的分数 Ordered Fractions

## 题目描述

输入一个自然数 $n$，对于一个最简分数 $a/b$（分子和分母互质的分数），满足 $1 \le b \le n,0 \le a/b \le 1$，请找出所有满足条件的分数。

这有一个例子，当 $n=5$ 时，所有解为：

$$\frac01,\frac15,\frac14,\frac13,\frac25,\frac12,\frac35,\frac23,\frac34 ,\frac45,\frac11$$

给定一个自然数 $n$，请编程按分数值递增的顺序输出所有解。
 
注：   
1、$0$ 和任意自然数的最大公约数就是那个自然数。    
2、互质指最大公约数等于1的两个自然数。


## 说明/提示

【数据范围】    
对于 $100\%$ 的数据，$1\le n \le 160$。

USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
5
```

### 输出

```
0/1
1/5
1/4
1/3
2/5
1/2
3/5
2/3
3/4
4/5
1/1
```

# AI分析结果



### 综合分析与结论
本题核心是生成满足条件的最简分数并按序排列。题解主要分为两类：分治法（利用Stern-Brocot树生成有序分数）与枚举+排序法（暴力枚举后排序）。分治法在时间复杂度（O(n)）和代码简洁性上显著优于枚举法（O(n² logn)），但需要数学证明支持。枚举法直观但需处理重复和排序。

---

### 精选题解（评分≥4星）

#### 1. 浮尘ii（5星）
**关键亮点**：  
- **Stern-Brocot树分治**，无需排序直接生成有序序列  
- 数学证明支撑每个分数的最简性  
- 代码极度简洁（仅10行核心递归逻辑）  
**核心代码**：
```cpp
void DFS(int l1, int l2, int r1, int r2) {
    if(l2 + r2 > N) return; // 分母超限终止
    DFS(l1, l2, l1+r1, l2+r2); // 左子树递归
    printf("%d/%d\n", l1+r1, l2+r2); // 输出中间分数
    DFS(l1+r1, l2+r2, r1, r2); // 右子树递归
}
```
**个人心得**：作者提到该方法来源于"分数树"题目，体现算法迁移能力。

#### 2. 开挂老司机（4星）
**关键亮点**：  
- **二分法实现分治思路**，与Stern-Brocot异曲同工  
- 代码更易理解，适合分治入门  
**核心代码**：
```cpp
void binary(int l1,int l2,int r1,int r2) {
    int sum1=l1+r1, sum2=l2+r2;
    if(sum2>n) return;
    binary(l1,l2,sum1,sum2); // 左递归
    printf("%d/%d\n",sum1,sum2);
    binary(sum1,sum2,r1,r2); // 右递归
}
```

#### 3. 重回巅峰！（4星）
**关键亮点**：  
- **Pascal代码展示分治通用性**  
- 变量命名清晰（midx/midy表中间分数）  
**核心代码**：
```pascal
procedure work(a,b,c,d:longint);
begin
    midx:=a+c; midy:=b+d;
    if midy>n then exit;
    work(a,b,midx,midy); // 左递归
    writeln(midx,'/',midy);
    work(midx,midy,c,d); // 右递归
end;
```

---

### 关键思路总结
**Stern-Brocot树分治法**：  
1. **数学基础**：对任意相邻分数a/b < c/d，插入(a+c)/(b+d)必为最简且位于两者之间  
2. **实现步骤**：  
   - 初始化区间(0/1, 1/1)  
   - 递归生成中间分数并输出  
   - 终止条件：分母超过n  
3. **优势**：O(n)时间复杂度，无需存储排序

---

### 拓展建议
1. **同类型题**：  
   - P1495 法雷数列（Stern-Brocot直接应用）  
   - P2651 添加括号III（分数运算与最简性判断）  
   - P1378 油滴扩展（分治思想应用）
2. **优化技巧**：  
   - 分治法的数学证明可参考《具体数学》第四章  
   - 枚举法中可用「分子分母交换比较」避免浮点精度问题

---

### 重点代码片段（分治法C++实现）
```cpp
#include <iostream>
using namespace std;
int N;

void DFS(int l1, int l2, int r1, int r2) {
    if(l2 + r2 > N) return;
    DFS(l1, l2, l1+r1, l2+r2);
    printf("%d/%d\n", l1+r1, l2+r2);
    DFS(l1+r1, l2+r2, r1, r2);
}

int main() {
    cin >> N;
    printf("0/1\n");
    DFS(0, 1, 1, 1);
    printf("1/1\n");
}
```

---
处理用时：57.25秒