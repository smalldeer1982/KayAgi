# Water Taps

## 题目描述

Consider a system of $ n $ water taps all pouring water into the same container. The $ i $ -th water tap can be set to deliver any amount of water from $ 0 $ to $ a_{i} $ ml per second (this amount may be a real number). The water delivered by $ i $ -th tap has temperature $ t_{i} $ .

If for every ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/035d166bda223ecd5c31eb614a76bdcc9b8fe8c4.png) you set $ i $ -th tap to deliver exactly $ x_{i} $ ml of water per second, then the resulting temperature of water will be ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/4d0f711b0c4dc1450cd61a20f118d34a644e0d79.png) (if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF954E/dbce41b29215315b290a54646261b5eaa9727507.png), then to avoid division by zero we state that the resulting water temperature is $ 0 $ ).

You have to set all the water taps in such a way that the resulting temperature is exactly $ T $ . What is the maximum amount of water you may get per second if its temperature has to be $ T $ ?

## 样例 #1

### 输入

```
2 100
3 10
50 150
```

### 输出

```
6.000000000000000
```

## 样例 #2

### 输入

```
3 9
5 5 30
6 6 10
```

### 输出

```
40.000000000000000
```

## 样例 #3

### 输入

```
2 12
1 3
10 15
```

### 输出

```
1.666666666666667
```

# 题解

## 作者：欧鹰 (赞：1)

（日常聊天）第四道cf题解（个人觉得CF题挺好的）。



------------


首先看原题的式子，我们会发现他很容易变成∑xi(ti−T)=0这个式子，然后~~显然~~这是道贪心。

每次其实就是把一边选完（即ti<T与ti>T两边），看着这两个哪个大，就选那个小，为了保证这个数可以成0；

然后如果，都是大于等于T或小于等于T，就特判一下。

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

struct node{
	int num,t;
}water[2200500];

int n,t,sum,ans,num1,num2,num3;

bool cmp(node a,node b)
{
	return a.t<b.t;
}

signed main()//主程序
{
	cin>>n>>t;
	
	for(int i=1;i<=n;i++) cin>>water[i].num;
	
	for(int i=1;i<=n;i++)
	{
		int tt;
		
		cin>>tt;
		
		water[i].t=tt-t;
		
		if(water[i].t<0) num1+=water[i].t*water[i].num;
		
		else if(water[i].t>0) num2+=water[i].t*water[i].num;
		
		else num3+=water[i].num;
	}
	
	sort(water+1,water+1+n,cmp);
	
	if(num1==0||num2==0)
	{
		printf("%.15f",(double)num3);
		
		return 0;
	}

	else if(-num1<num2)
	{
		for(int i=1;i<=n;i++)
		{
			if(sum+water[i].t*water[i].num>=0)
			{
				double anss=(double)ans+(double)(-sum)/(double)water[i].t;
				
				printf("%.15f",anss);

				return 0;
			}
		
			sum+=water[i].t*water[i].num;
		
			ans+=water[i].num;
		}
	}
	
	else
	{
		for(int i=n;i>=1;i--)
		{
			if(sum+water[i].t*water[i].num<=0)
			{
				double anss=(double)ans+(double)sum/(double)(-water[i].t);
			
				printf("%.15f",anss);

				return 0;
			}	
		
			sum+=water[i].t*water[i].num;
		
			ans+=water[i].num;
		}
	}
	
	return 0;
}
```


---

## 作者：UncleSam_Died (赞：1)

### 解题思路
其实题目翻译中已经给出一些提示了。

显然，对于式子 $\displaystyle \frac{\displaystyle\sum_{i=1}^n x_i\times t_i}{\displaystyle \sum_{i=1}^n x_i}=T$，我们稍加变形就可以得到 $\displaystyle \sum_{i=1}^n x_i\times(t_i-T)=0$。考虑在读入的时候，对于每一个 $i\in [1,n]$，进行操作 $t_i\gets t_i-T$，那么这时的式子即转变为 $\displaystyle \sum_{i=1}^n x_i\times t_i=0$。

观察可以发现，在有解的条件下，只有三种 $t_i$ 的取值可以满足：
- $\forall i\in[1,n]$，$t_i=0$；
- $\forall i \in [1,n]$，一部分 $t_i>0$ 剩下的 $t_i<0$；
- $\forall i \in [1,n]$，一部分 $t_i>0$ ，一部分 $t_i<0$，其余的 $t_i=0$；

将这三种情况综合一下，可以发现只需要第三种情况，那么当 $t_i=0$ 时，$x_i\times t_i=0$，即这个水龙头无论出多少水，对式子的成立情况都没有影响。那么，我们可以直接让这些水龙头的出水取最大值 $a_i$，在接下来的步骤中排除这些水龙头即可。

对于剩下的水龙头，我们考虑按照温度从小到大排序后双指针，设当 $i=c$ 时，$t_i<0$ 且 $t_{i+1}>0$，那么，我们令 $l=c$，$r=c+1$，分别向 $1$ 和 $m$ 移动，其中 $m$ 是 $t_i$ 不为 $0$ 的水龙头的数量。分以下三种情况考虑：
- $a_l\times t_l+a_r\times t_r<0$ ，也就是说，如果此时 $l$ 和 $r$ 水龙头均打开到最大值，那么温度将低于 $0$（减去后的温度），因此，选择将 $r$ 开到最大值，同时调节 $l$，使得温度恰好为 $0$。由于 $l$ 仍然存在一些水量进行分配，那么我们将 $r$ 向右移动一位，同时把 $l$ 的剩余的水量 $a_l\gets a_l-(-\frac{(a_r\times a_t)}{t_l})$；
- $a_l\times t_l+a_r\times t_r>0$ ，也就是说，如果此时 $l$ 和 $r$ 水龙头均打开到最大值，那么温度将高于 $0$（减去后的温度），因此，选择将 $l$ 开到最大值，同时调节 $r$，使得温度恰好为 $0$。由于 $r$ 仍然存在一些水量进行分配，那么我们将 $l$ 向左移动一位，同时把 $r$ 的剩余的水量 $a_r\gets a_r-(-\frac{(a_l\times a_l)}{t_r})$；
- $a_l\times t_l+a_r\times t_r=0$，两个水龙头均开到最大，并同时分别向左、右移动一。

### AC 代码
代码进行防抄袭处理，勿直接 copy。
```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 200005
#define eps 1e-15
int n;double T,t[N],a[N];
struct Tap{
	double t;
	double a;
}tap[N];int m;
inline bool cmp(Tap A,Tap B){
	return A.t<B.t;
}signed main(){
	scanf("%d%lf",&n,&T);
	for(register int i=1;i<=n;++i)
		scanf("%lf",&a[i]);
	for(register int i=1;i<=n;++i)
		scanf("%lf",&t[i]);
	for(register int i=1;i<=n;++i)
		t[i]=t[i]-T;
	double ans=0.0;
	for(register int i=1;i<=n;++i){
		if(fabs(t[i])<=eps)
			ans+=a[i];
		else tap[++m]={t[i],a[i]};
	}std::sort(tap+1,tap+m+1,cmp);
	int l=1,r=m;
	while(tap[l].t+eps<=0) ++l;--l;
	while(tap[r].t+eps>=0) --r;++r;
	while(l>=1&&r<=m){
		double _1=tap[l].a*tap[l].t;
		double _2=tap[r].a*tap[r].t;
		if(_1+_2+eps<0){
			tap[l].a-=-_2/tap[l].t;
			ans+=tap[r].a-_2/tap[l].t;
			++r;
		}else if(_1+_2-eps>0){
			tap[r].a-=-_1/tap[r].t;
			ans+=tap[l].a-_1/tap[r].t;
			--l;
		}else{
			ans+=tap[l].a;
			ans+=tap[r].a;
			--l,++r;
		}
	}printf("%12.lf",ans);
}
```

---

## 作者：Fimlty (赞：0)

提供一种~~清晰、优雅~~，不需要太多判断语句的实现方式。

具体内容在代码里解释。

```cpp
#include<bits/stdc++.h>
using namespace std;
const double ex = 1e-8;
int n;
double T, ans = 0, AA[200005], TT[200005];
vector<pair<double, double>>H, C;
int main(){
    cin >> n >> T;
    for(int i = 1; i <= n; i++) cin >> AA[i];
    for(int i = 1; i <= n; i++) cin >> TT[i];
    for(int i = 1; i <= n; i++){
        double a = AA[i], t = TT[i];
        t -= T;//改成相对温度
        if(fabs(t) < ex)ans += a;//和目标温度相同的水直接计入答案
        else{
            if(t < 0) C.push_back({fabs(t), a});
            else H.push_back({t, a});
        }//按正负分两类存储
    }
    sort(H.begin(), H.end());
    sort(C.begin(), C.end());确保有序
    int hl = 0, cl = 0;
    while(hl < H.size() && cl < C.size()){
        auto& [ht, ha] = H[hl];
        auto& [ct, ca] = C[cl];//取址 + auto 关键字便于访问修改
        if(ht * ha > ct * ca + ex){//热水太多了
            ans += (ct * ca / ht) + ca;
            ha -=  (ct * ca / ht);
            cl++;
        }
        else if(ht * ha + ex < ct * ca){//冷水太多了
            ans += (ht *  ha / ct) + ha;
            ca -=  (ht * ha / ct);
            hl++;
        }//根据较少的水的量进行操作，直接在变量上修改，可以修改掉 vector 里的值
        else {
            ans += ha + ca;
            hl++, cl++;
        }//若一样多，直接全计入答案，指针都向后移动
    }//只要有一种水用完就结束循环
    cout << fixed << setprecision(7) << ans;
}
```

---

## 作者：LiJoQiao (赞：0)

洛谷的翻译给出的是形式化题意，这里写一下原题意描述：  

> 有 $T$ 个水龙头，每个水龙头可以流出最多 $a_i$ 的量的温度为 $t_i$ 的水，求最多可以得到多少温度为 $T$ 的水，若无法得到则输出 $0$。  

我们把水分成三类，温度较 $T$ 高的热水是一类，温度较 $T$ 低的冷水是一类，还有一类是温度正好为 $T$ 的温水。  

题意求的最终温水可以是原来就存在的温水，也可以是一些冷水和热水掺起来后的水。  

我们将前者直接累加进答案，后者我们希望能掺的越多越好。  

以下水的热量差均指与等量温水的热量差。  

因为由热水和冷水可以掺出来温水，这个过程的充要条件是还存在热水和冷水，即存在热水的热量差和冷水的热量差。  
所以热水和冷水都存在热量差就可以继续得到温水，不能得到温水时至少有一类水的热量差已用尽。  
题意想要最多的温水，我们肯定会不断进行掺水的过程直到不能得到温水。  

有一些解能满足一类水热量差是 $0$，但不是最优解。研究得到该解的过程可以发现，相较于最优解，其过程中掺水所用的水的温度与 $T$ 相差较大。  

可以发现在等量的情况下，水的温度与 $T$ 的差越大，在掺水过程中抵消热量差就越多。也就是抵消等热量差的条件下，水的温度与 $T$ 的差越大，可以掺出的水越少。所以掺水的时候需要在两类水中都需要从温度接近 $T$ 的水开始向温度不接近 $T$ 的水的方向选取。  

最后掺水要么会剩下热水，要么会剩下冷水，要么刚好掺完。  

双指针不是很好写，这里我写了一个小的分类讨论。  
记录一下热水的热量差和冷水的热量差，然后让最小值与其相反温度的水里面贪心选取即可。  

代码如下。  

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int MAXN=2e5+10;
int n,T;
ll rs,ls;
double ans=0;
struct slt{
    int a,t;
    bool operator<(const slt x)const{
        return t<x.t;
    }
}a[MAXN];
int main(){
    scanf("%d%d",&n,&T);
    for(int i=1;i<=n;++i)scanf("%d",&a[i].a);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i].t);a[i].t-=T;
        if(a[i].t<0)ls-=(ll)a[i].t*a[i].a;
        else if(a[i].t==0)ans+=a[i].a;
        else rs+=(ll)a[i].t*a[i].a;
    }
    sort(a+1,a+n+1);
    if(ls<rs){
        for(int i=1;i<=n;++i){
            if(a[i].t<0){ans+=a[i].a;}
            else if(a[i].t>0){
                if((ll)a[i].t*a[i].a<=ls){
                    ls-=(ll)a[i].t*a[i].a;
                    ans+=a[i].a;
                }else{
                    ans+=(double)ls/a[i].t;
                    break;
                }
            }
        }
    }else{
        for(int i=n;i>=1;--i){
            if(a[i].t>0){ans+=a[i].a;}
            else if(a[i].t<0){
                if((ll)-a[i].t*a[i].a<=rs){
                    rs+=(ll)a[i].t*a[i].a;
                    ans+=a[i].a;
                }else{
                    ans+=(double)rs/-a[i].t;
                    break;
                }
            }
        }
    }
    printf("%lf\n",ans);
    return 0;
}
```



---

## 作者：lizicheng3042 (赞：0)

~~说实话好像不难~~  
## 题目思路
首先，题目中要求我们找到用水的最大值。我们实际上来考虑这样一个问题：有若干种可以购买的商品和若干种可以售出的商品，怎么样销售才能做到买入和卖出的商品的数目最多且收入和支出相等？答案显然是优先购买单价最小的商品和售出单价最小的商品，这是一个可以想出来的结论。  
回归本题，我们发现，这个题的思路可以转化为我们刚刚思考的问题：把水当作商品，把水龙头的出水量当作商品数，那么单价是什么呢？因为题目要求的是达到固定温度，所以我们可以认为，单价实际上是给定温度与水温的差，那么可以认为小于 $0$ 是售出，大于 $0$ 是买入，问题转化为上述题目。  
这样的话，我们就只需要将每个水龙头的温度减去 $T$，然后再按温度排序。此时可以分成三部分：  
1. 温度等于目标温度的，可以直接加满。  
2. 小于，可以拿去与温度大于的抵消。  
3. 大于，可以和温度小于的抵消。  

我们发现，最后答案的最大值一定是一方把另一方完全抵消，只需要模拟这个过程即可，复杂度 $O(n)$。
## 代码
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps=5e-7;
int n,temp[200005],start;
double T,ans;
struct node
{
	double v,whole,u;
	bool operator <(const node &a){return u<a.u;}
}k[200005];
int main()
{
	scanf("%d%lf",&n,&T);
	for(int a=1;a<=n;a++)
		scanf("%lf",&k[a].v);
	for(int a=1;a<=n;a++)
	{
		scanf("%d",&temp[a]);
		k[a].u=temp[a]-T;
		k[a].whole=(temp[a]-T)*k[a].v;
	}
	sort(k+1,k+n+1);
	k[0].u=-10;k[n+1].u=10;
	for(int a=1;a<=n+1;a++)
		if(k[a].u>0&&k[a-1].u<=0)
		{
			start=a;		
			break;	
		}
	if(start==n+1||start==1)
	{
		for(int a=1;a<=n;a++)
		{
			if(abs(k[a].u)<=eps)
				ans+=k[a].v;
		}
		if(ans<=eps)
			printf("0");
		else
			printf("%lf",ans);
		return 0;
	}
	int l=start-1,r=start;
	while(l>0&&r<=n)
	{
		if(abs(k[l].whole-k[r].whole)<=eps)
		{
			ans+=k[l--].v+k[r++].v;
		}
		else
		{
			if(abs(k[l].whole)>k[r].whole)
			{
				double c=k[r].whole/abs(k[l].u);
				k[l].whole+=k[r].whole;
				ans+=k[r++].v+c;
				k[l].v-=c;
			}
			else
			{
				double c=abs(k[l].whole)/k[r].u;
				k[r].whole+=k[l].whole;
				ans+=k[l--].v+c;
				k[r].v-=c;				
			}
		}
	}
	printf("%lf",ans);
	return 0;
}
```



---

## 作者：Kelin (赞：0)

### [题意](https://blog.csdn.net/benoble_/article/details/79658969)

$\forall x_i\in[1,a_i],$对于所有满足$\sum_{i=1}^nx_i(t_i-T)=0$的情况,求$\sum_{i=1}^nx_i$的最大值

---

### 题解

先把$t_i$减去$T$,然后按照$t$排序

把数组分成两块,一半小于等于$0$,一半大于$0$

用贪心的思想,可以发现有一半必须全选,另一半选最靠近$T$的那些

证明:

假设负数集里面还有一些没选,正数集里还有数剩余

那么我们就可以把他们凑出一个$0$出来,直到某一边用完为止.证毕.

~~后半句话是显然的...~~

所以就可以直接贪心了

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(int i=a,I=b-1;i>I;--i)
#define go(u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){if(A==B){B=(A=ss)+fread(ss,1,1<<17,stdin);if(A==B)return EOF;}return*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),c<48||57<c)if(c=='-')y=-1;x=c^48;
    while(c=gc(),47<c&&c<58)x=(x<<1)+(x<<3)+(c^48);x*=y;
}
const int N=2e5+5;
const double eps=1e-8;
typedef int arr[N];
int n,T;double tp,ans;
struct da{int a,t;double s;}a[N];
inline bool cmp(da a,da b){return a.t<b.t;}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    sd(n);sd(T);
    fp(i,1,n)sd(a[i].a);fp(i,1,n)sd(a[i].t),a[i].t-=T;
    sort(a+1,a+n+1,cmp);
    if(a[1].t>0||a[n].t<0)return puts("0"),0;
    fp(i,1,n)a[i].s=(double)a[i].a*a[i].t,tp+=a[i].s;
    if(tp<0){fp(i,1,n)a[i].t=-a[i].t,a[i].s=-a[i].s;reverse(a+1,a+n+1);}
    tp=0;
    fp(i,1,n){
    	if(tp+a[i].s>0){ans+=(-tp)/a[i].t;break;}
    	tp+=a[i].s,ans+=a[i].a;
	}
	printf("%.6lf",ans);
return 0;
}
```

---

