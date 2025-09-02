# 题目信息

# Switches and Lamps

## 题目描述

You are given $ n $ switches and $ m $ lamps. The $ i $ -th switch turns on some subset of the lamps. This information is given as the matrix $ a $ consisting of $ n $ rows and $ m $ columns where $ a_{i,j}=1 $ if the $ i $ -th switch turns on the $ j $ -th lamp and $ a_{i,j}=0 $ if the $ i $ -th switch is not connected to the $ j $ -th lamp.

Initially all $ m $ lamps are turned off.

Switches change state only from "off" to "on". It means that if you press two or more switches connected to the same lamp then the lamp will be turned on after any of this switches is pressed and will remain its state even if any switch connected to this lamp is pressed afterwards.

It is guaranteed that if you push all $ n $ switches then all $ m $ lamps will be turned on.

Your think that you have too many switches and you would like to ignore one of them.

Your task is to say if there exists such a switch that if you will ignore (not use) it but press all the other $ n-1 $ switches then all the $ m $ lamps will be turned on.

## 样例 #1

### 输入

```
4 5
10101
01000
00111
10000
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 5
10100
01000
00110
00101
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
# 开关与灯

## 题目描述
给定 $n$ 个开关和 $m$ 盏灯。第 $i$ 个开关可以打开一部分灯，这些信息用一个 $n$ 行 $m$ 列的矩阵 $a$ 表示，其中若 $a_{i,j}=1$，则表示第 $i$ 个开关可以打开第 $j$ 盏灯；若 $a_{i,j}=0$，则表示第 $i$ 个开关与第 $j$ 盏灯没有连接。

初始时，所有 $m$ 盏灯都是关闭的。

开关的状态只能从“关闭”变为“打开”。这意味着，如果有两个或更多的开关连接到同一盏灯，那么在按下任何一个连接到该灯的开关后，灯就会被打开，并且即使之后再按下任何连接到该灯的开关，灯的状态也会保持不变。

保证当按下所有 $n$ 个开关时，所有 $m$ 盏灯都会被打开。

你认为开关太多了，想忽略其中一个开关。

你的任务是判断是否存在这样一个开关，如果你忽略（不使用）它，但按下其余的 $n - 1$ 个开关，所有 $m$ 盏灯仍然可以被打开。

## 样例 #1
### 输入
```
4 5
10101
01000
00111
10000
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
4 5
10100
01000
00110
00101
```
### 输出
```
NO
```

### 综合分析与结论
这些题解的核心思路基本一致，都是先统计每盏灯能被多少个开关控制，再枚举去掉每个开关，检查去掉该开关后是否所有灯仍能被打开。部分题解在代码实现上有差异，如使用 `bitset` 优化位运算，但整体算法框架相同。

### 题解评分与选择
- **ztyo_zysclown（5星）**：思路清晰，代码简洁易懂，变量命名直观，易于理解。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define zyto_zysclown return 0
int n,m;
int qwe[111000];//判断每个灯有多少个开关相连。 
char op[5500][5500];
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>op[i][j];
            if(op[i][j]=='1'){
                qwe[j]++;
            }
        }
    } 
    for(int i=1;i<=n;i++){
        bool b=false;
        for(int j=1;j<=m;j++){
            if(op[i][j]=='1'&&qwe[j]==1){
                b=true;
            }
        }
        if(!b){
            cout<<"YES";
            return 0;
        }
    }
    cout<<"NO";
    zyto_zysclown;
}
```
核心实现思想：先遍历矩阵统计每盏灯连接的开关数，再枚举每个开关，检查去掉该开关后是否有灯无法被打开。

- **AutumnKite（4星）**：思路清晰，对时间复杂度进行了分析和优化，代码规范。
```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cctype>
using namespace std;
const int N = 2005;
int n, m, cnt[N];
char a[N][N];
int main(){
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            while (!isdigit(a[i][j] = getchar()));
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            cnt[j] += a[i][j] ^ '0'; // 统计cnt
    for (register int i = 1; i <= n; ++i){
        register bool bo = true;
        for (register int j = 1; j <= m; ++j)
            if (a[i][j] == '1' && cnt[j] == 1) bo = false; // 直接判断即可
        if (bo) return printf("YES"), 0;
    }
    return printf("NO"), 0;
}
```
核心实现思想：同样先统计每盏灯连接的开关数，然后枚举开关，判断去掉该开关后是否影响所有灯的开启。

- **xiaozeyu（4星）**：思路清晰，将问题转化为判断点的入度，代码结构良好。
```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define f(a) ((a)*(a))
#define p(x) printf("%lld ",(x))
#define P() puts("")
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
const int maxn=2010;
const int maxm=100010;
int n,m,d[maxm];
char a[maxn][maxn];
signed main()
{
    n=read();m=read();
    For(i,1,n)
        For(j,1,m)
        {
            a[i][j]=getchar();
            while(!isdigit(a[i][j])) a[i][j]=getchar();
            if(a[i][j]=='1') d[j]++;
        }
    bool flag;
    For(i,1,n)
    {
        flag=true;
        For(j,1,m) if(d[j]==1&&a[i][j]=='1') flag=false;
        if(flag)
        {
            puts("YES");
            return 0;	
        }
    }
    puts("NO");
}
```
核心实现思想：把开关和灯的关系看作图，统计每个点（灯）的入度，枚举开关，判断去掉该开关后是否有入度为 0 的点。

### 最优关键思路或技巧
- 统计每盏灯连接的开关数，避免重复计算，将时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。
- 部分题解使用 `bitset` 优化位运算，提高效率。

### 拓展思路
同类型题可考虑增加开关和灯的状态变化规则，如开关状态可反复切换，或灯有多种状态等。类似算法套路可用于解决图论中的连通性问题，通过统计节点的入度、出度来判断节点的重要性。

### 洛谷相似题目推荐
- P1118 [USACO06FEB]Backward Digit Sums G
- P1036 选数
- P1057 传球游戏

### 个人心得摘录
本题题解中未包含个人心得。 

---
处理用时：39.98秒