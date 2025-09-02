# 题目信息

# Garland

## 题目描述

Vadim loves decorating the Christmas tree, so he got a beautiful garland as a present. It consists of $ n $ light bulbs in a single row. Each bulb has a number from $ 1 $ to $ n $ (in arbitrary order), such that all the numbers are distinct. While Vadim was solving problems, his home Carp removed some light bulbs from the garland. Now Vadim wants to put them back on.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1286A/44ebad0b7dea7f3147d7078591406d3a6ec6de35.png)Vadim wants to put all bulb back on the garland. Vadim defines complexity of a garland to be the number of pairs of adjacent bulbs with numbers with different parity (remainder of the division by $ 2 $ ). For example, the complexity of 1 4 2 3 5 is $ 2 $ and the complexity of 1 3 5 7 6 4 2 is $ 1 $ .

No one likes complexity, so Vadim wants to minimize the number of such pairs. Find the way to put all bulbs back on the garland, such that the complexity is as small as possible.

## 说明/提示

In the first example, one should place light bulbs as 1 5 4 2 3. In that case, the complexity would be equal to 2, because only $ (5, 4) $ and $ (2, 3) $ are the pairs of adjacent bulbs that have different parity.

In the second case, one of the correct answers is 1 7 3 5 6 4 2.

## 样例 #1

### 输入

```
5
0 5 0 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
1 0 0 5 0 0 2```

### 输出

```
1```

# AI分析结果

### 题目中文重写
# 花环

## 题目描述
瓦迪姆喜欢装饰圣诞树，所以他收到了一个漂亮的花环作为礼物。它由一排 $n$ 个灯泡组成。每个灯泡都有一个从 $1$ 到 $n$ 的编号（顺序任意），且所有编号都不同。当瓦迪姆在解题时，他的宠物卡尔普从花环上取下了一些灯泡。现在瓦迪姆想把它们装回去。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1286A/44ebad0b7dea7f3147d7078591406d3a6ec6de35.png)
瓦迪姆想把所有灯泡都装回到花环上。瓦迪姆将花环的复杂度定义为相邻灯泡编号奇偶性不同的对数。例如，1 4 2 3 5 的复杂度是 $2$，1 3 5 7 6 4 2 的复杂度是 $1$。

没有人喜欢复杂度高的花环，所以瓦迪姆想尽量减少这样的对数。找出一种将所有灯泡装回花环的方法，使得复杂度尽可能小。

## 说明/提示
在第一个示例中，应该将灯泡排列为 1 5 4 2 3。在这种情况下，复杂度等于 2，因为只有 $(5, 4)$ 和 $(2, 3)$ 是相邻灯泡奇偶性不同的对。

在第二个示例中，其中一个正确答案是 1 7 3 5 6 4 2。

## 样例 #1
### 输入
```
5
0 5 0 2 3
```
### 输出
```
2
```

## 样例 #2
### 输入
```
7
1 0 0 5 0 0 2
```
### 输出
```
1
```

### 算法分类
本题最相关的算法分类为：动态规划、贪心

### 综合分析与结论
这些题解主要围绕如何将缺失的灯泡放回花环，使得相邻灯泡编号奇偶性不同的对数最少展开。题解主要分为贪心和动态规划两类思路。

贪心思路的题解主要是将序列分成全 $0$ 段，根据段两端数的奇偶性分类讨论，优先满足两端奇偶性相同且长度较短的全 $0$ 段，同时特判首尾的全 $0$ 段。动态规划思路的题解则是通过定义状态，根据当前位置的情况进行状态转移，最终得到最小的奇偶性不同对数。

### 所选题解
- **Kewth（5星）**
    - **关键亮点**：思路清晰，通过贪心策略，对中间全是 $0$ 的已确定数的区间进行分类讨论，合理安排 $0$ 的填充方式以最小化复杂度。使用基数排序优化复杂度至 $O(n)$，并通过枚举前缀和后缀的奇偶性解决边界问题。
- **灵茶山艾府（4星）**
    - **关键亮点**：提供简洁的动态规划解法，通过定义状态 $f[i][j][0/1]$ 表示前 $i$ 个数中有 $j$ 个偶数时的奇偶性不同对的最小个数，根据当前数字和上一个数字的奇偶性得到转移方程，还进行了空间优化。
- **suxxsfe（4星）**
    - **关键亮点**：使用动态规划，详细定义状态和转移方程，考虑了多种情况，虽然复杂度为 $O(n^3)$，但思路完整，代码注释清晰。

### 重点代码
#### Kewth 的题解核心代码
```cpp
int solve(int n) {
    int las = 0;
    int res = 0;
    for(int i = 1; i <= n + 1; i ++)
        if(p[i]) {
            if(p[i] == p[las])
                ++ q[p[i] - 2][i - las - 1];
            else
                ++ res;
            las = i;
        }

    for(int i = 0; i < 2; i ++) {
        int max = tot[i];
        for(int x = 0; x <= max; x ++) {
            while(q[i][x] and x <= max) {
                max -= x;
                -- q[i][x];
            }
        }
    }

    for(int i = 0; i <= n; i ++) {
        res += 2 * (q[0][i] + q[1][i]);
        q[0][i] = q[1][i] = 0;
    }

    return res;
}
```
**核心实现思想**：先统计相邻不同奇偶性的对数和两端奇偶性相同的全 $0$ 段信息，然后根据剩余奇数和偶数的数量，优先满足长度较短的全 $0$ 段，最后计算总复杂度。

#### 灵茶山艾府的题解核心代码（优化后）
```go
func main() {
    in := bufio.NewReader(os.Stdin)
    var n, v int
    Fscan(in, &n)
    f := make([][2]int, n/2+1)
    for i := 1; i <= n/2; i++ {
        f[i] = [2]int{1e9, 1e9}
    }
    for i := 0; i < n; i++ {
        Fscan(in, &v)
        for j := n / 2; j >= 0; j-- {
            if v == 0 || v%2 > 0 {
                f[j][1] = min(f[j][1], f[j][0]+1)
            } else {
                f[j][1] = 1e9
            }
            if j > 0 && v%2 == 0 {
                f[j][0] = min(f[j-1][0], f[j-1][1]+1)
            } else {
                f[j][0] = 1e9
            }
        }
    }
    Print(min(f[n/2][0], f[n/2][1]))
}

func min(a, b int) int { if a > b { return b }; return a }
```
**核心实现思想**：通过一维数组 $f$ 记录状态，根据当前数字的奇偶性和剩余偶数的数量进行状态转移，最终得到最小的奇偶性不同对数。

#### suxxsfe 的题解核心代码
```cpp
for(R int i=2;i<=n;i++){
    if(a[i]!=-1){
        for(R int o=num[0];o>=0;o--){
            for(R int j=num[1];j>=0;j--)
                min(f[i][o][j][a[i]],f[i-1][o][j][1]+(a[i]!=1)),
                min(f[i][o][j][a[i]],f[i-1][o][j][0]+(a[i]!=0));
        }
        continue;
    }
    for(R int o=num[0];o>=0;o--){
        for(R int j=num[1];j>=0;j--){
            min(f[i][o][j][1],f[i-1][o][j+1][1]);
            min(f[i][o][j][1],f[i-1][o][j+1][0]+1);
            min(f[i][o][j][0],f[i-1][o+1][j][0]);
            min(f[i][o][j][0],f[i-1][o+1][j][1]+1);
        }
    }
}
```
**核心实现思想**：根据当前位置是否确定，分情况进行状态转移，考虑当前位置填奇数或偶数时与前一个位置的奇偶性关系，更新状态数组 $f$。

### 关键思路或技巧
- **贪心思路**：将序列分成全 $0$ 段，根据段两端数的奇偶性分类讨论，优先满足两端奇偶性相同且长度较短的全 $0$ 段，可有效降低复杂度。
- **动态规划思路**：通过定义合适的状态和状态转移方程，利用已有的状态信息更新当前状态，逐步得到最优解。同时可以考虑空间优化，减少内存使用。

### 可拓展之处
同类型题可能会改变序列的形式或条件，如序列变为二维数组、增加更多的限制条件等。类似算法套路可用于解决其他需要通过合理安排元素来优化某个目标值的问题，如排列组合问题、资源分配问题等。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，可使用动态规划求解。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：动态规划入门题，通过状态转移求解最大路径和。
- [P2670 扫雷游戏](https://www.luogu.com.cn/problem/P2670)：可使用模拟和枚举的方法解决，与本题的枚举和分类讨论思想有相似之处。

### 个人心得摘录与总结
- **suxxsfe**：觉得这题作为一个 C 比 div2 的 B 要简单点，算是找回点 dp 的信心。总结：通过做这道题，对动态规划有了更多的信心，说明做合适难度的题目有助于提升对算法的掌握程度。
- **liuyz11**：这题是在大佬的提示下才做出来的，没搞懂这题怎么贪。总结：遇到难题时可以向他人请教，同时对于贪心算法的理解还需要进一步加强。

---
处理用时：70.94秒