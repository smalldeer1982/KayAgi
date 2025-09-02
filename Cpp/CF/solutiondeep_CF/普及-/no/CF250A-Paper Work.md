# 题目信息

# Paper Work

## 题目描述

Polycarpus has been working in the analytic department of the "F.R.A.U.D." company for as much as $ n $ days. Right now his task is to make a series of reports about the company's performance for the last $ n $ days. We know that the main information in a day report is value $ a_{i} $ , the company's profit on the $ i $ -th day. If $ a_{i} $ is negative, then the company suffered losses on the $ i $ -th day.

Polycarpus should sort the daily reports into folders. Each folder should include data on the company's performance for several consecutive days. Of course, the information on each of the $ n $ days should be exactly in one folder. Thus, Polycarpus puts information on the first few days in the first folder. The information on the several following days goes to the second folder, and so on.

It is known that the boss reads one daily report folder per day. If one folder has three or more reports for the days in which the company suffered losses $ (a_{i}&lt;0) $ , he loses his temper and his wrath is terrible.

Therefore, Polycarpus wants to prepare the folders so that none of them contains information on three or more days with the loss, and the number of folders is minimal.

Write a program that, given sequence $ a_{i} $ , will print the minimum number of folders.

## 说明/提示

Here goes a way to sort the reports from the first sample into three folders:

 1 2 3 -4 -5 | -6 5 -5 | -6 -7 6In the second sample you can put all five reports in one folder.

## 样例 #1

### 输入

```
11
1 2 3 -4 -5 -6 5 -5 -6 -7 6
```

### 输出

```
3
5 3 3 ```

## 样例 #2

### 输入

```
5
0 -1 100 -1 0
```

### 输出

```
1
5 ```

# AI分析结果

### 题目内容
# 文案工作

## 题目描述
Polycarpus已经在“F.R.A.U.D.”公司的分析部门工作了 $n$ 天。现在，他的任务是制作一系列关于公司过去 $n$ 天业绩的报告。我们知道，每日报告中的主要信息是值 $a_{i}$，即公司在第 $i$ 天的利润。如果 $a_{i}$ 为负数，则表示公司在第 $i$ 天遭受了损失。

Polycarpus需要将每日报告整理到文件夹中。每个文件夹应包含公司连续几天的业绩数据。当然，这 $n$ 天中的每一天的信息都应恰好放在一个文件夹中。因此，Polycarpus将前几天的信息放在第一个文件夹中。接下来几天的信息放在第二个文件夹中，依此类推。

已知老板每天会查看一个每日报告文件夹。如果一个文件夹中有三天或更多天公司遭受损失（$a_{i}<0$），他就会发脾气，而且脾气非常可怕。

因此，Polycarpus希望整理文件夹，使得没有一个文件夹包含关于三天或更多天损失的信息，并且文件夹的数量最少。

编写一个程序，给定序列 $a_{i}$，输出最少的文件夹数量。

## 说明/提示
以下是将第一个示例中的报告整理到三个文件夹的方法：
1 2 3 -4 -5 | -6 5 -5 | -6 -7 6
在第二个示例中，你可以将所有五个报告放在一个文件夹中。

## 样例 #1
### 输入
```
11
1 2 3 -4 -5 -6 5 -5 -6 -7 6
```
### 输出
```
3
5 3 3 
```

## 样例 #2
### 输入
```
5
0 -1 100 -1 0
```
### 输出
```
1
5 
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是基于贪心策略，即尽可能让每个文件夹中包含的负数接近但不超过2个，以达到文件夹数量最少的目的。算法要点在于遍历序列，统计负数个数，当负数个数达到3时，就将前面的数划分到一个文件夹，并重置负数计数。解决难点在于理解题意中对文件夹内负数数量的限制以及如何通过合理划分来满足最小化文件夹数量的要求。各题解思路基本一致，主要差异在于代码实现的细节和方式。

### 所选的题解
- **作者：帝千秋丶梦尘 (5星)**
  - **关键亮点**：思路清晰，代码简洁明了，直接通过计数负数个数，当达到3个负数时重新计数并划分文件夹。
  - **重点代码核心思想**：遍历输入数据，若为负数则负数计数加1，当负数计数达到3时，记录当前文件夹的长度并重置文件夹长度和负数计数。
  ```cpp
  for(ri int i(1);i<=n;++i)
  {
      cin>>x;
      ans++;
      if(x<0) sum++;
      if(sum==3)
      {
          a[++temp]=ans-1;
          ans=1;
          sum=1;
      }
  }
  ```
- **作者：Eason_AC (4星)**
  - **关键亮点**：代码简洁高效，利用前缀和数组记录每个文件夹的长度，逻辑清晰。
  - **重点代码核心思想**：遍历输入数据，若为负数则负数计数加1，当负数计数超过2时，增加文件夹数量并调整负数计数，同时更新前缀和数组记录文件夹长度。
  ```cpp
  for(int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]);
      if(a[i] < 0)	neg++;
      if(neg > 2) {
          ++s[0];
          neg -= 2;
      }
      s[s[0]]++;
  }
  ```
- **作者：nanatsuhi (4星)**
  - **关键亮点**：通过前缀和数组记录每个文件夹的结束位置，巧妙地计算出每个文件夹的长度，思路清晰。
  - **重点代码核心思想**：遍历输入数据，若为负数则负数计数加1，当负数计数达到3时，记录当前位置减1作为当前文件夹结束位置，重置负数计数，最后通过前缀和数组差值得到每个文件夹长度。
  ```cpp
  for(int i=1;i<=n;i++)
  {
      scanf("%d",&x);
      if(x<0) k++;
      if(k==3) as[cnt++]=i-1,k=1;
  }
  as[cnt]=n;
  printf("%d\n",cnt);
  for(int i=1;i<=cnt;i++)
      printf("%d ",as[i]-as[i-1]);
  ```

### 最优关键思路或技巧
采用贪心策略，在遍历序列时实时统计负数个数，一旦负数个数达到3，就进行文件夹划分，这样能保证每个文件夹中的负数尽可能多但不超过限制，从而实现文件夹数量最少。同时，利用数组记录文件夹的相关信息（如长度等），方便后续输出。

### 同类型题或类似算法套路拓展
此类题目通常围绕资源分配或分组问题，在满足一定条件下求最优解。类似套路是明确限制条件和优化目标，采用贪心策略，在每一步决策中选择当前最优的方案，逐步构建出整体最优解。

### 洛谷相似题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：同样是分组问题，需要根据给定条件对物品进行分组以满足特定要求。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及到策略选择和资源分配，通过合理的贪心策略来获取最优结果。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据时间限制和任务分配的条件，运用贪心思想找到最优的排队方案。

### 个人心得摘录与总结
部分作者提到容易误解题意，比如未注意到文件夹内数据需连续。这提醒在解题时要仔细审题，明确题目隐藏条件。同时，在调试过程中要全面考虑各种边界情况和特殊输入，避免因理解偏差导致错误。 

---
处理用时：53.84秒