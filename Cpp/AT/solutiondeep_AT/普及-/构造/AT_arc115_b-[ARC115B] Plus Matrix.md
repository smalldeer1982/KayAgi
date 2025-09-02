# 题目信息

# [ARC115B] Plus Matrix

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc115/tasks/arc115_b

$ N $ 行 $ N $ 列の非負整数を成分とする行列 $ C $ が与えられます。すべての $ (i,j) $ について $ C_{i,j}=A_i+B_j $ を満たすような非負整数列 $ A_1,A_2,\ldots,A_N $ と $ B_1,B_2,\ldots,B_N $ の組が存在するか判定し、存在するなら一つ出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 500 $
- $ 0\ \leq\ C_{i,j}\ \leq\ 10^9 $

### Sample Explanation 1

$ A,B $ は非負整数列であることに注意してください。

## 样例 #1

### 输入

```
3

4 3 5

2 1 3

3 2 4```

### 输出

```
Yes

2 0 1

2 1 3```

## 样例 #2

### 输入

```
3

4 3 5

2 2 3

3 2 4```

### 输出

```
No```

# AI分析结果

### 题目内容中文重写
给定一个 $N$ 行 $N$ 列的、以非负整数为元素的矩阵 $C$。需要判断是否存在满足对于所有的 $(i,j)$ 都有 $C_{i,j}=A_i+B_j$ 的非负整数序列 $A_1,A_2,\ldots,A_N$ 和 $B_1,B_2,\ldots,B_N$，若存在则输出其中一组。

### 综合分析与结论
这些题解的核心思路都是先判断是否存在满足条件的 $A$ 和 $B$ 数组，再在存在的情况下构造出这两个数组。判断的依据主要是利用矩阵 $C$ 的行和列的差分数组的性质，若行或列的差分数组不相同则无解。构造数组时，通常会选取矩阵 $C$ 中的某一行或某一列作为 $B$ 数组，再根据 $C_{i,j}=A_i+B_j$ 求出 $A$ 数组。

### 所选题解
- **作者：KυρωVixen（4星）**
    - **关键亮点**：思路清晰，通过贪心策略先处理矩阵，再检查每行元素是否相同来判断是否有解，代码实现简洁易懂。
    - **核心实现思想**：先把每列减去这一列最小值并记录 $b_j$，随后检查剩下每行的所有元素是否相同，若有不相同的则报告无解，否则对于每个 $i$ 令 $a_i\gets c_{i,1}$。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define rep(i,a,b) for(int i=(int)a;i<=(int)b;i++)
#define endl '\n'
using namespace std;
const int N=505;
int n,c[N][N],a[N],b[N];
int chk(int p){
    rep(i,2,n) if(c[p][i]!=c[p][1]) return -1;
    return c[p][1]; 
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n;
    rep(i,1,n) rep(j,1,n) cin>>c[i][j];
    rep(j,1,n){
        b[j]=INF;
        rep(i,1,n) b[j]=min(b[j],c[i][j]);
        rep(i,1,n) c[i][j]-=b[j];
    } 
    rep(i,1,n){
        int tmp=chk(i);
        if(tmp==-1){
            cout<<"No"<<endl; return 0;
        }
        a[i]=tmp;
    }
    cout<<"Yes"<<endl;
    rep(i,1,n) cout<<a[i]<<" ";
    cout<<endl;
    rep(i,1,n) cout<<b[i]<<" ";
    cout<<endl;
}
```
- **作者：xiongzecheng（4星）**
    - **关键亮点**：详细分析了判断无解和构造数组的过程，考虑了 $A$ 和 $B$ 数组元素非负的情况。
    - **核心实现思想**：先判断矩阵 $C$ 每一行相邻两数的差组成的数列是否全部相同，若不同则无解。然后构造出 $A$ 和 $B$ 数组的初始值，再根据两数组最小值的和判断是否能使所有元素非负。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c[505][505];
vector<int>st,a,b;
int main(){
    scanf("%d",&n);
    for(int j=1;j<=n;j++){
        scanf("%d",&c[1][j]);
        if(j!=1)st.push_back(c[1][j]-c[1][j-1]);
    }
    bool f=true;
    for(int i=2;i<=n;i++)
        for(int j=1;j<=n;j++){
            scanf("%d",&c[i][j]);
            if(j!=1&&c[i][j]-c[i][j-1]!=st[j-2])f=false;
        }
    if(!f){
        printf("No\n");
        return 0;
    }
    for(int i=1;i<=n;i++)a.push_back(c[i][1]);
    for(int i=1;i<=n;i++)b.push_back(c[1][i]-c[1][1]);
    int min1=INT_MAX,min2=INT_MAX;
    for(int i=0;i<a.size();i++){
        min1=min(min1,a[i]);
        min2=min(min2,b[i]);
    }
    if(min1+min2<0){
        printf("No\n");
        return 0;
    }
    printf("Yes\n");
    for(int i=0;i<a.size();i++)
        printf("%d ",a[i]-min1);
    printf("\n");
    for(int i=0;i<b.size();i++)
        printf("%d ",b[i]+min1);
    printf("\n");
    return 0;
}
```
- **作者：Laisira（4星）**
    - **关键亮点**：通过数学推导得出判断依据和数组元素的关系式，使用二分枚举 $A_1$ 的值来满足非负条件。
    - **核心实现思想**：根据矩阵元素的关系推导出判断依据，求出 $A$ 和 $B$ 数组元素的关系式，然后二分枚举 $A_1$ 的值，检查是否能使所有元素非负。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define Maxn 505 
using namespace std;
int C[Maxn][Maxn];
int a[Maxn],b[Maxn];
int res[Maxn],n;
bool check(int x) {
    res[1]=x;
    for(int i=2;i<=n;i++) {
        res[i]=res[i-1]-a[i];
        if(res[i] < 0)return false;
    } return true;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>C[i][j];
    for(int i=2;i<=n;i++)
        for(int j=2;j<=n;j++)
            if(C[i][j]!=C[i-1][j]+C[i][j-1]-C[i-1][j-1])
                return cout<<"No",0;
    for(int i=2;i<=n;i++)
        a[i]=C[i-1][1]-C[i][1];
    for(int i=2;i<=n;i++)
        b[i]=C[1][i-1]-C[1][i];
    int l=0,r=C[1][1],mid,ans=-1;
    while(l <= r) {
        mid=(l+r)>>1;
        if(!check(mid))l=mid+1;
        else r=mid-1,ans=mid;
    } if(ans == -1)return cout<<"No",0;
    a[1]=ans; b[1]=C[1][1]-ans;
    for(int i=2;i<=n;i++) {
        a[i]=a[i-1]-a[i],b[i]=b[i-1]-b[i];
        if(b[i] < 0)return cout<<"No",0;
    } cout<<"Yes\n";
    for(int i=1;i<=n;i++)
        cout<<a[i]<<" ";
    cout<<"\n";
    for(int i=1;i<=n;i++)
        cout<<b[i]<<" ";
    return 0;
}
```

### 最优关键思路或技巧
- **差分数组的运用**：通过计算矩阵 $C$ 的行和列的差分数组来判断是否存在满足条件的 $A$ 和 $B$ 数组，若差分数组不同则无解。
- **贪心策略**：如将每列的最小值作为 $B_j$，可以简化问题的处理。
- **数学推导**：通过对矩阵元素关系的推导，得出判断依据和数组元素的关系式，有助于问题的解决。

### 可拓展之处
同类型题可以是判断是否存在其他形式的数组满足矩阵元素的组合关系，例如 $C_{i,j}=A_i\times B_j$ 等。类似算法套路可以是先通过数学推导找出判断条件，再根据条件进行构造或求解。

### 推荐洛谷题目
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)
- P1428 [小鱼比可爱](https://www.luogu.com.cn/problem/P1428)

### 个人心得摘录与总结
- **作者：czh___**：提到题目隐含了 $A,B$ 的每个元素都为非负数这个条件，导致自己错了好几次，提醒我们做题时要仔细读题，注意题目中的隐含条件。
- **作者：lihongqian__int128**：表示没看见 $A,B$ 中的元素应 $\ge 0$，卡了好一会才调出来，同样强调了读题的重要性。

---
处理用时：50.86秒