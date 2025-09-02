# 题目信息

# [USACO22OPEN] Counting Liars B

## 题目描述

奶牛 Bessie 躲在数轴上的某处。Farmer John 的 $N$ 头奶牛（$1\le N\le 1000$）中的每头奶牛都有一条信息要分享：第 $i$ 头奶牛说 Bessie 躲在小于或等于 $p_i$ 的某个位置，或者说 Bessie 躲在大于或等于 $p_i$ 的某个位置（$0\le p_i\le 10^9$）。

不幸的是，可能不存在躲藏位置与所有奶牛的回答均一致，这意味着并非所有奶牛都在说真话。计算在撒谎的奶牛的最小数量。

## 说明/提示

【样例解释 1】

有可能没有奶牛在撒谎。

【样例解释 2】

至少一头奶牛在撒谎。

## 样例 #1

### 输入

```
2
G 3
L 5```

### 输出

```
0```

## 样例 #2

### 输入

```
2
G 3
L 2```

### 输出

```
1```

# AI分析结果

### 综合分析与结论
这些题解主要围绕计算在撒谎的奶牛的最小数量这一问题展开，多数题解采用了枚举的思路，通过不同方式优化枚举过程以降低时间复杂度。常见做法是将 `L` 和 `G` 条件分别处理，排序后进行枚举和判断。部分题解还运用了离散化、差分等技巧进一步优化。

### 所选题解
- **Ginger_he（5星）**
    - **关键亮点**：思路清晰，详细阐述了前置知识和枚举过程，还给出了优化思路，代码注释详细，可读性高。
    - **核心实现思想**：将 `L` 和 `G` 条件分别存入数组 `a` 和 `b` 并排序，通过双重循环枚举 `a` 和 `b` 中的元素，判断条件是否合法，更新最小撒谎奶牛数量。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1005
int n,t,x,y,a[N],b[N],ans;
char c;
int main()
{
    scanf("%d",&n);
    b[++y]=-1;
    for(int i=1;i<=n;i++)
    {
        scanf("\n%c%d",&c,&t);
        if(c=='L') a[++x]=t;
        else b[++y]=t;
    }
    sort(a+1,a+x+1);
    sort(b+1,b+y+1);
    a[++x]=1e9+1,ans=n-1;
    for(int i=1;i<=x;i++)
    {
        for(int j=1;j<=y;j++)
        {
            if(a[i]>=b[j]) ans=min(ans,i-1+y-j);
            else break;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
- **_lfxxx_（4星）**
    - **关键亮点**：提供了两种复杂度的解法，详细说明了优化思路，包括离散化和差分的运用。
    - **核心实现思想（$O(n^2)$）**：枚举每头奶牛的位置，判断其他奶牛的条件是否满足，统计撒谎奶牛数量并取最小值。
```cpp
namespace solution{
constexpr int N=1e3+5;
struct cow{
    char op;
    int p;
}a[N];
void main(){
    int n,s,ans(N);
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i].op>>a[i].p;
    for(int i=1;i<=n;++i){
        s=0;
        for(int j=1;j<=n;++j)
            s+=a[j].op=='L'&&a[j].p<a[i].p||a[j].op=='G'&&a[j].p>a[i].p;
        ans=min(ans,s);
    }
    cout<<ans<<endl;
}
}
```
- **lsj2009（4星）**
    - **关键亮点**：运用前缀和（后缀和）与离散化技巧，思路独特，复杂度较低。
    - **核心实现思想**：使用离散化将 $p_i$ 的值转换到 $1$ 至 $n$ 之间，通过前缀和（后缀和）计算不同位置说真话的奶牛数量，进而求出最小撒谎奶牛数量。
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
const int N=1e3+5;
int a[N],t[N],sum0[N],sum1[N],n,ans,len;
char opt[N];
signed main() {
    cin>>n;
    _for(i,1,n)
        cin>>opt[i]>>a[i],t[i]=a[i];
    sort(t+1,t+n+1);
    len=unique(t+1,t+n+1)-(t+1);
    _for(i,1,n) {
        int x=lower_bound(t+1,t+len+1,a[i])-t;
        if(opt[i]=='L')
            ++sum0[x];
        else
            ++sum1[x];
    }
    _for(i,1,len) sum1[i]+=sum1[i-1];
    _rep(i,len,1) sum0[i]+=sum0[i+1];
    _for(i,1,len)
        ans=max(ans,sum0[i]+sum1[i]);
    printf("%d",n-ans);
    return 1;
}
```

### 最优关键思路或技巧
- **离散化**：当数据范围较大时，可将数据映射到较小的区间，减少枚举范围，如 `Galex`、`_lfxxx_` 和 `lsj2009` 的题解。
- **差分**：将条件转化为区间加的形式，通过差分优化判断合法的过程，如 `_lfxxx_` 的题解。
- **前缀和（后缀和）**：用于快速计算满足条件的奶牛数量，如 `lsj2009` 的题解。

### 可拓展之处
同类型题可能涉及更多复杂的不等式条件或更高维度的空间，类似算法套路可应用于区间覆盖、交集判断等问题。

### 推荐题目
- P1007 独木桥
- P1226 快速幂取余运算
- P1168 中位数

### 个人心得
- **苏联小渣**：原代码错在忽略了说 `L` 的和说 `R` 的人可以全错，提醒我们在解题时要考虑全面特殊情况。
- **ImposterAnYu**：正常枚举 $x$ 会很慢，可优化为枚举 $i$ 让 $x = a_i$，体现了优化枚举策略的重要性。 

---
处理用时：32.75秒