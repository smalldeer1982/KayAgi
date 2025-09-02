# 题目信息

# Armchairs

## 题目描述

There are $ n $ armchairs, numbered from $ 1 $ to $ n $ from left to right. Some armchairs are occupied by people (at most one person per armchair), others are not. The number of occupied armchairs is not greater than $ \frac{n}{2} $ .

For some reason, you would like to tell people to move from their armchairs to some other ones. If the $ i $ -th armchair is occupied by someone and the $ j $ -th armchair is not, you can tell the person sitting in the $ i $ -th armchair to move to the $ j $ -th armchair. The time it takes a person to move from the $ i $ -th armchair to the $ j $ -th one is $ |i - j| $ minutes. You may perform this operation any number of times, but these operations must be done sequentially, i. e. you cannot tell a person to move until the person you asked to move in the last operation has finished moving to their destination armchair.

You want to achieve the following situation: every seat that was initially occupied must be free. What is the minimum time you need to do it?

## 说明/提示

In the first test, you can perform the following sequence:

1. ask a person to move from armchair $ 1 $ to armchair $ 2 $ , it takes $ 1 $ minute;
2. ask a person to move from armchair $ 7 $ to armchair $ 6 $ , it takes $ 1 $ minute;
3. ask a person to move from armchair $ 4 $ to armchair $ 5 $ , it takes $ 1 $ minute.

In the second test, you can perform the following sequence:

1. ask a person to move from armchair $ 1 $ to armchair $ 4 $ , it takes $ 3 $ minutes;
2. ask a person to move from armchair $ 2 $ to armchair $ 6 $ , it takes $ 4 $ minutes;
3. ask a person to move from armchair $ 4 $ to armchair $ 5 $ , it takes $ 1 $ minute;
4. ask a person to move from armchair $ 3 $ to armchair $ 4 $ , it takes $ 1 $ minute.

In the third test, no seat is occupied so your goal is achieved instantly.

## 样例 #1

### 输入

```
7
1 0 0 1 0 0 1```

### 输出

```
3```

## 样例 #2

### 输入

```
6
1 1 1 0 0 0```

### 输出

```
9```

## 样例 #3

### 输入

```
5
0 0 0 0 0```

### 输出

```
0```

# AI分析结果

### 题目翻译
# 扶手椅

## 题目描述
有 $n$ 个扶手椅，从左到右编号为 $1$ 到 $n$。有些扶手椅有人坐（每个扶手椅最多坐一人），有些则空着。有人坐的扶手椅数量不超过 $\frac{n}{2}$。

出于某种原因，你想让人们从他们的扶手椅移到其他椅子上。如果第 $i$ 个扶手椅有人坐，而第 $j$ 个扶手椅是空的，你可以让坐在第 $i$ 个扶手椅上的人移到第 $j$ 个扶手椅上。一个人从第 $i$ 个扶手椅移动到第 $j$ 个扶手椅所需的时间是 $|i - j|$ 分钟。你可以进行任意次数的此操作，但这些操作必须按顺序进行，即你必须等到上一次操作中被要求移动的人到达目的地扶手椅后，才能再让其他人移动。

你希望达到这样的情况：最初有人坐的每个座位都空出来。你完成这个目标所需的最短时间是多少？

## 说明/提示
在第一个测试用例中，你可以按以下顺序操作：
1. 让一个人从扶手椅 $1$ 移动到扶手椅 $2$，这需要 $1$ 分钟；
2. 让一个人从扶手椅 $7$ 移动到扶手椅 $6$，这需要 $1$ 分钟；
3. 让一个人从扶手椅 $4$ 移动到扶手椅 $5$，这需要 $1$ 分钟。

在第二个测试用例中，你可以按以下顺序操作：
1. 让一个人从扶手椅 $1$ 移动到扶手椅 $4$，这需要 $3$ 分钟；
2. 让一个人从扶手椅 $2$ 移动到扶手椅 $6$，这需要 $4$ 分钟；
3. 让一个人从扶手椅 $4$ 移动到扶手椅 $5$，这需要 $1$ 分钟；
4. 让一个人从扶手椅 $3$ 移动到扶手椅 $4$，这需要 $1$ 分钟。

在第三个测试用例中，没有座位有人坐，所以你的目标瞬间达成。

## 样例 #1
### 输入
```
7
1 0 0 1 0 0 1
```
### 输出
```
3
```

## 样例 #2
### 输入
```
6
1 1 1 0 0 0
```
### 输出
```
9
```

## 样例 #3
### 输入
```
5
0 0 0 0 0
```
### 输出
```
0
```

### 算法分类
动态规划

### 综合分析与结论
这些题解主要围绕动态规划和最小费用最大流两种思路来解决问题。
- **动态规划思路**：多数题解采用动态规划，核心在于定义合适的状态，如 $f_{i,j}$ 表示前 $i$ 个人在前 $j$ 个椅子中找到空位的最小花费，通过状态转移方程 $f_{i,j}=\min(f_{i,j - 1}, f_{i - 1,j - 1}+|p_i - q_j|)$ 进行递推求解，其中 $p_i$ 是第 $i$ 个人的位置，$q_j$ 是第 $j$ 个空位的位置。
- **最小费用最大流思路**：将问题转化为图论中的最小费用最大流问题，通过构建图，设置源点、汇点，连接不同节点并赋予相应的流量和费用，最后跑最小费用最大流算法得到结果。

### 所选题解
- **作者：LRL65 (赞：14)，4星**
    - **关键亮点**：思路清晰，对动态规划的状态定义和转移方程解释详细，代码实现简洁明了。
    - **个人心得**：赛场上用贪心 WA 在了第 8 个点，赛后用 dp 过了，说明贪心策略在本题中不适用，需要使用动态规划来解决。
- **作者：oimaster (赞：7)，4星**
    - **关键亮点**：同样采用动态规划，对状态和递推式子的解释清晰，代码结构合理。
- **作者：Erica_N_Contina (赞：1)，4星**
    - **关键亮点**：先通过简单情况证明不交叉原则，为动态规划的状态设计提供了理论依据，思路严谨。

### 重点代码
#### 作者：LRL65
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[5005],f[5005][5005],b[5005];
int main() {
    cin>>n;
    memset(f,0x3f3f3f,sizeof(f));
    int cnt=0;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        if(a[i]==1)b[++cnt]=i;
    }
    for(int i=0;i<=n;i++)f[0][i]=0;
    for(int i=1;i<=cnt;i++) {
        for(int j=1;j<=n;j++) {
            if(a[j]==0)  
                f[i][j]=min(f[i][j-1],f[i-1][j-1]+abs(b[i]-j));
            else 
                f[i][j]=f[i][j-1];
        }
    }
    cout<<f[cnt][n]<<endl;
}
```
**核心实现思想**：先预处理人的位置，初始化 $f$ 数组，$f_{0,k}=0$。然后两层循环进行状态转移，根据当前位置是否有人，更新 $f_{i,j}$ 的值，最后输出 $f_{cnt,n}$。

#### 作者：oimaster
```cpp
#include<iostream>
#include<vector>
using namespace std;
int getc(int a,int b){
    if(a>=b)
        return a-b;
    return b-a;
}
int main(){
    int n;
    cin>>n;
    vector<int>si(1,-1);
    vector<int>pe(1,-1);
    for(int i=1;i<=n;++i){
        int x;
        cin>>x;
        if(x==1)
            pe.push_back(i);
        else
            si.push_back(i);
    }
    n=pe.size()-1;
    int m=si.size()-1;
    int dp[n+1][m+1];
    for(int i=1;i<=n;++i)
        for(int j=0;j<=m;++j)
            dp[i][j]=100000000;
    for(int j=0;j<=m;++j)
        dp[0][j]=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+getc(si[j],pe[i]));
    int minv=100000000;
    for(int i=1;i<=m;++i)
        minv=min(minv,dp[n][i]);
    cout<<minv<<endl;
}
```
**核心实现思想**：先预处理出人的下标和空椅子的下标，初始化 $dp$ 数组，$dp_{0,j}=0$。然后两层循环进行状态转移，更新 $dp_{i,j}$ 的值，最后找出 $dp_{n,i}$ 中的最小值输出。

#### 作者：Erica_N_Contina
```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rd read()
inline int read()
{
    int xx=0,ff=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
    return xx*ff;
}
inline void write(int out)
{
    if(out<0) putchar('-'),out=-out;
    if(out>9) write(out/10);
    putchar(out%10+'0');
}
const int N=5e3+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;
int q;
int t,ans,p[M],mn=INF,mx;
int cnt,r;
int f[N][N];
int a[M];
bool f2;
signed main(){
    n=rd;
    for(int i=1;i<=n;i++){
        a[i]=rd;
        if(a[i])p[++cnt]=i;
    }
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<=n;i++)f[0][i]=0;
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=n;j++){
            if(a[j])f[i][j]=f[i][j-1];
            else f[i][j]=min(f[i][j-1],f[i-1][j-1]+abs(p[i]-j));
        }
    }
    cout<<f[cnt][n];
    return 0;
}
```
**核心实现思想**：先预处理人的位置，初始化 $f$ 数组，$f_{0,k}=0$。然后两层循环进行状态转移，根据当前位置是否有人，更新 $f_{i,j}$ 的值，最后输出 $f_{cnt,n}$。

### 最优关键思路或技巧
- **动态规划状态设计**：通过定义合适的状态，如 $f_{i,j}$ 表示前 $i$ 个人在前 $j$ 个椅子中找到空位的最小花费，将问题分解为子问题进行求解。
- **不交叉原则**：证明让靠左的人坐靠左的椅子不劣，为动态规划的状态设计提供了理论依据。

### 拓展思路
同类型题或类似算法套路：
- 区间动态规划问题，如石子合并问题，通过定义区间状态进行状态转移。
- 分配类动态规划问题，如任务分配问题，将任务分配给不同的人，求最小代价。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，考察动态规划的基本思想。
- [P1176 路径计数2](https://www.luogu.com.cn/problem/P1176)：涉及动态规划和路径计数，需要考虑障碍物的影响。
- [P1854 花店橱窗布置](https://www.luogu.com.cn/problem/P1854)：动态规划的应用，需要合理定义状态和转移方程。

---
处理用时：72.88秒