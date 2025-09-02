# 题目信息

# Card Deck

## 题目描述

You have a deck of $ n $ cards, and you'd like to reorder it to a new one.

Each card has a value between $ 1 $ and $ n $ equal to $ p_i $ . All $ p_i $ are pairwise distinct. Cards in a deck are numbered from bottom to top, i. e. $ p_1 $ stands for the bottom card, $ p_n $ is the top card.

In each step you pick some integer $ k > 0 $ , take the top $ k $ cards from the original deck and place them, in the order they are now, on top of the new deck. You perform this operation until the original deck is empty. (Refer to the notes section for the better understanding.)

Let's define an order of a deck as $ \sum\limits_{i = 1}^{n}{n^{n - i} \cdot p_i} $ .

Given the original deck, output the deck with maximum possible order you can make using the operation above.

## 说明/提示

In the first test case, one of the optimal strategies is the next one:

1. take $ 1 $ card from the top of $ p $ and move it to $ p' $ : $ p $ becomes $ [1, 2, 3] $ , $ p' $ becomes $ [4] $ ;
2. take $ 1 $ card from the top of $ p $ : $ p $ becomes $ [1, 2] $ , $ p' $ becomes $ [4, 3] $ ;
3. take $ 1 $ card from the top of $ p $ : $ p $ becomes $ [1] $ , $ p' $ becomes $ [4, 3, 2] $ ;
4. take $ 1 $ card from the top of $ p $ : $ p $ becomes empty, $ p' $ becomes $ [4, 3, 2, 1] $ .

 In result, $ p' $ has order equal to $ 4^3 \cdot 4 + 4^2 \cdot 3 + 4^1 \cdot 2 + 4^0 \cdot 1 $ $ = $ $ 256 + 48 + 8 + 1 = 313 $ .In the second test case, one of the optimal strategies is:

1. take $ 4 $ cards from the top of $ p $ and move it to $ p' $ : $ p $ becomes $ [1] $ , $ p' $ becomes $ [5, 2, 4, 3] $ ;
2. take $ 1 $ card from the top of $ p $ and move it to $ p' $ : $ p $ becomes empty, $ p' $ becomes $ [5, 2, 4, 3, 1] $ ;

 In result, $ p' $ has order equal to $ 5^4 \cdot 5 + 5^3 \cdot 2 + 5^2 \cdot 4 + 5^1 \cdot 3 + 5^0 \cdot 1 $ $ = $ $ 3125 + 250 + 100 + 15 + 1 = 3491 $ .In the third test case, one of the optimal strategies is:

1. take $ 2 $ cards from the top of $ p $ and move it to $ p' $ : $ p $ becomes $ [4, 2, 5, 3] $ , $ p' $ becomes $ [6, 1] $ ;
2. take $ 2 $ cards from the top of $ p $ and move it to $ p' $ : $ p $ becomes $ [4, 2] $ , $ p' $ becomes $ [6, 1, 5, 3] $ ;
3. take $ 2 $ cards from the top of $ p $ and move it to $ p' $ : $ p $ becomes empty, $ p' $ becomes $ [6, 1, 5, 3, 4, 2] $ .

 In result, $ p' $ has order equal to $ 6^5 \cdot 6 + 6^4 \cdot 1 + 6^3 \cdot 5 + 6^2 \cdot 3 + 6^1 \cdot 4 + 6^0 \cdot 2 $ $ = $ $ 46656 + 1296 + 1080 + 108 + 24 + 2 = 49166 $ .

## 样例 #1

### 输入

```
4
4
1 2 3 4
5
1 5 2 4 3
6
4 2 5 3 6 1
1
1```

### 输出

```
4 3 2 1
5 2 4 3 1
6 1 5 3 4 2
1```

# AI分析结果

### 题目内容
# 纸牌堆

## 题目描述
你有一副包含 $n$ 张牌的纸牌堆，你想要将其重新排列成一个新的纸牌堆。

每张牌都有一个在 $1$ 到 $n$ 之间的值 $p_i$ 。所有的 $p_i$ 两两不同。纸牌堆中的纸牌从下到上编号，即 $p_1$ 代表最下面的牌，$p_n$ 是最上面的牌。

在每一步中，你选择某个整数 $k > 0$ ，从原始纸牌堆的顶部取出 $k$ 张牌，并按照它们当前的顺序放在新纸牌堆的顶部。你重复这个操作，直到原始纸牌堆为空。（参考注释部分以更好地理解）。

我们将一个纸牌堆的顺序定义为 $\sum\limits_{i = 1}^{n}{n^{n - i} \cdot p_i}$ 。

给定原始纸牌堆，输出你可以通过上述操作得到的具有最大可能顺序的纸牌堆。

## 说明/提示
在第一个测试用例中，一种最优策略如下：
1. 从 $p$ 的顶部取 $1$ 张牌并将其移动到 $p'$ ：$p$ 变为 $[1, 2, 3]$ ，$p'$ 变为 $[4]$ ；
2. 从 $p$ 的顶部取 $1$ 张牌 ：$p$ 变为 $[1, 2]$ ，$p'$ 变为 $[4, 3]$ ；
3. 从 $p$ 的顶部取 $1$ 张牌 ：$p$ 变为 $[1]$ ，$p'$ 变为 $[4, 3, 2]$ ；
4. 从 $p$ 的顶部取 $1$ 张牌 ：$p$ 变为空，$p'$ 变为 $[4, 3, 2, 1]$ 。

结果，$p'$ 的顺序等于 $4^3 \cdot 4 + 4^2 \cdot 3 + 4^1 \cdot 2 + 4^0 \cdot 1$ $ = $ $256 + 48 + 8 + 1 = 313$ 。
在第二个测试用例中，一种最优策略如下：
1. 从 $p$ 的顶部取 $4$ 张牌并将其移动到 $p'$ ：$p$ 变为 $[1]$ ，$p'$ 变为 $[5, 2, 4, 3]$ ；
2. 从 $p$ 的顶部取 $1$ 张牌并将其移动到 $p'$ ：$p$ 变为空，$p'$ 变为 $[5, 2, 4, 3, 1]$ ；

结果，$p'$ 的顺序等于 $5^4 \cdot 5 + 5^3 \cdot 2 + 5^2 \cdot 4 + 5^1 \cdot 3 + 5^0 \cdot 1$ $ = $ $3125 + 250 + 100 + 15 + 1 = 3491$ 。
在第三个测试用例中，一种最优策略如下：
1. 从 $p$ 的顶部取 $2$ 张牌并将其移动到 $p'$ ：$p$ 变为 $[4, 2, 5, 3]$ ，$p'$ 变为 $[6, 1]$ ；
2. 从 $p$ 的顶部取 $2$ 张牌并将其移动到 $p'$ ：$p$ 变为 $[4, 2]$ ，$p'$ 变为 $[6, 1, 5, 3]$ ；
3. 从 $p$ 的顶部取 $2$ 张牌并将其移动到 $p'$ ：$p$ 变为空，$p'$ 变为 $[6, 1, 5, 3, 4, 2]$ 。

结果，$p'$ 的顺序等于 $6^5 \cdot 6 + 6^4 \cdot 1 + 6^3 \cdot 5 + 6^2 \cdot 3 + 6^1 \cdot 4 + 6^0 \cdot 2$ $ = $ $46656 + 1296 + 1080 + 108 + 24 + 2 = 49166$ 。

## 样例 #1
### 输入
```
4
4
1 2 3 4
5
1 5 2 4 3
6
4 2 5 3 6 1
1
1
```
### 输出
```
4 3 2 1
5 2 4 3 1
6 1 5 3 4 2
1
```

### 算法分类
贪心

### 综合分析与结论
所有题解都基于贪心策略，核心思路是为使 $\sum\limits_{i = 1}^{n}{n^{n - i} \cdot p_i}$ 最大，要让较大值尽可能处于低位（即靠前位置）。
 - **思路方面**：都围绕如何确定每次移动的牌组，保证最终序列字典序最大。
 - **算法要点**：多数通过寻找当前剩余牌中的最大值及其位置相关信息，来决定移动哪些牌。如记录前缀最大值、从后往前扫描找最大值等方式。
 - **解决难点**：理解并证明贪心策略的正确性，即为何每次取剩余牌中的最大值及其后续牌移动能得到最优解。部分题解通过将式子类比为 $n$ 进制数，利用 $n$ 进制数大小比较规则辅助理解。

### 所选的题解
- **作者：KSToki (5星)**
  - **关键亮点**：提供两种思路，代码实现采用从后往前扫，扫到当前最大值时输出当前位置到上一个位置之间数的方法，思路清晰，代码简洁。
  - **核心代码**：
```cpp
int T,n,a[100001];
bool h[100001];
int main()
{
    T=read();
    while(T--)
    {
        n=read();
        for(R int i=1;i<=n;++i)
            a[i]=read(),h[i]=0;
        int p=n,lst=n+1;
        for(R int i=n;i;--i)
        {
            if(a[i]==p)
            {
                for(R int j=i;j<lst;++j)
                    printf("%d ",a[j]);
                lst=i;
                --p;
                while(h[p])
                    --p;
            }
            h[a[i]]=1;
        }
        puts("");
    }
    return 0;
}
```
  - **核心思想**：从后往前遍历数组 `a`，当遇到值等于当前最大值 `p` 时，输出从当前位置 `i` 到上一次最大值位置 `lst` 之间的数，更新 `lst` 为 `i`，并更新 `p` 为下一个未处理的最大值。同时用数组 `h` 标记已处理的数。
- **作者：xuezhe (4星)**
  - **关键亮点**：提出每次后缀取最大值相当于倒着取出每个前缀最大值，通过预处理前缀最大值，按从大到小顺序取出对应区间数，时间复杂度 $O(n)$。
  - **核心代码**：
```cpp
const int N(100005);
int t,n,p[N];
vector<int> v;
 
void fakemain(){
    Read(t);
    while(t--){
        v.clear();
        Read(n);
        for(int i=1;i<=n;++i){
            Read(p[i]);
            if(!v.size() || p[v.back()]<p[i])
                v.push_back(i);
        }
        v.push_back(n+1);
        for(int i=v.size()-2;~i;--i)
            for(int j=v[i];j<v[i+1];++j)
                Print(p[j],32);
        putchar(10);
    }
}
```
  - **核心思想**：遍历输入数组 `p`，若当前数大于 `vector v` 中最后一个位置对应的数，则将当前位置加入 `v`，这样 `v` 中保存了前缀最大值的位置。最后按从大到小顺序遍历 `v`，输出每个位置区间内的数。
- **作者：超级玛丽王子 (4星)**
  - **关键亮点**：详细证明贪心策略的正确性，通过将计算结果类比为不进位的 $n$ 进制数，从字典序角度分析为何贪心策略能使结果最大。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T;
int n;
int a[N],mx[N],pos=0,last,b[N];
inline int read() {
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    int x=0;
    while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
    return x;
}
inline int write(int x) {
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int main(void) {
    T=read();
    while(T--) {
        n=read();
        pos=0,last=n+1;
        for(int i=1;i<=n;++i) a[i]=read(),mx[i]=max(mx[i-1],a[i]);
        for(int i=n;i>=1;--i) {
            if(a[i]==mx[i]) {
                for(int j=i;j<last;++j) b[++pos]=a[j];
                last=i;
            }
        }
        for(int i=1;i<=n;++i) write(b[i]),putchar(' ');
        putchar('\n');
    }
    return 0;
}
```
  - **核心思想**：先预处理出数组 `a` 的前缀最大值数组 `mx`，从后往前遍历 `a`，当当前数等于当前位置前缀最大值时，将当前位置到 `last` 之间的数存入 `b` 数组，更新 `last` 为当前位置，最后输出 `b` 数组。

### 最优关键思路或技巧
将计算结果类比为 $n$ 进制数，利用 $n$ 进制数高位数字越大值越大的特性，采用贪心策略，每次选择剩余牌中的最大值及其后续牌移动到新序列，可使最终序列对应值最大。

### 同类型题或类似算法套路拓展
此类题目通常涉及通过特定操作使某个与序列相关的式子值最大或最小，关键在于分析操作对式子的影响，找到符合直觉且可证明正确性的贪心策略。一般可以从式子结构出发，如本题通过分析 $\sum\limits_{i = 1}^{n}{n^{n - i} \cdot p_i}$ 类似 $n$ 进制数的结构得到贪心思路。

### 洛谷相似题目推荐
 - **P1080 [NOIP2012 提高组] 国王游戏**：通过对数据的分析找到贪心策略，解决与本题类似的通过合理安排顺序使某个值最大的问题。
 - **P1199 [NOIP2010 普及组] 三国游戏**：同样需要寻找合适的贪心策略，根据题目规则使结果最优，与本题在思路上有相似之处。
 - **P1248 加工生产调度**：运用贪心思想，根据不同条件确定任务执行顺序以优化结果，和本题利用贪心确定操作顺序类似。

### 个人心得摘录与总结
无。 

---
处理用时：134.96秒