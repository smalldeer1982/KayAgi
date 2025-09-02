# [ABC368C] Triple Attack

## 题目描述

你正在玩一款游戏。

游戏中有 $N$ 个敌人排成一排，第 $i$ 个敌人有 $h_i$ 的血量,当敌人血量降至 0 或以下时该敌人被消灭。  

从第 1 只敌人开始打，时间 $T$ 从 0 开始，重复执行如下操作:

- $T$ 增加 1，若此时 $T$ 为 3 的倍数，当前敌人掉 3 滴血，否则掉 1 滴血。

 求消灭全部敌人所需时间 $T$。

---

## 说明/提示

采取的行动如下:

- $T=1$，攻击第 $1$ 个敌人，第一个敌人的血量为 $6-1=5$；
- $T=2$，攻击第 $1$ 个敌人，第一个敌人的血量为 $5-1=4$；
- $T=3$，攻击第 $1$ 个敌人，第一个敌人的血量为 $4-3=1$；
- $T=4$，攻击第 $1$ 个敌人，第一个敌人的血量为 $1-1=0$；
- $T=5$，攻击第 $2$ 个敌人，第二个敌人的血量为 $2-1=1$；
- $T=6$，攻击第 $2$ 个敌人，第二个敌人的血量为 $1-3=-2$；
- $T=7$，攻击第 $3$ 个敌人，第三个敌人的血量为 $2-1=1$；
- $T=8$，攻击第 $3$ 个敌人，第三个敌人的血量为 $1-1=0$；


## 样例 #2

### 样例输入 #2

```
9
1 12 123 1234 12345 123456 1234567 12345678 123456789
```

### 样例输出 #2

```
82304529
```

## 样例 #3

### 样例输入 #3

```
5
1000000000 1000000000 1000000000 1000000000 1000000000
```

### 样例输出 #3

```
3000000000
```


注意数据溢出。


---

- $ 1 \leq\ N \leq\ 2\times 10^5 $
- $ 1 \leq\ H_i \leq 10^9 $
- 所有输入均为整数

## 样例 #1

### 输入

```
3
6 2 2```

### 输出

```
8```

## 样例 #2

### 输入

```
9
1 12 123 1234 12345 123456 1234567 12345678 123456789```

### 输出

```
82304529```

## 样例 #3

### 输入

```
5
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
3000000000```

# 题解

## 作者：_Gabriel_ (赞：3)

### 题意

有 $n$ 个敌人，生命值为 $h_i$。

可以将初始化为 $0$ 的 $T$ 重复以下操作：

将 $T$ 增加 $1$，可攻击最前方生命值 $\ge 1$ 的敌人生命值减 $1$，若 $T$ 是 $3$ 的倍数，敌人的生命值会减少 $3$。

当所有敌人的生命值 $\le 0$，求 $T$。

### 思路

注意攻击顺序从左到右，当前敌人生命值 $h_i \le 0$ 才能攻击下一个人。

不难发现，$T$ 每增加 $3$，可以让 $h_i$ 减少 $5$，那么这三组行动就会重复 $\lfloor\frac{h_i}{5}\rfloor$ 组，按照这规律即可解决此题。

时间复杂度 $O(n)$。

### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int N = 2e5 + 10;
ll a[N];
int n;
ll now;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		int q = a[i] / 5;
		now += q * 3;
		a[i] -= q * 5;
		while (a[i] > 0) {
			now++;
			if (now % 3 == 0) {
				a[i] -= 3;
			} else {
				a[i]--;
			}
		}
	}
	cout << now;
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：3)

一个一个人计算。对于一个人，先把 $T$ 调整不超过 $2$ 次直到 $3|T$，然后就 $5$ 点伤害/$3$ 次攻击为一组，直接除法可以得到几组，然后计算即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, x, ans, tmp;
signed main(){
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &x);
		while(ans % 3 && x > 0){
			ans++;
			if(ans % 3 == 0) x -= 3;
			else x--;
		}
		tmp = x / 5;
		ans += tmp * 3;
		x -= tmp * 5;
		while(x > 0){
			ans++;
			if(ans % 3 == 0) x -= 3;
			else x--;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：3)

显然，每次攻击产生的伤害是 $3$ 次一周期，且每个周期会产生 $5$ 点伤害。

所以，我们先把当前人的生命变成它除以 $5$ 的余数，把答案加上生命除 $5$ 再乘 $3$ 的结果。

接下来，我们继续攻击此人。我们维护当前攻击和上一次攻击（为了推出下一次）的伤害。每攻击一次，把生命减少当前伤害，再更新当前伤害，答案加一。直到此人生命小于等于 $0$ 为止。

最后，输出答案即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200001],an,no=1,pr;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		an+=a[i]/5*3;
		a[i]%=5;
		while(a[i]>0){
			a[i]-=no,an++;
			if(no==1&&pr==1)no=3,pr=1;
			else if(no==3&&pr==1)pr=3,no=1;
			else pr=1;
		}
	}
	cout<<an;
	return 0;
}
```

---

## 作者：yh888 (赞：2)

## [ABC368C] Triple Attack 题解

[传送门](https://www.luogu.com.cn/problem/AT_abc368_c)

### 题目大意

给定 $n$ 个数 $h_1$ 到 $h_n$，每次操作先将 $t$ 加 $1$，将第一个大于 $0$ 的数 $h_i$ 减去一个数，当 $t$ 是 $3$ 的倍数则减 $3$，否则减 $1$，重复以上操作，直到 $h_i\le 0$。$t$ 的初始值是 $0$，求当所有数都小于或等于 $0$ 时 $t$ 的值。

### 分析

暴力做法不难想到。$\\$
每次输入一个 $h_i$ 后，模拟 $h_i$ 减到 $0$ 的过程，求出 $t$。
```cpp
while (h[i] > 0) {
  t++;
  h[i] -= (t % 3 == 0) ? 3 : 1;		//t是3的倍数则减3
}
```
然而时间复杂度近似 $O(n\times h)$，观察数据范围明显会 TLE。

考虑用数学方法。$t$ 是在 $3$ 的倍数时会让 $h_i$ 减 $3$，让人想到对 $t$ 进行分组。每 $3$ 个数会让 $h_i$ 减 $1+1+3=5$。因此可以直接用 $\lfloor h_i\div 5\rfloor$ 算出 $t$ 需要加多少个 $3$，再计算出 $h_i$ 剩余部分，即 $h_i\bmod 5$ 的部分。$\\$
时间复杂度近似 $O(n)$。

友情提示：不开 long long 见祖宗。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n, h[N], t;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
		t += 3 * (h[i] / 5);
		h[i] %= 5;
		while (h[i] > 0) {
			t++;
			h[i] -= (t % 3 == 0) ? 3 : 1;
		}
	}
	cout << t;
	return 0;
}
```

---

## 作者：XXh0919 (赞：2)

我又来写题解啦！

### 题意

给定 $N$ 个人的生命值，每次攻击可以使最前面的人的生命值减少，当当前攻击次数为 $3$ 的倍数时，攻击力为 $3$，否则攻击力为 $1$。求最少攻击次数使得 $N$ 个人的生命值全部为非正整数。

### 解法

根据 C 题的惯例，直接模拟肯定会爆炸，所以考虑优化。可以观察到当当前攻击次数为 $3$ 的倍数时攻击力会变为 $3$，所以我们可以将三次攻击看作一次攻击，攻击力为 $5$。于是我们可以先算出最前面的人最多能抗多少次攻击，然后对于剩下的血量进行暴力模拟即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pi pair<int,int>
#define mkp(a,b) make_pair((a),(b)) 
#define IOS cin.tie(0)->sync_with_stdio(0)
using namespace std;
const int N=2e6+15;

int n,ans;
int h[N];

signed main(){
	cin>>n;
	rep(i,1,n)cin>>h[i];
	rep(i,1,n){
		ans+=h[i]/5*3;//三次为一次
		h[i]-=h[i]/5*5;//血量减少
		while(h[i]>0){//模拟
			++ans;
			if(ans%3==0)h[i]-=3;
			else --h[i];
		}
	}
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：Walter_Fang (赞：1)

题意言简意赅无需赘述。注意每次只攻击最前面生命值为正数的怪物。

### 思路解析
由题意可知怪物生命减少数量以 `1 1 3` 为一组循环，所以只需先将每组血量一起减少 $5$，如果这只怪物在本回合没有死则再次执行上述操作即可。

### 代码实现
代码实现非常简单。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+10;
ll n,i,x,t,f,a[N];
int main(){
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=1;i<=n;i++){
		if(a[i]>0&&!f)a[i]--,f++,x++;
		if(a[i]>0&&f==1)a[i]--,f++,x++;
		if(a[i]>0&&f==2)a[i]-=3,f=0,x++;
		t=a[i]/5;x+=t*3;a[i]-=t*5;
		if(a[i]>0)a[i]--,f++,x++;
		if(a[i]>0)a[i]--,f++,x++;
		if(a[i]>0)a[i]-=3,f=0,x++;
	}
	cout<<x;
}
```

---

## 作者：Walrus (赞：1)

ex 题，喜提 4 发罚时。

## 题意

有 $n$ 只怪，第 $i$ 只有 $a_i$ 点血，还有一个初始化为 0 的变量 $T$，每次对最前面没死的怪（定义怪物血量小于等于 0 就算死）进行如下操作：

- 先将 $T$ 加 1，若 $T$ 能被 3 整除，则对怪造成 3 点伤害，否则造成 1 点伤害。

求杀死所有怪后的 $T$ 值。

细节题，考虑每三次分一组，一组伤害为 5，如果不能被整三次打死，则额外拿东西记录即可，比较简单但细节较多，具体看代码。

```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define pb push_back
#define int long long
using namespace std;
const int N = 2e5 + 5;

int a[N], n, k, ans, t, lt;//lt 上一轮没打完的次数

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	
	rep(i, 1, n) {
		if(lt && lt + 2 >= a[i]) {
			if(lt == 1) 
				++ans, lt = 0;
			else {
				if(a[i] <= 1) {
					if(i < n && a[i + 1] <= 3) ans += lt, lt = 0, ++i;
					else a[i + 1] -= 3, ans += lt, lt = 0;
				}
				else ans += lt, lt = 0;
			}
			continue;
		}
		int p = (a[i] - (lt ? lt + 2 : lt)) % 5;
		ans += lt + (a[i] - (lt ? lt + 2 : lt)) / 5 * 3;
		if(p >= 3) p = 3, ans += 3;
		else ans += p;
		if(p) lt = 3 - p;
		else lt = 0;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 题意

有 $N$ 个敌人排成一排，第 $i$ 个敌人的生命力是 $H_i$。我们会从第一个敌人开始，依次攻击，同时记录一个变量 $T$，每次攻击时 $T+1$。对于每个敌人，只有把他的血量打到 $H_i \le0$ 才行。如果现在的 $T\bmod3=0$，那就可以打掉 3 的生命值，否则只能打掉 1 的生命值。请问当打完所有敌人后，$T$ 的值为多少。
## 分析

首先我们应该意识到，对于每个敌人去循环地模拟每次攻击肯定是不行的，因为 $N$ 是非常大的，应该会超时。那么很容易的想到，我们对于每个敌人 $O(1)$ 地求出需要攻击当前这个敌人多少次，记为 $cnt$，然后 $T+cnt$ 就可以表示出这一轮以后 $T$ 变为的数。

那么现在的难点就是我们需要找出当前 $T \bmod 3$ 是多少，才能知道对于这一个敌人我们的循环是从哪里开始，如 ```1 1 3```，```1 3 1``` 或 ```3 1 1```。那么我们就可以先求出当前的 $T$ 是在循环中的那一个位置，然后将它补齐到我们统一的一个循环中。接下来只需要 $T\div5$ 后再算出后面还剩余了多少生命力，我们手动把剩下的打掉就行了，具体实现方式看代码吧。
## 代码+注释

大家一定要记得开 long long。
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,h[200005],t;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>h[i];
	for(int i=1;i<=n;i++){
		//这里进行的是补齐操作，我是把它补成 1 1 3 
		if(t%3==1){
			//补第一位 
			h[i]-=1;
			t++;
			//如果刚补完就已经打败了，直接进行下一个 
			if(h[i]<=0) continue;
			//补第二位 
			h[i]-=3;
			t++;
			if(h[i]<=0) continue;
		}
		if(t%3==2){
			//只用补一位 
			h[i]-=3;
			t++;
			if(h[i]<=0) continue;
		}
		//看看有几轮 
		int a=h[i]/5;
		t+=a*3; //记得每一轮有3次 
		if(h[i]%5==0) //没有剩下的，正好打完 
			continue;
		h[i]-=a*5;//求出剩下的生命力 
		if(h[i]<=1){//只用打一次 
			t++;
			continue;
		}
		if(h[i]<=2){//打两次 
			t+=2;
			continue;
		}
		t+=3;//打三次 
	}
	cout<<t;
	return 0;
}
```

---

## 作者：longlong_int (赞：1)

这道题一看就是模拟，但是如果 $T$ 一个一个加，连样例 3 都过不去，所以，我们探究一下 $T$ 变化、敌人减血的规律：

- $T$ 每增加 3，第一个有血的敌人（下标为第 `head` 个）的血量将减少 5。

所以，第一个有血的敌人与 $T$ 的变化是这样：

$$T \to 3 \times \lfloor h_{head} \div 5 \rfloor,\space\space h_{head} \to (h_{head} \text{ mod } 5)$$

然后模拟即可。注意不要在 `vector` 里用 `vec.erase(vec.begin())`，这个操作是 $O(n)$ 的。  
需要删除时使用 $head \leftarrow head+1$ 即可。

[源代码](https://atcoder.jp/contests/abc368/submissions/57058511)，[~~T 掉的源代码~~](https://atcoder.jp/contests/abc368/submissions/57053525)

---

## 作者：lcfollower (赞：1)

~~赛后才觉得是简单题，但是我赛时没过。~~

明显可以分周期，每 $3$ 个怪兽减少的值分为一个周期，这个周期为 $\left(1,1,3\right)$。那么对于怪物 $i$，重复这样 $T$ 会增加 $\lfloor\frac{a_i}{1+1+3}\rfloor\times 3$。

当然不免还有余数，即 $a_i\bmod 5 \ne 0$，这时候直接暴力减即可，最多减 $4$ 次而已，不影响时间复杂度。

这时候你可能会和我一样，对于 $T\bmod 3\ne 1$（即结束部位循环的第一个 $1$）的情况下暴力增加，然后~~也许哪里打挂~~，但是仔细想一想，$\left(1,3,1\right)$ 以及 $\left(3,1,1\right)$ 也可以做为一个周期。

时间复杂度为 $\mathcal O(n)$，代码[在这](https://atcoder.jp/contests/abc368/submissions/57109414)。

---

## 作者：linjinkun (赞：1)

首先看到 $1 \le N \le 2 \times 10^5,1 \le A_i \le 10^9$，明显暴力是不行的，我们可以从暴力的角度考虑优化，发现最容易优化的部分是对于每一个敌人计算要攻击多少次，但是却发现很难通过数学方法计算出每一个敌人计算要攻击多少次，这个时候……二分大法好！！我们可以二分打一个敌人需要攻击多少次，发现具有单调性（这个不用我说了吧），于是直接写代码！这里给出代码：
```cpp
int l = 1,r = a[i],ans = 0;
while(l<=r)
{
  int mid = l+r>>1;
  int s = (T+mid)/3-T/3;
  int day = mid-s;
  if((a[i]-s*3)<=day)
  {
    ans = mid;
    r = mid-1;
  }
  else
  {
    l = mid+1;
  }
}
T+=ans;
```
解释一下重点的几句话，首先是 ```int s = (T+mid)/3-T/3```，这句话其实是计算区间 $[T+1,T+mid]$ 中有几个 $3$ 的倍数，原理很简单，就相当于 $f(l,r) = f(1,r)-f(1,l-1)$，顺便说一下计算 $3$ 的倍数的用处，我们发现攻击对敌人造成的伤害只有 $3$ 和 $1$，那么我们发现攻击为 $3$ 是比较特殊的情况才会出现，那么我们可以预处理出区间 $[T+1,T+mid]$ 中有几个 $3$ 的倍数，相当于计算区间 $[T+1,T+mid]$ 中有几次会触发暴击（就是攻击为 $3$），接下来下一句话：```int day = mid-s```，是在计算区间 $[T,T+mid]$ 中有几次攻击为 $1$，接下来是 ```if((a[i]-s*3)<=day)```，意思是如果这个敌人的血量减去特殊的攻击为 $3$ 的攻击，剩下的攻击为 $1$ 的攻击是否能击倒他。

***注：不开 ```long long``` 见祖宗。***

讲完重点之后直接给代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int a[200005];
signed main()
{
	int n;
	scanf("%lld",&n);
	for(int i = 1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	int T = 0;
	for(int i = 1;i<=n;i++)
	{
		int l = 1,r = a[i],ans = 0;
		while(l<=r)
		{
			int mid = l+r>>1;
			int s = (T+mid)/3-T/3;
			int day = mid-s;
			if((a[i]-s*3)<=day)
			{
				ans = mid;
				r = mid-1;
			}
			else
			{
				l = mid+1;
			}
		}
		T+=ans;
	}
	printf("%lld",T);
	return 0;
}
```

---

## 作者：Zhi_ptb (赞：0)

[更好的阅读体验](https://www.cnblogs.com/shengzhu/p/18378838)

# updata
2025/2/16 修改博客网址。

# 题意概述

有 $N$ 个数，分别为 $H_1,H_2,H_3……H_N$。

你将使用初始化为 $0$ 的变量 $T$ 重复以下操作，直到所有数的值都变为 $0$ 或更少。

- 将 $T$ 增加 $1$ 。然后，减少最前方 $H_i$ 值大于等于 $1$ 的值。如果 $T$ 是 $3$ 的倍数，$H_i$ 的值会减少 $3$ ；否则，$H_i$ 的值会减少 $1$。

当所有 $H_i$ 的值变为 $0$ 或更少时，求 $T$ 的值。

# 思路

先找规律 $T$ 加的时候两次不是三的倍数，第三次是，根据 $1 + 1 + 3 = 5$ 那么可得当 $5 \le H_i$ 时， $T$ 便增加了 $\lfloor H_i \div 5 \rfloor \times 3$，然后 $H_i \bmod 5$，剩下 $H_i \le 4$ 的情况咱直接暴力求解即可。

# 代码

```
#include <bits/stdc++.h>
#define ll long long
#define N 200001
#define mod 998244353
using namespace std;
mt19937_64 mrand(random_device{}());

int n;
ll h[N], t;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &h[i]);
    for (int i = 1; i <= n; i++) {
        if (h[i] >= 5) {
            t += h[i] / 5 * 3;
            h[i] %= 5;
        }
        while (h[i] > 0) {
            t += 1LL;
            if (t % 3)
                h[i]--;
            else
                h[i] -= 3;
        }
    }
    printf("%lld", t);
}
```

---

## 作者：x1489631649 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc368_c)
### 分析
我们通过观察发现 $n(1 \le n \le 2 \times 10^5)$ 并且 $a_i(1 \le a_i \le 10^9)(1 \le i \le n)$。而通过数据范围我们可以发现，**最简单的暴力只能得到一个无助的爆零。因为时间复杂度会超时**。不甘于只得到 $300$ 的我又开始尝试新的方法。既然我们枚举不可以那就开始找规律吧。**我发现 $t$ 每三个就可以看做一轮，此时的伤害为 $5$**。然而问题又来了，每一轮都是从 $t \equiv 0 \pmod 5$ 开始的吗？显然这是不一定的，所以我们先减掉上一轮剩下的伤害，当然可能他还没减完就已经小于等于 $0$ 了。
### Code
```
#include<bits/stdc++.h>
using namespace std;
long long a[200005]; 
int main()
{
	long long n,t=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(t%3==1&&a[i]>0)
		{
			t++;
			if(a[i]-1>0)//没有处理第二次操作是因为他会进入下一个判断。
				a[i]=a[i]-1;
			else a[i]=0;//注意要等于 0，负数对 5 取模也是有结果的不过是负数。会令答案产生错误。
		}
		if(t%3==2&&a[i]>0)//不能加 else 因为这样会让上面的操作结束进不来。
		{
			t++;
			if(a[i]-3>0)
				a[i]=a[i]-3;
			else a[i]=0;
		}
		t+=(a[i]/5)*3;
		a[i]%=5;
		if(a[i]==1)
			t+=1;
		else if(a[i]==2)
			t+=2;
		else if(a[i]>=3)
			t+=3;
	}
	cout<<t;
}
```
### 时间复杂度
时间复杂度为 $O(n)$，显然可以通过。

---

## 作者：KobeBeanBryantCox (赞：0)

# AT_abc368_c [ABC368C] Triple Attack 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc368_c)。

--------------------

## 题意

你正在玩一个游戏。

有 $N$ 个敌人排成一排，最前面的 $i$ 个敌人的生命值是 $H_i$ 。

你将使用初始化为 $0$ 的变量 $T$ 重复以下操作，直到所有敌人的生命值都变为 $0$ 或更少。

- 将 $T$ 增加 $1$ 。然后，攻击最前方生命值大于等于 $1$ 的敌人。如果 $T$ 是 $3$ 的倍数，则敌人的生命值会减少 $3$ ；否则，生命值会减少 $1$ 。

当所有敌人的生命值变为 $0$ 或更少时，求 $T$ 的值。

-----------------------

## 题解

容易发现敌人的生命值的周期是 $5$，每一次周期需要 $3$ 次操作，于是就能 $O(n)$ 解决。

还要注意一下小细节，比如最后不够的情况，下一次要先减到原来的状态。

具体见代码。

-------------------

## AC 代码

```cpp
#include<bits/stdc++.h>
#define Code using
#define by namespace
#define wjb std
Code by wjb;
#define int long long
int in()
{
	int k=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')k=k*10+c-'0',c=getchar();
	return k*f;
}
void out(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
const int N=2e5+10;
int h[N];
signed main()
{
	int n=in();
	for(int i=1;i<=n;i++)h[i]=in();
	int ans=0,t=1;
	for(int i=1;i<=n;i++)
	{
		if(t==2)h[i]--,ans++,t=3;
		if(t==3&&h[i]>0)h[i]-=3,ans++,t=1;
		if(h[i]==1)h[i]=0,t=2,ans++;
		else if(h[i]==2)h[i]=0,t=3,ans+=2;
		else if(h[i]>=3&&h[i]<=5)h[i]-=5,t=1,ans+=3;
		if(h[i]<0)continue; // 以上把上次剩下的操作减掉
		ans+=h[i]/5*3,h[i]%=5; // 5 为周期，次数为 3
		while(h[i]>0)
			if(t!=3)h[i]--,ans++,t=t%3+1;
			else h[i]-=3,ans++,t=1; // 最后不够减特判
	}
	out(ans);
	return 0;
}
```

-----------------

## 后记

若讲得不对，欢迎提出错误；若讲得不清楚，欢迎提问。

注意事项：十年 oi 一场空，不开 long long 见祖宗！

---

## 作者：liluhexuan (赞：0)

~~一道大水题~~

首先，我们可以按题面模拟。但时间复杂度约为 $O(\sum a_i)$，肯定无法通过。

但实际上我们可以用 $O(1)$ 的时间复杂度找到在某一位士兵趋势后的 $t$，因为每攻击三次所打掉的血量为 $5$，所以我们可以先看每位士兵会挨多少个三次。然后根据这时的 $t$ 进行特判。如果 $t \bmod 3=1$，那么这个士兵接下来就会受到 $1,1,3$ 的伤害。那么，如果这个士兵还有 $1$ 的血量，那他还会在挨 $1$ 次；如果这个士兵还有 $2$ 的血量，那他还会在挨 $2$ 次；如果这个士兵还有 $2$ 以上的血量（不可能有 $4$ 以上的血量，因为如果他的血量大于 $4$，他还会再挨一个三次）他就会再挨 $3$ 次。其他情况同理，下面这是各种情况的表格：

||$t \bmod 3=1$|$t \bmod 3=2$|$t \bmod 3=0$|
|:-:|:-:|:-:|:-:|
|攻击情况|$1,1,3$|$1,3,1$|$3,1,1$|
|血量还剩 $0$|$0$|$0$|$0$|
|血量还剩 $1$|$1$|$1$|$1$|
|血量还剩 $2$|$2$|$2$|$1$|
|血量还剩 $3$|$3$|$2$|$1$|
|血量还剩 $4$|$3$|$2$|$2$|

然后，我们只要按这个模拟就行啦。

```cpp
#include<iostream>
using namespace std;
#define int long long
signed main(){
	int n,t=1;
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		t+=a/5*3;
		if(t%3==1){
			if(a%5==1) t++;
			if(a%5==2) t+=2;
			if(a%5>2) t+=3;	
		}
		else if(t%3==2){
			if(a%5==0) continue;
			if(a%5==1) t++;
			else t+=2;
		}
		else{
			if(a%5==0) continue;
			if(a%5<=3) t++;
			else t+=2;
		}
	}
	cout<<t-1;
	return 0;
}

```

---

## 作者：pengzy (赞：0)

### 题意
给你 $n$ 敌人，和一个攻击力 $T$，攻击力 $1$，$1$，$3$ 循环。用当前攻击力攻击敌人（从左到右攻击），当他生命值小于等于零时停止攻击。问使所有敌人死亡要攻击多少下。

### 思路
我们以攻击力 $5$ 为一个循环，用变量 $T$ 来记录**上一次攻击完后当前的攻击里是多少**，即判断是否是 $3$ 的倍数。然后根据取余情况进行讨论。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,h[200005],ans,T=0;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>h[i];
	for(int i=1;i<=n;i++) {
		if(h[i]%5==0)ans+=(h[i]/5*3);
		else if(h[i]%5==1) {
			ans+=(h[i]/5*3+1);
			T++;
		}
		else if(h[i]%5==2) {
			if(T%3==2)ans+=(h[i]/5*3+1),T++;
			else ans+=(h[i]/5*3+2),T+=2;
		}
		else if(h[i]%5==3) {
			if(T%3==2)ans+=(h[i]/5*3+1),T++;
			else if(T%3==1)ans+=(h[i]/5*3+2),T+=2;
			else ans+=(h[i]/5*3+3);
		}
		else if(h[i]%5==4) {
			if(T%3==2)ans+=(h[i]/5*3+2),T+=2;
			else if(T%3==1)ans+=(h[i]/5*3+2),T+=2;
			else ans+=(h[i]/5*3+3);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

你说的对，但我选择大力分讨。

每 $3$ 个时间能打 $5$ 点生命，所以按生命模 $5$ 分类，再依据时刻模 $3$ 分类讨论。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, a[N];

long long get(int m, int x) {
	if (x == 1) return 1;
	int st = x % 5;
	if (st == 0) return x / 5 * 3;
	if (st == 1) return (x / 5 - 1) * 3 + 4;
	if (st == 2) return m == 2 ? ((x / 5 - 1) * 3 + 4) : ((x / 5 - 1) * 3 + 5);
	if (st == 3) {
		if (m == 2) return (x / 5 - 1) * 3 + 4;
		else if (m == 1) return (x / 5 - 1) * 3 + 5;
		return (x / 5 - 1) * 3 + 6;
	}
	if (st == 4) {
		if (m == 0) return (x / 5 - 1) * 3 + 6;
		return (x / 5 - 1) * 3 + 5;
	}
	return 0;
}

void _main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	long long res = 0;
	for (int i = 1; i <= n; i++) res += get(res % 3, a[i]);
	cout << res;
} 
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc368_c)
## 思路
可以看出，对于每一个敌人，都可以按 $5$ 滴血为一个周期算。但对于每一个敌人，都需要特判一下当前是否能开始一个新的周期，若不能则需先减掉上一个周期剩余的血量。同时还需特判这些周期完之后还剩下几滴血，需要花的时间。
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

int n, t;
int h[N];
queue<int> q;

signed main()
{
 	scanf("%lld", &n);
 	for (int i = 1; i <= n; i++)
    {
    	scanf("%lld", &h[i]);
    	q.push(i);
	}
    while (q.size())
    {
    	int u = q.front();
    	int v = h[u];
    	bool flag = false;
    	while (t % 3) // 特判当前是否能开始一个新的周期
    	{
	 	    t++;
    		if (t % 3 == 0) v -= 3;
    		else v--;
    		if (v <= 0)
    		{
    			flag = true;
    			break;
			}
		}
		if (!flag)
		{
		    int k = v / 5;
	    	t += 1ll * 3 * k;
	    	v %= 5;
            // 特判这些周期完之后还剩下几滴血，需要花的时间
	    	if (v == 1) t++;
	    	else if (v == 2) t += 2;
	    	else if (v > 2) t += 3;
		}
		q.pop();
	}
	printf("%lld\n", t);
	return 0;
}
```

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc368_c [ABC368C] Triple Attack
### 题目大意
给定 $n$ 个数 $h_1,\dots, h_n$。设初始时 $t=0$，按照以下规则变化。

- 首先，$t$ 加 $1$；
- 设 $h_i$ 满足 $h_1,\dots,h_{i-1} \le 0,h_i > 0$，则 $h_i$ 减去 $1$，若 $t$ 是 $3$ 的倍数，$t$ 再减去 $2$。
- 重复以上两点直到 $h_1,\dots,h_{n} \le 0$，求此时 $t$ 的值。

数据范围：
- $1\le h_i \le 10^9$
- $1\le N \le 2 \times 10^5$
### 思路
如果 $t$ 为 $3$ 的倍数，$h_i$ 减去 $3$，否则减去 $1$。我们可以近似地看做 $t$ 减去 $3$ 使 $h_i$ 减去 $5$。用除法消去这部分，暴力求剩下小于 $5$ 的部分。时间复杂度为 $O(n)$。
### 代码
**注意开 `long long`！**
```cpp

#include <cstdio>
using namespace std;

#define int long long

int h[200010];
int n;
int t;

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &h[i]);
        //除去被5整除的部分
		t += (int)(h[i] / 5) * 3;
		h[i] -= (int)(h[i] / 5) * 5;
        //暴力求剩下的部分
		while (h[i] > 0) {
			t++;
			if (t % 3 == 0)	h[i] -= 3;
			else	h[i]--;
		}
	}
	printf("%lld", t);
	return 0;
}

```

---

## 作者：liruixiong0101 (赞：0)

# C - Triple Attack
## 题意：
给定一个长度为 $n$ 的序列，$T$ 初始为 $0$，定义一次操作为：
- 将 $T\gets T+1$。
- 将序列中的第一个正整数减去 $c$。
	- 若 $T\equiv 0\pmod 3$，则 $c=3$。
	- 否则 $c=1$。

请问几次操作过后，序列中没有正整数。

## 思路：
可以发现每 $3$ 次操作一定会减去 $5$，所以考虑先将第一个数花 $3$ 次操作减 $5$ 的整体操作，之后暴力做小部分操作即可。

## 代码：
<https://atcoder.jp/contests/abc368/submissions/57052296>

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路

  首先考虑模拟，但是我们发现，如果 $T$ 一点一点加的话，对面血太厚了，等打完，肯定时超，所以考虑优化暴力，我们设三次操作为一个周期，那么一个周期就可以打掉五点血量，则 $T$ 一次加 $3$，我们先判断当前枚举到的敌人能抗几个周期，直接减。但是我们发现这样会出问题，因为敌人的血量有时候虽然小于一个周期，但是还没死，那么分类讨论一下，如果血量为 $1$，那么只需要再打一发，下一个周期从第二发开始；血量为 $2$，那么就要打两发，下一个周期从第三发开始；否则就必须要打完一个周期，下个周期正常开始。至于本周期从第几发开始，用标记变量标记一下，在正常周期开始前判断一下即可。

- ### 具体实现

  ```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  int n,h[200005];
  signed main()
  {
  	scanf("%lld",&n);
  	for(int i=1;i<=n;i++)
  	{
  		scanf("%lld",&h[i]);
  	}
  	int T=0,cnt,s=0;
  	for(int i=1;i<=n;i++)
  	{
  		if(s==2)
  		{
  			h[i]-=3;
  			T++;
  			s=0;
  			if(h[i]<=0) continue;
  		}
  		else if(s==1)
  		{
  			h[i]--;
  			T++;
  			s=2;
  			if(h[i]<=0) continue;
  			s=0;
  			h[i]-=3;
  			T++;
  			if(h[i]<=0) continue;
  		}
  		cnt=h[i]/5;
  		h[i]-=cnt*5;
  		s=0;
  		T+=cnt*3;
  		if(h[i]<=0) continue;
  		else if(h[i]==2) T+=2,s=2;
  		else if(h[i]==1) T+=1,s=1;
  		else T+=3,s=0;
  	}
  	printf("%lld",T);
  }
  ```

---

## 作者：xiexinzhe (赞：0)

# 思路
这道题我一开始想用暴力，结果发现时间不行。所以我们要想办法压缩时间。

首先，判断怪物血量否大于 $5$。如果符合，就让当前的怪物减去 $5$ 点血，相当于经过 $1,1,3$ 一个轮回（当然不一定是按顺序的），然后次数加 $3$。这个过程我们可以用除法完成。然后判断怪物血量是否大于 $0$，如果是，就减去下一个，同时次数加 $1$，直到怪物血量小于等于 $0$ 为止。这样，时间就是接近 $O(n)$，可以通过。 

### 代码 
```cpp
#include<bits/stdc++.h>
using namespace std;
#define Cin(x) scanf("%lld",&x)
#define Cout(x) printf("%lld\n",x)
#define int long long  //注意要开 long long 
int k[3]={1,1,3};//三次一个轮回 
int a,dq,ans;
signed main()
{
	int n;
	Cin(n);
	for(int i=1;i<=n;i++)
	{
		Cin(a);
		if(a>5)//注意要在血量大于5时进行，不然会浪费 
		{
			int bla=a/5;//组数 
			ans+=bla*3;
			a%=5;
		}
		while(a>0)//还有剩下的 
		{
			a-=k[dq%3];
			ans++;
			dq++;
		}
	}
	Cout(ans);
	return 0;
}
```

---

## 作者：xuduang (赞：0)

### 题意

有 $n$ 个数组成的数列 $A$，你有一个自增变量 $T$，当 $T$ 是 $3$ 的倍数时，最前面的一个大于 $0$ 的数减 $3$，否则减 $1$。问不能进行操作时 $T$ 是多少。

### 分析

直接算显然是接受不了的，我们考虑对于一个数在 $O(1)$ 中计算次数。

可以简单的发现，伤害可以构成一个长为 $3$ 的一个循环，且总伤害为 $5$。我们可以直接使 $T$ 加上 $\frac{A_i}{5}\times 3$。最后多出来的慢慢计算即可。

### 代码

细节比较多，给出简化过的代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e6 + 10;
int n;
int a[N];
int t;
signed main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++)
    {
        t += (a[i] / 5) * 3;//直接计算
        a[i] %= 5;
        while(a[i])//一点一点分开算
        {
            // t++;
            t++;
            if(t % 3) a[i]--;
            else a[i] -= 3;
            if(a[i] <= 0) break;
        }
        // cout << t << endl;
    }
    cout << t << endl;
    return 0;
}

```

---

## 作者：coding_goat (赞：0)

注意到 $T\mid3$ 时会有一次暴击，于是 $3$ 次攻击分一次组，每一组攻击减去 $5$ 点血，$T$ 会增加 $3 \times (\lfloor \frac {a_i}{5}\rfloor)$，$a_i$ 变成 $a_i \bmod 5$。多出的 $a_i$ 模拟即可。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define mem(a,b) memset((a),(b),sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
using namespace std;
inline int read()
{
	int xx=0;int f=1;
	char c = getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-') f = -1;
		c = getchar();
	}
	while(c>='0'&&c<='9')
	{
		xx = (xx<<1)+(xx<<3)+(c^48);
		c = getchar();
	}
	return xx*f;
}
#define maxn 200050
int n,a[maxn];
int T=0;
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++)
	{
	//	cout<<T<<' ';
		T++;
		a[i]-=(T%3==0?3:1);
		T+=3*(a[i]/5);
		a[i]%=5;
		while(a[i]>0)
		{
			T++;
			if(T%3==0) a[i]-=3;
			else a[i]--;
		
		}	
//		cout<<T<<'\n';
	}
	cout<<T;
	return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

分类讨论题。

可以发现，我们可以根据 $T\mod 3$ 的值和 $H_i$ 进行分类。这一部分很容易推导出来。推导过程：

首先，我们会以 $5$ 为一个单位对敌人进行整体伤害，此时 $T$ 增加 $3$。代码如下（代码中 $T,H$ 小写，下同）：
```cpp
if(h[i]>=5){
  t+=h[i]/5*3;
  h[i]%=5;
}
```
然后打出一个表：

$T$ 的值|伤害
-|-
1|1
2|1
3|3
4|1
5|1

现在我们分别取 $T \mod 3$ 的值为 $1,2,3$，然后逐个枚举 $H_i$ 的值，求出各种情况下 $T$ 应增加的值。

该部分代码：
```cpp
if(t%3==2)t+=(h[i]==1?1:2);
else if(t%3==1)t+=(h[i]<=2?h[i]:3);
else t+=(h[i]<=3?1:2);
```

[完整参考代码](https://atcoder.jp/contests/abc368/submissions/57072088)

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个长为 $N$ 的序列 $H$，给定 $T=0$，每次进行下面的操作直到序列 $H$ 全变为非正数：将 $T$ 增加一，如果 $T$ 为 $3$ 的倍数就将最前面为正数的 $H_i$ 减少 $3$，否则减少 $1$，问最后的 $T$ 值。

## 解题思路

因为样例 $3$ 中的 $T$ 达到了 $3\times 10^9$，所以暴力模拟肯定不行。可以发现，每次操作后减少的数应为 $1,1,3,1,1,3,\cdots$，所以我们可以把 $1,1,3$ 看成一个整体，让 $H_i$ 直接先把所有的 $1,1,3$ 跳完，剩下的再通过暴力跳就可以了。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,h,ans,k=3;

int main()
{
    n=read();

    for(int i=1; i<=n; ++i)
    {
        h=read();
        if(k<2) --h,++k,++ans; 
        if(k==2 && h>0) h-=3,++k,++ans;
        if(h<1) continue;
        ans+=h/5*3; h%=5;
        if(h && h<3) k=h,ans+=h;
        else if(h>2) k=3,ans+=3;
    }

    write(ans);
    return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

很明显，每个数的减少都是以三次减少 $5$ 为周期的。

所以先把整个周期内的次数全部加上，然后单独算剩余的。

所以，需要记录现在的操作对应的周期模 $3$ 的余数。

然后，对于剩下的部分，不断减直到小于 $0$ 即可。

时间复杂度为 $O(n)$。

---

