# 题目信息

# Long Long

## 题目描述

给出一个包含 $n$ 个数字的数列 $a$。你可以执行任意次操作，每次操作可以更改 [l, r] 范围内的正负性（正数变负，负数变正，0 不变）。你要使得数列每个元素之和尽量大，问最小的操作次数。

多组询问。

## 说明/提示

$1\leq T \leq 10^4$

$1\leq n \leq 2\times10^5$

$-10^9\leq a_i \leq 10^9$

数据保证所有询问的 $n$ 总和不超过 $2\times10^5$。

统计数字之和部分可能会爆 int，请选择合适的储存方式。

## 样例 #1

### 输入

```
5
6
-1 7 -4 -2 5 -8
8
-1 0 0 -2 1 0 -3 0
5
2 -1 0 -3 -7
5
0 -17 0 1 0
4
-1 0 -2 -1```

### 输出

```
27 3
7 2
13 1
18 1
4 1```

# AI分析结果

【题目内容】已为中文，无需翻译。
【算法分类】贪心

【综合分析与结论】
这些题解的核心思路一致，都将问题拆分为两部分：一是求数列和的最大值，二是求达到最大值所需的最少操作次数。对于第一部分，大家都发现最优情况是让数列元素全为非负数，所以最大和就是数列元素绝对值之和。对于第二部分，通过贪心策略，将连续的负数区间视为一个整体进行操作，操作次数即为负数连续区间的数量。
不同题解在处理细节和代码实现上略有差异，比如部分题解选择忽略 0，部分题解将 0 与负数一同处理，但本质都是为了统计负数连续区间的个数。

【所选的题解】
- Auto_Accepted（5 星）：关键亮点在于思路清晰，证明了贪心策略的正确性，代码简洁易懂。
- Dream__Sky（4 星）：思路明确，代码注释详细，便于理解。
- _O_v_O_（4 星）：思路清晰，代码结构简洁，通过标记判断负数区间的开始和结束。

【重点代码】
Auto_Accepted 的核心代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n , a[1000005];
signed main() {
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        int ans = 0 , cnt = 0;
        for(int i = 1;i <= n;i++){
            cin >> a[i];
            ans += abs(a[i]);
        }
        a[0] = 114514;
        for(int i = 1;i <= n;i++){
            if(a[i] < 0){
                cnt++;
                while(a[i] <= 0 && i <= n) i++;
            }
        }
        cout << ans << ' ' << cnt << endl;
    }
    return 0;
}
```
核心实现思想：先计算数列元素绝对值之和得到最大和，再遍历数列，遇到负数时操作次数加 1，并跳过该负数区间。

Dream__Sky 的核心代码：
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,x;
signed main()
{
    cin>>T;
    while(T--){
        int daan1=0,daan2=0;
        bool p=0;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>x;
            daan1+=abs(x);
            if(x<0&&!p) p=1,daan2++;
            else if(x>0) p=0;
        }
        
        cout<<daan1<<" "<<daan2<<"\n";
    }
    return 0;
}
```
核心实现思想：同样先计算绝对值之和，利用标记 `p` 判断是否为新的连续负数子序列的开始，若是则操作次数加 1。

_O_v_O_ 的核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long  
int t,n,a;
signed main(){
    cin>>t;
    while(t--){
        int ans1=0,ans2=0; 
        bool flag=true; 
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a;
            ans1+=abs(a);
            if(a<0&&flag){ 
                ans2++;
                flag=false;
            } 
            if(!flag&&a>0) flag=true; 
        }
        cout<<ans1<<' '<<ans2<<endl;
    }
    return 0;
}
```
核心实现思想：先计算最大和，通过标记 `flag` 确定负数区间的开始和结束，统计操作次数。

【可拓展之处】
同类型题可能会对操作进行更多限制，如限制操作次数、操作区间长度等，或者改变操作的具体内容。类似算法套路可应用于其他需要通过局部最优达到全局最优的问题，如区间覆盖、资源分配等。

【推荐题目】
1. P1223 排队接水（https://www.luogu.com.cn/problem/P1223）
2. P1090 合并果子（https://www.luogu.com.cn/problem/P1090）
3. P2240 部分背包问题（https://www.luogu.com.cn/problem/P2240）

【个人心得】
_Only_this：“这题本是道水题，但我却调了半个小时。” 总结：即使题目看起来简单，也可能在实现过程中遇到问题，需要仔细调试。 

---
处理用时：31.91秒