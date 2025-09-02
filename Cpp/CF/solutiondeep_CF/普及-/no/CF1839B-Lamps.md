# 题目信息

# Lamps

## 题目描述

You have $ n $ lamps, numbered by integers from $ 1 $ to $ n $ . Each lamp $ i $ has two integer parameters $ a_i $ and $ b_i $ .

At each moment each lamp is in one of three states: it may be turned on, turned off, or broken.

Initially all lamps are turned off. In one operation you can select one lamp that is turned off and turn it on (you can't turn on broken lamps). You receive $ b_i $ points for turning lamp $ i $ on. The following happens after each performed operation:

- Let's denote the number of lamps that are turned on as $ x $ (broken lamps do not count). All lamps $ i $ such that $ a_i \le x $ simultaneously break, whether they were turned on or off.

Please note that broken lamps never count as turned on and that after a turned on lamp breaks, you still keep points received for turning it on.

You can perform an arbitrary number of operations.

Find the maximum number of points you can get.

## 说明/提示

In first test case $ n = 4 $ . One of ways to get the maximum number of points is as follows:

- You turn lamp $ 4 $ on and receive $ b_4 = 13 $ points.
- The number of lamps that are turned on is $ 1 $ , so all lamps with $ a_i \le 1 $ (namely lamps $ 2 $ , $ 3 $ and $ 4 $ ) break. Lamp $ 4 $ is no longer turned on, so the number of lamps that are turned becomes $ 0 $ .
- The only lamp you can turn on is lamp $ 1 $ , as all other lamps are broken. You receive $ b_1 = 2 $ points for turning it on.
- The number of lamps that are turned on is $ 1 $ . As $ a_1 = 2 $ , lamp $ 1 $ doesn't break.

Your receive $ 13 + 2 = 15 $ points in total. It can be shown that this is the maximum number of points you can get, so the answer for the first test case is $ 15 $ .

In the second test case, one of the ways to get the maximum number of points is as follows:

- On the first operation you turn on lamp $ 4 $ and receive $ 2 $ points. No lamps break after the first operation.
- On the second operation you turn on lamp $ 3 $ and receive $ 5 $ points. After the second operation, there are $ 2 $ lamps turned on. As $ a_3 \le 2 $ , lamp $ 3 $ breaks.
- On the third operation, you turn on lamp $ 1 $ and receive $ 4 $ points.
- On the fourth operation, you turn on lamp $ 5 $ and receive $ 3 $ points. After that there are $ 3 $ lamps turned on: lamps $ 1 $ , $ 4 $ and $ 5 $ . Lamps $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ simultaneously break, because for all of them $ a_i \le 3 $ .

You receive $ 2 + 5 + 4 + 3 = 14 $ points in total. It can be shown that this is the maximum number of points you can get.

In the third test case, one of the ways to get the maximum number of points is as follows:

- Turn the lamp $ 3 $ on and receive $ 4 $ points. Lamps $ 1 $ and $ 3 $ break.
- Turn the lamp $ 2 $ on and receive $ 4 $ points.
- Turn the lamp $ 6 $ on and receive $ 3 $ points. Lamp $ 6 $ breaks.
- Turn the lamp $ 4 $ on and receive $ 4 $ points.
- Turn the lamp $ 5 $ on and receive $ 5 $ points. Lamps $ 2 $ , $ 4 $ and $ 5 $ break.

You receive $ 4 + 4 + 3 + 4 + 5 = 20 $ points in total. It can be shown that this is the maximum number of points you can get.

## 样例 #1

### 输入

```
4
4
2 2
1 6
1 10
1 13
5
3 4
3 1
2 5
3 2
3 3
6
1 2
3 4
1 4
3 4
3 5
2 3
1
1 1```

### 输出

```
15
14
20
1```

# AI分析结果

### 题目翻译
你有 $n$ 盏灯，编号从 $1$ 到 $n$。每盏灯 $i$ 有两个整数参数 $a_i$ 和 $b_i$。

在每个时刻，每盏灯处于以下三种状态之一：打开、关闭或损坏。

最初，所有灯都处于关闭状态。在一次操作中，你可以选择一盏关闭的灯并将其打开（不能打开已损坏的灯）。打开灯 $i$ 时，你将获得 $b_i$ 分。每次操作完成后，会发生以下情况：

- 用 $x$ 表示当前打开的灯的数量（损坏的灯不计入）。所有满足 $a_i \le x$ 的灯 $i$ 会同时损坏，无论它们之前是打开还是关闭状态。

请注意，损坏的灯永远不会被视为打开状态，并且在打开的灯损坏后，你仍然保留打开该灯时获得的分数。

你可以执行任意数量的操作。

请找出你能获得的最大分数。

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，优先打开 $a$ 值较小的灯，确保在其坏掉之前拿到最多分数。对于相同 $a$ 值的灯，选择 $b$ 值最大的。题解们在实现上有所不同，部分使用队列维护打开的灯，部分使用分组、排序等方式处理。主要难点在于处理灯坏掉后打开灯数量的变化。

### 所选题解
- snowingbird（4星）
  - 关键亮点：思路清晰，详细解释了贪心策略和队列的使用，代码注释丰富。
  - 个人心得：提醒注意测试数量、排序细节、队列判空等容易出错的地方。
- beifa（4星）
  - 关键亮点：思路明确，结合队列维护灯的状态，对灯坏掉后 $x$ 的变化解释清晰。
  - 个人心得：强调认真审题，自己曾因审错题导致赛时没做出来。
- shower1114（4星）
  - 关键亮点：简洁明了地阐述贪心思路，手写队列实现模拟过程。

### 重点代码
#### snowingbird 的代码
```cpp
struct lamp{
    int a,b;
}lamps[200010];
queue<int>q;
bool cmp(lamp a,lamp b){
    if(a.a<b.a)return 1;
    if(a.a==b.a){
        if(a.b>b.b)return 1;
        return 0;
    }
    return 0;
} 
int main(){
    cin>>t;
    while(t--){
        while(!q.empty()){
            q.pop();
        }
        long long ans=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>lamps[i].a>>lamps[i].b;
        }
        sort(lamps+1,lamps+n+1,cmp);
        int mx=0;
        for(int i=1;i<=n;i++){
            int x=q.size();
            mx=max(mx,x);
            while(!q.empty()&&q.front()<=x){
                q.pop();
                x--; 
            }
            if(lamps[i].a<=mx)continue;
            ans+=lamps[i].b;
            q.push(lamps[i].a);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：先对灯按 $a$ 从小到大、$a$ 相同时按 $b$ 从大到小排序。使用队列维护打开的灯，模拟点亮过程，根据队列大小判断哪些灯坏掉，跳过已坏掉的灯，累加分数。

#### beifa 的代码
```cpp
struct lamp{
    int a , b;
}e[N];
bool cmp(lamp x , lamp y)
{
    if(x.a == y.a) return x.b > y.b;
    else return x.a < y.a;
}
signed main()
{
    cin >> t;
    while(t--)
    {
        queue<int>q;
        cin >> n;
        for(int i = 1 ; i <= n ; ++i)
        {
            cin >> e[i].a >> e[i].b;
        }
        sort(e+1,e+n+1,cmp);
        int f = 0;
        for(int i = 1; i <= n ; ++i)
        {
            if(f < e[i].a)
            {
                sum += e[i].b;
                x++;
                q.push(e[i].a);
                f = max(f,x);
            }
            while(!q.empty() && q.front() <= f)
            {
                x--;
                q.pop();
            }
        }
        cout << sum << '\n';
        x = 0;
        sum = 0;
    }
    return 0;
}
```
核心实现思想：同样先对灯排序，使用队列维护打开的灯。用变量 $f$ 记录坏灯的情况，当满足条件时累加分数，更新队列和 $f$ 的值。

#### shower1114 的代码
```cpp
struct node{
    int a,b;
}x[200005];
bool cmp(node p,node q){
    if(p.a == q.a) return p.b > q.b;
    return p.a < q.a;
}
signed main(){
    cin >> T;
    while(T--){
        int n;
        ans = 0;
        cin >> n;
        for(int i = 1;i <= n;i++){
            cin >> x[i].a >> x[i].b;
        }
        sort(x+1,x+1+n,cmp);
        int cnt = 0,h = 0;
        for(int i = 1;i <= n;i++){
            if(h>=i)continue;
            cnt++;
            ans += x[i].b;
            int t=h;
            while(x[t+1].a<=cnt && t<n) t++;
            cnt-=min(i,t)-h;
            h=t;
        }
        cout << ans << "\n";	
    }
    return 0;
}
```
核心实现思想：对灯排序后，手写队列模拟过程。通过变量 $cnt$ 记录打开灯的数量，$h$ 记录已处理的灯的位置，根据条件更新 $cnt$ 和 $h$，累加分数。

### 最优关键思路或技巧
- 贪心策略：优先打开 $a$ 值小的灯，相同 $a$ 值选 $b$ 值大的灯。
- 队列的使用：利用队列先进先出的特点，维护打开的灯，方便处理灯坏掉的情况。

### 拓展思路
同类型题可能会有更多状态或规则变化，但贪心的核心思想不变，即优先选择对结果更有利的操作。类似算法套路可以应用在资源分配、任务调度等问题中，通过合理排序和模拟过程来求解最优解。

### 推荐题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P2240 硬币购物](https://www.luogu.com.cn/problem/P2240)

### 个人心得总结
- 认真审题，注意题目中的细节，如灯坏掉后打开灯数量的变化。
- 实现时注意容易出错的地方，如测试数量、排序细节、队列判空等。 

---
处理用时：46.05秒