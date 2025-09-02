# 题目信息

# Cubes

## 题目描述

Let's imagine that you're playing the following simple computer game. The screen displays $ n $ lined-up cubes. Each cube is painted one of $ m $ colors. You are allowed to delete not more than $ k $ cubes (that do not necessarily go one after another). After that, the remaining cubes join together (so that the gaps are closed) and the system counts the score. The number of points you score equals to the length of the maximum sequence of cubes of the same color that follow consecutively. Write a program that determines the maximum possible number of points you can score.

Remember, you may delete no more than $ k $ any cubes. It is allowed not to delete cubes at all.

## 说明/提示

In the first sample you should delete the fifth and the sixth cubes.

In the second sample you should delete the fourth and the seventh cubes.

In the third sample you shouldn't delete any cubes.

## 样例 #1

### 输入

```
10 3 2
1 2 1 1 3 2 1 1 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 2 2
1 2 1 2 1 1 2 1 1 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 1 2
1 1 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
#### Cubes
1. **题目描述**：想象你正在玩一个简单的电脑游戏。屏幕上显示 $n$ 个排成一排的方块。每个方块被涂成 $m$ 种颜色中的一种。你可以删除不超过 $k$ 个方块（这些方块不一定要连续）。之后，剩下的方块会连接在一起（即填补空缺），然后系统计算得分。你的得分等于连续相同颜色方块组成的最长序列的长度。编写一个程序，确定你能获得的最大得分。
记住，你最多可以删除 $k$ 个方块，也可以一个都不删。
2. **说明/提示**：
    - 在第一个样例中，你应该删除第5个和第6个方块。
    - 在第二个样例中，你应该删除第4个和第7个方块。
    - 在第三个样例中，你不应该删除任何方块。
3. **样例 #1**：
    - **输入**：
```
10 3 2
1 2 1 1 3 2 1 1 2 2
```
    - **输出**：
```
4
```
4. **样例 #2**：
    - **输入**：
```
10 2 2
1 2 1 2 1 1 2 1 1 2
```
    - **输出**：
```
5
```
5. **样例 #3**：
    - **输入**：
```
3 1 2
1 1 1
```
    - **输出**：
```
3
```

### 算法分类
枚举 + 双指针

### 题解综合分析与结论
这几道题解主要围绕如何在给定条件下找出最长连续相同颜色方块序列展开。多数题解先枚举颜色，再通过双指针或二分的方式求解。
1. **思路方面**：
    - **枚举 + 双指针思路**：先枚举每种颜色，将问题转化为对单一颜色方块序列的处理。使用双指针维护一个子串，通过移动指针保证删除方块数不超过 $k$ 个，同时更新最长子串长度。
    - **二分思路**：二分答案，即猜测最长连续相同颜色方块序列的长度 $len$ ，然后通过检查对于每种颜色，是否存在满足删除方块数不超过 $k$ 个的长度为 $len$ 的子序列，来确定最终答案。
2. **算法要点**：
    - **枚举 + 双指针**：关键在于用合适的数据结构记录每种颜色方块的位置信息，如链表或 `vector` 。双指针移动过程中，准确计算需要删除的方块数量。
    - **二分**：二分答案的范围通常是 $[1, n]$ ，每次二分后，对每种颜色检查是否存在符合条件的子序列，这一检查过程时间复杂度需控制在合理范围。
3. **解决难点**：
    - **共同难点**：如何高效处理多种颜色以及控制删除方块数量不超过 $k$ 个。
    - **枚举 + 双指针**：难点在于数据结构的选择与双指针移动条件的判断，确保不遗漏和重复计算。
    - **二分**：难点在于如何设计高效的 `check` 函数，快速判断当前二分的长度是否符合条件。

### 所选的题解
1. **作者：E1_de5truct0r (5星)**
    - **关键亮点**：利用链表思想（链式前向星）优化枚举每种颜色方块位置的过程，使得时间复杂度从 $O(nm)$ 优化到 $O(n)$ 。双指针移动逻辑清晰，准确控制删除方块数量。
    - **重点代码 - 核心实现思想**：通过链表记录每种颜色方块位置，枚举颜色时，用双指针在链表上移动，计算当前颜色最长连续子串长度。
```cpp
int head[200005],lst[200005],nxt[200005],a[200005];
int main()
{
    int n,m,k; cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(!lst[a[i]]) head[a[i]]=i,lst[a[i]]=i; 
        else nxt[lst[a[i]]]=i,lst[a[i]]=i; 
    }
    int ans=0;
    for(int i=1;i<=m;i++) 
    {
        int l,r,cnt=1; l=r=head[i]; 
        do
        {
            r=nxt[r]; cnt++; 
            while(r-l+1-cnt>k) l=nxt[l],cnt--; 
            if(cnt>ans) ans=cnt; 
        }while(nxt[r]); 
    }
    printf("%d",min(ans,n)); 
    return 0;
}
```
2. **作者：Dream__Sky (4星)**
    - **关键亮点**：思路清晰，用 `vector` 记录每种颜色方块位置，代码简洁易懂。双指针操作逻辑明确，容易理解和实现。
    - **重点代码 - 核心实现思想**：将每种颜色方块位置存入 `vector` ，对每种颜色用双指针维护子串，计算最长子串长度。
```cpp
vector<int> v[100010]; 
int check(int x)
{
    int len=v[x].size();
    int l=0,r=0,ans=0;
    while(l<=r&&r<=len)
    {
        while(r<len&&v[x][r]-v[x][l]-(r-l)<=k) r++;
        ans=max(ans,r-l);
        l++;
    }
    return ans;
}
int main()
{
    cin>>n>>m>>k;
    for(int i=1,x;i<=n;i++) 
    {
        cin>>x;
        v[x].push_back(i);
    }
    
    for(int i=1;i<=m;i++)
        maxn=max(maxn,check(i));
    
    cout<<maxn;
    return 0;
}
```
3. **作者：COsm0s (4星)**
    - **关键亮点**：采用二分答案的思路，使问题解决方式较为新颖。利用 `vector` 记录每个值出现位置，通过检查条件判断二分的长度是否合法。
    - **重点代码 - 核心实现思想**：二分答案 `len` ，对每种颜色遍历其位置数组，检查是否存在满足删除方块数条件的长度为 `len` 的子序列。
```cpp
bool check(int mid) {
    for (int i = 1; i <= m; i ++)
        for (int j = 0; j + mid - 1 < vec[i].size(); j ++)
            if (vec[i][j + mid - 1] - vec[i][j] + 1 - mid <= k)
                return true;
    return false;
}
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i ++) cin >> x, vec[x].emplace_back(i);
    int l = 0, r = n + 1, ans = 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    cout << ans << '\n';
    return 0;
}
```

### 最优关键思路或技巧
1. **数据结构选择**：使用链表（如链式前向星）或 `vector` 记录每种颜色方块位置，方便后续对单一颜色方块序列进行操作。链表在优化枚举颜色位置时可降低时间复杂度，`vector` 则实现简单，代码可读性好。
2. **双指针技巧**：通过双指针维护子串，动态调整子串范围，保证删除方块数不超过限制，同时有效更新最长子串长度。
3. **二分思想**：当答案具有单调性时，可二分答案，将求解问题转化为判断问题，通过设计高效的 `check` 函数确定二分的答案是否合法。

### 可拓展之处
1. **同类型题**：此类题目通常围绕序列中满足特定条件的子序列长度展开，可能会在删除元素条件、序列元素性质等方面变化。比如序列元素可能是字符，条件可能变为删除相邻元素等。
2. **类似算法套路**：遇到求满足一定限制条件下的最长子序列问题，可考虑枚举 + 双指针或二分答案的思路。先分析问题是否具有单调性，若有则二分答案；若无则尝试枚举可能情况，用双指针维护子序列。

### 洛谷相似题目推荐
1. **P1100 高低位交换**：涉及位运算和数据处理，与本题类似在于需要对数据进行特定操作以满足条件，可锻炼对数据的处理能力。
2. **P1909 买铅笔**：运用贪心思想解决购买方案选择问题，与本题都需要在多种情况中找出最优解，有助于提升贪心策略运用能力。
3. **P1088 火星人**：通过模拟和字典序相关操作解决问题，与本题类似之处在于对给定序列按一定规则进行处理并求解，可加强模拟和序列处理能力。 

---
处理用时：86.67秒