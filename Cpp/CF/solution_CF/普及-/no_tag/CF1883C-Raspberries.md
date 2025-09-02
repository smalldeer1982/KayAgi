# Raspberries

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ and a number $ k $ ( $ 2 \leq k \leq 5 $ ). In one operation, you can do the following:

- Choose an index $ 1 \leq i \leq n $ ,
- Set $ a_i = a_i + 1 $ .

Find the minimum number of operations needed to make the product of all the numbers in the array $ a_1 \cdot a_2 \cdot \ldots \cdot a_n $ divisible by $ k $ .

## 说明/提示

In the first test case, we need to choose the index $ i = 2 $ twice. After that, the array will be $ a = [7, 5] $ . The product of all the numbers in the array is $ 35 $ .

In the fourth test case, the product of the numbers in the array is $ 120 $ , which is already divisible by $ 5 $ , so no operations are needed.

In the eighth test case, we can perform two operations by choosing $ i = 2 $ and $ i = 3 $ in any order. After that, the array will be $ a = [1, 6, 10] $ . The product of the numbers in the array is $ 60 $ .

## 样例 #1

### 输入

```
15
2 5
7 3
3 3
7 4 1
5 2
9 7 7 3 9
5 5
5 4 1 2 3
7 4
9 5 1 5 9 5 1
3 4
6 3 6
3 4
6 1 5
3 4
1 5 9
4 4
1 4 1 1
3 4
3 5 3
4 5
8 9 9 3
2 5
1 6
2 5
10 10
4 5
1 6 1 1
2 5
7 7```

### 输出

```
2
2
1
0
2
0
1
2
0
1
1
4
0
4
3```

# 题解

## 作者：allen2010 (赞：4)

# 思路

考虑到 $k$ 较小，可以先从 $k$ 入手。

可以发现，当 $k$ 为质数，即 $k = 2,3,5$ 时，只要把 $a$ 中的一个数改成其倍数即可。

当 $k = 4$ 时，分两种情况讨论：

1. 将 $a$ 中两个数分别修改成 $2$ 的倍数。

2. 将 $a$ 中一个数修改成 $4$ 的倍数。

取两种情况最小值即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100007];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		int minn=0xfffffff;
		for(int i=0;i<n;i++) cin>>a[i];
		if(k!=4){
			for(int i=0;i<n;i++)
			{
				int x=a[i];
				minn=min(minn,(x%k!=0?k-x%k:0));
			}
		}else{
           	for(int i=0;i<n;i++)
			{
				int x=a[i];
				minn=min(minn,(x%k!=0?k-x%k:0));
			}
            	int minn1=0xfffffff;
			k=2;
			int id=0;
			for(int i=0;i<n;i++)
			{
				int x=a[i];
				if(minn1>(x%k!=0?k-x%k:0))
				{
					minn1=(x%k!=0?k-x%k:0);
					id=i;
				}
			}
			a[id]=0xfffffff;
			int minn2=0xfffffff;
			for(int i=0;i<n;i++)
			{
				int x=a[i];
				minn2=min(minn2,(x%k!=0?k-x%k:0));
			}
			minn1+=minn2;
        	minn=min(minn1,minn);
		}
     	ansok:
			cout<<minn<<endl;
	}
	return 0;
}
```


---

## 作者：Milthm (赞：3)

首先发现 $2\le k\le5$，然后发现如果 $k$ 是质数，则只要找每个 $a_i$，它加多少能变成 $k$ 的倍数，然后取最小值即可。

发现 $2\sim5$ 只有 $4$ 不是质数，所以特殊讨论 $k=4$。这种情况下可以先看 $a$ 序列所有数的因子 $2$ 个数之和。如果大于等于 $2$ 个则不需要操作，如果是 $1$ 个则只需要把一个数从奇数改成偶数，答案是 $1$。如果是 $0$ 个则再分类讨论，如果有加 $1$ 就能变成 $4$ 的倍数的，答案即为 $1$，否则为 $2$。

### AC code

```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
int T,n,k,a[200005],ans; 
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		ans=1e9;
		for(int i=1;i<=n;++i)scanf("%d",&a[i]);
		if(k!=4){
			for(int i=1;i<=n;++i){
				int cnt=0;
				while(a[i]%k!=0)++a[i],++cnt;
				ans=min(ans,cnt);
			}
			cout<<ans<<'\n';
		}
		else{
			int cnt=0;
			for(int i=1;i<=n;++i){
				int p=a[i];
				while(p%2==0){
					++cnt;p/=2;
				}
			}
			if(cnt>=2)cout<<"0\n";
			else if(cnt==1)cout<<"1\n";
			else{
				for(int i=1;i<=n;++i){
					if(a[i]%4==3){
						cnt=1;break;
					}
				} 
				if(cnt)cout<<"1\n";
				else cout<<"2\n";
			}
		}
	}
	return 0;
}

```


---

## 作者：GenesisCrystal (赞：2)

[本文章与博客园同步发布](https://www.cnblogs.com/sbsclc/p/17889258.html)
[洛谷传送门](https://www.luogu.com.cn/problem/CF1883C)
[CF传送门](http://codeforces.com/problemset/problem/1883/C)

## 思路

首先， 一眼丁真， 题目中说， 要 $\prod \limits_{i=1}^n a_i \bmod k = 0$, 即 $a_1$ 至 $a_n$ 中有能够 $\bmod k$ 为零的， 则遍历一遍数组， 答案取 $ \min \sum \limits_{i=1}^{n} (k - a[i] \bmod k)$。

当然， 这是错误的， 当 $k$ 为 $4$ 时， 它还可以变成 $k = 2 \times 2$， 所以该怎么办呢？

因为 $1 \le k \le 5$， 所以我们可以特判。令 $c = \sum \limits_{i=1}^{n}a_i \bmod 2$， 则答案为 $\max(0, 2-c)$。

思路知道了后， 代码就很简单了， 在此不放。

---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1883C) & [CF 传送门](http://codeforces.com/problemset/problem/1883/C)
# 思路
一看数据范围，$2\le k\le5$，其中只有 $4$ 是合数，其它都是质数。对于除了 $4$ 的其它数，我们只需要判断哪个 $a_i$ 最快能变成 $k$ 的倍数即可。而对于 $k=4$ 的情况，我们还需要考虑两个 $2$ 的倍数之积也是 $4$ 的倍数。我们把两种情况取一个 $\min$ 即可。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, k, minx, a[100005], min1, min2;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> k;
		minx = 10; //多组数据要初始化
		for (int i = 0; i < n; ++ i)
			cin >> a[i], minx = min (minx, k - 1 - (a[i] - 1) % k);
		if (k == 4) { //特判 k=4
			min1 = min2 = 10; //要有两个 min 变量，min1 是最小，min2 是次小
			for (int i = 0; i < n; ++ i) {
				k = a[i] & 1;
				if (k < min1)
					min2 = min1, min1 = k;
				else if (k < min2)
					min2 = k;
			}
			minx = min (minx, min1 + min2); //注意要取min
		}
		cout << minx << '\n';
	}
	return 0;
}
```

---

## 作者：FireRain (赞：0)

# 思路

首先发现当 $k$ 为质数时，如果有一个数 $a_i$ 满足 $a_i \bmod k = 0$，那么无需操作；如果没有，则需要将某一个 $a_i$ 变化到 $k$ 的倍数，那么直接选取操作数量最少的即可。

然后考虑 $k$ 不为质数怎么做。在本题中，$k$ 不为质数，只存在于 $k = 4$ 的情况，那么统计 $t$ 表示所有 $a_i$ 的 $2$ 的因子数量。简单分讨一下：

1. $t \geq 2$，无需修改。

2. $t = 1$，因为 $n > 1$，所以修改一个奇数 $a_i$ 即可满足条件。

3. $t = 0$，首先需要看是否有 $a_i$ 能加 $1$ 变为 $4$ 的倍数，如果可以说明只需操作一次；反之需要操作两次。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10,inf = 1e9 + 10;
int T,n,k;
int arr[N],val[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int get(int a,int b){
	if (a % b == 0) return 0;
	return b - a % b;
}

inline void solve(){
	n = read();
	k = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	if (k == 2 || k == 3 || k == 5){
		int Min = inf;
		bool falg = false;
		for (re int i = 1;i <= n;i++) Min = min(Min,get(arr[i],k));
		for (re int i = 1;i <= n;i++){
			if (arr[i] % k == 0) falg = true;
		}
		if (falg) puts("0");
		else printf("%d\n",Min);
	}
	else{
		int num = 0;
		for (re int i = 1;i <= n;i++){
			while (arr[i] % 2 == 0){
				num++;
				arr[i] /= 2;
			}
		}
		if (num >= 2) puts("0");
		else if (num == 1) puts("1");
		else{
			int res = 0;
			for (re int i = 1;i <= n;i++){
				if ((arr[i] + 1) % 4 == 0) res++;
			}
			if (res) puts("1");
			else puts("2");
		}
	}
}

int main(){
	T = read();
	while (T--) solve();
	return 0;
}
```

---

## 作者：Falling_Sakura (赞：0)

# 思路

我们观察到 $2\le k \le 5$ 那么 $k$ 的取值除了 $4$ 就一定是质数，也就是说序列中一定要有一个数为 $k$，所以我们找到最接近 $k$ 的倍数的一个数，操作它即可。

那么怎么找最接近 $k$ 的倍数的数呢？模 $k$ 的值最大即可。

假如原来就有 $k$ 了，那就不用操作了。

至于 $k=4$ 的情况，特判一下两个 $2$ 的即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 8;

int a[N];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        // k <= 5
        sort(a + 1, a + 1 + n);
        int maxn = -1;
        if(k == 4)
        {
            int cnt = 0;
            bool bj = false;
            for(int i = 1; i <= n; i++)
            {
                if(a[i] % 4 == 0)
                {
                    bj = true;
                    cout << 0 << endl;
                    break;
                }
                if(a[i] % 2 == 0) cnt++;
                maxn = max(maxn, a[i] % 4);
            }
            if(bj) continue;
            if(cnt >= 2)
            {
                cout << 0 << endl;
            }
            else if(cnt == 1) cout << 1 << endl;
            else cout << min(4 - maxn, 2) << endl;
            continue;
        }
        bool bj = false;
        for(int i = 1; i <= n; i++)
        {
            if(a[i] % k == 0)
            {
                bj = true;
                cout << 0 << endl;
                break;
            }
            maxn = max(maxn, a[i] % k);
        }
        if(bj) continue;
        cout << k - maxn << endl;
    }
    return 0;
}
```

---

## 作者：SCAR_L (赞：0)

我当时参加比赛时看到这道题，感觉好难呀（要分解质因数），结果后面看了一圈后发现后面的更难 qwq。             
于是我就又读了边题，发现数据范围中有一项十分特别：$2 \le k \le 5$！

于是我就将 $k$ 分成两种情况进行讨论：
1. $k$ 为质数，即 $k = 2,3,5$ 时；要想让积为 $k$ 的倍数，只能让 $a$ 中含有 $k$ 的倍数。
	- 找出对 $k$ 取余的最大值 $mx = \max ( a_i \! \! \!\mod k) $（要是有 $k$ 的倍数就直接输出 $0$），输出 $k - mx$。
2. $k$ 为合数，即 $k = 4$ 时；在 $a$ 中，有以下几种情况：
	- 若有两个 $2$ 的倍数或一个 $4$ 的倍数，不需任何更改即可满足条件，输出 $0$。
	- 若只有一个 $2$ 的倍数，则将其他任意一项加一即可，输出 $1$。
	- 若 $\exists\ a_i \equiv 3 \pmod 4$，则将其加一即可满足条件，输出 $1$。
	- 若没有 $2$ 的倍数，则将其他任意两项加有一项加一即可，输出 $2$。

有了以上分析，我们就可以较为轻松的写出代码：
```cpp
#include <iostream>
using namespace std;
int a[1000005];
int n, k;
void work1() // 处理情况一（即k为1, 3, 5）
{
    int mx = 0;
    for(int i = 1; i <= n; i++)
		if(a[i] % k == 0)	// 找到k的倍数了
		{
			cout << 0 << endl;
			return ;
		}
		else mx = max(mx, a[i] % k);
	cout << k - mx << endl;
}
void work2() // 处理情况二（即k为4）
{
    int cnt = 0;	// 因子2的个数
    bool flag = 0;	// 是否有除以4余3的
    for(int i = 1; i <= n; i++)
    {
        if(a[i] % 4 == 3) flag = true;
        if(a[i] % 4 == 0) cnt += 2;
        else if(a[i] % 2 == 0) cnt++;
    }
    if(cnt >= 2) cout << 0 << endl;
    else if(flag || cnt == 1) cout << 1 << endl;
    else cout << 2 << endl;

} 
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n >> k;
		for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
		if(k == 2 || k == 3 || k == 5) work1();
        else work2();
	}
	return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

最开始晃眼一看，感觉很难，仔细一读题，哦，原来 $k\in [2,5]$ 啊。

首先如果 $k$ 是质数，也就是 $k$ 不等于 $4$ 的情况，必须要有一个数是 $k$ 的倍数，那么计算每个数需要的操作数，取最小即可。

如果 $k$ 不是质数，也就是 $k$ 等于 $4$ 的情况，要么是一个数是 $4$ 的倍数，要么有两个数是 $2$ 的倍数，那么取最小即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a,ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m),ans=m+2;
		if(m==4)//当时想复杂了，所以写得又臭又长
		{
			ans=2;
			if(n==1)
			{
				scanf("%d",&a);
				printf("%d\n",(a%4==0)?0:(m-a%m));
			}
			else
			{
				int num=4;
				for(int i=1;i<=n;++i)
				{
					scanf("%d",&a),ans-=(a%4==0)?2:(a%2==0)?1:0;
					if(a%4==3) num=1;
					if(a%4==2) num=min(num,2);
				}
				printf("%d\n",min(num,max(ans,0)));
			}
			continue;
		}
		for(int i=1;i<=n;++i) scanf("%d",&a),ans=min(ans,(a%m==0)?0:(m-a%m));
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Starrykiller (赞：0)


## Statement

给定数列 $a_1,a_2,\cdots,a_n$ 和整数 $k$，每次操作选择任意一个 $a_u$ 加上一。问至少操作多少次后，有 $k\mid \prod_{i=1}^{n}a_i$。

**保证 $\boldsymbol{2\leq k \leq 5}$**。

## Solution

我们讨论 $k$ 为素数（$k=2,3,5$）时的情况。

显然，若 $\exists i\in a_i$，有 $k \mid a_i$，则答案显然为 $0$。

否则将 $a_i$ 变为可被 $k$ 整除需要 $k-a_i \bmod k$ 次。所以答案为 $\displaystyle \min _{1\leq i\leq n} (k-a_i \bmod k)$。

现在我们讨论 $k=4$ 的情况。

对于 $\exists i\in a_i$，有 $4 \mid a_i$ 的情况，是 trivial 的；但是对于 $k=4=2\times 2$ 的情况，还需要注意：若存在两个偶数，则答案也为 0。

如果存在正好一个偶数，则答案为 1，因为只需要再使一个 $a_i$ 变为偶数即可；否则（若没有偶数）答案为 $2$。

时间复杂度 $\mathcal{O}(\sum n)$。

完整代码见[此处](https://www.luogu.com.cn/paste/jau45ype)。

那么，如果不限定 $k$ 的范围，或者说，$2\leq k \leq \max_{i=1}^{n} a_i$，本题是否可做？欢迎一起来探讨下（什么）


---

## 作者：Gyc_Fisher (赞：0)

# CF1883C Raspberries 题解

题目链接：[Raspberries](https://www.luogu.com.cn/problem/CF1883C)

我们发现如果 $k$ 是一个质数，那我们必须凑出其倍数。若是一个合数，我们需要凑出一对可以组成它的因数。

在本题 $k$ 的范围中：$2$，$3$，$5$ 均为质数，只有 $4$ 为合数，那我们只用对 $4$ 进行特判即可。

对于 $k$ 的所有情况，若最开始数组中就有其倍数，或者最开始的乘积已经是其倍数，则不需要进行任何操作（即答案为 $0$）；否则，针对质数，只用遍历一遍数组，看哪个数可以通过加上较少的值去凑成 $k$ 的倍数，答案也就是这个较小的值。针对唯一的合数 $4$，我们发现其只由两个 $2$ 组成，那我们只需要在上述统计质数的方法上，多统计 $2$ 出现的次数，若为一次答案为 $1$，若为零次答案为 $2$，出现两次及以上，此时答案为 $0$，最后将在两种统计的答案中去最小值作为答案即可。

附上代码：

```cpp
#include <bits/stdc++.h>
#define MAXN 200010
using namespace std;
int t;
int n,k;
int a[MAXN];
int main(){
	scanf("%d",&t);
	while(t--){
		int ans=0x3f3f3f3f;
		scanf("%d%d",&n,&k);
		bool fl=false;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]%k==0) fl=true;
		}
		if(fl){
			puts("0");
			continue;
		}
		int ret=0;
		for(int i=1;i<=n;i++){
			if(a[i]%2==0) ret++;
			int num=a[i];
			num=((num+k)/k)*k-num;
			ans=min(ans,num);
		}
		if(k==4){
			if(ret==1) ans=min(ans,1);
			else if(ret>=2) ans=0;
			else ans=min(ans,2);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```





---

