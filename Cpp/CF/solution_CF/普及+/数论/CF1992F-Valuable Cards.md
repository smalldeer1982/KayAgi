# Valuable Cards

## 题目描述

In his favorite cafe Kmes once again wanted to try the herring under a fur coat. Previously, it would not have been difficult for him to do this, but the cafe recently introduced a new purchasing policy.

Now, in order to make a purchase, Kmes needs to solve the following problem: $ n $ cards with prices for different positions are laid out in front of him, on the $ i $ -th card there is an integer $ a_i $ , among these prices there is no whole positive integer $ x $ .

Kmes is asked to divide these cards into the minimum number of bad segments (so that each card belongs to exactly one segment). A segment is considered bad if it is impossible to select a subset of cards with a product equal to $ x $ . All segments, in which Kmes will divide the cards, must be bad.

Formally, the segment $ (l, r) $ is bad if there are no indices $ i_1 < i_2 < \ldots < i_k $ such that $ l \le i_1, i_k \le r $ , and $ a_{i_1} \cdot a_{i_2} \ldots \cdot a_{i_k} = x $ .

Help Kmes determine the minimum number of bad segments in order to enjoy his favorite dish.

## 样例 #1

### 输入

```
8
6 4
2 3 6 2 1 2
9 100000
50000 25000 12500 6250 3125 2 4 8 16
5 2
1 1 1 1 1
8 6
4 3 4 3 4 3 4 3
7 12
6 11 1 3 11 10 2
10 5
2 4 4 2 4 4 4 3 1 1
7 8
4 6 5 1 2 4 1
8 27
3 9 17 26 2 20 9 3```

### 输出

```
3
2
1
1
2
1
3
3```

# 题解

## 作者：I_will_AKIOI (赞：4)

考虑贪心做法。尽可能地把数放进一个区间内，直到放进去不合法才另开一个区间。

在把数放进区间的过程，容易想到用一个数组 $cnt$ 记录当前区间能不能凑出某个数字。若 $cnt_i=1$ 说明能凑出 $i$，否则不能。把一个数放进去之后，枚举 $cnt$ 的每一位，然后更新 $cnt$，类似 dp 的思想，若当前放进去的为 $a$，转移方程就是 $cnt_{i\cdot a}=\max(cnt_{i\cdot a},cnt_i)$。发现 $i\cdot a>x$ 就没什么用，就不需要枚举了。

但是这样复杂度为 $O(n^2)$，开了四秒还是过不去。发现只有当 $a$ 是 $x$ 的因数时，才有可能凑出 $x$，否则肯定是凑不出的。所以我们预处理出 $x$ 的因数再枚举，复杂度就降到了 $O(n\sqrt{n})$。注意在 $cnt$ 转移的时候，因数要从大到小枚举，不然会发生重复使用一个数的情况，原因类似背包问题第二层循环枚举的顺序问题。

```cpp
#include<bits/stdc++.h>
#define N 100005
#pragma GCC optimize("O3")
using namespace std;
int n,k,a[N],d[N];
vector<int>v;
void solve()
{
  int ans=1;
  cin>>n>>k;
  for(int i=1;i<=n;i++) cin>>a[i];
  v.clear();
  for(int i=1;i*i<=k;i++)
  {
    if(k%i==0)
    {
      v.push_back(i);
      if(i*i!=k) v.push_back(k/i);
    }
  }
  sort(v.begin(),v.end(),greater<int>());
  for(int now:v) d[now]=0;
  d[1]=1;
  for(int i=1;i<=n;i++)
  {
    if(k%a[i]) continue;
    if(d[k/a[i]])
    {
      ans++;
      for(int now:v) d[now]=0;
      d[1]=d[a[i]]=1;
    }
    else for(int now:v) if(k%(now*a[i])==0) d[now*a[i]]|=d[now];
  }
  cout<<ans<<"\n";
  return;
}
int main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：liaoz123 (赞：3)

首先有一个明显的贪心思路，我们从第一项开始往后延申，如果当前所有数仍不能合成 $x$，那么我们可以贪心地继续向下走，如果可以，则在当前位与前一位之间划分，这就能保证上一段不能合成 $x$ 且尽量长。

考虑实现这个贪心过程。

明显只有 $x$ 的因子对合成 $x$ 有作用，因为不是它的因子的数无论如何都合成不了 $x$。也就是说只有 $x$ 的因子是有用的。

注意到 $x$ 的范围只有 $10^5$，而 $10^5$ 内的数因子最多不超过 $128$ 个，这就启发我们以 $x$ 的因子作为一个状态，做一个类似背包的东西，具体来说，维护一个数组 $f_k$，表示当前的段能否合成出 $x$ 的一个因子 $k$。那么我们只要在向后延申的时候，遇到 $x$ 的因子时，就用它更新我们的 $f$，当能合成出 $x$ 时就说明我们需要在这里重新划分一段。

代码实现是容易的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int n,a[N],k,m;
vector<int> q;
bool vis[N],f[N];
int main(){
	int t;cin>>t;
	while(t--){
		q.clear();
		cin>>n>>k;int ans=1;f[1]=1;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=sqrt(k);i++)
		if(k%i==0){
			q.push_back(i);vis[i]=true;
			if(i*i!=k)q.push_back(k/i),vis[k/i]=true;
		}
		sort(q.begin(),q.end());
		for(int i=1;i<=n;i++){
			if(!vis[a[i]])continue;
			for(int j=q.size()-1;j>=0;j--)
			if(q[j]%a[i]==0)f[q[j]]|=f[q[j]/a[i]];
			if(f[k]){
				ans++;
				for(int j=0;j<q.size();j++)f[q[j]]=false;f[1]=true;
				for(int j=q.size()-1;j>=0;j--)
				if(q[j]%a[i]==0)f[q[j]]|=f[q[j]/a[i]];
			}
		}
		cout<<ans<<endl;
		for(int i=1;i<=k;i++)vis[i]=false,f[i]=false;
	}
	return 0;
}
```

---

## 作者：OIer_Hhy (赞：3)

# Part 1：前言

### 题目翻译

在他最喜欢的咖啡馆里，Kmes再次想尝尝皮草大衣下的鲱鱼。以前，这对他来说并不难，但咖啡馆最近推出了一项新的购买政策。

现在，为了进行购买，Kmes需要解决以下问题：在他面前摆放着 $n$ 张不同价格的卡，第 $i$ 张卡的价格为 $a_i$，在这些价格中没有整数 $x$
。

Kmes被要求将这些卡划分为最少数量的坏段（这样每张卡只属于一个段）。如果无法选择乘积等于 $x$ 的卡子集，则认为该段是坏的。Kmes 划分卡片的所有段都必须是坏的。

从形式上讲，如果没有下标 $i_1<i_2<\ldots<i_k$，使得 $l\le i_1,i_k\le r$ 且 $\prod _ {j=1} ^ {k}  a_{i_j} = x$，则段 $(l,r)$ 是坏的。

帮助Kmes确定坏段的最小数量，以便享受他最喜欢的菜肴。

### 输入格式
第一行包含一个整数 $t（1\le t\le 10^3）$——测试用例的数量。

每组输入数据的第一行分别给出整数 $n$ 和 $x(1\le n\le 10^5，2\le x\le 10^ 5)$——卡片数量和整数。

每组输入数据的第二行包含 $n$ 个整数$a_i(1\le a_i\le 2\cdot 10^5，a_i\neq x)$——卡片上的价格。

保证所有测试数据集的 $n$ 总和不超过$10^5$。

### 输出格式

对于每组输入数据，输出坏段的最小数量。

# Part 2：思路

这道题，咱就选择贪心吧（主要是我 dp 不大会）。

坏段 $B$ 的定义：$\exist$ 子序列 $A \in B, \prod A=x$。

显然，一个坏段的长度是有单调性的：当 $a_1,a_2,\dots,a_k$ 是坏段时，$a_1,a_2,\dots,a_{k+1}$ 也必定是坏段。

所以，我们每次判断出一个段是坏段时，就把 ans 加一。

怎么判断呢？考虑用一个速度更快的 unordered_set，存储之前所有子序列的乘积。

每次循环遍历这个 unordered_set，令当前遍历到的为 $k$。当 $a_i \times k=x$ 时，我们就知道，已经有一个坏段产生了。我们把 unordered_set 清空，将 ans 加一。

但是这样时间复杂度太高，极端情况下，复杂度为 $O(nx) \approx 10^{10}$，即使 4s 时限，也救不了你。

所以我们要考虑优化。

- 当 $x \bmod (a_i \times k)=0$ 时，将 $a_i \times k$ 放入 unordered_set 里。

- 当 $x \bmod(a_i \times k)\neq 0$ 时，由于无论之后的数怎么样，子序列的乘积已经 $\neq x$ 了，就舍去。


# Part 3：代码

你们终于来到了这里
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
ll t,n,x,a[N],ans;
unordered_set<ll> st,us;
inline void FIO(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #define endl '\n'
} 
inline void work(){
	st.clear();us.clear();ans=1;
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		for(auto j:st){
			ll k=a[i]*j;
			if(x%k==0){
				if(k==x){
					ans++;st.clear();us.clear();
					break;
				}
				us.insert(k);
			}
		}
		for(auto j:us) st.insert(j);
		us.clear();
		if(x%a[i]==0) st.insert(a[i]);
	}
	cout<<ans<<endl;
}
signed main(){
    FIO();
    cin>>t;
    while(t--) work();
}
```

![](https://cdn.luogu.com.cn/upload/image_hosting/skzfni9b.png)

满江绿的感受，是那样的美好，那么的舒适！

---

## 作者：OIerYang (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1992F)

此题我的思路为暴力枚举。~~主要是不太会dp~~

每次把是 $x$ 的因数的 $a_i$ 放进一个集合。

将一切不符合条件的都去掉。

然后做一遍过滤操作：
```cpp
for(auto j:p){
		int k=a[i]*j;
		if(x%k==0){
			if(x==k){
				ans++;p.clear();q.clear();break;
			}
			q.insert(k);
		}
}
```
再把 $q$ 集合中的数转移到 $p$ 集合中。

你们最想看的来了：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n,m;cin>>n>>m;
	vector<int>a(n);
	set<int>s,t;
	int ans=1;
	for(int i=0;i<n;i++){
		cin>>a[i];
		for(auto p:s){
			int k=a[i]*p;
			if(m%k==0){//符合条件的
				if(k==m){
					ans++;//是一个答案
					s.clear();t.clear();
					break;//全部"重开"
				}
				t.insert(k);//符合条件的放入另一个集合中
			}
		}
		for(auto q:t)s.insert(q);转移
		t.clear();//t集合清零做下次操作用
		if(m%a[i]==0)s.insert(a[i]);//是因数的放入
	}cout<<ans<<endl;
}
signed main(){
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：寄风 (赞：1)

### 题意：
定义一个区间 $[l,r]$ 是坏的，当且仅当这个区间内不存在 $i_1<i_2<...<i_k$ 满足 $l\leq i_1,i_k\leq r$ 并且 $\prod \limits_{j=1}^k a_{i_j}=x$（$x$ 在输入中给出）。现在给你一个长度为 $n$ 的序列 $a$ 和 一个正整数 $x$，请你求出最少能把整个序列划分成几个坏区间。

### 题解：
先判断掉 $a_i$ 不是 $x$ 因子的情况，然后开一个 $\operatorname{set}$ 去维护目前因子所带来的乘积，若是超过了 $x$ 就删除，如果等于 $x$ 就直接把答案加 $1$，然后把枚举的位置减去 $1$。不难发现，$x$ 因子的乘积只有 $3$ 种情况：

1. 结果是 $x$，直接把目前的划分段数加一，然后清空 $\operatorname{set}$。
1. 结果是 $x$ 的倍数，直接删除这个数。
1. 结果是 $x$ 的因数。

所以，$\operatorname{set}$ 里面全都是 $x$ 的因数，个数是根号级别的，暴力即可。

时间复杂度 $O(n \sqrt{n} \log n)$，虽然很高但是时限 $4$ s，过得去 $10^5$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair <int , int>
int cnt[1000005];
vector <int> e[1000005];
int a[1000005];
int n , k;
inline void solve(){
    cin>>n>>k;
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    for(int i = 1;i <= n;i++){
        e[a[i]].clear();
    }
    for(int i = 1;i <= n;i++){
        e[a[i]].push_back(i);
        cnt[a[i]]++;
    }
    int ct = 0 , r = INT_MAX;
    set <int> now;
    for(int i = 1;i <= n+1;i++){
        // for(auto v:now)cerr<<v<<' ';
        // cerr<<'\n';
        if((*(now.lower_bound(k))) == k){
            now.clear();
            ct++;
            i--;
        }
        if(i>n)continue;
        if(a[i] == 1 || k % a[i]) continue;
        if(now.empty()){
        now.insert(a[i]);
        continue;
        }
        vector <int> dw;
        for(auto x:now){
            if(x>k)continue;
            x*=a[i];
            if(x<=k)dw.push_back(x);
            // now.erase(now.lower_bound(x));
        }
        for(auto v:dw) now.insert(v);
        now.insert(a[i]);
    }
    cout<<ct+1<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
           cout.tie(0);
    int T;
    cin>>T;
    while(T--)solve();
}
```

---

## 作者：abensyl (赞：0)

原题：[CF1992F Valuable Cards](https://www.luogu.com.cn/problem/CF1992F)。

好题，不难，但是硬耗我两小时。

## 思路

考虑贪心，可行性显然。

如果能够拼接在上一个区间上并且不存在乘积为 $x$ 的子序列，那就拼接在上一个区间上，否则就新开一个区间。

显然，如果某些数相乘有可能等于 $x$，那么这些数一定都是 $x$ 的因数，所以对于不是 $x$ 的因数的那些数字，不需要进行考虑。

对于 $a_i$（$a_i$ 是 $x$ 的因数），考虑是否可以接入上一个区间，只需要考虑上一个区间是否可以乘出 $x\over a_i$ 即可，显然 $x\over a_i$ 也是 $x$ 的因数，这里可以开 set 维护能够乘出的数。

由于所有 $\leq 10^5$ 的数字的因数个数最多有 $128$ 个，所以最多计算次数为 $128\times n$。

[代码 + 我的 AC 记录](https://codeforces.com/contest/1992/submission/281934380)。

---

## 作者：SnapYust (赞：0)

### 更好的阅读感受

[这里](https://www.cnblogs.com/snapyust/p/18300198)

### 题目传送门

[Valuable Cards](https://www.luogu.com.cn/problem/CF1992F)

### 思路

很直接的**贪心**（吧）。因为块数要越少越好，所以每一块中的元素应当越多越好。

我们先将 $x$ 分解因数，以便快速查询。接下来枚举每一个块，枚举 $x$ 的因数，如果当前枚举的 $a_j$ 是 $x$ 因数的因数，那么查询一下当前这一块中是否有另外一个整数与 $a_j$ 相乘等于 $x$ 的因数，如果有，那就将这个 $x$ 的因数存入查询中，最后再将 $a_j$ 自身存入查询。

每一次枚举过后都要考虑查询中有没有 $x$，如果有的话，那么就重新开始枚举下一块，`ans++`。

我们定义一个 `unordered_map` 来完成上述操作。由于 `unordered_map` 的平均复杂度为 $O(1)$，所以总时间复杂度应该是 $O(\sum{n\sqrt{x}})$。

### 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,a[100001];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;
    while(t--){
        int ans=0,cnt=0;int num[1001];
        cin>>n>>x;for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=x;i++)if(x%i==0)num[++cnt]=i;
        for(int i=1;i<=n;i++){
            ans++;unordered_map<int,bool>p;
            for(int j=i;j<=n;j++){
            	vector<int>v;
                for(int k=1;k<=cnt;k++){
                    if(num[k]%a[j]==0&&p.count(num[k]/a[j]))
                        v.push_back(num[k]);
                }
                for(int i=0;i<v.size();i++)p.emplace(v[i],0);
				p.emplace(a[j],0);
                if(p.count(x)){i=j-1;break;}
                else if(j==n){i=j;break;}
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

