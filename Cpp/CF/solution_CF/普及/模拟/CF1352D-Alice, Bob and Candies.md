# Alice, Bob and Candies

## 题目描述

**题意：**

Alice和Bob两人轮流在数组a中取数，一个从左端开始（第一次取$a_1$）,另一个从右端开始，取得的元素和必须严格大于上一个人取得的元素和，数组元素全部取完时，输出回合数以及两人取得的数的总和。

## 样例 #1

### 输入

```
7
11
3 1 4 1 5 9 2 6 5 3 5
1
1000
3
1 1 1
13
1 2 3 4 5 6 7 8 9 10 11 12 13
2
2 1
6
1 1 1 1 1 1
7
1 1 1 1 1 1 1```

### 输出

```
6 23 21
1 1000 0
2 1 2
6 45 46
2 2 1
3 4 2
4 4 3```

# 题解

## 作者：b6e0_ (赞：5)

打完CF又来写题解啦~求兹磁qwq（第一次AK CF比赛）

[CF题面传送门](https://codeforces.com/contest/1352/problem/D) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1352D) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1352D)

膜你题。按照题意膜你即可。具体细节看代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010];
int main()
{
	int t,n,i,j,tot,sum,p,A,B;//i和j分别表示Alice和Bob在哪，tot记录走了多少步，sum记当前吃的糖的大小和，p为上一次吃的糖的大小和，A和B分别为Alice和Bob共吃了多少大小的糖
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(i=1;i<=n;i++)
			cin>>a[i];
		tot=A=B=p=0;//清零
		for(i=1,j=n;i<=j;)
		{
			sum=0;
			for(;i<=j&&sum<=p;i++)
				sum+=a[i];//累加
			if(i<=j)//如果成立，则下面还会有Bob的一轮
				tot+=2;
			else//如果不成立，则这一轮后游戏就结束了
				tot++;
			A+=sum;//累加
			p=sum;//更新
			sum=0;
			for(;i<=j&&sum<=p;j--)
				sum+=a[j];
        	//这儿没有tot++
			B+=sum;//累加
			p=sum; //更新
		}
		cout<<tot<<' '<<A<<' '<<B<<endl;
	}
	return 0;
}
```
时间复杂度为$O(tn)$。

---

## 作者：__int127 (赞：1)

## CF1352D Alice, Bob and Candies 题解

#### [题目传送门](https://www.luogu.com.cn/problem/CF1352D)

### 题目大意

本题有多组数据。

有由 $n$ 个糖果组成的序列 $a$，第 $i$ 个糖果上有数值 $a_i$，有两个人分别从两端吃糖果，每次吃**若干个**糖果，**每次每个人**吃糖果被称为一回合，每次吃的糖果上数值之和需大于上一次另一人吃的糖果数值之和，如果最后把糖果吃完时，最后吃糖果的人吃的糖果上数值之和还是没有上一次另一人吃的糖果数值之和，则这个人这一回合吃的糖果上数值之和就为刚才吃的糖果上数值之和。
### 思路

根据题意可知有两个人在两端吃糖果，可以定义两个指针 $l$ 和 $r$，当 $l-1=r$（或者 $r+1=l$）时，说明糖果已经吃完（$l$ 和 $r$ 表示的是下一个待吃的糖果），退出循环，读入下一组数据。

具体如何实现呢？来看一下两个指针的移动过程，以下用样例 \#1 的第一组数据举例（$n=11,a={\{3,1,4,1,5,9,2,6,5,3,5\}}$）。

未开始吃时：

![](https://cdn.luogu.com.cn/upload/image_hosting/xp5grz20.png)

第 $1$ 回合：

![](https://cdn.luogu.com.cn/upload/image_hosting/ymvbzfbb.png)

第 $2$ 回合：

![](https://cdn.luogu.com.cn/upload/image_hosting/un01f9of.png)

第 $3$ 回合：

![](https://cdn.luogu.com.cn/upload/image_hosting/d9n1lia4.png)

第 $4$ 回合：

![](https://cdn.luogu.com.cn/upload/image_hosting/azkz94fs.png)

第 $5$ 回合：

![](https://cdn.luogu.com.cn/upload/image_hosting/f0h1b56g.png)

第 $6$ 回合：

![](https://cdn.luogu.com.cn/upload/image_hosting/dzmk12b0.png)

（由于不同的设备和界面可能会导致指针错位，这里采用图片的方式呈现，清晰度会有所降低）

此时 $l-1=r$，退出循环，加和也已经计算好，输出就可以了，那么来看代码吧。

### 代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[1005], l, r;
int sum_l, sum_r, up_l, up_r;
int hs;
int main(){
	cin >> t;
	while (t--){
		cin >> n;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
		}
		l = 1, r = n;
		if (l == r){// 特殊判定：如果只有一个糖果
			cout << "1 " << a[1] << " 0\n";
			continue;
		}
		while (1){
			if (l >= r + 1){
				break;
			}
			hs++;// 回合数 +1
			while (up_l <= up_r){
				if (l - 1 == r){
					break;
				}
				up_l += a[l];// 计算左加和
				l++;
			}
			sum_l += up_l;// 总数加加和
			up_r = 0;// 右加和重置
			if (r <= l - 1){
				break;
			}
			hs++;// 回合数 +1
			while (up_r <= up_l){
				if (r + 1 == l){
					break;
				}
				up_r += a[r];// 计算右加和
				r--;
			}
			sum_r += up_r;// 总数加加和
			up_l = 0;// 左加和重置
		}
		cout << hs << " " << sum_l << " " << sum_r << "\n";// 输出并换行
		// 以下全部为重置变量
		hs = 0;
		sum_l = 0;
		sum_r = 0;
		up_l = 0;
		up_r = 0;
	}
	return 0;
}
```

### 最后
本篇题解过长，感谢认真观看，希望大家能看懂、有思路。

---

## 作者：封禁用户 (赞：1)

一道模拟题，就按照题目说的从两边往中间扫呗，然后加一个 $\text{while}$ 循环直接模拟，多了就吐出来就行了。

具体见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n,a[N];
inline int readint(int &x,short f=1){
	x=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
int main(){
	readint(t);
	while(t--){
		readint(n);
		for(int i=1;i<=n;i++)readint(a[i]);
		int now1=0,now2=0,cnt=0,ans1=0,ans2=0;
		int l=0,r=n+1;bool flag=false;
		while(l<r){
			cnt++;
			if(!flag){
				now1=0;
				while(now1<=now2)l++,now1+=a[l];//从左往右吃
				if(l>=r){
					while(l>=r)now1-=a[l],l--;
					l++;//多了吐出来
				}ans1+=now1;
			}else{
				now2=0;
				while(now2<=now1)r--,now2+=a[r];//从右往左吃
				if(l>=r){
					while(r<=l)now2-=a[r],r++;
					r--;//多了吐出来
				}ans2+=now2;
			}
			flag=!flag;
			if(l==r-1)break;//相遇就结束
		}
		cout<<cnt<<" "<<ans1<<" "<<ans2<<endl;
	}
	return 0;
}
```


---

## 作者：Edmundino (赞：1)

# 题意

给你一个长度为 $n$ 的数组，

第 $i$ 个数表示第 $i$ 个位置有 $a_i$ 个糖果。

有两个人分别从前和后来吃连续一段的糖果，

从前面吃的人先开始，

两个人每次吃的糖果要比另一个人上次吃的糖果多。

例子：

```
 if n=11 and a=[3,1,4,1,5,9,2,6,5,3,5] ,
 第一次前面的人吃了三个糖果，
 第二次后面的人吃了五个糖果（因为5>3，所以不用继续吃了）
 第三次前面的人要吃1+4+1=6个糖果，这样才能大于5。
 第四次后面的人要吃3+5=8个糖果，这样才能大于6
 第五次前面的人要吃5+9=14个糖果，这样才能大于8
 第六次后面的人无论怎么吃，都不能大于14，所以他只能把剩下的2+6=8个糖果吃掉，游戏结束。
```

# 分析

其实这题就是一道模拟，

我们先用个$while$循环，停止条件即为当所以的数都访问过一次的时候。

接着，我们要有个记住步数的变量$ans$（初始为$0$),

当 $ans$ 为偶数时，我们就从前面去模拟，

当 $ans$ 为奇数时，我们就从后面去模拟，

如何模拟：

当时前面的时候，我们把这次吃的数量记为 $tot$,

后面则是 $res$,

当前面时，我们先把 $tot$ 清 $0$，

然后不断去取后面的数，当 $tot > res$ 结束。

后面的也是这样。


# 代码
**模拟部分**
```cpp
		while(e<n)
		{

        int o=0;
			if(ans%2==0)
			{
				tot=0;
				while(x<=y)
				{
					tot+=a[x];
					x++;
					e++;
					if(tot>res)
					{
						s+=tot;
						o=1;
						break;
					}
					  
				}
				if(o==0)
				{
					ans++;
					s+=tot;
					break;
				}
			}
			else
			{
				res=0;
				while(y>=x)
				{
					res+=a[y];
					y--;
					e++;
					if(res>tot)
					{
						d+=res;
						o=1;
						break;
					}
					
				}
				if(o==0)
				{
					ans++;
					d+=res;
					break;
				}
			}
			ans++;
		}
```



**$AC$代码**

~~这份代码有我当时脑残写了一个前缀和和后缀和，不用管他~~

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<iomanip>
 
using namespace std;
 
const int N=1050; 
 
int t,n,k,s,d,e,a[N],b[N],c[N];
 
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		b[0]=0;
		for(int i=1;i<=n;i++)
	    {
	    	cin>>a[i];
	    	b[i]=b[i-1]+a[i];
		}
		c[n+1]=0;
		for(int i=n;i>=1;i--)
		{
			c[i]=c[i+1]+a[i];
		}
		s=d=e=0;
		int ans=0,x=1,y=n,tot=0,res=0;
		while(e<n)
		{

        int o=0;
			if(ans%2==0)
			{
				tot=0;
				while(x<=y)
				{
					tot+=a[x];
					x++;
					e++;
					if(tot>res)
					{
						s+=tot;
						o=1;
						break;
					}
					  
				}
				if(o==0)
				{
					ans++;
					s+=tot;
					break;
				}
			}
			else
			{
				res=0;
				while(y>=x)
				{
					res+=a[y];
					y--;
					e++;
					if(res>tot)
					{
						d+=res;
						o=1;
						break;
					}
					
				}
				if(o==0)
				{
					ans++;
					d+=res;
					break;
				}
			}
			ans++;
		}
		cout<<ans<<" "<<s<<" "<<d<<endl;
	}
}
```



---

## 作者：Jerry_heng (赞：0)

（一）

直接模拟。

用 $l$ 和 $r$ 记录当前左端点和右端点编号。

用 $step$ 记录步数。

用 $slnow$ 和 $srnow$ 记录有超过的数以及当前累加和。

用 $sl$ 和 $sr$ 记录从左到右和从右到左的和。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1001];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int l=2,r=n,slnow=a[1],srnow=0,sl=a[1],sr=0,step=1;
		bool flag=1;
		while(l<=r){
			step++;
			if(flag){
				while(l<=r&&srnow<=slnow){
					srnow+=a[r];
					sr+=a[r];
					r--;
				}
				flag=0,slnow=0;
			}
			else{
				while(l<=r&&slnow<=srnow){
					slnow+=a[l];
					sl+=a[l];
					l++;
				}
				flag=1,srnow=0;
			}
		}
		cout<<step<<" "<<sl<<" "<<sr<<endl;
	}
	return 0;
}
```

---

## 作者：Nemonade (赞：0)

提供一份比较简洁也比较快的代码。

当然这是个模拟。首先游戏结束的原因只有两个人已经把所有糖取完了。这意味着有可能在 Alice 取完之后 Bob 没办法取了，要特判。还有就是记住不要多测不清空。

用了 while 再加快读快输所以常数小也比较简洁，成功卡进最优解第二位。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rd() read<int>()
#define wt(x) write<int>(x) 
#define pfor(i,x,y) for(register int i=x;i<=y;++i)
#define mfor(i,x,y) for(register int i=x;i>=y;--i)
template<typename T>
inline T read(){
	T x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=true;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
template<typename T>
inline void write(T x){
	if(x<0){putchar('-');x=-x;}
	if(x/10) write(x/10);
	putchar((x%10)^48);return;
}
const int N=1e3+5;
using std::max;using std::min;using std::abs;
using std::cin;using std::cout;using std::endl;
int n,l,r,resl,resr,sum,last,cnt,a[N];
signed main(){
	int T=rd();
	while(T--){
		l=1,n=r=rd(),resl=resr=last=cnt=0;
		pfor(i,1,n) a[i]=rd();
		while(l<=r&&++cnt){
			sum=0;
			while(l<=r&&sum<=last) sum+=a[l++];
			resl+=sum,last=sum,sum=0;
			if(l<=r) ++cnt;//只有当有糖的情况下才可以进入Bob的回合 
			else break;
			while(l<=r&&sum<=last) sum+=a[r--];
			resr+=sum,last=sum;
		}
		wt(cnt),putchar(' '),wt(resl),putchar(' '),wt(resr),puts("");
	}
	return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

### 题目简化和分析：

这题可以直接按照题意进行模拟，当然有些细节需要注意。  

翻译的不足：这里的回合指任意一个人吃掉都算，而不是双方一个回合，最后一个人即使不满足也算一个回合。    

我们可以采用两个指针模拟两个人吃的位置，并按照题意进行模拟即可！   

### Solution:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n;
int a[1010];
int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		int l=1,r=n;
		int ans=0,lans=0,rans=0,lres=0,rres=0;
		while(l<=r){
			lres=0;
			while(lres<=rres&&l<=r){
				lres+=a[l];
				++l;
			}
			++ans;
			lans+=lres;
			if(l>r) break;
			rres=0;
			while(rres<=lres&&l<=r){
				rres+=a[r];
				--r;
			}
			++ans;
			rans+=rres;
			if(l>r) break;
		}
		printf("%d %d %d\n",ans,lans,rans);
	}
}
```

---

## 作者：do_while_true (赞：0)

直接模拟游戏过程即可，采用双指针往中间扫。

更多的在于代码中的细节。

[$\mathcal{Code}$](https://codeforces.com/contest/1352/submission/79539333)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[100010];
int sum[100010],sum2[100010],ans1,ans2,l,r,cnt,now1,now2;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		now1=now2=cnt=ans1=ans2=0;
		//now1,now2为左,右指针上一次一共扫了多少
		//cnt为扫了多少次
		//ans1,ans2为左，右指针总共扫了多少 
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		l=0;r=n+1;//两个指针往中间扫 
		bool f=0;//f代表的是不同的人走 
		while(l<r)
		{
			cnt++;//一个回合 
			if(!f) {//左指针往中间走 
				now1=0;
				while(true) {
					l++;
					now1+=a[l];
					if(now1>now2) break;
				}//当now1扫超过了now2就跳出 
				if(l>=r) {//即把剩下的全部拿走 
					while(l>=r) {
						now1-=a[l];
						l--;
					}
					l++;
				}
				ans1+=now1;//累加 
			}
			else {//同上 
				now2=0;
				while(true) {
					r--;
					now2+=a[r];
					if(now2>now1) break;
				}
				if(l>=r) {
					while(r<=l) {
						now2-=a[r];
						r++;
					}
					r--;
				}
				ans2+=now2;
			}
			f=!f;
			if(l==r-1) break;//如果两个指针恰好全部分配完，跳出 
		}
		printf("%d %d %d\n",cnt,ans1,ans2);
	}
}
```


---

