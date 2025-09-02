# Tian Ji -- The Horse Racing

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4090

[PDF](https://uva.onlinejudge.org/external/13/p1344.pdf)

## 样例 #1

### 输入

```
3
92 83 71
95 87 74
2
20 20
20 20
2
20 19
22 18
0```

### 输出

```
200
0
0```

# 题解

## 作者：_蒟蒻—信含_ (赞：6)

### 说在前面
如果提交的时候弹出错误窗口，极大概率是您没有绑定**UVA**

**请*仔细* 阅读下面的文字并重试**
>您提交的代码将被发送回原 OJ进行评测，并由洛谷抓取其评测结果。

>您正在提交 UVA 题库。该题库在境内可访问性较差，如出现各种错误请您过一段时间重试。提交 UVA 题库时服务器将会登录您绑定的账户，请您在本地不要操作 UVA，否则会将服务器的登录踢出而提交失败。

>UVA 题目不支持使用公用账户评测，如果您没有绑定过 UVA 账户，请您绑定个人账户。由于 UVA 在境内可访问性较差，绑定可能会频繁失败，如无法绑定，请您过一段时间重试。

~~啥？你还没注册？~~ [单击此处启动注册向导](https://www.luogu.com.cn/blog/312003829xinhan/zhu-ce-UVA)  
### 正文
非常简单的一道模拟水题  
首先，本题与[**P1650**](https://www.luogu.com.cn/problem/P1650)是差不多的，只不过1650只有一组数据而已

解释标注在代码里

### 警告
直接ctrl+C,ctrl+v会导致CE，请谨慎操作！
### Code
```cpp
#include<iostream>
#incldue<cstdio>
#include<cmath>
#incldue<ctime>
#include<algorithm>
using namespace stO;
long long n,money,x1,x2,y11,y2;//定义一堆变量
int a[10001],b[10001];
int main()
{
//    cin>>n;//把本行的前注释去掉，while屏蔽掉就是P1650的解法
	while(cin>>n&&n!=0)//无尽循环，直到输入一个“0”结束
	{
		for(int i=0;i<n;i++)
    	    cin>>a[i];//读入田忌的（马）车速
    	for(int i=0;i<n;i++)
    	    cin>>b[i];//读入齐王的（马）车速
    	sort(a,a+n);//sort一下
    	sort(b,b+n);//目的是让车速按照升序排序
    	x1=x2=0;
    	y11=y2=n-1;
    	money=0;//这三行是初始化，P1650可以不加带注释的这行
    	while(x1<=y11)
		{
    	    if(a[y11]>b[y2])//田忌的上等马比齐王的上等马快
			{
    	        money+=200;
    	        y11--;
    	        y2--;//这两行意思是双方消耗掉了这匹马，在这里起指针作用
    	    }
    	    else if(a[y11]<b[y2])//古代田忌的方法
			{
    	        money-=200;
    	        x1++;
    	        y2--;//同上
    	    }
    	    else{//如果两人最快马速度一样
    	        if(a[x1]>b[x2]){//如果田忌的下等马比齐王的下等马快
    	            money+=200;
                	x1++;
                	x2++;
            	}
            	else{//要不然就去耗掉齐王的上等马
       		        if(a[x1]<b[y2])
    	                money-=200;
    	            x1++;
    	            y2--;
    	        }
    	    }
    	}
    	cout<<money<<endl;//本题需要加换行，P1650不需要
	}
    return 0;//结束
}
```
***
嗯好了本文结束
### 说在后面
本题为大膜你，也算比较简单 ~~况且可以吃双倍经验~~

---

## 作者：OItby (赞：3)

[传送门](https://www.luogu.org/problemnew/show/UVA1344)$($ $UVA$ $1344$ 【$Tian$ $Ji$ -- $The$ $Horse$ $Racing$】$)$

![样例图(POJ)](http://poj.org/images/2287_1.jpg)


------------

# 分析 $:$ [DP](https://baike.sogou.com/v61658563.htm?fromTitle=%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92) 或 [贪心](https://baike.sogou.com/v1706021.htm?fromTitle=%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95)


------------

## 1.$DP$ $:$ 
设$f[i][j]$表示齐王按从强到弱的顺序出马和田忌进行了$i$场比赛之后，从$"$头$"$取了$j$匹较强的马，从$"$尾$"$取了$i$-$j$匹较弱的马，所能获得的最大盈利。
### 则状态转移方程为:$f[i][j]$ $=$ $max$ $($ $f[i-1][j]$ $+$ $g[n-(i-j)+1][i]$ $,$ $f[i-1][j-1]$ $+$ $g[j][i]$ $;$
其中$g[i][j]$表示田忌的马和齐王的马分别按照由强到弱的顺序排序之后，田忌的第 $i$ 匹马和齐王的第 $j$ 匹马赛跑所能取得的盈利，胜为 $200$ ，负为 $-200$ ，平为 $0$。

### 图解：

![](https://cdn.luogu.com.cn/upload/pic/51624.png)
![](https://cdn.luogu.com.cn/upload/pic/51623.png)


### 动态规划代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N=2001,INF=-2e+8;
int a[N],b[N],f[N][N],g[N][N];

bool Cmp(int x,int y) {return x>y;}

int main()
{
	int n,Ans,i,j;
	while (scanf("%d",&n))
	{
		if (n==0) return 0;
		for (i=1;i<=n;++i) scanf("%d",&a[i]);
		for (i=1;i<=n;++i) scanf("%d",&b[i]);
		sort(a+1,a+n+1,Cmp),sort(b+1,b+n+1,Cmp);
		for (i=1;i<=n;++i)
			for (j=1;j<=n;++j)
			{
				if (a[i]>b[j]) g[i][j]=200;
				else if (a[i]==b[j]) g[i][j]=0;
					 else g[i][j]=-200;
				f[i][j]=INF;
			}
		for (i=1;i<=n;++i)
		{
			f[i][0]=f[i-1][0]+g[n-i+1][i],f[i][i]=f[i-1][i-1]+g[i][i];
			for (j=1;j<i;++j) f[i][j]=max(f[i-1][j-1]+g[j][i],f[i-1][j]+g[n-i+j+1][i]);
		}
		Ans=f[n][1];
		for (i=2;i<=n;++i) Ans=max(Ans,f[n][i]);
		printf("%d\n",Ans);
	}
}
```



------------


## 2.$\text{贪心}$ $($推荐$)$ $:$ 分以下三种情况考虑：

- #### 如果田忌目前的最快马快于齐王目前的最快马，则两者比

- #### 如果田忌的最快马慢于齐王的最快马，则用田忌的最慢马与齐王的最快马比$($减少损失$)$

- #### 如果田忌的最快马和齐王的最快马相等，分以下两种情况：
	1. 若田忌的最慢马快与齐王的最慢马，两者比（能赢就赢呗）
    2. 其他，用田忌的最慢马与齐王的最快马比（贡献最大）


### 贪心代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N=1200;
int a[N],b[N];

void Scanf(int &x)
{
	x=0;
	char s=getchar();
	while(s<'0'||s>'9') s=getchar();
	while(s>='0'&&s<='9') x=x*10+s-'0',s=getchar();
}

int main()
{
	int Ans,n,la,lb,ra,rb,i;
	while (1)
	{
		Scanf(n);
		if (n==0) goto end;
		for (i=1;i<=n;++i) Scanf(a[i]);
		for (i=1;i<=n;++i) Scanf(b[i]);
		sort(a+1,a+n+1),sort(b+1,b+n+1);
		Ans=0,la=lb=1,ra=rb=n;
		for (i=1;i<=n;++i)
		{
			if (a[ra]>b[rb]) Ans+=200,--ra,--rb;
			else if (a[ra]<b[rb]) Ans-=200,++la,--rb;
				 else if (a[la]>b[lb]) Ans+=200,++la,++lb;
				 	  else
				 	  {
				 	  	if (a[la]<b[rb]) Ans-=200;
				 	  	++la,--rb;
					  }
		}
		printf("%d\n",Ans);
	}
	end:
	return 0;
}
```


------------

##### $\color{red}\text{具体见}$
[题解 P1650 【田忌赛马】](https://www.luogu.org/blog/141448/solution-p1650tby)
### 另一种方法：
[POJ 2287 【Tian Ji -- The Horse Racing】](https://www.luogu.org/blog/141448/poj-2287-tian-ji-the-horse-racingtby)

---

## 作者：朱江黄河 (赞：2)

# 贪心

先将田忌的马和齐王的马排一下序，然后按照以下策略进行贪心 
1. 当田忌最慢的马比齐王最慢的马快，赢一场
2. 当田忌最慢的马比齐王最慢的马慢，和齐王最快的马比，输一场
3. 当田忌最慢的马和齐王最慢的马一样时，比较他们最快的马 
4. 当田忌最快的马比齐王最快的马快时，赢一场先。
5. 否则，拿最慢的马和齐王最快的马比。

## 证明

1、2就不解释了

当情况3时，如果我们不比，则少一个平局，但会多赢若干(可能为0)局

所以我们先比较田忌最快的马和齐王最快的马

如果田忌最快的马快，反正田忌最快的马所在那局一定赢，就耗掉齐王最快的马

否则齐王最快的马所在的那局肯定赢不了，就用最慢的马耗掉它。但是这可能会出现本来是平局，用最慢的马就输了的情况，从而不是最优。

仔细想想，发现本来最慢的马是平局(平局才比最快的马)，也就是两个平局，现在最慢的马输了，但其他局至少会多赢一局(比如直接拿田忌最快的马和齐王最慢的马比肯定赢，其他局还不影响)所以是最优解

### 压行不是很严重的代码?
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define maxn 1005
#define inf 0x7fffffff
int n,a[maxn],b[maxn];
void work(){
	for(int i=0;i<n;i++)scanf("%d",a+i);
	for(int i=0;i<n;i++)scanf("%d",b+i);
	sort(a,a+n);sort(b,b+n);
	int ans=0;
	for(int l=0,r=n-1,l1=0,r1=n-1;l<=r&&l1<=r1;){
		if(a[l]>b[l1])l++,l1++,ans++;
		else if(a[l]<b[l1])l++,r1--,ans--;
		else if(a[r]>b[r1])r--,r1--,ans++;
		else ans-=a[l]!=b[r1],l++,r1--;
	} 
	printf("%d\n",ans*200);
}
int main(){
	while(~scanf("%d",&n)&&n)work();
	return 0;
}
```

---

## 作者：做梦想Peach (赞：1)

这题的样例输出有一点小问题，就是要**换行**，管理大大看到时希望可以改下哈。

----
QwQ，这是一道双倍经验的题目呢，原题是洛谷的[P1650 田忌赛马](https://www.luogu.com.cn/problem/P1650)。

都是一道经典的贪心题目。

1. 将田忌和齐王的马进行排序。
1. 然后将田忌最大的马与国王的进行比较。
1. 如果田忌最大的马大于国王的，那么就胜场加一。
1. 如果田忌最大的马小于国王的，那么就一定会输，所以用田忌最小的马输给国王最大的马。
1. 如果田忌最大的马等于国王的，那么就比较最小的马。

接下来代码也就呼之欲出了。


```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
int a[2010],b[2010],n;
int main () {
	while (scanf ("%d",&n)) {
		if (n==0) 
			return 0;
		for (int i=0;i<n;i++) scanf ("%d",&a[i]);
		for (int i=0;i<n;i++) scanf ("%d",&b[i]);
		sort (a,a+n);
		sort (b,b+n);//排序
		int i=0,j=n-1;
		int t=0,k=n-1,cnt=0;
		int x=0,y=0;
		while (cnt<n) {
			if (a[j]>b[k]) {
				x++;
				j--;
				k--;
				cnt++;
			} 
			else {
				while (a[i]>b[t]&&cnt<n) {
					x++;
					i++;
					t++;
					cnt++;
				}
				if(cnt==n) 
					break;
				if (a[i]<b[k]) y++;
				i++;
				k--;
				cnt++;
			}
			if (j<0||k<0)
				break;
		}
		printf ("%d\n",(x-y)*200);
	}
	return 0;
}
```

---

