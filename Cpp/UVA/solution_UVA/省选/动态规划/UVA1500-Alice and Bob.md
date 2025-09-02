# Alice and Bob

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4246

[PDF](https://uva.onlinejudge.org/external/15/p1500.pdf)

# 题解

## 作者：Eon_Sky (赞：6)

$Update$
- 2021.7.30 增加公式与文字之间忘加的空格以及公式错用。

------------

#### 博弈论
复杂度：$O(TN)$，应该是最优复杂度，读入 $O(N)$，判断 $O(1)$，题解首杀。  
此外，也是码量最小的解法。

------------

我们设 $most$ 为除去石子数量为 $1$ 的堆后的最大操作总数，$cnt$ 为石子数量为 $1$ 的堆数。

当拿走只有 $1$ 个石子的堆时，先后手会发生变化，因为这相当于先合并再拿走 $1$，是两次操作，然而你只用一次就做到了，这是这道题的关键。

假设 $cnt$ 为偶数，后手不需要改变先后，则此时无论先手进行啥操作，结果都取决于后手的决定（被动优势，建议和同伴试试）。

- 假设 $most$ 是奇数且 $most\ge3$
	- 则先手的目的就是保证操作最多即可（显然操作数是奇数时，先手必胜），所以先手不会拿走 $1$ （单独一堆）来改变先后手，先手会尽可能合并两个 $1$（单独一堆）来保证对手不能改变先后手，若后手拿走一张 $1$ (单独一堆)，先手也必须拿走一堆保证先后手不变。所以不难看出，先手要想赢的话，每轮操作都会减少两个 $1$ 的数量（合并两个 $1$；后手拿一个，先手拿一个）。
   1. $cnt$ 为奇数，
   		- 为了不让后手拿到被动优势，先手可以将 $1$ （单独一堆）合并到其他不为 $1$ 的堆里去，这时场上的 $1$ 一定是偶数，然而后手必须要改变先后，但是那样他又没有被动优势，要是为了拿到被动优势，又拿不到先后，所以先手必胜。
   2. $cnt$ 为偶数，
   		- 这时先手合并两个 $1$ 即可得到被动优势，后手又像上面说的不能两全其美（改变先后和拿到被动优势），先手必胜。
- 假设 $most$ 是偶数且 $most\ge2$
	- 此时先手一定要改变先后（拿走单个）。
   1. $cnt$ 为奇数，
   		- 此时先手可以直接拿走一张（改变先后），为了挽回，后手只能拿一张（否则相当于投降），拿几轮后最后一定只剩一堆单个的了，控制权此时在先手，先手必赢。
   2. $cnt$ 为偶数，
   		- 此时先手不能两全其美，先手必输。
        
综上所述 $cnt\bmod 2=1$ 或者 $most\bmod 2=1$ 时先手必胜。

但是当 $most\le2$ 时，结论不成立，此时的 $most$ 可以不讨论（因为一定是偶数），就相当于只有 $cnt$ 个 $1$ 单取，此时我们一个个讨论。
1. $0$ 个 $1$
	- 显然，先手必输。
2. $1$ 个 $1$
	- 显然，先手必赢。
3. $2$ 个 $1$
	- 先手合并两个 $1$，先手必赢。
4. $3$ 个 $1$
	- 先手必输，自己推一下即可。
5. $4$ 个 $1$
	- 先手拿走一个，变成情况 $4$，先手必赢。
6. $5$ 个 $1$
	- 先手不想改变先后，合并两个，对手无论怎样一定要取走一张，此时先手拿到被动优势，先手必赢。
    
- 接下来的情况都可以转换成之前出现过的情况，就不往下推了。

综上所述
- 在 $most>2$ 的前提下 $cnt\bmod 2=1$ 或者 $most\bmod 2=1$ 时先手必胜。
- 在 $most\le2$ 的前提下 $cnt\bmod 3=0$ 先手必输。

$\text{Code:}$

```cpp
#include <bits/stdc++.h>

using namespace std;

int T;

int n;

int main() 
{
    scanf("%d",&T);
    for(int i=1;i<=T;i++)
	{
        scanf("%d",&n);
        int most=0,cnt=0;
        for(int x,j=1;j<=n;j++)
		{
            scanf("%d",&x);
            if(x==1)
				cnt++;
            else 
				most+=x+1;
        }
		most--;
        if(most<=2)
		{
            if(cnt%3)
				printf("Case #%d: Alice\n",i);
            else 
				printf("Case #%d: Bob\n",i);
        }
        else
			if(cnt%2==1||most%2==1)
				printf("Case #%d: Alice\n",i);
        else 
			printf("Case #%d: Bob\n",i);
    }
    return 0;
}
```

---

## 作者：Strelitzia (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/UVA1500)

---

确实没想出来，嫖了题解，现在写来记录生活。

对于没有 $1$ 的数来说，取的次数不是数的和，是 $\text{sum + n - 1}$ 次，毕竟可以合并呀。

如果有 $1$，取了这个 $1$ 后就不能合并了，所以有 $1$ 的要讨论一下。

解释这四个搜索什么意思：

>dfs(x - 1,y) 表示取一个 1

>dfs(x,y - 1) 表示从可行操作中用一次操作

>dfs(x - 1,y - 1) 表示合并一个 1 到 y 中

>dfs(x - 2,y + 2 + (y ? 1 : 0)) 表示合并两个 1

```cpp
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<typename T>void Swap(T &x,T &y) {T z = x;x = y;y = z;}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}
template<typename T>T Abs(T x) {return x < 0 ? -x : x;}

const int N = 50;

int f[N][N * 1000];

int T,n,turn;

int dfs(int x,int y) {
	if (~f[x][y]) return f[x][y];
	if (x == 0)   return f[x][y] = y & 1;
	if (y == 1)   return f[x][y] = dfs(x + 1,0);
	
	return f[x][y] = Min(Min(dfs(x - 1,y),y ? dfs(x,y - 1) : 114),Min(x && y ? dfs(x - 1,y + 1) : 514,x >= 2 ? dfs(x - 2,y + 2 + (y ? 1 : 0)) : 1919810)) == 0;
    
}

int main () {
	read(T);
	memset(f,-1,sizeof f);
	while (T --) {
		read(n);
		int cnt = 0,sum = 0,x;
		for (int i = 1 ; i <= n ; ++ i) {
			read(x);
			if (x == 1) cnt ++;
			else sum += x;
		}
		if (sum) sum += n - cnt - 1;
		printf("Case #%d: ",++ turn);
		puts(dfs(cnt,sum) ? "Alice" : "Bob");
	}
	return 0;
}
```

---

## 作者：chihik (赞：2)

这道题的状态挺难设计的。。。

令 $s$ 为石子的总数，那么操作次数最多为 $s+(n-1)$ 

如果石子数量全不为一，那么先手必胜的条件为 $s+(n-1)$ 为奇数，因为他一定可以保证操作 $s+(n-1)$ 次。

反之后手必胜。

问题在于石子数量可能为 $1$ ，这时去掉这颗石子便无法合并。

所以状态应该与石子数量为 $1$ 的堆数，石子数量不为 $1$ 的堆的最大操作次数有关。

令 $SG(a,b)$ 表示剩下 $a$ 堆数量为 $1$ 的石子堆，其余石子堆能操作 $b$ 次的 $SG$ 函数值。

那么后继状态有五种种：

- 在石子数不为 $1$ 的石子堆取掉一颗石子
- 合并两堆不为 $1$ 的石子堆
- 取掉一堆为 $1$ 的石子堆
- 将两堆为 $1$ 的石子堆合并
- 将一堆为 $1$ 和一堆不为 $1$ 的石子堆合并

边界条件就是最开始讲的。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 50 , MAXV = MAXN * 1000;
int T , n;

int SG[ MAXN + 5 ][ MAXV + 5 ];
int dfs( int Cnt1 , int oper ) {
	if( SG[ Cnt1 ][ oper ] ) return SG[ Cnt1 ][ oper ];
	if( oper == 1 ) return SG[ Cnt1 ][ oper ] = dfs( Cnt1 + 1 , 0 );
	if( Cnt1 == 0 ) return SG[ Cnt1 ][ oper ] = oper % 2;
	
	int Mex = 2;
	if( Cnt1 ) Mex = min( Mex , dfs( Cnt1 - 1 , oper ) );
	if( oper ) Mex = min( Mex , dfs( Cnt1 , oper - 1 ) );
	if( Cnt1 >= 2 ) Mex = min( Mex , dfs( Cnt1 - 2 , oper + 2 + ( oper ? 1 : 0 ) ) );
	if( Cnt1 && oper ) Mex = min( Mex , dfs( Cnt1 - 1 , oper + 1 ) );
	return SG[ Cnt1 ][ oper ] = Mex == 0 ? 1 : 0;
}

int main( ) {
	scanf("%d",&T);
	for( int t = 1 ; t <= T ; t ++ ) {
		printf("Case #%d: ", t );
		
		int Cnt1 = 0 , oper = 0;
		scanf("%d",&n);
		for( int i = 1 , x ; i <= n ; i ++ ) {
			scanf("%d",&x);
			if( x == 1 ) Cnt1 ++;
			else oper += x + 1;
		}
		if( oper ) oper --; //合并次数=堆数-1
		puts( dfs( Cnt1 , oper ) ? "Alice" : "Bob" );
	}
	return 0;
} 
```

---

## 作者：zsc2003 (赞：2)

定义$dp[i][j]$表示还剩i个单独为一堆的，剩余还能拿走j次

其中$dp$数组要开$n*suma_i$即$60*51000$

对于是1的堆可以单独处理

而对于其它堆,需要直接加起来比奇偶,

最后如果等于$dp[i][j]=1$那么就是先取的胜，否则就是后取的剩

于是只有是$1$的堆才会影响最后的结果,

如果这个堆大于$1$,

那个此时会胜的人,一定会先把这些堆先合,最后再比奇偶

而要败的人没有任何办法,此时他就想办法改变$1$的堆,

因为合并$1$的堆相当于操作两次,会变最后的结果,

这样所有的人,都要抢是$1$的堆是$1$的堆,

总共有$4$种操作,

第$1$种$:$是直操拿是$1$的堆;

$2:$合并$1$的堆到非1的堆;

$3:$取不是$1$的堆;

$4:$合并两个非$1$的堆;

第$4$种又有$2$种情况,

第一全都是$1$,这时,只能加$2$不能合并到非$1$的堆,

第二有非$1$的堆,那么,两个$1$的堆加再合到一个非$1$的堆加$3$


下面附上本人的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//读入优化
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=60,VAL=51000;//VAL=n*sumai
int n,T,sum,tot;
int a[N];
int dp[N][VAL];
bool dfs(int n,int p)
{
	if(dp[n][p]!=-1)
		return dp[n][p];
	if(p==1)
		return dp[n][p]=dfs(n+1,0);
	if(n>0&&!dfs(n-1,p))//拿走一个单独为一堆的
		return dp[n][p]=1;
	if(p>1&&!dfs(n,p-1))//从多个为一堆中取走一个 
		return dp[n][p]=1;
	if(n>0&&p>0&&!dfs(n-1,p+1))//将一个单个为一堆的并入另外一堆 
		return dp[n][p]=1;   
	if(n>=2)//???为什么 
		if((p>0&&!dfs(n-2,p+3))||(p==0&&!dfs(n-2,p+2)))
			return dp[n][p]=1;
	return dp[n][p]=0;
}
int main()
{
	memset(dp,-1,sizeof(dp));
	T=read();
	for(int t=1;t<=T;t++)
	{
		printf("Case #%d: ",t);
		n=read(),sum=0,tot=0;//tot每堆只有一个的堆数 
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			if(a[i]==1)
				tot++;
			else
				sum+=a[i]+1;
		}
		if(sum)sum--;	
		puts(dfs(tot,sum)?"Alice":"Bob");
	}
	return 0;
}
```

---

## 作者：_Cheems (赞：1)

更新了下题解。
### dp 做法
首先，令 $S=sum+n-1$。这是最大操作数。

然后有个 simple 的想法：每次操作会改变 $S$ 奇偶，如果 $S$ 是奇数，先手必胜；反之后手必胜。

但是很容易被 hack，原因在于没有考虑 $a_i=1$ 的情况。在此情况下可以移走 $a_i=1$ 的堆将其清零，然后 $S$ 奇偶不变。

不过，对于 $\forall a_i>1$ 的情况，结论依旧成立。胜者只要每次将场上 $a=1$ 的堆合并，那么败者怎么操作都无法将某一堆删成 $0$。即最优策略下每次操作都会改变奇偶。

这启示我们按照将所有石子分为 $a_i=1$ 和 $a_i>1$ 的两部分。定义 $f_{cnt,S}$ 表示 $cnt$ 个 $a_i=1$，$a_i>1$ 部分的 $sum+n-1$（即最大操作数）为 $S$ 时，先手是否必胜。

然后考虑 $f_{cnt,S}$ 转移到哪些局面：

1. 只对 $a_i>1$ 的进行操作，删除或合并都一样：$f_{cnt,S-1}$。这里无需考虑 $2$ 堆挪去一个石子变成 $1$ 堆，因为根据先前讨论赢家可以合并从而让这个 $1$ 堆无法被清空。
 
2. 删除 $a_i=1$ 的：$f_{cnt-1,S}$。

3. 合并两个 $a_i=1$ 的，注意特判 $S=0$：$f_{cnt-2,S+2+[S>0]}$。

4. 合并 $a_i=1$ 和 $a_i>1$：$f_{cnt-1,S+1}$。

然后注意下边界：

1. $cnt=0$：必胜条件为 $S$ 是奇数。
2. $cnt>0$ 且 $S=1$，此时把 $S$ 中这个 $1$ 堆挪去会导致两次变化,所以需要返回 $f_{cnt+1,0}$。

将上述过程用记忆化搜索实现即可。复杂度 $O(n\sum a)$。

#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MIN(a, b) a = min(a, b)
const int N = 55, M = 50005;
int T, n, a[N], f[N][M];

inline int dfs(int cnt, int S){
	if(f[cnt][S] != -1) return f[cnt][S];
	if(!cnt) return f[cnt][S] = (S & 1);
	if(S == 1) return f[cnt][S] = dfs(cnt + 1, 0);
	int res = 2;
	if(cnt) MIN(res, dfs(cnt - 1, S));
	if(cnt >= 2) MIN(res, dfs(cnt - 2, S + 2 + (S ? 1 : 0)));
	if(S) MIN(res, dfs(cnt, S - 1));
	if(cnt && S) MIN(res, dfs(cnt - 1, S + 1));
	return f[cnt][S] = (res == 0 ? 1 : 0);
}
signed main(){
	memset(f, -1, sizeof f);
	cin >> T;
	for(int t = 1; t <= T; ++t){
		scanf("%d", &n);
		int _cnt = 0, _S = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", &a[i]);
			if(a[i] == 1) ++_cnt;
			else _S += a[i] + 1;
		}
		_S -= (_S > 0);
		printf("Case #%d: ", t);
		if(dfs(_cnt, _S)) puts("Alice");
		else puts("Bob");
	}
	return 0;
}
```
### 大力推理做法
我们记 $sum$ 表示只对 $\ge 2$ 的石子堆操作的最大操作数，$cnt$ 表示 $=1$ 的石子堆数量。

* 结论 $1$：若 $sum>2,2\mid sum,2\mid cnt$，则后手必胜。

证明：考虑归纳，首先 $cnt=0$ 时结论成立。其它情况下先手无论如何操作，后手都能将其归约到上述条件。就算先手把一个 $2$ 堆移成 $1$ 堆，由于 $sum>2$ 所以必然存在另一个 $\ge 2$ 的堆，合并过去即可，游戏局数有限所以后手必胜。

* 结论 $2$：若 $sum>2$，后手必胜当且仅当 $2\mid sum,2\mid cnt$。

证明:

1. $2\nmid sum,2\mid cnt$：若 $cnt=0$ 显然，否则先手将两个 $1$ 堆合并，由结论 $1$ 可知先手必胜。

2. $2\nmid sum,2\nmid cnt$：只需将一个 $1$ 堆合并到 $\ge 2$ 堆上即可。

3. $2\mid sum,2\nmid cnt$：将一个 $1$ 删掉即可。

* 结论 $3$：若 $sum=0,2$，后手必胜当且仅当 $3\mid cnt$。

证明：归纳，记 $cnt=3k+p$。

1. $k=0$: 手玩下即可发现结论成立。
2. $k>1$：当 $p=0$ 时枚举所有情况可知后手必胜；当 $p=1$ 时先手将 $1$ 堆删去即可；$p=2$ 时先手合并 $1$ 堆即可。

复杂度 $O(n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int T, n, a, sum, c1, c2;

signed main(){
	cin >> T;
	while(T--){
		scanf("%d", &n), sum = c1 = c2 = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", &a);
			if(a > 1) sum += a, ++c2;
			else ++c1;
		}
		sum += max(0, c2 - 1);
		if(sum > 2)
			if(sum % 2 == 0 && c1 % 2 == 0) puts("NO");
			else puts("YES");
		else 
			if(c1 % 3) puts("YES");
			else puts("NO");
	}
	return 0;
}
```

---

## 作者：cly312 (赞：0)

1. **状态表示**：
  - 使用两个变量来表示当前游戏的状态：$a$ 表示包含 $1$ 个石子的堆的数量，$b$ 表示包含多于 $1$ 个石子的堆的可操作次数。

2. **游戏策略**：
- 1. 从包含多个石子的堆中取走一个石子，这会减少 $b$。
- 2. 从包含 $1$ 个石子的堆中取走一个石子，这会减少 $a$。
- 3. 合并两个包含 $1$ 个石子的堆，变成一个包含多个石子的堆。这会减少 $a$ 并增加 $b$。
- 4. 将一个包含 $1$ 个石子的堆合并到包含多个石子的堆中，这会减少 $a$ 并增加 $b$。

3. **临界情况**：
- 如果当前所有堆中石子数量都为 $1$（$a > 0$ 且 $b = 0$），那么最终会剩下一个石子，这时轮到操作的玩家输。
- 如果所有堆都包含多个石子，且可操作次数 $b$ 为奇数，那么先手玩家有必胜策略。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int n,f[50][N];
//f[i][j]表示有i个1，大于1的堆有j此操作。
int dfs(int a,int b) {
	if(f[a][b]!=-1)return f[a][b];//记忆化
	if(!a)return f[a][b]=b%2;
	//若全是大于1的堆，b为奇数则先手必赢
	if(b==1)return dfs(a+1,0);//没有大于1的堆
	int t=2;
	if(b)t=min(t,dfs(a,b-1));//取走大于1的堆中一个元素
	if(a)t=min(t,dfs(a-1,b));//取走1的堆中一个元素
	if(a>1)t=min(t,dfs(a-2,b+2+(b?1:0)));//将两个1合并
	if(a&&b)t=min(t,dfs(a-1,b+1));//1合并到大于2的堆中
	if(!t)f[a][b]=1;
	else f[a][b]=0;
	return f[a][b];
}
int main() {
	int T;
	cin>>T;
	memset(f,-1,sizeof(f));
	for(int k=1; k<=T; k++) {
		int a=0,tot=0;
		cin>>n;
		for(int i=1; i<=n; i++) {
			int x;
			cin>>x;
			if(x==1)a++;
			else tot+=x+1;
		}
		if(tot)tot--;
		//可操作数==堆数+求和（堆中元素数）-1
		cout<<"Case #"<<k<<": ";
		if(dfs(a,tot))
			cout<<"Alice"<<endl;
		else cout<<"Bob"<<endl;
	}
}
```

---

