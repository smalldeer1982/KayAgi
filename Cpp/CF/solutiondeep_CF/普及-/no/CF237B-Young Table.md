# 题目信息

# Young Table

## 题目描述

You've got table $ a $ , consisting of $ n $ rows, numbered from 1 to $ n $ . The $ i $ -th line of table $ a $ contains $ c_{i} $ cells, at that for all $ i $ $ (1&lt;i<=n) $ holds $ c_{i}<=c_{i-1} $ .

Let's denote $ s $ as the total number of cells of table $ a $ , that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF237B/41032ee9d28de3347d7865d06640fb12d664cefb.png). We know that each cell of the table contains a single integer from $ 1 $ to $ s $ , at that all written integers are distinct.

Let's assume that the cells of the $ i $ -th row of table $ a $ are numbered from 1 to $ c_{i} $ , then let's denote the number written in the $ j $ -th cell of the $ i $ -th row as $ a_{i,j} $ . Your task is to perform several swap operations to rearrange the numbers in the table so as to fulfill the following conditions:

1. for all $ i,j $ $ (1&lt;i<=n; 1<=j<=c_{i}) $ holds $ a_{i,j}&gt;a_{i-1,j} $ ;
2. for all $ i,j $ $ (1<=i<=n; 1&lt;j<=c_{i}) $ holds $ a_{i,j}&gt;a_{i,j-1} $ .

In one swap operation you are allowed to choose two different cells of the table and swap the recorded there numbers, that is the number that was recorded in the first of the selected cells before the swap, is written in the second cell after it. Similarly, the number that was recorded in the second of the selected cells, is written in the first cell after the swap.

Rearrange the numbers in the required manner. Note that you are allowed to perform any number of operations, but not more than $ s $ . You do not have to minimize the number of operations.

## 样例 #1

### 输入

```
3
3 2 1
4 3 5
6 1
2
```

### 输出

```
2
1 1 2 2
2 1 3 1
```

## 样例 #2

### 输入

```
1
4
4 3 2 1
```

### 输出

```
2
1 1 1 4
1 2 1 3
```

# AI分析结果

### 题目内容
# Young Table

## 题目描述
你有一个表格 $a$，由 $n$ 行组成，行号从 1 到 $n$。表格 $a$ 的第 $i$ 行包含 $c_{i}$ 个单元格，并且对于所有 $i$ （$1 < i \leq n$）都有 $c_{i} \leq c_{i - 1}$。

我们用 $s$ 表示表格 $a$ 的单元格总数，即 $\sum_{i = 1}^{n}c_{i}$。我们知道表格的每个单元格都包含一个从 1 到 $s$ 的整数，并且所有写入的整数都是不同的。

假设表格 $a$ 第 $i$ 行的单元格从 1 到 $c_{i}$ 编号，那么我们用 $a_{i, j}$ 表示第 $i$ 行第 $j$ 个单元格中写入的数字。你的任务是执行几次交换操作来重新排列表格中的数字，以满足以下条件：
1. 对于所有 $i, j$（$1 < i \leq n$；$1 \leq j \leq c_{i}$），都有 $a_{i, j} > a_{i - 1, j}$；
2. 对于所有 $i, j$（$1 \leq i \leq n$；$1 < j \leq c_{i}$），都有 $a_{i, j} > a_{i, j - 1}$。

在一次交换操作中，你可以选择表格中的两个不同单元格，并交换记录在那里的数字，即在交换之前记录在第一个所选单元格中的数字，在交换之后被写入第二个单元格。类似地，在交换之前记录在第二个所选单元格中的数字，在交换之后被写入第一个单元格。

以所需的方式重新排列数字。请注意，你可以执行任意数量的操作，但不超过 $s$ 次。你不必最小化操作次数。

## 样例 #1
### 输入
```
3
3 2 1
4 3 5
6 1
2
```
### 输出
```
2
1 1 2 2
2 1 3 1
```

## 样例 #2
### 输入
```
1
4
4 3 2 1
```
### 输出
```
2
1 1 1 4
1 2 1 3
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解的核心思路都是利用题目对操作步数限制宽松（不超过 $s$ 次）这一条件，采用较为暴力的模拟交换方式来解决问题。各题解都基于表格内数字是 1 到 $s$ 的全排列这一特性，先记录原数字位置，再按升序排列的理想状态进行交换。主要区别在于代码实现的细节，如记录位置的方式、交换逻辑的具体实现等。

### 所选的题解
 - **作者：__DayLight__ 星级：4星**
    - **关键亮点**：思路清晰，先将表格数字升序排序，通过对比排序后与原表格数字位置，确定交换操作，代码注释详细，便于理解。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s;
int c[55],x[2505],y[2505],p[2505],q[2505];
int t[55][55];
int a[2505];
signed main(){
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>c[i];
    for(int i=1; i<=n; i++)
        for(int j=1; j<=c[i]; j++)
        {
            cin>>a[++s];
            t[i][j]=a[s];
        }
    sort(a+1,a+1+s);
    s=0; 
    for(int i=1; i<=n; i++)
        for(int j=1; j<=c[i]; j++)
        {
            s++;
            if(a[s]!=t[i][j])
            {
                m++;
                for(int k=1; k<=n; k++)
                    for(int l=1; l<=c[k]; l++)
                    {
                        if(a[s]==t[k][l])x[m]=k,y[m]=l;
                        if(t[i][j]==t[k][l])p[m]=k,q[m]=l;
                    }
                swap(t[x[m]][y[m]],t[p[m]][q[m]]);
            }
        }
    cout<<m<<'\n';
    for(int i=1; i<=m; i++)
        cout<<x[i]<<' '<<y[i]<<' '<<p[i]<<' '<<q[i]<<'\n';
    return 0;
} 
```
    - **核心实现思想**：先将输入表格数据存入 `a` 数组并复制到 `t` 数组，对 `a` 数组排序。遍历 `t` 数组，若当前位置数字与排序后对应位置数字不同，寻找原表格中这两个数字位置并交换，同时记录交换操作。
 - **作者：JimmyLee 星级：4星**
    - **关键亮点**：代码简洁，通过自定义函数 `upd` 实现表格中位置的移动，利用 `pair` 和 `vector` 等容器记录位置和答案，逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 52

int len[maxn];
int mp[maxn][maxn];

void upd(int &x, int &y) 
{
    if(y==len[x]) y=1, x++;
    else y++;
}

pair<int, int> pos[maxn*maxn]; 
struct ans{int a, b, c, d;};
vector<ans> vc; 

int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>len[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=len[i];j++)
            cin>>mp[i][j], pos[mp[i][j]]={i, j};
    int sum=accumulate(len+1, len+1+n, 0); 
    int x=0, y=0;
    for(int i=1;i<sum;i++)
    {
        upd(x, y); 
        if(mp[x][y]==i) continue; 
        vc.push_back({x,y,pos[i].first,pos[i].second});
        int l=mp[x][y];
        swap(mp[x][y], mp[pos[i].first][pos[i].second]);
        swap(pos[l], pos[i]);
    }
    cout<<vc.size()<<'\n';
    for(auto [a, b, c, d]:vc) cout<<a<<' '<<b<<' '<<c<<' '<<d<<'\n'; 
    return 0;
}
```
    - **核心实现思想**：读入表格数据同时记录每个数字位置到 `pos`。通过 `upd` 函数移动位置，若当前位置数字与理想数字不符，记录交换操作并进行交换。
 - **作者：_edge_ 星级：4星**
    - **关键亮点**：同样采用暴力交换思路，代码中通过详细的注释和清晰的变量命名，使得逻辑易于理解，利用数组记录位置和答案，操作过程清晰。
    - **重点代码**：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=55;
int n,c[INF],sum,a[INF*INF],b[INF*INF],Map[INF][INF],ans,ans1[INF*INF][11];
signed main()
{
        scanf("%d",&n);
        for (int i=1; i<=n; i++) scanf("%d",&c[i]),sum+=c[i];
        for (int i=1; i<=n; i++) {
                for (int j=1; j<=c[i]; j++) {
                        int x=0; scanf("%d",&x);
                        a[x]=i; b[x]=j; Map[i][j]=x;
                }
        }
        int x=1,y=1;
        for (int i=1; i<sum; i++) {
                if (a[i]==x && b[i]==y) {
                        if (y==c[x]) {
                                x++; y=1;
                        }
                        else y++;
                        continue;
                }
                ans++; ans1[ans][0]=x; ans1[ans][1]=y;
                ans1[ans][2]=a[i]; ans1[ans][3]=b[i];
                swap(a[Map[x][y]],a[i]);
                swap(b[Map[x][y]],b[i]);
                swap(Map[x][y],Map[a[Map[x][y]]][b[Map[x][y]]]);
                if (y==c[x]) {
                        x++; y=1;
                }
                else y++;
        }
        cout<<ans<<"\n";
        for (int i=1; i<=ans; i++) cout<<ans1[i][0]<<" "<<ans1[i][1]<<" "<<ans1[i][2]<<" "<<ans1[i][3]<<"\n";
        return 0;
}
```
    - **核心实现思想**：读入数据时记录每个数字所在行列位置。按顺序遍历理想位置，若当前位置数字不符则交换并记录操作，同时更新位置信息。

### 最优关键思路或技巧
利用题目对操作次数限制宽松，直接模拟交换过程。关键在于巧妙记录每个数字的原始位置，通过对比理想升序排列状态下的位置，确定交换操作。

### 可拓展之处
此类题目属于表格数据重排满足特定条件的模拟题，类似套路是先分析目标状态，利用数据特性（如本题全排列），通过记录位置、模拟移动或交换等操作实现。

### 洛谷相似题目推荐
 - [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)：涉及字符串变换，通过模拟不同规则下的字符串变化求解。
 - [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：对二维表格进行模拟填充，与本题对表格操作有相似之处。
 - [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)：通过模拟括号匹配过程，与本题模拟数据操作思路类似。 

---
处理用时：64.97秒