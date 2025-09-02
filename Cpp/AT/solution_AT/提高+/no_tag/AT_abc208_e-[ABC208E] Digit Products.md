# [ABC208E] Digit Products

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc208/tasks/abc208_e

$ N $ 以下の正の整数のうち、各桁の数字の積が $ K $ 以下であるものは何個ありますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- 入力は全て整数である。

### Sample Explanation 1

$ 13 $ 以下の正の整数のうち、各桁の数字の積が $ 2 $ 以下であるものは $ 1,2,10,11,12 $ の $ 5 $ つです。

### Sample Explanation 2

$ 100 $ 以下の正の整数のうち、$ 99 $ 以外のものが条件を満たします。

### Sample Explanation 3

答えが $ 32 $ bit 整数に収まらない可能性があることに注意してください。

## 样例 #1

### 输入

```
13 2```

### 输出

```
5```

## 样例 #2

### 输入

```
100 80```

### 输出

```
99```

## 样例 #3

### 输入

```
1000000000000000000 1000000000```

### 输出

```
841103275147365677```

# 题解

## 作者：_Ponder_ (赞：7)

[Digit Products](https://www.luogu.com.cn/problem/AT_abc208_e)

### 题目大意

求有多少个不大于 $n$ 的正整数，使得该正整数各位乘积不大于 $k$。

### 思路分析

观察数据范围，首先考虑数位 DP。

考虑设计记忆化搜索函数 `dfs(int pos,bool limit,bool lead0,int mul)` 表示当前枚举到第 $\text{pos}$ 位，第 $\text{pos}$ 位是否受到限制，是否存在前导零，当前乘积为 $\text{mul}$ 时的满足条件的数的个数。同时设 $f_{\text{pos},\text{mul}}$ 表示在没有前导零，没有限制的条件下的记忆化数组。

然后分类讨论一下：

设当前枚举的数为 $i$。

- 当存在前导零，且 $i=0$ 时，$\text{mul}$ 不变。

- 当存在前导零，且 $i\not =0$ 时，$\text{mul}=i$。

- 当不存在前导零时，$\text{mul}=\text{mul}\times i$。

然后套板子就可以了。

注意乘积的值域可能很大，但状态不会很多，因此 $f$ 可以用 `map` 储存。

### 代码

```
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;
const int N=20;
#define int long long

int n,k;
int a[N];

map<int,int> f[N];//使用 map 储存 f

int dfs(int pos,bool limit,bool lead0,int mul){
    if(!pos) return mul<=k;//边界条件
    if(!limit&&!lead0&&f[pos].count(mul)) 
        return f[pos][mul];//记忆化
    int up=limit?a[pos]:9,res=0;//上届
    for(int i=0;i<=up;i++){
        int tmp;
        if(lead0&&i==0) tmp=mul;
        else if(lead0&&i!=0) tmp=i;
        else tmp=mul*i;//分类讨论
        res+=dfs(pos-1,limit&&i==up,lead0&&i==0,tmp);//直接累加
    }
    if(!limit&&!lead0) f[pos][mul]=res;
    return res;
}

int solve(int x){
    int len=0;
    while(x){//拆分数位
        a[++len]=x%10;
        x/=10;
    }
    return dfs(len,1,1,0);
}

signed main(){
    scanf("%lld%lld",&n,&k);
    cout<<solve(n)-1<<'\n';//注意 0 会被计算在内，需减去
    return 0;
}
```

---

## 作者：Rnfmabj (赞：2)

## ABC208E

*2024

### 题意

求有多少个不大于 $N$ 的正整数，使得该正整数各位乘积不大于 $K$。

$N \le 10^{18},K \le 10^9$

### 题解

$N$ 很大而且要求求解数位相关问题，显然数位 DP。

如果把乘积换成和这题就纯数位 DP 入门题了，比较卡手的地方在于当前乘积是一定要被设计到状态里的，但是一方面乘积太大了不好存，另一方面这个过大的乘积会不会造成状态数过多导致效率问题？

答案是想多了。

实际上会出现的乘积相当有限（极限情况下大约只有 $4 × 10^4$），而且还有内鬼数位 $0$。为啥说是内鬼呢，因为一旦 $0$ 不作为前导零出现而是在中间出现的话，整个数的乘积就会变成 $0$，后面再怎么改都没用，减少了一定的状态。而且由于是乘积，同一个乘积可以被很多种组合凑出来，存在大量的重复计算。

所以直接上  `std::unordered_map` 存状态就好了。设 $f_{zero,pre,dig,mul}$ 表示当前是否仍在前导零，是否紧贴上界限制，枚举到第几位，当前乘积时有多少合法方案，直接枚举转移即可。其中第四位 $mul$ 用 `std::unordered_map` 存储。

### 代码

```cpp
unordered_map<ll,ll>f[2][2][20];
ll n,k,lim[20];
ll dfs(bool z,bool p,ll x,ll mul){
	if(!x){
		if(mul<=k)return 1;
		else return 0;
	}
	if(f[z][p][x].count(mul))return f[z][p][x][mul];
	ll res=0;
	for(ll i=0;i<=(p?lim[x]:9);i++){
		if(z){
			if(i==0)res+=dfs(z,p&&i==lim[x],x-1,mul);
			else res+=dfs(0,p&&i==lim[x],x-1,i);
		}
		else {
			res+=dfs(z,p&&i==lim[x],x-1,mul*i);
		}
	}
	return f[z][p][x][mul]=res;
}
void solve(){
	n=R,k=R;
	ll tot=0;
	while(n){
		lim[++tot]=n%10;
		n/=10;
	}
	we(dfs(1,1,tot,0)-1);
	return ;
}
```



---

## 作者：Pop_Agoni (赞：1)

## 1.题目大意：

> 求有多少个不大于 $N$ 的正整数，使得该正整数各位乘积不大于 $K$。
其中 $N \le 10^{18} $，$K \le 10^9$。

---

## 2.主要思路：
这里有个考场时想到的思路，可以分享给大家。（可以直接下去看正解思路。）

我们枚举 $1 \leq i \leq K$，从 $K$ 开始往 $1$ 枚举。

然后对于每个 $i$ 进行质因数分解，并且我们只要 $2$，$3$，$5$，$7$ 这些质因数，其他因为都是大于 $10$ 的，不能填在一个十进制数的里面。

那么我们用这些质因数所填出来的数相乘必定小于 $K$。

因为一个数乘上一之后仍然等于他本身，所以我们可以用无限个 $1$。

我们先设 $i$ 的分解质因数的集合为 $q$。

然后我们就可以去算出相乘小于等于当前这个 $i$ 的方案有多少个，因为如果对于一个 $j$ 小于等于当前 $i$ 但是其分解出的质因数（只包含 $10$ 以内的）的集合 $p \subset  q$，则 $j=i \div k$，$k \in Z $。

我们不妨设之前分解过的数为 $L$。

那么我们就可以判断如果当前枚举的 $L \equiv 0 \pmod i$，那么我们直接跳过当次枚举。最后处理方案中有 $0$ 的情况。（好像可以动态开空间+状压 DP。）

---

但是我在处理方案时只想到了用数位 DP 的方法，所以不如直接数位 DP。

挺模板的，所以我讲些细节。

1. 乘积不一定单调递增，可以乘上 $0$。

2. 在乘法时要判断当前的 $0$ 是不是前导 $0$。

剩下的可以在代码中看注释理解。

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k,cnt,c[25],t;
__int128 ans;//以防万一，开 __int128
map<__int128,__int128> mp[20][2][2];
map<__int128,bool> vis[20][2][2];
void write(__int128 x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}//快写
__int128 dfs(ll x,bool flag,__int128 sum,bool bz){
    if(x<=0){
        if(bz||sum>k) return 0;//判断乘积时候小于 K，且是否全由 0 组成
        else return 1;
    }
    if(vis[x][flag][bz][sum]!=0) return mp[x][flag][bz][sum];//记忆话搜索，开map防止爆空间
    __int128 pot=0;
    for(ll i=0;i<=9;i++){
        if((!flag||c[x]>=i)) pot+=dfs(x-1,(flag&&c[x]==i),(sum*((bz&&i==0)?1:i)),(i==0&&bz));//注意点1与2，其他正常转移
        else break;   
    }
    vis[x][flag][bz][sum]=1;
    return mp[x][flag][bz][sum]=pot;
}
void init(ll x){
    t=x;
    while(t){
        c[++cnt]=t%10;
        t/=10;
    }//正常位数分解
    ans+=dfs(cnt,1,1,1);
}
int main(){
    cin>>n>>k;
    init(n);
    write(ans);
    printf("\n");
    return 0;
}

```

tips：如果有大佬写出来我的考场想法，可以私信我，谢谢。

---

## 作者：YuYuanPQ (赞：1)

注意到要求的是区间内某种数的个数，数据范围很大。\
考虑数位 DP。

设 $f_{x,sum}$ 表示当前到第 $x$ 位（倒序枚举），数字乘积为 $sum$ 时，满足 $sum\leq k$ 的数的个数。\
但是你会发现 $sum$ 很大，又显然可以想到其实出现的值并不多，所以可以用 `map` 来存。

最费脑子的也就这里：
- 当有前导零限制时：
  - 若 $i=0$，这意味着还没有非 $0$ 数出现，所以 $sum$ 不变（还是 $0$）。
  - 若 $i\neq 0$，这就是第 $1$ 个有效位，令 $sum=i$。
- 没有限制时：$sum$ 就乘上 $i$。

然后套数位 DP 的模板就好啦！

---
呃呃，这题赛时想到了正解但没敢打......（还因为当时已经不是很熟了）\
而且赛后发现我确实不完全会打数位 DP 模板。\
还不是因为自己不够努力。

## Code
```cpp
#include<bits/stdc++.h>

typedef int IT;
typedef long long LL;
typedef __int128 int128;
typedef double DB;
typedef long double LDB;

#define pb push_back
#define fst first
#define sec second
#define psh push
#define mkp make_pair
#define PII pair<IT,IT>
#define PLI pair<LL,IT>
#define lowbit(x) ((x)&(-x))

using namespace std;

const int WS=18;

LL n;
int k;

int d[WS+5],dl;
unordered_map<LL,LL>f[WS+3];

LL dfs(int x,LL sum,bool lim,bool zer){
    if(!x) return sum<=k;
    if(!lim&&!zer&&f[x].count(sum)) return f[x][sum];
    LL cnt=0;
    for(int i=0;i<=(lim?d[x]:9);i++){
        if(zer){
            if(!i) cnt+=dfs(x-1,sum,lim&&(i==d[x]),1);
            else cnt+=dfs(x-1,i,lim&&(i==d[x]),0);
        }
        else{
            cnt+=dfs(x-1,sum*i,lim&&(i==d[x]),0);
        }
    }
    if(!lim&&!zer) f[x][sum]=cnt;
    return cnt;
}

LL calc(LL x){
    dl=0;
    while(x){
        d[++dl]=x%10;
        x/=10;
    }
    return dfs(dl,0,1,1)-1;
}

int main(){
    scanf("%lld%d",&n,&k);
    printf("%lld\n",calc(n));
    return 0;
}
```

[Link](https://atcoder.jp/contests/abc208/submissions/65321619)

---

## 作者：__xxy_free_ioi__ (赞：1)

# AT\_abc208\_e \[ABC208E] Digit Products

数位 DP。

记忆化大法好。

## 解法

先将 $N$ 数位分解，然后考虑记忆化搜索，设 $f_{p,lead,limit,s}$ 表示当枚举到第 $p$ 位，该位是否是前导零，是否前面全部打满，乘积为 $s$ 的个数。可以单独开一个 map 用于存储 $s$。

直接套模板即可（爱死记忆化）（其他细节在代码注释里）!

```
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 35;

int n, k;
int num[N];
map<int, int> f[N][2][2];

int dfs(int p, int s, bool lead, bool limit) {
	if (p == 0) return (s <= k) && (!lead); // 注意，题目要求正整数
	if (f[p][lead][limit].count(s)) return f[p][lead][limit][s];
// 已经有记录就可以不继续dfs了
	
	int up = (limit == 1 ? num[p] : 9), res = 0;
// 前面是否打满
	for (int i = 0; i <= up; i++) {
		if (lead && i == 0) // 前导零需要特判
			res += dfs(p - 1, 1, 1, (i == up) && limit);
		else res += dfs(p - 1, s * i, 0, (i == up) && limit);
	}
	
	return f[p][lead][limit][s] = res;
// 返回时记录一下（下次就不用跑了）
}

int solve(int x) {
	int len = 0;
	while (x) num[++len] = x % 10, x /= 10;
// 数位分解
	return dfs(len, 1, 1, 1);
}

signed main() {
	cin >> n >> k;
	
	cout << solve(n) << '\n';
	
	return 0;
}
/*
13 2

100 80

1000000000000000000 1000000000
*/
```

---

## 作者：dangerous_DZR (赞：0)

# AT_abc208_e [ABC208E] Digit Products 题解
## 分析
当我们看到 $N \le 10 ^ {18}$ 时，一个响彻 OI 界的名字便会浮现而出——数位 dp（~~其实就是 dfs + 记忆化搜索~~）！

于是我们~~直接套模版~~再温习一下数位 dp：

- 将一个大的答案区间的左右端点按位进行拆分并用 dfs 构造符合要求的答案
- 为防止重复计算用 $f$ 数组进行记忆化搜索
- 注意判断前导零和上下限
- 此题还需要一个变量 $p$ 表示各位上的乘积（因题而异）
### 注意
1. 此题中各位的乘积可能不能用数组存储，所以考虑使用 map。
2. 本题的一大坑点：有时虽然前面一些数位的乘积大于 $k$，不满足条件，**但是任何数乘零等于零**！如果下一位是零呢？所以千万不要为了~~优化时间复杂度~~而在构造中途就判定错误，不记录答案。
3. 注意是**正整数**。
## 实现
令 $len$ 表示上限的长度（位数），$now$ 表示当前位，$u$ 表示当前位的上限，$f_{i,j, 0 / 1, 0 / 1}$ 表示构造一个长度（位数+前导零数量）为 $len - i$，各个位（不含前导零）上的乘积为 $j$，之前构造的数（没）达到上限，（没）有前导零的数的方案数。

则转移为：

- 当当前位为0且为前导零时，$f_{i, j, k, l} = f_{i, j, k, l} + f_{i - 1, 1, 0, 1}$
- 否则，$f_{i,j, k, l} = f_{i, j, k, l} + f_{i - 1, j \times now, k \land (now = u), 0}$

具体内容见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, num[25], len;
map<long long, long long> f[25][3][3];//使用 map 记录答案
long long dfs(long long now, long long p, bool last, bool zero){
	if (!now)return p <= k && !zero;//判断答案是否符合要求——注意前导零
	if (f[now][last][zero][p])return f[now][last][zero][p];//记忆化搜索
	long long u = last ? num[now] : 9, ans = 0;//是否达到上限
	for (long long i = 0; i <= u; i ++){
		if (i == 0 && zero)ans += dfs(now - 1, 1, 0, 1);//有前导零
		else ans += dfs(now - 1, p * i, last && i == u, 0);//继续构造
	}
	return f[now][last][zero][p] = ans;//记录答案
}
signed main(){
	cin >> n >> k;
	while (n)num[++ len] = n % 10, n /= 10;//数位拆分
	cout << dfs(len, 1, 1, 1);//初始条件
	return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

这显然是一个数位 DP，那么我们可以用记忆化搜索来实现，由于方便一些，就这样搞。

我们记录状态也就可以用 map 了。

```cpp
int dfs(int p,int fg,int front0,int cnt)
```

这是我的 DFS 的参数。

 $p$ 位，$fg$ 是否受进位限制，$front0$ 前导 $0$，$cnt$ 目前答案。
 
 我们把需要知道的参数都给列出来了，这样我们就可以直接递归转移，每一次枚举能选哪些数，然后开一个 map 对其状态记录。
 
 这样，就做完了。
 
 [link](https://atcoder.jp/contests/abc208/submissions/51992160)。

---

## 作者：DDF_ (赞：0)

## 题面

求 $[1,n]$ 范围内，各个位的乘积不大于 $k$ 的数字数。

## 题解

看到求大范围内满足条件的数字数量首先考虑数位 DP。

定义 $f_{x,y}$ 为从最高位到倒数第 $x$ 位，乘积为 $y$ 的可行数字数。

然后就可以记忆化搜索，从最高位一位不漏统计到第一位，考虑每一位可行的取值，并将这个位的答案存在 $f$ 中。特殊地，当这一位仍为前导 $0$ 的位或者这一位仍在范围的最上界，由于没有取到 $0$ 和 $9$ 之间的所有数，所以不将其存进 $f$ 中。

数位 DP 经常会处理 $[0,n]$ 的数字数，且得到的答案呈现前缀和的形式，所以我们要进行类似前缀和的删数。

而这里只用删掉 $0$ 就行，所以我们将得到的答案减去 $1$。

其实大部分的数位 DP 都是套板子，把板子记住就可以攻克很多数位 DP 题。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[22];
ll n,k;
unordered_map <ll,ll> f[22];
ll dfs(int pos,ll c,bool qd,bool lim) {
	if(pos==0) return c<=k;
	if(!lim&&!qd&&f[pos].count(c)) return f[pos][c];
	int end=lim?a[pos]:9;
	ll ret=0;
	for(int i=0;i<=end;i++) {
		if(qd) ret+=dfs(pos-1,i,(qd&&i==0),(lim&&i==end));
		else ret+=dfs(pos-1,c*i,0,(lim&&i==end));
	}
	if(!qd&&!lim) f[pos][c]=ret;
	return ret;
} //数位DP模板
ll ask(ll x) {
	int cnt=0;
	while(x) a[++cnt]=x%10,x/=10;
	return dfs(cnt,0,1,1); 
}
int main() {
	scanf("%lld%lld",&n,&k);
	printf("%lld",ask(n)-1);
	return 0;
}
```

---

## 作者：xiaoPanda (赞：0)

## ABC208E - Digit Products(*2024)

### Problem
在 $1$ 到 $n$ 中，有多少正整数 $i$ 满足 $i$ 的各个数位之积不大于 $k$。

### Solution
注意到 $n$ 很大，考虑数位 DP。

为避免对个位数的初始化，这里将题目改为有多少自然数 $i$ 满足条件，并且规定个位数可以看成最后一位是 $0$ 的两位数（换句话说，个位数是一位数，$0$ 是零位数），并且定义 $0$ 各个数位乘积等于 $1$，最后答案再减 $1$。 

那么可以设 $f_{i,j}$ 表示在 $0$ 到 $i$ 中满足积不大于 $j$ 的自然数。

考虑对于一个数 $x$，当 $x$ 的零位是 $0$ 时，即 $x=0$ 时，若 $k>0$，根据之前的定义，$0$ 各个数位乘积等于 $1$，答案就是 $1$ 个，若 $k=0$，则没有答案。

当 $x$ 的个位是 $0$ 时，$x$ 各个数位的乘积一定是 $0$，满足条件，这样的数有 $\lfloor\frac x {10}\rfloor$ 个

当 $x$ 的个位不为 $0$ 时，设 $x=10p+q(1\le q\le 9)$，尝试枚举 $q$，可以得出 $p\le \lfloor\frac {n-q} {10}\rfloor$，并且 $p$ 的位数之积 $\le \lfloor\frac k q\rfloor$（注意到 $\lfloor\frac k q\rfloor* q\le k$），即 $f_{\lfloor\frac {x-q} {10}\rfloor,\lfloor\frac k q\rfloor}$。

综上所述，可以得到：

$$f_{i,j}=[k>0]+\lfloor\frac i {10}\rfloor+\sum_{w=1}^9 f_{\lfloor\frac {i-w} {10}\rfloor,\lfloor\frac j w\rfloor}$$

记忆化搜索即可，$f$ 数组建议使用 `map`，因为 $i,j$ 可能很大，但并不是所有都要使用，时间复杂度为 $O(\log n)$。

---

