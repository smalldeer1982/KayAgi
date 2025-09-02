# 题目信息

# Young Photographer

## 题目描述

Among other things, Bob is keen on photography. Especially he likes to take pictures of sportsmen. That was the reason why he placed himself in position $ x_{0} $ of a long straight racetrack and got ready to take pictures. But the problem was that not all the runners passed him. The total amount of sportsmen, training at that racetrack, equals $ n $ . And each of them regularly runs distances within a particular segment of the racetrack, which is the same for each sportsman. For example, the first sportsman runs from position $ a_{1} $ to position $ b_{1} $ , the second — from $ a_{2} $ to $ b_{2} $

What is the minimum distance that Bob should move to have a chance to take pictures of each sportsman? Bob can take a picture of a sportsman, if he stands within the segment that this sportsman covers on the racetrack.

## 样例 #1

### 输入

```
3 3
0 7
14 2
4 6
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 年轻的摄影师

## 题目描述
除此之外，鲍勃热衷于摄影。他尤其喜欢拍摄运动员的照片。这就是为什么他站在一条长长的直跑道的位置 \( x_{0} \) 处，准备拍照。但问题是，并非所有的跑步者都会从他身边经过。在那条跑道上训练的运动员总数为 \( n \) 。而且他们每个人都在跑道的特定线段内定期跑步，这对每个运动员来说都是一样的。例如，第一个运动员从位置 \( a_{1} \) 跑到位置 \( b_{1} \) ，第二个运动员从 \( a_{2} \) 跑到 \( b_{2} \) 。

鲍勃要移动的最小距离是多少，才有机会拍摄到每个运动员的照片呢？如果鲍勃站在运动员在跑道上覆盖的线段内，他就可以拍摄该运动员的照片。

## 样例 #1
### 输入
```
3 3
0 7
14 2
4 6
```
### 输出
```
1
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕找出 \( n \) 条线段的公共区间，再计算该区间与点 \( x_{0} \) 的距离。主要有两种方法：
 - **暴力标记法**：利用数组记录每个点被区间覆盖的次数，遍历所有区间进行标记，找出覆盖次数为 \( n \) 的点，计算这些点到 \( x_{0} \) 的距离并取最小值。这种方法直观，但代码量相对较大。
 - **直接计算公共区间法**：通过比较各区间端点，直接计算出公共区间的左右端点 \( left \) 和 \( right \) ，再根据点 \( x_{0} \) 与公共区间的位置关系得出距离。这种方法逻辑较为清晰，代码相对简洁。

解决难点在于处理输入时区间端点可能无序的情况，所有题解都通过比较并交换端点来解决。

### 所选的题解
 - **作者：Miraik (赞：3)  星级：4星 关键亮点：直接计算公共区间的左右端点，逻辑清晰，代码简洁，通过三目运算符简洁地输出结果**
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
int n,k,x,y,l,r=1005;
inline int _max(int x,int y){return x>y?x:y;}
inline int _min(int x,int y){return x<y?x:y;}
inline int _abs(int x){return x>0?x:-x;}
int main(){
    n=read(),k=read();//k为题目中的点x 
    while(n--)
        x=read(),y=read(),//x为l[i]，y为r[i] 
        l=_max(_min(x,y),l),r=_min(_max(x,y),r);//不保证l[i]<r[i]，因此要取max和min 
    //printf("%d %d\n",l,r);
    printf("%d\n",l>r?-1:(k>=l&&k<=r)?0:_min(_abs(k-l),_abs(k-r)));
    //三目运算符：l>r时，输出-1；点在区间内时，输出0；否则输出点与l距离和r距离的较小值（结合第3和第4点） 
    return 0;
}
```
核心实现思想：先通过 `read` 函数读入数据，在循环读入每个区间时，通过 `_max` 和 `_min` 函数处理可能无序的端点，更新公共区间的左右端点 \( l \) 和 \( r \) ，最后通过三目运算符根据公共区间与点 \( k \) 的位置关系输出结果。

 - **作者：AllanPan (赞：0)  星级：4星 关键亮点：思路清晰地分为求出区间交集和计算走进区间最小距离两个步骤，代码简洁明了**
```cpp
#include <iostream>
using namespace std;

int main()
{
    int n, pos, start[105], end[105], a, b;
    int startmax = -1, endmin = 9999;
    cin >> n >> pos;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a >> b;
        start[i] = min(a, b);
        end[i] = max(a, b);
        if (start[i] > startmax)
            startmax = start[i];
        if (end[i] < endmin)
            endmin = end[i];
    }
    if (endmin < startmax)
        cout << -1;
    else
    {
        if (startmax <= pos && pos <= endmin)
            cout << 0;
        else
        {
            if (pos < startmax)
                cout << (startmax - pos);
            else
            {
                cout << (pos - endmin);
            }
        }
    }
    return 0;
}
```
核心实现思想：先读入 \( n \) 和点 \( pos \) ，在循环读入每个区间时，记录每个区间的起点和终点，并更新最靠右的起点 `startmax` 和最靠左的终点 `endmin` ，以此得到公共区间，最后根据公共区间与点 `pos` 的位置关系输出结果。

### 最优关键思路或技巧
直接计算公共区间法更为简洁高效，通过比较各区间端点直接确定公共区间，避免了暴力标记法中对每个点的遍历标记，减少了时间和空间复杂度。

### 拓展思路
此类题目属于区间相关的模拟问题，类似套路包括处理区间合并、区间查询等。同类型题可能会增加区间的维度，如二维区间问题，或者对区间的条件进行更复杂的限制。

### 洛谷相似题目
 - [P1197 地毯填补问题](https://www.luogu.com.cn/problem/P1197)
 - [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
 - [P2036 [COCI2008-2009#2] PERKET](https://www.luogu.com.cn/problem/P2036) 

---
处理用时：60.69秒