# [入门赛 #10] Coin Selection G（hard version）

## 题目描述

Farmer John 和 Bessie 正在一起玩硬币选择游戏。

初始时桌面上有 $n$ 枚硬币，每枚硬币有一个面额，我们使用 $a _ 1, a _ 2, \cdots, a _ n$ 分别代表第 $1, 2, \cdots, n$ 枚硬币的面额。

他们还各有一个属于自己的钱包，初始时，钱包都是空的。

从 **Bessie** 开始，双方轮流操作。每次操作中，当前的操作者会从桌面上剩余的硬币中选择**面值不超过当前自己钱包中硬币的总面额**的硬币中**面额最大的**一枚硬币，把它从桌子上拿走，放到自己的钱包里。如果桌面上剩余的**所有**硬币面值都**超过了自己钱包里已有硬币的总面额**，那么选择剩余的所有硬币中面额**最小**的一个。

当桌面上没有硬币时，游戏结束。

请你分别求出，	游戏结束后，Farmer John 和 Bessie 钱包里硬币的总面额。

## 说明/提示

### 数据规模与约定

- 对 $100\%$ 的数据，保证 $1 \leq n \leq 10^5$，$1 \leq a_i \leq 10^{9}$。

Provider：一扶苏一

## 样例 #1

### 输入

```
2
3 2```

### 输出

```
2 3```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
9 6```

# 题解

## 作者：_GeorgeAAAADHD_ (赞：7)

**注：本题作者使用二分算法。**

感谢 @[zhuweiqi](https://www.luogu.com.cn/user/909294) 指出重大错误。

------------
### 题目大意：

给定 $n$ 和 $n$ 个正整数 $a_i$，你需要输出两个数字 $sum1$ 和 $sum2$。

总共执行 $n$ 次操作，当这次操作为第奇数次操作时，在所有 $a_i$ 中找到一个最大但不超过 $sum1$ 的 $a_i$，加上它并将它删去。如果所有 $a_i$ 均大于 $sum1$，将 $sum1$ 加上最小的 $a_i$ 并将这个 $a_i$ 删去。如果这次操作是第偶数次操作，则对 $sum2$ 执行同样的操作。

数据范围：$1 \le n \le 10^5$，$1 \le a_i \le 10^9$。

------------
### 分析：

暴力枚举是 $O(n^2)$ 算法，肯定超时。

于是我们思考一下二分的做法。

发现将 $a_i$ 升序排序后，可以利用二分查找最大但不超过 $sum1$ 或 $sum2$ 的 $a_i$。注意排序时应写成 `sort(a.begin(),a.end());`。

然后我们用一个 `vector` 存储所有 $a_i$，动态维护这个 `vector`，每次操作后将要删除的 $a_i$ 删除就可以了。这个地方需要用到 `iterator`，即迭代器，可以自行上网搜索。

于是我们便愉快地 AC 了本题。

**注：$sum1$ 和 $sum2$ 的最终结果有可能会超过 `int` 范围，因此我们要开 `long long`。**

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,suma=0,sumb=0,k;
bool f=1;
vector<long long> a;
void add(long long &sum){
	int l=0,r=a.size()-1,ans=0,x=0;
	while(l<=r){
		int mid=(l+r)/2;
		if(a[mid]<=sum){
			x=mid;
			ans=a[mid];
			l=mid+1;
		}
		else r=mid-1;
	}
	if(!ans){
		sum+=a[0];
		a.erase(a.begin());
	}
	else{
		sum+=a[x];
		a.erase(a.begin()+x);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>k;
		a.push_back(k);
	}
	sort(a.begin(),a.end());
	for(int i=1;i<=n;i++){
		if(f)add(suma);
		else add(sumb);
		f=!f;
	}
	cout<<suma<<' '<<sumb;
}
```

---

## 作者：Huangjy88 (赞：1)

# P7891题解
一道二分查找的好题！

如果暴力模拟，时间复杂度为 $O(n^{2})$，过不了此题，考虑用二分来优化。先对序列排序，对于每次操作，设现有面额为 $m$，若 $m$ 小于最小值，直接选取最小值。否则，可以用函数 `upper_bound` 找出小于等于 $m$ 且最大的数，选取即可。由于序列长度会变化，可以用 `vector` 来维护。时间复杂度为 $O(n\log_{2}{n})$。

`AC Code`：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<int>a;
int res[2];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
	int x;cin>>x;
	a.push_back(x);
    }
    sort(a.begin(),a.end());
    for(int i=1;i<=n;i++){
	int k=i%2;
	if(res[k]<a[0]){
	    res[k]+=a[0];
	    a.erase(a.begin());
	}
	else{
	    int m=upper_bound(a.begin(),a.end(),res[k])-a.begin();
	    res[k]+=a[m-1];
	    a.erase(a.begin()+m-1);
	}
    }
    cout<<res[1]<<' '<<res[0];
    return 0;
}

```
注释就不加了，~~一定要开 `long long`！！~~

---

## 作者：Wangjunhao2011 (赞：1)

## 题目纠正
题目中的输出格式说的是输出两行，其实是输出一行。
## 正解
看见各位大佬都用 ``vector``,我赶紧来水一发 ``map`` + ``set`` 组合。

``set`` 中虽然没有直接返回一个指向第一个不大于给定值的元素的迭代器，但有直接返回一个指向第一个不小于给定值的元素的迭代器 ``lower_bound()``。而且时间复杂度也是 $O(\log n)$。于是我们稍加改造，一个直接返回一个指向第一个不大于给定值的元素的迭代器就好了。
```cpp
set<int>::iterator it=s.lower_bound();
if(*it!=x)//x是给定值
it--;
```
这道题就是一道模拟题，乖乖按题目要求做就行，切记不可用暴力时间复杂度是 $O(n^2)$，$n$ 又小于等于 $10^5$，绝对 ``TLE``。就算开 $O2$ 也救不回来。

我们用 ``set`` 储存元素，``map`` 储存元素个数。

你问我为什么不用 ``multiset``？那是因为 ``multiset`` 的删除是将所有与想删除的数相同的元素全部删除，不方便。

还有，这道题还有一个坑，要开 ``long long``！

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//将所有int替换成long long
signed main(){       //signed与int相同
	map<int,int>mp;  
	set<int>s;
	int a=0,b=0;
	int n;cin>>n;
	for(int i=1;i<=n;i++){
		int op;cin>>op;
		s.insert(op);
		mp[op]++;
	}
	set<int>::iterator it,itt;
	for(int i=1;i<=n;i++){
		if(i%2==1){
			it=s.begin();
			if(*it>b){
				b+=*it;
				mp[*it]--;
				if(mp[*it]==0){
					s.erase(*it);
				}
			} 
			else{
				itt=s.lower_bound(b);
				if(*itt!=b) 
				itt--;
				b+=*itt;
				mp[*itt]--;
				if(mp[*itt]==0){
					s.erase(*itt);
				}
			}
		}
		else{
			it=s.begin();
			if(*it>a){
				a+=*it;
				mp[*it]--;
				if(mp[*it]==0){
					s.erase(*it);
				}
			} 
			else{
				itt=s.lower_bound(a);
				if(*itt!=a) 
				itt--;
				a+=*itt;
				mp[*itt]--;
				if(mp[*itt]==0){
					s.erase(*itt);
				}
			}
		}
	}
	cout<<b<<" "<<a;
	return 0;
} 
```

---

## 作者：HDZmessi (赞：1)

TLE 了三个月终于过了，太不容易了！！

大多数人最先想到的是暴力枚举，但再看看数据范围发现根本无法水过此题，怎么办呢？其实这道题考察的就是我们如何把平方复杂度转换成对数复杂度，所以要用分治思想，显然二分查找是最合适的。

不会二分查找的同学们可以[点击这里](https://blog.csdn.net/qq_52188351/article/details/124548842)，二分查找会的大佬们就可以开始分析此题了，首先每次每人取硬币的时候都用二分查找寻找题目要求的数据，然后用 vector 容器进行维护，注意，***一定要把 vector 容器维护的步骤加入到二分函数里***，我就是因为这个才 TLE 了一次，下面是我的错误代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll> p;
ll fj,b,n;
ll check(ll a){
	if(a<p[0]) return p[0];
	ll left=0,right=p.size()-1,mid,ans;
	while(left<=right){
		mid=(left+right)/2;
		if(p[mid]>a){
			right=mid-1;
		}
		else{
			left=mid+1;
			ans=p[mid];
		}
	}
	return ans;
}
int main(){
	cin>>n;
	ll m=n;
	for(int i=0;i<n;i++){
		ll u;cin>>u;
		p.push_back(u);
	}
	sort(p.begin(),p.end());
	while(!p.empty()){
		if(m%2==n%2){
			ll x=check(b);
			b+=x;
			auto it=find(p.begin(),p.end(),x);
			p.erase(it,it+1);
		}
		else{
			ll x=check(fj);
			fj+=x;
			auto it=find(p.begin(),p.end(),x);
			p.erase(it,it+1);
		}
		m--;
	}
	cout<<b<<" "<<fj;
	return 0;
} 
```
大家可以看到我的以上代码把维护的过程放在了循环里面，导致计算机还要每次进行一次找寻元素的函数，这是一个无用功，只需要每次记录查找结果的迭代器就行了。 用 auto 来记录是最方便的（不懂的[点击这里](https://blog.csdn.net/qq_42957923/article/details/90107840)），于是就有了一下的 AC 代码。

AC Code:

```cpp
#include<bits/stdc++.h> //万能头 
#define ll long long  //恒定义后面更好操作 
using namespace std;
vector<ll> p;  //vector维护 
ll fj,b,n;
ll check(ll a){
	auto it=p.begin();  //初始化迭代器 
	if(a<p[0]){
		ll y=p[0];
		p.erase(it);   //进行维护 
		return y;
	} 
	ll left=0,right=p.size()-1,mid,ans;
	while(left<=right){   //二分查找 
		mid=(left+right)/2;
		if(p[mid]>a){
			right=mid-1;
		}
		else{
			it=p.begin()+mid;  //记录结果的迭代器 
			left=mid+1;
			ans=p[mid];
		}
	}
	p.erase(it);  //维护别忘了！ 
	return ans;
}
int main(){
	cin>>n;
	ll m=n;
	for(int i=0;i<n;i++){
		ll u;cin>>u;
		p.push_back(u);
	}
	sort(p.begin(),p.end());  //排序 
	while(!p.empty()){
		if(m%2==n%2){  //判断这次是谁取硬币 
			ll x=check(b);
			b+=x;
		}
		else{
			ll x=check(fj);
			fj+=x;
		}
		m--;
	}
	cout<<b<<" "<<fj;
	return 0;   //华丽结束！ 
} 
```
希望我的题解能对大家有帮助！

---

## 作者：Po7ed (赞：1)

**[题目传送门](https://www.luogu.com.cn/problem/P7891)**

### 错误思路
暴力模拟，显然 $O(n^2)$，过不了 $1 \leq n \leq 10^5$。
### 正解
#### 思路
重新看题面，可以发现想快速查找
>面值不超过当前自己钱包中硬币的总面额的硬币中面额最大的一枚硬币

可使用二分法。

#### 算法流程
- 将读入的硬币数组排序（或在输入时就用二分插入使数组有序）。
- 判断当前自己钱包里已有硬币的总面额是否大于等于最小的硬币。
  - 若是，则取合适的硬币。
  - 若不是，则取面值最小的硬币。
- Farmer John 和 Bessie 交替取硬币。

#### STL
因为硬币一直被取走，所以可以用 `vector` 动态存储硬币面值。

用 `lower_bound(begin,end,value)` 查找从小到大排序的数组在[begin,end)区间中第一个大于等于 `value` 的数，并返回一个迭代器指向此数。

#### 代码

```cpp
//by Po7ed
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	long long n;
	scanf("%lld",&n);
	vector<long long> v;//存储硬币面值
	long long t;
	for(long long i=0;i<n;i++)
	{
		scanf("%lld",&t);
		v.insert(lower_bound(v.begin(),v.end(),t,greater<long long>()),t);
        //此处在输入时直接用lower_bound插入面值。使得v有序（从大到小）。
        //lower_bound用greater<long long>()重载，使lower_bound知道v是从大到小排序的。下同。
	}
	long long a=0,b=0;
	for(long long i=1;v.size();i++)
	{
		if(i&1)//当取奇数次时
		{
			if(a<v.back())//如果面值不够
			{
				a+=v.back();
				v.pop_back();
			}
			else//如果面值够
			{
				t=lower_bound(v.begin(),v.end(),a,greater<long long>())-v.begin();
                //查找合适的硬币
				a+=v[t];
				v.erase(v.begin()+t);
			}
		}
		else//当取偶数次时
		{
			if(b<v.back())//如果面值不够
			{
				b+=v.back();
				v.pop_back();
			}
			else//如果面值够
			{
				t=lower_bound(v.begin(),v.end(),b,greater<long long>())-v.begin();
                //查找合适的硬币
				b+=v[t];
				v.erase(v.begin()+t);
			}
		}
	}
	printf("%lld %lld",a,b);
	return 0;
}
```
### 注意事项
不开 `long long` 见祖宗！
### 参考
[upper_bound和lower_bound用法（史上最全）](https://zhuanlan.zhihu.com/p/576200578)

---

## 作者：liupan2010 (赞：1)

前言：

[题目传送门](https://www.luogu.com.cn/problem/P7891)

简单二分，但是我做了好久！我真的太菜了。

思路：

STL 大法好！

因为硬币数量会变，所以我们可以用 ``vector`` 进行维护。

为了二分，我们先将硬币金额排序，可以用 ``sort``。

如果操作者金额比当前硬币金额都小，那么直接取最小的即可。

否则我们可以用 ``upper_bound`` 查找最大的不超过操作者金额的迭代器。

你可以看到，STL 把整个题都包揽了下来。

代码：

省略了快读快写，想要的话[点这里](https://www.luogu.com.cn/paste/5szj8hn6)。

码风有点清奇，请见谅。

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
long long FarmerJohn,Bessie,Temp;
int n,Money;
bool Turn;
vector<long long> Coin;
int main(){
    n=Read();
    while(n--) Money=Scan(),Coin.push_back(Money);
    sort(Coin.begin(),Coin.end());
    while(Coin.size()){
        if(!Turn){
            if(FarmerJohn<Coin[0]){
            	FarmerJohn+=Coin[0];
				Coin.erase(Coin.begin());
			}
            else{
            	Temp=FarmerJohn;
				FarmerJohn+=Coin[upper_bound(Coin.begin(),Coin.end(),FarmerJohn)-Coin.begin()-1];
				Coin.erase(upper_bound(Coin.begin(),Coin.end(),Temp)-1);
			}
        }
        else{
            if(Bessie<Coin[0]){
            	Bessie+=Coin[0];
				Coin.erase(Coin.begin());
			}
            else{
            	Temp=Bessie;
				Bessie+=Coin[upper_bound(Coin.begin(),Coin.end(),Bessie)-Coin.begin()-1];
				Coin.erase(upper_bound(Coin.begin(),Coin.end(),Temp)-1);
			}
        }
        Turn=!Turn;
    }
    Write(FarmerJohn),putchar_unlocked(' '),Write(Bessie);
    return 0;
}
```

鸣谢：

感谢[天南星魔芋](https://www.luogu.com.cn/user/399239)在[这个帖子](https://www.luogu.com.cn/discuss/619370)所给予的帮助！

---

