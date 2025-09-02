# 题目信息

# Green and Black Tea

## 题目描述

Innokentiy likes tea very much and today he wants to drink exactly $ n $ cups of tea. He would be happy to drink more but he had exactly $ n $ tea bags, $ a $ of them are green and $ b $ are black.

Innokentiy doesn't like to drink the same tea (green or black) more than $ k $ times in a row. Your task is to determine the order of brewing tea bags so that Innokentiy will be able to drink $ n $ cups of tea, without drinking the same tea more than $ k $ times in a row, or to inform that it is impossible. Each tea bag has to be used exactly once.

## 样例 #1

### 输入

```
5 1 3 2
```

### 输出

```
GBGBG
```

## 样例 #2

### 输入

```
7 2 2 5
```

### 输出

```
BBGBGBB```

## 样例 #3

### 输入

```
4 3 4 0
```

### 输出

```
NO
```

# AI分析结果

### 题目内容（中文重写）
# 绿茶和红茶

## 题目描述
伊诺肯季非常喜欢喝茶，今天他正好想喝 $n$ 杯茶。他很乐意喝更多，但他正好有 $n$ 个茶包，其中 $a$ 个是绿茶，$b$ 个是红茶。

伊诺肯季不喜欢连续喝超过 $k$ 次同一种茶（绿茶或红茶）。你的任务是确定泡茶包的顺序，使伊诺肯季能够喝到 $n$ 杯茶，且不会连续喝同一种茶超过 $k$ 次，或者告知这是不可能的。每个茶包必须恰好使用一次。

## 样例 #1
### 输入
```
5 1 3 2
```
### 输出
```
GBGBG
```

## 样例 #2
### 输入
```
7 2 2 5
```
### 输出
```
BBGBGBB
```

## 样例 #3
### 输入
```
4 3 4 0
```
### 输出
```
NO
```

### 算法标签
贪心

### 综合分析与结论
这些题解主要围绕如何判断能否构造出符合条件的喝茶顺序以及如何构造展开。大部分题解采用贪心算法，每次优先选择剩余数量多的茶，同时考虑连续喝同一种茶不超过 $k$ 次的限制。难点在于判断无解的情况，不同题解给出了不同的判断条件。部分题解还尝试了搜索算法，但因超时而放弃。

### 所选题解
- **作者：_Michael0727_（5星）**
    - **关键亮点**：思路清晰，先尝试深搜但因超时改用贪心算法，详细给出了无解的判断条件，代码实现逻辑明确。
    - **个人心得**：一开始用深搜 DFS 枚举超时，后来发现可以用贪心做。
- **作者：PR_CYJ（4星）**
    - **关键亮点**：同样采用贪心算法，简洁地给出了无解判断条件和构造方法，代码简洁。
- **作者：OI_AKed_me（4星）**
    - **关键亮点**：明确指出题目两个难点（判断能否做到和构造），构造时注意到了一些细节，代码有一定优化。

### 重点代码
#### _Michael0727_ 的代码
```cpp
# include <bits/stdc++.h>
using namespace std ;
int n , k , a , b , ai , bi ; 
int main ( )
{
    cin >> n >> k >> a >> b ;
    if ( ( a + 1 < ( b + k - 1 ) / k ) || ( b + 1 < ( a + k - 1 ) / k ) ) // 无解特判 1
    {
        cout << "NO" << endl ;
        exit ( 0 ) ;
    }
    if ( k == 0 ) // 无解特判 2
    {
        cout << "NO" << endl ;
        exit ( 0 ) ;
    }
    for ( int i = 1 ; i <= n ; i ++ )
    {
        if ( a >= b && ai < k )
        {
            bi = 0 ;
            for ( int j = ai ; j < k && a >= 1 && i <= n ; i ++ , j ++ , a -- )
            {
                cout << 'G' ;
                ai ++ ;
            }
            if ( b )
            {
                cout << 'B' ;
                ai = 0 ;
                bi = 1 ;
                b -- ;
            }
        }
        else if ( bi < k )
        {
            ai = 0 ;
            for ( int j = bi ; j < k && b >= 1 && i <= n ; i ++ , j ++ , b -- )
            {
                cout << 'B' ;
                bi ++ ;
            }
            if ( a )
            {
                cout << 'G' ;
                bi = 0 ;
                ai = 1 ;
                a -- ;
            }
        }
        else if ( bi < k && b )
        {
            cout << 'B' ;
            ai = 0 ;
            bi ++ ;
            b -- ;
        }
        else
        {
            cout << 'G' ;
            bi = 0 ;
            ai ++ ;
            a -- ;
        }
    }
    return 0 ;
}
```
**核心实现思想**：先进行无解特判，然后在循环中根据剩余茶的数量和连续喝同一种茶的次数，优先选择剩余数量多的茶，当达到连续喝的上限时切换茶的种类。

#### PR_CYJ 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,nw,a[5];//m表示k，啊a[1]表示a，a[0]表示b，nw表示当前连续用了几次 
char c='G';
int main()
{
    cin>>n>>m>>a[1]>>a[0];
    if (a[0]<(a[1]+m-1)/m-1||a[1]<(a[0]+m-1)/m-1)
    {
        cout<<"NO"<<endl;
        return 0;
    }
    for(int i=1;i<=n;i++)
        if (nw<m&&a[c%2]>a[!(c%2)])//两种条件必不可少 
        {
            nw++;
            cout<<c;
            a[c%2]--;
        }
        else//换种茶 
        {
            nw=1;
            if (c=='G')
                c='B';
            else
                c='G';
            cout<<c;
            a[c%2]--;
        }
}
```
**核心实现思想**：先判断无解情况，然后在循环中，若连续喝同一种茶次数未达到上限且该种茶剩余数量多，则继续喝该种茶，否则切换茶的种类。

#### OI_AKed_me 的代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ss stable_sort
#define inf INT_MAX
#define re register
#pragma GCC opitimize(3)
using namespace std;
int n,k,a,b,bigger;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k>>a>>b;
    if((a+1<(b+k-1)/k)||(b+1<(a+k-1)/k)){//前面讲的难点1
        cout<<"NO";
        return 0;
    }
    bigger=2;
    while(a||b){
        if(a>b){
            for(int i=1;i<=min(a,k-(bigger==0));i++) cout<<'G';//注意加(bigger==0)，我在这死了两次
            if(b){
                cout<<'B';
                b--;
            }
            a-=min(a,k-(bigger==0));//同理
            bigger=1;
        }else{
            for(int i=1;i<=min(b,k-(bigger==1));i++) cout<<'B';//同理
            if(a){
                cout<<'G';
                a--;
            }
            b-=min(b,k-(bigger==1));//同理
            bigger=0;			
        }
    }
    return 0;
}
```
**核心实现思想**：先判断无解情况，然后在循环中，根据剩余茶的数量，优先选择数量多的茶，同时注意连续喝同一种茶的次数限制，通过 `bigger` 变量处理一些细节。

### 最优关键思路或技巧
- **贪心策略**：每次优先选择剩余数量多的茶，直到达到连续喝的上限或该种茶用完，再切换茶的种类。
- **无解判断**：通过数学关系判断是否无法构造出符合条件的喝茶顺序，如 $a + 1 < \frac{b + k - 1} {k} $ 或 $b + 1 < \frac{a + k - 1} {k} $ 时无解。

### 拓展思路
同类型题可能会有更多种类的茶或更复杂的限制条件，解题时仍可考虑贪心策略，根据不同种类物品的数量和限制条件进行选择。类似算法套路可用于资源分配、任务调度等问题。

### 推荐题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心算法的经典应用，根据不同任务的时间进行排序和分配。
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略每次选择最小的两个果子进行合并。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：利用贪心思想，根据物品的价值和重量选择最优的物品组合。

---
处理用时：54.29秒