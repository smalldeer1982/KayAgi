# 3SUM Closure

## 题目描述

我们定义一个数组是 “3SUM-closed” 的，当且仅当对于任意满足 $1\le i<j<k\le n$ 的三个数 $(i,j,k)$，都存在有 $1\le l\le n$，使得 $a_i+a_j+a_k=a_l$。  
现在给你 $T$ 个数组，对于每个数组，若它是“3SUM-closed”的，则输出 `YES`（大小写不敏感，下同）；若不是，则输出 `NO`。

## 样例 #1

### 输入

```
4
3
-1 0 1
5
1 -2 -2 1 -3
6
0 0 0 0 0 0
4
-1 2 -3 4```

### 输出

```
YES
NO
YES
NO```

# 题解

## 作者：zmza (赞：5)

首先，我们可以发现如果三个数中有两个零，那么三个数加起来一定等于剩下的一个非零数。所以，如果数组中有多个零，我们只需要一个零就可以了。

其次，如果有三个及以上的负数或正数，那么答案一定为 `NO` 。因为可以将最大的三个正或负数加起来，一定不存在一个数与之相等。

然后我们就直接用暴力判断。因为可以发现实际有效的数最多为一个零，两个正数和负数。如果多余这五个数，直接输出 `NO` 即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int sum = 0, ne = 1;
	char ch = getchar();
	for (; (ch < '0' || ch > '9') && ch != '-'; ch = getchar());
	if (ch == '-')
		ne = -1, ch = getchar();
	for (; ch >= '0' && ch <= '9'; ch = getchar())
		sum = (sum << 3) + (sum << 1) + (ch - '0');
	return sum * ne;
}
const int maxn = 2e5 + 5;
int a[maxn];
map <int, bool> mp;
vector <int> vec;
signed main()
{
	int t = read();
	while (t--)
	{
		mp.clear();
		vec.clear();
		int n = read();
		bool flag1 = 0;
		bool flag2 = 0;
		for (int i = 1; i <= n; i++)
		{
			a[i] = read(), mp[a[i]] = 1;
			if (!flag2 && !a[i])
				vec.push_back(a[i]), flag2 = 1; 
			if (a[i])
				vec.push_back(a[i]);
			flag1 = max(flag1, a[i] != 0); 
		}
		if (!flag1)
			puts("YES");
		else if (vec.size() > 5)
			puts("NO");
		else
		{
			bool flag = 0;
			for (int i = 0; i < vec.size(); i++)
				for (int j = 0; j < vec.size(); j++)
					for (int k = 0; k < vec.size(); k++)
						if (i != j && j != k && i != k && !mp[vec[i] + vec[j] + vec[k]])
						{
							flag = 1;
							goto lab;
						}
			lab: puts(flag ? "NO" : "YES");
							
		}
	}
	return 0;
}
```

---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个长度为 $n$ 的数组，询问是否满足从中任意选取三个数的和也是这个数组的元素。

#### 思路分析


------------
如果这个数组中出现了超过三个正数或者偶数，那么这个数组必不可能满足题意，因为最大的三个正数的和必大于该数组中的任何一个数。

所以满足题意的数组中正数和负数的数量比不可能超过4个，其他的元素皆为 $0$，而我们只需要最多保留剩余所有的 $0$ 中的三个。

所以枚举即可。

#### 代码实现


------------
```cpp
void solve(){
	int n;
	cin >> n;
	vector<int> zz, ff, a;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (x > 0) {zz.push_back(x);}
		else if (x < 0) {ff.push_back(x);}
		else {
			if (a.size() < 2) {a.push_back(x);}
		}
	}
	if (zz.size() > 2 || ff.size() > 2) {cout << "NO\n"; return;}
	
	for (int i : zz){
		a.push_back(i);
	}
	for (int i : ff){
		a.push_back(i);
	}
	for (int i = 0; i < a.size(); i++) {
		for (int j = i + 1; j < a.size(); j++) {
			for (int k = j + 1; k < a.size(); k++) {
				bool flag = false;
				for (int l = 0; l < a.size(); l++) {
					if (a[i] + a[j] + a[k] == a[l]) {flag = true;}
				}
				if (!flag) {cout << "NO\n"; return;}
			}
		}
	}
	cout << "YES\n";
}
```


---

## 作者：__stick (赞：1)

# 题意
给出一个数组，问这个数组是否满足这个数组中任意三个元素的和都在这个数组中。

# 思路

首先想到 $n^3$ 枚举和 $n^2 \log n$ 预处理两个数的和，但发现面对 $2 \cdot10^5$ 的数据无能为力，再仔细想想，会发现如果这个数组中正数或负数的个数大于等于 $2$ 那么就一定不行，为什么呢？因为这两个数相加结果的绝对值一定会大于这两个数，那么数组中最大的两个正数加起来就一定超过了这个数组中的所有数，负数也是同理，所以我们可以直接扫描一遍即可，如果正数负数的个数都小于 $2$ 那么我们直接暴力扫描即可。

# 代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
#define mp make_pair
const int MAXN=2e5+10;

int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int T;cin>>T;
	while(T--)
	{
		int n;cin>>n;
		int ne=0,pos=0,x;
		vi a;
		vi v1,v2;
		for(int i=0;i<n;i++)
		{
			cin>>x;
			if(x<0)ne++,v1.push_back(x);
			else if(x>0)pos++,v2.push_back(x);
			else if(a.size()<2) a.push_back(0);//关键，a中存两个 0 就够了如果无脑存0后果不用我说吧 
		}
		if(ne>2||pos>2){cout<<"NO\n";continue;}
		copy(v1.begin(),v1.end(),back_inserter(a));
		copy(v2.begin(),v2.end(),back_inserter(a));
		bool flag=1;
		for(int i=0;i<a.size();i++)
			for(int j=i+1;j<a.size();j++)
				for(int k=j+1;k<a.size();k++)
					if(find(a.begin(),a.end(),a[i]+a[j]+a[k])==a.end())flag=0;
		if(flag)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：让风忽悠你 (赞：1)

不难看出非负数的数量大于等于 $3$ 时是不可行的，因为一个数和**其他两个和大于零的数**相加的结果必然大于原数，最大数加上这样两个数以后的和显然不会在数列里出现，非正数同理。

上述情况是对非负数和非正数的数量做出限制，但是会发现对于 $0$ 的数量实质上并没有限制。事实上，任意一组形如 $0,0,x$ 的组合都是合法的，所以对于存在多个 $0$ 我们可以只保留一个 $0$。

做完以上操作后剩下的数列长度不会超过 $5$，此时就可以直接暴力判断了。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<map>
#define N 200005

using namespace std;

int T,n,tot;
int a[N],b[N];
map <int,bool> mp;
int cnt_1,cnt_2,fl_0;
bool fl;

int main(){
	scanf("%d",&T);
	
	while(T--){
		mp.clear();
		tot=0;
		fl=0;
		fl_0=cnt_1=cnt_2=0;
		scanf("%d",&n);
		
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			
			if(a[i]>0) ++cnt_1;
			else if(a[i]<0) ++cnt_2;
			else if(a[i]==0) fl_0=1; 
		} 
			
		if(cnt_1+fl_0>=3 || cnt_2+fl_0>=3){
			printf("NO\n");
			continue;
		} // 判断非负数和非正数的个数是否合法 
			
		sort(a+1,a+1+n);
		
		for(int i=1;i<=n;i++){
			if(!b[tot] && !a[i]) continue;
			b[++tot]=a[i];
			mp[b[tot]]=1;
		} // 处理 0 
		
		for(int i=1;i<=tot;i++)
			for(int j=i+1;j<=tot;j++)
				for(int k=j+1;k<=tot;k++)
					if(!mp[b[i]+b[j]+b[k]])
						fl=1;
		// 暴力判断 
				
		printf(fl?"NO\n":"YES\n");
	}
	
	return 0;
}
```


---

## 作者：SoyTony (赞：1)

# 题意
判断一个数列是否满足，对于任何的 $1\le i<j<k\le n,1\le l\le n$，都有 $a_i+a_j+a_k=a_l$。
# 赛时降智做法
如果不考虑最值的做法，不知道怎么胡出来能满足的数列排序后是等差的。

然后发现这个数列最大三个值之和必须要出现在数列中，因此三个数中必定不能全部为正。然后开始各种特判。

- 没有或只有一个非零数
- 若干零与一对相反数
- 三个数中包含一对相反数

然而 $3,-3,-3,9$ 这组就判不出来了，于是降智。
# 正解
因为最大三个值中必定不能全正，同理最小三个值中必定不能全负，而且若干个 $0$ 与两个 $0$ 是等价的，直接把多余的去掉。

之后可能符合条件的数列最多只剩下 $6$ 个数，然后暴力判断。

这个故事告诉我们，不要瞎猜结论，退一步打暴力海阔天空。

---

## 作者：yszs (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1698C)

~~一道诈骗题~~

### $\texttt{Description}$

给你一个集合 $a$，如果它的所有三元组满足：

$a_i + a_j + a_k  = a_l$ 并且 $1 \le i < j < k \le n ,l\in a$。

那么它就是 $\text{3SUM-closed}$。

如果是输出 `YES` 否则输出 `NO`。

### $\texttt{Solution}$

结论 `1`:如果有三个及以上个正数/负数,一定不是。

结论 `2`:如果零的个数大于等于二，那么看做只有一个零。

#### 证明结论 `1`:

$ a_i,a_j,a_k$ 分别为三个正/负数，$a_k$ 为 $a$ 中
绝对值最大的，那么他们的加和一定会超出集合 $a$，所以不是  $\text{3SUM-closed}$。

#### 证明结论 `2`:

有两个 `0` 时，我们只需要选两个 `0` 然后任选一个数，让 $a_l$ 等于它即可。

有三个以上的 `0` 时，显然。

现在我们已经将范围缩减到最大为 `5`。

直接暴力判断即可。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define For(i,u) for(int i=head[u];i;i=e[i].next)
const int N=1e6+6;
int n,m,a[N],b[10];
using namespace std;
map<int,int>mp;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,zheng=0,fu=0;
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		mp.clear();
		cin>>n;
		rep(i,1,n)
		{
			cin>>a[i];
			if(a[i]>0) zheng++;
			if(a[i]<0) fu++;
		}
		if(zheng>2||fu>2)
		{
			cout<<"NO"<<endl;
			continue;
		}
		sort(a+1,a+1+n);
		int tot=0,flag=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=0)
			{
				b[++tot]=a[i];
				mp[a[i]]=1;
			}
			else if(a[i]==0)
			{
				if(!flag)
				{
					b[++tot]=0;
					mp[0]=1;
					flag=1;
				}
			}
		}
		int fllag=0;
		for(int i=1;i<=tot;i++)
		{
			if(fllag) break;
			for(int j=i+1;j<=tot;j++)
			{
				if(fllag) break;
				for(int k=j+1;k<=tot;k++)
				{
					if(fllag) break;
					if(!mp[b[i]+b[j]+b[k]])
					{
						cout<<"NO"<<endl;
						fllag=1;
						break;
					}
				}
			}
		}
		if(!fllag)
		{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```

~~考场上读错题了，读成了只要有任意一个三元组满足，输出 `YES` 人直接傻了，以为是什么不可做之题，浪费了一个小时。~~

---

