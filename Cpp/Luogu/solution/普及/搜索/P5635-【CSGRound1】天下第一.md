# 【CSGRound1】天下第一

## 题目背景

天下第一的 cbw 以主席的身份在 8102 年统治全宇宙后，开始了自己休闲的生活，并邀请自己的好友每天都来和他做游戏。由于 cbw 想要显出自己平易近人，所以 zhouwc 虽然是一个蒟蒻，也有能和 cbw 玩游戏的机会。

## 题目描述

游戏是这样的：

给定两个数 $x$，$y$，与一个模数 $p$。

cbw 拥有数 $x$，zhouwc 拥有数 $y$。

第一个回合：$x\leftarrow(x+y)\bmod p$。

第二个回合：$y\leftarrow(x+y)\bmod p$。

第三个回合：$x\leftarrow(x+y)\bmod p$。

第四个回合：$y\leftarrow(x+y)\bmod p$。

以此类推....

如果 $x$ 先到 $0$，则 cbw 胜利。如果 $y$ 先到 $0$，则 zhouwc 胜利。如果 $x,y$ 都不能到 $0$，则为平局。

cbw 为了捍卫自己主席的尊严，想要提前知道游戏的结果，并且可以趁机动点手脚，所以他希望你来告诉他结果。

## 说明/提示

$1 \leq T \leq 200$。

$1 \leq x,y,p \leq 10000$。

## 样例 #1

### 输入

```
1 10
1 3
```

### 输出

```
error```

## 样例 #2

### 输入

```
1 10
4 5
```

### 输出

```
1```

# 题解

## 作者：MY（一名蒟蒻） (赞：85)

这题一看，第一反应**记忆化搜索**。看完标签，坚定了信心（但洛谷标签很多时候都是**骗人**的）。
## 记忆化搜索的好处：如果搜到以前的便无需再搜，直接返回。对每一个点最多只需找一次。极大的节省了时间。
**话不多说上**~~一开始的~~**代码**，注释嘛，请您看下去。
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int t,x,y,mod,book[10010][10010]; 
int rem(int x,int y)
{
	if(book[x][y] == -1) return -1;
	if(book[x][y]) return book[x][y];
	book[x][y]=-1;
	if(!x) return book[x][y]=1;
	if(!y) return book[x][y]=2;
	int num=(x+y)%mod;
	return book[x][y]=rem(num,(num%mod+y)%mod); 
}
int main()
{
	scanf("%d %d",&t,&mod);
	for(int i=0;i<t;i++) 
	{
		scanf("%d %d",&x,&y); 
		int ans=rem(x,y);
		if(ans == -1) puts("error");
		else if(ans == 1) puts("1");
		else puts("2");
	}
	return 0;
}
```
---
为什么煤油注释？因为这个代码**连窝本地编译都过不了**！

一看数据范围，这样肯定**会炸**呀！

什么？连int都炸？那**怎么办办**呢？

作者在深思熟虑一秒钟后，打开了[度娘](https://www.baidu.com/)。

### 原来还有个叫short的东西！！！

short只占用两个字节，而int需要4个。

---

**于是修改代码后就可以愉快地AC啦！**

```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int t,x,y,mod;//定义
short book[10010][10010]; 
int rem(int x,int y)
{
	if(book[x][y] == -1) return -1;//不行
	if(book[x][y]) return book[x][y];//如果之前搜到过
	book[x][y]=-1;//标记
	if(!x) return book[x][y]=1;//zhouwc赢
	if(!y) return book[x][y]=2;//cbw赢
	int num=(x+y)%mod;//num=处理后的x
    	//(num+y)%mod=处理后的y
	return book[x][y]=rem(num,(num%mod+y)%mod);//记忆化核心
}
int main()
{
	scanf("%d %d",&t,&mod);//读入
	for(int i=0;i<t;i++) 
	{
		scanf("%d %d",&x,&y); 
		int ans=rem(x,y);//搜索
        	//输出
		if(ans == -1) puts("error");
		else if(ans == 1) puts("1");
		else puts("2");
	}
	return 0;
}
```
~~话说zhouwc说踏寄几是蒟蒻你信吗？~~
#### 写题解不易，点个赞好不好嘛。——滚去写作业之前还厚颜无耻要赞的作者

---

## 作者：mot1ve (赞：28)

1. 用short类型二维数组防止MLE。
2. 这里用的记忆化搜索，如果f[x][y]已经有值了，直接返回这个值。
3. 判断error的方法：如果下一次又访问到它，说明出现了循环，这样是永远%不到0的，所以，第一次访问一次f[x][y]就给它赋值-1，如果下一次又访问到f[x][y]=-1，直接return 3，输出error

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int t,x,y,mod;
short f[10010][10010];
int cal(int x,int y)
{
	if(f[x][y]==-1)
	return 3;
	if(f[x][y])
	return f[x][y];
	f[x][y]=-1;
	if(x==0) return f[x][y]=1;
	if(y==0) return f[x][y]=2;
	return f[x][y]=cal((x+y)%mod,((x+y)%mod+y)%mod);
}
int main()
{
	cin>>t>>mod;
	for(int i=1;i<=t;i++)
	{
		cin>>x>>y;
		int ans=cal(x,y);
		if(ans==3)
		cout<<"error"<<endl;
		if(ans==2)
		cout<<"2"<<endl;
		if(ans==1)
		cout<<"1"<<endl;
	}
	return 0;
}

---

## 作者：unputdownable (赞：7)

## 题目链接：[$\color{blue}\text{P5635-天下第一}$](https://www.luogu.org/problem/P5635)

首先，看着这个方程就想到了**斐波那契数列**

~~其实是爆搜，只是~~ 需要判断循环，所以用了斐波那契数列

如果定义 $x_0=x$ , $y_0=y$ ( 初始值 )

那么就有

$x=x_0+y_0 \% Mod $

$y=(x_0+y_0)+y_0=x_0+2y_0 \% Mod $

接着继续操作 , 就是：

$x=(x_0+y_0)+(x_0+2y_0)=2x_0+3y_0 \% Mod $

$y=(2x_0+3y_0)+(x_0+2y_0)=3x_0+5y_0 \% Mod $

$x=(3x_0+5y_0)+(2x_0+3y_0)=5x_0+8y_0 \% Mod $

$y=(5x_0+8y_0)+(3x_0+5y_0)=8x_0+13y_0 \% Mod $

...

也就是说 **如果斐波那契数列$mod\ Mod$循环，那么想 $x$ , $y$ $mod\ Mod$也是循环的** 

然而易证斐波那契数列$mod\ Mod$循环

$\therefore$ $x$ , $y$ $mod\ Mod$是循环的

所以判断 $( x , y )$ 是会循环会原值的

~~然而我还是用了斐波那契数列去判断~~

至于其他，数据都不会爆$int$ , 斐波那契数列$\ mod 10000\ $的循环节也只有$\ 15000$

所以可以放心大胆的去爆搜

---------
---------
## code:
```
#include<bits/stdc++.h>
using namespace std;
int T,x,y,mod,a,b,c,n;//a,b存斐波那契数列的值,c是辅助,其他如题意示
int main(){
	cin>>T>>mod;
	for(int i=1;i<=T;++i){
		cin>>x>>y;
		if((x+y)%mod==0){//初次判断
			cout<<1<<endl;
			continue;
		}
		a=1;
		b=2;
		n=1;
		while(a!=1||b!=1){//判断是否循环
			n++;
			c=b;
			b=(a+b)%mod;
			a=c;//转换斐波那契数列
			if((a*x+b*y)%mod==0){
				cout<<n%2+1<<endl;//
				break;
			}
		}
		if(a==1&&b==1)//特判
			cout<<"error\n";
	}
}
```

---

## 作者：asdfczf (赞：3)

我还是太弱。。。

#### 思路：模拟就完事了

#### 关于 error：一开始想到的就是如果 x 和 y 以相同的值出现过，那么就输出“error”，所以自然而然想到了神奇SLT大法中的 map<pair<int, int> > mapp

### 然而 200ms 请（

#### 85pts

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, p, x, y; 

int main() {
	scanf("%d%d", &t, &p); 
	while(t--) {
		scanf("%d%d", &x, &y); 
		map<pair<int, int>, int> mapp;
		while(1) {
			x = (x + y) % p;
			if (x == 0) {
				printf("%d\n", 1);
				break;
			}
			y = (x + y) % p;
			if (y == 0) {
				printf("%d\n", 2);
				break;
			}
			if (mapp[make_pair(x, y)] == 0) {
				mapp[make_pair(x, y)] = 1;
				continue;
			}
			else {
				printf("error\n");;
				break;
			}
		}
	}
	return 0;
}
```


#### 100pts 众所周知，STL在o2优化的情况下可以[跑得飞快](https://www.luogu.org/record/26803814) 

### 正解
因为没有看月赛的讲评，但是看到出题人和大部分AC记录都是这样的，所以假定它是正解？

设一个计数器cnt，如果它循环了10000次以上，就假装没有结果，输出"error"

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, p, x, y, cnt; 

int main() {
	scanf("%d%d", &t, &p); 
	while(t--) {
		scanf("%d%d", &x, &y); 
		cnt = 0;
		while(1) {
			cnt++;
			x = (x + y) % p;
			if (x == 0) {
				printf("%d\n", 1);
				break;
			}
			y = (x + y) % p;
			if (y == 0) {
				printf("%d\n", 2);
				break;
			}
			if (cnt == 10000) {
				printf("error\n");
				break;
			}
		}
	}
	return 0;
}
```

2333同样这个方法可以用在大法师上（写正解的大佬不要喷我qwq）

```cpp
void dfs() {
	cnt++;
	if (cnt == 100000) {
		cout << ans;
		exit(0);
	}
}
```
# csps rp++


---

## 作者：pomelo_nene (赞：2)

我们很容易猜到我们的答案是会有循环节的（斐波那契），所以说我们要开一个map去储存我们之前经过的游戏状态

同时，如果我们发现了，输出error，否则继续模拟，直到出现0或者发现error为止

但是因为一直模拟会太慢，所以要开个O2才能过

当然你可以用hash_table，但是 map开O2就过了不需要
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#define Game pair<int,int>
#define mp make_pair
using namespace std;
map<Game,bool> appear;
int T,mod;
void Clear(map<Game,bool> &n)
{
	map<Game,bool> tmp;
	n=tmp;
}//不知道这个到底能不能快速clear，可以替换为appear.clear()
void dfs(int x,int y,bool who)
{
	if(appear[mp(x,y)])	return void(puts("error"));//我们发现出现了以前的出现过的游戏状态，输出error。注意void是可以强制类转的
	appear[mp(x,y)]=true;
	if(!who)
	{
		x=(x+y)%mod;
		if(x==0)	return void(puts("1"));
		dfs(x,y,!who);
	}
	else
	{
		y=(x+y)%mod;
		if(y==0)	return void(puts("2"));
		dfs(x,y,!who);
	}//继续模拟，who表示当前谁操作
}
int main(){
	scanf("%d %d",&T,&mod);
	while(T-->0)
	{
		int a,b;
		Clear(appear);
		scanf("%d %d",&a,&b);
		dfs(a,b,false);
	}
	return 0;
}
```

---

## 作者：xiaohuang (赞：2)

[更好的阅读体验](https://xiaohuang888.github.io/2019/12/11/%E3%80%8CLuogu%205635%E3%80%8D%E3%80%90CSGRound1%E3%80%91%E5%A4%A9%E4%B8%8B%E7%AC%AC%E4%B8%80/)

### Solution

这题很容易看出来是记忆化搜索，我们对于每一次询问的每一次答案都记录下来，在下一次的搜索中，如果有这个答案了，就直接输出，否则继续搜索并记录，直到出现过为止。

但是$10000 \times 10000$的$\rm{int}$数组会$\rm{MLE}$，于是我们可以用$\rm{short}$类型来存储记忆化搜索的结果。

**附：$10000 \times 10000$的$\rm{int}$类型的数组内存是$\rm{381.47MB}$，$10000 \times 10000$的$\rm{short}$类型的数组内存是$\rm{190.735MB}$。所以此题用$\rm{int}$类型会爆空间**

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN = 10005;
int T, mod, x, y;
short dp[MAXN][MAXN];
inline short solve(int x, int y, int cnt) {//记忆化搜索
    if (cnt >= 10000) return 0;//cnt表示循环次数，以判断平局的情况
    if (dp[x][y]) return dp[x][y];
    if (x == 0) return 1;
    if (y == 0) return 2;
    return dp[x][y] = solve((x + y) % mod, ((x + y) % mod + y) % mod, cnt + 1);
}
int main() {
    scanf("%d%d", &T, &mod);
    while (T--) {
        scanf("%d%d", &x, &y);
        int ans = solve(x, y, 0);
        if (ans == 1) printf("1\n"); else
        if (ans == 2) printf("2\n"); else printf("error\n");
    }
    return 0;
}
```

---

## 作者：zumgze (赞：1)

### 这道题用暴力模拟的方法是完全可以的

因为我们发现，x和y组成的序列是周期性的，循环了一个周期之后要及时终止，中间遇到0也要及时终止

所以只需要按照规则依次暴力模拟x，y的值即可

x和y组成的序列大概是这样的：x，y，x+y，x+2y......

以样例1为例

1,3,4,7,1,8,9,7,6,3,9,2,1,3......到第二个1,3之前是一个周期，一旦发现出现了1,3就要及时终止
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	long long t,mod;
	cin>>t>>mod;
	while(t--)
	{
		long long x,y;
		cin>>x>>y;
		long long ans=0;
		long long xx=x,yy=y;
		long long k=0;
		while(true)
		{
			if(k&&xx==x&&yy==y)break;//循环了一个周期，这里加上k是为了防止一进入循环就直接跳出去了
			xx+=yy; //保证每次都是累加到xx上
			xx%=mod;
			if(xx==0)//遇到0及时终止
			{
				ans=(k%2+1);//k是奇数代表第一个人，偶数代表第二个人，这种写法可以直接将k的值和需要输出的结果对应了起来
				break;
			}
			swap(xx,yy); //保证每次都是累加到xx上
			k++;//计数，主要是通过奇偶判断是第一个人先到达0还是第二个人先到达0
		}
		if(ans==0)cout<<"error"<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：GGboy0 (赞：1)

有朋友用循环次数大于一定值从而判断error的，我认为不妥；我采用记忆搜索，但存储记忆的数组为爆内存，无奈采用short型，反正只存储0，1，2，3，不影响。
```
#include<bits/stdc++.h>
using namespace std;
short res[10001][10001];	//因为范围是1~10000
int m;
int fun(int x,int y){
	int t_x=x;				//存储现有的x，y
	int t_y=y;
	if(res[x][y]==3){		//3，说明是error
		return 3;
	}
	if(res[x][y]!=0){
		return res[x][y];
	}else if(x==0){
		return 1;
	}else if(y==0){
		return 2;
	}else{
		x=(x+y)%m;
		y=(x+y)%m;
		res[t_x][t_y]=3;//此时赋值3，事后判断为3说明已经开始循环
		res[t_x][t_y]=fun(x,y);
	}
	return res[t_x][t_y];
}
int main(){
	memset(res,0,sizeof(res));	//赋数组初值为全0
	int t;
	cin>>t>>m;
	int x,y;
	for(int i=0;i<t;i++){
		cin>>x>>y;
		short result=fun(x,y);
		if(result==3){
			cout<<"error"<<endl;
		}else{
			cout<<result<<endl;
		}
	}
	return 0;
}
```



---

