# [NERC2024] Fix Flooded Floor

## 样例 #1

### 输入

```
4
10
#.......##
##..#.##..
6
...#..
..#...
8
........
........
3
###
###```

### 输出

```
Unique
None
Multiple
Unique```

# 题解

## 作者：reinforest (赞：0)

## Problem

给你一个 $2 \times n$ 的字符矩阵，要求你用 $1 \times 2$ 的多米诺骨牌密铺，多米诺骨牌不能互相重合。但是有些点是不能被覆盖的，具体来说，`.` 是可以被覆盖的，`#` 是不可以被覆盖的。

不存在密铺方式输出 `None`，存在唯一方式输出 `Unique`，方式不唯一输出 `Multiple`。

$1 \leq n \leq 2\times 10^5$。

## Solution

这道题实际上是**贪心**。

如果我们找到**第一个存在 `.` 的列**，设其下标为 $i$，因为我们用的是 $1 \times 2$ 的骨牌，可能对下一列有影响，所以我们把下一列的情况纳入讨论范围，发现有以下 $6$ 种情况**必须**进行如下放置：

放置前：

```
#. ## .. .. .# .. .#
.. .. #. ## .# .# ..
```
放置后：

```
#. ## xx xx x# x. x#
xx xx #. ## x# x# x.
```

以下 $1$ 种情况可以有 $2$ 种放置方式：

```
..
..
```

其余的情况都无解。

我们这样就至少可以密铺完第 $i$ 列以及之前的所有列。然后重复执行以上操作即可得到答案。

---

对于以上结论进行分析，我们发现如果第 $i$ 列上没有 `#`，那么都在判断有 $2$ 种放置方式的情况之后，把这一列铺满一定不劣。

否则，找到第 $i$ 列上为 `.` 的点 $(p,i)$，我们需要把 $(p,i)$ 与 $(p,i+1)$ 铺上骨牌。当然此时的无解判断条件就是 $(p,i+1)$ 是否是 `.`。

为了代码简便，我们把字符串每一行的最后补上 `#`。

## Code

代码简单易懂。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
constexpr ll maxn=2e5+5;
char ch[2][maxn];
ll T,n;
int work(){
    cin>>n;
    for(ll i=0;i<2;i++)cin>>(ch[i]+1);
    ch[0][n+1]=ch[1][n+1]='#';
    bool multi=false;
    for(ll i=1;i<=n;i++){
        if(ch[0][i]=='.' || ch[1][i]=='.'){
            if(ch[0][i]=='.' && ch[1][i]=='.'){
                if(ch[0][i+1]=='.' && ch[1][i+1]=='.'){
                    multi=true;
                }
                ch[0][i]='#';
                ch[1][i]='#';
            }else if(ch[0][i]=='#'){
                if(ch[1][i+1]=='#')return -1;
                ch[1][i]=ch[1][i+1]='#';
            }else{
                if(ch[0][i+1]=='#')return -1;
                ch[0][i]=ch[0][i+1]='#';
            }
        }
    }
    return multi;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        switch(work()){
            case -1:cout<<"None\n";break;
            case 0:cout<<"Unique\n";break;
            case 1:cout<<"Multiple\n";break;
        }
    }
    return 0;
}

```

---

