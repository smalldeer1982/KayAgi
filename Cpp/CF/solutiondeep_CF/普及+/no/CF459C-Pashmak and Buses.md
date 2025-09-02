# 题目信息

# Pashmak and Buses

## 题目描述

Recently Pashmak has been employed in a transportation company. The company has $ k $ buses and has a contract with a school which has $ n $ students. The school planned to take the students to $ d $ different places for $ d $ days (each day in one place). Each day the company provides all the buses for the trip. Pashmak has to arrange the students in the buses. He wants to arrange the students in a way that no two students become close friends. In his ridiculous idea, two students will become close friends if and only if they are in the same buses for all $ d $ days.

Please help Pashmak with his weird idea. Assume that each bus has an unlimited capacity.

## 说明/提示

Note that two students become close friends only if they share a bus each day. But the bus they share can differ from day to day.

## 样例 #1

### 输入

```
3 2 2
```

### 输出

```
1 1 2 
1 2 1 
```

## 样例 #2

### 输入

```
3 2 1
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# Pashmak和公交车

## 题目描述
最近Pashmak受雇于一家运输公司。该公司有$k$辆公交车，并且与一所拥有$n$名学生的学校签订了合同。学校计划在$d$天内将学生带到$d$个不同的地方（每天去一个地方）。每天公司都会提供所有公交车用于出行。Pashmak必须安排学生乘坐公交车。他希望以一种方式安排学生，使得没有两个学生成为亲密朋友。按照他荒谬的想法，当且仅当两个学生在所有$d$天内都乘坐同一辆公交车时，他们才会成为亲密朋友。

请帮助Pashmak实现他这个奇怪的想法。假设每辆公交车的载客量是无限的。

## 说明/提示
请注意，两个学生只有在每天都乘坐同一辆公交车时才会成为亲密朋友。但是他们每天乘坐的公交车可以不同。

## 样例 #1
### 输入
```
3 2 2
```
### 输出
```
1 1 2 
1 2 1 
```

## 样例 #2
### 输入
```
3 2 1
```
### 输出
```
-1
```

### 算法分类
构造

### 综合分析与结论
这三道题解思路基本一致，都先判断了 $k^d$ 是否小于 $n$，若小于则无解输出 -1，因为总共只有 $k^d$ 种不同的坐车组合方式，如果学生数 $n$ 大于此数则无法满足要求。然后都利用 $k$ 进制数来构造学生每天的坐车安排，将每个学生 $d$ 天的坐车情况看作一个 $k$ 进制数，由于 $k$ 进制数每位取值范围是 $0$ 到 $k - 1$，而题目要求是 $1$ 到 $k$，所以输出时每个数要加一。不同点在于对 $k^d$ 的计算方式略有不同，有的使用循环计算并在超过 $n$ 时截断处理，有的提到可以用 `pow()` 函数并特判范围。整体思路清晰，核心都是基于进制转换的构造算法。

### 所选的题解
- **作者：_Kimi_**（5星）
    - **关键亮点**：思路清晰，代码实现完整且详细，通过自定义函数 `check` 来判断是否有解，在计算 $k^d$ 时采用循环累乘并在超过 $n$ 时截断处理，代码结构完整，可读性高。
    - **个人心得**：无
    ```cpp
    int check(int a, int b) {
        int res = 1;
        bool flag = 0;
        for(int i = 1; i <= b; i++){
            res *= k;
            if(res > n) res = n;
        }
        if(res < n) return 0;
        return 1;
    }
    void input(){
        ios::sync_with_stdio(0);
        cin.tie(0);
        cin >> n >> k >> d;
        if(!check(k, d)) cout << -1 << endl, ex;
    }
    signed main(){
        input();
        for (int i = 1; i <= n; i++) {
            int now = i;
            for (int j = 1; j <= d; j++) a[i][j] = now % k + 1, now /= k;
        }
        for (int j = 1; j <= d; ++j) {
            for (int i = 1; i <= n; ++i) cout << a[i][j] << ' ';
            cout << endl;
        }
        return 0;
    }
    ```
- **作者：迟暮天复明**（4星）
    - **关键亮点**：将题意简化为构造数列问题，表述简洁明了，直接指出把每个数列抽象成 $k$ 进制数，按字典序最小构造，即每个数列值为 $0$ 到 $n - 1$，最后输出加一，思路清晰。
    - **个人心得**：无
- **作者：CarrotMeow**（4星）
    - **关键亮点**：准确理解题意并指出利用抽屉原理判断无解情况，提到 $k^d \geq n$ 时计算方式的多样性，如循环计算或用 `pow()` 特判范围，思维全面。
    - **个人心得**：无

### 最优关键思路或技巧
利用进制转换的思想，将学生 $d$ 天的坐车安排看作 $k$ 进制数，通过这种方式巧妙构造出满足条件的方案。同时在计算 $k^d$ 时，根据数据范围合理选择计算方式以避免溢出等问题。

### 同类型题或类似算法套路
此类题目属于构造类问题，通常需要根据给定的条件和限制，构造出符合要求的数据结构或序列。类似套路是先分析问题本质，找到一种能够满足所有条件的表示方法，如本题利用进制表示来满足学生坐车安排的条件。

### 洛谷相似题目推荐
- [P1108 低价购买](https://www.luogu.com.cn/problem/P1108)：涉及到构造满足一定条件的序列，与本题构造满足条件的学生坐车安排序列类似。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：同样是在给定条件下构造合适的方案，不过本题是路径构造，与本题构造思路有相通之处。
- [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：需要根据题目条件构造出满足要求的跳跃方案，与本题构造满足条件的安排方案思路类似。 

---
处理用时：42.35秒