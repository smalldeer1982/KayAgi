# Blinds

## 题目描述

The blinds are known to consist of opaque horizontal stripes that can be rotated thus regulating the amount of light flowing in the room. There are $ n $ blind stripes with the width of 1 in the factory warehouse for blind production. The problem is that all of them are spare details from different orders, that is, they may not have the same length (it is even possible for them to have different lengths)

Every stripe can be cut into two or more parts. The cuttings are made perpendicularly to the side along which the length is measured. Thus the cuttings do not change the width of a stripe but each of the resulting pieces has a lesser length (the sum of which is equal to the length of the initial stripe)

After all the cuttings the blinds are constructed through consecutive joining of several parts, similar in length, along sides, along which length is measured. Also, apart from the resulting pieces an initial stripe can be used as a blind if it hasn't been cut. It is forbidden to construct blinds in any other way.

Thus, if the blinds consist of $ k $ pieces each $ d $ in length, then they are of form of a rectangle of $ k×d $ bourlemeters.

Your task is to find for what window possessing the largest possible area the blinds can be made from the given stripes if on technical grounds it is forbidden to use pieces shorter than $ l $ bourlemeter. The window is of form of a rectangle with side lengths as positive integers.

## 说明/提示

In the first sample test the required window is $ 2×4 $ in size and the blinds for it consist of 4 parts, each 2 bourlemeters long. One of the parts is the initial stripe with the length of 2, the other one is a part of a cut stripe with the length of 3 and the two remaining stripes are parts of a stripe with the length of 4 cut in halves.

## 样例 #1

### 输入

```
4 2
1 2 3 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 3
5 5 7 3 1
```

### 输出

```
15
```

## 样例 #3

### 输入

```
2 3
1 2
```

### 输出

```
0
```

# 题解

## 作者：Accepted_Z (赞：7)

打一个小广告：[点我](https://www.luogu.org/blog/hhhh123/)

以下正文：

------------
看完题面，哈哈，这道题是裸的模拟呀！暴力都能过。
### 思路
输入数据以后把每片的长度i从l到n枚举一遍。然后用ans来记录得到的总片数，面积就是ans*i的值，再比较一下，用mx记录当前最大值，枚举结束后再输出最大值，就233啦(注意：本题不需要特判0的情况，因为如果a[i]的值小于l，那么a[i]/l就等于0啦，并不会影响mx的值，因为mx初始化的值为-1）
### 史上最短代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,l,ans=0,mx=-1,a[10005];//ans是当前长度能得到的叶片数量，mx是当前最大的百叶窗面积。
int main()
{
    cin>>n>>l;
    for(int i=1;i<=n;i++)
    	cin>>a[i];//输入每个叶片的长度
    for(int i=l;i<=100;i++)//从l到100（因为a[i]最大值为100）都枚举一遍
    {
    	ans=0;
    	for(int j=1;j<=n;j++)
    		ans=ans+a[j]/i;//a[j]/i表示第j个叶片能割多少个长度为i的叶片
    	mx=max(mx,ans*i);//比较取最大值
    }
    cout<<mx;//输出最大的面积
    return 0;//233啦
}

```

---

## 作者：hexiao (赞：4)

看完题面，这道题是裸的模拟呀！暴力都能过!

于是写完代码没跑样例就交了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,a[10005];
int main()
{
    cin>>n>>l;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int maxv=-1;
    for(int i=1;i<=100;i++)
    {
        int ans=0;
        for(int j=1;j<=n;j++)
            ans+=a[j]/i;
        maxv=max(maxv,ans*i);
    }
    cout<<maxv;
    return 0;
}
```
然后：![](https://cdn.luogu.com.cn/upload/pic/62215.png)
## what?!
 我开始认真看题：出于技术原因**禁止使用短于l的横条**！
 
于是我把代码改成了：
```cpp
#include<bits/stdc++.h>//万能库
using namespace std;//命名空间
int n,l,a[10005];//n是横条数量，l是可以使用的横条的最短长度，a[i]是第i个横条的长度
int main()
{
    cin>>n>>l;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }//读入
    int maxv=-1;//最大值，要设为1
    for(int i=l/*把1改成l*/;i<=100/*1<=a[i]<=100*/;i++)//枚举百叶窗的长
    {
        int ans=0;
        for(int j=1;j<=n;j++)
            ans+=a[j]/i;//计算百叶窗的宽
        if(maxv<ans*i)
        {
            maxv=ans*i;//更新最大值
            //是面积，不是长度!!!
        }
    }
    cout<<maxv;//输出最大值
    return 0;
}
```

---

## 作者：_Aoi_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF38C)

### 题目大意
给你$n$个条子，长为$a_i$，宽为$1$，条子可以切割，但不能拼接，让你用这些条子，组成一个长大于$l$，宽为组成这个长方形的总条子数的面积最大的长方形。

### 思路
从$l$~$100$依次枚举（为什么是$100$,因为$a_i$的长度至多为$100$），每次尽量多切割条子，记录条子总数：
```cpp
	num+=(a[i]/k);
```
每试一种长度，就判断它是否为面积最大的长方形：
```cpp
	maxx=max(maxx,num*k);
```
### 注意
- $l$~$100$的所有整数都可以作为条子的长度
- 每次统计完条子数$num$都要清零
- 取最大值时取的是面积（长*宽），并不是长

### AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,a[110],ans,maxx;
int main()
{
	cin>>n>>l;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int k=l;k<=100;k++)
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<k)
				continue;
			ans+=(a[i]/k);
			//cout<<ans<<",";
		}
		maxx=max(maxx,ans*k);
	}
	cout<<maxx;
	return 0;
}

```

---

## 作者：Fido_Puppy (赞：2)

首先，这个百叶窗我们得了解一下啊！

不然还冒着被红题反杀的风险。

## Sol

其实，这个百叶窗的长是我们自己定的。

瞅一瞅 $a_i$ 的范围。

值得注意的是，这个长度小于 $l$ 的横条是不能选的。

那么百叶窗的长的范围就是 $l$~$100$ 辣。

### for i:=l to 100 do

接下来，每一个长度为 $x$ 的横条，被截成长度为 $y$ 的横条，能截 $x$ $div$ $y$ 根。

每根的宽度为 $1$，所以百叶窗的宽度就是 $x$ $div$ $y$。

### for j:=1 to n do inc(ans,x div y);

两重循环定了，剩下的就简单了。

## Code

```pascal
var
  a:array[1..100] of longint;
  i,n,l,j,ans,max:longint;
begin
  ans:=1;
  readln(n,l);
  for i:=1 to n do read(a[i]);
  for i:=l to 100 do begin
    ans:=0;
    for j:=1 to n do ans:=ans+a[j] div i;
    if max<ans*i then max:=ans*i;
  end;
  writeln(max);
end.
```


---

## 作者：Dry_ice (赞：2)

> 这道题珂以说是我见过的较简单的一道C题。

## 思路引导

因为这道题中横条长度最多也只有 $100$，所以直接枚举横条长度即百叶窗的横向宽 $i\ (i=1,2,\cdots,100)$，然后枚举计算每根横条能被切成多少个长度为 $i$ 的横条。
时间复杂度 $O(100\cdot n)$（即近乎线性，只不过常数为 $100$，相对较大）。

然后直接上代码。

## CODE

```cpp
#include <stdio.h>
int n, l, a[105];
int main(void) {
    scanf("%d %d", &n, &l);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    int ans = 0, num;
    for (int i = l; i <= 100; ++i) {
        num = 0;
        for (int j = 1; j <= n; ++j)
            num += a[j] / i;
        ans = i * num > ans ? i * num : ans;
    }
    printf("%d\n", ans);
    return 0;
}
```

留个赞再走ლ(°◕‵ƹ′◕ლ)

---

## 作者：Lucifer_Bartholomew (赞：2)

# 模拟
直接模拟横条长度找最大。
```cpp
#include <cstdio>
#include <algorithm>
#define rr register int
using namespace std;
inline int read()
{
    char ch=getchar();
    if(!(~ch))return 0;
    int f=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    int x=0;
    while(ch>='0'&&ch<='9')
    {
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int f[100];
int main()
{
	int n=read(),m=read(),maxn=0;
    for(rr i=0;i<n;++i)//读入
	{
		f[i]=read();
		if(f[i]>maxn)maxn=f[i];
	}
	int ans=0;
    for(rr i=m;i<=maxn;++i)//枚举横条长度
    {
    	rr sum=0;//计可以割出几条横条
    	for(rr j=0;j<n;++j)
    		sum+=f[j]/i;
    	sum*=i;
    	if(sum>ans)ans=sum;//若现在百叶窗面积更大，就更新
    }
	printf("%d\n",ans);
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：Mophie (赞：1)

### CF38C【Blinds】题解

[题目传送门](https://www.luogu.com.cn/problem/CF38C)

简化一下，其实这道题就是求 $\sum_{i=1}^n \left \lfloor \frac{a[i]}{k} \right \rfloor *k(k \geq l)$ 的最大值

那么可以建立一个数组 $p[i]$ 记录一下每个数 $x$ 的 $\left \lfloor \frac{x}{i} \right \rfloor (k \geq l)$

最后统计答案即可

#### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int l,n,ans,a[109],x;
int main()
{
    cin>>n>>l;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        for(int j=l;j<=100;j++)a[j]+=x/j;//记录一下p[i]的值
    }
    for(int i=l;i<=100;i++)ans=max(ans,a[i]*i);//算出答案
    cout<<ans<<endl;//完结撒花
    return 0;
}
```


---

## 作者：xiaozeyu (赞：1)

这竟然是C题？

其实并没有想象中的那么难

第一反应，二分？

脑子中出现了这个题

[网线截取？](https://cdn.luogu.com.cn/upload/image_hosting/0l0w5jkg.png)

看了下要求，然而并不是

![](https://cdn.luogu.com.cn/upload/image_hosting/j4mgq62n.png)

$ 1\le n,l\le 100 $

$ 1\le a_i\le 100 $

这么小的数据直接做 $ n^2$ 的都行

在截取时有两种写法
```cpp
sum=0;
for(int j=1;j<=n;j++)
	sum=sum+a[j]-(a[j]%len);
```
或
```cpp
For(j,1,n)
	if(l[j]>=i)
		ans=ans+l[j]/i*i; 
maxx=max(maxx,ans);
```
即
```cpp
ans=0;
for(int j=1;j<=n;j++)
	ans+=a[j]/i;
if(ans*i>maxn) 
	maxn=ans*i;
```
于是第一次
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,a[105];
int ans,sum;
int main()
{
	cin>>n>>len;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);	
		ans=ans+a[i]-(a[i]%len);
	}
	if(ans==0)
	{
		cout<<"0";
		return 0;
	}
	for(int i=len;i<=100;i++)
	{
		sum=0;
		for(int j=1;j<=n;j++)
			sum=sum+a[j]-(a[j]%len);
		if(sum<ans) break;
		else ans=sum;
	}
	cout<<ans;
}
```

直接ＷＡ了

哪里错了？？

找到了好几个问题，希望看到后的人能够规避

1.  并非是单调性的

```cpp
if(sum<ans) break;
else ans=sum;
```
这个是错的，应该这样写：
```cpp
sum=0;
for(int j=1;j<=n;j++)
	sum=sum+a[j]-(a[j]%i);
ans=max(ans,sum);
```

2. 低级错误

这是很多人都会有的沙雕错误

但我这么写在模拟赛中竟然80分，~~数据太水~~

你看看：

```cpp
sum=sum+a[j]-(a[j]%len);
```
正确的：
```cpp
sum=sum+a[j]-(a[j]%i);
```
好了，易错点说了，拿上两种（3个）代码

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,a[105];
int ans,sum;
int main()
{
	cin>>n>>len;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);	
		ans=ans+a[i]-(a[i]%len);
	}
	if(ans==0)
	{
		cout<<"0";
		return 0;
	}
	for(int i=len+1;i<=100;i++)
	{
		sum=0;
		for(int j=1;j<=n;j++)
			sum=sum+a[j]-(a[j]%i);
		//if(sum<ans) break;
		//else ans=sum;
		ans=max(ans,sum);
	}
	cout<<ans;
}
```
------------
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
using namespace std;
int n,length;
int l[105];
int maxx;
int main(){
	cin>>n>>length;
	For(i,1,n) cin>>l[i];
	For(i,length,100){
		int ans=0;
		For(j,1,n) if(l[j]>=i) ans=ans+l[j]/i*i; 
		maxx=max(maxx,ans);
		if(ans==0) break;
	}
	cout<<maxx;
	return 0;
} 
```
------------
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int maxn=1024;
int n,len,a[maxn],Max=0,ans=0;
int main()
{
	scanf("%d%d",&n,&len);
	For(i,1,n)
	{
		scanf("%d",&a[i]);
		Max=max(Max,a[i]);
	}
	Rep(i,Max,len)
	{
		int cnt=0;
		For(j,1,n)
			cnt+=a[j]/i;
		ans=max(ans,cnt*i);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：houpingze (赞：1)

 ~~蒟蒻又来水题解了~~

进入正题

 思路：~~暴力~~枚举，从$l$~$100$（因为a[i]最大是100），找到大于$l$的所有木板，算出面积：$i*cnt$ （cnt是符合条件的木板数量），然后打擂台，算出面积最大的方案，输出。

想到这个思路，本蒟蒻就打了如下代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,cnt,mx;
int l,a[10000000];
int main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=l;i<=100;i++){
		cnt=0;
		for(int p=1;p<=n;p++){
			if(a[p]>=i) cnt++;
		}
		mx=max(mx,cnt*i);
	}
	printf("%d",mx);
}
```

还没过样例就提交了。

然鹅：WA……扎心。。。

我们来康康哪里错了：
### 题目上说：横条可以切断但不能拼接
# 这说明：一个大于$i$的木板可以分成$a[i]/i$个木板。
 ~~然后终于AC了~~

# AC CODE：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,cnt,mx=0;
int l,a[10000000];//a数组是存储木板长度的 
int main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++){
		cin>>a[i];//输入木板长度 
	}
	for(int i=l;i<=100;i++){
		cnt=0;
		for(int p=1;p<=n;p++){
			cnt+=a[p]/i;//此木板（第p个）可以裁多少个木板（当a[p]<i时这个木板就加0个） 
		}
		mx=max(mx,cnt*i);//打擂台，算出最大面积 
	}
	printf("%d",mx);//输出 
}

```





---

## 作者：happybob (赞：0)

暴力一下。

竟然是C题！

代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[105];

int main()
{
	int n, l;
	cin >> n >> l;
	for (register int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		for (register int j = l; j <= 100; j++)
		{
			a[j] += x / j;
		}
	}
	int maxn = -1;
	for (register int i = l; i <= 100; i++) maxn = max(maxn, a[i] * i);
	cout << maxn << endl;
	//system("pause");
	return 0;
}
```


---

## 作者：Creroity (赞：0)

对于样例一，我觉得应该会有人像我一样懵圈很久。（吧？）

#### 所以先解释一下样例一：（当然你也可以直接去翻译样例说明）

就是可以把 4 切成两个 2 ，然后再把 3 切成 2 和 1 ，拼成一个长 4 宽 2 的百叶窗。

#### 其次是我的思路：

很简单，就是枚举。通过枚举截取的长度来实现寻找最大面积。

每次都将 $tot + a_i \div j$ 就可以啦~

然后一个 max 应该都是没有问题的。但是这里记得将 $tot \times j$ 来计算面积。

最后就是代码啦：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005],ans=-1;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];      //输入 
	for(int i=m;i<=100;i++){
		int tot=0;                       //初始化 
		for(int j=1;j<=n;j++)tot+=a[j]/i;//计算个数 
		if(tot==0)break;                 //一个可有可无的优化 
		ans=max(tot*i,ans);              //计算并比较面积 
	}
	cout<<ans;
	return 0;
}
```
~~求个赞~~

---

## 作者：Lithium_Chestnut (赞：0)

这题是CF的C题？？？

~~好简单~~

算法：模拟。

直接模拟求木条最大长度和面积。

这题的数据范围很重要，因为 $1 \leq a_i \leq 100$，所以模拟的循环从 $l$（最小长度）枚举到101（多一个保险）就可以了。

具体步骤：输入 $n$ 和 $l$，循环读入 $a_i$，开始枚举，每次一定要先把 $ans$（答案）清零，以免有上一轮的残留，然后套二层循环进行枚举宽度，每次 $ans$ 加上 $a_j/i$，让 $ans$ 变成宽度，然后算面积，每次比较**面积**，如果 $ans$ 乘 $i$ 大于 $maxn$（最大面积，初值为 $-1$，便于算最大值），那么 $maxn$ 就设为 $ans$ 乘 $i$，最后枚举下来，$maxn$ 就是最大面积，输出 $maxn$ 即可。

前面讲的应该够清楚了，就不加注释了，放代码！

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,a[10001],ans,maxn=-1;
int main()
{
    cin>>n>>l;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=l;i<=101;i++)
    {
        ans=0;
        for(int j=1;j<=n;j++) ans+=a[j]/i;
        if(ans*i>maxn) maxn=ans*i;
    }
    cout<<maxn;
    return 0;
}return 0;
}
```

---

