# [USACO25OPEN] More Cow Photos B

## 题目描述

今天奶牛们的心情特别顽皮！Farmer John 只是想拍摄一张奶牛们排成一行的照片，但她们总是在他得到机会按下快门之前移动位置。

具体地说，FJ 的 $N$ 头奶牛（$1 \le N \le 10^5$）每一头的身高都是 $1$ 到 $N$ 的整数。FJ 想要拍摄奶牛以一种特定的顺序排成一行的照片。如果奶牛们排成一行时从左到右有身高 $h_1, \dots, h_K$，他希望奶牛们的身高拥有以下三个性质：

- 他希望奶牛们的身高先递增再递减。形式化地说，必须存在一个整数 $i$ 使得 $h_1 \le \dots \le h_i \ge \dots \ge h_K$。
- 他不希望任何奶牛与另一头身高完全相同的奶牛相邻。形式化地说，对于所有 $1 \le i < K$ 有 $h_i \neq h_{i+1}$。
- 他希望照片是对称的。形式化地说，如果 $i + j = K+1$，则 $h_i = h_j$。

FJ 希望照片中包含尽可能多的奶牛。具体地说，FJ 可以移除一些奶牛并重新排列余下的奶牛。计算 FJ 在满足他的限制的情况下可以在照片中包含的奶牛的最大数量。

## 说明/提示

对于第一个测试用例，FJ 可以选择身高为 $1$，$1$ 和 $3$ 的奶牛，并重新排列为 $[1,3,1]$，满足所有条件。对于第二个测试用例，FJ 可以选择身高为 $3$ 的奶牛以组成一张合法的照片。

- 测试点 $2\sim3$：$T\le 100$，$N \le 7$。
- 测试点 $4\sim5$：$T \le 10^4$，所有奶牛的身高不超过 $10$。
- 测试点 $6\sim11$：没有额外限制。

## 样例 #1

### 输入

```
2
4
1 1 2 3
4
3 3 2 1```

### 输出

```
3
1```

# 题解

## 作者：Clare613 (赞：4)

## 思路
既然想要奶牛数量越多越好，那么就需要尽量得多放奶牛。\
我们可以把奶牛的身高统计起来，不难发现，数量大于等于 $2$ 的身高都可以选其中的两头奶牛。\
最后要注意，身高最高的即使有很多头，也只能选其中的一头。
## code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000007
using namespace std;
int a[1000005];
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--){
		int n,maxn=0;
		cin>>n;
        for(int i=1;i<=n;i++) a[i]=0;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			a[x]++;
            maxn=max(maxn,x);
		}
		int ans=0;
		for(int i=1;i<maxn;i++){
			if(a[i]>=2){
				ans+=2;
			}
		}
        cout<<ans+1<<"\n";
	}
	return 0;
}
```

---

## 作者：volatile (赞：3)

# 思路

因为是对称的数组，所以除了中间最高的奶牛，其他奶牛的身高至少出现 $2$ 次，记录最高的奶牛，并且遍历桶数组即可。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>cnt;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,s=1,maxn=0;
        vector<int>sg;
        cin>>n;
        for(int i=1;i<=n;i++){
            int a;
            cin>>a;
            maxn=max(maxn,a);
            cnt[a]++;
            if(cnt[a]==1) sg.push_back(a);
        }
        for(int i=0;i<sg.size();i++){
            if(cnt[sg[i]]>=2&&sg[i]!=maxn) s+=2;
        }
        cout<<s<<endl;
        cnt.clear();
    }
    return 0;
}
```

---

## 作者：YYF_Maple_Leaves (赞：3)

## 解题思路
这里是蒟蒻的第二篇题解呀。


这一题中让我们求照片中可以包含的奶牛的最大数量，

首先照片中可以包含的奶牛身高要符合题目要求。

题目中对身高的要求先递增再递减，并且身高相同的两只奶牛不能排在一起。

根据题目中所给的要求，我们不难看出同一张照片中每一个身高值 $h_{i}$ 最多只能出现两次。

我们可以在读入数据中寻找最大值，除了这个最大值只能出现 $1$ 次，其他每个身高都最少且最多只能出现两次。

输入后遍历整个身高数组，如果 $2$ $ \le$ 该身高 $h_{i}$ 出现的次数,那么在 $ ans $ 中增加 $2$ 个值。

相对地，如果该身高 $h_{i}$ 是这个数组中的最大值，那么在 $ans$ 中增加 $1$ 个值。

最后的 $ans$ 即为答案。
## AC代码

```cpp
#include <iostream>
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int h[100005]={0};
		int n;
		cin>>n;
		int maxn=0;
		long long ans=0;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			h[x]++;
			if(x>maxn)
			{
				maxn=x;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(h[i]>=2 &&  i!=maxn)
			{
				ans+=2;
			}
			else if(i==maxn)
			{
				ans+=1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：CSP_S_2023_T2 (赞：3)

### 思路

容易发现，题目所求数列满足：
- $K$ 为奇数且 $h_1 < \cdots <h_{\frac{K+1}{2}} > \cdots > h_K$ （即题目中 $i=\frac{K+1}{2}$ 的情况）。

- 对于任意 $1 \le i \le K$ 满足 $h_i=h_{K-i+1}$。

证明在本文末尾。

为了使 $K$ 尽可能大，我们需要从身高序列中找到所有**出现次数大于等于两次**的数字，记满足条件的数字个数为 $ans$。

为了方便起见，记身高序列中的最大值为 $H$。

- $H$ 出现的次数 $\ge 2$，如果我们取 $2$ 只身高为 $H$ 的奶牛，则这 $2$ 只奶牛必定会排在第 $h_{\frac{K-1}{2}}$ 处和第 $h_{\frac{K+3}{2}}$ 处，此时 $h_{\frac{K+1}{2}}$ 必须大于 $H$，矛盾。所以最多只能取 $1$ 只身高为 $H$ 的奶牛。为了使 $K$ 尽可能大，除 $H$ 外所有满足条件的数字都得取 $2$ 次，答案即为 $(ans-1) \times 2+1=ans\times2-1$。

- $H$ 出现的次数 $= 1$，同理，所有满足条件的数字都得取 $2$ 次，答案即为 $ans\times2+1$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[100005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));       //多测不清空，爆零两行泪 
		cin>>n;
		int ans=0,maxn=0;
		for(int i=1;i<=n;i++){
			cin>>x;
			a[x]++;                  //记录每个数字的出现数字 
			maxn=max(maxn,x);        //记录最大值 
		}
		for(int i=1;i<=n;i++){
			if(a[i]>1) ans++;        //统计出现次数大于等于 2 的数字 
		}
		if(a[maxn]>1) cout<<ans*2-1;
		else cout<<ans*2+1;
	}
	return 0;  //完结撒花 
}
```

### 证明

由题中前两个条件可得存在一个整数 $i$ 使得 $h_1<\cdots<h_i>\cdots>h_K$。

若 $K$ 为偶数，根据题意得 $h_{\frac{K}{2}}=h_{\frac{K+2}{2}}$ 且 $h_{\frac{K}{2}}\ne h_{\frac{K+2}{2}}$，矛盾。

所以 $K$ 只能为奇数。

若 $i < \frac{K+1}{2}$，则 $i \le \frac{K-1}{2}$，必有 $h_{\frac{K-1}{2}}>h_{\frac{K+1}{2}}>h_{\frac{K+3}{2}}$，但 $h_{\frac{K-1}{2}}=h_{\frac{K+3}{2}}$，矛盾。

若 $i > \frac{K+1}{2}$，同理，矛盾。

故 $i=\frac{K+1}{2}$。

---

## 作者：PKUS_zmj (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P12023)
# 思路
首先最高的**其中一只**奶牛肯定放中间，所以答案初始化要为 $1$，这个排列肯定是一个对称排列，所以只要看身高小于最高的奶牛的奶牛数是否大于或等于 $2$，若是，总数加 $2$，否则不变。这里采用分治法。
# AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int a[n+5];
		int cnt[n+5]={0};
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			cnt[a[i]]++;
		}
		sort(a+1,a+1+n);
		int ans=1;
		for(int i=1;i<n;i++) if(cnt[i]>=2&&i<a[n]) ans+=2;
        cout<<ans<<endl;
	}
	return 0;
}
```
勿抄代码！！！

---

## 作者：IcyDragon (赞：2)

## 思路

由于所有奶牛都不能高于中间的那头牛，所以选择最高的那头牛站在照片中间，以选择更多的牛进入照片。

其它的牛按以下方式处理：遍历每一种身高，若这种身高的牛超过两头，就选取两头放在照片两侧。

可以用 `map` 记录每一种身高有几头牛。

## 代码

```cpp
#include<iostream>
#include<map>
using namespace std;

map<int,int> m;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T,n,t,c,mx;
	for(cin>>T; T--; cout<<'\n'){
		cin>>n;
		m.clear();
		c = mx = 0;
		for(int i = 1; i <= n; i++){
			cin>>t;
			mx = max(mx,t);
			m[t]++;
		}
		m[mx] = 0;
		c++;
		for(auto p : m){
			if(p.second >= 2){
				c += 2;
			}
		}
		cout<<c;
	}
	return 0;
}
```

---

## 作者：niuniudundun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12023)

## Problem

有 $N$ 个不超过 $N$ 的整数，求出满足先递增再递减、没有相同的数相邻并且是对称的序列的最长长度。

## Solution

假设身高是 $h$，答案为 $ans$。

首先最高的那个一定排中间，不然其他的排不上，不是最优。因为相邻的奶牛身高一定不同，所以顶多在两边放两个，所以找出有两个相同高度的奶牛就可以拍照，答案就可以加 $2$。不过这样复杂度有 $O(N^2)$，可以使用 `map` 加速。

## Code

复杂度：$O(N\log N+\max h_i)$，$\log N$ 是 `map` 常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1;
int T=0;
signed main(){
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		map<int,int> cow;
		int h[maxn],maxh=-1,ans=1;
		for(int i=1;i<=n;i++){
			cin>>h[i];
			cow[h[i]]++;
			maxh=max(maxh,h[i]);
		}
		cow[maxh]=0;
		for(int i=0;i<maxh;i++){
			if(cow[i]>=2){
				ans+=2;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
/*
2
4
1 1 2 3
4
3 3 2 1
*/
```

---

## 作者：Jerry555 (赞：1)

## 题目分析
这道题目要求在所有奶牛中选出一个序列，要求必须满足以下几点：
1. 先递增再递减。
2. 相邻奶牛身高不同。
3. 对称排列。

换句话说，就是除了最高的奶牛外，所有同一身高的奶牛仅保留 $2$ 个。因为题目仅需要输出数量，因此递增、递减关系不用考虑；因为只要有一个最高的奶牛卡在中间，所有奶牛就一定不相邻。

## 解题思路
1. 我们可以先统计每一个相同身高的奶牛的数量，再从奶牛中选出一个最大值挑出来。
2. 我们把相同身高但是只有 $1$ 个的奶牛删掉，把相同身高但是数量大于 $2$ 个的奶牛仅保留两个。
3. 输出剩余奶牛的数量，要注意需要包含最高的奶牛。

## 最终代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int h[100005];
int sum[100005];
// 数组尽量要开大一点，防止越界。
int main(){
    int T;
    cin >> T;
    while(T--){
        for(int i=1;i<=100001;i++)sum[i]=0; // 一定要记得初始化，尤其是这种直接拿来用的数组。
        int n;
        cin >> n;
        int maxn=-1;
        for(int i=1;i<=n;i++){
            cin >> h[i];
            sum[h[i]]++;
            maxn=max(maxn,h[i]);
        }
        int ans=0;
        for(int i=1;i<maxn;i++)if(sum[i]>1)ans+=2;
        cout << ans+1 << endl; // 这里的+1是最高的奶牛。
    }
}
```

---

## 作者：GSQ0829 (赞：1)

### 题目思路：
首先，我们要知道这个照片拍出来需要满足的条件：
1. 身高要先递增再递减；
2. 不希望任何奶牛与另一头身高完全相同的奶牛相邻；
3. 身高得对称排列。

那么，全部牛当中最高的那头一定是站在中心位的，然后，其他身高的牛只要同身高的牛数至少有两头，就加入两头。

所以这道题目的代码很简单，首先要有一个记录最高高度牛的变量，还有一个桶数组用来记录不同牛的身高，接着根据刚才的思路进行编写代码即可。

整体代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
int a[MAXN], h[MAXN], t, n, maxn, ans;

int main() {
	cin >> t;
	while (t--) {
		memset(a, 0, sizeof(a)); // 记得清空数组
		cin >> n;
        // 记得清零计数器
		maxn = INT_MIN;
		ans = 0;
		for (int i = 1; i <= n; i++) {
			cin >> h[i];
			a[h[i]]++; // 桶数组用来保存高度
			maxn = max(maxn, h[i]); // 求最高的牛
		}
		for (int i = 1; i < maxn; i++) {
			if (a[i] > 1) ans += 2; // 只要这个身高的牛数大于1，总数就+2
		}
		cout << ans + 1 << endl; // 最后记得加上最高的那只牛的1
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12023)

很水，我们可以先统计一下每种身高的奶牛的数量，并找出最大身高，然后统计一下小于最大身高且数量不少于 $2$ 的身高种类数设为 $m$，然后由于照片是对称的，每种满足条件的身高可以在照片的两侧各放一头，再加上最大身高的奶牛，答案就是 $2m+1$。

```cpp
#include <iostream>
#include <map>
#define F first
#define S second
using namespace std;

map<int, int> cnt;

int main()
{
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		int mx = 0;
		cnt.clear();
		for (int i = 1; i <= n; i++)
		{
			int x;
			cin >> x;
			cnt[x]++;
			if (x > mx) mx = x;
		}
		int m = 0;
		for (auto p : cnt)
			if (p.F < mx && p.S >= 2) m++;
		cout << m * 2 + 1 << "\n";
	}
	return 0;
}
```

---

## 作者：qW__Wp (赞：0)

显然将答案序列升序排序后，除最大值外，每个数都出现了两次。

容易想到对于所有出现两次及以上的数，将每种数抽出两个加入答案序列，再加入一个最大值。因此记原序列中两次及以上的数有 $sum$ 种，则答案为 $sum \times 2 + 1$。

但是发现即使所有数的最大值 $max$ 也出现两次及以上，最多仍然只能加入一个 $max$。因此 $sum$ 中不能算上 $max$。

```C++
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int a[N];

signed main() {
	int T; cin >> T;
	while (T --) {
		int n; cin >> n;
		for (int i = 1; i <= n; i ++) cin >> a[i];
		sort(a + 1, a + n + 1);
		int tot = 0, i = 1;
		while (i < n) {
			if (a[i] == a[i + 1]) tot ++;
			while (i < n && a[i] == a[i + 1]) i ++;
			if (i < n) i ++;
			else tot --; // i = n，说明是最大值，不计算贡献
		}
		cout << tot * 2 + 1 << endl;
	}
	return 0;
}
```

---

## 作者：Tiger_Rory (赞：0)

我们统计每个身高对应的奶牛数量，然后直接算出答案即可。注意其中身高最高的奶牛数量不管是多少都可以且只能对答案产生 $1$ 个贡献，否则就有两头身高相同的奶牛相邻了。其余奶牛如果数量大于 $1$ 就能对答案产生 $2$ 个贡献，否则没有贡献。

接下来是代码实现。


```cpp
//这是最直接的代码实现，最慢的点甚至超过了 1s，不过能过
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5; 
int T,n,a[N];   
map<int,int>mp; 
map<int,bool>vis; 
signed main() {
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n; 
		int maxx=-1; 
		for(int i=1;i<=n;i++){
			cin>>a[i];
			vis[a[i]]=0;
			mp[a[i]]=0;  
			maxx=max(a[i],maxx); 
		}
		for(int i=1;i<=n;i++)mp[a[i]]++; 
		int ans=0;
		bool flag=0; 
		for(int i=1;i<=n;i++){
			if(vis[a[i]])continue; 
			if(mp[a[i]]>=2){
				if(a[i]==maxx){
					ans++; 
				}
				else ans+=2; 
				vis[a[i]]=1; 
			}
			else{
				if(a[i]==maxx)ans++; 
				vis[a[i]]=1; 
			}
		}
		cout<<ans<<'\n'; 
	}
	return 0;
}
```

---

