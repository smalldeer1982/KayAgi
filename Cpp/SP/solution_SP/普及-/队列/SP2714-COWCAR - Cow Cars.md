# COWCAR - Cow Cars

## 题目描述

N (1 ≤ N ≤ 50,000) cows conveniently numbered 1, ..., N are driving in separate cars along a highway in Cowtopia. Cow i can drive in any of M different high lanes (1 ≤ M ≤ N) and can travel at a maximum speed of S $ _{i} $ (1 ≤ S $ _{i} $ ≤ 1,000,000) km/hour.

After their other bad driving experience, the cows hate collisions and take extraordinary measures to avoid them. On this highway, cow i reduces its speed by D (0 ≤ D ≤ 5,000) km/hour for each cow in front of it on the highway (though never below 0 km/hour). Thus, if there are K cows in front of cow i, the cow will travel at a speed of max(S $ _{i} $ - D\*K, 0). While a cow might actually travel faster than a cow directly in front of it, the cows are spaced far enough apart so crashes will not occur once cows slow down as described.

Cowtopia has a minimum speed law which requires everyone on the highway to travel at a a minimum speed of L (1 ≤ L ≤ 1,000,000) km/hour, so sometimes some of the cows will be unable to take the highway if they follow the rules above. Write a program that will find the maximum number of cows that can drive on the highway while obeying the minimum speed limit law.

## 样例 #1

### 输入

```
3 1 1 5
5
7
5```

### 输出

```
2```

# 题解

## 作者：huwanpeng (赞：6)

既然题目都说了 P2909，那肯定就是双倍经验呗。

贪心题一个：

先排序，排序是为了让速度本来就小的奶牛靠前，这样它减的速度就小，自然能上公路的概率就大；

再遍历，遍历每一个判断此奶牛速度是否大于等于 $L$，是的就把它加上。最后的最后，千万不要忘记，一共有 $M$ 条车道，当一排放满时，要再加一排。

最后的最后的最后，是你们最喜欢的完整代码：

```
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,d,l,s[50010];
int ans,cnt;//cnt记录奶牛需要放几条车道 
int main()
{
	cin>>n>>m>>d>>l;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++)
	{
		if(s[i]-cnt*d>=l)
		{
			ans++;
			if(ans%m==0)
			cnt++;//一排放满，再放一排 
		}
	}
	cout<<ans;
	return 0; 
}
```

既然来了，就点个赞再走吧！

---

## 作者：Matt_Wang (赞：3)

# ~~此题和P2909一样~~
------------
#### 这题现在没有题解，于是本蒟蒻准备水一发题解

### 机房蒟蒻最近在学习优先级队列，看什么都是优先级队列

首先这道题的思路很简单，就是**贪心**！

我们想到，首先把整个速度按照从小到大的顺序排个序（~~其实是为了使用小根堆~~）
```cpp
priority_queue<int, vector<int>, less<int> > name;			
//从大到小排列的优先级队列——大根堆

priority_queue<int, vector<int>, greater<int> > name;		
//从小到大排列的优先级队列——小根堆
```

使用一个cowline数组来记录每条路上车的数量

然后从第一个车道一直到最后一个车道，只要能放就放，能放的条件就是**这条路前面车的数量 * d + l 小于这辆车的数量**。

即
```cpp
this_car >= cowline[point_it] * d + l
```
如果可以，把结果加一。

这道题就迎刃而解了！

------------


### 附上代码
```cpp
#include <bits/stdc++.h>
using namespace std;


int m, n, d, l, buf, cowline[50505], ans;
priority_queue<int, vector<int>, greater<int> > cow;


void read(void)
{
	scanf("%d%d%d%d", &n, &m, &d, &l);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &buf);
		cow.push(buf);
	}
}


void solve(void)
{
	int p_start = 0, point_it = 0;
	while(cow.top() < l){
		cow.pop();
		p_start++;
		continue;
	}
	
	for(int i = p_start; i < n; i++)
	{
		buf = cow.top();
		cow.pop();
		if(buf >= cowline[point_it] * d + l){
			cowline[point_it]++;
			ans++;
			point_it++;
			if(point_it == m) point_it = 0;
		}
	}
}


int main(void)
{
	read();
	solve();
	cout << ans << endl;
	return 0;
}
```
**谢谢阅读，祝大家NOIP RP++！**


---

## 作者：LiteratureCollege (赞：1)

~~从P2909过来的，但那题已经有很多大佬发过题解了，**本菜鸡**只能来发此题的题解。~~

此题的贪心策略其实并不难想，因为对每一车道越靠后汽车速度要求越高，所以我们将原车速较慢的车放在车道的前面，而速度快的放后面。

我们先将速度从小到大排序，将速度前m小的车子放在车道第一位，速度m+1到2m为的放在每一车道第二位，以此类推，可以保证求到最优的分配方案。

```
#include<bits/stdc++.h> 
using namespace std;
int n,m,d,l,a[50416],gy[50010],zjy,t=1;
//n是奶牛数，m是车道数，gy[i]表示i号车道上有几辆车，t为现在所在的车道编号，zjy为答案 
int main()
{
	cin>>n>>m>>d>>l;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+1+n);//排序 
	for(int i=1;i<=n;i++)
	{
		if(a[i]-d*gy[t]>=l)//逐一判断 
		{
			gy[t++]++;
			zjy++;
		}
		t%=m;//t要保证小于等于m 
	}
	cout<<zjy;
	return 0;
}
```


---

## 作者：_Camille_ (赞：1)

### 前言

双倍经验，题目也标明的很清楚了，[移步于此](https://www.luogu.com.cn/problem/P2909)

### 解题思路
贪心。将**速度值较小**的放在路的前面，这样减速就会多一点，就可以符合 $ L $ 了。再把已经上路的牛所在的数组位置**清零**，相当于把它拿走了。最后循环 $M$ 次处理 $M$ 条路。

细节实现看代码吧。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50001];
int main(){
    int n,m,d,l;
    cin>>n>>m>>d>>l;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);//先排序使速度值较小的放在前面
    int ans=0;
    for(int i=1;i<=m;i++){
        int s=0;
        for(int j=1;j<=n;j++){
            if(!a[j]) continue;//若以上过路，则跳过本次循环
            if(l<=a[j]-s*d || (a[j]-s*d<=0 && !l)){//按题意进行判断
                ans++;
                s++;
                a[j]=0;//若为真，ans&s++，把a[j]清零
            }
        }
    }
    cout<<ans;//输出答案
    return 0;
}
```

---

## 作者：Nt_Tsumiki (赞：0)

## 题意

[题目传送门](https://www.luogu.com.cn/problem/SP2714)

有 $m$ 条公路，在公路上有 $n$ 辆车，假设第 $i$ 辆车的速度为 $s_i$ 且它前面有 $k$ 辆车，那么这辆车的速度就不会超过 $s_i-k \times d$，如果这个数小于零，那么它的值即为零，道路的最低时速为 $l$ 求有多少辆车能上路。

## 做法

### 算法

我们考虑贪心。

很明显，如果前面的车越多，那么 $s_i$ 要减去的值也就越多，所以我们可以把 $s_i$ 由小到大排序一遍，再依次模拟即可。

时间复杂度 $O(nm)$

### 优化

由于本题的时限较低，所以我们考虑优化成 $O(n)$。

我们可以换一个方向来思考，横着摆，即摆一辆车换一条路。

很显然，如果在第 $i$ 辆车之前有 $k$ 辆车已经在道路中排好位，那么依照贪心的思想，这辆车应该被排在第 $k \bmod m$ 的道路上，那么答案也就呼之欲出了。

至于这条道路前面车的辆数，开个桶记录一下就行了。

## Code
```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
int n,m,d,l,k;
int s[500001],t[500001];//速度和前方车辆个数

int main() {
    scanf("%d%d%d%d",&n,&m,&d,&l);
    for (int i=1;i<=n;i++) scanf("%d",s+i);
    sort(s+1,s+n+1);//升序排序
    for (int i=1;i<=n;i++) {
        int tmp1=k%m;//第几条道路
        int tmp2=s[i]-t[tmp1]*d;//计算速度
        if (tmp2<0) tmp2=0;//特判
        if (tmp2>=l) k++,t[tmp1]++;
    }
    printf("%d\n",k);//k 同样也是答案
    return 0;
}
```

---

## 作者：20100202w (赞：0)

这道题和 P 2909 是一样的 。

贪心策略就是从小到大排一遍，然后扫描，先算出有没有车道，有的话答案肯定 + 1 ，没有的话再判断，看是否符合 。

从小到大排一遍是因为较大数会比较小数减速后大于等于最低时速的可能性更大，如果较大数都不行，那较小数就更不行了，所以越小越靠前是为了减得更少，是为了能行驶的车辆更多 。

最后附上代码：

```cpp
#include<algorithm> 
#include<iostream>
#include<cstdio>//头文件
using namespace std;
int a[50005];
int main()
{
	int n,m,l,d,ans=0;
	scanf("%d%d%d%d",&n,&m,&d,&l);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);// n 个数
	sort(a+1,a+n+1);//升序
	for(int i=1;i<=n;i++)//从 1 到 n 扫描一遍
	{
		int p=ans/m;//看剩余车道是第几行
		if(a[i]-p*d>=l)//判断减速后是否高于最低时速
			ans++;//答案 + 1
	} 
	printf("%d",ans);//输出答案
	return 0;//养成好习惯
}

```


---

## 作者：胡金梁 (赞：0)

## 贪心
因为对每一车道越靠后汽车速度要求越高，所以我们将原车速较慢的车放在车道的前面，而速度快的放后面。那么我们先将速度从小到大排序，将速度前m小的车子放在车道第一位，速度m+1到2m为的放在每一车道第二位，以此类推，可以保证求到最优的分配方案。这题必须用快速排序，可以用函数，不支持STL库的可以手写。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50005],gy[50050];
signed main()
{
	int n,m,d,l,s=0,t=0;//n,m,d,l可以看题目，s是可以放的车数，t是车道
	scanf("%d%d%d%d",&n,&m,&d,&l);
	for(int i=1;i<=n;i++)
	{
	    scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);//c++专属偷懒方法
	for(int i=1;i<=n;i++)//枚举每条车道
	{
		if(a[i]-gy[t]*d>=l)
		{
			gy[t++]++;
			s++
		}
		t%=m;
	}
	printf("%d",s);
}
```


---

## 作者：jbc392 (赞：0)

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

## 作者：瓜皮少年 (赞：0)

我没有说错的话，这一道题的本质就是贪心，~~（好简单的贪心）~~

## 后面的车速可以比前面的车速快！！
（这个车距有多长啊！）

具体思路：把所有的车速从小到大进行排序（因为慢车可以放的快车也可以放，反过来就不行了）

然后车道就不停的轮回，能放就放。

接下来上代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int Read(){
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-') c=getchar();
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int n,m,d,l;
int si[50010];
int race[50010]; //记录每个跑道上的汽车数量
int main(){
	n=Read(),m=Read(),d=Read(),l=Read();
	for(int i=1;i<=n;i++){
		si[i]=Read();
	}
	sort(si+1,si+n+1);//排序
	int ans=0;
	int now=1;;//当前车道
	for(int i=1;i<=n;i++){
		if(si[i]-d*race[now]>=l){//可以放
			race[now]++;
			ans++;//答案加一
			now++;//下一个跑道
			if(now>m){
				now=1;
			}
		}
		i++;
	}
	cout<<ans;
	return 0;
}

```

---

