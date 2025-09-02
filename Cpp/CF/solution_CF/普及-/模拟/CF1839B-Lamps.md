# Lamps

## 题目描述

You have $ n $ lamps, numbered by integers from $ 1 $ to $ n $ . Each lamp $ i $ has two integer parameters $ a_i $ and $ b_i $ .

At each moment each lamp is in one of three states: it may be turned on, turned off, or broken.

Initially all lamps are turned off. In one operation you can select one lamp that is turned off and turn it on (you can't turn on broken lamps). You receive $ b_i $ points for turning lamp $ i $ on. The following happens after each performed operation:

- Let's denote the number of lamps that are turned on as $ x $ (broken lamps do not count). All lamps $ i $ such that $ a_i \le x $ simultaneously break, whether they were turned on or off.

Please note that broken lamps never count as turned on and that after a turned on lamp breaks, you still keep points received for turning it on.

You can perform an arbitrary number of operations.

Find the maximum number of points you can get.

## 说明/提示

In first test case $ n = 4 $ . One of ways to get the maximum number of points is as follows:

- You turn lamp $ 4 $ on and receive $ b_4 = 13 $ points.
- The number of lamps that are turned on is $ 1 $ , so all lamps with $ a_i \le 1 $ (namely lamps $ 2 $ , $ 3 $ and $ 4 $ ) break. Lamp $ 4 $ is no longer turned on, so the number of lamps that are turned becomes $ 0 $ .
- The only lamp you can turn on is lamp $ 1 $ , as all other lamps are broken. You receive $ b_1 = 2 $ points for turning it on.
- The number of lamps that are turned on is $ 1 $ . As $ a_1 = 2 $ , lamp $ 1 $ doesn't break.

Your receive $ 13 + 2 = 15 $ points in total. It can be shown that this is the maximum number of points you can get, so the answer for the first test case is $ 15 $ .

In the second test case, one of the ways to get the maximum number of points is as follows:

- On the first operation you turn on lamp $ 4 $ and receive $ 2 $ points. No lamps break after the first operation.
- On the second operation you turn on lamp $ 3 $ and receive $ 5 $ points. After the second operation, there are $ 2 $ lamps turned on. As $ a_3 \le 2 $ , lamp $ 3 $ breaks.
- On the third operation, you turn on lamp $ 1 $ and receive $ 4 $ points.
- On the fourth operation, you turn on lamp $ 5 $ and receive $ 3 $ points. After that there are $ 3 $ lamps turned on: lamps $ 1 $ , $ 4 $ and $ 5 $ . Lamps $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ simultaneously break, because for all of them $ a_i \le 3 $ .

You receive $ 2 + 5 + 4 + 3 = 14 $ points in total. It can be shown that this is the maximum number of points you can get.

In the third test case, one of the ways to get the maximum number of points is as follows:

- Turn the lamp $ 3 $ on and receive $ 4 $ points. Lamps $ 1 $ and $ 3 $ break.
- Turn the lamp $ 2 $ on and receive $ 4 $ points.
- Turn the lamp $ 6 $ on and receive $ 3 $ points. Lamp $ 6 $ breaks.
- Turn the lamp $ 4 $ on and receive $ 4 $ points.
- Turn the lamp $ 5 $ on and receive $ 5 $ points. Lamps $ 2 $ , $ 4 $ and $ 5 $ break.

You receive $ 4 + 4 + 3 + 4 + 5 = 20 $ points in total. It can be shown that this is the maximum number of points you can get.

## 样例 #1

### 输入

```
4
4
2 2
1 6
1 10
1 13
5
3 4
3 1
2 5
3 2
3 3
6
1 2
3 4
1 4
3 4
3 5
2 3
1
1 1```

### 输出

```
15
14
20
1```

# 题解

## 作者：snowingbird (赞：3)

# CF1839B题解
## 题目大意
有 $n$ 盏灯，每盏灯有坏掉、亮、暗这 $3$ 种状态。一开始每盏灯都是暗的。第 $i$ 盏灯有两个值 $a_i$ 和 $b_i$。可以进行若干次操作，每次操作都可以选择一盏不亮的灯将其点亮，并获得 $b_i$ 的分数。每次操作结束后，记录有 $x$ 盏灯亮着，则所有 $a_i≤x$ 的灯 $i$ 都会损坏。求能得到的最大分数。
## 解题思路
这题很明显考察贪心。
灯的 $a$ 越小，灯就更容易坏掉，因为坏掉的灯无法对分数有任何改变，所以尽量要在它们坏掉之前点亮得分。
所以先将所有的灯按 $a$ 从小到大排序，模拟依次点亮的过程。注意：如果有相同 $a$ 值的灯，也就是说只能点亮一个（毕竟如果你这时候又点亮了一个，那么 $x$ 就会大于等于 $a$ ，灯就会坏）那依照常理可知，一定要选$b$ 最大的一个，这个地方排序要注意。

在模拟这个过程的时候，处理坏灯的这个步骤，就需要用到**队列**来实现，因为前一步是按照 $a$ 从小到大点亮的，那么灯坏掉的顺序也是 $a$ 从小到大的，符合 “FIFO” （先进先出）队列的特点。所以我们把点亮的灯全部压入，只需观察队首灯的 $a$ 和 $x$ （即队列的大小）的大小关系，就可以模拟整个过程了。
## AC代码（附带注释）
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
//(WA)别漏测试数量！
struct lamp{
	int a,b;
}lamps[200010];
//用了一个结构体来定义每一个灯，所以下面要多写一个cmp用来排序
queue<int>q;
//存储每个灯的a，所以是int类型
bool cmp(lamp a,lamp b){
	if(a.a<b.a)return 1;
	if(a.a==b.a){
		if(a.b>b.b)return 1;
		return 0;
	}
	return 0;
} 
//(WA)这里排序要注意细节；有两个部分的排序
int main(){
	cin>>t;
	while(t--){
		while(!q.empty()){
			q.pop();
		}
		long long ans=0;
//(WA)初始化（因为有多组数据）
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>lamps[i].a>>lamps[i].b;
		}
		sort(lamps+1,lamps+n+1,cmp);
//(WA)别漏了排序，否则辛辛苦苦写的cmp就没用了
		int mx=0;
		for(int i=1;i<=n;i++){
			int x=q.size();
			mx=max(mx,x);
			while(!q.empty()&&q.front()<=x){
//(TLE+RE)这里的!q.empty一定不能忘！
				q.pop();
				x--; 
			}
			if(lamps[i].a<=mx)continue;
			ans+=lamps[i].b;
			q.push(lamps[i].a);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
## 致谢
感谢管理员能抽出一点时间来审核我的题解

感谢大佬们能抽出一点时间来修改我的题解

感谢我自己能抽出一点时间来编写我的题解

感谢洛谷给我留出一道题让我写第一篇题解

---

## 作者：beifa (赞：3)

## CF1839B 题解来喽！

借鉴 Furthe77oad 的思路......

建议评绿。

## 思路：

这道题就是考虑贪心。

贪心的思路就是优先打开 $a$ 值较小的台灯，确保在它坏掉之前拿到最多的分数。

先排序，$a$ 从小到大排列，**在此基础上** $b$ 从大到小排列。

当我们**认真审题**时~~（本蒟蒻审错题导致赛时没做出来）~~不难发现当我们已经点亮的台灯坏了之后，自己的 $x$ 会**减少**，例如：

```
5
1 1
2 2
3 1
3 2
3 3
```

输出应该是 $5$ 个全部加起来的和，因为当点亮$1$号台灯时$1$号台灯会坏，此时 $x$ 仍然等于 $0$。

同理可得点亮 $2$ 号台灯时仍然是 $x=0$。

所以在代码中我们需要加入一个队列维护哪一盏亮了的台灯会坏，相应的 $x$ 就会减少。变量中的 $f$ 意思是坏了的台灯不能再复原，举个例子就是现在 $x=3$，然后同时坏了 $3$ 盏台灯，$x=0$，但是坏了的台灯不能再复原，故令 $f=3$ 。每次枚举时判断是否 $a\le f$，如果满足就跳过，如果不满足用 $sum$ 直接加 $b$（因为已经排过序了），再看队列队头一定是最小的 $a$ ，当已经坏了的时候 $pop$ 出去，然后 $x-1$ 即可。

## 下面附上大家最爱看的代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 200010;
int t , n , maxn , mp[N] , idx[N] , ans , dp[N] , sum;
struct lamp{
    int a , b;
}e[N];

bool cmp(lamp x , lamp y)
{
    if(x.a == y.a) return x.b > y.b;
    else return x.a < y.a;
}
int x;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--)
    {
        queue<int>q;
        cin >> n;
        for(int i = 1 ; i <= n ; ++i)
        {
            cin >> e[i].a >> e[i].b;
        }
        sort(e+1,e+n+1,cmp);
        int f = 0;
        for(int i = 1; i <= n ; ++i)
        {
            if(f < e[i].a)
            {
                sum += e[i].b;
                x++;
                q.push(e[i].a);
                f = max(f,x);
            }
            while(!q.empty() && q.front() <= f)
            {
                x--;
                q.pop();
            }
        }
        cout << sum << '\n';
        x = 0;
        sum = 0;
    }
    return 0;
}
```
## 写在最后：
鉴于是英文题面，一定要注意审题！

完结撒花！

---

## 作者：shower1114 (赞：3)

# 题目描述

有 $n$ 盏灯，只有 $3$ 种状态，可以点亮第 $i$ 个灯获得 $b_i$ 求可以得到的最大价值。

# Solution

这不是一眼贪心。

对于相同的 $a_i$ 肯定先要点亮 $b_i$ 更大的灯。

所以我们应该根据第一关键字 $a_i$ 从小到大进行排序，再根据第二关键字 $b_i$ 从大到小进行排序。

在进行一次操作后 $a_i \le x$ 的灯都会坏，说明先点亮的灯先熄灭。

那么我们就会十分容易的想到一个数据结构队列,先入队的先出队，刚好满足。那么这道题目就迎刃而解了。

# 下面就是代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define INF 2147483647
using namespace std;
int T;
int ans;
struct node{
	int a,b;
}x[200005];
bool cmp(node p,node q){         //贪心排序
	if(p.a == q.a) return p.b > q.b;
	return p.a < q.a;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> T;
	while(T--){
		int n;
		ans = 0;
		cin >> n;
		for(int i = 1;i <= n;i++){
			cin >> x[i].a >> x[i].b;
		}
		sort(x+1,x+1+n,cmp);
		int cnt = 0,h = 0;      //这里我手写了一个队列
		for(int i = 1;i <= n;i++){
			if(h>=i)continue;
			cnt++;
			ans += x[i].b;
			int t=h;
			while(x[t+1].a<=cnt && t<n) t++;
			cnt-=min(i,t)-h;
			h=t;
		}
		cout << ans << "\n";	
	}
	return 0;
}
```


---

## 作者：Furthe77oad (赞：2)

# CF1839B Lamps 题解
## 写在最前

**请一定一定把题意读明白！！！**

~~蒟蒻~~因为没有读明白题意，犯了很多错误。

## 题意注意点

当一个灯点完之后正好坏了，我们可以得到其分值，当目前所有亮着的灯的数量 $x \ge a_i$ 时，所有和该灯 $a$ 值一样的灯都会坏掉。

还有就是对于一盏灯，如果点亮它时，正好它坏了，那么 $x - 1$ 且给答案加上该灯的贡献值。

## 分析

那么显然可以想到，我们对于所有的灯，以 $a$ 值为第一关键字从小到大排序，把所有 $a$ 相同分成多段，我们可以在每一段中，挑选其中贡献值最大的一个，作为答案的一部分，加入 $ans$ 中。

**对于上面的解释：**

因为我们每次点亮的话，当前点亮的灯数量 $x$ 会 $+1$ 所以我们考虑在每段挑选出最大的贡献值，并加入到 $ans$ 当中。其实就是贪心，我们把每一层最大的贡献值选中，那么最终答案一定是最大的。

还要考虑分完段后，会出现 $a$ 值不连续的情况，参考一下样例：

```
1 1
1 2
3 3
3 4
```

其中就没有 $a = 2$ 的情况，对于这样的，我们可以考虑把原本要在 $a=2$ 这一段选的，放到 $a=3$ 中去选。

**对于上面的解释：**

其实就是，原本我是每一层都选一个最大的，但是我这样的断层情况里没法选 $a=2$ 的那一层，所以我们就给 $a=3$ 那一层多选一个灯（你没法在 $a=1$ 里面多选，所以给 $a=3$ 里多选）。

**分析一个样例看看**

原数据：

```
5
3 4
3 1
2 5
3 2
3 3
```

排序后：

```
5
2 5
3 4
3 1
3 2
3 3
```

那么我们可以分成俩部分，如下用 $---$ 划分：

```
5
2 5
----
3 4
3 1
3 2
3 3
```
先选 $2 \space \space 5$ 然后再在剩余一部分中选择 $3$ 个，这里为什么要选 $3$ 个呢？

因为当我们点亮第 $2$ 盏灯时，第一次选择的 $2 \space \space 5$ 这盏灯会灭掉，所以我们要再点 $3$ 盏灯。

## 具体实现：

我们考虑随便用个容器装好 $a$ 值和 $b$ 值，然后排序、分层，最后在每一层里模拟上述**分析**部分的过程，每一层里挑个最大的，遇到断层情况就把本属于这一层的加到下一层里去，最终累加得到答案。

## 代码实现

分析完毕，我们来看看代码。

~~马蜂清奇，不喜勿喷~~。

```C++
#include <bits/stdc++.h>
#define int long long
using namespace std;
void sol() { 
    int n;
    cin >> n;
    vector <pair <int, int> > val(n);
    for (int i = 0; i < n; i++) cin >> val[i].first >> val[i].second;
    map <int, vector <int> >mp;
    int ans = 0;
    set <int> st;
    for (int i = 0; i < n; i++) {
        st.insert(val[i].first);
        mp[val[i].first].push_back(val[i].second);
    }
    for (auto c : st) {
    	sort(mp[c].begin(), mp[c].end());
    	reverse(mp[c].begin(), mp[c].end());
    }
    for (auto c : mp) {
        for (int i = 0; i < min((int)c.first, (int)c.second.size()); i++) {
            ans += c.second[i];
        }
    }
    cout << ans << '\n';

}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
         sol();
    }
    return 0; 
}
```

---

## 作者：slzx_CPS (赞：1)

~~第三篇题解啦，好开心~~

好大一道**贪心**啊……

首先读一遍题后就想到了要排序，并且以 $a$ 为第一关键字从小到大，以 $b$ 为第二关键字从大到小，这样可以使可以选择的灯更多且 $value$ 更大。

然后看样例就可以想到，坏掉的灯中存在打开的灯，因此我们使用一个队列 $q$ 来维护打开的灯。

这样大体思路就有了，以下是几点提醒：

1. 注意语句的顺序。

2. 注意队列的清空。

3. 注意是 $\le$ 而不是 $<$（可能只有我会打错了吧）

下面附上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//养成好习惯~
const int N=2e5+5;
struct cvb{
	int cdt,val;//cdt：condition
} a[N];
queue <int> q;
int t,n,zd,ans;
bool xcv(cvb u,cvb v){//不要问变量名是啥，看键盘
	if(u.cdt==v.cdt) return u.val>v.val;
	else return u.cdt<v.cdt;
}
signed main(){
	cin>>t;
	for(int e=0;e<t;e++){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i].cdt>>a[i].val;
		sort(a+1,a+1+n,xcv);
		zd=0;ans=0;//清零
		while(!q.empty()) q.pop();//这里不要忘了清空
		for(int i=1;i<=n;i++){
			zd=max(zd,(int)(q.size()));
			while(!q.empty() && q.front()<=q.size()) q.pop();//维护队列
			if(a[i].cdt<=zd) continue;
			ans+=a[i].val;//存入答案
			q.push(a[i].cdt);//加入队列
		}
		cout<<ans<<endl;//输出答案
	}
	return 0;
}
```


---

## 作者：Erotate (赞：0)

先点亮 $a$ 值比较小的灯显然更优；对于 $a$ 相同的值，先点亮 $b$ 较大的显然更优。所以我们可以把 $a$ 值相同的灯分成一类，从 $b$ 值较大的开始点亮，直到不能点亮即点亮的个数大于等于 $a$ 时停止。根据上述算法，从 $a$ 值小的灯开始点亮对 $a$ 值较大的灯没有影响，所以是正确的。

```cpp
const int N=2e5+5;
int T,n;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
	T=read();
	while(T--){
		n=read();
		map<int,vector<int> >mp;
		for(int i=1;i<=n;++i){
			int a=read(),b=read();
			mp[a].push_back(b);
		}
		LL ans=0;
		for(int i=1;i<=n;++i){
			sort(mp[i].begin(),mp[i].end(),greater<int>());
			for(int j=0;j<mp[i].size() && j<i;++j) ans+=mp[i][j];
		}
		Write(ans);
	}
    return 0;
}
```

总时间复杂度 $O(Tn \log n)$，可以通过。

---

## 作者：QWQ_SenLin (赞：0)

显然是**贪心**

因为 $a_i$ 越小，就会越早损坏，因此要优先开 $a_i$ 小的灯。

假设当前开了 $0$ 盏灯，那么相同 $a_i$ 的灯最多开 $a_i$ 盏。也就是 $a_i=1$ 的灯最多开 $1$ 盏，$a_i=2$ 的灯最多开 $2$ 盏，$a_i=3$ 的灯最多开 $3$ 盏，以此类推。

因此我们先按照 $a$ 升序，相同情况下 $b$ 大的排前面进行排序。然后给相同的 $a$ 进行分组，每组都选择开 $b$ 大的灯最多 $a$ 个，然后累计即可。

下面是关键代码。

```cpp
struct QWQ {
	int a , b;
	inline bool operator < (QWQ bb){
		if(a == bb.a)
			return b > bb.b;
		return a < bb.a;
	}
}qwq[200005];

...

long long ans = 0;
scanf("%d" , &n);
for(int i = 1;i <= n;i++)
	scanf("%d%d" , &qwq[i].a , &qwq[i].b);
sort(qwq + 1 , qwq + 1 + n);
int i = 1;
while(i <= n){
	if(cnt[qwq[i].a] < qwq[i].a){
		ans += qwq[i].b;
		cnt[qwq[i].a]++;
	}
	i++;
}
printf("%lld\n" , ans);
```

---

## 作者：white_carton (赞：0)

[$\color{#52C41A}\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1839B)

[$\color{#52C41A}\text{更好的体验}$](https://inksennns.blog.luogu.org/)

---
### 分析
这题是贪心。

我们很容易可以想到，最优方案肯定是从 $a_i$ 最小的灯开始开，因为如果先开  $a_i$ 大的灯可能会因为 $a_i$ 小的灯坏掉而无法得到应该得到的分数。

所以我们把 $a_i$ 当作第一关键词，从小到大排，$b_i$ 当作第二关键词，从大到小排，以此开灯。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct node{
	int a,b;
	friend bool operator<(node a,node b){
		if(a.a==b.a){
			return a.b>b.b;
		}
		return a.a<b.a;      //关键词排序
	}
}a[200100];
int dc=1;
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
	}
	int summ=0,maxn=0,x=0;
	for(int i=1;i<=n;i++){
		if(a[i].a<=maxn){
			continue;
		}
		summ+=a[i].b;
		maxn++;
	}
	cout<<summ<<endl;
}
signed main(){
	int t=(dc?read():1);
	while(t--)
		solve();
	return 0;
}
```
我们惊奇的发现，连样例都没过。

手模了 $2$ 次样例后，我发现，坏掉的灯不计入 $x$。

所以我们再开个队列，维护此时开的灯。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
struct node{
	int a,b;
	friend bool operator<(node a,node b){
		if(a.a==b.a){
			return a.b>b.b;
		}
		return a.a<b.a;
	}
}a[200100];
int dc=1;
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
	}
	sort(a+1,a+1+n)
	queue<int> q;
	int summ=0,maxn=0,x=0;
	for(int i=1;i<=n;i++){
		maxn=max(maxn,(int)(q.size()));      //最大的x
		while(!q.empty()&&q.front()<=q.size()){
			q.pop();
		}
		if(a[i].a<=maxn){
			continue;
		}
		summ+=a[i].b;
		q.push(a[i].a);
	}
	cout<<summ<<endl;
}
signed main(){
	int t=(dc?read():1);
	while(t--)
		solve();
	return 0;
}
```

---

## 作者：Furina_Hate_Comma (赞：0)

~~赛时 A 想不出来，B 出来了但是发现没有报名。~~

这题**贪大心**。

1. $b_i$ 也就是有多少灯在时这盏灯会炸大的，一定是后来加入的。
2. $b_i$ 相对的情况应该按得分 $a_i$ 排序。

所以可以先按 $b$ ,再按 $a$ 排序，然后用双端队列维护点亮区间，每次从未点亮区间拿最大值即可。

code：

```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
using namespace std;
#define int long long
struct lamp{
	int a,b;
};
lamp l[200010];
bool cmp(lamp a,lamp b){
	if(a.a==b.a)
		return a.b>b.b;
	return a.a<b.a;
}
deque<lamp>q;

signed main()
{
	int t;
	cin>>t;
	while(t--){
        q.clear();
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>l[i].a>>l[i].b;
		sort(l+1,l+1+n,cmp);
		int hi=0,ans=0;
		for(int r=1;r<=n;r++){
            if(l[r].a<=hi)continue;
            q.push_back(l[r]);
            ans+=l[r].b;
            int s=q.size();
            hi=max(hi,s);
            while(q.size()&&q.front().a<=s)q.pop_front();
		}
        cout<<ans<<'\n';
	}
    return 0;
}
```

---

## 作者：rainygame (赞：0)

比较简单的一道题，建议评黄/绿。

首先，我们有一个显然的贪心思路，先打开 $a_i$ 小的，相同就打开 $b_i$ 大的。因为 $a_i$ 小的更容易坏掉，而如果可以开 $a_i$ 相同的灯，就一定要开最大的，否则到时候坏掉就更亏了。

我们可以考虑用桶来储存相同 $a_i$ 的 $b$，但是需要维护最大值，所以可以整一个“桶套堆”以维护相同 $a_i$ 的 $b$ 的最大值。

然后就是简单的模拟过程了，可以考虑开一个数组储存每个桶有多少个开了的灯，注意**坏掉的灯不计入**，所以坏完之后要清空。

时间复杂度 $O(tn \log n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200001

int t, n, cnt, a, b, flag, tmp;
int opened[MAXN];
long long ans;
priority_queue<int> pq[MAXN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> t;
	while (t--){
		cin >> n;
		for (int i(1); i<=n; ++i){
			while (!pq[i].empty()) pq[i].pop();
		}
		
		for (int i(1); i<=n; ++i){
			cin >> a >> b;
			pq[a].push(b);
		}
		
		memset(opened, 0, sizeof(opened));
		cnt = ans = 0;
		for (int i(1); i<=n; ++i){
			if (cnt >= i) continue;
			flag = 0;
			while (cnt < i && !pq[i].empty()){
				tmp = cnt;
				cnt -= opened[cnt];
				opened[tmp] = 0;
				ans += pq[i].top();
				pq[i].pop();
				++opened[i];
				++cnt;
			}
		}
		
		cout << ans << '\n';
	}
	
	return 0;
}

```


---

## 作者：ljlawa (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1839B)

# 题意：

有 $n$ 盏灯，灯 $i$ 有临界值 $a_i$ 和贡献 $b_i$，当场上亮着的灯个数 $\ge a_i$ 时，它就会坏掉，若它坏掉时是亮着的，那么我们依然可以获得它的贡献。坏掉的灯不计入亮灯总数。求最大得分。

# 思路：

既然达到临界值 $x$ 时所有临界值小于等于 $x$ 的等都会坏掉，那么我们就要让对应临界值的选灯方案的贡献达到最大。（对于临界值 $x$ 我们将临界值等于 $x$ 的灯中最大的 $x$ 个，然后这一临界值以下的灯就会爆掉，如果不够可以不选满）如果选不满，我们交给下一层一样可以把这一层爆掉然后正常操作。

所以我们按第一关键字 $a_i$ 从小到大进行排序，对所有灯分类，再按 $b_i$ 排序（方便选取）。

# 代码：

```
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 5;

int t;
int n;

struct node
{
	int a, b;
} a[N];

bool cmp (node a, node b)
{
	if (a.a == b.a) return a.b < b.b;
	return a.a < b.a;
}
int v[N], tot;

signed main()
{
	cin >> t;
	while (t --)
	{
		int ans = 0;
		tot = 0;
		cin >> n;
		for (int i = 1; i <= n; i ++) cin >> a[i].a >> a[i].b;
		sort (a + 1, a + 1 + n, cmp);
		int cnt = 0;
		for (int i = 1; i <= n; i ++)  // 分出所有不同临界值
		{
			if (a[i].a != a[i - 1].a) v[++ tot] = i;
			else v[tot] = i;
		}
		int lst = 0;
		for (int i = 1; i <= tot; i ++) // 分别满足 
		{
			int kd = a[v[i]].a;
			int l = v[i] - kd + 1;
			if (l < v[i - 1] + 1) l = v[i - 1] + 1; // 数量不够就不选 
			int r = v[i];
			for (int j = l; j <= r; j ++) ans += a[j].b;
		}
		cout << ans << endl;
	}
    return 0;
}
```


---

## 作者：ballpoint_pen (赞：0)

### 题意

有 $n$ 盏灯，每盏灯的状态有：开、关、坏掉三种，初始时全部为关。每盏灯有 $a_i,b_i$ 两个指标。每次你可以打开任意一盏关着的灯 $i$，并且获得 $b_i$ 的价值；假设你打开后有 $k$ 盏灯开着（坏掉的不算），那么所有满足 $a_j\le k$ 的灯立刻坏掉（这不会扣除你已经获得的价值）。求最后能获得的最大价值。

$n\le 2\times 10^5$

### 解法

不难发现如果要使价值最大肯定从 $a_i$ 最小的灯开始开，因为如果先开大的会导致 $a_i$ 较小的灯直接坏掉，损失价值；而先从小的开则不会影响到大的灯，因为 $a_i$ 较小的灯一定会先坏。

于是按照 $a_i$ 为第一关键字排递增序，$b_i$ 为第二关键字排递减序。之后按照题意模拟，用一个左端点指针记录哪些灯已经坏了，如果当前的灯没坏就打开，否则跳过。时间复杂度：$O(n\log n)$。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int x,y;
}a[200005];
bool cmp(node x,node y){
	if(x.x!=y.x)return x.x<y.x;
	return x.y>y.y;
}
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	sort(a+1,a+n+1,cmp);
	int ans=0,cnt=0;
	int l=0;
	for(int i=1;i<=n;i++){
		if(l>=i)continue;
		cnt++; ans+=a[i].y;
		int r=l;
		while(a[r+1].x<=cnt&&r<n) r++;
		cnt-=min(i,r)-l;
		l=r;
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int tc;
	cin>>tc;
	while(tc--)solve();
	return 0;
}
```

---

