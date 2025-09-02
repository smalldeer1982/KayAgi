# 题目信息

# Minimize Permutation Subarrays

## 题目描述

You are given a permutation $ p $ of size $ n $ . You want to minimize the number of subarrays of $ p $ that are permutations. In order to do so, you must perform the following operation exactly once:

- Select integers $ i $ , $ j $ , where $ 1 \le i, j \le n $ , then
- Swap $ p_i $ and $ p_j $ .

For example, if $ p = [5, 1, 4, 2, 3] $ and we choose $ i = 2 $ , $ j = 3 $ , the resulting array will be $ [5, 4, 1, 2, 3] $ . If instead we choose $ i = j = 5 $ , the resulting array will be $ [5, 1, 4, 2, 3] $ .

Which choice of $ i $ and $ j $ will minimize the number of subarrays that are permutations?

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

An array $ a $ is a subarray of an array $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

For the first test case, there are four possible arrays after the swap:

- If we swap $ p_1 $ and $ p_2 $ , we get the array $ [2, 1, 3] $ , which has 3 subarrays that are permutations ( $ [1] $ , $ [2, 1] $ , $ [2, 1, 3] $ ).
- If we swap $ p_1 $ and $ p_3 $ , we get the array $ [3, 2, 1] $ , which has 3 subarrays that are permutations ( $ [1] $ , $ [2, 1] $ , $ [3, 2, 1] $ ).
- If we swap $ p_2 $ and $ p_3 $ , we get the array $ [1, 3, 2] $ , which has 2 subarrays that are permutations ( $ [1] $ , $ [1, 3, 2] $ ).
- If we swap any element with itself, we get the array $ [1, 2, 3] $ , which has 3 subarrays that are permutations ( $ [1] $ , $ [1, 2] $ , $ [1, 2, 3] $ ).

 So the best swap to make is positions $ 2 $ and $ 3 $ .For the third sample case, after we swap elements at positions $ 2 $ and $ 5 $ , the resulting array is $ [1, 4, 2, 5, 3] $ . The only subarrays that are permutations are $ [1] $ and $ [1, 4, 2, 5, 3] $ . We can show that this is minimal.

## 样例 #1

### 输入

```
8
3
1 2 3
3
1 3 2
5
1 3 2 5 4
6
4 5 6 1 2 3
9
8 7 6 3 2 1 4 5 9
10
7 10 5 1 9 8 3 2 6 4
10
8 5 10 9 2 1 3 4 6 7
10
2 3 5 7 10 1 8 6 4 9```

### 输出

```
2 3
1 1
5 2
1 4
9 5
8 8
6 10
5 4```

# AI分析结果

### 题目内容（中文重写）
# 最小化排列子数组

## 题目描述
给定一个长度为 $n$ 的排列 $p$。你需要恰好执行一次以下操作，以最小化 $p$ 中是排列的子数组的数量：
- 选择整数 $i$ 和 $j$，其中 $1 \le i, j \le n$。
- 交换 $p_i$ 和 $p_j$。

例如，如果 $p = [5, 1, 4, 2, 3]$，且我们选择 $i = 2$，$j = 3$，则结果数组将是 $[5, 4, 1, 2, 3]$。如果我们选择 $i = j = 5$，则结果数组将是 $[5, 1, 4, 2, 3]$。

选择哪一对 $i$ 和 $j$ 可以最小化是排列的子数组的数量？

长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是一个排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是一个排列（$n = 3$ 但数组中有 $4$）。

如果数组 $a$ 可以通过从数组 $b$ 的开头删除若干（可能为零个或全部）元素以及从末尾删除若干（可能为零个或全部）元素得到，则数组 $a$ 是数组 $b$ 的子数组。

## 说明/提示
对于第一个测试用例，交换后有四种可能的数组：
- 如果我们交换 $p_1$ 和 $p_2$，得到数组 $[2, 1, 3]$，它有 3 个子数组是排列（$[1]$，$[2, 1]$，$[2, 1, 3]$）。
- 如果我们交换 $p_1$ 和 $p_3$，得到数组 $[3, 2, 1]$，它有 3 个子数组是排列（$[1]$，$[2, 1]$，$[3, 2, 1]$）。
- 如果我们交换 $p_2$ 和 $p_3$，得到数组 $[1, 3, 2]$，它有 2 个子数组是排列（$[1]$，$[1, 3, 2]$）。
- 如果我们将任何元素与其自身交换，得到数组 $[1, 2, 3]$，它有 3 个子数组是排列（$[1]$，$[1, 2]$，$[1, 2, 3]$）。

所以最佳的交换位置是 $2$ 和 $3$。对于第三个样例，在交换位置 $2$ 和 $5$ 的元素后，结果数组是 $[1, 4, 2, 5, 3]$。唯一是排列的子数组是 $[1]$ 和 $[1, 4, 2, 5, 3]$。我们可以证明这是最小的情况。

## 样例 #1
### 输入
```
8
3
1 2 3
3
1 3 2
5
1 3 2 5 4
6
4 5 6 1 2 3
9
8 7 6 3 2 1 4 5 9
10
7 10 5 1 9 8 3 2 6 4
10
8 5 10 9 2 1 3 4 6 7
10
2 3 5 7 10 1 8 6 4 9
```

### 输出
```
2 3
1 1
5 2
1 4
9 5
8 8
6 10
5 4
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路基本一致，都是通过分析排列的特性，发现要使排列子数组数量最少，需将最大数 $n$ 放在 $1$ 和 $2$ 之间。因为 $[1]$ 和原数组本身一定是排列，而其他排列通常会涉及 $2$，把最大数 $n$ 放在 $1$ 和 $2$ 之间，能让其他子数组难以构成排列。

各题解的算法要点在于先找出 $1$、$2$ 和 $n$ 在数组中的位置，然后根据它们的相对位置关系进行交换操作。主要难点在于准确判断这三个数的位置关系，并确定合适的交换方案。

### 所选题解
- **作者：ACtheQ (赞：5)，4星**
  - 关键亮点：思路清晰，代码简洁，通过简单的变量记录位置并进行判断输出。
  - 重点代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
    	int n;
    	cin>>n;
    	int x,y,z;
    	for(int i=1;i<=n;i++)
    	{
    		int k;
    		cin>>k;
    		if(k==1) x=i;
    		if(k==2) y=i;
    		if(k==n) z=i;
		}
		if(x>y) swap(x,y);
		if(z>y) cout<<y<<" "<<z<<endl;
		else if(z<x) cout<<z<<" "<<x<<endl;
		else cout<<x<<" "<<x<<endl;
	}
    return 0;
}
```
核心实现思想：先读取测试用例数量，对于每个测试用例，读取数组长度和数组元素，记录 $1$、$2$ 和 $n$ 的位置，然后根据它们的相对位置输出交换的位置。

- **作者：MrPython (赞：3)，4星**
  - 关键亮点：思路详细，对题意和解析都有清晰的阐述，代码使用了 `vector` 存储数组，通过三目运算符压行记录位置。
  - 重点代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n;
        cin>>n;
        vector<ui> a(n);
        size_t onepos,twopos,npos;
        for (size_t i=0;i<n;i++) 
            cin>>a[i],
            a[i]==1?onepos=i+1  //记录1, 2, n的位置，用三目压行
            :a[i]==2?twopos=i+1
            :a[i]==n?npos=i+1
            :0;
        if (onepos < twopos && twopos < npos) cout<<twopos<<' '<<npos;
        if (onepos < npos && npos < twopos)   cout<<1<<' '<<1;
        if (twopos < onepos && onepos < npos) cout<<onepos<<' '<<npos;
        if (twopos < npos && npos < onepos) cout<<1<<' '<<1;
        if (npos < onepos && onepos < twopos) cout<<onepos<<' '<<npos;
        if (npos < twopos && twopos < onepos) cout<<twopos<<' '<<npos;
        cout.put('\n');
    }
    return 0;
}
```
核心实现思想：先关闭输入输出流同步，提高效率。对于每个测试用例，读取数组长度和数组元素，用三目运算符记录 $1$、$2$ 和 $n$ 的位置，再根据它们的相对位置输出交换的位置。

- **作者：Kedit2007 (赞：2)，4星**
  - 关键亮点：思路明确，给出了伪代码参考，方便理解。
  - 重点代码（伪代码）：
```cpp
int n = read();
int pos1, pos2, posn;
for (int i = 1; i <= n; i++)
{
  int t = read();
  if (t == 1) pos1 = i;
  if (t == 2) pos2 = i;
  if (t == n) posn = i;
}

if (pos1 > pos2) swap(pos1, pos2); // 交换一下方便操作

if (posn > pos2) cout << pos2 << ' ' << posn; // 形如 2 1 n, 1 2 n
else if (posn < pos1) cout << posn << ' ' << pos1; // 形如 n 1 2, n 2 1
else cout << "1 1";
```
核心实现思想：读取数组长度和数组元素，记录 $1$、$2$ 和 $n$ 的位置，交换 $1$ 和 $2$ 的位置（如果 $1$ 的位置在 $2$ 之后），然后根据它们的相对位置输出交换的位置。

### 最优关键思路或技巧
- 思维方式：通过分析排列的特性，抓住 $1$、$2$ 和 $n$ 这三个关键数字，利用最大数 $n$ 来破坏其他可能形成排列的子数组。
- 代码实现技巧：使用简单的变量记录关键数字的位置，通过比较位置关系进行判断和输出，避免了复杂的数组操作。

### 可拓展之处
同类型题可能会改变排列的条件或操作方式，但核心思路仍然是分析关键元素对结果的影响，通过构造合适的排列来达到目标。类似算法套路可以应用于其他需要通过特定操作优化某个指标的问题，关键在于找出影响指标的关键因素并进行合理构造。

### 推荐洛谷题目
- [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)：涉及动态规划和构造最优路径。
- [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)：结合了动态规划和树的构造。
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：使用贪心算法构造最优合并方案。

### 个人心得摘录与总结
- **作者：xujingyu**：一开始想把 $1$ 和 $2$ 分开，但被样例 $1,3,2$ 否决；尝试把 $2$ 放到最右边，又被样例 $4,5,1,3,2$ 否决。最后发现把 $n$ 弄到 $1$ 和 $2$ 之间可以解决问题。总结：在解题时不能仅凭直觉，要多考虑不同的样例，通过不断尝试和调整来找到正确的思路。 

---
处理用时：63.05秒