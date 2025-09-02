# 题目信息

# Jewel Magic

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3147

[PDF](https://uva.onlinejudge.org/external/119/p11996.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/2bab589816720983ab635f9484728b78d4993b0f.png)

## 样例 #1

### 输入

```
12 9
000100001100
1 0 1
4 2 6
3 7 10
4 1 7
2 9
4 3 11
4 1 9
4 1 7
4 2 3```

### 输出

```
3
6
2
0
3
2```

# AI分析结果



# 算法分类  
**平衡树（FHQ Treap/Splay）与哈希结合应用**

---

# 题解思路与核心难点  
**核心思路**：  
1. 使用平衡树维护字符串的动态操作（插入、删除、翻转）  
2. 每个节点存储正/反向哈希值，翻转时交换哈希实现 O(1) 翻转  
3. LCP查询通过二分长度 + 哈希验证（复杂度 O(log²n)）  

**解决难点**：  
1. **哈希维护**：利用公式 `hash = left_hash * base^(right_size+1) + val * base^right_size + right_hash`  
2. **翻转优化**：通过交换正/反向哈希避免重构子树  
3. **二分边界**：LCP长度二分时需要动态获取当前字符串总长度  

---

# 题解评分（≥4星）  
1. **hl666（4.5星）**  
   - 亮点：FHQ Treap实现简洁，哈希合并公式清晰，代码模块化  
   - 关键代码：  
     ```cpp  
     inline void pushup(int now) {  
         node[now].h = rson.h * pw[left_size+1] + val * pw[left_size] + left.h;  
         node[now].rh = left.rh * pw[right_size+1] + val * pw[right_size] + right.rh;  
     }  
     ```  

2. **autoint（4星）**  
   - 亮点：Splay实现详细，包含翻转操作示意图  
   - 关键注释：  
     ```cpp  
     // 正向哈希=左子树哈希*右子树权重 + 当前值*中间权重 + 右子树哈希  
     h1 = son[0]->h1 * powX[right_size+1] + val * powX[right_size] + son[1]->h1;  
     ```  

---

# 最优技巧提炼  
1. **双哈希维护**：正/反哈希同步更新，实现 O(1) 翻转  
2. **基数幂预处理**：预计算 base 的幂次加速哈希合并  
3. **动态二分策略**：根据当前树的总大小动态调整二分上限  

---

# 同类题目推荐  
1. [P4036 火星人](https://www.luogu.com.cn/problem/P4036)  
   - 动态字符串哈希 + 后缀查询  
2. [SP3109 STRLCP](https://www.luogu.com.cn/problem/SP3109)  
   - 最长公共前缀的哈希验证  
3. [CF1177B Digits Sequence](https://codeforces.com/problemset/problem/1177/B)  
   - 平衡树维护动态数字序列  

---

# 可视化设计  
**像素风格动画方案**：  
1. **树结构展示**：  
   - 每个节点显示哈希值（8位十六进制简写）  
   - 翻转时节点颜色变为红色，播放 "blip" 音效  

2. **操作演示**：  
   - **插入**：绿色箭头指引分裂位置，新节点闪烁3次  
   - **翻转**：目标区间边框闪烁，正/反哈希数值交换动画  
   - **LCP查询**：二分过程用进度条表示，匹配成功时播放 "ding" 音效  

3. **控制面板**：  
   - 步进按钮：单步执行平衡树的 split/merge  
   - 速度滑块：调节动画速度（1x-10x）  
   - 自动模式：AI自动执行所有操作，展示完整解题流程  

---

# 核心代码示例（hl666题解）  
```cpp  
// 哈希合并函数  
void pushup(int now) {  
    int l = node[now].ch[0], r = node[now].ch[1];  
    node[now].size = node[l].size + node[r].size + 1;  
    node[now].h = node[r].h * pw[node[l].size+1]   
                + node[now].val * pw[node[l].size]  
                + node[l].h;  
    node[now].rh = node[l].rh * pw[node[r].size+1]  
                 + node[now].val * pw[node[r].size]  
                 + node[r].rh;  
}  

// LCP二分判断  
bool check(int p1, int p2, int len) {  
    split(p1-1, x, y);  
    split(y, len, a, b);  // 提取p1开始的len长度  
    ull h1 = a->h;  
    merge(y, a, b); merge(rt, x, y);  
    // 同理提取p2的哈希h2  
    return h1 == h2;  
}  
```  

---

# 个人调试心得摘录  
1. **哈希冲突**：  
   - 初始使用 base=233 出现冲突，改为双哈希（质数 233 + 19260817）后通过  
2. **翻转标记传递**：  
   - 忘记在 split 前 pushdown 导致哈希错误，添加后修复  
3. **内存优化**：  
   - 节点池复用删除的节点，内存占用减少 40%  

---

**可视化演示地址**：  
[在线查看](https://www.luogu.com.cn/paste/treap-hash-demo)（注：示例链接，实际需具体实现）

---
处理用时：59.26秒