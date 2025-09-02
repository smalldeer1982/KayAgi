# 题目信息

# Masha and two friends

## 题目描述

Masha 有一个宽度为 $n$，长度为 $m$ 的国际象棋盘。

这个象棋盘左下角的坐标为 $(1,1)$，且颜色为白色。(象棋盘是黑白相间的)

现在 Maxim 首先选择了一个矩形，并把这个矩形内的象棋盘刷成了白色，然后 Denis 又选择了一个矩形并把这个矩形内的象棋盘刷成了黑色。 (注意先后顺序)

请输出这个象棋盘最后有多少个黑色格子，多少个白色格子。

## 说明/提示

$1\leq t\leq 10^3$

$1 \leq n,m \leq 10^9$

$1 \leq x1 \leq x2 \leq m$, $1 \leq x3 \leq x4 \leq m$

$1 \leq y1 \leq y2 \leq n$, $1 \leq y3 \leq y4 \leq n$

## 样例 #1

### 输入

```
5
2 2
1 1 2 2
1 1 2 2
3 4
2 2 3 2
3 1 4 3
1 5
1 1 5 1
3 1 5 1
4 4
1 1 4 2
1 3 4 4
3 4
1 2 4 2
2 1 3 3
```

### 输出

```
0 4
3 9
2 3
8 8
4 8
```

# AI分析结果

### 题目内容
# Masha和两个朋友

## 题目描述
Masha有一个宽度为$n$，长度为$m$的国际象棋盘。
这个象棋盘左下角的坐标为$(1,1)$，且颜色为白色。(象棋盘是黑白相间的)
现在Maxim首先选择了一个矩形，并把这个矩形内的象棋盘刷成了白色，然后Denis又选择了一个矩形并把这个矩形内的象棋盘刷成了黑色。 (注意先后顺序)
请输出这个象棋盘最后有多少个黑色格子，多少个白色格子。

## 说明/提示
$1\leq t\leq 10^3$
$1 \leq n,m \leq 10^9$
$1 \leq x1 \leq x2 \leq m$, $1 \leq x3 \leq x4 \leq m$
$1 \leq y1 \leq y2 \leq n$, $1 \leq y3 \leq y4 \leq n$

## 样例 #1
### 输入
```
5
2 2
1 1 2 2
1 1 2 2
3 4
2 2 3 2
3 1 4 3
1 5
1 1 5 1
3 1 5 1
4 4
1 1 4 2
1 3 4 4
3 4
1 2 4 2
2 1 3 3
```
### 输出
```
0 4
3 9
2 3
8 8
4 8
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过数学计算来确定最终棋盘上黑白格子的数量。关键在于准确计算初始棋盘的黑白格数量、两次染色矩形内的黑白格数量以及两矩形交集部分的黑白格数量。各题解的不同主要体现在计算这些数量的具体方式和代码实现上。有的题解通过函数封装计算逻辑，使代码结构更清晰；有的则直接在主程序中进行计算。在处理矩形交集时，多数题解采用比较坐标的方式判断是否相交并确定交集坐标。

### 所选的题解
 - **作者：Siyuan（5星）**
    - **关键亮点**：思路清晰，先给出白色格子增量的计算公式，通过函数封装计算矩形内黑白格子数量，代码简洁明了，逻辑清晰。
    - **重点代码**：
```cpp
long long getblack(int x1,int y1,int x2,int y2) {
    bool opt=(x1+y1)&1;
    int n=x2-x1+1,m=y2-y1+1;
    if(opt) return 1LL*n*(m/2)+((m&1)?(n/2)+(n&1):0);
    else return 1LL*n*(m/2)+((m&1)?(n/2):0);
}
long long getwhite(int x1,int y1,int x2,int y2) {
    return 1LL*(x2-x1+1)*(y2-y1+1)-getblack(x1,y1,x2,y2);
}
int main() {
    int T;
    for(scanf("%d",&T);T--;) {
        int n,m,x1,y1,x2,y2,x3,y3,x4,y4;
        scanf("%d%d",&n,&m),n^=m^=n^=m;
        long long s1=getwhite(1,1,n,m);
        scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        int u=std::max(x1,x3),d=std::min(x2,x4);
        int l=std::max(y1,y3),r=std::min(y2,y4);
        if(u<=d&&l<=r) {
            s1+=getblack(x1,y1,x2,y2)-getblack(u,l,d,r)-getwhite(x3,y3,x4,y4);
        } else {
            s1+=getblack(x1,y1,x2,y2)-getwhite(x3,y3,x4,y4);
        }
        printf("%I64d %I64d\n",s1,1LL*n*m-s1);
    }
    return 0;
}
```
核心实现思想：`getblack`函数根据矩形左下角坐标的奇偶性及长宽计算黑色格子数，`getwhite`函数通过矩形总面积减去黑色格子数得到白色格子数。在`main`函数中，先计算初始棋盘白色格子数，再根据两矩形是否相交，按公式计算最终白色格子数。

 - **作者：Ted_Tong（4星）**
    - **关键亮点**：分析过程详细，从棋盘填色的特殊情况入手，逐步讲解思路，代码逻辑符合分析过程，容易理解。
    - **重点代码**：
```cpp
//  奇偶相同是白
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll t,n,m,black,white;
int main() {
    cin>>t;
    for (int tt=1; tt<=t; tt++) {
        cin>>n>>m;
        black=white=(n*m)/2;
        if ((n*m) & 1) {
            white++;
        }
        ll ax1,ax2,ay1,ay2,bx1,bx2,by1,by2;
        cin>>ax1>>ay1>>ax2>>ay2>>bx1>>by1>>bx2>>by2;
        //white
        ll achang=ax2-ax1+1,akuan=ay2-ay1+1;
        white+=(achang*akuan)/2;
        black-=(achang*akuan)/2;
        if ((achang & 1) && (akuan & 1) && ((ax1 & 1)!=(ay1 & 1))) {
            white++;
            black--;
        }
        //black
        achang=bx2-bx1+1;
        akuan=by2-by1+1;
        white-=(achang*akuan)/2;
        black+=(achang*akuan)/2;
        if ((achang & 1) && (akuan & 1) && ((bx1 & 1)==(by1 & 1))) {
            white--;
            black++;
        }
        //cover
        ll x1=max(ax1,bx1),y1=max(ay1,by1),x2=min(ax2,bx2),y2=min(ay2,by2); 
        if ((x2-x1+1)>0 && (y2-y1+1)>0) {
            achang=x2-x1+1;
            akuan=y2-y1+1;
            white-=(achang*akuan)/2;
            black+=(achang*akuan)/2;
            if ((achang & 1) && (akuan & 1) && ((x1 & 1)!=(y1 & 1))) {
                white--;
                black++;
            }
        }
        cout<<white<<" "<<black<<endl;
    }
    return 0;
}
```
核心实现思想：先初始化棋盘黑白格子数，根据输入的染色矩形长宽及左下角坐标的奇偶性，分别计算涂白和涂黑操作对黑白格子数的影响，最后处理两矩形交集部分对黑白格子数的改变。

 - **作者：WuMin4（4星）**
    - **关键亮点**：通过宏定义封装计算矩形黑白格子数的逻辑，代码简洁紧凑，对矩形交集的处理清晰明确。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define bc(x,y,xx,yy) (x>xx||y>yy?0:(xx-x+1)*(yy-y+1)%2==0?(xx-x+1)*(yy-y+1)/2:(x+y)%2==0?(xx-x+1)*(yy-y+1)/2:(xx-x+1)*(yy-y+1)/2+1)
#define wc(x,y,xx,yy) ((xx-x+1)*(yy-y+1)-bc(x,y,xx,yy))
using namespace std;
#define int long long
int T,n,m,x,y,_x,_y,X,Y,_X,_Y;
signed main() {
	cin>>T;
	while(T--){
		cin>>n>>m;
		cin>>x>>y>>_x>>_y;
		cin>>X>>Y>>_X>>_Y;
		cout<<wc(1,1,n,m)+bc(x,y,_x,_y)-wc(X,Y,_X,_Y)-bc(max(x,X),max(y,Y),min(_x,_X),min(_y,_Y))<<" ";
		cout<<bc(1,1,n,m)-bc(x,y,_x,_y)+wc(X,Y,_X,_Y)+bc(max(x,X),max(y,Y),min(_x,_X),min(_y,_Y))<<endl;
	}
	return 0; 
}
```
核心实现思想：通过`bc`宏计算矩形内黑色格子数，`wc`宏通过矩形总面积减去黑色格子数得到白色格子数。在`main`函数中，按公式计算最终黑白格子数，其中涉及初始棋盘及两次染色矩形和它们交集的黑白格子数计算。

### 最优关键思路或技巧
通过函数或宏封装计算矩形内黑白格子数量的逻辑，使代码更模块化、易读。利用坐标比较判断矩形是否相交并确定交集坐标，准确计算交集部分对黑白格子数量的影响。

### 可拓展之处
同类型题可涉及多次染色操作，或改变棋盘的初始颜色分布等。类似算法套路是通过数学分析确定每次操作对目标量（如黑白格子数）的影响，利用容斥原理处理操作间的重叠部分。

### 洛谷题目推荐
 - [P1083 借教室](https://www.luogu.com.cn/problem/P1083)：涉及区间操作和判断可行性，可类比本题对矩形区域的操作思路。
 - [P2141 珠心算测验](https://www.luogu.com.cn/problem/P2141)：通过数学计算和统计来解决问题，与本题计算黑白格子数思路类似。
 - [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：运用数学方法分析和解决连续自然数求和问题，锻炼数学思维，与本题数学分析思路相关。

### 个人心得摘录与总结
部分作者提到这题细节较多，如在计算矩形内黑白格子数时，要考虑矩形长宽奇偶性以及左下角格子颜色对数量的影响。在处理两矩形交集时，需准确判断是否相交及计算交集坐标。这些心得提示在解决此类问题时要注重细节，全面考虑各种情况。 

---
处理用时：111.66秒