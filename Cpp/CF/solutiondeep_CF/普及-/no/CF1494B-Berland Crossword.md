# 题目信息

# Berland Crossword

## 题目描述

Berland crossword is a puzzle that is solved on a square grid with $ n $ rows and $ n $ columns. Initially all the cells are white.

To solve the puzzle one has to color some cells on the border of the grid black in such a way that:

- exactly $ U $ cells in the top row are black;
- exactly $ R $ cells in the rightmost column are black;
- exactly $ D $ cells in the bottom row are black;
- exactly $ L $ cells in the leftmost column are black.

Note that you can color zero cells black and leave every cell white.

Your task is to check if there exists a solution to the given puzzle.

## 说明/提示

Here are possible solutions to testcases $ 1 $ , $ 2 $ and $ 4 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1494B/d621c171f085bccb3662990f2929812003bf6b92.png)

## 样例 #1

### 输入

```
4
5 2 5 3 1
3 0 0 0 0
4 4 1 4 0
2 1 1 1 1```

### 输出

```
YES
YES
NO
YES```

# AI分析结果

### 题目内容
# Berland Crossword

## 题目描述
Berland纵横字谜是一种在具有$n$行和$n$列的正方形网格上解决的谜题。最初，所有单元格都是白色的。
为了解决这个谜题，必须将网格边界上的一些单元格涂黑，使得：
- 最上面一行恰好有$U$个黑色单元格；
- 最右边一列恰好有$R$个黑色单元格；
- 最下面一行恰好有$D$个黑色单元格；
- 最左边一列恰好有$L$个黑色单元格。
注意，你可以涂黑零个单元格，让每个单元格都保持白色。
你的任务是检查给定的谜题是否存在解决方案。

## 说明/提示
以下是测试用例1、2和4的可能解决方案：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1494B/d621c171f085bccb3662990f2929812003bf6b92.png)

## 样例 #1
### 输入
```
4
5 2 5 3 1
3 0 0 0 0
4 4 1 4 0
2 1 1 1 1
```
### 输出
```
YES
YES
NO
YES
```

### 算法分类
枚举

### 综合分析与结论
这些题解主要围绕判断在给定的$n\times n$网格边界上涂黑单元格的限制条件下，是否存在可行的涂色方案。大部分题解思路基于对四个角的状态进行讨论，因为角上的格子同时影响行和列的黑色格子数量。不同题解在实现方式上略有差异，有的通过穷举四个角的所有$2^4 = 16$种状态（0表示不涂黑，1表示涂黑），判断剩余边的黑色格子数量是否满足条件；有的则是通过分析边界值（如$n - 1$和$n$的情况），计算行列在输入限制下的最小黑色格子数，再判断是否超过输入限制。

### 所选的题解
- **作者：_Violet_Evergarden（4星）**
  - **关键亮点**：思路清晰，通过计算超过$n - 2$的行和列的数量，直接判断是否存在违法情况，代码简洁明了。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a,b,c,d;
int flag1,flag2,flag3,flag4;
int m;
int main()
{
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>n;
        cin>>a>>b>>c>>d;
        flag1=max(0,a-n+2);
        flag2=max(0,b-n+2);
        flag3=max(0,c-n+2);
        flag4=max(0,d-n+2);
        if((a+c)<(flag2+flag4)||(b+d)<(flag1+flag3)||a<(flag2/2+flag4/2)||c<(flag2/2+flag4/2)||b<(flag1/2+flag3/2)||d<(flag1/2+flag3/2)){
            cout<<"NO"<<endl;
        }
        else{
            cout<<"YES"<<endl;
        }
    }
    return 0;
} 
```
  - **核心思想**：用`flag1` - `flag4`分别记录每行每列超过$n - 2$的数量，通过一系列不等式判断是否存在合法方案。

- **作者：Booksnow（4星）**
  - **关键亮点**：分析出四个角落的格子对行和列黑格个数的特殊影响，直接拿掉四个点讨论其是否变黑，穷举16种情况，思路直接，代码逻辑清晰。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline bool check(int n,int u,int r,int d,int l)
{
    if(u>n-2||r>n-2||d>n-2||l>n-2) return false;
    return true;
}
int main()
{
    T=read();
    while(T--){
        int N=read(),U=read(),R=read(),D=read(),L=read();
        bool flag=false;
        int u=U,r=R,d=D,l=L;
        for(register int i=0;i<=1;i++){
            for(register int j=0;j<=1;j++){
                for(register int k=0;k<=1;k++){
                    for(register int p=0;p<=1;p++){
                        u=U,r=R,d=D,l=L;
                        if(i==1) u--,l--;
                        if(j==1) u--,r--;
                        if(k==1) d--,l--;
                        if(p==1) d--,r--;
                        if(u<0||d<0||l<0||r<0) continue;
                        if(check(N,u,r,d,l)) { flag=true; break; }
                    }
                    if(flag) break;
                }
                if(flag) break;
            }
            if(flag) break;
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
} 
```
  - **核心思想**：四层循环穷举四个角的状态，根据角的状态调整剩余行列需涂黑的格子数，再通过`check`函数判断是否满足条件。

- **作者：GoodLuckCat（4星）**
  - **关键亮点**：利用二进制数巧妙表示四个角的状态，通过位运算快速提取每一位，代码简洁高效。
  - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n,U,R,D,L;
        cin>>n>>U>>R>>D>>L;
        string p="NO\n";
        for(int i=0;i<=15;i++)
        {
            int u=U,r=R,d=D,l=L;
            if(i&1)u--,l--;
            if(i&2)u--,r--;
            if(i&4)r--,d--;
            if(i&8)d--,l--;
            if(u>=0&&r>=0&&d>=0&&l>=0&&u<=n-2&&r<=n-2&&d<=n-2&&l<=n-2)
            {
                p="YES\n";
                break;
            }
        }
        cout<<p;
    }
    return 0;
}
```
  - **核心思想**：用`i`从0到15循环表示四个角的16种状态，通过位运算判断每个角是否涂黑并调整对应行列的黑色格子数，最后判断剩余黑色格子数是否满足条件。

### 最优关键思路或技巧
利用二进制数表示四个角的状态并通过位运算提取每一位，这种方法简洁高效，减少了代码量，同时也提高了代码的可读性和运行效率。对于类似涉及多个具有两种状态元素组合影响结果的问题，可以考虑使用这种状态压缩的思想。

### 可拓展之处
同类型题或类似算法套路：对于一些在矩阵边界上有条件限制的填充或判断问题，都可以考虑从边界特殊位置（如角、边中点等）入手，通过枚举这些特殊位置的状态，结合条件判断是否存在可行解。在解决这类问题时，要善于分析特殊位置对整体条件的影响，找到简洁有效的判断条件。

### 推荐题目
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过枚举菜品选择情况，结合预算限制判断可行方案，与本题枚举角的状态判断可行性类似。
- [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)：利用位运算解决问题，与本题中使用位运算表示角的状态有相似之处。
- [P2241 统计方形（数据加强版）](https://www.luogu.com.cn/problem/P2241)：在矩阵中根据一定条件统计满足要求的图形数量，与本题在矩阵上进行条件判断有类似的思考方式。 

---
处理用时：70.68秒