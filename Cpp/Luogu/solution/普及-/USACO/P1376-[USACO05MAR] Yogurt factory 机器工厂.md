# [USACO05MAR] Yogurt factory 机器工厂

## 题目描述

小 T 开办了一家机器工厂，在 $N$个星期内，原材料成本和劳动力价格不断起伏，第 $i$ 周生产一台机器需要花费 $C_i$ 元。若没把机器卖出去，每保养一台机器，每周需要花费 $S$ 元，这个费用不会发生变化。

机器工厂接到订单，在第 $i$ 周需要交付 $Y_i$ 台机器给委托人，第 $i$ 周刚生产的机器，或者之前的存货，都可以进行交付。

请你计算出这 $n$ 周时间内完成订单的最小代价。

## 说明/提示

$1\leq n\leq 10^4$，$1 \le C_i \le 5000$，$1 \le S\le 100$，$0\le Y_i\le 10^4$。

## 样例 #1

### 输入

```
4 5
88 200
89 400
97 300
91 500
```

### 输出

```
126900
```

# 题解

## 作者：Jason224413 (赞：61)

很简单的一道题，时间O（n）,空间O（1），注意ans用long long！否则会错。并且注意循环的其实值！！！

```cpp
#include<iostream>
using namespace std;
int main()
{
    int c,y;
    long long n,ans=0;
    int k,lastweek;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>c>>y;
        if(i==1) lastweek=c;
        else lastweek=min(lastweek+k,c);
        ans+=lastweek*y;
    }
    cout<<ans;
    //system("pause");
    return 0;
}

```

---

## 作者：Ar_HomeTree (赞：28)

# 本蒟蒻第二次发题解谢谢.
本方法主要采用的就是贪心,
找到最小的价值.来进行购买
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int min(int x,int y)//比较函数,懒得写头文件
{
    return x>y?y:x;//三目运算符,解释下如果x>y为ture,则返回y,反之x.
}
int main()
{
    //freopen("c.in","r",stdin);
    //freopen("c.out","w",stdout);//测试很好用,文件调用
    int n,s;
    int c,y;
    long long  ans,sum=0;
    cin>>n>>s;
    cin>>c>>y;//第一个入读,特殊处理,由于前面没有生产机器
    ans=c;
    sum+=ans*y;
    for(int i=1;i<n;i++)
    {
        cin>>c>>y;
        ans=min(ans+s,c);//和之前的价值+维修费与现状的价钱比较,找小的
        sum+=ans*y;//计算
    }
    cout<<sum;
    return 0; 
} 

```
谢谢,求赞.

---

## 作者：花千树 (赞：18)

本题思路：在线做，超短代码，所谓在线，他的精髓就在**边读边做**四个字上，不知道其他dalao有没有用，反正本人自认为我的思路很奇葩（应该是特别），dalao可以跳过，在线主要是适用于刚学的萌新使用（可能都不知道数组是啥），比较好理解

话不多说，上代码！！！！！！！

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long ans,sum,tmp,f,n,s;//记得开long long，不然爆
int main(){//过程华丽开始
    scanf("%lld%lld",&n,&s);//这两个其实可以不用%lld，但是用了保险一点，不易错
    scanf("%d%d",&sum,&tmp);//先把第一个单独做了，就它例外
    ans+=sum*tmp;//必须直接生产，别无他法
    f=sum;//这是一个存最小数的变量，这就是贪心，新手自动理解为min
    for(int i=2;i<=n;i++){//开始循环，边读边做
        scanf("%d%d",&sum,&tmp);//在线读入
        if(f+s<sum)f=f+s;//判断f+s是否比当前值小，如果小，就不变，加一个s维修费
        else f=sum;//如果大就用当前值做
    ans+=f*tmp;
    }
    printf("%lld\n",ans);//完美输出
    return 0;//过程华丽结束
}

```

---

## 作者：EarthGiao (赞：13)

## 【思路】 
贪心   
这个题很好想    
枚举到了第i月，如果前面有某一个月     
制造出机器的成本 + 到达第i天保养得花费    
是小于在第i个月直接造出来花费的成本的    
那就可以替换掉    
所以这就很显然了吗    
直接从第一个开始枚举    
记录目前建造机器需要花费的最小值    
不过这个最小值是每过一个月就需要加上s      
这个时候在和枚举到的那个月份需要造一台机子花费    
比较一下    
还是记录最小的    

通过上面    
我们可以求出每个月份的造价最低是多少    
这样就可以求出总共的最优解     
注意需要开long long 哦    

## 【完整代码】

```cpp
#include<iostream>
#include<cstdio>

using namespace std;
int c,y;
long long ans = 0;
int main()
{
	int n,s;
	cin >> n >> s;
	int last;
	for(int i = 1;i <= n;++ i)
	{
		cin >> c >> y;
		if(i == 1)last = c;
		else	last = min(last + s,c);
		ans += last * y;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：KesdiaelKen (赞：10)

注意到了数据范围吗：n<=10000，说明是可以n^2过的！

对于每一个星期，枚举它前面所有的星期，找到使价格最小的一个星期，得到最小的钱数，然后让sum加上它。然后枚举所有的星期，此题便做完了。

然后要注意一下常数优化，不然会被卡90分。

下为代码：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;
long long c[20000],y[20000]={0};
long long shu;
char ch;
inline int dy()//读优函数
{
    shu=ch=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))shu=shu*10+ch-'0',ch=getchar();
    return shu;
}
int main()
{
    int n=dy();
    long long s=dy();
    for(int i=1;i<=n;i++)c[i]=dy(),y[i]=dy();
    long long sum=0;
    long long minn;
    for(register int i=1;i<=n;i++)//register加速
    {
        minn=2e18;//初始化为inf
        for(register int j=1;j<=i;j++)minn=min(minn,c[j]*y[i]+s*y[i]*(i-j));//枚举前面所有的星期
        sum+=minn;//加上最小值
    }
    printf("%lld",sum);//输出
    return 0;
}
```

---

## 作者：My_666 (赞：5)

#  蒟蒻第一次发题解

------------
##  贪心：
求出制造每周机器的最小单价（制造费＋保养费）。

**ps：数据范围n < 10000, 用枚举可以过的。**


#### 代码如下：
```cpp
#include <bits/stdc++.h> 

using namespace std;

typedef long long ll; //做题的好习惯 （本题不开long long会爆） 

ll n, s, ans;

ll c[1000000], y[1000000];
ll dj[1000000]; // 制造第i周机器的最小单价

int main() {
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> c[i] >> y[i];
        dj[i] = c[i];  //先赋值，便于下面计算最小单价 
    }
    //枚举所有可能的制造单价，取最小值 
    for (int i = 1; i <= n; i++) { //从第i天制造机器 
        for (int j = i; j <= n; j++) {
            dj[j] = min(dj[j], c[i] + s * (j - i));//到第j天的单价
            //s * (j - i)是每机器从第i天保养到第j天的保养费； 
        }
    }
    for (int i = 1; i <= n; i++) {
        ans += dj[i] * y[i]; //单价乘上数量当然是最后结果了！ 
    }
    cout << ans;
    return 0;
}
```
------------
# 感谢！


---

## 作者：yzx4188 (赞：4)

### 这只是一道简单的贪心题

本篇题解为蒟蒻专用，各位dalao可以自行跳过（~~不过我估计dalao们也不会看题解~~）


```cpp
#include<bits/stdc++.h>//万能头万岁！！！
using namespace std;
int n,s,c[10101],y[10101];//这几个可以不开long long 
long long ans;//忘开long long见祖宗
int main(){
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&c[i],&y[i]);
    for(int i=1,mc;i<=n;i++){//mc是最便宜的卖法
        mc=c[i];//mc初始值为c[i]
        for(int j=1;j<i;j++)
            if(c[j]+(i-j)*s<min(c[i],mc))
                mc=c[j]+(i-j)*s;//如果在之前造好保养到现在还比现在便宜的话就提前造好
        ans+=mc*y[i];
    }
    printf("%lld",ans);//输出
    return false;//一切都结束了
} 
```

我绝不会告诉你~~这题代码本人一遍就过了~~ 我花了10分钟就过了。

---

## 作者：F_S_R_M (赞：4)

##### 这个题还可以吧
## 思路：
机器的造价每周都是不同的，而且每周都有保养费

一看就是贪心

总体思想就是：

枚举前几周的单价+每周每台的保养费，

**如果某一周的单价+每周每台机器的保养费 < 当前单价，**

就将当前单价更新成  某一周的单价+每周的保养费

然后总数加上 $ci[i]*yi[i]$;

**注意用 ```long long```  不然会WA一个点**

## 代码：
```cpp
#include<iostream>
#include<cstdio>		//快读的头文件 
using namespace std;
inline int read() {
	char c = getchar(); int x = 0, f = 1;
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
}									//以上是快读 
int ci[10001],yi[10001];
int main()
{
	int n,s;
	cin>>n>>s;			//读入 n ，s 
	for(int i=1;i<=n;i++)
		ci[i]=read(),yi[i]=read(); 
	long long u=0;		//定义 long long，不然会WA掉一个点 
	u+=ci[1]*yi[1];   	//将第一个点单独加上 因为第一周必须以当前单价造 
	for(int i=2;i<=n;i++)		//从 2 开始
	{
		for(int j=i-1;j>=1;j--)		//枚举之前的几个星期 
		{
			if(ci[j]+(i-j)*s<ci[i])		//某一周的单价+每周每台机器的保养费
				ci[i]=ci[j]+(i-j)*s;	//更新 
		}
		u+=ci[i]*yi[i];				//加入总数 
	}
	cout<<u;				//输出 
	return 0;
}
```


---

## 作者：化学小哥 (赞：4)

c++题解驾到……

一道贪心的水题，瞎搞一下就好了……

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long ans;int n,m,k,x,y;
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {scanf("%d%d",&x,&y);
     if (i==1) k=x;
     else k=min(k+m,x);   //以k为当前最小代价
     ans+=k*y;
    }
    printf("%lld",ans);
}
```

---

## 作者：「QQ红包」 (赞：4)

本题为贪心。本周的最低价是本周的价格或者是上一周的最低价+保养费用。

所以这一道题是不需要数组的，然而ylx最开始开了数组就懒得去掉了，反正不会爆空间

```delphi

var n,s,i,min:longint;sum:int64;
    c,y:array[-5..100000] of longint;//当初数组开1..10000只有90分
begin
    read(n,s);
    sum:=0;
    for i:=1 to n do
        read(c[i],y[i]);
    min:=200000000;
    for i:=1 to n do
    begin
        if c[i]<min+s then min:=c[i] else min:=min+s;//求本周最低价
        sum:=sum+min*y[i];//加到代价里去
    end;
    write(sum);
end.

```

---

## 作者：Dr_殇 (赞：3)

#很简单的一道贪心题，我不知道为什么楼上的都不用结构体，结构体不是更简单吗？


##代码如下：





```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>//头文件准备
using namespace std;
struct code{//定义结构体数组，用于存储生产机器的价格和需要的个数
    int cost;
    int need;
}w[10005];
int main(){
    //freopen("1376.in","r",stdin);
    //freopen("1376.out","w",stdout);
    int i,j,k,n,s;long long ans=0,tmp;//注意：ans必须要为long long类型，否则就会超出范围
    scanf("%d%d",&n,&s);
    for(i=1;i<=n;i++) scanf("%d%d",&w[i].cost,&w[i].need);
    k=1;
    for(i=1;i<=n;i++)
    {
        if(w[i].cost<=w[k].cost+(i-k)*s) k=i;//判断用哪个星期的机器人
        tmp=w[k].cost*w[i].need+(i-k)*s*w[i].need;//tmp等于第k个星期的机器人加上机器人的保养费用
        ans+=tmp;//ans加上这个星期的价值
    }
    printf("%lld",ans);//最后输出答案
        while (1);//反抄袭
     return 0;
}
```
#珍爱生命，拒绝抄袭！

---

## 作者：Ryan_ (赞：1)

一道普及题，看来是自己想太多了

一开始的贪心策略是
 
  第一周直接计算答案就好
  
  若往后的一周保养费乘以第一周的所有订单比
  
  往后的那一周还要小的话我们即考虑在第一周
  
  就买好第二周需要的货，否则就不买
  
  如果第一周囤货确实时价格更少了
  
  那么我们就考虑第三周该不该囤货，以及实在第一周囤货
  
  还是在第二周囤货以此类推
  
  注意：被cut掉的方案永远不会再用，因为越往后性价比
  
  只可能越劣，所以前面的方案肯定比后面（cut掉）的方案劣 

于是最高70分，想了想大仙自己没有考虑到，随着i的增大，原本更优的方案，可能会比原本更劣的（已经cut掉的）方案更劣

**30分代码**

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int long long n,s,ans=0;
struct object{
	int cost,sale;
}a[10001];
int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].cost,&a[i].sale);
	}
	ans+=a[1].cost*a[1].sale;
	int flag=1;
	for(int i=2;i<=n;i++){
		if(a[flag].cost*(i-flag)*s*a[i].sale<a[i].cost*a[i].sale){
			ans+=a[flag].cost*((i-flag)*s*a[i].sale);
			if(a[flag].cost*(i-flag+1)*s*a[i+1].sale>=a[i].cost*s*a[i+1].sale){
				flag=i;
			}
		}
		else {
			flag=i;
			ans+=a[flag].cost*a[flag].sale;
		}
	}
	printf("%d",ans);
	return 0;
}
```

**60分代码**

```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int long long n,s,ans=0;
struct object{
	int cost,sale;
}a[10001];
int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i].cost,&a[i].sale);
	}
	ans+=a[1].cost*a[1].sale;
	int flag=1;
	for(int i=2;i<=n;i++){
		if(a[flag].cost*a[i].sale+(i-flag)*s*a[flag].sale<a[i].cost*a[i].sale){
			ans+=a[flag].cost*a[i].sale+((i-flag)*s*a[i].sale);
			if(a[flag].cost*a[i+1].sale+(i-flag+1)*s*a[i+1].sale>=a[i].cost*s*a[i+1].sale){
				flag=i;
			}
		}
		else {
			flag=i;
			ans+=a[flag].cost*a[flag].sale;
		}
	}
	printf("%d",ans);
	return 0;
}
```


**70分代码**


```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int long long n,s,ans=0;
struct object{
	int cost,sale;
}a[100001];
int main(){
	scanf("%lld%lld",&n,&s);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].cost,&a[i].sale);
	}
	ans+=a[1].cost*a[1].sale;
	int flag=1;
	for(int i=2;i<=n;i++){
		if(a[flag].cost*a[i].sale+(i-flag)*s*a[flag].sale<a[i].cost*a[i].sale){
			ans+=a[flag].cost*a[i].sale+((i-flag)*s*a[i].sale);
			if(a[flag].cost*a[i+1].sale+(i-flag+1)*s*a[i+1].sale>=a[i].cost*s*a[i+1].sale){
				flag=i;
			}
		}
		else {
			flag=i;
			ans+=a[flag].cost*a[flag].sale;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

100分代码

```
#include<bits/stdc++.h>
using namespace std;
long long minn(int long long a,int long long b){
	if(a<b)return a;
	else return b;
}
int main(){
	int long long last,n,s,ans=0;
	cin>>n>>s;
	for(int i=1,a,b;i<=n;i++){
		cin>>a>>b;
		if(i==1)last=a;
		else last=minn(last+s,a);
		ans+=last*b;
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：jinhaoxian (赞：1)

思路：以O（n）的复杂度，求出每周获取机器1台（当周制造、之前几周制造并保养）的最低价格，并求出总最低价。
```
#include<bits/stdc++.h>
using namespace std;
long long n,c[10500],s,m[10500],y[10500],ans,i;
int main()
{
    cin>>n>>s;
    for (i=1;i<=n;i++)
    cin>>c[i]>>y[i];
    m[0]=2140000000;
    for (i=1;i<=n;i++)//最低价格
    m[i]=min(m[i-1]+s,c[i]);
    for (i=1;i<=n;i++)
    ans+=m[i]*y[i];//答案
    cout<<ans;
    return 0;
}
```

---

## 作者：fadeAwayLi (赞：0)

基本思路：贪心，记录当前的最低价格（将本周最低价格复制给[u]本周生产价格[/u]和[u]上周最低价格+保养费[/u]，然后计算代价即可。

```delphi

program t1376;
var n,bp,i,minp,p,l:longint;
    s:int64;
begin
     readln(n,bp);
     s:=0;
     minp:=0;
     for i:=1 to n do
     begin
          readln(p,l);
          if i=1 then minp:=p
                 else begin
                      inc(minp,bp);
                      if p<minp then minp:=p;
                 end;
          inc(s,minp*l);
     end;
     writeln(s);
     readln;
end. 

```

---

