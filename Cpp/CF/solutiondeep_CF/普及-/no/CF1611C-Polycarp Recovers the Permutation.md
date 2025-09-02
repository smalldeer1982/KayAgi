# 题目信息

# Polycarp Recovers the Permutation

## 题目描述

Polycarp wrote on a whiteboard an array $ p $ of length $ n $ , which is a permutation of numbers from $ 1 $ to $ n $ . In other words, in $ p $ each number from $ 1 $ to $ n $ occurs exactly once.

He also prepared a resulting array $ a $ , which is initially empty (that is, it has a length of $ 0 $ ).

After that, he did exactly $ n $ steps. Each step looked like this:

- Look at the leftmost and rightmost elements of $ p $ , and pick the smaller of the two.
- If you picked the leftmost element of $ p $ , append it to the left of $ a $ ; otherwise, if you picked the rightmost element of $ p $ , append it to the right of $ a $ .
- The picked element is erased from $ p $ .

Note that on the last step, $ p $ has a length of $ 1 $ and its minimum element is both leftmost and rightmost. In this case, Polycarp can choose what role the minimum element plays. In other words, this element can be added to $ a $ both on the left and on the right (at the discretion of Polycarp).

Let's look at an example. Let $ n=4 $ , $ p=[3, 1, 4, 2] $ . Initially $ a=[] $ . Then:

- During the first step, the minimum is on the right (with a value of $ 2 $ ), so after this step, $ p=[3,1,4] $ and $ a=[2] $ (he added the value $ 2 $ to the right).
- During the second step, the minimum is on the left (with a value of $ 3 $ ), so after this step, $ p=[1,4] $ and $ a=[3,2] $ (he added the value $ 3 $ to the left).
- During the third step, the minimum is on the left (with a value of $ 1 $ ), so after this step, $ p=[4] $ and $ a=[1,3,2] $ (he added the value $ 1 $ to the left).
- During the fourth step, the minimum is both left and right (this value is $ 4 $ ). Let's say Polycarp chose the right option. After this step, $ p=[] $ and $ a=[1,3,2,4] $ (he added the value $ 4 $ to the right).

Thus, a possible value of $ a $ after $ n $ steps could be $ a=[1,3,2,4] $ .

You are given the final value of the resulting array $ a $ . Find any possible initial value for $ p $ that can result the given $ a $ , or determine that there is no solution.

## 说明/提示

The first test case in the example is clarified in the main section of the problem statement. There may be other correct answers for this test set.

In the second test case, $ n=1 $ . Thus, there is only one permutation that can be the answer: $ p=[1] $ . Indeed, this is the answer to this test case.

In the third test case of the example, no matter what permutation you take as $ p $ , after applying the $ n $ steps, the result will differ from $ a=[1, 3, 5, 4, 2] $ .

## 样例 #1

### 输入

```
4
4
1 3 2 4
1
1
5
1 3 5 4 2
3
3 2 1```

### 输出

```
3 1 4 2
1
-1
2 3 1```

# AI分析结果

### 题目内容
# Polycarp恢复排列

## 题目描述
Polycarp在白板上写了一个长度为 $n$ 的数组 $p$，它是从 $1$ 到 $n$ 的数字的一个排列。换句话说，在 $p$ 中，从 $1$ 到 $n$ 的每个数字都恰好出现一次。

他还准备了一个结果数组 $a$，最初它是空的（即长度为 $0$）。

之后，他恰好进行了 $n$ 步操作。每一步操作如下：
- 查看 $p$ 的最左边和最右边的元素，选取两者中较小的那个。
- 如果你选取的是 $p$ 的最左边元素，将它添加到 $a$ 的左边；否则，如果你选取的是 $p$ 的最右边元素，将它添加到 $a$ 的右边。
- 选取的元素从 $p$ 中删除。

注意，在最后一步，$p$ 的长度为 $1$，它的最小元素既是最左边也是最右边的元素。在这种情况下，Polycarp 可以选择这个最小元素扮演的角色。换句话说，这个元素既可以添加到 $a$ 的左边，也可以添加到 $a$ 的右边（由 Polycarp 自行决定）。

让我们看一个例子。设 $n = 4$，$p = [3, 1, 4, 2]$。最初 $a = []$。然后：
- 在第一步，最小值在右边（值为 $2$），所以在这一步之后，$p = [3, 1, 4]$ 且 $a = [2]$（他将值 $2$ 添加到了右边）。
- 在第二步，最小值在左边（值为 $3$），所以在这一步之后，$p = [1, 4]$ 且 $a = [3, 2]$（他将值 $3$ 添加到了左边）。
- 在第三步，最小值在左边（值为 $1$），所以在这一步之后，$p = [4]$ 且 $a = [1, 3, 2]$（他将值 $1$ 添加到了左边）。
- 在第四步，最小值既是左边也是右边的元素（这个值是 $4$）。假设 Polycarp 选择了右边的选项。在这一步之后，$p = []$ 且 $a = [1, 3, 2, 4]$（他将值 $4$ 添加到了右边）。

因此，$n$ 步之后 $a$ 的一个可能值是 $a = [1, 3, 2, 4]$。

给定最终的结果数组 $a$。找出任何一个可能的初始值 $p$，使得它能得到给定的 $a$，或者确定不存在解。

## 说明/提示
示例中的第一个测试用例在问题陈述的主要部分有详细说明。对于这个测试集可能还有其他正确答案。

在第二个测试用例中，$n = 1$。因此，只有一个排列可以作为答案：$p = [1]$。实际上，这就是这个测试用例的答案。

在示例的第三个测试用例中，无论你将什么排列作为 $p$，在应用 $n$ 步操作后，结果都将与 $a = [1, 3, 5, 4, 2]$ 不同。

## 样例 #1
### 输入
```
4
4
1 3 2 4
1
1
5
1 3 5 4 2
3
3 2 1
```
### 输出
```
3 1 4 2
1
-1
2 3 1
```

### 算法分类
构造

### 综合分析与结论
所有题解的核心思路都是先判断无解情况，再构造有解时的答案。判断无解的依据都是由于每次操作取两端最小值，所以最终数组 $a$ 中最大值 $n$ 必定在首位或末位，否则无解。对于有解情况，多数题解发现将数组 $a$ 倒序输出就是一种可能的解；部分题解采用从数组 $a$ 两端取较大值反向模拟构造原数组 $p$ 的方式。各题解思路相似，主要差异在于代码实现方式与细节处理。

### 所选的题解
- **作者：szkzyc (5星)**
    - **关键亮点**：思路清晰简洁，先明确指出无解判断条件，再说明有解时直接倒序输出即可，代码量少且逻辑清晰。
    - **重点代码核心实现思想**：先读入数据，通过判断数组 $a$ 的首位和末位是否为 $n$ 来确定是否有解，有解则倒序输出数组 $a$。
    ```cpp
    int main(){
        int t;
        cin >> t;
        while(t--){
            int n;
            cin >> n;
            for(int i = 1; i <= n; i++) cin >> a[i];
            if(a[1]!= n && a[n]!= n) puts("-1");
            else{
                for(int i = n; i >= 1; i--) cout << a[i] << ' ';
            }
            cout << '\n';
        }
        return 0;
    }
    ```
- **作者：Texas_the_Omertosa (4星)**
    - **关键亮点**：思路阐述详细，将思路分为判断无解和输出可能解两部分，代码实现规范，使用了 `ios::sync_with_stdio(0);` 等优化输入输出。
    - **重点代码核心实现思想**：与szkzyc思路一致，先判断无解情况，再倒序输出数组 $a$ 作为可能解。
    ```cpp
    signed main()
    {
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        int t;
        cin>>t;
        for(int asdf=1;asdf<=t;asdf++)
        {
            int n;
            cin>>n;
            for(int i=1;i<=n;i++)
            {
                cin>>a[i];
            }
            if(a[n]!=n&&a[1]!=n)
            {
                cout<<"-1\n";
                continue;
            }
            for(int i=n;i>=1;i--)
            {
                cout<<a[i]<<' ';
            }
            cout<<'\n';
        }
        return 0;
    } 
    ```
- **作者：HPXXZYY (4星)**
    - **关键亮点**：对有解时倒序输出的原理进行了分析，即从与最大数相邻元素的位置关系进行推理，逻辑较严谨。
    - **重点代码核心实现思想**：先读入数据判断无解，有解则倒序输出数组 $a$。
    ```cpp
    int main(){
        for(int T=1,Q=read();T<=Q;T++){
            n=read();
            for(int i=1;i<=n;i++)
                a[i]=read();

            if (a[1]!=n&&a[n]!=n)
                printf("-1\n");
            else{
                for(int i=n;i>=1;i--)
                    printf("%d ",a[i]);
                printf("\n");
            }
        }
        return 0;
    }
    ```

### 最优关键思路或技巧
通过分析操作过程特点得出无解判断条件，即最终数组中最大值必须在两端。对于有解情况，巧妙利用操作性质，发现将结果数组倒序即为一种可能的原数组，简化了构造过程。

### 拓展
此类题目属于根据特定操作规则进行逆向构造的问题。类似套路是先深入分析正向操作的性质与规律，从而得出无解条件与有解时的构造方法。比如一些根据序列变换规则求原序列的题目，都可尝试从操作特点入手分析。

### 相似知识点洛谷题目
- [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)：通过模拟特定规则下元素的删除过程，与本题类似在于都需理解并遵循给定规则进行操作，只是本题是逆向构造。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：需要根据一定条件构造满足要求的数的组合，和本题一样考察构造能力，只是条件和构造方式不同。
- [P2672 推销员](https://www.luogu.com.cn/problem/P2672)：根据题目设定的收益计算规则，选择合适的路线，和本题类似在要依据特定规则进行分析与构造方案。 

---
处理用时：47.31秒