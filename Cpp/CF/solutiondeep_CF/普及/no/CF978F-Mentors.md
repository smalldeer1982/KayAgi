# 题目信息

# Mentors

## 题目描述

In BerSoft $ n $ programmers work, the programmer $ i $ is characterized by a skill $ r_i $ .

A programmer $ a $ can be a mentor of a programmer $ b $ if and only if the skill of the programmer $ a $ is strictly greater than the skill of the programmer $ b $ $ (r_a > r_b) $ and programmers $ a $ and $ b $ are not in a quarrel.

You are given the skills of each programmers and a list of $ k $ pairs of the programmers, which are in a quarrel (pairs are unordered). For each programmer $ i $ , find the number of programmers, for which the programmer $ i $ can be a mentor.

## 说明/提示

In the first example, the first programmer can not be mentor of any other (because only the second programmer has a skill, lower than first programmer skill, but they are in a quarrel). The second programmer can not be mentor of any other programmer, because his skill is minimal among others. The third programmer can be a mentor of the second programmer. The fourth programmer can be a mentor of the first and of the second programmers. He can not be a mentor of the third programmer, because they are in a quarrel.

## 样例 #1

### 输入

```
4 2
10 4 10 15
1 2
4 3
```

### 输出

```
0 0 1 2 
```

## 样例 #2

### 输入

```
10 4
5 4 1 5 4 3 7 1 2 5
4 6
2 1
10 8
3 5
```

### 输出

```
5 4 0 5 3 3 9 0 2 5 
```

# AI分析结果

### 题目内容重写

在BerSoft公司有$n$名程序员，第$i$名程序员的能力值为$r_i$。

程序员$a$可以成为程序员$b$的导师，当且仅当程序员$a$的能力值严格大于程序员$b$的能力值（即$r_a > r_b$），并且程序员$a$和$b$之间没有发生口角。

给定每个程序员的能力值和一个包含$k$对程序员的口角列表（这些对是无序的）。对于每个程序员$i$，找出有多少名程序员可以成为他的导师。

### 算法分类
排序

### 题解分析与结论

1. **SqrtSecond的题解**（评分：4星）
   - **关键亮点**：使用`sort+lower_bound`快速计算每个程序员的能力值排名，然后通过遍历口角列表调整结果。思路清晰，代码简洁。
   - **核心思想**：先计算每个程序员的能力值排名，然后根据口角列表调整结果。
   - **代码片段**：
     ```cpp
     sort(b+1,b+n+1);
     for(int i=1;i<=n;++i)
     {
         int l=lower_bound(b+1,b+n+1,a[i])-b;
         ans[i]=l-1;
     }
     while(m--)
     {
         x=read();y=read();
         if(a[x]<a[y])ans[y]--;
         if(a[y]<a[x])ans[x]--;
     }
     ```

2. **「已注销」的题解**（评分：4星）
   - **关键亮点**：使用下标排序，递推计算每个程序员的能力值排名，并通过口角列表调整结果。代码结构清晰，逻辑严谨。
   - **核心思想**：通过下标排序和递推计算每个程序员的能力值排名，然后根据口角列表调整结果。
   - **代码片段**：
     ```cpp
     sort(s+1,s+n+1,cmp);
     for(int i=2;i<=n;++i){
         if(r[s[i]]>r[s[i-1]])ruo[s[i]]=i-1;
         else ruo[s[i]]=ruo[s[i-1]];
     }
     for(int i=1;i<=n;++i)printf("%d ",ruo[i]-h[i]);
     ```

3. **GoldenFishX的题解**（评分：4星）
   - **关键亮点**：使用结构体存储程序员信息，通过排序和二分查找计算每个程序员的能力值排名，并根据口角列表调整结果。代码实现较为复杂，但思路清晰。
   - **核心思想**：通过排序和二分查找计算每个程序员的能力值排名，然后根据口角列表调整结果。
   - **代码片段**：
     ```cpp
     sort(a + 1, a + n + 1, cmp1);
     for(int i = 2; i <= n; i++){
         l = 1; r = i;
         while(l <= r){
             mid = (l + r) / 2;
             if(a[mid].r < a[i].r) l = mid + 1;
             else r = mid - 1;
         }
         a[i].app += r;
     }
     ```

### 最优关键思路或技巧
1. **排序与二分查找**：通过排序和二分查找快速计算每个程序员的能力值排名，是解决该问题的核心技巧。
2. **口角列表调整**：根据口角列表调整每个程序员的结果，确保不会将发生口角的程序员计算在内。

### 可拓展之处
1. **类似问题**：可以扩展到其他需要根据某种条件筛选元素的问题，如根据某种属性排序后查找符合条件的元素。
2. **优化思路**：可以考虑使用更高效的数据结构（如树状数组）来进一步优化计算过程。

### 推荐题目
1. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)
2. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)
3. [P1068 分数线划定](https://www.luogu.com.cn/problem/P1068)

---
处理用时：25.75秒