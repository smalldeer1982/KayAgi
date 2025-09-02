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

### 题目内容重写（中文）

Nadeko的生日快到了！她在为派对装饰房间时，在墙上显眼的位置挂了一串由石竹形纸片组成的长花环。Koyomi哥哥一定会喜欢的！

但Nadeko对这花环还不满意，决定再次打磨它。花环有$n$个纸片，从左到右编号为$1$到$n$，第$i$个纸片的颜色为$s_{i}$，用小写英文字母表示。Nadeko将最多重新涂色$m$个纸片，给它们任意的新颜色（仍然用小写英文字母表示）。完成这项工作后，她会找出所有仅包含颜色$c$的花环子段——Koyomi哥哥最喜欢的颜色，并取其中最长的子段的长度作为花环的“Koyomity”。

例如，假设花环表示为“kooomo”，Koyomi哥哥最喜欢的颜色是“o”。在所有仅包含“o”的子段中，“ooo”是最长的，长度为$3$。因此，这个花环的Koyomity为$3$。

但问题来了，Nadeko不确定Koyomi哥哥最喜欢的颜色，并且对工作量也有不同的想法。她有$q$个计划，每个计划可以表示为一个整数$m_{i}$和一个小写字母$c_{i}$，含义如上所述。你需要找出根据每个计划重新涂色后，花环的最大Koyomity。

### 说明/提示

在第一个样例中，有三个计划：

- 在第一个计划中，最多可以重新涂色$1$个纸片。将“y”涂成“o”后，花环变为“kooomi”，其Koyomity为$3$，这是可以达到的最佳值；
- 在第二个计划中，最多可以重新涂色$4$个纸片，花环变为“oooooo”，其Koyomity为$6$；
- 在第三个计划中，最多可以重新涂色$4$个纸片，花环变为“mmmmmi”或“kmmmmm”，其Koyomity为$5$。

### 样例 #1

#### 输入

```
6
koyomi
3
1 o
4 o
4 m
```

#### 输出

```
3
6
5
```

### 样例 #2

#### 输入

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

#### 输出

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

### 样例 #3

#### 输入

```
10
aaaaaaaaaa
2
10 b
10 z
```

#### 输出

```
10
10
```

### 题解分析与结论

#### 题解1：Luo_gu_ykc（4星）
- **关键亮点**：使用双指针法，通过维护一个滑动窗口来找到最长的符合条件的子串。代码简洁，思路清晰。
- **核心思想**：通过双指针维护一个窗口，窗口内非目标字符的数量不超过$m$，更新最大长度。
- **代码片段**：
```cpp
for(int i = 0, j = i; i < n; i++){ // 双指针
    for(; j < n && sum < m; j++){ 
        if(s[j] != c){ // 判断
            sum++;
        }
    }
    maxi = max(maxi, j - i); // 特判
    for(; j < n && s[j] == c; j++){//枚举子串长度
        if(j - i + 1 > maxi){
            maxi = j - i + 1; 
        }
    }
    if(s[i] != c){ // 移动左指针时要特判
        sum--; 
    }
}
```

#### 题解2：Galex（4星）
- **关键亮点**：通过预处理前缀和，优化了双指针法的效率，减少了重复计算。时间复杂度为$O(n^2 \times 26)$，适合大规模数据。
- **核心思想**：预处理每个字符的前缀和，快速计算任意子串中非目标字符的数量。
- **代码片段**：
```cpp
for(int i = 1; i <= n; i++){
    for(int j = 0; j < 26; j++)
        s[i][j] = s[i - 1][j];
    s[i][readc() - 'a']++;
}
```

#### 题解3：Ninelife_Cat（4星）
- **关键亮点**：结合前缀和与双指针，进一步优化了查询效率，时间复杂度为$O(nq)$，适合大规模查询。
- **核心思想**：通过前缀和快速计算子串中非目标字符的数量，使用双指针维护窗口。
- **代码片段**：
```cpp
while(r <= n){
    while(sum[r][ch-'a']-sum[l-1][ch-'a']+x < r-l+1) ++l;
    ans = max(ans, r-l+1); ++r;
}
```

### 最优关键思路与技巧
1. **双指针法**：通过维护一个滑动窗口，窗口内非目标字符的数量不超过$m$，更新最大长度。
2. **前缀和优化**：预处理每个字符的前缀和，快速计算任意子串中非目标字符的数量，减少重复计算。
3. **预处理与记忆化**：对于大规模查询，预处理所有可能的答案，避免重复计算。

### 可拓展之处
- **类似题目**：可以扩展到其他需要计算子串最大长度的问题，如最长连续相同字符子串、最长不重复字符子串等。
- **算法套路**：双指针法、前缀和、预处理与记忆化是解决类似问题的常用套路。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3376 【模板】网络最大流](https://www.luogu.com.cn/problem/P3376)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

### 个人心得总结
- **调试经历**：在处理大规模数据时，预处理和记忆化是避免超时的关键。
- **踩坑教训**：双指针法的边界条件需要特别注意，尤其是窗口的移动和更新。
- **顿悟感想**：前缀和的使用可以大大减少重复计算，提高算法效率。

---
处理用时：50.37秒