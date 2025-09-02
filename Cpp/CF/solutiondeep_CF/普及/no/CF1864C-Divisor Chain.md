# 题目信息

# Divisor Chain

## 题目描述

You are given an integer $ x $ . Your task is to reduce $ x $ to $ 1 $ .

To do that, you can do the following operation:

- select a divisor $ d $ of $ x $ , then change $ x $ to $ x-d $ , i.e. reduce $ x $ by $ d $ . (We say that $ d $ is a divisor of $ x $ if $ d $ is an positive integer and there exists an integer $ q $ such that $ x = d \cdot q $ .)

There is an additional constraint: you cannot select the same value of $ d $ more than twice.

For example, for $ x=5 $ , the following scheme is invalid because $ 1 $ is selected more than twice: $ 5\xrightarrow{-1}4\xrightarrow{-1}3\xrightarrow{-1}2\xrightarrow{-1}1 $ . The following scheme is however a valid one: $ 5\xrightarrow{-1}4\xrightarrow{-2}2\xrightarrow{-1}1 $ .

Output any scheme which reduces $ x $ to $ 1 $ with at most $ 1000 $ operations. It can be proved that such a scheme always exists.

## 说明/提示

In the first test case, we use the following scheme: $ 3\xrightarrow{-1}2\xrightarrow{-1}1 $ .

In the second test case, we use the following scheme: $ 5\xrightarrow{-1}4\xrightarrow{-2}2\xrightarrow{-1}1 $ .

In the third test case, we use the following scheme: $ 14\xrightarrow{-2}12\xrightarrow{-6}6\xrightarrow{-3}3\xrightarrow{-1}2\xrightarrow{-1}1 $ .

## 样例 #1

### 输入

```
3
3
5
14```

### 输出

```
3
3 2 1
4
5 4 2 1
6
14 12 6 3 2 1```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个整数 $x$，你的任务是将 $x$ 减少到 $1$。

你可以执行以下操作：

- 选择一个 $x$ 的因数 $d$，然后将 $x$ 修改为 $x - d$，即 $x$ 减少 $d$。（我们称 $d$ 是 $x$ 的因数，如果 $d$ 是一个正整数且存在整数 $q$ 使得 $x = d \cdot q$。）

此外，还有一个额外的限制：你不能选择相同的 $d$ 超过两次。

例如，对于 $x=5$，以下方案是无效的，因为 $1$ 被选择了超过两次：$5\xrightarrow{-1}4\xrightarrow{-1}3\xrightarrow{-1}2\xrightarrow{-1}1$。然而，以下方案是有效的：$5\xrightarrow{-1}4\xrightarrow{-2}2\xrightarrow{-1}1$。

输出任何将 $x$ 减少到 $1$ 的方案，且操作次数最多为 $1000$ 次。可以证明这样的方案总是存在。

#### 说明/提示

在第一个测试用例中，我们使用以下方案：$3\xrightarrow{-1}2\xrightarrow{-1}1$。

在第二个测试用例中，我们使用以下方案：$5\xrightarrow{-1}4\xrightarrow{-2}2\xrightarrow{-1}1$。

在第三个测试用例中，我们使用以下方案：$14\xrightarrow{-2}12\xrightarrow{-6}6\xrightarrow{-3}3\xrightarrow{-1}2\xrightarrow{-1}1$。

#### 样例 #1

##### 输入

```
3
3
5
14
```

##### 输出

```
3
3 2 1
4
5 4 2 1
6
14 12 6 3 2 1
```

### 算法分类

位运算、数学

### 题解分析与结论

该题的核心思路是将问题转化为二进制操作，利用 `lowbit` 函数逐步减少 $x$ 的值，直到 $x$ 变为 $1$。具体来说，通过每次减去 $x$ 的二进制表示中的最低位的 $1$，可以将 $x$ 逐步减少到 $2^k$，然后再通过每次除以 $2$ 的方式将 $2^k$ 减少到 $1$。这种方法保证了每个因数 $d$ 最多被使用两次，且操作次数在 $O(\log x)$ 级别。

### 所选高分题解

#### 题解1：Jerry_heng (5星)

**关键亮点**：
- 利用二进制分解的思路，每次减去 `lowbit(x)`，直到 $x$ 变为 $2^k$，然后再通过除以 $2$ 的方式减少到 $1$。
- 代码简洁明了，逻辑清晰，易于理解。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,cnt,x,a[1010];
int lowbit(int x){
    return x&-x;
}
int main(){
    cin>>t;
    while(t--){
        cin>>x,cnt=0;
        for(;x&(x-1);x-=lowbit(x))a[++cnt]=x;
        for(;x;x>>=1)a[++cnt]=x;
        cout<<cnt<<endl;
        for(int i=1;i<=cnt;i++)cout<<a[i]<<" ";
        cout<<endl;
    }
    return 0;
}
```

#### 题解2：cjh20090318 (4星)

**关键亮点**：
- 通过二进制拆分的方式，逐步减去 $x$ 的最低次幂，直到 $x$ 变为 $2^k$，然后再通过砍半的方式减少到 $1$。
- 详细证明了每一步的合理性，确保每个因数 $d$ 最多被使用两次。

**核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
void solve(){
    int x;scanf("%d",&x);
    std::vector<int> v;
    v.emplace_back(x);
    int y=1<<std::__lg(x);
    int z=x-y;
    for(int i=0;i<=30;i++)if(z&(1<<i))v.emplace_back(x-=(1<<i));
    while(y>1)v.emplace_back(y>>=1);
    printf("%zu\n",v.size());
    for(const int y:v) printf("%d ",y);
    putchar('\n');
}
int main(){
    int T;scanf("%d",&T);
    while(T--) solve(); 
    return 0;
}
```

#### 题解3：One_JuRuo (4星)

**关键亮点**：
- 通过将 $x$ 逐步减少到 $2^k$，然后再通过每次减去 $x/2$ 的方式减少到 $1$。
- 详细解释了每一步的操作，确保每个因数 $d$ 最多被使用两次。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int lowbit(int x){return x&(-x);}
int T,n,ans[1005],cnt,nn;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n),cnt=0,nn=n;
        while(n&(n-1)){
            ans[++cnt]=lowbit(n),n-=lowbit(n);
        }
        while(n>1) ans[++cnt]=n/2,n/=2;
        printf("%d\n",cnt+1);
        for(int i=1;i<=cnt;++i)
        {
            printf("%d ",nn),nn-=ans[i];
        }
        printf("%d\n",nn);
    }
    return 0;
}
```

### 最优关键思路

利用二进制分解的思路，每次减去 `lowbit(x)`，直到 $x$ 变为 $2^k$，然后再通过除以 $2$ 的方式减少到 $1$。这种方法保证了每个因数 $d$ 最多被使用两次，且操作次数在 $O(\log x)$ 级别。

### 拓展思路

类似的问题可以通过二进制分解或位运算来解决，尤其是在涉及因数操作或减少操作时，二进制分解往往能提供简洁高效的解决方案。

### 推荐题目

1. [P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)
2. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)
3. [P1010 幂次方](https://www.luogu.com.cn/problem/P1010)

---
处理用时：36.07秒