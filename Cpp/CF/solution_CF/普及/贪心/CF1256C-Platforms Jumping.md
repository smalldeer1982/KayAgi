# Platforms Jumping

## 题目描述

有一条宽度为$n$的河。河的左岸编号为$0$，右岸编号为$n + 1$。河流上还有$m$个木制平台，第$i$个平台的长度为$ci$（所以说第i个平台占据河流的$ci$个连续位置）。保证平台长度的总和不超过n。

你正站在$0$（左岸），并且想到达右岸即$n + 1$的位置。如果您站在位置x，则可以跳到$[x + 1; x + d]$范围内的任何位置。但是， 你只能跳到木质平台上（ _即不能下水_ ）。例如，如果$d = 1$，则只能跳到下一个位置（如果这个位置上有木制平台）。您可以假设单元格$0$和$n + 1$属于木制平台。

您可以将任意平台向左或向右移动任意次数（也可以不移动），只要它们彼此不重叠（但两个平台可以挨在一起）。也就是说你不能更改平台的相对顺序。

**请注意，你应该先移动平台再跳跃（一旦你出发后，你就不能再移动平台了）。**

例如，如果$n = 7$，$m = 3$，$d = 2$和$c = [1,2,1]$，这就是从左岸跳到右岸的方法之一：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1256C/df0d8d2f8a9c6cd940b3eabc79499fe8d2091270.png)

## 样例 #1

### 输入

```
7 3 2
1 2 1
```

### 输出

```
YES
0 1 0 2 2 0 3 
```

## 样例 #2

### 输入

```
10 1 11
1
```

### 输出

```
YES
0 0 0 0 0 0 0 0 0 1 
```

## 样例 #3

### 输入

```
10 1 5
2
```

### 输出

```
YES
0 0 0 0 1 1 0 0 0 0 
```

# 题解

## 作者：jianhe (赞：3)

[CF1256C Platforms Jumping](https://www.luogu.com.cn/problem/CF1256C)
题解

### 算法：贪心
先贪心地将跳过路段最大化，跳出边界后再一个个紧挨着放即可。

### 代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long

const ll N=1010;

ll n,m,d,ans,c[N],sum,i,t,p=1;

int main(){

	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

	cin>>n>>m>>d;d--;

	for(i=1;i<=m;i++) cin>>c[i],sum+=c[i];	

	if(sum+(m+1)*d<n){

		cout<<"NO";

		return 0;
        //最大化路程，也无法达到终点

	}else cout<<"YES\n";

	t=n-sum;i=0;

	while(i<=n){

		for(int j=1;j<=d&&t;j++){

			cout<<"0 ";

			i++,t--;
            //能跳则跳

		}

		if((++i)>n||p>m) return 0;

		for(int j=i;j<c[p]+i;j++) cout<<p<<" ";
        //不能跳就挨着放

		p++;

	}

	return 0;

}
```

---

## 作者：wlj_55 (赞：2)

## 题意简述
有一条河，长度为$n$，你有$m$块木板，每块长度为$c_i$，你可以跳跃，每次跳跃可以跳$[1,d]$中任意距离，求一种合法的放置木板的方案，使得你可以每一次都跳在木板上，直到跳到河对岸。

要求：每块木板都**必须按顺序**放，木板可以相交，但不能重叠。

## 思路
直接贪心每次跳最大距离放木板一定不可行，因为可能到了最后放不完所有木板。

但是让我们换一种思路，我们先把所有的木板放在河上，然后再挪动这些木板，观察到剩余的空隙部分是不会变的，于是我们可以贪心，每次先跳最大距离，跳完后在该点放木板，直到跳满空隙为止。之后再放上所有木板即可。

## Code
```cpp
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int n,m,k,a[1005],ans[1005];
bool cmp(int x,int y){
	return x>y;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	int sm=0;
	for(int i=1;i<=m;i++){
		scanf("%d",&a[i]);
		sm+=a[i];
	}
	if(sm==0){
		printf("NO\n");
		return 0;
	}
	int emp=n-sm;
	if(emp>(k-1)*(m+1)){
		printf("NO");
		return 0;
	}
	int now=1,p=0;
	while(p<n){
		if(emp<k-1){
			p+=emp+1,emp=0;
			for(int i=p;i<=p+a[now]-1;++i)
			ans[i]=now;
			p+=a[now]-1;
			now++;
		}
		else{
			p+=k,emp-=k-1;
			for(int i=p;i<=p+a[now]-1;++i)
			ans[i]=now;
			p+=a[now]-1;
			now++;
		}
	}
	printf("YES\n");
	for(int i=1;i<=n;i++)
	  printf("%d ",ans[i]);
}
```

---

## 作者：small_turtle (赞：1)

简单的贪心题，30min 水完，顺便捞了个 0ms 最优解。
***
### 一、无解判定：
首先贪心的让每次跳的距离最大（即 $d-1$），那么跳过木板可以一个一个跳，最多能跳过 $m+1$ 河流，如果木板的总长度加上这 $m+1$ 次最多能跳的长度还不能到达河流长 $n$，则无解。

代码：
```cpp
if(sum+(m+1)*d<n)
{
	puts("NO");
   return 0;
}
```
否则输出 `YES`。

### 二、方案构造：
令 $jl$ 为需要跳过河流长度（即 $n-sum$）为了必定可构造出解，可以先每次跳最远（即 $d-1$），直到不能再跳，此时后面的木板只能是长长的无空隙的一条。

只需要模拟此思路便能构造出正解，具体见代码。
***
### 三、CODE：
```cpp
/*
Author:xwg
Time:2022.11.2
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define unordered_map map
const int inf=2147483647;
const double eps=1e-6;
using namespace std;

int n,m,d,sum,jl,now=1,a[1005];
bool b[1005];

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
    scanf("%d%d%d", &n, &m, &d);
    --d;
    for(int i=1;i<=m;++i)
    {
        scanf("%d", &a[i]);
        sum+=a[i];
    }
    b[0]=b[n+1]=true;
    if(sum+(m+1)*d<n)
    {
        puts("NO");
        return 0;
    }
    puts("YES");
    jl=n-sum;
    int i=0;
    while(i<=n)
    {
    	if(jl)
    	{
    		for(int j=1;j<=d;++j)
    		{
    			printf("0 ");
    			++i;
    			--jl;
    			if(!jl)
    			{
    				break;
    			}
    		}
    	}
    	++i;
    	if(i>n||now>m)
    	{
    		break;
    	}
    	int r=a[now]+i;
    	for(int j=i;j<r;++j)
    	{
    		printf("%d ", now);
    	}
    	++now;
    }
	return 0;
}
```
时间复杂度 $\mathcal{O(n)}$，[通过记录](https://www.luogu.com.cn/record/93080408)。

---

## 作者：Big_Dinosaur (赞：0)

构造题。

在前面几次多跳几个单位，后面合并在一起，是合法方案。

尽可能让前面经过河流跳 $d$ 格，相邻两块木板隔 $d-1$ 格，第 $\lfloor\dfrac{n-\sum^{m}_{i=1}c_i}{d}\rfloor$ 组隔 $n-\sum^{m}_{i=1}c_i-d\times\lfloor\dfrac{n-\sum^{m}_{i=1}c_i}{d}\rfloor$ 格，其它相邻。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mp make_pair
using namespace std;
namespace IO {
	inline int r() {
		int z=1,y=0;
		char t=getchar();
		while(t<'0'||t>'9') {
			if(t=='-')z=-1;
			t=getchar();
		}
		while(t<='9'&&t>='0') {
			y=(y<<1)+(y<<3)+(t^48);
			t=getchar();
		}
		return z*y;
	}
	inline void w_(int x) {
		if(x<0) {
			x=-x;
			putchar('-');
		}
		if(x==0)return;
		w_(x/10);
		putchar(x%10+48);
	}
	inline void wln(int x) {
		if(x==0)putchar('0');
		else w_(x);
		putchar('\n');
	}
	inline void ww(int x) {
		if(x==0)putchar('0');
		else w_(x);
		putchar(' ');
	}
	inline void w(int x) {
		if(x==0)putchar('0');
		else w_(x);
	}
}
using namespace IO;
namespace Dino {
	int n,m,d,a[114514],Ans[114514],now,N;
	inline void _() {
		n=r(),m=r(),d=r();
		N=n;
		for(int i=1; i<=m; ++i)a[i]=r(),N-=a[i];
		for(int i=1; i<=m; ++i) {
			now+=min(d,N+1);
			for(int j=1; j<a[i]; ++j)Ans[now++]=i;
			Ans[now]=i;
			N-=(d-1);
			if(N<0)N=0;
		}
		if(now+d<=n)puts("NO");
		else {
			puts("YES");
			for(int i=1; i<=n; ++i)ww(Ans[i]);
		}
	}
}
signed main() {
	Dino::_();
}
```

---

## 作者：jiangchen1234 (赞：0)

### 题目描述

请看题目翻译。

### 思路

对于本题，我们可用贪心的思想来判断是否能过河。

我们可以将起点和终点均看作平台，那么就最多有 $m + 1$ 个空隙，而每次最多跳 $d - 1$ 格，所以不用平台的个数最多为 $(m + 1) \times (d - 1)$，我们只要求出平台的总长度 $sum$。如果 $sum + (m + 1) \times (d - 1) < n$ 就不能被构造出来。

代码如下：

```cpp
il bool check() {
	return sum + (m + 1) * (d - 1) < n;
}
```

判断完能否构造，我们再来看如何构造。

我们可以求出一共要跳几次，然后就可以一个一个枚举出当前点应该是什么。

### 代码

[提交记录](https://codeforces.com/problemset/submission/1256/236381327)

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define rg register
#define F(i,l,r) for(rg int i(l),i##end=r;i<=i##end;++i)
#define G(i,l,r) for(rg int i(l),i##end=r;i>=i##end;--i)
#define endl '\n'
il int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;
}
il void write(int x) {
	if(0<=x&&x<=9) {
		putchar(x + '0');
		return ;
	}
	write(x/10);
	putchar(x%10+'0');
}
int cnt,n,m,d,c[1005],f[1005],a[1005],sum,cnt1,cnt2;
il bool check() {
	return sum + (m + 1) * (d - 1) < n;
}
signed main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	n = read(),m = read(),d = read();
	F(i,1,m) {
		a[i] = read();
		sum += a[i];
	}
	if(check()) {
		puts("NO");
	} else {
		cout<<"YES"<<endl;
		if(d - 1 == 0) {
			cnt1 = 0;
		} else cnt1 = (n - sum) / (d - 1);
		F(i,1,m) {
			if(cnt2 < cnt1) {
				++cnt2;
				cnt += d - 1;
			}
			F(j,1,a[i]) {
				c[cnt + j] = i;
			}
			cnt += a[i];
		}
		F(i,1,n) {
			cout<<c[i]<<" ";
		}
	}
	return 0;
}





```


---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF1256C)
## 题意：
有一条宽度为 $n$ 的河。河的左岸编号为 $0$，右岸编号为 $n+1$。河流上还有 $m$ 个木制平台，第 $i$ 个平台的长度为$c_i$（所以说第i个平台占据河流的 $c_i$ 个连续位置）。保证平台长度的总和不超过 $n$。

你正站在 $0$（左岸），并且想到达右岸即 $n+1$ 的位置。如果您站在位置 $x$ ，则可以跳到 $[x+1 \cdots x+d]$ 范围内的任何位置。但是， 你只能跳到木质平台上（即不能下水）。例如，如果 $d=1$，则只能跳到下一个位置（如果这个位置上有木制平台）。您可以假设单元格 $0$ 和 $n+1$属于木制平台。

您可以将任意平台向左或向右移动任意次数（也可以不移动），只要它们彼此不重叠（但两个平台可以挨在一起）。也就是说你不能更改平台的相对顺序。

请注意，你应该先移动平台再跳跃（一旦你出发后，你就不能再移动平台了）。

如果不可能从 $0$ 达到 $n+1$，则在第一行中输出 ```NO```。否则，在第一行中打印```YES```，在第二行中输出长度为 $n$ 的数组 输出河流的序列（不输出单元格 $0$ 和单元格 $n+1$）。

如果河流单元格i不属于任何平台，输出 $0$。否则，它应该是等于平台的编号（平台编号是从 $1$ 到 $m$ 输入的顺序）。
## 思路：
首先贪心的让每次跳的距离最大（即 $d-1$），那么跳过木板可以一个一个跳，最多能跳过 $m+1$ 个河流，如果木板的总长度加上这 $m+1$ 次最多能跳的长度还不能到达河流长 $n$，则无解，输出 ```NO```。

令 $hl$ 为需要跳过河流长度（即 $n-sum$）为了必定可构造出解，可以先每次跳最远（即 $d-1$），直到不能再跳，此时后面的木板只能是长长的无空隙的一条。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n=0,m=0,d=0,c[100001]={},sum=0,hl=0,now=1,j=0;
/*sum为木板总长度,hl为需要跳过河流长度,now是现在木板的编号*/
int main(){
	scanf("%lld%lld%lld",&n,&m,&d);
	--d;
	for(int i=1;i<=m;i++){
		scanf("%lld",&c[i]);
		sum+=c[i];
	}
	if(sum+d*(m+1)<n){
		printf("NO");
		return 0;
	}
	printf("YES\n");
	hl=n-sum;
	while(j<=n){
		if(hl!=0){
			for(int i=1;i<=d;i++){
				hl--;
				j++;
				printf("0 ");
				if(hl==0){
					break;
				}
			}
		}
		j++;
		if(j>n||now>m){
    		break;
    	}
		for(int i=j;i<c[now]+j;i++){
			printf("%lld ",now);
		}
		now++;
	}
	return 0;
}
```

---

## 作者：lsr1409111459 (赞：0)

#### 1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1256C)）

##### 1.1 题目大意

有一条长度为 $n$ 的河，你站在坐标 $0$ 处，要到达坐标 $n+1$ 处。

你会跳，但每次最多只能跳 $d$ 坐标距离。即你可以从 $0$ 到达 $1\sim d$ 的任意坐标处，但是不能到 $d+1$ 及更大的坐标处。

你有 $m$ 块木板，可以在木板上随意走动。在开始前你可以随意放木板，但要遵守以下规则：

（1）木板的相对位置不能变。即木板只能按照输入顺序排列。

（2）木板只能放在河里，即不能有木板跑到岸上。

（3）木板间不能重叠，即河里的每个坐标上至多只能放一块木板。

（4）一旦你开始跳跃，木板就不能再更改位置。

本题可能有多种解，因此采用 $spj$ 。

##### 1.2 输入格式

第一行三个整数 $n,m,d(1 \leq n,m,d \leq 1000,m \leq n)$ 。分别表示河的长度，木板的数量和能跳的最远距离。

第二行 $m$ 个整数 $c_1,c_2,...,c_m(1 \leq c_i \leq n,\sum\limits_{i=1}^m{c_i \leq n})$ 。其中 $c_i$ 表示第 $i$ 块木板的长度。

##### 1.3 输出格式

如果不能到达 $n+1$ 处，则输出一行 "NO"。

否则，则共两行输出。第一行输出 "YES"。

第二行输出满足要求的木板的放法。共 $n$ 个数字，表示坐标为 $i$ 的位置放了哪块木板。如果没有木板即为 $0$ ，否则输出木板对应的下标值。注意，输出要满足题干要求的规则。

#### 2 解题思路

贪心。我们在能跳到的最远距离处放下一块木板，并走到木板最末尾处跳下一次。我们要时刻记录答案，但注意我们可能用不到所有木板，因此针对这种情况要特别处理（因为题目要求我们用到所有木板）。个人处理是把所有木板放在最后面。

官方的题解是直接把所有木板放在最后面，然后需要木板的时候就直接拿过来，觉得很巧妙。

#### 3 解题代码

```cpp
#include <iostream>
using namespace std;
int n,m,d;
int a[1010];
int ans[1010];
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=m;i++)scanf("%d",&a[i]);
    int now=0,i=1;//now表示当前位置，i表示当前木板号
    while(now+d<=n&&i<=m)
    {
        now+=d;
        for(int j=now;j<=min(n,now+a[i]-1);j++)
            ans[j]=i;
        now+=(a[i++]-1);
    }
    if(now+d<=n)printf("NO\n");//如果所有木板放完后，now+d还是没有达到n+1，则说明无解
    else
    {
        printf("YES\n");
        if(now>=n+1)i--;//如果now大于等于n+1，说明最后放的木板有一部分放在了岸上
        now=n;
        for(int j=m;j>=i;j--)//倒序放没有放的木板
        {
            for(int k=now;k>=now-a[j]+1;k--)
            {
                if(ans[k])i=ans[k];//如果这个位置之前有木板，则这块木板也需要重新放
                ans[k]=j;
            }
            now=now-a[j];//注意，此时的now是下一块木板的结束位置，因此不是now-a[j]+1。后者是当前木板的开始位置
        }
        for(int i=1;i<=n;i++)printf("%d ",ans[i]);
        printf("\n");
    }
    return 0;
}
```

#### 4 解题心得

本题难度不高，但是最后处理未放置木板时需要特别注意，稍有差错便会导致WA。细节还是很重要。比如最开始把 $i=ans[k]$ 写成 $i=k$ 这种问题。这道题考场上用时28min，属实有点拖进度。

---

