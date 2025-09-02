# 题目信息

# Bargaining Table

## 题目描述

Bob wants to put a new bargaining table in his office. To do so he measured the office room thoroughly and drew its plan: Bob's office room is a rectangular room $ n×m $ meters. Each square meter of the room is either occupied by some furniture, or free. A bargaining table is rectangular, and should be placed so, that its sides are parallel to the office walls. Bob doesn't want to change or rearrange anything, that's why all the squares that will be occupied by the table should be initially free. Bob wants the new table to sit as many people as possible, thus its perimeter should be maximal. Help Bob find out the maximum possible perimeter of a bargaining table for his office.

## 样例 #1

### 输入

```
3 3
000
010
000
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 4
1100
0000
0000
0000
0000
```

### 输出

```
16
```

# AI分析结果

### 题目内容
# 谈判桌

## 题目描述
Bob想在他的办公室放置一张新的谈判桌。为此，他彻底测量了办公室并绘制了平面图：Bob的办公室是一个\(n×m\)米的矩形房间。房间的每平方米要么被一些家具占据，要么是空的。谈判桌是矩形的，并且放置时其边应与办公室墙壁平行。Bob不想改变或重新布置任何东西，所以桌子占据的所有方格最初都应该是空的。Bob希望新桌子能容纳尽可能多的人，因此其周长应最大。帮助Bob找出适合他办公室的谈判桌的最大可能周长。

## 样例 #1
### 输入
```
3 3
000
010
000
```
### 输出
```
8
```

## 样例 #2
### 输入
```
5 4
1100
0000
0000
0000
0000
```
### 输出
```
16
```

### 算法分类
枚举

### 综合分析与结论
这几道题解均针对小数据范围采用不同方式的枚举策略来解决问题。主要差异在于判断矩形是否符合放置条件的方法不同。
 - **灵光一闪的题解**：直接暴力枚举所有可能的矩形端点组合，通过`checker`函数遍历矩形内所有方格判断是否为空，计算周长并更新最大值。优点是思路直接简单，代码直观；缺点是时间复杂度较高，对每个矩形都要遍历内部所有方格。
 - **封禁用户的题解**：利用二维前缀和优化判断矩形是否为空的过程，通过前缀和快速判断一个矩形区域内是否全为0，再计算周长更新最大值。优点是减少了每次判断矩形是否为空的时间复杂度；缺点是前缀和的构建相对复杂，代码量稍多。
 - **小恐的题解**：先预处理每行每个位置前连续0的个数，然后枚举截取列的方法，再逐行判断该列区间是否全为0，若全为0则更新周长最大值。优点是通过预处理减少了重复判断，时间复杂度相对较低；缺点是思路相对复杂，理解成本稍高。
 - **ahawzlc的题解**：枚举矩形的左上端点和右下端点，通过4个`while`循环判断矩形边框是否有1，若边框无1则更新周长最大值。优点是只需判断边框，减少了部分无效判断；缺点是代码逻辑相对复杂，`while`循环嵌套较多。
 - **qzhwmjb的题解**：与ahawzlc思路类似，同样是枚举端点后判断边框是否有1，进而更新周长最大值。

### 所选的题解
 - **灵光一闪的题解**：★★★
    - **关键亮点**：思路简单直接，代码直观易懂，初学者容易理解。
    - **重点代码**：
```cpp
bool checker(int x1,int y1,int x2,int y2)
{
    for(int i=x1;i<=x2;i++)
        for(int j=y1;j<=y2;j++)
            if(a[i][j]=='1')
                return false;
    return true;
}
int C(int x1,int y1,int x2,int y2)
{
    return ((x2-x1+1)+(y2-y1+1))*2;
}
int ans;
int n,m;
int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>a[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            for(int k=0;k<n;k++)
                for(int l=0;l<m;l++)
                    if(checker(i,j,k,l)&&i<=k&&j<=l)
                        ans=max(ans,C(i,j,k,l));
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：`checker`函数用于判断以\((x1, y1)\)为左上角，\((x2, y2)\)为右下角的矩形内是否全为0，`C`函数计算矩形周长。主函数中通过四层循环枚举所有可能的矩形，调用上述函数判断并更新最大周长。
 - **封禁用户的题解**：★★★★
    - **关键亮点**：利用二维前缀和优化判断矩形是否为空的操作，减少时间复杂度。
    - **重点代码**：
```cpp
scanf("%d %d\n",&n,&m);
for (int i=1; i<=n; i++) {
    for (int j=1; j<=m; j++) {
        char ch=' ';
        scanf("%c",&ch);
        if (ch=='0') sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
        else sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+1;
    }
    scanf("\n");
}
for (int x=1; x<=n; x++)
    for (int y=1; y<=m; y++)
        for (int x_=x; x_<=n; x_++)
            for (int y_=y; y_<=m; y_++) {
                if ((sum[x_][y_]-sum[x_][y-1]-sum[x-1][y_]+sum[x-1][y-1])==0) {
                    ans=max(((x_-x+1)+(y_-y+1))*2,ans);
                }
            }
printf("%d\n",ans);
```
    - **核心实现思想**：先通过循环构建二维前缀和数组`sum`，之后通过四层循环枚举所有可能的矩形，利用前缀和公式判断矩形区域内是否全为0，若是则更新最大周长。
 - **小恐的题解**：★★★★
    - **关键亮点**：通过预处理每行连续0的个数，优化判断过程，降低时间复杂度。
    - **重点代码**：
```cpp
for(int i=1;i<=m;++i)
    scanf("%s",a[i]+1);
for(int i=1;i<=m;++i)
    for(int j=1;j<=n;++j)
    {
        if(a[i][j]=='1')
            qian[i][j]=0;
        else
            qian[i][j]=qian[i][j-1]+1;
    }
for(int i=1;i<=n;++i)
    for(int j=i;j<=n;++j)
    {
        int len=j-i+1;
        dp=0;
        for(int k=1;k<=m;++k)
        {
            if(qian[k][j]>=len)
                dp+=1,ans=max(2*(dp+len),ans);
            else
                dp=0;
        }
    }
```
    - **核心实现思想**：先读入数据，然后预处理出每行每个位置前连续0的个数存于`qian`数组。通过三层循环，外层两层枚举截取列的范围，内层循环逐行判断该列区间是否全为0，若全为0则更新周长最大值。

### 最优关键思路或技巧
在小数据范围下，利用二维前缀和或预处理每行连续0的个数，可以优化判断矩形是否符合条件的过程，从而降低时间复杂度。

### 拓展
同类型题通常是在矩形区域内进行特定条件的搜索或计算，类似算法套路包括利用前缀和优化区域判断，或者预处理某些信息减少重复计算。

### 洛谷相似题目推荐
 - [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过枚举和动态规划解决在一定预算内点菜的方案数问题，与本题在枚举思路上有相似之处。
 - [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串的枚举和匹配，可锻炼枚举相关的思维。
 - [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：利用广度优先搜索在棋盘上进行遍历，与本题在处理二维区域问题上有类似场景。

### 个人心得摘录与总结
 - **封禁用户**：调试二维前缀和花费半小时，意识到自己能力有待提高。总结出在小数据范围下，二维前缀和是解决此类问题不错的选择。这表明在处理二维区域问题时，二维前缀和虽构建稍复杂，但能有效优化判断过程，不过调试时需细心。 

---
处理用时：48.20秒