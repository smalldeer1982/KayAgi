# 题目信息

# Hongcow's Game

## 题目描述

This is an interactive problem. In the interaction section below you will see the information about flushing the output.

In this problem, you will be playing a game with Hongcow. How lucky of you!

Hongcow has a hidden $ n $ by $ n $ matrix $ M $ . Let $ M_{i,j} $ denote the entry $ i $ -th row and $ j $ -th column of the matrix. The rows and columns are labeled from $ 1 $ to $ n $ .

The matrix entries are between $ 0 $ and $ 10^{9} $ . In addition, $ M_{i,i}=0 $ for all valid $ i $ . Your task is to find the minimum value along each row, excluding diagonal elements. Formally, for each $ i $ , you must find ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF744B/60abf7e287a9efbab7664bfef9cac9ebdb2e6b1f.png).

To do this, you can ask Hongcow some questions.

A question consists of giving Hongcow a subset of distinct indices $ {w_{1},w_{2},...,w_{k}} $ , with $ 1<=k<=n $ . Hongcow will respond with $ n $ integers. The $ i $ -th integer will contain the minimum value of $ min_{1<=j<=k}M_{i,wj} $ .

You may only ask Hongcow at most $ 20 $ questions — he thinks you only need that many questions answered.

When you are ready to answer, print out a single integer $ -1 $ on its own line, then $ n $ integers on the next line. The $ i $ -th integer should be the minimum value in the $ i $ -th row of the matrix, excluding the $ i $ -th element. Do not forget to flush the final answer as well. Printing the answer does not count as asking a question.

You will get Wrong Answer verdict if

- Your question or answers are not in the format described in this statement.
- You ask strictly more than $ 20 $ questions.
- Your question contains duplicate indices.
- The value of $ k $ in your question does not lie in the range from $ 1 $ to $ n $ , inclusive.
- Your final answer is not correct.

 You will get Idleness Limit Exceeded if you don't print anything or if you forget to flush the output, including for the final answer (more info about flushing output below).

## 说明/提示

In the first sample, Hongcow has the hidden matrix

`<br></br>[<br></br> [0, 3, 2],<br></br> [5, 0, 7],<br></br> [4, 8 ,0],<br></br>]<br></br>`Here is a more readable version demonstrating the interaction. The column on the left represents Hongcow, while the column on the right represents the contestant.

`<br></br>3<br></br>              3<br></br>              1 2 3<br></br>0 0 0<br></br>              1<br></br>              3<br></br>2 7 0<br></br>              2<br></br>              1 2<br></br>0 0 4<br></br>              1<br></br>              2<br></br>3 0 8<br></br>              1<br></br>              1<br></br>0 5 4<br></br>              -1<br></br>              2 5 4<br></br>`For the second sample, it is possible for off-diagonal elements of the matrix to be zero.

## 样例 #1

### 输入

```
3
0 0 0
2 7 0
0 0 4
3 0 8
0 5 4```

### 输出

```
3
1 2 3
1
3
2
1 2
1
2
1
1
-1
2 5 4
```

## 样例 #2

### 输入

```
2
0 0
0 0```

### 输出

```
1
2
1
1
-1
0 0```

# AI分析结果

### 题目内容
#### Hongcow的游戏
这是一道交互式题目。在下面的交互部分，你会看到关于刷新输出的信息。

在这个问题中，你将与Hongcow玩一个游戏。你真幸运！

Hongcow有一个隐藏的 $n \times n$ 矩阵 $M$。设 $M_{i,j}$ 表示矩阵第 $i$ 行第 $j$ 列的元素。行和列的编号从 $1$ 到 $n$。

矩阵元素在 $0$ 到 $10^{9}$ 之间。此外，对于所有有效的 $i$，$M_{i,i}=0$。你的任务是找到每行中除对角元素外的最小值。形式上，对于每个 $i$，你必须找到 $\min_{j \neq i} M_{i,j}$。

为了做到这一点，你可以向Hongcow提出一些问题。

一个问题包括给Hongcow一个不同索引的子集 $\{w_{1},w_{2},\cdots,w_{k}\}$，其中 $1\leq k\leq n$。Hongcow会回应 $n$ 个整数。第 $i$ 个整数将包含 $\min_{1\leq j\leq k}M_{i,wj}$ 的最小值。

你最多只能向Hongcow问 $20$ 个问题 —— 他认为你只需要回答这么多问题。

当你准备好回答时，在单独的一行上打印一个整数 $-1$，然后在下一行打印 $n$ 个整数。第 $i$ 个整数应该是矩阵第 $i$ 行中除第 $i$ 个元素之外的最小值。也不要忘记刷新最终答案。打印答案不算提问。

如果出现以下情况，你将得到Wrong Answer的判定：
- 你的问题或答案不符合本声明中描述的格式。
- 你提问的数量严格超过 $20$ 个。
- 你的问题包含重复的索引。
- 你问题中的 $k$ 值不在 $1$ 到 $n$（含）的范围内。
- 你的最终答案不正确。

如果你什么都不打印，或者忘记刷新输出，包括最终答案（下面有关于刷新输出的更多信息），你将得到Idleness Limit Exceeded。

#### 说明/提示
在第一个样例中，Hongcow有一个隐藏矩阵：
\[
\begin{bmatrix}
0 & 3 & 2 \\
5 & 0 & 7 \\
4 & 8 & 0
\end{bmatrix}
\]
这里有一个更易读的版本展示交互过程。左边一列代表Hongcow，右边一列代表参赛者。
\[
\begin{array}{c|c}
\text{Hongcow} & \text{参赛者} \\
\hline
3 & 3 \\
 & 1\ 2\ 3 \\
0\ 0\ 0 & \\
 & 1 \\
 & 3 \\
2\ 7\ 0 & \\
 & 2 \\
 & 1\ 2 \\
0\ 0\ 4 & \\
 & 1 \\
 & 2 \\
3\ 0\ 8 & \\
 & 1 \\
 & 1 \\
0\ 5\ 4 & \\
 & -1 \\
 & 2\ 5\ 4
\end{array}
\]
对于第二个样例，矩阵的非对角元素有可能为零。

#### 样例 #1
**输入**
```
3
0 0 0
2 7 0
0 0 4
3 0 8
0 5 4
```
**输出**
```
3
1 2 3
1
3
2
1 2
1
2
1
1
-1
2 5 4
```
#### 样例 #2
**输入**
```
2
0 0
0 0
```
**输出**
```
1
2
1
1
-1
0 0
```

### 算法分类
位运算

### 综合分析与结论
这三道题解思路一致，均采用二进制拆分的方法。由于矩阵对角线上元素为0，会干扰每行非对角线最小值的判断，所以要保证每个非对角线元素都至少在一次询问中，不与它所在行对角线上的元素同时出现。利用二进制的特性，任意一个非对角线元素与其所在行对角线元素的列号，至少有一个二进制位不同，通过枚举每个二进制位，分别询问在该二进制位上是0或1的列号，从而得到有效询问结果，更新每行的最小值。

### 所选的题解
- **作者：suxxsfe (5星)**
    - **关键亮点**：思路清晰，代码简洁高效，详细解释了二进制思路的原理，且代码注释较为完善。
    - **重点代码**：
```cpp
int main(){
    int n=read();
    std::memset(a,0x3f,sizeof a);
    for(reg int cnt,i=0;i<10;i++){// 枚举二进制位
        cnt=0;
        for(reg int j=1;j<=n;j++)if(j&(1<<i)) cnt++;
        if(!cnt) goto NEXT;
        printf("%d\n",cnt);
        for(reg int j=1;j<=n;j++)if(j&(1<<i)) printf("%d ",j);EN;
        std::fflush(stdout);
        for(reg int j=1;j<=n;j++){
            cnt=read();
            if(j&(1<<i)) continue;
            a[j]=std::min(a[j],cnt);
        }
        NEXT:;
        cnt=0;
        for(reg int j=1;j<=n;j++)if(!(j&(1<<i))) cnt++;
        if(!cnt) continue;
        printf("%d\n",cnt);
        for(reg int j=1;j<=n;j++)if(!(j&(1<<i))) printf("%d ",j);EN;
        std::fflush(stdout);
        for(reg int j=1;j<=n;j++){
            cnt=read();
            if(!(j&(1<<i))) continue;
            a[j]=std::min(a[j],cnt);
        }
    }
    puts("-1");
    for(reg int i=1;i<=n;i++) printf("%d ",a[i]);
    std::fflush(stdout);
    return 0;
}
```
    - **核心实现思想**：通过枚举二进制位，构造询问集合，根据询问结果更新每行的最小值，最后输出结果。
- **作者：封禁用户 (4星)**
    - **关键亮点**：先简述题意和解题思路，使读者更易理解，代码逻辑清晰，利用函数计算二进制位数，增强代码可读性。
    - **重点代码**：
```cpp
int main()
{
    cin >> n;
    for(int i = 1 ; i <= n ; i++)
    {
        a[i] = 1000000007;
    }
    for(int i = 0 ; i < ds(n) ; i++){// 枚举二进制位
        cnt = 0;
        for(int j = 1 ; j <= n ; j++)
        {
            if(j & (1 << i))
            {
                cnt++;
            }
        }
        if(cnt)
        {
            cout << cnt << endl;
            for(int j = 1 ; j <= n ; j++)
            {
                if(j & (1 << i))
                {
                    cout << j << ' ';
                }
                cout << endl;
            }
            for(int j = 1 ; j <= n ; j++)
            {
                cin >> cnt;
                if(j & (1 << i))
                {
                    continue;
                }
                a[j] = min(a[j], cnt);
            }   
        }
        cnt = 0;
        for(int j = 1 ; j <= n ; j++)
        {
            if(!(j & (1 << i)))
            {
                cnt++;
            }
        }
        if(!cnt)
        {
            continue;
        }
        cout << cnt << endl;
        for(int j = 1 ; j <= n ; j++)
        {
            if(!(j & (1 << i)))
            {
                cout << j << ' '; 
            }
            cout << endl;
        }
        for(int j = 1 ; j <= n ; j++)
        {
            cin >> cnt;
            if(!(j & (1 << i)))
            {
                continue;
            }
            a[j] = std::min(a[j], cnt);
        }
    }
    cout << "-1" << endl;
    for(int i = 1 ; i <= n ; i++)
    {
        cout << a[i] << ' ';
    }
    cout << endl;
    return 0;
}
```
    - **核心实现思想**：与上一题解类似，通过枚举二进制位构造询问，更新每行最小值并输出。
- **作者：hongshixiaobai (4星)**
    - **关键亮点**：简洁明了地阐述了二进制拆分的解题思路，代码风格简洁，变量命名直观。
    - **重点代码**：
```cpp
int main()
{
    memset(ans,0x3f,sizeof(ans));
    cin>>n;
    for(i = 0;i<=19;i++){// 枚举二进制位
        cnt = 0;
        for(j = 1;j<=n;j++)
            if(j&(1<<i))
                qry[++cnt] = j;
        if(!cnt)continue;
        cout<<cnt<<endl;
        for(j = 1;j<=cnt;j++)
            cout<<qry[j]<<' ';
        cout<<endl;
        for(j = 1;j<=n;j++)
        {
            cin>>tmp;
            if(j&(1<<i))continue;
            ans[j] = min(ans[j],tmp);
        }
        cnt = 0;
        for(j = 1;j<=n;j++)
            if(!(j&(1<<i)))
                qry[++cnt] = j;
        if(!cnt)continue;
        cout<<cnt<<endl;
        for(j = 1;j<=cnt;j++)
            cout<<qry[j]<<' ';
        cout<<endl;
        for(j = 1;j<=n;j++)
        {
            cin>>tmp;
            if(!(j&(1<<i)))continue;
            ans[j] = min(ans[j],tmp);
        }
    }
    cout<<-1<<endl;
    for(i = 1;i<=n;i++)cout<<ans[i]<<' ';
    cout<<endl;
}
```
    - **核心实现思想**：同样是利用二进制位构造询问，更新每行最小值并输出最终结果。

### 最优关键思路或技巧
利用二进制位的特性，通过枚举二进制位来构造询问集合，巧妙避免对角线上元素（值为0）对每行非对角线最小值判断的干扰，高效解决问题。

### 拓展
同类型题或类似算法套路：这种利用二进制位特性解决问题的方法，在一些涉及到元素分组、状态表示等问题中较为常见。例如在一些图论问题中，用二进制表示点的状态，通过位运算进行状态转移或分组操作。

### 推荐题目
- [P1876 开灯](https://www.luogu.com.cn/problem/P1876)：通过位运算模拟开关灯的操作，考察对二进制的理解和运用。
- [P1514 引水入城](https://www.luogu.com.cn/problem/P1514)：需要利用位运算优化状态表示，解决复杂的地图水流问题。
- [P3164 [CQOI2014]和谐矩阵](https://www.luogu.com.cn/problem/P3164)：通过位运算对矩阵状态进行处理和判断，与本题利用二进制特性解决矩阵相关问题思路类似。

### 个人心得
无。

---
处理用时：95.82秒