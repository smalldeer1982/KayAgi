# [USACO25FEB] Making Mexes B

## 题目描述

给定一个包含 $N$ 个非负整数的数组 $a$，$a_1, a_2, \dots, a_N$（$1\le N\le 2\cdot 10^5$，$0\le a_i\le N$）。在一次操作中，你可以将 $a$ 的任一元素修改为任意非负整数。

一个数组的 mex 是它不包含的最小非负整数。对于范围 $0$ 到 $N$ 内的每一个 $i$，计算使 $a$ 的 mex 等于 $i$ 所需要的最小操作次数。

## 说明/提示

样例 1 解释：

- 为使 $a$ 的 mex 等于 $0$，我们可以将 $a_4$ 修改为 $3$（或任何正整数）。在得到的数组 $[2, 2, 2, 3]$ 中，$0$ 是数组不包含的最小非负整数，因此 $0$ 是数组的 mex。
- 为使 $a$ 的 mex 等于 $1$，我们不需要进行任何修改，因为 $1$ 已经是 $a = [2, 2, 2, 0]$ 中不包含的最小非负整数。
- 为使 $a$ 的 mex 等于 $2$，我们需要修改 $a$ 的前三个元素。例如，我们可以将 $a$ 修改为 $[3, 1, 1, 0]$。

- 测试点 $2\sim 6$：$N\le 10^3$。
- 测试点 $7\sim 11$：没有额外限制。

## 样例 #1

### 输入

```
4
2 2 2 0```

### 输出

```
1
0
3
1
2```

# 题解

## 作者：chenqishuo (赞：4)

# 思路

这道题他是求在对于 $i$ 最少需要修改多少次才能使 $0$ 到 $i$ 中不包含的最小非负整数为 $i$。

对于 $i$ 我们要求不包含的最小非负整数，自然就要知道 $i$ **之前**不包含的最小非负整数的个数。如果对于 $i$ 我们再去循环 $0$ 到 $i - 1$ 统计数量的话，那么复杂度就会变成 $O(n^2)$，看一看数据范围 $1 \le N \le 2 \times 10^5$ 不用说肯定炸烂掉。

那怎么办呢？我们可以定义一个 $cnt$ 变量在枚举 $i$ 时来统计 $i$ 之前不包含的最小非负整数的个数。在统计之前需要将输入的数进行一个整合，就是计算每个数的数量，当这个数的数量为 $0$ 时，$cnt$ 增加 $1$，也就是 `cnt++;`。

接下来就是判断至少需要修改多少次。经过观察我们可以发现：

1. 当 $cnt$ 为 $0$ 时，说明 $i$ 之前没有不包含的最小非负整数。这时如果 $i$ 的数量为 $0$，那么 $i$ 为不包含的最小非负整数，修改次数就为 $0$ 次。

2. 当 $cnt$ 为 $0$ 时，如果 $i$ 的数量不为 $0$，意味这 $i$ 为包含的非负整数，要令不包含的最小非负整数为 $i$，就需要把所有的 $i$ 修改为不为 $i$ 的值，修改次数就为 $i$ 的个数。

3. 当 $cnt$ 不为 $0$ 时，说明 $i$ 之前有不包含的最小非负整数。就需要把这 $cnt$ 个数各用一个数代替，如果 $i$ 这个数的个数小于等于 $cnt$ 时，我们就可以用所有的 $i$ 和其他有多余的数进行修改，直到刚好将这 $cnt$ 个数都代替，修改次数就为 $cnt$。

4. 当 $cnt$ 不为 $0$ 时，且 $i$ 这个数的个数大于 $cnt$ 时，我们就可以用所有的 $i$ 进行修改，直到刚好将这 $cnt$ 个数都代替，剩余的部分全部修改不为 $i$ 数，修改次数为 $i$ 的个数。

剩下的就可以交给代码实现了。

# 代码

###  时间复杂度：$O(n)$

```cpp
#include <iostream>

using namespace std;

const int N = 2e5 + 10;
int a[N];

int main()
{
	int n;
	cin >> n;
	for(int i = 1;i <= n; ++ i)
	{
		int x;
		cin >> x;
		a[x] ++; //计算每个相同的数的数量
	}
	
	long long cnt = 0;
	
	for(int i = 0;i <= n; ++ i)
	{
		if(cnt > a[i])
			cout << cnt << endl;
		else cout << a[i] << endl;
//------------------------------------------------
//计算i之前不包含的最小非负整数的个数
		if(a[i] == 0)
			cnt ++;
	}
	return 0;
}
```

---

## 作者：Starry_Sky_135 (赞：3)

**思路**

---

先定义一个 $t$ 数组，$t_i$ 表示 $i$ 在数组中出现的次数。

若要让 $i$ 成为没出现过的最小非负整数，需要满足以下两个条件：

*    $i$ 没出现过
*    $0$ 到 $i-1$ 都出现过


于是想到前缀和。可以定义一个 $sum$ 数组，用来统计 $0$ 到  $i-1$ 的出现次数。

```cpp
sum[i]=sum[i-1]+(!t[i-1]);//如果i-1没有出现就在sum[i-1]的基础上+1
```
但是，还需要 $i$ 没有出现过，将 $i$ 变为没有出现过的最小操作次数是 $t_i$，于是知道答案为 $sum_i$ 和 $t_i$ 取最大值。

特别地，当 $i=0$ 时，答案为 $t_0$。


---

**AC 代码**


---


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+8;
int n;
int t[N],sum[N];
int main()
{
	cin>>n;
	for(int i=1,x;i<=n;i++)
	{
		cin>>x;
		t[x]++;
	}
	cout<<t[0]<<endl;
	
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(!t[i-1]);
	
	for(int i=1;i<=n;i++) cout<<max(sum[i],t[i])<<endl;
    return 0;
}
```

---

## 作者：Eason0324 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11837)

## 思路
先看样例。

首先对于 $0$ 来说，因为 $a_i$ 中有一个 $0$，所以要把这个 $0$ 调走。

于是我们就想到用计数器去维护每一个数的数量。

接下来看到 $4$。如果按照第一种去算，就会发现答案是 $0$，显然是错误的。可以看到， $1$ 和 $3$ 在 $a_i$ 中是没有的，得把它补上。

于是我们可以创建另一个数组维护前面有多少空缺。

最后是 $2$。你可以把其中部分 $2$ 变成前面空缺的 $1$，还有一部分变成其他的数。


可以发现答案就是两个中的最大值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200009],n,ji[200009],le[200009];
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		ji[a[i]]++;
	}
	if(!ji[0]) le[0]=1;
	for(int i=1;i<=n;i++){
		le[i]=le[i-1];
		if(!ji[i]) le[i]++;
	}
    cout<<ji[0]<<endl;
	for(int i=1;i<=n;i++){
		cout<<max(ji[i],le[i-1])<<endl;
	}
}
```

---

## 作者：DeepSleep_Zzz (赞：1)

**begin**

[P11837 [USACO25FEB] Making Mexes B](https://www.luogu.com.cn/problem/P11837)

# 思路

按照题目描述我们可以得到以下 $2$ 个条件：

- $i$ 不能在序列 $a$ 中出现。
- 对于任意 $0 \le j < i $，保证其至少在序列 $a$ 中存在一次。

我们可以开一个桶数组来记录每个数字出现的次数（条件 1）。

对于条件 2，我们用 $sum_i$ 表示 $0\sim i-1$ 完全没有出现过的数字的个数（其中 $i\ge1 $）。我们用 $flag$ 来表示 $i-1$ 这个数字是否出现过，出现过为 $0$ 未出现过为 $1$，那么我们有：

$$sum_i=sum_{i-1}+flag$$

注意最后的答案并不是 $sum_i+t_i$。

我们发现可以用 $t_i$ 去填补 $sum_i$，所以最后的答案应该是 $\max(t_i,sum_i)$。

然后为了数组越界的不必要麻烦，我们直接把 $i=0$ 的情况单拎出来，直接特判即可。

## 小小的空间优化

观察思路，我们需要开 $t$ 和 $sum$ 两个数组，但是 $sum$ 数组我们只用到了 $sum_i$ 和 $sum_{i-1}$。所以我们可以开一个 $lst$ 来存储 $sum_{i-1}$，这样就省下了一些空间。

# Code


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll M=2e5+10;
ll n,t[M],a,sum,lst; // 第一个 lst 为 0
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for (ll i=1;i<=n;i++) cin>>a,t[a]++; // 桶
    cout<<t[0]<<"\n"; // 第一个情况的特判
    for (ll i=1;i<=n;i++)
    {
        sum=lst+(t[i-1]?0:1),lst=sum;
        cout<<max(sum,t[i])<<"\n";
    }
    return 0;
}
```

**end**

---

## 作者：封禁用户 (赞：1)

### 思路

注意到本题每一次询问需要满足 $2$ 个条件：
- $i$ 在数组中不出现。
- 对于 $0 \le j<i$ 的每个 $j$，$j$ 在数组中出现至少 $1$ 次。

因此，对于 $0 \le i \le N$ 的每一个 $i$，我们需要统计 $2$ 个量：
- $i$ 在数组中出现的次数，记为 $a_i$。
- 对于 $0 \le j<i$ 的每一个 $j$，有多少个 $j$ 在数组中出现过，记为 $b_i$。

对于第 $1$ 个条件，我们需要把 $a_i$ 个 $i$ 都修改掉，至少要修改 $a_i$ 次。对于第 $2$ 个条件，我们需要让数组中所有小于 $i$ 的非负整数至少出现 $1$ 次，至少要修改 $i-b_i$ 次。

最终，对于每一个 $i$，答案就是 $a_i$ 和 $i-b_i$ 的较大值。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=2e5+5;
int a[N],b[N];
int n;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0); 
	cin>>n;
	for(int i=1;i<=n;i++){
		int k;
		cin>>k;
		a[k]++;
	}
	b[0]=int(bool(a[0]));
	for(int i=1;i<=n;i++){
		b[i]=int(bool(a[i]))+b[i-1];
	}
	for(int i=0;i<=n;i++){
		//cout<<"a["<<i<<"]="<<a[i]<<endl;
		if(i==0)
		cout<<a[i]<<endl;
		else cout<<max((i-b[i-1]),a[i])<<endl;
	}
} 
```

---

## 作者：sen_lin114514 (赞：1)

# P11837 \[USACO25FEB] Making Mexes B

### 思路

观察可发现，要让 $i$ 成为它前面都没出现过的最小非负整数。也就是，在 $i$ 前，$1$ 到 $(i - 1)$ **的数字** 中都出现过。

于是，我们输入时，直接记录 $x$ 出现的次数即可。

对于每一个 $i$，我们可以使用类似前缀和的思想，记录一个变量 $t$，表示 $1$ 至 **目前的** $i-1$ 中未出现的数字的数量，这个 $i$ 的答案，即是 $\max(t, a_i)$ , $a_i$ 表示 $i$ 出现的数量。

### 细节

对于 $i = 0$ 时，直接输出 $0$ 的数量即可，即 $a_0$。

### AC 代码

```cpp
#include <iostream>

const int N = 1145140;

int n;
int a[N];

int main()
{
	std :: cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		int x;
		std :: cin >> x;
		a[x] ++;
	}
	std :: cout << a[0] << "\n";
	int ans = 0;
	for (int i = 1 ; i <= n ; i ++)
	{
		ans += (!a[i - 1]);
		std :: cout << std :: max(ans,a[i]) << "\n";
	}
}
```

---

## 作者：George222 (赞：1)

闲话：庆祝本蒟蒻 AK USACO 25FEB B！个人认为这题是铜里最水的一道。

## 思路

要让数组 $a$ 中的 $mex = i$，我们需要让数组 $a$ 满足两个条件：

   - $\forall x \in \{0, 1, \dots, i-1\}, \quad x \in a$
   - $i \notin a$

对于代码实现，我们可以先预处理一个数组 $cnt$，$cnt_i$ 表示数组 $a$ 中数字 $i$ 的个数。

对于每个 $mex$ 的询问，我们先遍历 $0 \sim i - 1$，查看有多少个数缺失，设为 $miss$（条件 1）；然后再调取 $cnt_i$ 查看有多少它本身在数组 $a$（条件 2）。

此时，我们已经得到了解法，但是这种解法在每次解决 $\forall x \in \{0, 1, \dots, n\}, \quad x = mex$ 时都要重新计算 $miss$，时间复杂度 $O(n^2)$，显然过不了 $2 \times 10^5$，我们需要优化。

而显然，$miss$ 可以预处理进行优化，具体思路类似递推或 dp。

设 $miss_i$ 为 $0 \sim i - 1$ 中有多少个数缺失，而 $miss_i$ 可以从 $miss_{i - 1}$ 转移：

$
miss_i =
\begin{cases}
    miss_{i-1} + 1, & \text{if } cnt_{i-1} \neq 0 \\
    miss_{i-1}, & \text{if } cnt_{i-1} = 0
\end{cases}
$

时间复杂度约为 $O(n)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
int cnt[200005];
int miss[200005];

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		a.push_back(x);
		cnt[x]++;
	}
	sort(a.begin(), a.end());
	for (int i = 1; i <= n; i++)
	{
		if (cnt[i - 1] == 0)
			miss[i] = miss[i - 1] + 1;
		else
			miss[i] = miss[i - 1];
	}
	
	int q = 0;
	while (q <= n)
	{
		int now = cnt[q] - miss[q];
		if (now >= 0)
			cout << cnt[q] << "\n";
		else
			cout << cnt[q] + abs(now) << "\n";
		q++;
	}
	return 0;
}

```

---

## 作者：qhr2023 (赞：1)

## solution

简单贪心。

要让 $i$ 成为没出现过的最小非负整数，需满足以下两点。
* $i$ 的出现次数为 $0$。
* $1$ 到 $i-1$ 都出现过。

我们的修改一定是为了使这两点成立。若能让尽可能多的 $i$ 改为 $1$ 到 $i-1$ 中任一个没出现过的数一定是更优的。

记 $S$ 表示 $1$ 到 $i-1$ 中没出现过的数的数量，$a_i$ 表示 $i$ 的出现次数，所以说 $i$ 的答案就是 $\max(S, a_i)$。特别的，当 $i=0$ 时，答案就是 $0$ 出现的次数，即 $a_0$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[200005], sum;
int main () { 
	cin >> n;
	for (int i=1, x; i<=n; ++i) 
		cin >> x,
		a[x]++;
	cout << a[0] << '\n';
	for (int i=1; i<=n; ++i) 
		sum+=(!a[i-1]),
		cout << max(sum, a[i]) << '\n';
	return 0;
}
```

---

## 作者：New_Void (赞：1)

# [P11837 [USACO25FEB] Making Mexes B](https://www.luogu.com.cn/problem/P11837)

### 思路
大致思路就是：

- 补全缺失的数的操作次数。

- 移除 $i$ 的操作次数。

所以这道题，我们可以使用前缀和数组，来判断：

使用一个数组 $qs[]$，其中 $qs[i]$ 表示 $0$ 到 $i-1$ 中有多少个数没有在数组中出现过。

这个前缀和用于快速计算补全缺失数的操作次数。

### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    int arr[n+2]={0};
    int num[n+2]={0};
    for (int i=0;i<n;i++){
        cin>>arr[i];
        if (arr[i]<=n){
            num[arr[i]]++;
        }
    }
    int qs[n+2]={0};
    for (int i=1;i<=n+1;i++){
        qs[i]=qs[i-1];
        if (i-1<=n && num[i-1]==0){
            qs[i]++;
        }
    }
    int ans[n+2];
    for (int i=0;i<=n;i++){
        int c=0;
        if (i==0){
            c=0;
        }
        else{
            c=qs[i];
        }
        ans[i]=max(num[i],c);
    }
    for (int i=0;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}

```

---

## 作者：ZSYhaouuan (赞：1)

题目不难，我就不概括了吧。

容易发现，我们要让数组中不包含的最小非负整数等于 $i$ 的话，必须满足以下两个条件：

- 数组中包含从 $0$ 到 $i-1$ 所有整数。不满足的话，我们要求的答案一定小于 $i$。

- 数组中不包含等于 $i$ 的整数。不满足的话，我们要求的答案一定大于 $i$。

我们可以先用一个桶维护每一个数出现的次数。在循环输出答案的时候，用变量 front 表示从 $0$ 到 $i-1$ 不同整数的个数，变量 now 表示等于 $i$ 的整数个数。

分析 now 对答案的贡献：因为数组不能包含等于 $i$ 的整数，这 now 个数都要改。

再来看 front 的贡献：如果 now 个数大于需更改的数量，则无需再次修改；反之，则还需要改需求量与 now 的差次。

---

讲的比较细，还是看不懂的看代码吧：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 2e5+200;
ll n;
ll a[N], f[N];
/*
a[i]:统计第i个数出现次数
f[i]:统计从 0 到 i-1 不同的数的个数
*/
int main() {
	cin >> n;
	for (ll i = 1; i <= n; i++) {
		ll x;
		cin >> x;
		a[x]++;//桶计数
	}
	for (ll i = 0; i <= n; i++) f[i] = f[i - 1] + (a[i] > 0);//前缀和
	for (ll i = 0; i <= n; i++) {
		/*
		front:从 0 到 i-1 不同整数的个数,(为了防止越界，需做判断)
		now:等于 i 的整数个数
		nees:从 0 到 i-1 需要补来数的个数,(i-front)
		*/
		ll front = (i == 0) ? 0 : (f[i - 1]);
		ll now = a[i];
		ll need = i - front;
		//累加贡献，分两个部分
		cout << now + ((now < need) ? (need - now) : 0) << "\n";
	}
	return 0;
}
```

---

## 作者：e666 (赞：0)

## 思路
这道题的思路就是将 $i$ 的出现个数与 $i$ 前未出现的数的个数做比较，输出大的。
为避免超时，得预先处理，我用数组 $s$ 存每个数出现个数，用数组 $y$ 存这之前有多少数为 $0$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000000],s[1000000],y[1000000];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[a[i]]++;
	}
  //在第二个循环处理y数组
	for(int i=0;i<=n;i++){
		y[i+1]=y[i];
		if(s[i]==0)
			y[i+1]++;
	}
	for(int i=0;i<=n;i++){
		cout<<max(s[i],y[i])<<endl;
	}
	return 0;
}
```

求管理大大审过。

---

## 作者：lvweisi (赞：0)

一道~~非常简单~~贪心题。

注意到，要让 $i$ 作为最小的非负整数，要使得 $i$ 的出现次数为零且 $1$ 到 $i-1$ 的数要至少出现一次，而 $n$ 只到 $200000$，所以只需要开一个桶把每一个数出现的个数存储下来，进行线性更新答案就好了。

### 代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
int t[200005];
int n;
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		int a;
    cin>>a;
		t[a]++;//存桶
	}
	int ans=0;
	cout<<t[0]<<'\n';
	for(int i=1; i<=n; i++) {
		if(t[i-1]==0)ans++;
		cout<<max(t[i],ans)<<'\n';
	}
	return 0;
}
```

---

## 作者：nqrqwq (赞：0)

### P11837 [USACO25FEB] Making Mexes B 题解
#### 思路
看题面可以发现如果要让 $i$ 成为最小负整数，而且需要满足 $0$ 到 $i$ 的前一个数都有出现过且 $i$ 还没有出现过。于是可以拿一个前缀和的变量 $cnt$ 来统计 $0$ 到 $i-1$ 是否出现了，当然用数组也可以，再定义一个数组 $a$ 用来看操作次数，然后判断 $cnt$ 和 $a$ 哪个大，哪个大输出哪个。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],cnt;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	int b;
    	cin>>b;
    	a[b]++;
	}
	cout<<a[0]<<endl;
	for(int i=1;i<=n;i++){
		cnt=cnt+(!a[i-1]);
		if(cnt>a[i]) cout<<cnt<<endl;
		else if(a[i]>cnt) cout<<a[i]<<endl;
		else if(a[i]==cnt) cout<<cnt<<endl;	
	}
    return 0;
}
```

---

## 作者：Manchester_City_FC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11837)

题目大意就不讲了，是人都懂。

我们令 $a_i$ 表示数字 $x$ 在数组中出现了多少次，$b_i$ 表示范围 $[0,i]$ 内出现过的数字总种类数。

首先我们先思考 mex 为 $0$ 的情况：由于 mex 为 $0$ 时数组中不能出现 $0$，因此需要删除所有 $0$，即答案为 $a_0$。

下面考虑 mex 为 $i(1 \le i \le n)$ 的情况：

数组 mex 为 $i$ 意味着所有数字 $0$ 到 $i-1$ 必须至少存在一个。而 $b_{i-1}$ 表示 $[0,i-1]$ 中出现过的数字种类数，所以缺失的数字个数为 $i-b_{i-1}$。

而另一方面，数字 $i$ 必须不出现。所以对于出现在数组中的 $i$ 来说，保留一个（或不保留都行）就行，其他全部需要删除，删除次数为 $a_i$（因为如果有多余的话，多余比例肯定比“填补缺失”更多，所以答案取二者较大者）。
于是对于 mex 为 $i$ 的操作次数，答案就是 $\max(i-b_{i-1},a_i)$。

### AC 代码
```cpp
#include<bits/stdc++.b>
using namespace std;
const int N=2e5+1;
int n,a[N],b[N];
int main(){
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		a[x]++,b[x]=1;
	}
	for(int i=1;i<=n;i++) b[i]+=b[i-1];
	cout<<a[0]<<endl;
	for(int i=1;i<=n;i++) cout<<max(i-b[i-1],a[i])<<endl;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

显然当 $\operatorname{mex}=v$ 时 $a$ 中有 $0$ 到 $v-1$ 中的所有数，并且没有 $v$。

因此最少的操作次数就是 $v$ 的个数与 $v$ 减去 $0$ 到 $v-1$ 出现的数的个数，二者取最大值。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a, t[200005], h[200005];
int main() {
	ios::sync_with_stdio(0); cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a, t[a]++, h[a] = 1;
	for (int i = 1; i <= n; ++i) h[i] += h[i - 1];
	cout << t[0] << endl;
	for (int i = 1; i <= n; ++i)
		cout << max((i - h[i - 1]), t[i]) << endl;
}
```

---

## 作者：MonKeySort_ZYczc (赞：0)

## 思路流程
考虑任意一个数 $k(1\le k\le n)$ 成为该序列的 mex 的条件：

- 对于任意 $p(0\le t< k)$，序列中至少存在一个 $a_i$ 有 $a_i=p$。 
- 对于任意 $a_i$ 都有 $a_i\neq k$。

那么将一个数变为这个序列的 mex 的最小步数应该是满足第一个条件的最小步数与满足第二个条件的最小步数的 max。  

推导到这里就容易想到思路了：  
先桶排，用 $cnt_i$ 记录序列中 $i$ 出现的次数（不用离散化美滋滋），并用 $q_i$ 记录序列中所有 $0\le t\le i$ 并满足 $cnt_t\neq 0$ 的数量。  
每行只需要输出 $\max(i-q_{i-1},cnt_i)$ 的值即可。   
解释：$i-q_{i-1}$ 即满足第一个条件的方案数，$cnt_i$ 即满足第二个条件的方案数。

总时间复杂度：$O(n)$。
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=211451;
int n,t[N],q[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a;cin>>a;
		t[a]++;
	}
	for(int i=0;i<=n;i++) q[i]=q[i-1]+bool(t[i]);
	cout<<t[0]<<'\n'; 
	for(int i=1;i<=n;i++) cout<<max(t[i],i-q[i-1])<<'\n';
}

```

---

