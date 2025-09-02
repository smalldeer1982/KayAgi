# Sakurako's Task

## 题目描述

Sakurako has prepared a task for you:

She gives you an array of $ n $ integers and allows you to choose $ i $ and $ j $ such that $ i \neq j $ and $ a_i \ge a_j $ , and then assign $ a_i = a_i - a_j $ or $ a_i = a_i + a_j $ . You can perform this operation any number of times for any $ i $ and $ j $ , as long as they satisfy the conditions.

Sakurako asks you what is the maximum possible value of $ mex_k $ $ ^{\text{∗}} $ of the array after any number of operations.

 $ ^{\text{∗}} $ $ mex_k $ is the $ k $ -th non-negative integer that is absent in the array. For example, $ mex_1(\{1,2,3 \})=0 $ , since $ 0 $ is the first element that is not in the array, and $ mex_2(\{0,2,4 \})=3 $ , since $ 3 $ is the second element that is not in the array.

## 样例 #1

### 输入

```
6
1 3
3
2 10
1 1
3 1
1 2 3
3 2
1 2 4
4 5
2 2 2 16
4 5
2 2 2 3```

### 输出

```
2
11
3
4
8
8```

# 题解

## 作者：liugh_ (赞：1)

###### [Sakurako's Task](https://codeforces.com/contest/2008/problem/G)

我们的目标是让每个数越小越好，然而要避免出现两个相同的数。注意到 $a_i\gets a_i-a_j$ 类似辗转相减，考虑往 $\gcd$ 这方面想。对于 $n=1$ 的情况，特判掉即可。对于 $n>1$，我们求出整个序列的 $\gcd$，容易想到原序列一定可以转化成序列 $b$，满足 $b_i=(i-1)\gcd$。于是扫一遍 $b$ 求出答案即可，时间 $O(n\log n)$。

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int cse;for(cin>>cse;cse--;){
		int n,k;
		cin>>n>>k;
		vector<int> a(n+5);
		int gcd=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			gcd=__gcd(gcd,a[i]);
		}
		if(n==1){
			if(k-1<a[1])cout<<k-1<<'\n';
			else cout<<k<<'\n';
			continue;
		}
		for(int i=1;i<=n;i++){
			a[i]=(i-1)*gcd;
		}
		a[n+1]=2e9;
		for(int i=1;i<=n;i++){
			if(k<=a[i+1]-a[i]-1){
				cout<<a[i]+k<<'\n';
				break;
			}
			k-=a[i+1]-a[i]-1;
		}
	}
}
```

---

## 作者：eb0ycn (赞：1)

默认 $n>1$，因为 $n=1$ 时按题意模拟即可。

对于 $a_i$ 和 $a_j$，每次可以相加或相减，进行若干次操作后就可以形成 $x \times a_i + y \times a_j$，其中 $x,y \in \mathbb{Z}$。

对于整个数组，根据裴蜀定理，最后得到的元素 $b_i$ 应满足 $\gcd_{j=1}^{n}a_j | b_i$ 或 $b_i=0$。下面把这个 $\gcd_{j=1}^n a_j$ 记作 $d$。

根据 $\operatorname{mex_k}$ 的性质，很难不发现 $b_i$ 应该尽量“紧凑”。因此 $b_i=(i-1)\times d$ 是最优的。

那么最后的序列就确定了，再算 $\operatorname{mex_k}$ 就很简单了。


```cpp
#include<cstdio>
int t,n,k,d,a;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k),d=0;
		for(int i=0;i<n;++i)scanf("%d",&a),d=gcd(d,a);
		if(n==1)printf("%d\n",k-(a>=k));
		else if(k>1ll*(n-1)*(d-1))printf("%d\n",k+n-1);
		else a=(k+d-2)/(d-1)-1,printf("%d\n",a+k);
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

题目中的操作可以看作是辗转相减，于是整个数组能凑出的最小非零值为 $d=\displaystyle\gcd_{i=1}^n a_i$，此时可重新构造 $a$：$a_i=(i-1)d$，这时答案为 $\operatorname{mex}_k a$。

# Code

```cpp
#include<bits/stdc++.h>
int T,n,m,d;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		d=0;
		for(int i=1,x;i<=n;++i)
			scanf("%d",&x),d=std::__gcd(d,x);
		if(!d||n==1)
			printf("%d\n",m-(m<=d));
		else if(d==1)
			printf("%d\n",n-1+m);
		else
			printf("%d\n",std::min((m-1)/(d-1),n-1)+m);
	}
	return 0;
}
```

---

## 作者：Meickol (赞：0)

当 $n=1$ 时比较简单，直接模拟即可得出答案。

下面考虑 $n \gt 1$ 时的解决方案。

根据 $\operatorname{mex}$ 运算的性质，要让 $\operatorname{mex}_k$ 最大，则构造出的序列应当尽可能往前靠且紧凑分布。

不难想到让序列中的某个数变得最小后，其他数便可通过加减这个最小的数使得最终构造出的序列尽可能紧凑。

即先让序列中的某个数通过题意给定的操作变成最小公差 $d$，那么最后构造出的新序列 $B$，且 $b_i=(i-1) \times d$。

不难想到这个能构造出的最小公差 $d$ 应该等于 $\gcd (a_1,a_2,\dots,a_n)$，基于裴蜀定理。

最后我们根据 $d$ 进行讨论即可：

- 当 $d=1$ 时，显然前 $[0,n-1]$ 初始时都能被构造出来。

- 当 $d \gt 1$ 时，我们统计一下 $[0,k]$ 内有多少个点初始时被构造了，然后我们将没被构造的点填上，然后再补上剩余的数量即可。

```cpp
#define rep(x,y,z) for(int x=y;x<=z;x++)
int n,k;
void solve(){
	cin>>n>>k;
	int d=0;
	rep(i,1,n){
		int x;
		cin>>x;
		d=__gcd(d,x);
	}
	if(n==1) return cout<<k-1+(d<=k-1),void(); //n=1时,d=a[1]
	else if(d==1) return cout<<n-1+k,void();
	else return cout<<min((k+d-2)/(d-1),n)+k-1,void();
}

```

---

