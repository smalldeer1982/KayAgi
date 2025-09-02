# Inaccurate Subsequence Search

## 题目描述

Maxim 有一个长度为 $n$ 的整数数组 $a$ 和一个长度为 $m$ 的整数数组 $b$（$m \le n$）。

Maxim 认为长度为 $m$ 的数组 $c$ 是好的，如果数组 $c$ 的元素可以重新排列，使得其中至少有 $k$ 个元素与数组 $b$ 的元素相同。

例如，如果 $b = [1, 2, 3, 4]$ 且 $k = 3$，那么数组 $[4, 1, 2, 3]$ 和 $[2, 3, 4, 5]$ 是好的（它们可以分别重排为 $[1, 2, 3, 4]$ 和 $[5, 2, 3, 4]$），而数组 $[3, 4, 5, 6]$ 和 $[3, 4, 3, 4]$ 不是好的。

Maxim 想要选择数组 $a$ 的每一个长度为 $m$ 的连续子段作为数组 $c$ 的元素。请帮助 Maxim 统计有多少个被选中的数组是好的。

换句话说，求有多少个位置 $1 \le l \le n - m + 1$，使得 $a_l, a_{l+1}, \dots, a_{l + m - 1}$ 组成的数组是好的数组。

## 说明/提示

在第一个样例中，所有子段都是好的。

在第二个样例中，好的子段起始于位置 $1$、$2$ 和 $3$。

在第三个样例中，好的子段起始于位置 $1$ 和 $2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
7 4 2
4 1 2 3 4 5 6
1 2 3 4
7 4 3
4 1 2 3 4 5 6
1 2 3 4
7 4 4
4 1 2 3 4 5 6
1 2 3 4
11 5 3
9 9 2 2 10 9 7 6 3 6 3
6 9 7 8 10
4 1 1
4 1 5 6
6```

### 输出

```
4
3
2
4
1```

# 题解

## 作者：YZMX (赞：7)

## 题目描述

给定长度为 $n$ 的数组 $a$ 和长度为 $m$ 的数组 $b$。找出数组 $a$ 中长度为 $m$ 的连续子区间，并且区间中有至少 $k$ 个数与数组 $b$ 相同，求满足条件区间数量。

## 题目分析

考虑相邻两个区间的关系，如下图：

![image5dbbca0383feb6fc.png](https://www.z4请更换图床a.net/images/2024/04/11/image5dbbca0383feb6fc.png)

可以观察到，对于当前区间与上一个区间相比，区间内的数只去掉了上一个区间的区间头，加上了当前区间的区间末尾。所以可以枚举每个长度为 $m$ 的区间，然后以 $O(1)$ 转移，即可求出答案。

一个问题：假设区间内与 $b$ 相同的数的数量为 $S$。当转移时，需要增加一个数，或是减少一个数。增加一个数时需要满足什么条件，才可以将 $S+1$ 呢？

因为是**与 $b$ 区间相同的个数**，所以说要记录一下 $b$ 数组第 $i$ 个数出现过的次数 $T_{b_i}$。为什么记录次数，因为当区间新加入的数在 $a$ 出现的次数还没到 $T_{b_i}$ 的时候，应当 $S+1$。同理可得，当减少的数出现次数小于 $T_{b_i}$ 的时候，才 $S-1$。

## 代码

```
#include<iostream>
#include<map>
#define int long long
#define qwq ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define pii pair<int,int>
using namespace std;

int n,t,a[200005],m,k,b[200005],sum,ans;


signed main(){
    cin>>t;
    while(t--){
        cin>>n>>m>>k;
        ans=0;
        sum=0;
        map<int,int>mp,mp2;
        for(int i=0;i<=n;i++) a[i]=0;
        for(int i=0;i<=m;i++) b[i]=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=m;i++){
            cin>>b[i];
            mp[b[i]]++;//记录一下b数组每个数出现次数
        }
        for(int i=1;i<=m;i++){//先处理a第一个区间与b数组相同的个数
            //当且仅当a[i]在b出现且数量小于它在b数组出现次数的时候将个数加1
            if(mp[a[i]]!=0&&mp2[a[i]]<mp[a[i]]){
                sum++;
            }
            mp2[a[i]]++;
        }
        for(int i=1;i<=n-m+1;i++){
            if(sum>=k) ans++;
            //处理将区间头移除时操作
            if(mp[a[i]]!=0&&mp2[a[i]]<=mp[a[i]]) sum--;
            mp2[a[i]]--;
            //处理将区间尾加入时操作
            if(mp[a[i+m]]!=0&&mp2[a[i+m]]<mp[a[i+m]]) sum++;
            mp2[a[i+m]]++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：xiaozhangawa (赞：1)

## 思路

先考虑对每一个 $1\leq i\leq n-m+1$ 计算 $i\sim i+m-1$ 是否是好的，时间复杂度 $\Theta(nm)$。

考虑优化。注意到在暴力思路中存在许多重复计算的情况（如 $1\sim m$ 和 $2\sim m+1$ 都计算了 $2\sim m$），所以我们可以参考**滑动窗口**的做法，将重复的统计记录下来。

我们可以用 `map<int,int> ma` 来记录 $a$ 数组**的选段**，用 `map<int,int> mb` 来记录 $b$ 数组的数字出现情况。

那么我们就先处理 $a$ 数组 $1\sim m$ 段的情况，然后枚举 $m<i\leq n$ 逐个统计贡献。

现在需要知道的是如何统计贡献。先看 $1\sim m$ 的情况，先把 $a$ 数组 $1\sim m$ 段的数字塞到 $ma$ 里去，把 $b$ 数组塞到 $mb$ 里去。然后枚举 $ma$ 里的元素，并取出 $mb$ 里键相同的元素。注意到对于任意一个正整数 $i$，都有贡献为 $\min(ma_i,mb_i)$。

接下来是另外的情况，这时我们应该处理贡献的增减。首先，会去掉 $a_{i-m}$ 的一个元素，我们首先 $ma_{a_{i-m}}\gets ma_{a_{i-m}}-1$，此时可能会发生贡献的减少，那么我们来分析一下：如果 $ma_{a_{i-m}}<mb_{a_{i-m}}$，说明 $a_{i-m}$ 产生了贡献，那么此时应该将贡献减一；反之，则 $a_{i-m}$ 没有产生贡献，那么此时贡献不变。接下来会加入一个元素 $a_i$，那么如果此时 $ma_{a_i}<mb_{a_i}$，说明此时 $a_i$ 会产生贡献，贡献应该加一；反之，则 $a_i$ 没有产生贡献，贡献不变。最后，更新计数器 $ma_{a_i}\gets ma_{a_i}+1$。

对于每个区间，做一个判断，如果贡献 $\geq k$，则将答案加一。最终时间复杂度 $\Theta(n\log n+m)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[200010],b[200010];
void solve(){
	map<int,int> ma,mb;// 计数器
	int n,m,k,kk=0,ans=0;// kk 为贡献，ans 为答案
	cin>>n>>m>>k;
	for(int i = 1;i <= n;i++){
		cin>>a[i];
		if(i<=m) ma[a[i]]++;// 注意这里 i<=m 的判断
	}
	for(int i = 1;i <= m;i++){
		cin>>b[i];
		mb[b[i]]++;
	}
	for(auto i:ma){// 用 range-for 枚举 ma 中的元素
		// 这里 i 是一个 pair，它的 first 存键，second 存值
		kk += min(i.second,mb[i.first]);
	}
	if(kk >= k) ans++;// 统计答案
	for(int i = m+1;i <= n;i++){
		// 对贡献做增减
		ma[a[i-m]]--;
		if(ma[a[i-m]]<mb[a[i-m]]) kk--;
		if(ma[a[i]]<mb[a[i]]) kk++;
		ma[a[i]]++;
		if(kk >= k) ans++;
	}
	cout<<ans<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/1955/304355168)。

---

## 作者：114514xxx (赞：0)

## 思路
由于固定了 $m$ 个数的区间，我们很容易可以想到滑动窗口，且每次只有第一个数和最后一个数发生改变，因此我们可以用桶进行维护。

那么如何利用桶维护进行维护呢？我们可以发现因为只有第一个数和最后一个数发生改变，便可以借此进行转移，进一步用来判断当前是否匹配。

具体细节见代码。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+25;
const int inf=2e9;
int a[N],q[N],n,m,k,b[N];
map<int,int>mp;
map<int,int>mp1;
map<int,int>vis;
inline void solve(){
    mp.clear();
    mp1.clear();
    vis.clear();
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)cin>>a[i],mp[a[i]]++;
    for(int i=1;i<=m;i++)cin>>b[i],mp1[b[i]]++;
    int cnt=0,ans=0;
    for(int i=1;i<=m;i++)
        if(mp1[a[i]]&&!vis[a[i]])cnt+=min(mp[a[i]],mp1[a[i]]),vis[a[i]]=1;
    ans+=(cnt>=k);
    for(int i=2;i<=n-m+1;i++){
        int p1=a[i-1],p2=a[i+m-1];
        if(mp1[p1]){
            cnt-=min(mp1[p1],mp[p1]);
            mp[p1]--;
            cnt+=min(mp1[p1],mp[p1]);
        }
        if(mp1[p2]){
            cnt-=min(mp1[p2],mp[p2]);
            mp[p2]++;
            cnt+=min(mp1[p2],mp[p2]);
        }//进行转移
        ans+=(cnt>=k);//判断是否合法
    }
    cout<<ans<<'\n';
}
int t;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--)solve();
}
```

---

## 作者：yaaaaaan (赞：0)

## 思路
这道题可以先用两个数据结构来记录每个数字在两个数组分别出现的次数。

因为区间的长度是固定的，我们可以采用滑动窗口的思想，依次去滑动区间。可以用一个变量 $cnt$ 表示当前区间和数组 $b$ 匹配的元素个数。根据区间滑动，判断两端端点情况，不断更新 $cnt$。如果 $k\le cnt$，则更新最后答案。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optmize(3)
using namespace std;
int n,m,k,t;
int a[200010];
int b[200010];
map<int,int> aa,bb;
signed main() 
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--) 
	{
		cin>>n>>m>>k;
		aa.clear();
		bb.clear();
		int cnt=0;
		int ans=0;
		for(int i=1;i<=n;i++) 
		{
			cin>>a[i];
			if(i<=m)aa[a[i]]++;
		}
		for(int i=1;i<=m;i++)
		{
			cin>>b[i];	
			bb[b[i]]++;;
		}
		for(auto it:bb) 
		{
			cnt+=min(aa[it.first],it.second);
		}
		if(cnt>=k) ans++;
		for(int i=m+1;i<=n;i++) 
		{
			if(aa[a[i-m]]<=bb[a[i-m]]) 
			{
				cnt--;
			}
			aa[a[i-m]]--;
			if(aa[a[i]]<bb[a[i]]) 
			{
				cnt++;
			}
			aa[a[i]]++;
			if(cnt>=k) ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
/*
*/
```

---

## 作者：Lujoqera (赞：0)

### 思路：
- 首先,可以发现这个 $m$ 的长度是固定了的，所以很容易想到**滑动窗口**的做法。
- 你去统计最开始的 $m$ 个相同的个数，然后从 $m+1$ 开始枚举每次会把 $a_{i}$ 加上，那如果当前这个区域 $a_{i}$ 的个数比 $b$ 数组少的话，则相同个数会多一个，否则不会影响。也会把 $a_{i-m}$ 减掉，同理，如果当前这个区域 $a_{i}$ 的个数比 $b$ 数组多的话，则不会影响，否则相同个数会少一个。
- 每次枚举时统计相同个数即 $cnt \ge k$ 时，那么 $ans+1$ 即可。

### 代码
```
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
typedef long long LL;
using namespace std;
 
int n,m,k;
int a[200010];
int b[200010];
map<int,int> cnt1;
map<int,int> cnt2;
 
signed main() 
{
	int t;
	cin>>t;
	while(t--) 
	{
		int n,m,k;
		cin>>n>>m>>k;
		cnt1.clear();
		cnt2.clear();
		for(int i=1;i<=n;i++) 
		{
			cin>>a[i];
		}
		for(int i=1;i<=m;i++)
		{
			cin>>b[i];
		}
		int cnt=0;
		int ans=0;
		for(int i=1;i<=m;i++) 
		{
			cnt1[a[i]]++;
		}
		for(int i=1;i<=m;i++) 
		{
			cnt2[b[i]]++;
		}
	    for(auto i:cnt2) 
		{
			cnt+=min(cnt1[i.first],i.second);
		}
		if(cnt>=k) ans++;
		for(int i=m+1;i<=n;i++) 
		{
			if(cnt1[a[i-m]]<=cnt2[a[i-m]]) 
			{
				cnt--;
			}
			cnt1[a[i-m]]--;
			if(cnt1[a[i]]<cnt2[a[i]]) 
			{
				cnt++;
			}
			cnt1[a[i]]++;
			if(cnt>=k) ans ++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
/*
*/
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 我们发现，其实 $m$ 的**长度是固定死了的**，所以我们考虑用**滑动窗口**。
- 由于这道题目是让你统计匹配的数量，因此引导了我们用两个数组 $cnt$ 和 $b$ 分别统计 $a$ 数组和 $b$ 数组中每一个数出现了多少次。
- 对于**每次进队的元素** $x$，如果 $cnt_{x} \le b_{x}$ 的话，就相当于**匹配的数量增加**了，定义 $ans$ 是指**当前窗口**中和 $b$ 数组**匹配的个数**，那么此刻 $ans+1$。
- 我的做法是一遍扫完 $a$ 数组，那么当 $i \ge m$ 时，我们就要把 $cnt_{a_{i-m}}-1$，保证**窗口的大小**是等于 $k$。当如果去掉了 $a_{i-m}$ 这个元素，导致了 $cnt_{a_{i-m}}\le b_{a_{i-m}}$，**匹配数量就要减小**，即 $ans-1$。
- 定义 $cn$ 是**最后的答案**。每次循环后，如果 $ans\ge k$ 并且 $i\ge m$，那么 $cn+1$。

### 代码：
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,k;
int a[200001];
int cnt[1000001];
map<int,int>b;
void solve(){
	b.clear();
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		b[x]++;
	}
	int ans=0;
	int cn=0;
	for(int i=1;i<=n;i++){
		cnt[a[i]]++;
		if(cnt[a[i]]<=b[a[i]])ans++;
		if(i>m){
			cnt[a[i-m]]--;
			if(cnt[a[i-m]]<b[a[i-m]])ans--;
		}
		if(ans>=k&&i>=m)cn++;
		//if(i>=m){
			//cout<<i<<" "<<ans<<endl;
		//}
	}
	for(int i=1;i<=n;i++){
		cnt[a[i]]=0;
	}
	cout<<cn<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tt;
	cin>>tt;
	while(tt--)solve();
	return 0;
}
 		  		      		 	 					    				
```

---

## 作者：MA_tian (赞：0)

# 题目大意
有一个有 $ n $ 个数的数组 $ a $，要求你在 $ a $ 数组中寻找长度与 $ b $ 数组长度相等的区间，和数组 $ b $ 中至少有 $ k $ 个数与 $ b $ 数组中的数相同，有 $ T $ 组数据。
# 题目解法
建议先看看[这题](https://www.luogu.com.cn/problem/P1886)。

这题第一眼想到的肯定是滑动窗口，做法不难。每两次求值变动的只有第一个位置和最后一个位置，前删后加。

滑动窗口中，运用到了桶的思想。

本题中只有两种情况：

情况一：加入数后影响结果，答案增加，桶的对应项也增加。

情况二：加入数后影响结果，答案减少，桶的对应项也减少。

如何判断会不会影响结果？

我们需要创立另一个桶，用于记录 $ b $ 数组的数，在运算过程中进行对比，即可完成这题。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005],use1[1000005],use2[1000005],sum,ans,l,r;
void js1(const int&v){
	use1[a[v]]++;
	if(use1[a[v]]<=use2[a[v]]){
		sum++;	
	}
}
void js2(const int&v){
	if(use1[a[v]]<=use2[a[v]]){
		sum--;
	}
	use1[a[v]]--;
}
int main(){
	int T,n,m,k;
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		sum=0;
		ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=m;i++){
			cin>>b[i];
			use2[b[i]]++;
		}
		for(l=1,r=0;r<m;){
			r++;
			js1(r);
		}
		while(r<=n){
			if(sum>=k){
				ans++;
			}
			js2(l);
			l++;
			r++;
			js1(r);
		} 
		cout<<ans<<endl;
		for(int i=1;i<=m;i++){
			use2[b[i]]--;
		}
		while(l<=r){
			js2(l);
			l++;
		}
	}
	return 0;
}
```

---

## 作者：lovely_qiqi (赞：0)

## 思路

第一眼思路：枚举每个区间，暴力统计，时间复杂度 $O(nm)$ 左右。

但是数据范围直接告诉我们这是一个 $O(n)$ 的算法。

于是不难用**滑动窗口**的思想看出当前区间 $[l,r]$ 一定是由上一个区间 $[l-1,r-1]$ 减去 $l$ 号元素再加上 $r$ 号元素得到。于是先处理第一个区间，然后按题意模拟即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
int t,n,m,k,cnt,ans,add,a[200010],b[200010];
map<int,int> bc,ac;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(int tt=1;tt<=t;tt++){
		cin>>n>>m>>k;
		cnt=0,ans=0;
		bc.clear();
		ac.clear();
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) cin>>b[i];
		for(int i=1;i<=m;i++) bc[b[i]]++;
		for(int i=1;i<=m;i++) ac[a[i]]++;
		for(auto it:bc){
			ans=ans+min(ac[it.first],bc[it.first]);
		}
		if(ans>=k) cnt++;
//		cout<<"1 "<<m<<" "<<ans<<endl;
		for(int i=2;i<=n-m+1;i++){
			
			add=i+m-1;
			if(ac[a[i-1]]<=bc[a[i-1]]) ans--;
			ac[a[i-1]]--;
			ac[a[add]]++;
			if(bc[a[add]]>=ac[a[add]]) ans++;
//			cout<<i<<" "<<add<<" "<<ans<<endl;
			if(ans>=k) cnt++;
		}
		cout<<cnt<<endl;
	}
	return 0;
}

```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

典型的“滑动窗口”。每两次求值时的不同的部分只有前一次的第一个位置，应当删去；以及后一次的最后一个位置，应当加入。

这时候，我们可以用桶来解决这个问题。约定 $t$ 为滑动区间的桶，$tb$ 为整个 $b$ 数组的桶。若干细节：

假设这次滑动要加入的数的下标为 $r$，要删去的为 $l$。那么 $t[a_r]$ 加一。如果此时的 $t[a_r]\le tb[a_r]$，那么可以接着匹配到一个新的，匹配数加一。如果此时的 $t[a_l]\le tb[a_l]$，那么有一个已匹配的数被删除，匹配数减一。再将 $t[a_l]$ 减一。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int tt, n, m, k, a[200005], b[200005], t[1000005], tb[1000005], ant, ans, lp, rp;
inline void inc(const int& v) {
	t[a[v]]++; ant += (t[a[v]] <= tb[a[v]]);
}
inline void dec(const int& v) {
	ant -= (t[a[v]] <= tb[a[v]]); t[a[v]]--;
}
int main() {
	ios::sync_with_stdio(0);
	cin >> tt;
	while (tt--) {
		cin >> n >> m >> k;
		ant = ans = 0;
		for (int i = 1; i <= n; ++i) cin >> a[i];
		for (int i = 1; i <= m; ++i) cin >> b[i], tb[b[i]]++;
		for (lp = 1, rp = 0; rp < m;) rp++, inc(rp);
		do {
			ans += ant >= k;
			dec(lp); lp++;
			rp++; inc(rp);
		} while (rp <= n);
		cout << ans << endl;
		for (int i = 1; i <= m; ++i) tb[b[i]]--;
		while (lp <= rp) dec(lp), lp++;
	}
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1955D)

## 思路

一道用到滑动窗口思想的题。

观察到 $1\le a_i,b_i\le 10^6$，可以想到我们用两个桶，统计 $b$ 数组和 $a$ 数组的窗口中的数字，计算相同的个数。

之后我们顺次滑动，每次滑动一位，然后统计这一位的差异并更改。每次判断当前窗口在 $b$ 数组内相同值的个数是否大于等于 $k$，如果是那么计数器 $+1$。

判断方法：

- 删除时，如果这个数字删过后的数量**不多于** $b$ 数组，那么计录相同值 $-1$（删后影响结果，使其变小）；否则不进行计算。

- 增加时，如果这个数字增加过后的数量**大于** $b$ 数组，那么不进行计算（加多了不会对结果造成影响）；否则计录相同值 $+1$。

这道题有多组测试数据，所以要**清空变量**。但是如果用数组来标记，设标记数组大小为 $L$，则 ``memset()`` 清空所用的总时间复杂度为 $\mathcal{O}(TL)$，会导致超时。我们可以选用 ``map`` 代替数组，用 ``clear()`` 清空可以降低时间复杂度至 $\mathcal{O}(Tn)$。

- 可选优化：把 ``map`` 替换为 ``unordered_map``。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
signed solution();
signed main(){solution();return 0;}
ll read(){//快读。
	ll k=0;bool flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag^=1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	if(flag)return k;return -k;
}
const int N=1e6+10;
int n,m,k,a[N],b[N];
unordered_map<int,int>tom,num,vis;
signed solution(){
	int T=read();
	while(T--){
		n=read(),m=read(),k=read();
		vis.clear();
		tom.clear();
		num.clear();
		for(int i=1;i<=n;++i)a[i]=read();
		for(int i=1;i<=m;++i){
			b[i]=read();
			++tom[a[i]];
			++num[b[i]];
		}
		int now=0,ans=0;
		for(int i=1;i<=m;++i){//因为要判断多出来的情况，所以增加一个 vis 标点。
			if(tom[a[i]]>num[a[i]]&&!vis[a[i]])now+=num[a[i]];
			else if(tom[a[i]]<=num[a[i]])++now;
			vis[a[i]]=1;
		}
		if(now>=k)++ans;//这是第一个窗口，统计。
		for(int i=m+1;i<=n;++i){
			--tom[a[i-m]];
			if(tom[a[i-m]]<num[a[i-m]])--now;//注意等号。
			++tom[a[i]];
			if(tom[a[i]]<=num[a[i]])++now;
			if(now>=k)++ans;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/155211385)

---

## 作者：yshpdyt (赞：0)

## 题意
求长为 $n$ 的序列 $a_i$，有多少个长为 $m$ 的区间，使得区间里的数经过**任意排列**后可以与另一个长为 $m$  的序列有至少 $k$ 个位置相同。
## Sol
动态维护以 $i$ 开头长为 $m$ 的区间。先将 $b_i$ 序列以桶的方式存下来，设为 $c$ 数组。

从左到右枚举区间，每次右移开头减去旧开头的贡献，加上新末尾的贡献。

具体来说就是开个桶 $cnt$，让 $cnt_{a_{i+m-1}}\rightarrow cnt_{a_{i+m-1}}+1$，$cnt_{a_{i-1}}\rightarrow cnt_{a_{i-1}}-1$。

然后对比 $c$ 桶，若 $cnt_{a_{i+m-1}} \le c_{a_{i+m-1}}$ ，$k \rightarrow k-1$，若 $cnt_{a_{i-1}} <c_{a_{i-1}}$，$k \rightarrow k+1$，若 $k\le 0$ ，说明该区间合法，合法区间增加，这样即维护相似数字的个数。 
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000005
#define endl "\n" 
#define fi fisrt
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
map<ll,ll> mp,cnt;
ll n,m,a[N],k,res,now; 
bool vis[N];
void sol(){
    res=0,now=0;
    cin>>n>>m>>k;
    mp.clear();
    cnt.clear();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        vis[i]=0;
    }
    for(int i=1;i<=m;i++){
        ll x;
        cin>>x;
        mp[x]++;
    }
    for(int i=1;i<=n;i++){
        cnt[a[i]]++;
        if(cnt[a[i]]<=mp[a[i]])now++;
        if(i<m)continue;
        if(now>=k)res++;
        cnt[a[i-m+1]]--;
        if(cnt[a[i-m+1]]<mp[a[i-m+1]])now--;
    }
    cout<<res<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();

    return 0;
}
```

---

