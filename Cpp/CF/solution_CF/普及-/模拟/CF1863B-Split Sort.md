# Split Sort

## 题目描述

You are given a permutation $ ^{\dagger} $ $ p_1, p_2, \ldots, p_n $ of integers $ 1 $ to $ n $ .

You can change the current permutation by applying the following operation several (possibly, zero) times:

- choose some $ x $ ( $ 2 \le x \le n $ );
- create a new permutation by: 
  - first, writing down all elements of $ p $ that are less than $ x $ , without changing their order;
  - second, writing down all elements of $ p $ that are greater than or equal to $ x $ , without changing their order;
- replace $ p $ with the newly created permutation.

For example, if the permutation used to be $ [6, 4, 3, 5, 2, 1] $ and you choose $ x = 4 $ , then you will first write down $ [3, 2, 1] $ , then append this with $ [6, 4, 5] $ . So the initial permutation will be replaced by $ [3, 2, 1, 6, 4, 5] $ .

Find the minimum number of operations you need to achieve $ p_i = i $ for $ i = 1, 2, \ldots, n $ . We can show that it is always possible to do so.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ n = 1 $ and $ p_1 = 1 $ , so there is nothing left to do.

In the second test case, we can choose $ x = 2 $ and we immediately obtain $ p_1 = 1 $ , $ p_2 = 2 $ .

In the third test case, we can achieve the minimum number of operations in the following way:

1. $ x = 4 $ : $ [6, 4, 3, 5, 2, 1] \rightarrow [3, 2, 1, 6, 4, 5] $ ;
2. $ x = 6 $ : $ [3, 2, 1, 6, 4, 5] \rightarrow [3, 2, 1, 4, 5, 6] $ ;
3. $ x = 3 $ : $ [3, 2, 1, 4, 5, 6] \rightarrow [2, 1, 3, 4, 5, 6] $ ;
4. $ x = 2 $ : $ [2, 1, 3, 4, 5, 6] \rightarrow [1, 2, 3, 4, 5, 6] $ .

## 样例 #1

### 输入

```
5
1
1
2
2 1
6
6 4 3 5 2 1
3
3 1 2
19
10 19 7 1 17 11 8 5 12 9 4 18 14 2 6 15 3 16 13```

### 输出

```
0
1
4
1
7```

# 题解

## 作者：One_JuRuo (赞：4)

## 思路

对于每次操作，会把序列分成两个部分，两部分之间不会排序。

考虑仅每次排一个数字，理由如下：

假设已经排好了 $1,2,3\cdots i-1$ 的顺序，对于数字 $i$，如果 $i+1$ 在该数字的前面，那么 $k$ 应选择为 $i+1$，这样才能排好 $i$ 和 $i+1$。如果选择的 $k$ 大于 $k+1$ 那么还是需要再排一次使 $i$ 和 $i+1$ 的顺序正确，操作数不变，只是操作顺序不同。

所以我们可以枚举 $i$，如果 $i+1$ 在前面，则需要排序，如果在后面，则不需要排序，记录排序次数就好。

因为需要快速知道两个数的位置关系，可以提前存下来。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a,ans;
map<int,int>m;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n),ans=0;
		for(int i=1;i<=n;++i) scanf("%d",&a),m[a]=i;
		for(int i=1;i<n;++i) if(m[i+1]<m[i]) ++ans;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：1)

### 题意

多组数据。

给你一个长度为 $n$ 的序列，每一次可以选一个数 $x$，进行以下操作：

* 把小于 $x$ 的给按顺序写下。
* 把大于等于 $x$ 再按顺序写到上面操作的序列后。

求最少的次数让序列变成从小到大有序的。

保证给的序列是 $1\sim n$ 的一个排列。

### Solution

我们发现如果一个数，可以被比他小的数变成有序的的话，就没有必要选这个数，手模一下样例也可以看出选数的先后顺序对答案没有影响。

我们考虑如何最优化。

记录一个 $cnt$，初始值为 $n$。

我们从序列最右段开始扫，如果遇到了一个 $a_{i} = cnt$，那么我们把 $cnt$ 减一，如果能还找到 $cnt$ 的话，说明上一个 $cnt$ 值，如果选了当前的 $cnt$ 可以被排成有序的。

然后扫到最左端，当前的 $cnt$ 就是我们第一个操作的数。

直到 $cnt = 0$，我们就可以排好序了，此时最少的操作次数就是我们扫了几遍这个序列减一，因为最后一次扫的部分实际上已经有序了。

我们开一个 $pos$ 记录每一个数的出现位置，然后给他判断比他小一的是不是在他左边，然后就代替了我们扫一遍这 $n$ 个数的过程，复杂度也从 $O(n^2)$ 降到了 $O(n)$。

具体细节看代码。

```cpp
/*
 * @Author: Aisaka_Taiga
 * @Date: 2023-08-30 23:17:01
 * @LastEditTime: 2023-08-30 23:29:10
 * @LastEditors: Aisaka_Taiga
 * @FilePath: \Desktop\CFB.cpp
 * 心比天高，命比纸薄。
 */
#include <bits/stdc++.h>

#define int long long
#define N 1000100

using namespace std;

int t, n, a[N], vis[N];

signed main()
{
    cin >> t;
    while(t --)
    {
        cin >> n;
        for(int i = 1; i <= n; i ++) cin >> a[i], vis[a[i]] = i;
        int cc = n, cnt = 0;
        while(1)
        {
            while(vis[cc - 1] < vis[cc]) cc --;
            cc --;
            cnt ++;
            if(cc == -1) break;
        }
        cout << cnt - 1 << endl;
    }
    return 0;
}
// 10 19 7 1 17 11 8 5 12 9 4 18 14 2 6 15 3 16 13
// 19,17,14,10,7,5,4,1
```

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1863B)
这是打模拟赛时没做出来的题（本蒟蒻太逊了）

我打比赛时的思路是如果序列不符合要求（$q[i] \ne i$）就进行一次操作，直到符合要求。

于是写了个暴力。

代码如下：
```cpp
//两个数组轮流换 
//四层循环暴力
//前两个点没T是我没想到的
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005][2],num,cnt;
bool zt,f;
int main(){
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
        scanf("%d",&n);
        zt=0;
        for(int i=1;i<=n;i++)scanf("%d",&a[i][zt]);
        for(cnt=0;;cnt++){
            f=0;
            for(int i=1;i<=n;i++)
                if(a[i][zt]!=i){
                    num=0;
                    for(int j=1;j<=n;j++)
                        if(a[j][zt]<a[i][zt])
                            a[++num][1-zt]=a[j][zt];
                    for(int j=1;j<=n;j++)
                        if(a[j][zt]>=a[i][zt])
                            a[++num][1-zt]=a[j][zt];
                    zt=1-zt;
                    f=1;
                    break;
                }
            if(f==0)break;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
```
### [结果](https://www.luogu.com.cn/record/133395251)
说实话，这题的样例很好，一点误导的成分都没有，甚至在引导你。

研究样例可以发现，当数组中的一个元素大于它后面的元素时，必须进行一次操作，否则这两个元素的相对位置不会发生改变（该元素不为最后一个元素），因此本题就是求相邻的两个数中有多少次前面的数比后面的数大的情况。

有点类似于求逆序对数量，不过要求是相邻的。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005],b[100005],ans;
//b数组用于存储a数组中元素的位置
int main(){
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
        scanf("%d",&n);
        ans=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            b[a[i]]=i;
        }
        for(int i=1;i<n;i++)
            if(b[i]>b[i+1])
                ans++;
        printf("%d\n",ans); 
    }
}
```
[终于](https://www.luogu.com.cn/record/133409350)

这么简单的一道题我比赛时竟然还爆零了，大悲。

---

## 作者：copper_ingot (赞：0)

比赛时见到的，一遍切了。我真棒。

[题目传送门](https://www.luogu.com.cn/problem/CF1863B)

我的思路与其他人不一样。

因为 $p$ 是 $1 \sim n$ 的全排列，所以首先建一个 $b$ 数组，$b_i$ 表示 $i$ 在 $p$ 中出现的位置。

然后寻找 $b$ 中有多少个“长上升连续子序列”。

此处“长上升连续子序列”指 $b$ 的一个连续子序列 $b_i \sim b_j$，满足：

- 对于每个 $i < k \le j$，有 $b_k > b_{k - 1}$。

- 若 $i \neq 1$，$b_i < b_{i - 1}$。

- 若 $j \neq n$，$b_j > b_{j + 1}$。

然后把统计出来的答案减一即可。

因为每操作一次就能把一个“长上升连续子序列”中的下标 $i \sim j$ 合起来（最后一次可以合并两个），所以该方案可行。

$code$：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, p[100001], b[100001], cnt;
int main(){
    scanf("%d", &t);
    while (t--){
        scanf("%d", &n);
        for (register int i = 1; i <= n; i++){
            scanf("%d", &p[i]);
            b[p[i]] = i;//存b数组
        } cnt = 0;
        for (register int i = 2; i <= n; i++)
            if (b[i] < b[i - 1]) cnt++;//统计
        printf("%d\n", cnt);
    }
    return 0;
}
```

---

## 作者：guozhe6241 (赞：0)

这题也是比赛赛题，赛时手打了个快排，然后 $T$ 了，$40$ 分。

# 题目传送门

[CF1863B](https://www.luogu.com.cn/problem/CF1863B)

# 题意

见题面 [CF1863B](https://www.luogu.com.cn/problem/CF1863B)

# 思路

这道题本质就是快排，如果当前数字大于后面的数字，就要进行一次变换。注意此

题有多组数据。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5; 
int t,n,a[maxn],ans,x[maxn];
int main(){
	cin>>t;
	while(t--){
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			x[a[i]]=i;
		}
		for(int i=1;i<n;++i){
			ans+=(x[i]>x[i+1]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/133234119)

---

## 作者：ys_kylin__ (赞：0)

这题考到了，当时把我折磨死了，结果发现只是橙。。。

题意：给一个序列，可以进行操作：选定 $x$，将 $< x$ 的数抽出，组成一个新序列，放到原序列的前面。求经过多少次操作后，能给原序列排好序。

首先求出按当前数组从小到高排序时的原下标，因为原数组已经离散化过了，用桶排很方便。然后不难发现，当其中一个数他于它后面相邻的数时，必须通过操作后面的数来排好序。那就是求相邻的逆序对，非常简单，$O(n)$ 解决。

注意有多组数据。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int mp[100005],a[100005];
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int n,ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			mp[a[i]]=i;
		}
		for(int i=1;i<n;i++) {
			if(mp[i]>mp[i+1]) ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：feiji_code (赞：0)

##  题目：
## Split Sort



给定一个 $1 \sim n$ 的排列 $q$，你可以多次进行以下操作：

- 新建一个初始为空的序列 $q$；
- 选择一个整数 $x$（$2 \leq x \leq n$）；
- 按照在 $p$ 中出现的顺序将所有小于 $x$ 的数添加到序列 $q$ 末尾。
- 按照在 $p$ 中出现的顺序将所有大于等于 $x$ 的数添加到序列 $q$ 末尾。
- 用序列 $q$ 替代排列 $p$。

你需要找到使 $\forall i \in [1,n]$，$p_{i} = i$ 的最小操作次数。

本题有多组测试数据，$1 \leq T \leq 10^{3}$，$1 \leq n,\sum n \leq 10^{5}$。

## 思路：
可以用下标的相邻逆序对解决问题，每一个相邻逆序对都代表一次操作，全部加起来就是答案了。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114514],mp[114514];
int main(){
	int t;
	cin>>t;
	while(t--){
		int ans=0;
		memset(a,0,sizeof(a));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],mp[a[i]]=i;
		for(int i=1;i<n;i++) if(mp[i+1]<mp[i]) ans++;
		cout<<ans<<endl;
	}

}

```


---

## 作者：hfjh (赞：0)

# CF1863B Split Sort 题解
## 题意

给定一个 $1 \sim n$ 的排列 $p$，你可以多次进行以下操作：

- 新建一个初始为空的序列 $q$；
- 选择一个整数 $x$（$2 \leq x \leq n$）；
- 按照在 $p$ 中出现的顺序将所有小于 $x$ 的数添加到序列 $q$ 末尾。
- 按照在 $p$ 中出现的顺序将所有大于等于 $x$ 的数添加到序列 $q$ 末尾。
- 用序列 $q$ 替代排列 $p$。

你需要找到使 $\forall i \in [1,n]$，$p_{i} = i$ 的最小操作次数。

本题有多组测试数据，$1 \leq T \leq 10^{3}$，$1 \leq n,\sum n \leq 10^{5}$。

## 题解

例如样例：$10, 7, 1, 8, 5, 9, 4, 2, 6, 3$。

我们发现 $123$ 连续，第一次选取 $4$ 。

$4$ 连续，第二次选取 $5$。

$56$ 连续，选取 $7$。

$789$ 连续，选取 $10$。

至此操作完。

最优操作就是按上述操作。

我们设 $w_i$ 表示 $i$ 出现的位置，那么答案也就是 $\sum_{i=2}^n[w_i < w_{i-1}]$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10; 
int t, n, a[N], ans, w[N];
void input(){
	cin>> n;
	for(int i = 1; i <= n; ++i) cin>> a[i], w[a[i]] = i; 
}
void op(){
	for(int i = 1; i < n; ++i){
		ans += w[i] > w[i + 1];
	}
} 
int main(){
	cin >> t;
	while(t--){
		ans = 0;
		input();
		op();
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：shipeiqian (赞：0)

# CF1863B 题解

## 题意

对一个排列 $p$ 进行任意次操作，每次选择一个 $x(2\leq x\leq n)$，然后按顺序写下所有 $p_i(p_i<x)$，再按顺序写下所有 $p_i(p_i\geq x)$。求出把排列变成 $1\dots n$ 的最小操作次数。

## 思路

可以发现，如果选择了一个 $x$ 后，对于所有小于 $x$ 的数，他们的顺序是从小到大，那么就可以选择这个 $x$，从而将 $1\dots x-1$ 直接排好，而最后剩下的一组无需操作，因为会比先前选择的所有 $x$ 大，会直接排到后面。

例如 $6\ 4\ 3\ 5\ 2\ 1$ 可以最少分成 $5$ 组：$\color{red}{6}\ \color{orange}{4}\ \color{blue}{3}\ \color{orange}{5}\ \color{green}{2}\ \color{black}{1}$，那么答案就是 $4$。

形式化地，对于所有的 $i<j$，如果 $p_i=p_j-1$，那么选择 $x=p_j+1$ 后，$p$ 的前 $x-1$ 个数会变成 $1,\dots,x-1$，所以选择更大且满足条件的 $x$ 是最优选择。

## 做法

可以遍历数组，用 map 记录一个数的前一个是否出现，如果未出现过，那么就是新的一组，更新答案，并记录进 map 即可。

## Code

```cpp
//核心代码
void solve(){
    cin >>n;
    int ans=n-1;
    map<int,int>ok;
    while(n--){
        int x;
        cin >>x;
        if(ok[x-1])ans--;
        ok[x]=1;
    }
    cout <<ans <<"\n";
}
```

---

