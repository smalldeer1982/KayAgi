# Karen and Coffee

## 题目描述

To stay woke and attentive during classes, Karen needs some coffee!

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF816B/84ca24fa194ecce1cb9c3e825b543dfb7809c444.png)Karen, a coffee aficionado, wants to know the optimal temperature for brewing the perfect cup of coffee. Indeed, she has spent some time reading several recipe books, including the universally acclaimed "The Art of the Covfefe".

She knows $ n $ coffee recipes. The $ i $ -th recipe suggests that coffee should be brewed between $ l_{i} $ and $ r_{i} $ degrees, inclusive, to achieve the optimal taste.

Karen thinks that a temperature is admissible if at least $ k $ recipes recommend it.

Karen has a rather fickle mind, and so she asks $ q $ questions. In each question, given that she only wants to prepare coffee with a temperature between $ a $ and $ b $ , inclusive, can you tell her how many admissible integer temperatures fall within the range?

## 说明/提示

In the first test case, Karen knows $ 3 $ recipes.

1. The first one recommends brewing the coffee between $ 91 $ and $ 94 $ degrees, inclusive.
2. The second one recommends brewing the coffee between $ 92 $ and $ 97 $ degrees, inclusive.
3. The third one recommends brewing the coffee between $ 97 $ and $ 99 $ degrees, inclusive.

A temperature is admissible if at least $ 2 $ recipes recommend it.

She asks $ 4 $ questions.

In her first question, she wants to know the number of admissible integer temperatures between $ 92 $ and $ 94 $ degrees, inclusive. There are $ 3 $ : $ 92 $ , $ 93 $ and $ 94 $ degrees are all admissible.

In her second question, she wants to know the number of admissible integer temperatures between $ 93 $ and $ 97 $ degrees, inclusive. There are $ 3 $ : $ 93 $ , $ 94 $ and $ 97 $ degrees are all admissible.

In her third question, she wants to know the number of admissible integer temperatures between $ 95 $ and $ 96 $ degrees, inclusive. There are none.

In her final question, she wants to know the number of admissible integer temperatures between $ 90 $ and $ 100 $ degrees, inclusive. There are $ 4 $ : $ 92 $ , $ 93 $ , $ 94 $ and $ 97 $ degrees are all admissible.

In the second test case, Karen knows $ 2 $ recipes.

1. The first one, "wikiHow to make Cold Brew Coffee", recommends brewing the coffee at exactly $ 1 $ degree.
2. The second one, "What good is coffee that isn't brewed at at least $ 36.3306 $ times the temperature of the surface of the sun?", recommends brewing the coffee at exactly $ 200000 $ degrees.

A temperature is admissible if at least $ 1 $ recipe recommends it.

In her first and only question, she wants to know the number of admissible integer temperatures that are actually reasonable. There are none.

## 样例 #1

### 输入

```
3 2 4
91 94
92 97
97 99
92 94
93 97
95 96
90 100
```

### 输出

```
3
3
0
4
```

## 样例 #2

### 输入

```
2 1 1
1 1
200000 200000
90 100
```

### 输出

```
0
```

# 题解

## 作者：智子·起源 (赞：45)

#### “可笑名义上的监管，影身在迷雾之间。靠题解来获得存在感~~”


------------
## ~~第一篇题解的详细版~~
------------

### 总体思路：


------------

### 1、用一个数组来存放当前温度的推荐个数。


------------

### 2、用部分和数组来存放从温度1~当前已经有多少个推荐温度。


------------

### 3、依次读入q组数据，每读入一组就输出当前区间的推荐温度个数（引用上面的部分和数组）


------------

这道题在给第一步数组赋值时，直接用for循环直接处理会超时，所以可以用差分来优化。（其实蒟蒻也不知道差分是什么）
    
  其原理是：再开一个数组（好多数组啊……QAQ）来存当前推荐个数的加减情况（从左端点开始加1，从右端点+1位开始减1），到输完n组数据之后再用第一步的数组来统计。（真的看不懂的话看看下面的程序^_^）

献上代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,k,f[200000+5],ff[200000+5],fff[200000+5],a,b;
int main()
{
  scanf("%d%d%d",&n,&k,&m);
  for(int i=0;i<n;i++)
  {
    scanf("%d%d",&a,&b);
    ff[a]++,ff[b+1]--;
  }
  for(int i=1;i<=200000;i++)
  {
    f[i]=f[i-1]+ff[i];
    if(f[i]>=k)fff[i]=fff[i-1]+1;
      else fff[i]=fff[i-1];
  }
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&a,&b);
    printf("%d\n",fff[b]-fff[a-1]);
  }
  return 0;
}
```
#### 如果这篇题解帮助了你，妾身想让你帮忙点个赞，谢谢！^_^

---

## 作者：AISakura (赞：12)

### 这是蒟蒻的第一篇题解emmmmm
#### 如果排版不好请各位见谅  
刚开始没看到数据范围和难度标签，十分naive地暴力模拟了一通，果断TLE.复杂度O(2n*n)

然后很自然地想到可以前缀和搞一搞，发现如果是极端数据，那么仅仅模拟计算所有温度被提到的次数就会T掉，前缀和有没有都一样.复杂度O(n*n+n)   
(复杂度仍为同一个大阶，常数/2并没有什么用)
 
但蒟蒻的我仍然抱着希望数据水的侥幸态度,试着交了一发，果然又T了.  
以下是错误代码
```cpp
#include<iostream>       
#include<cstdio>  
using namespace std;  
int t[200001],s[200001];   
int main(){  
	int n,k,q,a,b;
	scanf("%d%d%d",&n,&k,&q);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		for(int j=a;j<=b;j++)
			t[j]++;
	}
	for(int i=1;i<=200001;i++)
		if(t[i]>=k)
			t[i]=1;
		else
			t[i]=0;
	for(int i=1;i<=200001;i++)
		s[i]=t[i]+s[i-1];
	for(int i=1;i<=q;i++){
		scanf("%d%d",&a,&b);
		printf("%d\n",(s[b]-s[a]+t[a]));
	}
	return 0;
}
```

十分难受地去看题解，发现楼下dalao是差分A的   
可是我想要使用一些奇技淫巧  
~~其实是蒟蒻还不会差分，分块对蒟蒻来说更是不可能学过的~~

然后想到不直接模拟的话，可以用结构体保存每个区间的左右边界，用一个计数器tot扫过每一个温度来统计当前温度在几个区间内；然后再前缀和跑一遍就好了.O(n)即可实现 .具体实现见代码中注释
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int s[200001],te[200001];
struct qj{               //结构体-
	int l,r;
}t[200001];
int main(){
	int n,k,q,a,b,tot=0;
	scanf("%d%d%d",&n,&k,&q);
	for(int i=1;i<=n;i++){                //输入左右边界
		scanf("%d%d",&a,&b);
		t[a].l++;   t[b].r++; 
	}
	for(int i=1;i<=200001;i++){            //tot遇到一个温度就加上在该温度上的左边界数，
                                           //减去前一个温度上的右边界数，即为当前温度所在的区间数.
		tot+=t[i].l;   tot-=t[i-1].r; 	 //即可实现O(n)时间内计算每一温度
		te[i]=tot;          
	}
	for(int i=1;i<=200001;i++)             //判断是否大于等于k
		if(te[i]>=k)
			te[i]=1;
		else
			te[i]=0;
	for(int i=1;i<=200001;i++)             //前缀和
		s[i]=te[i]+s[i-1];
	for(int i=1;i<=q;i++){
		scanf("%d%d",&a,&b);
		printf("%d\n",(s[b]-s[a]+te[a]));
	}
	return 0;
}
```
emmm差不多就是这样  
这题给我的教训是应该向楼下大佬一样好好学习差分  
但蒟蒻我的方法也不失为一种增加思维量，减少代码量的折中方法  
希望对各位有帮助(虽然这好像是道冷门题，应该没多少人)

---

## 作者：欧鹰 (赞：6)

（日常聊天），三篇啦，~~希望可以过~~。



------------

看着题解中，各位大佬的代码，表示蒟蒻打了个线段树。

1. 先来个差分，统计每个区间加了几次。

2. 然后统计哪个温度大于等于k，线段树单点加1.

3. 区间求和。

```cpp
#include<bits/stdc++.h>

using namespace std;

int a[2005005],sum[2005005],tree[2005005],n,k,q;

void modify(int u,int l,int r,int x)
{
	if(l==r&&l==x)
	{
		tree[u]=1;
		
		return;
    }
    
    int mid=(l+r)/2;
    
    if(x<=mid) modify(u*2,l,mid,x);
    
    else modify(u*2+1,mid+1,r,x);
    
    tree[u]=tree[u*2]+tree[u*2+1];
}

int query(int u,int l,int r,int x,int y)
{
	if(l>=x&&r<=y) return tree[u];
	//if(u==2) cout<<1;
	int mid=(l+r)/2,ans=0;
	
	if(x<=mid) ans+=query(u*2,l,mid,x,y);
	
	if(y>mid) ans+=query(u*2+1,mid+1,r,x,y);
	
	return ans; 
}

int main()//主程序 
{
	cin>>n>>k>>q;
	
	for(int i=1;i<=n;i++)
	{
		int u,v;
		
		cin>>u>>v;
		
		if(u>v) swap(u,v);
		
		a[u]++;
		
		a[v+1]--;
	}
	
	for(int i=1;i<=200000;i++) sum[i]=sum[i-1]+a[i];

	for(int i=1;i<=200000;i++) if(sum[i]>=k) modify(1,1,200000,i);
	
	while(q--)
	{
		int l,r;
		
		cin>>l>>r;
		
		if(l>r) swap(l,r);
		
		cout<<query(1,1,200000,l,r)<<'\n';
	}
	
	return 0;
	
}
 
```


---

## 作者：锦瑟，华年 (赞：5)

恕我直言，这题实在太水了，普及-了不得了。

好了，题目如下：

可怜是咖啡的狂热爱好者,她去看了n本食谱,每本上面写着在[l,r]两个温度之间煮咖啡会使咖啡有最好的口感.可怜认为若大于或者等于k本食谱上面都认为a度有最好的口感,则她认为a度是一个推荐温度.她有q个询问,每个询问给出a,b,询问[a,b]之间有多少个推荐温度。（输入第一行为n,k,q）

本题思路：差分+前缀和

首先，我们来了解一下差分是什么：输入l和r，在l和r之间每个数都加上一个数。

那么我们如何实现呢？简单，开一个桶，在a[l]上加上这个数，再在a[r+1]上减去这个数（使其到了r+1时就自动抵消了）。由于输入通常不是一组l,r，所以，把l,r全部输进来，进行以上操作，最后从头到尾遍历一遍，把a[i]+=a[i-1]即可。

差分代码：

	int max=0;
	for(i=1;i<=n;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		f[a]+=c;f[b+1]-c;
		if(b>max)max=b;
	}
	for(i=1;i<=max;i++){
		f[i]=f[i-1]+f[i];
	}
    
好了，前缀和是什么呢？即计算l至r这一段区间的和。先计算从头到每一个数的之间的数的总和，最后输出时，把a[r]-=a[l-1]即可。代码：

	for(i=1;i<=n;i++){
		f[i]+=f[i-1];
	}
    
很显然了，此题先用差分把每一本书的推荐温度记在一个桶上，再用前缀和计算推荐温度个数，最后输出即可。

代码：

	#include<stdio.h>
	using namespace std;
	int f[200005];
	int main(){
		int n,m,k;
		scanf("%d%d%d",&n,&m,&k);
		int i;
		int max=0;
		for(i=1;i<=n;i++){//差分代码
			int a,b;
			scanf("%d%d",&a,&b);
			f[a]+=1;f[b+1]-=1;
			if(b>max)max=b;
		}
		for(i=1;i<=max;i++){
			f[i]=f[i-1]+f[i];
		}
		for(i=1;i<=200000;i++){//前缀和
			if(f[i]>=m)f[i]=1+f[i-1];
			else f[i]=f[i-1];
		}
		for(i=1;i<=k;i++){
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",f[r]-f[l-1]);//前缀和计算
		}
		return 0;
	} 

---

## 作者：Khassar (赞：4)

一开始看到题，我以为是一道见过的分块题~~（哎呀，好麻烦不想写分块，人家只是来水题的啊）~~，然后看见难度  -  入门？？？？？

入门 那肯定不是分块啊，然后发现最终的询问可以用前缀和搞，前面那一套选温度（？）可以差分，这个问题就变成了一道两遍前缀的水题了。

怀着~~偷税~~愉悦的心情我交了一发，第三个点就WA了（也就是只过了样例两个点）？

终于到了我写这篇水题题解的目的了—— 我非常naive的在选温度时求了个温度上界出来，以为可以跑得快一点。

```
int l=read(),r=read();
a[l]++;a[r+1]--;
up=max(up,r+1);//就是这个
```

然后它就在询问时问了个更大的温度，导致前缀没有更新到哪里，就变成了0

比如：

2 1 1

1 1

90 100

99 200

希望大家不要像我一样蠢，特写此篇题解，对于前缀怎么写，请看代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>

#define ll long long
#define R register
#define IL inline
#define Rf(a,b,c) for(R int (a)=(b);(a)<=(c);++(a))
#define Tf(a,b,c) for(R int (a)=(b);(a)>=(c);--(a))
#define MES(a,b) memset((a),(b),sizeof((a)))
#define MEC(a,b) memcpy((a),(b),sizeof((b)))
#define D double

using namespace std;

const int N=200005;

int n,k,q,a[N],b,c[N],up;

IL int read() {
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
    return x*f;
}
IL void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

signed main()
{
	n=read();k=read();q=read();
	Rf(i,1,n) {
		R int l=read(),r=read();
		a[l]++;a[r+1]--;//差分
		up=max(up,r+1);
	}
	up=N-3;
	Rf(i,1,up) {
		b+=a[i];//差分的前缀和为原位置上的值
		if(b>=k) c[i]=1;//大于k就是1，表示这个可以
		c[i]+=c[i-1];//询问的前缀和
	}
	Rf(i,1,q) {
		R int l=read(),r=read();
		write(c[r]-c[l-1]);//前缀和求l~r答案
		putchar('\n');
	}

    return 0;
}
```


---

## 作者：wzm2007 (赞：2)

    只需要用差分来维护每种温度的认可度,再用前缀和处理询问即可
    代码如下:

------------

    #include<bits/stdc++.h>
    using namespace std;
    int a[200010],sum[200010];
    int main()
    {
        int n,k,q,l,r,sum1=0,sum2=0;
        cin>>n>>k>>q;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&l,&r);
            a[l]++,a[r+1]--;  //差分
        }
        for(int i=1;i<=200000;i++)
        {
            sum1+=a[i];  //累计
            if(sum1>=k)sum2++;  //判断是否超过k
            sum[i]=sum2;  //前缀和数组
        }
        for(int i=0;i<q;i++)
        {
            scanf("%d%d",&l,&r);
            printf("%d\n",sum[r]-sum[l-1]);  //前缀和
        }
        return 0;  //完美结束
    }

---

