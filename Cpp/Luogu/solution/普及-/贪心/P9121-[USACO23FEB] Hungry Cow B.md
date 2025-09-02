# [USACO23FEB] Hungry Cow B

## 题目描述

Bessie 是一头饥饿的奶牛。每天晚餐时，如果谷仓中有干草，她会吃掉一捆干草。为了防止 Bessie 挨饿，有些天 Farmer John 会在早晨（晚餐之前）送来一些干草。具体地说，在第 $d_i$ 天，Farmer John 送来了 $b_i$ 捆干草（$1 \leq d_i \leq 10^{14}, 1 \leq b_i \leq 10^9$）。

请计算 Bessie 在前 $T$ 天内共吃掉了多少捆干草。

## 样例 #1

### 输入

```
1 5
1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
2 5
1 2
5 10```

### 输出

```
3```

## 样例 #3

### 输入

```
2 5
1 10
5 10```

### 输出

```
5```

# 题解

## 作者：zhlzt (赞：15)

### 题目
- 有一位农场主约翰，他有一只饥饿的牛贝西。
- 每一天晚上，如果农场里有至少 $1$ 堆干草，那么贝西吃且仅吃 $1$ 堆干草。
- 有 $n$ 个事件，第 $i$ 个事件表示第 $d_i$ 天早晨约翰搬运了 $b_i$ 堆干草到农场。
- 求第 $1\thicksim t$ 天贝西共吃掉干草堆的数量。
- $1\le n\le 10^{5}$，$1\le t\le10^{14}$，$1\le d_i\le 10^{14}$，$1\le b_i\le 10^{9}$。
- $1\le d_1<d_2<\cdots<d_n\le t$。

### 模拟做法
设 $sum$ 为目前农场里剩余干草堆的数量，$ans$ 为目前贝西共吃掉干草堆的数量。

对于每个 $i$，我们不妨设 $pos$ 为第 $d_{i-1}\thicksim d_{i}-1$ 天贝西共吃掉干草堆的数量，则有 $pos=\min(sum,d_i-d_{i-1})$，并执行 $sum\gets sum-pos$ 与 $ans\gets ans+pos$，最后不能忘了执行 $sum\gets sum+b_i$。

千万要注意，第 $d_n\thicksim t$ 天共吃掉干草堆的数量还没加上，所以最终要输出 $ans+\min(sum,t-d_n+1)$，而不是直接输出 $ans$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,sum,ans,pos,d[100010],b[100010];
int main(){
	scanf("%lld%lld",&n,&t);
	for(long long i=1;i<=n;i++){
		scanf("%lld%lld",&d[i],&b[i]);
		pos=min(sum,d[i]-d[i-1]);
		sum-=pos,ans+=pos,sum+=b[i];
	}
	printf("%lld",ans+min(sum,t-d[n]+1));
	return 0;
}
```

---

## 作者：Loser_Syx (赞：6)

## 思路

每进行一次新的补粮之前，要计算前 $d_i - d_{i-1}$ 天能吃多少粮食，然而前 $d_i - d_{i-1}$ 天只能吃 $d_i - d_{i-1}$ 个单位的粮食或剩余粮食。当退出循环后，还要计算 $T - d_N + 1$ 天时候能吃多少粮食，最后输出总和即可。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#define int long long
#define f(X, Y, Z) for(int i = X; i <= Y; i += Z)
#define F(X, Y, Z) for(int i = X; i >= Y; i -= Z)
#define debug puts("I AK USACO!")
using namespace std;
int d[114514], b[114514];
main(){
	int n, t, food = 0, ans = 0;
	scanf("%lld%lld", &n, &t);
	f(1, n, 1){
		scanf("%lld%lld", &d[i], &b[i]);
		if(food >= d[i] - d[i - 1]){//如果食物能够支撑这几天的食物
			ans += d[i] - d[i - 1];
			food -= d[i] - d[i - 1];
		}else{//其他情况直接把食物吃空
			ans += food;
			food = 0;
		}
		food += b[i];//加入剩余粮食
	}
	if(food >= t - d[n] + 1){//如果这些食物能够支撑 t - d[n] 这几天的食物
		ans += t - d[n] + 1;
	}else{//其他情况直接把食物吃空
		ans += food;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：watergod (赞：6)

## P9121 Hungry Cow 题解

[题目传送](https://www.luogu.com.cn/problem/P9121)

注意题目中数据比较大，要开 long long。

**主要思路：**

建立一些指针变量

假装建立一个大小为 $n$ 的数组，用 $days$ 和 $t$ 两个指针来不停变化数组内到底有没有稻草块可以吃，相当于是一个模拟的过程。

其中最重要的就是用一个变量来表示每次可以增加的稻草数，否则代码就会非常长。

具体的分析见下面。

**主要代码分析：**
```cpp
if(days < a){
	days = a;
}
```
此时的 $days$ 表示当前的天数，当有一些稻草进来且比天数要小的时候，即 $days<a$ 的时候，我们就可以假装把数组内的前 $days$ 个值都设为有稻草可以放，那么这个时候直接把 $days$ 跳过前 $a$ 项（因为前面 $a$ 项已经有稻草可吃了）

```cpp
long long diff = min(t - days + 1,sum);
```
其中 $t-days+1$ 表示该轮一共可以放进的稻草数，此时的 $sum$ 就是目前有的稻草。

- 当 $sum<t-days+1$ 时，也就是当我现在可以放的稻草数没有总天数的时候，这个时候就只能放入现在有的稻草数。

- 当 $sum>t-days+1$ 时，也就是我现在可以放的稻草数大于总天数，我也只能放入总天数个数的稻草数。

所以 $diff$ 变量就是用来表示每一轮可以吃到的稻草，值应该赋为目前有的稻草和可以放进的稻草的最小值，之后就可以直接对每个变量进行操作了。

所以通过比较 $sum$ 和 $t-days+1$ ，就可以准确的得出我现在要放入的稻草个数，后面就可在 $ans$ 里面改变可以放入的稻草数了。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,t; //n表示送n轮稻草,t表示在前t天可以吃到的稻草 
	cin >> n >> t;
	long long a,b; //a表示在第a天送来稻草,b表示送来稻草的个数 
	long long days = 1,sum = 0, ans = 0; //同代码分析
	for(int i=0;i<n;i++){ // 循环n-1轮判断
		cin >> a >> b; //第1行以后的输入
		sum += b; //总共的稻草数，开始赋值为 b(第一轮的稻草) 
		if(days < a){
			days = a;
		} //如果此时的天数比一共的稻草要小，直接把目前天数覆盖满 
		long long diff = min(t - days + 1,sum);
		// t和days可以理解成指针，对着每一天进行放入 
		sum -= diff; 
		ans += diff;
		days += diff;	
		// 第一种情况：当t-days+1比sum大的时候，即总天数要比sum大，此时只能放sum天进去
		// 先把sum中减去放的，已经放的答案++,再把天数跳过这几天
		// 第二种情况：当t-days+1比sum小的时候，即sum比总天数还要多余
		// 此时撑死了只能放总天数，同第一种情况，sum-,答案++,天数依然直接跳过（此时直接换到第n+1天了） 
	}	 
	cout << ans << endl;
	return 0;
}
```

[AC代码](https://www.luogu.com.cn/record/103822817)

---

## 作者：Nuyoah_awa (赞：5)

### 题目大意

有一个初始没有干草的仓库，如果仓库中有干草，Bessie 每天吃掉一捆干草，有 $n$ 次指令，表示 Farmer John 会在第 $d_i$ 天在仓库中放入 $b_i$ 捆干草（$1 \le d_1 \le d_2 \le … \le d_N \le T$）。求 Bessie 一共需要吃多少干草。

### 题目分析

本题的思路是模拟。

思路一：我们可以按照时间模拟，对于每次指令计算它与上一个指令之间有几天 Bessie 需要吃草。

思路二：我们可以记一个值 $last$ 表示剩余干草 Bessie 会在第几天吃完，每次输入一条新指令时更新 $last$。

如果所有指令进行完后，$last > T$ 最终 Bessie 需要吃的干草数就是 $\sum_{i = 1}^{i \le n} b_i - (last - T - 1)$；否则，答案为 $\sum_{i = 1}^{i \le n} b_i$。

### code
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long n, T, d, b, last, ans;
int main()
{
	cin >> n >> T;
	for(int i = 1;i <= n;i++)
	{
		cin >> d >> b;
		if(last < d)
			last = d + b;
		else
			last += b;
		ans += b;
	}
	if(last > T)
		ans -= (last - T - 1);
	cout << ans;
	return 0;
}
```

---

## 作者：ivyjiao (赞：2)

题意：奶牛每天晚上吃一捆草，如果没有就不吃，农夫在 $d_i$ 天早上会给牛送草，问奶牛 $T$ 天吃了多少捆草。

思路：由于 $T$ 太大，考虑 $O(n)$ 解法。

如果送草之后现在的草能吃到下一次送草的时候，就每天都吃（也就是吃 $d_{i+1}-d_i$ 份），否则把粮仓里的所有草吃完。

注意：要特判最后一天，要开 `long long`。

代码：

```cpp
#include<iostream>
using namespace std;
long long n,t,a[100010],b[100010],cnt,ans;
int main(){
    cin>>n>>t;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    a[n+1]=t;
    for(int i=1;i<=n;i++){
        cnt+=b[i];
        ans+=min(a[i+1]-a[i],cnt);
        cnt=max(cnt-(a[i+1]-a[i]),0ll);
    }
    if(cnt) ans++;
    cout<<ans;
}

```

---

## 作者：incra (赞：2)

## 题解
注意到 $n$ 很小，$d_i$ 很大，所以我们可以考虑 $(d_1,d_2),(d_2,d_3),\dots,(d_n,T)$ 这几段时间之间的答案。

假设当前在第 $i$ 个位置，要求 $(d_i,d_{i+1})$ 这一段的答案，如果 $b_i>=d_{i+1}-d_i+1$ 那肯定是够吃的，并且还有 $b_i-(d_{i+1}-d_i+1)$ 的多余，答案加上 $d_{i+1} - d_i+1$，否则，把能吃的都吃了，答案加上 $b_i$。

考虑到会有多余的草料可以延续到后面继续吃，所以我们在用一个变量记录之前剩下了几捆草。最终还要特判一下如果某一个点 $d_i$，它能吃到 $T$ 天以后的话，那么就只能吃到 $T$ 天后退出。
## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define l first
#define r second
using namespace std;
typedef long long LL;
typedef pair <LL,LL> PLL;
const int N = 100010;
int n;
LL t;
PLL a[N];
int main () {
	cin >> n >> t;
	LL ans = 0,last = 0,last_pos = 0;
	for (int i = 1;i <= n;i++) {
		LL d,x;
		cin >> d >> x;
		if (last >= d - last_pos) {
			ans += d - last_pos;
			last -= d - last_pos;
		}
		else {
			ans += last;
			last = 0;
		}
		last += x;
		last_pos = d;
		if (d + x - 1 > t) {
			ans += t - d + 1;
			cout << ans << endl;
			return 0;
		}
	}
	cout << ans + min (last,t - last_pos) << endl;
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：2)

假设第 $x$ 次运送干草的时间为 $a_1$，运来了 $l$ 捆干草。第 $x+1$ 次运送干草的时间为 $a_2$，前 $a_1-1$ 天剩下了 $k$ 捆干草。那么如果 $k+l \ge a_2-a_1$，说明当前剩余的干草数足够第 $a_1$ 天到第 $a_2-1$ 天吃。这几天贝茜每天都能吃到干草。如果 $k+l<a_2-a_1$，说明剩下的这些干草不够第 $a_1$ 天到第 $a_2-1$ 天吃，那么贝茜就只有 $k+l$ 天有干草吃了。

第 $T$ 天需要特判一下。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,T,total,D,ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	n=read();T=read();
	D=read();total=read();
	for(int i=2;i<=n;i++){
		int d,b;d=read();b=read();
		if(total>=d-D)total-=(d-D),ans+=(d-D);
		else ans+=total,total=0;
		D=d;total+=b;
	}
	int d=T;
	if(total>=d-D)total-=(d-D),ans+=(d-D);
	else ans+=total,total=0;
	if(total)ans++;//特判
	cout<<ans;
	return 0;
}

```

---

## 作者：zhuweiqi (赞：2)

思路：注意到此题的数据范围除了 $N$ 以外都很大，所以我们就假设时间复杂度为 $O(n)$，从 $N$ 入手：每运来一批干草，我们肯定要先把它吃光，如果在下一批干草运来之前吃不完的话，那么多出来的就可以放在下一批干草里一起吃，还要注意，最多只能吃 $T$ 天干草！如果当前的库存足以维持到第 $T$ 天那就可以直接退出程序了。上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n;
}
ll d[100002],b[100002];
int main(){
	ll n=read(),t=read(),ans=0;
	for(int i=1;i<=n;i++) d[i]=read(),b[i]=read();
	d[n+1]=t+1;
	for(int i=1;i<=n;i++){
		if(d[i]+b[i]>t){
			ans+=t-d[i]+1;
			break;
		}
		if(b[i]<=d[i+1]-d[i]) ans+=b[i];
		else {
			ans+=d[i+1]-d[i];
			b[i+1]+=b[i]-d[i+1]+d[i];
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：minVan (赞：1)

**题目大意**

在第 $d_i$ 天，有 $b_i$ 份粮草给 $\text{Bessie}$，$\text{Bessie}$ 每天最多吃一份，问前 $t$ 天 $\text{Bessie}$ 能吃多少天。

**解题思路*

$b$ 数组是用来存前 $t$ 天内所有不重复的区间 `b[i].l` 为第 $i$ 个区间的左端点，`b[i].r` 为第 $i$ 个区间的右端点。

对于每一个 $i$，当 $d_i \le t$ 时，`b[i].l` 为 `max(a[i].l, b[i - 1].r + 1)`，`b[i].r` 为 `min(t, b[cnt].l + a[i].r - 1)`。

最后遍历所有区间，累加所有区间长度即 `b[i].r - b[i].l + 1`。

**增加区间部分代码**

```cpp
if(a[i].l <= t) {
	b[++cnt].l = max(a[i].l, b[i - 1].r + 1);
	b[cnt].r = min(t, b[cnt].l + a[i].r - 1);
}
```

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int N = 1e5 + 5;
struct node {
    int l, r;
} a[N], b[N];
int n, t, ans, cnt;
signed main() {
    cin >> n >> t;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
        if(a[i].l <= t) {
            b[++cnt].l = max(a[i].l, b[i - 1].r + 1);
            b[cnt].r = min(t, b[cnt].l + a[i].r - 1);
        }
    }
    for(int i = 1; i <= cnt; i++) {
        ans += b[i].r - b[i].l + 1;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

## 题目翻译

- 有一头奶牛，如果能吃干草的话，每天 **会且只会** 吃一捆甘草。
- 有 $n$ 天，对于这些 $d_i$ 天农场主会送来 $b_i$ 捆干草。
- 求 $t$ 天前一共会吃多少捆干草。仓库一开始是空的。

## 思路简述

可以发现，$t$ 的值非常的大，于是考虑通过干草的变化来求最终答案。

因为在没有变化的时候，奶牛都会吃一捆干草，当干草不够了，它也没办法，只能在那里等。于是可以得出模拟 $n$ 次更改即可。定义一个变量 $last$ 来储存现在还剩多少干草块，对于每个 $b_i$，加上即可。

接下来的重点即在于如何判断吃不吃完：

这其实也很简单，当两次送干草的时间相差大于等于 $last$ 时，干草块就会吃完，吃的块数即为剩余数。

当相差小于 $last$ 时，干草块不会吃完，这 $d_i-1$ 到 $d_i$ 天每天都会吃一捆。

记得将 $last$ 减去吃的量，加上送的量。

对于 $d_n$ 以后的天数，我们并没有管，于是需要我们特殊处理一下。

## AC 代码（橙题没必要 ctj 了吧，应该很好想的）

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//t 那么大明摆着让你开long long
ll n,t,ans,last,d[100050],b[100050];
int main(){
	cin>>n>>t;
	for(ll i=1;i<=n;i++){
		cin>>d[i]>>b[i];//边输入边处理，简洁一点
		if(last>=d[i]-d[i-1]){//够吃
			last-=d[i]-d[i-1];
			ans+=d[i]-d[i-1]; 
		}else{//不够
			ans+=last;
			last=0;
		}
		last+=b[i];//加上，别忘
	}
	if(last>t-d[n])cout<<ans+t-d[n]+1;//对于我们没有循环到的最后这几天要进行特殊处理，请思考为什么这里要加上 1
	else cout<<ans+last;
	return 0;
}
```


---

## 作者：AKPC (赞：0)

### 题意
奶牛每天吃一捆草，如果没有了，那就不吃。$d_i$ 天会增加 $b_i$ 捆草，问奶牛 $T$ 天能吃多少捆。
### 思路
显然考虑 $\text O(n)$ 做法。

如果送来草的时候粮仓没有空，就不浪费存着的草，把新的草等到粮仓空了否则再放。最后计算答案：若 $d_i+b_i>T$，则 $ans$ 只要加上剩下的天数就行了，反之每次直接加上 $b_i$ 即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,t,ans,now=0,d[100005],b[100005];
void update(int i){
	if (now>d[i]) d[i]=now;
	now=d[i]+b[i];
	if (d[i]+b[i]>t) ans+=t-d[i]+1;
	else ans+=b[i];
}
signed main(){
	cin>>n>>t;
	for (int i=1;i<=n;i++){
		cin>>d[i]>>b[i];
		update(i);
		if (now>t) break;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Bulyly (赞：0)

## Solution

- 因为送草次数的范围是极小的，我们很容易想到，枚举每次送草，来判断到下一次送草时，奶牛的饥饿情况。

- 具体实现：因为可能上次送的草没有吃完，需要维护每次送草时草的份数，即剩余的加上送来草的数量。然后判断到下一次送草期间的情况，草的数量如果大于相隔天数，则每天都能吃，并记录剩余多少，如果草的数量小于相隔天数，则只能吃草的数量那么多天，当然剩余为零。这些都是非常好维护的。具体实现，详见代码。
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#define int long long

using namespace std;

const int N=1e5+10;
map<int,int> d,b;
int n,m;

signed main()
{
	scanf("%lld%lld",&n,&m);
	int last=0;
	int t,x;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&t,&x);
		if(t>m)  d[last]=m+1;
		else d[last]=t;
		b[t]+=x;
		last=t;	
	}
	d[t]=m+1;
	int day=0,rest=0;
	for(int i=d[0];i<=m;)
	{
		int tp=rest+b[i];
		if(tp<d[i]-i)
		{
			day+=tp;
			rest=0;
		}
		else
		{
			day+=d[i]-i;
			rest=tp-d[i]+i;
		}
		i=d[i];
	}
	printf("%lld\n",day);
	
	return 0; 
}
```
完结撒花~

---

## 作者：chlchl (赞：0)

来发超级简短的。

## Solution
$T$ 很大，$n$ 比较适中，显然考虑 $O(n)$ 的做法。

定义一个变量 $now$，表示当前送来的草最多够吃到多少天。

若在第 $i$ 批草堆送来之前，已经能够撑到 $d_i$ 天，那么这批干草堆将被平移至第 $now$ 天再开始吃。

接着更新 $now$。设 $ans$ 为最后答案，那么每次都加上 $b_i$ 即可。注意，若 $d_i+b_i>T$，则 $ans$ 只要加上剩下的天数就行了。

简单题，放在 Cu 的 T1 还可以。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e5 + 10;
int n;
ll t, ans, d[N], b[N];

int main(){
	scanf("%d%lld", &n, &t);
	ll now = 0;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld", &d[i], &b[i]);
		if(now > d[i])
			d[i] = now;//平移
		now = d[i] + b[i];//更新now
		if(d[i] + b[i] > t)//吃到大于 t 天了
			ans += t - d[i] + 1;//吃完剩下天数就行了
		else
			ans += b[i];//更新答案
		if(now > t)
			break;//吃到第 t 天了，剩下送来的就没意义了
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

