# New Year Transportation

## 题目描述

New Year is coming in Line World! In this world, there are $ n $ cells numbered by integers from $ 1 $ to $ n $ , as a $ 1×n $ board. People live in cells. However, it was hard to move between distinct cells, because of the difficulty of escaping the cell. People wanted to meet people who live in other cells.

So, user tncks0121 has made a transportation system to move between these cells, to celebrate the New Year. First, he thought of $ n-1 $ positive integers $ a_{1},a_{2},...,a_{n-1} $ . For every integer $ i $ where $ 1<=i<=n-1 $ the condition $ 1<=a_{i}<=n-i $ holds. Next, he made $ n-1 $ portals, numbered by integers from 1 to $ n-1 $ . The $ i $ -th ( $ 1<=i<=n-1 $ ) portal connects cell $ i $ and cell $ (i+a_{i}) $ , and one can travel from cell $ i $ to cell $ (i+a_{i}) $ using the $ i $ -th portal. Unfortunately, one cannot use the portal backwards, which means one cannot move from cell $ (i+a_{i}) $ to cell $ i $ using the $ i $ -th portal. It is easy to see that because of condition $ 1<=a_{i}<=n-i $ one can't leave the Line World using portals.

Currently, I am standing at cell $ 1 $ , and I want to go to cell $ t $ . However, I don't know whether it is possible to go there. Please determine whether I can go to cell $ t $ by only using the construted transportation system.

## 说明/提示

In the first sample, the visited cells are: $ 1,2,4 $ ; so we can successfully visit the cell $ 4 $ .

In the second sample, the possible cells to visit are: $ 1,2,4,6,7,8 $ ; so we can't visit the cell $ 5 $ , which we want to visit.

## 样例 #1

### 输入

```
8 4
1 2 1 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
8 5
1 2 1 2 1 1 1
```

### 输出

```
NO
```

# 题解

## 作者：Register (赞：8)

## 很简单的递推，按照题目来
	每次都加上改牢房对应的传送距离，方案只有一种
##### for循环的好处就是三个语句可以执行很多的事，所以递推一行for就能搞定
上代码：
```cpp
#include <iostream>
using namespace std;
int main(){
    int a[30001],n,t;
    cin>>n>>t;
    for(int i=1;i<n;i++) cin>>a[i];
    int i;
    for(i=1/*从牢房1开始*/;i<t/*大于等于t就可以下结论了*/;i+=a[i]/*每次加对应的距离*/) ;//递推
    if(i==t) cout<<"YES"<<endl;//到达
    else cout<<"NO"<<endl;//超过了
    return 0;
}
```

---

## 作者：HNYLMS_MuQiuFeng (赞：4)

~~这道题也是很水呢。~~

这道题其实就是先读完所有数据再加现在这个点上的步数。

如果刚刚好到达目标点就可以

如果超过了就不行

AC代码如下：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int n,t;cin>>n>>t;
	int a[n+1];
	int ans=1;
	for(int i=1;i<=n-1;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n-1;i++)
	{
		ans+=a[ans];//加这一个点上的步数
		if(ans==t)
		{
			cout<<"YES";
			return 0;
		}
		if(ans>t)
		{
			cout<<"NO";
			return 0;
		}
	}
}//日常AC啦！锵锵！
```
## 杜绝抄袭，从我做起！！

---

## 作者：OdtreePrince (赞：4)

# -递归-

这道题用了递归的思想，由于每个牢房只有一个传送门，

只需慢慢递归到传送门到达的牢房，如果能到达，yes。

就这么简单，上代码。

~~~
#include<bits/stdc++.h>
using namespace std;
int n,a[30005],t;
int main(){
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n-1;i++){
        scanf("%d",&a[i]);
        a[i]+=i;
    }
    int j=1;
    while(a[j]!=t&&j!=n){
        j=a[j];
    }
    if(a[j]==t) cout<<"YES";
    else cout<<"NO";
    return 0;
}~~~

---

## 作者：empty_zhm (赞：3)

~~**挑战题解最短啊！**~~ 
# 思路是递推
**就是从一号房开始一层一层的往前传送（因为是唯一路径嘛）**
```cpp
#include<iostream>
using namespace std;
int N[50100],n,k,j=1;
int main()
{
	cin >> n >> k;
	for(int i=1;i<=n-1;i++) cin >> N[i];
	while(j<k) j+=N[j];//这里只有TP没有B键，没法回头，超过去就已经失败了
	cout << (j==k?"YES":"NO");
}
```
~~**当然有更短的**~~
```cpp
#include<iostream>
using namespace std;
int i=1,n,t,a,k=1;
int main()
{
	cin >> n >> t;
	for(;i<n;i++)
		cin >> a,
		k+=i^k?0:k<t?a:0;
	cout << (k^t?"NO":"YES");
}
```
PS:三目运算符的嵌套可以参考if语句


---

## 作者：Lips (赞：2)

# $dijkstra$ 模板

楼下全是递推和递归~~或者是一些奇奇怪怪的操作~~,这里蒟蒻就写个 $dijkstra$。也作为蒟蒻 $AC$ 的第 $100$ 个橙题纪念一下。

**首先，可以将此题意抽象成一张图**

有 $n$ 个点，$(n-1)$ 条边，第 $i$ 条边连接点 $i$ 和点 $i+a_i$（单向边），问：从点 $1$ 是否能到达点 $t$。

**解题思路**

输入时对于每一个 $i(1\le i< n)$ 连一条边 $(i,a_i+i)$ 即可。之后以 $1$ 点为起点跑一边 $dijkstra$ 最短路，用 $d$ 来记录 $1$ 到各个点的最短路，初始设为 $1e9$，只要在跑完最短路后 $d_t$ 的值为 $1e9$，那么就说明不可到达，输出 `NO`；否则输出 `YES`。

~~这么一道一眼水题真的是没什么好讲的了。~~

$Code:$ （高清无删减~~方某些人便抄~~）

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=30010;
int n,t,a[MAXN],d[MAXN];
struct edge
{
	int to,cost;
	edge(int to,int cost):to(to),cost(cost){}
};
vector<edge>G[MAXN];
typedef pair<int,int> P;
void dijkstra(int s)
{
	priority_queue<P,vector<P>,greater<P> >q;
	for(register int i=1;i<=n;i++) d[i]=1e9;
	d[s]=0;
	q.push(make_pair(0,s));
	while(!q.empty())
	{
		P p=q.top();
		q.pop(); 
		int v=p.second;
		if(d[v]<p.first) continue;
		for(register int i=0;i<G[v].size();i++)
		{
			edge e=G[v][i];
			if(d[e.to]>d[v]+e.cost)
			{
				d[e.to]=d[v]+e.cost;
				q.push(make_pair(d[e.to],e.to));
			}
		}
	}
}
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
void add_edge(int u,int v) {G[u].push_back(edge(v,1));}
int main()
{
	n=read(),t=read();
	for(register int i=1;i<n;i++) a[i]=read();
	for(register int i=1;i<n;i++) add_edge(i,i+a[i]);
	dijkstra(1);
	if(d[t]==1e9) puts("NO");
	else puts("YES");
	return 0;
} 
```

完结撒花~!




---

## 作者：chenyilai (赞：1)

**目录**
1. 目录
2. 思路
4. 代码

**思路**

根据题意模拟 $m$（你通过传送门到的牢房）,可以用递归或循环。

模拟时：
* 如果 $m=t$，表示你已经到达了这个牢房，输出`YES`。
* 如果 $m>t$，表示你过了这个牢房，输出`NO`。

**代码**

提供一种递归的做法：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,a[30001];
bool sou(int m){
	return((m==t)?true:(m>t)?false:sou(m+a[m-1]));
}
int main(){
	scanf("%lld%lld",&n,&t);
	for (int i=0;i<t;i++) scanf("%lld",&a[i]);//读入t后面的数据毫无意义，可以不读。
	printf("%s",(sou(1)?"YES":"NO"));
	return 0;
}
```
对于不懂sou函数中这~~奇奇怪怪~~的式子的同学，可以看[这个](http://iwo.im/?q=%E4%B8%89%E7%9B%AE%E8%BF%90%E7%AE%97%E7%AC%A6)。

这条语句也可以理解为：
```cpp
if (m==t) return true;
else if (m>t) reutrn false;
else return sou(m+a[m-1]);
```

---

## 作者：RainFestival (赞：1)

这道题有那么水吗？？居然是红题

我们可以用图论的方法连边

把i与i+ai连一条边（有向）

再用bfs或者dfs求1，t是否连通就可以啦

但是我们注意到ai都是正数

也就是说

你在某一个牢房，只能从这个牢房到比这个牢房编号大的牢房

就可用递推啦

我们用bi表示第i个牢房是否可以到达

如果bi=true，则b i+ai=true

初始条件b1=true

最后看bk是否为true就行啦

下面是代码：

```cpp
#include<iostream>
using namespace std;
int a[30005],b[30005];
int main()
{
    int n,t;
    cin>>n>>t;
    for (int i=1;i<=n-1;i++)
      cin>>a[i];
    b[1]=true;
    for (int i=1;i<=n;i++)
      if (b[i]) b[i+a[i]]=true;
    if (b[t]) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
    return 0;
}
```

时间885ms,空间244k,代码长度0.3k

谢谢神犇、大佬、巨佬们的观赏！！！

---

## 作者：GVNDN (赞：0)

~~大水题一道~~

若令当前房号为$f_i$，则$f_i = f_i-_1 + a_i-_1$，根据这个式子从1号房往后推就好了。

若令目标房号为d，共有n个房，则结束条件是$f_i = f_d$（成功到达目标房）或$f_i >= n$（已经到了最后一个房或超过了最后一个房的号却没有到达目标房）。

代码如下：
```cpp
#include<iostream>
using namespace std;

int a[30100], n, dest;

int go(int n1){
	if(n1 == dest) return 1;    //注意两个结束判断语句顺序不能反
	if(n1 >= n) return 0;
	int n2 = n1 + a[n1];
	go(n2);
}

int main(){
	cin >> n >> dest;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	int f = go(1);
	if(f) cout << "YES";
	else cout << "NO";
	return 0;
}
```

---

## 作者：北雪2009 (赞：0)

~~这道题是一道暴力题。~~   
这道题只需要枚举就行啦qaq！！！   
首先先输入，然后循环输入a数组。接下来就到了本程序最最最最最……重要的地方了！！那就是：for穿越牢房！！走起！！等等啊，情绪有点小激动了！首先先定义一个变量为穿越变量，将其设为1。然后开始穿越。在穿越时穿越变量不能超过要去的牢房，否则……你走到哭也不能走到你想去的那个牢房！！最后，再判断穿越变量是否等于要去的牢房的号码，如果等于就输出“YES”，否则输出“NO”。      
（为了响应洛谷的“不要抄袭”的口号，程序嘛……就不写出来了！！！）

---

## 作者：打表大蒟蒻 (赞：0)

找了一圈，没发现用递归函数做的，蒟蒻就来补一个

递归各位大佬应该都知道，是一个~~诡异的~~神器，就是一个函数不停的调用自己，如果到了终止条件就退出。这道题可以用一个形参num做判断标志，代替题意中的i。
具体注释代码里有，直接上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXn = 30000 + 10;  //定义常量
int a[MAXn];  //定义数组
inline int read(){
   int s=0,w=1;   
   char ch=getchar();   
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}   
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();   
   return s*w;
}//懒得手写快读，就从网站上复制了一个
void pd(int t,int num){  //一个t和一个判断标志num
	if(num==t) {printf("YES\n");return ;} //如果运行到了t号牢房就输YES，退出
	else if(num>t)  {printf("NO\n");return ;}  //如果跑过站了，说明无解，直接输NO
	num+=a[num];  //num加上a[num] 根据题意写
	pd(t,num);   //继续递归
}  
int main ()  //开始极简主函数
{
	int n, t;  
	n=read();t=read();  //快读
	for(int i=1;i<n;i++) a[i]=read();
	pd(t,1);  //递归调用
	return 0;  //完美结束
 } 
```
~~说实话，CF中的普及-难度题也就是洛谷中的红题~~

---

