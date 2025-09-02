# 题目信息

# Lala Land and Apple Trees

## 题目描述

Amr lives in Lala Land. Lala Land is a very beautiful country that is located on a coordinate line. Lala Land is famous with its apple trees growing everywhere.

Lala Land has exactly $ n $ apple trees. Tree number $ i $ is located in a position $ x_{i} $ and has $ a_{i} $ apples growing on it. Amr wants to collect apples from the apple trees. Amr currently stands in $ x=0 $ position. At the beginning, he can choose whether to go right or left. He'll continue in his direction until he meets an apple tree he didn't visit before. He'll take all of its apples and then reverse his direction, continue walking in this direction until he meets another apple tree he didn't visit before and so on. In the other words, Amr reverses his direction when visiting each new apple tree. Amr will stop collecting apples when there are no more trees he didn't visit in the direction he is facing.

What is the maximum number of apples he can collect?

## 说明/提示

In the first sample test it doesn't matter if Amr chose at first to go left or right. In both cases he'll get all the apples.

In the second sample test the optimal solution is to go left to $ x=-1 $ , collect apples from there, then the direction will be reversed, Amr has to go to $ x=1 $ , collect apples from there, then the direction will be reversed and Amr goes to the final tree $ x=-2 $ .

In the third sample test the optimal solution is to go right to $ x=1 $ , collect apples from there, then the direction will be reversed and Amr will not be able to collect anymore apples because there are no apple trees to his left.

## 样例 #1

### 输入

```
2
-1 5
1 5
```

### 输出

```
10```

## 样例 #2

### 输入

```
3
-2 2
1 4
-1 3
```

### 输出

```
9```

## 样例 #3

### 输入

```
3
1 9
3 5
7 10
```

### 输出

```
9```

# AI分析结果

### 题目翻译
# Lala Land 和苹果树

## 题目描述
Amr 生活在 Lala Land。Lala Land 是一个非常美丽的国家，它位于一条坐标线上。Lala Land 以其随处可见的苹果树而闻名。

Lala Land 恰好有 $n$ 棵苹果树。第 $i$ 棵树位于位置 $x_{i}$，树上结有 $a_{i}$ 个苹果。Amr 想从这些苹果树上收集苹果。Amr 目前站在 $x = 0$ 的位置。一开始，他可以选择向右或向左走。他会沿着这个方向一直走，直到遇到一棵他还没去过的苹果树。他会摘下这棵树上的所有苹果，然后改变方向，继续沿着新的方向走，直到遇到另一棵他还没去过的苹果树，依此类推。换句话说，Amr 每次访问一棵新的苹果树时就会改变方向。当他面对的方向上没有他还没去过的树时，Amr 就会停止收集苹果。

他最多能收集多少个苹果？

## 说明/提示
在第一个样例测试中，Amr 一开始选择向左还是向右走并不重要。在这两种情况下，他都会得到所有的苹果。

在第二个样例测试中，最优的解决方案是先向左走到 $x = -1$，从那里收集苹果，然后改变方向，Amr 必须走到 $x = 1$，从那里收集苹果，然后再次改变方向，Amr 走到最后一棵树 $x = -2$。

在第三个样例测试中，最优的解决方案是向右走到 $x = 1$，从那里收集苹果，然后改变方向，Amr 将无法再收集到更多的苹果，因为他左边没有苹果树了。

## 样例 #1
### 输入
```
2
-1 5
1 5
```
### 输出
```
10
```

## 样例 #2
### 输入
```
3
-2 2
1 4
-1 3
```
### 输出
```
9
```

## 样例 #3
### 输入
```
3
1 9
3 5
7 10
```
### 输出
```
9
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即优先选择苹果树数量多的一侧开始采摘，这样可以多采摘一次。题解的主要步骤包括：将苹果树按坐标正负分类存储，对分类后的苹果树按坐标排序，计算左右两侧苹果树数量，根据数量关系确定采摘顺序并计算最大苹果数。

各题解的不同之处在于数据结构的选择（如结构体数组、vector、二维数组等）和代码实现细节，但整体思路一致。

### 所选题解
- **作者：ForMyDream (赞：4)，4星**
    - **关键亮点**：思路清晰，有详细的分析和注释，代码结构简洁，使用结构体存储苹果树信息，易于理解。
    - **个人心得**：无
- **作者：crh1272336175 (赞：1)，4星**
    - **关键亮点**：使用 vector 和 pair 存储苹果树信息，代码简洁，时间复杂度分析明确。
    - **个人心得**：无
- **作者：TLEWA (赞：1)，4星**
    - **关键亮点**：思路清晰，对不同情况的分析明确，代码注释详细。
    - **个人心得**：无

### 重点代码
#### ForMyDream 的代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;

struct Tree{
    int apple,address;
    //树上的苹果 坐标 
};
Tree pos[101],neg[101];
//positive 存储坐标为正的树 negative 存储坐标为负的树 
int n,x,a,pos1,pos2;//指针 在存储、记录方面用 

bool cmp(Tree t1,Tree t2){
    return t1.address<t2.address;
    //记住树的坐标是混乱的 要按照坐标排序 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>x>>a;
        if (x<0){
            x=-x;
            neg[pos2].address=x;neg[pos2].apple=a;
            pos2++; 
        }else {
            pos[pos1].address=x;pos[pos1].apple=a;
            pos1++;
        } 
    }
    sort(pos,pos+pos1,cmp);
    sort(neg,neg+pos2,cmp);
    int x=min(pos1,pos2),ans=0;
    for (int i=0;i<x;i++){
        ans+=pos[i].apple;
        ans+=neg[i].apple;
    }
    if (pos1>pos2) ans+=pos[x].apple;
    else if (pos2>pos1) ans+=neg[x].apple;
    cout<<ans;
    return 0;
} 
```
**核心实现思想**：使用结构体 `Tree` 存储苹果树信息，将坐标为正和负的树分别存储在 `pos` 和 `neg` 数组中，对数组排序后，以树少的一侧为基准，两侧同时累加苹果数，最后根据两侧树的数量关系，多加上树多一侧的一个苹果树的苹果数。

#### crh1272336175 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
const int N=1005;
ll n,ans;
vector<PLL> le,ri;//正方向，负方向 
int main()
{
    scanf("%lld",&n);
    for(register ll i=1; i<=n; i++)
    {
        ll a,b; scanf("%lld%lld",&a,&b);
        if(a>0) ri.push_back({a,b});
        else le.push_back({-a,b});
    }
    sort(ri.begin(),ri.end());
    sort(le.begin(),le.end());
    ll num=min(le.size(),ri.size());
    for(register ll i=0; i<num; i++)
        ans+=le[i].second+ri[i].second;
    if(le.size()>ri.size()) ans+=le[ri.size()].second;
    else if(le.size()<ri.size()) ans+=ri[le.size()].second;
    printf("%lld",ans);
    return 0;
}
```
**核心实现思想**：使用 `vector<PLL>` 存储苹果树信息，将坐标为正和负的树分别存储在 `ri` 和 `le` 中，对 `vector` 排序后，以树少的一侧的数量为基准，两侧同时累加苹果数，最后根据两侧树的数量关系，多加上树多一侧的一个苹果树的苹果数。

#### TLEWA 的代码
```cpp
#include<bits/stdc++.h>

using namespace std;

struct Node{ //用来存储苹果信息的结构体
    int val,num;
}arr1[10086],arr2[10086];

int p1,p2; //两个变量,作为指针使用
long long summ; //计数变量

bool cmp(Node n1,Node n2){ //别问我为什么不用pair(其实是忘了)
    return n1.val<n2.val;
}

int main(){
    ios::sync_with_stdio(false); //解除同步流
    cin.tie(0);
    cout.tie(0);
    int n,val,num;
    cin >> n;
    for(int i=0;i!=n;++i){ //循环读入
        cin >> val >> num;
        if(val<0) arr1[p1].val=-val/*倒序一下*/,arr1[p1].num=num,p1++; //给垃圾(划掉)苹果分类
        else arr2[p2].val=val,arr2[p2].num=num,p2++;
    }
    //将分好类的苹果分别排序
    sort(arr1,arr1+p1,cmp);
    sort(arr2,arr2+p2,cmp);
    
    int p3=min(p1,p2);
    for(int i=0;i<p3;++i){
        summ+=arr1[i].num+arr2[i].num; //两个数组同时累加
    }
    //最后判断一下哪边大
    if(p1<p2) summ+=arr2[p3].num;
    else if(p1>p2) summ+=arr1[p3].num;
    
    cout << summ; //输出结果
    return 0;
}
```
**核心实现思想**：使用结构体 `Node` 存储苹果树信息，将坐标为正和负的树分别存储在 `arr2` 和 `arr1` 数组中，对数组排序后，以树少的一侧的数量为基准，两侧同时累加苹果数，最后根据两侧树的数量关系，多加上树多一侧的一个苹果树的苹果数。

### 最优关键思路或技巧
- **贪心策略**：优先选择苹果树数量多的一侧开始采摘，可多采摘一次，从而获得最大苹果数。
- **分类存储**：将坐标为正和负的苹果树分别存储，便于后续处理。
- **排序**：对分类后的苹果树按坐标排序，确保采摘顺序正确。

### 拓展思路
同类型题或类似算法套路：在一些涉及选择策略以获取最优解的题目中，可考虑贪心算法。例如，在资源分配、区间选择等问题中，通过分析问题的特点，找到局部最优的选择策略，从而得到全局最优解。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略合并果子，使总代价最小。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：使用贪心算法解决部分背包问题，获取最大价值。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过贪心策略安排排队顺序，使平均等待时间最短。

### 个人心得摘录与总结
无

---
处理用时：59.83秒