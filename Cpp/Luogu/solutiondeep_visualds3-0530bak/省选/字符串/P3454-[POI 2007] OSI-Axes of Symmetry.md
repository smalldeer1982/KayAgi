# 题目信息

# [POI 2007] OSI-Axes of Symmetry

## 题目描述

Johnny 是一位非常年轻的数学家，但他此刻正在为他妹妹的数学作业烦恼。

这个周末，他的妹妹需要完成一项作业，计算各种几何图形的对称轴数量。因为 Johnny 这个周末想要去海边旅行，所以他希望他的妹妹能尽快完成这项作业。

于是他找到了擅长编程的你，你一定能帮助他完成这项任务的！

## 说明/提示

$1 \leq t \leq 10$，$3 \leq n \leq 10^5$，$-10^8 \leq x_i,y_i \leq 10^8$。

## 样例 #1

### 输入

```
2
12
1 -1
2 -1
2 1
1 1
1 2
-1 2
-1 1
-2 1
-2 -1
-1 -1
-1 -2
1 -2
6
-1 1
-2 0
-1 -1
1 -1
2 0
1 1```

### 输出

```
4
2```

# AI分析结果



## 算法分类
**字符串处理（回文相关算法）**

---

## 综合分析与结论

### 核心思路与难点
1. **几何问题转字符串回文**  
   将多边形的边（长度平方）和角（叉积）交替排列为环状序列，对称轴对应环上某处断开的回文序列。
2. **环的处理技巧**  
   通过将序列复制成双倍长度链，将环问题转化为线性序列的回文匹配问题。
3. **高效回文检测**  
   使用 **KMP**、**Manacher** 或 **哈希** 算法在 O(n) 时间复杂度内判断回文。

### 可视化设计思路
1. **动画流程**  
   - **Step 1**: 多边形顶点坐标 → 边角序列（黄色块为边，蓝色块为角）  
   - **Step 2**: 断环成链，复制序列（灰色虚线表示连接处）  
   - **Step 3**: 应用回文算法（如 Manacher 的红色扩展半径或 KMP 的绿色匹配指针）  
2. **复古像素风格**  
   - **颜色方案**: 8-bit 色调（边：黄色，角：蓝色，回文区：闪烁绿色）  
   - **音效**: 匹配成功时播放 "POWER-UP" 音效，回文扩展时播放 "LASER" 音效。  
3. **交互功能**  
   - 步进控制观察回文匹配过程，支持速度调节。

---

## 题解评分（≥4星）

### 1. 白桦树（KMP）⭐️⭐️⭐️⭐️⭐️
- **亮点**:  
  - 严格数学推导边角表示（叉积代替角度，平方长度避免浮点）  
  - 环转链后反向匹配的巧妙 KMP 应用  
  - 时间复杂度 O(n)，适合 1e5 规模  

### 2. Drinkwater（Manacher）⭐️⭐️⭐️⭐️
- **亮点**:  
  - 直接处理边角序列为回文半径问题  
  - 代码简洁，Manacher 模板清晰  

### 3. Butterfly_qwq（哈希+离散化）⭐️⭐️⭐️⭐️
- **亮点**:  
  - 离散化处理避免哈希冲突  
  - 双哈希保证正确性  

---

## 最优思路与技巧提炼

### 关键步骤
1. **边角序列构造**  
   ```cpp
   for(int i=1; i<=n; i++){
       edge[i] = (a[i]-a[i%n+1]).squared_length();
       ang[i]  = cross(a[i], a[i%n+1], a[(i+1)%n+1]);
   }
   ```
2. **环转链处理**  
   ```cpp
   vector<int> s(edge.begin(), edge.end());
   s.insert(s.end(), edge.begin(), edge.end());
   ```
3. **Manacher 回文检测**  
   ```cpp
   for(int i=0, l=0, r=-1; i<2*n; i++){
       int k = (i>r) ? 1 : min(r-i, rad[2*l-i]);
       while(k<=i && i+k<4*n && s[i-k]==s[i+k]) k++;
       rad[i] = k--;
       if(i+k > r) { l=i; r=i+k; }
   }
   ```

---

## 类似题目推荐
1. **[P3805 Manacher算法模板题](https://www.luogu.com.cn/problem/P3805)**  
   - 直接练习 Manacher 的核心应用  
2. **[P4551 最长回文子串](https://www.luogu.com.cn/problem/P4551)**  
   - 哈希与回文结合的双倍经验  
3. **[CF835E 对称图形计数](https://codeforces.com/problemset/problem/835/E)**  
   - 几何对称性转字符串分析的变种  

---

## 核心代码实现（Manacher 版）
```cpp
int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        vector<Point> poly(n);
        for(auto& p : poly) cin >> p.x >> p.y;

        vector<LL> s; // 边角交替序列
        for(int i=0; i<n; i++) {
            int j = (i+1)%n, k = (i+2)%n;
            s.push_back(dist2(poly[i], poly[j]));
            s.push_back(cross(poly[i], poly[j], poly[k]));
        }

        // 断环成链
        vector<int> rad(4*n);
        for(int i=0, l=0, r=-1; i<2*n; i++) {
            int k = (i>r) ? 1 : min(rad[l+r-i], r-i);
            while(k<=i && i+k<4*n && s[(i-k)%(2*n)] == s[(i+k)%(2*n)]) k++;
            rad[i] = k--;
            if(i+k > r) l=i-k, r=i+k;
        }

        int ans = 0;
        for(int i=0; i<2*n; i++)
            if(rad[i] >= n) ans++;
        cout << ans/2 << endl;
    }
}
```

---

## 可视化演示（伪代码）
```javascript
// Canvas 绘制示例
function drawPolygonAndString() {
    ctx.fillStyle = "#FFD700"; // 金色边块
    ctx.fillRect(x, y, 20, 20); 
    ctx.fillStyle = "#1E90FF"; // 蓝色角块
    ctx.beginPath();
    ctx.arc(x+10, y+10, 10, 0, Math.PI*2);
    ctx.fill();
    
    // 回文匹配高亮
    if(isPalindrome) {
        ctx.fillStyle = "#32CD32"; // 绿色闪烁
        requestAnimationFrame(blink);
    }
}
```

---
处理用时：82.69秒