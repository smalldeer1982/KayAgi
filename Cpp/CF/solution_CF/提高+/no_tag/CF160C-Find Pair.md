# Find Pair

## 题目描述

你又遇到了一道关于排列的问题。

首先，考虑一个包含 _n_ 个整数的数列 _a₁_ , _a₂_ ... _aₙ_ (不一定互不相同)。你发现由其中任意两项组成的数对 (aᵢ, aⱼ)(1 <= i, j <= n)十分有趣，于是你想探究给定数列中所有 _n²_ 组数对的规律。

例如，数列{3, 1, 5}能组成九组数对：
(3, 3), (3, 1), (3, 5), (1, 3), (1, 1), (1, 5), (5, 3), (5, 1), (5, 5)。

接下来，将这些数对按照字典序升序排列。比如，两组数对(_p₁_, _p₂_)，(_q₁_, _q₂_)，当且仅当 _p₁_ < _p₂_，或 _p₁_ = _p₂_ 且 _q₁_ < _q₂_ 时，我们说(_p₁_, _p₂_)的字典序小于(_q₁_, _q₂_)的字典序。

于是，上述数列组成的数对排序后将成为：
(1, 1), (1, 3), (1, 5), (3, 1), (3, 3), (3, 5), (5, 1), (5, 3), (5, 5)。

将排好序的数组标上按顺序编号为 1 ～ _n²_ 。现在，你想要知道其中第 _k_ 组数对是什么。

## 说明/提示

样例 #1 中排好序的数对为：
(1, 1), (1, 2), (2, 1), (2, 2)
所以第4项为(2, 2)。

样例 #2 中排好序的数对为：
(1, 1), (1, 3), (1, 5), (3, 1), (3, 3), (3, 5), (5, 1), (5, 3), (5, 5)
所以第2项为(1, 3)。

## 样例 #1

### 输入

```
2 4
2 1
```

### 输出

```
2 2
```

## 样例 #2

### 输入

```
3 2
3 1 5
```

### 输出

```
1 3
```

# 题解

## 作者：Feyn (赞：2)

[link](https://www.luogu.com.cn/problem/CF160C)

难度虚高的基础题目。约定：$num_x$ 代表数列 $q$ 中 $x$ 的个数。

按照有序二元组的大小定义，我们可以从小到大枚举第一个数，假设当前枚举到的数是 $x$，那么我们应该找到以 $x$ 为第一个数的二元组的数量 $num$（显然 $num=num_x\times n$），然后判断 $num$ 和 $k$ 的大小关系。如果 $num$ 大，说明 $x$ 为第一个的二元组足够多，答案二元组的第一个数就是 $x$；如果 $k$ 大，说明此时的 $x$ 还不够大，那么让 $k$ 减去 $num$ 之后枚举下一个 $x$ 即可。

于是跳出循环的时候我们有一个 $x$ 和一个 $k$，还需要做的是找到合法的第二个元素。按照相同的方法从小到大枚举 $y$，然后比较当前的 $num=num_x\times num_y$ 和 $k$ 的大小即可。复杂度 $O(N)$。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
const int N=100010;
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,a[N],k,s[N],num[N],n;

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(k);
	for(int i=1;i<=m;i++)read(a[i]);
	sort(a+1,a+m+1);
	for(int i=1;i<=m;i++){
		if(i==1||(a[i]^a[i-1]))s[++n]=a[i];
		num[n]++;
	}
	for(int i=1;i<=n;i++){
		int now=num[i]*m;
		if(now<k){k-=now;continue;}
		for(int j=1;j<=n;j++){
			int ss=num[i]*num[j];
			if(ss<k){k-=ss;continue;}
			printf("%I64d %I64d\n",s[i],s[j]);
			return 0;
		}
	}
	
	return 0;
}
```

---

## 作者：Trimsteanima (赞：1)

### Description
给定$n$个数，形成$n*n$数对，求第k小的数对。

### Solution

先排序，每一个数有$n$个数对，第$k$小数对第一个数是$a[(k-1)/n]$，比$a[(k - 1)/n]$都不行。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100000 + 100];
long long k, t;
int main() {
	int i;
	scanf("%d%lld", &n, &k);
	for (i = 0; i < n; ++i)	scanf("%d", &a[i]);
	std :: sort(a, a + n), --k;
	for (i = 0; i < n; i += t) {
		for (t = 1; a[i] == a[i + t]; ++t);
		if (t * n > k)
			break;
		k -= t * n;
	}
	cout << a[i] << " " << a[k / t] << endl;
	return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 思路
对于 $a_i$ 一共有 $n$ 个数对，假设有 $j$ 个相同的数则一共有 $j\times n$ 个数对。令 $qz[i]$ 表示以数值为第 $i$ 小的数为结尾一共有几个数。然后我们就可以排一下序，并且对相同的 $a_i$ 进行去重，算一下 $j\times n$ 的值，如果它小于 $k$ 就继续，否则二分一下数对的第二项 $l$ 使得 $qz[l]\ge k$ 且 $qz[l-1]<k$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,b[100005];
int a[100005],top;
int qz[100005];
map<int,int> mp; 
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>a[i];
		mp[a[i]]++;//记录出现次数
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=a[i-1]||i==1)//去重
		{
			b[++top]=a[i];
		}
	}
	for(int i=1;i<=top;i++) qz[i]=qz[i-1]+mp[b[i]];//记录前缀和
	for(int i=1;i<=top;i++)
	{
		int d=mp[b[i]]*n;//一共有几对
		if(d<k)
		{
			k-=d;
			continue;
		}
		int l=1,r=top;
		while(l<=r)//二分
		{
			int mid=(l+r)/2;
			if(mp[b[i]]*qz[mid]>=k) r=mid-1;
			else l=mid+1;
		}
		cout<<b[i]<<' '<<b[l]<<endl;
		return 0;
	}
}
```


---

