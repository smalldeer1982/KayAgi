# 题目信息

# Thorns and Coins

## 题目描述

你发现了一个世界。这是一个有 $n$ 个连续单元格的路径，每个单元格可以是空的、含有荆棘或者硬币。在一次移动中，你可以沿着路径向右移动一格或两格，前提是目标单元格不含有荆棘（并且属于路径）。如果你移动到的单元格正好含有硬币的单元格，你就会捡起它。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/bbfdc346db7373b864d2642fd35cef4a577781a2.png)
 
上图中，绿色箭头表示合法移动，红色箭头表示非法移动。你想要在这个发现的世界中收集尽可能多的硬币。你从路径的最左边单元格开始，找出你可以在这个世界中收集的最大硬币数量。


第二个示例的图片如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/e0c47ff41c71ce332d7b876f950ed50eee6c4f4d.png)

第三个示例的图片如下：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/880dc20f87f4adb0891a434fca6a4717f38a2a7e.png)

## 样例 #1

### 输入

```
3
10
.@@*@.**@@
5
.@@@@
15
.@@..@***..@@@*```

### 输出

```
3
4
3```

# AI分析结果

### 题目翻译
# 荆棘与硬币

## 题目描述
你发现了一个世界。这是一条由 $n$ 个连续单元格组成的路径，每个单元格可能为空、有荆棘或者有硬币。在一次移动中，你可以沿着路径向右移动一格或两格，前提是目标单元格不包含荆棘（且在路径范围内）。如果你移动到的单元格恰好有硬币，你就会捡起它。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/bbfdc346db7373b864d2642fd35cef4a577781a2.png)

上图中，绿色箭头表示合法移动，红色箭头表示非法移动。你想在这个发现的世界中收集尽可能多的硬币。你从路径最左边的单元格开始，找出你在这个世界中可以收集的最大硬币数量。

第二个示例的图片如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/e0c47ff41c71ce332d7b876f950ed50eee6c4f4d.png)

第三个示例的图片如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1932A/880dc20f87f4adb0891a434fca6a4717f38a2a7e.png)

## 样例 #1

### 输入
```
3
10
.@@*@.**@@
5
.@@@@
15
.@@..@***..@@@*
```

### 输出
```
3
4
3
```

### 综合分析与结论
这些题解主要围绕模拟和动态规划两种思路来解决问题。

- **模拟思路**：多数题解采用模拟的方法，核心是遍历路径字符串，遇到硬币就计数，遇到连续两个荆棘就停止遍历，因为无法跨越连续两个荆棘。
- **动态规划思路**：使用动态规划数组 `dp` 记录到每个位置能获得的最多金币数，使用 `b` 数组记录每个位置是否可达，通过状态转移更新 `dp` 数组。

**解决难点**：关键在于处理连续两个荆棘的情况，因为这会导致无法继续前进，需要在遍历过程中及时判断并停止。

### 题解评分及分析
所有题解均不足 4 星，通用建议与扩展思路如下：
- **通用建议**：在模拟思路中，代码实现较为简单，但要注意边界条件的处理，避免数组越界。动态规划思路虽然更具通用性，但对于本题数据范围较小的情况，可能会增加代码复杂度。
- **扩展思路**：可以考虑对路径进行预处理，标记出所有连续荆棘的位置，这样在遍历过程中可以更快速地判断是否遇到无法跨越的障碍。对于动态规划思路，可以尝试优化空间复杂度，减少不必要的数组使用。

### 重点代码
#### 模拟思路（以 Hutao__ 的题解为例）
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        int n,ans=0;
        string s;
        cin>>n>>s;
        int f=0;
        for(int i=0;i<n;i++){
            if(s[i]=='@')ans++,f=0;
            else if(s[i]=='*')f++;
            else f=0;
            if(f==2)break;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```
**核心实现思想**：遍历路径字符串，用 `f` 记录连续荆棘的数量，遇到硬币 `@` 就增加计数 `ans` 并重置 `f`，遇到荆棘 `*` 就增加 `f`，遇到空地就重置 `f`，当 `f` 达到 2 时停止遍历。

#### 动态规划思路（以 maokaiyu 的题解为例）
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
I t,n,dp[60],ans;
char a[60];
bool b[60];
I main(){
    scanf("%d",&t);
    for(;t--;){
        scanf("%d%s",&n,a + 1);
        memset(dp,0,sizeof(dp));
        memset(b,false,sizeof(b));
        ans = 0;
        b[1] = true;
        dp[1] = (a[1] == '@');
        for(I i = 1;i <= n;i++){
            if(b[i]){
                if(a[i] == '@') dp[i]++;
                if(a[i + 1] != '*'){
                    b[i + 1] = true;
                    dp[i + 1] = max(dp[i + 1],dp[i]);
                }
                if(a[i + 2] != '*'){
                    b[i + 2] = true;
                    dp[i + 2] = max(dp[i + 2],dp[i]); 
                }
            }
            ans = max(ans,dp[i]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：使用 `b` 数组记录每个位置是否可达，`dp` 数组记录到每个位置能获得的最多金币数。从起点开始，根据当前位置的可达性和下一个、下下一个位置是否有荆棘，更新 `b` 数组和 `dp` 数组，最后取 `dp` 数组中的最大值作为结果。

### 推荐洛谷题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：涉及路径规划和动态规划，与本题的路径移动和状态转移有相似之处。
2. [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：经典的动态规划问题，通过状态转移求解最优路径。
3. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：动态规划的应用，与本题的状态转移和最优解求解思路类似。

### 个人心得
题解中未包含个人心得。

---
处理用时：44.17秒