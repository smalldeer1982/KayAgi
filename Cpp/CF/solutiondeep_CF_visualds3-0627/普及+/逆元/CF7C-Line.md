# 题目信息

# Line

## 题目描述

A line on the plane is described by an equation $ Ax+By+C=0 $ . You are to find any point on this line, whose coordinates are integer numbers from $ -5·10^{18} $ to $ 5·10^{18} $ inclusive, or to find out that such points do not exist.

## 样例 #1

### 输入

```
2 5 3
```

### 输出

```
6 -3
```

# AI分析结果



# 算法分类  
扩展欧几里得算法

---

# 题解核心思路与难点对比  

## 核心算法流程  
所有题解均采用扩展欧几里得算法（exgcd）解决线性不定方程 `Ax + By = -C`，关键步骤：  
1. **方程变形**：将直线方程转换为标准不定方程形式  
2. **判断解的存在性**：通过裴蜀定理验证 `gcd(A,B) | -C`  
3. **递归求解 exgcd**：获取 `Ax + By = gcd(A,B)` 的特解  
4. **系数调整**：将特解缩放 `k = (-C)/gcd(A,B)` 倍  

## 解决难点  
1. **递归推导**：理解 exgcd 中 `x = y1, y = x1 - a/b*y1` 的变量传递关系  
2. **负数处理**：样例输入 `C` 需取反后代入方程  
3. **变量作用域**：使用全局变量或引用参数传递 `x,y` 的差异（Crab_Dave 用全局变量，Dog_Two 用引用）  
4. **整数溢出**：必须使用 `long long` 类型存储大范围数据  

## 优化手段  
- **先除后乘**：`x = (c/d)*x` 避免大数相乘溢出（KagurazakaKano 题解）  
- **最小化变量**：部分题解将 `gcd(a,b)` 与特解计算合并  

---

# 题解评分（≥4星）  

## 5星：Crab_Dave  
- **亮点**：  
  - 完整推导裴蜀定理与 exgcd 递归公式  
  - 包含通解公式与三种应用场景  
  - 代码注释清晰，处理了 `-C` 的符号  

## 4星：Dog_Two  
- **亮点**：  
  - 分模块讲解线性方程、同余方程、逆元  
  - 独立函数 `linear_Eqa` 封装解判断逻辑  

## 4星：江户川·萝卜  
- **亮点**：  
  - 手写推导 exgcd 过程，适合新手理解  
  - 强调 `#define int long long` 避免溢出  

---

# 最优思路提炼  
1. **符号预处理**：将 `Ax+By+C=0` 转换为 `Ax+By = -C`  
2. **特解缩放**：`x = x0 * (-C/gcd), y = y0 * (-C/gcd)`  
3. **递归边界**：当 `b=0` 时返回 `x=1, y=0`  
4. **逆推变量更新**：`x = y_prev, y = x_prev - (a/b)*y_prev`  

---

# 同类型题与算法套路  
**通用解法**：  
- 线性不定方程 → exgcd 求特解 + 系数缩放  
- 同余方程 → 转换为不定方程形式  

**洛谷推荐题目**：  
1. [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)  
2. [P5656 二元一次不定方程](https://www.luogu.com.cn/problem/P5656)  
3. [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)  

---

# 个人心得摘录  
- **符号陷阱**：多个题解提到忘记处理 `C = -C` 导致错误（江户川·萝卜）  
- **变量传递**：递归时 `x,y` 必须用引用或全局变量（Dog_Two）  
- **溢出教训**：未用 `long long` 在 CF 提交会 WA（叶枫）  

---

# 可视化算法设计  

## 动画方案（8位像素风格）  
**核心元素**：  
- **递归树**：展示 exgcd 的递归层级，用不同颜色标记当前 `a,b`  
- **变量更新**：高亮每次递归后的 `x,y` 值变化  
- **系数缩放**：用像素箭头动态显示 `x *= k` 的过程  

**交互功能**：  
1. **步进控制**：按空格键单步执行递归  
2. **音效提示**：  
   - 成功找到解时播放「通关」音效（8-bit 上扬音阶）  
   - 无解时播放「失败」音效（低音哔声）  
3. **自动演示**：AI 模式自动播放完整流程  

## 关键代码片段（Canvas 绘制）  
```javascript
// 绘制递归树节点（伪代码）
function drawStep(a, b, x, y, depth) {
  ctx.fillStyle = depth % 2 ? '#FF5555' : '#55FF55'; // 交替颜色
  ctx.fillRect(10 + depth*50, 10, 40, 40); // 方块表示递归层级
  ctx.fillText(`a=${a}`, 15 + depth*50, 30); 
  ctx.fillText(`b=${b}`, 15 + depth*50, 45);
}
```

---

# 题解核心代码  
**Crab_Dave 的完整实现**：  
```cpp
#include<cstdio>
using namespace std;
long long a,b,c,x,y,d;

int exgcd(int a,int b) {
  if(b==0){x=1;y=0;return a;}
  int tmp=exgcd(b,a%b);
  int t=x;
  x=y; y=t-a/b*y;
  return tmp;
}

int main() {
  scanf("%lld%lld%lld",&a,&b,&c);
  c=-c; // 关键符号处理
  int d=exgcd(a,b);
  if(c%d!=0){printf("-1");return 0;}
  x=c/d*x; y=c/d*y;
  printf("%lld %lld\n",x,y);
  return 0;
}
```

---
处理用时：79.15秒