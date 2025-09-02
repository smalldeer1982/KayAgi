# Bottom-Tier Reversals

## 题目描述

You have a permutation: an array $ a = [a_1, a_2, \ldots, a_n] $ of distinct integers from $ 1 $ to $ n $ . The length of the permutation $ n $ is odd.

You need to sort the permutation in increasing order.

In one step, you can choose any prefix of the permutation with an odd length and reverse it. Formally, if $ a = [a_1, a_2, \ldots, a_n] $ , you can choose any odd integer $ p $ between $ 1 $ and $ n $ , inclusive, and set $ a $ to $ [a_p, a_{p-1}, \ldots, a_1, a_{p+1}, a_{p+2}, \ldots, a_n] $ .

Find a way to sort $ a $ using no more than $ \frac{5n}{2} $ reversals of the above kind, or determine that such a way doesn't exist. The number of reversals doesn't have to be minimized.

## 说明/提示

In the first test case, the permutation is already sorted. Any even number of reversals of the length $ 3 $ prefix doesn't change that fact.

In the second test case, after reversing the prefix of length $ 3 $ the permutation will change to $ [5, 4, 3, 2, 1] $ , and then after reversing the prefix of length $ 5 $ the permutation will change to $ [1, 2, 3, 4, 5] $ .

In the third test case, it's impossible to sort the permutation.

## 样例 #1

### 输入

```
3
3
1 2 3
5
3 4 5 2 1
3
2 1 3```

### 输出

```
4
3 3 3 3
2
3 5
-1```

# 题解

## 作者：gyh20 (赞：10)

由于只能翻转奇数的前缀，所以每个数最终对应的位置的奇偶性不会改变。

若存在一个数的奇偶性与所在位置的奇偶性不同，一定不合法。

否则，一定合法，可以通过如下的构造证明。

发现对于偶数下标，到达其应该到达的位置时，后面一个数的大小一定其数值 $+1$。

而我们无法翻偶数前缀，相当于这两个数我们是一起返过来的，我们可以将数两两打包，并依次构造使得末尾的两个数变为 $n-1$ 和 $n$，然后递归处理前面的问题。

$\dfrac 5 2$ 的限制其实是对于任意一次将数列末尾变为 $n-1$ 和 $n$ 的操作不能执行超过 $5$ 次翻转前缀。

对着 $5$ 次构造，令 $pos_i$ 表示值为 $i$ 的数的位置，进行如下的翻转，均用 $[l,r]$ 代替翻转 $[l,r]$：

$1.[1,pos_i]$，将 $i$ 换到第一个。

$2.[1,pos_{i-1}-1]$，将 $i$ 换到 $i-1$ 前一个。

$3.[1,pos_{i-1}+1]$，将 $i$ 换到位置 $3$，$i-1$ 换到位置 $2$。

$4.[1,3]$，将 $i$ 换到位置 $1$，$i-1$ 换到位置 $2$。

$5.[1,i]$，将 $i$ 换到 $i$，$i-1$ 换到 $i-1$。

这样刚好是满足条件的：

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,a[200002],pos[200002],X[200002],Y[200002],tot;
inline void rev(re int l,re int r){
	reverse(a+l,a+r+1);X[++tot]=r;
	for(re int i=l;i<=r;++i)pos[a[i]]=i;
}
int main(){
	int t=read();
	while(t--){
		n=read(),tot=0;
		re bool ia=1;
		for(re int i=1;i<=n;++i)pos[a[i]=read()]=i;
		for(re int i=1;i<=n;i+=2)if(!(pos[i]&1)){ia=0;break;}
		if(!ia){
			puts("-1");
			continue;
		}
		for(re int i=n;i>1;i-=2){
			rev(1,pos[i]),rev(1,pos[i-1]-1);
			rev(1,pos[i-1]+1),rev(1,3);
			rev(1,i);
		}
		printf("%d\n",tot);
		for(re int i=1;i<=tot;++i)printf("%d ",X[i]);
		puts("");
		
	}
}

```


---

## 作者：Miraik (赞：4)

首先判断无解的情况。显然因为 $p$ 只能取奇数，因此 $a_i$ 的奇偶性是恒定的。因此只要给出的 $a_i$ 与 $i$ 奇偶性不同，直接输出 $-1$ 即可。

然后发现，对于每次选择 $p$ 的操作，$[a_{p+1},a_{p+2},\cdots a_n]$ 这个区间是不变的。因此我们考虑从后向前处理。

又因为题目要求操作次数小于等于 $\frac{5n}{2}$，自然想到通过 $5$ 次操作将 $2$ 个数归位。

假设**当前尚未进行归位操作的最大数字**为 $k$，显然此时 $[a_{k+1},a_{k+2},\cdots a_n]$ 已经归位，我们不再考虑它们。考虑如何将 $k$ 与 $k-1$ 归位。

发现如果能让 $a_1=k$ 且 $a_2=k-1$，那么只需要进行一次操作 $p=k$ 的操作即可将 $k$ 与 $k-1$ 归位。 

首先找到当前 $k$ 当前所处位置 $x$，显然 $x$ 是奇数。

我们先进行一次操作 $p=x$，然后就有 $a_1=k$ 了。

然后我们在找到当前 $k-1$ 当前所处位置 $y$，显然 $y$ 是偶数。

这时我们发现我们还能进行 $4$ 次操作，于是有了这个巧妙的方案：

进行操作 $p=y-1$，序列变为 $[a_{y-1},a_{y-2},...,a_3,k,k-1,a_{y+1},a_{y+2},...,a_{k}]$。

进行操作 $p=y+1$，序列变为 $[a_{y+1},k-1,k,a_3,...,a_{y-2},a_{y-1},a_{y+2},...,a_{k}]$。

这时我们发现 $a_2=k-1$，$a_3=k$。

然后我们进行操作 $p=3$，序列变为 $[k,k-1,a_{y+1},a_3,...,a_{y-2},a_{y-1},a_{y+2},...,a_{k}]$。

此时我们再进行操作 $p=k$，$k$ 与 $k-1$ 就归位了！

至此，我们成功通过 $5$ 次操作将 $2$ 个数归位。

显然将上述操作重复 $\frac{n-1}{2}$ 次，就可以使得 $n$ 个数全部归位。

总操作次数 $\frac{5(n-1)}{2}$。

代码：

```cpp
/*
+   +   +   +    +++     +++++     ++++
 + +     + +      +         +      +   +
  +       +       +        +       +   +
 + +      +       +       +        +   +
+   +     +      +++     +++++     ++++
*/
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int N=100005;
const int inf=1<<30;
const ll inff=1ll<<60;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,a[N],ans[N],cnt;
void xyizd_is_stupid(int pre){
	for(int i=1,j=pre;i<j;i++,j--)
	    a[i]^=a[j]^=a[i]^=a[j];
	ans[++cnt]=pre; 
}
void solve(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)
	    if((a[i]+i)%2){
	    	puts("-1");
	    	return;
	    }
	cnt=0;
	while(n>=3){
		int pos_n,pos_m;
		for(int i=1;i<=n;i++)
		    if(a[i]==n)pos_n=i;
		xyizd_is_stupid(pos_n);
		for(int i=1;i<=n;i++)
		    if(a[i]==n-1)pos_m=i;
		xyizd_is_stupid(pos_m-1);
		xyizd_is_stupid(pos_m+1);
		xyizd_is_stupid(3);
		xyizd_is_stupid(n);
		n-=2;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)printf("%d ",ans[i]);
	puts("");
}
int main(){int tests=1;tests=read();//
while(tests--){
	solve();
}	return 0;
}
/*
1
5
3 4 1 2 5
*/

```


---

## 作者：Lice (赞：3)

### Description

你有一个 $n$ 长度的排列，$n$ 为奇数。你可以进行若干次操作，每次翻转一个前缀，要求前缀长度为偶数。求能否在 $5n/2$ 次操作内完成排列的升序排序，若能则输出方案。

### Constraints

$3\le n\le 2021$

### Solution

妙妙题

观察次数限制是 $5n/2$​，不妨猜想一波每确定一对数花费 $5$​ 次操作。由于我们每次翻转一个前缀，那么对于较大的数理应优先处理，因为固定了的大数必然在后面，不会为之后的操作所影响。

还有一个限制就是，一次操作只能对偶数长度翻转，那么对于无解的判断：对于位置 $i$，其上的数值 $x$ 与 $i$ 的奇偶性不同。若存在如此的 $i$ 则直接无解。

考虑当前要操作一对数字 $k, k-1$​​​，而 $k+1\sim n$​​​ 都已在对应的 $k+1\sim n$​​​ 位置上。接下来的方向是让 $k-1, k$​​​ （注意左右顺序）贴一块，这样就能一口气转到前端，然后直接目标要求位置上。可以发现一个小套路就是扔到开头，然后想到哪就到哪。

考虑如何贴一块。还是套路地先找到 $k$，转到头上，然后找到 $k-1$ 让 $k$ 转到其前一个。不是先找 $k-1$ 的原因就是因为偶数长度翻转的限制。贴上之后，由于那个偶长限制我们故意空一个再转到前面，可以发现必然可以做到空一格，反之就是在 $k$ 转到前面之前 $k-1$ 是第一个，而 $k-1$ 为偶数，是上面的无解情况。剩下还有两次操作：翻转前 $3$ 个，最后转到 $k-1,k$ 位置上，一共 $5$ 次。

显然最后操作下来 $1$ 一定在第一个位置，于是做完了。

### Code

膜拜 xyf007

```cpp
#include <bits/stdc++.h>
  
const int N = 1e4 + 5;
int n, a[N];
  
void solve() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) {
    if ((i & 1) && !(a[i] & 1)) { std::cout << "-1\n"; return; }
    if (!(i & 1) && (a[i] & 1)) { std::cout << "-1\n"; return; }
  }
  
  std::vector<int> ans;
  auto apply = [&](int x) {
    ans.push_back(x);
    std::reverse(a + 1, a + 1 + x);
  };
  
  for (int i = n; i > 2; i -= 2) {
    int eq = 1;
    for (; eq <= i; ++eq)
      if (a[eq] == i) break;
    apply(eq);
  
    for (eq = 0; eq <= i; ++eq)
      if (a[eq] == i - 1) break;
    apply(eq - 1), apply(eq + 1);
    apply(3), apply(i);
  }
  
  std::cout << ans.size() << '\n';
  for (int x : ans) std::cout << x << ' ';
  std::cout << '\n';
}
  
signed main() {
  int T; std::cin >> T;
  while (T--) solve();
}
```

广告：https://www.cnblogs.com/-Wallace-/p/sol-cf-740.html

---

## 作者：zimujun (赞：1)

因为每次只能选择一段长度为奇数的前缀，因此每次翻转操作都不会改变原来位置所在数下标的奇偶性，因此如果在原序列中存在某个数的奇偶性与其初始下标的奇偶性不同则无解。

题目中保证 $n$ 是奇数，考虑将 $1$ 单独拿出来，然后两个数分一组，即 $\{2, 3\},\{4, 5\}, \cdots, \{n - 1, n\}$。那么想要把这个排列翻转为升序，就可以先把最后一组放到最后两个位置，然后就转化成了一个关于长度为 $n - 2$ 的排列的相同的问题。

可以按照如下方式构造排列，举个例子来说，初始排列：

$$1, 2, 3, {\color{red}6}, 5, 4, {\color{red}7}$$

这一轮操作的目标是将 $6, 7$ 放到最后两个位置，按照如下操作：

1. 将奇数（$7$）翻到最前面；

$${\color{red}7}, 4, 5, {\color{red}6}, 3, 2, 1$$

2. 将奇数翻到偶数（$6$）的上一位，因为数的奇偶性一定和下标的奇偶性相同，所以保证这些操作都是合法的；

$$5, 4, {\color{red}7}, {\color{red}6}, 3, 2, 1$$

3. 操作偶数的下一个位置（$3$），把偶数和奇数分别放在 $2, 3$ 位置上；

$$3, {\color{red}6}, {\color{red}7}, 4, 5, 2, 1$$

4. 操作奇数所在位置，使奇数和偶数分别在 $1, 2$ 位置上；

$${\color{red}7}, {\color{red}6}, 3, 4, 5, 2, 1$$

5. 操作整个排列，将两个数放到最后；

$$1, 2, 5, 4, 3, {\color{red}6}, {\color{red}7}$$

接下来对于剩下的 $1\sim 5$ （未标红）的排列执行相同操作即可。

可以证明这样操作一轮的总次数不会大于 $5$ 次，又两个数分了一组，因此总的操作次数不会大于 $5\lfloor\dfrac{n}{2}\rfloor$，代码也非常好写。

---

## 作者：Crab_Dave (赞：0)

## CF1558C 题解

vp的时候有点口胡地过了这题，回来捋一下思路。

+ ### 题意

  给你一个长为奇数 $n$ 的排列，你可以选择一个长为奇数 $x$ 的前缀并将其翻转，你的目标是将序列升序排列，要求输出一种操作数 $\le \frac{5n} 2$ 的方案，$3 \le n \le 2021$.

+ ### 思路

  首先注意到 $\frac {5n} 2$.

  为什么有 $\frac {} 2$ 呢，我们猜测这是枚举每一个奇数位置；

  为什么有 $\frac {5n} {}$ 呢，我们猜测枚举每个位置时我们要进行五次操作。

  那我们就来尝试胡这五条操作。

  在此之前我们考虑一下各种限制：

  1. 由于 $n$ 是奇数，那么实际上我们并没有办法枚举所有奇数位置因为会超过 $\frac {5n} 2$。所以我们要在枚举$\frac {n-1} 2$ 个位置时归位其他所有 $n-1$ 个数。
  2. 那么每次操作就要还原当前奇数位以后的所有数，最后剩下 $1$，也就是每次要把 $pos$ 和 $pos-1$ 归位。
  3. 并且每次尽量不对其他位置造成影响。
  4. 关于 $-1$：注意到每次交换后奇数位置的还是在奇数位置上，所以奇数位置不能是偶数，偶数部分不能是奇数。

  我们倒序处理整个序列，这样序列后面有序的部分可以忽略。

  以下我们设 $find(i)$ 表示 $i$ 这个数当前在的位置。

  考虑当前枚举到奇数位置 $i$：

  第一个操作肯定是把 $i$ 这个数找到并移到前端：`rev(find(i))`；

  接下来应该是找 $i-1$，但是这个数必然在偶数位，所以我们只能移动它两侧的数：`rev(find(i-1)-1),rev(find(i-1)+1)`。

  我们想想序列是怎样变化的：

  $\{i \dots [已经排好序的部分] \}$

  $\to \{ \dots i,i-1 \dots [已经排好序的部分] \}$

  $\to \{ x,i-1,i \dots [已经排好序的部分] \}$

  那剩下两步自然呼之欲出了：

  $\to \{ i,i-1 \dots [已经排好序的部分] \}$

  $\to \{ \dots i-1,i,[已经排好序的部分] \}$

  其实这里思路上应该先填最后一条，这条启发我们要将目标移到首端后翻转到后面。

  但是不管怎样，我们磕磕绊绊地胡出了一个构造方法。

+ ### 代码

  有不懂的部分还是看看代码吧：

  ```cpp
  n=read();rep(i,1,n)a[i]=read(),fl[i]=(a[i]^i)&1;
  int num=0;rep(i,1,n)num+=fl[i];
  if(num){puts("-1");return;}
  ans.clear();
  for(int i=n;i>1;i-=2){
      int x=find(i);
      ans.push_back(x);rep(j,1,x/2)swap(a[j],a[x-j+1]);
      x=find(i-1)-1;
      ans.push_back(x);rep(j,1,x/2)swap(a[j],a[x-j+1]);
      x=find(i-1)+1;
      ans.push_back(x);rep(j,1,x/2)swap(a[j],a[x-j+1]);
      x=3;
      ans.push_back(x);rep(j,1,x/2)swap(a[j],a[x-j+1]);
      x=i;
      ans.push_back(x);rep(j,1,x/2)swap(a[j],a[x-j+1]);
      //		rep(i,1,n)printf("%d ",a[i]);puts("");
  }
  printf("%d\n",ans.size());
  for(int x:ans)printf("%d ",x);puts("");
  ```

---

