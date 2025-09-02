# 题目信息

# 388535 (Easy Version)

## 题目描述

This is the easy version of the problem. The difference in the constraints between both versions is colored below in red. You can make hacks only if all versions of the problem are solved.

Marin and Gojou are playing hide-and-seek with an array.

Gojou initially performs the following steps:

- First, Gojou chooses $ 2 $ integers $ l $ and $ r $ such that $ l \leq r $ .
- Then, Gojou makes an array $ a $ of length $ r-l+1 $ which is a permutation of the array $ [l,l+1,\ldots,r] $ .
- Finally, Gojou chooses a secret integer $ x $ and sets $ a_i $ to $ a_i \oplus x $ for all $ i $ (where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)).

Marin is then given the values of $ l,r $ and the final array $ a $ . She needs to find the secret integer $ x $ to win. Can you help her?

Note that there may be multiple possible $ x $ that Gojou could have chosen. Marin can find any possible $ x $ that could have resulted in the final value of $ a $ .

## 说明/提示

In the first test case, the original array is $ [3, 2, 1, 0] $ .

In the second test case, the original array is $ [0, 3, 2, 1] $ .

In the third test case, the original array is $ [2, 1, 0] $ .

## 样例 #1

### 输入

```
3
0 3
3 2 1 0
0 3
4 7 6 5
0 2
1 2 3```

### 输出

```
0
4
3```

# AI分析结果

### 题目中文重写
这是该问题的简单版本。两个版本之间约束条件的差异在下面用红色标记。只有当所有版本的问题都被解决时，你才能进行 Hack 操作。

Marin 和 Gojou 正在用一个数组玩捉迷藏游戏。

Gojou 最初会执行以下步骤：
- 首先，Gojou 选择两个整数 $l$ 和 $r$，使得 $l \leq r$。
- 然后，Gojou 生成一个长度为 $r - l + 1$ 的数组 $a$，该数组是 $[l, l + 1, \ldots, r]$ 的一个排列。
- 最后，Gojou 选择一个秘密整数 $x$，并对所有的 $i$ 将 $a_i$ 设为 $a_i \oplus x$（其中 $\oplus$ 表示[按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)）。

然后 Marin 会得到 $l$、$r$ 和最终的数组 $a$。她需要找到这个秘密整数 $x$ 才能获胜。你能帮助她吗？

请注意，Gojou 可能选择的 $x$ 可能有多个。Marin 可以找到任何一个可能导致数组 $a$ 最终值的 $x$。

### 算法分类
位运算

### 综合分析与结论
这些题解主要围绕位运算来解决问题。不同题解的思路大多是按位考虑，通过统计二进制位上 1 的个数来确定秘密整数 $x$。部分题解还利用了异或的性质和字典树（trie）来辅助判断。
- **思路对比**：大部分题解从按位统计 1 的个数入手，如通过比较原排列和异或后数组对应位上 1 的个数差异来确定 $x$ 的每一位；部分题解利用 0 异或的特性，枚举可能的 $x$ 并结合字典树判断是否能还原成排列。
- **算法要点**：按位统计 1 的个数是核心操作，部分题解使用字典树来高效处理异或最大值和最小值的查询。
- **解决难点**：关键在于理解异或运算对二进制位的影响，以及如何通过统计和比较来确定 $x$ 的值。

### 所选题解
- **sprads（5星）**
  - **关键亮点**：提供了两种不同的思路，第一种按位统计 1 的个数确定 $x$，代码简洁易懂；第二种利用 0 异或的特性和字典树判断，思路巧妙。
  - **核心代码**：
```cpp
// 第一种做法
for(int j = 0;j <= 17;j++){
    int c1 = 0,c2 = 0;
    for(int i = L;i <= R;i++){
        if(i & (1 << j))c1++;
        if(a[i] & (1 << j))c2++;
    }
    if(c1 != c2)
        res += 1 << j;
}

// 第二种做法
void insert(int v){
    int p = 0;
    for(int i = 17;i >= 0;i--){
        int x = (v >> i) & 1;
        if(!ch[p][x])
            ch[p][x] = ++cnt;
        p = ch[p][x];
    }
}
int query(int v){
    int p = 0,res = 0;
    for(int i = 17;i >= 0;i--){
        int x = (v >> i) & 1;
        if(ch[p][x ^ 1]){
            res += 1 << i;
            p = ch[p][x ^ 1];
        }
        else p = ch[p][x];
    }
    return res;
}
```
- **JS_TZ_ZHR（4星）**
  - **关键亮点**：利用 $a$ 中一定存在一个数 $a_i$ 使得 $a_i$ 异或 $x$ 等于 $l$ 的性质，结合字典树判断是否能还原成排列，思路清晰。
  - **核心代码**：
```cpp
void insert(int sum){
    int now=0;
    for(int i=17;i>=0;i--){
        bool tmp=(1<<i)&sum;
        if(!trie[now][tmp])trie[now][tmp]=++cnt;
        now=trie[now][tmp];
    }
}
int Max(int sum){
    int now=0,res=0;
    for(int i=17;i>=0;i--){
        bool tmp=(1<<i)&sum;
        if(!trie[now][tmp^1])now=trie[now][tmp];
        else now=trie[now][tmp^1],res+=(1<<i);
    }
    return res;
}
int Min(int sum){
    int now=0,res=0;
    for(int i=17;i>=0;i--){
        bool tmp=(1<<i)&sum;
        if(!trie[now][tmp])now=trie[now][tmp^1],res+=(1<<i);
        else now=trie[now][tmp];
    }
    return res;
}
```
- **封禁用户（4星）**
  - **关键亮点**：按位统计 1 的个数，通过比较差异确定 $x$ 的每一位，代码简洁。
  - **核心代码**：
```cpp
for(int i=l,x,y;i<=r;i++){
    cin>>x,y=i;
    for(int j=1;j<=20;j++){
        s[j][x&1]++;
        s[j][y&1]--;
        x>>=1,y>>=1;
    }
}
int ans=0;
for(int i=20;i>=1;i--){
    ans=ans<<1|(s[i][1]!=0);
    s[i][1]=0;
}
```

### 最优关键思路或技巧
- 按位考虑异或运算，通过统计二进制位上 1 的个数来确定 $x$ 的每一位。
- 利用 0 异或的特性，枚举可能的 $x$ 并结合字典树判断是否能还原成排列。

### 拓展思路
同类型题或类似算法套路可以参考涉及位运算的题目，例如通过位运算进行状态压缩、按位统计信息等。可以关注一些关于异或性质应用的题目，如异或和的计算、异或方程的求解等。

### 推荐洛谷题目
- P1886 滑动窗口 /【模板】单调队列
- P1908 逆序对
- P3808 【模板】AC 自动机（简单版）

### 个人心得
- **SnowTrace**：赛场上被该题卡住，通过思考发现可以按位考虑异或运算，利用桶排序统计二进制位上 1 的个数来解决问题。总结是遇到异或相关问题可以从二进制位的角度去分析。 

---
处理用时：44.41秒