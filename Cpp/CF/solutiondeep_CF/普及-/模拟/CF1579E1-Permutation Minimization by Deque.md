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

### 题目中文重写
# 通过双端队列实现排列最小化

## 题目描述

实际上，问题 E1 和 E2 并没有太多共同之处。你应该将它们视为两个独立的问题。

给定一个长度为 $n$ 的排列 $p$。长度为 $n$ 的排列是一个长度为 $n$ 的数组，其中从 $1$ 到 $n$ 的每个整数恰好出现一次。例如，$ [1, 4, 3, 2] $ 和 $ [4, 2, 1, 3] $ 是正确的排列，而 $ [1, 2, 4] $ 和 $ [1, 2, 2] $ 不是。

让我们考虑一个空的[双端队列](https://tinyurl.com/pfeucbux)（deque）。双端队列是一种支持在开头和结尾添加元素的数据结构。因此，如果当前双端队列中有元素 $ [1, 5, 2] $，在开头添加元素 $ 4 $ 将产生序列 $ [\color{red}{4}, 1, 5, 2] $，在结尾添加相同元素将产生 $ [1, 5, 2, \color{red}{4}] $。

排列中的元素按顺序添加到初始为空的双端队列中，从 $ p_1 $ 开始，到 $ p_n $ 结束。在将每个元素添加到双端队列之前，你可以选择将其添加到开头还是结尾。

例如，如果我们考虑排列 $ p = [3, 1, 2, 4] $，一种可能的操作序列如下：
1. 将 $ 3 $ 添加到双端队列的末尾：双端队列中的序列为 $ [\color{red}{3}] $；
2. 将 $ 1 $ 添加到双端队列的开头：双端队列中的序列为 $ [\color{red}{1}, 3] $；
3. 将 $ 2 $ 添加到双端队列的末尾：双端队列中的序列为 $ [1, 3, \color{red}{2}] $；
4. 将 $ 4 $ 添加到双端队列的末尾：双端队列中的序列为 $ [1, 3, 2, \color{red}{4}] $；

找出处理完整个排列后，双端队列中字典序最小的元素序列。

如果存在 $ i \leq n $ 使得 $ x_1 = y_1 $，$ x_2 = y_2 $，$ \ldots $，$ x_{i - 1} = y_{i - 1} $ 且 $ x_i < y_i $，则序列 $ [x_1, x_2, \ldots, x_n] $ 的字典序小于序列 $ [y_1, y_2, \ldots, y_n] $。换句话说，如果序列 $ x $ 和 $ y $ 有一些（可能为空）匹配的前缀，并且序列 $ x $ 的下一个元素严格小于序列 $ y $ 的对应元素。例如，序列 $ [1, 3, 2, 4] $ 小于序列 $ [1, 3, 4, 2] $，因为在开头的两个匹配元素 $ [1, 3] $ 之后，第一个序列的元素 $ 2 $ 小于第二个序列的对应元素 $ 4 $。

## 说明/提示
从排列 $ [3, 1, 2, 4] $ 得到字典序最小的排列 $ [1, 3, 2, 4] $（第一个样例测试用例）的一种方法在问题描述中已有说明。

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
2 1
```
### 输出
```
1 3 2 4 
1 2 3 
1 3 2 
1 2 
1 2
```

### 综合分析与结论
- **思路对比**：大部分题解思路一致，采用贪心策略，通过比较待插入元素与队首元素的大小，决定将元素插入队首还是队尾，以保证最终队列的字典序最小。部分题解还提出了其他思路，如递归、使用小根堆、结构体排序、单调栈等。
- **算法要点**：核心是使用双端队列（`std::deque` 或 `std::list`）模拟元素插入过程。在插入元素时，若元素小于队首元素，则插入队首；否则插入队尾。
- **解决难点**：主要难点在于如何保证最终队列的字典序最小。通过贪心策略，每次插入时比较元素与队首元素大小，可有效解决该问题。同时，需要注意队列为空时的特殊处理，避免调用 `front()` 方法报错。

### 评分较高的题解
- **作者：kimidonatsu（5星）**
    - **关键亮点**：思路清晰，详细解释了双端队列的使用方法和字典序的判断逻辑，并给出了 `std::deque` 和 `std::list` 两种实现版本的代码，代码注释详细。
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
    - **关键亮点**：思路简洁明了，对贪心策略进行了证明，代码实现简洁，可读性高。
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
    - **关键亮点**：思路清晰，代码简洁，对代码逻辑进行了详细注释。
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
- **贪心策略**：每次插入元素时，比较元素与队首元素的大小，若元素小于队首元素，则插入队首；否则插入队尾，可保证最终队列的字典序最小。
- **双端队列的使用**：使用 `std::deque` 或 `std::list` 可以方便地实现元素的插入和删除操作，时间复杂度为常数级。

### 可拓展之处
- **同类型题**：类似的题目可能会改变排列的规则或双端队列的操作方式，但核心思路仍然是通过贪心策略和合适的数据结构来保证最终结果的最优性。
- **类似算法套路**：贪心算法在很多排序和选择问题中都有应用，通过局部最优选择来达到全局最优。在处理这类问题时，需要仔细分析问题的特点，找到合适的贪心策略。

### 推荐洛谷题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略和优先队列实现果子的合并，使总代价最小。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过贪心策略对排队顺序进行排序，使平均等待时间最短。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过贪心策略和排序算法，使皇后的工作时间最短。

### 个人心得摘录与总结
部分题解提到在队列为空时调用 `front()` 方法会报错，需要进行特判，这是在使用双端队列时需要注意的一个细节。在实际编程中，要充分考虑边界情况，避免因边界条件处理不当导致程序出错。

---
处理用时：43.78秒