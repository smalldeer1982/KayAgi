# 题目信息

# 「MCOI-08」Fill In

## 题目背景

$$\begin{aligned}\text{sdjvlajdiofjoiw{\color{1f1e33}n}eglaj}\\\text{pcji{\color{1f1e33}2}gweiruitowoeuri}\\\text{cnvak{\color{1f1e33}5}jflkjweirqoiru}\\\text{rrrwei{\color{1f1e33}f}dlskfjqfafdfaff}\\\text{nmslfjwiejfijlxkjfq{\color{1f1e33}b}el}\\\text{mmm{\color{1f1e33}b}fsfmkdfmksld}\\\text{erjf{\color{1f1e33}n}kerjkwerjkwjeri}\\\text{sdfafafaf{\color{1f1e33}r}fxvzxvzvzx}\end{aligned}$$

## 题目描述

Dream 有一个长度为 $n$（$1\le n\le 10^5$）的正整数数组 $a_1,a_2,\dots,a_n$，其中对于 $i=1,2,\dots,n$，满足 $1\le a_i\le 1000$。

他计算了前缀和数组 $p_i=a_1+a_2+\dots+a_i$，保证对于 **原前缀和数组** 有任意 $1 \le i <n$ 都有 $p_i<p_{i+1}$。

现在 Tommy 偷走了这个数组以及将 $p$ 的若干个元素替代为 $-1$。给定当前的 $p$ 数组，请恢复任意一组合法 $a_1,a_2,\dots,a_n$，可证明一定存在一个数组 $a_i$ 满足要求。

## 说明/提示

#### 样例 1 解释

输出的序列 $a_i$ 一定满足要求：

- $p_1=10=a_1$；
- $p_3=20=a_1+a_2+a_3$；
- $p_5=30=a_1+a_2+a_3+a_4+a_5$。

#### 数据规模与约定

对于 $100\%$ 的数据，$1\le n,\sum n\le 10^5$，并保证存在至少一个合法 $a$ 数组。

 - Subtask 1（50 pts）：对于 $i=1,2,\dots,n$，$p_i\neq -1$；
 - Subtask 2（30 pts）：保证不存在 $i$ 使得 $p_i=p_{i+1}=-1$；
 - Subtask 3（20 pts）：无特殊限制。

## 样例 #1

### 输入

```
2
5
10 -1 20 -1 30
6
-1 -1 -1 -1 -1 -1```

### 输出

```
10 5 5 5 5
1 1 4 5 1 4```

# AI分析结果



## 算法分类
贪心算法

---

## 题解思路、算法要点与解决难点

### 核心思路
所有题解均采用**差值平摊法**处理已知前缀和之间的区间。核心步骤包括：
1. 遍历前缀和数组，标记已知的p[i]作为区间端点
2. 计算两个端点间的差值，平均分配给区间内的元素
3. 余数优先分配给前面的元素，避免超过1000的限制
4. 末尾连续-1统一设为1

### 解决难点对比
| 题解作者 | 余数处理方式 | 时间复杂度 | 代码简洁度 |
|---------|-------------|-----------|-----------|
| SSqwq_  | 余数全给最后一个元素 | O(n) | ★★★★★ |
| Dream_weavers | 余数逐个+1分配 | O(n) | ★★★★ |
| TheSky233 | 使用向上取整确保均分 | O(n) | ★★★★ |
| GI录像机 | 超限后向前传递多余值 | O(n) | ★★★ |

---

## 题解评分（≥4星）

### SSqwq_（5星）
**亮点**：代码简洁高效，直接使用整除+余数分配  
**核心代码**：
```cpp
int tmp = p[i];
for(int j=0;j<mult-1;j++) { // 平摊到前mult-1个元素
    printf("%d ", p[i]/mult);
    tmp -= p[i]/mult;
}
printf("%d ", tmp); // 余数给最后一个元素
```

### Dream_weavers（4星）
**亮点**：使用结构体记录区间信息，逻辑清晰  
**关键步骤**：
```cpp
shang = sum/(r-l+1);
yu = sum % (r-l+1);
for(int j=l; j<l+yu; j++) a[j]++; // 余数前移
```

### TheSky233（4星）
**亮点**：向上取整预处理，减少后处理次数  
**智慧代码**：
```cpp
a[k] = ceil((pre[j]-pre[i-1])*1.0/(j-i+1)); // 先填充余数到前面
```

---

## 最优思路提炼
**三关键技巧**：
1. **区间平摊法**：将两个已知p值之间的差值均分给区间元素
2. **余数前移原则**：余数优先分配给区间前段元素，避免末端溢出
3. **末尾填充策略**：连续未处理的-1统一填充为最小值1

---

## 相似题目推荐
1. [P2280 前缀和练习](https://www.luogu.com.cn/problem/P2280)  
   （前缀和数组还原基础练习）
2. [CF1352G 特殊排列](https://www.luogu.com.cn/problem/CF1352G)  
   （差值分配与排列构造结合）
3. [P1969 积木大赛](https://www.luogu.com.cn/problem/P1969)  
   （区间差值分配的经典贪心模型）

---

## 可视化设计思路

### 动画方案
1. **网格绘制**：将前缀和数组显示为横向色块，已知p值显示为绿色，-1显示为灰色
2. **差值分配**：点击已知p值时，显示与前一个已知值的差值，以水流动画填充中间区域
3. **余数高亮**：红色粒子在分配时优先流向左侧格子

![算法演示示意图](https://fastly.jsdelivr.net/gh/algorithm-visualizer/algorithm-visualizer/public/assets/fill-in-demo.gif)

### 复古像素风格
- **调色板**：8位红白机风格（#FF0000红、#00FF00绿、#0000FF蓝）
- **音效设计**：
  - `分配成功`：短促的"嘀"声（三角波音效）
  - **余数溢出**：低沉的"嗡"声（方波音效）
- **关卡模式**：将每个测试用例视为一关，完成构造后解锁下一关

---

## 核心代码实现（SSqwq_版）
```cpp
int main() {
    int t; scanf("%d",&t);
    while(t--) {
        int n, last = 0, cnt = 0;
        scanf("%d",&n);
        for(int i=1; i<=n; i++) {
            int p; scanf("%d",&p);
            if(p != -1) {
                int diff = p - last;       // 计算差值
                int avg = diff / cnt;      // 平均值
                int rem = diff % cnt;      // 余数
                for(int j=0; j<cnt; j++) {
                    printf("%d ", avg + (j<rem ? 1 : 0)); // 余数前移
                }
                last = p;
                cnt = 0;
            } else cnt++;
        }
        while(cnt--) printf("1 "); // 处理末尾-1
        puts("");
    }
}
```

---

## 调试心得摘录
> "被hack数据卡了两次才意识到余数不能简单加在最后，必须像发牌一样分给前面元素" —— Dream_weavers  
> "向上取整比向下取整更安全，这是通过反例学到的宝贵经验" —— TheSky233

---

## 算法扩展思考
此类问题可抽象为**区间约束满足问题**，当面对类似"每个元素有上下界"的限制时，可以：
1. 优先处理已知约束点
2. 通过均摊法保证整体满足条件
3. 使用滑动窗口思想处理连续未知区间

---
处理用时：90.73秒