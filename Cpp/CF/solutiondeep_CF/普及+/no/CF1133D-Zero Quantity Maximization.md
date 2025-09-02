# 题目信息

# Zero Quantity Maximization

## 题目描述

# 零数最大化

给出两个长度为 $n$ 的数组 $a,b$。



你想要创建一个长度为 $n$ 的数组 $c$，且$c_i=d*a_i+b_i,i\in[1, n]$，要求你给 $d$ 赋值，使得数组 $c$ 中的 $0$ 的个数最多并输出最多的 $0$ 的个数。

## 样例 #1

### 输入

```
5
1 2 3 4 5
2 4 7 11 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
13 37 39
1 2 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
0 0 0 0
1 2 3 4
```

### 输出

```
0
```

## 样例 #4

### 输入

```
3
1 2 -1
-6 -12 6
```

### 输出

```
3
```

# AI分析结果

【题目内容】已为中文，无需翻译。
【算法分类】数学

【综合分析与结论】
这些题解的核心思路都是根据 $c_i = d\times a_i + b_i = 0$ 推导出 $d = -\frac{b_i}{a_i}$（$a_i\neq0$），然后分类讨论：当 $a_i = b_i = 0$ 时，$d$ 可以取任意值；当 $a_i = 0$ 且 $b_i\neq0$ 时，无解。通过统计满足 $a_i = b_i = 0$ 的个数，以及使用 `map` 统计 $-\frac{b_i}{a_i}$ （以分数形式存储，避免精度问题）出现的最大次数，两者相加得到最终结果。

各题解的算法要点基本相同，主要区别在于代码实现细节，如输入输出方式、分数化简和正负号处理等。解决的难点在于处理精度问题，通过使用分数形式存储 $d$ 来避免。

【所选的题解】
- andyli 的题解（4星）
  - 关键亮点：思路清晰，代码简洁，对分数的正负号处理和化简有详细的实现。
- AndyMo 的题解（4星）
  - 关键亮点：使用了自定义的输入函数，代码结构清晰，对特殊情况的处理明确。
- CQ_Bob 的题解（4星）
  - 关键亮点：封装了多个常用函数，代码模块化程度高，对分数的处理逻辑清晰。

【重点代码】
### andyli 的题解
```cpp
#include <cstdio>
#include <map>
#include <numeric>
using namespace std;
const int maxn = 200005;

int A[maxn];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);
    int sum = 0, ans = 0;
    map<pair<int, int>, int> mp;
    for (int i = 0; i < n; i++) {
        int a = A[i], b;
        scanf("%d", &b);
        if (!a && !b)
            sum++; // 第2种情况
        else if(!a) continue; // a=0时-b/0不合法
        else{
            if (1LL * a * b < 0) // 如果a, b异号，注意使用long long判断
                a = -abs(a), b = abs(b);
            else // a, b同号
                a = abs(a), b = abs(b);
            int t = gcd(a, b); // C++17中numeric头文件里包含gcd函数，不需要考虑正负
            ans = max(ans, ++mp[pair(b / t, a / t)]);
        }
    }
    printf("%d\n", sum + ans);
    return 0;
}
```
核心实现思想：先读取输入，然后遍历数组，对于 $a_i = b_i = 0$ 的情况，计数器 `sum` 加 1；对于 $a_i\neq0$ 的情况，处理分数的正负号并化简，使用 `map` 统计分数出现的次数，更新最大次数 `ans`，最后输出 `sum + ans`。

### AndyMo 的题解
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
namespace io{
    // 自定义输入函数
    il void read(int &x){
        x=0;int f=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
        while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
        x*=f;
    }
}using namespace io;
#define N 200005
int n;
int a[N],b[N];
map <pair<int,int>,int> cnt;
int main(){
    int ans=0,res=0;
    read(n);
    for(re int i=1;i<=n;i++) read(a[i]);
    for(re int i=1;i<=n;i++){
        read(b[i]);
        if(a[i]==0){
            //特判：a[i]==0时，无论d取多少c都只与b[i]有关
            if(b[i]==0) res++;
            continue;
        }
        int gcd=__gcd(a[i],b[i]);
        ans=max(ans,++cnt[make_pair(a[i]/gcd,b[i]/gcd)]);
    }
    printf("%d",ans+res);
    return 0;
}
```
核心实现思想：使用自定义输入函数读取输入，遍历数组，对于 $a_i = 0$ 且 $b_i = 0$ 的情况，计数器 `res` 加 1；对于 $a_i\neq0$ 的情况，化简分数并使用 `map` 统计分数出现的次数，更新最大次数 `ans`，最后输出 `ans + res`。

### CQ_Bob 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
namespace yzqwq{
    // 封装多个常用函数
    il int gcd(int a,int b){
        if(!b) return a;
        return gcd(b,a%b);
    }
    il int read(){
        int x=0,f=1;char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
        while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
        return x*f;
    }
}
using namespace yzqwq;

const int N=2e5+10;
int n,a[N],b[N];
map<pii,int> cnt;

il void solve(){
    n=rd;
    for(re int i=1;i<=n;++i) a[i]=rd;
    for(re int i=1;i<=n;++i) b[i]=rd;
    int mx=0,ans=0;
    for(re int i=1;i<=n;++i){
        if(!a[i]){
            if(!b[i]) ++ans;
            continue;
        }
        int x=-1*b[i];
        int y=a[i];
        int g=gcd(x,y);
        x/=g,y/=g;
        mx=max(mx,++cnt[{x,y}]);
    }
    printf("%lld\n",mx+ans);
    return ;
}

signed main(){
    int t=1;while(t--)
    solve();
    return 0;
}
```
核心实现思想：封装了常用函数，读取输入后遍历数组，对于 $a_i = 0$ 且 $b_i = 0$ 的情况，计数器 `ans` 加 1；对于 $a_i\neq0$ 的情况，计算分数并化简，使用 `map` 统计分数出现的次数，更新最大次数 `mx`，最后输出 `mx + ans`。

【最优关键思路或技巧】
- 使用 `map` 存储分数形式的 $d$，避免了浮点数的精度问题。
- 对分数进行化简和统一正负号处理，确保相同的 $d$ 能被正确统计。

【拓展思路】
同类型题或类似算法套路：
- 涉及方程求解和统计的问题，如给定一组线性方程，求某个参数使得满足方程的解最多。
- 处理精度问题时，可考虑使用分数、整数或其他精确表示的方式。

【推荐题目】
- P1047 [NOIP2005 普及组] 校门外的树
- P1067 [NOIP2009 普及组] 多项式输出
- P1075 [NOIP2012 普及组] 质因数分解

【个人心得】
happybob 的题解提到用 `double` 存精度不够，实测 WA on test 37，提醒我们在处理涉及除法运算时要注意精度问题，可考虑使用分数或 `long double` 等方式来避免。 

---
处理用时：51.17秒