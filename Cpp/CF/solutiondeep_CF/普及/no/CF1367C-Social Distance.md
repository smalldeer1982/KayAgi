# 题目信息

# Social Distance

## 题目描述

Polycarp and his friends want to visit a new restaurant. The restaurant has $ n $ tables arranged along a straight line. People are already sitting at some tables. The tables are numbered from $ 1 $ to $ n $ in the order from left to right. The state of the restaurant is described by a string of length $ n $ which contains characters "1" (the table is occupied) and "0" (the table is empty).

Restaurant rules prohibit people to sit at a distance of $ k $ or less from each other. That is, if a person sits at the table number $ i $ , then all tables with numbers from $ i-k $ to $ i+k $ (except for the $ i $ -th) should be free. In other words, the absolute difference of the numbers of any two occupied tables must be strictly greater than $ k $ .

For example, if $ n=8 $ and $ k=2 $ , then:

- strings "10010001", "10000010", "00000000", "00100000" satisfy the rules of the restaurant;
- strings "10100100", "10011001", "11111111" do not satisfy to the rules of the restaurant, since each of them has a pair of "1" with a distance less than or equal to $ k=2 $ .

In particular, if the state of the restaurant is described by a string without "1" or a string with one "1", then the requirement of the restaurant is satisfied.

You are given a binary string $ s $ that describes the current state of the restaurant. It is guaranteed that the rules of the restaurant are satisfied for the string $ s $ .

Find the maximum number of free tables that you can occupy so as not to violate the rules of the restaurant. Formally, what is the maximum number of "0" that can be replaced by "1" such that the requirement will still be satisfied?

For example, if $ n=6 $ , $ k=1 $ , $ s= $ "100010", then the answer to the problem will be $ 1 $ , since only the table at position $ 3 $ can be occupied such that the rules are still satisfied.

## 说明/提示

The first test case is explained in the statement.

In the second test case, the answer is $ 2 $ , since you can choose the first and the sixth table.

In the third test case, you cannot take any free table without violating the rules of the restaurant.

## 样例 #1

### 输入

```
6
6 1
100010
6 2
000000
5 1
10101
3 1
001
2 2
00
1 1
0```

### 输出

```
1
2
0
1
1
1```

# AI分析结果

【题目内容】
# 社交距离

## 题目描述

Polycarp和他的朋友们想参观一家新餐厅。餐厅有$n$张桌子沿一条直线排列。有些桌子已经有人坐了。桌子从左到右编号为$1$到$n$。餐厅的状态由一个长度为$n$的字符串描述，包含字符“1”（桌子被占用）和“0”（桌子空着）。

餐厅的规则禁止人们坐在距离$k$或更近的位置。也就是说，如果一个人坐在编号为$i$的桌子，那么编号从$i-k$到$i+k$（除了第$i$个）的所有桌子都应该空着。换句话说，任何两个被占用的桌子的编号之差的绝对值必须严格大于$k$。

例如，如果$n=8$且$k=2$，那么：
- 字符串“10010001”、“10000010”、“00000000”、“00100000”满足餐厅的规则；
- 字符串“10100100”、“10011001”、“11111111”不满足餐厅的规则，因为每个字符串中都有一对“1”之间的距离小于或等于$k=2$。

特别地，如果餐厅的状态由一个没有“1”的字符串或只有一个“1”的字符串描述，那么餐厅的要求是满足的。

给你一个二进制字符串$s$，描述餐厅的当前状态。保证字符串$s$满足餐厅的规则。

找出你可以占用的最大数量的空桌子，以便不违反餐厅的规则。形式上，最多可以将多少个“0”替换为“1”，使得要求仍然满足？

例如，如果$n=6$，$k=1$，$s=$“100010”，那么问题的答案将是$1$，因为只有位置$3$的桌子可以被占用，使得规则仍然满足。

## 说明/提示

第一个测试用例在题目描述中解释。

在第二个测试用例中，答案是$2$，因为你可以选择第一和第六张桌子。

在第三个测试用例中，你不能在不违反餐厅规则的情况下占用任何空桌子。

## 样例 #1

### 输入

```
6
6 1
100010
6 2
000000
5 1
10101
3 1
001
2 2
00
1 1
0```

### 输出

```
1
2
0
1
1
1```

【算法分类】贪心

【题解分析与结论】
本题的核心思路是通过贪心算法，尽可能多地放置“1”，同时确保每个“1”之间的距离大于$k$。多个题解都采用了类似的方法，但实现细节有所不同。主要思路包括：
1. 遍历字符串，找到可以放置“1”的位置。
2. 使用前缀和或记录上一个“1”的位置来快速判断当前位置是否可以放置“1”。
3. 在放置“1”后，跳过接下来的$k$个位置，以避免违反规则。

【评分较高的题解】

1. **作者：LeavingZzz (赞：4)**
   - **星级：4.5**
   - **关键亮点**：使用前缀和数组快速判断当前位置是否可以放置“1”，代码简洁高效。
   - **核心代码**：
     ```cpp
     for(register int i=1;i<=N;i++) {
         if(s[i]=='1') last=i;
         if(i-last>k&&sum[i+k]==sum[i]) ++ans,last=i;
     }
     ```
   - **个人心得**：通过前缀和数组避免了复杂的边界判断，代码可读性强。

2. **作者：追梦之鲸 (赞：3)**
   - **星级：4**
   - **关键亮点**：使用前缀和数组优化暴力解法，思路清晰，代码易于理解。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         if(a[i]) i+=k;
         else if(b[i]==b[min(i+k,n)]) ans++,i+=k;
     }
     ```
   - **个人心得**：通过前缀和数组优化了暴力解法，减少了时间复杂度。

3. **作者：__int127 (赞：0)**
   - **星级：4**
   - **关键亮点**：使用前缀和数组快速判断当前位置是否可以放置“1”，代码简洁高效。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         if(a[i]==1) i+=k;
         else if(sum[i]==sum[min(i+k,n)]) gs++,i+=k;
     }
     ```
   - **个人心得**：通过前缀和数组避免了复杂的边界判断，代码可读性强。

【最优关键思路】
使用前缀和数组快速判断当前位置是否可以放置“1”，并在放置“1”后跳过接下来的$k$个位置，以确保不违反规则。这种方法既高效又易于实现。

【可拓展之处】
类似的问题可以扩展到二维空间，例如在网格中放置物体，要求物体之间的距离大于某个值。可以使用类似的前缀和或二维前缀和来优化判断。

【推荐题目】
1. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：34.90秒