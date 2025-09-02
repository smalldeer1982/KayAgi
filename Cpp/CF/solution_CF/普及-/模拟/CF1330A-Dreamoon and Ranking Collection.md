# Dreamoon and Ranking Collection

## 题目描述

Dreamoon 热衷于参加 Codeforces 竞赛。

一天，他声称自己再参加两场 rated 场后，就会获得过从第 $1$ 名到第 $54$ 名的所有名次。这真是不可思议！

基于此，你提出了如下一个问题：

张三参加了 $n$ 场 Codeforces 比赛。他第一场的排名为 $a_1$，第二场的排名为 $a_2$，……，第 $n$ 场的排名为 $a_n$。

给出一个正整数 $x$。请找到最大的 $v$，满足张三在再参加 $x$ 场 rated 比赛后，有可能取得 $1$ 到 $v$ 中所有名次。

换句话说，你需要找到最大的 $v$，满足在继续参加 $x$ 场 rated 比赛后，有可能对于任意的 $1 \le i \le v$，存在一场张三排在第 $i$ 名的比赛。

举个例子，如果 $n = 6, x = 2, a = [3, 1, 1, 5, 7, 10]$，那么答案 $v = 5$。因为如果接下来的两次比赛内，张三分别取得了第 $2$ 名和第 $4$ 名，他可以获得过第 $1$ 名到第 $5$ 名内的所有名次，所以 $v = 5$ 是可能达成的最大答案。


对于第二组测试数据，张三将会再参加 $100$ 场比赛，他可以以任意顺序取得第 $1, 2, \ldots, 99$ 和 $101$ 名，就获得过第 $1, 2, \ldots, 101$ 名中的所有名词。

## 样例 #1

### 输入

```
5
6 2
3 1 1 5 7 10
1 100
100
11 1
1 1 1 1 1 1 1 1 1 1 1
1 1
1
4 57
80 60 40 20```

### 输出

```
5
101
2
2
60```

# 题解

## 作者：tuzhewen (赞：11)

题意很复杂……~~（表示我看了10min才看懂真正的意思）~~

于是我们简化一下题意就是：给定一个数组，然后再给你一个$x$，你就可以往这个数组里面添加$x$个数字。然后求一个最大的$v$，代表这个数组中添加了$x$个数字之后，排序后存在一个**连续不间断**的序列$1$~$v$。

举个栗子更好食用：

比如说我们现在有一个数组长这样：

`1 3 8 4 7 6`

并且可以往里面添加$2$个数（即$x=2$）,那么我们将输出`8`。

为什么呢？因为我们往里面添加$2$个数分别为$2$和$5$，那么这个数组中就含有$1$~$8$之间的所有数字，所以输出$8$

其实也不用排序，刚才那么说只是为了方便理解，也只是说数组里存在$1$~$v$就行了。

并且我们发现数据很小，所以用一个桶就能$AC$了

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,v;
int a[1005];
bool flag[1005];//数组开大一点总没有事的，空间不要钱嘛~（好像不止“一点”了……）
int main() {
	scanf("%d",&t);//t组数据
	while(t--) {
		int cnt=0;
		memset(flag,0,sizeof(flag));//不要初始化啊！！
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			flag[a[i]]=true;//如果出现了就标记一下
		}
		while(true) {//这里其实完全可以改成for(int i=1;i<=201;i++)只不过感觉这样保险一点qwq
        //所以说这个循环就是在从1开始枚举啦~
			cnt++;//每次加一
			if(!flag[cnt]) {//如果不在数组里面
				if(x>0) x--;//可以添加的话就添加
				else if(!x) break;//如果x都没了那么这个数组就没救了，直接弃疗（break掉）
			}
		}
		printf("%d\n",--cnt);//这里要减去1！因为如果你取不到当前cnt的数的话那么这个数是不算的！
        //（不测样例换来的血的教训qaq）
	}
	return 0;//良好习惯~
}
```

[记录详情](https://www.luogu.com.cn/record/32540230)

---

## 作者：lichenzhen (赞：3)

## 题目大意
给出一个人参加了 $n$ 场比赛的排名，问再参加 $x$ 场比赛后最多能取得从 $1$ 到几的所有名次（也就是题目要求的 $v$）。

有 $t$ 组数据。

## 题目解法
题目比较长，需要认真读题。

理解题目之后，就很容易做了。这道题目可以运用桶思想来解决。

定义一个桶，记录是否获得这个名次。最后循环扫描这个桶，如果没有这个名次，就假设他获得了这个名次，就 $x$ 减去 $1$。

最后直到 $x$ 场比赛都没有了，并且在进行 $x$ 场比赛之前也没有获得这个名次，就直接输出当前循环轮次减去 $1$ 即可（因为当前这个名次不可以获得了）。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,book[1000];
int main()
{
    int T;
    cin>>T;
    while(T--){
        memset(book,0,sizeof(book));//一定要注意每次都将桶清零
        int n,x;
        cin>>n>>x;
        for(int i=1;i<=n;i++)
            cin>>a,book[a]=1;
        int i=0;
        while(1){//循环扫描桶
            i++;
            if(book[i]==0&&x==0){
                cout<<i-1<<'\n';
                break;
            }
            if(book[i]==0)
                x--;
        } 
    }
    return 0;
}
```

本题可以用快读优化读入效率，代码就不放了。

---

## 作者：szh_AK_all (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1330A)

对于这道题，我们要用一个桶来记录每个排名。但桶的大小不能设为 $100$ 左右，而是要设到 $200$ 左右。因为:
$$x\le100,a _   {i}\le100$$
所以，上线可能到达 $200$。但由于组数可能大于 $1$，所以我们还需要初始化，我们可以直接使用函数，如 `memset(a,0,sizeof(a))`，也可以在循环过程中一边判断一边初始化，下面在代码中用第一种方法。
## Code
```c
#include<iostream>
#include<cstring>
using namespace std;
int a[205];//注意，不要设成105
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,m;
        cin>>n>>m;
        for(int j=1;j<=n;j++)
        {
            int x;
            cin>>x;
            a[x]=1;
        }
        for(int j=1;j<=200;j++)
        {
            if(a[j]==0)
			{
            m--;
			a[j]=1;//补充还没取得的名次
			}
            if(m==0)//如果不能补充了
            {
                int y=j;
                while(a[y]==1)//考虑还有没有本身就取得的名次
                y++;
                cout<<y-1<<endl;
                break;
            }
        }
        memset(a,0,sizeof(a));
    }
    return 0;
}

```


---

## 作者：xh001 (赞：1)

# 题意
首先给定一个整数 $t$ 表示有 $t$ 组数据，每组数据包含两个数 $n$，$x$ 和一个长度为 $n$ 的序列 $a$，$n$ 为已经打过的场次，$x$ 为能打的比赛场次，序列 $a$ 为每个场次的名次，求最大的 $v$ 使得在再打了 $x$ 场比赛后（这 $x$ 场比赛的名次可以是**任何**大于 $1$ 的数），名次包含 $1-v$ 中的所有数。
# 思路
本题第一眼下去就是大模拟，只需要开一个标记数组记录得过的名次，当碰到没得过的名次时就打一场得到该名次的比赛就可以继续枚举。
# 注意事项
详见代码注释：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//好习惯。 
ll t,n,x,a,sum;
bool f[201];//开桶记录拿过的名次（注意：记得开大点，最大能到200名）。 
inline ll read()//快读。 
{
	ll k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		x=read();
		sum=0;//即题目中的v。 
		memset(f,0,sizeof(f));//初始化。 
		for(ll i=1;i<=n;i++)
		{
			a=read();
			f[a]=1;
		}
		while(x>0)//比赛场次用完就退出循环。 
		{
			while(f[sum+1]) sum++; //拿过的名次直接过。
			sum++;
			x--;//此时一定是没拿过的名次，消耗一场比赛来获得该名次。 
		}
		while(f[sum+1]) sum++;//防止后面紧跟着拿过的名次。 
		cout<<sum<<endl;
	}
	return 0;
}
```


---

## 作者：blsya23a2 (赞：0)

## 分析
这道题**不需要**排序。首先，我们把一个变量 $i$ 从 $1$ 向上递增，如果 $i$ 不在输入的序列 $a$ 中，就加入 $a$，重复这个过程直到加入 $x$ 次。再把一个变量 $j$ 从 $1$ 向上递增，直到 $j$ 不在 $a$ 中，就输出 $j-1$。
## 代码
```python
a = int(input())
for b in range(a):
    c,d = map(int,input().split())
    g,h = list(map(int,input().split())),0
    i = 1
    while h < d:
        while i in g:
            i += 1
        g.append(i)
        h += 1
    for j in range(1,len(g)+2):
        if j not in g:
            print(j-1)
            break
```
还没有 python 题解，希望管理员通过！

---

## 作者：fangyicheng1216 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1330A)

# 思路

这道题的题意简化一下就是，在一个长度为 $n$ 的数组中可以加入 $x$ 个任意数字，求最大的 $v$ 使得 $[1,v]$ 之间的数字数组中都有。

那么因为这道题的 $a_i$ 很小，所以考虑开一个数组 $pd$，$pd_i$ 表示数组中是否含有数字 $i$。接下来枚举 $pd$ 数组，每遇到一次 $pd_i=0$ 的，就让 $x$ 减一，直到 $x$ 与 $pd_i$ 都为 $0$ 时输出枚举到的数加一。

这个最优是可以证明的，因为我们要求一个区间 $[1,v]$ 最长，所以最好的办法就是把区间 $[1,v]$ 中间的空缺都补上，这样可以得到最长的区间。

# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){//快读 
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        f=ch!='-';
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return f?x:-x;
}
inline void write(int x){//快写 
    if(x>=10) write(x/10);
    putchar(x%10+48);
}
inline int quickPower(int a,int b){//没有用的快速幂 
	int ans=1,base=a;
	while(b>0){
		if(b&1)
			ans*=base;
        base*=base;
		b>>=1;
	}
	return ans;
}
int T,n,x;
bool pd[205];
signed main(){
	T=read();
	while(T--){
		memset(pd,0,sizeof(pd));//一定要初始化！ 
		n=read(),x=read();
		for(int i=1;i<=n;i++) pd[read()]=1;//对于每一个输入的数就把它对应的pd数组的位置变为1
		//枚举最大能到达的位置 
		int ans;
		for(ans=1;;ans++){
			if(x==0&&pd[ans]==0) break;
			if(pd[ans]==0) x--;
		}
		write(ans-1);//（为什么要-1其实我也不知道qwq） 
		putchar('\n');//换行 
	}
	return 0;
}
```


---

## 作者：xuhanxi_dada117 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1330A)

# 题目大意

给出一个数组，求正整数中第 $x$ 个没有在数组中出现的数。


# Solution

注意到 $a_i \le 100$：

直接开一个桶统计谁出现过，遇到有的跳过没有的减掉。

判断是不是第 $x$ 个即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,_,a[100010],vst[1000010];
int main(){
	cin>>_;
	while(_--){
		cin>>n>>k;
		memset(vst,0,sizeof(vst));//多测要清空！
		for(int i=1;i<=n;++i) cin>>a[i],vst[a[i]]=1;int i;
		for(i=1;i<=114514;++i){
			if(!vst[i]){//如果不在数组内
				if(k) k--;//更新
				else break;
			}
		}
		cout<<i-1<<"\n";//一定要-1！！这是第x+1个！
	}
	return 0;
} 
```

---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1330A)

### **[题意解析]**
~~这题的题面是真的难读懂~~，大概意思就是给你张三的 $n$ 场比赛的排名 $a_i$，让你求参加完 $n$ 场比赛后再参加多少场比赛才能使张三获得 $1$ 到 $v$ 的排名，我们的 $v$ 要尽量大。

### **[思路分析]**
题意读懂了，那这道题就成了一道~~数组计数~~**桶**的入门题，我们用我们的桶记录张三第 $i$ 场比赛中是否获得成绩，然后循坏查询一边我们的桶。
+ 如果没获得第 $i$ 个名次，就用 $x$ 补一个名次，$x$ 减去 $1$。
+ 如果 $x$ 变成 $0$ 了，说明这第 $i$ 个名次，张三是怎样都拿不到了，直接输出最大的 $v$，退出循环就好了。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,t,ans;
bool used[1010];
int main()
{
	cin>>T;
	while(T--){
		cin>>n>>t;
		memset(used,0,sizeof(used));
		/*记得归0*/
		ans=0;
		for(int i=1; i<=n; i++){
			int a;
			cin>>a,used[a]=1;
		}
		/*用桶记录张三获得过的排名*/
		for(int i=1; i<=1010; i++){
			/*遍历一遍我们的桶*/
			if(!t&&!used[i]){/*如果t补不了了且这个成绩张三不知道，直接输出*/ 
				cout<<i-1<<"\n";
				/*注意，要-1，因为这个成绩张三获取不了*/
				break;
			}
			if(!used[i])t--;
			/*用t补成绩*/
		}
	}
	return 0;
}
```


---

## 作者：j1ANGFeng (赞：0)

### 题意
给你一个数列，往里面添加 $x$ 个数，得到最大的 $v$；代表这个数列排序去重后从 $1$ 到 $v$ 是连续不间断的数列。

### 分析
用一个桶记录什么数出现了，然后从 $1$ 开始找没有出现的数并记录有多少个数没出现。当没出现的数达到 $x$ 并且当前判断的数为零时记录答案并输出。

### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#define ll long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}
int vis[N];
signed main(){
    int t=rd()+1;
    while(--t){
        memset(vis,0,sizeof(vis));
        int n=rd(),x=rd();
        for(int i=1;i<=n;++i)
          vis[rd()]=1;
        int ans=0;
        for(int i=1;;++i){
            if(x==0&&vis[i]==0){
                ans=i-1;
                break;
            }
            if(vis[i]==0){
                --x;
            }
        }
        wt(ans);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：chenyuhe (赞：0)

题意：给出T组数据，每组数据有一个n，m。n代表这位选手已经有的n次比赛的名次。现在又要举行m次比赛，问经过m次比赛后，这位选手最多可以有从1开始，连续的几个名次。

举例：样例中的3 1 1 5 7 10，表示这位选手已经获得过第3，1，1，5，7，10名，问2次考试过后他最多能从1开始后连续的几个名次。显然这里已经有1，3，5名了，在接下来两场比赛中他获得第2，4名，则他有连续的5个名词。所以输出5。

懂题意以后这题就变得容易许多（~~本蒟蒻看题看了20min~~）

首先肯定是将已有的名次排序。
```cpp
sort(a+1,a+n+1);//a[i]存储着第i次考试的名次
```
接下来：由于有m场考试，所以肯定能保证有连续m个名次。然后判断前n次考试中是否有相同的名次，把相同的给pd[i]=false掉，就可以保证在后面不会重复算。

代码如下：
```cpp
int sum=m;//这里sum记录着最大连续的名次
for(int i=2;i<=n;i++){
    if(a[i]!=a[i-1])pd[i]=true;
    else pd[i]=false;
}
```
注意：在m次考试结束后，还要判断是否与前n场考试中的名次是相邻的。

代码如下：
```
for(int i=1;i<=n;i++){
    if(a[i]<=sum+1&&pd[i]){
       sum++;
    }
}
```

加上一些初始化，这题就完成了：

完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[1000005];
bool pd[1000005];
int main(){
	cin>>t;
	while(t--){
		int n,x,sum=0;
                memset(pd,false,sizeof(false));
		cin>>n>>x;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		sum+=x;
		pd[1]=true;
		for(int i=2;i<=n;i++){
			if(a[i]!=a[i-1])pd[i]=true;
			else pd[i]=false;
		}
		for(int i=1;i<=n;i++){
			if(a[i]<=sum+1&&pd[i]){
				sum++;
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}
```
想法过于奇特，大佬勿喷

---

## 作者：dead_X (赞：0)

## 1 题意简述
给你 $n$ 场比赛的排名，问你在参加这些比赛的一些后再参加 $k$ 场比赛，最多可能收集到从第一到第几的排名。 
## 2 思路简述
读题有一点点困难

不过问题不大

排序然后依次判断打排名从小到大的 $x$ 场再从后补 $k$ 场能收集到多少名次即可

代码难度不大
## 3 代码
```
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
int a[10003];
int main()
{
	int t=read();
	while(t--)
	{
		a[0]=-1;
		int n=read(),k=read(),cnt=0;
		for(int i=1; i<=n; i++) a[i]=read();
		bool f=0;
		sort(a+1,a+n+1);
		for(int i=1; i<=n; i++) 
		{
			if(a[i]!=a[i-1]) cnt++;
			if(cnt+k<a[i])
			{
				if(a[i]==a[i-1]) printf("%d\n",cnt+k);else printf("%d\n",cnt+k-1);
				f=1;
				break;
			}
		}
		if(!f) printf("%d\n",cnt+k);
	}
	return 0;
}
```
## 4 总结
稍稍难那么一点点的2A

---

## 作者：xrdrsp (赞：0)

这是本人的第 $003$ 篇题解。

这里介绍一下稍微不同的方法。

由于在每次判断中不需要知道具体的名次，而只需要知道 Dreamoon 有没有达到过这个名次，所以 `sort()` 是不必要的。用 $a_i$ 存下是否达到过 $i$ 这个名次，然后按顺序判断即可。这是符合要求的。

另一篇题解讲的很清楚了。

下面是 $\colorbox{green}{AC}$ 代码，具体见注释。

```c++
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int a[2 * N];                               // 开二倍

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        memset(a, 0, sizeof(a));
        int n, x;
        cin >> n >> x;                      // 读入
        int k;                              // 比赛名次
        int cnt = 0;                        // 加数字次数
        for (int i = 0; i < n; i++) {       // 读入
            cin >> k;
            a[k] = k;
        }
        for (int i = 1; i <= 2 * N; i++) {  // 统计
            if (!a[i]) {                    // 若第 i 名没有出现过，就把它补上，并更新计数器
                cnt++;
                // printf("  asdf %d\n", a[i]);
            }
            if (cnt == x + 1) {                  // 判断补的次数是否超过限制
                cout << endl << i - 1 << endl << endl;      // 输出
                break;
            }
        }
    }
    return 0;
}
```

Wish you high rating.

---

