# [NOISG 2016] LunchBox

## 题目描述

你是一家餐馆的经理。你准备了 $N$ 个饭盒，希望分发给一些学校。假设有 $m$ 所学校且第 $i$ 所学校需要 $k_i$ 个午餐盒。你的目标是将午餐盒分发到尽可能多的学校。同时，你有一个规则。对于第 $i$ 所学校，你要么不提供餐盒，要么必须提供 $k_i$ 个午餐盒。你能写一个程序来找到可以接收午餐盒的学校的最大数量吗？

## 说明/提示

### 样例解释

在这个样例中，答案是 $3$，因为 $3 + 4 + 2 \leq 10$ 且 $3 + 9 + 4 + 2 > 10$。

### 子任务

每个测试数据的时限为 $0.5$ 秒。您的程序将在满足以下限制的输入数据上进行测试：

| 子任务 | 分值 | 限制 |
|:-------:|:-----:|:------------:|
| 1       | 20    | 每组输入数据满足 $m = 1$, $0 < N \leq 60000$ 且 $0 < k_i \leq 30000$。 |
| 2       | 30    | 每组输入数据满足 $0 < m \leq 1000$, $0 < N \leq 60000$ 且 $0 < k_i \leq 1000$。 |
| 3       | 50    | 每组输入数据满足 $0 < N,m \leq 60000$ 且 $0 < k_i \leq 30000$。 |

## 样例 #1

### 输入

```
10 4
3
9
4
2```

### 输出

```
3```

# 题解

## 作者：wangshengyue (赞：4)

~~个人认为不值普及-。~~

本题要求在给定饭盒总数的限制下，最大化能满足需求的学校数量。每所学校有固定的饭盒需求量，要么完全满足（提供其所需的全部数量），要么不提供。

### 解题思路
本题一眼**贪心**：为了让更多学校得到满足，应优先选择需求最少的学校。


### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    vector<int>a(m);
    for(int i=0;i<m;++i)cin>>a[i];
    sort(a.begin(),a.end()); // 按需求从小到大排序
    int c=0,s=0;
    for(int k:a){
        if(s+k<=n){
            s+=k;
            c++;
        } // 累加需求，统计数量
        else break;
    }
    cout<<c<<endl;
    return 0;//完美结束
}
```

---

## 作者：Ghosty_Neutrino (赞：4)

## 题意
需要将准备好的 $M$ 个午餐盒分发给 $N$ 所学校。每所学校 $i$ 要求 $a_i$ 个午餐盒，规则是：给某所学校要么分发 $0$ 个，要么正好分发 $a_i$ 个。你的目标是让尽可能多的学校收到午餐盒，求最多能满足的学校数量。

## 分析
要最大化满足的学校数量，应优先选择需求最小的学校。因为较小的需求能在有限的午餐盒总数 $M$ 内容纳更多学校。将所有学校的需求 $a_i$ 从小到大排序，依次累加需求值，直到总和超过 $M$，此时累加的学校数量即为最大值。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int m,n,sum,c;
int main(){
    cin>>m>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    // 对需求从小到大排序
    sort(a.begin(),a.end());
    for(int num:a){
        if(sum+num<=m) {
            sum+=num;
            c++;
        }else break;
    }
    cout<<c;
    return 0;
}
```

---

## 作者：xuyixuan_123 (赞：4)

## 中文题意：
你是一家餐馆的经理。你准备了 $N$ 个饭盒，希望分发给一些学校。假设有 $m$ 所学校且第 $i$ 所学校需要 $k_i$ 个午餐盒。你的目标是将午餐盒分发到尽可能多的学校。同时，你有一个规则。对于第 $i$ 所学校，你要么不提供餐盒，要么必须提供 $k_i$ 个午餐盒。你能写一个程序来找到可以接收午餐盒的学校的最大数量吗？

选自[这个工单](https://www.luogu.com.cn/ticket/RXJW782926)。
## 思路
简单循环即可。

因为我们要求的是可以接收午餐盒的学校的最大数量，所以先要进行排序。

然后用 $ans$ 来存从第 $1$ 到第 $i$ 个的午餐盒之和，用 $cnt$ 来存可以接收午餐盒的学校的最大数量。

在循环的开始，我们先要用 $ans$ 加上 $k_i$，然后判断 $ans$ 是否大于 $n$。如果 $ans$ 大于 $n$，就输出 $i-1$，否则就继续循环下去。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k[60010],ans;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>k[i];
	}
	sort(k+1,k+m+1);
	for(int i=1;i<=m;i++){
		ans+=k[i];
		if(ans>n){
			cout<<i-1;
			break;
		}
	}
	return 0;
}
```

---

## 作者：zhouxiaodong (赞：2)

# 思路
把 $m$ 所学校的需求从小到大排序，优先满足需求小的学校，记录答案，最后输出。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[60010],ans=0,id=1;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+m+1);
	while(n>=a[id]&&id<=m)
	{
		n-=a[id];
		id++;
		ans++;
	}
	cout<<ans;
}
```

---

## 作者：Clare613 (赞：1)

## 思路：
贪心+排序。思路易得，自然是越小越先完成，我们只需要对于所有请求排序，从小到大，然后用 `while` 来计算最多可以满足几个请求即可。
## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
signed main () {
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	sort(a+1,a+m+1);
	int k=1;
	while(k<=m&&n>=a[k]){
		n-=a[k];
		k++;
	}
	cout<<k-1;
    return 0;
}
```

---

## 作者：Cake_W (赞：1)

## 洛谷P13646题解
[题目传送门](https://www.luogu.com.cn/problem/P13646)
## 分析
因为我们要让分到饭盒的学校尽量多，且对于每个学校，要么就不给饭盒，要么就给完，所以我们肯定要优先找需要饭盒数量少的学校。我们可以直接对每个学校需要的饭盒数量从小到大排序，再用循环遍历一遍，如果可以给这所学校拿饭盒，就给，不能给就直接输出。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=60005;
int n,m,a[N],ans=0,k;
int main()
{
	cin>>n>>m;
	k=n;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+1+m);//排序
	for(int i=1;i<=m;i++)
	{
		if(k>=a[i])
		{
			k-=a[i];
			ans++;
		}
		else
		{
			cout<<ans;
			return 0;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：1)

## 思路

凭直觉，应该选择从小到大排序的 $a$ 数组，然后选择前面任意个数，使得其和小于 $N$。

#### 怎么证明？

我们假设 $A_1\sim A_n$ 为 $a_1\sim a_n$ 的从小到大排序，设我们可以分发 $k$ 盒盒饭，若我们的思路不是最优解，若有另一个排列 $A'_1\sim A'_n$，能分发 $k'$ 盒。

不难发现选择 $A_1$ 和 $A'_1$，对 $N$ 造成的影响是 $N-A_1$ 和 $N-A'_1$，已知 $A_1$ 最小，故 $N-A_1<N-A'_1$，所有的 $i:1\sim n$ 都有 $N-A_i<N-A'_i$。所以我们的假设矛盾，故得证。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[60006];
signed main(){
    int N,m;
    cin>>N>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i];
    }
    sort(a+1,a+m+1);
    int sum=0;
    int cnt=0;
    for(int i=1;i<=m;i++){
        if(sum+a[i]>N)break;
        sum+=a[i];
        cnt++;
    }
    cout<<cnt;
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

此题考虑贪心策略，每次选择并满足所有学校里要求最少的那一个学校。

当加上最小的那一个也不够时，就可以输出答案了，也就是满足的学校数量。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c,ans,a[60001];//c表示已经用了多少午餐盒，ans表示给了多少个学校
int main(){
    cin >> m >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    sort(a+1,a+n+1);//排序，这样就可以每次选择最小值了
    for(int i=1;i<=n;i++){
        if(c+a[i]<=m){//够！
            c+=a[i];//加上需要的个数
            ans++;//答案+1
        }else{//如果不够，那么更大的也没希望了，退出！
            break;
        }
    }
    cout << ans;//输出答案
    return 0;
}
```

---

## 作者：ryf2011 (赞：1)

# 1.题目大意
给定长度为 $m$ 的数组 $k$，给定一个数字 $N$，以及一个计数变量 $cnt$ 且初始为 $0$，对于每一个 $k_i(1 \le i \le m)$，你可以让 $N$ 减去 $k_i$，并让 $cnt$ 加 $1$，你也可以不进行操作。你需要在 $N$ 始终大于等于 $0$ 的情况下最大化 $cnt$ 的值。

# 2.题目思路
考虑贪心。

要想让答案最大，我们就需要让 $N$ 每次减去最小的值，这样能使 $N$ 尽量减掉更多的 $k_i$。由此想到把 $k$ 数组从小到大排序，这样再从头遍历一遍数组，直到 $N$ 不能再减，就退出循环。

时间复杂度 $\mathcal O(N \log N)$，足以通过此题。

# 3.代码
注：代码仅供参考。

:::info[代码]{open}
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int max_m=60002;
int n,m,k[max_m],l,ans;
long long sum;
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&k[i]);
    }
    sort(k+1,k+m+1); //排序
    l=1; //初始化
    while(sum+k[l]<=n&&l<=m){
        sum+=k[l]; //求和
        ans++; //计数+1
        l++; //指针+1
    }
    printf("%d\n",ans);
    return 0;
}
```
:::

# 4.后记
更多内容，请移步至：

1. [$\color{red}\texttt{Luogu ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")；
2. [$\color{orange}\texttt{cnblogs（博客园） cnblogs2011ryf}$](https://www.cnblogs.com/cnblogs2011ryf)。

---

## 作者：alice_c (赞：1)

## 思路

考虑贪心。我们可以先给 $k$ 从小到大排序，然后枚举每一个 $k_i$，如果剩余的饭盒数量已经小于 $k_i$ 停止，否则答案加一。容易证明这一定是最优方案。

## 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n,m,a[60005],cnt;
int main()
{
    cin >> n >> m;
    for(int i=1;i<=m;i++)
        cin >> a[i];
    sort(a+1,a+m+1);
    for(int i=1;i<=m && n>=a[i];i++){
        cnt++;
        n-=a[i];
    }
    cout << cnt;
}
``````

---

## 作者：BlackHoles (赞：1)

### 正解

考虑一个很显然的贪心，将 $k_i$ 按照从小到大进行排序。先满足要求小的，在满足要求大的，必定是最优方案，即能满足最多的学校。

时间复杂度为排序，$O(m \log m)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, k[N], m;
int ans;
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> m >> n;
	for (int i = 0; i < n; ++i)
		cin >> k[i];
	sort(k, k + n);
	for (int i = 0; i < n; ++i) {
		if (m >= k[i]) {
			++ans;
			m -= k[i];
		}
		else break;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：wangziyang202511036 (赞：1)

# 题解：P13646 [NOISG 2016] LunchBox  
## 题目大意
现有 $N$ 个午餐盒及 $m$ 个学校，每个学校需要 $k_i$ 个午餐盒。对于每个学校，要么发 $k_i$ 个，要么一个都不发，求最多能发多少个学校。
## 思路  
因为要让发的学校数量尽可能多，而每个学校需要的数量又是固定的，所以肯定是需要的午餐盒数量**越少越好**。  
于是，我们可以先对所有需要的午餐盒数量进行排序，然后从小到大去判断，如果能发出去就发，不能就直接退出循环，这样可以保证发的学校数量一定是最多的。
## 完整代码  
时间复杂度 $O(m)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int M=6e4+5;
int a[M];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)//注意是m个学校不是n个学校
    {
        cin>>a[i];
    }
    sort(a+1,a+m+1);
    int ans=0;
    for(int i=1;i<=m;i++)
    {
        if(n>=a[i])//如果能发
        {
            ans++;
            n-=a[i];
        }
        else//不能发就说明之后都发不出去了
        {
            break;
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_aszxqw_ (赞：0)

一道非常水的贪心。     
贪心策略：    
进行一次排序，把小的放在前面大的放在后面，因为这样送出的饭盒最多。接着逐个枚举就可以了。    
### AC 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
    int n,m,ans=0;
    cin>>n>>m;
    int a[m+1];
    for(int i=1;i<=m;i++)cin>>a[i];
    sort(a+1,a+1+m);
    for(int i=1;i<=m;i++){
        if(n-a[i]>=0){
            n-=a[i];
            ans++;
        }
    }
    cout<<ans;
    return 0;
} 
```

---

## 作者：qiaohaoran123 (赞：0)

## 题意

有 $N$ 个午餐盒和 $m$ 个学校，第 $i$ 个学校需要 $k_i$ 个午餐盒，需要将午餐盒分发给学校。

对于第 $i$ 个学校，要么不分发午餐盒，要么分发 $k_i$ 个午餐盒，问最多有多少个学校能接收到午餐盒。

## 思路

将 $k_i$ 从小到大排序，从 $k_i$ 最小的学校开始分发，直到剩余的饭盒不能继续分发或所有学校都分发完，分发到饭盒的个数就是答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,m,k[60006],ans;
int main(){
	cin>>N>>m;
	for(int i=1;i<=m;i++)cin>>k[i];
	sort(k+1,k+m+1);
	for(int i=1;i<=m;i++){
		if(N-k[i]>=0)ans++,N-=k[i];
		else break;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：TLE_qwq (赞：0)

### 题目大意
餐厅有 $N$ 份盒饭，需分给 $m$ 所学校（每所学校需 $k_i$ 份），要么满足某学校需求，要么就不给，求最多能满足的学校数量。

### 解题思路
简单题，不难想到，要最大化满足的学校数量，一定要优先满足需求较小的学校。所以，将所有学校的需求按从小到大排序，然后依次累加，直到总盒饭数超过 $N$。这样就能保证满足最多的学校。

### 解决代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, m;
    cin >> N >> m;
    vector<int> k(m);
    for (int i = 0; i < m; i++) {
        cin >> k[i];
    }
    sort(k.begin(), k.end());
    int sum = 0;
    int count = 0;
    for (int i = 0; i < m; i++) {
        if (sum + k[i] <= N) {
            sum += k[i];
            count++;
        } else {
            break;
        }
    }
    cout << count << endl;
    return 0;
}
```

---

## 作者：b_donk (赞：0)

### 题目大意

你是一个餐厅经理，准备了 $N$ 个午餐盒，要分发给 $M$ 所学校。每所学校需要 $k_i$ 个午餐盒。求出最多满足几个学校的请求。

### 题目思路

贪心算法，让尽可能多的学校得到午餐盒，对午餐盒数量进行排序，优先给需要午餐盒少的学校。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1145140];
main() {
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i ++) cin >> a[i];
	sort(a, a+m);
	int ans = 0;
	for(int i = 0; i < m; i ++) {
		n -= a[i];
		if(n < 0) break;
		ans ++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：yanghongzheng (赞：0)

# 题解：P13646 [NOISG 2016] LunchBox
## 题意
有 $N$ 个午餐盒，要分给 $m$ 所学校。

第 $i$ 所学校要么得到 $k_i$ 个午餐盒，要么一个都不给。

问最多能让多少所学校拿到午餐盒。



## 思路分析
我们希望让尽可能多的学校拿到午餐盒，而每所学校的需求是固定的。

显然，如果我们想尽量多满足学校，就应该优先满足需求最少的学校，这样可以节省午餐盒，让剩余的午餐盒去满足更多学校。

根据此思路，我们可以将 $k$ 进行升序排序，从需求量最少的 $k_1$ 开始，依次发放午餐盒，直到手里的午饭盒不够下一个学校为止。

## 代码
### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m,cnt=0;
    long long k[114514];
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> k[i];
    }
    sort(k,k+m);
    for(int i=0;i<m;i++){
        if(n<k[i]){
            cout << cnt << endl;
            return 0;
        }
        n -= k[i];
        cnt++;
        if(n==0){
            cout << cnt << endl;
            return 0;
        }
    }
    cout << cnt << endl;
}
```
### Python
```
n,m = map(int,input().split())
k = []
cnt = 0
for i in range(m):
    k.append(int(input()))
k.sort()
for i in range(m):
    if n >= k[i]:
        n -= k[i]
        cnt += 1
    else:
        break
    if n == 0:
        break
print(cnt)
```

---

## 作者：封禁用户 (赞：0)

## 题目大意
将 $N$ 份午餐分给 $M$ 所学校，第 $i$ 学校有 $k_i$ 个人。对于第 $i$ 所学校，要么分给该学校 $k_i$ 份午餐，要么就一份都不分。求最多能分给几个学校。
## 解题思路
只有当分给的学校人数较少时才能分给尽可能多的学校。因此可以将学校人数升序排序，从低位开始尝试，直到 $N$ 耗尽或**已全部分完**。
## 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int k[100000];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>k[i];
	}
	sort(k+1,k+1+m);
	int i=1;
	while(i<=m&&k[i]<=n)
	{
		ans++;
        n-=k[i];
        i++;
	}
	cout<<ans;
	return 0;
}
```

---

