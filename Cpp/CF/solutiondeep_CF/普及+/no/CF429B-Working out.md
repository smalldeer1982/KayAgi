# 题目信息

# Working out

## 题目描述

夏天要到了，$\texttt{dxbt}$ 和 $\texttt{songke}$ 决定去健身。它们要去的健身房可以被看做一个 $n$ 行 $m$ 列的矩阵。定义 $a_{i,j}$ 为在健身房第 $i$ 行第 $j$ 列运动后消耗的卡路里。

$\texttt{dxbt}$ 从 $\left(1,1\right)$ 出发，要去 $\left(n,m\right)$。并且，他只能从 $\left(i,j\right)$ 走到 $\left(i+1,j\right)$ 或 $\left(i,j+1\right)$；$\texttt{songke}$ 从 $\left(n,1\right)$ 出发，要去 $\left(1,m\right)$。并且，他只能从 $\left(i,j\right)$ 走到 $\left(i-1,j\right)$ 或 $\left(i,j+1\right)$。

由于 $\texttt{dxbt}$ 和 $\texttt{songke}$ 要聚在一起发张自拍，他们必须在健身房的某行某列相遇。由于他们没有好好健身，所以在自拍地点的卡路里消耗不计入总卡路里消耗值。

如果 $\texttt{dxbt}$ 和 $\texttt{songke}$ 中任何一个人完成了健身，则健身结束。你的任务是求出 $\texttt{dxbt}$ 和 $\texttt{songke}$ 可以消耗的最大总卡路里值。

另外，由于他们的健身速度不一定相同，所以可以走过的路线长度也不一定相同。

## 说明/提示

对于样例 $1$，$\texttt{dxbt}$ 可以选择：

$$
\left(1,1\right)\rightarrow\left(1,2\right)\rightarrow\left(2,2\right)\rightarrow\left(3,2\right)\rightarrow\left(3,3\right)
$$

$\texttt{songke}$ 可以选择：

$$
\left(3,1\right)\rightarrow\left(2,1\right)\rightarrow\left(2,2\right)\rightarrow\left(2,3\right)\rightarrow\left(1,3\right)
$$

## 样例 #1

### 输入

```
3 3
100 100 100
100 1 100
100 100 100
```

### 输出

```
800```

# AI分析结果

### 题目内容
夏天要到了，dxbt和songke决定去健身。它们要去的健身房可以被看做一个n行m列的矩阵。定义$a_{i,j}$为在健身房第i行第j列运动后消耗的卡路里。
dxbt从$(1,1)$出发，要去$(n,m)$。并且，他只能从$(i,j)$走到$(i + 1,j)$或$(i,j + 1)$；songke从$(n,1)$出发，要去$(1,m)$。并且，他只能从$(i,j)$走到$(i - 1,j)$或$(i,j + 1)$。
由于dxbt和songke要聚在一起发张自拍，他们必须在健身房的某行某列相遇。由于他们没有好好健身，所以在自拍地点的卡路里消耗不计入总卡路里消耗值。
如果dxbt和songke中任何一个人完成了健身，则健身结束。你的任务是求出dxbt和songke可以消耗的最大总卡路里值。
另外，由于他们的健身速度不一定相同，所以可以走过的路线长度也不一定相同。

### 说明/提示
对于样例1，dxbt可以选择：
$$(1,1)\rightarrow(1,2)\rightarrow(2,2)\rightarrow(3,2)\rightarrow(3,3)$$
songke可以选择：
$$(3,1)\rightarrow(2,1)\rightarrow(2,2)\rightarrow(2,3)\rightarrow(1,3)$$

### 样例 #1
#### 输入
```
3 3
100 100 100
100 1 100
100 100 100
```
#### 输出
```
800
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是通过动态规划的方法，用四个数组分别预处理出从四个角出发到每个点的最大卡路里值，然后枚举两人相遇的点，计算并比较不同相遇路径组合下的总卡路里值，从而得出最大值。
- **思路**：都基于两人必定在某点相遇且相遇点卡路里不计入的条件，考虑从四个角到相遇点的不同路径组合。
- **算法要点**：利用动态规划递推公式计算从四个角出发到各点的最大卡路里值，再通过枚举相遇点计算总卡路里值。
- **解决难点**：如何合理地设计动态规划的状态转移方程以及全面地考虑两人相遇的不同路径组合情况。

### 所选的题解
- **作者：Sakii (赞：12)  星级：5星  关键亮点**：思路清晰，结合图示说明两种相遇路径组合情况，代码简洁明了。
```cpp
#include<iostream>
#include <algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int dp1[1010][1010],dp2[1010][1010],dp3[1010][1010],dp4[1010][1010];//用四个dp数组存放最大值
int n,m;
int a[1010][1010];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
        scanf("%d ",&a[i][j]);
    }
}
memset(dp1,0,sizeof(dp1));
memset(dp2,0,sizeof(dp2));
memset(dp3,0,sizeof(dp3));
memset(dp4,0,sizeof(dp4));
     for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
        dp1[i][j]=a[i][j]+max(dp1[i-1][j],dp1[i][j-1]);}}
    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
        dp2[i][j]=a[i][j]+max(dp2[i+1][j],dp2[i][j+1]);}}
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m;j++){
        dp3[i][j]=a[i][j]+max(dp3[i+1][j],dp3[i][j-1]);}}
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
        dp4[i][j]=a[i][j]+max(dp4[i-1][j],dp4[i][j+1]);}}
    int x=0;
    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++)
        {
        x=max(x,dp1[i][j-1]+dp2[i][j+1]+dp3[i+1][j]+dp4[i-1][j]);
        x=max(x,dp1[i-1][j]+dp2[i+1][j]+dp3[i][j-1]+dp4[i][j+1]);}
    }
    printf("%d\n",x);
    return 0;
}
```
核心代码实现思想：通过四个嵌套循环分别计算从左上、右下、左下、右上四个方向到各点的最大卡路里值（即状态转移），再通过两层循环枚举相遇点，计算并更新最大总卡路里值。

- **作者：Allanljx (赞：4)  星级：4星  关键亮点**：思路阐述详细，对枚举过程和原因解释清晰。
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp1[1001][1001],dp2[1001][1001],dp3[1001][1001],dp4[1001][1001];
int n,m;
int a[1001][1001];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        	cin>>a[i][j];
    for(int i=1;i<=n;i++)//A从出发点到照相点 
        for(int j=1;j<=m;j++)
        	dp1[i][j]=a[i][j]+max(dp1[i-1][j],dp1[i][j-1]);
    for(int i=n;i>=1;i--)//A从终点到照相点 
        for(int j=m;j>=1;j--)
        	dp2[i][j]=a[i][j]+max(dp2[i+1][j],dp2[i][j+1]);
    for(int i=n;i>=1;i--)//B从出发点到照相点 
        for(int j=1;j<=m;j++)
        	dp3[i][j]=a[i][j]+max(dp3[i+1][j],dp3[i][j-1]);
    for(int i=1;i<=n;i++)//B从终点到照相点 
        for(int j=m;j>=1;j--)
        	dp4[i][j]=a[i][j]+max(dp4[i-1][j],dp4[i][j+1]);
    int x=0;//x记录总卡路里数 
    for(int i=2;i<n;i++)//枚举照相点
        for(int j=2;j<m;j++)
	        x=max(max(x,dp1[i][j-1]+dp2[i][j+1]+dp3[i+1][j]+dp4[i-1][j]),max(x,dp1[i-1][j]+dp2[i+1][j]+dp3[i][j-1]+dp4[i][j+1]));
    cout<<x<<endl;
    return 0;
}
```
核心代码实现思想：与Sakii类似，先通过四个嵌套循环进行动态规划预处理，再枚举相遇点计算最大总卡路里值。

- **作者：tuzhewen (赞：4)  星级：4星  关键亮点**：结合图示说明两种相遇路径情况，代码使用了自定义的宏定义简化循环书写。
```cpp
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define uF(i,l,r) for(register int i=l;i>=r;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
using namespace std;
const int N=1005;
int n,m;
int mp[N][N];
ll ans,maxn,dp[N][N],dp1[N][N],dp2[N][N],dp3[N][N];
int main() {
	scanf("%d%d",&n,&m);
	F(i,1,n) F(j,1,m) scanf("%d",&mp[i][j]);
	F(i,1,n) F(j,1,m) dp[i][j]=mp[i][j]+max(dp[i][j-1],dp[i-1][j]);//左上
	F(i,1,n) uF(j,m,1) dp1[i][j]=mp[i][j]+max(dp1[i][j+1],dp1[i-1][j]);//右上
	uF(i,n,1) F(j,1,m) dp2[i][j]=mp[i][j]+max(dp2[i+1][j],dp2[i][j-1]);//左下
	uF(i,n,1) uF(j,m,1) dp3[i][j]=mp[i][j]+max(dp3[i+1][j],dp3[i][j+1]);//右下
	F(i,2,n-1) F(j,2,m-1) /*枚举出发点*/maxn=max({maxn,dp[i-1][j]+dp1[i][j+1]+dp2[i][j-1]+dp3[i+1][j],dp[i][j-1]+dp1[i-1][j]+dp2[i+1][j]+dp3[i][j+1]});//计算两种走法
	printf("%lld\n",maxn);
	return 0;
}
```
核心代码实现思想：利用宏定义的循环进行动态规划预处理四个方向到各点的最大卡路里值，然后枚举相遇点计算最大总卡路里值。

### 最优关键思路或技巧
利用动态规划，通过四个数组分别记录从四个角出发到每个点的最大卡路里值，全面考虑两人相遇的不同路径组合，并且在代码实现上，合理利用循环结构和状态转移方程来高效计算结果。

### 可拓展之处
同类型题通常围绕在矩阵中不同起点和终点的路径规划，且路径存在一定限制和特殊条件（如路径相交、经过点的权值计算等）。类似算法套路是先通过动态规划预处理从不同起点到各点的状态值，再根据题目特殊条件枚举相关点来计算最终结果。

### 推荐洛谷题目
- [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)：同样是在矩阵中两条路径的问题，不过限制条件和本题略有不同，需要考虑两条路径不能相交等情况，锻炼动态规划的应用能力。
- [P1280尼克的任务](https://www.luogu.com.cn/problem/P1280)：虽然场景不同，但也是通过动态规划解决在时间序列上的任务安排和最优值计算问题，有助于加深对动态规划的理解。
- [P1434 [SHOI2002]滑雪](https://www.luogu.com.cn/problem/P1434)：在矩阵上进行动态规划，根据相邻元素关系确定路径，与本题在矩阵上进行动态规划求解的思路类似。

### 个人心得
无。 

---
处理用时：97.85秒