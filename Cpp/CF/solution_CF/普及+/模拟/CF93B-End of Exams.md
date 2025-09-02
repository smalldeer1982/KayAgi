# End of Exams

## 题目描述

Students love to celebrate their holidays. Especially if the holiday is the day of the end of exams!

Despite the fact that Igor K., unlike his groupmates, failed to pass a programming test, he decided to invite them to go to a cafe so that each of them could drink a bottle of... fresh cow milk. Having entered the cafe, the $ m $ friends found $ n $ different kinds of milk on the menu, that's why they ordered $ n $ bottles — one bottle of each kind. We know that the volume of milk in each bottle equals $ w $ .

When the bottles were brought in, they decided to pour all the milk evenly among the $ m $ cups, so that each got a cup. As a punishment for not passing the test Igor was appointed the person to pour the milk. He protested that he was afraid to mix something up and suggested to distribute the drink so that the milk from each bottle was in no more than two different cups. His friends agreed but they suddenly faced the following problem — and what is actually the way to do it?

Help them and write the program that will help to distribute the milk among the cups and drink it as quickly as possible!

Note that due to Igor K.'s perfectly accurate eye and unswerving hands, he can pour any fractional amount of milk from any bottle to any cup.

## 样例 #1

### 输入

```
2 500 3
```

### 输出

```
YES
1 333.333333
2 333.333333
2 166.666667 1 166.666667
```

## 样例 #2

### 输入

```
4 100 5
```

### 输出

```
YES
3 20.000000 4 60.000000
1 80.000000
4 40.000000 2 40.000000
3 80.000000
2 60.000000 1 20.000000
```

## 样例 #3

### 输入

```
4 100 7
```

### 输出

```
NO
```

## 样例 #4

### 输入

```
5 500 2
```

### 输出

```
YES
4 250.000000 5 500.000000 2 500.000000
3 500.000000 1 500.000000 4 250.000000
```

# 题解

## 作者：Feyn (赞：1)

[link](https://www.luogu.com.cn/problem/CF93B?contestId=82109)

按照原文的输入格式，$n$ 应该是饮料杯数，$w$ 是每杯饮料的容量，$m$ 是人数。有一点误导，但看样例应该就可以理解了。

先对人数和饮料数的大小关系分类讨论，当人少饮料多时，显然每个人会分到超过已被饮料，这样一来我们就可以考虑从前向后分配每一瓶饮料，当前这个人填满了就换下一个即可。由于每个人分到了不少于一瓶，所以这个人不可能在分他获得的第一瓶饮料时就被填满，所以每瓶饮料不会被超过两个人分，构造合法。

然后就是人多饮料少的情况。因为希望尽量减少每瓶饮料的分配人数，所以可以考虑先让 $n$ 个人从每瓶饮料中拿走该拿的部分，于是剩下的 $m-n$ 个人需要分 $n$ 瓶喝过的饮料。由于每瓶饮料已经被一个人喝过的，所以每瓶残存的饮料只能被一个人喝，也就是 $m-n|n$，由于具有倍数关系，显然有 $\gcd(m-n,n)=m-n$。而知周所众，$\gcd(m,n)=\gcd(m-n,n)=m-n$，于是我们需要做的就是求出人数和饮料数的最大公倍数，然后判断和两个数的差是否相等即可。

要卡一下精度，毕竟 CF 上的数据都是被百般 Hack 后的产物……

```cpp
#include<bits/stdc++.h>
//#define feyn
#define ss sss
const double eps=1e-9;
using namespace std;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

inline int gcd(int s1,int s2){
	return s2==0?s1:gcd(s2,s1%s2);
}
int m,n,num;

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);read(n);read(num);
	double ss=(double)m*n/num;
	if(num>m&&m+gcd(m,num)!=num){
		printf("NO\n");return 0;
	}
	printf("YES\n");
	if(num<=m){
		double want=ss,val=n;int pl=1,wh=1;
		while(wh<=num){
			double now=min(want,val);
			printf("%d %.10f ",pl,now);
			val-=now;want-=now;
			if(want<eps){wh++;want=ss;putchar('\n');}
			if(val<eps)pl++,val=n;
		}
	}
	else{
		for(int i=1;i<=m;i++)printf("%d %.10f\n",i,ss);
		int turn=m/(num-m);
		for(int i=1;i<=num-m;i++){
			for(int j=1;j<=turn;j++)printf("%d %.10f ",(i-1)*turn+j,n-ss);
			putchar('\n');
		}
	}
	
	return 0;
}
```

---

## 作者：ran_qwq (赞：0)

首先 $w$ 对方案不影响。

有一种显然的构造：尽量使得一瓶饮料的划分次数不超过 $1$。把饮料排成一列，对于 $i\in[1,m)$，在 $\dfrac{in}m$ 的位置分开，然后第 $i$ 个人获得 $[\dfrac{(i-1)n}m,\dfrac{in}m]$ 的部分。如果无法划分则无解。

注意下精度。

```cpp
int n,w,m; ldb a[N];
void QwQ() {
	n=rd(),w=rd(),m=rd();
	for(int i=1;i<=m;i++) a[i]=1.*i*n/m;
	for(int i=1;i<=m;i++) if(ceil(a[i])==ceil(a[i-1])&&floor(a[i])==floor(a[i-1])) return puts("NO"),void();
	puts("YES");
	for(int i=1;i<=m;i++)
		if(ceil(a[i])-floor(a[i-1])==1) printf("%d %.6Lf\n",(int)ceil(a[i]),(a[i]-a[i-1])*w);
		else {
			int st,ed;
			if(floor(a[i-1])!=a[i-1]) printf("%d %.6Lf ",st=(int)ceil(a[i-1]),(ceil(a[i-1])-a[i-1])*w);
			else st=a[i-1];
			if(ceil(a[i])!=a[i]) printf("%d %.6Lf ",ed=(int)ceil(a[i]),(a[i]-floor(a[i]))*w);
			else ed=a[i]+1;
			for(int i=st+1;i<ed;i++) printf("%d %.6Lf ",i,(ldb)w);
			puts("");
		}
}
```

---

