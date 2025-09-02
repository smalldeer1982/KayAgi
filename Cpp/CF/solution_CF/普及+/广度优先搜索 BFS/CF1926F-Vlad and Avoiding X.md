# Vlad and Avoiding X

## 题目描述

Vladislav has a grid of size $ 7 \times 7 $ , where each cell is colored black or white. In one operation, he can choose any cell and change its color (black $ \leftrightarrow $ white).

Find the minimum number of operations required to ensure that there are no black cells with four diagonal neighbors also being black.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1926F/b96bca00ab008cd943717e290ba9a2dfa2e51cb4.png)The left image shows that initially there are two black cells violating the condition. By flipping one cell, the grid will work.

## 说明/提示

The first test case is illustrated in the statement.

The second test case is illustrated below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1926F/7822d3ff7cf3565e0c2fe901fc2a936bc32a31de.png)In the third test case, the grid already satisfies the condition.

## 样例 #1

### 输入

```
4
WWWWWWW
WWWWBBB
WWWWWBW
WWBBBBB
WWWBWWW
WWBBBWW
WWWWWWW
WWWWWWW
WWWWWWW
WBBBBBW
WBBBBBW
WBBBBBW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WWWWWWW
WBBBBBW
BBBBBBB
BBBBBBB
WWWWWWW
BBBBBBB
BBBBBBB
BBBBBBB```

### 输出

```
1
2
0
5```

# 题解

## 作者：WaterSun (赞：5)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]CF1926F%20Vlad%20and%20Avoiding%20X)

非常（断句）好暴力。。。

# 题意

有一个 $7 \times 7$ 个网格，每一个格子上都有两种颜色，一种是 `B`，一种是 `W`。

现在你可以让一个格子上的颜色经行反转（即 `B` 变为 `W` 或 `W` 变为 `B`），使得网格上没有一个 X 形的图形的颜色都是 `B`。

# 思路

首先通过瞪眼法可以发现答案最多为 $8$。

然后你再按照下图重新分析一下，发现蓝色和红色的反转是无关的，并且红色和蓝色反转的次数都最多为 $4$，因此考虑分别计算。

![](https://espresso.codeforces.com/0fe77fd8b67663428fb6129ef7155b91ecd08222.png)

以下以红色为例，蓝色的计算方式同理。

首先枚举反转次数 $i$，然后暴力 DFS 去 check。由于我们将红色和蓝色分开了，因此红色点集合的元素是 $\frac{n}{2}$ 的。

单次 check 的复杂度就是在红色的 $\frac{n}{2}$ 选出 $i$ 个数去反转，因此为 $\Theta(\binom{25}{i} \times \frac{n}{2})$。总复杂度大约是 $\Theta(\binom{25}{4} \times n)$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 10;
int dx[] = {0,1,1,-1,-1};
int dy[] = {0,1,-1,1,-1};
int arr[N][N];
char s[N][N];

struct point{
    int x,y;
};
vector<point> g[2];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void init(){
    for (re int i = 1;i <= 7;i++){
        for (re int j = 1;j <= 7;j++) g[(i + j) % 2].push_back({i,j});
    }
}

inline bool check(int op){
    for (auto x:g[op]){
        if (!arr[x.x][x.y]) continue;
        int num = 0;
        for (re int i = 1;i <= 4;i++){
            int tx = x.x + dx[i];
            int ty = x.y + dy[i];
            if (tx >= 1 && tx <= 7 && ty >= 1 && ty <= 7) num += arr[tx][ty];
        }
        if (num == 4) return false;
    }
    return true;
}

inline bool dfs(int u,int res,int op){
    if (!res) return check(op);
    if (u == g[op].size()) return false;
    bool ok = false;
    point x = g[op][u];
    ok |= dfs(u + 1,res,op);
    arr[x.x][x.y] ^= 1;
    ok |= dfs(u + 1,res - 1,op);
    arr[x.x][x.y] ^= 1;
    return ok;
}

inline void solve(){
    int ans = 0;
    for (re int i = 1;i <= 7;i++){
        scanf("%s",s[i] + 1);
        for (re int j = 1;j <= 7;j++) arr[i][j] = (s[i][j] == 'B');
    }
    for (re int i = 0;i <= 4;i++){
        if (dfs(0,i,0)){
            ans += i;
            break;
        }
    }
    for (re int i = 0;i <= 4;i++){
        if (dfs(0,i,1)){
            ans += i;
            break;
        }
    }
    printf("%d\n",ans);
}

int main(){
    init();
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：Annihilation_y (赞：3)

# 题意
一共 $t$ 组数据。

每一组数据有一个 $7 \times 7$ 的网格。网格里面只含有黑白两种颜色，分别被表示为 ``B`` 和 ``W``。

每一次操作，我们都可以将一个点的颜色进行翻转，最终让网格中没有一个 `X` 形状的图形，颜色都是 ``B``。求最少的操作次数。

# 思路
![](https://cdn.luogu.com.cn/upload/image_hosting/2ob0daz0.png)

由上图可知，只需要对所有的蓝色点进行操作，就可以让网格满足要求。所以答案最大为 $8$。但是显然不可能对这八个点进行枚举。

设 $c=49^2 \times 48^2$，时间复杂度大概为 $O(ct)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xuk4cyuk.png)

通过染色，可以发现，红色和绿色的处理是互不干扰的。且各最多处理四个点，所以直接暴力循环枚举翻转的点即可。

设 $C=25^6$，时间复杂度大概为 $O(Ct)$。

# 代码
~~~c++
#include <bits/stdc++.h>
using namespace std;
int t;
int mp[10][10],ans,X1,Y1,X2,Y2,X3,Y3,X4,Y4;
bool Check1(){//对红色块的检查 
	bool flag=1;
	for(int i=2;i<=6;i++){
		if(flag==0) break;
		for(int j=2;j<=6;j++){
			if((i+j)%2==1) continue;
			if(flag==0) break;
			if(mp[i][j]&&mp[i-1][j-1]&&mp[i-1][j+1]&&mp[i+1][j-1]&&mp[i+1][j+1]) {
				flag=0;
			}
		}
	}
	if(flag) return 1;
	else return 0;
}
bool Check2(){//对绿色块的检查 
	bool flag=1;
	for(int i=2;i<=6;i++){
		if(flag==0) break;
		for(int j=2;j<=6;j++){
			if((i+j)%2==0) continue;
			if(flag==0) break;
			if(mp[i][j]&&mp[i-1][j-1]&&mp[i-1][j+1]&&mp[i+1][j-1]&&mp[i+1][j+1]){
				flag=0;
			}
		}
	}
	if(flag) return 1;
	else return 0;
}
int main(){
	int t;cin>>t;
	while(t--){
		ans=INT_MAX;
		for(int i=1;i<=7;i++){
			getchar();
			for(int j=1;j<=7;j++){
				char c;
				c=getchar();
				if(c=='B') mp[i][j]=1; 
				else mp[i][j]=0;
			}
		}
		int ans1=5,ans2=5;
		if(Check1()) ans1=0;
		for(int i=1;i<=49;i+=2){//枚举红色块 
			if(ans2==0||ans2==1) break;
			X1=(i-1)/7+1;Y1=(i%7==0)?7:(i%7);
			if(mp[X1][Y1]==1){
				mp[X1][Y1]=0;
				if(Check1()){ ans1=min(ans1,1);break;}
				for(int j=i+2;j<=49;j+=2){
					X2=(j-1)/7+1;Y2=(j%7==0)?7:(j%7);
					if(mp[X2][Y2]==1){
						mp[X2][Y2]=0;
						if(Check1()) ans1=min(ans1,2);
						for(int ii=j+2;ii<=49;ii+=2){
							X3=(ii-1)/7+1;Y3=(ii%7==0)?7:(ii%7);
							if(mp[X3][Y3]==1){
								mp[X3][Y3]=0;
								if(Check1()) ans1=min(ans1,3);
								for(int jj=ii+2;jj<=49;jj+=2){
									X4=(jj-1)/7+1;Y4=(jj%7==0)?7:(jj%7);
									if(mp[X4][Y4]==1){
										mp[X4][Y4]=0;
										if(Check1()) ans1=min(ans1,4);
										mp[X4][Y4]=1;
									}
								}	
								mp[X3][Y3]=1;
							}
						}
						mp[X2][Y2]=1;
					}
				}
				mp[X1][Y1]=1;
			}
		}
		if(Check2()) ans2=0;
		for(int i=2;i<=48;i+=2){//枚举绿色块 
			if(ans2==0||ans2==1) break;
			X1=(i-1)/7+1;Y1=(i%7==0)?7:(i%7);
			if(mp[X1][Y1]==1){
				mp[X1][Y1]=0;
				if(Check2()){ ans2=min(ans2,1);break;}
				for(int j=i+2;j<=48;j+=2){
					X2=(j-1)/7+1;Y2=(j%7==0)?7:(j%7);
					if(mp[X2][Y2]==1){
						mp[X2][Y2]=0;
						if(Check2()) ans2=min(ans2,2);
						for(int ii=j+2;ii<=48;ii+=2){
							X3=(ii-1)/7+1;Y3=(ii%7==0)?7:(ii%7);
							if(mp[X3][Y3]==1){
								mp[X3][Y3]=0;
								if(Check2()) ans2=min(ans2,3);
								for(int jj=ii+2;jj<=48;jj+=2){
									X4=(jj-1)/7+1;Y4=(jj%7==0)?7:(jj%7);
									if(mp[X4][Y4]==1){
										mp[X4][Y4]=0;
										if(Check2()) ans2=min(ans2,4);
										mp[X4][Y4]=1;
									}
								}	
								mp[X3][Y3]=1;
							}
						}
						mp[X2][Y2]=1;
					}
				}
				mp[X1][Y1]=1;
			}
		}
//		cout<<ans1<<" "<<ans2<<endl;
		printf("%d\n",ans1+ans2);
	}
	return 0;
}
~~~

---

## 作者：迟暮天复明 (赞：3)

首先套路的把棋盘黑白染色之后显然两者是独立的。

然后可以用类似于炮兵阵地的方式套路地设计一个状压 DP，令 $f_{i,j,k}$ 表示第 $i-1,i$ 行的状态分别为 $j,k$ 的最少修改次数。

转移的话就是枚举 $i-2,i-1,i$ 三行分别的状态为 $j,k,l$，判断是否会出现叉就行，也就是需要保证 $(j \operatorname{shl} 1) \operatorname{AND}(j \operatorname{shr} 1) \operatorname{AND}k\operatorname{AND}(l\operatorname{shl} 1) \operatorname{AND}(l \operatorname{shl} 1)$ 为 $0$。

时间复杂度的话，因为黑白染色了，所以枚举子集的时间复杂度不超过 $2^4=2^{n/2}$，总时间复杂度就是 $O(Tn\times8^{n/2})$。

枚举子集别忘了 0。

[提交记录](https://codeforces.com/contest/1926/submission/247758200)

---

## 作者：沉石鱼惊旋 (赞：3)

[更好的阅读体验](http://blog.cyx2009.top/archives/258/)

# 题目翻译

给定 $7\times 7$ 的黑白网格，问至少改多少点才能使得不出现大小为 $3\times 3$ 的**黑色** $\tt X$ 形。定义改一个点指改变这个点的颜色，黑变成白，白变成黑。

多测，$1\leq t\leq 200$。

# 题目思路

显然只需要黑色改白色。

一个不是很显然的结论是 $ans\leq 8$。

你考虑对于网格进行红绿染色（其实就是黑白染色，但是和题意重合了）。就是 $(1,1)$ 红色，$(1,2)$ 和 $(2,1)$ 绿色这样子交叉递推。显然红色与绿色的部分是可以分开计算的。

然后我们瞪眼法发现一个 $ans=8$ 的通解：染色 $(3,3),(3,4),(3,5),(4,3),(4,5),(5,3),(5,4),(5,5)$。这也就告诉我们，$ans$ 上界为 $8$。其中红绿两部分各 $4$ 个。

但是这不一定能构造最优解。~~因为我在 test 2 的 case 16 WA 了。~~

但是这启发我们，因为答案很小，每个部分也都很少，我们可以直接暴力枚举具体是哪 $4$ 个格子被染白了。

时间复杂度是 $\mathcal O(\binom{25}{4}\times 25+\binom{24}{4}\times 24)$ 的。后面加的 $\times 25$ 之类的是用来 check 是否为合法的方案的。~~时间复杂度能这么写吗我不知道啊。~~

# 完整代码

写的很丑。

[CF submission 247566445](https://codeforces.com/contest/1926/submission/247566445)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
const int n = 7;
const int m = 9;
const int dx[] = {3, 3, 3, 4, 4, 4, 5, 5, 5};
const int dy[] = {3, 4, 5, 3, 4, 5, 3, 4, 5};
char mp[10][10];
vector<pii> v[2];
bool ok(int x, int y) { return mp[x - 1][y - 1] == 'B' && mp[x - 1][y + 1] == 'B' && mp[x + 1][y - 1] == 'B' && mp[x + 1][y + 1] == 'B'; }
void change(pii a, char to) { mp[a.first][a.second] = to; }
int siz(int a, int b, int c, int d)
{
    set<int> s;
    s.insert(a);
    s.insert(b);
    s.insert(c);
    s.insert(d);
    return s.size();
}
int calc(vector<pii> &v)
{
    bool need = 0;
    for (pii p : v)
    {
        int x = p.first;
        int y = p.second;
        if (mp[x][y] == 'B')
            if (ok(x, y))
                need = 1;
    }
    if (!need)
        return 0;
    int ret = 8;
    for (int p1 = 0; p1 < v.size(); p1++)
    {
        for (int p2 = p1; p2 < v.size(); p2++)
        {
            for (int p3 = p2; p3 < v.size(); p3++)
            {
                for (int p4 = p3; p4 < v.size(); p4++)
                {
                    need = 1;
                    change(v[p1], 'W'), change(v[p2], 'W'), change(v[p3], 'W'), change(v[p4], 'W');
                    for (pii p : v)
                    {
                        int x = p.first;
                        int y = p.second;
                        if (mp[x][y] == 'B')
                            if (ok(x, y))
                                need = 0;
                    }
                    if (need)
                        chkmn(ret, siz(p1, p2, p3, p4));
                    change(v[p1], 'B'), change(v[p2], 'B'), change(v[p3], 'B'), change(v[p4], 'B');
                }
            }
        }
    }
    return ret;
}
void solve()
{
    v[0].clear(), v[1].clear();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> mp[i][j];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            if (mp[i][j] == 'B')
                v[(i & 1) ^ (j & 1)].push_back({i, j});
    }
    cout << calc(v[0]) + calc(v[1]) << '\n';
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Shunpower (赞：1)

## Statement

给定一个 $7\times 7$ 的黑白矩阵，每次允许反转一个格子上的颜色。输出最小的操作次数使得对于任意一个黑色格子，都满足其四个角上的相邻格子有至少一个是白色的。

多测，$T\leq 200$。

## Solution

感觉是炫酷的中档题。

限制条件对四个角上的相邻格子做出了限制，想到对矩阵进行相间染色，然后发现两种颜色部分是独立的。这里借用原题解的一张图：

![](https://espresso.codeforces.com/0fe77fd8b67663428fb6129ef7155b91ecd08222.png)

在这张图上的粉色格子和蓝色格子部分是互相独立的。也就是说，我们可以先让蓝色部分的每个黑色格子都满足条件，再让粉色部分的每个黑色格子都满足条件，这是互不影响的。最终答案把两部分的最小值求和就行了。

这样相当于问题规模减小了一半。

考虑每个部分怎么做，手玩可以发现，即便是需要操作次数最多的情况（也就是这个部分的所有格子都是黑的，很容易证明这是极限情况）操作次数也不会超过 $4$ 次：

```
1010101 0101010
0101010 1010101
10*0*01 010*010
0101010 10*0*01
10*0*01 010*010
0101010 1010101
1010101 0101010
```

各自操作 `*` 处的四个黑色格子即可。

显然，超过一次改变一个位置的颜色没有任何意义，所以对于每个部分我们可以 $\mathcal O({\frac{nm}{2}\choose4}nm)$ 地暴力枚举选择哪些格子反转并检验是否合法，严格按照复杂度进行精细实现的话运算次数大概在 $10^7$ 左右。

对于两个部分都在所有暴力枚举出来合法情况中取步数最小的，再加在一起就行了。

## Code

由于原题时限足够大，我直接写的 $\mathcal O((nm)^5)$ 加上剪枝就过了，所以代码仅供参考。

```cpp
char c[10][10];
int sum[2];
int dx[]={1,-1,1,-1},dy[]={-1,1,1,-1};
bool ok(int x,int y){
    fr1(i,0,3){
       if(c[x+dx[i]][y+dy[i]]=='W') return 1; 
    }
    return c[x][y]!='B';
}
bool check(int op){
    bool f=1;
    fr1(i,2,6){
        fr1(j,2,6){
            if(((i&1)^(j&1))==op) f&=ok(i,j);
        }
    }
    return f;
}
void dfs(int x,int op){
    if(check(op)){
        sum[op]=min(sum[op],x-1);
    }
    if(x>=sum[op]){
        return;
    }
    fr1(i,1,7){
        fr1(j,1,7){
            if(((i&1)^(j&1))!=op) continue;
            char tmp=c[i][j];
            c[i][j]=(tmp=='W'?'B':'W');
            dfs(x+1,op);
            c[i][j]=tmp;
        }
    }
}
void solve(){
    fr1(i,1,7){
        fr1(j,1,7){
            cin>>c[i][j];
        }
    }
    sum[0]=sum[1]=5;
    dfs(1,0);
    dfs(1,1);
    cout<<sum[0]+sum[1]<<'\n';
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意

给一个 $7\times 7$ 的 $01$ 矩阵（对应 `W` 和 `B`），你可以操作若干次，每次把一个 $1$ 改成 $0$。求最少的操作次数，使得矩阵中不存在 $1$ 构成 X 形，即不存在一个 $3\times 3$ 的正方形的四个角和中间的数都是 $1$。多组数据，$T\le 200$。

## 题目分析
 
显然此题需要状压，设 $dp_{i,S}$ 表示前 $i$ 行，最后两行的数长成 $S$ ，且前 $i$ 行合法的最小步数。枚举 $i+1$ 行的状态即可 $O(2^{3n})$ 次方转移，总复杂度 $O(Tn^22^{3n})$，无法通过。

发现黑白染色后只有同色的格子会互相限制，分开计算即可，复杂度 $O(Tn^22^{1.5n})$，可以通过。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N =8,M=1<<4,inf=(1LL<<31)-1,mod=998244353;
const ll llf=2e18;
char c[N][N];
bool a[N][N];
int n=7,S=M-1;
int f[N][M][M],g[N][M][M];
bool check(int s,int i){
	return (s>>i-1)&1;
}
int disf(int x,int S){
	int ans=0,st=2-(x&1),nw=0;
	while(nw<=3&&st<=n){
		ans+=(a[x][st]!=check(S,nw+1));
		st+=2,nw++;
	}
	return ans;
}
int disg(int x,int S){
	int ans=0,st=2-(!(x&1)),nw=0;
	while(nw<=3&&st<=n){
		ans+=(a[x][st]!=check(S,nw+1));
		st+=2,nw++;
	}
	return ans;
}
void sol(int x){
	rep(i,0,S)rep(j,0,S)if(f[x-1][i][j]<8){
		rep(k,0,S){
			int d=disf(x,k);
			bool fl=1;
			if(x&1){
				rep(y,1,3)fl&=!(check(j,y)&check(i,y)&check(k,y)&check(i,y+1)&check(k,y+1));
			}else {
				rep(y,2,3)fl&=!(check(j,y)&check(i,y)&check(k,y)&check(i,y-1)&check(k,y-1));
			}
			if(fl)f[x][j][k]=min(f[x][j][k],f[x-1][i][j]+d);
		}
	}
	rep(i,0,S)rep(j,0,S)if(g[x-1][i][j]<8){
		rep(k,0,S){
			int d=disg(x,k);
			bool fl=1;
			if(!(x&1)){
				rep(y,1,3)fl&=!(check(j,y)&check(i,y)&check(k,y)&check(i,y+1)&check(k,y+1));
				
			}else {
				rep(y,2,3)fl&=!(check(j,y)&check(i,y)&check(k,y)&check(i,y-1)&check(k,y-1));
			}
			if(fl)g[x][j][k]=min(g[x][j][k],g[x-1][i][j]+d);
		}
	}
}
void Main(){
	repn(i)repn(j)cin >>c[i][j],a[i][j]=c[i][j]=='B';
	memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
	rep(i,0,S)rep(j,0,S)f[2][i][j]=disf(1,i)+disf(2,j),g[2][i][j]=disg(1,i)+disg(2,j);
	
	rep(i,3,n)sol(i);
	int ans=inf,as=inf;
	rep(i,0,S)rep(j,0,S)ans=min(ans,f[7][i][j]),as=min(as,g[7][i][j]);
	cout <<ans+as<<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```


---

## 作者：wth2026 (赞：0)

## 题目描述

弗拉迪斯拉夫有一个大小为 $7 \times 7$ 的网格，其中每个单元格的颜色都是黑色或白色。在一次操作中，他可以选择任何一个单元格并改变其颜色（黑色 $\leftrightarrow$ 白色）。

求最少需要多少次操作才能确保没有黑色单元格的对角线上的四个相邻单元格也是黑色的。

## 思路

我们可以将棋盘上的格子分成两种，坐标同奇同偶的是一种，其他的又是一种。我们可以发现，出现题目所述的情况的五个点肯定都是同一种，而且每一种最多改四个就可以达到目标。于是我们可以将点分成两组后暴力搜索。

## AC code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

bool a[9][9];
char in;

bool pd(int x, int y) {
	return a[x + 1][y + 1] && a[x - 1][y + 1] && a[x - 1][y - 1] && a[x + 1][y - 1];
}

bool pd0() {
	int x, y;
	
	for (int i = 1; i <= 49; i += 2) {
		x = (i - 1) / 7 + 1;
		y = (i - 1) % 7 + 1;
		
		if (a[x][y] && pd(x, y)) {
			return false;
		}
	}
	
	return true;
}

bool pd1() {
	int x, y;
	
	for (int i = 2; i < 49; i += 2) {
		x = (i - 1) / 7 + 1;
		y = (i - 1) % 7 + 1;
		
		if (a[x][y] && pd(x, y)) {
			return false;
		}
	}
	
	return true;
}

int ans0() {
	if (pd0()) {
		return 0;
	}
	
	int x[4], y[4];
	
	for (int i = 1; i <= 49; i += 2) {
		x[0] = (i - 1) / 7 + 1;
		y[0] = (i - 1) % 7 + 1;
		
		if (!a[x[0]][y[0]]) {
			continue;
		}
		
		a[x[0]][y[0]] = 0;
		
		if (pd0()) {
			return 1;
		}
		
		a[x[0]][y[0]] = 1;
	}
	
	for (int i = 1; i <= 49; i += 2) {
		x[0] = (i - 1) / 7 + 1;
		y[0] = (i - 1) % 7 + 1;
		
		if (!a[x[0]][y[0]]) {
			continue;
		}
		
		a[x[0]][y[0]] = 0;
		
		for (int j = i + 2; j <= 49; j += 2) {
			x[1] = (j - 1) / 7 + 1;
			y[1] = (j - 1) % 7 + 1;
			
			if (!a[x[1]][y[1]]) {
				continue;
			}
			
			a[x[1]][y[1]] = 0;
			
			if (pd0()) {
				return 2;
			}
			
			a[x[1]][y[1]] = 1;
		}
		
		a[x[0]][y[0]] = 1;
	}
	
	for (int i = 1; i <= 49; i += 2) {
		x[0] = (i - 1) / 7 + 1;
		y[0] = (i - 1) % 7 + 1;
		
		if (!a[x[0]][y[0]]) {
			continue;
		}
		
		a[x[0]][y[0]] = 0;
		
		for (int j = i + 2; j <= 49; j += 2) {
			x[1] = (j - 1) / 7 + 1;
			y[1] = (j - 1) % 7 + 1;
			
			if (!a[x[1]][y[1]]) {
				continue;
			}
			
			a[x[1]][y[1]] = 0;
			
			for (int k = j + 2; k <= 49; k += 2) {
				x[2] = (k - 1) / 7 + 1;
				y[2] = (k - 1) % 7 + 1;
				
				if (!a[x[2]][y[2]]) {
					continue;
				}
				
				a[x[2]][y[2]] = 0;
				
				if (pd0()) {
					return 3;
				}
				
				a[x[2]][y[2]] = 1;
			}
			
			a[x[1]][y[1]] = 1;
		}
		
		a[x[0]][y[0]] = 1;
	}
	
	return 4;
}

int ans1() {
	if (pd1()) {
		return 0;
	}
	
	int x[4], y[4];
	
	for (int i = 2; i <= 49; i += 2) {
		x[0] = (i - 1) / 7 + 1;
		y[0] = (i - 1) % 7 + 1;
		
		if (!a[x[0]][y[0]]) {
			continue;
		}
		
		a[x[0]][y[0]] = 0;
		
		if (pd1()) {
			return 1;
		}
		
		a[x[0]][y[0]] = 1;
	}
	
	for (int i = 2; i <= 49; i += 2) {
		x[0] = (i - 1) / 7 + 1;
		y[0] = (i - 1) % 7 + 1;
		
		if (!a[x[0]][y[0]]) {
			continue;
		}
		
		a[x[0]][y[0]] = 0;
		
		for (int j = i + 2; j <= 49; j += 2) {
			x[1] = (j - 1) / 7 + 1;
			y[1] = (j - 1) % 7 + 1;
			
			if (!a[x[1]][y[1]]) {
				continue;
			}
			
			a[x[1]][y[1]] = 0;
			
			if (pd1()) {
				return 2;
			}
			
			a[x[1]][y[1]] = 1;
		}
		
		a[x[0]][y[0]] = 1;
	}
	
	for (int i = 2; i <= 49; i += 2) {
		x[0] = (i - 1) / 7 + 1;
		y[0] = (i - 1) % 7 + 1;
		
		if (!a[x[0]][y[0]]) {
			continue;
		}
		
		a[x[0]][y[0]] = 0;
		
		for (int j = i + 2; j <= 49; j += 2) {
			x[1] = (j - 1) / 7 + 1;
			y[1] = (j - 1) % 7 + 1;
			
			if (!a[x[1]][y[1]]) {
				continue;
			}
			
			a[x[1]][y[1]] = 0;
			
			for (int k = j + 2; k <= 49; k += 2) {
				x[2] = (k - 1) / 7 + 1;
				y[2] = (k - 1) % 7 + 1;
				
				if (!a[x[2]][y[2]]) {
					continue;
				}
				
				a[x[2]][y[2]] = 0;
				
				if (pd1()) {
					return 3;
				}
				
				a[x[2]][y[2]] = 1;
			}
			
			a[x[1]][y[1]] = 1;
		}
		
		a[x[0]][y[0]] = 1;
	}
	
	return 4;
}

int T, ans[2];

void init() {
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	
	cin >> T;
	
	while (T --) {
		ans[0] = ans[1] = 0;
		
		for (int i = 1; i <= 7; ++ i) {
			for (int j = 1; j <= 7; ++ j) {
				cin >> in;
				a[i][j] = (in == 'B');
			}
		}
		
		ans[0] = ans0();
		ans[1] = ans1();
		cout << ans[0] + ans[1] << endl;
	}
	
	return 0;
}
```

---

