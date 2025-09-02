# 题目信息

# Almost Sorted

## 题目描述

Seiji Maki doesn't only like to observe relationships being unfolded, he also likes to observe sequences of numbers, especially permutations. Today, he has his eyes on almost sorted permutations.

A permutation $ a_1, a_2, \dots, a_n $ of $ 1, 2, \dots, n $ is said to be almost sorted if the condition $ a_{i + 1} \ge a_i - 1 $ holds for all $ i $ between $ 1 $ and $ n - 1 $ inclusive.

Maki is considering the list of all almost sorted permutations of $ 1, 2, \dots, n $ , given in lexicographical order, and he wants to find the $ k $ -th permutation in this list. Can you help him to find such permutation?

Permutation $ p $ is lexicographically smaller than a permutation $ q $ if and only if the following holds:

- in the first position where $ p $ and $ q $ differ, the permutation $ p $ has a smaller element than the corresponding element in $ q $ .

## 说明/提示

For the first and second test, the list of almost sorted permutations with $ n = 1 $ is $ \{[1]\} $ .

For the third and fifth test, the list of almost sorted permutations with $ n = 3 $ is $ \{[1, 2, 3], [1, 3, 2], [2, 1, 3], [3, 2, 1]\} $ .

## 样例 #1

### 输入

```
5
1 1
1 2
3 3
6 5
3 4```

### 输出

```
1 
-1
2 1 3 
1 2 4 3 5 6 
3 2 1```

# AI分析结果

### 题目内容（中文重写）
# 几乎有序排列

## 题目描述
牧木诚司（Seiji Maki）不仅喜欢观察人际关系的发展，还喜欢观察数字序列，尤其是排列。今天，他关注的是几乎有序的排列。

一个由 $1, 2, \dots, n$ 组成的排列 $a_1, a_2, \dots, a_n$ 被称为几乎有序的，当且仅当对于所有介于 $1$ 到 $n - 1$（包含两端）的 $i$，都满足条件 $a_{i + 1} \ge a_i - 1$。

牧木正在考虑由 $1, 2, \dots, n$ 组成的所有几乎有序排列的列表，这些排列按字典序排列，他想找到这个列表中的第 $k$ 个排列。你能帮他找到这样的排列吗？

排列 $p$ 在字典序上小于排列 $q$，当且仅当满足以下条件：
- 在 $p$ 和 $q$ 不同的第一个位置上，排列 $p$ 中的元素小于 $q$ 中对应的元素。

## 说明/提示
对于第一和第二个测试，$n = 1$ 时的几乎有序排列列表是 $\{[1]\}$。
对于第三和第五个测试，$n = 3$ 时的几乎有序排列列表是 $\{[1, 2, 3], [1, 3, 2], [2, 1, 3], [3, 2, 1]\}$。

## 样例 #1
### 输入
```
5
1 1
1 2
3 3
6 5
3 4
```
### 输出
```
1 
-1
2 1 3 
1 2 4 3 5 6 
3 2 1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先分析出几乎有序排列的性质，得出其排列个数为 $2^{n - 1}$，再根据字典序的特点来找出第 $k$ 小的排列。不同题解在具体实现上有所差异，有的通过位运算，有的使用递归、二分等方法。

### 所选题解
- **Alex_Wei（5星）**
    - **关键亮点**：思路清晰，通过分析几乎有序排列与切割方案的一一对应关系，利用位运算巧妙地解决了字典序问题，代码简洁高效。
- **Eibon（4星）**
    - **关键亮点**：对 Alex_Wei 的代码进行了详细解释，有助于理解位运算在本题中的应用，代码逻辑清晰。
- **Little09（4星）**
    - **关键亮点**：通过递推得出排列个数，使用递归的方式依次填入数字，代码复杂度为线性，思路简洁明了。

### 重点代码
#### Alex_Wei 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n,k;
void solve(){
    cin>>n>>k,k--;
    if(n<62&&k>>n-1)return puts("-1"),void();
    for(int i=1,p=1;i<=n;i=p+1,p=i){
        while(p<n&&n-p<=62&&(k>>n-p-1)&1)p++;
        for(int j=p;j>=i;j--)cout<<j<<" ";
    } cout<<endl;
}

int main(){
    int t=1;
    cin>>t;
    while(t--)solve();
    return 0;
}
```
**核心实现思想**：先判断 $k$ 是否超出排列个数范围，然后根据 $k$ 的二进制表示确定切割位置，将对应区间翻转输出。

#### Eibon 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int T,n,k,ans,cnt;
int a[maxn];
signed main()
{
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld",&n,&k);
        if((k-1)>>(n-1)&&n<=62){//2^(n-1)>=k
            printf("-1\n");
            continue;
        }
        k--;
        for(int i=1,now=1;i<=n;i=now+1,now=i){
            while(now<n&&n-now<=62&&(k>>(n-(now+1)))&1){
                now++;
            }
            for(int j=now;j>=i;j--){
                printf("%lld ",j);
            }
        }
        printf("\n");
    }
    return 0;
}
```
**核心实现思想**：与 Alex_Wei 的思路一致，对 $k$ 进行处理后，根据二进制位确定区间并倒序输出。

#### Little09 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(x) memset(x,0,sizeof(x))
const int N=200001;
int n,T;
ll k; 
ll f[N];

inline ll F(ll x)
{
    if (x>61) x=61;
    return f[x];
}

void dfs(int x,ll y)
{
    if (x==n) return;
    ll res=0;
    for (int i=x+1;i<=n;i++)
    {
        if (res+F(n-i)>=y)
        {
            for (int j=i;j>=x+1;j--) cout << j << " ";
            dfs(i,y-res);
            return;
        }
        res+=F(n-i);
    }
}

void work()
{
    cin >> n >> k;
    if (n<=61&&k>f[n])
    {
        puts("-1");
        return;
    }
    dfs(0,k);
    puts("");
    return;
}

int main()
{
    f[0]=f[1]=1ll;
    for (int i=2;i<=61;i++) f[i]=f[i-1]*2ll;
    T=read();
    while (T--)
    {
        work();
    }
    return 0;
}
```
**核心实现思想**：先递推计算出排列个数，然后通过递归依次填入数字，根据剩余字典序选择合适的数字。

### 关键思路或技巧
- 分析出几乎有序排列与切割方案的一一对应关系，利用二进制表示来处理字典序问题。
- 通过递推得出排列个数，使用递归或迭代的方式依次确定每个位置的数字。

### 拓展思路
同类型题可能会改变排列的条件，或者要求计算满足条件的排列个数等。类似算法套路可以用于处理一些与排列组合相关的问题，通过分析排列的性质，找到与其他数学概念（如二进制、递推等）的联系来解决问题。

### 推荐题目
- [P1088 火星人](https://www.luogu.com.cn/problem/P1088)
- [P1338 末日的传说](https://www.luogu.com.cn/problem/P1338)
- [P2708 硬币翻转](https://www.luogu.com.cn/problem/P2708)

### 个人心得摘录与总结
- **TLE_Automat**：表示一开始找不到突破口，后来看了官方题解才明白做法，强调了深入挖掘性质的重要性。总结：遇到难题时要多从题目条件中挖掘性质，不能浅尝辄止。
- **Miko35**：提到自己比较蠢，没发现 $n>60$ 必然有解的性质，但还是二分过掉了题。总结：即使没有发现最优性质，也可以尝试用其他方法解决问题。 

---
处理用时：57.40秒