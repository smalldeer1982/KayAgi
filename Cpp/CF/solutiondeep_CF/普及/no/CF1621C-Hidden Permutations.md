# 题目信息

# Hidden Permutations

## 题目描述

This is an interactive problem.

The jury has a permutation $ p $ of length $ n $ and wants you to guess it. For this, the jury created another permutation $ q $ of length $ n $ . Initially, $ q $ is an identity permutation ( $ q_i = i $ for all $ i $ ).

You can ask queries to get $ q_i $ for any $ i $ you want. After each query, the jury will change $ q $ in the following way:

- At first, the jury will create a new permutation $ q' $ of length $ n $ such that $ q'_i = q_{p_i} $ for all $ i $ .
- Then the jury will replace permutation $ q $ with pemutation $ q' $ .

You can make no more than $ 2n $ queries in order to quess $ p $ .

## 说明/提示

In the first test case the hidden permutation $ p = [4, 2, 1, 3] $ .

Before the first query $ q = [1, 2, 3, 4] $ so answer for the query will be $ q_3 = 3 $ .

Before the second query $ q = [4, 2, 1, 3] $ so answer for the query will be $ q_2 = 2 $ .

Before the third query $ q = [3, 2, 4, 1] $ so answer for the query will be $ q_4 = 1 $ .

In the second test case the hidden permutation $ p = [1, 3, 4, 2] $ .

Empty strings are given only for better readability. There will be no empty lines in the testing system.

## 样例 #1

### 输入

```
2
4

3

2

1

4

2

4

4```

### 输出

```
? 3

? 2

? 4

! 4 2 1 3

? 2

? 3

? 2

! 1 3 4 2```

# AI分析结果

### 中文题目重写

#### 题目描述

这是一个交互题。

裁判有一个长度为 $n$ 的排列 $p$，并希望你来猜测它。为此，裁判创建了另一个长度为 $n$ 的排列 $q$。初始时，$q$ 是一个恒等排列（即 $q_i = i$ 对所有 $i$ 成立）。

你可以通过查询来获取 $q_i$ 的值，其中 $i$ 是你指定的任意位置。每次查询后，裁判会按照以下方式更新 $q$：

1. 首先，裁判会创建一个新的排列 $q'$，使得 $q'_i = q_{p_i}$ 对所有 $i$ 成立。
2. 然后，裁判会用 $q'$ 替换当前的排列 $q$。

你最多可以进行 $2n$ 次查询来猜测 $p$。

#### 说明/提示

在第一个测试用例中，隐藏的排列 $p = [4, 2, 1, 3]$。

在第一次查询之前，$q = [1, 2, 3, 4]$，因此查询 $q_3$ 的答案为 $3$。

在第二次查询之前，$q = [4, 2, 1, 3]$，因此查询 $q_2$ 的答案为 $2$。

在第三次查询之前，$q = [3, 2, 4, 1]$，因此查询 $q_4$ 的答案为 $1$。

在第二个测试用例中，隐藏的排列 $p = [1, 3, 4, 2]$。

空行仅用于提高可读性。在测试系统中不会有空行。

#### 样例 #1

##### 输入

```
2
4

3

2

1

4

2

4

4```

##### 输出

```
? 3

? 2

? 4

! 4 2 1 3

? 2

? 3

? 2

! 1 3 4 2```

### 算法分类
构造

### 题解分析与结论

本题的核心是通过交互查询来推断隐藏的排列 $p$。由于每次查询后 $q$ 会按照 $q'_i = q_{p_i}$ 进行更新，因此可以通过多次查询来追踪 $q$ 的变化，从而推断出 $p$ 的结构。

#### 题解对比

1. **XL4453 的题解**：
   - **思路**：通过连续查询一个位置，观察 $q$ 的变化，推断出 $p$ 的环结构。
   - **难点**：需要确保查询次数不超过 $2n$，并且要正确处理环的闭合。
   - **代码实现**：通过 `ask` 函数进行查询，并使用 `rec` 数组记录查询结果，最终通过环结构推断出 $p$。
   - **评分**：4星，思路清晰，代码简洁，但缺少对环结构的详细解释。

2. **清烛 的题解**：
   - **思路**：通过追踪 $q$ 的变化，找到 $p$ 的环结构，并利用环上的关系推断出 $p$。
   - **难点**：同样需要控制查询次数，并正确处理环的闭合。
   - **代码实现**：使用 `ask` 函数进行查询，并通过 `vec` 数组记录环上的元素，最终推断出 $p$。
   - **评分**：4星，思路清晰，代码可读性强，但缺少对查询次数的优化。

#### 最优关键思路

通过追踪 $q$ 的变化，找到 $p$ 的环结构，并利用环上的关系推断出 $p$。关键在于确保查询次数不超过 $2n$，并且正确处理环的闭合。

#### 可拓展之处

类似的问题可以出现在其他需要推断隐藏结构的交互题中，例如通过有限的查询次数推断出图的结构或序列的排列。

#### 推荐题目

1. [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)
2. [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

### 题解代码片段

#### XL4453 的题解代码

```cpp
void ask(int x,int y){
    printf("? %d\n",x);
    fflush(stdout);
    scanf("%d",&rec[y]);
}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)ans[i]=0;
        for(int i=1;i<=n;i++){
            if(ans[i]!=0)continue;
            ask(i,1);ask(i,2);cnt=2;
            while(rec[cnt]!=rec[1])ask(i,++cnt);
            for(int i=1;i<cnt;i++)ans[rec[i]]=rec[i+1];
        }
        printf("! ");
        for(int i=1;i<=n;i++)
        printf("%d ",ans[i]);
        printf("\n");
        fflush(stdout);
    }
    return 0;
}
```

#### 清烛 的题解代码

```cpp
int ask(int i) {
    cout << "? " << i << endl;
    int x; cin >> x;
    return x;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) vis[i] = 0;
        FOR(i, 1, n) {
            if (vis[i]) continue;
            vector<int> vec;
            int st = ask(i);
            vec.push_back(st);
            int u;
            do {
                u = ask(i);
                vec.push_back(u);
            } while (u != st);
            FOR(j, 0, (int)vec.size() - 2) {
                ans[vec[j]] = vec[j + 1];
                vis[vec[j]] = 1;
            }
        }
        cout << "! ";
        FOR(i, 1, n) cout << ans[i] << ' ';
        cout << endl;
    }
    return 0;
}
```

---
处理用时：40.90秒