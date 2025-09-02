# Restore the Permutation

## 题目描述

A sequence of $ n $ numbers is called permutation if it contains all numbers from $ 1 $ to $ n $ exactly once. For example, the sequences \[ $ 3, 1, 4, 2 $ \], \[ $ 1 $ \] and \[ $ 2,1 $ \] are permutations, but \[ $ 1,2,1 $ \], \[ $ 0,1 $ \] and \[ $ 1,3,4 $ \] — are not.

For a permutation $ p $ of even length $ n $ you can make an array $ b $ of length $ \frac{n}{2} $ such that:

- $ b_i = \max(p_{2i - 1}, p_{2i}) $ for $ 1 \le i \le \frac{n}{2} $

For example, if $ p $ = \[ $ 2, 4, 3, 1, 5, 6 $ \], then:

- $ b_1 = \max(p_1, p_2) = \max(2, 4) = 4 $
- $ b_2 = \max(p_3, p_4) = \max(3,1)=3 $
- $ b_3 = \max(p_5, p_6) = \max(5,6) = 6 $

 As a result, we made $ b $ = $ [4, 3, 6] $ .For a given array $ b $ , find the lexicographically minimal permutation $ p $ such that you can make the given array $ b $ from it.

If $ b $ = \[ $ 4,3,6 $ \], then the lexicographically minimal permutation from which it can be made is $ p $ = \[ $ 1,4,2,3,5,6 $ \], since:

- $ b_1 = \max(p_1, p_2) = \max(1, 4) = 4 $
- $ b_2 = \max(p_3, p_4) = \max(2, 3) = 3 $
- $ b_3 = \max(p_5, p_6) = \max(5, 6) = 6 $

A permutation $ x_1, x_2, \dots, x_n $ is lexicographically smaller than a permutation $ y_1, y_2 \dots, y_n $ if and only if there exists such $ i $ ( $ 1 \le i \le n $ ) that $ x_1=y_1, x_2=y_2, \dots, x_{i-1}=y_{i-1} $ and $ x_i<y_i $ .

## 说明/提示

The first test case is parsed in the problem statement.

## 样例 #1

### 输入

```
6
6
4 3 6
4
2 4
8
8 7 2 3
6
6 4 2
4
4 4
8
8 7 4 5```

### 输出

```
1 4 2 3 5 6 
1 2 3 4 
-1
5 6 3 4 1 2 
-1
1 8 6 7 2 4 3 5```

# 题解

## 作者：honglan0301 (赞：4)

## 题意简述
$t(1\leq t\leq 10^4)$ 组数据，每组数据给一个长度为 $n\over2$ 的数列 $b\ (2\leq n\leq 2\cdot10^5,2\leq \sum n\leq 2\cdot 10^5)$。   

请找出一个长度为 $n$ 的排列 $p$, 使得对于 $∀i∈[1,n/2]$, 满足 $b_i=\max(p_{2i-1},p_{2i})$，并且使得排列 $p$ 的字典序最小，若不存在则输出 $-1$。  

## 题目分析
看到字典序的限制，考虑从后向前，贪心地选取能用的最大元素，下面证明这种做法的正确性。  

1. 首先，因为无解的充要条件是 $\exists\ i∈[1,n]$, 使得 $[1,i]$ 中有超过 $i\over2$ 个数在 $b$ 中，显然这个做法的构造不会误判无解。  

2. 再考虑字典序。如果这个方法构造出的 $p_1$ 并不最小，那么必然存在一个 $i\geq1$, 使得 $p_1$ 可以与 $p_{2i-1}$ 互换，而这与我们构造数列的方法矛盾，故 $p_1$ 一定满足字典序最小的要求。同理，在字典序最小的前提下（即 $p_{1...2i}$ 固定），$p_{2i+1}$ 也一定满足要求，以此类推，排列 $p$ 的字典序最小。

## 代码
用 map/set 即可。
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
int t,n,b[100005],c[100005];
set <int> s;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		s.clear();
		bool flag=0;
		for(int i=1;i<=n;i++)
		{
			s.insert(i);
		}
		for(int i=1;i<=n/2;i++)
		{
			cin>>b[i];
			if(s.find(b[i])==s.end())//特判无解 
			{
				flag=1;
			}
			s.erase(b[i]);
		}
		if(flag)
		{
			cout<<"-1"<<endl;
			continue;
		}
		for(int i=n/2;i>=1;i--)
		{
			auto it=s.upper_bound(b[i]);
			if(it==s.begin())//特判无解 
			{
				flag=1;
				break;
			}
			it--;
			c[i]=*it;
			s.erase(c[i]);
		}
		if(flag)
		{
			cout<<"-1"<<endl;
			continue;
		}
		for(int i=1;i<=n/2;i++)
		{
			cout<<c[i]<<" "<<b[i]<<" ";
		}
		cout<<endl;
	}
}
```
代码写得很乱。

---

## 作者：y_kx_b (赞：2)

闲话： 感觉没有 \*1900 啊，个人感觉 1759E（\*1500）比这个难 qwq

题意
---
给定 $b_1\sim b_\frac n2$，求一个字典序最小的排列 $p_1\sim p_n$ 使得 $\forall i\in[1,\frac n2] \text{ s.t. }b_i = \max(p_{2i-1},p_{2i})$。

保证 $n$ 是偶数，且 $\sum n\leqslant 2\times10^5$。

解法
---
首先显然我们需要贪心地把大数往后面放。

1. 显然 $b_i=p_{2i}$（显然当 $p_{2i-1} > p_{2i}$ 时交换 $p_{2i-1}$ 和 $p_{2i}$ 会使字典序变小，更优），所以由 $p_{2i-1} < p_{2i}$ 得 $p_{2i-1} < b_i$。
2. 设 $x\in[1,n]$ 且 $\forall i\text{ s.t. }x \not= b_i$（因为当 $x=b_i$ 时这个 $x$ 已经被固定位置了），那么这个 $x$ 需要尽可能往后放，也就是说， $x$ 需要放在 $\max\limits_{b_i > x}(2i)-1$ 的位置。
3. 如果 $\forall i \text{ s.t. } b_i\leqslant x$ 那么一定无解，因为你 $x$ 没处放。或者换句话说，$x$ 放哪里都会使 $b_?$ 的值和给定值不一样。
4. 上述过程可以用堆实现。

```
int a[N], b[N];// a[i] <-> p[2i-1]; b[i] <-> p[2i]
int vis[N];//每个b数值出现的位置 / 2
bool major(int T = 1) {
	int n = read(); for(int i = 1; i <= n; i++) vis[i] = 0;
	for(int i = 1; i <= n >> 1; i++) vis[b[i] = read()] = i;
	priority_queue<int> s;
	for(int i = n; i; i--) {
		if(vis[i]) s.push(vis[i]);
		else if(s.empty()) return puts("-1");
		else a[s.top()] = i, s.pop();
	}
	for(int i = 1; i <= n >> 1; i++) printf("%d %d%c", a[i], b[i], " \n"[i == n]);
	return 0;
}
```

---

## 作者：luogu_gza (赞：1)

讲述一种很好理解，调试很快，不同于目前题解区的做法。

时间复杂度：$O(n \log n)$。

贪心策略：从后往前，填能填的最大的数。

证明别人已经讲得很清楚了，我也不再赘述。

一般的做法是二分，但是我们考虑建立数组 `ne`，令 `ne[i]` 表示 $i$ 之前第一个没有被占位的位置，这个定义看上去是不是很像并查集呢？

我们考虑每一次使用类似于并查集的方法维护 `ne`，代码自然呼之欲出了。

细节：

1. 每一次维护勤用 `find` 函数，防止神秘错误。
2. 无解还可能是 $b$ 数组中有重复的数。
3. $b$ 数组的大小是 $\frac{n}{2}$。

### [代码](https://codeforces.com/contest/1759/submission/212915843)

后记：有生之年第一次干掉了 `div3` 的最后一题。

---

## 作者：_JF_ (赞：0)

[CF1759G Restore the Permutation ](https://www.luogu.com.cn/problem/CF1759G)

唉，还是不会思维题。

先判掉无解，无解一种是无法构成排列，一种是我们对给定的数和剩下的数排序，一一配对，如果配不上，那就是不合法。（因为你不能调整到其他的位置去了。）

肯定是先固定题目给出的 $n$ 个数的位置在 $b$ 的偶数位，考虑剩下的进行一个填数。

首先直接无脑的贪心取是不对的，因为我们无法保证到第 $i$ 位剩下能取的最小数一定会小于对应的数 $b_i$。

所以我们考虑反着进行填数，这样限制会少。我们考虑每次找到剩余数中小于 $b_i$ 的最大数 $p$ 进行填充。

这样做是对的。考虑证明。如果你选一个 $p_1<p$ 填的话，抛开后面有没有解不谈，你把 $p$ 放到前面去，字典序上肯定是不如把 $p_1$ 放到前面去优秀的。

并且我们这样每次选的是“最大数”，也就是卡着极限去填的，必然保证有解。（实在不理解也可以假定 $p_1<p$）去反证一下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
int n,a[N],b[N],c[N],tot,Vis[N];
set<int> s;
bool check(){
	for(int i=1;i<=n/2;i++)	Vis[a[i]]++,b[i]=a[i];
	for(int i=1;i<=n;i++)	if(Vis[i]==false)	c[++tot]=i,s.insert(i);
	for(int i=1;i<=n;i++)	if(Vis[i]>1)	return false;
	sort(b+1,b+n/2+1),sort(c+1,c+n/2+1);
	for(int i=n/2;i>=1;i--)	if(b[i]<c[i])	return false;
	return true;	
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		s.clear(),tot=0;
		cin>>n;
		for(int i=1;i<=n;i++)	Vis[i]=false; 
		for(int i=1;i<=(n/2);i++)	cin>>a[i];
		if(check()==false)	{cout<<"-1"<<endl;  continue;}
		for(int i=n/2;i>=1;i--){
			auto now=s.upper_bound(a[i]);
			now--,c[i]=*now,s.erase(*now);
		}
		for(int i=1;i<=n/2;i++)	cout<<c[i]<<" "<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1759G) & [CF 传送门](//codeforces.com/problemset/problem/1759/G)
# 思路
这题中 $b_i=\max(p_{2i},p_{2i+1})$（如果 $i$ 从 $0$ 开始），而题目又要求 $p$ 的字典序最小，则我们可以让每个 $p_{2i+1}=b_i$，而让 $p_{2i}<b_i$。这题的贪心时可以倒着枚举，每次选当前最大的且没被选过的 $<b_i$ 的元素作为 $p_{2i}$，再把这个数删了。这一点可以用 STL 中的 vector + lower_bound + erase（当然你用 set + lowerbound + erase 也可以）。记住还要时刻判断是否合法。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, m, a[200005], b[200005];
bool vis[200005];
vector <int> v;
vector <int> :: iterator j;
void f () {
	cin >> n;
	m = n >> 1;
	v.clear (); //多组数据要清空
	for (int i = 1; i <= n; ++ i)
		vis[i] = 0;
	for (int i = 0; i < m; ++ i)
		cin >> b[i];
	for (int i = 0; i < m; ++ i)
		if (b[i] < 2 || vis[b[i]]) { //是 1 或者出现过了，不合法
			cout << "-1\n";
			return ;
		} else
			vis[a[i * 2 + 1] = b[i]] = 1;
	for (int i = 1; i <= n; ++ i)
		if (! vis[i]) //没出现过
			v.push_back (i); //存入 vector
	for (int i = m - 1; ~ i; -- i) {
		j = lower_bound (v.begin (), v.end (), b[i]) - 1; //lower_bound 再 -1 就是最大的比它小的值了
		if (j < v.begin ()) { //没有比它小的数，不合法
			cout << "-1\n";
			return ;
		}
		a[i << 1] = *j; //记录
		v.erase (j); //删掉元素
	}
	for (int i = 0; i < n; ++ i)
		cout << a[i] << ' ';
	cout << '\n';
	return ;
}
int main () {
	cin >> t;
	while (t --)
		f ();
	return 0;
}
```

---

## 作者：lzqy_ (赞：0)

据说这道题反着填数很容易，但我偏要正着做（

考虑 $b_i=\max(p_{2i-1},p_{2i})$，最优的方式一定是让 $p_{2i}=b_i$，然后尽量往小的 $p_{2i-1}$ 里填数。

假设现在已经填完了所有的 $p_{2i}$，考虑怎么样填 $p_{2i-1}$。

将 $p_{2i}$ 排序，设第 $x$ 大的 $p_{2i}$ 为 $c_x$。那么如果存在 $c_i<2i$，就一定无解，反之至少存在一组解，即按照 $p_{2i}$ 的大小顺序从大到小填数。

接下来考虑如何在一定有解的情况下找到字典序最小的解。

考虑如果 $c_i=2i$，那么意味着可填的（$b$ 中没有出现的数）前 $i$ 小的数，填的位置必须在前 $i$ 小的 $p_{2i}$ 所对应的 $p_{2i-1}$ 的位置上（**不一定一一对应**）。

进一步地，若 $c_i-2i=k$，那么意味着可填的前 $i$ 小的数，最多有 $k$ 个数可以不填在前 $i$ 小的 $p_{2i}$ 所对应的 $p_{2i-1}$ 的位置上。

于是就可以贪心了。我们从大到小填数 ，每次找到第一个满足 $c_i=2i$ 的位置，意味着当前数填的位置不能超过 $i$。然后贪心地填在 $[1,i]$ 内还未被填过的、编号最小的位置 $k$ 上。填完这个数后，再将 $[1,k)$ 内的位置对应的 $(c_j-2j)$ 的值 $-1$ 即可。

维护两个线段树来模拟以上过程，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define il inline
using namespace std;
const int maxn=200010;
const int N=maxn<<2;
il int read(){
	int x=0,f=1;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x*f;
}
int st[maxn],top;
vector<pair<int,int> >v;
pair<int,int>c[maxn];
pair<int,int>data[N];
pair<int,int>dataa[N];
int lz[N];
int tap[maxn];
int b[maxn],p[maxn];
int T,n;
il void pushup(int i){
	if(data[i<<1].first==data[i<<1|1].first)
		data[i]=mp(data[i<<1].first,min(data[i<<1].second,data[i<<1|1].second));
	else if(data[i<<1].first<data[i<<1|1].first) data[i]=data[i<<1];
	else data[i]=data[i<<1|1];
}
il void pushdown(int i){
	if(lz[i]==0) return ;
	data[i<<1].first+=lz[i],data[i<<1|1].first+=lz[i];
	lz[i<<1]+=lz[i],lz[i<<1|1]+=lz[i],lz[i]=0;
}
pair<int,int> Queryy(int i,int l,int r,int L,int R){
	if(l>=L&&r<=R) return dataa[i];
	int mid=l+r>>1;
	if(mid<L) return Queryy(i<<1|1,mid+1,r,L,R);
	if(mid>=R) return Queryy(i<<1,l,mid,L,R);
	pair<int,int>t1=Queryy(i<<1,l,mid,L,R);
	pair<int,int>t2=Queryy(i<<1|1,mid+1,r,L,R);
	return min(t1,t2);
}
void Modifyy(int i,int l,int r,int x,int k){
	if(l==x&&r==x){
		dataa[i]=mp(k,l);
		return ;
	}int mid=l+r>>1;
	if(mid>=x) Modifyy(i<<1,l,mid,x,k);
	else Modifyy(i<<1|1,mid+1,r,x,k);
	dataa[i]=min(dataa[i<<1],dataa[i<<1|1]); 
}
void Modify(int i,int l,int r,int L,int R,int x){
	if(L>R) return ;
	if(l>=L&&r<=R){
		data[i].first+=x,lz[i]+=x;
		return ;
	}int mid=l+r>>1;
	pushdown(i);
	if(mid>=L) Modify(i<<1,l,mid,L,R,x);
	if(mid<R) Modify(i<<1|1,mid+1,r,L,R,x);
	pushup(i);
}
void buildd(int i,int l,int r){
	if(l==r){
		dataa[i]=mp(0,0);
		return;
	}int mid=l+r>>1;
	if(mid>=l) buildd(i<<1,l,mid);
	if(mid<r) buildd(i<<1|1,mid+1,r);
	dataa[i]=mp(0,0);
}
void build(int i,int l,int r){
	lz[i]=0;
	if(l==r){
		if(l==n/2+1) data[i]=mp(0,l);
		else data[i]=mp(c[l].first-l-l,l);
		return;
	}int mid=l+r>>1;
	if(mid>=l) build(i<<1,l,mid);
	if(mid<r) build(i<<1|1,mid+1,r);
	pushup(i);
}
int main(){
	T=read();
	while(T--){
		top=0;
		for(int i=1;i<=n/2;i++) tap[b[i]]--;
		n=read();bool fl=0;v.clear();
		for(int i=1;i<=n/2;i++) b[i]=c[i].first=read(),tap[b[i]]++,c[i].second=i;
		for(int i=1;i<=n/2;i++) p[2*i]=b[i];
		for(int i=1;i<=n;i++) if(tap[i]>1){fl=1;printf("-1\n");break;}
		if(fl) continue;
		sort(c+1,c+1+n/2);
		for(int i=1;i<=n/2;i++)
			if(c[i].first<i+i){fl=1;printf("-1\n");break;}
		if(fl) continue;
		for(int i=1;i<=n;i++)
			if(!tap[i]) st[++top]=i;
		build(1,1,n/2+1),buildd(1,1,n/2);
		for(int i=1;i<=n/2;i++)
			Modifyy(1,1,n/2,i,c[i].second);
		for(int i=1;i<=n/2;i++){
			int End=data[1].second;
			pair<int,int>Min_id=Queryy(1,1,n/2,1,End);
			Modifyy(1,1,n/2,Min_id.second,1e9);
			p[Min_id.first*2-1]=st[i],Modify(1,1,n/2+1,1,Min_id.second,-1);
			Modify(1,1,n/2+1,Min_id.second,Min_id.second,1e9);
		}
		for(int i=1;i<=n;i++)
			printf("%d ",p[i]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：yeshubo_qwq (赞：0)

## Solution

$b_i=\max(p_{2i-1},p_{2i})$，要让字典序尽可能小，大的数一定放后面，于是我们确定了原来的排列的偶数位。

于是问题转化为每个位置要求填一个小于 $b_i$ 的数（有一定选择范围，且用过的不能再用），要求最后的结果的字典序最小。

我们首先考虑从前往后放，每次放能放的当中最小的，如果没有能放的则无解。然而这是错误的。

看这个例子：`6 4 2`。

按照上面的做法，我们前两位会填 `1 3`，此时，最后填不了 `5`，于是无解。

但显然存在另一种方案：`5 6 3 4 1 2 `。

所以我们改变一下策略，考虑从后往前放，每次放能放的当中最大的，如果没有能放的则无解。这是正确的。

从后往前放，每次放能放的当中最大的保证了字典序最小，同时防止了前面因为用了小的数导致后面无法填入数的问题。

放置数的时候，可以考虑使用 `vector` + 二分。

## Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
int n,m,i,l,vis[200005],b[200005],tot,ans[200005];
vector <int> vec;
int find(int tag){
	int ans=-1,l=0,r=vec.size()-1;
	while (l<=r){
		int mid=(l+r)>>1;
		if (vec[mid]<=tag) l=(ans=mid)+1;
			else r=mid-1;
	}
	if (ans==-1) return -1;
	int ret=vec[ans];
	vec.erase(lower_bound(vec.begin(),vec.end(),ret));
	return ret;
}
void go(){
	cin>>n,m=(n>>1);
	int flag=0;
	memset(vis,0,sizeof(vis));
	for (i=1;i<=m;i++){
		cin>>b[i];
		if (!vis[b[i]]) vis[b[i]]=1;
		else flag=1;
	}
	if (flag){
		cout<<"-1\n";
		return ;
	} 
	vec.clear();
	for (i=1;i<=n;i++)
		if (!vis[i]) vec.push_back(i);
	for (i=m;i>=1;i--){
//		<=b[i] max 
		int G=find(b[i]);
		if (G==-1){
			cout<<"-1\n";
			return ;
		}
		ans[i*2-1]=G,ans[i*2]=b[i];
	}
	for (i=1;i<=n;i++) cout<<ans[i]<<(i==n?'\n':' ');
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tests=1;
    cin>>tests;
    while (tests--) go();
    return 0;
}
```

---

## 作者：Shunpower (赞：0)

## 思路

首先很容易发现如果 $b$ 数组有重复的数就是无解。

接着又可以发现，在我给 $b$ 数组里面每个数构造出另一半（也就是两者的 $\min$ 的那个数，因为 $\max$ 被放进了 $b$ 数组）之后，我要把它的另一半放在它前面更好。

于是考虑如何给每个数找出它的另一半。

有一个显然的贪心是我们把所有不在 $b$ 数组里面的数从小到大排序然后依次配对，但是有一个问题是后面的数可能没得选，被前面的数占完了。这种情况也不一定无解，可能可以通过交换得到答案。

所以你不妨考虑倒着放，从后面开始配对，去避免前面的干涉后面的。为了使得字典序最小，我每次拿出还未配对的第一个比它小的不在 $b$ 数组中的数和它配对。

下面是对在这种情况下，无法配对一定是无解的证明。

> 考虑当前枚举到了下标 $x$。由于无法配对，这意味着如果我们想要让他们配对，我们将从 $x$ 后面的所有位置中寻找一个位置 $y$ 通过一次交换使得两者都能满足。而这意味着存在一个数 $z$ 大于 $b_x$ 并小于 $b_y$，同时位置 $y$ 的另一半要小于 $b_x$，但位置 $y$ 上的另一半没有取到 $z$，说明其另一半一定大于 $z$，因此大于 $b_x$。

于是直接模拟即可。将所有不在 $b$ 数组中的数放入 `set` 然后使用 `set` 的 `lower_bound` 即可找到“还未配对的比它小的不在 $b$ 数组中的数”。

## 代码

```
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define inf INT_MAX
#define uinf INT_MIN
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int N=2e5+10;
int T;
int n;
int b[N];
int bol[N];
vector <int> ans;
// vector <int> p;
set <int> s;
void solve(){
    cin>>n;
    s.clear();
    ans.clear();
    fr1(i,1,n){
        bol[i]=0;
    }
    fr1(i,1,n/2){
        cin>>b[i];
        bol[b[i]]++;
    }
    fr1(i,1,n){
        if(bol[i]>=2){
            cout<<"-1"<<endl;
            return;
        }
        if(!bol[i]){
            // p.pb(i);
            s.insert(i);
        }
    }
    fr2(i,n/2,1){
        // int d=lower_bound(p.begin(),p.end(),b[i])-p.begin();
        auto d=s.lower_bound(b[i]);
        if(d==s.begin()){
            cout<<"-1"<<endl;
            return;
        }
        d--;
        // cout<<i<<","<<(*d)<<endl;
        ans.pb(*d);
        s.erase(d);
    }
    reverse(ans.begin(),ans.end());
    fr1(i,1,n/2){
        cout<<ans[i-1]<<" "<<b[i]<<" ";
    }
    cout<<endl;
}
int main(){
    cin>>T;
    while(T--){
        solve();
    }
    ET;
}
//Teens-in-Times
//HJL 2004.06.15
//YHX 2004.08.16
//Everything For Ji, Lin, Hao, Shun, Hang and You.
```

[AC 记录](https://www.luogu.com.cn/record/95239716)

---

