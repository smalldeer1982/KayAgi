# 题目信息

# Nearly Shortest Repeating Substring

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin characters. Find the length of the shortest string $ k $ such that several (possibly one) copies of $ k $ can be concatenated together to form a string with the same length as $ s $ and, at most, one different character.

More formally, find the length of the shortest string $ k $ such that $ c = \underbrace{k + \cdots + k}_{x\rm\ \text{times}} $ for some positive integer $ x $ , strings $ s $ and $ c $ has the same length and $ c_i \neq s_i $ for at most one $ i $ (i.e. there exist $ 0 $ or $ 1 $ such positions).

## 说明/提示

In the first test case, you can select $ k = \texttt{a} $ and $ k+k+k+k = \texttt{aaaa} $ , which only differs from $ s $ in the second position.

In the second test case, you cannot select $ k $ of length one or two. We can have $ k = \texttt{abba} $ , which is equal to $ s $ .

## 样例 #1

### 输入

```
5
4
abaa
4
abba
13
slavicgslavic
8
hshahaha
20
stormflamestornflame```

### 输出

```
1
4
13
2
10```

# AI分析结果



---

### 算法分类
**因数枚举、字符串匹配**

---

### 题解思路与难点对比

#### 核心思路
1. **因数枚举**：候选子串长度必须是原字符串长度的因数，因此需枚举所有因数。
2. **双候选检查**：对每个因数，检查其前 `i` 个字符和后 `i` 个字符作为候选子串，避免漏解。
3. **差异统计**：逐个字符比对，统计拼接后与原字符串的差异数是否 ≤1。

#### 解决难点
- **候选子串选择**：样例4中，正确候选子串位于字符串尾部而非头部，需同时检查前后两部分。
- **高效比较**：不显式拼接字符串，而是通过模运算直接比对，时间复杂度为 O(n²/√n)（枚举因数 O(√n)，每个因数比对 O(n)）。

---

### 题解评分（≥4星）

1. **Infinite_Loop（★★★★★）**  
   - **亮点**：双候选检查（前/后子串）确保正确性，代码简洁。  
   - **优化**：直接遍历原字符串，无需额外空间。  
   - **代码**：  
     ```cpp
     // 核心代码片段
     string s2 = s.substr(0, i); // 前候选
     string s3 = s.substr(n-i, i); // 后候选
     for (遍历字符，统计差异)
     ```

2. **spire001（★★★★）**  
   - **亮点**：枚举因数时同时检查小和大因数，减少遍历次数。  
   - **优化**：使用 `check` 函数分离逻辑，代码可读性高。  
   - **代码**：  
     ```cpp
     // 核心代码片段
     bool check(int x) {
         string tmp = s.substr(0, x);
         // 拼接后比对差异
     }
     ```

3. **Dtw_（★★★★）**  
   - **亮点**：通过位置映射直接统计差异，避免拼接字符串。  
   - **优化**：双重循环减少内存访问次数。  
   - **代码**：  
     ```cpp
     // 核心代码片段
     for (int j=0; j<i; j++) { // 每个位置独立检查
         for (int k=j+i; k<n; k+=i) {
             if (s[k] != s[j]) cnt++;
         }
     }
     ```

---

### 最优思路提炼
**双候选覆盖法**：  
1. 枚举所有因数长度 `i`。  
2. 对每个 `i`，取前 `i` 和后 `i` 字符作为候选子串。  
3. 分别统计全串差异，差异数 ≤1 即合法。  

---

### 同类型题目推荐
1. **LeetCode 459. 重复的子字符串**  
   - 判断字符串是否由子串重复构成。  
2. **洛谷 P4392 [BOI2007]Sound 静音问题**  
   - 滑动窗口与极值统计，涉及分段检查。  
3. **Codeforces 1326D2. Prefix-Suffix Palindrome**  
   - 基于前后缀的字符串匹配优化。  

---

### 个人心得摘录
- **Infinite_Loop**：样例4的调试发现必须检查后候选，否则漏解。  
- **Dtw_**：通过直接映射位置而非生成拼接字符串，节省内存且提升效率。  

---

### 可视化算法设计

#### 动画方案
1. **像素风格展示**：  
   - 原字符串显示为彩色像素块，候选子串高亮为黄色（前）和蓝色（后）。  
   - 差异字符闪烁红色，统计栏实时更新差异数。  
2. **步进控制**：  
   - 单步执行：按因数从小到大逐步检查，显示当前候选子串和差异位置。  
   - 速度调节：滑动条控制比对速度（0.5x~3x）。  
3. **音效反馈**：  
   - **差异统计**：每发现一个差异播放短促“滴”声。  
   - **成功/失败**：找到解时播放胜利音效，否则低沉提示音。  

#### 复古风格实现
```javascript
// 伪代码：Canvas绘制与音效
function drawPixel(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*10, y*10, 8, 8); // 8x8像素块
}

function playSound(effect) {
    const sfx = { success: [500, 100], fail: [200, 300] };
    const osc = new OscillatorNode(ctx, { frequency: sfx[effect][0] });
    osc.connect(ctx.destination);
    osc.start().stop(ctx.currentTime + sfx[effect][1]/1000);
}
```

---

### 核心代码实现
**Infinite_Loop 的完整代码**  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>s;
        int ans=n;
        for(int i=1;i<=n;i++){
            if(n%i!=0) continue;
            // 前候选检查
            string s2 = s.substr(0,i);
            int sum=0;
            for(int j=0,k=0; j<n; j++){
                if(s[j]!=s2[k++]) sum++;
                if(k>=i) k=0;
                if(sum>1) break;
            }
            if(sum<=1) ans=min(ans,i);
            // 后候选检查
            string s3 = s.substr(n-i,i);
            sum=0;
            for(int j=0,k=0; j<n; j++){
                if(s[j]!=s3[k++]) sum++;
                if(k>=i) k=0;
                if(sum>1) break;
            }
            if(sum<=1) ans=min(ans,i);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---
处理用时：131.75秒