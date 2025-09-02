# Servers

## 题目描述

There are $ n $ servers in a laboratory, each of them can perform tasks. Each server has a unique id — integer from $ 1 $ to $ n $ .

It is known that during the day $ q $ tasks will come, the $ i $ -th of them is characterized with three integers: $ t_{i} $ — the moment in seconds in which the task will come, $ k_{i} $ — the number of servers needed to perform it, and $ d_{i} $ — the time needed to perform this task in seconds. All $ t_{i} $ are distinct.

To perform the $ i $ -th task you need $ k_{i} $ servers which are unoccupied in the second $ t_{i} $ . After the servers begin to perform the task, each of them will be busy over the next $ d_{i} $ seconds. Thus, they will be busy in seconds $ t_{i},t_{i}+1,...,t_{i}+d_{i}-1 $ . For performing the task, $ k_{i} $ servers with the smallest ids will be chosen from all the unoccupied servers. If in the second $ t_{i} $ there are not enough unoccupied servers, the task is ignored.

Write the program that determines which tasks will be performed and which will be ignored.

## 说明/提示

In the first example in the second $ 1 $ the first task will come, it will be performed on the servers with ids $ 1 $ , $ 2 $ and $ 3 $ (the sum of the ids equals $ 6 $ ) during two seconds. In the second $ 2 $ the second task will come, it will be ignored, because only the server $ 4 $ will be unoccupied at that second. In the second $ 3 $ the third task will come. By this time, servers with the ids $ 1 $ , $ 2 $ and $ 3 $ will be unoccupied again, so the third task will be done on all the servers with the ids $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ (the sum of the ids is $ 10 $ ).

In the second example in the second $ 3 $ the first task will come, it will be performed on the servers with ids $ 1 $ and $ 2 $ (the sum of the ids is $ 3 $ ) during three seconds. In the second $ 5 $ the second task will come, it will be performed on the server $ 3 $ , because the first two servers will be busy performing the first task.

## 样例 #1

### 输入

```
4 3
1 3 2
2 2 1
3 4 3
```

### 输出

```
6
-1
10
```

## 样例 #2

### 输入

```
3 2
3 2 3
5 1 2
```

### 输出

```
3
3
```

## 样例 #3

### 输入

```
8 6
1 3 20
4 2 1
6 5 5
10 1 1
15 3 6
21 8 8
```

### 输出

```
6
9
30
-1
15
36
```

# 题解

## 作者：封禁用户 (赞：2)

# 0.前言
题目链接：http://codeforces.com/contest/747/problem/C

题目大意：
 $n$ 个服务器，序号从 $1$ 到 $n$，有 $q$ 个任务；
每个任务在 $t[i]$ 秒的时间到，需要 $k[i]$ 台服务器，每台占用 $d[i]$ 秒的时间；
询问：当每个任务到达时，是否有足够的机器完成任务；
如果可以完成，则选择序号最小的机器，输出机器的序号和；
如果不能完成，输出 $-1$。
# 1.样例解释
```
 input
 4 3
 1 3 2
 2 2 1
 3 4 3
 output
 6
 -1
 10
```
 - 第一个任务在第 $1$ 秒到达，所有机器空闲，选择 $1,2,3$ 号机器，所以输出 $6$；
 - 第二个任务在第 $2$ 秒到达，这时空闲的机器只有机器 $4$，任务无法完成，输出 $-1$；
 - 第三个任务在第 $3$ 秒到达，所有机器都空闲，选择 $1,2,3,4$ 号机器，输出 $10$。


# 2.解析：
直接说做法吧：

一维数组和结构体表示机器的序号和空闲时间。

从号最小的机器开始遍历，看是否有符合条件的机器。

若符合，就将机器的空闲时间转为完成时间。
# 3.code
```cpp
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int value, pos;
    bool operator<(const Node &tmp) const{
        if (tmp.pos != pos) return pos > tmp.pos;
        else return value > tmp.value;
    };
    Node(int x, int y):value(x), pos(y){};
    Node(){};
}node[114514];
char a[114514];

int main(){
    int n,q;
    cin>>n>>q;
    vector<Node> s(n);
    for (int i = 0; i < n; ++i) s[i] = Node(i + 1, 0);
    while (q--) {
        int c, need, t;
        scanf("%d%d%d", &c, &need, &t);
        vector<Node> re;
        for (int i = 0; i < s.size() && re.size() < need; ++i){
            if (s[i].pos <= c) re.push_back(s[i]);
        }
        if (re.size() == need) {
            int ans = 0;
            for (int i = 0; i < re.size(); ++i) {
                ans += re[i].value;
                re[i].pos = c + t;
            }
            cout << ans << endl;
        }
        else  cout << -1 << endl;
        for (int i = 0; i < re.size(); ++i) s[re[i].value - 1].pos = re[i].pos;
    }
    return 0;
}

```
最后求个关注 qwq！！！

---

## 作者：XCH_0803 (赞：1)

# 题意

有 $n$ 个服务器，有 $q$ 个问题，接下来 $q$ 行会出现三个数, $t$ （在时刻 $t$ 处出现问题）、$k$（需要 $k$ 个服务器处理问题）、$d$（需要处理 $d$ 秒），要求求出是否能在 $t$ 时刻执行问题。若能，输出服务器编号之和，否则输出 $-1$ 。


# 思路

题目有多组数据，且数据之间有关联性，所以存在一个数据状态更新的问题。

接下来就是简单的模拟。建立一个数组 $a$ 以记录服务器可用的时间的时刻，即在 $x$ 秒的时候及以后可，然后判断，更新。

话不多说，上代码

```c
#include<bits/stdc++.h>
using namespace std;
int a[200];
int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=q;i++){
        int t,k,d;
        cin>>t>>k>>d;
        int t1=t+d;//记录下一轮个别服务器可用的时间坐标
        int cnt=0,sum=0;
        for(int j=1;j<=n;j++){
            if(a[j]<=t){//表示当前a[j]可用
                cnt++;
				sum+=j;
                if(cnt>=k){
					break;//数够服务器数量跳出
                }
            }
        }
        if(cnt<k){
			cout<<"-1"<<endl;
        }
        else{
            for(int j=1;j<=n;j++){//对下轮服务器数据进行更新
                if(a[j]<=t&&cnt>0){
                    a[j]=t1;
                    cnt--;
                }
            }
            cout<<sum<<endl;
        }
    }
    return 0;
}
```


---

## 作者：Alexandra (赞：0)

## 题目分析
一共有 $n$ 台机器，令 $a_j$ 为第 $j$ 台机器当前工作的最后时间。一共 $q$ 个询问，针对每一个询问，遍历当前所有的机器，如果这台机器在这个任务到达前结束工作，即 $a_j < k_i$，那么它就可以执行给定的任务。统计这样的机器的个数。如果大于 $k_i$，说明这个任务可以被完成，我们就从前向后更新 $a_j$，并统计序号和。反之则输出 $-1$。  

分析一下时间复杂度，枚举 $q$ 个询问，$q$ 最大可以取到 $10^5$。在每一个询问里枚举 $n$ 台机器，最多有 $10^3$ 台机器，所以最终复杂度为 $O(nq)$，常数小点是能过的。


#### 注意：
1. 更新 $a_j$ 时不应将 $a_j$ 直接加当前的 $d_i$，而是改为 $t_i+d_i-1$，因为当前的 $a_j$ 可能小于 $t_i$。  
2. 如果这一轮的满足要求的机器的个数小于 $k_i$，应该直接输出 $-1$，避免重复更新。

## 代码
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 110
long long n,q,a[N];
inline long long read()
{
	long long wjl=0,jia=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')jia*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		wjl=(wjl<<1)+(wjl<<3)+(ch^48);
		ch=getchar();
	}
	return wjl*jia;
}
int main ()
{
	n=read(),q=read();
	for(long long i=1;i<=q;i++)//1e5
	{
		long long t=read(),k=read(),d=read();
		long long cnt=0,ans=0;
		for(long long j=1;j<=n;j++)
		{
			if(a[j]<t)cnt++;
			if(cnt>=k)break;
		}
		if(cnt>=k)
		{
			for(long long j=1;j<=n;j++)
			{
				if(a[j]<t)a[j]=t+d-1,ans+=j,cnt--;
				if(cnt==0)break;
			}
			printf("%lld\n",ans);
		}
		else printf("-1\n");
	}
	return 0;
}
```


---

## 作者：nj_peak (赞：0)

思路：

说实话，这道题只需要简简单单的想出思路就可以正确了。

首先，我们创建一个一维数组来存储机器的序号，然后进行简简单单的模拟后就可以得出代码了：

```cpp
#include<bits/stdc++.h>    
using namespace std;
int vis[1005],x,y,f=0,ans=0;
int main()
{
    scanf("%d%d",&x,&y);
    for(int i=1;i<=y;++i)   
	{
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        int h=a+c;    
        for(int j=1;j<=x;++j)
		{
            if(vis[j]<=a)
			{
                f++;
				ans=ans+j;
                if(f>=b)
				break;
            }
        }
        if(f<b)
		printf("-1\n");
        else
		{
            for(int j=1;j<=x;++j)
			{
                if(vis[j]<=a && f>0)
				{
                    vis[j]=h;
                    f--;
                }
            }
            printf("%d\n",ans);
        }
    }
}

```
但我们提交后发现：出错了！！！

怎么办呢？原来我们设的 ans 设在了外面，所以导致了累加。

正确代码：

```cpp
#include<bits/stdc++.h>   //万能头 
using namespace std;
int vis[1005],x,y,f=0;
int main()
{
    scanf("%d%d",&x,&y);
    for(int i=1;i<=y;++i)    //++i比i++更快 
	{
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        int h=a+c;
        int ans=0;         //一定要在里面设 ans=0; 不然输出时就会累加！ 
        for(int j=1;j<=x;++j)
		{
            if(vis[j]<=a)
			{
                f++;
				ans=ans+j;
                if(f>=b)
				break;
            }
        }
        if(f<b)
		printf("-1\n");
        else
		{
            for(int j=1;j<=x;++j)
			{
                if(vis[j]<=a && f>0)
				{
                    vis[j]=h;
                    f--;
                }
            }
            printf("%d\n",ans);
        }
    }
}

```


---

## 作者：菲斯斯夫斯基 (赞：0)

## CF747C Servers 题解

简单的一道**模拟题**。

用 $a_i$ 来存下第 $i$ 台机子任务结束的时间，每次有新任务的时候从 $1$ 到 $n$ 枚举每一个机子是否可以接受当前的任务，如果可以，那么就用这台机子。

我使用了 $f$ 数组来存下需要使用的机子，这样在后面的处理会方便一点。

你也可以使用 `vector` 来存，这样似乎更加方便。但是 $n\le100$，基本上没有什么区别。

**更详细的过程见代码注释。**

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int f[110];
struct ccf
{
	int t,k,d;
}a[110];
int main()
{
	cin>>n>>t;
	while(t--)
	{
		int l=0,ans=0;
		ccf x;
		cin>>x.t>>x.k>>x.d;
		for(int i=1;i<=n;i++)
		{
			if(a[i].t>x.t)continue;//该机子无法接受任务 
			if(x.k==0)break;//机子数量够了就直接退出 
			f[++l]=i,x.k--,ans+=i;//存下答案 
		}
		if(x.k!=0)cout<<"-1\n";//没有机子够用就输出-1
		else
		{
			for(int i=1;i<=l;i++)
				a[f[i]].t=x.t+x.d;//更新机子任务结束时间 
			cout<<ans<<endl;
		}
	}
	return 0;
}

```

---

## 作者：IcyFoxer_XZY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF747C)

### 分析

题目要求我们求出当有足够机器完成任务时序号最小机器的机器序号和，那么我们可以定义一个数组 $w[i]$ 来存储编号 $i$ 服务器结束最后一次任务的时间。当 $w[i]$ 小于 $t$ 时，该服务器可以执行任务。因此我们就可以得出可以执行任务的数量 $cnt$，当 $cnt$ 小于 $k$ 时，输出 $-1$，否则输出序号和并把 $w$ 数组重新赋值。

### code:

```cpp
#include<cstdio>
int n,q,t,k,d,w[105],s,cnt;
int main(){
	scanf("%d%d",&n,&q);
	while(q--){
		s=0,cnt=0;//cnt表示机器数量，s表示序号和 
		scanf("%d%d%d",&t,&k,&d);
		for(register int i=1;i<=n&&cnt<k;++i)
			if(w[i]<t){//可以执行任务 
				++cnt;//机器数量+1 
				s+=i;
			}	
		if(cnt<k)puts("-1");//不能完成输出-1 
		else{
			printf("%d\n",s);//否则输出序号和 
			for(register int i=1;i<=n&&cnt;++i)
				if(w[i]<t){//可以执行任务 
					--cnt;
					w[i]=t+d-1;//重新赋值 
				}
		}
	}
	return 0;
}
```
Bye！

---

## 作者：As_Snow (赞：0)

### 思路
对于每一次去执行任务，都把每一个点遍历一遍。
用 $endt_i$ 记录编号为 $i$ 的服务器执行的最后一次任务的结束时间，如果当前的 $t$ 大于 $endt_i$，说明 $i$ 号服务器可以执行当前任务。
如果找到了足够的服务器来执行任务，输出这些服务器编号之和，并更新它们的 $endt$。

## Code

```
#include<bits/stdc++.h>
using namespace std;
const int N = 1e2+12;
int n,q,t,k,d;
int endt[N];
signed main(){
	scanf("%d%d",&n,&q);
	while(q--){
		int sum=0,num=0;
		scanf("%d%d%d",&t,&k,&d);
		for(int i=1;i<=n&&num<k;i++)
			if(endt[i]<t)
				num++,sum+=i;
		if(num<k)printf("-1\n");
		else{
			printf("%d\n",sum);
			for(int i=1;i<=n&&num;i++)
				if(endt[i]<t)
					num--,endt[i]=t+d-1;
		}
	}
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

第一步：

输入 $n,q$，循环 $q$ 次，在循环中输入 $t,k,d$，不需要用数组，定义一个 $a$ 数组，$a_i$ 表示第 $i$ 台服务器再次空闲的时间。

------------

第二步：

对于每一组询问，定义变量 $sum$ 和 $num$。$sum$ 记录目前可以选择的服务器序号和，$num$ 表示目前已选的服务器数量和。

再进行一次循环，在循环中去判断是否可选。

判断条件：
1. $i$ 服务器空闲。
2. 数量不够（$k \neq num$）。

若符合条件,累加序号，选择服务器数量加 $1$。

------------

第三步：

若循环结束后，$num$ 的值与 $k$ 相等，输出 $sum$，并更新重新进入工作状态后的服务器的下次空闲时间，否则输出 $-1$。

------------

下面附上 AC 代码！！！

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
using namespace std;
int n,q,t,k,d,a[N];//定义 
signed main()
{
	//第一步 
	cin>>n>>q;
	rep1(i,1,q)
	{
		cin>>t>>k>>d;
		//第二步 
		int sum=0,num=0;
		rep1(i,1,n) 
		{
			if(a[i]<=t&&num<k)//判断是否可选 
			{
				sum+=i;//序号累加 
				++num;//个数累加 
			}
		}
		if(num!=k)//判断是否能完成任务 
		{
			puts("-1");//输出 
			continue;//跳转至下一次循环 
		}
		//第三步 
		num=0;
		rep1(i,1,n) 
		{
			if(a[i]<=t&&num<k) 
			{
				a[i]=t+d;//更新下一次空闲时间 
				++num;//个数累加 
			}
		}
		cout<<sum<<endl;//输出 
	}
	return 0;//收场 
}
```

---

## 作者：AlicX (赞：0)

#### 前言：拿到此题，只要你静下心来读题。就会发现：此题是一道模拟题。

 前置知识：[map 的用法](https://blog.csdn.net/weixin_43719622/article/details/90274130?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166538891016781432984269%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166538891016781432984269&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-90274130-null-null.142^v52^control,201^v3^control&utm_term=map%E7%9A%84%E7%94%A8%E6%B3%95&spm=1018.2226.3001.4187)

### 具体思路：

本蒟蒻想的做法是用 map 存储每个机器工作的结束时间，在读入时，循环遍历每个机器，如果这个机器的工作时间 $\leq $ 现在的任务的开始时间。我们就可以采用这台机器（因为要求编号最小，从前往后遍历时一旦有了足够的机器就退出循环），在代码里面用一个计数变量记录机器的数量即可，当这个计数变量的值等于要选的机器数量，就退出循环，如果最后没有要的机器的数量那么多，就输出 $-1$，否则再遍历一遍累加编号和，输出编号和，并把选中的机器的工作时间更新为做完这次工作的时间。
那么我们这道题就完成了。

### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=110; 
int n,m;
map<int,int> mp;//用来存储每个机器工作时间的 map 
signed main(){
	cin>>n>>m;
	while(m--){
		int t,k,d;
		cin>>t>>k>>d;//读入 
		int sum=0,cnt=0;
		for(int i=1;i<=n;i++) if(mp[i]<=t&&cnt<k) sum+=i,cnt++;//判断，如果这台机器的工作时间是小于等于任务的开始时间，就采用，cnt记录有了多少台机器
		if(cnt<k) cout<<-1<<endl;//判断机器的数量是否足够 
		else{
			cnt=0;
			for(int i=1;i<=n;i++) if(mp[i]<=t&&cnt<k) mp[i]=t+d,cnt++;//更新工作时间 
			cout<<sum<<endl;
		}
	}
	return 0;//Bye~
}
```

$$ Thanks  $$


---

## 作者：Limury (赞：0)

### 题意

给定 $n$ 个服务器，$q$ 个任务，每个任务都有开始时间，需要服务器的个数，任务完成需要花的时间，求每个任务完成所需要的服务器的编号和最小值。

### 思路

可观察数据范围，我们发现 $O(qn^2)$ 朴素的算法是过不去的，题目又是关于最小值，于是很自然想到了优先队列优化。 我们考虑使用一个以编号靠前排的优先队列，一个以结束时间早靠前的优先队列，分别维护进行操作。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
   int t,p;
   bool operator<(const node& a)const{
       return a.t<t;
   }
}x;

int n,q,k,t,d,l;
priority_queue<int,vector<int>,greater<int> > qi;
priority_queue<node> qj;


int main(){
	cin>>n>>q;
    for(int i=1;i<=n;i++){
    	qi.push(i);
	}
    while(q--){
    	cin>>t>>k>>d;
        while(!qj.empty()){
            x=qj.top();
            if(x.t>t){
            	break;
			}
            qj.pop();
            qi.push(x.p);
        }
        l=qi.size();
        if(l<k){
        	printf("-1\n");
		}
        else{
            int ans=0;
            while(k--){
                int y=qi.top();
                qi.pop();
                x.t=t+d;
                x.p=y;
                ans+=y;
                qj.push(x);
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}

```


---

## 作者：Keroshi (赞：0)

# 题目分析   
题目需要求将要执行任务的 $id$ 总和，   
那么可以用一个数组 $w$ 来存储每个服务器任务的截至时间，  
如果没有任务就设为 $0$ 并每次更新。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=105;
int n,q,t,k,d;
int w[N];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d%d",&t,&k,&d);
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(w[i]<=t) w[i]=0; // 任务已经完成
            if(w[i]==0) cnt++; // 记录是否有足够的服务器
        }
        if(cnt<k) {
            printf("-1\n");
            continue;
        }
        cnt=0;
        int res=0;
        for(int i=1;i<=n;i++){
            if(w[i]==0){
                cnt++;
                w[i]=t+d; // 更新时间
                res+=i;
            }
            if(cnt==k) break;
        }
        printf("%d\n",res);
    }
    return 0;
}
```

---

