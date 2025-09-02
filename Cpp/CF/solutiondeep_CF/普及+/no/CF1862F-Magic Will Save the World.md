# 题目信息

# Magic Will Save the World

## 题目描述

A portal of dark forces has opened at the border of worlds, and now the whole world is under a terrible threat. To close the portal and save the world, you need to defeat $ n $ monsters that emerge from the portal one after another.

Only the sorceress Vika can handle this. She possesses two magical powers — water magic and fire magic. In one second, Vika can generate $ w $ units of water mana and $ f $ units of fire mana. She will need mana to cast spells. Initially Vika have $ 0 $ units of water mana and $ 0 $ units of fire mana.

Each of the $ n $ monsters that emerge from the portal has its own strength, expressed as a positive integer. To defeat the $ i $ -th monster with strength $ s_i $ , Vika needs to cast a water spell or a fire spell of at least the same strength. In other words, Vika can spend at least $ s_i $ units of water mana on a water spell, or at least $ s_i $ units of fire mana on a fire spell.

Vika can create and cast spells instantly. Vika can cast an unlimited number of spells every second as long she has enough mana for that.

The sorceress wants to save the world as quickly as possible, so tell her how much time she will need.

## 说明/提示

In the first sample, after the first second, Vika can spend $ 2 $ units of fire mana to kill the first monster. Then she has $ 2 $ units of water mana and $ 1 $ unit of fire mana. After the third second, she will have $ 6 $ units of water mana and $ 7 $ units of fire mana at her disposal. This will be enough to immediately kill the second and third monsters.

## 样例 #1

### 输入

```
4
2 3
3
2 6 7
37 58
1
93
190 90
2
23 97
13 4
4
10 10 2 45```

### 输出

```
3
2
1
5```

# AI分析结果

### 中文题目重写

**魔法将拯救世界**

**题目描述**

在世界的边界，黑暗力量的传送门已经打开，整个世界正面临可怕的威胁。为了关闭传送门并拯救世界，你需要击败从传送门中依次出现的 $n$ 只怪物。

只有女巫 Vika 能够应对这一挑战。她拥有两种魔法力量——水魔法和火魔法。每秒，Vika 可以生成 $w$ 单位的水魔力和 $f$ 单位的火魔力。她需要魔力来施放法术。初始时，Vika 拥有 $0$ 单位的水魔力和 $0$ 单位的火魔力。

每只从传送门中出现的怪物都有自己的力量，用一个正整数表示。为了击败第 $i$ 只怪物，Vika 需要施放一个至少与其力量相等的水法术或火法术。换句话说，Vika 可以花费至少 $s_i$ 单位的水魔力施放水法术，或者花费至少 $s_i$ 单位的火魔力施放火法术。

Vika 可以瞬间创建和施放法术。只要她有足够的魔力，每秒可以施放无限数量的法术。

女巫希望尽快拯救世界，因此请告诉她需要多少时间。

**说明/提示**

在第一个样例中，第一秒后，Vika 可以花费 $2$ 单位的火魔力击败第一只怪物。然后她拥有 $2$ 单位的水魔力和 $1$ 单位的火魔力。第三秒后，她将拥有 $6$ 单位的水魔力和 $7$ 单位的火魔力。这将足以立即击败第二和第三只怪物。

**样例 #1**

**输入**

```
4
2 3
3
2 6 7
37 58
1
93
190 90
2
23 97
13 4
4
10 10 2 45
```

**输出**

```
3
2
1
5
```

### 算法分类
动态规划

### 题解分析与结论

该题的核心在于如何分配水魔力和火魔力来击败所有怪物，并且最小化所需的时间。大多数题解都采用了动态规划的思路，通过枚举所有可能的水魔力和火魔力的分配方案，找到最小的时间。

#### 题解对比与总结
1. **ax_by_c** 的题解使用了经典的01背包动态规划，通过枚举所有可能的水魔力分配方案，计算所需时间。该题解思路清晰，代码简洁，但未进行优化，时间复杂度较高。
2. **WrongAnswer_90** 的题解使用了 `bitset` 优化动态规划，大大减少了时间和空间复杂度，代码简洁且高效。
3. **信息向阳花木** 的题解采用了二分法和背包动态规划的结合，通过二分时间来优化计算，思路新颖，但代码复杂度较高。

### 精选题解

#### 1. WrongAnswer_90 (★★★★★)
**关键亮点**：使用 `bitset` 优化动态规划，大大减少了时间和空间复杂度，代码简洁且高效。
**核心代码**：
```cpp
bitset<1000001> f;f[0]=1;
while(n--)read(x),f|=(f<<x),sum+=x;
for(int i=0;i<=1000000;++i)if(f[i])minn=min(minn,max((i-1)/A+1,(sum-i-1)/B+1));
```
**实现思想**：通过 `bitset` 来存储所有可能的水魔力分配方案，然后枚举所有可能的分配方案，计算最小时间。

#### 2. ax_by_c (★★★★)
**关键亮点**：经典的01背包动态规划，思路清晰，代码简洁。
**核心代码**：
```cpp
f[0]=1;
for(int i=1;i<=n;i++)
    for(int j=m;j>=a[i];j--)
        f[j]|=f[j-a[i]];
int ans=min(calc(0,m),calc(m,0));
```
**实现思想**：通过01背包动态规划枚举所有可能的水魔力分配方案，计算最小时间。

#### 3. 信息向阳花木 (★★★★)
**关键亮点**：二分法与背包动态规划的结合，通过二分时间来优化计算，思路新颖。
**核心代码**：
```cpp
bool check(int x)
{
    memset(f, 0, sizeof f);
    f[0] = 1;
    for (int i = 1; i <= n; i ++ )
        for (int j = (int)min(1ll * sum, 1ll * a * x); j >= s[i]; j -- )
            f[j] |= f[j - s[i]];
    for (int i = 0; i <= sum; i ++ )
        if(f[i] && sum - i <= b * x) return 1;
    return 0;
}
```
**实现思想**：通过二分法枚举时间，然后使用背包动态规划判断是否可以在该时间内击败所有怪物。

### 最优关键思路
使用 `bitset` 优化动态规划，通过枚举所有可能的水魔力和火魔力的分配方案，找到最小的时间。这种方法不仅减少了时间和空间复杂度，还保持了代码的简洁性。

### 拓展思路
类似的问题可以通过动态规划和 `bitset` 优化来解决，特别是在需要枚举所有可能的分配方案时，`bitset` 可以显著提高效率。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

### 个人心得摘录
- **WrongAnswer_90**：使用 `bitset` 优化动态规划，大大减少了时间和空间复杂度，代码简洁且高效。
- **ax_by_c**：经典的01背包动态规划，思路清晰，代码简洁。
- **信息向阳花木**：二分法与背包动态规划的结合，通过二分时间来优化计算，思路新颖。

---
处理用时：49.63秒