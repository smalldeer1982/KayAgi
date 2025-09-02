# [AGC008C] Tetromino Tiling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc008/tasks/agc008_c

正方形のマスを $ 4 $ 個繋げた形をテトロミノといいます。 次の $ 7 $ 種類のテトロミノを順に I, O, T, J, L, S, Z 型と呼ぶことにします。

 ![a60bcb8e9e8f22e3af51049eda063392.png](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc008_c/41da26817a0aa4921d5f3228c5ba880f4ed240c0.png)

すぬけ君は I, O, T, J, L, S, Z 型のテトロミノをそれぞれ $ a_I $, $ a_O $, $ a_T $, $ a_J $, $ a_L $, $ a_S $, $ a_Z $ 個ずつ持っています。 すぬけ君はこれらのテトロミノのうち $ K $ 個を組み合わせ、縦 $ 2 $ マス、横 $ 2K $ マスの長方形を作ろうとしています。 このとき、すぬけ君は次のルールに従います。

- 各テトロミノを置くとき、回転はできるが、反転はできない。
- 長方形の各マスにはちょうど $ 1 $ 個のテトロミノが置かれているようにする。
- 長方形の外部にテトロミノが置かれていないようにする。

すぬけ君はできるだけ大きい長方形を作ろうとしています。 $ K $ の最大値を求めてください。

## 说明/提示

### 制約

- $ 0\ <\ =a_I,a_O,a_T,a_J,a_L,a_S,a_Z\ <\ =10^9 $
- $ a_I+a_O+a_T+a_J+a_L+a_S+a_Z\ >\ =1 $

### Sample Explanation 1

たとえば、図のように組み合わせればよいです。 !\[45515ed2a1dd5e41c5e4ca1f39323d8e.png\](https://atcoder.jp/img/agc008/45515ed2a1dd5e41c5e4ca1f39323d8e.png)

### Sample Explanation 2

長方形を作ることができません。

## 样例 #1

### 输入

```
2 1 1 0 0 0 0```

### 输出

```
3```

## 样例 #2

### 输入

```
0 0 10 0 0 0 0```

### 输出

```
0```

# 题解

## 作者：FFTotoro (赞：6)

一道很好的思维题，一贯有 AtCoder 的风格。

观察题目，我们可以得到显而易见的两个结论：

- T,S,Z 三种形状是绝对不可以选择的（原因：这三种形状会将整个 $2\times 2K$ 的长方形分成两个奇数块的形状，填到最后便无法填充）；

- O 形方块可以全选，对答案 $K$ 的贡献值就为它的块数。

现在我们再来考虑剩下的三种方块：

很显然，2 个 J、2 个 I 或 2 个 L 可以构成一个 $2\times4$ 的长方形，对 $K$ 的贡献值为 2，我们称其为方案一。但是，还有一种情况——用 1 个 J、1 个 I 和 1 个 L，可以构成一个 $2\times6$ 的长方形，对 $K$ 的贡献值为 3，我们称其为方案二。

易证 2 个及以上的“方案二”构成的长方形可以由“方案一”（或再加上 1 个“方案二”）来构成，所以只用考虑出现 1 个“方案二”即可。

但是要注意，可以构成“方案二”当且仅当 I,J,K 三种方块的数量都不小于 1。所以需要特判。

放代码：

```cpp
#include<iostream>
#define int long long
using namespace std;
signed main(){
    int i,o,t,j,l; cin>>i>>o>>t>>j>>l; // J 和 L 后面的都不用读入了
    cout<<o+max(i&&j&&l?3+(i-1)/2*2+(j-1)/2*2+(l-1)/2*2:0,i/2*2+j/2*2+l/2*2)<<endl; // 如果只用上文所述的方案二，用完方块还有剩余 1 块那么就不能用；方案一也是类似的道理
    return 0;
}
```

---

## 作者：fengenrong (赞：5)

这道题其实是一道思维题，我们分别用 $I$，$O$，$T$，$J$，$L$，$S$，$Z$ 表示下图的七个图形。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_agc008_c/41da26817a0aa4921d5f3228c5ba880f4ed240c0.png)

我们不难发现图形 $T$，$S$，$Z$ 要是和其它的图形组成的话必定会剩下单独一个空格，而题目要求宽是为 $2$。所以如果选了图形 $T$，$S$，$Z$，填到最后便无法填充，那我们就不考虑图形 $T$，$S$，$Z$。

接着我们再来看图形 $O$，因为图形 $O$ 不管怎样都是可以全部选上的，所以我们让 $ans$ 加上 图形 $O$ 的数量。

我们排除这些特殊的图形后，就只剩下图形 $J$，$I$，$L$。我们可以发现利用这三个图形有两种组成的方法，第一种是用两个 $J$、两个 $I$ 或两个 $L$  组成的 $2\times 4$ 的长方形，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/gv9117ns.png)

而另一种方法则是图形 $J,I,L$ 各用一个组成的 $2\times 6$ 的长方形，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mufirjo2.png)

我们再让 $ans$ 加上这两个中的最大值就行了。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int I,O,T,J,L,S,Z,ans;
signed main()
{
	cin>>I>>O>>T>>J>>L>>S>>Z;//输入各个图形的数量
	ans=max(I/2*2+J/2*2+L/2*2,I>0&&J>0&&L>0?(I-1)/2*2+(J-1)/2*2+(L-1)/2*2+3:0);//求两种方案的最优解
	cout<<O+ans<<endl;//注意：一定不要忘记加上图形O的数量
	return 0;
}
```

---

## 作者：A_Đark_Horcrux (赞：3)

我们可以先找一找哪些拼法能满足条件：

$K=1:$ 单独一个 O 块

$K=2:$ 可以用 I 块、J 块、L 块，有如下三种方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/gv9117ns.png)

$K > 2:$ 可以用 I 块、J 块、L 块，拼成如下的结构：

![](https://cdn.luogu.com.cn/upload/image_hosting/mufirjo2.png)

此时 $K=3$，是一种更优的结构。这个结构可以无限延申下去，但是你会发现，每次延申需要两个 I 块，这和单独用两个 I 块拼，结果是相同的；而如果把这个结构复制一遍，结果和用两个 I 块、两个 J 块和两个 L 块的结果是一样的。因此这个结构只需要在最终结果中出现一次。

计算结果，O 块全部记上；I 块、J 块、L 块可以先凑一个上面的结构，剩下的分别每两个 K+=2，或者直接分别每两个算 K+=2，取最大值即可。T 块、S 块和 Z 块是拼不起来的，忽略


```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
ll I,O,T,J,L,S,Z,x,ans;
ll min(ll x,ll y){return x<y?x:y;}
ll max(ll x,ll y){return x>y?x:y;}
int main()
{
	scanf("%lld %lld %lld %lld %lld %lld %lld",&I,&O,&T,&J,&L,&S,&Z);
	ans=max(O+I/2*2+J/2*2+L/2*2,I>0&&J>0&&L>0?O+(I-1)/2*2+(J-1)/2*2+(L-1)/2*2+3:0);//两种方案取较大
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：XYukari (赞：3)

[更好的阅读体验](https://www.cnblogs.com/q0000000/p/15506349.html)

给出如下图的 $7$ 种俄罗斯方块各 $a,b,c,d,e,f,g$ 块，可以旋转不能翻转，要求拼成宽度为 $2$ 的长方形。输出能得到的最大长度的一半——奇怪的题目要求。

![](https://cdn.luogu.com.cn/upload/image_hosting/d63tq7sy.png)

不难发现，第 $3,6,7$ 种方块压根用不上，因为它们造成了长度为 $1$ 的凹槽，而这些凹槽永远不可能被填平：要填平它们，就要用这三种方块；用了这三种方块，又会有新的凹槽产生。

下面考虑每种方块“自力更生”能否拼出宽度为 $2$ 的长方形：

- 第 $1$ 种，竖着两个并排，长宽 $4\times 2$；
- 第 $2$ 种，自己符合条件，长宽 $2\times 2$；
- 第 $3,4$ 种，一个倒扣在另一个上面，长宽 $4\times 2$。

看起来长度的一半为 $L=\lfloor\dfrac{a}{2}\rfloor\times 2+b+\lfloor\dfrac{d}{2}\rfloor\times 2+\lfloor\dfrac{e}{2}\rfloor\times 2$。

还没完！我们继续考虑几种方块“通力合作”能否拼出宽度为 $2$ 的长方形：只有一种方案，即第 $1,4,5$ 种方块各一个，拼成长宽 $6\times 2$ 的长方形，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/pwjrb557.png)

以此为基础，我们对上面的式子进行修正：

- 如果第 $1,4,5$ 种方块都为奇数，在满足“自力更生”前提下，每种恰有一块剩余，可以组合，故 $L\gets L+3$；
- 如果第 $1,4,5$ 种方块，只有两种为奇数，则最后会剩下两块。例如剩下了 $1,4$ 各一块，这时，我们拆出一个 $5$，能得到更优的答案——拆出减 $4$，重组加 $6$，$L\gets L+1$。

下面是 AC 代码：

```cpp
void main() {
	cin.tie(0), cout.tie(0);
	long long a, b, c, d, e, f, g;
	cin >> a >> b >> c >> d >> e >> f >> g;
	long long ans = (a / 2) * 2 + b + (d / 2) * 2 + (e / 2) * 2;
	if ((a & 1) + (d & 1) + (e & 1) >= 3)
			ans += 3;
	else if ((a & 1) + (d & 1) + (e & 1) >= 2 && (a > 0) && (d > 0) && (e > 0))//必须保证有，才能拆借
		ans++;
	cout << ans << endl;
}
```

虽然是 AGC 的 C 题，也没有那么难啊，主要是细节太多，如果放到 OI 赛制的模拟赛中，是一道很好的“签到题”。

## THE END

---

## 作者：zhylj (赞：3)

注意到 T, S, Z 是不可能存在于答案中的。

发现两个 I，一个 O，两个 L，两个 J 都可以组成 $2\times x$ 的矩形。

然后还有一种 I, L, J 组成的矩形，显然这个矩形至多出现一次足以成为最优解之一（如果增加 I 的数量，可以相当于若干个由两个 I 组成的矩形拼在一起），枚举是否出现即可。

```cpp
ll Check(ll a1, ll a2, ll a4, ll a5) {
	return (a1 - a1 % 2) + a2 + (a4 - a4 % 2) + (a5 - a5 % 2);
}

int main() {
	ll a1, a2, a3, a4, a5, a6, a7;
	rd(a1, a2, a3, a4, a5, a6, a7);
	ll ans = Check(a1, a2, a4, a5);
	ans = std::max(ans, Check(a1 - 1, a2, a4 - 1, a5 - 1) + (a1 > 0 && a4 > 0 && a5 > 0) * 3);
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：tmp_get_zip_diff (赞：2)

思路：

首先，第二种类型是绝对要用上的，因为只要把它放在最顶端，不会影响到下面的操作。

其次，第三、六、七种是绝对不能用的，证明：

> 反证法：  
> 假设使用第三种可以，那么对于它最顶端放在的位置是第 $k$ 行，上面的空位即为 $2 \times k -1$ 个，必定为奇数，而其他积木都是偶数块，因此填不满，假设不成立。
> 
> 其余两种同理。

剩下的是第一、四、五种，我们发现两个第一、四、五种都可以用两个搭成一个 $4 \times 2$ 的矩形。

还有呢，第一、四、五种各一个可以搭成一个 $6 \times 2$ 的矩形。

因此我们的贪心策略是：先把第二种加上，再尽量让第一、四、五种尽量留一个或两个，其他的两个一拼，剩下的分类讨论即可。

我们算的是高度，最终要 $\div 2$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int tmp,ans;

signed main()
{
	int fan,k1,k2,k3;
	cin>>k1>>fan>>tmp>>k2>>k3;
	ans=fan*2;
	int p1=(k1-1)/2,p2=(k2-1)/2,p3=(k3-1)/2;
	ans+=(p1+p2+p3)*4;
	k1-=p1*2,k2-=p2*2,k3-=p3*2;
	if(min({k1,k2,k3})==0)
	{
		switch (k1+k2+k3)
		{
			case 2:
				if(max({k1,k2,k3})==2)
					ans+=4;
				break;
			case 3:
				ans+=4;
				break;
			case 4:
				ans+=8;
				break;
		}
	}
	else
	{
		switch (k1+k2+k3)
		{
			case 3:
			case 4:
				ans+=6;
				break;
			case 5:
				ans+=8;
				break;
			case 6:
				ans+=12;
				break;
		}
	}
	cout<<ans/2;
	return 0;
}

```

---

## 作者：Tachibana27 (赞：1)

有点意思的思维题



------------
### 思路

1.  不难发现「T 方块」「S 方块」「Z 方块」是无法以任何方式拼成长方形的，所以不考虑。

2. 「O 方块」的插入是会将长增加 $2$ 的，所以必然需要使用「O 方块」。

3. 「I 方块」「J 方块」「L 方块」均可以使用两个自身拼成一个长为 $4$ 的合法长方形。

4. 「I 方块」「J 方块」「L 方块」可以各使用一个自身拼成一个长为 $6$ 的的合法长方形。

那么答案就是 $3$ 方案和 $4$ 方案取最大后加上「O 方块」的贡献除以 $2$。

详见代码。

code: 

```cpp
#include<bits/stdc++.h>
inline long long read(){
	long long s=0;
	long long w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())
		s=s*10+ch-'0';
	return s*w;
}

void write(long long x){
	if(x<0){
   		putchar('-');
   		x=-x;
	}
	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
}//快读快写自动掠过
long long i,o,j,l;
signed main(){
    i=read();//「I 方块」
    o=read();//「O 方块」
    read();
    j=read();//「J 方块」
    l=read();//「L 方块」
    read();
    read();//由于它们对答案没有贡献，所以不用读入
    write((std::max((long long)(i/2)*4+(long long)(j/2)*4+(long long)(l/2)*4,(i&&j&&l)?(long long)(i-1)/2*4+(long long)((j-1)/2)*4+(long long)((l-1)/2)*4+6:0)+o*2)/2);//这里的/2是因为3方案方块拼组需要2个，而奇数只能/2向下取整；要保证i，j，l均不为0才能拼组
    return 0;//完结撒花
}
```

---

## 作者：Liyunze123 (赞：0)

很容易发现，如果用了第 $3,6,7$ 种是一定拼不出来的，第 $2$ 种加在长方形的末尾和放中间是一样的，即我们可以求出不带这种的最长长度，加上 $O$ 就是正确答案。

第 $1,4,5$ 种可以用两个某一种的拼成 $2\times 4$，各用一个能拼成 $2\times 6$ 的。

我们可以枚举拼了几个 $2\times 6$。因为各种优化卡过了。
```
//c++20 -02
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f;
long long ans;
int main(){
	scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f);
	for(int w=0,x=min(min(e,d),a);w<=x;w++)ans=max(ans,w*3ll+(a-w)/2ll*2+(e-w)/2ll*2+(d-w)/2ll*2);
	printf("%lld",ans+b);
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：0)

简单思维题。

我们称七个的颜色分别为红橙黄绿蓝靛紫。

不难看出黄靛紫三色一定不能用，用了总会有一块是填不上的，而题目要求是要填一个矩形。

我们考虑计算长度，最后答案把长度除以二即可。

显然橙色是可以直接加上的，两个红、两个绿、两个蓝的长度均为 $4$，一红一绿一蓝的长度为 $6$。

我们看一下上面的数字，发现一个方块的平均贡献均为 $2$，所以我们可以先进行同色组，然后再进行异色组。

具体的，我们把红绿蓝三色方块都两两组合，直到剩下的数不多于 $2$。我们设剩下的三个数为 $a,b,c$。

我们按照是否有一个数为 $0$ 来进行分类讨论，用 $a+b+c$ 的大小来判断个数，具体看代码。

注意当 $a+b+c=0$ 时如果最大的数为 $2$ 也要加上 $4$。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int a,b,c,d,f,ans;
signed main()
{
	a=read(),d=read(),f=read(),b=read(),c=read(),f=read(),f=read();
	ans=d*2;
	int k1=(a-1)/2,k2=(b-1)/2,k3=(c-1)/2;
	ans+=(k1+k2+k3)*4;
	a=a-k1*2;
	b=b-k2*2;
	c=c-k3*2;
	if(min(a,min(b,c))==0){
		if(a+b+c==2&&max(a,max(b,c))==2)
			ans+=4;
		if(a+b+c==3)
			ans+=4;
		if(a+b+c==4)
			ans+=8;
		printf("%lld",ans/2);
		return 0;
	}
	if(a+b+c==2)
		ans+=4;
	if(a+b+c==3)
		ans+=6;
	if(a+b+c==4)
		ans+=6;
	if(a+b+c==5)
		ans+=8;
	if(a+b+c==6)
		ans+=12;
	printf("%lld",ans/2);
	return 0;
}

```

---

## 作者：_ChongYun_ (赞：0)

七种方块给定数量，摆放 $K$ 枚方块拼成一个宽为 $2$，长为 $2K$ 的长方形，求最大的 $K$ 值。

# 解析

很有趣的一道思维题。

因为宽是 $2$，所以可以这样理解，就是往一个宽为 $2$，长无穷大的长方形内放方块。

首先我们可以发现以下几点：

- 显然的，无论如何使用「O 方块」都可以使得 $K$ 值增加一，所以一定要用上「O 方块」，答案必然加上它的数量。

- 显然的，如果使用「T 方块」「S 方块」「Z 方块」，一定不能将一个符合题意的长方形拼出来，总会有一些边边角角被遗漏。

剩下的方块有「I 方块」「J 方块」「L 方块」，对于它们的摆放有两种方式。

1. 「I 方块」「J 方块」「L 方块」均可以使用两个自身拼成一个 $K$ 为 $2$ 的合法长方形。 

2. 「I 方块」「J 方块」「L 方块」可以各使用一个自身拼成一个 $K$ 为 $3$ 的合法长方形。

取两种方案的较大值并加上「O 方块」的数量即为答案。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,c,d,e,f,g;
int ff(int x){ return x-x%2; }
signed main(){
    cin>>a>>b>>c>>d>>e>>f>>g;
    cout<<b+max(ff(a)+ff(d)+ff(e),(a&&d&&e)?ff(a-1)+ff(d-1)+ff(e-1)+3:0)<<endl;
    return 0;
}
```


---

