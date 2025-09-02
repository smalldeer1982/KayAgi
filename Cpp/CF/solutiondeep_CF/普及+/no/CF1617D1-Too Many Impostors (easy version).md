# 题目信息

# Too Many Impostors (easy version)

## 题目描述

This is an interactive problem. The only difference between the easy and hard version is the limit on number of questions.

There are $ n $ players labelled from $ 1 $ to $ n $ . It is guaranteed that $ n $ is a multiple of $ 3 $ .

Among them, there are $ k $ impostors and $ n-k $ crewmates. The number of impostors, $ k $ , is not given to you. It is guaranteed that $ \frac{n}{3} < k < \frac{2n}{3} $ .

In each question, you can choose three distinct integers $ a $ , $ b $ , $ c $ ( $ 1 \le a, b, c \le n $ ) and ask: "Among the players labelled $ a $ , $ b $ and $ c $ , are there more impostors or more crewmates?" You will be given the integer $ 0 $ if there are more impostors than crewmates, and $ 1 $ otherwise.

Find the number of impostors $ k $ and the indices of players that are impostors after asking at most $ 2n $ questions.

The jury is adaptive, which means the indices of impostors may not be fixed beforehand and can depend on your questions. It is guaranteed that there is at least one set of impostors which fulfills the constraints and the answers to your questions at any time.

## 说明/提示

Explanation for example interaction (note that this example only exists to demonstrate the interaction procedure and does not provide any hint for the solution):

For the first test case:

Question "? 1 2 3" returns $ 0 $ , so there are more impostors than crewmates among players $ 1 $ , $ 2 $ and $ 3 $ .

Question "? 3 4 5" returns $ 1 $ , so there are more crewmates than impostors among players $ 3 $ , $ 4 $ and $ 5 $ .

Outputting "! 3 4 1 2" means that one has found all the impostors, by some miracle. There are $ k = 3 $ impostors. The players who are impostors are players $ 4 $ , $ 1 $ and $ 2 $ .

For the second test case:

Question "? 7 1 9" returns $ 1 $ , so there are more crewmates than impostors among players $ 7 $ , $ 1 $ and $ 9 $ .

Outputting "! 4 2 3 6 8" means that one has found all the impostors, by some miracle. There are $ k = 4 $ impostors. The players who are impostors are players $ 2 $ , $ 3 $ , $ 6 $ and $ 8 $ .

## 样例 #1

### 输入

```
2
6

0

1

9

1```

### 输出

```
? 1 2 3

? 3 4 5

! 3 4 1 2

? 7 1 9

! 4 2 3 6 8```

# AI分析结果

### 题目内容（中文重写）
# 太多冒名顶替者（简单版本）

## 题目描述
这是一道交互式题目。简单版本和困难版本的唯一区别在于询问次数的限制。

有 $n$ 名玩家，编号从 $1$ 到 $n$。保证 $n$ 是 $3$ 的倍数。

其中有 $k$ 名冒名顶替者和 $n - k$ 名船员。冒名顶替者的数量 $k$ 不会告诉你。保证 $\frac{n}{3} < k < \frac{2n}{3}$。

在每次询问中，你可以选择三个不同的整数 $a$、$b$、$c$（$1 \leq a, b, c \leq n$）并询问：“在编号为 $a$、$b$ 和 $c$ 的玩家中，是冒名顶替者多还是船员多？” 如果你得到整数 $0$，表示冒名顶替者比船员多；如果得到整数 $1$，则表示船员比冒名顶替者多。

在最多进行 $2n$ 次询问后，找出冒名顶替者的数量 $k$ 和冒名顶替者的编号。

评测程序是自适应的，这意味着冒名顶替者的编号可能事先没有确定，并且可能取决于你的询问。保证在任何时候都至少有一组冒名顶替者满足约束条件和对你的询问的回答。

## 说明/提示
示例交互的解释（请注意，此示例仅用于演示交互过程，不提供任何解题提示）：

对于第一个测试用例：
询问 “? 1 2 3” 返回 $0$，所以在玩家 $1$、$2$ 和 $3$ 中，冒名顶替者比船员多。
询问 “? 3 4 5” 返回 $1$，所以在玩家 $3$、$4$ 和 $5$ 中，船员比冒名顶替者多。
输出 “! 3 4 1 2” 意味着某人奇迹般地找到了所有冒名顶替者。有 $k = 3$ 名冒名顶替者。冒名顶替者是玩家 $4$、$1$ 和 $2$。

对于第二个测试用例：
询问 “? 7 1 9” 返回 $1$，所以在玩家 $7$、$1$ 和 $9$ 中，船员比冒名顶替者多。
输出 “! 4 2 3 6 8” 意味着某人奇迹般地找到了所有冒名顶替者。有 $k = 4$ 名冒名顶替者。冒名顶替者是玩家 $2$、$3$、$6$ 和 $8$。

## 样例 #1

### 输入
```
2
6

0

1

9

1
```

### 输出
```
? 1 2 3

? 3 4 5

! 3 4 1 2

? 7 1 9

! 4 2 3 6 8
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是利用题目中冒名顶替者数量的范围限制（$\frac{n}{3} < k < \frac{2n}{3}$），通过对每三个相邻的人进行询问，找到两组答案不同的询问，从而确定两个身份不同的人（一个冒名顶替者和一个船员）。然后利用这两个人，通过询问确定其余所有人的身份。

#### 思路对比
- 所有题解都采用了先找身份不同的两人，再利用这两人确定其他人身份的思路。
- 部分题解在确定身份不同的两人时，选择的是相邻两组询问中位置重叠的两人（如 $i + 1$ 和 $i + 2$），而有些题解选择的是相邻两组询问中位置不重叠的两人（如 $i$ 和 $i + 3$）。

#### 算法要点
1. **寻找身份不同的两人**：对每三个相邻的人进行询问，由于冒名顶替者数量的限制，必然存在两组答案不同的询问。
2. **确定其余人的身份**：利用找到的两个身份不同的人，与其余人进行询问，根据询问结果确定其余人的身份。

#### 解决难点
- **找到身份不同的两人**：通过对相邻三人的询问结果进行比较，找到答案不同的两组询问。
- **确定最终的身份**：在确定其余人的身份后，还需要通过额外的询问确定之前找到的两个身份不同的人的具体身份。

### 所选题解
- **作者：Tyyyyyy (赞：5)，4星**
  - **关键亮点**：思路清晰，代码结构简洁，注释较少但不影响理解，按照核心思路逐步实现，易于学习。
- **作者：123zbk (赞：1)，4星**
  - **关键亮点**：代码逻辑清晰，变量命名规范，对核心思路的实现较为直观，便于理解。
- **作者：Priestess_SLG (赞：0)，4星**
  - **关键亮点**：使用 `vector` 存储结果，代码风格现代，逻辑清晰，实现了核心思路。

### 重点代码
以作者 Tyyyyyy 的代码为例，核心实现思想是先对每三个相邻的人进行询问，找到答案不同的两组询问，确定两个身份不同的人，然后利用这两个人确定其余人的身份，最后确定这两个人的身份。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[10010];
int ans[10010],cnt;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        // 对每三个相邻的人进行询问
        for(int i=1;i<=n-2;i++)
        {
            printf("? %d %d %d\n",i,i+1,i+2);
            fflush(stdout);
            scanf("%d",&a[i]);
        }
        int x,y,xx,yy;
        // 找到答案不同的两组询问，确定两个身份不同的人
        for(int i=1;i<n-2;i++)
            if(a[i]!=a[i+1]){x=i+1,y=i+2;break;}
        int rec;cnt=0;
        // 利用这两个人确定其余人的身份
        for(int i=1;i<=n;i++)
        {
            if(i==x||i==y)continue;
            printf("? %d %d %d\n",x,y,i);
            fflush(stdout);
            scanf("%d",&rec);
            if(rec==0)ans[++cnt]=i,xx=i;
            else yy=i;
        }
        // 确定这两个人的身份
        printf("? %d %d %d\n",xx,yy,x);
        fflush(stdout);
        scanf("%d",&rec);
        if(rec==0)ans[++cnt]=x;
        printf("? %d %d %d\n",xx,yy,y);
        fflush(stdout);
        scanf("%d",&rec);
        if(rec==0)ans[++cnt]=y;
        // 输出结果
        printf("! %d ",cnt);
        for(int i=1;i<=cnt;i++)printf("%d ",ans[i]);
        puts("");
        fflush(stdout);
    }
    return 0;
}
```

### 可拓展之处
同类型题或类似算法套路：
- 其他交互式题目，通过有限的询问次数来确定某些信息。
- 利用已知条件进行构造，通过逐步确定部分信息来得到整体信息的题目。

### 洛谷题目推荐
1. P1160 队列安排
2. P1996 约瑟夫问题
3. P2058 海港

### 个人心得
题解中均未包含个人心得。

---
处理用时：46.97秒