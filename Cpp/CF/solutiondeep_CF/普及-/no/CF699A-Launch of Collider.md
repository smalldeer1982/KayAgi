# 题目信息

# Launch of Collider

## 题目描述

There will be a launch of a new, powerful and unusual collider very soon, which located along a straight line. $ n $ particles will be launched inside it. All of them are located in a straight line and there can not be two or more particles located in the same point. The coordinates of the particles coincide with the distance in meters from the center of the collider, $ x_{i} $ is the coordinate of the $ i $ -th particle and its position in the collider at the same time. All coordinates of particle positions are even integers.

You know the direction of each particle movement — it will move to the right or to the left after the collider's launch start. All particles begin to move simultaneously at the time of the collider's launch start. Each particle will move straight to the left or straight to the right with the constant speed of $ 1 $ meter per microsecond. The collider is big enough so particles can not leave it in the foreseeable time.

Write the program which finds the moment of the first collision of any two particles of the collider. In other words, find the number of microseconds before the first moment when any two particles are at the same point.

## 说明/提示

In the first sample case the first explosion will happen in $ 1 $ microsecond because the particles number $ 1 $ and $ 2 $ will simultaneously be at the same point with the coordinate $ 3 $ .

In the second sample case there will be no explosion because there are no particles which will simultaneously be at the same point.

## 样例 #1

### 输入

```
4
RLRL
2 4 6 10
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
LLR
40 50 60
```

### 输出

```
-1
```

# AI分析结果

【题目内容（中文重写）】
# 对撞机的启动

## 题目描述
很快将会有一台全新、强大且不同寻常的对撞机启动，它沿着一条直线分布。将会有 $n$ 个粒子在其中发射。所有粒子都位于一条直线上，且不能有两个或更多粒子位于同一点。粒子的坐标与它们到对撞机中心的距离（单位：米）一致，$x_{i}$ 是第 $i$ 个粒子的坐标，同时也是它在对撞机中的位置。所有粒子位置的坐标均为偶数。

你知道每个粒子的运动方向 —— 在对撞机启动后，它将向左或向右移动。所有粒子在对撞机启动的瞬间同时开始移动。每个粒子将以每秒 1 米的恒定速度向左或向右直线移动。对撞机足够大，在可预见的时间内粒子不会离开它。

编写一个程序，找出对撞机中任意两个粒子首次碰撞的时刻。换句话说，找出任意两个粒子首次位于同一点之前的微秒数。

## 说明/提示
在第一个样例中，第一次碰撞将在 1 微秒后发生，因为 1 号和 2 号粒子将同时位于坐标为 3 的点。

在第二个样例中，不会发生碰撞，因为没有粒子会同时位于同一点。

## 样例 #1
### 输入
```
4
RLRL
2 4 6 10
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3
LLR
40 50 60
```
### 输出
```
-1
```

【算法分类】
枚举

【综合分析与结论】
- **思路对比**：大部分题解思路一致，均认为只有相向（左 L 右 R）的粒子才可能相遇，同向粒子因速度相同不会相遇。多数题解直接枚举相邻的“R - L”组合来计算相遇时间；peppaking8 的题解先排序再处理，增加了复杂度。
- **算法要点**：核心要点是判断相邻粒子的方向是否为“R - L”，若是则计算相遇时间（两粒子距离的一半），最后取所有可能相遇时间的最小值。
- **解决难点**：主要难点在于理解粒子运动情况，排除同向和反向（非相邻“R - L”）不会相遇的情况，准确计算相遇时间。

【所选的题解】
- **pandaSTT（5星）**：
  - **关键亮点**：思路清晰，明确指出题目中坐标递增，无需排序，时间复杂度为 $O(n)$；代码中添加快读优化，提高效率。
  - **个人心得**：无
- **开始新的记忆（4星）**：
  - **关键亮点**：代码简洁，直接枚举相邻“R - L”组合计算相遇时间。
  - **个人心得**：无
- **Eason_AC（4星）**：
  - **关键亮点**：思路简洁明了，代码实现直接，准确解决问题。
  - **个人心得**：无

【重点代码】
- **pandaSTT 的核心代码**：
```cpp
int n,ans=INF;
string s;
struct nobe{
    int position;
    char direction;
}arr[200005];
int main(){
    n=read();
    cin>>s;
    for(int i=1;i<=n;i++){
        arr[i].position=read();
        arr[i].direction=s[i-1];
        if(i!=1){
            if(arr[i].direction=='L'&&arr[i-1].direction=='R'){
                ans=min(ans,(arr[i].position-arr[i-1].position)/2);
            }
        }
    }
    if(ans==INF){
        ans=-1;
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：定义结构体存储粒子的位置和方向，通过快读读取输入，遍历粒子，判断相邻粒子是否为“R - L”组合，若是则计算相遇时间并更新最小值，最后根据结果输出 -1 或最小相遇时间。

- **开始新的记忆的核心代码**：
```cpp
int n,a[100010],ans=0x7fffffff;
string s;
int main()
{
    cin>>n>>s;
    for(int i=0;i<n;++i)
        cin>>a[i];
    for(int i=1;i<n;++i)
        if(s[i-1]=='R' && s[i]=='L')
            ans=min(ans,abs(a[i-1]-a[i])/2);
    if(ans==0x7fffffff)
        cout<<-1<<endl;
    else 
        cout<<ans<<endl;
    return 0;
}
```
**核心实现思想**：用数组存储粒子坐标，读取输入后，遍历数组，判断相邻粒子是否为“R - L”组合，若是则计算相遇时间并更新最小值，最后根据结果输出 -1 或最小相遇时间。

- **Eason_AC 的核心代码**：
```cpp
char s[200007];
int n, a[200007], ans = 0x3f3f3f3f;
int main() {
    scanf("%d%s", &n, s + 1);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 2; i <= n; ++i)
        if(s[i - 1] == 'R' && s[i] == 'L') ans = min(ans, (a[i] - a[i - 1]) / 2);
    printf("%d", (ans == 0x3f3f3f3f) ? -1 : ans);
}
```
**核心实现思想**：用数组存储粒子坐标和方向，读取输入后，遍历数组，判断相邻粒子是否为“R - L”组合，若是则计算相遇时间并更新最小值，最后根据结果输出 -1 或最小相遇时间。

【最优关键思路或技巧】
- 利用题目中坐标递增的条件，直接枚举相邻的“R - L”组合，避免不必要的排序和复杂计算，将时间复杂度控制在 $O(n)$。
- 初始化答案为一个极大值，方便后续更新最小值。

【拓展思路】
同类型题可能会改变粒子的速度、运动规则或增加更多维度的信息。类似算法套路是先分析物体的运动规律，找出可能发生碰撞或其他事件的条件，然后通过枚举或其他方法找出满足条件的最小时间或其他最优解。

【推荐题目】
- P1036 选数：枚举组合情况，计算满足条件的组合数量。
- P1217 [USACO1.5] 回文质数：枚举数字，判断是否为回文数和质数。
- P1057 传球游戏：枚举传球过程，计算不同传球次数下的传球方案数。

---
处理用时：42.14秒