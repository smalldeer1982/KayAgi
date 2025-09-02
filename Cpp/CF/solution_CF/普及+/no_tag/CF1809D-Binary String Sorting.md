# Binary String Sorting

## 题目描述

You are given a binary string $ s $ consisting of only characters 0 and/or 1.

You can perform several operations on this string (possibly zero). There are two types of operations:

- choose two consecutive elements and swap them. In order to perform this operation, you pay $ 10^{12} $ coins;
- choose any element from the string and remove it. In order to perform this operation, you pay $ 10^{12}+1 $ coins.

Your task is to calculate the minimum number of coins required to sort the string $ s $ in non-decreasing order (i. e. transform $ s $ so that $ s_1 \le s_2 \le \dots \le s_m $ , where $ m $ is the length of the string after applying all operations). An empty string is also considered sorted in non-decreasing order.

## 说明/提示

In the first example, you have to remove the $ 1 $ -st element, so the string becomes equal to 00.

In the second example, the string is already sorted.

In the third example, you have to swap the $ 2 $ -nd and the $ 3 $ -rd elements, so the string becomes equal to 0011.

In the fourth example, you have to swap the $ 3 $ -rd and the $ 4 $ -th elements, so the string becomes equal to 00011101, and then remove the $ 7 $ -th element, so the string becomes equal to 0001111.

In the fifth example, you have to remove the $ 1 $ -st element, so the string becomes equal to 001101, and then remove the $ 5 $ -th element, so the string becomes equal to 00111.

In the sixth example, the string is already sorted.

## 样例 #1

### 输入

```
6
100
0
0101
00101101
1001101
11111```

### 输出

```
1000000000001
0
1000000000000
2000000000001
2000000000002
0```

# 题解

## 作者：听取MLE声一片 (赞：8)

排序的结果肯定是一串 $0$ 后面再加上一串 $1$。

注意到两个操作的代价都很大且差很小，所以我们首先要让操作数最小，在此条件下让交换的次数最多。

考虑枚举交界处，交界处左的全部改为 $0$，交界处右全部改为 $1$，不同的直接删除。因为如果这些不同的不删除，必然会交换移动好几次，不能满足操作次数最小。

然后就交界处的两个数，如果交界处上的两个数分别为 $1$ 和 $0$，这时是可以交换的，记录交换的代价。

维护前缀和后缀和计算每一个位置即可。

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
const int N=3e5+10;
const int inf=1e18;
const int P=1000000000000ll;
const int Q=1000000000001ll;
int n,a[N],b[N];
char str[N];
signed main()
{
	int T=read();
	while(T--){
		scanf("%s",str+1);
		n=strlen(str+1);
		for(int i=1;i<=n;i++){
			a[i]=a[i-1];
			if(str[i]=='1')
				a[i]++;
		}
		for(int i=n;i>=1;i--){
			b[i]=b[i+1];
			if(str[i]=='0')
				b[i]++;
		}
		int ans=inf;
		for(int i=0;i<=n;i++)
			ans=min(ans,(a[i]+b[i+1])*Q);
		for(int i=1;i<=n;i++)
			if(str[i]=='1'&&str[i+1]=='0')
				ans=min(ans,P+(a[i-1]+b[i+2])*Q);
		cout<<ans<<'\n';
		for(int i=0;i<=n+1;i++)
			a[i]=b[i]=0;
	}
	return 0;
}

```

---

## 作者：Esucu (赞：6)

UPD:2024.6.8  

****看到本题大家用的都是贪心，这里提供一种动态规划的做法，比较易写。****  

定义状态：  
$f_{i,0}$ 表示处理到原数组的第 $i$ 位，保证经过处理后使得数组的第 $1$ 位到第 $i$ 位单调不递减，且末尾没有 $1$ 的最小花费。  
$f_{i,1}$ 保证末尾只有一个 $1$ 的最小花费，其他定义与 $f_{i,0}$ 一样。  
$f_{i,2}$ 保证末尾有多个 $1$ 的最小花费，其他定义与 $f_{i,0}$ 一样。 

于是转移方程就很好想了，不过因为比较长，具体在代码中体现。 
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5,p=1e12,q=1e12+1;
int t,f[N][3],a[N],n;
string s;
signed main(){
	scanf("%lld",&t);
	while(t--){
		cin>>s; n=s.size();
		for(int i=1;i<=n;i++) a[i]=s[i-1]-'0';
		for(int i=1;i<=n;i++){//转移方程就是本循环内的代码 
			if(a[i]){
				f[i][0]=f[i-1][0]+q;	
				f[i][1]=f[i-1][0];
				f[i][2]=min(f[i-1][1],f[i-1][2]);
			}else{
				f[i][0]=f[i-1][0];
				f[i][1]=f[i-1][1]+p;//实现交换操作的关键 
				f[i][2]=f[i-1][2]+q;	
			}
		}
		printf("%lld\n",min(min(f[n][0],f[n][1]),f[n][2]));
	}
	return 0;
} 
```
这样已经可以通过本题了，~~~~不过无聊的人也可以继续看下去。~~~~

我们发现，数组是可以滚动的。

于是，就有了下面这份 $O(1)$ 空间的代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=1e12,q=1e12+1;
int t,f[3],a,n,x,y,z;
char ch;
signed main(){
	scanf("%lld",&t);
	ch=getchar();
	while(t--){
		while(1){
			ch=getchar();
			if(ch<'0'||ch>'9') break;
			a=ch-'0';
			x=f[0],y=f[1],z=f[2];
			f[0]=(a?x+q:x);
			f[1]=(a?x:y+p);
			f[2]=(a?min(y,z):z+q);
		}
		printf("%lld\n",min(min(f[0],f[1]),f[2]));
		f[0]=f[1]=f[2]=0;
	}
	return 0;
} 
```
当前最短代码。

---

## 作者：CuCl4Loliko (赞：4)

## 比较水的题目，场上一眼出答案，感觉没C难

### 题目大意
- 给你 $n$ 个 $01$ 串，总长度不超过 $3e5$
- 现在有两种操作，一种是从串中删除一个字符，代价为 $1e12+1$ ，另一种是交换相邻的两个字符，代价为 $1e12$。
- 求把给定串变为一个单调不减的序列的最小花费。


------------
把序列变为单调不减，事实上就是把序列变为左边全为 $0$ ，右边全为 $1$ 的序列。考虑枚举，我们可以枚举每一个断点，并 $O(1)$ 地算出以此作为断点的花费，更新答案。 

将一个点的左边全部变为 $0$ ，右边全部变为 $1$ ，其实就是将左边的 $1$ 和右边的 $0$ 全部删除，代价为左边 $1$ 的数量加右边 $0$ 的数量，可以在开始时将串扫两遍，预处理出每个点左右的 $01$ 数量。

接下来考虑交换操作的影响。很显然，当断点右边为 $0$ ，左边为 $1$ 时，交换操作比删除这两个字符的花费更优。也易证明，当需要删除的字符达到三个及以上时，交换的花费就不比删除更优了。

代码中的操作就是先预处理扫两边，然后枚举断点，再在每次枚举时加入交换的特判

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=4e5+5,INF=5e18,base=1e12+1;
int a[maxn],b[maxn];

signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		for(int i=0;i<=(int)s.size()+1;i++)//多测不清空，保龄两行泪
		{
			a[i]=0;
			b[i]=0;
		}
		for(int i=0;i<(int)s.size();i++)//预处理每个点左边1的数量
		{
			if(i==0)
			{
				a[i]=(s[0]=='0'?0:1);
				continue;
			 }
			else a[i]=a[i-1];
			if(s[i]=='1') a[i]++;
		}
		for(int i=(int)s.size()-1;i>=0;i--)//预处理每个点右边0的数量
		{
			b[i]=b[i+1];
			if(s[i]=='0') b[i]++;
		}
		int ans=INF;
		ans=(b[0]*base);
		for(int i=0;i<(int)s.size();i++)//枚举断点与特判
			ans=min(ans,(a[i]+b[i+1])*base-(s[i]=='1'&&s[i+1]=='0'?base+1:0));
		cout<<ans<<endl;
	}
	return 0;
}

```

赛时的代码，有点丑。（忘了处理边界吃了六发罚时，破大防）

感谢管理大大的审核！Orz

---

## 作者：xujingyu (赞：1)

在这题上挂得很惨，好累。

## 题面:

给出一个**二进制**字符串 $s$，可以对字符串做以下操作：

* 交换两个相邻的元素，消耗 $10^{12}$。
* 删除一个元素，消耗 $10^{12}+1$。

~~（有必要吗？整这么大）~~

要求把 $s$ 排成元素不下降的状态，求最小消耗。

## 解答

把一个字符串排序完后，必定会是左边一堆 $0$，右边一堆 $1$。如：

`00101101`排序完后是`0001111`。

$0$ 和 $1$ 的分界点就是第 $3$ 个位置和第 $4$ 个位置之间。

现在就要枚举这个分界点。

再以这个数据为例，枚举分界点（枚举到的那个地方是最后一个 $0$ 的位置），枚举到第 $3$ 个位时先计算消耗（非当前位置最小消耗），将第 $3$ 个位左边所有的 $1$ **删除**（包括自己），右边所有的 $0$ 删除。计算消耗。目前消耗为 $3 \times 10^{12}$。

> 为了知道左边 $1$ 的数量、右边 $0$ 的数量，还要在输入后使用两个数组 $\texttt l1[]$ 和 $\texttt r0[]$，以前缀和与后缀和的方式计算出来。

但显然不一定是最小消耗，因为**交换**可以使消耗最小。所以再判断，若当前这个是 $1$ 并且下一个是 $0$（即可以交换），那么就交换。将多加上的消耗减去。减多少?

因为是多算了两个删除花费，即 $2 \times (10^{12}+1)$，交换会消耗 $10^{12}$，所以要减去

$2 \times (10^{12}+1)-10^{12}=10^{12}+2$。

当前消耗为最小消耗 $2 \times 10^{12} + 1$。

减完后全局取 $\min$ 最小值。

## code:

```php
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <set>
#include <map>
using namespace std;

int t,l1[400001],r0[400002];
string s;
long long huge = 1e12;

signed main()
{
	scanf("%d",&t);
	while(t--)
	{
		cin >> s;
		int len = s.size();
		for(int i = 0;i <= len + 1;i++) l1[i] = r0[i] = 0;//要记得清空
		if(s[0] == '1') l1[0] = 1;//初始化左边第一个
		for(int i = 0;i < len;i++)
		{
			if(i > 0)//第0个已经初始化了
			{
				l1[i] = l1[i - 1];//先赋值
				if(s[i] == '1') l1[i]++;//若当前这个是1,那么更新left one number
			}
			
			int j = len - i - 1;//为了省一个循环,这里直接状态转移right zero number
			r0[j] = r0[j + 1];//同上
			if(s[j] == '0') r0[j]++;
		}
		//for(int i = 0;i < len;i++) printf("%d %d\n",l1[i],r0[i]);
		long long ans = 0,minn = r0[0] * (huge + 1);//初始化,注意minn的赋值,就是把所有0删除
		for(int i = 0;i < len;i++)
		{
			ans = (l1[i] + r0[i + 1]) * (huge + 1);//在当前断点删除所有左边的1,右边的0
			if(s[i] == '1' && s[i + 1] == '0') ans -= (huge + 2);//若可以交换,减去多算的
			minn = min(minn,ans);//更新最小值
		}
		printf("%lld\n",minn);
	}
	return 0;
}
```


---

## 作者：w9095 (赞：1)

[CF1809D Binary String Sorting](https://www.luogu.com.cn/problem/CF1809D)

贪心。由于每次操作的代价都很大，所以需要优先减少操作次数，然后尽量多使用交换操作。

易得交换操作最多只会发生一次，因为每次交换操作只能消除一个逆序对，当存在两个或多个逆序对时，可以通过删除操作来减少更多的逆序对，减少操作次数。当只存在一个逆序对时，自然也只能交换一次。

然后，由于排序结束后 $0$ 和 $1$ 之间必然有一条分界线，左边是 $0$，右边是 $1$。我们考虑枚举这条分界线，在分界线左边的 $1$ 需要删除，在分界线右边的 $0$ 需要删除。在分界线的同侧进行交换操作是无意义的，因为这并不会减少左边的 $1$ 或右边的 $0$。

如果一次交换操作能恰好把左边的 $1$ 换到右边，右边的 $0$ 换到左边，那么可以优先执行这个交换操作，我们发现这种情况只会在分界线左右第一个元素发生，正好印证了上文交换操作最多只会发生一次。所以，当分界线左边第一个元素为 $1$，右边第 $1$ 个元素为 $0$ 时，需要进行一次交换操作，从而减少两次修改操作。

如果分界线不满足左边第一个元素为 $1$，右边第 $1$ 个元素为 $0$ 时，其实也不用处理分界线左右第一个元素。因为无论是 $00$ 还是 $11$ 还是 $01$，其实都是符合条件的数对，并不会影响结果。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,sf=1e12,df=1e12+1;
char str[400000];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long s0=0,s1=0,z=0,y=0,ans=1e18;
	   	scanf("%s",str+1);
	   	n=strlen(str+1);
	   	for(int i=2;i<=n;i++)
	   	    if(str[i]=='0')y++;
	   	for(int i=1;i<=n-1;i++)
	   	    {
	   	    if(str[i+1]=='0')y--;
			if(str[i-1]=='1')z++;	
	   	    if(str[i]=='1'&&str[i+1]=='0')ans=min(ans,(z+y)*df+sf);
	   	    else ans=min(ans,(z+y)*df);
		    }
		if(ans==1e18)printf("0\n");
		else printf("%lld\n",ans);
	   }
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/120401822)

---

## 作者：TruchyR (赞：0)

## Part 1 思路
看到特殊的花费可知，我们需要在**操作总数**最小的情况下**使得删除次数最小**。  
易得删除操作比交换操作对于答案更有利，以下是简单说明：  
- 一次交换操作会把 $1\ 0$ 交换为 $0\ 1$。  
- 但可以使用删除操作把 $1\ 0$ 删除为 $0$ 或 $1$，明显更优。  

所以我们先考虑只有删除操作时怎么做：  
- 为了方便，我们可以把字符串按照 $0/1$ 分成 $m$ 个字符串。
$$\color{black}00101101\rightarrow00\ |\ 1\ |\ 0\ |\ 11\ |\ 0\ |\ 1(m=6)$$
$$\color{black}1001101\rightarrow1\ |\ 00\ |\ 11\ |\ 0\ |\ 1(m=5)$$
- 最终排序的字符串必然是左边全是 $0$，右边全是 $1$ 的。  
- 考虑枚举一个分割点，把分割点**左侧的** $1$ 全部删去，**右侧的** $0$ 全部删去。  
- 分割字符串可以 $O(n)$ 完成，计算这些贡献可以 $O(m)$ 完成。

我们知道最小操作数后，就需要从那些最小方案中寻求优化了：  
- 先看几个最小方案：（红色为分割点，蓝色为删除的串）
$$\color{black}00101101\rightarrow00\ |\ \color{blue}1\color{black}\ |\ 0\ \color{red}|\color{black}\ 11\ |\ \color{blue}0\color{black}\ |\ 1(m=6)$$
$$\color{black}1001101\rightarrow\color{blue}1\color{black}\ |\ 00\ \color{red}|\color{black}\ 11\ |\ \color{blue}0\color{black}\ |\ 1(m=5)$$
- 发现这些方案的分割点**左侧是** $0$，**右侧是** $1$，说明如下：
- 如果一个最小方案的分割点左侧是 $1$，右侧是 $0$，那么可以把分割点左移使得左侧的 $1$ 不需要删除。
- 那如何把一些删除换成交换呢？  
- 左侧删除的第一串 $1$ 在只需要 $1$ 次交换的情况下可以替换成交换操作。
- 右侧删除的第一串 $0$ 在只需要 $1$ 次交换的情况下可以替换成交换操作。
- 显然，这两个优化无法同时进行。
- 综上，判断一下分割点两侧的串长度是否为 $1$ 即可。

## Part 2 代码
```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
#define int long long
#define MX 300005
#define INF 1000000000000000000ll
using namespace std;
const int CHECK=0,FIL=0;
int T,n,m,p,q,mn,res,a[MX],s[MX];string S;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	FRE freopen(".in","r",stdin);
	FRE freopen(".out","w",stdout);
	cin>>T;while(T--){cin>>S;
		m=1;q=p=a[1]=0;n=S.size();mn=res=INF;
		for(int i=1;i<=n;i++) s[i]=S[i-1]-'0';
		//分割字符串
		//这里的方式可能会在开头产生一个长度为0的串
		//但是这对答案没有影响
		for(int i=1;i<=n;i++){
			if(s[i]==s[i-1]) a[m]++;
			else a[++m]=1;
		}a[m+1]=a[m+2]=a[m+3]=0;
		//先记录分割点在左侧时右侧要删除几个1
		for(int i=3;i<=m;i+=2) p+=a[i];
		//将分割点右移，计算最小值
		for(int i=1;i<=m;i++){
			if(i>1 && i%2) p-=a[i];
			if(!(i%2)) q+=a[i];
			mn=min(mn,p+q);
		}p=q=0;
		//再算一遍
		for(int i=3;i<=m;i+=2) p+=a[i];
		for(int i=1;i<=m;i++){
			if(i>1 && i%2) p-=a[i];
			if(!(i%2)) q+=a[i];
			if(p+q<=mn){
			    //如果是最小方案，就考虑能否优化
				int w=(p+q)*1000000000001;
				if(a[i]==1) res=min(res,w-a[i-1]);
				if(a[i+1]==1) res=min(res,w-a[i+2]);
				res=min(res,w);
			}
		}//输出
		cout<<res<<'\n';
	}return 0;
}
```


---

## 作者：NightmareAlita (赞：0)

## 简要题意

给定一个 $01$ 串，要求你交换相邻两个数或删掉一个数，使得该串单调不降。其中交换相邻两个数的代价是 $10^{12}$，删除的代价是 $10^{12} + 1$，求最小代价。

## 策略分析

本题需要我们发现一个重要的性质，因为我们需要把数列变成形如 `00000...11111` 的形式，所以必然存在一个分界点，这个分解点的两边的数可能是 $10$ 或 $01$。现在假设我们知道这个分界点在哪里了，那么我们就要把分界点左边的 $1$ 想办法弄到右边，或者直接扔掉。我们发现，除非是 $10$ 情况下的分界点左边的那个 $1$，其余的 $1$ 删掉的代价一定比一次一次交换过来少，因为删除只需要一次，而交换至少需要两次，显然 $2 \times 10^{12} > 10^{12} + 1$，处理分界点右边的 $0$ 同理。那么我们只需要枚举这个分界点在哪里，并判断分界点两边的数是 $10$ 还是 $01$ 即可，如果是 $10$ 还要额外判断一下转更优还是不转更优，顺序枚举一遍即可得解。

具体来讲，我们对于每个位置，预处理出其前面（包括自己在内）有多少个 $1$，后面有多少个 $0$，枚举到每一个位置的时候用预处理出的值乘以代价即可，注意预处理的前后缀数组要多组数据清空。

时间复杂度 $O(Tn)$。

## 参考代码

``` cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define LL long long
using namespace std;

namespace SHAWN {
    const LL N = 3e5 + 7, C = 1e12 + 1;
    LL q[N], h[N];
    int T;
    signed work()
    {
        cin >> T;
        while (T--) {
            string s; cin >> s;
            int len = s.length();
            s = ' ' + s;
            LL ans = 1e18;
            for (int i = 1; i <= len; ++i) {
                q[i] = q[i - 1];
                if (s[i] == '1') { ++q[i]; }
            }
            for (int i = len; i >= 1; --i) {
                h[i] = h[i + 1];
                if (s[i] == '0') { ++h[i]; }
            }
            for (int i = 0; i <= len; ++i) {
                if (s[i] == '1' && s[i + 1] == '0') {
                    ans = min(ans, q[i - 1] * C + h[i + 2] * C + C - 1);
                }
                ans = min(ans, q[i] * C + h[i + 1] * C);
            }
            cout << ans << '\n';
            for (int i = 0; i <= len; ++i) { q[i] = h[i] = 0; }
        }
        return 0;
    }
}

signed main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：vegetable_chili (赞：0)

贪心题，~~很水~~。

由于最后的字符串要满足单调递增，所以最后的结果肯定是一些 $0$ 加上一些 $1$，否则就一定会出现至少一个 $10$，这样就不满足条件了。

考虑**枚举交界点**，如果交界处左边是 $1$，右边是 $0$，那就可以进行**交换**操作。其他情况下还不如直接**删除**。

对于交界处两边，为了更快速地计算 $0$ 和 $1$ 的个数，我们可以用**前缀和**与**后缀和**统计，这样的效率会更高。

最后的答案取**最小值**即可。

```cpp
#include<iostream>
#include<string>
#define int long long
using namespace std;
const int Length=3e5+10;
const int cost=1e12+1;
int T,ans,one[Length],zero[Length];
string s;
signed main(){
	cin>>T;
	while(T--){
		cin>>s;
		zero[s.size()+1]=0;
		ans=1e18;
		for(int i=1;i<=s.size();i++){
			one[i]=one[i-1];
			if(s[i-1]=='1')one[i]++;//1的前缀和
		}
		for(int i=s.size();i>0;i--){
			zero[i]=zero[i+1];
			if(s[i-1]=='0')zero[i]++;//0的后缀和
		}
		for(int i=1;i<=s.size();i++){
			ans=min(ans,min((one[i]+zero[i+1])*cost,(one[i-1]+zero[i])*cost));//不进行交换，直接将左边的1和右边的0删除
		}
		for(int i=2;i<=s.size();i++){
			if(s[i-2]=='1'&&s[i-1]=='0'){
				ans=min(ans,cost*(zero[i+1]+one[i-2]+1)-1);//交换区间交界处的0和1
			}
		}
		cout<<ans<<"\n";
	}
}
```


---

## 作者：2018ljw (赞：0)

题意：给定一个 $01$ 串，一次可以交换相邻两个字符或删去一个字符。要求让所有 $0$ 在所有 $1$ 前面。最小化操作次数的前提下最小化删除操作的次数。

根据冒泡排序的流程可知，一次交换会使逆序对减一。

考虑每个 $0$，其交换次数为其产生的逆序对个数。那么一旦它产生逆序对大于 $1$，显然删除优于交换。对于 $1$ 也是一样的。

但另一个问题是，删除后可能会影响其它位置的逆序对，这时就可能会导致一个原本该被保留的位置因为操作顺序问题而被删除。

不妨先确定删除哪些元素，然后利用交换将其变为合法。

那么一个很重要的结论是，最优策略中，剩下的序列的逆序对个数至多为 $1$。否则至少会有一个位置产生逆序对大于 $1$，那么这个序列就相当于没删干净。

所以最后剩下的序列只能是两种，`0...0101...1` 或 `0...01...1`。

情况二直接暴力贪就行，接下来考虑情况一。

首先前半的 $0$ 和后半的 $1$ 一定是尽可能保留的，只需要考虑 `10` 是哪两个位置即可。

假设确定的 $1$ 后面有多个 $0$，那么选最近的一定最优。对于 $0$ 而言也一定是选前面最近的 $1$。

由此，这对 $10$ 在原序列中一定相邻，再扫一遍跑贪心就好了。

```
#include<cstdio>
#include<cstring>
#include<algorithm>
const long long inf=1e12;
using namespace std;
int n;
char s[300003];
int main(){
	int i,t;
	scanf("%d",&t);
	while(t--){
		int s0=0,s1=0;
		long long res=1e18;
		scanf("%s",s+1);n=strlen(s+1);
		s[n+1]='0';
		for(i=1;i<=n+1;i++)if(s[i]=='0')s0++;
		for(i=1;i<=n;i++){
			if(s[i]=='1'&&s[i+1]=='0'){
				long long d=0;
				if(i!=n)d+=inf;
				int pl=s1,pr=s0-1;
				if(pr)pr--;
				d+=(pl+pr)*(inf+1);
				if(d<res)res=d;
			}
			if(s[i]=='1')s1++;
			else s0--;
		}
		s1=s0=0;
		for(i=1;i<=n;i++)if(s[i]=='0')s0++;
		for(i=1;i<=n;i++){
			if(s[i]=='1'){
				res=min(res,(inf+1)*(s0+s1));
				s1++;
			}
			else s0--;
			res=min(res,(inf+1)*(s0+s1));
		}
		printf("%lld\n",res);
	}
}
```

---

## 作者：六楼溜刘 (赞：0)

## 题意
- 给你一个仅含 $0,1$ 的数字串，你有两个操作。
- 一个是花费 $10^{12}+1$ 代价删除一个数。
- 另一个是花费 $10^{12}$ 代价交换两个相邻的数。
- 求使这个串单调不减的最小代价。
- 多组测试数据。

## 题解
首先我们考虑转化完成之后这个串应该长什么样。

显然，是一堆 $0$ 后面跟一堆 $1$ 的形式，也就是说存在一个位置，这个位置左边全是 $0$，右边全是 $1$（性质 $1$）。

![图示](https://cdn.luogu.com.cn/upload/image_hosting/silucoow.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

另外，容易发现，至多只会进行 $1$ 次交换操作。

利用反证法，假设有一种情况的最优解会进行至少两次交换操作，那么由于性质 $1$，显然这两次操作的结果必定是把某个 $1$ 移到两个 $0$ 的后面（或者把某个 $0$ 移到 $1$ 的前面）：

![图示](https://cdn.luogu.com.cn/upload/image_hosting/jmtefdp7.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

而这样做的代价是 $2\times 10^{12}$，显然不如直接花费代价 $10^{12}+1$ 把那个数删了。

并且容易发现，如果有一个交换操作那它必定发生在 $0,1$ 的交界处（不然就毫无意义）。

所以我们可以 $O(n)$ 预处理前缀 $1$ 的个数和后缀 $0$ 的个数。然后 $O(n)$ 枚举分解处（在某两个数之间），分别计算交换和不交换的代价求解。

需要注意，分界处可能在 $0,1$ 之间或者 $n,n+1$ 之间，需要特殊考虑。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=getchar())){if(c=='-')f=-1;}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=3e5+5,inf=1e18,add=1e12;
int n,t,ans=inf,sum1[N],sum2[N];
string a;
signed main(){
    t=read();
    while(t--){
        cin>>a;ans=0;
        n=a.length();//多测不清空，罚时两行泪。
        ans=inf;
        for(int i=1;i<=n;i++){//预处理前后缀
            sum1[i]=sum1[i-1];
            if(a[i-1]=='1'){
                sum1[i]++;
            }
        }
        sum1[n+1]=sum1[n];
        sum2[n+1]=0;
        for(int i=n;i>=1;i--){
            sum2[i]=sum2[i+1];
            if(a[i-1]=='0'){
                sum2[i]++;
            }
        }
        sum2[0]=sum2[1];
        for(int i=0;i<=n;i++){//枚举分界点
            if(i!=0&&a[i-1]=='1'&&a[i]=='0'){
                ans=min(ans,sum1[i-1]*(add+1)+sum2[i+2]*(add+1)+add);
            }
            ans=min(ans,sum1[i]*(add+1)+sum2[i+1]*(add+1));
        }
        printf("%lld\n",ans);
    }
}
}
```


---

