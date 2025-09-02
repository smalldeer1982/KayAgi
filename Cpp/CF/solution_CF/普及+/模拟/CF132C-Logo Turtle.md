# Logo Turtle

## 题目描述

A lot of people associate Logo programming language with turtle graphics. In this case the turtle moves along the straight line and accepts commands "T" ("turn around") and "F" ("move 1 unit forward").

You are given a list of commands that will be given to the turtle. You have to change exactly $ n $ commands from the list (one command can be changed several times). How far from the starting point can the turtle move after it follows all the commands of the modified list?

## 说明/提示

In the first example the best option is to change the second command ("T") to "F" — this way the turtle will cover a distance of 2 units.

In the second example you have to change two commands. One of the ways to cover maximal distance of 6 units is to change the fourth command and first or last one.

## 样例 #1

### 输入

```
FT
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
FFFTFFF
2
```

### 输出

```
6
```

# 题解

## 作者：Mortis_Vampire (赞：8)


这道题其实直接按照题意进行爆搜就可以了。

只是要用记忆化。

详细讲解一下 dfs 吧：

设命令串为 $S$。


第 now 个指令  
cnt 表示修改指令个数   
d 表示当前离起点的距离  
direction 是面朝的方向(当 direction 为 0 时是初始正方向)

对于当前的命令 $S_{now}$ 一共两种情况：

1.如果当前的命令为 T，搜两次：

```
dfs(now+1,cnt+1,d+((direction==0)?1:-1),direction);
dfs(now+1,cnt,d,(direction==0)?1:0);

```
第一个dfs延着当前方向走下去，把 T 变成了 F ，修改命令数 $+1$，距离 $+1$或 $-1$（看方向），进入下一个命令。

第二个dfs方向变化，按照命令行事，方向变化，进入下一个命令。

2.如果当前的命令为 F，也是一样的搜两次：

```
dfs(now+1,cnt,d+((direction==0)?1:-1),direction);
dfs(now+1,cnt+1,d,(direction==0)?1:0);

```
第一个 dfs 延着当前方向走下去，按照命令行事，距离 $+1$ 或 $-1$（看方向），进入下一个命令。

第二个 dfs 方向变化，把 F 变成 T ，修改命令数 $+1$，进入下一个命令。

最后因为一个命令可以被改变多次，所以需要再 dfs 一次保持当前命令状态：
```
dfs(now,cnt+2,d,direction);
```
即修改命令数 $+2$，其他状态不变。

## 代码

~~码风清奇，见谅~~
```
void dfs(int now,int cnt,int d,int direction) {
//第now个指令
//cnt表示修改指令个数    
//d表示离起点的距离
//direction面朝的方向(当direction为0时是正方向)
	if (v[now][cnt][d+100][direction])return;//利用v数组记忆化保存当前状态，剪枝优化
	v[now][cnt][d+100][direction]=1;
	if (now>len+1||cnt>n)return;//递归边界
	if (now==len+1&&cnt==n) {
		ans=max(ans,abs(d));//更新ans值
		return;
	}
   //爆搜
	if (s[now]=='T')//当第now个命令为T时
		dfs(now+1,cnt+1,d+((direction==0)?1:-1),direction);
	else dfs(now+1,cnt,d+((direction==0)?1:-1),direction);//当第now个命令为F时
	if (s[now]=='F')//当第now个命令为F时
		dfs(now+1,cnt+1,d,(direction==0)?1:0);
	else  dfs(now+1,cnt,d,(direction==0)?1:0);//当第now个命令为T时
	dfs(now,cnt+2,d,direction);
}
```
然后注意dfs是从第 $1$ 个命令，修改命令 $0$ 次，离起点距离为 $0$ ，方向   $0$（正方向）开始搜的：
```cpp
dfs(1,0,0,0);
```


---

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF132C)
# 思路分析
这道题我们明显能看出来正解是 **dp**，但是本蒟蒻不会写，不过当我看见 $ 1\le n\le 50 $，最多有 $ 100 $ 个指令以及时限为 $ 2 $ 秒时，我就知道我能通过**记忆化** dfs 加剪枝来通过这道题。

dfs 函数一共有 $ 4 $ 个参数，分别代表当前位置为 $ pos $，已经改变了 $ sum $ 个指令，海龟已经向正方向移动了 $ dis $ 单元，当前方向为 $ dt $（记初始方向为正方向）。为了方便，记 $ dt $ 为 $ 1 $ 时代表正方向，$ dt $ 为 $ -1 $ 时代表反方向，这样更新 $ dis $ 时可以直接加减，就不用判断了。

对于记忆化，本蒟蒻用了一个四维数组来记录当前状态是否搜过，如果是，就直接 ` return `，如果不是，就继续进行。

搜索每一位时，如果当前位为 T，搜索 $ 2 $ 次，第一次是不改变当前命令，直接转向；第二次是改变当前命令为 F，并向当前方向前进 $ 1 $ 个单位。
```cpp
dfs(pos+1,sum,dis,dt*(-1));
dfs(pos+1,sum+1,dis+dt,dt);
```

如果当前位为 F，同样也搜索 $ 2 $ 次，第一次是不改变当前命令，向当前方向前进 $ 1 $ 个单位；第二次是改变当前命令为 T，然后转向。
```cpp
dfs(pos+1,sum,dis+dt,dt);
dfs(pos+1,sum+1,dis,dt*(-1));
```

最后，因为每一位都可以无限次数的更改指令，所以我们还要进行一次搜索，即 $ sum $ 加 $ 2 $，而其它参数不变。
```cpp
dfs(pos,sum+2,dis,dt);
```
而初始值其实很好设定，因为海龟最初面向正方向，位移为 $ 0 $，我们从字符串的首位开始搜索，所以 dfs 调用时就是这样：
```cpp
dfs(0,0,0,1);
```
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
string s;
bool f[110][60][300][5];
inline void dfs(int pos,int sum,int dis,int dt)
{
	if (sum>m||abs(dis)+n-pos<=ans||f[pos][sum][dis+110][dt+2])
		return;//剪枝以及记忆化 
	if (pos==n)
	{
		if (sum==m)
			ans=max(ans,abs(dis));
		return;
	}
	f[pos][sum][dis+110][dt+2]=true;//因为 dis和 dt可能为负数，所以要加 
	if (s[pos]=='T')
	{
		dfs(pos+1,sum,dis,dt*(-1));//不改变指令，直接转向 
		dfs(pos+1,sum+1,dis+dt,dt);//改变指令为 F，并移动一个单位 
	}
	else
	{
		dfs(pos+1,sum,dis+dt,dt);//不改变指令，直接移动一个单位 
		dfs(pos+1,sum+1,dis,dt*(-1));//改变指令为 T，然后转向 
	}
	dfs(pos,sum+2,dis,dt);//改变两次指令 
}
int main()
{
	cin>>s>>m;
	n=s.size();
	dfs(0,0,0,1);//调用 
	cout<<ans<<endl;
}
```


---

## 作者：Sakurajima_Mai (赞：4)

- 可以用三维$dp$来保存状态， $dp[i][j][k]$表示在前$i$个字符变换了j步之后方向为$k(k = 1 $ $or$  $k = 0)$的最优解，也就是离原点的最大距离。这里规定0方向为正方向，1位负方向，表示的是当前这个人朝哪个方向。这两个方向是对立的。

- 所以就可以递推一个关系式，分第$i$个字符为$F$ or $T$时

#### 1. 如果为$F$

- 依次枚举在第$i$个位置变换了几步，这是枚举的范围为$[0,j]$, 假设变换了$k$步(和上面的$dp[i][j][k]$当中的$k$不是一个)

1. 如果当$k$为奇数的时候，就是相当于变化了1步，所以$F$就变成$T$了，那么他的方向也因此变化了。所以当前的方向一定和上一步(也就是$i - 1$时的方向)的方向相反，所以有$dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - k][1])$, 

   同理，
   
   $dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - k][0])$

2. 如果$k$为偶数，相当于没有变化，所以还是字符$F$，如果是正方向，那么他就可以由上一步继续向正方向走一步，也就是加1， 如果是负方向，相当于往回走一步，距离就减1，

   递推方程为:$dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - k][0] + 1);$ 
   $dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - k][1] - 1);$

#### 2.如果为$T$

依次枚举在第$i$个位置变化了几步，范围也是$[0,j]$,假设变换$k$步

1. 如果$k$为奇数，这时就变化成了$F$,所以$dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - k][0] + 1); $
   $ dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - k][1] - 1)$

2. 如果$k$为偶数，这时还是$T$，所以$dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - k][1]);$
   $ dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - k][0])$

#### 其中还有一个问题:
  就是和刚开始的方向的无关，不用管朝哪个方向，只要走的最远的就行了，而且始终有两个相互对立的方向。初始化的时候$dp[0][0][0]$和$dp[0][0][1]$都得初始化$0$，这样才可以往哪走都可以.
  
```cpp
for (int i = 0; i <= len; i++)
        for (int j = 0; j <= n; j++) dp[i][j][0] = dp[i][j][1] = -inf;
    dp[0][0][0] = 0;//正方向
    dp[0][0][1] = 0;//负方向，两边都可以走
    for (int i = 1; i <= len; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k <= j; k++)
            {
                if (cmd[i] == 'F')
                {
                    if (k & 1)
                    {
                        dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - k][1]);
                        dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - k][0]);
                    }
                    else
                    {
                        dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - k][0] + 1);
                        dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - k][1] - 1);
                    }
                }
                else
                {

                    if (k & 1)
                    {
                        dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - k][0] + 1);
                        dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - k][1] - 1);
                    }
                    else
                    {
                        dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - k][1]);
                        dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - k][0]);
                    }
                }
            }

        }

    }
```

---

## 作者：oimaster (赞：3)

[仍然是老习惯，早上起床打一场 Codeforces。今天起晚了，打不起来，所以就做了一道 C 题。我是拿随机数跳题跳的，爬取题面到本地以后一直在做，调了好久，感到奇怪，最后交的时候才发现这是 Div.1 （唔，问题是我居然 AC 了？](https://oi-master.github.io/post/codeforces-contest-132-c-ti-jie/)

## 思路
典型的 DP 题目。我们可以用一个三维 DP 来做这道题目，是 $dp_{i,j,k}$ ，表示的是前 $i$ 个字符，换了 $j$ 次，然后方向为 $k$ 的时候里原点最大的距离。$k$ 的取值为 $0$ 或者是 $1$ ，$0$标识的就是正方向，$1$ 表示的就是负方向。

然后，我们来分析一下状态转移方程，不过，直接写不太方便，我觉得我们应该从每个情况看起。

1. 如果 $s_i$ 是 `F`：

    我们枚举在这个 $i$ 的位置上换了几次，枚举的范围就是 $0$ 至 $j$，然后我们把这个换的次数的值叫做 $k$ ，接下来我们再进一步分析一下 $k$。
    
    如果 $k$ 是奇数的话，那么因为抵消的关系就相当于 $k$ 是 $1$ 。那么，现在的方向一定和上一次的方向是相反的，所以，可以得知，状态转移方程如下：
    
    $$dp_{i,j,0}=max(dp_{i,j,0},dp_{i-1,j-k,1})$$
    然后，我们也可以得知
    
    $$dp_{i,j,1}=max(dp_{i,j,1},dp_{i-1,j-k,0})$$
    
    否则，那么 $k$ 就是偶数，那么就等于字符没变呢。所以，我们就按照现在的方向向前走一步，如果是正方向，那么位置就加上 $1$ 。如果是负方向，那么位置就减掉 $1$ 。这个应该很好理解，上式子。
    
    $$dp_{i,j,0}=max(dp_{i,j,0},dp_{i-1,j-k,0}+1)$$
    
    几乎一样的式子：
    
    $$dp_{i,j,1}=max(dp_{i,j,1},dp_{i-1,j-k,1}-1)$$
    是吧？很好理解对不对？
    
2. 如果 $s_i$ 是字符 `T`：

    额，一样的一样的，如果 $k$ 是
    奇数的话，那么 $s_i$ 就会变成 `F` ，状态转移方程搬下来：
    $$dp_{i,j,0}=max(dp_{i,j,0},dp_{i-1,j-k,0}+1)$$
    $$dp_{i,j,1}=max(dp_{i,j,1},dp_{i-1,j-k,1}-1)$$
    
    如果 $k$ 是偶数的话：
    
    $$dp_{i,j,0}=max(dp_{i,j,0},dp_{i-1,j-k,1})$$
    $$dp_{i,j,1}=max(dp_{i,j,1},dp_{i-1,j-k,0})$$

好了，现在是不是感觉很简单？我们只需要加一个简单的初始化即可。

$$dp_{0,0,0}=dp_{0,0,1}=0$$

其他的格子都赋值为无限小（$-inf$）。

上代码。
### 代码
```cpp
/* Generated by powerful Codeforces Tool
 * You can download the binary file in here https://github.com/xalanq/cf-tool
 * Author: OI_Master
 * Time: 2020-04-06 08:37:08
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[101][51][2];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s;
	cin>>s;
	int n;
	cin>>n;
	int size=s.size();
	s=' '+s;
	for(int i=0;i<=size;++i)
		for(int j=0;j<=n;++j)
			dp[i][j][0]=dp[i][j][1]=-1000000000000;
	dp[0][0][0]=0;
	dp[0][0][1]=0;
	for(int i=1;i<=size;++i)
		for(int j=0;j<=n;++j)
			for(int k=0;k<=j;++k)
				if(s[i]=='F')
					if(k%2==1){
						dp[i][j][0]=max(dp[i][j][0],dp[i-1][j-k][0]);
						dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-k][0]);
					}
					else{
						dp[i][j][0]=max(dp[i][j][0],dp[i-1][j-k][0]+1);
						dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-k][1]-1);
					}
				else
					if(k%2==1){
						dp[i][j][0]=max(dp[i][j][0],dp[i-1][j-k][0]+1);
						dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-k][1]-1);
					}
					else{
						dp[i][j][0]=max(dp[i][j][0],dp[i-1][j-k][1]);
                        dp[i][j][1]=max(dp[i][j][1],dp[i-1][j-k][0]);
					}
	cout<<max(dp[size][n][0],dp[size][n][1]);
	return 0;
}
```
没了，没了，下面就是评论区了。

---

## 作者：R·Buffoon (赞：3)

##  $\color{#66ccff}\text{解法：动态规划}$
 
 动态规划的题，一般都有两种写法，一种是直推（for循环），另一种就是写递归函数（dfs），用dp数组实现记忆化搜索。这里用的是递归（直推有人写了）
 ***
 **思路**：尽可能多的将T转化为F，有点贪心的思想，只要~~爆搜~~记忆化搜索就可以了 
 
 **注意：当T都改变为F后剩下的还可改变的命令数为奇数，那么距离-1**
 ***
 dp数组说明：dp[a][b][c][d]:第a个命令；距离起点b；还剩c个命令；当前方向
 ***
 
 ~~~cpp
#include<bits/stdc++.h>
using namespace std;

const int N=55;

int dp[N<<1][N<<2][N][2]={0};
char c[N<<1];
int n,l,ans=0;

int dfs(int x,int cnt_t,int sum_t,int now)
//x:遍历的命令序号；cnt_t:改变了多少个T；sum_t:出现几个T；now：当前移动距离
{
	if(cnt_t>n) return 0;//修改的命令大于n，返回0
	if(x==l)//搜完
	{
		ans=max(ans,abs(now)-((n-cnt_t)&1));
		//求的是相对距离，所有取now绝对值
		//如果T都改变为F后剩下的还可改变的命令数（n-cnt_t）为奇数，那么-1
		return ans;
	}

	int &sum=dp[x][now+100][n-cnt_t][(sum_t-cnt_t)&1];//定义指针（写的方便）
	if(sum) return sum;//记忆化搜索
	if(c[x]=='F')//如果是F,那么不转换
	{
		int m=((sum_t-cnt_t)&1)?-1:1;
		//判断当前方向，出现的T减改变的T如果是奇数则方向与初始相反，距离-1，否则距离+1
		return sum=dfs(x+1,cnt_t,sum_t,now+m);//搜下一个命令
	}
	if(c[x]=='T')
	{
		int ans1=dfs(x+1,cnt_t,sum_t+1,now);
		int m=((sum_t-cnt_t)&1)?-1:1;
		int ans2=dfs(x+1,cnt_t+1,sum_t+1,now+m);
     	//改变和不改变的情况所得的答案
		return sum=max(ans1,ans2);//取两者最大值
	}
}

int main()
{
	scanf("%s%d",c,&n);//输入，没的说
	l=strlen(c);//求c的长度

	dfs(0,0,0,0);//从0开始搜

	printf("%d\n",ans);//输出答案

	return 0;
}
~~~

---

## 作者：GavinCQTD (赞：0)

# 题解：CF132C Logo Turtle

## 思路

根据题意，dfs 枚举即可。\
同时，我们可以记忆化降低时间。
设 `vis[i][j][k][l]` 代表当前执行第 $i$ 个指令，已经修改了 $j$ 个，距 $0$ 点 $k$ 格，方向为 $l$ 时的状态是否被搜索过。\
注意：每次 dfs 需要单独搜索 $j+2$ 的情况。

## 代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int n,len=0,ans=0;
bool vis[105][105][105][5];
string s;

void dfs(int i,int j,int k,int l){
    if(vis[i][j][k][l]) return;
    vis[i][j][k][l] = 1;
    if(i>len||j>n) return;
    if(i==len&&j==n){
        ans = max(ans,abs(k));
        return;
    }
    
    if(s[i]=='F'){
        // F 不变
        if(l==0) dfs(i+1,j,k-1,l);
        else dfs(i+1,j,k+1,l);

        // F 变 T
        if(l==0) dfs(i+1,j+1,k,1);
        else dfs(i+1,j+1,k,0);
    }
    else{
        // T 不变
        if(l==0) dfs(i+1,j,k,1);
        else dfs(i+1,j,k,0);

        // T 变 F
        if(l==0) dfs(i+1,j+1,k-1,l);
        else dfs(i+1,j+1,k+1,l);
    }
    dfs(i,j+2,k,l);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> s >> n;
    len = s.length();

    dfs(0,0,0,0);

    cout << ans;
    return 0;
}
```

---

## 作者：Happy_mouse (赞：0)

# [Logo Turtle](https://www.luogu.com.cn/problem/CF132C) 题解
### 写在前面
CF 的 RemoteJudge 这段时间崩了，在本校 OJ 上测试是 AC，发篇题解~~祭奠~~纪念一下。

## 分析与解答
好像大家都用的记忆化搜索，我的想法似乎不太一样~~导致代码又长又臭~~，拿来分享一波。

小乌龟有两个方向可以跑对吧，设定初始方向为正方向，那么小乌龟的坐标就可以用一个整数来表示，最远距离即为坐标绝对值中最大。

最大值中又分两种：最大正数，或是最小负数（则绝对值更大）。

因此分别对最大值与最小值进行 DP。

两开三维动规数组，则 $dp_{i,j,opt}$ 表示进行到第 $i$ 步行动，已经改变 $j$ 次，面对方向 $opt$（$0$ 为负方向，$2$ 为正方向，便于操作，代码中有解释）时可以到达的最大/最小距离。

注意，此时数组里还保留正负号，便于进行大小比较与移动，最后求出答案时才会取绝对值。

状态转移方程有点小复杂，详见代码。

~~KaTeX 弄起来是真累啊~~

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int f[105][55][3];//存最大
int f2[105][55][3];//存最小
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	int n;
	cin>>s>>n;
	int len=s.size();//取得操作数
	//进行初始化，全部设为无解
	for(int i=1;i<=len;i++){
		for(int j=0;j<=n;j++) f[i][j][0]=f[i][j][2]=f2[i][j][0]=f2[i][j][2]=1e15;
	}
	for(int i=0;i<=n;i++){
		if(i%2==(s[0]=='T')/*这里有点小简化，不然代码太长了，不理解自己推一下*/) f[1][i][2]=f2[1][i][2]=1;//向前移动，方向为正
		else f[1][i][0]=f2[1][i][0]=0;//转方向，设为负方向
	}
	for(int i=2;i<=len;i++){
		//对上一轮的结果进行继承
		for(int j=0;j<=n;j++){
			for(int fx=-1;fx<=1;fx+=2){
				//这里就体现了把方向设为 0,2 的好处
				//正、负方向各往前走一个单位就是 +1/-1，即 fx 变量
				//在确定方向时，直接用 fx+1 就可以标出正负方向
				//主要是数组不能开到 -1 去，否则就根本不需要 fx+1 了
				if(s[i-1]=='F'){
					if(f[i-1][j][fx+1]!=1e15) f[i][j][fx+1]=f[i-1][j][fx+1]+fx;
					if(f2[i-1][j][fx+1]!=1e15) f2[i][j][fx+1]=f2[i-1][j][fx+1]+fx;
				}
				else{
					if(f[i-1][j][-fx+1]!=1e15) f[i][j][fx+1]=f[i-1][j][-fx+1];
					if(f2[i-1][j][-fx+1]!=1e15) f2[i][j][fx+1]=f2[i-1][j][-fx+1];
				}
			}
		}
		//DP转移方程就是这一大坨（还是我简化过的）
		//知道我为啥刚刚不写了吗……
		//要是不简化，不加注释都得有七八十行（我t*****，头都大了）
		for(int j=1;j<=n;j++){
			for(int k=1;k<=j;k++){
				for(int fx=-1;fx<=1;fx+=2){
					if(k%2==(s[i-1]=='T')/*这儿又是简化，不懂自己分情况讨论*/&&f[i-1][j-k][fx+1]!=1e15/*判无解，否则不能用它来更新*/)
						f[i][j][fx+1]=max(f[i][j][fx+1],f[i-1][j-k][fx+1]+fx);//更新当前最大
					//下面同理，不写了
					if(k%2==(s[i-1]=='T')&&f2[i-1][j-k][fx+1]!=1e15)
						f2[i][j][fx+1]=min(f2[i][j][fx+1],f2[i-1][j-k][fx+1]+fx);
					if(k%2==(s[i-1]=='F')&&f[i-1][j-k][-fx+1]!=1e15)
						f[i][j][fx+1]=max(f[i][j][fx+1],f[i-1][j-k][-fx+1]);
					if(k%2==(s[i-1]=='F')&&f2[i-1][j-k][-fx+1]!=1e15&&f2[i][j][fx+1]>f2[i-1][j-k][-fx+1])
						f2[i][j][fx+1]=min(f2[i][j][fx+1],f2[i-1][j-k][-fx+1]);
				}
			}
		}
	}
	//分别把有解情况的距离取绝对值，取最大
	int ans=-1;//因为距离一定非负，初值赋值为 -1 即可
	if(abs(f[len][n][2])!=1e15) ans=max(ans,abs(f[len][n][2]));
	if(abs(f[len][n][0])!=1e15) ans=max(ans,abs(f[len][n][0]));
	if(abs(f2[len][n][0])!=1e15) ans=max(ans,abs(f2[len][n][0]));
	if(abs(f2[len][n][2])!=1e15) ans=max(ans,abs(f2[len][n][2]));
	//输出
	cout<<ans;
	return 0;//华丽结束
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
看见 $n\le50$，我们可以想到暴搜，我们需要 $4$ 个参数：当前位置、当前字符下标、已使用修改次数、当前行使方向。对于 $s_i=\text F$ 的情况，则有两种选择：不修改，则位置行驶一格，下标加 $1$，修改次数不变，行驶方向不变；修改，则位置不变，下标加 $1$，修改次数加 $1$，行使方向改变。对于 $s_i=\text T$ 的情况，也有两种选择：不修改，则位置不变，下标加 $1$，修改次数不变，行驶方向改变；修改，则位置走一个，下标加 $1$，修改次数加 $1$，行驶方向不变。最后套个记忆化就行啦。

因为可以反复修改，所以在统计答案时不必修改次数 $=n$，而是只要和 $n$ 同奇偶就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, k, maxx;
string a;
bitset <2> vis[105][205][55];
void dfs (int step, int now, int use, int dir) {
	if (use > k || vis[step][now + 100][use][dir])
		return ;
	vis[step][now + 100][use][dir] = 1;
	if (step >= n) {
		if ((use ^ k ^ 1) & 1)
			maxx = max (maxx, abs (now));
		return ;
	}
	if (a[step] == 'F')
		dfs (step + 1, now + dir, use, dir), dfs (step + 1, now, use + 1, -dir);
	else
		dfs (step + 1, now, use, -dir), dfs (step + 1, now + dir, use + 1, dir);
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> a >> k;
	n = a.size ();
	dfs (0, 0, 0, 1);
	cout << maxx;
	return 0;
}
```

---

## 作者：_HMZ_ (赞：0)

## 题目大意：

有一只海龟，初始在数轴上 $0$ 的位置，再给定一个序列。

海龟会一步一步的执行，如果当前是 `F`，则他会往前走一步。如果当前是 `T`，则它会转 $180 \degree$。

你必须精确的修改 $k$ 步，但每一个位置可以多次修改，问海龟最远能走多远（正方向）。

## 解题思路：

很明显是 dp 了。设 $dp_{i,j,0/1}$ 为前 $i$ 个命令，修改 $j$ 个，最后方向是 $0/1$ 时的最远距离。

~~然后随便搞搞就好了~~。

由于单个命令可以改多次，所以要再枚举一重 $w$，既为当前命令花几次操作来改变。

倘若在更改完之后为 `F`，那么就按照当前方向走一步，否则改变当前方向。

注意这里要求严格改 $k$ 次，所以在 $i=1$ 的时候 $w$ 一定要从 $j$ 开始。

否则如果第一个命令改 $w$ 次，但命令个数有 $j$ 个，就会变成第 $0$ 个命令改变 $j-w$ 次。

显然，这样的情况会使得最后不是精确 $k$ 次。

## AC代码：

```cpp
#include<iostream>
using namespace std;
int k, dp[105][105][2];
string s;
int main()
{
	cin >> s >> k;
	for (int i = 1; i <= s.size(); i++)//当前枚举到第几位了，从1开始方便处理。
	{
		for (int j = 0; j <= k; j++)//当前改变了几步。
		{
			for (int f = 0; f <= 1; f++)//当前方向。
			{
				dp[i][j][f] = -0x3f3f3f3f;
				for (int w = (i == 1 ? j : 0); w <= j; w++)//在当前位置花多少个次数来更改。
				{
                			//这里有个小优化，如果 w 是偶数，且当前是 T；
                       			//或者说 w 是奇数但当前是 F，这两种情况都会变成 T。
					if (w % 2 + (s[i - 1] == 'T') == 1)
						dp[i][j][f] = max(dp[i - 1][j - w][!f], dp[i][j][f]);//当前命令为 T。
					else
						dp[i][j][f] = max(dp[i][j][f], dp[i - 1][j - w][f] + (f == 0 ? 1 : -1));//否则当前命令是 F
				}
			}
		}
	}
	cout << max(dp[s.size()][k][1], dp[s.size()][k][0]);
	return 0;
}//ck
```


---

