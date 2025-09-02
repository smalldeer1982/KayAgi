# Metro

## 题目描述

Alice今天过生日，所以她邀请了她的好朋友Bob。现在Bob需要找到一种方法前去Alice家。
在Alice和Bob住的城市里，第一条地铁线正在施工中，仍处于试运行阶段。现在的地铁线有n个车站，编号从1至n。Bob住在1号站附近，Alice住在s号站附近。这条地铁线有两条轨道。第一条从1至n行驶，另一条则反之。当一辆车到达终点后，它会直接前去车辆段（停车场），所以Bob不可以坐到头后继续坐在车上。
有一些车站只是部分打开，而某些车站则完全没有打开。Bob取到了他要去拜访Alice时所有车站的开关情况。如果一个车站在某轨道上是关闭的，则列车在经过此车站时，会不加停靠的直接开过去。
在Bob研究了一会时间表后，他发现去参加Alice的Party可能会不一般的困难。请帮助Bob确定他应该坐地铁还是换一种交通方式去拜访Alice。

## 样例 #1

### 输入

```
5 3
1 1 1 1 1
1 1 1 1 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
5 4
1 0 0 0 1
0 1 1 1 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
5 2
0 1 1 1 1
1 1 1 1 1
```

### 输出

```
NO
```

# 题解

## 作者：yzh_Error404 (赞：2)

 ### 题意
 $\text{Bob}$家住在地铁的$1$号站，$\text{Alice}$家住在$s$号站，地铁有两条轨道，一条从$1$到$n$,另一条从$n$到$1$，中间有一些站点不开放，$\text{Bob}$想去$\text{Alice}$家玩，问能否到达
 
### 题解
我们可以把坐到$s$号站的方法分成两种：
 
1. **在第一条轨道上从$1$号站坐到$s$号站**
	
    如果第一条轨道上的$1$号和$s$号站都开放的话，$\text{Bob}$就可以实现不换车到达$s$号站，特判即可

2. **在第一条轨道上坐到$k$号站，再换乘第二条轨道坐到$s$号站**（$k \in [s+1,n]$）
	  
    如果第二条轨道上的$s$号站开放，且后面有可以换乘的站点时，$\text{Bob}$也是可以到达的
    
上代码
 	
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s;
bool a[1005],b[1005];
inline void Yes()
{
	puts("Yes");
	return;
}
inline void No()
{
	puts("No");
	return;
}
int main()
{
	scanf("%d%d",&n,&s);
	for(register int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(register int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	if(a[1]==0){No();return 0;}//Bob连上车都不行，肯定到不了
	if(a[s]==1){Yes();return 0;}//可以直接到达s号站
	if(b[s]==0){No();return 0;}//不能换乘第二条轨道
	for(register int i=s+1;i<=n;i++)
	{
		if(a[i]==b[i]&&a[i]==1)//找到了可以换乘的站台
		{
			Yes();
			return 0;
		}
	}
	No();
	return 0;
}

```

---

## 作者：sxq9 (赞：1)

这一题挺简单的，其实只要将各种情况特判就好了，情况一共就几种，每一种判断就好了：

1.不能到达的：

- Bob 进不了站
- Alice 家的站到不了
- Alice 家的站不能过去但是可以回来，且无法换乘

2.可以到达的:

- Bob 家的站到 Alice 家的站可直达
- Bob 家的站可以通过换乘到达

分析完了，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,s,a[3][1010];
	cin>>n>>s;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	if(a[1][1]==0||a[1][s]==0&&a[2][s]==0){cout<<"NO";return 0;}//不能进站或不可到达
	else if(a[1][1]&&a[1][s]){cout<<"YES";return 0;}//可以直达
	else{
		for(int i=s;i<=n;i++){
			if(a[1][i]&&a[2][i]){cout<<"YES";return 0;}//可以换乘，注意从s开始
		}
	}
	cout<<"NO";//可去不可回，且无法换乘
	return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：  

就是两趟火车，去一趟，回一趟。

如果开门就可以进否则就进不了。  

这题可以**大分讨**！

注意以下判断有先后顺序。   

1. 终点是我家 成立！ $s=1$     
1. 家都出不了 不成立！ $a_1=0$     
1. 一趟就可达 成立！$a_s=1$      
1. 回来家被封 不成立！$b_s=0$   
1. 可去又可回 成立！ $a_k=1$ 并且 $b_k=1$     

### Solution：

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e3+50;
const int M=1e5+50;
const int Mod=1e9+7;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

int n,s;

int a[N],b[N];

int main()
{
	n=read(),s=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) b[i]=read();
	if(s==1) {
		printf("YES\n");
		return 0;
	}
	if(a[1]==0){
		printf("NO\n");
		return 0;
	}
	if(a[s]==1){
		printf("YES\n");
		return 0;
	}
	if(b[s]==0){
		printf("NO\n");
		return 0;
	}
	bool flag=0;
	for(int i=s+1;i<=n;++i){
		if(a[i]&&b[i]){
			flag=1;
			break;
		}
	}
	if(flag){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
	return 0;
}

```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1055A)

## 前言

看到这题是个蓝题还以为要写最短路，做完以后感觉这题~~最多是个黄~~。

## 分析

我们用序列 $A$ 记录 $1-n$ 中站点的开放情况，用序列 $B$ 记录 $n - 1$ 中站点开放的情况。

这题其实就是一个分类讨论的题目，我们来思考一下什么情况能到，什么情况到不了。

1. 当 $A[1] == 0$，也就是连车都上不了，肯定到不了。
2. 当 $A[1]\&\&A[s]$，这个时候我们可以通过 $1-n$ 的路线直达目的地，所以可以到达。
3. 当 $1$, $2$ 两种情况均不满足，我们考虑从 $s + 1 - n$ 这一段路线中转，我们可以枚举这一段路径上的所有站点，如果存在一个站点 $i$ 使得 $A[i]\&\&B[i]\&\&B[s]$ ，这个时候我们就可以从 $1$ 坐到 $i$ ，再从 $i$ 坐到 $s$，我们就可以到达了，反之如果不存在这样的站点，那我们就到达不了。

所以，我们就可以根据这些结论写出极短的代码了。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 1010;
int a[N], b[N];

int main()
{
    int n, s;
    cin >> n >> s;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    if (!a[1]) puts("NO");
    else if (a[s]) puts("YES");
    else
    {
        bool flag = false;
        for (int i = s + 1; i <= n; i++)
            if (a[i] && b[i] && b[s])
                {
                    puts("YES");
                    flag = true;
                    break;
                }
        if (!flag) puts("NO");
    }
    return 0;
}
```





---

## 作者：charleshe (赞：0)

来一篇不太一样的题解。

我们可以把所有站点抽象的看成是一些点，而地铁线路看成链接这些点的线。

此时可以发现：这些站点构成了一张有向图啊！

因此题目就变成了：给出一张有向图，问 1 点和 $s$ 点中间是否有路径相连。

考虑图论。

由于点的数量（即题目中的 $n$）数据范围极小，因此考虑邻接矩阵。

注意有几个细节：

1. 当 Bob 可以直接到达 Alice 家（即乘坐一辆地铁就可以到达）时，直接输出 YES。
1. 在此基础上，若第一条地铁到不了 Bob 家，或第二条地铁到不了 Alice 家，直接输出 NO。（注意是在此基础上，不然你会 WA 在第四个点上）。
1. 无需考虑 $1,2,\ldots,s-1$ 这些点，毕竟 Bob 在这些点换乘也到不了 Alice 家。

考虑完这些，写代码就轻松了。
```
#include <iostream>
using namespace std;
int n,s;
bool a[1001],b[1001],w[1001][1001];//a和b为两条地铁线路，w为邻接矩阵
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	if(a[1]&&a[s]) cout<<"YES";//一条地铁可到直接输出YES
	else if(!a[1]||!b[s]) cout<<"NO";//连家门口都到不了，直接输出NO
	else{
		for(int i=s;i<=n;i++){//细节三（其实这个可以算一个小优化）
			if(a[i]) w[1][i]=1;
			if(b[i]) w[i][s]=1;//利用两条地铁线路推广至有向图，将每条边存入邻接矩阵
		}
		bool flag=true;
		for(int i=s;i<=n;i++){
			if((w[1][i]&&w[i][s])){//若可以到达输出YES
				cout<<"YES";
				flag=false;
				break;
			}
		}
		if(flag/*flag用来判断是否有输出。若无输出，即无法到达，输出NO*/) cout<<"NO";
	}
	return 0;
}
```

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题其实考察的就是对基本语法的应用，那这道题的难点在哪里呢，其实在于本题需要分类讨论的情况是比较多的，所以大家在写代码时一定要认真细致，分类不重不漏哦~

接下来我来带着大家分类：

1. 如果 Bob 家从第 $1$ 站开往第 $n$ 站的的地铁根本就不停，那么 Bob 根本就上不了地铁，更别说到 Alice 的家了。
1. 如果 Alice 家双向的地铁都不停的话，那么 Bob 就算上了地铁也无法出站，所以也是不行的。

那么除了这两种容易特别容易因考虑不全面而 WA 的情况以外，还有两种大家都能想到的正常线路分类：

1. 如果 Bob 家到 Alice 家能直达，那么 Bob 就会从第 $1$ 站开始往第 $n$ 站的方向坐，直接做到第 $s$ 站即可。
1. 那如果不能直达呢？那么此时 Bob 如果想到 Alice 家，就必须从第 $1$ 站开始往第 $n$ 站的方向坐，先坐过 Alice 家去找一个双向都通的站去换成反方向，然后坐回到 Alice 家。

鉴于上面第二种不好理解，所以我放一张图片解释一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/u7w58mzl.png)

说了这么多，上代码：

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,s;
	cin>>n>>s;
	const int maxn=1000+5;
	bool a[maxn],b[maxn];
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	
	if(a[1]==1&&(a[s]==1||b[s]==1))
	{
		if(a[s]==1)
		{
			cout<<"Yes";
			return 0;
		}
		else
		{
			for(int i=s+1;i<=n;i++)
			{
				if(a[i]==1&&b[i]==1)
				{
					cout<<"Yes";
					return 0;
				}
			}
			
		}
	}
	cout<<"No";
	return 0;
}

```

谢谢观看~

---

## 作者：shenmadongdong (赞：0)

其实这道题只需判断一些特殊情况即可

代码：
```
var n,s,i,g:longint;
    a,b:array [1..1000] of longint;
begin
  read(n,s);
  for i:=1 to n do read(a[i]);
  for i:=1 to n do read(b[i]);
  if a[1]=0 then begin write('NO'); exit; end;
  if a[s]=1 then begin write('YES'); exit; end;//判断能否不掉头就到
  if b[s]=0 then begin write('NO'); exit; end;
  for i:=s+1 to n do if (a[i]=1)and(b[i]=1) then g:=1;
  if g=1 then write('YES') else write('NO');//判断能否掉头后到
end.
```

---

