# Lost Permutation

## 题目描述

A sequence of $ n $ numbers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once. For example, the sequences \[ $ 3, 1, 4, 2 $ \], \[ $ 1 $ \] and \[ $ 2,1 $ \] are permutations, but \[ $ 1,2,1 $ \], \[ $ 0,1 $ \] and \[ $ 1,3,4 $ \] — are not.

Polycarp lost his favorite permutation and found only some of its elements — the numbers $ b_1, b_2, \dots b_m $ . He is sure that the sum of the lost elements equals $ s $ .

Determine whether one or more numbers can be appended to the given sequence $ b_1, b_2, \dots b_m $ such that the sum of the added numbers equals $ s $ , and the resulting new array is a permutation?

## 说明/提示

In the test case of the example, $ m=3, s=13, b=[3,1,4] $ . You can append to $ b $ the numbers $ 6,2,5 $ , the sum of which is $ 6+2+5=13 $ . Note that the final array will become $ [3,1,4,6,2,5] $ , which is a permutation.

In the second test case of the example, $ m=1, s=1, b=[1] $ . You cannot append one or more numbers to $ [1] $ such that their sum equals $ 1 $ and the result is a permutation.

In the third test case of the example, $ m=3, s=3, b=[1,4,2] $ . You can append the number $ 3 $ to $ b $ . Note that the resulting array will be $ [1,4,2,3] $ , which is a permutation.

## 样例 #1

### 输入

```
5
3 13
3 1 4
1 1
1
3 3
1 4 2
2 1
4 3
5 6
1 2 3 4 5```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：zajasi (赞：4)

### 题意

给你一个数组 $b$，问能不能生成一个排列 $a$，使得：

1.	$b$ 中所有数都在 $a$ 中出现。	 

1.	$a$ 中所有数的和为 $s$。

问有没有这样的排列 $a$。

### 解法

首先，$b$ 中最大的数必须在 $a$ 中出现，也就是这个排列最小的总和就是 $\sum\limits^{b_k}_{i=1}i$，其中 $b_k$ 是 $b$ 排列中最大的数。

然后，我们根据 $s$ 的值适当将 $a$ 的长度加减，看看总和能不能到 $s$ 就行。

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,m;
int x;
int s,ma;
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m;
		s=ma=0;
		for(int i=1;i<=n;i++){
			cin>>x;
			s+=x;
			ma=max(ma,x);
		}
		int z=(ma+1)*ma/2;
		int zz=z-s;
		if(zz>m){
			cout<<"NO\n";
			continue;
		}
		int f=0;
		int c=ma;
		while(zz<=m){
			if(zz==m){
				f=1;
				cout<<"YES\n";
				break;
			}
			zz+=++c;
		}
		if(f==0)cout<<"NO\n";
	}
	return 0;
}

```


---

## 作者：sw2022 (赞：1)

## 题意简析

给定一个序列 $b\ (|b|=m,m>0)$ 和一个数 $s$，问能否在序列中加入任意数量的元素，使得序列变成一个排列且加入的元素和为 $s$。从 $1$ 开始枚举序列缺少的元素并把他加入序列，当加入的元素和大于等于 $s$ 时判断序列是否是排列即可。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
bool f[101];
int main()
{
	int t,m,mx,s,c,b,i;
	cin>>t;
	while(t--)
	{
		memset(f,false,sizeof(f));
		cin>>m>>s;mx=0,c=0;
		for(i=1;i<=m;i++)
		{
			cin>>b,f[b]=true;
			c++,mx=max(mx,b);
		}
		for(i=1;i<=100&&s>0;i++)
		if(!f[i]) f[i]=true,s-=i,c++;
		printf(s||c<mx?"NO\n":"YES\n");
	}
	return 0;
}
```

---

## 作者：justin_jiajia (赞：0)

一种奇妙的解法

# 题意

有一个数列是 $1 \sim n$ 的一种排列。丢掉了几个数，给出丢掉数的和留着的数，问它们是否能组成这个数列？

# 思路

我们~~都知道~~，求这样公差为 $1$ 的等差数列的和公式是
$$\dfrac{n(n+1)}{2}$$

而根据输入的数据我们可以把数列和求出来，$\times2$ 再平方根即可求出 $n$ ！

最后确保 $n \geq$ 留着的数中最大的数**并且**用 $n$ 套入上面的公式验证它等于输入的和。

# 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
void s() {
	int n, tot_lost;
	cin >> n >> tot_lost;
	int maxx = -1;
	int tot_found = 0;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		tot_found += x;
		maxx = max(maxx, x);
	}
	int tot = tot_found + tot_lost;
	int f = sqrt(double(tot * 2));
	int e = f * (f + 1) / 2;
	if (e == tot && f >= maxx) cout << "YES" << endl;
	else cout << "NO" << endl;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	while (n--) {
		s();
	}
	return 0;
}
```

---

## 作者：隐仞Mrsu (赞：0)

# 题意
给 $m$ 个不同的正整数，询问能否补充若干个正整数，使所有数构成一个排列。其中，补充的数之和要等于给定的 $s$。

# 分析
一个 $n$ 长的排列，需满足数字从 $1$ 到 $n$，每个数出现次数正好为 $1$。

令 $mx$ 为给定的 $m$ 个数的最大值，那么从 $1$ 到 $mx$ 中，没出现的数字都要补充。记录缺少了的数的总和 $sum$。

从 $1$ 记录到 $mx$ 后进行判断：
- 若 $sum>s$，说明 $s$ 太小，不足以构成排列，答案为否；
- 若 $sum=s$，说明此时正好可以用总和为 $s$ 的数据构成排列了，答案为正确；
- 若 $sum<s$，说明此时的 $s$ 还没用完，还需要继续判断。

继续判断时，让 $sum$ 逐个加上数据，从 $mx+1$ 开始累加。每次加完后，用上述方法进行判断。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int N = 1e6+5;
LL _,n,s,sr;
bool b[N];
void work(){
	for(LL i=1;i<=100;i++)b[i]=0;//清空数组
	cin>>n>>s;
	LL mx=0;
	for(LL i=1;i<=n;i++){
		cin>>sr;
		b[sr]=1;
		mx=max(mx,sr);
	}
	LL sum=0;
	for(LL i=1;i<=mx;i++){
		if(!b[i])sum+=i;
	}
	if(sum==s){
		cout<<"YES\n";
		return;
	}
	if(sum>s){
		cout<<"NO\n";
		return;
	}
	for(LL i=mx+1;i<=100;i++){
		if(!b[i])sum+=i;
		if(sum==s){
			cout<<"YES\n";
			return;
		}
		if(sum>s){
			cout<<"NO\n";
			return;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>_;
	while(_--){
		work();
	}
} 
```


---

## 作者：CLCK (赞：0)

~~翻译者水一发~~

先说思路：

既然要求的是从 $1$ 到 $n$ 的合法的排列，那么必定有 $1$ 到 $n$ 的所有数字构成，因此在输入时对数字进行标记，先从 $1$ 补全到 $\max\{b_1, ..., b_m\}$，若此时已经超过 $sum$ 则为 `false`; 而如果此时还没有用完，则从 $max + 1$ 开始依次补足，看是否能使得补全数字的和正好等于 $sum$，若超过则 `false`；反之则为 `true`。

上代码！

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int t;
bool flag;
int m, s, mx;
bool vis[5005];
bool check() {
    for (int i = 1; i <= mx; i++) { // 判断有没有补全
        if (!vis[i]) return false;
    }
    return true;
}
void work() {
    int cnt = 0, sum = 0;
    for (int i = 1; ; i++) {
        if (!vis[i]) {
            cnt++; sum += i;
            vis[i] = 1;
        }
        if (sum == s && check()) { // 是否合法 && 是否可行？
            flag = true;
            return ;
        }
        if (sum > s) return ; // 超过则直接 false
    }
}
int main() {
    cin >> t;
    while (t--) {
        cin >> m >> s;
        memset(vis, 0, sizeof(vis));
        flag = 0; mx = 0;
        for (int i = 1; i <= m; i++) {
            int tmp; cin >> tmp;
            mx = max(mx, tmp); // 记最大数
            vis[tmp] = true; // 标记
        }
        work();
        if (flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
```

完结撒花~

---

## 作者：BlackPanda (赞：0)

**[Problem](https://www.luogu.com.cn/problem/CF1759B)**

------------
### 题意：

有 $t$ 次输入，每次两个数 $m$，$s$ 和一个长度为 $m$ 的数组 $b$。

求出 $b$ 数组加上若干个数是否可以构造出形如 $1 \sim n$ 的数组 $a$，且补充的数字总和为 $s$，可以输出 $\verb!YES!$，否则输出 $\verb!NO!$。

------------
### 思路：

建议评橙。

首先 $b$ 数组中的最大值一定会在 $a$ 中出现，所以 $a$ 数组的最小总和为从 $1$ 到 $\max\{b_i\}$ 的和。

如果总和小于 $s$，就从 $\max\{b_i\} + 1$ 按顺序继续往后枚举累加，看看剩下的 $s$ 是否正好等于枚举到的数即可。

------------
### 赛时 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
int m, s;
int b[105];
bool vis[105] = {0};

void solve()
{
    memset(vis, 0, sizeof(vis));
    int maxx = -1005;
    cin >> m >> s;
    for (int i = 1; i <= m; i ++ )
    {
        cin >> b[i];
        maxx = max(maxx, b[i]);
        vis[b[i]] = 1;
    }

    for (int i = 1; i <= maxx; i ++ )
    {
        if (s < 0)
        {
            cout << "NO\n";
            return ;
        }
        if (!vis[i])
            s -= i;
    }
    if (s == 0)
    {
        cout << "YES\n";
        return ;
    }
    for (int i = maxx + 1; i; i ++ )
    {
        if (s < 0) 
        {
            cout << "NO\n";
            return ;
        }
        if (s == 0)
        {
            cout << "YES\n";
            return ;
        }
        s -= i;
    }
}

int main()
{
    cin >> t;
    while (t -- )
    {
        solve();
    }
    return 0;
}

```

---

## 作者：Engulf (赞：0)

找到已知的数的最大值 $x$，为了使序列是一个排列，$1 \sim x$ 的数都必须先选上。

计算出 $1 \sim x$ 中没出现过的数的和 $t$，如果 $t < s$（$s$ 是题目条件，未知的数的和）就从 $x + 1$ 开始往上加数（还是得满足是个排列）。

最后判断一下加上的数的和是不是 $s$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int m, s;
int a[N];
bool st[N];

int main()
{
	int tt;
	cin >> tt;
	while (tt -- )
	{
		memset(st, 0, sizeof st);
		cin >> m >> s;
		int mx = 0;
		for (int i = 1; i <= m; i ++ ) cin >> a[i], st[a[i]] = 1, mx = max(mx, a[i]);
		int sum = 0;
		for (int i = 1; i <= mx; i ++ ) if (!st[i]) sum += i;
		for (int i = mx + 1; sum < s; i ++ ) sum += i;
		puts(sum == s ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：Cczzyy20150005 (赞：0)

## 思路
模拟题。

每次输入时就标记一下这个数有了，然后再从 $1$ 向后找，如果已经有了，就跳过，没有就加到 $sum$ 里。

如果 $sum \ge s$ 了，就直接跳出循环，判断 $sum$ 是否等于 $s$，如果是的话就在遍历一遍 $1$ 到最大的数之间是不是都有了，否则就输出 `NO`。

### 一些细节
因为 $s \le 1000$，所以直接开数组标记就行了（~~但我很懒~~，用的 `map`）。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,s;
map<int,bool> mp;
void solve(){
	int maxn=0;
	mp.clear();
	cin>>m>>s;
	for(int i=1,x;i<=m;i++){
		cin>>x;
		mp[x]=1;//标记
		maxn=max(maxn,x);//保存最大
	}
	int sum=0,now=1;
	while(sum<s){
		if(mp[now]!=1)sum+=now,mp[now]=1;//如果没有就加入sum，记得也要标记
		maxn=max(maxn,now);//保存最大
		now++;
	}
	for(int i=1;i<=maxn;i++){
		if(mp[i]!=1){//如果1到maxn之间的数没有标记完说明不行
			puts("NO");
			return;
		}
	}
	sum==s?puts("YES"):puts("NO");
}
int main(){
	int t;cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Lyu_echo (赞：0)

### 题目大意
定义排列组合为由 $n$ 个数字组成的序列恰好包含一次从 $1$ 到 $n$ 的所有整数。

给定 $n$ 个整数的序列 $a_1,a_2,a_3,\ldots,a_n$ 和一个整数 $m$, 判断是否可以在给定序列 $a$ 上添加一个或多个整数, 使得添加的数字之和为 $m$, 并且使新的序列是一个排列组合。

### 解题思路
记录每一个 $a_i$, 计算所有的 $i$, $i\in [1,n]$, $i\notin a$ 之和, 记为 $\text{sum}$。

若 $\text{sum}$ 等于 $m$, 存在。

若 $\text{sum}$ 小于 $m$, 计算 $(n+1)+(n+2)+(n+3)+\ldots+(n+k)$, $1\le k$ 是否等于 $m-\text{sum}$。 如果是, 则存在; 反之, 不存在。 

若 $\text{sum}$ 大于 $m$, 不存在。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int t[100]={0};
	int n,m,mmax=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		mmax=max(a,mmax);
		t[a]++;
		if(t[a]>1){ //如果有重复出现
			cout<<"NO"<<endl; //则必定不符合要求
			return;
		}
	}
	for(int i=1;i<=mmax;i++){
		if(t[i]==0) m-=i;
	}
	if(m==0){ //情况1,sum==m
		cout<<"YES"<<endl;
		return;
	}
	if(m<0){  //情况3,sum>m
		cout<<"NO"<<endl;
		return;
	}
	if(m>0){  //情况2,sum<m
		for(int i=mmax+1;i;i++){
			m-=i;
			if(m<0){
				cout<<"NO"<<endl;
				return;
			}
			if(m==0){
				cout<<"YES"<<endl;
				return;
			}
		}
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
 
	int t;
	cin>>t;
	while(t--) solve();
 
	return 0;
}
```

---

