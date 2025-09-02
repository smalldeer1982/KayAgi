# [NOISG 2023 Qualification] Swords

## 题目描述

YH 有 $n$ 把剑，第 $i$ 把剑的攻击力为 $a_i$，防御能力为 $b_i$。

对于一把剑 $i$，如果存在一个 $j(j \not = i)$，使得 $a_i\le a_j$ 且 $b_i\le b_j$，那么 YH 就认为这把剑是无用的。反之，他就认为这把剑是有用的。

在本题中，我们保证，不可能找到两把剑 $i,j$，使得 $a_i=a_j$ 且 $b_i=b_j$。

请你帮助 YH 求出这 $n$ 把剑中，有用的剑的数量。

## 说明/提示

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$11$|$n\le500$|
|$2$|$21$|$a_i,b_i\le500$|
|$3$|$34$|$a_i=i$|
|$4$|$25$|对于每一个 $1\le i<j\le n$，有 $a_i\not =a_j$|
|$5$|$9$|无|

对于所有数据，$1\le n\le100000,1\le a_i,b_i\le10^9$。

## 样例 #1

### 输入

```
3
2 3
1 3
5 3
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
5 6
2 5
6 9
1 3
```

### 输出

```
1```

# 题解

## 作者：封禁用户 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/P10728)

作为这道题除出题人外的首个 AC ~~而且代码长度比出题人短~~，来写篇题解。

------------

直接暴力对于 $n\le 10^5$ 肯定不行，考虑优化。

首先将所有剑按照攻击力从大到小排序，如果攻击力相同则按防御力从大到小排序，这样一来任何一把剑后面的剑的攻击力都会比它小。然后对于每一把剑，如果这把剑的防御力大于之前的最大防御力，那么这把剑就是有用的，因为它没有在任何方面被后面的剑所超越，然后更新最大防御力，最后输出答案。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;

struct Node {
    int a, b;
} p[N];

bool cmp(Node x, Node y) {
    if (x.a != y.a)
        return x.a > y.a;
    return x.b > y.b;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].a >> p[i].b;
    sort(p + 1, p + 1 + n, cmp);
    int ans = 0, mx = 0;
    for (int i = 1; i <= n; i++)
        if (p[i].b > mx)
            ans++, mx = p[i].b;
    cout << ans;
    return 0;
}
```

---

## 作者：FurippuWRY (赞：5)

注意到一把剑存在两个元素，考虑用 `pair`。

定义 `pair<int, int> p[100001];`，将题目中的 $a_i$ 与 $b_i$ 分别存入 `p[i].first` 与 `p[i].second`，然后进行排序。因为 `pair` 自带的排序规则是按照 `first` 成员进行升序排序，所以是按照攻击力大小排序。接着定义变量 `ans` 与 `maxn`，分别代表有用剑数量与当前最大防御力，然后从攻击力最大的元素开始遍历（这样第 $i$ 把剑的攻击力一定大于后边所有的剑，所以只需考虑防御力），假如碰到第 $i$ 把剑的防御力大于 `maxn`，`ans` 自增，更新最大值为第 $i$ 把剑的防御力。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ans, maxn;
pair<int, int> p[100001];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> p[i].first >> p[i].second;
    }
    sort(p + 1, p + 1 + n);
    for (int i = n; i; --i) {
    	if (p[i].second > maxn) {
    		ans++;
    		maxn = p[i].second;
    	}
    }
    cout << ans;
    return 0;
}
```

---

## 作者：XXh0919 (赞：2)

简单的一道题，主要就是结构体排序。

因为要使剑有用，所以排序时可以优先选择攻击力最大的剑，若两者攻击力相等，就按防御力从大到小进行排序。所以在最后的判断里就只需要比较防御力的大小，因为排完序后攻击力是一定能保证从大到小的。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pi pair<int,int>
#define mkp(a,b) make_pair((a),(b))
using namespace std;
const int N=3e6+15,inf=1e9;

int n,ans,maxx;

struct node{
	int fight,defense;
}a[N];

bool cmp(node x,node y){
	return x.fight>y.fight||(x.fight==y.fight&&x.defense>y.defense);
}

signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n){
		cin>>a[i].fight>>a[i].defense;
	}
	sort(a+1,a+n+1,cmp);
	rep(i,1,n){
		if(a[i].defense>maxx){
			maxx=a[i].defense;
			++ans;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：King_and_Grey (赞：2)

## [题目传送门](/problem/P10728)

首先这一题 $1 \le n\le 10 ^ 5$，直接打暴力，结果[会超时。](https://www.luogu.com.cn/record/164867669)

### 思路讲解

首先定义一个结构体，输入第 $a_i$ 把剑的攻击值和防御值，然后先按攻击值排序，然后按防御值排序（从大到小排序），遍历结构体，如果这把剑的防御值比之前最大防御值大，那么这把剑就是有用的，更新一下最大防御值，最后输出答案。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 10;
struct node{
    int attack,defense;//attack为攻击，defense为防御
}a[N];

bool cmp(node x, node y) {
    if (x.attack != y.attack){
        return x.attack > y.attack;
    }
    return x.defense > y.defense;
}
int n,ans,Max;//Max:之前的最大防御力
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin >> n;
    for (int i = 1;i <= n;i++){
        cin >> a[i].attack >> a[i].defense;
    }
    sort(a + 1,a + 1 + n,cmp);//从大到小排序
    for (int i = 1;i <= n;i++){
        if (a[i].defense > Max){
            ans++;//答案增加
			Max = a[i].defense;//更新最大防御值
        }
    }
    cout << ans << endl;
    return 0;
}
```
[通过记录。](https://www.luogu.com.cn/record/164873424)

管理员大大求过！QwQ

---

## 作者：JYX0924 (赞：1)

对于这道题，我们可以先对所有剑按照攻击力从小到大排个序，然后在每一把剑后面找比它防御力强的剑。如果找到了，说明它是无用的。

我们可以用 $dp_{i}$ 表示以 $a_{i}$ 结尾，从 $a_{n}$ 开始的区间最大值，则 $dp_{i}=\max\{a_{i},dp_{i+1}\}$。这样就可以通过此题了。

下面是我的 AC 代码。

```c
#include<bits/stdc++.h>
using namespace std;
int n,a,b,dp[100005],ans;
pair<int,int> tt[100005];
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b; tt[i].first=a,tt[i].second=b;
	}
	sort(tt+1,tt+n+1); dp[n]=tt[n].second;
	for(int i=n-1;i>=1;i--) dp[i]=max(tt[i].second,dp[i+1]);
	for(int i=1;i<=n;i++)
	{
		if(tt[i].second<=dp[i+1]) ans++;
	}
	cout<<n-ans;
	return 0;
}
```
谢谢大家！！！

---

## 作者：Vct14 (赞：1)

考虑使用结构体。我们暴力枚举所有剑两两之间的关系显然会 TLE，因此我们将剑的攻击力排序，这样我们可以确保后面的剑一定强于前面的剑。如果后面的剑的防御能力也不如前面的剑，那么它就是无用的。特别地，如果两把剑的攻击力相等，那么我们就按防御能力排序，防御能力弱的就是无用的剑。

```c++
#include<bits/stdc++.h>
using namespace std;

struct Sword{
    int ATK,DEF;
}s[100002];

bool cmp(Sword a,Sword b){
	if(a.ATK==b.ATK) return a.DEF<b.DEF;
    return a.ATK<b.ATK;
}

int main(){
    int n;cin>>n;
    for(int i=1; i<=n; i++) cin>>s[i].ATK>>s[i].DEF;
    sort(s+1,s+1+n,cmp);
    int MaxDEF=0,swords=0;
    for(int i=n; i>=1; i--) if(s[i].DEF>MaxDEF) swords++,MaxDEF=s[i].DEF;
    cout<<swords;
    return 0;
}
```

---

## 作者：letianJOE (赞：1)

## 一些闲话

下午偶然间看到这一题，还能写题解。

本来没啥思路，跟同学踢完球突然茅塞顿开了。

对了，NOISG 是新加坡的全国赛事，怎么这么水。

## 题目大意

有 $n$ 个剑，每个剑都有攻击和防御属性。

一个剑只要两个属性都小于等于另外一个剑，那么这个剑就是无用的，否则这个剑就是有用的。

求有用的剑的个数。

## 思路

题目中需要两个属性都小于。

那么如果我们保证 $a$ 剑的攻击属性小于 $b$ 剑，那么我们就只需要判断一个属性了。

## 实现

从这方面考虑。

我们想到可以先对攻击属性作为第一关键字倒序排序，那么排在后面的剑攻击属性就一定小于等于排在前面的剑。

那么我们在对攻击属性相同的进行防御属性的第二关键字倒序排序，保证不会有无用的剑排在一个有用的剑前面的位置，导致多一个答案。

这样排序后，我们就可以对答案开始处理了。

我们遍历排序后的数组。

设一个最大值，后面的防御属性必须要比最大值大才是有用的剑，更新最大值。

因为如果后面的防御属性比最大值小，那么它不仅攻击属性更小，而且防御属性也更小。那这肯定就是一个无用的剑了。

## CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5;
const int inf=0x7fffffff;
struct node
{
	int a,b;
}sword[N+5];
int n;
int ans,maxx;
bool cmp(node sword1,node sword2)
{
	if(sword1.a==sword2.a)
		return sword1.b>sword2.b;
	return sword1.a>sword2.a;
}
main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>sword[i].a>>sword[i].b;
	sort(sword+1,sword+n+1,cmp);
	for(int i=1;i<=n;i++)
		if(sword[i].b>maxx)
		{
			ans++;
			maxx=sword[i].b;
		}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：donnieguo (赞：1)

## 题意简述

YH 有 $n$ 把剑，对于第 $i$ 把剑有两个数值，分别是 $a_i$ 和 $b_i$。如果其他 $n-1$ 把剑没有任何一把剑 $j$ 满足 $a_i \leq a_j$ 且 $b_i \leq b_j$，则这把剑是有用的，否则这把剑是无用的。求所有有用的剑的数量。

## 思路

首先看到这题我的第一反应就是 $\Theta(n^2)$，暴力枚举每一个 $i$ 和 $j$，求数量，但是 $n \leq 10^5$，所以 $\Theta(n^2)$ 的做法肯定会 TLE。

考虑优化。

这时候肯定有人会说，答案不就是 $2$ 吗？$a_i$ 的最大值以及 $b_i$ 的最大值。但仔细一想就会发现这个结论是错误的。

考虑如下 hack 数据：

```
3
1 3
2 2
3 1
```

很明显，答案是 $3$，不是 $2$。

问题就是 $j$ 不能每次都保证 $a_i \leq a_j$ **且** $b_i \leq b_j$。

但是这个思路也能给我们一些启发：从最大值和最小值入手。于是自然而然想到排序。

对所有的剑以 $a_i$ 为第一关键字，$b_i$ 为第二关键字进行排序，这样就能保证序号大的剑的 $a_i$ 和 $b_i$ 一定更大。

令 $\text{maxn}$ 为 当前的最大 $b_i$，然后我们倒着遍历一遍所有的剑，如果这一把剑的 $b_i$ 比 $\text{maxn}$ 更大，则说明当前的第 $i$ 把剑虽然 $a$ 比前面的剑更小，但是 $b$ 比所有前面的剑都更大，所以这把剑一定是合法的。然后更新 $\text{maxn}$，将答案 $+1$。

## AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, ans;

struct sword {
	int a, b;
} sw[100010];

bool cmp(sword x, sword y) {
	if (x.a != y.a) return x.a < y.a;
	return x.b < y.b;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> sw[i].a >> sw[i].b;
	sort(sw + 1, sw + n + 1, cmp);
	int maxn = 0;
	for (int i = n; i >= 1; i--)
		if (maxn < sw[i].b) {
			ans++;
			maxn = sw[i].b;
		}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：hard_learn (赞：0)

# 简要题意
 求出这 $n$ 把剑中，有用的剑的数量。
# 思路
- 首先要将剑进行排序，按照攻击力升序排序，如果攻击力相同则按照防御力升序排序。
- 然后进行从 $n$ 到 $1$ 的遍历，因为剑的攻击力已经是按 $1$ 到 $n$ 升序排好的，所以 $n$ 到 $1$ 就是降序排列，因此剑的攻击力一定会比后面的低或等于，所以只需要将剑的防御力进行比较看是否有用即可。
# 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct st{
	int a,b;
}s[100005];
bool cmp(st a,st b){// 按照攻击力升序排序，如果攻击力相同则按照防御力升序排序
	if(a.a==b.a){
		return a.b<b.b;
	}
	else{
		return a.a<b.a;
	}
}
signed main(){
	cin>>n;// 输入剑的数量
	for(int i=1;i<=n;i++){
		cin>>s[i].a>>s[i].b;
	}
	sort(s+1,s+n+1,cmp);// 排序剑
	int ans=0;
	int cnt=-1;
	for(int i=n;i>=1;i--){
		int dd=s[i].b; 
		if(s[i].b>cnt){
			ans++;
			cnt=s[i].b;
		}
	}//22~29行 计算有用的剑的数量
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 题面简述
对于任意一把剑，有一把剑两方面都不比他弱，则称他为无用的。

反之，它是有用的。
## 思路
$n \le 100000$ 显然不能枚举每一把，考虑优化。

可以将每把剑按攻击或防御排序，比如按攻击排序，大的靠前。

举个栗子：
```
n=4
3 3
1 4
2 2
4 1
```
排序：
```
n=4
4 1
3 3
2 2
1 4
```
不难发现，每往后一把剑，攻击永远不会比前面的强。

于是，但凡他的防御没之前最高的高，他就没用了。

接下来就是写代码了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxf=0,ans;
struct gf{
	int g,f;
}a[100100];//数组
bool cmp(gf x,gf y){
	if(x.g!=y.g){
		return x.g>y.g;
	}
	return x.f>y.f;
}//排序依据
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].g>>a[i].f;//读入
	sort(a+1,a+n+1,cmp);//排序v
	for(int i=1;i<=n;i++){
		if(a[i].f>maxf){//防御比前面强
			maxf=a[i].f;
			ans++;//有用的增加
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
将 $n$ 把剑进行排序，如果两把剑的攻击力不一样，则将攻击力更大的排前面，否则按照防御力更大的排前面。

最后从前往后遍历排好序的数组，如果当前剑的防御力大于当前最大的防御力，则说明这把剑是有效的，答案 $+1$，并且将最大的防御力更新成当前剑的防御力。

最后输出答案。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#define N 100005
struct Node{
	int a,b;
}a[N];
int cnt,max_b;
int main(){
	int n;
	std::cin>>n;
	for(int i=1;i<=n;i++)
		std::cin>>a[i].a>>a[i].b;
	std::sort(a+1,a+1+n,[](Node x,Node y){return x.a!=y.a?x.a>y.a:x.b>y.b;});
	for(int i=1;i<=n;i++){
		if(a[i].b>max_b){
			cnt++;
			max_b=a[i].b;
		}
	}
	std::cout<<cnt; 
}
```

---

