# 题目信息

# Chess Placing

## 题目描述

You are given a chessboard of size $ 1×n $ . It is guaranteed that  $ n $ is even. The chessboard is painted like this: "BWBW $ ... $ BW".

Some cells of the board are occupied by the chess pieces. Each cell contains no more than one chess piece. It is known that the total number of pieces equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/e98ace5c1ad627053f6404505602ba90672a171b.png).

In one step you can move one of the pieces one cell to the left or to the right. You cannot move pieces beyond the borders of the board. You also cannot move pieces to the cells that are already occupied.

Your task is to place all the pieces in the cells of the same color using the minimum number of moves (all the pieces must occupy only the black cells or only the white cells after all the moves are made).

## 说明/提示

In the first example the only possible strategy is to move the piece at the position $ 6 $ to the position $ 5 $ and move the piece at the position $ 2 $ to the position $ 3 $ . Notice that if you decide to place the pieces in the white cells the minimum number of moves will be $ 3 $ .

In the second example the possible strategy is to move ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/4f3653422b6429c3f89311497c438fd20547c4f8.png) in 4 moves, then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/6c4181624e2b8f95750df668d534111d8ee2005d.png) in 3 moves, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/74a8630d5d683f941562dca49b5d40bcde2fe1ef.png) in 2 moves and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/b97ec32af1cd5347877d0d15bd3de6cc845fde76.png) in 1 move.

## 样例 #1

### 输入

```
6
1 2 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10
1 2 3 4 5
```

### 输出

```
10
```

# AI分析结果

### 题目翻译
## 棋盘放置

### 题目描述
给定一个大小为 $1×n$ 的棋盘，保证 $n$ 是偶数。棋盘的颜色按照 “BWBW... BW” 的规律交替涂色。

棋盘的某些格子上放置了棋子，每个格子最多放置一个棋子，已知棋子的总数为 $\frac{n}{2}$。

每一步操作可以将一个棋子向左或向右移动一格，不能将棋子移出棋盘边界，也不能将棋子移动到已经有棋子的格子上。

你的任务是使用最少的移动步数，将所有棋子放置在相同颜色的格子中（所有棋子最终必须都位于黑色格子或都位于白色格子）。

### 说明/提示
在第一个样例中，唯一可能的策略是将位置 $6$ 的棋子移动到位置 $5$，将位置 $2$ 的棋子移动到位置 $3$。注意，如果选择将棋子放置在白色格子中，最少移动步数将为 $3$。

在第二个样例中，一种可能的策略是将某个棋子移动 $4$ 步，另一个棋子移动 $3$ 步，再一个棋子移动 $2$ 步，最后一个棋子移动 $1$ 步。

### 样例 #1
#### 输入
```
6
1 2 6
```
#### 输出
```
2
```

### 样例 #2
#### 输入
```
10
1 2 3 4 5
```
#### 输出
```
10
```

### 综合分析与结论
- **思路**：所有题解思路一致，均发现最终棋子放置只有奇数位置和偶数位置两种情况，通过分别计算棋子移动到这两种位置所需的总步数，取最小值得到答案。
- **算法要点**：
    1. 读取棋子初始位置并存储。
    2. 对棋子位置进行排序，确保棋子按顺序与目标位置对应。
    3. 分别计算棋子移动到奇数位置和偶数位置的总步数。
    4. 输出两种情况中总步数的最小值。
- **解决难点**：
    - 确定最终可能的放置情况：通过分析棋盘黑白相间的特性，得出只有奇数位置和偶数位置两种放置方式。
    - 保证棋子对应关系：由于棋子不能跨越，需对初始位置排序，使棋子从左到右与目标位置从左到右一一对应。

### 所选题解
- **作者：little_sun（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对变量的含义解释明确，便于理解。
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int a[101];
    int odd[101]/*奇数*/,even[101]/*偶数*/;
    int main()
    {
        int n;
        scanf("%d",&n);
        int ans1=0,ans2=0;/*奇,偶情况下的解*/
        for(int i=1;i<=n/2;i++)
        {
            scanf("%d",&a[i]);
        }
        sort(a+1,a+n/2+1);
        for(int i=1;i<=n/2;i++)
        {
            //算对应位
            odd[i]=i*2-1;
            even[i]=i*2;
            //更新答案
            ans1+=abs(odd[i]-a[i]);//记得绝对值
            ans2+=abs(even[i]-a[i]);
        }
        printf("%d",min(ans1,ans2));//最小值
        return 0;
    }
    ```
    核心实现思想：先读取棋子位置，排序后分别计算棋子移动到奇数位置和偶数位置的总步数，最后输出最小值。
- **作者：E1_de5truct0r（4星）**
    - **关键亮点**：思路阐述清晰，配有示意图，对两种情况的说明直观易懂。
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int a[105];
    int main()
    {
        //读入，不做解释
        int n; cin>>n;
        for(int i=1;i<=n/2;i++) cin>>a[i];
        sort(a+1,a+1+n/2); //数据可能会出现大小不按顺序的情况，需要重新排序 
        int sum1,sum2; sum1=sum2=0; 
        for(int i=1;i<=n/2;i++)
        {
            int a1=2*i-1,a2=2*i; //a1 为这一位应在的奇数位（情况1），a2 为这一位应在的偶数位（情况2）
            sum1+=abs(a[i]-a1); //如果放在奇数位的移动次数 
            sum2+=abs(a[i]-a2); //如果放在偶数位的移动次数 
        }
        cout<<min(sum1,sum2)<<endl; //取 min 
        return 0;
    }
    ```
    核心实现思想：读取棋子位置并排序，分别计算棋子移动到奇数位置和偶数位置的总步数，输出最小值。
- **作者：olegekei（4星）**
    - **关键亮点**：对棋子相对位置不变的特性进行了详细分析，为后续计算提供了理论支持。
    ```cpp
    #include<iostream>
    #include<algorithm> 
    using namespace std;
    int n,m;
    int a[111];
    int main(){
        cin>>n;
        m=n/2;
        for(int i=1;i<=m;i++)cin>>a[i];
        sort(a+1,a+m+1);
        int black=1,white=2;
        int ans1=0,ans2=0;
        for(int i=1;i<=m;i++){
            ans1+=abs(a[i]-black);
            ans2+=abs(a[i]-white);
            black+=2;white+=2;
        }
        cout<<min(ans1,ans2);
        return 0;
    }
    ```
    核心实现思想：读取棋子位置并排序，通过循环分别计算棋子移动到奇数位置和偶数位置的总步数，最后输出最小值。

### 最优关键思路或技巧
- **思维方式**：通过分析棋盘和棋子移动规则，确定最终的两种放置情况，将问题简化为计算两种情况下的最小移动步数。
- **代码实现技巧**：对棋子初始位置进行排序，保证棋子与目标位置的对应关系，避免复杂的位置判断。

### 可拓展之处
同类型题或类似算法套路：
- 其他棋盘类问题，如棋子在不同形状棋盘上的移动和放置。
- 区间分配问题，将元素分配到不同区间，使某种代价最小。

### 推荐洛谷题目
1. P1007 独木桥
2. P1199 三国游戏
3. P1223 排队接水

### 个人心得
- **作者：GusyNight**：解释了对棋子位置排序的原因，强调了对应关系的重要性，即每个棋子要找到自己对应的目标位置才能保证移动到正确位置。 

---
处理用时：38.40秒