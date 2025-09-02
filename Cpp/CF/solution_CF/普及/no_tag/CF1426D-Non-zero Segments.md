# Non-zero Segments

## 题目描述

Kolya got an integer array $ a_1, a_2, \dots, a_n $ . The array can contain both positive and negative integers, but Kolya doesn't like $ 0 $ , so the array doesn't contain any zeros.

Kolya doesn't like that the sum of some subsegments of his array can be $ 0 $ . The subsegment is some consecutive segment of elements of the array.

You have to help Kolya and change his array in such a way that it doesn't contain any subsegments with the sum $ 0 $ . To reach this goal, you can insert any integers between any pair of adjacent elements of the array (integers can be really any: positive, negative, $ 0 $ , any by absolute value, even such a huge that they can't be represented in most standard programming languages).

Your task is to find the minimum number of integers you have to insert into Kolya's array in such a way that the resulting array doesn't contain any subsegments with the sum $ 0 $ .

## 说明/提示

Consider the first example. There is only one subsegment with the sum $ 0 $ . It starts in the second element and ends in the fourth element. It's enough to insert one element so the array doesn't contain any subsegments with the sum equal to zero. For example, it is possible to insert the integer $ 1 $ between second and third elements of the array.

There are no subsegments having sum $ 0 $ in the second example so you don't need to do anything.

## 样例 #1

### 输入

```
4
1 -5 3 2```

### 输出

```
1```

## 样例 #2

### 输入

```
5
4 -2 3 -9 2```

### 输出

```
0```

## 样例 #3

### 输入

```
9
-1 1 -1 1 -1 1 1 -1 -1```

### 输出

```
6```

## 样例 #4

### 输入

```
8
16 -5 -11 -15 10 5 4 -4```

### 输出

```
3```

# 题解

## 作者：胖头鱼学员 (赞：9)

# [CF传送门](https://codeforces.com/contest/1426/problem/D)
# [洛谷传送门](https://www.luogu.com.cn/problem/CF1426D)

## 题意

给定一个序列,求最少插入多少数,才能使此序列任意子段和均不为$0$。

## 做法

我们处理每一段区间的前缀和，那么对于任意两个$i$，$j$（$1 \leq j \leq i 
\leq n$），让$f_i - f_j$就为$a_j$至$a_i$的区间和。

那么如果存在$f_i - f_j = 0$（$1 \leq j \leq i \leq n$），即存在$f_i = f_j$（$1 \leq j \leq i \leq n$）的情况，就代表$a_j$至$a_i$的区间和为$0$，如果这样那我们可以在这段区间中间插入一个$Max$，使得这段区间不为$0$的同时不会出现一段新的区间和为$0$，再把这个位置记录下来，之后的查询都必须在这个之后。

那么现在我们的思路就十分清晰了，就是对于每一个$f_i$（$1 \leq i \leq n$）,查询每一个$f_j$（$pos \leq j < i$）是否和$f_i$相同（$pos$为上次查询位置）。那么这么做是近似于$O(n^2)$的复杂度的（$1 \leq n \leq 200000$），这样必定会超时。

那么我们再把这个问题转换一下，查询是否有$f_j = f_i$等价于$f_i$在之前是否出现过，那么现在就可以用**哈希表**优化。

## $Code$：
```cpp
#include <iostream>

using namespace std;

const int kMaxN = 2000001;

long long n, a[kMaxN], s, pos, ans;

map<long long, long long> mp;

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s += a[i];
    if (((!s && !mp[s]) || mp[s]) && mp[s] >= pos - 1) {
      ans++; 
      pos = i;
    }
    mp[s] = i;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：king_xbz (赞：7)

# 题意简述
给定一个序列，如果有连续子序列中出现和为0的情况，可以在任意位置插入任意一个数，求最少插入数的数量
# 思路分析
考场上没想出来QAQ。

首先要知道插入的数能任意大，所以只要插入就一定会破坏序列，使其不为0，同时如果和为0的序列重叠，插入的一个数也可以对后续产生影响。

$O(N^2)$的做法很好想，前缀和乱搞即可。

可惜过不了。

其实可以用map标记一下，首先用前缀和数组维护一下，当一个前缀和数第二次出现时，就证明出现了0序列，下一个序列的判定从此开始即可。

# 代码实现

```cpp
map <int,int>mp;
signed main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(fint i=1;i<=n;i++)
	cin>>a[i];
	mp[0]=1;
	int tot=0,ans=0;
	for(fint i=1;i<=n;i++)
	{
		tot+=a[i];
		if(mp[tot])
		ans++,mp.clear(),mp[0]=1,tot=a[i];
		mp[tot]++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zjgmartin (赞：2)

## 题目分析
显然，插入的数为无穷大时作用最大。同时，如果两个和为0的子区间有重叠部分，则只需要在重叠部分插入就可以使两个子区间同时满足条件。将所有和为0的子区间抽取出来单独考虑，题意即可简化为：有一些区间，如何插入最少的特殊元素，使得每个区间中都有至少一个特殊元素。

这就成了一个贪心的经典题，策略为：从左往右扫描每个区间的左端点，对于某一个暂时没有特殊元素的区间，将特殊元素插入到区间的最右端。（证明略）

但是，如果先找出这些区间再做处理，复杂度太高，考虑使用前缀和优化。从左往右扫描数组，用STL set维护左侧出现过的前缀和。对于每一个位置，如果当前位置的前缀和在set中存在，则在它们中间有一段需要处理的区间，进行计数。此时，后面的与其有重复部分的区间（即左端点在当前位置左边的区间）可以不用再考虑，于是直接将set清空。但是要注意，子区间有可能在端点处重合，这种情况不属于有重复部分，所以清空set以后还需要插入当前位置左侧一位置的前缀和。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,ans;
ll sum,x;
set<ll> s;

int main()
{
	scanf("%d",&n); s.insert(0);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&x); sum+=x;
		if(s.find(sum)!=s.end()) ans++,s.clear(),s.insert(sum-x);
		s.insert(sum);
	}
	printf("%d\n",ans);
	
	return 0;
}
```
前往：[Martin's Blog](https://martin-xu.com/2020/10/16/%e3%80%90%e9%a2%98%e8%a7%a3%e3%80%91cf1426d-non-zero-segments/)

---

## 作者：dead_X (赞：1)

## 题意
往一个数列里插入一些数，使得没有连续子序列和为 $0$ 。
## 思路
首先，根据贪心，我们应该使插入的数竟可能大（比如 $787^{754}$ ），
这样这个数与别的数一定构不成连续子序列。

那么问题就变成了分段数组使得每一组没有连续子序列和为 $0$ 。

这个问题可以记录前缀和并且往 map 记录搞定。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
    int num=0;
    char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num*=10,num+=ch-48,ch=getchar();
    return num;
}
const int N=200005;
int n,a[N],ans;
map<int,bool>mp;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
	mp[0]=1;
	for(int i=1,sum=0;i<=n;++i){
		sum+=a[i];
		if(mp[sum]){
			++ans,mp.clear(),sum=a[i],mp[0]=1;
		}
		mp[sum]=1;
	}
	printf("%lld\n",ans);
}
```

---

## 作者：Chinese_zjc_ (赞：1)

考虑如果有子段和为 $0$ ,那么我们在这个子段的倒数第二个位置插入一个极大值,必然能够把这个子段分成两部分,使其前面的部分没有子段和为 $0$ .

插入完之后,前面部分就不用管了,直接继续枚举后面部分即可.

那么怎么判断出现子段和为 $0$ 呢?

显然用 $\text{map}$ 维护一下即可,因为只要出现 $sum_i-sum_j=0$ ( $sum_i$ 表示前缀和,即 $sum_i=a_1+a_2+\dots+a_i$ ),就会使其出现一个和为 $0$ 的子段.

于是就可以用 $\text{map}$ 维护之前是否出现过 $sum_j=sum_i$ ,就能判断了.

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
//头文件已省略
#define int long long
#define double long double
using namespace std;
const double PI = acos(-1);
const double eps = 0.0000000001;
const int INF = 0x3fffffffffffffff;
map<int, bool> has;//为true说明出现过
int sum, n, a[200005], ans;
signed main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    has[0] = true;//注意初始化
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        sum += a[i];
        if (has[sum])
        {
            ++ans;
            has.clear();
            sum = a[i];//分开后最后一个数字会留下干扰后面
            has[0] = true;//这里也要初始化
        }
        has[sum] = true;
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：我是人999 (赞：0)

首先我们观察到如果一个子段 $\left[l,r\right]$ 的和为零即 $\sum\limits_{i=l}^ra_i=0$，那么区间 $[1,l-1]$ 和 $[1,r]$ 的和必然相等。也就是
$$\sum\limits_{i=1}^ra_i=\sum\limits_{i=1}^{l-1}a_i+\sum\limits_{i=l}^ra_i=\sum\limits_{i=1}^{l-1}a_i$$

那么我们将空位编号为 $1\cdots n-1$，枚举空位的右端点，记录前缀和；

当前缀和出现重复的值时，我们就把所有相同前缀和在前面出现的位置视为左端点，向右端点连一条线段，我们需要在这条线段上选取一个点插入一个 $\infty$ 来满足子段和不为零的限制。

事实上我们只需要向上一次出现的重复前缀和连线就够了，这是因为若覆盖这条线段一定能够覆盖更前面的线段。

这是可以用贪心求解的问题。具体来说就是按右端点排序，然后每条未覆盖的线段都选最右边覆盖。由于我们上一步直接枚举了右端点，所以并不需要再对右端点排序了。

代码采用了离散化实现，与其他题解的 map 做法本质相同：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
struct node
{
	int l,r;
	bool operator <(const node &x)
	{
		return r<x.r;
	}
}
q[200005];
int cnt,covered_r,ans;
int n,a[200005],last[200005];
long long sum[200005],val[200005];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];
		val[i]=sum[i];
	}
	sort(val+1,val+n+1);
	int len=unique(val+1,val+n+1)-(val+1);
	for(int i=1;i<=n;i++)
	{
		int x=lower_bound(val+1,val+len+1,sum[i])-val;
		if(!sum[i]||last[x])
		{
			q[++cnt].l=last[x]+1;
			q[cnt].r=i-1;	
		}
		last[x]=i;
	}
	//sort(q+1,q+cnt+1);
	for(int i=1;i<=cnt;i++)
	{
		if(covered_r<q[i].l)
		{
			covered_r=q[i].r;
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：ZigZagKmp (赞：0)

本文同步于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13758252.html)

本场所有题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1426-solution)
## CF1426D
### 题意简述
给定一个序列,求最少插入多少数,才能使此序列任意子段和均不为 $0$ 。

插入的数字为任意整数，甚至可以很大或很小。

$2\le n\le 2\cdot10^5,-10^9\le a_i\le 10^9,a_i\neq 0$。

### 算法标签
前缀和 hash
### 算法分析
区间 $[l,r]$ 子段和为 $0$ 等价于 $s_r=s_{l-1}$，其中 $s_i$ 为前缀和。

因此我们只需要在出现前缀和相等时（不妨设为 $s_i=s_j,i<j$）在 $j$ 前插入一个很大的数，那么在 $i-1$ 之前的所有值都不会对后面的前缀和产生影响。

查询前缀和相等需要用 hash ，可以使用 set 等实现。

时间复杂度 $O(n\log n)$。
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define int long long
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m;
set<int>st;
int s[maxn];
int sum;
signed main(){
	read(n);
	for(int i=1;i<=n;++i)read(s[i]),s[i]+=s[i-1];
	st.insert(0);
	for(int i=1;i<=n;++i){
		if(st.find(s[i])!=st.end()){
			++sum;st.clear();st.insert(s[i-1]);
		}
		st.insert(s[i]);
	}
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：mot1ve (赞：0)

此题考查前缀和与子段和的联系。证明一下这个结论。

如果 $[l,r]$ 子段和为 $0$ ，那么在前缀和中 $sum[r]=sum[l-1]$ 。 

这个很好证明，由于$[l,r]$ 子段和为 $0$ ，那么这个子段对于$sum[r]$的前缀和是没有贡献的，所以 $sum[r]$ 等于 $sum[l-1]$ 。

可以用$map$记录哪些前缀和出现过，第一次出现之后，在这个数的位置之前插一个无穷大的值可以保证这个位置之前的所有子段和都不为0。因为如果之前有子段为0的情况早就被搜出来了。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans,sum,n;
map<int,bool> mapp;
signed main()
{
	mapp[0]=1;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		sum+=x;
		if(mapp[sum])
		{
			ans++;
			sum=x;
			mapp.clear();
			mapp[0]=1;
		}
		mapp[sum]=1;
	}
	cout<<ans;
}
```

---

## 作者：KSToki (赞：0)

首先我们搞出一个前缀和，然后从 $1$ 到 $n$ 扫一遍。当扫到某一个 $i$ 且 $s[i]$ 在之前出现过，那么这一段的子段和一定为 $0$。此时我们只需要在 $i$ 前插入一个极大值，把 $s[i]$~$s[n]$ 全部减去 $s[i-1]$ 即可。显然不用真的加，需要一个标记 $tag$ 每次记录下 $s[i-1]$，计算时减即可。注意这里 $tag$ 是要覆盖的。

我们需要 $O(nlogn)$ 的复杂度，用一个 set 维护即可，multiset 也行。记得开 `long long`。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a,s[200001],tag,cnt,ans;
multiset<ll>q;
int main()
{
	scanf("%lld",&n);
	for(register ll i=1;i<=n;++i)
		scanf("%lld",&a),s[i]=s[i-1]+a;
	q.insert(0);//注意
	for(register ll i=1;i<=n;++i)
	{
		multiset<ll>::iterator it=q.find(s[i]-tag);
		if(it!=q.end())
		{
			++ans;
			tag=s[i-1];//覆盖标记
			q.clear();//消除之前的数的影响
			q.insert(0);//注意
		}
		q.insert(s[i]-tag);//加入当前数
	} 
	printf("%lld\n",ans);
	return 0;
}
```


---

