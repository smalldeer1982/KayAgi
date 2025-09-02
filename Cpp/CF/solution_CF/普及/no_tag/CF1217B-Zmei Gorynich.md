# Zmei Gorynich

## 题目描述

You are fighting with Zmei Gorynich — a ferocious monster from Slavic myths, a huge dragon-like reptile with multiple heads!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1217B/7c3f181294cd1faa21453100051e900a119a772c.png)Initially Zmei Gorynich has $ x $ heads. You can deal $ n $ types of blows. If you deal a blow of the $ i $ -th type, you decrease the number of Gorynich's heads by $ min(d_i, curX) $ , there $ curX $ is the current number of heads. But if after this blow Zmei Gorynich has at least one head, he grows $ h_i $ new heads. If $ curX = 0 $ then Gorynich is defeated.

You can deal each blow any number of times, in any order.

For example, if $ curX = 10 $ , $ d = 7 $ , $ h = 10 $ then the number of heads changes to $ 13 $ (you cut $ 7 $ heads off, but then Zmei grows $ 10 $ new ones), but if $ curX = 10 $ , $ d = 11 $ , $ h = 100 $ then number of heads changes to $ 0 $ and Zmei Gorynich is considered defeated.

Calculate the minimum number of blows to defeat Zmei Gorynich!

You have to answer $ t $ independent queries.

## 说明/提示

In the first query you can deal the first blow (after that the number of heads changes to $ 10 - 6 + 3 = 7 $ ), and then deal the second blow.

In the second query you just deal the first blow three times, and Zmei is defeated.

In third query you can not defeat Zmei Gorynich. Maybe it's better to convince it to stop fighting?

## 样例 #1

### 输入

```
3
3 10
6 3
8 2
1 4
4 10
4 1
3 2
2 6
1 100
2 15
10 11
14 100
```

### 输出

```
2
3
-1
```

# 题解

## 作者：knsg251 (赞：3)

## 题目大意
王子有几个技能问最少释放几次能砍掉所有头
## 题目分析
一共三种情况
*   永远杀不死，也就是技能砍掉的数量小于长出来的数量
*	 一个技能直接砍掉所有的头
*	 正常情况，一直释放技能直到杀死怪兽。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,x,ans,maxn;
int d[105],h[105];
int main(){
    cin>>t;
    while(t--){
        scanf("%d%d",&n,&x);
        ans = -9999;
		maxn = -9999;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&d[i],&h[i]);//输入第i个技能释放后打掉的和新长的数量
            ans = max(ans,d[i] - h[i]);//计算第i个技能释放后一共打掉的头的个数 
            maxn = max(maxn,d[i]);//特判：一个技能能否直接杀死 
        }
        if(maxn >= x){
            cout<<"1"<<endl;//一刀秒 
        }else if(ans <= 0){
            cout<<"-1"<<endl;//永远杀不死 
        }else{
            cout<<(x - maxn + ans - 1) / ans + 1<<endl;//最少技能计算公式 
        }
    }
    return 0;//over
}
```

---

## 作者：qpzc (赞：2)

题意还是很好理解的，这里主要讲一下思路：

和蜗牛爬井问题类似，当最后一次将 $x$ 个头全部砍完时恶龙就**不会再长出新的头**了。所以如果能一次砍完就一定用 $d_i$ 最大的招数，否则就用 $d_i-h_i$ 最大的招数。所以答案为 $\lceil \frac{x-max(d_i)}{max(d_i-h_i)} \rceil+1$。

还要注意几点：

- 如果能一次砍完就直接输出 $1$。
- 如果 $d_i-h_i \le 0$，那砍不完恶龙的头，输出 $-1$。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
		int t; cin>>t;
		while(t--){
			int n,x,mx1=-1e9,mx2=-1e9;//mx1记录最大的di，mx2记录最大的di-hi
			cin>>n>>x;
			while(n--){
				int d,h; cin>>d>>h;
				mx1=max(mx1,d),mx2=max(mx2,d-h);//更新最大值
			}
			if(mx1>=x){puts("1");continue;}
			if(mx2<1){puts("-1");continue;}
			cout<<ceil((x-mx1)*1.0/mx2)+1<<endl;
		}
		return 0;
}
```

---

## 作者：Dreamerly (赞：1)

## 题目：[CF1217B](https://www.luogu.com.cn/problem/CF1217B)
## 思路：
理解题意，明显贪心。

首先，既然技能可以无限使用，那我们每次都用 $d_i - h_i$ 最大的，保证一次能减少最多的头。

但是，有几个点需要特判。

1. 若 $\left(d_i - h_i\right) \max\leq 0$，说明一次操作下来，恶龙的头根本没少，则无论如何都杀不死它了。
1. 若 $x-d_i\max$ 大于总头数，即可一刀秒杀。

最后，根据我们的贪心思路，只要能一刀砍死的就用 $d_i\max$ 砍，否则用 $\left(d_i - h_i\right) \max$ 去砍。即最后用公式 $\ulcorner \dfrac{x-d_i\max}{\left(d_i-h_i\right)\max} \urcorner + 1$ 一定能保证技能使用次数最少。
## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
}
void write(int x){ 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
signed main(){
	int T=read();
	while(T--){
		int n=read(),x=read();
		int sk_max; //一次能砍掉最多的头 
		int k_max;  //一次能减少最多的头 
		sk_max=k_max=-1;
		
		for(int i=1;i<=n;i++){
			int a=read(),b=read();
			sk_max=max(sk_max,a);
			k_max=max(k_max,a-b);
		}
		if(sk_max>=x){
		  	write(1),printf("\n");
			continue;
		}
		
		if(k_max<=0) write(-1);
		else         write(ceil(1.0*(x-sk_max)/k_max)+1); //减去秒杀的一步，剩下的头每次砍掉 k_max 个     
		printf("\n");
	}
	return 0;
}
```


---

## 作者：xiaoqian02 (赞：1)

~~恕我直言，这道题绝对没有绿，橙题封顶。~~

很显然，最后一次砍完之后就不会重新长出来了。因此，最后一次一定用砍掉最多的招式（注意与长出来没有关系）。

因为这道题招式可以重复用，那每次肯定都用最强的，也就是 $d_i - h_i$ 最大的。

注意本题有两个特判：

**1.** 如果用一次砍最多的能直接把恶龙干掉，那就直接用。

**2.** 如果最强的招式都会使恶龙头数一直不变或不减反增，那很遗憾，干不死，直接输出 ```-1``` 退出。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,x,n,kkk,maxx,maxx2,w[105];//怕被卡 int，实际没啥用
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);//这两句都是优化 cin，经实测比 scanf 快
    cin>>T;
    while(T--)
    {
        cin>>n>>x;
	maxx=maxx2=-1;
	for(ll i=1;i<=n;i++)
	{
	    cin>>w[i]>>kkk;
	    maxx=max(maxx,w[i]);
	    w[i]-=kkk;
	    maxx2=max(maxx2,w[i]);
	}
	if(x<=maxx)//特判
	{
	    cout<<1<<endl;
	    continue;
	}
	x-=maxx;
	if(maxx2<=0) cout<<-1<<endl;//还是特判
	else cout<<(long long)(ceil(1.0*x/maxx2)+1)<<endl;//公式
    }
    return 0;
}
```
蒟蒻第一次发题解，希望大家支持。

注：码风奇丑勿喷。

---

## 作者：兮水XiShui丶 (赞：1)


~~这么可爱的怪兽我怎么可能忍心去打它呢~~  

我们看到题,首先想到,如果我们砍一刀,这个怪兽不死,那么它如果长出来的头大于我们我们这次砍掉的头.那么我们这次的操作显然没用.所以,在前几刀砍不死怪兽的情况下,我们需要最大化每一次砍头时的$d_i-h_i$,同时我们发现.在某一次砍头中,如果这次的$d_j$非常大,大到一下子可以把怪兽剩下的头砍完.我们就可以不用管这次砍头的副作用$h_j$了.  

所以我们维护两个最大值,即$d_i-h_i$的最大值以及$d_i$的最大值,然后直接找题意做即可.

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int maxs=-1e16;
		int Damage=-1e16;
		cin>>n>>x;
		for(int i=1;i<=n;i++) {
			int tx,ty;
			cin>>tx>>ty;
			maxs=max(maxs,tx);
			Damage=max(Damage,tx-ty);
		}
		if ( x <= maxs ) {
			cout << "1" << endl;
			continue;
		}			
		
		if(Damage<=0){
			cout<<"-1"<<endl;
			continue;
		}
	
		int now = ( x - maxs ) / Damage;
		if ( now * Damage < x - maxs ) 
			now+=2;
		else 
			now++;
		cout<<now<<endl;
	}
	return 0;
} 
```

---

## 作者：Helium_Ship (赞：0)

我们首先考虑对于最后一刀并不会增加怪物的头数，所以就选用一个 $d_i$ 值最大的即可，而剩下的 $n-max{d_i}$ 个头数，因为会增加，所以我们考虑用 $max{d_i-h_i}$ 去砍。

对于能够一刀秒的情况直接输出 $1$。

当 $max{d_i-h_i}$ 为负数的情况下会出现无解，我们直接输出 $-1$。

剩下的情况则直接输出 $\lceil\frac{n-max{d_i}}{max{d_i-h_i}}\rceil+1$。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,x,max1,max2;
struct node{
	long long d,h;
}a[110];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while (T--){
		cin>>n>>x;
		max1=max2=-1e9;
		for (int i=1;i<=n;i++){
			cin>>a[i].d>>a[i].h;
			max1=max(max1,(a[i].d-a[i].h));
			max2=max(max2,a[i].d);
		}
		if (x<=max2)cout<<1<<'\n';
		else if (max1<=0)
			cout<<-1<<'\n';
		else cout<<(x-max2)/max1+((x-max2)%max1?1:0)+1<<'\n';
	}
	return 0;
}
```

---

## 作者：开始新的记忆 (赞：0)

题目大意：现在你要刷怪，这个怪物有x点血，你有n个技能，每个技能都会先扣掉怪物di点血，然后再回hi点血，如果在任意时刻怪物的血小于等于0就算死亡，问你最少用多少个技能才能让怪物死亡，如果不行就输出-1.

大致思路：每次打怪要用的就两个技能：1.di最高的技能。2.di-hi最高的技能。我们处理出来后可以进行一下判断：如果目前x>dmax且(d-h)max<=0那么就是-1，反之就先用第二个将怪物打到刚好大于di的血量然后再用di攻击即可


```
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
struct Node{
    int x;
    int y;
} a[10005];
 
int main()
{
	cin>>t;
    while(t--)
	{
        cin>>n>>m;
        int maxn=0,maxx=-0x7fffffff;
        for(int i=1,x,y;i<=n;++i)
		{
            cin>>x>>y;
            maxn=max(maxn,x);
            maxx=max(maxx,x-y);
        }
        if(maxn>=m)
		{
            cout<<1<<endl;
            continue;
        }
        if(maxx<=0)
		{
            cout<<-1<<endl;
            continue;
        }
        int ans=(m-maxn+maxx-1)/maxx;
        cout<<ans+1<<endl;
    }
	return 0;
}
```


---

## 作者：big_news (赞：0)

题目大意：
有一条恶龙，初始血量是x，你现在要用n种技能把它砍死。第i种技能会砍掉di点血量，并使恶龙回复hi点血量。当恶龙的血量⩽0时就认为它死了，问你最少需要放多少次技能才能把它砍死（技能可以重复用），砍不死输出-1。**题目有多组数据。**

贪心策略：每次用能减少的头的数量(di-hi)最多的那个技能去砍，然后每次砍之前，看看现在能不能用伤害最高的技能直接把它砍死。但是，这样写的话复杂度不够优秀，实际上可以把这个过程反过来：先用伤害最高的技能砍一次，然后再用减少头的数量最多的技能一次一次的去砍，这样就可以直接做除法了。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

#define LL long long

int main()
{
    int t;
    scanf("%d",&t);

    while(t--){
        int n,x;
        scanf("%d%d",&n,&x);
       
        int hack = 0,max_hit = 0;
        for(int i=1;i<=n;i++){
            int a,b;
            scanf("%d%d",&a,&b);
            hack = max(hack, a-b);
            max_hit = max(max_hit, a);
        }
        
        if(!hack && max_hit<x){ //砍不死
            printf("-1\n");
            continue;
        }

        x -= max_hit;
        int times = 1;
        if(x > 0){
            int cnt = x/hack;
            if(x % hack) cnt += 1; //上取整
            times += cnt;
        }

        printf("%d\n",times);
    }
    
    return 0;
}
```

---

## 作者：弦巻こころ (赞：0)

题意:一条恶龙有$x$的生命值,你的第$i$种攻击可以对它$d_i$的伤害,
但在这过后它会恢复$h_i$点生命值,需要注意的是,如果你打死了它.它便不会再恢复生命值了. 现在你可以进行无数次每种攻击,问你最小需要砍几刀.

我们用一个简单的贪心就可以解决问题,由于每种攻击可以进行无数次,我们就先减去伤害值最大的一次攻击(最后一击),在进行 伤害-生命值 后攻击最大的一击就行了. ~~(然而丢人的我还被人叉了艹)~~

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
struct att
{
	long long d,h,num;
}a[1005];
long long n,ans,x,max1,max2;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		scanf("%d%I64d",&n,&x);
		ans=0;
		max1=-1e9,max2=-1e9;
		for(int i=1;i<=n;i++)
		{
			scanf("%I64d%I64d",&a[i].d,&a[i].h);
			a[i].num=a[i].d-a[i].h;//设这个为攻击力
			max1=max(a[i].d,max1);//最后一击(伤害值最大)
			max2=max(a[i].num,max2);//其它时候的攻击(攻击力最大)
		}
		x-=max1;
		x=max(0ll,x); 
		ans+=1;
		if(x==0)//这里要加特判,不然会RE
		{
			printf("1\n");
			continue;
		}
		if(max2<=0&&x!=0)
		{
			printf("-1\n");
			continue;
		}
		
		ans+=ceil(1.0*x/max2);//要取ceil值.
		printf("%I64d\n",ans);
	}
}

```
后记: 刚刚看发现rating涨了40+,这还是在这道题被叉了情况下,如果不被叉就上蓝了 CF你还我rating 

---

