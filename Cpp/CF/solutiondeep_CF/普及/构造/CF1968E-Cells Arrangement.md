# 题目信息

# Cells Arrangement

## 题目描述

You are given an integer $ n $ . You choose $ n $ cells $ (x_1,y_1), (x_2,y_2),\dots,(x_n,y_n) $ in the grid $ n\times n $ where $ 1\le x_i\le n $ and $ 1\le y_i\le n $ .

Let $ \mathcal{H} $ be the set of distinct Manhattan distances between any pair of cells. Your task is to maximize the size of $ \mathcal{H} $ . Examples of sets and their construction are given in the notes.

If there exists more than one solution, you are allowed to output any.

Manhattan distance between cells $ (x_1,y_1) $ and $ (x_2,y_2) $ equals $ |x_1-x_2|+|y_1-y_2| $ .

## 说明/提示

In the first testcase we have $ n=2 $ . One of the possible arrangements is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/75dc943a7c64415a7537c95e5a0a8ab6f7bb8c40.png) The arrangement with cells located in $ (1,1) $ and $ (1,2) $ .  In this case $ \mathcal{H}=\{|1-1|+|1-1|,|1-1|+|2-2|,|1-1|+|1-2|\}=\{0,0,1\}=\{0,1\} $ . Hence, the size of $ \mathcal{H} $ is $ 2 $ . It can be shown that it is the greatest possible answer.In the second testcase we have $ n=3 $ . The optimal arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c33264fb4d38aae733c98659eb0f28334deed2c9.png) The arrangement with cells located in $ (2,1) $ , $ (2,3) $ and $ (3,1) $ . $ \mathcal{H} $ = $ \{|2-2|+|1-1|,|2-2|+|3-3|,|3-3|+|1-1|,|2-2|+|1-3|,|2-3|+|1-1|,|2-3|+|3-1|\} $ = $ \{0,0,0,2,1,3\} $ = $ \{0,1,2,3\} $ .

For $ n=4 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c8c88e231569a366e81dbe59dfe40f3bca88662e.png)For $ n=5 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/3a3f9b43e6fc8c9643d27a1bfc597d0efe1c8425.png)For $ n=6 $ a possible arrangement is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/b0bf5b17a4bc6da02c3ed5a2113cf7373a9e3ccc.png)

## 样例 #1

### 输入

```
5
2
3
4
5
6```

### 输出

```
1 1
1 2

2 1
2 3
3 1

1 1
1 3
4 3
4 4

1 1
1 3
1 4
2 1
5 5

1 4
1 5
1 6
5 2
5 5
6 1```

# AI分析结果

### 题目中文重写
# 单元格排列

## 题目描述
给定一个整数 $n$。你需要在 $n\times n$ 的网格中选择 $n$ 个单元格 $(x_1,y_1), (x_2,y_2),\dots,(x_n,y_n)$，其中 $1\le x_i\le n$ 且 $1\le y_i\le n$。

设 $\mathcal{H}$ 为任意两个单元格之间不同的曼哈顿距离的集合。你的任务是最大化 $\mathcal{H}$ 的大小。注释中给出了集合及其构造的示例。

如果存在多个解，你可以输出任意一个。

单元格 $(x_1,y_1)$ 和 $(x_2,y_2)$ 之间的曼哈顿距离等于 $|x_1 - x_2| + |y_1 - y_2|$。

## 说明/提示
在第一个测试用例中，$n = 2$。一种可能的排列如下：

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/75dc943a7c64415a7537c95e5a0a8ab6f7bb8c40.png) 单元格位于 $(1,1)$ 和 $(1,2)$ 的排列。在这种情况下，$\mathcal{H}=\{|1 - 1| + |1 - 1|,|1 - 1| + |2 - 2|,|1 - 1| + |1 - 2|\}=\{0,0,1\}=\{0,1\}$。因此，$\mathcal{H}$ 的大小为 $2$。可以证明这是最大可能的答案。

在第二个测试用例中，$n = 3$。最优排列如下：

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c33264fb4d38aae733c98659eb0f28334deed2c9.png) 单元格位于 $(2,1)$、$(2,3)$ 和 $(3,1)$ 的排列。$\mathcal{H} = \{|2 - 2| + |1 - 1|,|2 - 2| + |3 - 3|,|3 - 3| + |1 - 1|,|2 - 2| + |1 - 3|,|2 - 3| + |1 - 1|,|2 - 3| + |3 - 1|\} = \{0,0,0,2,1,3\} = \{0,1,2,3\}$。

对于 $n = 4$，一种可能的排列如下：

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/c8c88e231569a366e81dbe59dfe40f3bca88662e.png)

对于 $n = 5$，一种可能的排列如下：

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/3a3f9b43e6fc8c9643d27a1bfc597d0efe1c8425.png)

对于 $n = 6$，一种可能的排列如下：

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1968E/b0bf5b17a4bc6da02c3ed5a2113cf7373a9e3ccc.png)

## 样例 #1
### 输入
```
5
2
3
4
5
6
```
### 输出
```
1 1
1 2

2 1
2 3
3 1

1 1
1 3
4 3
4 4

1 1
1 3
1 4
2 1
5 5

1 4
1 5
1 6
5 2
5 5
6 1
```

### 综合分析与结论
- **思路对比**：大部分题解思路相近，先确定曼哈顿距离的最大值为 $2(n - 1)$，猜测 $\mathcal{H}$ 应包含 $0$ 到 $2(n - 1)$ 的所有值。然后通过尝试不同的点放置方式，如先放对角点，再调整其他点位置来构造满足条件的方案。部分题解通过手玩样例找规律，部分题解从理论上分析点之间距离的产生情况。
- **算法要点**：多数题解采用先放置 $(1, 1)$ 和 $(1, 2)$ 两点，再将剩余点依次放在对角线上（即 $(i, i)$，$i$ 从 $3$ 到 $n$）的构造方法。少数题解有不同的放置方式，但核心都是为了使不同曼哈顿距离的数量最大。
- **解决难点**：难点在于如何构造出能产生最多不同曼哈顿距离的点集。需要考虑如何产生奇数和偶数距离，避免距离重复。通过将对角线上的一个点调整位置（如将 $(2, 2)$ 移到 $(1, 2)$）来产生奇数距离是常见的解决方法。

### 题解评分
| 作者 | 评分 | 理由 |
| --- | --- | --- |
| JuRuoOIer | 5星 | 思路清晰，从找规律到构造方案再到证明正确性，步骤完整，代码可读性高。 |
| liuhongyang123 | 4星 | 简洁明了地指出关键思路，代码简洁。 |
| junee | 4星 | 准确分析出构造方案及距离产生情况，代码规范。 |

### 所选题解
- **JuRuoOIer（5星）**
    - **关键亮点**：详细展示找规律过程，对构造方案进行了严格证明，思路严谨。
    - **个人心得**：无
    - **核心代码**
```cpp
ll t,n;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        cout<<"1 1\n1 2\n";
        for(int i=3;i<=n;i++){
            cout<<i<<' '<<i<<endl;
        }
        cout<<endl;
    }
    return 0;
}
```
核心实现思想：先输出 $(1, 1)$ 和 $(1, 2)$ 两点，再通过循环输出对角线上从 $(3, 3)$ 到 $(n, n)$ 的点。

- **liuhongyang123（4星）**
    - **关键亮点**：思路简洁，直接点明问题关键，代码简洁易懂。
    - **个人心得**：无
    - **核心代码**
```cpp
int T,n;
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        cout<<"1 1"<<endl<<"1 2"<<endl;
        for(int i=3;i<=n;i++) cout<<i<<" "<<i<<endl;
        cout<<endl;
    }
    return 0;
} 
```
核心实现思想：与 JuRuoOIer 的代码类似，先输出前两个点，再输出对角线上的点。

- **junee（4星）**
    - **关键亮点**：对构造方案的距离产生情况分析清晰，代码规范。
    - **个人心得**：无
    - **核心代码**
```cpp
int T,n;
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        cout<<1<<' '<<1<<'\n'<<1<<' '<<2<<'\n';
        for(int i=3;i<=n;i++)cout<<i<<' '<<i<<'\n';
    }
    return 0;
}
```
核心实现思想：同样是先输出 $(1, 1)$ 和 $(1, 2)$，再输出对角线上的点。

### 最优关键思路或技巧
- **思维方式**：通过找规律、手玩样例来猜测构造方案，再进行理论分析和验证。
- **代码实现技巧**：采用简单的循环来输出构造的点，代码简洁高效。

### 拓展思路
同类型题可能会改变距离的计算方式（如欧几里得距离）或网格的形状（如矩形网格），解题思路依然可以从找最大距离、分析距离产生情况、构造点集等方面入手。

### 推荐题目
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径规划和状态转移，与本题的构造思路有一定相似性。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：需要通过合理选择来达到某种最优结果，锻炼构造和分析能力。
- [P1216 [USACO1.5][IOI1994]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：涉及路径选择和最优解的构造。

### 个人心得摘录与总结
- **Special_Tony**：赛时百思不得其解，赛后看他人代码恍然大悟。总结：遇到难题时，可参考他人思路来启发自己。
- **g1ove**：该题是非常神秘的构造题，考场大脑旋转，目前收获 154 个差评。总结：构造题有一定难度，需要不断尝试和思考。 

---
处理用时：45.53秒