# 题目信息

# Maximum AND

## 题目描述

给出两个长度为 $n$ 的数组 $a,b$ ，规定 $f(a,b)$ 表示以下操作：

1. 创建一个长度为 $n$ 的 $c$ 数组，满足 $c_i=a_i \oplus b_i$ （此处的 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin)）。
2. 则 $f(a, b) = c_1\space\& c_2\space\& \cdots \& c_n$。

你可以将 $b$ 数组进行任意的排列（包括保留原始情况），试求出最大的 $f(a,b)$ 。

## 样例 #1

### 输入

```
3
5
1 0 0 3 3
2 3 2 1 0
3
1 1 1
0 0 3
8
0 1 2 3 4 5 6 7
7 6 5 4 3 2 1 0```

### 输出

```
2
0
7```

# AI分析结果

### 题目内容
# 最大与值

## 题目描述
给出两个长度为 $n$ 的数组 $a,b$ ，规定 $f(a,b)$ 表示以下操作：
1. 创建一个长度为 $n$ 的 $c$ 数组，满足 $c_i=a_i \oplus b_i$ （此处的 $\oplus$ 表示[按位异或](https://baike.baidu.com/item/%E5%BC%82%E6%88%96/10993677?fr=aladdin)）。
2. 则 $f(a, b) = c_1\space\& c_2\space\& \cdots \& c_n$。

你可以将 $b$ 数组进行任意的排列（包括保留原始情况），试求出最大的 $f(a,b)$ 。

## 样例 #1
### 输入
```
3
5
1 0 0 3 3
2 3 2 1 0
3
1 1 1
0 0 3
8
0 1 2 3 4 5 6 7
7 6 5 4 3 2 1 0
```
### 输出
```
2
0
7
```

### 综合分析与结论
这些题解的核心思路都是按位贪心，从二进制高位到低位枚举，判断每一位能否为1来构造最大的 $f(a,b)$。
- **思路**：若答案某一位为1，需满足所有 $a_i$ 与 $b_i$ 在该位取值不同。不同题解在判断该条件及后续处理方式上有所差异。
- **算法要点**：主要通过排序、集合分裂、桶计数、map维护等方式实现按位贪心的判断与处理。
- **解决难点**：难点在于保证每一位判断时不影响前面已确定的位，同时要高效地进行判断和数据处理。比如处理当前位时如何确保与前面位的决策兼容，以及如何在 $O(n\log n)$ 复杂度内完成判断。

### 所选的题解
- **作者：jrxxx (5星)**
    - **关键亮点**：思路清晰简洁，利用sort排序巧妙简化判断过程和后续处理。通过排序后按位遍历判断能否取1，若能则贡献答案并利用排序的有序性直接进入子集合处理；若不能则推平该位重新排序消除影响。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7,V=30;
int a[N],b[N];
int main()
{
    ios::sync_with_stdio(0),cin.tie(0);
    int T,n,i,j,ans;
    for(cin>>T;T--;)
    {
        cin>>n;
        for(i=1;i<=n;++i) cin>>a[i];
        for(i=1;i<=n;++i) cin>>b[i];
        sort(a+1,a+n+1,less<int>());
        sort(b+1,b+n+1,greater<int>());
        ans=0;
        for(i=V;~i;--i)
        {
            for(j=1;j<=n;++j)
                if((a[j]&(1<<i))==(b[j]&(1<<i)))
                    break;
            if(j>n) ans|=1<<i;
            else 
            {
                for(j=1;j<=n;++j)
                    a[j]|=(1<<i),b[j]|=(1<<i);
                sort(a+1,a+n+1,less<int>());
                sort(b+1,b+n+1,greater<int>());
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```
    - **核心实现思想**：先对 $a$ 升序、$b$ 降序排序，从高位到低位枚举每一位，遍历判断 $a,b$ 对应位是否都不同，若都不同则该位可贡献答案；否则将该位置为1后重新排序，继续下一位判断。
- **作者：Ginger_he (4星)**
    - **关键亮点**：通过vector和sort来判断前 $j$ 位是否满足条件，代码简洁明了。利用check函数，将 $a,b$ 数组对应元素与当前考虑的掩码进行与操作后排序比较，判断是否能使当前位为1。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100005
int t,n,a[N],b[N],ans;
bool check(int x)
{
    vector<int> u,v;
    for(int i=1;i<=n;i++)
    {
        u.push_back(a[i]&x);
        v.push_back((b[i]&x)^x);
    }
    sort(u.begin(),u.end());
    sort(v.begin(),v.end());
    return u==v;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        for(int i=29;i>=0;i--)
        {
            if(check(ans|(1<<i)))
                ans|=(1<<i);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：定义check函数，将 $a$ 数组元素与掩码与操作，$b$ 数组元素先与掩码与操作再异或掩码，然后排序比较两者是否相等，相等则说明当前位可使答案为1。主函数中从高位到低位枚举，若check通过则更新答案。
- **作者：苏联小渣 (4星)**
    - **关键亮点**：详细阐述了按位贪心的原理和集合分裂的过程，便于理解。通过创建集合存储 $a,b$ 中的数，从高位往低位贪心，判断集合是否合法（即满足 $a$ 中1的个数等于 $b$ 中0的个数，$a$ 中0的个数等于 $b$ 中1的个数），合法则分裂集合并更新答案。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, s1, s2, siz, sizz, pd, ans, a[100010], b[100010];
vector <int> d[100010], p[100010], dd[100010], pp[100010];
signed main(){
    scanf ("%lld", &t);
    while (t --){
        for (int i=1; i<=siz; i++) d[i].clear(), p[i].clear();
        siz = 1; ans = 0;
        scanf ("%lld", &n);
        for (int i=1; i<=n; i++){
            scanf ("%lld", &a[i]);
            d[1].push_back(i);
        }
        for (int i=1; i<=n; i++){
            scanf ("%lld", &b[i]);
            p[1].push_back(i);
        }
        for (int i=30; i>=0; i--){
            pd = 1;
            for (int j=1; j<=siz; j++){
                s1 = s2 = 0;
                for (int k=0; k<d[j].size(); k++){
                    int x = a[d[j][k]];
                    if ((x >> i) & 1) s1 ++;
                    int y = b[p[j][k]];
                    if ((y >> i) & 1) s2 ++;
                }
                if (s1 + s2!= d[j].size()){
                    pd = 0;
                    break;
                }
            }
            if (pd){
                for (int j=1; j<=siz; j++){
                    for (int k=0; k<d[j].size(); k++) dd[j].push_back(d[j][k]), pp[j].push_back(p[j][k]);
                }
                for (int j=1; j<=siz; j++) d[j].clear(), p[j].clear();
                sizz = 0;
                ans += (1 << i);
                for (int j=1; j<=siz; j++){
                    sizz ++;
                    for (int k=0; k<dd[j].size(); k++){
                        int x = a[dd[j][k]];
                        int y = b[pp[j][k]];
                        if ((x >> i) & 1) d[sizz].push_back(dd[j][k]);
                        if (!((y >> i) & 1)) p[sizz].push_back(pp[j][k]);
                    }
                    if (d[sizz].size() == 0) sizz --;
                    sizz ++;
                    for (int k=0; k<pp[j].size(); k++){
                        int x = a[dd[j][k]];
                        if (!((x >> i) & 1)) d[sizz].push_back(dd[j][k]);
                        int y = b[pp[j][k]];
                        if ((y >> i) & 1) p[sizz].push_back(pp[j][k]);
                    }
                    if (d[sizz].size() == 0) sizz --;
                }
                for (int j=1; j<=siz; j++){
                    dd[j].clear(), pp[j].clear();
                }
                siz = sizz;
            }
        }
        printf ("%lld\n", ans);
    }
    return 0;
}
```
    - **核心实现思想**：初始化一个集合存储所有数，从高位到低位枚举，对每个集合判断是否合法，合法则分裂集合为两个新集合（分别存储 $a$ 中1与 $b$ 中0、$a$ 中0与 $b$ 中1的组合），同时更新答案和集合状态。

### 最优关键思路或技巧
按位贪心是解决此类问题的核心思想。jrxxx通过巧妙排序简化判断和后续处理过程，是较为高效和简洁的实现方式。在处理位运算相关的最大最小值问题时，从高位到低位按位贪心，同时结合合适的数据结构操作（如排序）来优化判断过程是关键技巧。

### 同类型题或类似算法套路
同类型题通常围绕位运算和贪心策略展开，类似套路包括先分析位运算性质确定贪心方向，再通过排序、分组、计数等方式实现贪心判断和决策。例如对于一些需要构造满足特定位运算条件的数组或序列问题，都可以尝试从位的角度出发，按位贪心求解。

### 洛谷相似题目
- [P1879 [USACO06NOV]玉米田Corn Fields](https://www.luogu.com.cn/problem/P1879)：涉及状态压缩和按位处理，通过二进制表示状态进行动态规划，与本题按位处理思路类似。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：虽然主要是背包问题，但可以通过二进制优化实现按位贪心选择，与本题按位决策思想有相通之处。
- [P2196 挖地雷](https://www.luogu.com.cn/problem/P2196)：在搜索过程中可以结合按位操作优化判断条件，与本题按位判断可行性的思路类似。

### 个人心得摘录与总结
- **苏联小渣**：提到本题与[ARC 146 B](https://atcoder.jp/contests/arc146/tasks/arc146_b)做法相似，通过按位贪心，从高位到低位考虑每一位能否为1，详细阐述了集合分裂的原理和过程，帮助理解按位贪心在这类问题中的应用。总结了按位贪心的可行性证明，即高位优先选择最优策略，因为低位组合无法超过高位选择的贡献。同时提到实现中vector清空以及集合分裂后空集合处理的注意点。 

---
处理用时：55.12秒