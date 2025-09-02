# 题目信息

# Cost Equilibrium

## 题目描述

An array is called beautiful if all the elements in the array are equal.

You can transform an array using the following steps any number of times:

1. Choose two indices $ i $ and $ j $ ( $ 1 \leq i,j \leq n $ ), and an integer $ x $ ( $ 1 \leq x \leq a_i $ ). Let $ i $ be the source index and $ j $ be the sink index.
2. Decrease the $ i $ -th element by $ x $ , and increase the $ j $ -th element by $ x $ . The resulting values at $ i $ -th and $ j $ -th index are $ a_i-x $ and $ a_j+x $ respectively.
3. The cost of this operation is $ x \cdot |j-i|  $ .
4. Now the $ i $ -th index can no longer be the sink and the $ j $ -th index can no longer be the source.

 The total cost of a transformation is the sum of all the costs in step $ 3 $ .For example, array $ [0, 2, 3, 3] $ can be transformed into a beautiful array $ [2, 2, 2, 2] $ with total cost $ 1 \cdot |1-3| + 1 \cdot |1-4| = 5 $ .

An array is called balanced, if it can be transformed into a beautiful array, and the cost of such transformation is uniquely defined. In other words, the minimum cost of transformation into a beautiful array equals the maximum cost.

You are given an array $ a_1, a_2, \ldots, a_n $ of length $ n $ , consisting of non-negative integers. Your task is to find the number of balanced arrays which are permutations of the given array. Two arrays are considered different, if elements at some position differ. Since the answer can be large, output it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, $ [1, 2, 3] $ is a valid permutation as we can consider the index with value $ 3 $ as the source and index with value $ 1 $ as the sink. Thus, after conversion we get a beautiful array $ [2, 2, 2] $ , and the total cost would be $ 2 $ . We can show that this is the only transformation of this array that leads to a beautiful array. Similarly, we can check for other permutations too.

In the second example, $ [0, 0, 4, 4] $ and $ [4, 4, 0, 0] $ are balanced permutations.

In the third example, all permutations are balanced.

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
6```

## 样例 #2

### 输入

```
4
0 4 0 4```

### 输出

```
2```

## 样例 #3

### 输入

```
5
0 11 12 13 14```

### 输出

```
120```

# AI分析结果


### 💡 Kay的C++算法解析：Cost Equilibrium 深入学习指南 💡

#### 题目解读与核心算法识别
✨ **本题主要考察**：组合数学（计数问题）  
🗣️ **初步分析**：  
> 解决本题的关键在于运用组合数学思想。就像在像素游戏中分类道具一样，我们将数组元素分为三类：小于平均值的"汇点"（需增加）、等于平均值的"自由点"（不变）、大于平均值的"源点"（需减少）。  
> - 当源点或汇点≤1时，所有排列均合法，答案为多重集排列数  
> - 否则，需满足所有源点在汇点同侧（全左/全右），避免代价不唯一  
> - 可视化设计：8位像素风格展示分组排列过程，源点（红）、汇点（蓝）、自由点（绿）。动画高亮分组边界变化，伴随"滴"声标记关键操作。

---

#### 精选优质题解参考
**题解一（作者：Tx_Lcy）**  
* **点评**：思路简洁清晰，巧妙使用`map`统计数字频率，代码模块化（三组分类→分情况计算→组合公式）。亮点在于用`qpow`高效计算逆元，边界处理严谨（特判cnt0/cnt2≤1），实践性强可直接用于竞赛。

**题解二（作者：DaiRuiChen007）**  
* **点评**：逻辑推导透彻，状态定义明确（S/T/F组）。代码结构工整，预处理阶乘逆元提升效率。亮点在于严格证明排列条件（源点同侧），用`map`动态统计频率，可读性强便于调试学习。

---

#### 核心难点辨析与解题策略
1. **难点：理解平衡条件本质**  
   * **分析**：需推导出"代价唯一"⇔源点/汇点无交叉排列。通过反证法：若存在S-T交叉，可构造不同操作序列使代价不等。
   * 💡 **学习笔记**：代价唯一性取决于源汇点的位置关系

2. **难点：分类讨论的实现**  
   * **分析**：优质题解均先计算平均数整除性，再分cnt0/cnt2≤1与>1两种情况。关键变量`cnt1`（自由点数量）决定组合数计算方式。
   * 💡 **学习笔记**：分类讨论是计数问题的核心技巧

3. **难点：组合公式的优化计算**  
   * **分析**：预处理阶乘和逆元（O(n)），避免重复计算。多重集排列数公式：$n!/(\prod c_i!)$，用模逆元实现除模运算。
   * 💡 **学习笔记**：预处理阶乘逆元是组合计数的常见优化

✨ **解题技巧总结**  
- **问题分解**：将复杂条件拆解为三组分类+位置约束  
- **边界优先**：优先处理特殊情形（单源/汇点）简化逻辑  
- **模块化计算**：分离阶乘预处理、组合数计算、频率统计等模块

---

#### C++核心代码实现赏析
**通用核心C++实现参考**  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e5+5, MOD=1e9+7;

ll qpow(ll a,ll b){ // 快速幂求逆元
    ll res=1;
    for(;b;b>>=1,a=a*a%MOD) if(b&1) res=res*a%MOD;
    return res;
}

int main(){
    int n; cin>>n;
    vector<ll> fac(MAXN,1), inv(MAXN,1);
    for(int i=1;i<MAXN;i++) fac[i]=fac[i-1]*i%MOD; // 阶乘预处理
    inv[MAXN-1]=qpow(fac[MAXN-1],MOD-2);
    for(int i=MAXN-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%MOD; // 逆元预处理

    ll sum=0;
    vector<ll> a(n);
    map<ll,int> freq;
    for(int i=0;i<n;i++){
        cin>>a[i]; sum+=a[i];
        freq[a[i]]++;
    }
    if(sum%n) { cout<<0; return 0; } // 非整数平均数

    ll avg=sum/n, cnt0=0, cnt1=0, cnt2=0;
    map<ll,int> freq0, freq2;
    for(auto x:a){
        if(x<avg) cnt0++, freq0[x]++;
        else if(x>avg) cnt2++, freq2[x]++;
        else cnt1++;
    }

    if(cnt0<=1 || cnt2<=1){ // 特殊情况：多重集排列
        ll ans=fac[n];
        for(auto [x,cnt]:freq) ans=ans*inv[cnt]%MOD;
        cout<<ans; return 0;
    }

    // 一般情况：C(n,cnt1)*∏(cnt0!cnt2!)/∏freq! *2
    ll comb=fac[n]*inv[cnt1]%MOD*inv[n-cnt1]%MOD; // C(n,cnt1)
    ll ans=2*comb*fac[cnt0]%MOD*fac[cnt2]%MOD;
    for(auto [x,c]:freq0) ans=ans*inv[c]%MOD; // 汇点内部排列
    for(auto [x,c]:freq2) ans=ans*inv[c]%MOD; // 源点内部排列
    cout<<ans%MOD;
}
```

**题解二（DaiRuiChen007）片段赏析**  
```cpp
// 分组统计
for(int i=1;i<=n;++i){
    if(a[i]>avr) ++S, ++freq2[a[i]]; // 源点
    else if(a[i]<avr) ++T, ++freq0[a[i]]; // 汇点
}
// 特殊情况处理
if(S<=1 || T<=1){
    ll ans=fac[n];
    for(auto p:cnt) ans=ans*inv[p.second]%MOD; // 多重集排列
    printf("%lld\n",ans); return;
}
// 一般情况计算
ll partS=fac[S], partT=fac[T];
for(auto [x,cnt]:freq2) partS=partS*inv[cnt]%MOD; // 源点排列
for(auto [x,cnt]:freq0) partT=partT*inv[cnt]%MOD; // 汇点排列
ll ans=2*partS*partT%MOD*binom(n,S+T)%MOD; // 乘组合数
```

---

#### 算法可视化：像素动画演示
**设计思路**  
> 采用复古红白机像素风格，用颜色区分元素类型：源点(🔴)、汇点(🔵)、自由点(🟢)。动画演示排列过程，强化"同侧排列"核心思想。

**实现方案**  
1. **初始化**：像素网格显示初始数组，底部控制面板（开始/步进/重置）
2. **分组阶段**：
   - 元素按值自动分组，伴随分类音效（源点：高音"叮"，汇点：低音"咚"）
   - 自由点淡出至顶部状态栏
3. **排列阶段**：
   - 源点向左聚集（🔴→），汇点向右聚集（←🔵），伴随滑动动画
   - 关键帧：当源点全部左移后，播放胜利音效并高亮分割线
4. **交互功能**：
   - 拖拽元素体验非法排列（交叉时触发警告音）
   - "对比模式"：并排展示合法/非法排列的代价差异
5. **游戏化设计**：
   - 完成合法排列解锁"平衡勋章"（像素奖杯）
   - 操作连击时显示Combo特效

---

#### 拓展练习与相似问题
1. **洛谷 P1494** - 小Z的袜子  
   → 同类技巧：组合计数+频率统计
2. **洛谷 P3197** - 越狱  
   → 相似思想：补集转换+分组计算
3. **洛谷 P3223** - 排队  
   → 进阶应用：多重集排列+插空法

---

> 本次解析由Kay提供，希望帮助你掌握组合计数的核心思想。记住：将复杂问题分解为独立条件是解题关键！下次见~ 🚀

---
处理用时：133.39秒