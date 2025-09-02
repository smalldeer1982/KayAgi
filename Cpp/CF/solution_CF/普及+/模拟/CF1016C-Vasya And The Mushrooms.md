# Vasya And The Mushrooms

## 题目描述

Vasya 住在森林里，附近有一个会长蘑菇的空地。这个空地被分成两行，每行分为 $n$ 个连续的格子。Vasya 知道每分钟每个格子里能长多少个蘑菇。他要花一分钟从一个格子走到相邻的格子上，并且他不能离开空地。（我们称两个格子相邻，当且仅当它们有公共边。）当 Vasya 进入一个格子时，他会马上收集那个格子里的所有蘑菇。

Vasya 从左上角的格子开始收集蘑菇。因为他等不及蘑菇生长了，所以每分钟内他必须移动到一个相邻格子。他想每个格子都恰好走一遍并且最大化他所收集的蘑菇数量。一开始所有格子都没有蘑菇。Vasya也不一定要回到开始的格子。
帮帮 Vasya！计算出他能收集到的最大蘑菇数量。

## 说明/提示

#### 样例1:

在第一个测试用例中，最佳路径如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1016C/fbb0db02f46ac40c8f18dc6a212852df14543f5e.png) 

这样，蘑菇的收集重量将为 $0·1 + 1·2 + 2·3 + 3·4 + 4·5 + 5·6 =70$。

#### 样例2:

在第二个测试用例中，最佳路径如下：

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1016C/0853812a60511dc1127814cc7d3f93535736820f.png) 

这样，蘑菇的收集重量将为 $0·1 + 1·10 + 2·100 + 3·1000 + 4·10000 + 5·100000 =543210$

## 样例 #1

### 输入

```
3
1 2 3
6 5 4
```

### 输出

```
70
```

## 样例 #2

### 输入

```
3
1 1000 10000
10 100 100000
```

### 输出

```
543210
```

# 题解

## 作者：Mickey_snow (赞：8)

这道题难度并不算大，主要考的是细心程度。

### 思路

这题思路并不难想，注意有一句非常关键的话: _每个格子必须且只能经过一次。_ 不难发现，方案数量是线性的。

![](https://cdn.luogu.com.cn/upload/pic/26669.png )

![](https://cdn.luogu.com.cn/upload/pic/26670.png )

这是样例解释中的两张图，我们分别记他们为 **方案1** 和 **方案2** ,可以发现，我们有三种可行方案：方案1，方案2，前 $i$ 列使用方案1，随后使用方案2.

这样，所有的方案都已经被找到，将他们计算出来的时间复杂度为 $O(N^2)$ ,超时。虽然时间超了，但是这种思路没错。

### 优化方案

为了简单起见，以下图片中的数字代表 _位于这个格子中的数字(蘑菇生长速度)为最终的答案的贡献值_ 也就是 _采集这个蘑菇时它生长了多少秒_ 换句话说， _到达这个格子时可以采集到多少倍于它每秒生长值的蘑菇_.

如图，这是方案2中每个蘑菇的贡献。 $(n=8)$

![](https://cdn.luogu.com.cn/upload/pic/26671.png )

这是采用两行方案1之后采用方案2每个蘑菇的贡献。

![](https://cdn.luogu.com.cn/upload/pic/26672.png )

这样，不难发现规律：从第三列开始，下图中每个数都比上图大2.我们可以使用两个变量 $now$ 和 $last$ ，分别记录现在这种方案中方案1和方案2对答案的贡献，像这样每隔一列更新一下，可以手算出八种变化，然后后边大2的部分前缀和快速求和乘2即可。不要忘记方案1有可能采用奇数列，可以用一样的方法计算。最后 $ans = max(now_i+last_i)$

建议手算变化量时，画个图给自己看，可以让思路更加清晰。

![](https://cdn.luogu.com.cn/upload/pic/26678.png )

伪代码如下：

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CF1016C
{
    class Program
    {
        public class Global
        {
            public static Int64[,] num;
            public static Int64[] perf;
        }

        public static Int64 GetSum(int fr, int to){
            if (fr == 0) return Global.perf[to];
            else return (Global.perf[to] - Global.perf[fr - 1]);
        }

        static void Main(string[] args)
        {
            string inp; string[] div;

            int totList = Convert.ToInt32(Console.ReadLine()), p;
            Int64 nowNum, leftNum, _max, together;
            Global.num = new Int64[2, totList];Global.perf = new Int64[totList];

            for (int i = 0; i < 2; i++) {
                inp = Console.ReadLine(); div = inp.Split(' ');
                for (int j = 0; j < totList; j++) {
                    Global.num[i, j] = Convert.ToInt64(div[j]);
                }
            }
            Global.perf[0] = Global.num[0, 0] + Global.num[1, 0];
            for (int i = 1; i < totList; i++)
                Global.perf[i] = Global.perf[i - 1] + Global.num[1, i] + Global.num[0, i];

            nowNum = leftNum = 0;
            for (int i = 0; i < totList; i++) leftNum += Global.num[0, i] * i;
            for (int i = totList - 1; i >= 0; i--) leftNum += Global.num[1, i] * ((totList << 1) - i - 1);
            together = _max = leftNum;

            for(int cgList = 2; cgList < totList; cgList += 2) {
                p = (cgList << 1) - 4;
                nowNum += Global.num[0, cgList - 2] * p++;
                nowNum += Global.num[1, cgList - 2] * p++;
                nowNum += Global.num[1, cgList - 1] * p++;
                nowNum += Global.num[0, cgList - 1] * p;

                p = ((cgList - 2) << 1);
                leftNum -= Global.num[0, cgList - 2] * p++;
                leftNum -= Global.num[0, cgList - 1] * p;
                p = (totList << 1) - 1;
                leftNum -= Global.num[1, cgList - 2] * p--;
                leftNum -= Global.num[1, cgList - 1] * p;
                leftNum += (GetSum(cgList, totList - 1) << 1);

                _max = Math.Max(_max, nowNum + leftNum);
            }

            nowNum = Global.num[1,0];leftNum = 0;
            for (int i = 1; i < totList; i++) leftNum += Global.num[1, i] * (i + 1);
            for (int i = totList - 1; i > 0; i--) leftNum += Global.num[0, i] * ((totList << 1) - i);
            _max = Math.Max(_max, nowNum + leftNum);

            for (int cgList = 3; cgList < totList; cgList += 2) {
                p = ((cgList - 2) << 1);
                nowNum += Global.num[1, cgList - 2] * p++;
                nowNum += Global.num[0, cgList - 2] * p++;
                nowNum += Global.num[0, cgList - 1] * p++;
                nowNum += Global.num[1, cgList - 1] * p;

                p = ((cgList - 2) << 1);
                leftNum -= Global.num[1, cgList - 2] * p++;
                leftNum -= Global.num[1, cgList - 1] * p;
                p = (totList << 1) - 1;
                leftNum -= Global.num[0, cgList - 2] * p--;
                leftNum -= Global.num[0, cgList - 1] * p;
                leftNum += (GetSum(cgList, totList - 1) << 1);

                _max = Math.Max(_max, nowNum + leftNum);
            }

            Console.WriteLine(_max.ToString());
        }
    }
}
```

CF支持C#。在 .NET Framework 4.7.1 或更高版本的框架下编译并运行。

---

## 作者：YellowBean_Elsa (赞：5)

## 从没做过如此难的 CF-C qwq

首先注意到爆搜直接爆炸

然后发现方案数是O(N)的，且每个方案都有一个共同特点：

- 先不停的上下移动（方案1）

- 到一个点（第1行）时向右走到底再回来（方案2）

- 或先向下再走到底然后回来（方案3）

然而计算这些方案每个O(N)会爆

**所以我们分析方案两两之间能否递推**

最后发现要用几个前缀和

于是做完了

贴上极短的代码：

```cpp
//coder: FeliksYB, an AKer of IMO
//懒得改long long问题了，全开保证不见祖宗233 
#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int N=3e5+10;
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}
int n;
int a[N],b[N];
ll ans;
ll s[N],sum1[N],sum2[N];
ll u[N];
ll cur=-1;//计算方案1时所用“时间戳” 
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=n;i>=1;i--){
		s[i]=s[i+1]+a[i]+b[i];//后缀两行和 
		sum1[i]=sum1[i+1]+s[i+1]+b[i]+b[i]*((n-i)<<1);//后缀方案2和			
		sum2[i]=sum2[i+1]+s[i+1]+b[i]+a[i+1]*((n-i)<<1);//后缀方案3和 
	}for(int i=3;i<=n;i+=2){
		u[i]=u[i-2]+a[i-2]*(++cur)+b[i-2]*(++cur)+b[i-1]*(++cur)+a[i-1]*(++cur);
		//在第i（奇数）列第一行结束方案1，开始使用方案2或3时，使用方案1的总收入 
	}for(int i=1;i<=n;i+=2){//计算答案 
		ans=max(ans,u[i]+sum1[i]+s[i]*((i<<1)-2));
		ans=max(ans,u[i]+sum2[i]+s[i]*((i<<1)-2));
	}printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：yybyyb (赞：4)

发现这样一个性质，如果当前在$(1,i)$位置，  
并且$(2,i-2)$没被走过，
那么就只能够先一直走到$(1,n)$再下来再回来这样走了。  
那么一个合法的方案一定是现在前面若干列上下上下这样$S$形走，  
然后一直在这一行走到尽头再转回来，  
那么走到尽头再转回来这个过程直接预处理，从头到尾模拟一遍就好了。   
预处理之后所有东西都可以直接计算了。  
细节需要注意，这场CF细节好多啊。   
[强行插入博客链接](https://www.cnblogs.com/cjyyb/p/9426296.html)
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll long long
#define MAX 300300
inline int read()
{
	int x=0;bool t=false;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
	if(ch=='-')t=true,ch=getchar();
	while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
	return t?-x:x;
}
int n,a[MAX],b[MAX];
ll s,sa[MAX],sb[MAX],ra[MAX],rb[MAX],ans,da[MAX],db[MAX];
int main()
{
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i)b[i]=read();
	for(int i=n;i>=1;--i)da[i]=da[i+1]+a[i],db[i]=db[i+1]+b[i];
	s=0;for(int i=n;i>=1;--i)sa[i]=sa[i+1]+s,s+=a[i];
	s=0;for(int i=n;i>=1;--i)sb[i]=sb[i+1]+s,s+=b[i];
	for(int i=n;i>=1;--i)ra[i]=ra[i+1]+1ll*(n-i)*a[i];
	for(int i=n;i>=1;--i)rb[i]=rb[i+1]+1ll*(n-i)*b[i];
	s=0;
	for(int i=1,t=0;i<=n;++i)
		if(i&1)
		{
			ans=max(ans,s+sa[i]+rb[i]+1ll*t*da[i]+1ll*(t+n-i+1)*db[i]);
			s+=1ll*t*a[i];++t;
			ans=max(ans,s+sb[i]+ra[i+1]+1ll*t*db[i]+1ll*(t+n-i+1)*da[i+1]);
			s+=1ll*t*b[i];++t;
		}
		else
		{
			ans=max(ans,s+sb[i]+ra[i]+1ll*t*db[i]+1ll*(t+n-i+1)*da[i]);
			s+=1ll*t*b[i];++t;
			ans=max(ans,s+sa[i]+rb[i+1]+1ll*t*da[i]+1ll*(t+n-i+1)*db[i+1]);
			s+=1ll*t*a[i];++t;
		}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：aison (赞：2)

（注：以下$a_{i}$表示第1行第i列，$b_{i}$表示第2行第i列）
### 思路
由于每个格子必须遍历一遍，
假设你现在在第1行第k列（k为奇数），不难发现你一共只有3种选择：
1. 从$a_{k}$走到$a_{n}$，再从$b_{n}$走回$b_{k}$。
1. 从$b_{k}$走到$b_{n}$，再从$a_{n}$走回$a_{k}$。
1. 沿着$a_{k}$->$b_{k}$->$b_{k+1}$->$a_{k+1}$->$a_{k+2}$走,进而跳转到下一个状态（你在第1行第k+2列），此时你又可以选择1、2、3中的任一方式继续走下去

如果你选择方案1、2中的任一一种，那就等于直接走完了整个方阵，大功告成，也就不存在之后的状态了，此时你可以直接计算方案1和方案2所得到蘑菇贡献值的最大值，和之前已经获得的贡献值相加得到答案，更新最终答案即可。只有当你选择方案3时，才可能出现下一个状态。因此，对于每个状态，它之前的所有状态做出的选择一定都是第3种，即走了若干个U形。从每个状态到下一个状态多走了4个方格，即$a_{k}$->$b_{k}$->$b_{k+1}$->$a_{k+1}$，把它们的权值（即蘑菇增长速度）乘以抵达的时间相加即可得到转移方程。

### 计算

我们用s[k]表示$\sum_{i=k}^{n}(a_{i}+b_{i}),$用ret1[k]表示当前在第1行第k列，采用方案1获得的权值，ret2[k]表示当前在第1行第k列，采用方案2获得的权值。在计算的过程中，由于从第1行第k列出发的时刻和从第1行第k-2列出发的时刻不同，不利于计算，我们可以先假设出发的时刻都是0，计算出权值和，再加上(2×k-2)×s[k]。（说明：对于从第1行第k列出发的这个状态，$a_{1}$~$a_{k-1}$、$b_{1}$~$b_{k-1}$一定都已经走过了，所以出发的时刻是2×k-2，并且每晚开始走1秒，没走的格子的权值都要增加一倍，所以乘以s[k]）

根据题意我们不难列出各数组之间的递推公式，详见代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<set>
#include<map>
#include<vector>
#include<stack>
#include<cmath>
#include<string>
#include<algorithm>
#include<iomanip>
typedef long long int ll;
using namespace std;
ll n;
ll a[300005];
ll b[300005];
ll s[300005],ret1[300005],ret2[300005];
ll dw[300005];
//dw[k]表示当前在第1行第k列，在该状态前一直选择方案3得到的权值和
ll ans=0;
int main()
{
	scanf("%lld",&n);
	for(ll j=1;j<=n;j++)
	{
		scanf("%lld",&a[j]);
		s[1]+=a[j];
		ret1[1]+=(j-1)*a[j];
		if(j!=1)ret2[1]+=(2*n-j+1)*a[j];
	}
	for(ll j=1;j<=n;j++)
	{
		scanf("%lld",&b[j]);
		s[1]+=b[j];
		ret1[1]+=(2*n-j)*b[j];
		ret2[1]+=j*b[j];
	}
	for(ll i=3;i<=n;i+=2)
	{
		s[i]=s[i-2]-a[i-2]-a[i-1]-b[i-2]-b[i-1];
		ret1[i]=ret1[i-2]-a[i-1]-2*s[i]-(2*n-2*i+4)*b[i-1]-(2*n-2*i+5)*b[i-2];
		ret2[i]=ret2[i-2]-b[i-2]-2*s[i]-(2*n-2*i+5)*a[i-1]-(2*n-2*i+2)*a[i]-2*b[i-1];
		dw[i]=dw[i-2]+(2*i-6)*a[i-2]+(2*i-5)*b[i-2]+(2*i-4)*b[i-1]+(2*i-3)*a[i-1];
	}
	for(ll i=1;i<=n;i+=2)
	{
		ans=max(ans,dw[i]+max(ret1[i],ret2[i])+(2*i-2)*s[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```
注：各数组的计算可以有多种递推方法，上述代码采取的是顺推，逆推也是正确的做法。

---

## 作者：liangjindong0504 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1016C)

[CF 题目传送门](https://codeforces.com/contest/1016/problem/C)

难度：*1800

本人一开始把题目看错了，把时间看成 $1$ 到 $2n$ 了，不太想改，减一个总和就行。（如果你不理解，后面会说）
### 题目大意
有一个大小为 $2 \cdot n$ 的地方，你每次可以往四个方向走一次，花费 $1$ 点时间。如果你在第 $t$ 秒到达 $a_{i,j}$，你可以获得 $t \cdot a_{i,j}$。初始时你在 $a_{1,1}$，需要每个方格恰走一次。最大化得分。（初始时间为 $0$，这就是我看错的地方）。
### 思路分析
首先注意到“每个方格恰走一次”这个信息，可知，有以下几种走法。

**第一种**：

以 $n=6$ 为例。
```
0 图
1  2  3  4  5  6
12 11 10 9  8  7

1 图
1  4  5  6  7  8
2  3  12 11 10 9

2 图
1  4  5  8  9  10
2  3  6  7  12 11
```
注意到，就是前面偶数个列用蛇形走法，后面从第一行走到底再从第二行回来。

注：以下的“位”，是以 0 图为标准的“位”，同时先不考虑权值，仅考虑通过时间。（第二种也是）

首先，我们可以看到，1 图与 0 图中，第 2 位到第 10 位都加了两次。再看 2 图与 1 图，第 4 位到第 8 位增加了两次。（有没有看出什么？）很明显，第 $i$ 幅图所增加的地方即为 $2i \sim 2(n-i)$。（其实可以证明，比较简单）

其次，若减去不变的数字，是不是还剩下两个数字特别麻烦？那我们单独拿出来看看。
```
12 11 --> 2 3
12 11 --> 6 7
```
发现了吗？每一次，减掉的数时间都是 $2n,2n-1$，而第 $i$ 幅图这两个数的时间则是 $4i-2,4i-1$。继续看到，处理的是哪几个方格呢？通过观察，发现正好是 $a_{2,2i-1},a_{2,2i}$。

于是，我们可以先预处理第 0 幅图，然后一步一步往下递推。综上，若以 $dp$ 为图的权值，则 $dp_i=dp_{i-1}+2 \cdot sum(2i,2(n-i))-2n \cdot a_{2,2i-1}-(2n-1) \cdot a_{2,2i}+(4i-2) \cdot a_{2,2i-1}+(4i-1) \cdot a_{2,2i}$。求和可以使用前缀和。

**第二种**：

还是使用图片来说明。不过这次，我们将 $n$ 换成 $7$，更好理解。
```
0 图
1  14 13 12 11 10 9
2  3  4  5  6  7  8

1 图
1  4  5 14 13 12 11
2  3  6  7  8  9 10

2 图
1  4  5  8  9 14 13
2  3  6  7 10 11 12
```
这一种情况，其实就是前面奇数个列蛇形前进，然后第二行走到底再从第一行走回来。

有了第一种情况，第二种情况与前面类似，就不推了，由读者自行推导。

经过推导，可知第 $i$ 幅图，第二种情况增加的（即乘 2 的），是第 $2i+2 \sim 2(n-i)$。而剩下的两格，则是：
```
2n 2n-1 --> 4 5
2n 2n-1 --> 8 9
```
以此类推。

根据此，可得它变成了 $4i,4i+1$，而变换的地方是 $a_{1,2i},a_{1,2i+1}$。

于是，若新建一个数组 $ds$ 用来存放，先预处理出第 0 幅图，然后递推。$ds_i=ds_{i-1}+2 \cdot sum(2i+1,2(n-i))-2n \cdot a_{1,2i}-(2n-1) \cdot a_{1,2i+1}+4i \cdot a_{1,2i}+(4i+1) \cdot a_{1,2i+1}$。求和依然靠前缀和。

最后这些情况取最大值即可。
### 完整代码
忠告：**不开 long long 见祖宗！！！**

哦还有一个，就是开头讲的那个错误导致最后必须减掉一个总和。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll a[3][300010];
ll s1[600010],s2[600010];
ll dp[300010],ds[300010],ans;
//前缀和 
ll sum_1(int l,int r){
	return s1[r]-s1[l-1];
}
ll sum_2(int l,int r){
	return s2[r]-s2[l-1];
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=n;j++) cin>>a[i][j];
	}
	//预处理 
	for(ll i=1;i<=n;i++){
		dp[0]+=i*a[1][i];
		s1[i]=s1[i-1]+a[1][i];
	}
	for(ll i=n;i;i--){
		dp[0]+=(2*n-i+1)*a[2][i];
		s1[2*n-i+1]=s1[2*n-i]+a[2][i];
	}
	s2[1]=a[1][1],s2[2]=a[1][1]+a[2][1];
	ds[0]=a[1][1]+2*a[2][1];
	for(ll i=2;i<=n;i++){
		ds[0]+=(i+1)*a[2][i];
		s2[i+1]=s2[i]+a[2][i];
	}
	for(ll i=n;i>=2;i--){
		ds[0]+=(2*n-i+2)*a[1][i];
		s2[2*n-i+2]=s2[2*n-i+1]+a[1][i];
	}
	ans=max(dp[0],ds[0]);
	//第一种 
	for(ll i=1;i<=n/2;i++){
		dp[i]=dp[i-1]+2*sum_1(2*i,2*(n-i));
		dp[i]=dp[i]-2*n*a[2][2*i-1]-(2*n-1)*a[2][2*i];
		dp[i]+=(4*i-2)*a[2][2*i-1]+(4*i-1)*a[2][2*i];
		ans=max(ans,dp[i]);
	}
	//第二种 
	for(ll i=1;i<=(n-1)/2;i++){
		ds[i]=ds[i-1]+2*sum_2(2*i+2,2*(n-i));
		ds[i]=ds[i]-2*n*a[1][2*i]-(2*n-1)*a[1][2*i+1];
		ds[i]+=4*i*a[1][2*i]+(4*i+1)*a[1][2*i+1];
		ans=max(ans,ds[i]);
	}
	cout<<ans-s1[2*n];//减掉总和
	return 0;//功德圆满
}
```
码风较丑，勿喷。

这应该是 div 2 最难的 C 了吧。（逃）

---

## 作者：MspAInt (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1016C)

duel bot.duel bot.duel bot.

说实话这个题蛮恶心的。

显然行走路线只有 $n$ 种，即对于第 $1$ 列至第 $i$ 列蛇行的前进（样例 2），对于 $i+1$ 至 $n$ 列，向前走到底再走回来（样例 1）。

首先枚举 $i$，然后考虑怎么统计。

对于左边的蛇形，直接一步一步往后模拟即可。

但是右边比较麻烦，这边我预处理出了上下两行的带权前后缀 $A1,B1,A2,B2$ 和以及原前缀和 $A,B$。前缀第 $i$ 项的权为 $(i-1)\times a_i$，后缀则是 $(n-i)\times a_i$，第二行同理。

此时可以统计一部分右侧答案：

![](https://cdn.luogu.com.cn/upload/image_hosting/3cibusb8.png)

我们再加上 $(B_n-B_i)\times i$：

![](https://cdn.luogu.com.cn/upload/image_hosting/u9fy1b3i.png)

再加上走到第一行的贡献 $(A_n-A_i)\times(n+i)$：

![](https://cdn.luogu.com.cn/upload/image_hosting/32vfanlr.png)

其实这个过程就是把系数递增的部分预处理，枚举时将之前在左边走的时间贡献到右边，可以自行模拟一下。

这是 $i$ 为奇数的情况，为偶数时的计算方式也没啥区别。$i=0$ 单独计算，记得开 `long long`。

Code:

```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,a[N],b[N],res;
long long l,r,ans,A1[N],B1[N],A2[N],B2[N],A[N],B[N];
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)A1[i]=A1[i-1]+1ll*(i-1)*a[i],B1[i]=B1[i-1]+1ll*(i-1)*b[i];
    for(int i=n;i>=1;i--)A2[i]=A2[i+1]+1ll*(n-i)*a[i],B2[i]=B2[i+1]+1ll*(n-i)*b[i];
    for(int i=1;i<=n;i++)A[i]=A[i-1]+a[i],B[i]=B[i-1]+b[i];
    ans=A1[n]+B2[1]+B[n]*n;
    // printf("%lld\n",ans);
    for(int i=1;i<=n;i++){
        if(i&1)l+=1ll*a[i]*(i*2-2)+1ll*b[i]*(i*2-1);
        else l+=1ll*a[i]*(i*2-1)+1ll*b[i]*(i*2-2);
        if(i&1)r=B1[n]-B1[i]+(B[n]-B[i])*i+A2[i+1]+(A[n]-A[i])*(n+i);
        else r=A1[n]-A1[i]+(A[n]-A[i])*i+B2[i+1]+(B[n]-B[i])*(n+i);
        // printf("%lld %lld\n",l,r);
        if(ans<l+r)res=i,ans=l+r;
    }
    printf("%lld\n",ans);
    system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/123828064)

---

## 作者：forest114514 (赞：0)

# Vasya And The Mushrooms 题解
### [题目传送门](https://www.luogu.com.cn/problem/CF1016C])
------------
# 题目翻译：

Vasya 住在森林里，附近有一个会长蘑菇的空地。这个空地被分成两行，每行分为 $n$ 个连续的格子。 Vasya 知道每分钟每个格子里能长多少个蘑菇。他要花一分钟从一个格子走到相邻的格子上，并且他不能离开空地。（我们称两个格子相邻，当且仅当它们有公共边）当 Vasya 进入一个格子时，他会马上收集那个格子里的所有蘑菇。

 Vasya 从左上角的格子开始收集蘑菇。因为他等不及蘑菇生长了，所以每分钟内他必须移动到一个相邻格子。他想每个格子都恰好走一遍并且最大化他所收集的蘑菇数量。一开始所有格子都没有蘑菇。  Vasya 也不一定要回到开始的格子。 帮帮 Vasya  计算出他能收集到的最大蘑菇数量。
 
------------

# 分析： 
 这道题的可能走法一共是 $n$ 种，如果暴力去模拟一遍每一种走法时间复杂度是 $O(N^2)$ ，对于 $3\times 10^5$ 的数据显然超时了。我们可以考虑优化每一次答案的查找，我们记录三个前缀和数组 $sum[2][N],suml[2][N],sumr[2][N]$ 分别记录朴素前缀和，从左至右走能采蘑菇数的前缀和以及从右至左走能采蘑菇数的前缀和，则蓝色部分的采集蘑菇数为：

$(i-1)\times(sum[i\bmod2][n]-sum[i\bmod2][i])
+suml[i\bmod2][n]-suml[i\bmod2][i])
+(n+i-1)\times(sum[(i+1)\bmod2][n]-sum[(i+1)\bmod2][i])+(sumr[(i+1)\bmod2][n]-sumr[(i+1)\bmod2][i])
$。

再用一个 $cnt$ 记录蛇形路径(图中红色划线路径)一共采集的蘑菇数，这样就能 $O(1)$ 计算每一种走法，时间与空间复杂度均为 $O(N)$ 。

![一个模拟图](https://cdn.luogu.com.cn/upload/image_hosting/xt7my19s.png)

 细节： 
 1. 十年 OI 一场空，不开 longlong 见祖宗。

 2. 计算情况时应从 $0$ 到 $n-1$ 枚举，因为有可能不走蛇形直接一去一回就行了。

------------
# CODE:
```cpp
//蒟蒻一枚
#include<bits/stdc++.h>
#define re register
#define il inline
using namespace std;
typedef long long LL;
inline LL read(){
	LL x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=getchar();
	return x*f;
}
const int N=3e5+100;
LL n,num[N][2];
LL sum[2][N],suml[2][N],sumr[2][N];
LL cnt=0,maxx=-1,now;
int main(){
	n=read();
	num[0][0]=num[0][1]=0;
	for(re int i=1;i<=n;++i){
		num[i][0]=read();
		sum[0][i]=sum[0][i-1]+num[i][0];
		suml[0][i]=suml[0][i-1]+LL(i*num[i][0]);
		sumr[0][i]=sumr[0][i-1]+LL((n-i+1)*num[i][0]);
	}
		
	for(re int i=1;i<=n;++i){
		num[i][1]=read();
		sum[1][i]=sum[1][i-1]+num[i][1];
		suml[1][i]=suml[1][i-1]+LL(i*num[i][1]);
		sumr[1][i]=sumr[1][i-1]+LL((n-i+1)*num[i][1]);
	}
	for(re int i=0;i<n;++i){
		cnt+=(2*i-2)*num[i][(i+1)%2]+(2*i-1)*num[i][i%2];   
		now=cnt+(i-1)*(sum[i%2][n]-sum[i%2][i])+(n+i-1)*(sum[(i+1)%2][n]-sum[(i+1)%2][i])+(suml[i%2][n]-suml[i%2][i])+(sumr[(i+1)%2][n]-sumr[(i+1)%2][i]);
		maxx=max(now，maxx);
	}
	printf("%lld\n",maxx)；
	return 0；
}

```
 **Tips：请不要直接 copy 代码。**


---

## 作者：yuheng_wang080904 (赞：0)

## 题意

给定 $n$ 与数组 $a$ 和 $b$。其中 $a_i(1 \le i \le n)$ 表示第一行第 $i$ 个格子一分钟能生长的蘑菇，$b_i(1 \le i \le n)$ 表示第二行第 $i$ 个格子一分钟能生长的蘑菇。一个人在这两行格子的左上角，他没移动到一个相邻的各自需要花一分钟，每次移动后他就会把那个格子里的蘑菇采掉。这个人希望每个格子仅走到一次，请帮他求出能采到的最多蘑菇数。

## 思路

我们来考虑一下那个人做的路线，一共是 3 种情况。大家可以画图来理解我的文字说明。

看样例，给出了我们两种极端情况，第一种是先往右走，到最后往下，然后往左走到底。我们可以证明如果一开始就往右走只有这一种情况可以成立：如果你在中间某一列向下走，如果往左走那么右边一部分就无法走到，如果往右走那下面一行的左边一部分就无法走到。

第二种是先往下走，再往右走，再往上走，再往左走，再往下走……每次都是走一格，直到最右边一列全部走完为止，像这样不断绕弯弯，这种方法是肯定没有问题的。

第三种便是两种的结合，我们可以考虑先向第二种一样绕弯弯，然后再用第一种走到底转弯再走到底。但这一种也分为两种可能，第一种即转弯是往上转，第二种则是往下转，写代码的时候要注意判别 $i \equiv 0/1(\operatorname{mod} 2)$ 来判断上下转。

把每种情况都试一遍，时间复杂度为 $O(n)$。为了做每种情况时时间复杂度为 $O(1)$，注意要预处理。

对于预处理大家可以有不同的思路，只要能表示出最后的结果即可，我预处理的可能有些多。我一共预处理了这些，$a$ 数组与 $b$ 数组的元素前缀和与后缀和，$a$ 数组与 $b$ 数组的元素及对应下标乘积的前缀和与后缀和。

## 代码

下面放上我的代码，请大家理解思路，我的代码及预处理若可改进，可留言！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,res,n,a[300005],b[300005],c[300005];
long long s11[300005],s21[300005],s12[300005],s22[300005];
long long r11[300005],r21[300005],r12[300005],r22[300005];
int main(){ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++){
	if(i%2==0)c[i]=b[i]*(2*i-2)+a[i]*(2*i-1);
	else c[i]=a[i]*(2*i-2)+b[i]*(2*i-1);
    }
    for(int i=1;i<=n;i++)s11[i]=a[i]+s11[i-1];
    for(int i=1;i<=n;i++)s21[i]=b[i]+s21[i-1];
    for(int i=n;i>=1;i--)s12[i]=a[i]+s12[i+1];
    for(int i=n;i>=1;i--)s22[i]=b[i]+s22[i+1];
    for(int i=1;i<=n;i++)r11[i]=a[i]*(i-1)+r11[i-1];
    for(int i=1;i<=n;i++)r21[i]=b[i]*(i-1)+r21[i-1];
    for(int i=n;i>=1;i--)r12[i]=a[i]*(n-i)+r12[i+1];
    for(int i=n;i>=1;i--)r22[i]=b[i]*(n-i)+r22[i+1];
    ans=max(ans,r11[n]+r22[1]+n*s22[1]);
    for(int i=1;i<=n;i++){
	res+=c[i];
	if(i%2)ans=max(ans,res+r21[n]-r21[i]+(s21[n]-s21[i])*i+r12[i+1]+s12[i+1]*(n+i));
	else ans=max(ans,res+r11[n]-r11[i]+(s11[n]-s11[i])*i+r22[i+1]+s22[i+1]*(n+i));
    }
    cout<<ans<<endl;
    return 0;
}
```


---

