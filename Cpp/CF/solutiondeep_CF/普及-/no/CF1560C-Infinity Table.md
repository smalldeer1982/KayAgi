# 题目信息

# Infinity Table

## 题目描述

Polycarp has found a table having an infinite number of rows and columns. The rows are numbered from $ 1 $ , starting from the topmost one. The columns are numbered from $ 1 $ , starting from the leftmost one.

Initially, the table hasn't been filled and Polycarp wants to fix it. He writes integers from $ 1 $ and so on to the table as follows.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1560C/fbe22cdb57a9c1d91e54741c4b3ed27f17ef455a.png)The figure shows the placement of the numbers from $ 1 $ to $ 10 $ . The following actions are denoted by the arrows.The leftmost topmost cell of the table is filled with the number $ 1 $ . Then he writes in the table all positive integers beginning from $ 2 $ sequentially using the following algorithm.

First, Polycarp selects the leftmost non-filled cell in the first row and fills it. Then, while the left neighbor of the last filled cell is filled, he goes down and fills the next cell. So he goes down until the last filled cell has a non-filled neighbor to the left (look at the vertical arrow going down in the figure above).

After that, he fills the cells from the right to the left until he stops at the first column (look at the horizontal row in the figure above). Then Polycarp selects the leftmost non-filled cell in the first row, goes down, and so on.

A friend of Polycarp has a favorite number $ k $ . He wants to know which cell will contain the number. Help him to find the indices of the row and the column, such that the intersection of the row and the column is the cell containing the number $ k $ .

## 样例 #1

### 输入

```
7
11
14
5
4
1
2
1000000000```

### 输出

```
2 4
4 3
1 3
2 1
1 1
1 2
31623 14130```

# AI分析结果

### 题目内容
# Infinity Table

## 题目描述
Polycarp发现了一张有无穷多行和列的表格。行从1开始编号，从最上面一行开始。列也从1开始编号，从最左边一列开始。

最初，表格尚未填充，Polycarp想要填充它。他按如下方式将整数从1开始依次写入表格。

![表格数字填充示意图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1560C/fbe22cdb57a9c1d91e54741c4b3ed27f17ef455a.png)
该图展示了数字1到10的放置位置。以下操作由箭头表示。表格最左上角的单元格填充数字1。然后，他从2开始按顺序使用以下算法在表格中写入所有正整数。

首先，Polycarp选择第一行中最左边的未填充单元格并填充它。然后，当最后填充的单元格的左邻居已填充时，他向下移动并填充下一个单元格。因此，他一直向下移动，直到最后填充的单元格的左邻居未填充（查看上图中向下的垂直箭头）。

之后，他从右到左填充单元格，直到在第一列停止（查看上图中的水平行）。然后Polycarp选择第一行中最左边的未填充单元格，向下移动，依此类推。

Polycarp的一个朋友有一个最喜欢的数字k。他想知道哪个单元格将包含这个数字。帮助他找到行和列的索引，使得行和列的交点就是包含数字k的单元格。

## 样例 #1
### 输入
```
7
11
14
5
4
1
2
1000000000
```
### 输出
```
2 4
4 3
1 3
2 1
1 1
1 2
31623 14130
```
### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是通过寻找数字在表格中排列的规律，来直接计算出给定数字k所在的行列位置，避免了模拟填数的复杂过程。
1. **思路方面**：多数题解都关注到了表格数字排列按层或按对角线的规律。如将表格一圈看成一段，发现每段结束数字为n^2 ，中间数（第n行第n列）为n^2 - n + 1 ；或者观察到第一列都是完全平方数等。
2. **算法要点**：利用这些规律，通过计算平方根、比较数字大小等方式确定数字所在层或对角线，再进一步确定其在行和列上的具体偏移量。
3. **解决难点**：难点在于准确找出数字排列规律，并根据规律设计出正确的计算逻辑。不同题解在规律的挖掘角度和具体实现细节上有所不同。

### 所选的题解
- **作者：Doqin07 (5星)**
    - **关键亮点**：思路清晰简洁，直接找出每段数字的结束值和中间数规律，分三种情况清晰地给出计算数字坐标的方法，代码简洁高效。
    - **重点代码核心思想**：先计算k的平方根n，判断k与n^2 以及中间数n^2 - n + 1 的关系，根据不同情况输出对应的行列坐标。
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    int T, k;
    int main(){
        scanf("%d", &T);
        while (T--){
            scanf("%d", &k);
            int n = sqrt(k);
            if (n * n == k){
                printf("%d 1\n", n);
            } else{
                n++;
                int cur = n * n - n + 1;
                if (k == cur) printf("%d %d\n", n, n);
                else{
                    if (k > cur){
                        printf("%d %d\n", n, n - (k - cur));
                    } else{
                        printf("%d %d\n", n - (cur - k), n);
                    }
                }
            }
        }
        return 0;
    }
    ```
- **作者：Arctic_1010 (4星)**
    - **关键亮点**：通过二次函数拟合的方式找出对角线上数字与坐标的关系，思路独特，对找规律的方法有创新性展示，分情况讨论清晰。
    - **重点代码核心思想**：枚举对角线，通过抛物线解析式y = x^2 - x + 1计算对角线上的数字s ，判断目标数字n与s的位置关系，分情况输出坐标。
    ```cpp
    #include<cstdio>
    using namespace std;
    int q;
    signed main()
    {
        scanf("%d",&q);
        while(q--)
        {
            int n;
            scanf("%d",&n);
            for(int i=1;i<=31624;i++)
            {
                int s=i*i-i+1;
                if(s==n)
                {
                    printf("%d %d\n",i,i);
                    break;
                }
                if((s-i+1<=n && n<=s)||(s<=n && n<=s+i-1))
                {
                    if(s-n<0) printf("%d %d\n",i,i+s-n);
                    else printf("%d %d\n",i-s+n,i);
                    break;
                }
            }
        } 
        return 0;
    }
    ```
- **作者：滑_稽 (4星)**
    - **关键亮点**：先利用第一列是完全平方数求出数字所在的大致行列范围，再通过推导对角线上数字通项公式来确定数字具体坐标，逻辑连贯，算法简洁。
    - **重点代码核心思想**：计算k的上取整平方根n，得到坐标为(n,n)的数字mid = n*(n - 1)+1 ，比较k与mid大小，根据差值计算坐标。
    ```cpp
    #include<iostream>
    #include<cstdio>
    #include<cmath>
    using namespace std;

    int t,k,r,c,n,mid;

    int main(){
        ios::sync_with_stdio(false);
        cin>>t;
        while(t--){
            cin>>k;
            n=ceil(sqrt(k));
            mid=n*(n-1)+1;
            if(k<mid) r=n+k-mid,c=n;
            else if(k==mid) r=c=n;
            else r=n,c=n-k+mid;
            cout<<r<<" "<<c<<endl;
        }
        return 0;
    }
    ```

### 最优关键思路或技巧
1. **观察数字排列规律**：通过观察表格中数字按层或对角线排列的规律，建立数字与行列坐标的联系，这是解决本题的关键。
2. **利用数学关系计算**：如通过计算平方根确定数字所在层或对角线，利用通项公式计算特定位置的数字，再通过比较大小和差值计算具体坐标。

### 可拓展之处
此类题目属于数字规律探索类型，类似套路是先观察数字排列特点，尝试从不同角度（如层、对角线、行列等）找出规律，并用数学公式表达，再根据规律进行计算。同类型题可考察不同的数字排列方式和规律挖掘方向。

### 洛谷相似题目推荐
1. [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析日常生活中的数据规律来解决问题，锻炼找规律能力。
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：需要从字符串中寻找特定单词出现次数的规律，结合字符串处理和规律分析。
3. [P1464 Function](https://www.luogu.com.cn/problem/P1464)：通过探索函数值的规律来解决问题，与本题类似，都需要挖掘数字间隐藏的规律。 

---
处理用时：54.41秒