# Rudolf and the Ticket

## 题目描述

鲁道夫打算去拜访伯纳德，他决定乘坐地铁前往。地铁票可以在售票机上购买，售票机只接受恰好两枚硬币，且这两枚硬币的面额之和不超过 $k$。

鲁道夫有两个口袋装着硬币。左口袋有 $n$ 枚硬币，面额分别为 $b_1, b_2, \dots, b_n$。右口袋有 $m$ 枚硬币，面额分别为 $c_1, c_2, \dots, c_m$。他想要从左口袋中选出一枚硬币，从右口袋中选出一枚硬币（共两枚）。

请你帮助鲁道夫计算，有多少种方法可以选择下标 $f$ 和 $s$，使得 $b_f + c_s \le k$。

## 说明/提示

注意，这里的配对是指硬币在数组中的下标对，而不是它们的面额。

在第一个测试用例中，鲁道夫可以选择以下硬币对：$[1, 1], [1, 2], [1, 4], [2, 1], [2, 2], [2, 4]$。

在第二个测试用例中，鲁道夫无法从每个口袋各选一枚硬币，使得它们的面额之和不超过 $k=4$。

在第三个测试用例中，鲁道夫可以选择：$[1, 1], [2, 1], [3, 1], [4, 1]$。

在第四个测试用例中，鲁道夫可以从左口袋和右口袋中任意选择一枚硬币。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
4 4 8
1 5 10 14
2 1 8 1
2 3 4
4 8
1 2 3
4 2 7
1 1 1 1
2 7
3 4 2000
1 1 1
1 1 1 1```

### 输出

```
6
0
4
12```

# 题解

## 作者：_Star_Universe_ (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1941A)
### 思路
很简单，只要输入 $t$ 组数据，然后每一组用 for 循环嵌套判断如果 $a_i + b_j \le k$ 就将答案加 $1$，最后输出，注意多测一定要初始化！

### 代码
```c
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[105],b[105];
signed main(){
	int t,n,m,k;
	cin>>t;
	while(t--){
		int ans=0;
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=m;i++){
			cin>>b[i];
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i]+b[j]<=k){
					ans+=1;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：GeYang (赞：3)

# 题意
给你 $k$ 和 $n$ 个数 $b_1，b_2\cdots b_n$，$m$ 个数 $c_1，c_2\cdots c_n$，求满足 $b_f+c_s\le k$ 的 $f$ 和 $s$ 有多少组。

# 思路
暴力枚举 $f$ 和 $s$ 的每种情况，然后判断是否小于等于 $k$ 并输出。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int b[105],c[105];
void solve()
{
	int n,m,k,ans=0;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>c[i];
	}
	for (int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(b[i]+c[j]<=k)
			{
				ans+=1;
			}
		}
	} 
	cout<<ans<<"\n";
} 
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：Base_ring_tree (赞：2)

# solution
这个题我们可以挨个看每一对数，看看他们的和是否大于 $k$ 就好了，这是 $O(nm)$ 的。我们再进行一点小小的优化，如果发现当前 $a_i$ 自己就大于**等于** $k$ 了，那也就不必去遍历他加上一个 $b_j$ 会不会小于等于 $k$ 了。注意，等于的情况也不需要遍历，因为每个数都至少为一。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m;
int k,ans;
int a[101005],b[10155];
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<=m;i++)
		{
			cin>>b[i];
		}
		ans=0;//多测不清空爆零两行泪 
		for(int i=1;i<=n;i++)
		{
			if(a[i]<k)
			{
				for(int j=1;j<=m;j++)
				{
					if(a[i]+b[j]<=k)
					{
						ans++;
					}
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：lgydkkyd (赞：1)

这题数据较小，建议两层循环水过，判断两数相加是否超过 $k$ 即可如果小于则累加答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,a[101],b[101],ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=m;i++)cin>>b[i];
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i]+b[j]<=k){
					ans++;
				}
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：_Deer_Peach_ (赞：1)

#### 题目简述：
给定两个长度分别为 $n$ 与 $m$ 的数组，每个数组分别拿出一个数使得两个数的和小于 $k$。求有几种方法。

#### 思路：
由于数据范围可以让我们两重循环暴力枚举，所以我们就可以用两重循环枚举方案。思路很简单，代码也很简单。

#### 代码：
```
#include<bits/stdc++.h>
using namespace std;
int t;
signed main(){
	cin>>t;
	while(t--){ 
		int n,m,k,ans=0;
		cin>>n>>m>>k;
		int a[n],b[m];
		for(int i=0;i<n;i++)cin>>a[i];
		for(int i=0;i<m;i++)cin>>b[i];
		for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(a[i]+b[j]<=k)ans++;
		cout<<ans<<endl;
	}return 0;
}
```

---

## 作者：OPEC (赞：1)

# [Rudolf and the Ticket](https://www.luogu.com.cn/problem/CF1941A)

这道题暴力枚举每一个 $b_i$ 和 $c_i$ 是否小于 $k$，这是不会超时的，时间复杂度 $O(nmt)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t,n,m,k;
int a[N];
int b[N];
void solve()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i]+b[j]<=k)
				sum++;
		}
	}
	cout<<sum<<'\n';
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：SecuritySetting (赞：0)

暴力大水题。

直接用两重循环枚举两个数组中的数，如果两数之和小于 $k$ 答案就加一，代码其实很简单。

具体代码：
```
#include <bits/stdc++.h>
using namespace std;
int t;
int n, m, k, ans;
int a[1005], b[1005];
int main() {
	cin >> t;
	while (t --) { //多组数据
		ans = 0;//注意清零
		cin >> n >> m >> k;
		for (int i = 1; i <= n; i ++) {
			cin >> a[i];
		}
		for (int i = 1; i <= m; i ++) {
			cin >> b[i];
		}
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= m; j ++) {
				if (a[i] + b[j] <= k) {//循环枚举
					ans ++;
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Dream_Mr_li (赞：0)

## 思路

这道题只需双重循环暴力枚举每一个 $b_f+c_s$ 是否 $\le k$，是的话答案就 $+1$。

时间复杂度为 $O(tnm)$，可以通过此题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int t,n,m,k,a[N],b[N],ans;
void solve(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i]+b[j]<=k){
				ans++;
			}
		}
	}
	cout<<ans<<endl;
}
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：Genshin_ZFYX (赞：0)

双重循环枚举出所有的情况，如果目前枚举到的两数之和 $\le k$，则将答案加 $1$，循环结束后输出答案并换行，时间复杂度 $O(nmt)$，足以通过此题。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],b[105];
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t;cin>>t;
	while(t--)
	{
		int n,m,k,ans=0;cin>>n>>m>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=m;i++)cin>>b[i];
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		if(a[i]+b[j]<=k)ans++;
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：Hacker_Cracker (赞：0)

## CF1941A Rudolf and the Ticket 题解
### Soltuion
因为  $ 1 \le t , n , m \le 100 $  ，考虑暴力枚举。首先一层循环遍历  $ 1 \to n $  ， 内套一层循环遍历  $ 1 \to m $  ，枚举  $ b_i + c_j \le k $  的个数。
### [AC](https://codeforces.com/contest/1941/submission/260476682) Code
```cpp
#include <iostream>
using namespace std;
int a[105] , b[105] , ans;
int main() {
	ios :: sync_with_stdio (false) , cin.tie (0) , cout.tie (0); 
	int __T;
	cin >> __T;
	while (__T --) {
		int n , m , k , ans = 0;
		cin >> n >> m >> k;
		for (int i = 1 ; i <= n ; i ++ ) cin >> a[i];
		for (int i = 1 ; i <= m ; i ++ ) cin >> b[i];
		for (int i = 1 ; i <= n ; i ++ ) {
			for (int j = 1 ; j <= m ; j ++ ) {
				if (a[i] + b[j] <= k ) ans ++;
			}
		}
		cout << ans << endl;
	}
	return 0;
} 
```

---

## 作者：iyka (赞：0)

### 题目大意
求出有多少对 $f,s$ 满足 $b_f+c_s\le k (1\le f\le n, 1\le s\le m)$。

### 求解办法
因为题目只要求求出有多少对 $f,s$，所以 $f,s$ 的具体数值我们可以不用记录。  
我们可以跑一个双重循环，先从 $1\to n(i)$，再在里面跑一边从 $1\to m(j)$，如有 $b_i+c_j\le k$，就把 $i$ 视为 $f$，把 $j$ 视为 $s$，满足题意。然后再统计一下出现了几次 $b_i+c_j\le k$ 的情况，最后再输出情况数就行了。

时间复杂度为 $O(t\times n\times m)$，极限状态下也就 $10^6$，可以跑过。

### 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int t,n,m,k,b[N],c[N],ans;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>k; ans=0;// 记得每次重置统计数为0
		for(int i=1;i<=n;++i)
			cin>>b[i];
		for(int i=1;i<=m;++i)
			cin>>c[i];
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				if(b[i]+c[j]<=k)
					++ans;
		cout<<ans<<"\n";
	}
	return 0;
} 
```

---

