# [AGC023A] Zero-Sum Ranges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc023/tasks/agc023_a

長さ $ N $ の整数列 $ A $ があります。

$ A $ の **空でない** **連続する** 部分列であって、その総和が $ 0 $ になるものの個数を求めてください。 ただし、ここで数えるのは **部分列の取り出し方** であることに注意してください。 つまり、ある $ 2 $ つの部分列が列として同じでも、取り出した位置が異なるならば、それらは別々に数えるものとします。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ -10^9\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

空でない連続した部分列であって、その総和が $ 0 $ になるのは、$ (1,3,-4) $, $ (-4,2,2) $, $ (2,-2) $ の $ 3 $ つです。

### Sample Explanation 2

この例では、列として同じだが取り出す位置の異なる部分列が複数回数えられています。 例えば、$ (1,-1) $ は $ 3 $ 回数えられています。

### Sample Explanation 3

空でない連続した部分列であって、その総和が $ 0 $ になるものはありません。

## 样例 #1

### 输入

```
6
1 3 -4 2 2 -2```

### 输出

```
3```

## 样例 #2

### 输入

```
7
1 -1 1 -1 1 -1 1```

### 输出

```
12```

## 样例 #3

### 输入

```
5
1 -2 3 -4 5```

### 输出

```
0```

# 题解

## 作者：fish_love_cat (赞：4)

这题要求的是区间和为 0 的区间数量，一眼前缀和。

我们知道，要使区间和为 0，起始位置前一格的前缀和与终点位置的前缀和必然是相同的。我们记录每个数字作为前缀和出现的次数，如果说这个数字在前面出现过甚至出现了不止一次，那么对于前面每出现一次对应的数字，我们就可以形成一个合法的区间。所以对于该前缀和，答案数应增加不含本次的该前缀和出场次数。

特别的，0 在第一个数字前出现过，所以在开始时，前缀和为 0，需要记录一下。

**代码：**

记得开 ```long long``` 哦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
map<long long,int> mapp;
long long sum;//千万别忘了呢。
long long ans;
int main(){
    cin>>n;
    mapp[0]=1;//0の特别待遇
    for(int i=1,x;i<=n;i++){
        cin>>x;
        sum+=x;
        mapp[sum]++;
        ans+=mapp[sum]-1;//减1除去了此次出现。
    }
    cout<<ans;
	return 0;
} 
```

~~不过讲这么细了还需要看代码吗？~~

---

## 作者：yyz_100110 (赞：2)

此题的翻译简单点说就是让你区间和为 $0$ 的区间数量。

我们要使区间和为 $0$。所以我们要用变量去记录这个区间数量，我们可以用两个变量去储存他的次数，那么我们理解完了之后，就可以开始加工我们的代码了。

$0$ 是我们的特殊目标在第一个数出现过所以要单独拿出来，要先去记录一下他的存在。

**重点：**

要开 ```long long```！！！

**Code：**

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n,a[200005]; //全局变量
map<int, int> b;
int sum,ans=0; //我们的计数变量
signed main() {
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		sum+=a[i];
		if (sum ==0&&b[sum]==0) 
			b[sum]++; //记录
		b[sum]++;
		ans+=(b[sum]-1);
	}
	printf("%lld", ans);
	return 0;
} //求过！
```

---

## 作者：cqbzjyh (赞：2)

### Solution.

不难想到前缀和，设 A 数组的前缀和为 $sum$， 如果 $sum_i=sum_j$，则 $i \sim j$ 这一段的和一定为 $0$ 。对于当前的 $sum_i$， 它就可以与之前的每一个值等于 $sum_i$ 的元素构成区间和为 $0$ ，于是我们就可以用一个桶维护每一个前缀和的值已经出现的数量。这里要注意对 $sum_i=0$ 进行特判。这里我们可以用 map 来维护。

时间复杂度为 $O(n \log n)$

### Code.

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[200005];
map<int, int> b;
int sum;
int ans;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		sum += a[i];
		if (sum == 0 && b[sum] == 0) {
			b[sum]++;
		}
		b[sum]++;
		ans += (b[sum] - 1);
//		cout << b[sum] << endl;
	}
	printf("%lld", ans);
	return 0;
} 

```


---

## 作者：shenbairui (赞：1)

## 题目分析
此题要求的是区间和为 $0$ 的区间数量，这样我们想到了前缀和这个东西，我们可以设一个 $a$，$sum$ 就是 $a$ 的前缀和，如果 $sun_i=sum_j$,则 $i \sim j$ 等于 $0$，我们用一个 ```map``` 来维护每一个前缀和的数量。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
map<long long,int> mapp;
long long sum;
long long ans;
int main(){
    cin>>n;
    mapp[0]=1;
    for(int i=1;i<=n;i++){
       cin>>x;
       sum+=x;
       mapp[sum]++;
       ans+=mapp[sum]-1;
    }
   cout<<ans;
   return 0;//好习惯
} 
```

下期见！

---

## 作者：SunsetSamsara (赞：1)

## 题意

输入一个数列 $a$，任选 $i,j$ 满足 $i\le j$。问有多少种情况 $a_i+a_{i + 1}\cdots+a_j=0$。

## 分析

前缀和，设 $a$ 数组的前缀和为 $sum$，如果 $sum_i=sum_j$，则 $i \sim j$ 这一段的和为 $0$ 。于是我们就可以用一个 `map` 维护每一个前缀和的值已经出现的数量。

时间复杂度为 $\Theta(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h> 
#define lld long long 
using namespace std;
int n;
lld a[200005];
map<lld, lld> b;
lld sum;
lld ans;
int main() {
	scanf("%d", & n);
	for (int i = 1; i <= n; ++ i) {
		scanf("%lld", a + i);
		sum += a[i];
		if (!sum && !b[sum]) ++ b[sum];
		++ b[sum];
		ans += b[sum] - 1;
	}
	printf("%lld\n", ans);
}

```

---

## 作者：CQ_Bab (赞：0)

# 思路
我们看到题就可以将从 $a_i$ 加到 $a_j$ 转换成 $s_j-s_{i-1}=0$ （$s_i$ 为 $i$ 的前缀和）那么我们再转一下就变为 $s_j=s_{i-1}$ 那么我们就只用求 $s_i$ 相等的 $i$ 有多少个即可，再看一下数据发现太大就可以用 map 来做了，记 $mp_i$ 为前缀和为 $i$ 时出现的次数。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
const int N=2e5+10;
int n,s[N],res;
map<int,int>mp;
fire main() {
	cin>>n;
	mp[0]=1; //若何为0也可以
	rep(i,1,n) cin>>a[i],res+=mp[s[i]+=s[i-1]]++; //累加 s[i] 并更新答案
	cout<<res<<endl;
	return false;
}

```


---

## 作者：untrigintillion (赞：0)

题意不用赘述了吧。。。

# 方法一

暴力枚举所有的 $i$, $j$, 然后对数列暴力求和。

时间复杂度 $\Theta (n^3)$.

# 方法二

将数列中前 $n$ 项分别求和，并存入一个新的数列 $b$ 中。然后暴力枚举所有的 $i$, $j$, 并判断 $b_i$ 与 $b_j$ 是否相等。

时间复杂度 $\Theta (n^2)$.

# 正解方法三

在方法二中前缀和的基础上，将 $b_i$ 中每个数存入一个 `map<int,int>` 数组中。（因为 `map` 具有不连续下标的性质）

然后在每一次存入 `map` 时，将答案加上 当前 `map` 该下标中的数， 然后再将 `map[b[i]]` 加上 1。

注意特判 $a_i=0$.

时间复杂度 $\Theta (n)$.

---

## 作者：cqbzhyf (赞：0)

只是一道循环结构题目，目的是对思维的考验。

首先，看一下数据范围 $N$ 较大，$A_i$ 也不小，于是只能开一个 `map` 来存储可能和的数目，容易证明，如果已经第二次出现同样的值，则其中一定会有解。

不需开前缀和数组，只需要简单的 $A_i=A_i+A_{i+1}$ 预处理，之后判断之前的说明，就可以得到正解（注意如果 $A_i=0$ 也算一种解）。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+7;
int n,a[maxn],ans;
inline int read(){int ch=0,num=0;char c=getchar();while(c>'9'||c<'0')ch|=(c=='-'),c=getchar();while(c>='0'&&c<='9')num=(num<<1)+(num<<3)+(c^48),c=getchar();if(ch)num=-num;return num;}
map<int,int>t;
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		a[i]+=a[i-1];
		ans+=t[a[i]]++;
		if(!a[i])++ans;
	}
	printf("%lld",ans);
	return 0;
} 
/*
1 3 -4 2 2 -2
1 4 0 2 4 2
*/
```

可以将快读去掉（极限押行）

---

## 作者：Unnamed114514 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT3952)

## 思路
首先，我们求出前缀和 $sum_i$，可以想出如下思路：

设当前求的和为 $[l,r]$，那么和为 $sum_r-sum_{l-1}$。按照要求，使它和为 0，即 $sum_r-sum_{l-1}=0$，即 $sum_r=sum_{l-1}$，所以我们倒序枚举，用 `unordered_map` 维护当前的 $sum_{l-1}$ 在后面出现的次数，然后再把 $sum_{l-1}$ 放入集合即可，答案即为所有的操作之和。时间复杂度 $O(n)$，空间复杂度 $O(n)$。
## AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long//见祖宗
using namespace std;
inline int read(){
	int res=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		f|=(ch=='-');
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=getchar();
	}
	return f?-res:res;
}
const int maxn=2e5+5;
int n=read(),a[maxn],sum[maxn],ans;
unordered_map<int,int> vis;
signed main(){
	for(int i=1;i<=n;++i)
		a[i]=read(),sum[i]=sum[i-1]+a[i];
	for(int i=n+1;i>=1;--i){
		ans+=vis[sum[i-1]];
		++vis[sum[i-1]];
	}//求出答案
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：ys_kylin__ (赞：0)

不用说，这道题是一道典型的前缀和。因为 $n$ 的范围（$2 \times 10^5$）不可以用暴力，因此，要从前缀和的特性出发。

让我们思考一下，假设有两段前缀和的数值相等，如从一到 $x$ 与从一到 $y$ 的前缀和相同，那从 $x+1$ 到 $y$ 的区间和就是 $0$。可以利用此性质来求有多少区间和为 $0$。

每一次用一个 map 来算前缀和为下标的数有多少个，在把前缀和塞进 map 中时，如果发现 map 已经有了数，则 `ans+=cnt[sum]-1`，代表多了 `cnt[sum]-1` 个区间。最后输出 $ans$。

**特别注意！**
- 因为最大要计算 $1$ 到 $10^9$ 的前缀和，所以不开 long long 见祖宗！
- 同样的，由于数据范围，所以要开 map。

## code:
```cpp
#include<bits/stdc++.h>
#define ll long long //十年oi一场空，不开long long见祖宗 ！！！ 
using namespace std;
map <ll,int> cnt;
int main(){
	cnt[0]=1;//对于0,要特殊处理 
	int n;
	ll sum=0,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
    	int x;
        scanf("%d",&x);
        sum+=x,cnt[sum]++,ans+=cnt[sum]-1;//计算更新。 
    }
    printf("%lld",ans);
	return 0;
} 
```

---

## 作者：yzyjh (赞：0)

这道题貌似还没有题解

### 题意

* 给一个数组 a，问其中有多少个区间的和为 0。

### 思路

* 算出前缀和，在其中找出i和j，如果两个点的前缀和相等，ans就加1.

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[100010],b[100010],ans;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	cin>>a[0];
	b[0]=a[0];
	for(int i=1; i<n; i++) {
		cin>>a[i];
		b[i]=b[i-1]+a[i];//算前缀和
	}
	for(int i=0; i<n; i++) {
		for(int j=i+2; j<n; j++) {
			if(b[j]==b[i]) {//如果两个点前缀和相等
				ans++;
			}
		}
	}
	for(int i=0; i<n; i++) {
		if(b[i]==0) {
			ans++;
		}
	}
	cout<<ans;//输出
}
```


---

