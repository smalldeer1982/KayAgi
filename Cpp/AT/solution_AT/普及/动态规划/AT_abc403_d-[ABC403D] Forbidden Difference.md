# [ABC403D] Forbidden Difference

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc403/tasks/abc403_d

给定一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\dots,A_N)$ 和一个非负整数 $D$。我们需要通过删除 $A$ 中的若干元素，得到一个新序列 $B$，使其满足以下条件：

- 对于所有 $i,j\ \ (1 \leq i < j \leq |B|)$，都有 $|B_i - B_j| \neq D$。

求最少需要删除多少个元素才能满足条件。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq D \leq 10^6$
- $0 \leq A_i \leq 10^6$
- 输入中的所有值均为整数

### 样例解释 #1

删除 $A_1=3$，得到 $B=(1,4,1,5)$，此时对于所有 $i<j$，都有 $|B_i - B_j| \neq 2$。

### 样例解释 #2

原始序列 $A$ 已经满足条件，因此不需要删除任何元素。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5 2
3 1 4 1 5```

### 输出

```
1```

## 样例 #2

### 输入

```
4 3
1 6 1 8```

### 输出

```
0```

## 样例 #3

### 输入

```
10 3
1 6 2 10 2 3 2 10 6 4```

### 输出

```
2```

# 题解

## 作者：hlsnqdmz (赞：19)

## 大概题意：
将一个整数序列删除至对于每个数都没有比它大 $D$ 和比它小 $D$ 的数，求最少删除次数。

## 正式开始：
阅读完题我们可以发现：对于每个数，决定它是否被删除取决于比它大 $D$ 和小 $D$ 的数的个数，我们可能会想到一个贪心：对于每个数，删除与它相同的数或者与它大或小 $D$ 的数中个数更少的那一个，但是我们难以保证这样是对的，但是这个方法给了我们一个灵感：既然贪心不行，那 dp 呢？

对于一个数又要考虑比它大 $D$ 又要考虑比它小 $D$ 的数是很难受的，但是我们可以只考虑比它小的，每个都只考虑比它小 $D$ 的数，那也不会出错。我们设 $dp[i][0]$ 是对于第 $i$ 个数，删除比它小 $D$ 的最少删除次数，$dp[i][1]$ 是对于第 $i$ 个数，删除它自己的最少删除次数。我们可以拿一个数组 `v[1000005]` 存储每个值在序列里出现的次数，为了优化，我们可以用 $mx$ 来记录序列里最大的数，$mn$ 记录最小的数，先预处理 $mn\sim mn+D-1$，再从 $mn+D$ 开始 dp，答案就是 $\sum_{i=mx-D+1}^{mx}\min(dp[i][0],dp[i][1])$。

dp 转移方程也可以列出来了：
$$$
dp[i][0]=\min(dp[i-d][0]+v[i-d],dp[i-d][1])\\
dp[i][1]=\min(dp[i-d][0]+v[i],dp[i-d][1]+v[i])
$$$
但是对于这道题有很坑的点：$D=0$，对于这种情况，我们可以发现：让在序列里出现过的每个值都只剩下一个数，所以答案加上出现过的每个值出现的次数减一就可以了。

最后要注意统计答案时要注意 $mx-D+1<0$ 的情况防止越界，贴出代码：
```
//Just Sayori
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
#define rnt register int
#define gr getchar
#define pr putchar
#define N 1000005
#define M 1000000007
using namespace std;
inline ll read()
{
    ll x = 0, f = 1;
    char ch = gr();
    while (ch < '0' || ch > '9') ch == '-' ? f = -1, ch = gr() : ch = gr();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = gr();
    return x * f;
}
inline void write(ll x, bool k)
{
    static int sta[39], top = 0;
    if (x < 0) pr('-'), x = -x;
    do sta[++top] = x % 10, x /= 10;
    while (x);
    while (top) pr(sta[top--] + 48);
    k ? pr(32) : pr(10);
}
ll a[N], v[N];
ll dp[N][2];//删前，删自
int main()
{
    ll n = read(), d = read(), mx = 0, mn = M;
    ll ans = 0;
    for (rnt i = 1; i <= n; i++) a[i] = read(), v[a[i]]++, mx = max(mx, a[i]), mn = min(mn, a[i]);
    if (!d)
    {
        for (rnt i = mn; i <= mx; i++) ans += v[i] ? v[i] - 1 : 0;
        write(ans, 0);
    }
    else
    {
        for (rnt i = mn; i < mn + d; i++)
            dp[i][1] = v[i];
        for (rnt i = mn + d; i <= mx; i++)
        {
            dp[i][0] = min(dp[i - d][0] + v[i - d], dp[i - d][1]);
            dp[i][1] = min(dp[i - d][0] + v[i], dp[i - d][1] + v[i]);
        }
        for (rnt i = mx; i >= max(0ll, mx - d + 1); i--)//这里要判断，防止越界
            ans += min(dp[i][0], dp[i][1]);
        write(ans, 0);
    }
    return 0;
}
```
### 感谢您的观看！

---

## 作者：Jerry20231029 (赞：6)

## 题目大意

给出一个长度为 $N$ 序列 $A$ 和一个自然数 $D$，求最少删去 $A$ 中的几个元素，可以满足 $|A_i-A_j| \ne D (1 \le i,j \le N,i \ne j)$。

## 思路

先用一个桶 $a$ 记录 $A$ 中各种元素有几个，然后分情况讨论。

### 当 $D = 0$ 时

当 $D = 0$ 时，$A$ 中不能有重复的元素。所以我们只要统计 $A$ 中每种元素多出来了几个，就可以得到答案。

### 当 $D > 0$ 时

我们先将 $A$ 中的每种元素按模 $D$ 的余数分组（分组时实际放入的是这种元素的数量）。

然后我们分组进行 DP，$dp_i$ 表示这一组中从第 $1$ 种元素到第 $i$ 种元素，最多能保留多少**个**元素。

状态转移方程为：

$$
dp_i = \max(dp_{i-1},l+v)
$$

其中 $l$ 是前面不与第 $i$ 种元素相邻的元素个数最多的那一种元素，$v$ 是第 $i$ 种元素的元素个数。

所以每一组的答案就是 $dp_{size}$，$size$ 表示本组元素种类个数。

最后将每一组的答案累加起来，就是最多能保留的元素数量，再用 $N$ 减去它，就能得到本题答案。

## 代码


```cpp
#include<iostream>
#include<vector>
using namespace std;

int a[1000100],dp[1000100];
vector<int> b[1000100];

int main(){
	int n,d,t,c=0;
	cin>>n>>d;
	for(int i = 1; i <= n; i++){
		cin>>t;
		a[t]++;
	}
	if(d == 0){
		for(int i = 0; i <= 1e6; i++){
			if(a[i] > 0){
				c += a[i]-1;
			}
		}
		cout<<c;
		return 0;
	}
	for(int i = 0; i <= 1e6; i++){
		b[i%d].push_back(a[i]);
	}
	int l;
	for(int i = 0; i < d; i++){
		if(b[i].empty()){
			continue;
		}
		l = 0;
		dp[0] = b[i].front();
		for(int j = 1; j < b[i].size(); j++){
			dp[j] = max(dp[j-1],l+b[i][j]);
			l = max(l,dp[j-1]);
		}
		c += dp[b[i].size()-1];
	}
	cout<<n-c;
	return 0;
}
```

---

## 作者：PDAFX (赞：5)

## 题目大意

给你一串数字，问你最少删几个才能使得任意两个数字差不等于 $d$。

## 思路

起初想的是贪心，是假的。

考虑 DP，令 $f_{i,0/1}$ 表示删 / 不删去 $i$ 后最小值。

如果它不删，那么它只能由上一个删转移而来。

```cpp
f[i][0]=f[i-d][1];
```

如果它不选，那么与上一个无关。

```cpp
f[i][1]=min(f[i-d][0],f[i-d][1])+s[i];
```

## 代码 (考场版)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[3000001],d,ans,cnt,f[2000001][2],s[3000001];
int od(int x)
{
	int anss=1e9,lst=0,i;
	for(i=0;i*d+x<=1000000;i++)
	{
		if(i==0)
		{
			f[i][0]=0;
			f[i][1]=s[x];
		}
		else
		{
			f[i][0]=f[i-1][1];
			f[i][1]=min(f[i-1][0],f[i-1][1])+s[i*d+x];
		}
//		cout<<f[i][0]<<" "<<f[i][1]<<endl;
//		lst=i;
	}
	return min(f[i-1][0],f[i-1][1]);
}
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(!s[a[i]])
		{
			cnt++;
		}
		s[a[i]]++;
	}
	if(d==0)
	{
		cout<<n-cnt;
		return 0;
	}
	for(int i=0;i<d;i++)
	{
		ans+=od(i);
	}
	cout<<ans;
}
```

---

## 作者：20090818Cc (赞：5)

### 题意

  给你一个数列 $a$ ，再给你一个距离 $d$ ，你可以删一些数让 $a$ 中没有两个数的差值为 $d$ ，问删的数的最小个数，数列长度在 $10^6$ 以内。

### 思路

很容易想到**动态规划**，我们设 $dp_{x,0/1}$ 来表示一个数 $x$ 删与不删的最小删除个数，由于差值为 $d$， 可以把 $x\bmod  d$ 相等的数看成一组，每次求解 $dp_{x,1/0}$ 时继承上一个与 $x\bmod d$ 相等的数的 dp 值。

具体来说：
- 在保留 $i$ 时，$dp_{i,1}=dp_{j,0}$。
- 在不保留 $i$ 时，$dp_{i,0}= \min(dp_{j,1},dp_{j,0})+sum_{i}$。

### 解题步骤

读入结构体 $sum$，$num$，并以 $num$（数的大小）排序。

记录 $last[i]$ 表示 $num \equiv i \pmod d $ 的最后一个数。

$dp$ 后在所有 $dp[last[i]][1/0]$ 中取最小值累加。

要注意 $d=0$ 的情况！

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=2e6+110;
inline int read(){
	int sum=0,k=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')k=-1;c=getchar();}
	while(c>='0'&&c<='9'){sum=sum*10+c-48;c=getchar();}
	return sum*k;
}
struct Node{
	int sum,num;
}b[M];
inline bool cmp(Node a,Node b){
	return a.num<b.num;
}
int n,d,a[M],c[M],res=0,Cnt;
bool vis[M],Vip[M];
int dp[M][2],last[M],cnt[M],Tot=0;
signed main(){
	n=read(),d=read();
	for(int i=1;i<=n;i++){
		int num=read();
		c[i]=num;
		a[num]++;
	}
	for(int i=1;i<=n;i++)if(a[c[i]]&&!vis[c[i]]) {
		vis[c[i]]=1;
		b[++Cnt]={a[c[i]],c[i]};
		if(d==0) res+=a[c[i]]-1;
	}
	if(d==0){
		cout<<res<<endl;
		return 0;
	}
	sort(b+1,b+1+Cnt,cmp);
//	for(int i=1;i<=Cnt;i++) cout<<"num="<<b[i].num<<" sum="<<b[i].sum<<endl;
	for(int i=1;i<=Cnt;i++){
		int sum=b[i].sum,num=b[i].num;
		int id=num%d,befo=last[id];
		if(num>=d){
			if(last[num%d]!=num-d){
				int minn=min(dp[befo][0],dp[befo][1]);
				dp[num][0]=minn+sum;
				dp[num][1]=minn;
			}
			else{
				dp[num][0]=min(dp[befo][0],dp[befo][1])+sum;
				dp[num][1]=dp[befo][0];
			}
		}
		else dp[num][0]=sum;
		last[id]=num;
		if(!Vip[id]){
			Vip[id]=1;
			cnt[++Tot]=id;
		}
//		cout<<"num= "<<num<<endl<<"dp[num][0]= "<<dp[num][0]<<endl<<"dp[num][1]= "<<dp[num][1]<<endl;
	}
	for(int i=1;i<=Tot;i++){
		res+=min(dp[last[cnt[i]]][0],dp[last[cnt[i]]][1]);
	}
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：WuMin4 (赞：2)

## [ABC403D] Forbidden Difference

## 题意

给出 $n$ 个非负整数 $a_i$，你需要删去最少数量的 $a_i$ 使得不存在任意两个 $a_i$ 绝对值之差等于非负整数 $d$。

## 思路

我们观察到对于一个数 $x$，只有当 $x-d$ 或 $x+d$ 存在时才会不满足条件。

因此我们每次可以找出一段连续且均存在的数字序列 $x,x+d,x+2d,\cdots$，可以发现若要使得这些数满足条件，则要使得所有与存在的数相邻的数都不存在。

很显然这是一个简单 dp。设 $f_{i,0/1} $ 表示数字 $i$ 是否存在，$cnt_i$ 表示数字 $i$ 的出现次数，则易得转移方程：

$$
f_{i,0}=\min{(f_{i-d,0},f_{i-d,1})}+cnt_i \\
f_{i,1}=f_{i-d,0}
$$

最后最少需要删去的数量即为每个序列最末尾的数字 $x$ 的 $\min{(f_{x,0},f_{x,1})}$ 之和。注意判断边界情况。

然后你就会发现这么写完后还 WA 了 $5$ 个点。因为 $d$ 有可能等于 $0$，所以当 $d=0$ 时，每个数字最多只能存在一个，需要将所有多余的数删去，特判即可。

[记录](https://atcoder.jp/contests/abc403/submissions/65271363)

---

## 作者：Willson1307 (赞：2)

## [[ABC403D] Forbidden Difference](https://www.luogu.com.cn/problem/AT_abc403_d)题解
### 题目大意
给定一个序列 $a_i$，求最少删除多少个数使得 $\forall i<j\wedge i,j\in[1..n],|a_i-a_j|\ne d$，其中 $d$ 为常数。
### 思路分析
- 问题可以转化为最多剩下多少。
- 我们发现是否满足限制与序列顺序无关，所以我们可以用计数器把每个值的数量存下来。
- 因为 $d$ 为常数，所以我们可以把每个元素按 $a_i\bmod d$ 进行分类。
- 题目要求每对数的差不能为 $d$，也就是模 $d$ 同余的数不能“相邻”，这一段详见代码。
- 求序列中选择不连续元素总和的最大值使用一个简单的 DP 就可以解决，这一段也是详见代码。
- 最后把每个分类的答案求和可以算出最多剩下多少个，用 $n$ 减去这个数就是答案。
- **但是**上述做法基于模 $d$ 的分类讨论，而 $d=0$ 时显然不能这么做。不过这种情况也好解决，对于每个相同的元素只能留一个。

思路整理完毕，具体实现过程参见代码注释。
### AC代码
```cpp
#include<bits/stdc++.h>
const int N = 2e5 + 10, D = 1e6 + 10; //N为元素总和最大值，D为d的最大值
int n, d, a[N], cnt[D], f[D], sum; //n, d, a的意义见题目，cnt是计数器，用于统计每个数值的数量；f是后来DP用的状态，sum是最多剩下多少个元素
std::vector<int> b[D]; //b用于存储每个类别的每个元素的个数
int main(){
	scanf("%d%d", &n, &d);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		cnt[a[i]]++; //计数
	}
	if(d == 0){ //一定要特判d = 0！
		for(int i = 0; i <= 1e6; i++){
			if(cnt[i]) sum += cnt[i] - 1; //有相同的只能留一个
		}
		printf("%d", sum);
		return 0;
	}
	for(int i = 0; i <= 1e6; i++){
		b[i % d].emplace_back(cnt[i]); //把每个值的数量放入b中，注意是每个值，因为后面要判“相邻”
	}
	for(int i = 0; i < d; i++){
		int pm = 0, sz = b[i].size(); //pm是pre_max的缩写，用于前缀最大值优化；sz是size的缩写
		if(sz >= 1) f[0] = b[i][0]; //赋初值，判断size >= 1是为了避免越界
		for(int j = 1; j < sz; j++){
			f[j] = std::max(f[j - 1], pm + b[i][j]); //转移，f[i]要么继承f[i-1]的状态，要么等于前一个的前一个状态（不能“相邻”）加上这个值
			pm = std::max(pm, f[j - 1]); //求前缀max
		}
		sum += f[sz - 1]; //累加
	}
	printf("%d", n - sum); //算出来的是最多剩下多少个，n - sum才是最终答案
	return 0;
}
```

---

## 作者：__Ship_ (赞：2)

![](能在没过的时候给一下具体位置或者您是谁，谢谢您能够一次性指出所有问题，能方便我更好的改进（找错找不到），谢谢您的支持，这篇题解对我很重要)

没有二分的吗，我来一发。

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc403_d)

## 思路

既然是找一个数能不能被删，且限制下标，不是有序的，就不能用二分了？

我们发现 $|B_i-B_j|\ \neq\ D$ 也就是说这个限制对于排序来说没有作用，所以排序。

排完序后就可以直接二分了吗？

因为我们枚举每个数，从这个数开始往后找，我们只需要找到后直接计数器加一，所以删哪个都一样。

至于删去后的数，直接存数组里打标记，否则会导致我下一次遍历到这个数时又给他用了，但他早已被删了。

有个需要注意的地方：

举个例子：

```cpp
6 3
2 2 2 5 5 5
```

这个情况下，我能直接二分到这一堆 $5$ 中间去然后走人吗？这样的话就不好二分了，我们可以往右找，直到没有了或被用了。

还有另一个要注意的地方：

当 $d=0$ 的情况，再举个例子：

```cpp
10 0
1 2 2 3 3 3 4 4 4 4
```

很明显这里不能**都**只删一个，所以要判断情况：当前这剩余数量小于两个的时候只删一个；大于两个的时候就每找一次就删两下，直到剩余数量小于两个的时候，这时只删一个。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,a[200050],cnt=0,vis[2000050],t[2000050];
int main(){
	cin>>n>>d;
	for(int i = 1 ; i <= n ; i++){
		cin>>a[i];
		t[a[i]]++;
	}
	if(n==1){//特判，我也不知道为什么
		cout<<0;
		return 0;
	}
	sort(a+1,a+n+1);
	for(int i = 1 ; i <= n ; i++){
		int l=i,r=n,ret=0;
		if(!vis[i]){
			while(l<=r){
				int mid=(l+r)/2;
				if(a[i]-a[mid]==-d&&!vis[mid]){
					ret=mid;
					l=mid+1;
				}
				else if(a[i]-a[mid]>-d){
					l=mid+1;
				}
				else{
					r=mid-1;
				}
			}
		}
		if(ret){
			if(ret!=i){
				if(d==0&&t[a[ret]]-2>=1){//0的情况
					t[a[ret]]-=2;
					cnt++;
				}
				vis[ret]=1;
				cnt++;
			} 
			
		}
		
	}
	cout<<cnt;
	return 0;
}

//1 2 2 2 3 4 5 5 10 10
//1 1 3 4 5
```

[通过记录](https://atcoder.jp/contests/abc403/submissions/65308491)

---

## 作者：Qerucy (赞：1)

先排序。

考虑到只有差为 $d$ 的两个数会被影响到，所以我们可以分别对模 $d$ 同余的这 $d$ 个集合分别统计答案。

题目要求删去最少的数，我们可以求保留最多的数，再去用 $n$ 去减，这个东西可以用线性 dp 求解。

我们用 $dp_{i,0/1}$ 表示这个位置删不删，则有以下 dp
 式子：
$$dp_{i,0}=\max(dp_{i-1,0},dp_{i-1,1})$$
$$dp_{i,1}=\max(dp_{i-1,0}+sum_i,dp_{i-1,1})$$

其中 $sum_i$ 表示 $a_i$ 的数量。

注意特判 $d=0$ 的情况。

以下是赛时代码。


```cpp
#include<bits/stdc++.h>

using namespace std;

int n,d;
int a[1000010];
int ans[2];
int sum;
int b[1000010];
int aaa;
int f[1000010][2];

vector<int>v[1000010];

signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]++;
	}
	sort(a+1,a+1+n);
	for(int i=0;i<=1000000;i++){
		if(b[i]) aaa+=b[i]-1;
	}
	if(d==0){
		cout<<aaa;
		//assert(d!=0);
		return 0;
	}
	n=unique(a+1,a+1+n)-a-1;
	//printf("aa %d\n",n);
	for(int i=1;i<=n;i++){
		v[a[i]%d].push_back(a[i]);
	}
	for(int x=0;x<d;x++){
		if(v[x].size()==0) continue;
		f[0][0]=0;
		f[0][1]=b[v[x][0]];
		int qsu=b[v[x][0]];
		for(int i=1;i<v[x].size();i++){
			if(v[x][i]-v[x][i-1]==d){
				f[i][0]=max(f[i-1][0],f[i-1][1]);
				if(i>=2) f[i][1]=max(f[i-1][0],f[i-2][1])+b[v[x][i]];
				else f[i][1]=f[i-1][0]+b[v[x][i]];
			}
			else{
				f[i][0]=max(f[i-1][0],f[i-1][1]);
				f[i][1]=f[i][0]+b[v[x][i]];
			}
			qsu+=b[v[x][i]];
		}
		int bbb=max(f[v[x].size()-1][1],f[v[x].size()-1][0]);
		sum+=qsu-bbb;
		//printf("qwqwqwq %d %d\n",qsu,bbb);
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：lilong (赞：1)

观察到一个数 $x$ 是否删除取决于 $x+d$ 和 $x-d$ 是否删除。考虑 dp，设 $f_{i,0/1}$ 表示当前为数字 $i$ 的最少删除次数，其中 $0$ 表示删除 $i$，$1$ 表示不删除，则应当由 $f_{i-d,0/1}$ 转移过来。具体地，有：

$$f_{i,0}=\min(f_{i-d,0},f_{i-d,1})+b_i$$

$$f_{i,1}=f_{i-d,0}$$

其中 $b_i$ 表示 $i$ 的出现次数。最后答案为 $ \sum_{i=M-d+1}^M \min(f_{i,0},f_{i,1})$，其中 $M$ 为值域上限。时间复杂度 $O(N+M)$，实现时注意边界情况及特判 $d=0$ 的情况。


```cpp
#include<iostream>
#include<cstdio>
#include<map>
#define N 2000010
using namespace std;
int n,d,a[N],b[N],f[N][2],ans;
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		cin>>a[i],b[a[i]]++;
	if(d==0){//d=0时，相同的数只保留一个
		for(int i=0;i<=1000000;i++)
			if(b[i])
				ans+=b[i]-1;
		cout<<ans;
		return 0;
	}
	for(int i=0;i<=1000000;i++){
		if(i<d){
			f[i][0]=b[i];
			continue;
		}
    f[i][0]=min(f[i-d][0],f[i-d][1])+b[i];
    f[i][1]=f[i-d][0];
	}
	for(int i=1000000;i>1000000-d;i--)
		ans+=min(f[i][0],f[i][1]);
	cout<<ans;
	return 0;
}
```

---

## 作者：include13_fAKe (赞：1)

隔位 dp 的略微加强版，为什么我们机房只有 $4$ 个人切了，并且我凭这题在 A 最后一个切的情况下暂时翻到了机房的 rank $1$？



---

首先用新数组统计原数组的数的出现次数，后面的 dp 都在新数组上进行。

考虑按模 $d$ 的余数进行分组。

设 $dp_{i,1/0}$ 表示现在选（或不选）值为 $i$ 的数使**这一组**能达到的最小删除数。

具体来说 $dp_{i,1}$ 只能从 $dp_{i-d,0}$ 转移而来。$dp_{i,0}$ 可以从 $dp_{i-d,0}$ 或 $dp_{i-d,1}$ 转移而来，但要加上目前数 $i$ 的出现次数。

最后统计每一组的最后一个数的 $dp$ 值的最小值即可。时间复杂度 $O(n+\max a_i)$。

一个经典的坑是 $d=0$ 的情况，此时只需要把重复的数删光即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,k;
int a[5*114514];
int sum[10*114514];
int dp[1919810][2];	//dp[i][j] 表示到了第 i 个位置 选或不选 
int ans[1919810];	//不同余数的答案  
signed main(){
	cin>>n>>k;
//	if(k==0){
//		for(int i=1;i<=n;i++){
//			cin>>a[i];
//		
//	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
//		a[i]=a[i]%(k*2);
		sum[a[i]]++;
	}
	int ans2=0;
	for(int i=0;i<=1000005;i++){
		ans2+=max(0ll,sum[i]-1);
	} 
	if(k==0){
		cout<<ans2<<endl;
		return 0;
	}
//	int include13=0;
//	for(int i=0;i<k;i++){
//		include13+=min(sum[i],sum[i+k]);
//	}
//	cout<<include13<<endl;
	for(int i=0;i<=1000005;i++){
		if(i<k){
			dp[i][1]=0;
			dp[i][0]=sum[i];
		}
		else{
			dp[i][1]=dp[i-k][0];
			dp[i][0]=min(dp[i-k][0],dp[i-k][1])+sum[i];
		}
		ans[i%k]=min(dp[i][1],dp[i][0]);
	} 
	int include13=0;
	for(int i=0;i<k;i++){
		include13+=ans[i];
	}
	cout<<include13<<endl;
	return 0;
}//ABC403D 
```

---

