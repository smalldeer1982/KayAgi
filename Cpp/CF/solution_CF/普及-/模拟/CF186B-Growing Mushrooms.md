# Growing Mushrooms

## 题目描述

每年，矮人王城堡里都会举行矮人种植蘑菇比赛。这项比赛是最负盛名的比赛之一，获胜者会得到一个木制沙拉碗。今年的比赛汇集了世界各地最优秀的蘑菇种植者，因此我们不得不对比赛规则稍作改动，使比赛更具观赏性。

每位蘑菇种植者都有自己要在比赛中种植的蘑菇。根据新规则，比赛由两部分组成。第一部分持续 $t1$ 秒，第二部分持续 $t2$ 秒。第一部分和第二部分之间有一小段休息时间。

哨声响起后，比赛的第一部分开始，所有蘑菇种植者同时开始种植蘑菇，每个人的速度为 $v_i$ 米/秒。$t1$ 秒后，蘑菇种植者停止种植蘑菇，开始休息。在休息期间，由于不明原因，所有蘑菇的生长量减少了 $k$% 。休息后，比赛的第二部分开始，所有种菇人同时继续种菇，每个人的速度为 $u_i$ 米/秒。经过 $t2$ 秒后，比赛结束。注意休息前后的速度可能不同。

赛前，小矮人帕夏向所有参赛者了解了他们选择的两种速度。不过，参赛者并不想向他透露自己的所有策略，因此也没有说他们将按照什么顺序使用这些速度。也就是说，如果参与者选择了速度 $a_i$ 和 $b_i$，则有两种策略：他要么先使用速度 $a_i$，后用 $b_i$，反之亦然。 

小矮人帕夏非常想赢得总分赛。他知道每个参赛者都会选择使蘑菇高度最大化的策略。帮助小矮人帕夏制作比赛结果的最终表格。

在成绩表中，参赛者按蘑菇高度排序（蘑菇高度高的参赛者排在前面）。如果蘑菇高度相同，则按参赛者的编号排序（编号小的参赛者排在前面）。

## 样例 #1

### 输入

```
2 3 3 50
2 4
4 2
```

### 输出

```
1 15.00
2 15.00
```

## 样例 #2

### 输入

```
4 1 1 1
544 397
280 101
280 101
693 970
```

### 输出

```
4 1656.07
1 937.03
2 379.99
3 379.99
```

# 题解

## 作者：canwen (赞：4)

## 分析
总的来说，题意就是在两种速度里面规划一种最划算的顺序，计算出对应的蘑菇种植高度进行排序。

计算式子样例解释都能看出来。

用 $a_{i},b_{i},t1,t2,k$ 分别表示每个参赛者的两种速度，两段时间和蘑菇一段时间内生长的百分比，对应的最后的蘑菇高度是:

$$\max( (1-k)a_{i}t1 + b_{i}t2, (1-k)b_{i}t1 + a_{i}t2)$$

接着进行排序，这里给出一种在结构体内重载运算符的写法，在写其他数据结构（如大根堆、小根堆）也会经常使用的。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define i(a,b,c) for(int i=(a);i<=(b);i+=(c))
struct node{
	int id;double num;
	bool operator<(const node &tmp)const{if(tmp.num==num) return tmp.id>id; else return tmp.num<num;}//重载运算符 	
}v[1005];
int n,t1,t2;double k;
signed main(){
	cin>>n>>t1>>t2>>k,k/=100;//先化成百分数（k是double类型） 
	i(1,n,1){
		double a,b;cin>>a>>b;
		v[i].num=max((1-k)*a*t1+b*t2,(1-k)*b*t1+a*t2),v[i].id=i;//id --> 选手编号 
	}
	sort(v+1,v+1+n);
	i(1,n,1) printf("%lld %.2f\n",v[i].id,v[i].num);
	return 0;
}
```

---

## 作者：miraculously (赞：4)

题目大意：

有 $n$ 个蘑菇，蘑菇生长分成两个部分，在 $T_1$ 的时间里蘑菇生长速度减少百分之 $k$,在 $T_2$ 的时间里正常速度生长，每个蘑菇有两个速度，在两个时间段分别用一个速度，使蘑菇高度最高，蘑菇按高度从小到大输出，如果高度相同先输出编号小的。

分析：

这题直接把两个速度代入 $T_1$,$T_2$ 中，然后再把速度换一下，比较二者高度，取较大值。

代码实现（有注释）：



```cpp
#include<bits/stdc++.h>
using namespace std;
struct name{
	int h,id;//h表示每个蘑菇的高度，id表示蘑菇的编号
}bl[1001];
bool cmp(name x,name y)
{
	if(x.h==y.h)
	return x.id<y.id;
	return x.h>y.h;
}//蘑菇从大到小排序，大小相同，编号从小到大排序
int main()
{
	int n,t1,t2,k,a,b;
	scanf("%d%d%d%d",&n,&t1,&t2,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		bl[i].id=i;
		bl[i].h=max(a*(100-k)*t1+b*100*t2,a*100*t2+b*(100-k)*t1);//将a速度和b速度分别用两个时间算一下，取最大值，我这里把高度扩大一百倍，好写
	}
	sort(bl+1,bl+n+1,cmp);
	for(int i=1;i<=n;i++)
	printf("%d %.2lf\n",bl[i].id,0.01*bl[i].h);//之前高度扩大一百倍，所以乘上0.01
}
```


---

## 作者：RE_Prince (赞：3)

# CF186B

[link](https://www.luogu.com.cn/problem/CF186B)

## Sol


一道不错的模拟题。


按照题目要求，分类讨论两种情况：$a_i\rightarrow b_i$ 还是 $b_i\rightarrow a_i$。值得注意的是过了 $t_1$ 分钟后下降的长度需要简单处理一下。最后将所有蘑菇的高度还要排个序。见代码。

```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
double m,c,t1,t2;
int n;
int i,j,k;
const int N=1e5+9;
double a[N],b[N];
struct Mush
{
	int id;
	double height;
}d[N];//方便排序的结构体
inline bool cmp(Mush x,Mush y)
{
	if(x.height==y.height) return x.id<y.id;
	return x.height>y.height;
}//注意第一个判断，一样高编号小的在先
signed main()
{
	cin>>n>>t1>>t2>>c;
	c/=100;//预处理c
	for(i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(i=1;i<=n;i++)
	{
		double r1=(1-c)*a[i]*t1+b[i]*t2;
		double r2=(1-c)*b[i]*t1+a[i]*t2;
		d[i]={i,max(r1,r2)};//计算哪种更高
	}
	cout<<fixed<<setprecision(2);//两位小数
	sort(d+1,d+n+1,cmp);
	for(i=1;i<=n;i++) cout<<d[i].id<<" "<<d[i].height<<endl;
	return 0;//华丽结束
}
```

---

## 作者：abc1234shi (赞：2)

一道模拟题，因为最后要输出编号和值，所以使用结构体解题会更好。

我们算出如果先使用速度 $a_i$，后使用速度 $b_i$ 可生长的高度，和如果先使用速度 $b_i$，后使用速度 $a_i$ 可生长的高度，取一个最大值就好了。

难点在于如何算，我们以先使用速度 $a_i$，后使用 $b_i$ 为例。我们先算出使用速度 $a_i$ 时，蘑菇上升了 $t_1\times a_i$ 米，但是休息时间它会下降，下降的高度就为刚刚上升的高度的 $k\%$ ，计算方算就为 $t_1\times a_i\times \frac{k}{100}$。后使用 $b_i$ 的蘑菇高度又上升了 $t_2\times b_i$，把两个高度相加再减去下降的高度即可。那么我们以先使用速度 $a_i$，后使用 $b_i$ 的公式就为 $a_i \times t_1\times\frac{100-k}{100}+b_i\times t_2$，注意答案该开始时答案要 $\times1.00$，不然会出现精度误差。

如果先使用速度 $b_i$，后使用速度 $a_i$ 可生长的高度，计算方式与先使用速度 $a_i$，后使用 $b_i$ 的计算方式同理，公式仅需将 $a_i$ 和 $b_i$ 的位置交换一下，就为 $b_i \times t_1\times \frac{100-k}{100}+a_i\times t_2$。最后取两个的最大值就是这个蘑菇的最终最大高度。

算完所有的后从大到小排序，依此输出编号和最终最大高度即可，注意换行。

---

## 作者：zengxuheng (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF186B)

---
# solution：
对于每个小矮人，直接把两个速度 $a_i$，$b_i$ 代入 $t_1$，$t_2$ 中计算蘑菇高度，然后再把 $a_i$，$b_i$ 位置互换一下，再计算一次，取二者高度较大值即可。

当速度 $a$ 带入 $t_1$，速度 $b$ 带入 $t_2$ 时，高度公式为：

$$a \times t_1 \times (1-k) \div 100 + b \times t_2$$

反之，当速度 $b$ 带入 $t_1$，速度 $a$ 带入 $t_2$ 时，高度公式为：

$$b \times t_1 \times (1-k) \div 100 + a \times t_2$$

# 代码：

思路理清楚了，就是代码时间了：
```
#include<bits/stdc++.h>
using namespace std;
struct node{//为了输出编号，所以要用结构体
	int i;
	double z;
}a[1010];
bool cmp(node x,node y){
	if(x.z!=y.z) return x.z>y.z;
	return x.i<y.i;
}
int main(){
	int n,t1,t2,k,x,y;
	cin>>n>>t1>>t2>>k;
	for(int i = 1;i <= n;i++){
		cin>>x>>y;
		a[i].i=i;
		a[i].z=max(1.0*x*t1*(100-k)/100+1.0*y*t2,1.0*y*t1*(100-k)/100+1.0*x*t2);//主要代码
	}
	sort(a+1,a+n+1,cmp);//排序
	for(int i = 1;i <= n;i++) cout<<a[i].i<<" "<<fixed<<setprecision(2)<<a[i].z<<'\n';//输出
}
```
**完结撒花**

---

## 作者：Ljh421 (赞：1)

感谢@[LYC20111119](https://www.luogu.com.cn/user/1126085) 提供的部分思路。

### 思路 

一道非常简单的模拟题。

主要就是看是先用 $u$ 速度还是 $v$ 速度，只需要计算出来用这两种速度的高度，然后取一个 max 就可以了。

最后按高度从大到小(如果高度相同就按编号从小到大)排一下序，输出答案。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,t1,t2;
double k;
struct node{
	int id;//选手的编号
	double a,b;//速度
	double ans;//高度
}e[N];
bool cmp(node a,node b){
	if(a.ans==b.ans) return a.id<b.id;//高度相同，按序号排序
	return a.ans>b.ans;
}
int main(){
	
	cin>>n>>t1>>t2>>k;//输入
	k/=100;//换成百分比
	for(int i=1;i<=n;i++){
		cin>>e[i].a>>e[i].b;
		e[i].id=i;
		double ans1=e[i].a*t1*(1-k)+e[i].b*t2,ans2=e[i].b*t1*(1-k)+e[i].a*t2;
		//看是先用a速度生长高度高，还是用b速度生长速度高
		e[i].ans=max(ans1,ans2);
	}
	sort(e+1,e+n+1,cmp);//排序
	for(int i=1;i<=n;i++){
		cout<<e[i].id<<" ";//输出
		printf("%.2lf\n",e[i].ans);
	}
	
	return 0;
}
```

不喜勿喷，最后点个赞吧，QWQ。

---

## 作者：wangzc2012 (赞：1)

# CF186B Growing Mushrooms
## 思路分析
一道简单的~~膜你~~模拟题，题目意思很明确，这里不再赘述。  
瞪眼法不难发现，这里有两种方案，分别是 $a \to b$ 和 $b \to a$，直接算出两种方案分别能让蘑菇长多高，然后取较大值，并按题意排序即可。  
## 注意事项
本题有几个很坑人的点需要注意：  
- 题目描述中，在 $T_{1}$ 时间里种植的蘑菇生长速度会减少**百分之** $k$，所以计算时 $k$ 要除以 $100$。
- 蘑菇高度要**从大到小**并**保留两位小数**输出，高度一样则编号**小**在前。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t1,t2;
double a,b,k;
struct m{  //结构体方便排序
    int id;  //编号
    double h;  //高度
}lt[1005];
bool cmp(m x,m y){
    if (x.h==y.h) return x.id<y.id;  //高度一样，编号小在前
    else return x.h>y.h;  //否则高度大在前
}
int main(){
    cin>>n>>t1>>t2>>k;
    k/=100;  //特别注意这一行，详见“注意事项”
    for (int i=1;i<=n;i++){
        cin>>a>>b;
        lt[i].id=i;  //编号
        lt[i].h=max((1-k)*a*t1+b*t2,(1-k)*b*t1+a*t2);  //计算两种方案的高度，取较大值
    }
    sort(lt+1,lt+n+1,cmp);  //排序
    for (int i=1;i<=n;i++) printf("%d %.2f\n",lt[i].id,lt[i].h);  //输出编号和高度（保留两位小数）
    return 0;  //圆满结束！
}
```

---

## 作者：hcy1117 (赞：1)

## 一句话题意
算出每个参赛者的蘑菇的最大高度并进行排序([题目传送门](https://www.luogu.com.cn/problem/CF186B)）。
## 思路
题目要求求高度但没有说哪个速度在前，哪个速度在后，所以要把两种情况都算出来取最大值。

1. 速度 $a$ 在前，高度为 $ a \times t_{1} \times (1-k)\div 100.0+b \times t_{2}$。
1. 速度 $b$ 在前，高度为 $ b \times t_{1} \times (1-k)\div 100.0+a \times t_{2}$。

最后排序可以使用结构体存下高度和编号（输入的顺序），直接快排。

其余不懂的可以参考代码与注释。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	double h;//高度 
	int id;//编号 
}w[1005];
bool cmp(node x,node y)//结构体排序 
{
	if(x.h==y.h)return x.id<y.id;
	return x.h>y.h;
}
int main()
{
	int n,t1,t2;
	double k;
	cin>>n>>t1>>t2>>k;
	k/=100;
	k=1-k;//提前处理k 
	for(int i=1;i<=n;i++)
	{
		int a,b;
		cin>>a>>b;
		w[i].h=max((a*t1)*k*1.0+b*t2*1.0,(b*t1)*k*1.0+a*t2*1.0);//计算高度 
		w[i].id=i;
	}
	sort(w+1,w+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		printf("%d %.2lf\n",w[i].id,w[i].h); 
	}
}
```

---

## 作者：_int123_ (赞：1)

题目：

## Growing Mushrooms

### 题意：

给你 $n$ 个蘑菇，蘑菇生长分为两个部分，$t_1$ 和 $t_2$。在 $t_1$ 的时间里蘑菇生长速度会减少 $k\%$，在 $t_2$ 的时间里就以其正常速度生长。

每个蘑菇在两个时间段分别有一个速度，我们想让蘑菇的高度最高，最后按蘑菇的高度从小到大输出，如果高度相同的话就先输出编号小的。

### 思路：

首先，我们可以使用结构体来记录每一个蘑菇的编号和高度。

```cpp
struct node
{
	int num;//编号 
	double h;//高度 
}mushroom[100005];
```

由于每个蘑菇在两个时间段分别有一个速度，我们想让蘑菇的高度最高，所以两者分别代入，求最大值。

```cpp
	for(int i=1;i<=n;i++) mushroom[i]={i,max((1-k)*a[i]*t1+b[i]*t2,(1-k)*b[i]*t1+a[i]*t2)};//蘑菇高度为更大的那一个 

```

最后将蘑菇高度排序。

```cpp
bool cmp(node x,node y)//排序 
{
	if(x.h==y.h) return x.num<y.num;//高度一样先输出编号小的 
	return x.h>y.h;//不然先输出高度高的 
}
```

然后就差不多了。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
#define int long long//习惯开 long long，虽然这题没用 
using namespace std;
int n;
double a[100005],b[100005];//蘑菇生长的速度 
double k,t1,t2;
struct node
{
	int num;//编号 
	double h;//高度 
}mushroom[100005];
bool cmp(node x,node y)//排序 
{
	if(x.h==y.h) return x.num<y.num;//高度一样先输出编号小的 
	return x.h>y.h;//不然先输出高度高的 
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>n>>t1>>t2>>k;
	k/=100;//k%，要除以100 
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++) mushroom[i]={i,max((1-k)*a[i]*t1+b[i]*t2,(1-k)*b[i]*t1+a[i]*t2)};//蘑菇高度为更大的那一个 
	sort(mushroom+1,mushroom+n+1,cmp);//排序 
	for(int i=1;i<=n;i++) cout<<fixed<<setprecision(2)<<mushroom[i].num<<" "<<mushroom[i].h<<'\n';//保留两位小数输出 
	return 0;
}

```

完结撒花！！！


---

## 作者：sun_qy (赞：1)

# CF186B Growing Mushrooms 题解

[洛谷链接](https://www.luogu.com.cn/problem/CF186B)
[CF链接](https://codeforces.com/problemset/problem/186/B)

## 题意简述

有 $n$ 个蘑菇，在 ${T_1}$ 时间内蘑菇的生长速度是正常速度的 $(100-k)\%$，在 ${T_2}$ 时间内蘑菇按正常速度生长。在两个时间段内第 $i$ 个蘑菇会分别用 ${a_i,b_i}$ 的速度生长。现编程给定上述量，求解每个蘑菇的最高高度，按高度**从大到小**输出，若高度相同按编号**从小到大**输出。

## 题目分析

对于题目，先用一个结构体去包装每个蘑菇。这里有一个小技巧，为了防止小数的出现，由于本题保留 $2$ 位小数，可以将高度扩大到 $100$ 倍去存储，输出的时候再缩回去。

排序方面我比较习惯重载小于号，当然写一个 `bool cmp(mushroom a, mushroom b)` 函数也是没有问题的。

```cpp
struct mushroom {
	int h, id;
	inline bool operator < (const mushroom& A) const {
		if(h == A.h) return id < A.id;
		return h > A.h;
	}
	inline void print() {
		printf("%d %.2lf\n", id, 0.01 * h);
	}
}m[1145];
```
接下来，对于每个蘑菇我们只需要分别将速度 $a,b$ 交换顺序两次带入 $T_1,T_2$，分别计算高度取最大值即可。

```cpp
inline int calc(int a, int b) {
	int h1 = a * (100 - k) * t1 + b * 100 * t2;
	int h2 = a * 100 * t2 + b * (100 - k) * t1;
	return max(h1, h2);
}
```

最后排序输出即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct mushroom {
	int h, id;
	inline bool operator < (const mushroom& A) const {
		if(h == A.h) return id < A.id;
		return h > A.h;
	}
	inline void print() {
		printf("%d %.2lf\n", id, 0.01 * h);
	}
}m[1145];
inline int read() {
	int s = 0, f = 1;
	char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') f *= (-1);
		c = getchar();
	}
	while(isdigit(c)) {
		s = (s << 1) + (s << 3) + c - '0';
		c = getchar();
	}
	return s * f;
}
int n, t1, t2, k;
inline int calc(int a, int b) {
	int h1 = a * (100 - k) * t1 + b * 100 * t2;
	int h2 = a * 100 * t2 + b * (100 - k) * t1;
	return max(h1, h2);
}
signed main() {
	n = read(), t1 = read(), t2 = read(), k = read();
	for(int i = 1; i <= n; i ++) {
		int a = read(), b = read();
		m[i].id = i;
		m[i].h = calc(a, b);
	}
	sort(m + 1, m + 1 + n);
	for(int i = 1; i <= n; i ++)
		m[i].print();
	return 0;
}
```

---

## 作者：xiaokang_suancai (赞：0)

# CF186B 题解
[题目传送门](https://www.luogu.com.cn/problem/CF186B)
## 思路解析
一道非常不错的模拟题，由于每个选手都会采用最优方案，所以我们把通过两种策略种出来的蘑菇高度都算出来，然后取最大值即可。\
详细内容见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
double t1,t2,k,a[100005],b[100005],h1,h2;
struct mushroom
{
	int id;
	double h;
}m[100005];  // 结构体方便排序
bool cmp(mushroom x,mushroom y)
{
	if(x.h!=y.h)
		return x.h>y.h;
	else
		return x.id<y.id;
} // 在同样高度的情况下，编号小的选手排在前面
int main()
{
	cin>>n>>t1>>t2>>k; // 朴实无华的输入 
	k=k*1.0/100; // 由于题目输入的是百分数，所以要对 k 进行预处理
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++)
	{
		h1=a[i]*t1*(1-k)+b[i]*t2;
		h2=b[i]*t1*(1-k)+a[i]*t2;
		m[i].id=i;
		m[i].h=max(h1,h2); // 将两种策略产生的蘑菇高度进行比较，取最大值
	}
	sort(m+1,m+n+1,cmp); // 对选手的蘑菇排序
	for(int i=1;i<=n;i++)
	{
		cout<<m[i].id<<" ";
		cout<<fixed<<setprecision(2)<<m[i].h<<endl; // 注意输出两位小数
	}
	return 0; // 朴实无华的结束
}
```

---

## 作者：lostxxx (赞：0)

# 题解 CF186B

## 题目分析

在此处，我们需要考虑的只有 $a_i$ 和 $b_i$ 的使用先后关系。但是由于此处只有两个情况，于是我们无需多余判断，直接使用 ```max``` 函数求出最大然后按高度为第一关键字，```id``` 为第二关键词排序输出即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,t1,t2;
double k;
struct node{
	double c;
	ll id;
}x[200100];
double a,b;
bool cmp(node a,node b){
	if (a.c==b.c)
		return a.id<b.id;
	return a.c>b.c;
}
int main(){
	cin>>n>>t1>>t2>>k;
	for (int i=1;i<=n;i++){
		cin>>a>>b;
		x[i].id=i;
		x[i].c=max(a*t1*(100-k)/100+b*t2,b*t1*(100-k)/100+a*t2);
	}
	sort(x+1,x+n+1,cmp);
	for (int i=1;i<=n;i++){
		printf("%lld %.2lf\n",x[i].id,x[i].c);
	}
}
```

---

## 作者：2020luke (赞：0)

# [CF186B Growing Mushrooms](https://www.luogu.com.cn/problem/CF186B) 题解

## 思路解析

题目没有说 $a_i,b_i$ 分别对应 $t_1,t_2$ 中的哪一个，于是就要自己枚举每种情况。枚举完后用一个数组 $s$ 存下来，同时一起存下编号，然后按照重量 `sort` 即可。注意在重量相同时按编号从小到大排序。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define db double
#define PID pair<int, db>
#define fir first
#define sec second
const int N = 1010;
int n, t1, t2, k;
int a[N], b[N];
PID s[N];
int main() {
	scanf("%d%d%d%d", &n, &t1, &t2, &k);
	for(int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
		db v1 = (1.0 - (db)k / 100.0) * a[i] * t1 + 1.0 * b[i] * t2;
		db v2 = (1.0 - (db)k / 100.0) * b[i] * t1 + 1.0 * a[i] * t2;
		s[i].fir = i;
		s[i].sec = max(v1, v2);
	}
	sort(s + 1, s + n + 1, [](PID x, PID y) {
		if(x.sec != y.sec) return x.sec > y.sec;
		else return x.fir < y.fir;
	});
	for(int i = 1; i <= n; i++) {
		printf("%d %.2lf\n", s[i].fir, s[i].sec);
	}
	return 0;
}
```

---

## 作者：Tjl0427 (赞：0)

# 题解：CF186B Growing Mushrooms
[题目传送门。](https://www.luogu.com.cn/problem/CF186B#translate)
### 题意：
有 $n$ 个蘑菇，每个蘑菇生长速度分为 $t_1$ 和 $t_2$。在 $t_1$ 时间段速度会减少百分之 $k$。第 $i$ 个蘑菇以 $a_i,b_i$ 的速度生长，求出每个蘑菇的最大生长高度。高度从大到小输出，若高度相等，则先输出编号小的。
### 题目分析：
分别算出**先是速度 $a_i$ 再是速度 $b_i$ 生长的蘑菇的高度**和**先是速度 $b_i$ 再是速度 $a_i$ 生长的蘑菇的高度**。再取最大值就行了。
### 思路：
建立一个结构体，储存编号和高度：
```c
struct stu{
	int Identity_document;
	double height;
}c[100001];
```
输入数据：
```c
scanf("%d%lf%lf%lf",&n,&t1,&t2,&k);
k/=100;
for(inti=1;i<=n;i++)scanf("%lf%lf",&c1[i],&c2[i]);
```
储存每个蘑菇的编号和最大高度：
```c
for(int i=1;i<=n;i++){
		p1=(1-k)*c1[i]*t1+c2[i]*t2;
		p2=(1-k)*c2[i]*t1+c1[i]*t2;
		c[i]={i,max(p1,p2)};
	}
```
再写一个排序：
```c
bool cmp(stu a,stu b){
	if(a.height==b.height)
	return a.Identity_document<b.Identity_document;
	return a.height>b.height;
}
```
最后就可以输出了：
```c
for(int i=1;i<=n;i++)
printf("%d%.2lf\n",c[i].Identity_document,c[i].height);
```

---

