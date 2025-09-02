# 题目信息

# Building an Aquarium

## 题目描述

You love fish, that's why you have decided to build an aquarium. You have a piece of coral made of $ n $ columns, the $ i $ -th of which is $ a_i $ units tall. Afterwards, you will build a tank around the coral as follows:

- Pick an integer $ h \geq 1 $ — the height of the tank. Build walls of height $ h $ on either side of the tank.
- Then, fill the tank up with water so that the height of each column is $ h $ , unless the coral is taller than $ h $ ; then no water should be added to this column.

 For example, with $ a=[3,1,2,4,6,2,5] $ and a height of $ h=4 $ , you will end up using a total of $ w=8 $ units of water, as shown.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1873E/7c1e58fc4d1641ece42f30c898039b9158eaffda.png)  You can use at most $ x $ units of water to fill up the tank, but you want to build the biggest tank possible. What is the largest value of $ h $ you can select?

## 说明/提示

The first test case is pictured in the statement. With $ h=4 $ we need $ 8 $ units of water, but if $ h $ is increased to $ 5 $ we need $ 13 $ units of water, which is more than $ x=9 $ . So $ h=4 $ is optimal.

In the second test case, we can pick $ h=4 $ and add $ 3 $ units to each column, using a total of $ 9 $ units of water. It can be shown that this is optimal.

In the third test case, we can pick $ h=2 $ and use all of our water, so it is optimal.

## 样例 #1

### 输入

```
5
7 9
3 1 2 4 6 2 5
3 10
1 1 1
4 1
1 4 3 4
6 1984
2 6 5 9 1 8
1 1000000000
1```

### 输出

```
4
4
2
335
1000000001```

# AI分析结果

### 题目翻译
# 建造一个水族馆

## 题目描述
你喜欢鱼，所以你决定建造一个水族馆。你有一块由 $n$ 列组成的珊瑚，第 $i$ 列的高度为 $a_i$ 个单位。之后，你将按以下方式在珊瑚周围建造一个水箱：
- 选择一个整数 $h \geq 1$ —— 水箱的高度。在水箱的两侧建造高度为 $h$ 的墙壁。
- 然后，向水箱中注水，使每列的高度达到 $h$，除非珊瑚的高度高于 $h$；在这种情况下，该列不添加水。

例如，当 $a=[3,1,2,4,6,2,5]$ 且高度 $h = 4$ 时，你最终将使用总共 $w = 8$ 个单位的水，如图所示。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1873E/7c1e58fc4d1641ece42f30c898039b9158eaffda.png)
你最多可以使用 $x$ 个单位的水来填充水箱，但你想建造尽可能大的水箱。你可以选择的 $h$ 的最大值是多少？

## 说明/提示
第一个测试用例在题目描述中有图示。当 $h = 4$ 时，我们需要 8 个单位的水，但如果 $h$ 增加到 5，我们需要 13 个单位的水，这超过了 $x = 9$。所以 $h = 4$ 是最优的。
在第二个测试用例中，我们可以选择 $h = 4$，并向每列添加 3 个单位的水，总共使用 9 个单位的水。可以证明这是最优的。
在第三个测试用例中，我们可以选择 $h = 2$ 并使用所有的水，所以这是最优的。

## 样例 #1
### 输入
```
5
7 9
3 1 2 4 6 2 5
3 10
1 1 1
4 1
1 4 3 4
6 1984
2 6 5 9 1 8
1 1000000000
1
```
### 输出
```
4
4
2
335
1000000001
```

### 算法分类
二分

### 综合分析与结论
这些题解主要围绕二分答案的思路来解决问题。核心在于发现随着 $h$ 的增大，$\sum_{i=1}^n\max(h - a_i, 0)$ 也增大，满足单调性，所以可以使用二分查找最大的 $h$ 使得该和不超过 $x$。各题解的主要差异在于二分的左右边界设定和代码实现细节。部分题解还采用了排序的方法，通过逐步计算剩余水量来更新 $h$。

### 所选题解
- **yszkddzyh（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对二分查找的写法有推荐和解释，适合初学者学习。
    - **个人心得**：二分推荐写法记录答案，这种写法对于初学者比较好调试。
- **minVan（4星）**
    - **关键亮点**：明确指出 $h$ 的范围小于 $\max\limits_{i\in [1,n]}\{a_i\}+x$，缩小了二分查找的范围。
- **xuchuhan（4星）**
    - **关键亮点**：详细阐述了选择二分算法的原因，包括题目特征和复杂度分析。

### 重点代码
#### yszkddzyh 的核心代码
```cpp
bool check(int h){//检查式子结果是否不超过 x
    ll c = 0;
    for(int i = 1; i <= n; i++)
        if(a[i] < h)
            c += h - a[i];
    return c <= x;
}

int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &x);
        for(int i = 1; i <= n; i++)
            scanf("%d", a + i);
        int l = 1, r = 2e9, mid, ans;
        while(l <= r){
            mid = (r - l >> 1) + l;
            if(check(mid)) l = mid + 1, ans = mid;
            else r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```
**核心实现思想**：通过 `check` 函数计算当 $h$ 为当前值时所需的水量，若不超过 $x$，则更新答案并在右半部分继续查找；否则在左半部分查找。

#### minVan 的核心代码
```cpp
inline bool check(int xx) {
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        cnt += (a[i] < xx ? xx - a[i] : 0);
    }
    return cnt <= x;
}

signed main() {
    int t;
    cin >> t;
    while(t--) {
        int maxi = -1, ans = 0;
        cin >> n >> x;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            maxi = max(maxi, a[i]);
        }
        int l = 1, r = maxi + x;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(check(mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```
**核心实现思想**：先找出序列中的最大值，确定二分的右边界为最大值加 $x$。通过 `check` 函数判断当前 $h$ 是否满足条件，更新答案和边界。

#### xuchuhan 的核心代码
```cpp
bool check(int mid){
    //带入去算
    int sum = 0;
    for(int i = 1; i <= n; i++)
        sum = sum + max(0LL, mid - a[i]);
    return sum <= x;
}

signed main(){
    cin >> t;
    while(t--){
        cin >> n >> x;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        int ans = 0;
        int l = 1;
        int r = INT_MAX;
        while(l <= r){
            int mid = (l + r)/2;
            if(check(mid))
                l = mid + 1, ans = mid;//合法
            else
                r = mid - 1;//不合法
        }
        cout << ans << "\n";
    }
    return 0;
}
```
**核心实现思想**：通过 `check` 函数计算当前 $h$ 所需水量，根据结果更新二分的左右边界，记录满足条件的最大 $h$。

### 关键思路与技巧
- **二分答案**：利用答案的单调性，通过二分查找快速定位满足条件的最大值。
- **范围确定**：合理确定二分的左右边界，如 $h$ 的范围小于 $\max\limits_{i\in [1,n]}\{a_i\}+x$，可以减少不必要的查找。
- **记录答案**：在二分过程中记录满足条件的答案，方便最终输出。

### 拓展思路
同类型题通常具有答案单调性的特点，如求最大值的最小值、最小值的最大值等问题。类似算法套路可应用于其他二分答案的题目，如在一定条件下求最优解的问题。

### 推荐题目
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)
- [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)

---
处理用时：46.61秒