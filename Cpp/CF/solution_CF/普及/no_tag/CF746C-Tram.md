# Tram

## 题目描述

The tram in Berland goes along a straight line from the point $ 0 $ to the point $ s $ and back, passing $ 1 $ meter per $ t_{1} $ seconds in both directions. It means that the tram is always in the state of uniform rectilinear motion, instantly turning around at points $ x=0 $ and $ x=s $ .

Igor is at the point $ x_{1} $ . He should reach the point $ x_{2} $ . Igor passes $ 1 $ meter per $ t_{2} $ seconds.

Your task is to determine the minimum time Igor needs to get from the point $ x_{1} $ to the point $ x_{2} $ , if it is known where the tram is and in what direction it goes at the moment Igor comes to the point $ x_{1} $ .

Igor can enter the tram unlimited number of times at any moment when his and the tram's positions coincide. It is not obligatory that points in which Igor enter and exit the tram are integers. Assume that any boarding and unboarding happens instantly. Igor can move arbitrary along the line (but not faster than $ 1 $ meter per $ t_{2} $ seconds). He can also stand at some point for some time.

## 说明/提示

In the first example it is profitable for Igor to go by foot and not to wait the tram. Thus, he has to pass $ 2 $ meters and it takes $ 8 $ seconds in total, because he passes $ 1 $ meter per $ 4 $ seconds.

In the second example Igor can, for example, go towards the point $ x_{2} $ and get to the point $ 1 $ in $ 6 $ seconds (because he has to pass $ 3 $ meters, but he passes $ 1 $ meters per $ 2 $ seconds). At that moment the tram will be at the point $ 1 $ , so Igor can enter the tram and pass $ 1 $ meter in $ 1 $ second. Thus, Igor will reach the point $ x_{2} $ in $ 7 $ seconds in total.

## 样例 #1

### 输入

```
4 2 4
3 4
1 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 4 0
1 2
3 1
```

### 输出

```
7
```

# 题解

## 作者：封禁用户 (赞：5)

# 0.前言
http://codeforces.com/contest/746/problem/C

再次提交一道题的第一个题解。

题目大意：在一条直线上，有一辆公共汽车从点 $0$ 到点 $s$，不断往返，速度为 $t1$ 秒每米；有一个人，要从点 $x1$ 到点 $x2$，速度为 $t2$ 秒每米；
当人和车子的位置重叠时，人可以上车，之后可以随时下车。（上下车时间忽略）
现在求人到达目的地的最短时间是多少？
# 1.解析
题目限制： $0≤x1,x2≤s$， 表示行程最终一定会覆盖到 $x1$ 和 $x2$。
那么就不会出现人上车后下车再走的情况。
学过贪心策略的人会知道：一直走到终点站或者走一段距离，然后上车，一直到终点。
 
直接走到终点的时间为 $time1=t2\times |x2 - x1|$;

第二种情况：
假设人在 $x1$ 不动，等车过来。
计算出来车第一次经过终点的时间，同时看这个有没有经过点 $x1$；
如果没有计算车第二次经过终点的时间，直到经过点 $x1$，得到 $time2$;
 
$ans=\min(time1,time2)$

# 2.code
主函数部分放上：（~~你要是想抄题解的话直接加头文件啥的就行~~）
```cpp
int main(){
    int s, x1, x2, t1, t2, p, d;
    cin >> s >> x1 >> x2 >> t1 >> t2 >> p >> d;
    int ans = abs(x1 - x2) * t2; // 直接走到终点
    int t = 0, ok = 0;
    if (p != x2) { // 车先到达终点
        if (p < x2) {
            t = (x2 - p) * t1;
            if (d == -1) {
                t += p * 2 * t1;
                d = -d;
                if (x1 <= x2) ok = 1;
            }
            else {
                if (x1 <= x2 && p <= x1) ok = 1;
            }
        }
        else {
            t = (p - x2) * t1;
            if (d == 1) {
                t += (s - p) * 2 * t1;
                if (x1 >= x2) {
                    ok = 1;
                }
                d = -d;
            }
            else {
                if (x1 >= x2 && x1 <= p) ok = 1;
            }
        }
    }
    if (ok) ans = min(ans, t);
    else {
        if ((x2 - x1) / d > 0) t += s * 2 * t1;
        else {
            if (x2 < x1) t += (s - x2) * 2 * t1;
            else t += x2 * 2 * t1;
        }
        ans = min(ans, t);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：xrtbclx (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF746C)
### 思路：
不难发现，本题中有几种可能为最优方案的方案。先将每个方案的时间计算公式推出，再带入数据，算出具体用时。最后比较得最优方案，输出即可。

### 具体一点：
由于 $0 \le x_1,x_2 \le s$，所以由贪心策略知：走一段后上车再下车再走的策略绝对不是最优的。
#### 方案1：
贪心策略，一直走到底，或走一段后坐车。时间 $time_1 = t_2 \times | x_2-x_1|$。

#### 方案2：
同样是贪心策略，一直等到车来，再坐车。计算车第一次经过终点的时间，同时看有没有经过点 $x_1$，如果没有计算车第二次经过终点的时间，直到经过 $x_1$，得 $time_2$。

#### 答案：  
$ans = \min(time_1,time_2)$。

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF746C)

## 题意
有一辆电车在数轴上从坐标点 $0$ 到坐标点 $s$，以 $t_1$ 秒每米的速度匀速往返运行，并在点 $x=0$ 和点 $x=s$ 处瞬间转向。你现从点 $x_1$ 出发要到达点 $x_2$，你可以选择步行（速度为 $t_2$ 秒每米），也可以坐车，最短需要多长时间？已知你从坐标点 $x_1$ 出发时电车的位置为 $p$ 和运行方向（用 $d$ 表示），你可以在任何时刻进入电车，且进入和离开电车的位置不一定是整数，上下车瞬间完成，当然也可以在某个点停留任意时间。

## 思路
通过画图我们看到总共有两种可能：
- 画图可以看出来，往目标方向走让车追你和往目标方向相反的方向去迎车的时间只会更快。所以要先往目标走后坐车。时间为 $time_1=t_2\times|x_2-x_1|$。
- 第二种情况为在原地不动等车，等到后全程坐车。计算车经过终点的且同时经过点 $x_1$，得到 $time_2$。

最后答案即为两种答案的最小值。

---

