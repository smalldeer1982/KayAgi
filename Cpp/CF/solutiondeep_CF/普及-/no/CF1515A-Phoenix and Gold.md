# 题目信息

# Phoenix and Gold

## 题目描述

Phoenix has collected $ n $ pieces of gold, and he wants to weigh them together so he can feel rich. The $ i $ -th piece of gold has weight $ w_i $ . All weights are distinct. He will put his $ n $ pieces of gold on a weight scale, one piece at a time.

The scale has an unusual defect: if the total weight on it is exactly $ x $ , it will explode. Can he put all $ n $ gold pieces onto the scale in some order, without the scale exploding during the process? If so, help him find some possible order.

Formally, rearrange the array $ w $ so that for each $ i $ $ (1 \le i \le n) $ , $ \sum\limits_{j = 1}^{i}w_j \ne x $ .

## 说明/提示

In the first test case, Phoenix puts the gold piece with weight $ 3 $ on the scale first, then the piece with weight $ 2 $ , and finally the piece with weight $ 1 $ . The total weight on the scale is $ 3 $ , then $ 5 $ , then $ 6 $ . The scale does not explode because the total weight on the scale is never $ 2 $ .

In the second test case, the total weight on the scale is $ 8 $ , $ 9 $ , $ 11 $ , $ 14 $ , then $ 18 $ . It is never $ 3 $ .

In the third test case, Phoenix must put the gold piece with weight $ 5 $ on the scale, and the scale will always explode.

## 样例 #1

### 输入

```
3
3 2
3 2 1
5 3
1 2 3 4 8
1 5
5```

### 输出

```
YES
3 2 1
YES
8 1 2 3 4
NO```

# AI分析结果

### 题目内容
# Phoenix and Gold

## 题目描述
Phoenix收集了$n$块金子，他想把它们一起称重，这样他就能感受到富有。第$i$块金子的重量为$w_i$。所有重量都不同。他将把$n$块金子一次一块地放在秤上。
秤有一个不寻常的缺陷：如果秤上的总重量恰好为$x$，它就会爆炸。他能否以某种顺序将所有$n$块金子放在秤上，且在这个过程中秤不会爆炸？如果可以，请帮他找到一种可能的顺序。
形式上，重新排列数组$w$，使得对于每个$i$（$1 \leq i \leq n$），$\sum_{j = 1}^{i}w_j \neq x$。

## 说明/提示
在第一个测试用例中，Phoenix先把重量为$3$的金块放在秤上，然后是重量为$2$的金块，最后是重量为$1$的金块。秤上的总重量依次为$3$、$5$、$6$。秤不会爆炸，因为秤上的总重量永远不会是$2$。
在第二个测试用例中，秤上的总重量依次为$8$、$9$、$11$、$14$、$18$。它永远不会是$3$。
在第三个测试用例中，Phoenix必须把重量为$5$的金块放在秤上，秤总是会爆炸。

## 样例 #1
### 输入
```
3
3 2
3 2 1
5 3
1 2 3 4 8
1 5
5
```
### 输出
```
YES
3 2 1
YES
8 1 2 3 4
NO
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕判断是否存在满足条件的排列以及如何构造该排列展开。多数题解都发现当所有金子重量和等于$x$时无解，其他情况有解。不同点在于构造满足条件排列的方法，有的采用随机化打乱模拟，有的通过特定顺序遍历和交换元素来实现。

### 所选的题解
 - **作者：_easy_ (4星)**
    - **关键亮点**：思路清晰，分两种情况讨论，先判断总和与$x$的关系，对于有解情况通过遍历并交换元素来构造序列。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,x,a[105],sum;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>x;
        sum=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            sum+=a[i];
        }
        if(sum==x){
            cout<<"NO"<<endl;
            continue;
        }
        cout<<"YES"<<endl;
        sum=0;
        for(int i=1;i<=n;i++){
            sum+=a[i];
            if(sum==x){
                swap(a[i+1],a[i]);
                cout<<a[i]<<" "<<a[i+1]<<" ";
                i++;
                sum+=a[i];
            }else{
                cout<<a[i]<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：先计算总和判断是否无解。有解时遍历数组，若前缀和等于$x$，交换当前与下一个元素并输出，否则直接输出当前元素。
 - **作者：feicheng (4星)**
    - **关键亮点**：提出将序列从大到小排序，遍历过程跳过会使前缀和为$x$的数，最后将跳过的数放于数组尾端的构造方法。
    - **重点代码**：
```cpp
inline void solve() {
    v.clear() ;
    memset(vis,0,sizeof vis) ;
    memset(a,0,sizeof a) ;
    cin >> n >> x;
    for(int i = 1;i <= n;++i) cin >> a[i];
    std::sort(a+1,a+1+n,[](const int p,const int q) {return p > q;}) ;
    int sum = 0 ;
    for(int i = 1;i <= n;++i) {
        if(sum > x) break ;
        if(sum + a[i]!= x) {
            sum += a[i] ;
            v.push_back(a[i]) ;
            vis[i] = 1 ;
        }
    }
    sum = 0 ;
    for(int i = 1;i <= n;++i) {
        if(!vis[i]) v.push_back(a[i]) ;
    }
    for(auto it : v) {
        sum += it ;
        if(sum == x) return cout << "NO\n",void() ;
    }
    cout << "YES\n" ;
    for(auto it : v) cout << it << " " ;
    cout << endl ;
}
```
    - **核心实现思想**：排序后遍历，跳过使前缀和为$x$的数，最后整合并检验是否仍存在前缀和为$x$的情况。
 - **作者：pragma_GCC (4星)**
    - **关键亮点**：全面分类讨论总和与$x$的三种大小关系，针对$num > x$ 的情况通过交换元素避免前缀和为$x$。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,w[1001],x;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>x;
        int num=0;
        for(int i=1;i<=n;i++){
            cin>>w[i];
            num+=w[i];
        }
        if(num<x){
            cout<<"YES\n";
            for(int i=1;i<=n;i++){
                cout<<w[i]<<' ';
            }
            cout<<"\n";
        }else if(num==x){
            cout<<"NO\n";
        }else{
            int t=0;
            cout<<"YES\n";
            for(int i=1;i<=n;i++){
                if(w[i]+t==x){
                    swap(w[i],w[n]);
                }
                cout<<w[i]<<' ';
                t+=w[i];
            }
            cout<<'\n';
        }
    }
    return 0;
}
```
    - **核心实现思想**：根据总和与$x$ 的大小关系分别处理，$num > x$ 时遍历数组，若当前元素使前缀和为$x$，则与最后一个元素交换。

### 最优关键思路或技巧
对于此类构造满足特定前缀和条件序列的问题，关键在于先判断无解情况（总和等于目标值），对于有解情况，利用元素的不同，通过排序、遍历过程中的交换等操作来构造满足条件的序列。

### 同类型题或类似算法套路拓展
此类题目通常围绕特定条件下的序列构造。套路一般是先分析无解的边界条件，再针对有解情况，利用给定数据的特性（如本题元素各不相同），通过排序、交换元素等方式构造出符合要求的序列。

### 推荐题目
 - [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)，通过贪心策略构造满足条件的数，与本题构造满足条件序列思路类似。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)，运用贪心思想对序列进行排序构造最优方案，与本题构造思路相关。
 - [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)，利用贪心构造最优合并顺序，和本题构造满足条件排列思路相似。

### 个人心得摘录与总结
无。 

---
处理用时：70.61秒