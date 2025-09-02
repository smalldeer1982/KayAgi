# 题目信息

# Permutation Minimization by Deque

## 题目描述

In fact, the problems E1 and E2 do not have much in common. You should probably think of them as two separate problems.

A permutation $ p $ of size $ n $ is given. A permutation of size $ n $ is an array of size $ n $ in which each integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1, 4, 3, 2] $ and $ [4, 2, 1, 3] $ are correct permutations while $ [1, 2, 4] $ and $ [1, 2, 2] $ are not.

Let us consider an empty [deque](https://tinyurl.com/pfeucbux) (double-ended queue). A deque is a data structure that supports adding elements to both the beginning and the end. So, if there are elements $ [1, 5, 2] $ currently in the deque, adding an element $ 4 $ to the beginning will produce the sequence $ [\color{red}{4}, 1, 5, 2] $ , and adding same element to the end will produce $ [1, 5, 2, \color{red}{4}] $ .

The elements of the permutation are sequentially added to the initially empty deque, starting with $ p_1 $ and finishing with $ p_n $ . Before adding each element to the deque, you may choose whether to add it to the beginning or the end.

For example, if we consider a permutation $ p = [3, 1, 2, 4] $ , one of the possible sequences of actions looks like this:

 $ \quad $ 1.add $ 3 $ to the end of the deque:deque has a sequence $ [\color{red}{3}] $ in it; $ \quad $ 2.add $ 1 $ to the beginning of the deque:deque has a sequence $ [\color{red}{1}, 3] $ in it; $ \quad $ 3.add $ 2 $ to the end of the deque:deque has a sequence $ [1, 3, \color{red}{2}] $ in it; $ \quad $ 4.add $ 4 $ to the end of the deque:deque has a sequence $ [1, 3, 2, \color{red}{4}] $ in it;Find the lexicographically smallest possible sequence of elements in the deque after the entire permutation has been processed.

A sequence $ [x_1, x_2, \ldots, x_n] $ is lexicographically smaller than the sequence $ [y_1, y_2, \ldots, y_n] $ if there exists such $ i \leq n $ that $ x_1 = y_1 $ , $ x_2 = y_2 $ , $ \ldots $ , $ x_{i - 1} = y_{i - 1} $ and $ x_i < y_i $ . In other words, if the sequences $ x $ and $ y $ have some (possibly empty) matching prefix, and the next element of the sequence $ x $ is strictly smaller than the corresponding element of the sequence $ y $ . For example, the sequence $ [1, 3, 2, 4] $ is smaller than the sequence $ [1, 3, 4, 2] $ because after the two matching elements $ [1, 3] $ in the start the first sequence has an element $ 2 $ which is smaller than the corresponding element $ 4 $ in the second sequence.

## 说明/提示

One of the ways to get a lexicographically smallest permutation $ [1, 3, 2, 4] $ from the permutation $ [3, 1, 2, 4] $ (the first sample test case) is described in the problem statement.

## 样例 #1

### 输入

```
5
4
3 1 2 4
3
3 2 1
3
3 1 2
2
1 2
2
2 1```

### 输出

```
1 3 2 4 
1 2 3 
1 3 2 
1 2 
1 2```

# AI分析结果

### 题目翻译
## 用双端队列实现排列最小化

### 题目描述
实际上，问题E1和E2并没有太多共同之处。你应该把它们看作两个独立的问题。

给定一个长度为 $ n $ 的排列 $ p $。长度为 $ n $ 的排列是一个长度为 $ n $ 的数组，其中从 $ 1 $ 到 $ n $ 的每个整数恰好出现一次。例如，$ [1, 4, 3, 2] $ 和 $ [4, 2, 1, 3] $ 是正确的排列，而 $ [1, 2, 4] $ 和 $ [1, 2, 2] $ 不是。

让我们考虑一个空的[双端队列](https://tinyurl.com/pfeucbux)。双端队列是一种支持在两端添加元素的数据结构。因此，如果当前双端队列中有元素 $ [1, 5, 2] $，在开头添加元素 $ 4 $ 将得到序列 $ [\color{red}{4}, 1, 5, 2] $，在末尾添加相同元素将得到 $ [1, 5, 2, \color{red}{4}] $。

排列中的元素按顺序添加到初始为空的双端队列中，从 $ p_1 $ 开始，到 $ p_n $ 结束。在将每个元素添加到双端队列之前，你可以选择将其添加到开头还是结尾。

例如，如果我们考虑排列 $ p = [3, 1, 2, 4] $，一种可能的操作序列如下：
1. 将 $ 3 $ 添加到双端队列的末尾：双端队列中的序列为 $ [\color{red}{3}] $；
2. 将 $ 1 $ 添加到双端队列的开头：双端队列中的序列为 $ [\color{red}{1}, 3] $；
3. 将 $ 2 $ 添加到双端队列的末尾：双端队列中的序列为 $ [1, 3, \color{red}{2}] $；
4. 将 $ 4 $ 添加到双端队列的末尾：双端队列中的序列为 $ [1, 3, 2, \color{red}{4}] $；

找出处理完整个排列后，双端队列中字典序最小的元素序列。

如果存在 $ i \leq n $ 使得 $ x_1 = y_1 $，$ x_2 = y_2 $，$ \ldots $，$ x_{i - 1} = y_{i - 1} $ 且 $ x_i < y_i $，则序列 $ [x_1, x_2, \ldots, x_n] $ 的字典序小于序列 $ [y_1, y_2, \ldots, y_n] $。换句话说，如果序列 $ x $ 和 $ y $ 有一些（可能为空）匹配的前缀，并且序列 $ x $ 的下一个元素严格小于序列 $ y $ 的对应元素。例如，序列 $ [1, 3, 2, 4] $ 小于序列 $ [1, 3, 4, 2] $，因为在开头的两个匹配元素 $ [1, 3] $ 之后，第一个序列的元素 $ 2 $ 小于第二个序列的对应元素 $ 4 $。

### 说明/提示
问题描述中描述了一种从排列 $ [3, 1, 2, 4] $（第一个样例测试用例）得到字典序最小排列 $ [1, 3, 2, 4] $ 的方法。

### 样例 #1
#### 输入
```
5
4
3 1 2 4
3
3 2 1
3
3 1 2
2
1 2
2
2 1
```
#### 输出
```
1 3 2 4 
1 2 3 
1 3 2 
1 2 
1 2
```

### 综合分析与结论
- **思路**：多数题解采用贪心策略，核心思路是将元素依次加入双端队列时，若元素小于队首元素，则将其插入队首；若大于队首元素，则插入队尾，以此保证最终队列的字典序最小。
- **算法要点**：使用双端队列（如 `std::deque` 或 `std::list`）模拟元素插入过程，通过比较元素与队首元素大小决定插入位置。
- **解决难点**：主要难点在于理解如何保证字典序最小，通过贪心策略，每次插入时做出最优选择，避免了复杂的搜索过程。

### 高评分题解
- **作者：kimidonatsu（5星）**
    - **关键亮点**：思路清晰，详细解释了双端队列的使用方法和操作复杂度，还给出了 `std::deque` 和 `std::list` 两种实现版本，代码注释详细。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, x;
deque< int > q;
int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            if (i == 1) q.push_front(x);
            else if (x > q.front()) q.push_back(x);
            else q.push_front(x);
        }
        while (!q.empty()) {
            cout << q.front() << " ";
            q.pop_front();
        }
        cout << endl;
    }
    return 0;
}
```
- **作者：Jerrlee✅（4星）**
    - **关键亮点**：对贪心策略进行了证明，思路明确，代码简洁易懂，还提供了AC记录。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,a;
        cin>>n;
        deque<int>d;
        for(int i=0;i<n;i++){
            cin>>a;
            if(i==0||a<d[0]) d.push_front(a); 
            else d.push_back(a);
        }
        for(int x:d) cout<<x<<" ";
        cout<<endl;
    }
}
```
- **作者：yimuhua（4星）**
    - **关键亮点**：思路清晰，代码简洁，注释明确，采用贪心策略解决问题。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, x;
deque<int> dq;
int main() {
    cin >> t;
    while(t--) {
        cin >> n >> x;
        dq.push_back(x);
        for(int i = 1; i < n; i++) {
            cin >> x;
            if(x > dq.front())
                dq.push_back(x);
            else
                dq.push_front(x);
        }
        while(!dq.empty())
            cout << dq.front() << ' ', dq.pop_front();
        cout << endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
- **数据结构**：使用双端队列 `std::deque` 或 `std::list` 来模拟元素的插入操作，支持在队列两端高效插入元素。
- **算法优化**：采用贪心策略，每次插入元素时根据与队首元素的大小关系做出最优选择，避免了枚举所有可能的插入顺序，时间复杂度为 $O(n)$。
- **思维方式**：通过分析字典序的特点，将问题转化为每次插入时的局部最优选择，从而得到全局最优解。

### 拓展思路
同类型题目可能会改变排列的规则、双端队列的操作限制或增加其他条件。类似算法套路包括贪心算法在其他数据结构（如栈、堆）上的应用，以及对字典序、排列组合等概念的进一步考察。

### 洛谷相似题目推荐
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的使用。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：涉及贪心策略和排序的应用。
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：使用贪心算法解决区间覆盖问题。

### 个人心得摘录与总结
- **kimidonatsu**：提到在队列为空时调用 `front()` 会报错，所以第一次推送时加了特判，提醒注意边界情况。
总结：在使用数据结构的方法时，要注意边界条件，避免因边界情况导致程序出错。 

---
处理用时：43.21秒