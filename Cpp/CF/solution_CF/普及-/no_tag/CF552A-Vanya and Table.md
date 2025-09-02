# Vanya and Table

## 题目描述

Vanya has a table consisting of $ 100 $ rows, each row contains $ 100 $ cells. The rows are numbered by integers from $ 1 $ to $ 100 $ from bottom to top, the columns are numbered from $ 1 $ to $ 100 $ from left to right.

In this table, Vanya chose $ n $ rectangles with sides that go along borders of squares (some rectangles probably occur multiple times). After that for each cell of the table he counted the number of rectangles it belongs to and wrote this number into it. Now he wants to find the sum of values in all cells of the table and as the table is too large, he asks you to help him find the result.

## 说明/提示

Note to the first sample test:

Values of the table in the first three rows and columns will be as follows:

 $ 121 $

 $ 121 $

 $ 110 $

So, the sum of values will be equal to $ 10 $ .

Note to the second sample test:

Values of the table in the first three rows and columns will be as follows:

 $ 222 $

 $ 222 $

 $ 222 $

So, the sum of values will be equal to $ 18 $ .

## 样例 #1

### 输入

```
2
1 1 2 3
2 2 3 3
```

### 输出

```
10
```

## 样例 #2

### 输入

```
2
1 1 3 3
1 1 3 3
```

### 输出

```
18
```

# 题解

## 作者：lichenzhen (赞：4)

## 题目大意

一张由 $100$ 行构成的表格，每行有 $100$ 个单元格。行从下到上编号为 $1$ 到 $100$，列从左到右编号为 $1$ 到 $100$。

在这张表格中，选择了 $n$ 个沿着正方形边界的矩形（有些矩形可能会出现多次）。之后，为表格的每个单元格计算出它所属的矩形的数量，并将这个数字写入其中。求出表格中所有单元格的值的总和。

## 题目解法
这是一道模拟题，可以用桶思想来解决这道题。

我们先定义一个数组`table`，代表这个表格，之后每当输入一个 $x_{1}$ 和 $y_{1}$（左下角单元格的列号和行号）$x_{2}$ 和 $y_{2}$（是右上角单元格的列号和行号）时，就循环把这个矩形范围内的表格的数值加 $1$。最后再扫描一遍整个数组，把这个数组内所有的数都加起来。

### 参考代码
```cpp
#include <iostream>
using namespace std;
int table[101][101],sum;//定义全局变量自动清零 
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2; 
        cin>>x1>>y1>>x2>>y2;
        for(int j=y1;j<=y2;j++)
            for(int k=x1;k<=x2;k++)
                table[j][k]++;//循环将矩形范围内表格的数值加1 
    }
    for(int i=1;i<=100;i++)
        for(int j=1;j<=100;j++)
            sum+=table[i][j];//循环扫描一下整个数组，把数组内所有的数据都加起来。 
    cout<<sum;
    return 0;
}
```


---

## 作者：N_z_ (赞：2)

## 思路
实际上就是求$n$个矩形的面积之和，读入时处理即可。

注意对于左上坐标是$(a,b)$，右下坐标是$(c,d)$的矩形，在本题中它对答案的贡献是它占点的数量，即$(c-a+1)\times (d-b+1)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int ans=0;
    while(n--)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        ans+=(abs(c-a)+1)*(abs(d-b)+1);
    }
    cout<<ans<<endl;
}
```

---

## 作者：szhqwq (赞：0)

## 题目大意

给定 $n$ 个矩阵的左上角和右下角的坐标，求这些矩阵的面积之和。

## 分析

矩形面积等于其长与宽的乘积，题中给出了矩形的左上角坐标 $(x_1,y_1)$ 右下角坐标 $(x_2,y_2)$，则矩形面积为 $(x_2 - x_1 + 1) \times (y_2 - y_1 + 1)$。

**注意：$x,y$ 坐标之差需要加 $1$**。

AC code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 110;

int n;

signed main() {
	ios :: sync_with_stdio(false);
	cin >> n;
	int res = 0;
	for (int i = 1; i <= n; i ++ ) {
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		res += (x2 - x1 + 1) * (y2 - y1 + 1);
	}
	cout << res << endl;
	return 0;
}
```

---

