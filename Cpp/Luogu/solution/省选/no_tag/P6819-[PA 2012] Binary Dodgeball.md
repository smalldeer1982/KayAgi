# [PA 2012] Binary Dodgeball

## 题目背景

PA 2012 Round 6。

## 题目描述

有 $n$ 个盒子，开始时每个盒子中有一个棋子。


两位选手轮流操作，每次可以选择一个 $i$ 号盒子中的棋子和一个正整数 $p$，将棋子移到编号为 $2^p\times i$ 的盒子中。若编号为 $2^p\times i$ 的盒子中已有棋子了，则这两个棋子都会被移出盒子。不能移动者输。

求第 $k$ 小的 $n$，使得**后**手能赢得游戏。

## 说明/提示

对于 $100\%$ 的数据，$1\le k<10^9$。

## 样例 #1

### 输入

```
2```

### 输出

```
10```

# 题解

## 作者：AFewSuns (赞：5)

非常妙的一道题目。

### 题目大意

有 $n$ 个盒子，开始时每个盒子中有一个棋子。两个人进行博弈，每次选择两个正整数 $i$，$p$，将 $i$ 号盒子中的一个棋子移到 $2^p\times i$ 号盒子中。若 $2^p\times i$ 号盒子已有棋子，则抛弃这两个棋子。不能移动者输。

求第 $k$ 小的 $n$，使得先手必**败**。

$1 \leq k \leq 10^9$

### 题目分析

为了找到第 $k$ 小的合法的 $n$，我们需要先会判断一个 $n$ 合不合法。

将 $1 \sim n$ 写成二进制的形式，那么乘一个 $2^p$ 相当于在末尾增加 $p$ 个 $0$，当所有数都大于 $n$ 时就输了。

不难发现，只有当两个数 $\text{lowbit}$ 位前面部分相同时，它们才有可能被同时抛弃。举个例子：

- $1001101|000$

- $1001101|00000$

这两个数字在 $\text{lowbit}$ 位的左边都相同，那么在第一个数字后面添加两个 $0$ 时，它们会被同时抹去。

- $11001|0000$

- $10010|000$

这两个数字在 $\text{lowbit}$ 位的左边不同，所以就算在第二个数字后面添加一个 $0$，它们也不会被同时抹去。

于是将 $1 \sim n$ 按照 $\text{lowbit}$ 位的前面部分进行区分，相同的则划分成一个组。

对于同一个组，令其前面相同部分为 $w$，则这些数一定形如 $w \times 2^p$，当 $p_1 < p_2$ 时，$w \times 2^{p_1}$ 号盒子的棋子可以放到 $w \times 2^{p_2}$ 号盒子。将题目反过来，操作改为把 $i\times 2^p$ 号盒子的棋子放到 $i$ 号盒子，此时结果也是一样的。

所以现在从增加 $0$ 变成了删去 $0$，没得删的人输。

发挥你们大脑的想象力，把一个一个 $0$ 看成石子，这就变成了一个没那么经典的取石子游戏：

**每次可以从一堆石子拿走一些石子，不能不拿，如果拿完后同一组有两堆石子个数一样，则把这两堆拿走。**

考虑把后面的强制操作去掉。假如有两堆石子个数一样，但我不拿走，会影响答案吗？

如果先手必胜，那么只有可能后手碰这两堆石子，但后手只要从一堆取了一些石子，先手就可以模仿他在另一堆取同样石子，直到两堆变为 $0$ 或后手不取了，那还是先手必胜。后手同理。

所以现在变为了最简单的取石子游戏，**先手必输当且仅当石子个数异或和为** $0$。

---

继续优化判断方法。对于每一个 $i$，计算 $1 \sim n$ 中有多少个数 $\text{lowbit}$ 后有 $i$ 个 $0$，很容易算出有 $\lfloor \dfrac{n}{2^i}\rfloor-\lfloor \dfrac{n}{2^{i+1}}\rfloor$ 个。

因为要求异或和，所以只跟其奇偶性有关系。将 $n$ 用二进制表示，这个式子的奇偶性其实就是第 $i$ 位等不等于第 $i+1$ 位。等于就是偶数，不等于就是奇数。

设 $n$ 的二进制形式为 $p$，则异或和为 $\oplus_i{[p_i \neq p_{i+1}]i}$。

发现 $k$ 比较大，无法直接枚举判断，所以考虑二分。假设现在二分到 $x$，就要求 $[1,x]$ 有多少个符合条件的 $n$。

现在的 $n$ 的答案只跟其二进制的相邻位有关系，直接对其进行数位 dp。设 $f_{i,j,k,0/1}$ 表示考虑到 $n$ 的第 $i$ 位，其中第 $i$ 位为 $j$，目前异或和为 $k$，是否贴着 $x$ 上界。转移很好转移，就不再赘述。

二分一个 $\log$，数位 dp 两个 $\log$，总复杂度 $O(\log^3n)$，实测 $k$ 取 $10^9$ 时 $n$ 大约为 $7 \times 10^{10}$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fr(i,x,y) for(register ll i=(x);i<=(y);i++)
#define pfr(i,x,y) for(register ll i=(x);i>=(y);i--)
using namespace std;
ll K,f[66][2][66][2];
ll ck(ll x){
	fr(i,0,60) fr(j,0,1) fr(k,0,63) fr(l,0,1) f[i][j][k][l]=0;
	f[60][0][0][1]=1;
	pfr(i,60,1){
		fr(j,0,1){
			fr(k,0,63){
				fr(l,0,1){
					if(!f[i][j][k][l]) continue;
					if(l==1){
						if((x>>(i-1))&1){
							f[i-1][1][k^((j^1)*(i-1))][1]+=f[i][j][k][l];
							f[i-1][0][k^(j*(i-1))][0]+=f[i][j][k][l];
						}
						else f[i-1][0][k^(j*(i-1))][1]+=f[i][j][k][l];
					}
					else{
						f[i-1][1][k^((j^1)*(i-1))][0]+=f[i][j][k][l];
						f[i-1][0][k^(j*(i-1))][0]+=f[i][j][k][l];
					}
				}
			}
		}
	}
	ll res=0;
	fr(i,0,1) fr(j,0,1) res+=f[0][i][0][j];
	return res-1;
}
int main(){
	scanf("%lld",&K);
	ll l=1,r=(1ll<<60)-1;
	while(l<r){
		ll mid=(l+r)>>1;
		if(ck(mid)<K) l=mid+1;
		else r=mid;
	}
	printf("%lld",l);
} 
```

---

## 作者：qczrz6v4nhp6u (赞：4)

好玩的题目。

### Solution

考虑判定一个局面是先手必胜还是后手必胜。一眼丁真每个棋子都是独立的，所以直接启动 ${\rm SG}$。

然后发现每个状态的后继都是一个链状的结构，这跟 Nim 游戏是一样的，所以我们知道 ${\rm SG}(i)=\lfloor\log_2\frac ni\rfloor$。于是一个局面的 ${\rm SG}$ 值 ${\rm SG}(1\sim n)=\bigoplus_{1\le i\le n}\lfloor\log_2 \frac ni\rfloor$。

枚举每一个值并统计它出现了多少次，推式子：

$${\rm SG}(1\sim n)=\bigoplus_{k}\Big(\big(\lfloor\frac{n}{2^k}\rfloor-\lfloor\frac n{2^{k+1}}\rfloor\big)\bmod 2\Big)\times k$$

其中 $\big(\lfloor\frac{n}{2^k}\rfloor-\lfloor\frac n{2^{k+1}}\rfloor\big)$ 就是满足 $\frac{n}{i}\in [2^k,2^{k+1})$ 的 $i$ 的个数。观察一下，发现 $\Big(\big(\lfloor\frac{n}{2^k}\rfloor-\lfloor\frac n{2^{k+1}}\rfloor\big)\bmod 2\Big)$ 就是 $n$ 的第 $k$ 位与第 $k+1$ 位是否相同。

接下来考虑拆位，即统计 $n$ 的每一位贡献到 ${\rm SG}$ 值的系数。打表 code：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
ull f[6];
void init(){
	for(int i=0;i<64;i++)
		for(int j=0;j<6;j++)
			if(i>>j&1)
				f[j]^=3ull<<i;
}
int n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init();
	for(int i=0;i<6;i++)
		for(int j=0;j<64;j++)
			cerr<<(f[i]>>j&1)<<" \n"[j==63];
	return 0;
}
```

打出来的表长这样：

```
0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0
0 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

不难发现规律：第 $0$ 列的系数均为 $0$；设 $j=\log_2{\rm lowbit}(i)$，则 $[0,j]$ 行内第 $i$ 列的贡献系数都是 $1$，$(j,+\infty)$ 行内第 $i$ 列的贡献系数都是 $0$。

对它消元，使得每列仅出现一个 $1$。那么此时的后手必胜要求就是对于每一种 $j$，所有满足 ${\rm lowbit}(i)=j$ 的数位 $i$ 异或起来是 $0$。

现在我们有相当好的办法刻画 ${\rm SG}$ 值，直接从高到低确定每一位即可。时间复杂度 $O(\log n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
ui n;bool val[64];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;n++;
	ull ans=0,cnt=1ull<<29;
	for(int i=35;i>=1;i--){
		if(!(i&(i-1)))ans|=(ull)val[i]<<i;
		else{
			if(n>cnt)
				n-=cnt,ans|=1ull<<i,val[i&-i]^=1;
			cnt>>=1;
		}
	}
	cout<<(ans+(n>1))<<'\n';
	return 0;
}
```

---

## 作者：_Fatalis_ (赞：3)

很好的思维+板题。啊虽然不知道是不是很板，但是知道做法后这么一想感觉确实挺板的，还是见识太少。

题意可以转化为在 $1\sim n$ 中奇数个数条链上进行跳石子博弈，具体的：

1. 每一条链长度为 $\lfloor\log \lfloor\frac{n}{i}\rfloor\rfloor +1$；
2. 每次可以选择某个位置上的结点向后跳到任意位置；
3. 也可以每次选择两个位置上的结点消掉；

于是就有个大概的思路，找到对于某个 $n$ 的 SG 值，对其分析；要么推式子直接算答案，要么推前缀式子二分答案。

简单观察就能发现 3 中的操作无需考虑，其实本质上就是将某个节点向后跳到一个有石子的节点上。实际上将两个石子跳在一起，相当于两者 SG 值相等，于是抵消，与两者直接删去的 SG 值相同，方案等价。感性上也很好理解，反证即可。

于是可以转换为简单 Nim 游戏，链上某点位置的 SG 值为当前是链的倒数第几个位置 $rk - 1$；

比如 $n=10$，有 $sg(n=10)=[(sg_{\text{nim}}(3) \oplus sg_{\text{nim}}(2) \oplus sg_{\text{nim}}(1)]\oplus [sg_{\text{nim}}(1)]\oplus [sg_{\text{nim}}(1)]$

因为 $[1\to 2\to 4\to 8],\ [3\to 6],\ [5\to 10],\ [7],\ [9]$

于是就有式子：

$$
sg(n) =\bigoplus\limits_{i=0}^{n/2}\bigoplus\limits_{j = 1} ^ {\lfloor\log_2 {\lfloor\frac{n}{2i+1}\rfloor}\rfloor} j
$$

赛时卡在这里，这里已经有了 $O(n\log n) - O(1)$ 的做法了。

考虑交换求和顺序，对式子分析：

$$
\log_2 \frac{n}{2i+1}\ge j\\\ \\
\frac{n}{2i+1}\ge 2^j\\\ \\
t=\frac{n}{2i+1}\le \lfloor\frac{n}{2^j}\rfloor
$$

同时打表注意到对于整数 $k$ 有 $f(2k-1)=0\iff f(2k) = 0$，于是考虑只统计偶数的情况，

于是就发现可以对不同 $j$ 统计奇偶性来加速计算。发现式子中右式含义即为二进制下第 $j$ 位的值。对奇偶差分便能得到结论：对 $n$ 二进制拆分 $n=\sum_{x\in S} 2^x$，设 $S_k$ 表示 $S$ 中 $\operatorname{lowbit}=k$ 的 $x$ 个数。

$$
f(n)=0 \iff \bigoplus\limits_{x\in S}x =\bigoplus\limits_{x\in S} (x - 1) \iff \forall k,\ S_k \text{ is odd}
$$

于是对最后一个结论数位 dp 即可，设 $f_{i,j}$ 表示考虑了 $x< 2^{i+1}$（考虑了前 $i$ 位），$\operatorname{lowbit}$ 异或和当前为 $j$ 的个数。

统计的时候对 $n$ 按位统计，感觉做法很厉害，在此拜谢 masterhuang 大神对我的帮助。

要注意考虑分奇偶的贡献统计，一些要考虑清楚的边界。

时间复杂度 $O(\log^2 n)-O(\log^2 n)$。

_可能有用的东西：https://oeis.org/A253315_ 

```cpp
// Copyright 2024 Lotuses
#include <bits/stdc++.h>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

// #define int long long
typedef long long ll;
typedef unsigned long long ull;
typedef std::vector<int> vi;
typedef std::pair<int, int> pii;
#define sint static int

ll f[64][64];
#define lowbit(x) ((x) & -(x))
void init() {
    f[0][0] = 1;
    for (int i = 1; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            if (f[i - 1][j]) {
                f[i][j] += f[i - 1][j];
                f[i][j ^ lowbit(i)] += f[i - 1][j];
            }
        }
    }
}

ll query(ll r) {
    ll t = 0, bw = 0; r += 2;
    for (int b = std::__lg(r); b > 0; b--)
        if ((r >> b) & 1) t += f[b - 1][bw], bw ^= lowbit(b);
    return t;
}

int main() {
    init(); int T;
    read(T);
    while (T--) {
        ll n, odd, l = 0, r = 1e18;
        read(n); odd = n & 1; (n += 2) /= 2;
        while (l < r) {
            ll mid = (l + r) >> 1;
            if (query(mid) >= n) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        printf("%lld\n", (r + odd));
    }
    return 0;
}
```

---

## 作者：Vidoliga (赞：2)

提供一种更为容易理解的方法。

考虑同位置删除这个条件等同没有，我们可以算每个点的 sg 值。

考虑到他是类似取石子游戏，那么 sg 值即为可以走的步数。

考虑到一种分块形式初始 $len=n$，每次将后 $\lceil \frac{len}{2} \rceil$ 个位置分成一块并将其移除序列，将 $len$ 修改为当前序列长度。

不难发现第 $i$ 块数的 sg 值即为 $i$。

不难发现对于一个 $n$ 在二进制位上的表达为 $s_ns_{n-1} \dots s_1 s_0$。

根据上述分块结构，不难得出 sg 为 $i$ 的贡献为 $s_i+s_{i+1} \bmod 2$。

可以二分答案后直接数位 dp。

复杂度 $O(\log ^3 k)$。

```cpp
int k,f[N][N*2][2][2];
int calc(int u){
    memset(f,0,sizeof(f));
    f[60][0][1][0]=1;
    for(int i=60;i;i--) for(int j=0;j<=120;j++){
        for(int s=0;s<2;s++) for(int t=0;t<2;t++){
            int lim=s?(u>>(i-1))&1:1;
            for(int g=0;g<=lim;g++){
                if((t+g)&1) f[i-1][j^(i-1)][s&&g==lim][g]+=f[i][j][s][t];
                else f[i-1][j][s&&g==lim][g]+=f[i][j][s][t];
            }
        }
    }
    int ans=f[0][0][1][0]+f[0][0][1][1]+f[0][0][0][0]+f[0][0][0][1]-1;
    return ans;
}
signed main(){
    k=read();
    int l=0,r=5e14;
    while(l<r){
        int mid=(l+r)>>1;
        if(calc(mid)<k) l=mid+1;
        else r=mid;
    }
    printf("%lld\n",l);
    return 0;
}
////7950
```


---

## 作者：banned_gutongxing (赞：2)

## 思路

找规律。

首先，容易发现这个游戏其实就是基本的硬币游戏。

所以对于如果有 $k$ 个数，它的 SG 函数为 $\displaystyle\bigoplus_{i=1}^n \log_2 \text{lowbit}(i)$。

我们直接对其进行打表找规律，打表代码：
```cpp
const int MAXN = 30010;
int n,MAXQ,f[MAXN];
bitset<MAXN> vis;
int get(int x,int y){
  int tot = 0;
  while(!(x%y)){
    tot++;
    x/=y;
  }
  return tot;
}
int y = 0;
bitset<64> u;
int tot = 0;
signed main(){
  int ans = 0;
  for(int i = 1;i<=65000000000ll;i++){
    ans ^= (int)log2(i&-i);
    if(ans==0){
      cout << ++tot << " " << i << endl;
    }
  }
  return 0;
}
```

输出出来的结果为：

```plant
1 1
2 10
3 11
4 34
5 35
6 40
7 41
8 68
9 69
10 78
11 79
12 102
13 103
14 108
15 109
16 130
......
```

容易发现，对于一个第 $k$ 个可行的数，其答案应该为第其所有二进制位个数异或起来的结果。定义 $kth(i)$ 表示第 $i$ 个可行的数。例如：$kth(11)=kth(1)\oplus kth(2)\oplus kth(8)=1\oplus 10\oplus 68=79$。

所以我们可以将上面的程序稍加修改求出前 $30$ 个二的幂次数最后异或起来即可。（对于上面的程序，跑大约 $11$ 多分钟就能跑出来）

上面的程序：

```cpp
const int MAXN = 30010;
int n,MAXQ,f[MAXN];
bitset<MAXN> vis;
int get(int x,int y){
  int tot = 0;
  while(!(x%y)){
    tot++;
    x/=y;
  }
  return tot;
}
int y = 0;
bitset<64> u;
int tot = 0;
signed main(){
//		read(n);
  int ans = 0;
  for(int i = 1;i<=65000000000ll;i++){
    ans ^= (int)log2(i&-i);
    if(ans==0){
      tot++;
      if((tot&-tot)==tot) cout << tot << " " << i << endl;
    }
  }
  return 0;
}
```

输出为：
```plant
1 1
2 10
4 34
8 68
16 130
32 514
64 1028
128 2050
256 4112
512 8194
1024 16388
2048 32770
4096 131074
8192 262148
......（我就不放完了，代码中见）
```

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do st[++tot]=x%10,x/=10; while(x);
		while(tot){putchar(st[tot--]+'0');}
	}
	void write(int x,char y){write(x);write(y);}
#ifndef int
	void read(long long &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void write(long long x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do st[++tot]=x%10,x/=10; while(x);
		while(tot){putchar(st[tot--]+'0');}
	}
	void write(long long x,char y){write(x);write(y);}
#endif
	int y[60] = {1,10,34,68,130,514,1028,2050,4112,8194,16388
,32770,131074,262148,524290,1048592,2097154, 4194308
,8388610,16777472,33554434,67108868,134217730,268435472,536870914
,1073741828,2147483650,8589934594,17179869188,34359738370
};
	signed main(){
		int k;
		cin >> k;
		int u = 0;
		int ans = 0;
		while(k){
			if(k&1){
				ans^=y[u];
			}
			u++;
			k>>=1;
		}
		write(ans);
		return 0;
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
//	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

---

