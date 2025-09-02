# New Year and Three Musketeers

## 题目描述

Do you know the story about the three musketeers? Anyway, you must help them now.

Richelimakieu is a cardinal in the city of Bearis. He found three brave warriors and called them the three musketeers. Athos has strength $ a $ , Borthos strength $ b $ , and Caramis has strength $ c $ .

The year 2015 is almost over and there are still $ n $ criminals to be defeated. The $ i $ -th criminal has strength $ t_{i} $ . It's hard to defeat strong criminals — maybe musketeers will have to fight together to achieve it.

Richelimakieu will coordinate musketeers' actions. In each hour each musketeer can either do nothing or be assigned to one criminal. Two or three musketeers can be assigned to the same criminal and then their strengths are summed up. A criminal can be defeated in exactly one hour (also if two or three musketeers fight him). Richelimakieu can't allow the situation where a criminal has strength bigger than the sum of strengths of musketeers fighting him — a criminal would win then!

In other words, there are three ways to defeat a criminal.

- A musketeer of the strength $ x $ in one hour can defeat a criminal of the strength not greater than $ x $ . So, for example Athos in one hour can defeat criminal $ i $ only if $ t_{i}<=a $ .
- Two musketeers can fight together and in one hour defeat a criminal of the strength not greater than the sum of strengths of these two musketeers. So, for example Athos and Caramis in one hour can defeat criminal $ i $ only if $ t_{i}<=a+c $ . Note that the third remaining musketeer can either do nothing or fight some other criminal.
- Similarly, all three musketeers can fight together and in one hour defeat a criminal of the strength not greater than the sum of musketeers' strengths, i.e. $ t_{i}<=a+b+c $ .

Richelimakieu doesn't want musketeers to fight during the New Year's Eve. Thus, he must coordinate their actions in order to minimize the number of hours till all criminals will be defeated.

Find the minimum number of hours to defeat all criminals. If musketeers can't defeat them all then print "-1" (without the quotes) instead.

## 说明/提示

In the first sample Athos has strength $ 10 $ , Borthos $ 20 $ , and Caramis $ 30 $ . They can defeat all criminals in two hours:

- Borthos and Caramis should together fight a criminal with strength $ 50 $ . In the same hour Athos can fight one of four criminals with strength $ 1 $ .
- There are three criminals left, each with strength $ 1 $ . Each musketeer can fight one criminal in the second hour.

In the second sample all three musketeers must together fight a criminal with strength $ 51 $ . It takes one hour. In the second hour they can fight separately, each with one criminal. In the third hour one criminal is left and any of musketeers can fight him.

## 样例 #1

### 输入

```
5
10 20 30
1 1 1 1 50
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30
1 1 1 1 51
```

### 输出

```
3
```

## 样例 #3

### 输入

```
7
30 20 10
34 19 50 33 88 15 20
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
6
10 5 10
10 9 5 25 20 5
```

### 输出

```
3
```

# 题解

## 作者：int08 (赞：1)

## 前言
这题有一种每次打 XCPC 都会碰到一道的贪心分讨题的美。
# Solution
先特判全局 $\max$ 大于 $a+b+c$ 时候输出 $-1$。

发现只有正好三个人攻击，不多不少，猜测贪心做法，于是先将 $a,b,c$ 从大到小排序。

这三个人组合起来的攻击力有大有小，而且排序之后大部分的顺序是**固定的**，具体来说是 $a+b+c>a+b>a+c>\max(b+c,a)\ge \min(b+c,a)>b>c$。

而每只怪物既可以被正好大于等于它的组合方式消灭，也可以被攻击力更大的组合方式消灭，于是从大到小考虑怪物的攻击力。

1. 有一些怪物攻击力大于 $a+b$，显然只能用 $a+b+c$ 消灭，浪费一轮。
2. 接下来会有一些只能用 $a+b$ 消灭的，每一个也需要浪费一轮，但是每一轮可以让 $c$ 单独杀一个，贪心的杀去小于等于 $c$ 中最大的。
3. 接下来会有一些只能用 $a+c$ 消灭的，每一个也需要浪费一轮，但是每一轮可以让 $b$ 单独杀一个，贪心的杀去小于等于 $b$ 中最大的。

剩下的没法用上面的方案拆了，因为不知道 $b+c,a$ 的大小关系。

1. 假设 $b+c>a$，会有一些只能用 $b+c$ 消灭的，类似上文那样贪心，然后剩下 $x$ 个只能用 $a$ 杀的，$y$ 个能用 $a,b$ 杀的，$z$ 个能用 $a,b,c$ 杀的，与此同时，$x$ 过多时，可以把一部分 $a$ 杀改为 $b+c$ 杀。
2. 假设 $b+c\le a$，已经剩下 $x$ 个只能用 $a$ 杀的，$y$ 个能用 $a,b$ 杀的，$z$ 个能用 $a,b,c$ 杀的，与此同时，$x$ 过多时，只能把小于等于 $b+c$ 的部分将 $a$ 杀改为 $b+c$ 杀。

现在变成这样一个问题：$A,B,C$ 三个盒子里各有 $x,y,z$ 个球，$C$ 盒子里的球可以随意放进 $B,A$ 盒子，$B$ 盒子里的球可以随意放进 $A$ 盒子中，至多 $w$ 个 $A$ 盒子的球可以变成 $B,C$ 盒子中各一个球，最小化 $\max(x,y,z)$。

考虑~~诶是不是可以二分~~贪心。

如果 $z>y$，先匀一下。

然后如果 $y>x$，答案是 $\max(\lceil\frac{x+y}{2}\rceil,\lceil\frac{x+y+x}{3}\rceil)$。

否则根据 $d$ 来尽量地匀平，最后答案为 $\max(x,y)$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,t,mx,ans,i;
multiset<int> s;
int main()
{
	cin>>n>>a>>b>>c;
	if(c>b) swap(c,b);
	if(b>a) swap(b,a);
	if(c>b) swap(c,b);
	for(i=1;i<=n;i++) cin>>t,mx=max(mx,t),s.insert(t);
	if(mx>a+b+c) cout<<-1,exit(0);
	while(s.size()&&*(--s.end())>a+b) ans++,s.erase(--s.end());
	while(s.size()&&*(--s.end())>a+c)
	{
		ans++,s.erase(--s.end());
		if(s.size()&&s.upper_bound(c)!=s.begin()) s.erase(--s.upper_bound(c));
	}
	while(s.size()&&*(--s.end())>max(a,b+c))
	{
		ans++,s.erase(--s.end());
		if(s.size()&&s.upper_bound(b)!=s.begin()) s.erase(--s.upper_bound(b));
	}
	if(b+c>a)
	{
		while(s.size()&&*(--s.end())>a)
		{
			ans++,s.erase(--s.end());
			if(s.size()&&s.upper_bound(a)!=s.begin()) s.erase(--s.upper_bound(a));
		}
	}
	int ad=0,bd=0,cd=0,kz=0;
	for(auto x:s) if(x>b) ad++;
	else if(x>c) bd++;
	else cd++;
	if(b+c>a) kz=ad;
	else
	{
		for(auto x:s) if(x>b&&x<=b+c) kz++;
	}
	if(cd>bd)
	{
		int del=(cd-bd)/2;cd-=del,bd+=del;
	}
	if(bd>=ad) ans+=max((bd+ad+1)/2,(bd+cd+ad+2)/3);
	else
	{
		int del=min((ad-bd)/2,kz);
		ad-=del,bd+=del;
		ans+=max(ad,bd);
	}
	cout<<ans;
}
```
# The End.

---

## 作者：__stick (赞：1)


##  题意

 三个不同战斗值的 jc，战斗值分别为 $a,b,c(a \le b\le c)$，$n$ 个罪犯每个有一个防御值，只有一个罪犯的防御值不大于对他发起进攻警察防御值的和才能被消灭，每秒钟 jc 可以发动一次攻击，问最少多久消灭所有罪犯。

## 思路

首先这个问题应该是个贪心，但是每次贪心的情况很复杂，如果从小到大依次攻击的话就很难办，于是考虑从大到小进行贪心。

每次取出最大的罪犯设战斗值为 $mx$，然后进行分类讨论，大概这么几种情况：

1. $mx\le a$ 直接暴力每个 jc 找个最大的能干掉的干掉即可。

2. $a\le mx\le b$ 就也是贪心的干掉每一个能干掉的，这样一定比 $a,b$ 联合更好，因为有可能一次干掉 $3$ 个。
3. $b\le mx \le c$ 这时就要讨论一下了，看看 $a,b$ 能不能自己干掉一个，如果可以，就去干掉，如果不能两个联合起来干掉这个最大值。
4. $ c\le mx \le a+b$   $a,b$ 就一起干掉这个最大值即可，反正这个最大值是一定要干掉的，就这次干掉即可。
5. $a+b\le mx\le a+c$ 就让 $a,c$ 干掉它即可。
6. $a+c\le mx \le b+c$ 同上。
7. $b+c\le mx \le a+b+c$ 直接三个齐上。
8. 无解。

这个每次干掉最大的能干掉的操作可以通过在 set 里面找前驱来实现，于是就能做到 $O(n\log n)$ 的复杂度。

## 代码
各位就参考一下，写的比较丑。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
#define mp make_pair
const int mod=1e9+7;
const int MAXN=1e6+10;

int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n,a,b,c;cin>>n>>a>>b>>c;
	vi v={a,b,c};
	vi d(n+1);
	for(int i=1;i<=n;i++)cin>>d[i];
	multiset<int>s(d.begin()+1,d.end());
	sort(v.begin(),v.end());
	int ans=0;
	auto fight=[&](int x)->int
	{
		auto ii=s.upper_bound(x);
		if(ii!=s.begin())
		{
			ii--;
			int w=*ii;
			s.erase(ii);
			return w;
		}	
		return 0;
	};
	auto ispre=[&](int x)
	{
		return s.upper_bound(x)==s.begin();
	};
	for(int i=1;!s.empty()&&i<=n;i++)
	{
		int mmax=*s.rbegin();
	//	cerr<<s.size()<<'\n';
		ans++;
		if(mmax<=v[0])
		{
			ans+=(s.size()+2)/3-1;
			break;
		}
		if(mmax<=v[1])
		{
			for(int j=0;j<3;j++)fight(v[j]);
		}
		else if(mmax<=v[2])
		{
			int w;
			if(w=fight(v[0]))
			{
				if(fight(v[1]))
				{
					fight(v[2]);
				}
				else 
				{
					s.insert(w);
					fight(v[0]+v[1]),fight(v[2]);
				}
			}
			else 
			{
				fight(v[0]+v[1]),fight(v[2]);
			}
		}
		else
		{
			if(mmax<=v[0]+v[1])
			{
				fight(v[0]+v[1]),fight(v[2]);
			}
			else if(mmax<=v[0]+v[2])
			{
				fight(v[0]+v[2]),fight(v[1]);
			}
			else if(mmax<=v[1]+v[2])
			{
				fight(v[1]+v[2]),fight(v[0]);
			}
			else if(mmax<=v[0]+v[1]+v[2])fight(v[0]+v[1]+v[2]);
			else 
			{
				cout<<-1;
				return 0;
			}
		}
	}
	cout<<ans;
 	return 0;
}
```


---

## 作者：shinkuu (赞：0)

为什么现有题解都是带 $\log$ 的呢……

先钦定 $a\le b\le c$。容易发现对于一个 $t_i$，实际上可能最优的决策不会很多。

- 对于 $t_i\le b$，一定只用一个数满足。
- 对于 $c<t_i\le b+c$，一定用两个。
- 对于 $t_i>b+c$，只能用三个。
- 对于 $a+b<t_i\le c$，一定只用 $c$。
- 剩下的可能用 $a+b$ 可能用 $c$。

同时，对于只能用一个/两个的，可行决策有包含关系。比如，如果可以用 $a$，就一定能用 $b$；如果能用 $a+c$，就一定能用 $b+c$。

再考虑一个问题：如果知道了分别用 $a,b,c,ab,ac,bc,abc$ 操作数量，怎么求出最小操作次数。首先 $abc$ 一定单独做。$ab,ac,bc$ 两两不能一起做,所以这里需要 $ab+ac+bc$。剩下 $a,b,c$，分别可以和 $bc,ac,ab$ 一起做。剩下需要 $\max(a-bc,b-ac,c-ab,0)$ 次。

但是事实上还可以用上面的包含关系调整。不过注意到上面的式子是上个差值的形式，所以把一个 $ab$ 变成 $ac$ 和把一个 $b$ 变成 $c$ 是等价的。于是只需要考虑 $a,b,c$ 的调整。

容易发现，令 $a-bc=x,b-ac=y,c-ab=z$。这相当于可以在 $x$ 中取任意个给 $y$，$y$ 给 $z$ 同理。所以答案就是 $\max(z,\left\lceil\frac{y+z}2\right\rceil,\left\lceil\frac{x+y+z}3\right\rceil)$。

于是回到原问题，只需要枚举 $5$ 种情况中的最后一种选多少个 $c$，多少个 $ab$ 即可。复杂度 $O(n)$。同时应该是题解区中实际码长最短的做法。

code：

```cpp
int n,m;
void Yorushika(){
	int A,B,C;
	read(n,A,B,C);
	if(A>B)swap(A,B);
	if(A>C)swap(A,C);
	if(B>C)swap(B,C);
	int a=0,b=0,c=0,ab=0,ac=0,bc=0,abc=0,cnt=0,ans=n;
	rep(i,1,n){
		int x;read(x);
		if(x>A+B+C){
			puts("-1");
			return;
		}
		if(x<=A)a++;
		else if(x<=B)b++;
		else if(x>C){
			if(x<=A+B)ab++;
			else if(x<=A+C)ac++;
			else if(x<=B+C)bc++;
			else abc++;
		}else{
			if(x>A+B) c++;
			else cnt++;
		}
	}
	c+=cnt;
	rep(i,0,cnt){
		ans=min(ans,abc+ab+ac+bc+max({c-ab,(b+c-ac-ab+1)/2,(a+b+c-ab-ac-bc+2)/3,0}));
		c--,ab++;
	}
	printf("%d\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

