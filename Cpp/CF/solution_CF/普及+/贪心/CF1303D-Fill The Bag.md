# Fill The Bag

## 题目描述

You have a bag of size $ n $ . Also you have $ m $ boxes. The size of $ i $ -th box is $ a_i $ , where each $ a_i $ is an integer non-negative power of two.

You can divide boxes into two parts of equal size. Your goal is to fill the bag completely.

For example, if $ n = 10 $ and $ a = [1, 1, 32] $ then you have to divide the box of size $ 32 $ into two parts of size $ 16 $ , and then divide the box of size $ 16 $ . So you can fill the bag with boxes of size $ 1 $ , $ 1 $ and $ 8 $ .

Calculate the minimum number of divisions required to fill the bag of size $ n $ .

## 样例 #1

### 输入

```
3
10 3
1 32 1
23 4
16 1 4 1
20 5
2 1 16 1 8```

### 输出

```
2
-1
0```

# 题解

## 作者：fls233666 (赞：4)

首先我们看到 $1 \le n \le 10^{18}$，那么显然不能用传统的背包 DP 来写这题了。

这时我们不妨来观察题目的其他性质。我们注意到，我们只关心我们用现有的或者划分后的物品是否能把背包填满，而并不关心我们用了多少物品。而且题目的物品大小也很有特点：$a_i$ 是 $2$ 的非负整数次幂。既然涉及到了 $2$ 的次幂，我们又要使用物品填满背包，为什么不考虑**把 $n$ 和 $a_i$ 转化成二进制表示**呢？

那么设 $a_i=2^k(k \in \mathbb{N})$。仔细一想，我们发现，如果把 $a_i$ 和 $n$ 都转化为二进制数表示后，原本为 $2^k$ 的 $a_i$ 会转化为 $1\underbrace{000 \cdots 000}_{k-1}$ 的形式。换一个方式想，此时的 $a_i$ 能填掉 $n$ 的二进制表示下的第 $k$ 位的 $1$。

再看 $n$ 的范围，我们知道 $2^{60}>10^{18}$，所以 $n$ 拆分后不会超过 $60$ 位。于是我们可以开一个数组当作桶，记录能填掉第 $k$ 位上的 $1$ 的物品有几个。将 $n$ 二进制拆分后，我们可以从低位到高位依次处理二进制表示下的 $n$。如果处理到的位数上的数字是 $1$，就考虑拿物品填掉这一位，如果此时这一位没有对应的能填掉的物品，就直接找更高位上是否有对应的物品。如果有则进行划分，直到有物品把当前位的 $1$ 填上。同时，因为存在 $2^k+2^k=2^{k+1}$，在处理完第 $i$ 位跳到第 $i+1$ 位时，可以把大小为 $2^i$ 的物品两两合并后带到第 $i+1$ 位上计算。这样暴力把 $n$ 的所有二进制表示下的 $1$ 填掉，背包就被正好填满了，此时的划分次数就是答案。

想到了这些，无解的情况也就很容易考虑到了。当 $\sum_{i=1}^{n} a_i <n$ 时，所有的物品放进背包都无法填满背包，必然无解。**因为无论怎样划分，物品的总大小都是不变的。**

于是这题就在这个 $O(n)$ 的贪心中做完了，下面放上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define rgt register int
#define qmx(a,b) a<b?b:a
using namespace std;

const int mxn = 1e5+5;
const int mxht = 60;

int m,ans,wht[62],wxn[62],out_n; 
ll n,cake[mxn],mxcake,sumcake;

inline ll getcake(){
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	ll inx = (c^48);
	c=getchar();
	while(c>='0'&&c<='9'){
		inx=inx*10+(c^48);
		c=getchar();
	}
	return inx;
}  //快速读入


int main(){
	int test;
	scanf("%d",&test);
	while(test--){
		n=getcake();
		m=getcake();
		mxcake=sumcake=out_n=ans=0;
		memset(wht,0,sizeof(wht));
		for(rgt i=1;i<=m;i++){
			cake[i]=getcake();
			sumcake+=cake[i];
			mxcake=qmx(mxcake,cake[i]);
		}//读入数据
        
		if(sumcake<n){
			printf("-1\n");
			continue;
		}//判断无解
        
		sort(cake+1,cake+1+m);
		for(rgt iwh=1,cntwh=1,i=1;iwh<=mxcake;iwh<<=1,cntwh++){
			while(i<=m&&cake[i]==iwh){
				wht[cntwh]++;
				i++;
			}			
		}//把每个物品放到对应的桶中
        
		while(n){
			out_n++;
			wxn[out_n]=(n&1);
			n>>=1;
		}//求 n 的二进制表示
        
		for(rgt dti,i=1;i<=out_n;i++){
			wht[i]+=wht[i-1]/2;  //填充上一位的物品两两合并后放到下一位的桶中一起计算
			if(wxn[i]){  //当前位是 1，找物品填充。
				if(!wht[i]){  //没有物品，去更高位上找物品
					dti=i+1;
					while(!wht[dti])
						dti++;
					while(dti>i){
						ans++;
						wht[dti]--;
						wht[dti-1]+=2;
						dti--;
					}  //找到物品，划分，直到回到第 i 位
				}
				wht[i]--; //用一个物品填上这一位
			}
		}
		printf("%d\n",ans);  //得到答案
	}
	return 0;
}

```


---

## 作者：installb (赞：4)

Codeforces官方评分：$\sf{1800}$  

贪心题，没用到什么前置知识，码量也不大，比较考验思维。  

首先如果 $\sum a_i<n$ 则一定填不满，否则一定能够填满（拆分至全部为 $1$ 一定可行）  

直接加很难处理，考虑先全部盒子的大小加上去，然后移走一些盒子使得大小之和正好为 $n$，需要移走盒子的大小之和 $s=\sum a_i-n$。  

考虑到每一个盒子大小都是 $2^i$，考虑把 $s$ 写成二进制形式，如果第 $i$ 位为 $1$ 则需要移走一个大小为 $2^i$ 的盒子。  
有两种改变盒子大小的方式：  
- 把两个大小为 $2^i$ 的盒子拼成一个 $2^{i+1}$ 的盒子。
- 把一个大小为 $2^i$ 的盒子拆成两个 $2^{i-1}$ 的盒子，花费为 $1$。

接下来就是贪心，按位处理，从低位到高位，对于第 $i$ 位，如果这一位需要移走一个 $2^i$ 的盒子，那么要是有对应大小的盒子就直接移走一个，没有的话就先记录，直到遇到一个有盒子的位 $j$，把这一位的盒子一路拆分到有记录的最小的位，这样 $i$ 到 $j-1$ 位每一位会各有一个盒子，而我们其实也只需要一个，**注意这样处理完之后第 $j$ 位可能还需要移走盒子但是没盒子了，没关系，把这位记录下来，然后后面照常做**。  
处理完上面的事情后，这一位剩余的盒子（如果还有）已经没用了，所以把它们两两拼成 $2^{i+1}$ 的盒子，处理下一位。  

把各对应大小的盒子数量 存个数组记录。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
using namespace std;
typedef long long LL;

map <LL,LL> mp;
LL dvd[36],cnt[36],sum;
LL T,n,m,a[500005];

LL solve(LL x){
	for(LL i = 0;i <= 32;i ++) if((x >> i) & 1) dvd[i] = 1;
	LL ret = 0,lst = -1;
	for(LL i = 0;i <= 32;i ++){
		if(lst != -1 && cnt[i]){ cnt[i] --; ret += (i - lst); lst = -1; }
		if(dvd[i]){
			if(cnt[i]) cnt[i] --;
			else if(lst == -1) lst = i;
		}
		cnt[i + 1] += (cnt[i] >> 1);
		cnt[i] = cnt[i] & 1;
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin >> T;
	for(LL i = 0;i <= 32;i ++) mp[(1LL << i)] = i;
	while(T --){
		memset(cnt,0,sizeof(cnt));
		memset(dvd,0,sizeof(dvd));
		cin >> n >> m; sum = 0;
		for(LL i = 1;i <= m;i ++){
			cin >> a[i];
			cnt[mp[a[i]]] ++; sum += a[i];
		}
		sum -= n;
		if(sum < 0){ cout << -1 << endl; continue; }
		cout << solve(sum) << endl;
	}
	return 0;
}
```
我认为这题难度不小，至少比这场比赛的 $\mathsf{E}$ 题要难。  

知识点400码量600算法应用(好像没有)思维1600

---

## 作者：linyihdfj (赞：1)

## D.Fill The Bag ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16436837.html)
### 题目描述： ###
[原题面](https://codeforces.com/problemset/problem/1303/D)
### 题目分析： ###
考虑物品大小都是 $2$ 的非负整数次幂也就可以联想到将 $n$ 二进制拆分，因为这些物品的顺序不影响答案所以就考虑将他们存放到 $cnt$ 数组中去。

考虑如果 $n$ 的当前位我们数组中有那么直接减就好了，很显然这样做最优。而如果没有那么就要考虑是用比当前位小的那些数加和凑出这个位还是从比当前位更大的位拆。

那么这样就意味着我们要维护一个 $sum$ 代表比当前位小的那些数的和，如果这个值大于当前位的值显然就扫一遍比它小的位然后减去这些位的值直到减为 $0$ 就好。

而如果用比它小的数凑不出来当前位那么就找到比当前位大的最小的有值一位，然后从这一位一直拆，拆到当前位然后减掉就好了。
### 代码详解： ###

```
#include<bits/stdc++.h>
using namespace std;
const long long MAXN = 3e5+5;
long long cnt[MAXN];
int main(){
	long long t;
	cin>>t;
	while(t--){
		memset(cnt,0,sizeof(cnt));
		long long flag = 0;
		long long n,m;
		long long mx = 0;
		cin>>n>>m;
		for(long long i=1; i<=m; i++){
			long long a;
			cin>>a;
			cnt[int(log2(a))]++;
			mx = max(mx,a);
			flag += a;
		}
		if(flag < n){
			printf("-1\n");
			continue;
		}
		long long sum = 0;
		long long now = 0;
		long long ans = 0;
		while(n){
			if(n & 1){
				if(cnt[now]){
					cnt[now]--;
				}
				else if(sum >= (1<<now)){  //用低位补 
					long long res = (1<<now);
					for(long long i=now-1; i>=0 && res; i--){  
						if(cnt[i] * (1<<i) <= res){
							sum -= cnt[i] * (1<<i);
							res -= cnt[i] * (1<<i);
							cnt[i] = 0;
						}
						else{
							while(cnt[i] && (1<<i) <= res){
								res -= (1<<i);
								sum -= (1<<i);
								cnt[i]--;
							}
						}
					}
				}
				else{  //找到高位拆
					for(long long j = now+1; j<=mx; j++){
						if(cnt[j]){
							for(long long k=j; k>now; k--){
								cnt[k-1] += 2;
								cnt[k]--;
								ans++;
							}
							break;
						}
					}
					cnt[now]--;
				}
			}
			n>>=1;
			sum += cnt[now] * (1<<now);
			now++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

注意一开始先判断有无解，也就是所有数加起来能不能大于等于 $n$，若能大于等于显然有解。

---

## 作者：Error_Eric (赞：1)

### 前言

估——值——

wtcl

![](https://cdn.luogu.com.cn/upload/image_hosting/o4nppr1u.png)

### 正文

这道题是道思维题。

首先，我们不妨把所有的物品放入背包。

这个时候，如果物品还不够，那么显然是没法满足要求，输出 ``-1`` 的情况了。

如果刚刚好或者超过了背包的大小，显然是有解的，毕竟可以将所有物品拆分成大小为 $1$ 的物品。

所以可以转化为求可否从总数中去掉若干个物品，使得最终的总重刚好为 $n$ 。

然后因为每个物品的大小都是 $2$ 的幂次。所以可以考虑按位枚举。

举个例子：

```
10 3
1 32 1
```

>先将所有的物品塞进背包里。此时背包里总体积为 $34$ 。所以需要减去体积为 $24(11000B)$ 的物品。

>最低位的 $1$ 在第三位上。

>$2^3=8$。没有 $8$ 。

>向上传递 $8$。

>$2^4=16$。没有 $16$。

>显然，如果有一个数拆分之后得到了 $8$ 在这之前一定遗留下了一个 $16$ 。

>向上传递 $8$ 。

>$2^5=32$ 有 $32$ 。

>拆分$32$。拆分到 $8$ 需要拆分两次。

>此时拆分完毕，答案为 $2$ 。

具体实现看代码。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define NO -1
#define int long long //不然 "WA on test 8"
const int size=100005;
int t,n,m,a[size],tot,bar[31];
int log2(int x){//log2,好理解吧。
	int ans=0;
	while(x>1)x>>=1,++ans;
	return ans;
}
void f(int x){//贪心
	int ans=0,l=NO;//l表示之前没有减掉的最小为多少。
	for(int i=0;i<30;i++){//按位枚举。
		if((l!=NO)and(bar[i]!=0))bar[i]--,ans+=(i-l),l=NO;
		if((x>>i)&1)
			if(bar[i])bar[i]--;//如果这一位要减，而且刚刚好有这个数。
			else if(l==NO)l=i;//不然就等到到了高位在减去。
		bar[i+1]+=(bar[i]>>1);bar[i]&=1;//更新,把所有的这个体积的合并成更大的。
	}
	printf("%lld\n",ans);//输出结果。
}
void mian(){
	scanf("%lld%lld",&n,&m),tot=0;//输入
	for(int i=0;i<31;i++)bar[i]=0;//一定要记得初始化，循环一定要从0开始，不然"WA on test 3"。
	for(int i=1;i<=m;i++)
		scanf("%lld",&a[i]),tot+=a[i],bar[log2(a[i])]++;//输入，记录总数，统计每个数出现的个数。
	if(tot<n)return(void)puts("-1");//如果总数小于背包大小，直接输出-1。
	else return f(tot-n);//不然就继续。
} 	
signed main(){
    scanf("%lld",&t);
    while(t--)mian();
}
```

---

## 作者：ix35 (赞：1)

一道玄学题。

第一步：玄学分析，感觉要把 $n$ 拆成二进制，然后考虑。

第二步：玄学贪心，从低位往高位贪，如果当前位的数的个数不小于 $2$，且 $n$ 在这一位上没有值，那么可以直接进位，例如我有三个 $8$，如果 $n$ 在 $8$ 这一位上是 $0$，那么就可以直接变成 $16$ 和 $8$。

第三步：玄学策略，如果 $n$ 当前这一位上是个 $1$，且没有这个盒子，那么就将离得最近的一个高位上的盒子分解到这一位上来。

感觉是对的，严格证明可能有些麻烦。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=70;
int t,m;
ll n,sum,ans,powof2[MAXN],x,cnt[MAXN];
int main () {
	scanf("%d",&t);
	powof2[0]=1;
	for (int i=1;i<=60;i++) {powof2[i]=powof2[i-1]*2;}
	for (int ii=1;ii<=t;ii++) {
		scanf("%lld%d",&n,&m);
		memset(cnt,0,sizeof(cnt));
		sum=ans=0;
		for (int i=1;i<=m;i++) {
			scanf("%lld",&x);
			sum+=x;
			for (int j=0;j<=60;j++) {
				if (powof2[j]==x) {cnt[j]++;break;}
			}
		}
		if (sum<n) {printf("-1\n");continue;}
		for (int i=0;i<=60;i++) {
			if (n&(1ll<<i)) {
				if (cnt[i]) {cnt[i]--;}
				else {
					int cur=i;
					while (!cnt[cur]) {cnt[cur]++;cur++,ans++;}
					cnt[cur]--;
					continue;
				}
			}
			cnt[i+1]+=cnt[i]/2;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：panyanppyy (赞：0)

## Problem 
给你 $m$ 个形如 $2^x$ 的数，一次操作可以把一个数分成两半，求用最少的操作数分割出若干个数和正好为 $n$（背包容量）。
## Solution
不会二进制，贪之。

考虑不用拆的数从大往小取显然更优，那要拆的数是哪些呢？

考虑当你不取这个数时剩下数的和比剩下背包容量小那不取这个数显然不能填满背包，那就只能把他拆了。

那一个贪心就应运而生了：

用大根堆维护一剩下可以取得数，如果要拆，就把它拆成两份继续放入堆中，否则考虑如果它比当前 $n$ 大就扔了，否则放入背包中继续这个过程。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
int T,m,ans;
ll n,s;
priority_queue<int>q;
inline void work(){
	scanf("%lld%d",&n,&m),ans=s=0;
	q=priority_queue<int>();
	for(int i=1,x;i<=m;i++)
		scanf("%d",&x),q.emplace(x),s+=x;
	if(s<n)return puts("-1"),void();
	while(n){
		int x=q.top();q.pop();
		if(x<=n)n-=x,s-=x;
		else if(s-x<n)ans++,q.emplace(x>>1),q.emplace(x>>1);
		else s-=x;
	}
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--)work();
	return 0;
}
```

---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16166876.html)  
[题目传送门](https://codeforces.com/problemset/problem/1303/D)
### 题目大意
给定一个大小为 $k$ 的背包以及 $n$ 个物体。第 $i$ 个物体的体积为 $a_i$，并且保证 $a_i$ 为 $2$ 的非负整数幂。现在你可以将一些物品切开，变成两个只有体积为原来一半的物体，求能把背包恰好装满至少需要切几次。
### 题目解析
不难想到二进制拆分。考虑贪心。  
二进制拆分后，如果这一位没有大小恰好为 $2^i$ 的物体，那么就去更大的切分。  
如果从高到低考虑，我们不难发现这是假的，所以考虑从低到高位考虑。  

具体的做法是这样的：  
从低位到高位考虑，如果这一位恰好有大小为 $2^i$ 的物体，那么就不需要切割，否则就找到最小的更大的物体来切割。  

现在来证明这种做法的正确性和时间复杂度。  
先证明正确性。不难发现如果将一个大小为 $2^c$ 的物体分割成大小为 $2^a$ 的物体，和把一个大小为 $2^c$ 的物体分割成 $2^b$ 的物体再分割成 $2^a$ 的物体所需的次数是一样的（$a<b<c$）。所以这个做法是正确的。  
然后证明时间复杂度。如果我们将分割了一个大小为 $2^b$ 的物体到 $2^a$ 的大小，那么就会多出 $2^{a+1},2^{a+2},\dots,2^{b-2},2^{b-1}$ 这些物体。因此在暴力向上查找最小的更大的物体切割的时候，每个物体最多被搜到一次，所以可以保证时间复杂度为 $\Theta\left(n\right)$。

无解的情况是显然的，因为切割的时候总体积不变，所以只要 $\sum a_i<k$ 的时候就无解，否则是有解的，因为你可以把所以的物体切成大小为 $1$ 的大小。  

核心代码：
```cpp
int n,x,ans,t[39]; ll m,sum;
void work(){
	m=read(); n=read(); Me(t,0); sum=0; ans=0; int i,j;
	for(i=1;i<=n;i++) x=read(),sum+=x,t[(int)log2(x)]++;
	if(sum<m){ puts("-1"); return; } if(sum==m){ puts("0"); return; }
	for(i=0;i<31;i++){
		if(!t[i]&&(m&(1<<i))){ j=i; while(!t[j]) j++,ans++; t[j]--; for(j=j-1;j>=i;j--) t[j]++; }
		if(m&(1<<i)) t[i]--; t[i+1]+=(t[i]>>1);
	} print(ans),pc('\n'); return; 
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑从低位到高位放数。             

显然如果 $\sum_{i = 1} ^ m a_i < n$ 就直接无解。

如果低位没数就从最近的高位拿一个数放下来就可以了，选后面的高位是不优的因为你可以后面再去选它然而走下来的路径也不会更短。            

时间复杂度 $O(m \log a_i)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
long long n,sum,ans;
int m,a[Len],cnt[66];
int main()
{
	//freopen("buy.in","r",stdin);
	//freopen("buy.out","w",stdout);
	int T;scanf("%d",&T);
	while(T --)
	{
		memset(cnt , 0 , sizeof cnt);
		ans = sum = 0;
		scanf("%lld %d",&n,&m);
		for(int i = 1 ; i <= m ; i ++) 
		{
			scanf("%d",&a[i]);
			sum += a[i];
			for(int j = 0 ; j <= 33 ; j ++) 
			{
				if((1ll << j) == a[i]) 
				{
					cnt[j] ++;
					break;
				}
			}
		}
		if(sum < n){puts("-1");continue;}
		for(int i = 0 ; i <= 61 ; i ++) 
		{
			if((n >> i) & 1) 
			{
				if(cnt[i]) cnt[i] --;
				else
				{
					for(int k = i + 1 ; k <= 61 ; k ++) 
					{
						if(cnt[k]) 
						{
							cnt[k] --;
							ans += k - i;
							for(int j = k - 1 ; j >= i ; j --) cnt[j] ++;
							break;
						}
					}
				}
			}cnt[i + 1] += (cnt[i] >> 1);
		}
		printf("%lld\n",ans);
	}
	return 0;
} 
```

---

## 作者：syksykCCC (赞：0)

我们可以按位贪心。

用 $c_i$ 表示 $a$ 数组中 $2^i$ 出现的个数，记 $sum = \sum\limits_{i=1}^{m} a_i$，显然，有解的充要条件是 $sum \ge n$，反之无解。

我们从 $2^0 \to 2^{29}$ 贪心，比如现在在考虑 $2^i$ 这一位，如果 $n \operatorname{and} 2^i=0$（$n$ 不含这一位） ，那显然是没那个必要考虑的。如果是 $1$ 的话，那么用 $tmp$ 来表示用 $a$ 数组中 $2^0 \sim 2^{i - 1}$ 能拼出来多少个 $2^i$。如果 $tmp \ge 1$ 的话，直接 $tmp \gets tmp - 1$ 就行了，表示消耗一个；如果 $tmp = 0$，那我们显然只能借助于 $2^i \sim 2^{29}$ 来完成这个操作了，这时可以暴力的用 $j$ 从 $i \to 29$ 枚举，找到第一个 $c_j \ge 1$ 的，把 $c_j \gets c_j - 1$，然后把 $c_i \sim c_{j - 1}$ 都增加 $1$，同时 $ans$ 要累加上 $j - i$（从 $2^j$ 除到 $2^i$ 就是 $j - i$ 次），别忘了 $tmp$ 要变成 $0$。最后按照 $tmp$ 的定义，当我们考虑 $2^{i+1}$ 时，$2^i$ 显然是要累加进去的，所以 $tmp = \frac{tmp + c_i}{2}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL; 
const int M = 100005;
LL n, m, a[M], ans;
int c[50];
int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--)
	{
		ans = 0;
		LL sum = 0;
		memset(c, 0, sizeof c); 
		cin >> n >> m;
		for(int i = 1; i <= m; i++) cin >> a[i];
		for(int i = 1; i <= m; i++)
		{
			int k = 0;
			sum += a[i];
			while(a[i] > 1) k++, a[i] >>= 1;
			c[k]++;
		}
		if(sum < n)
		{
			cout << "-1\n";
			continue;
		}
		LL tmp = 0;
		for(int i = 0; i < 30; i++)
		{
			if(n >> i & 1) tmp--;
			if(tmp < 0)
			{
				int j;
				for(j = i; !c[j]; j++) c[j] = 1;
				c[j]--;
				ans += j - i;
				tmp = 0; 
			}
			tmp = tmp + c[i] >> 1;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

