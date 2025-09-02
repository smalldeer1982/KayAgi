# Tiles

## 题目描述

Bob is decorating his kitchen, more precisely, the floor. He has found a prime candidate for the tiles he will use. They come in a simple form factor — a square tile that is diagonally split into white and black part as depicted in the figure below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/51fd9adf02d36f09b63ea5e4909ce958161fd4a1.png)The dimension of this tile is perfect for this kitchen, as he will need exactly $ w \times h $ tiles without any scraps. That is, the width of the kitchen is $ w $ tiles, and the height is $ h $ tiles. As each tile can be rotated in one of four ways, he still needs to decide on how exactly he will tile the floor. There is a single aesthetic criterion that he wants to fulfil: two adjacent tiles must not share a colour on the edge — i.e. one of the tiles must have a white colour on the shared border, and the second one must be black.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/b795f3504af8553334180ece9878d04b86535357.png)The picture on the left shows one valid tiling of a $ 3 \times 2 $ kitchen. The picture on the right shows an invalid arrangement, as the bottom two tiles touch with their white parts.Find the number of possible tilings. As this number may be large, output its remainder when divided by $ 998244353 $ (a prime number).

## 样例 #1

### 输入

```
2 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
64
```

# 题解

## 作者：Zhoumy (赞：6)

**首先**：我们知道一个格子只有$4$种状态：左上黑，右上黑，左下黑和右下黑。因为一个对于地砖的每一条边，其两侧都应为不同的颜色，所以我们把它当成一个表格来填写，我们发现，如果第一行和第一列填完了，其他的都会确定，只有一种可能。  
**思路**:因为一个在第一行或第一列的格子除了第一行第一列都会受到旁边的格子的牵连，所以每一个都只有$2$种可能性，第一行第一列因为最开始填，所以有$4$种选法。然后思路就显而易见了。
```
#include<iostream>
using namespace std;
long long ans=1,w,h;
int main(){
	cin>>w>>h;
	for(int i=1;i<=w+h;i++){
		ans*=2;
		ans%=998244353;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Waddles (赞：3)

找一下规~~绿~~律就出来啦

~~其实猜也好猜~~

每个格子只有4种情况，只考虑下和右，黑白情况各两种

而确定它为黑，右可以选两种白，下可以选两种白

反之亦然

然后就可以画图推出整个图（不放图了，字太丑）

推出来应该是$2^{w+h}$

这里写了一个快速幂

```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
template<class Read>void in(Read &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
const int M=998244353;
ll n,m;
ll ksm(ll x,ll y){//快速幂
	ll s=1;
	while(y){
		if(y&1)s=(s*x)%M;
		x=(x*x)%M;
		y>>=1;
	}
	return s%M;
}
int main(){
	in(n);in(m);
	cout<<ksm(2ll,n+m)<<endl;//输出
	return 0;
}
```

---

## 作者：_bql (赞：3)

### 类型
~~小学奥数~~	数学

### 思路
总之肯定先推呗  其实看见样例是这样差不多可以猜到答案是什么了……  
开始推（瞎分析）：
（望巨佬提出更好的思路）

为了方便分析 我们把左上半边是黑色的方块称为“左上”，左下半边是黑色的称为“左下”，其余两种以此类推。  
然后观察一下，对于一个格子，与他相邻一个格子已经确定的情况下 满足情况的摆法共有两种。

例如：当这个格子的上方是“右下”时，它可能的取法有：“左下”和“右下”

如图：  
![](https://cdn.luogu.com.cn/upload/pic/65107.png )
![](https://cdn.luogu.com.cn/upload/pic/65108.png )

而当一个格子四周有大于等于2个格子被确定下来之后 这个格子就只有一种取法了（不贴图了 大家自己想一下）
所以我们完成了第一步分析  
然后这里要注意 可能有人会认为答案是$2^{w*h}$ 但是注意第一步的分析是建立在“当前的格子周围只有一个格子是被定下来的”的前提下  
当这个矩阵的第一行和第一列被确定下来的时候 整个矩阵就被确定下来了

所以答案为$2^{w+h}$ 要用快速幂

### Code主要部分
```cpp
#define mo 998244353
#define ll long long

ll n,k;
int main()
{
	cin>>n>>k;
    ll p=n+k,b=2,ans=1;
    while(p>0)
    {
        if(p%2==1) ans=ans*b%mo;
        b=b*b%mo;
        p=p/2;   
    }
	cout<<ans;
	return 0;
}
```

---

## 作者：xiezihanAKIOI (赞：0)

感觉这道题应有意思的，赶紧来写篇题解。

首先，我们看到这个图形。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178C/51fd9adf02d36f09b63ea5e4909ce958161fd4a1.png)

他由黑、白两种颜色组成，并且可以旋转，那么一种图形就有四种状态。

| 黑 |  |
| -----------: | -----------: |
|  | 白 |


| 白 |  |
| -----------: | -----------: |
|  | 黑 |

|  | 黑 |
| -----------: | -----------: |
| 白 |  |

|  | 白 |
| -----------: | -----------: |
| 黑 |  |

四种状态。那么我们就先从开始手动模拟。

当第一个格子为第一种状态时。

| 黑 |  | （黑） | （白） |
| -----------: | -----------: | -----------: | -----------: |
|  | 白 | （黑） | （白） |
| （黑） | （黑） |  |  |
| （白） | （白） |  |  |

注：括号表示这地方可以放置这个颜色。多个括号则不止一种选择。

那么很明显，当第一个格子白在下时，那么下方的各自可以选择黑在左上或右上两种可能，右边的同样左上或左下两种可能。以此类推。这个时候，大家可以去思考一下三行三列的格子的状态。很明显，他的状态已经是个定值了。那么我们就可以得出结论：当一个格子的两边都被确认时，其余的格子都是不变的了。

那么这个时候就很明确了。我们只需要把第一列和第一行的状态枚举出来，结果就是显而易见的了。（不懂的自己可以自己推。）

从上面的表格可以知道，当第一行第一列的值确定时，下方有黑在左上，右上两种状态。那么第一行的状态就有 $2^w$ 种，行的推论也一样，有 $2^h$ 种。那么答案就很明确了，就是行和列的状态的种类相乘。那么通过七下数学可以得知，~~（别问我为什么那么清楚，因为我就是七年级）~~ $a^x \times a^y=a^{x+y}$，所以 $2^w \times 2^h=2^{w+h}$

最后附上代码（记得用快速幂。）：

```
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int p = 998244353;

int ans = 1, n, k, n1, k1;

signed main () {
	cin >> n >> k;
	k += n;
	n = 2;
	while (k > 0) {
		if (k & 1) ans = ans * n % p;
		n = n * n % p;
		k >>= 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：金霸王电池 (赞：0)

可以~~看样例猜出~~证明答案为 $2^{w+h}$。

原因很简单。我们称一个格子有几个邻接格子确定为有几个限制。容易看出没有限制有 4 种方案，一个限制有 2 种方案，2 个限制则唯一确定。

因此，每添加一行或一列，除第一个有 2 个限制，其余都有 1 个限制，那么方案数乘 2 。又因为 $w=h=1$ 时成立，因此对任意的 $w$ 与 $h$ ，方案数都为 $2^{w+h}$。

AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,m;
int pow(int k){//快速幂
	if(k==0)return 1;
	int x=pow(k/2);
	if(k%2)return x*x%mod*2%mod;
	return x*x%mod;
}
signed main(){
	cin>>n>>m;
	cout<<pow(n+m);
	return 0;
}
```


---

## 作者：OLE_OIer (赞：0)

这一道题目的思路性比较强，而对代码能力要求较低。

这道题是一道数学题。我的思路是这样的：

在 $1 \times 1$ 的地板上，显然有 $4$ 种方法。现在把地板添加 $1$ 格，得到 $1 \times 2$ 的地板，则第 $2$ 块地板在第 $1$ 块地板已经确定的时候有 $2$ 种方法。同理把地板转化为 $2 \times 2$ 的地板，发现第 $2$ 行第 $1$ 块也有 $2$ 种方法。而第 $2$ 行第 $2$ 块在它上方与左边的地砖确定的时候就只有 $1$ 种方法了。于是对于 $w \times h$ 的地板，有 $2^{w+h}$ 种方法，且 $w$ 和 $h$ 数据不大，所以可以不用快速幂求解，直接用循环即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int main(){
	ios::sync_with_stdio(false);//输入输出加速
	long long cnt=1;
	int a,b;
	cin>>a>>b;
	for(int i=1;i<=a+b;++i) cnt=(cnt<<1)%mod;//计算可能性总数
	cout<<cnt;
	return 0;
}
```

---

