# 题目信息

# Sonya and Hotels

## 题目描述

Sonya decided that having her own hotel business is the best way of earning money because she can profit and rest wherever she wants.

The country where Sonya lives is an endless line. There is a city in each integer coordinate on this line. She has $ n $ hotels, where the $ i $ -th hotel is located in the city with coordinate $ x_i $ . Sonya is a smart girl, so she does not open two or more hotels in the same city.

Sonya understands that her business needs to be expanded by opening new hotels, so she decides to build one more. She wants to make the minimum distance from this hotel to all others to be equal to $ d $ . The girl understands that there are many possible locations to construct such a hotel. Thus she wants to know the number of possible coordinates of the cities where she can build a new hotel.

Because Sonya is lounging in a jacuzzi in one of her hotels, she is asking you to find the number of cities where she can build a new hotel so that the minimum distance from the original $ n $ hotels to the new one is equal to $ d $ .

## 说明/提示

In the first example, there are $ 6 $ possible cities where Sonya can build a hotel. These cities have coordinates $ -6 $ , $ 5 $ , $ 6 $ , $ 12 $ , $ 13 $ , and $ 19 $ .

In the second example, there are $ 5 $ possible cities where Sonya can build a hotel. These cities have coordinates $ 2 $ , $ 6 $ , $ 13 $ , $ 16 $ , and $ 21 $ .

## 样例 #1

### 输入

```
4 3
-3 2 9 16
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 2
4 8 11 18 19
```

### 输出

```
5
```

# AI分析结果

### 题目翻译
# Sonya与酒店

## 题目描述
Sonya认为经营自己的酒店业务是赚钱的最佳方式，因为她可以在任何她想去的地方盈利和休息。

Sonya所在的国家是一条无限长的直线。这条直线上的每个整数坐标处都有一座城市。她有 $n$ 家酒店，其中第 $i$ 家酒店位于坐标为 $x_i$ 的城市。Sonya很聪明，所以她不会在同一个城市开设两家或更多的酒店。

Sonya明白她的业务需要通过开设新酒店来扩展，因此她决定再建一家。她希望这家新酒店到其他所有酒店的最小距离等于 $d$。这个女孩知道有很多可能的位置可以建造这样的酒店。因此，她想知道可以建造新酒店的城市的坐标数量。

因为Sonya正在她的一家酒店的按摩浴缸里放松，所以她让你找出她可以建造新酒店的城市数量，使得从原来的 $n$ 家酒店到新酒店的最小距离等于 $d$。

## 说明/提示
在第一个样例中，有 $6$ 个可能的城市可以让Sonya建造酒店。这些城市的坐标是 $ - 6$、$5$、$6$、$12$、$13$ 和 $19$。

在第二个样例中，有 $5$ 个可能的城市可以让Sonya建造酒店。这些城市的坐标是 $2$、$6$、$13$、$16$ 和 $21$。

## 样例 #1
### 输入
```
4 3
-3 2 9 16
```
### 输出
```
6
```

## 样例 #2
### 输入
```
5 2
4 8 11 18 19
```
### 输出
```
5
```

### 综合分析与结论
- **思路对比**：各题解思路基本一致，都是先考虑在最左侧和最右侧各能建一家酒店，所以初始答案为 2，然后枚举相邻两家酒店之间的距离，根据距离与 $2d$ 的大小关系判断可建造新酒店的数量。
- **算法要点**：核心算法是遍历相邻酒店的距离，根据 $2d$ 与相邻酒店距离的大小关系进行分类讨论，分别计算可建造新酒店的数量。
- **解决难点**：主要难点在于处理相邻酒店之间的距离与 $2d$ 的关系，判断新酒店的可建造位置，避免重复计算。

### 所选题解
- **作者：Node_Edge（5星）**
    - **关键亮点**：思路清晰，通过图文结合的方式详细解释了三种情况，代码可读性高。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,cnt=2;
int a[105];
int main(){
    cin>>n>>d;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n-1;i++){
        int x=a[i+1]-a[i];
        if(x>2*d) cnt+=2;
        else if(x==2*d) cnt++;
    }
    cout<<cnt;
    return 0;
}
```
核心实现思想：先读入酒店数量 $n$ 和最小距离 $d$，再读入每个酒店的坐标。遍历相邻酒店的距离，根据距离与 $2d$ 的大小关系更新可建造新酒店的数量，最后输出结果。

- **作者：猜一猜我是谁（4星）**
    - **关键亮点**：思路简洁明了，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[105];
int main(){
    long long n,d,ans=2;
    cin>>n>>d;
    for(long long i=1;i<=n;i++) cin>>a[i];
    for(long long i=1;i<n;i++){
        int b=a[i+1]-a[i];
        if(b==2*d) ans++;
        else if(b>2*d) ans+=2;
    }
    cout<<ans;
}
```
核心实现思想：与上一题解类似，先初始化答案为 2，读入数据后遍历相邻酒店距离，根据条件更新答案，最后输出。

- **作者：Luo_gu_ykc（4星）**
    - **关键亮点**：对思路和代码进行了详细注释，便于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int n, k, a[N], sum;
int main(){
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        if(i >= 2){
            int cha = a[i] - a[i - 1];
            if(cha == 2 * k){
                sum++;
            }
            if(cha > 2 * k){
                sum += 2;
            }
        }
    }
    cout << sum + 2;
    return 0;
}
```
核心实现思想：同样先读入数据，在读取每个酒店坐标时，计算相邻酒店的距离，根据距离与 $2k$ 的关系更新可建造酒店数量，最后加上最左侧和最右侧的两种情况输出结果。

### 最优关键思路或技巧
- **分类讨论**：根据相邻酒店距离与 $2d$ 的大小关系进行分类讨论，清晰地计算出可建造新酒店的数量。
- **初始化**：先考虑最左侧和最右侧的情况，将答案初始化为 2，简化后续计算。

### 拓展思路
同类型题目可能会改变问题场景，如在二维平面上给定一些点，要求找到一个新的点，使其到这些点的最小距离满足一定条件。解题思路仍然可以是先考虑边界情况，再枚举相邻点之间的关系进行分类讨论。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：涉及区间处理和分类讨论。
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)：需要对不同情况进行分析和计算。
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：需要根据条件进行模拟和判断。

### 个人心得摘录与总结
- **作者：maple_love**：开始看到题目以为很难，以为是在二维矩阵里求盈利最多的方法，后来发现想多了。总结：读题要准确，避免过度解读题目。

---
处理用时：31.66秒