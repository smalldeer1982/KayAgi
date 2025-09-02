# I Wanna Be the Guy

## 题目描述

There is a game called "I Wanna Be the Guy", consisting of $ n $ levels. Little X and his friend Little Y are addicted to the game. Each of them wants to pass the whole game.

Little X can pass only $ p $ levels of the game. And Little Y can pass only $ q $ levels of the game. You are given the indices of levels Little X can pass and the indices of levels Little Y can pass. Will Little X and Little Y pass the whole game, if they cooperate each other?

## 说明/提示

In the first sample, Little X can pass levels \[1 2 3\], and Little Y can pass level \[2 4\], so they can pass all the levels both.

In the second sample, no one can pass level 4.

## 样例 #1

### 输入

```
4
3 1 2 3
2 2 4
```

### 输出

```
I become the guy.
```

## 样例 #2

### 输入

```
4
3 1 2 3
2 2 3
```

### 输出

```
Oh, my keyboard!
```

# 题解

## 作者：清小秋ovo (赞：9)

# CF469A题解
本人第一篇提交的题解，~~超级激动~~。

萌新一个，代码写的非常水。
## 题目理解
有一个若干关的游戏，两个人分别可以通过所有关卡中的一部分关，给出两个人各自都能通过的关卡数以及所有关卡编号 ，当两人合作时是否能够通过所有关？
## 输入输出解析
输入

```latex
4

3 1 2 3

2 2 4
```


可以看到，第一个人可以通过 $1$ 至 $3$ 关，而第二个人能通过第二和第四关，说明两人合作时，所有关卡都可以全部通过过，故输出：

“I become the guy.”


如果两人合作并不能通过所有的关卡，输出：

“Oh, my keyboard!”


## 解题思路
本题数据范围并不大，只有 $n \le100$，所以一个暴力模拟就可以轻松水过去
~~（然而现实中我做了快10遍才过的~~。

先开一个大数组 ，存储每个关的通过信息（初始为 $0$，表示不通过）。

再依次输入通关信息，并在数组中找到对应的下标并修改为 $1$（表示通关）。

最后，从下标为 $1$ 开始到 $n$ 依次循环，检查是否都为通过（也就是检查是否该元素为 $1$）。

然后一个简单的判断输出就好啦！

## 附上本人超级水的代码 & AC记录
```cpp
#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<cstdio>
#include<algorithm>

using namespace std;

int main()
{
    //定义n，并输入n
    int n;
    cin>>n;
    //开一个大数组
    int ans[200];
    //初始化均为0
    for(int i=0;i<200;i++) ans[i]=0;
    //x存储的是小x通过的关卡数，y存储的是小y的通过关卡数
    int x;
    int y;
    int tmp;
    cin>>x;
    //依次存储x的通关信息
    for(int i=0;i<x;i++){
        cin>>tmp;
        ans[tmp]=1;
    }
    cin>>y;
    //依次存储y的通关信息
    for(int i=0;i<y;i++){
        cin>>tmp;
        ans[tmp]=1;
    }
    //循环检查
    int check=0;
    for(int i=1;i<n+1;i++){
        if(ans[i]==0){
            check=0;
            cout<<"Oh, my keyboard!"<<endl;
            break;
        }else if(ans[i]==1){
            check =1;
        }
    }
    if(check){
        cout<<"I become the guy."<<endl;
    }

}
```
[本人的AC记录](https://www.luogu.com.cn/record/54759603)。

代码有很多有待优化的地方。

谢谢各位！

—— 清小秋 $2021.8.2$。

---

## 作者：Ryan_Yu (赞：5)

此题可以利用桶排的思想解决。

先定义一个 `bool` 型数组 $flag$ ，将其置为 $false$。

读入数据后，分两个循环进行操作。

如果某一关的号码为出现了，就把 $flag_b$ 置为 $true$ 。

操作结束后，出现一关不能通过就输出 $\texttt{“Oh, my keyboard!”}$ ，否则输出 $\texttt{“I become the guy.”}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,b,c,i;bool flag[105]={false};
int main()
{
	cin>>n>>x;
	for(i=1; i<=x; i++)
		{
			cin>>b;
			flag[b]=true;
		}
	cin>>y;
	for(i=1; i<=y; i++)
		{
			cin>>c;
			flag[c]=true;
		}
	for(i=1; i<=n; i++)
		{
			if(!flag[i])
				{
					cout<<"Oh, my keyboard!";
					return 0;

				}
		}
	cout<<"I become the guy.";
	return 0;
}
```


---

## 作者：GaryH (赞：2)

# 蒟蒻又来发题解啦！
（据说CSP—J前天发题解可使rp+=nan*inf）
### 当然，其实此题~~比我还水~~

我知道此题的正解是开个桶进行统计，但由于我~~瓜~~闲，所以我用了深搜.

那直接上代码（解释在代码里）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,q,x,c;
bool cnt[101];
inline void dfs(int x){//深搜函数 
	if(cnt[x]){
		c++;//统计可过关卡数 
	}
	if(x==n)return;//退出 
	else dfs(x+1);//搜下一层 
}
int main(){
	cin>>n>>p;//输入 1 
	for(int i=1;i<=p;i++)cin>>x,cnt[x]=1;//统计此关是否能过 1
	cin>>q;//输入 2
	for(int i=1;i<=q;i++)cin>>x,cnt[x]=1;//统计此关是否能过 2
	dfs(1);//开始从一搜 
	if(c==n/*判断*/){
		cout<<"I become the guy.";//可以 
	}else{
		cout<<"Oh, my keyboard!";//不可以 
	}
	return 0;
}
```
其实还有一种用rand()的做法，但由于太玄学，所以就不放代码了~~什么~~：)

# 再见！

---

## 作者：jiangXxin (赞：2)

可以使用桶排思想，把所有能通关的关卡标记一下，然后看哪一关不能被标记，如果全部被标记，就能通过.

**code:**

```cpp
/**
*    author:  a2954898606
*    created: 2019/10/25 11:57:42
**/
#include<bits/stdc++.h>
#define REP(A,B,I) for(int I=(A);I<=(B);I++)
#define PER(A,B,I) for(int I=(A);I>=(B);I--)
#define read(FILENAME) freopen((FILENAME + ".txt"), "r", stdin);
#define write(FILENAME) freopen((FILENAME + ".txt"), "w", stdout);
#define LL long long
#define N 1000010
#define M 100
using namespace std;
const long long mod=1e9+7;
long long quickmul(long long a,long long b){
    a%=mod;b%=mod;
    long long c=(long long)a*b/mod;
    long long ret=a*b-c*mod;
    if(ret<0)ret+=mod;
    else if(ret>=mod)ret-=mod;
    return ret;
}
long long quickpow(long long a,long long b){
    long long ret=1;
    while(b){
        if(b&1)ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(b==0){
        x=1;y=0;return a;
    }
    long long d=exgcd(b,a%b,x,y);
    long long z=x;x=y;y=z-y*(a/b);
    return d;
}
int n,p,q;
int x,vis[N];
int main(){
    //read(1)
    //write(1)
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>p;
    REP(1,p,i)cin>>x,vis[x]=1;
    cin>>q;
    REP(1,q,i)cin>>x,vis[x]=1;
    REP(1,n,i){
        if(!vis[i]){
            cout<<"Oh, my keyboard!"<<endl;
            return 0;
        }
    }
    cout<<"I become the guy."<<endl;
    return 0;
}

```

再想一下，如果它给的关卡N太大，数组标记不下怎么办.考虑使用c++的unique去重函数，去重后的m如果等于n，那就可以通过，否则就不可以通过.(**注意，unique去重前需要排序,不然去重会失败**)

**Code**

```cpp
/**
*    author:  a2954898606
*    created: 2019/10/25 12:02:42
**/
#include<bits/stdc++.h>
#define REP(A,B,I) for(int I=(A);I<=(B);I++)
#define PER(A,B,I) for(int I=(A);I>=(B);I--)
#define read(FILENAME) freopen((FILENAME + ".txt"), "r", stdin);
#define write(FILENAME) freopen((FILENAME + ".txt"), "w", stdout);
#define LL long long
#define N 1000010
#define M 100
using namespace std;
const long long mod=1e9+7;
long long quickmul(long long a,long long b){
    a%=mod;b%=mod;
    long long c=(long long)a*b/mod;
    long long ret=a*b-c*mod;
    if(ret<0)ret+=mod;
    else if(ret>=mod)ret-=mod;
    return ret;
}
long long quickpow(long long a,long long b){
    long long ret=1;
    while(b){
        if(b&1)ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(b==0){
        x=1;y=0;return a;
    }
    long long d=exgcd(b,a%b,x,y);
    long long z=x;x=y;y=z-y*(a/b);
    return d;
}
int n,p,q,x,m;
vector<int> vt;
int main(){
    //read(1)
    //write(1)
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin>>n>>p;
    REP(1,p,i){
        cin>>x;
        vt.push_back(x);
    }
    cin>>q;
    REP(1,q,i){
        cin>>x;
        vt.push_back(x);
    }
    sort(vt.begin(),vt.end());
    m=unique(vt.begin(),vt.end())-(vt.begin());
    if(m==n)cout<<"I become the guy."<<endl;
    else cout<<"Oh, my keyboard!"<<endl;
    return 0;
}

```


---

## 作者：REAL_曼巴 (赞：1)

此题的题意十分简单，我就不再阐述了，下面来讲一下知识。

知识：桶。要知道，我们的桶是用来装东西的，但装的东西比较特殊，是某样东西出现了几次。我们可以把这个东西的名子（也就是数字下标）作为桶的编号，如果这个东西出现一次，就把这个桶加一。但这样的缺点是浪费空间。（良心自制图片）

![](https://cdn.luogu.com.cn/upload/image_hosting/f4wovr02.png)

思路：用桶来统计每个数出现的次数，如果桶的那一项是零，说明不能完成游戏，反之亦然。

```
#include<iostream>
using namespace std;
int tong[100001];
int main(){
    int n,b;
    cin>>n;
    while(cin>>b)tong[b]++;
    for(int i=1;i<=n;++i)
        if(tong[i]==0){
            cout<<"Oh, my keyboard!";
            return 0;
        }
    cout<<"I become the guy.";
    return 0;
}


```




---

## 作者：小坦克 (赞：1)

#### [CF469A I Wanna Be the Guy](https://www.luogu.com.cn/problem/CF469A) 

------------
解题前肯定要 $Relax$ 一波~~

![](http://img3.downza.cn/download/201907/143841-5d3013f1bd6bd.jpg)

吐槽一句：$I$ $Wanna$ $Be$ $The$ $Guy$ 让我心态都崩了！！！


------------
## 言归正传：
- 思路：

1. 首先用两个 `for` 循环输入小$X$ 和小$Y$ 能够通过的关卡，并且用一个数组储存起来。

2. 接着再来一个循环，如果有一个关卡两人都不能通过，则输出`Oh, my keyboard!`。

3. 否则输出`I become the guy.`。


------------
- 代码（有详解）：
```cpp
#include<bits/stdc++.h> //万能头 
using namespace std;
int main()
{
	int n[105]; //用来储存能通过的关卡 
	memset(n,0,sizeof(n)); //memset定初值，0为不能通过，1为能通过 
	int a; //a表示一共有多少关卡 
	cin>>a; //输入 
	int b; //表示小X能通过多少关卡 
	cin>>b; //输入 
	for(int i=1;i<=b;i++){
		int c;
		cin>>c;
		n[c]=1; //标记能通过 
	}
	int d; //表示小Y能通过多少关卡
	cin>>d;
	for(int i=1;i<=d;i++){
		int e;
		cin>>e;
		n[e]=1; //标记 
	}
	for(int i=1;i<=a;i++)
		if(n[i]==0){ //如果有关卡不能通过则输出Oh, my keyboard!
			cout<<"Oh, my keyboard!";
			return 0;
	}
	cout<<"I become the guy."; //否则输出I become the guy.
	return 0;
}
```


------------
完结撒花！

---

## 作者：HNYLMS_MuQiuFeng (赞：1)

这道题，可以说是非常的简单~~（原谅我一开始没看懂题）~~

大体思路就是：输入——标记——枚举——如果有未标记的就输出“Oh,my keyboard!”然后结束程序——如果全标记了就输出“I bacome the guy.”

AC代码如下：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a,b,c,d;
int main()
{
	cin>>a;int n[a+1]={0};
	cin>>b;
	for(int i=1;i<=b;i++)
	{
		cin>>d;//一个一个输入一个一个标记，这样就免去了先存再标记的繁琐程序
        //而且避免TLE或者MLE
		n[d]=1;
	}
	cin>>c;
	for(int i=1;i<=c;i++)
	{
		cin>>d;//同样也是边读边记
		n[d]=1;
	}
	for(int i=1;i<=a;i++)
	{
		if(n[i]==0)//判断，这里可以简写成if(!n[i])
		{
			cout<<"Oh, my keyboard!";
			return 0;
		}
	}
	cout<<"I become the guy.";
	return 0;//愉快输出！AC啦！锵锵！
}
```
# 杜绝抄袭从我做起！！！！

---

## 作者：清清老大 (赞：0)

## 思路

用桶排的思路，把每一个能通关的关卡都标记一遍，最后如果还有没被标记的关卡，就不能通过。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,a,x;
    bool flag[1234] = {0};//flag数组用来做标记
    cin >> n >> a;
    for(int i = 0;i < a;i ++)
    {
        cin >> x;
        flag[x] = 1;
    }
    cin >> a;//重复利用a
    for(int i = 0;i < a;i ++)
    {
        cin >> x;
        flag[x] = 1;
    }
    for(int i = 1;i <= n;i ++)
    {
        if(!flag[i])//如果没被标记
        {
            cout << "Oh, my keyboard!";
            return 0;
        }
    }
    cout << "I become the guy.";
    return 0;
}
```


---

## 作者：Cult_style (赞：0)

题目 不难，可以用数组计数标记两人通过的关卡，如果有任何一关两人中的任意一个都无法通过此关，那么直接输出$I$ $become$ $the$ $guy.$,然后结束，如果到最后还没有结束，那就输出$I$ $become$ $the$ $guy.$

```
#include<bits/stdc++.h>
#define up(i,a,b) for(int i=a;i<=b;++i)
#define end exit(0)
using namespace std;
int n;
int vis[105];
int main(){
	int t;
	scanf("%d%d",&n,&t);
	while(t--){
		int x;
		scanf("%d",&x);
		vis[x]++;
	}
	scanf("%d",&t);
	while(t--){
		int x;
		scanf("%d",&x);
		vis[x]++;
	}
	up(i,1,n){
		if(!vis[i]){
			puts("Oh, my keyboard!");
			end;
		}
	}
	puts("I become the guy.");
	
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
小 A 和小 B 正在玩一个游戏，游戏一共有 $n$ 关，而两个人各只能通过 $p_A,p_B$ 个关卡。问他们能否通过合作通关这个游戏。

**数据范围：$1\leqslant n\leqslant 100,0\leqslant p_A,p_B\leqslant n$。**
## Solution
这题目和 [CF615A](https://www.luogu.com.cn/problem/CF615A) 几乎一模一样，而且还弱化了，只有两组，那题最多有 $100$ 组……

呃，扯远了，拉回正题。这里我们发现，只要两个人能通过的关卡包括所有的关卡那就可以通关，否则不能通关。因此，我们需要开个 $vis$ 数组，来存储每个人能玩过的关卡，最后看是否把所有的关卡都通过。
## Code
```cpp
#include <cstdio>
using namespace std;

int n, m, k, x, vis[107];

int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &k);
		for(int j = 1; j <= k; ++j)	{
			scanf("%d", &x);
			vis[x] = 1;
		}
	}
	for(int i = 1; i <= n; ++i)	if(!vis[i])	return printf("NO"), 0;
	return printf("YES"), 0;
}
```

---

## 作者：chenpengda (赞：0)

注意到$1<=n<=100$，可以使用数组进行统计。

提示1：数组开得大一些，以免发生意外的RE

提示2：可以使用define定义数组空间最大值，在循环的时候可以使用。另外，以后要修改的时候也只用修改Define了

定义部分的代码：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
#define maxn 105//这个的意思是maxn是一个常量，值是105，也可以int const maxn=105
int main()
{
	int n,p,q;//见题目描述
	bool pass[maxn];//这个关卡是否可过
	for(int i=0;i<maxn;i++)pass[i]=0;//你也可以使用：memset(pass,0,sizeof(pass);
```
之后我们输入了$p$，通过while或for语句，循环输入数，把这些都标记成“可以通过”（即1）

同样输入$q$，通过while或for语句，循环输入$q$个数，把这些都标记成“可以通过”（即1），注意如果$p$和$q$中都可以通过的，还是被覆盖成了1。

统计和输入部分的代码

```cpp
	cin>>n;
	cin>>p;
	while(p--)//你也可以用：for(int i=0;i<p;i++)或for(int i=1;i<=p;i++)
	{
		int m;//这个数只是供给输入
		cin>>m;
		pass[m]=1;//你也可以用：pass[m]=true;
	}
	cin>>q;//也可以再输入一次p
	while(q--)
	{
		int m;//这个数只是供给输入
		cin>>m;
		pass[m]=1;
	}
```


那么统计就统计完啦，最后就是输出了。

通过一个遍历，如果这一段里面有$0$，那么就输出`Oh, my keyboard!`否则就输出`I become the guy.`

输出部分的代码。

```cpp
	for(int i=1;i<=n;i++)
	{
		if(pass[i]==0)//你也可以用：if(pass[i]==false)
		{
			cout<<"Oh, my keyboard!";
			return 0;
		}
	}
	cout<<"I become the guy.";
	return 0;
} 
```

那么，这道题目便完成了。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 105
int main()
{
	int n,p,q;
	bool pass[maxn];
	for(int i=0;i<maxn;i++)pass[i]=0;
	cin>>n;
	cin>>p;
	while(p--)
	{
		int m;
		cin>>m;
		pass[m]=1;
	}
	cin>>q;
	while(q--)
	{
		int m;
		cin>>m;
		pass[m]=1;
	}
	for(int i=1;i<=n;i++)
	{
		if(pass[i]==0)
		{
			cout<<"Oh, my keyboard!";
			return 0;
		}
	}
	cout<<"I become the guy.";
	return 0;
} 
```

**综合来看，这道题目综合了循环和数组计数（桶计数）思想，是一道较简单的练手题。**

---

## 作者：Franka (赞：0)

### **题目**
小$X$和小$Y$在玩一个有$n$关的游戏，其中小$X$只能通过$p$关，小$Y$只能通过$q$关，现在他们一起玩这个游戏，请问是否能过关，如果行，输出`I become the guy.`，否则输出`Oh, my keyboard!`。
### **思路**
因为这道题目的$a_i$并不大，因此可以用**桶**。

将他们能过的关储存在一个桶里，然后从$1$到$n$依次扫过去，如果$a_i=0$，就直接输出`Oh, my keyboard!`。

当$1$到$n$都有的时候，就输出`I become the guy.`。
### **代码**
```cpp
var n,p,q,i,x:longint;a:array[1..100] of 0..1;
begin
 read(n);//读入n
 read(p);//读入p（注意这里读入p是不换行的）
 for i:=1 to p do//p个数
  begin
   read(x);//读入x
   a[x]:=1;//统计
  end;
 read(q);
 for i:=1 to q do
  begin
   read(x);
   a[x]:=1;
  end;//同理
 for i:=1 to n do//1到n
  if a[i]=0 then//如果有0
   begin
    write('Oh, my keyboard!');//输出
    halt;//结束整个程序
   end;
 write('I become the guy.');//输出
end.
```


---

## 作者：Snow_Dreams (赞：0)

这道题我觉得是恶意评分诶


~~尽管现在只是道橙题~~

差不多红题吧

这道题就首先开一个a数组，接着读入数据，将读入的关卡数标记为true，最后再扫一遍，如果每一个关卡都被标记过了，就输出I become the guy.，如果有未标记的关卡，就输出Oh, my keyboard!并且直接return 0

献上代码

~~其实没有必要了~~：

```cpp
#include<cstdio>
int a[105], n;
int main()
{
	scanf("%d",&n);
	int x;scanf("%d",&x);
   for(int i = 1;i <= x;i++){
   	  int y;scanf("%d",&y);
     	a[y]=1;
   }
  	scanf("%d",&x);
   for(int i = 1;i <= x;i++){
  int y;scanf("%d",&y);
  a[y]=1;
  }
  for(int i = 1;i <= n;i++){
    if(!a[i]){
      printf("Oh, my keyboard!");
      return 0;
   		}
   }
 	printf("I become the guy.");
  	return 0;
                           }
```


---

## 作者：LYR_ (赞：0)

可前往本人博客查看，链接：[我的博客](https://www.cnblogs.com/Ryan-juruo/p/11627447.html)

这道题非常简单，有两种做法：
1. 用一个数组标记是不是每个关卡小X或小Y都可以通过
1. 用set储存小X和小Y能够通过的关卡（set有去重功能），最后判断set的长度是否等于n

因为楼上已经有第一种做法的题解了，所以，我用第二种方法。

set具体用法可以上百度

------------
代码如下（C++）：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	set<int> s;
	cin>>n;
	int p,q;
	cin>>p;
	for(int i=1;i<=p;i++) {
		int x;
		cin>>x;
		s.insert(x);//将输入的关卡存入set
	}
	cin>>q;
	for(int i=1;i<=q;i++) {
		int x;
		cin>>x;
		s.insert(x);
	}
	if(s.size()==n) cout<<"I become the guy."<<endl;//能够完成游戏
	else cout<<"Oh, my keyboard!"<<endl;//不能
	return 0;
}

```


---

