# 题目信息

# Selection Sort

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041M/d5dc69f2c95d765850bbfc6e16bfc04c742abf70.png)Every student enrolled in the algorithms course is required to submit an assignment this week. The task is to implement an $ O(n^2) $ -time algorithm to sort $ n $ given integers in non-decreasing order. Alice has already completed her assignment, and her implementation is shown below.

```
<pre class="lstlisting">```
int alice_sort(int *s, int n){<br></br>  for(int i = 0; i < n; ++i){<br></br>    for(int j = i + 1; j < n; ++j){<br></br>      if(s[i] > s[j]){<br></br>        int swap = s[i];<br></br>        s[i] = s[j];<br></br>        s[j] = swap;<br></br>      }<br></br>    }<br></br>  }<br></br>  return 0;<br></br>}<br></br>
```
```

While you have access to Alice's code, you prefer not to simply copy it. Instead, you want to use Alice's sorting function as a building block for your own solution. There are two ways as listed below you can utilize her function, but each of them can be applied at most once. The order in which these two operations are invoked can be arbitrary.

- Prefix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s, i\texttt{)} $ . This sorts the first $ i $ elements in the array $ s $ .
- Suffix sort: choose a length $ i \in \{1, 2, \ldots, n\} $ and call $ \texttt{alicesort(}s+n-i, i\texttt{)} $ . This sorts the last $ i $ elements in the array $ s $ .

Due to the time complexity of the sorting algorithm, the cost of performing either a prefix or suffix sort is $ i^2 $ , where $ i $ is the length of the chosen subarray. Your goal is to determine the minimum cost to sort the input array $ s $ of $ n $ integers in non-decreasing order using Alice's function, following the rules mentioned above.

For example, Let $ s=[3,2,5,5,4,1] $ . We can first perform a suffix sort of length $ 4 $ , and the array becomes $ [3,2,1,4,5,5] $ . Then, we perform a prefix sort of length $ 3 $ , and the array becomes $ [1,2,3,4,5,5] $ , which is a sorted array. The cost is $ 4^2+3^2=25 $ . Here is another example, let $ s=[4,3,2,1] $ . We can complete the sorting by performing only a prefix sort of length $ 4 $ , and the cost is $ 4^2=16 $ .

## 样例 #1

### 输入

```
6
3 2 5 5 4 1```

### 输出

```
25```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
16```

# AI分析结果

### 题目内容
# 选择排序

## 题目描述
本周，每一位报名参加算法课程的学生都需要提交一份作业。任务是实现一个时间复杂度为$O(n^2)$的算法，将给定的$n$个整数按非递减顺序排序。爱丽丝已经完成了她的作业，她的实现如下：
```
int alice_sort(int *s, int n){
  for(int i = 0; i < n; ++i){
    for(int j = i + 1; j < n; ++j){
      if(s[i] > s[j]){
        int swap = s[i];
        s[i] = s[j];
        s[j] = swap;
      }
    }
  }
  return 0;
}
```
虽然你可以看到爱丽丝的代码，但你不想直接抄袭。相反，你想用爱丽丝的排序函数作为你自己解决方案的一个构建块。有以下两种使用她函数的方法，但每种方法最多只能应用一次。这两种操作的调用顺序可以是任意的。
- 前缀排序：选择一个长度$i \in \{1, 2, \ldots, n\}$，并调用$\texttt{alicesort(}s, i\texttt{)}$ 。这将对数组$s$的前$i$个元素进行排序。
- 后缀排序：选择一个长度$i \in \{1, 2, \ldots, n\}$，并调用$\texttt{alicesort(}s+n-i, i\texttt{)}$ 。这将对数组$s$的最后$i$个元素进行排序。
由于排序算法的时间复杂度，执行前缀排序或后缀排序的代价是$i^2$，其中$i$是所选子数组的长度。你的目标是确定按照上述规则，使用爱丽丝的函数将包含$n$个整数的输入数组$s$按非递减顺序排序的最小代价。
例如，设$s = [3, 2, 5, 5, 4, 1]$。我们可以首先对长度为$4$的后缀进行排序，数组变为$[3, 2, 1, 4, 5, 5]$。然后，我们对长度为$3$的前缀进行排序，数组变为$[1, 2, 3, 4, 5, 5]$，这就是一个已排序的数组。代价是$4^2 + 3^2 = 25$。再举一个例子，设$s = [4, 3, 2, 1]$。我们可以仅通过对长度为$4$的前缀进行排序来完成排序，代价是$4^2 = 16$。

## 样例 #1
### 输入
```
6
3 2 5 5 4 1
```
### 输出
```
25
```

## 样例 #2
### 输入
```
4
4 3 2 1
```
### 输出
```
16
```

### 综合分析与结论
三道题解均围绕如何利用前缀排序和后缀排序（每种操作限用一次）将给定数组排序并求最小代价展开。
 - **思路方面**：
    - **lfxxx**：按排序区间$[1,l],[r,n]$是否相交分类讨论，通过两个小根堆维护前缀中的数与排好序后的序列前缀中的数对消来计算关键值$k$，从而确定两次排序的范围。
    - **ccjjxx**：认为一定是一次前缀一次后缀排序（排序次数不大于2次），通过优先队列预处理找到前缀排序后第二次排序的起始位置，进而计算最小代价。
    - **沉石鱼惊旋**：枚举先排前缀还是先排后缀，将数组改成$[1,n]$的排列后，枚举前缀排序位置，通过维护值的连续段和小根堆来确定后缀排序位置，同时处理后缀无需排序和前缀扩展中不必要元素的情况。
 - **算法要点**：都利用优先队列或堆结构辅助确定排序范围，通过枚举不同排序情况计算最小代价。
 - **解决难点**：如何准确确定两次排序的范围使得代价最小，以及处理数组中的重复值。沉石鱼惊旋通过将数组转化为特定排列处理重复值，lfxxx和ccjjxx则通过堆结构在计算过程中处理重复值的影响。

三道题解整体质量相近，均未达到4星。

### 通用建议与扩展思路
 - **关键思路或技巧**：利用堆结构维护数据，通过枚举不同操作顺序和操作范围，结合贪心思想，找到最小代价的排序方式。处理重复值时，可以通过特殊的数据预处理（如转化为特定排列）或在计算过程中利用堆结构动态处理。
 - **拓展**：此类题目属于排序优化及贪心策略结合的类型，类似套路包括在有限操作次数下利用特定排序方式对序列进行优化，通常需要结合数据结构辅助确定操作范围和顺序。
 - **相似题目推荐**：
    - **P1094 [NOIP2007 普及组] 纪念品分组**：通过合理分组，运用贪心策略解决问题，与本题确定最小代价思路类似。
    - **P1199 [NOIP2010 普及组] 三国游戏**：涉及贪心和博弈策略，需分析不同操作顺序对结果的影响，和本题操作顺序及代价计算有相似性。
    - **P1223 排队接水**：利用贪心算法，根据不同数据特点确定最优顺序，与本题通过枚举确定最优排序操作有类似思维方式。 

---
处理用时：22.39秒