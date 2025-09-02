# 题目信息

# Alice, Bob, Two Teams

## 题目描述

Alice and Bob are playing a game. The game involves splitting up game pieces into two teams. There are $ n $ pieces, and the $ i $ -th piece has a strength $ p_{i} $ .

The way to split up game pieces is split into several steps:

1. First, Alice will split the pieces into two different groups $ A $ and $ B $ . This can be seen as writing the assignment of teams of a piece in an $ n $ character string, where each character is $ A $ or $ B $ .
2. Bob will then choose an arbitrary prefix or suffix of the string, and flip each character in that suffix (i.e. change $ A $ to $ B $ and $ B $ to $ A $ ). He can do this step at most once.
3. Alice will get all the pieces marked $ A $ and Bob will get all the pieces marked $ B $ .

The strength of a player is then the sum of strengths of the pieces in the group.

Given Alice's initial split into two teams, help Bob determine an optimal strategy. Return the maximum strength he can achieve.

## 说明/提示

In the first sample Bob should flip the suffix of length one.

In the second sample Bob should flip the prefix or the suffix (here it is the same) of length $ 5 $ .

In the third sample Bob should do nothing.

## 样例 #1

### 输入

```
5
1 2 3 4 5
ABABA
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
AAAAA
```

### 输出

```
15
```

## 样例 #3

### 输入

```
1
1
B
```

### 输出

```
1
```

# AI分析结果



# 题目内容中文翻译

## 题目描述

Alice和Bob正在玩一个游戏。游戏涉及将游戏棋子分成两个队伍。共有$n$个棋子，第$i$个棋子的强度为$p_i$。

分组的步骤分为几个阶段：
1. Alice首先将棋子分为两个不同的组$A$和$B$。这可以看作是用一个$n$字符的字符串表示每个棋子的队伍分配，每个字符是$A$或$B$。
2. Bob将选择该字符串的任意前缀或后缀，并将该前缀/后缀中的每个字符翻转（即$A$变为$B$，$B$变为$A$）。此步骤最多执行一次。
3. Alice获得所有标记为$A$的棋子，Bob获得所有标记为$B$的棋子。

玩家的强度是其组中棋子强度之和。给定Alice的初始分组，帮助Bob确定最优策略，返回他能达到的最大强度。

## 说明/提示
- 第一个样例中，Bob应翻转长度为1的后缀。
- 第二个样例中，Bob应翻转长度为5的前缀或后缀。
- 第三个样例中，Bob不应操作。

## 样例 #1
### 输入
5
1 2 3 4 5
ABABA
### 输出
11

## 样例 #2
### 输入
5
1 2 3 4 5
AAAAA
### 输出
15

## 样例 #3
### 输入
1
1
B
### 输出
1

**算法分类**: 贪心

---

# 题解分析与结论

各题解均采用**贪心算法**，核心思路为：
1. 计算初始状态下Bob的强度总和。
2. 枚举所有可能的前缀和后缀翻转情况，计算每种情况的强度变化。
3. 维护最大值作为最终结果。

**关键思路**：翻转操作带来的收益变化可以通过线性扫描快速计算。每个位置翻转后的总收益变化等于原收益减去翻转区域的Bob收益并加上翻转区域的Alice收益。

---

# 精选题解

## 题解1（作者：hxhhxh） ★★★★☆
**亮点**：代码简洁，双循环处理前缀和后缀。
```cpp
int n,a[500005],t,ans;
char ch[500005];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    cin>>ch+1;
    for(int i=1;i<=n;i++) if(ch[i]=='B') t+=a[i]; // 初始总和
    // 处理前缀
    for(int i=1,j=t;i<=n;i++){
        if(ch[i]=='A') j+=a[i];
        else j-=a[i];
        ans=max(ans,j);
    }
    // 处理后缀
    for(int i=n,j=t;i>=1;i--){
        if(ch[i]=='A') j+=a[i];
        else j-=a[i];
        ans=max(ans,j);
    }
    cout<<max(t,ans);
}
```

## 题解2（作者：DevOvO） ★★★★☆
**亮点**：利用前缀和与后缀和优化计算。
```cpp
int tot = b1[n]; // 初始总和
// 枚举前缀
for (int i=0; i<=n; ++i) 
    ans = Max(ans, tot - b1[i] + a1[i]);
// 枚举后缀
for (int i=0; i<=n; ++i)
    ans = Max(ans, tot - b2[i] + a2[i]);
```

## 题解3（作者：szh_AK_all） ★★★★
**亮点**：变量命名清晰，逻辑直白。
```cpp
long long ans = tmp;
// 枚举前缀
for(int i=1; i<=n; i++) {
    if(b[i]==1) ans -= a[i];
    else ans += a[i];
    tmp = max(tmp, ans);
}
// 枚举后缀
for(int i=n; i>=1; i--) {
    if(b[i]==1) k -= a[i];
    else k += a[i];
    tmp = max(tmp, k);
}
```

---

# 最优技巧总结
1. **实时更新法**：在遍历前缀/后缀时，动态维护当前翻转后的总强度，避免重复计算。
2. **对称处理**：前缀和后缀的处理逻辑完全对称，可用相同结构代码实现。
3. **贪心决策**：每个位置独立判断翻转带来的收益变化，只需一次线性扫描即可确定最优解。

---

# 拓展与相似题目
- **最大子段和**：P1115（利用类似的前缀和思想）
- **区间翻转优化**：P5638（贪心+前缀和）
- **分组策略问题**：P2671（前缀和与贪心结合）

掌握此类问题的核心在于识别区间操作的收益变化模式，并利用线性扫描高效求解。

---
处理用时：72.15秒