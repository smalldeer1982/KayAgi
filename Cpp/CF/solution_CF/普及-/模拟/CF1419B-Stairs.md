# Stairs

## 题目描述

Jett is tired after destroying the town and she wants to have a rest. She likes high places, that's why for having a rest she wants to get high and she decided to craft staircases.

Staircase is a squared figure that consists of square cells. Each staircase consists of an arbitrary number of stairs. If a staircase has $ n $ stairs, then it is made of $ n $ columns, the first column is $ 1 $ cell high, the second column is $ 2 $ cells high, $ \ldots $ , the $ n $ -th column if $ n $ cells high. The lowest cells of all stairs must be in the same row.

A staircase with $ n $ stairs is called nice, if it may be covered by $ n $ disjoint squares made of cells. All squares should fully consist of cells of a staircase.

 This is how a nice covered staircase with $ 7 $ stairs looks like: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1419B/20e8f39717a3a82bb8f73bd6c4f499217c03a037.png)Find out the maximal number of different nice staircases, that can be built, using no more than $ x $ cells, in total. No cell can be used more than once.

## 说明/提示

In the first test case, it is possible to build only one staircase, that consists of $ 1 $ stair. It's nice. That's why the answer is $ 1 $ .

In the second test case, it is possible to build two different nice staircases: one consists of $ 1 $ stair, and another consists of $ 3 $ stairs. This will cost $ 7 $ cells. In this case, there is one cell left, but it is not possible to use it for building any nice staircases, that have not been built yet. That's why the answer is $ 2 $ .

In the third test case, it is possible to build only one of two nice staircases: with $ 1 $ stair or with $ 3 $ stairs. In the first case, there will be $ 5 $ cells left, that may be used only to build a staircase with $ 2 $ stairs. This staircase is not nice, and Jett only builds nice staircases. That's why in this case the answer is $ 1 $ . If Jett builds a staircase with $ 3 $ stairs, then there are no more cells left, so the answer is $ 1 $ again.

## 样例 #1

### 输入

```
4
1
8
6
1000000000000000000```

### 输出

```
1
2
1
30```

# 题解

## 作者：Chinese_zjc_ (赞：4)

先看哪些是好阶梯:

看样例图:

![样例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1419B/20e8f39717a3a82bb8f73bd6c4f499217c03a037.png)

红色正方形把整个阶梯分成了两个级数为 $ 3 $ 的阶梯,然后黄色正方形又把其分成了两个级数为 $ 1 $ 的阶梯.

于是我们提出假设,只有级数为 $ 2^n-1 $ 的阶梯才是好阶梯.

下面我们来证明这个结论:

证明:

先来证明一个结论:每个正方形都必须占到一个阶梯每层最左的方块.$(1)$

证明也很简单,每个正方形只有一个左上角的方块,只能占用一个最左方块,那么 $ x $ 级的阶梯必定至少需要 $ x $ 个正方形才能填充完.

当级数为 $ 2^1-1 $ 时,显然是好阶梯.

当级数为 $ 2^n-1(n>1) $ 的情况,我们必定可以以阶梯右下角为正方形右下角,放置一个最大的正方形使其分成两部分,两部分的级数均为 $ 2^{n-1}-1 $ ,而 $ 2^{n-1}-1 $ 级的阶梯又可以用相同的方法分成两半,不断分治,最后必定会得到 $ 2^1-1 $ 的阶梯,并且总共恰好用了 $ 2^n-1 $ 个正方形.

当级数为偶数时,我们显然不能在右下角放置一个最大的正方形,并将其分成两半的同时也占用一层的最左的方块.故与 $ (1) $ 不符,因此级数为偶数的阶梯不是好阶梯.

当级数为奇数且不为 $ 2^n-1 $ 时,我们开始时可以同 $ 2^n-1 $ 级的方法进行分割,但是分割到后面必然会出现分割偶数级数的阶梯的情况,于是又不可分割,因此级数为奇数且不为 $ 2^n-1 $ 的阶梯不是好阶梯.

那么我们就可以用贪心的思想,每次选级数尽可能小的阶梯即可.由于阶梯级数是指数级递增的,复杂度为 $ O(log_2n) $

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
//头文件已省略
#define int long long
#define PI 3.14159265358979323
#define INF 0x3fffffffffffffff
using namespace std;
int T, n, ans;
signed main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--)
    {
        cin >> n;
        ans = 0;
        for (int i = 1; n >= ((1ll << i) - 1) * (1ll << i) / 2; ++i)
        {
            ++ans;
            n -= ((1ll << i) - 1) * (1ll << i) / 2;
        }
        cout << ans << endl;
    }
    return 0;
}
```



---

## 作者：511_Juruo_wyk (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1419B)

这道题最难的地方就是找“好阶梯”的规律，我们不妨拿题目中的七级阶梯研究一下。
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1419B/20e8f39717a3a82bb8f73bd6c4f499217c03a037.png)

注意看，红色正方形把整个阶梯分成了上下两部分，而这两部分还可以继续分；黄色正方形把这两个小部分再次分成了四小块，变成了四个绿色小正方形。你会奇迹般地发现，这是典型的分治思想，每一块三角形都可以被一个大正方形分成两部分，而这些部分可以继续分割成更小的部分……

多次研究发现，只有当 $n=2^k-1$（$k$ 为正整数）时，$n$ 层阶梯就是“好阶梯”。

找到规律之后，这题就水很多了。
```cpp
#include<bits/stdc++.h>
#define endl '\n'//让endl的时间复杂度变低 
using namespace std;
int t;
long long num;//注意开long long 
long long power;
long long sum(long long n){return n*(n+1)/2;}//高斯求和公式 
int main(){
    std::ios::sync_with_stdio(false);//让cin和cout速度变快，但是不能使用scanf和printf 
    cin>>t;
    while(t--){
        cin>>num;
        power=1;//初始化 
        while(num>0){
            power++;
            num=num-sum((1<<power)-1);//位运算符时间复杂度比pow(2,power)要低很多 
        }
        cout<<power-1<<endl;//注意power是从1开始的，所以输出时要减1 
    }
    return 0;//养成好习惯 
}
/*个人习惯把样例复制在代码下面 
4 
1 
8 
6 
1000000000000000000
*/
```


---

## 作者：Mine_King (赞：1)

这题我们首先看题目给的一张图，我们发现这个图很优美，为什么？因为它每次都从右下角取一个最大的正方形，然后将楼梯分成两部分，对于每一部分都继续分下去。 

既然是分成两份，那么我们就要去考虑 $2$ 的次幂。我们发现这个阶梯的阶数正好是 $2^3-1$。那么是不是所有 $2^n-1$ 阶的楼梯都是好楼梯？我们来证明一下。  
首先，阶数为 $1$ 的是好楼梯。然后，每次把一个好楼梯分成两个，放在右上和左下，中间再放一个大正方形，就又形成了一个好楼梯。而这样分下去，假设 $a_1=1$，那么
$$a_2 = a_1 \times 2+1=1 \times 2+1=3$$
$$a_3 = a_2 \times 2+1=3 \times 2+1=7$$
$$\vdots$$
观察可以发现 $a_i = 2^i-1$。于是就可以证明 $2^n-1$ 阶的楼梯都是好楼梯。

那么又有一个问题，是不是只有 $2^n-1$ 阶的楼梯是好楼梯？  
再证明一下。  
首先我们要知道，对于楼梯的每个角，都不能和其他的角放在同一个正方形里，那么如果一个楼梯是好楼梯，则每个正方形都必须包括一个角，。  
然后，若阶梯的阶数是偶数阶，那么每个角都有一个正方形后，可以发现右下角一定有一块空白，可以自己模拟一下。那么这块空白又要用至少一个正方形来填补，就不满足条件。  
对于不是 $2^n-1$ 阶的奇数阶阶梯，我们也像 $2^n-1$ 阶那样分，可以发现最后总会遇到偶数阶的情况，也不满足条件。  
由上可知有且仅有 $2^n-1$ 阶的楼梯是好楼梯。

接着，我们考虑最多能搭出多少不同的好的楼梯。由于每个楼梯对于答案的贡献是一样的，都是 $1$，所以只要贪心取最小的即可。

我的证明有些繁琐，但一步步走下来应该会很容易理解QAQ。

贴代码：
```cpp
#include<cstdio>
#define int long long
using namespace std;
int T,n,ans;
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        ans=0;
        scanf("%lld",&n);
        int k=2;
        while(true)
        {
            int x=k-1;
            int res=(1+x)*x/2;
            if(n>=res) n-=res;
            else break;
            ans++;
            k*=2;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：_buzhidao_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1419B)  
# 题目分析
设 $m$ 级阶梯是好阶梯：  
- 若 $m$ 为偶数，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/42qyztlv.png)  
显然，在用大正方形覆盖时，总会出现无法用大正方形覆盖的三个一组的小正方形（如图）。想象一下，若平移大正方形，会出现更大的空隙。这些空隙占用的空间始终会超过 $m$。  
所以，当 $m$ 为偶数，不可能成为好阶梯。  
- 若 $m$ 为奇数，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/yit56vmn.png)  
显然，用最大正方形填充后，会将大阶梯分割成两个 $\frac{m-1}{2}$ 级阶梯。若 $\frac{m-1}{2}$ 为偶数，则 $m$ 级阶梯不可成为好阶梯。  
所以，我们不仅需要让 $\frac{m-1}{2}$ 不为偶数，还需要让 $\frac{m_1-1}{2}(m_1=\frac{m-1}{2})$、$\frac{m_2-1}{2}(m_2=\frac{m_1-1}{2})$……都不为偶数。  
所以最终剩下的，也是最小的 $m_i$ 必然等于 $1$。  
所以 $\frac{m_{i-1}-1}{2}=m_i$，$m_{i-1}=2\times m_i+1=2\times 1+1=3$，  
$\frac{m_{i-2}-1}{2}=m_{i-1}$，$m_{i-2}=2\times m_{i-1}+1=2\times 3+1=7$……  
所以 $m=2^k-1$。

将 $m=2^k-1$ 代入，得：  
- $m_1=\frac{m-1}{2}=\frac{2^k-2}{2}=2^{k-1}-1$。
- $m_2=\frac{m_1-1}{2}=\frac{2^{k-1}-2}{2}=2^{k-2}-1$。  
……
- $m_i=\frac{m_{i-1}-1}{2}=\frac{2^2-2}{2}=2^1-1=1$。

成立。

综上，当且仅当 $m=2^k-1$ 时，$m$ 级阶梯是好阶梯。  

## 解题思路
本题考虑贪心，枚举 $k$。  
若 $2^k-1<n$（能建造 $2^k-1$ 级阶梯），则将 $n$ 减去 $2^k-1$ 级阶梯所需要的单位数（建造阶梯）。  
> 等差数列求和公式：$\frac{(\text{头}+\text{尾})\times \text{项数}}{2}$。

$2^k-1$ 级阶梯所需要的单位数：  
$=\frac{(1+2^k-1)\times (2^k-1)}{2}$，  
$=\frac{2^k\times (2^k-1)}{2}$，  
$=\frac{2^k}{2}\times(2^k-1)$，  
$=2^{k-1}\times(2^k-1)$。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,cnt;ll n,m,tmp,_1=1;
//_1为1的long long形式
int main(){
	cin>>t;
	for(int i=0;i<t;++i){
		cin>>n;m=n;cnt=0;
		for(int j=1;;++j){//贪心
			tmp=(_1<<(j-1))*((_1<<j)-1);//(2^j-1)阶阶梯需要的单位数
			if(tmp<=m){//如果能建造
				m-=tmp,cnt++;
			}
			else break;
		}
		cout<<cnt<<endl;
	}
	return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## Solution:

很容易发现，只有 $2 ^ k - 1$ 阶的楼梯是漂亮的。

那我们就可以预处理出所有漂亮的楼梯要的方块数，再根据贪心，先选少的就能选的更多。

假设我们现在找的的是一个 $a$ 阶的楼梯，那方块数的算法就是 $a \times (a + 1) \div 2$。

那就能切掉此题了。

[AC记录](https://www.luogu.com.cn/record/143532153)

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, x, a[65];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i = 1; i <= 62; i++){
		a[i] = ((1 << i) - 1);
		a[i] = a[i] * (a[i] + 1) / 2;
	}
	cin >> t;
	while(t--){
		cin >> x;
		int pos = 1;
		while(x >= a[pos]){
			x -= a[pos];
			pos++;
		}
		cout << pos - 1 << "\n";
	}
	return 0;
}
```

---

## 作者：drah_yrev (赞：0)

我们先枚举一下，看看当 $X$ 为多少的时候，$X$ 级阶梯是一个“好阶梯”。



|  $x$| 1 | 2 | 3 | 4 | 5 |6  |7  | 8 | 9 |10 | 11  
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: 
|  是否为“好阶梯”| 是| 否| 是|   否| 否 |  否| 是| 否 | 否 | 否 | 否 |  | 否 |否  | 否 | 否|


我们可以发现，当 $X$ 为 $2^n-1$ 的时候，$X$ 级阶梯是一个“好阶梯”。

我们再证明一下

我们知道：$1$ 级楼梯是“好阶梯”，此时级数为 $1$，**最大正方形边长**为 $1$。

然后我们将 $2$ 个 $1$ 级楼梯放在上端和左端，在在中间放上一个边长为**最大正方形边长的两倍**的正方形，此时又是一个“好阶梯”，级数为 $3$，**最大正方形边长**为 $2$。

然后我们将 $2$ 个 $3$ 级楼梯放在上端和左端，在在中间放上一个边长为**最大正方形边长的两倍**的正方形，此时又是一个“好阶梯”，级数为 $7$，**最大正方形边长**为 $4$。

……

变化过程如下图：（可能有点糊）

![](https://cdn.luogu.com.cn/upload/image_hosting/683ac61h.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们发现，好阶梯永远是 $2^n-1$ 级阶梯。

那我们要做的事就简单了：枚举 $n$ 到 $1$ 之间，有几个数是 $2^n-1$。

注意：要开 `long long`！


---

## 作者：ICU152_lowa_IS8 (赞：0)

本题是一道简单的思维~~和感性理解~~题。

首先观察可以得到，显然阶数为 $2^n-1$ 的阶梯为一个好阶梯，能用的正方形边长为 $2^k$，

如何证明阶数不为 $2^n-1$ 的阶梯不是一个好阶梯？

感性理解：不为 $2^n-1$ 的阶梯一定要多出一块，而那一块不能被多出的几个可以摆的正方形填补；

对如上感性理解进行理性思考:

设阶梯使用的格子数目为 $k$，则有 $2^n-1<k<2^{n+1}+1$；在这种情况下，显然能使用的正方形边长不会变；

相当于向右边扩展了几列，模拟~~感性理解~~可得无论如何，在正方形边长能拓展的拓展完之后还会剩一个无法被多出来的可用的几个边长为 $2^v(0\leq v)$ 的正方形填满的空。

对于本题还要注意，题目问的是可以摆成多少个而不是最大阶数，贪心的枚举即可。

代码就不放了。

---

## 作者：Genshin_ZFYX (赞：0)

不难发现，只有 $n$ 为 $2^{k}-1$ 时，才能组成一个“好阶梯”。推理过程如下：

任意“好阶梯”中最大的正方形把整个阶梯分成了上下两部分，而这两部分又分成了两个小的“好阶梯”。而次大的正方形把这两个小的“好阶梯”再次分出两个更小的“好阶梯”。以此类推，每一个“好阶梯”都可以被一个正方形再次分出两小的“好阶梯”，而这些部分可以继续分割成更小的“好阶梯”。

接下来就是代码实现了，需要使用位运算和高斯求和公式。

温馨提示：十年 OI 一场空，不开 long long 见祖宗！

AC 代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int t;cin>>t;
	while(t--)
	{
		int n,p=1;cin>>n;
		while(n>0)
		{
			p++;
			int k=(1<<p)-1;//位运算
			n-=k*(k+1)/2;//高斯求和
		}
		cout<<p-1<<endl;//p 需要减 1
	}
	return 0;
}
```

---

## 作者：tmp_get_zip_diff (赞：0)

首先，观察一下图片：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1419B/20e8f39717a3a82bb8f73bd6c4f499217c03a037.png)

我们发现他的长为：$2^0+2^1+2^2=7$，即为 $2^3-1$。

也就是说，长为 $2^k-1$ 的三角形，是“好阶梯”，其间的方块个数为 $(2^k)(2^k-1)(\frac{1}{2})$。

那么每输入一个 $n$，枚举 $i \to 1 \sim 63$，看能不能拼成，能拼成就拼，否则直接退出，统计个数即可。

我是预处理的，也行，记得看 `long long`。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long

int n,num[65];

void Work()
{
	cin>>n;
	int ans=0;
	for(int i=1;i<=63;i++)
		if(n>=num[i])
		{
			ans++;
			n-=num[i];
		}
	cout<<ans<<"\n";
	return ;
}

signed main()
{
	for(int i=1;i<=63;i++)
	{
		int tmp=(1ull<<i)-1ull;
		num[i]=(1ull+tmp)*tmp/2ull;
	}
	int T;
	cin>>T;
	while(T--)
		Work();
	return 0;
}
```

---

## 作者：星空舞涵 (赞：0)

##### ~~这道题所有题解被大佬撤了，属实没想到~~

我来水一发

#### 首先我是如何发现规律的呢

打表

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[100001];
int main()
{
	int n,t;
	cin>>n;
	dp[1]=1;
	cout<<1<<" " <<dp[1]<<endl;
	for(int i=2;i<=n;i++)
	{
		dp[i]=dp[i/2]*2+1;
		cout<<i<<" "<<dp[i]<<endl;
	}
}
```
#### 分析

对于一个$i$级阶梯，它是由一个正方形以及两个$i/2$级的阶梯组成的；

所以我们可以递归求$i$级阶梯由几个正方形组成

大概这样一个操作：

```
int digui(int n)
{
	if(n==1)return 1;
	return 2*digui(n/2)+1;
} 
```


对与一个$i$级阶梯，假设$i$处于$2^j$≤i＜$2^{j+1}$,那么$i$级阶梯就是由$\sum _{k=0}^j 2^k$个正方形组成

$\sum _{k=0}^j 2^k$=$2^{k+1}-1$

所以当$i$等于$2^{j-1}$时，他才是一个好阶梯

然后求一个前缀和记录前$i$个阶梯需要的格子的数量就可以了

### 代码

```
#include<bits/stdc++.h>
using namespace std;
long long dp[100001],er[32],s[32];long long  n,t;
int main()
{
	
	cin>>t;
	er[0]=1;
	for(int i=1;i<=30;i++)
	{
		er[i]=er[i-1]*2;
		s[i]=s[i-1]+(er[i]-1)*(er[i]/2);
	}
	while(t--)
	{
		cin>>n;
		for(int i=30;i>=1;i--)
		{
			if(n>=s[i])
			{
				cout<<i<<endl;
				break;
			}
		}
	} 
}
```




---

