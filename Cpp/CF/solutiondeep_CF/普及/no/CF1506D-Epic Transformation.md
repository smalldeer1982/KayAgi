# 题目信息

# Epic Transformation

## 题目描述

You are given an array $ a $ of length $ n $ consisting of integers. You can apply the following operation, consisting of several steps, on the array $ a $ zero or more times:

- you select two different numbers in the array $ a_i $ and $ a_j $ ;
- you remove $ i $ -th and $ j $ -th elements from the array.

For example, if $ n=6 $ and $ a=[1, 6, 1, 1, 4, 4] $ , then you can perform the following sequence of operations:

- select $ i=1, j=5 $ . The array $ a $ becomes equal to $ [6, 1, 1, 4] $ ;
- select $ i=1, j=2 $ . The array $ a $ becomes equal to $ [1, 4] $ .

What can be the minimum size of the array after applying some sequence of operations to it?

## 样例 #1

### 输入

```
5
6
1 6 1 1 4 4
2
1 2
2
1 1
5
4 5 4 5 4
6
2 3 2 1 3 1```

### 输出

```
0
0
2
1
0```

# AI分析结果

### 题目翻译

给定一个长度为 $n$ 的整数数组 $a$，你可以对数组进行以下操作零次或多次：

- 选择数组中两个不同的元素 $a_i$ 和 $a_j$；
- 从数组中移除第 $i$ 和第 $j$ 个元素。

例如，如果 $n=6$ 且 $a=[1, 6, 1, 1, 4, 4]$，那么你可以执行以下操作序列：

- 选择 $i=1, j=5$，数组 $a$ 变为 $[6, 1, 1, 4]$；
- 选择 $i=1, j=2$，数组 $a$ 变为 $[1, 4]$。

问：在对数组进行若干次操作后，数组的最小可能长度是多少？

### 样例 #1

#### 输入

```
5
6
1 6 1 1 4 4
2
1 2
2
1 1
5
4 5 4 5 4
6
2 3 2 1 3 1
```

#### 输出

```
0
0
2
1
0
```

### 算法分类
贪心

### 题解分析与结论

本题的核心思想是通过贪心策略，尽可能多地删除数组中的不同元素，最终得到数组的最小可能长度。主要思路是通过统计每个元素的出现次数，并根据出现次数最多的元素来决定最终剩余的数组长度。

#### 关键思路与技巧
1. **贪心策略**：优先删除出现次数最多的元素，以减少最终剩余的元素数量。
2. **统计元素出现次数**：使用 `map` 或排序后的数组来统计每个元素的出现次数。
3. **数学推导**：通过数学公式计算最终剩余的元素数量，公式为 `max(2 * cnt - n, n % 2)`，其中 `cnt` 是出现次数最多的元素的出现次数。

#### 最优题解
以下是评分较高的题解：

### 题解1：作者：Gokix (赞：6)

#### 星级：5星
#### 关键亮点：
- 使用栈算法来高效找到出现次数最多的元素。
- 通过数学推导得出最终剩余的元素数量。
- 代码清晰，逻辑严谨。

#### 核心代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack> 
using namespace std;
long long t,n,a[200010],cnt,ans;
stack <long long> s;

void init(){
    memset(a,0,sizeof(a));
    cnt=ans=0;
    while(!s.empty()) s.pop();
}

int main()
{
    long long i,j,u,v;
    cin>>t;
    while(t--){
        init();
        cin>>n;
        for(i=1;i<=n;i++){
            cin>>a[i];
        }
        for(i=1;i<=n;i++){
            if(s.empty()) s.push(a[i]);
            else{
                u=s.top();
                if(u!=a[i]) s.pop();
                else s.push(a[i]);
            }
        }
        if(s.empty()){
            if(n&1) cout<<1<<endl;
            else cout<<0<<endl;
            continue;
        }
        u=s.top();
        for(i=1;i<=n;i++){
            if(a[i]==u) cnt++;
        }
        if(cnt<=n/2){
            if(n&1) cout<<1<<endl;
            else cout<<0<<endl;
        }
        else cout<<n-(n-cnt)*2<<endl;
    }
    return 0;
}
```

### 题解2：作者：moqizhu2005 (赞：4)

#### 星级：4星
#### 关键亮点：
- 使用排序和统计方法来找到出现次数最多的元素。
- 通过数学推导得出最终剩余的元素数量。
- 代码简洁，易于理解。

#### 核心代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll maxn=200005;
ll t,n,a[maxn];
int main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld",&n);
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        sort(a+1,a+1+n);
        ll p=0,ma=0;
        for(int i=1;i<=n;i++){
            if(a[i]!=a[i-1]){
                ma=max(ma,p);
                p=1;
            }
            else p++;
        }
        ma=max(ma,p);
        if(ma>n/2) printf("%lld\n",n-2*(n-ma));
        else if(n%2==1) printf("1\n");
        else printf("0\n");
    }
    return 0;
}
```

### 题解3：作者：_GW_ (赞：3)

#### 星级：4星
#### 关键亮点：
- 使用 `map` 来统计元素出现次数。
- 通过数学推导得出最终剩余的元素数量。
- 代码简洁，逻辑清晰。

#### 核心代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,num,n,m,val,a[N],b[N];
map<int,int> mp;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n;mp.clear();num=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];mp[a[i]]++;
            num=max(num,mp[a[i]]);
        }
        if(n%2==1)
        {
            if(num<=n/2)
            {
                cout<<1<<endl;
            }
            else
            {
                cout<<max(num*2-n,0)<<endl;
            }
        }
        else
        {
            cout<<max(num*2-n,0)<<endl;    
        }    
    }
    return 0;
}
```

### 总结
最优的关键思路是通过贪心策略和数学推导，找到出现次数最多的元素，并根据其出现次数计算最终剩余的元素数量。推荐使用栈算法或排序统计方法来高效解决问题。

### 推荐题目
1. [P2397 摩尔投票法](https://www.luogu.com.cn/problem/P2397)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

---
处理用时：43.38秒