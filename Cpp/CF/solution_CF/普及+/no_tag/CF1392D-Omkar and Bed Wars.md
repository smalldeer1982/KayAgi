# Omkar and Bed Wars

## 题目描述

Omkar is playing his favorite pixelated video game, Bed Wars! In Bed Wars, there are $ n $ players arranged in a circle, so that for all $ j $ such that $ 2 \leq j \leq n $ , player $ j -       1 $ is to the left of the player $ j $ , and player $ j $ is to the right of player $ j - 1 $ . Additionally, player $ n $ is to the left of player $ 1 $ , and player $ 1 $ is to the right of player $ n $ .

Currently, each player is attacking either the player to their left or the player to their right. This means that each player is currently being attacked by either $ 0 $ , $ 1 $ , or $ 2 $ other players. A key element of Bed Wars strategy is that if a player is being attacked by exactly $ 1 $ other player, then they should logically attack that player in response. If instead a player is being attacked by $ 0 $ or $ 2 $ other players, then Bed Wars strategy says that the player can logically attack either of the adjacent players.

Unfortunately, it might be that some players in this game are not following Bed Wars strategy correctly. Omkar is aware of whom each player is currently attacking, and he can talk to any amount of the $ n $ players in the game to make them instead attack another player — i. e. if they are currently attacking the player to their left, Omkar can convince them to instead attack the player to their right; if they are currently attacking the player to their right, Omkar can convince them to instead attack the player to their left.

Omkar would like all players to be acting logically. Calculate the minimum amount of players that Omkar needs to talk to so that after all players he talked to (if any) have changed which player they are attacking, all players are acting logically according to Bed Wars strategy.

## 说明/提示

In the first test case, players $ 1 $ and $ 2 $ are attacking each other, and players $ 3 $ and $ 4 $ are attacking each other. Each player is being attacked by exactly $ 1 $ other player, and each player is attacking the player that is attacking them, so all players are already being logical according to Bed Wars strategy and Omkar does not need to talk to any of them, making the answer $ 0 $ .

In the second test case, not every player acts logically: for example, player $ 3 $ is attacked only by player $ 2 $ , but doesn't attack him in response. Omkar can talk to player $ 3 $ to convert the attack arrangement to LRLRRL, in which you can see that all players are being logical according to Bed Wars strategy, making the answer $ 1 $ .

## 样例 #1

### 输入

```
5
4
RLRL
6
LRRRRL
8
RLLRRRLL
12
LLLLRRLRRRLL
5
RRRRR```

### 输出

```
0
1
1
3
2```

# 题解

## 作者：Chinese_zjc_ (赞：9)

$DP$ 题.

看完题目,就不难发现,一个合法的环一定是由下面四种字符串组成的:
$$
RL,RRL,RLL,RRLL
$$


这还不简单?

直接用 $dp[i]$ 表示前 $i$ 个字符最少需要改动的字符数量,暴力 $O(n)$ 跑就能 $AC$ 了.

**这题是环,要考虑首尾问题,由于我们状态转移最多涉及到之前的 $4$ 个,我们只需要进行旋转字符串 $4$ 次,做 $4$ 次 $DP$ 即可.**

```cpp
//This Code was made by Chinese_zjc_.
#include<iostream>
#include<string>
#define int long long
using namespace std;
int n,t,dp[200005],ans;
string s;
const string g[]={"RL","RRL","RLL","RRLL"};//貌似没用
int diff(string A,string B)
{
    int tmp=0;
    for(int i=0;i<(int)A.length();++i)
    {
        if(A[i]!=B[i])
        {
            ++tmp;
        }
    }
    return tmp;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--)
    {
        cin>>n>>s;
        s=' '+s;
        ans=INF;
        for(int l=1;l<=5;++l)
        {
            dp[0]=0;
            dp[1]=INF;
            for(int i=2;i<=n;++i)
            {
                dp[i]=dp[i-2]+diff("RL",s.substr(i-1,2));
                if(i>=3)
                {
                    dp[i]=min(dp[i],dp[i-3]+diff("RRL",s.substr(i-2,3)));
                    dp[i]=min(dp[i],dp[i-3]+diff("RLL",s.substr(i-2,3)));
                    if(i>=4)
                    {
                        dp[i]=min(dp[i],dp[i-4]+diff("RRLL",s.substr(i-3,4)));
                    }
                }
            }
            ans=min(ans,dp[n]);
            s=' '+s.substr(2,n-1)+s[1];
        }
        cout<<ans<<endl;
    }
    return 0;
}
```



---

## 作者：dead_X (赞：7)

## 题意
注意到唯一禁止的情况就是 A 打 B ， B 打 C ， C 打 D。


那么题意就是一个 ``'L'`` 和 ``'R'`` 组成的环，问最少改变几个 ``'L'`` 或 ``'R'`` 才能使环上不存在连续的三个相同字符。
## 思路
Tags：贪心，字符串，细节

我们先统计连续的字符数量。

比如 ``"LRLLLLRRRRRLRRRR"`` 就是 $\{1,1,4,5,1,4\}$ 。

(注意，这是一个环，破环为链要保证第一个字符和最后一个字符不同；如果全部相同就直接特判)

然后对于每一段字符，对答案的贡献就是 $len/3$ 。

**特别注意，对于全部一样的情况，答案是 $(n+2)/3$** ~~细节题就这？~~
## 代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
char a[2000003];
int main()
{
	int T=read();
	while(T--)
	{
		int n=read(),ans=0;
		scanf("%s",a+1);
		for(int i=1; i<=n; i++) a[i+n]=a[i];
		bool f=1;
		char tmp=a[1];
		for(int i=2; i<=n; i++) if(a[i]!=tmp) f=0;
		if(f) 
		{
			printf("%d\n",(n-1)/3+1);
			continue;
		}
		int pos=0,now=0;
		for(int i=1; i<n; i++) if(a[i]!=a[n]) { pos=i-1; break; }
		for(int i=1; i<=n; i++) a[i]=a[i+pos];
		for(int i=1; i<=n; i++) 
		{
			if(a[i]!=a[i-1]) ans+=now/3,now=0;
			++now;
		}
		ans+=now/3;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：fls233666 (赞：6)

根据题目中的描述，我们来考虑什么是 *不合法的攻击状态*。

我们发现，存在不合法的攻击状态，**当且仅当 $a$ 被 $b$ 攻击，$a$ 不攻击 $b$ 而是去攻击不攻击 $a$ 的 $c$。** 具体而言，存在不合法的攻击状态，就是环中存在连续的一段 $\texttt{LLL}$ 或一段 $\texttt{RRR}$。

于是题目变成了**通过修改环上一些位置的人的攻击方向，使环中不存在连续的三个人攻击方法相同。**

考虑拆环为链统计 $\texttt{L}$ 或 $\texttt{R}$ 的连续段，因为如果出现连续三个攻击方向相同的人就要修改一个，所以我们把统计出来的每个连续段的长度除 $3$ 加到答案中即为要修改的位置数。

**那么，从环的哪个位置拆环为链呢？**

为了能让输入的串上的 $\texttt{L}$ 和 $\texttt{R}$ 在我们扫描时全凑在一起，我们可以把输入的串复制一遍接在原串最后，然后 **暴力找到第一个 $\texttt{L}$ 与 $\texttt{R}$ 的分界点**，从这个位置开始往后的 $n$ 个字符，就是我们拆环的结果。

但是，**如果都是 $\texttt{L}$ 或者都是 $\texttt{R}$ 的情况怎么办？**

我们拿样例的最后一组测试数据来考虑：

	5
    RRRRRR

把这个序列画成环：

![Pic1](https://cdn.luogu.com.cn/upload/image_hosting/vjyv7nsr.png)

根据我们刚刚处理的其它情况方法，这里有 $5$ 个 $\texttt{R}$，按照上文的处理方法，我们应该修改 $1$ 个攻击方向，于是我们得到了下面这张图：

![Pic2](https://cdn.luogu.com.cn/upload/image_hosting/j13t49km.png)

我们发现，改了一个后情况还是不合法的：**因为 $\texttt{R}$ 的整个序列首尾相连，导致 $\texttt{L}$ 左右两边的两个 $\texttt{R}$ 连在了一起，又产生了连续的四个 $\texttt{R}$，使整个序列不合法了。**

那么处理的方法是什么？再改一个就好了。

![Pic3](https://cdn.luogu.com.cn/upload/image_hosting/fl5iasu3.png)

进一步观察，我们发现：**当整个环的人的攻击方向都相同时，如果序列长度不能被 $3$ 整除，就需要在上文方法得到的答案的基础上再 $+1$。**

可以拿 $n=4$ 全是 $\texttt{R}$ 的情况验证一下：

![Pic4](https://cdn.luogu.com.cn/upload/image_hosting/ouxf7e9o.png)

显然这个猜测是对的。于是这题就做完了。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 2e5+5;
char rb[mxn<<1];
int n,cnt,ans;

inline void getrb(){
	char c=getchar();
	while(c!='L'&&c!='R')
		c=getchar();
	int tg=1;
	rb[tg+n]=rb[tg]=c;
	tg++;
	c=getchar();
	while(c=='L'||c=='R'){
		rb[n+tg]=rb[tg]=c;
		tg++;
		c=getchar();
	}
}  //快速读入字符串序列

int main(){
	int test,dt;
	scanf("%d",&test);
	while(test--){
		scanf("%d",&n);
		getrb();
		
        dt=1;
		while(dt<n){
			if(rb[dt+1]!=rb[dt])
				break;
			dt++;
		}  //找到 L 与 R 的第一个分界点
        
		cnt=1;
		ans=0;
		for(rgt i=dt+2;i<=dt+n;i++){
			if(rb[i]!=rb[i-1]){
				ans+=cnt/3;  //统计答案
				cnt=1; 
			}else
				cnt++;  //算连续段长度
		}
		ans+=cnt/3;
        
		if(dt==n&&cnt%3)  //特判全是 L 或全是 R的情况
			ans++;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：cqbzFGR (赞：1)

# 题解：CF1392D Omkar and Bed Wars
### 题目分析
对于这一道题，有两种方式求解，这里讲解 DP 的方法。\
根据题目，可以依次枚举出每一个合法的最小长什么样。\
对于2个字符：$RL$。\
对于3个字符：$RRL$ $RLL$。\
对于4个字符：$RRLL$。\
而其他的合法字符都可以与以上最小基数的字符串组合而成。\
并且我们可以发现，这道题不是链而是环，所以要么破环成链，要么就把字符串轮 $4$ 次分别跑 DP。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
const int maxn=2e5+5;
long long dp[maxn];
string s;
int work(string x,string y){
	int ans=0,m=x.size();
	for(int i=0;i<m;i++){
		if(x[i]!=y[i]) ans++;
	}
	return ans;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>s;
		long long ans=INT_MAX;
		s=" "+s;
		for(int k=0;k<=4;k++){
			dp[0]=0;
			dp[1]=INT_MAX;
			for(int i=2;i<=n;i++){
				dp[i]=dp[i-2]+work("RL",s.substr(i-1,2));
				if(i>=3) dp[i]=min(dp[i],min(dp[i-3]+work("RRL",s.substr(i-2,3)),dp[i-3]+work("RLL",s.substr(i-2,3))));
				if(i>=4) dp[i]=min(dp[i],dp[i-4]+work("RRLL",s.substr(i-3,4)));
			}
			ans=min(ans,dp[n]);
			s=" "+s.substr(2,n-1)+s[1];
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：魔符sigil (赞：1)

### Description: 

给定一个字符串，字符串由LR两种字母组成，且首尾相连形成一个环，分别表示每个位置上的人攻击的方向，一次修改能改变一个位置的攻击方向，求最少修改次数，使得每个人都至少受到一个人的攻击。

### Solution: 

容易发现答案成立的充要条件是没有连续的三个人的攻击方向相同，即不存在情况 LLL 或 RRR。因此，当且仅当存在3个连续的方向时，才会对答案造成贡献。

于是我们可以将连续的方向合并为一整段，考虑每段对答案的贡献。很多题解都有给出贡献的式子为 $\lfloor \frac{len}{3} \rfloor$，却没有给出证明，这里提供一种思路。

考虑最基础的几种情况，最优修改方式显然为：

RRR ->RLR

RRRR->RLRR 或 RRRR->RRLR

RRRRR->RRLRR

对于长度为6的段 RRRRRR 显然只修改一处是不可能的。类似的，由于长度为5时最优修改的方式，会导致每到3的倍数时都必然需要多一次修改。因此便可以想到以3为单位修改，即可以转换为 RRLRRL，但这样做会改变右边一段的长度，但只需稍加修改，例如将最右边的RL交换即可保证段的长度不变且保证正确性。

还需注意的是可能存在整个环的方向都相同的情况，此时只需先在任意一处修改破环为链，接下来把剩下的部分当成整段处理即可，答案为：$1+\lfloor\frac{len-1}{3}\rfloor$。

---

## 作者：白依尘_轩子墨 (赞：1)

**题意:**


给一个 ```01``` 段，问最少改变多少个 ```0``` 或 ```1``` 使得不存在长度为 3 的 ```01``` 子段。

**思路:**

先破环为链。

暴力硬搞，找到每一个连续段的长度。

对于每一段，需要改变的最小字符数量即为这一段 $\lfloor \frac{len}{3} \rfloor$

**证明：**
对于一段连续的序列，改变 $n$ 个位置要保证不存在长度为 3 的序列，我们可以想到一个贪心想法，即每隔两个连续的 ```0``` 或 ```1``` ，就改变这个位置使其变成 ```1``` 或 ```0```，则对于一段长度为 $len$ 的序列，
若 $len\equiv 0  \pmod{3} $,则对于答案的贡献就是 $\frac{len}{3}$,否则只要将多出来的连续序列移到开头即可。

比如:

$00000 \to 10000 \to 00100$ 

若整个链为一个连续序列，先把3的倍数处理掉，就会多出一小段连续序列，需要多改变一个位置使其不连续，其对答案的贡献即为 $\lceil \frac{len}{3} \rceil$。

综上所述，一段连续序列对答案的贡献即为 
 $\lfloor \frac{len}{3} \rfloor$.
 
**例子:**

 ```000001111111``` ,转化为 $\{5,7\}$.

不难发现， $ans$ 就是 $\lfloor \frac{5}{3} \rfloor+\lfloor \frac{7}{3} \rfloor=3$.

特别的，对于全部是 ```0``` 和 ```1``` 的情况，
$ans$ 为 $\lceil \frac{n}{3} \rceil$. 

**代码:**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=4e5+10;
const int mod=1e9+7;
const int inf=0x7fffffff;
typedef long long ll;
namespace io{
	const int _SIZE=(1<<21)+1;
	char *iS,*iT,ibuf[_SIZE],c,stk[40];int tot;
#define gc()getchar()
	template<class I>
	inline void read(I &_x){
		I fl=1;
		for(c=gc();c<'0'||c>'9';c=gc()) if(c=='-') fl=-1;
		for(_x=0;c>='0'&&c<='9';c=gc()) _x=(_x<<3)+(_x<<1)+(c&15);
		_x*=fl;
	}
	template<class I>
	inline void prt(I _x,char ch='\0'){
		tot=0;
		if(_x<0) putchar('-'),_x*=-1;
		do{
			stk[tot++]=_x%10|48,_x/=10;
		}while(_x);
		do{
			putchar(stk[--tot]);
		}while(tot);
		if(ch) putchar(ch);
	}
}
using io::read;
using io::prt;
int t;
int n,tot;
int a[Maxn],cnt[Maxn],len[Maxn];
bool flag=true;
ll ans;
int main(){
	read(t);
	while(t--){
		read(n);
		for(int i=1;i<=n;i++){
			char ch;
			scanf("%c",&ch);
			if(ch=='L') a[i]=a[i+n]=0;
			if(ch=='R') a[i]=a[i+n]=1;
			if(a[i]!=a[1]) flag=false;
		}
		if(flag){ 
			prt((n+2)/3,'\n');
			continue;
		}
		cnt[++tot]=len[tot]=1;//cnt表示下标，len表示每一段的长度 ，tot表示每一段的编号 
		for(int i=2;i<=(n<<1);i++){
			if(a[i]==a[i-1]) cnt[tot]=i;
			if(a[i]!=a[i-1]) cnt[++tot]=i; /
			len[tot]++;
		} 
		int k=upper_bound(cnt+1,cnt+1+tot,n)-cnt;//找第一个结尾大于n的段的下标
		for(int i=2;i<=k;i++) ans+=len[i]/3;//统计每一段的贡献 (从二开始是为了把第一段接到尾段) 
		prt(ans,'\n');
		for(int i=1;i<=tot;i++) cnt[i]=len[i]=0;
		ans=tot=0,flag=true;
	}
	return 0;
}

```


---

## 作者：isletfall (赞：1)

# 思路
一道思维量不大的贪心题。我们把题目意思翻译过来，不合法的充要条件是一个人他左右的人和他攻击方向都相同。那么我们需要统计一下有多少个连续的相同攻击方向的人。

接下来我们要考虑怎么统计答案，发现对于一串连续的相同序列，我们将每三个人中间那个人方向取反就一定使得这三个人都变成合法状态，所以操作的次数就是将每串连续相同的序列的长度除以三加起来就行了。

$ Tip :$

 $ 1. $ 因为题目是链，所以我们需要拆环为链来进行统计

 $ 2. $ 全部相同需要特判

 $ 3. $ 多组数据记得清空 
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+7;
int n,a[maxn],sum[maxn],cnt,now=0,ans,p,t;
bool pd1,pd2;
char c;
int main(){
	scanf("%d",&t);
	while(t--){
	scanf("%d",&n);
	ans=0;
	cnt=0;now=0;pd1=0;pd2=0;
	memset(sum,0,sizeof(sum));
	memset(a,-1,sizeof(a));
	for(int i=1;i<=n;i++){
		cin>>c;
		if(c=='L')a[i]=0,a[i+n]=0;
		if(c=='R')a[i]=1,a[i+n]=1;
		if(a[i]!=a[1])pd1=1;
	}
	for(int i=2;i<=n;i++)
	{if(a[i]!=a[i-1]){
	p=i;now=i-1;break;}}
	while(now<=2*n){
		if(now>=p+n){break;}
		now++;
		++cnt;sum[cnt]=1;
		while(a[now]==a[now+1]){
			sum[cnt]++;
			now++;
			if(now>=p+n)break;		
		}
	}
	for(int i=1;i<=cnt;i++)
	ans+=sum[i]/3;
	if(!pd1)printf("%d\n",int(ceil(double (n)/3.0)));
	else printf("%d\n",ans);	}
	return 0;
} 
```


---

## 作者：pigstd (赞：1)

一道比较好的dp题，小蒟蒻实现的时候犯了很多sb错误。

观察一下，发现答案只能由若干个 $\text{RL,RRL,RLL,RRL}$ 这样的串组成，即连续的 $L$ 和 $R$ 的数目不大于 $2$，并且以 $R$ 开头，$L$ 结尾。

下文中令 $L$ 为 $1$，$R$ 为 $0$。

那么先考虑当是一个队列（即首尾不连接）而不是一个环的时候怎么做：设$dp_{i,0/1,1/2}$表示到第$i$个数，这个数为$0/1$，已经连续了$1/2$次。

那么状态转移方程就很快能够推出来：

$dp_{i,0,1} = \min (dp_{i-1,1,1} , dp_{i-1,1,2}) + (a_i == 1)$

$dp_{i,0,2} = dp_{i-1,0,1} + ( a_i == 1 )$

$dp_{i,1,1} = \min(dp_{i-1,0,1},dp_{i-1,0,2}) + ( a_i == 0 )$

$dp_{i,1,2} = dp_{i-1,1,1} + a_i == 0$

其中， $(a_{i}==0)$ 表示当 $a_i=0$ 是返回 $1$ ，否则返回 $0$ 。反之亦然。

初始化也很容易得到：

$dp_{1,0,1}=(a_1==1),dp_{1,1,1} = dp_{1,0,2} = dp_{1,1,2} = \inf$ 

那么最后的结果就是 $\min(dp_{n,1,1},dp_{n,1,2})$ 。

那么，如果是一个环呢？

我们发现一个环中的答案，必然是由一种队列的答案推出来的，因为组成这个答案的串的长度最多是 $4$，那么我们对队列左移$/$右移$0 - 3$格，一定就有一个就是答案。

[code](https://www.luogu.com.cn/paste/1z7enh93)

---

## 作者：奇米 (赞：1)

# 题解 - $\mathrm{P1392D}$

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/CF1392D)

## $\mathrm{Sol}$

好像大家都是找规律做法，我提供一种 dp 的做法

设 $f_{i,j,k}$ 表示到第 $i$ 个人攻击方向为 $j∈[0,1]$ 当前受到 $k∈[0,1,2]$ 个人攻击的最少修改次数。

我们每次枚举上一个人的攻击方向 $lj$ 以及受到攻击次数 $lk$ 进行转移。分 $4$ 种情况进行讨论：

* $i$ 和 $i-1$ 攻击方向相同且攻击左边，那么此时转移的条件为 $lk=2$ 因为只有受到两个人的攻击才能往任意方向进攻，此时 $i$ 可能受到 $0\sim 1$ 个攻击来自 $i+1$。所以转移为 $f_{i,0,0/1}=\min(f_{i-1,lj,lk}+[s_i='R'])[lk==2]$

* 对于 $i$ 和 $i-1$ 都攻击右边的转移为：$f_{i,1,2}=\min(f_{i-1,lj,lk}+[s_i='L'])[lk<2]$

* 对于 $i$ 攻击左边，$i-1$ 攻击右边那么转移为：$f_{i,0,0/1}=\min(f_{i-1,lj,lk}+[s_i=='L'])[lk<2]$

* 对于 $i$ 攻击右边，$i-1$ 攻击左边那么转移为：$f_{i,1,1/2}=\min(f_{i-1,lj,lk}+[s_i=='R'])[lk>0]$


时间复杂度：$O(\sum n)$ 附加一个大常数 

## $\mathrm{Code}$

```cpp
const int N=2e5+5;

char a[N];
int Q,n,ans,f[N][2][4];

inline int C(char c) { return (c=='R')?1:0; }

int main()
{
	io.read(Q);
	for (;Q--;)
	{
		io.read(n);
		scanf("%s",a+1);
		//0:left 1:right 
		int ans=1e9;
		For(j,0,1) For(k,0,2) 
		{
			For(i,0,n+1) mem(f[i],88);
			f[0][j][k]=0;
			For(i,1,n) For(jj,0,1) For(kk,0,2) For(Newj,0,1) 
			{
				int Newk;
				if(jj==Newj&&jj&&kk<2) f[i][Newj][2]=min(f[i][Newj][2],f[i-1][jj][kk]+(C(a[i])^Newj));
				if(jj==Newj&&!jj&&kk==2) For(Newk,0,1) f[i][Newj][Newk]=min(f[i][Newj][Newk],f[i-1][jj][kk]+(C(a[i])^Newj));
				if(jj!=Newj&&jj&&kk>0) For(Newk,1,2) f[i][Newj][Newk]=min(f[i][Newj][Newk],f[i-1][jj][kk]+(C(a[i])^Newj));
				if(jj!=Newj&&!jj&&kk<2) For(Newk,0,1) f[i][Newj][Newk]=min(f[i][Newj][Newk],f[i-1][jj][kk]+(C(a[i])^Newj));
			}
			ans=min(ans,f[n][j][k]);
		}
		io.write(ans);
		puts("");
	}
	return 0;
}
/*
1
6
LRRRRL
*/
		
```


---

## 作者：Hydrogen_Huang (赞：0)

## 题解：CF1392D Omkar and Bed Wars
### 题目分析
什么情况是不合法的（即需要改变方向）？

考虑有三个人，思考在怎样的情况下，需要改变中间的人。

三个人的情况有八种，但是只有这两种情况是不合法的

`LLL` 或者 `RRR`。

所以题目就变成了：给定一个环，在这个环中不能出现连续三个相同字母，求最少需要改变多少个字母。

对于一个长度为 $n(n \geq 3)$ 的连续字母串来说，要使这个串合法，至少需要改变 $\frac{n}{3}$ 个字母。

如果这个一整个环都是相同的字母，则需要改变
$\lceil \frac{n}{3} \rceil$ 个字母，因为字母可以从末尾继续拼到开头形成一个新的连续串。

从哪里开始算这个串？

因为末尾的字母如果与开头的字母相同，那么它就可以与开头的连续字母串组成一组更长的连续字母串，所以就可以把末尾的连续与开头字母相同的字母直接加到开头的连续字母串里面，算成同一个字母串。

即 `RRLRLR` 可以看做 `RRRLRL`。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;
char c[N];//c[i]表示第i个连续字母串是什么字母连续
char tmp;
int len[N];//len[i]表示第i个连续字母串的长度
int n;
int t;
int cnt;//统计连续相同字母串的数量
int ans;

void work()
{
	cnt=0;
	
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>tmp;
		if(tmp!=c[cnt])
//如果与前面的字母不相同，就创建一个新的连续相同字母串。
		{
			c[++cnt]=tmp;
			len[cnt]=1;
		}
		else
//如果相同，则前面的连续相同字母串的长度增加
			len[cnt]++;
	}

//只有一个连续相同字母串，就是所有字母都相同的情况，特判
	if(cnt==1)
	{
		cout<<(n-1)/3+1<<"\n";
		return;
	}
//合并末尾的串到开头来
	if(c[1]==c[cnt])
	{
		len[1]+=len[cnt];
		cnt--;
//合并后串的数量减少
	}
//统计答案
	ans=0;
	for(int i=1;i<=cnt;i++)
		ans+=len[i]/3;
	
	cout<<ans<<"\n";
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);

//用不可能出现的字母来初始化，那么第一个字母一定就会创建一个新的串
  c[0]='K';

	cin>>t;
	while(t--)
	{
		work();
	}
	return 0;
}
```

第一次写题解，写的不好请见谅。

管理员大大求通过！

---

## 作者：wxzzzz (赞：0)

### 思路

考虑最本原的合法串，显然是 $\tt RL$。

稍微扩展，得到 $\tt RRL,RLL$。

发现如果一个字符串合法那么它的每一个字符至少属于一个 $\tt RL$、$\tt RRL$ 或 $\tt RLL$。

发现 $\tt RL\in RLL,RL\in RRL,RLL\notin RRL$，考虑对原串进行一遍 $\tt RLL,RRL$ 覆盖，再用 $\tt RL$ 覆盖。这样就能覆盖所有的合法部分。

未覆盖的部分便是需要操作的区域，对于一串连续的 $\tt LLL\dots L$ 或 $\tt RRR\dots R$，记其长度为 $cnt$，需要操作 $\lceil\cfrac{cnt}{3}\rceil$ 次，使其分别变成形如 $\tt RLLRLLRLL\dots$ 和 $\tt RRLRRLRRL\dots$。

接下来考虑放到环上如何做。

对于覆盖，只需在边界尝试覆盖几次即可。

对于操作，记 $pl,pr$ 表示最长的 $1\sim pl,pr\sim n$ 均为被覆盖，先对 $[pl+1,pr-1]$ 操作，再将 $1\sim pl$ 接到 $pr\sim n$ 后面，对这两段区间单独操作即可。

注意特判全未被覆盖的情况，此时 $s$ 每个字符均相同，直接统计整个串即可，无需考虑环。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m, ans;
char s[200005], g[200005];
bool flag[200005];
int main() {
    cin >> T;

    while (T--) {
        for (int i = 1; i <= n; i++)
            flag[i] = 0;

        cin >> n;
        scanf("%s", s + 1);

        if (n >= 3) {
            if ((s[n - 1] == 'R' && s[n] == 'L' && s[1] == 'L') || (s[n - 1] == 'R' && s[n] == 'R' && s[1] == 'L'))
                flag[n - 1] = flag[n] = flag[1] = 1;

            if ((s[n] == 'R' && s[1] == 'L' && s[2] == 'L') || (s[n] == 'R' && s[1] == 'R' && s[2] == 'L'))
                flag[n] = flag[1] = flag[2] = 1;
        }

        for (int i = 1; i <= n - 2; i++)
            if ((s[i] == 'R' && s[i + 1] == 'L' && s[i + 2] == 'L') || (s[i] == 'R' && s[i + 1] == 'R' &&
                    s[i + 2] == 'L'))
                flag[i] = flag[i + 1] = flag[i + 2] = 1;

        for (int i = 1; i <= n - 1; i++)
            if (s[i] == 'R' && s[i + 1] == 'L')
                flag[i] = flag[i + 1] = 1;

        if (n >= 2 && s[n] == 'R' && s[1] == 'L')
            flag[n] = flag[1] = 1;

        int pl = 0, pr = n + 1;

        while (pl <= n && !flag[pl + 1])
            pl++;

        while (pr >= 1 && !flag[pr - 1])
            pr--;

        ans = 0;

        for (int i = pl + 1, cnt = 1; i < pr; i++) {
            if (flag[i])
                continue;

            if (!flag[i - 1] && s[i] == s[i - 1])
                cnt++;
            else
                cnt = 1;

            if (s[i] != s[i + 1] || flag[i + 1] || i == pr - 1)
                ans += (cnt + 2) / 3;
        }

        m = 0;

        if (pl == n + 1) {
            for (int i = 1; i <= n; i++)
                g[++m] = s[i];
        } else {
            for (int i = pr; i <= n; i++)
                g[++m] = s[i];

            for (int i = 1; i <= pl; i++)
                g[++m] = s[i];
        }

        for (int i = 1, cnt = 1; i <= m; i++) {
            if (g[i] == g[i - 1])
                cnt++;
            else
                cnt = 1;

            if (g[i] != g[i + 1] || i == m)
                ans += (cnt + 2) / 3;
        }

        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：leoair (赞：0)

### 题意：
有 $n$ 个人在玩起床战争，他们围成一个圈，使第 $i$ 个人在第 $i+1$ 个的左边（其中第 $n$ 个人在第 $1$ 个人左边）。给定一个长度为 $n$ 的字符串，若第 $i$ 个字符是 `L`，则代表第 $i$ 个人攻击他左边的人，否则就是在攻击他右边的人。
我们定义一个合法的攻击为：
- 若只有 $a$ 攻击 $b$，则 $b$ 必须攻击 $a$。
- 若 $a$ 和 $c$ 同时攻击 $b$，或 $a$ 和 $c$ 都不攻击 $b$，则 $b$ 可以任意攻击 $a$ 和 $c$ 中的一个。
你每次可以进行一次操作，使字符串中的一个字符从 `L` 变为 `R`，或从 `R` 变为 `L`。求使字符串所代表的攻击状态合法的最小操作次数。

### 分析：
显然，若相邻两个人的攻击状态为 `RL`，则这两个人的攻击必定合法。相邻三人的攻击状态，若是 `RLL` 或 `RRL`，那么这三人就组成了一个合法攻击的环。同理，若相邻四人的攻击状态是 `RRLL`，则这四人就组成了一个合法攻击的环。
因此，我们可以在字符串中寻找这四个字符串，并记 $dp_i$ 为使前 $i$ 个字符合法的最小操作次数。
由于这四个字符串最多有四种状态，所以将原字符串代表的环的用四个顺序寻找答案。

### Code：
```cpp
/*
user:leoair
time:2022.3.24
*/
#include <bits/stdc++.h>
#define int long long
#define N 200010
using namespace std;

int dp[N];
string s;

inline int read(){
    int s = 0, w = 1;
    char ch = getchar();
    for (; ch < '0' || ch > '9'; w *= ch == '-' ? -1 : 1, ch = getchar());
    for (; ch >= '0' && ch <= '9'; s = s * 10 + ch - '0', ch = getchar());
    return s * w;
}

int calc(string a, string b, int res = 0){
    for (int i = 0; i < a.size(); ++i)
        if (a[i] != b[i]) ++res;
    return res;
}

signed main(){
    for (int _ = read(), ans, n; _--; ){
        n = read(), cin >> s, s = " " + s, ans = 2147482597;
        for (int i = 1; i < 5; ++i){
            dp[0] = 0, dp[1] = 2147482597;
            for (int i = 2; i <= n; ++i){
                dp[i] = dp[i - 2] + calc("RL", s.substr(i - 1, 2));
                if (i > 2){
                    dp[i] = min(dp[i], dp[i - 3] + min(calc("RRL", s.substr(i - 2, 3)), calc("RLL", s.substr(i - 2, 3))));
                    if (i > 3) dp[i] = min(dp[i], dp[i - 4] + calc("RRLL", s.substr(i - 3, 4)));
                }
            }
            ans = min(ans, dp[n]), s = " " + s.substr(2, n - 1) + s[1];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

不难发现存在一种贪心构造可以将一条方向连续的颜色段进行三个三个的分组，去掉不计入贡献的首尾后答案就是 $\lceil \frac{len-2}{3} \rceil$。

对于首位的颜色段要合并算。            

最后特判所有颜色相等的情况，不然会被卡掉。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int n,nums;
char s[Len];
int Ceil(int x)
{
	x -= 2;
	if(x <= 0) return 0;
	if(x % 3) return x / 3 + 1;
	return x / 3;
}
vector<int> calc;
int main()
{
	//freopen("exercises.in","r",stdin);
	//freopen("exercises.out","w",stdout);
	int T;scanf("%d",&T);
	while(T --)
	{
		calc.clear();
		nums = 0;
		scanf("%d",&n);
		scanf("%s",s + 1);bool eq = 1;
		for(int i = 2 ; i <= n ; i ++) if(s[i] != s[i - 1]) eq = 0;
		if(eq) 
		{
			printf("%d\n",(n + 2) / 3);
			continue;	
		} 
		int tot = 0;calc.push_back(0);
		for(int l = 1 , r ; l <= n ; l = r + 1) 
		{
			r = l;
			while(r + 1 <= n && s[r + 1] == s[l]) r ++;
			if(r == n)
			{
				if(s[1] == s[n]) 
				{
					calc[1] += r - l + 1;
					continue;
				}
			}
			calc.push_back(0);tot ++;
			calc[tot] = (r - l + 1);
		}
		for(int i = 1 ; i <= tot ; i ++) nums += Ceil(calc[i]);
		printf("%d\n",nums);
	}
	return 0;
}
```

---

