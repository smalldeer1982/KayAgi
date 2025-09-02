# 题目信息

# Tear It Apart

## 题目描述

You are given a string $ s $ , consisting of lowercase Latin letters.

In one operation, you can select several (one or more) positions in it such that no two selected positions are adjacent to each other. Then you remove the letters on the selected positions from the string. The resulting parts are concatenated without changing their order.

What is the smallest number of operations required to make all the letters in $ s $ the same?

## 说明/提示

In the first testcase, you can select positions $ 2, 4 $ and $ 6 $ and remove the corresponding letters 'b', 'c' and 'b'.

In the third testcase, the letters in the string are already the same, so you don't have to make any operations.

In the fourth testcase, one of the possible solutions in $ 2 $ operations is the following. You can select positions $ 1, 4, 6 $ first. The string becomes "bce". Then select positions $ 1 $ and $ 3 $ . The string becomes "c". All letters in it are the same, since it's just one letter.

## 样例 #1

### 输入

```
5
abacaba
codeforces
oooooooo
abcdef
mewheniseearulhiiarul```

### 输出

```
1
3
0
2
4```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个由小写拉丁字母组成的字符串 $s$。

在一次操作中，你可以选择字符串中的多个位置（至少一个），且这些位置不能相邻。然后删除这些位置上的字符。删除后，字符串的剩余部分会按原顺序拼接起来。

问：最少需要多少次操作，才能使字符串中的所有字符都相同？

#### 说明/提示

在第一个测试用例中，你可以选择位置 $2, 4$ 和 $6$，并删除对应的字符 'b', 'c' 和 'b'。

在第三个测试用例中，字符串中的字符已经全部相同，因此不需要进行任何操作。

在第四个测试用例中，一个可能的解决方案是进行 $2$ 次操作。首先选择位置 $1, 4, 6$，字符串变为 "bce"。然后选择位置 $1$ 和 $3$，字符串变为 "c"。此时，字符串中的所有字符都相同，因为只剩下一个字符。

#### 样例 #1

##### 输入

```
5
abacaba
codeforces
oooooooo
abcdef
mewheniseearulhiiarul
```

##### 输出

```
1
3
0
2
4
```

### 算法分类

枚举、字符串

### 题解分析与结论

#### 题解对比

1. **spider_oyster** 和 **Lovely_Chtholly** 的题解思路相似，都是枚举每个字符作为最终保留的字符，然后计算删除其他字符所需的最少操作次数。核心思想是将字符串分割成若干段，每段的长度为 $x$，删除次数为 $\log_2x + 1$。代码实现简洁，时间复杂度为 $O(n \times 26)$，适合本题的数据范围。

2. **Night_sea_64** 的题解使用了标记数组来模拟删除过程，虽然思路清晰，但实现较为复杂，且时间复杂度较高，不推荐。

3. **arrow_king** 的题解预处理了每个长度的删除次数，优化了计算过程，代码较为高效，但实现稍显复杂。

4. **zeekliu** 和 **aeiouaoeiu** 的题解思路与 **spider_oyster** 类似，但代码实现较为简洁，适合初学者理解。

5. **M00R** 和 **Wf_yjqd** 的题解通过记录字符出现的位置来计算最大间隔长度，思路清晰，代码实现较为简洁。

6. **Miyamizu_Mitsuha** 和 **yuanruiqi** 的题解思路与 **spider_oyster** 类似，但代码实现较为简洁，适合初学者理解。

#### 最优题解

1. **spider_oyster** (5星)
   - 关键亮点：思路清晰，代码简洁，时间复杂度低。
   - 代码核心思想：枚举每个字符作为最终保留的字符，计算删除其他字符所需的最少操作次数。
   ```cpp
   int ans=1e9;
   for(int c='a';c<='z';c++)
   {
       int res=0,len=0;
       for(int i=0;i<s.size();i++)
           if(s[i]!=c) len++;
           else res=max(res,len),len=0;
       res=max(res,len);
       if(res==0) {ans=0;break;}
       ans=min(ans,(int)log2(res)+1);
   }
   ```

2. **Lovely_Chtholly** (5星)
   - 关键亮点：思路清晰，代码简洁，时间复杂度低。
   - 代码核心思想：与 **spider_oyster** 类似，枚举每个字符作为最终保留的字符，计算删除其他字符所需的最少操作次数。
   ```cpp
   int minn=INF;
   for(char i='a';i<='z';i++)
   {
       int len=0,sum=0;
       for(int j=0;j<s.size();j++)
       {
           if(i==s[j])len=max(len,sum),sum=0;
           else sum++;
       }
       len=max(len,sum);
       if(len)minn=min(minn,(int)(log2(len))+1);
       else
       {
           puts("0");
           goto next;
       }
   }
   ```

3. **arrow_king** (4星)
   - 关键亮点：预处理删除次数，优化计算过程。
   - 代码核心思想：预处理每个长度的删除次数，枚举每个字符作为最终保留的字符，计算删除其他字符所需的最少操作次数。
   ```cpp
   oper[1]=1;
   for(int i=2;i<=200000;i++) oper[i]=oper[i/2]+1;
   t=read();
   while(t--) {
       scanf("%s",s+1);
       n=strlen(s+1);
       ans=1e9;
       for(int now='a';now<='z';now++) {
           last=0,tot=0;
           for(int i=1;i<=n;i++) {
               if(s[i]==now) {
                   tot=max(tot,oper[i-last-1]);
                   last=i;
               }
           }
           tot=max(tot,oper[n-last]);
           ans=min(ans,tot);
       }
       printf("%d\n",ans);
   }
   ```

### 关键思路与技巧

1. **枚举法**：枚举每个字符作为最终保留的字符，计算删除其他字符所需的最少操作次数。
2. **分段处理**：将字符串分割成若干段，每段的长度为 $x$，删除次数为 $\log_2x + 1$。
3. **预处理优化**：预处理每个长度的删除次数，优化计算过程。

### 拓展思路

1. **类似题目**：可以扩展到处理其他类型的字符串操作问题，如删除特定模式的字符、替换字符等。
2. **优化思路**：可以考虑使用更高效的数据结构或算法来优化计算过程，如使用位运算或动态规划。

### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3805 【模板】Manacher算法](https://www.luogu.com.cn/problem/P3805)
3. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)

---
处理用时：40.07秒