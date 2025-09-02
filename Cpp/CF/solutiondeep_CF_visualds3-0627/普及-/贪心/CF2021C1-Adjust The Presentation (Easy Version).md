# 题目信息

# Adjust The Presentation (Easy Version)

## 题目描述

This is the easy version of the problem. In the two versions, the constraints on $ q $ and the time limit are different. In this version, $ q=0 $ . You can make hacks only if all the versions of the problem are solved.

A team consisting of $ n $ members, numbered from $ 1 $ to $ n $ , is set to present a slide show at a large meeting. The slide show contains $ m $ slides.

There is an array $ a $ of length $ n $ . Initially, the members are standing in a line in the order of $ a_1, a_2, \ldots, a_n $ from front to back. The slide show will be presented in order from slide $ 1 $ to slide $ m $ . Each section will be presented by the member at the front of the line. After each slide is presented, you can move the member at the front of the line to any position in the lineup (without changing the order of the rest of the members). For example, suppose the line of members is $ [\color{red}{3},1,2,4] $ . After member $ 3 $ presents the current slide, you can change the line of members into either $ [\color{red}{3},1,2,4] $ , $ [1,\color{red}{3},2,4] $ , $ [1,2,\color{red}{3},4] $ or $ [1,2,4,\color{red}{3}] $ .

There is also an array $ b $ of length $ m $ . The slide show is considered good if it is possible to make member $ b_i $ present slide $ i $ for all $ i $ from $ 1 $ to $ m $ under these constraints.

However, your annoying boss wants to make $ q $ updates to the array $ b $ . In the $ i $ -th update, he will choose a slide $ s_i $ and a member $ t_i $ and set $ b_{s_i} := t_i $ . Note that these updates are persistent, that is changes made to the array $ b $ will apply when processing future updates.

For each of the $ q+1 $ states of array $ b $ , the initial state and after each of the $ q $ updates, determine if the slideshow is good.

## 说明/提示

For the first test case, you do not need to move the members as both slides are presented by member $ 1 $ , who is already at the front of the line.

For the second test case, the following is a possible way to move members so that the presentation is good:

1. $ [1,2,3] $ , do not move member $ 1 $ .
2. $ [1,2,3] $ , move member $ 1 $ after member $ 3 $ .
3. $ [2,3,1] $ , move member $ 2 $ after member $ 3 $ .
4. $ [3,2,1] $ , do not move member $ 3 $ .
5. $ [3,2,1] $ , move member $ 3 $ after member $ 1 $ .
6. $ [2,1,3] $ , do not move member $ 2 $ .

## 样例 #1

### 输入

```
3
4 2 0
1 2 3 4
1 1
3 6 0
1 2 3
1 1 2 3 3 2
4 6 0
3 1 4 2
3 1 1 2 3 4```

### 输出

```
YA
YA
TIDAK```

# AI分析结果



---

### 唯一算法分类  
**贪心算法**

---

### 题解思路与算法分析  
#### 核心思路  
所有题解的核心思路均为：**验证每个元素在 `b` 数组中的第一次出现顺序与原数组 `a` 中的顺序一致**。具体来说，每个元素的首次出现位置必须满足其在 `a` 中的原始位置是连续的或已被处理。通过维护当前已处理元素的最大原始位置 `max_pos`，若新元素首次出现时的位置超过 `max_pos + 1`，则无法合法构造。

#### 解决难点  
- **关键条件推导**：每次移动队首元素后，后续操作中该元素可被任意调整位置。但元素首次出现时，必须满足其在原数组中的顺序未被破坏。  
- **维护最大位置**：遍历 `b` 数组时，维护已处理元素的最大原始位置 `max_pos`。若首次出现的元素位置超过 `max_pos + 1`，则说明原数组中存在未处理的中间元素，导致不合法。

#### 可视化设计  
1. **动态维护 `max_pos`**：用进度条或高亮区域表示当前已处理的最大位置。  
2. **元素首次出现判断**：标记当前处理的 `b[i]`，若首次出现且位置合法（≤ `max_pos + 1`），则更新 `max_pos`；否则触发错误提示（如红色闪烁）。  
3. **复古像素风格**：用 8-bit 风格网格表示数组，当前处理的 `b[i]` 显示为闪烁方块，合法时播放“成功”音效，非法时播放“失败”音效。

---

### 题解评分（≥4星）  
1. **Double_Light（4.5星）**  
   - **亮点**：代码简洁，维护 `maxn` 和 `cnt` 验证顺序，直接判断条件。  
   - **核心代码**：  
     ```cpp
     if (!p[x] && b[x] < maxn) f = 0;  
     maxn = max(maxn, b[x]);  
     ```
   
2. **Colinxu2020（4.5星）**  
   - **亮点**：逻辑清晰，直接维护 `mx`，条件判断简洁。  
   - **核心代码**：  
     ```cpp
     if (bi[i] > mx + 1) flag = 1;  
     mx = max(mx, bi[i]);  
     ```
   
3. **kanzaki（4星）**  
   - **亮点**：将元素映射为原始位置，通过贪心遍历验证。  
   - **核心代码**：  
     ```cpp
     if (b[i] > mx + 1) cout << "TIDAK\n";  
     mx = max(mx, b[i]);  
     ```

---

### 最优思路提炼  
**贪心验证首次出现顺序**  
- **映射原始位置**：将 `a` 数组中的元素位置记录为 `mp[x]`。  
- **维护最大位置 `max_pos`**：遍历 `b` 数组时，若元素 `x` 首次出现且 `mp[x] > max_pos + 1`，则不合法；否则更新 `max_pos` 为 `max(max_pos, mp[x])`。

---

### 同类型题与算法套路  
- **类似问题**：验证序列是否满足特定顺序约束（如栈混洗、队列操作合法性）。  
- **通用解法**：通过贪心维护关键变量（如最大/最小值、当前处理位置）判断合法性。

---

### 推荐相似题目  
1. **P1090 [NOIP2004 提高组] 合并果子**（贪心策略）  
2. **P1106 删数问题**（贪心选择最小序列）  
3. **P1233 木棍加工**（贪心+排序）

---

### 代码实现（Colinxu2020 题解）  
```cpp
#include<iostream>
using namespace std;

const int maxn=2e5+10;
int t,n,m,q,ai[maxn],bi[maxn],mp[maxn];

int main(){
    cin>>t;
    while(t--){
        cin>>n>>m>>q;
        for(int i=1;i<=n;i++)cin>>ai[i],mp[ai[i]]=i;
        for(int i=1;i<=m;i++)cin>>bi[i],bi[i]=mp[bi[i]];
        int mx=0; bool flag=0;
        for(int i=1;i<=m&&!flag;i++){
            if(bi[i]>mx+1) flag=1; // 首次出现位置超过 max_pos +1
            mx=max(mx, bi[i]);     // 更新最大位置
        }
        cout<<(flag?"TIDAK":"YA")<<endl;
    }
}
```

---

### 可视化算法演示  
**动画步骤**：  
1. **初始化**：显示原数组 `a`，高亮每个元素的原始位置。  
2. **遍历 `b` 数组**：逐个处理元素，若首次出现且位置合法，更新 `max_pos` 进度条；否则显示红色错误框。  
3. **音效反馈**：合法时播放“滴”声，非法时播放“嗡”声。  
**复古风格**：采用 8-bit 像素字体，进度条以绿色方块填充，当前处理元素闪烁黄色。

---

### 个人心得摘录  
- **Double_Light**：通过观察元素首次出现的顺序与原数组前缀的关系，快速锁定核心条件。  
- **ivyjiao 的调试教训**：未正确处理元素重插入后的逻辑，需注意移动操作的后续影响。

---
处理用时：179.57秒