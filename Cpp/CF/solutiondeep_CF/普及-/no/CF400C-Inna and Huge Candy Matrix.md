# 题目信息

# Inna and Huge Candy Matrix

## 题目描述

Inna and Dima decided to surprise Sereja. They brought a really huge candy matrix, it's big even for Sereja! Let's number the rows of the giant matrix from $ 1 $ to $ n $ from top to bottom and the columns — from $ 1 $ to $ m $ , from left to right. We'll represent the cell on the intersection of the $ i $ -th row and $ j $ -th column as $ (i,j) $ . Just as is expected, some cells of the giant candy matrix contain candies. Overall the matrix has $ p $ candies: the $ k $ -th candy is at cell $ (x_{k},y_{k}) $ .

The time moved closer to dinner and Inna was already going to eat $ p $ of her favourite sweets from the matrix, when suddenly Sereja (for the reason he didn't share with anyone) rotated the matrix $ x $ times clockwise by 90 degrees. Then he performed the horizontal rotate of the matrix $ y $ times. And then he rotated the matrix $ z $ times counterclockwise by 90 degrees. The figure below shows how the rotates of the matrix looks like.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400C/168ff7db18e226cd45113b10da5f3c7fbd5680f5.png)Inna got really upset, but Duma suddenly understood two things: the candies didn't get damaged and he remembered which cells contained Inna's favourite sweets before Sereja's strange actions. Help guys to find the new coordinates in the candy matrix after the transformation Sereja made!

## 说明/提示

Just for clarity. Horizontal rotating is like a mirroring of the matrix. For matrix:

`<br></br>QWER      REWQ <br></br>ASDF  ->  FDSA<br></br>ZXCV      VCXZ<br></br>`

## 样例 #1

### 输入

```
3 3 3 1 1 9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
```

### 输出

```
1 3
1 2
1 1
2 3
2 2
2 1
3 3
3 2
3 1
```

# AI分析结果

### 题目内容
#### Inna和巨大的糖果矩阵
#### 题目描述
Inna和Dima决定给Sereja一个惊喜。他们带来了一个非常巨大的糖果矩阵，即使对Sereja来说，这个矩阵也很大！让我们将这个巨大矩阵的行从顶部到底部从1到n编号，列从左到右从1到m编号。我们将第i行和第j列交叉处的单元格表示为(i, j)。正如预期的那样，巨大糖果矩阵的一些单元格中包含糖果。矩阵中总共有p颗糖果：第k颗糖果位于单元格(xk, yk)。

时间临近晚餐，Inna正准备从矩阵中吃掉p颗她最喜欢的糖果，这时突然Sereja（出于他没有与任何人分享的原因）将矩阵顺时针旋转了x次，每次旋转90度。然后，他对矩阵进行了y次水平旋转。接着，他又将矩阵逆时针旋转了z次，每次旋转90度。下图展示了矩阵的旋转情况。

![矩阵旋转图示](https://cdn.luogu.com.cn/upload/vjudge_pic/CF400C/168ff7db18e226cd45113b10da5f3c7fbd5680f5.png)

Inna非常沮丧，但Duma突然明白了两件事：糖果没有损坏，并且他记得在Sereja奇怪的操作之前，Inna最喜欢的糖果所在的单元格。帮助他们找到在Sereja进行变换后，糖果矩阵中糖果的新坐标！

#### 说明/提示
为了清晰起见。水平旋转就像矩阵的镜像。对于矩阵：
`<br></br>QWER      REWQ <br></br>ASDF  ->  FDSA<br></br>ZXCV      VCXZ<br></br>`

#### 样例 #1
##### 输入
```
3 3 3 1 1 9
1 1
1 2
1 3
2 1
2 2
2 3
3 1
3 2
3 3
```
##### 输出
```
1 3
1 2
1 1
2 3
2 2
2 1
3 3
3 2
3 1
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是通过模拟矩阵的旋转和翻转操作来计算糖果坐标的变化。所有题解都注意到了旋转和翻转操作的周期性，即顺时针或逆时针旋转4次、镜面对称2次后矩阵会恢复原样，因此对x、y、z分别进行取模操作（x %= 4，y %= 2，z %= 4）以减少计算量。

在具体实现上，各题解都分别定义了函数来处理顺时针旋转、水平旋转和逆时针旋转操作，通过遍历每个糖果的坐标并根据操作规则更新坐标值。不同题解在代码风格和变量命名上略有差异，但整体思路和实现逻辑基本一致。

### 所选的题解
#### 作者：I_like_magic (5星)
- **关键亮点**：思路清晰，代码结构良好，将每种旋转操作封装成独立函数，逻辑明确，易于理解和维护。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,z,p;
struct e{
    int x,y;
}d[100005];
void fun1(int t){
    while(t--){
        for(int i=1;i<=p;i++){
            int o=d[i].x;
            d[i].x=d[i].y;
            d[i].y=n-o+1;
        }
        swap(n,m); //记得交换
    }
}
void fun2(int t){
    while(t--){
        for(int i=1;i<=p;i++){
            d[i].y=m-d[i].y+1;
        }
    }
}
void fun3(int t){
    while(t--){
        for(int i=1;i<=p;i++){
            int o=d[i].y;
            d[i].y=d[i].x;
            d[i].x=m-o+1;
        }
        swap(n,m);
    }
}
int main(){
    cin>>n>>m>>x>>y>>z>>p;
    x%=4;y%=2;z%=4; //记得模一下
    for(int i=1;i<=p;i++)cin>>d[i].x>>d[i].y;
    fun1(x);fun2(y);fun3(z);
    for(int i=1;i<=p;i++)cout<<d[i].x<<" "<<d[i].y<<"\n";
    return 0;
} 
```
核心实现思想：定义`fun1`、`fun2`、`fun3`函数分别处理顺时针旋转、水平旋转和逆时针旋转操作。在`main`函数中，先对输入的旋转次数取模，再依次调用这三个函数进行操作，最后输出糖果的新坐标。

#### 作者：digby (4星)
- **关键亮点**：通过插入旋转操作的动态图辅助理解，使思路更直观。代码简洁明了，逻辑清晰。
```cpp
#include<iostream>
using namespace std;
int N, M, x, y, z, p;
struct fz{
    int x, y;
} ;
fz E[100010];
void turn_x(){
    for(int i = 1; i <= p; i++){
        int t = N + 1 - E[i].x;
        E[i].x = E[i].y;
        E[i].y = t;
    }
    swap(N, M);
}
void turn_y(){
    for(int i = 1; i <= p; i++)
        E[i].y = M + 1 - E[i].y;
}
void turn_z(){
    for(int i = 1; i <= p; i++){
        int t = M + 1 - E[i].y;
        E[i].y = E[i].x;
        E[i].x = t;
    }
    swap(N, M);
}
int main (){
    cin >> N>>M;
    cin >>x>>y>>z;
    cin>>p;
    for(int i = 1; i <= p; i++){
        cin >>E[i].x>>E[i].y;
    }
    x %= 4;//处理x，y，z；
    y %= 2;
    z %= 4;
    
    for(int i = 1; i <= x; i++){
      turn_x(); //处理x
    }
    if(y){ //
        turn_y();//处理y
     }
    
    for(int i = 1; i <= z; i++){
        turn_z();//处理z
    }
    
    for(int i = 1; i <= p; i++){
        cout << E[i].x<<' '<<E[i].y<<endl;
    }
    return 0;
}
```
核心实现思想：定义`turn_x`、`turn_y`、`turn_z`函数分别实现三种旋转操作。在`main`函数中，先对旋转次数取模，再根据取模后的次数调用相应函数处理糖果坐标，最后输出结果。

#### 作者：xvl_ (4星)
- **关键亮点**：详细地分析了每种旋转操作后坐标的变化规律，并通过注释展示了观察过程，帮助读者理解。代码规范，结构合理。
```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, m, x, y, z, p;
int X[100005], Y[100005];
void solve_x() {
    for (int i = 1; i <= p; i++) {
        int tmp = X[i];
        X[i] = Y[i];
        Y[i] = n - tmp + 1; 
    }
    swap(n, m); // 交换
}
void solve_y() {
    for (int i = 1; i <= p; i++) Y[i] = m - Y[i] + 1;
}
void solve_z() {
    for (int i = 1; i <= p; i++) {
        int tmp = Y[i];
        Y[i] = X[i];
        X[i] = m - tmp + 1;
    }
    swap(n, m); // 交换
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m >> x >> y >> z >> p;
    x %= 4, y %= 2, z %= 4; // 注意取模
    for (int i = 1; i <= p; i++) cin >> X[i] >> Y[i];
    for (int i = 1; i <= x; i++) solve_x();
    for (int i = 1; i <= y; i++) solve_y();
    for (int i = 1; i <= z; i++) solve_z();
    for (int i = 1; i <= p; i++) cout << X[i] << " " << Y[i] << "\n";
    return 0;
}
```
核心实现思想：定义`solve_x`、`solve_y`、`solve_z`函数分别负责顺时针旋转、水平旋转和逆时针旋转操作。在`main`函数中，先对输入的旋转次数取模，然后按顺序调用这三个函数更新糖果坐标，最后输出新坐标。

### 最优关键思路或技巧
利用操作的周期性对旋转次数进行取模，减少不必要的计算。将每种旋转操作封装成独立函数，使代码结构清晰，易于维护和理解。

### 拓展与类似题目
此类题目属于图形变换的模拟题，类似套路是观察图形变换的规律，利用规律简化计算。例如，对于其他角度的旋转或不同类型的对称操作，都可以通过分析坐标变化规律来解决。

### 推荐题目
- [P1035 [NOIP2002 普及组] 级数求和](https://www.luogu.com.cn/problem/P1035)：通过模拟计算级数的和，锻炼基本的模拟能力。
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：根据给定的规则模拟小玉游泳的过程，涉及简单的条件判断和循环操作。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：模拟购买铅笔的方案选择过程，需要考虑不同包装铅笔的价格和数量关系。 

---
处理用时：86.61秒