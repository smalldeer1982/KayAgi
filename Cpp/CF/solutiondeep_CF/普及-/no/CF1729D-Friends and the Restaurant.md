# 题目信息

# Friends and the Restaurant

## 题目描述

A group of $ n $ friends decide to go to a restaurant. Each of the friends plans to order meals for $ x_i $ burles and has a total of $ y_i $ burles ( $ 1 \le i \le n $ ).

The friends decide to split their visit to the restaurant into several days. Each day, some group of at least two friends goes to the restaurant. Each of the friends visits the restaurant no more than once (that is, these groups do not intersect). These groups must satisfy the condition that the total budget of each group must be not less than the amount of burles that the friends in the group are going to spend at the restaurant. In other words, the sum of all $ x_i $ values in the group must not exceed the sum of $ y_i $ values in the group.

What is the maximum number of days friends can visit the restaurant?

For example, let there be $ n = 6 $ friends for whom $ x $ = \[ $ 8, 3, 9, 2, 4, 5 $ \] and $ y $ = \[ $ 5, 3, 1, 4, 5, 10 $ \]. Then:

- first and sixth friends can go to the restaurant on the first day. They will spend $ 8+5=13 $ burles at the restaurant, and their total budget is $ 5+10=15 $ burles. Since $ 15 \ge 13 $ , they can actually form a group.
- friends with indices $ 2, 4, 5 $ can form a second group. They will spend $ 3+2+4=9 $ burles at the restaurant, and their total budget will be $ 3+4+5=12 $ burles ( $ 12 \ge 9 $ ).

It can be shown that they will not be able to form more groups so that each group has at least two friends and each group can pay the bill.

So, the maximum number of groups the friends can split into is $ 2 $ . Friends will visit the restaurant for a maximum of two days. Note that the $ 3 $ -rd friend will not visit the restaurant at all.

Output the maximum number of days the friends can visit the restaurant for given $ n $ , $ x $ and $ y $ .

## 说明/提示

The first test case in explained in the problem statement.

In the second test case, friends cannot form at least one group of two or more people.

In the third test case, one way to visit the restaurant in one day is to go in a group of all three friends ( $ 1+3+10 \ge 2+3+7 $ ). Note that they do not have the option of splitting into two groups.

## 样例 #1

### 输入

```
6
6
8 3 9 2 4 5
5 3 1 4 5 10
4
1 2 3 4
1 1 2 2
3
2 3 7
1 3 10
6
2 3 6 9 5 7
3 2 7 10 6 10
6
5 4 2 1 8 100
1 1 1 1 1 200
6
1 4 1 2 4 2
1 3 3 2 3 4```

### 输出

```
2
0
1
3
1
3```

# AI分析结果

### 题目内容
# 朋友与餐厅

## 题目描述
有 n 个朋友决定去餐厅。每个朋友计划花费 \( x_i \) 卢布点餐，并且各自拥有 \( y_i \) 卢布（\( 1 \leq i \leq n \)）。

朋友们决定将去餐厅的行程分成几天进行。每天，至少有两个朋友组成一组去餐厅。每个朋友最多去一次餐厅（即这些组不相交）。这些组必须满足一个条件：每组的总预算必须不少于该组朋友在餐厅计划花费的金额。换句话说，组内所有 \( x_i \) 值的总和不得超过组内 \( y_i \) 值的总和。

朋友们最多可以分几天去餐厅呢？

例如，假设有 \( n = 6 \) 个朋友，\( x \) = [ \( 8, 3, 9, 2, 4, 5 \) ] 且 \( y \) = [ \( 5, 3, 1, 4, 5, 10 \) ] 。那么：
 - 第一天，第一个和第六个朋友可以去餐厅。他们在餐厅将花费 \( 8 + 5 = 13 \) 卢布，而他们的总预算是 \( 5 + 10 = 15 \) 卢布。由于 \( 15 \geq 13 \) ，他们实际上可以组成一组。
 - 索引为 \( 2, 4, 5 \) 的朋友可以组成第二组。他们在餐厅将花费 \( 3 + 2 + 4 = 9 \) 卢布，而他们的总预算将是 \( 3 + 4 + 5 = 12 \) 卢布（\( 12 \geq 9 \)）。

可以证明，他们无法再组成更多组，使得每组至少有两个朋友且每组都能支付账单。

所以，朋友们最多可以分成的组数是 \( 2 \) 组。朋友们最多可以去餐厅两天。注意，第 \( 3 \) 个朋友根本不会去餐厅。

对于给定的 \( n \)、\( x \) 和 \( y \) ，输出朋友们最多可以去餐厅的天数。

## 说明/提示
第一个测试用例在题目描述中有解释。

在第二个测试用例中，朋友们无法组成至少一个由两个或更多人组成的组。

在第三个测试用例中，一种在一天内去餐厅的方式是所有三个朋友一起去（\( 1 + 3 + 10 \geq 2 + 3 + 7 \)）。注意，他们没有分成两组的选择。

## 样例 #1
### 输入
```
6
6
8 3 9 2 4 5
5 3 1 4 5 10
4
1 2 3 4
1 1 2 2
3
2 3 7
1 3 10
6
2 3 6 9 5 7
3 2 7 10 6 10
6
5 4 2 1 8 100
1 1 1 1 1 200
6
1 4 1 2 4 2
1 3 3 2 3 4
```
### 输出
```
2
0
1
3
1
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路较为一致，均基于贪心策略，认为要使组数最多，每组应尽量只有两人。通过构造数组 \( c[i] = y[i] - x[i] \)，将问题转化为寻找满足 \( c[p] + c[q] \geq 0 \) 的数对。算法要点在于对数组 \( c \) 进行排序，然后利用双指针法遍历数组，寻找符合条件的数对并计数。解决难点主要在于证明每组人数为2是最优解以及双指针法的正确运用。不同题解在代码实现细节和对思路的阐述上有所差异，但整体思路和算法框架相似。

### 所选的题解
 - **作者：lrqlrq250 (赞：4)  星级：4星**
    - **关键亮点**：思路清晰，先阐述关键结论，再详细说明双指针的移动方式，对时间复杂度分析准确。
    - **个人心得**：无
    - **核心代码**：
```cpp
int main(){
    int t;
    scanf("%d", &t);
    while (t--){
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &y[i]), c[i] = y[i] - x[i];
        stable_sort(c + 1, c + n + 1);
        int cnt = 0, p = 1, q = n;
        while (p < q){
            while (c[p] + c[q] < 0 && p < q) p++;
            if (p == q) break;
            if (c[p] + c[q] >= 0) cnt++;
            p++, q--; 
        }
        printf("%d\n", cnt);
    }
    return 0;
}
```
    - **核心实现思想**：读入数据并计算 \( c[i] = y[i] - x[i] \)，对 \( c \) 数组排序。使用双指针 \( p \) 和 \( q \) 分别指向数组首尾，移动指针寻找满足 \( c[p] + c[q] \geq 0 \) 的数对，找到则答案加一，继续移动指针寻找下一对。
 - **作者：endswitch (赞：3)  星级：4星**
    - **关键亮点**：简洁明了，直接阐述贪心思路和双指针的运用过程，代码简洁。
    - **个人心得**：无
    - **核心代码**：
```cpp
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>T;
    while(T--) {
        cin>>n;
        ans = 0, l = 1, r = n;
        for(int i = 1; i <= n; i++)
            cin>>x[i];
        for(int i = 1; i <= n; i++)
            cin>>y[i], z[i] = y[i] - x[i];
        sort(z + 1, z + 1 + n);
        while(l < r) {
            while(z[l] + z[r] < 0 && l < r) l++;
            if(l == r) break;
            if(z[l] + z[r] >= 0) ans++;
            l++, r--;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```
    - **核心实现思想**：读入数据并计算 \( z[i] = y[i] - x[i] \)，排序后用双指针 \( l \) 和 \( r \) 从两端遍历数组，寻找满足 \( z[l] + z[r] \geq 0 \) 的数对，找到则答案加一，并移动指针继续寻找。
 - **作者：lyt_awa (赞：1)  星级：4星**
    - **关键亮点**：对贪心思路解释详细，代码中使用了自定义的读入优化函数，对双指针的运用描述清晰。
    - **个人心得**：无
    - **核心代码**：
```cpp
int main() {
    t = read();
    while (t--) {
        ans = 0;
        n = read();
        for (int i = 1; i <= n; ++i) x[i] = read();
        for (int i = 1; i <= n; ++i) {
            y[i] = read();
            c[i] = y[i] - x[i];
        }
        sort(c + 1, c + n + 1);
        l = 1, r = n;
        while (l < r) {
            while (c[l] + c[r] < 0 && l < r) ++l;
            if (l == r) break;
            if (c[l] + c[r] >= 0) ++ans;
            l++, r--;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```
    - **核心实现思想**：通过自定义读入函数读入数据，计算 \( c[i] = y[i] - x[i] \) 并排序。利用双指针 \( l \) 和 \( r \) 从数组两端寻找满足 \( c[l] + c[r] \geq 0 \) 的数对，计数并移动指针。

### 最优关键思路或技巧
核心思路是贪心策略，认为每组人数为2时能使组数最多。通过构造差值数组并排序，利用双指针法高效地找到符合条件的数对，这种方法避免了暴力枚举，大大降低了时间复杂度。

### 可拓展思路
此类题目属于贪心策略在组合分组问题中的应用。类似题目常围绕资源分配、任务分组等场景，通过分析最优情况，利用排序和双指针等技巧解决。例如，在一些任务分配场景中，根据任务难度和人员能力进行分组，使完成的任务组数最多。

### 推荐题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过贪心策略解决分配问题，与本题类似，需分析最优分配方式。
 - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：涉及字符串分组问题，可运用贪心和排序思想解决。
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：通过贪心策略优化生产调度，与本题在寻找最优分组或安排上思路相似。 

---
处理用时：65.95秒