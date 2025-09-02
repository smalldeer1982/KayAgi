# Mancala

## 题目描述

在外国有一种棋，这种棋在一个有 $14$ 个孔的棋盘上玩。一开始，每个洞有 $a_i$ 个石头。当玩家操作的时候，他会选择一个石头个数为正整数的孔并把所有石头都放到这个孔里，然后逆时针把这些石头一个一个地重新分配到下一个洞里方向。逆时针方向的意思是：玩家将在第 $(i+1)$ 、第 $(i+2) \dots$ 个孔依次放入一块石头。如果玩家将一块石头放入第 $14$ 个孔，则下一个要放在第 $1$ 个孔里面。在操作之后，玩家将从包含偶数个石头的洞里收集所有的石头，收集的石头数就是得分。请问一次移动后得到的最高分数是多少？

## 样例 #1

### 输入

```
0 1 1 0 0 0 0 0 0 7 0 0 0 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 1 1 1 1 0 0 0 0 0 0 0 0 0
```

### 输出

```
8
```

# 题解

## 作者：Zouzhuoxuan (赞：6)

# $\text{CF975B Mancala 题解}$
## [题目传送门](https://www.luogu.com.cn/problem/CF975B)
## [博客观看](https://www.luogu.com.cn/blog/800322/cf975b-mancala-ti-xie-1)
-----------
### 一、题目简述
一个首尾相连的环一共有 $14$ 个点，每个点有 $a_i$ 个石头，现在选定一个点，将这个点的石头平均分到剩下的每一个点上。如不能均分，将剩下的石头按逆时针序（$1\rightarrow2\rightarrow3\rightarrow...\rightarrow n\rightarrow1$）放到后面的点上。我们令得分 $p=\displaystyle\sum^{14}_{i=2}a_i$，求 $p_{\max}$。

### 二、分析
首先我们发现这个环只有 $14$ 个点，可以考虑暴力模拟解决这个问题。

为了方便观看，设选定的点编号为 $x$，得分设为 $p_i$，即从 $x$ 点开始的得分为 $p_x$。

那么显然现在的目标为求 $\displaystyle\max_{1\le i\le14}p_i$。

我们可以循环 $x\rightarrow1\sim14$ 计算出每个 $p_x$。

如果是**每个点循环分发石头**的话时间复杂度为 $O(\sum a_i)$。

显然 $a_i\le 10^9$ 的范围不允许这么做。

那么可以考虑**将分发的石头量对 $14$ 取余**。理由是每个点**分到**的石头量无非就是 $\dfrac{a_x}{14}$ 或者 $\dfrac{a_x}{14}+1$。不如先将每个点加上 $\dfrac{a_x}{14}$，剩下的石头量再以一个 $\le 14$ 的循环分发。

求和的时间复杂度为一个常数 $O(n)$。

所以本题的时间、空间复杂度均为常数（此处把 $14$ 看作常量，如果 $n=14$ 的话本题的时间复杂度约等于 $O(n^2)$）。

### 三、特殊注意
+ 此处的 $a_i\le 10^9$，而得分可以达到 $p=\displaystyle\sum^n_{i=2}a_i=\dfrac 7 2(a_2+a_{14})\le 7\times 10^9$，所以需要使用`long long`数据类型。

+ $a_x=\dfrac{a_x}{14}$。
### 四、代码
```cpp
#include<bits/stdc++.h>
#define int long long //数据类型要注意! 
#define n 14 
using namespace std;
int a[n+1],t[n+1]; //我们每一次操作都将a数组中的数移动到t数组中操作，维护a数组。 
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); //读写加速(不过这里好像没什么用) 
	int i,ans=0;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n;i++)
	{
		memset(t,0,sizeof(t)); //清空t数组 
		if(!a[i]) continue; //如果这一项没有石头就没必要进行操作了，直接跳过
		int tmp=a[i],x=i+1,sum=0;
		for(int j=1;j<=14;j++) t[j]=a[j]+tmp/n; //每一项加上a[x]/14 
		t[i]=tmp/n; //本身这个点上只会剩下 a[x]/14个石头 
		tmp%=n;
		while(tmp) //模拟分发
		{
			if(x==15) x=1;
			t[x]++,tmp--,x++;
		}
		for(int j=1;j<=14;j++) if(t[j]%2==0) sum+=t[j]; //加和
		ans=max(ans,sum); 
	}
	cout<<ans<<endl;
	return 0;
}
```

### 五、拓展
+ 如果不是 $14$ 个洞，而是 $n$ 个洞（$n\le 10^4$）的话应该怎么做？
+ 我们可以稍微修改一下上面的代码的宏定义和输入输出。
+ 参考代码如下:
```cpp
#include<bits/stdc++.h>
#define int long long //数据类型要注意! 
#define N 10005
using namespace std;
int a[N],t[N]; //我们每一次操作都将a数组中的数移动到t数组中操作，维护a数组。 
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0); //读写加速
	int i,ans=0,n;
    cin>>n;//如果你想用这个程序交这道题的话请将这里改成 n=14;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n;i++)
	{
		memset(t,0,sizeof(t)); //清空t数组 
		if(!a[i]) continue; //如果这一项没有石头就没必要进行操作了，直接跳过
		int tmp=a[i],x=i+1,sum=0;
		for(int j=1;j<=n;j++) t[j]=a[j]+tmp/n; //每一项加上a[x]/n 
		t[i]=tmp/n; //本身这个点上只会剩下 a[x]/n个石头 
		tmp%=n;
		while(tmp) //模拟分发
		{
			if(x==n+1) x=1;
			t[x]++,tmp--,x++;
		}
		for(int j=1;j<=n;j++) if(t[j]%2==0) sum+=t[j]; //加和
		ans=max(ans,sum); 
	}
	cout<<ans<<endl;
	return 0;
}
```
**如果您觉得这篇题解写得好的话请留下一个赞！**

---

## 作者：Creator_157 (赞：2)

### 主要题意：
有 $14$ 个孔，每个孔里有 $a_i$ 个石头，选择一个孔，将其中的石头平均分到剩下的每一个孔中、如不能均分，将剩下的石头顺次放到后面的孔中。

偶数个石头的洞里的石头数就是得分。请问一次移动后得到的最高分数是多少？

------------

### 大体思路：
既然只有十四个，那么我们就直接模拟选择每一个孔进行操作，选择一个最大的即可。

------------
### code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[20],b[20],cnt,sum,ans;
int main()
{
    for(int i=1;i<=14;i++)cin>>a[i];
    for(int i=1;i<=14;i++)
    {
        sum=0;
        ans=a[i];
        if(ans==0)continue;//如果没有石头就直接跳过 
        for(int j=1;j<=14;j++)b[j]=a[j];
        b[i]=0;
        int s=ans/14;
        for(int j=1;j<=14;j++)b[j]+=s;
        ans%=14;
        int ne=i+1;
        while(ans)//分发石头 
        {
            if(ne==15)ne=1;
            b[ne]++;
            ans--;
            ne++;
        }
        for(int j=1;j<=14;j++)
        {
            if(b[j]%2==0)sum+=b[j];
        }
        cnt=max(cnt,sum);
    }
    cout<<cnt;
    return 0;
}
```


---

## 作者：Cappuccino_mjj (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF975B)
题目意思：

你现在要下一种棋，并且按照规则移动一次，请问能得到的最大的分数是多少？（规则请自行去题目查看）

---

思路：

首先我们发现棋盘中只有 ``14`` 个空位，因此暴力枚举每个空位是可行的。但是 $a_i$ 最高可达 $10^9$，所以不能循环分配石子。

接着我们研究就可以发现，如果当前空位的石子数量 $a_i$ 多于 ``14``，那么其他空位就一定会被放上 $\lfloor \displaystyle \frac{a_i}{14}\rfloor$ 个石子。因此我们先循环一遍，将可数的完整循环节所加的石子数量加起来，剩下不足 ``14`` 个石子再循环累加。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[20],b[20],ans;
signed main()
{
	for(int i=1;i<=14;i++)
		cin>>a[i];
	for(int k=1;k<=14;k++)
	{
		if(a[k]==0)continue;
		for(int i=1;i<=14;i++)
			b[i]=a[i];
		int w=a[k]/14;
		for(int i=1;i<=14;i++)
		{
			if(i==k)
			{
				b[k]-=w;
				continue;
			}
			b[i]+=w;
			b[k]-=w;
		}
		for(int i=k+1;b[k];i++)
		{
			if(i==15)i=1;
			if(i==k)continue;
			b[i]++;
			b[k]--;
		}
		b[k]+=w;
		int sum=0;
		for(int i=1;i<=14;i++)
		{
//			cout<<b[i]<<" ";
			if(b[i]%2==0&&b[i]!=0)
				sum+=b[i];
		}
//		cout<<endl;
		ans=max(ans,sum);
	}
	cout<<ans;
	return 0;
}
```

---

完美撒花~

---

## 作者：125125A (赞：0)

# 前言
随机跳题跳过来的，当我看见 $180$ 提交但是只有 $58$ 通过的时候，我还以为是什么世纪级难题，~~没想到只是一道模拟题~~。
# 正文
[题目传送门](https://www.luogu.com.cn/problem/CF975B)
## 思路
有 $14$ 个孔，每个孔里有 $a _ {i}$ 个石头，选择一个孔，将其中的石头平均分到剩下的每一个孔中，如不能均分，将剩下的石头顺次放到后面的孔中。

那么既然孔只有 $14$ 个，那么我们就可以直接模拟选择每一个孔进行操作的过程，最后选择一个最大的即可。

## 代码：

```cpp
# include <bits/stdc++.h>
using namespace std;

# define int long long // 十年OI一场空，不开long long见祖宗

int arr[20], brr[20], Count, sum, ans;

int main(){
	
	for(int i = 1;i <= 14;i++){
		cin >> arr[i];
	}
	
	for(int i = 1;i <= 14;i++){
		sum = 0;
		ans = arr[i];
		
		if(ans == 0) {
			continue;//如果这个孔没有石头就直接跳过 
		}
		
		for(int j = 1;j <= 14;j++){
			brr[j] = arr[j];
		}
		
		brr[i] = 0;
		int s = ans / 14;
		
		for(int j = 1;j <= 14;j++){
			brr[j] += s;
		}
		
		ans %= 14;
		
		int temp = i + 1;
		while(ans != 0){//放石头 
			if(temp == 15){
				temp = 1;
			}
			
			brr[temp]++;
			ans--;
			temp++;
		}
		
		for(int j = 1;j <= 14;j++){
			if(brr[j] % 2 == 0){
				sum += brr[j];// 记录得分
			}
		}
		
		Count = max(Count, sum);
	}
	
	cout << Count;
	
	return 0;
}
```
# 吐槽
关于 $0 \le a _ {i} \le 10 ^ {9}$ 这个数据范围，中文翻译未指出，望管理大大改正。

---

## 作者：ZYXzyx1006 (赞：0)

## 题意与思路
这道题看到数据量较小，仅有 $14$ 个起点。遂想到使用模拟，但每个起点可能拥有的石子个数很大，可能超时。我们进行思考，石子会沿着一个长度为 $14$ 的环移动，故最后一次回到起点时的石子数等于起点石子数求余 $14$。此时再进行模拟，计算时间将大大缩短。
#### 具体注释见代码。 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[15],b[15],ans=0,sum=0;//从一开始编号,15位
int main() {

	for(int i=1; i<=14; i++)
		cin>>a[i],b[i]=a[i];//模拟运动b数组
	for(int i=1; i<=14; i++) {
		if(a[i]==0)//题目要求正整数
			continue;
		else {
			//memset(b,0,sizeof(0));
			for(int j=1; j<=14; j++)
				b[j]=a[j];//初始赋值
			sum=0;
			for(int j=1; j<=14; j++)
				b[j]+=a[i]/14;
			b[i]=a[i]/14;//注意起点i的赋值
			int kk=a[i]%14,i1=i+1;// 不足14个与模拟
			while(kk>0) {
				if(i1>14)
					i1%=14;
				kk--;
				b[i1]++;
				i1++;
			}
			for(int k=1; k<=14; k++) {
				if(b[k]%2==0) {
					//cout<<k<<" "<<b[k]<<endl;
					sum+=b[k];//见题意
				}
			}
			ans=max(ans,sum);
		}
	}
	cout<<ans<<endl;
}
```
本人写题解经验少，写的不好还请见谅。

---

## 作者：kingho11 (赞：0)

很简单的模拟题，唯一需要注意的是 $0 \le a_i \le 10^9$，所以不能暴力移动石头。

## 具体做法：

暴力枚举移动哪一个格子，然后用一个变量记录里面有多少个石头，清空原来的，然后往右边放置，直到放到第 $14$ 个，然后批量放置来优化复杂度，最后再从第 $1$ 个格子开始放置，直到放完。不断重复这个操作，记得不要在原数组上改变即可。

## 代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=15;
int a[N],b[N];
int solve(int st)
{
	int o=b[st];
	b[st]=0;
	for(int i=st+1;i<=14 && o;i++)//先分别把一个石头放置到i~n的格子 
	{
		b[i]++;
		o--;
	}
	int p=o/14;
	for(int i=1;i<=14;i++)//批量放置减低复杂度 
	{
		b[i]+=p;
	}
	for(int i=1;i<=o%14;i++)//放置剩下的石头 
	{
		b[i]++;
	}
	int cnt=0;
	for(int i=1;i<=14;i++)//计算分数 
	{
		if(!(b[i]&1))
		{
			cnt+=b[i];
		}
	}
	return cnt;
}
signed main()
{
	for(int i=1;i<=14;i++)
	{
		cin>>a[i];
	}
	int maxn=-1;
	for(int i=1;i<=14;i++)//暴力枚举i 
	{
		for(int j=1;j<=14;j++)//复制一次数组 
		{
			b[j]=a[j];
		}
		if(a[i])
		{
			maxn=max(maxn,solve(i));
		}
	}
	cout<<maxn;
}
```

---

## 作者：linjinkun (赞：0)

一看到这道题，百分之百就是暴力优化（因为 $a_i$ 高达 $10^9$），那么如何暴力优化呢？我们将石子分配的过程分成三个部分：先分配到第 $n$ 个洞，然后把剩下的整块的不断分配到 $n$ 个洞的过程压缩成全部加上 $a_i \div 14$，最后，再把余下的石子依次分配，时间复杂度：$O(n^2)$。

**注意：十年 OI 一场空，不开 ```long long``` 见祖宗。**

代码（有详细注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 20;
#define n 14//习惯写n了
#define int long long//上面说了 
int a[N];
int b[N];//枚举每一个石子时，会改变a数组，要用b记录下来，改完之后，重新变成原来的a数组
signed main()
{
	for(int i = 1;i<=n;i++)
	{
		scanf("%lld",&a[i]);//读入
	}
	int maxx = 0;//记录最大值
	for(int i = 1;i<=n;i++)//枚举要动那个石子
	{
		for(int i = 1;i<=n;i++)//先记录下原来的a数组
		{
			b[i] = a[i];
		}
		int s = a[i];//记录下来a[i]
		int y = a[i];//再开一个变量记录下来a[i]，用处后面会说
		int sum = 0;//sum是记录得分的变量
		a[i] = 0;//当前石子要往前分配，当前这个位置的石子已经拿去分配了，当前位置已经没有石子
		for(int j = i+1;j<=n&&j<=i+y;j++)//有时候s<n-i，就只用遍历到s就好了
		{
			a[j]++;//分配
			s--;//减少
		}
		if(s!=0)//如果还能继续分配石子
		{
			int t = s%14;//记录下s mod 14和s ÷ 14
			int c = s/14;
			if(t == 0)//如果没有余数（相当于没有第三部分）
			{
				for(int i = 1;i<=n;i++)
				{
					a[i]+=c;//加上
				}
			}
			else
			{
				for(int i = 1;i<=n;i++)//同上
				{
					a[i]+=c;
				}
				for(int i = 1;i<=t;i++)//第三部分加上
				{
					a[i]++;
				}
			}	
		}
		for(int i = 1;i<=n;i++)
		{
			if(!(a[i]&1))//如果a[i]是偶数
			{
				sum+=a[i];//加上
			}
		}
		maxx = max(maxx,sum);//记录最大值
		for(int i = 1;i<=n;i++)
		{
			a[i] = b[i];//还原
		}
	}
	printf("%lld",maxx);//输出
	return 0;
}
```

---

## 作者：hcy1117 (赞：0)

## 前言
这道题的翻译有误，小心被坑，具体的见[讨论区](https://www.luogu.com.cn/discuss/757354)。
## [题目传送门](https://www.luogu.com.cn/problem/CF975B)
没看懂题的再去看看，看懂了的可以跳过。
## 解题思路
一开始可以想到暴力枚举每一个石头个数为正整数的孔，然后按题意一个一个的放石头，最后统计。但这是绝对不可能过的，因为 $0\le a_{i}\le 10^9$ 一次一次放最多会放 $10^9$ 次，所以过不了。

考虑如何优化放的过程，想到放的每一个孔一起就如同一个环，也可以看作一个周期。设当前枚举到的这一个孔中的石子数为 $sum$，如果 $14$ 整除 $sum$，那么每一个孔肯定都会放入 $\frac{sum}{14}$ 个石子。

但显然有时 $sum$ 并不是 $14$ 的倍数，这时设 $r$ 为 $sum\bmod14$，那么从周期的开头到第 $r$ 个孔中的石子数都应再加 $1$。

具体的实现可以参考代码和注释。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[15],b[15];//a数组存输入的石头数，b数组存每次重新放完后的石头数 
int pos[15];//pos[i]存放的是在原序列a中的第i个孔在周期中的位置 
int main()
{
	
	for(int i=1;i<=14;i++)scanf("%lld",&a[i]);
	long long maxx=0;
	for(int i=1;i<=14;i++)
	{
		if(!a[i])continue;//判断石子数是否为正整数 
		memset(b,0,sizeof(b));//每次记得清空 
		int cnt=0; 
		long long sum=a[i];
		for(int j=i+1;j<=14;j++)pos[j]=++cnt;
		for(int j=1;j<=i;j++)pos[j]=++cnt;
		for(int j=1;j<=14;j++)if(j!=i)b[pos[j]]=a[j];//加上一开始就有的石子 
		long long num=sum/14,r=sum%14; 
		for(int j=1;j<=14;j++)b[j]+=num;
		for(int j=1;j<=r;j++)b[j]+=1;
		long long ans=0;
		for(int j=1;j<=14;j++){
			if(b[pos[j]]%2==0)ans+=b[pos[j]];//题目要求石子数为偶数就加上 
		}
		maxx=max(maxx,ans);//取最大值 
	}
	printf("%lld",maxx);
}
```

---

## 作者：Francium_ (赞：0)

# 题目大意
有一个环，环上有 $14$ 个孔，每个孔里有 $a_i$ 个石头，选择一个孔，将剩下的石头顺次放到后面的孔中。
偶数个石头的洞里的石头数就是得分，求一次移动后得到的最高分数是多少。
# 思路
$n = 14$，考虑枚举每一个孔洞，如果纯暴力模拟分发过程的话，$a_i \leq 10^9$，肯定超时。我们可以考虑用除法优化，具体来说就是：每个孔都可以分到 $\frac{n}{14}$ 个，余数再来暴力模拟，余数不会超过 $13$，时间复杂度可以通过。
# 代码
```cpp
#include <bits/stdc++.h>//万能头大法
using namespace std;
#define int long long//不开long long见祖宗
int a[20], b[20];

signed main() {
	int n = 14, ans = -10;//这里定义n=14是为了方便后面处理。
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		b[i] = a[i];
	}
	for (int i = 1; i <= n; i++) {//枚举每个洞
		for (int j = 1; j <= n; j++)//多测不清空，0分两行泪
			a[j] = b[j];
		if (!a[i])//0不用考虑
			continue;//这里的判断要写在复原之后！！！
		int x = a[i] / n, y = a[i] % n;
		for (int j = 1; j <= n; j++)
			a[j] += x;//每个洞分到n/14个石头
		a[i] = x;//本身要特殊处理
		for (int j = i + 1; y; j++) {
		    if(j==15)//这里不能用模！i=14就寄了！！
			    j = 1;
			a[j]++;
			y--;
		}
		int sum = 0;
		for (int j = 1; j <= n; j++)
			if (a[j] % 2 == 0)//统计
				sum += a[j];
		ans = max(sum, ans);//更新
	}
	cout << ans;
	return 0;
}
```

---

## 作者：frz_fw (赞：0)

## 一：题意
有十四个洞，寻找一个洞，将这个洞里的所有石子**均分**到所有洞中。如果不能均分，那就以逆时针方向将剩下的石子分到其他洞中，最终将洞中石子数量是偶数的石子总数求 $max$。
 
## 二：分析
我们可以将这 $14$ 个洞抽象成一个环，模拟题意即可。

## 三：注意
$maxx$ 的值 ~~好像~~ 会超过 int 范围，要开 **long long**。

## 四：[Code](https://www.luogu.com.cn/paste/3wxa10cy)。

---

## 作者：封禁用户 (赞：0)

**题意**：有 $14$ 个孔，每个孔里有 $a_i$ 个石头，选择一个孔，将其中的石头平均分到剩下的每一个孔中、如不能均分，将剩下的石头顺次放到后面的孔中。偶数个石头的洞里的石头数就是得分。请问一次移动后得到的最高分数是多少？

**思路**：数据太小辣，只有 $14$ 个孔，我们就可以直接暴力模拟，选择每一个孔进行操作。但 $a_i$ 最多 $10^9$ 所以不能循环分配石子。我们可以我们先循环一遍，将**可数的完整循环节**所加的石子数量加起来，剩下不足 $14$ 个石子再循环累加。最后取最大的即可。

[代码](https://www.luogu.com.cn/paste/9hz9ait7)。

---

## 作者：404Not_Found (赞：0)

思路：模拟


只有 $14$ 个孔，自然想到直接模拟每一个进行操作。代码很简单，记得开 `long long`：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[15],b[15],ans;
int main()
{
	for(int i=1;i<=14;i++) cin>>a[i];
	for(int i=1;i<=14;i++)
	{
		if(!a[i]) continue;
		for(int j=1;j<=14;j++)	b[j]=a[j];
		b[i]=0;
		long long tmp=a[i];
		int idx=i+1;
		while(tmp)
		{
			if(idx==15) idx=1;
			b[idx++]++; tmp--;
		}
		long long sum=0;
		for(int j=1;j<=14;j++)
			if(b[j]&1^1) sum+=b[j];//位运算优化,相当于b[j]%2==0，实测快1ms（划掉）
		ans=max(ans,sum);
	}
	cout<<ans<<endl;
	return 0;
}
```
但是这样是会 TLE 的，问题出在这里：

```cpp
long long tmp=a[i];
int idx=i+1;
while(tmp)
{
	if(idx==15) idx=1;
	b[idx++]++; tmp--;
}

```
这里我们是一个一个去往后面分的。但是 $a_i$ 可能达到 $10^9$ 的级别，时间复杂度显然承受不了。

那怎么办呢？我们可以先均摊，把每一堆平均要放的存在变量 $k$ 里先累加，剩下的再单独处理。因为没有处理完的不会超过 $14$，所以运算次数只有 $14^2$ 了，极大程度优化了时间。

代码只用把前面那一段改成这样：

```cpp
long long tmp=a[i];
int k=a[i]/14;
for(int j=1;j<=14;j++) b[j]+=k;
tmp%=14; int idx=i+1;
while(tmp)
{
	if(idx==15) idx=1;
	b[idx++]++; tmp--;
}
```
就能愉快地 AC 了！

感谢观看。

---

