# [USACO08OPEN] Cow Cars S

## 题目描述

N (1 <= N <= 50,000) cows conveniently numbered 1..N are driving in separate cars along a highway in Cowtopia. Cow i can drive in any of M different high lanes (1 <= M <= N) and can travel at a maximum speed of S\_i (1 <= S\_i <= 1,000,000) km/hour.

After their other bad driving experience, the cows hate collisions and take extraordinary measures to avoid them. On this highway, cow i reduces its speed by D (0 <= D <= 5,000) km/hour for each cow in front of it on the highway (though never below 0 km/hour). Thus, if there are K cows in front of cow i, the cow will travel at a speed of max[S\_i - D \* K, 0]. While a cow might actually travel faster than a cow directly in front of it, the cows are spaced far enough apart so crashes will not occur once cows slow down as

described,

Cowtopia has a minimum speed law which requires everyone on the highway to travel at a a minimum speed of L (1 <= L <= 1,000,000) km/hour so sometimes some of the cows will be unable to take the highway if they follow the rules above. Write a program that will find the maximum number of cows that can drive on the highway while obeying the minimum speed limit law.


## 说明/提示

There are three cows with one lane to drive on, a speed decrease of 1, and a minimum speed limit of 5.


Two cows are possible, by putting either cow with speed 5 first and the cow with speed 7 second.


## 样例 #1

### 输入

```
3 1 1 5 
5 
7 
5 
```

### 输出

```
2 
```

# 题解

## 作者：Sirius_X (赞：15)

##这题只是一道简单的贪心，并不难##

###题目描述的有点模糊，意思其实就是一头牛跟在K头牛后面，然后判断那头牛的速度-K\*D是否>=L，求速度符合L标准的牛的数量###

###我的思路是：将N头牛读进来，从小到大排好，然后将速度值较小的放在路的前面，尽量让跑得快的，减速减得多一点，就可以符合L了。再把已经上路的牛所在的数组位置，清零，相当于把它拿走了（但要记得拿一个变量记录数量）。最后再做M次循环（因为总共有M条路，一次循环就相当于处理了一条路），输出###

以下是我的代码，仅供大家参考。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[50010];
int main(){
    int n,i,j,s=0,m,d,l,ans;
    scanf("%d %d %d %d",&n,&m,&d,&l);
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+1+n);//排序。
    for(i=1;i<=m;i++){
        ans=0;//每次循环前要清零，这就相当于记录j头牛前面有多少头牛（相当于题目中的K）。
        for(j=1;j<=n;j++){
            if(!a[j]) continue;//如果已经把拿出来了，就无需在判断。
            if(a[j]-ans*d>=l||(a[j]-ans*d<0&&l==0)){//判断。
                ans++;s++;a[j]=0;
            }
        }
    }
    printf("%d\n",s);
    return 0;
}
```

---

## 作者：花千树 (赞：7)

本题思路:本题不难，读入数据然后sort，硬穷举绝对不超时（本人是个比较新的新手，穷举万岁！），没什么要点，就是要仔细（在DEV里面测了好几次不对就是因为ans忘了给初值。。。）

话不多说，上代码！！！！！！！！！！

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>//sort必备头文件
#define N 50005//宏定义，本人比较建议用，一旦数组要开很大，宏定义不会错
using namespace std;
int a[N],b[N],ans,j=1;//直接调用宏，一开始ans放函数内没给初值，悲剧啊
int main(){//过程华丽开始
    int n,m,d,l;//定义
    cin>>n>>m>>d>>l;//读入，其实scanf更好，不过变量太多本人实在懒，dalao见谅
    for(int i=1;i<=n;i++)
        cin>>a[i];//同样cin读入QAQ
    sort(a+1,a+1+n);//sort快排！！！！
    for(int i=1;i<=n;i++){
        if(l<=a[i]-b[j]*d){ans++;b[j]++;j++;}//判断，记得1下标j初值为1，0下标为0！！
        if(j>m)j=1;//如果路走尽了，从头再来
    }
    printf("%d\n",ans);//输出ans
    return 0;//过程华丽结束
}

```

---

## 作者：zengxr (赞：7)

# 思路：
将牛从小到大排序，然后枚举每头奶牛，再判断符不符合要求就好了。

# 代码：
```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
int cows[100001];
using namespace std;
int main()
{
     int n,m,d,l;
	 cin>>n>>m>>d>>l;//输入
	 for(int i=1;i<=n;i++)
		 cin>>cows[i];//输入
	 sort(cows+1,cows+1+n);//从小到大排序
	 int ans=0;
	 for(int i=1;i<=n;i++)
	 {
		 int k=ans/m;
		 if(cows[i]-k*d>=l)ans++;//判断符不符合要求，符合就ans++
	 }
     cout<<ans;//输出
    return 0;
}
```


---

## 作者：文·和 (赞：4)

这道题不算难吧（刚模拟赛做的）：

先sort一遍，然后从小的开始扫，如果可以就让他开车  ~~别想歪了~~。因为越小条件越苛刻。越大越容易上路。用循环指针k表示轮到开哪条路开个数组表示路上已经有多少车。扫一遍即可。

根据思路贴出代码

```
#include <bits/stdc++.h>
using namespace std;
int v[50001],i,j,k,l,m,n,d,lu[50001],ans;//v表示车速..lu表示每条路上的车数，原谅变量有点多 
int ys(int x){//表示当x大于0时返回原数否则返回0 
	return (x+abs(x))/2;//简单数学 
}
int main(){
cin>>n>>m>>d>>l;
for(i=1;i<=n;i++) cin>>v[i];   //输入 
sort(v+1,v+n+1);  //排序一下 
k=1;   //从道路1开始 
for(i=1;i<=n;i++){
	if(ys(v[i]-lu[k]*d)>=l) lu[k]++,ans++,k=k%m+1; //如果可以上路那么答案++,那条路的车++,然后换下一条路（如果是最后一条路那么返回第一条） 
}
cout<<ans;  //输出即可 
return 0;  //养成好习惯 
}

```
我的题解就到此结束了，求通过qwq ~~话说奶牛怎么这么多~~

---

## 作者：Dr_殇 (赞：4)

#这道题就是不停的穷举公路，m条公路穷举完了以后，就回到公路1继续穷举公路，直到没有奶牛了。


##这道题千万不要被车速给迷惑了，就排完序以后就直接做，不用考虑车速的问题。


###不过话说开的快的为什么可以在开的慢的车后面。


##代码如下




```cpp
#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>//头文件准备 
using namespace std;
int n,m,l,d,ans,a[50005],map[50005];
int main(){
    freopen ("2909.in","r",stdin);
    freopen ("2909.out","w",stdout);
    scanf ("%d %d %d %d",&n,&m,&d,&l);//读入 
    for (int i=1;i<=n;i++){
        scanf ("%d",&a[i]);
    }
    sort (a+1,a+1+n);//sort排序 
    int k=1;//公路的指针，使题目简单化 
    for (int i=1;i<=n;i++){
        if (a[i]-map[k]*d>=l){//判断奶牛i是否能在公路k上行驶 
            ans++;
            map[k]++;
            k++;
            if (k>m)k=1;//如果m条公路穷举完了，再回到公路1 
```
}//如果能在公路k上行驶，答案就加1，公路k上的奶牛加1，然后穷举公路k+1

```cpp
    }
    printf ("%d\n",ans);//输出答案
    while (1);//反抄袭 
    return 0;
}
```
#还是我一贯的风格：
#真爱生命，拒绝抄袭。


##抄袭晚上会有人来找你的。


---

## 作者：jbc392 (赞：2)

思路:

既然要最多

所以奶牛要从小到大排序

既然有m条公路

所以定义一个vis数组来标记该奶牛有没有已经上路(~~次上路非你想的那个~~)

看代码注释

```
#include<bits/stdc++.h>
using namespace std;

int n ,m ,d ,l;
int k ,a[50010] ,ans;
bool vis[50010];

inline int read()//快读
{
    int x = 0 ,y = 1;
    char c = getchar();
    while(c > '9' || c < '0')
    {
        if(c == '-')y = -1;
        c = getchar();
    }
    while(c <= '9' && c >= '0')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * y;
}

int main(){
	
	n = read(); m = read(); d = read(); l = read();//输入
	for(int i = 1;i <= n;i++) a[i] = read();
	
	sort(a + 1 ,a + 1 + n);
	for(int i = 1;i <= n;i++) vis[i] = false;
	while(m--)
	{
		k = 0;
		for(int i = 1;i <= n;i++)
		{
			if(!vis[i] && a[i] - k * d >= l)//如果这头牛速度大于l他就要上路了
			{
				vis[i] = true;
				k++;
				ans++;//累加
			}
		}
	}
	
	cout << ans;//输出
	
	return 0;//好习惯
}
```


---

## 作者：Suiseiseki (赞：1)

我没有说错的话，这一道题的本质就是贪心，（~~好简单的贪心~~）

题目忘了补充一个条件，导致我被误导（~~其实是我自己想多了~~）

#后面的车速可以比前面的车速快！！

（~~这个车距有多长啊！~~）

~~貌似讲了一堆废话~~

具体思路：把所有的车速从小到大进行排序（因为慢车可以放的快车也可以放，反过来就不行了）

然后车道就不停的轮回，能放就放。

接下来上代码（结合代码看看吧，~~我语文实在挂科~~）

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[50005];
int race[105];//记录每个跑道上的汽车数量
int main(){
    int n,m,d,l;
    scanf("%d%d%d%d",&n,&m,&d,&l);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+1+n);//排序
    int ans=0;
    int i=1;
    int nowrace=1;//当前车道
    while(i<=n){
        if(a[i]-d*race[nowrace]>=l){//可以放
            race[nowrace]++;
            ans++;//答案加一
            nowrace++;//下一个跑道
            if(nowrace>m){
                nowrace=1;
            }
        }
        i++;
    }
    printf("%d\n",ans);
    return 0;
}
```
蒟蒻代码勿喷，望指教
（~~管理员大大让我过吧QAQ~~）


---

## 作者：Snow_Dreams (赞：0)

这道题就是一个贪心+快排

贪心指如果牛小就先考虑，此局部最优解为全局最优解，方法无后效性

所以就要将牛从小到大排序，然后考虑其符不符合要求

然后就讲一下排序（引用一下我自己的博客）：


桶排序： 写一个数组，用下标表示数，如果此数出现则把那个位置++

耗空间！！
冒泡排序： 每一趟只能将一个数归位

慢！！
bling bling

快速排序：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100005], n;
void quick_sort(int left, int right)
{
    if(left >= right) return;
    int x = a[(left+right)/2], i=left, j = right;
    while( i < j ){
        while(a[i] < x) i++; 
        while(a[j] > x) j--; 
        if( i<= j){
            swap(a[i], a[j]);
            i++, j--;
        }
    }
    if(left < j) quick_sort(left, j);
    if(i < right) quick_sort(i, right);
}
void pt()
{
    for(int i=1; i<=n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main()
{   
    scanf("%d", &n);
    for(int i=1; i<=n; i++) scanf("%d", a+i);
    quick_sort(1, n);
    pt();
    return 0;
}
```
采用双指针算法，但我还是建议直接用stl，不过我觉得要了解原理

---

## 作者：iawe (赞：0)

     #include<cstdio>
     #include<algorithm>
     #define maxn 2000002 
     using namespace std;
      int a[maxn],b[maxn];
     int n,m,d,l,tot;
     int main()
    {
	  scanf("%d%d%d%d",&n,&m,&d,&l);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	sort(a+1,a+1+n);//依据题意，可以见到贪心的影子。
    for(int i=1;i<=m;i++)//第一层枚举每一条道路
    {
    	for(int j=1;j<=n;j++)//第二层枚举每条路最多能走几个
    	{
    		if(a[j]-b[i]*d>=l)
    		{
    			b[i]++;
    			a[j]=-1;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		tot+=b[i];//每条路总和相加，为最终答案
	}
	printf("%d",tot);
	return 0;
    }

---

