# Coloring

## 题目描述

Cirno_9baka 的纸条上有 $n$ 个格子，他觉得空白的纸条看着有点无趣，于是想在纸条的格子上涂上 $m$ 种颜色。同时，他认为第 $i$ 种颜色必须要用 $a_i$ 次，且每连续 $k$ 个格子里涂的颜色必须互不相同。

Cirno_9baka 想知道有没有这样的一种涂色方案能符合他的要求。

## 说明/提示

第一个测试用例中，没有任何涂色的方案满足所有要求。

第二个测试用例中，可以将纸条涂成$(1,2,1,2,3,4,3,4,5,6,5,6)$，对于每两个连续的格子，颜色都是互不相同的。

## 样例 #1

### 输入

```
2
12 6 2
1 1 1 1 1 7
12 6 2
2 2 2 2 2 2```

### 输出

```
NO
YES```

# 题解

## 作者：xiaoqian02 (赞：13)

### 第一部分：思路
首先，这道题可以用抽屉原理（又名鸽巢原理）来解。

比如说，~~举个栗子~~，一条长 $13$ 的纸条，连续 $3$ 格中不能有相同。

接下来，假设第一格被涂上了红色。由于题设，第二格和第三格就不能涂红色。

为了涂得多一点，第四格能涂，就涂上第四格。

同理，接下来涂第七格、第十格、第十三格。

~~看到了没？这就是抽屉原理！~~

所以，知道[抽屉原理](https://baike.baidu.com/link?url=LFvNuBILsbQzgGjRazWn1MQ6HxcWaujXaowLLYut1KP4IHjrxtMyKmz5p0iF1Po5MrVFe3R5fmaKWhaxpmNny9Z6-HjnS8PahEL1A2XtpdRaetdjJtYJcmc9Gycgv_J6)，一下就能看出来，最多能涂 $\lceil \frac{n}{k} \rceil$ 格。因此，只要判出来有任意一个 $a_i$ 大于 $\lceil \frac{n}{k} \rceil$，就一定不行。

但是，but，however，如果直接这么写的话，你会得到这个结果：
```
Wrong Answer on #10
```
为什么挂了呢？这组数据可以 hack 掉。
```
1
13 5 3
5 5 1 1 1
```
问题就是：如果按刚才的想法，$\lceil \frac{13}{3} \rceil=5$，碰到两个 $5$ 不会判错。

但是，如果第一个涂了第二格，那这样就只能涂四格了：2，5，8，11。第一个涂第三个也一样。

因此，需要存下来可以达到最大值的个数。例如刚才的例子，最大值个数就只有 $1$ 个。每碰到一个最大值，就将个数减一。如果个数减到 $0$ 以下，也不行。

这样，我们就能成功地 $AC$ 这道题了。
### 第二部分：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k,p,x,nm;
bool b;
void IOS()//个人写习惯了 cin/cout，这三句是对 cin 的优化，可以让 cin 和 scanf 速度差不多
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return;
}
int main()
{
    IOS();
    cin>>T;
    while(T--)
    {
    	cin>>n>>m>>k;
    	p=n/k;
        //这里以 p+1 作为最大值
        //如果 k 是 n 的因数，虽然最大值会多 1，但下一句中 nm（统计最大值个数）就会变成 0，不会有问题
    	nm=n-p*k;
    	b=1;
    	for(int i=1;i<=m;i++)
    	{
            cin>>x;
            if(x>p+1) b=0;//大于最大值不行
            if(x==p+1) nm--;//等于最大值，个数减一
            if(nm<0) b=0;//个数小于 0 也不行
        }
        if(!b) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
    return 0;
}
```

---

## 作者：srds_cbddl (赞：9)

写篇题解来纪念一下赛时写 3 题挂 3 题。

### 思路

 - 对于 $n \bmod k = 0$ 的数据，说明纸条上的格子可以分成 $\dfrac{n}{k}$ 段。对于每个 $a_i$，如果满足 $a_i > \dfrac{n}{k}$，则说明纸条的格子不够用，直接输出 ```NO```。其实这个环节并不是很必要，主要是一些优化（即直接进行到下一个测试用例，不用再判断后面的了）。

Code（省略了缺省源）：

```cpp
if (n % k == 0) {
	rep (i, 0, m) {
		if (a[i] > (n / k)) {
			cout << "NO\n";
			return ;
		}
	}
}
```

 - 对于 $100\%$ 的数据，判断每个 $a_i$ 和 $\dfrac{n}{k}$ 的关系。对于每个 $a_i$，有 $a_i \leq \dfrac{n}{k}$，使得这个 $a$ 数组有效。所以如果有一个 $a_i$ 不满足这个关系，直接输出 ```NO```。特别的，如果 $n \bmod k$ 有剩余，可以容纳一些 $a_i - 1 = \dfrac{n}{k}$ 的项，此时需要单独统计有哪些项满足这个条件。如果满足该条件的项不足 $n \bmod k$，可以输出 ```YES```，否则输出 ```NO```。
 
Code（省略了缺省源）：

```cpp
int ans = 0;
bool flag = true;
rep (i, 0, m) {
	if (a[i] - 1 == n / k) ans ++;
	if (a[i] >= n / k) {
		flag = false;
		break;
	}
}
if (!flag) {
	cout << "NO\n";
	return ;
}
if (ans > (n % k)) {
	cout << "NO\n";
	return ;
}
cout << "YES\n";
```

以上两种算法的时间复杂度均为 $\mathcal{O}(m)$。

---

## 作者：NaOHqwq (赞：5)

## 前铺知识：抽屉原理

抽屉原理大家都不陌生，这个知识也出现在了小学课本上，小学六年级下册数学书中称其为“鸽巢原理”，但都是一样的。

例：桌上有十个苹果，要把这十个苹果放到九个抽屉里，无论怎样放，都会发现至少有一个抽屉里面放不少于两个苹果。

即当 $m\le n$ 时，把 $n+m$ 个苹果放进 $n$ 个抽屉里，至少有 $1$ 个抽屉里面放的苹果数 $\ge 2$。

由此可继续推出把 $kn+m$ 个苹果放进 $n$ 个抽屉里，至少有 $1$ 个抽屉里面放的苹果数 $\ge k+1$。

## 思路

那么如何将上面讲的抽屉原理运用到本题中呢？

再读题，从题目中的“同时，他认为第 $i$ 种颜色必须要用 $a_i$ 次，且每连续 $k$ 个格子里涂的颜色必须互不相同”这句话就可以找到抽屉原理的影子。

首先读完题后第一个想到的就是求段数（格数），即段数 $c=\frac{n}{k}$。

那么如果有 $a_i(1\le i\le m) > c$，根据上文的抽屉原理可得，至少有 $1$ 段的颜色数量 $\ge2$，显然是不符合题目要求的。

如果有 $x$ 个 $i$ 均满足 $a_i(1\le i\le m) = c$，设最后一段有 $y$ 个格，那如果 $x>y$，根据抽屉原理也至少有 $1$ 段的颜色数量 $\ge2$，也是不符合题目要求的。

除去以上两种不可行条件外，剩下的就是可行的啦。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main(){
	int n, m, t, k;
	cin >> t;
	while(t--){
		cin >> n >> m >> k;
		int c = ceil(n*1.0/k);
		int cnt = 0;
		bool flag = true;
		for(int i = 1;i <= m;i++){
			cin >> a[i];
			if(a[i] > c){
				flag = false;
			}
			if(a[i] == c){
				cnt++;
			}
		} 
		if(!flag){
			cout << "NO" << endl;
		}else if(cnt > (n-1)%k+1){
			cout << "NO" << endl;
		}else{
			cout << "YES" << endl;
		}
	}
	return 0;
} 
```

---

## 作者：Convergent_Series (赞：5)

## 知识：抽屉原理
$n+a(a\le n)$ 个苹果放进 $n$ 个抽屉，至少有 $1$ 个抽屉的苹果数 $\ge2$ 。  
$kn+a(a\le n)$ 个苹果放进 $n$ 个抽屉，至少有 $1$ 个抽屉的苹果数 $\ge k+1$ 。 

---
## 题意分析：
首先算出段数 $c= \lceil\frac{n}{k}\rceil$ 。

如果有 $a_i(1\le i \le m)>c$ ，则根据抽屉原理，至少有 $1$ 段的第 $i$ 种颜色数量 $\ge2$ ，无法构造出合格序列。

如果有$q$ 个 $i$ 满足 $a_i(1\le i \le m)=c$ ，则设最后一段（即最少的一段）有 $p$ 格，如果 $q>p$ ,则根据抽屉原理，至少有 $1$ 段包含两种及以上相同颜色，无法构造出合格序列。

否则，将第 $i$ 种颜色平均分在任意未满的 $a_i$ 段即可满足条件。

---
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,t,a[100010];
int main()
{
	int i;
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		int c=int(ceil(n*1.0/k)),fl=0,cnt=0;
		for(i=1;i<=m;i++){
			cin>>a[i];
			if(a[i]>c) fl=1;
			if(a[i]==c) cnt++;
		} 
		if(fl==1) cout<<"NO\n";
		else if(cnt>(n-1)%k+1) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
} 
```


---

## 作者：RNTBW (赞：1)

### 序

如何做 CF 结论题：

1. 先猜一个结论。

2. 再口胡一下结论。

3. 再随便写出来，被叉了就回到第一步。

## 题意

给出两个数 $n,k$ 和一个序列 $a$。

问能否在每个下标 $i$ 都选 $a_i$ 次的情况下保证每 $k$ 个下标不重复。

## 思路

先假设 $n\bmod k=0$。

考虑将 $n$ 按照 $k$ 分组，每 $k$ 个为一组。

现在就是让你填入这些 $i$。

我们可以画一个表格，有 $n\div k$ 行，$k$ 列，每组占一行。

我们要做的就是保证每个填入的 $i$，从左往右遍历 $k$ 个之内没有 $i$。

最优思路就是**每列从上到下填数，从右到左处理每列**，且每次都将 $i$ 填 $a_i$ 个，一次性填完。

为什么要从右往左呢？因为从左往右的话，当 $a_i=n\div k$ 时，$i$ 按顺序填，最后一个 $i$ 会在第一个 $i$ 的右上方位置。

而从最后一个 $i$ 开始从左往右数 $k$ 个正好到第一个 $i$。

也就是说，在 $k$ 个数内出现了两个 $i$，叉掉。读者可以画一个表格自行模拟。

那么从右往左填，就有以下情况：

- 如果对于一个 $i$，$a_i>\dfrac{n}{k}$，那么你不管把这些 $i$ 填到哪个组里面去都会造成每组之中出现重复。

而出现重复，就意味着在同一行内出现了两个一样的下标，显然违反规则。

反之，则可以填入。

那么我们加入 $n\bmod k >0$ 的情况呢？

这种情况下，表格会新添一行，这一行有 $n\bmod k$ 个空出的位置（下文简称新位置），可以竖着放入一些 $a_i=\dfrac{n}{k}+1$ 的 $i$。

然而新位置只有 $n\bmod k$ 个，也就是说 $a_i=\dfrac{n}{k}+1$ 的 $i$ 个数太多时也会多出一些下标。

这些下标只能放入行数仍旧为 $n\div k$ 的列。由于 $a_i=\dfrac{n}{k}+1$，所以它们明显放不下。

于是我们可以特判一下。

## 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int t,n,m,i,k,s,p;
bool f;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&m,&n,&p);//这里把m,n反着输入了一下
		k=m/p;s=f=0;//k不一样了哦
		for(i=1;i<=n;i++) scanf("%d",&a[i]);
		for(i=1;i<=n;i++)
		{
			if(a[i]>k)
			{
				if(a[i]>k+1)//超过太多
				{f=1;break;
				}
				s++;//又有一个下标放入了新位置
				if(s>(m%p))//新位置不够ai=m/p+1的下标放
				{f=1;break;
				}
			}
		}
		puts(f ? "NO":"YES");
	}
	return 0;
}
```


---

## 作者：Swiftie_wyc22 (赞：1)

这里用到了鸽笼原理 ~~（鸽巢原理、抽屉原理、狄利克雷原理）~~，鸽笼原理容易理解，但是活用并不容易。

将 $n$ 个元素的集合划分成 $m$ 个集合，则其中至少有一个集合中含有大于等于 $\left\lceil\dfrac{n}{m}\right\rceil$。

那么活用鸽笼原理，一定要记住这一点：分清楚谁是苹果谁是抽屉。

这题的抽屉便是 $k$，$k$ 的长度为一段，这一段内不能有重复。

那么我们可以算出段数，$v = \left\lceil\dfrac{n}{k}\right\rceil$，这个段数上取整的意义是为了包括最后一段。即每段都是 $k$ 段的段数加上模 $k$ 的余数 $r$，$r$ 就是最后一段内的数量 $0\le r<k$。

那么结合 $a_i$ 考虑。

（1）如果 $\exists a_i > v$，则无法构造出合法序列，最多只有 $c$ 个盒子，$a_i>v$ 意味着一定有一个盒子中的数量 $\ge 2$，这里面蕴含了鸽笼原理的思想；

（2）如果有 $q$ 个 $a_i=v$，且 $q > r$，也无法构造出合法序列，因为这 $q$ 个 $a_i$ 都是要往最后一段里加一个 $1$ 的，所以当 $q>r$ 时，必定有一个盒子重复。

（3）除此之外都可行。

```cpp
#include <bits/stdc++.h>

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();} while(ch>='0' && ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();return x*f;}

using namespace std;

int main()
{
	int T = read();
	int n,m,k;
	while (T--) {
		n = read(), m = read(), k = read();
		int v = int(ceil(n*1.0/k)), a, f = 0, c = 0;
        // v 的取整特别严格，只有这么写才不会挂分
		for (int i = 1; i <= m; i++) {
			a = read();
			if (a > v) f = 1;
			if (a == v) c++;
		}
		if (f == 1) printf("NO\n");
		else if (c > (n  - 1) % k + 1) printf("NO\n");
		else printf("YES\n");
	}
    return 0;
}
```

关注程序的第21行，`(n  - 1) % k + 1` 这个处理很妙。如果我们写 `n%k` 则是值域在 $[0,k-1]$，而前者是 $[1,k]$。我们可以写成 `n%k==0?n:n%k`。那么这里为什么要这么写呢？因为当 $k|n$ 时，$n$ 被恰好分为 $k$ 段，那么这时就没有多余的 $r$ 也就无需这样操作。

---

## 作者：yanxu_cn (赞：1)

### 题意简化
对于一个序列，其中任意长度为 $k$ 的子段中的元素均不相同。给出每个元素的数量，求出是否有一个序列满足上面的要求。
### 分析
经过分析，其实我们可以直接将这个序列分成 $\lceil n \div k\rceil$ 个段。每一个段（最后一个除外）都有 $k$ 个元素。然后往这些段中填元素。

可以证明的是：
+ 对于一个值，因为每个段至多有一个这个元素，所以最多也只能填入 $\lceil n \div k\rceil$ 个一样的元素，如果元素的数量多于这个值，那就不可能满足题意。
+ 如果个数恰好为 $\lceil n \div k\rceil$ 的元素的数量大于最后一个段的元素数量，那也一定不行。
+ 对于个数小于 $\lceil n \div k\rceil$ 的元素，一定可以有方法使其填入剩余的空位中，并且满足题意。

由此，我们只需要先把 $\lceil n \div k\rceil$ 计算出来，然后再与题目中的各个元素的数量比对一下，并求出相等的个数，最后判断一下即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t,n,m,k,tmp,v,cnt;
    bool f=false;
    cin>>t;
    while(t--)
    {
        cnt=0;
        f=false;
        cin>>n>>m>>k;
        tmp=ceil(n*1.0/k);
        while(m--)
        {
            cin>>v;
            if(v>tmp)
            {
                f=true;
            }
            if(v==tmp)
            {
                cnt++;
            }
        }
        if(cnt>(n-1)%k+1||f)
        {
            cout<<"NO\n";
        }
        else
        {
            cout<<"YES\n";
        }
    }
    return 0;
}
```

---

## 作者：Zimo_666 (赞：0)

## B. Coloring

看起来很困难的 B。事实是，比 D 难。

### Statement

有 $n$ 个位置，$m$ 种颜色，每种颜色要求涂 $a_i$ 次，且保证 $n=\sum\limits_{i=1}^{m} a_i$。要求是连续 $k$ 个位置颜色必须互不相同。

可以做到输出 `YES`，反之 `NO`。

### Solution

看起来就不太会了。

首先我们可以钦定一些问题。比如 $len=\lceil\frac{n}{k}\rceil$，那么如果有任意一个 $a_i>len$ 时，我们都存在一个区间，使得这个长度为 $k$ 的区间内有颜色相同的了。

那么我们还少考虑了一些在不能整除下的问题，就是当我们填完某一个颜色之后，可能由于下取整和限制的原因，最后一个区间就填不下了这个颜色了，所以我们计算所有 $a_i=len$ 的数量，如果这个值比最后一段的长度要大，那么就填不下了。

[Code](https://codeforces.com/contest/1774/submission/229359357)

---

## 作者：ImNot6Dora (赞：0)

~~我非常喜欢吸氧~~。
# 正文
这道题是一个不用吸氧的关于鸽笼原理的题目，所谓[鸽笼原理](https://baike.baidu.com/link?url=JfoHVZ9maJmHhZUhki37tVKbA9LNBx_p_JE-ks5ZgzUAN0WMoXz9IygBLBiR8zcYC1TmHmYff-IcEsSDD_3HfXYrti6Rcc2oMLUGGXy_0MFWhNg7u1xMwfeNnS_si1X7)，又称抽屉原理，就是说**把 $n+1$ 只**鸽子**放进 $n$ 个**铁笼中，则至少有一个铁笼中的鸽子数量 **大于 2**。

根据鸽笼原理，我们可以找出在本题里的“铁笼数”$\lceil\dfrac{n}{k}\rceil$，而每个笼子的容积我们也能确定，除最后一个笼子的容积可能为 $n\bmod k$ 之外，剩下的都是 $k$。这道题我们就可以转化成，**在 $\lceil\dfrac{n}{k}\rceil$ 个铁笼里放上不超过其容积的一些不同种类鸽子，且每个笼子里不能有相同种类的鸽子，是否有这样的方案**。

之后我们就来判断能否装下所有鸽子了。容易发现，如果 $a_i\gt\lceil\dfrac{n}{k}\rceil$，说明必须有一些笼子盛放两个同样的鸽子，则无法满足“每个笼子里不能有相同种类的鸽子”的条件，说明无法满足条件。

继续进行分析，发现有可能会有 $a_i=\lceil\dfrac{n}{k}\rceil$ 的情况，那么每个笼子里都会有一只第 $i$ 种鸽子。根据之前的分析，我们可以发现前面笼子的容积总是会大于等于最后一个笼子的容积，那我们只要看最后一个笼子的容积能否装下这些满足条件的 $a_i$ 数量好了。最后一个笼子的容积为 $n\bmod k$，如果满足条件的 $a_i$ 数量超过了最后一个笼子的容积，则最后一个笼子无法装下这么多的鸽子，说明无法满足条件。

当然，在上面的分析中，我们说的是最后一个笼子的容积**可能**为 $n\bmod k$，而如果 $n\bmod k=0$，说明最后一个笼子的容积是 $0$，但这样的话相当于没有这个笼子，所以顺延下来最后一个笼子的容积应该是 $k$，我们可以用一个三目运算符来表示： `n%k==0?k:n%k`。

否则，说明一定能装下这些鸽子。
# AC C++ CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main(){
	int t,n,m,k,tot=0;
	bool f=0;
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i=1;i<=m;i++){
			cin>>a[i];
			if(a[i]>ceil(n*1.0/k))f=1;
			else if(a[i]==ceil(n*1.0/k))tot++;
		}
		if(f||tot>(n%k==0?k:n%k))cout<<"NO\n";
		else cout<<"YES\n";
		tot=f=0;
	}
	return 0;
}
```
完结撒花！

By ImNot6Dora

---

## 作者：kimidonatsu (赞：0)

# CF1774B Coloring 题解

## 题意简述

* 有一个长度为 $n$ 的序列。
* 求一个长度为 $k$ 的子序列中的各个元素颜色均不相同。
* 现在给出每种元素的数量，要我们求出是否有一个这样的序列满足上述要求。

## 思路分析

抓到题目后不难联想到 [**抽屉原理**](https://oi-wiki.org/math/combinatorics/drawer-principle/)。简单来说就是：将 $n + 1$ 个物体，划分为 $n$ 组，那么有至少一组有两个（或以上）的物体。

由此，我们可以先将序列分割成 $\lceil \dfrac{n}{k} \rceil$ 份，除最后一段外，每个段都有 $k$ 个元素（最后一段的长度 $r$ 为 $0 \leq r \lt k$）。然后我们按照 $a_i$ 开始尝试构造序列，易得：

* 求出段数后，如果颜色数量大于段数，方案不可行
* 考虑最后一段 $r$，已知 $r$ 的长度为 $0 \leq r \lt k$，不均分，即如果元素数量 $a_i = \lceil \dfrac{n}{k} \rceil$ 大于 $r$，方案亦不可行

除此之外，求出 $\lceil \dfrac{n}{k} \rceil$ 之后我们就可以构造出满足题意的序列。

---

但是这里需要注意一下格式抓换的细节。我们这么定义段数 $l$：

```cpp
int l = (int) ceil(n * 1.0 / k);
```

由于 `ceil` 函数 要求类型为 `double`，所以我们先转类型，之后赋值回 $l$ 时再进行一次类型转换转回 `int`。这是一个得分点，比较坑。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 100050;

int t, n, m, k;
int a[N];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &n, &m, &k);
        int l = (int) ceil(n * 1.0 / k), cnt = 0;
        bool flag = false;
        for (int i = 1; i <= m; i++) {
            scanf("%d", &a[i]);
            if (a[i] > l) flag = true;
            if (a[i] == l) cnt++;
        }
        if (flag == true) printf("NO\n");
        else if (cnt > (n - 1) % k + 1) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}

```

## 参考资料

* 鸽巢原理：[OI Wiki](https://oi-wiki.org/math/combinatorics/drawer-principle/)
* `ceil` 函数：[cppreference.com](https://zh.cppreference.com/w/cpp/numeric/math/ceil)


---

