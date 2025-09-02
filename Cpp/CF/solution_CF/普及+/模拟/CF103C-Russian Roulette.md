# Russian Roulette

## 题目描述

After all the events in Orlando we all know, Sasha and Roma decided to find out who is still the team's biggest loser. Thankfully, Masha found somewhere a revolver with a rotating cylinder of $ n $ bullet slots able to contain exactly $ k $ bullets, now the boys have a chance to resolve the problem once and for all.

Sasha selects any $ k $ out of $ n $ slots he wishes and puts bullets there. Roma spins the cylinder so that every of $ n $ possible cylinder's shifts is equiprobable. Then the game starts, the players take turns, Sasha starts: he puts the gun to his head and shoots. If there was no bullet in front of the trigger, the cylinder shifts by one position and the weapon is given to Roma for make the same move. The game continues until someone is shot, the survivor is the winner.

Sasha does not want to lose, so he must choose slots for bullets in such a way as to minimize the probability of its own loss. Of all the possible variant he wants to select the lexicographically minimal one, where an empty slot is lexicographically less than a charged one.

More formally, the cylinder of $ n $ bullet slots able to contain $ k $ bullets can be represented as a string of $ n $ characters. Exactly $ k $ of them are "X" (charged slots) and the others are "." (uncharged slots).

Let us describe the process of a shot. Suppose that the trigger is in front of the first character of the string (the first slot). If a shot doesn't kill anyone and the cylinder shifts, then the string shifts left. So the first character becomes the last one, the second character becomes the first one, and so on. But the trigger doesn't move. It will be in front of the first character of the resulting string.

Among all the strings that give the minimal probability of loss, Sasha choose the lexicographically minimal one. According to this very string, he charges the gun. You have to help Sasha to charge the gun. For that, each $ x_{i} $ query must be answered: is there a bullet in the positions $ x_{i} $ ?

## 说明/提示

The lexicographical comparison of is performed by the < operator in modern programming languages. The $ a $ string is lexicographically less that the $ b $ string, if there exists such $ i $ ( $ 1<=i<=n $ ), that $ a_{i}&lt;b_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ a_{j}=b_{j} $ .

## 样例 #1

### 输入

```
3 1 3
1
2
3
```

### 输出

```
..X```

## 样例 #2

### 输入

```
6 3 6
1
2
3
4
5
6
```

### 输出

```
.X.X.X```

## 样例 #3

### 输入

```
5 2 5
1
2
3
4
5
```

### 输出

```
...XX```

# 题解

## 作者：smyslenny (赞：3)

**CF103C Russian Roulette**


[题目传送门](https://www.luogu.com.cn/problem/CF103C)


首先分析题意，我们可以得出三个性质：

   1. 如果最大程度上保证第一个人安全的话，**第一个位置不要放子弹**，不然上来就死了(除非所有的位置都要放子弹)。
	
   2. 让第二个人死的快点，那么需要**隔一个放一个子弹** (从第二个位置开始放)。
	
   3. 如果 $k>0$ ，**最后一个位置一定放子弹**，因为要保证字典序最小。

当当前的弹槽数为奇数时，由于性质3，易知最后一位一定是子弹，我们把最后一位删去，转换成偶数个，与偶数的情况一起讨论。

然后我们考虑两种情况：

- 子弹数 $>$ 弹槽数的一半

	由性质2，可知，从第二个个位置开始，每隔一个位置都有一个子弹，也就是偶数位置一定有子弹。非偶数位置，由于子弹数 $>$ 弹槽数的一半，肯定有的位置有子弹。为了保证字典序最小，剩余的子弹一定是从后往前填的，所以我们可以筛去偶数的情况进行计算。
    
    ![图1](https://cdn.luogu.com.cn/upload/image_hosting/d4ptklu8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
    
    如上图，假设我们 $k=5$ ,筛去偶数，给我们的弹槽重新编个号。
    
    因为已经使用了 $4$ 颗子弹，剩下那颗子弹一定在最后一个位置。
    ![图2](https://cdn.luogu.com.cn/upload/image_hosting/hmi65p7w.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
    
    因为我们已经筛去了偶数，所以说剩下的子弹就从后往前放就可以啦，判断一下我们要找的位置是否在后面的子弹序列里，就完成了。
    
    

- 子弹数 $\leqslant$ 弹槽个数的一半

	此时弹槽中的偶数位可能会填不满，所以我们不能按照之前那样先把偶数筛去，但是我们可以发现，奇数位置一定是没有子弹的，我们就可以按照之前的思路，把奇数筛去，子弹同样也是从后往前排的，判断查询位置是否在后面的子弹序列里就可以了。
    如下图， $k=3$
    
    ![图3](https://cdn.luogu.com.cn/upload/image_hosting/tv927es3.png?x-oss-process=image/resize,m_lfit,h_170,w_225 )

然后记得开 $long \ long $ ,不然亲测只能过五个点。

```c
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <cstdlib>

#define int long long
#define INF 0x3f3f3f3f

using namespace std;
int n,k,q; 
int read()
{
	register int x=0,y=1;
	register char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') y=0;c=getchar();}
	while(c>='0'&&c<='9') { x=x*10+(c^48),c=getchar();}
	return y?x:-x;
}
bool check(int x,int n,int k)
{
	if(n&1) { //子弹隔一个放一个最优，如果是奇数，且 k > n/2 那么一定有两个相同的弹夹，
		if(x==n && k) //如果是最后一位 ,当前还有子弹，最后一位一定是子弹 
			return true;
		n--;//不是最后一位，最后一位放子弹字典序最小，先排除了
		k--; 
	}
	if(k-n/2>0)//子弹数 > 弹夹容量一半 一定有三个相邻的位置装子弹 
	{
		if(x%2==0) //偶数一定有子弹 
			return true;
		k-=n/2;//减去使用了的子弹 
		x=x/2+1;//重新编号 
		k=n/2-k;//剩下子弹从后依次排列，找到子弹排列的最前面一个的前一个位置 
		if(x>k) return true;//在后面的子弹序列里 
		return false;
	}
	else
	{
		if(x&1) return false;//奇数位置，一定没有子弹
		x=x/2;//筛去奇数，重新编号 
		k=n/2-k;//子弹序列前端的上一位置 
		if(x>k) return true;
		return false;
	}
}
signed main()
{
	n=read(),k=read(),q=read();
	while(q--)
	{
		int pot=read();
		if(check(pot,n,k))
		printf("X");
		else printf(".");
	}
	return 0;
}

```


---

## 作者：_Violet_Evergarden (赞：2)

题解有些空缺，来发一发。

# 思路

首先我们仔细阅读题目，要想让自己赢的概率最大，那么我们肯定可以发现一个 $.$ 后接着一个 $X$ 才能让概率最大，可是当 $n$ 是奇数时，我们从最后开始一个隔一个就不是字典序最小的了，因为这时我们把一个 $X$ 放在最后面在进行刚才那个策略且将它从后往前开始填一个 $X$ 隔一个 $.$ 就可以了。然而这只是在大脑中的模拟过程，我们注意到 $n$ 的范围很大，所以我们不进行预处理，而是在它询问的时候直接输出答案即可。

# 代码
 ```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long k;
long long o;
long long flag;
int main()
{
	cin>>n>>k>>m;
	if(k==0){
		while(m--){
			cout<<".";
		}
		return 0;
	}
	if(n%2==1){
		n--;
		k--;
		flag=1;
	}
	for(int i=1;i<=m;i++){
		cin>>o;
		if(o==n+1){
			cout<<"X";
			continue;
		}
		if(o%2==0){
			if(k>=(n-o)/2+1){
				cout<<"X";
			}
			else{
				cout<<".";
			}
		}
		else{
			if(k-n/2>=(n-o+1)/2){
				cout<<"X";
			}
			else{
				cout<<".";
			}
		}
	}
	return 0;
}
```


---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
两个傻瓜玩俄罗斯轮盘（轮流开枪，直到一方死亡），$n$ 个位置里有 $k$ 个子弹，请你填装这 $k$ 个子弹，使先开枪者死亡的概率最小，在满足该条件的情况下最小化方案的字典序（空弹夹字典序更小）。  
每次询问位置 $x$ 是否装有子弹。  
$k\le n\le10^{18}$

## $\text{Solution}$
有点小细节的一道题。  
（样例真心良心）  
有子弹的地方先手必然死，所以我们就是让空弹夹先手死的尽可能少就行了。  

通过观察样例二可以发现，从后往前，隔一个放一颗子弹是一种很好的方案。  
但是观察样例三可以发现，在刚才那种构造的基础上，有的时候可以把一枚最前面的子弹挪到后面挨着放，死亡概率不变，但字典序更小。  
具体的，这种情况是在前面空出的连续空白段长度为偶数时成立，这时候前面去掉一个必胜位置的数量不变。  

还有一些其它边边角角的情况，在 $2k\ge n$ 时，后面挨着放前面隔着放即可；还要注意 $n=1$ 的时候不能“把最前面的一个挪到后面挨着放”（因为一共就只有一个）
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
#define ll long long
#define ui unsigned int
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}  
  while (isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}    
  return x*f;
}

ll n,k,m;
int op;
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();k=read();m=read();
  ll pl(0);
  if(k*2>=n){
    op=1;pl=2*(n-k);
  }
  else if((n-2*k)%2==0||k<=1){
    op=2;pl=n-2*k;
  }
  else{
    op=3;pl=2*k-2;
  }
  for(int i=1;i<=m;i++){
    ll x=read();
    if(op==1){
      if(x>pl||(x&1)==0) printf("X");
      else printf(".");
    }
    else if(op==2){
      if(x<=pl||((x-pl)&1)) printf(".");
      else printf("X");
    }
    else{
      x=n-x+1;
      if(x<=2||(x<=pl&&x%2==0)) printf("X");
      else printf(".");
    }
  }
  return 0;
}
/*
*/

```


---

