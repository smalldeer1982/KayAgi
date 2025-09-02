# 题目信息

# A Cookie for You

## 题目描述

Anna is a girl so brave that she is loved by everyone in the city and citizens love her cookies. She is planning to hold a party with cookies. Now she has $ a $ vanilla cookies and $ b $ chocolate cookies for the party.

She invited $ n $ guests of the first type and $ m $ guests of the second type to the party. They will come to the party in some order. After coming to the party, each guest will choose the type of cookie (vanilla or chocolate) to eat. There is a difference in the way how they choose that type:

If there are $ v $ vanilla cookies and $ c $ chocolate cookies at the moment, when the guest comes, then

- if the guest of the first type: if $ v>c $ the guest selects a vanilla cookie. Otherwise, the guest selects a chocolate cookie.
- if the guest of the second type: if $ v>c $ the guest selects a chocolate cookie. Otherwise, the guest selects a vanilla cookie.

After that:

- If there is at least one cookie of the selected type, the guest eats one.
- Otherwise (there are no cookies of the selected type), the guest gets angry and returns to home.

Anna wants to know if there exists some order of guests, such that no one guest gets angry. Your task is to answer her question.

## 说明/提示

In the first test case, let's consider the order $ \{1, 2,       2\} $ of types of guests. Then:

- The first guest eats a chocolate cookie. After that, there are $ 2 $ vanilla cookies and $ 1 $ chocolate cookie.
- The second guest eats a chocolate cookie. After that, there are $ 2 $ vanilla cookies and $ 0 $ chocolate cookies.
- The last guest selects a chocolate cookie, but there are no chocolate cookies. So, the guest gets angry.

So, this order can't be chosen by Anna.

Let's consider the order $ \{2, 2, 1\} $ of types of guests. Then:

- The first guest eats a vanilla cookie. After that, there is $ 1 $ vanilla cookie and $ 2 $ chocolate cookies.
- The second guest eats a vanilla cookie. After that, there are $ 0 $ vanilla cookies and $ 2 $ chocolate cookies.
- The last guest eats a chocolate cookie. After that, there are $ 0 $ vanilla cookies and $ 1 $ chocolate cookie.

So, the answer to this test case is "Yes".

In the fifth test case, it is illustrated, that the number of cookies ( $ a + b $ ) can be equal to zero, but the number of guests ( $ n + m $ ) can't be equal to zero.

In the sixth test case, be careful about the overflow of $ 32 $ -bit integer type.

## 样例 #1

### 输入

```
6
2 2 1 2
0 100 0 1
12 13 25 1
27 83 14 25
0 0 1 0
1000000000000000000 1000000000000000000 1000000000000000000 1000000000000000000```

### 输出

```
Yes
No
No
Yes
No
Yes```

# AI分析结果

### 题目重写

**题目名称：A Cookie for You**

**题目描述：**

Anna 是一个勇敢的女孩，深受城市中每个人的喜爱，市民们也喜欢她的饼干。她计划举办一个饼干派对。现在她有 $a$ 块香草饼干和 $b$ 块巧克力饼干用于派对。

她邀请了 $n$ 位第一类客人和 $m$ 位第二类客人参加派对。他们会以某种顺序来到派对。每位客人来到派对后，会选择一种饼干（香草或巧克力）来吃。他们选择饼干的方式有所不同：

- 如果当前有 $v$ 块香草饼干和 $c$ 块巧克力饼干，那么：
  - 如果是第一类客人：如果 $v > c$，客人会选择香草饼干，否则会选择巧克力饼干。
  - 如果是第二类客人：如果 $v > c$，客人会选择巧克力饼干，否则会选择香草饼干。

选择后：
- 如果所选类型的饼干至少有一块，客人会吃掉一块。
- 否则（所选类型的饼干没有剩余），客人会生气并回家。

Anna 想知道是否存在一种客人的顺序，使得没有客人会生气。你的任务是回答她的问题。

**说明/提示：**

在第一个测试用例中，考虑客人的顺序 $ \{1, 2, 2\} $：
- 第一位客人吃掉一块巧克力饼干。之后，剩下 $2$ 块香草饼干和 $1$ 块巧克力饼干。
- 第二位客人吃掉一块巧克力饼干。之后，剩下 $2$ 块香草饼干和 $0$ 块巧克力饼干。
- 最后一位客人选择巧克力饼干，但没有巧克力饼干剩余，因此客人生气。

所以，这个顺序不能被 Anna 选择。

考虑客人的顺序 $ \{2, 2, 1\} $：
- 第一位客人吃掉一块香草饼干。之后，剩下 $1$ 块香草饼干和 $2$ 块巧克力饼干。
- 第二位客人吃掉一块香草饼干。之后，剩下 $0$ 块香草饼干和 $2$ 块巧克力饼干。
- 最后一位客人吃掉一块巧克力饼干。之后，剩下 $0$ 块香草饼干和 $1$ 块巧克力饼干。

所以，这个测试用例的答案是 "Yes"。

在第五个测试用例中，饼干的数量（$a + b$）可以为零，但客人的数量（$n + m$）不能为零。

在第六个测试用例中，要注意 $32$ 位整数类型的溢出问题。

**样例 #1：**

**输入：**
```
6
2 2 1 2
0 100 0 1
12 13 25 1
27 83 14 25
0 0 1 0
1000000000000000000 1000000000000000000 1000000000000000000 1000000000000000000
```

**输出：**
```
Yes
No
No
Yes
No
Yes
```

### 算法分类
贪心

### 题解分析与结论

所有题解的核心思路都是通过贪心策略来判断是否存在一种客人的顺序，使得所有客人都能吃到饼干。具体来说，题解们主要关注以下几点：

1. **饼干总数与客人总数的关系**：如果饼干总数少于客人总数，则直接输出 "No"。
2. **第二类客人与较少饼干的关系**：第二类客人会选择较少的饼干，因此较少的饼干数量必须大于等于第二类客人的数量，否则输出 "No"。
3. **第一类客人与剩余饼干的关系**：在满足前两个条件的情况下，第一类客人可以选择较多的饼干，因此剩余的饼干数量必须大于等于第一类客人的数量。

### 所选题解

1. **作者：huayucaiji (赞：3)**
   - **星级：4**
   - **关键亮点**：清晰地分析了第二类客人与第一类客人的选择逻辑，并给出了简洁的判断条件。
   - **代码实现**：
     ```cpp
     if(a+b<n+m) {
         printf("No\n");
     }
     else if(min(a,b)>=m) {
         printf("Yes\n");
     }
     else {
         printf("nO\n");
     }
     ```

2. **作者：zlqwq (赞：2)**
   - **星级：4**
   - **关键亮点**：简洁明了地给出了两种不满足条件的情况，并直接进行判断。
   - **代码实现**：
     ```cpp
     if((min(a,b) < m) || (n + m > a + b)) cout << "No" << '\n';
     else cout << "Yes" << '\n';
     ```

3. **作者：封禁用户 (赞：1)**
   - **星级：4**
   - **关键亮点**：详细分析了第二类客人与第一类客人的选择逻辑，并给出了清晰的判断条件。
   - **代码实现**：
     ```cpp
     if(min(a,b)<m||n>a+b-m)
         cout<<"No"<<endl;
     else
         cout<<"Yes"<<endl;
     ```

### 最优关键思路或技巧

1. **优先处理第二类客人**：由于第二类客人会选择较少的饼干，因此优先处理他们可以确保第一类客人有足够的饼干选择。
2. **贪心策略**：通过贪心策略，先确保第二类客人有足够的饼干，再检查第一类客人是否有足够的饼干。

### 可拓展之处

类似的问题可以扩展到其他资源分配的场景，例如任务调度、资源分配等，通过贪心策略优先处理最严格的条件，再处理其他条件。

### 推荐题目

1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得

- **调试经历**：在处理第二类客人时，需要特别注意较少的饼干数量是否足够，否则容易漏掉一些情况。
- **顿悟感想**：通过优先处理最严格的条件，可以简化问题的复杂度，使得问题更容易解决。

---
处理用时：36.85秒