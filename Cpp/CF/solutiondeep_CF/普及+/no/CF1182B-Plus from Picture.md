# 题目信息

# Plus from Picture

## 题目描述

You have a given picture with size $ w \times h $ . Determine if the given picture has a single "+" shape or not. A "+" shape is described below:

- A "+" shape has one center nonempty cell.
- There should be some (at least one) consecutive non-empty cells in each direction (left, right, up, down) from the center. In other words, there should be a ray in each direction.
- All other cells are empty.

Find out if the given picture has single "+" shape.

## 说明/提示

In the first example, the given picture contains one "+".

In the second example, two vertical branches are located in a different column.

In the third example, there is a dot outside of the shape.

In the fourth example, the width of the two vertical branches is $ 2 $ .

In the fifth example, there are two shapes.

In the sixth example, there is an empty space inside of the shape.

## 样例 #1

### 输入

```
5 6
......
..*...
.****.
..*...
..*...
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 5
..*..
****.
.*...
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
7 7
.......
...*...
..****.
...*...
...*...
.......
.*.....
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
5 6
..**..
..**..
******
..**..
..**..
```

### 输出

```
NO
```

## 样例 #5

### 输入

```
3 7
.*...*.
***.***
.*...*.
```

### 输出

```
NO
```

## 样例 #6

### 输入

```
5 10
..........
..*.......
.*.******.
..*.......
..........
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
## 从图片中识别加号

### 题目描述
你有一张尺寸为 $ w \times h $ 的图片。判断给定的图片中是否只有一个 “+” 形状。“+” 形状的定义如下：
- “+” 形状有一个中心非空单元格。
- 从中心向每个方向（左、右、上、下）都应该有一些（至少一个）连续的非空单元格。换句话说，每个方向都应该有一条射线。
- 所有其他单元格都是空的。

找出给定的图片中是否只有一个 “+” 形状。

### 说明/提示
在第一个样例中，给定的图片包含一个 “+”。
在第二个样例中，两条垂直分支位于不同的列。
在第三个样例中，形状外有一个点。
在第四个样例中，两条垂直分支的宽度为 2。
在第五个样例中，有两个形状。
在第六个样例中，形状内部有一个空白空间。

### 样例 #1
#### 输入
```
5 6
......
..*...
.****.
..*...
..*...
```
#### 输出
```
YES
```

### 样例 #2
#### 输入
```
3 5
..*..
****.
.*...
```
#### 输出
```
NO
```

### 样例 #3
#### 输入
```
7 7
.......
...*...
..****.
...*...
...*...
.......
.*.....
```
#### 输出
```
NO
```

### 样例 #4
#### 输入
```
5 6
..**..
..**..
******
..**..
..**..
```
#### 输出
```
NO
```

### 样例 #5
#### 输入
```
3 7
.*...*.
***.***
.*...*.
```
#### 输出
```
NO
```

### 样例 #6
#### 输入
```
5 10
..........
..*.......
.*.******.
..*.......
..........
```
#### 输出
```
NO
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是围绕枚举来判断图片中是否只有一个 “+” 形状。不同题解的实现细节有所差异，但大多是先找到可能的中心点，再向四个方向扩展，通过统计 `*` 的数量或检查周围点的情况来判断是否符合 “+” 形状的定义。
- **思路对比**：部分题解直接枚举中心点，向四个方向搜索并统计 `*` 个数与总数比较；部分题解通过统计不同周围情况的 `*` 数量来判断；还有题解通过将找到的 “+” 形状的 `*` 置为 `.` ，再检查是否有多余的 `*` 。
- **算法要点**：主要是枚举所有可能的中心点，然后进行四个方向的扩展和条件判断。
- **解决难点**：关键在于准确判断 “+” 形状的特征，如中心的唯一性、四个方向的连续性以及是否有多余的 `*` 。

### 高评分题解
- **w9095（4星）**：
    - **关键亮点**：提供了一种码量较小且时间复杂度严格为 $O(wh)$ 的做法。通过统计地图中 `*` 周围四联通有不同数量 `*` 的位置的数量，利用 “+” 形图形的性质进行判断，思路新颖独特。
    - **个人心得**：无
- **alex_liu（4星）**：
    - **关键亮点**：使用简单的 dfs 对每一个点进行深搜，向四个方向统计 `*` 的个数，先特判有一个方向为 0 的情况，再统计能连接到的所有 `*` 并与总的 `*` 数量比较，思路清晰，代码实现简洁。
    - **个人心得**：做完题思考后发现本题不会出现有两个或以上满足条件的点，并给出了证明。
- **灵光一闪（4星）**：
    - **关键亮点**：先找到一个上下左右都是 `*` 的 `*` 作为中心点，然后向四周循环到没有 `*` ，统计 `*` 的数量并与总数比较，一旦发现有多余的就直接判断为 `NO` ，代码逻辑简单易懂。
    - **个人心得**：无

### 重点代码
#### w9095 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int w,h,cnt[5];
char map1[501][501];
int main()
{
    scanf("%d%d",&w,&h);
    for(int i=0;i<w;i++)
        scanf("%s",map1[i]);
    for(int i=0;i<w;i++)
        for(int j=0;j<h;j++)
            {
            int ans1=0,ans2=0;
            if(map1[i][j]!='*')continue; 
            if(i-1>=0&&map1[i-1][j]=='*')ans1++;
            if(i+1<w&&map1[i+1][j]=='*')ans1++; 
            if(j-1>=0&&map1[i][j-1]=='*')ans2++;
            if(j+1<h&&map1[i][j+1]=='*')ans2++; 
            if(ans1%2&&ans2%2) 
               { 
                printf("NO\n");
                return 0;
               }
            cnt[ans1+ans2]++;
            }
    if(cnt[0]==0&&cnt[1]==4&&cnt[3]==0&&cnt[4]==1)printf("YES\n"); 
    else printf("NO\n");
    return 0;
}
```
**核心实现思想**：通过遍历地图，统计每个 `*` 周围四联通 `*` 的数量，根据 “+” 形图形的性质判断是否满足条件。

#### alex_liu 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,all;
char c[505][505];
inline bool check(int x,int y){
    if(x<1||x>n||y<1||y>m)return 0;
    return 1;
}
inline int dfs(int x,int y){
    int x1=x-1,x2=x+1,x3=x,x4=x,y1=y,y2=y,y3=y+1,y4=y-1,cnt=0,cnt1=0,cnt2=0,cnt3=0,cnt4=0;
    while(!(c[x1][y1]^'*')&&check(x1,y1))++cnt1,--x1;
    while(!(c[x2][y2]^'*')&&check(x2,y2))++cnt2,++x2;
    while(!(c[x3][y3]^'*')&&check(x3,y3))++cnt3,++y3;
    while(!(c[x4][y4]^'*')&&check(x4,y4))++cnt4,--y4;
    cnt=cnt1+cnt2+cnt3+cnt4;
    if(cnt1&&cnt2&&cnt3&&cnt4)return cnt; 
    return -1;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c[i][j];
            all+=(c[i][j]^'*'?0:1);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(!(c[i][j]^'*')){
                if(dfs(i,j)+1==all)ans++;
            }
        }
    }
    puts(ans==1?"YES":"NO");
    return 0;
}
```
**核心实现思想**：使用 dfs 对每个 `*` 点进行搜索，向四个方向统计 `*` 的个数，若四个方向都有 `*` 且统计的个数与总数相等，则认为是一个有效的 “+” 形状。

#### 灵光一闪的代码
```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
char c[666][666];
int num,n,m;
void work(int x,int y){
    for(int i=x;c[i][y]=='*';i++){
        num--;
    }
    for(int i=x;c[i][y]=='*';i--){
        num--;
    }
    for(int j=y;c[x][j]=='*';j--){
        num--;
    }
    for(int j=y;c[x][j]=='*';j++){
        num--;
    }
    num+=3;
    if(num==0){
        puts("YES");
        exit(0);
    }
    else{
        puts("NO");
        exit(0);
    }
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c[i][j];
            if(c[i][j]=='*'){
                num++;
            }
        }
    }
    for(int i=1;i<n-1;i++){
        for(int j=1;j<m-1;j++){
            if(c[i-1][j]=='*'&&c[i+1][j]=='*'&&c[i][j-1]=='*'&&c[i][j+1]=='*'){
                work(i,j);
            }
        }
    }
    puts("NO");
    return 0;
}
```
**核心实现思想**：先统计 `*` 的总数，找到一个上下左右都是 `*` 的 `*` 作为中心点，向四周循环到没有 `*` ，统计 `*` 的数量并与总数比较，根据结果判断是否为有效的 “+” 形状。

### 关键思路或技巧
- **枚举中心点**：大多数题解都采用枚举所有可能的中心点，再向四个方向扩展的方法，这是解决此类问题的基本思路。
- **统计 `*` 数量**：通过统计 `*` 的总数和四个方向的 `*` 数量，进行比较判断是否符合 “+” 形状的定义。
- **利用图形性质**：如 w9095 的题解，通过统计不同周围情况的 `*` 数量，利用 “+” 形图形的性质进行判断，减少了不必要的搜索。

### 拓展思路
同类型题可能会有不同的图形判断，如判断其他形状（如矩形、三角形等）是否在给定的矩阵中唯一存在。类似算法套路还是以枚举和模拟为主，通过对图形特征的分析和条件判断来解决问题。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)

### 个人心得摘录与总结
- **alex_liu**：做完题思考后发现本题不会出现有两个或以上满足条件的点，并给出了证明。这启示我们在解题后可以进一步思考问题的本质，加深对题目的理解。

---
处理用时：71.68秒