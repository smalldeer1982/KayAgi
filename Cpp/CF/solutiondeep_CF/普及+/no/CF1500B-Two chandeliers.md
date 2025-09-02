# 题目信息

# Two chandeliers

## 题目描述

Vasya is a CEO of a big construction company. And as any other big boss he has a spacious, richly furnished office with two crystal chandeliers. To stay motivated Vasya needs the color of light at his office to change every day. That's why he ordered both chandeliers that can change its color cyclically. For example: red – brown – yellow – red – brown – yellow and so on.

There are many chandeliers that differs in color set or order of colors. And the person responsible for the light made a critical mistake — they bought two different chandeliers.

Since chandeliers are different, some days they will have the same color, but some days — different. Of course, it looks poor and only annoys Vasya. As a result, at the $ k $ -th time when chandeliers will light with different colors, Vasya will become very angry and, most probably, will fire the person who bought chandeliers.

Your task is to calculate the day, when it happens (counting from the day chandeliers were installed). You can think that Vasya works every day without weekends and days off.

## 说明/提示

In the first example, the chandeliers will have different colors at days $ 1 $ , $ 2 $ , $ 3 $ and $ 5 $ . That's why the answer is $ 5 $ .

## 样例 #1

### 输入

```
4 2 4
4 2 3 1
2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
3 8 41
1 3 2
1 6 4 3 5 7 2 8```

### 输出

```
47```

## 样例 #3

### 输入

```
1 2 31
1
1 2```

### 输出

```
62```

# AI分析结果

### 题目内容翻译
# 两盏吊灯

## 题目描述
瓦西亚是一家大型建筑公司的首席执行官。和其他大老板一样，他有一间宽敞、装修豪华的办公室，里面有两盏水晶吊灯。为了保持动力，瓦西亚需要办公室的灯光颜色每天都变化。这就是为什么他订购了两盏可以循环变色的吊灯。例如：红色 - 棕色 - 黄色 - 红色 - 棕色 - 黄色，以此类推。

市场上有很多吊灯，它们的颜色组合或颜色顺序各不相同。而负责灯光的人犯了一个严重的错误——他们买了两盏不同的吊灯。

由于吊灯不同，有些日子它们的颜色会相同，但有些日子颜色会不同。当然，颜色不同看起来很不协调，只会让瓦西亚感到恼火。结果，在第 $k$ 次两盏吊灯颜色不同时，瓦西亚会非常生气，很可能会解雇买吊灯的人。

你的任务是计算出这一情况发生的日期（从安装吊灯的那天开始计算）。你可以认为瓦西亚每天都工作，没有周末和假期。

## 说明/提示
在第一个样例中，两盏吊灯在第 $1$、$2$、$3$ 和 $5$ 天颜色不同。所以答案是 $5$。

## 样例 #1
### 输入
```
4 2 4
4 2 3 1
2 1
```
### 输出
```
5
```

## 样例 #2
### 输入
```
3 8 41
1 3 2
1 6 4 3 5 7 2 8
```
### 输出
```
47
```

## 样例 #3
### 输入
```
1 2 31
1
1 2
```
### 输出
```
62
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用两盏吊灯颜色变化的周期性，通过求解同余方程组来确定两盏吊灯颜色相同的时刻，进而计算出第 $k$ 次颜色不同的时刻。

- **思路对比**：大部分题解都是先找出两盏吊灯颜色相同的时刻，然后根据这些时刻计算颜色不同的时刻。Lynkcat 的题解是直接计算 $p\times m \bmod n$ 的值来确定贡献；Cry_For_theMoon、白鲟、enucai 的题解都使用了二分答案来确定最终结果；血色黄昏的题解则是通过取模和遍历的方式来确定答案。
- **算法要点**：主要涉及到扩展欧几里得算法（exgcd）求解同余方程组，以及最小公倍数（lcm）的计算。部分题解还使用了排序和二分查找来优化计算过程。
- **解决难点**：关键在于如何正确求解同余方程组，以及如何高效地统计颜色相同和不同的时刻。

### 所选题解
- **Cry_For_theMoon（4星）**
    - **关键亮点**：思路清晰，代码实现完整，使用扩展中国剩余定理（Excrt）求解同余方程组，并通过二分答案来确定最终结果，具有一定的通用性。
    - **个人心得**：曾经比赛时因为不会 exgcd 列出了方程然后束手无策。
- **白鲟（4星）**
    - **关键亮点**：思路简洁明了，明确指出以 $\operatorname{lcm}(n,m)$ 为循环节，通过解同余方程组预处理出相等位置，再二分答案求解，时间复杂度分析准确。
- **enucai（4星）**
    - **关键亮点**：代码实现简洁，对周期内重复位置的处理和二分答案的思路清晰，复杂度分析明确。

### 重点代码
#### Cry_For_theMoon 的核心代码
```cpp
ll Calc(ll i,ll j){
    ll minx=i,add=n; 
    ll c=j-minx,d=gcd(add,m);
    if(c%d)return -1;
    ll x,y;exgcd(add,m,x,y);
    ll add2=m/d,mult=c/d;
    if(mult>=0)mult%=add2;
    else mult=mult+((-mult+add2-1)/add2)*add2;
    x=mul(x,mult,add2);
    if(x>=0)x%=add2;
    else x=x+((-x+add2-1)/add2)*add2;
    minx=minx+add*x;
    add=lcm(n,m);
    if(minx>=0)minx%=add;
    else minx=minx+((-minx+add-1)/add)*add;
    if(!minx)minx=add;
    return minx;
}
bool check(ll mid){
    ll cnt=mid;
    rep(i,1,n){
        if(!t[1][a[i]])continue;
        if(minn[i]>mid || minn[i]==-1)continue;
        cnt-=(1+(mid-minn[i])/add);
    }
    return cnt>=k;
}
```
**核心实现思想**：`Calc` 函数用于求解同余方程组，得到两盏吊灯颜色相同的最小时刻；`check` 函数用于判断当前的 `mid` 是否满足第 $k$ 次颜色不同的条件。

#### 白鲟的核心代码
```cpp
void exgcd(int a, int b, ll &x, ll &y, int &d) {
    if (!b) {
        x = 1;
        y = 0;
        d = a;
        return;
    }
    exgcd(b, a%b, x, y, d);
    ll t = x;
    x = y;
    y = t - a / b * y;
    return;
}
bool check(ll mid) {
    return (mid - 1) / lcm * (lcm - solution_cnt) + 
           (mid - 1) % lcm + 1 - 
           (std::upper_bound(solution + 1, solution + solution_cnt + 1, (mid - 1) % lcm + 1) - solution - 1)
           >= k;
}
```
**核心实现思想**：`exgcd` 函数用于求解扩展欧几里得算法；`check` 函数用于判断当前的 `mid` 是否满足第 $k$ 次颜色不同的条件。

#### enucai 的核心代码
```cpp
int exgcd(int a,int b,int &x,int &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    int gcd=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return gcd;
}
int excrt(){
    int lcm=1,ans=0;
    For(i,1,2){
        int x,y,gcd=exgcd(lcm,qb[i],x,y),tmp=(qa[i]-ans%qb[i]+qb[i])%qb[i];
        if(tmp%gcd!=0) return -1;
        x=x*tmp/gcd;x%=qb[i]/gcd;
        ans+=x*lcm;
        lcm*=qb[i]/gcd;
    }
    int res=(ans%lcm+lcm)%lcm;
    if(res==0) res=lcm;
    return res;
}
bool check(int q){
    int cnt=(q/Lcm)*got;
    q%=Lcm;
    cnt+=q-(upper_bound(rep.begin(),rep.end(),q)-rep.begin());
    return cnt>=k;
}
```
**核心实现思想**：`exgcd` 函数用于求解扩展欧几里得算法；`excrt` 函数用于求解同余方程组；`check` 函数用于判断当前的 `q` 是否满足第 $k$ 次颜色不同的条件。

### 最优关键思路或技巧
- 利用最小公倍数 $\operatorname{lcm}(n,m)$ 作为循环节，将问题转化为在一个周期内求解。
- 使用扩展欧几里得算法（exgcd）求解同余方程组，确定两盏吊灯颜色相同的时刻。
- 部分题解使用二分答案来优化求解过程，提高效率。

### 拓展思路
同类型题或类似算法套路：
- 涉及周期性变化的问题，如时钟问题、循环序列问题等，可以考虑使用最小公倍数作为循环节进行处理。
- 求解同余方程组的问题，可使用扩展欧几里得算法或扩展中国剩余定理。

### 推荐洛谷题目
- P1082 [NOIP2012 提高组] 同余方程
- P3868 [TJOI2009] 猜数字
- P4777 [模板] 扩展中国剩余定理（EXCRT）

---
处理用时：60.58秒