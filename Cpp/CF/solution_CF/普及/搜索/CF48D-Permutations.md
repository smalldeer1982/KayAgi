# Permutations

## 题目描述

“排列”是指一个长度为n的序列，且其中1到n的每个数刚好出现一次。例如，(1) (4,3,5,1,2) (3,2,1)都是排列，而(1,1) (4,3,1) (2,3,4)则不是。

假设某人拿了几个排列（长度不一定相同），把它们连在一起写成了一个数列，并将这个数列打乱顺序。你的任务是将这个数列重新组成原来的几个排列（如果可能的话）。

## 说明/提示

在第1个样例中数组被分成了三个排列：(2,1) (3,2,1,4,5) (1,2)。第1个排列由原数列的第2和4个数组成，第2个排列由第3、5、6、7、9个元素组成，第3个排列由第1和8个元素组成。显然，还有另外几种分组的方式。

## 样例 #1

### 输入

```
9
1 2 3 1 2 1 4 2 5
```

### 输出

```
3
3 1 2 1 2 2 2 3 2
```

## 样例 #2

### 输入

```
4
4 3 2 1
```

### 输出

```
1
1 1 1 1 ```

## 样例 #3

### 输入

```
4
1 2 2 3
```

### 输出

```
-1
```

# 题解

## 作者：Tzs_yousa (赞：5)

# 思考历程
我曾经听人说过做题一定要仔细分析理解样例，然后我看了样例之后更懵了，就想着边写边想吧，于是就写了一个结构体，又写了一个  $ \ sort \ $ 排序，这显然不对啊，原来数组的顺序都没了，我便陷入了沉思。这个故事告诉我们要先想好了再去写题。

经过一番沉思之后，我想到了一种办法，既然正着思考怎样可以成立很难，为什么不去反着思考怎样不成立呢？（正难则反思想）

这样一想，很显然可以发现较大的数字受较小的数字的限制，而最小的便是1，如果较大的数字的数量超过较小的数字的数量，显然是不成立的；如果是成立的，那么序列数即是1的数量。

那么如何确定每个数字属于第几个排列呢？制定一个计数器，每个数字从第一组开始，进入之后这个数字所在的组数应加1。

补充：我又想排序又想保留原来的顺序，那就桶排啊！
# AC代码
```c
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],num[100001],maxn,zu[100001];//a数组存数，num数组存每个数出现的次数，zu存每个数字出现的组数 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		num[a[i]]++;//桶排 
		maxn=max(maxn,a[i]);
	}
	for(int i=2;i<=maxn;i++)
	{
		if(num[i]>num[i-1])
		{
			cout<<"-1";
			return 0;
		}
	}
	cout<<num[1]<<endl;
	for(int i=1;i<=n;i++)
	{
		zu[a[i]]++;//更新新的组 
		cout<<zu[a[i]]<<" ";
	}
	return 0;
}
```
完结撒花!

---

## 作者：b6e0_ (赞：3)

[CF题面传送门](https://codeforces.com/problemset/problem/48/D) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF48D) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF48D)

构造题的样例一般是坑人的，看了会使你的思路更乱。

对于任意一个正整数 $x$，如果 $x$ 出现的次数比 $x+1$ 出现的次数少，那么一定不能组成排列，因为一个排列如果出现了 $x+1$ 就一定出现 $x$，这样就会有一些 $x+1$ 没有 $x$ 搭配。

每个排列肯定都包含 $1$，所以排列的个数就是 $1$ 出现的次数。

对于每个 $i$，输出在 $i$ 之前 $a_i$ 出现的次数就行了。这样能保证相同的数不出现在同一个排列中，再由于出现次数是递减的，所以也能保证比它小的数都在这个排列中。

代码：

```cpp
#include<bits/stdc++.h>
using namepace std;
int a[100010],b[100010],ans[100010];//b是桶
inline int read()//快读
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x;
}
inline void write(int x)//快写
{
	int sta[10],tp=0;
	while(x)
	{
		sta[++tp]=x%10;
		x/=10;
	}
	while(tp)
		putchar(sta[tp--]+'0');
	putchar(' ');
}
int main()
{
	int n=read(),i;
	for(i=1;i<=n;i++)
	{
		a[i]=read();
		b[a[i]]++;
		ans[i]=b[a[i]];//此时b[a[i]]就是在i之前a[i]出现的次数
	}
	for(i=1;i<100003;i++)
		if(b[i]<b[i+1])//如果i的出现次数比i+1少
			break;
	if(i<100003)//如果这个条件成立，那么肯定刚刚的循环是break跳出来的
	{
		printf("-1");
		return 0;
	}
	write(b[1]);
	putchar('\n');
	for(i=1;i<=n;i++)
		write(ans[i]);//输出答案
	return 0;
}
```

---

## 作者：infinities (赞：2)

这个题乍一看可能有一点吓人，但是只要你稍微分析一下，便会发现其实它并不难，只是考你一下排列的知识罢了（话说题目里也告诉了排列的定义啊）

然后你要知道几条东西：

1. 排列的个数就是所给数字中$1$的个数

2. 如果那n个数字真的是由几个排列混合而成的，那么它们之中就不可能有大于n的数字（即如果有大于$n$的数字我们就可以立即输出$-1$并return）

3. 几个排列混合之后，大的数字的个数不可能大于小的数字的个数（同理于$2$.进行特判）

4. 如果判断完毕，数列是合法的，那么当它第$x$次出现时只需输出$x$即可（spj其实并没有什么卵用）

知道了这些，这题就好写多啦

code：

```cpp
#include<bits/stdc++.h>//搞个万能头

using namespace std;

int n,b,a[100000+100],c[100000+100],maxn,k,d[100000+10];

signed main(){
    cin>>n;
    
    for(int i=1;i<=n;i++){
        cin>>a[i];
        
        if(a[i]==1)k++;//计算排列数
        
        maxn=max(maxn,a[i]);
        
        if(a[i]>n){cout<<-1;return 0;}//特判1
        
        c[a[i]]++;//将数字装入一个桶中
    }
    
    for(int i=1;i<=maxn;i++)if(c[i]<c[i+1]){cout<<-1;return 0;}//特判2
    
    cout<<k<<"\n";//输出排列数
    for(int i=1;i<=n;i++)cout<<++d[a[i]]<<" ";//使用了简便写法
}
```


---

## 作者：tzc_wk (赞：1)

这道题就是纯暴力模拟

因为每个排列都含有数字1，所以考虑数字1的个数，数字1的个数就代表着排列数的个数

上代码吧，具体见注释
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+100;
int n,num[MAXN],x[MAXN];//num[i]表示数字i出现的次数
int max_num=0;//max_num表示输入的数组中最大的数
vector<int> pos[MAXN];//pos[i]中装的是数字i在原数组中的位置
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x[i];
		num[x[i]]++;
		max_num=max(max_num,x[i]);//更新max_num
		pos[x[i]].push_back(i);
	}
	int cur=0;//cur表示这是第几个排列
	while(num[1]!=0){//每次num[1]预示着有几个排列，如果num[1]=0，就表示没有其它合法的排列了
		int i=1;
		while(num[i]>0)	i++;//找出现在这列数中的最大值，并对1~i进行排列
		i--;//因为当i到达这列数的最大值时，num[i]>0，所以i还要+1，因此最后取到的i是比实际最大值多1的因此要-- 
		for(int j=1;j<=i;j++)	num[j]--;将1~i的所有数的个数减1
		cur++;//更新排列数的个数
		for(int j=1;j<=i;j++){
			x[pos[j][0]]=cur;//将数值为pos[j][0]的位置赋上cur
			pos[j].erase(pos[j].begin());//将第一个元素删除
		}
	}
	for(int i=2;i<=max_num;i++){
		if(num[i]){
			puts("-1\n");
			return 0;
		}
	}//找是否还有剩余的元素，如果有，就表示无法满足题目要求，输出-1
	cout<<cur<<endl;
	for(int i=0;i<n;i++)	cout<<x[i]<<" "; 
	return 0;
}
```

---

## 作者：fuzhelin1984 (赞：0)

题意

给你一个长度为 n 的数列，把它们分成若干个序列，且对于每个序列，元素都应从 1 开始连续递增 1 。

作法

标准桶排，但更小的数的出现次数不应小于更大的数，这样才能满足题目要求。

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 101000;
int a[N],t[N],p[N];
int main()
{
	int n,mx = -1,m = -1;
	cin >> n;
	for(int i = 1;i <= n;++i)
	{
		cin >> a[i];
		t[a[i]]++;
		mx = max(a[i],mx);
	} 
	t[0] = 1e8;
	for(int i = 1;i <= mx;++i)
	{
		if(t[i] > t[i-1])
		{
			cout<<"-1";
			return 0;
		}
		m = max(m,t[i]);
	}
	cout<<m<<endl;
	for(int i = 1;i <= n;++i)
	{
		p[a[i]]++;
		cout<<p[a[i]]<<" ";
	}
	return 0;
}

```


---

## 作者：Fa1thful (赞：0)

### 一、题意
给你一串数，求是否可以将这串数分成几个排列，如果可以输出每个数分别属于那个排列，如果不可以输出 `-1`。
### 二、分析
我们知道一个排列一定是由最小的数到最大的数都分别出现一次，所以越大的排列越难实现，小排列居多，所以在原来的数里面小的数一定是多于大的数的，而且 `1` 是最多的。所以只需要用一个桶记录每个数的个数判断是否严格不下降，最后相同的数不可能出现在同一个排列中，所以相同的数直接分成不同排列以此类推即可。

如果没看懂，没关系，我们用图讲解一遍：
![](https://cdn.luogu.com.cn/upload/image_hosting/tc3nmzub.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

首先我们看一个排列，发现它每个数字有且只有一个，接下来我们看一下样例：

![](https://cdn.luogu.com.cn/upload/image_hosting/57bdpfbm.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果要形成排列，必须从三个 `1` 中选一个， 三个 `2` 中选一个......，因为排列的性质。所以我们轻易地知道如果一个数比另一个数大，且这个数的个数也更多的话，那就没有足够多的小的数为所有这种数都找到一个排列，所以这个桶必须是单调不下降的。

![](https://cdn.luogu.com.cn/upload/image_hosting/ji86hvge.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果这个桶是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/xybuxsky.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么一定会有一个较大的数无法自成一个排列。

既然模拟思路已经清晰，下面就是代码

### 三、代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int a[1000005];
int t[1000005];   //桶 
int ans[1000005];   //答案 
int main()
{
	int maxx = -999999;      //桶中最大的数 
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		t[a[i]]++;    //记录桶 
		maxx = max(maxx, a[i]);    //更新最大数 
	}
	for (int i = 2; i <= maxx; i++)   //判断是否严格不下降 
	{
		if (t[i] > t[i - 1])    //并不是严格下降 
		{
			cout << -1 << endl;    //不可以 
			return 0;
		}
	}
	cout << t[1] << endl;   //先输出有几个排列，即1的个数，因为如果后面凑不成1也可以自成排列 
	for (int i = 1; i <= n; i++)
	{
		ans[a[i]]++;   //同一个数不再相同排列 
		cout << ans[a[i]] << " ";   //输出排列数。 
	}
	cout << endl;
	return 0;
}
```
谢谢观赏

---

## 作者：Graphcity (赞：0)

## 思路

我们开 $10^5$ 个栈，第 $i$ 个栈中存储着所有值为 $i$ 的数的下标。可以倒着考虑，对于最大的一个数（ 假设为 $x$ ），由于它必须得要组成一个排列，而且没有比它更大的数了，所以必然有一个排列是 $[1,x]$ 的。

如果在找 $[1,x]$ 的数中发现缺少了一个数，输出无解即可。否则将那一个排列的数全部删去，再继续寻找，直到所有的栈全部清空位置。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e5;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,tot,s[Maxn+5];
stack<int> st[Maxn+5]; // 存储下标

inline void Clear(int x) // 寻找排列
{
    ++tot;
    for(int i=x;i>=1;--i)
    {
        if(st[i].empty()) {printf("-1"); exit(0);}
        // 如果找不到,输出无解并退出
        s[st[i].top()]=tot,st[i].pop();
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;++i) st[read()].push(i);
    for(int i=Maxn;i>=1;--i) // 倒着考虑
        while(!st[i].empty()) Clear(i);
    printf("%d\n",tot);
    for(int i=1;i<=n;++i) printf("%d ",s[i]);
    return 0;
}
```

---

## 作者：Great_Influence (赞：0)

不要看样例，直接做。

先判断无解。很容易可以知道，如果存在一个数x，使得它的个数比x-1要多，那么肯定无解。

至于答案，对每个数开一个计数器，每出现一次就计数器+1，然后输出这个计数器记录次数。这样就能构造完成了。

代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x)
{
	T s=0,f=1;char k=getchar();
	while(!isdigit(k)&&(k^'-'))k=getchar();
	if(!isdigit(k)){f=-1;k=getchar();}
	while(isdigit(k)){s=s*10+(k^48);k=getchar();}
	x=s*f;
}
void file()
{
	#ifndef ONLINE_JUDGE
		freopen("test.in","r",stdin);
		freopen("test.out","w",stdout);
	#endif
}
#define Chkmax(a,b) a=a>(b)?a:(b)
#define Chkmin(a,b) a=a<(b)?a:(b)
const int MAXN=100007;
static int ma=100000;
static int n,w[MAXN],p[MAXN],cnt[MAXN];
inline void init()
{
	read(n);
	Rep(i,1,n)read(p[i]),++w[p[i]];
}
inline void solve()
{
	Rep(i,2,ma)if(w[i]>w[i-1])
	{printf("-1\n");exit(0);}
	printf("%d\n",w[1]);
 	Rep(i,1,n)printf("%d",++cnt[p[i]]);
	putchar('\n');
}
int main()
{
	file();
	init();
	solve();
	return 0;
}
```

---

## 作者：违规用户名gAGt8$%z (赞：0)

看到这题，显然可以发现如果较大的数字的数量超过较小的数字的数量，显然是不成立的；如果是成立的，那么序列个数就是 1 的数量。
那么如何确定每个数字属于第几个顺序呢？制定一个计数器，每个数字从第一组开始，进入之后这个数字所在的组数应加 1 。

ps:判断不成立时，想要不改变顺序，就需要桶排序。

以下为 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],num[100001],maxn,b[100001]; // a是原数组，b是计数器
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		num[a[i]]++;
		maxn=max(maxn,a[i]);
	}
	for(int i=2;i<=maxn;i++)
		if(num[i]>num[i-1]) // 如果较大数的数量多于较小数的数量
			return cout<<-1,0;
   cout<<num[1]<<endl;
	for(int i=1;i<=n;i++)
	{
		b[a[i]]++;
		cout<<b[a[i]]<<" ";
	}
	return 0;
}
```




---

