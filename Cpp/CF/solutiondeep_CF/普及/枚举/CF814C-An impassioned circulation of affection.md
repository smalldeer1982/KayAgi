# 题目信息

# An impassioned circulation of affection

## 题目描述

Nadeko's birthday is approaching! As she decorated the room for the party, a long garland of Dianthus-shaped paper pieces was placed on a prominent part of the wall. Brother Koyomi will like it!

Still unsatisfied with the garland, Nadeko decided to polish it again. The garland has $ n $ pieces numbered from $ 1 $ to $ n $ from left to right, and the $ i $ -th piece has a colour $ s_{i} $ , denoted by a lowercase English letter. Nadeko will repaint at most $ m $ of the pieces to give each of them an arbitrary new colour (still denoted by a lowercase English letter). After this work, she finds out all subsegments of the garland containing pieces of only colour $ c $ — Brother Koyomi's favourite one, and takes the length of the longest among them to be the Koyomity of the garland.

For instance, let's say the garland is represented by "kooomo", and Brother Koyomi's favourite colour is "o". Among all subsegments containing pieces of "o" only, "ooo" is the longest, with a length of $ 3 $ . Thus the Koyomity of this garland equals $ 3 $ .

But problem arises as Nadeko is unsure about Brother Koyomi's favourite colour, and has swaying ideas on the amount of work to do. She has $ q $ plans on this, each of which can be expressed as a pair of an integer $ m_{i} $ and a lowercase letter $ c_{i} $ , meanings of which are explained above. You are to find out the maximum Koyomity achievable after repainting the garland according to each plan.

## 说明/提示

In the first sample, there are three plans:

- In the first plan, at most $ 1 $ piece can be repainted. Repainting the "y" piece to become "o" results in "kooomi", whose Koyomity of $ 3 $ is the best achievable;
- In the second plan, at most $ 4 $ pieces can be repainted, and "oooooo" results in a Koyomity of $ 6 $ ;
- In the third plan, at most $ 4 $ pieces can be repainted, and "mmmmmi" and "kmmmmm" both result in a Koyomity of $ 5 $ .

## 样例 #1

### 输入

```
6
koyomi
3
1 o
4 o
4 m
```

### 输出

```
3
6
5
```

## 样例 #2

### 输入

```
15
yamatonadeshiko
10
1 a
2 a
3 a
4 a
5 a
1 b
2 b
3 b
4 b
5 b
```

### 输出

```
3
4
5
7
8
1
2
3
4
5
```

## 样例 #3

### 输入

```
10
aaaaaaaaaa
2
10 b
10 z
```

### 输出

```
10
10
```

# AI分析结果

### 题目中文重写
# 深情的爱意传递

## 题目描述
 Nadeko的生日快到了！当她为派对装饰房间时，一条由石竹形状纸片组成的长花环被挂在了墙上显眼的位置。哥哥Koyomi会喜欢的！

Nadeko仍然对这个花环不满意，决定再次对它进行修饰。花环从左到右有 $ n $ 个纸片，编号从 $ 1 $ 到 $ n $，第 $ i $ 个纸片的颜色为 $ s_{i} $，用小写英文字母表示。Nadeko最多会重新绘制 $ m $ 个纸片，给它们赋予任意新的颜色（仍然用小写英文字母表示）。完成这项工作后，她会找出花环中仅包含颜色 $ c $（哥哥Koyomi最喜欢的颜色）的所有子段，并取其中最长子段的长度作为花环的“Koyomity”值。

例如，假设花环用 "kooomo" 表示，哥哥Koyomi最喜欢的颜色是 "o"。在所有仅包含 "o" 的子段中，"ooo" 是最长的，长度为 $ 3 $。因此，这个花环的Koyomity值等于 $ 3 $。

但问题来了，Nadeko不确定哥哥Koyomi最喜欢的颜色，并且对要做的工作量也犹豫不决。她有 $ q $ 个计划，每个计划都可以表示为一对整数 $ m_{i} $ 和小写字母 $ c_{i} $，其含义如上所述。你需要找出根据每个计划重新绘制花环后可达到的最大Koyomity值。

## 说明/提示
在第一个样例中，有三个计划：
- 在第一个计划中，最多可以重新绘制 $ 1 $ 个纸片。将 "y" 纸片重新绘制成 "o" 后得到 "kooomi"，其Koyomity值为 $ 3 $，这是可达到的最佳值；
- 在第二个计划中，最多可以重新绘制 $ 4 $ 个纸片，得到 "oooooo"，Koyomity值为 $ 6 $；
- 在第三个计划中，最多可以重新绘制 $ 4 $ 个纸片，"mmmmmi" 和 "kmmmmm" 的Koyomity值都为 $ 5 $。

## 样例 #1
### 输入
```
6
koyomi
3
1 o
4 o
4 m
```
### 输出
```
3
6
5
```

## 样例 #2
### 输入
```
15
yamatonadeshiko
10
1 a
2 a
3 a
4 a
5 a
1 b
2 b
3 b
4 b
5 b
```
### 输出
```
3
4
5
7
8
1
2
3
4
5
```

## 样例 #3
### 输入
```
10
aaaaaaaaaa
2
10 b
10 z
```
### 输出
```
10
10
```

### 综合分析与结论
这些题解主要围绕如何找出在最多修改 $m$ 个字符的情况下，使字符串中连续相同字符 $c$ 的长度最长的问题展开。思路主要分为双指针、前缀和、二分查找、动态规划等方向。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|Luo_gu_ykc|使用双指针，确保子串中不等于字符 $c$ 的字符数量小于等于 $m$，从而求出最长符合条件的子串|双指针遍历字符串，动态调整子串范围|双指针的移动和边界处理|4星|
|叶枫|先枚举子区间，用动态规划计算每个查询的结果，为优化复杂度进行离线处理并打表|枚举子区间，动态规划计算，离线打表|动态规划状态设计和离线处理的实现|3星|
|Galex|预处理所有可能答案，通过枚举区间和字母，用前缀和优化计算修改字符数量的过程|枚举区间和字母，前缀和优化|前缀和数组的构建和使用|3星|
|Ninelife_Cat|结合前缀和与双指针，用前缀和预处理字符数量，双指针枚举子串|前缀和预处理，双指针枚举子串|前缀和的计算和双指针的配合|4星|
|77777_1031|提供双指针、前缀和双指针、动态规划三种方法|三种不同算法思路|不同算法的实现和复杂度分析|3星|
|dxrS|利用答案单调性二分查找，用前缀和维护字符个数，预处理所有答案|二分查找，前缀和维护，答案预处理|二分查找的边界和前缀和的使用|3星|
|Lyccrius|双指针和前缀和双指针两种方法，前者直接维护非 $c$ 字符数量，后者用前缀和优化|双指针遍历，前缀和优化|前缀和数组的构建和双指针的移动|4星|
|lnwhl|双指针枚举子串，前缀和预处理字符数量，记忆化存储答案避免重复计算|双指针枚举，前缀和预处理，记忆化存储|记忆化的实现和前缀和的使用|3星|
|cbyybccbyybc|二分答案，用前缀和维护改动字母个数，在 $check$ 函数中暴力枚举判断|二分答案，前缀和维护，$check$ 函数判断|二分查找的边界和 $check$ 函数的实现|3星|
|fletmer|尝试二分答案，包括裸二分、二分加记忆化和尺取法，最终尺取法通过|二分答案，记忆化，尺取法|不同方法的复杂度分析和实现|3星|

### 所选题解
- **Luo_gu_ykc（4星）**
    - 关键亮点：思路清晰，代码简洁，双指针的使用直接解决问题，易于理解。
    - 核心代码：
```cpp
for(int i = 0, j = i; i < n; i++){ 
    for(; j < n && sum < m; j++){ 
        if(s[j]!= c){ 
            sum++;
        }
    }
    maxi = max(maxi, j - i); 
    for(; j < n && s[j] == c; j++){
        if(j - i + 1 > maxi){
            maxi = j - i + 1; 
        }
    }
    if(s[i]!= c){ 
        sum--; 
    }
}
```
    - 核心实现思想：通过双指针 $i$ 和 $j$ 遍历字符串，$j$ 指针不断右移，当非 $c$ 字符数量达到 $m$ 时停止，更新最大长度，然后继续右移 $j$ 直到遇到非 $c$ 字符，最后移动 $i$ 指针并更新非 $c$ 字符数量。

- **Ninelife_Cat（4星）**
    - 关键亮点：前缀和与双指针结合，降低了计算子串中非 $c$ 字符数量的复杂度。
    - 核心代码：
```cpp
for(ri int i=1;i<=n;++i)
{
    for(ri int j=0;j<26;++j)
        sum[i][j]+=sum[i-1][j];
    ++sum[i][s[i]-'a'];
}
for(ri int i=1;i<=m;++i)
{
    cin>>x>>ch;ri int l=1,r=1,ans=0;
    while(r<=n)
    {
        while(sum[r][ch-'a']-sum[l-1][ch-'a']+x<r-l+1) ++l;
        ans=max(ans,r-l+1);++r;
    }
}
```
    - 核心实现思想：先预处理前缀和数组 $sum$，记录每个位置每个字符的出现次数。然后对于每个查询，使用双指针 $l$ 和 $r$ 枚举子串，通过前缀和快速计算子串中非 $c$ 字符数量，更新最大长度。

- **Lyccrius（4星）**
    - 关键亮点：提供了双指针和前缀和双指针两种方法，对不同复杂度的实现进行了对比。
    - 前缀和双指针核心代码：
```cpp
for (int i = 0; i < n; i++) {
    for (int j = 'a'; j <= 'z'; j++) pre[i][j - 'a'] = pre[i - 1][j - 'a'];
    pre[i][s[i] - 'a']++;
}
while (q--) {
    scanf("%d %c", &m, &c);
    int ans = 0;
    for (int i = 0, j = i; j < n; j++) {
        while ((j - i + 1) - (pre[j][c - 'a'] - pre[i - 1][c - 'a']) > m) i++;
        ans = std::max(ans, j - i + 1);
    }
    printf("%d\n", ans);
}
```
    - 核心实现思想：先预处理前缀和数组 $pre$，记录每个位置每个字符的出现次数。对于每个查询，使用双指针 $i$ 和 $j$ 枚举子串，通过前缀和快速计算子串中非 $c$ 字符数量，当非 $c$ 字符数量超过 $m$ 时移动 $i$ 指针，更新最大长度。

### 最优关键思路或技巧
- **双指针**：通过双指针动态调整子串范围，避免了枚举所有子串的高复杂度。
- **前缀和**：预处理前缀和数组，能够在 $O(1)$ 时间内查询子串中某个字符的数量，优化了计算非 $c$ 字符数量的过程。
- **记忆化**：对于重复的查询，存储已经计算过的答案，避免重复计算，提高效率。

### 可拓展之处
同类型题或类似算法套路：
- 字符串子串相关问题，如最长连续相同字符子串、满足特定条件的子串等。
- 双指针和前缀和结合的算法常用于处理区间统计问题，如区间和、区间字符数量等。

### 推荐洛谷题目
- [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)：双指针和前缀和的应用，求满足条件的最短区间。
- [P2698 [USACO12MAR]Flowerpot S](https://www.luogu.com.cn/problem/P2698)：双指针和二分查找结合，求满足条件的最小区间长度。
- [P3143 [USACO16OPEN]Field Reduction G](https://www.luogu.com.cn/problem/P3143)：双指针和枚举的应用，处理区间问题。

### 个人心得摘录与总结
题解中未明显体现个人调试经历、踩坑教训或顿悟感想等内容。

---
处理用时：56.70秒