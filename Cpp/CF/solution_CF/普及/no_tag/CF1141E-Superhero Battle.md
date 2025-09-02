# Superhero Battle

## 题目描述

A superhero fights with a monster. The battle consists of rounds, each of which lasts exactly $ n $ minutes. After a round ends, the next round starts immediately. This is repeated over and over again.

Each round has the same scenario. It is described by a sequence of $ n $ numbers: $ d_1, d_2, \dots, d_n $ ( $ -10^6 \le d_i \le 10^6 $ ). The $ i $ -th element means that monster's hp (hit points) changes by the value $ d_i $ during the $ i $ -th minute of each round. Formally, if before the $ i $ -th minute of a round the monster's hp is $ h $ , then after the $ i $ -th minute it changes to $ h := h + d_i $ .

The monster's initial hp is $ H $ . It means that before the battle the monster has $ H $ hit points. Print the first minute after which the monster dies. The monster dies if its hp is less than or equal to $ 0 $ . Print -1 if the battle continues infinitely.

## 样例 #1

### 输入

```
1000 6
-100 -200 -300 125 77 -4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
1000000000000 5
-1 0 0 0 0
```

### 输出

```
4999999999996
```

## 样例 #3

### 输入

```
10 4
-3 -6 5 4
```

### 输出

```
-1
```

# 题解

## 作者：sea_bird (赞：3)

# 题目分析

[题目传送门](https://www.luogu.com.cn/problem/CF1141E)。

这道题并不是那么难。~~虽然我还是提交了很多次~~ 。

来让我们看一下题目，超级英雄与怪物搏斗。这场战斗由几轮组成。我们没必要一轮一轮的看，因为每一轮的数据是相同的，所以先算出来一轮的结果再拿去判断是否为负数，否的话果断输出 -1。

~~让后完美结束了~~。

**但是**，这样根本过不了样例 5。

为什么呢？这忽略了一个问题，要是先是负数再是正数呢？在负数期间便可以消灭怪物了怎么办？所以需要在输入时加一个判断，当足够消灭怪物时直接输出当时的 $i$，接着直接结束程序，那么正常的情况下该怎么办？首先求出 $sum$ 的绝对值，方便后续运算，接着看排除最后一轮会怎么样，除尽与除不尽每轮伤害的情况下要分开处理，为什么要加上 1？因为有些时候除不尽，会多出一些伤害，但还是需要那一轮战斗。最后这个循环是循环最后一轮战斗，看到底战斗到第几分钟便能胜利，接着退出循环，得到最终答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[1000005]; 
int main(){
	long long t,n,sum=0,maxn=0,l;//十年oi一场空 
	long long ans=0;//十年oi一场空 
	cin>>t>>n;//n也是分钟数 
	for(int i=1;i<=n;i++){
		cin>>x[i];
		sum+=x[i];
		if(maxn>sum){//一轮中最大伤害 
			maxn=sum;
		}
		if(t+sum<=0){//判断在第一轮中伤害是否足够结束
			cout<<i<<endl;
			return 0;
		}
	}
	if(sum>=0){//当伤害不是复数时
		cout<<-1<<endl;
		return 0;
	}
	sum=abs(sum);//求绝对值
	l=(t+maxn)%sum;//排除最后一轮的情况 
	if(l>0){//就像样例#1
		ans=n*((t+maxn)/sum+1);//计算最后一轮之前的分钟数 
		t=t-((t+maxn)/sum+1)*sum;//更新t的值为不算最后一轮的情况 
	}
	else{//就像样例#2 
		ans=n*((t+maxn)/sum);
		
		t=t-((t+maxn)/sum)*sum;
	}
	for(int i=1;i<=n;i++){//再循环最后一轮的情况 
		t+=x[i];
		if(t<=0){
			ans+=i;
			break;//跳出循环
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
最后结果就是 AC 了。

---

## 作者：Y_QWQ_Y (赞：2)

线性算法万岁！

不会用二分的蒟蒻。。。

算法流程如下：

1. 输入并统计前缀和以及前缀和的最小值，即最大伤害。

2. 判断能否在 $1$ 到 $n-1$ 分钟之间完成任务，至于为什么会在第 3 步中给出。

3. 判断如果一个回合下来，不会增加伤害，甚至会增加血量，那么就直接输出无解。但是如果可以在第 $n$ 分钟之前击杀怪物，并在第 $n$ 分钟时可以把怪物的血量恢复到 $0$ 以上，就错过了最佳答案。

	给出一条样例说明：
	```
	9 4
	-4 -5 6 3
	```
	如果没有这一层判定，就会输出无解，但是通过手算可以发现其实在第 $2$ 分钟就可以击杀怪物了。

4. 计算扣完怪物的血量需要的轮数，但是要减去轮数 $\times$ 一轮的伤害。

- 给出了算法流程，代码实现就比较容易了，唯一的难点就是第 4 步，下面是第 4 步的代码。
```cpp
q = s / c;
if (s % c != 0)++ q;
s -= (m + q * c);
for (int i = 1; i <= n; ++ i)if (s + w[i] <= 0){cout << q * n + i;return 0;}
```

---

## 作者：da32s1da (赞：2)

先找到每一轮扣多少$hp$，如果大于0，则不可能击败。

注意一个坑点，可能一轮**先扣再加**，所以要判一下扣的最多时候是否死亡。

```cpp
#include<cstdio>
typedef long long LL;
const int N=2e5+50;
LL H,Ans,x,y;
int n,a[N];
int main(){
    scanf("%I64d%d",&H,&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        x+=a[i];
        if(y>x)y=x;//扣血最多的时候
        if(H+x<=0){//一轮没结束就死亡
            printf("%d\n",i);
            return 0;
        }
    }
    if(x>=0){puts("-1");return 0;}//判掉
    x=-x;
    Ans=1ll*n*((H+y)/x+((H+y)%x>0));//把整的几轮加上
    H=H-1ll*((H+y)/x+((H+y)%x>0))*x;//剩下的血
    for(int i=1;i<=n;i++){
        H+=a[i];
        if(H<=0){printf("%I64d\n",Ans+i);return 0;}
    }
}
```

---

## 作者：Ybll_ (赞：1)

# 题意：
~~**应该都看得懂吧？**~~
# 思路：
[前置芝士——前缀和](https://blog.csdn.net/m0_69323023/article/details/135789840)，

这题**暴力**肯定得 `TLE`，所以用**前缀和**进行优化，有点坑的是 `ta` 有可能**第一轮**就嘎了，还有就是虽然每回合造成的伤害可能让 `ta` **活很久**，但是某个回合的的一下**重击**可能给他**直接干死**。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005],sum,ans,mx=0x3f3f3f3f,flag;
signed main()
{
	int n,m;
	cin>>m>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
		mx=min(mx,sum);
		if(m+sum<=0)//这个彬彬逊到第一回合都撑不过哎
		{
			cout<<i;
			return 0;
		}
	}
	if(sum>-1)//死不了
	{
		cout<<-1;
		return 0;
	}
	sum=-sum;
	if((m+mx)%sum>0)flag=1;//有余数要+1，不然会wa掉
	ans=n*((m+mx)/sum+flag)+1;//答案
	m-=sum*((m+mx)/sum+flag);//还剩多少血
	for(int i=1;i<=n;i++,ans++)//最后再来一轮
	{
		m+=a[i];
		if(m<=0)//死了
		{
			cout<<ans;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

设 $s=\sum d_i$。

先模拟一轮，如果死了就直接输出，否则记录 $x$ 为 $d_i$ 的前缀和最小值。此时若 $s\ge 0$，那么以后永远也死不了，输出 $-1$。

二分出恰好死亡的轮数为 $t$，应满足 $H+(t-1)s+x\le 0$。然后进入第 $t$ 轮模拟一遍找到死亡位置即可。

---

## 作者：zwz6666 (赞：1)

# CF1141E Superhero Battle 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1141E)
## 题目大意
给定血量 $h$ 和 $n$ 个整数 $d_1,d_2,\dots,d_n$,
每轮 $n$ 次操作,第 $i$ 次操作使 $h=h+d_i$。
问在进行第几次操作后，$h \le 0$ 。 
如果永远无法死亡，输出 $-1$。


## 解题思路
- 首先枚举第一轮的 $n$ 次操作，记录最大扣血 $x$ 与  $n$ 次操作的总扣血 $sum$ 。同时特判第一轮就死亡（$h \le 0$）的情况，此时直接输出并结束程序。

- 若第一轮没有死亡，且 $sum \ge 0$，一定不会死亡。

- 若第一轮没有死亡，且 $sum < 0$，一定会死亡。此时先找到最小的轮数，使 $h \le x$。之后再模拟一轮即可。

详见代码。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 2e5+5;
ll d[maxn],h,n;
ll x=0;
int main() {
	cin>>h>>n;
	ll sum=0;
	for(int i=1;i<=n;i++){
		cin>>d[i];
		sum-=d[i];
		if(h-sum<=0){
			cout<<i;
			return 0;
		}
		x=max(x,sum);//最多扣x 
	if(ans<=0){
		cout<<-1;
		return 0;
	}
	ll ans=0;
	ans=(h-x)/sum;
	h-=ans*sum;
	if(h>x)ans++,h-=sum;//最少循环ans轮
	ans*=n;//ans轮ans*n次攻击
	//此时再来一轮一定可以死亡，但不一定是在总受伤最大时，可能更早
	for(int i=1;i<=n;i++){
		ans++;
		h+=d[i];
		if(h<=0){
			cout<<ans;
			break;
		}
	}
	return 0;
} 
```

---

## 作者：heyx0201 (赞：1)

# 题意
有一个人，他会执行一个长度为 $n$ 的操作序列，在第 $i$ 次操作时，他的生命值会增加 $d_i(-10^6 \le d_i \le 10^6)$，求他什么时候死，即生命值 $\le 0$。
# 思路
简单模拟题（~~sb 的我调了将近 1.5 h~~）。

没什么好说的，首先判断如果生命值只会增加，那么一定死不了，然后执行一轮的操作，如果他死在了第一轮，那么直接输出让他死亡的 $d_i$ 的 $i$，否则他一定能活过第一轮。发现每一轮他的生命值最低是 $h - \min(a_i)$，也就是如果某一轮 $h - \min(a_i) \le 0$，那么他就死了。于是可以求出他最多可以活多少轮，然后求出生前最后一轮他的生命值，最后模拟一轮的操作就好了。

具体的细节有亿点点多，在代码中说。
# 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2e5 + 10;

int n, a[MAXN];
long long h;

int main() {
  cin >> h >> n;
  long long s = 0;
  long long mi = LLONG_MAX, p = 0;
  int p2 = 0;
  bool f = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s += a[i];
    if (h + s <= 0 && !f) { // 特判死在第一轮
      f = 1;
      p2 = i;
    }
    if (s < mi) { // 求出一轮内最多减多少生命值
      mi = s, p = i;
    }
  }
  if (!f && s >= 0) { // 1145141919810 轮都死不了
    cout << -1;
    return 0;
  }
  if (f) { // 可怜的 TA 死在了第一轮
    cout << p2;
    return 0;
  }
  long long t = h + mi;
  long long ans = t / abs(s); // 计算最多活多少轮
  t += ans * s;
  ans *= n;
  int i;
  // 特判还活着的情况，继续模拟
  for (i = p + 1; i <= n && t > 0; t += a[i], i++) {
  }
  int j;
  for (j = 1; j <= p && t > 0; t += a[j], j++) {
  }
  cout << ans + i + j - 2; // -2 是因为 i 和 j 求的都是不合法的第一个位置，要同时 -1
  return 0;
}
```

---

## 作者：zhy12138 (赞：1)

本文同步发表于[我的博客](https://zhy12138.github.io/2019/03/24/CF-1141-div3/)

简单模拟题

这题让我想到了一道简单的[小学奥数题](https://www.zybang.com/question/08cac93d5b3e902ca4d64ef38039bd8a.html)

具体做法如上，判断一轮中一段前缀最多减去多少，然后再按轮减就行了

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
using namespace std;
inline ll read()
{
    ll kkk=0,x=1;
    char c=getchar();
    while((c<'0' || c>'9') && c!='-')
        c=getchar();
    if(c=='-')
        c=getchar(),x=-1;
    while(c>='0' && c<='9')
        kkk=(kkk<<3)+(kkk<<1)+(c-'0'),c=getchar();
    return kkk*x;
}
ll H,n,a[200001],sum,b[200001],ans;
int main()
{
	H=read(),n=read();
	for(register int i=1;i<=n;++i)
		a[i]=read(),sum-=a[i],b[i]=b[i-1]+a[i];
	ll minn=0;
	for(register int i=1;i<=n;++i)
		if(b[i]<minn)
			minn=b[i];
	H+=minn;
	if(H<=0)
	{
		H-=minn;
		for(register int i=1;i<=n;++i)
			if(H+b[i]<=0)
			{
				printf("%lld\n",i);
				return 0;
			}
	}
	if(sum<=0)
	{
		puts("-1");
		return 0;
	}
	ll round=H/sum;
	if(H%sum!=0)
		++round;
	ans+=round*n;
	H-=round*sum;
	H-=minn;
	for(register int i=1;i<=n;++i)
		if(H+b[i]<=0)
		{
			printf("%lld\n",ans+i);
			return 0;
		}
    return 0;
}
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1141E)


细节有一点啸多的题。可怕。

~~这要放个多测那就直接寄了。~~

记 $s$ 为前缀和。

首先你用 $\frac{H}{s_n}$ 的来算走了多少个循环节其实并不对，因为在你走的过程中可能并不需要走完一个循环节就已经结束了。

思路比较类似今年省选的 Day1 T1。就是枚举前缀作为循环节的终点，然后看剩下的就走整个循环节就做完了，这样就能够覆盖到所有的情况。

其次，如果 $s_n \ge0$，那么走一个或以上的循环节显然不优。

细节有一点多，包括但不限于：

- 答案需要开的比较大。
- 可以不走完一个循环节。（记 $s$ 为前缀和，也就是当 $s\ge0$ 时，不一定无解。）

~~没能一遍过，感觉耻辱。~~

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N =1e6+10;
    #define int long long
    int a[N],s[N],ans=1e18;
    signed main(){
    	int H,n,lst,Time=0;
    	cin>>H>>n;
    	for(int i=1;i<=n;i++)	cin>>a[i],s[i]=s[i-1]+a[i];
    	if(s[n]>=0){
    		for(int i=1;i<=n;i++)	if(H+s[i]<=0)	cout<<i<<endl,exit(0);
    		cout<<-1<<endl,exit(0);
    	}
    	for(int i=1;i<=n;i++){
    		if(s[i]>0)	continue;
    		int now=H+s[i];
    		if(now<=0)	ans=min(ans,i);
    		else{
    			if(now%s[n]==0)	ans=min(ans,now/(-s[n])*n+i);
    			else	ans=min(ans,(now/(-s[n])+1)*n+i);
    		}
    	}
    	cout<<((ans==1000000000000000000)?-1:ans)<<endl;
    	return 0;
    }
```

---

## 作者：__LZH__ (赞：0)

# CF1141E Superhero Battle

## 题意

[题面传送门](https://www.luogu.com.cn/problem/CF1141E)。

## 思路

典型的循环节问题，细节有点多。

- 首先，如果打完一轮血量不减且轮中血量大于 $0$，则无解。因为要达成条件必须使血量减少，若不减反增则一定无解。

- 其次，由于有负数，不能单纯用一轮来算，可能执行完一轮后血量大于 $0$，但中间小于 $0$，可以枚举循环节后剩的那一部分，然后计算即可（注意向上取整）。

- 最后，**记得开 `long long` ！！！**。

## 时空复杂度

时间：$O(n)$。

空间：$O(n)$。

## 代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

long long n, m, a[200010], sum[200010];

int main(){
  cin >> m >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
    sum[i] = sum[i - 1] + a[i];
    if(sum[i] + m <= 0){
      cout << i;
      return 0;
    }
  }
  if(sum[n] >= 0){
    cout << -1;
    return 0;
  }
  long long ans = 1e18;
  for(int i = 1; i <= n; i++){
    ans = min(ans, (m + sum[i] - sum[n] - 1) / (-sum[n]) * n + i);
  }
  cout << ans;
  return 0;
}

```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1141E)

# 简化题意

给定 $H,n$ 和一个长度为 $n$ 的序列 $d$，求一个最小的 $m$ 使得 $H+\sum\limits_{i=1}^{m}d_{(i-1) \bmod n+1} \le 0$。

# 解法

将式子移项后得到 $\sum\limits_{i=1}^{m}-d_{(i-1) \bmod n+1} \ge H$。

将 $\sum\limits_{i=1}^{m}-d_{(i-1) \bmod n+1}$ 拆成 $x\sum\limits_{i=1}^{n}-d_{i}$ 和 $\sum\limits_{i=1}^{y}-d_{i}$ 两部分，即 $m=xn+y$。枚举 $y \in [1,n]$，则对应的 $\min \{ x \}=\left\lceil \frac{H-\sum\limits_{i=1}^{y}-d_{i}}{\sum\limits_{i=1}^{n}-d_{i}} \right\rceil$。

最终，有 $\min\limits_{y=1}^{n} \{ \left\lceil \frac{H-\sum\limits_{i=1}^{y}-d_{i}}{\sum\limits_{i=1}^{n}-d_{i}} \right\rceil n+y \}$ 即为所求，注意精度影响，优化同 [[ABC345B] Integer Division Returns](https://www.luogu.com.cn/problem/AT_abc345_b) 。
  - 注意判无解时要对第一轮进行特判。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll d[200010],sum[200010];
int main()
{
    ll h,n,ans=0x7f7f7f7f7f7f7f7f,flag=0,i;
    cin>>h>>n;
    for(i=1;i<=n;i++)
    {
        cin>>d[i];
        sum[i]=sum[i-1]-d[i];
        if(sum[i]>=h&&flag==0)
        {
            flag=1;
            cout<<i<<endl;
        }
    }
    if(flag==0)
    {
        if(sum[n]<=0)
        {
            cout<<"-1"<<endl;
        }
        else
        {
            for(i=1;i<=n;i++)
            {
                ans=min(ans,(h-sum[i]+sum[n]-1)/sum[n]*n+i);
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1141E)。

## Solution

答案具有单调性，考虑二分。

对 $d$ 做前缀和： $s_i=\sum\limits_{j=1}^{i}d_i$，记 $mn$ 满足 $s_{mn}=\min s_i$，则我们可以先特判两种情况：

- $H+s_{mn} \le 0$，怪物撑不过第一轮。枚举 $1$ 到 $mn$，取满足 $H+s_i\le 0$ 最小的 $i$ 为答案。

- $H+s_{mn} > 0$ 且 $s_n \ge 0$，每轮后怪物的生命值都不会下降，战斗会无限持续。

接下来二分恰好能撑过 $mid$ 轮完整的战斗，界限 $l=1,r=\frac{H}{-s_n}$，注意 $s_n<0$，所以要取绝对值。

设 $now=H+mid \times s_n$，对于 $mid$ 进行如下验证：

- $now \le 0$：正好 $mid$ 轮，无需多余回合，答案 $ans \leftarrow n\times mid$，返回 $1$。

- $now+s_{mn} > 0$，需要更多完整轮数，返回 $0$。

- 否则枚举 $1$ 到 $mn$，取 $ans$ 为最小的满足 $H+s_i \le 0$ 的 $i$，返回 $1$。

复杂度 $O(n\log maxn)$，其中 $maxn=10^{12}$，$\log maxn$ 约等于 $40$。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int h,n,a[N],s[N],mn,ans;

bool check(int x){
	int now=h+x*s[n];
	if(now<=0){
		ans=x*n;
		return 1;
	}
	if(now+s[mn]>0) return 0;
	
	int p=mn;
	for(int i=mn-1;i>=1;--i) if(now+s[i]<=0) p=i;
	ans=x*n+p;
	return 1;
}

main(){
	h=wrd(),n=wrd();
	for(int i=1;i<=n;++i){
		s[i]=s[i-1]+(a[i]=wrd());
		if(!mn || s[mn]>s[i]) mn=i;
	}
	if(h+s[mn]<=0){
		int p=mn;
		for(int i=mn-1;i>=1;--i) if(h+s[i]<=0) p=i;
		return printf("%lld",p),0;
	}
	if(s[n]>=0) return puts("-1"),0;
	
	int l=1,r=-h/s[n]+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	return printf("%lld",ans),0;
}
```

---

## 作者：_Flame_ (赞：0)

## 思路

题目要求最小次数，这个东西显然符合单调性，可以用二分答案解决。

令 $sum_i$ 表示 $d$ 数组的前缀和，$mn$ 为 $sum_i$ 的最小值。这里分三种情况：

- $0\leq sum_n$，这时怪永远都死不了，输出无解即可。

- $mn+h \leq 0$，这时可以在一轮之内杀死怪，直接输出第一个 $h+sum_i \leq 0$ 的位置即可。

- 上面的两种都不满足，这时二分一个 $s$ 表示最少多少轮内可以将怪击杀，最终答案为 $s\times n+cnt$，其中 $cnt$ 为 $s$ 轮后最终击杀怪的位置，二分终止的条件为 $sum_n\times s+mn\leq0$， 即在 $s$ 轮后在取到最小值时肯定可以击杀怪。

二分的范围为 $1$ 到 $\frac{h}{-sum_n}+1$，可以过。

## Code

```cpp

#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=301000;
const int maxm=110;
const int mod=1e9+7;
const int inf=1e18;

int h,n;
int id;

int a[maxn],sum[maxn],mn=inf;

bool check(int x){
	int cnt=h-abs(sum[n])*x;
	if(cnt+mn<=0){
		return 1;
	}
	else{
		return 0;
	}
}

void solve(){
	h=read(),n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
		mn=min(mn,sum[i]);
	}
	if(h+mn<=0){
		for(int i=1;i<=n;i++){
			if(h+sum[i]<=0){
				write(i);
				puts("");
				return ;
			}
		}
	}
	if(sum[n]<0){
		int l=1,r=h/abs(sum[n])+1;
		int ans;
		while(l<=r){
			int mid=l+r>>1;
			if(check(mid)){
				r=mid-1;
				ans=mid;
			}
			else{
				l=mid+1;
			}
		}
		int ans1=ans*n,cnt1=h-(abs(sum[n])*ans),flag;
		for(int i=1;i<=n;i++){
			cnt1+=a[i];
			if(cnt1<=0){
				flag=i;
				break;
			}
		}
		write(flag+ans1);
		puts("");
	}
	else{
		puts("-1");
		return ;
	}
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}



```




---

## 作者：MuYC (赞：0)

#### 前言
这道题目其实就是 NOIP 2020 T4 微信步数 的40分做法。

这里提供 O($n$ + $log 10^{12}$)的做法 ------ 二分 + 前缀和(时间复杂度就是O(n))。

#### 题目分析

不难发现，这道题目是要我们求最少多少天就会杀死怪物，同时，这个东西是具有**单调性**的。

（有解的情况下） 天数越多肯定就会扣除怪物越多的血量，所以我们可以采用二分。

同时，这个题目肯定许多情况会循环往复进行许多轮，所以我们二分的对象就是会进行多少轮。

#### 具体做法

二分的话check函数就是二分的灵魂，往往check函数就会决定二分的复杂度。

采用前缀和优化后，我们可以找一个前缀和数组中的最小值 $M$ ？

求出来的 $M$ 就是表示在同一轮的操作中能够扣除的血量最大值。

假设我们现在二分到的是第 $x$ 轮 ， 那么我们判断 $H + sum[n] * x + M$ 是否小于等于 $0$  即可。

不难发现，这个check函数我们是可以实现 O(1) 判断答案合法性的。

这样子我们就可以通过二分找到要轮多少轮啦。

最后扫一遍前缀和数组就可以获得答案了。

#### 细节：

+ $Case1:$不需要轮许多轮，也就是第一轮就可以获得答案。
判断 $H$ 与 $M$ 的大小关系即可。

+ 在$Case1$ 不成立的情况下，也就是需要轮许多轮，但是我们发现轮完一轮得到的扣除怪物的血量为0,肯定无解。

+ 判断**无解**的方式(**最重要的一点**):
采用答案判断无解法，我们发现倘若题目给出的数据有解，答案肯定不会超过 $H * (n + 1)$，否则就是无解。

#### Code

(代码里面有注释，因为笔者比较菜，题目分析可能不够详尽，看不懂题目分析就看看代码吧)

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 200005;
int n,H,M = 0x3f;
int sum[MAXN];
 
inline int read()
{
    int x = 0 , flag = 1;
    char ch = getchar();
    for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
 
bool check(int x)
{
    if(x < 0ll)return 0;
    if(x * sum[n] + M + H <= 0ll) return 1;//O(1) check
    else return 0;
}
 
signed main()
{
    H = read() , n = read();
    for(int i = 1 ; i <= n ; i ++)
    {
        int x = read();
        sum[i] = sum[i - 1] + x;//累加前缀和
        M = min(M,sum[i]);//获得前缀和数组里面最小的一个
    }
    if(M + H <= 0ll)//这就是不需要进行多轮循环的情况
    {
        for(int i = 1 ; i <= n ; i ++)
            if(sum[i] + H <= 0ll ){cout << i ; break;}
        return 0;
    }
    if(sum[n] >= 0){cout << -1; return 0;}//假设需要多轮循环，但是每轮情况进行完使得怪物的血量增加或者不变，无解
    int Ans = -H / sum[n] + 5;//最多进行多少轮。
    for(int i = log2(Ans) ; i >= 0ll ; i --)
        if(check(Ans - (1ll << i))) Ans -= (1ll << i);
    int out = Ans * n;
    for(int i = 0 ; i <= n ; i ++)//一个小细节，从0开始枚举就是判断是否当前已经可以让怪物死了
        if(sum[i] + sum[n] * Ans + H <= 0ll) {out += i;break;}。
    if(out > (n + 1) * H)cout << -1;//根据得到的答案判断无解
    else cout << out;
    return 0;
}
```

---

## 作者：little_sun (赞：0)

### 题目大意

有一个有着$h$点血量的boss,
你的每一个回合有$n$种攻击

第$i$种攻击可以对boss造成$-d[i]$的伤害($h=h+d[i]$)

求最早在什么时候能击败boss(即boss血量$\leq0$)

### 题解

首先我们发现,回合数越少越好(废话)

怎么让回合数最小呢？

我们发现,让boss剩下最多(但是在一个回合内能够击杀)的血量时回合数最少

然后就没有然后了。。。

把boss的血量压到一个回合能击杀的范围内然后枚举即可

具体见代码(注意开long long!)

### Code

```cpp
#include <bits/stdc++.h>
#define R register
#define ll long long
#define cmin(a, b) ((a < b) ? a : b)
#define cmax(a, b) ((a < b) ? b : a)
const int MaxN = 2e5 + 10;
typedef std::pair<int, int> pa;
ll h, n;
ll d[MaxN], sum[MaxN];
int main()
{
    scanf("%lld%lld", &h, &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &d[i]), sum[i] = sum[i - 1] + d[i];
    for (int i = 1; i <= n; i++)
        if (h + sum[i] <= 0)
            return 0 * printf("%d\n", i);
    if (sum[n] >= 0)
        return 0 * printf("-1");
    ll min = *std::min_element(sum + 1, sum + n + 1);
    ll cnt = (h + min - 1) / (-sum[n]) + 1;
    h += cnt * sum[n];
    for (int i = 1; i <= n; i++)
        if (h + sum[i] <= 0)
            return 0 * printf("%lld\n", i + cnt * n);
    return 0;
}

```



---

