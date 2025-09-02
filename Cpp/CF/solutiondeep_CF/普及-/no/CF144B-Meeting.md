# 题目信息

# Meeting

## 题目描述

The Super Duper Secret Meeting of the Super Duper Secret Military Squad takes place in a Super Duper Secret Place. The place is an infinite plane with introduced Cartesian coordinate system. The meeting table is represented as a rectangle whose sides are parallel to the coordinate axes and whose vertexes are located at the integer points of the plane. At each integer point which belongs to the table perimeter there is a chair in which a general sits.

Some points on the plane contain radiators for the generals not to freeze in winter. Each radiator is characterized by the number $ r_{i} $ — the radius of the area this radiator can heat. That is, if the distance between some general and the given radiator is less than or equal to $ r_{i} $ , than the general feels comfortable and warm. Here distance is defined as Euclidean distance, so the distance between points $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF144B/db1ba0d5909a3b47109b2e5f65fe13400ae1bd9a.png)

Each general who is located outside the radiators' heating area can get sick. Thus, you should bring him a warm blanket. Your task is to count the number of warm blankets you should bring to the Super Duper Secret Place.

The generals who are already comfortable do not need a blanket. Also the generals never overheat, ever if they are located in the heating area of several radiators. The radiators can be located at any integer points on the plane, even inside the rectangle (under the table) or on the perimeter (directly under some general). Even in this case their radius does not change.

## 说明/提示

In the first sample the generals are sitting at points: $ (2,2) $ , $ (2,3) $ , $ (2,4) $ , $ (2,5) $ , $ (3,2) $ , $ (3,5) $ , $ (4,2) $ , $ (4,3) $ , $ (4,4) $ , $ (4,5) $ . Among them, 4 generals are located outside the heating range. They are the generals at points: $ (2,5) $ , $ (3,5) $ , $ (4,4) $ , $ (4,5) $ .

In the second sample the generals are sitting at points: $ (5,2) $ , $ (5,3) $ , $ (6,2) $ , $ (6,3) $ . All of them are located inside the heating range.

## 样例 #1

### 输入

```
2 5 4 2
3
3 1 2
5 3 1
1 3 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 2 6 3
2
6 2 2
6 5 3
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 会议

## 题目描述
超级秘密军事小队的超级秘密会议在一个超级秘密的地方举行。这个地方是一个引入了笛卡尔坐标系的无限平面。会议桌被表示为一个矩形，其边与坐标轴平行，顶点位于平面的整点上。在属于桌周边界的每个整点处都有一把椅子，一位将军坐在其中。

平面上的一些点设有散热器，以确保将军们在冬天不会受冻。每个散热器的特征是数字$r_{i}$，即该散热器能够加热的区域半径。也就是说，如果某个将军与给定散热器之间的距离小于或等于$r_{i}$，那么这位将军就会感到舒适温暖。这里的距离定义为欧几里得距离，所以点$(x_{1},y_{1})$和$(x_{2},y_{2})$之间的距离为$\sqrt{(x_{1}-x_{2})^2+(y_{1}-y_{2})^2}$。

每个位于散热器加热区域之外的将军都可能生病。因此，你需要为他带一条温暖的毯子。你的任务是计算需要带到超级秘密地点的温暖毯子的数量。

已经感觉舒适的将军不需要毯子。此外，即使将军位于多个散热器的加热区域内，他们也不会过热。散热器可以位于平面上的任何整点，甚至在矩形内部（桌子下方）或边界上（直接在某个将军下方）。即便如此，它们的半径也不会改变。

## 说明/提示
在第一个样例中，将军们坐在以下点上：$(2,2)$，$(2,3)$，$(2,4)$，$(2,5)$，$(3,2)$，$(3,5)$，$(4,2)$，$(4,3)$，$(4,4)$，$(4,5)$。其中，有4位将军位于加热范围之外。他们是位于点$(2,5)$，$(3,5)$，$(4,4)$，$(4,5)$的将军。

在第二个样例中，将军们坐在点$(5,2)$，$(5,3)$，$(6,2)$，$(6,3)$上。他们都位于加热范围内。

## 样例 #1
### 输入
```
2 5 4 2
3
3 1 2
5 3 1
1 3 2
```
### 输出
```
4
```

## 样例 #2
### 输入
```
5 2 6 3
2
6 2 2
6 5 3
```
### 输出
```
0
```

### 算法分类
枚举

### 综合分析与结论
所有题解均基于数据范围小的特点，采用暴力枚举的方法解题。思路均为枚举矩形周长上的每个点，再对每个点枚举所有散热器，通过计算欧几里得距离判断点是否在散热器加热范围内，进而统计未被覆盖的点的数量。各题解的不同主要体现在代码实现细节与优化上，如有的题解注意到矩形的轴对称性进行优化，有的题解在处理边界点避免重复计算方面有不同的实现方式。

### 所选的题解
- **作者：_xbn (5星)**
    - **关键亮点**：利用矩形轴对称性进行优化，代码注释详细，思路清晰，代码简洁明了。
    - **个人心得**：无
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int x[1010],y[1010],r[1010],n;
    int zone(int xx, int yy)//求两个点的欧几里得距离
    {
        for(int i=0;i<n;i++)
        {
           if((x[i]-xx)*(x[i]-xx)+(y[i]-yy)*(y[i]-yy)<=r[i]*r[i])return 0;//勾股定理
            
        } 
        return 1;
    }
    int main()
    {
        int xa,ya,xb,yb,ans=0;
        cin>>xa>>ya>>xb>>yb>>n;
        for(int i=0;i<n;i++) 
        {
            cin>>x[i]>>y[i]>>r[i];
        }
        for(int i=min(xa,xb);i<=max(xa,xb);i++)//横坐标从小到大枚举
            ans+=zone(i,ya)+zone(i,yb);
        for(int i=min(ya,yb)+1;i<max(ya,yb);i++)//纵坐标从小到大枚举
            ans+=zone(xa,i)+zone(xb,i);
        cout<<ans;
        return 0;
    } 
    ```
    - **核心代码简述**：`zone`函数用于判断点`(xx, yy)`是否在某个散热器范围内，主函数中通过两次循环枚举矩形周长上的点，调用`zone`函数统计未被覆盖的点的数量。
- **作者：yimuhua (4星)**
    - **关键亮点**：思路清晰，代码简洁，利用矩形轴对称性进行优化，代码结构合理。
    - **个人心得**：无
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int n, ans, x[1005], y[1005], r[1005];
    int f(int cx, int cy) {
        for(int i = 0; i < n; i++)
            if((x[i] - cx) * (x[i] - cx) + (y[i] - cy) * (y[i] - cy) <= r[i] * r[i])
                return 0;
        return 1;
    }
    int main() {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2 >> n;
        for(int i = 0; i < n; i++)
            cin >> x[i] >> y[i] >> r[i];
        for(int i = min(x1, x2); i <= max(x1, x2); i++)
            ans += f(i, y1) + f(i, y2);
        for(int i = min(y1, y2) + 1; i < max(y1, y2); i++)
            ans += f(x1, i) + f(x2, i);
        cout << ans;
        return 0;
    }
    ```
    - **核心代码简述**：`f`函数用于判断点`(cx, cy)`是否在某个散热器范围内，主函数通过两次循环枚举矩形周长上的点，调用`f`函数统计未被覆盖的点的数量。
- **作者：Ninelife_Cat (4星)**
    - **关键亮点**：思路清晰，代码结构合理，详细处理了矩形四个角上的点避免重复计算问题。
    - **个人心得**：无
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int x,y,x2,y2,n,tx[1001],ty[1001],r[1001],ans;
    int dis(int x,int y,int x2,int y2) {return (x2-x)*(x2-x)+(y2-y)*(y2-y);}
    //计算欧几里得距离,为了防止掉精度将两边同时平方
    signed main()
    {
        cin>>x>>y>>x2>>y2;//矩形坐标
        if(x2<x) swap(x2,x);
        if(y2<y) swap(y2,y);
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>tx[i]>>ty[i]>>r[i];//信号站坐标
        bool flag=0;//flag记录当前的点是否被覆盖
        for(int i=1;i<=n;i++)
            if(dis(x,y,tx[i],ty[i])<=r[i]*r[i]) {flag=1;break;}
        if(!flag) ans++;
        flag=0;
        for(int i=1;i<=n;i++)
            if(dis(x2,y,tx[i],ty[i])<=r[i]*r[i]) {flag=1;break;}
        if(!flag) ans++;
        flag=0;
        for(int i=1;i<=n;i++)
            if(dis(x,y2,tx[i],ty[i])<=r[i]*r[i]) {flag=1;break;}
        if(!flag) ans++;
        flag=0;
        for(int i=1;i<=n;i++)
            if(dis(x2,y2,tx[i],ty[i])<=r[i]*r[i]) {flag=1;break;}
        if(!flag) ans++;
        //特判矩形四个角上的点,防止重复计算
        for(int i=x+1;i<x2;i++)
        {
            flag=0;
            for(int j=1;j<=n;j++)
                if(dis(i,y,tx[j],ty[j])<=r[j]*r[j]) {flag=1;break;}
            if(!flag) ans++;
        }
        for(int i=x+1;i<x2;i++)
        {
            flag=0;
            for(int j=1;j<=n;j++)
                if(dis(i,y2,tx[j],ty[j])<=r[j]*r[j]) {flag=1;break;}
            if(!flag) ans++;
        }
        for(int i=y+1;i<y2;i++)
        {
            flag=0;
            for(int j=1;j<=n;j++)
                if(dis(x,i,tx[j],ty[j])<=r[j]*r[j]) {flag=1;break;}
            if(!flag) ans++;
        }
        for(int i=y+1;i<y2;i++)
        {
            flag=0;
            for(int j=1;j<=n;j++)
                if(dis(x2,i,tx[j],ty[j])<=r[j]*r[j]) {flag=1;break;}
            if(!flag) ans++;
        }
        cout<<ans;
        return 0;
    }
    ```
    - **核心代码简述**：`dis`函数计算两点间欧几里得距离的平方，主函数先特判矩形四个角上的点，再分别枚举矩形四条边上除角点外的点，通过`flag`标记判断点是否被覆盖，统计未被覆盖的点的数量。

### 最优关键思路或技巧
利用矩形的轴对称性减少枚举量，在计算欧几里得距离时，通过两边同时平方避免开方带来的精度问题，并且在枚举矩形周长上的点时，仔细处理边界点（如四个角上的点），防止重复计算。

### 可拓展之处
同类型题通常是在平面上给定一些几何图形（如矩形、圆形等）以及一些具有一定作用范围的元素（如本题的散热器），求几何图形上满足或不满足某些条件（如在作用范围内或外）的点的数量。类似算法套路都是通过合理的枚举方式，并结合相应的距离公式或几何关系判断条件是否满足。

### 推荐洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举不同的数的组合，判断其是否满足质数的条件，与本题枚举思路类似。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过枚举不同菜品的组合来满足价格条件，同样运用枚举思想。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：通过枚举字符串中的每个位置来统计单词出现次数，也是枚举思想的应用。

### 个人心得摘录与总结
arrow_king提到的细节问题很关键，包括注意初始点的位置关系，避免枚举时出现死循环；注意四个角上的点不要重复计算；分清坐标系横纵坐标关系；处理好点在辐射范围边缘的情况。这些细节在解决此类枚举几何图形上点的问题时经常遇到，需要特别关注。 

---
处理用时：97.39秒