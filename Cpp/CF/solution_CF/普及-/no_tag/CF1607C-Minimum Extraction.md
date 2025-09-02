# Minimum Extraction

## 题目描述

*Yelisey* 有一个含有 $n$ 个整数的数组 $a$。

如果 $a$ 的长度大于 $1$，*Yelisey* 就能对它进行一种被称为「提取最小值」的操作：

1. 将最小值 $m$ 从数组中删除，数组的长度会因此缩短 $1$。

   （如果有几个相同的 $m$，*Yelisei* 可以凭心情任选一个。）

2. 数组中剩下的元素也会被减去 $m$。

举个例子，有一个数组 $\{1, 6, -4, -2, -4\}$，其中的最小元素是 $-4$。我们将随意删去 $a_3$、$a_5$ 中的一个，再把剩余元素各减去 $-4$。显而易见，操作后的数组长这样：$\{1-(-4),6-(-4),-2-(-4),-4-(-4)\}$，化简后得到答案 $\{5, 10, 2, 0\}$。

由于 Yelisey 更喜欢大数，他希望这种操作能使数组 $a$ 中的元素数值尽可能大。

准确来说，他希望使数组 $a$ 中的最小值最大。为了达到这一目的，*Yelisey* 不惜对数组进行任意次「提取最小值」操作；当然，他也不一定非要进行这种操作。

现在，请你帮助他计算出在进行任意次「提取最小值」操作后，数组 $a$ 中的最小元素可以具有的最大值。

## 说明/提示

在第一组数据中，数组的原始长度 $n=1$，*Yelisey* 不能对它进行操作。因此最小元素的最大值是 $a_1=10$ 。

在第二组数据中，数组始终只有 $0$。所以，最小元素的最大值为 $a_2=0$。

在第三组数据中，数组的改变过程如下： $\{\color{blue}{-1}$$,2,0\}\to\{ 3,\color{blue}1$$\}\to$ $\{$$\color{blue} {2}$$\}$。所以，最小元素的最大值是 $a_3=2$ 。(当前数组最小的数以蓝色标出）

保证所有询问的数组原始长度 $n$ 之和不超过 $2\cdot 10^5$。

在第四组数据中，数组的改变过程如下：$\{2,10,$$\color{blue}{1}$$,7\}\to\{\color{blue}{1}$$,9,6\}\to\{8,\color {blue}{5}$$\}\to$$\{$$\color{blue}{3}$$\}$。 所以，最小元素的最大值是 $a_4=5$ 。

Translated by @[Aynxul03](https://www.luogu.com.cn/user/267459) & @[li142857](https://www.luogu.com.cn/user/540584)

## 样例 #1

### 输入

```
8
1
10
2
0 0
3
-1 2 0
4
2 10 1 7
2
2 3
5
3 2 -4 -2 0
2
-1 1
1
-2```

### 输出

```
10
0
2
5
2
2
2
-2```

# 题解

## 作者：xiaomuyun (赞：14)

# CF1607C Minimum Extraction 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1607C)

~~这个蒟蒻不会用树状数组，所以交了一篇非常容易理解的题解~~
## 大致题意
给出一个由 $n$ 个整数组成的序列 $a$，我们将以下动作称为一次操作：

1. 找到当前序列的最小值；
2. 从序列中删掉它，并将序列中的所有整数减去这个最小值。

现在题目求的是所有操作中找到的最大的最小值。
## 题目分析
因为我们知道每次删掉一个整数后，再遍历一遍整个序列肯定会时间超限，但是我们并不需要每次都遍历一遍整个序列，只需要维护一个 $sum$，每次将最小的数减去这个 $sum$，然后再将 $sum$ 增加这个最小的数即可。

不要忘了取 $\max$，即求这个最小的数的最大值。还有一开始要将序列从小到大排序。
## 代码
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;//不开long long见祖宗
const ll inf=0x3f3f3f3f3f3f3f3f;
ll n,a[200001],sum=0,mx=-inf;//mx初始化不能为0
int main(){
//	freopen("CF1607C.in","r",stdin);
//	freopen("CF1607C.out","w",stdout);
	ll t;
	scanf("%lld",&t);
	while(t--){
		sum=0,mx=-inf;//对于每组数据都要初始化
		scanf("%lld",&n);
		for(ll i=1;i<=n;++i) scanf("%lld",&a[i]);
		sort(a+1,a+1+n);
		for(ll i=1;i<=n;++i){
			a[i]-=sum,sum+=a[i];
			mx=max(a[i],mx);//取max
		}
		printf("%lld\n",mx);
	}
	return 0;
}
```
## 总结
求管理员通过！点个赞吧，制作不易！

---

## 作者：DaiRuiChen007 (赞：3)

# $\mathcal{CF} 1607 \mathcal{C}$ 最小值提取 题解

## 输入格式

输入一个整数$t$ (保证$t \in \left[1,10^4\right]$)

接下来 $t$ 组数据，每组有 $2$ 行：

第$1$行一个整数$n$ (保证$n \in \left[1,2\times 10^5\right]$)

第$2$行$n$个整数 表示数组中的 $a_i$ 元素  $($ 保证$ a_i \in \left[-10^9,10^9\right]$ $)$

## 输出格式

输出 $t$ 行

每行一个整数 $ans$ ，表示第$i$个数列经过若干次最小值提取操作所能获得的最大值

## 算法分析

#### 思路：~~膜你~~ 模拟算法

##### $step\,1.$ 大暴力

由于每次操作的过程是具体确定的，因此得出的结果只与经过的操作数有关

用 $f_i$  表示经过 $i$ 次操作后得到的最小值，用模拟计算即可

$ans=\max(f_i)\;\;i\in(1,n)$

时间复杂度：$\mathcal{O}(n)$ 枚举所有的$f_i$ ， $\mathcal{O}(n)$对每次的数据减小进行操作，总的时间复杂度 $\mathcal{O}(n^2)$ 显然会TLE，所以我们需要考虑一下优化

##### $step\,2.$ 暴力 $+$ 小小的优化

由于每一次 $f_i$ 的计算仅与当前 $a$ 的最小值有关，所以我们可以将每次删除的数记录下来并且累加，而不是对每个值进行减小，在提取$ f_i$ 的时候减去即可

##### $step\,3.$ 暴力 $+$ 不小的优化

我们发现 $f_i$ 与之前的状态无关，所以只需要用计算出当前的 $f_i$ 值，然后与 $ans$ 取得 $\max$  即可

时间复杂度：$\mathcal{O}(n\log n)$

空间复杂度：$\mathcal{O}(n)$

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int a[MAXN];
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		int n;
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		for(register int i=1;i<=n;++i) {
			scanf("%d",a+i);
		}
		if(n==1) {
			printf("%d\n",a[1]);
			continue;
		}
		//对a数组进行排序 
		sort(a+1,a+n+1);
		int sum,ans;
		//sum表示删去所有数的和，最开始sum和ans都是最小值 
		ans=sum=a[1];
		for(register int i=2;i<n;++i) {
			//用a[i]当前实际的值(a[i]-sum)来更新ans和sum 
			ans=max(ans,a[i]-sum);
			sum+=a[i]-sum;
		}
		//因为数组中只有一个数时不能操作，所以特殊处理最后一个数 
		ans=max(ans,a[n]-sum);
		printf("%d\n",ans);
	}
	return 0;
}
```



### $Auhtor: dairuichen$



---

## 作者：WaltVBAlston (赞：1)

大家好我是 Andy_2006，我非常喜欢线段树，所以我选择使用线段树完成这道题目。

对于这道题，如果你不会线段树的话，可能比较难想，可能想了很久才推出来规律。但是线段树不一样，你只需要阅读一遍题目就可以确定，这是一道单点修改，区间查询的简单线段树。

唯一的难点就是在标记上。但是没有关系，我们用一个 now 变量去存储当前所有数减的数量。不难发现：
```
now+=tree[1].minn-now
```
这是一句很有用的废话，他能帮我们确定每一轮的 now 就是 

```
tree[1].minn

```


然后就是基本线段树操作。不难证明，最多 $n-1$ 轮操作，最后记得要再取一遍最大值。复杂度 $O(n \log n)$，略慢，但是过这道题绰绰有余。

Code:

```
#include<iostream>
#include<cstdio>
using namespace std;
struct node{
	int minn;
	int tag;
}tree[1600005];
int n,t,a[200005];
void build(int i,int l,int r){
	if(l==r){
		tree[i].minn=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(i*2,l,mid),build(i*2+1,mid+1,r);
	tree[i].minn=min(tree[i*2].minn,tree[i*2+1].minn);
	return;
} 
void clean(int i,int l,int r){
	if(l==r){
		tree[i].minn=1000000000;
		return;
	}
	int mid=(l+r)/2;
	if(tree[i*2].minn<tree[i*2+1].minn)
		clean(i*2,l,mid);
	else
		clean(i*2+1,mid+1,r);
	tree[i].minn=min(tree[i*2].minn,tree[i*2+1].minn);
	return;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		build(1,1,n);
		int ans=tree[1].minn;
		int now=0;
		for(int i=1;i<=n-1;i++){
			ans=max(ans,tree[1].minn-now);
			//cout<<"minn=="<<get_min(1,1,n)-now<<" "<<ans<<endl;
			now=tree[1].minn;
			clean(1,1,n);
		}
		cout<<max(ans,tree[1].minn-now)<<endl;
	}
	return 0;
}
```


---

## 作者：Aiopr_2378 (赞：1)

# Solution CF1607C Minimum Extraction

### 题目大意：

给出一个由 $n$ 个整数组成的序列 $a$，依次进行每一次操作，直至数组为空：

1. 找到当前序列的最小值(如果有多个，就任选一个)；

1. 从序列中删掉它，并将序列中的所有整数减去这个最小值。

求每个操作中最大的最小值。

### 解题思路：

排序+贪心。

当我们拿到一个序列时，我们可以先对序列进行从小到大排序。

这时，我们就发现，我们删数的顺序就是现在数组的顺序。而题目要求的就是当前数和上一个数的差的最大值。

这样，我们就可以把问题简单化，时间复杂度合法。

### 参考代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,a[200005];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);
        int temp=a[1],maxi=a[1];
        for(int i=2;i<=n;i++){
            maxi=max(maxi,a[i]-temp);
            temp=a[i];
        }
        cout<<maxi<<endl;
    }
    return 0;
}
```


---

## 作者：引领天下 (赞：1)

考虑直接按题意模拟。

由于最后的答案与顺序无关，所以直接将读入的数组排序，然后删除 $a_i$ 时将 $a_{i+1}\sim a_n$ 全部加上 $-a_i$，再求 $\max{a_i}$ 即可。

具体实现我写的是树状数组，事实上你想写线段树也没啥问题。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[200005];
class Bit{
    private:
    #define N 200005
    int n;
    long long c[2][N];
    inline int lowbit(int x){return x&(-x);}
    inline void _add(bool flag,int x,int k){
        while(x<N)c[flag][x]+=k,x+=lowbit(x);
    }
    inline long long _ask(bool flag,int x){
        long long res=0;
        while(x)res+=c[flag][x],x-=lowbit(x);
        return res;
    }
    public:
    inline void clear(){
        memset(c,0,sizeof(c));
    }
    inline void add(int l,int r,long long k){
        _add(0,l,k);
        _add(0,r+1,-k);
        _add(1,l,l*k);
        _add(1,r+1,-k*(r+1));
    }
    inline void add(int x,long long k){
        add(x,x,k);
    }
    inline long long ask(int l,int r){
        return _ask(0,r)*(r+1)-_ask(1,r)-_ask(0,l-1)*l+_ask(1,l-1);
    }
}bit;//树状数组板子
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)bit.add(i,-bit.ask(i,i));//清空，不写成memset(c,0,sizeof(c))的原因是sum n<=1e6，如果每次都全数组清空的话会t。（因为清空了大量没用过的元素）
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++)bit.add(i,a[i]);
        int ans=a[1];//0次操作，最小值为a1
        for(int i=1;i<n;i++){
            bit.add(i+1,n,-bit.ask(i,i));//将i+1~n全部-a[i]
            ans=max(ans,bit.ask(i+1,i+1));//更新答案
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：ZZQF5677 (赞：0)

### 解题思路
先把数组排一遍序，保证每次遍历 $a_i$ 时，是需要操作的数中当前最小的。因为每个需要操作的数都是要一起更改的，所以就只用建立一个 $ans$，用来记录数组的统一减少动态，然后遍历 $a_i$ 时：

- 将 $a_i$ 更成之前的所有减少变化：$a_i \gets a_i-ans$。
- 再对比 $a_i$ 是不是整个数组变化后最小的：$smallest \gets \min(smallest,a_i)$。
- 更新减少变化：$ans \gets ans + a_i$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005];
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    sort(a, a + n);                 // 排序后食用就不用每次找最小的了！
    int smallest = a[0], ans = a[0];  // ans用于记录整个数组统一动态。
    for (int i = 1; i < n; i++) {
      a[i] = a[i] - ans;
      smallest = max(smallest, a[i]);
      ans = ans + a[i];  // 更新动态
    }
    cout << smallest << endl;
  }
  return 0;
}
```

---

## 作者：BootsH (赞：0)

模拟即可。

## 分析：

1. 此题已经告诉我们这些操作了，所以直接按照题目所做即可。

2. 注意到数组每个元素同时减去一个值时，数组内元素的相对大小不变，这时我们可以想到用堆来处理大小关系。

3. 对于（无修改，无添加元素的）堆内减去一个值，我们可以用一个标记，记录减去值的大小，取出时再把原值减去标记，就得到实际的值了。

## 思路：

一开始，把所有元素放到一个 `priority_queue` 里面，标记重置为 0。每次拿出一个值，先用它减去标记（得到实际值），再把标记加上这个值（即为新的标记）。每次把实际值拿出来比大小即可。

## 代码：

注意开 `long long`。

快读快写操作等略，看 [这里](https://www.luogu.com.cn/paste/2i2fp17n)

`iget` 为输入 `int` 类型数。

`llwln` 为输出 `long long` 类型数且换行。

```cpp
#include <queue>

namespace Solution
{
    using namespace AKA;
    using IO::gc; using IO::pc; 
    using IO::iget; using IO::ipr; using IO::iwsp; using IO::iwln;
    using IO::llget; using IO::llpr; using IO::llwsp; using IO::llwln;
    using IO::ullget; using IO::ullwsp; using IO::ullwln;
    using IO::spr; using IO::swsp; using IO::swln;


    std::priority_queue<int> qaq;


    void main(void)
    {
        #ifndef ONLINE_JUDGE
            std::ifstream cin("main.in");
            std::ofstream cout("main.out");
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #else
            std::ios::sync_with_stdio(false);
            using std::cin; using std::cout;
            #if __cplusplus >= 201103L
                cin.tie(nullptr); cout.tie(nullptr);
            #else
                cin.tie(NULL); cout.tie(NULL);
            #endif
            IO::inbuf = cin.rdbuf(); IO::outbuf = cout.rdbuf();
        #endif


        int general_q = iget();
        while (general_q--)
        {
            int n = iget();
            for (int i = 1; i <= n; ++i)
            {
                qaq.push(-llget());
            }
            ll sum = 0, maxv = -1e15;
            for (int i = 1; i <= n; ++i)
            {
                ll temp = -qaq.top();
                qaq.pop();
                temp -= sum;
                sum += temp;
                maxv = std::max(maxv, temp);
            }
            llwln(maxv);
        }


        #ifndef ONLINE_JUDGE
            cin.close(); cout.close();
        #endif
    }
} // namespace Solution
```


---

## 作者：qwq___qaq (赞：0)

### 题意简述
每次一个操作，往一个数组中删掉最小值，并让每个元素都减去它。
### 算法思路
每次删除之后模拟，我们都老老实实地计算一次，时间复杂度 $O(n^2)$，过不了。所以，我们**必须**优化。

首先，因为要求每次的最小，我们容易想到先排序，然后求删去前的结果的话，我们可以来模拟一下：

删掉 $a_1$，则 $a_2\gets a_2-a_1$，$a_3\gets a_3-a_1$。

删掉 $a_2$，则 $a_3\gets a_3-a_1-(a_2-a_1)=a_3-a_2$。

综上 $a_i\gets a_i-a_{i-1}$。
以此为基础，排完序之后直接遍历一遍数组，每次 $ans\gets \max{(a_i-a_{i-1},ans)}$，则可以直接求解答案，时间复杂度为 $O(n\log n)$，可以过，优化成功！
### AC Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int a[maxn],n,T;
inline void solve(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    stable_sort(a+1,a+1+n);//排序，推荐使用稳定的线性对数级
    int ans=a[1];//初始化为第一个数，避免初始值不够小
    for(int i=2;i<=n;i++){
        a[i]+=a[i-1];
        ans=max(a[i]-a[i-1],ans);//求解答案
    }
    printf("%lld\n",ans);
    return;
}
signed main(){
    scanf("%lld",&T);//多组测试数据
    for(int i=1;i<=T;++i) solve();
    return 0;
}
```

---

## 作者：Valhalla_Is_Calling (赞：0)

正常的前缀和做法看到其他题解都提到过，这边分享一个非常非常妙的做法。

### 题意简述
给定一个数列，每次选择任意一个最小值并将其删除，且将其他没有被删除的数字都减掉这个最小值，你可以进行任意次操作，问你能拿到的最小值最大是多少。

### 题解
第一眼看上去是二分答案，但是仔细一想并不需要。
容易发现，对于一个数 $a_i$ 来说，除非他被操作或者排序后的 $a_{i-1}$ 被操作，否则他相对于 $a_{i-1}$ 的大小是不变的（因为要减一起减），所以一个数看他能不能成为答案就看他跟排序后他的前一个数的差就好，这个差就是他最后能提供的贡献，所以综上我们只需要在排序后得到相邻两个数字的差的最大值即可。


---

## 作者：Madefaker (赞：0)

##### C. Minimum Extraction

题目大意：

对于多组数据 $(1 \le t \le 10^4)$，给定 $n(1 \le n \le 2 \times 10^5)$ 个整数的数列 $a(-10^9 \le a_i \le 10^9)$，进行 $n$ 次操作，第 $i$ 次选出数列 $a$ 里面最小的那个数作为 $min_i$ 删去，并将其他数都减去 $min_i$。要求输出这 $n$ 次操作中选出来的 $min_i$ 的最大值。

------

思路：

由于每一次给 $a$ 做的操作都没有影响 $a$ 中元素的相对位置，所以 $a$ 中元素被选出的顺序一定和其初始顺序一样，所以先排序，然后考虑处理所有数字在它们取出来做 $min$ 的时候分别加了多少。

由于每次都是加上最小值的相反数，所以可以遍历一遍整个数组，并累加 $min$ 所做的所有贡献，然后一个数在第 $i$ 次被取出之前，一定是做了前 $i-1$ 次所有操作，所以 $min_i = a_i + \sum_{j=1}^{i-1} {-min_{i-1}}$（$a$ 已排序）。

以样例为例：$a=[1,6,-4,-2,-4]$，排序之后 $a=[-4,-4,-2,1,6]$。取出 $-4$，并且其他数都减去 $-4$，得到 $a=[0,2,5,10]$。然后取出 $0$，并且其他数都减去 $0$，得到 $a=[2,5,10]$。取出 $2$，并且其他数都减去 $2$，得到 $a=[3,8]$。

此时所要减去的 $min_i=3$，它的初始位置上的数是 $1$，而它是由 $1-(-4+0+2)$ 来的。

------

实现：

用 $sum$ 记录累加贡献，直接线性遍历一遍即可。时间复杂度 $O(n \log n)$。

```c++
#include<bits/stdc++.h>
using namespace std;
#define f(i,a,b) for(int i = a;i <= (b);++i)
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	int t;
	cin >>t;
	while(t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		f(i, 0, n - 1) cin >> a[i];
		sort(a.begin(), a.end());
		int mx = -1e9, sum = 0; 
		f(i, 0, n - 1) {
			int now = a[i];
			a[i] += sum;
			mx = max(mx, a[i]);
			sum = sum + (-a[i]);
		}
		cout << mx <<endl;
	}
	return 0;
}
```



---

## 作者：Xhesika_Frost (赞：0)

我们假设现在有三个数 $x_1,x_2,x_3$ 满足 $x_1<x_2<x_3$ ，显然要使最小值最大的话，我们应该考虑从小到大删除。

现在我们删除了 $x_1$  得到的两个数是 $x_2-x_1 ,x_3-x_1$  
显然 $x_2-x_1>x_3-x_1$ 的，那么我们再减去第二个数会发生什么呢？

$x_3-x_1-(x_2-x_1)=x_3-x_2$，最小值变成了 $x_3-x_2$ 并且可以进一步推广到更多的数的情况，拍完序之后，答案就是相邻的数的差中最大的值。

注意还要和 $x_1$ 比较，因为只有一个数和不删的时候答案就是第一个数。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
template<class T>
void read(T &now){
	now=0;
	char c=getchar();
	int f=1;
	while((!isdigit(c))){
		if(c=='-') f=-1;
	//	cout<<isdigit(c)<<" "<<c<<" ";
		c=getchar();
	}
	while(isdigit(c)){
		now=(now<<1)+(now<<3)+c-'0';
		c=getchar();
	}
	now*=f;
}
long long a[10000001];
int n;
int ch;
int t;

long long up; 
int main(){
	read(t);
	while(t--){
		read(n);
		for(int i=1;i<=n;++i){
			read(a[i]);
		}
		up=0;
		sort(a+1,a+n+1);
		int l;
		long long ans=-9999999999999;
		for( l=1;l<=n;++l){
			//if(a[l]+up<a[l+1]+up-a[l]){
				ans=max(ans,a[l]+up);
			//	cout<<"V"<<a[l]+up<<endl;
				
				up-=(a[l]+up);
			//}
			
		}
		cout<<ans<<endl;
	}
	return 0;
}
```




---

