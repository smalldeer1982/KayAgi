# [ABC188D] Snuke Prime

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc188/tasks/abc188_d

株式会社すぬけは様々なサービスを提供しています。  
 この会社は、すぬけプライムという支払いプランを用意しています。  
 すぬけプライムへの加入中は、$ 1 $ 日あたり $ C $ 円を支払うことで、提供される全てのサービスを追加料金の支払いなしに利用することができます。  
 すぬけプライムへの加入および脱退は、それぞれ $ 1 $ 日の始めおよび終わりに自由に行うことができます。

高橋くんは、この会社のサービスのうち $ N $ 個を利用しようとしています。  
 そのうち $ i $ 個目のサービスは、今日を $ 1 $ 日目として、$ a_i $ 日目の始めから $ b_i $ 日目の終わりまで利用する予定です。  
 すぬけプライムに加入していない期間中は、$ i $ 個目のサービスを利用する際に $ 1 $ 日あたり $ c_i $ 円を支払う必要があります。

サービスを利用するために高橋くんが支払う必要のある最小の合計金額を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ C\ \leq\ 10^9 $
- $ 1\ \leq\ a_i\ \leq\ b_i\ \leq\ 10^9 $
- $ 1\ \leq\ c_i\ \leq\ 10^9 $
- 入力に含まれる値は全て整数

### Sample Explanation 1

$ 1 $ 番目のサービスは $ 1 $ 日目と $ 2 $ 日目に、 $ 2 $ 番目のサービスは $ 2 $ 日目に利用します。 $ 2 $ 日目のみすぬけプライムに加入すると、 $ 1 $ 日目に $ 4 $ 円、 $ 2 $ 日目に $ 6 $ 円がかかるため、高橋くんが支払う合計金額は $ 10 $ 円です。 高橋くんが支払う金額を $ 10 $ 円より少なくすることはできないため、 $ 10 $ を出力します。

### Sample Explanation 2

すぬけプライムに全く加入しないのが最適です。

## 样例 #1

### 输入

```
2 6
1 2 4
2 2 4```

### 输出

```
10```

## 样例 #2

### 输入

```
5 1000000000
583563238 820642330 44577
136809000 653199778 90962
54601291 785892285 50554
5797762 453599267 65697
468677897 916692569 87409```

### 输出

```
163089627821228```

## 样例 #3

### 输入

```
5 100000
583563238 820642330 44577
136809000 653199778 90962
54601291 785892285 50554
5797762 453599267 65697
468677897 916692569 87409```

### 输出

```
88206004785464```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc188_d)

### 思路

首先不难想到暴力思路。将所有的钱都加在每一天上，并遍历每一天，如果当天所用金额大于会员价，就开会员卡。

然后这样做会超时。题目中说从 $a_i$ 天到 $b_i$ 天，每天都要支付 $c_i$ 元，考虑**差分**。但是 $a_i,b_i\le10^9$，可以使用 map 储存。

这样做的时间复杂度是 $\mathcal{O}(N\log N)$，可以通过此题。

**注意事项**

- 不开 `long long` 见祖宗。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
map<int,int>mp;
signed main(){
	int n=read(),c=read();
	while(n--){
		int a=read(),b=read(),c=read();
		mp[a]+=c,mp[b+1]-=c;
	}
	int ans=0,sum=0,p=0;
	for(auto i:mp){
		ans+=(i.first-p)*min(sum,c);
		p=i.first;
		sum+=i.second;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：kevin1616 (赞：3)

### 审题
用户可以支付 $C$ 元，购买一天会员资格。拥有会员资格的期间，可以自由使用公司提供的所有服务。高桥君想要使用这个公司的 $N$ 种服务。使用第 $i$ 种服务的期间是从第 $a_i$ 天的开始到第 $b_i$ 天的结束。在没有会员资格的期间，要使用第 $i$ 种服务，每天需要支付 $c_i$ 元。求出高桥君需要支付的最小合计金额。

简单说就是看当天支付 $C$ 元便宜还是当天的 $c_i$ 的总和便宜，然后把所有最小值相加。

***
### 方法
【离散化】看到题目描述，一看就是离散化。离散化简单来说就是将类似数组一样连续映射拆开。看到求和，又想到差分优化。于是离散化对于这道题再适合不过了。
***
### 思路
将 $a_i$ 对应的差值加上 $c_i$，$b_i+1$ 对应的差值减去 $c_i$，分别存入 map 中。然后遍历一遍，每次求出当前所需费用，对 $C$ 和当天所需消费取最小值，每次记录上一个切换状态的天数。最后输出总共需要的费用即可。
***
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define QWQ return 0
using namespace std;
int n,C;
int a,b,c;
int sum,ans;
map <int,int> money; //经过差分优化过的map
signed main(){
    cin >> n >> C;
    for(int i = 1;i <= n;i++){
        cin >> a >> b >> c;
        money[a] += c;
        money[b + 1] -= c;
    }
    int last = 0;
    for(auto it : money){
        ans += (it.first - last) * min(C,sum); //累计答案
        sum += it.second; //当天所有所需费用
        last = it.first; //上一次切换购买状态的天数
    }
    cout << ans << endl; //输出答案
    QWQ; //好习惯
}
```
不抄题解，从我做起！

---

## 作者：GSQ0829 (赞：2)

_[题目传送门](https://www.luogu.com.cn/problem/AT_abc188_d)_

---
### 解题思路：
这题其实就是用前缀和与差分来做。

前缀和与差分的知识点：[点这里](https://oi-wiki.org/basic/prefix-sum/)。

那么在这题里面的前缀和与差分就是：
```cpp
mp[a] += c;
mp[b + 1] -= c;	
```
这些函数名就不用管了。

然后，还有一个知识点就是 map。

map 的知识点：[点这里](https://blog.csdn.net/WangZixuan1111/article/details/97941225)。

这题中 map 的定义就是：
```cpp
map<int, int> mp;
``` 

除了知识点以外，也有一些是需要注意的：

1. 数据范围。从题目中可知。
- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ C\ \leq\ 10^9 $
- $ 1\ \leq\ a_i\ \leq\ b_i\ \leq\ 10^9 $
- $ 1\ \leq\ c_i\ \leq\ 10^9 $

最大的高达 $10^9$，那么就必须开 long long 了。

2. 循环遍历部分。计算总价格这个地方，我们要先判断哪一种花费的最少，再加上第二天的正常花费。

既然知识点和注意部分都讲完了，那就三二一，上代码！

---
### code：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, c, a, b, c, s = 0, k = 0, ans = 0;
map<int, int> mp;

signed main() {
	cin >> n >> c;
	while (n--) {
		cin >> a >> b >> c;
		mp[a] += c;
		mp[b + 1] -= c;
	}
	for (auto i : mp) {
		ans += (i.first - k) * min(s, c);
		s += i.second;
		k = i.first;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：player_1_Z (赞：2)

### 先来理解题目
题目应该都懂，这里提醒一点，体验一个服务时每一天都要花费 $c_i$ 元，同时一天可以同时体验多个服务。
### 思路
这一题如果暴力就是把每一个服务的每一天的花费都加上 $c_i$ 元，最后在体验服务的每一天都加上这一天体验的服务的总价，同时如果这天花费大于会员费，就开会员。
可是这样会超时，于是我们想到用**前缀和**和**差分**（[大佬的前缀和博客](https://blog.csdn.net/m0_74826386/article/details/143436481)和[大佬的差分博客](https://blog.csdn.net/weixin_73378557/article/details/140851590)）。在一个数组中给每一个服务的第一天加上 $c_i$，最后一天的后一天减去 $c_i$。然后跑一遍前缀和。再看有服务的每一天是会员划算还是不用会员划算，如果会员划算就在总钱数上加会员的钱，否则直接加当天钱数。问题又来了，题目中的 $a_i$、$b_i$ 最大为 $10^9$，数组开不了这么大，于是我们想到用 map 优化（[大佬的 map 博客](https://blog.csdn.net/XFDG01/article/details/137522021)）
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,c,x,y,z,ans,s,k;
map<long long,long long> m;
int main(){
	cin>>n>>c;
	for(int i=1;i<=n;i++){
		cin>>x>>y>>z;
		m[x]+=z,m[y+1]-=z;//差分
	}
	for(auto it:m){
		ans+=(it.first-k)*min(s,c);//判断哪一种花费最少
		s+=it.second;//第二天的正常花费
		k=it.first;//这一次计算的时间
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zsq9 (赞：2)

[AC 记录](https://www.luogu.com.cn/record/196010160)

## 思路

最便宜的就是开会员的钱与直接买的钱。可以使用前缀和与差分。但是由于 $a$ 和 $b$ 的取值范围很大，所以用 map。大概就是先将 $a_i$ 对应的差值加上 $c_i$，$b_i+1$ 对应的差值减去 $c_i$，分别存入映射 map 中。然后遍历一遍，每次计算当前所需费用，对 $c$ 和当天所需消费取最小值，并记录上一个切换状态的天数。最后输出总共需要的费用就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define x first//代码会简单一点
#define y second
long long n,sc;
long long a,b,c;
long long sum,ans;
map <long long,long long> opzc;
int main(){
    cin >> n >> sc;
    for(int i = 1;i <= n;i++){
        cin >> a >> b >> c;
        opzc[a] += c;
        opzc[b + 1] -= c;//前缀和和差分
    }
    long long st = 0;
    for(auto it : opzc){
        ans += (it.x - st) * min(sc,sum); 
        sum += it.y; 
        st = it.x; 
    }
    cout << ans << "\n"; 
}
```

---

## 作者：Kyl_in_2024 (赞：2)

能看出来，最优情况下每天支付的钱是会员费和不开会员要付的钱的最小值，可以想到前缀和进行优化，但是 $1 \le a_{i} \le b_{i} \le 10^9$，肯定不能通过，但是怎么优化呢？

举个例子：

```
2 3
1 6 2
2 5 1
```

|   第几天 |    1 |    2 |   3 |   4 |   5 |    6 |    7 |
| ----: | ---: | ---: | --: | --: | --: | ---: | ---: |
| 做出的修改 | $+2$ | $+1$ | $0$ | $0$ | $0$ | $-1$ | $-2$ |
| 最终的答案 |  $2$ |  $3$ | $3$ | $3$ | $3$ |  $2$ |  $0$ |

发现，$2 \sim 5$ 这一段一天要花的钱没有任何改变。

可以压缩一下：

|   第几天  |               1              |               2              |               6              |               7              |
| :----: | :--------------------------: | :--------------------------: | :--------------------------: | :--------------------------: |
|   修改   |              +2              |              +1              |              -1              |              -2              |
| 要加上的答案 | $( 0 + 2 ) \times ( 2 - 1 )$ | $( 2 + 1 ) \times ( 6 - 2 )$ | $( 3 - 1 ) \times ( 7 - 6 )$ | $( 2 - 2 ) \times ( 7 - 7 )$ |

所以，我们可以把 $a_{i}$ 端点加上 $c_{i}$，把 $b_{i}+1$ 端点加上 $-c_{i}$，把这些操作排序。

再遍历一遍，记录当前要付的钱，判答案的时候对 $C$ 取最小值，再乘以经过的天数，时间复杂度可以通过。

又是一个细节：`pair<int,int>` 默认是按 `first` 排序的，不用写结构体也不用重载运算符。

#### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
pair<int,int> a[400005];
signed main(){
	int n,c,ans=0;
	cin >> n >> c;
	for(int i=1;i<=n;i++){
		int x,y,z;
		cin >> x >> y >> z;
		a[2*i-1]={x,z};
		a[2*i]={y+1,-z};
	}
	sort(a+1,a+2*n+1);
	int now=0,lst=0;
	for(int i=1;i<=2*n;i++){
		ans+=(a[i].first-lst)*min(c,now);
		now+=a[i].second;
		lst=a[i].first;
	}
	cout<<ans;
    return 0;
} 
```

审核辛苦了～

---

## 作者：xibaohe (赞：2)

# 题目翻译

Snuke 开了一家公司，提供各种各样的服务。并且公司推出了一个称作 Snuke Prime 的会员方案。
在每天的开始，用户可以支付 $C$ 元，购买一天会员资格。拥有会员资格的期间，可以自由使用公司提供的所有服务。
高桥君想要使用这个公司的 $N$ 种服务。使用第i种服务的期间是从第 $a_{i}$ 天的开始到第 $b_{i}$ 天的结束。在没有会员资格的期间，要使用第 $i$ 种服务，每天需要支付 $c_{i}$ 元。
求出高桥君需要支付的最小合计金额。

# 题目分析
1. 利用 map 容器记录每一个服务的起始和结束时间点，将时间点作为 key，每天需要的费用作为 value。

2. 通过改变起始时间点和结束时间点的 value，即在服务开始时增加每日费用，在服务结束后减少每日费用，得到了一个时间-费用变化的映射。

3. 进行遍历处理，对于每一个时间段，比较每日费用和会员费用，选择较小的一个作为该时间段的每日费用。

4. 最后，计算并输出所有时间段的总费用，这就是需要支付的最小合计金额。

总结：这个程序使用了贪心算法的思想，即在每一个时间段都做出在当前最优的选择（选择每日费用和会员费用中的较小者），从而得到全局最优的解（支付的最小合计金额）。同时，它利用了 map 容器方便处理时间和费用的特性，降低了问题的复杂性。


# 满分代码（含详细注释）
```cpp
#include<iostream>
#include<map>
using namespace std;

int n, C; // 定义n和C为整数变量，n代表服务的种数，C代表购买一天会员资格的费用
long long last, sum, ans; // 定义last、sum、ans为长整型变量，last表示上一个处理的时间点，sum表示当前累积的每日费用，ans表示总费用
map<int, long long> s; // 定义一个map，key为int类型，value为long long类型，表示时间点与每日费用的映射关系
map<int, long long> :: iterator it; // 定义一个迭代器，用来遍历map
 
int main()
{
	cin >> n >> C;
	for(int i = 1; i <= n; i++) // 对每一种服务进行处理
	{
		int a, b, c;
		cin >> a >> b >> c; // 输入服务的开始时间、结束时间和每日费用
		s[a] += c; // 在服务开始的时间点，每日费用增加
		s[b+1] -= c; // 在服务结束的时间点的下一天，每日费用减少
		//这两行代码是在进行"差分"操作，常用于优化时间复杂度。
//s[a] += c; 这一行是表示从第 a 天开始，每天的服务费用会增加 c 元。它在 map 中对应 a 时间点增加了 c 的值，表示这一天开始的服务的费用。
//s[b+1] -= c; 这一行表示在第 b+1 天，也就是第 i 种服务结束后的第一天，每天的服务费用会减少 c 元。实际上，这是撤销前面在 a 时间点增加的 c 的费用，因为在 b+1 这一天，第 i 种服务已经结束，不再需要这部分费用。
//使用这种差分的方法，我们可以很方便地知道在任何特定的时间点，每日服务的费用是多少。我们只需要遍历 map，并累加每个时间点的值（包括正值和负值），就可以得到这一天的服务费用总和。
	}

	for(it = s.begin(); it != s.end(); it++) // 遍历整个时间线
	{
		ans += min(sum, 1ll*C) * (it->first - last); // 计算当前时间段的费用，取每日费用和会员费用的较小值，乘以时间段的长度，加到总费用中
		last = it->first; // 更新上一个处理的时间点
		sum += it->second; // 更新当前累积的每日费用
	}
	cout << ans << endl; // 输出总费用
 
	return 0;
}

```


---

## 作者：loser_seele (赞：2)

注意到对于某一天的情况，设需要支付的费用为 $ s_i $，则实际上需要支付的费用为 $ \min(s_i,C) $。

所以问题在于如何计算 $ s_i $。不难想到前缀和实现区间加操作，然而值域过大无法通过。于是类似差分的思想，对于一个区间加操作 $ {l,r,c} $，转化为操作 $ [1,r,c] $ 和操作 $ [1,l-1,-c] $。

然后将所有需要操作的端点排序，之后对于每个区间分别处理答案。观察到排序后区间的端点单调不降，于是可以维护一个当前标记，设当前标记为 $ tag $，区间长度为 $ len $，则统计答案时加上 $ len \times \min(tag,C) $ 即可。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ll n, cc;
    cin>>n>>cc;
    vector<pair<int,int> > arr;
    for(ll i=0; i<n; i++)
    {
    	ll a, b, c;
    	cin>>a>>b>>c;
    	arr.push_back({a-1,c});
    	arr.push_back({b,-c});
    }
    sort(arr.begin(),arr.end());
    ll ans = 0;
    ll fees = 0;
    ll last = 0;
    for(auto a:arr)
    {
    	ll x = a.first;
    	ll y = a.second;
    	if(x != last)
        {
    		ans += min(cc, fees) * (x - last);
    		last = x;
    	}
    	fees += y;
    }
    cout<<ans;
}
```


---

## 作者：wangyihao0411 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc188_d)

### 前言

[博客戳这里](https://www.luogu.com.cn/article/uisa9yi2/edit)  
十年 OI 一场空，不开 long long 见祖宗。

### 思路

首先我们很容易看出来，最便宜的就是开会员的钱与直接买的钱。因此可以想到是要使用前缀和与差分。  
但是由于 $a$ 和 $b$ 的取值范围很大，因此考虑用 map。

### 代码

思路大家都看懂了吧，~~看不懂的话我也没办法了~~。  
下面附上 AC 代码，~~简单~~做了点注释。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<map>
#define int long long //不用担心爆int了！ 
using namespace std;
map<int,int> ma;
int a,b,c;
int n,m,ans,sum,k;
signed main() //同int，但由于上面把int都换成了long long，只能使用signed 
{
	cin >> n >> m;
	for(int i=1;i<=n;i++)
	{
		cin >> a >> b >> c;
		ma[a]+=c;
		ma[b+1]-=c;
	}
	for(auto it:ma) //c++14新功能，自动推倒变量类型 
	{
		ans+=(it.first-k)*min(sum,m);
		sum+=it.second;
		k=it.first;
	}
	cout << ans;
    return 0;
}
```

最后，感谢大家的耐心观看。

------------

### update

 $2024/7/7$：发布该题解

---

## 作者：zhouzihang1 (赞：1)

# [ABC188D] Snuke Prime题解

## 思路

题意很好理解，就是差分，由于 $a_i,b_i$ 范围是 $1 \le a_i \le b_i \le 10^9$ 用数组会炸，所以考虑用 map。

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
map<int,int> m;
int a,b,c;
int n,C,ans,sum,k;
int main()
{
	scanf("%d%d",&n,&C);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		m[a]+=c;
		m[b+1]-=c;//差分 
	}
	for(auto it:m)
	{
		ans+=(it.first-k)*min(sum,C);//记录答案 
		sum+=it.second;//累计消费 
		k=it.first;//记录状态 
	}
	printf("%d",ans);
    return 0;
}
```

然后，你会惊喜的发现，你 WA#16

### 十年OI一场空，不开long long见祖宗！

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
map<long long,long long> m;
long long a,b,c;
long long n,C,ans,sum,k;
//十年 OI 一场空，不开 long long 见祖宗！
int main()
{
	scanf("%lld%lld",&n,&C);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&a,&b,&c);
		m[a]+=c;
		m[b+1]-=c;//差分 
	}
	for(auto it:m)
	{
		ans+=(it.first-k)*min(sum,C);//记录答案 
		sum+=it.second;//累计消费 
		k=it.first;//记录状态 
	}
	printf("%lld",ans);
    return 0;
}
```



---

## 作者：autumnrain_qhc (赞：1)

# 思路

不难看出，本题可以开数组，维护每一个数的前缀和解决。

但这样需要的空间太多，有没有什么办法呢？

有，用 `map` 维护每个关键点的前缀和，再记录每一段的长度就可以解决了。

# AC代码

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
map<int, int> mp;
int n, C, a, b, c, ans, pre, bi;
signed main(){
    cin >> n >> C;
	for(int i = 1; i <= n; i++){
		cin >> a >> b >> c;
		mp[a] += c, mp[b + 1] -= c;
	}
	for(auto i : mp){
		ans += min(C, pre) * (i.first - bi);
		bi = i.first;
		pre += i.second;
	}
	cout << ans;
	return 0;
}

```


---

## 作者：Like_Amao (赞：0)

**前言**

[题目传送门](https://www.luogu.com.cn/problem/AT_abc188_d)

**思路**

这道题很差分，所以用差分来做，又因为数据较大，所以我们要用 map 来优化。

**注意事项**

记得开 **long long**。

**代码**


```cpp
#include<bits/stdc++.h> 
using namespace std;
map<long long,long long>mp;
int main()
{
	long long n,c,ans=0,sum=0,t=0;
	cin>>n>>c;
	for(long long i=1;i<=n;i++)
	{
		long long x,y,z;
		cin>>x>>y>>z;
		mp[x]+=z;
		mp[y+1]-=z;
	}
	for(auto i:mp)
	{
		ans+=(i.first-t)*min(sum,c);
		sum+=i.second;
		t=i.first;
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
支付 $C$ 元可购买一天会员。

你一共要使用 $N$ 件工具，每件工具会在 $a_i$ 到 $b_i$ 天内使用，若其中某天你没有会员，则需支付 $c_i$ 元。

问最少需要支付多少元。
# 思路
如果不考虑时空限制，可以暴力维护每一天不充会员所需支付的钱，然后与充会员的钱取小计入贡献。

然后看到 $N\le2\times10^5$，说明时间节点是不超过 $4\times10^5$ 个且时间段小于 $4\times10^5$ 个的，于是可以想到离散化处理时间段。

将时间点进行离散化，然后差分处理出离散后不同时间段不充会员每天所需支付的钱，与充会员的钱取其小乘以时间段跨度。

这里的离散有一点不同，考虑一个样例：
```
2 7
1 5 4
3 7 4
```
时间节点有四个数，也就是 $1,3,5,7$，用脑子算不难知道 $1$ 到 $2$ 和 $6$ 到 $7$ 是每天 $4$ 元，$3$ 到 $5$ 是每天 $8$ 元。

这个时候会发现，时间段两个节点的截取似乎并没有很规律，像 $3$ 到 $5$ 刚好取到两个节点，而 $1$ 到 $2$ 和 $6$ 到 $7$ 一个是右端点 $3$ 减少 $1$，一个是左端点增加 $1$。

这里的 $2$ 是 $3-1$，这个时候我们不妨将 $5$ 看作 $6-1$，$7$ 看作 $8-1$，于是本来的时间节点变为 $1,3,6,8$，其实就是每个 $b_i$ 增加了 $1$，但是却有了规律，每个时间段的左右节点等于一个时间节点以及往后数的第一个时间节点减一。

从另一个方面想，若只考虑第一行的两个时间节点 $1,5$，不难知道，首先 $1$ 定然是某个时间段的左端点，而 $6(6=5+1)$ 也大概率是某个时间段的左端点（这里的小概率是指 $5$ 已经为最大的时间节点，那么此时其不会为左端点）。

同时，如果某个区间的左端点大于等于 $1$ 且与 $[1,5]$ 重合了，那么 $1$ 到这个区间的左端点减一成一个时间段（没有重合的部分），所以减一自成一种规律，于是我们考虑到上一段提到的将此处规律扩大，也就是将区间右端点加一，此时该规律可应用于全局。

离散后，差分处理，这个很简单不多说了。然后是比较，更简单，不多嘴了，直接上代码。
# 代码
```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N=2e5+5;

int n,c;
int s[N],t[N],us[N];
int id,rev[N<<1];
int pay[N<<1];
int ans;

map<int,int> mp;

signed main(){

    scanf("%lld%lld",&n,&c);

    for(int i=1;i<=n;i++){
        
        scanf("%lld%lld%lld",&s[i],&t[i],&us[i]);

        t[i]++;

        mp[s[i]]=0;
        mp[t[i]]=0;
    }

    for(auto v:mp){

        mp[v.first]=++id;
        rev[id]=v.first;
    }
    
    for(int i=1;i<=n;i++){

        pay[mp[s[i]]]+=us[i];
        pay[mp[t[i]]]-=us[i];
    }

    for(int i=1;i<id;i++){

        pay[i]+=pay[i-1];

        ans+=(min(pay[i],c))*(rev[i+1]-rev[i]);
    }

    printf("%lld",ans);
    return 0;
}
```

---

## 作者：lilong (赞：0)

看到这题，第一反应是用线段树。但本题数据 $1 \le a_i \le b_i \le 10^9$，时间、空间复杂度均无法接受，于是改变思考方向。

维护区间修改的另一种方法是差分。但是由于区间长度很长，就不能对整个差分数组进行计算。取而代之的有一种方法，即将所有的有差分值的点记录下来，按其时间先后顺序进行排序，最后再依次枚举每一个点，计算当前每天应交的钱，再计算当前区间的长度，即可求出每一个区间的应交的钱。

注意，计算区间值时应当用当前每天应交的钱与 $C$ 的较小值来乘（$C$ 为题目中所述含义），**但不能更新每天应交的钱。**

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
int a,b,c,len,now,money,t,n,k,ans;
struct atc
{
	int p;
	int q;	
}d[1000001];
bool cmp(atc x,atc y)
{
	return x.p<y.p;
}
signed main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>c;
		len++;
		d[len].p=a;
		d[len].q=c;
		len++;
		d[len].p=b+1;
		d[len].q=-c;
	}
	sort(d+1,d+len+1,cmp);
	money=d[1].q;
	now=d[1].p;
	for(int i=2;i<=len;i++)
	{
		t=d[i].p;
		if(t!=now) ans+=(t-now)*min(money,k);
		now=t;
		money+=d[i].q;
	}
	cout<<ans;
	return 0;
} 
```


---

