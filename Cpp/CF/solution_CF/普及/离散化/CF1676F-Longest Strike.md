# Longest Strike

## 题目描述

Given an array $ a $ of length $ n $ and an integer $ k $ , you are tasked to find any two numbers $ l $ and $ r $ ( $ l \leq r $ ) such that:

- For each $ x $ $ (l \leq x \leq r) $ , $ x $ appears in $ a $ at least $ k $ times (i.e. $ k $ or more array elements are equal to $ x $ ).
- The value $ r-l $ is maximized.

If no numbers satisfy the conditions, output -1.

For example, if $ a=[11, 11, 12, 13, 13, 14, 14] $ and $ k=2 $ , then:

- for $ l=12 $ , $ r=14 $ the first condition fails because $ 12 $ does not appear at least $ k=2 $ times.
- for $ l=13 $ , $ r=14 $ the first condition holds, because $ 13 $ occurs at least $ k=2 $ times in $ a $ and $ 14 $ occurs at least $ k=2 $ times in $ a $ .
- for $ l=11 $ , $ r=11 $ the first condition holds, because $ 11 $ occurs at least $ k=2 $ times in $ a $ .

A pair of $ l $ and $ r $ for which the first condition holds and $ r-l $ is maximal is $ l = 13 $ , $ r = 14 $ .

## 样例 #1

### 输入

```
4
7 2
11 11 12 13 13 14 14
5 1
6 3 5 2 1
6 4
4 3 4 3 3 4
14 2
1 1 2 2 2 3 3 3 3 4 4 4 4 4```

### 输出

```
13 14
1 3
-1
1 4```

# 题解

## 作者：Coros_Trusds (赞：8)

# 题目分析

思路很简单。

我们把序列 $a$ 中每个数的出现次数记录下来，把出现次数大于等于 $m$ 的数放到集合 $b$ 里，他们可能是满足条件的。

把 $b$ 从小到大排列，找出 $b$ 中最大的连续数字段的左端点和右端点，这就是答案。

---------
举个例子，$[11,11,12,13,13,14,14]$，$k=2$。转到 $b$ 里之后：$[11,13,14]$，没错吧？

继续，找到最长的，连续的，数字段的左右端点，这不就是 $[13,14]$ 吗？左右端点就是 $l=13,r=14$ 咯。

时间复杂度 $\mathcal{O(n)}$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int a[N];
vector<int>vec;
int T,n,m;
inline void init() {
    vec.clear();
}
inline void solve() {
    cin >> n >> m;
    map<int,int>mp;
    for (register int i = 1;i <= n; ++ i) {
        cin >> a[i];
        mp[a[i]] ++;
    }
    for (map<int,int>::iterator it = mp.begin();it != mp.end(); ++ it) {
        if ((*it).second >= m) {
            vec.push_back((*it).first);
        }
    }
    if (!vec.size()) {
        puts("-1");
        return;
    }
    sort(vec.begin(),vec.end());
    int l = vec[0],r = vec[0],st = vec[0],maxx = 0;
    for (register int i = 1;i < vec.size(); ++ i) {
        if (vec[i] == vec[i - 1] + 1) {
            if (maxx < vec[i] - st) {   
                maxx = vec[i] - st;
                l = st,r = vec[i];
            }
        } else {
            st = vec[i];
        }
    }
    cout << l << " " << r << "\n";
}
int main(void) {
    cin >> T;
    while (T --) {
        init();
        solve();
    }

    return 0;
}
```

---

## 作者：FQR_ (赞：4)

[题目传送门](/problem/CF1676F)

### 题目大意

给定序列 $a$ ，求出区间 $ [ l , r ] $ ，使区间内所有数都出现不少于 $k$ 次。最大化 $r - l$ 。

### 思路

看到“区间内所有数都出现不少于 $k$ 次”,我们就可以想到，把出现个数超过 $k$ 的数字枚举出来。

使用一个map：`map<int,int> a;`，其中 $a_i$ 表示 $i$ 出现的次数。

```cpp
map<int,int> a;
int n,k,x;
cin>>n>>k;
for(int i=0;i<n;i++)
{
	cin>>x;
	a[x]++;
}
```
___
之后，我们把出现个数超过 $k$ 的数字存入 $b$ 数组里。

```cpp
int b[200005],t=0;
for(map<int,int>::iterator it=a.begin();it!=a.end();it++)
{
	if(it->second>=k) b[t++]=it->first;
}
```
___
此时，我们只要找到 $b$ 中最长的连续数字段就可以了。
```cpp
sort(b,b+t);//千万别忘记排个序
int l=b[0],r=b[0];//l，r代表答案
int ll=b[0];//ll表示暂时的左端点
for(int i=1;i<t;i++)
{
	if(b[i]!=b[i-1]+1) ll=b[i];//如果前后不相等，就把ll改为b[i]
	if(b[i]-ll>r-l) l=ll,r=b[i];//如果当前长度比当前结果大，就替换
}
```
___
### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		map<int,int> a;
		int n,k,x;
		cin>>n>>k;
		for(int i=0;i<n;i++)
		{
			cin>>x;
			a[x]++;
		}
		int b[200005],t=0;
		for(map<int,int>::iterator it=a.begin();it!=a.end();it++)
		{
			if(it->second>=k) b[t++]=it->first;
		}
		if(t==0) 
		{
			cout<<-1<<endl;
			continue;
		}
		sort(b,b+t);
		int l=b[0],r=b[0];
		int ll=b[0];
		for(int i=1;i<t;i++)
		{
			if(b[i]!=b[i-1]+1) ll=b[i];
			if(b[i]-ll>r-l) l=ll,r=b[i];
		}
		cout<<l<<" "<<r<<endl;
	}
	return 0;
}
```

---

## 作者：WaterSky (赞：3)

# [CF1676F Longest Strike](https://www.luogu.com.cn/problem/CF1676F)

这题似乎并不难。

---
题目让我们找一个其中任意元素在数列中出现不少于 $k$ 次的区间。

那么我们知道，在这题中，将这个数列排序并没有影响，那么可以将这个数列排序，以便下一步。

我们可以提前把数组中出现次数大于 $k$ 的数按顺序拎出来。

因为我们已经提前把原数组排了序，那么，我们可以保证现数组（所有元素在原数组中出现次数大于 $k$，且在现数组中只出现一次）有序。

又由于我们要求一段最长区间，那么到现在，这个问题就变成了求一段最长连续子序列。

额，应该之后就不用我多说了，上代码！

```
#include<bits/stdc++.h>
using namespace std;
long long T,n,k,a[1000005];
long long s[1000005],m;
long long x,ans;
long long l,r;
long long l1,r1;
int main(){
    cin>>T;
    while(T--){
        m=0,ans=0,l=0,r=0,l1=0; //归零
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);//排序
        for(int i=1;i<=n;i++){
            if(a[i]!=a[i-1]){
                if(x>=k && i!=1) m++,s[m]=a[i-1]; //找出所有数量大于 k 的数。
                x=1;
            }
            else x++;
        }
        if(x>=k) m++,s[m]=a[n]; //最后一定要记得也判断一下。
        x=0;
        if(m==0) {cout<<-1<<endl;continue;}//如果没有大于 k 的输出 -1。
        l=s[1];//记录左端点方便输出。
        for(int i=1;i<=m;i++)
        {
            if(s[i]==s[i-1]+1) x++;
            else{
                if(ans<x)
                ans=x,l1=l;//记录最大长度与其左端点。
                x=1,l=s[i];//归一，并且更新左端点。
            }
        }
        if(ans<x) ans=x,l1=l;//最后再判断一次。
        cout<<l1<<" "<<l1+ans-1<<endl;//输出区间。
    }
    return 0;
}
```

---

## 作者：Otue (赞：3)

## 思路
因为任何整数 $x∈[l,r]$，都要满足 $x$ 在 $a$ 中的出现次数不少于 $k$ 次。

所以只要存在一个 x 不符合，全部遭殃。则需要找到连续的一串符合要求的数字。

可能符合要求的数字（该数字出现次数大于等于 $k$ 次）可以提前处理出来，然后再 $O(n)$ 复杂度计算最长的连续数字。

整体时间复杂度 $O(n \log n)$，因为提前处理需要 `map`。

举个实际例子：

$a$ 数组为 `1 1 2 2 2 3 4 4 4 4 4`，而 $k=2$。

然而可能符合要求的数字为 $1,2,4$，连续的只有 $1,2$，则答案为 $2$。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	char c = ' ';
	int f = 1, x = 0;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}

inline void wr(int x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) wr(x / 10);
	putchar(x % 10 + '0');
}


const int N = 2e5 + 5;
int t, n, k;
int a[N];
vector<int> gg;

int main() {
	cin >> t;
	while (t--) {
		gg.clear();
		map<int, int> g;
		n = read(), k = read();
		for (int i = 1; i <= n; i++) a[i] = read(), g[a[i]]++;
		int maxn = 0, id = 0;
		for (auto i = g.begin(); i != g.end(); i++) {
			if (i -> second >= k) {
				gg.push_back(i -> first);
			}
	
		}
		if (gg.size() == 0) {
			puts("-1");
			continue;
		}
		sort(gg.begin(), gg.end());
		int l = gg[0], r = gg[0], st = gg[0];
		for (int i = 1; i < gg.size(); i++) {
			if (gg[i] == gg[i - 1] + 1) {
				if (maxn < gg[i] - st) {
					maxn = gg[i] - st;
					l = st, r = gg[i];
				}
			}
			else {
				st = gg[i];
			}
		}
		wr(l);
		putchar(' ');
		wr(r);
		putchar('\n');
	}
}
```

---

## 作者：3_14 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1676F)

# 题意

一共 $t$ 组数据，对于每组数据给你一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，最大化 $\left [ l,r \right ] $ 区间使得任意一个数在数组 $a$ 中出现次数不少于 $k$ 次。

# 思路

看到标签是 ```离散化```，所以可以用 ```map``` 来记录每一个数字出现的个数，然后考虑一下出现次数大于 $k$ 的数，处理下结果即可。

# 代码

[代码+AC记录](https://codeforces.com/problemset/submission/1676/295259768)

---

## 作者：lwx20211103 (赞：1)

## 题意

已有翻译，这里不多说了。

## 做法

既然有关数字的出现次数，那么我们可以用 `map` 维护每个数字的出现次数。然后把出现次数满足条件的数字放入容器里面。因为必须要连续的区间，满足条件的连续区间在容器里表现为前后相差 $1$。如果有区间满足条件并且数字更大，就更新答案。

关于容器的区间这里，比较好操作的就是用当前的数字减掉上一个数字。我们分别用四个变量 $l,r,lastnum,sum$ 表示答案左，答案右，更新到的上一个数字，$r-l$。

不满足条件，那么 $lastnum$ 就只能是当前这个数字。

满足条件，就再进行判断，如果枚举到的当前数字与 $lastnum$ 的差值比 $sum$ 大，就更新，$l$ 置为 $lastnum$，$r$ 就是当前数字。

最后输出 $l,r$ 即可。

## 代码

```cpp
// Problem: F. Longest Strike
// Contest: Codeforces - Codeforces Round 790 (Div. 4)
// URL: https://codeforces.com/contest/1676/problem/F
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define p_b push_back
#define ft first
#define nd second
#define pii pair<int, int>
#define pll pair<long long, long long>
#define YES cout << "YES" << "\n"
#define NO cout << "NO" << "\n"

using namespace std;

typedef long long ll;

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> nums(n);
	vector<int> v;
	map<int, int> mp;
	for (auto &&i : nums) 
		cin >> i, mp[i]++; //利用map储存每个数字的出现次数
	for (auto i : mp) //map自动给first升序排序
		if (i.nd >= k)
			v.p_b(i.ft);
	if (v.empty())
	{
		cout << "-1\n";
		return ;
	}
	int l, r, lastnum, sum = -114514;
	l = r = lastnum = v.front();
	for (int i = 1; i < v.size(); i++)
	{
		if (v[i] - v[i - 1] == 1)
		{
			if (v[i] - lastnum > sum) //如果答案比当前答案更大
			{
				sum = v[i] - lastnum;
				l = lastnum, r = v[i];//左边就是上一个数字，右边就是当前的数字
			}
		}
		else lastnum = v[i]; //不满足条件就更新上一个数字
	}
	cout << l << " " << r << "\n";
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}

```


---

## 作者：Engulf (赞：1)

首先找出所有出现次数 $\ge k$ 的数，存入数组 $s$，对 $s$ 排序，找出最长的连续序列的左右端点即可。

```cpp
// author: TMJYH09
// create time: 2022/05/11 00:18:45
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve(){
    int n,k;
    cin>>n>>k;
    vector <int> a(n);
    map <int,int> m;
    vector <int> s;
    for(auto &i:a){cin>>i,m[i]++;}
    for(auto &i:m){if(i.second>=k)s.push_back(i.first);}
    if(s.empty())return (void)(cout<<-1<<endl);
    sort(s.begin(),s.end());
    //for_each(s.begin(),s.end(),[](int x){cout<<x<<' ';});
    int l=s[0],r=s[0],pre=s[0];
    int _l=l,_r=r,ans=1;
    for(int i=1;i<s.size();i++){
        if(s[i]==pre+1){
            r=s[i];pre=s[i];
        }else{
            if((r-l+1)>ans){
                _l=l;_r=r;ans=r-l+1;
            }
            l=r=s[i];
            pre=s[i];
        }
    }
    if((r-l+1)>ans){
        _l=l;_r=r;ans=r-l+1;
    }
    cout<<_l<<' '<<_r<<endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int _;cin>>_;while(_--)solve();
    return 0;
}
```

---

## 作者：WilliamFranklin (赞：1)

不得不说，是一道超好的数列题。

前面几位大佬的方式有些复杂，我来写个谷民都能看懂的。

### 主要思路

一个朴素又简单的方法：用桶思想，将每一个数存在的次数都记录下来，看一看最多有多少个连续的数出现的次数都大于 $k$。

好啦。等！先别走！你是不是发现不对劲？题中说了：$1\le a_i\le 10^{9}$，所以如果真开 $10^{9}$ 的数组的话，空间会“太过充裕”啦！

唉，还要想一个更好的方法。

咦？我们是不是可以先将这个序列排队，这样就可以保证相同的数待在一起啦！其他的地方都同上。

好啦，上代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int ans[200005];
int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		sort(a + 1, a + n + 1);
		int sum = 0;
		for (int i = 1; i <= n;) {
			int weizhi = i;
			while(a[i] == a[weizhi] && i <= n) {
				i++;
			}
			if (i - weizhi >= k) {
				ans[++sum] = a[weizhi];
			}
		}
		if (sum == 0) {
			cout << "-1" << endl;
			continue;
		}
		int ansl = 0, ansr = 0;
		for (int i = 1; i <= sum;) {
			int l = ans[i], r = ans[i];
			i++;
			while (ans[i] == ans[i - 1] + 1 && i <= sum) {
				r = ans[i];
				i++;
			}
			if (ansr - ansl + 1 <= r - l + 1) {
				ansr = r;
				ansl = l;
			}
		}
		cout << ansl << ' ' << ansr << endl;
	}
}
```

可能会有些不足的地方，请大家指正，谢谢！

---

## 作者：Fireworks_Rise (赞：0)

# 解题思路

分析题目，想到可以用先把序列 $a$ 中的每个数的出现次数 $\ge m$ 的数放到 $vec$ 中，再对其中的数从小到大进行排序。

遍历整个 $vec$，寻找出一个数列 $b$，使得对于序列中除第一个数，每个数都有 $b_i- b_{i-1}=1$，并求出 $b_m-b_1$ 的最大值 $maxx$，最后输出左右端点即可。

奉上蒟蒻代码，使用 STL。

# Code

记得有多组数据，需要清零。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int t,n,k,a,b[N],q;
vector<int> vec;
signed main(){
	scanf("%lld",&t);
	while(t--) {
		map<int,int> mp;
		scanf("%lld%lld",&n,&k);
	    for(int i=1;i<=n;i++) {
	        scanf("%lld",&a);
	        mp[a]++;
	    }
	    for(map<int,int>::iterator it=mp.begin();it!=mp.end();++it)
	        if((*it).second>=k) vec.push_back((*it).first);
	    if(!vec.size()) {
	    	printf("-1\n");
	        continue;
	    }
	    sort(vec.begin(),vec.end());
	    int l=vec[0],r=vec[0],st=vec[0],maxx=0;
	    for(int i=1;i<vec.size();i++) {
	        if(vec[i]==vec[i-1]+1) {
	            if(maxx<vec[i]-st) {   
	                maxx=vec[i]-st;
	                l=st,r=vec[i];
	            }
	        } else st=vec[i];
	    }
	    printf("%lld %lld\n",l,r);
	    vec.clear();
	}
	return 0;
}
```

---

## 作者：legend_cn (赞：0)


# **解题思路：** 
 
这道题是在考察离散化思想，简单说是使用除了下标以外的索引进行查找元素。经典的离散化应用就是桶排。一般桶排都使用了个位进行索引，这就是一种**离散化**。

此题我使用了 map 实现离散化，因为 map 是一种比数组更智能的数据结构，可以使用任意类型的索引进行查找。 

对于每一组数据，首先需要使用一个 map 把所有的数进行统计，然后遍历 map 需要使用迭代器，查找 `map.second` 大于等于 m 的元素，插入到一个向量中。当向量为空时，输出 -1 ，否则，执行双指针寻找最大值。

#  **AC 代码：** 
 
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int a[N];

int main() 
{
	int t;
   cin >> t;
   while (t --) 
	{
       memset(a, 0, sizeof(a));
        
	    int n, m;
	    cin >> n >> m;
          
	    map<int, int> mp;
	    map<int, int> :: iterator it;//迭代器，因为需要遍历 map
          
	    for (int i = 1; i <= n; i ++ )
	    {
	        cin >> a[i];
	        mp[a[i]] ++;
	     }
	    
	     vector<int> V;
	     for (it = mp.begin(); it != mp.end(); it ++ )
	     {
	        if ((*it).second >= m) 
           {
	            V.push_back((*it).first);
           }
        }
	    
        if (!V.size())//vector为空，代表没有数字符合题意
        {
	         puts("-1");
	         continue;
	      }
	    
	      sort(V.begin(), V.end());
	    
         int l = V[0];
         int r = V[0];
         int tmp = V[0];
	      int maxn = INT_MIN;
		
	      for (int i = 1; i < V.size(); i ++ )//双指针
	      {
	          if (V[i] == V[i - 1] + 1)
             {
	               if (maxn < V[i] - tmp)//需要更新答案
	               {   
	                   maxn = V[i] - tmp;
	                   l = tmp；
                      r = V[i];
	               }
	          }
             else 
             {
	              tmp = V[i];
             }
	    }
	    
	    cout << l << " " << r << endl;
    }

    return 0;
}
```

---

## 作者：Deamer (赞：0)

# 题意：

给你一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，我们要最大化 $l-r+1$ 使得区间 $[l,r]$ 中任意一个数在 $a$ 出现不少于 $k$ 次。

# 思路

我们用一个 map 存一下每个数在 $a$ 中出现的总次数。

然后我们依次考虑一下 map 里出现次数大于 $k$ 的数，处理下结果即可。

复杂度大约是 $O(n)$ 。

**code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
map<int,int> mp;
map<int,int> s;
int main(){
	scanf("%d",&T);
	while(T--){
		mp.clear();
		s.clear();
		scanf("%d%d",&n,&k);
		int x,r,maxn=-1;
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			mp[x]++;
		}
		for(auto i=mp.begin();i!=mp.end();i++){		//迭代器
			int x=i->first,y=i->second;
			if(y<k) continue;
			s[x]=s[x-1]+1;							//类似dp思想
			if(s[x]>maxn){							//记录最优解	
				r=x;
				maxn=s[x];
			}
		}
		if(maxn!=-1) printf("%d %d\n",r-maxn+1,r);		//用最优解算出左端点
		else printf("-1\n");
	}
	return 0;
}
```
再来说一种方法，就是处理结果与上文不同。

这次我们先把 $a$ 排序并去重，再扫一遍，把所有出现过 $k$ 次以上的都存在数组 $s$ 里。这样 $s$ 数组就是不重复且有序的了，这样再扫起来就会省点时间。接下来处理结果就行了。

**code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,k;
int a[N],s[N];
map<int,int>mp;
int m,l,r,ansl,ansr,maxn,cnt;
int main(){
	scanf("%d",&T);
	while(T--){
		mp.clear();
		scanf("%d%d",&n,&k);
		maxn=-1;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			mp[a[i]]++;
		}
		for(int i=1;i<=n;i++) maxn=max(maxn,mp[a[i]]);
		if(maxn<k){							//特判-1
			printf("-1\n");
			continue;
		}
		sort(a+1,a+1+n);					//记得排序	
		m=unique(a+1,a+1+n)-a-1;			//去重操作，实际上就是把重复的移到数组末尾，m存的是去重后的长度
		cnt=0;
		for(int i=1;i<=m;i++){
			if(mp[a[i]]>=k) s[++cnt]=a[i];
		}
		 maxn=-1,l=1,r=0;
		s[0]=s[1]-1;						//千万不要忘了……
		for(int i=1;i<=cnt;i++){
			if(s[i]-s[i-1]!=1){				//不是连续的（到头了）
				if((r-l+1)>maxn){			//更新最优解
					maxn=r-l+1;
					ansl=s[l]; ansr=s[r];
				}
				l=r=i;						//更新l和r
			}
			else r++;						//如果还是连续的，就继续看看r+1是否连续
		}
		if((r-l+1)>maxn) ansl=s[l],ansr=s[r];	//记得还要更新一遍最优解。
		printf("%d %d\n",ansl,ansr);
	}
	return 0;
}
```
最后提几个第 2 种方法几个可能错的点吧：

- 丢了   ```s[0]=s[1]-1;```

- 丢了   ```if((r-l+1)>maxn) ansl=s[l],ansr=s[r];``` 因为最优解的 $r$ 可能到 $n$ ，我们执行完 ```r++``` 之后没更新答案就退出循环了，所以我们还要再更新一遍答案。




---

## 作者：5k_sync_closer (赞：0)

# 题意
给你一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，你要求一个区间 $[l,r]$ 满足：

- 对于任何整数 $x∈[l,r]$，$x$ 在 $a$ 中的出现次数不少于 $k$ 次。
- 最大化 $r-l$。

无解输出 `-1`。
# 思路
看到出现次数，先把 $a$ 装进桶 $c$ 里，

发现装不进去，就离散化一下再装进桶 $c$ 里。

令 $l,r$ 存正在处理的区间，$x,y$ 存目前最大的区间，$s$ 存目前最大区间的大小。

接着按离散化后的 $a_i$ 从小到大扫一遍：

- 如果 $c_i≥k$，区间可以包含 $a_i$，则 $r\gets a_i$，
>1. 如果 $a_i≠a_{i-1}+1$，不能与之前的区间接上，则“另起炉灶”，$l\gets a_i$。
>2. 否则 $l$ 保持原值不变。
>3. 用 $l,r$ 更新 $x,y,s$。
- 否则区间不能包含 $a_i$，$l\gets a_{i+1},r\gets a_{i+1}$。

注意这里 $a_1$ 必须“另起炉灶”，因为 $a_1$ 之前没有别的区间。

所以我们要手动让 $a_1≠a_0+1$，$a_0\gets-1$ 即可。

最后如果 $s$ 从未被更新过就是无解，否则解为 $[x,y]$。
# 代码
```cpp
#include <cstdio>
#include <algorithm>
#define h(x) lower_bound(a + 1, a + m + 1, x) - a
using namespace std;
int T, n, m, k, s, l, r, x, y, a[200050], b[200050], c[200050];
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &k);s = -1;
        for(int i = 1;i <= n;++i) scanf("%d", &a[i]), b[i] = a[i];
        sort(a + 1, a + n + 1);m = unique(a + 1, a + n + 1) - a - 1;
        for(int i = 1;i <= m;++i) c[i] = 0;
        for(int i = 1;i <= n;++i) ++c[h(b[i])];a[0] = -1;
        for(int i = 1;i <= m;++i)
            if(c[i] >= k)
            {
                if((r = a[i]) != a[i - 1] + 1) l = a[i];
                if(r - l > s) s = r - l, x = l, y = r;
            }
            else l = r = a[i + 1];
        if(s == -1) puts("-1");
        else printf("%d %d\n", x, y);
    }
    return 0;
}

```


---

## 作者：Withers (赞：0)

[题目传送门](https://codeforces.com/contest/1676/problem/F)
# 题目大意
给出 $n$ 个数，求最长连续的区间 $[l,r]$，使得 $r-l+1$ 最大，其中的数在数列里都出现了 $\ge k$ 次

# 思路
因为数据范围，所以必须要离散或用 map

这里我选择用 map，然后再开了个 map 记录答案

我们用这个 map 来存以 $x$ 结尾的最长连续区间长度

使用迭代器遍历，然后 dp 处理，记录最大值即可

状态转移方程：

$dp[i]=dp[i-1]+1( y\ge k)$，$dp[i]$ 表示以 $i$ 结尾的最长序列长度，$y$ 表示 $i$ 在数组中出现的个数。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200010];
//char s[200010];
map<int,int> mp;
map<int,int> ans;
int x,y,z,k;
void w1() 
{
	//scanf("%s",s+1);
}
void w2()
{
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		mp.clear();
		ans.clear();
		//memset(ans,0,sizeof(ans));
		scanf("%d%d",&n,&k);
		//w1()
		w2();
		for(int i=1;i<=n;i++)
		{
			mp[a[i]]++;
		}
		int lst=0,maxx=-1,maxi=-1;//初始化
		for(auto iter=mp.begin();iter!=mp.end();iter++)
		{//迭代器遍历
			x=iter->first,y=iter->second;
			if(y<k) continue;
			ans[x]=ans[x-1]+1;
			if(ans[x]>maxx)
			{
				maxi=x;
				maxx=ans[x];//比大小，记录最佳情况
			}
		}
		if(maxx!=-1) printf("%d %d\n",maxi-maxx+1,maxi);
		else printf("-1\n");
	}
}
```


---

