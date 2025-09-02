# Cut Ribbon

## 题目描述

给一长度为n的缎带，要求将其剪成若干长度为a,b,c的缎带，且缎带数量尽可能多。

## 样例 #1

### 输入

```
5 5 3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7 5 5 2
```

### 输出

```
2
```

# 题解

## 作者：zhangyuhan (赞：55)

看似完全背包模板题，实际上还是有不少坑点的QAQ

先谈谈为什么这道题用完全背包来解。

题目中说可以将长度为$n$的绸带切成长度分别为$a$、$b$、$c$三种长度的绸带，求最多切成多少段。

我们来这样理解：有一个容量为$n$的背包，有三种物品，每个物品的体积为$a$、$b$、$c$，求最多能到放进几个物品。

**so?**

这就是完全背包裸题喽。

**但是**，仔细揣摩原题，你会发现：绸带切成的小绸带长度一定要属于$a$，$b$，$c$中的一种，也就是说，转化成背包问题，**背包一定要装满！！！**

如何解决这个问题？

首先，将计算最大数量的$f$数组全部取$-1$，跑完全背包的方程时，**记住判断放入这个物品前时的f数组是不是-1**，如果不是，再执行状态转移方程。

你以为结束了？

**NO!**

如果你就这样乖乖地照着上面的思路打的话，你会发现程序一直输出$-1$!

**why？**

如果你全赋值成$-1$，状态转移方程将永远不会执行，$f[n]$也一直是$-1$!

**How to solve this problem?**

根据常识，一个长度为$0$的绸带，无论$a$、$b$、$c$是多少，都只能切成$0$段。

**so?**

将$f[0]$赋为$0$即可。

$AC$ $Code$

```cpp
#include<iostream>
#include<cstring>
using namespace std;

int n,w[4],f[4010];

int main(){
    cin>>n;
    for(int i=1;i<=3;i++)
        cin>>w[i];
    memset(f,-1,sizeof(f));
    f[0]=0;
    for(int i=1;i<=3;i++)
        for(int j=w[i];j<=n;j++){
            if(f[j-w[i]]!=-1)
                f[j]=max(f[j],f[j-w[i]]+1);
        }
    cout<<f[n]<<endl;
    return 0;
}
```

---

## 作者：wky32768 (赞：16)

这题就是一个裸的完全背包

可是背包必须要装满。

可是前面没有看出来~~一定是我英文太差~~

所以完全背包大家都会吧。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[12],f[120000];

int main() {
    cin>>n>>a[1]>>a[2]>>a[3];
    memset(f,-1,sizeof f);
    f[0]=0;
    for(int i=1;i<=3;i++)
        for(int j=a[i];j<=n;j++){
            if(f[j-a[i]]<0) continue;
            f[j]=max(f[j],f[j-a[i]]+1);
        }
    cout<<f[n];
    return 0;
}

神犇轻喷~~

```

---

## 作者：哔哩哔哩 (赞：4)

完全背包模板题

毕竟也是A题

完全背包差不多就是拆分成01背包就是二进制优化吧

上代码

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<stack>
#include<set>
#include<array>
#include<cstdio>
#include<cstring>
using namespace std;
const int inf=(int)2e9+99;
const int N=4e4+5;

int x,y,z;
int n,a[3],b[N];

int main()
{
    cin>>n>>a[0]>>a[1]>>a[2];
    memset(b,-1,sizeof(b));
    b[0]=0;
    for(int i=0;i<3;i++)
        for(int j=0;j<=n;j++)
            if(b[j]!=-1&&b[j]+1>b[j+a[i]]) b[j+a[i]]=b[j]+1;
    cout<<b[n];
    return 0;
}
```

---

