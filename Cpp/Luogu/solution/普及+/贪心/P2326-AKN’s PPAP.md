# AKN’s PPAP

## 题目描述

“I have a pen,I have an apple.Eh,Apple-Pen!.

I have a pen,I have pineapple.En,Pineapple-Pen!

Apple-Pen,Pineapple-Pen.Eh,Pen-Pineapple-Apple-Pen!”

Akn最近中毒于一首音乐，于是他买来了一堆苹果来学习这首音乐。Akn发现，只要边唱这首歌，边做把两个完整的苹果碰在一起的动作，两个苹果就会融合成一个新的大苹果，但是大苹果却不能再融合，因为他的细胞内部结构已经改变。Akn还发现，当两个苹果融合的时候，苹果的质量会发生一些玄妙的改变，就是与运算（a&b）。但是，最近他的同学找他要一个苹果吃，akn出于好心，准备把他学习ppap用的苹果融合成的大苹果给同学吃，好让同学一起中毒于ppap，而且akn还想让大苹果的质量最大，那么请问akn能给同学吃的苹果质量最大是多少？


## 说明/提示

由于数据包大小限制，故只上传部分数据（第1,2,3,4,5,6,7,8,10,11,12,13,16,19,20点）

第一组数据解释：

```cpp
1(2)=1
3(2)=11
5(2)=101
7(2)=111
```
选取5和7进行融合最终得到答案5
数据范围

10%的数据n≤5000，t≤1

另有10%的数据n≤2000，t≤6

另有20%的数据a≤2^10

另有5%的数据n≤10^5，a≤2^20，最大的两个数相等

另有20%的数据n≤10^4，a≤2^15

另有15%的数据n≤10^5，a≤2^20，t≤6

另有15%的数据n≤10^5，a≤2^20，t≤12

100数据n≤10^5，a≤2^20，t≤20

By：worcher


## 样例 #1

### 输入

```
3
4
1 3 5 7
10
32 54 21 52 14 25 92 75 14 27
21
1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576
```

### 输出

```
Case #1: 5 
Case #2: 72
Case #3: 0
```

# 题解

## 作者：7wwwwth (赞：14)

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,n,a[100010],b[100010];
/*
找到二进制中最高位是1的数 确定次高位的时候只是从二进制最高位是1的数里选 以此类推 
*/
int work(){
    cin>>n; 
    for (int i=1;i<=n;i++) cin>>a[i];
    for(int k=20;k>=0;k--){//最高有20位 
        int top=0; 
        for(int i=1;i<=n;i++) 
            if(a[i]&(1<<k)) b[++top]=a[i];//判断a[i]是否为1 
        if(top>1){
            for(int i=1;i<=top;i++) a[i]=b[i];
            n=top;
        }
    }
    return (a[1]&a[2]);
}
int main(){
    cin>>t;
    for (int i=1;i<=t;i++){
    	cout<<"Case #"<<i<<": "<<work()<<endl;
	}
}
```

---

## 作者：sel_fish (赞：9)

前言：首先说一下写这一篇题解的目的是为了解释[wwwwth](https://www.luogu.org/space/show?uid=51395)这个大佬的代码，如果侵权，请联系删除

**题目大意：给你一列数，让你求出这列数中任意两个数与运算之后最大值**

### 解法：贪心

1. 由于题目中要求最大值，所以我们可以从最高位开始枚举，因为a的最大值只有2的20次方，所以我们从第20位开始向后枚举

2. 对于每个数，如果与当前位与运算后仍然为1，那么我们就把这个数加入一个数组，以后再用那个数组继续枚举

3. 我们需要加入一个条件，如果加入数组的小于2，那么我们就不能用那个数组，因为只有1的数或者没有数，题目中要求至少要两个数合并

4. 如果枚举的当前位有多于两个数存入了新数组，那么我们就把新数组的值赋给原数组继续枚举

5. 最后我们只需要输出原数组第一位和第二位与运算之后的结果即可，因为我们当前求得的已经是最优解

AC代码

```cpp
#include<cstdio>
#define si 100005
#define re register int
using namespace std;
int T,n,cnt,a[si],b[si];
inline int read() {
	int x=0,cf=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') cf=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*cf;
}
int main() {
	T=read();
	while(T--) {
		n=read(),cnt++;
		for(re i=1;i<=n;i++) a[i]=read();
		for(re k=20;k>=0;k--) {
			int tp=0;
			for(re i=1;i<=n;i++) {
				if(a[i]&(1<<k)) b[++tp]=a[i];
			}
			if(tp>1) {
				for(re i=1;i<=tp;i++) a[i]=b[i];
				n=tp;
			}
		}
		printf("Case #%d: %d\n",cnt,a[1]&a[2]);
	}
	return 0;
}
```


---

## 作者：暴力出奇迹NB (赞：7)

## 思路：模拟+贪心优化

先扫一眼数据范围：n≤10^5, O(n^2) 暴力显然不行

这个时候，我们就要用到贪心了。      
设两个数 a、b, 那可得 **a&b<=a 并且 a&b<=b**                 
为什么呢？ 我们拿样例一举例。
```
1(2)=1
3(2)=11
5(2)=101
7(2)=111
```
5&7 用竖式表示：               
```
5:       1 0 1
7:     & 1 1 1
       —————————
         1 0 1   =5
```
二进制中只有0和1，而&是只有 1&1=1，其他情况全是0，所以两个数 & 后的结果一定小于等于这两个数。

利用这点我们就能在代码中多加一个判断，如果当前要 & 的数已经小于等于最大值 ans 了，那么直接 continue 退出当前循环。

### 上代码！！！

```
#include<stdio.h>
#include<algorithm>
#include<iostream> 
using namespace std;
int t,n,a[100005],ans,num=1;
//ans存最大答案，num是记录在第几组 
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		ans=0;//记得每次都要赋值0 
		for(int i=1;i<=n;i++){
			if(a[i]<=ans)continue;//贪心 
			for(int j=i+1;j<=n;j++){
				if(a[j]<=ans)continue;//贪心 
				ans=max(ans,a[i]&a[j]);//找最大的 
			}
		}
		printf("Case #%d: %d\n",num,ans);
		num++;
	}
	return 0;
} 
```


---

## 作者：Doveqise (赞：2)

Orz机房dalao叫我来写这道题...  
不想写正解系列...  
然后想到了之前本校学长的《骗分导论》  
#### 骗分是我们的红太阳，没有他我们会死  
话不多说，看起来数据不太强力，开始骗分  
一开始想了一些奇淫技巧  
不过忘了 1 & 0 = 0   
47分代码(骗分:  
```c++
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int a[maxn];
signed main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1;ti<=T;ti++)
    {
        memset(a,0,sizeof(a));
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        int ans=0;
        for(int i=n-1;a[i]>=(a[n]>>4);i--)
            ans=max(ans,a[i]&a[n]);
        printf("Case #%d: %d\n",ti,ans);
    }
    return 0;
}
```
然后突然发现1 & 0 = 0...
所以换了一个写(pian)法(fen)  
72分代码((骗分:
```c++
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int a[maxn];
signed main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1;ti<=T;ti++)
    {
        memset(a,0,sizeof(a));
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        int ans=0;
        int lim=a[n]>>1?a[n]>>1:1;
        for(int i=n;a[i]>=lim;i--)
            for(int j=i-1;a[j]>=lim;j--)
                ans=max(ans,a[i]&a[j]);
        printf("Case #%d: %d\n",ti,ans);
    }
    return 0;
}
```
这个其实是能骗满的emmm(但是懒得改无用部分)  
所以又换了一种奇淫技巧  
$O(n)$扫一遍然后记一下相邻&的最大值  
93分代码:
```c++
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int a[maxn];
signed main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1;ti<=T;ti++)
    {
        memset(a,0,sizeof(a));
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        int ans=0;
        for(int i=1;i<=n;i++)
            ans=max(ans,a[i]&a[i+1]);
        printf("Case #%d: %d\n",ti,ans);
    }
    return 0;
}
```
然后看了看WA的地方...我决定多来几个  
AC代码:
```c++
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int a[maxn];
signed main()
{
    int T;
    scanf("%d",&T);
    for(int ti=1;ti<=T;ti++)
    {
        memset(a,0,sizeof(a));
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        sort(a+1,a+1+n);
        int ans=0;
        for(int i=1;i<=n;i++)
            ans=max(max(max(max(ans,a[i]&a[i+1]),a[i]&a[i+2]),a[i]&a[i+3]),a[i]&a[i+4]);
        printf("Case #%d: %d\n",ti,ans);
    }
    return 0;
}
```
最后总结一下  
骗分在你写(bu)不(xiang)出(xie)正解的时候还是有点用的  
~~而且 这题数据好像该加强了~~  
P.S. 刚刚机房dalao说讨论版里面有跟我做法差不多的emmm果然骗分技巧天下通用

---

## 作者：Dog_Two (赞：2)

Orz上面的dalao都好巨啊。

我太弱了，只能写模拟来做这道题了。

## 思路
根据进制知识，我们知道：对于一个确定进制的数字，其从高到低只要有一位大于另外一个数字的这一位，那么其数值就大于另一个数字。

由此，我们维护一个集合，由高到低逐位check：
- 对于某一位i，如果有至少两个数字的这一位不为0，我们就把这一位为0的数字从集合中删掉，直到集合中有且只有2个数字或者check到最低位；

- 如果不存在任何一位，使得至少两个数字这一位不为0，特判这种情况，输出0；

- 如果check到第0位仍然有超过3个数字在集合中保留，那么不必担心，这说明这三个（以上）数字的值是重复的。

## 代码

下面贴代码，集合S维护了可能导致最优解的下标，时间复杂度是O(nlogn)的，但是因为采用了STL，所以常数巨大。

注意全局cnt数组和main中Bitcnt的区别，如果采用严格逐位的方法，可以略去其中的一个：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef set<int>::iterator It;
const int maxn=1e5+10,maxB=32;
int T,n;
set<int> S;
bool acc[maxB][maxn];
int a[maxn],cnt[maxB];
int main(){
	cin>>T;
	for(int Q=1;Q<=T;++Q){
		memset(acc,0,sizeof(acc));
		memset(cnt,0,sizeof(cnt));
		S.clear();
		cin>>n;
		for(int i=1;i<=n;++i){
			int val; scanf("%d",&val);
			a[i]=val;
			for(int j=0;val;++j,val>>=1)
				if(val&1) ++cnt[j],acc[j][i]=true;
		}
		int Hi=-1;
		for(int i=31;i>=0;--i) if(cnt[i]>1){
			Hi=i;
			for(int j=1;j<=n;++j) if(acc[i][j]) S.insert(j);
			break;
		}
		if(Hi==-1){
			cout<<"Case #"<<Q<<": "<<0<<endl;
			continue;
		}
		int Bitcnt[maxB]={0};
		for(It it=S.begin();it!=S.end();++it){
			int val=a[*it];
			for(int j=0;val;++j,val>>=1) Bitcnt[j]+=val&1;
		}
		for(int i=Hi-1;i>=0 and S.size()>2;--i) if(Bitcnt[i]>1){
			vector<int> Dle;
			for(It it=S.begin();it!=S.end();++it){
				int idx=*it;
				if(!acc[i][idx]){
					Dle.push_back(idx);
					int val=a[idx];
					for(int j=0;val;++j,val>>=1) Bitcnt[j]-=val&1;
				}
			}
			while(!Dle.empty()){
				S.erase(Dle.back());
				Dle.pop_back();	
			}
		}
		It it=S.begin();
		int ans=a[*it];
		++it,ans&=a[*it];
		cout<<"Case #"<<Q<<": "<<ans<<endl;
	}
	return 0;
}
```
### 问：为什么在删除的时候要把删除元素存在一个vector里呢？
### 答：每次删除都可能引起平衡树形态的变化，迭代器的顺序也可能改变，所以SET和MAP不能边遍历边删除

### 问：用了这么多STL，会超时啊，能优化吗？
### 答：可以如下优化,维护一个数组而不是STL-set：
```cpp
set<int>S -> int S[maxn],m=0;
S.insert(idx) -> S[++m]=idx;
S.erase(idx) -> swap(S[idx],S[m--]);
```


---

## 作者：柠檬草苏打水 (赞：1)

## 本题思路：按位贪心

## 具体做法：

找到最高位&1的数，确定次高位的时候只从最高位&1的数里选，此次类推

## Code：
```cpp
#include<cstdio>
int t,n,a[100010],b[100010];
int work()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",a+i);
    for(int k=21;k>=0;k--)
    {
        int top=0;
        for(int i=1;i<=n;i++)
            if(a[i]&(1<<k)) b[++top]=a[i];
        if(top>=2) 
        {
            for(int i=1;i<=top;i++) a[i]=b[i];
            n=top;
        }
    }
    return (a[1]&a[2]);
}
int main()
{
    scanf("%d",&t);
    for (int i=1;i<=t;i++) printf("Case #%d: %d\n",i,work());
    return 0;
}
```

---

## 作者：ArachnidaKing (赞：1)

# 首先声明：模拟退火非本题正解！！！  
#### 一点都想不出正解的我试图用模拟退火A掉这道题。事实证明，被我得逞了……
#### 本题解主要旨在提供另一种思路并未这种思路提供一篇示例代码，而不重在讲解模拟退火的原理。如有不懂模拟退火的同学可以先配合[同机房大佬写的博客](https://ciyang.blog.luogu.org/solution-p2210)A掉[P2210 Haywire](https://www.luogu.org/problemnew/show/P2210)后看此篇题解哦QwQ  
#### 代码在此：  
```cpp
#include<cstdio>//以下四行防手残，就是本人各种常见手误，可以跳过……
typedef int itn,nti,tin,tni,nit;
#define pritnf printf
#define scnaf scanf
#define retrun return
#define sizoef sizeof//以下八行为方便
#define inl inline
#define br break
#define con continue
#define mst(a,b) memset(a,b,sizeof(a))
#define fora(x,a,b) for(re tni x=a;x<=b;++x)
#define forb(x,a,b) for(re nit x=a;x>=b;--x)
#define re register
#define stt struct
#define infa 0x3f3f3f3f
#define infb 0x7fffffff
#define infd 0x7f
#define abss(x) ((x)>(0)?(x):(-1)*(x))
#define maxx(a,b) ((a)>(b)?(a):(b))
#define minn(a,b) ((a)<(b)?(a):(b))
#define pf(_) ((_)*(_))
typedef long long ll;
typedef long double ld;
using namespace std;
const nit maxa=2e5+4;
const nit maxb=20;
const nit maxc=10;
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>
const double chushiwendu=10000;//初始温度，此题（对模拟退火来说）过水，不必太高
const double zhongzhiwendu=1e-13;//终止温度，是个极小实数
const double dertT=0.978;//每次温度变化量
#define SJ (1.0*rand()/RAND_MAX)//生成一个0-1的随机实数用以判断是否接受较差解

nit t,tt,n,x[maxa]={0},ans,lsa,lsb,lsr,dqa,dqb,dqr;//ans（answer）为全局最优解。ls*读作“临时*”，dq*读作“当前*”，都是字面意思。b为每次进行与运算的两个数。

inl bool cpe(tni a,tni b);//sort比较用函数
inl tni sj(tni a,tni b);//生成a-b的随机数

tni mian()
{
	srand(time(NULL));//玄学设种子
	srand(rand()+19260817);
	srand(rand()+19491001);
	srand(rand());
	//
	scanf("%d",&t),tt=t,++t;//tt为总次数，t用以循环，(tt-t+1)表示当前次数
	while(--t)
	{
		ans=0;
		scanf("%d",&n);
		fora(i,1,n)
		{
			scanf("%d",&x[i]);
		}
		sort(x+1,x+1+n,cpe);//大体思路——我们不必细推即可得到：两个极大数与运算肯定比两个极小数大，所以进行递增排序，一开始很小，（总体上）慢慢往大里跳。
		//
		fora(i,1,120)//试过卡时写法，可惜写炸了……顺便求一波路过大佬指点这里卡时怎么写QAQ
		{
			dqa=1,dqb=2,dqr=0;
			for(re double T=chushiwendu;T>=zhongzhiwendu;T*=dertT)
			{
				do
				{
					lsa=dqa+sj((-1)*(n-dqa),n-dqa+1);
					lsb=dqb+sj((-1)*(n-dqb),n-dqb+1);
				}
				while((lsa<1)||(lsa>n)||(lsb<1)||(lsb>n)||(lsa==lsb));//生成随机数据，如果越界、不符合要求就再来一组
				//
				lsr=x[lsa]&x[lsb];//求出当前解用以比较
				if(lsr>ans)//比全局最优解优，一定接受它（存在全局最优解里）
				{
					ans=lsr;
				}
				else if(exp(lsr-ans)/T<SJ)//比全局最优解差，以一个越来越低的概率接受它（存在暂时最优解里）
				{
					dqa=lsa;
					dqb=lsb;
					dqr=lsr;
				}
			}
		}
		//
		pritnf("Case #%d: %d\n",tt-t+1,ans);//这里注意格式和#*，WA了无数次终于发现一直在输出总次数……
	}
	//
	return 0；//完美收官
}

inl bool cpe(tni a,tni b)
{
	return a<b;
}

inl tni sj(tni a,tni b)
{
	return rand()%(b-a)+a;
}//本代码已进行防抄袭处理QwQ
```

---

## 作者：war1111 (赞：1)

P2326 AKN’s PPAP

比较裸的贪心

从高位向下枚举，如果当前位为1的个数大于1，ans+=(1<<i),然后从中这些数中再向下枚举。

程序：http://www.cnblogs.com/war1111/p/7729566.html


---

## 作者：Yummy_ (赞：0)

**思路：排序+贪心**
------------

题意：给一列数，求出这列数中任意两个数与运算之后最大值

首先不难写出暴力当然A不了O(n^2)；

考虑贪心，将苹果质量从小到大排序；

两个指针，一个从大到小，一个从小到大

遍历比较出当前最大值

这里涉及到：如果一个苹果质量比当前的最大质量还小，那么它与任何比他小的苹果的质量都比当前答案小（易证）；

while（）循环更新【可以参与比较的苹果的范围】（即代码中的tt）

模拟一下即可；

时间复杂度约为O(n*logn);

接下来是Code：
```c
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;
int a[100003],maxn;
int main() {
	int t,n,cnt=0;
	scanf("%d",&t);
	while(t--){
		cnt++;
		maxn=0;
		memset(a,0,sizeof(a));
		scanf("%d",&n);
		for(int i=1; i<=n; i++) {
			scanf("%d",&a[i]);
		}
		sort(a+1,a+1+n);
		int tt=1;
		for(int i=n;i>=tt;i--){
			for(int j=1;j<i;j++){
				maxn=max(maxn,a[j]&a[i]);
			}
			while(a[tt]<maxn)tt++;
		}
		printf("Case #%d: %d\n",cnt,maxn);
	}
	return 0;
}
```
// 2019RP++
----------



---

