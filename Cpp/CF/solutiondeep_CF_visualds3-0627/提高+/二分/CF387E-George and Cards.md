# 题目信息

# George and Cards

## 题目描述

George is a cat, so he loves playing very much.

Vitaly put $ n $ cards in a row in front of George. Each card has one integer written on it. All cards had distinct numbers written on them. Let's number the cards from the left to the right with integers from $ 1 $ to $ n $ . Then the $ i $ -th card from the left contains number $ p_{i} $ ( $ 1<=p_{i}<=n $ ).

Vitaly wants the row to have exactly $ k $ cards left. He also wants the $ i $ -th card from left to have number $ b_{i} $ written on it. Vitaly gave a task to George, to get the required sequence of cards using the remove operation $ n-k $ times.

In one remove operation George can choose $ w $ ( $ 1<=w $ ; $ w $ is not greater than the current number of cards in the row) contiguous cards (contiguous subsegment of cards). Let's denote the numbers written on these card as $ x_{1},x_{2},...,x_{w} $ (from the left to the right). After that, George can remove the card $ x_{i} $ , such that $ x_{i}<=x_{j} $ for each $ j $ $ (1<=j<=w) $ . After the described operation George gets $ w $ pieces of sausage.

George wondered: what maximum number of pieces of sausage will he get in total if he reaches his goal and acts optimally well? Help George, find an answer to his question!

## 样例 #1

### 输入

```
3 2
2 1 3
1 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 5
1 2 3 4 5 6 7 8 9 10
2 4 6 8 10
```

### 输出

```
30
```

# AI分析结果



**唯一算法分类**：二分

---

### **综合分析与结论**

**核心思路**：  
所有题解均采用贪心策略，按数值**从小到大删除**未被保留的卡片。使用 `set` 维护保留卡片的位置，通过二分查找确定当前删除卡片的左右边界，结合树状数组/线段树快速统计区间剩余卡片数。

**二分关键点**：  
- **搜索区间**：`set` 中通过 `lower_bound` 二分查找当前卡片位置的左右边界。  
- **收缩条件**：左边界为前驱保留卡片位置+1，右边界为后继保留卡片位置-1。  
- **边界处理**：若无前驱/后继，则取序列的起点/终点。

**可视化设计思路**：  
1. **像素风格动画**：用网格表示卡片序列，当前处理的卡片高亮为红色，左右边界标记为绿色。  
2. **步进演示**：展示 `set` 插入保留卡片、二分查找边界、树状数组更新过程。  
3. **音效反馈**：删除卡片时播放“得分”音效，插入保留卡片时播放“确认”音效。

---

### **题解清单 (≥4星)**

1. **作者：wsyhb（5赞）**  
   **评分**：⭐️⭐️⭐️⭐️⭐️  
   **亮点**：思路清晰，树状数组与 `set` 结合高效，代码注释完整。

2. **作者：Saliеri（2赞）**  
   **评分**：⭐️⭐️⭐️⭐️⭐️  
   **亮点**：代码极简，树状数组与 `set` 实现仅 30 行，逻辑高度凝练。

3. **作者：_zuoqingyuan（1赞）**  
   **评分**：⭐️⭐️⭐️⭐️  
   **亮点**：详细分步解析，树状数组操作注释明确，适合新手理解。

---

### **最优思路与代码实现**

**关键思路**：  
1. 预处理每个数的位置 `pos[]`，标记保留数 `mark[]`。  
2. 按数值升序遍历，保留数插入 `set`，删除数通过二分确定左右边界。  
3. 树状数组维护剩余卡片数，累加区间贡献后删除当前卡片。

**核心代码**（Saliеri 题解）：
```cpp
#include <set>
#include <cstdio>
const int maxn = 1e6+5;
int n,k,a[maxn],inb[maxn],pos[maxn],c[maxn];
void update(int pos,int v){for(;pos<=n;pos+=(pos&-pos))c[pos] += v;}
int sum(int pos){
    int res = 0;
    for(;pos;pos-=(pos&(-pos)))res += c[pos];
    return res;
}
std :: set<int> p;
long long ans;
int main(){
    scanf("%d %d",&n,&k);
    for(int i=1,v;i<=n;++i)
        scanf("%d",&v),pos[v] = i,update(i,1);
    for(int i=1,v;i<=k;++i)
        scanf("%d",&v),inb[v] = 1;
    p.insert(0),p.insert(n+1);
    std :: set<int> :: iterator it1,it2;
    for(int i=1;i<=n;++i){
        if(!inb[i]){
            it1 = it2 = p.lower_bound(pos[i]), --it1;
            ans += sum((*it2)-1) - sum((*it1));
            update(pos[i],-1);
        }
        else p.insert(pos[i]);
    }
    printf("%lld",ans);
    return 0;
}
```

---

### **同类型题与拓展**

**类似题目**：  
1. **P1908 逆序对**：树状数组维护离散化后的数值位置。  
2. **P3380 【模板】二逼平衡树**：树套树或分块处理区间第 k 大。  
3. **P3919 【模板】可持久化线段树**：历史版本查询与二分结合。

**通用套路**：  
- **贪心+二分**：当操作顺序影响结果时，贪心排序后结合二分快速定位。  
- **离散化+树状数组**：处理动态区间统计问题，如逆序对、区间和。

---

### **复古游戏化动画设计**

**Canvas 动画**：  
1. **初始化**：绘制 n 个格子代表卡片，颜色按数值梯度填充。  
2. **处理流程**：  
   - **高亮当前数**：红色闪烁，显示数值和位置。  
   - **二分边界**：绿色标记左右保留卡片位置，黄色覆盖可删除区间。  
   - **得分更新**：区间长度以像素爆炸效果展示，分数栏递增。  

**音效设计**：  
- **插入保留卡片**：8-bit “确认”音（短促高音）。  
- **删除卡片**：得分音效（连续升调音符）。  
- **错误操作**：低沉“哔”声。

**AI 自动模式**：  
- 自动按数值升序处理卡片，每步延迟 1s，显示二分查找的收缩过程。

---

### **个人心得摘录**

- **作者：toolong114514**：线段树二分 TLE 后改用 `set`，意识到“暴力不如 STL 优雅”。  
- **作者：Hoks**：笛卡尔树合并尝试失败，回归贪心+数据结构更高效。

---
处理用时：63.91秒