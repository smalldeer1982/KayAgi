# Play with Power

## 题目描述

Masha 和 Stas 正在玩一个游戏。在游戏的开始，给出一个数  $n$，同时有两个正整数  $a,b$，初始时满足 $a^b\le n$。

Masha 先手。每一回合，玩家要将 $a,b$ 的其中一个数加上  $1$，但不能使 $a^b>n$，否则该玩家输。

现在，Masha 想知道，假如两人都使用最优策略，对于同一个 $n$ 和不同的 $a,b$，谁将获胜呢？


## 说明/提示

#### 数据规模与约定

- 对于  $30\%$ 的数据，有  $1\le n\le 2\cdot10^3$。
- 对于  $100\%$ 的数据，有  $1\le n\le 10^8$， $1\le t\le 100$， $1\le a,b,a^b\le n$。

## 样例 #1

### 输入

```
9 
2 
2  2 
1  4 ```

### 输出

```
Masha 
Missing```

# 题解

## 作者：Shallowy (赞：31)

~~**这么有趣的一道题居然没人发题解？**~~

乍一看是博弈论......

注意到N<=10^8,那么当Ai不小于2时2人轮流操作，最多30来次(log₂(n)).

所以我们很容易想到类似于dp的思想，好吧其实是记忆化搜索...


**设f(a,b)表示当前值a,b的状态，f(a,b)=0表示必败,=1表示平局,=2表示必胜，则f(a,b)的值可以由f(a+1,b)和f(a,b+1)推过来。**

即：对于f(a,b)：

- 若a^b>n，则对于当前的玩家来说，他是赢了的（上一次操作使得a^b>n为真），即；

- 否则，调用f(a+1,b)和f(a,b+1):

**方便起见，设n1=f(a+1,b),n2=f(a,b+1).**


**1. n1=n2=2.......==>f(a,b)=0;**

**2. n1=0或n2=0..==>f(a,b)=2;**

**3. 其余情况..........==>f(a,b)=1.**

还有，毕竟是记忆化搜索，得另开一个数组g[i][j]表示i^j，当i^j>n是g[i][j]=-1.

# ~~然而没有那么那么简单~~

**注意点：**

**1. 保险一点（我也没试过）最好开long long；**

**2. 用快速幂(不要告诉我你没想到要用快速幂)求幂的过程中还会超long long，其实是超n，此时应直接返回-1，不然会超范围；**

**3. 但是还是会超long long......**

**....极限数据：当a=1或b=1时会出现死循环或是爆long long，具体解决方法见代码**

**4. ~~右上角点个赞谢谢~~~**

附上丑陋的  c++代码


```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#define ll long long
using namespace std;
ll rd(){ll x=0; char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x;
}   //毫无用处的读优...
ll n=rd(),t=rd(),a,b,g[35][10005];
int c;
ll max(ll a,ll b){return a>b?a:b;}
ll p(ll a,ll x){ll ans=1;
    if(a>n) return -1;//不判的话可能一乘就炸了...
    while(x){
        if(x&1) ans*=a;
        a*=a,x>>=1;
        if(ans>n) return -1;
    }
    return ans;
}    //快速幂
inline int f(ll a,ll b){
    if(b>30) return 1;//对于a=1,如果直接判a是否为1,那在第一次调用f时会返回错误的答案1，另外，先手可以通过使a+1来让后手输
    if(!g[b][a]) g[b][a]=p(a,b);//试过删掉g，好像T掉了...
    if(!~g[b][a]) return 2;//~就是!=-1，下同
    int n1=f(a+1,b),n2=f(a,b+1);
    if(n1==2&&n2==2) return 0;//n1=n2=2
    if(!n1||!n2) return 2;//n1=0或n2=0
    return 1;//其余情况
}
int main(){
    double ss=sqrt(n);
    while(t--){
        a=rd(),b=rd();
        if(a>ss) c=b==1?(n-a&1?2:0):0;//对于特别大的a，快速幂中乘一次就没了...所以在p之前要先进行判断
        else c=!~p(a,b)?0:f(a,b);//a^b>n,必输（额，好像题目中说了不会的...O__O）
        switch(c){
            case 0:printf("Stas\n"); break;
            case 1:printf("Missing\n"); break;
            case 2:printf("Masha\n"); break;
        }
    }
    return 0;
}
```
提前祝大家：
  
  
╭┘└┘└╮

└┐．．┌┘────╮

╭┴──┤          ├╮

│ｏｏ│          │ ●

╰─┬─╯          │

HAPPY   牛   YEAR

        
——蒟蒻:Je


---

## 作者：一只小兔子 (赞：6)

~~是个绿题~~

博弈论，记忆化搜索所有情况先手是否获胜。（毕竟 $n$ 不变）

令 $f(a,b)$ 表示以 $a^b$ 开始的游戏先手是否必胜：

( 1 表示必胜， 2 表示必败， 3 表示**只能**平局 )

转移：（从 $f(a+1,b)$ 和 $f(a,b+1)$ ）

1. 若两个状态有一个必败，则此状态必胜；

2. 若两个状态均必胜，此状态必败；

3. **否则，此状态平局**

---------

本题不难，但细节多：

1. 当 $a^b>n$ 时， $f(a,b)=1$ （感性理解，这是从合法状态转移到的，即后手“无路可走必须犯规”，此时先手必胜）

2. $a=1$ ，当 $b$ 大到不能给 $a$ 加一时，平局。（边界条件1，两人只能无限给 $b$ 加一）

3. $b=1$ ，当 $a$ 大到不能给 $b$ 加一时，两人只能一个一个给 $a$ 加一，谁先到 $n$ 谁胜利。（边界条件2）

为防止爆 int 或 long long 可以用数学库的 pow(a,b) 判断。

代码：
```
#include<cstdio>//P1839
#include<cmath>
int n,g[10201][30];
int f(int a,int b){
	if(a==1&&b>27)return 3;
	if(b==1&&a>n/a)return ((n-a)&1)?1:2;
	if(g[a][b])return g[a][b];
	if(n<pow(a,b))return 1;
	int ta=f(a+1,b),tb=f(a,b+1);
	if(ta==1&&tb==1)return g[a][b]=2;
	else if(ta==2||tb==2)return g[a][b]=1;
	else return g[a][b]=3;
}
char st[4][8]={"Cheated","Masha","Stas","Missing"};
int main(){
	int t,a,b;scanf("%d%d",&n,&t);g[1][27]=3;
	while(t--){scanf("%d%d",&a,&b);printf("%s\n",st[f(a,b)]);}
}
```

---

## 作者：yuruilin2026 (赞：3)

一道不是很水的黄题，或许是因为我太菜了？\
思路：记忆化搜索。\
令 $dp_{i,j}$ 代表 $a=i$ 且 $b=j$ 时的胜负情况。\
其中 $1$ 表示赢，$2$ 表示输，$3$ 表示平局。\
令 $sub1=dp_{i+1,j}$，$sub2=dp_{i,j+1}$。\
可得：
1. 若 $n<i^j$，则 $dp_{i,j}=1$。\
   解释：这个应该不用解释。
2. 若 $sub1=1$ 并且 $sub2=1$，则 $dp_{i,j}=2$。\
   解释：如果两种情况都必胜，则对手必胜，自己必败。
3. 若 $sub1=2$ 或者 $sub2=2$，则 $dp_{i,j}=1$。\
   解释：如果有一个情况能让下一个人输，那就走那里，对手必败，自己必胜。
4. 如果都不成立，则 $dp_{i,j}=3$。

还需要注意一些细节，写在代码注释里了。\
好了，上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long dp[114510][540],a,b,n,t;
long long sou(long long x,long long y){
	if(x < 114510 && y < 540 && dp[x][y] != 0) return dp[x][y];//防火防盗防RE 
	if(x == 1 && y > 27){
		//dp[x][y] = 3;
		//一直是1的情况 
		//这种情况访问 dp[x][y] 有可能 RE 
		return 3;
	}
	if(y == 1 && x > n / x){
		//dp[x][y] = ((!((n - x) & 1)) + 1);
		//看谁先到 n 谁输 
		//这种情况访问 dp[x][y] 有可能 RE 
		return ((!((n - x) & 1)) + 1);
	}
	if(n < pow(x,y)){
		//dp[x][y] = 1;
		//这种情况访问 dp[x][y] 有可能 RE 
		return 1;
	}
	long long sub1 = sou(x+1,y),sub2 = sou(x,y+1);
	if(sub1 == 1 && sub2 == 1){
		dp[x][y] = 2;
		return 2;
	}
	if(sub1 == 2 || sub2 == 2){
		dp[x][y] = 1;
		return 1;
	}
	dp[x][y] = 3;
	return 3;
}
int main(){
	cin.tie(0);
	dp[1][27] = 3;//初始化 
	cin >> n >> t;
	while(t--){
		cin >> a >> b;
		if(sou(a,b) == 1) cout << "Masha" << endl;
		else if(sou(a,b) == 2) cout << "Stas" << endl;
		else if(sou(a,b) == 3) cout << "Missing" << endl;
	}
	return 0;
}
```

---

## 作者：wuzhexu (赞：3)

### 思路解析

这是一道明显的搜索和博弈论（不过这道题的博弈论很简单）。

还有就是，本题解探讨的必胜必败状态都是基于第一个人的视角。

从简单的递归终止条件开始写起（不管怎么加，都会最终演变成以下三种情况）。

第一种情况，当 $a=1$ 时，$b$ 足够大以至于如果再加 $a$ 就会立刻超过 $n$。此时根据两人的最优思路，是一直加 $b$，又因为 $a=1$，后果是平局了。

第二种情况，当 $b=1$ 时，也就是 $a$ 的指数为 $1$ 时，同时要保证 $a^2$ 比 $n$ 大，因为两人是交替相加，所以当 $(n-1) \bmod 2=1$ 时，第一个人必胜，反之，第二个人必胜。

最后一种情况，如果当前 $a^b > n$ 则第一个人必胜（这就不用说了吧）。

好，接下来开始搜索啦。

先开个数组。

有两种转移的方法，加 $a$ 或加 $b$，所以分类。

最后是回溯，如果两种选择都是上文提及的第一人必胜的话，则这状态必败（第二个人只要加另外一个变量就行了，这样第一个人当前状态将没有选择）。

如果两个选择都必败或任意一个必败，则这一状态必胜（因为第二个人将没有选择）。

最后就是输入和输出，很简单，就不细说了（大体就是在用一个数组要输出的三个字符串，根据返回值返回的下标打印内容）。

### 示例代码

之所以要把数组的那一位（见主函数）赋值，是因为递归终止条件里没有状态转移。这里之前的大佬都没说。

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;

#define int long long

int dp[20005][101];

int dfs(int a,int b){
	
	if(a==1 && b>27) return 3;
	
	if(b==1 && a>n/a){
		if((n-a)%2==1) return 1;
		else return 2;
	}
	
	if(n<pow(a,b)) return 1;
	
	int a_range=dfs(a+1,b);
	int b_range=dfs(a,b+1);
	
	if(a_range==1 && b_range==1){
		dp[a][b]=2;
		return 2;
	}
	
	else if(a_range==2 || b_range==2){
		dp[a][b]=1;
		return 1;
	}
	
	else {
		dp[a][b]=3;
		return 3;
	}
}

string st[4]={"Masha","Stas","Missing"};

signed main(){
	int t,a,b;
	cin>>n>>t;
	
	dp[1][27]=3;
	
	while(t--){
		cin>>a>>b;
		int i=dfs(a,b);
		cout<<st[i-1]<<endl;
	}
}
```

---

## 作者：cccz (赞：3)

我的思路和大佬差不多，也是记忆化搜索。

 $ans_{i,j}$ 数组用来存储当初始 $a$，$b$ 为 $i$，$j$ 时，先手的人的胜负情况，$1$ 表示先手的人赢，$2$ 表示先手输，$3$ 表示平局。

 $f(a + 1,b)$ 和 $f(a,b + 1)$ 表示下一个人胜负情况，若两个均胜，则本次先手的人必输，若有至少一个为负，因为是最优策略，则本次必胜。

当 $a = 1$ 时，因为 $a$ 的任何次幂都为 $1$，所以两个人会无限的执行 $b + 1$，只能平局。

当 $a = 2$ 时，如果 $b > 27,a^b$ 超过 $n$ 最大值，也要判断一下。

希望上述内容可以帮助大家理解。

最后，献上蒟蒻的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,t,a,b;
int ans[114514][30];
int dfs(int x,int y){
	if(x==1&&y>27){
		return 3;// 当b>27时，2^27>1e8，所以只能加b，但是1的任何次幂都是1，所以只能平局 
	}
	if(y==1&&x>n/x){
		return ((n-x)&1)?1:2;//当b=1时，若a^2>n，则只能a+1，若n-a为偶数，则 S胜，反之M胜 。
	}
	if(ans[x][y]){
		return ans[x][y];//已经有了这个状态，直接返回即可 。
	}
	if(n<pow(x,y)){
		return 1;
	}
	int xx=dfs(x+1,y),yy=dfs(x,y+1);  //题解里面已经说了。
	if(xx==1&&yy==1){
		return	ans[x][y]=2;
	}else if(xx==2||yy==2){
		return ans[x][y]=1;
	}else{
		return ans[x][y]=3;
	}
}
signed main(){
	cin>>n>>t;
	ans[1][27]=3;
	for(int i=1;i<=t;i++){
		scanf("%d%d",&a,&b);
		int temp=dfs(a,b);
		if(temp==1){
			printf("Masha\n");
		}else if(temp==2){
			printf("Stas\n");
		}else if(temp==3){
			printf("Missing\n");
		}
	}
	
	return 0;
}
```

---

## 作者：zhz_2013 (赞：1)

分几种情况讨论：  
第一种：$a ^ {b} $ 中 $a = 1$，$b > 27 $，此时如果 $a + 1$ 的话，$2 ^{b}$ 无论如何都 $> 10^{8}$，所以只能增加 $b$，但 $1^{b}$ 永远是 $1$，所以平局，输出 ```Missing```。  
第二种：$a^{b}$ 中 $b = 1$，$a^{2} > n$，如果 $b + 1$ 的话，就超过 $n$ 了，只能增加 $a$，比谁先增加到$n$。此时看 $n - a$ 的奇偶性，奇数输出 ```Masha```，偶数输出 ```Stas```。  
第三种：$n < a^{b}$，此时返回。  
第四种：记忆数组 $ans_{a,b}$ 记录过答案，直接返回答案。  
如果以上四种条件都不满足：  
设 $ans1$ 为 $a + 1$ 时的胜负结果， $ans2$ 为 $b + 1$ 时的胜负结果，则：如果 $ans1$ 和 $ans2$ 都为 $0$，也就是 $a+1$ 和 $b+1$ 都必败，则这个状态必胜，输出 ```Stas```。如果 $ans1$ 和 $ans2$ 其中一个为 $1$，也就是其中一个必胜，那么这个状态必败，输出 ```Masha```。否则平局，输出 ```Missing```。  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n,t;
int a,b;
int ans[10005][100];  //记忆化数组，存储每一次的答案
string out[3]={"Masha","Stas","Missing"};  //输出数组
int dfs(int a1,int b1){//a1就是底数，b1就是指数。
	if(a1==1&&b1>27){//如果不够给a1增加1的话，就一直是1，平手。
		return 2;
	}
	if(b1==1&&a1*a1>n){//指数没法增加，比谁先把底数增加到n。
		return !((n-a1)&1);
	}
	if(n<pow(a1,b1))return 0;//边界，a1^b1>=n。

	if(ans[a1][b1])return ans[a1][b1];//记录过了
//注：return x=y相当于把x赋值成y再return y
	int x=dfs(a1+1,b1),y=dfs(a1,b1+1);
	if(!x&&!y){//两个都必败，这个情况必胜。
		return ans[a1][b1]=1;
	}
	if(x==1||y==1)return ans[a1][b1]=0;//其中有一个必胜，那么必败。
	return ans[a1][b1]=2;//平局。
} 
signed main(){
	cin>>n;
	cin>>t;ans[1][27]=2;//初始化边界。
	while(t--){
		cin>>a>>b;
		cout<<out[dfs(a,b)]<<endl;//直接输出
	}
	return 0;
}

```

---

## 作者：Genius_Star (赞：1)

### 题意：
两个人根据 $n,a,b$，轮流将 $a$ 或者 $b$ 加一，但是不能使 $a^b>n$，如果当前玩家无法加一，则当前玩家输掉游戏。

Masha 先手，问如果两个人都使用最优策略，对于同一个 $n$ 和不同的 $a,b$，谁将获胜呢？

### 思路分析：

根据题目要求，每一回合只能将 $a$ 或 $b$ 加上 $1$，因此，在加 $1$ 之后，需要判断 $a^b$ 是否大于 $n$，如果大于则另一方胜利。

由此可以得出一个非常简单的记忆化搜索，具体思路如下：

- 状态表示：由于 $a$ 和 $b$ 的范围是 $1\le a,b\le n$，因此可以用一个二维的记忆化数组 $f[i][j]$ 表示在当前 $(a,b)$ 的情况下，先手是否必胜，如果必胜返回 $1$，否则返回 $0$。
- 状态计算：先手的胜负是通过后手的输赢来判断的。如果后手必输，那么先手必胜。如果后手必胜，那么先手必输。因此，状态计算公式为：

$f[i][j]=
\begin{cases}
1& a^b\geq n\\
\text{先手必胜} & f[i+1][j]=0 \text{或} f[i][j+1]=0 \\
\text{先手必败} & f[i+1][j]\neq 0 \text{且} f[i][j+1]\neq 0 \\
\end{cases}$

其中，$i,j$ 表示当前的 $a,b$ 的值，$f[i+1][j]$ 表示加上 $1$ 后的 $a$ 的值，$f[i][j+1]$ 表示加上 $1$ 后的 $b$ 的值。

### 时间复杂度分析：

由于状态数为 $O(n^2)$，每次状态计算需要 $O(1)$ 的时间，因此总的时间复杂度为 $O(n^2t)$。

### AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=10010,M=30;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
ll n,f[N][M];
ll dfs(ll a,ll b){
	if(a==1&&b>27)
	  return 3;
	if(b==1&&a>n/a)
	  return ((n-a)&1)?1:2;
	if(f[a][b])
	  return f[a][b];
	if(n<pow(a,b))
	  return 1;
	ll x=dfs(a+1,b),y=dfs(a,b+1);
	if(x==1&&y==1)
	  return f[a][b]=2;
	else if(x==2&&y==2)
	  return f[a][b]=1;
	else 
	  return f[a][b]=3;
}
string s[]={"","Masha","Stas","Missing"};
ll t,a,b;
int main(){
	n=read(),t=read();
	while(t--){
		a=read(),b=read();
		printf("%s\n",s[dfs(a,b)].c_str());
	}
	return 0;
}
```
大家要自己推一下哈，不要直接抄啊~
~~以开启防作弊模式……~~

---

## 作者：ainivolAGEM (赞：1)

**前情提要：**[更好的阅读体验。](https://www.luogu.com.cn/blog/tomby-gz-2011/solution-p1839)

## 题目大意

题目已经很简洁了，还没看题的可以戳[这里](https://www.luogu.com.cn/problem/P1839)。

## 题目分析

本题就是博弈论。

根据数据范围，我们可以发现本题用一个记忆化搜索是没有问题的，那么我们可以定义一个数组 $ans [ a ] [ b ]$ 来记录答案，其中 $0$ 表示胜利，$1$ 表示输，$2$ 则表示平局，定义一个输出的字符串数组方便输出，然后直接记忆化搜索。

很明显， $ans [ a ] [ b ]$ 可以由 $ans [ a + 1 ] [ b ]$ 和 $ans [ a ] [ b + 1]$ 推得。那么 $ans [ a ] [ b ]$ 可以有以下式子：

$$ ans [ a ] [ b ] = \begin{cases} 0 & n < a^b \text{或} ans [ a + 1 ] [ b ] = 1 \text{或} ans [ a ] [ b + 1 ] = 1 \\ 1 & ans [ a + 1 ] [ b ] = 0 \text{且} ans [ a ] [ b + 1 ] = 0 \\ 2 & \text{上面两个条件不成立} \end{cases}$$

但是需要注意！还需要加入亿些细节：

1. $a = 1$ 且 $b$ 的数据不能给 $a$ 加一时，两人只能无线增加 $b$，则 $ans [ a ] [ b ] = 2$。

1. $b = 1$ 且 $a$ 的数据不能给 $b$ 加一时，则两人谁先加 $a$ 加到 $n$ 上谁就胜利。

1. 记得初始化，可以发现在 $n$ 的最大范围内可获得的 $b$ 最大是 $27$，所以需要初始化 $ans [ 1 ] [ 27 ] = 3$。

1. 由于每次输入的值会覆盖之前的数组（而且之前的数组也不是没用）所以本题多测**不需要**清空。

1. 算次方需要用 c++ 自带的 `pow(a,b)` 或者快速幂，不然会爆 long long。

然后就可以打代码啦！还是千万注意**细节**！

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int A=10004;
const int B=30;
const int T=3;
ll n,t,a,b,ans[A][B];
string oput[T]={"Masha","Stas","Missing"};
ll dfs(ll x,ll y){
	if(x==1&&y>27){
		return 2;
	}
	if(y==1&&x>n/x){
		if((n-x)&1){
			return 0;
		}else{
			return 1;
		}
	}
	if(ans[x][y]){
		return ans[x][y];
	}
	if(n<pow(x,y)){
		return 0;
	}
	ll tx=dfs(x+1,y);
	ll ty=dfs(x,y+1);
	if(!tx&&!ty){
		return ans[x][y]=1;
	}
	if(tx==1||ty==1){
		return ans[x][y]=0;
	}
	return ans[x][y]=2;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>t;
	ans[1][27]=2;
	for(int i=1;i<=t;i++){
		cin>>a>>b;
		cout<<oput[dfs(a,b)]<<'\n';
	}
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P1839)
# 思路
使用记忆化搜索所有情况先手是否获胜。

定义：令 $dfs(a,b)$ 表示先手是否必胜。（$1$ 表示必胜，$2$ 表示必败，$3$ 表示平局）。

## 普通转移
有两种转移方式：$dfs(a+1,b)$ 和 $dfs(a,b+1)$。

1. 若两个状态均为 $1$，则 $dfs(a,b)$ 必为 $2$。
2. 若两个状态有一个为 $2$，则 $dfs(a,b)$ 必为 $1$。
3. 否则，$dfs(a,b)$ 为 $3$。
## 特殊情况
 1. 若 $a=1$，且 $b \ge 27$ 时，此时两人不能加 $a$，因为 $2^{27} > 10^8$。所以两人只能不停加 $b$，因此此状态为 $3$。
 2. 若 $b=1$，$a>n \div a$ 时，此时两人不能加 $b$，因为此时 $a^2>n$，所以 $b$ 不得被加。两人只能一个一个的加 $a$，谁先加到 $n$ 谁胜利。
 3. 当 $a^b > n$ 时，$dfs(a,b) = 1$，因为后手已经输，所以先手胜。
# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int f[N][100];
int n;
int dfs(int a,int b)
{
	if(a==1 && b>=27) return 3;
	if(b==1 && a>n/a)
	{
		if((n-a)%2==0) return 2;
		else return 1;
	}
	if(pow(a,b)>n) return 1;
	if(f[a][b]) return f[a][b];
	int t1=dfs(a+1,b);
	int t2=dfs(a,b+1);
	if(t1==1 && t2==1) return f[a][b]=2;
	else if(t1==2 || t2==2) return f[a][b]=1;
	else return f[a][b]=3;
	
}
string s[4]={"ccccccccc","Masha","Stas","Missing"};
int main()
{
	int t;
	cin >>n>>t;
	while(t--)
	{
		int a,b;
		cin >>a>>b;
		cout <<s[dfs(a,b)]<<'\n';
	}
	return 0;
}

```

---

## 作者：xk2013 (赞：0)

题目传送门：[P1839 Play with Power](/problem/P1839)

## 前置知识
- 记忆化搜索。

## 题意简述
本题让我们求出在给定的游戏规则下 `Masha` 和 `Stas` 谁会赢，或者报告平局 `Missing`。

## 解题思路
记忆化搜索，其实是动态规划的一种实现。观察到 $n \le 10^8$，在 $A > 1$ 时两人最多操作 $\left.\lceil\log_2n\rceil\right.$ 次，也就是最多操作 $27$ 次。

先设计状态，设 $ans_{a, b}$ 为输入的 $a, b$ 的答案，$0$ 表示 `Masha` 赢，$1$ 表示 `Stas` 赢，$2$ 表示平局。

按照动态规划的思想，我们要设一个初值。依据上文，$n \le 10^8$ 的情况下最多操作 $27$ 次，于是我们可以初始化 $ans_{1,27} = 2$。

然后就可以开始记忆化搜索，$ans_{a, b}$ 可以由 $ans_{a + 1. b}$ 和 $ans_{a, b + 1}$ 推出，具体可以看下面：

$$ans_{a, b} = \begin{cases}
0 & n < a^b \lor ans_{a + 1, b} = 1 \lor ans_{a, b + 1} = 1\\
1 & ans_{a + 1, b} = 0 \land ans{a, b + 1} = 0\\
2 & \text{otherwise.}
\end{cases}$$

然后需要注意几个地方：
- $a = 1$ 并且 $b > 27$ 的情况要特判为 $2$，而且不能存在 $ans$ 数组里面，不然你会喜提 [$\tt RE$ $30\tt pts$](/record/192108505)，不管数组开多大都没用；
- $b = 1$ 并且 $a > \dfrac{n}{a}$ 的情况也要特判为 $\left((n - a) \bmod 2\right) \oplus 1$（$\oplus$ 为 `C++` 中的异或 `^`），而且也不能存在 $ans$ 数组里面，不然你会喜提 [$\tt RE$ $30\tt pts$ 梅开二度](/record/192109344)，不管数组开多大也还是没用；
- 虽然本题多测，但是我们是在同一个 $n$ 下的，所以之前的 $ans$ 数组也不是没用，就算没用也是井水不犯河水，求的 $a, b$ 不一样，所以本题多测**不需要清空**；
- 因为本题 $a^b\le n \le 10^8$，所以你不开 `long long int` 不用快速幂也是能轻松[通过本题](/record/192173270)的。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！

```cpp
#include <cmath>
#include <cstdio>

const int A = 1e4 + 5, B = 30;
int T, n, a, b, ans[A][B]; // 记忆化数组

int dfs(int a, int b);

int main(void)
{
	scanf("%d", &n);
	scanf("%d", &T);
	
	while (T--)
	{
		scanf("%d %d", &a, &b);
		int answer = dfs(a, b);
		
		switch (answer)
		{
		case 0:
			printf("Masha\n");
			break;
			
		case 1:
			printf("Stas\n");
			break;
			
		case 2:
			printf("Missing\n");
			break;
		}
	}
	
	return 0;
}

int dfs(int a, int b)
{
	if (a == 1 && b > 27) // 注意这里
	{
		return 2;
	}
	
	if (b == 1 && a > n / a) // 以及这里
	{
		return !((n - a) % 2);
	}
	
	if (ans[a][b]) // 搜索过的直接返回结果
	{
		return ans[a][b];
	}
	
	if (pow(a, b) > n) // 如果已经超限说明输的人是上一个操作的
	{
		return ans[a][b] = 0;
	}
	
	int ta = dfs(a + 1, b), tb = dfs(a, b + 1);
	
	if (!ta && !tb) // 推柿子，看上面
	{
		return ans[a][b] = 1;
	}
	
	if (ta == 1 || tb == 1) // 推柿子，看上面
	{
		return ans[a][b] = 0;
	}
	
	return ans[a][b] = 2; // 否则就是平局
}

```
----------------------
这是本五年级蒟蒻小学生的第 15 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2024/11/30：初版。
- 2024/12/01：修改记录链接。
- 2024/12/02：发现错误，修改。

---

