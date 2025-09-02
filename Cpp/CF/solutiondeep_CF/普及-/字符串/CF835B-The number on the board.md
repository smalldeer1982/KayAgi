# 题目信息

# The number on the board

## 题目描述

Some natural number was written on the board. Its sum of digits was not less than $ k $ . But you were distracted a bit, and someone changed this number to $ n $ , replacing some digits with others. It's known that the length of the number didn't change.

You have to find the minimum number of digits in which these two numbers can differ.

## 说明/提示

In the first example, the initial number could be $ 12 $ .

In the second example the sum of the digits of $ n $ is not less than $ k $ . The initial number could be equal to $ n $ .

## 样例 #1

### 输入

```
3
11
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
99
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写

#### 题目描述

黑板上写有一个自然数，其各位数字之和不小于 $k$。但你稍不留神，有人将这个数改为了 $n$，替换了其中的一些数字。已知数字的长度没有改变。

你需要找出这两个数在最少多少个数字上不同。

#### 说明/提示

在第一个样例中，初始数字可能是 $12$。

在第二个样例中，$n$ 的各位数字之和不小于 $k$。初始数字可能与 $n$ 相同。

#### 样例 #1

##### 输入

```
3
11
```

##### 输出

```
1
```

#### 样例 #2

##### 输入

```
3
99
```

##### 输出

```
0
```

### 题解分析与结论

#### 综合分析

本题的核心思路是贪心算法。所有题解都采用了类似的策略：将数字的各位从小到大排序，然后依次将最小的数字改为9，直到数字之和满足条件。这种贪心策略确保了每次修改都能最大化地增加数字之和，从而最小化修改次数。

#### 最优关键思路

1. **贪心策略**：每次选择当前最小的数字改为9，以确保每次修改都能最大化地增加数字之和。
2. **排序优化**：将数字的各位从小到大排序，便于贪心策略的实施。
3. **特判处理**：如果初始数字之和已经满足条件，直接输出0，无需修改。

#### 推荐题解

1. **作者：wyk0247 (4星)**
   - **关键亮点**：代码结构清晰，逻辑简洁，注释详细，易于理解。
   - **核心代码**：
     ```cpp
     sort(a, a+len);
     if(he>=k)
         printf("0");
     else {
         for(int i=0;i<len;i++) {
             he+=9-a[i];
             ans=i+1;
             if(he>=k) break;
         }
         printf("%d",ans);
     }
     ```

2. **作者：LegendaryGrandmaster (4星)**
   - **关键亮点**：代码简洁，逻辑清晰，直接使用字符串排序，减少了数组转换的步骤。
   - **核心代码**：
     ```cpp
     sort(st.begin(),st.end());
     int c=0;
     for(int i=0;i<st.size();i++) c+=st[i]-48;
     if(c>=k) cout<<"0";
     else {
         c=abs(c-k);
         int ans=0;
         for(int i=0;i<st.size();i++) {
             c-=9-(st[i]-48);
             ans++;
             if(c<=0) break;
         }
         cout<<ans;
     }
     ```

3. **作者：kbzcz (4星)**
   - **关键亮点**：代码简洁，直接使用数组存储数字，排序后贪心修改，逻辑清晰。
   - **核心代码**：
     ```cpp
     sort(a+1,a+1+n);
     for(int i=1;i<=n;i++) {
         sum=sum-a[i]+9;
         a[i]=9;
         if(sum>=k) {
             printf("%d",i);
             return 0;
         }
     }
     ```

### 扩展思路与推荐题目

#### 扩展思路

本题的贪心策略可以应用于类似的问题，如“最小修改次数使数字满足某种条件”或“最大化某种收益的最小操作次数”。这类问题通常可以通过排序和贪心策略来解决。

#### 推荐题目

1. **P1090 [NOIP2004 提高组] 合并果子** - 贪心策略的应用。
2. **P1223 排队接水** - 贪心策略的应用。
3. **P1803 凌乱的yyy / 线段覆盖** - 贪心策略的应用。

### 个人心得摘录

- **wyk0247**：通过排序和贪心策略，确保了每次修改都能最大化地增加数字之和，从而最小化修改次数。
- **LegendaryGrandmaster**：直接使用字符串排序，减少了数组转换的步骤，代码更加简洁。
- **kbzcz**：通过排序和贪心修改，逻辑清晰，代码简洁，易于理解。

这些心得总结表明，贪心策略在解决类似问题时具有高效性和简洁性，值得在类似问题中推广应用。

---
处理用时：29.28秒