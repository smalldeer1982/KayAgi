# 题目信息

# Maximal Binary Matrix

## 题目描述

You are given matrix with $ n $ rows and $ n $ columns filled with zeroes. You should put $ k $ ones in it in such a way that the resulting matrix is symmetrical with respect to the main diagonal (the diagonal that goes from the top left to the bottom right corner) and is lexicographically maximal.

One matrix is lexicographically greater than the other if the first different number in the first different row from the top in the first matrix is greater than the corresponding number in the second one.

If there exists no such matrix then output -1.

## 样例 #1

### 输入

```
2 1
```

### 输出

```
1 0 
0 0 
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 0 0 
0 1 0 
0 0 0 
```

## 样例 #3

### 输入

```
2 5
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
# 最大二进制矩阵

## 题目描述
给定一个由 $n$ 行 $n$ 列的零填充的矩阵。你需要在其中放置 $k$ 个 $1$，使得得到的矩阵关于主对角线（从左上角到右下角的对角线）对称，并且字典序最大。

如果第一个矩阵中从顶部开始的第一个不同行中的第一个不同数字大于第二个矩阵中的相应数字，则一个矩阵在字典序上大于另一个矩阵。

如果不存在这样的矩阵，则输出 -1。

## 样例 #1
### 输入
```
2 1
```
### 输出
```
1 0 
0 0 
```

## 样例 #2
### 输入
```
3 2
```
### 输出
```
1 0 0 
0 1 0 
0 0 0 
```

## 样例 #3
### 输入
```
2 5
```
### 输出
```
-1
```

### 综合分析与结论
这些题解主要围绕如何在 $n\times n$ 的矩阵中放置 $k$ 个 $1$，使矩阵关于主对角线对称且字典序最大展开。思路大致可分为深度优先搜索（DFS）和贪心算法两类。

- **DFS 思路**：通过递归遍历矩阵的每个位置，尝试放置 $1$ 并回溯，同时处理对称和字典序比较的问题。
- **贪心思路**：从矩阵的左上角开始，按照一定规则优先放置 $1$，以保证字典序最大，同时满足对称性要求。

### 所选题解
- **作者：frankchenfu（4星）**
    - **关键亮点**：思路清晰，通过递归函数实现贪心策略，对不同剩余 $1$ 的数量进行分类讨论，代码简洁易懂。
    - **核心代码**：
```cpp
#include<cstdio>
#include<cstring>
const int MAXN=110;
int a[MAXN][MAXN];

void solve(int n,int pos,int k)
{
    if(k==1)
    {
        a[pos][pos]=1;
        return;
    }
    if(k==0)
        return;
    if(k<=(n<<1)-1)
    {
        for(int i=pos;i<=pos+(k-1>>1);i++)
            a[pos][i]=a[i][pos]=1;
        solve(n-1,pos+1,(k&1)^1);
    }
    else
    {
        for(int i=pos;i<=pos+n-1;i++)
            a[pos][i]=a[i][pos]=1;
        solve(n-1,pos+1,k-(n<<1)+1);
    }
    return; 
}

int main()
{
    int n,k;scanf("%d%d",&n,&k);
    if(k>n*n)
    {
        puts("-1");
        return 0;
    }
    solve(n,1,k);
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=n;j++)
            printf("%d ",a[i][j]);
    return 0;
}
```
    - **核心实现思想**：定义递归函数 `solve`，根据剩余 $1$ 的数量 `k` 和当前处理的矩阵宽度 `n` 进行不同的处理。当 `k` 大于当前行可填充的数量时，填满当前行并递归处理剩余部分；当 `k` 小于等于当前行可填充的数量时，尽可能对称填充并递归处理剩余部分。

- **作者：wflhx2011（4星）**
    - **关键亮点**：思路直接，从矩阵的左上角开始依次遍历，根据对称性和剩余 $1$ 的数量进行填充，代码简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][105],f;
int main()
{
    long long n,k;
    cin>>n>>k;
    if(n*n<k)
    {
        cout<<-1;
        return 0;
    }
    if(k==0)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
                cout<<0<<" ";
            cout<<endl;
        }
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(a[i][j]==0)
                if(i==j)
                    a[i][j]=1,k--;
                else
                    if(k==1)
                        if(a[i][i]==1)
                            a[i+1][i+1]=1,k--;
                        else
                            a[i][i]=1,k--;
                    else
                        a[i][j]=a[j][i]=1,k-=2;
                if(k==0)
                {
                    f=1;
                    break;
                }
        }
        if(f==1)
            break;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }	
    return 0;
}
```
    - **核心实现思想**：通过两层循环遍历矩阵，当当前位置未填充且为对角线时，填充一个 $1$；当不为对角线且剩余 $1$ 的数量大于 $1$ 时，填充两个对称的 $1$；当剩余 $1$ 的数量为 $1$ 时，将其填充在对角线上。

- **作者：_Lazy_zhr_（4星）**
    - **关键亮点**：代码结构清晰，通过遍历 $i \leq j$ 的点，根据位置和剩余 $1$ 的数量进行填充，处理简单高效。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
char ans[105][105];
void init(){ for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ans[i][j]='0'; }
void write(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout<<ans[i][j]<<" ";
        cout<<"\n";
    }
}
void solve(){
    cin>>n>>k;
    init();
    if(k>n*n){
        cout<<"-1\n";
        return ;
    }
    if(!k){
        write();
        return ;
    }
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++){
        if(i==j) ans[i][j]='1',k--;
        else ans[i][j]=ans[j][i]='1',k-=2;
        if(k==0){
            write();
            return ;
        }
        else if(k<0){
            ans[i][j]=ans[j][i]='0';
            ans[i+1][i+1]='1';
            write();
            return ;
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T=1;
//	cin>>T;
    while(T--) solve();
    return 0;
}
```
    - **核心实现思想**：先初始化矩阵为全 $0$，然后遍历 $i \leq j$ 的点，当为对角线时填充一个 $1$，否则填充两个对称的 $1$。当剩余 $1$ 的数量为 $0$ 时输出矩阵，当剩余 $1$ 的数量小于 $0$ 时调整填充位置并输出矩阵。

### 最优关键思路或技巧
- **贪心策略**：从矩阵的左上角开始，优先填充靠前的位置，以保证字典序最大。同时，根据对称性要求，在填充非对角线位置时，同时填充对称位置。
- **特判处理**：在开始填充前，先判断 $k$ 是否大于 $n^2$，若大于则直接输出 -1；若 $k$ 为 $0$，则输出全 $0$ 矩阵。

### 拓展思路
同类型题目可能会有不同的矩阵操作要求，如关于副对角线对称、旋转对称等，解题思路仍然是根据对称性要求和字典序规则进行填充。类似算法套路可以应用于其他矩阵填充问题，如在矩阵中放置特定形状的图案等。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：考察矩阵填充和坐标处理。
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：考察字典序的比较和排序。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：考察区间操作和标记处理。

### 个人心得摘录与总结
- **封禁用户**：模拟赛中把送分题打成爆蛋，用 DFS 骗分意外得到正解，说明在考试时可以尝试一些简单的算法来获取部分分数。
- **Base_ring_tree**：被 $k$ 为 $0$ 的情况卡疯，提醒我们在解题时要注意边界条件的处理，避免遗漏特殊情况。

---
处理用时：57.03秒