# Anastasia and pebbles

## 题目描述

Anastasia loves going for a walk in Central Uzhlyandian Park. But she became uninterested in simple walking, so she began to collect Uzhlyandian pebbles. At first, she decided to collect all the pebbles she could find in the park.

She has only two pockets. She can put at most $ k $ pebbles in each pocket at the same time. There are $ n $ different pebble types in the park, and there are $ w_{i} $ pebbles of the $ i $ -th type. Anastasia is very responsible, so she never mixes pebbles of different types in same pocket. However, she can put different kinds of pebbles in different pockets at the same time. Unfortunately, she can't spend all her time collecting pebbles, so she can collect pebbles from the park only once a day.

Help her to find the minimum number of days needed to collect all the pebbles of Uzhlyandian Central Park, taking into consideration that Anastasia can't place pebbles of different types in same pocket.

## 说明/提示

In the first sample case, Anastasia can collect all pebbles of the first type on the first day, of second type — on the second day, and of third type — on the third day.

Optimal sequence of actions in the second sample case:

- In the first day Anastasia collects $ 8 $ pebbles of the third type.
- In the second day she collects $ 8 $ pebbles of the fourth type.
- In the third day she collects $ 3 $ pebbles of the first type and $ 1 $ pebble of the fourth type.
- In the fourth day she collects $ 7 $ pebbles of the fifth type.
- In the fifth day she collects $ 1 $ pebble of the second type.

## 样例 #1

### 输入

```
3 2
2 3 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 4
3 1 8 9 7
```

### 输出

```
5
```

# 题解

## 作者：MZY666 (赞：7)

[原题传送门](https://www.luogu.com.cn/problem/CF789A)。
[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-cf789a)。

### 【 题意概括 】

Anastasia喜欢去公园收集石子。她有 $2$ 个口袋，每个口袋最多装 $k$ 个石子。

但她每天只去公园 $1$ 次，而且每次同一个口袋里只装同一种石子。问要装完 $n$ 种石子共要花多少天？

输入 $n$，以及每一种石子的数量 $w_i$。输出上述所求答案。

### 【 思路 】

我们可以简化一下题目，想成只有 $1$ 个口袋但每天可以去两次就行了。

那么不存在先取哪个石子的优先性、只需要保证每次能装就装就行了。根本不需要数组。

其它详情见代码。

### 【 代码实现 + 注释 】

```cpp
#include<bits/stdc++.h>//万能头文件好
using namespace std;
#define ll long long//个人习惯
int main(){
	ll n,k,w,i,ans=0;//先定义好
	scanf("%lld%lld",&n,&k);//输入n,k
	for(i=1;i<=n;i++){
		scanf("%lld",&w);//依次输入每一个w
		ans+=w/k;//先只装这个石子，看要装几次
		if(w%k!=0)ans++;//如果最后一次没法装完还得再装一次
	}
	if(ans%2!=0)ans++;
	//如果去公园的次数为奇数次则自动补齐，以保证次数为偶数
	printf("%lld\n",ans/2);//总天数=去公园的次数/2、
	return 0;//over~
}
```

完结撒花~（疯狂暗示！๑乛◡乛๑

---

## 作者：力巴尔 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF789A)

我们可以先统计把所有的石子都一次带走需要多少的口袋，再将这个数量除以 $\texttt 2$ 上取整。因为不管按怎样的顺序取石子，只要每次都尽量多的取，答案都是一样的。所以只需要每输入一种石子的个数，就统计取完这一种石子需要多少个口袋，以此类推，不断累加即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, s, a;
int main()
{
    scanf("%lld%lld", &n, &k);
    for (long long i = 1;i <= n;i++)
    {
        scanf("%lld", &a);
        s += (a % k == 0 ? a / k : a / k + 1);
    }
    printf("%lld", s & 1 ? s / 2 + 1 : s / 2);
}
```


---

## 作者：cqbztz2 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF789A)

[更好的阅读体验？](https://www.luogu.com.cn/blog/493271/solution-cf789a)

# Thinking

实现简单，思考较难。

首先按照题目考虑，我们会发现需要考虑的要素有许多，实现难度较大。

那就让我们逆向思考。既然每天可以用 $ 2 $ 个口袋装一次，那么可以将题目变化为：

每次可以用一个口袋装一次，一天可以装两次。

因此我们只需要算出对于每件物品，需要口袋装几次即可。

# Be careful

最后计算天数时，需要用统计的 $ ans / 2 $ 向上取整。

用代码是实现时，`(int)(ceil(ans*1.0/2.0))` 会出现精度问题，切记改为 `(int)(ceil(ans*1.0/2))`。

# Coding

```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  inline char gc(){
      static char buf[1000010],*p1=buf,*p2=buf;
      return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;
  }
  inline int read(){
      register int x=0,f=0;
      static char s=gc();
      while(s<'0'||s>'9')f|=s=='-',s=gc();
      while(s>='0'&&s<='9'){
          x=(x<<3)+(x<<1)+(s^48);s=gc();
      }return f?-x:x;
  }
  int n,k,a,now,ans;
  signed main(){
      n=read(),k=read();
      for(int i=1;i<=n;a=read(),ans+=(int)(ceil(a*1.0/k)),i++);
      printf("%lld",(int)(ceil(ans*1.0/2)));
      return 0;
  }
```


---

## 作者：sto_yyrdxh_orz (赞：0)

### 题目大意：
一个公园有 $n$ 种鹅卵石，有一个人有 $2$ 个口袋，容量都为 $k$，每天他都可以装小于 $k$ 个鹅卵石到每个兜里，但是一个兜只能装一种鹅卵石，需要几天才能全部装完？

### 题目分析：
我们可以把 $2$ 个兜看成一个兜，但是这一个兜里可以装 $2$ 种，如果剩余的鹅卵石个数装不满一个兜，那也算 $1$ 天装走的量。

### 具体代码：
```cpp
#include <iostream>
using namespace std;
int n, k, a, ans;
int main(){
	cin>>n>>k;
	//n种，口袋的容量k 
	for(int i=1;i<=n;i++){ 
		cin>>a;
		//第i个鹅卵石有a个 
		ans+=a/k;
		//把能装的都装了 
		if(a%k!=0){
			//没有装完也按1天拿的量来算 
		    ans++;
		}
	}
	cout<<(ans+1)/2;
    //要除以2，因为我们是把两个都合并成了一个兜
	return 0;
}
```

---

## 作者：sto_OwenLMZ2022_orz (赞：0)

一、题意

这道题的题意是：有一个小孩纸每天收集鹅卵石，她有 $2$ 个口袋，已知每个口袋能装 $k$ 个鹅卵石。有 $n$ 种鹅卵石，给定每种鹅卵石的数量，求她多少天能全带走这些鹅卵石。

二、思路

这题乍一看很难，但是其实如果我们把这 $2$ 个口袋想成 $1$ 个，最后再除以 $2$ ~~岂不会让这题瞬间水很多？~~ 这样处理后我们累加鹅卵石的数量，最后除以 $k$ 算出天数就可以啦（注意如果鹅卵石总数量不能整除 $k$ 的话还要加 $1$ 呦）。还有一点，就是最后的结果要进行判断：如果是偶数就直接除以 $2$，而奇数还需加 $1$。

三、代码实现

```cpp
#include<iostream>
using namespace std;
int main() {
    ios::sync_with_stdio (false);//加快cincout速度
    int n,k,w[100005] = {0},cnt = 0;//注意初始化为0
	cin>>n>>k;
	for(int i=1;i<=n;i++) {
		cin>>w[i];
		cnt+=w[i]/k;
		if(w[i]%k!=0){//特判+1
		    cnt++;
		}
	}
	if(cnt%2==0){//注意要判断cnt是奇数还是偶数，有不同的情况
	    cout<<cnt/2<<endl;
	}
	else{
	    cout<<cnt/2+1<<endl;
	}
	return 0;//好习惯
}
```


---

## 作者：cxy000 (赞：0)

其实这道题在我看来不是黄题的难度罢。

解析:

其实这道题非常简单。

只要我们将不同种类的石头分开计算需要多少次，最后再除以 $2$ （指两个口袋）即可。

但是注意，石子不一定是刚刚好的，所以我们需要加上 $k-1$ 即可。

为什么要加上 $k-1$ 呢？

如果最多装两个石子，那么三个石子要装两次，而四个也是两次。

当我们加上一个不大于 $k$ 的值时，若次数已经整除于 $k$ ，那么数值不会改变。

可以自己去推理。

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,m,x;
	cin>>n>>m;
	long long ans=0;
	for(int i=1;i<=n;i++){cin>>x;ans+=(x+m-1)/m;}
	cout<<(ans+1)/2;
	return 0;//就十行qwq
}
```


---

## 作者：_Give_up_ (赞：0)

## 题目大意
你有两个袋子。

给出 $n$ 和 $k$，分别表示石头的总数和每个袋子最多装的个数。

接着输入 $n$ 个数，表示每种石头有 $a[i]$ 个。

你每个袋子只能装同一种石头，求要装完所有的石头需要多少次。

## 题目思路
遍历一遍，求一个袋子装**完**每种石头需要的次数，把它们加起来，用 $ans$ 计数。

这个 $ans$ 就是如果有一个袋子，需要装的次数，因为你有两个袋子，所以把 $ans \div 2$ 就是答案（向上取证）。 

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int read()
{
    int x = 0,f = 1;
    char c = getchar();
    while(c<'0' || c>'9')
	{
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0' && c<='9')
	{
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
    return x*f;
}

int a[100005];

int main()
{
	int n=read(),k=read(),ans=0;
	for(int i=1;i<=n;i++)
		ans += ceil(read()*1.0/k);
	cout << ceil(ans*1.0/2) << endl;
	return 0;
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
Anastasia喜欢去公园收集石子.她有 $2$ 个口袋，每个口袋最多装 $k$ 个石子.

但她每天只去公园 $1$ 次，而且每次同一个口袋里只装同一种石子.问要装完 $n$ 种石子共要花多少天？
 
输入 $n$，以及每一种石子的数量 $w_i$. 输出上述所求答案.  

$1\le n\le 100000;1\le k\le 1000000000; 1\le w_i\le10000$
## $\text{Solution}$
求出每种石子需要几袋子装，全部加起来除以二上取整即可.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

ll n,m,k;
ll x[N],a[N],sum[N];
ll mn,mx,ans;
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=n;i++) x[i]=read();
  for(int i=1;i<n;i++) a[i]=abs(x[i]-x[i+1])*((i&1)?1:-1);
  for(int i=1;i<n;i++){
    sum[i]=sum[i-1]+a[i];
    if(i&1) ans=max(ans,sum[i]-mn);
    else ans=max(ans,mx-sum[i]);
    mx=max(mx,sum[i]);mn=min(mn,sum[i]);
  }
  printf("%lld\n",ans);
  return 0;
}
/*

*/

```


---

## 作者：Violet___Evergarden (赞：0)

题目是说每天去一次公园，有两个袋子可以装石头。那么我们可以转化成，每天上午和下午分别去一次，每次只能装一个袋子，于是就不需要考虑每次要装哪个石头，反正都要装完。这题就很简单了。

这里推库荐一个 cmath 库里的 ceil 函数，它是将一个小数的小数位当成 $1$ 来算，比如：

$$\operatorname{ceil}(3.5)=4$$
$$\operatorname{ceil}(5/2.0)=3$$

那么我们设 $day$ 表示需要多少天，则对于每个 $w_i$ 时：
$$ day \gets \operatorname{ceil}(w_i \cdot1.0\div k)$$
最后因为是每天当了两次计算，所以：

$$day \gets \operatorname{ceil}(day \cdot 1.0 \div 2)$$
```cpp
#include <iostream>
#include <cmath>
#define int long long
using namespace std;
int n,k,day;
signed main()
{
cin>>n>>k;
for(int i=1;i<=n;i++)
{
  int num;
  cin>>num;
  day+=ceil(num*1.0/k);
}
cout<<(int)ceil(day*1.0/2);
return 0;
}
```

---

## 作者：LRL65 (赞：0)

思路：

砸门先不用管两个口袋，直接**将它想成一个口袋，最后除以2**。

那么想成一个口袋以后，我们将所有类型全部扫一遍，分别算出它们需要多少天捡完（也就是 $w_i \div k$，**如果 $w_i$ 不是 $k$ 的倍数，还需要加一天**），最后相加。

好了，这一切全都做完以后，一定要记得**除以2，如果是奇数还得加1**。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,w[100005],ans;
int main() {
	cin>>n>>k;//输入
	for(int i=1;i<=n;i++) {
		cin>>w[i];
		ans+=w[i]/k;//累加
		if(w[i]%k!=0)ans++;//如果不是倍数，加1
	}
	cout<<ans/2+ans%2<<endl;//除以2输出，别忘记奇数时加上1
	return 0;
}
```


---

