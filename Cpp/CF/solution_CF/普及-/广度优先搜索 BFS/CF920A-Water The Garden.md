# Water The Garden

## 题目描述

It is winter now, and Max decided it's about time he watered the garden.

The garden can be represented as $ n $ consecutive garden beds, numbered from $ 1 $ to $ n $ . $ k $ beds contain water taps ( $ i $ -th tap is located in the bed $ x_{i} $ ), which, if turned on, start delivering water to neighbouring beds. If the tap on the bed $ x_{i} $ is turned on, then after one second has passed, the bed $ x_{i} $ will be watered; after two seconds have passed, the beds from the segment $ [x_{i}-1,x_{i}+1] $ will be watered (if they exist); after $ j $ seconds have passed ( $ j $ is an integer number), the beds from the segment $ [x_{i}-(j-1),x_{i}+(j-1)] $ will be watered (if they exist). Nothing changes during the seconds, so, for example, we can't say that the segment $ [x_{i}-2.5,x_{i}+2.5] $ will be watered after $ 2.5 $ seconds have passed; only the segment $ [x_{i}-2,x_{i}+2] $ will be watered at that moment.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/13bc7cf6794d83f150515b3ef05c019c5a177edb.png) The garden from test $ 1 $ . White colour denotes a garden bed without a tap, red colour — a garden bed with a tap.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920A/7701b634db65a2b1523162fa68f6ca25374deecc.png) The garden from test $ 1 $ after $ 2 $ seconds have passed after turning on the tap. White colour denotes an unwatered garden bed, blue colour — a watered bed. Max wants to turn on all the water taps at the same moment, and now he wonders, what is the minimum number of seconds that have to pass after he turns on some taps until the whole garden is watered. Help him to find the answer!

## 说明/提示

The first example consists of $ 3 $ tests:

1. There are $ 5 $ garden beds, and a water tap in the bed $ 3 $ . If we turn it on, then after $ 1 $ second passes, only bed $ 3 $ will be watered; after $ 2 $ seconds pass, beds $ [1,3] $ will be watered, and after $ 3 $ seconds pass, everything will be watered.
2. There are $ 3 $ garden beds, and there is a water tap in each one. If we turn all of them on, then everything will be watered after $ 1 $ second passes.
3. There are $ 4 $ garden beds, and only one tap in the bed $ 1 $ . It will take $ 4 $ seconds to water, for example, bed $ 4 $ .

## 样例 #1

### 输入

```
3
5 1
3
3 3
1 2 3
4 1
1
```

### 输出

```
3
1
4
```

# 题解

## 作者：nenugdi (赞：9)

除了第一个和最后一个龙头外，其他龙头间区域的覆盖时间都是两个龙头距离除2。第一个龙头和最后一个单独处理。

```cpp
#include <iostream>
using namespace std;
/**< 水龙头第一秒给自己所在区域浇水，第二秒开始向左右两个方向喷水 */
int main()
{
    int i,j,t,n,k,x,pre,maxn;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        cin>>pre;
        maxn=pre;/**< 第一个水龙头到最左侧第一个方格花费的时间 */
        for(i=2;i<=k;i++) /**<从第二个水龙头开始计算它与前一个水龙头的距离，距离除2再加1 */
        {
            cin>>x;
            maxn=max(maxn,(x-pre)/2+1);/**< 找最大值 */
            pre=x;
        }
        maxn=max(maxn,n-pre+1);/**< 最后一个水龙头到n的距离 */
        cout<<maxn<<endl;
    }
    return 0;
}

```

---

## 作者：codesonic (赞：9)

BFS，在每个水龙头放置的方格入队，然后bfs，顺便记录每个节点当前被搜索到的时间点，找出其中最大的即可
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=210;
int x[maxn];
bool vis[maxn];
int cnt=0;
struct node {
	int s,dep;//dep记录时间
};
queue<node> q;
int ans=-1;
int main() {
	int t;
	scanf("%d",&t);
	while(t--) {
		memset(vis,0,sizeof(vis));
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i=1; i<=k; i++) {
			int t;
			scanf("%d",&t);
			node temp;
			temp.s=t;
			temp.dep=1;
			q.push(temp);
			vis[temp.s]=1;//对每个扩展到的入队
		}
		while(!q.empty()) {
			node x=q.front();
			q.pop();
			ans=max(ans,x.dep);
			if(x.s-1>0&&!vis[x.s-1]) {
				node temp;
				temp.s=x.s-1;
				temp.dep=x.dep+1;
				vis[x.s-1]=1;
				q.push(temp);
			}
			if(x.s+1<=n&&!vis[x.s+1]) {
				node temp;
				temp.s=x.s+1;
				temp.dep=x.dep+1;
				vis[x.s+1]=1;
				q.push(temp);
			}//向两个方向扩展
		}//BFS
		printf("%d\n",ans);
		ans=-1;
	}
	return 0;
}
```

---

## 作者：CHIS_fy (赞：7)

蒟蒻的第一篇题解。

看完数据范围，很容易想到这题可以用搜索水过去。

这里本蒟蒻使用的是DFS来进行模拟，详细请看代码。

本题解适合跟本蒟蒻一样的初学者食用，dalao请略过

```cpp
#include <cstdio>
#include <cstring>
int n,k,T,a[220],cnt;
bool vis[220];//多开点不会有错,a数组存储水龙头位置，vis数组存储某位置是否被浇灌过
void DFS(int t)//参数是时间
{
	for(int i=1;i<=k;i++)//枚举水龙头
	{
		if(a[i]-t+1>0&&a[i]-t+1<=n)//如果本次水流达到的位置不越界
			if(!vis[a[i]-t+1])//且没有被浇灌过
			{
				vis[a[i]-t+1]=1;//标记
				cnt++;//记录下来已经被浇灌的格子数
			}
		if(a[i]+t-1>0&&a[i]+t-1<=n)//同理
			if(!vis[a[i]+t-1])
			{
				vis[a[i]+t-1]=1;
				cnt++;
			}
	}
	if(cnt==n){printf("%d\n",t);return;}//如果n个格子都被浇灌,输出此时的t,返回
	DFS(t+1);//没有返回,证明还需继续浇灌,搜索下一秒
}
int main()
{
	scanf("%d",&T);
	while(T--)//等效于while(T!=0){...;T--}
	{
		scanf("%d%d",&n,&k);
        for(int i=1;i<=k;i++)
        	scanf("%d",&a[i]);
        cnt=0;
        memset(vis,0,sizeof vis);//初始化一下
        DFS(1);//搜索第一秒
	}
	return 0;
}
```


---

## 作者：2132B (赞：3)

### 题目剖析

每个水龙头浇灌速度是一样的，只是每两个水龙头之间的距离和最左水龙头，最右水龙头决定了时间长短！

因此，如图

![](https://cdn.luogu.com.cn/upload/image_hosting/kv0u704n.png)

$AC$段只能靠$C$来浇灌，$CD$可以靠$C,D$一起浇灌........$FB$只能靠$B$点

所以除开头结尾，其余段时间:距离/2+1（第1秒不动

开头结尾时间：距离+1

### $code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, m, x[550], maxx, lef;
int main()
{
	cin >> m;//样例组数
	while (m--)//另一种循环写法
	{
        cin >> n >> k >> x[1];
        maxx = x[1];//开头（这里其实是maxx = max(maxx, lef);但可以简化
        for (int i = 2;i <= k;i++)
        {
            cin >> x[i];
            maxx = max(maxx, (x[i] - x[i - 1]) / 2 + 1);//除开头结尾情况
        }
        maxx = max(maxx, n - x[1] + 1);//结尾
        cout << maxx << endl;
	}
	return 0;
}
```


---

## 作者：LordLaffey (赞：3)

~~蒟蒻对自己拙劣的代码感到较为满意，发篇题解抒发感慨~~

# 正文
这道题由于数据的原因，貌似完全可以用搜索水过去，这里我用的bfs  

解释都在代码里

### 一定不要忘把队列清空！！！
###### （我在这卡了20min）小声bb

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int a[10000];
bool have[10000];           //是否被水浇过
int n,k;
int ans;

struct node{

    int l,r,t;              //当前水龙头在第t秒需要交的格子

};
queue<node> q;

node pu(int _l,int _r,int _t){
	
	node a;
	a.l=_l;
	a.r=_r;
	a.t=_t;
	return a;
}                       //一个比较稳得赋值方法(by 某机房dark佬

void bfs(int k){

	while(!q.empty())
		q.pop();        //warning 不要忘了清空 

    int tot=0;          //已经浇了多少个格子
    for(int i=1;i<=k;i++)
        q.push(pu(a[i],a[i],0));    //把每个水龙头放入队列
    
    while(!q.empty())
    {
        node x=q.front();
        q.pop();

		if(x.l<=0&&x.r>n)
			continue;           //如果已经流出花园

        if(x.l>0&&!have[x.l])
            have[x.l]=true,tot++;       //左边要浇的格子
        if(x.r<=n&&!have[x.r])
            have[x.r]=true,tot++;       //右边，同上
        
        if(tot==n)
        {
        	ans=x.t+1;
        	return ;
        }                       //如果都浇完了

        q.push(pu(x.l-1,x.r+1,x.t+1));  //左端点向左移，右端点向右移，时间+1
    }

}

int main(){

    int t;
    scanf("%d",&t);             //t个数据

    for(int i=1;i<=t;i++)
    {
    	memset(have,false,sizeof(have));    //初始化
        scanf("%d%d",&n,&k);

        for(int j=1;j<=k;j++)
            scanf("%d",&a[j]);
        
        bfs(k);
        printf("%d\n",ans);
    }

    return 0;

}//完结撒花qwq
```


---

## 作者：FP·荷兰猪 (赞：3)

首先把水龙头所在的位置设成1，其余的设成0.再枚举浇灌的时间，被浇过的地方都设成1,所有都是1时结束。
上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int n;
    cin>>n;
    int i,s,x,j,c,p,h,cnt;
    for (i=1;i<=n;i++)
    {
    	cin>>s>>x;
    	int f[s+1],t[x+1],a[s+1];//f数组为标记数组
    	for (j=1;j<=s;j++)
    	{
    		f[j]=0;//没有水龙头的位置设成1
    	}
    	for (j=1;j<=x;j++)
    	{
    		cin>>t[j];
    		f[t[j]]=1;//把水龙头所在的位置设成1
    	}
    	c=0;
    	p=0;
    	h=0;
    	for (j=1;j<=s;j++)
		{
			if (f[j]==0)
			{
				p=1;
			}
		}
		if (p==0)
		{
			h=1;
		}
    	while (p==1)
		{
			p=0;
			c++;//c表示时间
			cnt=0;
			for (j=1;j<=s;j++)
			{
				if (f[j]==1)
				{
					cnt++;
					a[cnt]=j;
				}
			}
			for (j=1;j<=cnt;j++)
			{
				f[a[j]+1]=1;
				f[a[j]-1]=1;
			}
			for (j=1;j<=s;j++)
			{
				if (f[j]==0)
				{
					p=1;
				}
			}
		}
		if (h==1)
		{
			cout<<"1"<<endl;//如果全都是水龙头，直接输出1
		}
		else
		{
			cout<<c+1<<endl;//否则输出时间+1
		}
    }
    return 0;
}
```

---

## 作者：Great_Influence (赞：2)

这是CF的A题，应该体现手速，代码量应该尽量短。

可以发现，答案就是

$\max\{p[1],n-p[k]+1,\frac{p[i]-p[i+1]}{2}(2<=i<=k-1)\}$

直接一遍扫。

代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x){
	T s=0,f=1;char k=getchar();
	while(!isdigit(k)&&k^'-')k=getchar();
	if(!isdigit(k)){f=-1;k=getchar();}
	while(isdigit(k)){s=s*10+(k^48);k=getchar();}
	x=s*f;
}
void file(void){
	#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	#endif
}
const int MAXN=333;
#define Chkmax(a,b) a=a>b?a:b
static int p[MAXN],n,k;
inline void init()
{
    read(n);read(k);
    Rep(i,1,k)read(p[i]);
    sort(p+1,p+k+1);
}
inline void solve()
{
    static int ans;ans=max(p[1],n-p[k]+1);
    Rep(i,1,k-1)Chkmax(ans,(p[i+1]-p[i])/2+1);
    printf("%d\n",ans);
}
int main(void){
	file();
    static int _;
    read(_);
    while(_--)
    init(),
    solve();
	return 0;
}

```

---

## 作者：胡金梁 (赞：1)

直接BFS，先把每个水龙头的位置入队，时间也入队，每个水龙头位置标记为浇过，接着再向两边拓展状态，然后还有不知道的自己理解代码，不要抄袭。
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[201],flag[201];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(flag,0,sizeof(flag));	
		int n,k,sum=0,ans=-1;
		cin>>n>>k;
		queue<int>w,s;
		for(int i=1;i<=k;i++)
		{
			cin>>a[i];
			w.push(a[i]);
			s.push(1);
			flag[a[i]]=1;
			sum++;
		}
		while(!w.empty())
		{
			int dw=w.front(),ds=s.front();
			w.pop();
			s.pop();
			ans=max(ans,ds);
			if(dw-1>0&&!flag[dw-1])
			{
				w.push(dw-1);
				s.push(ds+1);
				flag[dw-1]=1;
			}
			if(dw+1<=n&&!flag[dw+1])
			{
				w.push(dw+1);
				s.push(ds+1);
				flag[dw+1]=1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：sunyizhe (赞：0)

这题是个 BFS 好题！开始吧！

## 一、题意

有个长度为 $n$ 的花园和 $k$ 个水龙头。每个水龙头在第 $t$ 秒时可以灌溉前 $t-1$ 个格子与后 $t-1$ 个格子。问最少要多少秒才能灌溉到整个花园。

## 二、数据范围

- 有 $t$ 组数据。

- 数据范围：$1 \le k \le n \le 200$。

## 三、思路

这里定义 $vis$ 数组表示是否被灌溉，$true$ 表示灌溉过，$false$ 表示没有灌溉。这里要注意，因为有多组数据，所以每次必须初始化 $vis$ 数组。

接下来我们开始进行广度优先搜索。这里把水龙头看成只能灌溉到它左边的和右边的**各一个**格子。灌溉后，将它左边的和右边的位置建一个水龙头。先把样例给的水龙头入队列，同时记录该格被灌溉，过了一秒。出队头时，把 $ans$（存储答案，先初始化为 $-1$）与队头元素的时间取较大者，然后扩展。最后输出 $ans$。

## 四、代码

任何问题结合代码来看。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=210;
struct Node{
	int dis,s;//位置和时间
};
int n,k;
bool vis[N];
int bfs()
{
	queue<Node> q;
	for(int i=1;i<=k;i++)//将水龙头进队列
	{
		int x;
		scanf("%d",&x);
		Node t;
		t.dis=x;//在第x格位置
		t.s=1;//时间为1秒
		vis[x]=true;//灌溉过了
		q.push(t);
	}
	int ans=-1;//初始化为极小值
	while(!q.empty())
	{
		Node t=q.front();
		q.pop();
		ans=max(ans,t.s);//取较大者
		if(t.dis+1<=n&&!vis[t.dis+1])//向右扩展
		{
			Node tmp;
			tmp.dis=t.dis+1;
			tmp.s=t.s+1;
			vis[tmp.dis]=true;
			q.push(tmp);
		}
		if(t.dis-1>0&&!vis[t.dis-1])//向左扩展
		{
			Node tmp;
			tmp.dis=t.dis-1;
			tmp.s=t.s+1;
			vis[tmp.dis]=true;
			q.push(tmp);
		}
	}
	return ans;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(vis,false,sizeof(false));
		scanf("%d%d",&n,&k);
		printf("%d\n",bfs());
	}
	return 0;
}
```


---

## 作者：Qiancy1427 (赞：0)

## 暴力搜索方法
很多大佬都在用 BFS 和队列，还要很多大佬在用数学证明，其实这个蒟蒻认为没那么麻烦。

~~先声明一下，我不是不会 BFS~~

### 思路
有 $k$ 个水龙头，每一轮让这 $k$ 个水龙头都浇一遍。

如果没有被浇过，那么浇了的地方 $+1$，当这个数量达到了 $n$，当前浇过的次数就是答案。

~~很简单对吧，但是这个蒟蒻把变量搞错了，挂了好几次。~~

### 核心代码
```cpp
int bfs(){	//别管它，就是看了一下算法标签 
	memset(book,0,sizeof(book));	//每次开始前要重置 
	int cnt=0,ans=0;	//分别记录浇过了几块地和时间 
	while(cnt<n){
		ans++;	//每次加一 
		for(int i=1;i<=k;i++){
			if(book[s[i]-ans+1]==0&&s[i]-ans+1>0&&s[i]-ans+1<=n){	//前t-1个点 
				cnt++;	//加上 
				book[s[i]-ans+1]=1;	//标记 
			}
			if(book[s[i]+ans-1]==0&&s[i]+ans-1>0&&s[i]+ans-1<=n){	//后t-1个点（同上） 
				cnt++;
				book[s[i]+ans-1]=1;
			}
		}
	}
	return ans;	//最终答案 
}
```
### 全部代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;	//t,n,k同题目
int s[205],book[205];	//s记录水龙头的位置 
int bfs(){ 
	memset(book,0,sizeof(book));
	int cnt=0,ans=0;
	while(cnt<n){
		ans++;
		for(int i=1;i<=k;i++){
			if(book[s[i]-ans+1]==0&&s[i]-ans+1>0&&s[i]-ans+1<=n){
				cnt++;
				book[s[i]-ans+1]=1; 
			}
			if(book[s[i]+ans-1]==0&&s[i]+ans-1>0&&s[i]+ans-1<=n){ 
				cnt++;
				book[s[i]+ans-1]=1;
			}
		}
	}
	return ans; 
}
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n>>k;
		memset(s,0,sizeof(s));	//在每次开始前水龙头要初始化 
		for(int j=1;j<=k;j++){
			cin>>s[j];
		}
		cout<<bfs()<<endl;
	}
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

设 $garden[i]$ 为第 $i$ 个方块的浇水所需时间。

本题可以在每次读入水龙头位置 $x$ 时，可以先把 $garden[x]$ 设为 $1$，然后遍历整个 $garden$ 数组，如果 $garden[i]<abs(x-i)+1$，那么就把 $garden[i]$ 更新为 $abs(x-i)+1$。

最后，输出 $garden$ 的最大值。

时间复杂度是 $O(t\times k\times n^2+n)$，在最坏情况下（$t=k=n=200$），时间复杂度是 $O(8000200)$，也不算太大。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
int main()
{
	int t;
	scanf("%d",&t);
	for(int time=1;time<=t;time++)
	{
		int n,k;
		int garden[205];
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)//初始化。思考：为什么garden要被初始化为那么大的数值？
		{
			garden[i]=387836;
		}
		for(int i=1;i<=k;i++)
		{
			int x;
			scanf("%d",&x);
			garden[x]=1;//水龙头所在位置，浇水时间为1。
			for(int j=1;j<x;j++)//水龙头所在位置之前。
			{
				if(garden[j]>x-j+1)
				{
					garden[j]=x-j+1;
				}
			}
			for(int j=x+1;j<=n;j++)//水龙头所在位置之后。
			{
				if(garden[j]>j-x+1)
				{
					garden[j]=j-x+1;
				}
			}
		}
		int ans=0;
		for(int i=1;i<=n;i++)//遍历，求最大值。
		{
			if(garden[i]>ans)
			{
				ans=garden[i];
			}
		}
		printf("%d\n",ans);//输出。
	}
	return 0;//完结撒花！
}

```

### 三、思考题答案

不难理解，因为在读入水龙头位置时取最小值，如果初始化的值比真实情况还要小，就有可能出现错误的答案。

### 四、后记

记录：<https://www.luogu.com.cn/record/51525485>。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

完全没必要用BFS算法，暴力一下就行了。

我们要创一个数组 $g$。其中，$g_i$ 代表浇到点 $i$ 时所需要花费的最少时间。注意，刚开始时它要初始化一个比 $200$ 大的数，比如我用 $2021$。

我们可以一个个输入水龙头位置，以此为中心，计算这个水龙头的水到达每一个点的时间，再取较小的那一个。

最后，遍历整个数组，将里面的最大值 $ans$ 输出。

时间复杂度为 $O(t·n·k)$，在最坏的情况下，$t=n=k=200$，也能够过。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
const int max_n=200;
const int max_num=2021;//设一个很大的值用于初始化
int t;
int n;//花园长度
int g[max_n+2];//花园
int k;//水龙头数量
int tag;//水龙头
int ans;
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;++i){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i){
			g[i]=max_num;
		}
		//核心部分
		for(int i=1;i<=k;++i){
			scanf("%d",&tag);
			for(int j=tag;j>=1;--j){
				if(g[j]>tag-j+1){
					g[j]=tag-j+1;
				}
			}
			for(int j=tag;j<=n;++j){
				if(g[j]>j-tag+1){
					g[j]=j-tag+1;
				}
			}
		}
		ans=0;
		for(int i=1;i<=n;++i){
			if(ans<g[i]){
				ans=g[i];
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/51479492)

By **dengziyue**


---

## 作者：AkiwaZawa (赞：0)

## 暴力BFS
详情注释请见代码
```
#include<bits/stdc++.h>
using namespace std;
bool vis[205];//是否浏览过花台 
int ans,t[205];//流到花台i所需要的时间为t[i]
int n,k,l;
queue<int> Q;
void BFsearch(int x)
{
	if(Q.empty()==1) return ;
	int temp=Q.front();
	Q.pop();
	ans=max(ans,t[temp]);
	if(temp-1>=1&&vis[temp-1]==0)
	{
		vis[temp-1]=1;
		t[temp-1]=t[temp]+1;
		Q.push(temp-1);
	}
	if(temp+1<=n&&vis[temp+1]==0)
	{
		vis[temp+1]=1;
		t[temp+1]=t[temp]+1;
		Q.push(temp+1);
	}
	BFsearch(Q.front());
}
 
int main()
{
	int test;
	cin>>test;
	while(test--)
	{
		memset(vis,0,sizeof(vis));
		memset(t,0,sizeof(t));
		while(!Q.empty()) Q.pop();
		ans=-1;
		cin>>n>>k;
		for(int i=1;i<=k;i++)
		{
			cin>>l;// 喷头的位置 
			t[l]=1;//需要1时间 
			vis[l]=1;
			Q.push(l);
		}
		BFsearch(Q.front());
		cout<<ans<<endl;
	}
	return 0;
} 
```


---

