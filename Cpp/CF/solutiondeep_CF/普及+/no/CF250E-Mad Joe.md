# 题目信息

# Mad Joe

## 题目描述

Joe has been hurt on the Internet. Now he is storming around the house, destroying everything in his path.

Joe's house has $ n $ floors, each floor is a segment of $ m $ cells. Each cell either contains nothing (it is an empty cell), or has a brick or a concrete wall (always something one of three). It is believed that each floor is surrounded by a concrete wall on the left and on the right.

Now Joe is on the $ n $ -th floor and in the first cell, counting from left to right. At each moment of time, Joe has the direction of his gaze, to the right or to the left (always one direction of the two). Initially, Joe looks to the right.

Joe moves by a particular algorithm. Every second he makes one of the following actions:

- If the cell directly under Joe is empty, then Joe falls down. That is, he moves to this cell, the gaze direction is preserved.
- Otherwise consider the next cell in the current direction of the gaze. 
  - If the cell is empty, then Joe moves into it, the gaze direction is preserved.
  - If this cell has bricks, then Joe breaks them with his forehead (the cell becomes empty), and changes the direction of his gaze to the opposite.
  - If this cell has a concrete wall, then Joe just changes the direction of his gaze to the opposite (concrete can withstand any number of forehead hits).

Joe calms down as soon as he reaches any cell of the first floor.

The figure below shows an example Joe's movements around the house.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF250E/aabe6062681eed440c39038fe1d895d0f5c78597.png)Determine how many seconds Joe will need to calm down.

## 样例 #1

### 输入

```
3 5
..+.#
#+..+
+.#+.
```

### 输出

```
14```

## 样例 #2

### 输入

```
4 10
...+.##+.+
+#++..+++#
++.#++++..
.+##.++#.+
```

### 输出

```
42
```

## 样例 #3

### 输入

```
2 2
..
++
```

### 输出

```
Never```

# AI分析结果

### 题目内容
# 疯狂的乔

## 题目描述
乔在网上受到了伤害。现在他在房子里怒气冲冲地走来走去，破坏他所经过路径上的一切东西。

乔的房子有 $n$ 层，每层是一段包含 $m$ 个单元格的区域。每个单元格要么什么都没有（即空单元格），要么有一块砖头，要么有一堵混凝土墙（总是这三种情况之一）。假定每层的左右两侧都被混凝土墙围绕。

现在乔在第 $n$ 层，从左到右数的第一个单元格。在每一个时刻，乔都有一个注视方向，要么向右，要么向左（总是这两个方向之一）。最初，乔向右看。

乔按照特定的算法移动。每一秒他会执行以下操作之一：
- 如果乔正下方的单元格为空，那么乔就会掉下去。也就是说，他移动到这个单元格，注视方向保持不变。
- 否则，考虑当前注视方向上的下一个单元格。
  - 如果这个单元格为空，那么乔就移动到这个单元格，注视方向保持不变。
  - 如果这个单元格有砖头，那么乔就用额头把它们打破（这个单元格变为空单元格），并将注视方向改为相反方向。
  - 如果这个单元格有混凝土墙，那么乔仅仅将注视方向改为相反方向（混凝土可以承受任意次数的额头撞击）。

乔一旦到达第一层的任何一个单元格就会平静下来。

下图展示了乔在房子里移动的一个示例。
![乔的移动示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF250E/aabe6062681eed440c39038fe1d895d0f5c78597.png)
确定乔需要多少秒才能平静下来。

## 样例 #1
### 输入
```
3 5
..+.#
#+..+
+.#+.
```
### 输出
```
14
```

## 样例 #2
### 输入
```
4 10
...+.##+.+
+#++..+++#
++.#++++..
.+##.++#.+
```
### 输出
```
42
```

## 样例 #3
### 输入
```
2 2
..
++
```
### 输出
```
Never
```

### 算法分类
模拟

### 题解综合分析与结论
这两道题解都意识到直接暴力模拟会导致时间复杂度达到 $O(nm^2)$ 从而超时，因此都对模拟过程进行了优化。它们的核心思路都是通过记录走过的区间，避免重复计算，从而将时间复杂度降低到 $O(nm)$ 。不同之处在于具体实现细节，如指针的使用方式、边界条件的判断以及代码的结构等。

### 题解1（作者：bellmanford  5星）
- **关键亮点**：代码简洁明了，逻辑清晰。通过合理设置指针和循环，有效地处理了乔在各层的移动情况，并且在代码开头使用自定义的 `read` 函数来提高输入效率。对边界条件和各种情况的判断处理得当。
- **个人心得**：无
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

#define int long long

int read(){
    int x=0,y=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') y=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*y;
}

int n,m,tim=0;
char Map[105][10005];
void solve(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",Map[i]+1);
        Map[i][0]=Map[i][m+1]='#';//将两边变为墙 
    }
    int now=1,fx=1;//现在所处的位置，也就是某一层的出发点和面对的方向 
    for(int i=1;i<n;i++){//只用枚举前 n-1 层，因为到了最后一层就结束了 
        if(Map[i+1][now]=='.'){//特判直接下掉的情况 
            tim++;
            continue ;
        }
        int l=now-1,r=now+1;//走过的区间的左边过去一个和右边过去一个 
        while(1){
            if(Map[i][l]=='#'&&Map[i][r]=='#') return (void)(printf("Never\n"));//两边都是墙就不可能走出去了 
            tim+=r-l-2;//累加重复走过的地方 
            if(fx==1){
                while(Map[i][r]=='.'&&Map[i+1][r]!='.') r++,tim++;//如果前面有路且不会掉下去就增加右端点 
                if(Map[i][r]=='.'){
                    now=r,tim+=2;//因为前面的 while ，所以此时如果有路就意味着前面会掉下去，往前走和下掉各花费一秒，然后更新出发点 
                    break;
                }
                if(Map[i][r]=='+') fx=-fx,tim++,Map[i][r]='.';//遇到砖头的情况 
                else if(Map[i][r]=='#') fx=-fx,tim++;//遇到墙的情况 
            }
            else{//另一个方向同理 
                while(Map[i][l]=='.'&&Map[i+1][l]!='.') l--,tim++;
                if(Map[i][l]=='.'){
                    now=l,tim+=2;
                    break;
                }
                if(Map[i][l]=='+') fx=-fx,tim++,Map[i][l]='.';
                else if(Map[i][l]=='#') fx=-fx,tim++;
            }
        }
    }
    return (void)(printf("%lld\n",tim));
}

signed main(){
    solve();
}
```
核心实现思想：首先读取输入并初始化地图，将每层左右两端设为墙。然后从顶层开始遍历，对于每一层，根据乔当前位置下方是否为空来判断是否直接掉落。若不直接掉落，则通过双指针记录走过区间，根据乔的注视方向和单元格类型进行移动、破砖、转向等操作，同时累加时间。若某层左右两端都为墙则输出 `Never`，否则计算并输出总时间。

### 题解2（作者：_edge_  4星）
- **关键亮点**：通过自定义函数 `solvel` 和 `solver` 分别处理向左和向右移动的情况，代码结构较为清晰。在处理过程中，通过指针扩张来优化移动过程，减少不必要的移动计算。
- **个人心得**：强调了视线方向不变这一条件处理时要注意，否则过不了样例2，同时提到要开 `long long` 类型。
```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=105;
const int INFN=1e4+5;
int n,m,Map[INF][INFN],l,r,ans,ll,rr,fl1,fang;
char ch;
int solvel(int x) {
    #define i x
    ans+=r-l;int fl=0;
    while (Map[i][l-1]==0) {
        if (Map[i+1][l]==0) {fl=1;r=l;return 1;}
        l--,ans++;fl1=0;
    }
    if (Map[i+1][l]==0) {fl=1;r=l;return 1;}
    if (fl) return 1;
    if (Map[i][l-1]==1) {
        Map[i][l-1]=0;
        ans++;fl1=0;
    } 
    else ans++;
    //if (ll==l && r==rr && fl1) {cout<<"Never\n";return 2;}
    return 0;
}
int solver(int x) {
    ans+=r-l;int fl=0;
    while (Map[i][r+1]==0) {
        if (Map[i+1][r]==0) {fl=1;l=r;return 1;}
        r++,ans++;fl1=0;
    }
    if (Map[i+1][r]==0) {fl=1;l=r;return 1;}
    if (fl) return 1;
    if (Map[i][r+1]==1) {
        Map[i][r+1]=0;
        ans++;fl1=0;
    } 
    else ans++;
    return 0;
}
#undef i
signed main()
{
    scanf("%lld %lld ",&n,&m);
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            scanf(" %c",&ch);
            if (ch=='.') Map[i][j]=0;
            else if (ch=='+') Map[i][j]=1;
            else if (ch=='#') Map[i][j]=2;
        }
    }
    for (int i=1;i<=n;i++)
        Map[i][0]=Map[i][m+1]=2;
    l=1,r=1,ans=0;
    for (int i=1;i<=n;i++) {
        while (true) {
            ll=l;rr=r;fl1=1;
            if (fang==0) {
                int r1=solver(i);
                if (r1==1) {fang=0;break;}
                int l1=solvel(i);
                if (l1==1) {fang=1;break;}  
            }
            else {
                int l1=solvel(i);
                if (l1==1) {fang=1;break;}  
                int r1=solver(i);
                if (r1==1) {fang=0;break;}
            }
            //cout<<l<<" "<<r<<" over "<<i<<" "<<ans<<"\n";
            //cout<<l<<" "<<r<<" over "<<i<<" "<<ans<<"\n";
            if (ll==l && rr==r && fl1) {cout<<"Never\n";return 0;}
        }
        //cout<<l<<" "<<r<<" "<<ans<<" break\n";
    }
    cout<<ans+n-1<<"\n";
    return 0;
}
```
核心实现思想：先读取输入并初始化地图，同样将每层两端设为墙。在每一层通过 `while` 循环，根据注视方向调用 `solver` 或 `solvel` 函数，函数内通过指针扩张来模拟乔的移动，根据单元格类型更新地图和时间，若无法移动且未找到掉落点则判断为 `Never`，最后加上向下移动的时间输出结果。

### 最优关键思路或技巧
通过记录走过的区间来避免重复计算，从而优化暴力模拟，将时间复杂度从 $O(nm^2)$ 降低到 $O(nm)$ 。具体实现上，利用双指针分别记录左右边界，在移动过程中，根据单元格类型和乔的注视方向进行相应操作，并累加时间。

### 可拓展之处
此类题目属于模拟优化类型，类似的题目还有很多，通常可以通过寻找重复计算部分并进行优化来解决。例如，一些游戏角色在地图中的移动问题，地图可能存在不同类型的区域，角色按照特定规则移动，要求计算移动到目标位置的时间或判断是否能到达等。

### 洛谷相似题目推荐
 - [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)：字符串变换模拟，需要按照给定规则对字符串进行变换，与本题类似之处在于都需要按照特定规则进行操作并模拟过程。
 - [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：通过模拟填充颜色的过程，考察对二维数组的操作和逻辑判断，与本题在处理二维空间数据上有相似性。
 - [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：马在棋盘上按照特定规则移动并标记访问过的位置，同样是模拟移动过程并记录状态，与本题思路类似。 

---
处理用时：107.01秒