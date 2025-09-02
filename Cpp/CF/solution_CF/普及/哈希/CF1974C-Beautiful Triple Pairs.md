# Beautiful Triple Pairs

## 题目描述

Polycarp was given an array $ a $ of $ n $ integers. He really likes triples of numbers, so for each $ j $ ( $ 1 \le j \le n - 2 $ ) he wrote down a triple of elements $ [a_j, a_{j + 1}, a_{j + 2}] $ .

Polycarp considers a pair of triples $ b $ and $ c $ beautiful if they differ in exactly one position, that is, one of the following conditions is satisfied:

- $ b_1 \ne c_1 $ and $ b_2 = c_2 $ and $ b_3 = c_3 $ ;
- $ b_1 = c_1 $ and $ b_2 \ne c_2 $ and $ b_3 = c_3 $ ;
- $ b_1 = c_1 $ and $ b_2 = c_2 $ and $ b_3 \ne c_3 $ .

Find the number of beautiful pairs of triples among the written triples $ [a_j, a_{j + 1}, a_{j + 2}] $ .

## 说明/提示

In the first example, $ a = [3, 2, 2, 2, 3] $ , Polycarp will write the following triples:

1. $ [3, 2, 2] $ ;
2. $ [2, 2, 2] $ ;
3. $ [2, 2, 3] $ .

 The beautiful pairs are triple $ 1 $ with triple $ 2 $ and triple $ 2 $ with triple $ 3 $ .In the third example, $ a = [1, 2, 3, 2, 2, 3, 4, 2] $ , Polycarp will write the following triples:

1. $ [1, 2, 3] $ ;
2. $ [2, 3, 2] $ ;
3. $ [3, 2, 2] $ ;
4. $ [2, 2, 3] $ ;
5. $ [2, 3, 4] $ ;
6. $ [3, 4, 2] $ ;

 The beautiful pairs are triple $ 1 $ with triple $ 4 $ , triple $ 2 $ with triple $ 5 $ , and triple $ 3 $ with triple $ 6 $ .

## 样例 #1

### 输入

```
8
5
3 2 2 2 3
5
1 2 1 2 1
8
1 2 3 2 2 3 4 2
4
2 1 1 1
8
2 1 1 2 1 1 1 1
7
2 1 1 1 1 1 1
6
2 1 1 1 1 1
5
2 1 1 1 1```

### 输出

```
2
0
3
1
8
4
3
2```

# 题解

## 作者：Eddie08012025 (赞：13)

这题枚举显然是不行的，设三元组的三个数为 $a,b,c$，可以构成美丽三元组的情况有两个三元组 $a,b$ 相等，$a,c$ 相等，$b,c$ 相等。

所以我们可以考虑使用 $4$ 个 map 存储与三元组 $a,b,c$ 中 $a,b$ 相同，$a,c$ 相同，$b,c$ 相同，$a,b,c$ 都相同的三元组个数。

但是在 $a,b,c$ 都相同时会在 $4$ 个 map 中都存储一遍，但是这是不满足美丽三元组的要求的，所以应该减掉 $3$ 个$a,b,c$ 都相同的三元组数量。如果 $a,b$ 相同，$a,c$ 相同，$b,c$ 相同，$a,b,c$ 都相同的三元组个数分别是 $x,y,z,k$ 的话，美丽三元组的个数应该是 $x+y+z-3\times k$。

思路已经讲的比较清楚了吧，下面放出我的 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,z[200001],ans;
map<pair<int,int>,int>a,b,c,chu;//a,b,c分别存储a,c相同，b,c相同，a,b,c都相同的三元组个数，chu是为了方便初始化 
map<tuple<int,int,int>,int>d,chu1;//d存储a,b,c都相同的三元组个数，tuple和pair的区别是tuple存储3个元素 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		a=b=c=chu;
		d=chu1;
		for(int i=1;i<=n;i++){
			cin>>z[i];
		}//以上是输入与初始化
		for(int i=3;i<=n;i++){//a[i-2],a[i-1],a[i]这个三元组 
			ans+=a[make_pair(z[i-2],z[i-1])];//a,b相同的三元组个数 
			ans+=b[make_pair(z[i-2],z[i])];//a,c相同的三元组个数  
			ans+=c[make_pair(z[i-1],z[i])];//b,c相同的三元组个数 
			ans-=d[make_tuple(z[i-2],z[i-1],z[i])]*3;//ans要减去3*a,b,c都相同的三元组个数  
			//以上是统计答案 
			a[make_pair(z[i-2],z[i-1])]++;
			b[make_pair(z[i-2],z[i])]++;
			c[make_pair(z[i-1],z[i])]++;
			d[make_tuple(z[i-2],z[i-1],z[i])]++; 
		}cout<<ans<<"\n";
	}
	return 0;
}
```
**感谢观看！！！**

---

## 作者：ttq012 (赞：8)

直接暴力枚举两个三元组是显然不可行的，考虑维护答案。

因为造成贡献可以有三种情况：

+ 第一、二个位置相同，第三个位置不同。
+ 第一、三个位置相同，第二个位置不同。
+ 第二、三个位置相同，第一个位置不同。

因此考虑开四个桶分别维护第一、二个位置相同、第一、三个位置相同、第二、三个位置相同、三个位置全部相同的值。设四个值分别为 $A$，$B$，$C$，$D$，则根据容斥原理 $D$ 的值会在 $A$，$B$，$C$ 中分别算一次，但是 $D$ 本身是不符合答案的。因此答案为 $A+B+C-3\times D$。时间复杂度为 $O(n\log n)$。

```cpp
void $() {
    int n;
    cin >> n;
    F(i, 1, n) {
        cin >> a[i];
    }
    map<int, int> m1, m2, m3, m;
    int bas = 1000111, cnt = 0;
    F(i, 1, n - 2) {
        m1[a[i] * bas + a[i + 1]]++;
        m2[a[i] * bas + a[i + 2]]++;
        m3[a[i + 1] * bas + a[i + 2]]++;
        m[a[i] * bas * bas + a[i + 1] * bas + a[i + 2]]++;
        cnt += m1[a[i] * bas + a[i + 1]] - 1;
        cnt += m2[a[i] * bas + a[i + 2]] - 1;
        cnt += m3[a[i + 1] * bas + a[i + 2]] - 1;
        cnt -= 3 * (m[a[i] * bas * bas + a[i + 1] * bas + a[i + 2]] - 1);
    }
    cout << cnt << '\n';
}

signed main() { $(); }
```

---

## 作者：Louis_lxy (赞：3)

显然满足条件有几种情况，要么前两项都相同，要么后两项都相同，要么头和尾都相同。考虑哈希，我们开四个桶来存不同的数量，前三个存上述满足条件的三种情况，最后一种处理特殊情况，即两个三元组完全相同。令四个算出的哈希值分别是 $a1$，$a2$，$a3$，$a4$，四个桶分别编号 $t1$，$t2$，$t3$，$t4$。此时的答案为 $t1_{a1}+t2_{a2}+t3_{a3}-3\times t4_{a4}$。

AC 记录：https://www.luogu.com.cn/record/168596333

---

## 作者：Weekoder (赞：3)

### 思路

可以考虑用桶来维护四种情况：第一个不同，第二个不同，第三个不同，全部相等。为什么要维护全部相等的情况呢？我们在统计答案的时候，其实会算到三个值相等的不正确情况，而且三个桶会重复计算三次，所以可以维护全部相等的情况乘以 $3$ 并在答案中减去。

unordered_map 似乎可以做到近似 $\mathcal{O}(1)$，所以时间复杂度大约为 $\mathcal{O}(n)$。

这里有一个技巧：将三元组和二元组转换为 $133331$ 进制的数字，就可以做到压维。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 5;

int T, n, a[N];

unordered_map<int, int> mp1, mp2, mp3, mp4;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while (T --) {
	    cin >> n;
	    for (int i = 1; i <= n; i++)
	       cin >> a[i];
	    int ans = 0;
	    mp1.clear(), mp2.clear(), mp3.clear(), mp4.clear(); 
	    for (int i = 1; i <= n - 2; i++) {
            ans += mp1[a[i] * 133331 + a[i + 1]] + mp2[a[i] * 133331 + a[i + 2]] + mp3[a[i + 1] * 133331 + a[i + 2]] - 3 * mp4[a[i] * 133331 * 133331 + a[i + 1] * 133331 + a[i + 2]];
	        mp1[a[i] * 133331 + a[i + 1]]++;
            mp2[a[i] * 133331 + a[i + 2]]++;
            mp3[a[i + 1] * 133331 + a[i + 2]]++;
            mp4[a[i] * 133331 * 133331 + a[i + 1] * 133331 + a[i + 2]]++;
	    }
	    cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：DrAlfred (赞：3)

摘要：容斥，数据结构

[传送门：https://www.luogu.com.cn/problem/CF1974C](https://www.luogu.com.cn/problem/CF1974C)

## 题意

给定一个长度为 $n$ 的数列 $a$。考虑 $n - 2$ 个关于 $a$ 的三元对 $[a_j, a_{j + 1}, a_{j + 2}]$。我们定义两个三元对是美丽的，当且仅当他们只有一个位置不同。

求这 $n - 2$ 个三元对中，美丽的三元对数量。

## 分析思路

考虑容斥。先统计出**有**两个位置不同的对数 $x$。我们首先枚举这两个位置 $A, B$ $(0 \leq A \leq B \leq 2)$，考虑 $a_{j + A}, a_{j + B}$ 相同的对数，这可以用 `std::map` 辅助求出。

最后有一些**三个位置都相同**的对被重复统计了三次，记它们的数量为 $y$。同样的我们可以用 `std::map` 辅助求出。

最终答案即为 $x - 3y$，时间复杂度 $O\left(n \log n\right)$，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
using i64 = long long;
i64 t, n, ans, a[N];
inline void solve(void) {
    cin >> n, ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            map<pair<int, int>, int> cnt;
            for (int k = 1; k <= n - 2; k++) {
                ans += cnt[{a[k + i], a[k + j]}]++;
            }
        }
    }
    map<array<i64, 3>, int> cnt;
    for (int i = 1; i <= n - 2; i++) {
        ans -= 3 * cnt[{a[i], a[i + 1], a[i + 2]}]++;
    }
    cout << ans << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：ZhaoV1 (赞：2)

## 解析

这道题最重要的思想就是容斥原理（看其他题解才知道叫这个名字），如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2b6b8vea.png)

具体做法就是用多个桶，分别存第一位和第二位的值，第二位和第三位的值，第一位和第三位的值，第一位和第二位和第三位的值。遍历，将相同值个数多余 $1$ 的用组合数求出有多少相同的项，最后用图中公式得到答案。

AC Code
------------
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+5;
int t,n;
int temp[N];

int calculate(int n,int m){
	int ans = 1;
	for(int i=1;i<=m;i++){
		ans = ans*(n-m+i)/i;
	}
	return ans;
}

void solve(){ 
	int res = 0;
	cin >> n;
	map<pair<int,int>,int> mp1,mp2,mp3;
	map<pair<int,pair<int,int> >,int> mp4;
	//mp1->1,2  mp2->1,3  mp3->2,3 mp4->1,2,3
	for(int i=1;i<=n;i++){
		cin >> temp[i];
	}
	for(int i=1;i<=n-2;i++){
		mp1[{temp[i],temp[i+1]}]++;
		mp2[{temp[i],temp[i+2]}]++;
		mp3[{temp[i+1],temp[i+2]}]++;
		mp4[{temp[i],{temp[i+1],temp[i+2]}}]++;
	}
	for(auto it : mp1)//处理答案
		if(it.second > 1)
			res += calculate(it.second,2);
	for(auto it : mp2)
		if(it.second > 1)
			res += calculate(it.second,2);
	for(auto it : mp3)
		if(it.second > 1)
			res += calculate(it.second,2);
	for(auto it : mp4)
		if(it.second > 1)
			res -= 3*calculate(it.second,2);
	cout << res << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：2)

# CF1974C Beautiful Triple Pairs题解
明显容斥。

维护第 $1,2$ 位相同的、第 $1,3$ 位相同的、第 $2,3$ 位相同的、全部相同的，每一位的答案为：第 $1,2$ 位相同的 $+$ 第 $1,3$ 位相同的 $+$ 第 $2,3$ 位相同的 $-3\times$ 全部相同的。

用 ```STL``` 中的 ```map``` 与 ```pair``` 维护。

代码：

```cpp
#include <bits/stdc++.h>
#define mk make_pair
#define int long long
using namespace std ;
int t , n , a[200005] ;
map <pair <int , int> , int> x , y , z , c ;
map <pair <int , pair <int , int> > , int> m , cl ;
signed main()
{
	cin >> t ;
	while(t--)
	{
		x = y = z = c , m = cl ;
		cin >> n ;
		for(int i = 1 ; i <= n ; i++)	cin >> a[i] ;
		int ans = 0 ;
		for(int i = 2 ; i < n ; i++)
		{
			ans += x[mk(a[i - 1] , a[i])] ;
			x[mk(a[i - 1] , a[i])]++ ;
			ans += y[mk(a[i - 1] , a[i + 1])] ;
			y[mk(a[i - 1] , a[i + 1])]++ ;
			ans += z[mk(a[i] , a[i + 1])] ;
			z[mk(a[i] , a[i + 1])]++ ;
			ans -= 3 * m[mk(a[i - 1] , mk(a[i] , a[i + 1]))] ;
			m[mk(a[i - 1] , mk(a[i] , a[i + 1]))]++ ;
		}
		cout << ans << '\n' ;
	}
	return 0 ;
}
```

---

## 作者：JOE_ZengYuQiao_0928 (赞：2)

### [先看题](https://www.luogu.com.cn/problem/CF1974C)
## 题目大意：
给定一个数组，找到 $n-2$ 个三元对 $[a_i,a_{j + 1},a_{i + 2}]$，求两个三元对之间只有一个数不相同的方案数量。
## 思路：
可以考虑用 map 来维护四种情况：
- 第一个不同，第二个和第三个相同。
- 第二个不同，第一个和第三个相同。
- 第三个不同，第一个和第二个相同。
- 全部相同。

根据容斥原理，答案就是：第一个不同，第二个和第三个相同情况的个数加上第二个不同，第一个和第三个相同情况的个数，再加上第三个不同，第一个和第二个相同情况的个数减去全部相同情况的个数乘三。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,int> mp12;
map<int,int> mp13;
map<int,int> mp23;
map<int,int> mp123;
const int N=2e5+5;
int jin_zhi=1e6,ans,a[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		ans=0;
		mp12.clear();
		mp13.clear();
		mp23.clear();
		mp123.clear();
		int n;
	    cin>>n;
	    for(int i=1;i<=n;i++)cin>>a[i];
	    for(int i=3;i<=n;i++){
	        mp23[a[i]*jin_zhi+a[i-1]]++;
			mp13[a[i]*jin_zhi+a[i-2]]++;
			mp12[a[i-1]*jin_zhi+a[i-2]]++;
			mp123[a[i]*jin_zhi*jin_zhi+a[i-1]*jin_zhi+a[i-2]]++;
			ans+=mp12[a[i-1]*jin_zhi+a[i-2]]+mp13[a[i]*jin_zhi+a[i-2]]+mp23[a[i]*jin_zhi+a[i-1]]-3*(mp123[a[i]*jin_zhi*jin_zhi+a[i-1]*jin_zhi+a[i-2]]);
		}
		cout<<ans<<"\n";
	}
	return 0;
}

```

---

## 作者：albertting (赞：2)

前置知识：```map``` 和 ```pair```。

### 思路

考虑使用桶来维护三元组。

这里我们为你就需要召唤神圣的 ```STL```，它给了我们一种十分好用的数据结构 ```map```。

为了方便理解，我同时用 ```pair``` 作为 ```map``` 的下标进行访问。

我们在遍历三元组的时候，可以存下每个三元组的子二元组（就是只有第一个元素，只有第二个元素和只有第三个元素三种情况），如果某种子二元组在之前出现过，那么就说明它是符合条件的。

__但是，有可能某几个三元组的所有元素均相等，这种情况需要在计算过程中去掉。__

然后就愉快地 [AC](https://www.luogu.com.cn/record/160753814) 啦！

### AC 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;

int t, n;
int a[200005];
long long ans;
map<pair<int, int>, int> m1, m2, m3;
map<pair<int, pair<int, int> >, int> m4;

int main()
{
	scanf("%d", &t);
	while(t--)
	{
	    ans = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		m1.clear(), m2.clear(), m3.clear(), m4.clear();
		for(int i = 1; i <= n - 2; i++)
		{
			pair<int, int> p1, p2, p3;
			pair<int, pair<int, int> > p4;
			p1.first = a[i], p1.second = a[i + 1];
			p2.first = a[i], p2.second = a[i + 2];
			p3.first = a[i + 1], p3.second = a[i + 2];
			p4.first = a[i];
			p4.second.first = a[i + 1];
			p4.second.second = a[i + 2];
			ans += m1[p1] + m2[p2] + m3[p3] - 3 * m4[p4];
                        //关键点，要去除三个元素全等的情况。
			m1[p1]++;
			m2[p2]++;
			m3[p3]++;
			m4[p4]++;
		}
		printf("%lld\n", ans);
	}
	return 0;
}

```

有的小明可能就要疑惑了，为啥算的时候还要把减去的 ```m4[p4]``` 乘上三嘞？

我们来浅推一下：如果两个三元组中元素全部相等，那么在计算的时候，就会多计算三次（因为三个元素不能全等），所以乘三。如果不全等的话 ```m4[p4]``` 就为零，零乘任何数都得零。

祝自己信息与未来 $rp++$!

---

## 作者：Genshin_ZFYX (赞：1)

闲话：map 真的嘎嘎好用。

有三种情况，可以将两个三连对视为美丽三连对：

1. 前两个数相同，且第三个数不同；
2. 后两个数相同，且第一个数不同；
3. 前后两数相同，且中间的数不同。

我们先不管每一条后面的要求，用三个 map 套用 pair 依次记录这三种情况前一条要求，再用一个 map 记录三个数都相同的情况（情况 4），对于每个情况 4 我们都减去 3，因为每三个数中可以取出 3 对数。

用一个变量 $ans$ 记录答案，最后输出答案即可。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
map<pair<int,int>,int>mp,mp2,mp3;
map<pair<pair<int,int>,int>,int>mp4;
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t;cin>>t;
	while(t--)
	{
		int n;long long ans=0;
		cin>>n;
		mp.clear();
		mp2.clear();
		mp3.clear();
		mp4.clear();
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<n-1;i++)
		{
			ans+=mp[make_pair(a[i],a[i+1])];
			ans+=mp2[make_pair(a[i+1],a[i+2])];
			ans+=mp3[make_pair(a[i],a[i+2])];
			mp[make_pair(a[i],a[i+1])]++;
			mp2[make_pair(a[i+1],a[i+2])]++;
			mp3[make_pair(a[i],a[i+2])]++;
		}
		for(int i=2;i<n;i++)
		{
			ans-=mp4[make_pair(make_pair(a[i-1],a[i]),a[i+1])]*3;
			mp4[make_pair(make_pair(a[i-1],a[i]),a[i+1])]++;
		}
		cout<<ans<<'\n';
	}
	return 0;
 }
```

---

## 作者：haokee (赞：1)

一种比较通俗易懂的解法。

我们将需要相等的分为一组，也就是对应两个相等的性质，然后在每组里面分别进行统计：需要满足另外一个数不相等，那么我们只需要将答案累加这个数的数量乘上其他不同的数的数量就行了。

注意这种统计方法会双向统计，因此答案在输出的时候需要除以 $2$。

```cpp
#include <iostream>
#include <utility>
#include <map>

using namespace std;
using LL = long long;

const LL kMaxN = 2e5 + 5;

LL a[kMaxN], t, n, ans;
map<pair<LL, LL>, map<LL, LL>> f;  // 每一组里面的每一个数的记数
map<pair<LL, LL>, LL> c;           // 每一组里面元素数量

void solve(int x1, int x2, int x3) {         // x1 和 x2 满足等于，x3 满足不等于
  f.clear(), c.clear();                      // 清空
  for (LL i = 1; i <= n - 2; i++) {          // 遍历每一个三元组
    f[{a[i + x1], a[i + x2]}][a[i + x3]]++;  // 分组并加入
    c[{a[i + x1], a[i + x2]}]++;
  }
  for (auto &i : f) {                             // 遍历每一组
    for (auto &j : i.second) {                    // 遍历这一组里面的所有数
      ans += j.second * (c[i.first] - j.second);  // 当前数的数量乘上其他数的数量
    }
  }
}

int main() {
  for (cin >> t; t; t--) {
    cin >> n, ans = 0;
    for (LL i = 1; i <= n; i++) {
      cin >> a[i];
    }
    solve(0, 1, 2);           // 对于不同的限制分类求答案
    solve(0, 2, 1);
    solve(1, 2, 0);
    cout << ans / 2 << '\n';  // 注意除以二
  }
  return 0;
}
```

---

## 作者：liyp (赞：0)

[纯享版](https://www.luogu.com.cn/article/zww4lryb)
  [题目传送门](https://www.luogu.com.cn/problem/CF1974C)

## 思路
暴力枚举肯定是过不了的。

能构成这样的三元对需要满足以下三个条件的**任意**一个。

- **第一个**位置与**第二个**位置相同，**第三个**位置不同。
- **第二个**位置与**第三个**位置相同，**第一个**位置不同。
- **第一个**位置与**第三个**位置相同，**第二个**位置不同。

但是在满足以上条件的三元对中，有一些是**三个位置都相同**的，因此我们还要单独考虑。

可以考虑开 4 个 ``map``，分别存储第一、二位，第二、三位，第一、三位，第一、二、三位。

每一次我们处理一个三元对时，在 ``map`` 中查看有多少个和自己 1、2 位相同的、第 2、3 位相同的、第 1、3 位相同的以及完全相同的，将**满足前三个条件**的三元对（不包括自己）数量之和加入答案，再将**三倍的**与自己**完全相同**的三元对数量减去（原理如**图一**），就可以求出来了。

![图1](https://cdn.luogu.com.cn/upload/image_hosting/pxny0g21.png)

这道题就
[AC](https://www.luogu.com.cn/record/163701481)
了。

## 完整代码
```cpp
// C++14 (GCC 9)  718ms 37.59MB
// AC number: R163701481
#include <bits/stdc++.h>
#define LL long long
#define int long long
#define FR q.front()
using namespace std;
const int MAXN = 2e5 + 10;
int a[MAXN], n, ans = 0;
struct code {
	int a, b, c;
};
code s[MAXN];

int f[4],flag[MAXN],dis[MAXN];
bool amount(code x, code y) {
	if (x.a != y.a) return 0;
	if (x.b != y.b) return 0;
	if (x.c != y.c) return 0;
	return 1;
}
bool check(code x, code y) {
	int vis = 0;
	vis += (x.a == y.a);
	vis += (x.b == y.b);
	vis += (x.c == y.c);
	if (vis == 3) return 1;
	vis = 0;
	vis += (x.b == y.a);
	vis += (x.c == y.b);
	if (vis == 2) return 1;
	return 0;
}
const int c = 1000111;

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		cin >> n; ans = 0;
		map<LL, LL>m12, m23, m13, m;
		for (int i = 1; i <= n; i++) cin >> a[i];
		
		for (int i = 1; i <= n - 2; i++) {
			m12[a[i] * c + a[i + 1]]++;
			m23[a[i] * c + a[i + 2]]++;
			m13[a[i + 1] * c + a[i + 2]]++;
			m[a[i] * c * c + a[i + 1] * c + a[i + 2]]++;
			ans += m12[a[i] * c + a[i + 1]] - 1;
			ans += m23[a[i] * c + a[i + 2]] - 1;
			ans += m13[a[i + 1] * c + a[i + 2]] - 1;
			ans -= 3 * (m[a[i] * c * c + a[i + 1] * c + a[i + 2]] - 1);
		}
		cout << ans<<endl;
	}
	
	return 0;
}
```
## 附
[【STL简介】map  -  cnblog](https://www.cnblogs.com/thankgoodness/articles/1141572.html)

---

