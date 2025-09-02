# The Humanoid

## 题目描述

有 $n$ 名宇航员，他们每个人有大小为 $a_i$ 的能量。一个初始具有 $h$ 单位能量的邪恶的人形生物来这里吸收宇航员们的能量。  

人型生物可以做以下三个动作：  
- 吸收一个能量值严格低于当前人型生物的宇航员。
- 将自身的能量值翻倍 ($\times 2$), 这个操作最多能进行两次。
- 将自身的能量值翻三倍 ($\times 3$), 这个操作最多能进行一次。

其中，当一名具有 $a_i$ 能量的宇航员被吸收时，这名宇航员消失，人型生物的能量增加 $\lfloor {a_i\over 2} \rfloor$。

请你帮他算一算，如果他用最佳方案进行操作，他最多能吸收几名宇航员的能量？

## 样例 #1

### 输入

```
8
4 1
2 1 8 9
3 3
6 2 60
4 5
5 1 100 5
3 2
38 6 3
1 1
12
4 6
12 12 36 100
4 1
2 1 1 15
3 5
15 1 13```

### 输出

```
4
3
3
3
0
4
4
3```

# 题解

## 作者：fast_photon (赞：10)

**0. 前言**  
没啥好说的。   

**1. 分析**  
首先，拿到题目之后，我们不难想到“先打好打的”。也就是说，对 $a$ 数组从小到大排序。原理很简单，$h$ 只会是单调不降的，如果当前大的能打那么小的肯定也能，不如优先打小的。  
然后就是三瓶药水。我们先考虑一个较为简单的情况：只有三瓶绿色药水。  
不难发现，如果一个人已经被吸收了，那么此时使用绿色药水可以带来更多的体力增益。也就是说，如果当前能打过，就不要立即使用药水。  
这就是一个简单的贪心思想：捡最小的打，打不过了就吃药继续打。  
接下来我们考虑原题的情况：有一瓶蓝色药水介入。  
其实这个问题和简化情况区别不大，唯一的区别就是“嗑药的时候需要抉择”。然而实际上，磕三瓶药的顺序只有三种情况，当顺序固定了之后，最优解也固定了。所以只需要枚举三种情况，分别是：最先和蓝药，中间喝蓝药，最后喝蓝药。  

**2. 代码**  
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>
#include<cstring>
#include<queue>
#include<algorithm> 
#define int long long //一定要开LL！！！

using namespace std;

int t, n, s, a[200005];

signed main() {
	cin >> t;
	while(t--) {
		cin >> n >> s;
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}  
		int ans = 0;
		sort(a, a + n); //从小到大排序以贪心
		for(int d = 0; d < 3; d++) {//枚举每一种情况，这里的 d 指的是还剩 d 瓶绿药的时候，如果有蓝药那么就喝蓝药
			int cnt2 = 2, cnt3 = 1;
			int x = s;         //这里记得每次都要重新初始化一下数据
			for(int i = 0; i < n; i++) {
				while(x <= a[i]) { //只要打不过就一直喝药，直到没有药为止
					if(cnt2 == d && cnt3 > 0) {
						cnt3--;
						x *= 3;
					}
					else if(cnt2 > 0) {
						cnt2--;
						x *= 2;
					}
					else break;
				}
				if(x <= a[i]) break; //这时候一定是药喝完了并且还是打不过
				x += a[i] / 2;
				ans = max(ans, i + 1); 
			}
		} 
		cout << ans << endl;
	}
}
```

---

## 作者：linyihdfj (赞：3)

## CF1759E The Humanoid
### 题目分析：
第一反应是一个贪心，也就是先用绿色再用蓝色，但是不对。

其实我们也可以发现关键就在于我们使用绿色和蓝色的顺序，而绿色和蓝色总共就只有三瓶，那么直接枚举使用的顺序然后暴力模拟一遍就好了。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e6+5;
int a[N];
string pre[3] = {"LLB","LBL","BLL"};
signed main(){
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int t;
	scanf("%lld",&t);
	while(t--){
		int n,h;scanf("%lld%lld",&n,&h);
		for(int i=1; i<=n; i++)	scanf("%lld",&a[i]);
		sort(a+1,a+n+1);
		int ans = 0;
		for(int opt=0; opt<3; opt++){
			int w = 0,now = 1;
			int g = h;
			while(w <= 3){
				while(a[now] < h && now <= n)	h = h + a[now] / 2,now++;
				if(w == 3){
					ans = max(ans,now);
					break;
				}	
				if(pre[opt][w] == 'L')	h = h * 2,++w;
				else	h = h * 3,++w;
			}
			h = g;
		}
		printf("%lld\n",ans-1);
	}
	return 0;
}
```

---

## 作者：wuyonghuming (赞：2)

### 分析：
本题可以使用搜索解决。

先贪心给所有数从小到大排序，因为坏人吸不了能量较小的宇航员，也更不可能吸收能量更多的宇航员，所以他吸收宇航员顺序是从小到大的。

接着进行搜索，应当计入 $4$ 个参数，分别是：剩下将能量乘 $2$ 的机会次数，剩下将能量乘 $3$ 的机会次数，当前的能量，和正在吸收的宇航员的下标。

如果搜索的时候遇到的宇航员能量比他多，如果还有加倍能量机会，他就必须使用，他应该尽量用较小的能量加倍方法，根据乘法原理，本题情况中，应该先吸收宇航员的能量后用加倍的方法，因为先加后乘应当比先乘后加来得大。比如 :$(a+b)×c=bc+ac>ac+b$ 。

然而这样一个一个搜过去肯定会超时，我们需要剪枝。如果存在一种方法用的加倍的机会比当前的少而且干掉的宇航员不比当前的少，说明这次搜索是没用的。
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
unsigned long long in(){unsigned long long a=0,f=1;char b=getchar();while(b<'0'||b>'9'){if(b=='-')f=-1;b=getchar();}while(b>=48&&b<=57){a=a*10+b-'0';b=getchar();}return a*f;}
void out(unsigned long long a){if(a<0){putchar('-');a*=-1;}if(a>9)out(a/10);putchar(a%10+48);}
long long n,h;//记得开long long
int s[200001],dp[11][11];//记录的是当前剩下a个*2,b个*3最多干掉的宇航员
void dfs(int a,int b,int x,long long y)//分别记录剩下*2,*3次数,当前宇航员和能量
{
	dp[a][b]=max(dp[a][b],x-1);
	if((a!=2||b!=1)&&(dp[a][b]<=dp[a+1][b]||dp[a][b]<=dp[a+1][b+1]||dp[a][b]<=dp[a+2][b+1]||dp[a][b]<=dp[a][b+1]||dp[a][b]<=dp[a+2][b]))//判断这个状态是否没用
		return;
	if(x>n)
		return;
	if(s[x]<y)
		dfs(a,b,x+1,y+s[x]/2);
	if(s[x]<y*2&&a>=1)
		dfs(a-1,b,x+1,y*2+s[x]/2);
	if(s[x]<y*3&&b>=1)
		dfs(a,b-1,x+1,y*3+s[x]/2);
	if(s[x]<y*4&&a>=2)
		dfs(a-2,b,x+1,y*4+s[x]/2);
	if(s[x]<y*6&&a>=1&&b>=1)
		dfs(a-1,b-1,x+1,y*6+s[x]/2);
	if(s[x]<y*12&&a>=2&&b>=1)
		dfs(a-2,b-1,x+1,y*12+s[x]/2); 
}
int main()
{
	int t=in();
	while(t--)
	{
		memset(dp,0,sizeof(dp));
		n=in(),h=in();
		for(int i=1;i<=n;i++)
			s[i]=in();
		sort(s+1,s+n+1);
		dfs(2,1,1,h);
		out(dp[0][0]);
		puts("");
	}
	return 0; 
}
```


---

## 作者：sandwave114514 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1759E)

题目大意


有 $n$ 名宇航员，他们每个人有大小为 $a_i$ 的能量。一个初始具有 $h$ 单位能量的妖怪来这里吸收宇航员们的能量。  

妖怪可以做以下三个动作：  

- 吸收一个能量值**严格**低于当前妖怪能量的宇航员。
- 嗑一瓶绿色的药，将自身的能量值翻倍，这种药它有两瓶。
- 嗑一瓶蓝色的药，将自身的能量值翻三倍，这种药它有一瓶。

其中，当一名具有 $a_i$ 能量的宇航员被吸收时，这名宇航员消失，妖怪的能量增加 $\lfloor {a_i\over 2} \rfloor$。

解题思路

同时我们可以先给数组排序，把严格低于当前妖怪能量的宇航员给吃掉，由于只有三种药，我们可以分成蓝绿绿，绿蓝绿，绿绿蓝三种情况，我们只要枚举以上三种情况就可以了。

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
void write(long long n,bool p){
	if(n<0){putchar('-');n=-n;}
	if(n==0){if(p)putchar('0');return;}
	write(n/10,0);putchar(n%10+'0');
}//快写 
long long t,n,h,now,num,ans,x,y,a[200010];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>h;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);//排序 
		ans=0;
		//蓝绿绿 
		now=h;num=0;x=2;y=1;//x绿色药水  y蓝色药水  now现在妖怪的能量 num 当前总能量值 
		for(int i=1;i<=n;i++){
			if(now>a[i]){now+=a[i]/2;num++;continue;}
			if(x==2 && y==1){ 
				now=now*3;y--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
			if(x==2 && y==0){ 
				now=now*2;x--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
			if(x==1 && y==0){
				now=now*2;x--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
		}
		ans=max(ans,num);//记答案 
		//绿蓝绿 
		now=h;num=0;x=2;y=1;
		for(int i=1;i<=n;i++){
			if(now>a[i]){now+=a[i]/2;num++;continue;}
			if(x==2 && y==1){ 
				now=now*2;x--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
			if(x==1 && y==1){
				now=now*3;y--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
			if(x==1 && y==0){
				now=now*2;x--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
		}
		ans=max(ans,num);
		//绿绿蓝
		now=h;num=0;x=2;y=1;
		for(int i=1;i<=n;i++){
			if(now>a[i]){now+=a[i]/2;num++;continue;}
			if(x==2 && y==1){
				now=now*2;x--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
			if(x==1 && y==1){
				now=now*2;x--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
			if(x==0 && y==1){
				now=now*3;y--;
				if(now>a[i]){now+=a[i]/2;num++;continue;}
			}
		}
		ans=max(ans,num);
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：honglan0301 (赞：0)

## 题意简述
有 $n$ 个宇航员，每人有 $a_i$ 单位的能量。有另一个坏人（他初始有 $h$ 单位的能量）来这里吸收能量，我们要求出他最多能吸收多少宇航员的能量。这个坏人可以做如下几件事：

- 吸收一个能量值比他低的宇航员的能量（若一个有 $a_i$ 能量的宇航员被吸收，则它直接消失，坏人的能量增加 $\lfloor {a_i\over 2} \rfloor$）。
- 将自己的能量值乘以 $2$ （这个操作最多能进行 $2$ 次）。
- 将自己的能量值乘以 $3$ （这个操作最多能进行 $1$ 次）。  

## 题目分析
看起来就像贪心。我们只需要让坏人最终的能量值变得尽量大，因为坏人能量越大，能吸收的宇航员个数越多。那么我们对坏人的操作分段，可以猜到尽可能早地吸收能量一定是更优的。  

证明也很简单，坏人进行的操作相当于一个包含加法和乘法的操作序列，类似  $+b_1,+b_2,\times b_3,...+b_m$, 那么根据乘法分配律，我们把乘法对结果的贡献拆成加法的贡献之和，可以知道任意一次 $+b_i$ 的贡献 $=b_i\times \prod b_j\ (j>i,c_j=\times) $, 显然尽可能将加法操作放在序列前面是优的。  

不过需要注意的是我们并不能因此直接把 $\times 3$ 放在乘法序列的后面，因为这会减少之前可进行的加法的数量，两者的贡献不方便直接比较。


于是只需要对 $a_i$ 从小到大排序（方便找当前可以被吸收的宇航员），枚举坏人对自己能量值 $\times2,\ \times3$ 的顺序，然后贪心地在乘法之前吸收所有可以被吸收的宇航员即可。  

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
long long t,n,h,ans,a[200005],b[5],ansnow,hnow,anow;//记得开long long 
bool cmp(int xx,int yy) {return xx<yy;}
void work()//贪心地吸收 
{
	while(hnow>a[anow])
	{
		ansnow++;
		hnow+=a[anow]/2;
		anow++;
	}
}
long long solve()//对于每个乘法序列计算答案 
{
	ansnow=0,hnow=h,anow=1;
	work();
	hnow*=b[1];
	work();
	hnow*=b[2];
	work();
	hnow*=b[3];
	work();
	return ansnow;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>h;
		ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+n+1,cmp);
		a[n+1]=1000000000000000000;
		b[1]=2;b[2]=2;b[3]=3;//枚举乘法序列 
		ans=max(ans,solve());
		b[1]=2;b[2]=3;b[3]=2;
		ans=max(ans,solve());
		b[1]=3;b[2]=2;b[3]=2;
		ans=max(ans,solve());
		cout<<ans<<endl;
	}
}
```


---

## 作者：xiaomuyun (赞：0)

- [Luogu 传送门](https://www.luogu.com.cn/problem/CF1759E)
- [CodeForces 传送门](https://codeforces.com/contest/1759/problem/E)

## 思路分析

我们先将 $a$ 从小到大排个序，这样方便后面的计算。

然后我们顺序遍历一遍这个数组，也就是按照 $a$ 从小到大遍历每一位宇航员。

现在我们遍历到了宇航员 $i$，如果我们能吃掉他，那么就吃掉他；如果我们吃不掉他，就要仔细分析一下，确保我们一定不能吃掉他：

- 我们能遍历到这个宇航员，说明所有满足 $a_j<a_i$ 的宇航员 $j$ 已经被吃掉了，所以我们已经吸收了从他们身上获取的所有能量，如果此时还是不能吃掉他的话，就考虑注射血清。

现在我们考虑一下注射血清的部分：

- 首先，如果我们发现遍历到的宇航员吃不掉了，就要在还有血清的情况下注射血清。没有血清的话直接统计答案即可。
- 其次，我们要考虑三支血清的注射顺序。考虑枚举蓝色血清在第几次注射血清的时候被注射，即枚举 `BGG`、`GBG` 和 `GGB`（`G` 和 `B` 分别指绿色和蓝色血清）这三种情况。对于每种情况，我们都遍历一遍 $a$ 数组，然后进行上面一开始的运算。然后统计三种情况的结果哪个更优即可。

## 代码实现

```cpp
#include<algorithm>
#include<cstdio>
#define int long long
using namespace std;
const int maxn=2e5+2;
int t,n,h,a[maxn];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&h);
		for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
		sort(a+1,a+1+n);
		int res=0;
		for(int t=1;t<=3;++t){//t表示蓝色血清在第t次注射的时候被注射
			int cnt=0,cur=1,ch=h;//cnt表示当前情况下的答案，cur表示即将注射第cur支血清，ch是临时变量，维护当前humanoid的力量
			for(int i=1;i<=n;++i){
				if(a[i]<ch) ch+=a[i]/2,++cnt;//如果能吃掉就直接吃掉
				else {
					while(a[i]>=ch){//如果吃不掉就不停地注射血清
						if(cur==t) ch*=3,++cur;//如果这次注射轮到注射蓝色血清了，就让ch乘3
						else if(cur<=3) ch*=2,++cur;//否则如果还没注射完的话，就注射绿色血清，让ch乘2
						else break;//血清注射完了，退出循环
					}
					if(a[i]>=ch) break;//如果依然不能吃掉就直接退出统计答案
					else ch+=a[i]/2,++cnt;//否则吃掉他
				}
			}
			res=max(cnt,res);//更新答案
		}
		printf("%lld\n",res);
	}
	return 0;
}
```

## 总结

一道有趣的贪心题。

---

