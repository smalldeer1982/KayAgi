# [JOI 2018 Final] 寒冬暖炉 / Stove

## 题目描述

JOI 君的房间里有一个炉子。因为 JOI 君已经习惯了寒冷的温度，所以当他一个人在房间里时，他不需要打开炉子。但是，有客人时，他需要打开炉子。有一天，$N$ 位客人将拜访 JOI 君。第 $i$ 个客人 ($1 \leq i \leq N$) 将在时间 $T_i$ 到达，并在时间 $T_i+1$ 离开。任何时间最多有一个客人访问  JOI 君。JOI 君可以随时开火或关火。JOI 君用火柴打开炉子。JOI 君只有 $K$ 根火柴。 因此他最多可以打开炉子 $K$ 次。在一天的开始，炉子是关闭的。当炉子打开时，它需要燃料。因此，JOI 君控制着他何时打开或关闭炉子，他想尽量减少炉子的总运行时间。  
现给定访问 JOI 君的客人数据和 JOI 君拥有的火柴数，请编写一个程序来计算炉子总运行时间的最小值。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 \leq N \leq 10^5$，$1 \leq K \leq N$，$1 \leq T_i \leq 10^9$（$1 \leq i \leq N$），$T_i < T_{i+1}$（$1 \leq i \leq N-1$）。  
- Subtask $1$（$20$ points）：$N \leq 20$。  
- Subtask $2$（$30$ points）：$N \leq 5000$。  
- Subtask $3$（$50$ points）：没有额外的限制。  
#### 样例说明  
**对于样例 $1$**：三位客人将访问 JOI 君。如果他按以下方式打开和关闭炉子，那么当客人来访时打开炉子，他打开炉子两次，炉子的总运行时间为 $(4-1)+(7-6)=4$。  
- 当第一位客人到来时，他在时间 1 打开炉子。  
- 当第二位客人离开时，他在时间 4 关掉炉子。  
- 当第三位客人到来时，他在时间 6 打开炉子。  
- 当第三位客人离开时，他在时间 7 关掉炉子。  

由于炉子的总运行时间不能小于 $4$，输出 $4$。  
**对于样例 $2$**：JOI 君只能打开一次炉子。因此，他在第一个客人来的时间 $1$ 打开炉子，当第三位客人离开时他在时间 $7$ 关掉炉子。  
请注意，客人离开的时间可以与下一位客人到来的时间相同。  
**对于样例 $3$**：JOI 君在每位客人到来时打开炉子，并在每位客人离开时关掉炉子。  
#### 题目说明：  
来源于 The 17th Japanese Olympiad in Informatics (JOI 2017/2018) Final Round 的 [T1：Stove](https://www.ioi-jp.org/joi/2017/2018-ho/2018-ho-t1-en.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
3 2
1
3
6```

### 输出

```
4```

## 样例 #2

### 输入

```
3 1
1
2
6```

### 输出

```
6```

## 样例 #3

### 输入

```
3 3
1
3
6```

### 输出

```
3```

## 样例 #4

### 输入

```
10 5
1
2
5
6
8
11
13
15
16
20```

### 输出

```
12```

# 题解

## 作者：封禁用户 (赞：9)

供题人前来报到，现分享自己的解题思路及代码、官方解题代码、双倍经验告知。  
题目传送>>[P7666](https://www.luogu.com.cn/problem/P7666)。  
### 题意简述  
JOI 君会在家中有客人时开着可随时开关闭的炉子。现他有 $K$ 根可开炉子的火柴，将有 $N$ 名客人分别在已知的特定时刻 $T_i$ 前来并在 $T_i+1$ 离开，求炉子最短总运行时间。  
### 题目分析：  
因为客人在的时刻是零零散散的，所以就会存在一些无客人的时间间隔，而要想使炉子运行总时间最短，那么我们应尽可能地在合适的时刻及时关闭炉子，避免在无客人时造成炉子浪费，即尽可能做到只有有客人在时炉子才开着。而在下一次来客人时再打开炉子是需要消耗火柴的，而火柴数量又有限，所以有时我们可能需要保持炉子运行（即使此时无客人）。  
当第一位客人前来时我们必须消耗一根火柴打开炉子，但如果一直保持运行到最后一名客人走显然是不理智的。我们需要尽可能的避免较长时间无客人间隔运行炉子，此时我们就可在当前客人走时关闭炉子，在下一名客人来时再开炉子。即每多一根火柴，我们就可尽可能的避免一个无客间隔浪费。  
综上分析，我们可以分别计算各无客间隔时长（共 $N-1$ 个无客间隔），然后优先依靠炉子关开避免较大无客间隔期间的浪费。  
### Code1(己)：  
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,k;   //定义客人数、火柴数 
int a[100010],b[100010];   //开数组存各客人前来的时刻、各无客间隔时长 
int ans=0;   //定义炉子运行总时长 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k; 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	ans+=a[n]-a[1]+1;   //如不能避免无客间隔的全程时长 
	for(int i=1;i<n;i++)
	{
		b[i]=a[i+1]-a[i]-1;   //分别计算各无客间隔时长
	}
	sort(b+1,b+n);   //对各无客间隔时长排序（默认递增） 
	for(int i=n-1;i>=n-k+1;i--)   //因为递增排的序所以回着循环 ，注意共n-1个间隔，共k根火柴 
	{
		ans-=b[i];   //优先依靠炉子关开避免较大无客间隔期间的浪费并，减去间隔时长 
	}
	cout<<ans;	
	return 0;
}
```
### Code2(官方)（C++11及以上）：  
```cpp
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0;i<n;i++)
#define PB push_back

using vi=vector<int>;

int read(){
	int i;
	scanf("%d",&i);
	return i;
}

int main(){
	int n=read(),k=read();
	int mn,mx,last;
	vi len;
	REP(i,n){
		int t=read();
		if(i==0)mn=t;
		if(i==n-1)mx=t+1;
		if(0<i)len.PB(t-last-1);
		last=t;
	}
	sort(len.begin(),len.end(),greater<int>());
	int ans=mx-mn;
	REP(i,k-1)ans-=len[i];
	cout<<ans<<endl;
}
```  
### 结果（己）（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/854f38g0.png)  
### 双倍经验  
本供题人在供此题时即发现了此题与之前做过的一题基本同思路，现分享双倍经验>>[P1209 [USACO1.3]修理牛棚 Barn Repair](https://www.luogu.com.cn/problem/P1209)，区别即为后者输入数据多了一个无关变量且输入数据可能无序需多一次排序。  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：chlchl (赞：5)

## 题目意思
题目已经描述得很清楚了，就是有 $n$ 个客人来访，每个客人来访时间为 $t_i$，离开时间为 $t_i+1$。现在有 $k$ 根蜡烛，需要求最小点燃时长。

## 主要思路
思路：既然蜡烛有限，应该让它们的**利用价值最大**，在相邻两个时间段的差值，即 $t_{i+1}-t_i$ 最大时熄灭炉子，这样每根蜡烛就可以节省尽量多的点燃时间。

实现方法：先将相邻两个时间段的差值**从大到小**排序，算出总时间，然后将**前 $k-1$ 个差值减掉**（相当于用掉 $k-1$ 根蜡烛）。

**注意，这里是 $k-1$ 个间隔，因为第一次点燃火炉要消耗一根蜡烛。**

## 一些小坑
1. 算两点之间的间隔时，注意只有 $n-1$ 个间隔。
1. 注意答案初始值需要设为 $t_i-t_1-1$，即从第一个客人来时点燃火炉，最后一个客人离开时关闭火炉。
1. 排序时注意是从大到小排序（从小到大排序的话是减掉后 $k-1$ 个间隔）。

## 代码
建议各位看完本蒟蒻的题解后尝试自己写，以下代码仅供参考。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
int n, k, ans, t[N];

bool cmp(int x, int y){return x > y;}
//排序规则

int main(){
	cin >> n >> k;
	k--;//现在的k已经是前文的k-1了
	for(int i=1;i<=n;i++)	cin >> t[i];//读入不解释
	ans = t[n] - t[1] + 1;//初始情况全部打开 
	for(int i=1;i<=n;i++)	t[i] = t[i + 1] - t[i] - 1;//求两位客人间隔，直接用原数组即可，节省空间
	sort(t + 1, t + n, cmp);//从小到大排个序 
	for(int i=1;i<=k;i++)	ans -= t[i];//减掉前k-1个间隔
	cout << ans << endl;
	return 0;
} 
```
如果本篇题解对你有启发，点个赞再走吧。

---

## 作者：love_tide (赞：4)

## 总体策略：贪心

~~都知道是贪心，看你怎么贪呗！~~

------------
## 分析
 1.  如果要想让火炉燃烧时间少，就得在无客人到访的时候熄灭。
 
 2.  如果要想让火炉燃烧时间更少，就得让所有的火柴都用上，也就是尽可能多的点燃熄灭。
 
 3.  如果要想让火炉燃烧的时间最少，就得在客人到访时间间隔最长的时候熄灭，点燃火炉，使用火柴。

 总而言之 ， 让每次点燃熄灭，让每根火柴发挥最大用处。 

## 思路

 如果JOI中途不熄灭炉火，从第一位客人来访到最后一位客人离开，炉火运行时间是： $a_{n}-a_{1}+1$ 。(因为第一位客人到访后还有1的访问时间)



 贪心算法，就要尽可能的在时间间隔大两次访问之间熄灭炉火，所以也要推导出访问间隔公式： $a_{i+1}-a_{i}-1$ 。(因为其中夹杂着第一位客人的到访时间）
 
 把间隔时间存储在数组里，用 sort 从大到小排序，在依照火柴数量减去相应的间隔时间。


## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int n,k,a[100005];

bool cmp(int x,int y){
	
	return x>y;

} 

int main(){
	
	cin>>n>>k;
	
	for(int i=1;i<=n;i++){
		cin>>a[i];	
	}
	
	int time=a[n]-a[1]+1;//如果一直开着火炉的时间 
	
	for(int i=1;i<=n;i++){
		a[i]=a[i+1]-a[i]-1;
	} 
	
	sort(a+1,a+n,cmp);//cmp降序，最后一个数无间隔
	
	for(int i=1;i<=k-1;i++){//k-1是因为在第一次招待第一位客人时点燃炉火消耗了火柴 
		time-=a[i];
	} 
	
	cout<<time<<endl;
	
	return 0;
	
} 
```


---

## 作者：Malkin_Moonlight (赞：3)

[双倍经验](https://www.luogu.com.cn/problem/AT_joi2018ho_a)。

一道简单贪心，先把最大间隔求出来，再算两位客人间隔，把算出来的这些间隔从大到小排序，再用最大间隔减 $k - 1$ 次算出来的间隔。

为什么其他题解都是用结构体排序？要想从大到小排直接用 `greater<ll>()` 就可以了啊。

上代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 1e5 + 5;
ll n, k, ans;
ll a[maxn];
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	ans = a[n] - a[1] + 1;
	for (int i = 1; i <= n; i++) {
		a[i] = a[i + 1] - a[i] - 1;
	}
	sort(a + 1, a + n, greater<ll>());
	for (int i = 1; i < k; i++) {
		ans -= a[i];
	}
	cout << ans << endl;
	return 0;
}
```

[我的 AC 记录](https://www.luogu.com.cn/record/190737170)

---

## 作者：yzy1 (赞：3)

本题解修改于 @uliahradri 大佬的（未通过）题解。

## 题目大意

有 $n$ 个点，用 $k$ 个区间覆盖这些点且使区间长度和最小。

## 解题思路

随便手玩一下样例，画个图，可以发现这些区间之间存在 $k-1$ 个空。

而有 $n$ 个点，所以共有 $n-1$ 个空，点 $i$ 和点 $i+1$ 之间的空的长度为 $t_{i+1}-t_{i}-1$。

贪心地想，我们找到前 $k-1$ 大的空，那么答案就是 $t_n-t_1+1$ 再减去这 $k-1$ 个空的长度，找前 $k-1$ 大的空我们可以从大到小排序后贪心。

需要注意的是：某个测试点 $n=1$，如果写的丑可能需要特判一下。

## 参考代码

```cpp
signed main() {
  in(n)(k)(t, n);
  re(i, n - 1) u[i] = t[i + 1] - t[i] - 1;
  sort(u + 1, u + n, [](int a, int b) { return a > b; });
  ans = t[n] - t[1] + 1;
  re(i, k - 1) ans -= u[i];
  out(ans)('\n');
  return 0;
}
```

---

## 作者：ylch (赞：2)

首先考虑一种特殊的情况，即 $n=k$，此时由于我们可以在一个人走后，立即关闭炉子，所以答案就是 $n$。

再考虑当 $k=n-1$ 时，我们不得不让炉子在其中两个人之间开着，贪心地思考，我们肯定要让这个“开着”的时间最小，答案即为 $n$ 加上这个最小的差值。

发现可以一直这样推下去。整合一下，答案即为：$n$ 加上最小的 $n-k$ 个差值。

发现每个操作都是非常独立的，所以选择一个差值不会对其他造成影响，此方法可行。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;

int n, k, t[maxn], d[maxn];

void solve()
{
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> t[i];
	}
	for(int i = 1; i <= n - 1; i ++){
		d[i] = t[i + 1] - t[i] - 1; // 计算间隔，不包含t[i]和t[i+1]
	}
	sort(d + 1, d + n); // d 只有n-1个元素
	
	int ans = n; // 基础的n个时间肯定要有
	for(int i = 1; i <= n - k; i ++){
		ans += d[i]; // 不得不保持开火的时间，由于排过序，所以这样答案会尽可能小
	}
	cout << ans << '\n';
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：The_Best_OIer (赞：1)

# 题解：P7666 [JOI2018] Stove

[双倍经验](https://www.luogu.com.cn/problem/AT_joi2018ho_a)。

贪心题目，先求出求出来每一次上一个客人走到下一个客人来之间间隔的时间，然后从大到小排序，前 $k - 1$ 个就是最多能节省的空闲时间，最后用总时间，也就是最后一个与第一个相差的，减去刚才那 $k - 1$ 个，就可以求出答案。

时间复杂度 $O(n)$。

从大到小排序用 `greater` 就可以了，不用像一些题解一样写结构体排序。

---

## 作者：CPPfive (赞：1)

## 题目分析

首先，如果 $K=1$，那么从第一个客人到来的时刻开始直到最后一个客人离开，火炉要一直开着，总时间为 $T_{N}+1-T_{1}$。

然后，当我们有更多的火柴的时候，每一根火柴可以允许我们在一位客人离开后关闭火炉直到下一位客人到来，即每一根火柴可以节约 $T_{i+1}-(T_{i}+1)$ 的时间。

因此，只需把所有 $T_{i+1}-(T_{i}+1)$ 从大到小排序，贪心地将总时间减去每一根火柴可以省去的时间即可。

## Code
```
//洛谷P7666 

#include <bits/stdc++.h>
using namespace std;
#define cin std::ios::sync_with_stdio(false);cin//输入优化 
int N,K,all,T[100050],kong[100050];

int main()
{
	cin >> N >> K;
	for(int i=1;i<=N;i++){
		cin >> T[i];
	}
	all=T[N]+1-T[1];//只有一根火柴时的总时间 
	for(int i=2;i<=N;i++){
		kong[i-1]=T[i]-(T[i-1]+1);
	}
	sort(kong+1,kong+N,greater<int>());
	//这里只循环K-1次，因为第一根火柴不能减少时间 
	for(int i=1;i<K;i++){
		all-=kong[i];
	}
	cout << all << endl;
}
```


---

## 作者：kobebraint (赞：0)

## 题意
给你 $n$ 个人来的时间，每个人会停留 $1$ 单位时间，有人在房间里的时候炉子必须烧着，你有 $k$ 次机会点燃炉子，求炉子最少能烧多长时间。
## 做法
第一个人来的时候肯定会消耗 $1$ 个点燃炉子的机会，所以你可以熄灭再重新点燃炉子 $k-1$ 次，也就是你可以节省 $k-1$ 个空闲时间。  
这样的话，只需要求出来每一次上一个客人走到下一个客人来之间间隔的时间，并从大到小排序，就能求出最多能节省的时间为前 $k-1$ 个间隔时间，再用总时间（第一个客人来到最后一个客人走）减去最多节省的时间就可以了。
## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n,k,t[100050],a[100050],sum;

int main(){
	cin>>n>>k;
	for(ll i=1;i<=n;i++){
		cin>>t[i];
	}
	for(ll i=1;i<=n;i++){
		a[i]=t[i+1]-t[i]-1;
	}
	sort(a+1,a+n+1,greater<ll>());
	for(ll i=1;i<k;i++){
		sum+=a[i];
	}
	cout<<t[n]-t[1]+1-sum;
} 
```

---

## 作者：jayof12 (赞：0)

灌水：真的[双倍经验](https://www.luogu.com.cn/problem/AT_joi2018ho_a)  
[题目传送门](https://www.luogu.com.cn/problem/AT_joi2018ho_a)

### 解题思路
算是简单贪心。先求最大时间，再将数组从大到小排序后减去 $k-1$ 个间隔。

### 代码（含简单注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1000005];
bool cmp(int x,int y){
     return x>y;
}//搞个函数，调为从大到小排序 
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	    cin>>a[i];//输入 
	int sum=a[n]-a[1]+1;//计算最大时间，用计数器保存 
	for(int i=1;i<=n;i++)
        a[i]=a[i+1]-a[i]-1;//计算间隔时间，并重新赋值 
	sort(a+1,a+n,cmp);//排序 
	for(int i=1;i<=k-1;i++)
        sum-=a[i];//减去间隔 
	cout<<sum<<endl;//输出+换行 
	return 0;
}
```

感谢观看！

---

## 作者：7KByte (赞：0)

$k=1$ 时，唯一的选择是区间 $[T_1,T_N]$。

$k$ 每增加 $1$ ，我们可以选择在 $T_i$ 的位置断开，使得答案减少 $T_{i+1}-T_i-1$。

对邻项的差排序，减去前 $k-1$ 个即为答案。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 100005
using namespace std;
int n,k,a[N];
int main(){
	scanf("%d%d",&n,&k);k--;
	rep(i,1,n)scanf("%d",&a[i]);
	int ans = a[n] - a[1] + 1;
	rep(i,1,n)a[i] = a[i + 1] - a[i] - 1;
	sort(a+1,a+n);rep(i,1,k)ans -= a[n - i];
	printf("%d\n",ans);return 0;
} 
```

---

## 作者：Kratos_Charger (赞：0)

## P7666 [JOI2018] Stove 题解

### 前言：[双倍经验](https://www.luogu.com.cn/problem/AT_joi2018ho_a)

### 题目大意

题目要求通过合理地选择炉子开启和关闭的时机，最小化炉子总的运行时间。给定一系列客人到达的时间，以及可使用的火柴数目（即开炉子的次数），需要求出最小的炉子总运行时间。

### 思路

为了简化问题，可以按照以下进行分段处理：

首先，需要计算每个客人与前一个客人之间的时间差。这是因为，炉子关闭的时机受前一个客人离开的时间影响。将每个客人到达的时间与上一个客人到达时间的差值减去 $1$（即炉子可能会在这个时间差内运行），转换成一个新的数组 $a$，这表示每对相邻客人之间的时间差。

接下来，对这些时间差进行排序，因为最小的时间差表示可以将炉子保持开启的时间最长，而不浪费火柴。所以需要选择尽可能大的时间差）来减少总的炉子运行时间。


根据火柴数目 $k$，只能开 $k$ 次炉子。如果 $k$ 小于客人的数量，那么选择 $k$ 次最长的时间段来开炉子，剩下的时间段是要合并的部分。通过计算这些时间段，能得到最小的总运行时间。

### Code


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,ans,t,tt,a[50005];
signed main(){
    cin>>n>>k;  // 输入客人数量 n 和可用火柴数 k
    cin>>tt;     // 输入第一个客人到达时间（先前的离开时间）
    for(int i=0;i<n;i++){
        cin>>t;  // 输入第 i 个客人到达时间
        a[i]=t-tt-1;  // 客人与前一个客人之间的时间差减去1，得到时间段
        tt=t;  // 更新前一个客人到达时间
    }
    sort(a,a+n-1);  // 对时间差进行排序，从小到大排列
    for(int i=0;i<n-k;i++){
        ans+=a[i];  // 选择最小的时间差，并累加到答案中
    }
    cout<<ans+n<<endl;  // 输出总的运行时间，n是因为每个客人都有一个单位时间的运行
    return 0;
}

```

---

