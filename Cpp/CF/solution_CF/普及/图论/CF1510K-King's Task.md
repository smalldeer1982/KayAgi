# King's Task

## 题目描述

The brave Knight came to the King and asked permission to marry the princess. The King knew that the Knight was brave, but he also wanted to know if he was smart enough. So he asked him to solve the following task.

There is a permutation $ p_i $ of numbers from 1 to $ 2n $ . You can make two types of operations.

1. Swap $ p_1 $ and $ p_2 $ , $ p_3 $ and $ p_4 $ , ..., $ p_{2n-1} $ and $ p_{2n} $ .
2. Swap $ p_1 $ and $ p_{n+1} $ , $ p_2 $ and $ p_{n+2} $ , ..., $ p_{n} $ and $ p_{2n} $ .

The task is to find the minimal number of operations required to sort the given permutation.

The Knight was not that smart actually, but quite charming, so the princess asks you to help him to solve the King's task.

## 说明/提示

In the first example, you can sort the permutation in three operations:

1. Make operation 1: $ 3, 6, 5, 2, 1, 4 $ .
2. Make operation 2: $ 2, 1, 4, 3, 6, 5 $ .
3. Make operation 1: $ 1, 2, 3, 4, 5, 6 $ .

## 样例 #1

### 输入

```
3
6 3 2 5 4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
2
3 4 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 2 3 4 5 6 7 8```

### 输出

```
0```

# 题解

## 作者：unputdownable (赞：2)

[原题链接](https://www.luogu.com.cn/problem/CF1510K)

首先想到把 $2n$ 个数摆成一个 $2 \times n$ 的矩阵，可以发现操作 $2$ 就相当于交换两行。

而操作 $1$ 需要分类讨论：当 $n$ 是偶数时，只在行内交换；当 $n$ 是奇数时，会有一组跨行的交换。

--------

先讨论 $n$ 是偶数时的情况：

我们把可以交换的两组数连上线：

![](https://cdn.luogu.com.cn/upload/image_hosting/smw8ld8v.png)

所以只有每一组的 $4$ 个数可以交换，而 $4$ 个数时只有 $4$ 种情况，即不变，交换上下，交换左右，交换对角。

注意所有组内的操作必须是同步的，所以需要判断每个值是否在组内，在判断每组 $4$ 个数是否大小顺序相同，最后对第一组特判即可。

--------

接下来看 $n$ 是奇数的情况：

同样是连上线：

![](https://cdn.luogu.com.cn/upload/image_hosting/jy6x3maj.png)

可以看出 $2n$ 个数共同连成一个环：

![](https://cdn.luogu.com.cn/upload/image_hosting/hbkt6two.png)

黑白染色分组，可以得到两组数：

![](https://cdn.luogu.com.cn/upload/image_hosting/ni6q91ga.png)

可以发现操作 $1$ 相当于把上面那一组向左移一位，同时将下面那一组向右移一位，操作 $2$ 则刚好相反。

所以每一组中间的相对位置是不变的。

于是每一组中数的顺序应按照上图这种顺序排，并且两组数距离正确位置的距离应相等。

选择数字 $1$ 和 $2$ 为定位点，判断一下它们在环上需要移动的距离是否相等即可。

不要忘记特判另一个方向的距离更小的情况。

-------

Code：

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(void) {
	register int x=0;
	register short sgn=1;
	register char c=getchar();
	while(c<48||57<c) {
		if(c==45) sgn=0;
		c=getchar();
	}
	while(47<c&&c<58) {
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return sgn? x:-x;
}
inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
int BAns,WAns,Ans;
int Map[1005][2],srl[2005];
int Aap[1005][2],Arl[2005];
int k[100],pos1,pos2;
inline void work0(void) {
    for(register int i=3; i<n; i+=2) {
        if(!((Map[i][0]-Map[1][0])==(Map[i+1][0]-Map[2][0])&&(Map[i][1]-Map[1][1])==(Map[i+1][1]-Map[2][1])&&(Map[i+1][0]-Map[2][0])==(Map[i][1]-Map[1][1]))) {
            puts("-1");
            return ;
        }
    }
    for(register int i=1; i<n; i+=2) {
        k[0]=Map[i][0],k[1]=Map[i+1][0],k[2]=Map[i][1],k[3]=Map[i+1][1];
        sort(k,k+4);
        if(k[0]==i&&k[1]==i+1&&k[2]==i+n&&k[3]==i+n+1) continue;
        puts("-1");
        return ;
    }
    if(Map[1][0]==1) {
        if(Map[1][1]==n+1&&Map[2][0]==2&&Map[2][1]==n+2) puts("0");
        else puts("-1");
    }
    if(Map[2][0]==1) {
        if(Map[2][1]==n+1&&Map[1][0]==2&&Map[1][1]==n+2) puts("1");
        else puts("-1");
    }
    if(Map[1][1]==1) {
        if(Map[1][0]==n+1&&Map[2][1]==2&&Map[2][0]==n+2) puts("1");
        else puts("-1");
    }
    if(Map[2][1]==1) {
        if(Map[2][0]==n+1&&Map[1][1]==2&&Map[1][0]==n+2) puts("2");
        else puts("-1");
    }
    return ;
RE:
    puts("-1");
    return ;
}
inline void work1(void) {
    for(register int i=1; i<n; i+=2) {
        srl[(i-1)*2+1]=Map[i  ][0];
        srl[(i-1)*2+2]=Map[i+1][0];
        srl[(i-1)*2+3]=Map[i+1][1];
        srl[(i-1)*2+4]=Map[i+2][1];
    }
    srl[2*n-1]=Map[n][0];
    srl[2*n-0]=Map[1][1];
    for(register int i=1; i<n; i+=2) {
        Arl[(i-1)*2+1]=Aap[i  ][0];
        Arl[(i-1)*2+2]=Aap[i+1][0];
        Arl[(i-1)*2+3]=Aap[i+1][1];
        Arl[(i-1)*2+4]=Aap[i+2][1];
    }
    Arl[2*n-1]=Aap[n][0];
    Arl[2*n-0]=Aap[1][1];
    for(register int i=1; i<=2*n; ++i) if(srl[i]==1) {
        pos1=i;
        break;
    }
    for(register int i=1; i<=2*n; ++i) if(srl[i]==2) {
        pos2=i;
        break;
    }
    int _p1=pos1,__p1=1;
    int _p2=pos2,__p2=2;
    for(register int i=1; i<n; ++i) {
        _p1+=2,_p2+=2,__p1+=2,__p2+=2;
        if(_p1>2*n) _p1-=2*n;
        if(_p2>2*n) _p2-=2*n;
        if(__p1>2*n) __p1-=2*n;
        if(__p2>2*n) __p2-=2*n;
        if(srl[_p1]!=Arl[__p1]||srl[_p2]!=Arl[__p2]) {
            puts("-1");
            return ;
        }
    }
    int A1=pos1-1;
    int A2=pos2-2;
    if(A2<0) A2+=2*n;
    int B1=2*n-A1;
    int B2=2*n-A2;
    if(A1==0&&A2==0) write(0),puts("");
    else if(A1==B2)  write(min(A1,B1)),puts("");
    else             puts("-1"); 
}
signed main() {
	n=read();
    for(register int i=1; i<=n; ++i) Map[i][0]=read();
    for(register int i=1; i<=n; ++i) Map[i][1]=read();
    if(n==1) {
        if(Map[1][0]==1) puts("0");
        else puts("1");
        return 0;
    }
    for(register int i=1; i<=n; ++i) Aap[i][0]=i;
    for(register int i=1; i<=n; ++i) Aap[i][1]=i+n;
    if(n&1) work1();
    else    work0();
	return 0;
}
```

---

## 作者：zsyzsy_2012 (赞：1)

一道比较清新的思维题。

第一步，观察两个操作的特点，容易得出：任意一个操作执行偶数次是没有意义的，整个数组将会变回原样。所以我们可以想到最后作为答案的操作方式一定是交替的，例如（第一个 第二个 第一个 第二个 ……）或者（第二个 第一个 第二个 第一个……）

上述分析其实是非常关键的。有了它，我们只需讨论首位是哪种操作，然后依次交替进行操作，如果发现成功了就立刻跳出循环。最后只需对两个结果求一个最小值，就可以了。我们可以证明在进行有限次后必然会和原数组完全相同，这就意味着无解，直接按无解判断即可（这一段是在防死循环）。

最后给出代码，注释的比较清楚了。

代码：

```
#include <bits/stdc++.h>
#define N 2010
using namespace std ;
int n , a[N] , b[N] , c[N] ;
bool same(int s[] , int t[]) {
	for(int i = 1 ; i <= 2 * n ; i++) {
		if(s[i] != t[i]) {
			return false ;
		}
	}//判断两个数组是否完全相同
	return true ;
}
int main() {
	scanf("%d" , &n) ;
	for(int i = 1 ; i <= 2 * n ; i++) {
		scanf("%d" , &a[i]) ;
		b[i] = c[i] = a[i] ;
	}
	bool f = true ;
	for(int i = 1 ; i < 2 * n ; i++) {
		if(a[i] > a[i + 1]) {
			f = false ;
			break ;
		}
	}
	if(f) {
		puts("0") ;
		return 0 ;
	}
	int x = 1145141919 , y = 1145141919 , id = 1 , s = 0 ;
   //id表示当前是哪一种操作
   //初始值设为无限大
	while(!same(a , b) || !s) {
		s++ ;//第一种模式
		if(id) {
			for(int i = 1 ; i < 2 * n ; i += 2) {
				swap(b[i] , b[i + 1]) ;
			}
		}
		else {
			for(int i = 1 ; i <= n ; i++) {
				swap(b[i] , b[n + i]) ;
			}
		}
		id ^= 1 ;
		bool g = true ;
		for(int i = 1 ; i < 2 * n ; i++) {
			if(b[i] > b[i + 1]) {
				g = false ;
				break ;
			}//如果OK就立刻break
		}
		if(g) {
			x = s ;
			break ;
		}
	}
	id = s = 0 ;
	while(!same(a , c) || !s) {
		s++ ;//第二种模式
		if(id) {
			for(int i = 1 ; i < 2 * n ; i += 2) {
				swap(c[i] , c[i + 1]) ;
			}
		}
		else {
			for(int i = 1 ; i <= n ; i++) {
				swap(c[i] , c[n + i]) ;
			}
		}
		id ^= 1 ;
		bool g = true ;
		for(int i = 1 ; i < 2 * n ; i++) {
			if(c[i] > c[i + 1]) {
				g = false ;
				break ;
			}//同理
		}
		if(g) {
			y = s ;
			break ;
		}
	}
	int ans = min(x , y) ;
    //特判输出
	if(ans != 1145141919) printf("%d" , ans) ;
	else puts("-1") ;
	return 0 ;
}
```


---

## 作者：Ak_hjc_using (赞：0)

这道题目要求我们对长度为 $2n$ 的数列，通过两种操作使序列变为升序排列。我们需要找到最小的操作次数。首先，我们来分析题目的操作和思路。

### 大致题意

给定长度为 $2n$ 的数列，允许进行两种操作：

1. **操作一**：对于所有 $1 \leq k \leq n$，将数列的第 $2k$ 位和第 $2k-1$ 位交换。
2. **操作二**：对于所有 $1 \leq k \leq n$，将数列的第 $k$ 位和第 $k+n$ 位交换。

我们需要找到最少的操作次数使得这个数列变为递增有序。
### 思路
我们先来分析操作
- **操作一**：该操作可以交换每对相邻的元素。这实际上是将每两个相邻元素对调，但仅限于偶数位和奇数位。
- **操作二**：该操作将前半部分和后半部分的对应元素进行交换，即将位置 $1 \leq k \leq n$ 与 $k+n$ 的元素对调。

通过这两种操作，我们可以将数组中的元素逐步调整成递增有序。问题变成：我们如何通过这些操作，最小化操作次数。

所以这时，我们就可以使用贪心算法。

在贪心算法中，我们考虑如何尽量减少不必要的操作。我们可以先尝试按顺序执行操作一和操作二，看是否能够快速将数组变为有序。贪心的原则是每次进行能最大化减少无序对的操作。

不放代码。

---

## 作者：xuan_gong_dong (赞：0)

## 题面
[King's Task](https://www.luogu.com.cn/problem/CF1510K)
## 分析
看到题目要注意到两个点：

1. $n\le 1000$。
2. 容易发现如果执行连续两个操作，那等于不执行（抵消了），所有操作必须得交替执行。

直接暴搜即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[2010];
int Min=0x7f7f7f7f;
bool check(){
	for(int i=1;i<=n*2;i++)
		if(a[i]!=i)return 0;
	return 1;
}
void dfs(int step,int flag){
	if(step>n||step>=Min)
		return;
	if(check()){
		Min=min(Min,step);
		return;
	}
	if(flag){
		if(step&1){
			for(int i=1;i<=n;i++)
				swap(a[i],a[i+n]);
			dfs(step+1,flag);
			for(int i=1;i<=n;i++)
				swap(a[i],a[i+n]);
			return;				
		}
		for(int i=1;i<=n;i++)
			swap(a[i*2-1],a[i*2]);
		dfs(step+1,flag);
		for(int i=1;i<=n;i++)
			swap(a[i*2-1],a[i*2]);
	}
	else	{
		if((step&1)==0){
			for(int i=1;i<=n;i++)
				swap(a[i],a[i+n]);
			dfs(step+1,flag);
			for(int i=1;i<=n;i++)
				swap(a[i],a[i+n]);
			return;				
		}
		for(int i=1;i<=n;i++)
			swap(a[i*2-1],a[i*2]);
		dfs(step+1,flag);
		for(int i=1;i<=n;i++)
			swap(a[i*2-1],a[i*2]);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)
		scanf("%d",&a[i]);
	dfs(0,1);
	dfs(0,0);
	int hys=-1;
	printf("%d",Min==0x7f7f7f7f?hys:Min);
	return 0;
}
```


---

