# Replicating Processes

## 题目描述

A Large Software Company develops its own social network. Analysts have found that during the holidays, major sporting events and other significant events users begin to enter the network more frequently, resulting in great load increase on the infrastructure.

As part of this task, we assume that the social network is $ 4n $ processes running on the $ n $ servers. All servers are absolutely identical machines, each of which has a volume of RAM of $ 1 $ GB = $ 1024 $ MB $ ^{(1)} $ . Each process takes 100 MB of RAM on the server. At the same time, the needs of maintaining the viability of the server takes about $ 100 $ more megabytes of RAM. Thus, each server may have up to $ 9 $ different processes of social network.

Now each of the $ n $ servers is running exactly $ 4 $ processes. However, at the moment of peak load it is sometimes necessary to replicate the existing $ 4n $ processes by creating $ 8n $ new processes instead of the old ones. More formally, there is a set of replication rules, the $ i $ -th ( $ 1<=i<=4n $ ) of which has the form of $ a_{i}→(b_{i},c_{i}) $ , where $ a_{i} $ , $ b_{i} $ and $ c_{i} $ ( $ 1<=a_{i},b_{i},c_{i}<=n $ ) are the numbers of servers. This means that instead of an old process running on server $ a_{i} $ , there should appear two new copies of the process running on servers $ b_{i} $ and $ c_{i} $ . The two new replicated processes can be on the same server (i.e., $ b_{i} $ may be equal to $ c_{i} $ ) or even on the same server where the original process was (i.e. $ a_{i} $ may be equal to $ b_{i} $ or $ c_{i} $ ). During the implementation of the rule $ a_{i}→(b_{i},c_{i}) $ first the process from the server $ a_{i} $ is destroyed, then appears a process on the server $ b_{i} $ , then appears a process on the server $ c_{i} $ .

There is a set of $ 4n $ rules, destroying all the original $ 4n $ processes from $ n $ servers, and creating after their application $ 8n $ replicated processes, besides, on each of the $ n $ servers will be exactly $ 8 $ processes. However, the rules can only be applied consecutively, and therefore the amount of RAM of the servers imposes limitations on the procedure for the application of the rules.

According to this set of rules determine the order in which you want to apply all the $ 4n $ rules so that at any given time the memory of each of the servers contained at most $ 9 $ processes (old and new together), or tell that it is impossible.

## 说明/提示

 $ ^{(1)} $ To be extremely accurate, we should note that the amount of server memory is $ 1 $ GiB = $ 1024 $ MiB and processes require $ 100 $ MiB RAM where a gibibyte (GiB) is the amount of RAM of $ 2^{30} $ bytes and a mebibyte (MiB) is the amount of RAM of $ 2^{20} $ bytes.

In the first sample test the network uses two servers, each of which initially has four launched processes. In accordance with the rules of replication, each of the processes must be destroyed and twice run on another server. One of the possible answers is given in the statement: after applying rules $ 1 $ and $ 2 $ the first server will have $ 2 $ old running processes, and the second server will have $ 8 $ ( $ 4 $ old and $ 4 $ new) processes. After we apply rules $ 5 $ and $ 6 $ , both servers will have $ 6 $ running processes ( $ 2 $ old and $ 4 $ new). After we apply rules $ 3 $ and $ 7 $ , both servers will have $ 7 $ running processes ( $ 1 $ old and $ 6 $ new), and after we apply rules $ 4 $ and $ 8 $ , each server will have $ 8 $ running processes. At no time the number of processes on a single server exceeds $ 9 $ .

In the second sample test the network uses three servers. On each server, three processes are replicated into two processes on the same server, and the fourth one is replicated in one process for each of the two remaining servers. As a result of applying rules $ 2,3,4,6,7,8,10,11,12 $ each server would have $ 7 $ processes ( $ 6 $ old and $ 1 $ new), as a result of applying rules $ 1,5,9 $ each server will have $ 8 $ processes. At no time the number of processes on a single server exceeds $ 9 $ .

## 样例 #1

### 输入

```
2
1 2 2
1 2 2
1 2 2
1 2 2
2 1 1
2 1 1
2 1 1
2 1 1
```

### 输出

```
YES
1 2 5 6 3 7 4 8
```

## 样例 #2

### 输入

```
3
1 2 3
1 1 1
1 1 1
1 1 1
2 1 3
2 2 2
2 2 2
2 2 2
3 1 2
3 3 3
3 3 3
3 3 3
```

### 输出

```
YES
2 3 4 6 7 8 10 11 12 1 5 9
```

# 题解

## 作者：eastcloud (赞：1)

倒着做对完了。

考虑这个题要求构造一个合法方案，那你自然会去想不合法方案长什么样，大概是类似一个几条边连着三元环的东西，然后发现这个条件非常宽松，好像随便贪贪都能做。

但是上面分析的比较抽象，一个更加具象且应该思考的点是操作性质和操作数量影响了什么，能带来什么。在这题中，加操作刚好是两个，减刚好是一个，这两个加操作每次可能带来两个 $9$，如果操作一矛盾就爆了，这让我们没法乱搞，那怎么办？时光倒流让加操作变成一个！

我们从所有数都是 $8$ 的终态开始，加边减，减边加，不难发现每次最多多出一个 $9$，只要瞄准这个 $9$ 消，最后的方案就一定合法。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 500005
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x/10)write(x/10);
    putchar(x%10+'0');
}
int f[N],vis[N],a[N],b[N],c[N];
set<int> s[N];
vector<int> ans;
void opr(int i){
    ans.push_back(i);vis[i]++;
    f[a[i]]++;f[b[i]]--;f[c[i]]--;
    s[b[i]].erase(i);s[c[i]].erase(i);
    if(f[a[i]]==9)opr(*s[a[i]].begin());
}
int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    int n=read();
    for(int i=1;i<=4*n;i++){
        a[i]=read(),b[i]=read(),c[i]=read();
        s[b[i]].insert(i);s[c[i]].insert(i);
    }
    for(int i=1;i<=n;i++)f[i]=8;
    for(int i=1;i<=4*n;i++)if(!vis[i])opr(i);
    printf("YES\n");
    reverse(ans.begin(),ans.end());
    for(auto v:ans)write(v),putchar(' ');
}
```

---

## 作者：xkcdjerry (赞：1)

先摆结论：一直维护现在的可行转移每次随便拎出来一个转移一定可以转移完所有操作。

证明如下：（感谢 Codeforces 牛人 [VastoLorde95](http://codeforces.com/profile/VastoLorde95) [提供想法](http://codeforces.com/blog/entry/19518?#comment-245502)）


> 考虑最 naive 的转移集合：每一个转移的形式均为 `A -> A,A` 且每个相同的转移均出现四次。显而易见此时有解且以任何顺序执行皆可。    
考虑将任何一个可行解中某个 `A -> X,A` 的第二个 `A` 转化为 `Y`（即改为 `A -> X,Y`），显然此时 `Y` 最后会剩余 $9$ 个且 `A` 会剩余 $7$ 个，那么为了使 `Y` 中最终剩余 $8$ 个，我们必须将某个 `Y -> Y,N` 改为 `Y -> M,N`，则此时 `M` 最后会剩余 $9$ 个，以此类推最终一定会将某个 `Z -> Z,B` 改为 `Z -> A,B` （由于只有转移到 `A` 才能使所有剩余的均为 $8$ 个而停止转移），那么显然如果先执行所有本次操作改变转移的然后再执行这次操作没有改变的转移仍然可以完成所有转移。  
易证通过有限次的上述转移可以将基本情况转移为任何符合题意（也就是可能出现）的情况，故所有符合题意可能出现的情况均有解且任意转移皆可。

（实际实现中为了实现简单采用了倒推的方法，因为如果直接模拟可能会产生两个超过 $9$）

代码：
```cpp
#include <cstdio>
#include <unordered_set>
#define set std::unordered_set
#define N 30010
int n,top;
int a[N*4],b[N*4],c[N*4];
bool vis[N*4];
int ans[N*4];
int f[N];
set<int> usable[N];
void fix(int o)
{
	//乌拉！！！
	int WuLa=*usable[o].begin();
	usable[o].erase(usable[o].begin());
	f[b[WuLa]]--,f[c[WuLa]]--,f[a[WuLa]]++;
	vis[WuLa]=true;
	ans[top++]=WuLa;
	usable[b[WuLa]].erase(WuLa);
	usable[c[WuLa]].erase(WuLa);
	if(f[a[WuLa]]==9) fix(a[WuLa]);
}
int main()
{
	scanf("%d",&n);
	const int left=n*4;
	for(int i=0;i<left;i++) scanf("%d%d%d",a+i,b+i,c+i);
	for(int i=0;i<left;i++)
	{
		//可以用来“减小”值的 
		usable[b[i]].insert(i);
		usable[c[i]].insert(i);
	}
	for(int i=1;i<=n;i++) f[i]=8;
	//从末尾开始还原
	top=0; 
	for(int i=0;i<left;i++)
	{
		if(vis[i]) continue;
		//还原操作
		f[b[i]]--,f[c[i]]--,f[a[i]]++;
		vis[i]=true;
		ans[top++]=i;
		usable[b[i]].erase(i);
		usable[c[i]].erase(i);
		if(f[a[i]]==9) fix(a[i]);
	}
	puts("YES");
	for(int i=top-1;i>=0;i--) printf("%d ",ans[i]+1);
}
```

---

