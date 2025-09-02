# 题目信息

# Anti-Fibonacci Permutation

## 题目描述

Let's call a permutation $ p $ of length $ n $ anti-Fibonacci if the condition $ p_{i-2} + p_{i-1} \ne p_i $ holds for all $ i $ ( $ 3 \le i \le n $ ). Recall that the permutation is the array of length $ n $ which contains each integer from $ 1 $ to $ n $ exactly once.

Your task is for a given number $ n $ print $ n $ distinct anti-Fibonacci permutations of length $ n $ .

## 样例 #1

### 输入

```
2
4
3```

### 输出

```
4 1 3 2
1 2 4 3
3 4 1 2
2 4 1 3
3 2 1
1 3 2
3 1 2```

# AI分析结果

### 题目内容
# 反斐波那契排列

## 题目描述
我们称长度为 $n$ 的排列 $p$ 为反斐波那契排列，如果对于所有 $i$（$3 \leq i \leq n$），都满足条件 $p_{i - 2} + p_{i - 1} \neq p_i$ 。回忆一下，排列是一个长度为 $n$ 的数组，其中包含从 $1$ 到 $n$ 的每个整数恰好一次。

你的任务是对于给定的数字 $n$，输出 $n$ 个不同的长度为 $n$ 的反斐波那契排列。

## 样例 #1
### 输入
```
2
4
3
```
### 输出
```
4 1 3 2
1 2 4 3
3 4 1 2
2 4 1 3
3 2 1
1 3 2
3 1 2
```
### 算法分类
构造

### 综合分析与结论
这些题解主要围绕如何构造出满足反斐波那契排列条件的 $n$ 个序列展开。部分题解利用深搜（DFS），在搜索过程中通过约束条件 $p_{i - 2} + p_{i - 1} \neq p_i$ 来生成排列；多数题解则是基于数学分析，利用反斐波那契排列的特性直接构造。如发现倒序排列一定是反斐波那契排列，在此基础上通过移动特定数字（如将 $1$ 依次左移或右移，或者将最大数 $n$ 移动等）构造出其余 $n - 1$ 个排列。

### 所选的题解
- **作者：沉石鱼惊旋（5星）**
  - **关键亮点**：思路清晰简洁，利用降序数列的特性，每次把最后一个数往前挪来构造反斐波那契数列，代码实现简单高效。
  - **重点代码**：
```cpp
void solve()
{
    int n;
    cin>>n;
    int f=n;
    int a[n+1];
    for(int i=1;i<=n;i++)a[i]=n-i+1;
    for(int nn=0;nn<n;nn++)
    {
        for(int i=1;i<=n;i++)cout<<a[i]<<" ";
        cout<<endl;
        swap(a[f],a[f-1]);
        f--;
    }
}
```
  - **核心思想**：先创建降序数组，然后通过不断交换数组中特定位置（每次把当前最小位置的数往前挪）的元素，生成 $n$ 个不同的反斐波那契排列。

- **作者：_Fatalis_（5星）**
  - **关键亮点**：不仅给出了常规的DFS解法，还深入进行数学分析，证明了逆序排列及其相邻数字对调后的排列均为反斐波那契排列，从而实现了 $O(n)$ 的高效构造算法。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int j=n;j>=1;j--) printf("%d ",j);puts("");
        for(int i=n;i>=2;i--)
        {
            for(int j=n;j>=1;j--)
            {
                if(j==i) printf("%d %d ",j-1,j),j--;
                else printf("%d ",j);
            }
            puts("");
        }
    }
    return 0;
}
```
  - **核心思想**：先输出逆序排列，再通过循环，每次交换相邻两个数（特定位置）来构造其余 $n - 1$ 个反斐波那契排列。

- **作者：pandaSTT（4星）**
  - **关键亮点**：先给出一种直观的构造思路，即将大数字移至小数前面，再针对奇数 $n$ 的特殊情况进行分析和处理，通过检查和特判保证生成的排列满足条件。
  - **重点代码**：
```cpp
bool check(){
    for(int i=3;i<=n;i++){
        if(ans[i]==ans[i-1]+ans[i-2]){
            return false;
        }
    }
    return true;
}
signed main(){
    cin>>t;
    while(t--){
        memset(ans,0,sizeof ans);
        now=2;
        cin>>n;
        if(n==1){
            cout<<1<<endl;
        }
        else if(n%2==1){
            for(int i=n;i>=1;i--){
                ans[n-i+1]=i;
            }
            for(int i=1;i<=n;i++){
                if(check()==true){
                    for(int j=1;j<=n;j++){
                        cout<<ans[j]<<" ";
                    }
                    cout<<endl;
                }
                swap(ans[now],ans[now-1]);
                now++;
            }
            for(int i=n;i>=3;i--){
                cout<<i<<" ";
            }
            cout<<1<<" "<<2<<endl;
        }
        else{
            for(int i=n;i>=1;i--){
                ans[n-i+1]=i;
            }
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    cout<<ans[j]<<" ";
                }
                swap(ans[now],ans[now-1]);
                now++;
                cout<<endl;
            }
        }
    }
    return 0;
}
```
  - **核心思想**：先构造降序排列，然后通过交换相邻元素生成新排列，对奇数 $n$ 的情况，通过 `check` 函数检查是否满足反斐波那契条件，不满足则不输出，最后针对奇数 $n$ 补充一个特殊的排列（交换最后 $1$ 与 $2$ 的位置）。

### 最优关键思路或技巧
利用反斐波那契排列的特性，如倒序排列一定满足条件，在此基础上通过对特定数字（如最小数 $1$ 或最大数 $n$）的位置调整来构造出其余所需排列，这种基于特性的构造方法避免了复杂的搜索过程，大大提高了效率。

### 可拓展之处
此类构造题常见套路是先寻找满足条件的简单形式（如本题的倒序排列），再在此基础上通过合理变换构造出所有解。类似题目通常需要深入分析题目条件背后的数学性质或规律，利用这些性质进行高效构造。

### 洛谷相似题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举和组合的方式解决问题，与本题部分通过特定规则构造序列的思路类似。
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：考察对排列组合的理解与实现，与本题构造特定排列的要求有相似之处。
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：同样是构造满足特定条件的排列，需要利用回溯等方法，与本题在构造思路和实现技巧上有一定关联。 

---
处理用时：53.84秒