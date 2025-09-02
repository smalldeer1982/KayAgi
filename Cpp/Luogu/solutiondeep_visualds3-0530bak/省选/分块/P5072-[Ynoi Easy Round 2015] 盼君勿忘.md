# 题目信息

# [Ynoi Easy Round 2015] 盼君勿忘

## 题目背景

说起来，幸福本身就是因人而异的  
有些人认为只要能混口饭吃就行了  
有些人只要有书读就能满足  
![](https://cdn.luogu.com.cn/upload/pic/45571.png)  
有些人认为只有全力地生存才是最重要的  
有些人只要得到克服某种目标的瞬间就能满足  
有些人只要某个人得到幸福，自己就会跟着幸福  
也有些人则令人伤透脑筋地刚好相反  
![](https://cdn.luogu.com.cn/upload/pic/45572.png)
但是，大部分人都没有自觉  
他们不知道究竟什么能给自己带来幸福  
但是，他们会异口同声地表示想要获得幸福  
那样的人即使能察觉到幸福  
也没办法变得幸福  
最重要的是要敢于正视自己的内心  
![](https://cdn.luogu.com.cn/upload/pic/45573.png)  
【珂朵莉已经基本上不剩什么了】  
![](https://cdn.luogu.com.cn/upload/pic/45574.png)  
【心灵和身体，珂朵莉基本上快要全部失去了】  
![](https://cdn.luogu.com.cn/upload/pic/45575.png)  
【全部被我替换了】  
![](https://cdn.luogu.com.cn/upload/pic/45576.png)  
【幸好你在失去一切之前，回到了这里】  
【喜悦和悲伤】  
【还有喜欢某个人的情绪】  
【现在依旧还残存着一些吧？】  
嗯...  
确实还有那么一丝...  
【那就没问题了】  
【珂朵莉你，依旧是珂朵莉】  
![](https://cdn.luogu.com.cn/upload/pic/45578.png)  
![](https://cdn.luogu.com.cn/upload/pic/45579.png)  
威...廉...？   
![](https://cdn.luogu.com.cn/upload/pic/45580.png)  


## 题目描述

珂朵莉给了你一个序列，每次查询一个区间 $[l,r]$ 中所有子序列分别去重后的和 $\bmod\ p$。

## 说明/提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

对于 $100\%$ 的数据，$1\leq n,m,a_i \leq 10^5$，$1\leq p\leq 10^9$，$1\leq l\leq r\leq n$。

## 样例 #1

### 输入

```
5 5
1 2 2 3 4
1 2 233333
2 3 333333
1 5 5
3 5 15
2 4 8```

### 输出

```
6
6
1
6
0```

# AI分析结果



## 算法分类  
**莫队算法 + 根号分治 + 光速幂**

---

## 题解核心分析  

### 算法逻辑框架  
1. **贡献拆解**：每个元素的贡献为 `x*(2^len - 2^(len-cnt))`，其中 `len` 是区间长度，`cnt` 是该元素的出现次数  
2. **莫队维护**：动态维护区间内不同出现次数的元素和  
3. **根号分治**：  
   - 出现次数 ≤√n 的元素，通过链表维护  
   - 出现次数 >√n 的元素，单独记录（此类元素最多 √n 个）  
4. **光速幂优化**：预处理 2^k mod p 的值，支持 O(1) 查询  

### 解决难点对比  
| 题解作者 | 数据结构 | 光速幂处理 | 优化亮点 |  
|---------|---------|-----------|---------|  
| chenzida | 双向链表 | √n 分块 | 理论推导最清晰 |  
| rui_er | 双向链表 | 动态调整块大小 | 手写链表实现高效 |  
| mrsrz | unordered_set | 分块预处理 | STL容器简化代码 |  
| SIXIANG32 | 双向链表 | 特殊块大小 | 代码结构最简洁 |  

---

## 题解评分 (≥4★)  
1. **chenzida (★★★★★)**  
   - 贡献推导完整，光速幂预处理逻辑清晰  
   - 完整注释关键公式 `(2^t-2^{t-k})x` 的推导过程  
   - 代码含理论证明，适合学习算法原理  

2. **rui_er (★★★★☆)**  
   - 手写双向链表实现 O(1) 插入/删除  
   - 动态调整光速幂块大小至 `SIZE = sqrt(r-l+1)`  
   - 代码含详细调试日志输出接口  

3. **mrsrz (★★★★☆)**  
   - 使用 `unordered_set` 维护出现次数  
   - 分块预处理时处理到 `sqrt(len)` 优化空间  
   - 代码风格紧凑，适合快速实现  

---

## 最优技巧提炼  
1. **光速幂双数组法**  
```cpp  
void init_pow(int mod) {  
    pow1[0] = pow2[0] = 1;  
    for(int i=1; i<=blk; i++) pow1[i] = pow1[i-1] * 2 % mod;  
    for(int i=1; i<=blk; i++) pow2[i] = pow2[i-1] * pow1[blk] % mod;  
}  
inline int qpow(int x) { return pow1[x%blk] * pow2[x/blk] % mod; }  
```  
- 预处理 `pow1` 存储 2^0~2^blk  
- 预处理 `pow2` 存储 2^(blk*0), 2^(blk*1)...  

2. **莫队移动优化**  
```cpp  
// 奇偶块排序减少指针震荡  
bool operator < (const Query &b) const {  
    if(pos != b.pos) return l < b.l;  
    return (pos & 1) ? r < b.r : r > b.r;  
}  
```  

3. **链表维护出现次数**  
```cpp  
struct Linked_List {  
    int pre[N], nxt[N], tot;  
    void insert(int x) { nxt[tot]=x, pre[x]=tot, tot=x; }  
    void erase(int x) {  
        if(x != tot) nxt[pre[x]] = nxt[x], pre[nxt[x]] = pre[x];  
        else tot = pre[x];  
    }  
};  
```  

---

## 同类型题推荐  
1. **P1494 [国家集训队] 小Z的袜子**  
   - 莫队统计区间颜色出现次数的经典题  

2. **P3709 大爷的字符串题**  
   - 需要维护出现次数最大值，适合练习根号分治  

3. **P5071 [Ynoi2015] 此时此刻的光辉**  
   - 类似的时间复杂度要求，结合数论分解  

---

## 可视化设计要点  
### 动画演示逻辑  
1. **莫队指针移动**  
   - 用两个色块标记当前 l/r 指针位置  
   - 每次移动时显示增/删元素的数值和颜色  

2. **出现次数更新**  
   - 当元素加入区间时，旧计数红色闪烁后消失  
   - 新计数绿色高亮显示  

3. **贡献计算过程**  
   - 遍历链表时，当前处理的出现次数 k 显示为黄色  
   - 光速幂计算时显示分解过程：`2^15 = 2^(3*5) * 2^0`  

### 像素风格实现  
```javascript  
// Canvas 绘制示例  
function drawBlock(x, y, color) {  
    ctx.fillStyle = color;  
    ctx.fillRect(x*16, y*16, 15, 15);  
}  
// 音效触发  
function playSound(type) {  
    const sfx = { add: [500,0.2], del: [300,0.1], calc: [800,0.3] };  
    osc.frequency.value = sfx[type][0];  
    gain.gain.value = sfx[type][1];  
}  
```  
- **颜色方案**：红色(l指针)、蓝色(r指针)、绿色(新增)、黄色(当前计算)  
- **音效**：加入元素高音，删除元素低音，计算完成时和弦音  

---

## 关键代码片段  
**光速幂预处理与查询**  
```cpp  
void init(int mod) {  
    int blk = sqrt(mod) + 1;  
    pow1[0] = 1;  
    for(int i=1; i<=blk; ++i)   
        pow1[i] = pow1[i-1] * 2 % mod;  
    pow2[0] = 1;  
    for(int i=1; i<=blk; ++i)  
        pow2[i] = pow2[i-1] * pow1[blk] % mod;  
}  
inline int qpow(int x, int mod) {  
    return 1LL * pow1[x%blk] * pow2[x/blk] % mod;  
}  
```  

**莫队增删元素**  
```cpp  
void add(int pos) {  
    int x = a[pos];  
    sum[cnt[x]] -= x;          // 旧计数  
    if(!sum[cnt[x]]) list.del(cnt[x]);  
    cnt[x]++;  
    if(!sum[cnt[x]]) list.add(cnt[x]);  
    sum[cnt[x]] += x;          // 新计数  
}  
```  

---

## 个人调试心得摘录  
> "光速幂块大小设成 sqrt(n) 后 WA，改为 sqrt(len) 后 AC —— 必须根据当前区间长度动态调整块大小才能保证精度"  
> "手写链表比 unordered_set 快 3 倍，但要注意删除头结点时的边界条件"  
> "贡献公式中的减法需要加 mod 再取模，否则会有负数导致 WA"  

---

## 扩展思考  
当模数 p 较小时（如 p ≤1e5），可预先生成所有可能的 2^k mod p 值，进一步优化常数。此外，对于极大数据可使用四光速幂分块（将指数分解为 k = a*blk^3 + b*blk^2 + c*blk + d）

---
处理用时：108.28秒