# Vasily the Bear and Sequence

## 题目描述

Vasily the bear has got a sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Vasily the Bear wants to write out several numbers on a piece of paper so that the beauty of the numbers he wrote out was maximum.

The beauty of the written out numbers $ b_{1},b_{2},...,b_{k} $ is such maximum non-negative integer $ v $ , that number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by number $ 2^{v} $ without a remainder. If such number $ v $ doesn't exist (that is, for any non-negative integer $ v $ , number $ b_{1} $ $ and $ $ b_{2} $ $ and $ $ ... $ $ and $ $ b_{k} $ is divisible by $ 2^{v} $ without a remainder), the beauty of the written out numbers equals -1.

Tell the bear which numbers he should write out so that the beauty of the written out numbers is maximum. If there are multiple ways to write out the numbers, you need to choose the one where the bear writes out as many numbers as possible.

Here expression $ x $ $ and $ $ y $ means applying the bitwise AND operation to numbers $ x $ and $ y $ . In programming languages C++ and Java this operation is represented by "&", in Pascal — by "and".

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
2
4 5
```

## 样例 #2

### 输入

```
3
1 2 4
```

### 输出

```
1
4
```

# 题解

## 作者：Graphcity (赞：1)

## 思路

首先当然要倒序枚举 $v$，如果当前有一个 $v$ 满足题目所示的条件，输出当前的方案，然后终止程序就行了。

在枚举时，首先要找到所有满足 $a_i \ \text{and} \ 2^v$ 为真的数，只有这样它们进行与运算后的二进制第 $v$ 位是 1。

而且，选取的方案还要满足第 0 位到第 $v-1$ 位的值 **均为零** ，这样才能保证整除。由于与运算满足结果不大于进行运算的两个数，就把这些数全部选进去就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=int(1e5);

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,a[Maxn+5];
vector<int> v; // 记录方案

int main()
{
    n=read();
    for(register int i=1;i<=n;++i)
        a[i]=read();
    for(register int i=30;i>=0;--i)
    {
        int now=0,res=0; // now:数的个数 res:运算后的值
        v.clear();
        for(register int j=1;j<=n;++j)
            if(a[j]&(1<<i)) // 选取数
            {
                now++,res&=a[j],v.push_back(a[j]);
                if(now==1) res=a[j];
            }
        if(res%(1<<i)==0 && now) // 判断是否合法
        {
            printf("%d\n",now);
            for(auto i:v) printf("%d ",i);
            return 0;
        }
    }
    printf("-1");
    return 0;
}
```

---

## 作者：Rye_Catcher (赞：0)

### 题目链接

https://www.luogu.org/problemnew/show/CF336C

### 分析

一个比较妙的贪心

我们要让最后$and$起来的数被$2^k$整除且$k$最大,我们不妨从后往前枚举$k$,同时运用贪心的思路,对于二进制第$k$为1的数,我们想让最后得到的数除第$k$位外都为0,当然是$and$越多越好

### 代码
```
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <queue>
#include <bitset>
#define ll long long 
#define ri register int 
using std::min;
using std::max;
template <class T>inline void read(T &x){
    x=0;int ne=0;char c;
    while(!isdigit(c=getchar()))ne=c=='-';
    x=c-48;
    while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
    x=ne?-x:x;return ;
}
const int maxn=100005;
const int inf=0x7fffffff;
int a[maxn],n,q[maxn];
int main(){
    int x,y,z;
    int ans=0;
    read(n);
    for(ri i=1;i<=n;i++){
        read(a[i]);
    }
    for(ri k=30;k>=0;k--){
        x=(1<<k);
        y=x-1;
        ans=0;
        for(ri i=1;i<=n;i++){
            //printf("%d %d\n",a[i],x);
            if(a[i]&x){
                y=y&a[i];
                q[++ans]=a[i];
            }
        }
        if(y==0){
            printf("%d\n",ans);
            for(ri i=1;i<=ans;i++){
                printf("%d ",q[i]);
            }
            puts("");
            return 0;
        }
    }
    return 0;
}
```

---

