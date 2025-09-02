# 题目信息

# GCD Table

## 题目描述

有一个长度为$n$的数列$a$，它可以生成一个$n*n$的数表，数表的第$i$行第$j$列存放的数字是$\gcd(a[i],a[j])$ （即$a[i]$和$a[j]$的最大公因数）。



![一个例子：](https://cdn.luogu.com.cn/upload/image_hosting/zv3hmpih.png?x-oss-process=image/resize,m_lfit,h_170,w_225)



举个例子，上面那个表，就是由数列$a[]=\{4,3,6,2\}$生成的。



现在我们要做这样一件事情：将这个数表中的这$n*n$ 个数打乱，得到一个长度为$n*n$的序列(可参考样例1)。在已知这个序列的情况下，请还原出数列$a$。

## 样例 #1

### 输入

```
4
2 1 2 3 4 3 2 6 1 1 2 2 1 2 3 2
```

### 输出

```
4 3 6 2```

## 样例 #2

### 输入

```
1
42
```

### 输出

```
42 ```

## 样例 #3

### 输入

```
2
1 1 1 1
```

### 输出

```
1 1 ```

# AI分析结果

### 题目内容
# GCD表

## 题目描述
有一个长度为$n$的数列$a$，它可以生成一个$n*n$的数表，数表的第$i$行第$j$列存放的数字是$\gcd(a[i],a[j])$ （即$a[i]$和$a[j]$的最大公因数）。

![一个例子：](https://cdn.luogu.com.cn/upload/image_hosting/zv3hmpih.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

举个例子，上面那个表，就是由数列$a[]=\{4,3,6,2\}$生成的。

现在我们要做这样一件事情：将这个数表中的这$n*n$ 个数打乱，得到一个长度为$n*n$的序列(可参考样例1)。在已知这个序列的情况下，请还原出数列$a$。

## 样例 #1
### 输入
```
4
2 1 2 3 4 3 2 6 1 1 2 2 1 2 3 2
```
### 输出
```
4 3 6 2```

## 样例 #2
### 输入
```
1
42
```
### 输出
```
42 ```

## 样例 #3
### 输入
```
2
1 1 1 1
```
### 输出
```
1 1 ```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是基于“$\gcd(a,b) \leq \min(a,b)$”这一性质，得出数表中最大的数一定在原数列中的结论。进而每次从数表中选取当前最大值作为原数列中的数，然后将该数与已选数的最大公因数从数表中剔除（由于数表对称，每个最大公因数要删两个），重复此过程直至还原出原数列。各题解在具体实现上，主要差异在于数据结构的选择，有的使用`map`统计数表中每个数的出现次数，有的使用`multiset`。在思路清晰度和代码可读性上，部分题解通过详细的注释和较为规范的代码结构表现较好。

### 所选的题解
- **作者：Mine_King (5星)**
    - **关键亮点**：思路阐述详细，对最大数、次大值为何在原数列中给出了严谨证明，代码实现简洁明了，使用`map`解决值域大的问题。
    - **重点代码**：
```cpp
#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,cnt,ans,a[505],num[250005];
map<int,int>mp;
int gcd(int _a,int _b){return _b==0?_a:gcd(_b,_a%_b);}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*n;i++)
    {
        int x;
        scanf("%d",&x);
        if(!mp[x]) num[++cnt]=x;
        mp[x]++;
    }
    sort(num+1,num+cnt+1);
    for(int i=cnt;i>=1&&ans<n;)
    {
        while(!mp[num[i]]) i--;
        a[++ans]=num[i];//把数表中的最大值记入答案
        mp[num[i]]--;//删掉它（因为它实际上是gcd(num[i],num[i])。
        for(int j=1;j<ans;j++) mp[gcd(num[i],a[j])]-=2;//删掉它与其他数的gcd
    }
    for(int i=1;i<=ans;i++) printf("%d ",a[i]);
    return 0;
}
```
    - **核心实现思想**：先读入数据并用`map`统计每个数的出现次数，同时记录不同的数到`num`数组。对`num`数组排序后，从大到小遍历，每次取出当前最大数加入答案数组，同时更新`map`中该数与已选数的最大公因数的计数。
- **作者：Guess00 (4星)**
    - **关键亮点**：思路清晰，对核心操作步骤进行了编号说明，代码中使用快读快输模板，并且提到了去重与不去重两种实现方式。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=250005;
int n,i,j,x,cnt,num,a[MAXN],ans[MAXN];
map<int,int> m;//桶 
inline void read(int &x)  //快读 
{
    short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
        if(c=='-')
            negative=-1;
        c=getchar();
    }
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)  //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
inline int gcd(int a,int b){return (!a)?b:gcd(b%a,a);} 
inline bool cmp(int a,int b){return a>b;}
signed main(void)
{
    read(n);
    for (i=1;i<=n*n;i++)
    {
        read(x);
        if (!m[x])  //去重 
            a[++cnt]=x;
        m[x]++;
    }
    sort(a+1,a+cnt+1,cmp);//排序 
    for (i=1;i<=cnt && num<n;) //因为去重了,所以这里千万不要写i++ 
    {
        while (!m[a[i]])  //如果这个数已经被删完了 
            i++;
        ans[++num]=a[i];  //将最大的数加入序列 
        m[a[i]]--; 
        for (j=1;j<num;j++)
            m[gcd(ans[j],a[i])]-=2;  //删去最大数和序列中其他数的gcd(2个) 
    }
    for (i=1;i<=num;i++)  //输出 
        print(ans[i]),putchar(' ');
    return 0;
}
```
    - **核心实现思想**：通过快读读入数据，用`map`统计数并去重，将不同的数存入`a`数组。对`a`数组从大到小排序，遍历数组，每次将当前最大数加入答案数组，同时更新`map`中该数与已选数的最大公因数的计数，最后通过快输输出答案。
- **作者：andyli (4星)**
    - **关键亮点**：简洁地阐述题意和思路，使用`multiset`实现，时间复杂度分析清晰。
    - **重点代码**：
```cpp
int main()
{
    int n;
    io.read(n);
    multiset<int> s;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int x;
            io.read(x);
            s.insert(x);
        }
    vector<int> ans;
    while (!s.empty()) {
        int p = *s.rbegin();
        auto it = s.end();
        it--;
        s.erase(it);
        for (auto q : ans) {
            int t = gcd(p, q);
            auto it = s.upper_bound(t), it2 = it;
            it2--, it2--;
            s.erase(it2, it);
        }
        ans.push_back(p);
    }
    for (auto x : ans)
        io.write(x, " ");
    writeln();
    return 0;
}
```
    - **核心实现思想**：使用`multiset`存储数表中的数，每次取出`multiset`中的最大数加入答案数组，然后从`multiset`中删除该数与已选数的最大公因数，重复操作直至`multiset`为空。

### 最优关键思路或技巧
利用“$\gcd(a,b) \leq \min(a,b)$”这一数学性质确定原数列元素，通过合适的数据结构（如`map`统计数的出现次数、`multiset`方便查找和删除最大数）实现对数据的高效处理。

### 可拓展之处
同类型题通常围绕数论中的最大公因数、最小公倍数等概念展开，类似算法套路是基于数论性质对给定数据进行分析和处理，通过逐步筛选或构造的方式解决问题。

### 推荐洛谷题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：该题需要根据最大公约数和最小公倍数的关系进行枚举和判断，与本题都涉及数论中最大公因数的概念。
- [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)：考察高精度数的最大公因数计算，进一步加深对最大公因数计算的理解与应用。
- [P1572 计算分数的最大公约数和最小公倍数](https://www.luogu.com.cn/problem/P1572)：将最大公约数和最小公倍数的计算拓展到分数领域，锻炼对数论知识的灵活运用能力。

### 个人心得
无。

---
处理用时：93.52秒