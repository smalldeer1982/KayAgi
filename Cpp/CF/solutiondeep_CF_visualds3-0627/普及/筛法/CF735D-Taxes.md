# 题目信息

# Taxes

## 题目描述

Mr. Funt now lives in a country with a very specific tax laws. The total income of mr. Funt during this year is equal to $ n $ ( $ n>=2 $ ) burles and the amount of tax he has to pay is calculated as the maximum divisor of $ n $ (not equal to $ n $ , of course). For example, if $ n=6 $ then Funt has to pay $ 3 $ burles, while for $ n=25 $ he needs to pay $ 5 $ and if $ n=2 $ he pays only $ 1 $ burle.

As mr. Funt is a very opportunistic person he wants to cheat a bit. In particular, he wants to split the initial $ n $ in several parts $ n_{1}+n_{2}+...+n_{k}=n $ (here $ k $ is arbitrary, even $ k=1 $ is allowed) and pay the taxes for each part separately. He can't make some part equal to $ 1 $ because it will reveal him. So, the condition $ n_{i}>=2 $ should hold for all $ i $ from $ 1 $ to $ k $ .

Ostap Bender wonders, how many money Funt has to pay (i.e. minimal) if he chooses and optimal way to split $ n $ in parts.

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
27
```

### 输出

```
3
```

# AI分析结果



# 算法分类  
**数论（质数应用、哥德巴赫猜想）**

---

## 题解思路与核心难点  
### 核心思路  
1. **质数判定**：若n是质数，税款只能是1（无法拆分）  
2. **偶数拆分**：根据哥德巴赫猜想，任意偶数≥4可拆分为两个质数之和，税款总和为2  
3. **奇数拆分**：当n-2是质数时拆分为2+(n-2)，税款2；否则拆分为3+偶数（税款3）  

### 解决难点  
- 如何快速推导出 **"答案只能是1/2/3"** 的结论  
- 正确判定奇数拆分的边界条件（n-2是否为质数）  
- 将哥德巴赫猜想在有限范围内（n≤1e18）转化为确定性结论  

---

## 题解评分（≥4星）  
### 1. [yyyer] ★★★★★  
- **亮点**：代码最简洁，条件顺序合理，无需额外优化  
- **核心代码**：  
```cpp
if(isprime(n)) cout<<"1"; 
else if(n%2==0) cout<<"2"; 
else if(isprime(n-2)) cout<<"2"; 
else cout<<"3";
```

### 2. [ADivT] ★★★★☆  
- **亮点**：完整解释猜想与代码对应关系，结构清晰  
- **改进点**：合并奇数判断条件更高效  

### 3. [xujian] ★★★★☆  
- **亮点**：深入探讨质数判定优化，提供6x±1加速方案  
- **代码亮点**：  
```cpp
bool zs(int num) { // 优化版质数判断
    if(num%6!=1 && num%6!=5) return 0;
    int tmp=sqrt(num);
    for(int i=5;i<=tmp;i+=6) 
        if(num%i==0||num%(i+2)==0) return 0; 
    return 1;
}
```

---

## 最优思路提炼  
### 关键技巧  
1. **三叉决策树**：  
   ```mermaid
   graph TD
   A{n} --> B[质数?]
   B -->|是| C[输出1]
   B -->|否| D{偶数?}
   D -->|是| E[输出2]
   D -->|否| F[n-2质数?]
   F -->|是| G[输出2]
   F -->|否| H[输出3]
   ```

2. **数学优化**：仅需判断到√n的质数检测  
3. **边界处理**：n=2需特殊处理，但已被质数分支覆盖  

---

## 同类型题目推荐  
1. **P1217** 回文质数（质数判定+数位处理）  
2. **P1304** 哥德巴赫猜想（直接应用猜想）  
3. **P2563** 质数和分解（动态规划应用）  

---

## 可视化设计  
### 复古像素演示方案  
```html
<canvas id="taxes-demo" width="640" height="480"></canvas>
<script>
// 初始化8位风格
const palette = ["#000","#F00","#0F0","#00F","#FF0","#0FF","#F0F","#FFF"];
let step = 0, n = 27; // 样例输入27→3

function drawStep(ctx) {
  ctx.fillStyle = palette[7];
  ctx.fillRect(0,0,640,480);
  
  // 绘制当前状态
  ctx.fillStyle = palette[step>0?1:3];
  ctx.fillText(`n = ${n}`, 20, 40);
  
  // 步骤说明
  const steps = [
    "① 质数检测 → 红框闪烁",
    "② 偶数检测 → 绿框闪烁", 
    "③ n-2质数检测 → 蓝框闪烁",
    "④ 默认3 → 黄框"];
  steps.forEach((s,i) => {
    ctx.fillStyle = i === step%4 ? palette[5] : palette[7];
    ctx.fillText(s, 20, 80+i*30);
  });

  // 播放音效
  if(step > 0) new Audio('data:audio/wav;base64,UklGRl9v...').play(); // 8-bit音效
}

// 自动步进演示
setInterval(() => {
  const ctx = document.getElementById("taxes-demo").getContext("2d");
  drawStep(ctx);
  step = (step+1)%5;
}, 1500);
</script>
```

---

## 核心代码实现  
```cpp
#include <cmath>
#include <iostream>
using namespace std;

bool isPrime(int x) { // 标准质数检测
    if(x < 2) return false;
    for(int i=2; i*i<=x; ++i)
        if(x%i == 0) return false;
    return true;
}

int main() {
    int n; cin >> n;
    if(isPrime(n))       cout << 1;
    else if(n%2 == 0)   cout << 2;
    else if(isPrime(n-2))cout << 2;
    else                 cout << 3;
    return 0;
}
```

---

## 算法比较  
1. **质数检测优化**：xujian的6x±1法比常规sqrt法快约3倍  
2. **条件顺序**：先判断偶数比先判断n-2更高效（偶数占50%概率）  
3. **极端情况**：当n=1e18时需改用Miller-Rabin检测，但本题范围无需  

---

## 总结启示  
通过数学猜想将无限可能收敛到有限情况，是算法优化的重要思路。当遇到数论问题时，应优先考虑是否存在数学规律或著名猜想可简化计算。

---
处理用时：73.61秒