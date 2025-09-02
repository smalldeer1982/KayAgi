# Drazil and His Happy Friends

## 题目描述

Drazil has many friends. Some of them are happy and some of them are unhappy. Drazil wants to make all his friends become happy. So he invented the following plan.

There are $ n $ boys and $ m $ girls among his friends. Let's number them from $ 0 $ to $ n-1 $ and $ 0 $ to $ m-1 $ separately. In $ i $ -th day, Drazil invites ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/0da6b9a3d02abb66f05faf59011ade551446e858.png)-th boy and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/b11adea5506a14de900c875f929fb5324c4eb93f.png)-th girl to have dinner together (as Drazil is programmer, $ i $ starts from $ 0 $ ). If one of those two people is happy, the other one will also become happy. Otherwise, those two people remain in their states. Once a person becomes happy (or if he/she was happy originally), he stays happy forever.

Drazil wants to know whether he can use this plan to make all his friends become happy at some moment.

## 说明/提示

By ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/bc360a33d2d53f2f08a31e2a137952fc77466359.png) we define the remainder of integer division of $ i $ by $ k $ .

In first sample case:

- On the 0-th day, Drazil invites 0-th boy and 0-th girl. Because 0-th girl is happy at the beginning, 0-th boy become happy at this day.
- On the 1-st day, Drazil invites 1-st boy and 1-st girl. They are both unhappy, so nothing changes at this day.
- On the 2-nd day, Drazil invites 0-th boy and 2-nd girl. Because 0-th boy is already happy he makes 2-nd girl become happy at this day.
- On the 3-rd day, Drazil invites 1-st boy and 0-th girl. 0-th girl is happy, so she makes 1-st boy happy.
- On the 4-th day, Drazil invites 0-th boy and 1-st girl. 0-th boy is happy, so he makes the 1-st girl happy. So, all friends become happy at this moment.

## 样例 #1

### 输入

```
2 3
0
1 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 4
1 0
1 2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
2 3
1 0
1 1
```

### 输出

```
Yes
```

# 题解

## 作者：Dry_ice (赞：4)

~~本蒟蒻~~第 $4$ 篇题解，望管理给过。

~~一道极水的模拟题~~

## 思路：暴力 + GCD

由于每次第 $i$ 次是第 $i$ % $n$ 名男生和第 $i$ % $m$ 名女生一块 $happy$，所以时间复杂度为 $O(n*m)$ ，直接模拟就行了。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
template<typename TYPE>
inline void in(TYPE&x) { //快读正数
	x=0;
	char c=getchar();
	for(; c<'0'||c>'9'; c=getchar());
	for(; c>='0'&&c<='9'; x=(x<<3)+(x<<1)+(c^48),c=getchar());
}
int n,m,a;
int b,g;
int x[10050]= {0},y[10050]= {0},tmp[10050]= {0};
int main() {
	int s=0;
	in(n),in(m);
	in(b);
	for(int i=0; i<b; ++i)in(a),x[a]=1;
	in(g);
	for(int i=0; i<g; ++i)in(a),y[a]=1;
	memset(tmp,0,sizeof tmp);
	int G=std::__gcd(n,m); //algorithm里的gcd
	if(G==1) {
		if(b+g>=1)printf("Yes\n");
		else printf("No\n");
		return 0;
	}
	for(int i=0; i<n; ++i)if(x[i])tmp[i%G]=1;
	for(int i=0; i<m; ++i)if(y[i])tmp[i%G]=1;
	s=0;
	for(int i=0; i<G; ++i)
		s+=tmp[i];
	if(s==G) printf("Yes\n");
	else printf("No\n");
	return 0;
}
```

## The end. Thanks.

~~（走过路过一定赞过啊~~

---

## 作者：Carotrl (赞：3)

非常水。

如果数据放大的话，应该是数论题，但这么小的数据，纯模拟就可以AC了哎。

用桶表示男女生的状态，一共枚举$2×lcm(n,m)$次，每次更新状态，最后扫描判断即可。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int t,n,m,a[105],b[105],nl,ml,x;
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d",&nl);for(int i=1;i<=nl;i++)scanf("%d",&x),a[x]=1;
	scanf("%d",&ml);for(int i=1;i<=ml;i++)scanf("%d",&x),b[x]=1;
	int s=2*n*m/__gcd(n,m);
	for(int i=0;i<s;i++){
		int n1=i%n,n2=i%m;
		if(a[n1]||b[n2])a[n1]=b[n2]=1;
	}
	int ans=1;
	for(int i=0;i<n;i++)ans*=a[i];
	for(int i=0;i<m;i++)ans*=b[i];
	printf(ans?"Yes\n":"No\n");
}
```


---

## 作者：XL4453 (赞：2)

### 解题思路：

虽然看出来直接暴力就能通过，但是出题本意应该是数论解法吧，这里给出 $O(n+m)$ 解法。

由于序列无限，那么序列中只要 $(i-j)\bmod \gcd(n,m) =0$ 的位置都是能够相遇的，这个时候发现（其实这是个要背上的结论吧）将所有的可能碰到一起的人染色，其实就是序列中每隔 $\gcd (n,m)$ 染一次色。

证明可以先将序列分成 $\dfrac{n}{\gcd(n,m)}$ 和 $\dfrac{m}{\gcd(n,m)}$ 个块，然后通过互质的两长度全都能够相遇证明块内相遇，比较简单。

那么由这个结论就可以将两个序列分组，然后组内只要有任何一个乐观的人就会传染到所有的人，直接根据组判断即可。

计算 $\gcd(n,m)$ 复杂度 $O(\log (n+m))$，分组复杂度 $O(n+m)$，最后判断 $O(\log (n+m))$，总复杂度 $O(n,m)$。

[2021.12.9 日最优解](https://www.luogu.com.cn/record/64591355)

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int a[105],b[105],n,m,cur[105],GCD,now,x;
int gcd(int a,int b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%d%d",&n,&m);
	GCD=gcd(n,m);
	scanf("%d",&now);for(int i=1;i<=now;i++)scanf("%d",&x),a[x]=1;
	scanf("%d",&now);for(int i=1;i<=now;i++)scanf("%d",&x),b[x]=1;
	for(int u=0;u<GCD;u++){
		for(int i=u;i<=n;i+=GCD)cur[u]|=a[i];
		for(int i=u;i<=m;i+=GCD)cur[u]|=b[i];
	}
	int flag=1;
	for(int i=0;i<GCD;i++)
	flag&=cur[i];
	if(flag)printf("Yes\n");
	else printf("No\n");
	return 0;
}
```


---

## 作者：Miraik (赞：2)

水题，直接模拟即可。

因为每次是第 $i\bmod n$ 位男生和第 $i\bmod m$ 位女生共进晚餐，所以只需要模拟$2\times n\times m$次，即可保证模拟完所有情况，而不需要考虑循环节的问题。

然后用桶统计，扫描判断即可。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,m,b;
bool f[105],g[105],ans;
int main(){
	n=read(),m=read();
	b=read();
	while(b--)f[read()]=1;
	b=read();
	while(b--)g[read()]=1;
	for(int i=1;i<=n*m*2;i++)
		if(f[i%n]||g[i%m])
		    f[i%n]=g[i%m]=1;
	ans=1;
	for(int i=0;i<n;i++)
		if(!f[i]){
		    ans=0;break;
		}
	for(int i=0;i<m;i++)
		if(!g[i]){
		    ans=0;break;
		}
	puts(ans?"YES":"NO");
	return 0;
}
```


---

## 作者：Sun_wtup (赞：1)

# Drazil and His Happy Friends 题解
[题目传送](https://www.luogu.com.cn/problem/CF515B)
## 题意
有 $n$ 个男生和 $m$ 个女生，他们中有一些人最初是乐观的，有一些不乐观，在第 $i$ 天会有第 $(i \bmod n)$ 号男生和第 $(i \bmod m)$ 号女生共进晚餐，如果这两个人中有一个人是乐观的，两个人就都会变乐观，反之就都不乐观，问能否在若干天后使所有人乐观。
## 分析与思路
根据数据范围可知，这不是一道纯数学，是可以进行一定模拟的。那我们就看怎么模拟。题目说能否在若干天使所有人快乐，如果我们能找到这个“若干”，就可以直接模拟了。因为男生和女生是 $(i \bmod n)$ 或 $(i \bmod m)$ 得到的，所以我们很自然的想到 $ \operatorname{lcm}(n,m) $，但如果只循环到这里，你就会发现，诶，他过不了。因为跑一遍 $\operatorname{lcm}$ 覆盖不了所有情况，我们是想从一定的小范围的情况中涵盖所有情况，所以我们要全面一些，而只跑一遍就会有原本能相遇两个人相遇不了，就不是所有情况，而 $\times 2$ 就涵盖了所有情况，换句话说，$2\times \operatorname{lcm}(n,m)$ 之后的就都是循环的之前的情况了。然后模拟就好了。

温馨提示：$\operatorname{lcm}(n,m)=n\times m \div \gcd(n,m)$，求 $\gcd$ 有 C++ 的函数可以直接调用 `int gcd=__gcd(n,m);`，但能不能在大型比赛中使用就不一定了~~咱也不知道，咱也不敢问~~。
## Code
``` cpp
#include <bits/stdc++.h>
using namespace std;
bool a[105],b[105];
int main()
{
//  freopen("Luogu_P_1877.cpp.in","r",stdin);
//  freopen("Luogu_P_1877.cpp.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    int hn,hm;
    cin>>hn;
    int t;
    for(int i=1;i<=hn;i++){
    	cin>>t;
    	a[t]=1;
	}
	cin>>hm;
	for(int i=1;i<=hm;i++){
		cin>>t;
		b[t]=1;
	}
	int maxn=2*n*m/__gcd(n,m);
	for(int i=0;i<maxn;i++){
		if(a[i%n]|b[i%m]){
			a[i%n]=1;
			b[i%m]=1;
		}
	}
	bool fl=1,fla=1;
	for(int i=0;i<n;i++){
		if(!a[i])fl=0;
	}
	for(int i=0;i<m;i++){
		if(!b[i])fla=0;
	}
	if(fl & fla)cout<<"Yes";
	else cout<<"No";
//  fclose(stdin);
//  fclose(stdout);
    return 0;
}
```
本蒟蒻水平有限，如有不周之处，希望能原谅。

---

## 作者：qiliu (赞：1)

[题面传送门。](https://www.luogu.com.cn/problem/CF515B)


------------

### 思路。

一道很水的暴力题，似乎有数论解法。但因为数据范围小，可以先尝试用暴力解，本文提供的解法是暴力解法。

~~才不是因为数论做法没想出来。~~

因为数据范围较小，可以暴力枚举每一天，实时更新每一位朋友乐观或不乐观。

可以证明， $\operatorname{lcm(n,m)} \times 2$ 的天数即可求出是否能让朋友们 happy 起来。



------------

### 证明过程

为了规范括号使用问题，我们暂且设变量  $lcmm$ $=\operatorname{lcm(n,m)}$。

因为，$lcmm \equiv 0 \pmod n $ 且 $ lcmm \equiv 0 \pmod m $。~~这是显而易见的~~。

所以 $(  lcmm \ + 1 ) \equiv 1 \pmod n$且$( lcmm \ + 1 ) \equiv 1 \pmod m$。~~这更是显而易见的~~。

以此类推，在遍历到第一次 $\operatorname{lcm(n,m)}$ 后，所有的 $i \bmod  n$ 及 $ i \bmod m$ 都应该在之前出现过。（这很好证明。）

至于为什么 $ \times 2 $，是因为我们需要在第一批悲观朋友乐观之后，再让他们让更多悲观朋友乐观起来。因为 $ n , m $ 都小于等于一百且保证乐观朋友数量不为零，所以至少跑两遍就能让乐观朋友（如果满足条件）覆盖整个区间。

------------

### 以下为AC代码。

```c
//别问为什么这么多句号。
#include<bits/stdc++.h>
#define int long long
#define DEBUG(x) cerr<<#x<<'='<<x<<endl
using namespace std;
int boy[1005];
int girl[1005];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int n,m;
    cin>>n>>m;
	int b;
	cin>>b;
	for(int i=0;i<b;i++)
	{
		int x;
		cin>>x;
		boy[x]=1;
	}
	int g;
	cin>>g;
	for(int i=0;i<g;i++)
	{
		int y;
		cin>>y;
		girl[y]=1;
	}
	int lcmm=n/_gcd(n,m)*m;
	for(int i=0;i<=lcmm*2;i++)
	{
		if(boy[i%n]||girl[i%m])
		{
			boy[i%n]=girl[i%m]=1;
		}
	}
	for(int i=0;i<n;i++)
	{
		if(boy[i]==0)
		{
			cout<<"No";
			return 0;
		}
	}
	for(int i=0;i<m;i++)
	{
		if(girl[i]==0)
		{
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes";
    //fclose(stdin);
    //fclose(stdout);
	return 0;
}

```


---

## 作者：hubin1 (赞：0)

# Drazil and His Happy Friends

## 题目大意
Drazil 有许多朋友，有 $n$ 个男生和 $m$ 个女生。Drazil 决定第 $i$ 天邀请第 $i \bmod n$ 号男生和第 $i \bmod m$ 号女生共进晚餐。Drazil 觉得，乐观是可以传染的，即她认为如果有人是乐观的，那么与他（她）共进晚餐的另一个人也会变得乐观。现在的问题是，Drazil 想知道，这种办法能否在若干天后使得她的所有朋友都会变得乐观。

## 思路
1. 从题意和数据范围上来看，这道题可以直接模拟。
2. 模拟首先要确定范围。由题意得，这个共进晚餐的活动每 $\operatorname{lcm}(m, n)$ 循环一次，因此我们可以遍历这个区间。但是有一个问题：如果枚举到某一对男女，他们都是悲伤的，但后来其中有一个变成乐观，但在下一次循环时，实际上他们都会开朗，但程序会认为他们悲伤。因此要遍历 $2 \times \operatorname{lcm}(m, n)$ 次。这个 $2$ 指的是当男或女为开朗的两种情况，从而包含全部情况。
3. 由于数据范围不大，可以直接枚举到 $2 \times n \times m$。
4. 剩下的根据题意模拟即可

## Code
``` cpp
#include<bits/stdc++.h>
using namespace std;

#define debug(x) cout<<#x<<" = "<<x<<endl

const int MAX=100+10;

bool boy[MAX],girl[MAX];//乐观、悲伤

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int boy_h,girl_h;//男、女乐观的人数
	scanf("%d",&boy_h);
	for(int i=1;i<=boy_h;i++)
	{
		int id;
		scanf("%d",&id);
		boy[id]=1;//乐观标记为1
	}
	scanf("%d",&girl_h);
	for(int i=1;i<=girl_h;i++)
	{
		int id;
		scanf("%d",&id);
		girl[id]=1;
	}
	for(int i=0;i<=n*m*2;i++)//枚举，也可以枚举到 lcm(n,m)*2
	{
		if(boy[i%n]|girl[i%m])
		{
			boy[i%n]=1;
			girl[i%m]=1;
		}
		// cout<<i%n<<" "<<i%m<<endl;
	}
	for(int i=0;i<n;i++)//有一个悲伤就失败
	{
		if(!boy[i])
		{
			cout<<"No"<<endl;
			return 0;
		}
	}
	for(int i=0;i<m;i++)
	{
		if(!girl[i])
		{
			cout<<"No"<<endl;
			return 0;
		}
	}

	cout<<"Yes"<<endl;
	
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF515B)。

~~从并查集的 $\text{tag}$ 找过来的，结果发现可以直接模拟。~~

## Solution

每一次第 $i \bmod m$ 名男生与第 $j \bmod m$ 名女生共进晚餐，所以可知只需要 $2 \times \text{lcm}(n,m)$ 次，之后的操作都是重复的。

那么复杂度为 $O(\text{lcm}(n,m))$，显然这个东西小于 $10^4$，时间绰绰有余。

[Code](https://codeforces.com/problemset/submission/515/212613540)

（编号为 $0$ 到 $n+m-1$）

---

## 作者：yingkeqian9217 (赞：0)

## 前言

这题本身也不是很难，但本蒟蒻用的是并查集的做法，个人认为比较简便，可以供大家理解。

## 题目大意

Drazil 有许多朋友，有一些人是乐观的，而其他人则不然（未必就是悲观的），她决定帮助她的朋友们。她的朋友，有 $n$ 个男生和 $m$ 个女生，编号分别是 $0$ ~ $n-1$ 和 $0$ ~ $m-1$。Drazil 决定第 $i$ 天邀请第 （$i \bmod n$） 号男生和第 $j$（$=i \mod m$） 号女生共进晚餐，（$i=0,1,……$）。

Drazil 觉得，乐观是可以传染的，即她认为如果有人是乐观的，那么与他（她）共进晚餐的另一个人也会变得乐观（当然，如果两个人都是乐观的或者都不是乐观的，则保持原样），而且这种状态也会保持下去。现在的问题是，Drazil 想知道，这种办法能否在若干天后使得她的所有朋友都会变得乐观。

## 分析

首先，看到“乐观是可以传染的”以及后面的话时，应该就很容易想到将可以相互“传染”的人放在同一连通块里。而再仔细一想，这不就是并查集吗？

那么，怎么样的男女生之间可以相互“传染”呢？显然，题目中已经告诉我们了，当他们的编号 $x$，$y$ 间存在一个  $i$（即文中的 $i$）使得  $x=i \bmod n$，$y=j\bmod m$。

可以很容易发现，$i$ 存在周期，这个周期就是 $\text{lcm}(n,m)$， 那我们不妨把它看作 $n\times m$。

于是，寻找这一对可以相互“传染”的男女生就很简单了。我们只要枚举 $i\in(1,n\times m)$，从而寻找合适的 $x$，$y$ 进行并查集的合并操作即可。

不过，题目问我们的是，能否通过几个乐观的人将乐观传染给所有人，那我们也很简单，只要将记录每个连通块是否有乐观的人即可，可以用一个数组 ```hap``` 记录。

当然，这时还有最后一个问题要解决，那就是男女生的编号，我们知道并查集的 ```father``` 数组只能开一维，所以我们不妨把男生就设为 $0$ ~ $n-1$，将女生往后放，即设为 $n$ ~ $n+m-1$。

最后并查集不要忘记将 ```father``` 初始化为自己哦，祝你AC愉快~

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=12900001;
int n,m,p,fa[maxn];//变量名与题中类似，fa即并查集父亲数组
bool hap[maxn];//记录是否乐观
int find(int x){//并查集
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
signed main(){
	scanf("%d%d%d",&n,&m,&p);
	while(p--){//p为男生乐观人数
		int x;
		scanf("%d",&x);
		hap[x]=1;//将他标记为乐观的
	}
	scanf("%d",&p);
	while(p--){//此时的p为女生乐观人数
		int x;
		scanf("%d",&x);
		hap[n+x]=1;//注意女生要+n，下同
	}
	for(int i=0;i<n+m;i++) fa[i]=i;//初始化，注意要枚举n+m，下同
	for(int i=0;i<n*m;i++)
	 fa[find(i%n)]=find(n+i%m);//题目精髓，合并对应男女生
	for(int i=0;i<n+m;i++)
	 if(hap[find(i)]) continue;
	 else if(hap[i]) hap[find(i)]=1;//如果他自己是乐观的，那么将祖先标记为乐观，相当于以他所在的连通块全部可以变为乐观
	for(int i=0;i<n+m;i++)
	 if(!hap[find(i)]){//只要有一个连通块不成立，就永远无法使乐观传染至所有人
	 	printf("No");
	 	return 0;
	 }
	printf("Yes\n");//注意还要输出Yes
	return 0;
}
```

### 后记

据说乐观是可以传染的捏，你们的点赞就是把你们的乐观传染到我身上最好的方式呀！

---

## 作者：pref_ctrl27 (赞：0)

[链接](https://www.luogu.com.cn/problem/CF515B)

思路：使用并查集，如果男生和女生可能一起吃饭（即存在一个$ i $，使 $ i \bmod n = i \bmod m$），则将他们合并，表示能互相影响。

只要一个集合中有一个人乐观，那么，这个集合的所有元素都是乐观的。所以，只要更新集合的根节点是否乐观即可。

如何判断男生和女生可能一起吃饭呢？

设第 $i$ 个男生和第 $j$ 个女生可能一起吃饭，则

$$ xn+i=ym+j $$
$$ xn-ym=j-i $$

显然，$ xn-ym $ 是 $ \gcd(n,m) $ 的倍数，则 $ j-i $ 也应是 $ \gcd(n,m) $ 的倍数，由此即可判断男生和女生是否能一起吃饭。

代码：

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
template <typename _tp>
inline _tp in(_tp&x){
	char ch=getchar(),sgn=0;x=0;
	while(ch^'-'&&!isdigit(ch))ch=getchar();if(ch=='-')ch=getchar(),sgn=1;
	while(isdigit(ch))x=x*10+ch-'0',ch=getchar();if(sgn)x=-x;return x;
}
bool t[205];
int fa[205];
int ab(int n){
	return n<0?-n:n;
}
int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}
int rt(int u){
	if(u==fa[u]) return u;
	return fa[u]=rt(fa[u]);
}
int main(){
	memset(t,false,sizeof(t));
	int n,m,x,y,tot;in(n),in(m);tot=n+m;
	int tmp;
	in(x);
	while(x--) in(tmp),t[tmp]=true;
	in(y);
	while(y--) in(tmp),t[tmp+n]=true;
	for(int i=0;i<tot;++i){
		fa[i]=i;
	}
	tmp=gcd(n,m);
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			if(ab(i-j)%tmp==0){
				int ri=rt(i);
				int rj=rt(j+n);
				fa[rj]=ri;
				if(t[rj]) t[ri]=true;
			}
		}
	}
	bool flag=true;
	for(int i=0;i<tot;++i){
		if(!t[rt(i)]){
			puts("No");
			flag=false;
			break;
		}
	}
	if(flag) puts("Yes");
	return 0;
}
```

---

## 作者：ZJMZJM (赞：0)

直接暴力+gcd

水题
```
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>//头文件
#define For(k,i,j) for(int k=i;k<=j;k++)//For循环
#define MAXN 110//数据特别小
#pragma GCC optimize(4)//O4
using namespace std;
int boy[MAXN],girl[MAXN];
int gcd(int a,int b)
{
	if(b>a) swap(a,b);
	return b==0?a:gcd(b,a%b);
}
int get_lcm(int n,int m)
{
	return n*m/gcd(n,m);
}//GCD
inline int read()
{
    char ch;
    int res=1;
    while((ch=getchar())<'0'||ch>'9') if(ch=='-') res=-1;
    res*=ch-48;
    while((ch=getchar())>='0'&&ch<='9')
        res=res*10+ch-48;
    return res;
}
int main()
{
	int n=read(),m=read();
	int num_boy=read();
	For(i,1,num_boy)
	{
		int ID=read();
		boy[ID]=1;
	}
	int num_girl=read();
	For(i,1,num_girl)
	{
		int ID=read();
		girl[ID]=1;
	}//标记
	int max=2*get_lcm(n,m);
	For(i,0,max-1)
	{
		int id_b=i%n,id_g=i%m;
		if(boy[id_b]||girl[id_g])
			boy[id_b]=girl[id_g]=1;
	}
	int wa=0;
	For(i,0,n-1)
		if(!boy[i])
			wa=1;
	For(i,0,m-1)
		if(!girl[i])
			wa=1;//判断
	if(wa)
		printf("No\n");
	else
		printf("Yes\n");//输出
	return 0;
}

```

---

