# 题目信息

# Two Hundred Twenty One (easy version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that the easy version does not require you to output the numbers of the rods to be removed. You can make hacks only if all versions of the problem are solved.

Stitch likes experimenting with different machines with his friend Sparky. Today they built another machine.

The main element of this machine are $ n $ rods arranged along one straight line and numbered from $ 1 $ to $ n $ inclusive. Each of these rods must carry an electric charge quantitatively equal to either $ 1 $ or $ -1 $ (otherwise the machine will not work). Another condition for this machine to work is that the sign-variable sum of the charge on all rods must be zero.

More formally, the rods can be represented as an array of $ n $ numbers characterizing the charge: either $ 1 $ or $ -1 $ . Then the condition must hold: $ a_1 - a_2 + a_3 - a_4 + \ldots = 0 $ , or $ \sum\limits_{i=1}^n (-1)^{i-1} \cdot a_i = 0 $ .

Sparky charged all $ n $ rods with an electric current, but unfortunately it happened that the rods were not charged correctly (the sign-variable sum of the charge is not zero). The friends decided to leave only some of the rods in the machine. Sparky has $ q $ questions. In the $ i $ th question Sparky asks: if the machine consisted only of rods with numbers $ l_i $ to $ r_i $ inclusive, what minimal number of rods could be removed from the machine so that the sign-variable sum of charges on the remaining ones would be zero? Perhaps the friends got something wrong, and the sign-variable sum is already zero. In that case, you don't have to remove the rods at all.

If the number of rods is zero, we will assume that the sign-variable sum of charges is zero, that is, we can always remove all rods.

Help your friends and answer all of Sparky's questions!

## 说明/提示

In the first test case for the first query you can remove the rods numbered $ 5 $ and $ 8 $ , then the following set of rods will remain: +--+--++-++-. It is easy to see that here the sign-variable sum is zero.

In the second test case:

- For the first query, we can remove the rods numbered $ 1 $ and $ 11 $ , then the following set of rods will remain: --++---++---. It is easy to see that here the sign-variable sum is zero.
- For the second query we can remove the rod numbered $ 9 $ , then the following set of rods will remain: ---++-. It is easy to see that here the variable sum is zero.
- For the third query we can not remove the rods at all.

## 样例 #1

### 输入

```
3
14 1
+--++---++-++-
1 14
14 3
+--++---+++---
1 14
6 12
3 10
4 10
+-+-
1 1
1 2
1 3
1 4
2 2
2 3
2 4
3 3
3 4
4 4```

### 输出

```
2
2
1
0
1
2
1
2
1
2
1
1
2
1```

# AI分析结果

### 题目翻译
# 221（简单版本）

## 题目描述
这是该问题的简单版本。不同版本之间的区别在于，简单版本不要求你输出需要移除的杆的编号。只有当所有版本的问题都被解决后，你才能进行 Hack 操作。

斯迪奇喜欢和他的朋友斯帕基一起用不同的机器做实验。今天他们又制造了一台新机器。

这台机器的主要元件是 $n$ 根沿同一条直线排列的杆，编号从 $1$ 到 $n$ 。每根杆必须携带数量为 $1$ 或 $-1$ 的电荷（否则机器将无法工作）。这台机器正常工作的另一个条件是，所有杆上电荷的带符号变量和必须为零。

更正式地说，这些杆可以用一个包含 $n$ 个数字的数组来表示，这些数字代表电荷，取值为 $1$ 或 $-1$ 。那么必须满足条件：$a_1 - a_2 + a_3 - a_4 + \ldots = 0$ ，即 $\sum\limits_{i=1}^n (-1)^{i - 1} \cdot a_i = 0$ 。

斯帕基给所有 $n$ 根杆都通了电流，但不幸的是，杆的充电情况不正确（电荷的带符号变量和不为零）。朋友们决定只保留机器中的部分杆。斯帕基有 $q$ 个问题。在第 $i$ 个问题中，斯帕基问道：如果机器只由编号从 $l_i$ 到 $r_i$ 的杆组成，那么最少需要从机器中移除多少根杆，才能使剩余杆上电荷的带符号变量和为零？也许朋友们哪里弄错了，电荷的带符号变量和已经为零。在这种情况下，根本不需要移除任何杆。

如果杆的数量为零，我们将假设电荷的带符号变量和为零，也就是说，我们总是可以移除所有的杆。

帮助你的朋友们，回答斯帕基的所有问题！

## 说明/提示
在第一个测试用例的第一个查询中，你可以移除编号为 $5$ 和 $8$ 的杆，那么剩下的杆的排列为：+--+--++-++- 。很容易看出，这里的带符号变量和为零。

在第二个测试用例中：
- 对于第一个查询，我们可以移除编号为 $1$ 和 $11$ 的杆，那么剩下的杆的排列为：--++---++--- 。很容易看出，这里的带符号变量和为零。
- 对于第二个查询，我们可以移除编号为 $9$ 的杆，那么剩下的杆的排列为：---++- 。很容易看出，这里的变量和为零。
- 对于第三个查询，我们根本不需要移除任何杆。

## 样例 #1
### 输入
```
3
14 1
+--++---++-++-
1 14
14 3
+--++---+++---
1 14
6 12
3 10
4 10
+-+-
1 1
1 2
1 3
1 4
2 2
2 3
2 4
3 3
3 4
4 4
```

### 输出
```
2
2
1
0
1
2
1
2
1
2
1
1
2
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先通过前缀和处理序列，再根据区间长度和区间和的情况来判断最少的删除次数。具体结论为：若区间本身满足条件（区间和为 0），则无需删除；若区间长度为奇数，只需删除 1 次；若区间长度为偶数且区间和不为 0，则需删除 2 次。不同题解的区别主要在于对结论的证明方式不同。

### 所选题解
- XL4453（4星）
  - 关键亮点：思路清晰，先给出结论，再进行证明，代码简洁易懂。
  - 证明思路：发现形如 $++$ 或 $--$ 的序列不影响结果，将其删去后得到形如 $+-+-+-+-...$ 的序列。对于奇数长度的序列，删除正中间的节点可使序列满足条件；对于偶数长度的序列，删除中间的一个节点后还需再删除一个节点。
- Echidna（4星）
  - 关键亮点：详细证明了奇数长度序列最多删一次就行，通过定义函数 $g(x)$ 分析其变化情况，利用函数的零点性质证明结论。
  - 证明思路：设 $b_i = a_i \cdot (-1)^{i - 1}$，$f(l, r) = \sum\limits_{i = 1}^n b_i$，$g(x) = f(1, x - 1) - f(x + 1, n)$。分 $b_x \ne b_{x + 1}$ 和 $b_x = b_{x + 1}$ 两种情况讨论 $g(x)$ 的变化，发现 $g(1)$ 和 $g(n)$ 一定都是偶数且互为相反数，$g(x)$ 的变化以 2 为单位，所以 $g(x)$ 一定有零点，即奇数长度序列最多删一次就行。对于偶数长度序列，分不用删和需要删两种情况讨论，需要删时先删一个，问题转化为奇数长度序列，再删一次即可。
- KSToki（4星）
  - 关键亮点：证明过程简洁明了，通过分析每个数对答案的贡献，利用贡献的连续性证明奇数长度序列只需要删一个数。
  - 证明思路：设原本计算出的值为 $s$，删掉的数对最终答案贡献为 $\pm1$，并使其后面部分所有数的贡献反转，即总贡献取相反数。每个数对答案贡献为 $\pm1$，那么贡献将会是连续变化的，能取到 $s$ 就一定能取到 $\frac{s}{2}$，所以一定存在一个位置使左两部分原贡献相等，即奇数长度序列只需要删一个数。

### 重点代码
```cpp
// XL4453 的代码
#include<cstdio>
using namespace std;
int T,n,num[300005],q,l,r;
char c;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++){
            c=getchar();
            while(c!='+'&&c!='-')c=getchar();
            if(c=='+')num[i]=1;
            else num[i]=-1;
            if(i%2==0)num[i]*=-1;
            num[i]=num[i]+num[i-1];
        }
        for(int i=1;i<=q;i++){
            scanf("%d%d",&l,&r);
            if(num[r]-num[l-1]==0){printf("0\n");continue;}
            if((r-l)%2==0)printf("1\n");
            else printf("2\n");
        }
    }
    return 0;
}
```
核心实现思想：先通过前缀和处理序列，对于每个询问，判断区间和是否为 0，若为 0 则输出 0；否则根据区间长度的奇偶性输出 1 或 2。

### 关键思路与技巧
- 利用前缀和快速计算区间和。
- 发现连续的 $++$ 或 $--$ 序列不影响结果，对序列进行简化。
- 通过数学推理证明结论，根据区间长度的奇偶性判断最少删除次数。

### 拓展思路
同类型题可能会有不同的序列规则和操作要求，但核心思路都是通过分析序列的性质和操作的影响，找到满足条件的最少操作次数。类似的算法套路包括利用数学性质简化问题、通过前缀和等数据结构快速计算区间信息等。

### 推荐题目
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：考察动态规划和数学思维。
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，涉及动态规划和数学优化。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：考察递推和数学归纳思想。

### 个人心得
无

---
处理用时：101.86秒