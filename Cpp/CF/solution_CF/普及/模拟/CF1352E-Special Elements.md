# Special Elements

## 题目描述

Pay attention to the non-standard memory limit in this problem.

 In order to cut off efficient solutions from inefficient ones in this problem, the time limit is rather strict. Prefer to use compiled statically typed languages (e.g. C++). If you use Python, then submit solutions on PyPy. Try to write an efficient solution.

The array $ a=[a_1, a_2, \ldots, a_n] $ ( $ 1 \le a_i \le n $ ) is given. Its element $ a_i $ is called special if there exists a pair of indices $ l $ and $ r $ ( $ 1 \le l < r \le n $ ) such that $ a_i = a_l + a_{l+1} + \ldots + a_r $ . In other words, an element is called special if it can be represented as the sum of two or more consecutive elements of an array (no matter if they are special or not).

Print the number of special elements of the given array $ a $ .

For example, if $ n=9 $ and $ a=[3,1,4,1,5,9,2,6,5] $ , then the answer is $ 5 $ :

- $ a_3=4 $ is a special element, since $ a_3=4=a_1+a_2=3+1 $ ;
- $ a_5=5 $ is a special element, since $ a_5=5=a_2+a_3=1+4 $ ;
- $ a_6=9 $ is a special element, since $ a_6=9=a_1+a_2+a_3+a_4=3+1+4+1 $ ;
- $ a_8=6 $ is a special element, since $ a_8=6=a_2+a_3+a_4=1+4+1 $ ;
- $ a_9=5 $ is a special element, since $ a_9=5=a_2+a_3=1+4 $ .

Please note that some of the elements of the array $ a $ may be equal — if several elements are equal and special, then all of them should be counted in the answer.

## 样例 #1

### 输入

```
5
9
3 1 4 1 5 9 2 6 5
3
1 1 2
5
1 1 1 1 1
8
8 7 6 5 4 3 2 1
1
1```

### 输出

```
5
1
0
4
0```

# 题解

## 作者：SpeedStar (赞：4)

### 算法分析
考虑到本题的数据范围比较小，因此我们可以在$O(n^2)$的时间内处理。

首先统计出每个元素出现的次数，然后我们遍历长度至少为2的所有区间段求出所有的区间元素之和。注意到，我们并不需要区间元素和大于$n$，因为$a_i \leqslant n$。因此，如果当前的区间元素和不大于$n$的话则将其出现的次数计入答案，并将其出现的次数初始化为$0$以防止相同的元素出现几次这种情况。


### C++代码
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		vector<int> cnt(n + 1);
		int ans = 0;
		for (auto &it : a) {
			cin >> it;
			++cnt[it];
		}
		for (int l = 0; l < n; ++l) {
			int sum = 0;
			for (int r = l; r < n; ++r) {
				sum += a[r];
				if (l == r) continue;
				if (sum <= n) {
					ans += cnt[sum];
					cnt[sum] = 0;
				}
			}
		} 
		cout << ans << '\n';
	}
	
	return 0;
}
```


---

## 作者：RioFutaba (赞：2)

题目：**[CF1352E](https://www.luogu.com.cn/problem/CF1352E)**

## 思路
使用前缀和。

开一个桶，把 $a$ 所有连续子序列的和都扔进桶里。注意因为题目说明了 $a_i \le n$，所以没有必要记录大于 $n$ 的子段和。

最后检查每一个 $a_i$ 是否在桶里出现过即可。

题目明确说了 $\sum n \le8 \times 10^3$，所以 $O(n^2)$ 的算法是能通过的。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=8e3+5;
int t,n,a[maxn],b[maxn];//b为a的前缀和数组
bool v[maxn];//v[i]表示i是否是a的某一子段和
int main(){
	cin >> t;//多测
	while(t--){
		int cnt=0;
		cin >> n;
		memset(v,0,sizeof(v));//一定要记得清零
		for(int i=1;i<=n;i++){
			cin >> a[i];
			b[i]=a[i]+b[i-1];//前缀和
		}
		for(int l=1;l<=n;l++)
			for(int r=l+1;r<=n;r++)
				if(b[r]-b[l-1]<=n) v[b[r]-b[l-1]]=1;//记录
		for(int i=1;i<=n;i++) if(v[a[i]]) cnt++;
		cout << cnt << endl;
	}
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：2)

## 题解 CF1352E 【Special Elements】

### 题意

+ $n$ 个数 $a$；
+ 求有多少个数可以表示为数组中其他连续数的和；
+ 多组数据，$1\le a\le n\le8000$。

### 做法

最朴素的做法显然是枚举数和区间左右端点，求区间和，判断是否相等，$O(N^4)$，结果不用多说。

前缀和优化，$O(N^3)$，还是过不了。

然后可以想到可以把所有数放在桶里，$O(N^2)$，可过。

但是在 Virtual participation 的时候我想复杂了，看到内存只有 64M，还没有注意到 $a\le n$，以为会 MLE，没勇气写。

然后我想到了枚举每个点，然后双端队列优化枚举区间，时间复杂度也是 $O(N^2)$。

下面放上我 Virtual participation 时写的代码，代码较长，想看简单点的可以找别的题解。

### 代码

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

int arr[8005];

int n;

bool check(int x) {
	int last = 0, sum = 0;
	for (int i = 1; i <= n; ++i) {
		while (sum < x && last < n) {
			sum += arr[++last];
		}
		if (sum == x && last > i) {
			return 1;
		}
		sum -= arr[i];
	}
	return 0;
}

void run() {
	memset(arr, 0, sizeof arr);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &arr[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (check(arr[i])) {
			++ans;
		}
	}
	printf("%d\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

---

## 作者：b6e0_ (赞：2)

打完CF又来写题解啦~求兹磁qwq（第一次AK CF比赛）

[CF题面传送门](https://codeforces.com/contest/1352/problem/E) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1352E) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1352E)

看到这题的空间限制，~~我很紧张~~，觉得这题会卡我半天空间。。。其实一遍通过。

算了一下，$O(n^2\log n)$的时间复杂度过不去。

这种关于区间和的题目，前缀和肯定是要有的。将这个数组里的数都放进一个桶里。然后枚举区间的左右端点，答案累加为这个区间和的数的个数。有两个点需要注意：

1. 判断区间和是否超过$n$（因为区间里的数都在$n$以内），否则要么RE，要么炸空间。

2. 一次累加桶里的某个数后，要记得将桶里的这个数的个数清$0$，否则会重复算。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[8010],tot[8010];//s为前缀和，tot为桶
int main()
{
	int t,n,i,j,x,ans;
	cin>>t;
	while(t--)
	{
		memset(s,0,sizeof s);
		memset(tot,0,sizeof tot);//多测的数组清零不能忘！
		cin>>n;
		for(i=1;i<=n;i++)
		{
			cin>>x;
			tot[x]++;
			s[i]=s[i-1]+x;
		}
		ans=0;
		for(i=0;i<=n;i++)//注意是从0开始
			for(j=i+2;j<=n;j++)//注意是从i+2开始
				if(s[j]-s[i]<=n)
				{
					ans+=tot[s[j]-s[i]];//累加
					tot[s[j]-s[i]]=0;//清零！！！
				}
		cout<<ans<<endl;
	}
	return 0;
}
```
时间复杂度为$O(n^2)$。

---

## 作者：dingcx (赞：1)

~~这可能是这场比赛最难的一道题了~~

## 思路

要求一段区间的和，就想到用**前缀和**。最后要算的是一个数等于一段和，又注意到 $1 \le a_i \le n$，可以想到用**一个桶**装着**在 $[1,n]$ 范围**里所有**前缀和差**（也就是一段区间的和），然后遍历一遍判断有没有统计一下就好了。

为了减少时间和避免桶爆掉，需要在枚举两个前缀和的循环里加一句，**如果前缀和差 $>n$ 就 ```break```**，因为前缀和是**递增**的，越往后差会越大，不可能再 $\le n$。

注意 **```memset```**。

时间复杂度是 $O(tn^2)$ 加优化，~~我也不知道为啥过了~~。

## 代码

这样代码就很好写了（不要只看这里啊）

```cpp
#include<cstdio>
#include<cstring>//用到 memset
using namespace std;
const int MAXN=8010;
int a[MAXN],s[MAXN],t[MAXN];//原数组，前缀和，桶
int read(){//快读
	int num=0,sign=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
	return num*sign;
}
int main(){
	int T=read();
	while(T--){
		memset(t,0,sizeof(t));//清空
		int n=read(),ans=0;
		for(int i=1;i<=n;i++)
			a[i]=read(),s[i]=s[i-1]+a[i];//计算前缀和
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				if(s[j]-s[i-1]>n) break;//判断差，break
				t[s[j]-s[i-1]]++;//记到桶里
			}
		for(int i=1;i<=n;i++)
			if(t[a[i]]) ans++;//有一段区间和满足，统计
		printf("%d\n",ans);
	}
	return 0;//华丽结束
}
```
看我分析那么详细，总得点个赞吧qwq

---

## 作者：do_while_true (赞：1)

给每一个对 $[l,r]$ 的区间和都打上标记，如果 $a_i$ 有标记则答案 $+1$。使用 ```bitset``` 可以达到节省空间的效果。

因为 ``bool`` 一个是占用 $4$ 个字节储存，而 ``bitset`` 只占一个字节，所以能够大大的减少空间的占用。

[$\mathcal{Code}$](https://codeforces.com/contest/1352/submission/79553612)

---

## 作者：ZhaoV1 (赞：0)

# CF1352E Special Elements

### 题目分析
此题可以用前缀和和双指针来解决。 $n$ 的总数（每一轮累加）最高达到 $8000$ ，所以时间上完全没有问题。 $left$ 指向闭合区间左边， $right$ 指向闭合区间右边，在下标为 $index$ 的数的两边分别进行筛选即可得到答案。

\
Code
------------

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,temp,n;
int s[8005];

bool two_points(int left,int right,int top,int target){
	while(left < right && right < top){
		if(s[right] - s[left-1] > target){
			left++;
			if(left == right) right++;
		}
		else if(s[right] - s[left-1] == target) return true;
		else right++;
	}
	return false;
}

bool search(int x,int index){
	if(two_points(1,2,index,x) || two_points(index+1,index+2,n+1,x)) return true;
	else return false;
}

void solve(){
	int ans = 0;
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> temp;
		s[i] = s[i-1] + temp;
	}
	for(int i=1;i<=n;i++){
		if(search(s[i]-s[i-1],i)) ans++;
	}
	cout << ans << '\n';
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

## 作者：Arrtan_73 (赞：0)

# 题解 CF1352E
## 题目大意
- 求数组中有多少数是等于数组中其他连续数的和。

- $0<a_{i}<n<8000$。

## 题目思路&做法
首先我们可以很容易想到用前缀和的方法代表区间，去一个一个枚举是否为特殊值，但是这种做法的复杂度是 $O( n^{3} )$ 级别的，肯定会超时，所以我们还要进行优化与剪枝。我们可以发现 $a$ 数组的每一个元素都是大于 $0$ 的，也就是说前缀和数组是单调不减的。那么如果当前的前缀和超出了阙值 $n$，就得停止，因为接下来的数是都大于 $n$ 的，肯定不符合要求，直接退出循环。但是一试，哎呀，还是可能会超时，但是仔细一看，你会发现循环中某些区间是被多次计算了的，那么我们何不直接把所有符合要求的的可能存起来，直接去查找 $a$ 数组的元素呢？这里就直接用一个桶去装数，再一看，欸，大小最多 $8000$，不会爆，何乐而不为呢？

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long int T, n, d[8005], t[8005];

int main() {
	cin >> T;
	for (int k = 1; k <= T; k++) {
		memset(t, 0, sizeof(t));\\清零一遍，以防重复计算
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> d[i], d[i] += d[i - 1];
		int data = 0;
		for (int i = 1; i <= n - 1; i++)
			for (int j = i + 1; j <= n; j++) {
				int vis = d[j] - d[i - 1];
				if (vis > n)
					break;
				t[vis]++;
			}\\算区间和
		for (int i = 1; i <= n; i++)
			if (t[d[i] - d[i - 1]])
				data++;\\ 判断
		cout << data << endl;
	}
	return 0;
}
```

---

## 作者：小蒟蒻皮皮鱼 (赞：0)

## CF1352E Special Elements

题意：给你$a$数列，让你判断其中的每个元素是否能写成数列中几个连续元素之和，并统计个数。

这道题乍一看维护前缀和，枚举端点查找。$O(n^2*t)$的复杂度，但是一些特性让它的跑不满，就可以过了。

几个非常有意思的数据范围包括：$1\leq n\leq 8000,1\leq a_i \leq n$。

注意到他让你求的并不是任意一个数，而是$a_i$，并且$1\leq a_i \leq n$，也就是说他让你找的数其实只是在一到八千的范围内。对于枚举的$l$，如果$sum[r]-sum[l-1]>8000$，就不需要接着枚举$r$了。

那么处理前缀和，再开8000个桶分别装每一个数据就可以了。

```cpp
for (int l = 1; l < n; l++) 
{
	for (int r = l + 1; r <= n; r ++) 
    {
		int sum = b[r] - b[l - 1];
		if(sum<=n) vis[sum]++;
		else break;
	}
}
```



---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1352E)

首先，明显的，看到`几个连续元素之和`时，第一反应就是前缀和。

然后分析题目可知可以采用枚举区间计算和然后打标记的方式统计个数。

求区间和可以用前缀和优化，那么就剩枚举区间。

枚举区间需要枚举左端点和右端点，计算和可以用前缀和，所以复杂度 $O(n^2)$，可过。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,v[8010]={0};
bool b[8010]={0};
int ans=0;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(register int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			v[i]=v[i-1]+x;
		}
		for(register int l=1;l<=n;l++)
			for(register int r=l+1;r<=n;r++)
				if(v[r]-v[l-1]<=n) b[v[r]-v[l-1]]=1;
		for(register int i=1;i<=n;i++) if(b[v[i]-v[i-1]]) ans++;
		printf("%d\n",ans),ans=0;
		for(register int i=1;i<=n;i++) b[i]=0;
	}
	return 0;
}
```

---

