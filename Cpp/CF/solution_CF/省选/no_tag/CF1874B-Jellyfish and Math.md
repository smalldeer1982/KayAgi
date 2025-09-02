# Jellyfish and Math

## 题目描述

Jellyfish is given the non-negative integers $ a $ , $ b $ , $ c $ , $ d $ and $ m $ . Initially $ (x,y)=(a,b) $ . Jellyfish wants to do several operations so that $ (x,y)=(c,d) $ .

For each operation, she can do one of the following:

- $ x := x\,\&\,y $ ,
- $ x := x\,|\,y $ ,
- $ y := x \oplus y $ ,
- $ y := y \oplus m $ .

Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR) and $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Now Jellyfish asks you for the minimum number of operations such that $ (x,y)=(c,d) $ .

## 说明/提示

In the first test case, we can do the operation $ y = x \oplus y $ .

In the second test case, it is not possible to change $ (x,y)=(1,2) $ using any sequence of operations.

In the third test case, we can do the operation $ x = x\,\&\,y $ followed by the operation $ y = y \oplus m $ .

## 样例 #1

### 输入

```
10
1 0 1 1 1
3 3 1 2 1
1 6 0 7 1
2 4 4 9 8
21 4 0 17 28
50 50 0 0 39
95 33 1 33 110
138 202 174 64 108
78 340 68 340 461
457 291 491 566 766```

### 输出

```
1
-1
2
-1
-1
2
1
4
1
3```

# 题解

## 作者：wosile (赞：11)

感觉挺有意思的题，写了 2h 多然后没脑子写 C 光荣掉分。

首先这题操作全是位运算所以位之间独立，从而，对于两个不同的位而言，如果他们的初始状态相同，经过的操作也相同，那么结果相同。

也就是说，虽然输入的 $a,\,b,\,c,\,d,\,m$ 有 $30$ 位，但是由于初始状态只和 $a,\,b,\,m$ 有关，一个位的初始状态一共只有 $2^3=8$ 种不同情况。

如果两位对应的 $a,\,b,\,m$ 都相同而 $c,\,d$ 不同，显然无解。

否则，我们可以把 $a,\,b,\,m$ 相同的位全都当成同一位来看，这样 $a,\,b,\,c,\,d,\,m$ 最多只有 $8$ 位了，总状态数就是 $(2^8)^2=2^{16}$。

也就是对于一位的每一种初始状态 $(a=0/1,b=0/1,m=0/1)$，我们要求达到一个目标状态 $(c=0/1,d=0/1)$，或者没有要求。

预处理：跑一遍初始状态为 $x=a=(00001111)_2,\,y=b=(00110011)_2,\,m=(01010101)_2$ 的广搜，也就是 $8$ 位对应的 $a,\,b,\,m$ 分别为 $000,001,010,011,100,101,110,111$。从 $(a,b)$ 到 $(c,d)$ 的最短路就是对于以上 $8$ 种不同的初始状态，目标状态为 $(c,d)$ 的最少操作次数。

对于每一组输入，对于以上每种初始状态，我们都可以处理出一个限制 $(c=0/1,d=0/1)$（当然也可能没有限制），把这些限制按预处理的格式拼成一个状态然后查最短路即可。

注意预处理一下没有限制的情况。可以把这个也当成一种目标状态，总状态数就是 $(4+1)^8<4\times10^5$。

时间复杂度：$16\times(4+1)^8+30T$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int dis[100005];
int from[100005],op[100005];
int f1(int x){
	//f1和f2反了 
	x|=(x&(1<<1))>>1;
	x|=(x&(1<<3))>>1;
	x|=(x&(1<<5))>>1;
	x|=(x&(1<<7))>>1;
	x|=(x&(1<<9))>>1;
	x|=(x&(1<<11))>>1;
	x|=(x&(1<<13))>>1;
	x|=(x&(1<<15))>>1;
	return x;
}
int f2(int x){
	x&=((1<<16)-1)^((x&(1<<1))>>1)^(1<<0);
	x&=((1<<16)-1)^((x&(1<<3))>>1)^(1<<2);
	x&=((1<<16)-1)^((x&(1<<5))>>1)^(1<<4);
	x&=((1<<16)-1)^((x&(1<<7))>>1)^(1<<6);
	x&=((1<<16)-1)^((x&(1<<9))>>1)^(1<<8);
	x&=((1<<16)-1)^((x&(1<<11))>>1)^(1<<10);
	x&=((1<<16)-1)^((x&(1<<13))>>1)^(1<<12);
	x&=((1<<16)-1)^((x&(1<<15))>>1)^(1<<14);
	return x;
}
int f3(int x){
	x^=(x&(1<<0))<<1;
	x^=(x&(1<<2))<<1;
	x^=(x&(1<<4))<<1;
	x^=(x&(1<<6))<<1;
	x^=(x&(1<<8))<<1;
	x^=(x&(1<<10))<<1;
	x^=(x&(1<<12))<<1;
	x^=(x&(1<<14))<<1;
	return x;
}
int f4(int x){
	x^=(1<<9);
	x^=(1<<11);
	x^=(1<<13);
	x^=(1<<15); 
	return x;
}
queue<int>q;
int tmp[15];
int ans[1000005];
int p5[10];
void output(int x){
	for(int i=0;i<16;i++)printf("%d",(x>>i)&1);printf("\n");
}
int main(){
	int T;
	p5[0]=1;
	for(int i=1;i<=8;i++)p5[i]=p5[i-1]*5;
	scanf("%d",&T);
	memset(dis,0x3f,sizeof(dis));
	int S=0b1110010011100100;//初始状态 
	dis[S]=0;
	q.push(S);
	//bfs
	while(!q.empty()){
		int f=q.front();
		q.pop();
		int p1=f1(f),p2=f2(f),p3=f3(f),p4=f4(f);
		if(dis[p1]>dis[f]+1){
			dis[p1]=dis[f]+1;
			q.push(p1);
			from[p1]=f;
			op[p1]=1;
		}
		if(dis[p2]>dis[f]+1){
			dis[p2]=dis[f]+1;
			q.push(p2);
			from[p2]=f;
			op[p2]=2;
		}
		if(dis[p3]>dis[f]+1){
			dis[p3]=dis[f]+1;
			q.push(p3);
			from[p3]=f;
			op[p3]=3;
		}
		if(dis[p4]>dis[f]+1){
			dis[p4]=dis[f]+1;
			q.push(p4);
			from[p4]=f;
			op[p4]=4;
		}
	}
	memset(ans,0x3f,sizeof(ans));
	for(int i=0;i<(1<<16);i++){
		for(int j=0;j<8;j++)tmp[j]=i/((1<<j)<<j)%4;
		int x=0;
		for(int j=0;j<8;j++)x+=tmp[j]*p5[j];
		ans[x]=dis[i];
	}
	//处理没有限制的情况 
	for(int i=0;i<p5[8];i++){
		int pos=-1;
		for(int j=0;j<8;j++)if(i/p5[j]%5==4)pos=j;
		if(pos==-1)continue;
		for(int j=1;j<=4;j++)ans[i]=min(ans[i],ans[i-p5[pos]*j]);
	}
	while(T--){
		int a,b,c,d,m;
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&m);
		for(int i=0;i<8;i++)tmp[i]=4;
		int fl=0;
		for(int i=0;i<30;i++){
			//对应初始状态和目标状态 
			int da=((a>>i)&1);
			int db=((b>>i)&1);
			int dc=((c>>i)&1);
			int dd=((d>>i)&1);
			int dm=((m>>i)&1);
			int id=(dm<<2)+(db<<1)+da;
			int val=(dd<<1)+dc;
			if(tmp[id]!=4 && tmp[id]!=val)fl=1;
			tmp[id]=val;
		}
		if(fl==1){
			printf("-1\n");
			continue;
		}
		int x=0;
		for(int j=0;j<8;j++)x+=tmp[j]*p5[j];
		if(ans[x]==0x3f3f3f3f)printf("-1\n");
		else printf("%d\n",ans[x]);
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：9)

看到这种操作乱七八糟不能直接算的题，可以考虑最短路。

对于 $a, b, c, d, m$ 按位考虑，发现相同的 $(a, b, m)$ 无论如何操作必然还是相同的。

于是考虑对于每个可能的 $(0/1, 0/1, 0/1)$，所有终态有 $(c = 0/1, d = 0/1)$ 或者不确定。这样我们对于一组询问，可以压缩成一个状态，而本质不同状态有 $5^8$ 种。预处理一下最短路即可。然后对于不确定的位，预处理的时候枚举它是什么即可。

时间复杂度 $O(5^8 + t \log V)$。

[code](https://codeforces.com/problemset/submission/1874/226134830)

---

## 作者：___OccDreamer___ (赞：7)

### $\text{Solution}$

题目要求将 $(a,b)$ 变成 $(c,d)$ 的最小操作次数，最朴素的想法：将每个二元组看成一个节点，如果 $(x,y)$ 能通过一种操作变成 $(x',y')$，连一条 $(x,y)$ 到 $(x',y')$ 的有向边，求 $(a,b)$ 到 $(c,d)$ 的最短路。这样状态数太多，铁寄。

考虑如何减少状态数。由于操作都是位运算，考虑**拆位**。设 $a_i$ 表示 $a$ 二进制下第 $i$ 位。那么相同的 $(a_i,b_i,m_i)$ 经过相同的操作一定变成同一个 $(x_i,y_i)$，由于操作是对
全局的，所以我们得到了无解的一种情况：$(a_i,b_i,m_i)=(a_j,b_j,m_j)$ 且 $(c_i,d_i)\ne(c_j,d_j)$。

接下来朴素的想法是将 $(a_i,b_i,m_i,c_i,d_i)$ 看做一个状态，二进制状压一个状态是否存在来转移，这样需要 $32$ 位，也不行。但是基于上述无解的情况，我们知道一个 $(a_i,b_i,m_i)$ 只能对应一个 $(c_i,d_i)$，算上无限制，$(c_i,d_i)$ 一共有 5 种。我们可以用一个 8 位五进制数来描述一个状态，状态数 $5^8$。BFS 出最短路即可。

### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define cout cerr
#define fi first
#define se second
#define debug cout<<"debug"<<endl;
using namespace std;
const int N=4e5+5;
const int P=5;
int T,a,b,c,d,m,flag;
int p[8],S;
int dis[N],q[N],hd,tl;
unordered_map<int,int> mp;
inline int read() {
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=1; ch=getchar();}
	while(isdigit(ch)) {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return f?-x:x;
}
inline int abm(int x,int y,int z) {
	return (x<<2)|(y<<1)|z;
}
inline int cd(int x,int y) {
	return ((x<<1)|y)+1;
}
inline int change(int v,int op) {
	int ret=0;
	for(int i=0;i<8;i++) {
		int t=(v/p[i])%5-1;
		int x=t>>1&1,y=t&1;
		if(op==1) x&=y;
		if(op==2) x|=y;
		if(op==3) y^=x;
		if(op==4) y^=(i&1);
		ret+=p[i]*cd(x,y);
	}
	return ret;
}
inline void init() {
	int s=0;
	p[0]=1;
	for(int i=1;i<=8;i++) p[i]=p[i-1]*P;
	for(int i=0;i<=1;i++) {
		for(int j=0;j<=1;j++) {
			for(int k=0;k<=1;k++) {
				s+=p[abm(i,j,k)]*cd(i,j);
			}
		}
	}
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	hd=1,tl=0,q[++tl]=s;
	while(hd<=tl) {
		int x=q[hd++];
		for(int i=1;i<=4;i++) {
			int y=change(x,i);
			if(dis[y]>dis[x]+1) {
				dis[y]=dis[x]+1;
				q[++tl]=y;
			}
		}
	}
	for(int i=p[8]-1;i>=0;i--) {
		for(int j=0;j<8;j++) {
			int t=(i/p[j])%5;
			if(!t) {
				for(int k=1;k<=4;k++) dis[i]=min(dis[i],dis[i+p[j]*k]);
			}
		}
	}
}
inline void clear() {
	flag=0,S=0;
	mp.clear();
}
int main()
{
	init();
	T=read();
	while(T--) {
		clear();
		a=read(),b=read(),c=read(),d=read(),m=read();
		for(int i=0;i<31;i++) {
			int A=(a>>i)&1,B=(b>>i)&1,C=(c>>i)&1,D=(d>>i)&1,M=(m>>i)&1;
			if(!mp[abm(A,B,M)]) {
				mp[abm(A,B,M)]=cd(C,D);
				S+=p[abm(A,B,M)]*cd(C,D);
			}
			else if(mp[abm(A,B,M)]!=cd(C,D)) {flag=1; break;}
		}
		if(flag||dis[S]>1000000000) puts("-1");
		else printf("%d\n",dis[S]);
	}
	return 0;
}
```

---

## 作者：Euler_Pursuer (赞：5)

这边结合图片给大家更直观地理解这道题做了什么。

首先对于这种二进制操作，一般都需要拆位来看。

拆位之后，解决这道题的关键就在于这样的引理：

> **引理**：对于某一位 $i$ 的三元组 $(a_i,b_i,m_i)$ 来说，如果另一位 $j$ 的三元组 $(a_j,b_j,m_j)$ 与之相等，那么它们最终得到的对应位上的 $(c_i,d_i)$ 必须等于 $(c_j, d_j)$。

> **证明**：对于给定的四个操作，所有位上进行的操作都是同时的，所以只要初始值相等，之后每一步都会相等，一直到最后。

这个引理很显然，看起来没什么价值，关键就在于它为信息压缩，减少无效状态提供了支持。基于此，我们可以将等效位合并起来考虑。

如果我们只考虑**一个**三元组 $(a_i,b_i,m_i)$ 它到达各种 $(c_i,b_i)$ 所需的最少操作数是多少，这个很简单，直接用最短路思想 BFS 遍历所有可行状态即可。

而回到题目需要考虑的是有**若干**不同三元组的集合，每个三元组要到达不同的目标点。那么这个时候我们就思考到关键点了：集合的表示——状态压缩。

只不过通常我们考虑状态压缩都是表示每个状态只考虑是否存在，也就是只有 $0,1$ 两种状态。而这里则需要考虑每种状态是否存在，存在的时候当前又处于哪种状态，用图表示：

![初始态](https://cdn.luogu.com.cn/upload/image_hosting/lk1wxwys.png)

上图展示了所有状态都存在且处于初始态的情况。

这里要注意，每一次操作都会将所有存在的状态同时进行同一类型的操作，据此进行状态转移。

如果我们将所有状态进行编号，将三元组部分作为位数，将二元组以及不存在状态作为每一位的数字，我们就可以将这样的状态集合压缩到 $(4+1)^8<4\times10^5$ 的情况数内。确定所有初始态情况后，采用 BFS 的方式，跑一个最短路，即可得到每个状态的最少操作次数。

因此，我们将这些情况都初始化之后，每次询问时，只需要确定当前询问的状态对应哪个初始态，和哪个目标态，即可查询到达目标状态所需要的最少操作数了。

代码实现：

```cpp
#include <bits/stdc++.h>

using i64 = long long;

const int INF = 1e9;

std::vector<int> pw5(9, 1);
std::vector<int> min_op;

int cd_state(const int &c, const int &d)
{
    return c << 1 | d;
}

void init()
{
    for(int i = 1; i <= 8; i += 1) pw5[i] = pw5[i - 1] * 5;

    min_op.assign(pw5[8], -1);
    std::queue<int> states;

    /// initialize commencement state
    for(int i = 0; i < pw5[8]; i += 1)
    {
        int f = 1;
        for(int abm = 0; abm < 8; abm += 1)
        {
            int cd = i / pw5[abm] % 5, a = abm >> 2, b = abm >> 1 & 1;
            if(cd == 4) continue;
            int c = cd >> 1, d = cd & 1;
            if(c != a || d != b)
            {
                f = 0;
                break;
            }
        }
        if(f)
        {
            min_op[i] = 0;
            states.push(i);
        }
    }

    /// BFS for every state
    while(!states.empty())
    {
        int cur = states.front(), nxt[4] {};
        states.pop();

        for(int abm = 0; abm < 8; abm += 1)
        {
            int cd = cur / pw5[abm] % 5, m = abm & 1;
            if(cd == 4)
            {
                for(int i = 0; i < 4; i += 1) nxt[i] += 4 * pw5[abm];
                continue;
            }
            int c = cd >> 1, d = cd & 1;
            // 1. c &= d
            nxt[0] += cd_state(c & d, d) * pw5[abm];
            // 2. c |= d
            nxt[1] += cd_state(c | d, d) * pw5[abm];
            // 3. d ^= x
            nxt[2] += cd_state(c, d ^ c) * pw5[abm];
            // 4. d ^= m
            nxt[3] += cd_state(c, d ^ m) * pw5[abm];
        }
        for(int i = 0; i < 4; i += 1)
            if(min_op[nxt[i]] == -1)
            {
                min_op[nxt[i]] = min_op[cur] + 1;
                states.push(nxt[i]);
            }
    }
}

void solve()
{
    int nums[5] {};
    for(int i = 0; i < 5; i += 1) std::cin >> nums[i];
    int state = pw5[8] - 1; // all abm do not exist

    for(int i = 0; i < 30; i += 1)
    {
        int a = nums[0] & 1, b = nums[1] & 1, c = nums[2] & 1,
        d = nums[3] & 1, m = nums[4] & 1;
        for(int j = 0; j < 5; j += 1) nums[j] >>= 1;

        int abm = a << 2 | b << 1 | m, cd_ = state / pw5[abm] % 5;
        int c_ = cd_ >> 1, d_ = cd_ & 1;
        if(cd_ == 4) state -= (4 - cd_state(c, d)) * pw5[abm];
        else if(cd_ != cd_state(c, d))
        {
            std::cout << "-1\n";
            return;
        }
    }

    std::cout << min_op[state] << "\n";
}

int main()
{
    init();
    int t;
    std::cin >> t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：Zelotz (赞：3)

[CF1874B](https://codeforces.com/contest/1874/problem/B)

位运算常见思考方式：拆位。

可以发现，对于每一位，能影响其变化方式的只有 $(a,b,m)$ 的当前位的 $0/1$ 状态，所以一个位的初始状态只有 $8$ 种情况。所以对于询问中的不同位上相同的初始状态 $(a,b,m)$ ，其在对应位上的目标状态 $(c,d)$ 必须相同，否则无解。所以，对于每一种初始状态，我们目标达到的状态 $(c,d)$ 共有 $5$ 种（包含一种无要求的）。

预处理，对于每一种的 $(a,b,m)$ 对应的 $(c,d)$，求到其的最短路。每一种 $(a,b,m)$ 对应的 $(c,d)$ 可以看作一个 $8$ 位 $5$ 进制数。单独处理某些位上无要求的状态。时间复杂度可以做到 $\mathcal O(5^8+T\log V)$。

```
const int N = 4e5 + 5; 
int A, B, C, D, M, pow5[10] = {1}, dis[N];
map <int, int> mp;
int abm(int a, int b, int m) {
    return (a << 2) | (b << 1) | m;
}
int cd(int c, int d) {
    return ((c << 1) | d) + 1;
}
int change(int st, int op) {
    int res = 0;
    R(i, 0, 7) {
        int t = (st / pow5[i]) % 5 - 1;
        int x = t >> 1 & 1, y = t & 1;
        if (op == 1) x &= y;
        else if (op == 2) x |= y;
        else if (op == 3) y ^= x;
        else y ^= (i & 1); // m 的 01 状态是 i 的最后一位
        res += pow5[i] * cd(x, y);
    }
    return res;
}
void init() {
    memset(dis, 127, sizeof dis);
    int s = 0;
    R(i, 0, 1) 
        R(j, 0, 1)
            R(k, 0, 1) s += pow5[abm(i, j, k)] * cd(i, j);
    dis[s] = 0;
    queue <int> q; q.push(s);
    while (q.size()) {
        int x = q.front(); q.pop();
        R(i, 1, 4) {
            int y = change(x, i);
            if (dis[y] > dis[x] + 1) {
                dis[y] = dis[x] + 1;
                q.push(y);
            }
        }
    }
    for (int i = pow5[8] - 1; i >= 0; --i) { // 这里倒着枚举满足转移顺序
        R(j, 0, 7) {
            int t = (i / pow5[j]) % 5;
            if (t) continue;
            R(k, 1, 4) dis[i] = min(dis[i], dis[i + pow5[j] * k]);
        }
    }
}
void solve()
{   
    cin >> A >> B >> C >> D >> M;
    int state = 0;
    mp.clear();
    R(i, 0, 30) {
        int a = (A >> i) & 1, b = (B >> i) & 1, c = (C >> i) & 1, d = (D >> i) & 1, m = (M >> i) & 1;
        if (!mp[abm(a, b, m)]) {
            mp[abm(a, b, m)] = cd(c, d);
            state += pow5[abm(a, b, m)] * cd(c, d);
        } else {
            if (mp[abm(a, b, m)] != cd(c, d)) {
                puts("-1");
                return ;
            }
        }
    }
    cout << (dis[state] > 1e9 ? -1 : dis[state]) << '\n';
}
signed main() 
{
    R(i, 1, 8) pow5[i] = pow5[i - 1] * 5;
    init();
    int T = 1; 
    read(T); 
    while (T--) solve();
    return 0;
}
```

---

## 作者：eastcloud (赞：3)

先试图分析四个操作有什么特别的性质，分析无果，于是我们考虑一些比较暴力的做法。

由于每个运算都是位运算，我们可以拆位分析。由于每次操作都是全体操作，因此对于一组相同的 $(a,b,m)$ 操作后的记过一定相同，那么只要有一组 $(a,b,m)$ 相同且 $(c,d)$ 不同就一定无解。

进一步考虑，这个性质也有助于我们降低状态数量，这说明一组输入可以抽象成每个 $(a,b,m)$ 对应了一组终态 $(c,d)$（$(a,b,m)$ 已经确定了初态，初态一定是相同的），由于要考虑空状态，计算可以发现状态数只有 $5^8$，可以直接 bfs 搜出答案。

```cpp
// Problem: Jellyfish and Math
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1874B
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector> 
#include<queue>
#define ll long long
#define N 1000005
using namespace std;
int dis[N],pw[N];
queue<int> q;
int f(int a,int b,int m){
	return (a<<2)|(b<<1)|m;
}
int g(int c,int d){
	return (c<<1)|d;
}
int w(int mask,int b){
	return (mask/pw[b])%5;
}
int work(int mask,int opt){
	int ret=0;
	for(int a=0;a<2;a++)for(int b=0;b<2;b++)for(int m=0;m<2;m++){
		int x=w(mask,f(a,b,m)),c=(x>>1),d=(x&1);
		if(opt==1)c=(c&d);
		else if(opt==2)c=(c|d);
		else if(opt==3)d=(d^c);
		else d=(d^m);
		ret+=pw[f(a,b,m)]*g(c,d);
	}
	return ret;
}
void init(){
	pw[0]=1;
	for(int i=1;i<=10;i++)pw[i]=pw[i-1]*5;
	int S=0;
	for(int a=0;a<2;a++)for(int b=0;b<2;b++)for(int m=0;m<2;m++)S+=pw[f(a,b,m)]*g(a,b);
	memset(dis,0x3f,sizeof(dis));
	q.push(S);dis[S]=0;
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=1;i<=4;i++){
			int v=work(u,i);
			if(dis[v]>dis[u]+1){dis[v]=dis[u]+1;q.push(v);}
		}
	}
	for(int i=0;i<pw[8]-1;i++){
		for(int j=0;j<8;j++){
			if(w(i,j)==4){
				for(int k=1;k<=4;k++){
					dis[i]=min(dis[i],dis[i-pw[j]*k]);
				}
			}
		}
	}
}
int main(){
	init();
	int t;cin>>t;
	while(t--){
		int a,b,c,d,m;cin>>a>>b>>c>>d>>m;
		int ret=pw[8]-1,flag=0;
		for(int i=0;i<=30;i++){
			int A=((a>>i)&1),B=((b>>i)&1),C=((c>>i)&1),D=((d>>i)&1),M=((m>>i)&1);
			if(w(ret,f(A,B,M))!=4 && w(ret,f(A,B,M))!=g(C,D)){flag=1;break;}
			if(w(ret,f(A,B,M))==4)ret-=pw[f(A,B,M)]*(4-g(C,D));
		}
		if(flag || dis[ret]>10000000){cout<<-1<<endl;continue;}
		else cout<<dis[ret]<<endl;
	}
}

```


---

## 作者：iorit (赞：1)

[link](https://www.luogu.com.cn/problem/CF1874B)

给一个暴力做法：

把 $a,b,c,d,m$ 看作集合，画出一个韦恩图如下

![](https://cdn.luogu.com.cn/upload/image_hosting/kh4khev2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

第一，二，三个圆分别表示 $a,b,m$，中间的区域 $2,5$ 就是 $a\ \text{and}\ b$，$4,5$ 就是 $a\ \text{and}\ m$，$5,6$ 就是 $b\ \text{and}\ m$，$5$ 就是 $a\ \text{and}\ b\ \text{and}\ m$。

我们可以以此求出 $7$ 个区域各自表示的数（集合）。

显然这七个区域表示的集合互不相交。那么我们可以用这七个区域中的若干个表示出某个数。

现在 $(x,y)$ 初始在 $(a,b)$，用七个区域表示就是 $(\{1,2,4,5\},\{2,3,5,6\})$。

要到达 $(c,d)$，我们将表示出 $c,d$ 的区域求出来。设 $c,d$ 由集合 $S,T$ 表示，这里 $S,T$ 是由 $1\sim7$ 的元素构成，存在某个元素表示存在韦恩图中某一块。

可以建出图，共 $2^7\times2^7$ 个点，四种操作都能描述出一条边。

从 $(\{1,2,4,5\},\{2,3,5,6\})$ 开始 bfs 就能求出到每个点的最短路。

不妙的是，韦恩图中某些块可能是 $0$。这些块可取可不取，不会影响得到的数结果。

这样每次询问就需要枚举每种集合，复杂度乘上 $2^{14}$。很不妙。

好在能到达的点比较少，即从 $(\{1,2,4,5\},\{2,3,5,6\})$ 能到达的状态数比较少，大概只有 $1500$ 个。

因此枚举每个合法状态统计答案即可。复杂度 $1500q+2^{14}$。

注意 $c,d$ 不一定可以被表示出来，如果与 $7$ 个数中某个数成不完全包含状态即无解。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define sl(n) strlen(n)
#define endline puts("")
#define pii pair<int , int>
#define pr_q priority_queue
#define DEBUG puts("DEBUG.")
using namespace std;
const int N = 1 << 7 | 7;
const int inf = ~0u >> 2;
int dis[N][N],id[N][N];
pii st[3000];
int ct,cnt;
#define x first
#define y second
void bfs()
{
    queue<pii> q;
    q.push( pii(27 , 54) );
    memset(dis , 63 , sizeof dis),dis[27][54] = 0;
    while( !q.empty() )
    {
        pii u = q.front();
        q.pop();
        if( dis[u.x & u.y][u.y] > 1e9 )
            dis[u.x & u.y][u.y] = dis[u.x][u.y] + 1,q.push( pii(u.x & u.y , u.y) );
        if(dis[u.x | u.y][u.y] > 1e9)
            dis[u.x | u.y][u.y] = dis[u.x][u.y] + 1,q.push( pii(u.x | u.y , u.y) );
        if( dis[u.x][u.x ^ u.y] > 1e9 )
            dis[u.x][u.x ^ u.y] = dis[u.x][u.y] + 1,q.push( pii(u.x , u.x ^ u.y) );
        if( dis[u.x][u.y ^ 120] > 1e9 )
            dis[u.x][u.y ^ 120] = dis[u.x][u.y] + 1,q.push( pii(u.x , u.y ^ 120) );
    }
    for(int i = 0;i < 128;i++)
        for(int j = 0;j < 128;j++)
            if( dis[i][j] < 1e9)
                id[i][j] = ++cnt,st[cnt] = pii(i , j);
}
int w[8];
void print(int v)
{
    if(v >= 2)
        print(v / 2);
    putchar(v % 2 + '0');
}
int main()
{
    cin >> ct;
    bfs();
    while(ct--)
    {
        int a,b,c,d,m;
        scanf("%d%d%d%d%d" , &a , &b , &c , &d , &m);
        w[5] = a & b & m;
        w[2] = (a & b) ^ w[5];
        w[4] = (a & m) ^ w[5];
        w[6] = (b & m) ^ w[5];
        w[1] = a ^ w[2] ^ w[4] ^ w[5];
        w[3] = b ^ w[2] ^ w[5] ^ w[6];
        w[7] = m ^ w[4] ^ w[5] ^ w[6];
        int s = 0,t = 0,s0 = 0,t0 = 0;
        for(int i = 1;i < 8;i++)
        {
            // print( w[i] ),putchar('\n');
            if( w[i] )
            {
                if( (w[i] & c) == w[i] )
                    c ^= w[i],s |= 1 << i - 1;
                if( (w[i] & d) == w[i] )
                    d ^= w[i],t |= 1 << i - 1;
            }
            else
                s0 |= 1 << i - 1,t0 |= 1 << i - 1;
        }
        // cout << c << " " << d << endl;
        if(c || d)
            puts("-1");
        else
        {
            int res = inf;
            for(int i = 1;i <= cnt;i++)
                if( (st[i].x & s) == s && (st[i].y & t) == t && (st[i].x - s | s0) == s0 && (st[i].y - t | t0) == t0 )
                    res = min(res , dis[st[i].x][st[i].y] );
            if(res <= 1e9)
                printf( "%d\n" , res );
            else
                puts("-1");
        }
    }
    return 0;
}
```

---

