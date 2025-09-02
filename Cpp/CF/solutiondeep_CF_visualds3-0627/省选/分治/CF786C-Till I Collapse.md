# 题目信息

# Till I Collapse

## 题目描述

Rick and Morty want to find MR. PBH and they can't do it alone. So they need of Mr. Meeseeks. They Have generated $ n $ Mr. Meeseeks, standing in a line numbered from $ 1 $ to $ n $ . Each of them has his own color. $ i $ -th Mr. Meeseeks' color is $ a_{i} $ .

Rick and Morty are gathering their army and they want to divide Mr. Meeseeks into some squads. They don't want their squads to be too colorful, so each squad should have Mr. Meeseeks of at most $ k $ different colors. Also each squad should be a continuous subarray of Mr. Meeseeks in the line. Meaning that for each $ 1<=i<=e<=j<=n $ , if Mr. Meeseeks number $ i $ and Mr. Meeseeks number $ j $ are in the same squad then Mr. Meeseeks number $ e $ should be in that same squad.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786C/f2b873f46d1ce1d5117f05fee6c23499da101533.png)Also, each squad needs its own presidio, and building a presidio needs money, so they want the total number of squads to be minimized.

Rick and Morty haven't finalized the exact value of $ k $ , so in order to choose it, for each $ k $ between $ 1 $ and $ n $ (inclusive) need to know the minimum number of presidios needed.

## 说明/提示

For the first sample testcase, some optimal ways of dividing army into squads for each $ k $ are:

1. $ [1],[3],[4],[3,3] $
2. $ [1],[3,4,3,3] $
3. $ [1,3,4,3,3] $
4. $ [1,3,4,3,3] $
5. $ [1,3,4,3,3] $

For the second testcase, some optimal ways of dividing army into squads for each $ k $ are:

1. $ [1],[5],[7],[8],[1],[7],[6],[1] $
2. $ [1,5],[7,8],[1,7],[6,1] $
3. $ [1,5,7],[8],[1,7,6,1] $
4. $ [1,5,7,8],[1,7,6,1] $
5. $ [1,5,7,8,1,7,6,1] $
6. $ [1,5,7,8,1,7,6,1] $
7. $ [1,5,7,8,1,7,6,1] $
8. $ [1,5,7,8,1,7,6,1] $

## 样例 #1

### 输入

```
5
1 3 4 3 3
```

### 输出

```
4 2 1 1 1 
```

## 样例 #2

### 输入

```
8
1 5 7 8 1 7 6 1
```

### 输出

```
8 4 3 2 1 1 1 1 
```

# AI分析结果



### 算法分类
根号分治、贪心、二分

---

### 题解思路与解决难点
**核心思路**：将问题分为小规模和大规模两部分处理  
- **小规模**（k ≤ √n）：直接暴力贪心分段，每次尽可能向后扩展直到颜色数超过k  
- **大规模**（k > √n）：答案范围不超过√n，枚举答案并二分确定对应的k区间  

**关键难点与突破**：  
1. **根号分治的平衡点选择**：分界点选为√n，使得暴力处理小规模的总时间复杂度为O(n√n)  
2. **答案单调性利用**：答案随k增大单调不增，允许通过二分快速确定相同答案的k区间  
3. **高效分段实现**：在暴力分段时使用数组标记当前颜色，通过重置标记而非全局清空降低复杂度  

---

### 题解评分（≥4星）
1. **When（5星）**  
   - 思路清晰：明确划分根号分治的两种处理方式  
   - 代码简洁：仅用约30行实现核心逻辑，易读性强  
   - 巧妙优化：通过二分跳跃式处理大规模k，显著减少计算次数  

2. **Legitimity（4星）**  
   - 创新性：利用树状数组维护颜色数，实现O(n log²n)复杂度  
   - 空间优化：动态队列处理代替可持久化结构，空间O(n)  
   - 实现复杂度：代码较复杂，涉及链表预处理与树状数组操作  

3. **ARIS2_0（4星）**  
   - 独特视角：直接维护每个分块的颜色数，实现O(n√n)复杂度  
   - 动态更新：通过移动右端点更新分块信息，无需复杂数据结构  
   - 代码可读性：实现细节较多，需理解分块移动的同步更新  

---

### 最优思路提炼
**根号分治 + 二分跳跃**  
1. 分界点选取√n，暴力处理小规模k  
2. 对大规模k计算当前答案后，二分确定相同答案的连续k区间  
3. 时间复杂度从O(n²)优化至O(n√n + n√n logn)  

**代码实现要点**：  
```cpp
int work(int k){ // 暴力分段函数
    memset(T,0,sizeof(T));
    int sum=0, cnt=0, sta=1;
    for(int i=1; i<=n; ++i){
        if(!T[a[i]]) T[a[i]]=1, cnt++;
        if(cnt>k){ // 超过颜色限制
            sum++, cnt=1;
            for(int j=sta; j<i; ++j) T[a[j]]=0; // 仅重置当前段标记
            T[a[i]]=1; sta=i;
        }
    }
    return sum + (cnt>0);
}
// 主逻辑中的二分跳跃
for(int k=1; k<=n; ++k){
    if(k <= siz) printf("%d ", work(k));
    else{
        Ans = work(k);
        int l=k, r=n;
        while(l<=r){ // 二分确定相同答案区间
            mid = (l + r) >> 1;
            if(work(mid) < Ans) r=mid-1;
            else l=mid+1;
        }
        for(int i=k; i<=l-1; ++i) printf("%d ", Ans);
        k = l-1; // 跳跃处理
    }
}
```

---

### 相似题目推荐
1. **P1972 [SDOI2009] HH的项链**  
   - 区间颜色数统计，可持久化线段树经典应用  
2. **P4137 Rmq Problem / mex**  
   - 区间mex查询，根号分治与离线处理结合  
3. **CF220B Little Elephant and Array**  
   - 频率相关的区间查询，分块处理优化  

---

### 可视化设计
**8位像素风格分段演示**  
1. **颜色标记**：  
   - 当前段用绿色高亮，历史段用灰色  
   - 超过k种颜色时触发红色闪烁警告  
2. **动画流程**：  
   - 从左到右扫描数列，显示当前颜色计数  
   - 触发分段时播放"像素爆破"特效，重置计数器  
3. **音效设计**：  
   - 正常移动：8-bit "哔"声  
   - 成功分段：经典马里奥跳跃音  
   - 警告触发：红白机炸弹爆炸音  
4. **控制面板**：  
   - 滑动条调节k值，实时显示分段变化  
   - 支持暂停/继续观察分段细节  

---

### 核心算法动画演示（伪代码）
```javascript
// Canvas绘制核心逻辑
function drawStep(k) {
  let colors = new Set();
  let segments = [];
  for(let i=0, start=0; i<array.length; i++) {
    colors.add(array[i]);
    ctx.fillStyle = getColor(array[i]); // 随机生成色块
    ctx.fillRect(i*BLOCK_W, 0, BLOCK_W, BLOCK_H);
    
    if(colors.size > k) { // 触发分段
      playSound('explosion');
      segments.push([start, i-1]);
      start = i;
      colors = new Set([array[i]]);
      ctx.fillStyle = '#FF0000'; // 红色分割线
      ctx.fillRect((i-0.5)*BLOCK_W, 0, 2, BLOCK_H);
    }
  }
  // 绘制剩余段
  segments.push([start, array.length-1]);
  updateCounter(segments.length);
}
```

---

**总结**：根号分治结合二分跳跃是本题的最优解法，平衡了时间效率与实现难度。可视化设计通过复古像素风格直观展示分段过程，帮助理解贪心策略的核心思想。

---
处理用时：85.41秒