# Romantic Glasses

## 题目描述

Iulia has $ n $ glasses arranged in a line. The $ i $ -th glass has $ a_i $ units of juice in it. Iulia drinks only from odd-numbered glasses, while her date drinks only from even-numbered glasses.

To impress her date, Iulia wants to find a contiguous subarray of these glasses such that both Iulia and her date will have the same amount of juice in total if only the glasses in this subarray are considered. Please help her to do that.

More formally, find out if there exists two indices $ l $ , $ r $ such that $ 1 \leq l \leq r \leq n $ , and $ a_l + a_{l + 2} + a_{l + 4} + \dots + a_{r} = a_{l + 1} + a_{l + 3} + \dots + a_{r-1} $ if $ l $ and $ r $ have the same parity and $ a_l + a_{l + 2} + a_{l + 4} + \dots + a_{r - 1} = a_{l + 1} + a_{l + 3} + \dots + a_{r} $ otherwise.

## 说明/提示

In the first test case, Iulia can pick $ l=1 $ and $ r=3 $ . Then she drinks $ a_1+a_3=1+2=3 $ units and her date drinks $ a_2=3 $ units of juice.

In the second test case, Iulia can pick $ l=2 $ and $ r=5 $ . Then she drinks $ a_3+a_5=1+1=2 $ units and her date drinks $ a_2+a_4=1+1=2 $ units of juice.

In the third test case no such contiguous subarray works.

In the fourth test case, Iulia can pick $ l=2 $ and $ r=8 $ . Then she drinks $ a_3+a_5+a_7=11+1+1=13 $ units and her date drinks $ a_2+a_4+a_6+a_8=2+4+5+2=13 $ units of juice.

## 样例 #1

### 输入

```
6
3
1 3 2
6
1 1 1 1 1 1
10
1 6 9 8 55 3 14 2 7 2
8
1 2 11 4 1 5 1 2
6
2 6 1 5 7 8
9
2 5 10 4 4 9 6 7 8```

### 输出

```
YES
YES
NO
YES
NO
YES```

# 题解

## 作者：WsW_ (赞：6)

难度约为黄。

---
### 思路
首先奇偶分开，互不影响，就相当于是两个序列。  
由于需要区间求和，所以考虑前缀和。  
假设用 $sum_{0,i},sum_{1,i}$ 分别表示**原序列**前 $i$ 个数中 奇数/偶数 的和，那么题目变成了如下：

是否存在 $L,R\in[1,n]$，使得 $sum_{0,R}-sum_{0,L}=sum_{1,R}-sum_{1,L}$。

把等式两边移一下项，就成了 $sum_{0,R}-sum_{1,R}=sum_{0,L}-sum_{1,L}$。  

显然，最多只存在 $n$ 个不同的 $sum_{0,L}-sum_{1,L}$。  
因此，我们可以把所有的 $sum_{0,L}-sum_{1,L}$ 是多少存下来，如果存在相同的就说明等式可以成立。  

可是 $sum_{0,L}-sum_{1,L}$ 如果用数组开桶存，远远超出了内存。可以用 `set`、`map` 等容器存，或者存入一个序列，最后再排序。  

上述方法时间复杂度相同，单次询问复杂度均为 $O(n \log n)$。  

代码选择用 `set` 存储，代码较为简单。但是不要忘了多测要初始化。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int T;
int n;
int a[2][100003];
set<ll>s;
ll sum[2];
//0存偶数，1存奇数

void work(){
	s.clear();  s.insert(0);
	sum[1]=sum[0]=0;//初始化
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i&1][i+1>>1];
	}
	
	for(int i=1;i<=n;i++){
		sum[i&1]+=a[i&1][i+1>>1];
		if(s.count(sum[1]-sum[0])){//查询是否存在
			cout<<"YES\n";
			return;
		}
		s.insert(sum[1]-sum[0]);//存储
	}
	cout<<"NO\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：wxzzzz (赞：4)

### 思路

记 $sum1_i$ 表示 $1\sim i$ 所有奇数 $i$ 的 $a_i$ 之和。

记 $sum2_i$ 表示 $1\sim i$ 所有偶数 $i$ 的 $a_i$ 之和。

题目就被转化成了判断是否存在 $sum1_r-sum1_{l-1}=sum2_r-sum2_{l-1}$。

这个式子可化为 $sum1_r-sum2_r=sum1_{l-1}-sum2_{l-1}$。

用一个 map 判断即可，注意此题卡 unordered_map。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, sum1, sum2, a[200005];
map<long long, bool> flag;
bool check() {
    long long sum1 = 0, sum2 = 0;

    for (int i = 1; i <= n; i++) {
        if (i % 2)
            sum1 += a[i];
        else
            sum2 += a[i];

        if (sum1 == sum2 || flag[sum1 - sum2])
            return 1;

        flag[sum1 - sum2] = 1;
    }

    return 0;
}
int main() {
    cin >> t;

    while (t--) {
        cin >> n;
        flag.clear();

        for (int i = 1; i <= n; i++)
            cin >> a[i];

        if (check())
            puts("YES");
        else
            puts("NO");
    }

    return 0;
}
```

---

## 作者：huangzhixia (赞：2)

**[题目传送门](https://www.luogu.com.cn/problem/CF1915E)**

## 题意

跟往常的 CF 一样，有 $t$ 组数据，对于每组数据，有一个数 $n$，接下来 $n$ 个数 $a_1,a_2,……,a_n$。现在让我们看看又没有一个 $L$ 到 $R$ 的区间里的数下标是奇数的和与下标为偶数的和相等，相等输出 ```YES```，否则输出 ```NO```。

## 思路

首先我们想到的就是暴力！暴力枚举每个区间 $L$ 和 $R$，然后~~无脑~~简单地加一下，看看相不相同。

但这显然会 TLE，枚举 $L$ 一层 for，枚举 $R$ 一层 for，还要加起来看一看还是一层 for，这样我们会达到惊人的 $O(n^3)$ 的时间复杂度！$1s$ 显然是跑不出来的。

那正解怎么写呢？

这里涉及到区间相加的问题，相信大家不难想到**前缀和**，我们预处理，这里需要用到两个数组来记，如下：

- 用 $s1_i$ 来表示从 $1$ 到 $i$ 的下标为奇数之和。

- 用 $s2_i$ 来表示从 $1$ 到 $i$ 的下标为偶数之和。

这样我们就不用计算了，直接在 $s1$ 和 $s2$ 数组里找就行啦！等到以下判断式子：

这样，$s1_R - s2_{L-1} = s2_R - s2_{L-1}$。

可化简为：

简化为这样，$s1_R - s2_R = s1_{L-1}-s2_{L-1}$。

OK呀，经过前缀和的优化我们的时间复杂度成功降到了 $O(n^2)$，但还是会 TLE。除非我们降到 $O(n)$。

这里就要使用 STL 大法 map 啦！

map 存一些什么东西呢？

我们可以看一下我们的前缀和数组，把那数组里面的数加入一个看一个，看一下是不是出现过相等的。相等就直接输出 ```YES```，否则就继续看下去，一直循环，当然，这肯定是要预处理的。

无意之间我们就把此题时间复杂度将为了 $O(n)$。

## AC Code：

```cpp
#include <bits/stdc++.h>
#define hh; puts(""); //个人喜好 
using namespace std;    

map<int, bool> edges;
int test, s1, s2, n, a[200001]; //函数要用，不开栈里不行 

inline bool check() {
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) //是奇数 
            s1 += a[i]; //加上去 
        else //是偶数 
            s2 += a[i];
        if (s1 == s2 || edges[s1 - s2]) //讲过的式子 
            return true; 
        edges[s1 - s2] = true;
    }
    return false;
}       

inline void solve() {  	
	s1 = 0, s2 = 0;
	edges.clear();
	scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    	scanf("%d", &a[i]);
    if (check())
		printf("YES");
    else
		printf("NO");
	hh;
}

int main() {
	scanf("%d", &test);
    while (test--)
    	solve();
}
```


---

## 作者：ThySecret (赞：1)

[Romantic Glasses](https://www.luogu.com.cn/problem/CF1915E)

## 解题思路

题目说的很清楚了，求是否存在 $L$ 和 $R$，使 $a_L$ 到 $a_R$ 中奇数下标的数之和等于偶数下标的数之和，如果存在输出 `Yes`，否则输出 `No`。

### 方法一：前缀和 + 暴力

抛开时间复杂度（$n ^ 2$）不谈，在输入过程中根据下标奇偶性预处理前缀和数组，再通过双重循环判断即可。

```c++
for (int i = 1; i <= n; i ++)
	{
		int x; cin >> x;
		if (i & 1) pre[i] = pre[i - 2] + x;
		else pre[i] = pre[i - 2] + x;
	}
```

### 方法二：前缀和 + map

仔细想想不难看出，我们可以仅在一个前缀和数组上双向处理，如果 $i$ 为奇则加上这个数，为偶则减去这个数。此时求出的前缀和 $pre_i$ 就是 从 $1$ 到 $i$ 之中奇数下标之和与偶数下标之和之差。如果存在 $pre_{i - 1} = pre_j$，则说明从 $i - 1$ 到 $j$ 之中数下标的数之和等于偶数下标的数之和，此时可以输出 `YES`，如果在循环之后没有 `NO`。

## AC Code

```c++
// Problem: E. Romantic Glasses
// Contest: Codeforces - Codeforces Round 918 (Div. 4)
// URL: https://codeforces.com/contest/1915/problem/E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
#define int long long

const int N = 2e5 + 9;
const int INF = 0x3f3f3f3f;
int n, pre[N];
map<int, bool> mp;

bool solve()
{
	bool flag = false;
    cin >> n;
    mp.clear(); mp[0] = true;
    for (int i = 1; i <= n; i ++)
    {
        int x; cin >> x;
        if (i & 1) pre[i] = pre[i - 1] + x;
        else pre[i] = pre[i - 1] - x;
        
        if (mp[pre[i]] == true) flag = true;
        mp[pre[i]] = true;
    }
    return flag;
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin >> T;
    while (T --) cout << (solve() ? "YES\n" : "NO\n");
    return 0;
}
```

---

## 作者：AlicX (赞：1)

## Solution 

~~神题,orz~~。

用 $s1_i$ 表示 $\sum \limits_{j=1}^{i} a_j(j \bmod 2=1)$，用 $s2_i$ 表示 $\sum \limits_{j=1}^{i} a_j(j \bmod 2=1)$。

然后利用差分的思想不难将题目条件转化为 $s2_r-s2_{l-1}=s1_{r}-s1_{l-1}$，变一下式子即为 $s2_r-s1_r=s2_{l-1}-s1_{l-1}$，发现等式两边形如 $s2_i-s1_i$，用 `map` 打标记即可。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=2e5+10; 
int n; 
int a[N]; 
int s1[N],s2[N]; 
void work(){ 
	cin>>n; map<int,bool> mp;mp[0]=true;  
	for(int i=1;i<=n;i++){
		cin>>a[i]; 
		s1[i]=s1[i-1],s2[i]=s2[i-1]; 
		if(i&1) s1[i]+=a[i]; else s2[i]+=a[i]; 
	} for(int i=1;i<=n;i++){ 
		int x=s1[i]-s2[i]; 
		if(mp[x]){
			puts("YES"); 
			return ; 
		}
		mp[s1[i]-s2[i]]=true; 
//		s1[r]-s1[l-1]==s2[r]-s2[l-1] 
//		s1[r]-s2[r]==s1[l-1]-s2[l-1] 
	} puts("NO");
} 
signed main(){ 
	int T; scanf("%lld",&T); 
	while(T--) work(); return 0; 
} 
```


---

## 作者：foryou_ (赞：1)

我们考虑维护 $sum_i$ 表示前 $i$ 个数中偶数下标的数之和与奇数下标的数之和之差，其中 $sum_0=0$。

若在某一时刻，有 $sum_i=sum_j(j<i)$，说明 $j \sim i$ 中偶数下标的数之和与奇数下标的数之和之差为 $0$。这个使用 `map` 判断即可。

实现：

```cpp
int n,f=0; cin>>n;
m.clear(),m[0]=1; //m是用于判断的map
memset(sum,0,sizeof(sum));
for(int i=1,x;i<=n;i++){
	cin>>x;
	if(i%2==0) sum[i]=sum[i-1]+x;
	else sum[i]=sum[i-1]-x;
	if(m[sum[i]]) f=1;
	m[sum[i]]=1;
}
return f; //f为1输出YES，否则输出NO
```

---

## 作者：indream (赞：0)

## CF1915E Romantic Glasses 题解
[洛谷](https://www.luogu.com.cn/problem/CF1915E) | [CodeForces](http://codeforces.com/problemset/problem/1915/E) | [AC](https://codeforces.com/contest/1915/submission/241340962)
### 思路
类似前缀和。

设 $odd_i$ 表示前 $i$ 个数中 $i$ 为奇数的 $a_i$ 之和，$eve_i$ 表示前 $i$ 个数中 $i$ 为偶数的 $a_i$ 之和。

我们要求的是：
$$odd_r-odd_l=eve_r-eve_l$$
移项得：
$$odd_r-eve_r=odd_l-eve_l$$
所以我们只要用 `map` 记录所有 $odd_i-eve_i$ 的值，判重即可得知能否满足题目要求。

注意：
- 判断到重复后不能 `break;`，应把剩下的输入读完；
- 多测记得清空。

### 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
typedef long long ll;
ll odd[MAXN],eve[MAXN],tmp,T,n;
map<ll,bool> rem;
bool check;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>T;
    while(T--){
        rem.clear();rem[0]=1;
        odd[0]=0;eve[0]=0;
        check=1;
        cin>>n;
        for(int i=1;i<=n;++i){
            odd[i]=odd[i-1];
            eve[i]=eve[i-1];
            cin>>tmp;
            if(i&1) 
                odd[i]+=tmp;
            else
                eve[i]+=tmp;
            ll t2=odd[i]-eve[i];
            //cerr<<odd[i]<<'-'<<eve[i]<<'='<<t2<<'('<<check<<')'<<'\n';
            if(rem[t2]&&check){
                puts("Yes");
                check=0;
            }else{
                rem[t2]=1;
            }
        }
        if(check)
            puts("No");
    }
    return 0;
}

```


---

## 作者：细数繁星 (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/CF1915E)

[博客园体验更好！](https://www.cnblogs.com/2044-space-elevator/articles/17949489)

首先我们在 $i\nmid 2$ 时设 $a_i=-a_i$，这样我们可以将：

$$
\sum_{i=l}^ra_{2i}=\sum_{i=l}^ra_{2i+1}
$$
改为：

$$
\sum_{i=l}^ra_i=0
$$

接下来就好办了，设 $S(n)$ 为 $\large \sum\limits_{i=1}^na_i$，即其的前缀和，那么我们再搞个映射表 $V$，当 $V_{S(n)}=1$ 时，说明此前有一个 $S(n)$ 已经等于当前的 $S(n)$ 了，那么就输出 `YES`，否则设 $V_{S(n)}=1$。

需要注意以下三点：

- 映射表必须 `clear`！映射表必须 `clear`！映射表必须 `clear`！重要的事情说三遍！
- $V_0=1$，因为这说明存在 $\large \sum\limits_{i=1}^na_i=0$，那么这也是一种合法情况！
- 最后一个可能大家都会有：不要在遇见条件合法的情况直接给它 `break` 掉，因为这个数组后面的内容还没输进去，这样后面再输入 $n$ 时会把原来数组的数给弄进去。所以每一个小点你就算已经算出来了也得把数组里的数给磕完。
- 不开 `long long` 会看到祖宗哦。

~~本人应该是唯一一个不想用也懒得用数组的，唯一占空间的只有个映射表。~~

上代码吧。

```cpp
#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
#define vct vector
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define int ll
map<int, bool> mark;

void solve() {
    int n;
    mark.clear();
    // 您猜猜不 clear 会发生什么……
    mark[0] = 1;
    cin >> n;
    int x = 0;
    bool flag = 0;
    rep(i, 1, n) {
        int p;
        cin >> p;
        if (flag) {
            continue;
        }
        if (i % 2) {
            p = -p;
        }
        x += p;
        if (mark[x]) {
            RTY
            flag = 1; // 一个坑点，不要遇到 YES 直接 return 了，后面的数没读入到这样 cin 会把数组的数当 n 读进去
        }
        mark[x] = 1;
    }
    if (!flag)
        RTN
}


main() {
	int t; cin >> t; while (t--) solve();
	return 0;
}

```

---

## 作者：BugGod (赞：0)

首先看到静态区间的区间和，想到前缀和，可以很方便的维护奇数位的和以及偶数位的和。然后我们可以把题目中要求的式子变形一下：（$S$ 是奇数位的和，$T$ 是偶数位的和）

$$S_{r}-S_{l-1}=T_{r}-T_{l-1}$$

$$S_r-T_r=S_{l-1}-T_{l-1}$$

那么我们这个式子就变为了同一下标的奇数位和偶数位求和是否相等，我们开一个 `map` 维护每一个同位和，看一看是否有相等的。

*Tips:* 如果 $S_{r}=T_{r}$ 也是合法的（$[1,r]$ 的和），所以初始化 `map` 下标为 $0$ 的为真。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void file(string file_name)
{
	freopen((file_name+".in").c_str(),"r",stdin);
	freopen((file_name+".out").c_str(),"w",stdout);
}
int n,a[200010],sum[2][200010];
void solve()
{
	cin>>n;
	map<int,int>m;
	m[0]=114513&1;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		for(int s=0;s<=1;s++)sum[s][i]=sum[s][i-1]+(i&1^(1-s))*a[i];
	}
	for(int i=1;i<=n;i++)
	{
		int c=sum[0][i]-sum[1][i];
		//cout<<c<<'\n';
		if(m[c])
		{
			cout<<"yes\n";
			return ;
		}
		m[c]=1;
	}
	cout<<"no\n";
}
signed main()
{
	//IOS();
	//file("");
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

## 主要思路：前缀和
### 题意简述
输入 $t$ 个序列 $a$，求是否有满足要求的 $l$ 和 $r$ 使 $a_l$ 到 $a_r$ 中偶数下标数字之和等于奇数下标数字之和。
- - -
### 分析
我们可以开两个前缀和来分别记录奇数下标的前缀和，偶数下标的前缀和。将每个位置的两个前缀和之差存入标记数组中。如果两个前缀和之差在之前就出现过了，则可以说明有满足要求的 $l$ 和 $r$ 使 $a_l$ 到 $a_r$ 中偶数下标数字之和等于奇数下标数字之和。
- - -
### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,t,a,s[1000005],s1[1000005];
map<int,int> m;
void f1(int x,int y){//计算前缀和 
	s[x]=s[x-1];
	s1[x]=s1[x-1];
	if (x%2==1) s[x]+=y;//奇数 
	else s1[x]+=y;//偶数 
}
signed main(){
	cin.tie(),cout.tie();
	cin>>t;
	while(t--){
		m.clear();//清空标记数组 
		m[0]=1;
		int f=0;
		cin>>n;
		for (int i=1;i<=n;i++){
			cin>>a;//输入 
			f1(i,a);
			int x=s[i]-s1[i];//两个前缀和之差 
			if (m[x]==1 and f==0){//判断 
				cout<<"YES\n";
				f=1;
			}
			m[x]=1;
		}
		if (f==0){
			cout<<"NO\n";
		}
	}
	return 0;
} 
```

---

## 作者：___nyLittleT___ (赞：0)

## 题意简述
给定一个序列 $a$，求出有没有可能有一个区间满足区间内奇数下标的数之和等于偶数下标的数之和。  
## 复杂度分析
暴力法时间复杂度为 $\mathcal O(tn^2)$，显然，一堆 TLE 正在等着你提交代码。那么我们另辟蹊径。
## 怎样解决？
开两个前缀和数组，记录奇偶下标的前缀和。再比较同位之差就行了。
# 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a;
long long sum1[200005],sum2[200005];
map<long long,bool>same;
void init(){
	same[0]=1;
}
void solve() {
	same.clear();
	init();
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		scanf("%d",&a);
		sum1[i]=sum1[i-1];
		sum2[i]=sum2[i-1];
		if(i&1==1) sum1[i]+=a;
		else sum2[i]+=a;
	}
	for(int i=1; i<=n; i++) {
		long long tmp=sum1[i]-sum2[i];
		if(same[tmp]) {
			printf("YES\n");
			return;
		}
		same[tmp]=1;
	}
	printf("NO\n");
}
int main() {
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```
**写题解不易，万望管理员大大通过。**

---

## 作者：Addicted_Game (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF1915E)
### 题目大意
给定一个数组，求是否有其中一个区间内奇数下标数字之和等于偶数下标数字之和。

### 思路
先开前缀和数组 $s1$ 与 $s2$ 记为奇数与偶数项之和，然后找它们的同位的差值是否出现过即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long s1[200005],s2[200005];
int n;
map<long long,bool> d;
long long a[200005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		d.clear();//记得初始化
		d[0]=true;
		cin>>n;
		bool t=false;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			s1[i]=s1[i-1];
			s2[i]=s2[i-1];
			if(i%2) s1[i]+=a[i];
			else s2[i]+=a[i];//分别计算奇偶前缀和
			if(d[s1[i]-s2[i]]){
				cout<<"YES";
				t=true;
				break;
			}
			d[s1[i]-s2[i]]=true;
		}
		if(!t) cout<<"NO";
		cout<<"\n";		
	}
	return 0;
}
```


---

## 作者：Six_chestnuts (赞：0)

# 前言

类似于一种前缀和的同与思想的一种做法

# 详细步骤

开两个前缀和分别统计奇数下标的数组的和和偶数下标的数组的和。

再枚举一遍数组把奇数和偶数的前缀和的差统计起来如果之前有这个差就可以，因为两个区间的差就低消掉了。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int t,sum1[N],sum2[N],n;
void work()
{
	map<int,bool> m;
	cin>>n;
	m[0]=true;
	bool flag=false;
	for(int i=1;i<=n;i++)
	{
		int a;
		cin>>a;
		sum1[i]=sum1[i-1];
		sum2[i]=sum2[i-1];
		if(i%2==1)
			sum1[i]+=a;
		else
			sum2[i]+=a; 
		int diff=sum1[i]-sum2[i];
		if(m[diff]&&flag==false)
		{
			cout<<"YES\n";
			flag=true;
		}
		else if(flag==false)
			m[diff]=true;
	}
	if(flag==false)
		cout<<"NO\n";
	return ;
}
signed main()
{
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
		work();
	return 0;
}
```


---

## 作者：DrAlfred (赞：0)

摘要：数据结构，分类讨论，前缀和，统计

[传送门：https://www.luogu.com.cn/problem/CF1915E](https://www.luogu.com.cn/problem/CF1915E)

## 题意

$ t $ 组数据。每次给定一个数列 $ a $，判断是否存在一个区间 $ [l, r] $ 使得：

如果 $ l, r $ 同奇偶，则 $a_l + a_{l+2} + a_{l+4} + ... + a_r = a_{l+1} + a_{l+3} + ... + a_{r-1}$。

如果 $ l, r $ 异奇偶，则 $a_l + a_{l+2} + a_{l+4} + ... + a_{r-1} = a_{l+1} + a_{l+3} + ... + a_{r}$。

## 分析思路

记 $ x_i $ 表示到第 $ i $ 个位置，所有奇数位上的数的和。记 $ y_i $ 表示到第 $ i $ 个位置，所有偶数位上的数的和。

选定一个区间 $ [l, r] $。判断条件等价于 $x_r - x_{l - 1} = y_r - y_{l - 1}$。变形可得 $x_r - y_r = x_{l-1}-y_{l-1}$ 。在 `std::set` 中记录每一个位置的 $x_i-r_i$，判断在第 $ i $ 个位置之前是否有相同的差即可。

注意对于第 $0$ 个位置，$x_i - y_i = 0$，需要插入到 `std::set` 中。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
long long t, n, a[N];
inline void solve(void) {
    set<long long> S;
    cin >> n, S.insert(0);
    long long x = 0, y = 0, f = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i & 1) x += a[i];
        else y += a[i];
        if (S.count(x - y)) f = 1;
        S.insert(x - y);
    }
    puts(f ? "YES" : "NO");
}
int main(int argc, char const *argv[]) {
    cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：Xiphi (赞：0)

### CF1915E

考虑把式子转化成 $a_l-a_{l+1}+a_{l+2}-\dots ± a_r=0$，若 $r,l$ 同奇偶，加上 $a_r$，否则是减 $a_r$。



接着考虑一个性质，若有两个前缀和相等，设其为 $[1,i]$，$[1,j]$ 相等，则 $[i,j](i\le j)$ 的和一定等于 $0$。



那么把这个性质转化到这个题上，即把奇数下边转换成它的相反数，然后做前缀和判断有没有相等的就行了。



代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n,a[200005];
map<int,int> box1,box2;
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>T;
	while(T--){
		box1.clear(),box2.clear();
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		int s1=0,s2=0,flag=0;
		box1[0]++;
		for(int i=1;i<=n;i++){
			if(i&1) s1+=-a[i];
			else s1+=a[i];
			box1[s1]++;
		}
		for(auto it=box1.begin();it!=box1.end();++it){
			if(2<=it->second){
				flag=1;break;
			}
		}
		for(auto it=box2.begin();it!=box2.end();++it){
			if(2<=it->second){
				flag=1;break;
			}
		}
		if(flag) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

```




---

## 作者：Natori (赞：0)

>[CF1915E Romantic Glasses](https://www.luogu.com.cn/problem/CF1915E)

我们考虑把奇数下标位置上的数标记为原数的相反数，那么相当于询问是否存在一个区间的区间和为 $0$。

考虑求出新数组的前缀和数组。如果一段区间的和为 $0$，那么在前缀和数组中就必定会有两个相等的数。依次把数加入 ```map``` 中并判断是否出现过即可。~~笔者用 set 不知道为什么挂了~~

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
const int N=2e5+8;
int n,a[N],sa[N];
void mian(){
	for(int i=1;i<=n;i++){
		a[i]=0;
		sa[i]=0;
	}
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(i%2==1)
			a[i]=-a[i];
	}
	for(int i=1;i<=n;i++)
		sa[i]=sa[i-1]+a[i];
	map<int,int> Map;
	Map[0]=1;
	bool ok=0;
	for(int i=1;i<=n;i++){
		if(Map[sa[i]]==1){
			ok=1;
			break;
		}
		Map[sa[i]]=1;
	}
	if(ok==1)
		cout<<"YES";
	else
		cout<<"NO";
	cout<<'\n';
}
bool Mend;
signed main(){
//	File_Work();
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<fixed<<setprecision(3)<<(&Mbegin-&Mend)/1048576.0<<" MB\n\n\n";
	int testnum=1;
	cin>>testnum;
	while(testnum--)
		mian();
	cerr<<"\n\n\n"<<fixed<<setprecision(0)<<1e3*clock()/CLOCKS_PER_SEC<<" ms";
	return 0;
}
```

---

## 作者：Very_Smart_Honet (赞：0)

首先，我么们看到数据范围

$t\le 10^{4}$，$n\le 2\times 10^{5}$;

我们可以知道时间复杂度只能为 $O(T\times N)$，鉴于这道题只询问 `YES` 或 `NO`，所以我产生了以下思路：

- 看到这题我们就会想到前缀和，但这题需要简略前缀和。

- 用一个 $vis$ 来记录之前出现过的值，如果出现过，则输出 `YES`。
                                           
- 开一个 $flag$ 来记录有没有输出。
                                           
用 $sum1$ 记录奇数的个数，用 $sum2$ 记录偶数的个数。从 $1$ 一直循环到 $n$。如果我们找到两个奇偶相差一样的量，将这两个量相减，则中间的一段数就为奇偶亮相等的集合了。



注意：
- $vis$ 要开 map 类型
- 输入量较大，需要用 scanf。
                                           
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
ll t,sum1[N],sum2[N],n;
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		map<ll,bool>vis;
		scanf("%lld",&n);
		vis[0]=true;
		ll flag=0;
		for(ll i=1;i<=n;i++)
		{
			ll a;
			scanf("%lld",&a);
			sum1[i]=sum1[i-1];sum2[i]=sum2[i-1];
			if(i%2==1) sum1[i]+=a;
			else sum2[i]+=a; 
			ll x=sum1[i]-sum2[i];
			if(vis[x]==true&&flag==0)
			{printf("YES\n");flag=true;}
			else if(flag==0)vis[x]=true;
		}
		if(flag==0)printf("NO\n");
	}
	return 0;
}
```

---

