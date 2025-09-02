# 题目信息

# Contest for Robots

## 题目描述

Polycarp is preparing the first programming contest for robots. There are $ n $ problems in it, and a lot of robots are going to participate in it. Each robot solving the problem $ i $ gets $ p_i $ points, and the score of each robot in the competition is calculated as the sum of $ p_i $ over all problems $ i $ solved by it. For each problem, $ p_i $ is an integer not less than $ 1 $ .

Two corporations specializing in problem-solving robot manufacturing, "Robo-Coder Inc." and "BionicSolver Industries", are going to register two robots (one for each corporation) for participation as well. Polycarp knows the advantages and flaws of robots produced by these companies, so, for each problem, he knows precisely whether each robot will solve it during the competition. Knowing this, he can try predicting the results — or manipulating them.

For some reason (which absolutely cannot involve bribing), Polycarp wants the "Robo-Coder Inc." robot to outperform the "BionicSolver Industries" robot in the competition. Polycarp wants to set the values of $ p_i $ in such a way that the "Robo-Coder Inc." robot gets strictly more points than the "BionicSolver Industries" robot. However, if the values of $ p_i $ will be large, it may look very suspicious — so Polycarp wants to minimize the maximum value of $ p_i $ over all problems. Can you help Polycarp to determine the minimum possible upper bound on the number of points given for solving the problems?

## 说明/提示

In the first example, one of the valid score assignments is $ p = [3, 1, 3, 1, 1] $ . Then the "Robo-Coder" gets $ 7 $ points, the "BionicSolver" — $ 6 $ points.

In the second example, both robots get $ 0 $ points, and the score distribution does not matter.

In the third example, both robots solve all problems, so their points are equal.

## 样例 #1

### 输入

```
5
1 1 1 0 0
0 1 1 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
0 0 0
0 0 0```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 1 1 1
1 1 1 1```

### 输出

```
-1```

## 样例 #4

### 输入

```
9
1 0 0 0 0 0 0 0 1
0 1 1 0 1 1 1 1 0```

### 输出

```
4```

# AI分析结果

### 题目内容
#### 机器人竞赛
1. **题目描述**：Polycarp正在筹备首届机器人编程竞赛。竞赛中有$n$道题，许多机器人将参赛。解决第$i$题的机器人将获得$p_i$分，每个机器人在竞赛中的得分是其解决的所有题目$p_i$的总和。对于每道题，$p_i$是一个不小于$1$的整数。
有两家专门制造解题机器人的公司，“Robo - Coder Inc.”和“BionicSolver Industries”，它们也将各注册一个机器人参赛。Polycarp了解这些公司生产的机器人的优缺点，因此对于每道题，他确切知道每个机器人在竞赛中是否会解决该题。基于此，他可以尝试预测结果 —— 或者操纵结果。
出于某种原因（绝对不涉及贿赂），Polycarp希望“Robo - Coder Inc.”的机器人在竞赛中胜过“BionicSolver Industries”的机器人。Polycarp希望设置$p_i$的值，使得“Robo - Coder Inc.”的机器人获得的分数严格多于“BionicSolver Industries”的机器人。然而，如果$p_i$的值过大，可能会显得非常可疑 —— 所以Polycarp希望最小化所有题目中$p_i$的最大值。你能帮助Polycarp确定解决这些题目所给分数的最小可能上限吗？
2. **说明/提示**：
    - 在第一个示例中，一种有效的分数分配是$p = [3, 1, 3, 1, 1]$。此时，“Robo - Coder”得$7$分，“BionicSolver”得$6$分。
    - 在第二个示例中，两个机器人都得$0$分，分数分配无关紧要。
    - 在第三个示例中，两个机器人解决所有题目，所以它们的分数相等。
3. **样例 #1**：
    - **输入**：
```
5
1 1 1 0 0
0 1 1 1 1
```
    - **输出**：
```
3
```
4. **样例 #2**：
    - **输入**：
```
3
0 0 0
0 0 0
```
    - **输出**：
```
-1
```
5. **样例 #3**：
    - **输入**：
```
4
1 1 1 1
1 1 1 1
```
    - **输出**：
```
-1
```
6. **样例 #4**：
    - **输入**：
```
9
1 0 0 0 0 0 0 0 1
0 1 1 0 1 1 1 1 0
```
    - **输出**：
```
4
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解思路核心一致，均利用贪心策略。先明确两个机器人都答对或都答错的题目对结果无影响，仅关注一个机器人答对而另一个答错的题目。统计“Robo - Coder Inc.”机器人独对题目数量$cnt1$和“BionicSolver Industries”机器人独对题目数量$cnt2$。若$cnt1$为$0$，则“Robo - Coder Inc.”机器人无法获胜，输出$-1$；否则，为使“Robo - Coder Inc.”机器人获胜且$p_i$最大值最小，将$cnt2$个“BionicSolver Industries”机器人独对题目分值设为$1$，计算出使“Robo - Coder Inc.”机器人总分超过对手所需给其独对题目分配的分值（$cnt2 / cnt1 + 1$ ，这里除法为整数除法）。各题解在表述、代码风格及细节处理上有差异，但本质算法相同。

### 所选的题解
- **作者：do_while_true (5星)**
    - **关键亮点**：思路阐述清晰，从题目分析到代码实现，逐步讲解，对关键步骤如为何只考虑部分题目、如何分配分数等解释详细，代码简洁明了。
    - **重点代码核心实现思想**：通过循环统计两个机器人独对题目的数量，根据$cnt1$是否为$0$判断是否有解，若有解则输出$cnt2 / cnt1 + 1$。
```cpp
#include<iostream>
using namespace std;
int n,a[101],b[101],cnt1,cnt2;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	   scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
	   scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		if(a[i]&&(!b[i])) cnt1++;
		if(b[i]&&(!a[i])) cnt2++;
	}
	if(cnt1==0) puts("-1");
	else printf("%d\n",cnt2/cnt1+1);
    return 0;
}
```
- **作者：Aehnuwx (4星)**
    - **关键亮点**：表述简洁，直接点明统计不同情况的次数，并利用向上取整公式$\lceil \dfrac{b + 1}{c} \rceil$ 得出结果，对公式的正确性解释清晰。
    - **重点代码核心实现思想**：与其他题解类似，统计第一队赢、输和平局次数，根据条件判断输出结果，核心在于计算$\lceil \dfrac{b + 1}{c} \rceil$ ，这里通过判断循环条件实现类似向上取整效果。
```cpp
// 伪代码示意核心实现
// 假设已统计出赢的次数c，输的次数b
int o = 1;
while(o * c <= b) {
    o++;
}
cout << o; 
```
- **作者：formkiller (4星)**
    - **关键亮点**：对解题思路的分析详细，从不同类型题目对结果的影响，到如何让第二台机器总分最小化从而使第一台机器得分均摊下来分值较小，逐步推导得出答案，代码规范且有注释。
    - **重点代码核心实现思想**：通过循环统计两类题目数量$A$和$B$，根据$A$是否为$0$判断输出结果，若$A$不为$0$则输出$B / A + 1$。
```cpp
int main()
{
	read(N);
	for (int i = 1; i <= N; ++i) read(a[i]);
	for (int i = 1; i <= N; ++i) read(b[i]);
	for (int i = 1; i <= N; ++i)
	{
		if (a[i]&&!b[i]) ++A;
		if (!a[i]&&b[i]) ++B;
	}
	if (A==0) cout << -1 << endl;
	else	  cout << B/A+1 << endl;
    return 0;
}
```

### 最优关键思路或技巧
1. **思维方式**：快速抓住问题核心，意识到两个机器人都答对或答错的题目不影响最终结果，从而简化问题，只关注一个机器人答对而另一个答错的题目，这是解决本题的关键思维突破点。
2. **贪心策略**：将“BionicSolver Industries”机器人独对题目分值设为最小的$1$，以保证在满足“Robo - Coder Inc.”机器人获胜的条件下，使题目分值最大值最小，体现了贪心算法的应用。

### 拓展
1. **同类型题或类似算法套路**：此类题目通常涉及在一定条件下通过合理分配资源（本题为题目分值）来达到某个最优目标（本题为使某个机器人获胜且分值最大值最小）。类似套路是先分析哪些因素对目标无影响从而简化问题，再利用贪心思想，从局部最优选择（如本题给部分题目设最小分值）来达到全局最优。
2. **洛谷题目推荐**：
    - **P1094 [NOIP2007 普及组] 纪念品分组**：同样是贪心策略的应用，根据给定条件对物品进行分组，使分组数量最少。
    - **P1223 排队接水**：通过对数据的分析，利用贪心策略安排接水顺序，使所有人等待的总时间最短。
    - **P1199 [NOIP2010 普及组] 三国游戏**：在游戏场景下，运用贪心思想选择最优策略，以获得最大得分。 

---
处理用时：80.15秒