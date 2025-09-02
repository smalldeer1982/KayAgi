# [ABC085D] Katana Thrower

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc085/tasks/abc085_d

あなたが散歩していると、突然一体の魔物が出現しました。幸い、あなたは $ N $ 本の刀、刀 $ 1 $、刀 $ 2 $、$ … $、刀 $ N $ を持っていて、次の二種類の攻撃を自由な順番で行うことができます。

- 持っている刀のうち一本を振る。刀 $ i $ $ (1\ <\ =\ i\ <\ =\ N) $ を振ると、魔物は $ a_i $ ポイントのダメージを受ける。同じ刀を何度振ることもできる。
- 持っている刀のうち一本を投げつける。刀 $ i $ $ (1\ <\ =\ i\ <\ =\ N) $ を投げつけると、魔物は $ b_i $ ポイントのダメージを受け、あなたはその刀を失う。すなわち、あなたは以後その刀を振ることも投げつけることもできなくなる。

魔物は、受けたダメージの合計が $ H $ ポイント以上になると消滅します。魔物を消滅させるには、最小で合計何回の攻撃が必要でしょうか。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 10^5 $
- $ 1\ <\ =\ H\ <\ =\ 10^9 $
- $ 1\ <\ =\ a_i\ <\ =\ b_i\ <\ =\ 10^9 $
- 入力値はすべて整数である。

### Sample Explanation 1

あなたは $ 1 $ 本の刀を持っていて、振ると $ 3 $ ポイントのダメージ、投げつけると $ 5 $ ポイントのダメージを与えられます。刀を $ 2 $ 回振ってから投げつけると $ 3\ +\ 3\ +\ 5\ =\ 11 $ ポイントのダメージを与え、合計 $ 3 $ 回の攻撃で魔物が消滅します。

### Sample Explanation 2

先ほどの刀に加えてもう $ 1 $ 本別の刀もあり、こちらは振ると $ 2 $ ポイントのダメージ、投げつけると $ 6 $ ポイントのダメージを与えられます。両方の刀を投げつけると $ 5\ +\ 6\ =\ 11 $ ポイントのダメージを与え、$ 2 $ 回の攻撃で魔物が消滅します。

## 样例 #1

### 输入

```
1 10
3 5```

### 输出

```
3```

## 样例 #2

### 输入

```
2 10
3 5
2 6```

### 输出

```
2```

## 样例 #3

### 输入

```
4 1000000000
1 1
1 10000000
1 30000000
1 99999999```

### 输出

```
860000004```

## 样例 #4

### 输入

```
5 500
35 44
28 83
46 62
31 79
40 43```

### 输出

```
9```

# 题解

## 作者：ITZDC9 (赞：7)

## 题解 AT3854 【[ABC085D] Katana Thrower】

### 题目分析
每一把刀有两种造成伤害的方式，投掷或者劈砍，刀可以无数次劈砍，但只能投掷一次，求最少需要多少次攻击击杀怪物。

很显然我们需要将每一次的伤害最大化。

### 思路分析

#### 错误思路

首先，一把刀只能投掷一次，却能劈砍无数次，因此较高的劈砍伤害进行无数次劈砍显然更为有利。但可能投掷伤害大于劈砍伤害，因此我们需要进行贪心。

我一开始的思路为：找到劈砍伤害最高的刀，（在怪物没死的情况下）将其余刀按伤害从大到小投掷出去，然后用剩下的一把刀劈砍直到能投掷为止，这样也不用考虑刀是否已经投掷的问题。

这个方法显然有误：投掷伤害不一定全部大于劈砍伤害，例如当数据的情况如下的时候：
```
4 100
3 1
1 4
1 3
1 1
```

按照排序，我们造成的伤害图表如下（红色部分为投掷，蓝色部分为劈砍）：

![](https://s3.ax1x.com/2021/02/05/yGG4QP.png)

显然更优解应当如下：

![](https://s3.ax1x.com/2021/02/05/yGG2id.png)



#### 正解

因此，我们的思路应当是将刀的劈砍伤害与投掷伤害分开，再从大到小排序。这样我们造成的伤害就如上图最优解一样，先缓慢下降，接着维持不变（开始利用劈砍造成伤害）。

但还有一个问题：投掷过的刀就无法进行劈砍。按上文排序，假如劈砍伤害最高的刀为 A，但 A 的投掷伤害比劈砍伤害高，计算的时候就会先投掷 A 再劈砍 A，似乎不符合题意。

例如如下数据：
```
2 100
10 50
1 1
```
按照题意先劈砍后投掷的伤害图表如下：

![](https://s3.ax1x.com/2021/02/05/yGJhtJ.png)

但如果按照排序先投掷后劈砍：

![](https://s3.ax1x.com/2021/02/05/yGYS1I.png)

可以看出实际上先投掷对结果则并没有影响，只是将原来作为最后一击，提早结束战斗的投掷挪到第一击罢了。同时这样也不用判断是否只剩下一把刀而能否投掷的问题。

### 代码实现

我们利用结构体数组存储刀的信息。结构体中包括刀的伤害和种类（投掷还是劈砍）。

输入数据之后，从大到小排序，在怪物存活的情况下不断投掷，如果找到了类型为劈砍的刀，则劈砍直至怪物死亡即可。

#### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct knife
{
	int m;//刀的伤害
	bool t;//刀的种类（劈砍 0 或投掷 1）
}k[233333];

bool cmp(knife x,knife y)
{
	return x.m > y.m;//cmp函数，利用sort按刀的伤害从大到小排序
}

int main() 
{
	int n,h;
	cin >> n >> h;//输入数据
	int c=0;//因为拆分了两把刀所以不能用 i，添加一个 c 掌管数组位置。
	for(int i = 1;i <= n;i++)
	{
		cin >> k[++c].m;
		cin >> k[++c].m;
		k[c].t = 1;//将刀的类型设定为投掷
	}
	sort(k+1,k+c+1,cmp);//排序
	int i = 1,ans = 0;
	while(h > 0)//怪物还活着
	{
		if(k[i].t == 1)//如果刀的类型属于投掷
		{
			h -= k[i].m;//丢出去，怪物掉血（如果这里怪物直接去世了，那么h <= 0会自动结束循环）
			ans++;//攻击次数 + 1
		}
		else//刀的类型属于劈砍
		{
			if(h % k[i].m == 0)//特判一下防止除法少 1
			{
				ans += h / k[i].m;//算出来不断劈砍到怪物死亡要多少次
			}
			else
			{
				ans += h / k[i].m + 1;//和上面一样，这里是特判补上 1
			}
			h = 0;//怪物当场去世，自动结束结束循环
		}
		i++;//计算下一把刀
	}
	cout << ans;
    return 0;
}
```
------
第一篇题解，还是比较紧张的（

希望能过（

---

## 作者：chengni (赞：7)

有点贪心。我们不用考虑先飞还是先砍，直接最理想化。

把伤害从高到低排序，如果是飞的伤害，就把它飞出去，查找下一个伤害，直到该伤害为砍的伤害，然后一把刀砍到死就可以了。

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
struct p{
    int l;
    int r;
}a[1000000];
 
bool cmp(p xx,p yy){
    return xx.l>yy.l;
}
 
int main(){
    int n,h;
    int c=0;
    scanf("%d%d",&n,&h);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[c++].l);
        a[c].r=1;
        scanf("%d",&a[c++].l);
    }
    sort(a,a+c,cmp);
    int sum=0;
    for(int i=0;i<c;i++)
    {
        if(a[i].r==1)
        {
            sum++;
            h-=a[i].l;
            if(h<=0)
            {
                printf("%d",sum);
                return 0;
            }
        }
        else if(a[i].r!=1)
        {
            if(h%a[i].l==0) sum+=h/a[i].l;
            else sum+=h/a[i].l+1;
            printf("%d",sum);
            return 0;
            
        }
    }
}
```

---

## 作者：___new2zy___ (赞：6)

# 题解 AT3854 
# 【Katana Thrower】


## AtCoder Regular Contest 089  

## 题面翻译
  
  D - Katana Thrower
  
  当你突然遇到一个怪物时，你正在外出散步。 
  
  幸运的是，你有N卡塔娜（剑），武士刀1，武士刀2，...，武士刀N
  
  并可以以任何顺序执行以下两种攻击：
  
  1.挥舞你的武士刀之一。 当你使用武士刀i（1≤i≤N）时，怪物会受到ai点伤害同样的武士刀可以使用任何次数。
  
  2.扔你的一个武士刀。 当你把怪物卡塔纳i（1≤i≤N）扔到怪物身上时，它会受到bi的伤害，而你失去了武士刀。
    
   
   也就是说，你不能再使用或扔掉那个武士刀。
  
  当怪物获得的总伤害是H点或更多时，怪物将消失。 
  至少需要多少次攻击才能彻底杀死怪物？


**------------------------我是分割线--------------------------------------------------------------------------------------------------------------------------------------------
**


自己做完之后感觉是个~~大水题~~，难度有~~普及/提高-~~吧

本人在ATcoder做到本题时，略有点蒙，当时没看出来是贪心，结果..~~开始乱搞(搞了一个晚上233)~~，结果第二天猛地想到要~~xjb贪~~,不多说了，直接上代码~~~

     #include<iostream>
     #include<cstdio>
     #include<cmath>
     #include<algorithm>
     //#include<cstring>
     using namespace std;
     struct knife
     {
	     int ai;
	     bool f;
     }m[2000018];
     inline int read()
     {
       int p=0,f=1;char c=getchar();
       while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
       while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
       return f*p;}
     int N,H,ans;
     bool cmp(knife x,knife y)
     {
	     return x.ai>y.ai;//返回伤害最大的刀 
     }
     int main()
     {
	     N=read(),H=read();
	     for(int i=1;i<=N;i++)
	         m[i].ai=read(),
	   	  m[i+N].ai=read(),
	         m[i+N].f=true;
         //我们把每把刀看作是可以无限扔的和只能扔一次的两把刀，存进去 
	     sort(m+1,m+1+N*2,cmp);//排序，便于取 
	     int ans=0;           //ans最终答案
	     for(int i=1;i<=2*N;i++)//枚举2*N把刀 
	        {
              if(m[i].f)//接下来贪心，如果刀可以飞出去就废掉，同时加上伤害 
		        {ans++;
		         H-=m[i].ai;}
	          else
                 {
                  int u=H%m[i].ai;
                  //如果碰到第一把无限次飞而且伤害最高的就无限砍 
		          ans+=H/m[i].ai;
                  //一直砍到没血，记录ans+ 
	              if(u)ans++;
		  	    H=-1;
                 }
	           if(H<=0)
                 {printf("%d",ans);
                  return 0;}
                 //如果怪物没血了就输出 
	        }
     }
**完结撒花~~~**

顺便推广我的博客:
https://www.luogu.org/blog/new2zy/

---

## 作者：Mysterious_Cat (赞：4)

### 题目思路：
贪心，选出砍伤害最高的一把刀，然后把剩下的刀按投掷伤害排序，不断投掷，直到伤害小于砍刀伤害停止，然后一把刀砍到死，特判一下最后投不投掷，用一个vector存储即可
### Code：
```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10;
vector<long long> v;
int n;
long long a[maxn], b[maxn], h;
int main() {
	cin >> n >> h;
	int p = 1;
	for (int i = 1; i <= n; ++i) {
		scanf("%lld %lld", &a[i], &b[i]);
		
		if (a[p] < a[i] || a[p] == a[i] && b[p] > b[i]) p = i;
	}
	
	for (int i = 1; i <= n; ++i) {
		if (i != p && b[i] >= a[p]) {
			v.push_back(b[i]);
		}
	}
	sort(v.begin(), v.end());
	
	int len = v.size(); 
	long long ans = 0, t = 0;
	for (int i = len - 1; i >= 0; i--) {
		if (ans >= h) {
			cout << t;
			return 0;
		}
		t ++;
		ans += v[i];
	}
	long long delta = (h - ans);
	
	if (delta <= b[p]) {
		t ++;//特判一下
	} else {//砍刀
		t++;
		delta -= b[p];
		t += delta / a[p];
		if (delta % a[p] != 0)//特判一下
			t++;
	}
	cout << t;
	return 0;
}
```
感谢老师[cookiebus](https://www.luogu.com.cn/user/154195)带我写完了~~调了一年的~~代码

---

## 作者：happybob (赞：2)

先求出只挥不扔的答案，然后按照飞的值从大到小排序后模拟即可。

代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 1e5 + 10;
int a[MAXN];
int b[MAXN];
int ans = 0, max_a = 1, h = 0, n, k;

int main()
{
	scanf("%d%d", &n, &h);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &a[i], &b[i]);
		max_a = max(max_a, a[i]);
	}
	ans = ceil(double(h) / max_a);	//只挥不扔
	sort(b + 1, b + 1 + n, greater<int>());			//从大到小排序
	for (int i = 1; i <= n; i++)
	{
		h -= b[i];
		if (h < 0) h = 0;
		k = i + ceil(double(h) / max_a);
		ans = min(ans, k);
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：Hilte (赞：1)

# 一.基本思路
这是一道贪心题。

我们可以发现：
- 砍的话就用**砍的伤害值最大**的刀去砍
- 要扔就全部扔出去（除了**扔的伤害比砍的还小**的刀之外）

# 二.贪心思路
1. 要扔的话，我们要先扔伤害值最大的刀，这样怪物死的快

2. 当**扔的伤害比砍的还小**时就不用扔了
3. 如果怪物被扔死了直接输出答案
4. 如果怪物还没死就用**砍的伤害值最大**的刀去砍死

# 三.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
  
int n, h, a[100005], b[100005], ans = 0;
int main() 
{
    cin >> n >> h;
    for (int i = 1; i <= n; i++)
    	cin >> a[i] >> b[i];
    sort(a + 1, a + n + 1);//排序
    sort(b + 1, b + n + 1);
    
    for (int i = n; i >= 1 && b[i] > a[n] && h > 0; i--)//用刀扔及其特殊情况
    	h -= b[i], ans++;
    if (h > 0)//如果怪物没死就砍
    	ans += (h / a[n] + (h % a[n] != 0));
    
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Fat_Fish (赞：1)

将两种情况装进一个数据

从大到小排序，始终选取伤害最大的即可
（当然，飞的只能用一次）

典型的**贪心**思想，时间复杂度$O(n)$

具体细节详见代码

$Code$

```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+20;
struct node{
	int a;
	int x;//0砍 1飞
}s[N];
bool cmp(node x,node y){
	return x.a>y.a;//手写cmp
}
int main(){
	int h,n;
	cin>>n>>h;
	for(int i=1;i<=2*n;++i){
		cin>>s[i].a;
		if(i&1){
			s[i].x=0;//砍
		}
		else {
			s[i].x=1;//飞
		}
	}
	sort(s+1,s+1+2*n,cmp);
	int ans=0;
	for(int i=1;i<=2*n;++i){
		if(h<=0){
			break;//如果怪死了，退出
		}
		if(s[i].x==0){
			ans+=ceil(h*1.0/s[i].a);//如果砍，全部用砍
			break;
		}
		else {
			h-=s[i].a;//飞只使用一次
			++ans;
		}
	}
	cout<<ans<<'\n';//输出
	return 0;
}
```


---

