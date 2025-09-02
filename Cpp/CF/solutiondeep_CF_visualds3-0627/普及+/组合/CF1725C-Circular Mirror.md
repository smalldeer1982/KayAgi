# 题目信息

# Circular Mirror

## 题目描述

Pak Chanek has a mirror in the shape of a circle. There are $ N $ lamps on the circumference numbered from $ 1 $ to $ N $ in clockwise order. The length of the arc from lamp $ i $ to lamp $ i+1 $ is $ D_i $ for $ 1 \leq i \leq N-1 $ . Meanwhile, the length of the arc between lamp $ N $ and lamp $ 1 $ is $ D_N $ .

Pak Chanek wants to colour the lamps with $ M $ different colours. Each lamp can be coloured with one of the $ M $ colours. However, there cannot be three different lamps such that the colours of the three lamps are the same and the triangle made by considering the three lamps as vertices is a right triangle (triangle with one of its angles being exactly $ 90 $ degrees).

The following are examples of lamp colouring configurations on the circular mirror.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/f662b018d5c25548ad3c12ebf7297c4fe9cddb27.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/d15118feff1296e48df6066dea2761fdbf3bbba3.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1725C/904b8c54d18751fcd9444e012c7c141ddaf812b7.png)Figure 1. an example of an incorrect colouring because lamps $ 1 $ , $ 2 $ , and $ 3 $ form a right triangleFigure 2. an example of a correct colouringFigure 3. an example of a correct colouringBefore colouring the lamps, Pak Chanek wants to know the number of distinct colouring configurations he can make. Count the number of distinct possible lamp colouring configurations, modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, all correct lamp colouring configurations are $ [1, 1, 2, 1] $ , $ [1, 1, 2, 2] $ , $ [1, 2, 1, 2] $ , $ [1, 2, 2, 1] $ , $ [1, 2, 2, 2] $ , $ [2, 1, 1, 1] $ , $ [2, 1, 1, 2] $ , $ [2, 1, 2, 1] $ , $ [2, 2, 1, 1] $ , and $ [2, 2, 1, 2] $ .

## 样例 #1

### 输入

```
4 2
10 10 6 14```

### 输出

```
10```

## 样例 #2

### 输入

```
1 2
10```

### 输出

```
2```

# AI分析结果



---

## **唯一算法分类**  
**组合数学**

---

## **综合分析与结论**  

### **题目核心思路**  
圆内接直角三角形的斜边必为直径。因此问题转化为：统计所有直径对，确保不存在同色的直径对 + 同色的第三点。  

**关键步骤与变量**：  
1. **统计直径对**：计算圆周总长，若为偶数，遍历所有点判断是否存在对应的直径端点。  
2. **组合公式**：枚举使用 `i` 对直径染同色，剩余点颜色不与选中的 `i` 种颜色重复。公式为：  
   $$\sum_{i=0}^{\min(m,cnt)} C_{cnt}^i \cdot A_m^i \cdot (m-i)^{n-2cnt} \cdot [(m-i)(m-i-1)]^{cnt-i}$$  

### **难点对比**  
- **直径对统计**：需高效判断两点间弧长是否为半周长，各题解均使用前缀和 + `map` 快速查询。  
- **组合计算**：部分题解错误使用 `lucas` 定理（如题解3），实际上模数 `998244353` 是质数，直接预处理阶乘逆元即可。  
- **公式推导**：关键在于“选中 `i` 对颜色后，剩余直径对的端点必须颜色不同且不与选中颜色冲突”。  

### **可视化设计**  
- **动画流程**：  
  1. **直径统计**：圆上高亮匹配的直径对，播放“匹配成功”音效。  
  2. **染色过程**：选中 `i` 对直径染同色（不同颜色区分），剩余点渐变动画染色。  
  3. **公式分步**：动态展开组合数、排列数、幂次项，用颜色区分各部分。  
- **复古风格**：  
  - **像素圆**：圆心固定，圆周点用 8 位像素块表示。  
  - **音效**：直径匹配时播放 `8-bit` 音效，错误方案触发“失败”音。  
  - **自动模式**：展示从 `i=0` 到 `i=cnt` 的逐步计算，速度可调。  

---

## **题解清单 (≥4星)**  

### **题解1：yingkeqian9217（★★★★☆）**  
- **亮点**：代码简洁，预处理阶乘逆元；公式推导清晰，注释明确。  
- **核心代码**：  
  ```cpp
  for(int i=0;i<=min(m,cnt);i++)
    ans=(ans + qpow(m-i,n-cnt-i) * qpow(m-i-1,cnt-i) % Mod * C(cnt,i) * A(m,i)) % Mod;
  ```

### **题解2：江户川·萝卜（★★★★☆）**  
- **亮点**：公式表达规范，变量命名清晰；正确使用组合数预处理。  
- **核心代码**：  
  ```cpp
  ans = (ans + ... ) % mod;
  ```

### **题解4：Mariposa（★★★★☆）**  
- **亮点**：公式简化为统一幂次项，代码复用性高；预处理组合逻辑清晰。  

---

## **最优思路提炼**  
1. **直径对统计**：前缀和 + `map` 快速查询，时间复杂度 $O(N)$。  
2. **组合公式设计**：将问题分解为选中 `i` 对颜色的排列、剩余点的独立染色，避免重复计数。  
3. **模运算优化**：预处理阶乘和逆元，快速计算组合数与排列数。  

---

## **同类型题与算法套路**  
- **组合计数**：常见于限制条件下的染色问题（如 CF888D）。  
- **圆上几何**：涉及圆周点对统计（如洛谷 P1975）。  

---

## **推荐题目**  
1. **CF888D**：组合数枚举相似结构。  
2. **洛谷 P3197**：模数限制下的组合计数。  
3. **洛谷 P1975**：圆上点对关系统计。  

---

## **个人心得摘录**  
- **yingkeqian9217**：“调了好久才发现直径对统计的边界条件。”  
- **Siteyava_145**：“突然意识到选中 `i` 对后，其他颜色必须严格不同，否则会形成三角。”  

---

## **可视化与算法演示**  
```javascript
// 伪代码：Canvas 绘制圆与直径对  
function drawCircle() {
  ctx.fillStyle = "#8B00FF"; // 复古紫色
  ctx.beginPath();
  ctx.arc(centerX, centerY, radius, 0, 2 * Math.PI);
  ctx.stroke();
  // 绘制点对连线（直径）
  if (isDiameterPair(i, j)) {
    ctx.strokeStyle = "#FF4500"; // 像素橙
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.stroke();
    playSound("beep"); // 触发音效
  }
}
```

---

**答案与代码**  
最简实现（参考题解1）：  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e5+5, Mod=998244353;
ll n,m,cnt,sum[N],fac[N],inv[N];
map<ll,int> mp;

ll qpow(ll x, ll y) {
    ll res=1;
    for(;y;y>>=1,x=x*x%Mod) if(y&1) res=res*x%Mod;
    return res;
}

void init() {
    fac[0]=1;
    for(int i=1;i<=m;++i) fac[i]=fac[i-1]*i%Mod;
    inv[m]=qpow(fac[m],Mod-2);
    for(int i=m-1;i>=0;--i) inv[i]=inv[i+1]*(i+1)%Mod;
}

ll C(int a, int b) {
    return fac[a]*inv[b]%Mod * inv[a-b]%Mod;
}

ll A(int a, int b) {
    return fac[a]*inv[a-b]%Mod;
}

int main() {
    cin>>n>>m;
    for(int i=1;i<=n;++i) {
        cin>>sum[i]; sum[i]+=sum[i-1];
        mp[sum[i]]=1;
    }
    ll S=sum[n];
    if(S%2==0) {
        S/=2;
        for(int i=1;i<=n;++i) 
            if(mp.count(sum[i]+S)) cnt++;
    }
    init();
    ll ans=0;
    for(int i=0;i<=min(m,cnt);++i) {
        ll term = C(cnt,i) * A(m,i) % Mod;
        term = term * qpow(m-i, n-cnt-i) % Mod;
        term = term * qpow((m-i-1)*(m-i)%Mod, cnt-i) % Mod;
        ans = (ans + term) % Mod;
    }
    cout<<ans;
    return 0;
}
```

---
处理用时：84.42秒