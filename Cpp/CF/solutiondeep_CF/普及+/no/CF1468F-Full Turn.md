# 题目信息

# Full Turn

## 题目描述

There are $ n $ persons located on a plane. The $ i $ -th person is located at the point $ (x_i, y_i) $ and initially looks at the point $ (u_i, v_i) $ .

At the same moment of time, all persons will start to rotate clockwise synchronously with the same angular speed. They will rotate until they do one full $ 360 $ -degree turn.

It is said that persons $ A $ and $ B $ made eye contact if person $ A $ looks in person $ B $ 's direction at the same moment when person $ B $ looks in person $ A $ 's direction. If there is a person $ C $ located between persons $ A $ and $ B $ , that will not obstruct $ A $ and $ B $ from making eye contact. A person can make eye contact with more than one person at the same time.

Calculate the number of pairs of persons that will make eye contact at least once during the rotation (including the initial moment).

## 样例 #1

### 输入

```
3
2
0 0 0 1
1 0 2 0
3
0 0 1 1
1 1 0 0
1 0 2 0
6
0 0 0 1
1 0 1 2
2 0 2 3
3 0 3 -5
4 0 4 -5
5 0 5 -5```

### 输出

```
0
1
9```

# AI分析结果

### 题目内容中文重写
# 完整旋转

## 题目描述
平面上有 $n$ 个人。第 $i$ 个人位于点 $(x_i, y_i)$，初始时看向点 $(u_i, v_i)$。

在同一时刻，所有人将以相同的角速度同步顺时针旋转。他们将旋转直到完成一整圈 $360$ 度的转动。

如果在某一时刻，当 $A$ 看向 $B$ 所在方向的同时，$B$ 也看向 $A$ 所在方向，那么就称 $A$ 和 $B$ 进行了眼神交流。如果有一个人 $C$ 位于 $A$ 和 $B$ 之间，这不会妨碍 $A$ 和 $B$ 进行眼神交流。一个人可以同时与多个人进行眼神交流。

计算在旋转过程中（包括初始时刻）至少进行一次眼神交流的人的对数。

## 样例 #1
### 输入
```
3
2
0 0 0 1
1 0 2 0
3
0 0 1 1
1 1 0 0
1 0 2 0
6
0 0 0 1
1 0 1 2
2 0 2 3
3 0 3 -5
4 0 4 -5
5 0 5 -5
```

### 输出
```
0
1
9
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过分析得出两人能进行眼神交流的条件是他们的视线方向相反，在此基础上，不同题解采用了不同的方法来表示和统计方向相反的线的对数。
- **思路对比**：大部分题解都先将人平移到原点，计算视线方向向量，再判断方向是否相反；部分题解还考虑了斜率的计算和特殊情况（平行于坐标轴）的处理。
- **算法要点**：主要使用了 `map` 来统计方向相同的线的数量，通过查找相反方向的线的数量来计算答案；部分题解使用了双指针、排序等方法处理斜率。
- **解决难点**：主要难点在于处理斜率的精度问题，不同题解采用了双哈希、化简方向向量等方法来解决。

### 题解评分与选择
- **npqenqpve（4星）**：思路清晰，考虑了斜率精度问题，使用双哈希处理，但代码稍复杂。
- **Jinzixun（4星）**：代码简洁，直接通过化简方向向量并使用 `map` 统计，思路清晰易懂。
- **jhdrgfj（4星）**：思路与 Jinzixun 类似，同样使用 `map` 统计，处理了特殊情况。

### 重点代码及核心实现思想
#### npqenqpve
```cpp
// 核心思想：通过双哈希处理斜率，用 map 统计方向相同的线的数量，最后计算方向相反的线的对数
for(int i=1;i<=n;i++)
{
    cin>>a[i].x>>a[i].y>>a[i].u>>a[i].v;
    a[i].u-=a[i].x;
    a[i].v-=a[i].y;
    a[i].x=a[i].y=0;
}
for(int i=1;i<=n;i++)
{
    if(a[i].v==0)
    {
        // 处理 v 为 0 的情况
    }
    if(a[i].u==0)
    {
        // 处理 u 为 0 的情况
    }
    a[i].k1=(int)(998244353*(double)((double)a[i].v/(double)a[i].u))%(1000000000007);
    a[i].k2=(int)((int)(2147483647)*(double)((double)a[i].v/(double)a[i].u))%(998244353);
    // 判断方向
    m[make_pair(a[i].k1+a[i].k2,a[i].op)]++;
}
int ans=0;
for(int i=1;i<=n;i++)
{
    ans+=m[make_pair(a[i].k1+a[i].k2,-a[i].op)];
}
cout<<ans/2<<"\n";
```

#### Jinzixun
```cpp
// 核心思想：将人平移到原点，化简方向向量，用 map 统计方向相同的线的数量，同时累加方向相反的线的数量
map<pair<int, int>, int> mp;
while(n--){
    int x, y, u, v;
    scanf("%lld%lld%lld%lld", &x, &y, &u, &v);
    u -= x;
    v -= y;
    int g = abs(__gcd(u, v));
    u /= g;
    v /= g;
    ans += mp[make_pair(-u, -v)];
    mp[make_pair(u, v)]++;
}
printf("%lld\n", ans);
```

#### jhdrgfj
```cpp
// 核心思想：将人平移到原点，处理特殊情况，化简方向向量，用 map 统计方向相同的线的数量，最后计算方向相反的线的对数
map<pair<int,int>,long long> m;
for (int i=1;i<=n;i++){
    long long x1,x2,y1,y2; 
    cin>>x1>>y1>>x2>>y2;
    x.push_back(x2-x1);
    y.push_back(y2-y1);
    if (x[i]==0){
        y[i]=y[i]/abs(y[i]);
    }
    if (y[i]==0){
        x[i]=x[i]/abs(x[i]);
    }
    int gcd=abs(__gcd(x[i],y[i]));
    x[i]/=gcd;
    y[i]/=gcd;
    m[make_pair(x[i],y[i])]++;
}
for (int i=1;i<=n;i++){
    ans+=m[make_pair(-x[i],-y[i])];
} 
cout<<ans/2ll<<endl;
```

### 最优关键思路或技巧
- 使用 `map` 统计方向相同的线的数量，方便查找方向相反的线的数量。
- 化简方向向量，避免斜率的精度问题。

### 可拓展之处
同类型题可能会涉及三维空间中向量的方向判断，或者在不同的几何图形中判断视线是否相交等。类似算法套路可以应用于计算几何中判断向量平行、垂直等问题。

### 推荐洛谷题目
- P1355 神秘大三角
- P2782 友好城市
- P1090 合并果子

### 个人心得
- conti123 提到“听说精度可能会炸？不行就用哈希搞一下，反正VP时是可以过的”，总结：在处理涉及斜率等计算时，要注意精度问题，可以考虑使用哈希等方法解决。 

---
处理用时：52.45秒