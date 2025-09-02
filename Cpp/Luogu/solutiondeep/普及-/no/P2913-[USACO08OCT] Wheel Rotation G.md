# 题目信息

# [USACO08OCT] Wheel Rotation G

## 题目描述

Farmer John has an old-time thresher (wheat harvester) that requires belts to be installed on various gears to turn the parts. The engine drives pulley 1 in a clockwise direction which attaches via a belt to pulley 2. Pulley 2 attaches via a belt to pulley 3 and so on through a total of N (2 <= N <= 1,000) pulleys (and N-1 belts).

The diagram above depicts the two ways a belt can be installed between two gears. In this illustration, pulley 1's belt directly drives pulley 2 (a 'straight' connection) and thus they will rotate in the same direction. Pulley 3 drives pulley 4 via a 'crossed belt' that reverses the direction of the rotation.

Given a list of the belt types that connect the pulleys along with the fact that pulley 1 is driven in a clockwise direction by the engine, determine the drive direction of pulley N. Each belt is described by three integers:

```cpp
* S_i -- the driving (source) pulley 
* D_i -- the driven (destination) pulley 
* C_i -- the connection type (0=straight, 1=crossed) 
Unfortunately, FJ lists the belts in random order. 
By way of example, consider the illustration below. N = 4, and pulley 1 is driven clockwise by the thresher engine. Straight 
belts drive pulley 2 and then pulley 3, so they rotate clockwise. The crosswise belt reverses the rotation direction so pulley 4 (pulley N) rotates counterclockwise. 
```
POINTS: 70
约翰有一个过时的收割机，需要在它的各种滑轮上装配皮带才能让收割机的各个部分运作起 来.引擎能够驱动滑轮1向顺时针方向转动，滑轮1通过一条皮带又连接到滑轮2.滑轮2又通过一 条皮带连接到滑轮3，等等，总共有N(2 <= N <= 1000)个滑轮和N - 1条皮带.

皮带连接两个滑轮有两种方式：直接连接和交叉连接.直接连接的两个滑轮旋转方向相同， 即同为顺时针或同为逆时针.交叉连接的两个滑轮旋转方向相反.

现在给出一个列表，里面列出所有皮带的连接方式.已经知道滑轮1被引擎驱动着向顺时针方 向转动.每一条皮带由下面三个数定义：

•驱动滑轮S，输入驱动力的滑轮.

•被驱动滑轮D;，被驱使转动的滑轮.

•连接类型C，0表示直接连接，1表示交叉连接.

不幸的是，约翰的这个列表中，皮带的顺序是混乱的.所以请你写一个程序来求出滑轮N的 转动方向.


## 说明/提示

As in the example illustration.


## 样例 #1

### 输入

```
4 
2 3 0 
3 4 1 
1 2 0 
```

### 输出

```
1 
```

# AI分析结果

### 算法分类
**模拟**

### 综合分析与结论
题目要求根据皮带的连接方式（直接或交叉）确定最后一个滑轮的旋转方向。核心思路是通过模拟滑轮的旋转方向变化，最终得到结果。难点在于如何处理皮带的随机顺序，以及如何高效地计算旋转方向的变化。

### 所选题解

#### 1. 作者：NTG_Adiord (赞：10)
**星级：5星**
**关键亮点：**
- 使用位运算（异或）简化了方向变化的计算，代码简洁高效。
- 通过直接计算所有皮带的连接类型的异或和，避免了复杂的排序和遍历操作。

**核心代码：**
```cpp
#include <cstdio>
int main(){
    int n,a;bool b;
    scanf("%d",&n);n--;
    while(n--)scanf("%d%d%d",&a,&a,&a),b^=a;
    printf("%d",b);
}
```
**个人心得：**
- 通过异或运算直接得到结果，避免了复杂的逻辑判断和数据结构操作，代码简洁且高效。

#### 2. 作者：荷叶下 (赞：4)
**星级：4星**
**关键亮点：**
- 使用简单的布尔变量 `flag` 来记录旋转方向的变化，逻辑清晰易懂。
- 通过遍历所有皮带，根据连接类型更新 `flag`，最终输出结果。

**核心代码：**
```cpp
#include <bits/stdc++.h>
using namespace std ;
int n , a , b , c ;
bool flag ; //flag为滑轮转动方向 
int main()
{
    cin >> n ;
    for( int i = 1 ; i < n ; ++i ){
        cin >> a >> b >> c ;
        if( c == 1 ) flag = !flag ; //如果是交叉连接就转变方向 
    }
    cout << flag ? 0 : 1 ; //压行也是陋习
    return 0 ; 
}
```
**个人心得：**
- 通过简单的布尔变量和条件判断，实现了旋转方向的变化，代码简洁且易于理解。

#### 3. 作者：codemap (赞：0)
**星级：4星**
**关键亮点：**
- 通过统计交叉连接的数量，判断最终旋转方向，思路清晰。
- 代码简洁，直接遍历所有皮带并统计交叉连接的数量，最终输出结果。

**核心代码：**
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,i,s=0,a,b;
    bool f;
    cin>>n;
    for(i=1;i<n;i++)
    {
        cin>>a>>b>>f;
        if(f)//如果是1
            s++;//++
    }
    if(s%2==0)//如果是偶数个
        cout<<0;
    else//否则
        cout<<1;
    return 0;//完美结束
}
```
**个人心得：**
- 通过统计交叉连接的数量，简化了旋转方向的计算，代码简洁且易于理解。

### 最优关键思路或技巧
- **位运算（异或）**：通过异或运算直接计算所有皮带的连接类型，简化了方向变化的计算，代码简洁高效。
- **布尔变量**：使用布尔变量记录旋转方向的变化，逻辑清晰易懂。
- **统计交叉连接数量**：通过统计交叉连接的数量，判断最终旋转方向，思路清晰且代码简洁。

### 可拓展之处
- 类似题目可以考察其他位运算的应用，如与、或、非等。
- 可以扩展到更复杂的旋转方向变化问题，如多级滑轮系统或环形滑轮系统。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：28.49秒