# 题目信息

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

# AI分析结果

### 题目内容中文重写
# Vanya和表格

## 题目描述
Vanya 有一个由 100 行组成的表格，每行包含 100 个单元格。行从下到上用整数 1 到 100 编号，列从左到右用 1 到 100 编号。

在这个表格中，Vanya 选择了 n 个边沿着正方形边界的矩形（有些矩形可能会多次出现）。之后，他为表格的每个单元格计算它所属的矩形数量，并将这个数字写入单元格中。现在他想求出表格中所有单元格的值的总和，由于表格太大，他请求你帮助他得到结果。

## 说明/提示
第一个样例测试的注释：

表格中前三行和前三列的值如下：

1 2 1
1 2 1
1 1 0

因此，这些值的总和将等于 10。

第二个样例测试的注释：

表格中前三行和前三列的值如下：

2 2 2
2 2 2
2 2 2

因此，这些值的总和将等于 18。

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

### 算法分类
模拟

### 综合分析与结论
- **思路对比**：
    - lichenzhen 的思路是模拟整个过程，用二维数组表示表格，每次输入矩形范围后，将该矩形内的单元格数值加 1，最后遍历整个数组求和。
    - N_z_ 和 szhqwq 的思路相同，认为结果就是 n 个矩形的面积之和，直接根据矩形的坐标计算每个矩形的面积并累加。
- **算法要点**：
    - lichenzhen：使用二维数组模拟表格，通过两层循环遍历矩形范围更新单元格数值，再通过两层循环遍历数组求和。
    - N_z_ 和 szhqwq：根据矩形的左上角和右下角坐标，利用公式 `(x2 - x1 + 1) * (y2 - y1 + 1)` 计算矩形面积并累加。
- **解决难点**：
    - lichenzhen：需要处理二维数组的更新和遍历，代码复杂度相对较高。
    - N_z_ 和 szhqwq：需要理解题目本质是求矩形面积之和，避免重复计算的误区。

### 题解评分与展示
- **lichenzhen（3星）**：思路清晰，代码实现简单直接，但时间复杂度较高，为 $O(n * 100 * 100)$。
- **N_z_（4星）**：思路简洁明了，直接抓住问题本质，代码简洁，时间复杂度为 $O(n)$。
- **szhqwq（4星）**：思路与 N_z_ 相同，代码规范，使用 `#define int long long` 避免了数据溢出问题，时间复杂度为 $O(n)$。

### 最优关键思路或技巧
直接计算每个矩形的面积并累加，避免使用二维数组模拟表格，降低时间复杂度。

### 可拓展之处
同类型题目可能会涉及多个图形的重叠面积计算，或者在不同坐标系下的图形面积计算。类似算法套路可以先分析问题的本质，看是否可以通过数学公式直接计算，避免不必要的模拟操作。

### 推荐洛谷题目
1. P1387 最大正方形：考察如何在矩阵中找到最大的正方形，与本题的矩形面积计算有一定关联。
2. P2004 领地选择：给定一个矩阵，选择一个固定大小的子矩阵，使其元素和最大，与本题的矩阵操作类似。
3. P1577 切绳子：通过计算矩形的面积来解决实际问题，与本题的思路有相似之处。

### 重点代码
```cpp
// N_z_ 的代码
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

// szhqwq 的代码
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
核心实现思想：通过循环读取每个矩形的左上角和右下角坐标，利用公式 `(x2 - x1 + 1) * (y2 - y1 + 1)` 计算矩形面积并累加到结果中。

---
处理用时：32.67秒