# 题目信息

# Wonderful Coloring - 2

## 题目描述

This problem is an extension of the problem "Wonderful Coloring - 1". It has quite many differences, so you should read this statement completely.

Recently, Paul and Mary have found a new favorite sequence of integers $ a_1, a_2, \dots, a_n $ . They want to paint it using pieces of chalk of $ k $ colors. The coloring of a sequence is called wonderful if the following conditions are met:

1. each element of the sequence is either painted in one of $ k $ colors or isn't painted;
2. each two elements which are painted in the same color are different (i. e. there's no two equal values painted in the same color);
3. let's calculate for each of $ k $ colors the number of elements painted in the color — all calculated numbers must be equal;
4. the total number of painted elements of the sequence is the maximum among all colorings of the sequence which meet the first three conditions.

E. g. consider a sequence $ a=[3, 1, 1, 1, 1, 10, 3, 10, 10, 2] $ and $ k=3 $ . One of the wonderful colorings of the sequence is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1551B2/dbd09f59a345c41308d3382019b949ebfdfed535.png)The example of a wonderful coloring of the sequence $ a=[3, 1, 1, 1, 1, 10, 3, 10, 10, 2] $ and $ k=3 $ . Note that one of the elements isn't painted.Help Paul and Mary to find a wonderful coloring of a given sequence $ a $ .

## 说明/提示

In the first test case, the answer is shown in the figure in the statement. The red color has number $ 1 $ , the blue color — $ 2 $ , the green — $ 3 $ .

## 样例 #1

### 输入

```
6
10 3
3 1 1 1 1 10 3 10 10 2
4 4
1 1 1 1
1 1
1
13 1
3 1 4 1 5 9 2 6 5 3 5 8 9
13 2
3 1 4 1 5 9 2 6 5 3 5 8 9
13 3
3 1 4 1 5 9 2 6 5 3 5 8 9```

### 输出

```
1 1 0 2 3 2 2 1 3 3
4 2 1 3
1
0 0 1 1 0 1 1 1 0 1 1 1 0
2 1 2 2 1 1 1 1 2 1 0 2 2
1 1 3 2 1 3 3 1 2 2 3 2 0```

# AI分析结果

### 题目内容重写

#### 题目描述

这个问题是“Wonderful Coloring - 1”问题的扩展。它有许多不同之处，因此你应该完整阅读这个描述。

最近，Paul 和 Mary 发现了一个新的最喜欢的整数序列 $a_1, a_2, \dots, a_n$。他们想用 $k$ 种颜色的粉笔来涂色。一个序列的涂色被称为“wonderful”如果满足以下条件：

1. 序列中的每个元素要么被涂成 $k$ 种颜色之一，要么不被涂色；
2. 被涂成同一种颜色的两个元素必须不同（即没有两个相同的值被涂成同一种颜色）；
3. 对于每种颜色，计算被涂成该颜色的元素数量——所有计算出的数量必须相等；
4. 被涂色的元素总数在所有满足前三个条件的涂色方案中是最大的。

例如，考虑序列 $a=[3, 1, 1, 1, 1, 10, 3, 10, 10, 2]$ 和 $k=3$。其中一个“wonderful”涂色方案如图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1551B2/dbd09f59a345c41308d3382019b949ebfdfed535.png)  
序列 $a=[3, 1, 1, 1, 1, 10, 3, 10, 10, 2]$ 和 $k=3$ 的“wonderful”涂色示例。注意其中一个元素未被涂色。

帮助 Paul 和 Mary 找到给定序列 $a$ 的“wonderful”涂色方案。

#### 说明/提示

在第一个测试用例中，答案如图所示。红色颜色编号为 $1$，蓝色为 $2$，绿色为 $3$。

#### 样例 #1

##### 输入

```
6
10 3
3 1 1 1 1 10 3 10 10 2
4 4
1 1 1 1
1 1
1
13 1
3 1 4 1 5 9 2 6 5 3 5 8 9
13 2
3 1 4 1 5 9 2 6 5 3 5 8 9
13 3
3 1 4 1 5 9 2 6 5 3 5 8 9
```

##### 输出

```
1 1 0 2 3 2 2 1 3 3
4 2 1 3
1
0 0 1 1 0 1 1 1 0 1 1 1 0
2 1 2 2 1 1 1 1 2 1 0 2 2
1 1 3 2 1 3 3 1 2 2 3 2 0
```

### 算法分类
贪心

### 题解分析与结论

本题的核心在于如何分配颜色，使得被涂色的元素数量最大化，同时满足每种颜色的元素数量相等且同种颜色的元素值不同。多个题解都采用了贪心策略，通过统计每个元素的出现次数，并根据出现次数与颜色数量 $k$ 的关系来决定哪些元素可以被涂色。以下是各题解的要点对比：

1. **Starlit_Night** 的题解通过统计每个数字的出现次数，将可以被涂色的元素存入 `vector` 并排序，然后依次分配颜色。该题解思路清晰，代码实现简洁，且通过排序避免了同种颜色分配相同元素的问题。
   
2. **UperFicial** 的题解通过抽象 $k+1$ 个容器来处理元素的分配，思路较为复杂，但通过排序和去重的方式解决了元素分配的问题。该题解的实现较为复杂，但思路独特。

3. **NXYorz** 的题解通过结构体存储元素及其位置，排序后依次分配颜色。该题解的实现较为直接，但代码较为冗长，且存在 MLE 的问题。

4. **Interstellar_Zhou** 的题解通过 `vector` 存储每个元素的出现位置，并根据出现次数与 $k$ 的关系进行分配。该题解的实现较为简洁，但思路与 **Starlit_Night** 的题解类似。

5. **black_trees** 的题解通过统计每个元素的出现次数，并根据出现次数与 $k$ 的关系进行分配。该题解的实现较为简洁，但思路与 **Starlit_Night** 的题解类似。

6. **KSToki** 的题解通过 `vector` 存储每个元素的出现位置，并根据出现次数与 $k$ 的关系进行分配。该题解的实现较为简洁，但思路与 **Starlit_Night** 的题解类似。

7. **Mysterious_Mini** 的题解通过统计每个元素的出现次数，并根据出现次数与 $k$ 的关系进行分配。该题解的实现较为简洁，但思路与 **Starlit_Night** 的题解类似。

### 精选题解

#### 1. Starlit_Night (★★★★★)
- **关键亮点**：通过统计每个数字的出现次数，将可以被涂色的元素存入 `vector` 并排序，然后依次分配颜色。思路清晰，代码简洁。
- **核心代码**：
```cpp
sort(v.begin(),v.end());
int groups=v.size()/k;
for(int i=0;i<groups*k;i++){
    ans[v[i].second]=i%k+1;
}
```

#### 2. Interstellar_Zhou (★★★★)
- **关键亮点**：通过 `vector` 存储每个元素的出现位置，并根据出现次数与 $k$ 的关系进行分配。实现简洁，思路清晰。
- **核心代码**：
```cpp
for(int i=1;i<=cnt-cnt%k;i++){
    vec[i%k+1].push_back(b[i]);
}
```

#### 3. KSToki (★★★★)
- **关键亮点**：通过 `vector` 存储每个元素的出现位置，并根据出现次数与 $k$ 的关系进行分配。实现简洁，思路清晰。
- **核心代码**：
```cpp
for(R int i=0,up=vec.size();i+k-1<up;i+=k){
    for(R int j=i;j<i+k;++j)
        ans[vec[j]]=j-i+1;
}
```

### 最优关键思路或技巧
- **贪心策略**：通过统计每个元素的出现次数，并根据出现次数与颜色数量 $k$ 的关系来决定哪些元素可以被涂色。
- **排序**：通过排序避免同种颜色分配相同元素的问题。
- **分组分配**：将可以被涂色的元素分成 $k$ 组，依次分配颜色，确保每种颜色的元素数量相等。

### 可拓展之处
- **类似问题**：类似的问题可以扩展到更多颜色或更复杂的分配规则，如每种颜色的元素数量不一定相等，或者某些元素必须被涂成特定颜色。
- **算法套路**：贪心策略在分配问题中非常常见，尤其是在需要最大化或最小化某些条件的情况下。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录
- **Starlit_Night**：排序的目的是为了避免同个数字被染同样色，核心代码中的注释有详细解释。
- **NXYorz**：一开始考虑用 `vector` 然后放在队列里大力操作，MLE 了 /kk。后来发现不用把相同的数字绑在一起，把他们看成一个个单独的个体，排序一下所有相同的数字都会在一起，然后依次涂色即可 qwq。

---
处理用时：61.38秒