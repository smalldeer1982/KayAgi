# Fridge Lockers

## 题目描述

## 题意翻译

现在有$n$人，每人都拥有1个冰箱。现提供$m$条铁链，每条铁链可以连接两个冰箱，且只有这两个冰箱的主人可以解锁这条铁链。

只有冰箱上所有铁链都被解锁后，才能打开这个冰箱，如果一个冰箱被铁链加固后只有它的主人可以独自打开它，那么我们称这个冰箱是“私有的”。

另外，如果只有2个冰箱，那么无论有多少条铁链，两个冰箱都不是“私有的”，因为这两个人都可以独自打开对方的冰箱。

在图例中有4个冰箱和5条铁链，所有冰箱都是“私有的”。1号冰箱的主人可以解锁连接1-2和连接1-4的铁链，1号冰箱只能被它的主人独自打开，或者被2号和4号同时打开。

每个冰箱都有一个重量，记为$a_1,a_2,a_3,\ldots,a_n$。如果要给u号和v号冰箱用铁链加固，需要花费$a_u+a_v$元。两个冰箱之间可以有多条铁链加固。

请求出，在将$m$条铁链全部被使用后，所有冰箱是否可能均为“私有的”，如果可能，那么求出最小花费是多少。

## 样例 #1

### 输入

```
3
4 4
1 1 1 1
3 1
1 2 3
3 3
1 2 3
```

### 输出

```
8
1 2
4 3
3 2
4 1
-1
12
3 2
1 2
3 1```

# 题解

## 作者：Little_x_starTYJ (赞：6)

### 思路
题目告诉我们 $n$ 不能小于 $3$。

当 $m < n$ 时：不可能使每个点的度数都大于 $2$。

否则，就是有解的情况，我们不难想出，要满足题意，只能构成一个环，也就是 花费的点权之和的两倍。

CODE：
```cpp
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
        int n, m, res = 0;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
        int a;
			scanf("%d", &a);
			res += a;
		}
		res *= 2;
		if (n < 3 || m < n) {
			puts("-1");
			continue;
		}
		printf("%d\n", res);
		for (int i = 1; i < n; i++) printf("%d %d\n", i, i + 1);
		printf("%d 1\n", n);
	}
	return 0;
```
完结撒花~

---

## 作者：zhangzirui66 (赞：2)

**思路**

如果 $ n < 3 $ 则肯定会构造失败。

当 $ m < n $ 时，无法做到每个点的度数都大于或等于 $ 2 $。

反之，要想满足题意，就必须形成一个环，花费为冰箱总重量的两倍。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, a;
int main(){
    cin >> t;
    while(t --){
        cin >> n >> m;
        int sum = 0;
        for(int i = 1; i <= n; i ++){
            cin >> a;
            sum += a;//求出重量总和
        }
        sum *= 2;
        if(n < 3 || m < n){//无法形成
            puts("-1");
            continue;
        }
        printf("%d\n", sum);
        for(int i = 1; i < n; i ++) printf("%d %d\n", i, i + 1);
        printf("%d 1\n", n);//形成环
    }
    return 0;
}
```

---

## 作者：zhangzehao1 (赞：1)

### 思路

对于 $n$ 个点，要保证“私有”且花费最小，根据题意，让每个点度数都为 $2$，构成一个简单环即可。

### 分析

当有解时，最小花费即为点权和的两倍，输出最小和的两倍，再输出当前点 $i$ 与下一个点 $i+1$，最后首尾相接，输出 $n$ 与 $1$ 即可。

当无解时，有两种情况：

1. $m<n$ 的时候，此时不可能用 $m$ 条边使每个点度数为 $2$，形成的图要么不连通，要么是一棵树。

2. $n<3$ 时，题目已经给出了当 $n$ 等于 $2$ 时，不存在合法情况，当 $n$ 等于 $1$ 时，显然也不是合法的。

对于这两种情况，特判出来直接输出 $-1$ 即可。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
int T;
int main()
{
 	cin>>T;
 	while(T--)
	{
		int m,n,ans=0;//点权初值为0
		cin>>n>>m; 
		for(int i=1;i<=n;i++)
		{
			int a;
			cin>>a;
			ans+=a;	
		}
		if(n<3||m<n)
		{
			cout<<"-1"<<endl;
			continue;	
		}//特判
		cout<<ans*2<<endl;
		for(int i=1;i<n;i++)
		    cout<<i<<" "<<i+1<<endl;//输出环
		cout<<n<<" 1"<<endl;//首尾相接		
	} 
 	return 0;
}
```

---

## 作者：xh001 (赞：1)

# 题意
首先给定一个整数 $t$ 表示有 $t$ 组数据，每组数据包含两个数 $n$，$m$ 和一个长度为 $n$ 的序列 $a$，$n$ 为序列中数的个数，$m$ 为需要连的边数，序列 $a$ 为每个点的点权，连边需要花费两点的点权之和，求在连了 $m$ 条边且每个点度数大于一后的最小花费。
# 思路
首先进行分类讨论：

题面直接告诉了我们 $n$ 不能小于 $3$，所以直接特判即可。

当 $m<n$ 时：不可能使每个点的度数都大于 $2$，直接特判。

当 $m=n$ 时：这是唯一有解的情况，只需让所有点形成一个环即可，花费为点权之和乘 $2$。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//好习惯。 
ll t,n,m,ans,a;
inline ll read()
{
	ll k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
int main()
{
	t=read();
	while(t--)
	{
		ans=0;//多测清数据好习惯。 
		n=read();
		m=read();
		for(ll i=1;i<=n;i++)
		{
			a=read();
			ans+=a;
		}
		if(n==2 || m<n)//特判。 
		{
			cout<<-1<<endl;
			continue;
		}
		cout<<ans*2<<endl;
		for(ll i=1;i<n;i++) cout<<i<<' '<<i+1<<endl;
		cout<<n<<' '<<1<<endl;
	}
	return 0;
}
```


---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1255B)

------------
# 思路：
根据题意，每个点至少连两条边，$2$ 点时无解。那么就是说 $N$ 个点 $N$ 条边连完之后的权值都是一样，我们就考虑形成最大环的连法，对于多出来的边，肯定是连权值最小的边，题目给了说，两点之间可以连任意多的边。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int T,n,k;
struct fridge{
    int id,val;
}a[N];
int cmp(fridge a,fridge b){
    return a.val<b.val;
}
signed main(){
    cin>>T;
    while(T--){
        cin>>n>>k;
        int mi=0,ans=0;
        for(int i=1;i<=n;i++){
            cin>>a[i].val;
            a[i].id=i;
        }
        sort(a+1,a+1+n,cmp);
        if(k<n||n==2){
            cout<<-1<<endl;
            continue;
        }
        for(int i=1;i<=n;i++){
            ans+=a[i].val*2;
        }
        ans+=(k-n)*(a[1].val+a[2].val);
        cout<<ans<<endl;
        for(int i=1;i<n;i++){
            cout<<i<<" "<<i+1<<endl;
        }
        cout<<n<<" "<<1<<endl;
        for(int i=1;i<=k-n;i++){
            cout<<a[1].id<<" "<<a[2].id<<endl;
        }
    }
    return 0;
}
```
完结撒花~

---

## 作者：Genshin_ZFYX (赞：0)

我们先考虑哪些情况是无解的。

数据范围没有 $n=1$ 的情况，无需考虑。

$n=2$ 时，两人都可以独自打开对方的冰箱，无解。

$m<n$ 时，不能让每个冰箱连着的锁链数量都一样，无解。

其他情况均可连成一个环，最小花费即为每个冰箱的重量之和乘二。

AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define I return
#define love 0
#define FIRESTARS ;
#define endl '\n'
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;cin>>t;
    while(t--)
    {
    	int n,m,sum=0;cin>>n>>m;
    	for(int i=1;i<=n;i++)
    	{
    		int x;cin>>x;
    		sum+=x;
		}
		if(n<3||m<n)cout<<-1<<endl;
		else
		{
			cout<<sum*2<<endl;
			for(int i=1;i<n;i++)
			cout<<i<<" "<<i+1<<endl;
			cout<<n<<" 1"<<endl;
		}
	}
	I love FIRESTARS
}
```

---

## 作者：seika27 (赞：0)

### 分析
进行分类讨论：
当 $n<3$ 时：由题面可知不成立。

当 $m<n$ 时：显然不可能使每个点连的边数都大于 $2$。

当 $m=n$ 时：是本题唯一有解的情况，将所有点连成一个简单环。为了使花费最小，就让每个点都有两条边与其相连。那么，其花费为所有边权的 $2$ 倍。

### code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define cin std::cin
#define cout std::cout 
int T;
signed main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		int res=0;
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			res+=x;
		}
		if(n<3||m<n)			//无解
		{
			cout<<"-1\n";
			continue;
		}
		res<<=1;			//输出要二倍
		cout<<res;
		cout<<"\n";
		for(int i=1;i<n;i++)cout<<i<<' '<<i+1<<'\n';
		cout<<n<<" 1\n";
	}
	return 0;
}
```



---

## 作者：xxboyxx (赞：0)

### 思路

如果一个冰箱被大于等于两条铁链所链接，那么它就是“私有的”，为什么呢，因为就算与其相连接的其中一条铁链被解锁，但还有一条铁链未解锁，那么冰箱就是“私有的”，为了使花费最小，让每个冰箱都有两条铁链链接就行啦。其实就是**简单环**。下图为结点数为 $6$ 的简单环。

![](https://cdn.luogu.com.cn/upload/image_hosting/yecdcon5.png)

可以发现，每个冰箱都有两条铁链链接，那么计算花费时，从冰箱的角度来看就是每个冰箱的重量被计算两次（与该冰箱链接的两条铁链都会计算一次），那求最小花费的式子就是

$$\LARGE 2 \sum_{i=1}^{n} a_i$$

每个冰箱与下一个冰箱相链接，也就是第 $i$ 个冰箱与第 $i+1$ 个冰箱链接，特别的，第 $n$ 个冰箱与第 $1$ 个冰箱链接。当然有很多的链接方式，但只要是简单环，就是正确的。

### 注意

如果只有 $2$ 个冰箱，那么无论有多少条铁链，两个冰箱都不是“私有的”，因为这两个人都可以独自打开对方的冰箱。

以上是题目的原话，所以当 $n=2$ 时，应该输出`-1`。

因为简单环的特性，边的数量与结点的数量相等，所以当 $n<m$ 时，也就是铁链数量小于冰箱数量，是无解的，应该输出`-1`，我们也可以证明简单环已经是铁链最少的情况。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,s=0;
int main()
{
	cin>>t;
	while (t--)//T组数据 
	{
		int n,m,x;
		s=0;//初始化 
		cin>>n>>m;
		for (int i=1;i<=n;i++)//在输入时求和 
		{
			cin>>x;
			s+=x;
		}
		if (m<n || n<=2)//判断是否为两种无解的情况 
		{//这个是不能写在12行之前的，因为如果没有读入完，将会影响下一组数据 
			cout<<-1<<'\n';
			continue;
		}
		cout<<s*2<<'\n';//输出结果 
		for (int i=1;i<=n;i++)
		{
			if (i<n)
				cout<<i<<' '<<i+1<<'\n';//与下一个冰箱相链接 
			else
				cout<<n<<' '<<1<<'\n';//第n个冰箱与第1冰箱链接 
		}
	}
	return 0;
}
```

---

## 作者：tuanzi_pal (赞：0)

### 思路
由题面可知：当 $n = 2$ 时，两人可以互相开锁，故输出 $-1$ 。

当 $m < n$ 时，不可能使每个冰箱均被锁两次，无法构成私有，故也输出 $-1$ 。

否则，就是有解的，只需要求出每个冰箱加固价格的 $2$ 倍即可。

code ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	ios_base::sync_with_stdio(false);cout.tie(0);
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		int cnt=0;
		for(int i=1,x=0;i<=n;i++) cin>>x,cnt+=x;
		if(n<3||m<n){
			cout<<"-1\n";
			continue;
		}
		cout<<cnt*2<<"\n";
		for(int i=1;i<n;i++) cout<<i<<" "<<i+1<<"\n";
		cout<<n<<" 1\n";
	}
	return 0;
}
```
完结撒花 ~

---

## 作者：Berd__ (赞：0)

**~~极其水的一道题~~**

### 思路
大家都知道，如果只有两个冰箱，无论有多少条铁链，两个人都可以互相开锁（不会是私有的），故如果 $n=2$ 就必定输出 $-1$。

而如果 $m<n$，每个冰箱没法被锁两次（不连通）或成为一颗树，所以如果 $m<n$ 也输出 $-1$。

只有在 $m=n$ 的情况下，才能构成一个简单环，输出两倍的点权之和（每个冰箱加固的价格的两倍）以及简单环的构造即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,m,cnt;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n>>m;
		c=0;
		for(int j=1,x=0;j<=n;j++) cin>>x,c+=x;
		if(n<3||m<n) cout<<"-1"<<endl,continue;
		cout<<c+c<<endl;
		for(int k=1;k<n;k++) cout<<k<<" "<<k+1<<endl;
		cout<<n<<" "<<1<<endl;
	}
	return 0;
}
```

---

## 作者：lemon_qwq (赞：0)

分类讨论即可：

1. $n=2$ 时两个人可以互相开，故输出 $-1$。


2. $m\le n$ 时，图只可能是一棵树，或者不连通，故输出 $-1$。

3. $m=n$ 时，让所有点形成一个简单环即可，是最优解，最小花费为两倍的点权之和。

综上，如果 $m=n$，输出两倍的点权之和以及简单环的构造即可，否则输出 $-1$。

完结撒花！

---

## 作者：寒鸽儿 (赞：0)

我们得出的结论是:  
若$n=2$则一定无解。两个人可以互相开。  
在$n \geqslant 3$的情况下:  
#### 1.一个结点为private当且仅当其度数$\geqslant 2$.  
若度数为$0$则任意其他人可以打开。  
若度数为$1$则这条边的另一个端点的主人可以开。  
若度数大于$1$没有其他人能开。  
#### 2.若$m < n$则无解。  
在这种情况下要么不连通要么是一棵树。树的情况叶子结点肯定不是private.  
#### 3.若$m = n$必然有解。  
在这种情况下可以构成一个简单环。  
#### 4.简单环为$m = n$的最优解  
显然每个点对答案的贡献为其度数\*权值。  
由于每个点为private,度数$\geqslant 2$,而简单环的每个点的度数$=2$,因而不会有比简单环更小的解。  
```cpp
#include <cstdio>

using namespace std;

int main() {
	int t, n, m, ans, tmp;
	scanf("%d", &t);
	while(t--) {
		ans = 0;
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &tmp);
			ans += tmp;
		}
		ans <<= 1;
		if(n == 2 || m < n) {
			printf("-1\n");
			continue;
		}
		printf("%d\n", ans);
		for(int i = 1; i < n; ++i) printf("%d %d\n", i, i + 1);
		printf("%d %d\n", n, 1);
	}
	return 0;
}
```


---

