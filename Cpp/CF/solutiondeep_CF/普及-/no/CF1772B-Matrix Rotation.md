# 题目信息

# Matrix Rotation

## 题目描述

You have a matrix $ 2 \times 2 $ filled with distinct integers. You want your matrix to become beautiful. The matrix is beautiful if the following two conditions are satisfied:

- in each row, the first element is smaller than the second element;
- in each column, the first element is smaller than the second element.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1772B/3883cb5d5c3c3237649026ca712db7066e7d51ae.png)You can perform the following operation on the matrix any number of times: rotate it clockwise by $ 90 $ degrees, so the top left element shifts to the top right cell, the top right element shifts to the bottom right cell, and so on:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1772B/a844c7395726cf76b3147efc79ccce4d8f167fbf.png)Determine if it is possible to make the matrix beautiful by applying zero or more operations.

## 样例 #1

### 输入

```
6
1 3
5 7
8 10
3 4
8 10
4 3
6 1
9 2
7 5
4 2
1 2
4 3```

### 输出

```
YES
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容
# 矩阵旋转

## 题目描述
你有一个填充着不同整数的 $2 \times 2$ 矩阵。你希望这个矩阵变得美观。当满足以下两个条件时，该矩阵是美观的：
- 在每一行中，第一个元素小于第二个元素；
- 在每一列中，第一个元素小于第二个元素。

![矩阵示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1772B/3883cb5d5c3c3237649026ca712db7066e7d51ae.png)
你可以对该矩阵执行以下操作任意次数：顺时针旋转 $90$ 度，即左上角元素移动到右上角单元格，右上角元素移动到右下角单元格，依此类推：

![旋转示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1772B/a844c7395726cf76b3147efc79ccce4d8f167fbf.png)
确定通过应用零次或多次操作是否可以使矩阵变得美观。

## 样例 #1
### 输入
```
6
1 3
5 7
8 10
3 4
8 10
4 3
6 1
9 2
7 5
4 2
1 2
4 3
```
### 输出
```
YES
YES
NO
YES
YES
NO
```
### 算法分类
枚举

### 综合分析与结论
大部分题解采用暴力枚举的方法，利用矩阵旋转4次会变回原样的特性，对旋转0次、90度、180度、270度后的矩阵分别进行是否美观的判断。VertexNeko的题解通过找规律，利用异或运算判断矩阵是否能通过旋转变得美观，提供了不同的解题思路。整体来看，各题解思路清晰，实现方式略有差异。

### 所选的题解
- **作者：zajasi (赞：4)  星级：4星**
  - **关键亮点**：思路清晰，通过函数`check`判断矩阵是否美观，在`main`函数中循环枚举旋转情况，代码结构清晰。
  - **重点代码**：
```cpp
bool check(){
    if(a[1][1]<a[1][2]&&a[2][1]<a[2][2]&&a[1][1]<a[2][1]&&a[1][2]<a[2][2])return true;
    return false;
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        int f=0;
        cin>>a[1][1]>>a[1][2]>>a[2][1]>>a[2][2];
        for(int i=1;i<=5;i++){
            int x=a[1][1];
            a[1][1]=a[2][1];
            a[2][1]=a[2][2];
            a[2][2]=a[1][2];
            a[1][2]=x;
            if(check()){
                cout<<"YES\n";
                f=1;
                break;
            }
        }
        if(f==0) cout<<"NO\n";    
    }
    return 0;
}
```
  - **核心实现思想**：`check`函数判断矩阵是否美观，主函数中循环旋转矩阵并调用`check`函数判断，若有一次满足则输出`YES`，否则输出`NO`。
- **作者：LegendaryGrandmaster (赞：2)  星级：4星**
  - **关键亮点**：直接列出矩阵旋转的四种情况，并分别判断是否满足美观条件，代码简洁明了。
  - **重点代码**：
```cpp
int main()
{
    int t;
    cin>>t;
    while(t--){
        int a,b,c,d;
        cin>>a>>b;
        cin>>c>>d;
        bool ok=0;
        if(a<b&&a<c&&b<d&&c<d)ok=1;
        else if(c<a&&c<d&&a<b&&d<b)ok=1;
        else if(d<c&&d<b&&c<a&&b<a)ok=1;
        else if(b<d&&b<a&&d<c&&a<c)ok=1;
        cout<<(ok?"YES":"NO")<<'\n';
    }
}
```
  - **核心实现思想**：读入矩阵元素后，依次判断矩阵旋转0次、90度、180度、270度后的情况是否满足美观条件，满足则输出`YES`，否则输出`NO`。
- **作者：VertexNeko (赞：1)  星级：4星**
  - **关键亮点**：通过找规律，利用异或运算判断矩阵能否通过旋转变得美观，避免了直接枚举旋转情况，提供了新颖的思路。
  - **重点代码**：
```cpp
inline void solve() {
    int map[10][10];
    cin >> map[1][1] >> map[1][2];
    cin >> map[2][1] >> map[2][2];
    bool flag1 = (map[1][1] < map[2][1]) ^ (map[1][2] < map[2][2]);
    bool flag2 = (map[1][1] < map[1][2]) ^ (map[2][1] < map[2][2]);
    bool flag3 = flag1 | flag2;
    if (flag3 == 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
}
```
  - **核心实现思想**：通过异或运算判断矩阵元素间大小关系是否符合规律，`flag3`为`1`则说明无法通过旋转得到符合题意的矩阵，输出`NO`，否则输出`YES`。

### 最优关键思路或技巧
1. **暴力枚举**：利用矩阵旋转4次还原的特性，枚举所有可能的旋转情况并判断是否美观，是较为直接有效的方法。
2. **找规律优化**：如VertexNeko的题解，通过观察旋转后符合要求矩阵的特征，利用异或运算进行判断，减少了枚举的过程，优化了算法。

### 拓展
同类型题通常围绕矩阵的变换与条件判断展开，类似算法套路包括对矩阵特定操作后的状态枚举与规律总结。例如对于更大矩阵的旋转操作，可能需要总结更复杂的规律，或者采用更高效的数据结构来存储和操作矩阵。

### 推荐题目
1. [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：通过模拟灯的开关操作，考察对基本操作的枚举与逻辑判断。
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)：需要枚举不同的数字组合，判断是否满足质数条件，与本题枚举判断思路类似。
3. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：通过枚举二项式展开的各项，结合组合数学知识求解系数，考察枚举与数学知识结合。

### 个人心得摘录与总结
无。 

---
处理用时：42.33秒