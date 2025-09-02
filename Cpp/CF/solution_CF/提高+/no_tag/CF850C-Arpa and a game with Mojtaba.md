# Arpa and a game with Mojtaba

## 题目描述

Mojtaba和Arpa在玩一个游戏。  
游戏中有一个n个数的数列，在一个回合中，他可以选取一个形如$p^k$的数，其中$p$是个质数，而$k$是一个正整数，并且满足这个数列中至少有一个数能被它整除。每一个回合结束时将整个数列中所有的能被这个数整除的数都将除以这个数。  
（例如数列{$1$，$1$，$17$，$289$}.如果选取了$17$，经过一个回合之后数列将变成{$1$，$1$，$1$，$17$}）  
而游戏胜负的条件是有一个人如果无法选出这样一个数就输了。  
游戏中Mojtaba先手，游戏双方都将用最优策略，输出胜利者的名字

## 说明/提示

第一个样例中Mojtaba无法选取任何数字，Arpa胜；   
第二个样例中Mojtaba选取$17$（$17^1$），数列变为{$1$，$1$，$1$，$1$}，Arpa无法选取，Mojtaba胜；  
第三个样例中Mojtaba选取$17$（$17^1$），Arpa选取$17$（$17^1$），胜。或者Mojtaba选取$289$（$17^2$），Arpa选取$17$（$17^1$）胜。

## 样例 #1

### 输入

```
4
1 1 1 1
```

### 输出

```
Arpa
```

## 样例 #2

### 输入

```
4
1 1 17 17
```

### 输出

```
Mojtaba
```

## 样例 #3

### 输入

```
4
1 1 17 289
```

### 输出

```
Arpa
```

## 样例 #4

### 输入

```
5
1 2 3 4 5
```

### 输出

```
Arpa
```

# 题解

## 作者：HansLimon (赞：6)

在脑子里面想一下发现没有对应的模板，那么果断考虑上SG

----

枚举每一个素数，然后模拟题意除掉这么一个过程。

不过这么干就成了大模拟，显然(我也没试过，~~说不定可以~~)是不行的，然后选择的是形如$p^k$，那么就类似于一种状压(?)的感觉，把指数k作为函数下标。这样子就成了枚举消去素数的指数值。

基于这样，我们又知道，指数值不可能很大，与数据有关联，所以预处理的时候把每个素数p能够使用的指数k记下来，减少了很多运算(由于不是很清楚实际大小就开成了map)。

脑子里面胡一下就有后续状态
	
    now&((1<<i) - 1)|(now>>i)//now指当前状态，i指枚举到的k
    //顺便说当前k的下一个不是k ++ O.O

然后：
```cpp
//这里是头文件，自己挂qwq
int n, otp;//otp是输出
map<int, int> mem, cors;//前面的记已有的SG值，后面那玩意是k

//inline int counts(int now, int &goal){while (now)now >>=1, goal ++;}
int Penu(int now){
	if (!now || mem.find(now) != mem.end())return mem[now];
	register int ans = 0;register set<int> mex;//不一定用set，随便来个啥都行，你甚至可以平板电视
//	counts(now, counter);
	for (register int i = 1;i < 31;i ++)if (now >> i)mex.insert(Penu(now&((1<<i) - 1)|(now>>i)));
	while (mex.count(ans))ans ++;
	return mem[now] = ans;
}

int main(){
	mem[0] = 0;
	scanf("%d", &n);
	for (register int i = 1, j;i <= n;i ++){
		scanf("%d", &j);//传说中的预处理
		for (register int r = 2, c = 0;r*r <= j;r ++, c = 0){
			while (!(j%r)){
				c ++;
				j /= r;
			}
			if (c)cors[r] |= (1<<c);//不要if也行
		}
		if (j > 1)cors[j] |= 2;//没除完就还来
	}
	for (map<int, int>::iterator cnt = cors.begin();cnt != cors.end();cnt ++)otp ^= Penu(cnt -> second);//指针日常操作，还可以用auto
	return !printf("%s", otp?"Mojtaba":"Arpa");//Mojtaba先手
}
```

最后很想说一下做题感想，本来用的是平板电视，结果RE；递归改成map，RE；递归改成set，RE。最后发现主函数末尾写的是：
	
    return printf(....

然后codeforces就一个劲的error 4，喜提了4次RE

![FF](https://s2.ax1x.com/2020/02/21/3nLFZ6.jpg)

所以， _**最开始先把 ! 打好再做题啊啊**_ 

---

## 作者：Jay142753869 (赞：6)

原题传送门：[CF850C](https://www.luogu.com.cn/problem/CF850C) 

题意：给定一个正整数序列，两人轮流对这个数列进行如下修改：选取一个素数p和一个整数k将序列中能整除p^k的数除以p^k，问谁有必胜策略。

首先当然要先筛素数，之后把每一个序列里的数都分解质因数，统计其素数因子各次方数的数，然后用这个式子 $(x>>i)|(x&((1<<(i-1))-1))$ 去模拟删除 $x$  然后把$\dfrac{x}{p^k}$操作，因为每个质因数的操作都是独立的，那么可以看成一个nim游戏，将每个质因数的情况返回值异或一下即可。  
 _Code_ 
 ```cpp
#include<cstdio>
#include<map>
#include<cstring>
#define maxn 1000010
using namespace std;
int n,tot=0,flag=0,prime[maxn];
bool isprime[maxn];
map<int,int>sg,st;
inline int read()
{
    char c=getchar();
    int x=0;
    while(c<'0'||c>'9') c=getchar();
    while(c>='0'&&c<='9')
    	x=(x<<3)+(x<<1)+c-48,c=getchar();
    return x;
}
int ssg(int x){//SG函数 
    if(x==0)return 0;
    if(sg.count(x))return sg[x];
    map<int,int>vis;
    int p=x,t=0;
    while(p)p>>=1,t++;
    for(int i=1;i<=t;i++)
        vis[ssg((x>>i)|(x&((1<<i-1)-1)))]=1; //主要步骤   
    for(int i=0;;i++)
        if(!vis[i])return sg[x]=i;
}
inline void work(int x){//分解质因数 
    for(int i=1;prime[i]*prime[i]<=x;i++){
        int t=0;
        while(x%prime[i]==0){
            x/=prime[i];
            t++;
        }
        if(t)
			st[prime[i]]|=1<<(t-1);
    }
    if(x!=1)
		st[x]|=1;
}
inline void prepare(){//筛素数 
    memset(isprime,true,sizeof(isprime));
    isprime[1]=false;
    for(int i=2;i<=maxn-10;i++){
        if(isprime[i])prime[++tot]=i;
        for(int j=1;j<=tot&&i*prime[j]<=maxn-10;j++){
            isprime[i*prime[j]]=false;
            if(i%prime[j]==0)break;
        }
    }
}
int main(){
    prepare();
    n=read();
    for(int i=1;i<=n;i++){
        int x;
        x=read();
        work(x);
    }
    map<int,int>::iterator it;
    for(it=st.begin();it!=st.end();it++)
		flag^=ssg(it->second);
    if(flag)puts("Mojtaba");
    else puts("Arpa");
    return 0;
}
 ```

---

## 作者：kouylan (赞：4)

明显是一道 sg 分解的博弈题。

接下来，我们就来考虑判断是必胜还是必败的 grundy 函数怎么写。

我们发现，游戏只跟这个质数在每个数中出现的次数有关，比如样例三中，对于 $17$，它在四个数中的信息就是 $0,0,1,2$，我们发现，这些数是不超过 $31$ 的，所以可以对于每一个质数，状压的存储它在每个数中出现的次数。

接下来考虑如何转移。首先我们肯定可以把每一个质数分开考虑（即按质数分别 grundy 分解），假设我们对于一个质数 $p$，要除以它的 $i$ 次方，我们想，现在这个数的状态该如何表示。假设原状态为 $x$，那么，所有大于 $i$ 的位置，都会右移 $i$ 位，而前 $i-1$ 位不变（因为不能整除，所以不除）。因此，新状态就可以表示成

$$x>>i|(x\&(1<<i-1)-1)$$

最后，当 $x$ 为 $0$ 时，是必败态。这样，我们就能 grundy 了。

要注意，此题的 $a_i$ 较大，sg 函数需要用 map 存储。

下面是 AC 代码。

```cpp
/*
Codeforces 850C
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n,ans;
map<int,int> sg,s;

void work(int x)
{
	int tmp=x;
	for(int i=2;i*i<=tmp;i++)
		if(x%i==0)
		{
			int sum=0;
			while(x%i==0)
				sum++, x /= i;
			s[i] |= 1<<sum-1;
		}
	if(x>1)
		s[x] |= 1;
}

int grundy(int x)
{
	if(x==0)
		return 0;
	if(sg.count(x))
		return sg[x];
	map<int,int> vis;
	int tmp=x,m=0;
	while(tmp)
		m++, tmp >>= 1;
	for(int i=1;i<=m;i++)
	{
		int y=x>>i|(x&(1<<i-1)-1);
		vis[grundy(y)] = 1;
	}
	for(int i=0;;i++)
		if(!vis.count(i))
			return sg[x] = i;
}

signed main()
{
	cin>>n;
	for(int i=1,x;i<=n&&cin>>x;i++)
		work(x);
	for(map<int,int>::iterator it=s.begin();it!=s.end();it++)
		ans ^= grundy((*it).second);
	puts(ans ? "Mojtaba" : "Arpa");
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：shinkuu (赞：1)

学习 SG 基础题。

首先发现每个质数之间是独立的，于是分成了若干个子游戏。

考虑如何计算每个子游戏的 SG 值。一开始没搞懂为什么可以状压，看了大佬代码才明白：对于一个质数 $p$，$p^k$ 对答案是否有影响，**只和这个 $k$ 是否出现有关**。所以将 $k$ 的出现状态情况成二进制数 $u$，则它的所有后继状态 $v$ 可以表示为 $(u>>k)|(((1<<(k-1))-1)\&u)$，其中 $k$ 为该次选择 $p^k$。然后直接套用 SG 函数的计算方式即可。

计算出每个子游戏的 SG 值，最后套用 SG 定理即可。

注意到不同质数，状态相同，得到答案也相同。使用记忆化优化时间复杂度。~~具体复杂度我也不会算啊。~~

code：

```cpp
int n,m;
map<int,int> mp,f;//数据范围较大，使用 map
int calc(int u){
	if(!u)
		return 0;
	if(mp.count(u))
		return mp[u];
	set<int> st;
	for(int i=1;i<=30;i++){
		int v=(u>>i)|(((1<<(i-1))-1)&u);
		if(v==u)
			break;
		st.insert(calc(v));
	}
	for(int i=0;i<=100;i++){
		if(!st.count(i))
			return mp[u]=i;
	}//SG 函数取 mex
}
void solve(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		for(int j=2;j*j<=x;j++){
			int cnt=0;
			while(x%j==0)
				x/=j,cnt++;
			if(cnt>0)
				f[j]|=1<<(cnt-1);
		}
		if(x>1)
			f[x]|=1;
	}//质因数分解
	int ans=0;
	for(auto i=f.begin();i!=f.end();i++)
		ans^=calc(i->second);//SG 定理
	if(!ans)
		puts("Arpa");
	else
		puts("Mojtaba");
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

---

## 作者：xujindong_ (赞：0)

显然，每个质因数是独立的，因此这个游戏可看作若干子游戏的组合，每个子游戏形如 $b_i=\nu_p(a_i)$，每次选一个 $k\leq\max(b_i)$，将 $\geq k$ 的 $b_i$ 减去 $k$。

注意到我们只关心每种 $b$ 是否存在，将相同的 $b$ 合成一个，只剩 $2^{29}$ 种状态。此时我们直接依据定义记忆化搜索 SG 函数。

可以证明，单次搜索的复杂度不超过 $O(\sqrt V)$：按最高位分层，设 $V$ 所在层数为 $k=\lfloor\log_2n\rfloor$。搜索一个第 $i$ 层的数时，会搜索 $0\sim i-1$ 层的某个数各一次。对于前 $\frac k2$ 层，状态数是 $O(2^{\frac k2})=O(\sqrt V)$ 的；对于后 $\frac k2$ 层，从第 $k$ 层开始，每层被访问的次数依次为 $1,1,2,4,8,16\cdots$，也只会涉及 $O(\sqrt V)$ 个层。加上有大量重合的状态，复杂度很不满，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
unordered_map<int,int>p,f;
int sg(int n){
  if(f.count(n))return f[n];
  int ans=0;
  bool vis[30]={0};
  for(int i=1;i<=__lg(n)+1;i++)vis[sg(n>>i|(n&((1<<(i-1))-1)))]=1;
  while(vis[ans])ans++;
  return f[n]=ans;
}
int main(){
  f[0]=0,cin>>n;
  for(int i=1,a;i<=n;i++){
    cin>>a;
    for(int j=2;j*j<=a;j++){
      if(a%j==0){
        int cnt=0;
        while(a%j==0)a/=j,cnt++;
        p[j]|=1<<(cnt-1);
      }
    }
    if(a!=1)p[a]|=1;
  }
  for(unordered_map<int,int>::iterator it=p.begin();it!=p.end();it++)ans^=sg((*it).second);
  return puts(ans?"Mojtaba":"Arpa"),0;
}
```

---

## 作者：kimi0705 (赞：0)

~~更好的阅读体验~~节选自：[博弈论基础](https://www.cnblogs.com/kimi0705/p/18382642/game)。

### 题目描述
Mojtaba 和 Arpa 在玩一个游戏。

游戏中有一个 $n$ 个数的数列，在一个回合中，他可以选取一个形如 $p^k$ 的数，其中 $p$ 是个质数，而 $k$ 是一个正整数，并且满足这个数列中至少有一个数能被它整除。每一个回合结束时将整个数列中所有的能被这个数整除的数都将除以这个数。

（例如数列 $\{1,1,17,289\}$ 如果选取了 $17$，经过一个回合之后数列将变成 $\{1,1,1,17\}$）

而游戏胜负的条件是有一个人如果无法选出这样一个数就输了

游戏中 Mojtaba 先手，游戏双方都将用最优策略，输出胜利者的名字。
### 题目解析
因为每次只能删除 $1$ 种质数，所以每一种质数互不干扰。考虑分开计算，最后求异或和。

显然我们要质因数分解。

对于每一个质数，显然如果有对个 $k$ 相等那么相当于 $1$ 个。又因为 $p^k\le10^9$，所以 $k\le32$。所以可以状压。用 $b_i$ 记录这一个 $k$ 有没有出现过，然后枚举除数 $p^k$ 中的 $k$ 进行 $\texttt{SG}$ 转移（求 $\operatorname{mex}$）。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
map<int, int> mp, f; // 状态压缩； 记忆化
int SG(int x) {
    if (!x) return 0; // 什么都没有就什么都不用干
    if (f.count(x)) return f[x]; // 记忆化
    set<int> st; // mex
    int t = 0, p = x;
    while (p) p >>= 1, t++; // 最高位（因为要保证有一个数能被除）
    for (int i = 1; i <= t; i++) 
        st.insert(
            SG((x >> i) |  // 前半部分是被除以的，所以左移；
            (x & ((1 << (i - 1)) - 1))) // 后半部分是只留取后 [1, i - 1] 位的
        ); 
    int now = 0;
    while (st.count(now)) now++; // 求 mex
    return f[x] = now; // 记忆化
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                int cnt = 0;
                while (x % j == 0)
                    cnt++, x /= j;
                mp[j] |= (1 << (cnt - 1));
            }
        }
        if (x > 1)
            mp[x] |= 1;
    }
    int res = 0; // 异或和
    for (auto i : mp)
        res ^= SG(i.second); // 对于每一个子问题 (每一个质数)求解 SG
    if (res)
        cout << "Mojtaba" << endl;
    else
        cout << "Arpa" << endl;
}
```

---

