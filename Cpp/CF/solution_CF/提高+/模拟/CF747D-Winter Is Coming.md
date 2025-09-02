# Winter Is Coming

## 题目描述

The winter in Berland lasts $ n $ days. For each day we know the forecast for the average air temperature that day.

Vasya has a new set of winter tires which allows him to drive safely no more than $ k $ days at any average air temperature. After $ k $ days of using it (regardless of the temperature of these days) the set of winter tires wears down and cannot be used more. It is not necessary that these $ k $ days form a continuous segment of days.

Before the first winter day Vasya still uses summer tires. It is possible to drive safely on summer tires any number of days when the average air temperature is non-negative. It is impossible to drive on summer tires at days when the average air temperature is negative.

Vasya can change summer tires to winter tires and vice versa at the beginning of any day.

Find the minimum number of times Vasya needs to change summer tires to winter tires and vice versa to drive safely during the winter. At the end of the winter the car can be with any set of tires.

## 说明/提示

In the first example before the first winter day Vasya should change summer tires to winter tires, use it for three days, and then change winter tires to summer tires because he can drive safely with the winter tires for just three days. Thus, the total number of tires' changes equals two.

In the second example before the first winter day Vasya should change summer tires to winter tires, and then after the first winter day change winter tires to summer tires. After the second day it is necessary to change summer tires to winter tires again, and after the third day it is necessary to change winter tires to summer tires. Thus, the total number of tires' changes equals four.

## 样例 #1

### 输入

```
4 3
-5 20 -3 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 2
-5 20 -3 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
10 6
2 -5 1 3 0 0 -4 -3 1 0
```

### 输出

```
3
```

# 题解

## 作者：XiXi (赞：2)

### [题目链接](https://www.luogu.org/problemnew/show/CF747D)

### 思路分析

显然的一个贪心，首先算出下雪的天数$t$是否超过$k$，如果是就直接输出$-1$

在最坏情况下，每到雪天就换成雪地胎，过了雪天就换成普通的轮胎，也就是对于每一段连续的雪天都要换$2$次轮胎，$Ans=2\times t$

我们可以考虑将两段雪天并到一起，也就是在这两段之间不下雪时也用雪地胎，那么$k-=($不下雪天数$),Ans-=2$

根据贪心，我们每次将两段离得近的雪天并一起，这样得到的$Ans$最小

最后特判一下，如果最后换雪地胎可以直接用到结束，$Ans--$

### 代码解析
```cpp
#include<bits/stdc++.h>
#define mn 1111111
using namespace std;
int n,k,i=1,x,l=-1,s,p,q,a[mn];
int main()
{
	for (scanf("%d%d",&n,&k);i<=n;i++) 
	{
		scanf("%d",&x); 
		if (x<0) {if (p) a[++q]=i-p-1; l=p=i; s+=2; k--;}
	}
    //a数组记录两段雪天之间的天数,l记录最后一次雪天
	if (k<0) return puts("-1"),0; sort(a+1,a+1+q);
    //k不足下雪天数直接输出-1		顺便排个序
	for (i=1;i<=q;i++) if (k>=a[i]) k-=a[i],s-=2; else break;
    //贪心
	printf("%d",n-l<=k?s-1:s);
    //如果最后可以一直用雪地胎就保留
}
```

---

## 作者：jiangjiangQwQ (赞：1)

### 思路
首先这是一道贪心题。对于 $t_i<0$ 的雪天，我们用一个变量 $cnt$ 统计总天数。无解输出 $-1$ 的情况就是当 $cnt>k$。在雪地轮胎还能使用的前提下，考虑将一些要使用普通轮胎的**连续段**换成雪地轮胎，减少换轮胎的次数。即将每段使用普通轮胎的道路长度**从小到大**排序。设当前道路长度为 $len$，则在 $k\geq len$ 的时候把答案减少 $2$，并将 $k$ 减去 $len$。在最后，我们还需要特判最后一次雪天往后的路是否小于等于剩余雪地轮胎的使用次数，如是，将答案减 $1$。因为这在合并道路的时候没有将这段考虑进去。
### 代码
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
#define int long long
#define re register
#define For(i,l,r) for(re int i=l;i<=r;i++)
#define Rep(i,l,r) for(re int i=l;i>=r;i--)
const int N=3e5+5;
inline void fast(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
}
inline void read(int &x){
   x=0;int f=1;
   char c=getchar();
   while(!isdigit(c)){
		if(c=='-') f=-1;
		c=getchar();
   }while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
   }x*=f;
}
inline void write(int x){
   if(x<0){x=-x;putchar('-');}
   if(x>9) write(x/10);
   putchar(x%10+'0');
}int n,k;
int ans;
vector<int> ind;
priority_queue<int,vector<int>,greater<int> > d;
signed main(){
	fast();
	cin>>n>>k;
	int cnt=0,last=1e18;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		if(x<0){
			++cnt;
			if(last!=(int)(1e18)) d.push(i-last-1);
            last=i;
		}
	}
	if(cnt>k){
		cout<<-1;
		return 0;
	}
    // cout<<"ok\n";
	k-=cnt;
	ans=cnt*2;
	int max_ind=last;
    if(last==(int)(1e18)) max_ind=0;
	while(d.size()){
		int val=d.top();
        d.pop();
		if(k>=val){
			k-=val;
			ans-=2;
		}
	}
	if(k>=n-max_ind) ans--;
	cout<<max(ans,0ll);
	return 0;
}
```

---

## 作者：12345678hzx (赞：1)

## 题目大意
有两种轮胎，分别是雪地胎和普通轮胎。雪地胎可以在雪天行驶，而普通轮胎只能在不下雪的时候行驶。但雪地胎最多只能用 $k$ 天。

共有 $n$ 天，每一天有可能下雪，你需要统筹每一天使用哪种轮胎，使得其满足要求且换轮胎的次数最少，初始默认为普通轮胎。数据可能无解。
## 思路
显然，对于无解的情况，只有可能是下雪的天数超过 $k$，否则我们一定可以找出一种合法解，即雪天用雪地胎，否则就不用。

这启发我们想出一种思路，如果对于每一个雪天，我们都用雪地胎，则对于每一段连续的雪天我们都要换 $2$ 次胎，即开始一次和结束一次。

那么我们要如何让答案减少呢？也就是在不下雪的时候用雪地胎，将两段连续的雪天合并在一起，使答案减少 $2$。

所以，我们先预处理出连续的雪天，再贪心排序间隔，能合并就合并，最后注意特判最后一天不必换回来。

---

## 作者：WhisperingWillow (赞：0)

简单贪心题。

[题目传送门](https://www.luogu.com.cn/problem/CF747D)

考虑贪心。

先把下雪天都消耗掉雪胎，初始答案为下雪天数 $\times 2$，发现可以进行一个类似反悔贪心的算法：

- 如果还有一串连续的陆地，可以用雪，则我们贪心选择长度最小的，可以将答案减少 $2$，可以用堆来实现。
- 特判最后还可以被雪胎代替普通胎，但这样只能对答案减少 $1$。

当然，如果下雪天数 $>k$，报告无解。

---

## 作者：skyskyCCC (赞：0)

## 前言。
这是一道贪心题，但是如果你认为是一道数学题也是完全没有问题的。这个题有点某次 ABC 题的弱化版。
## 分析。
首先我们要判断一些是否可能存在方案，如果没有方案那么唯一的可能性就是雪地轮胎不够用。此时统计一些就可以判断。

那么如果雪地轮胎够用，那么一定存在方案。此时我们就要让换胎次数尽可能少。我们可以将这个天气的情况看做是一个个被隔开的区间。因为我们每次遇到下雪情况都从普通胎换成雪地胎，再从雪地胎换成普通胎，那么如果在某段区间内可以不用换胎，当且仅当在两个下雪天之间的一个全是晴天的区间。那么如果我们雪地胎够用那么我们便可以在这个区间内不换胎，即这段路都用雪地胎，那么这一段路都可以不用换胎。如果我们在考虑什么晴天，换成普通胎，那么显然多了换胎的次数。这时我们只需要考虑下界，也就是最后换成雪地胎还是普通胎即可。

还需要注意一点就是换胎次数不可能是负的所以要判断一下，如果是负的转换成 $0$ 即可。 

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n,k;
int tot,sum,cou,ans;
int a[200005],b[200005];
int main(){
	cin>>n>>k;
	cou=-k*2;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]<0){
			a[i]=-1;
			tot++;
		}
		else a[i]=1;
	}
	if(tot>k){
	    cout<<"-1\n";
		return 0;
	}
	k-=tot;
	tot*=2;
	for(int i=1;i<=n;i++){
		if(a[i]==-1){
			b[++sum]=i-cou-1;			
			cou=i;
		}
	}
	ans=cou;
	cou=1;
	sort(b+1,b+1+sum);
	while(true){
		if(k-b[cou]>=0){
			tot-=2;
			k-=b[cou];
			cou++;
		}
		else break;	
		if(cou>sum){
		    break;
		}
	}
	if(k>=n-ans){
	    tot--;
	}
	tot=max(tot,0);
	cout<<tot<<"\n";
	return 0;	
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Fan_Tuan (赞：0)

## 题意：
有雪地胎和普通轮胎两种轮胎，雪天只能用雪地胎，雪地胎最多只能用 $k$ 天，不下雪的时候都可以用，告诉你 $n$ 天内是否下雪，问度过这 $n$ 天最少的换轮胎次数，初始状态为普通轮胎，如果无论如何都无法度过这 $n$ 天，输出 -1。

## 思路：

如果下雪天大于 $k$，那么直接输出 -1。

否则考虑先将最差的 $ans$ 计算出来，即每次遇到不同的天气都进行换轮胎。

如果要使答案更优，无疑是在不下雪的时候用雪地胎，以求少换轮胎。
那么我们可以将每一连续的非负整数段的长度存起来。

最后，贪心的每次从中取出最小的长度，如果此时的 $k$ 大于等于此时的长度，那么 $ans$ 减去 2，一直到 $k$ 不满足情况为止，此时的答案为最优的。

注意，最后一个负数之后的区域如果进行处理的话，$ans$ 应该减 1 而不是减 2。 

## 代码：

```c
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
// #define int long long
using  namespace  std;

inline int read() {
	int f = 0, s = 0;
	char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void print(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 2e5 + 10;
int n, k, a[maxn];

priority_queue<int, vector<int>, greater<int> > q;

signed main() {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	int flag = 0, last = 1, id = 0;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] < 0) k--, id = i;
		if (a[i] < 0 && flag == 0) {
			if (i - last > 0 && last != 1) q.push(i - last);
			flag = 1;
			ans++;
		}
		if (a[i] >= 0 && flag == 1) flag = 0, last = i, ans++;
	}
	if (k < 0) print(-1);
	else {
		while (!q.empty()) {
			if (k - q.top() >= 0) {
				k -= q.top();
				q.pop();
				ans -= 2;
			}
			else break;
		}
		if (a[n] >= 0 && id && n - id > 0 && k - (n - id) >= 0) ans--; 
		print(ans);
	}
	return 0;
}
```

---

