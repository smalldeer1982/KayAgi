# Function

## 题目描述

对于一个递归函数 $w(a,b,c)$


- 如果 $a \le 0$ 或 $b \le 0$ 或 $c \le 0$ 就返回值 $1$。
- 如果 $a>20$ 或 $b>20$ 或 $c>20$ 就返回 $w(20,20,20)$
- 如果 $a<b$ 并且 $b<c$ 就返回 $w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c)$。
- 其它的情况就返回 $w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1)$


这是个简单的递归函数，但实现起来可能会有些问题。当 $a,b,c$ 均为 $15$ 时，调用的次数将非常的多。你要想个办法才行。

注意：例如 $w(30,-1,0)$ 又满足条件 $1$ 又满足条件 $2$，请按照最上面的条件来算，答案为 $1$。

## 说明/提示

### 数据规模与约定

保证输入的数在 $[-9223372036854775808,9223372036854775807]$ 之间，并且是整数。

保证不包括 $-1, -1, -1$ 的输入行数 $T$ 满足 $1 \leq T \leq 10 ^ 5$。

## 样例 #1

### 输入

```
1 1 1
2 2 2
-1 -1 -1```

### 输出

```
w(1, 1, 1) = 2
w(2, 2, 2) = 4```

# 题解

## 作者：DPair (赞：120)

我发现别人用的都是记忆化啊，本蒟蒻也发一篇**不一样的记忆化**。

# 记忆化搜索万岁！！！

## 思路
本题其实没有那么难，只要一个记忆化储存就可以避免大量运算量（和递推与动归差不多）。主要思路就是把每一个“w”函数的值储存起来，下一次就可以直接调用，节省大量时间，不然那个w(15, 15, 15)会浪死你。

## 代码
```cpp
#include <cstdio>
#define LL long long

LL dp[25][25][25];

LL w(LL a, LL b, LL c)
{
	if(a <= 0 || b <= 0 || c <= 0) return 1;//两个特判，题意里都有的。
	if(a > 20 || b > 20 || c > 20) return w(20, 20, 20);
	
	if(a <b && b < c)//情况一，每一个没有储存过的“w”值全部储存，如果有就直接调用。
	{
		if(dp[a][b][c-1] == 0)
		{
			dp[a][b][c-1] = w(a, b, c-1);
		}
		if(dp[a][b-1][c-1] == 0)
		{
			dp[a][b-1][c-1] = w(a, b-1 ,c-1);
		}
		if(dp[a][b-1][c] == 0)
		{
			dp[a][b-1][c] = w(a, b-1, c);
		}
		dp[a][b][c] = dp[a][b][c-1] + dp[a][b-1][c-1] - dp[a][b-1][c];
	}
	
	else//同上
	{
		if(dp[a-1][b][c] == 0)
		{
			dp[a-1][b][c] = w(a-1, b, c);
		}
		if(dp[a-1][b-1][c] == 0)
		{
			dp[a-1][b-1][c] = w(a-1, b-1 ,c);
		}
		if(dp[a-1][b][c-1] == 0)
		{
			dp[a-1][b][c-1] = w(a-1, b, c-1);
		}
		if(dp[a-1][b-1][c-1] == 0)
		{
			dp[a-1][b-1][c-1] = w(a-1, b-1, c-1);
		}
		dp[a][b][c] = dp[a-1][b][c] + dp[a-1][b][c-1] + dp[a-1][b-1][c] - dp[a-1][b-1][c-1];
	}
	
	return dp[a][b][c];
}

int main()
{
	LL a, b, c;
	
	while(scanf("%lld%lld%lld", &a, &b, &c))//无限输入，直到“-1 -1 -1”
	{
		if(a == -1 && b == -1 && c == -1) return 0;//-1 -1 -1就直接结束，不运算了。
		
		printf("w(%lld, %lld, %lld) = ", a, b, c);
		printf("%lld\n", w(a, b, c));
	}
}
```

---

## 作者：用户已注销 (赞：72)

# 下面的题解都很赞，我也满说一点

这道题是我第一次正式接触记忆化搜索，之前用的全都是自己想的，多有不当。

其实记忆化搜索是比较简单的一块内容，只要确定好数组和范围就可以把搜索中的每一次结果存起来，

而且 **正在搜索的项目中也可以用到这些信息** 。

这便是记忆化搜索的核心与关键：自定义函数与数组达到“实时互动的状态”。

下附代码（调了一晚上都快吐了）。

···
```cpp
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;
int w[25][25][25];
bool vis[25][25][25];
int mw(long long a,long long b,long long c)
{
    if(a<=0 or b<=0 or c<=0) return 1;
    if(a>20 or b>20 or c>20) return mw(20,20,20);
    if(vis[a][b][c]) return w[a][b][c];
    if(a<b and b<c)
        w[a][b][c]=mw(a,b,c-1)+mw(a,b-1,c-1)-mw(a,b-1,c);
    else
        w[a][b][c]=mw(a-1,b,c)+mw(a-1,b-1,c)+mw(a-1,b,c-1)-mw(a-1,b-1,c-1);
    vis[a][b][c]=true;
    return w[a][b][c];
}
int main()
{
    long long a,b,c;
    memset(vis,false,sizeof(vis));
    scanf("%lld %lld %lld",&a,&b,&c);
    while(a!=-1 or b!=-1 or c!=-1)
    {
        printf("w(%lld, %lld, %lld) = %d\n",a,b,c,mw(a,b,c));
        scanf("%lld %lld %lld",&a,&b,&c);
    }
    return 0;
}
···cpp
```

---

## 作者：Stalker (赞：26)

###这题目刚开始没看到最下方的记忆化搜索还真把我困扰了很久，傻傻地按照题意模拟递归，但是残忍的TLE告诉了我，这题必须用记忆化。也就是说，我们先按照题意把递归的内容写出来，然后把每次20以内的答案记录下来，下一次递归时如果w(x,y,z)有记录就直接输出就行啦，能省去大量的时间。另外有个细节值得注意（我就是因为这个错了好几次QAQ），良心（bian tai）的出题人会在输入中弄几个负数出来，这样的话你一开始的判断语句如果只写if（f[x][y][z]）就炸了（因为不能访问数组负数下标啊呵呵呵），因此加一个特判就行了。

代码奉上：

```cpp
#include<cstdio>
#include<iostream>
#define llx long long
using namespace std;
llx f[40][40][40],a,b,c;
llx fun(llx x,llx y,llx z){
    if(x<=20&&y<=20&&z<=20&&x>=0&&y>=0&&z>=0)if(f[x][y][z]){return f[x][y][z];}
    if((x<=0)||(y<=0)||(z<=0)){return 1;}
    if((x>20)||(y>20)||(z>20)){return fun(20,20,20);}
    if((x<y)&&(y<z)){return f[x][y][z]=fun(x,y,z-1)+fun(x,y-1,z-1)-fun(x,y-1,z);}
    return f[x][y][z]=fun(x-1,y,z)+fun(x-1,y-1,z)+fun(x-1,y,z-1)-fun(x-1,y-1,z-1);
}
void out(){
    printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,fun(a,b,c));
}
int main(){
    while(1){
        scanf("%lld%lld%lld",&a,&b,&c);
        if((a==-1)&&(b==-1)&&(c==-1)){
            break;
        }
        out();
    }
    return 0;
}

```

---

## 作者：Leo_Jiang (赞：24)

# 这题就是个纯递归题

而且是他让你干什么，你就干什么的那种，甚至不用记忆化

~~算了我还是稍微记忆一下吧~~
```
note[30][30][30];
```


我们先整理一下：
### 第一种情况：
```
a<=0 || b<=0 || c<=0
return 1;
```
对吧
### 第二种情况：
```
a>20 || b>20 || c>20
return w(20,20,20);

```
看来这就是上限了
### 第三种情况：
```
a<b<c
return w(a,b,c−1)+w(a,b−1,c−1)−w(a,b−1,c)
```
### 其他情况：
```
return w(a−1,b,c)+w(a−1,b−1,c)+w(a−1,b,c−1)−w(a−1,b−1,c−1)
```

首先，凭着数感，我们觉得int肯定够不上，所以要用long long,再者，记忆化也会让你的程序快很多。

然后就可以开始愉悦的写代码了！！
```
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;  //手懒得打long long

ll a,b,c,note[30][30][30] = {0}; //记忆初始化，记得都要用ll哦

ll w(ll i,ll j,ll k){
	if(i<=0||j<=0||k<=0) return 1;  //第一种情况
	if(i>20||j>20||k>20) return w(20,20,20);//第二种
	if(i<j&&j<k){//第三种
		if(note[i][j][k-1] == 0){//是否有记忆
			note[i][j][k-1] = w(i,j,k-1);
		}
		if(note[i][j-1][k-1] == 0){
			note[i][j-1][k-1] = w(i,j-1,k-1);
		}
		if(note[i][j-1][k] == 0){
			note[i][j-1][k] = w(i,j-1,k);
		}
		note[i][j][k] = note[i][j][k-1] + note[i][j-1][k-1] - note[i][j-1][k]; //返回
	}
	else{//其他情况
		if(note[i-1][j][k] == 0){
			note[i-1][j][k] = w(i-1,j,k);
		}
		if(note[i-1][j-1][k] == 0){
			note[i-1][j-1][k] = w(i-1,j-1,k);
		}
		if(note[i-1][j][k-1] == 0){
			note[i-1][j][k-1] = w(i-1,j,k-1);
		}
		if(note[i-1][j-1][k-1] == 0){
			note[i-1][j-1][k-1] = w(i-1,j-1,k-1);
		}
		note[i][j][k] = note[i-1][j][k] + note[i-1][j-1][k] +  note[i-1][j][k-1] - note[i-1][j-1][k-1]; 
	}
	return note[i][j][k];//结束
}
int main(){
	while(1){
		cin>>a>>b>>c;
		if(a==-1&&b==-1&&c==-1) return 0;
		cout<<"w("<<a<<", "<<b<<", "<<c<<')'<<" = "<<w(a,b,c)<<endl;
	}
}
```
其中要注意的是，判断四种情况是由顺序的，所以写if的时候也要按顺序嵌套哦~~~

886！


---

## 作者：UKE_bound (赞：13)

[ _**题目传送门**_ ](https://www.luogu.com.cn/problem/P1464)

这道题怎么能没有 c++ 的递推呢？今天，我来给大家一份 c++ 写的递推题解。我为啥要用递推写呢？[~~因为递归实在写不下去了~~](https://www.luogu.com.cn/record/list?pid=P1464&status=14&user=zhangjiaan&page=1)。
# 进入正题
## 部分代码&精讲
首先，开头不用说：
```cpp
#include<iostream>
#define int long long
using namespace std;
int p[21][21][21];
```
接下来，我们要来一波初始化：
```cpp
for(int i=0;i<21;i++){
	for(int j=0;j<21;j++){
		p[0][i][j]=1;//只要有一个0就返回1
		p[i][0][j]=1;
		p[i][j][0]=1;
	}
}
```
下一步，把每个值打出来：
```cpp
for(int a=1;a<21;a++){
	for(int b=1;b<21;b++){
		for(int c=1;c<21;c++){
        			//第一二条下一段代码处理
				if(a<b&&b<c){//第三条
					p[a][b][c]=
					p[a][b][c-1]
		   			+p[a][b-1][c-1]
		   			-p[a][b-1][c];
				}else{//第四条
					p[a][b][c]=
					p[a-1][b][c]
		   			+p[a-1][b-1][c]
		   			+p[a-1][b][c-1]
		   			-p[a-1][b-1][c-1];
				}
			}
	}
}
```
最后这部分有一些坑，在注释里（~~码风不好求原谅~~）：
```cpp
int a,b,c;
cin>>a>>b>>c;
for(;(a!=-1||b!=-1||c!=-1);cin>>a>>b>>c){
	int d=a,e=b,f=c;
  	//重要的事情说三遍
	if(d<=0)d=0,e=0,f=0;//有一个是零就全是零!
	if(e<=0)d=0,e=0,f=0;//有一个是零就全是零!
	if(f<=0)d=0,e=0,f=0;//有一个是零就全是零!
	if(d>20||e>20||f>20){//有一个20就全是20
		d=e=f=20;
	}
	printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,p[d][e][f]);//注意格式
} 
```
## 完整代码
当当当当。
```cpp
#include<iostream>
#define int long long
using namespace std;
int p[21][21][21];
signed main(){
	for(int i=0;i<21;i++){
		for(int j=0;j<21;j++){
			p[0][i][j]=1;
			p[i][0][j]=1;
			p[i][j][0]=1;
		}
	}
	for(int a=1;a<21;a++){
		for(int b=1;b<21;b++){
			for(int c=1;c<21;c++){
				if(a<b&&b<c){
					p[a][b][c]=
					p[a][b][c-1]
		   			+p[a][b-1][c-1]
		   			-p[a][b-1][c];
				}else{
					p[a][b][c]=
					p[a-1][b][c]
		   			+p[a-1][b-1][c]
		   			+p[a-1][b][c-1]
		   			-p[a-1][b-1][c-1];
				}
			}
		}
	}
	int a,b,c;
	cin>>a>>b>>c;
	for(;(a!=-1||b!=-1||c!=-1);cin>>a>>b>>c){
		int d=a,e=b,f=c;
		if(d<=0)d=0,e=0,f=0;
		if(e<=0)d=0,e=0,f=0;
		if(f<=0)d=0,e=0,f=0;
		if(d>20||e>20||f>20){
			d=e=f=20;
		}
		printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,p[d][e][f]);
	} 
	return 0;
}
```

---

## 作者：tomapo123 (赞：8)

本题不难
但是因为有可能有负数
所以直接访问三维数组肯定是有问题的
因为下标明显不能是负的
so我把它包装了一下
最后注意数据范围，long long是必须的哟
代码：

```cpp
#include <iostream>
const long long N = 1 << 5;
long long w[N][N][N];
long long W(long long a, long long b, long long c)
{
	if (a <= 0 || b <= 0 || c <= 0)
		return 1;
	if (a > 20 || b > 20 || c > 20)
		return w[20][20][20];
	if (a < b && b < c)
		return w[a][b][c - 1] + w[a][b - 1][c - 1] - w[a][b - 1][c];
	return w[a - 1][b][c] + w[a - 1][b - 1][c] + w[a - 1][b][c - 1] - w[a - 1][b - 1][c - 1];
}
int main()
{
	for (long long i = 0; i <= 20; ++i)
		for (long long j = 0; j <= 20; ++j)
			for (long long k = 0; k <= 20; ++k)
				w[i][j][k] = W(i, j, k);
	long long a, b, c;
	std::cin >> a >> b >> c;
	for (;; std::cin >> a >> b >> c)
		if (a == -1 && b == -1 && c == -1)
			break;
		else
			std::cout << "w(" << a << ", " << b << ", " << c << ") = " << W(a, b, c) << std::endl;
}
```

---

## 作者：「QQ红包」 (赞：7)

模拟+记忆化算法

从题目可以得知，递归的a,b,c范围就在1-20。因此可能会有很多次进行同样的递归。

开一个20\*20\*20的数组，存储每次递归的值。

```cpp

var a:array[-200..20,-200..20,-200..20] of longint;
   aa,bb,cc,i,j:longint;
function w(aaa,b,c:longint):longint;
begin
    if a[aaa,b,c]>0 then exit(a[aaa,b,c]);
    if (aaa<=0)or(b<=0)or(c<=0) then begin a[aaa,b,c]:=1;exit(a[aaa,b,c])end;
   if (aaa<b)and(b<c) then begin a[aaa,b,c]:=w(aaa,b,c-1)+w(aaa,b-1,c-1)-w(aaa,b-1,c);                                     exit(a[aaa,b,c])
                           end;
    a[aaa,b,c]:=w(aaa-1,b,c)+w(aaa-1,b-1,c)+w(aaa-1,b,c-1)-w(aaa-1,b-1,c-1);
    exit(a[aaa,b,c]);
end;
begin
    while 1=1 do
    begin
        readln(aa,bb,cc);
        if (aa=-1)and(bb=-1)and(cc=-1) then begin {write('w(-1, -1, -1) = 1');}halt;end else
        if (aa<=0) or (bb<=0) or (cc<=0) then writeln('w(',aa,', ',bb,', ',cc,') = 1') else 
        if (aa>20) or (bb>20) or (cc>20) then writeln('w(',aa,', ',bb,', ',cc,') = 1048576')else
        writeln('w(',aa,', ',bb,', ',cc,') = ',w(aa,bb,cc));
    end;
end.


```

---

## 作者：x670783915 (赞：6)

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int a[21][21][21] = {1};
int w(int x,int y,int z)//直接判断递归搜索即可
{
    if(x<=0||y<=0||z<=0) return 1;
    else if(x>20||y>20||z>20) return a[20][20][20]?a[20][20][20]:a[20][20][20]=w(20,20,20);
    else if(x<y&&y<z) return (a[x][y][z-1]?a[x][y][z-1]:a[x][y][z-1]=w(x,y,z-1)) + (a[x][y-1][z-1]?a[x][y-1][z-1]:a[x][y-1][z-1]=w(x,y-1,z-1)) - (a[x][y-1][z]?a[x][y-1][z]:a[x][y-1][z]=w(x,y-1,z));
    else return (a[x-1][y][z]?a[x-1][y][z]:a[x-1][y][z]=w(x-1,y,z)) + (a[x-1][y-1][z]?a[x-1][y-1][z]:a[x-1][y-1][z]=w(x-1,y-1,z)) + (a[x-1][y][z-1]?a[x-1][y][z-1]:a[x-1][y][z-1]=w(x-1,y,z-1)) - (a[x-1][y-1][z-1]?a[x-1][y-1][z-1]:a[x-1][y-1][z-1]=w(x-1,y-1,z-1));
    return 1;
}
int main()
{
    int  d,b,c;
    while(scanf("%d%d%d", &d, &b, &c) && (d + 1) || (b + 1) || (c + 1)){
    printf("w(%d, %d, %d) = %d\n", d, b, c, w(d, b, c));
    }
    return 0;
}

```

---

## 作者：linyorson (赞：5)

算法1 模拟

按题目要求写一个递归函数 超时肯定的！

算法2 模拟+记忆化算法

从题目可以得知，递归的a,b,c范围就在1-20。因此可能会有很多次进行同样的递归。

开一个20\*20\*20的数组，存储每次递归的值。

```cpp

int w(int a,int b,int c)
{
    if(a<=0 || b<=0 || c<=0)return 1;
    if(a>20 || b>20 || c>20)
    {   n[a][b][c]=w(20,20,20);//记忆
        return n[a][b][c];
    }
    if(n[a][b][c])return n[a][b][c];
    if(a<b && b<c)
    {   n[a][b][c]=w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);//记忆
        return n[a][b][c];}
    n[a][b][c]=w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);//记忆
    return n[a][b][c];
}

```

---

## 作者：bjrjk (赞：4)

题目中已经说的非常清楚了，让用记忆化搜索：

```cpp
#include<cstdio>//要用printf和scanf linux下引入stdio
#include<memory.h>//memset的库
using namespace std;
long long memory[25][25][25];//记忆化搜索的三维数组
long long w(long long a,long long b,long long c){//防止溢出全部用long long
    if(a<25&&b<25&&c<25&&a>0&&b>0&&c>0){
        if(memory[a][b][c]!=-1)return memory[a][b][c]; //读取数组中是否存在已经记录好的数值，直接返回
    }
    int result;
    if(a<=0||b<=0||c<=0)result=1;
    else if(a>20||b>20||c>20)result=w(20,20,20);
    else if(a<b&&b<c)result=w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
    else result=w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
    if(a<25&&b<25&&c<25&&a>0&&b>0&&c>0){
        memory[a][b][c]=result;//如果不存在，计算完毕后存储起来
    }
    return result;
}
int main(){
    memset(memory,-1,sizeof(long long)*25*25*25);//初始化记忆数组
    while(1){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        if(a==-1&&b==-1&&c==-1)break;
        printf("w(%d, %d, %d) = %lld\n",a,b,c,w(a,b,c));
    }
}
```

---

## 作者：Kidd (赞：4)

这题令我想吐血，答案错误好多次，还被格式绊倒脚……


深搜？没说的，超时。


深搜+记忆化+模拟？这还差不多……




































```cpp
var
  n,m,s:int64;
  a:array[0..20,0..20,0..20] of longint;
function try(x,y,z:longint):longint;
begin
   if (x<=20) and (y<=20) and (z<=20) and (x>0) and (y>0) and (z>0)
    then if a[x,y,z]<>0
          then exit(a[x,y,z])
     else if (x>20) or (y>20) or (z>20)
           then if a[20,20,20]<>0
                 then exit(a[20,20,20]);//这是记忆化，如果这三个数的深搜出现过，那么可以少很多岔路
   if (x<=0) or (y<=0) or (z<=0)
    then exit(1)
     else if (x>20) or (y>20) or (z>20)
           then begin a[20,20,20]:=try(20,20,20);exit(a[20,20,20]);end
            else if (x<y) and (y<z)
                  then begin a[x,y,z]:=try(x,y,z-1)+try(x,y-1,z-1)-try(x,y-1,z);exit(a[x,y,z]);end
                   else begin a[x,y,z]:=try(x-1,y,z)+try(x-1,y-1,z)+try(x-1,y,z-1)-try(x-1,y-1,z-1);exit(a[x,y,z]);end;//模拟+存储
end;
begin
   a[0,0,0]:=1;
   while true do
   begin
      readln(n,m,s);
      if (n=-1) and (m=-1) and (s=-1)
       then break;//读入，没说的
      if (n>20) or (m>20) or (s>20) then
      begin
         if (n>0) and (m>0) and (s>0)
          then writeln('w(',n,', ',m,', ',s,') = ',try(20,20,20))
           else writeln('w(',n,', ',m,', ',s,') = ',1)
      end
      else writeln('w(',n,', ',m,', ',s,') = ',try(n,m,s));//要做的判断，否则进行数组查找时会爆掉
   end;
end.
```

---

## 作者：高泽棵 (赞：3)

这道题可以用回溯，也可以用递推。

我喜欢后一种，代码如下：

```cpp
var a,b,c,i,j,k:longint;
f:array[0..20,0..20,0..20] of longint;
begin
  readln(a,b,c);
  while (a<>-1) or (b<>-1) or (c<>-1) do
  begin
    fillchar(f,sizeof(f),0);
    write('w(',a,', ',b,', ',c,') = ');
    if ((a>20) or (b>20) or (c>20)) and not ((a<=0) or (b<=0) or (c<=0)) then
    begin a:=20;b:=20;c:=20;end;{a>20 or b>20 or c>20的情况，但小心a,b,c要大于0}
    if (a<=0) or (b<=0) or (c<=0) then {a<0 or b<0 or c<0就输出1，否则搜到w(a,b,c)}
      writeln(1)
    else
    begin
      for i:=0 to a do
        for j:=0 to b do
          for k:=0 to c do
            if (i=0) or (j=0) or (k=0) then {i<=0 or j<=0 or k<=0就是1}
              f[i,j,k]:=1
            else
              if (i<j) and (j<k) then {a<b and b<c情况}
                f[i,j,k]:=f[i,j,k-1]+f[i,j-1,k-1]-f[i,j-1,k]
              else
                f[i,j,k]:=f[i-1,j,k]+f[i-1,j-1,k]+f[i-1,j,k-1]-f[i-1,j-1,k-1]; {其他情况}
      writeln(f[a,b,c]);
    end;
    readln(a,b,c);
  end;
end.
```

---

## 作者：ghj1222 (赞：3)

题目中说的什么意思根本不用理解，反正我也不清楚，按照题目要求编就得了~

加上个记忆化搜索就行了，否则。。。你懂得，TLE

dp数组是备忘录，w函数除了记忆化，完全按照题目的要求

因为a,b,c有一个小鱼等于0的或者a,b,c有一个大于20的就返回特定值，所以dp数组开到20就行了

那么说好的代码呢？下面

http://paste.ubuntu.com/23126570/


---

## 作者：ylsoi (赞：2)

这一题用记忆化搜索，用一个三维数组来存储每一种类型的数据；

但是有几点是需要注意的，那么就是在处理分支的顺序上，一定要按照原来的题目所给顺序；

还有就是在处理记忆数组的大小以及原来输入的三个参数的处理上。

具体的附上代码如下#include<iostream>

```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int mem[25][25][25];
void w(long long a,long long b,long long c)
{
    if(mem[a][b][c]!=0)return;
    if(a<=0||b<=0||c<=0)
    {
        mem[a][b][c]=1;
        return;
    }
    else if(a<b&&b<c)
    {
        w(a,b,c-1);
        w(a,b-1,c-1);
        w(a,b-1,c);
        mem[a][b][c]=mem[a][b][c-1]+mem[a][b-1][c-1]-mem[a][b-1][c];
    }
    else
    {
        w(a-1,b,c);
        w(a-1,b-1,c);
        w(a-1,b,c-1);
        w(a-1,b-1,c-1);
        mem[a][b][c]=mem[a-1][b][c]+mem[a-1][b-1][c]+mem[a-1][b][c-1]-mem[a-1][b-1][c-1];
    }
}
int main()
{
    long long a,b,c;//一定记得要用大整数型；因为题目的范围；
    while(1)
    {
        memset(mem,0,sizeof(mem));
        scanf("%lld%lld%lld",&a,&b,&c);
        if(a==-1&&b==-1&&c==-1)return 0;//遇到了题目所给的终止条件便终止了；
        if(a<=0||b<=0||c<=0)//一定要记得按照顺序；
        printf("w(%lld, %lld, %lld) = %d\n",a,b,c,1);
        else if(a>20||b>20||c>20)//如果输入的变量大于20的话，可以直接按照20的去做，但是要注意下面的结果调用的记忆化数组，只可以调用mem[20][20][20],否则便会越界；
        {
            w(20,20,20);
            printf("w(%lld, %lld, %lld) = %d\n",a,b,c,mem[20][20][20]);
        }
        else 
        {
            w(a,b,c);
            printf("w(%lld, %lld, %lld) = %d\n",a,b,c,mem[a][b][c]);
        }
    }
    return 0;
}
```

---

## 作者：BCZSX (赞：2)

~~这题虽然很水，但是我也做了很久……~~

这题就是一道递归的题目，按照题目的要求来写个递归就可以了，然后每次都要标记一下，否则会超时。
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
#define ll long long
int f[25][25][25];
int n;
ll a,b,c;
ll w(ll x,ll y,ll z)//按题意所说的递归
{
	if(x<=0||y<=0||z<=0) return 1;
	if(x>20||y>20||z>20) return f[20][20][20]=w(20,20,20);
	if(f[x][y][z]) return f[x][y][z];
	if(x<y&&y<z) return f[x][y][z]=w(x,y,z-1)+w(x,y-1,z-1)-w(x,y-1,z);
	else return f[x][y][z]=w(x-1,y,z)+w(x-1,y-1,z)+w(x-1,y,z-1)-w(x-1,y-1,z-1);
}
int main()
{
	while(scanf("%lld%lld%lld",&a,&b,&c)!=EOF)
	{
		if(a==-1&&b==-1&&c==-1) return 0;//如果a,b,c都为-1，return 0 。
		if(a<=0||b<=0||c<=0) printf("w(%lld, %lld, %lld) = 1\n",a,b,c);//判断是否小于等于0
		else if(a>20||b>20||c>20) printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,w(20,20,20));//判断是否大于20
		else printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,w(a,b,c));//其他情况输出w(a,b,c)
	}
}
```

---

## 作者：曦行夜落 (赞：2)

记忆化搜索大法好

如果单纯递归会发现时间炸，而且栈空间堪忧（题目也提示了）

这时候我们发现实际上有很多冗余计算，比如w（0,0,1）可能要算很多次。那这时候怎么办呢？其实很简单，只要加一个记忆数组f[i,j,k]，保存w(i,j,k)的值，因这个值不管怎样是不会变的，所以当我们要第二次计算这个值的时候，直接用就行啦

下面附上代码（注意！必须int64）




```cpp
var
  f:array[-1..20,-1..20,-1..20] of int64;
  a,b,c:int64;
function w(a,b,c:int64):int64;
begin
  if (a<=0) or (b<=0) or (c<=0) then exit(1);
  if (a>20) or (b>20) or (c>20) then
    begin
      a:=20; b:=20; c:=20;
    end;
  if f[a,b,c]<>-1 then exit(f[a,b,c]);
  if (a<b) and (b<c) then
    begin
      f[a,b,c]:=w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
      exit(f[a,b,c]);
    end;
  f[a,b,c]:=w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
  exit(f[a,b,c]);
end;
begin
  readln(a,b,c);
  while (a<>-1) and (b<>-1) and (c<>-1) do
    begin
      fillchar(f,sizeof(f),-1);
      writeln('w(',a,', ',b,', ',c,') = ',w(a,b,c));
      readln(a,b,c);
    end;
end.
//震惊！某OIer因多次拍断大腿购买假肢而破产！
```

---

## 作者：cn_lemon (赞：1)

    
    
        
        
    
    
```cpp
//c++题解，记忆化搜索（重要的事说三遍） 
#include<iostream>
#include<cstdio>
long long n1[500][4],n2[500][4];
int t[25][25][25];//记忆化搜索数组 
int w(int a,int b,int c)
{
    if(a<=0||b<=0||c<=0)return 1;//把题目中的递归语句 依次 依次 依次 打下来 
    else if(t[a][b][c]!=-10000)return t[a][b][c];// （先看下一条） 如果a,b,c对应t数组有值，直接返还这个值，避免多次递归 
    else if(a>20||b>20||c>20)t[a][b][c]=w(20,20,20);// 因为要递归很多次，所以用t数组来存储不同的a,b,c的情况，避免重复搜索 
    else if(a<b&&b<c) t[a][b][c]=w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
    else t[a][b][c]=w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
    return t[a][b][c];//最后返还w的值 
}
using namespace std;
int main()
{
    int i,j,k;
    for(i=1;i<=24;i++)
    for(j=1;j<=24;j++)
    for(k=1;k<=24;k++)
    t[i][j][k]=-10000;//这里我多余了，直接赋成0就可以了 
    for(i=1;;i++)
    {
        scanf("%lld%lld%lld",&n1[i][1],&n1[i][2],&n1[i][3]);
        n2[i][1]=n1[i][1]; 
        n2[i][2]=n1[i][2];
        n2[i][3]=n1[i][3];
        if(n1[i][1]>20)n1[i][1]=21;//如果数值大于20，那么直接变成21，效果是一样的，最后都会变成w(20,20,20) 
        if(n1[i][2]>20)n1[i][2]=21;//这样可以避免搜索里面的形参设为long long，那样会爆掉的 
        if(n1[i][3]>20)n1[i][3]=21;
        if(n1[i][1]==-1&&n1[i][2]==-1&&n1[i][3]==-1)
        { 
            i--;
            break;//停止输入 
        }
    }
    for(j=1;j<=i;j++)//直接输出了 
    printf("w(%lld, %lld, %lld) = %d\n",n2[j][1],n2[j][2],n2[j][3],w(n1[j][1],n1[j][2],n1[j][3]));
    return 0;
     }

```

---

