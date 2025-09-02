# 题目信息

# Sum in Binary Tree

## 题目描述

Vanya really likes math. One day when he was solving another math problem, he came up with an interesting tree. This tree is built as follows.

Initially, the tree has only one vertex with the number $ 1 $ — the root of the tree. Then, Vanya adds two children to it, assigning them consecutive numbers — $ 2 $ and $ 3 $ , respectively. After that, he will add children to the vertices in increasing order of their numbers, starting from $ 2 $ , assigning their children the minimum unused indices. As a result, Vanya will have an infinite tree with the root in the vertex $ 1 $ , where each vertex will have exactly two children, and the vertex numbers will be arranged sequentially by layers.

 ![](https://espresso.codeforces.com/3fe851b2505ce276dabd4a63ad7472346f98f9a8.png) Part of Vanya's tree.Vanya wondered what the sum of the vertex numbers on the path from the vertex with number $ 1 $ to the vertex with number $ n $ in such a tree is equal to. Since Vanya doesn't like counting, he asked you to help him find this sum.

## 说明/提示

In the first test case of example on the path from the root to the vertex $ 3 $ there are two vertices $ 1 $ and $ 3 $ , their sum equals $ 4 $ .

In the second test case of example on the path from the root to the vertex with number $ 10 $ there are vertices $ 1 $ , $ 2 $ , $ 5 $ , $ 10 $ , sum of their numbers equals $ 1+2+5+10 = 18 $ .

## 样例 #1

### 输入

```
6
3
10
37
1
10000000000000000
15```

### 输出

```
4
18
71
1
19999999999999980
26```

# AI分析结果

### 中文重写题目内容
# 二叉树中的求和

## 题目描述
万尼亚非常喜欢数学。有一天，当他在解决另一个数学问题时，他想出了一棵有趣的树。这棵树的构建方式如下：

最初，树只有一个编号为 $1$ 的顶点，即树的根节点。然后，万尼亚为它添加两个子节点，并分别给它们分配连续的编号 $2$ 和 $3$。之后，他将按照节点编号从小到大的顺序为节点添加子节点，并给它们的子节点分配最小的未使用索引。结果，万尼亚将得到一棵以顶点 $1$ 为根的无限树，其中每个顶点都恰好有两个子节点，并且顶点编号将按层依次排列。

![万尼亚树的一部分](https://espresso.codeforces.com/3fe851b2505ce276dabd4a63ad7472346f98f9a8.png)

万尼亚想知道，在这样的树中，从编号为 $1$ 的顶点到编号为 $n$ 的顶点的路径上的顶点编号之和是多少。由于万尼亚不喜欢计算，他请你帮他找到这个和。

## 说明/提示
在示例的第一个测试用例中，从根节点到顶点 $3$ 的路径上有两个顶点 $1$ 和 $3$，它们的和等于 $4$。

在示例的第二个测试用例中，从根节点到编号为 $10$ 的顶点的路径上有顶点 $1$、$2$、$5$、$10$，它们的编号之和等于 $1 + 2 + 5 + 10 = 18$。

## 样例 #1
### 输入
```
6
3
10
37
1
10000000000000000
15
```

### 输出
```
4
18
71
1
19999999999999980
26
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用完全二叉树的性质，即编号为 $x$ 的节点的父节点编号为 $\lfloor\frac{x}{2}\rfloor$，从编号为 $n$ 的节点开始，不断向上遍历到根节点（编号为 $1$），并累加路径上节点的编号。

各题解的算法要点都是通过循环或递归的方式实现节点的向上遍历和编号求和，解决的难点在于理解完全二叉树节点编号的规律并正确实现遍历过程。

### 题解评分与选择
- **_O_v_O_ 的题解（4星）**：
    - 关键亮点：思路清晰，代码注释详细，明确指出因数据原因要开 `long long`，代码可读性高。
- **Dream__Sky 的题解（4星）**：
    - 关键亮点：通过具体例子模拟节点遍历过程，有助于理解，代码简洁易懂。
- **ran_qwq 的题解（3星）**：
    - 关键亮点：代码简洁，但缺乏必要注释，可读性相对较差。
- **rainygame 的题解（3星）**：
    - 关键亮点：使用递归的方式解决问题，但没有给出具体代码实现。

选择的题解：
- **_O_v_O_ 的题解（4星）**：思路清晰，代码注释详细。
- **Dream__Sky 的题解（4星）**：通过具体例子辅助理解，代码简洁。

### 重点代码
#### _O_v_O_ 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long  //因数据原因，要开long long
int t;
signed main(){
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int ans=0;   //开始往上遍历，ans代表路径上的结点编号和。
        while(n>=1){   //遍历到根节点后暂停。
            ans+=n;
            n/=2;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：通过 `while` 循环从编号为 $n$ 的节点开始，不断将当前节点编号累加到 `ans` 中，并将节点编号更新为其父节点编号（$n/2$），直到遍历到根节点（$n = 1$）。

#### Dream__Sky 的题解
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,n; 
signed main()
{
    cin>>T;//T组数据
    while(T--)
    {
        cin>>n;
        int sum=0;
        while(n)
        {
            sum+=n;
            n/=2;
        }//模拟除以二的过程，直到到了根节点，即n=1
        cout<<sum<<endl;
    }
    return 0;
}
```
核心实现思想：同样使用 `while` 循环，从编号为 $n$ 的节点开始，将当前节点编号累加到 `sum` 中，并将节点编号更新为其父节点编号（$n/2$），直到遍历到根节点（$n = 0$）。

### 最优关键思路或技巧
利用完全二叉树节点编号的规律，即编号为 $x$ 的节点的父节点编号为 $\lfloor\frac{x}{2}\rfloor$，通过循环或递归的方式从目标节点向上遍历到根节点，累加路径上节点的编号。

### 可拓展之处
同类型题或类似算法套路：
- 计算完全二叉树中某一层节点的编号之和。
- 计算完全二叉树中两个节点之间路径上节点的编号之和。

### 推荐洛谷题目
- [P1087 FBI树](https://www.luogu.com.cn/problem/P1087)
- [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)
- [P1553 数字反转（升级版）](https://www.luogu.com.cn/problem/P1553)

### 个人心得
这些题解中没有包含个人心得（调试经历、踩坑教训、顿悟感想等）。

---
处理用时：34.42秒