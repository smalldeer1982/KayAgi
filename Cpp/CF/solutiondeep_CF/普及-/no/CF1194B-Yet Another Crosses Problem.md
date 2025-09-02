# 题目信息

# Yet Another Crosses Problem

## 题目描述

你将会得到若干个 $n$ 行 $m$ 列的矩阵。每一格都被涂成了黑色或白色

若矩阵中的某行，某列都为黑色，则这一行与一列构成了一个十字架

如下所示，这些矩阵都包含了至少一个十字架

![qaq](https://cdn.luogu.org/upload/vjudge_pic/CF1194B/88ab70f483371a989bc0a7f4c7494f932bf59239.png)

而下列矩阵则不包含十字架

![233](https://cdn.luogu.org/upload/vjudge_pic/CF1194B/a3af39e3883913d8cb154cdd61325299208144f4.png)

你的任务是，共有 $q$ 次询问。对于每一次询问，给出一个矩阵，求出至少还要将多少个白色格子涂成黑色，才能使这个矩阵包含至少一个十字架

## 样例 #1

### 输入

```
9
5 5
..*..
..*..
*****
..*..
..*..
3 4
****
.*..
.*..
4 3
***
*..
*..
*..
5 5
*****
*.*.*
*****
..*.*
..***
1 4
****
5 5
.....
..*..
.***.
..*..
.....
5 3
...
.*.
.*.
***
.*.
3 3
.*.
*.*
.*.
4 4
*.**
....
*.**
*.**
```

### 输出

```
0
0
0
0
0
4
1
1
2
```

# AI分析结果

### 题目内容
# 又一个十字问题

## 题目描述
你将会得到若干个 $n$ 行 $m$ 列的矩阵。每一格都被涂成了黑色或白色。
若矩阵中的某行，某列都为黑色，则这一行与一列构成了一个十字架。
如下所示，这些矩阵都包含了至少一个十字架。
![qaq](https://cdn.luogu.org/upload/vjudge_pic/CF1194B/88ab70f483371a989bc0a7f4c7494f932bf59239.png)
而下列矩阵则不包含十字架。
![233](https://cdn.luogu.org/upload/vjudge_pic/CF1194B/a3af39e3883913d8cb154cdd61325299208144f4.png)
你的任务是，共有 $q$ 次询问。对于每一次询问，给出一个矩阵，求出至少还要将多少个白色格子涂成黑色，才能使这个矩阵包含至少一个十字架。

## 样例 #1
### 输入
```
9
5 5
..*..
..*..
*****
..*..
..*..
3 4
****
.*..
.*..
4 3
***
*..
*..
*..
5 5
*****
*.*.*
*****
..*.*
..***
1 4
****
5 5
.....
..*..
.***.
..*..
.....
5 3
...
.*.
.*.
***
.*.
3 3
.*.
*.*
.*.
4 4
*.**
....
*.**
*.**
```
### 输出
```
0
0
0
0
0
4
1
1
2
```

### 算法分类
贪心

### 综合分析与结论
所有题解思路核心均为贪心策略，即通过寻找每行和每列中白色格子最少的情况来确定最少涂色次数。各题解主要区别在于数据存储方式和代码实现细节。部分题解提到数组开太大导致编译错误，因此需采用更灵活的存储方式，如`vector`、`string`或一维数组模拟二维数组。同时，部分题解考虑到选取的行和列交界处若为白色会重复计算，需减去1。

### 所选的题解
- **作者：RE_Prince (5星)**
    - **关键亮点**：思路清晰，代码简洁，不仅提出用`vector`解决数组清空耗时和爆栈问题，还给出完整且易读的代码实现。
    - **个人心得**：作者提到因多测习惯整体`memset`数组导致时间超限，改用`vector`后时间降下来，强调了数据结构选择对时间复杂度的影响。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k;
char ch;
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        vector<string> a(n);
        vector<int> col(m),line(n);
        for(i=0;i<n;i++) cin>>a[i];
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                line[i]+=(a[i][j]=='.'),
                col[j]+=(a[i][j]=='.');
        int ans=1e9;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                ans=min(ans,col[j]+line[i]-(a[i][j]=='.'));
        cout<<ans<<endl;
    } 
    return 0;  
}
```
    - **核心实现思想**：用`vector<string>`存储矩阵，两个`vector<int>`分别记录每行和每列的空白格数。遍历矩阵统计空白格，再遍历所有位置计算以该位置为中心构成十字架需涂色的最少次数，取最小值。
- **作者：Llf0703 (4星)**
    - **关键亮点**：同样采用贪心策略，通过记录每行每列已涂黑的点数量，找到涂黑点数最多的行和列来计算答案，同时考虑到行列交界处的重复统计问题。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while (ch<'0' || ch>'9')
    {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

int t,n,m;
char s[400005],ch[50005];

inline int f(int x,int y) { return m*(x-1)+y; }

signed main()
{
    t=read();
    while (t--)
    {
        n=read(); m=read();
        for (int i=1;i<=n;i++)
        {
            scanf("%s",ch+1);
            for (int j=1;j<=m;j++) s[f(i,j)]=ch[j];
        }
        int mx=0,ans=0; vector<int> mxi;
        for (int i=1;i<=n;i++)
        {
            int cnt=0;
            for (int j=1;j<=m;j++) cnt+=s[f(i,j)]=='*';
            if (cnt>mx) mx=cnt,mxi.clear(),mxi.emplace_back(i);
            else if (cnt==mx) mxi.emplace_back(i);
        }
        ans+=m-mx;
        mx=0; vector<int> mxj;
        for (int j=1;j<=m;j++)
        {
            int cnt=0;
            for (int i=1;i<=n;i++) cnt+=s[f(i,j)]=='*';
            if (cnt>mx) mx=cnt,mxj.clear(),mxj.emplace_back(j);
            else if (cnt==mx) mxj.emplace_back(j);
        }
        ans+=n-mx;
        for (auto i:mxi) for (auto j:mxj) if (s[f(i,j)]!='*') {ans--; goto output;}
        output:printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：用一维数组`s`模拟二维矩阵存储输入，通过`f`函数计算坐标对应位置。两次遍历分别找出涂黑点数最多的行和列，计算需涂色数，再检查行列交界处是否为白色，若是则答案减1。
- **作者：逃课小姐MS (4星)**
    - **关键亮点**：使用一位数组存图，思路简洁明了，代码实现也较为清晰，同时准确考虑到行列相交处重复计算的情况。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[50010],r[50010];
bool mage[400001];
int a1,p1,a2,p2;
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            c[i]=0;
            for(int j=1;j<=m;j++){
                char ch;
                cin>>ch;
                if(ch=='.'){
                    c[i]++,mage[i*m+j]=1;
                }
                else mage[i*m+j]=0;
            }
        }
        for(int i=1;i<=m;i++){
            r[i]=0;
            for(int j=1;j<=n;j++){
                r[i]+=mage[j*m+i];
            }
        }
        int ans=2147483647;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                ans=min(ans,r[j]+c[i]-mage[i*m+j]);
            }
        cout<<ans<<endl;
    }
}
```
    - **核心实现思想**：用`mage`一维数组存储矩阵，`c`数组记录每行空格数，`r`数组记录每列空格数。遍历矩阵统计空格数，再遍历所有位置计算构成十字架需涂色最少次数并取最小值。

### 最优关键思路或技巧
1. **数据存储优化**：由于题目数据范围限制，不能直接使用常规二维数组存储矩阵，采用`vector`、`string`或一维数组模拟二维数组可有效解决内存问题。
2. **贪心策略**：寻找每行每列白色格子最少的行和列，计算将其染黑所需最少次数，同时考虑行列交界处白色格子重复计算问题。

### 可拓展之处
此类题目属于图形填充优化类型，相似套路为通过贪心策略寻找最优解，同时注意数据存储方式以适应数据范围。类似题目可能会改变图形形状或条件限制，但核心思路依然是寻找最优的填充或修改方式。

### 洛谷相似题目
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：同样运用贪心策略解决分组问题。
2. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：涉及贪心思想结合二分查找来确定最优分段。
3. [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：在处理字符串相关问题时运用贪心策略。 

---
处理用时：103.68秒