# 题目信息

# [USACO18FEB] Snow Boots S

## 题目描述

农场的冬天到了，这意味着下雪了！从农舍到谷仓的路上有 $N$ 块地砖，方便地编号为 $1 \dots N$，第 $i$ 块地砖上覆盖了 $f_i$ 英尺的雪。

Farmer John 从第 $1$ 块地砖出发，必须到达第 $N$ 块地砖去叫醒奶牛。第 $1$ 块地砖被农舍的屋顶遮蔽，第 $N$ 块地砖被谷仓的屋顶遮蔽，因此这两块地砖上没有雪。但要踩在其他地砖上，Farmer John 需要穿靴子！

在他的恶劣天气背包中，Farmer John 有 $B$ 双靴子，编号为 $1 \dots B$。有些靴子比其他靴子更耐用，有些靴子比其他靴子更灵活。具体来说，第 $i$ 双靴子允许 Farmer John 在最多 $s_i$ 英尺深的雪中行走，并且每步最多可以移动 $d_i$ 块地砖。

不幸的是，靴子的打包方式使得 Farmer John 在任何时候只能访问最上面的一双靴子。因此，Farmer John 可以随时穿上最上面的一双靴子（丢弃旧靴子）或丢弃最上面的一双靴子（使下一双靴子可访问）。

Farmer John 只能在地砖上更换靴子。如果该地砖上有 $f$ 英尺的雪，那么他脱下的靴子和穿上的靴子都必须能够承受至少 $f$ 英尺的雪。他丢弃但未穿过的中间靴子不需要满足此限制。

请帮助 Farmer John 最小化浪费，确定他到达谷仓需要丢弃的最少靴子对数。假设 Farmer John 最初没有穿任何靴子。

## 说明/提示

题目来源：Brian Dean 和 Dhruv Rohatgi

## 样例 #1

### 输入

```
10 4
0 2 8 3 6 7 5 1 4 0
2 3
4 2
3 4
7 1```

### 输出

```
2
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕农场主穿靴子走过雪地的问题展开，解题方法主要分为动态规划（DP）和深度优先搜索（DFS）两大类。DP 类题解通过定义不同的状态数组来记录中间结果，逐步递推得到最终答案；DFS 类题解则通过递归的方式枚举所有可能的走法和换鞋情况，找到最少丢弃靴子数。

### 所选题解
- **作者：nihanchu (赞：18)，4星**
    - **关键亮点**：思路清晰，代码简洁，利用布尔数组 `f` 标记能否到达某块地砖，通过三重循环更新状态，时间复杂度为 $O(n^3)$，符合数据范围要求。
    - **个人心得**：作者提到一开始题意理解出了问题，导致想复杂了，提醒我们审题的重要性。
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#define maxn 500
using namespace std;
int d[maxn],b[maxn],a[maxn],n,m;
bool f[maxn];
int main()
{
  scanf("%d%d",&n,&m);
  for (int i=1;i<=n;i++) scanf("%d",&d[i]);
  for (int i=1;i<=m;i++) scanf("%d%d",&a[i],&b[i]);
  for (int i=1;i<=n;i++) f[i]=false;
  f[1]=true;
  int ans;
  for (int i=1;i<=m;i++)
  {
  	for (int j=1;j<=n;j++)
  	if (f[j]&&(a[i]>=d[j]))
  	{
  	 for (int k=j;k<=min(n,j+b[i]);k++)
	 if (a[i]>=d[k]) f[k]=true;	
	}
  	if (f[n]) {ans=i;break;}
  }
  printf("%d\n",ans-1);
  return 0;
}
```
核心实现思想：外层循环枚举靴子，中层循环枚举地砖，内层循环更新能到达的地砖状态。当能到达最后一块地砖时，记录当前靴子编号，最终答案为该编号减 1。

- **作者：communist (赞：17)，4星**
    - **关键亮点**：采用标准的 DP 思路，定义二维数组 `dp[i][j]` 表示穿着鞋子 `j` 到达位置 `i` 是否可行，通过四重循环进行状态转移，逻辑清晰。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=260;
int n,b,dp[maxn][maxn],f[maxn],s[maxn],d[maxn];
int main()
{
    scanf("%d%d",&n,&b);
    for(int i=1;i<=n;i++)
        scanf("%d",&f[i]);
    for(int i=1;i<=b;i++)
        scanf("%d%d",&s[i],&d[i]);
    dp[1][1]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=b;j++)
            if(dp[i][j])
                for(int k=j;k<=b;k++)
                    if(f[i]<=s[k])
                        for(int l=i+1;l<=min(n,i+d[k]);l++)
                            if(f[l]<=s[k])
                                dp[l][k]=1;
    for(int i=1;i<=b;i++)
        if(dp[n][i])
        {
            printf("%d\n",i-1);
            return 0;
        }
    return 0;
}
```
核心实现思想：先初始化 `dp[1][1]` 为 1，然后通过四重循环枚举位置、当前鞋子、更换的鞋子和走的步数，更新 `dp` 数组。最后枚举到达最后一块地砖的鞋子编号，输出最小编号减 1。

- **作者：KarL05 (赞：5)，4星**
    - **关键亮点**：使用 DFS 方法，通过递归枚举所有可能的走法和换鞋情况，利用 `visited` 数组避免重复搜索，思路直观。
```java
import java.io.*; 
import java.util.*; 

public class Main {
    static boolean[][] visited; 
    static int min = Integer.MAX_VALUE; 
    static int n; 
    static int b;
    static int f[];
    static int s[];
    static int d[]; 

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine()); 
        n = Integer.parseInt(st.nextToken());
        b = Integer.parseInt(st.nextToken());
        f = new int[n+1];
        s = new int[n+1];
        d = new int[n+1]; 
        visited = new boolean[n+1][n+1];
        st = new StringTokenizer(in.readLine()); 
        for (int i=1;i<=n;i++) {
            f[i]=Integer.parseInt(st.nextToken());
        }
        for (int i=1;i<=b;i++) {
            st = new StringTokenizer(in.readLine());
            s[i]=Integer.parseInt(st.nextToken());
            d[i]=Integer.parseInt(st.nextToken());
        } 
        dfs(1,1); 
        System.out.print(min); 
    }
    static void dfs(int pos, int boot) {
        if (visited[pos][boot]) {
            return;
        } 
        visited[pos][boot]=true;
        if (pos==n) {
            min = Math.min(min, boot-1);
            return;
        }
        for (int i=1;i<=d[boot];i++) { 
            if (pos+i>n) {
                return;
            }
            if (f[pos+i]>s[boot]) {
                continue;
            }
            dfs(pos+i,boot); 
        }
        for (int i=boot+1;i<=b;i++) { 
            if (s[i]<f[pos]) { 
                continue;
            }
            dfs(pos,i); 
        }
    }
}
```
核心实现思想：从起点开始 DFS，对于当前位置和靴子，枚举走的步数和更换的靴子，递归搜索。当到达终点时，更新最小丢弃靴子数。

### 最优关键思路或技巧
- **状态定义**：合理定义状态数组是解决动态规划问题的关键，如 `dp[i][j]` 表示穿着鞋子 `j` 到达位置 `i` 是否可行，或 `f[i]` 表示到达第 `i` 个地砖的最少用鞋数。
- **记忆化搜索**：在 DFS 中使用 `visited` 数组记录已经访问过的状态，避免重复搜索，提高效率。
- **剪枝优化**：在搜索过程中，当发现当前方案不是最优时，及时返回，减少不必要的计算。

### 可拓展之处
同类型题或类似算法套路：
- **路径规划问题**：如在地图中寻找最短路径，需要考虑不同的移动方式和限制条件。
- **资源分配问题**：如分配不同的资源以达到最优目标，需要考虑资源的属性和使用规则。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：0 - 1 背包问题，与本题的动态规划思想类似。
- [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)：经典的动态规划题目，通过递推求解最优路径。
- [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：深度优先搜索和记忆化搜索的结合，与本题的 DFS 思路相似。

### 个人心得总结
- **nihanchu**：一开始题意理解出错，导致想复杂了，提醒我们审题的重要性。
- **金银花露**：贪心思路会出错，应明确动态规划的方向，避免陷入错误的思维陷阱。

---
处理用时：53.21秒