# Coprime

## 题目描述

Given an array of $ n $ positive integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 1000 $ ). Find the maximum value of $ i + j $ such that $ a_i $ and $ a_j $ are coprime, $ ^{\dagger} $ or $ -1 $ if no such $ i $ , $ j $ exist.

For example consider the array $ [1, 3, 5, 2, 4, 7, 7] $ . The maximum value of $ i + j $ that can be obtained is $ 5 + 7 $ , since $ a_5 = 4 $ and $ a_7 = 7 $ are coprime.

 $ ^{\dagger} $ Two integers $ p $ and $ q $ are [coprime](https://en.wikipedia.org/wiki/Coprime_integers) if the only positive integer that is a divisor of both of them is $ 1 $ (that is, their [greatest common divisor](https://en.wikipedia.org/wiki/Greatest_common_divisor) is $ 1 $ ).

## 说明/提示

For the first test case, we can choose $ i = j = 3 $ , with sum of indices equal to $ 6 $ , since $ 1 $ and $ 1 $ are coprime.

For the second test case, we can choose $ i = 7 $ and $ j = 5 $ , with sum of indices equal to $ 7 + 5 = 12 $ , since $ 7 $ and $ 4 $ are coprime.

## 样例 #1

### 输入

```
6
3
3 2 1
7
1 3 5 2 4 7 7
5
1 2 3 4 5
3
2 2 4
6
5 4 3 15 12 16
5
1 2 2 3 6```

### 输出

```
6
12
9
-1
10
7```

# 题解

## 作者：Tooler_Yang (赞：8)

这道题目第一感应该是倒着找第一个 $i$ 和 $j$，使 $gcd(a_i,a_j)=1$。

但是，事实证明，$2\le n\le 2\times10^5$,用 $O(n^2)$ 并不优秀。

但是我们考虑到 $1\le a_i \le 1000$，所以我们可以枚举1000以内所有互质的数，然后再判断这两个数是否在数列中。若果在，就将答案更新。

一些芝士：
我们可以用 `__gcd(a,b)` 来求 $a,b$ 的最大公因数。

code：
```cpp
// Problem: CF1742D Coprime
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1742D
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Writing time:2022-10-21 13:51:10

#include<bits/stdc++.h>
using namespace std;
int a[1000001];
int mpl[1001];
int main(){
	int T;
	cin>>T;
	while(T--){
		memset(mpl,0,sizeof(mpl));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			mpl[a[i]]=i;//记录a[i]的下标
		}
		int ans=-1;
		for(int i=1;i<=1000;i++){
			for(int j=1;j<=1000;j++){
				if(__gcd(i,j)==1&&mpl[i]!=0&&mpl[j]!=0){
					ans=max(ans,mpl[i]+mpl[j]);
				}
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：what_can_I_do (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1742D)

桶思想。

先用一个桶来存储每一个出现过的数的下标，因为 $i+j$ 要最大，所以如果有数字重复一律按最后出现过的下标为准。最后去进行 gcd，找出最大的 $i+j$。

样例：$1\ 3\ 5\ 2\ 4\ 7\ 7$。

$a_1$ 是 $1$，那么我们就把桶数组 $t$ 的第一项 $t_1$ 变成 $1$ 在 $a$ 的位置，也就是 $1$。以此类推，推到 $a$ 的第六项时，$t$ 是这样的：$1\ 4\ 2\ 5\ 3\ 0\ 6$。

接下来 $a_7$ 又是 $7$，为了让 $i+j$ 最大，所以我们要把 $t_7$ 更换为 $7$ 最后一次出现的位置 $a_7$，于是 $t$ 数组变为：$1\ 4\ 2\ 5\ 3\ 0\ 7$。

最后把整个数组跑一遍取最大值就行了。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
inline int gcd(int a,int b)
{
	while(b^=a^=b^=a%=b);    
    return a;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int x,maxx=-1,a[1010]={0},maxd=-1;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%d",&x),a[x]=i,maxd=max(maxd,x);
		for(register int i=1;i<=maxd;i++) for(register int j=i;j<=maxd;j++) if(a[i]!=0&&a[j]!=0) if(gcd(i,j)==1) maxx=max(maxx,a[i]+a[j]);
		printf("%d\n",maxx);
	}
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

# 思路

## part 1

直接考虑 $\Theta(TN^2)$ 暴力，即：挨个循环 $a_i,a_j$，寻找最大值。

显然这个方法是行不通的，所以我们要想一想优化。

## part 2

我们可以看见 $1 \leq a_i \leq 1000$，因此，我们可以往 $\Theta(a_{max}^2)$ 的方向想。

我们可以用一个桶 $vis$ 来记录每一个数 $a_i$ 最后一次出现的位置（因为对于同一个数，值不变的情况下，对于结果必定是 $i$ 越大越好）。然后，直接双重循环 $1 \sim a_{max}$，判断三个条件：`vis[i]`，`vis[j]`，`gcd(i,j) ==  1`。如果成立就更新答案（这里是要将答案与当前的 $vis_i + vis_j$ 取最大值的）。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1010;
int T,n;
int vis[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int gcd(int a,int b){//辗转相除法没什么好说的吧 
	if (a % b == 0) return b;
	return gcd(b,a % b);
}

int main(){
	T = read();
	while (T--){
		memset(vis,false,sizeof(vis));
		int Max = 0,ans = -1;
		n = read();
		for (re int i = 1;i <= n;i++){
			int x;
			x = read();
			vis[x] = i;//记录 
			Max = max(Max,x);//找最大值 
		}
		for (re int i = 1;i <= Max;i++){
			for (re int j = 1;j <= Max;j++){
				if (vis[i] && vis[j] && gcd(i,j) == 1) ans = max(ans,vis[i] + vis[j]);//更新答案 
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Nephren_Sakura (赞：0)

题目传送门：[link](https://www.luogu.com.cn/problem/CF1742D)

首先我们可以想到一个显然的思路:

枚举 $i$,$j$,然后判断是否满足条件。

记 $maxa$ 为 $a$ 中值最大的元素,则 $maxa \le 1000$。

复杂度 $O(n^2 \times \log n)$。

考虑优化

我们可以发现题目的 $a$ 范围只有 $1000$,特别小。

所以我们可以考虑对于每一个数 $i$,记录下最大的 $j$ 满足 $a_j=i$。

最后枚举 $x,y$,判断 $\gcd(x,y)$ 是否为 $1$ 并且 $x,y$ 是否都在序列中出现过,如果满足条件则更新答案,时间复杂度为 $O(maxa^2 \times \log maxa)$ 可以通过。

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,a[1000005],ed[1005],n;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		memset(ed,-1,sizeof ed);
		cin>>n;
		for(int i=1; i<=n; i++)
			cin>>a[i],ed[a[i]]=i;
		int ans=-1;
		for(int i=1; i<=1000; i++)
			for(int j=1; j<=1000; j++)
				if(__gcd(i,j)==1&&ed[i]!=-1&&ed[j]!=-1)
					ans=max(ans,ed[i]+ed[j]);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：zbk233 (赞：0)

## 思路

$n \le 2 \times 10 ^ 5$，显然不可以直接做，但是因为 $1 \le a_i \le 1000$，所以我们可以从值域来考虑。

如果有相同的元素，那么显然，下标最大的元素优先级最大。所以，我们用一个桶来存储一个数出现的最后的位置。

之后只需要暴力枚举每一个数值就行了。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int num[1005];
int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		for(int i=1;i<=1000;i++) num[i]=0;
		int n,maxa=-1;
		cin>>n;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			num[x]=i;
		}
		for(int i=1;i<=1000;i++){
			if(!num[i]) continue;
			for(int j=1;j<=i;j++){
				if(!num[j]) continue;
				if(gcd(i,j)==1){
					maxa=max(maxa,num[i]+num[j]);
				}
			}
		}
		cout<<maxa<<'\n';
	}
	return 0;
}
```


---

## 作者：小明小红 (赞：0)

# CF1742D题解

**题目分析**:UKE 就是超时了，不能双重循环求解。可以换个觉得想想，题目既然给你了 $( 1 \le a_i \le 1000 )$ ，说明 $a_i$ 可能会用上。正解就是记录每个数最后一次出现的位置，然后枚举数字。

**没看懂看这里**：可以用数组 $a$ 来记录每个数最后一次出现在的位置，比如说前面有一个 $11$，后面也有 $11$。肯定所有与后面搭配所得的值比前面大，由此可推得公式。

# code
```c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,n,s[200009],ans,a[2009];
int main()
{
	cin>>T;
	while(T--)
	{
		memset(a,0,sizeof(a));//a一定要初始化 
		cin>>n;
		ans=-1;
		for(ll i=1;i<=n;i++)
		{
			cin>>s[i];
			a[s[i]]=i;//记录每个数最后出现的位置 
		}
		for(ll i=1;i<=1000;i++)//双重循环枚举数字 
		{
			for(ll j=i;j<=1000;j++)
			{
				if(a[i]!=0&&a[j]!=0&&__gcd(i,j)==1)//若两个数字出现过且两数互质 
				{
					ans=max(ans,a[i]+a[j]);//记录 
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0; 
}
```


---

## 作者：Allanljx (赞：0)

## 思路
观察到值域很小，只有 $10^3$，因此考虑先将 $\gcd(i,j)$ 预处理出来，然后记录每个数是否出现，枚举值域，当 $\gcd(x,y)$ 等于 $1$ 时说明两数互质，可以取 $\max$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int a[200005];
int bk[1005];
int g[1005][1005];
int m1[1005],m2[1005];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	for(int i=1;i<=1000;i++)
	{
		for(int j=1;j<=1000;j++)
		{
			if(__gcd(i,j)==1) g[i][j]=1;//预处理gcd
		}
	}
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			bk[a[i]]=1;
			m1[a[i]]=i;
		}
		int ans=0;
		for(int i=1;i<=1000;i++)
		{
			for(int j=i;j<=1000;j++)
			{
				if(bk[i]&&bk[j]&&g[i][j])//出现过并且互质
				{
					ans=max(ans,m1[i]+m1[j]);
				}
			}
		}
		if(!ans) cout<<-1<<endl;
		else cout<<ans<<endl;
		memset(bk,0,sizeof(bk));
		memset(m1,0,sizeof(m1));
		memset(m2,0,sizeof(m2));
	}
}
```

---

## 作者：江户川·萝卜 (赞：0)

给定一个长为 $n\ (2\le n\le 2\times10^5)$ 的序列 $a\ (1\le a_i\le 1000)$，求 $\max\limits_{\gcd(a_i,a_j)=1}\{i+j\}$。换句话说，求 $i+j$ 的最大值，其中  $i,j$ 满足 $a_i$ 和 $a_j$ 互质。

----
暴力枚举 $i,j$ 的时间复杂度是 $O(n^2)$ 的，显然不可取，考虑换一个角度，发现值域只有 $1000$，所以可以记录每一个值的最大下标，然后暴力枚举 $a_i,a_j$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls p<<1
#define rs p<<1|1
typedef long long ll;
int ind[1005];
void solve(){
    memset(ind,0,sizeof ind);
    int n;cin>>n;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        ind[x]=i;
    }
    int ans=-1;
    for(int i=1;i<=1000;i++){
    for(int j=i;j<=1000;j++){
        if(__gcd(i,j)==1&&ind[i]&&ind[j]) ans=max(ans,ind[i]+ind[j]);
    }
    }
    cout<<ans<<'\n';
}
int main(){
	std::ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--){
		solve();
	}
}
```

---

