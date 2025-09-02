# Carousel

## 题目描述

The round carousel consists of $ n $ figures of animals. Figures are numbered from $ 1 $ to $ n $ in order of the carousel moving. Thus, after the $ n $ -th figure the figure with the number $ 1 $ follows. Each figure has its own type — the type of the animal corresponding to this figure (the horse, the tiger and so on). The type of animal of the $ i $ -th figure equals $ t_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1328D/6fef0d63a3e427398bbe634881f56ca00339f29a.png)The example of the carousel for $ n=9 $ and $ t=[5, 5, 1, 15, 1, 5, 5, 1, 1] $ . You want to color each figure in one of the colors. You think that it's boring if the carousel contains two different figures (with the distinct types of animals) going one right after another and colored in the same color.

Your task is to color the figures in such a way that the number of distinct colors used is the minimum possible and there are no figures of the different types going one right after another and colored in the same color. If you use exactly $ k $ distinct colors, then the colors of figures should be denoted with integers from $ 1 $ to $ k $ .

## 样例 #1

### 输入

```
4
5
1 2 1 2 2
6
1 2 2 1 2 2
5
1 2 1 2 3
3
10 10 10```

### 输出

```
2
1 2 1 2 2
2
2 1 2 1 2 1
3
2 3 2 3 1
1
1 1 1```

# 题解

## 作者：WYXkk (赞：10)

随意手玩一下可以发现，答案不会超过 $3$。

你只要从第一个开始交替染 $1$ 和 $2$，然后假如 $n$ 为奇数把最后一个换成染 $3$，那么，很显然任意相邻两个颜色不同，自然也符合了条件。

考虑何时答案为 $1$：所有 $t_i$ 相等，全染 $1$ 即可。

考虑何时答案为 $2$：$n$ 为偶数，交替染 $1$ 和 $2$ 即可；

或者，有至少两个相邻的数相等，那么从中间断开为链后交替染 $1$ 和 $2$ 即可。

考虑何时答案为 $3$：$n$ 为奇数且相邻的每一对数都不相等。

此时，交替染 $1$ 和 $2$ 然后把最后一个改成 $3$ 即可。

分类讨论即可。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

int t[200005],c[200005];
int n,q;
int main()
{
	q=rd();
	while(q--)
	{
		n=rd();
		F(i,1,n) rd(t[i]);
		bool flg1=false,flg2=false;
		int x;
		t[n+1]=t[1];
		F(i,1,n) if(t[i]==t[i+1]) flg1=true,x=i;else flg2=true;
		if(!flg2)
		{
			puts("1");
			F(i,1,n) printf("1 ");puts("");
		}
		else
		{
			if(!(n&1))
			{
				puts("2");
				F(i,1,n) printf("%d ",(i&1)+1);puts("");
			}
			else if(flg1)
			{
				puts("2");
				F(i,1,n) c[(x+i-1)%n+1]=i&1;
				F(i,1,n) printf("%d ",c[i]+1);
				puts("");
			}
			else
			{
				puts("3");
				F(i,1,n-1) printf("%d ",(i&1)+1);
				puts("3");
			}
		}
	}
	return 0;
}
```



---

## 作者：do_while_true (赞：4)

### 题目分析

显然是一道构造题，我们考虑多种情况

#### 第1种情况: 只有一个不同的数

输出 $n$ 个 $1$ 即可。。

#### 第2种情况: 只有两个不同的数

一种数全输出 $1$ ,另一种数全输出 $2$ 。

因为必定并只会会出现两个不同数相邻的情况，这种输出保证了如果两个不同的数相邻颜色不同。

#### 第3种情况: n为偶数

输出"$1,2,1,2,1,2......1,2$"即可。

因为这种输出保证相邻位置的颜色一定不同。

#### 第4种情况: n为奇数

n为奇数时又分为两种情况：

所有相邻位置的都不同: 输出"$1,2,1,2,1,2...1,2,3$"。

这样可以保证相邻位置的颜色一定不同。

有的相邻位置的数相同: 选择其中一个和上一个填涂同样的颜色，把它化为一个长度为偶数的序列。

也就是这样输出:

"$1,2,1,2...1,1,2...1,2$"

"$1,2,1,2...2,2,1...1,2$"

这里是"$1,1$"和"$2,2$"这两个位置的数相同。

显然这样只处理一个相邻位置相同数的，可以化为第3种情况。

### Code:

```cpp
#include<iostream>
#include<cstdio>
#include<set>
using namespace std;
int T,n,a[200001];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		set<int>s;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			s.insert(a[i]);
		}
		if(s.size()==1)
		{
			puts("1");
			for(int i=1;i<=n;i++)
				printf("1 ");
			puts("");
			continue;
		}
		else if(s.size()==2)
		{
			int tmp=a[1];
			puts("2");
			for(int i=1;i<=n;i++)
			{
				if(tmp==a[i]) printf("1 ");
				else printf("2 ");
			}
			puts("");
			continue;
		}
		if(n%2==0)
		{
			puts("2");
			for(int i=1;i<=n;i++)
				printf("%d ",i%2+1);
			puts("");
			continue;
		}
		int tmp=0;
		a[0]=a[n];
		for(int i=1;i<=n;i++)
			if(a[i]==a[(i+1)%n]) tmp=i;
		if(!tmp)
		{
			puts("3");
			for(int i=1;i<n;i++)
				printf("%d ",2-i%2);
			puts("3");
			continue;
		}
		int cnt=1;
		puts("2");
		for(int i=1;i<=n;i++){
			printf("%d ",2-cnt%2);
			if(i!=tmp) cnt++;
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：小恐 (赞：2)

~~昨天CF炸了算smg~~

~~害的我只好切这4道题，后面题都没看~~

这道题分好几种情况：

所有数都一样：全都染1，用1种颜色。

偶数个：从第一个开始2 1 2 1……2 1，由于是一个环，首和尾必须不一样，用2种颜色。

奇数个，且有两个相邻数的相同：奇数个就因为首尾哪样染的话会相同，但此时有两个相邻的数相同，于是就可以安排他们相同，这样就使得还可以用上种方法干了。

奇数个，相邻的数都不相同：没办法2个数了，任意两个相邻的数都不能相同至少3个数，也很好构造，先按偶数个那么染，等到最后一个数就染成3。

注：以上的有两个相邻的数包括第一个和最后一个。

上代码吧：
```cpp
#include<stdio.h>
using namespace std;
int a[200005];
int main()
{
	int t,x,fi;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		bool flag=0,flag1=1;
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
			scanf("%d",a+i);
		for(int i=1;i<=n;++i)
		{
			int p=i-1;
			if(p==0)
				p=n;
			if(a[i]==a[p])
				flag=1;
			else
				flag1=0;
		}
		if(flag1)
		{
			printf("1\n");
			for(int i=1;i<=n;++i)
				printf("1 ");
			printf("\n");
		}
		else if(n%2==0)
		{
			printf("2\n");
			for(int i=1;i<=n/2;++i)
				printf("%d %d ",2,1);
			printf("\n");	
		}
		else if(flag)
		{
			printf("2\n");
			flag=0;
			for(int i=1;i<=n;++i)
			{
				int p=i-1;
				if(p==0)
					p=n;
				if(flag)
					printf("%d ",2-(i%2));
				else if(a[i]==a[p])
					printf("%d ",2-(i%2)),flag=1;
				else 
					printf("%d ",i%2+1);
			}
			printf("\n");
		}
		else 
		{
			printf("3\n");
			for(int i=1;i<n;++i)
			{
				printf("%d ",i%2+1);
			}
			printf("%d\n",3);
		}
	}
	return 0;
}
```
希望CF不要再炸！

---

## 作者：laboba (赞：1)

具体实现和楼上大佬差的不是很多，但是可以从另一种方式思考：
（首先还是要特判全部相等）如果这是一个链（不用考虑首尾）则答案必然为2，固定第一个数c[1]后，每一个数c[i]为2-c[i-1]。

所以链的情况是很简单的，我们考虑将这个环化为链。

1. n个数中没有连续相等的两个。则我们可以先按链的方式去填，因为按这个方式，只要第一个确定，其他的数也就确定了，所以填完后，如果c[n]和c[1]相等，则我们无法通过转换前面的数使得它们不等，所以必须将c[n]变为3，最终答案即为3.如果c[1]和c[n]不等，则可以直接输出，答案为2。
2. n个数中有连续相等的两个，不妨设为t[i]=t[i+1]，所以，t[i]和t[i+1]之间是没有限制的，那么我们可以愉快地发现，它等价于一条 i----1----n----i+1的链，按链的方法处理即可。注意，要特判一下c[1]=c[n]的情况。

至于代码。。。就不全贴了吧，放一段第二种情况的。
```cpp
		int x=0;//x即为刚才所述的i
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]==a[i-1])x=i-1;
		}
      if(a[1]==a[n])x=n;//特判
     if(x){
			printf("2\n");
			for(int i=1;i<=x;i++){//处理链x----1的部分
				if(i%2)printf("1 ");
				else printf("2 ");
			}
			for(int i=n;i>x;i--){//处理链n----x+1的部分
				if((n-i)%2)tmp[i]=1;
				else tmp[i]=2;
			}
			for(int i=x+1;i<=n;i++)printf("%d ",tmp[i]);
			printf("\n");
       }
```
有不懂的可以私信问我。

~~看在我思路如此清奇的份上，让我通过吧QAQ~~

---

## 作者：朝夕 (赞：0)

## 解题思路
### ①全部图案相同

则答案=1，全部输出颜色为1即可。

### ②有图案不同

#### 【1】n为偶数
答案为2，输出121212……即可。

#### 【2】n为奇数
（1）若有一对相邻的图案相同的

则答案=2，其他照样输出121212……相邻的那对相同图案颜色相同即可。

只需要一对，多对的情况也只要使一对颜色相同就够了。

举例来说11223，则涂成12112即可。

（2）若不存在相邻的图案相同的

答案=3，除最后一个颜色为3外，其他按照121212……涂即可。


## 参考代码

（比赛时打的代码有点乱，请见谅）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 1e8
#define INF 1e18
using namespace std;
int t[200005];
int c[200005];
int main()
{
    ios::sync_with_stdio(false);
    int q;
    cin>>q;
    while(q--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>t[i];
        int ans=1;
        c[1]=1;
        for(int i=2;i<=n;i++)
            if(t[i]!=t[i-1])
            {
                ans=2;
                break;
            }
        if(ans==1)
        {
            cout<<1<<endl;
            for(int i=1;i<=n;i++)
            {
                if(i!=1) cout<<" ";
                cout<<1;
            }
            cout<<endl;
        }
        else
        {
            int f=1;
            for(int i=2;i<=n;i++)
                if(t[i]==t[i-1]) f=0;
            if(t[n]==t[1]) f=0;
            if(n%2==0) f=0;
            if(f==0)
            {
                ans=2;
                if(n%2==0)
                {
                    for(int i=2;i<=n;i++)
                        if(c[i-1]==1) c[i]=2;
                        else c[i]=1;
                }
                else
                {
                    int r=1;
                    for(int i=2;i<=n;i++)
                    {
                        if(t[i]==t[i-1]&&r) c[i]=c[i-1],r=0;
                        else if(c[i-1]==1) c[i]=2;
                        else c[i]=1;
                    }
                }
            }
            else
            {
                ans=3;
                for(int i=2;i<n;i++)
                    if(t[i]==t[i-1]) c[i]=c[i-1];
                    else
                    {
                        if(c[i-1]==1) c[i]=2;
                        else c[i]=1;
                    }
                c[n]=3;
            }
            cout<<ans<<endl;
            for(int i=1;i<=n;i++)
            {
                if(i!=1) cout<<" ";
                cout<<c[i];
            }
            cout<<endl;
        }
    }
    return 0;
}

```


---

## 作者：fzwfzwfzw (赞：0)

这道题的题意就是给你一个数字串a，**这是一个环**

让你去构造一个b数字串，当ai！=aj时（**i和j相邻**）bi！=bj

当ai=aj的时候，bi=bj或bi！=bj

求最少用多少数字来构造b，并求出任意一个方案

首先判断所以当数字a全部相等时，b就只需要一个，bi全等于1

然后判断若数字串a的长度若为偶数，则b需要两个，方案为1 2 1 2 1 2 1 2 1 2 1 2 1 2…… 1 2结尾一定不和开头相同

然后判断有ai=aj的可能吗（注意这是一个环所以要判断开头和结尾），若有记录下位置，则b需要两个方案为 1 2 1 2 1 2 1 2 1 2……（当ai=aj的时候bi=bj）1 **2 2** 1 2 1 2 1 2……

若上述都没有可能，那么b需要3个 方案为1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2 1 2……1 2 **3**

这就是答案了。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
int n,m;
signed main(){
	n=read();
	for(int i=1;i<=n;i++)
	{
		int a;
		a=read();
		int cnt=0;//记录有没有ai等于aj
		int cww=1;//记录是不是全部相等
		int b=0;//每一个ai，就不开数组了
		int c=-1;//上一个位子的ai
		int ooo=0;//记录ai的位置
		int fir=0;//记录第一个位子好和最后一个位子比较
		for(int i=1;i<=a;i++)
		{
			b=read();
			if(i==1)fir=b;//记录第一个位子
			if(b==c)cnt=1,ooo=i-1;//记录有没有ai等于aj,记录ai的位置
			if(b!=c&&i!=1)cww=0;//记录是不是全部相等
			c=b;//上一个位子的ai
		}
		if(b==fir)//第一个位子和最后一个位子比较
		cnt=1,ooo=-2;
		if(cww)//第一个判断
		{
			printf("1\n");
			for(int i=1;i<a;i++)
			{
				printf("1 ");
			}
			printf("1\n");
			continue;
		}
		if(a%2==0)//第二个判断
		{
			printf("2\n");
			int q=1;
			for(int i=1;i<a;i++)
			{
				printf("%d ",q);
				q=3-q;
			}
			printf("2\n");
			continue;
		}
		if(cnt)//第三个判断
		{
			if(ooo==-2)//特判是不是第一个位置和最后一个位置相等
			{
				printf("2\n");
			int q=1;
			for(int i=1;i<a;i++)
			{
				printf("%d ",q);
				q=3-q;
			}
			printf("1\n");
			}
			else //正常判断
			{
				printf("2\n");
			int q=1;
			for(int i=1;i<a;i++)
			{
				printf("%d ",q);
				q=3-q;
				if(ooo==i)q=3-q;
			}
			printf("2\n");
			}
			continue;
		}//否则
		printf("3\n");
			int q=1;
			for(int i=1;i<a;i++)
			{
				printf("%d ",q);
				q=3-q;
			}
			printf("3\n");//注意，前面每一个位置都用了continue的；
	}
	return 0;
}
```


---

## 作者：andyli (赞：0)

分情况讨论。  
1. 只有一种动物：全部使用颜色 $1$ 。  
2. 只有两种动物：第一种使用颜色 $1$ ，第二种使用颜色 $2$ 。  
3. 否则，若 $2|n$ 或 首尾动物颜色相同 ：奇偶数位交替使用颜色 $1$ 与 $2$ 。  
4. 否则，若 有相邻动物种类相同，设位置为 $p~(1\leq p<n)$，则 $c_p=c_{p+1} $，前 $p$ 位交替使用颜色 $1$ 和颜色 $2$，第 $p+1$ 位使用与第 $p$ 为相同的颜色，从 $p+1$ 位开始继续交替使用颜色 $1$ 与颜色 $2$ 。  
5. 否则，前 $n-1$ 为交替使用颜色 $1$ 与颜色 $2$，第 $n$ 为使用颜色 $3$ 。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
#include <algorithm>
const int maxn = 200005;

int c[maxn], t[maxn];
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        for (int i = 1; i <= n; i++)
            io.read(c[i]), t[i] = c[i];
        std::sort(t + 1, t + n + 1);
        int _p = std::unique(t + 1, t + n + 1) - t - 1;
        if (_p == 1) { // (1)
            writeln(1);
            for (int i = 1; i <= n; i++)
                io.write(1, " \n"[i == n]);
            continue;
        }
        if (n % 2 == 0 || c[1] == c[n]) { // (3)
            writeln(2);
            for (int i = 1; i <= n; i++)
                io.write((i & 1) + 1, " \n"[i == n]);
            continue;
        }
        if (_p == 2) { // (2)
            writeln(2);
            for (int i = 1; i <= n; i++) {
                if (c[i] == t[1])
                    io.write(1, " \n"[i == n]);
                else
                    io.write(2, " \n"[i == n]);
            }
            continue;
        }
        int p = 0;
        for (int i = 1; i < n && !p; i++)
            if (c[i] == c[i + 1])
                p = i;
        if (!p) {  // Not found (5)
            writeln(3);
            for (int i = 1; i < n; i++)
                io.write((i & 1) + 1, " ");
            writeln(3);
        }
        else { // found c_p=c_{p+1} (4)
            writeln(2);
            for (int i = 1; i <= p; i++)
                io.write((i & 1) + 1, " ");
            for (int i = p + 1; i <= n; i++)
                io.write(((i & 1) ^ 1) + 1, " ");
            writeln();
        }
    }
    return 0;
}
```

---

## 作者：ZZ作者 (赞：0)

# CF1328D Carousel 题解
by ZZ作者

# 1 题目大意

给你一个由 $n$ 个数  $t_1, t_2, \dots, t_n$ 构成的**环**，请你给环上的每一个数涂色，使得任意两个相邻的不同数字被涂上不同的颜色（同一个数字可以用不同的颜色来涂）。请你输出你使用颜色的种类个数的最小值 $k$ ，并输出你的方案中每个数字的颜色 $c_1, c_2, \dots, c_n$ 。如有多解，输出任意一个。

# 2 分类讨论

## 2.1 当环中所有数均相等时（样例4）

我们把所有数都涂成一个颜色，于是这时有 $k=1$ 。

## 2.2 当 $n$ 为偶数时（样例2）

这时我们把 $2,1,2,1,\dots$ 顺次填入即可保证相邻不同色，且首尾不同色。这时有 $k=2$ 。

## 2.3 当 $n$ 为奇数时（样例1，3）

### 2.3.1 当首尾数相同时

这时就不用管首尾颜色相不相同了，那就还是把 $2,1,2,1,\dots$ 顺次填入，有 $k=2$ 。

### 2.3.2 当首尾数不同时

#### 2.3.2.1 当环中有两相邻且相等的数时

我们在第一次发现两相邻且相等的数时，**多涂一次**相同的色，再继续填 $1$ 和 $2$ ，就可以把 $c_n$ 垫成和 $c_1$ 不同的颜色

> 举例：
>
> 7
>
> 1 2 2 3 3 4 4
>
> 我们想涂成 2 1 2 1 2 1 2，但这样首尾冲突，因此既然有两个相邻的 2，就把他们涂成同色吧！
>
> 于是变成 2 1 1 2 1 2 1，可以满足条件

此时 $k=2$

#### 2.3.2.2 当环中无两相邻且相等的数时

这个时候我们垫颜色的方法就不管用了，那就老老实实开个新的颜色吧，把所有 $t_i = t_1$ 涂成 $3$，其余再用 $2,1,2,1,\dots$ 补全即可。

# 3 代码实现

主要思路都在上面，大家如果能看懂写出自己的过程就最好了~~都能吊打我的程序~~，这里就放一下我考场上写的代码吧（删去了一些乱七八糟的东西

```c++
//part1
#include<bits/stdc++.h>
using namespace std;
#define ll long long


//part2


//part3
inline ll rd()
{
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
} 

ll t,a,b;
ll num[200005]={0};
ll flag,flag3;

//part4
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a;
		flag=1;flag3=0;
		memset(num,0,sizeof(num));
		cin>>num[1];
		for(int i=2;i<=a;i++)
		{
			cin>>num[i];
			if(num[i]!=num[i-1])flag=0;
		}
		if(flag)
		{
			cout<<1<<endl;
			for(int i=1;i<=a;i++)cout<<1<<' ';
			cout<<endl;
		}
		else if(a%2==0||num[1]==num[a])
		{
			cout<<2<<endl;
			for(int i=1;i<=a;i++)cout<<(i%2)+1<<' ';
			cout<<endl;
		}
		else if(num[1]!=num[a])
		{
			for(int i=2;i<=a;i++)
			{
				if(num[i]==num[i-1])flag3=1;
			}
			if(flag3)
			{
				ll flag4=0;
				cout<<2<<endl;
				for(int i=1;i<=a;i++)
				{
					if(num[i]==num[i-1]&&flag4==0)
					{
						flag4=1;
					}
					cout<<(i-flag4)%2+1<<' ';
				}
			 	cout<<endl;
			}
			else
			{
				cout<<3<<endl;
				for(int i=1;i<=a;i++)
				{
					if(num[i]==num[1])cout<<3<<' ';
					else cout<<(i%2)+1<<' ';
				}
				cout<<endl;
			}
		}
	}
	return 0;
}
```

# 4 总结

这道题没有考察什么高级算法，但是考察了分类讨论的能力，我第三次才A……

这是蒟蒻第一次A掉CF的D题……（主要原因在于熬住了

感受：一定要敢想，如果过不去，要自己多造数据，争取全面考虑每一种情况。

---

