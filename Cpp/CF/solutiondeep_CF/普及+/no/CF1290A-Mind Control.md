# 题目信息

# Mind Control

## 题目描述

You and your $ n - 1 $ friends have found an array of integers $ a_1, a_2, \dots, a_n $ . You have decided to share it in the following way: All $ n $ of you stand in a line in a particular order. Each minute, the person at the front of the line chooses either the first or the last element of the array, removes it, and keeps it for himself. He then gets out of line, and the next person in line continues the process.

You are standing in the $ m $ -th position in the line. Before the process starts, you may choose up to $ k $ different people in the line, and persuade them to always take either the first or the last element in the array on their turn (for each person his own choice, not necessarily equal for all people), no matter what the elements themselves are. Once the process starts, you cannot persuade any more people, and you cannot change the choices for the people you already persuaded.

Suppose that you're doing your choices optimally. What is the greatest integer $ x $ such that, no matter what are the choices of the friends you didn't choose to control, the element you will take from the array will be greater than or equal to $ x $ ?

Please note that the friends you don't control may do their choice arbitrarily, and they will not necessarily take the biggest element available.

## 说明/提示

In the first test case, an optimal strategy is to force the first person to take the last element and the second person to take the first element.

- the first person will take the last element ( $ 5 $ ) because he or she was forced by you to take the last element. After this turn the remaining array will be $ [2, 9, 2, 3, 8] $ ;
- the second person will take the first element ( $ 2 $ ) because he or she was forced by you to take the first element. After this turn the remaining array will be $ [9, 2, 3, 8] $ ;
- if the third person will choose to take the first element ( $ 9 $ ), at your turn the remaining array will be $ [2, 3, 8] $ and you will take $ 8 $ (the last element);
- if the third person will choose to take the last element ( $ 8 $ ), at your turn the remaining array will be $ [9, 2, 3] $ and you will take $ 9 $ (the first element).

Thus, this strategy guarantees to end up with at least $ 8 $ . We can prove that there is no strategy that guarantees to end up with at least $ 9 $ . Hence, the answer is $ 8 $ .

In the second test case, an optimal strategy is to force the first person to take the first element. Then, in the worst case, both the second and the third person will take the first element: you will end up with $ 4 $ .

## 样例 #1

### 输入

```
4
6 4 2
2 9 2 3 8 5
4 4 1
2 13 60 4
4 1 3
1 2 2 1
2 2 0
1 2```

### 输出

```
8
4
1
1```

# AI分析结果

### 题目翻译
## 心灵控制

### 题目描述
你和 $n - 1$ 个朋友发现了一个整数数组 $a_1, a_2, \dots, a_n$。你们决定按以下方式分享这个数组：你们 $n$ 个人按特定顺序排成一队。每分钟，队首的人可以选择数组的第一个或最后一个元素，将其移除并据为己有。然后他离开队伍，下一个人继续这个过程。

你站在队伍的第 $m$ 个位置。在过程开始前，你可以选择最多 $k$ 个不同的人，并说服他们在轮到自己时总是选择数组的第一个或最后一个元素（对每个人来说是各自的选择，不一定对所有人都相同），无论元素本身是什么。一旦过程开始，你就不能再说服其他人，也不能改变你已经说服的人的选择。

假设你做出了最优选择，那么最大的整数 $x$ 是多少，使得无论你没有选择控制的朋友如何选择，你从数组中选取的元素都大于或等于 $x$？

请注意，你没有控制的朋友可以任意选择，他们不一定会选择最大的可用元素。

### 说明/提示
在第一个测试用例中，一个最优策略是强迫第一个人选择最后一个元素，第二个人选择第一个元素。
- 第一个人会选择最后一个元素（$5$），因为他或她被你强迫选择最后一个元素。这次操作后，剩余的数组将是 $[2, 9, 2, 3, 8]$；
- 第二个人会选择第一个元素（$2$），因为他或她被你强迫选择第一个元素。这次操作后，剩余的数组将是 $[9, 2, 3, 8]$；
- 如果第三个人选择第一个元素（$9$），轮到你时，剩余的数组将是 $[2, 3, 8]$，你将选择 $8$（最后一个元素）；
- 如果第三个人选择最后一个元素（$8$），轮到你时，剩余的数组将是 $[9, 2, 3]$，你将选择 $9$（第一个元素）。

因此，这个策略保证最终得到至少 $8$。我们可以证明，没有策略能保证最终得到至少 $9$。因此，答案是 $8$。

在第二个测试用例中，一个最优策略是强迫第一个人选择第一个元素。然后，在最坏的情况下，第二个人和第三个人都会选择第一个元素：你最终会得到 $4$。

### 样例 #1
#### 输入
```
4
6 4 2
2 9 2 3 8 5
4 4 1
2 13 60 4
4 1 3
1 2 2 1
2 2 0
1 2
```
#### 输出
```
8
4
1
1
```

### 算法分类
枚举

### 综合分析与结论
这些题解主要围绕如何在给定条件下求出最优选择下所能取到的最小的数的最大值。多数题解采用枚举的方法，通过枚举能控制的操作中选第一位的个数和不能控制的操作中选第一位的个数来计算结果。部分题解在此基础上使用单调队列或二分法进行优化，降低时间复杂度。

### 所选题解
- 乐哥（4星）
  - 关键亮点：思路清晰，先给出朴素的枚举解法，再用单调队列进行优化，详细解释了优化的思路和过程，代码注释丰富。
  - 个人心得：无
- Theophania（4星）
  - 关键亮点：对题意理解准确，详细分析了问题的特点，如不需要考虑排在自己后面的人、轮到自己时的情况只和之前在队首和队尾取的人数有关等，然后用单调队列优化，代码规范。
  - 个人心得：无

### 重点代码
#### 乐哥 - 枚举解法
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=3505;
int n,m,k,a[M];
int main()
{
    int t; scanf("%d",&t);
    while(t--)
    {
    	scanf("%d%d%d",&n,&m,&k);
    	k=min(k,m-1); 
    	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    	int ans=0;
    	for(int i=0;i<=k;i++) 
    	{
    		int s=1e9;
    		for(int j=0;j<=m-k-1;j++) 
    			s=min(s,max(a[i+j+1],a[n+i-m+j+1]));
    		ans=max(ans,s);
		}
		printf("%d\n",ans);
	}
    return 0;
}
```
核心实现思想：先将 $k$ 取为 $\min(k, m - 1)$，因为第 $m$ 次之后的操作与答案无关。然后枚举能控制的 $k$ 次操作中选第一位的个数 $i$ 和不能控制的操作中选第一位的个数 $j$，计算出每次情况下第 $m$ 次操作能取得数的最大值，取这些最大值中的最小值，再在所有最小值中取最大值作为最终答案。

#### 乐哥 - 单调队列优化解法
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=350005;
int n,m,k,a[M],b[M];
int main()
{
    int t; scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        k=min(k,m-1); 
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=m;i++) b[i]=max(a[i],a[i+n-m]); 
		deque<int> q; 
		for(int y=0;y<=m-k-1;y++) 
		{
			while(q.size()&&b[y+1]<b[q.back()]) q.pop_back(); 
			q.push_back(y+1);
		}
		int ans=b[q.front()];
        for(int x=1;x<=k;x++) 
        {
            while(q.size()&&q.front()<x+1) q.pop_front(); 
			while(q.size()&&b[x+m-k]<b[q.back()]) q.pop_back(); 
			q.push_back(x+m-k); 
			ans=max(ans,b[q.front()]); 
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
核心实现思想：先预处理出 $b$ 数组，$b[i] = \max(a[i], a[i + n - m])$。然后用单调队列维护 $x = 0$ 时的情况，之后 $x$ 变化时，通过单调队列的操作删去过期元素、维护队列单调性并加入新元素，更新答案。

### 可拓展之处
同类型题可能会改变数组的操作规则，或者增加控制条件等。类似算法套路可以是在有多种选择且要考虑最坏情况的问题中，先通过枚举找出所有可能情况，再用单调队列、二分等方法进行优化。

### 洛谷推荐题目
1. P1886 滑动窗口 /【模板】单调队列
2. P2672 [NOIP2015 普及组] 推销员
3. P3808 [模板] AC 自动机（简单版）

---
处理用时：56.79秒