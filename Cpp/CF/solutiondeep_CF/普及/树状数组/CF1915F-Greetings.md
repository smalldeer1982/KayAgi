# 题目信息

# Greetings

## 题目描述

There are $ n $ people on the number line; the $ i $ -th person is at point $ a_i $ and wants to go to point $ b_i $ . For each person, $ a_i < b_i $ , and the starting and ending points of all people are distinct. (That is, all of the $ 2n $ numbers $ a_1, a_2, \dots, a_n, b_1, b_2, \dots, b_n $ are distinct.)

All the people will start moving simultaneously at a speed of $ 1 $ unit per second until they reach their final point $ b_i $ . When two people meet at the same point, they will greet each other once. How many greetings will there be?

Note that a person can still greet other people even if they have reached their final point.

## 说明/提示

In the first test case, the two people will meet at point $ 3 $ and greet each other.

## 样例 #1

### 输入

```
5
2
2 3
1 4
6
2 6
3 9
4 5
1 8
7 10
-2 100
4
-10 10
-5 5
-12 12
-13 13
5
-4 9
-2 5
3 4
6 7
8 10
4
1 2
3 4
5 6
7 8```

### 输出

```
1
9
6
4
0```

# AI分析结果

### 题目内容翻译
## 问候

### 题目描述
数轴上有 $n$ 个人，第 $i$ 个人位于点 $a_i$，想要前往点 $b_i$。对于每个人，都有 $a_i < b_i$，并且所有人的起点和终点各不相同（也就是说，所有 $2n$ 个数 $a_1, a_2, \dots, a_n, b_1, b_2, \dots, b_n$ 都是不同的）。

所有人将同时以每秒 $1$ 个单位的速度开始移动，直到到达他们的终点 $b_i$。当两个人在同一点相遇时，他们会互相问候一次。会有多少次问候呢？

注意，即使一个人已经到达了终点，他仍然可以和其他人问候。

### 说明/提示
在第一个测试用例中，两个人将在点 $3$ 相遇并互相问候。

### 样例 #1
#### 输入
```
5
2
2 3
1 4
6
2 6
3 9
4 5
1 8
7 10
-2 100
4
-10 10
-5 5
-12 12
-13 13
5
-4 9
-2 5
3 4
6 7
8 10
4
1 2
3 4
5 6
7 8
```

#### 输出
```
1
9
6
4
0
```

### 综合分析与结论
- **思路对比**：多数题解都发现两人相遇的条件是一个人的区间包含另一个人的区间，即 $a_i < a_j < b_j < b_i$。部分题解将问题转化为逆序对问题，通过对 $a_i$ 排序后求 $b_i$ 的逆序对数量；部分题解使用树状数组来动态统计满足条件的点对数量。
- **算法要点**：主要算法有排序、逆序对求解、树状数组和离散化。排序用于将人按起点位置排序，逆序对求解可直接得出结果，树状数组用于动态统计比某个数小或大的数的个数，离散化用于处理值域较大的情况。
- **解决难点**：本题的难点在于分析出两人相遇的条件，以及处理值域较大的问题。通过排序和逆序对的转化，以及离散化和树状数组的使用，有效解决了这些难点。

### 所选题解
- **作者：foryou_ (赞：13)，5星**
    - **关键亮点**：思路简洁清晰，直接点明问题本质是求逆序对，没有过多复杂的推导，让人一目了然。
- **作者：ThySecret (赞：4)，4星**
    - **关键亮点**：不仅思路清晰，还给出了详细的代码实现，代码结构清晰，注释详细，适合初学者学习。
    - **核心代码**：
```c++
void mergesort(int bg, int ed)
{
    if (bg == ed)
        return;
    int mid = (bg + ed) / 2, i = bg, j = mid + 1, k = bg;
    mergesort(bg, mid), mergesort(mid + 1, ed);
    while (i <= mid && j <= ed)
    {
        if (a[i] <= a[j])
            c[k++] = a[i++];
        else
            c[k++] = a[j++], ans += mid - i + 1;
    }
    while (i <= mid)
        c[k++] = a[i++];
    while (j <= ed)
        c[k++] = a[j++];
    for (int l = bg; l <= ed; l++)
        a[l] = c[l];
}

void solve()
{
    int n; cin >> n;
    for (int i = 1; i <= n; i ++) cin >> tmp[i].l >> tmp[i].r;
    sort(tmp + 1, tmp + 1 + n);
    
    for (int i = 1; i <= n; i ++) 
        a[i] = tmp[i].r;
    ans = 0;
    mergesort(1, n);
    cout << ans << '\n';
}
```
**核心实现思想**：使用归并排序求解逆序对。先将人按起点排序，再将终点存入数组，通过归并排序过程中比较元素大小，统计逆序对数量。
- **作者：Natori (赞：1)，4星**
    - **关键亮点**：详细解释了将问题转化为二维偏序问题的过程，对 $b$ 取相反数转化成顺序对求解，思路独特。同时提醒了树状数组要开两倍空间的易错点。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++){
    ans+=bit.query_sum(emt[i].b-1);
    bit.modify_add(emt[i].b,1);
}
```
**核心实现思想**：先对 $a$ 和取反后的 $b$ 进行离散化并排序，然后使用树状数组统计顺序对数量。

### 最优关键思路或技巧
- **问题转化**：将两人相遇问题转化为逆序对或二维偏序问题，简化了问题的求解。
- **离散化**：处理值域较大的问题，将不同的数映射到较小的连续区间，方便使用树状数组等数据结构。
- **树状数组**：动态统计比某个数小或大的数的个数，时间复杂度为 $O(\log n)$。

### 可拓展之处
同类型题或类似算法套路：
- 区间包含问题：如求区间的嵌套关系、区间的覆盖次数等。
- 二维偏序问题：如求平面上点对的满足某种条件的数量。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：直接考察逆序对的求解。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：树状数组的基础应用。
- [P2617 Dynamic Rankings](https://www.luogu.com.cn/problem/P2617)：涉及离散化和树状数组的动态查询问题。

### 个人心得摘录与总结
- **作者：DrAlfred**：提到比赛时因为树状数组开的空间不足（没有开两倍）而挂掉，提醒我们在处理离散化问题时，要注意树状数组的空间大小。
- **作者：Natori**：因为树状数组空间问题交了三发罚时，再次强调了离散化后值域为 $2n$ 时，树状数组要开两倍空间的易错点。 

---
处理用时：36.21秒