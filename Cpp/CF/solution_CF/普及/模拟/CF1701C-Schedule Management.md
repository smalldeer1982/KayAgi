# Schedule Management

## 题目描述

## 题意简述
有 $n$ 个工人和 $m$ 个任务，每个任务都有且仅有一个工人擅长做，如果让擅长做的工人去做，那么要花一个单位时间，否则要花两个单位时间。请问完成所有的任务至少要花多少时间。

注意：每项工作只能由一个工人完成，不能合作完成。

## 样例 #1

### 输入

```
4
2 4
1 2 1 2
2 4
1 1 1 1
5 5
5 1 3 2 4
1 1
1```

### 输出

```
2
3
1
1```

# 题解

## 作者：qwq___qaq (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1701C)

首先，求出每个人可以用 $1$ 完成的数量，记作 $c$。

然后再开桶维护每个 $c$ 的数量。

记 $l$、$r$ 为桶中 $c$ 的最大、最小值。

然后，若 $r+2<l$，那说明删去一个 $l$，肯定不会使答案更劣，所以，我们把 $l$ 的工作转移到 $r$ 上，注意如果没有 $l$、$r$ 要转移。

对于 $l$、$r$，每个扫描一次，时间复杂度 $O(m)$。

---

## 作者：郑朝曦zzx (赞：4)

# 解题思路
这次的 C 题比较简单，二分答案即可，令 $x$ 表示二分的时间。

对于 check 函数，我们先记录每个工人所擅长的工作数量 $cnt_i$。

然后我们贪心，如果有擅长的工作就先去做，经分析有以下两种情况。

- 如果 $x \le cnt_i$，那么他能完成 $x$ 项工作。

- 否则，就先干擅长的 $cnt_i$ 项，后干不擅长的 $\lfloor\frac{x - cnt_i}{2}\rfloor$。

最后我们把干完的工作数量和 $m$ 比较即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, ans;
int p[200010], cnt[200010];
bool check(int x)
{
	long long sum = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (cnt[i] >= x) sum += x;
		else sum += cnt[i] + (x - cnt[i]) / 2;
	}
	return (sum >= m);
}
int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &m);
		memset(p, 0, sizeof(p));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= m; ++i)
		{
			scanf("%d", &p[i]);
			cnt[p[i]]++;
		}
		int l = 1, r = 2 * m;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (check(mid))
				ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：happybob (赞：1)

## 做法

考虑二分答案，显然要二分完成所有任务的时间。

对于完成所有任务的时间 $x$，如何判断在 $x$ 分钟内，所有任务可以做完呢？显然对于每一个工人所熟练的任务都有若干个，假设第 $i$ 个工人所熟练的任务有 $c_i$ 个，对于 $c_i < x$，第 $i$ 个工人做完之后，还会继续做 $\lfloor \dfrac{x - c_i}{2} \rfloor$ 个工作，而对于 $c_i > x$，这个工人会一直做下去，直到 $x$ 分钟结束。

所以只需要判断这 $x$ 分钟内，每个人多出的工作量，即对比 $\sum c_i - x$ 与每个人能额外做的工作量，即 $\sum \lfloor \dfrac{(x - c_i)}{2} \rfloor$ 的大小即可。

代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

#define int long long

const int N = 2e5 + 5;

int t, n, m, a[N];

inline bool check(int x)
{
	int c1 = 0, c2 = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] < x) c1 += (x - a[i]) / 2;
		else c2 += (a[i] - x);
	}
	return c1 >= c2;
}

signed main()
{
	scanf("%lld", &t);
	while (t--)
	{
		scanf("%lld%lld", &n, &m);
		for (int i = 1; i <= m; i++)
		{
			int x;
			scanf("%lld", &x);
			a[x]++;
		}
		int l = 0, r = 2 * m + 1;
		while (l + 1 < r)
		{
			int mid = (l + r) >> 1;
			if (check(mid))
			{
				r = mid;
			}
			else l = mid;
		}
		printf("%lld\n", r);
		for (int i = 1; i <= n; i++) a[i] = 0;
	}
	return 0;
}
```


---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1Nf4y1o7Cx)

### 2 思路

可以二分需要多久时间。

首先我们设 $a[i]$ 为第 $i$ 个工人熟练的工作数量 **（注意这与题目不一样）**。

我们如何判断工人们花 $x$ 小时能不能做完呢？

很明显，各位工人应最先完成自己熟练的工作。

设 $cnt$ 为剩余多少工作。

首先计算工人做完自己熟练的工作后还剩多少工作。对于每个 $i(1\le i\le n)$，如果 $a[i]>x$，那么 $cnt$ 增加 $a[i]-x$。

然后，如果 $a[i]\le x$，$cnt$ 减少 $\lfloor\dfrac{a[i]-x}{2}\rfloor$，表示这个工人有空闲时间可以干别人的活。

最后，如果 $cnt\le0$，说明所有的工作已经完成，否则没有完成。

二分得出答案即可。

### 3 代码与记录

```cpp
//Luogu submission
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
int m;
int a[max_n+2];//每个工人会多少个工作
int ans;
bool check(int x){
	int cnt=0;
	for(int i=1;i<=n;++i){
		if(a[i]>x)cnt+=a[i]-x;
	}
	for(int i=1;i<=n;++i){
		if(a[i]<=x)cnt-=((x-a[i])>>1);
		if(cnt<=0)return true;
	}
	return false;;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1701C_2.in","r",stdin);
	freopen("CF1701C_2.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)a[i]=0;
		for(int i=1,x;i<=m;++i){
			scanf("%d",&x);
			++a[x];
		}
		ans=0;
		for(int l=1,r=max_n<<2,mid;l<=r;){
			mid=(l+r)>>1;
			if(check(mid)){
				r=mid-1;
				ans=mid;
			}
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/78922244)

By **dengziyue**

---

## 作者：Gao_yc (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1701C)

记录下每个人精通多少种任务，二分答案，注意二分的上界不用开太大，上界开到 $m$ 然后 WA 的可能是因为 check 函数中的 $ans$ 爆 int 了。

check 函数中计算每个工人在一定时间内最多能完成多少任务。
由于每个人精通的任务互不相同，故每个人完成的任务数互不影响，直接判断累计完成的任务数是否大于等于 $m$ 就完事了。


时间复杂度 $\mathcal{O}(m \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int tt,n,m,a,t[N];
bool check(int x)
{
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		if(x<=t[i]) ans+=x;
		else ans+=(t[i]+(x-t[i])/2);
	}
	return ans>=m;
}
int main()
{
    scanf("%d",&tt);
    while(tt--)
    {
    	scanf("%d%d",&n,&m);
    	for(int i=1;i<=m;++i) scanf("%d",&a),t[a]++;
    	int l=1,r=(m/n+1)*2;
    	while(l<r)
    	{
    		int mid=(l+r)>>1;
    		if(check(mid)) r=mid;
    		else l=mid+1;
		}
		printf("%d\n",l);
		for(int i=1;i<=n;++i) t[i]=0;
	}
    return 0;
}
```


---

## 作者：GI录像机 (赞：0)

## 思路：

下文中一轮表示一小时。

由于每个任务只有一个工人精通，而任务顺序无关紧要，我们可以将工人按精通的任务数量排序。然后模拟每一轮做任务，我们要确保每一个人都有任务做。因为让一个没有任务的人来做多的任务是一定不比让精通此任务的人下一轮来做更劣（因为 $1+1=2$），这时我们排序的优势就体现出来了，我们可以保证在没有精通任务做的人一定在做这一轮已经不能只花 $1$ 轮就做好的任务，因为还有精通任务的人一定比他先开始做。具体实现中我们不需要考虑哪个工人哪一轮做了什么任务，只需要给计数器添加一就行了。

可以桶排做到线性，但我太懒了用了 sort。

可能讲得不是很清楚，请配合代码食用。

## 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10;
int t = read(), n, m, a[N], b[N];
bool cmp(int x, int y) {
	return x > y;
}
signed main() {
	while (t--) {
		for (int i = 1; i <= n; i++)a[i] = b[i] = 0;
		int tot = 0, tim = 0;
		n = read();
		m = read();
		for (int i = 1; i <= m; i++)a[read()]++;
		sort(a + 1, a + n + 1, cmp);
		while (tot < m) {
			tim++;
			for (int i = 1; i <= n; i++) {
				if (a[i]){
					tot++;
					a[i]--;
				}
				else if (!b[i]) {
					if (tot < m)b[i] = 1;
					tot++;
				} else b[i] = 0;
			}
		}
		for (int i = 1; i <= n; i++)
			if (b[i]) {
				tim++;
				break;
			}
		write(tim);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

典型的二分。

首先，我们通过二分，假定一个工人完成任务的时间。那么如何验证在这个时间之内工人是否可以完成工作呢？

我们可以发现，每一个工作，都一定有且只有一个工人熟练。

那么，我们可以记录这个工人熟练多少个工作。

接着，在验证时遍历所有工人。如果这个工人熟练的工作小于假定的完成任务的时间，就将剩余的工作交给他。否则，这个工人做不完的工作就交给其他工人的空闲时间去做。

### 二、代码

```
#include<cstdio>
using namespace std;
#define int long long//不开long long见祖宗
int t;
int n,m;
int a[200005];
bool check(int x)
{
	int last=0;//空闲的时间足够做多少不熟练的工作。
	for(int i=1;i<=n;i++)
	{
		if(a[i]<=x)//有空闲时间
		{
			last+=(x-a[i])/2;//思考：为什么要除以二？
		}
		else
		{
			last-=(a[i]-x);//将自己的工作交给其他工人。
		}
	}
	return last>=0;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)
		{
			a[i]=0;
		}
		for(int i=1;i<=m;i++)
		{
			int x;
			scanf("%lld",&x);
			a[x]++;
		}
		int ans=400005;
		int l=0,r=400005;
		while(l<=r)//标准二分。
		{
			int mid=(l+r)>>1;
			if(check(mid))
			{
				ans=mid;
				r=mid-1;
			}
			else
			{
				l=mid+1;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

### 三、思考题

如果一个工人，空闲了 $5$ 个小时。那么，他只能做 $2$ 个他不熟悉的工作，因为一个工作只能由一个工人去做。

所以，除以二的向下取整，是为了舍弃那多余的一分钟。

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1701C)

赛时没开 long long，寄！！！！！！！

注意到每个任务最多只有一个人精通，所以显然大家都做自己精通的不会发生冲突，于是可以直接大力贪心。

然后你当然可以维护一个堆或者 set 啥的去做，但是细节比较多，不太好写。

考虑构造出答案并不好做，但是判断这个答案能不能被构造出很好做。并且答案具有单调性，考虑一种比较好写的二分。

考虑检验答案是否合法怎么做。

显然对于给定的答案 $s$，记 $t_i$ 表示每个人精通的任务数，对于 $t_i \ge s$ 的人，他们能做 $s$ 个精通的任务，其他人只能做 $t_i$ 个任务，然后剩下的时间可以做 $\left\lfloor\dfrac{s-t_i}{2}\right\rfloor$ 个任务。

然后每个 $t_i \ge s$ 的人会剩下 $t_i-s$ 个任务，每个 $t_i<s$ 的人能多做 $\left\lfloor\dfrac{s-t_i}{2}\right\rfloor$ 个任务，比较一下能不能做完即可。

时间复杂度 $O(n \log m)$。

提示：不开 long long 见祖宗。

---

