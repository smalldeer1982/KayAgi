# 题目信息

# Yarik and Musical Notes

## 题目描述

Yarik is a big fan of many kinds of music. But Yarik loves not only listening to music but also writing it. He likes electronic music most of all, so he has created his own system of music notes, which, in his opinion, is best for it.

Since Yarik also likes informatics, in his system notes are denoted by integers of $ 2^k $ , where $ k \ge 1 $ — a positive integer. But, as you know, you can't use just notes to write music, so Yarik uses combinations of two notes. The combination of two notes $ (a, b) $ , where $ a = 2^k $ and $ b = 2^l $ , he denotes by the integer $ a^b $ .

For example, if $ a = 8 = 2^3 $ , $ b = 4 = 2^2 $ , then the combination $ (a, b) $ is denoted by the integer $ a^b = 8^4 = 4096 $ . Note that different combinations can have the same notation, e.g., the combination $ (64, 2) $ is also denoted by the integer $ 4096 = 64^2 $ .

Yarik has already chosen $ n $ notes that he wants to use in his new melody. However, since their integers can be very large, he has written them down as an array $ a $ of length $ n $ , then the note $ i $ is $ b_i = 2^{a_i} $ . The integers in array $ a $ can be repeated.

The melody will consist of several combinations of two notes. Yarik was wondering how many pairs of notes $ b_i, b_j $ $ (i < j) $ exist such that the combination $ (b_i, b_j) $ is equal to the combination $ (b_j, b_i) $ . In other words, he wants to count the number of pairs $ (i, j) $ $ (i < j) $ such that $ b_i^{b_j} = b_j^{b_i} $ . Help him find the number of such pairs.

## 样例 #1

### 输入

```
5
1
2
4
3 1 3 2
2
1000 1000
3
1 1 1
19
2 4 1 6 2 8 5 4 2 10 5 10 8 7 4 3 2 6 10```

### 输出

```
0
2
1
3
19```

# AI分析结果



# 题目内容

# Yarik 和音乐符号

## 题目描述

Yarik 是多种音乐的狂热爱好者。但他不仅喜欢听音乐，还喜欢创作音乐。他最喜欢电子音乐，因此创建了自己的音符系统，他认为这是最适合电子音乐的。

由于 Yarik 也喜欢信息学，在他的系统中，音符用 $2^k$（其中 $k \ge 1$ 是正整数）的整数表示。但如你所知，单独的音符无法谱写音乐，因此 Yarik 使用两个音符的组合。两个音符 $(a, b)$（其中 $a = 2^k$，$b = 2^l$）的组合用整数 $a^b$ 表示。

例如，当 $a = 8 = 2^3$，$b = 4 = 2^2$ 时，组合 $(a, b)$ 表示为 $a^b = 8^4 = 4096$。注意不同的组合可能具有相同的表示，例如组合 $(64, 2)$ 也表示为 $4096 = 64^2$。

Yarik 已经选择了 $n$ 个音符用于新旋律。由于这些整数可能非常大，他将其记录为数组 $a$（长度为 $n$），其中第 $i$ 个音符为 $b_i = 2^{a_i}$。数组 $a$ 中的整数可能有重复。

旋律将由多个音符组合构成。Yarik 想知道有多少对音符 $b_i, b_j$（$i < j$）满足组合 $(b_i, b_j)$ 等于组合 $(b_j, b_i)$。换句话说，需要计算满足 $b_i^{b_j} = b_j^{b_i}$ 的 $(i, j)$ 对（$i < j$）的数量。

## 样例 #1

### 输入

```
5
1
2
4
3 1 3 2
2
1000 1000
3
1 1 1
19
2 4 1 6 2 8 5 4 2 10 5 10 8 7 4 3 2 6 10
```

### 输出

```
0
2
1
3
19
```

---

**算法分类**：数学

---

### 题解综合分析

本题核心在于找出满足 $2^{a_i \cdot 2^{a_j}} = 2^{a_j \cdot 2^{a_i}}$ 的条件。通过数学推导可得，只有当 $a_i = a_j$ 或 $(a_i,a_j)=(1,2)/(2,1)$ 时等式成立。所有题解均基于此结论，通过统计各数值出现次数计算组合数。

---

### 高分题解推荐

#### 1. 作者：DerrickLo（★★★★☆）
**核心思路**：  
- 通过函数分析发现当且仅当 $a_i=a_j$ 或 $\{1,2\}$ 时满足条件  
- 使用排序后线性扫描统计相同元素的数量  
- 单独统计 1 和 2 的交叉组合  

**代码亮点**：  
```cpp
int cnt1=0,cnt2=0,ans=0,cnt=0;
for(int i=1;i<=n;i++)if(a[i]==1)cnt1++;
for(int i=1;i<=n;i++)if(a[i]==2)cnt2++;
ans += cnt1*cnt2;
// 统计相同元素的组合数
for(int i=1;i<=n+1;i++){
    if(a[i]!=a[i-1]) ans += cnt*(cnt-1)/2, cnt=0;
    cnt++;
}
```

#### 2. 作者：lailai0916（★★★★★）
**核心思路**：  
- 通过图像观察法验证条件成立情形  
- 使用 STL map 统计频率  
- 公式化计算组合数：$C(m_i,2) + m_1 \cdot m_2$  

**代码亮点**：  
```cpp
map<int,ll> m;
for(int t; n--; ) cin>>t, m[t]++;
ll ans = m[1]*m[2];
for(auto x : m) ans += x.second*(x.second-1)/2;
```

---

### 最优技巧总结
1. **数学建模**：将指数等式转化为线性关系 $a_i \cdot 2^{a_j} = a_j \cdot 2^{a_i}$  
2. **特例分析**：通过函数分析发现仅存在两种有效配对模式  
3. **频率统计**：使用哈希表/排序统计相同元素出现次数  
4. **组合计算**：利用组合公式 $C(n,2) = n(n-1)/2$ 计算相同元素对  

---

### 类似题目推荐
1. [CF86D - Powerful array](https://www.luogu.com.cn/problem/CF86D)（频率统计+数学公式）  
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)（哈希表统计配对）  
3. [CF1520D - Same Differences](https://www.luogu.com.cn/problem/CF1520D)（数学变形+频率统计）

---
处理用时：53.80秒