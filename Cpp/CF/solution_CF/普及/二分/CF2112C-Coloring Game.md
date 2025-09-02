# Coloring Game

## 题目描述

Alice 和 Bob 使用一个长度为 $n$ 的数列 $a$ 进行游戏。

初始时，任何数列中的数字都没有被染色。首先，Alice 选择 $3$ 个 $a$ 中的元素并将它们染为红色。然后 Bob 将选择一个任意元素并将它染为蓝色（如果这个元素原本是红色的，那么蓝色将覆盖掉红色）。Alice 获胜当且仅当剩余的红色的数字之和严格大于蓝色的数字。

你需要计算 Alice 有多少种选择 $3$ 个元素染色的方案使得无论 Bob 如何操作 Alive 都将获胜。

## 说明/提示

**样例解释**

对于前两组数据，无论 Alice 怎么选择元素，Bob 总有办法选择元素使得 Alice 不能获胜。

对于第三组数据，Alice 可以选择任意的三个元素。如果 Bob 选择对红色的某个元素染色，红色数字的和将为 $14$，蓝色数字的和将为 $7$；如果 Bob 选择对某个未染色的元素染色，红色数字的和将为 $21$，蓝色数字的和将为 $7$。

对于第四组数据，Alice 可以选择 $a_1,a_3,a_4$ 或 $a_2,a_3,a_4$。

## 样例 #1

### 输入

```
6
3
1 2 3
4
1 1 2 4
5
7 7 7 7 7
5
1 1 2 2 4
6
2 3 3 4 5 5
5
1 1 1 1 3```

### 输出

```
0
0
10
2
16
0```

# 题解

## 作者：lilong (赞：4)

设 Alice 取的位置为 $i,j,k$ 且 $i<j<k$，则 Bob 的最优策略有两种：取 $n$ 或 $k$。为了使 Alice 必胜，必须同时满足 $a_i+a_j+a_k>a_n,a_i+a_j>a_k$。枚举 $i,j$，显然满足两个条件的 $k$ 都是一段连续的区间。分别二分算出两个区间的边界，那么区间的交集即为合法的 $k$。时间复杂度 $O(\sum(n^2\log n))$。


```cpp
#include<iostream>
#include<cstdio>
#define N 5010
using namespace std;
int n,a[N];
long long ans;
void solve(){
    ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n-1;j++){
            int l=j+1,r=n,mid,ans1=n,ans2=j+1;
            if(a[i]+a[j]<=a[j+1])continue;
            while(l<=r){
                mid=(l+r)/2;
                if(a[i]+a[j]+a[mid]>a[n])ans1=mid,r=mid-1;
                else l=mid+1;
            }
            l=j+1,r=n;
            while(l<=r){
                mid=(l+r)/2;
                if(a[i]+a[j]>a[mid])ans2=mid,l=mid+1;
                else r=mid-1;
            }
            if(ans2>=ans1) ans+=ans2-ans1+1;
        }
    }
    cout<<ans<<'\n';
}
int main(){
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：Revitalize (赞：3)

蒟蒻太菜了，这种唐题都被卡了 $4$ 发罚时，是不是应该退役……    

>题意：    
>在一个正整数序列中选择 $3$ 个数涂红，再选 $1$ 个数涂蓝，蓝色可以覆盖红色，问有多少个三元组，满足：将它们涂成红色后，无论哪一个数涂蓝，都有红色数的和严格大于蓝色数。  

$n$ 范围很小，这启示我们使用 $O(n^2)$ 解法。  

其实题面的描述已经很通俗易懂了。  
首先，序列的顺序不影响最终的答案，那么可以将序列由大到小排序。  
再定义：$C(x,l,r)$ 为排序后下标 $[l,r]$ 范围内有多少个二元组的和严格大于 $x$。  
然后我们可以想到分讨：（注意，下文中“最大值”若无特殊说明，则指整个序列的最大值）    
**【Case 1】**  
如果最大值的数量 $k$ 大于等于 $3$ ，选 $3$ 个最大值涂红，此时显然无论把哪个数涂蓝，都不可能更大。  
一共就是 $\binom{k}{3}$ 种选法。  
**【Case 2】**  
如果最大值的数量 $k$ 大于等于 $2$ ，且序列存在非最大值，选 $2$ 个最大值涂红，再选任意一个非最大值涂红，此时显然无论把哪个数涂蓝，都不可能更大。  
一共就是 $\binom{k}{2}(n-k)$ 种选法。  
**【Case 3】**  
如果序列存在非最大值，选 $1$ 个最大值涂红，再选 $2$ 个非最大值涂红，此时涂蓝一个最大值对于蓝色来说是最优的，所以我们需要使那两个非最大值的和严格大于最大值。  
一共就是 $k\times C(m,k+1,n)$ 种选法，其中 $m$ 是最大值。  
**【Case 4】**    
如果序列存在非最大值，选 $3$ 个非最大值 $x,y,z$ 涂红，此时涂蓝一个最大值，或者是涂蓝 $\max(x,y,z)$ 对于蓝色来说都可能是最优的，所以我们需要使那三个非最大值的和严格大于最大值，同时较小的两个数的和严格大于三个数中最大的那个。    
枚举三个数中的最大数，一共就是 $\displaystyle\sum_{i=k+1}^{n-2} C(\max(m-a_i,a_i),i+1,n)$ 种选法，其中 $m$ 是最大值。  

现在我们来考虑 $C(x,l,r)$ 的计算，由于 $a$ 已经从大到小排序，所以可以双指针 $O(n)$ 维护，做法很显然，两个指针 $i,j$ 分别维护二元组的两个值的下标，始终保证 $i<j$，然后 $i$ 每往后移动一位，$j$ 就根据目前的 $a_i$ 往前移动，直到 $a_i+a_j$ 恰好刚刚大于 $x$，此时答案加上 $j-i$ 即可，代表着 $a_i+a_{[i+1,j]}$ 都大于 $x$。  

所以总体就是 $O(n^2)$。  

```cpp
#include <bits/stdc++.h>
#define sor(i, l, r) for (int i = l; i <= r; i++)
#define int unsigned long long
using namespace std;
namespace Revitalize
{
    const int N = 5e5;
    int T, n, a[N];
    int solve(int x, int l, int r)
    {
        int res = 0, j = r;
        for (int i = l; i <= r; i++)
        {
            if (j <= i)
                break;
            while ((a[i] + a[j] <= x) && (j > i + 1))
                j--;
            if (a[i] + a[j] > x)
                res += j - i;
        }
        return res;
    }
    inline void work()
    {
        cin >> T;
        while (T--)
        {
            cin >> n;
            sor(i, 1, n) cin >> a[i];
            sort(a + 1, a + n + 1, greater<int>());
            int b = n + 1;
            sor(i, 1, n)
            {
                if (a[i] != a[1])
                {
                    b = i;
                    break;
                }
            }
            int ans = 0;
            if (b - 1 >= 3)
                ans += (b - 1) * (b - 2) * (b - 3) / 6;
            if (b - 1 >= 2 && b != n + 1)
                ans += (b - 1) * (b - 2) * (n - b + 1) / 2;
            if (b != n + 1)
                ans += solve(a[1], b, n) * (b - 1);
            for (int i = b; i <= n - 2; i++)
            {
                ans += solve(max(a[1] - a[i],a[i]), i + 1, n);
            }
            cout << ans << "\n";
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    return Revitalize::work(), 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
有一个长 $n$ 的整数序列 $a$，开始所有数字都没有颜色，小 $A$ 先选择三个数涂上红色，小 $B$ 再选择一个数涂上蓝色（蓝色可覆盖小 $A$ 涂上的红色），问小 $A$ 最后有多少种方案使得无论小 $B$ 如何操作，红色的数总和总是严格大于蓝色的数。

$t\le10^3$ 组多测，$\sum n\le 5\times10^3,a_i\le10^6$，$a$ 序列单调递增。
# 思路
我们总结一下题目：

给定一个大小 $n$ 的序列 $a$，小 $A$ 先选择 $a_{i_1},a_{i_2},a_{i_3}(i_1<i_2<i_3)$，小 $B$ 再选择一个数 $a_j$。如果 $j=i_x(x\in[1,3])$，则视为小 $A$ 失去了所选的 $a_{i_x}$。问有多少种方案满足小 $B$ 取任何数都使得小 $A$ 得数字总和严格大于 $a_j$。

不妨翻转一下序列 $a$，使其单调递减。同时我们令值 $m$ 等于小 $A$ 数总和减去小 $B$ 所选数的值，那么若 $m>0$，则该方案成立。因为无论小 $B$ 如何操作都要确保 $m>0$，所以我们不必考虑小 $B$ 所有操作的情况，直接考虑其最优解即可。

考虑小 $A$ 取三个数 $a_{i_1},a_{i_2},a_{i_3}$：

- 如果小 $B$ 选择 $a_{i_x}(x\in[1,3])$，因为 $a$ 单调递减， 小 $B$ 最优选择 $a_{i_1}$，也就是三个数种最大的一个。最后 $m=a_{i_2}+a_{i_3}-a_{i_1}$。
- 如果小 $B$ 选择 $a_{i_x}(x\in[1,3])$ 外的其他数，同上道理，最优选择 $a_1$。最后 $m=a_{i_2}+a_{i_3}+a_{i_1}-a_1$。

小 $B$ 最优解下 $m=\min(a_{i_2}+a_{i_3}-a_{i_1},a_{i_2}+a_{i_3}+a_{i_1}-a_1)=a_{i_2}+a_{i_3}+\min(-a_{i_1},a_{i_1}-a_1)$。

不难观察到，我们可以把 $m$ 分 $a_{i_2}+a_{i_3},\min(-a_{i_1},a_1-a_{i_1})$ 两部分处理，遍历序列对于每一个 $a_{i_1}$，求出所有满足 $m>0$ 的 $a_{i_2},a_{i_3}$。考虑到 $\sum n\le 5\times10^3$，暴力地套三层循环肯定有问题，我们考虑遍历 $a_{i_1},a_{i_2}$，对于 $a_{i_3}$ 二分求解。

因为如果 $i_1=1$ 第二种情况本应该为 $m=a_{i_2}+a_{i-3}-a_{i_1}$，明显与分析不符，但是因为这是特例，特判即可。

注意到最多有 $C_n^3>2\times10^9$ 种方案。

时间复杂度 $O(n^2\log n)$。
# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5;
int n,a[N];
long long ans;
inline bool cmp(int x,int y){return x>y;}
inline void solve(){
	scanf("%d",&n);
	for(int i=n;i>=1;i--)scanf("%d",&a[i]);
	if(n==3){
		if(a[1]>=a[2]+a[3])puts("0");
		else puts("1");
		return;
	}
	if(a[1]>=a[2]+a[3]+a[4])return puts("0"),void();
	ans=0;
	for(int i=1;i<n-1;i++){
		int x=min(-a[i],a[i]-a[1]);
		if(i==1)x=-a[i];
		for(int j=i+1;j<n;j++){
			int l=j,r=n;
			while(l<r){
				int mid=l+r+1>>1;
				if(x+a[j]+a[mid]>0)l=mid;
				else r=mid-1;
			}
			ans+=l-j;
		}
	}
	printf("%lld\n",ans);
	return;
}
int main(){
	int t;scanf("%d",&t);
	while(t--)solve();
	return 0;
}
```

---

## 作者：sSkYy (赞：0)

# [CF2112C Coloring Game](https://www.luogu.com.cn/problem/CF2112C)

## 题意

Alice 和 Bob 正在玩一个游戏，使用一个大小为 $n$（$1 \leq n \leq 5000$）的整数数组 $a$。

$a$ 数组中的元素已从小到大排序。

初始时，数组中的所有元素都是无色的。

首先，Alice 选择 $3$ 个元素并将它们染成红色。

然后 Bob 选择任意**一个**元素并将其染成蓝色（如果它已经是红色，则覆盖）。

如果红色元素的和**严格大于**蓝色元素的值，Alice 获胜。

你的任务是计算 Alice 选择 $3$ 个元素的方式数，使得无论 Bob 如何操作，Alice 都能获胜。

## 题解

假设 Alice 已经选了三个元素 $(a_i,a_j,a_k)$，满足 $i<j<k$。

假设 Bob 选了 $a_x$，显然 $a_x$ 只会是 $a_n$ 或者 $a_k$，所以有：
$$
s.t.
\left\{
\begin{array}{}
a_i+a_j+a_k>a_n\\
a_i+a_j>a_k
\end{array}
\right.
$$

转换一下，有 $a_n-a_i-a_j+1\leq a_k\leq a_i+a_j$，由于 $n$ 最大只有 $5000$，可以 $O(n^2)$ 的枚举 $a_i$ 和 $a_j$，再用树状数组维护出 $a_k$，做到 $O(n^2 \log V)$。

具体的，由于需要满足 $i<j<k$，所以我们要倒序枚举 $a_j$，同时维护 $a_k$，再枚举 $a_i$，最后统计合法的 $a_k$ 数量。

注意每个测试点结束后要清空树状数组，而且不能暴力清空，得写一个 $\text{del}$ 函数。

记得开 `long long`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
const int M=1e5+5;
int n;
int a[N];

//树状数组
int t[M];
void upd(int x){ for(;x<M;x+=x&(-x)) t[x]++; }
void del(int x){ for(;x<M;x+=x&(-x)) t[x]--; }
int ask(int x){
    if(x<=0) return 0;
    int res=0;
    for(;x;x-=x&(-x)) res+=t[x];
    return res;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int an=a[n];
    long long ans=0;
    for(int j=n-1;j>=2;j--){//枚举 a_j
        upd(a[j+1]);//维护 a_k
        for(int i=j-1;i>=1;i--)//枚举 a_i
            ans+=(long long)max(0,ask(min(an,a[i]+a[j]-1))-ask(an-a[i]-a[j]));//计算合法的 a_k 数量
    }
    cout<<ans<<"\n";
    for(int i=3;i<=n;i++) del(a[i]);//清空树状数组
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：chatoudp (赞：0)

Bob 在 Alice 选完后有 $2$ 种选法，一种是把 Alice 选的最大的变成蓝色，另一种是把剩下没被 Alice 选的最大的染成蓝色。

所以 Alice 要严格大于 Bob 需要满足（设 Alice 选了的三个数为 $x,y,z$ 且 $x\le y\le z$）： $x+y>z$ 且 $x+y+z>a_n$。

我们可以先固定 $z$，然后就发现 $x+y$ 需要大于 $\max(z,a_n-z)$，于是就转换成了求 $a$ 数组的前缀有多少种选择 $2$ 个数使得其和大于某个数的方法数的问题。

我们再枚举 $y$ 然后用二分即可。

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,a[5005],n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		long long ans=0;
		for(int i=1;i<=n;i++){
			int qwq=max(a[i],a[n]-a[i]);
			for(int j=2;j<i;j++) ans+=j-(upper_bound(a+1,a+j,qwq-a[j])-a); 
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

