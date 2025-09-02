# 题目信息

# Clock and Strings

## 题目描述

There is a clock labeled with the numbers $ 1 $ through $ 12 $ in clockwise order, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/dc1b9b8cdcc08927ff93e17ee0e104c325e2c451.png)In this example, $ (a,b,c,d)=(2,9,10,6) $ , and the strings intersect.

Alice and Bob have four distinct integers $ a $ , $ b $ , $ c $ , $ d $ not more than $ 12 $ . Alice ties a red string connecting $ a $ and $ b $ , and Bob ties a blue string connecting $ c $ and $ d $ . Do the strings intersect? (The strings are straight line segments.)

## 说明/提示

The first test case is pictured in the statement.

In the second test case, the strings do not intersect, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/23548bb954ac5431bdc4259b9b8d572eb5d94e6e.png)

## 样例 #1

### 输入

```
15
2 9 10 6
3 8 9 1
1 2 3 4
5 3 4 12
1 8 2 10
3 12 11 8
9 10 12 1
12 1 10 2
3 12 6 9
1 9 8 4
6 7 9 12
7 12 9 6
10 12 11 1
3 9 6 12
1 4 3 5```

### 输出

```
YES
NO
NO
YES
YES
NO
NO
NO
NO
NO
NO
YES
YES
YES
YES```

# AI分析结果

### 题目中文重写
## 时钟与线段

### 题目描述
有一个时钟，按顺时针顺序标有从 1 到 12 的数字，如下图所示。

![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/dc1b9b8cdcc08927ff93e17ee0e104c325e2c451.png)

在这个例子中，$(a,b,c,d)=(2,9,10,6)$，并且两条线段相交。

爱丽丝和鲍勃有四个不超过 12 的不同整数 $a$、$b$、$c$、$d$。爱丽丝用一条红色线段连接 $a$ 和 $b$，鲍勃用一条蓝色线段连接 $c$ 和 $d$。这两条线段会相交吗？（线段为直线段）

### 说明/提示
第一个测试用例如题目描述中的图所示。
在第二个测试用例中，两条线段不相交，如下图所示。

![示例图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/23548bb954ac5431bdc4259b9b8d572eb5d94e6e.png)

### 样例 #1
#### 输入
```
15
2 9 10 6
3 8 9 1
1 2 3 4
5 3 4 12
1 8 2 10
3 12 11 8
9 10 12 1
12 1 10 2
3 12 6 9
1 9 8 4
6 7 9 12
7 12 9 6
10 12 11 1
3 9 6 12
1 4 3 5
```

#### 输出
```
YES
NO
NO
YES
YES
NO
NO
NO
NO
NO
NO
YES
YES
YES
YES
```

### 综合分析与结论
这些题解的核心都是判断时钟上两条线段是否相交，思路大体可分为以下几类：
1. **分类讨论端点位置**：通过固定一条线段，判断另一条线段的两个端点是否分别位于其两侧。如 cute_overmind、fwtv_24 等题解。
2. **枚举半圆弧上的点**：只枚举某一半圆弧上的数字，统计另一条线段端点出现的次数，若为 1 则相交。如 JXR_Kalcium 的题解。
3. **判断数字排列顺序**：将四个点按一定顺序排列，判断是否满足特定的交替排列情况。如 liuhongyang123、zzx114514 等题解。
4. **构造字符串判断**：按顺序遍历 1 到 12，将遇到的端点标记添加到字符串中，判断字符串是否为特定形式。如 Dream_Mr_li、L_xcy 等题解。

### 所选题解
- **cute_overmind（5 星）**
    - **关键亮点**：思路清晰，通过简单的分类讨论和计数，代码简洁高效。
    - **核心代码**：
```cpp
void solve()
{
    int a, b, c, d, cnt = 0;
    cin >> a >> b >> c >> d;
    if(a < b) swap(a, b);
    if(c >= b && c <= a) cnt++;
    if(d >= b && d <= a) cnt++;
    if(cnt % 2) cout << "YES" << "\n";
    else cout << "NO" << '\n';
}
```
核心思想：固定一条线段，统计另一条线段的端点落在该线段所划分的半圆弧上的数量，若数量为奇数则相交。

- **liuhongyang123（4 星）**
    - **关键亮点**：直接总结出相交的两种情况，代码逻辑简单明了。
    - **核心代码**：
```cpp
signed main(){
    int T,a,b,c,d;
    cin>>T;
    while(T--){
        cin>>a>>b>>c>>d;
        if(a>b) swap(a,b);
        if(c>d) swap(c,d);
        if(a<c&&c<b&&b<d) cout<<"YES";
        else if(c<a&&a<d&&d<b) cout<<"YES";
        else cout<<"NO";
        cout<<endl;
    }
    return 0;
}
```
核心思想：将四个点排序后，判断是否满足 $a<c<b<d$ 或 $c<a<d<b$ 这两种相交情况。

- **Dream_Mr_li（4 星）**
    - **关键亮点**：通过构造字符串的方式直观地判断线段是否相交，思路独特。
    - **核心代码**：
```c++
void solve(){
    int a,b,c,d;
    string s;
    cin>>a>>b>>c>>d;
    for(int i=1;i<=12;i++){
        if(i==a||i==b){
            s+="1";
        }if(i==c||i==d){
            s+="2";
        }
    }
    if(s=="1212"||s=="2121"){
        cout<<"YES\n";
    }else{
        cout<<"NO\n";
    }
}
```
核心思想：按顺序遍历 1 到 12，将遇到的端点标记添加到字符串中，若字符串为 "1212" 或 "2121" 则相交。

### 最优关键思路或技巧
- **固定一条线段分析**：将问题简化，通过固定一条线段，分析另一条线段端点的位置关系，降低问题复杂度。
- **字符串构造判断**：将端点的顺序信息转化为字符串，通过判断字符串的形式来确定线段是否相交，直观且易于实现。

### 可拓展之处
同类型题可能会扩展到更复杂的图形，如多边形、圆形等，判断其中线段或直线的相交情况。类似算法套路可用于解决几何图形中的位置关系判断问题，如判断点是否在多边形内、线段是否与多边形相交等。

### 推荐洛谷题目
1. [P1196 银河英雄传说](https://www.luogu.com.cn/problem/P1196)：涉及到并查集和线段相交判断的思想，用于处理节点之间的连通性和位置关系。
2. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880)：需要分析不同区间的合并情况，与本题中判断线段相交时分析端点位置关系有相似的思维方式。
3. [P2024 食物链](https://www.luogu.com.cn/problem/P2024)：同样需要通过分类讨论和逻辑判断来解决问题，与本题的分类讨论思路类似。

### 个人心得摘录与总结
部分题解提到在思考时会考虑特殊情况，如从一点引出的两条线段是否算相交，但通过测试数据发现不存在此类情况，从而简化了问题。这提醒我们在解题时要充分考虑各种可能的边界情况，但也要结合实际测试数据进行合理的取舍。 

---
处理用时：38.00秒