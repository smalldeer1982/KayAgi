# Slay the Dragon

## 题目描述

Recently, Petya learned about a new game "Slay the Dragon". As the name suggests, the player will have to fight with dragons. To defeat a dragon, you have to kill it and defend your castle. To do this, the player has a squad of $ n $ heroes, the strength of the $ i $ -th hero is equal to $ a_i $ .

According to the rules of the game, exactly one hero should go kill the dragon, all the others will defend the castle. If the dragon's defense is equal to $ x $ , then you have to send a hero with a strength of at least $ x $ to kill it. If the dragon's attack power is $ y $ , then the total strength of the heroes defending the castle should be at least $ y $ .

The player can increase the strength of any hero by $ 1 $ for one gold coin. This operation can be done any number of times.

There are $ m $ dragons in the game, the $ i $ -th of them has defense equal to $ x_i $ and attack power equal to $ y_i $ . Petya was wondering what is the minimum number of coins he needs to spend to defeat the $ i $ -th dragon.

Note that the task is solved independently for each dragon (improvements are not saved).

## 说明/提示

To defeat the first dragon, you can increase the strength of the third hero by $ 1 $ , then the strength of the heroes will be equal to $ [3, 6, 3, 3] $ . To kill the dragon, you can choose the first hero.

To defeat the second dragon, you can increase the forces of the second and third heroes by $ 1 $ , then the strength of the heroes will be equal to $ [3, 7, 3, 3] $ . To kill the dragon, you can choose a second hero.

To defeat the third dragon, you can increase the strength of all the heroes by $ 1 $ , then the strength of the heroes will be equal to $ [4, 7, 3, 4] $ . To kill the dragon, you can choose a fourth hero.

To defeat the fourth dragon, you don't need to improve the heroes and choose a third hero to kill the dragon.

To defeat the fifth dragon, you can increase the strength of the second hero by $ 2 $ , then the strength of the heroes will be equal to $ [3, 8, 2, 3] $ . To kill the dragon, you can choose a second hero.

## 样例 #1

### 输入

```
4
3 6 2 3
5
3 12
7 9
4 14
1 10
8 7```

### 输出

```
1
2
4
0
2```

# 题解

## 作者：Wuyanru (赞：3)

现有 $ n $ 个英雄与一个龙，每个英雄有一个能力值，龙有一个攻击值 $ x $ 与一个防御值 $ y $。现在你要派一个人去打龙，但是这个人的能力值必须大于等于龙的防御值；剩下的人守护城堡，他们的力量值和大于等于龙的攻击。一个金币可以提升一个人一点能力值，问最少需要多少金币。

我们来考虑会派谁去攻击龙。

1.  我们选择一个能力值小于 $ y $ 的人，提高他的能力值然后去打龙。这时选择的一定是小于 $ y $ 的且最大的一个人，否则将会造成更多的金币话费。

2.  我们选择一个能力值大于等于 $ y $ 的人。这时选择的一定是大于等于 $ y $ 的且最小的一个人，因为派一个能力值更大的人显然是一种浪费的行为。

不难发现，派出去的人能力值要么大于等于 $ y $,要么小于 $ y $,所以我们对于两种情况分别求出答案，再输出最小的一种即可。

具体实现就是先将所有英雄能力值进行排序，然后对于每一组询问，使用二分查出大于等于 $ y $ 的第一个位置即可。

注：我代码中的 `lower_bound()` 函数对应的就是二分的部分。

AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a[200001];
long long x,y;
int n,m;
int main()
{
	int t;
	t=1;
	while(t--)
	{
		long long sum=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld",a+i),sum+=a[i];
		sort(a+1,a+n+1);
		scanf("%d",&m);
		while(m--)
		{
			scanf("%lld%lld",&x,&y);
			long long ans=0x3f3f3f3f3f3f3f3fll;
			int num=lower_bound(a+1,a+n+1,x)-a;
			if(num!=n+1)
				ans=max(y-(sum-a[num]),0ll);
			num--;
			if(num)
				ans=min(ans,x-a[num]+max(y-(sum-a[num]),0ll));
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```
感谢观看！

---

## 作者：きりと (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF1574C)**

### 题目大意

给定 $n$ 名英雄的战斗力 $a[i]$，现有 $m$ 条纳什男爵，每条纳什男爵有防御力 $b[i]$ 和攻击力 $c[i]$。为了击杀每条纳什男爵，需要有一名战斗力 $\ge b[i]$ 的英雄，且剩下的英雄战斗力之和要 $\ge c[i]$，现可以进行若干次操作，每次操作要花费 $1$ 点蓝色精粹，使一名英雄战斗力 $+1$，求需要花费最小的精粹数量。

### 解题思路

对于所有英雄的战斗力加起来还不到 $b[i]+c[i]$ 的情况，直接输出差值就行。

对于其他情况，考虑贪心，我们显然要派一个战斗力比较接近 $b[i]$ 的英雄去和男爵solo。

那么就可以使用二分找一下第一个战斗力 $\ge b[i]$ 的英雄，然后分别计算派出这个英雄和派出第一个比他战斗力小的英雄，最终花费精粹的最小值即可。

具体实现可以康代码。

~~f数组很阿巴，感觉偷懒不写单调栈反而弄巧成拙了。~~

赛时没关同步，读入太拉了死了两发。

![](https://pic.imgdb.cn/item/614b3c5b2ab3f51d91011055.jpg)

### Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define forr(i,l,r) for(register int i=l;i<=r;i++)
#define ffor(i,r,l) for(register int i=r;i>=l;i--)
using namespace std;
const int N=2e5+10;
ll a[N],f[N];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    ll s=0;
    cin>>n;
    forr(i,1,n)
    {
        cin>>a[i];
        s+=a[i];
    }
    sort(a+1,a+n+1);
    a[0]=-1;
    forr(i,1,n)
    {
        if(a[i]!=a[i-1])
        {
            ffor(j,i-1,1)
            {
                if(a[j]<a[i])
                {
                    f[i]=j;     //f数组用来记录第一个比a[i]小的数字的下标。
                    break;
                }
            }
        }
        else
        {
            f[i]=f[i-1];
        }
    }
    int m;
    cin>>m;
    ll x,y;
    int l,r,mid;
    while(m--)
    {
        cin>>x>>y;
        l=1,r=n;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(a[mid]<x)
            {
                l=mid+1;
            }
            else
            {
                r=mid-1;
            }
        }
        if(a[l]==0)
        {
            cout<<x-a[n]+max(y-s+a[n],0LL)<<endl;       
            continue;
        }
        if(a[f[l]]==-1)
        {
            cout<<max(y-s+a[1],0LL)<<endl;             
            continue;
        }
        cout<<min(max(x-a[l],0LL)+max(y-s+a[l],0LL),max(x-a[f[l]],0LL)+max(y-s+a[f[l]],0LL))<<endl;
    }
}

```



---

## 作者：wheneveright (赞：0)

## 题意

你有 $n$ 个勇者，每个勇者有一个实力值 $a_i$，现在你面对着 $m$ 条龙，每条龙有两个值：$x, y$，表示防御值和攻击值，你需要找出一个勇者实力大于等于 $x$，且剩下的勇者实力值之和大于等于 $y$。你当然会出现找不到勇者的情况，因此，你可以用一个金币给任意一个勇者提升 $1$ 的实力值，问对于每条龙最少要多少金币（询问之间相互独立）？

## 解析

下面假定勇者实力值已经排序。

首先想到用二分找到第一个大于龙的防御值的情况，然后在选他或者实力值比他小的最大的勇者升级后去两种之间挑一种。

接下去就只要考虑几个小细节：

- 当第一个勇者就能干掉龙的时候不能去找他前面的勇者
- 当最后一个勇者干不掉龙的时候拿出来单独讨论
- 其他就是一些和 $0$ 取最大值的情况，因为会出现实力和吊打龙
- 读入太多要用快读
- 要开 `long long`
- 其他的东西注释里面有

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;

struct reader {
	template <typename Type>
	reader & operator >> (Type & ret) {
		int f = 1; ret = 0; char ch = getchar ();
		for (;!isdigit (ch); ch = getchar ()) if (ch == '-') f = -f;
		for (; isdigit (ch); ch = getchar ()) ret = (ret * 10) + ch - '0';
		ret *= f; return * this;
	}
} fin; // 读入优化 

int n, m;
long long a[maxn];
long long x, y, s;
int L, R, mid, res;
long long ans;

int main () {
	fin >> n;
	for (int i = 1; i <= n; i++)
		fin >> a[i], s += a[i]; // s 是总和
	sort (a + 1, a + 1 + n); 为二分准备
	fin >> m;
	while (m--) {
		fin >> x >> y;
		if (x > a[n]) {
			printf ("%lld\n", x - a[n] + max (0ll, y - s + a[n]));
			continue ; // 出现没有勇者能够胜任的情况，就是最强大的人升级，剩下的随便升级能抗住
		}
		L = 1; R = n;
		while (L <= R)
			a[mid = (L + R) >> 1] >= x ? R = mid - 1, res = mid : L = mid + 1;
		ans = max (y - s + a[res], 0ll); // 二分找到第一个能打败龙的
		if (res != 1) ans = min (ans, x - a[res - 1] + max (y - s + a[res - 1], 0ll));
		// 如果 res = 1 就会出先让编号为 0 的勇者，但是并没有这个人
		printf ("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Xhesika_Frost (赞：0)

首先可以考虑到把所有英雄按照  $a$ 排序

然后考虑对于一个龙，我们派出谁来打他呢？

派出浪费尽可能小的，也就是第一个 $a_i>=x$ 的英雄

这样的话思路就清晰了

每一个进行二分查找第一个大于等于 $x$ 的 $a_i$ 然后进行判断

每一次有两种选择，派这个英雄去，然后剩下的英雄抗龙

或者让第一个比这个英雄差的英雄用金币升级去抗龙

去一下最小值，分类讨论就可以了

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define int long long 
using namespace std;
int a[200005];
int n;
int m;
int x,y;
int sum;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		sum+=a[i];
	}
	sort(a+1,a+n+1);
	scanf("%lld",&m);
	for(int i=1;i<=m;++i){
		scanf("%lld%lld",&x,&y);
		int p=lower_bound(a+1,a+n+1,x)-a;
		if(a[p]>=x){
				if(p!=1){
				int co=min(x-a[p-1]+max((long long)0,y-sum+a[p-1]),max((long long)0,y-sum+a[p]));
				printf("%lld\n",co);
				}
				else{
					printf("%lld\n",max((long long)0,y-sum+a[p]));
				}
		}
		else{
			p--;
			if(sum-a[p]>=y){
				printf("%lld\n",x-a[p]);
			}else{
				printf("%lld\n",x-a[p]+(y-sum+a[p]));
			}
		}
	}
	return 0;
}
```

---

## 作者：引领天下 (赞：0)

简单的一个贪心题。

考虑我们派哪个英雄去打龙。事实上，我们证明，若 $a_k$ 为 $a_i$ 中第一个攻击力 $\ge x$ 的 $a_i$，则我们只可能派出 $a_k$ 或者 $a_{k-1}$ 去打龙。若不存在 $a_k$，显然派 $\max{a_i}$ 是最优的，证明与下方的第二类同理。

以下给出简略的证明：

设我们最终答案派出了 $a_j$。

- 若 $a_j>a_k$：显然派 $a_k$ 不会更劣，因为派出 $a_j$ 对攻击方面的答案没有影响（都是 $0$），却会导致防御下降从而产生额外的费用。
- 若 $a_j<a_{k-1}$：设除了 $a_j,a_{k-1}$ 之外的所有 $a_i$ 的和为 $sum$。若 $sum+a_{k-1}\le y$，则派出 $a_j$ 的费用为 $x-a_j+y-sum-a_{k-1}$，派出 $a_{k-1}$ 的费用为 $x-a_{k-1}+y-sum-a_j$，相同；而若 $sum+a_{k-1}>y$，则有 $a_{k-1}>y-sum$，此时派出 $a_j$ 的费用为 $x-a_{k-1}+a_{k-1}-a_j$，派出 $a_{k-1}$ 的费用为 $x-a_{k-1}+y-sum-a_j$。比较两者费用，由于 $a_{k-1}>y-sum$，所以事实上派出 $a_j$ 的费用更高。

贪心策略得证。至于 $a_{k-1}$ 和 $a_k$ 谁更优，是无法直接确定的：可能存在这样的情况，即 $a_{k-1}$ 非常接近 $x$，而 $a_k\gg x$。这种情况下，派出 $a_k$ 就会导致防御过低，事实上攻击溢出太多，是非常亏的做法。

对 code 来说，只需要先对 $a_i$ 排序，然后二分查找即可。唯一的坑点大约是若排序后的 $a_1$ 就已经 $\ge x$ 了，此时不存在上方讨论的第二类情况。（我就是这么在2min想出做法后wa3调半小时的）

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200005],m,x,y,sum;
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;sum+=a[i],i++)cin>>a[i];
    sort(a+1,a+n+1);
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        int k=lower_bound(a+1,a+n+1,x)-a;//二分查找，确定k
        if(a[k]<x)cout<<(x-a[n]+max(y-(sum-a[n]),0ll))<<endl;//如果不存在 a[k]>=x，则派 a[n]
        else cout<<min((k>1?x-a[k-1]+max(y-(sum-a[k-1]),0ll):1ll<<60),max(y-(sum-a[k]),0ll))<<endl;//否则两种情况取较小值
    }
    return 0;
}
```

---

## 作者：Jerrywang09 (赞：0)

# 题意简述

给定一个数组，有若干次询问。对于每次询问，输入 $x$ 和 $y$，要求在原数组中对若干个数进行 $+1$，每次操作花费一枚金币。找到一个元素 $a$，使得 $a>=x$ 且 除去 $a$ 外数组的总和大于等于 $y$。求最少金币数。

# 先说几句

一道有点难的贪心、二分、排序。建议难度 普及。

# 解题思路

输入数组后，进行排序。
对于每一个 $x$ 和 $y$，在数组中二分查找 lower_bound $x$。

记 $k$ 为 
```lower_bound(a, a+n, x)-a```。

## Part 1: $k=0$

令 $s$ 为除去 
 ```a[k]``` 
的总和。如果 $s<y$，则所需金币数为 $y-s$。否则不要花费金币。

## Part 2: $k<n$

需要分情况考虑。

### 情况1

假设取英雄 $k$ 打败龙。按照 Part 1 的方法计算金币数。

### 情况2

假设取英雄 $k-1$ 打败龙。按照 Part 1 的方法计算金币数。

只要输出上面两种情况的较小值就可以了。

## Part 3: 没有可选的英雄打败龙（$k=n$）

按照贪心思想，我们要选攻击力最大的英雄来打龙。

先计算出 $s$。如果 $s<y$，则保护城堡的金币数是 $y-s$，打败龙的金币数是 $x-a[maxi]$，总共金币数就是 
```y-s+x-a[maxi]```。

否则，只需要花费英雄的金币，就是 
```x-a[maxi]```。

## Part 4: 优化

必须按照下面的内容优化，否则会超时！

### 1.使用 inline 内联函数。

使用 inline 内联函数可以提高函数调用效率。

### 2.预处理 $maxi$ 和数组总和。

预处理过后，就不必反复循环计算了。

### 3.输入输出优化。

就是这三条语句：

```cpp
ios_base::sync_with_stdio(false);
cin.tie(0); cout.tie(0);
```


# 奉上代码

千万不要抄，小心棕名！

```cpp
// 1574C Slay the Dragon
#include <bits/stdc++.h>
#define var long long
using namespace std;

var totalsum;
inline var getsumWithout(var a[], var n, var k)
{
	return totalsum-a[k];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	var n; cin>>n;
	var a[n];
	var maxi=0;
	for(var i=0; i<n; i++)
		cin>>a[i], totalsum+=a[i];
	sort(a, a+n);
	maxi=n-1;
		
	var T; cin>>T;
	while(T--)
	{
		var x, y; cin>>x>>y;
		var k=lower_bound(a, a+n, x)—a;
		if(k==0) 
		{
			var s=getsumWithout(a, n, k);
			if(s<y)
				cout<<y-s<<endl;
			else
				cout<<0<<endl;
			continue;
		}
		if(k!=n)
		{
			var res1;
			{
				var s=getsumWithout(a, n, k);
				if(s<y)
					res1=y-s;
				else
					res1=0;
			}
			var res2=x-a[k-1];
			{
				var s=getsumWithout(a, n, k-1);
				if(s<y)
					res2+=y-s;
			}
			cout<<min(res1, res2)<<endl;
		}
		else
		{
			var s=getsumWithout(a, n, maxi);
			if(s<y)
				cout<<y-s+x-a[maxi]<<endl;
			else
				cout<<x-a[maxi]<<endl;
		}
	}

    return 0;
}

```


---

