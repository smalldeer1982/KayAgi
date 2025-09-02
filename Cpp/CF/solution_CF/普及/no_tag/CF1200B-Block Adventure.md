# Block Adventure

## 题目描述

你在玩一个游戏，已知在你面前有$n$列砖块，你的背包中有$m$个砖块，第$i$列有$h_i$个砖块。

在第$i$列你可以进行下列操作
- 如果你的背包中有砖块，你可以将将背包中的砖块放在第$i$列。
- 如果第$i$列有砖块，你可以捡起来，放在背包中。
- 如果第$i$列和第$i+1$列的高度差少于或等于$k$个砖块，你可以从第$i$列跳到第$i+1$列。

问你是否能从第一列从第$1$列跳到第$n$列。
如果能，输出$YES$,如果不能，输出$NO$。。

## 样例 #1

### 输入

```
5
3 0 1
4 3 5
3 1 2
1 4 7
4 10 0
10 20 10 20
2 5 5
0 11
1 9 9
99
```

### 输出

```
YES
NO
YES
NO
YES
```

# 题解

## 作者：引领天下 (赞：4)

这个题实际上就是个贪心……题意我交了翻译，这里就不重复说了

很明显，由于包的容量是无限大的，所以我们只要能往包里塞砖块就往里面塞，因为多塞肯定不吃亏

于是得到贪心策略：能把当前的砖能拿的尽量拿走，如果高度不够补到打擦边球……

具体看代码吧

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m,k,h[105];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&m,&k);
        for (int i=1;i<=n;i++)scanf("%d",&h[i]);
        bool flag=1;//判断是否有解
        for (int now=1;now<n&&flag;now++){
            if (h[now]>=h[now+1]-k)m+=min(h[now]-h[now+1]+k,h[now]);//能拿则多拿，但注意只能拿空，不能那成负的\滑稽
            else m-=h[now+1]-h[now]-k,h[now]=h[now+1]-k;//高度不够则补到刚好可以跳过去
            if (m<0)flag=0;//砖头用完了都跳不过去，则肯定无解
        }
        puts(flag?"YES":"NO");
    }
}
```

---

## 作者：一个低调的人 (赞：2)

### 为什么背包要用来装砖块，背包还无限大······(~~装点小零食、烤绿鸟不好吗，空间那么大~~)

- 你看那背包又大又宽，你看这个砖块放着没用，还不如放在背包里面，不用就可以拿来卖钱······（~~滑稽~~）

- 咳咳，进入正题。

- 看上面那句 ~~由《大碗宽面》歌词改编而成~~ 的那句话，这道题就知道是贪心，每当到了新的一列，我们看看下一列的高度是否小于等于 **k** ，是的话就把这一列的砖块全拿走（~~去卖钱~~）；如果不行的话，那就看看原高度是否达到**下一列的高度**-**k**的高度，够的话也把多的砖块拿走；如果还达不到的话，只能忍痛卸砖块，看看能不能用最少需要的砖块的数列过去；如果搭上了 **m** 块砖块还过不去，就不可能到第 **n** 列了，直接输出 "NO" ，如果成功到了终点，就输出 "YES" （~~然后就可以拿砖块卖钱去啦~~）。

## Code

```cpp
#include<map>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")*/
using namespace std;
int T,n,m,k,h[101];
bool bz;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>h[i];
		}
		bz=true;
		for(int i=1;i<n;i++)
		{
			if(h[i+1]<=k)
			{
				m+=h[i];
			}
			else if(h[i]>=h[i+1]-k)
			{
				m+=h[i]-(h[i+1]-k);
			}
			else if((h[i+1]-k-h[i])<=m)
			{
				m=m-(h[i+1]-k-h[i]);
			}
			else
			{
				bz=false;break;
			}
		}
		if(bz==true)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：Froggy (赞：1)

### 贪心好题

很显然,如果$h_{i+1}-h_{i}\le k$ ,那么把当前位置的木块尽量多的往包里塞(最多取$min(k+h_{i+1}-h_{i},h_{i})$,因为取完$h_{i+1}-h_{i}$还可以再取$k$个的差值,但取的总数不能超过$h_{i}$个

否则,从包里取出尽量少的木块,即$h_{i+1}-h_{i}-k$个木块,如过此时包里的木块数小于0,那么直接输出NO,退出

**代码:**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
#define N 111
inline ll read(){//快读
   	ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
ll T,n,m,k,h[N];//不开long long见祖宗
int main(){
	T=read();
	while(T--){
		bool ok=1;//记录是否成功
		n=read(),m=read(),k=read();
		for(int i=1;i<=n;i++){
			h[i]=read();
		}
		if(n==1){//如果只有一块,那么一定可以
			printf("YES\n");
			continue;
		}
		for(int i=1;i<n;i++){
			if(h[i+1]-h[i]>=k){
				m-=h[i+1]-h[i]-k;
				if(m<0){//如果包里没block了,直接走
					ok=0;
					printf("NO\n");
					break;
				}
			}
			else{
				m+=min(h[i],k+(h[i]-h[i+1]));//注意,不能取超过hi个,窝挂了好几次
			}
		}
		if(ok){
			printf("YES\n");
		}
	}
	return 0;
}

```


时间复杂度:$O(Tn)$

[Froggy's blog](https://www.luogu.org/blog/1445353309froggy/)



---

## 作者：ez_lcw (赞：0)

**显然，我们要想让自己能跳到最后一根柱子，就要让当前背包里的砖块个数越多越好。**

因为捡砖块是可以进行无限次的，而且没有耗费，但是搭砖块是要耗费你背包里的砖块的，所以你背包里的砖块要越多越好。

现在考虑一下从第 $i$ 根柱子跳到第 $i+1$ 根柱子上。

分两种情况讨论：

1. 如果你当前的高度 $h_i$ 比下一根柱子的最低跳跃范围大，即 $h_i>h_{i+1}-k$，那么你就可以捡砖块。

	这个时候考虑如何才能捡到最多的砖块，那当然是一直捡到当前高度为 $h_{i+1}-k$ 最赚啊。
    
    这时一共捡了 $h_i-(h_{i+1}-k)$ 个砖块，又可以完美跳到下一根柱子。

1. 如果你当前的高度 $h_i$ 比下一根柱子的最低跳跃范围小，即 $h_i<h_{i+1}-k$。

	那么显然你要搭砖块，而且背包里的砖块只减不加，所以考虑怎么样才能使耗费最小。
    
    显然当你达到 $h_{i+1}-k$ 的高度时，不仅能跳到下一根柱子，而且耗费最小。
    
那么把二者结合到一起，我们就可以算出从第 $i$ 根柱子跳到第 $i+1$ 根柱子上后，背包的增减量是多少：

$$bag_{new}=bag_{old}+h_i-(h_{i+1}-k)$$

然后再看一下背包内的砖块个数是否为负的就好了。如果是负的，就说明背包内的砖块不够用，输出 NO 就好了。

**这道题有一些比较坑细节，代码中的注释会说明。**

完整代码加注释如下：

```cpp
#include<bits/stdc++.h>
 
#define N 110
 
using namespace std;
 
int t,n,bag,k,h[N];
bool flag;
 
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		flag=false;//记得初始化
		scanf("%d%d%d",&n,&bag,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&h[i]);
		for(int i=1;i<n;i++)
		{
			int x=min(h[i],h[i]-(h[i+1]-k));//这里加个min是因为如果h[i+1]-k小于0那么最多只能跳到0
			bag+=x;
			if(bag<0)
			{
				flag=true;
				break;
			}
		}
		if(flag)//最后这里也要判断一下
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}
```


---

## 作者：Mars_ (赞：0)

[题目传送门](https://www.luogu.org/problem/CF1200B)

首先来说下题意：
```
主人公在玩一个游戏，若能从第一座大楼到第n座大楼，则游戏胜利。

每栋楼都有一个高度，且主人公有一个背包，可以放无数个方块。

最开始背包中有m个方块。

支持两个操作：

1.在当前的大楼取下方块放进背包，或者把方块从背包里拿出来放在大楼上

2.若如果两个大楼之间的高度差不超过k，则可以直接跳到下一座大楼。


共有t组数据。

对于每组数据，你都将被给出n,m,k的大小。

同时，题目里也会给出每栋大楼的高度h，

现在要你求出是否能通过，如果能，输出Yes，否则输出No
```


很明显，这是一道简单的贪心题

我们应当做到每次尽量从当前大楼拿下方块，以备后面的不时之需。（显然）

但是要注意，要判断这座大楼是不是被你夷为平地了！！！

不然就有可能会拿多方块（比赛的时候没想到这个所以掉分了）

代码如下:

```cpp
#include<iostream>
using namespace std;
int main() {
    int t;
    cin>>t;
    for (int i=0;i<t;++i) {
        int n,m,k,h[105];
        bool w=true;
        cin>>n>>m>>k;
        for (int j=0;j<n;++j)
            cin>>h[j];
        for (int j=0;j<n-1;++j)
        {
            if (h[j+1]-m-h[j]<=k) {
                if (h[j+1]-k>0)//判断是否拿多了
                    m+=h[j]-h[j+1]+k;
                else 
                    m+=h[j];
            }
            else {
                cout<<"No"<<endl;
                w=false;
                break;
            }
        }
        if (w)
            cout<<"Yes"<<endl;
    }
    return 0;
}
```

---

## 作者：Kizuna_AI (赞：0)

这道题就是一道贪心的题目。本人打比赛时做了半天（原因竟是本人竟然挖地洞了）  
挖地洞的代码(WA)：https://www.luogu.org/paste/axeqr2s6  
由于CF的输入是`%I64d`，不是`%lld`，所以本人也就不改回%lld了  
给出正确代码(AC)：
```
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,m,k;
long long h[110];
bool g;
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%I64d%I64d%I64d",&n,&m,&k);
		for(int i=1;i<=n;i++)
			scanf("%I64d",&h[i]);
		g=true;
		for(int i=2;i<=n;i++) {
			if(h[i-1]+m+k<h[i]) { //把我口袋中的所有东西都给你了还不够
				cout<<"NO\n";     //那就只能直接输出NO了
				g=false;
				break;
			}
			if(h[i-1]+k<h[i]) {
				m-=(h[i]-h[i-1]-k);b //若是不够，就把口袋里的东西尽可能少的给他，使他通过本关
			}
			else {
				m+=h[i-1]-max(h[i]-k,(long long)0); //防止挖地洞，需要判断是否<0，若<0就直接去0
			}
		}
		if(g) printf("YES\n");
	}
	return 0;
}

```

---

## 作者：Doveqise (赞：0)

这道题 一道简单贪心 CF的题质量都是很高的  
我们可以得出一个贪心的结论：  
当能拿方块的时候 尽可能多的拿方块  
可以(显然法)证明 尽可能多的拿方块是不劣于少拿方块的  
所以我们可以写出以下贪心代码  
(当然你要判一下现在是不是走到了地底
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e2+5;
int h[maxn];
signed main()
{
	int t;
	scanf("%d",&t);
	for(int ti=1;ti<=t;ti++)
	{
		memset(h,0,sizeof(h));
		int n,m,k,flg=0;
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&h[i]);
		for(int i=1;i<n;i++)
		{
			if(h[i]>=max(h[i+1]-k,0))
			{
				m+=h[i]-max(h[i+1]-k,0);
				continue;
			}
			else if(h[i+1]-k>h[i]+m)
			{
				puts("NO");
				flg=1;
				break;
			}
			else
			{
				m-=h[i+1]-h[i]-k;
				continue;
			}
		}
		if(flg)
			continue;
		else
			puts("YES");
	}
}
```

---

## 作者：破壁人五号 (赞：0)

采用贪心策略

假如该列不够高，我们只能往上摞

否则我们将尽可能多的方块挖掉，扔进背包

注意：挖掉的方块数量不能超过该列高度（因为这个 WA 了两次）

中途一旦方块不够用就 GG 了

```cpp
#include<bits/stdc++.h>
using namespace std;
 
int getint(){
    int ans=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-')f=-1;
        c=getchar();
	}
    while(c>='0'&&c<='9'){
        ans=ans*10+c-'0';
        c=getchar();
    }
    return ans*f;
}
int h[1010];
int main(){
	int t=getint();
	while(t--){
		long long n=getint(),m=getint(),k=getint();
		for(int i=0;i<n;i++){
			h[i]=getint();
		}
		bool ok=1;
		for(int i=0;i<n-1;i++){
			if(h[i]<h[i+1]-k)m-=h[i+1]-h[i]-k;
			else m+=min((long long)h[i],h[i]-h[i+1]+k);
			if(m<0)ok=0;
			//cout<<"? " <<m<<endl;
		}
		puts(ok?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：弦巻こころ (赞：0)

### 简单的贪心+模拟

思路：因为只要绝对值小于$k$就可以跳走。那我们肯定得将当前的$h$[$i$]变成 正好$h$[$i$+$1$]-$k$的高度 多出或少于就直接补或者拿就是了，需要特判的时候是当$h$[$i$+$1$]<=k的时候只能拿$h$[$i$]个方块，如果过程中包里方块小于$0$也就是方块不够了 就输出$NO$ 不然就输出$YES$

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,m,k;
bool pd;
int h[100005];
int main()
{
	cin>>t;
	while(t--)//多组数据
	{
		pd=0;
		scanf("%I64d%I64d%I64d",&n,&m,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&h[i]);
		}
		for(int i=1;i<=n-1;i++)
		{
			if(h[i+1]<=k)//如果在平地上都跳得到，就不能多拿
			{
				m+=h[i];
				continue;
			}
			m-=h[i+1]-h[i]-k;//拿或者补方块	
			if(m<0)//如果方块不够了
			{
				pd=1;
				break;
			}
		}
		if(pd==1)
		{
			printf("NO\n");
		}else
		{
			printf("YES\n");	
		}
	}
	return 0;
}
```

---

## 作者：Sakii (赞：0)

### 解析：
	其实是个很水的贪心(比赛永远打错字母）
   只要$h[i-1]$的高度大于等于$h[i]-k$时将$h[i-1]$的砖头拿到$h[i]-k$个即可。
   若$h[i-1]$的高度小于$h[i]-k$时讲包里的砖头拿出使$h[i-1]$的高度为$h[i]-k$，注意如果此时的m不够那么说明不合法则输出$NO$.
   
   

------------

### 代码：

```cpp
//≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈
//  Date : Plz press Shift + Ctrl + . in proper Sublime
//  Author : Sakii
//  website : zcqiever.tk
//  I'm so vegetable , QAQ..
//≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈

#include<bits/stdc++.h>
#define re register
#define il inline
#define lowbit(x) x&(-x)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

template <class T> inline void read(T &s){
    s = 0; re char ch = getchar(); re int w = 0;
    while(!isdigit(ch)) w |= ch == '-', ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
    if(w) s = -s;
}

namespace Sakii {
    int n,m,k,h[110];

    il void main() {
        int t;
        read(t);
        while(t--) {
            read(n); read(m); read(k);
            memset(h,0,sizeof(h));
            int jud = 1;
            for(int i = 1; i <= n; i++) {
                read(h[i]);
                if(i>=2) {
                    if(h[i-1]>=h[i]-k) {
                        int x = h[i-1]-h[i]+k;
                        int xx = min(x,h[i-1]);
                        m+=xx;
                        h[i-1] -= xx;
                    }
                    if(h[i]-h[i-1]>=k) {
                       int x = h[i] - h[i-1] - k;
                        h[i-1] = h[i] - k;
                        if(x>m) jud = 0;
                        m -= x;
                    }
                }
            }
            if(!jud)printf("NO\n");
            else printf("YES\n");
        }
    }
}

int main(){
    Sakii::main();
    return 0;
}


```


---

## 作者：Mubuky (赞：0)

# _**CF1200B Block Adventure 题解**_ 

![](https://api.gushi.ci/all.svg)

**首先分享一下做完这道题（ _Pretest Passed_ ）的感受:**

> 二维我的世界？？

当然了作为Div.2的A这么简单也无可厚非，并且这一次Div.2的ABC十分欢乐，D我又用动态规划刚了一发....然后...涨了Rating。

**题目大意（我作了翻译挂了上去）：**

这道题的意思很好理解，并没有什么坑的地方 **（雾** 。

**思路及解决方案：**

**贪心+模拟**

怎么贪心？

> 最优贪心（废话）

**贪心策略：保持背包内方块数量m最大。**

按照此策略，若遇见h[i+1]>h[i] && h[i+1]-h[i]>k，我们就需要向下垫方块以达到下一列，但如果h[i+1]>h[i] && h[i+1]-h[i]-m>k，即把背包内所有方块全部垫在脚下仍然不能达到下一列，但此时背包内方块数量已经是最大值，则说明一定无法赢得游戏。

**处理思路：如何保持背包内方块数量m最大？**

题目中表示只要两列高度差的绝对值在k的范围内就可以移动到下一列，我们不妨降低思维难度，分类讨论。

**1.若h[i]>=h[i+1]**

此时角色是平向/向下移动，我们为了保持背包内方块数量m最大,需要让m添加到不能再添加为止，即挖取脚下的方块放入背包，直到再挖取一个方块时，就会出现h[i]<=h[i+1] && h[i+1]-h[i]>k的情况。即挖取h[i]-h[i+1]+k个方块并放入背包中。

特殊情况：h[i]-h[i+1]+k>h[i],即通过上式计算的方块添加量大于第h列的方块数量h[i]，显然第i列的方块数量不能为负数，这是不合理的，此时背包中最多添加h[i]个方块。

```
if(h[i]>=h[i+1]){
	m+=min(h[i],h[i]-h[i+1]+k);
}
```

**2.若h[i]<h[i+1]**

此时角色是向上移动，我们可以继续分情况讨论：

(1)h[i]-h[i+1]=k

此时刚刚好可以移动到下一列，不需要用m进行任何操作。

(2)h[i]-h[i+1]\<k

与大情况1类似,我们为了保持背包内方块数量m最大,需要让m添加到不能再添加为止，即挖取脚下的方块放入背包，直到再挖取一个方块时，就会出现h[i]<h[i+1] && h[i+1]-h[i]>k的情况。即挖取k-(h[i+1]-h[i])个方块并放入背包中。

特殊情况：k-(h[i+1]-h[i])>h[i],即通过上式计算的方块添加量大于第h列的方块数量h[i]，显然第i列的方块数量不能为负数，这是不合理的，此时背包中最多添加h[i]个方块。

(3)h[i]-h[i+1]>k

使用背包中的方块垫在脚下，为移动至第i+1列铺路，每次花费背包中最少数量的方块，即达到h[i]-h[i+1]=k的情况，需要花费的方块数量为h[i]-h[i+1]-k。

特殊情况：若执行完该操作后m<0，说明背包内的方块数量全部垫在脚下后仍不足以使角色达到第i+1列，输出"NO"并结束这一组测试用例。

**讨论结束。**

若全部处理完成后没有输出"NO"，则说明可以达到第n列，输出"YES"。

**完整代码（时间复杂度O(n)）：**

```cpp
#include<cstdio>
#define min(a,b) ((a)<(b)?(a):(b))
int h[106];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m,k,pd=1;
		scanf("%d %d %d",&n,&m,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&h[i]);
		}
		for(int i=1;i<=n-1;i++){
			if(h[i+1]<=h[i]){
				m+=min(h[i],h[i]-h[i+1]+k);
			}else{
				if(h[i+1]-h[i]>k){
					m-=h[i+1]-h[i]-k;
					if(m<0){
						pd=0;
						break;
					}
				}else if(h[i+1]-h[i]<k){
					m+=min(h[i],k-(h[i+1]-h[i]));
				}
			}
		}
		printf("%s\n",pd?"YES":"NO");
	}
	return 0;
}
```

以上为分类讨论代码，降低了思维复杂度，但增加了时空常数。事实上我们处理每一组测试用例时并不需要如此复杂的多重判断，完全可以依照下面的英文题解中的式子直接处理。

**英文题解（出题人）：**

We can easily see that it's always optimal to have as many blocks as possible in the bag before getting to the next column. Therefore, if the character is currently on the top of the i-th column, Gildong just needs to make hi become max(0,hi+1−k) by repeating the 1-st or the 2-nd action. In other words, we should add hi−max(0,hi+1−k) blocks to the bag. Adding or subtracting one by one will lead to TLE. If there exists a situation where the bag will have negative number of blocks, the answer is NO. Otherwise the answer is YES.

 _**Name:** [Codeforces Round #578 (Div. 2)](http://codeforces.com/contest/1200)_ 

 _**Start:** Aug/11/2019 12:35UTC+8_ 

 _**Length** 02:00_ 

##  _**By Mubuky**_ 


---

