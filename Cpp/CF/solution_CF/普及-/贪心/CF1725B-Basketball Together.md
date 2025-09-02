# Basketball Together

## 题目描述

在篮球比赛中，一个队的球员人数没有最大或最小限制（不一定每场比赛有 $5$ 名球员）。比赛中有 $N$ 名候选球员将由世界上最好的篮球教练 Pak Chanek 训练。第二个候选玩家具有 $P_i$ 的幂。

Pak Chanek 将从 $N$ 名候选球员中组成零支或多支球队，条件是每个候选球员最多只能加入一支球队。Pak Chanek 的每一支球队都将被派去与拥有 $D$ 力量的敌方球队进行一次比赛。在每一场比赛中，如果阵型球员的力量之和严格大于 $D$，则被派去的球队将被称为击败敌方球队。

Pak Chanek 的一项技能是，当一支已经组建的球队在比赛中比赛时，他可以改变球队中每个球员的力量，使之等于球队中最大的球员力量。

输出 Pak Chanek 可获得的最大获胜次数。

## 样例 #1

### 输入

```
6 180
90 80 70 60 50 100```

### 输出

```
2```

# 题解

## 作者：ztrztr (赞：9)

# CF1725B
## 题意
这道题的意思是给定一个长度为 $N$ 的数组和 $D$，现在你可以把数组的任意的几个数改为数组里的另外的一个数，问修改完后最多可以组成多少组总和大于 $D$ 的组。
## 思路
一道贪心水题，我们先看数据：
```cpp
in:
6 180
90 80 70 60 50 100

out:
2

```
我们可以让一个大的带几个小的，这样就可以把较小的变为这几个数中最大的（原因见题目），比如这个样例就可以如下分组：
1. $100,50$ 一组，改为 $100,100$，$100 + 100 = 200,200 > 180$
2. $90, 80, 70$ 一组（有人会问为啥不能 $90, 70$ 一组，$90 + 90 = 180,180 \ge 180$ 但注意题目要求**严格大于**，所以不行），$90 + 90 + 90 = 270, 270 > 180$

那么实现就很简单了，具体步骤如下：

- 输入；排序。
- 设置变量 $Count, sum$，一个用来计数，一个看有没有超；倒序遍历数组；贪心，让 $sum + (\lfloor \frac{D} {P_i} \rfloor + 1)$（注意因为是**严格大于** $D$，所以要$+1$。
- 检查有没有超如果 $sum > N$ 那就超了，如果超了，退出循环；计数器加 $1$。
- 输出。

## 代码
```cpp
/*

 problem : https://www.luogu.com.cn/problem/CF1725B
 by : ztrztr(luogu 602124)
 date : 2022/10/16
 update : 2022/10/16
 
*/
#include<bits/stdc++.h>
using namespace std;
int N, D, P[100005];
int main() {
	cin >> N >> D;
	for (int i = 1; i <= N; i ++) {
		cin >> P[i]; //这是输入，不用说了 
	}
	sort (P + 1, P + N + 1); //排序，贪心是从大的开始往小的贪
	int Count = 0, sum = 0; //计数器 
	for (int i = N; i >= 1; i --) { //注意，因为我们是从大到小排序的，所以循环是倒着 
		sum += D / P[i] + 1; //注意，要加一，文中已说明
		if (sum > N) break;//如果严格大于N，直接结束循环 
		Count ++; //计数器 ++ 
	} 
	cout << Count;
}
```

---

## 作者：Purple_Circle (赞：2)

[传送门：Basketball Together](https://www.luogu.com.cn/problem/CF1725B)

题目说的很明白了，每次只要尽可能让实力强的人上场就行。

贪心如下：

每次打败敌方球队的人数需求为 $\Big\lfloor \displaystyle\frac{d}{p_i}\Big\rfloor +1$（$+1$ 是因为要严格大于对方），然后把上场的人从全部人中减去，$ans$ 每次 $+1$ 即可。

代码如下:
```cpp
#include<bits/stdc++.h>
#define rd read()
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}
int a[100010];
int n,d,ans;
int main(){
	n=rd,d=rd;
	for(int i=1;i<=n;i++){
		a[i]=rd;
	}
	sort(a+1,a+n+1,[](int x,int y){return x>y;});
	int rn=n;
   	for(int i=1;i<=n;i++){
    		rn-=(d/a[i]+1);
        	if(rn<0){
        		break;
		}
        	ans++; 
    	}
    	cout<<ans;
    	return 0;
}
```

---

## 作者：whitenightdaye (赞：2)

比较好写的贪心，只需要先选最大的，再从较小的人里面选一些人组队和敌方打一架，当然因为贪心，我们只需考虑人够即可，不用考虑到底选那些人，即一直枚举 $\left\lceil\dfrac{d}{a_i}+1\right\rceil$，直到人不够了结束即可。

#### 注意是严格大于，所以要加一。

# $ACcode$

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,d,p[100010],ans,r;
bool cmp(int x,int y)
{
    return x>y;//从大到小排序。
}
int main()
{
    cin>>n>>d;
    for(int i=1;i<=n;i++)
    {
        cin>>p[i];
    }
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        r+=d/p[i]+1;
        if(r>n) break;//如果人不够了就结束循环，输出答案。
        ans++;
    }
    cout<<ans;
    return 0;
}
```

蒟蒻的第二篇题解，如有错希望大佬指出，蒟蒻感激不尽。

---

## 作者：skcks (赞：1)

本题为
# 贪心题
Pak Chanek可以将任意球员的力量改为当前球队的最高球员的力量，最好是最高的力量的球员带一帮~~小弟弟~~力量小的球员。

敌方力量为 $d$，所以我们将 $p_i$ 从大到小枚举，所有球员都可以被Pak Chanek变成当前球队球员最大值，也就是 $p_i$，所以要求每队要上多少人就是求 $d$ 里面有多少个 $p_i$。

这里注意一下**严格大于**，下面分两种情况：

1. $\dfrac{d_i}{p_i}$ 是整数，说明敌人与球员力量相等，要求大于，所以加 $1$。

1. $\dfrac{d_i}{p_i}$ 不是整数，很好理解，所以缺一半的球员要补上，所以加 $1$。

由此推出公式：    $ans= \sum_{i=1}^n{\dfrac{d_i}{p_i}+1} $

# AC代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;
long long n,d;
long long tot=0; 
long long ans=0;
long long s[100001]; //十年OI一场空，不开long long见祖宗
bool cmp(long long a,long long b){
	return a>b;//由大到小排序
}
int main(){
	scanf("%lld%lld",&n,&d);//考试时必用scanf，因为比cin快特多
	for(int i=1;i<=n;i++){
		scanf("%lld",&s[i]); 
	} 
	sort(s+1,s+n+1,cmp);
	while(1){
		tot++;
		n-=(d/s[tot])+1;//统计剩余人数
		if(n<0){
			break;
		} 
		ans++;
	}
	printf("%lld",ans);
	return 0;//好习惯
}
```

---

## 作者：Kevin0007 (赞：1)

题意：

将 $n$ 个数分为 $k$ 组，使得每一组中的数的个数乘以这一组中的最大数的乘积都大于 $d$。求 $k$ 的最大值。

分析：

每次都用一个尽可能大的数带一些较小的数，这样可以保证利益最大化。

方法我们了解了，但如何实现是一个问题。

我们可以让所有已经被选的人数每次都和总人数比较，当备选的人数大于总人数时，说明 $k$ 已经达到了最大值，就可以跳出循环了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,a[100005],m,sum;
int main(){
  cin>>n>>d;
  for(int i=1;i<=n;i++) cin>>a[i];
  sort(a+1,a+n+1);
  for(int i=n;i>=1;i--){
    m+=(d/a[i]+1);
    if(m>n) break;
    sum++;
  }
  cout<<sum<<endl;
  return 0;
}
```


---

## 作者：Le_Saint_Chevalier (赞：1)

 很明显的**贪心**，先选力量最大的，去和敌方作战，需要的人数为
 $$m=\left\lceil\dfrac{D}{P_i}+1\right\rceil$$
 至于为何要加一，是因为题目中要求严格大于。
 所以，可以用 sort 从大到小排一遍序，再逐次累加，直到人数超限跳出。

# $ACCode$ 
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,d;
int a[100005];
int ans=0;
int p;
bool cmp(int x,int y)
{
	return x>y;//从大到小排序，方便贪心
}
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		p+=d/a[i]+1;
		if(p>n)
		break;
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```
本蒟蒻第二篇题解，大佬轻喷


---

## 作者：Wind_Smiled (赞：0)

## 简要题意
Pak Chanek 将从 $N$ 名候选球员中组成零支或多支球队，条件是每个候选球员最多只能加入一支球队。Pak Chanek 的每一支球队都将被派去与拥有 $D$ 力量的敌方球队进行一次比赛。在每一场比赛中，如果阵型球员的力量之和严格大于 $D$，则被派去的球队将被称为击败敌方球队。

Pak Chanek 的一项技能是，当一支已经组建的球队在比赛中比赛时，他可以改变球队中每个球员的力量，使之等于球队中最大的球员力量。


给定两个整数 $N$ 和 $D$，候选球员的数量和敌方球队的实力。

再给定 $N$ 个整数 $P_1$、$P_2$、$\ldots$、$P_ N$（$1≤P_i≤10^9$），所有候选球员的能力。


------------

### 贪心
显然，对于 Pak Chanek 的能力，要最大利用就必然是挑选能力最大的一个和最小的几个进行组队，只要能够击败对方，不再挑人，总人数减去这一组的人数作为下一轮可供挑选的人数。

排序使数组有序，运用手写 `cmp` 函数进行降序排列。循环枚举最大可能值。


------------

### 计算
对于每一次挑选，有总能力值等于能力值最大的球员的能力乘所选球员的个数。

设最大球员的能力为 $p_i$，对手能力值为 $d$。

则有个数 $ans= \lceil d/p_i \rceil $ 个 ，因为是严格大于，所以运用语言优势，舍去小数位后再加一，即最终个数为 $ans=d/p_i+1$。

判断人数是可能的情况（为非负整数），如果不是，则退出循环，否则答案就增加一。

最后输出答案即可。


------------

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,p[1000005],ans;
bool cmp(int a,int b){
	return a>b;//降序排列 
}
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++){
		scanf("%d",&p[i]);
	}
	sort(p+1,p+n+1,cmp);
	int n1=n;
	for(int i=1;i<=n;i++){
		n1-=d/p[i]+1;//对于每一次要击败对手，就要付出这么多的人数
		if(n1<0){
			break;//不符合就退出 
		}
		ans++;//未退出的话就表示有一种可能，累计答案 
	}
	printf("%d",ans);//把答案输出即可 
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：0)

## 题意
+ 你有 $N$ 个球员。
+ 你要组建一些队伍，其中每个球员的力量 $P_i$ 可以达到队里最高球员力量。
+ 队伍总力量**严格大于**对方队伍总力量 $D$ 即可取胜

## 突破
由题可得，
> Pak Chanek 可以改变球队中每个球员的力量，使之等于球队中最大的球员力量。

那么我们的贪心就有了思路。我们只需要选取一个最强者，然后堆几个人上去提高力量。此时我们尽可能选取一些力量小的球员，这样贪心带来的利益最高。

这时候每次的出场人数就非常明显了，对方的力量除以我们最厉害的球员（其实也是全体球员）的力量再加一。  
**注意：严格大于**对面力量才能取胜，所以不能向上取整而必须加一。可得公式 $D\div P_i+1$。

### 做法
首先对数组 $P$ 排序，每次选出力量最大的球员并算出这个球员还需带多少球员才能取胜，并把他们移除备选名单。当球员不够时结束算法。

## 代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100005;
int p[N], b[N];

bool cmp(int x, int y) {
  return x > y; //推荐使用从高到低排列力量 
}

int main() {
  int n, d;
  cin >> n >> d;
  for(int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  sort(p + 1, p + n + 1, cmp);
  int ans = 0;
  for(int i = 1; i <= n; i++) {
    long long a = d / p[i]; //使用我们推导出的公式，第一个球员已经被选所以需要减一 
    if(n - a >= i) {
      n -= a; //从后往前排除最弱的球员 
      ans++; //排除第一个最强的球员 
    } else {
      break; //球员不够了 
    }
  }
  cout << ans;
  return 0;
}
```

### 题外话
贪心的突破点一般在于把利益最大化。本题中的利益很明显是更大的力量，所以关键点在于如何提升力量。  
事实上并没有所谓 Pak Chanek 教练。根据姓氏推测他可能是匈牙利人或印度尼西亚人。  
本蒟蒻一直在坚持不懈的写第一篇题解。

---

## 作者：szhqwq (赞：0)

## 分析

这是一道简单贪心，因为可以将上场球员的能力值改为在场球员的最大值，所以，我们只要先从大到小排序，然后遍历 $p_i$，每次 $\lceil \frac{d}{p_i}+1\rceil$，这个表示的是我方需多少人才能战胜敌方，因为必须要大于，所以要加一。我们使用一个变量来存储我方上场的人，如果这个值一旦大于 $n$ 那么就结束循环，不然最大胜利数加一。

AC code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N=1e5+10;

int n,d;
int p[N];

inline bool cmp(int a,int b) { return a>b; }

signed main() {
	ios::sync_with_stdio(false);
	cin>>n>>d;
	for(int i=1;i<=n;i++) cin>>p[i];
	sort(p+1,p+n+1,cmp);
	int res=0,cnt=0;
	for(int i=1;i<=n;i++) {
		res+=d/p[i]+1;
		if(res>n) break;
		cnt++;
	}
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：lidundun (赞：0)

# Basketball Together
由于教练可以是力量变成最强球员的力量，所以决定最终力量的因素只有最强球员和球员数量，而最强球员力量强的情况下人数也可以减少，于是我们想到了贪心。

当我们选择了一个力量强的球员时，为了使力量变大，我们要多选几个球员，但是考虑到下一次选人，此时的最优方案就是选上几个力量弱的。

所以先把输入数组排个序，找一个最强的带上几个最弱的，然后用过的队员就可以排除掉了。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,s,a[100010];
int main()
{
	scanf("%d%d",&n,&m);
	m++;
	for(int i=1;i<=n;i++)  scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int l=1,r=n;
	while(l<=r&&n)
	{
		if(m%a[r]==0)  t=m/a[r];
		else  t=m/a[r]+1;
		if(n>=t)
		{
			s++;
			n-=t;	
		}
		l+=t-1;
		r--;
	}
	printf("%d",s);
}
```


---

## 作者：Tomato_Ya (赞：0)

## 题意
给你 $n$ 个人，让你组建几支球队，每个人最多只能进入一支球队，然后和一支球队去比赛，如果你的球队力量和大于 $D$，那么你就能打败他。

你有一项技能，可以让球队里所有队员的力量都变成球队里力量最大的那个球员的力量。

让你输出获胜次数。
## 思路
由于我们拥有可以让队员力量增大的技能，所以我们每次出场时派出一个力量大的队员，再在力量足够的情况下尽可能少的带力量小的队员，然后我们使用技能，让力量小的队员的力量都变大了，并且所有人都一样。

这时候每次的出场人数就等于你要战胜敌人需要的力量除以每次出场队员中力量最大的那个队员的力量加上一，也就是 $a=D\div P_i+1$。

### 具体做法
输入 $P$ 数组后进行从大到小排序，循环枚举从 $1$ 到 $n$，算出每次要选的队员数 $a$，从数组最前面选一个力量最大的队员，再在数组末尾带上 $a-1$ 个力量小的队员，这时进行判断如果 $n-a$ 大于等于 $i$，就说明队员还够我选，数组的长度 $n$ 减去 $a-1$，同时获胜场数 $s$ 加 $1$，如果 $n-a$ 小于 $i$，说明剩余的人已经不够选了，直接 ```break``` 跳出循环就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,s,p[100005],b[100005];
bool cmp(int x,int y){
    return x>y;
}
int main(){
    cin>>n>>d;
    for(int i=1;i<=n;i++)cin>>p[i];
    sort(p+1,p+1+n,cmp);
    for(int i=1;i<=n;i++){
        long long a=d/p[i]+1-1;
        if(n-a>=i)n-=a,s++;
        else break;
    }
    cout<<s;
    return 0;
}
```


---

## 作者：LiaoYF (赞：0)

本题是一个**贪心题**，贪心的方法也很好想。先从实力强的人开始上场，每次打败敌方球队需要的人数就是 $\large \frac{d}{p_i}+1$（因为是严格大于，所以要加一），然后把上场的人数从总人数里去掉就行了。
## AC代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(int x,int y){//排序从大到小
    return x>y;
}
int p[100005];
int main(){
    int n,d,ans=0;
    cin>>n>>d;
    for(int i=0;i<n;i++){
        cin>>p[i];
    }
    sort(p,p+n,cmp);//排序
    int nn=n;
    for(int i=0;i<n;i++,ans++){//打败一支球队后更新答案
        nn-=d/p[i]+1;
        if(nn<0)break;//人不够，退出循环
    }
    cout<<ans;//输出
    return 0;
}
```
[record（由于RMJ爆了所以是CF本站的）](https://codeforces.com/contest/1725/submission/173700963)

---

## 作者：cyhtxdy (赞：0)

比较显然的贪心。

因为一个队伍中的每个人的能力值取决于最大能力值的人，那么可以将所有人的能力值从大到小排序，每次选取 $p_i$，要想大于 $d$，该队伍所需要的人数就是 $\frac{d}{p_i}+1$，累计人数并且累加答案。枚举 $p_i$，当所需要的人数大于 $n$ 时，输出答案即可。

得到代码：
```
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

#define int long long

int p[N], n, d;

signed main () {
	cin >> n >> d;
	for (int i = 1; i <= n; i ++) {
		cin >> p[i];
	}
	sort (p + 1, p + 1 + n, greater<int>());//从大到小排序
	int ans = 0, now = 0;
	for (int i = 1; i <= n; i ++) {
		now += d / p[i] + 1;//累加所需人数
		if (now > n) {
			break;
		}
		ans ++;//累加答案
	}
	cout << ans;
	return 0;
}
```


---

## 作者：YH_Eternally (赞：0)

## 题意

有 $n$ 个球员，组建若干支球队，每个人最多只能进入一支球队。如果球队人数 $\times$ 球队最大力量值大于 $D$，那么就可以打败另一支球队，求最大的可能的获胜次数。

## 思路

明显的一道贪心题，所以我们将队员的力量值由大到小排序，每次用力量尽可能大的球员带力量较小的球员，确保队伍的力量和最大化。

## 代码实现方法

不难发现，我们每次派出的人数为 $\lfloor\frac {D}{P_i}\rfloor+1$，记录共选了多少人，当人数大于 $n$ 时，跳出循环，输出答案即可。

## 代码

``` cpp
#include <bits/stdc++.h>

using namespace std;

int n, p[105010], d, ans, sum;

inline int read() {
    int x = 0, f = 1;
    char ch;
    ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = 0;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return f ? x : -x;
}

bool cmp(int x, int y) {
    return x > y;
}

int main() {
    n = read();d = read();
    for(int i = 1; i <= n; i ++) p[i] = read();
    sort(p + 1, p + n + 1, cmp);//由大到小排序
    for(int i = 1; i <= n; i ++) {
        sum += d / p[i] + 1;//求队伍人数，累加
        if(sum > n) break;//跳出循环
        else ans ++;
    }
    printf("%d\n", ans);
    return 0;//完结撒花
}
```



---

