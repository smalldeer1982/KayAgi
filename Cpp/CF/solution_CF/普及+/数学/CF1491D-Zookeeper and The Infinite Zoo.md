# Zookeeper and The Infinite Zoo

## 题目描述

有一个无限图，其中有无数个节点，从 $1$ 开始标号。有一条从 $u$ 到 $u+v$ 的单向边，当且仅当 $u \&  v = v$ (这里的 $\&$ 指 [按位与](https://zh.wikipedia.org/wiki/位操作#按位与（AND）) 。除此以外没有其它边。

有 $q$ 个询问，询问是否存在一条从 $u$ 到 $v$ 的路径。

## 样例 #1

### 输入

```
5
1 4
3 6
1 6
6 2
5 5```

### 输出

```
YES
YES
NO
NO
YES```

# 题解

## 作者：XL4453 (赞：6)

### 解题思路:

看到 $u,v<2^{30}$ 的数据范围，图肯定是建不起来的，那么就考虑如何直接判断能否到达。

首先发现，对于任意的一个 $u>v$ 的数据，肯定是到达不了的，因为没有任何一条路是可以从大的点到小的点的。

然后就要把数字转二进制了，对于一个数，他所能到达的数都是比这个数大的，而且二进制位从后往前没有任何一个位置的后缀 1 的数目比他多的数。这还是比较显然的，因为在任意位置有一的位置加一都不可能使得这样的一个数的一的数目变多，也不可能使得后面的数位置上产生 1。

--------------

### 代码：

```
#include<cstdio>
using namespace std;
int n,x,y,cntx,cnty,flag;
int main(){
	scanf("%d",&n);
	while(n--){
		scanf("%d%d",&x,&y);
		if(x<=y){
			flag=1;cntx=cnty=0;
			for(int i=0;i<=31;i++){
				if(x&(1<<i))cntx++;
				if(y&(1<<i))cnty++;
				if(cntx<cnty){
					printf("NO\n");
					flag=0;
					break;
				}
			}
			if(flag)printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
```


---

## 作者：serverkiller (赞：6)

这里是官方题解。

显然加一个非 $2$ 的幂次等价于加若干个从大到小的 $2$ 的幂次，因此我们只需要考虑加的数是 $2$ 的幂的情况。

我们可以将一串 $11....10$ 调为 $00...01$。

可以发现，你一定是先将 $u$ 的最高位和 $v$ 调至一致，之后是次高位，……

于是先判断 $u$ 是否小于等于 $v$ ，然后贪心匹配 $u$ 和 $v$ 的 $1$ 位置看 $v$ 的每个 $1$ 是否都能对应到 $u$ 的**不低于**这个位置的 $1$ 即可。

---

## 作者：Cry_For_theMoon (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF1491D)

似乎2D总是偏爱找规律，纪念一下第一场赛时A掉ABCD的div2

观察一下，发现从点 $u$ 移动到某个点，相当于在 $u$ 的二进制表示上，找到一组 $0111...111$ 变成 $1000...000$. 举个例子，$u=5=(101)_2$ 时，可以变成 $(110)_2,(1001)_2$，当然得到的这两个数可以继续移动。于是我们发现了规律：

从右往左（此处右指低位）移动二进制上的 $1$，并且可以合并某些的连续的 $1$

考虑 $v$ 的二进制下的第一个为 $1$ 的位，记作第 $k$ 位（从这里开始全部指从右往左数），如果 $u$ 可以通过上述的操作到达 $v$，则 $u$ 的二进制下的 $1$ 到 $k$ 位必须有 $1$ 个 $1$，这样才能通过左移 $1$ 来匹配 $v$ 的第 $k$ 位。在满足上述条件的情况下，$v$ 的二进制下的第二个为 $1$ 的位 $k_2$ 位，必须满足在 $u$ 的二进制下的第 $1$ 到 $k_2$ 位至少有两个 $1$（第 $k$ 位匹配用掉一个，还剩不少于一个移到 $k_2$ 位与其匹配），以此类推.... 

所以显然得到一个结论：设数 $x$ 的二进制表示下，前 $i$ 位有 $f(x,i)$ 个 $1$，$u$ 能走到 $v$ 必须满足 $\forall 1<=j<=30,f(u,j)>=f(v,j)$.

但是你一定会WA或者fst，数据很简单：$u=(111)_2,v=(100)_2$。错误原因就是，比如说刚才推导过程的第一部分，当 $u$ 的第 $k$ 位和 $v$ 的第 $k$ 位都已经存在 $1$ 的情况下，实际上，如果在 $1$ 到 $k-1$ 位还存在 $1$，一定有一个 $1$ 会被推到下一位。但如果 $v$ 后面的位不存在 $1$ 了，那就无法匹配了。但是仔细想想，这种情况只可能 $u>v$ 时发生，完全可以一开始输入后就特判掉。

（感觉思维难度应该是普及+/提高吧，我都不知道我当时怎么乱蒙出规律的）

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define next Cry_For_theMoon
#define il inline
typedef long long ll;
using namespace std;
int q,u,v,sum1[40],sum2[40];
int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&u,&v);
		memset(sum1,0,sizeof sum1);
		memset(sum2,0,sizeof sum2);
		if(u>v){
			printf("NO\n");continue;
		}
		rep(j,1,30){
			sum1[j]=sum1[j-1];sum2[j]=sum2[j-1];
			if(u&1)sum1[j]++;
			if(v&1)sum2[j]++;
			u/=2;v/=2;
		}
		rep(j,1,30){
			if(sum1[j]<sum2[j])goto END;
		}
		printf("YES\n");continue;
		END:printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Eibon (赞：4)

显然易见，如果 $u_i < v_i$ ，则无法到达，如果二者相等，直接到达。

观察 $u$ ，发现每一次移动， $u$ 上的二进制中的 $1$ 只会向右移动，只会不变或减少，但一定不会变多。

所以如果 $u$ 合法，通过构造，一定能得到一种方案，使得 $v$ 中的 $1$ 的位置均大于等于 $u$ 中 $1$ 的位置， $1$ 的数量小于等于 $u$ 中 $1$ 的个数。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e5+5;
const int mod=1e9+7;
int T,u,v,VIP,a,b;
signed main()
{
	scanf("%lld",&T);
	while(T--){
		VIP=a=b=0;
		scanf("%lld%lld",&u,&v);
		if(u>v){
			printf("NO\n");
			continue;
		}
		for(int i=0;i<=30;i++){
			if(u&(1<<i)){
				a++;
			}
			if(v&(1<<i)){
				b++;
			}
			if(a<b){
				VIP=1;
				printf("NO\n");
				break;
			}
		}
		if(!VIP){
			printf("YES\n");
		}
	}
	return 0;
}
//dyyyyds
```

---

## 作者：pigstd (赞：3)

[CF1491D Zookeeper and The Infinite Zoo](https://www.luogu.com.cn/problem/CF1491D)

题意：对于点 $u$，有一条 $u \to (u+v)$ 的单向边当且仅当 $u\And v=v$，多组询问，每次给出一个 $(u,v)$，询问是否存在一条 $u\to v$ 的路径。

虽然只是 Global Round 的 D 题，但是我好菜。。。

第一个结论：若 $u>v$，则无解，原因显然。

第二个结论：对于每个 $u$，不妨每次增加一个 $v$ 满足 $v=2^i(i\in N)$。

为什么呢？如果增加的是另一个数 $x=2^{a_1}+2^{a_2}+...+2^{a_n}$，那么加 $n$ 次，第 $i$ 次加 $2^{a_i}$，显然是可行的，并且最终结果是一样的。

第三个结论：因为已知 $u \le v$，设 $v$ 中第一个为 $1$ 的数位为 $k$，那么 $u$ 中第一个为 $1$ 的数位必须 $\le k$，同时，第二，第三个都同理。即：设 $sum1_k$ 为 $u$ 在 $1-k$ 位中 $1$ 的个数，$sum2_k$ 为 $v$ 在 $1-k$ 位中 $1$ 的个数，那么对于任何时候都要有 $sum2_k\le sum1_k$。必要性显然。充分性我们可以这么构造：因为 $u \le v$，可以一位一位的把当前最高的不相同的位推到相同的，然后就可以了。建议手玩几个试一下。比如：$(011010)_2$ 和 $(100100)_2$，可以 $(011010)_2 \to (100010)_2 \to (100100)_2$。

代码就很好写了。[code](https://www.luogu.com.cn/paste/9ya1f72q)。

---

## 作者：FutaRimeWoawaSete (赞：3)

太SB了一点，虽然照样吃巨多罚时。                      

很显然我们可以把连边过程看做一个从 $u$ 变到 $u + v$ 的过程，那么我们发现这个过程就相当于把 $u$ 中的一些 $1$ 的位置加上 $1$ 然后给挪到前面去，当然进位也得照常进位。                   

我们考虑用一个结论来归纳这个操作，很显然我们 $u$ 中 $1$ 的个数变少可以通过进位控制，现在我们只需要保证 $v$ 的每一位可以被凑出来即可。                       

从后到前做，只要不出现 $u$ 的后缀 $1$ 个数小于 $v$ 的后缀 $1$ 个数那么当前位就可以拼凑出来。

```cpp
/*000010010

010000010 YES

直接暴力从后到前匹配即可*/
#include<bits/stdc++.h>
using namespace std;
const int Len = 1e5 + 5;
int n,m;
long long u,v;
bool check()
{
	if(u > v) return false;
	int numu = 0 , numv = 0;
	for(long long j = 0 ; j <= 32 ; j ++)
	{
		if((u >> j) & 1) numu ++;
		if((v >> j) & 1) numv ++;
		if(numv > numu) return false;
	}
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%lld %lld",&u,&v);
		if(!check()) puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：kimi0705 (赞：0)

### 题解：CF1491D Zookeeper and The Infinite Zoo
首先有这么几条显然的性质：
- 当 $u>v$ 时，$u$ 肯定到不了 $v$。
- 应为 $u\&v=u$ 所以 $u$ 二进制下所有的 $1$，$v$ 也必须为一。 $1$ 和 $1$ 相加必定进位，所以 $1$ 的数量必定减少或不变。(这里的 $\&$ 指[按位与](https://zh.wikipedia.org/wiki/%E4%BD%8D%E6%93%8D%E4%BD%9C#%E6%8C%89%E4%BD%8D%E4%B8%8E%EF%BC%88AND%EF%BC%89)。）
- $u$ 的 $1$ 必定不会往后移动。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, x, y, cntx, cnty;
void solve() {
    cin >> x >> y;
    if (x > y) return puts("NO"), void();
    cntx = cnty = 0;
    for (int i = 0; i <= 31; i++) {
        if (x & (1 << i)) cntx++;
        if (y & (1 << i)) cnty++;
        if (cntx < cnty) return puts("NO"), void();
    }
    return puts("YES"), void();
}
int main() {
    cin >> t;
    while (t--) solve();
    return 0;
}
```

---

## 作者：double_wings (赞：0)

# [Zookeeper and The Infinite Zoo](https://www.luogu.com.cn/problem/solution/CF1491D)
## 题意
如果 $u\operatorname{and}v=v$，则 $u$ 向 $u+v$ 连边，问存不存在 $u$ 到 $u+v$ 的路径。
## 思路 
设 $y=u+v$。
- 如果 $y$ 小于 $u$ 直接输出 `NO`。
- 把 $u$ 和 $y$ 拆成二进制可以发现 $v$ 是由 $u$ 中的 $1$ 所组成。我们可以令 $v$ 只取一位，也就是 $v$ 是 $2^x$，而 $u+v$ 就是在 $u$ 的二进制上不断进位，所以我们只需要判断能不能通过使 $u$ 不断进位变成 $y$。暴力判断即可。
## 代码

```cpp
#include <bits/stdc++.h>
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("-funroll-loops")
using namespace std;
using ll=long long;
using ull=unsigned long long;
//#define mid ((l+r)>>1)
//#define len (r-l+1)
//#define ls p<<1
//#define rs p<<1|1
//#define int long long
constexpr int inf=1e9+7;
constexpr int mod=998244353;
//constexpr ll inf=1e18+7;
//constexpr int N=;

int q;
bool get(int x,int y)
{
    int n=0,m=0;
    while(y)
    {
        if(x&1)n++;
        if(y&1)m++;
        x>>=1;y>>=1;
        if(n<m)return 0;
    }
    return 1;
}

// char buf[1<<21],*p1,*p2;
// #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();return x*f;}
void wt(long long x,char ch=0){if(x<0) putchar('-'),wt(-x);else{if(x>=10) wt(x/10);putchar(x%10+'0');}if(ch) putchar(ch);return;}
signed main(){
    //freopen("in.in","r",stdin);
    //freopen("ot.out","w",stdout);
    cin.tie(0);
    cout.tie(0);
    q=read();
    while(q--)
    {
        int u=read(),v=read();
        if(v<u) cout<<"NO";
        else 
        {
            if(get(u,v)) cout<<"YES";
            else cout<<"NO";
        }
        putchar('\n');
    }
    // cout<<clock()/(double)CLOCKS_PER_SEC;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

---

