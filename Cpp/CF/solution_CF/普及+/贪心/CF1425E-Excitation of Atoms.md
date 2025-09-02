# Excitation of Atoms

## 题目描述

Mr. Chanek is currently participating in a science fair that is popular in town. He finds an exciting puzzle in the fair and wants to solve it.

There are $ N $ atoms numbered from $ 1 $ to $ N $ . These atoms are especially quirky. Initially, each atom is in normal state. Each atom can be in an excited. Exciting atom $ i $ requires $ D_i $ energy. When atom $ i $ is excited, it will give $ A_i $ energy. You can excite any number of atoms (including zero).

These atoms also form a peculiar one-way bond. For each $ i $ , $ (1 \le i < N) $ , if atom $ i $ is excited, atom $ E_i $ will also be excited at no cost. Initially, $ E_i $ = $ i+1 $ . Note that atom $ N $ cannot form a bond to any atom.

Mr. Chanek must change exactly $ K $ bonds. Exactly $ K $ times, Mr. Chanek chooses an atom $ i $ , $ (1 \le i < N) $ and changes $ E_i $ to a different value other than $ i $ and the current $ E_i $ . Note that an atom's bond can remain unchanged or changed more than once. Help Mr. Chanek determine the maximum energy that he can achieve!

note: You must first change exactly $ K $ bonds before you can start exciting atoms.

## 说明/提示

An optimal solution to change $ E_5 $ to 1 and then excite atom 5 with energy 1. It will cause atoms 1, 2, 3, 4, 5 be excited. The total energy gained by Mr. Chanek is (5 + 6 + 7 + 8 + 10) - 1 = 35.

Another possible way is to change $ E_3 $ to 1 and then exciting atom 3 (which will excite atom 1, 2, 3) and exciting atom 4 (which will excite atom 4, 5, 6). The total energy gained by Mr. Chanek is (5 + 6 + 7 + 8 + 10 + 2) - (6 + 7) = 25 which is not optimal.

## 样例 #1

### 输入

```
6 1
5 6 7 8 10 2
3 5 6 7 1 10```

### 输出

```
35```

# 题解

## 作者：chenxia25 (赞：2)

**[Portal]( https://www.luogu.com.cn/problem/CF1425E )**

我们考虑对 $k$ 分类。

- $k=0$。那不用修改了，直接做吧；

- $k>1$。我们可以发现，如果真的把它当成一个有向图，然后求传递闭包啥的话，是肯定不可做的，所以一定有比较简明的结论。我们考虑答案的上限，就是用最小的代价获得最大的价值，也就是激活代价最小的一个原子，然后得到所有原子的价值。这能做到吗？不难想到一种方案，$\forall i\in[1,n)$，只需要令 $E_i=1,E_{i-1}=i+1$（$i=1$ 则不用动），则可实现从 $i$ 开始经过所有点。但是这还不完美，$i=n$ 的时候无法实现，要是偏偏 $d_n$ 最小该怎么办呢？我们考虑从 $n$ 出发的情况，显然它不能有出边，所以只能激活它本身，所以可以看作相对独立的；

- $k=1$。按照剧本，这三种情况应该主次分明，所以 $k=1$ 是主（

  我们考虑修改的是 $E_i$。那么分为两种情况，一是往前连，一是往 $i+1$ 后面连。根据贪心，连 $1$ 和连 $i+2$ 分别是所在情况中最优的，因为这样它们的所有点的传递闭包都包含其他情况下该点的传递闭包。于是对两种分别求一下即可。

  连 $1$ 的话，两边是断开的，左边是个环，右边是个链，都异常好求；连 $i+2$ 还稍微有点东西，被激活的点的集合分为三种情况：

  1. $[i+1,n]$ 的一个后缀。这个预处理一下随便求；
  2. $[1,i]\cup[i+2,n]$ 的一个后缀，这个显然先当作 $[1,n]$ 再把 $i+1$ 的减掉即可；
  3. $[1,n]$ 的一个后缀，这个先直接求，但是注意到要激活的不只有最有后缀的左端点，还有 $i+1$，加上去即可。

总的来说，这是一个非常不错的分类讨论题。下次看到这种按照算法不可做的题，一定要坚定信念寻找结论。

**_[code]( https://www.luogu.com.cn/paste/y6y9fb6v )_**

---

## 作者：suxxsfe (赞：0)

http://codeforces.com/problemset/problem/1425/E  

设 $sum_i$ 为前缀和，$gain_i$ 为 $\max sum_n-sum_{j-1}-D_j,j\ge i$，$gain2_i$ 为 $\max sum_n-sum_{j-1}-D_j,j\le i$  

### k=0  

显然 $ans=max(gain_1,0)$  

### k>1  

构造，对于一个 $i$，将 $E_i$ 改为 $1$，将 $E_{i-1}$ 改为 $i+1$  
这样可以激发所有原子，只要将 $i$ 选为 $D_i$ 最小的即可  

### k=1  

分两种情况  

将 $E_i$ 向前改，此时肯定改为 $1$，同样代价把前面都选上才会最优  
这样如果要激发 $[1,i]$，只需花费 $min=\min D_j,j\le i$ 的代价  
如果要激发 $[i+1,n]$ 中的某个子段，用 $gain$ 计算  
答案为 $sum_i-min+\max(gain_{i+1},0)$，枚举所有 $i$ 取最大值  

将 $E_{i-1}$ 向后改，此时肯定改为 $i+1$，否则少取中间跳过的一段也不会最优  
如果激发点 $j\ge i$，答案为 $gain_i$，和 $k=0$ 的类似  
如果激发点 $j<i$，那么会激发 $[j,n]$ 所有点除去 $i$，再考虑 $i$ 要不要单独激发一下，答案是 $gain2_{i-1}-\min(D_i,A_i)$  
单独再激发一下 $i$ 的情况已经包含了两个激发点同时在 $i$ 的前后，不用单独考虑这种两个激发点的情况了  
仍然枚举 $i$ 取最大值  

```cpp  
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#define reg register
inline int read(){
	register int x=0;register int y=0;
	register char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')y=1;c=getchar();}
	while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
	return y?-x:x;
}
#define N 100006
int n;
long long sum[N],a[N],gain[N],gain_[N];
long long d[N];
int main(){
	n=read();int k=read();
	for(reg int i=1;i<=n;i++) sum[i]=sum[i-1]+(a[i]=read());
	for(reg int i=1;i<=n;i++) d[i]=read();
	for(reg int i=1;i<=n;i++) gain[i]=sum[n]-sum[i-1]-d[i],gain_[i]=std::max(gain_[i-1],gain[i]);
	for(reg int i=n-1;i;i--) gain[i]=std::max(gain[i],gain[i+1]);
	if(!k) return printf("%lld",std::max(gain[1],0ll)),0;
	if(k>1){
		long long ans=sum[n]-d[1];
		for(reg int i=2;i<n;i++) ans=std::max(ans,sum[n]-d[i]);
		ans=std::max(ans,a[n]-d[n]);
		printf("%lld",std::max(ans,0ll));
		return 0;
	}
	long long ans=0;
	long long min=std::min(d[1],d[2]);
	for(reg int i=2;i<n;i++){
		ans=std::max(ans,sum[i]-min+std::max(0ll,gain[i+1]));//向前改 
		min=std::min(min,d[i+1]);
	}
	for(reg int i=2;i<n;i++){
		ans=std::max(ans,std::max(gain[i],gain_[i-1]-std::min(a[i],d[i])));//向后改
//		ans=std::max(ans,gain[])
	}
	for(reg int i=2;i<=n;i++) ans=std::max(ans,sum[n]-sum[i-1]-d[i]);
	printf("%lld",ans);
	return 0;
}
```

---

