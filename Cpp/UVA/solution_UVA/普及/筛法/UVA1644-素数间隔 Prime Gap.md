# 素数间隔 Prime Gap

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4519

[PDF](https://uva.onlinejudge.org/external/16/p1644.pdf)

# 题解

## 作者：封禁用户 (赞：8)

这题卡了我很久，最后才发现是读入的问题……

此题考察的是大家筛质数的知识。

因为质数最大为$1299709$，如果你筛质数用这个，会T得很惨：

```cpp
for(int i=2;i*i<=n;++i)
	if(n%i==0) return 0;
return 1;
```

好啦，那都是题外话，下面是重要的内容。

刚才也提到了，用普通方法肯定会TLE，所以必须用更快的**线性筛**。

你首先要知道：

不管$x$是不是质数，$x$的倍数肯定是合数，因为Ta除了$1$和Ta本身还有因数$x$。

埃氏筛：


用一个$bool$数组记录各个数字的情况。$a_x$为$true$，表明$x$为合数，$a_x$为$false$，表明$x$为质数。循环遍历$a$数组，将$i$的倍数标记为$true$。

欧拉筛：

欧拉筛是对埃氏筛的优化，可以避免重复筛，让程序跑得更快。

保险起见，还是用欧拉筛吧。

```cpp
memset(visit,0,sizeof(visit));
memset(prime,0,sizeof(prime));
visit[1]=visit[0]=true;
for(register int i=2; i<=1299709; ++i) {
    if(!visit[i]) {
        prime[++ans]=i;
    }
    for(register int j=1; prime[j]*i<=1299709&&j<=ans; ++j) {
        visit[i*prime[j]]=true;
        if(!(i%prime[j])) break;
    }
}
```


接着要考虑的问题就是这句话：

>否则输出离它最近的两个质数（一个比$n$大，一个比$n$小）之差。

很容易想到，只要在存储素数的$prime$数组里查找就可以了。如果数据无误，那么，假定$prime_i$比$n$大，那$prime_{i-1}$肯定比$n$小了。

所以得出：

```cpp
if(!visit[x]) printf("0\n");
else {
    for(register int i=1; i<=ans; ++i)
        if(prime[i]>x) {
            printf("%d\n",prime[i]-prime[i-1]);
            break;
        }
}
```

最后就是我掉进的坑，读入了。

看了[这位大佬](https://www.luogu.com.cn/user/164056)的题解，我恍然大悟，原来$while$循环前面要先读入一次！

无语了……


$AC$ $Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,prime[800001],x;
bool visit[1299710];
int main() {
	scanf("%d",&x);
    memset(visit,0,sizeof(visit));
    memset(prime,0,sizeof(prime));
    visit[1]=visit[0]=true;
    for(register int i=2; i<=1299709; ++i) {
        if(!visit[i]) {
            prime[++ans]=i;
        }
        for(register int j=1; prime[j]*i<=1299709&&j<=ans; ++j) {
            visit[i*prime[j]]=true;
            if(!(i%prime[j])) break;
        }
    }
    while(x) {
        if(!visit[x]) printf("0\n");
        else {
            for(register int i=1; i<=ans; ++i)
                if(prime[i]>x) {
                    printf("%d\n",prime[i]-prime[i-1]);
                    break;
                }
        }
        scanf("%d",&x);
    }
    return 0;
}
```


对你有帮助就点个赞吧~

---

## 作者：Hoichai (赞：6)

蒟蒻的第一篇题解

------------
此题很水，~~不然我也做不上来~~emmm...很好奇题目难度是怎么定义的。

```c++
	cin>>n; //刚开始忘输了
	while(n)
	{
		//处理
		cin>>n;
	}
```

大部分Uva都要用这个输入处理emmm...(就像来自岛国的题都要输回车)别问我这句话为什么不放上面，因为~~太懒了~~还要讲题。

------------

题目就是判断质数。筛法和单判都能用。
单独判断有一个好处就是省空间和时间。
呐，就有人问了，单独判断为什么会省时间？
```c++
void （int x）
{
	if(x==2||x==3)
		return 1;
	else if(x%6!=1&&x%6!=5)
		return 0;
	else
	{
		int n=sqrt(x);
		for(int i=5;i<=n;i+=6)
			if(x%i==0||x%(i+2)==0)
				return 0;
		return 1;
	}	
}
```
[判断质数代码来自:](https://blog.csdn.net/huang_miao_xin/article/details/51331710)
直接上代码emmm....
```
#include<iostream>
#include<math.h>
using namespace std;
bool yzx(int x)
{
	if(x==2||x==3)
		return 1;
	else if(x%6!=1&&x%6!=5)
		return 0;
	else
	{
		int n=sqrt(x);
		for(int i=5;i<=n;i+=6)
			if(x%i==0||x%(i+2)==0)
				return 0;
		return 1;
	}
		
}
int main()
{
	int n;
	cin>>n;
	while(n)
	{
		if(yzx(n))
			cout<<0<<endl;
		else
		{
			int i=n-1;
			int j=n+1;
			while(!yzx(i))
				i--;
			while(!yzx(j))
				j++;
			cout<<j-i<<endl;
		}
		cin>>n;
	}
	return 0;
}
```





又该回去瑟瑟发抖了..

---

## 作者：MoXiaodu (赞：2)

### 题意：
有多组数据，每组一个n，若n为0，程序结束。若n为质数，输出0.否则输出离它最近的两个质数（一个比n大，一个比n小）之差。（质数最大为 1299709，即抵十万个素数。）
### 做法：线性素数筛（欧拉筛）
首先，由题意得，最多有十万个素数，且不超过1299709；所以我们使用线筛筛到1299709就可以了。

### 核心代码：
```cpp
void get_s(){
	for(int i=2;i<=1299709;i++){//筛到1299709
		if(!v[i]){//如果这个数是素数（没被筛除）
		tt++;//总数++
		pr[tt]=i;}//记录
		for(int j=1;pr[j]<=1299709/i;j++){
			v[pr[j]*i]=1;//筛掉她的倍数
			if(i%pr[j]==0)break;
//任何合数都能表示成多个素数的积。所以，任何的合数肯定有一个最小质因子。我们通过这个最小质因子就可以判断什么时候不用继续筛下去了。
// 当i是prime[j]的整数倍时，也就是（i%prime[j]==0），i*prime[j+1]肯定被筛过，跳出循环。
//因为i可以看做prime[j]*x， i*prime[j+1]就可以看做 prime[j]*x*prime[j+1] 。而 prime[j] 必定小于 prime[j+1]，
//i*prime[j+1]必定已经被prime[j]*x 筛掉，就不用再筛了
		}
	}
}
```
部分引用：[这里](https://blog.csdn.net/tianwei0822/article/details/78309453)

### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,tt;
int pr[10000005];
bool v[10000005];
inline long long read(){//读入优化
	long long out=0,f=1;char b=getchar();
	while(b>'9'|| b<'0'){
		if(b=='-')f=-1;
		b=getchar();
	}
	while(b>='0'&& b<='9'){
		out*=10;
		out+=b-'0';
		b=getchar();
	}
	return out*f;
}
void get_s(){//上面已经解释惹
	for(int i=2;i<=1299709;i++){
		if(!v[i]){
		tt++;
		pr[tt]=i;}
		for(int j=1;pr[j]<=1299709/i;j++){
			v[pr[j]*i]=1;
			if(i%pr[j]==0)break;
		}
	}
}
int main(){
	n=read();
	v[1]=1;
	get_s();
	while(n){
		if(v[n]==1){//如果不是素数
			for(int i=1;i<=100000;i++){//暴力查找
				if(pr[i]>n){//找到第一个比她大的数数，一定离她最近
					cout<<pr[i]-pr[i-1]<<endl;//直接输出
					break;
				}
			}
		}
		else printf("0\n");//是素数输出0
		n=read();//继续读入
	}
	return 0;
}
```


---

## 作者：xixike (赞：1)

这道题一眼看上去很简单，~~实际上也很简单~~，我们可以用线性筛预处理出前100000个素数，然后对于每一个n，用二分查找找到第一个大于n的素数所处的位置，用这个位置上的素数减去前一位上的素数即可。

**附代码**
```cpp
#include<iostream>
#include<cmath>

using namespace std;

int p[100010],mindiv[1300000];       //p数组存每一个质数，mindiv[i]表示是通过那个质数乘过来的数
int tot;

//-----------------线性筛代码
void prime(){
	for(int i=2;i<=1299709;i++){
		if(!mindiv[i]) p[++tot]=mindiv[i]=i;
		for(int j=1;j<=tot&&p[j]<=mindiv[i]&&i*p[j]<=1299709;j++)
			mindiv[i*p[j]]=i;
	}
}

int main(){
	int n;
	prime();
	while(cin>>n){
		if(!n) break;
		if(mindiv[n]==n){       //特判n为质数时，直接输出
			cout<<0<<endl;
			continue;
		}
		int l=1,r=tot;          //二分查找第一个大于n的质数的位置
		while(l<=r){
			int mid=(l+r)>>1;
			if(p[mid]<=n) l=mid+1;
			else r=mid-1;
		}
		cout<<p[l]-p[l-1]<<endl;  //l位置上的质数减去l-1位置上的质数就是答案
	}
	return 0;
}
```


---

## 作者：ffacs (赞：1)

为什么要二分查找呢...
```cpp
    for(rg int i=0;i<cnt-1;i++){
        for(rg int j=prime[i]+1;j<prime[i+1];j++)
            ans[j]=prime[i+1]-prime[i];
    }
```


---

## 作者：珅肐 (赞：1)

说一下优化做法

首先把素数都筛出来，就可以比较优秀的处理问题

利用$lower$_$bound$函数，可以将每次询问降到$O$($log$ $n$)

因为毕竟素数是单调，就不用一个一个找了

总复杂度$O$($q$ $log$ $n$)

#### 完整代码奉上：
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch))f|=ch=='-',ch=getchar();
	while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
	return f?-x:x;
}
bool is_not[1299807]={1,1};
int prime[100007],cnt;
inline void Prime(int N=1299777){//筛素数
	for(int i=2;i<=N;++i){
		if(!is_not[i])prime[++cnt]=i;
		for(int j=1;j<=cnt && i*prime[j]<=N;++j){
			is_not[i*prime[j]]=1;
			if(i%prime[j]==0)break; 
		} 
	}
}
int main(){
	Prime();int n;
	while(n=read()){
		if(!is_not[n])puts("0");//如果是素数输出0
		else{
			int o=lower_bound(prime+1,prime+cnt+1,n)-prime;
			//找到第一个大于它的素数，o就是下标，那o-1对应的就是小于它的素数，输出差即可
            printf("%d\n",prime[o]-prime[o-1]);
		}
	}
	return 0;
}
```


---

## 作者：wzhy (赞：1)

# **题目大意**

有多组数据，每组一个n，若n为0，程序结束。若n为质数，输出0.否则输出离它最近的两个质数（一个比n大，一个比n小）之差。（质数最大为 1299709，即抵十万个素数。）
# **分析**

可先用筛法筛一筛，预先处理出质数，然后输入n，若n为质数，输出0，若不为，可从第2个质数往后扫，当出现第一个大于n的数时，即可将他减去上一个质数，即为答案。时间为50ms。

上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int v[1300010],prime[1300010],m=0;
void P(){
    memset(prime,0,sizeof(prime));
    memset(v,0,sizeof(v));
    for(int i=2;i<=1300010;i++){
        if(!v[i]){
            v[i]=i;
            prime[++m]=i;
        }
        for(int j=1;j<=m;j++){
            if(prime[j]>v[i]||prime[j]>1300010/i)
                break;
            v[i*prime[j]]=prime[j];
        }
    }
}
int main(){
    P();
    int n;
    while(scanf("%d",&n)){
        if(!n)
            return 0;
        if(v[n]==n){
            cout<<0<<endl;
            continue;
        }
        for(int j=2;j<=100000;j++){
            if(prime[j]>n){
                cout<<prime[j]-prime[j-1]<<endl;
                break;
            }	
        }
    }
}
```

---

## 作者：yoyiETO (赞：0)

## 题解 UVA1644 【素数间隔 Prime Gap】

有意做题者请先完成P3912，[传送门](https://www.luogu.com.cn/problem/P3912)

**【分析】**：还是先看数据范围：质数最大为 1299709,如果用普通方法$O(n\sqrt{n})$显然爆了，所以需要用**埃氏筛法**。

**【新算法】** 

名称：埃氏筛法

时间复杂度：$O(n log n)$(证明看[这里](https://www.zhihu.com/question/35112789?sort=created)，看不懂也没事)

效果：高效率筛出一个区间中的所有素数.

⒈所有数默认为素数。

⒉所有偶数标记为合数，节省时间。

3.$i$循环，枚举$1$~$\sqrt{n}$.

4.$j$循环，枚举$n$÷$i$,保证覆盖到每个数。

5.将$i$×$j$标记为合数。

```cpp
for(int i=4;i<=100000000;i+=2)
		ok[i]=1;
	for(int i=3;i*i<=n;i+=2)
        if(!ok[i])
            for(int j=3;j*i<=n;j+=2)
                ok[i*j]=1;
```
代入到本题就很简单了，如果$n=0$输出$0$,否则往左&右枚举。

**AC Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int n=2000000;
int k;
bool ok[2000001];
int main()
{
	for(int i=4;i<=2000000;i+=2)
		ok[i]=1;
	for(int i=3;i*i<=n;i+=2)
        if(!ok[i])
            for(int j=3;j*i<=n;j+=2)
                ok[i*j]=1;
    while(cin>>k)
    {
    	if(!k||!ok[k]) cout<<"0\n";
		else{
			for(int i=k-1;;i--)
				if(!ok[i]){
					cout<<i<<" ";
					break;
				}
			for(int i=k+1;;i++)
				if(!ok[i]){
					cout<<i<<"\n";
					break;
				}
		} 
	}
	return 0;
}
```

---

## 作者：光阴且含笑 (赞：0)

**思路：欧拉筛＋二分**

先筛出1到1299709内所有素数

每次读入n进行判断

若n为素数则输出0

若n不为素数则二分，下标从1到100000，l最终为第一个大于n的素数的下标

输出num[l]-num[l-1]

AC代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool Prime[1299710];
int step=0,num[1299710];
int l,r;
int main(){
	memset(Prime,true,sizeof(Prime));//欧拉筛模板
	Prime[1]=0;
	for(int i=2;i<=1299709;i++){
		if(Prime[i]) num[++step]=i;
		for(int j=1;j<=step&&i*num[j]<=1299709;j++){
			Prime[i*num[j]]=0;
			if(!i%num[j]) break;
		}
	}
	while(scanf("%d",&n)){
		if(n==0) return 0;//若为0则结束程序
		if(Prime[n]){//若为素数则输出0并换行
			printf("0\n");
			continue;
		}
		l=1,r=100000;//二分
		while(l<r){
			int mid=(l+r)>>1;
			if(num[mid]>n) r=mid;
			else l=mid+1;
		}
		printf("%d\n",num[l]-num[l-1]);
	}
	return 0;
}
```


---

## 作者：COUPDETAT (赞：0)

# 埃氏筛+二分查找

楼上楼下都说此题过水 ~~可我还是wa了好几发~~

对于筛素数的方法有很多种 包括线性的 但是埃氏筛我觉得就已经够用了
## 埃氏筛模板
```
void solve()
{
	for(ll i=2;i<=1299709;i++)
	if(!vis[i])
	{
		a[++N]=i;
		for(ll j=i*i;j<=1299709;j+=i) vis[j]=1;
	}	
}	
```
## 二分查找
：**lower_bound**( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于或等于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。

**upper_bound**( begin,end,num)：从数组的begin位置到end-1位置二分查找第一个大于num的数字，找到返回该数字的地址，不存在则返回end。通过返回的地址减去起始地址begin,得到找到数字在数组中的下标。



```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
long long  a[1500100],vis[1500100],N;
long long  n;
void solve()
{
	for(ll i=2;i<=1299709;i++)
	if(!vis[i])
	{
		a[++N]=i;
		for(ll j=i*i;j<=1299709;j+=i) vis[j]=1;
	}	
}	
int main()
{
	solve();

	while(1)
	{
		cin>>n;
		
		if(n==0) return 0;
		long long  pl=lower_bound(a+1,a+N+1,n)-a;
		//cout<<pl<<endl;
//		if(a[pl]==n) 
		if(!vis[n]) 
		{
			cout<<0<<endl;
		}
		else 
		{
			cout<<a[pl]-a[pl-1]<<endl;
		}
	}
	return 0;
}
```


---

## 作者：天际之光 (赞：0)

## ~~本题大水！~~


 本题先用欧拉质数筛法，而且只把这个数是否是质数的数据筛出（不用数组把质数存起来！循环到sqrt(n)就可以把后面的合数全部找出来并标记，所以循环到i*i<=1299709就够了，没有必要打整个质数表）。之后首先判定这个数是不是质数，不是的话直接输出0看下一组数据，否则从输入的这个数据开始往两边找质数，后输出。~~（时间复杂度0ms）~~
 
 不多说，上代码，大神勿喷：
 ```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n,b,s;//n为输入的这个数，b和s分别为后面的质数与前面的质数
bool a[1299710];//存是否为质数的数组a
void find_prime(){//寻找质数
    for(int i=2;i*i<=1299709;i++）//因为循环到sqrt(n)就可以把后面的合数全部找出来，所以循环到i*i<=1299709就够了（这个还是要自己理解）
        if(a[i]==false){//找到了一个质数
            for(int j=i;j*i<=1299709;j++){//标记不是质数的（第一个数为i*i,欧拉质数筛法，只标记一次，时间复杂度低）
                a[i*j]=true;//标记合数
            }
        }
    }
}
int main(){
    find_prime();
    while(scanf("%d",&n),n!=0){//判断输入的是否为0
        if(a[n]==false){//如果是质数
            printf("0\n");//直接输出0
            continue;//返回读入下一组数据
        }
        for(int j=n;j>=2;j--){//找前面的质数
            if(a[j]==false){//找到了
                s=j;//记录
                break;//跳出循环
            }
        }
        for(int j=n;;j++){//找后面的质数
            if(a[j]==false){//找到了
                b=j;//记录
                break;//跳出循环
            }
        }
        printf("%d\n",b-s);//输出两数之差
    }
    return 0;//读入到0后漂亮地结束！
}
```


---

## 作者：净霖 (赞：0)

有多组数据，每组一个n，若n为0，程序结束。若n为质数，输出0.否则输出离它最近的两个质数（一个比n大，一个比n小）之差。（质数最大为 1299709，即抵十万个素数。）

真的hei水 非常水 超级无敌水 拿来背质数筛! ![](http://images.cnblogs.com/cnblogs_com/lxyyyy/1402222/t_3de3d319eec334.jpg)

线性筛法 -- 欧拉筛法
比普通的Eratosthenes筛法（复杂度为(O(nloglogn)）效率要高些 为O(N)

原本的Eratosthenes筛法，其复杂度为O(nloglogn),会重复标记合数 像6=2*3，他会被2筛一次，还会被3筛一次。而欧拉筛法用v数组储存每个数的最小质因子 每个数只会被它最小的质因数筛一次

其他题可能会用到这个：prime[j]必定是prime[j]*i的最小质因子

```c
void primes(int n)
{
    memset(v,0,sizeof(v));//最小质因子
    cnt=0;//质数数量 
    for(int i=2;i<=n;i++)
    {//给i乘上一个质因子
        if(!v[i]) v[i]=i,prime[++cnt]=i;//若i为质数
        for(int j=1;j<=cnt;j++)
        if(prime[j]>v[i]||prime[j]>(n/i)) break;//i有比prime[j]更小的质因子||超出n的范围
        else v[i*prime[j]]=prime[j];
    }
}
```
然后就先把素数预先处理出来  如果它的最小质因子为它本身即v[x]==x则 x为素数
如果不是素数 就从左往右扫出第一个大于x的素数prime[i] 然后输出prime[i]-prime[i-1]

最后
```
#include<bits/stdc++.h>
using namespace std;
const int X=1299709+5;
int n,k;
int v[X],pri[X],cnt;
template<class t>void rd(t &x)
{
    x=0;int w=0;char ch=0;
    while(!isdigit(ch)) w|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    x=w?-x:x;
}

void prime()
{
    memset(v,0,sizeof(v));//最小质因子
    memset(pri,0,sizeof(pri));
    cnt=0;//质数数量 
    for(int i=2;i<=X;i++)
    {        
        if(!v[i]) v[i]=i,pri[++cnt]=i;
        for(int j=1;j<=cnt;j++)
        if(pri[j]>v[i]||pri[j]>(X/i)) break;
        else v[i*pri[j]]=pri[j];
    }
}

int main()
{
    prime();
    while(scanf("%d",&n)&&n)
    {
        if(v[n]==n) printf("0\n");
        else
            for(int i=2;i<=cnt;i++)
            if(pri[i]>n)
            {
                printf("%d\n",pri[i]-pri[i-1]);
                break;
            }
    }
    return 0;
}
```
暗戳戳放一下[blog](https://www.cnblogs.com/lxyyyy/)

---

