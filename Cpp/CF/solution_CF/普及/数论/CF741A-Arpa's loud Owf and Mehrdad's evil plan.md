# Arpa's loud Owf and Mehrdad's evil plan

## 题目描述

在小A的地盘上有许多可爱的妹子。
小A地盘上的所有人被从 $1$ 到 $n$ 编号，每个人都有一个暗恋的对象，第 $i$ 个人暗恋第 $crush_{i}$ 个人。
有一天，小A在宫殿的顶部大声喊着Owf，于是一个有趣的游戏在小A的地盘上开始了。规则如下。
该游戏有许多轮。如果编号为 $x$ 的人想要开始一轮游戏，他会对第 $crush_{x}$ 个人（ $x$ 暗恋的人 ）说"Oww...wwf"（有 $t$ 个w）。如果 $t > 1$，第 $crush_{x}$ 个人就会对第 $crush_{crush_{x}}$ 个人（$crush_{x}$暗恋的人）说"Oww...wwf"（有 $t - 1$ 个w）。直到有人听到"Owf"（$t = 1$）。这个人就是这一轮的Joon-Joon。不存在同时进行两轮游戏的情况。
为了使游戏更有意思，小M有一个邪恶的计划。他想找到最小的 $t$（$t >= 1$）使得对于每个人 $x$ 当第 $x$ 个人开始的一局游戏使 $y$ 成为了Joon-Joon，也使得由 $y$ 开始的一局游戏 $x$ 成为Joon-Joon。请为小M找这个最小的 $t$。
可能会有自恋的人。

## 样例 #1

### 输入

```
4
2 3 1 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
4 4 4 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
2 1 4 3
```

### 输出

```
1
```

# 题解

## 作者：zhang_kevin (赞：8)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF741A)

[CF题目传送门](http://codeforces.com/problemset/problem/741/A)

[更好的阅读体验？](https://www.luogu.com.cn/blog/zyc-Kevin-Luogu-blog/Solution-CF741A)

# 题目翻译

在小A的地盘上有许多可爱的妹子。小A的地盘上的所有人被从 $1$ 到 $n$ 编号，每个人都有一个暗恋的对象，第 $i$ 个人暗恋第 $crush_{i}$ 个人。
有一天，小A在宫殿的顶部大声喊着 `Owf` ，于是一个有趣的游戏在小A的地盘上开始了。

游戏规则如下：
该游戏有许多轮。如果编号为 $x$ 的人想要开始一轮游戏，他会对第 $crush_{x}$ 个人（ $x$ 暗恋的人 ）说 `Oww...wwf`（有 $t$ 个 `w` ）。如果 $t > 1$，第 $crush_{x}$ 个人就会对第 $crush_{crush_{x}}$ 个人（$crush_{x}$暗恋的人）说 `Oww...wwf`（有 $t - 1$ 个 `w`）。直到有人听到 `Owf`（$t = 1$）。这个人就是这一轮的 `Joon-Joon`。不存在同时进行两轮游戏的情况。

为了使游戏更有意思，小M有一个邪恶的计划。他想找到最小的 $t$（$t \geq 1$）使得对于每个人 $x$ 当第 $x$ 个人开始的一局游戏使 $y$ 成为了 `Joon-Joon`，也使得由 $y$ 开始的一局游戏 $x$ 成为 `Joon-Joon`。请为小M找这个最小的 $t$。
可能会有自恋的人。

这道题就是输入一个链表，先让你判断链表中的点是否都在某一个环中，让后让你求出所有环的点数的 `lcm`，对于偶数环在求 `lcm` 时将该偶数环的点数减半。
很多个人，一次给对应的人打电话。第 $t$ 个人就是第 $1$ 个人的 `Joon-Joon`。问 $t$ 最小为多少可以让每两个人互为 `Joon-Joon`。

# 解题思路

题目翻译太恶心了。这道题就是输入一个链表，先让你判断链表中的点是否都在某一个环中，让后让你求出所有环的点数的 `lcm`，对于偶数环在求 `lcm` 时将该偶数环的点数减半。

这样，题目就简单多了。注意开 `long long`！

# AC 代码

```cpp
#include<cstdio>
typedef long long ll;
ll gcd(ll a, ll b){
	if(!a){
		return b;
	}else if(!b){
		return a;
	}else{
		return gcd(b, a%b);
	}
}
ll lcm(ll a, ll b){
	return a / gcd(a, b) * b;
}
ll a[101], vis[101]; 
int main(){
	ll n;
	scanf("%lld", &n);
    for (int i = 1; i <= n; i++){
    	scanf("%lld", &a[i]);
	}
    ll ans = 1;
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            int Author_AK_IOI = i, Readers_AK_IOI = 0;
            while(!vis[Author_AK_IOI]){
                vis[Author_AK_IOI] = 1;
                Readers_AK_IOI++;
                Author_AK_IOI = a[Author_AK_IOI];
            }
            if(Author_AK_IOI != i){
                puts("-1");
                return 0;
            }
            if(!(Readers_AK_IOI%2)){
            	Readers_AK_IOI /= 2;
			}
            ans = lcm(ans, Readers_AK_IOI);
        }
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：封禁用户 (赞：4)

# 0.前言
本蒟蒻来发布此题的第一篇题解吧！！！

题目链接：[CF链接](http://codeforces.com/contest/741/problem/A)
 
题目大意：
给定 $n$ 个数字 $a[i]$，设定一个操作 $x=a[x]$;
找到一个最小的 $k$，要求：
执行 $k$ 次后，$x=a[x]$ ，使得 $x$ 的最终值是 $y$；
如果对 $y$ 也执行 $k$ 次，$y=a[y]$，$y$ 的最终值是 $x$。
# 1.解析
 $n$ 个数，每个数的选择只有一个！

对于 $a[i]$ 来说，可以连一条边使得 $i\to a[i]$。

从 $i$ 出去的边，最后需要指向自己。

按**边**来遍历，如果 $n$ 个数字能分成若干个“圆”就可以。

每个“圆”按各自的 $k$ 求出 LCM（最小公倍数）。因为 $x,y$ 可以互换，所以如果 $k$ 是 2 的倍数，要 $/2$。

# 2.code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 101001;
int a[N], u[N];
//通过GCD求LCM，这里是先求GCD
int gcd(int m,int n){
    int t;
    if(m<n){
    	t = n;
      n = m;
      m = t;
     }
    if(n == 0) return m;
    else return gcd(n,m % n);
}
//LCM
int lcm(int a,int b){
    return a/gcd(a,b) * b;
}
int main(){
    long long n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int ans = 1;
    for (int i = 1; i <= n; ++i){
        if (!u[i]){
            int t = i, k = 0;
            while(!u[t]){
                u[t] = 1;
                ++k;
                t = a[t];
            }
            if (t != i){
                ans = -1;
                break;
            }
            if (k % 2 == 0) k /= 2;
            ans = lcm(ans, k);
        }
    }
    cout << ans << endl;
    return 0;
}
```
也可以把 cin 改成 scanf 或者加一个 ios 更快，进行常数级优化，不过这都可以，看个人喜好。

参考资料：程序员进阶练习

---

## 作者：NotNaLocker (赞：1)

## CF741A Arpa's loud Owf and Mehrdad's evil plan 题解
### ~~几~~句闲话
题目翻译太太太良心了！

### 题目算法
- **GCD（最大公因数），LCM（最小公倍数）**

- **递归**

### 题目实现
模拟喊 Ow……f 的过程，用 next_crush 变量作为下一次找的暗恋对象，count 变量统计喊的次数，即 $t$。当找到重复的暗恋对象时，就用LCM取得 $t$ 的值，即判断此时的 $t$ 是否符合要求。

### 关键代码

```cpp
for(int i=1;i<=n;i++){  //遍历题中的y或x
		int next_crush=i,count=0;
		if(!f[i]){
			while(!f[next_crush]){
				f[next_crush]=1;  //标记为已访问
				count++;  //统计环
				next_crush=a[next_crush];  //继续找
			}
			if(count%2==0) count/=2;  //如果是偶数环就/2，因为x与y相互对应
			if(next_crush==i){  //可以匹配
				t=LCM(t,count);  //取最小公倍数
				continue;
			} 
			printf("-1\n");  //否则。。。
			return 0;
		} 
	}
```

## AC Coding

```cpp
#include<bits/stdc++.h>
#define ll long long  //注意！
using namespace std;
ll n,a[105],f[105],t=1;

ll GCD(ll x,ll y){
	if(!x) return y;
	else if(!y) return x;
	else return GCD(y,x%y);
}
ll LCM(ll x,ll y){
	return x/GCD(x,y)*y;
}
int main(){
	scanf("%lld",&n);  //注意！
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		int next_crush=i,count=0;
		if(!f[i]){
			while(!f[next_crush]){
				f[next_crush]=1;
				count++;
				next_crush=a[next_crush];
			}
			if(count%2==0) count/=2;
			if(next_crush==i){
				t=LCM(t,count);
				continue;
			} 
			printf("-1\n");
			return 0;
		} 
	}
	printf("%lld\n",t);
	return 0; 
} 
```
## Thanks for watching.

---

## 作者：Light_Star_RPmax_AFO (赞：0)

# 思路—— gcd & lcm

### 前言

[传送门](https://www.luogu.com.cn/problem/CF741A)

[博客](https://www.luogu.com.cn/blog/JJL0610666/cf741a-arpas-loud-owf-and-mehrdads-evil-plan-ti-xie-fan-hui-ti-mu)

## 讲解

首先做这题我们需要知道 **gcd** & **lcm**（最大公因数与最小公倍数）。

### gcd 最大公因数

在 _c++_ 库中有一个内置函数——**__gcd(x,y)** 那么其原理是什么呢？

答案是：[辗转相除法](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95/1647675?fromtitle=%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4%E6%B3%95&fromid=4625352&fr=aladdin)

看完了？那么代码如何实现呢？

用一个递归就可以完成。

```cpp
/*if(a<b)swap(a,b);
需要放在调用 gcd 函数的前面保证 a>b*/

int gcd(int a,int b){//实际参数需要满足 a>b。
	if(a%b==0)return b;
	else return gcd(b,a%b);
}
```

那么就实现了 **gcd**。

## lcm 最小公倍数

**lcm** 怎么去求呢？用辗转相除法？

这里就需要一点数学知识——**两个数** $a$,$b$

 $$lcm \times gcd = a \times b$$ 

有了这个知识实现 **lcm** 就很简单了。

$$lcm =a \times b \div gcd$$

```cpp 
int lcm(int a,int b){
	if(a<b)swap(a,b);
	return a/gcd(a,b)*b; 
} 
```

# 代码

```cpp
#include <bits/stdc++.h> 
#define int long long
using namespace std; 
int gcd(int a,int b){
	if(a<b)swap(a,b);
	if(a%b==0)return b;
	else return gcd(b,a%b);
}
int lcm(int a,int b){
	if(a<b)swap(a,b);
	return a/gcd(a,b)*b; 
} 
int n,a[110],ans=1;
bool u[110];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if (!u[i]){
            int temp=0,t=i;
            while(u[t]==0){
                u[t]=1;
                temp++;
                t=a[t];
            }
            if (t!=i){
                cout<<-1;
                return 0;
            }
            if (temp%2==0)temp/=2;
            ans=lcm(ans,temp);
        }
	}
	cout<<ans;
	return 0;
}
```





---

## 作者：大宝和小宝 (赞：0)

题意：给出 $n$ 个整数， 转换顺序 $a[x] \rightarrow a[a[x]]\rightarrow ....$ 一次规律继续进行下去 $t$ 次，若终点为 $y$，且满足 $y \rightarrow a[y] \rightarrow a[a[y]] \rightarrow ...$ 也进行 $t$ 次 得到终点为 $x$。就称之为一个环。要将数组里面分成若干个环，求最小的 $t$ 多大，不存在输出 $-1$。

------
代码如下：
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 105;
int a[maxn],mark[maxn];
 
LL gcd(LL a,LL b)
{
	if(b>a)
		swap(a,b);
	LL c;
	while(b>0)
	{
		c=a%b;	a=b;	b=c;
	}
	return a;
}
 
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		memset(mark,0,sizeof(mark));
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i]);
		LL ans=1;
		int flag=0;
		for(int i=1;i<=n;++i)
		{
			if(mark[i])
				continue;
			LL temp=1;		
			int y=a[i];
			mark[i]=1;
			while(y!=i){
				mark[y]=1;
				y=a[y];
				temp++;
				if(temp>n){//环不存在 
					flag=1;
					break;
				}
			}
			if(flag)
				break;
			if(temp%2==0)
				temp/=2;
			ans = ans/gcd(ans,temp)*temp;//求最小公倍数 
		}
		if(flag)
			printf("-1\n");
		else printf("%lld\n",ans);
	}
	return 0;
} 
```


---

