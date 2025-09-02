# Mark the Dust Sweeper

## 题目描述

问最少多少次操作能使 $a_1,a_2,...,a_{n-1}$ 均等于 $0$。

## 样例 #1

### 输入

```
4
3
2 0 0
5
0 2 0 2 0
6
2 0 3 0 4 6
4
0 0 0 10```

### 输出

```
3
5
11
0```

# 题解

## 作者：Jeremiahy (赞：7)

## 题意

给一个元素个数为 $n$ 的序列 $a$，你可以选出下标为 $i$ 和 $j$（$i<j$）的两个数，满足 $ a_i , a_{i+1} , \dots , a_{j-1} $ 都大于 $0$，此时可以将 $a_i$ 减 $1$，$a_j$ 加 $1$，输出将 $ a_1  ,  a_{2}  ,  \dots  , a_{n-1} $ 都变为 $0$ 至少需要几次操作。

# 分析

首先想最简单的情况，序列里某个数 $a_i$ 到 $a_n$ 的路上全是非 $0$，这时我们可以把 $a_i$ 全堆到 $a_n$ 上，需要 $a_i$ 次操作。

然而，如果中间存在一个 $0$ 呢？我们就需要填上它，这就会多增加 $1$ 次操作（因为可以先给它增加 $1$，$a_i$ 减少 $1$，然后就成为了上面最简单的情况），所以我们可以统计 $0$ 的个数（不含前导零），与 $ a_1 $ , $ a_{2} $ , $ \dots $ , $ a_{n-1} $ 求和即可。

另外，根据数据范围，最高可能达到 $10^{14}$ 级别，所以一定要开 long  long。

在具体的代码实现中，需要注意一些边界问题，具体在代码注释中说明。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, a[200010];
signed main () {
	cin >> t;
	while (t--) {
		int have = 0, cnt = 0, ans = 0;//每次初始化
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			if (a[i])
				have = 1;//处理前导零
			else if (have && i != n)//a[i]为零时不计数
				cnt++;
		}
		for (int i = 1; i < n; i++)
			ans += a[i];
		cout << ans + cnt << "\n";
	}
	return 0;
}
```


---

## 作者：Haber (赞：3)

**UPD:2022/07/18 改了几个语病/错别字。** 

### 题目大意

给一个长度为 $n$ 的序列 $a$，你需要进行以下操作使得序列 $a$ 的前 $n-1$ 项均为 $0$。

每个操作分为 $3$ 步：

1. 选择两个下标 $i$ 和 $j$，其中 $i<j$，并且 $a_i,a_{i+1},...,a_{j-1}$ 严格大于 $0$。

2. 把 $a_i$ 设置为 $a_i-1$。

3. 把 $a_j$ 设置为 $a_j+1$。

### 题目总评

这题首先考视力，笔者视力不好，一开始把 $a_i-1$ 看成 $a_{i-1}$，然后瞪了半天样例没看懂样例在干啥。好不容易发现了，结果又没开 long long，然后交了 N 发之后放弃了这道题。由于错得比较凄惨，写篇题解纪念一下。

### 解题方案

首先你会发现操作一次之后序列总和是不变，因为 $a_i+a_j=a_i+1+a_j-1$。所以你可以把这个操作看成是从 $i$ 这个地方挪了 $1$，然后到 $j$ 这个地方，有点像瞬移的感觉。

然后我们看一下我们的目标，就是把所有的数全部挪到 $a_n$ 上。你想一想，如果我们能一次性把一个数挪到最后该多好啊！可惜，如果中间有 $0$ 的话，我们就不能一次性转移到后面去。怎么办呢？

是零我们就把它变成非零的数，其实就是 $1$，因为变成 $1$ 的代价最小。怎么变？

举个例子 $[3,0,0,0]$。

这时我们发现 $3$ 的后方有 $0$ 不能直接转移，那么就把后方除了最后一个 $0$ 都填了。

1. $i=1,j=2$ 此时序列为 $[2,1,0,0]$。
2. $i=1,j=3$ 此时序列为 $[1,1,1,0]$。

此时序列除了最后一个 $0$ 以外的 $0$ 都被我们填掉了。并且发现了后面有几个 $0$ 就要填几次的重要~~废话~~结论。

有的小朋友就要问了，如果序列长这样 $[2,0,0,0,0]$，我们需要填 $3$ 个 $0$，但是我们只有 $2$ 怎么办？刚才的结论还成立吗？

模拟一下就好了。

1. $i=1,j=2$ 此时序列为 $[1,1,0,0,0]$。
2. $i=1,j=3$ 此时序列为 $[0,1,1,0,0]$。
3. $i=2,j=4$ 此时序列为 $[0,0,1,1,0]$。

至此，后方除了最后一个 $0$ 都填好了。可以发现这其实就是一个向后转移的过程。非常像一个游戏，叫推箱子。

都分析完了，开码！
### 代码实现

你需要向后填充的 $0$ 的个数用的是 `zero` 这个变量存储。当然你可以发现，第一个有数值之前的 $0$ 我们是不用去管它们的，因而不计入 `zero` 之中。

当你把后面的 $0$ 全部填充好了之后，还需要转移的次数就是除开最后一个数的和了。当然，最后一个数完全没有用，所以我就把它读掉，什么都不处理就行了。

操作次数就是 `zero+sum`。

**没啥用的代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a,sum,zero;
int main(){
	cin>>t;
	while(t--){
		sum=0,zero=0;
		bool fl=false;
		cin>>n;
		for(int i=1;i<n;i++){
			cin>>a,sum+=a;
			if(fl&&!a) zero++;	//需要填充的0
			if(a!=0) fl=true;	//是否读到了有数值的数
		}
		cin>>a;
		cout<<sum+zero<<endl;
	}
	return 0;
}
```

填空：十年OI一场空，不开 (    ) 见祖宗。

---

## 作者：shenyiran (赞：2)

### 分析
共有 $n$ 个房间，要想把灰尘都扫到最后一个房间，满足 $a_1=a_2=...=a_{n-1}$，但是每次只能移动一个房间，所以中间的 $0$ 最少会经过一次。假设 $a_i$ 为第一个非 $0$ 数字，将灰尘总数相加，再加上 $i$ 后面的 $0$ 的个数，因为前面没有灰尘，所以只算 $i$ 后面的，就得到结果了。
### AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[500010],p;
long long ans;
int main(){
	scanf("%lld",&t);
	while(t--){
		ans=0;
		p=1e9;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			if(a[i]!=0&&p==1e9){
				p=i;//找第一个非0数
			}
		}
		for(int i=p;i<=n-1;i++){//累加答案
			if(a[i]!=0){
				ans+=a[i];
			}
			else{
				ans++;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Failure_Terminator (赞：2)

比赛时想了好久都没想出来，现在开始补题。

## Problem

有一长度为 $n$ 的数列 $a$。

可以选定 $1$ 到 $n$ 之间的两个整数 $a_i$，$a_j$，然后使 $a_i = a_i - 1$，$a_j = a_j+1$。

我们称其为一次操作。

求要经过多少次操作，才能使除 $a_n$ 外的所有整数都变为 $0$。

## Solution

首先，我们知道，开头的一段 $0$ 是不需要任何处理的。

接着，我们需要将剩下的一段中为 $0$ 的数，用 $1$ 次操作都变为 $1$。

设第一个非 $0$ 位置是 $q$，这时 $a$ 数列满足任意在 $a_q$ 到 $a_n$ 之间的整数都不等于 $0$。

然后，我们就可以将 $a_q$ 到 $a_{n-1}$ 之间的数，通过操作将其变为 $0$。

可以证明没有更优解法。

由于此解法恰好将整个数组遍历一遍即可得出结果，因此时间复杂度为 $O(n)$。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std; 
int t;
int n,a[200005];
void solve(){
	scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    ll ans=0,q=1;
    while(q<=n&&a[q]==0) q++;
    for(int i=q;i<n;i++){
        ans+=a[i];
        if(a[i]==0) ans++;
    }
    cout<<ans<<endl;
}
int main()
{
    scanf("%d",&t);
    while(t--) solve();
    return 0;
}
```

By **haimo**

---

## 作者：GI录像机 (赞：0)

## 思路：

看到大佬们的各种找结论，本蒟蒻来交一个无脑模拟。

容易想到，本题是要把所有有值的点铺成一条路，让最左端的有值的点能够直接把值传到第 $n$ 个点。我们考虑模拟这个过程。

我们可以将所有在第一个有值点右侧的 $0$ 的下标加入优先队列，因为左侧肯定用不上。然后将所有有值的点的下标加入另一个优先队列。这样我们的堆顶就一定是最左侧的有值点和它后面第一个 $0$，刚好可以模拟题目给出的过程。

## 代码：

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
int t = read(), n, a[(int)(2e5) + 10];
signed main() {
	while (t--) {
		int ans = 0;
		n = read();
		priority_queue<int>q1, q2;
		for (int i = 1; i < n; i++) {
			a[i] = read();
			if (a[i])q1.push(i);
			else if (!q1.empty())q2.push(i);
			ans += a[i];
		}
		a[0] = read();
		if(q1.empty()){
			puts("0");
			continue;
		}
		int tmp = q1.top();
		q1.pop();
		while (!q2.empty()) {
			a[tmp]--;
			a[q2.top()]++;
			q1.push(q2.top());
			q2.pop();
			if (!a[tmp]) {
				tmp = q1.top();
				q1.pop();
			}
			ans++;
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}

```


---

## 作者：Qerucy (赞：0)

对于这道题，我们先找到所有非 $0$ 数中最左边的一个数，定义这个数的下标为 $i$。

然后我们开始想如何从 $i$ 开始往右把一个个数变为 $0$。

如果从 $a_i$ 到 $a_{n-1}$ 中每个数都是非 $0$ 数，那么我们只需要从 $a_i$ 开始到 $a_{n-1}$ 一个个把数搬到 $a_n$ 即可。

定义答案为 $ans$，那么就有以下这个式子：

$$ ans=\sum\limits_{j = i}^{n-1} a_j $$

然后我们考虑 $i$ 到 $n-1$ 中间有 $0$ 的情况。

如果 $i$ 到 $n-1$ 中间有一些数的值为 $0$，那么我们需要把这些数的值转变为非 $0$ 数才能满足题意。转变为什么好呢？我们要花最小的代价，所以搬的数就要尽可能的小，所以只能转变为 $1$。

最后我们来计算 $ans$，如果 $i$ 到 $n-1$ 中间有一些数的值为 $0$，那么我们需要给 $ans$ 加上从 $i$ 到 $n-1$ 之间值为 $0$ 的数的数量。最后输出 $ans$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
#define int long long //注意开long long
 
int n;
int a[2000010];
int t;
int x;
 
signed main(){
    scanf("%lld",&t);
    while(t--){
        int ans=0;
        bool fg=0;
        scanf("%lld",&n);
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
        }
        for(int i=1;i<=n-1;i++){
            if(a[i]==0){
                if(fg) ans++;
            }
            else{
                ans+=a[i];
                fg=1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1ud4y1Q7f5)

### 2 思路

我们可以发现，将 $a[i]$ 的数一步到位地扔给 $a[n]$ 肯定是最好的。但是，中间可能有些 $0$ 阻挡了它，那么就要填补这些 $0$ 之后，再依次将 $a[i]$ 扔给 $a[n]$。

所以，设 $pos$ 满足 $a[1]$ 到 $a[pos-1]$都为 $0$ 但是 $a[pos]$ 不为 $0$，答案就是：

$$\sum_{i=pos}^n\max(a[i],1)$$

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
int a[max_n+2];
long long ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1705B_1.in","r",stdin);
	freopen("CF1705B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		ans=0;
		for(int i=1,fl=false;i<n;++i){
			if(a[i])fl=true;
			if(!fl)continue;
			if(a[i]==0)++ans;
			else ans+=a[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80111580)

By **dengziyue**

---

## 作者：_lfxxx_ (赞：0)

### 题意：
给你一个 $n$ 个数的序列 $a$，你可以进行这样的操作：

选择一段满足区间 $[i,j-1]$ 内的数都严格大于 $0$ 的区间 $[i,j]$，之后给 $a_i$ 减 $1$，$a_j$ 加 $1$，即 $a_i\gets a_i-1$，$a_j\gets a_j+1$。

问至少需要几次操作使得 $a_1=a_2=a_3=\ldots=a_{n-1}=0$。
### 思路：
首先对于非 $0$ 的 $a_i(i<n)$，我们希望通过 $[i,n]$ 区间操作 $a_i$ 次使得 $a_i\gets 0$，但操作的要求是要满足区间内的树严格大于 $0$。因此对于 $a_j=0(i<j<n)$，我们可以通过 $[i,j]$ 使得 $a_j\gets1$。

那万一 $[i,j]$ 不满足呢？那就继续像上面的操作。其实我们就是从 $i$ 按顺序将 $0$ 填上。根据上面操作规则，容易得出将 $0$ 填上只要多花 $1$ 的贡献。

所以我们先找到第一个不为 $0$ 的数，然后加上它后面的所有数。特殊地，$0$ 加上 $1$ 的贡献。

时间复杂度是线性的，即 $O(\sum n)$。
### 代码：
```cpp
namespace solution{
void main(){
	int T,n,x;
	bool f;
	long long ans;
	cin>>T;
	while(T--){
		cin>>n;
		f=false,ans=0;
		for(int i=1;i<n;++i){
			cin>>x;
			if(x)
				f=true;
			ans+=x;
			if(f&&!x)
				++ans;
		}
		cin>>x;
		cout<<ans<<'\n';
	}
}
}
```


---

## 作者：Anguei (赞：0)

## 题意

有一个数组 $a$，长度为 $n$。每次操作可以选两个坐标 $i < j$，且满足 $[i, j-1]$ 所有位置的元素都严格大于零，令 $a_i = a_i - 1$，$a_j = a_j + 1$。

问：至少多少次操作，可以使数组 $a$ 的前 $n-1$ 个元素都为零？

## 分析

如果这个数组，前 $x$ 个数字都是零，那么这部分就无需考虑。于是可以直接删除掉前面 $x$ 个零，同时更新 $n$ 的大小。

假如 $n=2$，那么最小的操作次数就是 $a_1$。

假如 $n=3$，那么最小操作次数就是 $a_1 + a_2$，即先用 $a_1$ 次操作，把第一个位置的数字全都挪给 $a_3$，再花 $a_2$ 次操作把第二个位置的数字也全都给 $a_3$。

但是如果这中间有一些为零的位置，就要先把这些位置填上一个数字。

因此，答案为 $\sum_{i=1}^{n-1}a_i + \operatorname{zeroCount}(1, n-1)$。此处的 $a$ 与 $n$ 是指删除了开头一段零之后的新数组信息。

## 代码

```cpp
void solution() {
  int n;
  read(n);
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) read(a[i]);
  ll sum = std::accumulate(a.begin() + 1, a.end() - 1, 0ll);
  if (sum == 0) return print(0);
  int start = 0;
  for (int i = 1; i <= n - 1; ++i) {
    if (a[i] > 0) {
      start = i;
      break;
    }
  }
  int cnt = 0;
  for (int i = start; i <= n - 1; ++i) if (a[i] == 0) ++cnt;
  print(cnt + sum);
}
```



---

