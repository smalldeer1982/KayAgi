# 题目信息

# [USACO18DEC] Sort It Out P

## 题目描述

FJ 有 $N$（$1 \leq N \leq 10^5$）头奶牛（分别用 $1 \ldots N$ 编号）排成一行。FJ 喜欢他的奶牛以升序排列，不幸的是现在她们的顺序被打乱了。在过去，FJ 曾经使用一些诸如“冒泡排序”的开创性算法来使他的奶牛排好序，但今天他想偷个懒。取而代之，他会每次对着一头奶牛叫道“按顺序排好”。当一头奶牛被叫到的时候，她会确保自己在队伍中的顺序是正确的（从她的角度看来）。当有一头紧接在她右边的奶牛的编号比她小，她们就交换位置。然后，当有一头紧接在她左边的奶牛的编号比她大，她们就交换位置。这样这头奶牛就完成了“按顺序排好”，在这头奶牛看来左边的奶牛编号比她小，右边的奶牛编号比她大。

FJ 想要选出这些奶牛的一个子集，然后遍历这个子集，依次对着每一头奶牛发号施令（按编号递增的顺序），重复这样直到所有 $N$ 头奶牛排好顺序。例如，如果他选出了编号为 $\{2,4,5\}$ 的奶牛的子集，那么他会喊叫奶牛 $2$，然后是奶牛 $4$，然后是奶牛 $5$。如果 $N$ 头奶牛此时仍未排好顺序，他会再次对着这几头奶牛喊叫，如果有必要的话继续重复。

由于 FJ 不确定哪些奶牛比较专心，他想要使得这个子集最小。此外，他认为 $K$ 是个幸运数字。请帮他求出满足重复喊叫可以使得所有奶牛排好顺序的最小子集之中字典序第 $K$ 小的子集。

我们称 $\{1, \ldots ,N\}$ 的一个子集 $S$ 在字典序下小于子集 $T$，当 $S$ 的所有元素组成的序列（按升序排列）在字典序下小于 $T$ 的所有元素组成的序列（按升序排列）。例如，$\{1,3,6\}$ 在字典序下小于 $\{1,4,5\}$。

## 说明/提示

开始的时候序列为 $ \mathtt{\:4\:\; 2\:\; 1\:\; 3\:} $ 。在FJ喊叫编号为 $ 1 $ 的奶牛之后，序列变为 $ \mathtt{\:1\:\; 4\:\; 2\:\; 3\:} $ 。在FJ喊叫编号为 $ 4 $ 的奶牛之后，序列变为 $ \mathtt{\:1\:\; 2\:\; 3\:\; 4\:} $ 。在这个时候，序列已经完成了排序。

## 子任务

对于占总分 $ 3/16 $ 的测试数据， $ N \leq 6 $ ，并且 $ K=1 $ 。

对于另外的占总分 $ 5/16 $ 的测试数据， $ K=1 $ 。

对于另外的占总分 $ 8/16 $ 的测试数据，没有其他限制。

## 样例 #1

### 输入

```
4 1
4 2 1 3
```

### 输出

```
2
1
4
```

# AI分析结果



# 题解分析

## 算法分类
动态规划、贪心、树状数组

## 题解思路与核心难点
1. **问题转化**：发现合法的子集补集必须构成递增序列，转化为求最长递增子序列（LIS）及其补集。  
2. **字典序处理**：字典序第K小的补集等价于原序列的字典序第K大LIS。  
3. **动态规划优化**：从后往前用树状数组维护每个元素作为LIS开头时的最大长度和方案数。  
4. **试填法**：按LIS长度分层，从大到小枚举元素，通过方案数确定是否选中当前元素。

## 题解评分（≥4星）
1. **Mirach（5星）**  
   - 思路清晰，树状数组优化LIS计数  
   - 链式前向星分层处理，代码简洁高效  
   - 核心代码片段高亮关键逻辑  
   ```cpp
   for(int stp=qy(1).v,R=0;stp;--stp)
   for(int i=head[stp],v;i;i=e[i].nxt){
       v=e[i].v;
       if(g[v].c<k)k-=g[v].c;
       else { chs[a[v]]=true; break; }
   }
   ```
   
2. **xianglingao（4星）**  
   - 逆排列转换简化字典序处理  
   - 树状数组维护后缀信息  
   - 试填法逐层选择元素  
   ```cpp
   for(int i=m,pos=0;i>=1;--i){
       for(int j:vec[i]) if(b[j]>=pos && k<=c[j]){
           use[j]=true; pos=b[j]; break;
       }
   }
   ```

3. **Graphcity（4星）**  
   - 分层处理LIS，树状数组优化  
   - 动态开点线段树处理方案数  
   ```cpp
   void update(int x,node y){
       for(;x;x-=x&-x) bit[x]+=y;
   }
   ```

## 最优思路提炼
1. **LIS计数优化**  
   使用树状数组维护后缀最大值和方案数，从后往前处理元素。每个元素通过查询比它大的元素中最长的LIS长度，并累加方案数。

2. **字典序试填法**  
   按LIS长度分层，每层从大到小枚举元素。若当前元素方案数不足则跳过，否则选中并更新剩余K值。

3. **逆序转换技巧**  
   将原序列转换为逆排列 `b[a[i]]=i`，使字典序比较转化为下标比较，简化处理逻辑。

## 相似题目推荐
1. [P3308 SDOI2014 LIS](https://www.luogu.com.cn/problem/P3308)  
   （LIS最小割与方案构造）
2. [P4303 基因匹配](https://www.luogu.com.cn/problem/P4303)  
   （LCS转化为LIS的树状数组优化）
3. [P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439)  
   （排列LCS转LIS）

## 个人心得摘录
> "字典序第K大的LIS需要逆向思维，先处理高层再试填。树状数组的链式存储让分层更高效。" —— Mirach

## 算法可视化设计
### 核心逻辑演示
1. **树状数组更新**  
   - **动画**：展示从右向左扫描元素，树状数组节点动态更新最大值和方案数。  
   - **高亮**：当前处理元素及其对应的树状数组更新路径（红色闪烁）。  
   ```javascript
   // 伪代码：树状数组更新动画
   function updateAnimation(element, value) {
       highlight(element);
       for(let i=element; i>0; i-=i&-i){
           flashTreeBit(i); // 树状数组节点闪烁
       }
   }
   ```

2. **试填法选择过程**  
   - **动画**：按LIS长度分层显示候选元素，绿色表示选中，红色表示跳过。  
   - **音效**：选中时播放"coin.wav"，跳过时播放"error.wav"。  
   ```javascript
   // 伪代码：试填选择动画
   function selectElement(candidates, K) {
       for(let elem of candidates) {
           if(elem.value >= K) {
               playSound("coin.wav");
               markAsSelected(elem);
               K -= elem.value;
               break;
           } else {
               playSound("error.wav");
               K -= elem.value;
           }
       }
   }
   ```

### 复古像素风格实现
1. **Canvas绘制**  
   - **网格布局**：每个元素显示为16x16像素方块，颜色表示LIS长度（蓝→黄渐变）。  
   - **动态效果**：选中元素时方块变为绿色并放大10%。  
   ```html
   <canvas id="pixelGrid"></canvas>
   <script>
   function drawElement(x, y, color) {
       ctx.fillStyle = color;
       ctx.fillRect(x*20, y*20, 16, 16);
   }
   </script>
   ```

2. **8位音效**  
   - **背景音乐**：循环播放芯片音乐（[chiptune.js](https://github.com/richtaur/chiptune2.js)）。  
   - **音效触发**：选中元素时播放上升音阶，错误时播放低音。  

---

**核心代码片段（树状数组+LIS计数）**
```cpp
struct node{ int mx; ll cnt; };
vector<int> vec[N]; // 按LIS长度分层存储元素

for(int i=n; i; --i) {
    node res = query(a[i]+1); // 树状数组查询后缀最大值
    res.mx++;
    vec[res.mx].push_back(i);
    add(a[i], res); // 树状数组更新
}

// 试填法选择字典序第K大LIS
int cur_pos = 0;
for(int len = max_lis; len >=1; --len) {
    for(int elem : vec[len]) {
        if(pos[elem] < cur_pos) continue;
        if(k > cnt[elem]) k -= cnt[elem];
        else { select(elem); break; }
    }
}
```

---
处理用时：91.73秒