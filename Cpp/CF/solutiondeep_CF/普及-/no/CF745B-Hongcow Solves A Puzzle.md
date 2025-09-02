# 题目信息

# Hongcow Solves A Puzzle

## 题目描述

Hongcow likes solving puzzles.

One day, Hongcow finds two identical puzzle pieces, with the instructions "make a rectangle" next to them. The pieces can be described by an $ n $ by $ m $ grid of characters, where the character 'X' denotes a part of the puzzle and '.' denotes an empty part of the grid. It is guaranteed that the puzzle pieces are one 4-connected piece. See the input format and samples for the exact details on how a jigsaw piece will be specified.

The puzzle pieces are very heavy, so Hongcow cannot rotate or flip the puzzle pieces. However, he is allowed to move them in any directions. The puzzle pieces also cannot overlap.

You are given as input the description of one of the pieces. Determine if it is possible to make a rectangle from two identical copies of the given input. The rectangle should be solid, i.e. there should be no empty holes inside it or on its border. Keep in mind that Hongcow is not allowed to flip or rotate pieces and they cannot overlap, i.e. no two 'X' from different pieces can share the same position.

## 说明/提示

For the first sample, one example of a rectangle we can form is as follows

`<br></br>111222<br></br>111222<br></br>`For the second sample, it is impossible to put two of those pieces without rotating or flipping to form a rectangle.

In the third sample, we can shift the first tile by one to the right, and then compose the following rectangle:

`<br></br>.....<br></br>..XX.<br></br>.....<br></br>.....<br></br>.....<br></br>`

## 样例 #1

### 输入

```
2 3
XXX
XXX
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2
.X
XX
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 5
.....
..X..
.....
.....
.....
```

### 输出

```
YES
```

# AI分析结果

### 题目内容（中文重写）
# Hongcow 解谜题

## 题目描述
Hongcow 喜欢解谜。

有一天，Hongcow 发现了两个相同的拼图碎片，旁边还有“拼成一个矩形”的说明。这些碎片可以用一个 $n$ 行 $m$ 列的字符网格来描述，其中字符 'X' 表示拼图的一部分，'.' 表示网格的空白部分。保证拼图碎片是一个四连通的部分。有关拼图碎片的具体说明，请参阅输入格式和示例。

拼图碎片非常重，所以 Hongcow 不能旋转或翻转拼图碎片。但是，他可以向任何方向移动它们。拼图碎片也不能重叠。

给定其中一个碎片的描述作为输入。判断是否可以用两个相同的给定输入碎片拼成一个矩形。矩形应该是实心的，即内部或边界上不应有空白的洞。请记住，Hongcow 不允许翻转或旋转碎片，并且它们不能重叠，即不同碎片的两个 'X' 不能共享相同的位置。

## 说明/提示
对于第一个样例，我们可以拼成的一个矩形示例如下

```
111222
111222
```
对于第二个样例，不旋转或翻转这些碎片就不可能拼成一个矩形。

在第三个样例中，我们可以将第一个碎片向右移动一格，然后组成以下矩形：

```
.....
..XX.
.....
.....
.....
```

## 样例 #1
### 输入
```
2 3
XXX
XXX
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
2 2
.X
XX
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
5 5
.....
..X..
.....
.....
.....
```
### 输出
```
YES
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是通过找出包含所有 'X' 的最小矩阵，然后判断该矩阵中是否只包含 'X' 来解决问题。具体做法是先找出所有 'X' 的横纵坐标的最大最小值，从而确定矩阵的边界，再通过两种方式判断矩阵是否符合要求：一是遍历矩阵看是否存在非 'X' 字符；二是比较矩阵面积和 'X' 的数量是否相等。

### 所选题解
- **作者：Yizhixiaoyun（5星）**
    - **关键亮点**：思路清晰，代码规范，使用宏定义简化输出，并且有自定义的输入函数。
- **作者：_xbn（4星）**
    - **关键亮点**：代码简洁，直接通过比较矩形面积和 'X' 的数量来判断，实现简单。
- **作者：S__X（4星）**
    - **关键亮点**：思路清晰，代码简洁易懂，通过一次遍历完成 'X' 坐标最值的记录和数量统计。

### 重点代码
#### Yizhixiaoyun 的代码
```cpp
#include<bits/stdc++.h>
#define ok puts("YES")
#define no puts("NO")
using namespace std;
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-48;
        c=getchar();
    }
    return x*f;
}
const int inf=1e9;
const int maxn=502;
int n,m;
bool flag;
string s[maxn];
struct node{
    int x,y;
}fir,lst;
inline void init(){
    n=read();m=read();fir.x=inf;fir.y=inf;
    for(register int i=1;i<=n;++i){
        cin>>s[i];s[i]=" "+s[i];
        for(register int j=1;j<=m;++j){
            if(s[i][j]=='X'){
                fir.x=min(fir.x,i);fir.y=min(fir.y,j);
                lst.x=max(lst.x,i);lst.y=max(lst.y,j);
            }
        }
    }
}
int main(){
    init();
    for(register int i=fir.x;i<=lst.x;++i){
        for(register int j=fir.y;j<=lst.y;++j){
            if(s[i][j]!='X') no,exit(0);
        }
    }
    ok;
}
```
**核心实现思想**：先通过 `init` 函数读取输入并找出所有 'X' 的横纵坐标的最小和最大值，然后遍历该矩阵，若存在非 'X' 字符则输出 `NO`，否则输出 `YES`。

#### _xbn 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
int n,m,l,r,t,b,ans;
string str;
int main()
{
    cin>>n>>m;
    l=t=MAXN;
    r=b=-1;
    for(int i=0;i<n;i++)
    {
        cin>>str;
        for(int j=0;j<m;j++)
        {
            if(str[j]=='X')
            {
                ans++;
                l=min(l,j);
                r=max(r,j);
                t=min(t,i);
                b=max(b,i);
            }
        }
    }
    if((b-t+1)*(r-l+1)==ans)cout<<"YES";
    else cout<<"NO";
    return 0;
}
```
**核心实现思想**：在读取输入时统计 'X' 的数量，并记录其横纵坐标的最小和最大值，最后比较矩形面积和 'X' 的数量是否相等，相等则输出 `YES`，否则输出 `NO`。

#### S__X 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,max_x,max_y,min_x=1e9,min_y=1e9,sum;
char a;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a;
            if(a=='X') {
                ans++;//统计字符个数
                max_x=max(max_x,j);//找出横纵坐标最大最小值
                min_x=min(min_x,j);
                max_y=max(max_y,i);
                min_y=min(min_y,i);
            }
        }
    }
    sum=(max_x-min_x+1)*(max_y-min_y+1);
    if(sum==ans) printf("YES");
    else printf("NO");
    return 0;
}
```
**核心实现思想**：在读取输入时统计 'X' 的数量并记录其横纵坐标的最大最小值，计算矩形面积，比较面积和 'X' 数量是否相等，相等输出 `YES`，否则输出 `NO`。

### 最优关键思路或技巧
- 可以通过一次遍历找出所有 'X' 的横纵坐标的最大最小值，从而确定包含所有 'X' 的最小矩阵的边界。
- 比较矩形面积和 'X' 的数量是否相等可以避免再次遍历矩阵，提高效率。

### 可拓展之处
同类型题可能会有更多的限制条件，如允许旋转或翻转拼图碎片，或者要求拼成特定形状等。类似算法套路可以用于处理其他二维网格中的图形判断问题，如判断连通性、计算图形面积等。

### 推荐题目
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
- [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)
- [P2670 扫雷游戏](https://www.luogu.com.cn/problem/P2670)

### 个人心得
无

---
处理用时：50.02秒