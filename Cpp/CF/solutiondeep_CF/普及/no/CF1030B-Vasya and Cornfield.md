# 题目信息

# Vasya and Cornfield

## 题目描述

Vasya owns a cornfield which can be defined with two integers $ n $ and $ d $ . The cornfield can be represented as rectangle with vertices having Cartesian coordinates $ (0, d), (d, 0), (n, n - d) $ and $ (n - d, n) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030B/104e0bfeaf07ab93dff4c549bd13618b0eb766eb.png)An example of a cornfield with $ n = 7 $ and $ d = 2 $ .Vasya also knows that there are $ m $ grasshoppers near the field (maybe even inside it). The $ i $ -th grasshopper is at the point $ (x_i, y_i) $ . Vasya does not like when grasshoppers eat his corn, so for each grasshopper he wants to know whether its position is inside the cornfield (including the border) or outside.

Help Vasya! For each grasshopper determine if it is inside the field (including the border).

## 说明/提示

The cornfield from the first example is pictured above. Grasshoppers with indices $ 1 $ (coordinates $ (2, 4) $ ) and $ 4 $ (coordinates $ (4, 5) $ ) are inside the cornfield.

The cornfield from the second example is pictured below. Grasshoppers with indices $ 1 $ (coordinates $ (4, 4) $ ), $ 3 $ (coordinates $ (8, 1) $ ) and $ 4 $ (coordinates $ (6, 1) $ ) are inside the cornfield.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030B/e5639eb53ffd6809c606315deea176befa06452d.png)

## 样例 #1

### 输入

```
7 2
4
2 4
4 1
6 3
4 5
```

### 输出

```
YES
NO
NO
YES
```

## 样例 #2

### 输入

```
8 7
4
4 4
2 8
8 1
6 1
```

### 输出

```
YES
NO
YES
YES
```

# AI分析结果

【题目内容】
# Vasya和玉米田

## 题目描述

Vasya拥有一块玉米田，可以用两个整数$n$和$d$来定义。这块玉米田可以表示为一个矩形，其顶点在笛卡尔坐标系中的坐标为$(0, d)$、$(d, 0)$、$(n, n - d)$和$(n - d, n)$。

Vasya还知道在田附近（可能甚至在田内）有$m$只蚱蜢。第$i$只蚱蜢位于点$(x_i, y_i)$。Vasya不喜欢蚱蜢吃他的玉米，因此他想知道每只蚱蜢的位置是否在玉米田内（包括边界）或外。

帮助Vasya！对于每只蚱蜢，确定它是否在田内（包括边界）。

## 说明/提示

第一张图展示了$n = 7$和$d = 2$时的玉米田。坐标为$(2, 4)$和$(4, 5)$的蚱蜢在田内。

第二张图展示了$n = 8$和$d = 7$时的玉米田。坐标为$(4, 4)$、$(8, 1)$和$(6, 1)$的蚱蜢在田内。

## 样例 #1

### 输入

```
7 2
4
2 4
4 1
6 3
4 5
```

### 输出

```
YES
NO
NO
YES
```

## 样例 #2

### 输入

```
8 7
4
4 4
2 8
8 1
6 1
```

### 输出

```
YES
NO
YES
YES
```

【算法分类】
数学

【题解分析与结论】
本题的核心是判断一个点是否在给定的矩形内。矩形的边界由四条直线组成，因此可以通过求解这四条直线的方程，然后判断点是否在这些直线的范围内来确定点的位置。

大多数题解都采用了类似的方法，即通过求解四条直线的方程，然后通过不等式判断点是否在矩形内。这种方法的时间复杂度为$O(1)$，效率较高。

【评分较高的题解】
1. **作者：KagurazakaKano (5星)**
   - **关键亮点**：清晰地推导了四条直线的方程，并将问题转化为线性规划问题，代码简洁且易于理解。
   - **代码实现**：
     ```cpp
     #include <bits/stdc++.h>
     using namespace std;
     int main(){
         int n,d;
         scanf("%d%d",&n,&d);
         int m;
         scanf("%d",&m);
         for(int i = 1; i <= m; i++){
             int x, y;
             scanf("%d%d",&x,&y);
             if((x + y >= d) && (x + y <= (2 * n - d)) && (x - y >= -d) && (x - y) <= d){
                 printf("YES\n");
             } else {
                 printf("NO\n");
             }
         }
         return 0;
     }
     ```

2. **作者：qingchenMC (4星)**
   - **关键亮点**：详细解释了如何通过求解四条直线的方程来判断点的位置，代码实现清晰。
   - **代码实现**：
     ```cpp
     #include<bits/stdc++.h>
     using namespace std;
     int main(){
         int n,d,m;
         cin>>n>>d>>m;
         for(int i=1;i<=m;i++){
             int x,y;
             cin>>x>>y;
             if(y>=(-x+d)&&y>=(x-d)&&y<=(x+d)&&y<=(-x+2*n-d)){
                 cout<<"YES"<<endl;
             }
             else{
                 cout<<"NO"<<endl;
             }
         }
         return 0;
     }
     ```

3. **作者：FurippuWRY (4星)**
   - **关键亮点**：简洁地推导了四条直线的方程，并通过不等式判断点的位置，代码实现简洁。
   - **代码实现**：
     ```cpp
     #include <bits/stdc++.h>
     using namespace std;
     int n, d, x, y, k;
     int main() {
         cin >> n >> d >> k;
         while (k--) {
             cin >> x >> y;
             if (x + y >= d && 
                 x + y <= 2 * n - d && 
                 x - y >= -d && 
                 x - y <= d) cout << "YES\n";
             else cout << "NO\n";
         }
         return 0;
     }
     ```

【最优关键思路或技巧】
通过求解四条直线的方程，将问题转化为线性规划问题，利用不等式判断点是否在矩形内。这种方法不仅效率高，而且易于理解和实现。

【可拓展之处】
类似的问题可以扩展到其他几何形状，如三角形、圆形等，通过求解边界方程来判断点的位置。此外，这种方法也可以用于判断点是否在多边形内。

【推荐题目】
1. P1359 判断点是否在矩形内
2. P1360 判断点是否在三角形内
3. P1361 判断点是否在圆形内

---
处理用时：40.80秒