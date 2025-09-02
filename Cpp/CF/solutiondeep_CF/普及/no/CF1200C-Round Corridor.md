# 题目信息

# Round Corridor

## 题目描述

Amugae is in a very large round corridor. The corridor consists of two areas. The inner area is equally divided by $ n $ sectors, and the outer area is equally divided by $ m $ sectors. A wall exists between each pair of sectors of same area (inner or outer), but there is no wall between the inner area and the outer area. A wall always exists at the 12 o'clock position.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1200C/7fdeabfa2ad973f1b56c678ed3354417ac806e5e.png)The inner area's sectors are denoted as $ (1,1), (1,2), \dots, (1,n) $ in clockwise direction. The outer area's sectors are denoted as $ (2,1), (2,2), \dots, (2,m) $ in the same manner. For a clear understanding, see the example image above.

Amugae wants to know if he can move from one sector to another sector. He has $ q $ questions.

For each question, check if he can move between two given sectors.

## 说明/提示

Example is shown on the picture in the statement.

## 样例 #1

### 输入

```
4 6 3
1 1 2 3
2 6 1 2
2 6 2 4
```

### 输出

```
YES
NO
YES
```

# AI分析结果

### 题目内容重写

Amugae 在一个非常大的圆形走廊中。走廊由两个区域组成。内圈被等分为 $n$ 个扇区，外圈被等分为 $m$ 个扇区。每个扇区之间有一堵墙（内圈或外圈），但内圈和外圈之间没有墙。12点钟方向总是有一堵墙。

内圈的扇区按顺时针方向标记为 $ (1,1), (1,2), \dots, (1,n) $，外圈的扇区按相同方式标记为 $ (2,1), (2,2), \dots, (2,m) $。为了更清楚地理解，请参考上面的示例图片。

Amugae 想知道他是否可以从一个扇区移动到另一个扇区。他有 $q$ 个问题。

对于每个问题，检查他是否可以在两个给定的扇区之间移动。

### 样例 #1

#### 输入

```
4 6 3
1 1 2 3
2 6 1 2
2 6 2 4
```

#### 输出

```
YES
NO
YES
```

### 算法分类
数学

### 题解分析与结论

#### 题解对比与总结
1. **QwQcOrZ** 的题解通过计算内外圈的联通块数，利用 `gcd` 来判断两个扇区是否在同一个联通块内。代码简洁，思路清晰，且提供了数学证明。
2. **Kizuna_AI** 的题解同样使用 `gcd` 来判断联通块，但代码中使用了 `__gcd` 函数，虽然代码简洁，但缺乏数学证明。
3. **lygmh** 的题解思路与 QwQcOrZ 类似，但代码实现稍显冗长，且没有提供数学证明。

#### 最优关键思路
- 利用 `gcd(n, m)` 将内外圈分为 `gcd(n, m)` 个联通块，每个联通块内的扇区可以互相到达，不同联通块之间则无法到达。
- 通过计算扇区所在的联通块编号，判断两个扇区是否在同一个联通块内。

#### 可拓展之处
- 类似的问题可以扩展到其他几何形状的联通性问题，如矩形、多边形等。
- 可以使用并查集等数据结构来解决更复杂的联通性问题。

#### 推荐题目
1. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
2. [P1072 Hankson的趣味题](https://www.luogu.com.cn/problem/P1072)
3. [P1447 最大公约数](https://www.luogu.com.cn/problem/P1447)

### 精选题解

#### 题解1：QwQcOrZ (5星)
**关键亮点**：提供了详细的数学证明，代码简洁且高效。
**代码核心思想**：
```cpp
ll gcd(ll x,ll y) {
    return y==0?x:gcd(y,x%y);
}
ll get(ll a,ll b,ll x,ll y) {
    if (x==1) return (y-1)/a;
    else return (y-1)/b;
}
```
**完整核心代码**：
```cpp
int main() {
    ll n=read(),m=read(),q=read(),g=gcd(n,m),a=n/g,b=m/g;
    while (q--) {
        ll x1=read(),y1=read(),x2=read(),y2=read(),ans1=get(a,b,x1,y1),ans2=get(a,b,x2,y2);
        if (ans1==ans2) puts("Yes");
        else puts("No");
    }
    return 0;
}
```

#### 题解2：Kizuna_AI (4星)
**关键亮点**：代码简洁，使用了 `__gcd` 函数，适合快速实现。
**代码核心思想**：
```cpp
gcdnm=__gcd(n,m);
n/=gcdnm;m/=gcdnm;
```
**完整核心代码**：
```cpp
int main() {
    scanf("%I64d%I64d%I64d",&n,&m,&q);
    long long sx,sy,ex,ey;
    gcdnm=__gcd(n,m);
    n/=gcdnm;m/=gcdnm;
    for(int i=1;i<=q;i++) {
        scanf("%I64d%I64d%I64d%I64d",&sx,&sy,&ex,&ey);
        if(sx==1 && ex==1) {
            if((sy-1)/n==(ey-1)/n) printf("YES\n");
            else printf("NO\n");
        }
        else if(sx==1 && ex==2) {
            if((sy-1)/n==(ey-1)/m) printf("YES\n");
            else printf("NO\n");
        }
        else if(sx==2 && ex==1) {
            if((sy-1)/m==(ey-1)/n) printf("YES\n");
            else printf("NO\n");
        }
        else if(sx==2 && ex==2) {
            if((sy-1)/m==(ey-1)/m) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}
```

#### 题解3：lygmh (4星)
**关键亮点**：思路清晰，代码实现稍显冗长，但逻辑正确。
**代码核心思想**：
```cpp
LL gcd(LL a,LL b) {
    LL r;
    while(b) {r=a%b;a=b;b=r;}
    return a;
}
```
**完整核心代码**：
```cpp
int main() {
    scanf("%lld%lld%lld",&m,&n,&q);
    LL br=gcd(m,n);
    while(q--) {
        LL f1,f2,t1,t2,q1,q2;
        scanf("%lld%lld%lld%lld",&f1,&f2,&t1,&t2);
        q1=(f1==1)? ((f2-1)/(m/br)):((f2-1)/(n/br));
        q2=(t1==1)? ((t2-1)/(m/br)):((t2-1)/(n/br));
        if(q1==q2)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

---
处理用时：43.71秒