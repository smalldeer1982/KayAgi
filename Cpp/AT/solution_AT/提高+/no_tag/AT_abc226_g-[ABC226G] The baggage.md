# [ABC226G] The baggage

## 题目描述

有质量为 $1 \sim 5$ 的重物，质量为 $i(1 \leq i \leq 5)$ 的重物有 $A_i$ 个；同时有可搬运的最大质量不超过 $i(1 \leq i \leq 5)$ 的人 $B_i$ 个。 问是否存在一种分配方式，使所有重物均可被一次性搬运。

## 样例 #1

### 输入

```
3
5 1 0 0 1
0 0 0 2 1
0 3 0 0 0
0 0 2 0 0
10000000000000000 0 0 0 0
0 0 0 0 2000000000000000```

### 输出

```
Yes
No
Yes```

# 题解

## 作者：OIerYang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc226_g)

## 贪心

从 $5\to 1$ 去贪，分类讨论。

- $5$ 重量的货物只能由 $5$ 重量的工人来搬。
- $4$ 重量的货物可以由 $5$ 和 $4$ 重量的工人来搬。
- $3$ 重量的货物可以由 $5，4，3$ 重量的工人来搬。
- $2$ 重量的货物可以由 $5，4，3，2$ 重量的工人来搬。注意 $5$ 和 $4$ 的工人可以搬两个。
- $1$ 重量的货物只要把剩下的都加起来就好了。

  注意优先级是从大到小。

CODE:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[6],b[6];
bool check(){
	if(a[5]>b[5])return 0;//5不够直接输出No
	b[5]-=a[5];
	//4
	if(a[4]<=b[4])b[4]-=a[4];
	else{
		a[4]-=b[4];b[4]=0;
		if(a[4]<=b[5])b[1]+=a[4],b[5]-=a[4];//4不够5来凑
		else return 0;
	}
	//3
	if(a[3]<=b[3])b[3]-=a[3];
	else{
		a[3]-=b[3];b[3]=0;
		if(a[3]<=b[5])b[2]+=a[3],b[5]-=a[3];
		else{
			a[3]-=b[5];b[2]+=b[5];b[5]=0;
			if(a[3]<=b[4])b[1]+=a[3],b[4]-=a[3];
			else return 0;
		}
		//3不够5,4来凑
	}
	if(a[2]<=b[2])b[2]-=a[2];
	else{
		a[2]-=b[2];b[2]=0;
		if(a[2]<=b[5]*2){
			if(a[2]%2==1){
				b[5]-=a[2]/2;
				b[1]+=a[2]/2;
				b[5]--;
				b[3]++;
			}
			else{
				b[5]-=a[2]/2;
				b[1]+=a[2]/2;
			}
		}
		else{
			a[2]-=b[5]*2;b[1]+=b[5];b[5]=0;
			if(a[2]<=b[4]*2){
				if(a[2]&1){
					b[4]-=a[2]/2;
					b[4]--;
					b[2]++;
				}
				else{
					b[4]-=a[2]/2;
				}
			}
			else{
				a[2]-=b[4]*2;b[4]=0;
				if(a[2]<=b[3]){
					b[3]-=a[2];b[1]+=a[2];
				}
				else return 0;
			}
		}
		//2不够5,4,3来凑，注意5,4可以搬两个
	}
	int kkk=b[1]+b[2]*2+b[3]*3+b[4]*4+b[5]*5;
	if(a[1]>kkk)return 0;
	return 1;
	//最后把所有加起来判断1
}
void solve(){
	for(int i=1;i<=5;i++)cin>>a[i];
	for(int i=1;i<=5;i++)cin>>b[i];
	if(check())cout<<"Yes\n";
	else cout<<"No\n";
}
signed main(){
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：naoliaok_lovely (赞：2)

~~奇怪的翻译……~~

## 题目大意
有体积为 $i(1\le i\le5)$ 的物品和力量为 $j(1\le j\le5)$ 的人，分别为 $a_i$ 和 $b_j$ 个。力量为 $x$ 的人总共可以搬体积不超过 $x$ 的物品（物品不能切碎），问能否搬完。

# 贪心
提供一种简单直接的贪心思路：直接**按体积从大到小贪心**。

首先我们要明白贪心的目的：让每个人的力量发挥到极致，尽量不要出现浪费的情况。我们先把体积和力量相同的**抵消**掉，这一步正确性显然，方便我们后续的操作。

按照体积从大到小的意思就是指，按 $5,4,3,2,1$ 的顺序枚举物品，依次进行构造。正确性证明如下：（下列等式 $a=b-c$ 的含义是，体积为 $a$ 的物品让力量为 $b$ 的人去搬，然后这些人就变成了力量为 $c$ 的人）

- 体积为 $5$：如果存在，显然无解。（力量为 $5$ 的人已经被抵消掉了）
- 体积为 $4$：由于力量为 $4$ 的人已经没有了，于是构造 $4=5-1$。
- 体积为 $3$：我们有 $3=4-1$ 和 $3=5-2$，此时肯定优先选择后者。（因为这一步操作完之后，只会剩下体积为 $1,2$ 的物品。前者会剩下力量为 $1$ 的人，可能造成浪费；后者则必然不会浪费）
- 体积为 $2,1$：随便弄弄就好了。

## code
ps：为编码简单，例如当讨论到体积 $\le3$ 的物品时，力量为 $5$ 的人等效于 $2+3$。这时，不如主动提前分解，可以省去很多转移。注意，提前分解后要注意重新抵消。
```
#include<bits/stdc++.h>
using namespace std;
#define LL long long

LL a1,a2,a3,a4,a5, b1,b2,b3,b4,b5;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cin >> a1>>a2>>a3>>a4>>a5 >> b1>>b2>>b3>>b4>>b5;
		a1 < b1 ? (b1 -= a1, a1 = 0) : (a1 -= b1, b1 = 0),
		a2 < b2 ? (b2 -= a2, a2 = 0) : (a2 -= b2, b2 = 0),
		a3 < b3 ? (b3 -= a3, a3 = 0) : (a3 -= b3, b3 = 0),
		a4 < b4 ? (b4 -= a4, a4 = 0) : (a4 -= b4, b4 = 0),
		a5 < b5 ? (b5 -= a5, a5 = 0) : (a5 -= b5, b5 = 0);
		if(a5 || a4 > b5)
		{
			puts("No");
			continue;
		}
		b5 -= a4, b1 += a4;//体积为 4,5 的物品 
		LL k = min(a3, b5);
		a3 -= k, b5 -= k, b2 += k, b1 += b5, b2 += b5 << 1;//提前分解剩余 5 的人 
		if(a3 > b4) 
		{
			puts("No");
			continue;
		}
		b1 += a3 + b3, b2 += (b4 - a3 << 1) + b3;//处理 3 的物品，并分解力量为 3,4 的人 
		a1 < b1 ? (b1 -= a1, a1 = 0) : (a1 -= b1, b1 = 0),
		a2 < b2 ? (b2 -= a2, a2 = 0) : (a2 -= b2, b2 = 0);
		if(!a2 && a1 <= b2 << 1) puts("Yes");
		else puts("No");		
	}
	return 0;
}
```

---

## 作者：lovely_hyzhuo (赞：1)

这题昨天考试考了，场切了。

先看数据范围，$t\leq 2\times10^5$，可以发现，题目要我们在 $O(1)$ 内解决。

考虑贪心。

显然，如果能让该物品重量这个力量的搬运工去搬这个物块肯定是最优的，因为不会有被白费掉的力气。

然后就是如果搬不完就从 $5$ 开始，开始判看这个力气能不能搬完，然后把力气拆开，将 $b_{j-i}$ 加上剩下的搬运工数量。

然后没了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000010],b[1000010];
void solve()
{
	int n=5;
	int cnt=0,sum=0;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	for(int i=n;i>=1;i--)
	{
		if(b[i]>=a[i])
		{
			b[i]-=a[i];
			a[i]=0;
		}
		else
		{
			a[i]-=b[i];
			b[i]=0;
			for(int j=n;j>=i;j--)
			{
				if(b[j]==0)
					continue;
				int m=min(b[j],a[i]);
				a[i]-=m;
				b[j-i]+=m;
				b[j]-=m;
			} 
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=0)
		{
			cout<<"No\n";
			return;
		}
	}
	cout<<"Yes\n";
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```


---

## 作者：Genius_Star (赞：1)

### 题意：

有 $a_i$ 个重量为 $i$ 的包裹，和 $b_i$ 个力量为 $i$ 的人，每个人可以拿总重不超过自己力量上限的任意个包裹，问能否将所有的包裹都拿起。

### 思路：

不知道这题为什么放在 G 题，明明就是个极为简单的贪心。

分类讨论一下：

- 重量为 $5$ 的包裹：显然只有力量为 $5$ 的人才可以拿起。

- 重量为 $4$ 的包裹：力量为 $4$ 或者力量为 $5$ 的人都可以拿：

    1. 当力量为 $4$ 的人拿起后，可以节省一个力量为 $5$ 的人。（可以拿起 $[2,3]$，$[1,2,2]$，$[1,1,3]$，$[1,1,1,2]$，$[1,1,1,1,1]$ 这五种组合的物品）
    
    2. 当力量为 $5$ 的人拿起后，可以节省一个力量为 $4$ 的人，多出一个力量为 $1$ 的人。（可以拿起 $[1,1,3]$，$[1,2,2]$，$[1,1,1,2]$，$[1,1,1,1,1]$ 这四种组合的物品）
    
    - 综合上来看，先用力量 $4$ 的人拿更优秀。
    
- 重量为 $3$ 的包裹：力量为 $3$ 或者力量为 $4$ 和力量为 $5$ 的人都可以拿：

    1. 当力量为 $3$ 的人拿起后：
    
        1. 若节省一个力量为 $4$ 的人。（可以拿起 $[1,1,1,1]$，$[1,1,2]$，$[1,3]$，$[2,2]$，这四种组合的物品）
        
        2. 若节省一个力量为 $5$ 的人。（可以拿起 $[2,3]$，$[1,2,2]$，$[1,1,3]$，$[1,1,1,2]$，$[1,1,1,1,1]$ 这五种组合的物品）
     
    2. 当力量为 $4$ 的人拿起后（多出一个力量为 $1$ 的人）：
    
        1. 若节省一个力量为 $3$ 的人。（可以拿起 $[1,1,1,1]$，$[1,1,2]$ 这两种组合的物品）
        
        2. 若节省一个力量为 $5$ 的人。（可以拿起 $[1,2,3]$，$[1,1,2,2]$，$[1,1,1,3]$，$[1,1,1,1,2]$，$[1,1,1,1,1,1]$ 这五种组合的物品）  

    3. 当力量为 $5$ 的人拿起后（多出一个力量为 $2$ 的人）：
    
        1. 若节省一个力量为 $3$ 的人。（可以拿起 $[1,1,1,1,1]$，$[2,1,1,1]$，$[1,1,1,2]$，$[1,2,2]$ 这四种组合的物品）
        
        2. 若节省一个力量为 $4$ 的人。（可以拿起 $[1,1,1,1,1,1]$，$[2,1,1,1,1]$，$[1,1,1,1,2]$，$[2,1,1,2]$，$[1,1,1,3]$，$[2,1,3]$，$[1,1,2,2]$，$[2,2,2]$ 这八种组合的物品）
     
    - 综合上来看，先用力量 $5$ 的人拿更优秀，其次是用力量为 $3$ 的人，最后再用力量为 $4$ 的人。
    
- 重量为 $2$ 和 $1$ 的包裹的选择顺序都是按照力量从大到小。

注意到为了保证组合的正确，我们每次让力量为 $x$ 的人拿重量 $y$ 的包裹仅拿 $1$ 个，然后将它加入到 $x-y$ 力量的人中即可。

### 完整代码：

```cpp
// LUOGU_RID: 134786811
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=15;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n=5;
ll a[N],b[N];
void check(ll x,ll y){
	ll w=min(a[x],b[y]);
	a[x]-=w;
	b[y]-=w;
	b[y-x]+=w;
}
bool solve(){
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int i=1;i<=n;i++)
	  b[i]=read();
    check(5,5);
	check(4,4);
	check(4,5);
	check(3,5);
    check(3,3);
	check(3,4);
    for(int i=5;i>=2;i--) 
	  check(2,i);
    for(int i=5;i>=1;i--) 
	  check(1,i);
	for(int i=1;i<=n;i++)
	  if(a[i])
	    return 0;
	return 1;
}
int main(){
	T=read();
	while(T--){
		bool f=solve();
		if(f)
		  puts("Yes");
		else
		  puts("No");
	}
	return 0;
}
```


---

## 作者：Starry_Ocean (赞：0)

# 题解：AT_abc226_g [ABC226G] The baggage

- 参考文章：[ lovely_hyzhuo 的 《The baggage 题解》](https://www.luogu.com.cn/article/jamifm8f)。

#### 本题做法：贪心。

#### 主要思路 
梳理完题意，不难想到：**尽可能选择同等级的搬运工，如果无法满足，则按能力从上往下使用。**

时间复杂度 $O(T)$ 。

代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,a[10],b[10]; 
bool judge(){
	for(ll i = 5;i >= 1;--i){
		if(b[i]>=a[i]){
			b[i]-=a[i];
			a[i]=0;//如果同等级搬运工比物品多，用一些搬运工把物品搬完 
		}
		else {//如果同等级搬运工比物品少 ，调动更高等级的搬运工 
			a[i]-=b[i];
			b[i]=0; //同等级搬运工能搬就搬
			for(ll j = 5;j >= i;--j){//动用更高等级的搬运工 
				if(b[j]==0) continue;//没有搬运工了，跳出
				ll p = min(a[i],b[j]);
				/*
				比较搬运工数量与物品数量 
				两者都需要减去 p 
				注意：让 b[j-i] 加上 p (这是本题最难理解的部分，请仔细思考)
				*/ 
				a[i]-=p;
				b[j]-=p;
				b[j-i]+=p; 
			}
		} 
	}
	for(ll i = 1;i <= 5;++i){
		if(a[i]!=0) return false;
	}
	return true;
}
int main(){
	cin>>t;
	while(t--){
		for(ll i = 1;i <= 5;++i) cin>>a[i];
		for(ll i = 1;i <= 5;++i) cin>>b[i];
		if(judge()) cout << "Yes" << "\n";
		else cout << "No" << "\n";
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/172423575)

---

## 作者：CrTsIr400 (赞：0)

# ABC226G The Baggage

## 题意

有一些重量为 $1\sim 5$ 的包，有一些体力为 $1\sim 5$ 的人。一个人可以同时拿一些包。判断是否能够一次拿完。查询多次。

## 做法

这类贪心题一般要确定一个枚举顺序。

先做到“人选择包”的过程：**把体力和重量相同的人和包一起消掉**。这样可以保证前面操作过之后不会让后面的包没人能背。

我们感觉**越大的包越难被捡**，所以从**大到小**枚举能背它的人，这样的转移顺序**可以保证一个人拿多个这样大小的包**。

于是就做完了。哪这么麻烦。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
I T;
LL a[6],b[6];
bool pd(){
	fo(i,1,5)cin>>a[i];
	fo(i,1,5)cin>>b[i];
	fo(i,1,5){
		LL tmp=min(b[i],a[i]);
		a[i]-=tmp;
		b[i]-=tmp;}
	for(I i=5;i;--i){
		for(I c=5,d=c-i;d>=0;--c,--d){
			LL tmp=min(a[i],b[c]);
			b[c]-=tmp;a[i]-=tmp;
			b[d]+=tmp;}
		if(a[i])return 0;
	}return 1;
}
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;while(T--){
		puts(pd()?"Yes":"No");
	}
	return 0;}
```



---

