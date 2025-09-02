# Strange Addition

## 题目描述

Unfortunately, Vasya can only sum pairs of integers ( $ a $ , $ b $ ), such that for any decimal place at least one number has digit $ 0 $ in this place. For example, Vasya can sum numbers $ 505 $ and $ 50 $ , but he cannot sum $ 1 $ and $ 4 $ .

Vasya has a set of $ k $ distinct non-negative integers $ d_{1},d_{2},...,d_{k} $ .

Vasya wants to choose some integers from this set so that he could sum any two chosen numbers. What maximal number of integers can he choose in the required manner?

## 样例 #1

### 输入

```
4
100 10 1 0
```

### 输出

```
4
0 1 10 100 ```

## 样例 #2

### 输入

```
3
2 70 3
```

### 输出

```
2
2 70 ```

# 题解

## 作者：Larryyu (赞：3)

## _Description_
给定一串数 $d_1,d_2,\dots d_n(n\le 100,d_i\le 100)$，需要从其中选出一些数使其满足以下条件：

设选出的数为集合 $S$；

$\forall d_i,d_j\in S,d_i,d_j$ 两数中每一数位都至少要有1个0。

例：

- $70$ 百位和个位上均有 $1$ 个 $0$（不满三位则用 $0$ 补齐）。
- $70$ 和 $7$ 就满足上述条件（$70$ 有百位和个位，$7$ 有百位和十位）。
- $100$ 和 $26$ 也满足条件（$100$ 有十位和个位，$26$ 有百位）。

求 $\left\vert S\right\vert$ 的最大值，以及此时 $S$ 中的元素。

题目翻译有些难懂，但看懂例子后不难理解。
## _Solution_
可以先将 $d_i$ 分为以下几类：

- $d_i=100$；
- $10\mid d_i$；
- $0<d_i<10$；
- $d_i=0$；
- 不满足以上任何条件的 $d_i$，如 $26$；

通过考虑多种情况，可以得到以下几点规则：

1. 除了第四类，其他类每类至多只能有一个。

2. 第一类和第四类可以和其他任何一类构成条件。

3. 第二类能和第三类构成条件。

4. 第二类或第三类与第五类不能同时加入。

每次输入时记录第一、二、三、五类首个数的下标及第四类的个数。

最后按上述规则输出即可。
## _Code_
```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[110],ans,tot1,tot2;
int cnt1,cnt2,cnt3,cnt4,cnt5;
int read(){
    int x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]==100) cnt1=i; //第一类
        else if(a[i]==10||a[i]==20||a[i]==30||a[i]==40||a[i]==50||a[i]==60||a[i]==70||a[i]==80||a[i]==90) cnt2=i; //第二类
        else if(a[i]<10&&a[i]>0) cnt3=i; //第三类
        else if(a[i]==0) cnt4++; //第四类
        else cnt5=i; //第五类
    }
    if(cnt1) ans++;
    if(cnt2) tot1++;
    if(cnt3) tot1++;
    if(cnt5) tot2++;
    ans+=max(tot1,tot2); 
    if((ans+cnt4)<=1){ //特判只有一个数时
        cout<<1<<endl; //无论是哪一类都要输出
        cout<<a[1];
        return 0;
    }
    cout<<ans+cnt4<<endl;
    for(int i=1;i<=cnt4;i++) cout<<0<<" "; //第四类的数量
    if(cnt1) cout<<a[cnt1]<<" ";
    if(tot1>=tot2){ //考虑选择第二类和第三类还是第五类
        if(cnt2) cout<<a[cnt2]<<" ";
        if(cnt3) cout<<a[cnt3]<<" ";
    }else{
        if(cnt5) cout<<a[cnt5]<<" ";
    }
    return 0;
}
```

#### 完结撒花！！

---

## 作者：OIerJiang_1017 (赞：1)

## [CF305A 题目传送门](https://www.luogu.com.cn/problem/CF305A)

## 题目大意
对于一个整数对，如果这对整数中至少有一个数中包含有数字 $0$，那么就允许这两个数进行求和运算。例如，整数对 $505$ 和 $50$ 可以求和，但整数对 $1$ 和 $4$ 就不能求和。给定一个包含 $k$ 个不同非负整数 $d_1,d_2,d_3,\dots,d_k$ 的集合，请你确定从集合中做多能选择多少个整数，使得从这些数中任意选定两个数都可以求和。

## 解决思路
根据数据范围 $0 \leq x \leq 100$ **分类讨论**：
- 当 $x=0$ 或 $x=100$ 时 $x$ 可以与任何数相加, 直接存入数组
- 当 $1 \leq x \leq 9$ 时，如果没有出现过 $x$ 为一位数而且 $x$ 个位为零的情况，则将 $x$ 存进数组并标记 $f1=true$。
- 当 $10 \leq x \leq 99$ 时：
  - $x$ 个位为零时
如果没有出现过 $x$ 为两位数而且 $x$ 个位为零的情况 将 $x$ 存进数组并标记 $f2=true$。
  - $x$ 个位不是零时
更新 $z=x$, 因为十位与个位都不是零的数最多用一次如果 $f1$ 与 $f2$ 都为零而且 $z$ 不是 $0$， 将 $z$ 加入到数组里。

## 代码展示
```cpp
#include <iostream>
using namespace std;

const int N = 110;
int n, d[N], x, cnt, z;
//d[]为最终要输出的数d
//cnt是d数组下标
bool f1, f2;
//f1记录是否出现过 x为一位数 && x个位为零 的情况
//f2记录是否出现过 x为两位数 && x个位为零 的情况

int main()
{
	scanf("%d", &n);//建议scanf,更快
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		if(x == 0 || x == 100)//第一种情况
			d[++cnt] = x;
		if(1 <= x && x <= 9)//第二种情况
			if(f1 == false)
			{
				d[++cnt] = x;
				f1 = true;
			}
		if(10 <= x && x <= 99)
			if(x % 10 == 0)
			{
				if(f2 == false)
				{
					d[++cnt] = x;
					f2 = true;
				}
			}
			else z = x;
	}
	if(f1 == false && f2 == false && z != 0)
		d[++cnt] = z;
	printf("%d\n", cnt);//建议printf,更快
	for(int i = 1; i <= cnt; i++)
		printf("%d ", d[i]);
	return 0;
}
```

---

## 作者：lin_A_chu_K_fan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF305A)
# 题意
定义满足以下条件的两个数是可相加的：
> 对于每一个数位，两个数都至少有一个 $0$，没有数的自动补 $0$。

如，$50$ 和 $6$ 就可以相加，但注意，**不是两个数都有 $0$ 就可以相加**。
# 思路
首先，用结构体存储每个数的大小、每一位是否为 $0$ 和非零位个数，并按非零位个数对结构体排序。然后遍历所有数，判断是否符合条件，将答案储存起来，最后输出。

代码就不给了，求关~

---

## 作者：zzhbpyy (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF305A)

## 思路

使用结构体分别储存每个数原数大小、每一位上是否为 $0$ 和非零数位个数 $ans$。直接按 $ans$ 的大小对结构体进行排序。最后遍历所有的数，依次判断是否符合条件，统计个数，将答案存在一个 queue 里，最后输出即可。

## 完整代码

```c++
#include<bits/stdc++.h>
using namespace std;
struct Edge{
	int a[4],ans,d;//d是原数大小
}kk[105];
int kkk,a;
bool res[4];
signed main(){
	ios::sync_with_stdio(0);cin.tie(nullptr);cout.tie(nullptr);
	cin>>kkk;
	for(int i=1;i<=kkk;i++){
		cin>>a;int ans=0,cnt=0;kk[i].d=a;
		while(a){
			cnt++;
			if(a%10)ans++,kk[i].a[cnt]=true;//取出每一位判断是否为0
			a/=10;
		}
		kk[i].ans=ans;
	}
	sort(kk+1,kk+kkk+1,[](Edge a,Edge b){//lambda表达式
		return a.ans<b.ans;
	});
	queue<int>q;int y=0;//最多能放几个
	for(int i=1;i<=kkk;i++){
		for(int j=1;j<=3;j++){
			if(res[j]&&kk[i].a[j])goto A;
			res[j]|=kk[i].a[j];
		}
		y++;
		q.push(kk[i].d);
		A:;
	}
	cout<<y<<'\n';
	while(!q.empty())cout<<q.front()<<' ',q.pop();
	return 0;
}
```

---

## 作者：ztxtjz (赞：0)

开头说一句，那位说#3有问题的题目理解错了，数据没有问题。
## 【题意】
两个数的各个位数上都至少有一个$0$，位数不足自动补$0$，比如$30$和$50$不能相加，因为十位上没有$0$，并不是两个数中只要有$0$就可以相加。
## 【思路】
考虑数据范围$0≤d≤100$，以位数为标准进行分类讨论

①$d=0$或$d=100$时，显然可以与任何数相加（两个$100$不能相加）

②$1≤d≤9$时，根据$flag1$判断个位是否出现过非零的数，若没有，则添加到数组中，并把$flag1$标记为$1$，表示已存在上述的数。

③$10≤d≤99$时

Ⅰ $d$的个位为$0$时，根据$flag2$判断十位是否出现过非零的数，若没有，则添加到数组中，并把$flag2$标记为$1$，表示已存在上述的数。

Ⅱ $d$的个位非$0$时，变量$t$更新为$d$，因为十位、个位都非零的数至多能使用一次。

循环结束后，若$flag1==0$且$flag2==0$且$t!=0$，即$t$存在时，将$t$添加到数组中。
## 【代码】
```cpp
#include <cstdio>
int n,p[105],cnt,t;
bool flag1,flag2;
int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		if(x==0||x==100) p[++cnt]=x;
		else if(x<10)
		{
			if(!flag1)
				p[++cnt]=x,flag1=1;
		}
		else
		{
			if(!flag2)
			{
				if(x%10==0) p[++cnt]=x,flag2=1;
				else t=x;
			}
		}
	}
	if(!flag1&&!flag2&&t) p[++cnt]=t;
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%d ",p[i]);
	return 0;
}
```


---

## 作者：王熙文 (赞：0)

## 题解

这道题我思路复杂了，不过应该很好理解。

首先，观察到 $d$ 的位数小于等于 $3$，就可以基于位数做。

观察到，选出来的数对于每一位至多有一个不为 $0$ 的数（以下对于某一位不为 $0$ 的数称作 $1$），否则这两个放在一起不能相加。

所以我们枚举每一位上有 $1$ 的数，然后将这个数作为选出的数中这一位唯一有 $1$ 的。

接下来对于所有数，当它不为这选出来的数时，必须满足它的那一位为 $0$。如果对于每一位这个数都满足，就可以选这个数。

最后统计答案就好了。

写出代码，会发现一个问题，即没有数在某一位上是 $1$。这种情况可以特判，但我的实现方式是强制添加 $3$ 个数：$100,010,001$，这样就能保证每一位都有为 $1$ 的数了。注意要把这三个数标记上，统计答案时不计入答案。

复杂度 $ \mathcal O(n^4)$（太悬了）。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int d[110];

bool vis[110];

int ansd[110];

int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1; i<=n; ++i) scanf("%d",&d[i]);
	d[n+1]=114514100;
	d[n+2]=114514010;
	d[n+3]=114514001;
	n+=3;
	for(int i=1; i<=n; ++i)
	{
		if(d[i]%10==0) continue;
		for(int j=1; j<=n; ++j)
		{
			if(d[j]/10%10==0) continue;
			for(int k=1; k<=n; ++k)
			{
				if(d[k]/100%10==0) continue;
				memset(vis,0,sizeof(vis));
				for(int l=1; l<=n; ++l)
				{
					if(l!=i && d[l]%10) vis[l]=1;
					if(l!=j && d[l]/10%10) vis[l]=1;
					if(l!=k && d[l]/100%10) vis[l]=1;
				}
				int cnt=0;
				for(int l=1; l<=n; ++l)
				{
					if(!vis[l] && d[l]/1000==0) ++cnt;
				}
				if(ans<cnt)
				{
					ans=cnt;
					int now=0;
					for(int l=1; l<=n; ++l)
					{
						if(!vis[l] && d[l]/1000==0) ansd[++now]=d[l];
					}
				}
			}
		}
	}
	printf("%d\n",ans);
	for(int i=1; i<=ans; ++i) printf("%d ",ansd[i]);
	return 0;
}
```

---

