# Make Equal

## 题目描述

There are $ n $ containers of water lined up, numbered from left to right from $ 1 $ to $ n $ . Each container can hold any amount of water; initially, the $ i $ -th container contains $ a_i $ units of water. The sum of $ a_i $ is divisible by $ n $ .

You can apply the following operation any (possibly zero) number of times: pour any amount of water from the $ i $ -th container to the $ j $ -th container, where $ i $ must be less than $ j $ (i.e. $ i<j $ ). Any index can be chosen as $ i $ or $ j $ any number of times.

Determine whether it is possible to make the amount of water in all containers the same using this operation.

## 说明/提示

In the third test case of the example ( $ a=[4, 5, 2, 1, 3] $ ), you can proceed as follows:

- pour $ 1 $ unit of water from the first vessel to the fourth, then $ a=[3, 5, 2, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the third, then $ a=[3, 4, 3, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the fourth, then $ a=[3, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
6
1
43
2
1 3
5
4 5 2 1 3
3
1 2 3
7
4 5 5 0 6 4 4
7
6 5 5 1 3 4 4```

### 输出

```
YES
NO
YES
NO
NO
YES```

# 题解

## 作者：RyanLi (赞：4)

传送门：洛谷 [Make Equal](https://www.luogu.com.cn/problem/CF1931B) | Codeforces [B. Make Equal](https://codeforces.com/contest/1931/problem/B)

更佳的阅读体验：[CF1931B 题解](https://blog.ryanli.top/index.php/archives/33/)

---

**简要题意**：有 $n$ 个水桶，每个水桶最初包含 $a_i$ 单位的水。可以从前面的水桶向后面的水桶倒水，求是否可以使所有桶里的水量相等。

首先应当求出每个水桶里最终会得到多少水。在输入时统计总的水量（即 $\sum a_i$），然后除以 $n$ 即可。

遍历整个序列，可以想到，如果当前水桶里的水比最终应该得到的水多，那么就可以把多的这部分倒出来；如果当前水桶里的水比最终应该得到的水少，那么就把先前倒出来的水倒进这个水桶里。

我们维护这个“倒出来的水”。如果这部分水变为负数，也就意味着出现了水不够用的情况。因此，如果“倒出来的水”在遍历整个序列的过程中一直保持非负，则表明这个序列合法。

```cpp
#include <iostream>
using namespace std;
using ll = long long;

const int N = 2e5 + 10;
int t, n, a[N], diff;  // diff 表示“倒出来的水”
ll aver;  // 每个水桶分到的水
bool flag;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        aver = diff = 0, flag = false;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i], aver += a[i];
        aver /= n;
        for (int i = 1; i <= n; ++i) {
            diff += a[i] - aver;
            if (diff < 0) flag = true;
        } cout << (flag ? "NO\n" : "YES\n");
    } return 0;
}
```



---

## 作者：Eason_cyx (赞：1)

根据题目的限制，如果某一杯水未达到平均值，只能从前面的水杯多出来的倒。所以我们维护一个 $sum$，表示当前水杯之前所有多出来的水剩下多少。如果当前水量加上这个值仍然小于平均值，那么就无法完成这个目标。到末尾时，如果 $sum$ 刚好为 $0$，那么就可以达成目标。

时间复杂度 $O(tn)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005],d[200005];
int main() {
	int t; cin >> t;
	while(t--) {
		int n,sum = 0; cin >> n;
		for(int i = 1;i <= n;i++) {
			cin >> a[i];
			sum += a[i];
		}
		int pot = sum / n;
		for(int i = 1;i <= n;i++) {
			d[i] = a[i] - pot;
			// cout << d[i] << " \n"[i == n];
		}
		int psts = 0;
		bool flag = true;
		for(int i = 1;i <= n;i++) {
			if(d[i] == 0) continue;
			else if(d[i] < 0) {
				if(psts < abs(d[i])) {
					flag = false;
					break;
				}
				psts -= abs(d[i]);
			}
			else {
				psts += d[i];
			}
		}
		if(!flag || psts != 0) cout << "NO\n";
		else cout << "YES\n";
	}
	return 0;
}
```

[AC Record](https://codeforces.com/contest/1931/submission/246138437)

---

## 作者：SamHJD (赞：1)

## Make Equal

### Description

有 $n$ 个容器，第 $i$ 个容器中盛有 $a_i$ 升水，保证 $a_i$ 的和 $sum$ 是 $n$ 的倍数。你可以选 $1\le i<j\le n$，并将 $i$ 中的一部分水倒入 $j$。问是否能使每个容器中的水体积相同。

### Solution

从 $1$ 循环至 $n$，设一个临时容器存储多出来的水。若当前容器水量多于 $\dfrac{sum}{n}$，则将多出来的那部分放到临时容器中，否则用临时容器中的水补全，若不能补全则不能满足要求。

### [code](https://codeforces.com/contest/1931/submission/246350325)

---

## 作者：__O_v_O__ (赞：0)

首先我们注意到，水只能从前往后倒，且最终目标水量是一定的。

由此我们能推出：如果一瓶水比目标水量高，那么它必须把多余的水向后倒；而如果后面达到目标需要的总水量少于当前瓶子多余的水量，当前瓶子就不可能达到目标，则无解。

所以我们得到做法：定义一个变量记录现在这瓶水后面共需的水量，并从后向前遍历每一瓶水，有两种情况：

1. 这瓶水水量低于目标。此时变量增加这瓶水需要的水量。

2. 这瓶水水量高于目标。此时如果它多余的水量大于变量，则无解；否则变量减去它多余的水量。

目标水量计算很简单，相信大家一定会。

**AC code:**
```cpp
#include<bits/extc++.h>
using namespace std;
#define BTS 0
#define STB 1
#define afor(i,n,m,dir) for(int i=n;dir?i<=m:i>=m;dir?i++:i--)
#define int long long
int t,n,a[200001],sum,now,fl;//now:记录当前需求的变量，sum:目标水量
signed main(){
	ios::sync_with_stdio(0),cin>>t;
	afor(i,1,t,STB){
		cin>>n,sum=0;//清空
		afor(j,1,n,STB)cin>>a[j],sum+=a[j];
		sum/=n,now=0,fl=true;//计算目标水量
		afor(j,n,1,BTS){
			if(a[j]==sum)continue;
			if(a[j]>sum){
				if(a[j]-sum>now){fl=false;break;}
				else now-=(a[j]-sum);
			}else now+=(sum-a[j]);
		}
		if(fl)cout<<"Yes\n";
		else cout<<"No\n";
	}return 0;
}
```

---

## 作者：LegendaryGrandmaster (赞：0)

由于有解情况下最终每个容器的水量都会相同，所以先求出每个容器水量之和求平均值便是每个容器的目标水量。

因为只能编号小的容器倒水给编号大的容器，所以我们可以依次记录当前水量与目标数量的差值，当为负数时，代表编号较小的容器需要水，而编号较大的容器不能给其倒水，所以输出 `NO`。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void fast()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
}
const int N=2e5+10;
int a[N];
signed main()
{
	fast();
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int c=0;
		for(int i=1;i<=n;i++)cin>>a[i],c+=a[i];
		c/=n;
		bool ok=1;
		int ans=0;
		for(int i=1;i<=n;i++){
			ans+=a[i]-c;
			if(ans<0){
				ok=0;
				break;
			}
		}
		cout<<(ok?"yes":"no")<<'\n';
	}
}
```

---

## 作者：无名之雾 (赞：0)

# Make Equal 题解

~~超级大水题，赛时还挂了一发，悲。~~

## 题意

给定你一个数组 $a$ 表示 $n$ 个水杯中水的数量，你可以将 $a_i$ 中的任意的水量 $x$ 转移到 $a_j$，$i<j$ 问可不可以让所有水杯中的水数量相同。

## 思路

因为我们的操作只能由前向后转移，所以我们只需要倒着扫一遍，判断这一段的总和的平均数是否大于期望平均数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
signed main(){
	int t=read();
	while(t--){
		int n=read(),cnt=0;
		for(int i=1;i<=n;i++)a[i]=read(),cnt+=a[i];
		cnt/=n;
		if(n==1){
			puts("yes");
			continue;
		}
		int qujian=0,flag=0;
		for(int i=n;i>=1;i--){
			qujian+=a[i];
			double qwq=1.0*qujian/(n-i+1);
			if(qwq>cnt){
				flag=1;
				break;
			}
		}
		if(flag)puts("no");
		else puts("YeS"); 
	}
	return 0;
}

```

---

## 作者：Shadow_T (赞：0)

### 题目大意

每次操作可以选择 $a_i$ 和 $a_j$ 还有一个整数 $k$ 且满足 $i<j$，$a_i,a_j \leq k$，使 $a_i$ 减 $k$，$a_j$ 加 $k$。求是否可以通过任意次操作使 $a$ 序列元素全部相等。

### 解法分析

首先求出 $a$ 的平均值 $p$，即为每个 $a_i$ 应该有的值。

然后 $i$ 从 $1$ 开始，进行一下操作：

- 若 $a_i>p$ 则将 $a_i$ 多出来的部分存入“仓库”。

- 若 $a_i<p$ 则将“库存”取出修补 $a_i$，若“库存”不够，则无法成功，直接输出 `No`。

最后如果成功了，很明显所有小于 $p$ 的 $a_i$ 都被补平了，所有大于 $p$ 的 $a_i$ 就放入库存。最后的库存不会有剩余。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
int a[maxn];
void solve()
{
	int n;
	cin>>n;
	int sum=0;
	for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]),sum+=a[i];
	sum/=n;
	int d=0;
	for(int i=1;i<=n;i++)
	if(a[i]>sum)
	{
		d+=(a[i]-sum);
		a[i]=sum;
	}
	else if(a[i]<sum)
	{
		int y=a[i];
		a[i]+=d;
		a[i]=(a[i]<sum?a[i]:sum);
		d-=(a[i]-y);
		if(a[i]<sum)
		{
			puts("No");
			return;
		}
	}
	if(d>0) puts("No");
	else puts("Yes");
}
signed main()
{
	int t;
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：__Dist__ (赞：0)

显然，最终每个容器里的水量都要达到 $\frac{(\sum_{i = 1}^{n}a_i)}{n}$。

记 $p = \frac{(\sum_{i = 1}^{n}a_i)}{n}$，$now$ 为当前多出来的水量。

分两种情况：

1. 如果 $a_i > p$，那么多出来的水肯定要加到右边的容器里。$now \gets now + a_i - p$；

2. 如果 $a_i < p$，那么它肯定需要左边多出来的水加到里边。所以如果 $now < p - a_i$，那么水不够加，无法满足要求，输出 `No`；否则，就把多出来的水的一部分加入这个容器，$now \gets now - p + a_i$。

若最后所有的容器里装的水都满足要求，输出 `Yes`。

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 2e5 + 5;
int n;
ll a[MAXN];

void solve() {
	cin >> n;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	int now = 0;
	for (int i = 1; i <= n; i++) {
		if(a[i] < sum / n) {
			if(now < sum / n - a[i]) {
				puts("NO");
				return;
			}
			else {
				now -= sum / n - a[i];
			}
		}
		else {
			now += a[i] - sum / n;
		}
	}
	puts("YES");
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

考虑每个位置都是要满足值为 $\dfrac{\sum a}{n}$ 的，那么我们从前往后扫一遍，当前位置如果不够那就没办法了，否则就把多出来的给到下一位去，这样可以保证如果可行那一定是可以成功分完的。

```cpp
void solve() {
	cin >> n;
	int sum = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
	sum /= n;
	for (int i = 1; i <= n; i++) {
		if (a[i] < sum) {
			cout << "No\n";
			return;
		}
		a[i + 1] += a[i] - sum;
	}
	cout << "Yes\n";
}
 
```

---

## 作者：2021sunzishan (赞：0)

## 题目大意：
给定 $n$ 个自然数 $a_1\sim a_n$，保证和是 $n$ 的因数。现在进行若干次操作，将 $a_i$ 给 $a_j$ 一点，且 $i$ 在 $j$ 前面。问有没有一种方案，使得 $a_1\sim a_n$ 都相等。

## 思路：
非常好想。

1. 求出如果都相同的话应该是多少，就是所有的和除以 $n$，设为 $k$。

2. 将 $a_i$ 从 $1\sim n$ 遍历一遍，如果 $a_i$ 大于 $k$，就把多出来的加到 $a_{i+1}$ 里面。如果小于，那就不可能了。因为前面多的已经加上，而后面的不能加到前面。如果等于就不动。

3. 如果遍历过程中没有不可能的情况那就是可以的了。

以上就是本题的思路了，并不难。

如果还不懂就看代码吧！

**切勿抄袭！！！**

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define int long long//n<=2*10^5,a[i]<=10^9,和爆int
int t,n;
int a[N];
inline int read(){
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	t=read();
	while(t--){
		n=read();
		memset(a,0,sizeof(a));
		int s=0;
		for(int i=1;i<=n;i++)
			a[i]=read(),s+=a[i];//求和
		int k=s/n,f=1;//f记录有没有不行的情况 
		for(int i=1;i<=n;i++){
			if(a[i]<k){
				f=0;
				break;//小于不行跳出
			}
			a[i+1]+=a[i]-k; //多的加到后面去
		}
		if(f)
			printf("YES\n");
		else
			printf("NO\n");//输出
	}
	return 0;
}
```
完结~

---

## 作者：__Octhyccc__ (赞：0)

题意简述：有 $n$ 个水瓶，每个水瓶都有 $a_i$ 升水，保证所有 $a_i$ 的和能整除 $n$。每次选定两个数 $i,j$，并且 $i<j$，意为从 $i$ 号瓶中倒任意升水到 $j$ 号瓶中，求能否让所有瓶子中的水量相等，多组数据。

倒推法，从 $a_n$ 开始，只要有 $a_i\sim a_n$ 的和的平均数大于所有瓶子中水量的平均数就不可以，否则可以（因为操作时 $i<j$，右边的水一定不可以往左边移动）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[200000],b[200000];
ll cnt;bool k;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
			cnt+=a[i];
		}
		for(int i=n-1,j=0;i>=0;i--,j++){
			if(i==n-1)b[j]=a[i];
			else b[j]=a[i]+b[j-1];
		}
		cnt/=n;
		for(int i=0;i<n-1;i++){
			if(double(b[i])/double(i+1)>cnt){
				puts("No");
				k=1;break;
			}
		}
		if(!k)puts("Yes");
		k=0;cnt=0;
		for(int i=0;i<n;i++)b[i]=0;
	}
	return 0;
}
```

---

## 作者：IANYEYZ (赞：0)

简单模拟题。

先算出每个容器中最终应该有多少水（设这个水量为 $s$）。

题目的意思是每个水桶能够向右边的任意一个水桶倒水。

转换一下，具体的，考虑维护一个虚拟容器。

从左往右扫一遍（设当前扫到容器 $i$）：

当 $a_i \geq s$ 时，将多出来的部分（$a_i - s$）倒出至虚拟容器当中。

否则，从虚拟容器中取出不足的部分 $s - a_i$，不够取就无解。

这个做法的正确性是显然的，注意到需要补充水的容器中补的水一定来自于先前的容器。

代码（自行忽略 `debug` 库）：

```cpp
#include <iostream>
#ifndef ONLINE_JUDGE
#include "../../../debug.hpp"
#else
#define debug(...)
#define debugArr(...)
#endif
#define int long long
using namespace std;
int a[200010],sum[200010],t,n,s,re;
signed main()
{
	cin >> t;
	loop:while (t--) {
		cin >> n;
		s = 0;re = 0;
		sum[n + 1] = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			s += a[i];
		}
		s /= n;
		for (int i = n; i >= 1; i--) {
			sum[i] = sum[i + 1] + (a[i] < s ? s - a[i] : 0);
		}
		for (int i = 1; i <= n; i++) {
			if (a[i] > s) {
				re += a[i] - s;
			} else {
				if (s - a[i] > re) {
					cout << "NO" << "\n";
					goto loop;
				} else {
					re -= s - a[i];
				}
			}
			debug(i,re);
		}
		if (re != 0) {
			cout << "NO" << "\n";
			goto loop;
		}
		cout << "YES" << "\n";
	}
}
```

---

## 作者：vectorxyz (赞：0)

一道贪心题，赛时对了。

#### 题目分析
很容易发现，如果让所有数都相等，恰好，题目中说了所有 $a_i$ 的和可以整除 $n$，那我们肯定让所有数变成这个平均值。

解决了这一点，我们再来细看题目，他说每次选一个 $i$ 和 $j$，并且 $i < j$，让 $a_i$ 分一些给 $a_j$，我们可以把这个操作叫上贡。

然后我们逐一判断每一个数。如果当前数大于平均值，说明他可以给后面的数上贡，用一个计数器 $cnt$ 来储存；如果当前值等于平均值，不用操作；如果当前值小于平均值，又分两种情况，平均值减去 $a_i$ 的差比 $cnt$ 小，说明可以被上贡，那就进行上贡操作，让 $a_i$ 变为平均值，让 $cnt$ 减小。如果他们俩的差比 $cnt$ 大，那无法进行上贡，就不合法了，直接退出循环。

#### 代码实现
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;

int a[200005];
void work()
{
    int n;
    cin >> n;
    int sum = 0;
    for(int i = 1;i <= n;i ++ ) cin >> a[i], sum += a[i];
    sum /= n;
    int cnt = 0;
    for(int i = 1;i <= n;i ++ ){
        if(a[i] > sum){
            cnt += (a[i] - sum);
        }
        if(a[i] < sum){
            if(cnt >= sum - a[i]){
                cnt -= (sum - a[i]);
            }
            else{
                puts("NO"); return ;
            }
        }
    }
    puts("YES");
}
signed main()
{
    int T;
    cin >> T;
    while(T -- ) work();
    return 0;
}
```
#### 后记

[记录](https://codeforces.com/contest/1931/submission/246141561)。

---

## 作者：minVan (赞：0)

**题目大意**

对于 $1\le i<j\le n$，可以将 $a_i\gets a_i-x$，$a_j\gets a_j+x$，问能否通过多次操作使得 $a_i$ 两两相等。保证 $n\mid \sum a_i$。

**解题思路**

令 $sum=\left(\sum a_i\right)\div n$，则如果 $a_i<sum$，那么 $s\gets s-(sum-a_i)$，此时若 $s<0$，那么无解退出；否则 $s\gets s+(a_i-sum)$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, a[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    cin >> n;
    int sum = 0, s = 0;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
      sum += a[i];
    }
    sum /= n;
    bool flag = 0;
    for(int i = 1; i <= n; i++) {
      if(a[i] < sum) {
        if(s < sum - a[i]) {
          flag = 1;
          break;
        }
        s -= sum - a[i];
      } else {
        s += a[i] - sum;
      }
    }
    cout << (!flag ? "YES\n" : "NO\n");
  }
  return 0;
}
```

---

## 作者：Lemon_zqp (赞：0)

### 题意
给你一个数组 $a$，让你把每个杯子里的水操作平均，你只能从你前面的被子里去水，并且可以不全部倒完但也不能倒掉。请你求出是否可以完成要求。
### 思路
既然他保证了 $a_i$ 的总和肯定能被 $n$ 整除，那么就不用特判了。直接开始循环模拟，先求出平均数，当 $a_i$ 大于平均数时，将 $s$ 加上 $a_i$ 减平均数。$s$ 表示前面的水满足了条件还多出的部分的总和。当 $a_i$ 小于平均数时，$s$ 就派上用场了，判断 $s$ 是否大于等于平均数减 $a_i$，如果是，$s$ 减去平均数减 $a_i$ 的差。表示 $a_i$ 已经到达了平均数的线。否则输出 `No` 直接结束。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[200005];

signed main()
{
	int t;
	cin >> t;
	while(t--){
		int n, ping = 0;
		cin >> n;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			ping += a[i];
		}
		ping /= n;
		int sheng = 0;
		bool if_c = false;
		for(int i = 1; i <= n; i++){
			if(a[i] < ping){
				if((ping - a[i]) <= sheng){
					sheng -= (ping - a[i]);
				}
				else{
					cout << "No" << endl;
					if_c = true;
					break;
				}
				
			}
			else if(a[i] > ping){
				sheng += a[i] - ping;
			}
		}
		if(!if_c){
			cout << "Yes" << endl;
		}
	}
	return 0;
}
```


---

## 作者：Lele_Programmer (赞：0)

# CF1931B 题解

## 题目大意

给你 $n$ 个装有不同水量的容器，它们一字排开，每一次你只能拿编号靠前的容器向编号靠后的容器倒水，问经过多次操作后能否使所有容器的水量一致。

## 题目分析

最终，使得所有容器的水量一致，则这时候所有容器的水量即为总水量的平均数，所以在读入数据的时候记录一下总和并求出平均值。平均值记为 $avg$，每个容器的水量记为 $a_i$。

从前往后枚举每一个容器，如果这个容器水量超过平均值，那么它可以对后面产生 $a_i-avg$ 的贡献，如果这个容器水量低于平均值，它就会在前面所产生的贡献中消耗 $avg-a_i$。

我们将贡献记为 $addon$，每次只需将 $addon$ 加上 $a_i-avg$，当 $addon$ 的值在任何时刻小于 0 的时候，则无解，反之，则有解。

## 代码

经过理解分析之后，代码就不难写了！

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=200005;

int T,n;
int a[N],sum;

int main() {
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        sum=0;
        for (int i=1;i<=n;++i) {
            scanf("%d",a+i);
            sum+=a[i];
        }
        int avg=sum/n;
        int addon=0;
        bool ok=true;
        for (int i=1;i<=n;++i) {
            addon+=(a[i]-avg);
            if (addon<0) {
                ok=false;
                break;
            }
        }
        if (ok) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：Mrlaolu (赞：0)

**题目概述**：给你 $n$ 个正整数数字 $a_1-a_n$，它们的和保证能被 $n$ 整除。你进行任意次（包括 $0$ 次）把 $a_i$ 的数值分点给 $a_j$ 的操作，其中 $i$ 必须小于 $j$（即 $i < j$ ）且每次操作 $i$ 和 $j$ 都可变。问你能不能使该数组全变为平均数。

**题目类型**：贪心，模拟

**解题思路**：

先算出这 $n$ 个数字的平均数，记作 $ave$。因为可以进行无数次题目种所提到的操作，只要 $i < j$，所以我们创造一个变量 $spare$，从后往前遍历数组 $a_i$。只要 $a_i > ave$，我们就把多余的数值放到 $spare$ 里，如果 $a_i < ave$ ，则把 $spare$ 里的值取出来给 $a_i$。如果某时刻 $spare < 0$，则说明排在后面的数字多余的值不足以填上前面的数，输出“NO”；反正如果到结束都 $spare \ge 0$，则输出“YES”；

**AC代码**：

```c++
//
// Created by Mrlaolu on 2024/2/13.
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

void solve() {
  // code here
  int n;
  cin >> n;
  vector<int>arr(n);
  int sum = 0;
  for(int i = 0;i < n;++i)
  {
    cin >> arr[i];
    sum += arr[i];
  }
  int ave = sum / n;

  int spare = 0;
  for(int i = 0;i < n;++i)          
  {
    if(spare < ave - arr[i])
    {cout << "NO\n";return;}
    else
    {
      spare -= ave - arr[i];       //直接利用负负得正原理，少掉对ave-arr[i]正负的判断
    }
  }

  cout << "YES\n";
}

signed main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

