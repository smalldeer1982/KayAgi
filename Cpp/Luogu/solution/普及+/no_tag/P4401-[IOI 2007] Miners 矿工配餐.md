# [IOI 2007] Miners 矿工配餐

## 题目描述

现有两个煤矿，每个煤矿都雇用一组矿工。采煤工作很辛苦，所以矿工们需要良好饮食。每当一辆食品车到达煤矿时，矿工们便会产出一定数量的煤。

有三种类型的食品车：肉车，鱼车和面包车。
矿工们喜欢变化的食谱。如果提供的食品能够不断变化，他们的产煤量将会增加。每当一个新的食品车到达煤矿时，矿工们就会比较这种新的食品和前两次（或者少于两次，如果前面运送食品的次数不足两次）的食品，并且：

- 如果这几次食品车都是同一类型的食品，则矿工们产出一个单位的煤。
- 如果这几次食品车中有两种不同类型的食品，则矿工们产出两个单位的煤。
- 如果这几次食品车中有三种不同类型的食品，则矿工们产出三个单位的煤。

预先已知食品车的类型及其被配送的顺序。通过确定哪车食品送到哪个煤矿可以影响产煤量。食品车不能被拆分，每个食品车必须被全部送到一个或另一个煤矿。两个煤矿也并不要求接收相同数量的食品车（事实上，也允许将所有食品车都送到一个煤矿）。

给出食品车的类型及其被配送的顺序，要求你写一个程序，确定哪个食品车应被送到煤矿 $1$，哪个食品车应被送到煤矿 $2$，以使得两个煤矿的产煤量的总和最大。

## 说明/提示

在样例 $1$ 中，可以按照如下的顺序运送食品车：煤矿 $1$，煤矿 $1$，煤矿 $2$，煤矿 $2$，煤矿 $1$，煤矿 $2$，依次产生的产煤量为 $1, 2, 1, 2, 3$ 和 $3$ 个单位，一共是 $12$ 个单位。

还有其它运送方式也能产生上述最大总和的产煤量。

## 样例 #1

### 输入

```
6
MBMFFB```

### 输出

```
12```

## 样例 #2

### 输入

```
16
MMBMBBBBMMMMMBMB```

### 输出

```
29```

# 题解

## 作者：Mr_QwQ (赞：18)

![毒矿万岁](https://cdn.luogu.com.cn/upload/pic/18947.png)

AC的第一道IOI题目，发个题解纪念一下。

这个题是一个相当基础的dp，唯一的难点在于代码实现。

令dp[i][a1][a2][b1][b2]为当前送第i辆车，第一个矿前两次送a1和a2，第二个前两次送b1和b2。

然后直接看这辆车送第一个矿还是第二个就好了。

边界是第n+1辆车，某个矿前两辆车没送的情况就直接用0占位就好。

这里用的是记忆化，由于数据小，时空问题都不大。如果觉得记忆化可能会MLE/爆栈可以改用逆序dp（可以把i滚动掉），但是代码会复杂很多，不如记忆化好写，~~像我这样的~~萌新可以先用记忆化写一遍，再照着写dp。

代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,type[100010],dp[100010][4][4][4][4];
char ch;
char getchar(int){
    char c='\0';
    while(c!='M' && c!='F' && c!='B')c=getchar();
    return c;
}
int food(char c){
    if(c=='M')return 1;
    if(c=='F')return 2;
    if(c=='B')return 3;
    return -1;
}
int coal(int fa,int fb,int fc){
    if(!fa && !fb)return 1;
    if(!fa)return (fb!=fc)+1;
    if(fa==fb && fb==fc)return 1;
    return (fa!=fb)+(fb!=fc)+(fa!=fc);
}
int dfs(int now,int a1,int a2,int b1,int b2){
    if(now>n)return 0;
    if(dp[now][a1][a2][b1][b2])return dp[now][a1][a2][b1][b2];
    return dp[now][a1][a2][b1][b2]=max(dfs(now+1,a2,type[now],b1,b2)+coal(a1,a2,type[now]),dfs(now+1,a1,a2,b2,type[now])+coal(b1,b2,type[now]));
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        ch=getchar(233);
        type[i]=food(ch);
    }
    printf("%d\n",dfs(1,0,0,0,0));
    return 0;
}
```

---

## 作者：TRZ_2007 (赞：5)

**[题解 P4401 【[IOI2007]Miners 矿工配餐】](https://www.luogu.com.cn/problem/P4401)**  
# Solution  
其实重点就是这三句：
- 1：如果这几次食品车都是同一类型的食品，则矿工们产出一个单位的煤。

- 2：如果这几次食品车中有两种不同类型的食品，则矿工们产出两个单位的煤。  
- 3：如果这几次食品车中有三种不同类型的食品，则矿工们产出三个单位的煤。  

看懂了这三句后，我们来想动规。  
**状态定义**：看见有 $n$ 个物品，首先我们就要想到定义 $f(n)$ 表示送完第 $n$ 个物品后产煤量的最大值，因为产煤量和前面两次送的食物有关，所以我们引用LJ的名言：**加一维**，只不过这里要加4维罢了，于是乎最后的定义是：$f(n,a,b,c,d)$ 表示送完第 $n$ 个物品后且一号矿洞前两次的食物为 $a$ 和 $b$，二号矿洞前两次的食物为 $c$ 和 $d$ 。  
**转移方程**：显然，对于每一种食物，我们既可以把它放入一号矿洞，也可以把它放入二号矿洞，我们可以计算出放入这些矿洞后的产煤数，并取一个最大值即可。 

所以我们可以得到如下代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int N = 100009;
 
char s[N];
int n,len,a[N],ans = 0;
 
int dp[N][4][4][4][4];
 
int calc(int nw,int i,int j) {
    int cnt = 1;
    if(nw && nw != i && nw != j) cnt++;
    if(i && i != j) cnt++;
    return cnt;
}
 
int main() {
    scanf("%d",&n);
    scanf("%s",s + 1);
    for(int i = 1;i <= n;i++) {	//	为了方便计算，我们在这里把它转成数字
        if(s[i] == 'M') a[i] = 1;
        if(s[i] == 'F') a[i] = 2;
        if(s[i] == 'B') a[i] = 3;
    }
    memset(dp,-1,sizeof(dp));	//最初时所有状态都不存在
    dp[0][0][0][0][0] = 0;	//初始化状态
    for(int i = 1;i <= n;i++) {
        for(int a1 = 0;a1 < 4;a1++) {	//枚举所有的可能性
            for(int a2 = 0;a2 < 4;a2++) {
                for(int b1 = 0;b1 < 4;b1++) {
                    for(int b2 = 0;b2 < 4;b2++) {
                        if(dp[i - 1][a1][a2][b1][b2] == -1) continue;
                        int tmp1 = dp[i - 1][a1][a2][b1][b2] + calc(a1,a2,a[i]);	//计算把煤放入一号矿洞的收益
                        int tmp2 = dp[i - 1][a1][a2][b1][b2] + calc(b1,b2,a[i]);	//计算把煤放入二号矿洞的收益
                        dp[i][a2][a[i]][b1][b2] = max(dp[i][a2][a[i]][b1][b2],tmp1);
                        dp[i][a1][a2][b2][a[i]] = max(dp[i][a1][a2][b2][a[i]],tmp2);
                    }	//对其取最大值
                }
            }
        }
    }
    for(int a1 = 0;a1 < 4;a1++) {	//枚举可能解
        for(int a2 = 0;a2 < 4;a2++) {
            for(int b1 = 0;b1 < 4;b1++) {
                for(int b2 = 0;b2 < 4;b2++) {
                    ans = max(ans,dp[n][a1][a2][b1][b2]);
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
```  

当你兴致冲冲地打完代码后，你会发现它MLE了。  
为什么？因为这份代码的空间复杂度达到了 $\Theta(256N)$，面对 18 MB 的空间限制无疑会爆炸。  
怎么办？我们需要加优化，关于第一维的 $i$，我们发现它只和 $i-1$ 有关，所以我们对于 $i$ 和 $i-1$ 将其对 2 取模，结果不会受到影响。  

最后的 AC 代码如下：  
# Code 
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100009;

int f[2][4][4][4][4];
char s[N];
int a[N],ans,n;

int turn(char ch) {
	if(ch == 'M') return 1;
	if(ch == 'F') return 2;
	if(ch == 'B') return 3;
}

int calc(int nw,int i,int j) {
	int cnt = 1;
	if(nw && nw != i && nw != j) cnt++;
	if(i && i != j) cnt++;
	return cnt;
}

int main() {
	scanf("%d",&n);
	scanf("%s",s + 1);
	for(int i = 1;i <= n;i++) {
		a[i] = turn(s[i]);
	}
	memset(f,-1,sizeof(f));
	f[0][0][0][0][0] = 0;
	for(int i = 1;i <= n;i++) {
		for(int a1 = 0;a1 < 4;a1++) {
			for(int b1 = 0;b1 < 4;b1++) {
				for(int a2 = 0;a2 < 4;a2++) {
					for(int b2 = 0;b2 < 4;b2++) {
						if(f[(i - 1) % 2][a1][b1][a2][b2] == -1) continue;
						int tmp1 = f[(i - 1) % 2][a1][b1][a2][b2] + calc(a1,b1,a[i]);
						int tmp2 = f[(i - 1) % 2][a1][b1][a2][b2] + calc(a2,b2,a[i]);
						f[i % 2][b1][a[i]][a2][b2] = max(f[i % 2][b1][a[i]][a2][b2],tmp1);
						f[i % 2][a1][b1][b2][a[i]] = max(f[i % 2][a1][b1][b2][a[i]],tmp2);
					}
				}
			}
		}
	}
	for(int a1 = 0;a1 < 4;a1++) {
		for(int b1 = 0;b1 < 4;b1++) {
			for(int a2 = 0;a2 < 4;a2++) {
				for(int b2 = 0;b2 < 4;b2++) {
					ans = max(ans,f[n % 2][a1][b1][a2][b2]);
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：SIGSEGV (赞：4)

经典的滚动数组啊.......

方程没什么难的，各位dalao都已经讲过了：f[i][a][b][c][d]:第一矿场前两次吃a,b 第二矿场前两次吃c,d的最大价值。

直接上代码吧（滚动技巧见代码）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[2][4][4][4][4],n;
char s[100004];
int sub(char s) //返回对应的下标
{
    if (s == 'M') return 2;
    if (s == 'F') return 3;
    return 1;
}
int val(int a,int b,int c) //第一次吃a，第二次吃b，第3次吃c，产出的价值
{
    int ret = 1;
    if (a && a != b && a != c) ret++;
    if (b && b != c) ret++;
    return ret;
}
int main ()
{
    scanf("%d",&n);scanf("%s",s + 1);//读入操作
    memset(dp,-1,sizeof(dp));
    dp[0][0][0][0][0] = 0; 
    for (int i = 1;i <= n;i++)
    {
        for (int a1 = 0;a1 < 4;a1++)
            for (int a2 = 0;a2 < 4;a2++)
                for (int a3 = 0;a3 < 4;a3++)
                    for (int a4 = 0;a4 < 4;a4++)
                    {
                        if (dp[(i + 1) % 2][a1][a2][a3][a4] == -1) continue;//上一轮的当前状态不存在，无法推出下一个
                        int b = sub(s[i]);
                        dp[i % 2][a2][b][a3][a4] = 
                        max(dp[i % 2][a2][b][a3][a4],
                        dp[(i + 1) % 2][a1][a2][a3][a4] + val(a1,a2,b));//送给第一个煤矿（i % 2是滚动操作）
                        dp[i % 2][a1][a2][a4][b] = 
                        max(dp[i % 2][a1][a2][a4][b],
                        dp[(i + 1) % 2][a1][a2][a3][a4] + val(a3,a4,b));//送给第二个煤矿
                    }
        memset(dp[(i + 1) % 2],-1,sizeof(dp[(i + 1) % 2]));//清空上一轮的递推状态
    }
    int ans = 0;
    for (int a1 = 0;a1 < 4;a1++)
            for (int a2 = 0;a2 < 4;a2++)
                for (int a3 = 0;a3 < 4;a3++)
                    for (int a4 = 0;a4 < 4;a4++)
                        ans = max(ans,dp[n % 2][a1][a2][a3][a4]);
    printf("%d",ans);
    return 3;
}
```



---

## 作者：intel_core (赞：2)

UPD ON 20/05/27
人生中第二道IOI题目，纪念一下  
暴力算法DFS（直接搜，不讲了）   （？？？pts)   

### 下面考虑如何优化这个DFS 

观察题目，可以发现：  
*   解题时只关心两个煤矿最近3个食物车的食物  
*   食物车的顺序固定
*   我只关心产煤量的最大值

根据上面那一句话的性质，我们可以考虑DP了  
~~如果下文和你想象的不太一样，那说明你没读懂第6行那一句话，请再读一遍~~  

令`f[i][S1][S2]`表示考虑到第i个食物车，第一个煤矿的最近两个食物为S1，第二个煤矿的最近两个食物为S2时的最大煤产量 
你会发现，S1明明表示了两个食物，为什么只用S1一个量就可以了呢？  

这里讲一个能使代码更好调的技巧：状压  
*  0表示没有食物
*  1表示`Meat`
*  2表示`Fish`
*  3表示`Bread`  

这样我们就可以用一个四进制数来表示连续两个食物了  
calc函数表示三个量中不同量的个数（注意0）  
如何转移？ 
```cpp
f[i&1][((t1&3)<<2)|a[i]][t2]=max(f[(i-1)&1][t1][t2]+calc(t1>>2,t1&3,a[i]),f[i&1][((t1&3)<<2)|a[i]][t2]);
f[i&1][t1][((t2&3)<<2)|a[i]]=max(f[(i-1)&1][t1][t2]+calc(t2>>2,t2&3,a[i]),f[i&1][t1][((t2&3)<<2)|a[i]]);
```
位运算TIPS：    
*  x&3为取二进制数x的后两位
*  本题需要将f数组循环利用 ~~MLE别找我~~
*  x>>2为取x前两位
*  由于本题a[i]只占两位，所以`((t2&3)<<2)|a[i]`与`((t2&3)<<2)+a[i]`是等价的

上代码 
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstring>
using namespace std;
const int NR=1e5+10;
const int MR=4;
int f[3][1<<MR][1<<MR];
int a[NR];
int calc(int x,int y,int z){
	if(y==0)y=z;
	if(x==0)x=y;
	int cnt=(x==y)+(y==z)+(z==x);
	if(cnt==3)return 1;
	if(cnt==1)return 2;
	return 3;
}
int main(int argc, char const *argv[])
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;
		scanf(" %c",&c);
		if(c=='M')a[i]=1;
		if(c=='F')a[i]=2;
		if(c=='B')a[i]=3;
	}
	memset(f,-999999,sizeof(f));
	f[0][0][0]=0;
	for(int i=1;i<=n;i++){
		memset(f[i&1],-999999,sizeof(f[i&1]));
		for(int t1=0;t1<16;t1++)
			for(int t2=0;t2<16;t2++){
				f[i&1][((t1&3)<<2)|a[i]][t2]=max(f[(i-1)&1][t1][t2]+calc(t1>>2,t1&3,a[i]),f[i&1][((t1&3)<<2)|a[i]][t2]);
				f[i&1][t1][((t2&3)<<2)|a[i]]=max(f[(i-1)&1][t1][t2]+calc(t2>>2,t2&3,a[i]),f[i&1][t1][((t2&3)<<2)|a[i]]);
			}
	}
	int ans=0;
	for(int i=0;i<=15;i++)
		for(int j=0;j<=15;j++)
			ans=max(ans,f[n&1][i][j]);
	cout<<ans;
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：1)

#### Description

> 给定 $n$ 个食品车，一共有三种，有两个矿洞，每个食品车都必须进且只能进一个矿洞，当某一个矿洞接收到某一个食品车后，矿洞内的工作人员会比较这次的食品车与前两次的食品车，设这三次食品车的品种去重后的个数为 $k$，矿洞人员则会产出 $k$ 的单位的矿。求安排食品车使得两个矿洞产出的总矿最多是多少个单位。

#### Solution

考虑状压 dp，本篇题解为主动转移，如果想看被动转移的同学请移步其他题解。

设 $f_{i,s_1,s_2}$ 为考虑到第 $i$ 个食品车，设矿洞分别为 A 和 B，A 前两个食品车的种类为 $s_1$，B 前两个食品车的种类为 $s_2$，$s_1$ 与 $s_2$ 为两个长度为 $4$ 的 01 串，如果 $s_1=\tt0110$，就代表 A 上上一个接收的食品车为 ${\tt01}=1$，上一个接收的食品车为 ${\tt10}=2$。

考虑主动转移，对于每一个食品车，分别可以转移给 A 和 B，即为分两种情况：

- 转移给 A：$f_{i,s_1,s_2} \to f_{i+1,s_1',s_2}$，其中 $s_1'$ 即为 A 接收第 $i+1$ 个食品车后得到的 01 串；
- 转移给 B：$f_{i,s_1,s_2} \to f_{i+1,s_1,s_2'}$，其中 $s_2'$ 即为 B 接收第 $i+1$ 个食品车后得到的 01 串。

转移量即为组成 01 串的两个食品车种类和 $a_{i+1}$ 三个数去重后的个数。

但如果这么打下来可能会 MLE，我们发现出题人这个大坏蛋给空间限制设置的是不到 18MB，让我们重拳出击，使用滚存。

#### Code

代码非常的难看冗长，仅供参考。

```cpp
#include <bits/stdc++.h>

using namespace std;

string s;
int a[100015]; 
int dp[3][16][16]; // dp[i][s1][s2]
int cnt[5];

int n12 (int n) {
	return n & 3;
}

int n34 (int n) {
	return n >> 2;
}

int ch (int a, int b, int c) {
	cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
	cnt[a] = cnt[b] = cnt[c] = 1;
	return cnt[1] + cnt[2] + cnt[3];
}

int main () {
	int n;
	scanf("%d", &n);
	cin >> s;
	s = " " + s;
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'M') a[i] = 1;
		if (s[i] == 'F') a[i] = 2; 
		if (s[i] == 'B') a[i] = 3;
	}
	memset(dp, -0x3f, sizeof(dp));
	dp[1][0][0] = 0;
	for (int i = 0; i < n; i++) {
		if (i != 0)
			for (int s1 = 0; s1 <= 15; s1++)
				for (int s2 = 0; s2 <= 15; s2++)
					dp[1][s1][s2] = dp[2][s1][s2], dp[2][s1][s2] = -0x3f3f3f3f;
		for (int s1 = 0; s1 <= 15; s1++)
			for (int s2 = 0; s2 <= 15; s2++) {
				int ch1 = ch(n12(s1), n34(s1), a[i + 1]), ch2 = ch(n12(s2), n34(s2), a[i + 1]);
				dp[2][((s1 << 2) + a[i + 1]) & 15][s2] = max(ch1 + dp[1][s1][s2], dp[2][((s1 << 2) + a[i + 1]) & 15][s2]);
				dp[2][s1][((s2 << 2) + a[i + 1]) & 15] = max(ch2 + dp[1][s1][s2], dp[2][s1][((s2 << 2) + a[i + 1]) & 15]);
			}
	}
	int ans = 0;
	for (int s1 = 0; s1 <= 15; s1++)
		for (int s2 = 0; s2 <= 15; s2++)
			ans = max(ans, dp[2][s1][s2]);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：_Imaginary_ (赞：1)

告诉大家一个非常有（mei）用的方法：遇到不会的题就 $DP$ ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！


好，言归正传。

令 $dp[i][a][b][c][d]$ 为前两次配餐为 a , b ; c , d ，通过推导容易得到。

## 代码解释：

 fun 函数求的是最近三次配餐得到的煤矿有多少。 ~~（我在思考如果矿工吃煤矿会怎么样）~~ 
 
 cmax 由于本人~~很懒~~怕时间超限不想写 $max(a,b)$ 函数。

## 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int dp[2][4][4][4][4];
int n;
char s[100005];
void cmax(int &a,int b)
{
	if(b>a) a=b;
}
int get(int x)
{
	return s[x]=='M'? 1:(s[x]=='B'? 2:3);
}
int fun(int a,int b,int c)//统计abc三数之间不同的个数
{
	if(!a && !b)return 1;
	if(!a)return (b!=c)+1;
	if(a==b && b==c)return 1;
	return (a!=b)+(b!=c)+(a!=c);
}
int main()
{
	scanf("%d",&n);
	memset(dp,-1,sizeof(dp));
	dp[0][0][0][0][0]=0;
	scanf("%s",s+1);
	int x;
	for(int i=1;i<=n;i++)
	{
		x=get(i);
		for(int a=0;a<=3;a++)
		for(int b=0;b<=3;b++)
		for(int c=0;c<=3;c++)
		for(int d=0;d<=3;d++)
		{
			if(dp[(i+1)%2][a][b][c][d]==-1) continue;
			cmax(dp[i%2][b][x][c][d],dp[(i+1)%2][a][b][c][d]+fun(a,b,x));//
			cmax(dp[i%2][a][b][d][x],dp[(i+1)%2][a][b][c][d]+fun(c,d,x));//
		}
	}
  int ans=0;
  for(int a=0;a<=3;a++)
  for(int b=0;b<=3;b++)
  for(int c=0;c<=3;c++)
  for(int d=0;d<=3;d++)
  {
  if(dp[n%2][a][b][c][d]!=-1) cmax(ans,dp[n%2][a][b][c][d]);
  }
  printf("%d",ans);
  return 0;
}
```

最后的最后，祝大家 $RP++$ ！

---

## 作者：HeCao2008 (赞：0)

~~之前那个写的太烂了，认真写一个~~

### 题意：
在两个矿坑中选择一个投放食品，来计算最大的**满意度**（因为生产的煤就相当于满意度）。其中，满意度取决于**食品种类的数目**。


### 算法：
这题题目一看就很 $dp$ 的样子。所以重点在于**状态转移方程**。
我们用 $dp[1][a1][a2][b1][b2]$ 来存第  $i$ 辆车去 $a$ 地前两次所放的食品 （$a1,a2$），去 $b$ 地前两次所投放的食品 （$b1,b2$） 的答案。

对于每次送，都有矿地 $a$ 与矿地 $b$ 两种情况，两种选择中，有与原先答案比较的内容。状态转移方程就出来了：

```cpp
dp[i][i2][a[i]][i3][i4]=max(dp[i][i2][a[i]][i3][i4],dp[i][i1][i2][i3][i4]+_main(i1,i2,a[i])); //将 a[i] 送到矿地 a 的情况。

dp[i][i1][i2][i4][a[i]]=max(dp[i][i1][i2][i4][a[i]],dp[i-1][i1][i2][i3][i4]+_main(i3,i4,a[i])); //将 a[i] 送到矿地 b 的情况。
```

### 优化：
这道题有一个比较难的点，就是**空间限制**，用上面的状态转移方程会炸，那么怎么优化呢？

这里介绍一种方案叫**滚动数组**，它的原理很好证明：

由于第一维 $i$ 的运算只有 $i,i-1$ 这种操作，所以可以将 $i$ 对 $2$ 取模，这样，第一维数组只需要开到 $2$ 就行了。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[2][4][4][4][4]; //五维数组
int a[100001];char c[100001];
int _main(int a,int b,int c){ //计算满意度
	int cnt=1;
	if(a!=0&&a!=b&&a!=c)cnt++;
	if(b!=0&&b!=c)cnt++;
	return cnt;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++){
		if(c[i]=='M')a[i]=1;
		if(c[i]=='F')a[i]=2;
		if(c[i]=='B')a[i]=3;
	} /转成数字做，方便。
	memset(dp,-1,sizeof(dp));
	dp[0][0][0][0][0]=0; //初始值
	for(int i=1;i<=n;i++){
		for(int i1=0;i1<=3;i1++){
			for(int i2=0;i2<=3;i2++){
				for(int i3=0;i3<=3;i3++){
					for(int i4=0;i4<=3;i4++){
						if(dp[(i-1)%2][i1][i2][i3][i4]==-1)continue;
						dp[i%2][i2][a[i]][i3][i4]=max(dp[i%2][i2][a[i]][i3][i4],dp[(i-1)%2][i1][i2][i3][i4]+_main(i1,i2,a[i])); //矿地 a
						dp[i%2][i1][i2][i4][a[i]]=max(dp[i%2][i1][i2][i4][a[i]],dp[(i-1)%2][i1][i2][i3][i4]+_main(i3,i4,a[i])); //矿地 b
					}
				}
			}
		}
	}
	int ans=-114514;
	for(int i1=0;i1<=3;i1++)for(int i2=0;i2<=3;i2++)for(int i3=0;i3<=3;i3++)for(int i4=0;i4<=3;i4++)ans=max(ans,dp[n%2][i1][i2][i3][i4]); //计算最终答案
	cout<<ans<<endl;
	return 0;
}
```

**有错误可以提出！谢谢！！！**

---

## 作者：Yukinoshita_Yukino (赞：0)

题意：将 $n$ 个食品车安排顺序输送到两个煤矿，食品车有三种类型。输送食品车到煤矿后，矿工产的煤数量上相当于最近三天食品种类数。求最大的产煤数量。

考虑 $dp$ 。设 $dp[i]$ 为前 $i$ 天产煤最大值，发现无法转移 $dp$ 数组，所以我们要**加维**。

转移 $dp$ 数组时要根据前几天矿工配餐的食品种类来转移，所以我们考虑记录前两天两个矿的食品种类。

设 $dp[i][a][b][c][d]$  为前 $i$ 天，第一个矿场吃了 $a$ 类 和 $b$ 类食物，第二个矿场吃了 $c$ 类 和 $d$ 类食物的最大产煤数量。

转移时分类讨论即可。

注意到这题直接开 $dp$ 数组会超出空间限制，所以要滚动数组优化。

代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char s[100010];
int dp[2][5][5][5][5];
int calc(int a,int b,int c)
{
	int sum=1;
	if(b&&b!=c) sum++;
	if(a&&a!=b&&a!=c) sum++;
	return sum;
}//计算产煤数量
int main()
{
	cin>>n;
	cin>>s+1;
	memset(dp,-1,sizeof dp);
	dp[0][0][0][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int a=0;a<=3;a++)
		{
			for(int b=0;b<=3;b++)
			{
				for(int c=0;c<=3;c++)
				{
					for(int d=0;d<=3;d++)
					{
						int now;
						if(s[i]=='M') now=1;
						if(s[i]=='F') now=2;
						if(s[i]=='B') now=3;
						if(dp[(i-1)%2][a][b][c][d]==-1) continue;
						dp[i%2][b][now][c][d]=max(dp[i%2][b][now][c][d],dp[(i-1)%2][a][b][c][d]+calc(a,b,now));
						dp[i%2][a][b][d][now]=max(dp[i%2][a][b][d][now],dp[(i-1)%2][a][b][c][d]+calc(c,d,now));
					}
				}
			}
		}
		
	}
	int ans=-0x7ffffff;
	for(int a=0;a<=3;a++)
	{
		for(int b=0;b<=3;b++)
		{
			for(int c=0;c<=3;c++)
			{
				for(int d=0;d<=3;d++)
				{
					ans=max(ans,dp[n%2][a][b][c][d]);
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：0x3F (赞：0)

这是一道 DP 好题。

$dp_{i, a, b, c, d}$ 表示前 $i$ 车已经分发完毕，$1$ 号煤矿上次吃的食品为 $a$，上上次为 $b$，$2$ 号煤矿上次吃的食品为 $c$，上上次为 $d$ 时的最大产煤量。

方便起见，我们设 `M` 是 $1$，`F` 是 $2$，`B` 是 $3$，如果不存在记为 $0$。（例如，当 $a$ 为 $0$ 时表示 $1$ 号煤矿没有吃过饭，当 $b$ 为 $0$ 时表示 $1$ 号煤矿只吃过一次饭。）

设 $cnt_{a, b, c}$ 表示一个煤矿最后三次吃的食物分别为 $a, b, c$ 时的产煤量。

DP 方程：若将食物给 $1$ 号煤矿，则 $dp_{i, q, a, r, s} = \max(dp_{i-1, p, q, r, s})$

若将食物给 $2$ 号煤矿，则 $dp_{i, p, q, s, a} = \max(dp_{i-1, p, q, r, s})$

其中 $a$ 表示本次的食物。

如果某一个状态不存在，则设其为 $-1$，而且转移时要特判。

然而，我们发现，内存 $17.58\operatorname{M}$。

果断使用滚动数组。

我打滚动数组的码风和大家不太一样，大佬勿喷。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a, ans;
char ch;
int dp[4][4][4][4], last[4][4][4][4];

int change(char ch) {
	switch (ch) {
		case 'M': {
			return 1;
			break;
		}
		case 'F': {
			return 2;
			break;
		}
		case 'B': {
			return 3;
			break;
		}
		default: {
			return 0;
			break;
		}
	}
}

int cnt(int a, int b, int c) {
	if (a = 0) return 1 + (b != c && b && c);
	if (b = 0) return 1 + (a != c && a && c);
	if (c = 0) return 1 + (a != b && a && b);
	return 1 + (a != b || a != c || b != c) + (a != b && b != c && a != c);
}

int main() {
	cin >> n;
	memset(last, -1, sizeof(last));
	last[0][0][0][0] = 0;
	for (int i = 1; i <= n; i++) {
		memset(dp, -1, sizeof(dp));
		cin >> ch;
		a = change(ch);
		for (int p = 0; p < 4; p++) {
			for (int q = 0; q < 4; q++) {
				for (int r = 0; r < 4; r++) {
					for (int s = 0; s < 4; s++) {
						if (last[p][q][r][s] == 0) continue;
						dp[q][a][r][s] = max(dp[q][a][r][s], last[p][q][r][s] + cnt(p, q, a));
						dp[p][q][s][a] = max(dp[p][q][s][a], last[p][q][r][s] + cnt(p, q, a));
					}
				}
			}
		}
		memcpy(last, dp, sizeof(dp));
	}
	for (int p = 0; p < 4; p++) {
		for (int q = 0; q < 4; q++) {
			for (int r = 0; r < 4; r++) {
				for (int s = 0; s < 4; s++) {
					ans = max(ans, dp[p][q][r][s]);
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

后记：

代码里有三个坑哦！

---

## 作者：Yang818 (赞：0)

### 注意：内存限制17.58MB！！！
### 题目大意：
其实就是要争取每次送的东西和前面的不一样，然后求出一个最大值。因为只有两个工厂，我们只用挨个看就能得出正解。所以本题还是很好做的。

题目中有这几处信息比较有用，为了方便大家看下去，我把它们罗列在这里：
```
·如果这几次食品车都是同一类型的食品，则矿工们产出一个单位的煤。

·如果这几次食品车中有两种不同类型的食品，则矿工们产出两个单位的煤。

·如果这几次食品车中有三种不同类型的食品，则矿工们产出三个单位的煤。
```

### 分析：
本来是想用贪心的，结果发现这道题目不具备最优子结构，你不知道后面还会有什么餐车，然后觉得可以用背包。因为只有三种食物，和两个工厂，$dp$ 方程中只用包含每个工厂的前面两次送餐的内容就行了。我们为了方便写代码，可以把肉，鱼和面包分别用 $1，2，3$ 来表示。吧从第一步到最后一步每一次的最优解算出来，最后在总地算一遍就能得到 $ans$ 了。来，一起看看方程怎么写。

### 方程
根据上面的分析，我们可以得到最基础的方程式：

$f[n][a][b][c][d]$表示推到第 $n$ 个食品车时第一个煤厂前面两次运的是 $a$ 和 $b$ ，第二个煤厂前面两次与的是 $c$ 和 $d$。

其中$n$的范围是$10^5$，$a,b,c,d$ 都是 $4$ ，稍微一估算就知道内存不大够。我们不妨来详细算一下内存 :

$100000\times4\times4\times4\times4\times4\div1024\div1024\approx24$

不用想，参见注意事项，肯定MLE

来，上滚动数组，把 $n$ 滚成只有 $2$ 维的。

好了，不多说了，看代码
```c
#include<bits/stdc++.h>
using namespace std; 

inline int read(){
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}

int change(char ch){//方便写程序  
	if(ch=='M')
		return 1;
	if(ch=='F')
		return 2;
	if(ch=='B')
		return 3;
}

int calc(int n,int a,int b){//算一下 产量 
	int c=1;
	if(n&&b!=n&&a!=n)
		c++;
	if(a&&b!=a)
		c++;
		return c;
}

int g_n;
int g_choi[3][4][4][4][4];
char s[100010];
int g_meal[100010];

int main(){
	g_n=read();
	scanf("%s",s+1);
	for(int i=1;i<=g_n;i++){
		g_meal[i]=change(s[i]);//转 
	}
	memset(g_choi,-1,sizeof(g_choi));
	g_choi[0][0][0][0][0]=0;//别忘了赋初值，要不然全WA 
	for(int i=1;i<=g_n;i++){
		for(int a1=0;a1<4;a1++){
			for(int b1=0;b1<4;b1++){
				for(int a2=0;a2<4;a2++){
					for(int b2=0;b2<4;b2++){//好好理解理解 
						if(g_choi[(i-1)%2][a1][b1][a2][b2]==-1)
							continue;
						int tmp=g_choi[(i-1)%2][a1][b1][a2][b2]+calc(a1,b1,g_meal[i]);
						int tmpp=g_choi[(i-1)%2][a1][b1][a2][b2]+calc(a2,b2,g_meal[i]);
						g_choi[i%2][b1][g_meal[i]][a2][b2]=max(tmp,g_choi[i%2][b1][g_meal[i]][a2][b2]);
						g_choi[i%2][a1][b1][b2][g_meal[i]]=max(tmpp,g_choi[i%2][a1][b1][b2][g_meal[i]]);
					}
				}
			}
		}
	}
	int q=g_n%2;
	int ans=-1;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			for(int x=0;x<4;x++){
				for(int y=0;y<4;y++){
					ans=max(ans,g_choi[q][i][j][x][y]);//算一遍最优解 
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```


    

---

## 作者：Kiloio (赞：0)

# DP  
首先设定**状态**。有**两个矿井**，生产煤数与最近吃的**食物品种**有关。  
  
数组也一定是要**滚动**的，此题空间只有$17.58MB$

我们就设$f[i][a][b][c][d]$为第$i$辆车时，**第一个**矿井送了$a$、$b$两种食物。**第二个**矿井送了$c$、$d$两种食物。  
  
现在就有**两种情况**，一是送到$1$号矿井，二是送到$2$号矿井。  
  
### 可以据此列出方程：

$f$[$i$&$1$][$a$][$b$][$d$][$x$]=$max$(f[($i+1$)&1][$a$][$b$][$c$][$d$]+$Mining$($c$,$d$,$x$),$f$[$i$&$1$][$a$][$b$][$d$][$x$])

$f$[$i$&$1$][$b$][$x$][$c$][$d$]=$max$($f$[($i$+$1$)&$1$][$a$][$b$][$c$][$d$]+$Mining$($a$,$b$,$x$),$f$[$i$&$1$][$b$][$x$][$c$][$d$]);  

解释一下，$Mining$是求煤数的函数，$i$&$1$是**滚动数组**（$i$&$1$等效于$i$%$1$）

### $Mining$里该写什么，怎么求煤数？  
## $3$种**普通情况**    

1. 几次食品车**都是同一类型**的食品，产**一个**单位煤。  

2. 几次食品车中有**两种不同类型**的食品，产出**两个单位**的煤。  

3. 几次食品车中有**三种不同类型**的食品，产出**三个单位**的煤。   

**伪代码**：  
```
int Mining(int q,int w,int e){
	if(q==w && w==e){//第一种情况
		return 1;
	}
	if(q!=w && w!=e && q!=e){//第三种情况
		return 3;
	}
	return 2;//第二种情况	
}
``` 

## $2$种**特殊情况**  

当是**第一次送餐**时，先前的情况**无法判断**。但是是$1$个单位的煤  

因为有**两个**矿井，当**前一次餐车送的不是自己所处的矿井**，也要**特判**。  
如果有两种则产$2$个单位煤，如果有一种则产$1$个单位煤。  
  
**判断**代码：  
```
if(q==0 && w==0){//第一次送餐
	return 1;
}

if(q==0){//前面一次没送到
	if(w!=e){
		return 2;
	}
	else{
		return 1;
	}
}
```  

就没了。**总代码**：  
```
#include <bits/stdc++.h>
using namespace std;
long long n,f[3][4][4][4][4],ans=-1,x; 
string s;
int change(char op){//转成数字方便操作 
	if(op=='M'){
		return 1;
	}
	if(op=='F'){
		return 2;
	}
	if(op=='B'){
		return 3;
	}
}
int Mining(int q,int w,int e){
	if(q==0 && w==0){//第一次送餐
		return 1;
	}
	if(q==0){//前面一次没送到
		if(w!=e){//2种食物 
			return 2;
		}
		else{//1种食物 
			return 1;
		}
	}
	
	if(q==w && w==e){//第一种情况
		return 1;
	}
	if(q!=w && w!=e && q!=e){//第三种情况
		return 3;
	}
	return 2;//第二种情况
}
int main(){
	cin>>n>>s;
	//不要忘了初始化 
	memset(f,-1,sizeof(f));
	f[0][0][0][0][0]=0;
	for(int i=1; i<=n; i++){
		x=change(s[i-1]);
		//0是有不送这个矿井的情况 
		for(int a=0; a<=3; a++){
			for(int b=0; b<=3; b++){
				for(int c=0; c<=3; c++){				
					for(int d=0; d<=3; d++){
						if(f[(i+1)&1][a][b][c][d]==-1){
							continue;
						}
						f[i&1][a][b][d][x]=max(f[(i+1)&1][a][b][c][d]+Mining(c,d,x),f[i&1][a][b][d][x]);
						f[i&1][b][x][c][d]=max(f[(i+1)&1][a][b][c][d]+Mining(a,b,x),f[i&1][b][x][c][d]);			
					}
				}
			}
		}
	}
	
	for(int a=0; a<=3; a++){
		for(int b=0; b<=3; b++){
			for(int c=0; c<=3; c++){				
				for(int d=0; d<=3; d++){
					ans=max(ans,f[n&1][a][b][c][d]);
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Bigfatpig (赞：0)

#### 这只是一道很普通的DP
##### ~~但是看到空间限制，感觉是不是出BUG了~~
#### 其实只要用一个滚动数组就行啦
### 记f[now][i][i1][j][j1]为当前now时矿洞一前两餐为i,i1,矿洞二前两餐为j,j1
#### 转移很显然f[now][k][i][j][j1]=max(f[now][k][i][j][j1],f[now^1][i][i1][j][j1]+xx(k,i,i1));
##### k表示当前食物的标号,xx函数表示能产出的煤矿
#### 最后在遍历一遍now求出最大输出就行
#### ~~滚动就是now指针异或1就行啦QWQ~~
```cpp
#include<bits/stdc++.h>

using namespace std;

int n,now;
char c[100010];
int f[2][4][4][4][4];

int cc(char c)//给食物标号
{
	if(c=='M')return 1;
	if(c=='F')return 2;
	if(c=='B')return 3;
}

int xx(int z,int y,int x)//计算煤矿产量
{
    if(!x && !y) return 1;
    if(!x) return 1+(y!=z);
    if(x==y && y==z) return 1;
    return(x!=y)+(y!=z)+(x!=z);
}

int main()
{
	scanf("%d\n",&n);
	scanf("%s",c+1);
	memset(f,-1,sizeof(f));
	f[0][0][0][0][0]=0;
	for(int l=1;l<=n;l++)
	{
		int k=cc(c[l]);
		now=l%2;
		for(int i=0;i<=3;i++)
		for(int i1=0;i1<=3;i1++)
		for(int j=0;j<=3;j++)
		for(int j1=0;j1<=3;j1++)
		{
			if(f[now^1][i][i1][j][j1]==-1)continue;//注意必须要特判,否则可能实际还没吃前两餐就已经有标记了
			f[now][k][i][j][j1]=max(f[now][k][i][j][j1],f[now^1][i][i1][j][j1]+xx(k,i,i1));
			f[now][i][i1][k][j]=max(f[now][i][i1][k][j],f[now^1][i][i1][j][j1]+xx(k,j,j1));
		}
	}
	int Max=0;
	for(int i=0;i<=3;i++)
	for(int i1=0;i1<=3;i1++)
	for(int j=0;j<=3;j++)
	for(int j1=0;j1<=3;j1++)
	Max=max(Max,f[now][i][i1][j][j1]);//求最大输出
	printf("%d\n",Max);
	return 0;
}
```

---

## 作者：calix_x (赞：0)

dp，f[i][a][b][c][d]表示送第i辆车来时矿洞1的前两次吃a和b，矿洞2的前两次吃c和d，当b或d为0表示该矿洞只送过一辆车，当a、b或c、d为0时表示该矿洞没送过车。i可以滚动掉，同时i需倒序枚举。求矿工采煤量的分类讨论比较复杂，具体看代码。


------------
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inc(i,j,k) for(int i=j;i<=k;i++)
#define dec(i,j,k) for(int i=j;i>=k;i--)
#define maxn 100010
using namespace std;

int cg(char a){
    if(a=='M')return 1;else if(a=='F')return 2;else if(a=='B')return 3;
}
int f[maxn],n,x[4][4][4][4],y[4][4][4][4]; char s[maxn];
int main(){
    scanf("%d",&n); scanf("%s",s+1);
    inc(i,1,n){if(s[i]=='M')f[i]=1; if(s[i]=='F')f[i]=2; if(s[i]=='B')f[i]=3;} memset(x,0,sizeof(x));
    dec(i,n,1){
        memset(y,0,sizeof(y));
        inc(j1,0,3)inc(j2,0,3)inc(j3,0,3)inc(j4,0,3){
            if((j1&&!j2)||(j3&&!j4))continue; int plus1,plus2;
            if((!j1&&!j2)||(!j1&&j2==f[i])||(j1==j2&&j2==f[i]))plus1=1;else
            if(j1!=j2&&j2!=f[i]&&j1!=f[i]&&j1&&j2)plus1=3;else plus1=2;
            if((!j3&&!j4)||(!j3&&j4==f[i])||(j3==j4&&j4==f[i]))plus2=1;else
            if(j3!=j4&&j4!=f[i]&&j3!=f[i]&&j3&&j4)plus2=3;else plus2=2;
            y[j1][j2][j3][j4]=max(x[j2][f[i]][j3][j4]+plus1,x[j1][j2][j4][f[i]]+plus2);        
        }
        swap(x,y);
    }
    printf("%d",x[0][0][0][0]); return 0;
}
```

---

## 作者：ricky0916 (赞：0)

~~告诉大家一件事：有一个人叫小明，无论给他什么食物他都能挖到1000000000000000000000个矿！（略略略）~~
# P4401 题解
## **本题解决方法：DP**
令没有食物=$ 0 $，肉=$ 1 $，鱼=$ 2 $，面包=$ 3 $ ~~（原来数字能吃啊）~~
设$ dp[n][i1][i2][j1][j2] $为送了前$ n $辆食品车，矿洞$ 1 $前两次送的食物为$ i1 $,$ i2 $,矿洞$ 2 $前两次送的食物为$ j1 $,$ j2 $

令第$ n $次送的食物为$ x $，$ f(i,j,k) $为$ i,j,k $三个食物中不同食物的数量，此时可以得到转移:

$ dp[n][x][i1][j1][j2]=max(dp[n][x][i1][j1][j2],dp[n-1][i1][i2][j1][j2]+f(i1,i2,x)) $

$ dp[n][i1][i2][x][j1]=max(dp[n][i1][i2][x][j1],dp[n-1][i1][i2][j1][j2]+f(j1,j2,x)) $

其实$ f(i,j,k) $不需要很多条件判断，搞个桶就好了

但是此时会$ MLE $。怎么办呢？

~~容易~~通过观察可以发现，$ n $的这一维可以用滚动数组滚掉，所以只需要$ dp[2][4][4][4][4] $就够了，内存只有$ 2*4*4*4*4*4B=1024B<12MB $

最后，程序还需注意细节

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[2][4][4][4][4],temp,p=0,q=1,t[4];
char s[100010];
int x(int c,int b,int a){
	memset(t,0,sizeof(t));
	t[a]=1;
	t[b]=1;
	t[c]=1;
	return t[1]+t[2]+t[3];
}
int main(){
	scanf("%d",&n);
	memset(dp,-1,sizeof(dp));
	dp[0][0][0][0][0]=0;
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='M') temp=1;
		if(s[i]=='F') temp=2;
		if(s[i]=='B') temp=3;
		for(int a=0;a<=3;a++){
			for(int b=0;b<=3;b++){
				for(int c=0;c<=3;c++){
					for(int d=0;d<=3;d++){
						if(dp[p][a][b][c][d]==-1) continue;
						dp[q][temp][a][c][d]=max(dp[q][temp][a][c][d],dp[p][a][b][c][d]+x(temp,a,b));
						dp[q][a][b][temp][c]=max(dp[q][a][b][temp][c],dp[p][a][b][c][d]+x(temp,c,d));
					}
				}
			}
		}
		p^=1;
		q^=1;
	}
	int ans=-1;
	for(int a=0;a<4;a++){
		for(int b=0;b<4;b++){
			for(int c=0;c<4;c++){
				for(int d=0;d<4;d++){
					ans=max(ans,dp[p][a][b][c][d]);
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```
~~我的程序写得特别丑~~

---

## 作者：YuRuiH_ (赞：0)

**~~裸的dp水题吧~~**


技巧是用一个二位的三进制数表示该仓库前两天的配餐类型。

0表示M，1表示F，2表示B

两天一共有九种情况
（00， 01， 02， 10， 11，12，20，21，22，用0到8来表示）

一个特殊情况是该仓库还未配过餐，用9表示，另一个特殊情况是该仓库只配过一次餐

这种情况等价于前两天配餐种类相同。


而程序中的check函数返回的是如果三天的配餐种类分别为a，b，c，则矿工的出矿量为多少。


之后的动态规划就是很常规的思路了，边界条件是两个仓库都未配餐时总出矿量为0，值得注意的是刷表法要比一般的递推更好写，代码如下。
```c
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxn = 100000 + 10;
int n;
int d[10][10][2];

int readchar () {
    char c = getchar();
    if (c == 'M') return 0;
    if (c == 'F') return 1;
    if (c == 'B') return 2;
}

int check (int a, int b, int c) {
    if (a == b && b == c && a == c) return 1;
    if (a != b && a != c && b != c) return 3;
    return 2;
}

int main ()
{
//  freopen("in.txt", "r", stdin);
    cin >> n; getchar();
    
    for (int i = 0; i < 10; i++) 
        for (int j = 0; j < 10; j++) 
            d[i][j][0] = -INF;
    
    d[9][9][0] = 0;
    int t = 0;
    for (int cur = 0; cur < n; cur++) {
        for (int i = 0; i < 10; i++) 
            for (int j = 0; j < 10; j++) d[i][j][t^1] = -INF;
        
        int food = readchar();
        for (int i = 0; i < 10; i++) 
            for (int j = 0; j < 10; j++) if (d[i][j][t] >= 0) {
                if (i == 9) d[food*3+food][j][t^1] = max(d[food*3+food][j][t^1], d[i][j][t]+1);
                else {
                    int f1 = i/3, f2 = i%3;
                    int next = f2*3+food;
                    int v = check(f1, f2, food);
                    d[next][j][t^1] = max(d[next][j][t^1], d[i][j][t]+v);
                }
                
                if (j == 9) d[i][food*3+food][t^1] = max(d[i][food*3+food][t^1], d[i][j][t]+1);
                else {
                    int f1 = j/3, f2 = j%3;
                    int next = f2*3+food;
                    int v = check(f1, f2, food);
                    d[i][next][t^1] = max(d[i][next][t^1], d[i][j][t]+v);
                }
        }
        t ^= 1;
    }
    int ans = -INF;
    for (int i = 0; i < 10; i++) 
        for (int j = 0; j < 10; j++) ans = max(ans, d[i][j][t]);
    
    cout << ans;
    return 0;
}
```

---

