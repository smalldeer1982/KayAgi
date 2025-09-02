# 题目信息

# Library of Magic

## 题目描述

This is an interactive problem.

The Department of Supernatural Phenomena at the Oxenfurt Academy has opened the Library of Magic, which contains the works of the greatest sorcerers of Redania — $ n $ ( $ 3 \leq n \leq 10^{18} $ ) types of books, numbered from $ 1 $ to $ n $ . Each book's type number is indicated on its spine. Moreover, each type of book is stored in the library in exactly two copies! And you have been appointed as the librarian.

One night, you wake up to a strange noise and see a creature leaving the building through a window. Three thick tomes of different colors were sticking out of the mysterious thief's backpack. Before you start searching for them, you decide to compute the numbers $ a $ , $ b $ , and $ c $ written on the spines of these books. All three numbers are distinct.

So, you have an unordered set of tomes, which includes one tome with each of the pairwise distinct numbers $ a $ , $ b $ , and $ c $ , and two tomes for all numbers from $ 1 $ to $ n $ , except for $ a $ , $ b $ , and $ c $ . You want to find these values $ a $ , $ b $ , and $ c $ .

Since you are not working in a simple library, but in the Library of Magic, you can only use one spell in the form of a query to check the presence of books in their place:

- "xor l r" — Bitwise XOR query with parameters $ l $ and $ r $ . Let $ k $ be the number of such tomes in the library whose numbers are greater than or equal to $ l $ and less than or equal to $ r $ . You will receive the result of the computation $ v_1 \oplus v_2 \oplus ... \oplus v_k $ , where $ v_1 ... v_k $ are the numbers on the spines of these tomes, and $ \oplus $ denotes the operation of [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng).

Since your magical abilities as a librarian are severely limited, you can make no more than $ 150 $ queries.

## 说明/提示

In the first test case, the books in the library after the theft look like this:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2036G/fa5245a6b21b822e029654d6d78459d7dcab42ae.png)

Now consider the answers to the queries:

- For the query "xor 1 1", you receive the result $ 1 \oplus 1 = 0 $ . Two tomes satisfy the condition specified in the query — both with the number $ 1 $ .
- For the query "xor 2 2", you receive the result $ 2 $ , as only one tome satisfies the specified condition.
- For the query "xor 3 3", you receive the result $ 3 $ .
- For the query "xor 4 6", you receive the result $ 4 \oplus 6 \oplus 4 \oplus 5 \oplus 6 = 5 $ .

In the second test case, there are only $ 3 $ types of books, and it is easy to guess that the missing ones have the numbers $ 1 $ , $ 2 $ , and $ 3 $ .

## 样例 #1

### 输入

```
2
6

0

2

3

5

3```

### 输出

```
xor 1 1

xor 2 2

xor 3 3

xor 4 6

ans 2 3 5

ans 1 2 3```

# AI分析结果

### 题目内容
# 魔法图书馆

## 题目描述
这是一道交互题。

奥森弗特学院的超自然现象系开放了魔法图书馆，馆内收藏着瑞达尼亚最伟大的巫师们的著作——共有 $n$（$3 \leq n \leq 10^{18}$）种书籍，编号从 $1$ 到 $n$ 。每本书的书脊上都标有其类型编号。此外，图书馆中每种类型的书都恰好有两本！而你被任命为图书管理员。

一天晚上，你被一阵奇怪的噪音吵醒，看到一个生物从窗户离开了大楼。神秘小偷的背包里露出三本不同颜色的厚书。在你开始寻找它们之前，你决定先计算出写在这些书书脊上的数字 $a$、$b$ 和 $c$ 。这三个数字各不相同。

所以，你有一组无序的书籍，其中包括一本标有两两不同数字 $a$、$b$ 和 $c$ 的书，以及除了 $a$、$b$ 和 $c$ 之外，编号从 $1$ 到 $n$ 的所有数字对应的两本书。你想找到这些值 $a$、$b$ 和 $c$ 。

由于你工作的不是普通图书馆，而是魔法图书馆，你只能使用一种以查询形式出现的魔法咒语来检查书籍是否在原位：
- “xor l r” —— 带参数 $l$ 和 $r$ 的按位异或查询。设 $k$ 为图书馆中编号大于等于 $l$ 且小于等于 $r$ 的书籍数量。你将得到计算结果 $v_1 \oplus v_2 \oplus \cdots \oplus v_k$，其中 $v_1 \cdots v_k$ 是这些书书脊上的数字，$\oplus$ 表示 [按位异或](http://tiny.cc/xor_wiki_eng) 运算。

由于你作为图书管理员的魔法能力严重受限，你最多只能进行 $150$ 次查询。

## 说明/提示
在第一个测试用例中，盗窃发生后图书馆中的书籍情况如下：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2036G/fa5245a6b21b822e029654d6d78459d7dcab42ae.png)

现在考虑对查询的回答：
- 对于查询 “xor 1 1”，你得到的结果是 $1 \oplus 1 = 0$ 。有两本书满足查询中指定的条件 —— 两本书的编号都是 $1$ 。
- 对于查询 “xor 2 2”，你得到的结果是 $2$，因为只有一本书满足指定条件。
- 对于查询 “xor 3 3”，你得到的结果是 $3$ 。
- 对于查询 “xor 4 6”，你得到的结果是 $4 \oplus 6 \oplus 4 \oplus 5 \oplus 6 = 5$ 。

在第二个测试用例中，只有 $3$ 种类型的书，很容易猜到丢失的书的编号是 $1$、$2$ 和 $3$ 。

## 样例 #1
### 输入
```
2
6

0

2

3

5

3
```
### 输出
```
xor 1 1

xor 2 2

xor 3 3

xor 4 6

ans 2 3 5

ans 1 2 3
```

### 综合分析与结论
1. **思路要点**：所有题解都基于先通过“xor 1 n”获取三个缺失数的异或和 $a \oplus b \oplus c$ ，再分情况讨论。当 $a \oplus b \oplus c \neq 0$ 时，利用二分查找确定其中两个数，进而求出第三个数；当 $a \oplus b \oplus c = 0$ 时，利用该条件下三个数二进制位的特殊性质，先确定其中一个数，再通过二分查找确定另外两个数。
2. **难点对比**：难点在于处理 $a \oplus b \oplus c = 0$ 的情况。此时常规二分查找因不具有单调性而失效，需要挖掘该条件下三个数二进制位的性质，如最高位不可能三个数都为 $0$ ，一定是两个 $1$ ；或者 $b$、$c$ 位数相同且大于 $a$ 的位数等，从而找到解决办法。
3. **简要评分**：
    - 沉石鱼惊旋：5星。思路清晰，详细阐述了二分查找失效的原因及特殊情况的处理方式，代码简洁明了，逻辑清晰。
    - luogu_gza：4星。简洁地阐述了整体思路，虽然未详细展开代码，但核心思路明确。
    - MrPython：4星。对两种情况的分析清晰，代码使用C++20新特性，较为简洁优美。

### 所选的题解
1. **沉石鱼惊旋**
    - **星级**：5星
    - **关键亮点**：对二分查找在特殊情况下失效的原因分析透彻，针对 $a \oplus b \oplus c = 0$ 的情况，通过从大到小枚举最高位，利用该情况下二进制位的性质找到最小值，再二分找出最大值，逻辑严谨，代码实现清晰。
    - **重点代码**：
```cpp
ll xor_n(ll n)
{
    ll t = n & 3;
    if (t & 1)
        return t / 2 ^ 1;
    return t / 2 ^ n;
}
ll query(ll l, ll r)
{
    cout << "xor " << l << ' ' << r << '\n';
    ll x;
    cin >> x;
    return x;
}
void solve()
{
    ll n;
    cin >> n;
    ll axbxc = query(1, n);
    if (axbxc == 0)
    {
        for (int i = 60; i >= 0; i--)
        {
            if ((1LL << i) - 1 > n)
                continue;
            ll t = query(1, (1LL << i) - 1);
            if (t)
            {
                ll a = t;
                ll L = a + 1, R = n;
                ll c = 1;
                while (L <= R)
                {
                    ll mid = L + R >> 1;
                    if (query(mid, n))
                        L = (c = mid) + 1;
                    else
                        R = mid - 1;
                }
                cout << "ans " << a << ' ' << (axbxc ^ a ^ c) << ' ' << c << endl;
                return;
            }
        }
    }
    else
    {
        ll L = 1, R = n, a = n;
        while (L <= R)
        {
            ll mid = L + R >> 1;
            if (query(1, mid))
                R = (a = mid) - 1;
            else
                L = mid + 1;
        }
        L = 1, R = n;
        ll c = 1;
        while (L <= R)
        {
            ll mid = L + R >> 1;
            if (query(mid, n))
                L = (c = mid) + 1;
            else
                R = mid - 1;
        }
        cout << "ans " << a << ' ' << (axbxc ^ a ^ c) << ' ' << c << endl;
    }
}
```
    - **核心实现思想**：先通过query(1, n)获取三个缺失数的异或和axbxc。若axbxc为0，从60位开始从大到小枚举，找到第一个使query(1, (1LL << i) - 1)不为0的i，此时该值为最小值a，再从a + 1开始二分找到最大值c，最后计算出中间值。若axbxc不为0，直接通过两次二分分别找到最小值a和最大值c，再计算出中间值。
2. **luogu_gza**
    - **星级**：4星
    - **关键亮点**：简洁地指出两种情况的处理思路，即根据q(1,n)的值，分别采用不同的二分策略，虽然未给出详细代码，但核心思路明确。
    - **重点代码**：无
    - **核心实现思想**：若q(1,n)>0，用二分求出a和b，再通过c = q(1,n) ⊕ a ⊕ b得到c；若q(1,n)=0，先二分出a，再对q(a + 1,n)套用q(1,n)>0的方法求出b和c。
3. **MrPython**
    - **星级**：4星
    - **关键亮点**：对两种情况的分析清晰，通过C++20的ranges库简化了二分查找的实现，代码简洁优美。
    - **重点代码**：
```cpp
uli ask(uli l, uli r) {
  fout << "xor " << l << ' ' << r << endl;
  uli ans;
  fin >> ans;
  return ans;
}
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    uli n;
    fin >> n;
    uli x = ask(1, n) == 0
               ? [n] {
                    for (uli i = 2; i < n; i *= 2) {
                      uli res = ask(1, i - 1);
                      if (res!= 0) return res;
                    }
                    exit(300);
                  }()
                : [n] {
                    auto view = ranges::views::iota(1ull, n + 1) |
                                ranges::views::transform(
                                    [](uli v) -> bool { return ask(1, v); });
                    auto it = ranges::lower_bound(view, true);
                    return uli(it - view.begin()) + 1ull;
                  }();
    uli y = [n, x] {
      auto view = ranges::views::iota(x + 1, n + 1) |
                  ranges::views::transform(
                      [x](uli v) -> bool { return ask(x + 1, v); });
      auto it = ranges::lower_bound(view, true);
      return uli(it - view.begin()) + (x + 1);
    }();
    uli z = ask(y + 1, n);
    fout << "ans " << x << ' ' << y << ' ' << z << endl;
  }
  return 0;
}
```
    - **核心实现思想**：通过ask函数进行查询。在主函数中，根据ask(1, n)的结果，若为0，从2开始以2的倍数枚举，找到第一个使ask(1, i - 1)不为0的i，该值为x；若不为0，通过ranges::views::iota和ranges::views::transform结合ranges::lower_bound找到第一个使ask(1, v)为真的v，该值为x。然后类似地找到y，最后通过ask(y + 1, n)得到z。

### 最优关键思路或技巧
1. **利用异或性质**：利用 $x \oplus x = 0$ 的性质，将区间查询转化为对缺失三个数的异或和查询，从而简化问题。
2. **分情况讨论与二分查找**：根据三个缺失数异或和是否为0分情况讨论。当异或和不为0时，利用前缀和后缀异或的单调性进行二分查找；当异或和为0时，挖掘二进制位性质，先确定一个数，再二分查找另外两个数。

### 可拓展之处
1. **同类型题**：此类交互题通常需要根据给定的操作和限制条件，巧妙利用数据性质，通过特定的查询策略解决问题。类似的题目可能会改变数据范围、查询操作或限制条件等。
2. **类似算法套路**：在处理涉及异或运算的问题时，常利用异或的基本性质（如交换律、结合律、$x \oplus x = 0$ 等）对问题进行简化和转化。同时，分情况讨论和二分查找是解决此类具有特殊条件限制问题的常用策略。

### 洛谷相似题目推荐
1. [P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)：基础的二分查找应用题目，帮助巩固二分查找的基本实现。
2. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：通过二分答案来解决最值问题，锻炼二分查找在实际问题中的应用能力。
3. [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：同样是二分答案的题目，进一步加深对二分查找在优化问题中应用的理解。

### 个人心得摘录与总结
1. **沉石鱼惊旋**：一开始看错题，以为还要求1到n的数的异或和。总结：做题需仔细读题，明确题目要求，避免因误解题意浪费时间。
2. **Hoks**：卡G，10发，最后5min意识到但还是写错，赛后一发过。总结：做题时要注意边界条件和细节处理，同时在比赛中要合理分配时间，及时检查和修正代码。 

---
处理用时：57.46秒