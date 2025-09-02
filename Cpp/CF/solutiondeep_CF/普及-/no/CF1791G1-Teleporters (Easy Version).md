# 题目信息

# Teleporters (Easy Version)

## 题目描述

The only difference between the easy and hard versions are the locations you can teleport to.

Consider the points $ 0, 1, \dots, n $ on the number line. There is a teleporter located on each of the points $ 1, 2, \dots, n $ . At point $ i $ , you can do the following:

- Move left one unit: it costs $ 1 $ coin.
- Move right one unit: it costs $ 1 $ coin.
- Use a teleporter at point $ i $ , if it exists: it costs $ a_i $ coins. As a result, you teleport to point $ 0 $ . Once you use a teleporter, you can't use it again.

You have $ c $ coins, and you start at point $ 0 $ . What's the most number of teleporters you can use?

## 说明/提示

In the first test case, you can move one unit to the right, use the teleporter at index $ 1 $ and teleport to point $ 0 $ , move two units to the right and use the teleporter at index $ 2 $ . You are left with $ 6-1-1-2-1 = 1 $ coins you don't have enough coins to use another teleporter. You have used two teleporters, so the answer is two.

In the second test case, you go four units to the right and use the teleporter to go to $ 0 $ , then go six units right and use the teleporter at index $ 6 $ to go to $ 0 $ . The total cost will be $ 4+6+6+4 = 20 $ . You are left with $ 12 $ coins, but it is not enough to reach any other teleporter and use it so the answer is $ 2 $ .

In the third test case, you don't have enough coins to use any teleporter, so the answer is zero.

## 样例 #1

### 输入

```
10
5 6
1 1 1 1 1
8 32
100 52 13 6 9 4 100 35
1 1
5
4 5
4 3 2 1
5 9
2 3 1 4 1
5 8
2 3 1 4 1
4 3
2 3 4 1
4 9
5 4 3 3
2 14
7 5
5 600000000
500000000 400000000 300000000 200000000 100000000```

### 输出

```
2
2
0
1
2
2
1
1
1
2```

# AI分析结果

### 题目内容
# Teleporters (Easy Version)

## 题目描述
本题简单版本与困难版本的唯一区别在于你能够传送至的位置。

考虑数轴上的点 \(0, 1, \dots, n\) 。在点 \(1, 2, \dots, n\) 上各有一个传送器。在点 \(i\) ，你可以进行以下操作：
- 向左移动一个单位：花费 \(1\) 枚硬币。
- 向右移动一个单位：花费 \(1\) 枚硬币。
- 如果点 \(i\) 处存在传送器，使用该传送器：花费 \(a_i\) 枚硬币。结果是，你传送至点 \(0\) 。一旦你使用了一个传送器，就不能再次使用它。

你拥有 \(c\) 枚硬币，并且从点 \(0\) 出发。你最多能够使用多少个传送器？

## 说明/提示
在第一个测试用例中，你可以向右移动一个单位，使用索引为 \(1\) 的传送器并传送至点 \(0\) ，再向右移动两个单位并使用索引为 \(2\) 的传送器。此时你还剩下 \(6 - 1 - 1 - 2 - 1 = 1\) 枚硬币，不足以再使用另一个传送器。你已经使用了两个传送器，所以答案是 \(2\) 。

在第二个测试用例中，你向右移动四个单位并使用传送器回到 \(0\) ，然后向右移动六个单位并使用索引为 \(6\) 的传送器回到 \(0\) 。总花费将是 \(4 + 6 + 6 + 4 = 20\) 。你还剩下 \(12\) 枚硬币，但这不足以到达任何其他传送器并使用它，所以答案是 \(2\) 。

在第三个测试用例中，你没有足够的硬币使用任何传送器，所以答案是 \(0\) 。

## 样例 #1
### 输入
```
10
5 6
1 1 1 1 1
8 32
100 52 13 6 9 4 100 35
1 1
5
4 5
4 3 2 1
5 9
2 3 1 4 1
5 8
2 3 1 4 1
4 3
2 3 4 1
4 9
5 4 3 3
2 14
7 5
5 600000000
500000000 400000000 300000000 200000000 100000000
```
### 输出
```
2
2
0
1
2
2
1
1
1
2
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解的核心思路均基于贪心策略。由于每次使用传送器后都会回到 \(0\) 点，所以使用第 \(i\) 个传送器的总代价为从 \(0\) 走到 \(i\) 的代价 \(i\) 加上使用传送器的代价 \(a_i\) ，即 \(i + a_i\) 。然后将所有传送器按此总代价从小到大排序，依次尝试使用传送器，直到硬币不足。各题解的主要区别在于代码实现细节，如输入输出方式、数据结构使用等。

### 所选的题解
- **作者：arrow_king (5星)**
  - **关键亮点**：思路清晰简洁，代码实现高效，使用自定义的快速读入函数优化输入过程，整体代码结构紧凑，逻辑流畅。
  - **重点代码**：
```cpp
il ll read() {
    ll x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { f = -1; } c = getchar(); }
    while (c >= '0' && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
    return x * f;
}
int t, n, c, a[200005];
int main() {
    t = read();
    while (t--) {
        n = read(), c = read();
        for (int i = 1; i <= n; i++) {
            a[i] = read();
            a[i] += i;
        }
        sort(a + 1, a + n + 1);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (c >= a[i]) {
                c -= a[i];
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```
  - **核心实现思想**：先通过 `read` 函数快速读入数据，然后计算每个传送器的总代价并排序，通过遍历排序后的数组，在硬币足够时使用传送器并更新硬币数量和答案。

- **作者：LincW (4星)**
  - **关键亮点**：代码简洁明了，逻辑清晰，使用 `sum` 变量累计已使用传送器的总花费，通过一次遍历判断是否还能使用下一个传送器。
  - **重点代码**：
```cpp
ll arr[200005];
int main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        ll n, c;
        cin >> n >> c;
        for (int i = 1; i <= n; ++i)
        {
            cin >> arr[i];
            arr[i] += i;
        }
        sort(arr + 1, arr + 1 + n);
        ll sum = 0, ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            sum += arr[i];
            ans++;
            if (sum > c)
            {
                ans--;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```
  - **核心实现思想**：读入数据并计算每个传送器的总代价后排序，遍历排序后的数组，累加总花费，当总花费超过硬币数时，回退答案并结束循环。

- **作者：ttq012 (4星)**
  - **关键亮点**：代码简洁，利用 `lambda` 表达式对结构体进行排序，使代码更紧凑，逻辑清晰。
  - **重点代码**：
```cpp
struct node{
    int x, id;
}c[N];
int a[N];
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)cin >> a[i];
        for (int i = 1; i <= n; i++)c[i].x = i + a[i], c[i].id = i;
        sort(c + 1, c + n + 1, [&](const node&lhs, const node&rhs) {
            return lhs.x < rhs.x;
        });
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (m < c[i].x)break;
            cnt++, m -= c[i].x;
        }
        cout << cnt << '\n';
    }
    return 0;
}
```
  - **核心实现思想**：定义结构体存储每个传送器的相关信息，计算总代价后用 `lambda` 表达式按总代价排序，遍历排序后的数组，在硬币足够时使用传送器并更新硬币数量和答案。

### 最优关键思路或技巧
1. **贪心策略**：明确每次使用传送器的总代价为 \(i + a_i\) ，并基于此进行贪心选择，优先使用总代价小的传送器。
2. **排序优化**：通过对传送器按总代价排序，简化了选择传送器的过程，使得贪心策略能够高效实现。

### 可拓展思路
此类题目属于典型的贪心策略应用，类似套路可用于解决资源分配、最优选择等场景的问题。例如，在一系列具有不同收益和成本的任务中，在资源有限的情况下选择任务以获取最大收益。

### 推荐洛谷题目
1. **P1094 [NOIP2007 普及组] 纪念品分组**：同样是基于贪心策略，根据给定的条件对物品进行分组，以满足特定要求。
2. **P1199 [NOIP2010 普及组] 三国游戏**：通过分析游戏规则，利用贪心思想确定最优策略。
3. **P1223 排队接水**：根据接水时间对人进行排序，采用贪心算法求出总等待时间最短的方案。 

---
处理用时：65.26秒