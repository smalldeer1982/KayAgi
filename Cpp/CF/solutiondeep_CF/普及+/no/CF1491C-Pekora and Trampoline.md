# 题目信息

# Pekora and Trampoline

## 题目描述

有 $n$ 个蹦床排成一列，每个蹦床有一个弹力值 $s_i$

每一轮的最开始，Pekora 会选择一个蹦床作为她的起点（任意一个蹦床都可以作为起点）。当她在蹦床 $i$ 时，她会跳到蹦床 $i+s_i$ 上，并且 $s_i$ 会变为 $\max(1,s_i-1)$（也就是说，蹦床每被跳一次弹力值就会减一，直到弹力值为 $1$）。当她跳到了第 $n$ 个蹦床的后面时，该轮结束。

现在，Pekora 想要把所有的 $s_i$ 都变成 $1$，问最少要多少轮才能实现这个目标

## 说明/提示

$1 \le T \le 500$  
$\sum n \le 5000$  
$1 \le s_i \le 10^9$

## 样例 #1

### 输入

```
3
7
1 4 2 2 2 2 2
2
2 3
5
1 1 1 1 1```

### 输出

```
4
3
0```

# AI分析结果

### 题目翻译
本题内容已为中文，无需翻译。

### 算法分类
贪心

### 综合分析与结论
这些题解大多围绕贪心思想展开，通过维护每个蹦床被经过的次数来计算最少轮数。不同题解在实现细节和优化方法上有所不同，如使用差分、树状数组、并查集等数据结构进行优化。

### 所选题解
- **作者：nalemy（4星）**
  - **关键亮点**：思路清晰，详细说明了贪心的选择原因，代码实现简洁，使用差分进行区间更新。
  - **个人心得**：提到多组数据要记得数组清零，否则会踩坑。
- **作者：ailanxier（4星）**
  - **关键亮点**：分析了贪心的合理性，使用差分优化区间更新，代码注释详细。
- **作者：SSerxhs（4星）**
  - **关键亮点**：提供了 $O(\sum n)$ 的做法，思路简洁，代码实现高效。

### 重点代码
#### nalemy 的代码
```C++
#include<iostream>
#include<cstring>
#define N 5010
using namespace std;
typedef long long ll;

int n, s[N], d[N];
int main() {
    int t; cin >> t;
    while(t--) {
        cin >> n; ll cnt = 0, t = 0;
        memset(d, 0, sizeof(d));
        for(int i=0; i<n; i++)
            cin >> s[i];
        for(int i=0; i<n; i++){
            t += d[i];
            if (t > s[i] - 1)
                d[i+1] += t - s[i] + 1, d[i+2] -= t - s[i] + 1;
            else cnt += s[i] - t - 1;
            if (i+2 <= min(s[i]+i, n))
                d[i+2]++, d[min(s[i]+i, n)+1]--;
        }
        cout << cnt << endl;
    }
    return 0;
}
```
**核心实现思想**：使用差分 `d` 数组记录每个位置的变化，遍历每个蹦床，根据当前蹦床被经过的次数 `t` 来更新差分数组和答案 `cnt`。

#### ailanxier 的代码
```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 6;
typedef long long ll;
int n,s[N],b[N];

int main(){
    int t;scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        ll ans = 0;
        for(int i = 1;i <= n;i++) scanf("%d", s + i), b[i] = 0;b[n + 1]=0;
        int las = 0;
        for(int i = 1;i <= n;i++){
            int now = b[i] + las;
            las = now;
            if(now > s[i] - 1){
                b[i+1] += now - s[i] + 1;
                b[i+2] -= now - s[i] + 1;
                now = s[i] - 1;
            }
            ans += s[i] - now - 1;
            if(min(s[i] + i, n) >= i + 2){
                b[i+2] ++;
                b[min(s[i] + i, n) + 1]--;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
**核心实现思想**：同样使用差分 `b` 数组，通过 `las` 记录上一个位置的变化，计算当前蹦床被经过的次数 `now`，更新差分数组和答案 `ans`。

#### SSerxhs 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef long long ll;
const int N=5e3+2;
ll ans;
ll f[N],g[N];
int a[N];
int T,n,m,c,i,j,k,x,y,z,la;
int main()
{
    T=1;read(T);
    while (T--)
    {
        read(n);ans=0;
        for (i=1;i<=n;i++) read(a[i]);
        memset(f+1,0,n<<3);
        memset(g+1,0,n<<3);
        for (i=1;i<=n;i++) 
        {
            f[i]+=(g[i]+=g[i-1]);
            if (f[i]<a[i]-1) ans+=a[i]-1-f[i]; else f[i+1]+=f[i]-(a[i]-1); 
            ++g[i+2];--g[1+min(n,i+a[i])];
        }
        printf("%lld\n",ans);
    }
}
```
**核心实现思想**：使用 `f` 数组记录每个蹦床被经过的次数，`g` 数组作为差分，遍历每个蹦床，更新 `f` 数组和答案 `ans`。

### 最优关键思路或技巧
- **贪心思想**：每次从第一个 $s_i$ 不为 $1$ 的蹦床开始跳，能让后面的 $s$ 尽可能减少。
- **差分优化**：使用差分可以将区间更新的时间复杂度优化到 $O(1)$。

### 拓展思路
同类型题可以考虑一些具有状态转移和区间操作的问题，例如一些游戏中的资源分配、跳跃问题等。类似算法套路可以使用贪心结合差分、树状数组等数据结构来优化区间操作。

### 推荐洛谷题目
1. P1083 借教室
2. P3374 【模板】树状数组 1
3. P2367 语文成绩

---
处理用时：43.42秒