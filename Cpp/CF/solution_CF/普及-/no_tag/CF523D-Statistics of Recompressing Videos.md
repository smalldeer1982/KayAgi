# Statistics of Recompressing Videos

## 题目描述

A social network for dogs called DH (DogHouse) has $ k $ special servers to recompress uploaded videos of cute cats. After each video is uploaded, it should be recompressed on one (any) of the servers, and only after that it can be saved in the social network.

We know that each server takes one second to recompress a one minute fragment. Thus, any server takes $ m $ seconds to recompress a $ m $ minute video.

We know the time when each of the $ n $ videos were uploaded to the network (in seconds starting from the moment all servers started working). All videos appear at different moments of time and they are recompressed in the order they appear. If some video appeared at time $ s $ , then its recompressing can start at that very moment, immediately. Some videos can await recompressing when all the servers are busy. In this case, as soon as a server is available, it immediately starts recompressing another video. The videos that await recompressing go in a queue. If by the moment the videos started being recompressed some servers are available, then any of them starts recompressing the video.

For each video find the moment it stops being recompressed.

## 样例 #1

### 输入

```
3 2
1 5
2 5
3 5
```

### 输出

```
6
7
11
```

## 样例 #2

### 输入

```
6 1
1 1000000000
2 1000000000
3 1000000000
4 1000000000
5 1000000000
6 3
```

### 输出

```
1000000001
2000000001
3000000001
4000000001
5000000001
5000000004
```

# 题解

## 作者：我和鱼过不去 (赞：1)

### 思路
有 $k$ 个服务器，所以最多可以同时压缩 $k$ 个视频。  
依次读入每个视频的信息，按下面两种情况安排压缩顺序：
1. 如果有**没有正在被使用**的服务器，则安排该视频进行压缩，结束压缩的时间则是 $s + m$；
2. 如果没有可以使用的服务器，则寻找结束压缩时间最早的服务器，安排该视频在此服务器结束上一个视频后进行压缩。    

考虑使用优先队列进行模拟：  
+ 严格保证队列的元素小于等于 $k$ （有 $k$ 个服务器）；
+ 按结束压缩的时间从小到大排列，则上面情况2中，当前视频结束压缩的时间应该是  ```max(s,q.top()) + m```。  

数据有点大，记得开 long long。
### 关于优先队列
>普通的队列是一种先进先出的数据结构，元素在队列尾追加，而从队列头删除。在优先队列中，元素被赋予优先级。当访问元素时，具有最高优先级的元素最先删除。优先队列具有最高级先出的行为特征。通常采用堆数据结构来实现。  

在这道题中，我们按**从小到大**来**赋予优先级**。  
下面作个示范：
```
priority_queue<int,vector<int>,greater<int> >q; 
```
这样就得到了一个 int 类型的从小到大出队的优先队列 $q$。  
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
priority_queue<long long,vector<long long>,greater<long long> >q; 
int main()
{
      scanf("%d%d",&n,&k);
      for(int i=1;i<=n;i++)
      {
            long long s,m;
            scanf("%lld%lld",&s,&m);
            if(q.size()>=k)  //情况2 
            {
                  s = max(s,q.top()) + m;  
                  q.pop();
            }
            else s += m;   //情况1 
            q.push(s);    //将当前视频结束压缩的时间加入队列 
            printf("%lld\n",s);  //输出结束压缩的时间 
      }
      return 0;
} 
```


---

## 作者：流绪 (赞：1)

贪心模拟！

n 个任务，可以同时执行 k 个，求最优下每个任务的结束时间。

我们需要得到任务的执行顺序，需要进行排序，那么我们可以考虑用小根堆来模拟这个过程。为什么用小根堆后面会解释！

因为任务是按开始时间出现的，那么我们读入一个任务，如果队列元素没有达到 k 个，那就直接执行它，它的结束时间自然就是开始时间 + 任务需要的时间。如果队列满了，那么我们就需要等最早结束的那个任务结束了才能开始这个任务。

这时候我们的小根堆就派上用场了！我们对于每一个任务的结束时间算出来，加入堆中，这样子堆顶元素始终是最小的，即目前堆中最早结束的任务，那么就知道队列满了之后，任务的结束时间怎么算了：堆顶元素大小 + 此时要算的任务的所需时间,此时记得要弹出堆顶，因为我们这时候是认为这个任务已经执行完毕，空出位置给下一个任务了！然后模拟一遍就好啦。

下面是 AC 代码，细节注释在代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mod 1000000009
using namespace std;
priority_queue<ll,vector<ll>,greater<ll> > q;//小根堆
int main()
{
	ios::sync_with_stdio(0);
	int n,k;
	cin >> n >> k;
	for(int i=1;i<=n;i++)
	{
		ll s,m;
		cin >> s >> m;
		if(q.size()>=k)//满了之后结束时间的计算
			s = max(s,q.top())+m,q.pop();//记得弹出堆顶元素
		else
			s += m;//队列未满,直接执行任务
		cout << s << endl;输出
		q.push(s);加入队列
	}
	return 0;
} 
```


---

## 作者：Zeryboy (赞：0)

**题目分析**

你需要管理一系列服务器，它们用于重新压缩上传到社交网络的视频。每个服务器需要一定的时间重新压缩视频，这取决于视频的长度。你的任务是，给定每个视频的上传时间和长度，确定每个视频何时完成压缩。

**解题思路**

1. **服务器的初始化**：开始时，所有的服务器都是空闲的，所以我们将所有服务器的空闲时间初始化为0。

2. **处理每一个视频**：对于上传的每一个视频，我们都检查最早变空闲的服务器。

3. **决定压缩的开始时间**：视频可以在它上传之后的任何时候开始压缩。这个“开始时间”是视频上传的时间和服务器变空闲的时间之间的较大值。

4. **更新服务器的空闲时间**：一旦确定了视频的压缩开始时间，我们就可以计算出它的压缩结束时间。然后，我们更新服务器的空闲时间为这个“结束时间”。

**满分代码**

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    // 提高C++ I/O效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;  // n是视频的数量，k是服务器的数量
    cin >> n >> k;

    // 使用优先队列维护每个服务器的空闲时间
    // 优先队列会使得最早变空闲的服务器始终位于队列的顶部
    priority_queue<long long, vector<long long>, greater<long long>> pq;

    // 初始化所有服务器的空闲时间为0
    for (int i = 0; i < k; ++i) {
        pq.push(0);
    }

    for (int i = 0; i < n; ++i) {
        long long s, m;  // s是视频上传的时间，m是视频的长度
        cin >> s >> m;

        // 获取最早变为空闲的服务器的时间
        long long freeTime = pq.top();
        pq.pop();

        // 计算视频开始压缩的时间：是视频上传的时间和服务器变空闲的时间之间的较大值
        long long startCompress = max(freeTime, s);

        // 计算视频完成压缩的时间
        long long endCompress = startCompress + m;

        // 输出视频完成压缩的时间
        cout << endCompress << "\n";

        // 更新服务器的空闲时间为视频完成压缩的时间
        pq.push(endCompress);
    }

    return 0;
}
```

这种方法利用了优先队列的性质，使我们能够在常数时间内找到最早变空闲的服务器，从而高效地处理每一个视频。

---

## 作者：wang_freedom (赞：0)

### 思路：
显而易见的优先队列。

如果有闲置的服务器，那么用这台服务器来进行压缩，结束压缩的时间即为 $s+m$。

如果没有闲置的服务器，则寻找当前压缩结束最早的服务器。

优先队列用小根堆来写即可。

### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
priority_queue<ll,vector<ll>,greater<ll> >q;
ll n,k; 
signed main(){
	cin.tie(0);cout.tie(0);std::ios::sync_with_stdio(0);
	cin>>n>>k;
	rep(i,1,n){
		ll m,s;
		cin>>m>>s;
		if(k<=q.size()){
			m=max(q.top(),m)+s;
			q.pop();
		}
		else
			m+=s;
		q.push(m);
		cout<<m<<endl;
	}
	return 0;
}
/*

*/

```
### 提示：
不开 `long long` 见祖宗！

---

## 作者：_WF_ (赞：0)

# 题意理解
**题意**：输入一个 $ n $ 和一个 $ k $，$ n $ 个视频 $ k $ 个压缩工具。每个压缩工具每压缩一分钟视频要花费 $ 1 $ 秒的时间。后面 $ n $ 行，每行输入两个数，第 $ i $ 行第一个数代表第 $ i $ 个待压缩视频的到达时间，后一个数代表第 $ i $ 个带压缩视频一共有多少分钟。一个压缩工具压缩完毕后立刻压缩后面未压缩的视频。

**思路**：这个题模拟就行了，用优先队列维护压缩时间最小的。

具体可用**优先队列**来实现。
# 优先队列：
 **优先队列**定义可分为两种：
 ```
//升序队列
priority_queue <int,vector<int>,greater<int> > q;

//降序队列
priority_queue <int,vector<int>,less<int> >q;

```
**根据题意**，这里使用**升序**。

# AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long,vector<long long>,greater<long long> > que;
int main(){
	long long n,k,a,b,all;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b;
		if(que.size()>=k) {
			all=max(a,que.top())+b;
			que.pop(); 
		}
		else all=a+b;
		cout<<all<<endl;
		que.push(all);
	}
	return 0;
} 
```

---

## 作者：Silence_World (赞：0)

# 题意

给你 $n$ 个视频和 $k$ 个服务器，如果有服务器未被占用就用这个服务器去处理此视频，耗费 $m$ 的时间，如果服务器全被占用就等一个服务器处理完再用，处理时间最后要加一个 $s$，问每个视频处理的最短时间是多少。

# 思路

因为要求每个，所以是很明显的贪心，优先队列维护，当服务器全被占用时，每次取最短的视频处理时间与本视频处理时间比较（因为要腾出服务器）取更大的（也就是数轴上覆盖最大的区域），加上个 $s$，挨个输出，搞定！但关键的是！！！这个题的输入输出卡了我好久 QAQ，因为此题数据非常大，用 cin 和 cout 无法通过此题，调了半天也不知道自己怎么 T 的，看了看题解发现和自己方法一样，自闭了好久呜呜。

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
priority_queue<int,vector<int>,greater<int> >q;
main(){
	int n,k;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		int x,y;
		
		scanf("%lld%lld",&x,&y);
		if(q.size() and q.size()>=k){
			x=max(x,q.top())+y;
			q.pop();
		}
		else{
			x+=y;
		}
		q.push(x);
		printf("%lld\n",x);
	}
} 
```


---

## 作者：haozinojc (赞：0)

一道用了**优先队列**就很简单的水题。

### 思路：

因为有 $k$ 个服务器，所以最多可以同时处理 $k$ 个视频。
所以按下面两种情况安排压缩顺序就行了：

- 如果有没有正在被使用的服务器，则安排该视频进行压缩，结束压缩的时间则是 $s+m$。

- 如果没有可以使用的服务器，则寻找结束压缩时间最早的服务器，安排该视频在此服务器结束上一个视频后进行压缩。

### 优先队列：



一种自动帮你以某种方式排序的容器。

- 小根堆（从小到大）：
```cpp
priority_queue<int,vector<int>,greater<int> >q;
```

- 大根堆（从大到小）：
```cpp
priority_queue<int,vector<int>,less<int> >q;
```
### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int,vector<int>,greater<int> >q;
int n,k,m,s;
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>m>>s;
		if(q.size()>=k){
			m=max(q.top(),m)+s;
			q.pop();
		}
		else m+=s;
		q.push(m);
		cout<<m<<"\n";
	}
	return 0;
} 

```


---

## 作者：xiaojuruo (赞：0)

## 题意
有 $n$ 个视频和 $k$ 个可以解压视频的服务器。第 $i$ 个视频要 $m_i$ 的时间上传，要 $s_i$ 的时间解压，求最短的解压时间。
## 分析
既然要求最短，我们不妨贪一贪，每次都优先上传最短的即可。那么我们就可以分为如下两种情况：

1.有**空闲**的服务器，我们直接上传后解压。

2.我们没有空闲的服务器，那么我们就等**最快**的一个服务器处理完后，我们再解压即可。

这是，我们有两种方式来存储，一是用数组存储，然后每次排序，二则是我们今天要讲的**优先队列**了。

~~另外十年OI一场空，不开longlong见祖宗~~
## 什么是优先队列
我们都知道，队列是一种先进先出的数据结构。但是在优先队列中，我们是以**数据**来作为优先级来出队入队的，一般是堆实现。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long,vector<long long>,greater<long long> > q;
//greater是最小堆，less则为最大堆。定义堆那不要将两个>放在一起，不然会是视为左移运算符
int main(){
	long long n,k,a1,a2,ans;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
			scanf("%lld%lld",&a1,&a2);
		   if(q.size()>=k) {
			ans=max(a1,q.top())+a2;
			q.pop(); 
		}
		else ans=a1+a2;
		cout<<ans<<endl;
		q.push(ans);
	}
	return 0;
} 
```



---

## 作者：_YyD_ (赞：0)

**题目大意：**

给你 $N$ 个任务单，每个任务单有两个元素 $s_i,m_i$ 分别表示来的时间，以及需要完成这个订单的时间。

问你最优去做的话，每个订单的结束时间是多少？

**思路：**

过程类似于优先队列，优先级为完成时间的早晚，越早越前面。

这样的话就是每加一个订单，就完成现在未完成订单中最早的那个，即弹掉队列头。

然后判断现在机器是否用满了：

1. 没用满，拿出一个空机给当前任务。

1. 用满了，取队头元素，等待这份订单结束之后，这台机器供给当前订单使用即可。

最后注意数据范围即可。

---

