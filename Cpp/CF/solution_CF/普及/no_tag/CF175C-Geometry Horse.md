# Geometry Horse

## 题目描述

Vasya plays the Geometry Horse.

The game goal is to destroy geometric figures of the game world. A certain number of points is given for destroying each figure depending on the figure type and the current factor value.

There are $ n $ types of geometric figures. The number of figures of type $ k_{i} $ and figure cost $ c_{i} $ is known for each figure type. A player gets $ c_{i}·f $ points for destroying one figure of type $ i $ , where $ f $ is the current factor. The factor value can be an integer number from $ 1 $ to $ t+1 $ , inclusive. At the beginning of the game the factor value is equal to 1. The factor is set to $ i+1 $ after destruction of $ p_{i} $ $ (1<=i<=t) $ figures, so the $ (p_{i}+1) $ -th figure to be destroyed is considered with factor equal to $ i+1 $ .

Your task is to determine the maximum number of points Vasya can get after he destroys all figures. Take into account that Vasya is so tough that he can destroy figures in any order chosen by him.

## 说明/提示

In the first example Vasya destroys three figures first and gets $ 3·1·10=30 $ points. Then the factor will become equal to $ 2 $ and after destroying the last two figures Vasya will get $ 2·2·10=40 $ points. As a result Vasya will get $ 70 $ points.

In the second example all $ 8 $ figures will be destroyed with factor $ 1 $ , so Vasya will get $ (3·8+5·10)·1=74 $ points.

## 样例 #1

### 输入

```
1
5 10
2
3 6
```

### 输出

```
70```

## 样例 #2

### 输入

```
2
3 8
5 10
1
20
```

### 输出

```
74```

# 题解

## 作者：lightningZ (赞：1)

## 思路
读了题后就能想到，大体的思路就是尽量摔价值小的东西。但是问题就在于我们在处理细节方面，分三种情况：

$1.$ 加上第 $i$ 个物品的数量后，总数量还到不了当前的 $p$。这是最简单的情况，直接把当前的数量加到总数量之后在把答案计算一下就可以。

$2.$ 加上第 $i$ 个物品的数量之后，总数量比当前的 $p$ 还要大。这个时候就要先把总数量补齐到当前的 $p$ ，然后我选择的做法是把当前的数量减去要补齐的值，然后在重新考虑一遍。

$3.$ 加上第 $i$ 个物品的数量之后，总数量比当前的 $p$ 要大，并且 $p$ 已经是最大的了。这个时候就需要记录一下把总数量补齐到 $p$ 之后，直接计算答案即可。注意这时候的 $f=t+1$ 。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
int p[105],f=1,ans,num,cnt,tmp;
struct node
{
	int k,c;
}a[105];
bool cmp(node a,node b)
{
	return a.c<b.c;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].k,&a[i].c);
	sort(a+1,a+n+1,cmp);//很容易想到的结构体排序
	scanf("%lld",&t);
	for(int i=1;i<=t;i++) scanf("%lld",&p[i]);
	for(int i=1;i<=n;i++)
	{
		if(f==t+1)//第三种情况，跳出循环
		{
			tmp=i;
			break;
		}
		if(num+a[i].k<p[f])//第一种情况
		{
			num+=a[i].k;
			ans+=a[i].k*f*a[i].c;
		}
		else if(num+a[i].k==p[f])//因为不会特殊处理所以单独打了一个相等的情况
		{
			num=p[f];
			ans+=a[i].k*f*a[i].c;
			f++;
		}
		else//第二种情况
		{
			ans+=(p[f]-num)*f*a[i].c;//补齐当前的p
			a[i].k-=p[f]-num;
			num=p[f];
			f++;
			i--;//再重新考虑一遍当前a的数量
		}
	}
	if(tmp)//第三种情况跳出循环后的计算答案
	{
		for(int i=tmp;i<=n;i++) ans+=a[i].k*f*a[i].c;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：yuzhechuan (赞：1)

贪心，注意有不少细节，很容易TLE

贪心是显而易见的，每次枚举价值最小的物品，进行销毁操作

朴素的枚举每一件物品复杂度为$O(\sum k_i)$，明显超时

我们注意到朴素的+1枚举中有很多情况是重复的，那就可以通过乘法来跳过

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,m,p[105];
struct obj{int k,c;}a[105];
inline bool cmp(const obj &x,const obj &y){return x.c<y.c;} //按物品数量进行排序
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].k,&a[i].c);
    sort(a+1,a+1+n,cmp);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&p[i]);
    p[m+1]=0x7fffffffffff; //防止f溢出
    int pt=0,f=1; //pt记录已经操作过的物品数
    for(int i=1;i<=n;i++){
        for(int j=1;j<=a[i].k;){
            int how=min(a[i].k-j+1,p[f]-pt); //正解与暴力的区别：要么对该种物品的所有剩余进行操作，要么对到下一个目标所需要的物品数进行操作
            ans+=f*a[i].c*how;
            pt+=how;
            while(pt>=p[f]&&f<=m) f++;
            j+=how;
        }
    }
    printf("%I64d",ans);
}

```

---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF175C)

[CF's link](https://codeforces.com/problemset/problem/175/C)

#### 题意：

有 $n$ 种数字，第 $i$ 种数字的数量为 $k_i$，价值为 $c_i$，依次取走数字，取走某个数字时获得的贡献为 $c_i \times F$。$F$ 表示当前贡献，初始为 $1$。当取走第 $p_i$ 个数字后，$F+1$。可以以任意顺序取走数字，求最大贡献和。

#### Solution：

贪心想到贡献小的应该排在前面，按贡献从小到大取走数字，统计下答案即可。

注意，要添加 $p_{t+1}$ 为无穷大，防止溢出。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-15 19:30:25 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-15 20:00:35
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
/*
快读快输
*/
int n,t,p[105],Ans,F=1,Sum;
struct Goods{
	int K,C;
}G[105];
bool cmp(Goods x,Goods y){
	return x.C<y.C;
}
signed main(){
	n=read();
	FOR(i,1,n) G[i].K=read(),G[i].C=read();
	sort(G+1,G+1+n,cmp);
	t=read();
	FOR(i,1,t) p[i]=read();
	p[t+1]=1e11+5;
	FOR(i,1,n){
		FOR(j,1,G[i].K){
			int x=min(G[i].K+1-j,p[F]-Sum);
			Ans+=F*G[i].C*x;
			Sum+=x;
			while(Sum>=p[F]&&F<=t) F++;
			j+=x-1;
		}
	}
	write(Ans);
	return 0;
}
```





---

## 作者：Suzt_ilymtics (赞：0)

# 写在前面
注意开long long，本人被迫因此重构代码

# 进入正题

### [-->题面](https://www.luogu.com.cn/problem/CF175C)


------------

这个题的主要做法是模拟+一点贪心+小学二年级数学

我们不难想到，把价值高的放在最后摧毁会更优

### 但是，问题来了：

**1、可能将这一类物品摧毁一部分后，就直接进入下一阶段**

**2、可能将这一类物品全部摧毁后，还不能满足下一阶段**

**3、可能将这一类物品全部摧毁后，会横跨好几个阶段**

**4、可能到达最后一个阶段，还有许多物品没有被摧毁**

最后我们直接开始模拟即可

如果遇到我们上述问题，多特判几下


------------

### 具体解释在下面代码中


```cpp
/*
Work by: Suzt_ilymtics

注：变量名zsf，lkp，lzx都是我的学姐，显然lkp没用（到）
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	long long num , c;
	bool operator < (const node & b) const {return c < b.c; }
}a[110];
int n,t,zsf = 1;//zsf贡献因子 
long long p[110], lzx = 0, wz = 1;//lkp摧毁物品数，lzx与下一个阶段的差距 
long long ans = 0;
int max(int x,int y){return x > y ? x : y ;}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i].num,&a[i].c);
	scanf("%d",&t);
	for(int i=1;i<=t;++i) scanf("%lld",&p[i]);
	sort(a+1,a+1+n);
	int i = 1;
	lzx = p[zsf];//算一下差距
	while(i<=n){
		if(a[i].num >= 0 && a[i].num - lzx < 0){//如果当前物品数不够 
			ans += a[i].c * zsf * a[i].num;//先加上当前价值*贡献因子*剩余的数量 
			lzx -= a[i].num;//差距要减掉a[i].num 
			a[i].num = 0;//减完之后还剩0个 
			i++; //换下一个物品 
		 }
		else{//如果够 
			ans += a[i].c * zsf * lzx;//直接加上当前价值*贡献因子*差距的数量 
			a[i].num -= lzx;//当前物品的数量要减去差距 
			if(zsf > t) {
				lzx = max(a[i].num,1);
				continue;//如果 贡献因子超过第t个数，则贡献因子达到最大值 
			}
			zsf++;//贡献因子++ 
			if(zsf > t) continue;
			lzx = p[zsf] - p[zsf-1];//更新差距 
		}
	}
	printf("%lld",ans);
	return 0;
}
```



------------



### 为了卡我自己的而手造的样例：

```cpp
cin:
1
5 1
2
2 3
cout:
10
```


------------


###### 如果您有什么疑问的地方，尽管来私信我

### The end.

---

## 作者：Imy_bisLy (赞：0)

## 十年OI一场空，不开longlong见祖宗
### 首先展现一下血泪史
![血泪史.jpg](https://cdn.luogu.com.cn/upload/image_hosting/g5fpan5x.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
### 本题的思路：
模拟（贪心，大概）+一点点的数学小知识

#### 先摧毁价值小的物品，价值大的后面摧毁，这样可知最终的贡献越大
### 解释一下样例1：

你有1种物品，该物品有5个，每一个的价值为10
有一个长度为2的单调递增序列p序列数值为3和6，
你先摧毁掉了3个物品，贡献值f变为2

这3个物品的总贡献ans=3 * 10 * 1 =30 

后面2个物品被摧毁ans=30 + 2 * 10 * 2 = 20
### 具体解释都在代码中
## code 
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
const int N=120;
struct node{
	long long k,c;
}a[N];
long long n,t,p[N];
bool cmp(node x,node y){
	return x.c<y.c;
}
long long ans,size; //size一共摧毁了几个物品  
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)	
		scanf("%lld%lld",&a[i].k,&a[i].c);
	sort(a+1,a+n+1,cmp);//从价值小的开始摧毁 
	memset(p,0x3f,sizeof(p));//防止超过t的锅掉 
	scanf("%lld",&t);
	for(int i=1;i<=t;i++)	
		scanf("%lld",&p[i]);
	long long f=1;//f贡献因子 
	long long i=1,place=1,m=0,cnt=0;
	while(i<=n){
		if(size+a[i].k<=p[place]) {//如果当前的物品Ki全部摧毁，个数小于等于p[place]
			ans+=(a[i].k*a[i].c*f);//直接加进去 
			size+=a[i].k;//存下个数 
		}
		else{//如果当前的物品Ki全部摧毁，个数大于p[i]
			while(size+a[i].k-cnt>p[place]){ 
			//之前的物品个数+当前的物品个数大于当前P序列 
				m=p[place]-size;// 那么就有m个物品是按之前的贡献值来加和的 
				ans+=m*a[i].c*f;//m个物品的贡献加进答案
				place++ ; //p的指针挪一位 
				f++;//贡献值+1； 
				size+=m;//把这m个物品加到size中 
				cnt+=m;//在a[i].k中已经有cnt个物品被摧毁 
			}
			ans=ans+(a[i].k-cnt)*a[i].c*f;//直接加进去 
			size=size+a[i].k-cnt;//存下个数 
			cnt=0;
		} 
		i++; 
	} //cnt这个细节的处理和m的处理我也就调了一早上
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：泠小毒 (赞：0)

# Geometry Horse
给定n种物品，每种物品有Ki个，价值为Ci，摧毁一个物品的贡献为Ci×f

f为贡献因子，有一个长度为t的单调递增序列p，当前摧毁的物品若超过p[i]，则贡献因子f=i+1

求最大贡献
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190515/)

[博客园(同步更新)](https://www.cnblogs.com/muronglin/p/hgoi-20190515.html)
## 解法
主要题意好难读懂啊emm

读懂之后，是一个显然的贪心，让价值小的先摧毁，价值大的后摧毁，模拟一遍=-=
## ac代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 2333333333333333333
using namespace std;
struct node{int k,c;}a[110];
int n,m,nw=1;
ll ans=0,p[110];
int cmp(node x,node y){return x.c<y.c;}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d",&a[i].k,&a[i].c);
    scanf("%d",&m);
    for(int i=1;i<=m;i++)scanf("%lld",&p[i]);
    for(int i=m;i>1;i--)p[i]-=p[i-1];
    p[m+1]=inf;
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        while(a[i].k>p[nw])ans+=1ll*nw*a[i].c*p[nw],a[i].k-=p[nw],nw++;
        ans+=1ll*nw*a[i].c*a[i].k,p[nw]-=a[i].k;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

