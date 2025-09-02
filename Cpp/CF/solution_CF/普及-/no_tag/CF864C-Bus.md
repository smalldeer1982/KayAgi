# Bus

## 题目描述

A bus moves along the coordinate line $ Ox $ from the point $ x=0 $ to the point $ x=a $ . After starting from the point $ x=0 $ , it reaches the point $ x=a $ , immediately turns back and then moves to the point $ x=0 $ . After returning to the point $ x=0 $ it immediately goes back to the point $ x=a $ and so on. Thus, the bus moves from $ x=0 $ to $ x=a $ and back. Moving from the point $ x=0 $ to $ x=a $ or from the point $ x=a $ to $ x=0 $ is called a bus journey. In total, the bus must make $ k $ journeys.

The petrol tank of the bus can hold $ b $ liters of gasoline. To pass a single unit of distance the bus needs to spend exactly one liter of gasoline. The bus starts its first journey with a full petrol tank.

There is a gas station in point $ x=f $ . This point is between points $ x=0 $ and $ x=a $ . There are no other gas stations on the bus route. While passing by a gas station in either direction the bus can stop and completely refuel its tank. Thus, after stopping to refuel the tank will contain $ b $ liters of gasoline.

What is the minimum number of times the bus needs to refuel at the point $ x=f $ to make $ k $ journeys? The first journey starts in the point $ x=0 $ .

## 说明/提示

In the first example the bus needs to refuel during each journey.

In the second example the bus can pass $ 10 $ units of distance without refueling. So the bus makes the whole first journey, passes $ 4 $ units of the distance of the second journey and arrives at the point with the gas station. Then it can refuel its tank, finish the second journey and pass $ 2 $ units of distance from the third journey. In this case, it will again arrive at the point with the gas station. Further, he can refill the tank up to $ 10 $ liters to finish the third journey and ride all the way of the fourth journey. At the end of the journey the tank will be empty.

In the third example the bus can not make all $ 3 $ journeys because if it refuels during the second journey, the tanks will contain only $ 5 $ liters of gasoline, but the bus needs to pass $ 8 $ units of distance until next refueling.

## 样例 #1

### 输入

```
6 9 2 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6 10 2 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6 5 4 3
```

### 输出

```
-1
```

# 题解

## 作者：Ggsddu_zzy (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/CF864C)

#### 题目大意

一辆汽车从 $0$ 到 $a$ 往返 $k \div 2$ 次（也就是去算一次，回算一次）；原来有 $b$ 升油，每行驶一单位距离消耗一升油，在 $f$ 有加油站（可以加满油或者不加油）；问要加多少次油；若到达不了 $a$ 处，输出 $-1$ ；

#### 解题思路

要先判断是否能用 $b$ 升油走到加油站。

不能就永远到不了，直接结束了。

如果能：

以加油站为分点，将这段路分为两段；

第一段：

去：如果能不加油到终点再走回来，就不加油；否则就加油。

回：同理。

注意每次都要判断到加油站的距离不能小于零。

代码如下：

```cpp
int first(int a,int b,int f,int k) {
	for(int i=1; i<=k-1; i++) {
		if(i%2==1) {　　　　
			if(sum>=2*(a-f))sum-=2*(a-f);
			else {
				sum=b-2*(a-f);
				ans++;
				if(sum<0) {
					cout<<"-1";
					exit(0);
				}
			}
		} 
		else {
			if(sum>=2*f)sum-=2*f;
			else {
				sum=b-2*f;
				ans++;
				if(sum<0) {
					cout<<"-1";
					exit(0);
				}
			}
		}
	}
}
```

第二段：

与第一段同理。

注意每次也都要判断到加油站的距离不能小于零。

代码如下：

```c++
int second(int a,int b,int f,int k) {
	if(k%2==1) {
		if(sum<(a-f)) {
			sum=b-(a-f);
			ans++;
			if(sum<0) {
				cout<<"-1";
				exit(0);
			}
		}
	} 
	else {
		if(sum<f) {
			sum=b-f;
			ans++;
			if(sum<0) {
				cout<<"-1";
				exit(0);
			}
		}
	}
}
```

注意一个地方：

在这里
，`return 0` 就是退出这个函数，而不是返回这个程序，用 `exit(0)` 相当于在 `main` 里 `return 0`（感谢 [kuailedetongnian](https://www.luogu.com.cn/user/749392) 的提醒）。

[完整 AC 代码](https://www.luogu.com.cn/paste/qikb6q97)

---

## 作者：xiaoxiaoxia (赞：5)

# Part 1 题意分析
题意是有一条坐标 $0-a$ 的路，$f$（$0-a$ 之间）为加油点，车从 $0$ 出发，最多装 $b$ 升油，油耗为一单位一升。让车来回走，$0-a$，$a-0$ 都算一趟，求 $k$ 趟最少加油次数。
# Part 2 思路分析
这道题目其实根本没有任何算法，只要按照题目的意思进行模拟即可。首先判断能不能开到目的地，如果不能，直接退出。接着再分成两端，去的和来的，能不加油就不加油，迫不得已才加油，如果还没有到加油站就没油了，也是直接退出。
# Part 3 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a, b, f, k;//根据题目要求 
    cin>>a>>b>>f>>k;
    int len[10010];
    len[0]=f;//记录路程 
    for(int i=1;i<k;i++)
    {
        if(i%2==0)
        {
        	len[i]=f*2;
		}
        else
        {
        	len[i]=(a-f)*2;
		}
    }
    if(k%2==1)//路程是否回到原点 
    {
    	len[k]=a-f;
	}
    else//回到原点 
    {
    	len[k]=f;
	}
    int oil=b;//存储油量 
    int ans=0;//存储答案 
    for(int i=0;i<=k;i++)
    {
        if(oil<len[i])//油量不够，到不了了 
        {
            ans=-1;
            break;
        }
        if(i<k&&len[i]+len[i+1]>oil)//到达本次的终点（记住：本次旅程！！！），油量变满 
        {
            oil=b;
            ans++;
        }
        else if(i<k&&len[i]+len[i+1]<=oil)//走了一段路 
        {
            oil-=len[i];//油量变少 
        }
    }
    cout<<ans<<endl;//输出 
    return 0;
}
```


---

## 作者：yewanxingkong (赞：4)

怎么说呢，这题简单做法就是一个暴力模拟。

大概是 $O(k)$ 的复杂度，而且 $k$ 值范围比较小，完全可以按照题意模拟做。

比较麻烦的就是一些细节的处理，不理解的可以看下我的代码。

应该可以用数学做，但我懒得想了。。。

下面是代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
using namespace std;
int a,b,f,k,z,y,you,chu;
int mo=1000007;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
int main(){
	a=read();
	b=read();
	f=read();
	k=read();
	z=f;//左边路段的长度 
	y=a-f;//右边路段的长度 
	you=b-f;//走到加油站前面那一小段 
	if(you<0){
		cout<<"-1";
		return 0;
	}
	for(int i=1;i<=k-1;i++){//开始模拟 
		if(i%2==1)
			if(you>=2*y)you-=2*y;
			else{
				you=b-2*y;
				chu++;
				if(you<0){
						cout<<"-1";
						return 0;
				}
			}
		else
			if(you>=2*z)you-=2*z;
			else{
				you=b-2*z;
				chu++;
				if(you<0){
						cout<<"-1";
						return 0;
				}
			}
	}
	if(k%2==1){//最后还有一小段没走 
		if(you<y){
			you=b-y;
			chu++;
			if(you<0){
				cout<<"-1";
				return 0;
			}
		}
	}
	else
		if(you<z){
			you=b-z;
			chu++;
			if(you<0){
				cout<<"-1";
				return 0;
			}
		}
	cout<<chu;//输出答案 
	return 0;
}
```


---

## 作者：yutong_Seafloor (赞：2)

# [题目在这里 · CF864C Bus](https://www.luogu.com.cn/problem/CF864C) 
### 题目简要：
有一汽车要旅行，单向的就算一次旅行，在旅行中间有一个加油站，在加油站你可以选择加满，也可以选择忽略他，问可以完成他~~伟大的~~旅行吗？可以就告诉他需要加几次油，不能就输出 $-1$。
### 题意分析
那么他什么时候需要加油呢？终点和起点不能加油，所以他一旦错过了加油站，他就需要用剩下的油走两趟的路程（有可能是终点到加油站的两倍路程，也有可能是起点到加油站的两倍路程），如果不行走不到，就要加油，这属于简单的模拟题，~~前人之述已备矣~~。

**所以在这里提出一种改良方法：如果他满油的时候都无法走出双倍的距离，我们就可以提前判定他能不能走出这个双倍距离以判断是不是能完成旅行，这样不仅可以节约代码，还可以省时间，下面只需要看看油够不够，需不需要加油就可以了。**

## 代码 


```cpp 
#include<bits/stdc++.h>
using namespace std;
int a,b1,b2,f,k,ans,i,af;
int main()
{
	cin>>a>>b1>>f>>k;
	af=a-f;
	if(a==0)
	cout<<"0";
	//
	else
	
	if(2*f>b1 || 2*af>b1)
	cout<<"-1";
	else
	{
		b2=b1-f;
		for(i=1;i<=k-1;i++)
		{	
			if(i%2==1)
			
			if(b2>=2*af)
			b2-=2*af;
			else
			b2=b1-2*af,ans+=1;
			//
			else
			if(b2>=2*f)
			b2-=2*f;
			else
			b2=b1-2*f,ans+=1;
		}
		if(k%2==1)
			
		if(b2>=af)
		b2-=af;
		else
		b2=b1-af,ans+=1;
		//
		else
		if(b2>=f)
		b2-=f;
		else
		b2=b1-f,ans+=1;
		cout<<ans; 
	} 
	return 0;
}
``` 

**这里要注意几个点：**
1. 他到加油站时没有油了的这种情况是可以存在的，因此写的时候是可以取等的。
2. 最后一次返程是一个单程，所以不用乘 $2$。

有错望指出，求审核大大过。

---

## 作者：王炸拆开打 (赞：2)

这是一道~~简单的~~模拟题，两分钟出思路，两天AC QAQ

前面的几位大佬代码稍稍长了点，我的思路稍微短一点

请dalao们指教

# 核心思想：模拟+贪心+特判
## 重要思想：把整个路线拉成一条
**模拟：模拟一段一段的来回路程**

**贪心：油不够去下一个地方再加**

**特判：见下方代码**


------------


**一、数组解释**： 

$use[2]$——这是一个非常巧妙的 _magic_ 数组

通过阅读程序可知，每一段路程的加油站是在有规律的变化的，奇数路段距离加油站距离为$f$，而偶数为$a-f$

$use[1]=f;use[0]=a-f;$则use[i%2]表示当前距离

------------
**二、代码解释**
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a,b,f,k,sum=0,use[2];//数组以及变量 
int main(){
	scanf("%d%d%d%d",&a,&b,&f,&k);
	int oil=b;//油加满，再上路 
 	use[0]=a-f;use[1]=f;//magic数组 
	for(int i=1;i<=k;i++){
		if(oil<use[i%2]){printf("-1");return 0;}//油不够了 
		if(i==k&&oil>=a){printf("%d",sum);return 0;}//最后一段，油够到达终点 
		if(i==k&&k!=1&&oil<a){printf("%d",sum+1);return 0;}//最后一段，且不只是一段，如果oil不够，那就在本段加油（sum++） 
		oil-=a;//走完一段的油减掉 
		if(oil<use[1-i%2]){//如果剩下的油不够去下一个加油站 
			oil=b-use[1-i%2];//加满后减掉到达下一段路起点的路程 
			sum++;
		}
		if(i==k&&oil<0){printf("-1");return 0;}//如果最后一段路加油后,油还是负的，那就算了吧 
	}
	printf("%d",sum);
	return 0;
}
```



---

## 作者：Phoenix_chaser (赞：2)

# 讲一讲思路
### 这是一道需要经过贪心处理的模拟题
#### 根据题意可得本题是来回往返
#### 求最少加油次数
但直接处理不太好解决，这边我们可以直接把来回往返 _**拉长成一条直线**_

拿样例一**举例**

##### 注：黑色为往返点，红色为加油站

![](https://cdn.luogu.com.cn/upload/image_hosting/zzow5qld.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（这里需要一个值得注意的地方是 _**往返的加油站位置不同**_ ）

接下来就是核心部分：

每次枚举它的位置，和油量，同时在进入加油站时进行一个**判断**：

#### 看它现在到达加油站的油量是否满足可以走到下一个加油站

如图中从2加油站到10加油站

当到2这个加油站时油量只有9-2=7

所以要进行加油，这样才可以到达下一个站

如果油量 _**大于到下一个站的消耗量**_ ，则不加油

 _**反正能到下一个加油站，那就到下一个再加**_ 

这样便可以尽可能让加油次数最小

代码就不放了，太丑了见谅

## 谢谢观看
完结




---

## 作者：wzkdh (赞：1)

一道挺有意思的模拟。



------------
第一眼看到本题，首先想到的是数学方法，不过奈何本人既没耐心也不擅长，所以直接跳过，毕竟计算机就是用来做大量计算的，要我们人来找规律干嘛（~~就是强行找菜的理由~~）

其实这道题用模拟写还是挺好的，能锻炼对细节的把握能力，此题在某些情况的处理还是很考验细节的。

具体情况请看代码注释，模拟题不好干讲（我太蒟蒻了）

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int a,b,c,d,ans;
int main()
{
	scanf("%d%d%d%d",&a,&b,&c,&d);
	int l=c,r=a-c,fx=1,hy=l,cs=0;
    //l表示从左走到加油站所需要的距离
    //r表示从右走到加油站所需要的距离
    //fx表示当前方向，1为向右，0为向左
    //hy表示当前汽车的油耗
    //cs表示已经走了多少来回
	if(!a)
	{
		printf("0");
	}
	if(b<l)
	{
		printf("-1");
		return 0;
	}//如果车开始从左跑不到加油站，直接gg
	while(1)
	{
		if(cs==d-1)
		{
			break;
		}//当车走完d-1次之后，直接跳出循环判断最后半个路程
		if(fx)
		{
			if(2*r>b)
			{
				printf("-1");
				return 0;
			}//如果车的油箱不足以跑到右端再回来，gg
			if(hy+2*r<=b)
			{
				hy+=2*r;
				cs++;
				fx=0;
			}//能不加油跑回来，就增加油耗，更改方向
			else
			{
				hy=0;
				ans++;
			}//油不够了，加油
		}
		else
		{
			if(2*l>b)
			{
				printf("-1");
				return 0;
			}
			if(hy+2*l<=b)
			{
				hy+=2*l;
				cs++;
				fx=1;
			}
			else
			{
				hy=0;
				ans++;
			}//向左时的情况，同上方向右
		}
	}
	if(fx)//判断最后半程
	{
		if(b<r)
			printf("-1");
        //一开始我这里犯了个错误，以为不需要判断这个
        //后来发现当d==1时，不会进循环，能不能到右端要在这里判断
		else if(hy+r<=b)
			printf("%d",ans);
		else
			printf("%d",ans+1);	
	}
	else
	{
		if(hy+l<=b)
			printf("%d",ans);
		else
			printf("%d",ans+1);	
	}//如果最后向左就不需要上面向右时的判断了
    //因为如果最后是向左的，一开始必定要先从左跑到加油站，就必定能跑回来
	return 0;
}

---

## 作者：ivyjiao (赞：1)

这道题时间限制是两秒，说明暴力 $O(k)$ 模拟是可以过的。

这个汽车是有去程和返程的，去程和返程是不一样的。

具体的，当 $i$ 为奇数时，汽车是去程；$i$ 为偶数时，汽车是返程。

**注意：到加油站的时候如果油正好用完，不算失败。**

```cpp
#include<cstdio>
using namespace std;
int a,b,f,k,ans,bb,z,y,kk;
int main(){
    scanf("%d %d %d %d",&a,&b,&f,&k);
    bb=b;
    z=f;//左边路段
    y=a-f;//右边路段
    bb=b-f;//先走了左边路段
    if(bb<0){
        printf("-1");
        return 0;
    }
    for(int i=1;i<k;i++){//开始模拟！
        if(i%2==1){//如果是去程
            if(bb>=2*y){//要注意的地方
                bb-=2*y;
            }
            else{
                bb=b-2*y;
                ans++;
                if(bb<0){
                    printf("-1");
                    return 0;
                }
            }
        }
        else{//如果是返程
            if(bb>=2*z){
                bb-=2*z;
            }
            else{
                bb=b-2*z;
                ans++;
                if(bb<0){
                    printf("-1");
                    return 0;
                }
            }
        }
    }
    if(k%2==1){//最后一段路程要特判
        if(bb<y){
			bb=b-y;
			ans++;
			if(bb<0){
				printf("-1");
				return 0;
			}	
		}
    }
    else{
        if(bb<z){
       	 bb=b-z;
			ans++;
			if(bb<0){
				printf("-1");
				return 0;
			}
		}
    }
    printf("%d",ans);
}
```


---

## 作者：Not_lazy (赞：0)

### [题目](https://www.luogu.com.cn/problem/CF864C)

## 1.Ideas
这是一道十分~~正统~~的模拟题，判断比较复杂。

时间 $2$ 秒，所以暴力模拟时间复杂度 $O(k)$ 是可以过的。

这个汽车是有去程和返程的，去程和返程是不一样的。

具体的，当 $i$ 为奇数时，汽车是去程；$i$ 为偶数时，汽车是返程。

**但是，如果汽车到了加油站刚好没有也是可以的。**

**Tip：循环要写循环到 $k-1$，因为最后一个来（回）的加油站到终点的一小段路我们得拿出来，分别考虑。**

## 2.Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,ans;
int main(){
	scanf("%d %d %d %d",&a,&b,&c,&d);
	int x=c,y=a-c,z=1,h=x,w=0;
	if(!a)printf("0");
	if(b<x){
		printf("-1");
		return 0;
	}
	while(1){
		if(w==d-1)break;//当车走完d-1次之后，直接跳出循环判断最后半个路程
		if(z){
			if(2*y>b){
				printf("-1");
				return 0;
			}//如果车的油箱不足以跑到右端再回来
			if(h+2*y<=b){
				h+=2*y;
				w++;
				z=0;
			}//能不加油跑回来，就增加油耗，更改方向
			else{
				h=0;
				ans++;
			}
		}
		else{
			if(2*x>b){
				printf("-1");
				return 0;
			}
			if(h+2*x<=b){
				h+=2*x;
				w++;
				z=1;
			}
			else{
				h=0;
				ans++;
			}
		}
	}
	if(z){
		if(b<y)printf("-1");
		else if(h+y<=b)printf("%d",ans);
		else printf("%d",ans+1);	
	}
	else{
		if(h+x<=b)printf("%d",ans);
		else printf("%d",ans+1);	
	}
	return 0;
}
```





---

## 作者：Deamer (赞：0)

这道题是一个模拟题。
# 我们考虑：

如果想让加油的总次数最小，我们就要让每次加油后跑的尽可能远，所以我们能先不加油就先不加油，等到迫不得已再加油，这样加油的总次数就尽可能小了，好像有点像贪心的思路。

我们对于每个来（回）分别考虑加不加油的情况就行了，时间复杂度大约是 $O( k )$ 的。


**~~reader : talks are cheap , show me the code !!!~~**

接下来就是一些边界及细节的处理，详细注释放代码里了。

 _**code:**_ 
 
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,f,k;
int l,r,y;
int ans;
int main(){
	scanf("%d%d%d%d",&a,&b,&f,&k);
	if(b<f){						//如果到不了加油站，就更到不了终点了，直接-1。
		printf("-1\n");
		return 0;
	}
	l=f,r=a-f,y=b-f;
	//l是从起点到加油站的距离，r是加油站到终点的距离，y表示还剩多少油。
	//我们前面已经确认了从起点能到加油站，所以我们直接默认到了加油站，故y=b-f，接下来对于每个来（回）我们都以加油站为中界点，分别考虑加油和不加油的情况。
	for(int i=1;i<=k-1;i++){
		if(i&1){					//等同于 i%2==1。
			if(y>=2*r) y-=2*r;		//如果剩下的油能从加油站到终点，回来还能到加油站，最优肯定不先加油。
			else{					//不能撑到再回来到加油站，我们就必须加油。
				y=b-2*r;		
				ans++;
				if(y<0){			//加了油都不能撑到再回来到加油站，直接-1。
					printf("-1\n");
					return 0;
				}
			}
		}
		else{						//思路同上
			if(y>=2*l) y-=2*l;
			else{
				y=b-2*l;
				ans++;
				if(y<0){
					printf("-1\n");
					return 0;
				}
			}
		}
	}
	//最后加油站到终点的一小段路我们得拿出来，分别考虑，请读者自己思考。
	if(k&1){
		if(y<r){					//剩下的油不够到终点，就得再加一次油。
			y=b-r;
			ans++;
			if(y<0){				//加了油都不能到终点，直接-1。
				printf("-1\n");
				return 0;
			}
		}
	}
	else{
		if(y<l){					//思路同上。
			y=b-l;
			ans++;
			if(y<0){
				printf("-1\n");
				return 0;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

最后提几个可能错的点吧：

- 循环要写循环到 ```k-1``` ，因为最后一个来（回）的加油站到终点的一小段路我们得拿出来，分别考虑。

- 记得分清 $l$ 和 $r$ 。

[完结撒花！！！](https://www.luogu.com.cn/record/76314151)


---

