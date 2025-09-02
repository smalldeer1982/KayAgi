# 题目信息

# Mirror Grid

## 题目描述

You are given a square grid with $ n $ rows and $ n $ columns. Each cell contains either $ 0 $ or $ 1 $ .

In an operation, you can select a cell of the grid and flip it (from $ 0 \to 1 $ or $ 1 \to 0 $ ). Find the minimum number of operations you need to obtain a square that remains the same when rotated $ 0^{\circ} $ , $ 90^{\circ} $ , $ 180^{\circ} $ and $ 270^{\circ} $ .

The picture below shows an example of all rotations of a grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1703E/df4a9e7a944efc8b4d2d665fb77f2a0392653bc5.png)

## 说明/提示

In the first test case, we can perform one operations to make the grid $ \begin{matrix}0 & 1 & 0\\ 1 & 1 & \color{red}{1}\\ 0 & 1 & 0\end{matrix} $ . Now, all rotations of the square are the same.

In the second test case, all rotations of the square are already the same, so we don't need any flips.

## 样例 #1

### 输入

```
5
3
010
110
010
1
0
5
11100
11011
01011
10011
11000
5
01000
10101
01010
00010
01001
5
11001
00000
11111
10110
01111```

### 输出

```
1
0
9
7
6```

# AI分析结果

### 题目内容
# 镜像网格

## 题目描述
给定一个具有 $n$ 行和 $n$ 列的正方形网格。每个单元格包含 $0$ 或 $1$。

在一次操作中，你可以选择网格中的一个单元格并翻转它（从 $0$ 变为 $1$ 或从 $1$ 变为 $0$）。求要得到一个在旋转 $0^{\circ}$、$90^{\circ}$、$180^{\circ}$ 和 $270^{\circ}$ 时保持不变的正方形，所需的最少操作次数。

下图展示了一个网格所有旋转的示例。
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1703E/df4a9e7a944efc8b4d2d665fb77f2a0392653bc5.png)

## 说明/提示
在第一个测试用例中，我们可以执行一次操作，使网格变为 $\begin{matrix}0 & 1 & 0\\ 1 & 1 & \color{red}{1}\\ 0 & 1 & 0\end{matrix}$ 。现在，该正方形的所有旋转都相同。

在第二个测试用例中，该正方形的所有旋转已经相同，因此我们不需要任何翻转操作。

## 样例 #1
### 输入
```
5
3
010
110
010
1
0
5
11100
11011
01011
10011
11000
5
01000
10101
01010
00010
01001
5
11001
00000
11111
10110
01111
```
### 输出
```
1
0
9
7
6
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于矩阵旋转的性质，找到矩阵中旋转后相互对应的点，通过统计这些对应点中0和1的数量，选择将它们变为全0或全1所需操作较少的情况来计算最少操作次数。不同题解的差异主要体现在遍历范围的选择和代码实现细节上。对于 $n$ 为奇数的情况，都意识到需要特殊处理中间部分。

### 所选的题解
- **作者：Halberd_Cease (5星)**
    - **关键亮点**：思路清晰，通过图形展示了 $n$ 为奇数和偶数时分别需要枚举的区域，代码实现简洁明了。
    - **核心代码**：
```cpp
void work(int x,int y)
{
    int xx=x - 1;int yy=y - 1;
    int x_1=1+yy,y_1=n - xx;
    int x_2=n - xx,y_2=n - yy;
    int x_3=n - yy,y_3=1+xx;
    int sum=mapp[x][y]+mapp[x_1][y_1]+mapp[x_2][y_2]+mapp[x_3][y_3];
    if(sum==0||sum==4)ans+=0;
    if(sum==1||sum==3)ans+=1;
    if(sum==2)ans+=2;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        ans = 0;
        cin>>n;
        char x;
        for(int i = 1;i <= n;i++)
        {
            for(int j = 1;j <= n;j++)
            {
                cin>>x;
                mapp[i][j]=x - '0';
            }
        }
        if(n%2==0)
        {
            for(int i = 1;i <= n/2;i++)
                for(int j = 1;j <= n/2;j++)
                    work(i,j);
        }
        else
        {
            for(int i = 1;i <= n/2;i++)
                for(int j = 1;j <= n/2 + 1;j++)
                    work(i,j);
        }
        cout<<ans<<'\n';
    }
}
```
    - **核心实现思想**：`work` 函数计算一个点及其旋转对应点的和，根据和的情况确定操作次数。`main` 函数根据 $n$ 的奇偶性，遍历相应区域调用 `work` 函数累加操作次数。

- **作者：lizhous (4星)**
    - **关键亮点**：分析详细，用图片展示了枚举区域和特殊处理的十字区域，代码逻辑清晰，对每个步骤有较好的注释。
    - **核心代码**：
```cpp
signed main() {
    scanf("%lld", &t);
    while (t--) {
        ans = 0; 
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++) {
            for (int z = 1; z <= n; z++) {
                scanf(" %c", &ch); 
                a[i][z] = ch - '0';
            }
        }
        cnt1 = cnt2 = 0; 
        for (int i = 1; (i << 1) <= n; i++) { 
            for (int z = 1; (z << 1) <= n; z++) {
                cnt1 = cnt2 = 0; 
                if (a[i][z] == 1) { 
                    cnt1++;
                } else {
                    cnt2++;
                }
                if (a[n - z + 1][i] == 1) {
                    cnt1++;
                } else {
                    cnt2++;
                }
                if (a[n - i + 1][n - z + 1] == 1) {
                    cnt1++;
                } else {
                    cnt2++;
                }
                if (a[z][n - i + 1] == 1) {
                    cnt1++;
                } else {
                    cnt2++;
                }
                ans += min(cnt1, cnt2); 
            }
        }
        cnt1 = cnt2 = 0;
        if (n & 1) { 
            for (int i = 1; (i << 1) <= n; i++) {
                cnt1 = cnt2 = 0;
                if (a[i][n / 2 + 1] == 1) { 
                    cnt1++;
                } else {
                    cnt2++;
                }
                if (a[n / 2 + 1][n - i + 1] == 1) {
                    cnt1++;
                } else {
                    cnt2++;
                }
                if (a[n / 2 + 1][i] == 1) {
                    cnt1++;
                } else {
                    cnt2++;
                }
                if (a[n - i + 1][n / 2 + 1] == 1) {
                    cnt1++;
                } else {
                    cnt2++;
                }
                ans += min(cnt1, cnt2); 
            }
        }
        cout << ans << endl; 
    }
}
```
    - **核心实现思想**：先读入矩阵，然后根据 $n$ 的奇偶性，分别遍历相应区域，统计每个点及其旋转对应点中0和1的数量，取较小值累加到答案中。

- **作者：xiaomuyun (4星)**
    - **关键亮点**：简洁地阐述了统计答案的方法，即通过四个对应点之和来确定操作次数，代码实现紧凑，有对避免重复计算的处理。
    - **核心代码**：
```cpp
int main(){
    scanf("%d",&t);
    while(t--){
        res = 0;
        scanf("%d",&n);
        for(int i = 1;i <= n;++i){
            for(int j = 1;j <= n;++j){
                char ch;
                cin>>ch;
                a[i][j]=(int)ch - '0';
            }
        }
        for(int i = 1;i <= (n + 1)/2;++i){
            for(int j = 1;j <= (n + 1)/2;++j){
                int cnt=a[i][j]+a[n - i + 1][n - j + 1]+a[j][n - i + 1]+a[n - j + 1][i];
                res+=min(4 - cnt,cnt);
                a[i][j]=a[n - i + 1][n - j + 1]=a[j][n - i + 1]=a[n - j + 1][i]=0;
            }
        }
        printf("%d\n",res);
    }
    return 0;
}
```
    - **核心实现思想**：读入矩阵后，遍历特定区域，计算每个点及其旋转对应点之和 `cnt`，通过 `min(4 - cnt, cnt)` 确定操作次数累加到 `res` 中，并将已处理的点设为0避免重复计算。

### 最优关键思路或技巧
1. **利用矩阵旋转对应点性质**：通过数学推导得出矩阵中一个点旋转后的对应点坐标，从而确定需要处理的点集。
2. **优化遍历范围**：根据 $n$ 的奇偶性，确定只需要遍历矩阵的部分区域（如左上角 $\frac{1}{4}$ 区域），就可以涵盖所有需要考虑的点，减少计算量。
3. **贪心策略**：对于每个点及其旋转对应点，选择将它们变为全0或全1中操作次数较少的方案，以达到整体最少操作次数。

### 同类型题或类似算法套路拓展
同类型题目通常围绕矩阵的变换（旋转、翻转等），并结合计数、最值求解等问题。类似算法套路是先找出变换后的对应关系，再根据题目要求（如求最值、可行性等），采用贪心、模拟等方法解决。例如对于一些要求矩阵经过多次变换后满足特定条件的题目，都可以先分析变换规律，再根据条件进行针对性计算。

### 洛谷相似题目推荐
1. **P1338 末日的传说**：涉及到对排列的变换和计算，与本题类似，需要找出变换后的对应关系并进行处理。
2. **P1443 马的遍历**：通过对棋盘上马的移动规则确定对应点，类似本题确定矩阵旋转后的对应点，然后进行广度优先搜索求解。
3. **P1002 过河卒**：在棋盘上根据棋子的移动规则计算路径数量，与本题确定矩阵元素变换后的对应关系并进行计算有相似之处。 

---
处理用时：68.48秒