# Valhalla Siege

## 题目描述

Ivar the Boneless is a great leader. He is trying to capture Kattegat from Lagertha. The war has begun and wave after wave Ivar's warriors are falling in battle.

Ivar has $ n $ warriors, he places them on a straight line in front of the main gate, in a way that the $ i $ -th warrior stands right after $ (i-1) $ -th warrior. The first warrior leads the attack.

Each attacker can take up to $ a_i $ arrows before he falls to the ground, where $ a_i $ is the $ i $ -th warrior's strength.

Lagertha orders her warriors to shoot $ k_i $ arrows during the $ i $ -th minute, the arrows one by one hit the first still standing warrior. After all Ivar's warriors fall and all the currently flying arrows fly by, Thor smashes his hammer and all Ivar's warriors get their previous strengths back and stand up to fight again. In other words, if all warriors die in minute $ t $ , they will all be standing to fight at the end of minute $ t $ .

The battle will last for $ q $ minutes, after each minute you should tell Ivar what is the number of his standing warriors.

## 说明/提示

In the first example:

- after the 1-st minute, the 1-st and 2-nd warriors die.
- after the 2-nd minute all warriors die (and all arrows left over are wasted), then they will be revived thus answer is 5 — all warriors are alive.
- after the 3-rd minute, the 1-st warrior dies.
- after the 4-th minute, the 2-nd warrior takes a hit and his strength decreases by 1.
- after the 5-th minute, the 2-nd warrior dies.

## 样例 #1

### 输入

```
5 5
1 2 1 2 1
3 10 1 1 1
```

### 输出

```
3
5
4
4
3
```

## 样例 #2

### 输入

```
4 4
1 2 3 4
9 1 10 6
```

### 输出

```
1
4
4
1
```

# 题解

## 作者：superballll (赞：3)

# 题目分析

题目中 $n$ 和 $q$ 的范围非常大，而且又具有**无限复活**的技能，因此简单的打暴力肯定会超时间复杂度。而对于这一类题目的最直观的优化方法就是使用二分法，但是需要具有**单调性**，难道我们要将战士按照血量的大小进行排序嘛？显然不可能！

我们发现，判断能够击败某位战士，除了一个一个去枚举外，我们还可以通过求和的方式来判断。比如 $b[i]$ 表示第 $1 \sim i$ 名战士的血量之和，那么如果某次攻击 $k \ge b[i]$ 则说明这 $i$ 名战士全部被击败了！而且战士的血量满足 $a[i] \ge 1$ 所以求和后的数组一定是递增的，这就满足使用二分法的前提了！当然，还是要计算下最大的数值范围，如果有 $2 \times {10}^5$ 个战士，血量都是 ${10}^9$，那最终的和为 $2 \times {10}^{14}$，因此记得开 ```long long```！该部分程序如下：
```
for(int i=1;i<=n;i++){
	cin>>a;
	b[i]=b[i-1]+a;
}
```
下面我们开始二分法的设计，在设计的过程中会发现有**伤害遗留问题**，比如说前一次进攻没有让某位战士倒下，但是该战士已经不是满血了，在下一次进攻中的血量计算就会发生变化。我们尽量不要去改变求和的数组，可以定义一个变量 $kk$ 来用于记录该部分伤害（初值为 $0$）。此外，由于战士的倒下，我们每次二分时的左指针的初始值都可能发生变化，因此再定义一个变量 $x$ 表示目前第一个站着的战士的下标（初始值为 $1$）。

为了节省复杂度，我们对于两种特殊情况进行优先处理：

- 当前攻击力非常高，直接导致全秒！所有战士原地复活！状态重新初始化。
- 当前攻击力非常低，没有战士倒地。$kk$ **增加**这次的伤害。

然后，我们就可以正常的采用二分法找到当次伤害后还能站着的首位战士的位置，并且不断地对两个变量进行更新就可以了。

# 代码
```
#include<bits/stdc++.h>
using namespace std;

long long n,q,k,kk=0;
long long a,b[200005]; 
long long l,r,mid,x;

int main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		b[i]=b[i-1]+a;
	}
	kk=0,x=1;
	while(q--)
	{
		cin>>k;
		if(k>=b[n]-kk)  //全军覆没
		{
			kk=0,x=1; 
			cout<<n<<endl; 
			continue;
		} 
		if(k<b[x]-kk)  //不能破防 
		{
			kk+=k;
			cout<<n-x+1<<endl;
			continue;  
		}
		l=x,r=n;
		while(r-l>=1)
		{
			mid=(l+r)/2;
			if(k>=b[mid]-kk)  l=mid+1; //mid阵亡 
			else r=mid; // mid未阵亡 
		}
		x=l,kk+=k; 
		cout<<n-x+1<<endl;
	}
	return 0;
} 
```

---

## 作者：__Watcher (赞：2)

### 嗯？一片题解都没有？

~~水一波社区贡献~~

明显，根据数据范围：n<=200000 ,只能使用nlogn的算法

于是，神奇的二分就出现了

此题应使用攻击力前缀和在士兵血量的前缀和的数组里二分查找

二分可以手写，也可以使用STL的二分函数

加了读入优化，速度会更快一些

ok,上代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,q,x,p;
long long a[200005];
long long read()//读入优化
{
    long long X=0; char ch=0;
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return X;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		x=read();
		a[i]=a[i-1]+x;//存前缀和
	}
	for(int i=1;i<=q;i++){
		x=read();
		p+=x;
		long long* r=upper_bound(a+1,a+n+1,p);//二分，注意返回类型
		if(r-a==n+1){//全倒了
			printf("%d\n", n);
			p=0;//前缀和重置
		}
		else printf("%d\n", n-(r-a-1));
	}
}

```

---

## 作者：Fubaogege (赞：1)

数据范围大，建议用二分。
#### 二分法
看题可得：
- 二分最后一个被打倒的武士。
- 判断目前伤害是否能杀死这个武士。
- 更新左右边界。  

二分代码：
```c
while(l<=r){
	mid=l+r>>1;
	if(sum[mid]+x-sum[s-1]>a[i])r=mid-1;
	else if(sum[mid]+x-sum[s-1]==a[i])break;
	else l=mid+1;
}
```
真干净的代码。

---

## 作者：jojoxie (赞：1)

本题可以用二分法来做

分别记录士兵血量和每分钟攻击力的前缀和，找每分钟能够打倒几个士兵。

代码如下：
```
#include <stdio.h>
#include <algorithm>
using namespace std;

int n, m;
long long b[200005], f[200005];//不开longlong会WA

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1; i<=n; i++){
		scanf("%lld", &f[i]);
		f[i] = f[i] + f[i-1];//记录前缀和
	}
	f[n+1] = 1e9;
	for(int i=1; i<=m; i++){
		scanf("%lld", &b[i]);
		b[i] = b[i] + b[i-1];
		int p = upper_bound(f+1, f+n+1, b[i]) - f;//二分查找最后一个没有被打倒的人
		p--;
		if(p >= n) {
			p = 0;
			b[i] = 0;
		}//如果所有士兵都被打倒，集体复活（即前缀和归零，被打倒0个人
		printf("%d\n", (n-p));//输出剩下没有被打倒的人
	}
	return 0;
}
```

---

## 作者：huangmingyi (赞：0)

## 题目大意
无骨伊瓦尔是一位伟大的领袖。他正试图从拉格塔捕获卡特加特。战争已经开始，一波接一波的伊瓦尔战士正在战斗中倒下。   
伊瓦尔有 $n$ 个战士，他把他们放在正门前的一条直线上，第二个战士就站在第 $i-1$ 个战士的后面。第一个战士带头进攻。每个攻击者最多可以获取 $a_i$ 只箭，然后他倒在地上，$a_i$ 是第二个战士的力量。拉格塔命令她的战士射杀伊瓦尔。在第二分钟，箭一支接一支地射中了第一个仍然站立的战士。   
在所有伊瓦尔的战士倒下，所有目前正在飞行的箭都飞了过去之后，托尔打碎了他的锤子，伊瓦尔的所有战士都恢复了以前的力量，站起来再次战斗。换言之，如果所有勇士都在 $t$ 分钟内死亡，那么他们都将在 $t$ 分钟结束时站起来战斗。   
战斗将持续 $q$ 分钟，每分钟后你都应该告诉无骨伊瓦尔他的常备战士人数。
## 输入格式    
第一行包含两个整数 $n$ 和 $q$（$1 \le n$ ，$q \le 200000$）代表战士人数和战斗分钟数。
第二行包含 $n$ 个整数 $a_1$、$a_2$、 $\ldots$ 、$a_n$（$1 \leq a_i\leq 10^9$）这代表了勇士队的实力。第三行包含 $q$ 个整数 $k_1$，$k_2$，$\ldots$，$k_q$（$1\leq k_i\leq 10^{14}$)，其中第 $i$ 个代表拉格塔在第 $i$ 分钟的命令：$k_i$ 只箭会攻击战士。
## 输出格式 
输出 $q$ 线，其中第 $i$ 条是第 $i$ 分钟后站立战士的数量。     
### 该题思路
这题可以用二分，二分对象是最后一个被打倒的伊瓦尔战士位置，维护一个前缀和的数组，判断目前的伤害能不能让当前第一个伊瓦尔的战士死亡，然后更新左右边界并继续进行二分查找就可以了。这题本蒟蒻就不放代码了

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF975C)

一道二分题。

先观察数据范围，$1\le n,q\le 200,000$，显然需要 $O(n\log n)$ 的复杂度。且 $1\le k_i\le 10^{14}$，需要开 `long long`。

我们需要二分到第一个血量大于伤害值的武士的位置，前面的武士都死了。而在 `C++` 算法库中，有一个函数 `upper_bound`（底层原理是二分）正好可以帮助我们实现此功能。

另外，为了优化时间复杂度，我们选择用前缀和来存储武士们的血量与伤害。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
ll n, q, d; // d 表示伤害
ll sum[200005]; // 前缀和
signed main() {
    ios :: sync_with_stdio(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		ll x;
        cin >> x;
		sum[i] = sum[i - 1] + x;
	}
	for (int i = 1; i <= q; i++) {
        ll x;
		cin >> x;
		d += x;
		ll loc = upper_bound(sum + 1, sum + n + 1, d) - sum; // 查找第一个血量大于伤害的武士的位置  
        loc--; // 死了多少个武士 
		if (loc >= n) { // 全死了的情况
            d = 0; // 伤害清零
			cout << n << "\n"; // 全部复活，所以有 n 个武士
		}
		else cout << n - loc << "\n"; // 剩余的武士
	}
}


```


---

## 作者：Stars_visitor_tyw (赞：0)

## CF975C Valhalla Siege 题解
### 思路
由于数据范围过大，这题可以用二分查找来写。二分最后一个被打倒的武士位置，维护一个前缀和数组，判断目前的伤害能否使当前这个武士死亡，然后更新左右边界并继续进行二分查找即可。

### 代码

```cpp
#include<assert.h> 
#include<ctype.h> 
#include<errno.h> 
#include<float.h> 
#include<math.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<time.h> 
#include<wchar.h> 
#include<wctype.h>
#include<algorithm> 
#include<bitset> 
#include<cctype> 
#include<cerrno> 
#include<clocale> 
#include<cmath> 
#include<complex> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<ctime> 
#include<deque> 
#include<exception> 
#include<fstream> 
#include<functional> 
#include<limits> 
#include<list> 
#include<map> 
#include<iomanip> 
#include<ios> 
#include<iosfwd>
#include<iostream> 
#include<istream> 
#include<ostream> 
#include<queue> 
#include<set> 
#include<sstream> 
#include<stack> 
#include<stdexcept> 
#include<streambuf> 
#include<string> 
#include<utility> 
#include<vector> 
#include<cwchar> 
#include<cwctype>
#define ll long long
using namespace std;
inline ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int maxn=2e5+5;
int n,q,st;
ll u;
ll a[maxn],k[maxn],sum[maxn];
int main()
{
	n=read();
	q=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	st=1;
	for(int i=1;i<=q;i++)
	{
		k[i]=read();
		if(u>k[i])
		{
		    u-=k[i];
		}
		else if(u==k[i])
		{
			u=0;
			++st;
		}
		else 
		{
			if(k[i]>=sum[n]-sum[st-1]+u)
			{
				st=1;
				u=0;
			} 
			else
			{
				int l=st ,r=n;
				while(l<=r)
				{
					int mid=l+r>>1;
					if(sum[mid]+u-sum[st-1]>k[i])
					{
					    r=mid-1;
					}
					else if(sum[mid]+u-sum[st-1]==k[i])
					{
					    break;
					}
					else
					{
					    l=mid+1;
					}
				}
				int m=l+r>>1;
				ll w=sum[m]+u-sum[st-1]-k[i];
				u=w;
				st=m+1;
			}
		}
		if(st==n+1)
		{
			st=1;
			u=0;
		}
		cout<<n-st+1<<endl;
	}
	return 0;
}

---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF975C)

题目大意：

```
有n个武士站成一列，每个武士有自己的血量。

一个人射箭攻击他们，每箭造成一点伤害。武士按照给定的顺序承受伤害。

如果血量被消耗完了，那么武士就会死掉，而下一次伤害会落到下一个武士身上。

如果一轮攻击之后，所有的武士都死了，那么他们会立即复活。

给出若干个询问，问每轮攻击之后还剩多少武士活着。
```

看到dalao们都用 $STL$ 的 $upper$__$bound$ 来二分，像我这种蒟蒻表示虽然很厉害，但还是自己手写一下二分更有助于理解与锻炼。于是，就有了这篇二分题解。

思路：二分最后一个被打倒的武士位置，维护一个前缀和，判断目前的伤害能否使当前这个武士死亡，然后继续进行二分。

方法（以一次询问为例）：

- $1.$ 输入射出的箭数；

- $2.$ 二分查找能使哪一个武士最后死亡；

- $3.$ 判断是否可行；

- $4.$ 根据上一步结果更新答案并修改范围，同时记录修改起点；

- $5.$ 继续二分。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long//个人习惯 
using namespace std;
LL n,q,a,k,h,s[200005];//n、q、a和k如题意，h是总伤害，s是前缀和 
LL fid(LL x)//fid函数是用来寻找最后一个被打倒的武士位置的 
{
	LL l=1,r=n,mid;//l，r和mid分别是二分的左右区间和当前枚举的位置
	while(l<=r)//二分板子 
	{
		mid=l+((r-l)>>1);//防止爆掉（等价于（l+r）/2） 
		if(s[mid]<=x)l=mid+1;//如果可行，扩大上界    
		else r=mid-1;//如果不可行，缩小下界
	}
	return l;//返回结果 
}
int main()
{
	scanf("%lld%lld",&n,&q);//输入 
	for(LL i=1;i<=n;i++)scanf("%lld",&a),s[i]=s[i-1]+a;//输入的同时计算前缀和	
	for(LL i=1;i<=q;i++)//q次询问 
	{
		scanf("%lld",&k);
		h+=k;//总伤害加上这次的伤害 
		LL p=fid(h)-1;//p是找到的一个被打倒的武士位置 
		if(p>=n)p=0,h=0;//如果全杀光了，就会全部复活 
		printf("%lld\n",n-p);//输出剩余武士数 
	}
	return 0;//结束程序 
}
```

---

