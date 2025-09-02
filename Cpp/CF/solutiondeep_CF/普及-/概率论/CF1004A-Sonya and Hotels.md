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

Sonya所在的国家是一条无限长的直线。在这条直线的每个整数坐标处都有一座城市。她拥有 $n$ 家酒店，其中第 $i$ 家酒店位于坐标为 $x_i$ 的城市。Sonya很聪明，所以她不会在同一座城市开设两家或更多的酒店。

Sonya明白她的业务需要通过开设新酒店来扩张，所以她决定再建一家。她希望这家新酒店到其他所有酒店的最小距离等于 $d$。这个女孩明白有很多可能的位置可以建造这样一家酒店。因此，她想知道可以建造新酒店的城市的坐标数量。

由于Sonya正在她的一家酒店的按摩浴缸里悠闲地泡澡，她请你找出她可以建造新酒店的城市数量，使得从原来的 $n$ 家酒店到新酒店的最小距离等于 $d$。

## 说明/提示
在第一个样例中，有 $6$ 个可能的城市可以让Sonya建造酒店。这些城市的坐标分别是 $-6$、$5$、$6$、$12$、$13$ 和 $19$。

在第二个样例中，有 $5$ 个可能的城市可以让Sonya建造酒店。这些城市的坐标分别是 $2$、$6$、$13$、$16$ 和 $21$。

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
- **思路对比**：所有题解核心思路一致，先考虑在最左侧酒店左边和最右侧酒店右边各能建一家新酒店，初始答案为 2。接着枚举相邻两家酒店的间隔，根据间隔与 $2d$ 的大小关系判断可建酒店数量。
- **算法要点**：主要是遍历相邻酒店间隔，通过比较间隔和 $2d$ 的大小来更新可建酒店的总数。
- **解决难点**：关键在于处理相邻酒店间隔不同情况，避免重复计算。如当间隔等于 $2d$ 时，两个可建点重合，只能算一个；间隔小于 $2d$ 时，中间不能建酒店。

### 所选题解
- **作者：Node_Edge（5星）**
    - **关键亮点**：思路清晰，通过配图直观展示三种情况，代码简洁易懂。
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
核心思想：先初始化可建酒店数为 2，遍历相邻酒店间隔，根据间隔与 $2d$ 的关系更新可建酒店数。
- **作者：猜一猜我是谁（4星）**
    - **关键亮点**：思路明确，代码简洁，变量使用清晰。
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
核心思想：同样先将答案初始化为 2，遍历相邻酒店间隔，依据间隔和 $2d$ 的比较结果更新答案。
- **作者：Hanghang（4星）**
    - **关键亮点**：代码简洁，注释清晰，对变量含义解释明确。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,s=2,x,y;
int main()
{
   cin>>n>>k>>x;y=x;
    for(int i=1;i<n;i++)
    {
        y=x;cin>>x;
        if(x-y>k*2)s+=2;
        if(x-y==k*2)s++;
    }
    cout<<s<<endl;
    return 0;
}
```
核心思想：初始化方案数为 2，通过不断更新当前酒店和上一个酒店的坐标，比较间隔与 $2k$ 的大小更新方案数。

### 最优关键思路或技巧
- 思维方式：先考虑边界情况（最左和最右），再枚举中间相邻酒店间隔，将复杂问题分解为简单的比较问题。
- 代码实现：使用一个变量记录可建酒店总数，根据不同情况更新该变量，简化代码逻辑。

### 可拓展之处
同类型题可能会拓展到二维平面或三维空间，判断新点到已知点的最小距离。类似算法套路是先确定边界情况，再枚举相邻元素的间隔或位置关系，根据条件更新结果。

### 推荐题目
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：涉及数据的排序和去重，与本题对酒店坐标的处理有相似之处。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：需要对数据进行排序并根据相邻元素关系计算结果。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：通过枚举区间来处理问题，和本题枚举相邻酒店间隔类似。

### 个人心得摘录与总结
- **作者：maple_love**：开始误将题目理解为二维矩阵中求盈利最多的方法，后来发现想多了。总结是要仔细读题，明确题目要求，避免过度联想。 

---
处理用时：30.60秒