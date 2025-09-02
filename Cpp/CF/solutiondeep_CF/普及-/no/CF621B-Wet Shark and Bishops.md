# 题目信息

# Wet Shark and Bishops

## 题目描述

Today, Wet Shark is given $ n $ bishops on a $ 1000 $ by $ 1000 $ grid. Both rows and columns of the grid are numbered from $ 1 $ to $ 1000 $ . Rows are numbered from top to bottom, while columns are numbered from left to right.

Wet Shark thinks that two bishops attack each other if they share the same diagonal. Note, that this is the only criteria, so two bishops may attack each other (according to Wet Shark) even if there is another bishop located between them. Now Wet Shark wants to count the number of pairs of bishops that attack each other.

## 说明/提示

In the first sample following pairs of bishops attack each other: $ (1,3) $ , $ (1,5) $ , $ (2,3) $ , $ (2,4) $ , $ (3,4) $ and $ (3,5) $ . Pairs $ (1,2) $ , $ (1,4) $ , $ (2,5) $ and $ (4,5) $ do not attack each other because they do not share the same diagonal.

## 样例 #1

### 输入

```
5
1 1
1 5
3 3
5 1
5 5
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3
1 1
2 3
3 5
```

### 输出

```
0
```

# AI分析结果

### 题目内容中文重写
# 湿鲨鱼和象

## 题目描述
今天，湿鲨鱼在一个 $1000 \times 1000$ 的网格上放置了 $n$ 个象。网格的行和列都从 $1$ 到 $1000$ 编号。行是从上到下编号，列是从左到右编号。

湿鲨鱼认为，如果两个象在同一条对角线上，它们就会互相攻击。注意，这是唯一的判断标准，所以即使两个象之间有其他象，它们也可能互相攻击（按照湿鲨鱼的规则）。现在湿鲨鱼想计算互相攻击的象的对数。

## 说明/提示
在第一个样例中，以下象对会互相攻击：$(1,3)$、$(1,5)$、$(2,3)$、$(2,4)$、$(3,4)$ 和 $(3,5)$。象对 $(1,2)$、$(1,4)$、$(2,5)$ 和 $(4,5)$ 不会互相攻击，因为它们不在同一条对角线上。

## 样例 #1
### 输入
```
5
1 1
1 5
3 3
5 1
5 5
```
### 输出
```
6
```

## 样例 #2
### 输入
```
3
1 1
2 3
3 5
```
### 输出
```
0
```

### 算法分类
组合数学

### 综合分析与结论
这些题解主要围绕计算在 $1000 \times 1000$ 棋盘上象的互相攻击对数展开。大部分题解思路是利用象在对角线上的特性，即同一左上到右下对角线的象横纵坐标差相等，同一右上到左下对角线的象横纵坐标和相等，统计每条对角线上象的数量，再用组合数学公式 $\frac{n(n - 1)}{2}$ 计算攻击对数。部分题解采用暴力 DFS 或排序的方法，但暴力 DFS 可能超时，排序方法相对复杂。

### 所选题解
- **作者：fzj2007 (赞：8)，4星**
  - **关键亮点**：思路清晰，详细讲解了找规律的过程，代码有注释，使用快读优化输入。
  - **个人心得**：强调要注意题目中象攻击规则与国际象棋不同，这是一个大坑，提醒要仔细审题。
- **作者：流绪 (赞：1)，4星**
  - **关键亮点**：思路简洁明了，直接阐述核心思路，代码实现简洁。
- **作者：achjuncool (赞：0)，4星**
  - **关键亮点**：使用 `unordered_map` 存储对角线信息，避免了数组下标可能为负的问题，代码逻辑清晰。

### 重点代码
#### fzj2007 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int ans=0,flag=1;
    char ch=getchar();
    while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
    if(ch=='-') flag=-1,ch=getchar();
    while(ch>='0'&&ch<='9'){
        ans=(ans<<1)+(ans<<3)+(ch^'0');
        ch=getchar();
    }
    return ans*flag;
}
int n,x,y;
int a[2005],b[2005];
long long ans;
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        x=read(),y=read();
        a[x+y]++;
        b[y-x+1001]++;
    }
    for(int i=0;i<=2000;i++)
        ans+=(long long)(a[i]*(a[i]-1)+b[i]*(b[i]-1))/2;
    printf("%lld\n",ans);
    return 0;
}
```
**核心实现思想**：先使用快读读取输入，然后统计每条对角线上象的数量，最后根据组合数学公式计算攻击对数。

#### 流绪的代码
```cpp
#include<bits/stdc++.h>
#define ll long long 
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define mod 10
using namespace std;
int a[maxn],b[maxn]; 
int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int c,d;
        cin >> c >> d;
        a[c+d]++;
        b[d-c+1000]++;
    }
    ll cnt = 0; 
    for(int i=1;i<=2000;i++)
        cnt +=a[i]*(a[i]-1)/2+b[i]*(b[i]-1)/2;
    cout << cnt;
    return 0; 
}  
```
**核心实现思想**：统计每条对角线上象的数量，再根据组合数学公式计算攻击对数。

#### achjuncool 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
ll n, x, y, ans;
unordered_map<ll, ll> add, minus1;
unordered_map<ll, ll>::iterator it;
int main(){
    qwq;
    cin >> n;
    for(ll i = 1; i <= n; i++){
        cin >> x >> y;
        it = add.find(x + y);
        if(it == add.end()) add[x + y] = 1;
        else add[x + y]++;
        it = minus1.find(x - y);
        if(it == minus1.end()) minus1[x - y] = 1;
        else minus1[x - y]++;
    }
    for(auto p = add.begin(); p != add.end(); p++) ans += (p->second - 1) * p->second / 2;
    for(auto p = minus1.begin(); p != minus1.end(); p++) ans += (p->second - 1) * p->second / 2;
    cout << ans << endl;
    return 0;
}
```
**核心实现思想**：使用 `unordered_map` 存储每条对角线上象的数量，最后根据组合数学公式计算攻击对数。

### 最优关键思路或技巧
- 利用象在对角线上的特性，通过横纵坐标的和与差来判断是否在同一条对角线上。
- 使用组合数学公式 $\frac{n(n - 1)}{2}$ 计算每条对角线上象的攻击对数。
- 对于可能出现的负下标，通过加上一个足够大的数来处理。

### 拓展思路
同类型题可能会改变棋盘大小、棋子类型或攻击规则，但核心思路还是利用棋子的位置特性和组合数学知识来计算对数。类似算法套路可用于解决其他涉及位置关系和组合计数的问题。

### 推荐题目
- [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)
- [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)

---
处理用时：42.20秒