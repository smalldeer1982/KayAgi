# [CSGRound3] 斗牛

## 题目背景

又是一年过去了。小 Z 在春节期间可以好好的放松放松，于是小 Z 和小伙伴们玩起了牛哄哄（斗牛）。

游戏规则是这样的：

给定 $5$ 张牌，分别从 $1 \sim 10$。你需要挑选其中的三张牌加起来是 $10$ 的倍数，另外两张牌的和的个位数则为你最后获得的点数，特别的，如果这两张牌的和是 $10$ 的倍数，则点数为 $10$，也叫做牛哄哄。如果不能构成 $10$ 的倍数，则点数为 $0$，也叫做牛不拢。

如 $5$ $3$ $2$ $3$ $4$ 的点数是 $7$，又叫做牛七。

小 Z 觉得玩的不过瘾，于是对上述规则进行了一些改变。

## 题目描述

给定 $n$ 张牌，牌的大小为 $1 \sim 10$。你需要挑选其中的 $n-2$ 张牌加起来是 $10$ 的倍数，另外两张牌和的个位数即为你所获得的点数。特别地，如果这两张牌的和是 $10$ 的倍数，则点数为 $10$，也叫做牛哄哄。如果任意 $n-2$ 张牌不能构成 $10$ 的倍数，则点数为 $0$，也叫做牛不拢。

由于小 Z 想要更开心的玩耍，所以需要你来完成这个程序来帮助小 Z 在 $1$ 秒内知道点数。

## 说明/提示

**【样例 1 解释】**

$10$ $10$ $10$ 三张牌凑成 $10$ 的倍数，$2+3=5$。

**【样例 2 解释】**

任意三张牌都不能凑成 $10$ 的倍数。

---

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（50 points）：$n = 5$。
- Subtask 2（30 points）：$n \le 5 \times 10^3$。
- Subtask 3（20 points）：无特殊限制。

对于 $100\%$ 的数据，$5 \le n \le 10^6$。



## 样例 #1

### 输入

```
5
10 10 10 2 3```

### 输出

```
5```

## 样例 #2

### 输入

```
5
3 4 5 6 7```

### 输出

```
0```

# 题解

## 作者：wpy233 (赞：22)

怎么感觉楼上楼下的$dalao$们这题都做烦了呀……

---

## 正文开始

众所周知，这道题目直接枚举$n-2$个数然后再累加计算肯定是不行的（会$T$飞~~虽然我没试过haha~~），貌似会得到$50pts$的好成绩。

但是，如果让我们来枚举剩下的两个数就非常容易了（效率就能高一大截，并拿到$80pts$的好成绩）……

萌新：诶，打住打住，那怎么判断剩下数的和是不是$10$的倍数呢？！！

作者：**你先在输入的时候把和累加一下，然后再减去枚举的两个数不就行了嘛~**

其实（呵呵），**这题剩下的两个数根本就不用枚举！！！**~~吓死我了~~

我们把所有和都累加起来，得到一个值（比如说是$19260817$），那我如果要让这个数是$10$的倍数，我只要把这个末位的$7$给减掉不就行了 ~~被吓死*2~~

萌新~~是的我又来了~~：诶，那把这个$17$给减掉不也行耶？？？

是的，这回楼上回的没错。因为给定的数是$1$~$10$范围内的，所以自然也可以凑出两个数，让它们的和为$17$。

这么一来，我们不就做完了吗？？？~~被吓死*3~~

那我们只要：

①开一个数组，累计$0$~$9$出现的次数（为毛不是$1$~$10$？你想想呀在这个题目中$10$跟$0$有什么区别？~~10就是来打酱油的~~）

②计算所有数之和并$\%10$

③判断能否用两个数字组成所有数之和$\%10$或所有数之和$\%10+10$即可。

例如：$19260817\%10=7$，我们只要判断有没有两个数字可以组成$7$或$17$就行了。

最优一发$58ms$，貌似挺优了吧……

~~另外吐槽这题有黄题难度吗qaq~~

~~正解应该不算难想吧~~
```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[15];//定义累计数字数组
long long ans=0;//其实这里用int就够了，不过保险起见&内存充足时用long long还是万无一失吧
int main()
{
	cin>>n;
	int x;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);//输入每个数字
		if(x==10) a[0]++;//10跟0没区别呀~
		else a[x]++;
		ans+=x%10;//累加
	}
	int t=ans%10;
    //以下是略长的判断过程
	if(t==0) if(a[0]>=2||a[1]&&a[9]||a[2]&&a[8]||a[3]&&a[7]||a[4]&&a[6]||a[5]>=2) cout<<10<<endl; else cout<<0<<endl;
	if(t==1) if(a[0]&&a[1]||a[2]&&a[9]||a[3]&&a[8]||a[4]&&a[7]||a[5]&&a[6]) cout<<1<<endl; else cout<<0<<endl;
	if(t==2) if(a[0]&&a[2]||a[1]>=2||a[3]&&a[9]||a[4]&&a[8]||a[5]&&a[7]||a[6]>=2) cout<<2<<endl; else cout<<0<<endl;
	if(t==3) if(a[0]&&a[3]||a[1]&&a[2]||a[4]&&a[9]||a[5]&&a[8]||a[6]&&a[7]) cout<<3<<endl; else cout<<0<<endl;
	if(t==4) if(a[0]&&a[4]||a[1]&&a[3]||a[2]>=2||a[5]&&a[9]||a[6]&&a[8]||a[7]>=2) cout<<4<<endl; else cout<<0<<endl;
	if(t==5) if(a[0]&&a[5]||a[1]&&a[4]||a[2]&&a[3]||a[6]&&a[9]||a[7]&&a[8]) cout<<5<<endl; else cout<<0<<endl;
	if(t==6) if(a[0]&&a[6]||a[1]&&a[5]||a[2]&&a[4]||a[3]>=2||a[7]&&a[9]||a[8]>=2) cout<<6<<endl; else cout<<0<<endl;
	if(t==7) if(a[0]&&a[7]||a[1]&&a[6]||a[2]&&a[5]||a[3]&&a[4]||a[8]&&a[9]) cout<<7<<endl; else cout<<0<<endl;
	if(t==8) if(a[0]&&a[8]||a[1]&&a[7]||a[2]&&a[6]||a[3]&&a[5]||a[4]>=2||a[9]>=2) cout<<8<<endl; else cout<<0<<endl;
	if(t==9) if(a[0]&&a[9]||a[1]&&a[8]||a[2]&&a[7]||a[3]&&a[6]||a[4]&&a[5]) cout<<9<<endl; else cout<<0<<endl;
    //如上，依次判断能不能有两个数字组成ans%10或ans%10+10即可
	return 0;//完 结 撒 花
}
```

---

## 作者：StudyingFather (赞：18)

首先有一个比较显然的结论：选牌的方式和最终点数无关。

如果所有牌的点数和的个位数为 $x$，那么无论我们怎么取那 $n-2$ 张牌，因为那 $n-2$ 张牌的点数和总是 $10$ 的倍数，这一局的点数和也一定是 $x$。

当然，上面这一切成立的前提是存在一种取 $2$ 张牌的方式使得这两张牌的点数和的个位数为 $x$。

完成这个判断，我们只需记录一下每种牌的出现次数即可。

```cpp
#include <iostream>
using namespace std;
int t[15];
int main()
{
 int n,ans=0;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
  int x;
  cin>>x;
  t[x%10]++;
  ans=(ans+x)%10;
 }
 for(int i=0;i<=9;i++)//枚举两种不同的牌
  for(int j=i+1;j<=9;j++)
   if(t[i]&&t[j]&&(i+j)%10==ans)
   {
    cout<<(!ans?10:ans)<<endl;
    return 0;
   }
 for(int i=0;i<=9;i++)//枚举两种相同的牌
  if(t[i]>=2&&(i+i)%10==ans)
  {
   cout<<(!ans?10:ans)<<endl;
   return 0;
  }
 cout<<0<<endl;
 return 0;
}
```


---

## 作者：kevin_y (赞：7)

别被数据吓到，这题要变难可以吧两张牌改为多张牌。

步入正题，首先把所有牌的点数加起来。如果有牛，个位数就为牛几。需要注意的是个位为0 是牛10。这里应该很好理解。

要做一个预处理，保存个位数字出现的情况。

直接上代码，批注应该挺详细。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,a[1000001],sum=0,d[11];//d保存个位数字出现的情况。
inline int read(){//快读
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();sum+=a[i];
		d[a[i]]++;//为啥不是d[a[i]]=1;因为不知这类牌是否出现两次
	}
	sum=sum%10;if(sum==0)sum=10;//0为牛10
	for(int i=1;i<=10;i++)
	for(int j=1;j<=10;j++)if(d[i]&&d[j])//首先要求这两数出现过
    if(((i==j)&&d[i]>1)||(i!=j))//若两数相同 则需要出现两次
    if((sum==(i+j))||((sum+10)==(i+j))){//加起来个位数相同，代表可以有牛（输出不为0）只要两数之和的个位数字等于sum则其他数一定可以为十的倍数，不懂的可以自己举例子。
    //这句话可以化简为if(sum==(i+j)%10)
		cout<<sum<<endl;return 0;//输出
	}
	cout<<0<<endl;
	return 0;
}
```
完结，散花qwq

---

## 作者：fls233666 (赞：4)

首先我们可以发现，这道题的牌的数量 $n$ 的范围是很大的： $5 \le n \le 10^6$。显然，暴力 $O(n^2)$ 枚举要删的两张牌会TLE。

但是我们可以发现一个很重要的事情：**牌的点数范围很小，仅为 $0 \thicksim 10$**。

看到这样子的情况，一般会想到**桶排序**。那么，我们就先把这 $n$ 张牌进行桶排序， $0 \thicksim 10$ 的牌各自对应一个桶。

再回来关注取牌的情况，我们发现**只要取两张牌**。又考虑到之前已经对读入的 $n$ 张牌进行了桶排序，我们就想去**枚举要删掉的两张牌的点数**。显然，因为牌的范围仅为 $0 \thicksim 10$ ，所以这个做法是 $O(121)$ 的常数复杂度解【 _$0 \thicksim 10$ 有 $11$ 张牌， $11 \times 11 = 121$ ，所以复杂度为 $O(121)$_ 】，是一定可以过这一题的。

那么，我们用两重循环分别枚举要取的这两张牌的点数。然后在牌的总点数中扣除这两张牌的点数，检查一下是否构成 $10$ 的倍数。如果构成，进一步判断存储牌的桶中是否有这两张牌。如果有，就输出答案。如果枚举过所有点数还是找不到答案，就输出 $0$。

最终实现的AC代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring> 
#define rgt register int
#define ll long long
using namespace std;

inline int rd(){
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	int x=(c^48);
	c=getchar();
	while(c<='9'&&c>='0'){
		x=x*10+(c^48);
		c=getchar();
	}
	return x;
} //快速读入

inline void print(int x){
	if(!x){
		putchar('0');
		return;
	}
	int num[22],siz=0,px=x;
	while(px){
		siz++;
		num[siz]=px%10;
		px/=10;
	}
	while(siz){
		putchar(num[siz]+'0');
		siz--;
	}
}   //快速输出

int pks[11],n,s,p;
//pks[]为存储各种牌的桶
//s为读入的牌的总点数
//p为要删的牌的总点数

int main()
{
  
	bool fdans=false;  //标记是否找到答案
	n=rd();
	for(rgt i=1,x;i<=n;i++){
		x=rd();  //读入一张牌的点数
		pks[x]++;  //放到对应的桶中
		s+=x;   //记入总点数
	}
                            
	for(rgt i=0;i<=10;i++){
		for(rgt j=0;j<=10;j++){
			p=i+j;  //计算枚举出的两张牌的总点数
			if((s-p)%10==0){  //如果构成10的倍数
				if(i==j){  //如果这两张牌点数相同
					fdans=pks[i]>=2?true:false;  //判断桶中是否有两张或以上的牌
				}else{
					fdans=pks[i]&&pks[j]?true:false;  //否则判断这两个桶是否都不为空
				}
				if(fdans){  //找到答案
					print(!(p%10)?10:p%10);
					return 0;  //输出
				}
			}
		}
	}
	print(0);  //没有答案，输出0
	return 0;
}
```


---

## 作者：时律 (赞：3)

**主要思路：** 

因为这 $n$ 张牌最后得出的点数是确定的，那么可以枚举是否有两张牌加在一起模 $10$ 后等于最后的点数。若没有，则可知点数为 $0$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[15],y[15];//x[i]表示牌上的点数 %10 后为 i 的张数，y[i]=1 表示有两张牌加在一起 %10 后为 i
int main()
{
	long long u=0;//为所有牌加在一起的总点数
	int a,b;
	scanf("%d",&a);
	for(int i=1;i<=a;i++)
	{
		scanf("%d",&b);
		if(b%10==0)
			x[10]++;
		else
			x[b%10]++;
		u+=b;
	}
	for(int i=1;i<=10;i++)//枚举判断（事实上没必要所有都扫一遍）
		for(int j=i;j<=10;j++)
			if((i!=j and x[i]>0 and x[j]>0) or (i==j and x[i]>=2))
				y[(i+j)%10]=1; 
	if(y[u%10]==0)//如果没有出现点数为 0
		cout<<0;
	else//否则输出点数
		if(u%10==0)
			cout<<10;
		else
			cout<<u%10;
}
```

---

## 作者：judgejudge (赞：2)

# 数学题
先看80分代码：
```cpp
#include <iostream>
#include <cstdio>
#define N 5001
using namespace std;
typedef long long ll;
ll a[N];
ll sum,n;
int main(){
	register int i,j;
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum+=a[i];sum%=10;
	}
	for(i=1;i<n;i++)
	for(j=i+1;j<=n;j++){//两重循环，自然不够快
		ll k=(a[i]+a[j])%10;
		if((sum+10-k)%10==0){
			if(k!=0)cout<<k<<endl;
			else cout<<10<<endl;
			return 0;
		}
	}
	cout<<0<<endl;
	return 0;
}
```
一看范围，直接死亡。

那么如何AC呢？

这道题只牵扯到个位数，所以我们可以全部%10先，这样好判断。

然后开始**数学证明**。

既然找到两个数的和，使得剩余数的总和是10的倍数，那么我们可以得到：

**数的总和%10=点数（0除外，点数是10）**

并且：**(数1+数2)%10=点数**

那么我们可以对所有数走一遍循环，如果出现过 **(数的总和+10-数n)%10的数**，
就找到了；

若两数和为10的倍数，证明总和也是10的倍数，所以：
```cpp
                if(tot[(sum+10-a[i])%10]){//关键代码：
			if(sum==0)cout<<10<<endl;
			else cout<<sum%10<<endl;
			return 0;
		}
```
接下来还有一个问题，对于数据：
```cpp
5
6 7 8 9 10
```
判断到10时，光靠以上代码是行不通的，因为此处10使用重复了。

所以再加一句：
```cpp
for(i=1;i<=n;i++){
		tot[opt[i]]--;//判断到自己时，先消去
		if(tot[(sum+10-a[i])%10]){
			if(sum==0)cout<<10<<endl;
			else cout<<sum%10<<endl;
			return 0;
		}
		tot[opt[i]]++; //再补回来
	}
```

这样整体只走一遍循环，速度自然过得去。

AC代码：
```cpp
#include <iostream>
#include <cstdio>
#define N 5000001//注意范围
using namespace std;
typedef long long ll;
ll tot[10];
ll a[N],opt[N];
ll sum,n;
int main(){
	register int i,j;
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum+=a[i];sum%=10;//不需要总和都求出来，只需要%10的余数即可
		tot[a[i]%10]++;//记录是否出现过该数
		opt[i]=a[i]%10;//为下文判断自己做预备
	}
	for(i=1;i<=n;i++){
		tot[opt[i]]--;//消记号
		if(tot[(sum+10-a[i])%10]){//如果符合条件
			if(sum==0)cout<<10<<endl;
			else cout<<sum%10<<endl;//两种情况
			return 0;
		}
		tot[opt[i]]++; //补记号
	}
	cout<<0<<endl;//查找不到
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/xjc95lxx.png)


---

## 作者：时间重洗 (赞：2)

忘了参加月赛，遗憾。

这道题，第一眼看题目是真的不知道怎么做，但是好好想一想后，就可以轻松地做出来了。

题目中说n-2张牌的和为10的倍数，下定决心，暴力枚举选择哪两张牌，判断综合减去这两张牌是否为是的倍数，但看了数据范围，果断放弃。

接着这个思路继续想下去，我们可以轻松地求出序列的总和，而去除两张后则为十的倍数。

那么我们假设总和为   s=10*a+k （~~我太蒟了不会Markdown~~）

如果去除两张牌后和s是十的倍数，则这两张牌的和为k或者10+k，则获得的点数就是k。剩下的问题就是判断这个序列中有没有两张牌的和是k或者10+k了

这就不用讲了吧，记录下每个点数有没有出现过，再枚举点数即可

代码

```cpp
#include<cmath>
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

bool vis[20];
int n,k;

inline void work(int s){
	bool flag=1;
	for(register int i=1;i<=10&&flag;++i){
		int j=(s-i+10)%10;
		if(vis[i]&&vis[j]) flag=0;
	}
	if(flag==0) printf("%d\n",s==0?10:s);
	else printf("0\n");
}//判断能否组成k或10+k

template <typename T> void in(register T& a){
    register T x=0,f=1;
	register char c=getchar();
    while(!isdigit(c)){
	    c=='-'?f=-1:f=1;
		c=getchar();
	}
    while(isdigit(c)){
        x=(x<<1)+(x<<3)+c-'0';
	    c = getchar();
	}
    a=x*f;
}
inline void init(){
	in(n);
	for(register int i=1;i<=n;++i){
		int x;
		in(x);
		vis[x]=1;k=(k+x)%10;
	}
	work(k);
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	init();
	return 0;
}

```

~~于是快乐的20分，别问我怎么知道的~~

为什么呢，因为本人的程序在找到第一种情况后就退出了，而会有这样的情况:

5

3 7 2 4 2

根据本蒟蒻的程序，s=18 ; k=8。在work函数运行到i=4时，i=j=4，且vis数组为1，则会输出8而不是0

所以改良后

```cpp
#include<cmath>
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int n,k,vis[20];

inline void work(int s){
	bool flag=1;
	for(register int i=1;i<=10&&flag;++i){
		int j=(s-i+10)%10;
		if(vis[i]&&vis[j]&&(i==j?vis[i]>=2:1)) flag=0;
        //如果i=j，那么判断是否出现了两次
	}
	if(flag==0) printf("%d\n",s==0?10:s);
	else printf("0\n");
}

template <typename T> void in(register T& a){
    register T x=0,f=1;
	register char c=getchar();
    while(!isdigit(c)){
	    c=='-'?f=-1:f=1;
		c=getchar();
	}
    while(isdigit(c)){
        x=(x<<1)+(x<<3)+c-'0';
	    c = getchar();
	}
    a=x*f;
}
inline void init(){
	in(n);
	for(register int i=1;i<=n;++i){
		int x;
		in(x);
		++vis[x];k=(k+x)%10;
	}
	work(k);
}

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	init();
	return o;
}

```

---

## 作者：gyh20 (赞：2)

要凑出$10$的倍数很难，但凑剩下的数很容易，只要保证总和$-$剩下的数为$10$的倍数即可。

所以剩下的两个数和为$sum%10$或$sum%10+10$，分别尝试即可。

记录1~10每个数出现次数会更方便。

```cpp
#include<cstdio>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
} 
int n,a[22],sum,opt,ans,x,y;
inline bool tr(re int x){
	for(re int i=1;i<=(x-1)/2;++i){
		if(a[i]&&a[x-i])return 1;
	}
	if(!(x&1)&&a[x/2]>=2)return 1;
	return 0;
}
signed main(){
n=read();
for(re int i=1;i<=n;++i){
	x=read();
	++a[x];
	sum+=x;
}
if(tr(sum%10)||tr(sum%10+10))printf("%d",sum%10?sum%10:10);
else puts("0");
    return 0;
}
```


---

## 作者：老咸鱼了 (赞：1)

不知道斗牛的人应该很少吧。

题目给了n个数，所有的数的和对10取模后的结果就是分数。因为除了最后两个数的和以外其他的数的和是10，最后两个数的和也是对10取模，这个相信大家都想得通。那么剩下第二个问题，去除两个数剩下的数能凑成的数是10的倍数，如果从n个数里面任意选两个减去这两个的话看看是不是10的倍数枚举所有数，这样的时间复杂度是O(n^2)很显然不可取。但是题目告诉我们了所有的数是1到10所以我们用一个数组记录1到10出现的次数，然后从1到10枚举有没有能2个数凑成结果，如果有的话就说明这个点数成立。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,t;
int vis[21]={0};
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&t);
		vis[t]++;
		s+=t;
	}
	s%=10;
	for(int i=1;i<=10;i++){
		for(int j=i;j<=10;j++){
			if((i+j)%10==s&&((vis[i]&&vis[j]&&i!=j)||(i==j&&vis[i]>=2))){
				if(s)
				cout<<s<<endl;
				else//注意这里如果是0的话要输出10分
				cout<<10<<endl;
				return 0;
			}
		}
	}
	cout<<0<<endl;
	return 0;
}
```


---

## 作者：DreamFox (赞：0)

本题思路：

因为本题中获得的分数不是$0$就是他们的总和模$10$（$0$除外，算$10$），所以我们就可以利用这个性质，把$0$到$9$一个个判断过去。如果符合条件，那么就输出他们的总和模$10$（$0$除外，算$10$），否则输出$0$

因为牌的大小为$1$到$10$，且只要找两张牌，所以只要从$2$到$10$和$11$到$20$即可

$AC$ $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000001],ans,minx,x[11];
int n;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i],ans+=a[i],++x[a[i]];
	bool y=0;
	switch(ans%10)
	{
		case 0:
			if((x[1]&&x[9])||(x[2]&&x[8])||(x[3]&&x[7])||(x[4]&&x[6])||(x[5]>=2)||(x[10]>=2))  //10=1+9=2+8=3+7=4+6=5+5,20=10+10
			minx=10,y=1;
			break;
		case 1:
			if((x[1]&&x[10])||(x[2]&&x[9])||(x[3]&&x[8])||(x[4]&&x[7])||(x[5]&&x[6]))  //11=5+6=4+7=3+8=2+9=1+10
			minx=1,y=1;
			break;
		case 2:
			if((x[2]&&x[10])||(x[3]&&x[9])||(x[4]&&x[8])||(x[5]&&x[7])||(x[6]>=2)||(x[1]>=2))  //12=6+6=5+7=4+8=3+9=2+10,2=1+1
			minx=2,y=1;
			break;
		case 3:
			if((x[3]&&x[10])||(x[4]&&x[9])||(x[5]&&x[8])||(x[6]&&x[7])||(x[1]&&x[2]))  //13=3+10=4+9=5+8=6+7,3=1+2
			minx=3,y=1;
			break;
		case 4:
			if((x[4]&&x[10])||(x[5]&&x[9])||(x[6]&&x[8])||(x[7]>=2)||(x[1]&&x[3])||(x[2]>=2))  //14=10+4=9+5=8+6=7+7,4=1+3=2+2
			minx=4,y=1;
			break;
		case 5:
			if((x[5]&&x[10])||(x[6]&&x[9])||(x[7]&&x[8])||(x[1]&&x[4])||(x[2]&&x[3]))  //15=7+8=6+9=5+10,5=1+4=2+3
			minx=5,y=1;
			break;
		case 6:
			if((x[6]&&x[10])||(x[7]&&x[9])||(x[8]>=2)||(x[1]&&x[5])||(x[2]&&x[4])||(x[3]>=2))  //16=8+8=7+9=6+10,6=1+5=2+4=3+3
			minx=6,y=1;
			break;
		case 7:
			if((x[7]&&x[10])||(x[8]&&x[9])||(x[1]&&x[6])||(x[2]&&x[5])||(x[3]&&x[4]))  //17=8+9=7+10,7=1+6=2+5=3+4
			minx=7,y=1;
			break;
		case 8:
			if((x[8]&&x[10])||(x[9]>=2)||(x[1]&&x[7])||(x[2]&&x[6])||(x[3]&&x[5])||(x[4]>=2))  //18=9+9=8+10,8=1+7=2+6=3+5=4+4
			minx=8,y=1;
			break;
		case 9:
			if((x[9]&&x[10])||(x[1]&&x[8])||(x[2]&&x[7])||(x[3]&&x[6])||(x[4]&&x[5]))  //19=9+10,9=4+5=3+6=2+7=1+8
			minx=9,y=1;
			break;
	}
	if(y!=0)
	cout<<minx<<endl;
	else
	cout<<"0\n";
	return 0;
}
```


---

## 作者：james1BadCreeper (赞：0)

对于 $Subtask1$ ，直接枚举每张牌取或不取即可。

对于 $Subtask2$ ，由于必定有 $2$ 张牌是不取的，枚举这两张牌即可。
```cpp
int n;
int a[1000005],sum=0,ans=0;

int main(void)
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)//枚举技巧，不会漏掉也不会重复
			{
				int k=sum-a[i]-a[j];
				if(k%10==0)
					ans=max(ans,(a[i]+a[j])%10==0?10:(a[i]+a[j])%10);//取最大值，按时间复杂度来讲不会超时，但实际可以证明直接输出ans即可，细节留给大家思考
			}
	printf("%d",ans);
	return 0;
}
```

对于 $Subtask3$ ，可以发现每张牌必定是$[1,10]$，所以利用类似计数排序的思想，枚举可能取的$[1,10]$的牌即可。

code：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>

namespace The_Future_Diary
{
	using namespace std;
	int __int;
	long long __LL;

	template<typename T>
	inline T read(T p)
	{
		register T x=0;
		register int c=getchar()/*,f=0*/;
		while(!isdigit(c)) c=getchar();/*{if(c=='-')f=1;c=getchar();}*/
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		//return f?-x:x;
		return x;
	}

	int buf[30];
	template<typename T>
	inline void print(T x,char k)
	{
		//if(x<0) putchar('-'),x=-x;
		register int tot=0;
		if(x==0) buf[++tot]=0;
		while(x)
		{
			buf[++tot]=x%10;
			x/=10;
		}
		for(register int i=tot;i>=1;i--)
			putchar(buf[i]+'0');
		putchar(k);
    }
}

using namespace The_Future_Diary;

int n;
int a,sum=0,ans=0,s[10];

int main(void)
{
	n=read(__int);
	for(register int i=1;i<=n;i++)
	{
		a=read(__int);
		sum+=a;
		s[a]++;
	}
	for(register int i=1;i<=10;i++)
		for(register int j=1;j<=10;j++)
		{
			if(s[i]==0||s[j]==0) continue;
			if(i!=j&&s[i]>=1&&s[j]>=1)
			{
				if((sum-(i+j))%10==0)
					ans=max(ans,(i+j)%10==0?10:((i+j)%10));
				continue;
			}
			if(i==j&&s[i]>=2)
			{
				if((sum-(i+j))%10==0)
					ans=max(ans,(i+j)%10==0?10:((i+j)%10));
				continue;
			}
		}
	print(ans,'\n');
	return 0;
}
```

---

## 作者：Y_B_Y (赞：0)

先看题面:你需要挑选其中的 $n-2$ 张牌加起来是 $10$ 的倍数，另外两张牌和的个位数即为你所获得的点数,特别地，如果这两张牌的和是 $10$的倍数，则点数为 $10$。

我们可以发现与其挑$n-2$张牌并满足加起来是$10$的被数,不如挑$2$张牌,使剩下的$n-2$张牌是$10$的倍数,因为牌的点数为$1∼10$,所以直接枚举两张牌点数,然后判断牌够不够且剩下的牌点数和是否为$10$的倍数,而剩下牌的点数和其实就是总点数减去那两张的点数.

为了判断一种点数的牌够不够,我们可以定义$hv[i]$表示点数为$i$的牌的数量.

### 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int sum,n,hv[21],ans;//ans为获得的点数的最大值,sum为总点数
int gt(int x)//求两张牌和的个位数且当如果这两张牌的和是 10的倍数时，返回10
{
	if(x%10==0) return 10;//如果为10的倍数返回10
	else return x%10;//返回个位
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		sum+=a;
		hv[a]++;//表示点数为$i$的牌的数量+1
	}
	for(int i=1;i<=10;i++)
	{
		for(int j=1;j<=10;j++)//枚举两张牌点数
		{
			if(i==j)点数相同特判
			{
				if(hv[i]>=2)//这一点数的牌数要大于2才够
				{
					if((sum-i-j)%10==0)//如果剩下的牌的点数和是10的倍数
					{
						ans=max(ans,gt(i+j));//求较大值
					}
				}
			}
			else
			{
				if(hv[i]&&hv[j])//两种点数都要有牌
				{
					if((sum-i-j)%10==0)//同上
					{
						ans=max(ans,gt(i+j));//同上
					}
				}
			}
		}
	}
	cout<<ans;//输出
	return 0;
}
```


---

## 作者：　　　吾皇 (赞：0)

### 题目分析
- 如果直接枚举 $n-2$ 张牌，略显繁琐，我们可以考虑枚举 $2$ 张牌，看去掉后剩下的是否为 $10$ 的倍数即可。
- 操作上可以先算出总和模 $10$ 的余数，再 $O(n)$ 进行枚举，看当前序列是否存在可以配对的。即对于 $i,j\in\{1,n\}$ 且 $i \ne j$ ，是否存在 $(i+j) \equiv sum (mod 10)$。如果存在，输出；不存在，输出0。
#### 实现思路

- 可以用桶来存下 $a[i]$ 模 $10$ 的余数，优化枚举。
- 注意 $i \ne j$，所以在 $a[i]=\text{另一方}$ 时，要注意 $t[i]>1$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   register int s=0,w=1;
   register char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n,a[1000001],sum,t[11];
int main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),a[i]%=10,sum+=a[i],t[a[i]]++;//将a[i]模10的余数存入桶
	sum%=10;//当前值即为要枚举两个数的总和
	for(int i=1;i<=n;i++)
    if(t[(sum+10-a[i])%10]){//如果另外一方有数（注意因为%10，sum可能小于a[i]，所以要先加10）
		if(a[i]==(sum+10-a[i])%10&&t[i]==1) continue; //如果另一方等于自己且等于自己的只有一个，那么无法配对
		if(sum==0) printf("10");//如果可以且总和能被10整除，说明删除的两个数也能被10整除
		else printf("%d",sum);//否则直接输出sum
		return 0;//停止程序
	}
	printf("0");//如果循环一圈没有能配对的，代表不行，输出0
}
```


---

## 作者：Kevin_Wa (赞：0)


## T2 斗牛

### 题目解析：

这不是牛哄哄吗？？？

题目说的很清楚。。。

首先我们要明确，假设没有牛不拢，输出的答案一定是所有数加起来的和模一个$10$。如果牛不拢，输出$0$。所以我们就只要判断是否牛不拢。

如果要按照题目的正面思维去思考$n-2$个数字，复杂度就会达到$O(n^2)$。所以打一个反面逻辑，其实只要思考有没有两个数的和与所有数的和模$10$是同余的。

用一个计数排序，在判断每种数字对的出现情况，即可判断是否牛不拢。

具体见代码：

### $Code$

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
int n,x,sum,f[10];
template <typename T> void read(T &x) {
x = 0; char c = getchar();int f=1;
for (; !isdigit(c); c = getchar())if (c=='-') f=-1;
for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
x*=f;
}
int main()
{
	read(n);
	for (int i=1;i<=n;i++)
	  {
	  	read(x);
	  	if (x==10) f[0]++;
	  	else f[x]++;
	  	sum+=x;
	  }
	sum=sum%10;
	int flag=0;
	for (int i=0;i<=9;i++)
	  for (int j=0;j<=9;j++)
	    if ((i+j)%10==sum)
	    {
	    	if (i!=j)
	    	  {
	    	  	if (f[i]>0 && f[j]>0)
	    	  	  flag=1;
			  }
			if (i==j)
			  {
			  	if (f[i]>1) flag=1;
			  }
		}
	if (flag) 
	  {
	  if (sum==0) sum=10;	
	  printf("%d\n",sum);
	  }
	else printf("0\n");
	return 0;
 } 
```


---

## 作者：SUNCHAOYI (赞：0)

**每张牌的大小为1-10，所以我们设数组b[i]表示余数为i的数的个数，s为余数的和。然后我们只要判断s来输出即可：将s%10后将有10种情况，对应0-9。**

**然后题目要求n-2张牌要是10的倍数，两张牌的和的 _个位数_ 则为你最后获得的点数，所以我们只要判断s可以由哪两个数相加得到即可。若这两个数存在，那么s就是点数（0对应10）**

**0-9分析:每个数都有两种情况，两数相加不进位得到与两数相加进位得到（原因：点数为两数相加的个位数，故会出现两种情况），例如：0:0 + 0,1 + 9,2 + 8,3 + 7,4 + 6,5 + 5。中共6种情况**

**无解分析：若0-9的情况都无法实现，便是无解（对应0）。**

**最后得到的代码：**
```
#include <iostream>
using namespace std;
const int MAX = 1000005;
int a[MAX],b[10] = {0};
int main()
{
	int n,s = 0;
	bool ok = 0;
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>a[i];
		b[a[i] % 10]++;//除以10的余数的一种情况+1 
		s += a[i] % 10;//余数累加 
		s %= 10;//不断取余 
	}
	switch(s)//逐一判断检测是否满足条件 
	{
		case 0:
		{
			if((b[0] > 1) || (b[1] > 0 && b[9] > 0) || (b[2] > 0 && b[8] > 0) || (b[3] > 0 && b[7] > 0) || (b[4] > 0 && b[6] > 0) || b[5] > 1) cout<<10<<endl,ok = 1;
			break;
		}
		case 1:
		{
			if((b[0] > 0 && b[1] > 0) || (b[5] > 0 && b[6] > 0)) cout<<1<<endl,ok = 1; 
			break;
		}
		case 2:
		{
			if((b[0] > 0 && b[2] > 0) || (b[1] > 1) || (b[3] > 0 && b[9] > 0) || (b[4] > 0 && b[8] > 0) || (b[5] > 0 && b[7] > 0) || b[6] > 1) cout<<2<<endl,ok = 1;
			break;
		}
		case 3:
		{
			if((b[0] > 0 && b[3] > 0) || (b[1] > 0 && b[2] > 0) || (b[4] > 0 && b[9] > 0) || (b[5] > 0 && b[8] > 0) || (b[6] > 0 && b[7] > 0)) cout<<3<<endl,ok = 1;
			break;
		}
		case 4:
		{
			if((b[0] > 0 && b[4] > 0) || (b[1] > 0 && b[3] > 0) || b[2] > 1 || (b[5] > 0 && b[9] > 0) || (b[6] > 0 && b[8] > 0) || b[7] > 1) cout<<4<<endl,ok = 1;
			break;
		}
		case 5:
		{
			if((b[0] > 0 && b[5] > 0) || (b[1] > 0 && b[4] > 0) || (b[2] > 0 && b[3] > 0) || (b[6] > 0 && b[9] > 0) || (b[7] > 0 && b[8] > 0)) cout<<5<<endl,ok = 1;
			break;
		}
		case 6:
		{
			if((b[0] > 0 && b[6] > 0) || (b[1] > 0 && b[5] > 0) || (b[2] > 0 && b[4] > 0) || b[3] > 1 || (b[7] > 0 && b[9] > 0) || b[8] > 1) cout<<6<<endl,ok = 1;
			break;
		}
		case 7:
		{
			if((b[0] > 0 && b[7] > 0) || (b[1] > 0 && b[6] > 0) || (b[2] > 0 && b[5] > 0) || (b[3] > 0 && b[4] > 0) || (b[8] > 0 && b[9] > 0)) cout<<7<<endl,ok = 1;
			break;
		}
		case 8:
		{
			if((b[0] > 0 && b[8] > 0) || (b[1] > 0 && b[7] > 0) || (b[2] > 0 && b[6] > 0) || (b[3] > 0 && b[5] > 0) || b[4] > 1 || b[9] > 1) cout<<8<<endl,ok = 1;
			break;
		}
		case 9:
		{
			if((b[0] > 0 && b[9] > 0) || (b[1] > 0 && b[8] > 0) || (b[2] > 0 && b[7] > 0) || (b[3] > 0 && b[6] > 0) || (b[4] > 0 && b[5] > 0)) cout<<9<<endl,ok = 1;
			break;
		}
	}
	if(!ok) cout<<0<<endl;//无解情况 
	return 0;
}
```


---

## 作者：Hexarhy (赞：0)

好坑的水题……~~顺便吐槽评测机影响比赛心情~~

-------

题面已经够清晰了~~虽然依然有坑~~，下面直接给出思路：

**请看完算法二再看算法三，因为算法三是算法二基础上的优化。**

### 解题思路

#### 算法一

考虑当 $n=5$，直接根据一般斗牛的游戏规则打几个`if`即可。

时间复杂度 $O(1)$，预计得分 $50\%$。

#### 算法二

按照题意暴力模拟，但**有技巧**的。

显然如果枚举那 $n-2$ 个数，操作难度极高，时间开销极大，数量还会变。

不如看剩下的 $2$ 个数，枚举数量不变，时间开销勉强能承受。故考虑枚举这 $2$ 个数，用总和减去再判断是否是 $10$ 的倍数即可。

那么只需开两个`for`枚举 $2$ 个数，再判断即可。

时间复杂度 $O(n^2)$，预计得分 $80\%$。

#### 算法三

当你打算用算法二尝试骗分时，你就应该能想到，能不能省去一个`for`呢？

当选定 $1$ 个数 $p$ 时，剩下 $n-1$ 个数的总和**不变**。

要再选出 $1$ 个数，使得总和减去这个数后，和的个位为 $0$。

设这个数为 $x$，那么 $x$ 也是**不变**的，因为总和不变。

设这个数列为 $a$。则：

$$x=[(\sum^n_{i=1}a_i)-p]\% 10$$

那就好办了！考虑二分查找，就省去了一个`for`。二分到 $x$ 存在，更新答案；否则，继续枚举 $p$。

注意，

至此，本题思路就结束了。

时间复杂度 $O(n\log n)$，预计得分 $100\%$，实际亦如此。

----------

### 实现细节

本题坑点多，这里才是重点。

1. 还记得那个关于 $x$ 的式子吗？受取模影响，$x$ 可能为 $0$，即包含 $x$ 的 $n-1$ 个数总和已经是 $10$ 的倍数了。那么**要查找的 $x$ 应该为 $10$ 而非 $0$**，这样总和个位数才依然为 $0$。

1. 可能出现**多个合法方案**，因此更新答案要**取最大值**，不能直接`return`。为什么呢？难道玩游戏时不是越大越好吗？

1. 二分到存在 $x$ 时，请判断$x$ 和 $p$ **是否为同一个数**。

1. 二分前别忘了排序数组 $a$。

1. 二分推荐使用STL里的`std::lower_bound()`，搭配`std::vector`使用更方便。一些使用细节代码里有。

1. 求数列区间总和可以使用`std::accumulate()`。详细用法见[这篇文章末尾](https://www.luogu.com.cn/blog/hyyyprtf06/solution-p2866)。

----------

### 参考代码

下面多处使用STL。建议O2优化。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
int n,sum,ans;
int output(const int& a,const int& b)//算两张牌的点数
{
	return ((a+b)%10==0?10:(a+b)%10);
}
int main()
{
	scanf("%d",&n);
	vector <int> a(n+5);//动态开数组，vector默认为0
	for(int i=1;i<=n;i++)//本文数组下标从1开始
	 scanf("%d",&a[i]);
	sort(a.begin()+1,a.begin()+1+n);//注意排序范围，不是begin()和end()
	sum=accumulate(a.begin(),a.end(),0);//求和。由于默认为0，故范围可以为begin()和end()
	for(vector<int>::iterator it=a.begin()+1;it!=a.begin()+1+n;it++)//注意范围
	{
		int x=(sum-*it)%10;
		if(!x)
		 x=10;//实现细节1
		const auto f=lower_bound(a.begin()+1,a.begin()+1+n,x);//二分
		if(f!=it && *f==x)//不是同一个数且符合数值，见实现细节3
		  ans=max(ans,output(*it,x));//实现细节2
	}
	cout<<ans<<endl;//ans本来为0，找不到合法方案不更新，依然为0
	return 0;
}
```

---

## 作者：唐一文 (赞：0)

蒟蒻~~在咕值的压迫下~~来发题解惹!
## 一、读题
给定$n$个为$1 \sim 10$之间的数。你需要挑选其中的$n-2$个数，使得它们的和是$10$的倍数，另外$2$个数的和的 **个位数** 即为你所获得的点数。特别地， **如果它们的和是$10$的倍数，则点数为 $10$。如果任意$n-2$个数不能构成$10$的倍数，则点数为$0$** 。
## 二、思路
- 很明显，要用到同余。
- 因为$n-2$个数太难找，所以可以换成选出$2$个数，剩下的数的和为$10$的倍数。
- 那么选出来的$2$个数的和必定与这$n$个数的和模$10$同余。
- 在有解的情况下，因为答案是个位数，所以答案为这$n$个数的和的个位数。如果这$n$个数的和为$10$的倍数，那么答案为$10$。
- 因此只要判断能否选出两个数，使它们的和与这$n$模$10$同余。
## 三、代码
代码应该都能看懂，我就不加注释了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,i,y,a[1000001],mod[11];
bool f;
main(){
    cin>>n;
	for(i=1;i<=n;++i){
		cin>>a[i];
		sum+=a[i];
		mod[a[i]%10]++;
	}
	y=sum%10;
	if(!y){
		y=10;
	}
	if(y==1){
		if((mod[0] && mod[1]) || (mod[2] && mod[9]) || (mod[3] && mod[8]) || (mod[4] && mod[7]) || (mod[5] && mod[6])){
			f=true;
		}
	}
	else if(y==2){
		if((mod[0] && mod[2]) || mod[1]==2 || (mod[3] && mod[9]) || (mod[4] && mod[8]) || (mod[5] && mod[7]) || mod[6]==2){
			f=true;
		}
	}
	else if(y==3){
		if((mod[0] && mod[3]) || (mod[1] && mod[2]) || (mod[4] && mod[9]) || (mod[5] && mod[8]) || (mod[6] && mod[7])){
			f=true;
		}
	}
	else if(y==4){
		if((mod[0] && mod[4]) || (mod[1] && mod[3]) || mod[2]==2 || (mod[5] && mod[9]) || (mod[6] && mod[8]) || mod[7]==2){
			f=true;
		}
	}
	else if(y==5){
		if((mod[0] && mod[5]) || (mod[1] && mod[4]) || (mod[2] && mod[3]) || (mod[6] && mod[9]) || (mod[7] && mod[8])){
			f=true;
		}
	}
	else if(y==6){
		if((mod[0] && mod[6]) || (mod[1] && mod[5]) || (mod[2] && mod[4]) || mod[3]==2 || (mod[7] && mod[9]) || mod[8]==2){
			f=true;
		}
	}
	else if(y==7){
		if((mod[0] && mod[7]) || (mod[1] && mod[6]) || (mod[2] && mod[5]) || (mod[3] && mod[4]) || (mod[8] && mod[9])){
			f=true;
		}
	}
	else if(y==8){
		if((mod[0] && mod[8]) || (mod[1] && mod[7]) || (mod[2] && mod[6]) || (mod[3] && mod[5]) || mod[4]==2 || mod[9]==2){
			f=true;
		}
	}
	else if(y==9){
		if((mod[0] && mod[9]) || (mod[1] && mod[8]) || (mod[2] && mod[7]) || (mod[3] && mod[6]) || (mod[4] && mod[5])){
			f=true;
		}
	}
	else{
		if(mod[0]==2 || (mod[1] && mod[9]) || (mod[2] && mod[8]) || (mod[3] && mod[7]) || (mod[4] && mod[6]) || mod[5]==2){
			f=true;
		}
	}
	if(f){
		cout<<y;
	}
	else{
		cout<<0;
	}
	return 0;
}
```

---

## 作者：peterwuyihong (赞：0)

# 这是一道模拟题
还有点坑

其实只要记录$0-10$的数出现了几个就行了，枚举$(0,0),(0,1),(0,2)\cdots(10,10)$就行了，用$Sum$表示总数，减去枚举的数对，看是否等于$0$即可

## 坑点：
当两个数相同时，必须要求这个数存在$2$个及以上

于是我之前的代码，万绿丛中一点红，但是只有$20pts$
```cpp
#include<bits/stdc++.h>
#define maxn 1000010
using namespace std;
template<class T>
inline void read(T&__x)
{T __ans=0;char __ch=getchar();short __f=1;
while(__ch<'0'||__ch>'9'){if(__ch=='-')__f=-1;__ch=getchar();}
while(__ch>='0'&&__ch<='9'){__ans=(__ans<<1)+(__ans<<3)+(__ch^48);__ch=getchar();}
__x=__ans*__f;}
int n,a,sum,ans;
int box[11];
int f[maxn];
int main()
{
	read(n);
	for(int i=1;i<=n;i++)read(a),box[a]++,sum+=a;
	for(int i=1;i<=10;i++)
	for(int j=1;j<=i;j++)
	if(box[i]&&box[j]&&(sum-i-j)%10==0){
		if(sum%10==0)ans=10;
		else ans=(i+j)%10;
		goto _;
	}
	puts("0");
	return 0;
	_:;
	cout<<ans;
}
```
## $AC$代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T&__x) {
	T __ans=0;
	char __ch=getchar();
	short __f=1;
	while(__ch<'0'||__ch>'9') {
		if(__ch=='-')__f=-1;
		__ch=getchar();
	}
	while(__ch>='0'&&__ch<='9') {
		__ans=(__ans<<1)+(__ans<<3)+(__ch^48);
		__ch=getchar();
	}
	__x=__ans*__f;
}
int n,a,ans;
long long sum;
int box[11];
int main() {
	read(n);
	for(int i=1; i<=n; i++)read(a),box[a]++,sum+=a;
	for(int i=10; i>=0; i--)
		for(int j=i; j>=0; j--)
			if(((box[i]&&box[j]&&i!=j)||(box[i]>=2&&i==j))&&(sum-i-j)%10==0) {
				ans=(i+j)%10;
				if(ans==0)ans=10;
			}
	cout<<ans;
}

```

---

## 作者：pomelo_nene (赞：0)

这道题错了好多次。。。

首先我们知道，如果不存在牛不拢的情况，我们的答案一定是总和模 10（因为我们其他 $n-2$ 张牌组成的数个位一定是 0）。这个值暂称为 $t$。现在我们应该考虑如何组成这个 $t$，因为组成 $t$ 只能要两张牌，所以我们枚举 1~10 的两张牌去组成，我们用一个桶把 1~10 的牌的数量装好枚举。如果可以的话直接输出 $t$，否则牛不拢，输出 0。

坑点：

- 如果组成的两张牌一样，判断数量应该是 `cdisk[i]>=2`。

- 输出 $t$ 的时候判断是否为 0，如果是 0 的话说明这是牛哄哄。

具体看代码吧。

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
int cdisk[11];
int main(){
	int n=read();
	int target=0;
	for(int i=1;i<=n;++i)
	{
		int x=read();
		target+=x;
		target%=10;
		++cdisk[x];
	}
	for(int i=1;i<=10;++i)
	{
		for(int j=1;j<=10;++j)
		{
			if(i==j && cdisk[i]>=2 && (i+j)%10==target)
			{
				printf("%d",target==0?10:target);
				return 0;
			}
			else if(i!=j && cdisk[i]>=1 && cdisk[j]>=1 && (i+j)%10==target)
			{
				printf("%d",target==0?10:target);
				return 0;
			}
		}
	}
	puts("0");
	return 0;
}
```

---

## 作者：optimize_2 (赞：0)

## 50 pts

暴力搜索所有`n-2`个数组成的组合并判断，可以过subtask1.

## 80 pts

搜索`n-2`个数求和，不就是总和减去剩下两个数的和吗?

先统计出和`sum`，接着枚举两个数`i,j`，判断`(sum-a[i]-a[j])%10==0`.

可以过subtask2.

## 100pts

已知`a[i]`，可以计算出若需凑齐10的倍数需要的`x`，并判断`a`数组包不包含`x`(打标记)

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,sum,a[1000010];
int ans;
bool hsh[20];

int main(){
	scanf("%d",&n);
	if(n<=5000) {  //task1,task2
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			sum+=a[i];
		}
		for(int i=1;i<n;i++) {
			for(int j=i+1;j<=n;j++) {
				if((sum-a[i]-a[j])%10==0) {
					ans=max(ans,(sum%10==0)?(10):(sum%10));
				}
			}
		}
		printf("%d\n",ans);
	} else {  //task3
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			sum+=a[i];
			hsh[a[i]]=1;
		}
		//for(int i=1;i<=n;i++) {if(hsh[10-a[i]]) {printf("10");return 0;}}
		for(int i=1;i<=n;i++) {
			if(hsh[(sum-a[i])%10]) {
				ans=max(ans,(sum%10==0)?(10):(sum%10));
				/*
				//cout<<sum<<" "<<i<<endl;
				if(sum%10==0) printf("10\n");
				else printf("%d\n",sum%10);
				return 0;
				*/
			}
		}
		printf("%d",ans);
	}
	return 0;
}
```

---

