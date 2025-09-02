# 题目信息

# Lucky Days

## 题目描述

Bob and Alice are often participating in various programming competitions. Like many competitive programmers, Alice and Bob have good and bad days. They noticed, that their lucky and unlucky days are repeating with some period. For example, for Alice days $ [l_a; r_a] $ are lucky, then there are some unlucky days: $ [r_a + 1; l_a + t_a - 1] $ , and then there are lucky days again: $ [l_a + t_a; r_a + t_a] $ and so on. In other words, the day is lucky for Alice if it lies in the segment $ [l_a + k t_a; r_a + k t_a] $ for some non-negative integer $ k $ .

The Bob's lucky day have similar structure, however the parameters of his sequence are different: $ l_b $ , $ r_b $ , $ t_b $ . So a day is a lucky for Bob if it lies in a segment $ [l_b + k t_b; r_b + k t_b] $ , for some non-negative integer $ k $ .

Alice and Bob want to participate in team competitions together and so they want to find out what is the largest possible number of consecutive days, which are lucky for both Alice and Bob.

## 说明/提示

The graphs below correspond to the two sample tests and show the lucky and unlucky days of Alice and Bob as well as the possible solutions for these tests.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055C/19d7a3762431cf8ed7d41c7aa787eb194dc6ab47.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055C/dee255111b7c12483568555df6c88766f900f855.png)

## 样例 #1

### 输入

```
0 2 5
1 3 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
0 1 3
2 3 6
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 幸运日

## 题目描述
鲍勃（Bob）和爱丽丝（Alice）经常参加各种编程竞赛。和许多竞赛程序员一样，爱丽丝和鲍勃都有状态好和状态不好的日子。他们注意到，他们的幸运日和不幸运日会以一定周期重复出现。例如，对于爱丽丝来说，区间$[l_a; r_a]$内的日子是幸运的，之后会有一些不幸运的日子：$[r_a + 1; l_a + t_a - 1]$，然后又是幸运的日子：$[l_a + t_a; r_a + t_a]$，依此类推。换句话说，如果某一天处于区间$[l_a + k t_a; r_a + k t_a]$中（其中$k$为某个非负整数），那么这一天对爱丽丝来说就是幸运日。

鲍勃的幸运日也有类似的结构，不过他的序列参数不同：$l_b$，$r_b$，$t_b$。所以，如果某一天处于区间$[l_b + k t_b; r_b + k t_b]$中（其中$k$为某个非负整数），那么这一天对鲍勃来说就是幸运日。

爱丽丝和鲍勃想一起参加团队竞赛，所以他们想找出两人同时都是幸运日的最大连续天数。

## 说明/提示
以下图表对应两个示例测试，展示了爱丽丝和鲍勃的幸运日和不幸运日，以及这些测试的可能解决方案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055C/19d7a3762431cf8ed7d41c7aa787eb194dc6ab47.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1055C/dee255111b7c12483568555df6c88766f900f855.png)

## 样例 #1
### 输入
```
0 2 5
1 3 5
```
### 输出
```
2
```
## 样例 #2
### 输入
```
0 1 3
2 3 6
```
### 输出
```
1
```

### 算法分类
数学

### 综合分析与结论
三道题解思路相近，均基于裴蜀定理解决问题。核心思路是让两个区间的左端点尽可能接近或重合，以求得最大重合度。难点在于理解如何运用裴蜀定理判断左端点能否重合，以及在不能重合时如何找到最接近的状态。题解通过分析式子$x \times ta - y \times tb = lb - la$与裴蜀定理$a \times x + b \times y = \gcd(a,b)$的关系，利用$\gcd(ta, tb)$判断方程是否有解，从而确定左端点能否重合。在左端点不能重合时，通过对区间左端点距离的分析，找到两种可能的最优状态进行计算。

### 所选的题解
- **作者：an_da (5星)**
    - **关键亮点**：思路清晰，详细阐述了从裴蜀定理出发的推导过程，对左端点不能重合时的两种情况分析透彻，并通过代码注释辅助理解。
    - **个人心得**：无
    - **重点代码及核心实现思想**：
```cpp
void solve()
{
    int la, ra, ta, lb, rb, tb;
    cin >> la >> ra >> ta >> lb >> rb >> tb;
    if(la > lb)
    {
        swap(la, lb);
        swap(ra, rb);
        swap(ta, tb);
    }
    int d = __gcd(ta, tb);
    int dis = (lb - la) % d; // 计算左端点的差
    int ans = 0;
    ans = max(ans, min(rb - lb + 1, ra - la + 1 - dis)); // 第一种可能的最优状态
    dis = d - dis; // 向右移动一步
    ans = max(ans, min(ra - la + 1, rb - lb + 1 - dis)); // 第二种可能的最优状态
    cout << ans << "\n";
}
```
核心实现思想是先确保$la \leq lb$，然后计算$ta$和$tb$的最大公约数$d$，根据$lb - la$对$d$取模得到左端点的差$dis$，通过两种情况计算可能的最大重合长度并取最大值。

- **作者：liujiaxi123456 (4星)**
    - **关键亮点**：从特殊情况入手，逐步推广到一般情况，引导思考过程清晰，代码简洁明了。
    - **个人心得**：无
    - **重点代码及核心实现思想**：
```cpp
inline int main() {
    cin>> l1>> r1>> t1>> l2>> r2>> t2;
    if(l1 > l2)    swap(l1, l2), swap(r1, r2), swap(t1, t2);
    int k = __gcd(t1, t2), len = l2-l1;
    int move = len/k*k;
    int ans = min(r1, r2-move) - max(l1, l2-move) + 1;
    move += k;
    ans = max(ans, min(r1, r2-move)-max(l1, l2-move)+1);
    cout<< max(ans, 0)<< '\n';
    return 0;
}
```
核心实现思想是先保证$l1 \leq l2$，计算$t1$和$t2$的最大公约数$k$，通过$l2 - l1$计算移动距离$move$，分两种情况计算重合长度并取最大值，最后输出结果。

### 最优关键思路或技巧
利用裴蜀定理判断两个区间左端点能否重合，在不能重合时通过分析左端点距离的变化找到最优状态。在代码实现上，通过交换保证一个区间左端点小于等于另一个区间左端点，简化后续计算。

### 同类型题或类似算法套路拓展
此类题目通常涉及周期性区间的重合问题，关键在于利用数论知识（如裴蜀定理）分析区间相对位置的变化规律，通过对区间端点的操作和分析找到最优解。

### 洛谷相似题目推荐
- **P1082 [NOIP2012 提高组] 同余方程**：同样考查裴蜀定理的应用，通过求解同余方程加深对裴蜀定理的理解。
- **P4549 【模板】裴蜀定理**：直接应用裴蜀定理判断方程是否有解，与本题对裴蜀定理的运用思路相似。
- **P2613 【模板】有理数取余**：涉及数论相关知识，通过取余操作考查对数学原理的应用，与本题在运用数学知识解决问题的思路上有相通之处。 

---
处理用时：90.08秒