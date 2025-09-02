# 题目信息

# XOR on Segment

## 题目描述

You've got an array $ a $ , consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . You are allowed to perform two operations on this array:

1. Calculate the sum of current array elements on the segment $ [l,r] $ , that is, count value $ a_{l}+a_{l+1}+...+a_{r} $ .
2. Apply the xor operation with a given number $ x $ to each array element on the segment $ [l,r] $ , that is, execute ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a6ed6800239445c652bf1618450a09b2fce8b86d.png). This operation changes exactly $ r-l+1 $ array elements.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF242E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise xor operation to numbers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example in language C++ and Java it is marked as "^", in Pascal — as "xor".

You've got a list of $ m $ operations of the indicated type. Your task is to perform all given operations, for each sum query you should print the result you get.

## 样例 #1

### 输入

```
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3
```

### 输出

```
26
22
0
34
11
```

## 样例 #2

### 输入

```
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3
```

### 输出

```
38
28
```

# AI分析结果



# 算法分类
线段树+位运算拆位

# 综合分析与结论
## 核心思路与难点
本题需维护区间异或和区间求和操作。直接暴力处理区间异或时间复杂度不可接受，需采用拆位线段树。将每个数拆分为20个二进制位，对每个二进制位建立线段树维护该位为1的个数。异或操作时，若x某位为1则翻转区间内该位的状态（1变0，0变1），求和时累加各二进制位的贡献。

关键难点在于：
1. 异或操作的不可叠加性，传统懒标记无法直接使用
2. 需要将数值拆解为独立二进制位处理
3. 如何高效维护每个二进制位的状态变更

## 题解对比与评分
### 评分 ≥4星题解
1. **gzw2005（5星）**  
   核心思路清晰，代码结构简洁。通过维护线段树节点中每个二进制位的1的数量，异或时根据x的二进制位决定是否翻转。代码实现中将20个二进制位压缩存储在同一线段树节点中，空间利用率高。

2. **SymphonyOfEuler（4星）**  
   使用21棵独立线段树分别维护每个二进制位，逻辑直观但空间消耗较大。亮点在于每个线段树独立维护，便于理解拆位思想。

3. **do_while_true（4星）**  
   通过位运算性质推导异或操作的叠加性，提出奇偶次异或等效性。代码实现中通过tag记录异或次数，为理解线段树懒标记提供新视角。

## 最优思路与代码实现
**拆位线段树核心逻辑：**
```cpp
struct Node {
    int cnt[21];    // 每个二进制位1的个数
    int tag;        // 异或标记
} tree[N<<2];

void push_down(int node, int l, int r) {
    for(int i=0; i<20; ++i) {
        if((tree[node].tag >> i) & 1) { // 需要翻转的位
            int mid = (l+r)/2;
            tree[left].cnt[i] = (mid-l+1) - tree[left].cnt[i];
            tree[right].cnt[i] = (r-mid) - tree[right].cnt[i];
        }
    }
    tree[left].tag ^= tree[node].tag;
    tree[right].tag ^= tree[node].tag;
    tree[node].tag = 0;
}
```

## 同类型题目
1. **P2574 XOR的艺术** - 区间取反与求和
2. **P4145 上帝造题的七分钟2** - 区间开方与求和
3. **P1558 色板游戏** - 位运算颜色混合

# 可视化设计
## 动画方案
1. **拆位展示**  
   以20个并排的像素条表示每个二进制位，颜色深浅表示该位1的密度。异或操作时，对应位条闪烁并翻转颜色。

2. **线段树操作高亮**  
   - 更新时：当前处理的区间边框变为红色
   - 懒标记下传时：子节点闪烁黄色
   - 求和时：贡献值以气泡形式从各二进制位升起

3. **复古像素风格**  
   ```javascript
   // 绘制线段树节点（示例）
   function drawNode(x, y, bits) {
       ctx.fillStyle = '#2C3E50'; // 深蓝背景
       ctx.fillRect(x, y, 32, 32);
       for(let i=0; i<20; ++i) {
           if(bits & (1<<i)) { // 绘制二进制位
               ctx.fillStyle = ['#E74C3C','#27AE60'][i%2];
               ctx.fillRect(x+i%4*8, y+Math.floor(i/4)*8, 6, 6);
           }
       }
   }
   ```

## 交互功能
- **速度调节**：滑块控制动画速度（0.5x~4x）
- **位过滤**：勾选特定二进制位观察其变化
- **历史回退**：记录操作步骤可回溯任意时刻状态

# 题解推荐代码（gzw2005版）
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=1e5+2;
int cnt[MAXN<<2][20],tag[MAXN<<2];

void update(int L,int R,int cur,int l,int r,int val){
    if(R<l||r<L)return;
    if(l<=L && R<=r){
        for(int i=0;i<20;i++)
            if((val>>i)&1) cnt[cur][i]=(R-L+1)-cnt[cur][i];
        tag[cur]^=val;
        return;
    }
    int mid=(L+R)>>1;
    // 下传标记逻辑...
    update(L,mid,ls(cur),l,r,val);
    update(mid+1,R,rs(cur),l,r,val);
    for(int i=0;i<20;i++) 
        cnt[cur][i]=cnt[ls(cur)][i]+cnt[rs(cur)][i];
}

long long query(int L,int R,int cur,int l,int r){
    if(R<l||r<L)return 0;
    if(l<=L && R<=r){
        long long ret=0,Pow=1;
        for(int i=0;i<20;i++){
            ret+=Pow*cnt[cur][i];
            Pow<<=1;
        }
        return ret;
    }
    // 下传标记...
    return query(L,mid,ls(cur),l,r)+query(mid+1,R,rs(cur),l,r);
}
```

# 总结与扩展
本题的拆位思想可延伸至其他位运算问题，如区间与/或操作时，可针对每个二进制位分析其变化规律。当遇到类似"区间操作+复杂位运算"的组合问题时，拆位维护往往是突破时间复杂度瓶颈的关键。

---
处理用时：115.75秒