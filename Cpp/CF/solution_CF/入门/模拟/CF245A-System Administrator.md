# System Administrator

## 题目描述

Polycarpus是系统管理员。在他的严格指导下有两台服务器——a和b。为了了解服务器的性能，Polycarpus执行命令“ping a”和“ping b”。每个ping命令都会向命令参数中指定的服务器发送10个数据包。执行程序会产生两个整数x$ 和 y（x+y=10；x，y>=0）。这些数字意味着 x 包通过网络成功地到达了相应的服务器，y 包丢失了，今天 Polycarpus 在工作日执行了n个ping命令。现在，对于每个服务器，Polycarpus都想知道服务器是否“活动”。Polycarpus认为服务器是“活动的”，如果我们发送到该服务器的数据包中至少有一半是通过网络成功到达的。帮助Polycarpus，根据给定的命令及其结果来确定每个服务器是否“活动”。

## 样例 #1

### 输入

```
2
1 5 5
2 6 4
```

### 输出

```
LIVE
LIVE
```

## 样例 #2

### 输入

```
3
1 0 10
2 0 10
1 10 0
```

### 输出

```
LIVE
DEAD
```

# 题解

## 作者：liangbowen (赞：1)


[题目传送门](https://www.luogu.com.cn/problem/CF245A)

[$\color{red}{see}\space \color{green}{in}\space \color{blue}{my}\space \color{purple}{blog}$](https://www.luogu.com.cn/blog/liangbowen/solution-cf245a)

小学生又双叒叕来写题解啦！

这题难度并不高，是一个简单的**模拟**。

## 题目大意：

+ 有两台服务器。

+ 向服务器发送信息，信息分为两种：发送成功与发送失败。

+ 最后计算服务器是“活的”还是“死的”。

## 解题思路：

在此为萌新隆重推出：结构体！

结构体定义如下：

```cpp
//定义一个名字叫 QAQ 的结构体。 
struct QAQ
{
	//可以在结构体内定义各种类型的变量。 
	int a, b;  
	bool c;
};            //注意末尾的分号不要漏掉。 
QAQ x, y;     //创建 QAQ 类型的变量。
QAQ z[233];   //也可以定义数组。 
```

定义完了，如何使用呢？

```cpp
int main()
{
	cin >> x.a >> y.b;  //读入。
	cout << x.a << " " << y.b << " ";  //输出。
	x.a += 233;
	cout << x.a << " ";
	if (x.a == y.b) cout << "equal!";
	//和变量一样，可以斌值、比较等。 
	return 0;
}
```

结构体很容易吧，那就试着用结构体做这一题！

我们用结构体记录两个服务器的状态，如下。

```cpp
struct Ping
{
	int live, dead;
};
Ping a, b;
```

对于每条信息，我们可以这样处理：

```cpp
int t, x, y;
cin >> t >> x >> y;
if (t == 1)  //第一台服务器。
{
	a.live += x;
	a.dead += y;
}
else if (t == 2)  //第二台服务器。
{
	b.live += x;
	b.dead += y;
}
```
最后，判断计算机“是活是死”。

```cpp
if (a.live >= a.dead) cout << "LIVE\n";
else cout << "DEAD\n";
if (b.live >= b.dead) cout << "LIVE\n";
else cout << "DEAD\n"; 
```

这样就可以轻松通过这一题啦！

前面已经讲解得很详细，完整代码便不加注释了。

## 完整代码：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
struct Ping
{
	int live, dead;
};
Ping a, b;
int main()
{
	int n;
	scanf("%d", &n);
	while (n--)
	{
		int t, x, y;
		scanf("%d%d%d", &t, &x, &y);
		if (t == 1)
		{
			a.live += x;
			a.dead += y;
		}
		else if (t == 2)
		{
			b.live += x;
			b.dead += y;
		}
	}
	if (a.live >= a.dead) printf("LIVE\n");
	else printf("DEAD\n");
	if (b.live >= b.dead) printf("LIVE\n");
	else printf("DEAD\n"); 
	return 0;
}
```

---

## 作者：chenyilai (赞：1)

这是一道简单的模拟题，难度为入门。我们只需用一个数组（或几个变量）来存储服务器1和服务器2接收和没接收到的

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,lx,x,y,a[3][3];
//a[1][1]用来存储服务器1接收到的，a[1][2]用来存储服务器1没接收到的。
//a[2][1]用来存储服务器2接收到的，a[2][2]用来存储服务器2没接收到的。
int main(){
	scanf("%lld",&T);
	while (T--){
		scanf("%lld%lld%lld",&lx,&x,&y);
	    a[lx][1]+=x; a[lx][2]+=y;//读入数据并进行存储。
	}
	if (a[1][1]>=a[1][2]) printf("LIVE\n");
	else printf("DEAD\n");//判断服务器1是"LIVE"还是"DEAD"并输出
	if (a[2][1]>=a[2][2]) printf("LIVE\n");
	else printf("DEAD\n");//判断服务器2并输出。
    return 0;
}
```
最后提醒大家千万不要抄答案，要自己认真思考哟！

---

## 作者：lovely_hyzhuo (赞：0)

## 本题思路

模拟，先就设定两个结构体变量，里面都只存两种变量。

```cpp
struct comp
{
	int sum;//sum表示总共从网络过来多少数据包
	int t;//t表示总共成功过来多少数据包
};
```
然后对于每一次命令（将每次发射数据包称为 $1$ 次命令）,记录成功多少次，$t$ 累加，总共来了多少，$sum$ 累加。

接下来看是否达到一半即可。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct comp
{
	int sum;
	int t;
};
int main()
{
	int n;
	cin>>n;
	comp a,b;
	a.sum=0;
	a.t=0;
	b.sum=0;
	b.t=0;
	for(int i=1;i<=n;i++)
	{
		int ti,ci,bi;
		cin>>ti>>ci>>bi;
		if(ti==1)
		{
			a.t+=ci;
			a.sum+=ci+bi;
		}
		else
		{
			b.t+=ci;
			b.sum+=ci+bi;
		}
	}
	if(a.t>=a.sum/2)
	{
		cout<<"LIVE"<<endl;
	}
	else
	{
		cout<<"DEAD"<<endl;
	}
	if(b.t>=b.sum/2)
	{
		cout<<"LIVE"<<endl;
	}
	else
	{
		cout<<"DEAD"<<endl;
	}
	return 0;
}
```


---

## 作者：lmndiscyhyzdxss (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF245A)
## 题意
题目就是说每次  Polycarpus  会向服务器  a  或服务器  b  发送十个数据包，十个数据包中，有的发送成功，有的发送失败，如果最后成功数量大于失败数量，则这个服务器是活动的，便输出  "LIVE" ,反之便是不活动的，输出  "DEAD" 。两个服务器的状态都要输出。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,p,c,s,ac/*a成功的数量*/,as/*a失败的数量*/,bc/*b成功的数量*/,bs/*b失败的数量*/;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>p>>c>>s;//输入
        if(p==1)ac+=c,as+=s;//记录服务器a成功与失败数量
        if(p==2)bc+=c,bs+=s;//记录服务器b成功与失败数量
    }
    if(ac>=as)cout<<"LIVE"<<endl;//输出服务器a的状态
    else cout<<"DEAD"<<endl;
    if(bc>=bs)cout<<"LIVE"<<endl;//输出服务器a的状态
    else cout<<"DEAD"<<endl;
    return 0;
}
```


---

## 作者：ttq012 (赞：0)

模拟题。

定义 $s_1$，$s_2$，$d_1$，$d_2$ 四个变量，初始值为 $0$。

对于每一组输入数据，如果第一个数为 $1$，那么令 $s_1$ 加上第二个数，$d_1$ 加上第三个数，否则令 $s_2$ 加上第二个数，$d_2$ 加上第三个数。

当 $s_1\ge d_1$，就代表第一个机器成功到达的数量比没有成功到达的数量要多，那么就代表机器是活动的，输出 `LIVE`，否则机器不是活动的，输出 `DEAD`。

$s_2$ 和 $d_2$ 的输出处理同理。

```cpp
#include <bits/stdc++.h>
using namespace std;

signed main() {
    int n;
    cin>>n;
    int s_1=0,s_2=0,d_1=0,d_2=0;
    for(int i=1;i<=n;i++)
    {
        int c,a,b;
        cin>>c>>a>>b;
        if(c==1)s_1+=a,d_1+=b;
        else s_2+=a,d_2+=b;
    }
    if (s_1>=d_1)puts("LIVE");
    else puts("DEAD");
    if (s_2>=d_2)puts("LIVE");
    else puts("DEAD");
    return 0;
}

```

---

## 作者：TianLuen (赞：0)

# CF245A C++题解
## 题目大意
- 有 $2$ 台服务器。
- 有 $n$ 条命令。
- 每条命令会发送 $10$ 个文件。
- 每条指令会指明发送对象，成功文件数和失败文件数。
- 如果一台服务器 没有收到的文件数 $<$ 成功收到的文件数，那么此服务器是活跃的(LIVE)，反之是 ~~死的~~ 不活跃的(DEAD)。
- 输出两台服务器的活跃状态。
## 题意分析
此题纯模拟即可。

仔细读题之后，可以看出代码应该怎么写。这里有两种解法，本质上是类似的。
### 解法一
在读入数据时，分别存储每个服务器成功数和失败数。比如我，用`as,af,bs,bf`四个变量存储（s指success，f指fail），中规中矩地输入变量。在输出时比较两者，输出 LIVE 或 DEAD 即可。

优点：容易理解，浅显易懂
### 解法二
在读入数据时，每个服务器用 $1$ 个变量存储，**加上成功数，减掉失败数**。在输出部分时判断，如果为**非负数**，输出 LIVE ，反之输出 DEAD。

优点：变量较少，代码较短
## 代码
### 解法一
```
#include<iostream>
using namespace std;
int as,af,bs,bf,N,n,a,b;
int main()
{
    cin>>N;
    for(int i=0;i<N;i++)
    {
        cin>>n>>a>>b;
        if(n==1)
        {
            as+=a;
            af+=b;
        }
        else
        {
            bs+=a;
            bf+=b;
        }
    }
    if(as>=af)
        cout<<"LIVE\n";
    else
        cout<<"DEAD\n";
    if(bs>=bf)
        cout<<"LIVE\n";
    else
        cout<<"DEAD\n";
    return 0;
}
```
### 解法二
```
#include<iostream>
using namespace std;
int aa,bb,N,n,a,b;
int main()
{
    cin>>N;
    for(int i=0;i<N;i++)
    {
        cin>>n>>a>>b;
        if(n==1)
            aa+=a-b;
        else
            bb+=a-b;
    }
    if(aa>=0)
        cout<<"LIVE\n";
    else
        cout<<"DEAD\n";
    if(bb>=0)
        cout<<"LIVE\n";
    else
        cout<<"DEAD\n";
    return 0;
}
```
## THE END

---

## 作者：inoichi_lim (赞：0)

我们可以定义一个$a$数组。

用$a_{i,1}$来表示第$i$个服务器收到的数量，用$a_{i,2}$来表示第$i$个服务器没收到的数量。

先执行$n$个指令分别输入$z,x,y$。

然后将$a_{z,1}$加上$x$，$a_{z,2}$加上$y$。

----

最后分别比较$a_{1,1}$与$a_{1,2}$，以及$a_{2,1}$与$a_{2,2}$，大则输出`LIVE`，小则输出`DEAD`。

代码：
```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#undef FILE
int a[11][11],n;
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	fs(i,1,n,1){
		int x,y,z;
		cin>>z>>x>>y;
		a[z][1]+=x;
		a[z][2]+=y;
	}
	if(a[1][1]>=a[1][2]) cout<<"LIVE\n";
	else cout<<"DEAD\n";
	if(a[2][1]>=a[2][2]) cout<<"LIVE\n";
	else cout<<"DEAD\n";
	return 0;
}

```

---

## 作者：FR_qwq (赞：0)

这题非常水，题意就是有俩服务器，有 n 个指令，每个指令分别有仨操作数 t、x 和 y，t 表示是哪个服务器，x 表示传出文件成功的个数，y 表示传出文件t失败的个数，请求出哪个多哪个少，传出文件成功总数 ≥ 失败总数输出 LIVE 否则输出 DEAD。

看完题后，你一定会想：这不就是一道水模拟吗？？？

没错，你对了（~~你以为我会说你错吗~~）

所以，我们就能很快的吧程序编出来了。

这是 pascal 代码：
```pascal
var n,t,x,y,i:longint;
a:array[1..2,0..1]of longint;
begin
readln(n);
for i:=1 to n do
  begin
  readln(t,x,y);//美丽的输入
  a[t,1]:=a[t,1]+x;//后面的1表示成功总数
  a[t,0]:=a[t,0]+y;//后面的0表示失败总数
  end;
if a[1,1]>=a[1,0]then writeln('LIVE')
else writeln('DEAD');//判断，如果成功总数≥失败总数，输出 LIVE 否则输出 DEAD
if a[2,1]>=a[2,0]then writeln('LIVE')
else writeln('DEAD');//同上
end.
```

C 党看这：
```c++
#include<iostream>
#include<cstdio>//you 也 can use 万能头
using namespace std;
int n,t,x,y,i,a[3][2];//好的定义
int main(){
    scanf("%d",&n);//美丽的输入
    for(i=1;i<=n;i++)
        scanf("%d%d%d",&t,&x,&y),a[t][1]+=x,a[t][0]+=y;//后面的1表示成功总数,后面的0表示失败总数
    if(a[1][1]>=a[1][0])printf("LIVE\n");
    else printf("DEAD\n");//判断，如果成功总数≥失败总数，输出 LIVE 否则输出 DEAD
    if(a[2][1]>=a[2][0])printf("LIVE\n");
    else printf("DEAD\n");//同上
    return 0;
}
```


---

