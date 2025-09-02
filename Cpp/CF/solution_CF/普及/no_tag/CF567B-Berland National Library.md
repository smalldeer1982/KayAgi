# Berland National Library

## 题目描述

Berland National Library has recently been built in the capital of Berland. In addition, in the library you can take any of the collected works of Berland leaders, the library has a reading room.

Today was the pilot launch of an automated reading room visitors' accounting system! The scanner of the system is installed at the entrance to the reading room. It records the events of the form "reader entered room", "reader left room". Every reader is assigned a registration number during the registration procedure at the library — it's a unique integer from $ 1 $ to $ 10^{6} $ . Thus, the system logs events of two forms:

- "+ $ r_{i} $ " — the reader with registration number $ r_{i} $ entered the room;
- "- $ r_{i} $ " — the reader with registration number $ r_{i} $ left the room.

The first launch of the system was a success, it functioned for some period of time, and, at the time of its launch and at the time of its shutdown, the reading room may already have visitors.

Significant funds of the budget of Berland have been spent on the design and installation of the system. Therefore, some of the citizens of the capital now demand to explain the need for this system and the benefits that its implementation will bring. Now, the developers of the system need to urgently come up with reasons for its existence.

Help the system developers to find the minimum possible capacity of the reading room (in visitors) using the log of the system available to you.

## 说明/提示

In the first sample test, the system log will ensure that at some point in the reading room were visitors with registration numbers $ 1 $ , $ 1200 $ and $ 12001 $ . More people were not in the room at the same time based on the log. Therefore, the answer to the test is 3.

## 样例 #1

### 输入

```
6
+ 12001
- 12001
- 1
- 1200
+ 1
+ 7
```

### 输出

```
3```

## 样例 #2

### 输入

```
2
- 1
- 2
```

### 输出

```
2```

## 样例 #3

### 输入

```
2
+ 1
- 1
```

### 输出

```
1```

# 题解

## 作者：wanggk (赞：4)

## 读题
主要是两个要点：

- 动态更新每个人依次的状态，更新当前人数。

- 【初值】处理最开始最少有几个人。

## 分析

#### 一、先计算初值：
有一些莫名其妙，没进来就出去的（这个人**前面的字符是减号 ，前面也没有输入加号**），也就是最开始已经在里面的。

可以用一个数组 $f[i]$ 记录编号为 $i$ 的人有没有进来过，如果没有进来过，就出现一个减号，那么就认定为最开始就在的，也就是 $f2[i]=1$ （ $f2$ 数组紧接着会讲）。

#### 二、过程中状态的更新

刚刚说到 $f2[i]$ ，$f2[i]$ 其实就表示编号为 $i$ 的人现在的状态。

**区分:** $f[i]$ 是记录他是先加还是先减（先减就是之前就有的），用于初始化； $f2[i]$ 是记录过程中的状态。

初始如果这人开始就在，则 $f2[i]$ 初值为 $1$ ,否则为 $0$ .

至于过程中的加减，加的话就更新为 $1$, 出去时改为 $0$ 即可.

#### 三、过程中人数的计算

两个变量：$cnt$ 和 $ans$ .

$cnt$ : 当前人数，随着输入的语句，跟着 $f2[i]$ 同步更新。

$ans$ : 过程中 $cnt$ 的巅峰（最大值）。

（**建议自己先写再看下面的代码部分**）

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ans;
int cnt;
int a[105];//a[i]为正表示编号进，为负表示编号出 
bool f[1000005];
bool f2[1000005]; 
int main()
{
	scanf("%d",&n);
	//1.输入的处理，a[i]为正表示编号进，为负表示编号出  
	for(int i=1;i<=n;i++){
		char c;
		cin>>c>>a[i];
		if(c=='-') a[i]=0-a[i];
	}
	//2.预处理出一开始就在的人，别忘了累计进cnt的初值里 
	for(int i=1;i<=n;i++)
	{
		if(a[i]>0) f[a[i]]=1;
		else if(a[i]<0&&f[-a[i]]==0) f2[-a[i]]=1,cnt++;
	}
	//3.过程中不断更新f2的值 
	ans=cnt; 
	for(int i=1;i<=n;i++)
	{
		if(a[i]>0) cnt++,f2[a[i]]=1;
		else cnt--,f2[-a[i]]=1;
		ans=max(ans,cnt);
	}
	printf("%d\n",ans);
	return 0;
}
```
讲的很详细了

~~求通过。~~

---

## 作者：lichenzhen (赞：3)

## 题目大意
给出一个时间片段图书馆人员的进出信息，求图书馆的最小容量是多少。
## 题目解法
一道比较简单的桶思想的题目，我们把所有的人的 ID 卡号都对应一个桶，我们要看一下原题面，可以发现 $1\le r_i \le 10^6$，也就是说 ID 卡号最大到 $10^6$，所以桶要开 $ \ge 10^6$ 个。

这道题可以使用 `map` 来当作桶，可以省一部分空间，但是普通的一维数组也是可以的。

对于每个进出信息，要分情况处理，我们把当前图书馆内的人数定义为 $d$，图书馆的最小容量为 $a$。

- 如果是进入了一个人，就将 $d+1$，然后将其编号对应的桶设为 $1$，表示这个人在图书馆里了，之后要更新一下最小容量的的值。
- 如果是有一个人出来了，要判断他是在输入这个片段之前就在图书馆里还是之后在图书馆里。如果是在这之前，就需要将 $a+1$，否则就将 $d-1$ 将他的 ID 卡号对应的桶设为 $0$，表示这个人不在图书馆里。

#### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char opt;
int book[1000001],n,ans,d,s;
int main()
{
    cin>>n;
    while(n--){
        cin>>opt>>s;
        if(opt=='+'){
            d++;
            book[s]=1;
            ans=max(d,ans);//更新最小容量的的值
        }
        else{
            if(book[s]==0) ans++;
            else{
                book[s]=0;
                d--;
            }
        }
    }
    cout<<ans;
}
```


---

## 作者：__HHX__ (赞：2)

# 思路（求初值）
初值就是他没进去就出来的人。

求出初值后，只需看如果有人出去 $cnt - 1$，有人进来 $cnt + 1$。

最后求出 $cnt$ 最大值即可。
# 代码
```cpp
#include<iostream>

using namespace std;

const int MaxN = 1e2 + 3, MaxV = 1e6 + 3;

int add[MaxN], ans, cnt;
bool f[MaxV];
int main() {
	int n;
	cin >> n;
	for(int i = 1, x; i <= n; i++) {
		char ch;
		cin >> ch >> x;
		bool l = (ch == '-');
		ans += l & !f[x];
		f[x] = 1;
		add[i] = l;
	}
	for(int i = 1, cnt = ans; i <= n; i++) {
		if(add[i]) {
			ans = max(ans, --cnt);
		} else {
			ans = max(ans, ++cnt);
		}
	}
	cout << ans;
} 
```

---

## 作者：BYWYR (赞：1)

~~这题评个**红**不过分吧。~~

简单的 **桶排序** 思维。

## 思路

开一个 vis 标记数组，标记哪些人**进来过**哪些人**没进来过**。

再按顺序判断是 **进来的（+）** 还是 **出去的（-）**。

1. 进来的

- 现在人数增加；

- 标记一下已经进来；

- 与场内现有最多人数比较。

2. 出去的

**分两种情况**。

- 已经进来过的；

- 没进来过的。


## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,now,ans;
bool vis[1000005];
char ch;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>ch;
		int x;
		cin>>x;
		if(ch=='+'){
			now++;//现在人数增加
			vis[x]=true;//标记一下已经进来
			ans=max(ans,now);//与场内现有最多人数比较
		}
		if(ch=='-'){
			if(vis[x]==false){//没进来过的
				ans++;//没进来过，但以前在
			}
			else if(vis[x]==true){//已经进来过的
				now--;//出去了，现在人数少了
				vis[x]=false;//标记一下出去了
			}
		}
	}
	cout<<ans<<endl;
	return 0;//完美结束
}

```


---

## 作者：szh_AK_all (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF567B)

## 题意和分析
我们称一个人进出图书馆为一次操作，已知 $n$ 次操作，要求我们求出图书馆最少可能容纳的人数。

首先，我们遍历每次操作，如果有人进入图书馆，那么让第一个计时器加 $1$，在判断第一个计时器是否超过了第二个计时器（第二个计时器用来记录第一个计时器最大时刻的值），如果超过了，那么更新第二个计时器。

如果有人从图书馆出去，那么我们先判断他之前是否进入过图书馆（用一个桶来记录，因为每个人的编号是数字，如果是字符串可以用键值对），如果他之前进入过图书馆，那么第一个计时器减 $1$，否则，就代表在程序运行之前，他就已经在图书馆了，所以让第一个计时器加 $1$。最后将这个人在桶内的状态改为不在图书馆。

## Code
```c
#include<iostream>
using namespace std;
int a[1000000];
int main()
{
    int ans=0,tmp=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        char x;
        int y;
        cin>>x>>y;
        if(x=='+')
        {
            a[y]=1;
            ans++;
            if(ans>tmp)
            tmp=ans;
        }
        else
        {
            if(a[y]==1)
                a[y]=0,ans--;
            else
                tmp++;
        }
    }
    cout<<tmp;
    return 0;
}
```


---

## 作者：_buzhidao_ (赞：0)

[题目传送门](/problem/CF567B)  
# 解题思路
比较像**桶排序**。  
在一个 `bool` 数组里存放**每一个客人在不在图书馆里**。  
有些客人很神奇，没进来就出去了，这些客人就是题目所说的**在程序运行之前就在里面的客人**。  
需要处理**最开始至少有几个客人**。  
最后只需输出**在图书馆里最少人数的峰值**即可。  
## 具体做法
在输入时处理一切，可以让时间复杂度降低。  
  
如果出去一个人：
- 当这个人**已经在里面了**，把图书馆现在的人数**减少** $1$，再把这个人移出图书馆。**即，把** `bool` **数组的第 $id$ 位替换成** $0$。
- 当这个人**还没进去就出来了**，说明这个人**早就在里面了**，把**峰值增加** $1$，可以说是**留初值**。  
  
如果进去一个人，只要把这个人**放进图书馆**，然后把**图书馆现在的人数增加** $1$。  
为优化空间复杂度，我们使用 `bitset` 数组，只占有 `bool` 数组 $\frac{1}{8}$ 的空间。

### 为什么处理早就在里面的人需要增加**峰值**而不是**目前人数**？

理论上是走了一个人，图书馆**目前人数**应该减少，但是因为**此人进入未被统计**，所以不用减少，更不用增加。  
但是此人**以前是图书馆里的人**，所以统计到此人出去，**图书馆人数的峰值**还少了 $1$，所以要把峰值加 $1$，而不是增加现在人数。
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,cnt;//ans：人数峰值；cnt：目前人数
bitset<1000003> qaq;//bitset数组
bool isin;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);//IO优化，加速输入输出 
	cin>>n;char ch;int w;
	for(int i=0;i<n;++i){
		cin>>ch>>w;
		if(ch=='-'){//当出来一个人 
			if(qaq[w]) qaq[w]=0,--cnt;//此人在统计时进入，移出图书馆，目前人数减一 
			else ++ans;//这个人在程序运行前进入，将人数峰值增加一 
		}
		else{
			qaq[w]=1;++cnt;//进来一个人 
		}
		ans=max(ans,cnt);//求人数峰值 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Neilchenyinuo (赞：0)

## Solution 

1. 先计算初值（初值是指原来就在里面的人）。

2. 根据题面模拟，有人出去就 $cnt \gets cnt-1$，反之 $cnt \gets cnt+1$。

3. 最后求出 $cnt$ 最大值即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[105],ans,cnt;
bool vis[N];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		char s;
		cin>>s>>x;
		bool flag=(s=='-');
		ans+=flag & !vis[x];
		vis[x]=1;
		a[i]=flag;
	}
	cnt=ans;
	for(int i=1;i<=n;i++)
	{
		if(a[i])
			ans=max(ans,--cnt);
		else
			ans=max(ans,++cnt);
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：zhicheng (赞：0)

### 思路

用一个 `sum` 记录从一开始进去图书馆的人还有多少没出来。每次遇见一个 $+$ 就把它记到 `sum` 里并更新答案，同时用一个 `map` 记录它已经在图书馆里。而遇见一个 $-$，如果这个人在 `map` 里，那么从 `map` 里把他清出来，`sum` 减一。如果不在，说明他在记录开始前就已经在图书馆里，直接把最小容量减一即可，`sum` 不变。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int>mapp;
int main(){
	int n,a,ans=0,sum=0; //注意置0
	char d;
	scanf("%d",&n);
	while(n--){
		getchar(); //注意换行符
		scanf("%c %d",&d,&a);
		if(d=='-'){
			if(!mapp[a]){  //开始前进去的
				ans++;
			}
			else{  //在map里
				sum--;
				mapp[a]=0;
			}
		}
		else{
			ans=max(ans,++sum); //增加人数并更新答案
			mapp[a]=1;
		}
	}
	printf("%d",ans);
}
```

---

## 作者：Big_Brain (赞：0)

按照惯例，先上[题目传送门](https://www.luogu.com.cn/problem/CF567B)。

## 题意简述

有一个可以装入若干个数的容器。给出 $n$ 个操作，每个操作可能是这两个之一：

- 当输入的字符为 `+`，那么在容器中放入给定一个数；

- 当输入的字符为 `-`，那么把容器中的给定的一个数删去。

**注意：在进行操作之前，容器中有可能已经有数。**

求容器可能的最小容量 $t$。

## 思路总结

我们定义两个变量：

- $ans$ 表示最小容量；

- $tmp$ 表示现在的容量。

在两种操作下分别讨论。

#### 当操作为 `+`：

这种情况比较简单。如果操作为 `+`，那么说明容器中多出了一个数。

我们将现在的容量 $tmp$ 加上 $1$，并且把 $ans$ 取为 $\max \{ans,tmp \}$ 即可。

#### 当操作为 `-`：

这种情况会复杂一些。首先，我们需要定义一个数组 $a$，用来储存这个数在之前有没有进入过容器，判断这个数是否是容器原本就有的。如果发现原来就有，说明在之前的计算过程中，都没有算入这个数，将 $ans$ 增加 $1$ 即可；否则，将现在的容量 $tmp$ 减去 $1$ 即可。

## 完整代码

```python

n = int(input())
a = [0] * 10000010 #初始化
ans = 0
tmp = 0
for _ in range(n):
    op, num = input().split() #输入操作符号和数
    num = int(num)
    if op == '+': #如果操作为‘+’
        a[num] = 1 #输入了这个数，代表这个数不是容器原本就有的
        tmp += 1 #将现在的容量增加 1
        if ans < tmp:
            ans = tmp
    else: #否则操作为‘-’
        if a[num] == 1: #如果不是原本就有的
            tmp -= 1 #将现在的容量减少 1
        else: #否则，是原本就有的
            ans += 1 #将答案减少 1
print(ans) 
#珍爱生命，远离抄袭
```


---

## 作者：lcy_2009 (赞：0)

[CF原题链接](https://codeforces.com/problemset/problem/567/B?csrf_token=daa2c156fbd813344a607667e854f843)

[洛谷链接](https://www.luogu.com.cn/problem/CF567B)

## 题目分析
1. 如果输入的是 $ + $,则将现在图书馆内的人数 $now+1$,如果 $now > ans$,则把 $ans = now$。

2. 如果输入的是 $ - $,并且这个id进入时有记录，则 $ now-1 $ 。

3. 如果输入的是 $ - $,并且这个id进入时没有记录，则 $ ans+1 $。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,id,now,ans,b[120010];
char c;
int main(){
   cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c>>id;
		if(c=='+'){
			b[id]=1;
			now++;
			if(now>ans)ans=now;
		}
		else
			if(b[id]==0)ans++;
			else {
				now--;
				b[id]=0;
		}
	}
	cout<<ans;
   return 0;
}
```


---

