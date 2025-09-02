# [USACO23JAN] Moo Route S

## 题目描述

Farmer Nhoj dropped Bessie in the middle of nowhere! At time $t=0$, Bessie is located at $x=0$ on an infinite number line. She frantically searches for an exit by moving left or right by $1$ unit each second. However, there actually is no exit and after $T$ seconds, Bessie is back at $x=0$, tired and resigned.

Farmer Nhoj tries to track Bessie but only knows how many times Bessie crosses $x=0.5,1.5,2.5, \cdots ,(N−1).5$, given by an array $A_0,A_1, \cdots ,A_{N−1} (1 \le N \le 10^5, 1 \le A_i \le 10^6, \sum A_i \le 10^6)$. Bessie never reaches $x>N$ nor $x<0$.

In particular, Bessie's route can be represented by a string of $T= \sum\limits_{i=0}^{N-1}A_i$
$L$s and $R$s where the $i$-th character represents the direction Bessie moves in during the ith second. The number of direction changes is defined as the number of occurrences of $LR$s plus the number of occurrences of $RL$s.

Please help Farmer Nhoj find any route Bessie could have taken that is consistent with A
and minimizes the number of direction changes. It is guaranteed that there is at least one valid route. 

## 说明/提示

### Explanation for Sample 1

There is only $1$ valid route, corresponding to the route $0 \rightarrow 1 \rightarrow 2 \rightarrow 1 \rightarrow 2 \rightarrow 1 \rightarrow 0$. Since this is the only possible route, it also has the minimum number of direction changes. 

### Explanation for Sample 2

There are $3$ possible routes:

RRLRRLRLLL  
RRRLRLLRLL  
RRRLLRRLLL  

The first two routes have $5$ direction changes, while the last one has only $3$. Thus the last route is the only correct output.

### Scoring

 - Inputs $3-5$: $N \le 2$
 - Inputs $3-10$: $T=A_0+A_1+ \cdots +A_{N−1} \le 5000$
 - Inputs $11-20$: No additional constraints.

## 样例 #1

### 输入

```
2
2 4```

### 输出

```
RRLRLL```

## 样例 #2

### 输入

```
3
2 4 4```

### 输出

```
RRRLLRRLLL```

# 题解

## 作者：FFTotoro (赞：11)

本题需要使用**贪心算法**。

考虑如何让转向的次数尽量少：在往一个方向走的时候，**能走就走**，最大限度地消耗完经过次数。

往右走的时候，策略十分简单——只要当前点的次数大于等于 $2$，那么就一定可以走（包括返程正好 $2$ 次）。走过之后，这个点的次数减去 $1$。

往左走的时候，如果将要走到某个坐标时，这个坐标上的剩余次数大于等于 $3$，那么就可以放心地走过去——因为如果需要再回来消耗剩余的次数，次数绝对是足够的。但是如果这个点只剩下走过去的那仅有的一次机会，那就要分情况讨论了：

- 现在所在的点右边的点次数全部消耗完——反正不用再回去了，往左走；

- 右边的点次数没有消耗完——回到往右走的状态，因为如果往左走了就再也回不去了；

走过去后该点次数减 $1$。

实现时，如果次数没消耗完，就标记一下，往左走的时候看一下标记即可。

放代码：

```cpp
/*
ID: CrowMatrix
TASK: Moo Route
LANG: C++
*/
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n,x=0; cin>>n;
  vector<int> a(n);
  for(auto &i:a)cin>>i;
  while(1){
    vector<bool> r(n+1); // 标记数组
    while(x<n){
      if(a[x]>=2)a[x]--,x++,cout<<'R'; // 还可以往右走
      else break; // 次数没了，不需要继续往右走
    }
    while(1){
      if(x<n&&(a[x]>1||r[x+1]))r[x]=true; // 右边还有没消耗完的次数
      if(x&&(!r[x]||a[x-1]>1))a[--x]--,cout<<'L'; // 可以往左走
      else break; // 还要回去
    }
    if(!x&&!r[0])break; // 走完了
  }
  return 0;
}
```

---

## 作者：Xy_top (赞：8)

这题我们可以贪心构造。

大体思路是这样的：如果能继续维持之前走的方向，那么就维持，否则就改变。

什么时候能维持呢？

1. 上一次是向右走，右边还有走的次数，那就向右走，否则向左走。
2. 上一次是向左走，有些复杂，先看左边走的次数还剩下多少，只剩下 $1$ 次意味着走过去就不能再来了，所以右边的必须都是 $0$ 才可以继续往左走，否则只能向右走。如果左边的次数 比 $1$ 大，那就向左走。

按照思路模拟就行了，右边全为 $0$ 可以使用树状数组维护，但是没这个必要，只需要检查右边的元素是否为 $0$ 即可。

---

## 作者：Demeanor_Roy (赞：4)

- 摘自 [here](https://www.luogu.com.cn/blog/261213wrh/usaco-2023-jan-sliver-ti-xie)。

------------

由于数据保证有解，我们只需要坚持一个基本原则：**能不转向就不转向**。

往右走，只要左边经过次数未满且未到边界就一直走。

往左走，此时需要考虑最后要走回去，所以还需满足 **不经过第二个剩余经过次数为 $1$ 的连通块。** 举个例子，如还需经过次数为 `3 1 1 5 5 5 1 1 1`，就最多只能走到四号位置。

暴力模拟，由于指针加减次数不超过 $\sum A_i$，所以时间复杂度为 $O(\sum A_i)$。[代码](https://www.luogu.com.cn/paste/wucn2ifr)

---

## 作者：yujinning (赞：4)

本题存在两种解法，第一种较为简明，使用算法均为贪心。

----

### 解法一


显然，贪心的方针为尽量不转向。

因为每个 $.5$ 都是代表一条线段需要被经过几次，而每条线段若向左遍历一次必向右遍历一次，所以值为偶数。 

设原来的 $x.5$ 的值为 $k$ ，则本条线段必然会被向左走的遍历经过 $k/2$ 次。

既然贪心的方针为不转向，那么第一次操作必然会向右走到头，每条线段就还会被遍历 $k/2-1$ 次。

记新数组为 $a$ ，对于新数组的贪心，考虑每次在非零最右边的点走到次右边值为 $1$ 的点的线段的右边的线段，然后再走回来，这样可以保证每次走的范围都能做到最大，还不会出现无解状况。

---

### 解法二

贪心方针不变，但考虑什么时候转向是最晚的且合法的。

具体来说：

* 如果上次往左走，考虑左边线段的值是否为 $1$，如果是 $1$，考虑右边是否还有线段未遍历，有则向右遍历，无则向左回退。

* 如果上次往右走，若右边还能走，就往有走，否则就向左走。

事实上，解法二同于解法一，因为解法二中往右走等同于解法一种的 $a$ 数组，而向左走则与“考虑每次在非零最右边的点走到次右边值为 $1$ 的点的线段的右边的线段”解法相同，尽管思路不同。

----

AC 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100009;
int n,a[N],b[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	for(int i=1;i<=n;i++) cout<<"R";
	for(int i=1;i<=n;i++) b[i]=(b[i]-2)/2;
	int id=n;
	for(;id>=1;id--){
		while(b[id]!=0){
			int i;
			for(i=id;i>=1;i--){
				if(b[i]==0) break;
				b[i]--;
				cout<<"L";
			}
			for(int j=i+1;j<=id;j++) cout<<"R";
		}
		cout<<"L";
	}
	return 0;
}

```

---

## 作者：Yujinhe469 (赞：3)

### 终于升金组了，~~再次~~特此纪念

## 题目分析

题目要求我们找到一组中途改变方向的次数尽量少的可行解，显然使用贪心是最合适的。

* 贪心：每次能不转向就不转向。

证明：若是在能不转向的节点转向，则必须再次转向以经过该节点后的所需节点，而不转向直至最后再转向也可以经过所需经过的节点，且一定不劣于转向的解，故贪心正确。

* 什么时候必须转向？

分两种可能性：

1.走到了边缘，即该节点方向的下一节点剩余经过的次数为 $0$ 。

2.向左走时遇到某节点剩余经过次数为 $1$ （除非右边所有节点的经过次数皆为 $0$ ），必须转向，否则就无法再次经过右边的节点。

* 时间复杂度是 $O(\sum_{i=0}^{n-1} A[i])$，因为每次经过，当前节点的所需经过次数就会减 $1$ ，并且每次操作是 $O(1)$ 的。

### AC代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100009;
int n,a[N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int i=1,d=1;
	a[1]--;
	cout<<"R";
	while(1){
		if(i==0){
			if(a[1]==0) break;
			cout<<"R";
			a[1]--;
			d=1;
			i++;
		}
		else if(i==n){
			cout<<"L";
			a[n]--;
			d=0;
			i--;
		}
		else if(d==0){
			if(a[i]==1){
				if(a[i+1]==0){
					cout<<"L";
					a[i]--;
					i--;
				}
				else{
					cout<<"R";
					i++;
					a[i]--;
					d=1;
				}
			}
			else{
				cout<<"L";
				a[i]--;
				i--;
			}
		}
		else if(d==1){
			if(a[i+1]==0){
				cout<<"L";
				a[i]--;
				i--;
				d=0;
			}
			else{
				cout<<"R";
				i++;
				a[i]--;
			}
		}
	}
	return 0;
}

```

代码中 $d$ 记录方向， $0$ 表示向左， $1$ 表示向右。

---

## 作者：__11jiang08__ (赞：1)

### 思路

本题要求的是一个行走方式使转弯次数最少，那么可以考虑贪心。

贪心原则：尽量保持原来的方向。如果当前方向是右，那么除非已经在最后一格，就向右走。如果当前方向是左，那么要考虑能不能走回来。如果剩余行走次数 $\geq3$，那么肯定能走回来，就可以往左走。否则要判断右边是否还有没走的，如果没有则往左走，反之往右走。

判断右边还有没有没走的可以用树状数组求和。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
int n;
ll cnt[100009],bit[100009];
ll lsb(int x){
	return x&(-x);
}
ll psq(int x){
	int res=0;
	while(x){
		res+=bit[x];
		x-=lsb(x);
	}
	return res;
}
void add(int x,int p){
	while(x<=n){
		bit[x]+=p;
		x+=lsb(x);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)  cin>>cnt[i];
	for(int i=1;i<=n;i++)  add(i,cnt[i]);
	int pos=1;
	char dir='R';
	while(1){
		if(dir=='R'){
			if(pos!=n+1&&cnt[pos]>0){
				cout<<'R';
				pos++,cnt[pos-1]--;
				add(pos-1,-1);
			}
			else{
				cout<<'L';
				dir='L';
				pos--,cnt[pos]--;
				add(pos,-1);
			}
		}
		else{
			if(cnt[pos-1]>=3){
				cout<<'L';
				pos--,cnt[pos]--;
				add(pos,-1);
			}
			else{
				if(psq(n)-psq(pos-1)>0){
					cout<<'R';
					dir='R';
					pos++,cnt[pos-1]--;
					add(pos-1,-1);
				}
				else{
					cout<<'L';
					pos--,cnt[pos]--;
					add(pos,-1);
				}
			}
		}
		if(pos==1&&cnt[pos]==0)  break;
	}
	return 0;
}
```


---

