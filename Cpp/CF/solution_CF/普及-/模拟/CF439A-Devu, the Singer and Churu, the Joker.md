# Devu, the Singer and Churu, the Joker

## 题目描述

Devu is a renowned classical singer. He is invited to many big functions/festivals. Recently he was invited to "All World Classical Singing Festival". Other than Devu, comedian Churu was also invited.

Devu has provided organizers a list of the songs and required time for singing them. He will sing $ n $ songs, $ i^{th} $ song will take $ t_{i} $ minutes exactly.

The Comedian, Churu will crack jokes. All his jokes are of 5 minutes exactly.

People have mainly come to listen Devu. But you know that he needs rest of 10 minutes after each song. On the other hand, Churu being a very active person, doesn't need any rest.

You as one of the organizers should make an optimal sсhedule for the event. For some reasons you must follow the conditions:

- The duration of the event must be no more than $ d $ minutes;
- Devu must complete all his songs;
- With satisfying the two previous conditions the number of jokes cracked by Churu should be as many as possible.

If it is not possible to find a way to conduct all the songs of the Devu, output -1. Otherwise find out maximum number of jokes that Churu can crack in the grand event.

## 说明/提示

Consider the first example. The duration of the event is $ 30 $ minutes. There could be maximum $ 5 $ jokes in the following way:

- First Churu cracks a joke in $ 5 $ minutes.
- Then Devu performs the first song for $ 2 $ minutes.
- Then Churu cracks $ 2 $ jokes in $ 10 $ minutes.
- Now Devu performs second song for $ 2 $ minutes.
- Then Churu cracks $ 2 $ jokes in $ 10 $ minutes.
- Now finally Devu will perform his last song in $ 1 $ minutes.

Total time spent is $ 5+2+10+2+10+1=30 $ minutes.

Consider the second example. There is no way of organizing Devu's all songs. Hence the answer is -1.

## 样例 #1

### 输入

```
3 30
2 2 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 20
2 1 1
```

### 输出

```
-1
```

# 题解

## 作者：李至擎 (赞：4)

[点我看题](https://www.luogu.com.cn/problem/CF439A)

由题意可知，$Devu$唱一首歌要花$t[i]$分钟，而且他每唱完一首歌就要休息10分钟，所以他至少要有$\sum_{1}^{n}t[i] +10*(n-1)$分钟才能唱完所有歌。

而由于要使$Churu$讲的笑话尽量多，那么在除了$\sum_{1}^{n}t[i]$分钟的唱歌时间外，其余时间他都要拿来讲笑话，所以他总共可讲$(d-(\sum_{1}^{n}t[i] +10*(n-1)))/5$个笑话。

代码：

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int n,d,s,tim;//n,d如题意，s是唱歌总时间(不包括休息时间)，tim是唱当前这首歌的时间
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>tim;
		s+=tim;//总时间加上当前时间
	}
	if(s+(n-1)*10<=d)cout<<(d-s)/5;//时间足够
	else cout<<-1;//时间不够，输出-1
	return 0;
}
```

完成！！！

---

## 作者：封禁用户 (赞：1)

题目传送>>[CF439A](https://www.luogu.com.cn/problem/CF439A)  
### 题意简述：  
一个活动 $d$ 分钟，Devu 要在每唱一首歌休息 $10$ 分钟的前提下唱完 $n$ 首歌，每首歌用时已知，期间 Churu 每讲一个笑话 $5$ 分钟。如不能唱完所有歌输出 $-1$，否则输出最多讲笑话数。  
### 题目分析：  
时间很紧，而 Devu 每唱完一首歌就要休息 $10$ 分钟，如果仅他休息所需时间就大于等于活动时间，那么他必不能完成唱歌。如果活动时间足以使其休息之余还有空闲，那么我们再来考虑空闲是否足以支持其唱完所有歌，如能，我们便输出 Churu 能最多能讲多少笑话。Churu 除 Devu 台上唱歌时不能讲笑话，在 Devu 休息时和活动剩余时间都能不停地讲笑话（~~根本不用休息，卖力表演~~），即 Churu 能讲的笑话数为 $(d-\sum_{i=1}^{n}{t_i})/5$ 。    
### 问题解决：  
#### 判断：  
我们可以直接使用 if...else... 进行判断。当然，我们也可以使用一个小东西 —— 三目运算符 “?:”。  
例 ：a?b:c 的含义是：如果 a 为真，则表达式的值是 b，否则是 c。
### Code:  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int n,d,ti;   //定义歌数，活动时间，每首歌用时
	int dt=0,r;   //定义唱歌总用时，最终结果
	cin>>n>>d;
	if((n-1)*10>=d)   //如果仅他休息所需时间就大于等于活动时间，那么他必不能完成唱歌
	{
		cout<<"-1";   //直接输出不能完成
		return 0;   //直接结束整个程序
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			cin>>ti;
			dt+=ti;    //累加唱歌总用时
		}
	}
	r=(((n-1)*10+dt)>d)? -1:(d-dt)/5;	//利用三目运算符判断最终结果
	cout<<r;
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/kgff6tek.png)  
企鹅的题解到此结束，祝各位 OIers 进步++~

---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF439A)

这道题有很多未知条件，需要我们自己用代码求出来，我们一条一条来看。

------------
### 步骤

1. 计算出 ```Devu``` 歌唱的时间总和。

这一个条件相当重要，在后面的判断中，需要经常用到它。不然我们不知道他休息要多久，也不能算出 ```Churu``` 讲的笑话数量。

```
for(int i=1;i<=n;i++){
    cin >> a[i];
    sum+=a[i];
}
```

2. 计算 ```Devu``` 歌唱中的间隙总时间。

我们需要用这个时间来判断 ```Devu``` 是否唱得完他所有的歌。所以得用总时间加上他唱的歌曲的总数减一的差，最后不要忘了乘上它每次间隙的时间。

```if(sum+(n-1)*10<=m)```

3. 算出 ```Churu``` 的总笑话数。

这回第一步又派上大用场了。我们只需要用用总时间减去 ```Devu``` 歌唱的时间整除五就能得到答案。

```
cout << (m-sum)/5 << endl;
```


------------
### 完整 ```AC``` 代码:
```
#include<iostream>
using namespace std;
int a[110],n,m,sum;
int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        sum+=a[i];
    }
    if(sum+(n-1)*10<=m)cout << (m-sum)/5 << endl;
    else cout << -1 << endl;
    return 0;
}
```


---

## 作者：naroanah (赞：0)

非常显然的模拟题。

唱完所有歌的时间是$\sum\limits_{i=1}^nt_i$，中间有 $n-1$ 次休息，每次 10 分钟，所以最后的总用时就是 $Sum=\sum\limits_{i=1}^nt_i+(n-1)\times10$。

如果用时大于 $d$，输出 -1 即可。

如果小于 $d$，那么剩下的时间就可以用来讲笑话，答案就是 $\dfrac{n-Sum}{5}$ 。

---

## 作者：thomas_zjl (赞：0)

这道题并不是很难。

我们应该要从 $Devu$ 唱歌的时间来做题。

首先我们知道 $Devu$ 唱第 $i$ 首歌要 $t_i$ 分钟。

而他每唱完一首歌要休息 $10$ 分钟。

计算他的唱歌的总时间是 $t_1+t_2+…+t_n+(n-1)*10$ 分钟。

如果刚才那一串数字大于 $d$ 输出 $-1$。

如果小于 $d$ 那么 $Churu$ 能讲 $(d-(t_1+t_2+…+t_n))/5$ 个笑话。

接下来就是代码。

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,d;
	scanf("%d%d",&n,&d);
	int st=0;//因为t1+t2+t3+…tn在重复的出现，所以可以用st数组来代替。
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		st+=x;//用来加上ti。
	}
   //接下来用我刚才的式子来做题就可以了。
	if(st+(n-1)*10<=d)
		printf("%d",(d-st)/5);
	else
		printf("-1");
	return 0;
}

```


---

## 作者：k3v1n070828 (赞：0)

我们先要找出最优解的规律：

样例的解释给了蒟蒻我很大的帮助，通过解释（那里的英文应该是比较好理解的），可以发现每次当$Devu$休息时，$Churu$都可以讲两个笑话，唱歌休息期间能讲$(n-1)×2$个笑话。

另外一开始需要特判$Devu$是否能在规定时间内唱完所有的歌，如果不可以的话，就直接 输出1+return 0 。

还有一种情况一些同学们容易忘掉，那就是如果$Devu$唱完歌后还有很多时间，那么$Churu$则应该继续讲笑话，那么需要一个变量$sum$记录一下$Devu$的唱歌总时长，它的大小是：$(a[1]+a[2]+a[3]+...+a[n])+(n-1)×10$，所以Churu在剩下时间能讲的笑话总数是$sum/5$。

思路讲完，代码写出：
```cpp
#include<cstdio>//头文件
using namespace std;
int n,d;//歌的总数和总时间
int a[110];//记录每首歌时间的数组，数据范围是100
int sum;//唱歌总时间
int ans;//答案变量
int main(){
	scanf("%d%d",&n,&d);//输入
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);//循环输入每首歌的长度
		sum+=a[i];//在输入时顺便把sum中歌唱总时间记录
	}
	sum+=((n-1)*10);//两首歌之间的休息时间也算上
	if(sum>d)//特判是否能唱完所有歌
	{
		printf("-1\n");//如果不能，输出-1
		return 0;//结束程序
	}
	ans+=((n-1)*2);//休息期间的笑话总数
	ans+=((d-sum)/5);//唱完歌后的笑话总数，经过了上面的特判，肯定是非负数
	printf("%d\n",ans);//输出答案（养成结尾换行的好习惯）
	return 0;//结束程序
} 
```

然后就能AC了。

下次题解见，Bye~

---

## 作者：sysu_yzc (赞：0)

## 思路
由于Devu每次唱歌需要休息10分钟，且唱歌需耗时$\sum_{1}^{n}t[i]$分钟，所以Devu总共需耗时$10(n-1)+\sum_{1}^{n}t[i]$分钟。

要使Churu讲的笑话尽量多，则应该让Churu在Devu的休息时间讲笑话，且Devu唱完歌剩余的时间都让Churu讲笑话，则Churu可讲$2(n-1)+(n-10(n-1)-\sum_{1}^{n}t[i])/5$个笑话。

## 上代码
```cpp
#include<iostream>
using namespace std;
int t[110];
int main(){
    int n,d;
    cin>>n>>d;
    for(int i=1;i<=n;i++){
        cin>>t[i];
        d-=t[i];
    }
    d-=10*(n-1);
    if(d<0){
        cout<<-1;
        return 0;
    }
    cout<<(n-1)*2+d/5;
    return 0;
}
```

---

## 作者：CobaltChloride (赞：0)

```
#include<bits/stdc++.h>
using namespace std;
int n,d,a,i,j=-2;//歌的数量会比休息次数多1,为了计算方便,先初始化成-2
int main(){
	cin>>n>>d;
	d+=10;//道理同上
	for(i=1;i<=n;i++){
		cin>>a;
		d-=a+10;//消耗时间
		j+=2;//讲2个笑话
	}
	if(d<0) cout<<-1;//时间不够
	else{
		j+=d/5;//剩下的时间全讲笑话
		cout<<j;
	}
	return 0;
}
```

---

