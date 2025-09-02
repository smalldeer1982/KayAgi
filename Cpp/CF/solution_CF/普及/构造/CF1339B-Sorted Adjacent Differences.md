# Sorted Adjacent Differences

## 题目描述

## 题意简述
给定一个由$n(1\le n\le 10^{5})$个整数$a_{1},a_{2},a_{3}…a_{n}$组成的数组，请你给出**任意一种**排列方式使得排列后的数组满足$\left|a_{1}-a_{2}\right|\le\left|a_{2}-a_{3}\right|…\le\left| a_{n-1}-a_{n}\right|$，其中$\left|x\right|$表示$x$的绝对值。

你需要回答$t$组独立的测试用例

## 样例 #1

### 输入

```
2
6
5 -2 4 8 6 5
4
8 1 4 2```

### 输出

```
5 5 4 6 8 -2
1 2 4 8```

# 题解

## 作者：vectorwyx (赞：9)

## [题目翻译](https://www.luogu.com.cn/paste/d9ru48qf)
又是一道构造题……

题目就是要求我们通过排序使得相邻元素的差是非递减的

如果我们先把给定数组按从小到大排序，即$a_{1}\le a_{2}\le a_{3}\le …\le a_{n}$，显然有如下结论：$\left| a_{i}-a{j} \right|\ge \left|a_{i}-a_{j+1}\right|,\left| a_{i}-a{j} \right|\le \left|a_{i+1}-a_{j}\right|$

因此，我们可以把$a_{1},a{n}$放到最后面，然后再把$a_{n-1}$插在$a_{1}$前面，再把$a_{2}$插到$a_{n-1}$前面……以此类推，直到所有元素都放到了数组里。

我们最后得到的数组应该长这样（这是n为偶数的情况，n为奇数时还需要在最前面插入$a_{n/2+1}$）：$a_{n/2},a_{n+1-n/2},a_{n/2-1},a_{n+1-(n/2-1)}…,a_{1},a_{n}$，通过上面的结论很容易证明最后得到的数组是一定满足条件的。

故而我们可以用一个头指针和一个尾指针分别初始化为$1$和$n$，不断右移头指针、左移尾指针再用一个栈记录答案，输出，这题就解决了。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
//宏定义简化for循环
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){//快读
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=1e5+5;
int a[maxn],ans[maxn],cnt;
//a是给定的数组，ans是记录答案的栈，cnt是栈顶

inline void work(){
	int n=read();
	cnt=0;
	fo(i,1,n) a[i]=read();
	sort(a+1,a+1+n);//排序
	int k1=1,k2=n;//k1是头指针，k2是尾指针
	while(k1<k2){//开始记录答案
		ans[++cnt]=a[k1];
		ans[++cnt]=a[k2];
		k1++;//右移头指针
		k2--;//左移尾指针
	}
	if(n&1) printf("%d ",a[(n+1)/2]);
   //特殊处理n为奇的情况
	go(i,cnt,1) printf("%d ",ans[i]);//输出
	printf("\n");//不要忘记换行
}

int main(){
	int T=read();//测试用例的数量
	while(T--){
		work();
	}
	return 0;
}
```
你AC了没？AC了就给个赞呗QAQ

---

## 作者：yangrunze (赞：4)

啊，又是一道好玩的构造题

这道题目的要求：给定一个序列$a_1,a_2,a_3,\cdots,an$，将它重新排序，使得每两项之差的绝对值递增，也就是说$|a_1-a_2|\leq|a_2-a_3|\leq|a_3-a_4|\leq\cdots|a_{n-1}-a_n|$

既然是关于“递增”的问题，我们肯定会考虑到排序

排完序之后呢？然后……就没有然后了……不会了……

别忘了[之前说过的构造题秘诀：](https://www.luogu.com.cn/blog/ravenclawyangrunze/solution-cf1333a)**考虑特殊情况，得到简单答案**

那什么才算特殊情况呢？不难看出，**最大值减最小值的差一定是最大的**

所以，我们就可以把它俩放到最后两项

那接下来就应该考虑次大值和次小值了，仔细想一想就会发现还是一样处理，这样答案就呼之欲出啦！

至于代码实现的话……我们可以从头部和尾部各设一个“指针”，从两头向中间逼近！（想想判断回文数或者数组反转的时候是怎么做的）

还有注意最后别忘了是倒序输出（想想为什么）

code：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[233333],s[233333];//a是原数组，s是重排之后的答案
void orzwyx(){//www.luogu.com.cn/blog/yuan-xin/solution-cf1339b
	int n,tot=0;//据某个神仙说，vector常数比较大，所以我们还是用手写的数组，tot是当前s内元素的个数
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);//从输入开始
	sort(a+1,a+1+n);//排个序
	for(int i=1,j=n;i<=j;i++,j--)
	s[++tot]=a[i],s[++tot]=a[j];//从头尾各拿一个
	for(int i=n;i;i--)printf("%d ",s[i]);//因为要把最大值和最小值放在最后，所以要倒序输出
	printf("\n");
}
int main(){//这就没啥好说的了吧
	int t;
	scanf("%d",&t);
	while(t--){
		orzwyx();
	}
} 
```

最后，从来没涨过Rating的yrz祝大家CF能涨Rating哦！


---

## 作者：gyh20 (赞：3)

CF 一道感觉比较水的构造题。

假设我们把所有数排序，再放到数轴上，看起来就明显很多了。

我们可以从最中间的点开始，一直向左，然后向右一直重复，可以发现，因为 $a_{i+1}-a_{i-1}\geq a_{i+1}-a_i$，所以这样始终是合法的。

单独这样处理不是很好处理，可以直接分 $n$ 的奇偶性讨论。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
} 
int n,m,t,a[100002];
int main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=read();
		sort(a+1,a+n+1);
		if(n&1){
			re int x=n/2+1;printf("%d ",a[x]);
			for(re int i=1;i<=n/2;++i)printf("%d %d ",a[x+i],a[x-i]);
		}
		else{
			re int x=n/2;printf("%d ",a[x]);
			for(re int i=1;i<=n/2-1;++i)printf("%d %d ",a[x+i],a[x-i]);printf("%d ",a[n]);
			putchar('\n');
		}
	}
}
```


---

## 作者：devout (赞：0)

这题刚开始看样例的构造方法没啥思路就先把C给切掉了回来再想

我们不要看他样例里面给出的答案，样例解释里面有这样两句话

> There are other possible answers like "5 4 5 6 -2 8".

> There are other possible answers like "2 4 8 1".

然后我们就很容易想到从中位数往左，往右往左往右的来回取，而这样做显然是对的，因为每次的差都比之前大

然后我们发现样例里面只给出了偶数的情况，所以奇数和偶数要分类讨论（雾）

奇数要先输出一下中位数然后再往两边取

然后就是代码了，~~自认为写的很简洁~~

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int t,n;
int a[N];

int main()
{
    read(t);
    while(t--){
        read(n);
        Rep(i,1,n)read(a[i]);
        sort(a+1,a+n+1);
        int l,r;
        if(n&1)printf("%d ",a[n/2+1]),l=n/2,r=n/2+2;
        else l=n/2,r=n/2+1;
        while(l>=1||r<=n){
            if(l>=1)printf("%d ",a[l]);
            if(r<=n)printf("%d ",a[r]);
            l--,r++;
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：老咸鱼了 (赞：0)

题目大意：给你一串数组，要你排序后的数组满足abs(a[i]-a[i-1])>=abs(a[i-1]-a[i-2]).

题目数据范围是1e5，所以肯定只能用不超过nlogn的算法写，这种时间复杂度再根据题目的有序，我们很容易就想到要排序，观察样例我们会发现，他这个是按照排完序后的数组从中间到两边的顺序输出，所以我们只要照着他这个模仿就行了。

具体证明：因为数组是有序的所以a[i]-a[i-1]>=a[i]-a[i-2].然后我们是从中间开始的,假设我们是一个数组长度为5的,那么abs(a[3]-a[2])<=abs(a[4]-a[2]),然后abs(a[4]-a[2])<=abs(a[4]-a[1]),接着我们可以类比到n的情况.

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1555555;
inline int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;c=getchar();
	}
	while(c>='0'&&c<='9'){
		s=(s<<1)+(s<<3)+(c^48);c=getchar();
	}
	return f*s;
}
int a[N];
int main(){
	int T=read();
	while(T--){
		int n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		sort(a+1,a+1+n);
		if(n%2==1){
			printf("%d ",a[(n+1)/2]);
		}
		int l=n/2,r=n-l+1;
		for(int i=1;i<=n/2;i++){
			printf("%d %d ",a[l--],a[r++]);
		}
		printf("\n");
	}
	return 0;
}
```


---

