# 题目信息

# Beautiful Mirrors

## 题目描述

Creatnx has $ n $ mirrors, numbered from $ 1 $ to $ n $ . Every day, Creatnx asks exactly one mirror "Am I beautiful?". The $ i $ -th mirror will tell Creatnx that he is beautiful with probability $ \frac{p_i}{100} $ for all $ 1 \le i \le n $ .

Creatnx asks the mirrors one by one, starting from the $ 1 $ -st mirror. Every day, if he asks $ i $ -th mirror, there are two possibilities:

- The $ i $ -th mirror tells Creatnx that he is beautiful. In this case, if $ i = n $ Creatnx will stop and become happy, otherwise he will continue asking the $ i+1 $ -th mirror next day;
- In the other case, Creatnx will feel upset. The next day, Creatnx will start asking from the $ 1 $ -st mirror again.

You need to calculate [the expected number](https://en.wikipedia.org/wiki/Expected_value) of days until Creatnx becomes happy.

This number should be found by modulo $ 998244353 $ . Formally, let $ M = 998244353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test, there is only one mirror and it tells, that Creatnx is beautiful with probability $ \frac{1}{2} $ . So, the expected number of days until Creatnx becomes happy is $ 2 $ .

## 样例 #1

### 输入

```
1
50
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
10 20 50
```

### 输出

```
112
```

# AI分析结果



0. **题目翻译**

# 美丽的镜子

## 题目描述

Creatnx 有 $n$ 面镜子，编号从 $1$ 到 $n$。每天，Creatnx 会按顺序询问镜子"我漂亮吗？"。第 $i$ 面镜子有 $\frac{p_i}{100}$ 的概率回答"漂亮"。

Creatnx 从第 $1$ 面镜子开始依次询问。当某天询问第 $i$ 面镜子时：
- 如果镜子回答"漂亮"且 $i = n$，Creatnx 会开心并停止询问
- 如果镜子回答"漂亮"但 $i < n$，则下一天继续询问第 $i+1$ 面镜子
- 如果回答"不漂亮"，下一天必须从第 $1$ 面镜子重新开始

要求计算 Creatnx 停止询问的期望天数，结果对 $998244353$ 取模。

## 输入格式
第一行输入 $n$，第二行输入 $n$ 个整数表示 $p_1$ 到 $p_n$

## 说明/提示
样例 1 中，单面镜子概率 $\frac{1}{2}$，期望天数为 $2$

1. **唯一算法分类**  
线性DP

---

2. **综合分析与结论**

### 核心算法思路
采用线性动态规划模型，定义 $f[i]$ 表示通过前 $i$ 面镜子的期望天数。关键推导公式：
$$ f[i] = \frac{100(f[i-1]+1)}{p_i} $$
其中 $p_i$ 的概率转换为模数下的乘法逆元处理。

### 可视化设计要点
1. **DP矩阵动态更新**：  
   - 创建像素风格网格，每行表示一面镜子，列表示期望值计算过程
   - 使用绿色高亮当前计算的 $f[i]$ 格子，红色标记使用的 $f[i-1]$ 值
   - 展示公式推导过程时，用黄色闪烁效果突出乘法逆元步骤

2. **复古音效系统**：
   - 状态更新时播放 8-bit 风格的"滴"声（频率 800Hz，持续 50ms）
   - 完成全部计算时播放胜利音效（三音阶上升旋律）
   - 错误操作时播放短促的"哔"声（频率 2000Hz，持续 100ms）

3. **自动演示模式**：
   ```javascript
   // 伪代码示例
   function autoDemo() {
     let current = 0;
     const interval = setInterval(() => {
       if(current > n) clearInterval(interval);
       else {
         highlightMirror(current);  // 高亮当前镜子
         updateDPGrid(current);     // 更新DP矩阵
         playSound('beep');         // 播放音效
         current++;
       }
     }, 1000); // 每秒执行一步
   }
   ```

---

3. **题解清单 (≥4星)**

| 题解作者 | 星级 | 核心亮点 |
|---------|------|---------|
| 万弘     | ★★★★★ | 正向递推式简洁优雅，时间复杂度 O(n) |
| UltiMadow | ★★★★☆ | 通过无穷级数巧妙化简，数学推导严谨 |
| Plozia   | ★★★★☆ | 状态定义清晰，代码可读性极佳 |

---

4. **最优思路与代码实现**

### 核心递推逻辑
```cpp
const int mod = 998244353;
ll f[MAXN]; // f[i]表示通过前i面镜子的期望

for(int i=1; i<=n; ++i) {
    f[i] = (f[i-1] + 1) * 100 % mod; 
    f[i] = f[i] * qpow(p[i], mod-2, mod) % mod;
}
```

### 完整代码（万弘版）
```cpp
#include<bits/stdc++.h>
#define ll long long
const ll mod=998244353;
ll f[200005], n;

ll qpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod; b>>=1;
    }return res;
}

int main(){
    scanf("%lld",&n);
    for(ll i=1,p;i<=n;++i){
        scanf("%lld",&p);
        f[i] = (f[i-1]+1)*100 % mod * qpow(p,mod-2) % mod;
    }
    printf("%lld",f[n]);
    return 0;
}
```

---

5. **同类问题扩展**

### 相似题型套路
- **状态线性递推**：当后序状态仅依赖前一个状态时适用
- **模数下逆元处理**：概率问题中常见分数取模技巧
- **失败重置机制**：需要设计包含回退的状态转移

### 推荐练习题
1. P6835 [线性期望DP] 类似镜子排列但扩展了条件概率
2. P1654 数学期望经典题，包含多状态转移
3. P1850 结合概率的期望DP，需要处理复杂状态

---

6. **可视化算法演示**

```html
<canvas id="dpGrid"></canvas>

<script>
// 初始化像素画布
const canvas = document.getElementById('dpGrid');
const ctx = canvas.getContext('2d');
const CELL_SIZE = 40;

function drawDPGrid(fValues) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    fValues.forEach((val, idx) => {
        // 绘制像素风格格子
        ctx.fillStyle = idx === currentStep ? '#00FF00' : '#FFFFFF';
        ctx.fillRect(idx*CELL_SIZE, 0, CELL_SIZE-1, CELL_SIZE-1);
        // 显示数值
        ctx.fillStyle = '#000000';
        ctx.font = '12px retro';
        ctx.fillText(`f[${idx}]=${val}`, idx*CELL_SIZE+2, 20);
    });
}
</script>
```

---

7. **个人心得摘录**

> "当发现状态方程中存在自循环项（如 $dp_i$ 同时出现在等式两边），可以通过代数变形将其转换为线性递推式。这种将递归结构展开为线性表达的能力，是解决复杂期望问题的关键。" —— 万弘题解中的核心洞见

---

8. **知识迁移建议**

当遇到以下特征时，可考虑类似解法：
1. 过程具有顺序性（镜子依次询问）
2. 失败时重置进度（回到第一面镜子）
3. 需要处理模数下的分数运算

训练时重点关注：
- 模逆元的快速计算
- 状态转移方程的代数变形能力
- 将递归结构转换为线性递推式的技巧

---
处理用时：84.87秒